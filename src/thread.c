#include "thread.h"


static inline size_t round_up_pow_two(size_t x) {
    x--;
    x |= x >> 1;
    x |= x >> 2;
    x |= x >> 4;
    x |= x >> 8;
    x |= x >> 16;
#if SIZE_MAX > 0xFFFFFFFF
    x |= x >> 32;
#endif
    return x + 1;
}

#define BASE_SIZE sizeof(thread) + STACK_SIZE
#define ALLOC_SIZE (round_up_pow_two(BASE_SIZE))

static thread* idle_thread;
static list thread_list;
static ctx* context;


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


    __asm__ volatile("mov %0, %%rsp" : : "r"(t->stack));


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
    thread* t = thread_current();

}


thread* thread_current(void) {
    thread* t = thread_running();

    ASSERT(t != NULL);
    ASSERT(t->magic == THREAD_MAGIC);

    t->func(t->aux);

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


