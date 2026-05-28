// Shop.h
// Shop system.
// Responsible for selling items to player.
//
// Menu example:
// 1. Buy potion
// 2. Buy weapon
// 3. Buy armor
// 4. Back
//
// Suggested storage:
// - map<string, item data>
#pragma once
#include <vector>
#include <memory>
#include "../Items/Item.h"
#include "../Items/Inventory.h"

class Shop {
private:
    std::vector<std::unique_ptr<Item>> showcase;
public:
    Shop();
    void showAssortment() const;
    void buyItem(size_t idx, Inventory& inv, int& gold);
    void sellItem(size_t idx, Inventory& inv, int& gold);
};
