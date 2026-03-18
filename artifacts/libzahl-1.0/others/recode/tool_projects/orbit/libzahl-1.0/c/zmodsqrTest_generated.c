/* Test file for zmodsqr function - Generated test */
#include "zahl.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <setjmp.h>

/* Test helper: Compare two z_t values */
int z_equals(z_t a, z_t b) {
    return zcmp(a, b) == 0;
}

/* Test helper: Set z_t from string */
void z_from_str(z_t a, const char *str) {
    zsets(a, str);
}

void test_zmodsqr_basic() {
    printf("Test: zmodsqr_basic - (17 * 17) %% 10 = 9\n");
    jmp_buf jmp;
    if (setjmp(jmp)) {
        printf("FAIL: Unexpected error\n");
        exit(1);
    }
    zsetup(jmp);

    z_t a, b, c, expected;
    zinit(a); zinit(b); zinit(c); zinit(expected);

    zseti(b, 17);
    zseti(c, 10);
    zseti(expected, 9);

    zmodsqr(a, b, c);

    assert(z_equals(a, expected));
    printf("PASS\n");

    zfree(a); zfree(b); zfree(c); zfree(expected);
    zunsetup();
}

void test_zmodsqr_zero() {
    printf("Test: zmodsqr_zero - (0 * 0) %% 10 = 0\n");
    jmp_buf jmp;
    if (setjmp(jmp)) {
        printf("FAIL: Unexpected error\n");
        exit(1);
    }
    zsetup(jmp);

    z_t a, b, c, expected;
    zinit(a); zinit(b); zinit(c); zinit(expected);

    zseti(b, 0);
    zseti(c, 10);
    zseti(expected, 0);

    zmodsqr(a, b, c);

    assert(z_equals(a, expected));
    printf("PASS\n");

    zfree(a); zfree(b); zfree(c); zfree(expected);
    zunsetup();
}

void test_zmodsqr_negative() {
    printf("Test: zmodsqr_negative - (-7 * -7) %% 10 = 9\n");
    jmp_buf jmp;
    if (setjmp(jmp)) {
        printf("FAIL: Unexpected error\n");
        exit(1);
    }
    zsetup(jmp);

    z_t a, b, c, expected;
    zinit(a); zinit(b); zinit(c); zinit(expected);

    zseti(b, -7);
    zseti(c, 10);
    zseti(expected, 9);

    zmodsqr(a, b, c);

    assert(z_equals(a, expected));
    printf("PASS\n");

    zfree(a); zfree(b); zfree(c); zfree(expected);
    zunsetup();
}

void test_zmodsqr_zero_modulus() {
    printf("Test: zmodsqr_zero_modulus - Should trigger error for modulus = 0\n");
    jmp_buf jmp;
    int error_occurred = 0;

    if (setjmp(jmp)) {
        error_occurred = 1;
        printf("PASS: Error correctly triggered for zero modulus\n");
        zunsetup();
        return;
    }
    zsetup(jmp);

    z_t a, b, c;
    zinit(a); zinit(b); zinit(c);

    zseti(b, 5);
    zseti(c, 0);

    zmodsqr(a, b, c);

    zfree(a); zfree(b); zfree(c);
    zunsetup();

    if (!error_occurred) {
        printf("FAIL: No error triggered for zero modulus\n");
        exit(1);
    }
}

void test_zmodsqr_large() {
    printf("Test: zmodsqr_large - (12345 * 12345) %% 1000 = 25\n");
    jmp_buf jmp;
    if (setjmp(jmp)) {
        printf("FAIL: Unexpected error\n");
        exit(1);
    }
    zsetup(jmp);

    z_t a, b, c, expected;
    zinit(a); zinit(b); zinit(c); zinit(expected);

    zseti(b, 12345);
    zseti(c, 1000);
    zseti(expected, 25);

    zmodsqr(a, b, c);

    assert(z_equals(a, expected));
    printf("PASS\n");

    zfree(a); zfree(b); zfree(c); zfree(expected);
    zunsetup();
}

