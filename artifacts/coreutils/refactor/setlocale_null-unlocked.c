#include <arg-nonnull.h>
#include <assert.h>
#include <config.h>
#include <errno.h>
#include <locale.h>
#include <setlocale_null-unlocked.c>
#include <setlocale_null.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

extern int setlocale_null_r_unlocked(int category, char *buf, size_t bufsize);
extern const char *setlocale_null_unlocked(int category);
extern int setlocale_null_r(int category, char *buf, size_t bufsize);
extern const char *setlocale_null(int category);
const char *setlocale_null_unlocked(int category)
{
  const char *result = setlocale(category, 0);
  return result;
}

int setlocale_null_r_unlocked(int category, char *buf, size_t bufsize)
{
  const char *result = setlocale_null_unlocked(category);
  if (result == 0)
  {
    if (bufsize > 0)
    {
      buf[0] = '\0';
    }
    return EINVAL;
  }
  else
  {
    size_t length = strlen(result);
    if (length < bufsize)
    {
      memcpy(buf, result, length + 1);
      return 0;
    }
    else
    {
      if (bufsize > 0)
      {
        memcpy(buf, result, bufsize - 1);
        buf[bufsize - 1] = '\0';
      }
      return ERANGE;
    }
  }
}


extern int setlocale_null_r_unlocked(int category, char *buf, size_t bufsize);
extern const char *setlocale_null_unlocked(int category);
extern int setlocale_null_r(int category, char *buf, size_t bufsize);
extern const char *setlocale_null(int category);
const char *setlocale_null_unlocked(int category)
{
  const char *result = setlocale(category, 0);
  return result;
}

int setlocale_null_r_unlocked(int category, char *buf, size_t bufsize)
{
  const char *result = setlocale_null_unlocked(category);
  if (result == 0)
  {
    if (bufsize > 0)
    {
      buf[0] = '\0';
    }
    return EINVAL;
  }
  else
  {
    size_t length = strlen(result);
    if (length < bufsize)
    {
      memcpy(buf, result, length + 1);
      return 0;
    }
    else
    {
      if (bufsize > 0)
      {
        memcpy(buf, result, bufsize - 1);
        buf[bufsize - 1] = '\0';
      }
      return ERANGE;
    }
  }
}

