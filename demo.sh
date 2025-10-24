#!/bin/bash

echo "=== Демонстрация работы Log Parser ==="
echo

# Проверяем, что программа скомпилирована
if [ ! -f "./log_parser" ]; then
    echo "Ошибка: программа log_parser не найдена. Сначала выполните 'make'"
    exit 1
fi

# Создаем тестовый лог-файл
cat > demo.log << EOF
2023-10-01 INFO: Application started
2023-10-01 INFO: Loading configuration  
2023-10-01 WARN: Using default settings
2023-10-01 INFO: Database connection established
2023-10-01 ERROR: Failed to load user data
2023-10-01 WARN: Retrying connection
2023-10-01 INFO: User session created
2023-10-01 ERROR: Permission denied
EOF

echo "Создан тестовый файл demo.log"
echo

# Демонстрация команд
echo "1. Подсчет строк:"
./log_parser demo.log --count
echo

echo "2. Поиск ошибок:"
./log_parser demo.log --search "ERROR"
echo

echo "3. Фильтрация по уровню:"
./log_parser demo.log --level WARN
echo

echo "4. Статистика:"
./log_parser demo.log --summary
echo

# Удаляем тестовый файл
rm -f demo.log
echo "Демонстрация завершена"