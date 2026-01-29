#include "uart.h"
#include "cli.h"
#include "systick.h"

/* NVIC enable register for IRQs 32–63 */
#define NVIC_ISER1 (*(volatile unsigned int *)0xE000E104)

int main(void)
{
    /* Initialize peripherals */
    uart_init();
    systick_init();

    /* Enable USART1 interrupt (IRQ37 → bit 5 of ISER1) */
    NVIC_ISER1 = (1 << 5);
    uart_enable_rx_irq();   /* <-- abstracted, not raw register */

    /* Banner + prompt */
    uart_puts("\r\nBare-Metal CLI (Renode)\r\n");
    uart_puts("> ");

    while (1) {
        cli_poll();        /* RX parser (non-blocking) */
        systick_poll();    /* prints [alive] periodically */
    }
}
