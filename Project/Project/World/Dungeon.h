#pragma once
#include <string>
#include "../Core/Logger.h"
#include "Enemy.h"

class Dungeon {
private:
    string dungeonName;
    Enemy boss1_;
    Enemy boss2_;
    int level;
    Logger& logger_;

public:
    Dungeon(string dName, string bName, int lvl, Logger& logger);
    Dungeon(string dName, string b1Name,string b2Name, int lvl, Logger& logger);
    void showInfo();
    void showMenu();
};
