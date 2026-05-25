#include "Game.h"
#include "Exceptions.h"
#include <iostream>

Game::Game() : m_isRunning(true), m_player(nullptr), m_saveSystem("save.dat") {}

void Game::run() {
    m_logger.log("Game engine started.");
    while (m_isRunning) {
        if (!m_player) {
            showMainMenu();
        } else {
            showGameMenu();
        }
    }
}

void Game::showMainMenu() {
    std::cout << "\n1. New Game\n2. Continue\n3. View Logs\n4. Exit\nChoice: ";
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
        default: std::cout << "Invalid choice.\n";
    }
}

void Game::showGameMenu() {
    std::cout << "\n1. Dungeon\n2. Shop\n3. Rest\n4. Save\n5. Exit\nChoice: ";
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
            default: std::cout << "Invalid action.\n";
        }
    } 
    catch (const InventoryException& ex) {
        std::cout << "\n[Inventory Management Alert]: " << ex.what() << "\n";
        m_logger.log(std::string("Inventory rejection: ") + ex.what());
    } 
    catch (const ShopException& ex) {
        std::cout << "\n[Merchant Transaction Refused]: " << ex.what() << "\n";
        m_logger.log(std::string("Shop rejection: ") + ex.what());
    } 
    catch (const GameException& ex) {
        std::cerr << "\n[Subsystem Exception]: " << ex.what() << "\n";
        m_logger.log(std::string("Game state warning: ") + ex.what());
    }
}

void Game::startNewGame() {
    selectCharacterClass();
}

void Game::continueGame() {
    try {
        m_player = m_saveSystem.loadGame();
    } catch (const SaveLoadException& ex) {
        std::cout << "\n[Load Error]: Failed to recover save file. " << ex.what() << "\n";
    }
}

void Game::selectCharacterClass() {
    m_logger.log("Character class selected.");
}

void Game::goToDungeon() {
    m_logger.log("Entering Dungeon Subsystem.");
}

void Game::goToShop() {
    m_logger.log("Entering Shop Subsystem.");
}

void Game::restAtHome() {
    m_logger.log("Player rested.");
}

void Game::saveGame() {
    m_saveSystem.saveGame(m_player);
}
