#include "synch.h"





void lock_init(struct lock* lck) {
    lck->value = 0;
    lck->owner = NULL;
}


void lock_acquire(struct lock* lck) {
    ASSERT(!lock_held_by_thread(lck));
    while (1) {
        int expected = 0;
        /* if lck->value = expected (which is 0)
           then set lck->val = 1 */
        if (__atomic_compare_exchange_n(&lck->value, &expected, 1, false, 
                                        __ATOMIC_ACQUIRE, __ATOMIC_RELAXED)) {
            lck->owner = thread_current();
            return;
        }
        /* if lck->value = 1, wait until otherwise */
        futex_wait(&lck->value, 1);
    }
}


void lock_release(struct lock* lck) {
    ASSERT(lock_held_by_thread(lck));
    lck->owner = NULL;
    /* set lck->value = 0 */
    __atomic_exchange_n(&lck->value,0,__ATOMIC_RELEASE);
    /* wake 1 thread */
    futex_wake(&lck->value, 1);
}




bool lock_held_by_thread(struct lock* lck) {
    return thread_current() == lck->owner;
}




static int futex_wait(int* address, int expected) {
    int fw = syscall(SYS_futex, address, FUTEX_WAIT, expected, NULL, NULL, 0);
    
    ASSERT(fw != -1);
    ASSERT(errno == EAGAIN);
    ASSERT(errno == EINTR);
    
    return fw;
}


static int futex_wake(int* address, int count) {
    int fw = syscall(SYS_futex, address, FUTEX_WAKE, count, NULL, NULL, 0);
    
    ASSERT(fw != -1);
    ASSERT(errno == EAGAIN);
    ASSERT(errno == EINTR);
    
    return fw;
}