#include "uart.h"

static volatile unsigned int ticks = 0;

void SysTick_Handler(void)
{
    ticks++;
    if ((ticks % 1000) == 0) {
        uart_puts("[alive]\r\n");
    }
}
