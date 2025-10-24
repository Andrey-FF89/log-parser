#ifndef LOG_PARSER_H
#define LOG_PARSER_H

#include <string>
#include <vector>
#include <map>

class LogParser {
public:
    // Конструктор, принимающий путь к файлу
    LogParser(const std::string& filename);
    
    // Основные методы
    int countLines() const;
    std::vector<std::string> search(const std::string& keyword) const;
    std::vector<std::string> filterByLevel(const std::string& level) const;
    std::map<std::string, int> getLevelStats() const;
    void printSummary() const;

private:
    std::string filename;
};

#endif