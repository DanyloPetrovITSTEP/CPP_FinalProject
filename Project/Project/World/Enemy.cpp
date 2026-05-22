// Enemy.cpp
// Implementation file for Enemy.
// Future logic:
// - enemy takes damage
// - enemy attacks player
// - enemy gives reward after defeat


#include "Enemy.h"
#include <iostream>'
#include <string>

using namespace std;

Enemy::Enemy(const string& name, int maxHealth, int damage, int gold)
{
    ename_ = name;
	maxHealth_ = maxHealth;
	health_ = maxHealth;
    damage_ = damage;
    gold_ = gold;

    if (maxHealth_ < 1)
    {
        maxHealth_ = 1;
        health_ = 1;
	}
    if (damage_ < 0)
    {
        damage_ = 0;
    }
    if (gold_ < 0)
    {
        gold_ = 0;
	}
}

string Enemy::getName()
{
	return ename_;
}
int Enemy::getHealth()
{
	return health_;
}
int Enemy::getMaxHealth()
{
    return maxHealth_;
}
int Enemy::getDamage()
{
	return damage_;
}
int Enemy::getGold()
{
	return gold_;
}
void Enemy::updateIsDead()
{
    this->is_dead_ = getHealth() <= 0;

    if (is_dead_)
    {
        cout << this->ename_ << " has died!" << endl;
    }
}

