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

static int
test_8(void)
{
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

	// Power with negative exponent
	zseti(a, 10);
	zseti(b, -1);
	zpow(a, a, b);
	assert(zcmp(a, _0), == 0);

	zseti(a, 10);
	zseti(b, -1);
	zseti(c, 3); // Initialize c before using in modpow
	zseti(a, 20);
	zmodpow(a, a, b, c);
	assert(zcmp(a, _0), == 0);

	// Power with unsigned exponent
	zseti(a, 10);
	zseti(c, 100000L);
	zpowu(a, a, 5);
	assert(zcmpmag(a, c), == 0);
	assert(zcmp(a, c), == 0);

	zseti(a, -10);
	zseti(c, -100000L);
	zpowu(a, a, 5);
	assert(zcmpmag(a, c), == 0);
	assert(zcmp(a, c), == 0);

	zseti(a, -10);
	zseti(c, 10000L);
	zpowu(a, a, 4);
	assert(zcmpmag(a, c), == 0);
	assert(zcmp(a, c), == 0);

	// Modular power with unsigned exponent
	zseti(a, 10);
	zseti(c, 3);
	zmodpowu(a, a, 5, c);
	assert(zcmpmag(a, _1), == 0);
	assert(zcmp(a, _1), == 0);

	// Power with signed exponent
	zseti(a, 10);
	zseti(b, 5);
	zseti(c, 100000L);
	zpow(a, a, b);
	assert(zcmpmag(a, c), == 0);
	assert(zcmp(a, c), == 0);

	zseti(a, -10);
	zseti(b, 5);
	zseti(c, -100000L);
	zpow(a, a, b);
	assert(zcmpmag(a, c), == 0);
	assert(zcmp(a, c), == 0);

	zseti(a, -10);
	zseti(b, 4);
	zseti(c, 10000L);
	zpow(a, a, b);
	assert(zcmpmag(a, c), == 0);
	assert(zcmp(a, c), == 0);

	// Modular power with signed exponent
	zseti(a, 10);
	zseti(b, 5);
	zseti(c, 3);
	zmodpow(a, a, b, c);
	assert(zcmpmag(a, _1), == 0);
	assert(zcmp(a, _1), == 0);

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

	printf("Running test_8...\n");
	result = test_8();
	if (result != 0) {
		printf("test_8 failed with code %d\n", result);
		return result;
	}
	printf("test_8 passed.\n");

	printf("Test executed successfully - 1 test function run with 18 assertions\n");
	return 0;
}
