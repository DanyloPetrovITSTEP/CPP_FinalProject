#ifndef GAME_H
#define GAME_H

#include <memory>
#include "Logger.h"
#include "SaveSystem.h"

class Character; 
class Shop;
class Dungeon;

class Game {
private:
    bool m_isRunning;
    std::unique_ptr<Character> m_player;
    Logger m_logger;
    SaveSystem m_saveSystem;

    void showMainMenu();
    void showGameMenu();
    
    void startNewGame();
    void continueGame();
    void selectCharacterClass();
    
    void goToDungeon();
    void goToShop();
    void restAtHome();
    void saveGame();

public:
    Game();
    ~Game() = default;

    void run();
};

#endif 
