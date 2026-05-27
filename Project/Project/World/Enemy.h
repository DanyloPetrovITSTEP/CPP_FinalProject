#pragma once
#include <string>
#include "../Core/Logger.h"
#include "../Characters/Character.h"



class Enemy : public Character {
private:
    string ename_;
    int health_;
    int maxHealth_;
    int damage_;
    int gold_;
    bool is_dead_;
    Logger& logger_;

public:
    Enemy(const string& name, int maxHealth, int damage, int gold, Logger& logger);
    string getName() const;
    int getHealth() const;
    int getMaxHealth() const;
    int getDamage() const;
    int getGold() const;
    void updateIsDead();
    void takeDamage(int value);
    bool basicAttack(Character& target) override;
    bool isAlive() const;



    virtual string getClassName() const override;

    // Names are used in battle menu
    virtual string getBasicAttackName() const override;
    virtual string getSecondActionName() const override;
    virtual string getFirstAbilityName() const override;
    virtual string getSecondAbilityName() const override;

    // Each class has its own actions and abilities
    virtual bool basicAttack(Character& target) override;
    virtual bool secondAction(Character& target) override;
    virtual bool firstAbility(Character& target, vector<Character*>& enemies) override;
    virtual bool secondAbility(Character& target, vector<Character*>& enemies) override;
};
