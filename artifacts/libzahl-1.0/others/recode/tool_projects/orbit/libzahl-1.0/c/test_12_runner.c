/* Test runner for test_12 only */
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

static int
test_12(void){
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


	// Very large number operations
	zsetu(a, 4000000000ULL);
	zsetu(b, 4000000000ULL);
	zadd(c, a, a);
	zsets(d, "8000000000");
	assert(zcmp(c, d), == 0);
	zadd(c, a, b);
	assert(zcmp(c, d), == 0);
	zadd(c, c, a);
	zsets(d, "12000000000");
	assert(zcmp(c, d), == 0);
	zsub(c, c, a);
	zsets(d, "8000000000");
	assert(zcmp(c, d), == 0);
	zsub(c, c, a);
	zsets(d, "4000000000");
	assert(zcmp(c, d), == 0);
	zsets(d, "8000000000");
	zrsh(d, d, 1);
	assert(zcmp(c, d), == 0);
	zsets(a, "6234216714");
	zsets(b, "9424614147");
	zsets(d, "830476546");
	zand(c, a, b);
	assert(zcmp(c, d), == 0);
	zsets(a, "234216714");
	zsets(b, "9424614147");
	zsets(d, "9629466379");
	zor(c, a, b);
	assert(zcmp(c, d), == 0);
	zsets(a, "6234216714");
	zsets(b, "9424614147");
	zsets(d, "13997877769");
	zxor(c, a, b);
	assert(zcmp(c, d), == 0);
	zsets(a, "34216714");
	zsets(b, "9424614147");
	zsets(d, "9458821129");
	zxor(c, a, b);
	assert(zcmp(c, d), == 0);
	zsetu(a, 1000000000ULL);
	zsets(d, "1000000000000000000");
	zmul(c, a, a);
	assert(zcmp(c, d), == 0);
	zdiv(c, c, a);
	assert(zcmp(c, a), == 0);
	zsetu(a, 1000000000ULL);
	zsets(d, "1000000000000000000");
	zsqr(c, a);
	assert(zcmp(c, d), == 0);
	zsetu(a, 1000000000ULL);
	zmodpowu(c, a, 5, _3);
	assert(zcmpu(c, 1), == 0);
	zsetu(a, 1000000000ULL);
	zsets(d, "1");
	zpowu(c, a, 0);
	assert(zcmp(c, d), == 0);
	zsetu(a, 1000000000ULL);
	zsets(d, "1000000000");
	zpowu(c, a, 1);
	assert(zcmp(c, d), == 0);
	zsetu(a, 1000000000ULL);
	zsets(d, "1000000000000000000");
	zpowu(c, a, 2);
	assert(zcmp(c, d), == 0);
	zsetu(a, 1000000000ULL);
	zsets(b, "1000000000000000000");
	zsets(d, "1000000000000000000000000000");
	zmul(c, a, b);
	assert(zcmp(c, d), == 0);
	zsetu(a, 1000000000ULL);
	zsets(d, "1000000000000000000000000000");
	zmul(b, a, a);
	zmul(b, b, a);
	assert(zcmp(c, d), == 0);
	zsetu(a, 1000000000ULL);
	zsets(d, "1000000000000000000000000000");
	zpowu(c, a, 3);
	assert(zcmp(c, d), == 0);
	zsetu(a, 1000000000ULL);
	zsets(d, "1000000000000000000000000000000000000");
	zpowu(c, a, 4);
	assert(zcmp(c, d), == 0);
	zsetu(a, 1000000000ULL);
	zsets(d, "1000000000000000000000000000000000000000000000");
	zpowu(c, a, 5);
	assert(zcmp(c, d), == 0);



#include "test-random.c"

	ret = 0;
done:
	zfree(a), zfree(b), zfree(c), zfree(d), zfree(_0), zfree(_1), zfree(_2), zfree(_3);
	zunsetup();
	return ret;
}

int main(void) {
	int result;
	printf("Running test_12...\n");
	result = test_12();
	if (result != 0) {
		printf("test_12 failed with code %d\n", result);
		return result;
	}
	printf("test_12 passed.\n");
	return 0;
}
