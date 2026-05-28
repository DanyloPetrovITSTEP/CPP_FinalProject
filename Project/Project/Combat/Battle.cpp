#include "Battle.h"
#include "../Items/Potion.h"
#include <iostream>

using namespace std;

Battle::Battle(Character& player, vector<Character*>& enemies, Inventory& inventory, Logger& logger)
    : player_(player), enemies_(enemies), inventory_(inventory), logger_(logger)
{
}
void Battle::EnemyTurn()
{
    if (IsBattleOver())
        return;

    cout << "\nEnemy turn!\n";

    for (Character* enemy : enemies_)
    {
        if (!enemy->isAlive())
            continue;

        enemy->processStatusEffects();

        if (!enemy->isAlive())
        {
            continue;
        }

        enemy->basicAttack(player_);
        cout << enemy->getName() << " attacked " << player_.getName() << "!\n";
        logger_.log(enemy->getName() + " attacked " + player_.getName() + "!");

        if (!player_.isAlive())
        {
            IsBattleOver();
            return;
        }
    }
}
void Battle::ShowEnemies()
{
    cout << "\n----- ENEMIES -----\n";
    for (int i = 0; i < enemies_.size(); i++)
    {
        if (enemies_[i]->isAlive())
            cout << i + 1 << ". " << enemies_[i]->getName() << " HP: " << enemies_[i]->getHealth() << endl;
        else
            cout << i + 1 << ". " << enemies_[i]->getName() << " (Defeated)" << endl;
    }
}
void Battle::ShowStats()
{
    cout << "\n----- STATS -----" << endl;
    cout << "Player HP: " << player_.getHealth() << endl;
    for (Character* enemy : enemies_)
    {
        if (enemy->isAlive())
            cout << enemy->getName() << " HP: " << enemy->getHealth() << endl;
        else
            cout << enemy->getName() << " (Defeated)" << endl;
    }
}
bool Battle::ProcessPlayerAction(function<bool(Character&)> action)
{
    Character* target = nullptr;

    while (!target)
    {
        target = ChooseTarget();

        if (!target)
        {
            cout << "Try again!\n";
        }
    }

    bool action_success = action(*target);

    if (!action_success)
    {
        return false;
    }

    player_.reduceCooldowns();
    player_.processStatusEffects();

    if (IsBattleOver())
    {
        return true;
    }

    EnemyTurn();

    IsBattleOver();
    return true;
}
bool Battle::IsBattleOver()
{
    bool enemiesAlive = false;
    for (Character* e : enemies_)
    {
        if (e->isAlive())
        {
            enemiesAlive = true;
            break;
        }
    }
    if (!player_.isAlive())
    {
        if (!battle_result_printed_)
        {
            cout << "\nYou lost!\n";
            logger_.log(player_.getName() + " lost the battle.");
            battle_result_printed_ = true;
        }

        return true;
    }

    if (!enemiesAlive)
    {
        if (!battle_result_printed_)
        {
            cout << "\nYou won the battle!\n";
            logger_.log(player_.getName() + " won the battle!");
            battle_result_printed_ = true;
        }

        return true;
    }
    return false;
}

Character* Battle::ChooseTarget()
{
    if (enemies_.size() > 1)
    {
        ShowEnemies();

        int choice;
        cout << "Choose target: ";
        cin >> choice;

        if (choice < 1 || choice > enemies_.size())
        {
            cout << "Invalid choice!\n";
            logger_.log(player_.getName() + " made an invalid target choice during battle.");
            return nullptr;
        }

        Character* target = enemies_[choice - 1];

        if (!target->isAlive())
        {
            cout << "This enemy is already defeated!\n";
            logger_.log(player_.getName() + " chose an already defeated enemy as a target during battle.");
            return nullptr;
        }

        return target;
    }
    else
    {
        Character* target = enemies_[0];
        if (!target->isAlive())
        {
            cout << "This enemy is already defeated!\n";
            logger_.log(player_.getName() + " chose an already defeated enemy as a target during battle.");
            return nullptr;
        }
        return target;
    }
}



