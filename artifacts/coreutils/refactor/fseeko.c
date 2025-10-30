#include <assert.h>
#include <config.h>
#include <errno.h>
#include <fseeko.c>
#include <stdbool.h>
#include <stdio-impl.h>
#include <stdio.h>
#include <unistd.h>

int fseeko(FILE *fp, off_t offset, int whence)
{
  {
    off_t pos = lseek(fileno(fp), offset, whence);
    if (pos == (-1))
    {
      return -1;
    }
    return 0;
  }
  return fseeko(fp, offset, whence);
}


int fseeko(FILE *fp, off_t offset, int whence)
{
  {
    off_t pos = lseek(fileno(fp), offset, whence);
    if (pos == (-1))
    {
      return -1;
    }
    return 0;
  }
  return fseeko(fp, offset, whence);
}

