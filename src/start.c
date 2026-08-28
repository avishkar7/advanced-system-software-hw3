#include "main.h"
#include "riscv.h"
#include "stdint.h"

extern void trap_entry();

void start() {

    // set M Exception Program Counter to main, for mret.
    // requires gcc -mcmodel=medany
    w_mepc((uint64_t)main);

    // setup trap_entry
    w_mtvec((uint64_t)trap_entry);

    // physical memory protection
    w_pmpcfg0(0xf);
    w_pmpaddr0(0xffffffffffffffff);

    // switch to supervisor mode and jump to main().
    asm volatile("mret");
}