#ifndef _LIST_H_
#define _LIST_H_

#include "thread.h"
#include <stdbool.h>
#include "debug.h"

typedef struct Thread thread;

typedef struct Node {
    thread* t;
    struct Node* next;
} node;


typedef struct List {
    node* head;
    node* tail;
} list;


void list_init(list*);
void list_push_back(list*,node*);
void print_list(list*);
node* gen_node(thread*);

#endif