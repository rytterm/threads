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
    ASSERT(func != NULL);

    allocate_tid(t);
    t->magic = THREAD_MAGIC;
    t->idle = true;
    t->func = func;
    t->aux = aux;
    t->status = THREAD_BLOCKED;
    t->stack = (uint8_t*)t + ALLOC_SIZE;

    ASSERT(t->stack != NULL);

    t->stack -= sizeof(thread*);
    *((thread**)t->stack) = t;
    t->stack -= sizeof(void*);
    *((void**)t->stack) = thread_entry;


    list_push_back(&thread_list,gen_node(t));
    thread_ready(t);
    
    ctx_save(t->stack);

    return t->tid;
}


void thread_ready(thread* t) {
    ASSERT(t != NULL);
    ASSERT(t->status == THREAD_BLOCKED);

    t->status = THREAD_READY;
    scheduler();
}


void thread_yield(void) {
    //thread* t = thread_current();
    //t->status = THREAD_RUNNING;
    //ctx_switch(t->stack,idle_thread->stack);
    ctx_restore(idle_thread->stack);
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

    list_remove(&thread_list,gen_node(t));
    //free(t);

    scheduler();

    __builtin_unreachable();

}


void scheduler(void) {
    node* head = thread_list.head;
    if (thread_list.head == thread_list.tail) {
        idle_thread = head->t;
    } else {
        idle_thread = head->next->t;
    }
    ASSERT(idle_thread != NULL);
    thread_yield();
}