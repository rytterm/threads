#ifndef _SYNCH_H_
#define _SYNCH_H_


#include "debug.h"
#include "thread.h"
#include <stdbool.h>
#include <sys/syscall.h>
#include <linux/futex.h>
#include <unistd.h>
#include <errno.h>


struct lock {
    int value;
    thread* owner;
};



void lock_init(struct lock*);
void lock_acquire(struct lock*);
void lock_release(struct lock*);


bool lock_held_by_thread(struct lock* lck);

// Helper functions
static int futex_wait(int*, int);
static int futex_wake(int*, int);


#endif