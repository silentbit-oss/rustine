#include <assert.h>
#include <config.h>
#include <langinfo.h>
#include <localcharset.c>
#include <localcharset.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern const char *locale_charset(void);
struct table_entry
{
  const char alias[11 + 1];
  const char canonical[11 + 1];
};
static const struct table_entry alias_table[] = {{"", ""}};
const char *locale_charset(void)
{
  const char *codeset;
  unsigned int codeset_idx = 0;
  codeset_idx = nl_langinfo(CODESET);
  if ((&codeset[codeset_idx]) == 0)
  {
    codeset_idx = "";
  }
  {
    {
      if (codeset[0 + codeset_idx] == '\0')
      {
        codeset_idx = "ASCII";
      }
    }
  }
  return codeset;
}


extern const char *locale_charset(void);
struct table_entry
{
  const char alias[11 + 1];
  const char canonical[11 + 1];
};
static const struct table_entry alias_table[] = {{"", ""}};
const char *locale_charset(void)
{
  const char *codeset;
  unsigned int codeset_idx = 0;
  codeset_idx = nl_langinfo(CODESET);
  if ((&codeset[codeset_idx]) == 0)
  {
    codeset_idx = "";
  }
  {
    {
      if (codeset[0 + codeset_idx] == '\0')
      {
        codeset_idx = "ASCII";
      }
    }
  }
  return codeset;
}

