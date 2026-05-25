// Battle.cpp
// Implementation file for Battle.
// Future logic:
// - run battle loop
// - player turn
// - enemy turn
// - check victory/defeat
// - write battle events to Logger

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
    cout << "Player attacks enemy for " << damage << " damage!" << endl;
}
void Battle::EnemyAttack()
{
    int damage = enemy_.getDamage();
    player_.takeDamage(damage);
    cout << "Enemy attacks player for " << damage << " damage!" << endl;
}
void Battle::UseItem()
{
    
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
            UseItem();
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
