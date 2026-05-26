#include "Dungeon.h"
#include <iostream>
#include <string>

using namespace std;

Dungeon::Dungeon(string dName, string bName, int lvl, Logger& logger)
    : logger_(logger)
{
    dungeonName = dName;
    boss1_ = bName;
    level = lvl;
}
Dungeon::Dungeon(string dName, string b1Name, string b2Name, int lvl, Logger& logger)
    : logger_(logger)
{
    dungeonName = dName;
    boss1_ = b1Name;
    boss2_ = b2Name;
    level = lvl;
}

void Dungeon::showInfo()
{
    cout << "Name: " << dungeonName << "\n"
        << "Bosses: " << boss1Name << ", " << boss2Name << "\n"
        << "Level: " << level << "\n";
}

void Dungeon::showMenu()
{
    logger_.log("Player opened the dungeon menu.");
    int choice;
    do {
        cout << "\n--- DUNGEON MENU ---\n"
            << "1. Goblin's Cave\n"
            << "2. Skeleton's Temple\n"
            << "3. Frozen Mountain\n"
            << "4. Fire Mines\n"
            << "5. Forgotten Forest\n"
            << "6. Storm Ruins\n"
            << "7. Back\n"
            << "Choice: ";
        cin >> choice;

        switch (choice) {

        case 1: {
            Dungeon GoblinsCave("Goblin's Cave", "Goblin King", 1, logger_);
            Enemy GoblinKing("Goblin King", 200, 20, 25, logger_);
            GoblinsCave.showInfo();

            cout << "Start the battle? (y/n)";
            char startBattle;
            cin >> startBattle;

            if (startBattle == 'y' || startBattle == 'Y') {
                cout << "Starting battle" << "...\n";
                logger_.log("Player started the battle with " + GoblinKing.getName() + " in the " + GoblinsCave.dungeonName + " dungeon.");
            }
            else if (startBattle == 'n' || startBattle == 'N') {
                cout << "Returning to dungeon menu...\n";
            }
            break;
        }
        case 2: {
            Dungeon SkeletonsTemple("Skeleton's Temple", "Giant Skeleton", 2, logger_);
            Enemy GiantSkeleton("Giant Skeleton", 300, 35, 40, logger_);
            SkeletonsTemple.showInfo();

            cout << "Start the battle? (y/n)";
            char startBattle;
            cin >> startBattle;

            if (startBattle == 'y' || startBattle == 'Y') {
                cout << "Starting battle" << "...\n";
                logger_.log("Player started the battle with " + GiantSkeleton.getName() + " in the " + SkeletonsTemple.dungeonName + " dungeon.");
            }
            else if (startBattle == 'n' || startBattle == 'N') {
                cout << "Returning to dungeon menu...\n";
            }
            break;
        }
        case 3: {
            Dungeon FrozenMountain("Frozen Mountain", "Yety", 3, logger_);
            Enemy Yety("Yety", 500, 65, 75, logger_);
            FrozenMountain.showInfo();

            cout << "Start the battle? (y/n)";
            char startBattle;
            cin >> startBattle;

            if (startBattle == 'y' || startBattle == 'Y') {
                cout << "Starting battle" << "...\n";
                logger_.log("Player started the battle with " + Yety.getName() + " in the " + FrozenMountain.dungeonName + " dungeon.");
            }
            else if (startBattle == 'n' || startBattle == 'N') {
                cout << "Returning to dungeon menu...\n";
            }
            break;
        }
        case 4: {
            Dungeon FireMines("Fire Mines", "Mine Demon", "Ash Golem", 4, logger_);
            Enemy MineDemon("Mine Demon", 150, 15, 30, logger_);
            Enemy AshGolem("Ash Golem", 250, 30, 50, logger_);
            FireMines.showInfo();

            cout << "Start the battle? (y/n)";
            char startBattle;
            cin >> startBattle;

            if (startBattle == 'y' || startBattle == 'Y') {
                cout << "Starting battle" << "...\n";
                logger_.log("Player started the battle with " + MineDemon.getName() + " and " + AshGolem.getName() + " in the " + FireMines.dungeonName + " dungeon.");
            }
            else if (startBattle == 'n' || startBattle == 'N') {
                cout << "Returning to dungeon menu...\n";
            }
            break;
        }
        case 5: {
            Dungeon ForgottenForest("Forgotten Forest", "Rot Wolf", "Forest Ghost", 5, logger_);
            Enemy RotWolf("Rot Wolf", 300, 40, 35, logger_);
            Enemy ForestGhost("Forest Ghost", 500, 10, 70, logger_);
            ForgottenForest.showInfo();

            cout << "Start the battle? (y/n)";
            char startBattle;
            cin >> startBattle;

            if (startBattle == 'y' || startBattle == 'Y') {
                cout << "Starting battle" << "...\n";
                logger_.log("Player started the battle with " + RotWolf.getName() + " and " + ForestGhost.getName() + " in the " + ForgottenForest.dungeonName + " dungeon.");
            }
            else if (startBattle == 'n' || startBattle == 'N') {
                cout << "Returning to dungeon menu...\n";
            }

            break;
        }
        case 6: {
            Dungeon StormRuins("Storm Ruins", "Thunder Wraith", "Wind Elemental", 6, logger_);
            Enemy ThunderWraith("Thunder Wraith", 250, 40, 35, logger_);
            Enemy WindElemental("Wind Elemental", 350, 20, 80, logger_);
            StormRuins.showInfo();

            cout << "Start the battle? (y/n)";
            char startBattle;
            cin >> startBattle;

            if (startBattle == 'y' || startBattle == 'Y') {
                cout << "Starting battle" << "...\n";
                logger_.log("Player started the battle with " + ThunderWraith.getName() + " and " + WindElemental.getName() + " in the " + StormRuins.dungeonName + " dungeon.");
            }
            else if (startBattle == 'n' || startBattle == 'N') {
                cout << "Returning to dungeon menu...\n";
            }
            break;
        }
        case 7: {
            cout << "\nBack to main menu...\n";
            logger_.log("Player returned to the main menu from the dungeon menu.");
            break;
        }

        default:
            cout << "\nInvalid choice!\n";
        }
    } while (choice != 7);
}