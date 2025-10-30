static bool mi_malloc_is_naturally_aligned(size_t size, size_t alignment)
{
  (_mi_is_power_of_two(alignment) && (alignment > 0)) ? ((void) 0) : (_mi_assert_fail("_mi_is_power_of_two(alignment) && (alignment > 0)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 20, __func__));
  if (alignment > size)
  {
    return 0;
  }
  if (alignment <= 16)
  {
    return 1;
  }
  const size_t bsize = mi_good_size(size);
  return (bsize <= ((1UL << (3 + (13 + 3))) / 8)) && ((bsize & (alignment - 1)) == 0);
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
inline static bool _mi_is_power_of_two(uintptr_t x)
{
  return (x & (x - 1)) == 0;
}


----------------------------
None
----------------------------
***/


static void *mi_heap_malloc_zero_no_guarded(mi_heap_t *heap, size_t size, bool zero)
{
  return _mi_heap_malloc_zero(heap, size, zero);
}


/*** DEPENDENCIES:
inline extern void *_mi_heap_malloc_zero(mi_heap_t *heap, size_t size, bool zero)
{
  return _mi_heap_malloc_zero_ex(heap, size, zero, 0);
}


----------------------------
None
----------------------------
***/


static void *mi_heap_malloc_zero_aligned_at_overalloc(mi_heap_t * const heap, const size_t size, const size_t alignment, const size_t offset, const bool zero)
{
  (size <= (PTRDIFF_MAX - (sizeof(mi_padding_t)))) ? ((void) 0) : (_mi_assert_fail("size <= (MI_MAX_ALLOC_SIZE - MI_PADDING_SIZE)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 57, __func__));
  ((alignment != 0) && _mi_is_power_of_two(alignment)) ? ((void) 0) : (_mi_assert_fail("alignment != 0 && _mi_is_power_of_two(alignment)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 58, __func__));
  void *p;
  unsigned int p_idx = 0;
  size_t oversize;
  if (__builtin_expect(!(!(alignment > ((1UL << (9 + (13 + 3))) >> 1))), 0))
  {
    if (__builtin_expect(!(!(offset != 0)), 0))
    {
      _mi_error_message(75, "aligned allocation with a very large alignment cannot be used with an alignment offset (size %zu, alignment %zu, offset %zu)\n", size, alignment, offset);
      return 0;
    }
    oversize = (size <= (128 * (sizeof(void *)))) ? ((128 * (sizeof(void *))) + 1) : (size);
    p_idx = _mi_heap_malloc_zero_ex(heap, oversize, 0, alignment);
    if ((&p[p_idx]) == 0)
    {
      return 0;
    }
  }
  else
  {
    oversize = (((size < 16) ? (16) : (size)) + alignment) - 1;
    p_idx = mi_heap_malloc_zero_no_guarded(heap, oversize, zero);
    if ((&p[p_idx]) == 0)
    {
      return 0;
    }
  }
  mi_page_t *page = _mi_ptr_page(p);
  const uintptr_t align_mask = alignment - 1;
  const uintptr_t poffset = (((uintptr_t) p) + offset) & align_mask;
  const uintptr_t adjust = (poffset == 0) ? (0) : (alignment - poffset);
  (adjust < alignment) ? ((void) 0) : (_mi_assert_fail("adjust < alignment", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 91, __func__));
  void *aligned_p = (void *) (((uintptr_t) p) + adjust);
  if (aligned_p != (&p[p_idx]))
  {
    mi_page_set_has_aligned(page, 1);
    _mi_padding_shrink(page, (mi_block_t *) p, adjust + size);
  }
  (mi_page_usable_block_size(page) >= (adjust + size)) ? ((void) 0) : (_mi_assert_fail("mi_page_usable_block_size(page) >= adjust + size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 106, __func__));
  (((((uintptr_t) aligned_p) + offset) % alignment) == 0) ? ((void) 0) : (_mi_assert_fail("((uintptr_t)aligned_p + offset) % alignment == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 107, __func__));
  (mi_usable_size(aligned_p) >= size) ? ((void) 0) : (_mi_assert_fail("mi_usable_size(aligned_p)>=size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 108, __func__));
  (mi_usable_size(p) == (mi_usable_size(aligned_p) + adjust)) ? ((void) 0) : (_mi_assert_fail("mi_usable_size(p) == mi_usable_size(aligned_p)+adjust", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 109, __func__));
  mi_page_t * const apage = _mi_ptr_page(aligned_p);
  void *unalign_p = _mi_page_ptr_unalign(apage, aligned_p);
  ((&p[p_idx]) == unalign_p) ? ((void) 0) : (_mi_assert_fail("p == unalign_p", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 113, __func__));
  if (alignment > ((1UL << (9 + (13 + 3))) >> 1))
  {
    ;
    if (zero)
    {
      _mi_memzero_aligned(aligned_p, mi_usable_size(aligned_p));
    }
  }
  if ((&p[p_idx]) != aligned_p)
  {
    ;
  }
  return aligned_p;
}


/*** DEPENDENCIES:
inline extern void *_mi_heap_malloc_zero_ex(mi_heap_t *heap, size_t size, bool zero, size_t huge_alignment)
{
  if (__builtin_expect(!(!(size <= (128 * (sizeof(void *))))), 1))
  {
    (huge_alignment == 0) ? ((void) 0) : (_mi_assert_fail("huge_alignment == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 172, __func__));
    return mi_heap_malloc_small_zero(heap, size, zero);
  }
  else
  {
    (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 182, __func__));
    ((heap->thread_id == 0) || (heap->thread_id == _mi_thread_id())) ? ((void) 0) : (_mi_assert_fail("heap->thread_id == 0 || heap->thread_id == _mi_thread_id()", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 183, __func__));
    void * const p = _mi_malloc_generic(heap, size + (sizeof(mi_padding_t)), zero, huge_alignment);
    if (p != 0)
    {
      (mi_usable_size(p) == size) ? ((void) 0) : (_mi_assert_fail("mi_usable_size(p)==(size)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 185, __func__));
      ;
    }
    ;
    return p;
  }
}


----------------------------
static void *mi_heap_malloc_zero_no_guarded(mi_heap_t *heap, size_t size, bool zero)
{
  return _mi_heap_malloc_zero(heap, size, zero);
}


----------------------------
mi_block_t *_mi_page_ptr_unalign(const mi_page_t *page, const void *p)
{
  ((page != 0) && (p != 0)) ? ((void) 0) : (_mi_assert_fail("page!=NULL && p!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 59, __func__));
  size_t diff = ((uint8_t *) p) - page->page_start;
  size_t adjust;
  if (__builtin_expect(!(!(page->block_size_shift != 0)), 1))
  {
    adjust = diff & ((((size_t) 1) << page->block_size_shift) - 1);
  }
  else
  {
    adjust = diff % mi_page_block_size(page);
  }
  return (mi_block_t *) (((uintptr_t) p) - adjust);
}


----------------------------
void _mi_error_message(int err, const char *fmt, ...)
{
  va_list args;
  __builtin_va_start(args);
  mi_show_error_message(fmt, args);
  ;
  if (mi_error_handler != 0)
  {
    mi_error_handler(err, atomic_load_explicit(&mi_error_arg, memory_order_acquire));
  }
  else
  {
    mi_error_default(err);
  }
}


----------------------------
None
----------------------------
inline static bool _mi_is_power_of_two(uintptr_t x)
{
  return (x & (x - 1)) == 0;
}


----------------------------
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
inline static void mi_page_set_has_aligned(mi_page_t *page, bool has_aligned)
{
  page->flags.x.has_aligned = has_aligned;
}


----------------------------
inline static void _mi_memzero_aligned(void *dst, size_t n)
{
  ((((uintptr_t) dst) % (1 << 3)) == 0) ? ((void) 0) : (_mi_assert_fail("(uintptr_t)dst % MI_INTPTR_SIZE == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 1135, __func__));
  void *adst = __builtin_assume_aligned(dst, 1 << 3);
  _mi_memzero(adst, n);
}


----------------------------
void _mi_padding_shrink(const mi_page_t *page, const mi_block_t *block, const size_t min_size)
{
  size_t bsize;
  size_t delta;
  bool ok = mi_page_decode_padding(page, block, &delta, &bsize);
  (ok) ? ((void) 0) : (_mi_assert_fail("ok", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 457, __func__));
  if ((!ok) || ((bsize - delta) >= min_size))
  {
    return;
  }
  (bsize >= min_size) ? ((void) 0) : (_mi_assert_fail("bsize >= min_size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 459, __func__));
  if (bsize < min_size)
  {
    return;
  }
  size_t new_delta = bsize - min_size;
  (new_delta < bsize) ? ((void) 0) : (_mi_assert_fail("new_delta < bsize", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 462, __func__));
  mi_padding_t *padding = (mi_padding_t *) (((uint8_t *) block) + bsize);
  ;
  padding->delta = (uint32_t) new_delta;
  ;
}


----------------------------
size_t mi_usable_size(const void *p)
{
  return _mi_usable_size(p, "mi_usable_size");
}


----------------------------
inline static mi_page_t *_mi_ptr_page(void *p)
{
  (p != 0) ? ((void) 0) : (_mi_assert_fail("p!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 585, __func__));
  return _mi_segment_page_of(_mi_ptr_segment(p), p);
}


----------------------------
inline static size_t mi_page_usable_block_size(const mi_page_t *page)
{
  return mi_page_block_size(page) - (sizeof(mi_padding_t));
}


----------------------------
None
----------------------------
***/


static void *mi_heap_malloc_zero_aligned_at_generic(mi_heap_t * const heap, const size_t size, const size_t alignment, const size_t offset, const bool zero)
{
  ((alignment != 0) && _mi_is_power_of_two(alignment)) ? ((void) 0) : (_mi_assert_fail("alignment != 0 && _mi_is_power_of_two(alignment)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 137, __func__));
  if (__builtin_expect(!(!(size > (PTRDIFF_MAX - (sizeof(mi_padding_t))))), 0))
  {
    _mi_error_message(75, "aligned allocation request is too large (size %zu, alignment %zu)\n", size, alignment);
    return 0;
  }
  if ((offset == 0) && mi_malloc_is_naturally_aligned(size, alignment))
  {
    void *p = mi_heap_malloc_zero_no_guarded(heap, size, zero);
    ((p == 0) || ((((uintptr_t) p) % alignment) == 0)) ? ((void) 0) : (_mi_assert_fail("p == NULL || ((uintptr_t)p % alignment) == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 151, __func__));
    const bool is_aligned_or_null = (((uintptr_t) p) & (alignment - 1)) == 0;
    if (__builtin_expect(!(!is_aligned_or_null), 1))
    {
      return p;
    }
    else
    {
      (0) ? ((void) 0) : (_mi_assert_fail("false", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 158, __func__));
      mi_free(p);
    }
  }
  return mi_heap_malloc_zero_aligned_at_overalloc(heap, size, alignment, offset, zero);
}


/*** DEPENDENCIES:
static void *mi_heap_malloc_zero_no_guarded(mi_heap_t *heap, size_t size, bool zero)
{
  return _mi_heap_malloc_zero(heap, size, zero);
}


----------------------------
static void *mi_heap_malloc_zero_aligned_at_overalloc(mi_heap_t * const heap, const size_t size, const size_t alignment, const size_t offset, const bool zero)
{
  (size <= (PTRDIFF_MAX - (sizeof(mi_padding_t)))) ? ((void) 0) : (_mi_assert_fail("size <= (MI_MAX_ALLOC_SIZE - MI_PADDING_SIZE)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 57, __func__));
  ((alignment != 0) && _mi_is_power_of_two(alignment)) ? ((void) 0) : (_mi_assert_fail("alignment != 0 && _mi_is_power_of_two(alignment)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 58, __func__));
  void *p;
  unsigned int p_idx = 0;
  size_t oversize;
  if (__builtin_expect(!(!(alignment > ((1UL << (9 + (13 + 3))) >> 1))), 0))
  {
    if (__builtin_expect(!(!(offset != 0)), 0))
    {
      _mi_error_message(75, "aligned allocation with a very large alignment cannot be used with an alignment offset (size %zu, alignment %zu, offset %zu)\n", size, alignment, offset);
      return 0;
    }
    oversize = (size <= (128 * (sizeof(void *)))) ? ((128 * (sizeof(void *))) + 1) : (size);
    p_idx = _mi_heap_malloc_zero_ex(heap, oversize, 0, alignment);
    if ((&p[p_idx]) == 0)
    {
      return 0;
    }
  }
  else
  {
    oversize = (((size < 16) ? (16) : (size)) + alignment) - 1;
    p_idx = mi_heap_malloc_zero_no_guarded(heap, oversize, zero);
    if ((&p[p_idx]) == 0)
    {
      return 0;
    }
  }
  mi_page_t *page = _mi_ptr_page(p);
  const uintptr_t align_mask = alignment - 1;
  const uintptr_t poffset = (((uintptr_t) p) + offset) & align_mask;
  const uintptr_t adjust = (poffset == 0) ? (0) : (alignment - poffset);
  (adjust < alignment) ? ((void) 0) : (_mi_assert_fail("adjust < alignment", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 91, __func__));
  void *aligned_p = (void *) (((uintptr_t) p) + adjust);
  if (aligned_p != (&p[p_idx]))
  {
    mi_page_set_has_aligned(page, 1);
    _mi_padding_shrink(page, (mi_block_t *) p, adjust + size);
  }
  (mi_page_usable_block_size(page) >= (adjust + size)) ? ((void) 0) : (_mi_assert_fail("mi_page_usable_block_size(page) >= adjust + size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 106, __func__));
  (((((uintptr_t) aligned_p) + offset) % alignment) == 0) ? ((void) 0) : (_mi_assert_fail("((uintptr_t)aligned_p + offset) % alignment == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 107, __func__));
  (mi_usable_size(aligned_p) >= size) ? ((void) 0) : (_mi_assert_fail("mi_usable_size(aligned_p)>=size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 108, __func__));
  (mi_usable_size(p) == (mi_usable_size(aligned_p) + adjust)) ? ((void) 0) : (_mi_assert_fail("mi_usable_size(p) == mi_usable_size(aligned_p)+adjust", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 109, __func__));
  mi_page_t * const apage = _mi_ptr_page(aligned_p);
  void *unalign_p = _mi_page_ptr_unalign(apage, aligned_p);
  ((&p[p_idx]) == unalign_p) ? ((void) 0) : (_mi_assert_fail("p == unalign_p", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 113, __func__));
  if (alignment > ((1UL << (9 + (13 + 3))) >> 1))
  {
    ;
    if (zero)
    {
      _mi_memzero_aligned(aligned_p, mi_usable_size(aligned_p));
    }
  }
  if ((&p[p_idx]) != aligned_p)
  {
    ;
  }
  return aligned_p;
}


----------------------------
void _mi_error_message(int err, const char *fmt, ...)
{
  va_list args;
  __builtin_va_start(args);
  mi_show_error_message(fmt, args);
  ;
  if (mi_error_handler != 0)
  {
    mi_error_handler(err, atomic_load_explicit(&mi_error_arg, memory_order_acquire));
  }
  else
  {
    mi_error_default(err);
  }
}


----------------------------
None
----------------------------
None
----------------------------
inline static bool _mi_is_power_of_two(uintptr_t x)
{
  return (x & (x - 1)) == 0;
}


----------------------------
static bool mi_malloc_is_naturally_aligned(size_t size, size_t alignment)
{
  (_mi_is_power_of_two(alignment) && (alignment > 0)) ? ((void) 0) : (_mi_assert_fail("_mi_is_power_of_two(alignment) && (alignment > 0)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 20, __func__));
  if (alignment > size)
  {
    return 0;
  }
  if (alignment <= 16)
  {
    return 1;
  }
  const size_t bsize = mi_good_size(size);
  return (bsize <= ((1UL << (3 + (13 + 3))) / 8)) && ((bsize & (alignment - 1)) == 0);
}


----------------------------
None
----------------------------
***/


static void *mi_heap_malloc_zero_aligned_at(mi_heap_t * const heap, const size_t size, const size_t alignment, const size_t offset, const bool zero)
{
  if (__builtin_expect(!(!((alignment == 0) || (!_mi_is_power_of_two(alignment)))), 0))
  {
    _mi_error_message(75, "aligned allocation requires the alignment to be a power-of-two (size %zu, alignment %zu)\n", size, alignment);
    return 0;
  }
  if (__builtin_expect(!(!((size <= (128 * (sizeof(void *)))) && (alignment <= size))), 1))
  {
    const uintptr_t align_mask = alignment - 1;
    const size_t padsize = size + (sizeof(mi_padding_t));
    mi_page_t *page = _mi_heap_get_free_small_page(heap, padsize);
    if (__builtin_expect(!(!(page->free != 0)), 1))
    {
      const bool is_aligned = ((((uintptr_t) page->free) + offset) & align_mask) == 0;
      if (__builtin_expect(!(!is_aligned), 1))
      {
        void *p = (zero) ? (_mi_page_malloc_zeroed(heap, page, padsize)) : (_mi_page_malloc(heap, page, padsize));
        (p != 0) ? ((void) 0) : (_mi_assert_fail("p != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 195, __func__));
        (((((uintptr_t) p) + offset) % alignment) == 0) ? ((void) 0) : (_mi_assert_fail("((uintptr_t)p + offset) % alignment == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 196, __func__));
        if (p != 0)
        {
          (mi_usable_size(p) == size) ? ((void) 0) : (_mi_assert_fail("mi_usable_size(p)==(size)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 197, __func__));
          ;
        }
        ;
        return p;
      }
    }
  }
  return mi_heap_malloc_zero_aligned_at_generic(heap, size, alignment, offset, zero);
}


/*** DEPENDENCIES:
None
----------------------------
extern void *_mi_page_malloc_zeroed(mi_heap_t *heap, mi_page_t *page, size_t size)
{
  return _mi_page_malloc_zero(heap, page, size, 1);
}


----------------------------
void _mi_error_message(int err, const char *fmt, ...)
{
  va_list args;
  __builtin_va_start(args);
  mi_show_error_message(fmt, args);
  ;
  if (mi_error_handler != 0)
  {
    mi_error_handler(err, atomic_load_explicit(&mi_error_arg, memory_order_acquire));
  }
  else
  {
    mi_error_default(err);
  }
}


----------------------------
None
----------------------------
inline static mi_page_t *_mi_heap_get_free_small_page(mi_heap_t *heap, size_t size)
{
  (size <= ((128 * (sizeof(void *))) + (sizeof(mi_padding_t)))) ? ((void) 0) : (_mi_assert_fail("size <= (MI_SMALL_SIZE_MAX + MI_PADDING_SIZE)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 516, __func__));
  const size_t idx = _mi_wsize_from_size(size);
  (idx < ((128 + ((((sizeof(mi_padding_t)) + (1 << 3)) - 1) / (1 << 3))) + 1)) ? ((void) 0) : (_mi_assert_fail("idx < MI_PAGES_DIRECT", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 518, __func__));
  return heap->pages_free_direct[idx];
}


----------------------------
inline static bool _mi_is_power_of_two(uintptr_t x)
{
  return (x & (x - 1)) == 0;
}


----------------------------
typedef struct mi_page_s
{
  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed : 1;
  uint8_t is_zero_init : 1;
  uint8_t is_huge : 1;
  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero : 1;
  uint8_t retire_expire : 7;
  mi_block_t *free;
  mi_block_t *local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;
  size_t block_size;
  uint8_t *page_start;
  uintptr_t keys[2];
  _Atomic mi_thread_free_t xthread_free;
  _Atomic uintptr_t xheap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  void *padding[1];
} mi_page_t
----------------------------
size_t mi_usable_size(const void *p)
{
  return _mi_usable_size(p, "mi_usable_size");
}


----------------------------
static void *mi_heap_malloc_zero_aligned_at_generic(mi_heap_t * const heap, const size_t size, const size_t alignment, const size_t offset, const bool zero)
{
  ((alignment != 0) && _mi_is_power_of_two(alignment)) ? ((void) 0) : (_mi_assert_fail("alignment != 0 && _mi_is_power_of_two(alignment)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 137, __func__));
  if (__builtin_expect(!(!(size > (PTRDIFF_MAX - (sizeof(mi_padding_t))))), 0))
  {
    _mi_error_message(75, "aligned allocation request is too large (size %zu, alignment %zu)\n", size, alignment);
    return 0;
  }
  if ((offset == 0) && mi_malloc_is_naturally_aligned(size, alignment))
  {
    void *p = mi_heap_malloc_zero_no_guarded(heap, size, zero);
    ((p == 0) || ((((uintptr_t) p) % alignment) == 0)) ? ((void) 0) : (_mi_assert_fail("p == NULL || ((uintptr_t)p % alignment) == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 151, __func__));
    const bool is_aligned_or_null = (((uintptr_t) p) & (alignment - 1)) == 0;
    if (__builtin_expect(!(!is_aligned_or_null), 1))
    {
      return p;
    }
    else
    {
      (0) ? ((void) 0) : (_mi_assert_fail("false", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 158, __func__));
      mi_free(p);
    }
  }
  return mi_heap_malloc_zero_aligned_at_overalloc(heap, size, alignment, offset, zero);
}


----------------------------
None
----------------------------
***/


void *mi_heap_malloc_aligned_at(mi_heap_t *heap, size_t size, size_t alignment, size_t offset)
{
  return mi_heap_malloc_zero_aligned_at(heap, size, alignment, offset, 0);
}


/*** DEPENDENCIES:
static void *mi_heap_malloc_zero_aligned_at(mi_heap_t * const heap, const size_t size, const size_t alignment, const size_t offset, const bool zero)
{
  if (__builtin_expect(!(!((alignment == 0) || (!_mi_is_power_of_two(alignment)))), 0))
  {
    _mi_error_message(75, "aligned allocation requires the alignment to be a power-of-two (size %zu, alignment %zu)\n", size, alignment);
    return 0;
  }
  if (__builtin_expect(!(!((size <= (128 * (sizeof(void *)))) && (alignment <= size))), 1))
  {
    const uintptr_t align_mask = alignment - 1;
    const size_t padsize = size + (sizeof(mi_padding_t));
    mi_page_t *page = _mi_heap_get_free_small_page(heap, padsize);
    if (__builtin_expect(!(!(page->free != 0)), 1))
    {
      const bool is_aligned = ((((uintptr_t) page->free) + offset) & align_mask) == 0;
      if (__builtin_expect(!(!is_aligned), 1))
      {
        void *p = (zero) ? (_mi_page_malloc_zeroed(heap, page, padsize)) : (_mi_page_malloc(heap, page, padsize));
        (p != 0) ? ((void) 0) : (_mi_assert_fail("p != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 195, __func__));
        (((((uintptr_t) p) + offset) % alignment) == 0) ? ((void) 0) : (_mi_assert_fail("((uintptr_t)p + offset) % alignment == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 196, __func__));
        if (p != 0)
        {
          (mi_usable_size(p) == size) ? ((void) 0) : (_mi_assert_fail("mi_usable_size(p)==(size)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 197, __func__));
          ;
        }
        ;
        return p;
      }
    }
  }
  return mi_heap_malloc_zero_aligned_at_generic(heap, size, alignment, offset, zero);
}


----------------------------
None
----------------------------
***/


static void *mi_heap_realloc_zero_aligned_at(mi_heap_t *heap, void *p, size_t newsize, size_t alignment, size_t offset, bool zero)
{
  (alignment > 0) ? ((void) 0) : (_mi_assert_fail("alignment > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 277, __func__));
  if (alignment <= (sizeof(uintptr_t)))
  {
    return _mi_heap_realloc_zero(heap, p, newsize, zero);
  }
  if (p == 0)
  {
    return mi_heap_malloc_zero_aligned_at(heap, newsize, alignment, offset, zero);
  }
  size_t size = mi_usable_size(p);
  if (((newsize <= size) && (newsize >= (size - (size / 2)))) && (((((uintptr_t) p) + offset) % alignment) == 0))
  {
    return p;
  }
  else
  {
    void *newp = mi_heap_malloc_aligned_at(heap, newsize, alignment, offset);
    if (newp != 0)
    {
      if (zero && (newsize > size))
      {
        size_t start = (size >= (sizeof(intptr_t))) ? (size - (sizeof(intptr_t))) : (0);
        _mi_memzero(((uint8_t *) newp) + start, newsize - start);
      }
      _mi_memcpy_aligned(newp, p, (newsize > size) ? (size) : (newsize));
      mi_free(p);
    }
    return newp;
  }
}


/*** DEPENDENCIES:
inline static void _mi_memzero(void *dst, size_t n)
{
  memset(dst, 0, n);
}


----------------------------
None
----------------------------
None
----------------------------
static void *mi_heap_malloc_zero_aligned_at(mi_heap_t * const heap, const size_t size, const size_t alignment, const size_t offset, const bool zero)
{
  if (__builtin_expect(!(!((alignment == 0) || (!_mi_is_power_of_two(alignment)))), 0))
  {
    _mi_error_message(75, "aligned allocation requires the alignment to be a power-of-two (size %zu, alignment %zu)\n", size, alignment);
    return 0;
  }
  if (__builtin_expect(!(!((size <= (128 * (sizeof(void *)))) && (alignment <= size))), 1))
  {
    const uintptr_t align_mask = alignment - 1;
    const size_t padsize = size + (sizeof(mi_padding_t));
    mi_page_t *page = _mi_heap_get_free_small_page(heap, padsize);
    if (__builtin_expect(!(!(page->free != 0)), 1))
    {
      const bool is_aligned = ((((uintptr_t) page->free) + offset) & align_mask) == 0;
      if (__builtin_expect(!(!is_aligned), 1))
      {
        void *p = (zero) ? (_mi_page_malloc_zeroed(heap, page, padsize)) : (_mi_page_malloc(heap, page, padsize));
        (p != 0) ? ((void) 0) : (_mi_assert_fail("p != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 195, __func__));
        (((((uintptr_t) p) + offset) % alignment) == 0) ? ((void) 0) : (_mi_assert_fail("((uintptr_t)p + offset) % alignment == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 196, __func__));
        if (p != 0)
        {
          (mi_usable_size(p) == size) ? ((void) 0) : (_mi_assert_fail("mi_usable_size(p)==(size)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 197, __func__));
          ;
        }
        ;
        return p;
      }
    }
  }
  return mi_heap_malloc_zero_aligned_at_generic(heap, size, alignment, offset, zero);
}


----------------------------
size_t mi_usable_size(const void *p)
{
  return _mi_usable_size(p, "mi_usable_size");
}


----------------------------
void *_mi_heap_realloc_zero(mi_heap_t *heap, void *p, size_t newsize, bool zero)
{
  const size_t size = _mi_usable_size(p, "mi_realloc");
  if (__builtin_expect(!(!(((newsize <= size) && (newsize >= (size / 2))) && (newsize > 0))), 0))
  {
    (p != 0) ? ((void) 0) : (_mi_assert_fail("p!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 263, __func__));
    return p;
  }
  void *newp = mi_heap_malloc(heap, newsize);
  if (__builtin_expect(!(!(newp != 0)), 1))
  {
    if (zero && (newsize > size))
    {
      const size_t start = (size >= (sizeof(intptr_t))) ? (size - (sizeof(intptr_t))) : (0);
      _mi_memzero(((uint8_t *) newp) + start, newsize - start);
    }
    else
      if (newsize == 0)
    {
      ((uint8_t *) newp)[0] = 0;
    }
    if (__builtin_expect(!(!(p != 0)), 1))
    {
      const size_t copysize = (newsize > size) ? (size) : (newsize);
      ;
      _mi_memcpy(newp, p, copysize);
      mi_free(p);
    }
  }
  return newp;
}


----------------------------
void *mi_heap_malloc_aligned_at(mi_heap_t *heap, size_t size, size_t alignment, size_t offset)
{
  return mi_heap_malloc_zero_aligned_at(heap, size, alignment, offset, 0);
}


----------------------------
inline static void _mi_memcpy_aligned(void *dst, const void *src, size_t n)
{
  (((((uintptr_t) dst) % (1 << 3)) == 0) && ((((uintptr_t) src) % (1 << 3)) == 0)) ? ((void) 0) : (_mi_assert_fail("((uintptr_t)dst % MI_INTPTR_SIZE == 0) && ((uintptr_t)src % MI_INTPTR_SIZE == 0)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 1128, __func__));
  void *adst = __builtin_assume_aligned(dst, 1 << 3);
  const void *asrc = __builtin_assume_aligned(src, 1 << 3);
  _mi_memcpy(adst, asrc, n);
}


----------------------------
None
----------------------------
***/


static void *mi_heap_realloc_zero_aligned(mi_heap_t *heap, void *p, size_t newsize, size_t alignment, bool zero)
{
  (alignment > 0) ? ((void) 0) : (_mi_assert_fail("alignment > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 302, __func__));
  if (alignment <= (sizeof(uintptr_t)))
  {
    return _mi_heap_realloc_zero(heap, p, newsize, zero);
  }
  size_t offset = ((uintptr_t) p) % alignment;
  return mi_heap_realloc_zero_aligned_at(heap, p, newsize, alignment, offset, zero);
}


/*** DEPENDENCIES:
None
----------------------------
void *_mi_heap_realloc_zero(mi_heap_t *heap, void *p, size_t newsize, bool zero)
{
  const size_t size = _mi_usable_size(p, "mi_realloc");
  if (__builtin_expect(!(!(((newsize <= size) && (newsize >= (size / 2))) && (newsize > 0))), 0))
  {
    (p != 0) ? ((void) 0) : (_mi_assert_fail("p!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 263, __func__));
    return p;
  }
  void *newp = mi_heap_malloc(heap, newsize);
  if (__builtin_expect(!(!(newp != 0)), 1))
  {
    if (zero && (newsize > size))
    {
      const size_t start = (size >= (sizeof(intptr_t))) ? (size - (sizeof(intptr_t))) : (0);
      _mi_memzero(((uint8_t *) newp) + start, newsize - start);
    }
    else
      if (newsize == 0)
    {
      ((uint8_t *) newp)[0] = 0;
    }
    if (__builtin_expect(!(!(p != 0)), 1))
    {
      const size_t copysize = (newsize > size) ? (size) : (newsize);
      ;
      _mi_memcpy(newp, p, copysize);
      mi_free(p);
    }
  }
  return newp;
}


----------------------------
static void *mi_heap_realloc_zero_aligned_at(mi_heap_t *heap, void *p, size_t newsize, size_t alignment, size_t offset, bool zero)
{
  (alignment > 0) ? ((void) 0) : (_mi_assert_fail("alignment > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 277, __func__));
  if (alignment <= (sizeof(uintptr_t)))
  {
    return _mi_heap_realloc_zero(heap, p, newsize, zero);
  }
  if (p == 0)
  {
    return mi_heap_malloc_zero_aligned_at(heap, newsize, alignment, offset, zero);
  }
  size_t size = mi_usable_size(p);
  if (((newsize <= size) && (newsize >= (size - (size / 2)))) && (((((uintptr_t) p) + offset) % alignment) == 0))
  {
    return p;
  }
  else
  {
    void *newp = mi_heap_malloc_aligned_at(heap, newsize, alignment, offset);
    if (newp != 0)
    {
      if (zero && (newsize > size))
      {
        size_t start = (size >= (sizeof(intptr_t))) ? (size - (sizeof(intptr_t))) : (0);
        _mi_memzero(((uint8_t *) newp) + start, newsize - start);
      }
      _mi_memcpy_aligned(newp, p, (newsize > size) ? (size) : (newsize));
      mi_free(p);
    }
    return newp;
  }
}


----------------------------
None
----------------------------
***/


void *mi_heap_rezalloc_aligned(mi_heap_t *heap, void *p, size_t newsize, size_t alignment)
{
  return mi_heap_realloc_zero_aligned(heap, p, newsize, alignment, 1);
}


/*** DEPENDENCIES:
static void *mi_heap_realloc_zero_aligned(mi_heap_t *heap, void *p, size_t newsize, size_t alignment, bool zero)
{
  (alignment > 0) ? ((void) 0) : (_mi_assert_fail("alignment > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 302, __func__));
  if (alignment <= (sizeof(uintptr_t)))
  {
    return _mi_heap_realloc_zero(heap, p, newsize, zero);
  }
  size_t offset = ((uintptr_t) p) % alignment;
  return mi_heap_realloc_zero_aligned_at(heap, p, newsize, alignment, offset, zero);
}


----------------------------
None
----------------------------
***/


void *mi_heap_recalloc_aligned(mi_heap_t *heap, void *p, size_t newcount, size_t size, size_t alignment)
{
  size_t total;
  if (mi_count_size_overflow(newcount, size, &total))
  {
    return 0;
  }
  return mi_heap_rezalloc_aligned(heap, p, total, alignment);
}


/*** DEPENDENCIES:
inline static bool mi_count_size_overflow(size_t count, size_t size, size_t *total)
{
  if (count == 1)
  {
    *total = size;
    return 0;
  }
  else
    if (__builtin_expect(!(!mi_mul_overflow(count, size, total)), 0))
  {
    _mi_error_message(75, "allocation request is too large (%zu * %zu bytes)\n", count, size);
    *total = SIZE_MAX;
    return 1;
  }
  else
    return 0;
}


----------------------------
void *mi_heap_rezalloc_aligned(mi_heap_t *heap, void *p, size_t newsize, size_t alignment)
{
  return mi_heap_realloc_zero_aligned(heap, p, newsize, alignment, 1);
}


----------------------------
None
----------------------------
***/


void *mi_recalloc_aligned(void *p, size_t newcount, size_t size, size_t alignment)
{
  return mi_heap_recalloc_aligned(mi_prim_get_default_heap(), p, newcount, size, alignment);
}


/*** DEPENDENCIES:
void *mi_heap_recalloc_aligned(mi_heap_t *heap, void *p, size_t newcount, size_t size, size_t alignment)
{
  size_t total;
  if (mi_count_size_overflow(newcount, size, &total))
  {
    return 0;
  }
  return mi_heap_rezalloc_aligned(heap, p, total, alignment);
}


----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
***/


void *mi_heap_rezalloc_aligned_at(mi_heap_t *heap, void *p, size_t newsize, size_t alignment, size_t offset)
{
  return mi_heap_realloc_zero_aligned_at(heap, p, newsize, alignment, offset, 1);
}


/*** DEPENDENCIES:
static void *mi_heap_realloc_zero_aligned_at(mi_heap_t *heap, void *p, size_t newsize, size_t alignment, size_t offset, bool zero)
{
  (alignment > 0) ? ((void) 0) : (_mi_assert_fail("alignment > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 277, __func__));
  if (alignment <= (sizeof(uintptr_t)))
  {
    return _mi_heap_realloc_zero(heap, p, newsize, zero);
  }
  if (p == 0)
  {
    return mi_heap_malloc_zero_aligned_at(heap, newsize, alignment, offset, zero);
  }
  size_t size = mi_usable_size(p);
  if (((newsize <= size) && (newsize >= (size - (size / 2)))) && (((((uintptr_t) p) + offset) % alignment) == 0))
  {
    return p;
  }
  else
  {
    void *newp = mi_heap_malloc_aligned_at(heap, newsize, alignment, offset);
    if (newp != 0)
    {
      if (zero && (newsize > size))
      {
        size_t start = (size >= (sizeof(intptr_t))) ? (size - (sizeof(intptr_t))) : (0);
        _mi_memzero(((uint8_t *) newp) + start, newsize - start);
      }
      _mi_memcpy_aligned(newp, p, (newsize > size) ? (size) : (newsize));
      mi_free(p);
    }
    return newp;
  }
}


----------------------------
None
----------------------------
***/


void *mi_heap_recalloc_aligned_at(mi_heap_t *heap, void *p, size_t newcount, size_t size, size_t alignment, size_t offset)
{
  size_t total;
  if (mi_count_size_overflow(newcount, size, &total))
  {
    return 0;
  }
  return mi_heap_rezalloc_aligned_at(heap, p, total, alignment, offset);
}


/*** DEPENDENCIES:
inline static bool mi_count_size_overflow(size_t count, size_t size, size_t *total)
{
  if (count == 1)
  {
    *total = size;
    return 0;
  }
  else
    if (__builtin_expect(!(!mi_mul_overflow(count, size, total)), 0))
  {
    _mi_error_message(75, "allocation request is too large (%zu * %zu bytes)\n", count, size);
    *total = SIZE_MAX;
    return 1;
  }
  else
    return 0;
}


----------------------------
void *mi_heap_rezalloc_aligned_at(mi_heap_t *heap, void *p, size_t newsize, size_t alignment, size_t offset)
{
  return mi_heap_realloc_zero_aligned_at(heap, p, newsize, alignment, offset, 1);
}


----------------------------
None
----------------------------
***/


void *mi_recalloc_aligned_at(void *p, size_t newcount, size_t size, size_t alignment, size_t offset)
{
  return mi_heap_recalloc_aligned_at(mi_prim_get_default_heap(), p, newcount, size, alignment, offset);
}


/*** DEPENDENCIES:
void *mi_heap_recalloc_aligned_at(mi_heap_t *heap, void *p, size_t newcount, size_t size, size_t alignment, size_t offset)
{
  size_t total;
  if (mi_count_size_overflow(newcount, size, &total))
  {
    return 0;
  }
  return mi_heap_rezalloc_aligned_at(heap, p, total, alignment, offset);
}


----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
***/


void *mi_heap_malloc_aligned(mi_heap_t *heap, size_t size, size_t alignment)
{
  return mi_heap_malloc_aligned_at(heap, size, alignment, 0);
}


/*** DEPENDENCIES:
void *mi_heap_malloc_aligned_at(mi_heap_t *heap, size_t size, size_t alignment, size_t offset)
{
  return mi_heap_malloc_zero_aligned_at(heap, size, alignment, offset, 0);
}


----------------------------
None
----------------------------
***/


void *mi_malloc_aligned(size_t size, size_t alignment)
{
  return mi_heap_malloc_aligned(mi_prim_get_default_heap(), size, alignment);
}


/*** DEPENDENCIES:
void *mi_heap_malloc_aligned(mi_heap_t *heap, size_t size, size_t alignment)
{
  return mi_heap_malloc_aligned_at(heap, size, alignment, 0);
}


----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
***/


void *mi_malloc_aligned_at(size_t size, size_t alignment, size_t offset)
{
  return mi_heap_malloc_aligned_at(mi_prim_get_default_heap(), size, alignment, offset);
}


/*** DEPENDENCIES:
void *mi_heap_malloc_aligned_at(mi_heap_t *heap, size_t size, size_t alignment, size_t offset)
{
  return mi_heap_malloc_zero_aligned_at(heap, size, alignment, offset, 0);
}


----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
***/


void *mi_heap_zalloc_aligned_at(mi_heap_t *heap, size_t size, size_t alignment, size_t offset)
{
  return mi_heap_malloc_zero_aligned_at(heap, size, alignment, offset, 1);
}


/*** DEPENDENCIES:
static void *mi_heap_malloc_zero_aligned_at(mi_heap_t * const heap, const size_t size, const size_t alignment, const size_t offset, const bool zero)
{
  if (__builtin_expect(!(!((alignment == 0) || (!_mi_is_power_of_two(alignment)))), 0))
  {
    _mi_error_message(75, "aligned allocation requires the alignment to be a power-of-two (size %zu, alignment %zu)\n", size, alignment);
    return 0;
  }
  if (__builtin_expect(!(!((size <= (128 * (sizeof(void *)))) && (alignment <= size))), 1))
  {
    const uintptr_t align_mask = alignment - 1;
    const size_t padsize = size + (sizeof(mi_padding_t));
    mi_page_t *page = _mi_heap_get_free_small_page(heap, padsize);
    if (__builtin_expect(!(!(page->free != 0)), 1))
    {
      const bool is_aligned = ((((uintptr_t) page->free) + offset) & align_mask) == 0;
      if (__builtin_expect(!(!is_aligned), 1))
      {
        void *p = (zero) ? (_mi_page_malloc_zeroed(heap, page, padsize)) : (_mi_page_malloc(heap, page, padsize));
        (p != 0) ? ((void) 0) : (_mi_assert_fail("p != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 195, __func__));
        (((((uintptr_t) p) + offset) % alignment) == 0) ? ((void) 0) : (_mi_assert_fail("((uintptr_t)p + offset) % alignment == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 196, __func__));
        if (p != 0)
        {
          (mi_usable_size(p) == size) ? ((void) 0) : (_mi_assert_fail("mi_usable_size(p)==(size)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 197, __func__));
          ;
        }
        ;
        return p;
      }
    }
  }
  return mi_heap_malloc_zero_aligned_at_generic(heap, size, alignment, offset, zero);
}


----------------------------
None
----------------------------
***/


void *mi_heap_zalloc_aligned(mi_heap_t *heap, size_t size, size_t alignment)
{
  return mi_heap_zalloc_aligned_at(heap, size, alignment, 0);
}


/*** DEPENDENCIES:
void *mi_heap_zalloc_aligned_at(mi_heap_t *heap, size_t size, size_t alignment, size_t offset)
{
  return mi_heap_malloc_zero_aligned_at(heap, size, alignment, offset, 1);
}


----------------------------
None
----------------------------
***/


void *mi_zalloc_aligned(size_t size, size_t alignment)
{
  return mi_heap_zalloc_aligned(mi_prim_get_default_heap(), size, alignment);
}


/*** DEPENDENCIES:
void *mi_heap_zalloc_aligned(mi_heap_t *heap, size_t size, size_t alignment)
{
  return mi_heap_zalloc_aligned_at(heap, size, alignment, 0);
}


----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
***/


void *mi_zalloc_aligned_at(size_t size, size_t alignment, size_t offset)
{
  return mi_heap_zalloc_aligned_at(mi_prim_get_default_heap(), size, alignment, offset);
}


/*** DEPENDENCIES:
void *mi_heap_zalloc_aligned_at(mi_heap_t *heap, size_t size, size_t alignment, size_t offset)
{
  return mi_heap_malloc_zero_aligned_at(heap, size, alignment, offset, 1);
}


----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
***/


void *mi_heap_calloc_aligned_at(mi_heap_t *heap, size_t count, size_t size, size_t alignment, size_t offset)
{
  size_t total;
  if (mi_count_size_overflow(count, size, &total))
  {
    return 0;
  }
  return mi_heap_zalloc_aligned_at(heap, total, alignment, offset);
}


/*** DEPENDENCIES:
inline static bool mi_count_size_overflow(size_t count, size_t size, size_t *total)
{
  if (count == 1)
  {
    *total = size;
    return 0;
  }
  else
    if (__builtin_expect(!(!mi_mul_overflow(count, size, total)), 0))
  {
    _mi_error_message(75, "allocation request is too large (%zu * %zu bytes)\n", count, size);
    *total = SIZE_MAX;
    return 1;
  }
  else
    return 0;
}


----------------------------
void *mi_heap_zalloc_aligned_at(mi_heap_t *heap, size_t size, size_t alignment, size_t offset)
{
  return mi_heap_malloc_zero_aligned_at(heap, size, alignment, offset, 1);
}


----------------------------
None
----------------------------
***/


void *mi_heap_calloc_aligned(mi_heap_t *heap, size_t count, size_t size, size_t alignment)
{
  return mi_heap_calloc_aligned_at(heap, count, size, alignment, 0);
}


/*** DEPENDENCIES:
void *mi_heap_calloc_aligned_at(mi_heap_t *heap, size_t count, size_t size, size_t alignment, size_t offset)
{
  size_t total;
  if (mi_count_size_overflow(count, size, &total))
  {
    return 0;
  }
  return mi_heap_zalloc_aligned_at(heap, total, alignment, offset);
}


----------------------------
None
----------------------------
***/


void *mi_calloc_aligned(size_t count, size_t size, size_t alignment)
{
  return mi_heap_calloc_aligned(mi_prim_get_default_heap(), count, size, alignment);
}


/*** DEPENDENCIES:
void *mi_heap_calloc_aligned(mi_heap_t *heap, size_t count, size_t size, size_t alignment)
{
  return mi_heap_calloc_aligned_at(heap, count, size, alignment, 0);
}


----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
***/


void *mi_calloc_aligned_at(size_t count, size_t size, size_t alignment, size_t offset)
{
  return mi_heap_calloc_aligned_at(mi_prim_get_default_heap(), count, size, alignment, offset);
}


/*** DEPENDENCIES:
void *mi_heap_calloc_aligned_at(mi_heap_t *heap, size_t count, size_t size, size_t alignment, size_t offset)
{
  size_t total;
  if (mi_count_size_overflow(count, size, &total))
  {
    return 0;
  }
  return mi_heap_zalloc_aligned_at(heap, total, alignment, offset);
}


----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
***/


void *mi_heap_realloc_aligned(mi_heap_t *heap, void *p, size_t newsize, size_t alignment)
{
  return mi_heap_realloc_zero_aligned(heap, p, newsize, alignment, 0);
}


/*** DEPENDENCIES:
static void *mi_heap_realloc_zero_aligned(mi_heap_t *heap, void *p, size_t newsize, size_t alignment, bool zero)
{
  (alignment > 0) ? ((void) 0) : (_mi_assert_fail("alignment > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 302, __func__));
  if (alignment <= (sizeof(uintptr_t)))
  {
    return _mi_heap_realloc_zero(heap, p, newsize, zero);
  }
  size_t offset = ((uintptr_t) p) % alignment;
  return mi_heap_realloc_zero_aligned_at(heap, p, newsize, alignment, offset, zero);
}


----------------------------
None
----------------------------
***/


void *mi_realloc_aligned(void *p, size_t newsize, size_t alignment)
{
  return mi_heap_realloc_aligned(mi_prim_get_default_heap(), p, newsize, alignment);
}


/*** DEPENDENCIES:
void *mi_heap_realloc_aligned(mi_heap_t *heap, void *p, size_t newsize, size_t alignment)
{
  return mi_heap_realloc_zero_aligned(heap, p, newsize, alignment, 0);
}


----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
***/


void *mi_heap_realloc_aligned_at(mi_heap_t *heap, void *p, size_t newsize, size_t alignment, size_t offset)
{
  return mi_heap_realloc_zero_aligned_at(heap, p, newsize, alignment, offset, 0);
}


/*** DEPENDENCIES:
static void *mi_heap_realloc_zero_aligned_at(mi_heap_t *heap, void *p, size_t newsize, size_t alignment, size_t offset, bool zero)
{
  (alignment > 0) ? ((void) 0) : (_mi_assert_fail("alignment > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-aligned.c", 277, __func__));
  if (alignment <= (sizeof(uintptr_t)))
  {
    return _mi_heap_realloc_zero(heap, p, newsize, zero);
  }
  if (p == 0)
  {
    return mi_heap_malloc_zero_aligned_at(heap, newsize, alignment, offset, zero);
  }
  size_t size = mi_usable_size(p);
  if (((newsize <= size) && (newsize >= (size - (size / 2)))) && (((((uintptr_t) p) + offset) % alignment) == 0))
  {
    return p;
  }
  else
  {
    void *newp = mi_heap_malloc_aligned_at(heap, newsize, alignment, offset);
    if (newp != 0)
    {
      if (zero && (newsize > size))
      {
        size_t start = (size >= (sizeof(intptr_t))) ? (size - (sizeof(intptr_t))) : (0);
        _mi_memzero(((uint8_t *) newp) + start, newsize - start);
      }
      _mi_memcpy_aligned(newp, p, (newsize > size) ? (size) : (newsize));
      mi_free(p);
    }
    return newp;
  }
}


----------------------------
None
----------------------------
***/


void *mi_realloc_aligned_at(void *p, size_t newsize, size_t alignment, size_t offset)
{
  return mi_heap_realloc_aligned_at(mi_prim_get_default_heap(), p, newsize, alignment, offset);
}


/*** DEPENDENCIES:
void *mi_heap_realloc_aligned_at(mi_heap_t *heap, void *p, size_t newsize, size_t alignment, size_t offset)
{
  return mi_heap_realloc_zero_aligned_at(heap, p, newsize, alignment, offset, 0);
}


----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
***/


void *mi_rezalloc_aligned(void *p, size_t newsize, size_t alignment)
{
  return mi_heap_rezalloc_aligned(mi_prim_get_default_heap(), p, newsize, alignment);
}


/*** DEPENDENCIES:
void *mi_heap_rezalloc_aligned(mi_heap_t *heap, void *p, size_t newsize, size_t alignment)
{
  return mi_heap_realloc_zero_aligned(heap, p, newsize, alignment, 1);
}


----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
***/


void *mi_rezalloc_aligned_at(void *p, size_t newsize, size_t alignment, size_t offset)
{
  return mi_heap_rezalloc_aligned_at(mi_prim_get_default_heap(), p, newsize, alignment, offset);
}


/*** DEPENDENCIES:
void *mi_heap_rezalloc_aligned_at(mi_heap_t *heap, void *p, size_t newsize, size_t alignment, size_t offset)
{
  return mi_heap_realloc_zero_aligned_at(heap, p, newsize, alignment, offset, 1);
}


----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
***/


