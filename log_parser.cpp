#include "log_parser.h"
#include <fstream>
#include <iostream>
#include <map>
#include <algorithm>

/*
 * Конструктор класса LogParser
 *
 * @param filename путь к файлу логов для анализа.
 */
LogParser::LogParser(const std::string& filename) : filename(filename) {
}

/*
 * Подсчет общего количества строк в файле
 *
 * @return количество строк в файле или -1 в случае ошибки.
 */
int LogParser::countLines() const {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return -1;
    }
    
    int count = 0;
    std::string line;
    
    while (std::getline(file, line)) {
        count++;
    }
    
    file.close();
    return count;
}

/*
 * Поиск строк содержащих указанное ключевое слово
 *
 * @param keyword ключевое слово для поиска.
 * @return вектор строк содержащих ключевое слово.
 */
std::vector<std::string> LogParser::search(const std::string& keyword) const {
    std::vector<std::string> results;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return results;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.find(keyword) != std::string::npos) {
            results.push_back(line);
        }
    }
    
    file.close();
    return results;
}

/*
 * Фильтрация записей лога по уровню логирования
 *
 * @param level уровень логирования (INFO, WARN, ERROR).
 * @return вектор строк соответствующего уровня логирования.
 */
std::vector<std::string> LogParser::filterByLevel(const std::string& level) const {
    std::vector<std::string> results;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return results;
    }
    
    std::string line;
    std::string levelPattern = level + ":";
    
    while (std::getline(file, line)) {
        if (line.find(levelPattern) != std::string::npos) {
            results.push_back(line);
        }
    }
    
    file.close();
    return results;
}

/*
 * Получение статистики по уровням логирования
 *
 * @return словарь с количеством записей для каждого уровня.
 */
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

/*
 * Вывод сводной информации по файлу логов
 */
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

/*
 * Извлечение всех дат из записей лога
 *
 * @return вектор строк с датами в формате YYYY-MM-DD.
 */
std::vector<std::string> LogParser::extractAllDates() const {
    std::vector<std::string> dates;
    std::ifstream file(filename);
    
    if (!file.is_open()) return dates;
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.length() >= 10) {
            std::string date = line.substr(0, 10);
            if (date[4] == '-' && date[7] == '-') {
                dates.push_back(date);
            }
        }
    }
    
    file.close();
    return dates;
}

/*
 * Вывод статистики по временным меткам в логах
 */
void LogParser::printTimeStats() const {
    auto dates = extractAllDates();
    
    if (dates.empty()) {
        std::cout << "No valid dates found in log file" << std::endl;
        return;
    }
    
    std::string minDate = *std::min_element(dates.begin(), dates.end());
    std::string maxDate = *std::max_element(dates.begin(), dates.end());
    
    std::cout << "=== Time Statistics ===" << std::endl;
    std::cout << "Earliest date: " << minDate << std::endl;
    std::cout << "Latest date:   " << maxDate << std::endl;
    std::cout << "Period:        " << minDate << " to " << maxDate << std::endl;
}