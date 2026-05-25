#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <fstream>
#include <stdexcept>
#include <string_view>
#include <algorithm>

namespace GameSettings {
    const std::string SAVE_FILE_NAME = "save.dat";
    
    constexpr int POTION_PRICE = 15;
    constexpr int WEAPON_PRICE = 50;
    constexpr int ARMOR_PRICE = 45;

    constexpr size_t MAX_INVENTORY_SLOTS = 3;
}
class GameException : public std::runtime_error {
public:
    explicit GameException(const std::string& message) : std::runtime_error(message) {}
};

class SaveLoadException : public GameException {
public:
    explicit SaveLoadException(const std::string& message) : GameException("Save/Load Error: " + message) {}
};

class InventoryException : public GameException {
public:
    explicit InventoryException(const std::string& message) : GameException("Inventory Error: " + message) {}
};

class BattleException : public GameException {
public:
    explicit BattleException(const std::string& message) : GameException("Battle Error: " + message) {}
};

class ShopException : public GameException {
public:
    explicit ShopException(const std::string& message) : GameException("Shop Error: " + message) {}
};

class Logger {
private:
    std::vector<std::string> m_history;

public:
    Logger() = default;
    
    void log(std::string_view message) {
        m_history.emplace_back(message);
    }

    void print() const {
        std::cout << "\n--- [GAME LOG HISTORY] ---\n";
        if (m_history.empty()) {
            std::cout << "No logs recorded yet.\n";
        } else {
            for (auto it = m_history.cbegin(); it != m_history.cend(); ++it) {
                std::cout << " -> " << *it << "\n";
            }
        }
        std::cout << "--------------------------\n";
    }

    void clear() {
        m_history.clear();
    }
};

class Item {
protected:
    std::string m_name;
    int m_value;

public:
    Item(std::string name, int value) : m_name(std::move(name)), m_value(value) {}
    virtual ~Item() = default;

    virtual void use() = 0; 
    
    [[nodiscard]] std::string getName() const { return m_name; }
    [[nodiscard]] int getValue() const { return m_value; }
};

class Potion : public Item {
public:
    Potion() : Item("Health Potion", 25) {}
    void use() override { std::cout << "Gulp! Restored " << m_value << " HP.\n"; }
};

class Weapon : public Item {
public:
    Weapon() : Item("Iron Sword", 15) {}
    void use() override { std::cout << "Equipped " << m_name << " (+" << m_value << " Attack).\n"; }
};

class Armor : public Item {
public:
    Armor() : Item("Steel Breastplate", 10) {}
    void use() override { std::cout << "Equipped " << m_name << " (+" << m_value << " Defense).\n"; }
};

class Inventory {
private:
    std::vector<std::unique_ptr<Item>> m_items;

public:
    Inventory() = default;

    void addItem(std::unique_ptr<Item> item) {
        if (!item) return;

        if (m_items.size() >= GameSettings::MAX_INVENTORY_SLOTS) {
            throw InventoryException("Your inventory is absolutely full! (" 
                                     + std::to_stdio_string(GameSettings::MAX_INVENTORY_SLOTS) + " slots max)");
        }
        m_items.emplace_back(std::move(item));
    }

    void showInventory() const {
        std::cout << "--- Inventory Slots (" << m_items.size() << "/" << GameSettings::MAX_INVENTORY_SLOTS << ") ---\n";
        if (m_items.empty()) {
            std::cout << "[Empty]\n";
            return;
        }
        for (size_t i = 0; i < m_items.size(); ++i) {
            std::cout << i + 1 << ". " << m_items[i]->getName() << "\n";
        }
    }

    void useItem(size_t index) {
        if (index >= m_items.size()) {
            throw InventoryException("Invalid action: select a valid slot index!");
        }
        m_items[index]->use();
        if (dynamic_cast<Potion*>(m_items[index].get())) {
            m_items.erase(m_items.begin() + index);
        }
    }
    
    [[nodiscard]] size_t getSize() const { return m_items.size(); }
};

class Character {
protected:
    std::string m_name;
    int m_health;
    int m_maxHealth;
    int m_damage;
    int m_gold;
    Inventory m_inventory; 

public:
    Character(std::string name, int hp, int dmg, int gold)
        : m_name(std::move(name)), m_health(hp), m_maxHealth(hp), m_damage(dmg), m_gold(gold) {}
        
    virtual ~Character() = default;

    virtual void uniqueAction() = 0;

