// Enemy.h
// Base enemy class.
#pragma once
#include <string>
#include "../Core/Logger.h"

using namespace std;

class Enemy {
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
};