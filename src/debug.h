#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <stdio.h>
#include <stdlib.h>



#ifndef NDEBUG
#define ASSERT(EXPR) \
    do { \
        if (!(EXPR)) { \
            fprintf(stderr, "ASSERTION FAILED AT %s:%d | %s", __FILE__, __LINE__, #EXPR); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)
#else
#define ASSERT(EXPR) ((void)0)
#endif


#endif