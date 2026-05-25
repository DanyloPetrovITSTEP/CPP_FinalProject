// Item.cpp
// Implementation file for common Item methods.
// Future logic:
// - item name getter
// - item description getter
// - item price getter
// Item.cpp
// Implementation file for common Item methods.

#include "Item.h"
#include <utility>

Item::Item(std::string n, std::string desc, int p)
    : name(std::move(n)), description(std::move(desc)), price(p) {
}

std::string Item::getName() const {
    return name;
}

std::string Item::getDescription() const {
    return description;
}

int Item::getPrice() const {
    return price;
}
