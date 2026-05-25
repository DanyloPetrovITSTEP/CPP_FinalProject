#include "Battle.h"
#include <iostream>

using namespace std;

Battle::Battle(Character& player, Enemy& enemy, Inventory& inventory, Logger& logger): player_(player), enemy_(enemy), inventory_(inventory), logger_(logger)
{
}
void Battle::PlayerAttack()
{
    int damage = player_.getDamage();
    enemy_.takeDamage(damage);
    cout << "Player attacks enemy for " << damage << " damage!"<< endl;
	logger_.log(player_.getName() + " attacked " + enemy_.getName() + " for " + to_string(damage) + " damage.");
}
void Battle::EnemyAttack()
{
    int damage = enemy_.getDamage();
    player_.takeDamage(damage);
    cout << "Enemy attacks player for " << damage << " damage!" << endl;
	logger_.log(enemy_.getName() + " attacked " + player_.getName() + " for " + to_string(damage) + " damage.");
}
void Battle::ShowStats()
{
    cout << "\n----- STATS -----" << endl;
    cout << "Player HP: " << player_.getHealth() << endl;
    cout << "Enemy HP: " << enemy_.getHealth() << endl;
}
void Battle::RunAway()
{
	cout << "You ran away from the battle!" << endl;
	logger_.log(player_.getName() + " ran away from " + enemy_.getName() + "!"); 
}



void Battle::StartBattle()
{
    bool battleRunning = true;
    while (battleRunning)
    {
        cout << "\n----- BATTLE -----" << endl;
        cout << "1. Attack" << endl;
        cout << "2. Use item" << endl;
        cout << "3. Show stats" << endl;
        cout << "4. Run away" << endl;
        cout << "Choose: ";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            PlayerAttack();
            if (enemy_.getHealth() <= 0)
            {
                cout << "Enemy defeated!" << endl;
                battleRunning = false;
                break;
            }
            EnemyAttack();
            if (player_.getHealth() <= 0)
            {
                cout << "Player died!" << endl;
                battleRunning = false;
            }
            break;
        case 2:
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
            break;
        case 3:
            ShowStats();
            break;
        case 4:
            RunAway();
            battleRunning = false;
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
        }
    }
}
