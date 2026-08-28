#ifndef TRAP_H
#define TRAP_H
#include <stdint.h>

void handle_trap(uintptr_t* reg, uintptr_t mepc);
#endif