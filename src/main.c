#include "thread.h"
#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "list.h"

void f(int i) {
    printf("hello");
}


int main () {
    init_thread_system();
    tid_t tid = thread_create((func_t*)f,(void*)1);


    return (EXIT_SUCCESS);
}