// Item.h
// Base abstract item class.
// Responsible for common item data.
//
// Fields:
// - name
// - description
// - price
//
// Virtual methods:
// - getType()
// - use()
//
// Derived classes:
// - Potion
// - Weapon
// - Armor
#pragma once
#include <string>
#include <memory>

enum class ItemType { Potion, Weapon, Armor };

class Item {
private:
    std::string name;
    std::string description;
    int price;
protected:
    int upgradeLevel{ 0 };
    Item(std::string n, std::string desc, int p);
    void addPrice(int amount);
public:
    virtual ~Item() = default;
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] std::string getDescription() const;
    [[nodiscard]] int getPrice() const;
    [[nodiscard]] int getUpgradeLevel() const;
    [[nodiscard]] virtual ItemType getType() const = 0;
    virtual void use(bool& shouldDestroy) = 0;
    [[nodiscard]] virtual std::unique_ptr<Item> clone() const = 0;
};