    void takeDamage(int dmg) {
        m_health = std::max(0, m_health - dmg);
        std::cout << m_name << " takes " << dmg << " damage! (Current HP: " << m_health << ")\n";
    }

    void heal(int amount) {
        m_health = std::min(m_maxHealth, m_health + amount);
        std::cout << m_name << " heals for " << amount << ". (Current HP: " << m_health << ")\n";
    }

    [[nodiscard]] bool isAlive() const { return m_health > 0; }
    
    [[nodiscard]] std::string getName() const { return m_name; }
    [[nodiscard]] int getGold() const { return m_gold; }
    void modifyGold(int amount) { m_gold += amount; }
    
    Inventory& getInventory() { return m_inventory; }
    [[nodiscard]] const Inventory& getInventory() const { return m_inventory; }
};

class Warrior : public Character {
public:
    explicit Warrior(std::string name) : Character(std::move(name), 100, 10, 50) {}
    void uniqueAction() override { std::cout << "[Shield Slam] Blocked incoming attack and stunned enemy!\n"; }
};

class Archer : public Character {
public:
    explicit Archer(std::string name) : Character(std::move(name), 85, 14, 60) {}
    void uniqueAction() override { std::cout << "[Double Shot] Fired two arrows in rapid succession!\n"; }
};

class Mage : public Character {
public:
    explicit Mage(std::string name) : Character(std::move(name), 70, 18, 100) {}
    void uniqueAction() override { std::cout << "[Fireball] Unleashed massive area-of-effect elemental burst!\n"; }
};

class Rogue : public Character {
public:
    explicit Rogue(std::string name) : Character(std::move(name), 80, 15, 75) {}
    void uniqueAction() override { std::cout << "[Shadowstep] Vanished into shadows for a critical backstab!\n"; }
};

class Enemy {
protected:
    std::string m_type;
    int m_health;
    int m_damage;

public:
    Enemy(std::string type, int hp, int dmg) : m_type(std::move(type)), m_health(hp), m_damage(dmg) {}
    virtual ~Enemy() = default;

    [[nodiscard]] bool isAlive() const { return m_health > 0; }
    [[nodiscard]] std::string getType() const { return m_type; }
    [[nodiscard]] int getDamage() const { return m_damage; }
    
    void takeDamage(int amount) { m_health = std::max(0, m_health - amount); }
};

class Goblin : public Enemy {
public:
    Goblin() : Enemy("Goblin Scout", 30, 5) {}
};

class Skeleton : public Enemy {
public:
    Skeleton() : Enemy("Undead Skeleton", 45, 8) {}
};

class Boss : public Enemy {
public:
    Boss() : Enemy("Dragon Overlord", 120, 20) {}
};

class BattleSystem {
public:
    static bool startFight(Character& player, std::unique_ptr<Enemy> enemy) {
        if (!enemy) throw BattleException("Cannot start a battle against an empty void!");

        std::cout << "\n!!! BATTLE STARTED: " << player.getName() << " vs " << enemy->getType() << " !!!\n";
        
        while (player.isAlive() && enemy->isAlive()) {
            std::cout << "\n-- Battle Menu --\n1. Basic Attack\n2. Special Ability\n3. Run Away\nChoose option: ";
            
            int action;
            if (!(std::cin >> action)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }

            if (action == 1) {
                enemy->takeDamage(15); 
                std::cout << "You hit " << enemy->getType() << "!\n";
            } else if (action == 2) {
                player.uniqueAction();
                enemy->takeDamage(25);
            } else if (action == 3) {
                std::cout << "Fled successfully.\n";
                return false;
            }

            if (enemy->isAlive()) {
                player.takeDamage(enemy->getDamage());
            }
        }

        if (player.isAlive()) {
            std::cout << "\nVictory! You earned 30 gold.\n";
            player.modifyGold(30);
            return true;
        }
        return false;
    }
};

