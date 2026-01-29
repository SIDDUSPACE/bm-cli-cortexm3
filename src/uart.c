#define USART1_BASE   0x40013800UL
#define USART1_SR     (*(volatile unsigned int *)(USART1_BASE + 0x00))
#define USART1_DR     (*(volatile unsigned int *)(USART1_BASE + 0x04))
#define USART1_CR1    (*(volatile unsigned int *)(USART1_BASE + 0x0C))

#define RX_BUF_SIZE 64

volatile char rx_buf[RX_BUF_SIZE];
volatile unsigned int rx_head = 0;
volatile unsigned int rx_tail = 0;

static void rx_push(char c)
{
    unsigned int next = (rx_head + 1) % RX_BUF_SIZE;
    if (next != rx_tail) {
        rx_buf[rx_head] = c;
        rx_head = next;
    }
}

int uart_rx_available(void)
{
    return rx_head != rx_tail;
}

char uart_getc_nonblock(void)
{
    if (rx_head == rx_tail)
        return 0;

    char c = rx_buf[rx_tail];
    rx_tail = (rx_tail + 1) % RX_BUF_SIZE;
    return c;
}

/* USART1 IRQ handler here */
void USART1_IRQHandler(void)
{
    if (USART1_SR & (1 << 5)) {  
        char c = (char)USART1_DR;
        rx_push(c);
    }
}
void uart_enable_rx_irq(void)
{
    USART1_CR1 |= (1 << 5); 
}
