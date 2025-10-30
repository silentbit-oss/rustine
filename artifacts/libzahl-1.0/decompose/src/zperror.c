void zperror(const char *prefix)
{
  if (libzahl_error >= 0)
  {
    errno = libzahl_error;
    perror(prefix);
  }
  else
  {
    abort();
  }
}


/*** DEPENDENCIES:
extern int libzahl_error
----------------------------
***/


