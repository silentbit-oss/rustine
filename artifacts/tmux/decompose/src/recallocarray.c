void *recallocarray(void *ptr, size_t oldnmemb, size_t newnmemb, size_t size)
{
  size_t oldsize;
  size_t newsize;
  void *newptr;
  unsigned int newptr_idx = 0;
  if (ptr == 0)
  {
    return calloc(newnmemb, size);
  }
  if ((((newnmemb >= (((size_t) 1) << ((sizeof(size_t)) * 4))) || (size >= (((size_t) 1) << ((sizeof(size_t)) * 4)))) && (newnmemb > 0)) && ((SIZE_MAX / newnmemb) < size))
  {
    errno = ENOMEM;
    return 0;
  }
  newsize = newnmemb * size;
  if ((((oldnmemb >= (((size_t) 1) << ((sizeof(size_t)) * 4))) || (size >= (((size_t) 1) << ((sizeof(size_t)) * 4)))) && (oldnmemb > 0)) && ((SIZE_MAX / oldnmemb) < size))
  {
    errno = EINVAL;
    return 0;
  }
  oldsize = oldnmemb * size;
  if (newsize <= oldsize)
  {
    size_t d = oldsize - newsize;
    if ((d < (oldsize / 2)) && (d < ((size_t) getpagesize())))
    {
      memset(((char *) ptr) + newsize, 0, d);
      return ptr;
    }
  }
  newptr_idx = malloc(newsize);
  if ((&newptr[newptr_idx]) == 0)
  {
    return 0;
  }
  if (newsize > oldsize)
  {
    memcpy(newptr, ptr, oldsize);
    memset(((char *) newptr) + oldsize, 0, newsize - oldsize);
  }
  else
    memcpy(newptr, ptr, newsize);
  explicit_bzero(ptr, oldsize);
  free(ptr);
  return newptr;
}


/*** DEPENDENCIES:
***/