class DungeonSystem {
public:
    void displayDungeonMenu(Character& player, Logger& logger) {
        bool inDungeonMenu = true;
        while (inDungeonMenu) {
            std::cout << "\n=== DUNGEON SELECTION ===\n1. Easy\n2. Medium\n3. Hard\n4. Back\nSelect level: ";

            int level;
            if (!(std::cin >> level)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }

            std::unique_ptr<Enemy> activeEnemy = nullptr;
            switch (level) {
                case 1: activeEnemy = std::make_unique<Goblin>(); logger.log("Entered Easy Dungeon."); break;
                case 2: activeEnemy = std::make_unique<Skeleton>(); logger.log("Entered Medium Dungeon."); break;
                case 3: activeEnemy = std::make_unique<Boss>(); logger.log("Challenged the Dragon Boss."); break;
                case 4: inDungeonMenu = false; break;
                default: std::cout << "Unknown choice.\n";
            }

            if (activeEnemy) {
                if (!BattleSystem::startFight(player, std::move(activeEnemy))) {
                    inDungeonMenu = false; 
                }
            }
        }
    }
};

class ShopSystem {
public:
    void openShop(Character& player, Logger& logger) {
        bool inShop = true;
        while (inShop) {
            std::cout << "\n=== TOWN MERCHANT SHOP ===\n"
                      << "Your Gold: " << player.getGold() << "g\n"
                      << "1. Buy Health Potion (" << GameSettings::POTION_PRICE << " gold)\n"
                      << "2. Buy Iron Sword (" << GameSettings::WEAPON_PRICE << " gold)\n"
                      << "3. Buy Steel Armor (" << GameSettings::ARMOR_PRICE << " gold)\n"
                      << "4. Leave Shop\n"
                      << "Choose transactional item: ";

            int choice;
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }

            std::unique_ptr<Item> purchasedItem = nullptr;
            int finalCost = 0;

            switch (choice) {
                case 1: purchasedItem = std::make_unique<Potion>(); finalCost = GameSettings::POTION_PRICE; break;
                case 2: purchasedItem = std::make_unique<Weapon>(); finalCost = GameSettings::WEAPON_PRICE; break;
                case 3: purchasedItem = std::make_unique<Armor>(); finalCost = GameSettings::ARMOR_PRICE; break;
                case 4: inShop = false; break;
                default: std::cout << "The merchant stares at you blankly.\n";
            }

            if (purchasedItem) {
                if (player.getGold() < finalCost) {
                    throw ShopException("Inadequate monetary funds to complete trade! You need " 
                                        + std::to_string(finalCost) + " gold.");
                }
                player.getInventory().addItem(std::move(purchasedItem));
                player.modifyGold(-finalCost);
                logger.log("Purchased gear successfully.");
                std::cout << "Transaction successful! Item added to inventory.\n";
            }
        }
    }
};

class SaveSystem {
public:
    void saveProgress(const std::unique_ptr<Character>& player) {
        if (!player) throw SaveLoadException("No active hero session to save!");

        std::ofstream file(GameSettings::SAVE_FILE_NAME);
        if (!file.is_open()) {
            throw SaveLoadException("Critical data lock! Failed to open system stream.");
        }

        file << player->getName() << "\n";
        file << player->getGold() << "\n";
        std::cout << "Game progress recorded successfully.\n";
    }

    std::unique_ptr<Character> loadProgress() {
        std::ifstream file(GameSettings::SAVE_FILE_NAME);
        if (!file.is_open()) {
            throw SaveLoadException("No save file detected on local storage device.");
        }

        std::string heroName;
        int heroGold;
        if (!(file >> heroName >> heroGold)) {
            throw SaveLoadException("Save data block is corrupted or read process failed.");
        }

        std::cout << "Data loaded successfully!\n";
        return std::make_unique<Warrior>(heroName);
    }
};

class Game {
private:
    bool m_isRunning;
    std::unique_ptr<Character> m_activePlayer;
    Logger m_logger;
    SaveSystem m_saveSystem;
    DungeonSystem m_dungeonSystem;
    ShopSystem m_shopSystem;

public:
    Game() : m_isRunning(true), m_activePlayer(nullptr) {}

    void run() {
        m_logger.log("Core system engine active.");
        while (m_isRunning) {
            if (!m_activePlayer) {
                showMainMenu();
            } else if (!m_activePlayer->isAlive()) {
                std::cout << "\nYour character has dead. Returning to Main Menu.\n";
                m_activePlayer.reset();
            } else {
                showGameMenu();
            }
        }
    }

private:
    void showMainMenu() {
        std::cout << "\n=== RPG MAIN MENU ===\n1. New Game\n2. Continue\n3. View Logs\n4. Exit\nChoose option: ";
        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            return;
        }

