#include "thread.h"



static thread* idle_thread;




tid_t thread_create(func_t* func, void* aux) {
    thread* t = malloc(sizeof(thread));
    ASSERT(t != NULL);

    allocate_tid(t);
    t->magic = THREAD_MAGIC;
    t->idle = 0;
    t->func = func;
    t->aux = aux;
    t->status = THREAD_BLOCKED;
    t->stack = (uint8_t*)t + STACK_SIZE;

    ASSERT(t->stack != NULL);
    ASSERT(t->func != NULL);


    idle_thread = thread_current();

    return t->tid;
}


void thread_ready(thread* t) {
    ASSERT(t != NULL);
    ASSERT(t->status == THREAD_BLOCKED);
    
}


void thread_yield(void) {
    thread* t = thread_current();

}


thread* thread_current(void) {
    thread* t = thread_running();

    ASSERT(t != NULL);
    ASSERT(t->magic == THREAD_MAGIC);

    return t;
}



thread* thread_running(void) {
    uint8_t *rsp;
    __asm__ volatile("mov %%rsp, %0" : "=r" (rsp));
    return (void *) ((uintptr_t) rsp & ~PGMASK);
}


void allocate_tid(thread* t) {
    static int next = 1;
    t->tid = next++;
}


