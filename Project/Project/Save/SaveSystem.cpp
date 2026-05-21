#include "SaveSystem.h"
#include "Exceptions.h"
#include <fstream>
#include <iostream>

class Character {
public:
    virtual ~Character() = default;
};

SaveSystem::SaveSystem(std::string saveFileName) 
    : m_saveFileName(std::move(saveFileName)) {}

void SaveSystem::saveGame(const std::unique_ptr<Character>& player) {
    if (!player) {
        throw SaveLoadException("Cannot save a non-existing character!");
    }

    std::ofstream outFile(m_saveFileName, std::ios::binary);
    if (!outFile) {
        throw SaveLoadException("Failed to open file for saving: " + m_saveFileName);
    }
    
    std::cout << "Game successfully saved to " << m_saveFileName << "\n";
}

std::unique_ptr<Character> SaveSystem::loadGame() {
    std::ifstream inFile(m_saveFileName, std::ios::binary);
    if (!inFile) {
        throw SaveLoadException("Failed to open save file: " + m_saveFileName);
    }
    
    std::cout << "Game successfully loaded from " << m_saveFileName << "\n";
    
    return std::make_unique<Character>();
}
