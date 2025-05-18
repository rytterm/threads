#include "thread.h"




static thread* idle_thread;
static list thread_list;


void init_thread_system(void) {
    list_init(&thread_list);
}


tid_t thread_create(func_t* func, void* aux) {

    void* memory;
    posix_memalign(&memory, ALLOC_SIZE, ALLOC_SIZE);
    
    thread* t = (thread*)memory;
    ASSERT(t != NULL);

    allocate_tid(t);
    t->magic = THREAD_MAGIC;
    t->idle = 0;
    t->func = func;
    t->aux = aux;
    t->status = THREAD_BLOCKED;
    t->stack = (uint8_t*)t + ALLOC_SIZE;
    t->stack -= sizeof(thread*);
    *((thread**)t->stack) = t;
    t->stack -= sizeof(void*);
    *((void**)t->stack) = thread_entry;


    ctx_init(&t->context,t->stack);
    ctx_restore(&t->context);


    ASSERT(t->stack != NULL);
    ASSERT(t->func != NULL);




    //idle_thread = t;

    //list_push_back(&thread_list, gen_node(idle_thread));

    thread* tmp = thread_current();
    
    //print_list(&thread_list);

    return t->tid;
}


void thread_ready(thread* t) {
    ASSERT(t != NULL);
    ASSERT(t->status == THREAD_BLOCKED);
    
}


void thread_yield(void) {
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
    return (thread*) ((uintptr_t)rsp & ~(ALLOC_SIZE - 1));

}


void allocate_tid(thread* t) {
    static int next = 1;
    t->tid = next++;
}


void NORETURN thread_entry(void) {
    thread* t = thread_current();
    ASSERT(t != NULL);
    ASSERT(t->func != NULL);
    ASSERT(t->aux != NULL);
    t->func(t->aux);
    thread_exit();
    __builtin_unreachable();
}

void NORETURN thread_exit(void) {
    thread* t = thread_current();
    ASSERT(t != NULL);
    t->status = THREAD_DYING;
    free(t);

    exit(0);


    __builtin_unreachable();

}