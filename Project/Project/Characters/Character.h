#pragma once

#include <string>

using namespace std;

class Character
{
private:
	string name_;
	int health_;
	int maxHealth_;
	int damage_;
	int gold_;

protected:
	void setDamage(int damage);

public:
	Character(const string& name, int maxHealth, int damage, int gold);

	virtual ~Character() = default;

	const string& getName() const;
	int getHealth() const;
	int getMaxHealth() const;
	int getDamage() const;
	int getGold() const;

	bool isAlive() const;

	void takeDamage(int value);
	void heal(int value);
	void addGold(int value);
	void spendGold(int value);

	virtual string getClassName() const = 0;
	virtual void specialAbility(Character& target) = 0;
};