#ifndef UART_H
#define UART_H

#include <stdint.h>

void uart_init();
void uart_send(char c);
void print_s(const char* s);

#endif /* ifndef UART_H */
