/* See LICENSE file for copyright and license details. */
/* Generated test file for zerror function */
#include "zahl.h"

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

#define assert_test(expr, msg)\
	do {\
		if (!(expr)) {\
			fprintf(stderr,\
				"Failure at line %i: %s\n",\
				__LINE__, msg);\
			ret = 1;\
			goto done;\
		}\
	} while (0)


static int
test_zerror(void)
{
	static z_t a, b, _0, _1;
	static int ret = 0;
	static jmp_buf env, env2;
	const char *desc = NULL;
	enum zerror err_code;

	if (setjmp(env)) {
		zperror(0);
		ret = 2;
		goto done;
	}

	zsetup(env);
	zinit(a), zinit(b), zinit(_0), zinit(_1);

	zsetu(_0, 0);
	zsetu(_1, 1);

	/* Test 1: Check that zerror returns ZERROR_ERRNO_SET when no error */
	err_code = zerror(&desc);
	assert_test(err_code == ZERROR_ERRNO_SET, "Expected ZERROR_ERRNO_SET when no error");
	printf("Test 1 passed: No error returns ZERROR_ERRNO_SET\n");

	/* Test 2: Trigger a division by zero error and check zerror */
	if (setjmp(env2)) {
		/* After error, check zerror function */
		err_code = zerror(&desc);
		assert_test(err_code == ZERROR_ERRNO_SET, "Expected ZERROR_ERRNO_SET after error");
		assert_test(desc != NULL, "Expected non-NULL error description");
		assert_test(errno != 0, "Expected errno to be set");
		printf("Test 2 passed: Error returns ZERROR_ERRNO_SET with description: %s\n", desc);

		/* Reset to main environment */
		zsetup(env);
	} else {
		/* Trigger an error - division by zero */
		zsetup(env2);
		zdiv(a, _1, _0); /* This should trigger an error */
		fprintf(stderr, "Failure: zdiv should have triggered an error\n");
		ret = 1;
		goto done;
	}

	/* Test 3: Check zerror without description pointer */
	if (setjmp(env2)) {
		/* After error, check zerror function with NULL desc */
		err_code = zerror(NULL);
		assert_test(err_code == ZERROR_ERRNO_SET, "Expected ZERROR_ERRNO_SET even with NULL desc");
		printf("Test 3 passed: zerror works with NULL description pointer\n");

		/* Reset to main environment */
		zsetup(env);
	} else {
		/* Trigger another error */
		zsetup(env2);
		zmod(a, _1, _0); /* This should trigger an error */
		fprintf(stderr, "Failure: zmod should have triggered an error\n");
		ret = 1;
		goto done;
	}

	/* Test 4: Verify errno is set correctly */
	if (setjmp(env2)) {
		int saved_errno = errno;
		err_code = zerror(&desc);
		assert_test(errno == saved_errno, "Expected errno to remain the same after zerror call");
		assert_test(saved_errno != 0, "Expected errno to be non-zero after error");
		printf("Test 4 passed: errno is correctly preserved (errno=%d)\n", saved_errno);

		/* Reset to main environment */
		zsetup(env);
	} else {
		/* Trigger another error */
		zsetup(env2);
		zpow(a, _0, _0); /* This should trigger an error (0^0 is undefined) */
		fprintf(stderr, "Failure: zpow should have triggered an error\n");
		ret = 1;
		goto done;
	}

	ret = 0;
done:
	zfree(a), zfree(b), zfree(_0), zfree(_1);
	zunsetup();
	return ret;
}

int
main(void)
{
	int result;

	printf("Running test_zerror...\n");
	result = test_zerror();
	if (result != 0) {
		printf("test_zerror failed with code %d\n", result);
		return result;
	}
	printf("test_zerror passed.\n");

	printf("Test passed successfully!\n");
	return 0;
}
