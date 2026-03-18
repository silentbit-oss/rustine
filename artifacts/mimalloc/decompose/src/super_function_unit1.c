// element in merge of:  _mi_malloc_generic,_mi_page_malloc_zero
void *_mi_malloc_generic(mi_heap_t *heap, size_t size, bool zero, size_t huge_alignment)
{
  unsigned int heap_idx = 0;
  ((&heap[heap_idx]) != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 942, __func__));
  if (__builtin_expect(!(!(!mi_heap_is_initialized(heap))), 0))
  {
    heap_idx = mi_heap_get_default();
    if (__builtin_expect(!(!(!mi_heap_is_initialized(heap))), 0))
    {
      return 0;
    }
  }
  (mi_heap_is_initialized(heap)) ? ((void) 0) : (_mi_assert_fail("mi_heap_is_initialized(heap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 949, __func__));
  if (__builtin_expect(!(!((++heap->generic_count) >= 1000)), 0))
  {
    heap->generic_collect_count += heap->generic_count;
    heap->generic_count = 0;
    _mi_deferred_free(heap, 0);
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
  (mi_page_immediate_available(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_immediate_available(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 979, __func__));
  (mi_page_block_size(page) >= size) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) >= size", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 980, __func__));
  (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 981, __func__));
  (_mi_ptr_page(page) == (&page[page_idx])) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 982, __func__));
  void * const p = _mi_page_malloc_zero(heap, page, size, zero);
  (p != 0) ? ((void) 0) : (_mi_assert_fail("p != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 986, __func__));
  if (mi_page_is_full(page))
  {
    mi_page_to_full(page, mi_page_queue_of(page));
  }
  return p;
}


/*** DEPENDENCIES:
None
----------------------------
long mi_option_get_clamp(mi_option_t option, long min, long max)
{
  long x = mi_option_get(option);
  return (x < min) ? (min) : ((x > max) ? (max) : (x));
}


----------------------------
None
----------------------------
inline static bool mi_heap_is_initialized(const mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 542, __func__));
  return (heap != 0) && (heap != (&_mi_heap_empty));
}


----------------------------
inline static mi_page_t *_mi_ptr_page(const void *p)
{
  ((p == 0) || mi_is_in_heap_region(p)) ? ((void) 0) : (_mi_assert_fail("p==NULL || mi_is_in_heap_region(p)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 638, __func__));
  return _mi_checked_ptr_page(p);
}


----------------------------
inline static bool mi_page_immediate_available(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 720, __func__));
  return page->free != 0;
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
static mi_page_t *mi_find_page(mi_heap_t *heap, size_t size, size_t huge_alignment)
{
  const size_t req_size = size - (sizeof(mi_padding_t));
  if (__builtin_expect(!(!(req_size > PTRDIFF_MAX)), 0))
  {
    _mi_error_message(75, "allocation request is too large (%zu bytes)\n", req_size);
    return 0;
  }
  mi_page_queue_t *pq = mi_page_queue(heap, (huge_alignment > 0) ? (((8 * (1 * (1UL << (13 + 3)))) / 8) + 1) : (size));
  if (__builtin_expect(!(!(mi_page_queue_is_huge(pq) || (req_size > PTRDIFF_MAX))), 0))
  {
    return mi_huge_page_alloc(heap, size, huge_alignment, pq);
  }
  else
  {
    (size >= (sizeof(mi_padding_t))) ? ((void) 0) : (_mi_assert_fail("size >= MI_PADDING_SIZE", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 929, __func__));
    return mi_find_free_page(heap, pq);
  }
}


----------------------------
inline static bool _mi_is_aligned(void *p, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 423, __func__));
  return (((uintptr_t) p) % alignment) == 0;
}


----------------------------
static void mi_page_to_full(mi_page_t *page, mi_page_queue_t *pq)
{
  (pq == mi_page_queue_of(page)) ? ((void) 0) : (_mi_assert_fail("pq == mi_page_queue_of(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 362, __func__));
  (!mi_page_immediate_available(page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_immediate_available(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 363, __func__));
  (!mi_page_is_in_full(page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_is_in_full(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 364, __func__));
  mi_heap_t *heap = mi_page_heap(page);
  if (heap->allow_page_abandon)
  {
    _mi_page_abandon(page, pq);
  }
  else
    if (!mi_page_is_in_full(page))
  {
    mi_page_queue_enqueue_from(&mi_page_heap(page)->pages[73U + 1], pq, page);
    _mi_page_free_collect(page, 0);
  }
}


----------------------------
inline static bool mi_page_is_full(mi_page_t *page)
{
  const bool full = page->reserved == page->used;
  ((!full) || (page->free == 0)) ? ((void) 0) : (_mi_assert_fail("!full || page->free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 735, __func__));
  return full;
}


----------------------------
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
}


----------------------------
mi_heap_t *mi_heap_get_default(void)
{
  mi_heap_t *heap = mi_prim_get_default_heap();
  unsigned int heap_idx = 0;
  if (__builtin_expect(!(!(!mi_heap_is_initialized(heap))), 0))
  {
    mi_thread_init();
    heap_idx = mi_prim_get_default_heap();
  }
  return heap;
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
void mi_heap_collect(mi_heap_t *heap, bool force)
{
  mi_heap_collect_ex(heap, (force) ? (MI_FORCE) : (MI_NORMAL));
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
None
----------------------------
***/


// element in merge of:  _mi_malloc_generic,_mi_page_malloc_zero
inline extern void *_mi_page_malloc_zero(mi_heap_t *heap, mi_page_t *page, size_t size, bool zero)
{
  if (page->block_size != 0)
  {
    (mi_page_block_size(page) >= size) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) >= size", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 34, __func__));
    (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 35, __func__));
    (_mi_ptr_page(page) == page) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 36, __func__));
  }
  mi_block_t * const block = page->free;
  if (__builtin_expect(!(!(block == 0)), 0))
  {
    return _mi_malloc_generic(heap, size, zero, 0);
  }
  ((block != 0) && (_mi_ptr_page(block) == page)) ? ((void) 0) : (_mi_assert_fail("block != NULL && _mi_ptr_page(block) == page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 44, __func__));
  page->free = mi_block_next(page, block);
  page->used += 1;
  ((page->free == 0) || (_mi_ptr_page(page->free) == page)) ? ((void) 0) : (_mi_assert_fail("page->free == NULL || _mi_ptr_page(page->free) == page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 49, __func__));
  ((page->block_size < 16) || _mi_is_aligned(block, 16)) ? ((void) 0) : (_mi_assert_fail("page->block_size < MI_MAX_ALIGN_SIZE || _mi_is_aligned(block, MI_MAX_ALIGN_SIZE)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 50, __func__));
  const size_t bsize = mi_page_usable_block_size(page);
  ;
  if (__builtin_expect(!(!zero), 0))
  {
    if (page->free_is_zero)
    {
      block->next = 0;
      ;
    }
    else
    {
      _mi_memzero_aligned(block, bsize);
    }
  }
  if ((!zero) && (!mi_page_is_huge(page)))
  {
    memset(block, 0xD0, bsize);
  }
  if (bsize <= ((8 * (1 * (1UL << (13 + 3)))) / 8))
  {
    __mi_stat_increase(&heap->tld->stats.malloc_normal, bsize);
    __mi_stat_counter_increase(&heap->tld->stats.malloc_normal_count, 1);
    const size_t bin = _mi_bin(bsize);
    __mi_stat_increase(&heap->tld->stats.malloc_bins[bin], 1);
    __mi_stat_increase(&heap->tld->stats.malloc_requested, size - (sizeof(mi_padding_t)));
  }
  mi_padding_t * const padding = (mi_padding_t *) (((uint8_t *) block) + bsize);
  ptrdiff_t delta = (((uint8_t *) padding) - ((uint8_t *) block)) - (size - (sizeof(mi_padding_t)));
  ((delta >= 0) && (bsize >= ((size - (sizeof(mi_padding_t))) + delta))) ? ((void) 0) : (_mi_assert_fail("delta >= 0 && bsize >= (size - MI_PADDING_SIZE + delta)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/alloc.c", 99, __func__));
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
inline static void _mi_memzero_aligned(void *dst, size_t n)
{
  _mi_memset_aligned(dst, 0, n);
}


----------------------------
inline static size_t mi_page_usable_block_size(const mi_page_t *page)
{
  return mi_page_block_size(page) - (sizeof(mi_padding_t));
}


----------------------------
None
----------------------------
void __mi_stat_counter_increase(mi_stat_counter_t *stat, size_t amount)
{
  stat->total += amount;
}


----------------------------
inline static mi_page_t *_mi_ptr_page(const void *p)
{
  ((p == 0) || mi_is_in_heap_region(p)) ? ((void) 0) : (_mi_assert_fail("p==NULL || mi_is_in_heap_region(p)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 638, __func__));
  return _mi_checked_ptr_page(p);
}


----------------------------
inline static uint32_t mi_ptr_encode_canary(const void *null, const void *p, const uintptr_t *keys)
{
  const uint32_t x = (uint32_t) mi_ptr_encode(null, p, keys);
  return x & 0xFFFFFF00;
}


----------------------------
void __mi_stat_increase(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_update(stat, (int64_t) amount);
}


----------------------------
size_t _mi_bin(size_t size)
{
  return mi_bin(size);
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
inline static bool mi_page_is_huge(const mi_page_t *page)
{
  return mi_page_is_singleton(page) && ((page->block_size > ((8 * (1 * (1UL << (13 + 3)))) / 8)) || (mi_memkind_is_os(page->memid.memkind) && (page->memid.mem.os.base < ((void *) page))));
}


----------------------------
inline static bool _mi_is_aligned(void *p, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 423, __func__));
  return (((uintptr_t) p) % alignment) == 0;
}


----------------------------
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
}


----------------------------
typedef struct mi_padding_s
{
  uint32_t canary;
  uint32_t delta;
} mi_padding_t
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
None
----------------------------
***/


