# Компилятор и флаги
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
TARGET = log_parser
SOURCES = main.cpp log_parser.cpp
OBJECTS = $(SOURCES:.cpp=.o)

# Основная цель по умолчанию
all: $(TARGET)

# Сборка исполняемого файла
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

# Компиляция .cpp файлов в .o объектные файлы
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Отладочная сборка
debug: CXXFLAGS += -g -O0
debug: clean $(TARGET)

# Релизная сборка
release: CXXFLAGS += -O3 -DNDEBUG
release: clean $(TARGET)

# Запуск демонстрации
demo: $(TARGET)
	@echo "=== Запуск демонстрации ==="
	@./demo.sh

# Очистка проекта
clean:
	rm -f $(TARGET) $(OBJECTS) *.log

# Установка в систему (опционально)
install: $(TARGET)
	sudo cp $(TARGET) /usr/local/bin/
	@echo "Утилита установлена в /usr/local/bin/"

# Справка по целям
help:
	@echo "Доступные цели:"
	@echo "  all      - сборка проекта (по умолчанию)"
	@echo "  debug    - отладочная сборка"
	@echo "  release  - оптимизированная сборка"
	@echo "  demo     - запуск демонстрации"
	@echo "  clean    - очистка проекта"
	@echo "  install  - установка в систему"
	@echo "  help     - эта справка"

# Объявляем фейковые цели (не файлы)
.PHONY: all debug release demo clean install help