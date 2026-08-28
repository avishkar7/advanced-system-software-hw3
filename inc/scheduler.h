#ifndef SCHEDULER_H
#define SCHEDULER_H

extern uint8_t state1, state2, state3;
extern uintptr_t addr1, addr2, addr3;

void scheduler_init();
void schedule();

#endif