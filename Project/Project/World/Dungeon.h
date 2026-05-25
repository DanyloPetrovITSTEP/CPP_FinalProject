// Dungeon.h
// Dungeon system.
// Responsible for dungeon level selection.
//
// Menu example:
// 1. Easy dungeon
// 2. Medium dungeon
// 3. Hard dungeon
// 4. Back
//
// Future logic:
// - create enemies for selected level
// - start Battle
// - give rewards after victory
#pragma once
#include <string>

using namespace std;

class Dungeon {
private:
    string dungeonName;
    string bossName;
    int level;

public:
    Dungeon(string dName, string bName, int lvl);
    void showInfo();
    void showMenu();
};