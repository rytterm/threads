#include "thread.h"
#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "list.h"


void p1(int i) {
    printf("Number for p1 is: %d\n",i);
}


void hello_world(void) {
    printf("Hello World!\n");
}

void third(bool b) {
    if (b) printf("true\n");
    else printf("false");
}


int main () {
    init_thread_system();

    thread* t1 = thread_create((func_t*)p1,(void*)1, 2);
    thread* t2 = thread_create((func_t*)hello_world, NULL, 10);
    thread* t3 = thread_create((func_t*)third,(void*)true, 15);
   
    scheduler();

    print_thread_list();

    return (EXIT_SUCCESS);
}