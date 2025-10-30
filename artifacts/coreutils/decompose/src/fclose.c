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


/*** DEPENDENCIES:
***/


