// Inventory.cpp
// Implementation file for Inventory.
// Future logic:
// - add item to vector
// - validate item index
// - throw InventoryException on wrong index
// - use selected item
// - remove used item if needed
#include "Inventory.h"
#include <iostream>
#include <stdexcept>

void Inventory::addItem(std::unique_ptr<Item> item) {
    if (item) slots.emplace_back(std::move(item));
}

void Inventory::showItems() const {
    if (isEmpty()) { std::cout << "[Inventory is empty]\n"; return; }
    std::cout << "\n--- PLAYER INVENTORY ---\n";
    for (size_t i = 0; i < slots.size(); ++i) {
        std::cout << i + 1 << ". " << slots[i]->getName();
        if (slots[i]->getUpgradeLevel() > 0) std::cout << " +" << slots[i]->getUpgradeLevel();
        std::cout << " (" << slots[i]->getDescription() << ") | Price: " << slots[i]->getPrice() << " Gold\n";
    }
}

void Inventory::useItem(size_t index, std::shared_ptr<Weapon>& eqW, std::shared_ptr<Armor>& eqA) {
    if (index >= slots.size()) throw std::out_of_range("Index error");
    if (slots[index]->getType() == ItemType::Weapon) {
        if (auto* wPtr = dynamic_cast<Weapon*>(slots[index].get())) {
            eqW = std::shared_ptr<Weapon>(static_cast<Weapon*>(wPtr->clone().release()));
        }
    }
    else if (slots[index]->getType() == ItemType::Armor) {
        if (auto* aPtr = dynamic_cast<Armor*>(slots[index].get())) {
            eqA = std::shared_ptr<Armor>(static_cast<Armor*>(aPtr->clone().release()));
        }
    }
    bool destroy = false;
    slots[index]->use(destroy);
    if (destroy) slots.erase(slots.begin() + index);
}

void Inventory::useItem(size_t index) {
    std::shared_ptr<Weapon> eqW = nullptr;
    std::shared_ptr<Armor> eqA = nullptr;
    useItem(index, eqW, eqA);
}

bool Inventory::isEmpty() const { return slots.empty(); }
size_t Inventory::getSize() const { return slots.size(); }

Item* Inventory::getItemPtr(size_t index) {
    return (index >= slots.size()) ? nullptr : slots[index].get();
}

std::unique_ptr<Item> Inventory::extractItem(size_t index) {
    if (index >= slots.size()) return nullptr;
    auto item = std::move(slots[index]);
    slots.erase(slots.begin() + index);
    return item;
}

const std::vector<std::unique_ptr<Item>>& Inventory::getItems() const
{
    return slots;
}

void Inventory::clear()
{
    slots.clear();
}