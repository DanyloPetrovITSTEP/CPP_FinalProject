#ifndef SAVESYSTEM_H
#define SAVESYSTEM_H

#include "../Characters/Character.h"
#include <string>
#include <memory>

class SaveSystem {
public:
    static void saveGame(const std::string& filename, const Character& player);
    
    static std::unique_ptr<Character> loadGame(const std::string& filename);
};

#endif 
