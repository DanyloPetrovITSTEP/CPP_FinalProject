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

Enemy::Enemy(string eName, int hp, int dmg, int gold)
{
    enemyName = eName;
    health = hp;
    damage = dmg;
    rewardGold = gold;
}

string Enemy::getName()
{
	return enemyName;
}
int Enemy::getHealth()
{
	return health;
}
int Enemy::getDamage()
{
	return damage;
}
int Enemy::getRewardGold()
{
	return rewardGold;
}

