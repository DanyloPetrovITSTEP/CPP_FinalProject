#include "Battle.h"
#include <iostream>

using namespace std;

Battle::Battle(Character& player, vector<Character*>& enemies, Inventory& inventory, Logger& logger) : player_(player), enemies_(enemies), inventory_(inventory), logger_(logger)
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

        enemy->basicAttack(player_);
        cout << enemy->getName() << " used " << enemy->getBasicAttackName() << "!\n";
		logger_.log(enemy->getName() + " used " + enemy->getBasicAttackName() + " on " + player_.getName() + "!");
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
void Battle::ProcessPlayerAction(function<void(Character&)> action)
{
    Character* target = nullptr;
    while (!target)
    {
        target = ChooseTarget();
        if (!target)
            cout << "Try again!\n";
    }
    action(*target);

    if (IsBattleOver()) 
        return;

    EnemyTurn();

    if (IsBattleOver()) 
        return;
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
        cout << "You lost!\n";
        logger_.log(player_.getName() + " lost the battle.");
        return true;
    }

    if (!enemiesAlive)
    {
        cout << "You won the battle!\n";
		logger_.log(player_.getName() + " won the battle!");
        return true;
    }
    return false;
}

Character* Battle::ChooseTarget()
{
    if(enemies_.size()>1)
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
    bool battleRunning = true;

    while (!IsBattleOver())
    {
        if (IsBattleOver()){
            break;
        }

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
                    player_.basicAttack(enemy);
                    logger_.log(player_.getName() + " used " + player_.getBasicAttackName() + " on " + enemy.getName() + "!");
                }
            );
            break;
        }
        case 2:
        {
            ProcessPlayerAction([&](Character& enemy)
                {
                    player_.secondAction(enemy);
                    logger_.log(player_.getName() + " used " + player_.getSecondActionName() + " on " + enemy.getName() + "!");
                }
            );
            break;
        }
        case 3:
        {
            ProcessPlayerAction([&](Character& enemy)
                {
                    if (player_.firstAbility(enemy, enemies_))
                        logger_.log(player_.getName() + " used " + player_.getFirstAbilityName() + " on " + enemy.getName() + "!");
                    else
                        cout << "Cannot use ability!" << endl;
                }
            );
            break;
        }
        case 4:
        {
            ProcessPlayerAction([&](Character& enemy)
                {
                    if (player_.secondAbility(enemy, enemies_))
                        logger_.log(player_.getName() + " used " + player_.getSecondAbilityName() + " on " + enemy.getName() + "!");
                    else
                        cout << "Cannot use ability!" << endl;
                }
            );
            break;
        }
        case 5:
        {
            cout << "\n----- INVENTORY -----" << endl;
            if (inventory_.isEmpty()) {
                cout << "Your inventory is empty!" << endl;
                break;
            }
            inventory_.showItems();
            int inv_choice;
            cout << "Choose item to use (0 to cancel): ";
            cin >> inv_choice;
            if (inv_choice > 0 && inv_choice <= inventory_.getSize()) {
                inventory_.useItem(inv_choice - 1);
                logger_.log(player_.getName() + " used " + inventory_.getItemPtr(inv_choice - 1)->getName() + " during battle.");
            }

            else if (inv_choice != 0) {
                cout << "Invalid item choice!" << endl;
                logger_.log(player_.getName() + " made an invalid item choice during battle.");
            }

            else if (inv_choice == 0) {
                cout << "Cancelled item use." << endl;
                logger_.log(player_.getName() + " cancelled item use during battle.");
                break;
            }

            EnemyTurn();

            if (IsBattleOver())
                battleRunning = false;

            break;
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