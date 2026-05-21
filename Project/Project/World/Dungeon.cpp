// Dungeon.cpp
// Implementation file for Dungeon.
// Future logic:
// - print dungeon menu
// - handle player choice
// - create enemy list
// - call battle system

#include "Dungeon.h"
#include <iostream>'
#include <string>

using namespace std;

Dungeon::Dungeon(string dName, string bName, int lvl) 
{
    dungeonName = dName;
    bossName = bName;
    level = lvl;
}

void Dungeon::showInfo() 
{
    cout << "Name: " << dungeonName << "\n"
         << "Boss: " << bossName << "\n"
         << "Level: " << level << "\n";
}

void Dungeon::showMenu()
{
    int choice;
    do {
        cout << "\n--- DUNGEON MENU ---\n"
            << "1. Easy dungeon\n"
            << "2. Medium dungeon\n"
            << "3. Hard dungeon\n"
            << "4. Back\n"
            << "Choice: ";
        cin >> choice;

        switch (choice) {

        case 1: {
            Dungeon easyDungeon("Goblin Cave", "Goblin King", 1);
            easyDungeon.showInfo();
            break;
        }
        case 2: {
            Dungeon mediumDungeon("Skeleton Temple", "Giant Skeleton", 1);
            mediumDungeon.showInfo();
            break;
        }
        case 3: {
            Dungeon hardDungeon("Frozen Mountain", "Yety", 1);
            hardDungeon.showInfo();
            break;
        }
        case 4:
            cout << "\nBack to main menu...\n";
            break;

        default:
            cout << "\nInvalid choice!\n";
        }
    } while (choice != 4);
}
