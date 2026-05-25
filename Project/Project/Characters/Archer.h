#pragma once

#include "Character.h"

class Archer : public Character
{
public:

	Archer(const string& name);

	string getClassName() const override;
	void specialAbility(Character& target) override;
};