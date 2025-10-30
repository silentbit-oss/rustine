typedef struct MemoryManager
{
  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void *opaque;
} MemoryManager
/*** DEPENDENCIES:
typedef void *(*brotli_alloc_func)(void *opaque, size_t size)
----------------------------
typedef void (*brotli_free_func)(void *opaque, void *address)
----------------------------
***/


