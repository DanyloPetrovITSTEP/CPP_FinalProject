#pragma once

#include "Character.h"

class Warrior : public Character
{
public:

	Warrior(const string& name);

	string getClassName() const override;
	void specialAbility(Character& target) override;
};