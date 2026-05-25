#include "Warrior.h"

Warrior::Warrior(const string& name) : Character(name, 100, 10, 50) {}

string Warrior::getClassName() const { return "Warrior" };

void Warrior::specialAbility(Character& target)
{
	target.takeDamage(getDamage() * 2);
}