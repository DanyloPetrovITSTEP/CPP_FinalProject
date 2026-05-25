#include "Dungeon.h"
#include <iostream>
#include <string>

using namespace std;

Dungeon::Dungeon(string dName, string bName, int lvl, Logger& logger) 
    : logger_(logger)
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
            Dungeon easyDungeon("Goblin Cave", "Goblin King", 1, logger_);
            easyDungeon.showInfo();
			logger_.log("Player entered the " + easyDungeon.dungeonName + " dungeon.");
            break;
        }
        case 2: {
            Dungeon mediumDungeon("Skeleton Temple", "Giant Skeleton", 1, logger_);
            mediumDungeon.showInfo();
			logger_.log("Player entered the " + mediumDungeon.dungeonName + " dungeon.");
            break;
        }
        case 3: {
            Dungeon hardDungeon("Frozen Mountain", "Yety", 1, logger_);
            hardDungeon.showInfo();
			logger_.log("Player entered the " + hardDungeon.dungeonName + " dungeon.");
            break;
        }
        case 4:
            cout << "\nBack to main menu...\n";
			logger_.log("Player returned to the main menu from the dungeon menu.");
            break;

        default:
            cout << "\nInvalid choice!\n";
        }
    } while (choice != 4);
}
