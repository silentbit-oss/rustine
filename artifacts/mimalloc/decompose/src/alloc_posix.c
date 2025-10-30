int mi_wdupenv_s(unsigned short **buf, size_t *size, const unsigned short *name)
{
  if ((buf == 0) || (name == 0))
  {
    return 22;
  }
  if (size != 0)
  {
    *size = 0;
  }
  *buf = 0;
  return 22;
}


/*** DEPENDENCIES:
***/


void *mi__expand(void *p, size_t newsize)
{
  void *res = mi_expand(p, newsize);
  if (res == 0)
  {
    errno = 12;
  }
  return res;
}


/*** DEPENDENCIES:
void *mi_expand(void *p, size_t newsize)
{
  (void) p;
  (void) newsize;
  return 0;
}


----------------------------
***/


size_t mi_malloc_size(const void *p)
{
  return mi_usable_size(p);
}


/*** DEPENDENCIES:
size_t mi_usable_size(const void *p)
{
  return _mi_usable_size(p, "mi_usable_size");
}


----------------------------
***/


size_t mi_malloc_good_size(size_t size)
{
  return mi_good_size(size);
}


/*** DEPENDENCIES:
size_t mi_good_size(size_t size)
{
  if (size <= ((1UL << (3 + (13 + 3))) / 8))
  {
    return _mi_bin_size(mi_bin(size + (sizeof(mi_padding_t))));
  }
  else
  {
    return _mi_align_up(size + (sizeof(mi_padding_t)), _mi_os_page_size());
  }
}


----------------------------
***/


size_t mi_malloc_usable_size(const void *p)
{
  return mi_usable_size(p);
}


/*** DEPENDENCIES:
size_t mi_usable_size(const void *p)
{
  return _mi_usable_size(p, "mi_usable_size");
}


----------------------------
***/


void *mi_reallocarray(void *p, size_t count, size_t size)
{
  void *newp = mi_reallocn(p, count, size);
  if (newp == 0)
  {
    errno = 12;
  }
  return newp;
}


/*** DEPENDENCIES:
void *mi_reallocn(void *p, size_t count, size_t size)
{
  return mi_heap_reallocn(mi_prim_get_default_heap(), p, count, size);
}


----------------------------
***/


void *mi_aligned_recalloc(void *p, size_t newcount, size_t size, size_t alignment)
{
  return mi_recalloc_aligned(p, newcount, size, alignment);
}


/*** DEPENDENCIES:
void *mi_recalloc_aligned(void *p, size_t newcount, size_t size, size_t alignment)
{
  return mi_heap_recalloc_aligned(mi_prim_get_default_heap(), p, newcount, size, alignment);
}


----------------------------
***/


void *mi_aligned_offset_recalloc(void *p, size_t newcount, size_t size, size_t alignment, size_t offset)
{
  return mi_recalloc_aligned_at(p, newcount, size, alignment, offset);
}


/*** DEPENDENCIES:
void *mi_recalloc_aligned_at(void *p, size_t newcount, size_t size, size_t alignment, size_t offset)
{
  return mi_heap_recalloc_aligned_at(mi_prim_get_default_heap(), p, newcount, size, alignment, offset);
}


----------------------------
***/


unsigned char *mi_mbsdup(const unsigned char *s)
{
  return (unsigned char *) mi_strdup((const char *) s);
}


/*** DEPENDENCIES:
char *mi_strdup(const char *s)
{
  return mi_heap_strdup(mi_prim_get_default_heap(), s);
}


----------------------------
***/


void mi_cfree(void *p)
{
  if (mi_is_in_heap_region(p))
  {
    mi_free(p);
  }
}


/*** DEPENDENCIES:
bool mi_is_in_heap_region(const void *p)
{
  return mi_is_valid_pointer(p);
}


----------------------------
None
----------------------------
***/


void *mi_memalign(size_t alignment, size_t size)
{
  void *p = mi_malloc_aligned(size, alignment);
  ((((uintptr_t) p) % alignment) == 0) ? ((void) 0) : (_mi_assert_fail("((uintptr_t)p % alignment) == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-posix.c", 71, __func__));
  return p;
}


/*** DEPENDENCIES:
void *mi_malloc_aligned(size_t size, size_t alignment)
{
  return mi_heap_malloc_aligned(mi_prim_get_default_heap(), size, alignment);
}


----------------------------
None
----------------------------
***/


void *mi_valloc(size_t size)
{
  return mi_memalign(_mi_os_page_size(), size);
}


/*** DEPENDENCIES:
size_t _mi_os_page_size(void)
{
  return mi_os_mem_config.page_size;
}


----------------------------
void *mi_memalign(size_t alignment, size_t size)
{
  void *p = mi_malloc_aligned(size, alignment);
  ((((uintptr_t) p) % alignment) == 0) ? ((void) 0) : (_mi_assert_fail("((uintptr_t)p % alignment) == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-posix.c", 71, __func__));
  return p;
}


----------------------------
***/


