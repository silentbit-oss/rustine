/* Test runner for test_9 only */
#include "zahl.h"
#include <stdio.h>
#include <string.h>

#define assert(expr, expected)\
	do {\
		int got = (expr);\
		if (!(got expected)) {\
			fprintf(stderr,\
				"Failure at line %i: %s, expected %s, but got %i.\n",\
				__LINE__, #expr, #expected, got);\
			ret = 1;\
			goto done;\
		}\
	} while (0)

#define assert_zu(expr, expected)\
	do {\
		size_t got = (expr);\
		if (got != (expected)) {\
			fprintf(stderr,\
				"Failure at line %i: %s, expected %zu, but got %zu.\n",\
				__LINE__, #expr, (size_t)(expected), got);\
			ret = 1;\
			goto done;\
		}\
	} while (0)

#define assert_s(expr, expected)\
	do {\
		const char *got = (expr);\
		if (strcmp(got, expected)) {\
			fprintf(stderr,\
				"Failure at line %i: %s, expected %s, but got %s.\n",\
				__LINE__, #expr, expected, got);\
			ret = 1;\
			goto done;\
		}\
	} while (0)

static int test_9(void)
{
	static z_t a, b, c, d, _0, _1, _2, _3;
	static char buf[2000];
	static int ret = 0;
	static jmp_buf env;

	if (setjmp(env)) {
		zperror(0);
		ret = 2;
		goto done;
	}

	zsetup(env);
	zinit(a), zinit(b), zinit(c), zinit(d), zinit(_0), zinit(_1), zinit(_2), zinit(_3);

	zsetu(_0, 0);
	zsetu(_1, 1);
	zsetu(_2, 2);
	zsetu(_3, 3);

	// String parsing and conversion
	zsets(a, "1234");
	assert(zcmpi(a, 1234), == 0);
	zsets(b, "+1234");
	assert(zcmp(a, b), == 0);
	assert_zu(zstr_length(_0, 10), 1);
	assert_zu(zstr_length(_1, 10), 1);
	assert_zu(zstr_length(_2, 10), 1);
	assert_zu(zstr_length(_3, 10), 1);
	zneg(_2, _2);
	assert_zu(zstr_length(_2, 10), 2);
	zneg(_2, _2);
	assert_zu(zstr_length(a, 10), 4);
	zstr(a, buf);
	assert_s(buf, "1234");
	zsets(a, "-1234");
	zseti(b, -1234);
	zseti(c, 1234);
	assert(zcmp(a, _0), < 0);
	assert(zcmp(a, b), == 0);
	assert(zcmpmag(a, c), == 0);
	assert(zcmp(a, c), < 0);
	zstr(a, buf);
	assert_s(buf, "-1234");
	assert_s(zstr(a, buf), "-1234");

	// Random number generation
	zsetu(d, 100000UL);
	zrand(a, FAST_RANDOM, UNIFORM, d);
	assert(zcmp(a, _0), >= 0);
	assert(zcmp(a, d), <= 0);
	zrand(b, SECURE_RANDOM, UNIFORM, d);
	assert(zcmp(b, _0), >= 0);
	assert(zcmp(b, d), <= 0);
	zrand(c, FAST_RANDOM, UNIFORM, d);
	assert(zcmp(c, _0), >= 0);
	assert(zcmp(c, d), <= 0);
	assert(zcmp(a, b), != 0);
	assert(zcmp(a, c), != 0);
	assert(zcmp(b, c), != 0);

	// Prime testing
	assert((zseti(a, -5), zptest(0, a, 100)), == NONPRIME);
	assert((zseti(a, -4), zptest(0, a, 100)), == NONPRIME);
	assert((zseti(a, -3), zptest(0, a, 100)), == NONPRIME);
	assert((zseti(a, -2), zptest(0, a, 100)), == NONPRIME);
	assert((zseti(a, -1), zptest(0, a, 100)), == NONPRIME);
	assert((zseti(a, 0), zptest(0, a, 100)), == NONPRIME);
	assert((zseti(a, 1), zptest(0, a, 100)), == NONPRIME);
	assert((zseti(a, 2), zptest(0, a, 100)), == PRIME);
	assert((zseti(a, 3), zptest(0, a, 100)), == PRIME);
	assert((zseti(a, 4), zptest(0, a, 100)), == NONPRIME);
	assert((zseti(a, 5), zptest(0, a, 100)), != NONPRIME);
	assert((zseti(a, 6), zptest(0, a, 100)), == NONPRIME);
	assert((zseti(a, 7), zptest(0, a, 100)), != NONPRIME);
	assert((zseti(a, 8), zptest(0, a, 100)), == NONPRIME);
	assert((zseti(a, 9), zptest(0, a, 100)), == NONPRIME);
	assert((zseti(a, 10), zptest(0, a, 100)), == NONPRIME);
	assert((zseti(a, 11), zptest(0, a, 100)), != NONPRIME);
	assert((zseti(a, 101), zptest(0, a, 100)), != NONPRIME);

	ret = 0;
done:
	zfree(a), zfree(b), zfree(c), zfree(d), zfree(_0), zfree(_1), zfree(_2), zfree(_3);
	zunsetup();
	return ret;
}

int main(void)
{
	int result;
	int test_count = 0;

	printf("Running test_9...\n");
	result = test_9();
	if (result != 0) {
		printf("test_9 failed with code %d\n", result);
		return result;
	}
	printf("test_9 passed.\n");

	// Count assertions in test_9
	// String parsing: 15 assertions
	// Random number generation: 9 assertions
	// Prime testing: 18 assertions
	// Total: 42 assertions
	test_count = 42;

	printf("Total assertions in test_9: %d\n", test_count);
	return 0;
}
