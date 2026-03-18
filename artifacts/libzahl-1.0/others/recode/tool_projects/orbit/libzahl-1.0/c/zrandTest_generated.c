/* Test file for zrand_get_random_bits function
 * Since zrand_get_random_bits is static, we need to compile this with the source
 */
#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <setjmp.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "zahl.h"

/* Import internal definitions */
#define BITS_PER_CHAR 32
#define LB_BITS_PER_CHAR 5
#define CEILING_BITS_TO_CHARS(bits) (((bits) + (BITS_PER_CHAR - 1)) >> LB_BITS_PER_CHAR)
#define BITS_IN_LAST_CHAR(bits) ((bits) & (BITS_PER_CHAR - 1))
#define SET_SIGNUM(a, signum) ((a)->sign = (signum))
#define ENSURE_SIZE(a, n) do { if ((a)->alloced < (n)) libzahl_realloc(a, (n)); } while (0)
#define FAILURE(error) (libzahl_error = (error), longjmp(libzahl_jmp_buf, 1))

extern void libzahl_realloc(z_t a, size_t need);
extern jmp_buf libzahl_jmp_buf;
extern int libzahl_error;

/* Copy of the static function we're testing */
static void
zrand_get_random_bits(z_t r, size_t bits, int fd)
{
	size_t read_total = 0, n, chars;
	ssize_t read_just;
	zahl_char_t mask;
	char *buf;

	/* Handle zero bits case */
	if (bits == 0) {
		SET_SIGNUM(r, 0);
		return;
	}

	chars = CEILING_BITS_TO_CHARS(bits);
	mask = 1;

	ENSURE_SIZE(r, chars);
	buf = (char *)(r->chars);

	for (n = chars * sizeof(zahl_char_t); n;) {
		read_just = read(fd, buf + read_total, n);
		if (read_just < 0)
			FAILURE(errno);
		read_total += (size_t)read_just;
		n -= (size_t)read_just;
	}

	bits = BITS_IN_LAST_CHAR(bits);
	if (bits != 0) {
		mask <<= bits;
		mask -= 1;
		r->chars[chars - 1] &= mask;
	}

	for (n = chars; n--;) {
		if (r->chars[n]) {
			r->used = n + 1;
			SET_SIGNUM(r, 1);
			return;
		}
	}
    SET_SIGNUM(r, 0);
}

static jmp_buf test_jmp_buf;

void test_zero_bits() {
    z_t result;
    int fd;

    zinit(result);
    fd = open("/dev/urandom", O_RDONLY);
    assert(fd >= 0);

    zrand_get_random_bits(result, 0, fd);
    assert(zzero(result)); /* Should be zero */

    close(fd);
    zfree(result);
    printf("PASS: test_zero_bits\n");
}

void test_small_bits_fast() {
    z_t result;
    int fd;
    size_t bits = 8;
    z_t upper_bound;

    zinit(result);
    zinit(upper_bound);

    fd = open("/dev/urandom", O_RDONLY);
    assert(fd >= 0);

    zrand_get_random_bits(result, bits, fd);

    /* Result should be < 2^8 = 256 */
    zsetu(upper_bound, 256);
    assert(zcmpmag(result, upper_bound) < 0);

    close(fd);
    zfree(result);
    zfree(upper_bound);
    printf("PASS: test_small_bits_fast\n");
}

void test_medium_bits_fast() {
    z_t result;
    int fd;
    size_t bits = 16;
    z_t upper_bound;

    zinit(result);
    zinit(upper_bound);

    fd = open("/dev/urandom", O_RDONLY);
    assert(fd >= 0);

    zrand_get_random_bits(result, bits, fd);

    /* Result should be < 2^16 = 65536 */
    zsetu(upper_bound, 65536);
    assert(zcmpmag(result, upper_bound) < 0);

    close(fd);
    zfree(result);
    zfree(upper_bound);
    printf("PASS: test_medium_bits_fast\n");
}

