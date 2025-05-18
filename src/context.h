#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include <stdint.h>
#include "debug.h"


typedef struct Context {
    uintptr_t sp;
    uintptr_t pc;
} ctx;



void ctx_init(ctx*, uint8_t*);
void ctx_restore(ctx*) NORETURN;
void ctx_save(ctx*);


#endif