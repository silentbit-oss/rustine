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
test_10(void)
{
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

	// Error condition tests
	assert_nr(zdivmod(a, b, _0, _0));
	assert_nr(zdivmod(a, b, _1, _0));
	zdivmod(a, b, _0, _1);
	zdivmod(a, b, _1, _1);
	assert_nr(zdiv(a, _0, _0));
	assert_nr(zdiv(a, _1, _0));
	zdiv(a, _0, _1);
	zdiv(a, _1, _1);
	assert_nr(zmod(a, _0, _0));
	assert_nr(zmod(a, _1, _0));
	zmod(a, _0, _1);
	zmod(a, _1, _1);
	assert_nr(zpow(a, _0, _0));
	assert_nr((zneg(_1, _1), zpow(a, _0, _1))); zneg(_1, _1);
	zpow(a, _0, _1);
	zpow(a, _1, _0);
	zneg(_1, _1), zpow(a, _1, _0), zneg(_1, _1);
	assert_nr(zmodmul(a, _1, _1, _0));
	assert_nr(zmodpow(a, _0, _0, _1));
	assert_nr((zneg(_1, _1), zmodpow(a, _0, _1, _1))); zneg(_1, _1);
	zmodpow(a, _0, _1, _1);
	zmodpow(a, _1, _0, _1);
	zneg(_1, _1), zmodpow(a, _1, _0, _1), zneg(_1, _1);
	assert_nr(zmodpow(a, _0, _0, _0));
	assert_nr((zneg(_1, _1), zmodpow(a, _0, _1, _0))); zneg(_1, _1);
	assert_nr(zmodpow(a, _0, _1, _0));
	assert_nr(zmodpow(a, _1, _0, _0));
	assert_nr((zneg(_1, _1), zmodpow(a, _1, _0, _0))); zneg(_1, _1);
	assert_nr(zpowu(a, _0, 0));
	zpowu(a, _0, 1);
	zpowu(a, _1, 0);
	zneg(_1, _1), zpowu(a, _1, 0), zneg(_1, _1);
	assert_nr(zmodpowu(a, _0, 0, _1));
	zmodpowu(a, _0, 1, _1);
	zmodpowu(a, _1, 0, _1);
	zneg(_1, _1), zmodpowu(a, _1, 0, _1), zneg(_1, _1);
	assert_nr(zmodpowu(a, _0, 0, _0));
	assert_nr((zneg(_1, _1), zmodpowu(a, _0, 1, _0))); zneg(_1, _1);
	assert_nr(zmodpowu(a, _0, 1, _0));
	assert_nr(zmodpowu(a, _1, 0, _0));
	assert_nr((zneg(_1, _1), zmodpowu(a, _1, 0, _0))); zneg(_1, _1);

	ret = 0;
done:
	zfree(a), zfree(b), zfree(c), zfree(d), zfree(_0), zfree(_1), zfree(_2), zfree(_3);
	zunsetup();
	return ret;
}

int
main(void)
{
	int result;

	printf("Running test_10...\n");
	result = test_10();
	if (result != 0) {
		printf("test_10 failed with code %d\n", result);
		return result;
	}
	printf("test_10 passed.\n");

	printf("Test passed successfully!\n");
	return 0;
}
