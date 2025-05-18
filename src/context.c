#include "context.h"


void ctx_init(ctx* context, uint8_t* stack) {
    ASSERT(stack != NULL);
    ASSERT(context != NULL);
    context->sp = (uintptr_t)stack;
}

void NORETURN ctx_restore(ctx* context) {
    __asm__ volatile(
        "mov %0, %%rsp  \n" 
        "ret            \n"
        :
        : "r" (context->sp)
        : "memory"
    );    
    __builtin_unreachable();
}

void ctx_save(ctx* context) {
    __asm__ volatile("mov %%rsp, %0" : "=r" (context->sp));
}