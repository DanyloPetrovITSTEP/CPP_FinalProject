// Potion.cpp
// Implementation file for Potion.
// Future logic:
// - restore health
// - write event to Logger
// Potion.cpp
// Implementation file for Potion consumables.

#include "Potion.h"
#include <iostream>
#include <utility>

Potion::Potion(std::string n, std::string desc, int p, int heal)
    : Item(std::move(n), std::move(desc), p), healAmount(heal) {
}

ItemType Potion::getType() const {
    return ItemType::Potion;
}

int Potion::getHealAmount() const {
    return healAmount;
}

void Potion::use(bool& shouldDestroy) {
    shouldDestroy = true;
    std::cout << "🧪 [POTION] Consumed " << getName() << " (Healed +" << healAmount << " HP)\n";
}

std::unique_ptr<Item> Potion::clone() const {
    return std::make_unique<Potion>(*this);
}
