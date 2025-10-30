char *osdep_get_name(int fd, char *tty)
{
  FILE *f;
  unsigned int f_idx = 0;
  char *path;
  char *buf;
  unsigned int buf_idx = 0;
  size_t len;
  int ch;
  pid_t pgrp;
  if ((pgrp = tcgetpgrp(fd)) == (-1))
  {
    return 0;
  }
  xasprintf(&path, "/proc/%lld/cmdline", (long long) pgrp);
  if ((f_idx = fopen(path, "r")) == 0)
  {
    free(path);
    return 0;
  }
  free(path);
  len = 0;
  buf_idx = 0;
  while ((ch = fgetc(f)) != EOF)
  {
    if (ch == '\0')
    {
      break;
    }
    buf_idx = xrealloc(buf_idx, len + 2);
    buf[len + buf_idx] = ch;
    len += 1;
  }

  if ((&buf[buf_idx]) != 0)
  {
    buf[len + buf_idx] = '\0';
  }
  fclose(f);
  return buf;
}


/*** DEPENDENCIES:
int xasprintf(char **ret, const char *fmt, ...)
{
  va_list ap;
  int i;
  __builtin_va_start(ap);
  i = xvasprintf(ret, fmt, ap);
  ;
  return i;
}


----------------------------
void *xrealloc(void *ptr, size_t size)
{
  return xreallocarray(ptr, 1, size);
}


----------------------------
***/


char *osdep_get_cwd(int fd)
{
  static char target[MAXPATHLEN + 1];
  char *path;
  pid_t pgrp;
  pid_t sid;
  ssize_t n;
  if ((pgrp = tcgetpgrp(fd)) == (-1))
  {
    return 0;
  }
  xasprintf(&path, "/proc/%lld/cwd", (long long) pgrp);
  n = readlink(path, target, MAXPATHLEN);
  free(path);
  if ((n == (-1)) && (ioctl(fd, TIOCGSID, &sid) != (-1)))
  {
    xasprintf(&path, "/proc/%lld/cwd", (long long) sid);
    n = readlink(path, target, MAXPATHLEN);
    free(path);
  }
  if (n > 0)
  {
    target[n] = '\0';
    return target;
  }
  return 0;
}


/*** DEPENDENCIES:
int xasprintf(char **ret, const char *fmt, ...)
{
  va_list ap;
  int i;
  __builtin_va_start(ap);
  i = xvasprintf(ret, fmt, ap);
  ;
  return i;
}


----------------------------
***/


struct event_base *osdep_event_init(void)
{
  struct event_base *base;
  unsigned int base_idx = 0;
  setenv("EVENT_NOEPOLL", "1", 1);
  base_idx = event_init();
  unsetenv("EVENT_NOEPOLL");
  return base;
}


/*** DEPENDENCIES:
***/


