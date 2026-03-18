#ifndef TEST_COMMON_H
#define TEST_COMMON_H

#include <stdio.h>
#include <stdlib.h>

#define ASSERT(cond, msg) \
    do { \
        if (!(cond)) { \
            fprintf(stderr, "❌ ASSERT FAILED: %s (%s:%d)\n", msg, __FILE__, __LINE__); \
            exit(EXIT_FAILURE); \
        } \
    } while (0)

#define PASS(msg) printf("✅ %s passed\n", msg)

#endif
