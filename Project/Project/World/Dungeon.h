#pragma once
#include <string>
#include "../Core/Logger.h"
#include "Enemy.h"
#include "../Characters/Character.h"
#include "../Items/Inventory.h"
#include "../Combat/Battle.h"


class Dungeon {
private:
    string dungeonName;
    vector<Enemy> bosses;
    int level;
    Logger& logger;

public:
    Dungeon(string dName, vector<Enemy> bosses, int lvl, Logger& logger);
    void showInfo();
    void showMenu(Character& player, Inventory& inventory);
    void StartDungeonBattle(Character& player, Inventory& inventory);
};