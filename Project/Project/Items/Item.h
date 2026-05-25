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

enum class ItemType {
    Potion,
    Weapon,
    Armor
};

class Item {
private:
    std::string name;
    std::string description;
    int price;

protected:
    Item(std::string n, std::string desc, int p);

public:
    virtual ~Item() = default;

    std::string getName() const;
    std::string getDescription() const;
    int getPrice() const;

    virtual ItemType getType() const = 0;
    virtual void use(bool& shouldDestroy) = 0;
    virtual std::unique_ptr<Item> clone() const = 0;
};
