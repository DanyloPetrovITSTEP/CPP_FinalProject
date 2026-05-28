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

enum class WeaponClass { Warrior, Archer, Mage, Thief };

class Weapon final : public Item {
private:
    int damage;
    WeaponClass reqClass;
public:
    Weapon(std::string n, std::string desc, int p, int dmg, WeaponClass wClass);
    [[nodiscard]] ItemType getType() const override;
    void use(bool& shouldDestroy) override;
    [[nodiscard]] std::unique_ptr<Item> clone() const override;
    [[nodiscard]] int getDamage() const;
    [[nodiscard]] WeaponClass getRequiredClass() const;
    void upgradeWeapon(int damageBonus, int priceIncrease);
};
