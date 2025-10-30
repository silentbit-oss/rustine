#include <arg-nonnull.h>
#include <assert.h>
#include <config.h>
#include <errno.h>
#include <locale.h>
#include <setlocale_null.c>
#include <setlocale_null.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern int setlocale_null_r_unlocked(int category, char *buf, size_t bufsize);
extern const char *setlocale_null_unlocked(int category);
extern int setlocale_null_r(int category, char *buf, size_t bufsize);
extern const char *setlocale_null(int category);
int setlocale_null_r(int category, char *buf, size_t bufsize)
{
  return setlocale_null_r_unlocked(category, buf, bufsize);
}

const char *setlocale_null(int category)
{
  return setlocale_null_unlocked(category);
}


extern int setlocale_null_r_unlocked(int category, char *buf, size_t bufsize);
extern const char *setlocale_null_unlocked(int category);
extern int setlocale_null_r(int category, char *buf, size_t bufsize);
extern const char *setlocale_null(int category);
int setlocale_null_r(int category, char *buf, size_t bufsize)
{
  return setlocale_null_r_unlocked(category, buf, bufsize);
}

const char *setlocale_null(int category)
{
  return setlocale_null_unlocked(category);
}

