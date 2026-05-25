#include "SaveSystem.h"
#include "../Core/Exceptions.h" 
#include <fstream>

SaveSystem::SaveSystem(std::string saveFileName) 
    : m_saveFileName(std::move(saveFileName)) {}

void SaveSystem::saveGame(const std::unique_ptr<Character>& player) {
    if (!player) {
        throw SaveLoadException("Cannot save state: Player instance is null.");
    }

    std::ofstream outFile(m_saveFileName, std::ios::binary);
    if (!outFile) {
        throw SaveLoadException("Critical I/O error: Unable to open " + m_saveFileName + " for writing.");
    }
    
}

std::unique_ptr<Character> SaveSystem::loadGame() {
    std::ifstream inFile(m_saveFileName, std::ios::binary);
    if (!inFile) {
        throw SaveLoadException("Resource missing: Save file " + m_saveFileName + " could not be found.");
    }

    return nullptr; 
}
