#include "list.h"


void list_init(void) {
    head = NULL;
    tail = NULL;
}


void list_push_back(list* l, thread* t) {
    l->t = t;
    if (empty(l)) {
        head = l;
        tail = l;
        l->next = tail;
    } else {
        tail = l;
        l->next = tail;
    }
}



bool empty(list* l) {
    return head == NULL && tail == NULL;
}