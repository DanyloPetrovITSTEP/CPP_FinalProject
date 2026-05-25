#include "Warrior.h"

Warrior::Warrior(const string& name) : Character(name, 100, 10, 50), viking_call_hits_(0) {}

string Warrior::getClassName() const
{
	return "Warrior";
}

string Warrior::getBasicAttackName() const
{
	return "Steel Strike";
}

string Warrior::getSecondActionName() const
{
	return "Shield Bash";
}

string Warrior::getFirstAbilityName() const
{
	return "Viking Call";
}

string Warrior::getSecondAbilityName() const
{
	return "Crusher";
}

int Warrior::getCurrentAttackDamage()
{
	int current_damage = getDamage();

	// Viking Call boosts next two attacks damage
	if (viking_call_hits_ > 0)
	{
		current_damage = static_cast<int>(current_damage * 1.5);
		viking_call_hits_--;
	}

	return current_damage;
}

bool Warrior::basicAttack(Character& target)
{
	target.takeDamage(getCurrentAttackDamage());
	return true;
}

bool Warrior::secondAction(Character& target)
{
	target.takeDamage(getCurrentAttackDamage() + 3);
	return true;
}

bool Warrior::firstAbility(Character& target, vector<Character*>& enemies)
{
	if (!canUseFirstAbility())
	{
		return false;
	}

	viking_call_hits_ = 2;

	setFirstAbilityCooldown(4);
	setOtherAbilityCooldown(true);

	return true;
}

bool Warrior::secondAbility(Character& target, vector<Character*>& enemies)
{
	if (!canUseFirstAbility())
	{
		return false;
	}

	target.takeDamage(25);

	setSecondAbilityCooldown(6);
	setOtherAbilityCooldown(true);

	return true;
}