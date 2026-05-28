#ifndef SAVESYSTEM_H
#define SAVESYSTEM_H

#include <string>
#include <memory>

class Character;

class SaveSystem {
private:
    std::string m_saveFileName;

public:
    explicit SaveSystem(std::string saveFileName = "save.dat");
    ~SaveSystem() = default;

    void saveGame(const std::unique_ptr<Character>& player);
    std::unique_ptr<Character> loadGame();
};

#endif 
