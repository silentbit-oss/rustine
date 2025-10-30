char *fgetln(FILE *fp, size_t *len)
{
  static char *buf = 0;
  unsigned int buf_idx = 0;
  static size_t bufsz = 0;
  size_t r = 0;
  char *p;
  unsigned int p_idx = 0;
  int c;
  int e;
  if ((!fp) || (!len))
  {
    errno = EINVAL;
    return 0;
  }
  if (!(&buf[buf_idx]))
  {
    if (!(buf_idx = calloc(1, 1024)))
    {
      return 0;
    }
    bufsz = 1024;
  }
  while ((c = getc(fp)) != EOF)
  {
    buf[r + buf_idx] = c;
    r += 1;
    if (r == bufsz)
    {
      if (!(p_idx = reallocarray(buf, 2, bufsz)))
      {
        e = errno;
        free(buf);
        errno = e;
        buf_idx = 0, bufsz = 0;
        return 0;
      }
      buf_idx = &p[p_idx], bufsz = 2 * bufsz;
    }
    if (c == '\n')
    {
      break;
    }
  }

  return (*len = r) ? (buf) : (0);
}


/*** DEPENDENCIES:
***/


