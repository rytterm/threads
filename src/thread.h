#ifndef _THREAD_H_
#define _THREAD_H_

#include "debug.h"
#include "list.h"
#include <stdint.h>
#include <stdbool.h>
#include "switch.h"
#include "attr.h"


#define THREAD_MAGIC    0xDEADBEEF
#define ALLOC_SIZE      4096


enum thread_status {
    THREAD_RUNNING,
    THREAD_READY,
    THREAD_BLOCKED,
    THREAD_DYING
};


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
    bool                idle;
    
} thread;




void init_thread_system(void);
void print_thread_list(void);

thread* thread_create(func_t*,void*);
void thread_yield(void);
void allocate_tid(thread*);
thread* thread_current(void);
thread* thread_running(void);
void thread_ready(thread*);
void thread_entry(void) NORETURN;
void thread_exit(void) NORETURN;

void scheduler(void);
void enqueue_thread(thread*);



extern void NORETURN ctx_restore(uint8_t**);
extern void ctx_save(uint8_t**);
extern void ctx_switch(uint8_t**, uint8_t**);


#endif