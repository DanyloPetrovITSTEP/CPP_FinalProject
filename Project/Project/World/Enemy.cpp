#include "Enemy.h"
#include <iostream>

using namespace std;

Enemy::Enemy(const string& name, int maxHealth, int damage, int gold, Logger& logger)
    : Character(name, maxHealth, damage, gold), logger_(logger), ename_(name), is_dead_(false)
{
    updateIsDead();
}

string Enemy::getName() const { return ename_; }
int Enemy::getHealth()  const { return Character::getHealth(); }
int Enemy::getMaxHealth()   const { return Character::getMaxHealth(); }
int Enemy::getDamage()  const { return Character::getDamage(); }
int Enemy::getGold()    const { return Character::getGold(); }

bool Enemy::isAlive() const { return Character::isAlive(); }

void Enemy::takeDamage(int value) {
    Character::takeDamage(value);
    updateIsDead();
}

void Enemy::updateIsDead() {
    if (!is_dead_ && !isAlive()) {
        is_dead_ = true;
        cout << ename_ << " has died!" << endl;
        logger_.log(ename_ + " has died!");
    }
}

bool Enemy::basicAttack(Character& target) {
    target.takeDamage(getDamage());
    return true;
}

string Enemy::getClassName() const { return "Enemy"; }
string Enemy::getBasicAttackName() const { return "Strike"; }
string Enemy::getSecondActionName() const { return ""; }
string Enemy::getFirstAbilityName() const { return ""; }
string Enemy::getSecondAbilityName() const { return ""; }
bool Enemy::secondAction(Character&) { return false; }
bool Enemy::firstAbility(Character&, vector<Character*>&) { return false; }
bool Enemy::secondAbility(Character&, vector<Character*>&) { return false; }