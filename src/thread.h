#ifndef _THREAD_H_
#define _THREAD_H_

#include "context.h"
#include "debug.h"
#include "list.h"


#define THREAD_MAGIC    0xDEADBEEF
#define STACK_SIZE      1024
#define ALLOC_SIZE      4096


enum thread_status {
    THREAD_RUNNING,
    THREAD_READY,
    THREAD_BLOCKED,
    THREAD_DYING
};

typedef int sema;

typedef void func_t (void* aux);

typedef int tid_t;
#define TID_ERROR ((tid_t) -1)


typedef struct Thread {
    tid_t               tid;
    uint8_t*            stack;
    unsigned            magic;
    enum thread_status  status;
    func_t*             func;
    void*               aux;
    sema                idle;
    struct Context      context;
} thread;




void init_thread_system(void);
tid_t thread_create(func_t*,void*);
void thread_yield(void);
void allocate_tid(thread*);
thread* thread_current(void);
thread* thread_running(void);
void thread_ready(thread*);
void thread_entry(void) NORETURN;
void thread_exit(void) NORETURN;



#endif