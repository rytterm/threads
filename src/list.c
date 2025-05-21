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


void list_remove(list* l, thread* t) {
    ASSERT(l != NULL);
    ASSERT(t != NULL);

    node* prev = NULL;
    node* curr = l->head;

    while (curr != NULL) {
        if (curr->t == t) {
            if (prev == NULL) {
                l->head = curr->next;
            } else {
                prev->next = curr->next;
            }

            if (curr == l->tail) {
                l->tail = prev;
            }

            free(curr);
            return;
        }

        prev = curr;
        curr = curr->next;
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