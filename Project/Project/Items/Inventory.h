// Inventory.h
// Player inventory class.
// Responsible for storing and using items.
//
// Suggested storage:
// - vector<unique_ptr<Item>>
//
// Methods:
// - addItem()
// - showItems()
// - useItem()
// - removeItem()
// - isEmpty()

#pragma once
#include <vector>
#include <memory>
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"

// Player inventory class.
// Responsible for storing and using items.

class Inventory {
private:
    std::vector<std::unique_ptr<Item>> slots;
public:
    Inventory() = default;
    void addItem(std::unique_ptr<Item> item);
    void showItems() const;
    void useItem(size_t index, std::shared_ptr<Weapon>& eqW, std::shared_ptr<Armor>& eqA);
    void useItem(size_t index);
    [[nodiscard]] bool isEmpty() const;
    [[nodiscard]] size_t getSize() const;
    [[nodiscard]] Item* getItemPtr(size_t index);
    std::unique_ptr<Item> extractItem(size_t index);
    const std::vector<std::unique_ptr<Item>>& getItems() const;
    void clear();
};