void *mi_aligned_alloc(size_t alignment, size_t size)
{
  void *p = mi_malloc_aligned(size, alignment);
  ((((uintptr_t) p) % alignment) == 0) ? ((void) 0) : (_mi_assert_fail("((uintptr_t)p % alignment) == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-posix.c", 98, __func__));
  return p;
}


/*** DEPENDENCIES:
void *mi_malloc_aligned(size_t size, size_t alignment)
{
  return mi_heap_malloc_aligned(mi_prim_get_default_heap(), size, alignment);
}


----------------------------
None
----------------------------
***/


int mi_reallocarr(void *p, size_t count, size_t size)
{
  (p != 0) ? ((void) 0) : (_mi_assert_fail("p != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-posix.c", 109, __func__));
  if (p == 0)
  {
    errno = 22;
    return 22;
  }
  void **op = (void **) p;
  void *newp = mi_reallocarray(*op, count, size);
  if (__builtin_expect(!(!(newp == 0)), 0))
  {
    return errno;
  }
  *op = newp;
  return 0;
}


/*** DEPENDENCIES:
void *mi_reallocarray(void *p, size_t count, size_t size)
{
  void *newp = mi_reallocn(p, count, size);
  if (newp == 0)
  {
    errno = 12;
  }
  return newp;
}


----------------------------
None
----------------------------
***/


unsigned short *mi_wcsdup(const unsigned short *s)
{
  if (s == 0)
  {
    return 0;
  }
  size_t len;
  for (len = 0; s[len] != 0; len += 1)
  {
  }

  size_t size = (len + 1) * (sizeof(unsigned short));
  unsigned short *p = (unsigned short *) mi_malloc(size);
  if (p != 0)
  {
    _mi_memcpy(p, s, size);
  }
  return p;
}


/*** DEPENDENCIES:
inline static void _mi_memcpy(void *dst, const void *src, size_t n)
{
  memcpy(dst, src, n);
}


----------------------------
inline extern void *mi_malloc(size_t size)
{
  return mi_heap_malloc(mi_prim_get_default_heap(), size);
}


----------------------------
***/


int mi_dupenv_s(char **buf, size_t *size, const char *name)
{
  if ((buf == 0) || (name == 0))
  {
    return 22;
  }
  if (size != 0)
  {
    *size = 0;
  }
  char *p = getenv(name);
  if (p == 0)
  {
    *buf = 0;
  }
  else
  {
    *buf = mi_strdup(p);
    if ((*buf) == 0)
    {
      return 12;
    }
    if (size != 0)
    {
      *size = _mi_strlen(p);
    }
  }
  return 0;
}


/*** DEPENDENCIES:
size_t _mi_strlen(const char *s)
{
  if (s == 0)
  {
    return 0;
  }
  size_t len = 0;
  while (s[len] != 0)
  {
    len += 1;
  }

  return len;
}


----------------------------
char *mi_strdup(const char *s)
{
  return mi_heap_strdup(mi_prim_get_default_heap(), s);
}


----------------------------
***/


int mi_posix_memalign(void **p, size_t alignment, size_t size)
{
  if (p == 0)
  {
    return 22;
  }
  if ((alignment % (sizeof(void *))) != 0)
  {
    return 22;
  }
  if ((alignment == 0) || (!_mi_is_power_of_two(alignment)))
  {
    return 22;
  }
  void *q = mi_malloc_aligned(size, alignment);
  if ((q == 0) && (size != 0))
  {
    return 12;
  }
  ((((uintptr_t) q) % alignment) == 0) ? ((void) 0) : (_mi_assert_fail("((uintptr_t)q % alignment) == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-posix.c", 64, __func__));
  *p = q;
  return 0;
}


/*** DEPENDENCIES:
inline static bool _mi_is_power_of_two(uintptr_t x)
{
  return (x & (x - 1)) == 0;
}


----------------------------
void *mi_malloc_aligned(size_t size, size_t alignment)
{
  return mi_heap_malloc_aligned(mi_prim_get_default_heap(), size, alignment);
}


----------------------------
None
----------------------------
***/


void *mi_pvalloc(size_t size)
{
  size_t psize = _mi_os_page_size();
  if (size >= (SIZE_MAX - psize))
  {
    return 0;
  }
  size_t asize = _mi_align_up(size, psize);
  return mi_malloc_aligned(asize, psize);
}


/*** DEPENDENCIES:
inline static uintptr_t _mi_align_up(uintptr_t sz, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 386, __func__));
  uintptr_t mask = alignment - 1;
  if ((alignment & mask) == 0)
  {
    return (sz + mask) & (~mask);
  }
  else
  {
    return ((sz + mask) / alignment) * alignment;
  }
}


----------------------------
size_t _mi_os_page_size(void)
{
  return mi_os_mem_config.page_size;
}


----------------------------
void *mi_malloc_aligned(size_t size, size_t alignment)
{
  return mi_heap_malloc_aligned(mi_prim_get_default_heap(), size, alignment);
}


----------------------------
***/


