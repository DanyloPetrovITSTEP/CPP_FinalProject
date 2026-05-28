#include "SaveSystem.h"
#include "../Core/Exceptions.h"
#include "../Characters/Character.h"
#include "../Characters/Warrior.h"
#include "../Characters/Archer.h"
#include "../Characters/Mage.h"
#include "../Characters/Rogue.h"
#include <fstream>

SaveSystem::SaveSystem(std::string saveFileName) 
    : m_saveFileName(std::move(saveFileName)) {}

void SaveSystem::saveGame(const std::unique_ptr<Character>& player) {
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
    outFile << player->getDamage() << "\n";
    outFile << player->getGold() << "\n";
}

std::unique_ptr<Character> SaveSystem::loadGame() {
    std::ifstream inFile(m_saveFileName);
    if (!inFile.is_open()) {
        throw SaveLoadException("Read target channel missing: Save tracking record file does not exist.");
    }

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

    return loadedPlayer;
}
