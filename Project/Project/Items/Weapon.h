// Weapon.h
// Weapon item class.
// Responsible for increasing character damage.
//
// Example:
// - Iron Sword gives +5 damage
// - Magic Staff gives +8 damage
//
// Overrides:
// - getType()
// - use()
#pragma once
#include "Item.h"

// Weapon categories matching the 4 character classes
enum class WeaponClass {
    Warrior, // Swords, Axes, Heavy weapons
    Archer,  // Bows, Crossbows
    Mage,    // Staves, Wands
    Thief    // Daggers, Short blades
};

class Weapon final : public Item {
private:
    int damage;
    WeaponClass reqClass; // Required class to wield this weapon

public:
    Weapon(std::string n, std::string desc, int p, int dmg, WeaponClass wClass);

    [[nodiscard]] ItemType getType() const override;
    void use(bool& shouldDestroy) override;
    [[nodiscard]] std::unique_ptr<Item> clone() const override;

    // Getter for player to calculate and sum up total damage
    [[nodiscard]] int getDamage() const;

    // Getter to check if player class matches weapon requirements
    [[nodiscard]] WeaponClass getRequiredClass() const;
};
