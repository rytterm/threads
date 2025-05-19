#include "thread.h"
#include <stdio.h>
#include <stdlib.h>
#include "debug.h"
#include "list.h"

void f(void* i) {
    float* fp = (float*)i;
    printf("hello the number is: %f",*fp);
}


void f2(int i) {
    printf("hello the number is: %d",i);
}

int main () {
    init_thread_system();
    float* i = malloc(sizeof(float)); 
    *i = 3.4f;


    tid_t tid = thread_create((func_t*)f,i);
    tid_t tid2 = thread_create((func_t*)f2,i);

    return (EXIT_SUCCESS);
}