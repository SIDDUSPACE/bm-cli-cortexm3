#include "uart.h"
#include "cli.h"
#include "systick.h"

#define NVIC_ISER1 (*(volatile unsigned int *)0xE000E104)

int main(void)
{
    uart_init();
    systick_init();
    NVIC_ISER1 = (1 << 5);
    uart_enable_rx_irq();  
    uart_puts("\r\nBare-Metal CLI (Renode)\r\n");
    uart_puts("> ");
    while (1) {
        cli_poll();        
        systick_poll();    
    }
}
