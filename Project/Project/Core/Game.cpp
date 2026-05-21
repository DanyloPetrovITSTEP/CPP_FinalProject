#include "Game.h"
#include "Exceptions.h"
#include <iostream>

Game::Game() : m_isRunning(true), m_player(nullptr), m_saveSystem("save.dat") {}

void Game::run() {
    m_logger.log("Game engine initialized.");
    while (m_isRunning) {
        if (!m_player) {
            showMainMenu();
        } else {
            showGameMenu();
        }
    }
}

void Game::showMainMenu() {
    std::cout << "\n=== RPG GAME MAIN MENU ===\n"
              << "1. Start New Game\n"
              << "2. Continue Game (Load)\n"
              << "3. View Log History\n"
              << "4. Exit\n"
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
        case 4: m_isRunning = false; m_logger.log("Game exited by user."); break;
        default: std::cout << "Invalid choice! Try again.\n";
    }
}

void Game::showGameMenu() {
    std::cout << "\n=== ADVENTURE MENU ===\n"
              << "1. Enter Dungeon (Battle)\n"
              << "2. Visit Town Shop\n"
              << "3. Rest at Home (Heal)\n"
              << "4. Save Game\n"
              << "5. View Log History\n"
              << "6. Return to Main Menu\n"
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
            case 5: m_logger.print(); break;
            case 6: m_player.reset(); m_logger.log("Returned to main menu."); break;
            default: std::cout << "Invalid choice! Try again.\n";
        }
    } 
    catch (const GameException& ex) {
        std::cerr << "\n[!] Game error caught: " << ex.what() << "\n";
        m_logger.log(std::string("Error occurred: ") + ex.what());
    }
}

void Game::startNewGame() {
    m_logger.log("Starting a new game creation.");
    selectCharacterClass();
}

void Game::continueGame() {
    try {
        m_player = m_saveSystem.loadGame();
        m_logger.log("Game loaded successfully.");
    } 
    catch (const SaveLoadException& ex) {
        std::cerr << "\n[!] Load failed: " << ex.what() << "\n";
        m_logger.log("Failed to load game file.");
    }
}

void Game::selectCharacterClass() {
    std::cout << "\n--- SELECT YOUR CLASS ---\n"
              << "1. Warrior\n"
              << "2. Archer\n"
              << "3. Mage\n"
              << "4. Rogue\n"
              << "Choose class: ";
              
    int classChoice;
    std::cin >> classChoice;
    m_player = std::make_unique<Character>(); 
    
    m_logger.log("New character successfully created.");
}

void Game::goToDungeon() {
    m_logger.log("Hero entered the dungeon.");
    std::cout << "\n[Dungeon] You enter dark corridors... (Evgeniy's logic trigger)\n";
}

void Game::goToShop() {
    m_logger.log("Hero entered the shop.");
    std::cout << "\n[Shop] Welcome to the merchant counter! (Yaroslav's logic trigger)\n";
}

void Game::restAtHome() {
    m_logger.log("Hero rested at home.");
    std::cout << "\n[Home] You take a rest and restore your strength.\n";
}

void Game::saveGame() {
    m_saveSystem.saveGame(m_player);
    m_logger.log("Game progress saved.");
}