void test_zmodsqr_one() {
    printf("Test: zmodsqr_one - (1 * 1) %% 10 = 1\n");
    jmp_buf jmp;
    if (setjmp(jmp)) {
        printf("FAIL: Unexpected error\n");
        exit(1);
    }
    zsetup(jmp);

    z_t a, b, c, expected;
    zinit(a); zinit(b); zinit(c); zinit(expected);

    zseti(b, 1);
    zseti(c, 10);
    zseti(expected, 1);

    zmodsqr(a, b, c);

    assert(z_equals(a, expected));
    printf("PASS\n");

    zfree(a); zfree(b); zfree(c); zfree(expected);
    zunsetup();
}

void test_zmodsqr_modulus_larger_than_square() {
    printf("Test: zmodsqr_modulus_larger - (5 * 5) %% 100 = 25\n");
    jmp_buf jmp;
    if (setjmp(jmp)) {
        printf("FAIL: Unexpected error\n");
        exit(1);
    }
    zsetup(jmp);

    z_t a, b, c, expected;
    zinit(a); zinit(b); zinit(c); zinit(expected);

    zseti(b, 5);
    zseti(c, 100);
    zseti(expected, 25);

    zmodsqr(a, b, c);

    assert(z_equals(a, expected));
    printf("PASS\n");

    zfree(a); zfree(b); zfree(c); zfree(expected);
    zunsetup();
}

void test_zmodsqr_aliasing() {
    printf("Test: zmodsqr_aliasing - Test when a and c are the same\n");
    jmp_buf jmp;
    if (setjmp(jmp)) {
        printf("FAIL: Unexpected error\n");
        exit(1);
    }
    zsetup(jmp);

    z_t a, b, expected;
    zinit(a); zinit(b); zinit(expected);

    zseti(a, 10);  /* a serves as both output and modulus */
    zseti(b, 7);
    zseti(expected, 9);

    zmodsqr(a, b, a);  /* a is both output and modulus */

    assert(z_equals(a, expected));
    printf("PASS\n");

    zfree(a); zfree(b); zfree(expected);
    zunsetup();
}

void test_zmodsqr_very_large() {
    printf("Test: zmodsqr_very_large - Test with very large numbers\n");
    jmp_buf jmp;
    if (setjmp(jmp)) {
        printf("FAIL: Unexpected error\n");
        exit(1);
    }
    zsetup(jmp);

    z_t a, b, c, expected;
    zinit(a); zinit(b); zinit(c); zinit(expected);

    /* b = 123456789123456789 */
    z_from_str(b, "123456789123456789");
    /* c = 1000000007 (large prime) */
    z_from_str(c, "1000000007");
    /* Expected: (123456789123456789^2) % 1000000007 = 165980939 */
    z_from_str(expected, "165980939");

    zmodsqr(a, b, c);

    assert(z_equals(a, expected));
    printf("PASS\n");

    zfree(a); zfree(b); zfree(c); zfree(expected);
    zunsetup();
}

void test_zmodsqr_negative_modulus() {
    printf("Test: zmodsqr_negative_modulus - (7 * 7) %% -10\n");
    jmp_buf jmp;
    if (setjmp(jmp)) {
        printf("FAIL: Unexpected error\n");
        exit(1);
    }
    zsetup(jmp);

    z_t a, b, c, expected;
    zinit(a); zinit(b); zinit(c); zinit(expected);

    zseti(b, 7);
    zseti(c, -10);
    /* C implementation returns 9 (positive result) */
    zseti(expected, 9);

    zmodsqr(a, b, c);

    assert(z_equals(a, expected));
    printf("PASS\n");

    zfree(a); zfree(b); zfree(c); zfree(expected);
    zunsetup();
}

int main() {
    printf("Running zmodsqr tests...\n\n");

    test_zmodsqr_basic();
    test_zmodsqr_zero();
    test_zmodsqr_negative();
    test_zmodsqr_zero_modulus();
    test_zmodsqr_large();
    test_zmodsqr_one();
    test_zmodsqr_modulus_larger_than_square();
    test_zmodsqr_aliasing();
    test_zmodsqr_very_large();
    test_zmodsqr_negative_modulus();

    printf("\n=== All zmodsqr C tests passed! ===\n");
    return 0;
}
