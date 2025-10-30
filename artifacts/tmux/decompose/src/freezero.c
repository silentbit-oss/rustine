void freezero(void *ptr, size_t size)
{
  if (ptr != 0)
  {
    memset(ptr, 0, size);
    free(ptr);
  }
}


/*** DEPENDENCIES:
***/


