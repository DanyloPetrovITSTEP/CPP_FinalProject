#include "Logger.h"
#include <iostream>

void Logger::log(std::string_view message) {
    m_history.emplace_back(message);
}

void Logger::print() const {
    std::cout << "\n--- GAME LOG HISTORY ---\n";
    if (m_history.empty()) {
        std::cout << "[Log is empty]\n";
        return;
    }
    
    for (auto it = m_history.cbegin(); it != m_history.cend(); ++it) {
        std::cout << *it << "\n";
    }
    std::cout << "------------------------\n";
}

void Logger::clear() {
    m_history.clear();
}

const std::vector<std::string>& Logger::getHistory() const {
    return m_history;
}
