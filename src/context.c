#include "context.h"


void ctx_switch(uint8_t* sold, uint8_t* snew) {
    if (sold != NULL) {
        ctx_save(sold);
    }
    ctx_restore(snew);
}


void NORETURN ctx_restore(uint8_t* stack) {
    ASSERT(stack != NULL);

    __asm__ volatile(
        "mov %0, %%rsp  \n" 
        "ret            \n"
        :
        : "r" (stack)
        : "memory"
    );    
    __builtin_unreachable();
}

void ctx_save(uint8_t* stack) {
    __asm__ volatile("mov %%rsp, %0" : "=r" (stack));
}