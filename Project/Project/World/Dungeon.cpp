#include "Dungeon.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

Dungeon::Dungeon(string dName, vector<Enemy> bosses, int lvl, Logger& logger)
    : dungeonName(dName), bosses(bosses), level(lvl), logger(logger)
{
}

void Dungeon::showInfo()
{
    cout << "\nName: " << dungeonName << "\n";
    cout << "Bosses: ";

    for (size_t i = 0; i < bosses.size(); i++)
    {
        cout << bosses[i].getName();
        if (i != bosses.size() - 1)
            cout << ", ";
    }

    cout << "\nLevel: " << level << "\n";
}

void Dungeon::StartDungeonBattle(Character& player, Inventory& inventory)
{
    showInfo();

    cout << "Start the battle? (y/n): ";

    char startBattle;
    cin >> startBattle;

    vector<Character*> bossesPtrs;
    for (auto& boss : bosses)
        bossesPtrs.push_back(&boss);

    if (startBattle == 'y' || startBattle == 'Y')
    {
        cout << "Starting battle...\n";
        logger.log("Player started the battle in the " + dungeonName + " dungeon.");

        Battle battle(player, bossesPtrs, inventory, logger);
        battle.StartBattle();

        if (player.isAlive())
        {
            int reward = 0;

            for (Enemy& boss : bosses)
            {
                reward += boss.getGold();
            }

            player.addGold(reward);

            cout << "\nDungeon cleared!\n";
            cout << "You received " << reward << " gold.\n";
            logger.log("Player cleared dungeon and received " + to_string(reward) + " gold.");
        }
    }
    else
        cout << "Returning to dungeon menu...\n";
}


void Dungeon::showMenu(Character& player_, Inventory& inventory_)
{
    logger.log("Player opened the dungeon menu.");
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
            Enemy GoblinKing("Goblin King", 200, 20, 25, logger);
            Dungeon GoblinsCave("Goblin's Cave", { GoblinKing }, 1, logger);

            GoblinsCave.StartDungeonBattle(player_, inventory_);

            if (!player_.isAlive())
            {
                return;
            }

            break;
        }
        case 2: {
            Enemy GiantSkeleton("Giant Skeleton", 300, 35, 40, logger);
            Dungeon SkeletonsTemple("Skeleton's Temple", { GiantSkeleton }, 2, logger);

            SkeletonsTemple.StartDungeonBattle(player_, inventory_);

            if (!player_.isAlive())
            {
                return;
            }

            break;
        }
        case 3: {
            Enemy Yety("Yety", 500, 65, 75, logger);
            Dungeon FrozenMountain("Frozen Mountain", { Yety }, 3, logger);

            FrozenMountain.StartDungeonBattle(player_, inventory_);

            if (!player_.isAlive())
            {
                return;
            }

            break;
        }
        case 4: {
            Enemy MineDemon("Mine Demon", 150, 15, 30, logger);
            Enemy AshGolem("Ash Golem", 250, 30, 50, logger);
            Dungeon FireMines("Fire Mines", { MineDemon, AshGolem }, 4, logger);

            FireMines.StartDungeonBattle(player_, inventory_);

            if (!player_.isAlive())
            {
                return;
            }

            break;
        }
        case 5: {
            Enemy RotWolf("Rot Wolf", 300, 40, 35, logger);
            Enemy ForestGhost("Forest Ghost", 500, 10, 70, logger);
            Dungeon ForgottenForest("Forgotten Forest", { RotWolf, ForestGhost }, 5, logger);

            ForgottenForest.StartDungeonBattle(player_, inventory_);

            if (!player_.isAlive())
            {
                return;
            }

            break;
        }
        case 6: {
            Enemy ThunderWraith("Thunder Wraith", 250, 40, 35, logger);
            Enemy WindElemental("Wind Elemental", 350, 20, 80, logger);
            Dungeon StormRuins("Storm Ruins", { ThunderWraith, WindElemental }, 6, logger);

            StormRuins.StartDungeonBattle(player_, inventory_);

            if (!player_.isAlive())
            {
                return;
            }

            break;
        }
        case 7: {
            cout << "\nBack to main menu...\n";
            logger.log("Player returned to the main menu from the dungeon menu.");
            break;
        }

        default:
            cout << "\nInvalid choice!\n";
        }
    } while (choice != 7 && player_.isAlive());
}