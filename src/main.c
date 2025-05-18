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
    func_t* func = (func_t*)f;
    int i = 1;
    void* aux = (void*)i;

    tid_t tid = thread_create(func,aux);

    return (EXIT_SUCCESS);
}