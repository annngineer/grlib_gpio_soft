/*
 * main.c — Управление первым светодиодом на DE2-115 через GPIO2
 *
 * Адреса регистров gpio2 (из grmon > info sys):
 *   APB: 0x80000600 - 0x80000700
 *
 * Карта регистров grgpio:
 *   +0x00  Data Input Register  (чтение → вход)
 *   +0x04  Output Enable        (1 = выход, 0 = вход)
 *   +0x08  Data Output Register (запись → выход)
 *
 * На плате DE2-115 gpio2 управляет зелёными светодиодами LEDG
 */

/* Базовый адрес gpio2 */
#define GPIO2_BASE  0x80000600

/* Смещения регистров */
#define GPIO_OE (*(volatile unsigned int *)(GPIO2_BASE + 0x04))
#define GPIO_DATA_OUT (*(volatile unsigned int *)(GPIO2_BASE + 0x08))

/* Количество светодиодов на gpio2 */
#define LED_COUNT 8


static void delay(volatile unsigned int n)
{
    while (n--) {
    }
}

int main(void)
{
    unsigned int led;

    /*
     * Шаг 1: Настраиваем все 8 пинов на ВЫХОД.
     */
    GPIO_OE = 0xFF;

    /* Шаг 2: начальное состояние — горит только LEDG[0] */
    led = 0x00000001;

    /* Шаг 3: бесконечный цикл сдвига */
    while (1) {
        GPIO_DATA_OUT = led;      /* выставить текущую позицию */
        delay(500000);            /* подождать */

        led <<= 1;                /* сдвинуть единицу влево */  

        /*
         * Если единица ушла за пределы 8 разрядов —
         * вернуть её в начало (замкнуть кольцо).
         */
        if (led & (1u << LED_COUNT)) {
            led = 0x1;
        }
    }

    return 0;  /* никогда не выполнится */
}
