/*
 * main.c — Управление первым светодиодом на DE2-115 через GPIO2
 *
 * Адреса регистров gpio2 (из grmon > info sys):
 *   APB: 0x80000600 - 0x80000700
 *
 * Карта регистров grgpio:
 *   +0x00  Data Input Register        (чтение → вход)
 *   +0x04  Output Enable              (1 = выход, 0 = вход)
 *   +0x08  Data Output Register       (запись → выход)
 *
 * На плате DE2-115 gpio2 управляет зелёными светодиодами LEDG
 */

/* Базовый адрес gpio2 */
#define GPIO2_BASE  0x80000600

/* Смещения регистров */
#define GPIO_OE (*(volatile unsigned int *)(GPIO2_BASE + 0x04))
#define GPIO_DATA_OUT (*(volatile unsigned int *)(GPIO2_BASE + 0x08))

int main(void)
{
    /*
     * Шаг 1: Настраиваем пин 0 на ВЫХОД.
     * Записываем 1 в бит 0 регистра Output Enable.
     * Остальные биты = 0 (остаются входами).
     */
    GPIO_OE = 0x00000001;

    /*
     * Шаг 2: Подаём единицу на пин 0.
     * Светодиод LEDG[0] загорается.
     */
    GPIO_DATA_OUT = 0x00000001;

    /*
     * Шаг 3: Бесконечный цикл.
     * Без него процессор закончит программу
     */
    while (1) {
        /* ничего не делаем — светодиод горит */
    }

    return 0;  /* никогда не выполнится */
}
