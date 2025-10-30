#include <assert.h>
#include <config.h>
#include <errno.h>
#include <progname.c>
#include <progname.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern const char *program_name;
extern void set_program_name(const char *argv0);
const char *program_name = 0;
void set_program_name(const char *argv0)
{
  unsigned int argv0_idx = 0;
  const char *slash;
  unsigned int slash_idx = 0;
  const char *base;
  unsigned int base_idx = 0;
  if ((&argv0[argv0_idx]) == 0)
  {
    fputs("A NULL argv[0] was passed through an exec system call.\n", stderr);
    abort();
  }
  slash_idx = strrchr(argv0, '/');
  base_idx = ((&slash[slash_idx]) != 0) ? ((&slash[slash_idx]) + 1) : (argv0);
  if ((((&base[base_idx]) - (&argv0[argv0_idx])) >= 7) && (strncmp((&base[base_idx]) - 7, "/.libs/", 7) == 0))
  {
    argv0_idx = &base[base_idx];
    if (strncmp(base, "lt-", 3) == 0)
    {
      argv0_idx = (&base[base_idx]) + 3;
      program_invocation_short_name = (char *) argv0;
    }
  }
  program_name = &argv0[argv0_idx];
  program_invocation_name = (char *) argv0;
}


extern const char *program_name;
extern void set_program_name(const char *argv0);
const char *program_name = 0;
void set_program_name(const char *argv0)
{
  unsigned int argv0_idx = 0;
  const char *slash;
  unsigned int slash_idx = 0;
  const char *base;
  unsigned int base_idx = 0;
  if ((&argv0[argv0_idx]) == 0)
  {
    fputs("A NULL argv[0] was passed through an exec system call.\n", stderr);
    abort();
  }
  slash_idx = strrchr(argv0, '/');
  base_idx = ((&slash[slash_idx]) != 0) ? ((&slash[slash_idx]) + 1) : (argv0);
  if ((((&base[base_idx]) - (&argv0[argv0_idx])) >= 7) && (strncmp((&base[base_idx]) - 7, "/.libs/", 7) == 0))
  {
    argv0_idx = &base[base_idx];
    if (strncmp(base, "lt-", 3) == 0)
    {
      argv0_idx = (&base[base_idx]) + 3;
      program_invocation_short_name = (char *) argv0;
    }
  }
  program_name = &argv0[argv0_idx];
  program_invocation_name = (char *) argv0;
}

