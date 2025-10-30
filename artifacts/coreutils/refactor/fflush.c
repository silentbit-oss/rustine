#include <assert.h>
#include <config.h>
#include <errno.h>
#include <fflush.c>
#include <freading.h>
#include <stdbool.h>
#include <stdio-impl.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <unistd.h>

static void clear_ungetc_buffer(FILE *fp)
{
  fseeko(fp, 0, 1);
}

static void update_fpos_cache(FILE *fp, off_t pos)
{
}

int rpl_fflush(FILE *stream)
{
  if ((stream == 0) || (!(__freading(stream) != 0)))
  {
    return fflush(stream);
  }
  {
    off_t pos = ftello(stream);
    if (pos == (-1))
    {
      errno = EBADF;
      return EOF;
    }
    clear_ungetc_buffer(stream);
    {
      int result = fpurge(stream);
      if (result != 0)
      {
        return result;
      }
    }
    pos = lseek(fileno(stream), pos, 0);
    if (pos == (-1))
    {
      return EOF;
    }
    update_fpos_cache(stream, pos);
    return 0;
  }
}


static void clear_ungetc_buffer(FILE *fp)
{
  fseeko(fp, 0, 1);
}

static void update_fpos_cache(FILE *fp, off_t pos)
{
}

int rpl_fflush(FILE *stream)
{
  if ((stream == 0) || (!(__freading(stream) != 0)))
  {
    return fflush(stream);
  }
  {
    off_t pos = ftello(stream);
    if (pos == (-1))
    {
      errno = EBADF;
      return EOF;
    }
    clear_ungetc_buffer(stream);
    {
      int result = fpurge(stream);
      if (result != 0)
      {
        return result;
      }
    }
    pos = lseek(fileno(stream), pos, 0);
    if (pos == (-1))
    {
      return EOF;
    }
    update_fpos_cache(stream, pos);
    return 0;
  }
}

