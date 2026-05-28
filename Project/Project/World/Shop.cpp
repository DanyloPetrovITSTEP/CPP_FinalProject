// Shop.cpp
// Implementation file for Shop.
// Future logic:
// - show shop menu
// - check player gold
// - add bought item to inventory
// - log purchase
#include "Shop.h"
#include "../Items/Weapon.h"
#include "../Items/Armor.h"
#include "../Items/Potion.h"
#include <iostream>
#include <stdexcept>

class InsufficientGoldException : public std::runtime_error {
public:
    InsufficientGoldException() : std::runtime_error("Not enough gold!") {}
};

Shop::Shop() {
    showcase.emplace_back(std::make_unique<Weapon>("Iron Sword", "For Warrior", 80, 25, WeaponClass::Warrior));
    showcase.emplace_back(std::make_unique<Weapon>("Long Bow", "For Archer", 75, 18, WeaponClass::Archer));
    showcase.emplace_back(std::make_unique<Weapon>("Runic Staff", "For Mage", 90, 30, WeaponClass::Mage));
    showcase.emplace_back(std::make_unique<Weapon>("Shadow Dagger", "For Rogue", 60, 14, WeaponClass::Thief));
    showcase.emplace_back(std::make_unique<Armor>("Steel Armor", "Heavy armor", 150, 12));
    showcase.emplace_back(std::make_unique<Potion>("Health Potion", "Restores 50 HP", 20, 50));
}

void Shop::showAssortment() const {
    std::cout << "\n--- SHOP ASSORTMENT ---\n";
    for (size_t i = 0; i < showcase.size(); ++i) {
        std::cout << i + 1 << ". " << showcase[i]->getName() << " | " << showcase[i]->getPrice() << " Gold\n";
    }
}

void Shop::buyItem(size_t idx, Inventory& inv, int& gold) {
    if (idx >= showcase.size()) throw std::out_of_range("Invalid index");
    int cost = showcase[idx]->getPrice();
    if (gold < cost) throw InsufficientGoldException();
    gold -= cost;
    inv.addItem(showcase[idx]->clone());
    std::cout << "\nBought " << showcase[idx]->getName() << " for " << cost << " gold.\n";
}

void Shop::sellItem(size_t idx, Inventory& inv, int& gold) {
    auto item = inv.extractItem(idx);
    if (!item) return;
    int price = item->getPrice() / 2;
    gold += price;
    std::cout << "\nSold " << item->getName() << " for " << price << " gold.\n";
}
