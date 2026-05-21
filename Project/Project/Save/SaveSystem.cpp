#include "SaveSystem.h"
#include "../Core/Exceptions.h"
#include "../Core/Logger.h"

#include "../Characters/Warrior.h"
#include "../Characters/Mage.h"
#include "../Characters/Archer.h"
#include "../Characters/Rogue.h"

#include <fstream>

void SaveSystem::saveGame(const std::string& filename, const Character& player) {
    std::ofstream out(filename);
    
    if (!out.is_open()) {
        throw SaveLoadException("Failed to open save file for writing: " + filename);
    }

    out << player.getClassName() << "\n";
    out << player.getName() << "\n";
    out << player.getHealth() << "\n";
    out << player.getMaxHealth() << "\n";
    out << player.getDamage() << "\n";
    out << player.getGold() << "\n";
    out << 0 << "\n"; 

    Logger::getInstance().log("Game progress successfully saved to: " + filename);
}

std::unique_ptr<Character> SaveSystem::loadGame(const std::string& filename) {
    std::ifstream in(filename);
    
    if (!in.is_open()) {
        throw SaveLoadException("Save file not found or cannot be opened: " + filename);
    }

    std::string class_name, name;
    int health, max_health, damage, gold;

    if (!(in >> class_name >> name >> health >> max_health >> damage >> gold)) {
        throw SaveLoadException("Save file is corrupted or has an invalid format!");
    }

    std::unique_ptr<Character> loaded_player = nullptr;
    
    if (class_name == "Warrior") {
        loaded_player = std::make_unique<Warrior>(name, max_health, damage, gold);
    } else if (class_name == "Mage") {
        loaded_player = std::make_unique<Mage>(name, max_health, damage, gold);
    } else if (class_name == "Archer") {
        loaded_player = std::make_unique<Archer>(name, max_health, damage, gold);
    } else if (class_name == "Rogue") {
        loaded_player = std::make_unique<Rogue>(name, max_health, damage, gold);
    } else {
        throw SaveLoadException("Unknown character class found in save file: " + class_name);
    }

    int health_to_reduce = max_health - health;
    if (health_to_reduce > 0) {
        loaded_player->takeDamage(health_to_reduce);
    }

    int item_count = 0;
    if (in >> item_count) {
        for (int i = 0; i < item_count; ++i) {
        }
    }

    Logger::getInstance().log("Game progress successfully loaded from: " + filename);
    return loaded_player;
}
