#include <stdint.h>
#include "uart.h"

static volatile uint8_t *uart;

void uart_init() {
    uart = (uint8_t *)(void *) 0x10000000;
    uint32_t uart_freq = 1843200;
    uint32_t baud_rate = 115200;
    uint32_t divisor = uart_freq / (16 * baud_rate);
    uart[0x03] = 0x80;
    uart[0x00] = divisor & 0xff;
    uart[0x01] = (divisor >> 8) & 0xff;
    uart[0x03] = 0x08 | 0x03;
}

static int uart_putchar(int ch) {
    while ((uart[0x05] & 0x40) == 0)
        ;
    return uart[0x00] = ch & 0xff;
}

void uart_send(char c) { uart_putchar(c); }

void print_s(const char *s) {
    while (*s != '\0') {
        /* convert newline to carrige return + newline */
        if (*s == '\n') uart_send('\r');
        uart_send(*s++);
    }
}