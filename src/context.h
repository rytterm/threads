#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include <stdint.h>


typedef struct Context {
    uintptr_t sp;
    uintptr_t pc;
} ctx;




#endif