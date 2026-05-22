// Enemy.h
// Base enemy class.
// Responsible for enemy stats and behavior.
//
// Fields:
// - name
// - health
// - damage
// - reward gold
//
// Derived enemy ideas:
// - Goblin
// - Skeleton
// - DungeonBoss

#pragma once
#include <string>

using namespace std;

class Enemy {
private:
    string ename_;
    int health_;
    int maxHealth_;
    int damage_;
    int gold_;

protected:
    Enemy(const string& name, int maxHealth, int damage, int gold);
    string getName();
    int getHealth();
	int getMaxHealth();
    int getDamage();
    int getGold();
};