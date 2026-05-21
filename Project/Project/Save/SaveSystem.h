#pragma once

#include "../Characters/Character.h"
#include "../Characters/CharacterFactory.h"
#include <string>
#include <memory>

class SaveSystem final {
public:
    static void saveGame(const std::string& filename, const Character& player);
    
    static std::unique_ptr<Character> loadGame(const std::string& filename, CharacterFactory& factory);
};
