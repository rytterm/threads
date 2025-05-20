#ifndef _SWITCH_H_
#define _SWITCH_H_


#include <stdint.h>
#include "debug.h"

void NORETURN ctx_restore(uint8_t**);
void ctx_save(uint8_t**);
void ctx_switch(uint8_t**, uint8_t**);


#endif