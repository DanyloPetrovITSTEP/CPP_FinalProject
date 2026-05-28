#ifndef SAVESYSTEM_H
#define SAVESYSTEM_H

#include <string>
#include <memory>
#include "../Items/Inventory.h"
#include "../Items/Weapon.h"
#include "../Items/Armor.h"

class Character;

class SaveSystem {
private:
    std::string m_saveFileName;

public:
    explicit SaveSystem(std::string saveFileName = "save.dat");
    ~SaveSystem() = default;

    void saveGame(const std::unique_ptr<Character>& player, const Inventory& inventory, const std::shared_ptr<Weapon>& equippedWeapon, const std::shared_ptr<Armor>& equippedArmor);

    std::unique_ptr<Character> loadGame(Inventory& inventory, std::shared_ptr<Weapon>& equippedWeapon, std::shared_ptr<Armor>& equippedArmor);
};

#endif 
