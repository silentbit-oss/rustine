// element in merge of:  _mi_malloc_generic,_mi_page_malloc,_mi_page_malloc_zero
extern void *_mi_page_malloc(mi_heap_t *heap, mi_page_t *page, size_t size)
{
  return _mi_page_malloc_zero(heap, page, size, 0);
}


/*** DEPENDENCIES:
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
None
----------------------------
None
----------------------------
***/


// element in merge of:  _mi_malloc_generic,_mi_page_malloc,_mi_page_malloc_zero
inline extern void *_mi_page_malloc_zero(mi_heap_t *heap, mi_page_t *page, size_t size, bool zero)
{
  (size >= (sizeof(mi_padding_t))) ? ((void) 0) : (_mi_assert_fail("size >= MI_PADDING_SIZE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 33, __func__));
  ((page->block_size == 0) || (mi_page_block_size(page) >= size)) ? ((void) 0) : (_mi_assert_fail("page->block_size == 0 || mi_page_block_size(page) >= size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 34, __func__));
  mi_block_t * const block = page->free;
  if (__builtin_expect(!(!(block == 0)), 0))
  {
    return _mi_malloc_generic(heap, size, zero, 0);
  }
  ((block != 0) && (_mi_ptr_page(block) == page)) ? ((void) 0) : (_mi_assert_fail("block != NULL && _mi_ptr_page(block) == page", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 41, __func__));
  page->free = mi_block_next(page, block);
  page->used += 1;
  ((page->free == 0) || (_mi_ptr_page(page->free) == page)) ? ((void) 0) : (_mi_assert_fail("page->free == NULL || _mi_ptr_page(page->free) == page", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 46, __func__));
  ((page->block_size < 16) || _mi_is_aligned(block, 16)) ? ((void) 0) : (_mi_assert_fail("page->block_size < MI_MAX_ALIGN_SIZE || _mi_is_aligned(block, MI_MAX_ALIGN_SIZE)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 47, __func__));
  ;
  if (__builtin_expect(!(!zero), 0))
  {
    (page->block_size != 0) ? ((void) 0) : (_mi_assert_fail("page->block_size != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 62, __func__));
    (!mi_page_is_huge(page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_is_huge(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 63, __func__));
    (page->block_size >= (sizeof(mi_padding_t))) ? ((void) 0) : (_mi_assert_fail("page->block_size >= MI_PADDING_SIZE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 65, __func__));
    if (page->free_is_zero)
    {
      block->next = 0;
      ;
    }
    else
    {
      _mi_memzero_aligned(block, page->block_size - (sizeof(mi_padding_t)));
    }
  }
  if ((!zero) && (!mi_page_is_huge(page)))
  {
    memset(block, 0xD0, mi_page_usable_block_size(page));
  }
  const size_t bsize = mi_page_usable_block_size(page);
  if (bsize <= ((1UL << (3 + (13 + 3))) / 8))
  {
    _mi_stat_increase(&heap->tld->stats.malloc_normal, bsize);
    _mi_stat_counter_increase(&heap->tld->stats.malloc_normal_count, 1);
    const size_t bin = _mi_bin(bsize);
    _mi_stat_increase(&heap->tld->stats.malloc_bins[bin], 1);
    _mi_stat_increase(&heap->tld->stats.malloc_requested, size - (sizeof(mi_padding_t)));
  }
  mi_padding_t * const padding = (mi_padding_t *) (((uint8_t *) block) + mi_page_usable_block_size(page));
  ptrdiff_t delta = (((uint8_t *) padding) - ((uint8_t *) block)) - (size - (sizeof(mi_padding_t)));
  ((delta >= 0) && (mi_page_usable_block_size(page) >= ((size - (sizeof(mi_padding_t))) + delta))) ? ((void) 0) : (_mi_assert_fail("delta >= 0 && mi_page_usable_block_size(page) >= (size - MI_PADDING_SIZE + delta)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 101, __func__));
  ;
  padding->canary = mi_ptr_encode_canary(page, block, page->keys);
  padding->delta = (uint32_t) delta;
  if (!mi_page_is_huge(page))
  {
    uint8_t *fill = ((uint8_t *) padding) - delta;
    const size_t maxpad = (delta > 16) ? (16) : (delta);
    for (size_t i = 0; i < maxpad; i += 1)
    {
      fill[i] = 0xDE;
    }

  }
  return block;
}


/*** DEPENDENCIES:
None
----------------------------
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 591, __func__));
  return page->block_size;
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
None
----------------------------
void _mi_stat_increase(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_update(stat, (int64_t) amount);
}


----------------------------
inline static uint32_t mi_ptr_encode_canary(const void *null, const void *p, const uintptr_t *keys)
{
  const uint32_t x = (uint32_t) mi_ptr_encode(null, p, keys);
  return x & 0xFFFFFF00;
}


----------------------------
inline static size_t mi_page_usable_block_size(const mi_page_t *page)
{
  return mi_page_block_size(page) - (sizeof(mi_padding_t));
}


----------------------------
size_t _mi_bin(size_t size)
{
  return mi_bin(size);
}


----------------------------
inline static mi_page_t *_mi_ptr_page(void *p)
{
  (p != 0) ? ((void) 0) : (_mi_assert_fail("p!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 585, __func__));
  return _mi_segment_page_of(_mi_ptr_segment(p), p);
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
inline static void _mi_memzero_aligned(void *dst, size_t n)
{
  ((((uintptr_t) dst) % (1 << 3)) == 0) ? ((void) 0) : (_mi_assert_fail("(uintptr_t)dst % MI_INTPTR_SIZE == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 1135, __func__));
  void *adst = __builtin_assume_aligned(dst, 1 << 3);
  _mi_memzero(adst, n);
}


----------------------------
typedef struct mi_padding_s
{
  uint32_t canary;
  uint32_t delta;
} mi_padding_t
----------------------------
inline static bool _mi_is_aligned(void *p, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 380, __func__));
  return (((uintptr_t) p) % alignment) == 0;
}


----------------------------
inline static bool mi_page_is_huge(const mi_page_t *page)
{
  ((page->is_huge && (_mi_page_segment(page)->kind == MI_SEGMENT_HUGE)) || ((!page->is_huge) && (_mi_page_segment(page)->kind != MI_SEGMENT_HUGE))) ? ((void) 0) : (_mi_assert_fail("(page->is_huge && _mi_page_segment(page)->kind == MI_SEGMENT_HUGE) || (!page->is_huge && _mi_page_segment(page)->kind != MI_SEGMENT_HUGE)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 596, __func__));
  return page->is_huge;
}


----------------------------
inline static mi_block_t *mi_block_next(const mi_page_t *page, const mi_block_t *block)
{
  mi_block_t *next = mi_block_nextx(page, block, page->keys);
  unsigned int next_idx = 0;
  if (__builtin_expect(!(!(((&next[next_idx]) != 0) && (!mi_is_in_same_page(block, next)))), 0))
  {
    _mi_error_message(14, "corrupted free list entry of size %zub at %p: value 0x%zx\n", mi_page_block_size(page), block, (uintptr_t) next);
    next_idx = 0;
  }
  return next;
}


----------------------------
void _mi_stat_counter_increase(mi_stat_counter_t *stat, size_t amount)
{
  if (mi_is_in_main(stat))
  {
    mi_atomic_addi64_relaxed(&stat->total, (int64_t) amount);
  }
  else
  {
    stat->total += amount;
  }
}


----------------------------
None
----------------------------
***/


// element in merge of:  _mi_malloc_generic,_mi_page_malloc,_mi_page_malloc_zero
void *_mi_malloc_generic(mi_heap_t *heap, size_t size, bool zero, size_t huge_alignment)
{
  unsigned int heap_idx = 0;
  ((&heap[heap_idx]) != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 989, __func__));
  if (__builtin_expect(!(!(!mi_heap_is_initialized(heap))), 0))
  {
    heap_idx = mi_heap_get_default();
    if (__builtin_expect(!(!(!mi_heap_is_initialized(heap))), 0))
    {
      return 0;
    }
  }
  (mi_heap_is_initialized(heap)) ? ((void) 0) : (_mi_assert_fail("mi_heap_is_initialized(heap)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 996, __func__));
  if (__builtin_expect(!(!((++heap->generic_count) >= 100)), 0))
  {
    heap->generic_collect_count += heap->generic_count;
    heap->generic_count = 0;
    _mi_deferred_free(heap, 0);
    _mi_heap_delayed_free_partial(heap);
    const long generic_collect = mi_option_get_clamp(mi_option_generic_collect, 1, 1000000L);
    if (heap->generic_collect_count >= generic_collect)
    {
      heap->generic_collect_count = 0;
      mi_heap_collect(heap, 0);
    }
  }
  mi_page_t *page = mi_find_page(heap, size, huge_alignment);
  unsigned int page_idx = 0;
  if (__builtin_expect(!(!((&page[page_idx]) == 0)), 0))
  {
    mi_heap_collect(heap, 1);
    page_idx = mi_find_page(heap, size, huge_alignment);
  }
  if (__builtin_expect(!(!((&page[page_idx]) == 0)), 0))
  {
    const size_t req_size = size - (sizeof(mi_padding_t));
    _mi_error_message(12, "unable to allocate memory (%zu bytes)\n", req_size);
    return 0;
  }
  (mi_page_immediate_available(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_immediate_available(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 1029, __func__));
  (mi_page_block_size(page) >= size) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) >= size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 1030, __func__));
  void *p;
  unsigned int p_idx = 0;
  if (__builtin_expect(!(!(zero && mi_page_is_huge(page))), 0))
  {
    p_idx = _mi_page_malloc(heap, page, size);
    ((&p[p_idx]) != 0) ? ((void) 0) : (_mi_assert_fail("p != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 1037, __func__));
    _mi_memzero_aligned(p, mi_page_usable_block_size(page));
  }
  else
  {
    p_idx = _mi_page_malloc_zero(heap, page, size, zero);
    ((&p[p_idx]) != 0) ? ((void) 0) : (_mi_assert_fail("p != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 1042, __func__));
  }
  if (page->reserved == page->used)
  {
    mi_page_to_full(page, mi_page_queue_of(page));
  }
  return p;
}


/*** DEPENDENCIES:
None
----------------------------
inline static bool mi_heap_is_initialized(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 501, __func__));
  return (heap != 0) && (heap != (&_mi_heap_empty));
}


----------------------------
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 591, __func__));
  return page->block_size;
}


----------------------------
static void mi_page_to_full(mi_page_t *page, mi_page_queue_t *pq)
{
  (pq == mi_page_queue_of(page)) ? ((void) 0) : (_mi_assert_fail("pq == mi_page_queue_of(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 366, __func__));
  (!mi_page_immediate_available(page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_immediate_available(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 367, __func__));
  (!mi_page_is_in_full(page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_is_in_full(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 368, __func__));
  if (mi_page_is_in_full(page))
  {
    return;
  }
  mi_page_queue_enqueue_from(&mi_page_heap(page)->pages[73U + 1], pq, page);
  _mi_page_free_collect(page, 0);
}


----------------------------
void _mi_deferred_free(mi_heap_t *heap, bool force)
{
  heap->tld->heartbeat += 1;
  if ((deferred_free != 0) && (!heap->tld->recurse))
  {
    heap->tld->recurse = 1;
    deferred_free(force, heap->tld->heartbeat, atomic_load_explicit(&deferred_arg, memory_order_relaxed));
    heap->tld->recurse = 0;
  }
}


----------------------------
None
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
inline static size_t mi_page_usable_block_size(const mi_page_t *page)
{
  return mi_page_block_size(page) - (sizeof(mi_padding_t));
}


----------------------------
void mi_heap_collect(mi_heap_t *heap, bool force)
{
  mi_heap_collect_ex(heap, (force) ? (MI_FORCE) : (MI_NORMAL));
}


----------------------------
inline static bool mi_page_immediate_available(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 668, __func__));
  return page->free != 0;
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
static mi_page_t *mi_find_page(mi_heap_t *heap, size_t size, size_t huge_alignment)
{
  const size_t req_size = size - (sizeof(mi_padding_t));
  if (__builtin_expect(!(!((req_size > (((1UL << (3 + (13 + 3))) / 8) - (sizeof(mi_padding_t)))) || (huge_alignment > 0))), 0))
  {
    if (__builtin_expect(!(!(req_size > PTRDIFF_MAX)), 0))
    {
      _mi_error_message(75, "allocation request is too large (%zu bytes)\n", req_size);
      return 0;
    }
    else
    {
      return mi_large_huge_page_alloc(heap, size, huge_alignment);
    }
  }
  else
  {
    (size >= (sizeof(mi_padding_t))) ? ((void) 0) : (_mi_assert_fail("size >= MI_PADDING_SIZE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 977, __func__));
    return mi_find_free_page(heap, size);
  }
}


----------------------------
inline static void _mi_memzero_aligned(void *dst, size_t n)
{
  ((((uintptr_t) dst) % (1 << 3)) == 0) ? ((void) 0) : (_mi_assert_fail("(uintptr_t)dst % MI_INTPTR_SIZE == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 1135, __func__));
  void *adst = __builtin_assume_aligned(dst, 1 << 3);
  _mi_memzero(adst, n);
}


----------------------------
long mi_option_get_clamp(mi_option_t option, long min, long max)
{
  long x = mi_option_get(option);
  return (x < min) ? (min) : ((x > max) ? (max) : (x));
}


----------------------------
static mi_page_queue_t *mi_page_queue_of(const mi_page_t *page)
{
  mi_heap_t *heap = mi_page_heap(page);
  mi_page_queue_t *pq = mi_heap_page_queue_of(heap, page);
  ;
  return pq;
}


----------------------------
inline static bool mi_page_is_huge(const mi_page_t *page)
{
  ((page->is_huge && (_mi_page_segment(page)->kind == MI_SEGMENT_HUGE)) || ((!page->is_huge) && (_mi_page_segment(page)->kind != MI_SEGMENT_HUGE))) ? ((void) 0) : (_mi_assert_fail("(page->is_huge && _mi_page_segment(page)->kind == MI_SEGMENT_HUGE) || (!page->is_huge && _mi_page_segment(page)->kind != MI_SEGMENT_HUGE)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 596, __func__));
  return page->is_huge;
}


----------------------------
None
----------------------------
***/