void Battle::StartBattle()
{
    while (!IsBattleOver())
    {
        cout << "\n----- BATTLE -----" << endl;
        cout << "1. " << player_.getBasicAttackName() << endl;
        cout << "2. " << player_.getSecondActionName() << endl;
        cout << "3. " << player_.getFirstAbilityName() << endl;
        cout << "4. " << player_.getSecondAbilityName() << endl;
        cout << "5. Use item" << endl;
        cout << "6. Show stats" << endl;
        cout << "Choose: ";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            ProcessPlayerAction([&](Character& enemy)
            {
                logger_.log(player_.getName() + " used " + player_.getBasicAttackName() + " on " + enemy.getName() + "!");
                return player_.basicAttack(enemy);
            });
            break;
        }
        case 2:
        {
            if (player_.getClassName() == "Mage")
            {
                logger_.log(player_.getName() + " used " + player_.getSecondActionName() + "!");

                if (player_.secondAction(player_))
                {
                    player_.reduceCooldowns();
                    player_.processStatusEffects();

                    if (!IsBattleOver())
                    {
                        EnemyTurn();
                    }

                    IsBattleOver();
                }
            }
            else
            {
                ProcessPlayerAction([&](Character& enemy)
                    {
                        logger_.log(player_.getName() + " used " + player_.getSecondActionName() + " on " + enemy.getName() + "!");
                        return player_.secondAction(enemy);
                    });
            }

            break;
        }
        case 3:
        {
            ProcessPlayerAction([&](Character& enemy)
            {
                if (!player_.firstAbility(enemy, enemies_))
                {
                    cout << "Cannot use ability!" << endl;
                    return false;
                }

                logger_.log(player_.getName() + " used " + player_.getFirstAbilityName() + " on " + enemy.getName() + "!");
                return true;
            });
            break;
        }
        case 4:
        {
            ProcessPlayerAction([&](Character& enemy)
            {
                if (!player_.secondAbility(enemy, enemies_))
                {
                    cout << "Cannot use ability!" << endl;
                    return false;
                }

                logger_.log(player_.getName() + " used " + player_.getSecondAbilityName() + " on " + enemy.getName() + "!");
                return true;
            });
            break;
        }
        case 5:
        {
            cout << "\n----- INVENTORY -----" << endl;

            if (inventory_.isEmpty())
            {
                cout << "Your inventory is empty!" << endl;
                break;
            }

            inventory_.showItems();

            int inv_choice;
            cout << "Choose item to use (0 to cancel): ";
            cin >> inv_choice;

            if (inv_choice > 0 && inv_choice <= inventory_.getSize())
            {
                Item* used_item = inventory_.getItemPtr(inv_choice - 1);
                string item_name = used_item ? used_item->getName() : "unknown item";

                if (used_item && used_item->getType() != ItemType::Potion)
                {
                    cout << "You can equip weapons and armor only outside battle.\n";
                    break;
                }

                if (Potion* potion = dynamic_cast<Potion*>(used_item))
                {
                    player_.heal(potion->getHealAmount());
                }

                inventory_.useItem(inv_choice - 1);

                cout << "Current HP: " << player_.getHealth() << "/" << player_.getMaxHealth() << "\n";

                logger_.log(player_.getName() + " used " + item_name + " during battle.");

                break;
            }
            else if (inv_choice != 0)
            {
                cout << "Invalid item choice!" << endl;
                logger_.log(player_.getName() + " made an invalid item choice during battle.");
                break;
            }
            else
            {
                cout << "Cancelled item use." << endl;
                logger_.log(player_.getName() + " cancelled item use during battle.");
                break;
            }
        }
        case 6:
        {
            ShowStats();
            if (IsBattleOver())
                break;
            continue;
        }
        default:
            cout << "Invalid choice" << endl;
            break;
        }
    }
}