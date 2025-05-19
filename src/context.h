#ifndef _CONTEXT_H_
#define _CONTEXT_H_

#include <stdint.h>
#include "debug.h"



void ctx_switch(uint8_t*, uint8_t*);
void ctx_restore(uint8_t*) NORETURN;
void ctx_save(uint8_t*);


#endif