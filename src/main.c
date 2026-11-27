/*
 * main.c — Светодиоды отражают состояние переключателей на DE2-115
 *
 * Аппаратная конфигурация (из leon3mp.vhd и grmon > info sys):
 *   gpio1  APB: 0x80000500 - 0x80000600  → переключатели SW0..SW16 (18 бит)
 *   gpio2  APB: 0x80000600 - 0x80000700  → светодиоды LEDG0..LEDG8 (8 бит)
 *
 * Карта регистров grgpio:
 *   +0x00  Data Input Register        (чтение → вход)
 *   +0x04  Output Enable              (1 = выход, 0 = вход)
 *   +0x08  Data Output Register       (запись → выход)
 *
 * Логика работы: в бесконечном цикле читаем переключатели
 * и записываем младшие 8 бит в регистр вывода светодиодов
 */

/* Базовые адреса блоков */
#define GPIO1_BASE      0x80000500    /* переключатели */
#define GPIO2_BASE      0x80000600    /* светодиоды    */

/* Регистры gpio1 — только чтение */
#define GPIO1_DATA_IN   (*(volatile unsigned int *)(GPIO1_BASE + 0x00))

/* Регистры gpio2 — настройка и вывод */
#define GPIO2_OE        (*(volatile unsigned int *)(GPIO2_BASE + 0x04))
#define GPIO2_DATA_OUT  (*(volatile unsigned int *)(GPIO2_BASE + 0x08))

/* Количество светодиодов и маска: 8 единиц = 0xFF */
#define LED_COUNT       8
#define LED_MASK        ((1u << LED_COUNT) - 1u)


int main(void)
{
    unsigned int sw;

    /*
     * Шаг 1: Настраиваем все 8 пинов gpio2 на ВЫХОД.
     */
    GPIO2_OE = LED_MASK;

    /* Шаг 2: Гасим все светодиоды в начальный момент */
    GPIO2_DATA_OUT = 0x00000000;

    /* Шаг 3: Основной цикл — постоянное отражение состояния */
    while (1) {
        /* Читаем все 18 переключателей одним 32-битным обращением */
        sw = GPIO1_DATA_IN;

        /*
         * Отбрасываем старшие биты: переключателей 18,
         * а светодиодов только 8. Операция AND с маской
         * оставляет младшие 8 бит, остальные обнуляет.
         */
        GPIO2_DATA_OUT = sw & LED_MASK;
    }

    return 0;  /* никогда не выполнится */
}