void test_exact_char_boundary() {
    z_t result;
    int fd;
    size_t bits = 32; /* Exactly one char */
    z_t upper_bound;

    zinit(result);
    zinit(upper_bound);

    fd = open("/dev/urandom", O_RDONLY);
    assert(fd >= 0);

    zrand_get_random_bits(result, bits, fd);

    /* Result should be < 2^32 */
    zsetu(upper_bound, 1);
    zlsh(upper_bound, upper_bound, 32);
    assert(zcmpmag(result, upper_bound) < 0);

    close(fd);
    zfree(result);
    zfree(upper_bound);
    printf("PASS: test_exact_char_boundary\n");
}

void test_large_bits_fast() {
    z_t result;
    int fd;
    size_t bits = 128;

    zinit(result);

    fd = open("/dev/urandom", O_RDONLY);
    assert(fd >= 0);

    zrand_get_random_bits(result, bits, fd);

    /* Result should be < 2^128 */
    /* We verify by checking zbits(result) <= 128 */
    assert(zbits(result) <= bits);

    close(fd);
    zfree(result);
    printf("PASS: test_large_bits_fast\n");
}

void test_secure_random_device() {
    z_t result;
    int fd;
    size_t bits = 64;

    zinit(result);

    fd = open("/dev/random", O_RDONLY);
    assert(fd >= 0);

    zrand_get_random_bits(result, bits, fd);

    /* Result should be < 2^64 */
    assert(zbits(result) <= bits);

    close(fd);
    zfree(result);
    printf("PASS: test_secure_random_device\n");
}

void test_non_aligned_bits() {
    z_t result;
    int fd;
    size_t bits = 37; /* Not aligned to 32-bit boundary */

    zinit(result);

    fd = open("/dev/urandom", O_RDONLY);
    assert(fd >= 0);

    zrand_get_random_bits(result, bits, fd);

    /* Result should be < 2^37 */
    /* We verify by checking zbits(result) <= 37 */
    assert(zbits(result) <= bits);

    close(fd);
    zfree(result);
    printf("PASS: test_non_aligned_bits\n");
}

void test_multiple_calls_different_results() {
    z_t result1, result2;
    int fd;
    size_t bits = 64;
    int same_count = 0;
    int iterations = 10;

    zinit(result1);
    zinit(result2);

    fd = open("/dev/urandom", O_RDONLY);
    assert(fd >= 0);

    /* Generate multiple random numbers and verify they're not all the same */
    for (int i = 0; i < iterations; i++) {
        zrand_get_random_bits(result1, bits, fd);
        zrand_get_random_bits(result2, bits, fd);

        if (zcmp(result1, result2) == 0) {
            same_count++;
        }
    }

    /* It's astronomically unlikely that all 10 pairs are identical */
    assert(same_count < iterations);

    close(fd);
    zfree(result1);
    zfree(result2);
    printf("PASS: test_multiple_calls_different_results\n");
}

void test_single_bit() {
    z_t result;
    int fd;
    size_t bits = 1;
    z_t upper_bound;

    zinit(result);
    zinit(upper_bound);

    fd = open("/dev/urandom", O_RDONLY);
    assert(fd >= 0);

    zrand_get_random_bits(result, bits, fd);

    /* Result should be 0 or 1 */
    zsetu(upper_bound, 2);
    assert(zcmpmag(result, upper_bound) < 0);

    close(fd);
    zfree(result);
    zfree(upper_bound);
    printf("PASS: test_single_bit\n");
}

int main() {
    printf("Starting zrand_get_random_bits tests...\n\n");

    /* Initialize libzahl */
    zsetup(test_jmp_buf);

    /* Run tests */
    test_zero_bits();
    test_small_bits_fast();
    test_medium_bits_fast();
    test_exact_char_boundary();
    test_large_bits_fast();
    test_secure_random_device();
    test_non_aligned_bits();
    test_multiple_calls_different_results();
    test_single_bit();

    /* Clean up */
    zunsetup();

    printf("\nAll tests passed!\n");
    return 0;
}
