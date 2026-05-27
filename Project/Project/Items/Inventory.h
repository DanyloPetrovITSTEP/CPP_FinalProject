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
#include "../Items/Item.h"

// Player inventory class.
// Responsible for storing and using items.
class Inventory {
private:
    // Suggested storage:
    std::vector<std::unique_ptr<Item>> slots;

public:
    Inventory() = default;

    // Methods required by structural comments:
    void addItem(std::unique_ptr<Item> item);
    void showItems() const;
    void useItem(size_t index);
    void removeItem(size_t index);
    bool isEmpty() const;

    // Helper methods for Shop interaction:
    size_t getSize() const { return slots.size(); }
    Item* getItemPtr(size_t index) { return slots[index].get(); }
    std::unique_ptr<Item> extractItem(size_t index);
};