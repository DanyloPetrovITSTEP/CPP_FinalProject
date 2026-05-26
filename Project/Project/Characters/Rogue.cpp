#include "Rogue.h"

Rogue::Rogue(const string& name) : Character(name, 75, 14, 50), guaranteed_stealth_hits_(0) {}

string Rogue::getClassName() const
{
	return "Rogue";
}

string Rogue::getBasicAttackName() const
{
	return "Dagger Strike";
}

string Rogue::getSecondActionName() const
{
	return "Stealth Strike";
}

string Rogue::getFirstAbilityName() const
{
	return "Master Of Stealth";
}

string Rogue::getSecondAbilityName() const
{
	return "Life Steal";
}

bool Rogue::basicAttack(Character& target)
{
	target.takeDamage(getDamage());
	return true;
}

bool Rogue::secondAction(Character& target)
{
	if (guaranteed_stealth_hits_ > 0)
	{
		target.takeDamage(getDamage() * 2);
		guaranteed_stealth_hits_--;
	}
	else
	{
		target.takeDamage(getDamage());
	}
	return true;
}

bool Rogue::firstAbility(Character& target, vector<Character*>& enemies)
{
	if (!canUseFirstAbility())
	{
		return false;
	}

	guaranteed_stealth_hits_ = 2;

	setFirstAbilityCooldown(4);
	setOtherAbilityCooldown(true);

	return true;
}

bool Rogue::secondAbility(Character& target, vector<Character*>& enemies)
{
	if (!canUseSecondAbility())
	{
		return false;
	}
	
	if (isFullHealth())
	{
		return false;
	}

	int stolen_health = target.getHealth() / 10;

	if (stolen_health < 1)
	{
		stolen_health = 1;
	}

	target.takeDamage(stolen_health);
	heal(stolen_health);

	setSecondAbilityCooldown(6);
	setOtherAbilityCooldown(false);

	return true;
}