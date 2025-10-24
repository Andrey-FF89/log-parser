#include "log_parser.h"
#include <fstream>
#include <iostream>
#include <map>

LogParser::LogParser(const std::string& filename) : filename(filename) {
    // Конструктор теперь просто сохраняет имя файла
}

int LogParser::countLines() const {
    std::ifstream file(filename);  // открываем файл для чтения
    
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return -1;  // возвращаем -1 при ошибке
    }
    
    int count = 0;
    std::string line;
    
    while (std::getline(file, line)) {  // читаем файл построчно
        count++;  // увеличиваем счетчик для каждой строки
    }
    
    file.close();  // закрываем файл
    return count;  // возвращаем результат
}

std::vector<std::string> LogParser::search(const std::string& keyword) const {
    std::vector<std::string> results;  // вектор для найденных строк
    std::ifstream file(filename);      // открываем файл
    
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return results;  // возвращаем пустой вектор при ошибке
    }
    
    std::string line;
    while (std::getline(file, line)) {  // читаем файл построчно
        // Если ключевое слово найдено в строке
        if (line.find(keyword) != std::string::npos) {
            results.push_back(line);  // добавляем строку в результаты
        }
    }
    
    file.close();
    return results;
}

std::vector<std::string> LogParser::filterByLevel(const std::string& level) const {
    std::vector<std::string> results;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return results;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        // Ищем уровень логгирования в строке
        // Ищем паттерны типа "INFO:", "ERROR:", "WARN:"
        std::string levelPattern = level + ":";
        if (line.find(levelPattern) != std::string::npos) {
            results.push_back(line);
        }
    }
    
    file.close();
    return results;
}

std::map<std::string, int> LogParser::getLevelStats() const {
    std::map<std::string, int> stats = {{"INFO", 0}, {"WARN", 0}, {"ERROR", 0}};
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        return stats;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("ERROR:") != std::string::npos) {
            stats["ERROR"]++;
        } else if (line.find("WARN:") != std::string::npos) {
            stats["WARN"]++;
        } else if (line.find("INFO:") != std::string::npos) {
            stats["INFO"]++;
        }
    }
    
    file.close();
    return stats;
}

// Новая функция: вывод сводки по файлу
void LogParser::printSummary() const {
    int totalLines = countLines();
    auto stats = getLevelStats();
    
    std::cout << "=== Log File Summary ===" << std::endl;
    std::cout << "File: " << filename << std::endl;
    std::cout << "Total lines: " << totalLines << std::endl;
    std::cout << "INFO: " << stats["INFO"] << " lines" << std::endl;
    std::cout << "WARN: " << stats["WARN"] << " lines" << std::endl;
    std::cout << "ERROR: " << stats["ERROR"] << " lines" << std::endl;
    
    int other = totalLines - (stats["INFO"] + stats["WARN"] + stats["ERROR"]);
    if (other > 0) {
        std::cout << "Other: " << other << " lines" << std::endl;
    }
}