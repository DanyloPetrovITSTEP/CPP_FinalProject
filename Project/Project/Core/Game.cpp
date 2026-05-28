#include "Game.h"
#include "Exceptions.h"

#include "../Characters/Character.h"
#include "../Characters/Warrior.h"
#include "../Characters/Archer.h"
#include "../Characters/Mage.h"
#include "../Characters/Rogue.h"
#include "../World/Dungeon.h"
#include "../World/Shop.h"
#include "../Items/Potion.h"

#include <iostream>
#include <ctime>

bool CanEquipWeapon(const Character& player, const Weapon& weapon)
{
    std::string className = player.getClassName();
    WeaponClass requiredClass = weapon.getRequiredClass();

    if (className == "Warrior" && requiredClass == WeaponClass::Warrior)
    {
        return true;
    }

    if (className == "Archer" && requiredClass == WeaponClass::Archer)
    {
        return true;
    }

    if (className == "Mage" && requiredClass == WeaponClass::Mage)
    {
        return true;
    }

    if (className == "Rogue" && requiredClass == WeaponClass::Thief)
    {
        return true;
    }

    return false;
}

Game::Game() 
    : m_isRunning(true), 
      m_player(nullptr), 
      m_saveSystem("save.dat"),
      m_equippedWeapon(nullptr),
      m_equippedArmor(nullptr) {}

void Game::run() {
    srand(static_cast<unsigned int>(time(nullptr)));
    m_logger.log("System Engine running safely.");
    
    while (m_isRunning) {
        if (!m_player) {
            showMainMenu();
        } else if (!m_player->isAlive()) {
            std::cout << "\n[GAME OVER] " << m_player->getName() << " has been killed!\n";
            m_logger.log("Player character died: " + m_player->getName());
            m_player.reset(); 
        } else {
            showGameMenu();
        }
    }
}

void Game::showMainMenu() {
    std::cout << "\n=== MEDIEVAL HEROES | CONSOLE EDITION ===\n"
              << "1. Start New Journey\n"
              << "2. Load Saved Progression\n"
              << "3. Display Engine Logs\n"
              << "4. Quit Application\n"
              << "Selection: ";
              
    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return;
    }

    switch (choice) {
        case 1: startNewGame(); break;
        case 2: continueGame(); break;
        case 3: m_logger.print(); break;
        case 4: m_isRunning = false; break;
        default: std::cout << "Action unrecognised.\n";
    }
}

void Game::showGameMenu() {
    std::cout << "\n=== HERO PROFILE: " << m_player->getName() << " (" << m_player->getClassName() << ") ===\n"
              << "HP: " << m_player->getHealth() << "/" << m_player->getMaxHealth() << "\n"
              << "Damage: " << m_player->getDamage() << "\n"
              << "Current Wealth: " << m_player->getGold() << " Gold\n"
              << "Active Weapon: " << (m_equippedWeapon ? m_equippedWeapon->getName() : "Bare Hands") << "\n"
              << "Active Armor: " << (m_equippedArmor ? m_equippedArmor->getName() : "None") << "\n"
              << "----------------------------------------\n"
              << "1. Travel into Danger (Dungeons)\n"
              << "2. Visit Town Marketplace (Shop)\n"
              << "3. Rest at Safehouse (+25 HP Recovery)\n"
              << "4. Commit Progress to Save File\n"
              << "5. Disconnect Profile (Main Menu)\n"
              << "Action: ";

    int choice;
    if (!(std::cin >> choice)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return;
    }

    try {
        switch (choice) {
            case 1: goToDungeon(); break;
            case 2: goToShop(); break;
            case 3: restAtHome(); break;
            case 4: saveGame(); break;
            case 5: m_player.reset(); break;
            default: std::cout << "Invalid action choice.\n";
        }
    } 
    catch (const InventoryException& ex) {
        std::cout << "\n[Inventory Rejection Trap]: " << ex.what() << "\n";
        m_logger.log(std::string("Inventory rejection: ") + ex.what());
    } 
    catch (const ShopException& ex) {
        std::cout << "\n[Marketplace Error Notice]: " << ex.what() << "\n";
        m_logger.log(std::string("Shop interaction exception raised: ") + ex.what());
    } 
    catch (const GameException& ex) {
        std::cerr << "\n[Core System Halt caught]: " << ex.what() << "\n";
        m_logger.log(std::string("General Exception processed: ") + ex.what());
    }
}

void Game::startNewGame() {
    m_inventory.clear();
    m_equippedWeapon = nullptr;
    m_equippedArmor = nullptr;

    selectCharacterClass();
}

void Game::continueGame() {
    try {
        m_player = m_saveSystem.loadGame(m_inventory, m_equippedWeapon, m_equippedArmor);

        if (m_equippedWeapon)
        {
            m_player->setWeaponDamageBonus(m_equippedWeapon->getDamage());
        }

        if (m_equippedArmor)
        {
            m_player->setArmorDefense(m_equippedArmor->getDefense());
        }

        std::cout << "\nGame loaded successfully!\n";
    }
    catch (const SaveLoadException& ex) {
        std::cout << "\n[I/O Failure Intercepted]: " << ex.what() << "\n";
    }
}

