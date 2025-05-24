#include "thread.h"



static thread* idle_thread;
static list thread_list;
static uint8_t* main_stack = NULL;


void init_thread_system(void) {
    list_init(&thread_list);
}


thread* thread_create(func_t* func, void* aux, int priority) {

    void* memory;
    posix_memalign(&memory, ALLOC_SIZE, ALLOC_SIZE);
    
    thread* t = (thread*)memory;
    ASSERT(t != NULL);
    ASSERT(func != NULL);

    allocate_tid(t);
    t->magic = THREAD_MAGIC;
    t->func = func;
    t->aux = aux;
    t->priority = priority;
    t->status = THREAD_BLOCKED;
    t->stack = (uint8_t*)t + ALLOC_SIZE;

    ASSERT(t->stack != NULL);

    t->stack -= sizeof(void*);
    *((void**)t->stack) = thread_entry;

    t->idle_time = time(NULL);
    
    thread_ready(t);

    return t;
}


void thread_ready(thread* t) {
    ASSERT(t != NULL);
    ASSERT(t->status == THREAD_BLOCKED);

    t->status = THREAD_READY;

    list_push_back(&thread_list,gen_node(t));
}


void thread_yield(void) {
    for (;;);
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
    ASSERT(t->func != NULL);
    t->func(t->aux);
    thread_exit();
    __builtin_unreachable();
}

void NORETURN thread_exit(void) {
    thread* t = thread_current();

    t->status = THREAD_DYING;  
    list_remove(&thread_list,t); 
    ctx_restore(&main_stack);
    __builtin_unreachable();

    free(t);
}


void update_prio(void) {
    node* tmp = thread_list.head;
    while (tmp != NULL) {
        tmp->t->idle_time = time(NULL) - tmp->t->idle_time;
        tmp->t->priority += tmp->t->idle_time;
        tmp = tmp->next;
    }
}


void print_thread_list(void) {
    print_list(&thread_list);
}


/* Schedule the next thread to run based on all threads priority */
void scheduler(void) {
    // Threads finished running
    if (thread_list.head == NULL) exit(EXIT_SUCCESS); 

    update_prio();

    
    node* curr = thread_list.head;
    thread* next = curr->t;
    while (curr != NULL) {
        printf("%d\n",curr->t->priority);
        if (curr->t->priority > next->priority) {
            next = curr->t;
        }
        curr = curr->next;
    }

    enqueue_thread(next);
}



void enqueue_thread(thread* t) {
    ASSERT(t != NULL);
    ASSERT(t->magic == THREAD_MAGIC);
    ASSERT(t->status == THREAD_READY);

    ctx_switch(&main_stack,&t->stack);
    scheduler();
}

