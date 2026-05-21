#pragma once

#include <stdexcept>
#include <string>

class GameException : public std::runtime_error {
public:
    explicit GameException(const std::string& message) : std::runtime_error(message) {}
    virtual ~GameException() = default;
};

class SaveLoadException final : public GameException {
public:
    explicit SaveLoadException(const std::string& message) : GameException("Save/Load Subsystem Error: " + message) {}
};

class InvalidMenuChoiceException final : public GameException {
public:
    explicit InvalidMenuChoiceException(const std::string& message) : GameException("UI/Menu Error: " + message) {}
};
