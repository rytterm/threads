#ifndef _LIST_H_
#define _LIST_H_

#include "thread.h"
#include <stdbool.h>
#include "debug.h"

typedef struct List {
    thread* t;
    struct List* next;
} list;

list* head;
list* tail;

void list_init(void);
void list_push_back(list*, thread*);
bool empty(list*);

#endif