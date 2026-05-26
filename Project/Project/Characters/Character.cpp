#include "Character.h"

Character::Character(const string& name, int max_health, int damage, int gold)
    : name_(name), health_(max_health), max_health_(max_health), damage_(damage), gold_(gold), first_ability_cooldown_(0), second_ability_cooldown_(0), burn_damage_(0), burn_rounds_(0), damage_multiplier_(1.0), damage_multiplier_rounds_(0)
{
    // Keep starting stats valid
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

bool Character::isFullHealth() const
{
    return health_ == max_health_;
}

int Character::getFirstAbilityCooldown() const
{
    return first_ability_cooldown_;
}

int Character::getSecondAbilityCooldown() const
{
    return second_ability_cooldown_;
}

bool Character::canUseFirstAbility() const
{
    return first_ability_cooldown_ == 0;
}

bool Character::canUseSecondAbility() const
{
    return second_ability_cooldown_ == 0;
}

void Character::takeDamage(int value)
{
    if (value < 0)
    {
        return;
    }

    // Some effects can increase damage
    if (damage_multiplier_rounds_ > 0)
    {
        value = static_cast<int>(value * damage_multiplier_);
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

void Character::applyBurn(int damage, int rounds)
{
    if (damage <= 0 || rounds <= 0)
    {
        return;
    }

    burn_damage_ = damage;
    burn_rounds_ = rounds;
}

void Character::applyDamageMultiplier(double multiplier, int rounds)
{
    if (multiplier <= 1.0 || rounds <= 0)
    {
        return;
    }

    damage_multiplier_ = multiplier;
    damage_multiplier_rounds_ = rounds;
}

void Character::processStatusEffects()
{
    // Burning damage is applied once per character turn
    if (burn_rounds_ > 0)
    {
        takeDamage(burn_damage_);
        burn_rounds_--;
    }

    if (damage_multiplier_rounds_ > 0)
    {
        damage_multiplier_rounds_--;

        if (damage_multiplier_rounds_ == 0)
        {
            damage_multiplier_ = 1.0;
        }
    }
}

void Character::reduceCooldowns()
{
    // Cooldowns are reduced after player's action
    if (first_ability_cooldown_ > 0)
    {
        first_ability_cooldown_--;
    }

    if (second_ability_cooldown_ > 0)
    {
        second_ability_cooldown_--;
    }
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

void Character::setFirstAbilityCooldown(int cooldown)
{
    if (cooldown < 0)
    {
        cooldown = 0;
    }

    first_ability_cooldown_ = cooldown;
}

void Character::setSecondAbilityCooldown(int cooldown)
{
    if (cooldown < 0)
    {
        cooldown = 0;
    }

    second_ability_cooldown_ = cooldown;
}

void Character::setOtherAbilityCooldown(bool first_ability_was_used)
{
    // After using one ability, the opposite one gets a small cooldown
    if (first_ability_was_used)
    {
        if (second_ability_cooldown_ < 2)
        {
            second_ability_cooldown_ = 2;
        }
    }
    else
    {
        if (first_ability_cooldown_ < 2)
        {
            first_ability_cooldown_ = 2;
        }
    }
}