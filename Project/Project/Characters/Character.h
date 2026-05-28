#pragma once

#include <string>
#include <vector>

using namespace std;

class Character
{
private:
	// Basic character stats
	string name_;
	int health_;
	int max_health_;
	int damage_;
	int gold_;
	int weapon_damage_bonus_;
	int armor_defense_;

	// Cooldowns for character two special abilities
	int first_ability_cooldown_;
	int second_ability_cooldown_;

	// Simple status effects
	int burn_damage_;
	int burn_rounds_;

	double damage_multiplier_;
	int damage_multiplier_rounds_;

protected:
	// Protected setters are used by child classes
	void setFirstAbilityCooldown(int cooldown);
	void setSecondAbilityCooldown(int cooldown);
	void setOtherAbilityCooldown(bool first_ability_was_used);

public:
	Character(const string& name, int max_health, int damage, int gold);

	virtual ~Character() = default;

	// Getters for character stats
	const string& getName() const;
	int getHealth() const;
	int getMaxHealth() const;
	int getDamage() const;
	int getGold() const;
	int getBaseDamage() const;
	int getWeaponDamageBonus() const;
	int getArmorDefense() const;

	void setDamage(int damage);
	void setWeaponDamageBonus(int bonus);
	void setArmorDefense(int defense);

	bool isAlive() const;
	bool isFullHealth() const;

	// Cooldown checks for special abilities
	int getFirstAbilityCooldown() const;
	int getSecondAbilityCooldown() const;

	bool canUseFirstAbility() const;
	bool canUseSecondAbility() const;

	// Basic character state changes
	void heal(int value);
	void addGold(int value);
	bool spendGold(int value);

	// Status effects are used by some abilities
	void applyBurn(int damage, int rounds);
	void applyDamageMultiplier(double multiplier, int rounds);
	void processStatusEffects();
	void reduceCooldowns();

	// Each character class must return its own class name
	virtual string getClassName() const = 0;
	
	// Names are used in battle menu
	virtual string getBasicAttackName() const = 0;
	virtual string getSecondActionName() const = 0;
	virtual string getFirstAbilityName() const = 0;
	virtual string getSecondAbilityName() const = 0;

	// Each class has its own actions and abilities
	virtual void takeDamage(int value);
	virtual bool basicAttack(Character& target) = 0;
	virtual bool secondAction(Character& target) = 0;
	virtual bool firstAbility(Character& target, vector<Character*>& enemies) = 0;
	virtual bool secondAbility(Character& target, vector<Character*>& enemies) = 0;
};