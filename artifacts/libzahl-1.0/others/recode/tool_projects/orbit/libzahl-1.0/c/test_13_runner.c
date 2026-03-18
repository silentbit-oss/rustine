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

#define assert_nr(expr)\
	do {\
		if (setjmp(env2)) {\
			ret = 0;\
			zsetup(env);\
		} else {\
			zsetup(env2);\
			expr;\
			fprintf(stderr,\
				"Failure at line %i: %s, should not have returned.\n",\
				__LINE__, #expr);\
			ret = 1;\
			goto done;\
		}\
	} while (0)


static int
test_13(void){
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


	zsetu(a, 4294967294ULL);
	assert_s(zstr(a, buf), "4294967294");
	zsetu(a, 4294967295ULL);
	assert_s(zstr(a, buf), "4294967295");
	zsetu(a, 4294967296ULL);
	assert_s(zstr(a, buf), "4294967296");
	zsetu(a, 4294967297ULL);
	assert_s(zstr(a, buf), "4294967297");

	zseti(a, 9223372036854775807LL);
	assert_s(zstr(a, buf), "9223372036854775807");
	zseti(a, -9223372036854775807LL);
	assert_s(zstr(a, buf), "-9223372036854775807");
	zseti(a, -9223372036854775807LL - 1LL);
	assert_s(zstr(a, buf), "-9223372036854775808");

	zsetu(a, 18446744073709551614ULL);
	assert_s(zstr(a, buf), "18446744073709551614");
	zsetu(a, 18446744073709551615ULL);
	assert_s(zstr(a, buf), "18446744073709551615");
	zadd(a, a, _1);
	assert_s(zstr(a, buf), "18446744073709551616");
	zadd(a, a, _1);
	assert_s(zstr(a, buf), "18446744073709551617");

	zsets(a, "1000000000000000000000000000000");
	assert_s(zstr(a, buf), "1000000000000000000000000000000");
	zsets(a, "+1000000000000000000000000000000");
	assert_s(zstr(a, buf), "1000000000000000000000000000000");
	zsets(a, "-1000000000000000000000000000000");
	assert_s(zstr(a, buf), "-1000000000000000000000000000000");

	zsetu(a, 1000000000000000ULL);
	zsqr(a, a);
	assert_s(zstr(a, buf), "1000000000000000000000000000000");



#include "test-random.c"

	ret = 0;
done:
	zfree(a), zfree(b), zfree(c), zfree(d), zfree(_0), zfree(_1), zfree(_2), zfree(_3);
	zunsetup();
	return ret;
}


int
main(void)
{
	int result13;

	printf("Running test 13...\n");
	result13 = test_13();
	if (result13 != 0) {
		printf("test 13 failed with code %d\n", result13);
		return result13;
	}
	printf("test 13 passed.\n");

	printf("Test passed successfully!\n");
	return 0;
}
