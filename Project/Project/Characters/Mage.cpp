#include "Mage.h"

Mage::Mage(const string& name)
    : Character(name, 70, 18, 50)
{
}

string Mage::getClassName() const
{
    return "Mage";
}

string Mage::getBasicAttackName() const
{
    return "Magic Missile";
}

string Mage::getSecondActionName() const
{
    return "Healing";
}

string Mage::getFirstAbilityName() const
{
    return "Crystallization";
}

string Mage::getSecondAbilityName() const
{
    return "Fireball";
}

bool Mage::basicAttack(Character& target)
{
    target.takeDamage(getDamage());
    return true;
}

bool Mage::secondAction(Character& target)
{
    target.heal(15);
    return true;
}

bool Mage::firstAbility(Character& target, vector<Character*>& enemies)
{
    if (!canUseFirstAbility())
    {
        return false;
    }

    target.applyDamageMultiplier(2.0, 2);

    setFirstAbilityCooldown(3);
    setOtherAbilityCooldown(true);

    return true;
}

bool Mage::secondAbility(Character& target, vector<Character*>& enemies)
{
    if (!canUseSecondAbility())
    {
        return false;
    }

    // Fireball damages all alive enemies and applies burning.
    for (Character* enemy : enemies)
    {
        if (enemy != nullptr && enemy->isAlive())
        {
            enemy->takeDamage(10);
            enemy->applyBurn(2, 3);
        }
    }

    setSecondAbilityCooldown(5);
    setOtherAbilityCooldown(false);

    return true;
}