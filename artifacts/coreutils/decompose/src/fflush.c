static void update_fpos_cache(FILE *fp, off_t pos)
{
}


/*** DEPENDENCIES:
***/


static void clear_ungetc_buffer(FILE *fp)
{
  fseeko(fp, 0, 1);
}


/*** DEPENDENCIES:
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


----------------------------
***/


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


/*** DEPENDENCIES:
static void clear_ungetc_buffer(FILE *fp)
{
  fseeko(fp, 0, 1);
}


----------------------------
static void update_fpos_cache(FILE *fp, off_t pos)
{
}


----------------------------
***/


