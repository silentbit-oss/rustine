void *BrotliAllocate(MemoryManager *m, size_t n)
{
  void *result = m->alloc_func(m->opaque, n);
  if (!result)
  {
    exit(1);
  }
  return result;
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
***/


void BrotliFree(MemoryManager *m, void *p)
{
  m->free_func(m->opaque, p);
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
***/


void BrotliWipeOutMemoryManager(MemoryManager *m)
{
  (void) m;
}


/*** DEPENDENCIES:
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
***/


void BrotliInitMemoryManager(MemoryManager *m, brotli_alloc_func alloc_func, brotli_free_func free_func, void *opaque)
{
  if (!alloc_func)
  {
    m->alloc_func = BrotliDefaultAllocFunc;
    m->free_func = BrotliDefaultFreeFunc;
    m->opaque = 0;
  }
  else
  {
    m->alloc_func = alloc_func;
    m->free_func = free_func;
    m->opaque = opaque;
  }
}


/*** DEPENDENCIES:
typedef void (*brotli_free_func)(void *opaque, void *address)
----------------------------
void BrotliDefaultFreeFunc(void *opaque, void *address)
{
  (void) opaque;
  free(address);
}


----------------------------
typedef void *(*brotli_alloc_func)(void *opaque, size_t size)
----------------------------
typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
----------------------------
void *BrotliDefaultAllocFunc(void *opaque, size_t size)
{
  (void) opaque;
  return malloc(size);
}


----------------------------
***/


