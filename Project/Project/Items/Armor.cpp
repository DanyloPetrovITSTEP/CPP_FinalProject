// Armor.cpp
// Implementation file for Armor.
// Future logic:
// - apply protection or max health bonus
// - write event to Logger
// Armor.cpp
// Implementation file for Armor.

// Armor.cpp
// Implementation file for Armor.

#include "Armor.h"
#include <iostream>

Armor::Armor(std::string n, std::string desc, int p, int def)
    : Item(std::move(n), std::move(desc), p), defense(def) {
}

ItemType Armor::getType() const { return ItemType::Armor; }
int Armor::getDefense() const { return defense; }

void Armor::upgradeArmor(int defenseBonus, int priceIncrease) {
    upgradeLevel++;
    defense += defenseBonus;
    addPrice(priceIncrease);
}

void Armor::use(bool& shouldDestroy) {
    shouldDestroy = false;
    std::cout << "[ARMOR] Equipped " << getName();
    if (upgradeLevel > 0) std::cout << " +" << upgradeLevel;
    std::cout << " (Total defense: " << defense << ")\n";
}

std::unique_ptr<Item> Armor::clone() const {
    return std::make_unique<Armor>(*this);
}
