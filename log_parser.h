#ifndef LOG_PARSER_H
#define LOG_PARSER_H

#include <string>
#include <vector>
#include <map>

class LogParser {
public:
    /*
     * Конструктор класса LogParser
     *
     * @param filename путь к файлу логов для анализа.
     */
    LogParser(const std::string& filename);
    
    /*
     * Подсчет общего количества строк в файле
     *
     * @return количество строк в файле или -1 в случае ошибки.
     */
    int countLines() const;

    /*
     * Поиск строк содержащих указанное ключевое слово
     *
     * @param keyword ключевое слово для поиска.
     * @return вектор строк содержащих ключевое слово.
     */
    std::vector<std::string> search(const std::string& keyword) const;

    /*
     * Фильтрация записей лога по уровню логирования
     *
     * @param level уровень логирования (INFO, WARN, ERROR).
     * @return вектор строк соответствующего уровня логирования.
     */
    std::vector<std::string> filterByLevel(const std::string& level) const;

    /*
     * Получение статистики по уровням логирования
     *
     * @return словарь с количеством записей для каждого уровня.
     */
    std::map<std::string, int> getLevelStats() const;

    /*
     * Вывод сводной информации по файлу логов
     */
    void printSummary() const;

    /*
     * Вывод статистики по временным меткам в логах
     */
    void printTimeStats() const;

private:
    std::string filename;
    
    /*
     * Извлечение всех дат из записей лога
     *
     * @return вектор строк с датами в формате YYYY-MM-DD.
     */
    std::vector<std::string> extractAllDates() const;
};

#endif