#pragma once

#include "Character.h"

class Rogue : public Character
{
private:
    // Makes stealth hits guranteed for a few attacks
    int guaranteed_stealth_hits_;

public:
    Rogue(const string& name);

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