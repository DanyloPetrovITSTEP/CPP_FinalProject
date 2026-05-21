#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class GameException : public std::runtime_error {
public:
    explicit GameException(const std::string& message) : std::runtime_error(message) {}
};

class SaveLoadException : public GameException {
public:
    explicit SaveLoadException(const std::string& message) : GameException("Save/Load Error: " + message) {}
};

class InventoryException : public GameException {
public:
    explicit InventoryException(const std::string& message) : GameException("Inventory Error: " + message) {}
};

class BattleException : public GameException {
public:
    explicit BattleException(const std::string& message) : GameException("Battle Error: " + message) {}
};

class ShopException : public GameException {
public:
    explicit ShopException(const std::string& message) : GameException("Shop Error: " + message) {}
};

#endif 
