#include "SaveSystem.h"
#include "../Core/Exceptions.h"
#include "../Characters/Character.h"
#include "../Characters/Warrior.h"
#include "../Characters/Archer.h"
#include "../Characters/Mage.h"
#include "../Characters/Rogue.h"
#include "../Items/Inventory.h"
#include "../Items/Weapon.h"
#include "../Items/Armor.h"
#include "../Items/Potion.h"
#include <fstream>
#include <utility>

SaveSystem::SaveSystem(std::string saveFileName) 
    : m_saveFileName(std::move(saveFileName)) {}

std::unique_ptr<Item> CreateItemByName(const std::string& itemName)
{
    if (itemName == "Iron Sword")
    {
        return std::make_unique<Weapon>("Iron Sword", "For warrior", 80, 25, WeaponClass::Warrior);
    }

    if (itemName == "Long Bow")
    {
        return std::make_unique<Weapon>("Long Bow", "For archer", 75, 18, WeaponClass::Archer);
    }

    if (itemName == "Runic Staff")
    {
        return std::make_unique<Weapon>("Runic Staff", "For mage", 90, 30, WeaponClass::Mage);
    }

    if (itemName == "Shadow Dagger")
    {
        return std::make_unique<Weapon>("Shadow Dagger", "For rogue", 60, 14, WeaponClass::Thief);
    }

    if (itemName == "Steel Armor")
    {
        return std::make_unique<Armor>("Steel Armor", "Heavy armor", 150, 12);
    }

    if (itemName == "Health Potion")
    {
        return std::make_unique<Potion>("Health Potion", "Restores 50 HP", 20, 50);
    }

    return nullptr;
}

void SaveSystem::saveGame(const std::unique_ptr<Character>& player, const Inventory& inventory, const std::shared_ptr<Weapon>& equippedWeapon, const std::shared_ptr<Armor>& equippedArmor) {
    if (!player) {
        throw SaveLoadException("Abort operations: Attempting to serialize a null object state reference.");
    }

    std::ofstream outFile(m_saveFileName);
    if (!outFile.is_open()) {
        throw SaveLoadException("I/O File creation lock failed for filename path: " + m_saveFileName);
    }

    outFile << player->getClassName() << "\n";
    outFile << player->getName() << "\n";
    outFile << player->getHealth() << "\n";
    outFile << player->getBaseDamage() << "\n";
    outFile << player->getGold() << "\n";

    const auto& items = inventory.getItems();

    outFile << items.size() << "\n";

    for (const auto& item : items)
    {
        outFile << item->getName() << "\n";
    }

    outFile << (equippedWeapon ? equippedWeapon->getName() : "None") << "\n";
    outFile << (equippedArmor ? equippedArmor->getName() : "None") << "\n";
}

std::unique_ptr<Character> SaveSystem::loadGame(Inventory& inventory, std::shared_ptr<Weapon>& equippedWeapon, std::shared_ptr<Armor>& equippedArmor) {
    std::ifstream inFile(m_saveFileName);
    if (!inFile.is_open()) {
        throw SaveLoadException("Read target channel missing: Save tracking record file does not exist.");
    }

    inventory.clear();

    std::string className;
    std::string name;
    int health = 0;
    int damage = 0;
    int gold = 0;

    if (!(inFile >> className >> name >> health >> damage >> gold)) {
        throw SaveLoadException("Data integrity compromised: file read mismatch or corrupted segments.");
    }

    std::unique_ptr<Character> loadedPlayer = nullptr;

    if (className == "Warrior") {
        loadedPlayer = std::make_unique<Warrior>(name);
    } else if (className == "Archer") {
        loadedPlayer = std::make_unique<Archer>(name);
    } else if (className == "Mage") {
        loadedPlayer = std::make_unique<Mage>(name);
    } else if (className == "Rogue") {
        loadedPlayer = std::make_unique<Rogue>(name);
    } else {
        throw SaveLoadException("Polymorphic runtime initialization failed: Class name trace token corrupt.");
    }

    if (loadedPlayer) {
        loadedPlayer->setDamage(damage);
        int hitDiff = loadedPlayer->getMaxHealth() - health;
        if (hitDiff > 0) {
            loadedPlayer->takeDamage(hitDiff);
        }
        loadedPlayer->addGold(gold - loadedPlayer->getGold());
    }

    size_t itemCount = 0;
    inFile >> itemCount;
    inFile.ignore();

    for (size_t i = 0; i < itemCount; i++)
    {
        std::string itemName;
        std::getline(inFile, itemName);

        std::unique_ptr<Item> item = CreateItemByName(itemName);

        if (item)
        {
            inventory.addItem(std::move(item));
        }
    }

    std::string equippedWeaponName;
    std::string equippedArmorName;

    std::getline(inFile, equippedWeaponName);
    std::getline(inFile, equippedArmorName);

    equippedWeapon = nullptr;
    equippedArmor = nullptr;

    std::unique_ptr<Item> weaponItem = CreateItemByName(equippedWeaponName);

    if (weaponItem && weaponItem->getType() == ItemType::Weapon)
    {
        equippedWeapon = std::shared_ptr<Weapon>(static_cast<Weapon*>(weaponItem.release()));
    }

    std::unique_ptr<Item> armorItem = CreateItemByName(equippedArmorName);

    if (armorItem && armorItem->getType() == ItemType::Armor)
    {
        equippedArmor = std::shared_ptr<Armor>(static_cast<Armor*>(armorItem.release()));
    }

    return loadedPlayer;
}
