/* See LICENSE file for copyright and license details. */
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

static int test_1(){
	static z_t a, b, c, d, _0, _1, _2, _3;
	static char buf[2000];
	static int ret = 0;
	static jmp_buf env, env2;
	static size_t n;

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

	// Test basic properties
	assert(zeven(_0), == 1);
	assert(zodd(_0), == 0);
	assert(zzero(_0), == 1);
	assert(zsignum(_0), == 0);
	assert(zeven(_1), == 0);
	assert(zodd(_1), == 1);
	assert(zzero(_1), == 0);
	assert(zsignum(_1), == 1);
	assert(zeven(_2), == 1);
	assert(zodd(_2), == 0);
	assert(zzero(_2), == 0);
	assert(zsignum(_2), == 1);

	// Test swap operations
	zswap(_1, _2);
	assert(zeven(_2), == 0);
	assert(zodd(_2), == 1);
	assert(zzero(_2), == 0);
	assert(zsignum(_2), == 1);
	assert(zeven(_1), == 1);
	assert(zodd(_1), == 0);
	assert(zzero(_1), == 0);
	assert(zsignum(_1), == 1);
	zswap(_2, _1);
	assert(zeven(_1), == 0);
	assert(zodd(_1), == 1);
	assert(zzero(_1), == 0);
	assert(zsignum(_1), == 1);
	assert(zeven(_2), == 1);
	assert(zodd(_2), == 0);
	assert(zzero(_2), == 0);
	assert(zsignum(_2), == 1);

	// Test negation
	assert((zneg(_2, _2), zsignum(_2)), == -1); zneg(_2, _2);
	assert(zsignum(_2), == 1);

	// Test comparison operations
	assert(zcmp(_0, _0), == 0);
	assert(zcmp(_1, _1), == 0);
	assert(zcmp(_0, _1), < 0);
	assert(zcmp(_1, _0), > 0);
	assert(zcmp(_1, _2), < 0);
	assert(zcmp(_2, _1), > 0);
	assert(zcmp(_0, _2), < 0);
	assert(zcmp(_2, _0), > 0);

	// Test bit set operations
	zbset(a, _0, 0, 1);
	assert(zcmp(a, _1), == 0);
	zbset(a, a, 1, 1);
	assert(zcmp(a, _3), == 0);
	zbset(a, a, 0, 0);
	assert(zcmp(a, _2), == 0);
	zbset(a, a, 0, 0);
	assert(zcmp(a, _2), == 0);
	zbset(a, a, 0, -1);
	assert(zcmp(a, _3), == 0);
	zbset(a, a, 0, -1);
	assert(zcmp(a, _2), == 0);

	// Test save/load operations
	zsetu(a, 1000);
	zsetu(b, 0);
	assert(zcmp(a, b), != 0);
	n = zsave(a, buf);
	assert(n, > 0);
	assert_zu(zload(b, buf), n);
	assert(zcmp(a, b), == 0);

	// Test bit operations
	assert_zu(zbits(_0), 1);
	assert_zu(zbits(_1), 1);
	assert_zu(zbits(_2), 2);
	assert_zu(zbits(_3), 2);

	assert_zu(zlsb(_0), SIZE_MAX);
	assert_zu(zlsb(_1), 0);
	assert_zu(zlsb(_2), 1);
	assert_zu(zlsb(_3), 0);

	ret = 0;
	done:
		zfree(a), zfree(b), zfree(c), zfree(d), zfree(_0), zfree(_1), zfree(_2), zfree(_3);
		zunsetup();
		return ret;
}

int
main(void)
{
	int result1;

	printf("Running test_1...\n");
	result1 = test_1();
	if (result1 != 0) {
		printf("test_1 failed with code %d\n", result1);
		return result1;
	}
	printf("test_1 passed.\n");

	printf("All tests passed successfully!\n");
	return 0;
}
