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
    string enemyName;
    int health;
    int damage;
    int rewardGold;

protected:
    Enemy(string eName, int hp, int dmg, int gold);
    string getName();
    int getHealth();
    int getDamage();
    int getRewardGold();
};