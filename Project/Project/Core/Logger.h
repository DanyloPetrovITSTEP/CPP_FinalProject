#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>
#include <string_view>

class Logger {
private:
    std::vector<std::string> m_history;

public:
    Logger() = default;
    ~Logger() = default;

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    void log(std::string_view message);
    void print() const;
    void clear();
    
    const std::vector<std::string>& getHistory() const;
};

#endif 
