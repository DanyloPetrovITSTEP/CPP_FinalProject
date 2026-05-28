// Weapon.cpp
// Implementation file for Weapon.
// Future logic:
// - apply damage bonus
// - write event to Logger
// Weapon.cpp
// Implementation file for Weapons targeting specific hero classes.

#include "Weapon.h"
#include <iostream>

Weapon::Weapon(std::string n, std::string desc, int p, int dmg, WeaponClass wClass)
    : Item(std::move(n), std::move(desc), p), damage(dmg), reqClass(wClass) {
}

ItemType Weapon::getType() const { return ItemType::Weapon; }
int Weapon::getDamage() const { return damage; }
WeaponClass Weapon::getRequiredClass() const { return reqClass; }

void Weapon::upgradeWeapon(int damageBonus, int priceIncrease) {
    upgradeLevel++;
    damage += damageBonus;
    addPrice(priceIncrease);
}

void Weapon::use(bool& shouldDestroy) {
    shouldDestroy = false;
    std::cout << "\n[WEAPON] Equipped " << getName();
    if (upgradeLevel > 0) std::cout << " +" << upgradeLevel;
    std::cout << " (Weapon damage: +" << damage << ")\n";
}

std::unique_ptr<Item> Weapon::clone() const {
    return std::make_unique<Weapon>(*this);
}
