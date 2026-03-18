/* Test for libzahl_realloc function */
#include "src/internals.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static int test_libzahl_realloc() {
    static z_t a, b, c;
    static jmp_buf env;
    static int ret = 0;

    if (setjmp(env)) {
        fprintf(stderr, "Error: libzahl_realloc test failed with error\n");
        zperror(0);
        ret = 2;
        goto done;
    }

    zsetup(env);
    zinit(a);
    zinit(b);
    zinit(c);

    printf("Test 1: Reallocating with small size (power of 2)\n");
    zsetu(a, 42);
    size_t original_alloced = a->alloced;
    printf("  Original allocated: %zu\n", original_alloced);

    // Request reallocation to 8 elements (power of 2)
    libzahl_realloc(a, 8);
    printf("  After realloc(8), allocated: %zu\n", a->alloced);
    assert(a->alloced >= 8);
    assert(a->chars != NULL);

    // Value should be preserved
    assert(zsignum(a) == 1);
    assert(zcmpu(a, 42) == 0);
    printf("  PASS: Value preserved, allocated >= 8\n");

    printf("\nTest 2: Reallocating with non-power-of-2 size\n");
    zsetu(b, 1234567890);
    original_alloced = b->alloced;
    printf("  Original allocated: %zu\n", original_alloced);

    // Request reallocation to 15 elements (not power of 2, should round up to 16)
    libzahl_realloc(b, 15);
    printf("  After realloc(15), allocated: %zu\n", b->alloced);
    assert(b->alloced >= 15);
    // Should be rounded up to power of 2 (16)
    assert(b->alloced == 16);
    assert(b->chars != NULL);

    // Value should be preserved
    assert(zsignum(b) == 1);
    assert(zcmpu(b, 1234567890) == 0);
    printf("  PASS: Value preserved, allocated rounded up to 16\n");

    printf("\nTest 3: Reallocating with larger size\n");
    zsetu(c, 999999999);
    original_alloced = c->alloced;
    printf("  Original allocated: %zu\n", original_alloced);

    // Request reallocation to 64 elements
    libzahl_realloc(c, 64);
    printf("  After realloc(64), allocated: %zu\n", c->alloced);
    assert(c->alloced >= 64);
    assert(c->alloced == 64); // Should be exactly 64 (power of 2)
    assert(c->chars != NULL);

    // Value should be preserved
    assert(zsignum(c) == 1);
    assert(zcmpu(c, 999999999) == 0);
    printf("  PASS: Value preserved, allocated = 64\n");

    printf("\nTest 4: Reallocating with size 1 (edge case)\n");
    zsetu(a, 7);
    libzahl_realloc(a, 1);
    printf("  After realloc(1), allocated: %zu\n", a->alloced);
    assert(a->alloced >= 1);
    assert(a->chars != NULL);
    assert(zcmpu(a, 7) == 0);
    printf("  PASS: Value preserved with size 1\n");

    printf("\nTest 5: Reallocating with size 2 (already power of 2)\n");
    zsetu(b, 100);
    libzahl_realloc(b, 2);
    printf("  After realloc(2), allocated: %zu\n", b->alloced);
    assert(b->alloced >= 2);
    assert(b->alloced == 2); // Should be exactly 2
    assert(b->chars != NULL);
    assert(zcmpu(b, 100) == 0);
    printf("  PASS: Value preserved, allocated = 2\n");

    printf("\nTest 6: Multiple reallocations\n");
    zsetu(c, 12345);
    libzahl_realloc(c, 4);
    size_t alloc_after_4 = c->alloced;
    printf("  After realloc(4), allocated: %zu\n", alloc_after_4);
    assert(alloc_after_4 >= 4);
    assert(zcmpu(c, 12345) == 0);

    libzahl_realloc(c, 32);
    size_t alloc_after_32 = c->alloced;
    printf("  After realloc(32), allocated: %zu\n", alloc_after_32);
    assert(alloc_after_32 >= 32);
    assert(zcmpu(c, 12345) == 0);

    libzahl_realloc(c, 8);
    size_t alloc_after_8 = c->alloced;
    printf("  After realloc(8), allocated: %zu\n", alloc_after_8);
    assert(alloc_after_8 >= 8);
    assert(zcmpu(c, 12345) == 0);
    printf("  PASS: Multiple reallocations succeeded\n");

    printf("\nTest 7: Large allocation\n");
    zsetu(a, 0);
    libzahl_realloc(a, 1024);
    printf("  After realloc(1024), allocated: %zu\n", a->alloced);
    assert(a->alloced >= 1024);
    assert(a->alloced == 1024); // Should be exactly 1024 (power of 2)
    assert(a->chars != NULL);
    assert(zcmpu(a, 0) == 0);
    printf("  PASS: Large allocation succeeded\n");

    printf("\n========================================\n");
    printf("All libzahl_realloc tests PASSED!\n");
    printf("========================================\n");
    ret = 0;

done:
    zfree(a);
    zfree(b);
    zfree(c);
    zunsetup();
    return ret;
}

int main(void) {
    int result = test_libzahl_realloc();
    if (result == 0) {
        printf("\nTEST RESULT: SUCCESS\n");
    } else {
        printf("\nTEST RESULT: FAILURE\n");
    }
    return result;
}
