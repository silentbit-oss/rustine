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

static int test_3(){
	static z_t a, b, c, d, _0, _1, _2, _3;
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

	// Test basic subtraction operations
	zsub(a, _2, _1);
	assert(zcmpmag(_2, _1), > 0);
	assert(zcmpmag(_2, _0), > 0);
	assert(zcmpmag(_1, _0), > 0);
	zsub(b, _1, _2);
	assert(zcmpmag(_2, _0), > 0);
	assert(zcmpmag(_1, _0), > 0);
	assert(zcmpmag(_2, _1), > 0);
	assert(zcmpmag(a, b), == 0);
	assert(zcmpmag(a, _1), == 0);
	assert(zcmp(a, b), > 0);
	assert(zcmp(a, _1), == 0);
	assert(zcmp(b, _1), < 0);

	// Test subtraction resulting in zero
	zsub(a, _1, _1);
	assert(zcmp(a, _0), == 0);
	zseti(b, 0);
	zsetu(c, 0);
	zsub(a, b, c);
	assert(zcmp(a, _0), == 0);

	// Test more subtraction cases
	assert(zcmpmag(_2, _1), > 0);
	assert(zcmp(_2, _1), > 0);
	zsub(a, _2, _1);
	assert(zsignum(a), == 1);
	assert(zcmpmag(a, _1), == 0);
	assert(zcmp(a, _1), == 0);
	zsub(a, a, _1);
	assert(zcmp(a, _0), == 0);
	zsub(a, a, _0);
	assert(zcmp(a, _0), == 0);
	zsub(a, _1, _2);
	assert(zcmp(a, _1), < 0);
	assert(zcmpmag(a, _1), == 0);

	// Test absolute value operations
	zabs(a, a);
	assert(zcmp(a, _1), == 0);
	zabs(a, a);
	assert(zcmp(a, _1), == 0);
	zabs(a, _1);
	assert(zcmp(a, _1), == 0);
	zabs(a, _0);
	assert(zcmp(a, _0), == 0);

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

	printf("Running test_3...\n");
	result = test_3();
	if (result != 0) {
		printf("test_3 failed with code %d\n", result);
		return result;
	}
	printf("test_3 passed.\n");

	return 0;
}
