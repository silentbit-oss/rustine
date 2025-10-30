#include <assert.h>
#include <config.h>
#include <hard-locale.c>
#include <hard-locale.h>
#include <locale.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

extern bool hard_locale(int category);
bool hard_locale(int category)
{
  char locale[256 + 1];
  if (setlocale_null_r(category, locale, sizeof(locale)))
  {
    return 0;
  }
  if (!((strcmp(locale, "C") == 0) || (strcmp(locale, "POSIX") == 0)))
  {
    return 1;
  }
  return 0;
}


extern bool hard_locale(int category);
bool hard_locale(int category)
{
  char locale[256 + 1];
  if (setlocale_null_r(category, locale, sizeof(locale)))
  {
    return 0;
  }
  if (!((strcmp(locale, "C") == 0) || (strcmp(locale, "POSIX") == 0)))
  {
    return 1;
  }
  return 0;
}

