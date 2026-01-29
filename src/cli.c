static char cmd_buf[32];
static int cmd_len = 0;

void cli_poll(void)
{
    while (uart_rx_available()) {
        char c = uart_getc_nonblock();

        if (c == '\r' || c == '\n') {
            cmd_buf[cmd_len] = 0;
            uart_puts("CMD: ");
            uart_puts(cmd_buf);
            uart_puts("\r\n");
            cmd_len = 0;
        }
        else if (cmd_len < (int)(sizeof(cmd_buf) - 1)) {
            cmd_buf[cmd_len++] = c;
        }
    }
}
