#include <stdint.h>
#include "processes.h"
#include "riscv.h"
#include "uart.h"

uint8_t state1, state2, state3;
uintptr_t addr1, addr2, addr3, ret_addr;
uint8_t ecall_id, proc;

void scheduler_init() {
    state1 = 0;
    state2 = 0;
    state3 = 0;
    addr1 = (uintptr_t)process1;
    addr2 = (uintptr_t)process2;
    addr3 = (uintptr_t)process3;
    ecall_id = 0;
    proc = 0;
}

void schedule(){
    // print_s("Inside scheduler\n");

    // retrieve the ecall_id
    asm volatile("mv %0, t6" : "=r" (ecall_id));
    // if the previous ecall was from exit_(), change the corresponding state to 1 
    //three status variables: state1, state2, and state3
    /* State Variable Value
    0 The process is ready to run
    1 The process has terminated
    2 The process is in the yield state
    */
    if(ecall_id == 1 && proc == 1) state1 = 1;
    else if(ecall_id == 1 && proc == 2) state2 = 1;
    else if(ecall_id == 1 && proc == 3) state3 = 1;

    // TODO: if the previous ecall was from yield_(), change the corresponding state to 2
    // and store the address right after the yield_() is called to resume the proc later
    if(ecall_id == 2){
        asm volatile("csrr %0, mepc" : "=r" (ret_addr));
        ret_addr += 4;
        if(proc == 1){
            state1 = 2;
            addr1 = ret_addr;
        } else if(proc == 2){
            state2 = 2;
            addr2 = ret_addr;
        } else if(proc == 3){
            state3 = 2;
            addr3 = ret_addr;
        }
    }

    // if all the processes are done, enter the infinite loop
    if(state1 == 1 && state2 == 1 && state3 == 1){
        print_s("All done.\n");
        while (1)
            ;
        return;
    }
	
	// TODO: if the process is not yet finished, set the destination addr in mepc for the mret instruction in trap_entry.s
    // if there are both ready and yield state processes, ready state processes have higher priority to be executed
    if (state1 == 0) {
        proc = 1;
        w_mepc(addr1);
    } else if (state2 == 0) {
        proc = 2;
        w_mepc(addr2);
    } else if (state3 == 0) {
        proc = 3;
        w_mepc(addr3);
    } else if (state1 == 2) {
        proc = 1;
        w_mepc(addr1);
    } else if (state2 == 2) {
        proc = 2;
        w_mepc(addr2);
    } else if (state3 == 2) {
        proc = 3;
        w_mepc(addr3);
    }

}
