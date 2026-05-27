// Potion.h
// Potion item class.
// Responsible for healing the player.
//
// Example:
// - Small Potion restores 20 HP
// - Big Potion restores 50 HP
//
// Overrides:
// - getType()
// - use()
#pragma once
#include "Item.h"

class Potion final : public Item {
private:
    int healAmount;

public:
    Potion(std::string n, std::string desc, int p, int heal);

    [[nodiscard]] ItemType getType() const override;
    void use(bool& shouldDestroy) override;
    [[nodiscard]] std::unique_ptr<Item> clone() const override;

    [[nodiscard]] int getHealAmount() const;
};