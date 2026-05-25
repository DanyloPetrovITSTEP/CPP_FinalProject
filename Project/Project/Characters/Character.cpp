// Character.cpp
// Implementation file for common Character methods.
// Here we will keep logic that is shared by all character classes.
//
// Examples:
// - health cannot go below 0
// - health cannot go above max health
// - gold cannot become negative
// - dead character cannot perform actions

#include "Character.h"

Character::Character(const string& name, int maxHealth, int damage, int gold)
    : name_(name), health_(maxHealth), max_health_(maxHealth), damage_(damage), gold_(gold)
{
    if (max_health_ < 1)
    {
        max_health_ = 1;
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

const string& Character::getName() const
{
    return name_;
}

int Character::getHealth() const
{
    return health_;
}

int Character::getMaxHealth() const
{
    return max_health_;
}

int Character::getDamage() const
{
    return damage_;
}

int Character::getGold() const
{
    return gold_;
}

bool Character::isAlive() const
{
    return health_ > 0;
}

void Character::takeDamage(int value)
{
    if (value < 0)
    {
        return;
    }

    health_ -= value;

    if (health_ < 0)
    {
        health_ = 0;
    }
}

void Character::heal(int value)
{
    if (value < 0)
    {
        return;
    }

    health_ += value;

    if (health_ > max_health_)
    {
        health_ = max_health_;
    }
}

void Character::addGold(int value)
{
    if (value < 0)
    {
        return;
    }

    gold_ += value;
}

bool Character::spendGold(int value)
{
    if (value < 0 || value > gold_)
    {
        return false;
    }

    gold_ -= value;
    return true;
}

void Character::setDamage(int damage)
{
    if (damage < 0)
    {
        damage_ = 0;
        return;
    }

    damage_ = damage;
}