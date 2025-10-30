void *BrotliDefaultAllocFunc(void *opaque, size_t size)
{
  (void) opaque;
  return malloc(size);
}


/*** DEPENDENCIES:
***/


void BrotliDefaultFreeFunc(void *opaque, void *address)
{
  (void) opaque;
  free(address);
}


/*** DEPENDENCIES:
***/


