#pragma once

void uart_init(void);
void uart_putc(char c);
void uart_puts(const char *s);
void uart_enable_rx_irq(void);

/* Phase-2 RX */
int uart_read(char *c);
