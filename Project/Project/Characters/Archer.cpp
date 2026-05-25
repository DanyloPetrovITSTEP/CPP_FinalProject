#include "Archer.h"

Archer::Archer(const string& name) : Character(name, 80, 12, 50) {}

string Archer::getClassName() const { return "Archer"; }

void Archer::specialAbility(Character& target)
{
	target.takeDamage(getDamage() + 5);
}