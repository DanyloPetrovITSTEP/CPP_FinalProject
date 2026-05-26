#include "SaveSystem.h"
#include "../Core/Exceptions.h"

#include "../Characters/Character.h"
#include "../Characters/Warrior.h"
#include "../Characters/Archer.h"
#include "../Characters/Mage.h"
#include "../Characters/Rogue.h"

#include <fstream>
#include <iostream>

SaveSystem::SaveSystem(std::string saveFileName) 
    : m_saveFileName(std::move(saveFileName)) {}

void SaveSystem::saveGame(const std::unique_ptr<Character>& player) {
    if (!player) {
        throw SaveLoadException("Cannot execute save: character instance is empty.");
    }

    std::ofstream outFile(m_saveFileName);
    if (!outFile.is_open()) {
        throw SaveLoadException("Failed to open storage file for writing data: " + m_saveFileName);
    }

    outFile << player->getClassName() << "\n";
    outFile << player->getName() << "\n";
    outFile << player->getHealth() << "\n";
    outFile << player->getDamage() << "\n";
    outFile << player->getGold() << "\n";

    std::cout << "Successfully saved progression data to file.\n";
}

std::unique_ptr<Character> SaveSystem::loadGame() {
    std::ifstream inFile(m_saveFileName);
    if (!inFile.is_open()) {
        throw SaveLoadException("No persistent save files found on local storage.");
    }

    std::string className;
    std::string name;
    int health;
    int damage;
    int gold;

    if (!(inFile >> className >> name >> health >> damage >> gold)) {
        throw SaveLoadException("Save file format is broken or corrupted.");
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
        throw SaveLoadException("Unknown or invalid character class type found in save data.");
    }

    if (loadedPlayer) {
        loadedPlayer->setDamage(damage);
        int damageTakenBefore = loadedPlayer->getMaxHealth() - health;
        if (damageTakenBefore > 0) {
            loadedPlayer->takeDamage(damageTakenBefore);
        }
        loadedPlayer->addGold(gold - loadedPlayer->getGold()); 
    }

    std::cout << "Progression recovered for character: " << name << " (" << className << ")\n";
    return loadedPlayer;
}
