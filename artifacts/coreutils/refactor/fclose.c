#include <assert.h>
#include <config.h>
#include <errno.h>
#include <fclose.c>
#include <freading.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <unistd.h>

int rpl_fclose(FILE *fp)
{
  int saved_errno = 0;
  int fd;
  int result = 0;
  fd = fileno(fp);
  if (fd < 0)
  {
    return fclose(fp);
  }
  if (((!(__freading(fp) != 0)) || (lseek(fileno(fp), 0, 1) != (-1))) && fflush(fp))
  {
    saved_errno = errno;
  }
  result = fclose(fp);
  if (saved_errno != 0)
  {
    errno = saved_errno;
    result = EOF;
  }
  return result;
}


int rpl_fclose(FILE *fp)
{
  int saved_errno = 0;
  int fd;
  int result = 0;
  fd = fileno(fp);
  if (fd < 0)
  {
    return fclose(fp);
  }
  if (((!(__freading(fp) != 0)) || (lseek(fileno(fp), 0, 1) != (-1))) && fflush(fp))
  {
    saved_errno = errno;
  }
  result = fclose(fp);
  if (saved_errno != 0)
  {
    errno = saved_errno;
    result = EOF;
  }
  return result;
}

