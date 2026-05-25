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

void Inventory::addItem(std::unique_ptr<Item> item) {
    if (item) {
        slots.push_back(std::move(item));
    }
}

void Inventory::showItems() const {
    if (isEmpty()) {
        std::cout << "[Inventory is empty]\n";
        return;
    }
    for (size_t i = 0; i < slots.size(); ++i) {
        std::cout << i + 1 << ". " << slots[i]->getName() << "\n";
    }
}

void Inventory::useItem(size_t index) {
    if (index >= slots.size()) return;

    bool shouldDestroy = false;
    slots[index]->use(shouldDestroy);

    if (shouldDestroy) {
        removeItem(index);
    }
}

void Inventory::removeItem(size_t index) {
    if (index < slots.size()) {
        slots.erase(slots.begin() + index);
    }
}

bool Inventory::isEmpty() const {
    return slots.empty();
}

std::unique_ptr<Item> Inventory::extractItem(size_t index) {
    std::unique_ptr<Item> extracted = std::move(slots[index]);
    removeItem(index);
    return extracted;
}
