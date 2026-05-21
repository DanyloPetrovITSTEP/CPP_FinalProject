#include "Logger.h"
#include <iostream>
#include <algorithm>
#include <iterator>

Logger& Logger::getInstance() noexcept {
    static Logger instance;
    return instance;
}

void Logger::log(const std::string& message) {
    history_.emplace_back("[INFO] " + message);
}

void Logger::logError(const std::string& message) {
    history_.emplace_back("[ERROR] " + message);
}

void Logger::print() const {
    std::cout << "\n=== SYSTEM EVENT HISTORY ===" << std::endl;
    if (history_.empty()) {
        std::cout << "[Log history is completely empty]" << std::endl;
        return;
    }
    
    std::copy(history_.cbegin(), history_.cend(), std::ostream_iterator<std::string>(std::cout, "\n"));
    std::cout << "============================" << std::endl;
}

void Logger::clear() noexcept {
    history_.clear();
}

const std::list<std::string>& Logger::getHistory() const noexcept {
    return history_;
}
