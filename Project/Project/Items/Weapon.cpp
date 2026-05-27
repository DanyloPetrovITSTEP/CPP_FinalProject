// Weapon.cpp
// Implementation file for Weapon.
// Future logic:
// - apply damage bonus
// - write event to Logger
// Weapon.cpp
// Implementation file for Weapons targeting specific hero classes.

#include "Weapon.h"
#include <iostream>
#include <utility>

Weapon::Weapon(std::string n, std::string desc, int p, int dmg, WeaponClass wClass)
    : Item(std::move(n), std::move(desc), p), damage(dmg), reqClass(wClass) {
}

ItemType Weapon::getType() const {
    return ItemType::Weapon;
}

int Weapon::getDamage() const {
    return damage;
}

WeaponClass Weapon::getRequiredClass() const {
    return reqClass;
}

void Weapon::use(bool& shouldDestroy) {
    shouldDestroy = false;

    std::cout << "⚔️ [WEAPON] Equipped " << getName() << " (+" << damage << " Damage)\n";
    std::cout << "[LOG]: Weapon equipped. Ready for stat recalculation.\n";
}

std::unique_ptr<Item> Weapon::clone() const {
    return std::make_unique<Weapon>(*this);
}