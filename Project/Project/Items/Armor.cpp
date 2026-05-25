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
#include <utility>

Armor::Armor(std::string n, std::string desc, int p, int def)
    : Item(std::move(n), std::move(desc), p), defense(def) {
}

ItemType Armor::getType() const {
    return ItemType::Armor;
}

int Armor::getDefense() const {
    return defense;
}

void Armor::use(bool& shouldDestroy) {
    shouldDestroy = false;
    std::cout << "🛡️ [ARMOR] Equipped " << getName() << " (+" << defense << " Defense)\n";
}

std::unique_ptr<Item> Armor::clone() const {
    return std::make_unique<Armor>(*this);
}
