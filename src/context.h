#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include <stdint.h>
#include "thread.h"

typedef struct Context {
    uintptr_t sp;
    uintptr_t pc;
} ctx;

typedef struct Thread thread;


void ctx_init(thread*,ctx*);



#endif