// Armor.h
// Armor item class.
// Responsible for increasing max health or reducing damage.
//
// Example:
// - Leather Armor gives +10 max HP
// - Steel Armor gives +25 max HP
//
// Overrides:
// - getType()
// - use()
#pragma once
#include "Item.h"

class Armor final : public Item {
private:
    int defense;
public:
    Armor(std::string n, std::string desc, int p, int def);
    [[nodiscard]] ItemType getType() const override;
    void use(bool& shouldDestroy) override;
    [[nodiscard]] std::unique_ptr<Item> clone() const override;
    [[nodiscard]] int getDefense() const;
    void upgradeArmor(int defenseBonus, int priceIncrease);
};
