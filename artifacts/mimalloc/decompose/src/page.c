inline static size_t mi_bin(size_t size)
{
  size_t wsize = _mi_wsize_from_size(size);
  if (__builtin_expect(!(!(wsize <= 8)), 1))
  {
    return (wsize <= 1) ? (1) : ((wsize + 1) & (~1));
  }
  else
    if (__builtin_expect(!(!(wsize > (((1UL << (3 + (13 + 3))) / 8) / (1 << 3)))), 0))
  {
    return 73U;
  }
  else
  {
    wsize -= 1;
    const size_t b = (((1 << 3) * 8) - 1) - mi_clz(wsize);
    const size_t bin = ((b << 2) + ((wsize >> (b - 2)) & 0x03)) - 3;
    ((bin > 0) && (bin < 73U)) ? ((void) 0) : (_mi_assert_fail("bin > 0 && bin < MI_BIN_HUGE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 88, __func__));
    return bin;
  }
}


/*** DEPENDENCIES:
inline static size_t mi_clz(size_t x)
{
  if (x == 0)
  {
    return (1 << 3) * 8;
  }
  return __builtin_clzll(x);
}


----------------------------
inline static size_t _mi_wsize_from_size(size_t size)
{
  (size <= (SIZE_MAX - (sizeof(uintptr_t)))) ? ((void) 0) : (_mi_assert_fail("size <= SIZE_MAX - sizeof(uintptr_t)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 445, __func__));
  return ((size + (sizeof(uintptr_t))) - 1) / (sizeof(uintptr_t));
}


----------------------------
None
----------------------------
***/


size_t _mi_bin_size(size_t bin)
{
  return _mi_heap_empty.pages[bin].block_size;
}


/*** DEPENDENCIES:
extern const mi_heap_t _mi_heap_empty
----------------------------
***/


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
size_t _mi_bin_size(size_t bin)
{
  return _mi_heap_empty.pages[bin].block_size;
}


----------------------------
size_t _mi_os_page_size(void)
{
  return mi_os_mem_config.page_size;
}


----------------------------
inline static size_t mi_bin(size_t size)
{
  size_t wsize = _mi_wsize_from_size(size);
  if (__builtin_expect(!(!(wsize <= 8)), 1))
  {
    return (wsize <= 1) ? (1) : ((wsize + 1) & (~1));
  }
  else
    if (__builtin_expect(!(!(wsize > (((1UL << (3 + (13 + 3))) / 8) / (1 << 3)))), 0))
  {
    return 73U;
  }
  else
  {
    wsize -= 1;
    const size_t b = (((1 << 3) * 8) - 1) - mi_clz(wsize);
    const size_t bin = ((b << 2) + ((wsize >> (b - 2)) & 0x03)) - 3;
    ((bin > 0) && (bin < 73U)) ? ((void) 0) : (_mi_assert_fail("bin > 0 && bin < MI_BIN_HUGE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 88, __func__));
    return bin;
  }
}


----------------------------
***/


// hint:  ['current_ref is a mutable refrence to size_t', 'rnd_ref is a mutable refrence to uintptr_t']
void helper_mi_page_free_list_extend_secure_1(size_t * const current_ref, uintptr_t * const rnd_ref, mi_page_t * const page, const size_t bsize, const size_t slice_count, mi_block_t *blocks[1UL << 6], size_t counts[1UL << 6], size_t i, size_t i)
{
  size_t current = *current_ref;
  uintptr_t rnd = *rnd_ref;
  const size_t round = i % (1 << 3);
  if (round == 0)
  {
    rnd = _mi_random_shuffle(rnd);
  }
  size_t next = (rnd >> (8 * round)) & (slice_count - 1);
  while (counts[next] == 0)
  {
    next += 1;
    if (next == slice_count)
    {
      next = 0;
    }
  }

  counts[next] -= 1;
  mi_block_t * const block = blocks[current];
  blocks[current] = (mi_block_t *) (((uint8_t *) block) + bsize);
  mi_block_set_next(page, block, blocks[next]);
  current = next;
  *current_ref = current;
  *rnd_ref = rnd;
}


/*** DEPENDENCIES:
inline static uintptr_t _mi_random_shuffle(uintptr_t x)
{
  if (x == 0)
  {
    x = 17;
  }
  x ^= x >> 30;
  x *= 0xbf58476d1ce4e5b9UL;
  x ^= x >> 27;
  x *= 0x94d049bb133111ebUL;
  x ^= x >> 31;
  return x;
}


----------------------------
inline static void mi_block_set_next(const mi_page_t *page, mi_block_t *block, const mi_block_t *next)
{
  mi_block_set_nextx(page, block, next, page->keys);
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
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
***/


inline static mi_block_t *mi_page_block_at(const mi_page_t *page, void *page_start, size_t block_size, size_t i)
{
  (void) page;
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 34, __func__));
  (i <= page->reserved) ? ((void) 0) : (_mi_assert_fail("i <= page->reserved", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 35, __func__));
  return (mi_block_t *) (((uint8_t *) page_start) + (i * block_size));
}


/*** DEPENDENCIES:
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
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
None
----------------------------
***/


static void mi_page_free_list_extend_secure(mi_heap_t * const heap, mi_page_t * const page, const size_t bsize, const size_t extend, mi_stats_t * const stats)
{
  (void) stats;
  (page->free == 0) ? ((void) 0) : (_mi_assert_fail("page->free == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 539, __func__));
  (page->local_free == 0) ? ((void) 0) : (_mi_assert_fail("page->local_free == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 540, __func__));
  ((page->capacity + extend) <= page->reserved) ? ((void) 0) : (_mi_assert_fail("page->capacity + extend <= page->reserved", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 542, __func__));
  (bsize == mi_page_block_size(page)) ? ((void) 0) : (_mi_assert_fail("bsize == mi_page_block_size(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 543, __func__));
  void * const page_area = mi_page_start(page);
  size_t shift = 6;
  while ((extend >> shift) == 0)
  {
    shift -= 1;
  }

  const size_t slice_count = ((size_t) 1U) << shift;
  const size_t slice_extend = extend / slice_count;
  (slice_extend >= 1) ? ((void) 0) : (_mi_assert_fail("slice_extend >= 1", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 554, __func__));
  mi_block_t *blocks[1UL << 6];
  size_t counts[1UL << 6];
  for (size_t i = 0; i < slice_count; i += 1)
  {
    blocks[i] = mi_page_block_at(page, page_area, bsize, page->capacity + (i * slice_extend));
    counts[i] = slice_extend;
  }

  counts[slice_count - 1] += extend % slice_count;
  const uintptr_t r = _mi_heap_random_next(heap);
  size_t current = r % slice_count;
  counts[current] -= 1;
  mi_block_t * const free_start = blocks[current];
  uintptr_t rnd = _mi_random_shuffle(r | 1);
  for (size_t i = 1; i < extend; i += 1)
  {
    helper_mi_page_free_list_extend_secure_1(&current, &rnd, page, bsize, slice_count, blocks, counts, i, i);
  }

  mi_block_set_next(page, blocks[current], page->free);
  page->free = free_start;
}


/*** DEPENDENCIES:
typedef struct mi_stats_s
{
  int version;
  mi_stat_count_t pages;
  mi_stat_count_t reserved;
  mi_stat_count_t committed;
  mi_stat_count_t reset;
  mi_stat_count_t purged;
  mi_stat_count_t page_committed;
  mi_stat_count_t pages_abandoned;
  mi_stat_count_t threads;
  mi_stat_count_t malloc_normal;
  mi_stat_count_t malloc_huge;
  mi_stat_count_t malloc_requested;
  mi_stat_counter_t mmap_calls;
  mi_stat_counter_t commit_calls;
  mi_stat_counter_t reset_calls;
  mi_stat_counter_t purge_calls;
  mi_stat_counter_t arena_count;
  mi_stat_counter_t malloc_normal_count;
  mi_stat_counter_t malloc_huge_count;
  mi_stat_counter_t malloc_guarded_count;
  mi_stat_counter_t arena_rollback_count;
  mi_stat_counter_t arena_purges;
  mi_stat_counter_t pages_extended;
  mi_stat_counter_t pages_retire;
  mi_stat_counter_t page_searches;
  mi_stat_count_t segments;
  mi_stat_count_t segments_abandoned;
  mi_stat_count_t segments_cache;
  mi_stat_count_t _segments_reserved;
  mi_stat_counter_t pages_reclaim_on_alloc;
  mi_stat_counter_t pages_reclaim_on_free;
  mi_stat_counter_t pages_reabandon_full;
  mi_stat_counter_t pages_unabandon_busy_wait;
  mi_stat_count_t _stat_reserved[4];
  mi_stat_counter_t _stat_counter_reserved[4];
  mi_stat_count_t malloc_bins[73U + 1];
  mi_stat_count_t page_bins[73U + 1];
} mi_stats_t
----------------------------
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 591, __func__));
  return page->block_size;
}


----------------------------
inline static mi_block_t *mi_page_block_at(const mi_page_t *page, void *page_start, size_t block_size, size_t i)
{
  (void) page;
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 34, __func__));
  (i <= page->reserved) ? ((void) 0) : (_mi_assert_fail("i <= page->reserved", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 35, __func__));
  return (mi_block_t *) (((uint8_t *) page_start) + (i * block_size));
}


----------------------------
void helper_mi_page_free_list_extend_secure_1(size_t * const current_ref, uintptr_t * const rnd_ref, mi_page_t * const page, const size_t bsize, const size_t slice_count, mi_block_t *blocks[1UL << 6], size_t counts[1UL << 6], size_t i, size_t i)
{
  size_t current = *current_ref;
  uintptr_t rnd = *rnd_ref;
  const size_t round = i % (1 << 3);
  if (round == 0)
  {
    rnd = _mi_random_shuffle(rnd);
  }
  size_t next = (rnd >> (8 * round)) & (slice_count - 1);
  while (counts[next] == 0)
  {
    next += 1;
    if (next == slice_count)
    {
      next = 0;
    }
  }

  counts[next] -= 1;
  mi_block_t * const block = blocks[current];
  blocks[current] = (mi_block_t *) (((uint8_t *) block) + bsize);
  mi_block_set_next(page, block, blocks[next]);
  current = next;
  *current_ref = current;
  *rnd_ref = rnd;
}


----------------------------
inline static void mi_block_set_next(const mi_page_t *page, mi_block_t *block, const mi_block_t *next)
{
  mi_block_set_nextx(page, block, next, page->keys);
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
None
----------------------------
inline static uintptr_t _mi_random_shuffle(uintptr_t x)
{
  if (x == 0)
  {
    x = 17;
  }
  x ^= x >> 30;
  x *= 0xbf58476d1ce4e5b9UL;
  x ^= x >> 27;
  x *= 0x94d049bb133111ebUL;
  x ^= x >> 31;
  return x;
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
inline static uint8_t *mi_page_start(const mi_page_t *page)
{
  (page->page_start != 0) ? ((void) 0) : (_mi_assert_fail("page->page_start != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 578, __func__));
  ;
  return page->page_start;
}


----------------------------
uintptr_t _mi_heap_random_next(mi_heap_t *heap)
{
  return _mi_random_next(&heap->random);
}


----------------------------
None
----------------------------
***/


static void mi_page_free_list_extend(mi_page_t * const page, const size_t bsize, const size_t extend, mi_stats_t * const stats)
{
  (void) stats;
  (page->free == 0) ? ((void) 0) : (_mi_assert_fail("page->free == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 597, __func__));
  (page->local_free == 0) ? ((void) 0) : (_mi_assert_fail("page->local_free == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 598, __func__));
  ((page->capacity + extend) <= page->reserved) ? ((void) 0) : (_mi_assert_fail("page->capacity + extend <= page->reserved", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 600, __func__));
  (bsize == mi_page_block_size(page)) ? ((void) 0) : (_mi_assert_fail("bsize == mi_page_block_size(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 601, __func__));
  void * const page_area = mi_page_start(page);
  mi_block_t * const start = mi_page_block_at(page, page_area, bsize, page->capacity);
  mi_block_t * const last = mi_page_block_at(page, page_area, bsize, (page->capacity + extend) - 1);
  mi_block_t *block = start;
  unsigned int block_idx = 0;
  while ((&block[block_idx]) <= last)
  {
    mi_block_t *next = (mi_block_t *) (((uint8_t *) block) + bsize);
    mi_block_set_next(page, block, next);
    block_idx = next;
  }

  mi_block_set_next(page, last, page->free);
  page->free = start;
}


/*** DEPENDENCIES:
typedef struct mi_stats_s
{
  int version;
  mi_stat_count_t pages;
  mi_stat_count_t reserved;
  mi_stat_count_t committed;
  mi_stat_count_t reset;
  mi_stat_count_t purged;
  mi_stat_count_t page_committed;
  mi_stat_count_t pages_abandoned;
  mi_stat_count_t threads;
  mi_stat_count_t malloc_normal;
  mi_stat_count_t malloc_huge;
  mi_stat_count_t malloc_requested;
  mi_stat_counter_t mmap_calls;
  mi_stat_counter_t commit_calls;
  mi_stat_counter_t reset_calls;
  mi_stat_counter_t purge_calls;
  mi_stat_counter_t arena_count;
  mi_stat_counter_t malloc_normal_count;
  mi_stat_counter_t malloc_huge_count;
  mi_stat_counter_t malloc_guarded_count;
  mi_stat_counter_t arena_rollback_count;
  mi_stat_counter_t arena_purges;
  mi_stat_counter_t pages_extended;
  mi_stat_counter_t pages_retire;
  mi_stat_counter_t page_searches;
  mi_stat_count_t segments;
  mi_stat_count_t segments_abandoned;
  mi_stat_count_t segments_cache;
  mi_stat_count_t _segments_reserved;
  mi_stat_counter_t pages_reclaim_on_alloc;
  mi_stat_counter_t pages_reclaim_on_free;
  mi_stat_counter_t pages_reabandon_full;
  mi_stat_counter_t pages_unabandon_busy_wait;
  mi_stat_count_t _stat_reserved[4];
  mi_stat_counter_t _stat_counter_reserved[4];
  mi_stat_count_t malloc_bins[73U + 1];
  mi_stat_count_t page_bins[73U + 1];
} mi_stats_t
----------------------------
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 591, __func__));
  return page->block_size;
}


----------------------------
inline static mi_block_t *mi_page_block_at(const mi_page_t *page, void *page_start, size_t block_size, size_t i)
{
  (void) page;
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 34, __func__));
  (i <= page->reserved) ? ((void) 0) : (_mi_assert_fail("i <= page->reserved", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 35, __func__));
  return (mi_block_t *) (((uint8_t *) page_start) + (i * block_size));
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
inline static void mi_block_set_next(const mi_page_t *page, mi_block_t *block, const mi_block_t *next)
{
  mi_block_set_nextx(page, block, next, page->keys);
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
inline static uint8_t *mi_page_start(const mi_page_t *page)
{
  (page->page_start != 0) ? ((void) 0) : (_mi_assert_fail("page->page_start != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 578, __func__));
  ;
  return page->page_start;
}


----------------------------
None
----------------------------
***/


static bool mi_page_extend_free(mi_heap_t *heap, mi_page_t *page, mi_tld_t *tld)
{
  ;
  (page->free == 0) ? ((void) 0) : (_mi_assert_fail("page->free == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 638, __func__));
  (page->local_free == 0) ? ((void) 0) : (_mi_assert_fail("page->local_free == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 639, __func__));
  if (page->free != 0)
  {
    return 1;
  }
  if (page->capacity >= page->reserved)
  {
    return 1;
  }
  _mi_stat_counter_increase(&tld->stats.pages_extended, 1);
  const size_t bsize = mi_page_block_size(page);
  size_t extend = page->reserved - page->capacity;
  (extend > 0) ? ((void) 0) : (_mi_assert_fail("extend > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 649, __func__));
  size_t max_extend = (bsize >= (4 * 1024)) ? (4) : ((4 * 1024) / bsize);
  if (max_extend < 4)
  {
    max_extend = 4;
  }
  (max_extend > 0) ? ((void) 0) : (_mi_assert_fail("max_extend > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 653, __func__));
  if (extend > max_extend)
  {
    extend = max_extend;
  }
  ((extend > 0) && ((extend + page->capacity) <= page->reserved)) ? ((void) 0) : (_mi_assert_fail("extend > 0 && extend + page->capacity <= page->reserved", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 661, __func__));
  (extend < (1UL << 16)) ? ((void) 0) : (_mi_assert_fail("extend < (1UL<<16)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 662, __func__));
  if ((extend < 2) || (0 == 0))
  {
    mi_page_free_list_extend(page, bsize, extend, &tld->stats);
  }
  else
  {
    mi_page_free_list_extend_secure(heap, page, bsize, extend, &tld->stats);
  }
  page->capacity += (uint16_t) extend;
  _mi_stat_increase(&tld->stats.page_committed, extend * bsize);
  ;
  return 1;
}


/*** DEPENDENCIES:
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 591, __func__));
  return page->block_size;
}


----------------------------
None
----------------------------
void _mi_stat_increase(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_update(stat, (int64_t) amount);
}


----------------------------
static void mi_page_free_list_extend(mi_page_t * const page, const size_t bsize, const size_t extend, mi_stats_t * const stats)
{
  (void) stats;
  (page->free == 0) ? ((void) 0) : (_mi_assert_fail("page->free == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 597, __func__));
  (page->local_free == 0) ? ((void) 0) : (_mi_assert_fail("page->local_free == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 598, __func__));
  ((page->capacity + extend) <= page->reserved) ? ((void) 0) : (_mi_assert_fail("page->capacity + extend <= page->reserved", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 600, __func__));
  (bsize == mi_page_block_size(page)) ? ((void) 0) : (_mi_assert_fail("bsize == mi_page_block_size(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 601, __func__));
  void * const page_area = mi_page_start(page);
  mi_block_t * const start = mi_page_block_at(page, page_area, bsize, page->capacity);
  mi_block_t * const last = mi_page_block_at(page, page_area, bsize, (page->capacity + extend) - 1);
  mi_block_t *block = start;
  unsigned int block_idx = 0;
  while ((&block[block_idx]) <= last)
  {
    mi_block_t *next = (mi_block_t *) (((uint8_t *) block) + bsize);
    mi_block_set_next(page, block, next);
    block_idx = next;
  }

  mi_block_set_next(page, last, page->free);
  page->free = start;
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
static void mi_page_free_list_extend_secure(mi_heap_t * const heap, mi_page_t * const page, const size_t bsize, const size_t extend, mi_stats_t * const stats)
{
  (void) stats;
  (page->free == 0) ? ((void) 0) : (_mi_assert_fail("page->free == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 539, __func__));
  (page->local_free == 0) ? ((void) 0) : (_mi_assert_fail("page->local_free == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 540, __func__));
  ((page->capacity + extend) <= page->reserved) ? ((void) 0) : (_mi_assert_fail("page->capacity + extend <= page->reserved", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 542, __func__));
  (bsize == mi_page_block_size(page)) ? ((void) 0) : (_mi_assert_fail("bsize == mi_page_block_size(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 543, __func__));
  void * const page_area = mi_page_start(page);
  size_t shift = 6;
  while ((extend >> shift) == 0)
  {
    shift -= 1;
  }

  const size_t slice_count = ((size_t) 1U) << shift;
  const size_t slice_extend = extend / slice_count;
  (slice_extend >= 1) ? ((void) 0) : (_mi_assert_fail("slice_extend >= 1", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 554, __func__));
  mi_block_t *blocks[1UL << 6];
  size_t counts[1UL << 6];
  for (size_t i = 0; i < slice_count; i += 1)
  {
    blocks[i] = mi_page_block_at(page, page_area, bsize, page->capacity + (i * slice_extend));
    counts[i] = slice_extend;
  }

  counts[slice_count - 1] += extend % slice_count;
  const uintptr_t r = _mi_heap_random_next(heap);
  size_t current = r % slice_count;
  counts[current] -= 1;
  mi_block_t * const free_start = blocks[current];
  uintptr_t rnd = _mi_random_shuffle(r | 1);
  for (size_t i = 1; i < extend; i += 1)
  {
    helper_mi_page_free_list_extend_secure_1(&current, &rnd, page, bsize, slice_count, blocks, counts, i, i);
  }

  mi_block_set_next(page, blocks[current], page->free);
  page->free = free_start;
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


static void mi_page_init(mi_heap_t *heap, mi_page_t *page, size_t block_size, mi_tld_t *tld)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 680, __func__));
  mi_segment_t *segment = _mi_page_segment(page);
  (segment != 0) ? ((void) 0) : (_mi_assert_fail("segment != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 682, __func__));
  (block_size > 0) ? ((void) 0) : (_mi_assert_fail("block_size > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 683, __func__));
  mi_page_set_heap(page, heap);
  page->block_size = block_size;
  size_t page_size;
  page->page_start = _mi_segment_page_start(segment, page, &page_size);
  ;
  (mi_page_block_size(page) <= page_size) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) <= page_size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 690, __func__));
  (page_size <= (page->slice_count * (1UL << (13 + 3)))) ? ((void) 0) : (_mi_assert_fail("page_size <= page->slice_count*MI_SEGMENT_SLICE_SIZE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 691, __func__));
  ((page_size / block_size) < (1L << 16)) ? ((void) 0) : (_mi_assert_fail("page_size / block_size < (1L<<16)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 692, __func__));
  page->reserved = (uint16_t) (page_size / block_size);
  (page->reserved > 0) ? ((void) 0) : (_mi_assert_fail("page->reserved > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 694, __func__));
  page->keys[0] = _mi_heap_random_next(heap);
  page->keys[1] = _mi_heap_random_next(heap);
  page->free_is_zero = page->is_zero_init;
  (page->is_committed) ? ((void) 0) : (_mi_assert_fail("page->is_committed", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 706, __func__));
  if ((block_size > 0) && _mi_is_power_of_two(block_size))
  {
    page->block_size_shift = (uint8_t) mi_ctz((uintptr_t) block_size);
  }
  else
  {
    page->block_size_shift = 0;
  }
  (page->capacity == 0) ? ((void) 0) : (_mi_assert_fail("page->capacity == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 714, __func__));
  (page->free == 0) ? ((void) 0) : (_mi_assert_fail("page->free == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 715, __func__));
  (page->used == 0) ? ((void) 0) : (_mi_assert_fail("page->used == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 716, __func__));
  (page->xthread_free == 0) ? ((void) 0) : (_mi_assert_fail("page->xthread_free == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 717, __func__));
  (page->next == 0) ? ((void) 0) : (_mi_assert_fail("page->next == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 718, __func__));
  (page->prev == 0) ? ((void) 0) : (_mi_assert_fail("page->prev == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 719, __func__));
  (page->retire_expire == 0) ? ((void) 0) : (_mi_assert_fail("page->retire_expire == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 720, __func__));
  (!mi_page_has_aligned(page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_has_aligned(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 721, __func__));
  (page->keys[0] != 0) ? ((void) 0) : (_mi_assert_fail("page->keys[0] != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 723, __func__));
  (page->keys[1] != 0) ? ((void) 0) : (_mi_assert_fail("page->keys[1] != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 724, __func__));
  ((page->block_size_shift == 0) || (block_size == (((size_t) 1) << page->block_size_shift))) ? ((void) 0) : (_mi_assert_fail("page->block_size_shift == 0 || (block_size == ((size_t)1 << page->block_size_shift))", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 726, __func__));
  ;
  if (mi_page_extend_free(heap, page, tld))
  {
    (mi_page_immediate_available(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_immediate_available(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 731, __func__));
  }
  return;
}


/*** DEPENDENCIES:
None
----------------------------
inline static mi_segment_t *_mi_page_segment(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 548, __func__));
  mi_segment_t *segment = _mi_ptr_segment(page);
  ((segment == 0) || ((((mi_slice_t *) page) >= segment->slices) && (((mi_slice_t *) page) < (segment->slices + segment->slice_entries)))) ? ((void) 0) : (_mi_assert_fail("segment == NULL || ((mi_slice_t*)page >= segment->slices && (mi_slice_t*)page < segment->slices + segment->slice_entries)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 550, __func__));
  return segment;
}


----------------------------
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 591, __func__));
  return page->block_size;
}


----------------------------
None
----------------------------
inline static bool mi_page_immediate_available(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 668, __func__));
  return page->free != 0;
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
inline static void mi_page_set_heap(mi_page_t *page, mi_heap_t *heap)
{
  (mi_page_thread_free_flag(page) != MI_DELAYED_FREEING) ? ((void) 0) : (_mi_assert_fail("mi_page_thread_free_flag(page) != MI_DELAYED_FREEING", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 631, __func__));
  atomic_store_explicit(&page->xheap, (uintptr_t) heap, memory_order_release);
  if (heap != 0)
  {
    page->heap_tag = heap->tag;
  }
}


----------------------------
inline static bool mi_page_has_aligned(const mi_page_t *page)
{
  return page->flags.x.has_aligned;
}


----------------------------
uint8_t *_mi_segment_page_start(const mi_segment_t *segment, const mi_page_t *page, size_t *page_size)
{
  const mi_slice_t *slice = mi_page_to_slice((mi_page_t *) page);
  uint8_t *p = _mi_segment_page_start_from_slice(segment, slice, mi_page_block_size(page), page_size);
  ((mi_page_block_size(page) > 0) || (_mi_ptr_page(p) == page)) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) > 0 || _mi_ptr_page(p) == page", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c", 364, __func__));
  (_mi_ptr_segment(p) == segment) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_segment(p) == segment", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c", 365, __func__));
  return p;
}


----------------------------
uintptr_t _mi_heap_random_next(mi_heap_t *heap)
{
  return _mi_random_next(&heap->random);
}


----------------------------
inline static size_t mi_ctz(size_t x)
{
  if (x == 0)
  {
    return (1 << 3) * 8;
  }
  return __builtin_ctzll(x);
}


----------------------------
static bool mi_page_extend_free(mi_heap_t *heap, mi_page_t *page, mi_tld_t *tld)
{
  ;
  (page->free == 0) ? ((void) 0) : (_mi_assert_fail("page->free == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 638, __func__));
  (page->local_free == 0) ? ((void) 0) : (_mi_assert_fail("page->local_free == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 639, __func__));
  if (page->free != 0)
  {
    return 1;
  }
  if (page->capacity >= page->reserved)
  {
    return 1;
  }
  _mi_stat_counter_increase(&tld->stats.pages_extended, 1);
  const size_t bsize = mi_page_block_size(page);
  size_t extend = page->reserved - page->capacity;
  (extend > 0) ? ((void) 0) : (_mi_assert_fail("extend > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 649, __func__));
  size_t max_extend = (bsize >= (4 * 1024)) ? (4) : ((4 * 1024) / bsize);
  if (max_extend < 4)
  {
    max_extend = 4;
  }
  (max_extend > 0) ? ((void) 0) : (_mi_assert_fail("max_extend > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 653, __func__));
  if (extend > max_extend)
  {
    extend = max_extend;
  }
  ((extend > 0) && ((extend + page->capacity) <= page->reserved)) ? ((void) 0) : (_mi_assert_fail("extend > 0 && extend + page->capacity <= page->reserved", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 661, __func__));
  (extend < (1UL << 16)) ? ((void) 0) : (_mi_assert_fail("extend < (1UL<<16)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 662, __func__));
  if ((extend < 2) || (0 == 0))
  {
    mi_page_free_list_extend(page, bsize, extend, &tld->stats);
  }
  else
  {
    mi_page_free_list_extend_secure(heap, page, bsize, extend, &tld->stats);
  }
  page->capacity += (uint16_t) extend;
  _mi_stat_increase(&tld->stats.page_committed, extend * bsize);
  ;
  return 1;
}


----------------------------
None
----------------------------
***/


size_t _mi_page_bin(const mi_page_t *page)
{
  const size_t bin = (mi_page_is_in_full(page)) ? (73U + 1) : ((mi_page_is_huge(page)) ? (73U) : (mi_bin(mi_page_block_size(page))));
  (bin <= (73U + 1)) ? ((void) 0) : (_mi_assert_fail("bin <= MI_BIN_FULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 144, __func__));
  return bin;
}


/*** DEPENDENCIES:
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 591, __func__));
  return page->block_size;
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
inline static bool mi_page_is_in_full(const mi_page_t *page)
{
  return page->flags.x.in_full;
}


----------------------------
inline static bool mi_page_is_huge(const mi_page_t *page)
{
  ((page->is_huge && (_mi_page_segment(page)->kind == MI_SEGMENT_HUGE)) || ((!page->is_huge) && (_mi_page_segment(page)->kind != MI_SEGMENT_HUGE))) ? ((void) 0) : (_mi_assert_fail("(page->is_huge && _mi_page_segment(page)->kind == MI_SEGMENT_HUGE) || (!page->is_huge && _mi_page_segment(page)->kind != MI_SEGMENT_HUGE)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 596, __func__));
  return page->is_huge;
}


----------------------------
inline static size_t mi_bin(size_t size)
{
  size_t wsize = _mi_wsize_from_size(size);
  if (__builtin_expect(!(!(wsize <= 8)), 1))
  {
    return (wsize <= 1) ? (1) : ((wsize + 1) & (~1));
  }
  else
    if (__builtin_expect(!(!(wsize > (((1UL << (3 + (13 + 3))) / 8) / (1 << 3)))), 0))
  {
    return 73U;
  }
  else
  {
    wsize -= 1;
    const size_t b = (((1 << 3) * 8) - 1) - mi_clz(wsize);
    const size_t bin = ((b << 2) + ((wsize >> (b - 2)) & 0x03)) - 3;
    ((bin > 0) && (bin < 73U)) ? ((void) 0) : (_mi_assert_fail("bin > 0 && bin < MI_BIN_HUGE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 88, __func__));
    return bin;
  }
}


----------------------------
None
----------------------------
***/


inline static bool mi_page_queue_is_full(const mi_page_queue_t *pq)
{
  return pq->block_size == (((1UL << (3 + (13 + 3))) / 8) + (2 * (sizeof(uintptr_t))));
}


/*** DEPENDENCIES:
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t block_size;
} mi_page_queue_t
----------------------------
***/


inline static bool mi_page_is_large_or_huge(const mi_page_t *page)
{
  return (mi_page_block_size(page) > ((1UL << (3 + (13 + 3))) / 8)) || mi_page_is_huge(page);
}


/*** DEPENDENCIES:
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 591, __func__));
  return page->block_size;
}


----------------------------
inline static bool mi_page_is_huge(const mi_page_t *page)
{
  ((page->is_huge && (_mi_page_segment(page)->kind == MI_SEGMENT_HUGE)) || ((!page->is_huge) && (_mi_page_segment(page)->kind != MI_SEGMENT_HUGE))) ? ((void) 0) : (_mi_assert_fail("(page->is_huge && _mi_page_segment(page)->kind == MI_SEGMENT_HUGE) || (!page->is_huge && _mi_page_segment(page)->kind != MI_SEGMENT_HUGE)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 596, __func__));
  return page->is_huge;
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
***/


inline static bool mi_page_queue_is_huge(const mi_page_queue_t *pq)
{
  return pq->block_size == (((1UL << (3 + (13 + 3))) / 8) + (sizeof(uintptr_t)));
}


/*** DEPENDENCIES:
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t block_size;
} mi_page_queue_t
----------------------------
***/


static mi_page_queue_t *mi_heap_page_queue_of(mi_heap_t *heap, const mi_page_t *page)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 149, __func__));
  const size_t bin = _mi_page_bin(page);
  mi_page_queue_t *pq = &heap->pages[bin];
  (((mi_page_block_size(page) == pq->block_size) || (mi_page_is_large_or_huge(page) && mi_page_queue_is_huge(pq))) || (mi_page_is_in_full(page) && mi_page_queue_is_full(pq))) ? ((void) 0) : (_mi_assert_fail("(mi_page_block_size(page) == pq->block_size) || (mi_page_is_large_or_huge(page) && mi_page_queue_is_huge(pq)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(pq))", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 152, __func__));
  return pq;
}


/*** DEPENDENCIES:
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 591, __func__));
  return page->block_size;
}


----------------------------
inline static bool mi_page_queue_is_huge(const mi_page_queue_t *pq)
{
  return pq->block_size == (((1UL << (3 + (13 + 3))) / 8) + (sizeof(uintptr_t)));
}


----------------------------
size_t _mi_page_bin(const mi_page_t *page)
{
  const size_t bin = (mi_page_is_in_full(page)) ? (73U + 1) : ((mi_page_is_huge(page)) ? (73U) : (mi_bin(mi_page_block_size(page))));
  (bin <= (73U + 1)) ? ((void) 0) : (_mi_assert_fail("bin <= MI_BIN_FULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 144, __func__));
  return bin;
}


----------------------------
None
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
inline static bool mi_page_is_in_full(const mi_page_t *page)
{
  return page->flags.x.in_full;
}


----------------------------
inline static bool mi_page_is_large_or_huge(const mi_page_t *page)
{
  return (mi_page_block_size(page) > ((1UL << (3 + (13 + 3))) / 8)) || mi_page_is_huge(page);
}


----------------------------
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t block_size;
} mi_page_queue_t
----------------------------
inline static bool mi_page_queue_is_full(const mi_page_queue_t *pq)
{
  return pq->block_size == (((1UL << (3 + (13 + 3))) / 8) + (2 * (sizeof(uintptr_t))));
}


----------------------------
None
----------------------------
***/


static mi_page_queue_t *mi_page_queue_of(const mi_page_t *page)
{
  mi_heap_t *heap = mi_page_heap(page);
  mi_page_queue_t *pq = mi_heap_page_queue_of(heap, page);
  ;
  return pq;
}


/*** DEPENDENCIES:
static mi_page_queue_t *mi_heap_page_queue_of(mi_heap_t *heap, const mi_page_t *page)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 149, __func__));
  const size_t bin = _mi_page_bin(page);
  mi_page_queue_t *pq = &heap->pages[bin];
  (((mi_page_block_size(page) == pq->block_size) || (mi_page_is_large_or_huge(page) && mi_page_queue_is_huge(pq))) || (mi_page_is_in_full(page) && mi_page_queue_is_full(pq))) ? ((void) 0) : (_mi_assert_fail("(mi_page_block_size(page) == pq->block_size) || (mi_page_is_large_or_huge(page) && mi_page_queue_is_huge(pq)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(pq))", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 152, __func__));
  return pq;
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
inline static mi_heap_t *mi_page_heap(const mi_page_t *page)
{
  return (mi_heap_t *) atomic_load_explicit(&((mi_page_t *) page)->xheap, memory_order_relaxed);
}


----------------------------
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t block_size;
} mi_page_queue_t
----------------------------
None
----------------------------
***/


static bool mi_heap_contains_queue(const mi_heap_t *heap, const mi_page_queue_t *pq)
{
  return (pq >= (&heap->pages[0])) && (pq <= (&heap->pages[73U + 1]));
}


/*** DEPENDENCIES:
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t block_size;
} mi_page_queue_t
----------------------------
None
----------------------------
***/


inline static void mi_heap_queue_first_update(mi_heap_t *heap, const mi_page_queue_t *pq)
{
  (mi_heap_contains_queue(heap, pq)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap,pq)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 171, __func__));
  size_t size = pq->block_size;
  if (size > (128 * (sizeof(void *))))
  {
    return;
  }
  mi_page_t *page = pq->first;
  unsigned int page_idx = 0;
  if (pq->first == 0)
  {
    page_idx = (mi_page_t *) (&_mi_page_empty);
  }
  size_t start;
  size_t idx = _mi_wsize_from_size(size);
  mi_page_t **pages_free = heap->pages_free_direct;
  if (pages_free[idx] == (&page[page_idx]))
  {
    return;
  }
  if (idx <= 1)
  {
    start = 0;
  }
  else
  {
    size_t bin = mi_bin(size);
    const mi_page_queue_t *prev = pq - 1;
    unsigned int prev_idx = 0;
    while ((bin == mi_bin(prev->block_size)) && ((&prev[prev_idx]) > (&heap->pages[0])))
    {
      prev_idx -= 1;
    }

    start = 1 + _mi_wsize_from_size(prev->block_size);
    if (start > idx)
    {
      start = idx;
    }
  }
  (start <= idx) ? ((void) 0) : (_mi_assert_fail("start <= idx", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 201, __func__));
  for (size_t sz = start; sz <= idx; sz += 1)
  {
    pages_free[sz] = &page[page_idx];
  }

}


/*** DEPENDENCIES:
static bool mi_heap_contains_queue(const mi_heap_t *heap, const mi_page_queue_t *pq)
{
  return (pq >= (&heap->pages[0])) && (pq <= (&heap->pages[73U + 1]));
}


----------------------------
None
----------------------------
extern const mi_page_t _mi_page_empty
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
inline static size_t _mi_wsize_from_size(size_t size)
{
  (size <= (SIZE_MAX - (sizeof(uintptr_t)))) ? ((void) 0) : (_mi_assert_fail("size <= SIZE_MAX - sizeof(uintptr_t)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 445, __func__));
  return ((size + (sizeof(uintptr_t))) - 1) / (sizeof(uintptr_t));
}


----------------------------
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t block_size;
} mi_page_queue_t
----------------------------
inline static size_t mi_bin(size_t size)
{
  size_t wsize = _mi_wsize_from_size(size);
  if (__builtin_expect(!(!(wsize <= 8)), 1))
  {
    return (wsize <= 1) ? (1) : ((wsize + 1) & (~1));
  }
  else
    if (__builtin_expect(!(!(wsize > (((1UL << (3 + (13 + 3))) / 8) / (1 << 3)))), 0))
  {
    return 73U;
  }
  else
  {
    wsize -= 1;
    const size_t b = (((1 << 3) * 8) - 1) - mi_clz(wsize);
    const size_t bin = ((b << 2) + ((wsize >> (b - 2)) & 0x03)) - 3;
    ((bin > 0) && (bin < 73U)) ? ((void) 0) : (_mi_assert_fail("bin > 0 && bin < MI_BIN_HUGE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 88, __func__));
    return bin;
  }
}


----------------------------
None
----------------------------
***/


static void mi_page_queue_remove(mi_page_queue_t *queue, mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 214, __func__));
  ;
  (((mi_page_block_size(page) == queue->block_size) || (mi_page_is_large_or_huge(page) && mi_page_queue_is_huge(queue))) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) == queue->block_size || (mi_page_is_large_or_huge(page) && mi_page_queue_is_huge(queue)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 216, __func__));
  mi_heap_t *heap = mi_page_heap(page);
  if (page->prev != 0)
  {
    page->prev->next = page->next;
  }
  if (page->next != 0)
  {
    page->next->prev = page->prev;
  }
  if (page == queue->last)
  {
    queue->last = page->prev;
  }
  if (page == queue->first)
  {
    queue->first = page->next;
    (mi_heap_contains_queue(heap, queue)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap, queue)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 227, __func__));
    mi_heap_queue_first_update(heap, queue);
  }
  heap->page_count -= 1;
  page->next = 0;
  page->prev = 0;
  mi_page_set_in_full(page, 0);
}


/*** DEPENDENCIES:
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 591, __func__));
  return page->block_size;
}


----------------------------
inline static bool mi_page_queue_is_huge(const mi_page_queue_t *pq)
{
  return pq->block_size == (((1UL << (3 + (13 + 3))) / 8) + (sizeof(uintptr_t)));
}


----------------------------
static bool mi_heap_contains_queue(const mi_heap_t *heap, const mi_page_queue_t *pq)
{
  return (pq >= (&heap->pages[0])) && (pq <= (&heap->pages[73U + 1]));
}


----------------------------
None
----------------------------
inline static mi_heap_t *mi_page_heap(const mi_page_t *page)
{
  return (mi_heap_t *) atomic_load_explicit(&((mi_page_t *) page)->xheap, memory_order_relaxed);
}


----------------------------
inline static void mi_page_set_in_full(mi_page_t *page, bool in_full)
{
  page->flags.x.in_full = in_full;
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
inline static bool mi_page_is_in_full(const mi_page_t *page)
{
  return page->flags.x.in_full;
}


----------------------------
inline static void mi_heap_queue_first_update(mi_heap_t *heap, const mi_page_queue_t *pq)
{
  (mi_heap_contains_queue(heap, pq)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap,pq)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 171, __func__));
  size_t size = pq->block_size;
  if (size > (128 * (sizeof(void *))))
  {
    return;
  }
  mi_page_t *page = pq->first;
  unsigned int page_idx = 0;
  if (pq->first == 0)
  {
    page_idx = (mi_page_t *) (&_mi_page_empty);
  }
  size_t start;
  size_t idx = _mi_wsize_from_size(size);
  mi_page_t **pages_free = heap->pages_free_direct;
  if (pages_free[idx] == (&page[page_idx]))
  {
    return;
  }
  if (idx <= 1)
  {
    start = 0;
  }
  else
  {
    size_t bin = mi_bin(size);
    const mi_page_queue_t *prev = pq - 1;
    unsigned int prev_idx = 0;
    while ((bin == mi_bin(prev->block_size)) && ((&prev[prev_idx]) > (&heap->pages[0])))
    {
      prev_idx -= 1;
    }

    start = 1 + _mi_wsize_from_size(prev->block_size);
    if (start > idx)
    {
      start = idx;
    }
  }
  (start <= idx) ? ((void) 0) : (_mi_assert_fail("start <= idx", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 201, __func__));
  for (size_t sz = start; sz <= idx; sz += 1)
  {
    pages_free[sz] = &page[page_idx];
  }

}


----------------------------
inline static bool mi_page_is_large_or_huge(const mi_page_t *page)
{
  return (mi_page_block_size(page) > ((1UL << (3 + (13 + 3))) / 8)) || mi_page_is_huge(page);
}


----------------------------
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t block_size;
} mi_page_queue_t
----------------------------
inline static bool mi_page_queue_is_full(const mi_page_queue_t *pq)
{
  return pq->block_size == (((1UL << (3 + (13 + 3))) / 8) + (2 * (sizeof(uintptr_t))));
}


----------------------------
None
----------------------------
***/


void _mi_page_free(mi_page_t *page, mi_page_queue_t *pq, bool force)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 433, __func__));
  ;
  (pq == mi_page_queue_of(page)) ? ((void) 0) : (_mi_assert_fail("pq == mi_page_queue_of(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 435, __func__));
  (mi_page_all_free(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_all_free(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 436, __func__));
  (mi_page_thread_free_flag(page) != MI_DELAYED_FREEING) ? ((void) 0) : (_mi_assert_fail("mi_page_thread_free_flag(page)!=MI_DELAYED_FREEING", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 437, __func__));
  mi_page_set_has_aligned(page, 0);
  mi_heap_t *heap = mi_page_heap(page);
  mi_segments_tld_t *segments_tld = &heap->tld->segments;
  mi_page_queue_remove(pq, page);
  mi_page_set_heap(page, 0);
  _mi_segment_page_free(page, force, segments_tld);
}


/*** DEPENDENCIES:
typedef struct mi_segments_tld_s
{
  mi_span_queue_t spans[35 + 1];
  size_t count;
  size_t peak_count;
  size_t current_size;
  size_t peak_size;
  size_t reclaim_count;
  mi_subproc_t *subproc;
  mi_stats_t *stats;
} mi_segments_tld_t
----------------------------
None
----------------------------
inline static mi_heap_t *mi_page_heap(const mi_page_t *page)
{
  return (mi_heap_t *) atomic_load_explicit(&((mi_page_t *) page)->xheap, memory_order_relaxed);
}


----------------------------
inline static bool mi_page_all_free(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 656, __func__));
  return page->used == 0;
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
static void mi_page_queue_remove(mi_page_queue_t *queue, mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 214, __func__));
  ;
  (((mi_page_block_size(page) == queue->block_size) || (mi_page_is_large_or_huge(page) && mi_page_queue_is_huge(queue))) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) == queue->block_size || (mi_page_is_large_or_huge(page) && mi_page_queue_is_huge(queue)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 216, __func__));
  mi_heap_t *heap = mi_page_heap(page);
  if (page->prev != 0)
  {
    page->prev->next = page->next;
  }
  if (page->next != 0)
  {
    page->next->prev = page->prev;
  }
  if (page == queue->last)
  {
    queue->last = page->prev;
  }
  if (page == queue->first)
  {
    queue->first = page->next;
    (mi_heap_contains_queue(heap, queue)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap, queue)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 227, __func__));
    mi_heap_queue_first_update(heap, queue);
  }
  heap->page_count -= 1;
  page->next = 0;
  page->prev = 0;
  mi_page_set_in_full(page, 0);
}


----------------------------
inline static void mi_page_set_has_aligned(mi_page_t *page, bool has_aligned)
{
  page->flags.x.has_aligned = has_aligned;
}


----------------------------
inline static void mi_page_set_heap(mi_page_t *page, mi_heap_t *heap)
{
  (mi_page_thread_free_flag(page) != MI_DELAYED_FREEING) ? ((void) 0) : (_mi_assert_fail("mi_page_thread_free_flag(page) != MI_DELAYED_FREEING", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 631, __func__));
  atomic_store_explicit(&page->xheap, (uintptr_t) heap, memory_order_release);
  if (heap != 0)
  {
    page->heap_tag = heap->tag;
  }
}


----------------------------
inline static mi_delayed_t mi_page_thread_free_flag(const mi_page_t *page)
{
  return (mi_delayed_t) (atomic_load_explicit(&((mi_page_t *) page)->xthread_free, memory_order_relaxed) & 3);
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
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t block_size;
} mi_page_queue_t
----------------------------
void _mi_segment_page_free(mi_page_t *page, bool force, mi_segments_tld_t *tld)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c", 1053, __func__));
  mi_segment_t *segment = _mi_page_segment(page);
  ;
  mi_segment_page_clear(page, tld);
  ;
  if (segment->used == 0)
  {
    mi_segment_free(segment, force, tld);
  }
  else
    if (segment->used == segment->abandoned)
  {
    mi_segment_abandon(segment, tld);
  }
  else
  {
    mi_segment_try_purge(segment, 0);
  }
}


----------------------------
None
----------------------------
***/


void _mi_heap_collect_retired(mi_heap_t *heap, bool force)
{
  size_t min = 73U + 1;
  size_t max = 0;
  for (size_t bin = heap->page_retired_min; bin <= heap->page_retired_max; bin += 1)
  {
    mi_page_queue_t *pq = &heap->pages[bin];
    mi_page_t *page = pq->first;
    if ((page != 0) && (page->retire_expire != 0))
    {
      if (mi_page_all_free(page))
      {
        page->retire_expire -= 1;
        if (force || (page->retire_expire == 0))
        {
          _mi_page_free(pq->first, pq, force);
        }
        else
        {
          if (bin < min)
          {
            min = bin;
          }
          if (bin > max)
          {
            max = bin;
          }
        }
      }
      else
      {
        page->retire_expire = 0;
      }
    }
  }

  heap->page_retired_min = min;
  heap->page_retired_max = max;
}


/*** DEPENDENCIES:
void _mi_page_free(mi_page_t *page, mi_page_queue_t *pq, bool force)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 433, __func__));
  ;
  (pq == mi_page_queue_of(page)) ? ((void) 0) : (_mi_assert_fail("pq == mi_page_queue_of(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 435, __func__));
  (mi_page_all_free(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_all_free(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 436, __func__));
  (mi_page_thread_free_flag(page) != MI_DELAYED_FREEING) ? ((void) 0) : (_mi_assert_fail("mi_page_thread_free_flag(page)!=MI_DELAYED_FREEING", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 437, __func__));
  mi_page_set_has_aligned(page, 0);
  mi_heap_t *heap = mi_page_heap(page);
  mi_segments_tld_t *segments_tld = &heap->tld->segments;
  mi_page_queue_remove(pq, page);
  mi_page_set_heap(page, 0);
  _mi_segment_page_free(page, force, segments_tld);
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
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t block_size;
} mi_page_queue_t
----------------------------
inline static bool mi_page_all_free(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 656, __func__));
  return page->used == 0;
}


----------------------------
None
----------------------------
***/


size_t _mi_bin(size_t size)
{
  return mi_bin(size);
}


/*** DEPENDENCIES:
inline static size_t mi_bin(size_t size)
{
  size_t wsize = _mi_wsize_from_size(size);
  if (__builtin_expect(!(!(wsize <= 8)), 1))
  {
    return (wsize <= 1) ? (1) : ((wsize + 1) & (~1));
  }
  else
    if (__builtin_expect(!(!(wsize > (((1UL << (3 + (13 + 3))) / 8) / (1 << 3)))), 0))
  {
    return 73U;
  }
  else
  {
    wsize -= 1;
    const size_t b = (((1 << 3) * 8) - 1) - mi_clz(wsize);
    const size_t bin = ((b << 2) + ((wsize >> (b - 2)) & 0x03)) - 3;
    ((bin > 0) && (bin < 73U)) ? ((void) 0) : (_mi_assert_fail("bin > 0 && bin < MI_BIN_HUGE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 88, __func__));
    return bin;
  }
}


----------------------------
***/


static bool mi_page_queue_contains(mi_page_queue_t *queue, const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 119, __func__));
  mi_page_t *list = queue->first;
  unsigned int list_idx = 0;
  while ((&list[list_idx]) != 0)
  {
    ((list->next == 0) || (list->next->prev == (&list[list_idx]))) ? ((void) 0) : (_mi_assert_fail("list->next == NULL || list->next->prev == list", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 122, __func__));
    ((list->prev == 0) || (list->prev->next == (&list[list_idx]))) ? ((void) 0) : (_mi_assert_fail("list->prev == NULL || list->prev->next == list", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 123, __func__));
    if ((&list[list_idx]) == page)
    {
      break;
    }
    list_idx = list_idx->next;
  }

  return (&list[list_idx]) == page;
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
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t block_size;
} mi_page_queue_t
----------------------------
None
----------------------------
***/


static void mi_page_queue_push(mi_heap_t *heap, mi_page_queue_t *queue, mi_page_t *page)
{
  (mi_page_heap(page) == heap) ? ((void) 0) : (_mi_assert_fail("mi_page_heap(page) == heap", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 239, __func__));
  (!mi_page_queue_contains(queue, page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_queue_contains(queue, page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 240, __func__));
  (((mi_page_block_size(page) == queue->block_size) || (mi_page_is_large_or_huge(page) && mi_page_queue_is_huge(queue))) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) == queue->block_size || (mi_page_is_large_or_huge(page) && mi_page_queue_is_huge(queue)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 244, __func__));
  mi_page_set_in_full(page, mi_page_queue_is_full(queue));
  page->next = queue->first;
  page->prev = 0;
  if (queue->first != 0)
  {
    (queue->first->prev == 0) ? ((void) 0) : (_mi_assert_fail("queue->first->prev == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 253, __func__));
    queue->first->prev = page;
    queue->first = page;
  }
  else
  {
    queue->first = (queue->last = page);
  }
  mi_heap_queue_first_update(heap, queue);
  heap->page_count += 1;
}


/*** DEPENDENCIES:
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 591, __func__));
  return page->block_size;
}


----------------------------
inline static bool mi_page_queue_is_huge(const mi_page_queue_t *pq)
{
  return pq->block_size == (((1UL << (3 + (13 + 3))) / 8) + (sizeof(uintptr_t)));
}


----------------------------
None
----------------------------
inline static mi_heap_t *mi_page_heap(const mi_page_t *page)
{
  return (mi_heap_t *) atomic_load_explicit(&((mi_page_t *) page)->xheap, memory_order_relaxed);
}


----------------------------
inline static void mi_page_set_in_full(mi_page_t *page, bool in_full)
{
  page->flags.x.in_full = in_full;
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
inline static bool mi_page_is_in_full(const mi_page_t *page)
{
  return page->flags.x.in_full;
}


----------------------------
static bool mi_page_queue_contains(mi_page_queue_t *queue, const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 119, __func__));
  mi_page_t *list = queue->first;
  unsigned int list_idx = 0;
  while ((&list[list_idx]) != 0)
  {
    ((list->next == 0) || (list->next->prev == (&list[list_idx]))) ? ((void) 0) : (_mi_assert_fail("list->next == NULL || list->next->prev == list", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 122, __func__));
    ((list->prev == 0) || (list->prev->next == (&list[list_idx]))) ? ((void) 0) : (_mi_assert_fail("list->prev == NULL || list->prev->next == list", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 123, __func__));
    if ((&list[list_idx]) == page)
    {
      break;
    }
    list_idx = list_idx->next;
  }

  return (&list[list_idx]) == page;
}


----------------------------
inline static void mi_heap_queue_first_update(mi_heap_t *heap, const mi_page_queue_t *pq)
{
  (mi_heap_contains_queue(heap, pq)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap,pq)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 171, __func__));
  size_t size = pq->block_size;
  if (size > (128 * (sizeof(void *))))
  {
    return;
  }
  mi_page_t *page = pq->first;
  unsigned int page_idx = 0;
  if (pq->first == 0)
  {
    page_idx = (mi_page_t *) (&_mi_page_empty);
  }
  size_t start;
  size_t idx = _mi_wsize_from_size(size);
  mi_page_t **pages_free = heap->pages_free_direct;
  if (pages_free[idx] == (&page[page_idx]))
  {
    return;
  }
  if (idx <= 1)
  {
    start = 0;
  }
  else
  {
    size_t bin = mi_bin(size);
    const mi_page_queue_t *prev = pq - 1;
    unsigned int prev_idx = 0;
    while ((bin == mi_bin(prev->block_size)) && ((&prev[prev_idx]) > (&heap->pages[0])))
    {
      prev_idx -= 1;
    }

    start = 1 + _mi_wsize_from_size(prev->block_size);
    if (start > idx)
    {
      start = idx;
    }
  }
  (start <= idx) ? ((void) 0) : (_mi_assert_fail("start <= idx", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 201, __func__));
  for (size_t sz = start; sz <= idx; sz += 1)
  {
    pages_free[sz] = &page[page_idx];
  }

}


----------------------------
inline static bool mi_page_is_large_or_huge(const mi_page_t *page)
{
  return (mi_page_block_size(page) > ((1UL << (3 + (13 + 3))) / 8)) || mi_page_is_huge(page);
}


----------------------------
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t block_size;
} mi_page_queue_t
----------------------------
inline static bool mi_page_queue_is_full(const mi_page_queue_t *pq)
{
  return pq->block_size == (((1UL << (3 + (13 + 3))) / 8) + (2 * (sizeof(uintptr_t))));
}


----------------------------
None
----------------------------
***/


void _mi_page_reclaim(mi_heap_t *heap, mi_page_t *page)
{
  ;
  (mi_page_heap(page) == heap) ? ((void) 0) : (_mi_assert_fail("mi_page_heap(page) == heap", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 260, __func__));
  (mi_page_thread_free_flag(page) != MI_NEVER_DELAYED_FREE) ? ((void) 0) : (_mi_assert_fail("mi_page_thread_free_flag(page) != MI_NEVER_DELAYED_FREE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 261, __func__));
  mi_page_queue_t *pq = mi_page_queue(heap, mi_page_block_size(page));
  mi_page_queue_push(heap, pq, page);
  ;
}


/*** DEPENDENCIES:
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 591, __func__));
  return page->block_size;
}


----------------------------
static void mi_page_queue_push(mi_heap_t *heap, mi_page_queue_t *queue, mi_page_t *page)
{
  (mi_page_heap(page) == heap) ? ((void) 0) : (_mi_assert_fail("mi_page_heap(page) == heap", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 239, __func__));
  (!mi_page_queue_contains(queue, page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_queue_contains(queue, page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 240, __func__));
  (((mi_page_block_size(page) == queue->block_size) || (mi_page_is_large_or_huge(page) && mi_page_queue_is_huge(queue))) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) == queue->block_size || (mi_page_is_large_or_huge(page) && mi_page_queue_is_huge(queue)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 244, __func__));
  mi_page_set_in_full(page, mi_page_queue_is_full(queue));
  page->next = queue->first;
  page->prev = 0;
  if (queue->first != 0)
  {
    (queue->first->prev == 0) ? ((void) 0) : (_mi_assert_fail("queue->first->prev == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 253, __func__));
    queue->first->prev = page;
    queue->first = page;
  }
  else
  {
    queue->first = (queue->last = page);
  }
  mi_heap_queue_first_update(heap, queue);
  heap->page_count += 1;
}


----------------------------
None
----------------------------
inline static mi_heap_t *mi_page_heap(const mi_page_t *page)
{
  return (mi_heap_t *) atomic_load_explicit(&((mi_page_t *) page)->xheap, memory_order_relaxed);
}


----------------------------
inline static mi_page_queue_t *mi_page_queue(const mi_heap_t *heap, size_t size)
{
  return &((mi_heap_t *) heap)->pages[_mi_bin(size)];
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
inline static mi_delayed_t mi_page_thread_free_flag(const mi_page_t *page)
{
  return (mi_delayed_t) (atomic_load_explicit(&((mi_page_t *) page)->xthread_free, memory_order_relaxed) & 3);
}


----------------------------
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t block_size;
} mi_page_queue_t
----------------------------
None
----------------------------
***/


bool _mi_page_try_use_delayed_free(mi_page_t *page, mi_delayed_t delay, bool override_never)
{
  mi_thread_free_t tfreex;
  mi_delayed_t old_delay;
  mi_thread_free_t tfree;
  size_t yield_count = 0;
  do
  {
    tfree = atomic_load_explicit(&page->xthread_free, memory_order_acquire);
    tfreex = mi_tf_set_delayed(tfree, delay);
    old_delay = mi_tf_delayed(tfree);
    if (__builtin_expect(!(!(old_delay == MI_DELAYED_FREEING)), 0))
    {
      if (yield_count >= 4)
      {
        return 0;
      }
      yield_count += 1;
      mi_atomic_yield();
    }
    else
      if (delay == old_delay)
    {
      break;
    }
    else
      if ((!override_never) && (old_delay == MI_NEVER_DELAYED_FREE))
    {
      break;
    }
  }
  while ((old_delay == MI_DELAYED_FREEING) || (!atomic_compare_exchange_weak_explicit(&page->xthread_free, &tfree, tfreex, memory_order_release, memory_order_relaxed)));
  return 1;
}


/*** DEPENDENCIES:
inline static void mi_atomic_yield(void)
{
}


----------------------------
typedef enum mi_delayed_e
{
  MI_USE_DELAYED_FREE = 0,
  MI_DELAYED_FREEING = 1,
  MI_NO_DELAYED_FREE = 2,
  MI_NEVER_DELAYED_FREE = 3
} mi_delayed_t
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
inline static mi_delayed_t mi_tf_delayed(mi_thread_free_t tf)
{
  return (mi_delayed_t) (tf & 0x03);
}


----------------------------
inline static mi_thread_free_t mi_tf_set_delayed(mi_thread_free_t tf, mi_delayed_t delayed)
{
  return mi_tf_make(mi_tf_block(tf), delayed);
}


----------------------------
typedef uintptr_t mi_thread_free_t
----------------------------
***/


void _mi_page_use_delayed_free(mi_page_t *page, mi_delayed_t delay, bool override_never)
{
  while (!_mi_page_try_use_delayed_free(page, delay, override_never))
  {
    mi_atomic_yield();
  }

}


/*** DEPENDENCIES:
bool _mi_page_try_use_delayed_free(mi_page_t *page, mi_delayed_t delay, bool override_never)
{
  mi_thread_free_t tfreex;
  mi_delayed_t old_delay;
  mi_thread_free_t tfree;
  size_t yield_count = 0;
  do
  {
    tfree = atomic_load_explicit(&page->xthread_free, memory_order_acquire);
    tfreex = mi_tf_set_delayed(tfree, delay);
    old_delay = mi_tf_delayed(tfree);
    if (__builtin_expect(!(!(old_delay == MI_DELAYED_FREEING)), 0))
    {
      if (yield_count >= 4)
      {
        return 0;
      }
      yield_count += 1;
      mi_atomic_yield();
    }
    else
      if (delay == old_delay)
    {
      break;
    }
    else
      if ((!override_never) && (old_delay == MI_NEVER_DELAYED_FREE))
    {
      break;
    }
  }
  while ((old_delay == MI_DELAYED_FREEING) || (!atomic_compare_exchange_weak_explicit(&page->xthread_free, &tfree, tfreex, memory_order_release, memory_order_relaxed)));
  return 1;
}


----------------------------
inline static void mi_atomic_yield(void)
{
}


----------------------------
typedef enum mi_delayed_e
{
  MI_USE_DELAYED_FREE = 0,
  MI_DELAYED_FREEING = 1,
  MI_NO_DELAYED_FREE = 2,
  MI_NEVER_DELAYED_FREE = 3
} mi_delayed_t
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
***/


static void _mi_page_thread_free_collect(mi_page_t *page)
{
  mi_block_t *head;
  unsigned int head_idx = 0;
  mi_thread_free_t tfreex;
  mi_thread_free_t tfree = atomic_load_explicit(&page->xthread_free, memory_order_relaxed);
  do
  {
    head_idx = mi_tf_block(tfree);
    tfreex = mi_tf_set_block(tfree, 0);
  }
  while (!atomic_compare_exchange_weak_explicit(&page->xthread_free, &tfree, tfreex, memory_order_acq_rel, memory_order_acquire));
  if ((&head[head_idx]) == 0)
  {
    return;
  }
  size_t max_count = page->capacity;
  size_t count = 1;
  mi_block_t *tail = head;
  unsigned int tail_idx = 0;
  mi_block_t *next;
  unsigned int next_idx = 0;
  while (((next_idx = mi_block_next(page, tail)) != 0) && (count <= max_count))
  {
    count += 1;
    tail_idx = &next[next_idx];
  }

  if (count > max_count)
  {
    _mi_error_message(14, "corrupted thread-free list\n");
    return;
  }
  mi_block_set_next(page, tail, page->local_free);
  page->local_free = &head[head_idx];
  page->used -= (uint16_t) count;
}


/*** DEPENDENCIES:
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
inline static void mi_block_set_next(const mi_page_t *page, mi_block_t *block, const mi_block_t *next)
{
  mi_block_set_nextx(page, block, next, page->keys);
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
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
inline static mi_block_t *mi_tf_block(mi_thread_free_t tf)
{
  return (mi_block_t *) (tf & (~0x03));
}


----------------------------
inline static mi_thread_free_t mi_tf_set_block(mi_thread_free_t tf, mi_block_t *block)
{
  return mi_tf_make(block, mi_tf_delayed(tf));
}


----------------------------
typedef uintptr_t mi_thread_free_t
----------------------------
***/


void _mi_page_free_collect(mi_page_t *page, bool force)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 218, __func__));
  if (force || (mi_page_thread_free(page) != 0))
  {
    _mi_page_thread_free_collect(page);
  }
  if (page->local_free != 0)
  {
    if (__builtin_expect(!(!(page->free == 0)), 1))
    {
      page->free = page->local_free;
      page->local_free = 0;
      page->free_is_zero = 0;
    }
    else
      if (force)
    {
      mi_block_t *tail = page->local_free;
      unsigned int tail_idx = 0;
      mi_block_t *next;
      unsigned int next_idx = 0;
      while ((next_idx = mi_block_next(page, tail)) != 0)
      {
        tail_idx = &next[next_idx];
      }

      mi_block_set_next(page, tail, page->free);
      page->free = page->local_free;
      page->local_free = 0;
      page->free_is_zero = 0;
    }
  }
  ((!force) || (page->local_free == 0)) ? ((void) 0) : (_mi_assert_fail("!force || page->local_free == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 247, __func__));
}


/*** DEPENDENCIES:
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
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
inline static void mi_block_set_next(const mi_page_t *page, mi_block_t *block, const mi_block_t *next)
{
  mi_block_set_nextx(page, block, next, page->keys);
}


----------------------------
inline static mi_block_t *mi_page_thread_free(const mi_page_t *page)
{
  return (mi_block_t *) (atomic_load_explicit(&((mi_page_t *) page)->xthread_free, memory_order_relaxed) & (~3));
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
static void _mi_page_thread_free_collect(mi_page_t *page)
{
  mi_block_t *head;
  unsigned int head_idx = 0;
  mi_thread_free_t tfreex;
  mi_thread_free_t tfree = atomic_load_explicit(&page->xthread_free, memory_order_relaxed);
  do
  {
    head_idx = mi_tf_block(tfree);
    tfreex = mi_tf_set_block(tfree, 0);
  }
  while (!atomic_compare_exchange_weak_explicit(&page->xthread_free, &tfree, tfreex, memory_order_acq_rel, memory_order_acquire));
  if ((&head[head_idx]) == 0)
  {
    return;
  }
  size_t max_count = page->capacity;
  size_t count = 1;
  mi_block_t *tail = head;
  unsigned int tail_idx = 0;
  mi_block_t *next;
  unsigned int next_idx = 0;
  while (((next_idx = mi_block_next(page, tail)) != 0) && (count <= max_count))
  {
    count += 1;
    tail_idx = &next[next_idx];
  }

  if (count > max_count)
  {
    _mi_error_message(14, "corrupted thread-free list\n");
    return;
  }
  mi_block_set_next(page, tail, page->local_free);
  page->local_free = &head[head_idx];
  page->used -= (uint16_t) count;
}


----------------------------
None
----------------------------
***/


void _mi_page_abandon(mi_page_t *page, mi_page_queue_t *pq)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 381, __func__));
  ;
  (pq == mi_page_queue_of(page)) ? ((void) 0) : (_mi_assert_fail("pq == mi_page_queue_of(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 383, __func__));
  (mi_page_heap(page) != 0) ? ((void) 0) : (_mi_assert_fail("mi_page_heap(page) != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 384, __func__));
  mi_heap_t *pheap = mi_page_heap(page);
  mi_segments_tld_t *segments_tld = &pheap->tld->segments;
  mi_page_queue_remove(pq, page);
  (mi_page_thread_free_flag(page) == MI_NEVER_DELAYED_FREE) ? ((void) 0) : (_mi_assert_fail("mi_page_thread_free_flag(page)==MI_NEVER_DELAYED_FREE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 393, __func__));
  mi_page_set_heap(page, 0);
  for (mi_block_t *block = (mi_block_t *) pheap->thread_delayed_free; (&block[block_idx]) != 0; block_idx = mi_block_nextx(pheap, block_idx, pheap->keys))
  {
    (_mi_ptr_page(block) != page) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(block) != page", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 399, __func__));
  }

  unsigned int block_idx = 0;
  (mi_page_heap(page) == 0) ? ((void) 0) : (_mi_assert_fail("mi_page_heap(page) == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 404, __func__));
  _mi_segment_page_abandon(page, segments_tld);
}


/*** DEPENDENCIES:
typedef struct mi_segments_tld_s
{
  mi_span_queue_t spans[35 + 1];
  size_t count;
  size_t peak_count;
  size_t current_size;
  size_t peak_size;
  size_t reclaim_count;
  mi_subproc_t *subproc;
  mi_stats_t *stats;
} mi_segments_tld_t
----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
None
----------------------------
inline static mi_heap_t *mi_page_heap(const mi_page_t *page)
{
  return (mi_heap_t *) atomic_load_explicit(&((mi_page_t *) page)->xheap, memory_order_relaxed);
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
static void mi_page_queue_remove(mi_page_queue_t *queue, mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 214, __func__));
  ;
  (((mi_page_block_size(page) == queue->block_size) || (mi_page_is_large_or_huge(page) && mi_page_queue_is_huge(queue))) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) == queue->block_size || (mi_page_is_large_or_huge(page) && mi_page_queue_is_huge(queue)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 216, __func__));
  mi_heap_t *heap = mi_page_heap(page);
  if (page->prev != 0)
  {
    page->prev->next = page->next;
  }
  if (page->next != 0)
  {
    page->next->prev = page->prev;
  }
  if (page == queue->last)
  {
    queue->last = page->prev;
  }
  if (page == queue->first)
  {
    queue->first = page->next;
    (mi_heap_contains_queue(heap, queue)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap, queue)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 227, __func__));
    mi_heap_queue_first_update(heap, queue);
  }
  heap->page_count -= 1;
  page->next = 0;
  page->prev = 0;
  mi_page_set_in_full(page, 0);
}


----------------------------
inline static void mi_page_set_heap(mi_page_t *page, mi_heap_t *heap)
{
  (mi_page_thread_free_flag(page) != MI_DELAYED_FREEING) ? ((void) 0) : (_mi_assert_fail("mi_page_thread_free_flag(page) != MI_DELAYED_FREEING", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 631, __func__));
  atomic_store_explicit(&page->xheap, (uintptr_t) heap, memory_order_release);
  if (heap != 0)
  {
    page->heap_tag = heap->tag;
  }
}


----------------------------
inline static mi_block_t *mi_block_nextx(const void *null, const mi_block_t *block, const uintptr_t *keys)
{
  ;
  mi_block_t *next;
  unsigned int next_idx = 0;
  next_idx = (mi_block_t *) mi_ptr_decode(null, block->next_idx, keys);
  ;
  return next;
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
void _mi_segment_page_abandon(mi_page_t *page, mi_segments_tld_t *tld)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c", 1136, __func__));
  (mi_page_thread_free_flag(page) == MI_NEVER_DELAYED_FREE) ? ((void) 0) : (_mi_assert_fail("mi_page_thread_free_flag(page)==MI_NEVER_DELAYED_FREE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c", 1137, __func__));
  (mi_page_heap(page) == 0) ? ((void) 0) : (_mi_assert_fail("mi_page_heap(page) == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c", 1138, __func__));
  mi_segment_t *segment = _mi_page_segment(page);
  ;
  segment->abandoned += 1;
  _mi_stat_increase(&tld->stats->pages_abandoned, 1);
  (segment->abandoned <= segment->used) ? ((void) 0) : (_mi_assert_fail("segment->abandoned <= segment->used", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c", 1145, __func__));
  if (segment->used == segment->abandoned)
  {
    mi_segment_abandon(segment, tld);
  }
}


----------------------------
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t block_size;
} mi_page_queue_t
----------------------------
inline static mi_delayed_t mi_page_thread_free_flag(const mi_page_t *page)
{
  return (mi_delayed_t) (atomic_load_explicit(&((mi_page_t *) page)->xthread_free, memory_order_relaxed) & 3);
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
static void * _Atomic deferred_arg
----------------------------
static mi_deferred_free_fun * volatile deferred_free = 0
----------------------------
None
----------------------------
***/


size_t _mi_page_queue_append(mi_heap_t *heap, mi_page_queue_t *pq, mi_page_queue_t *append)
{
  (mi_heap_contains_queue(heap, pq)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap,pq)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 355, __func__));
  (pq->block_size == append->block_size) ? ((void) 0) : (_mi_assert_fail("pq->block_size == append->block_size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 356, __func__));
  if (append->first == 0)
  {
    return 0;
  }
  size_t count = 0;
  for (mi_page_t *page = append->first; (&page[page_idx]) != 0; page_idx = page_idx->next)
  {
    atomic_store_explicit(&page->xheap, (uintptr_t) heap, memory_order_release);
    _mi_page_use_delayed_free(page, MI_USE_DELAYED_FREE, 0);
    count += 1;
  }

  unsigned int page_idx = 0;
  if (pq->last == 0)
  {
    (pq->first == 0) ? ((void) 0) : (_mi_assert_fail("pq->first==NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 375, __func__));
    pq->first = append->first;
    pq->last = append->last;
    mi_heap_queue_first_update(heap, pq);
  }
  else
  {
    (pq->last != 0) ? ((void) 0) : (_mi_assert_fail("pq->last!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 382, __func__));
    (append->first != 0) ? ((void) 0) : (_mi_assert_fail("append->first!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 383, __func__));
    pq->last->next = append->first;
    append->first->prev = pq->last;
    pq->last = append->last;
  }
  return count;
}


/*** DEPENDENCIES:
static bool mi_heap_contains_queue(const mi_heap_t *heap, const mi_page_queue_t *pq)
{
  return (pq >= (&heap->pages[0])) && (pq <= (&heap->pages[73U + 1]));
}


----------------------------
void _mi_page_use_delayed_free(mi_page_t *page, mi_delayed_t delay, bool override_never)
{
  while (!_mi_page_try_use_delayed_free(page, delay, override_never))
  {
    mi_atomic_yield();
  }

}


----------------------------
None
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
inline static void mi_heap_queue_first_update(mi_heap_t *heap, const mi_page_queue_t *pq)
{
  (mi_heap_contains_queue(heap, pq)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap,pq)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 171, __func__));
  size_t size = pq->block_size;
  if (size > (128 * (sizeof(void *))))
  {
    return;
  }
  mi_page_t *page = pq->first;
  unsigned int page_idx = 0;
  if (pq->first == 0)
  {
    page_idx = (mi_page_t *) (&_mi_page_empty);
  }
  size_t start;
  size_t idx = _mi_wsize_from_size(size);
  mi_page_t **pages_free = heap->pages_free_direct;
  if (pages_free[idx] == (&page[page_idx]))
  {
    return;
  }
  if (idx <= 1)
  {
    start = 0;
  }
  else
  {
    size_t bin = mi_bin(size);
    const mi_page_queue_t *prev = pq - 1;
    unsigned int prev_idx = 0;
    while ((bin == mi_bin(prev->block_size)) && ((&prev[prev_idx]) > (&heap->pages[0])))
    {
      prev_idx -= 1;
    }

    start = 1 + _mi_wsize_from_size(prev->block_size);
    if (start > idx)
    {
      start = idx;
    }
  }
  (start <= idx) ? ((void) 0) : (_mi_assert_fail("start <= idx", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 201, __func__));
  for (size_t sz = start; sz <= idx; sz += 1)
  {
    pages_free[sz] = &page[page_idx];
  }

}


----------------------------
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t block_size;
} mi_page_queue_t
----------------------------
None
----------------------------
***/


inline static bool mi_page_queue_is_special(const mi_page_queue_t *pq)
{
  return pq->block_size > ((1UL << (3 + (13 + 3))) / 8);
}


/*** DEPENDENCIES:
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t block_size;
} mi_page_queue_t
----------------------------
***/


void _mi_page_retire(mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 463, __func__));
  ;
  (mi_page_all_free(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_all_free(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 465, __func__));
  mi_page_set_has_aligned(page, 0);
  mi_page_queue_t *pq = mi_page_queue_of(page);
  const size_t bsize = mi_page_block_size(page);
  if (__builtin_expect(!(!(!mi_page_queue_is_special(pq))), 1))
  {
    if ((pq->last == page) && (pq->first == page))
    {
      _mi_stat_counter_increase(&_mi_stats_main.pages_retire, 1);
      page->retire_expire = (bsize <= ((1UL << (13 + 3)) / 8)) ? (16) : (16 / 4);
      mi_heap_t *heap = mi_page_heap(page);
      (pq >= heap->pages) ? ((void) 0) : (_mi_assert_fail("pq >= heap->pages", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 483, __func__));
      const size_t index = pq - heap->pages;
      ((index < (73U + 1)) && (index < 73U)) ? ((void) 0) : (_mi_assert_fail("index < MI_BIN_FULL && index < MI_BIN_HUGE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 485, __func__));
      if (index < heap->page_retired_min)
      {
        heap->page_retired_min = index;
      }
      if (index > heap->page_retired_max)
      {
        heap->page_retired_max = index;
      }
      (mi_page_all_free(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_all_free(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 488, __func__));
      return;
    }
  }
  _mi_page_free(page, pq, 0);
}


/*** DEPENDENCIES:
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 591, __func__));
  return page->block_size;
}


----------------------------
None
----------------------------
inline static bool mi_page_queue_is_special(const mi_page_queue_t *pq)
{
  return pq->block_size > ((1UL << (3 + (13 + 3))) / 8);
}


----------------------------
inline static mi_heap_t *mi_page_heap(const mi_page_t *page)
{
  return (mi_heap_t *) atomic_load_explicit(&((mi_page_t *) page)->xheap, memory_order_relaxed);
}


----------------------------
void _mi_page_free(mi_page_t *page, mi_page_queue_t *pq, bool force)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 433, __func__));
  ;
  (pq == mi_page_queue_of(page)) ? ((void) 0) : (_mi_assert_fail("pq == mi_page_queue_of(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 435, __func__));
  (mi_page_all_free(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_all_free(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 436, __func__));
  (mi_page_thread_free_flag(page) != MI_DELAYED_FREEING) ? ((void) 0) : (_mi_assert_fail("mi_page_thread_free_flag(page)!=MI_DELAYED_FREEING", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 437, __func__));
  mi_page_set_has_aligned(page, 0);
  mi_heap_t *heap = mi_page_heap(page);
  mi_segments_tld_t *segments_tld = &heap->tld->segments;
  mi_page_queue_remove(pq, page);
  mi_page_set_heap(page, 0);
  _mi_segment_page_free(page, force, segments_tld);
}


----------------------------
inline static bool mi_page_all_free(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 656, __func__));
  return page->used == 0;
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
extern mi_stats_t _mi_stats_main
----------------------------
static mi_page_queue_t *mi_page_queue_of(const mi_page_t *page)
{
  mi_heap_t *heap = mi_page_heap(page);
  mi_page_queue_t *pq = mi_heap_page_queue_of(heap, page);
  ;
  return pq;
}


----------------------------
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t block_size;
} mi_page_queue_t
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


void helper_mi_page_queue_enqueue_from_ex_1(mi_page_queue_t * const to, mi_page_t * const page, mi_heap_t * const heap)
{
  if (to->first != 0)
  {
    (heap == mi_page_heap(to->first)) ? ((void) 0) : (_mi_assert_fail("heap == mi_page_heap(to->first)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 319, __func__));
    mi_page_t *next = to->first->next;
    page->prev = to->first;
    page->next = next;
    to->first->next = page;
    if (next != 0)
    {
      next->prev = page;
    }
    else
    {
      to->last = page;
    }
  }
  else
  {
    page->prev = 0;
    page->next = 0;
    to->first = page;
    to->last = page;
    mi_heap_queue_first_update(heap, to);
  }
}


/*** DEPENDENCIES:
None
----------------------------
inline static mi_heap_t *mi_page_heap(const mi_page_t *page)
{
  return (mi_heap_t *) atomic_load_explicit(&((mi_page_t *) page)->xheap, memory_order_relaxed);
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
inline static void mi_heap_queue_first_update(mi_heap_t *heap, const mi_page_queue_t *pq)
{
  (mi_heap_contains_queue(heap, pq)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap,pq)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 171, __func__));
  size_t size = pq->block_size;
  if (size > (128 * (sizeof(void *))))
  {
    return;
  }
  mi_page_t *page = pq->first;
  unsigned int page_idx = 0;
  if (pq->first == 0)
  {
    page_idx = (mi_page_t *) (&_mi_page_empty);
  }
  size_t start;
  size_t idx = _mi_wsize_from_size(size);
  mi_page_t **pages_free = heap->pages_free_direct;
  if (pages_free[idx] == (&page[page_idx]))
  {
    return;
  }
  if (idx <= 1)
  {
    start = 0;
  }
  else
  {
    size_t bin = mi_bin(size);
    const mi_page_queue_t *prev = pq - 1;
    unsigned int prev_idx = 0;
    while ((bin == mi_bin(prev->block_size)) && ((&prev[prev_idx]) > (&heap->pages[0])))
    {
      prev_idx -= 1;
    }

    start = 1 + _mi_wsize_from_size(prev->block_size);
    if (start > idx)
    {
      start = idx;
    }
  }
  (start <= idx) ? ((void) 0) : (_mi_assert_fail("start <= idx", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 201, __func__));
  for (size_t sz = start; sz <= idx; sz += 1)
  {
    pages_free[sz] = &page[page_idx];
  }

}


----------------------------
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t block_size;
} mi_page_queue_t
----------------------------
None
----------------------------
***/


static void mi_page_queue_enqueue_from_ex(mi_page_queue_t *to, mi_page_queue_t *from, bool enqueue_at_end, mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 276, __func__));
  ;
  ;
  const size_t bsize = mi_page_block_size(page);
  (void) bsize;
  ((((((bsize == to->block_size) && (bsize == from->block_size)) || ((bsize == to->block_size) && mi_page_queue_is_full(from))) || ((bsize == from->block_size) && mi_page_queue_is_full(to))) || (mi_page_is_large_or_huge(page) && mi_page_queue_is_huge(to))) || (mi_page_is_large_or_huge(page) && mi_page_queue_is_full(to))) ? ((void) 0) : (_mi_assert_fail("(bsize == to->block_size && bsize == from->block_size) || (bsize == to->block_size && mi_page_queue_is_full(from)) || (bsize == from->block_size && mi_page_queue_is_full(to)) || (mi_page_is_large_or_huge(page) && mi_page_queue_is_huge(to)) || (mi_page_is_large_or_huge(page) && mi_page_queue_is_full(to))", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 281, __func__));
  mi_heap_t *heap = mi_page_heap(page);
  if (page->prev != 0)
  {
    page->prev->next = page->next;
  }
  if (page->next != 0)
  {
    page->next->prev = page->prev;
  }
  if (page == from->last)
  {
    from->last = page->prev;
  }
  if (page == from->first)
  {
    from->first = page->next;
    (mi_heap_contains_queue(heap, from)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap, from)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 296, __func__));
    mi_heap_queue_first_update(heap, from);
  }
  if (enqueue_at_end)
  {
    page->prev = to->last;
    page->next = 0;
    if (to->last != 0)
    {
      (heap == mi_page_heap(to->last)) ? ((void) 0) : (_mi_assert_fail("heap == mi_page_heap(to->last)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 306, __func__));
      to->last->next = page;
      to->last = page;
    }
    else
    {
      to->first = page;
      to->last = page;
      mi_heap_queue_first_update(heap, to);
    }
  }
  else
  {
    helper_mi_page_queue_enqueue_from_ex_1(to, page, heap);
  }
  mi_page_set_in_full(page, mi_page_queue_is_full(to));
}


/*** DEPENDENCIES:
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 591, __func__));
  return page->block_size;
}


----------------------------
inline static bool mi_page_queue_is_huge(const mi_page_queue_t *pq)
{
  return pq->block_size == (((1UL << (3 + (13 + 3))) / 8) + (sizeof(uintptr_t)));
}


----------------------------
static bool mi_heap_contains_queue(const mi_heap_t *heap, const mi_page_queue_t *pq)
{
  return (pq >= (&heap->pages[0])) && (pq <= (&heap->pages[73U + 1]));
}


----------------------------
None
----------------------------
inline static mi_heap_t *mi_page_heap(const mi_page_t *page)
{
  return (mi_heap_t *) atomic_load_explicit(&((mi_page_t *) page)->xheap, memory_order_relaxed);
}


----------------------------
void helper_mi_page_queue_enqueue_from_ex_1(mi_page_queue_t * const to, mi_page_t * const page, mi_heap_t * const heap)
{
  if (to->first != 0)
  {
    (heap == mi_page_heap(to->first)) ? ((void) 0) : (_mi_assert_fail("heap == mi_page_heap(to->first)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 319, __func__));
    mi_page_t *next = to->first->next;
    page->prev = to->first;
    page->next = next;
    to->first->next = page;
    if (next != 0)
    {
      next->prev = page;
    }
    else
    {
      to->last = page;
    }
  }
  else
  {
    page->prev = 0;
    page->next = 0;
    to->first = page;
    to->last = page;
    mi_heap_queue_first_update(heap, to);
  }
}


----------------------------
inline static void mi_page_set_in_full(mi_page_t *page, bool in_full)
{
  page->flags.x.in_full = in_full;
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
inline static void mi_heap_queue_first_update(mi_heap_t *heap, const mi_page_queue_t *pq)
{
  (mi_heap_contains_queue(heap, pq)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap,pq)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 171, __func__));
  size_t size = pq->block_size;
  if (size > (128 * (sizeof(void *))))
  {
    return;
  }
  mi_page_t *page = pq->first;
  unsigned int page_idx = 0;
  if (pq->first == 0)
  {
    page_idx = (mi_page_t *) (&_mi_page_empty);
  }
  size_t start;
  size_t idx = _mi_wsize_from_size(size);
  mi_page_t **pages_free = heap->pages_free_direct;
  if (pages_free[idx] == (&page[page_idx]))
  {
    return;
  }
  if (idx <= 1)
  {
    start = 0;
  }
  else
  {
    size_t bin = mi_bin(size);
    const mi_page_queue_t *prev = pq - 1;
    unsigned int prev_idx = 0;
    while ((bin == mi_bin(prev->block_size)) && ((&prev[prev_idx]) > (&heap->pages[0])))
    {
      prev_idx -= 1;
    }

    start = 1 + _mi_wsize_from_size(prev->block_size);
    if (start > idx)
    {
      start = idx;
    }
  }
  (start <= idx) ? ((void) 0) : (_mi_assert_fail("start <= idx", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 201, __func__));
  for (size_t sz = start; sz <= idx; sz += 1)
  {
    pages_free[sz] = &page[page_idx];
  }

}


----------------------------
inline static bool mi_page_is_large_or_huge(const mi_page_t *page)
{
  return (mi_page_block_size(page) > ((1UL << (3 + (13 + 3))) / 8)) || mi_page_is_huge(page);
}


----------------------------
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t block_size;
} mi_page_queue_t
----------------------------
inline static bool mi_page_queue_is_full(const mi_page_queue_t *pq)
{
  return pq->block_size == (((1UL << (3 + (13 + 3))) / 8) + (2 * (sizeof(uintptr_t))));
}


----------------------------
None
----------------------------
***/


static void mi_page_queue_enqueue_from_full(mi_page_queue_t *to, mi_page_queue_t *from, mi_page_t *page)
{
  mi_page_queue_enqueue_from_ex(to, from, 1, page);
}


/*** DEPENDENCIES:
static void mi_page_queue_enqueue_from_ex(mi_page_queue_t *to, mi_page_queue_t *from, bool enqueue_at_end, mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 276, __func__));
  ;
  ;
  const size_t bsize = mi_page_block_size(page);
  (void) bsize;
  ((((((bsize == to->block_size) && (bsize == from->block_size)) || ((bsize == to->block_size) && mi_page_queue_is_full(from))) || ((bsize == from->block_size) && mi_page_queue_is_full(to))) || (mi_page_is_large_or_huge(page) && mi_page_queue_is_huge(to))) || (mi_page_is_large_or_huge(page) && mi_page_queue_is_full(to))) ? ((void) 0) : (_mi_assert_fail("(bsize == to->block_size && bsize == from->block_size) || (bsize == to->block_size && mi_page_queue_is_full(from)) || (bsize == from->block_size && mi_page_queue_is_full(to)) || (mi_page_is_large_or_huge(page) && mi_page_queue_is_huge(to)) || (mi_page_is_large_or_huge(page) && mi_page_queue_is_full(to))", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 281, __func__));
  mi_heap_t *heap = mi_page_heap(page);
  if (page->prev != 0)
  {
    page->prev->next = page->next;
  }
  if (page->next != 0)
  {
    page->next->prev = page->prev;
  }
  if (page == from->last)
  {
    from->last = page->prev;
  }
  if (page == from->first)
  {
    from->first = page->next;
    (mi_heap_contains_queue(heap, from)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap, from)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 296, __func__));
    mi_heap_queue_first_update(heap, from);
  }
  if (enqueue_at_end)
  {
    page->prev = to->last;
    page->next = 0;
    if (to->last != 0)
    {
      (heap == mi_page_heap(to->last)) ? ((void) 0) : (_mi_assert_fail("heap == mi_page_heap(to->last)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 306, __func__));
      to->last->next = page;
      to->last = page;
    }
    else
    {
      to->first = page;
      to->last = page;
      mi_heap_queue_first_update(heap, to);
    }
  }
  else
  {
    helper_mi_page_queue_enqueue_from_ex_1(to, page, heap);
  }
  mi_page_set_in_full(page, mi_page_queue_is_full(to));
}


----------------------------
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t block_size;
} mi_page_queue_t
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
***/


void _mi_page_unfull(mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 352, __func__));
  ;
  (mi_page_is_in_full(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_in_full(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 354, __func__));
  if (!mi_page_is_in_full(page))
  {
    return;
  }
  mi_heap_t *heap = mi_page_heap(page);
  mi_page_queue_t *pqfull = &heap->pages[73U + 1];
  mi_page_set_in_full(page, 0);
  mi_page_queue_t *pq = mi_heap_page_queue_of(heap, page);
  mi_page_set_in_full(page, 1);
  mi_page_queue_enqueue_from_full(pq, pqfull, page);
}


/*** DEPENDENCIES:
None
----------------------------
inline static mi_heap_t *mi_page_heap(const mi_page_t *page)
{
  return (mi_heap_t *) atomic_load_explicit(&((mi_page_t *) page)->xheap, memory_order_relaxed);
}


----------------------------
inline static void mi_page_set_in_full(mi_page_t *page, bool in_full)
{
  page->flags.x.in_full = in_full;
}


----------------------------
static void mi_page_queue_enqueue_from_full(mi_page_queue_t *to, mi_page_queue_t *from, mi_page_t *page)
{
  mi_page_queue_enqueue_from_ex(to, from, 1, page);
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
inline static bool mi_page_is_in_full(const mi_page_t *page)
{
  return page->flags.x.in_full;
}


----------------------------
static mi_page_queue_t *mi_heap_page_queue_of(mi_heap_t *heap, const mi_page_t *page)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 149, __func__));
  const size_t bin = _mi_page_bin(page);
  mi_page_queue_t *pq = &heap->pages[bin];
  (((mi_page_block_size(page) == pq->block_size) || (mi_page_is_large_or_huge(page) && mi_page_queue_is_huge(pq))) || (mi_page_is_in_full(page) && mi_page_queue_is_full(pq))) ? ((void) 0) : (_mi_assert_fail("(mi_page_block_size(page) == pq->block_size) || (mi_page_is_large_or_huge(page) && mi_page_queue_is_huge(pq)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(pq))", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 152, __func__));
  return pq;
}


----------------------------
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t block_size;
} mi_page_queue_t
----------------------------
None
----------------------------
***/


void _mi_page_force_abandon(mi_page_t *page)
{
  mi_heap_t *heap = mi_page_heap(page);
  _mi_page_use_delayed_free(page, MI_NEVER_DELAYED_FREE, 0);
  _mi_heap_delayed_free_all(heap);
  if (page->capacity == 0)
  {
    return;
  }
  mi_page_queue_t *pq = mi_heap_page_queue_of(heap, page);
  if (mi_page_all_free(page))
  {
    _mi_page_free(page, pq, 0);
  }
  else
  {
    _mi_page_abandon(page, pq);
  }
}


/*** DEPENDENCIES:
static mi_page_queue_t *mi_heap_page_queue_of(mi_heap_t *heap, const mi_page_t *page)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 149, __func__));
  const size_t bin = _mi_page_bin(page);
  mi_page_queue_t *pq = &heap->pages[bin];
  (((mi_page_block_size(page) == pq->block_size) || (mi_page_is_large_or_huge(page) && mi_page_queue_is_huge(pq))) || (mi_page_is_in_full(page) && mi_page_queue_is_full(pq))) ? ((void) 0) : (_mi_assert_fail("(mi_page_block_size(page) == pq->block_size) || (mi_page_is_large_or_huge(page) && mi_page_queue_is_huge(pq)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(pq))", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 152, __func__));
  return pq;
}


----------------------------
void _mi_page_abandon(mi_page_t *page, mi_page_queue_t *pq)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 381, __func__));
  ;
  (pq == mi_page_queue_of(page)) ? ((void) 0) : (_mi_assert_fail("pq == mi_page_queue_of(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 383, __func__));
  (mi_page_heap(page) != 0) ? ((void) 0) : (_mi_assert_fail("mi_page_heap(page) != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 384, __func__));
  mi_heap_t *pheap = mi_page_heap(page);
  mi_segments_tld_t *segments_tld = &pheap->tld->segments;
  mi_page_queue_remove(pq, page);
  (mi_page_thread_free_flag(page) == MI_NEVER_DELAYED_FREE) ? ((void) 0) : (_mi_assert_fail("mi_page_thread_free_flag(page)==MI_NEVER_DELAYED_FREE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 393, __func__));
  mi_page_set_heap(page, 0);
  for (mi_block_t *block = (mi_block_t *) pheap->thread_delayed_free; (&block[block_idx]) != 0; block_idx = mi_block_nextx(pheap, block_idx, pheap->keys))
  {
    (_mi_ptr_page(block) != page) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(block) != page", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 399, __func__));
  }

  unsigned int block_idx = 0;
  (mi_page_heap(page) == 0) ? ((void) 0) : (_mi_assert_fail("mi_page_heap(page) == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 404, __func__));
  _mi_segment_page_abandon(page, segments_tld);
}


----------------------------
void _mi_page_use_delayed_free(mi_page_t *page, mi_delayed_t delay, bool override_never)
{
  while (!_mi_page_try_use_delayed_free(page, delay, override_never))
  {
    mi_atomic_yield();
  }

}


----------------------------
None
----------------------------
inline static mi_heap_t *mi_page_heap(const mi_page_t *page)
{
  return (mi_heap_t *) atomic_load_explicit(&((mi_page_t *) page)->xheap, memory_order_relaxed);
}


----------------------------
inline static bool mi_page_all_free(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 656, __func__));
  return page->used == 0;
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
void _mi_page_free(mi_page_t *page, mi_page_queue_t *pq, bool force)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 433, __func__));
  ;
  (pq == mi_page_queue_of(page)) ? ((void) 0) : (_mi_assert_fail("pq == mi_page_queue_of(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 435, __func__));
  (mi_page_all_free(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_all_free(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 436, __func__));
  (mi_page_thread_free_flag(page) != MI_DELAYED_FREEING) ? ((void) 0) : (_mi_assert_fail("mi_page_thread_free_flag(page)!=MI_DELAYED_FREEING", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 437, __func__));
  mi_page_set_has_aligned(page, 0);
  mi_heap_t *heap = mi_page_heap(page);
  mi_segments_tld_t *segments_tld = &heap->tld->segments;
  mi_page_queue_remove(pq, page);
  mi_page_set_heap(page, 0);
  _mi_segment_page_free(page, force, segments_tld);
}


----------------------------
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t block_size;
} mi_page_queue_t
----------------------------
None
----------------------------
***/


static mi_page_t *mi_page_fresh_alloc(mi_heap_t *heap, mi_page_queue_t *pq, size_t block_size, size_t page_alignment)
{
  (pq != 0) ? ((void) 0) : (_mi_assert_fail("pq != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 275, __func__));
  (mi_heap_contains_queue(heap, pq)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap, pq)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 276, __func__));
  (((page_alignment > 0) || (block_size > ((1UL << (3 + (13 + 3))) / 8))) || (block_size == pq->block_size)) ? ((void) 0) : (_mi_assert_fail("page_alignment > 0 || block_size > MI_MEDIUM_OBJ_SIZE_MAX || block_size == pq->block_size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 277, __func__));
  mi_page_t *page = _mi_segment_page_alloc(heap, block_size, page_alignment, &heap->tld->segments);
  if (page == 0)
  {
    return 0;
  }
  (((page_alignment > 0) || (block_size > ((1UL << (3 + (13 + 3))) / 8))) || (_mi_page_segment(page)->kind != MI_SEGMENT_HUGE)) ? ((void) 0) : (_mi_assert_fail("page_alignment >0 || block_size > MI_MEDIUM_OBJ_SIZE_MAX || _mi_page_segment(page)->kind != MI_SEGMENT_HUGE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 287, __func__));
  ((pq != 0) || (mi_page_block_size(page) >= block_size)) ? ((void) 0) : (_mi_assert_fail("pq!=NULL || mi_page_block_size(page) >= block_size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 288, __func__));
  const size_t full_block_size = ((pq == 0) || mi_page_is_huge(page)) ? (mi_page_block_size(page)) : (block_size);
  (full_block_size >= block_size) ? ((void) 0) : (_mi_assert_fail("full_block_size >= block_size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 291, __func__));
  mi_page_init(heap, page, full_block_size, heap->tld);
  _mi_stat_increase(&heap->tld->stats.pages, 1);
  _mi_stat_increase(&heap->tld->stats.page_bins[_mi_page_bin(page)], 1);
  if (pq != 0)
  {
    mi_page_queue_push(heap, pq, page);
  }
  ;
  return page;
}


/*** DEPENDENCIES:
inline static mi_segment_t *_mi_page_segment(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 548, __func__));
  mi_segment_t *segment = _mi_ptr_segment(page);
  ((segment == 0) || ((((mi_slice_t *) page) >= segment->slices) && (((mi_slice_t *) page) < (segment->slices + segment->slice_entries)))) ? ((void) 0) : (_mi_assert_fail("segment == NULL || ((mi_slice_t*)page >= segment->slices && (mi_slice_t*)page < segment->slices + segment->slice_entries)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 550, __func__));
  return segment;
}


----------------------------
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 591, __func__));
  return page->block_size;
}


----------------------------
static void mi_page_queue_push(mi_heap_t *heap, mi_page_queue_t *queue, mi_page_t *page)
{
  (mi_page_heap(page) == heap) ? ((void) 0) : (_mi_assert_fail("mi_page_heap(page) == heap", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 239, __func__));
  (!mi_page_queue_contains(queue, page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_queue_contains(queue, page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 240, __func__));
  (((mi_page_block_size(page) == queue->block_size) || (mi_page_is_large_or_huge(page) && mi_page_queue_is_huge(queue))) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) == queue->block_size || (mi_page_is_large_or_huge(page) && mi_page_queue_is_huge(queue)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 244, __func__));
  mi_page_set_in_full(page, mi_page_queue_is_full(queue));
  page->next = queue->first;
  page->prev = 0;
  if (queue->first != 0)
  {
    (queue->first->prev == 0) ? ((void) 0) : (_mi_assert_fail("queue->first->prev == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 253, __func__));
    queue->first->prev = page;
    queue->first = page;
  }
  else
  {
    queue->first = (queue->last = page);
  }
  mi_heap_queue_first_update(heap, queue);
  heap->page_count += 1;
}


----------------------------
size_t _mi_page_bin(const mi_page_t *page)
{
  const size_t bin = (mi_page_is_in_full(page)) ? (73U + 1) : ((mi_page_is_huge(page)) ? (73U) : (mi_bin(mi_page_block_size(page))));
  (bin <= (73U + 1)) ? ((void) 0) : (_mi_assert_fail("bin <= MI_BIN_FULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 144, __func__));
  return bin;
}


----------------------------
static bool mi_heap_contains_queue(const mi_heap_t *heap, const mi_page_queue_t *pq)
{
  return (pq >= (&heap->pages[0])) && (pq <= (&heap->pages[73U + 1]));
}


----------------------------
None
----------------------------
void _mi_stat_increase(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_update(stat, (int64_t) amount);
}


----------------------------
mi_page_t *_mi_segment_page_alloc(mi_heap_t *heap, size_t block_size, size_t page_alignment, mi_segments_tld_t *tld)
{
  mi_page_t *page;
  unsigned int page_idx = 0;
  if (__builtin_expect(!(!(page_alignment > ((1UL << (9 + (13 + 3))) >> 1))), 0))
  {
    (_mi_is_power_of_two(page_alignment)) ? ((void) 0) : (_mi_assert_fail("_mi_is_power_of_two(page_alignment)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c", 1649, __func__));
    (page_alignment >= (1UL << (9 + (13 + 3)))) ? ((void) 0) : (_mi_assert_fail("page_alignment >= MI_SEGMENT_SIZE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c", 1650, __func__));
    if (page_alignment < (1UL << (9 + (13 + 3))))
    {
      page_alignment = 1UL << (9 + (13 + 3));
    }
    page_idx = mi_segment_huge_page_alloc(block_size, page_alignment, heap->arena_id, tld);
  }
  else
    if (block_size <= ((1UL << (13 + 3)) / 8))
  {
    page_idx = mi_segments_page_alloc(heap, MI_PAGE_SMALL, block_size, block_size, tld);
  }
  else
    if (block_size <= ((1UL << (3 + (13 + 3))) / 8))
  {
    page_idx = mi_segments_page_alloc(heap, MI_PAGE_MEDIUM, 1UL << (3 + (13 + 3)), block_size, tld);
  }
  else
    if (block_size <= ((1UL << (9 + (13 + 3))) / 2))
  {
    page_idx = mi_segments_page_alloc(heap, MI_PAGE_LARGE, block_size, block_size, tld);
  }
  else
  {
    page_idx = mi_segment_huge_page_alloc(block_size, page_alignment, heap->arena_id, tld);
  }
  (((&page[page_idx]) == 0) || _mi_heap_memid_is_suitable(heap, _mi_page_segment(page)->memid)) ? ((void) 0) : (_mi_assert_fail("page == NULL || _mi_heap_memid_is_suitable(heap, _mi_page_segment(page)->memid)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c", 1666, __func__));
  ;
  (((&page[page_idx]) == 0) || (_mi_page_segment(page)->subproc == tld->subproc)) ? ((void) 0) : (_mi_assert_fail("page == NULL || _mi_page_segment(page)->subproc == tld->subproc", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c", 1668, __func__));
  return page;
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
inline static bool mi_page_is_huge(const mi_page_t *page)
{
  ((page->is_huge && (_mi_page_segment(page)->kind == MI_SEGMENT_HUGE)) || ((!page->is_huge) && (_mi_page_segment(page)->kind != MI_SEGMENT_HUGE))) ? ((void) 0) : (_mi_assert_fail("(page->is_huge && _mi_page_segment(page)->kind == MI_SEGMENT_HUGE) || (!page->is_huge && _mi_page_segment(page)->kind != MI_SEGMENT_HUGE)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 596, __func__));
  return page->is_huge;
}


----------------------------
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t block_size;
} mi_page_queue_t
----------------------------
static void mi_page_init(mi_heap_t *heap, mi_page_t *page, size_t block_size, mi_tld_t *tld)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 680, __func__));
  mi_segment_t *segment = _mi_page_segment(page);
  (segment != 0) ? ((void) 0) : (_mi_assert_fail("segment != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 682, __func__));
  (block_size > 0) ? ((void) 0) : (_mi_assert_fail("block_size > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 683, __func__));
  mi_page_set_heap(page, heap);
  page->block_size = block_size;
  size_t page_size;
  page->page_start = _mi_segment_page_start(segment, page, &page_size);
  ;
  (mi_page_block_size(page) <= page_size) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) <= page_size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 690, __func__));
  (page_size <= (page->slice_count * (1UL << (13 + 3)))) ? ((void) 0) : (_mi_assert_fail("page_size <= page->slice_count*MI_SEGMENT_SLICE_SIZE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 691, __func__));
  ((page_size / block_size) < (1L << 16)) ? ((void) 0) : (_mi_assert_fail("page_size / block_size < (1L<<16)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 692, __func__));
  page->reserved = (uint16_t) (page_size / block_size);
  (page->reserved > 0) ? ((void) 0) : (_mi_assert_fail("page->reserved > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 694, __func__));
  page->keys[0] = _mi_heap_random_next(heap);
  page->keys[1] = _mi_heap_random_next(heap);
  page->free_is_zero = page->is_zero_init;
  (page->is_committed) ? ((void) 0) : (_mi_assert_fail("page->is_committed", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 706, __func__));
  if ((block_size > 0) && _mi_is_power_of_two(block_size))
  {
    page->block_size_shift = (uint8_t) mi_ctz((uintptr_t) block_size);
  }
  else
  {
    page->block_size_shift = 0;
  }
  (page->capacity == 0) ? ((void) 0) : (_mi_assert_fail("page->capacity == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 714, __func__));
  (page->free == 0) ? ((void) 0) : (_mi_assert_fail("page->free == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 715, __func__));
  (page->used == 0) ? ((void) 0) : (_mi_assert_fail("page->used == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 716, __func__));
  (page->xthread_free == 0) ? ((void) 0) : (_mi_assert_fail("page->xthread_free == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 717, __func__));
  (page->next == 0) ? ((void) 0) : (_mi_assert_fail("page->next == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 718, __func__));
  (page->prev == 0) ? ((void) 0) : (_mi_assert_fail("page->prev == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 719, __func__));
  (page->retire_expire == 0) ? ((void) 0) : (_mi_assert_fail("page->retire_expire == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 720, __func__));
  (!mi_page_has_aligned(page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_has_aligned(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 721, __func__));
  (page->keys[0] != 0) ? ((void) 0) : (_mi_assert_fail("page->keys[0] != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 723, __func__));
  (page->keys[1] != 0) ? ((void) 0) : (_mi_assert_fail("page->keys[1] != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 724, __func__));
  ((page->block_size_shift == 0) || (block_size == (((size_t) 1) << page->block_size_shift))) ? ((void) 0) : (_mi_assert_fail("page->block_size_shift == 0 || (block_size == ((size_t)1 << page->block_size_shift))", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 726, __func__));
  ;
  if (mi_page_extend_free(heap, page, tld))
  {
    (mi_page_immediate_available(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_immediate_available(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 731, __func__));
  }
  return;
}


----------------------------
None
----------------------------
***/


static mi_page_t *mi_large_huge_page_alloc(mi_heap_t *heap, size_t size, size_t page_alignment)
{
  size_t block_size = _mi_os_good_alloc_size(size);
  ((mi_bin(block_size) == 73U) || (page_alignment > 0)) ? ((void) 0) : (_mi_assert_fail("mi_bin(block_size) == MI_BIN_HUGE || page_alignment > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 920, __func__));
  bool is_huge = (block_size > ((1UL << (9 + (13 + 3))) / 2)) || (page_alignment > 0);
  mi_page_queue_t *pq = mi_page_queue(heap, (is_huge) ? (((1UL << (9 + (13 + 3))) / 2) + 1) : (block_size));
  ((!is_huge) || mi_page_queue_is_huge(pq)) ? ((void) 0) : (_mi_assert_fail("!is_huge || mi_page_queue_is_huge(pq)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 926, __func__));
  mi_page_t *page = mi_page_fresh_alloc(heap, pq, block_size, page_alignment);
  if (page != 0)
  {
    (mi_page_immediate_available(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_immediate_available(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 930, __func__));
    if (is_huge)
    {
      (mi_page_is_huge(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_huge(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 933, __func__));
      (_mi_page_segment(page)->kind == MI_SEGMENT_HUGE) ? ((void) 0) : (_mi_assert_fail("_mi_page_segment(page)->kind == MI_SEGMENT_HUGE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 934, __func__));
      (_mi_page_segment(page)->used == 1) ? ((void) 0) : (_mi_assert_fail("_mi_page_segment(page)->used==1", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 935, __func__));
    }
    else
    {
      (!mi_page_is_huge(page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_is_huge(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 942, __func__));
    }
    const size_t bsize = mi_page_usable_block_size(page);
    {
      _mi_stat_increase(&heap->tld->stats.malloc_huge, bsize);
      _mi_stat_counter_increase(&heap->tld->stats.malloc_huge_count, 1);
    }
  }
  return page;
}


/*** DEPENDENCIES:
static mi_page_t *mi_page_fresh_alloc(mi_heap_t *heap, mi_page_queue_t *pq, size_t block_size, size_t page_alignment)
{
  (pq != 0) ? ((void) 0) : (_mi_assert_fail("pq != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 275, __func__));
  (mi_heap_contains_queue(heap, pq)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap, pq)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 276, __func__));
  (((page_alignment > 0) || (block_size > ((1UL << (3 + (13 + 3))) / 8))) || (block_size == pq->block_size)) ? ((void) 0) : (_mi_assert_fail("page_alignment > 0 || block_size > MI_MEDIUM_OBJ_SIZE_MAX || block_size == pq->block_size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 277, __func__));
  mi_page_t *page = _mi_segment_page_alloc(heap, block_size, page_alignment, &heap->tld->segments);
  if (page == 0)
  {
    return 0;
  }
  (((page_alignment > 0) || (block_size > ((1UL << (3 + (13 + 3))) / 8))) || (_mi_page_segment(page)->kind != MI_SEGMENT_HUGE)) ? ((void) 0) : (_mi_assert_fail("page_alignment >0 || block_size > MI_MEDIUM_OBJ_SIZE_MAX || _mi_page_segment(page)->kind != MI_SEGMENT_HUGE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 287, __func__));
  ((pq != 0) || (mi_page_block_size(page) >= block_size)) ? ((void) 0) : (_mi_assert_fail("pq!=NULL || mi_page_block_size(page) >= block_size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 288, __func__));
  const size_t full_block_size = ((pq == 0) || mi_page_is_huge(page)) ? (mi_page_block_size(page)) : (block_size);
  (full_block_size >= block_size) ? ((void) 0) : (_mi_assert_fail("full_block_size >= block_size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 291, __func__));
  mi_page_init(heap, page, full_block_size, heap->tld);
  _mi_stat_increase(&heap->tld->stats.pages, 1);
  _mi_stat_increase(&heap->tld->stats.page_bins[_mi_page_bin(page)], 1);
  if (pq != 0)
  {
    mi_page_queue_push(heap, pq, page);
  }
  ;
  return page;
}


----------------------------
size_t _mi_os_good_alloc_size(size_t size)
{
  size_t align_size;
  if (size < (512 * 1024UL))
  {
    align_size = _mi_os_page_size();
  }
  else
    if (size < (2 * (1024UL * 1024UL)))
  {
    align_size = 64 * 1024UL;
  }
  else
    if (size < (8 * (1024UL * 1024UL)))
  {
    align_size = 256 * 1024UL;
  }
  else
    if (size < (32 * (1024UL * 1024UL)))
  {
    align_size = 1 * (1024UL * 1024UL);
  }
  else
    align_size = 4 * (1024UL * 1024UL);
  if (__builtin_expect(!(!(size >= (SIZE_MAX - align_size))), 0))
  {
    return size;
  }
  return _mi_align_up(size, align_size);
}


----------------------------
inline static mi_segment_t *_mi_page_segment(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 548, __func__));
  mi_segment_t *segment = _mi_ptr_segment(page);
  ((segment == 0) || ((((mi_slice_t *) page) >= segment->slices) && (((mi_slice_t *) page) < (segment->slices + segment->slice_entries)))) ? ((void) 0) : (_mi_assert_fail("segment == NULL || ((mi_slice_t*)page >= segment->slices && (mi_slice_t*)page < segment->slices + segment->slice_entries)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 550, __func__));
  return segment;
}


----------------------------
inline static bool mi_page_queue_is_huge(const mi_page_queue_t *pq)
{
  return pq->block_size == (((1UL << (3 + (13 + 3))) / 8) + (sizeof(uintptr_t)));
}


----------------------------
None
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
void _mi_stat_increase(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_update(stat, (int64_t) amount);
}


----------------------------
inline static size_t mi_page_usable_block_size(const mi_page_t *page)
{
  return mi_page_block_size(page) - (sizeof(mi_padding_t));
}


----------------------------
inline static bool mi_page_immediate_available(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 668, __func__));
  return page->free != 0;
}


----------------------------
inline static mi_page_queue_t *mi_page_queue(const mi_heap_t *heap, size_t size)
{
  return &((mi_heap_t *) heap)->pages[_mi_bin(size)];
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
inline static bool mi_page_is_huge(const mi_page_t *page)
{
  ((page->is_huge && (_mi_page_segment(page)->kind == MI_SEGMENT_HUGE)) || ((!page->is_huge) && (_mi_page_segment(page)->kind != MI_SEGMENT_HUGE))) ? ((void) 0) : (_mi_assert_fail("(page->is_huge && _mi_page_segment(page)->kind == MI_SEGMENT_HUGE) || (!page->is_huge && _mi_page_segment(page)->kind != MI_SEGMENT_HUGE)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 596, __func__));
  return page->is_huge;
}


----------------------------
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t block_size;
} mi_page_queue_t
----------------------------
inline static size_t mi_bin(size_t size)
{
  size_t wsize = _mi_wsize_from_size(size);
  if (__builtin_expect(!(!(wsize <= 8)), 1))
  {
    return (wsize <= 1) ? (1) : ((wsize + 1) & (~1));
  }
  else
    if (__builtin_expect(!(!(wsize > (((1UL << (3 + (13 + 3))) / 8) / (1 << 3)))), 0))
  {
    return 73U;
  }
  else
  {
    wsize -= 1;
    const size_t b = (((1 << 3) * 8) - 1) - mi_clz(wsize);
    const size_t bin = ((b << 2) + ((wsize >> (b - 2)) & 0x03)) - 3;
    ((bin > 0) && (bin < 73U)) ? ((void) 0) : (_mi_assert_fail("bin > 0 && bin < MI_BIN_HUGE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 88, __func__));
    return bin;
  }
}


----------------------------
None
----------------------------
***/


static void mi_page_queue_move_to_front(mi_heap_t *heap, mi_page_queue_t *queue, mi_page_t *page)
{
  (mi_page_heap(page) == heap) ? ((void) 0) : (_mi_assert_fail("mi_page_heap(page) == heap", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 267, __func__));
  (mi_page_queue_contains(queue, page)) ? ((void) 0) : (_mi_assert_fail("mi_page_queue_contains(queue, page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 268, __func__));
  if (queue->first == page)
  {
    return;
  }
  mi_page_queue_remove(queue, page);
  mi_page_queue_push(heap, queue, page);
  (queue->first == page) ? ((void) 0) : (_mi_assert_fail("queue->first == page", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 272, __func__));
}


/*** DEPENDENCIES:
static void mi_page_queue_push(mi_heap_t *heap, mi_page_queue_t *queue, mi_page_t *page)
{
  (mi_page_heap(page) == heap) ? ((void) 0) : (_mi_assert_fail("mi_page_heap(page) == heap", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 239, __func__));
  (!mi_page_queue_contains(queue, page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_queue_contains(queue, page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 240, __func__));
  (((mi_page_block_size(page) == queue->block_size) || (mi_page_is_large_or_huge(page) && mi_page_queue_is_huge(queue))) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) == queue->block_size || (mi_page_is_large_or_huge(page) && mi_page_queue_is_huge(queue)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 244, __func__));
  mi_page_set_in_full(page, mi_page_queue_is_full(queue));
  page->next = queue->first;
  page->prev = 0;
  if (queue->first != 0)
  {
    (queue->first->prev == 0) ? ((void) 0) : (_mi_assert_fail("queue->first->prev == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 253, __func__));
    queue->first->prev = page;
    queue->first = page;
  }
  else
  {
    queue->first = (queue->last = page);
  }
  mi_heap_queue_first_update(heap, queue);
  heap->page_count += 1;
}


----------------------------
None
----------------------------
inline static mi_heap_t *mi_page_heap(const mi_page_t *page)
{
  return (mi_heap_t *) atomic_load_explicit(&((mi_page_t *) page)->xheap, memory_order_relaxed);
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
static void mi_page_queue_remove(mi_page_queue_t *queue, mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 214, __func__));
  ;
  (((mi_page_block_size(page) == queue->block_size) || (mi_page_is_large_or_huge(page) && mi_page_queue_is_huge(queue))) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) == queue->block_size || (mi_page_is_large_or_huge(page) && mi_page_queue_is_huge(queue)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 216, __func__));
  mi_heap_t *heap = mi_page_heap(page);
  if (page->prev != 0)
  {
    page->prev->next = page->next;
  }
  if (page->next != 0)
  {
    page->next->prev = page->prev;
  }
  if (page == queue->last)
  {
    queue->last = page->prev;
  }
  if (page == queue->first)
  {
    queue->first = page->next;
    (mi_heap_contains_queue(heap, queue)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap, queue)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 227, __func__));
    mi_heap_queue_first_update(heap, queue);
  }
  heap->page_count -= 1;
  page->next = 0;
  page->prev = 0;
  mi_page_set_in_full(page, 0);
}


----------------------------
static bool mi_page_queue_contains(mi_page_queue_t *queue, const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 119, __func__));
  mi_page_t *list = queue->first;
  unsigned int list_idx = 0;
  while ((&list[list_idx]) != 0)
  {
    ((list->next == 0) || (list->next->prev == (&list[list_idx]))) ? ((void) 0) : (_mi_assert_fail("list->next == NULL || list->next->prev == list", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 122, __func__));
    ((list->prev == 0) || (list->prev->next == (&list[list_idx]))) ? ((void) 0) : (_mi_assert_fail("list->prev == NULL || list->prev->next == list", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 123, __func__));
    if ((&list[list_idx]) == page)
    {
      break;
    }
    list_idx = list_idx->next;
  }

  return (&list[list_idx]) == page;
}


----------------------------
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t block_size;
} mi_page_queue_t
----------------------------
None
----------------------------
***/


static mi_page_t *mi_page_fresh(mi_heap_t *heap, mi_page_queue_t *pq)
{
  (mi_heap_contains_queue(heap, pq)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap, pq)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 302, __func__));
  mi_page_t *page = mi_page_fresh_alloc(heap, pq, pq->block_size, 0);
  if (page == 0)
  {
    return 0;
  }
  (pq->block_size == mi_page_block_size(page)) ? ((void) 0) : (_mi_assert_fail("pq->block_size==mi_page_block_size(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 305, __func__));
  (pq == mi_page_queue(heap, mi_page_block_size(page))) ? ((void) 0) : (_mi_assert_fail("pq==mi_page_queue(heap, mi_page_block_size(page))", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 306, __func__));
  return page;
}


/*** DEPENDENCIES:
static mi_page_t *mi_page_fresh_alloc(mi_heap_t *heap, mi_page_queue_t *pq, size_t block_size, size_t page_alignment)
{
  (pq != 0) ? ((void) 0) : (_mi_assert_fail("pq != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 275, __func__));
  (mi_heap_contains_queue(heap, pq)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap, pq)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 276, __func__));
  (((page_alignment > 0) || (block_size > ((1UL << (3 + (13 + 3))) / 8))) || (block_size == pq->block_size)) ? ((void) 0) : (_mi_assert_fail("page_alignment > 0 || block_size > MI_MEDIUM_OBJ_SIZE_MAX || block_size == pq->block_size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 277, __func__));
  mi_page_t *page = _mi_segment_page_alloc(heap, block_size, page_alignment, &heap->tld->segments);
  if (page == 0)
  {
    return 0;
  }
  (((page_alignment > 0) || (block_size > ((1UL << (3 + (13 + 3))) / 8))) || (_mi_page_segment(page)->kind != MI_SEGMENT_HUGE)) ? ((void) 0) : (_mi_assert_fail("page_alignment >0 || block_size > MI_MEDIUM_OBJ_SIZE_MAX || _mi_page_segment(page)->kind != MI_SEGMENT_HUGE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 287, __func__));
  ((pq != 0) || (mi_page_block_size(page) >= block_size)) ? ((void) 0) : (_mi_assert_fail("pq!=NULL || mi_page_block_size(page) >= block_size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 288, __func__));
  const size_t full_block_size = ((pq == 0) || mi_page_is_huge(page)) ? (mi_page_block_size(page)) : (block_size);
  (full_block_size >= block_size) ? ((void) 0) : (_mi_assert_fail("full_block_size >= block_size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 291, __func__));
  mi_page_init(heap, page, full_block_size, heap->tld);
  _mi_stat_increase(&heap->tld->stats.pages, 1);
  _mi_stat_increase(&heap->tld->stats.page_bins[_mi_page_bin(page)], 1);
  if (pq != 0)
  {
    mi_page_queue_push(heap, pq, page);
  }
  ;
  return page;
}


----------------------------
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 591, __func__));
  return page->block_size;
}


----------------------------
static bool mi_heap_contains_queue(const mi_heap_t *heap, const mi_page_queue_t *pq)
{
  return (pq >= (&heap->pages[0])) && (pq <= (&heap->pages[73U + 1]));
}


----------------------------
None
----------------------------
inline static mi_page_queue_t *mi_page_queue(const mi_heap_t *heap, size_t size)
{
  return &((mi_heap_t *) heap)->pages[_mi_bin(size)];
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
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t block_size;
} mi_page_queue_t
----------------------------
None
----------------------------
***/


static bool mi_page_is_expandable(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 746, __func__));
  (page->capacity <= page->reserved) ? ((void) 0) : (_mi_assert_fail("page->capacity <= page->reserved", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 747, __func__));
  return page->capacity < page->reserved;
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
***/


static void mi_page_queue_enqueue_from(mi_page_queue_t *to, mi_page_queue_t *from, mi_page_t *page)
{
  mi_page_queue_enqueue_from_ex(to, from, 1, page);
}


/*** DEPENDENCIES:
static void mi_page_queue_enqueue_from_ex(mi_page_queue_t *to, mi_page_queue_t *from, bool enqueue_at_end, mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 276, __func__));
  ;
  ;
  const size_t bsize = mi_page_block_size(page);
  (void) bsize;
  ((((((bsize == to->block_size) && (bsize == from->block_size)) || ((bsize == to->block_size) && mi_page_queue_is_full(from))) || ((bsize == from->block_size) && mi_page_queue_is_full(to))) || (mi_page_is_large_or_huge(page) && mi_page_queue_is_huge(to))) || (mi_page_is_large_or_huge(page) && mi_page_queue_is_full(to))) ? ((void) 0) : (_mi_assert_fail("(bsize == to->block_size && bsize == from->block_size) || (bsize == to->block_size && mi_page_queue_is_full(from)) || (bsize == from->block_size && mi_page_queue_is_full(to)) || (mi_page_is_large_or_huge(page) && mi_page_queue_is_huge(to)) || (mi_page_is_large_or_huge(page) && mi_page_queue_is_full(to))", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 281, __func__));
  mi_heap_t *heap = mi_page_heap(page);
  if (page->prev != 0)
  {
    page->prev->next = page->next;
  }
  if (page->next != 0)
  {
    page->next->prev = page->prev;
  }
  if (page == from->last)
  {
    from->last = page->prev;
  }
  if (page == from->first)
  {
    from->first = page->next;
    (mi_heap_contains_queue(heap, from)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap, from)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 296, __func__));
    mi_heap_queue_first_update(heap, from);
  }
  if (enqueue_at_end)
  {
    page->prev = to->last;
    page->next = 0;
    if (to->last != 0)
    {
      (heap == mi_page_heap(to->last)) ? ((void) 0) : (_mi_assert_fail("heap == mi_page_heap(to->last)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 306, __func__));
      to->last->next = page;
      to->last = page;
    }
    else
    {
      to->first = page;
      to->last = page;
      mi_heap_queue_first_update(heap, to);
    }
  }
  else
  {
    helper_mi_page_queue_enqueue_from_ex_1(to, page, heap);
  }
  mi_page_set_in_full(page, mi_page_queue_is_full(to));
}


----------------------------
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t block_size;
} mi_page_queue_t
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
***/


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


/*** DEPENDENCIES:
void _mi_page_free_collect(mi_page_t *page, bool force)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 218, __func__));
  if (force || (mi_page_thread_free(page) != 0))
  {
    _mi_page_thread_free_collect(page);
  }
  if (page->local_free != 0)
  {
    if (__builtin_expect(!(!(page->free == 0)), 1))
    {
      page->free = page->local_free;
      page->local_free = 0;
      page->free_is_zero = 0;
    }
    else
      if (force)
    {
      mi_block_t *tail = page->local_free;
      unsigned int tail_idx = 0;
      mi_block_t *next;
      unsigned int next_idx = 0;
      while ((next_idx = mi_block_next(page, tail)) != 0)
      {
        tail_idx = &next[next_idx];
      }

      mi_block_set_next(page, tail, page->free);
      page->free = page->local_free;
      page->local_free = 0;
      page->free_is_zero = 0;
    }
  }
  ((!force) || (page->local_free == 0)) ? ((void) 0) : (_mi_assert_fail("!force || page->local_free == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 247, __func__));
}


----------------------------
inline static mi_heap_t *mi_page_heap(const mi_page_t *page)
{
  return (mi_heap_t *) atomic_load_explicit(&((mi_page_t *) page)->xheap, memory_order_relaxed);
}


----------------------------
inline static bool mi_page_immediate_available(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 668, __func__));
  return page->free != 0;
}


----------------------------
static void mi_page_queue_enqueue_from(mi_page_queue_t *to, mi_page_queue_t *from, mi_page_t *page)
{
  mi_page_queue_enqueue_from_ex(to, from, 1, page);
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
inline static bool mi_page_is_in_full(const mi_page_t *page)
{
  return page->flags.x.in_full;
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
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t block_size;
} mi_page_queue_t
----------------------------
None
----------------------------
***/


// hint:  ['count_ref is a mutable refrence to size_t', 'candidate_count_ref is a mutable refrence to size_t', 'page_candidate_idx_ref is a mutable refrence to unsigned int', 'page_idx_ref is a mutable refrence to unsigned int']
void helper_mi_page_queue_find_free_ex_1(size_t * const count_ref, size_t * const candidate_count_ref, unsigned int * const page_candidate_idx_ref, unsigned int * const page_idx_ref, mi_page_queue_t * const pq, mi_page_t * const page_candidate, mi_page_t * const page)
{
  size_t count = *count_ref;
  size_t candidate_count = *candidate_count_ref;
  unsigned int page_candidate_idx = *page_candidate_idx_ref;
  unsigned int page_idx = *page_idx_ref;
  mi_page_t *next = page->next;
  count += 1;
  candidate_count += 1;
  _mi_page_free_collect(page, 0);
  const bool immediate_available = mi_page_immediate_available(page);
  if ((!immediate_available) && (!mi_page_is_expandable(page)))
  {
    ((!mi_page_is_in_full(page)) && (!mi_page_immediate_available(page))) ? ((void) 0) : (_mi_assert_fail("!mi_page_is_in_full(page) && !mi_page_immediate_available(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 783, __func__));
    mi_page_to_full(page, pq);
  }
  else
  {
    if ((&page_candidate[page_candidate_idx]) == 0)
    {
      page_candidate_idx = &page[page_idx];
      candidate_count = 0;
    }
    else
      if (((page->used >= page_candidate->used) && (!mi_page_is_mostly_used(page))) && (!mi_page_is_expandable(page)))
    {
      page_candidate_idx = &page[page_idx];
    }
    if (immediate_available || (candidate_count > 4))
    {
      ((&page_candidate[page_candidate_idx]) != 0) ? ((void) 0) : (_mi_assert_fail("page_candidate!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 799, __func__));
      break;
    }
  }
  page_idx = next;
  *count_ref = count;
  *candidate_count_ref = candidate_count;
  *page_candidate_idx_ref = page_candidate_idx;
  *page_idx_ref = page_idx;
}


/*** DEPENDENCIES:
void _mi_page_free_collect(mi_page_t *page, bool force)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 218, __func__));
  if (force || (mi_page_thread_free(page) != 0))
  {
    _mi_page_thread_free_collect(page);
  }
  if (page->local_free != 0)
  {
    if (__builtin_expect(!(!(page->free == 0)), 1))
    {
      page->free = page->local_free;
      page->local_free = 0;
      page->free_is_zero = 0;
    }
    else
      if (force)
    {
      mi_block_t *tail = page->local_free;
      unsigned int tail_idx = 0;
      mi_block_t *next;
      unsigned int next_idx = 0;
      while ((next_idx = mi_block_next(page, tail)) != 0)
      {
        tail_idx = &next[next_idx];
      }

      mi_block_set_next(page, tail, page->free);
      page->free = page->local_free;
      page->local_free = 0;
      page->free_is_zero = 0;
    }
  }
  ((!force) || (page->local_free == 0)) ? ((void) 0) : (_mi_assert_fail("!force || page->local_free == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 247, __func__));
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
static bool mi_page_is_expandable(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 746, __func__));
  (page->capacity <= page->reserved) ? ((void) 0) : (_mi_assert_fail("page->capacity <= page->reserved", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 747, __func__));
  return page->capacity < page->reserved;
}


----------------------------
inline static bool mi_page_immediate_available(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 668, __func__));
  return page->free != 0;
}


----------------------------
inline static bool mi_page_is_mostly_used(const mi_page_t *page)
{
  if (page == 0)
  {
    return 1;
  }
  uint16_t frac = page->reserved / 8U;
  return (page->reserved - page->used) <= frac;
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
inline static bool mi_page_is_in_full(const mi_page_t *page)
{
  return page->flags.x.in_full;
}


----------------------------
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t block_size;
} mi_page_queue_t
----------------------------
None
----------------------------
***/


static mi_page_t *mi_page_queue_find_free_ex(mi_heap_t *heap, mi_page_queue_t *pq, bool first_try)
{
  size_t count = 0;
  size_t candidate_count = 0;
  mi_page_t *page_candidate = 0;
  unsigned int page_candidate_idx = 0;
  mi_page_t *page = pq->first;
  unsigned int page_idx = 0;
  while ((&page[page_idx]) != 0)
  {
    helper_mi_page_queue_find_free_ex_1(&count, &candidate_count, &page_candidate_idx, &page_idx, pq, page_candidate, page);
  }

  _mi_stat_counter_increase(&heap->tld->stats.page_searches, count);
  if ((&page_candidate[page_candidate_idx]) != 0)
  {
    page_idx = &page_candidate[page_candidate_idx];
  }
  if ((&page[page_idx]) != 0)
  {
    if (!mi_page_immediate_available(page))
    {
      (mi_page_is_expandable(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_expandable(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 827, __func__));
      if (!mi_page_extend_free(heap, page, heap->tld))
      {
        page_idx = 0;
      }
    }
    (((&page[page_idx]) == 0) || mi_page_immediate_available(page)) ? ((void) 0) : (_mi_assert_fail("page == NULL || mi_page_immediate_available(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 832, __func__));
  }
  if ((&page[page_idx]) == 0)
  {
    _mi_heap_collect_retired(heap, 0);
    page_idx = mi_page_fresh(heap, pq);
    if (((&page[page_idx]) == 0) && first_try)
    {
      page_idx = mi_page_queue_find_free_ex(heap, pq, 0);
    }
  }
  else
  {
    mi_page_queue_move_to_front(heap, pq, page);
    page->retire_expire = 0;
  }
  (((&page[page_idx]) == 0) || mi_page_immediate_available(page)) ? ((void) 0) : (_mi_assert_fail("page == NULL || mi_page_immediate_available(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 849, __func__));
  return page;
}


/*** DEPENDENCIES:
static bool mi_page_is_expandable(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 746, __func__));
  (page->capacity <= page->reserved) ? ((void) 0) : (_mi_assert_fail("page->capacity <= page->reserved", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 747, __func__));
  return page->capacity < page->reserved;
}


----------------------------
void helper_mi_page_queue_find_free_ex_1(size_t * const count_ref, size_t * const candidate_count_ref, unsigned int * const page_candidate_idx_ref, unsigned int * const page_idx_ref, mi_page_queue_t * const pq, mi_page_t * const page_candidate, mi_page_t * const page)
{
  size_t count = *count_ref;
  size_t candidate_count = *candidate_count_ref;
  unsigned int page_candidate_idx = *page_candidate_idx_ref;
  unsigned int page_idx = *page_idx_ref;
  mi_page_t *next = page->next;
  count += 1;
  candidate_count += 1;
  _mi_page_free_collect(page, 0);
  const bool immediate_available = mi_page_immediate_available(page);
  if ((!immediate_available) && (!mi_page_is_expandable(page)))
  {
    ((!mi_page_is_in_full(page)) && (!mi_page_immediate_available(page))) ? ((void) 0) : (_mi_assert_fail("!mi_page_is_in_full(page) && !mi_page_immediate_available(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 783, __func__));
    mi_page_to_full(page, pq);
  }
  else
  {
    if ((&page_candidate[page_candidate_idx]) == 0)
    {
      page_candidate_idx = &page[page_idx];
      candidate_count = 0;
    }
    else
      if (((page->used >= page_candidate->used) && (!mi_page_is_mostly_used(page))) && (!mi_page_is_expandable(page)))
    {
      page_candidate_idx = &page[page_idx];
    }
    if (immediate_available || (candidate_count > 4))
    {
      ((&page_candidate[page_candidate_idx]) != 0) ? ((void) 0) : (_mi_assert_fail("page_candidate!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 799, __func__));
      break;
    }
  }
  page_idx = next;
  *count_ref = count;
  *candidate_count_ref = candidate_count;
  *page_candidate_idx_ref = page_candidate_idx;
  *page_idx_ref = page_idx;
}


----------------------------
None
----------------------------
inline static bool mi_page_immediate_available(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 668, __func__));
  return page->free != 0;
}


----------------------------
static mi_page_t *mi_page_fresh(mi_heap_t *heap, mi_page_queue_t *pq)
{
  (mi_heap_contains_queue(heap, pq)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap, pq)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 302, __func__));
  mi_page_t *page = mi_page_fresh_alloc(heap, pq, pq->block_size, 0);
  if (page == 0)
  {
    return 0;
  }
  (pq->block_size == mi_page_block_size(page)) ? ((void) 0) : (_mi_assert_fail("pq->block_size==mi_page_block_size(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 305, __func__));
  (pq == mi_page_queue(heap, mi_page_block_size(page))) ? ((void) 0) : (_mi_assert_fail("pq==mi_page_queue(heap, mi_page_block_size(page))", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 306, __func__));
  return page;
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
void _mi_heap_collect_retired(mi_heap_t *heap, bool force)
{
  size_t min = 73U + 1;
  size_t max = 0;
  for (size_t bin = heap->page_retired_min; bin <= heap->page_retired_max; bin += 1)
  {
    mi_page_queue_t *pq = &heap->pages[bin];
    mi_page_t *page = pq->first;
    if ((page != 0) && (page->retire_expire != 0))
    {
      if (mi_page_all_free(page))
      {
        page->retire_expire -= 1;
        if (force || (page->retire_expire == 0))
        {
          _mi_page_free(pq->first, pq, force);
        }
        else
        {
          if (bin < min)
          {
            min = bin;
          }
          if (bin > max)
          {
            max = bin;
          }
        }
      }
      else
      {
        page->retire_expire = 0;
      }
    }
  }

  heap->page_retired_min = min;
  heap->page_retired_max = max;
}


----------------------------
static void mi_page_queue_move_to_front(mi_heap_t *heap, mi_page_queue_t *queue, mi_page_t *page)
{
  (mi_page_heap(page) == heap) ? ((void) 0) : (_mi_assert_fail("mi_page_heap(page) == heap", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 267, __func__));
  (mi_page_queue_contains(queue, page)) ? ((void) 0) : (_mi_assert_fail("mi_page_queue_contains(queue, page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 268, __func__));
  if (queue->first == page)
  {
    return;
  }
  mi_page_queue_remove(queue, page);
  mi_page_queue_push(heap, queue, page);
  (queue->first == page) ? ((void) 0) : (_mi_assert_fail("queue->first == page", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c", 272, __func__));
}


----------------------------
static bool mi_page_extend_free(mi_heap_t *heap, mi_page_t *page, mi_tld_t *tld)
{
  ;
  (page->free == 0) ? ((void) 0) : (_mi_assert_fail("page->free == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 638, __func__));
  (page->local_free == 0) ? ((void) 0) : (_mi_assert_fail("page->local_free == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 639, __func__));
  if (page->free != 0)
  {
    return 1;
  }
  if (page->capacity >= page->reserved)
  {
    return 1;
  }
  _mi_stat_counter_increase(&tld->stats.pages_extended, 1);
  const size_t bsize = mi_page_block_size(page);
  size_t extend = page->reserved - page->capacity;
  (extend > 0) ? ((void) 0) : (_mi_assert_fail("extend > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 649, __func__));
  size_t max_extend = (bsize >= (4 * 1024)) ? (4) : ((4 * 1024) / bsize);
  if (max_extend < 4)
  {
    max_extend = 4;
  }
  (max_extend > 0) ? ((void) 0) : (_mi_assert_fail("max_extend > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 653, __func__));
  if (extend > max_extend)
  {
    extend = max_extend;
  }
  ((extend > 0) && ((extend + page->capacity) <= page->reserved)) ? ((void) 0) : (_mi_assert_fail("extend > 0 && extend + page->capacity <= page->reserved", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 661, __func__));
  (extend < (1UL << 16)) ? ((void) 0) : (_mi_assert_fail("extend < (1UL<<16)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 662, __func__));
  if ((extend < 2) || (0 == 0))
  {
    mi_page_free_list_extend(page, bsize, extend, &tld->stats);
  }
  else
  {
    mi_page_free_list_extend_secure(heap, page, bsize, extend, &tld->stats);
  }
  page->capacity += (uint16_t) extend;
  _mi_stat_increase(&tld->stats.page_committed, extend * bsize);
  ;
  return 1;
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
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t block_size;
} mi_page_queue_t
----------------------------
None
----------------------------
***/


inline static mi_page_t *mi_find_free_page(mi_heap_t *heap, size_t size)
{
  mi_page_queue_t *pq = mi_page_queue(heap, size);
  mi_page_t *page = pq->first;
  if (page != 0)
  {
    {
      _mi_page_free_collect(page, 0);
    }
    if (mi_page_immediate_available(page))
    {
      page->retire_expire = 0;
      return page;
    }
  }
  return mi_page_queue_find_free_ex(heap, pq, 1);
}


/*** DEPENDENCIES:
static mi_page_t *mi_page_queue_find_free_ex(mi_heap_t *heap, mi_page_queue_t *pq, bool first_try)
{
  size_t count = 0;
  size_t candidate_count = 0;
  mi_page_t *page_candidate = 0;
  unsigned int page_candidate_idx = 0;
  mi_page_t *page = pq->first;
  unsigned int page_idx = 0;
  while ((&page[page_idx]) != 0)
  {
    helper_mi_page_queue_find_free_ex_1(&count, &candidate_count, &page_candidate_idx, &page_idx, pq, page_candidate, page);
  }

  _mi_stat_counter_increase(&heap->tld->stats.page_searches, count);
  if ((&page_candidate[page_candidate_idx]) != 0)
  {
    page_idx = &page_candidate[page_candidate_idx];
  }
  if ((&page[page_idx]) != 0)
  {
    if (!mi_page_immediate_available(page))
    {
      (mi_page_is_expandable(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_expandable(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 827, __func__));
      if (!mi_page_extend_free(heap, page, heap->tld))
      {
        page_idx = 0;
      }
    }
    (((&page[page_idx]) == 0) || mi_page_immediate_available(page)) ? ((void) 0) : (_mi_assert_fail("page == NULL || mi_page_immediate_available(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 832, __func__));
  }
  if ((&page[page_idx]) == 0)
  {
    _mi_heap_collect_retired(heap, 0);
    page_idx = mi_page_fresh(heap, pq);
    if (((&page[page_idx]) == 0) && first_try)
    {
      page_idx = mi_page_queue_find_free_ex(heap, pq, 0);
    }
  }
  else
  {
    mi_page_queue_move_to_front(heap, pq, page);
    page->retire_expire = 0;
  }
  (((&page[page_idx]) == 0) || mi_page_immediate_available(page)) ? ((void) 0) : (_mi_assert_fail("page == NULL || mi_page_immediate_available(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 849, __func__));
  return page;
}


----------------------------
void _mi_page_free_collect(mi_page_t *page, bool force)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 218, __func__));
  if (force || (mi_page_thread_free(page) != 0))
  {
    _mi_page_thread_free_collect(page);
  }
  if (page->local_free != 0)
  {
    if (__builtin_expect(!(!(page->free == 0)), 1))
    {
      page->free = page->local_free;
      page->local_free = 0;
      page->free_is_zero = 0;
    }
    else
      if (force)
    {
      mi_block_t *tail = page->local_free;
      unsigned int tail_idx = 0;
      mi_block_t *next;
      unsigned int next_idx = 0;
      while ((next_idx = mi_block_next(page, tail)) != 0)
      {
        tail_idx = &next[next_idx];
      }

      mi_block_set_next(page, tail, page->free);
      page->free = page->local_free;
      page->local_free = 0;
      page->free_is_zero = 0;
    }
  }
  ((!force) || (page->local_free == 0)) ? ((void) 0) : (_mi_assert_fail("!force || page->local_free == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 247, __func__));
}


----------------------------
inline static bool mi_page_immediate_available(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 668, __func__));
  return page->free != 0;
}


----------------------------
inline static mi_page_queue_t *mi_page_queue(const mi_heap_t *heap, size_t size)
{
  return &((mi_heap_t *) heap)->pages[_mi_bin(size)];
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
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t block_size;
} mi_page_queue_t
----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
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
inline static mi_page_t *mi_find_free_page(mi_heap_t *heap, size_t size)
{
  mi_page_queue_t *pq = mi_page_queue(heap, size);
  mi_page_t *page = pq->first;
  if (page != 0)
  {
    {
      _mi_page_free_collect(page, 0);
    }
    if (mi_page_immediate_available(page))
    {
      page->retire_expire = 0;
      return page;
    }
  }
  return mi_page_queue_find_free_ex(heap, pq, 1);
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
static mi_page_t *mi_large_huge_page_alloc(mi_heap_t *heap, size_t size, size_t page_alignment)
{
  size_t block_size = _mi_os_good_alloc_size(size);
  ((mi_bin(block_size) == 73U) || (page_alignment > 0)) ? ((void) 0) : (_mi_assert_fail("mi_bin(block_size) == MI_BIN_HUGE || page_alignment > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 920, __func__));
  bool is_huge = (block_size > ((1UL << (9 + (13 + 3))) / 2)) || (page_alignment > 0);
  mi_page_queue_t *pq = mi_page_queue(heap, (is_huge) ? (((1UL << (9 + (13 + 3))) / 2) + 1) : (block_size));
  ((!is_huge) || mi_page_queue_is_huge(pq)) ? ((void) 0) : (_mi_assert_fail("!is_huge || mi_page_queue_is_huge(pq)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 926, __func__));
  mi_page_t *page = mi_page_fresh_alloc(heap, pq, block_size, page_alignment);
  if (page != 0)
  {
    (mi_page_immediate_available(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_immediate_available(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 930, __func__));
    if (is_huge)
    {
      (mi_page_is_huge(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_huge(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 933, __func__));
      (_mi_page_segment(page)->kind == MI_SEGMENT_HUGE) ? ((void) 0) : (_mi_assert_fail("_mi_page_segment(page)->kind == MI_SEGMENT_HUGE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 934, __func__));
      (_mi_page_segment(page)->used == 1) ? ((void) 0) : (_mi_assert_fail("_mi_page_segment(page)->used==1", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 935, __func__));
    }
    else
    {
      (!mi_page_is_huge(page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_is_huge(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c", 942, __func__));
    }
    const size_t bsize = mi_page_usable_block_size(page);
    {
      _mi_stat_increase(&heap->tld->stats.malloc_huge, bsize);
      _mi_stat_counter_increase(&heap->tld->stats.malloc_huge_count, 1);
    }
  }
  return page;
}


----------------------------
None
----------------------------
***/


void mi_register_deferred_free(mi_deferred_free_fun *fn, void *arg)
{
  deferred_free = fn;
  atomic_store_explicit(&deferred_arg, arg, memory_order_release);
}


/*** DEPENDENCIES:
static void * _Atomic deferred_arg
----------------------------
static mi_deferred_free_fun * volatile deferred_free = 0
----------------------------
typedef void mi_deferred_free_fun(bool force, unsigned long long heartbeat, void *arg)
----------------------------
***/


