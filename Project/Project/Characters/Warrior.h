#pragma once

#include "Character.h"

class Warrior : public Character
{
private:
	// Counts attacks boosted by "Viking Call" ability
	int viking_call_hits_;

	int getCurrentAttackDamage();

public:

	Warrior(const string& name);

	string getClassName() const override;
	
	string getBasicAttackName() const override;
	string getSecondActionName() const override;
	string getFirstAbilityName() const override;
	string getSecondAbilityName() const override;

	bool basicAttack(Character& target) override;
	bool secondAction(Character& target) override;
	bool firstAbility(Character& target, vector<Character*>& enemies) override;
	bool secondAbility(Character& target, vector<Character*>& enemies) override;
};