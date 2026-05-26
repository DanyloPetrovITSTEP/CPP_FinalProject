#include "Game.h"
#include "Exceptions.h"

#include "../Characters/Character.h"
#include "../Characters/Warrior.h"
#include "../Characters/Archer.h"
#include "../Characters/Mage.h"
#include "../Characters/Rogue.h"

#include <iostream>
#include <ctime> 

Game::Game() : m_isRunning(true), m_player(nullptr), m_saveSystem("save.dat") {}

void Game::run() {
    srand(static_cast<unsigned int>(time(nullptr)));
    
    m_logger.log("Game engine core successfully initialized.");
    
    while (m_isRunning) {
        if (!m_player) {
            showMainMenu();
        } else if (!m_player->isAlive()) {
            std::cout << "\n[Game Over] " << m_player->getName() << " has fallen in battle...\n";
            m_logger.log("Character " + m_player->getName() + " died.");
            m_player.reset();
        } else {
            showGameMenu();
        }
    }
}

void Game::showMainMenu() {
    std::cout << "\n=== RPG GAME MAIN MENU ===\n"
              << "1. Start New Game\n"
              << "2. Continue Game\n"
              << "3. View Log History\n"
              << "4. Exit Game\n"
              << "Choose option: ";
              
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
        case 4: m_isRunning = false; m_logger.log("Application exited by user."); break;
        default: std::cout << "Invalid choice! Try again.\n";
    }
}

void Game::showGameMenu() {
    std::cout << "\n=== " << m_player->getClassName() << ": " << m_player->getName() << " ===\n"
              << "HP: " << m_player->getHealth() << "/" << m_player->getMaxHealth() << " | Gold: " << m_player->getGold() << "g\n"
              << "------------------------\n"
              << "1. Go into the Dungeon\n"
              << "2. Go to the Town Shop\n"
              << "3. Go Rest in Home (Heal)\n"
              << "4. Save Game Progress\n"
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
            case 1: goToDungeon(); break;
            case 2: goToShop(); break;
            case 3: restAtHome(); break;
            case 4: saveGame(); break;
            case 5: m_player.reset(); m_logger.log("Returned to main menu."); break;
            default: std::cout << "Invalid choice! Try again.\n";
        }
    } 
    catch (const InventoryException& ex) {
        std::cout << "\n[INVENTORY WARNING]: " << ex.what() << "\n";
        m_logger.log(std::string("Inventory action blocked: ") + ex.what());
    } 
    catch (const ShopException& ex) {
        std::cout << "\n[MERCHANT REJECTION]: " << ex.what() << "\n";
        m_logger.log(std::string("Shop transaction declined: ") + ex.what());
    } 
    catch (const GameException& ex) {
        std::cerr << "\n[GAME RUNTIME ERROR]: " << ex.what() << "\n";
        m_logger.log(std::string("Runtime subsystem warning: ") + ex.what());
    }
}

void Game::startNewGame() {
    m_logger.log("Initiated character creation process.");
    selectCharacterClass();
}

void Game::continueGame() {
    try {
        m_player = m_saveSystem.loadGame();
        if (m_player) {
            m_logger.log("Save file loaded successfully for: " + m_player->getName());
        }
    } 
    catch (const SaveLoadException& ex) {
        std::cout << "\n[LOAD ERROR]: " << ex.what() << "\n";
        m_logger.log("Failed to load save state from storage.");
    }
}

void Game::selectCharacterClass() {
    std::cout << "\nEnter your character's name: ";
    std::string name;
    std::cin >> name;

    std::cout << "\n--- CHOOSE YOUR ARCHETYPE ---\n"
              << "1. Warrior (100 HP, 10 DMG)\n"
              << "2. Archer  (80 HP, 12 DMG)\n"
              << "3. Mage    (70 HP, 18 DMG)\n"
              << "4. Rogue   (75 HP, 14 DMG)\n"
              << "Choose class: ";
              
    int classChoice;
    if (!(std::cin >> classChoice)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        classChoice = 1; 
    }
    
    switch (classChoice) {
        case 1: m_player = std::make_unique<Warrior>(name); break;
        case 2: m_player = std::make_unique<Archer>(name); break;
        case 3: m_player = std::make_unique<Mage>(name); break;
        case 4: m_player = std::make_unique<Rogue>(name); break;
        default: 
            std::cout << "Invalid class choice. Warrior selected by default.\n";
            m_player = std::make_unique<Warrior>(name);
            break;
    }
    
    m_logger.log("Created a new " + m_player->getClassName() + " named " + m_player->getName());
}

void Game::goToDungeon() {
    m_logger.log("Hero requested dungeon entry.");
    std::cout << "\n[Dungeon] Entering dark zones... (Evgeniy's Battle Subsystem trigger)\n";
}

void Game::goToShop() {
    m_logger.log("Hero visited town merchant shop.");
    std::cout << "\n[Shop] Inspecting merchant items... (Yaroslav's Shop Subsystem trigger)\n";
}

void Game::restAtHome() {
    m_logger.log("Hero rested at home sanctuary.");
    std::cout << "\n[Home] You sleep comfortably in your bed.\n";
    
    m_player->heal(25);
}

void Game::saveGame() {
    m_saveSystem.saveGame(m_player);
    m_logger.log("Game successfully saved.");
}
