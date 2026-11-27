# =============================================
#  Makefile для сборки программы под LEON3
#  Плата: Terasic DE2-115
# =============================================

# --- Инструменты ---
CC      = sparc-gaisler-elf-gcc

# --- Папки ---
SRC_DIR   = src
BUILD_DIR = build

# --- Файлы ---
TARGET = $(BUILD_DIR)/gpio_led.elf
SRCS   = $(SRC_DIR)/main.c

# --- Флаги компиляции ---
#   -msoft-float     без аппаратного FPU (в конфиге CFG_FPU=0)
#   -O0              без оптимизации (для наглядной отладки)
#   -g               отладочные символы (для работы в grmon)
CFLAGS  = -msoft-float -O0 -g



# =============================================
#  Правила сборки
# =============================================

# Главная цель: собрать проект
all: $(BUILD_DIR) $(TARGET)

# Создать папку build, если её нет
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Скомпилировать исходники в ELF
$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRCS) -o $(TARGET)


# Очистка: удалить папку со сборкой
clean:
	rm -rf $(BUILD_DIR)

# Справка по доступным командам
help:
	@echo "Доступные цели:"
	@echo "  make all    - собрать проект (по умолчанию)"
	@echo "  make clean  - удалить папку со сборкой"
	@echo "  make help   - показать эту справку"

.PHONY: all clean
