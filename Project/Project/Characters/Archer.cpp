#include "Archer.h"

Archer::Archer(const string& name) : Character(name, 80, 12, 50) {}

string Archer::getClassName() const
{
	return "Archer";
}

string Archer::getBasicAttackName() const
{
	return "Arrow Shot";
}

string Archer::getSecondActionName() const
{
	return "Precise Shot";
}

string Archer::getFirstAbilityName() const
{
	return "Iron Rain";
}

string Archer::getSecondAbilityName() const
{
	return "Speed Of Sound Shot";
}

bool Archer::basicAttack(Character& target)
{
	target.takeDamage(getDamage());
	return true;
}

bool Archer::secondAction(Character& target)
{
	target.takeDamage(getDamage() + 5);
	return true;
}

bool Archer::firstAbility(Character& target, vector<Character*>& enemies)
{
	if (!canUseFirstAbility())
	{
		return false;
	}

	// Iron Rain damages all alive enemies
	for (Character* enemy : enemies)
	{
		if (enemy != nullptr && enemy->isAlive())
		{
			enemy->takeDamage(15);
		}
	}

	setFirstAbilityCooldown(4);
	setOtherAbilityCooldown(true);

	return true;
}

bool Archer::secondAbility(Character& target, vector<Character*>& enemies)
{
	if (!canUseSecondAbility())
	{
		return false;
	}

	target.takeDamage(getDamage() * 3);

	setSecondAbilityCooldown(6);
	setOtherAbilityCooldown(false);

	return true;
}