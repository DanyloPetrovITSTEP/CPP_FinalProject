#pragma once
#include <string>
#include "../Core/Logger.h"

using namespace std;

class Dungeon {
private:
    string dungeonName;
    string bossName;
    int level;
    Logger& logger_;

public:
    Dungeon(string dName, string bName, int lvl, Logger& logger);
    void showInfo();
    void showMenu();
};