        switch (choice) {
            case 1: showClassSelectionMenu(); break;
            case 2: 
                try {
                    m_activePlayer = m_saveSystem.loadProgress();
                    m_logger.log("Loaded game file successfully.");
                } catch (const SaveLoadException& e) {
                    std::cerr << "\n[SYSTEM ERROR]: " << e.what() << "\n";
                }
                break;
            case 3: m_logger.print(); break;
            case 4: m_isRunning = false; break;
            default: std::cout << "Invalid protocol choice.\n";
        }
    }

    void showClassSelectionMenu() {
        std::cout << "\nEnter your hero's name: ";
        std::string name;
        std::cin >> name;

        std::cout << "\n=== CHOOSE YOUR ARCHETYPE ===\n1. Warrior\n2. Archer\n3. Mage\n4. Rogue\n5. Exit\nChoose: ";
        int classChoice;
        if (!(std::cin >> classChoice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            return;
        }

        switch (classChoice) {
            case 1: m_activePlayer = std::make_unique<Warrior>(name); break;
            case 2: m_activePlayer = std::make_unique<Archer>(name); break;
            case 3: m_activePlayer = std::make_unique<Mage>(name); break;
            case 4: m_activePlayer = std::make_unique<Rogue>(name); break;
            case 5: m_isRunning = false; break;
            default: m_activePlayer = std::make_unique<Warrior>(name);
        }
        if (m_activePlayer) m_logger.log("Manifested hero: " + m_activePlayer->getName());
    }

    void showGameMenu() {
        std::cout << "\n=== MAIN TOWN SQUARE ===\n"
                  << "Hero: " << m_activePlayer->getName() << " | Gold: " << m_activePlayer->getGold() << "g\n"
                  << "1. Go into the dungeon\n"
                  << "2. Go to the shop\n"
                  << "3. Go rest in home (Manage Inventory & Rest)\n"
                  << "4. Save game\n"
                  << "5. Exit to Main Menu\n"
                  << "Choose action: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            return;
        }

        try {
            switch (choice) {
                case 1: m_dungeonSystem.displayDungeonMenu(*m_activePlayer, m_logger); break;
                case 2: m_shopSystem.openShop(*m_activePlayer, m_logger); break;
                case 3: manageHomeRestContext(); break;
                case 4: m_saveSystem.saveProgress(m_activePlayer); m_logger.log("Progress saved."); break;
                case 5: m_activePlayer.reset(); m_logger.log("Exited back to main menu."); break;
                default: std::cout << "Invalid destination.\n";
            }
        }
        catch (const InventoryException& err) {
            std::cout << "\n[INVENTORY WARNING]: " << err.what() << " Clean up items before trying again!\n";
            m_logger.log(std::string("Inventory block: ") + err.what());
        }
        catch (const ShopException& err) {
            std::cout << "\n[SHOP REJECTION]: " << err.what() << " Go hunt some monsters to get more gold!\n";
            m_logger.log(std::string("Shop transaction declined: ") + err.what());
        }
        catch (const GameException& err) {
            std::cerr << "\n[GENERAL GAME EXCEPTION]: " << err.what() << "\n";
            m_logger.log(std::string("Runtime warning: ") + err.what());
        }
    }

    void manageHomeRestContext() {
        m_logger.log("Hero visited home sanctuary.");
        m_activePlayer->heal(100); 
        
        bool insideHome = true;
        while (insideHome) {
            std::cout << "\n--- HOME SANCTUARY ---\n1. Inspect and use items\n2. Return to Town\nChoose: ";
            int homeChoice;
            if (!(std::cin >> homeChoice)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                continue;
            }

            if (homeChoice == 1) {
                m_activePlayer->getInventory().showInventory();
                if (m_activePlayer->getInventory().getSize() > 0) {
                    std::cout << "Enter slot index to activate item (or 0 to cancel): ";
                    size_t slot;
                    std::cin >> slot;
                    if (slot > 0) {
                        try {
                            m_activePlayer->getInventory().useItem(slot - 1);
                        } catch (const InventoryException& itemErr) {
                            std::cout << "\n[ITEM ERROR]: " << itemErr.what() << "\n";
                        }
                    }
                }
            } else {
                insideHome = false;
            }
        }
    }
};

int main() {
    try {
        Game systemEngine;
        systemEngine.run();
    } 
    catch (const std::exception& fatal) {
        std::cerr << "CRITICAL CORE ABORT: " << fatal.what() << "\n";
        return 1;
    }
    catch (...) {
        std::cerr << "CRITICAL CORE ABORT: Unknown environment exception.\n";
        return 2;
    }
    return 0;
}
