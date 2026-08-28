#include "uart.h"
#include "stdlib_.h"

void process1(), process2(), process3();

void process1(){
    print_s("process1 is running\n");
    // TODO: call yield_() function here to yield the process
    // print a message to tell the process is starting again from the yield state
    yield_();
    print_s("process1 is back from yield\n");
    exit_();
}

void process2(){
    print_s("process2 is running\n");
    // TODO: call yield_() function here to yield the process
    // print a message to tell the process is starting again from the yield state
    yield_();
    print_s("process2 is back from yield\n");
    exit_();
}

void process3(){
    print_s("process3 is running\n");
    // TODO: call yield_() function here to yield the process
    // print a message to tell the process is starting again from the yield state
    yield_();
    print_s("process3 is back from yield\n");
    exit_();
}
