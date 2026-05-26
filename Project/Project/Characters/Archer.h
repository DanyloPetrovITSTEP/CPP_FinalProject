#pragma once

#include "Character.h"

class Archer : public Character
{
public:

    Archer(const string& name);

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