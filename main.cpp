#include <iostream>
#include <string>
#include "log_parser.h"

// Цветные коды для терминала
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_RESET   "\033[0m"

/*
 * Вывод справки по использованию программы
 */
void printUsage() {
    std::cout << "Usage: ./log_parser <file.log> <command> [argument]\n";
    std::cout << "Commands:\n";
    std::cout << "  --count                    Count total lines\n";
    std::cout << "  --search <keyword>         Search for keyword\n";
    std::cout << "  --level <INFO|WARN|ERROR>  Filter by log level\n";
    std::cout << "  --summary                  Show file summary with statistics\n";
    std::cout << "  --timestats                Show time statistics\n";
}

/*
 * Вывод строки лога с цветовым оформлением в зависимости от уровня
 *
 * @param line строка лога для вывода.
 */
void printColoredLevel(const std::string& line) {
    if (line.find("ERROR:") != std::string::npos) {
        std::cout << COLOR_RED << line << COLOR_RESET << std::endl;
    } else if (line.find("WARN:") != std::string::npos) {
        std::cout << COLOR_YELLOW << line << COLOR_RESET << std::endl;
    } else if (line.find("INFO:") != std::string::npos) {
        std::cout << COLOR_GREEN << line << COLOR_RESET << std::endl;
    } else {
        std::cout << line << std::endl;
    }
}

/*
 * Главная функция программы - обработка аргументов командной строки
 * и выполнение соответствующих команд
 *
 * @param argc количество аргументов командной строки.
 * @param argv массив аргументов командной строки.
 * @return код завершения программы (0 - успех, 1 - ошибка).
 */
int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << COLOR_RED << "Error: Too few arguments!" << COLOR_RESET << std::endl;
        printUsage();
        return 1;
    }
    
    std::string filename = argv[1];
    std::string command = argv[2];
    
    LogParser parser(filename);
    
    if (command == "--count") {
        int lineCount = parser.countLines();
        if (lineCount >= 0) {
            std::cout << COLOR_BLUE << "Total lines in " << filename << ": " 
                      << COLOR_GREEN << lineCount << COLOR_RESET << std::endl;
        }
    }
    else if (command == "--search") {
        if (argc < 4) {
            std::cerr << COLOR_RED << "Error: --search requires a keyword argument" << COLOR_RESET << std::endl;
            printUsage();
            return 1;
        }
        std::string keyword = argv[3];
        auto results = parser.search(keyword);
        
        std::cout << COLOR_BLUE << "Found " << results.size() 
                  << " lines with '" << keyword << "':" << COLOR_RESET << std::endl;
        for (const auto& line : results) {
            printColoredLevel(line);
        }
    }
    else if (command == "--level") {
        if (argc < 4) {
            std::cerr << COLOR_RED << "Error: --level requires a level argument (INFO, WARN, ERROR)" << COLOR_RESET << std::endl;
            printUsage();
            return 1;
        }
        std::string level = argv[3];
        auto results = parser.filterByLevel(level);
        
        std::cout << COLOR_BLUE << "Found " << results.size() 
                  << " lines with level '" << level << "':" << COLOR_RESET << std::endl;
        for (const auto& line : results) {
            printColoredLevel(line);
        }
    }
    else if (command == "--summary") {
        parser.printSummary();
    }
    else if (command == "--timestats") {
        parser.printTimeStats();
    }
    else {
        std::cerr << COLOR_RED << "Unknown command: " << command << COLOR_RESET << std::endl;
        printUsage();
        return 1;
    }
    
    return 0;
}