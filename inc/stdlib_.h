#ifndef STDLIB_H
#define STDLIB_H

void exit_(){
    asm volatile("li t6, 1"); // We use t6 to store the ecall_id
    asm volatile("ecall");
}

static inline void yield_(){
    asm volatile("li t6, 2"); // We use t6 to store the ecall_id
    asm volatile("ecall"); 
}

#endif
