#pragma once

#include <string>
#include <list>

class Logger final {
public:
    static Logger& getInstance() noexcept;

    void log(const std::string& message);
    void logError(const std::string& message);
    void print() const;
    void clear() noexcept;
    
    const std::list<std::string>& getHistory() const noexcept;

private:
    Logger() = default;
    ~Logger() = default;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    std::list<std::string> history_; 
};
