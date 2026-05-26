#include "Enemy.h"
#include <iostream>'
#include <string>

using namespace std;

Enemy::Enemy(const string& name, int maxHealth, int damage, int gold, Logger& logger)
    :logger_(logger)
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
    updateIsDead();
}

string Enemy::getName() const
{
    return ename_;
}
int Enemy::getHealth()  const
{
    return health_;
}
int Enemy::getMaxHealth()   const
{
    return maxHealth_;
}
int Enemy::getDamage()  const
{
    return damage_;
}
int Enemy::getGold()    const
{
    return gold_;
}
void Enemy::updateIsDead()
{
    this->is_dead_ = getHealth() <= 0;

    if (is_dead_)
    {
        cout << this->ename_ << " has died!" << endl;
        logger_.log(this->ename_ + " has died!");
    }
}
void Enemy::takeDamage(int value)
{
    if (value < 0)
        return;

    health_ -= value;

    if (health_ < 0)
        health_ = 0;
    updateIsDead();
}