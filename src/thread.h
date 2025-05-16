#ifndef _THREAD_H_
#define _THREAD_H_

#include "context.h"
#include "debug.h"

#define THREAD_MAGIC    0xDEADBEEF
#define STACK_SIZE      1024


#define BITMASK(SHIFT, CNT) (((1ull << (CNT)) - 1) << (SHIFT))

/* Page offset (bits 0:12). */
#define PGSHIFT 0                          /* Index of first offset bit. */
#define PGBITS  12                         /* Number of offset bits. */
#define PGSIZE  (1 << PGBITS)              /* Bytes in a page. */
#define PGMASK  BITMASK(PGSHIFT, PGBITS)   /* Page offset bits (0:12). */



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
} thread;


tid_t thread_create(func_t*,void*);
void thread_yield(void);
void allocate_tid(thread*);
thread* thread_current(void);
thread* thread_running(void);
void thread_ready(thread* t);



#endif