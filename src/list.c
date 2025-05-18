#include "list.h"


void list_init(list* l) {
    l->head = NULL;
    l->tail = NULL;
}


void list_push_back(list* l, node* n) {
    ASSERT(l != NULL);
    if (l->tail == NULL) {
        l->head = n;
        l->tail = n;
    } else {
        l->tail->next = n;
        l->tail = n;
    }
}


void print_list(list* l) {
    ASSERT(l != NULL);
    node* tmp = l->head;
    while (tmp != NULL) {
        printf("%d", tmp->t->tid);
        if (tmp->next != NULL) printf(", ");
        tmp = tmp->next;
    }
    printf("\n");
}


node* gen_node(thread* t) {
    node* n = malloc(sizeof(node));
    n->t = t;
    n->next = NULL;
    return n;
}