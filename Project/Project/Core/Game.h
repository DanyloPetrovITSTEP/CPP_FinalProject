#ifndef GAME_H
#define GAME_H

#include <memory>
#include "Logger.h"
#include "../Save/SaveSystem.h"
#include "../Items/Inventory.h"
#include "../Items/Weapon.h"
#include "../Items/Armor.h"

class Character; 

class Game {
private:
    bool m_isRunning;
    std::unique_ptr<Character> m_player;
    Inventory m_inventory;
    Logger m_logger;
    SaveSystem m_saveSystem;

    std::shared_ptr<Weapon> m_equippedWeapon;
    std::shared_ptr<Armor> m_equippedArmor;

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
