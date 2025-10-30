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


/*** DEPENDENCIES:
***/


