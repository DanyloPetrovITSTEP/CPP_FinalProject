#include "SaveSystem.h"
#include "../Core/Exceptions.h"
#include "../Core/Logger.h"
#include <fstream>

void SaveSystem::saveGame(const std::string& filename, const Character& player) {
    std::ofstream out(filename);
    if (!out.is_open()) {
        throw SaveLoadException("Critical: Unable to open file for writing serialization data: " + filename);
    }

    out << player.getClassName() << "\n";
    out << player.getName() << "\n";
    out << player.getHealth() << "\n";
    out << player.getMaxHealth() << "\n";
    out << player.getDamage() << "\n";
    out << player.getGold() << "\n";
    out << 0 << "\n"; 

    Logger::getInstance().log("Save state written successfully to target file: " + filename);
}

std::unique_ptr<Character> SaveSystem::loadGame(const std::string& filename, CharacterFactory& factory) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        throw SaveLoadException("Critical: Target save state file does not exist: " + filename);
    }

    std::string class_name, name;
    int health = 0, max_health = 0, damage = 0, gold = 0;

    if (!(in >> class_name >> name >> health >> max_health >> damage >> gold)) {
        throw SaveLoadException("Data stream failure: Save file structure is corrupted!");
    }
    
    auto loaded_player = factory.createCharacter(class_name, name, health, max_health, damage, gold);
    
    if (!loaded_player) {
        throw SaveLoadException("Factory processing failed: Unknown or unregistered character class token: " + class_name);
    }

    auto health_to_reduce = max_health - health;
    if (health_to_reduce > 0) {
        loaded_player->takeDamage(health_to_reduce);
    }

    int item_count = 0;
    if (in >> item_count) {
        for (int i = 0; i < item_count; ++i) {
        }
    }

    Logger::getInstance().log("Player session completely reconstructed from save state file.");
    return loaded_player;
}