void Game::selectCharacterClass() {
    std::cout << "\nEnter character moniker: ";
    std::string name;
    std::cin >> name;

    std::cout << "\nSelect Subclass Profile:\n1. Warrior\n2. Archer\n3. Mage\n4. Rogue\nIndex: ";
    int profileIndex;
    if (!(std::cin >> profileIndex)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        profileIndex = 1;
    }
    
    switch (profileIndex) {
        case 1: m_player = std::make_unique<Warrior>(name); break;
        case 2: m_player = std::make_unique<Archer>(name); break;
        case 3: m_player = std::make_unique<Mage>(name); break;
        case 4: m_player = std::make_unique<Rogue>(name); break;
        default: m_player = std::make_unique<Warrior>(name); break;
    }
    m_logger.log("Character registered: " + m_player->getName());
}

void Game::goToDungeon() {
    m_logger.log("Player transitioned environment contexts to Dungeons.");
    Dungeon dummyDungeon("", {}, 0, m_logger);
    dummyDungeon.showMenu(*m_player, m_inventory);
}

void Game::goToShop() {
    m_logger.log("Player transitioned environment contexts to Marketplace Shop.");
    Shop marketplace;
    
    int menuActive = true;
    while (menuActive) {
        marketplace.showAssortment();
        std::cout << "\nCurrent Balance: " << m_player->getGold() << " Gold\n";
        std::cout << "\n1. Purchase Item\n2. Sell Item from Inventory\n3. Show Inventory\n4. Leave Merchant\nChoice: ";
        int actionIndex;
        std::cin >> actionIndex;

        try {
            if (actionIndex == 1) {
                std::cout << "Enter item index code to buy: ";
                size_t buyIdx; std::cin >> buyIdx;
                int currentGold = m_player->getGold();

                if (buyIdx == 0)
                {
                    std::cout << "Invalid item index.\n";
                    continue;
                }
                
                marketplace.buyItem(buyIdx - 1, m_inventory, currentGold);

                int goldSpent = m_player->getGold() - currentGold;
                m_player->spendGold(goldSpent);

                std::cout << "Gold left: " << m_player->getGold() << "\n";
                m_logger.log("Item successfully bought by " + m_player->getName());
            } 
            else if (actionIndex == 2) {
                m_inventory.showItems();
                if (!m_inventory.isEmpty()) {
                    std::cout << "Enter index item to liquidate: ";
                    size_t sellIdx; std::cin >> sellIdx;
                    int currentGold = m_player->getGold();

                    if (sellIdx == 0)
                    {
                        std::cout << "Invalid item index.\n";
                        continue;
                    }

                    marketplace.sellItem(sellIdx - 1, m_inventory, currentGold);
                    m_player->addGold(currentGold - m_player->getGold()); 
                    m_logger.log("Item sold to merchant.");
                }
            } 
            else if (actionIndex == 3) {
                m_inventory.showItems();

                if (!m_inventory.isEmpty()) {
                    std::cout << "Enter item index to use/equip (0 to cancel): ";
                    size_t itemIndex;
                    std::cin >> itemIndex;

                    if (itemIndex > 0 && itemIndex <= m_inventory.getSize()) {
                        Item* item = m_inventory.getItemPtr(itemIndex - 1);

                        if (Weapon* weapon = dynamic_cast<Weapon*>(item))
                        {
                            if (!CanEquipWeapon(*m_player, *weapon))
                            {
                                std::cout << "This character cannot equip this weapon.\n";
                                continue;
                            }
                        }

                        if (Potion* potion = dynamic_cast<Potion*>(item))
                        {
                            m_player->heal(potion->getHealAmount());
                        }

                        m_inventory.useItem(itemIndex - 1, m_equippedWeapon, m_equippedArmor);

                        if (m_equippedWeapon)
                        {
                            m_player->setWeaponDamageBonus(m_equippedWeapon->getDamage());
                        }

                        if (m_equippedArmor)
                        {
                            m_player->setArmorDefense(m_equippedArmor->getDefense());
                        }
                    }
                }
            }
            else {
                menuActive = false;
            }
        } 
        catch (const std::exception& ex) {
            throw ShopException(ex.what());
        }
    }
}

void Game::restAtHome() {
    m_logger.log("Character completed rest tick action.");
    std::cout << "\nYou rest. Health systems refreshed.\n";
    m_player->heal(25);
}

void Game::saveGame() {
    m_saveSystem.saveGame(m_player, m_inventory, m_equippedWeapon, m_equippedArmor);
    std::cout << "\nGame saved successfully!\n";
    m_logger.log("Game saved successfully.");
}
