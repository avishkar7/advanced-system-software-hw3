#include "uart.h"
#include "scheduler.h"

int main() {
    uart_init();
    print_s("Before scheduler_init\n");
    scheduler_init();
    print_s("Before ecall\n");

    // Calling the scheduler here by ecall
    asm volatile("ecall");
    print_s("After ecall\n");
    while (1)
        ;
    return 0;
}

