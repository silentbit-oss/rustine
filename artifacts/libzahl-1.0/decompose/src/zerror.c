enum zerror
{
  ZERROR_ERRNO_SET = 0
}
/*** DEPENDENCIES:
***/


enum zerror zerror(const char **desc)
{
  if (libzahl_error >= 0)
  {
    if (desc)
    {
      *desc = strerror(libzahl_error);
    }
    errno = libzahl_error;
    return ZERROR_ERRNO_SET;
  }
  else
  {
    if (desc)
    {
      abort();
    }
    return -libzahl_error;
  }
}


/*** DEPENDENCIES:
extern int libzahl_error
----------------------------
***/


