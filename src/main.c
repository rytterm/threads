#include "thread.h"
#include <stdio.h>
#include <stdlib.h>
#include "debug.h"

void f(int i) {
    printf("hello");
}


int main () {

    tid_t tid = thread_create((func_t*)f,(void*)1);

    return (EXIT_SUCCESS);
}