static size_t mi_bin(size_t size)
{
  size_t wsize = _mi_wsize_from_size(size);
  if (__builtin_expect(!(!(wsize <= 8)), 1))
  {
    return (wsize <= 1) ? (1) : ((wsize + 1) & (~1));
  }
  else
    if (__builtin_expect(!(!(wsize > (((8 * (1 * (1UL << (13 + 3)))) / 8) / (1 << 3)))), 0))
  {
    return 73U;
  }
  else
  {
    wsize -= 1;
    const size_t b = (((1 << 3) * 8) - 1) - mi_clz(wsize);
    const size_t bin = ((b << 2) + ((wsize >> (b - 2)) & 0x03)) - 3;
    ((bin > 0) && (bin < 73U)) ? ((void) 0) : (_mi_assert_fail("bin > 0 && bin < MI_BIN_HUGE", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 92, __func__));
    return bin;
  }
}


/*** DEPENDENCIES:
inline static size_t _mi_wsize_from_size(size_t size)
{
  (size <= (SIZE_MAX - (sizeof(uintptr_t)))) ? ((void) 0) : (_mi_assert_fail("size <= SIZE_MAX - sizeof(uintptr_t)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 486, __func__));
  return ((size + (sizeof(uintptr_t))) - 1) / (sizeof(uintptr_t));
}


----------------------------
inline static size_t mi_clz(size_t x)
{
  return (x != 0) ? ((size_t) __builtin_clzll(x)) : ((1 << 3) * 8);
}


----------------------------
None
----------------------------
***/


size_t _mi_bin_size(size_t bin)
{
  (bin <= 73U) ? ((void) 0) : (_mi_assert_fail("bin <= MI_BIN_HUGE", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 108, __func__));
  return _mi_heap_empty.pages[bin].block_size;
}


/*** DEPENDENCIES:
extern const mi_heap_t _mi_heap_empty
----------------------------
None
----------------------------
***/


size_t mi_good_size(size_t size)
{
  if (size <= ((8 * (1 * (1UL << (13 + 3)))) / 8))
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
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 429, __func__));
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
  (bin <= 73U) ? ((void) 0) : (_mi_assert_fail("bin <= MI_BIN_HUGE", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 108, __func__));
  return _mi_heap_empty.pages[bin].block_size;
}


----------------------------
size_t _mi_os_page_size(void)
{
  return mi_os_mem_config.page_size;
}


----------------------------
static size_t mi_bin(size_t size)
{
  size_t wsize = _mi_wsize_from_size(size);
  if (__builtin_expect(!(!(wsize <= 8)), 1))
  {
    return (wsize <= 1) ? (1) : ((wsize + 1) & (~1));
  }
  else
    if (__builtin_expect(!(!(wsize > (((8 * (1 * (1UL << (13 + 3)))) / 8) / (1 << 3)))), 0))
  {
    return 73U;
  }
  else
  {
    wsize -= 1;
    const size_t b = (((1 << 3) * 8) - 1) - mi_clz(wsize);
    const size_t bin = ((b << 2) + ((wsize >> (b - 2)) & 0x03)) - 3;
    ((bin > 0) && (bin < 73U)) ? ((void) 0) : (_mi_assert_fail("bin > 0 && bin < MI_BIN_HUGE", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 92, __func__));
    return bin;
  }
}


----------------------------
***/


inline static bool mi_page_queue_is_special(const mi_page_queue_t *pq)
{
  return pq->block_size > ((8 * (1 * (1UL << (13 + 3)))) / 8);
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static bool mi_page_queue_is_huge(const mi_page_queue_t *pq)
{
  return pq->block_size == (((8 * (1 * (1UL << (13 + 3)))) / 8) + (sizeof(uintptr_t)));
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static bool mi_page_queue_is_full(const mi_page_queue_t *pq)
{
  return pq->block_size == (((8 * (1 * (1UL << (13 + 3)))) / 8) + (2 * (sizeof(uintptr_t))));
}


/*** DEPENDENCIES:
None
----------------------------
***/


size_t _mi_page_bin(const mi_page_t *page)
{
  const size_t bin = (mi_page_is_in_full(page)) ? (73U + 1) : ((mi_page_is_huge(page)) ? (73U) : (mi_bin(mi_page_block_size(page))));
  (bin <= (73U + 1)) ? ((void) 0) : (_mi_assert_fail("bin <= MI_BIN_FULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 172, __func__));
  return bin;
}


/*** DEPENDENCIES:
None
----------------------------
static size_t mi_bin(size_t size)
{
  size_t wsize = _mi_wsize_from_size(size);
  if (__builtin_expect(!(!(wsize <= 8)), 1))
  {
    return (wsize <= 1) ? (1) : ((wsize + 1) & (~1));
  }
  else
    if (__builtin_expect(!(!(wsize > (((8 * (1 * (1UL << (13 + 3)))) / 8) / (1 << 3)))), 0))
  {
    return 73U;
  }
  else
  {
    wsize -= 1;
    const size_t b = (((1 << 3) * 8) - 1) - mi_clz(wsize);
    const size_t bin = ((b << 2) + ((wsize >> (b - 2)) & 0x03)) - 3;
    ((bin > 0) && (bin < 73U)) ? ((void) 0) : (_mi_assert_fail("bin > 0 && bin < MI_BIN_HUGE", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 92, __func__));
    return bin;
  }
}


----------------------------
inline static bool mi_page_is_huge(const mi_page_t *page)
{
  return mi_page_is_singleton(page) && ((page->block_size > ((8 * (1 * (1UL << (13 + 3)))) / 8)) || (mi_memkind_is_os(page->memid.memkind) && (page->memid.mem.os.base < ((void *) page))));
}


----------------------------
inline static bool mi_page_is_in_full(const mi_page_t *page)
{
  return (mi_page_flags(page) & 0x01UL) != 0;
}


----------------------------
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
}


----------------------------
None
----------------------------
***/


static mi_page_queue_t *mi_heap_page_queue_of(mi_heap_t *heap, const mi_page_t *page)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 177, __func__));
  const size_t bin = _mi_page_bin(page);
  mi_page_queue_t *pq = &heap->pages[bin];
  (((mi_page_block_size(page) == pq->block_size) || (mi_page_is_huge(page) && mi_page_queue_is_huge(pq))) || (mi_page_is_in_full(page) && mi_page_queue_is_full(pq))) ? ((void) 0) : (_mi_assert_fail("(mi_page_block_size(page) == pq->block_size) || (mi_page_is_huge(page) && mi_page_queue_is_huge(pq)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(pq))", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 180, __func__));
  return pq;
}


/*** DEPENDENCIES:
size_t _mi_page_bin(const mi_page_t *page)
{
  const size_t bin = (mi_page_is_in_full(page)) ? (73U + 1) : ((mi_page_is_huge(page)) ? (73U) : (mi_bin(mi_page_block_size(page))));
  (bin <= (73U + 1)) ? ((void) 0) : (_mi_assert_fail("bin <= MI_BIN_FULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 172, __func__));
  return bin;
}


----------------------------
None
----------------------------
inline static bool mi_page_queue_is_full(const mi_page_queue_t *pq)
{
  return pq->block_size == (((8 * (1 * (1UL << (13 + 3)))) / 8) + (2 * (sizeof(uintptr_t))));
}


----------------------------
inline static bool mi_page_is_huge(const mi_page_t *page)
{
  return mi_page_is_singleton(page) && ((page->block_size > ((8 * (1 * (1UL << (13 + 3)))) / 8)) || (mi_memkind_is_os(page->memid.memkind) && (page->memid.mem.os.base < ((void *) page))));
}


----------------------------
inline static bool mi_page_is_in_full(const mi_page_t *page)
{
  return (mi_page_flags(page) & 0x01UL) != 0;
}


----------------------------
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
}


----------------------------
inline static bool mi_page_queue_is_huge(const mi_page_queue_t *pq)
{
  return pq->block_size == (((8 * (1 * (1UL << (13 + 3)))) / 8) + (sizeof(uintptr_t)));
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
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 177, __func__));
  const size_t bin = _mi_page_bin(page);
  mi_page_queue_t *pq = &heap->pages[bin];
  (((mi_page_block_size(page) == pq->block_size) || (mi_page_is_huge(page) && mi_page_queue_is_huge(pq))) || (mi_page_is_in_full(page) && mi_page_queue_is_full(pq))) ? ((void) 0) : (_mi_assert_fail("(mi_page_block_size(page) == pq->block_size) || (mi_page_is_huge(page) && mi_page_queue_is_huge(pq)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(pq))", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 180, __func__));
  return pq;
}


----------------------------
inline static mi_heap_t *mi_page_heap(const mi_page_t *page)
{
  return page->heap;
}


----------------------------
None
----------------------------
***/


static bool mi_heap_contains_queue(const mi_heap_t *heap, const mi_page_queue_t *pq)
{
  return (pq >= (&heap->pages[0])) && (pq <= (&heap->pages[73U + 1]));
}


/*** DEPENDENCIES:
None
----------------------------
***/


inline static void mi_heap_queue_first_update(mi_heap_t *heap, const mi_page_queue_t *pq)
{
  (mi_heap_contains_queue(heap, pq)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap,pq)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 199, __func__));
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
  (start <= idx) ? ((void) 0) : (_mi_assert_fail("start <= idx", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 229, __func__));
  for (size_t sz = start; sz <= idx; sz += 1)
  {
    pages_free[sz] = &page[page_idx];
  }

}


/*** DEPENDENCIES:
None
----------------------------
static size_t mi_bin(size_t size)
{
  size_t wsize = _mi_wsize_from_size(size);
  if (__builtin_expect(!(!(wsize <= 8)), 1))
  {
    return (wsize <= 1) ? (1) : ((wsize + 1) & (~1));
  }
  else
    if (__builtin_expect(!(!(wsize > (((8 * (1 * (1UL << (13 + 3)))) / 8) / (1 << 3)))), 0))
  {
    return 73U;
  }
  else
  {
    wsize -= 1;
    const size_t b = (((1 << 3) * 8) - 1) - mi_clz(wsize);
    const size_t bin = ((b << 2) + ((wsize >> (b - 2)) & 0x03)) - 3;
    ((bin > 0) && (bin < 73U)) ? ((void) 0) : (_mi_assert_fail("bin > 0 && bin < MI_BIN_HUGE", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 92, __func__));
    return bin;
  }
}


----------------------------
inline static size_t _mi_wsize_from_size(size_t size)
{
  (size <= (SIZE_MAX - (sizeof(uintptr_t)))) ? ((void) 0) : (_mi_assert_fail("size <= SIZE_MAX - sizeof(uintptr_t)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 486, __func__));
  return ((size + (sizeof(uintptr_t))) - 1) / (sizeof(uintptr_t));
}


----------------------------
extern const mi_page_t _mi_page_empty
----------------------------
static bool mi_heap_contains_queue(const mi_heap_t *heap, const mi_page_queue_t *pq)
{
  return (pq >= (&heap->pages[0])) && (pq <= (&heap->pages[73U + 1]));
}


----------------------------
None
----------------------------
***/


static void mi_page_queue_remove(mi_page_queue_t *queue, mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 242, __func__));
  ;
  (queue->count >= 1) ? ((void) 0) : (_mi_assert_fail("queue->count >= 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 244, __func__));
  (((mi_page_block_size(page) == queue->block_size) || (mi_page_is_huge(page) && mi_page_queue_is_huge(queue))) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) == queue->block_size || (mi_page_is_huge(page) && mi_page_queue_is_huge(queue)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 245, __func__));
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
    (mi_heap_contains_queue(heap, queue)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap, queue)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 255, __func__));
    mi_heap_queue_first_update(heap, queue);
  }
  heap->page_count -= 1;
  queue->count -= 1;
  page->next = 0;
  page->prev = 0;
  mi_page_set_in_full(page, 0);
}


/*** DEPENDENCIES:
None
----------------------------
inline static mi_heap_t *mi_page_heap(const mi_page_t *page)
{
  return page->heap;
}


----------------------------
inline static bool mi_page_queue_is_full(const mi_page_queue_t *pq)
{
  return pq->block_size == (((8 * (1 * (1UL << (13 + 3)))) / 8) + (2 * (sizeof(uintptr_t))));
}


----------------------------
inline static void mi_page_set_in_full(mi_page_t *page, bool in_full)
{
  mi_page_flags_set(page, in_full, 0x01UL);
}


----------------------------
inline static bool mi_page_is_huge(const mi_page_t *page)
{
  return mi_page_is_singleton(page) && ((page->block_size > ((8 * (1 * (1UL << (13 + 3)))) / 8)) || (mi_memkind_is_os(page->memid.memkind) && (page->memid.mem.os.base < ((void *) page))));
}


----------------------------
inline static void mi_heap_queue_first_update(mi_heap_t *heap, const mi_page_queue_t *pq)
{
  (mi_heap_contains_queue(heap, pq)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap,pq)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 199, __func__));
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
  (start <= idx) ? ((void) 0) : (_mi_assert_fail("start <= idx", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 229, __func__));
  for (size_t sz = start; sz <= idx; sz += 1)
  {
    pages_free[sz] = &page[page_idx];
  }

}


----------------------------
inline static bool mi_page_is_in_full(const mi_page_t *page)
{
  return (mi_page_flags(page) & 0x01UL) != 0;
}


----------------------------
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
}


----------------------------
static bool mi_heap_contains_queue(const mi_heap_t *heap, const mi_page_queue_t *pq)
{
  return (pq >= (&heap->pages[0])) && (pq <= (&heap->pages[73U + 1]));
}


----------------------------
inline static bool mi_page_queue_is_huge(const mi_page_queue_t *pq)
{
  return pq->block_size == (((8 * (1 * (1UL << (13 + 3)))) / 8) + (sizeof(uintptr_t)));
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
static size_t mi_bin(size_t size)
{
  size_t wsize = _mi_wsize_from_size(size);
  if (__builtin_expect(!(!(wsize <= 8)), 1))
  {
    return (wsize <= 1) ? (1) : ((wsize + 1) & (~1));
  }
  else
    if (__builtin_expect(!(!(wsize > (((8 * (1 * (1UL << (13 + 3)))) / 8) / (1 << 3)))), 0))
  {
    return 73U;
  }
  else
  {
    wsize -= 1;
    const size_t b = (((1 << 3) * 8) - 1) - mi_clz(wsize);
    const size_t bin = ((b << 2) + ((wsize >> (b - 2)) & 0x03)) - 3;
    ((bin > 0) && (bin < 73U)) ? ((void) 0) : (_mi_assert_fail("bin > 0 && bin < MI_BIN_HUGE", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 92, __func__));
    return bin;
  }
}


----------------------------
***/


void _mi_page_free(mi_page_t *page, mi_page_queue_t *pq)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 381, __func__));
  ;
  (pq == mi_page_queue_of(page)) ? ((void) 0) : (_mi_assert_fail("pq == mi_page_queue_of(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 383, __func__));
  (mi_page_all_free(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_all_free(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 384, __func__));
  mi_page_set_has_interior_pointers(page, 0);
  mi_page_queue_remove(pq, page);
  mi_tld_t * const tld = page->heap->tld;
  mi_page_set_heap(page, 0);
  _mi_arenas_page_free(page, tld);
  _mi_arenas_collect(0, 0, tld);
}


/*** DEPENDENCIES:
None
----------------------------
void _mi_arenas_page_free(mi_page_t *page, mi_tld_t *stats_tld)
{
  (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 808, __func__));
  (_mi_ptr_page(page) == page) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 809, __func__));
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 810, __func__));
  (mi_page_all_free(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_all_free(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 811, __func__));
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 812, __func__));
  ((page->next == 0) && (page->prev == 0)) ? ((void) 0) : (_mi_assert_fail("page->next==NULL && page->prev==NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 813, __func__));
  if (stats_tld != 0)
  {
    __mi_stat_decrease(&stats_tld->stats.page_bins[_mi_page_bin(page)], 1);
    __mi_stat_decrease(&stats_tld->stats.pages, 1);
  }
  else
  {
    __mi_stat_decrease_mt(&_mi_subproc()->stats.page_bins[_mi_page_bin(page)], 1);
    __mi_stat_decrease_mt(&_mi_subproc()->stats.pages, 1);
  }
  if ((page->memid.memkind == MI_MEM_ARENA) && (!mi_page_is_full(page)))
  {
    size_t bin = _mi_bin(mi_page_block_size(page));
    size_t slice_index;
    size_t slice_count;
    mi_arena_t * const arena = mi_page_arena(page, &slice_index, &slice_count);
    (mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 830, __func__));
    ((page->slice_committed > 0) || mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("page->slice_committed > 0 || mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 831, __func__));
    (mi_bitmap_is_clearN(arena->pages_abandoned[bin], slice_index, 1)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_clearN(arena->pages_abandoned[bin], slice_index, 1)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 832, __func__));
    (mi_bitmap_is_setN(page->memid.mem.arena.arena->pages, page->memid.mem.arena.slice_index, 1)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_setN(page->memid.mem.arena.arena->pages, page->memid.mem.arena.slice_index, 1)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 833, __func__));
  }
  _mi_page_map_unregister(page);
  if (page->memid.memkind == MI_MEM_ARENA)
  {
    helper__mi_arenas_page_free_1(page);
  }
  _mi_arenas_free(page, mi_page_full_size(page), page->memid);
}


----------------------------
static void mi_page_queue_remove(mi_page_queue_t *queue, mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 242, __func__));
  ;
  (queue->count >= 1) ? ((void) 0) : (_mi_assert_fail("queue->count >= 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 244, __func__));
  (((mi_page_block_size(page) == queue->block_size) || (mi_page_is_huge(page) && mi_page_queue_is_huge(queue))) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) == queue->block_size || (mi_page_is_huge(page) && mi_page_queue_is_huge(queue)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 245, __func__));
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
    (mi_heap_contains_queue(heap, queue)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap, queue)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 255, __func__));
    mi_heap_queue_first_update(heap, queue);
  }
  heap->page_count -= 1;
  queue->count -= 1;
  page->next = 0;
  page->prev = 0;
  mi_page_set_in_full(page, 0);
}


----------------------------
inline static void mi_page_set_heap(mi_page_t *page, mi_heap_t *heap)
{
  if (heap != 0)
  {
    page->heap = heap;
    page->heap_tag = heap->tag;
  }
  else
  {
    page->heap = 0;
  }
  const mi_threadid_t tid = (heap == 0) ? (0UL) : (heap->tld->thread_id);
  ((tid & 0x03UL) == 0) ? ((void) 0) : (_mi_assert_fail("(tid & MI_PAGE_FLAG_MASK) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 816, __func__));
  mi_threadid_t xtid_old = mi_page_xthread_id(page);
  mi_threadid_t xtid;
  do
  {
    xtid = tid | (xtid_old & 0x03UL);
  }
  while (!atomic_compare_exchange_weak_explicit(&page->xthread_id, &xtid_old, xtid, memory_order_release, memory_order_relaxed));
}


----------------------------
inline static bool mi_page_all_free(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 714, __func__));
  return page->used == 0;
}


----------------------------
void _mi_arenas_collect(bool force_purge, bool visit_all, mi_tld_t *tld)
{
  mi_arenas_try_purge(force_purge, visit_all, tld->subproc, tld->thread_seq);
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
inline static void mi_page_set_has_interior_pointers(mi_page_t *page, bool has_aligned)
{
  mi_page_flags_set(page, has_aligned, 0x02UL);
}


----------------------------
None
----------------------------
***/


void _mi_page_retire(mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 411, __func__));
  ;
  (mi_page_all_free(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_all_free(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 413, __func__));
  mi_page_set_has_interior_pointers(page, 0);
  mi_page_queue_t *pq = mi_page_queue_of(page);
  const size_t bsize = mi_page_block_size(page);
  if (__builtin_expect(!(!(!mi_page_queue_is_special(pq))), 1))
  {
    if ((pq->last == page) && (pq->first == page))
    {
      mi_heap_t *heap = mi_page_heap(page);
      __mi_stat_counter_increase(&heap->tld->stats.pages_retire, 1);
      page->retire_expire = (bsize <= (((1 * (1UL << (13 + 3))) - ((3 + 2) * 32)) / 8)) ? (16) : (16 / 4);
      (pq >= heap->pages) ? ((void) 0) : (_mi_assert_fail("pq >= heap->pages", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 433, __func__));
      const size_t index = pq - heap->pages;
      ((index < (73U + 1)) && (index < 73U)) ? ((void) 0) : (_mi_assert_fail("index < MI_BIN_FULL && index < MI_BIN_HUGE", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 435, __func__));
      if (index < heap->page_retired_min)
      {
        heap->page_retired_min = index;
      }
      if (index > heap->page_retired_max)
      {
        heap->page_retired_max = index;
      }
      (mi_page_all_free(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_all_free(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 438, __func__));
      return;
    }
  }
  _mi_page_free(page, pq);
}


/*** DEPENDENCIES:
None
----------------------------
inline static mi_heap_t *mi_page_heap(const mi_page_t *page)
{
  return page->heap;
}


----------------------------
void __mi_stat_counter_increase(mi_stat_counter_t *stat, size_t amount)
{
  stat->total += amount;
}


----------------------------
void _mi_page_free(mi_page_t *page, mi_page_queue_t *pq)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 381, __func__));
  ;
  (pq == mi_page_queue_of(page)) ? ((void) 0) : (_mi_assert_fail("pq == mi_page_queue_of(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 383, __func__));
  (mi_page_all_free(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_all_free(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 384, __func__));
  mi_page_set_has_interior_pointers(page, 0);
  mi_page_queue_remove(pq, page);
  mi_tld_t * const tld = page->heap->tld;
  mi_page_set_heap(page, 0);
  _mi_arenas_page_free(page, tld);
  _mi_arenas_collect(0, 0, tld);
}


----------------------------
inline static bool mi_page_queue_is_special(const mi_page_queue_t *pq)
{
  return pq->block_size > ((8 * (1 * (1UL << (13 + 3)))) / 8);
}


----------------------------
inline static bool mi_page_all_free(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 714, __func__));
  return page->used == 0;
}


----------------------------
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
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
inline static void mi_page_set_has_interior_pointers(mi_page_t *page, bool has_aligned)
{
  mi_page_flags_set(page, has_aligned, 0x02UL);
}


----------------------------
None
----------------------------
***/


void helper_mi_page_queue_enqueue_from_ex_1(mi_page_queue_t * const to, mi_page_t * const page, mi_heap_t * const heap)
{
  if (to->first != 0)
  {
    (heap == mi_page_heap(to->first)) ? ((void) 0) : (_mi_assert_fail("heap == mi_page_heap(to->first)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 380, __func__));
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
inline static void mi_heap_queue_first_update(mi_heap_t *heap, const mi_page_queue_t *pq)
{
  (mi_heap_contains_queue(heap, pq)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap,pq)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 199, __func__));
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
  (start <= idx) ? ((void) 0) : (_mi_assert_fail("start <= idx", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 229, __func__));
  for (size_t sz = start; sz <= idx; sz += 1)
  {
    pages_free[sz] = &page[page_idx];
  }

}


----------------------------
inline static mi_heap_t *mi_page_heap(const mi_page_t *page)
{
  return page->heap;
}


----------------------------
None
----------------------------
***/


static void mi_page_queue_enqueue_from_ex(mi_page_queue_t *to, mi_page_queue_t *from, bool enqueue_at_end, mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 334, __func__));
  (from->count >= 1) ? ((void) 0) : (_mi_assert_fail("from->count >= 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 335, __func__));
  ;
  ;
  const size_t bsize = mi_page_block_size(page);
  (void) bsize;
  ((((((bsize == to->block_size) && (bsize == from->block_size)) || ((bsize == to->block_size) && mi_page_queue_is_full(from))) || ((bsize == from->block_size) && mi_page_queue_is_full(to))) || (mi_page_is_huge(page) && mi_page_queue_is_huge(to))) || (mi_page_is_huge(page) && mi_page_queue_is_full(to))) ? ((void) 0) : (_mi_assert_fail("(bsize == to->block_size && bsize == from->block_size) || (bsize == to->block_size && mi_page_queue_is_full(from)) || (bsize == from->block_size && mi_page_queue_is_full(to)) || (mi_page_is_huge(page) && mi_page_queue_is_huge(to)) || (mi_page_is_huge(page) && mi_page_queue_is_full(to))", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 340, __func__));
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
    (mi_heap_contains_queue(heap, from)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap, from)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 355, __func__));
    mi_heap_queue_first_update(heap, from);
  }
  from->count -= 1;
  to->count += 1;
  if (enqueue_at_end)
  {
    page->prev = to->last;
    page->next = 0;
    if (to->last != 0)
    {
      (heap == mi_page_heap(to->last)) ? ((void) 0) : (_mi_assert_fail("heap == mi_page_heap(to->last)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 367, __func__));
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
None
----------------------------
inline static mi_heap_t *mi_page_heap(const mi_page_t *page)
{
  return page->heap;
}


----------------------------
inline static bool mi_page_queue_is_full(const mi_page_queue_t *pq)
{
  return pq->block_size == (((8 * (1 * (1UL << (13 + 3)))) / 8) + (2 * (sizeof(uintptr_t))));
}


----------------------------
inline static void mi_page_set_in_full(mi_page_t *page, bool in_full)
{
  mi_page_flags_set(page, in_full, 0x01UL);
}


----------------------------
inline static bool mi_page_is_huge(const mi_page_t *page)
{
  return mi_page_is_singleton(page) && ((page->block_size > ((8 * (1 * (1UL << (13 + 3)))) / 8)) || (mi_memkind_is_os(page->memid.memkind) && (page->memid.mem.os.base < ((void *) page))));
}


----------------------------
inline static void mi_heap_queue_first_update(mi_heap_t *heap, const mi_page_queue_t *pq)
{
  (mi_heap_contains_queue(heap, pq)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap,pq)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 199, __func__));
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
  (start <= idx) ? ((void) 0) : (_mi_assert_fail("start <= idx", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 229, __func__));
  for (size_t sz = start; sz <= idx; sz += 1)
  {
    pages_free[sz] = &page[page_idx];
  }

}


----------------------------
void helper_mi_page_queue_enqueue_from_ex_1(mi_page_queue_t * const to, mi_page_t * const page, mi_heap_t * const heap)
{
  if (to->first != 0)
  {
    (heap == mi_page_heap(to->first)) ? ((void) 0) : (_mi_assert_fail("heap == mi_page_heap(to->first)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 380, __func__));
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
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
}


----------------------------
static bool mi_heap_contains_queue(const mi_heap_t *heap, const mi_page_queue_t *pq)
{
  return (pq >= (&heap->pages[0])) && (pq <= (&heap->pages[73U + 1]));
}


----------------------------
inline static bool mi_page_queue_is_huge(const mi_page_queue_t *pq)
{
  return pq->block_size == (((8 * (1 * (1UL << (13 + 3)))) / 8) + (sizeof(uintptr_t)));
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
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 334, __func__));
  (from->count >= 1) ? ((void) 0) : (_mi_assert_fail("from->count >= 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 335, __func__));
  ;
  ;
  const size_t bsize = mi_page_block_size(page);
  (void) bsize;
  ((((((bsize == to->block_size) && (bsize == from->block_size)) || ((bsize == to->block_size) && mi_page_queue_is_full(from))) || ((bsize == from->block_size) && mi_page_queue_is_full(to))) || (mi_page_is_huge(page) && mi_page_queue_is_huge(to))) || (mi_page_is_huge(page) && mi_page_queue_is_full(to))) ? ((void) 0) : (_mi_assert_fail("(bsize == to->block_size && bsize == from->block_size) || (bsize == to->block_size && mi_page_queue_is_full(from)) || (bsize == from->block_size && mi_page_queue_is_full(to)) || (mi_page_is_huge(page) && mi_page_queue_is_huge(to)) || (mi_page_is_huge(page) && mi_page_queue_is_full(to))", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 340, __func__));
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
    (mi_heap_contains_queue(heap, from)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap, from)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 355, __func__));
    mi_heap_queue_first_update(heap, from);
  }
  from->count -= 1;
  to->count += 1;
  if (enqueue_at_end)
  {
    page->prev = to->last;
    page->next = 0;
    if (to->last != 0)
    {
      (heap == mi_page_heap(to->last)) ? ((void) 0) : (_mi_assert_fail("heap == mi_page_heap(to->last)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 367, __func__));
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
None
----------------------------
***/


void _mi_page_unfull(mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 347, __func__));
  ;
  (mi_page_is_in_full(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_in_full(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 349, __func__));
  (!mi_page_heap(page)->allow_page_abandon) ? ((void) 0) : (_mi_assert_fail("!mi_page_heap(page)->allow_page_abandon", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 350, __func__));
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
  return page->heap;
}


----------------------------
inline static void mi_page_set_in_full(mi_page_t *page, bool in_full)
{
  mi_page_flags_set(page, in_full, 0x01UL);
}


----------------------------
static void mi_page_queue_enqueue_from_full(mi_page_queue_t *to, mi_page_queue_t *from, mi_page_t *page)
{
  mi_page_queue_enqueue_from_ex(to, from, 1, page);
}


----------------------------
inline static bool mi_page_is_in_full(const mi_page_t *page)
{
  return (mi_page_flags(page) & 0x01UL) != 0;
}


----------------------------
static mi_page_queue_t *mi_heap_page_queue_of(mi_heap_t *heap, const mi_page_t *page)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 177, __func__));
  const size_t bin = _mi_page_bin(page);
  mi_page_queue_t *pq = &heap->pages[bin];
  (((mi_page_block_size(page) == pq->block_size) || (mi_page_is_huge(page) && mi_page_queue_is_huge(pq))) || (mi_page_is_in_full(page) && mi_page_queue_is_full(pq))) ? ((void) 0) : (_mi_assert_fail("(mi_page_block_size(page) == pq->block_size) || (mi_page_is_huge(page) && mi_page_queue_is_huge(pq)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(pq))", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 180, __func__));
  return pq;
}


----------------------------
None
----------------------------
***/


static void mi_page_thread_collect_to_local(mi_page_t *page, mi_block_t *head)
{
  if (head == 0)
  {
    return;
  }
  size_t max_count = page->capacity;
  size_t count = 1;
  mi_block_t *last = head;
  unsigned int last_idx = 0;
  mi_block_t *next;
  unsigned int next_idx = 0;
  while (((next_idx = mi_block_next(page, last)) != 0) && (count <= max_count))
  {
    count += 1;
    last_idx = &next[next_idx];
  }

  if (count > max_count)
  {
    _mi_error_message(14, "corrupted thread-free list\n");
    return;
  }
  mi_block_set_next(page, last, page->local_free);
  page->local_free = head;
  (count <= UINT16_MAX) ? ((void) 0) : (_mi_assert_fail("count <= UINT16_MAX", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 165, __func__));
  page->used = page->used - ((uint16_t) count);
}


/*** DEPENDENCIES:
None
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
None
----------------------------
***/


static void mi_page_thread_free_collect(mi_page_t *page)
{
  mi_block_t *head;
  unsigned int head_idx = 0;
  mi_thread_free_t tfreex;
  mi_thread_free_t tfree = atomic_load_explicit(&page->xthread_free, memory_order_relaxed);
  do
  {
    head_idx = mi_tf_block(tfree);
    if (__builtin_expect(!(!((&head[head_idx]) == 0)), 1))
    {
      return;
    }
    tfreex = mi_tf_create(0, mi_tf_is_owned(tfree));
  }
  while (!atomic_compare_exchange_weak_explicit(&page->xthread_free, &tfree, tfreex, memory_order_acq_rel, memory_order_acquire));
  ((&head[head_idx]) != 0) ? ((void) 0) : (_mi_assert_fail("head != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 181, __func__));
  mi_page_thread_collect_to_local(page, head);
}


/*** DEPENDENCIES:
None
----------------------------
inline static mi_block_t *mi_tf_block(mi_thread_free_t tf)
{
  return (mi_block_t *) (tf & (~1));
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
static void mi_page_thread_collect_to_local(mi_page_t *page, mi_block_t *head)
{
  if (head == 0)
  {
    return;
  }
  size_t max_count = page->capacity;
  size_t count = 1;
  mi_block_t *last = head;
  unsigned int last_idx = 0;
  mi_block_t *next;
  unsigned int next_idx = 0;
  while (((next_idx = mi_block_next(page, last)) != 0) && (count <= max_count))
  {
    count += 1;
    last_idx = &next[next_idx];
  }

  if (count > max_count)
  {
    _mi_error_message(14, "corrupted thread-free list\n");
    return;
  }
  mi_block_set_next(page, last, page->local_free);
  page->local_free = head;
  (count <= UINT16_MAX) ? ((void) 0) : (_mi_assert_fail("count <= UINT16_MAX", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 165, __func__));
  page->used = page->used - ((uint16_t) count);
}


----------------------------
inline static bool mi_tf_is_owned(mi_thread_free_t tf)
{
  return (tf & 1) == 1;
}


----------------------------
typedef uintptr_t mi_thread_free_t
----------------------------
inline static mi_thread_free_t mi_tf_create(mi_block_t *block, bool owned)
{
  return (mi_thread_free_t) (((uintptr_t) block) | ((owned) ? (1) : (0)));
}


----------------------------
None
----------------------------
***/


void _mi_page_free_collect(mi_page_t *page, bool force)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 188, __func__));
  mi_page_thread_free_collect(page);
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
  ((!force) || (page->local_free == 0)) ? ((void) 0) : (_mi_assert_fail("!force || page->local_free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 215, __func__));
}


/*** DEPENDENCIES:
None
----------------------------
inline static void mi_block_set_next(const mi_page_t *page, mi_block_t *block, const mi_block_t *next)
{
  mi_block_set_nextx(page, block, next, page->keys);
}


----------------------------
static void mi_page_thread_free_collect(mi_page_t *page)
{
  mi_block_t *head;
  unsigned int head_idx = 0;
  mi_thread_free_t tfreex;
  mi_thread_free_t tfree = atomic_load_explicit(&page->xthread_free, memory_order_relaxed);
  do
  {
    head_idx = mi_tf_block(tfree);
    if (__builtin_expect(!(!((&head[head_idx]) == 0)), 1))
    {
      return;
    }
    tfreex = mi_tf_create(0, mi_tf_is_owned(tfree));
  }
  while (!atomic_compare_exchange_weak_explicit(&page->xthread_free, &tfree, tfreex, memory_order_acq_rel, memory_order_acquire));
  ((&head[head_idx]) != 0) ? ((void) 0) : (_mi_assert_fail("head != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 181, __func__));
  mi_page_thread_collect_to_local(page, head);
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
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


void _mi_page_abandon(mi_page_t *page, mi_page_queue_t *pq)
{
  _mi_page_free_collect(page, 0);
  if (mi_page_all_free(page))
  {
    _mi_page_free(page, pq);
  }
  else
  {
    mi_page_queue_remove(pq, page);
    mi_heap_t *heap = page->heap;
    mi_page_set_heap(page, 0);
    page->heap = heap;
    _mi_arenas_page_abandon(page, heap->tld);
    _mi_arenas_collect(0, 0, heap->tld);
  }
}


/*** DEPENDENCIES:
void _mi_arenas_page_abandon(mi_page_t *page, mi_tld_t *tld)
{
  (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 881, __func__));
  (_mi_ptr_page(page) == page) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 882, __func__));
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 883, __func__));
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 884, __func__));
  (!mi_page_all_free(page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_all_free(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 885, __func__));
  ((page->next == 0) && (page->prev == 0)) ? ((void) 0) : (_mi_assert_fail("page->next==NULL && page->prev == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 886, __func__));
  if ((page->memid.memkind == MI_MEM_ARENA) && (!mi_page_is_full(page)))
  {
    helper__mi_arenas_page_abandon_1(page, tld);
  }
  else
  {
    mi_subproc_t *subproc = _mi_subproc();
    if ((page->memid.memkind != MI_MEM_ARENA) && mi_option_is_enabled(mi_option_visit_abandoned))
    {
      for (bool _go = (mi_lock_acquire(&subproc->os_abandoned_pages_lock), 1); _go; mi_lock_release(&subproc->os_abandoned_pages_lock), _go = 0)
      {
        page->prev = 0;
        page->next = subproc->os_abandoned_pages;
        if (page->next != 0)
        {
          page->next->prev = page;
        }
        subproc->os_abandoned_pages = page;
      }

    }
    __mi_stat_increase(&tld->stats.pages_abandoned, 1);
  }
  _mi_page_unown(page);
}


----------------------------
void _mi_page_free(mi_page_t *page, mi_page_queue_t *pq)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 381, __func__));
  ;
  (pq == mi_page_queue_of(page)) ? ((void) 0) : (_mi_assert_fail("pq == mi_page_queue_of(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 383, __func__));
  (mi_page_all_free(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_all_free(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 384, __func__));
  mi_page_set_has_interior_pointers(page, 0);
  mi_page_queue_remove(pq, page);
  mi_tld_t * const tld = page->heap->tld;
  mi_page_set_heap(page, 0);
  _mi_arenas_page_free(page, tld);
  _mi_arenas_collect(0, 0, tld);
}


----------------------------
void _mi_page_free_collect(mi_page_t *page, bool force)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 188, __func__));
  mi_page_thread_free_collect(page);
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
  ((!force) || (page->local_free == 0)) ? ((void) 0) : (_mi_assert_fail("!force || page->local_free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 215, __func__));
}


----------------------------
static void mi_page_queue_remove(mi_page_queue_t *queue, mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 242, __func__));
  ;
  (queue->count >= 1) ? ((void) 0) : (_mi_assert_fail("queue->count >= 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 244, __func__));
  (((mi_page_block_size(page) == queue->block_size) || (mi_page_is_huge(page) && mi_page_queue_is_huge(queue))) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) == queue->block_size || (mi_page_is_huge(page) && mi_page_queue_is_huge(queue)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 245, __func__));
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
    (mi_heap_contains_queue(heap, queue)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap, queue)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 255, __func__));
    mi_heap_queue_first_update(heap, queue);
  }
  heap->page_count -= 1;
  queue->count -= 1;
  page->next = 0;
  page->prev = 0;
  mi_page_set_in_full(page, 0);
}


----------------------------
inline static bool mi_page_all_free(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 714, __func__));
  return page->used == 0;
}


----------------------------
inline static void mi_page_set_heap(mi_page_t *page, mi_heap_t *heap)
{
  if (heap != 0)
  {
    page->heap = heap;
    page->heap_tag = heap->tag;
  }
  else
  {
    page->heap = 0;
  }
  const mi_threadid_t tid = (heap == 0) ? (0UL) : (heap->tld->thread_id);
  ((tid & 0x03UL) == 0) ? ((void) 0) : (_mi_assert_fail("(tid & MI_PAGE_FLAG_MASK) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 816, __func__));
  mi_threadid_t xtid_old = mi_page_xthread_id(page);
  mi_threadid_t xtid;
  do
  {
    xtid = tid | (xtid_old & 0x03UL);
  }
  while (!atomic_compare_exchange_weak_explicit(&page->xthread_id, &xtid_old, xtid, memory_order_release, memory_order_relaxed));
}


----------------------------
void _mi_arenas_collect(bool force_purge, bool visit_all, mi_tld_t *tld)
{
  mi_arenas_try_purge(force_purge, visit_all, tld->subproc, tld->thread_seq);
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
          _mi_page_free(pq->first, pq);
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
void _mi_page_free(mi_page_t *page, mi_page_queue_t *pq)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 381, __func__));
  ;
  (pq == mi_page_queue_of(page)) ? ((void) 0) : (_mi_assert_fail("pq == mi_page_queue_of(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 383, __func__));
  (mi_page_all_free(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_all_free(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 384, __func__));
  mi_page_set_has_interior_pointers(page, 0);
  mi_page_queue_remove(pq, page);
  mi_tld_t * const tld = page->heap->tld;
  mi_page_set_heap(page, 0);
  _mi_arenas_page_free(page, tld);
  _mi_arenas_collect(0, 0, tld);
}


----------------------------
inline static bool mi_page_all_free(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 714, __func__));
  return page->used == 0;
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
static mi_deferred_free_fun * volatile deferred_free = 0
----------------------------
static void * _Atomic deferred_arg
----------------------------
None
----------------------------
***/


void _mi_page_free_collect_partly(mi_page_t *page, mi_block_t *head)
{
  if (head == 0)
  {
    return;
  }
  mi_block_t *next = mi_block_next(page, head);
  if (next != 0)
  {
    mi_block_set_next(page, head, 0);
    mi_page_thread_collect_to_local(page, next);
    if ((page->local_free != 0) && (page->free == 0))
    {
      page->free = page->local_free;
      page->local_free = 0;
      page->free_is_zero = 0;
    }
  }
  if (page->used == 1)
  {
    (mi_tf_block(atomic_load_explicit(&page->xthread_free, memory_order_relaxed)) == head) ? ((void) 0) : (_mi_assert_fail("mi_tf_block(mi_atomic_load_relaxed(&page->xthread_free)) == head", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 238, __func__));
    (mi_block_next(page, head) == 0) ? ((void) 0) : (_mi_assert_fail("mi_block_next(page,head) == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 239, __func__));
    _mi_page_free_collect(page, 0);
  }
}


/*** DEPENDENCIES:
None
----------------------------
inline static void mi_block_set_next(const mi_page_t *page, mi_block_t *block, const mi_block_t *next)
{
  mi_block_set_nextx(page, block, next, page->keys);
}


----------------------------
inline static mi_block_t *mi_tf_block(mi_thread_free_t tf)
{
  return (mi_block_t *) (tf & (~1));
}


----------------------------
void _mi_page_free_collect(mi_page_t *page, bool force)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 188, __func__));
  mi_page_thread_free_collect(page);
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
  ((!force) || (page->local_free == 0)) ? ((void) 0) : (_mi_assert_fail("!force || page->local_free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 215, __func__));
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
static void mi_page_thread_collect_to_local(mi_page_t *page, mi_block_t *head)
{
  if (head == 0)
  {
    return;
  }
  size_t max_count = page->capacity;
  size_t count = 1;
  mi_block_t *last = head;
  unsigned int last_idx = 0;
  mi_block_t *next;
  unsigned int next_idx = 0;
  while (((next_idx = mi_block_next(page, last)) != 0) && (count <= max_count))
  {
    count += 1;
    last_idx = &next[next_idx];
  }

  if (count > max_count)
  {
    _mi_error_message(14, "corrupted thread-free list\n");
    return;
  }
  mi_block_set_next(page, last, page->local_free);
  page->local_free = head;
  (count <= UINT16_MAX) ? ((void) 0) : (_mi_assert_fail("count <= UINT16_MAX", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 165, __func__));
  page->used = page->used - ((uint16_t) count);
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
None
----------------------------
***/


static bool mi_page_queue_contains(mi_page_queue_t *queue, const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 124, __func__));
  mi_page_t *list = queue->first;
  unsigned int list_idx = 0;
  while ((&list[list_idx]) != 0)
  {
    ((list->next == 0) || (list->next->prev == (&list[list_idx]))) ? ((void) 0) : (_mi_assert_fail("list->next == NULL || list->next->prev == list", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 127, __func__));
    ((list->prev == 0) || (list->prev->next == (&list[list_idx]))) ? ((void) 0) : (_mi_assert_fail("list->prev == NULL || list->prev->next == list", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 128, __func__));
    if ((&list[list_idx]) == page)
    {
      break;
    }
    list_idx = list_idx->next;
  }

  return (&list[list_idx]) == page;
}


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
***/


static void mi_page_queue_push_at_end(mi_heap_t *heap, mi_page_queue_t *queue, mi_page_t *page)
{
  (mi_page_heap(page) == heap) ? ((void) 0) : (_mi_assert_fail("mi_page_heap(page) == heap", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 296, __func__));
  (!mi_page_queue_contains(queue, page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_queue_contains(queue, page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 297, __func__));
  (((mi_page_block_size(page) == queue->block_size) || (mi_page_is_huge(page) && mi_page_queue_is_huge(queue))) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) == queue->block_size || (mi_page_is_huge(page) && mi_page_queue_is_huge(queue)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 299, __func__));
  mi_page_set_in_full(page, mi_page_queue_is_full(queue));
  page->prev = queue->last;
  page->next = 0;
  if (queue->last != 0)
  {
    (queue->last->next == 0) ? ((void) 0) : (_mi_assert_fail("queue->last->next == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 308, __func__));
    queue->last->next = page;
    queue->last = page;
  }
  else
  {
    queue->first = (queue->last = page);
  }
  queue->count += 1;
  if (queue->first == page)
  {
    mi_heap_queue_first_update(heap, queue);
  }
  heap->page_count += 1;
}


/*** DEPENDENCIES:
None
----------------------------
static bool mi_page_queue_contains(mi_page_queue_t *queue, const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 124, __func__));
  mi_page_t *list = queue->first;
  unsigned int list_idx = 0;
  while ((&list[list_idx]) != 0)
  {
    ((list->next == 0) || (list->next->prev == (&list[list_idx]))) ? ((void) 0) : (_mi_assert_fail("list->next == NULL || list->next->prev == list", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 127, __func__));
    ((list->prev == 0) || (list->prev->next == (&list[list_idx]))) ? ((void) 0) : (_mi_assert_fail("list->prev == NULL || list->prev->next == list", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 128, __func__));
    if ((&list[list_idx]) == page)
    {
      break;
    }
    list_idx = list_idx->next;
  }

  return (&list[list_idx]) == page;
}


----------------------------
inline static mi_heap_t *mi_page_heap(const mi_page_t *page)
{
  return page->heap;
}


----------------------------
inline static bool mi_page_queue_is_full(const mi_page_queue_t *pq)
{
  return pq->block_size == (((8 * (1 * (1UL << (13 + 3)))) / 8) + (2 * (sizeof(uintptr_t))));
}


----------------------------
inline static void mi_page_set_in_full(mi_page_t *page, bool in_full)
{
  mi_page_flags_set(page, in_full, 0x01UL);
}


----------------------------
inline static bool mi_page_is_huge(const mi_page_t *page)
{
  return mi_page_is_singleton(page) && ((page->block_size > ((8 * (1 * (1UL << (13 + 3)))) / 8)) || (mi_memkind_is_os(page->memid.memkind) && (page->memid.mem.os.base < ((void *) page))));
}


----------------------------
inline static void mi_heap_queue_first_update(mi_heap_t *heap, const mi_page_queue_t *pq)
{
  (mi_heap_contains_queue(heap, pq)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap,pq)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 199, __func__));
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
  (start <= idx) ? ((void) 0) : (_mi_assert_fail("start <= idx", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 229, __func__));
  for (size_t sz = start; sz <= idx; sz += 1)
  {
    pages_free[sz] = &page[page_idx];
  }

}


----------------------------
inline static bool mi_page_is_in_full(const mi_page_t *page)
{
  return (mi_page_flags(page) & 0x01UL) != 0;
}


----------------------------
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
}


----------------------------
inline static bool mi_page_queue_is_huge(const mi_page_queue_t *pq)
{
  return pq->block_size == (((8 * (1 * (1UL << (13 + 3)))) / 8) + (sizeof(uintptr_t)));
}


----------------------------
None
----------------------------
***/


void _mi_heap_page_reclaim(mi_heap_t *heap, mi_page_t *page)
{
  (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 270, __func__));
  (_mi_ptr_page(page) == page) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 271, __func__));
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 272, __func__));
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 273, __func__));
  mi_page_set_heap(page, heap);
  _mi_page_free_collect(page, 0);
  mi_page_queue_t *pq = mi_heap_page_queue_of(heap, page);
  mi_page_queue_push_at_end(heap, pq, page);
  ;
}


/*** DEPENDENCIES:
None
----------------------------
inline static bool mi_page_is_owned(const mi_page_t *page)
{
  return mi_tf_is_owned(atomic_load_explicit(&((mi_page_t *) page)->xthread_free, memory_order_relaxed));
}


----------------------------
inline static mi_page_t *_mi_ptr_page(const void *p)
{
  ((p == 0) || mi_is_in_heap_region(p)) ? ((void) 0) : (_mi_assert_fail("p==NULL || mi_is_in_heap_region(p)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 638, __func__));
  return _mi_checked_ptr_page(p);
}


----------------------------
void _mi_page_free_collect(mi_page_t *page, bool force)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 188, __func__));
  mi_page_thread_free_collect(page);
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
  ((!force) || (page->local_free == 0)) ? ((void) 0) : (_mi_assert_fail("!force || page->local_free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 215, __func__));
}


----------------------------
inline static void mi_page_set_heap(mi_page_t *page, mi_heap_t *heap)
{
  if (heap != 0)
  {
    page->heap = heap;
    page->heap_tag = heap->tag;
  }
  else
  {
    page->heap = 0;
  }
  const mi_threadid_t tid = (heap == 0) ? (0UL) : (heap->tld->thread_id);
  ((tid & 0x03UL) == 0) ? ((void) 0) : (_mi_assert_fail("(tid & MI_PAGE_FLAG_MASK) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 816, __func__));
  mi_threadid_t xtid_old = mi_page_xthread_id(page);
  mi_threadid_t xtid;
  do
  {
    xtid = tid | (xtid_old & 0x03UL);
  }
  while (!atomic_compare_exchange_weak_explicit(&page->xthread_id, &xtid_old, xtid, memory_order_release, memory_order_relaxed));
}


----------------------------
inline static bool _mi_is_aligned(void *p, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 423, __func__));
  return (((uintptr_t) p) % alignment) == 0;
}


----------------------------
static void mi_page_queue_push_at_end(mi_heap_t *heap, mi_page_queue_t *queue, mi_page_t *page)
{
  (mi_page_heap(page) == heap) ? ((void) 0) : (_mi_assert_fail("mi_page_heap(page) == heap", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 296, __func__));
  (!mi_page_queue_contains(queue, page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_queue_contains(queue, page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 297, __func__));
  (((mi_page_block_size(page) == queue->block_size) || (mi_page_is_huge(page) && mi_page_queue_is_huge(queue))) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) == queue->block_size || (mi_page_is_huge(page) && mi_page_queue_is_huge(queue)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 299, __func__));
  mi_page_set_in_full(page, mi_page_queue_is_full(queue));
  page->prev = queue->last;
  page->next = 0;
  if (queue->last != 0)
  {
    (queue->last->next == 0) ? ((void) 0) : (_mi_assert_fail("queue->last->next == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 308, __func__));
    queue->last->next = page;
    queue->last = page;
  }
  else
  {
    queue->first = (queue->last = page);
  }
  queue->count += 1;
  if (queue->first == page)
  {
    mi_heap_queue_first_update(heap, queue);
  }
  heap->page_count += 1;
}


----------------------------
static mi_page_queue_t *mi_heap_page_queue_of(mi_heap_t *heap, const mi_page_t *page)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 177, __func__));
  const size_t bin = _mi_page_bin(page);
  mi_page_queue_t *pq = &heap->pages[bin];
  (((mi_page_block_size(page) == pq->block_size) || (mi_page_is_huge(page) && mi_page_queue_is_huge(pq))) || (mi_page_is_in_full(page) && mi_page_queue_is_full(pq))) ? ((void) 0) : (_mi_assert_fail("(mi_page_block_size(page) == pq->block_size) || (mi_page_is_huge(page) && mi_page_queue_is_huge(pq)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(pq))", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 180, __func__));
  return pq;
}


----------------------------
inline static bool mi_page_is_abandoned(const mi_page_t *page)
{
  return mi_page_thread_id(page) <= (0x03UL + 1);
}


----------------------------
None
----------------------------
***/


inline static mi_block_t *mi_page_block_at(const mi_page_t *page, void *page_start, size_t block_size, size_t i)
{
  (void) page;
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 34, __func__));
  (i <= page->reserved) ? ((void) 0) : (_mi_assert_fail("i <= page->reserved", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 35, __func__));
  return (mi_block_t *) (((uint8_t *) page_start) + (i * block_size));
}


/*** DEPENDENCIES:
None
----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
None
----------------------------
***/


static void mi_page_free_list_extend(mi_page_t * const page, const size_t bsize, const size_t extend, mi_stats_t * const stats)
{
  (void) stats;
  (page->free == 0) ? ((void) 0) : (_mi_assert_fail("page->free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 570, __func__));
  (page->local_free == 0) ? ((void) 0) : (_mi_assert_fail("page->local_free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 571, __func__));
  ((page->capacity + extend) <= page->reserved) ? ((void) 0) : (_mi_assert_fail("page->capacity + extend <= page->reserved", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 573, __func__));
  (bsize == mi_page_block_size(page)) ? ((void) 0) : (_mi_assert_fail("bsize == mi_page_block_size(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 574, __func__));
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
None
----------------------------
inline static void mi_block_set_next(const mi_page_t *page, mi_block_t *block, const mi_block_t *next)
{
  mi_block_set_nextx(page, block, next, page->keys);
}


----------------------------
inline static uint8_t *mi_page_start(const mi_page_t *page)
{
  return page->page_start;
}


----------------------------
inline static mi_block_t *mi_page_block_at(const mi_page_t *page, void *page_start, size_t block_size, size_t i)
{
  (void) page;
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 34, __func__));
  (i <= page->reserved) ? ((void) 0) : (_mi_assert_fail("i <= page->reserved", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 35, __func__));
  return (mi_block_t *) (((uint8_t *) page_start) + (i * block_size));
}


----------------------------
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
  mi_stat_count_t chunk_bins[MI_CBIN_COUNT];
} mi_stats_t
----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
}


----------------------------
None
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
None
----------------------------
***/


static void mi_page_free_list_extend_secure(mi_heap_t * const heap, mi_page_t * const page, const size_t bsize, const size_t extend, mi_stats_t * const stats)
{
  (void) stats;
  (page->free == 0) ? ((void) 0) : (_mi_assert_fail("page->free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 512, __func__));
  (page->local_free == 0) ? ((void) 0) : (_mi_assert_fail("page->local_free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 513, __func__));
  ((page->capacity + extend) <= page->reserved) ? ((void) 0) : (_mi_assert_fail("page->capacity + extend <= page->reserved", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 515, __func__));
  (bsize == mi_page_block_size(page)) ? ((void) 0) : (_mi_assert_fail("bsize == mi_page_block_size(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 516, __func__));
  void * const page_area = mi_page_start(page);
  size_t shift = 6;
  while ((extend >> shift) == 0)
  {
    shift -= 1;
  }

  const size_t slice_count = ((size_t) 1U) << shift;
  const size_t slice_extend = extend / slice_count;
  (slice_extend >= 1) ? ((void) 0) : (_mi_assert_fail("slice_extend >= 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 527, __func__));
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
None
----------------------------
inline static void mi_block_set_next(const mi_page_t *page, mi_block_t *block, const mi_block_t *next)
{
  mi_block_set_nextx(page, block, next, page->keys);
}


----------------------------
inline static uint8_t *mi_page_start(const mi_page_t *page)
{
  return page->page_start;
}


----------------------------
inline static mi_block_t *mi_page_block_at(const mi_page_t *page, void *page_start, size_t block_size, size_t i)
{
  (void) page;
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 34, __func__));
  (i <= page->reserved) ? ((void) 0) : (_mi_assert_fail("i <= page->reserved", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 35, __func__));
  return (mi_block_t *) (((uint8_t *) page_start) + (i * block_size));
}


----------------------------
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
  mi_stat_count_t chunk_bins[MI_CBIN_COUNT];
} mi_stats_t
----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
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
uintptr_t _mi_heap_random_next(mi_heap_t *heap)
{
  return _mi_random_next(&heap->random);
}


----------------------------
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
}


----------------------------
None
----------------------------
***/


static bool mi_page_extend_free(mi_heap_t *heap, mi_page_t *page)
{
  ;
  (page->free == 0) ? ((void) 0) : (_mi_assert_fail("page->free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 611, __func__));
  (page->local_free == 0) ? ((void) 0) : (_mi_assert_fail("page->local_free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 612, __func__));
  if (page->free != 0)
  {
    return 1;
  }
  if (page->capacity >= page->reserved)
  {
    return 1;
  }
  size_t page_size;
  mi_page_area(page, &page_size);
  __mi_stat_counter_increase(&heap->tld->stats.pages_extended, 1);
  const size_t bsize = mi_page_block_size(page);
  size_t extend = ((size_t) page->reserved) - page->capacity;
  (extend > 0) ? ((void) 0) : (_mi_assert_fail("extend > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 627, __func__));
  size_t max_extend = (bsize >= (4 * 1024)) ? (1) : ((4 * 1024) / bsize);
  if (max_extend < 1)
  {
    max_extend = 1;
  }
  (max_extend > 0) ? ((void) 0) : (_mi_assert_fail("max_extend > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 631, __func__));
  if (extend > max_extend)
  {
    extend = max_extend;
  }
  ((extend > 0) && ((extend + page->capacity) <= page->reserved)) ? ((void) 0) : (_mi_assert_fail("extend > 0 && extend + page->capacity <= page->reserved", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 639, __func__));
  (extend < (1UL << 16)) ? ((void) 0) : (_mi_assert_fail("extend < (1UL<<16)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 640, __func__));
  if (page->slice_committed > 0)
  {
    const size_t needed_size = (page->capacity + extend) * bsize;
    const size_t needed_commit = _mi_align_up(mi_page_slice_offset_of(page, needed_size), 1UL << (13 + 3));
    if (needed_commit > page->slice_committed)
    {
      (((needed_commit - page->slice_committed) % _mi_os_page_size()) == 0) ? ((void) 0) : (_mi_assert_fail("((needed_commit - page->slice_committed) % _mi_os_page_size()) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 647, __func__));
      if (!_mi_os_commit(mi_page_slice_start(page) + page->slice_committed, needed_commit - page->slice_committed, 0))
      {
        return 0;
      }
      page->slice_committed = needed_commit;
    }
  }
  if ((extend < 2) || (0 < 3))
  {
    mi_page_free_list_extend(page, bsize, extend, &heap->tld->stats);
  }
  else
  {
    mi_page_free_list_extend_secure(heap, page, bsize, extend, &heap->tld->stats);
  }
  page->capacity += (uint16_t) extend;
  __mi_stat_increase(&heap->tld->stats.page_committed, extend * bsize);
  ;
  return 1;
}


/*** DEPENDENCIES:
None
----------------------------
size_t _mi_os_page_size(void)
{
  return mi_os_mem_config.page_size;
}


----------------------------
inline static uint8_t *mi_page_slice_start(const mi_page_t *page)
{
  return (uint8_t *) page;
}


----------------------------
void __mi_stat_counter_increase(mi_stat_counter_t *stat, size_t amount)
{
  stat->total += amount;
}


----------------------------
static void mi_page_free_list_extend_secure(mi_heap_t * const heap, mi_page_t * const page, const size_t bsize, const size_t extend, mi_stats_t * const stats)
{
  (void) stats;
  (page->free == 0) ? ((void) 0) : (_mi_assert_fail("page->free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 512, __func__));
  (page->local_free == 0) ? ((void) 0) : (_mi_assert_fail("page->local_free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 513, __func__));
  ((page->capacity + extend) <= page->reserved) ? ((void) 0) : (_mi_assert_fail("page->capacity + extend <= page->reserved", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 515, __func__));
  (bsize == mi_page_block_size(page)) ? ((void) 0) : (_mi_assert_fail("bsize == mi_page_block_size(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 516, __func__));
  void * const page_area = mi_page_start(page);
  size_t shift = 6;
  while ((extend >> shift) == 0)
  {
    shift -= 1;
  }

  const size_t slice_count = ((size_t) 1U) << shift;
  const size_t slice_extend = extend / slice_count;
  (slice_extend >= 1) ? ((void) 0) : (_mi_assert_fail("slice_extend >= 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 527, __func__));
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
void __mi_stat_increase(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_update(stat, (int64_t) amount);
}


----------------------------
static void mi_page_free_list_extend(mi_page_t * const page, const size_t bsize, const size_t extend, mi_stats_t * const stats)
{
  (void) stats;
  (page->free == 0) ? ((void) 0) : (_mi_assert_fail("page->free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 570, __func__));
  (page->local_free == 0) ? ((void) 0) : (_mi_assert_fail("page->local_free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 571, __func__));
  ((page->capacity + extend) <= page->reserved) ? ((void) 0) : (_mi_assert_fail("page->capacity + extend <= page->reserved", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 573, __func__));
  (bsize == mi_page_block_size(page)) ? ((void) 0) : (_mi_assert_fail("bsize == mi_page_block_size(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 574, __func__));
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
bool _mi_os_commit(void *addr, size_t size, bool *is_zero)
{
  return _mi_os_commit_ex(addr, size, is_zero, size);
}


----------------------------
inline static uintptr_t _mi_align_up(uintptr_t sz, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 429, __func__));
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
inline static uint8_t *mi_page_area(const mi_page_t *page, size_t *size)
{
  if (size)
  {
    *size = mi_page_size(page);
  }
  return mi_page_start(page);
}


----------------------------
inline static size_t mi_page_slice_offset_of(const mi_page_t *page, size_t offset_relative_to_page_start)
{
  return (page->page_start - mi_page_slice_start(page)) + offset_relative_to_page_start;
}


----------------------------
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
}


----------------------------
None
----------------------------
***/


bool _mi_page_init(mi_heap_t *heap, mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 673, __func__));
  mi_page_set_heap(page, heap);
  size_t page_size;
  uint8_t *page_start = mi_page_area(page, &page_size);
  (void) page_start;
  ;
  ((page_size / mi_page_block_size(page)) < (1L << 16)) ? ((void) 0) : (_mi_assert_fail("page_size / mi_page_block_size(page) < (1L<<16)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 679, __func__));
  (page->reserved > 0) ? ((void) 0) : (_mi_assert_fail("page->reserved > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 680, __func__));
  page->keys[0] = _mi_heap_random_next(heap);
  page->keys[1] = _mi_heap_random_next(heap);
  (page->capacity == 0) ? ((void) 0) : (_mi_assert_fail("page->capacity == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 692, __func__));
  (page->free == 0) ? ((void) 0) : (_mi_assert_fail("page->free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 693, __func__));
  (page->used == 0) ? ((void) 0) : (_mi_assert_fail("page->used == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 694, __func__));
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 695, __func__));
  (page->xthread_free == 1) ? ((void) 0) : (_mi_assert_fail("page->xthread_free == 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 696, __func__));
  (page->next == 0) ? ((void) 0) : (_mi_assert_fail("page->next == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 697, __func__));
  (page->prev == 0) ? ((void) 0) : (_mi_assert_fail("page->prev == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 698, __func__));
  (page->retire_expire == 0) ? ((void) 0) : (_mi_assert_fail("page->retire_expire == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 699, __func__));
  (!mi_page_has_interior_pointers(page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_has_interior_pointers(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 700, __func__));
  (page->keys[0] != 0) ? ((void) 0) : (_mi_assert_fail("page->keys[0] != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 702, __func__));
  (page->keys[1] != 0) ? ((void) 0) : (_mi_assert_fail("page->keys[1] != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 703, __func__));
  ;
  if (!mi_page_extend_free(heap, page))
  {
    return 0;
  }
  (mi_page_immediate_available(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_immediate_available(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 709, __func__));
  return 1;
}


/*** DEPENDENCIES:
None
----------------------------
inline static bool mi_page_is_owned(const mi_page_t *page)
{
  return mi_tf_is_owned(atomic_load_explicit(&((mi_page_t *) page)->xthread_free, memory_order_relaxed));
}


----------------------------
static bool mi_page_extend_free(mi_heap_t *heap, mi_page_t *page)
{
  ;
  (page->free == 0) ? ((void) 0) : (_mi_assert_fail("page->free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 611, __func__));
  (page->local_free == 0) ? ((void) 0) : (_mi_assert_fail("page->local_free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 612, __func__));
  if (page->free != 0)
  {
    return 1;
  }
  if (page->capacity >= page->reserved)
  {
    return 1;
  }
  size_t page_size;
  mi_page_area(page, &page_size);
  __mi_stat_counter_increase(&heap->tld->stats.pages_extended, 1);
  const size_t bsize = mi_page_block_size(page);
  size_t extend = ((size_t) page->reserved) - page->capacity;
  (extend > 0) ? ((void) 0) : (_mi_assert_fail("extend > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 627, __func__));
  size_t max_extend = (bsize >= (4 * 1024)) ? (1) : ((4 * 1024) / bsize);
  if (max_extend < 1)
  {
    max_extend = 1;
  }
  (max_extend > 0) ? ((void) 0) : (_mi_assert_fail("max_extend > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 631, __func__));
  if (extend > max_extend)
  {
    extend = max_extend;
  }
  ((extend > 0) && ((extend + page->capacity) <= page->reserved)) ? ((void) 0) : (_mi_assert_fail("extend > 0 && extend + page->capacity <= page->reserved", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 639, __func__));
  (extend < (1UL << 16)) ? ((void) 0) : (_mi_assert_fail("extend < (1UL<<16)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 640, __func__));
  if (page->slice_committed > 0)
  {
    const size_t needed_size = (page->capacity + extend) * bsize;
    const size_t needed_commit = _mi_align_up(mi_page_slice_offset_of(page, needed_size), 1UL << (13 + 3));
    if (needed_commit > page->slice_committed)
    {
      (((needed_commit - page->slice_committed) % _mi_os_page_size()) == 0) ? ((void) 0) : (_mi_assert_fail("((needed_commit - page->slice_committed) % _mi_os_page_size()) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 647, __func__));
      if (!_mi_os_commit(mi_page_slice_start(page) + page->slice_committed, needed_commit - page->slice_committed, 0))
      {
        return 0;
      }
      page->slice_committed = needed_commit;
    }
  }
  if ((extend < 2) || (0 < 3))
  {
    mi_page_free_list_extend(page, bsize, extend, &heap->tld->stats);
  }
  else
  {
    mi_page_free_list_extend_secure(heap, page, bsize, extend, &heap->tld->stats);
  }
  page->capacity += (uint16_t) extend;
  __mi_stat_increase(&heap->tld->stats.page_committed, extend * bsize);
  ;
  return 1;
}


----------------------------
inline static bool mi_page_has_interior_pointers(const mi_page_t *page)
{
  return (mi_page_flags(page) & 0x02UL) != 0;
}


----------------------------
inline static bool mi_page_immediate_available(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 720, __func__));
  return page->free != 0;
}


----------------------------
inline static void mi_page_set_heap(mi_page_t *page, mi_heap_t *heap)
{
  if (heap != 0)
  {
    page->heap = heap;
    page->heap_tag = heap->tag;
  }
  else
  {
    page->heap = 0;
  }
  const mi_threadid_t tid = (heap == 0) ? (0UL) : (heap->tld->thread_id);
  ((tid & 0x03UL) == 0) ? ((void) 0) : (_mi_assert_fail("(tid & MI_PAGE_FLAG_MASK) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 816, __func__));
  mi_threadid_t xtid_old = mi_page_xthread_id(page);
  mi_threadid_t xtid;
  do
  {
    xtid = tid | (xtid_old & 0x03UL);
  }
  while (!atomic_compare_exchange_weak_explicit(&page->xthread_id, &xtid_old, xtid, memory_order_release, memory_order_relaxed));
}


----------------------------
inline static uint8_t *mi_page_area(const mi_page_t *page, size_t *size)
{
  if (size)
  {
    *size = mi_page_size(page);
  }
  return mi_page_start(page);
}


----------------------------
uintptr_t _mi_heap_random_next(mi_heap_t *heap)
{
  return _mi_random_next(&heap->random);
}


----------------------------
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
}


----------------------------
None
----------------------------
***/


static void mi_page_queue_push(mi_heap_t *heap, mi_page_queue_t *queue, mi_page_t *page)
{
  (mi_page_heap(page) == heap) ? ((void) 0) : (_mi_assert_fail("mi_page_heap(page) == heap", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 267, __func__));
  (!mi_page_queue_contains(queue, page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_queue_contains(queue, page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 268, __func__));
  (((mi_page_block_size(page) == queue->block_size) || (mi_page_is_huge(page) && mi_page_queue_is_huge(queue))) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) == queue->block_size || (mi_page_is_huge(page) && mi_page_queue_is_huge(queue)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 272, __func__));
  mi_page_set_in_full(page, mi_page_queue_is_full(queue));
  page->next = queue->first;
  page->prev = 0;
  if (queue->first != 0)
  {
    (queue->first->prev == 0) ? ((void) 0) : (_mi_assert_fail("queue->first->prev == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 281, __func__));
    queue->first->prev = page;
    queue->first = page;
  }
  else
  {
    queue->first = (queue->last = page);
  }
  queue->count += 1;
  mi_heap_queue_first_update(heap, queue);
  heap->page_count += 1;
}


/*** DEPENDENCIES:
None
----------------------------
static bool mi_page_queue_contains(mi_page_queue_t *queue, const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 124, __func__));
  mi_page_t *list = queue->first;
  unsigned int list_idx = 0;
  while ((&list[list_idx]) != 0)
  {
    ((list->next == 0) || (list->next->prev == (&list[list_idx]))) ? ((void) 0) : (_mi_assert_fail("list->next == NULL || list->next->prev == list", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 127, __func__));
    ((list->prev == 0) || (list->prev->next == (&list[list_idx]))) ? ((void) 0) : (_mi_assert_fail("list->prev == NULL || list->prev->next == list", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 128, __func__));
    if ((&list[list_idx]) == page)
    {
      break;
    }
    list_idx = list_idx->next;
  }

  return (&list[list_idx]) == page;
}


----------------------------
inline static mi_heap_t *mi_page_heap(const mi_page_t *page)
{
  return page->heap;
}


----------------------------
inline static bool mi_page_queue_is_full(const mi_page_queue_t *pq)
{
  return pq->block_size == (((8 * (1 * (1UL << (13 + 3)))) / 8) + (2 * (sizeof(uintptr_t))));
}


----------------------------
inline static void mi_page_set_in_full(mi_page_t *page, bool in_full)
{
  mi_page_flags_set(page, in_full, 0x01UL);
}


----------------------------
inline static bool mi_page_is_huge(const mi_page_t *page)
{
  return mi_page_is_singleton(page) && ((page->block_size > ((8 * (1 * (1UL << (13 + 3)))) / 8)) || (mi_memkind_is_os(page->memid.memkind) && (page->memid.mem.os.base < ((void *) page))));
}


----------------------------
inline static void mi_heap_queue_first_update(mi_heap_t *heap, const mi_page_queue_t *pq)
{
  (mi_heap_contains_queue(heap, pq)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap,pq)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 199, __func__));
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
  (start <= idx) ? ((void) 0) : (_mi_assert_fail("start <= idx", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 229, __func__));
  for (size_t sz = start; sz <= idx; sz += 1)
  {
    pages_free[sz] = &page[page_idx];
  }

}


----------------------------
inline static bool mi_page_is_in_full(const mi_page_t *page)
{
  return (mi_page_flags(page) & 0x01UL) != 0;
}


----------------------------
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
}


----------------------------
inline static bool mi_page_queue_is_huge(const mi_page_queue_t *pq)
{
  return pq->block_size == (((8 * (1 * (1UL << (13 + 3)))) / 8) + (sizeof(uintptr_t)));
}


----------------------------
None
----------------------------
***/


static mi_page_t *mi_page_fresh_alloc(mi_heap_t *heap, mi_page_queue_t *pq, size_t block_size, size_t page_alignment)
{
  (pq != 0) ? ((void) 0) : (_mi_assert_fail("pq != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 301, __func__));
  (mi_heap_contains_queue(heap, pq)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap, pq)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 302, __func__));
  (((page_alignment > 0) || (block_size > ((8 * (1 * (1UL << (13 + 3)))) / 8))) || (block_size == pq->block_size)) ? ((void) 0) : (_mi_assert_fail("page_alignment > 0 || block_size > MI_LARGE_MAX_OBJ_SIZE || block_size == pq->block_size", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 303, __func__));
  mi_page_t *page = _mi_arenas_page_alloc(heap, block_size, page_alignment);
  if (page == 0)
  {
    return 0;
  }
  if (mi_page_is_abandoned(page))
  {
    _mi_heap_page_reclaim(heap, page);
    if (!mi_page_immediate_available(page))
    {
      if (mi_page_is_expandable(page))
      {
        mi_page_extend_free(heap, page);
      }
      else
      {
        (0) ? ((void) 0) : (_mi_assert_fail("false", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 317, __func__));
        return 0;
      }
    }
  }
  else
    if (pq != 0)
  {
    mi_page_queue_push(heap, pq, page);
  }
  ((pq != 0) || (mi_page_block_size(page) >= block_size)) ? ((void) 0) : (_mi_assert_fail("pq!=NULL || mi_page_block_size(page) >= block_size", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 325, __func__));
  ;
  return page;
}


/*** DEPENDENCIES:
None
----------------------------
void _mi_heap_page_reclaim(mi_heap_t *heap, mi_page_t *page)
{
  (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 270, __func__));
  (_mi_ptr_page(page) == page) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 271, __func__));
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 272, __func__));
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 273, __func__));
  mi_page_set_heap(page, heap);
  _mi_page_free_collect(page, 0);
  mi_page_queue_t *pq = mi_heap_page_queue_of(heap, page);
  mi_page_queue_push_at_end(heap, pq, page);
  ;
}


----------------------------
inline static bool mi_page_is_expandable(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 727, __func__));
  (page->capacity <= page->reserved) ? ((void) 0) : (_mi_assert_fail("page->capacity <= page->reserved", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 728, __func__));
  return page->capacity < page->reserved;
}


----------------------------
static bool mi_page_extend_free(mi_heap_t *heap, mi_page_t *page)
{
  ;
  (page->free == 0) ? ((void) 0) : (_mi_assert_fail("page->free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 611, __func__));
  (page->local_free == 0) ? ((void) 0) : (_mi_assert_fail("page->local_free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 612, __func__));
  if (page->free != 0)
  {
    return 1;
  }
  if (page->capacity >= page->reserved)
  {
    return 1;
  }
  size_t page_size;
  mi_page_area(page, &page_size);
  __mi_stat_counter_increase(&heap->tld->stats.pages_extended, 1);
  const size_t bsize = mi_page_block_size(page);
  size_t extend = ((size_t) page->reserved) - page->capacity;
  (extend > 0) ? ((void) 0) : (_mi_assert_fail("extend > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 627, __func__));
  size_t max_extend = (bsize >= (4 * 1024)) ? (1) : ((4 * 1024) / bsize);
  if (max_extend < 1)
  {
    max_extend = 1;
  }
  (max_extend > 0) ? ((void) 0) : (_mi_assert_fail("max_extend > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 631, __func__));
  if (extend > max_extend)
  {
    extend = max_extend;
  }
  ((extend > 0) && ((extend + page->capacity) <= page->reserved)) ? ((void) 0) : (_mi_assert_fail("extend > 0 && extend + page->capacity <= page->reserved", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 639, __func__));
  (extend < (1UL << 16)) ? ((void) 0) : (_mi_assert_fail("extend < (1UL<<16)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 640, __func__));
  if (page->slice_committed > 0)
  {
    const size_t needed_size = (page->capacity + extend) * bsize;
    const size_t needed_commit = _mi_align_up(mi_page_slice_offset_of(page, needed_size), 1UL << (13 + 3));
    if (needed_commit > page->slice_committed)
    {
      (((needed_commit - page->slice_committed) % _mi_os_page_size()) == 0) ? ((void) 0) : (_mi_assert_fail("((needed_commit - page->slice_committed) % _mi_os_page_size()) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 647, __func__));
      if (!_mi_os_commit(mi_page_slice_start(page) + page->slice_committed, needed_commit - page->slice_committed, 0))
      {
        return 0;
      }
      page->slice_committed = needed_commit;
    }
  }
  if ((extend < 2) || (0 < 3))
  {
    mi_page_free_list_extend(page, bsize, extend, &heap->tld->stats);
  }
  else
  {
    mi_page_free_list_extend_secure(heap, page, bsize, extend, &heap->tld->stats);
  }
  page->capacity += (uint16_t) extend;
  __mi_stat_increase(&heap->tld->stats.page_committed, extend * bsize);
  ;
  return 1;
}


----------------------------
inline static bool mi_page_immediate_available(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 720, __func__));
  return page->free != 0;
}


----------------------------
static void mi_page_queue_push(mi_heap_t *heap, mi_page_queue_t *queue, mi_page_t *page)
{
  (mi_page_heap(page) == heap) ? ((void) 0) : (_mi_assert_fail("mi_page_heap(page) == heap", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 267, __func__));
  (!mi_page_queue_contains(queue, page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_queue_contains(queue, page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 268, __func__));
  (((mi_page_block_size(page) == queue->block_size) || (mi_page_is_huge(page) && mi_page_queue_is_huge(queue))) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) == queue->block_size || (mi_page_is_huge(page) && mi_page_queue_is_huge(queue)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 272, __func__));
  mi_page_set_in_full(page, mi_page_queue_is_full(queue));
  page->next = queue->first;
  page->prev = 0;
  if (queue->first != 0)
  {
    (queue->first->prev == 0) ? ((void) 0) : (_mi_assert_fail("queue->first->prev == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 281, __func__));
    queue->first->prev = page;
    queue->first = page;
  }
  else
  {
    queue->first = (queue->last = page);
  }
  queue->count += 1;
  mi_heap_queue_first_update(heap, queue);
  heap->page_count += 1;
}


----------------------------
mi_page_t *_mi_arenas_page_alloc(mi_heap_t *heap, size_t block_size, size_t block_alignment)
{
  mi_page_t *page;
  unsigned int page_idx = 0;
  if (__builtin_expect(!(!(block_alignment > (1UL << (13 + 3)))), 0))
  {
    (_mi_is_power_of_two(block_alignment)) ? ((void) 0) : (_mi_assert_fail("_mi_is_power_of_two(block_alignment)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 781, __func__));
    page_idx = mi_arenas_page_singleton_alloc(heap, block_size, block_alignment);
  }
  else
    if (block_size <= (((1 * (1UL << (13 + 3))) - ((3 + 2) * 32)) / 8))
  {
    page_idx = mi_arenas_page_regular_alloc(heap, mi_slice_count_of_size(1 * (1UL << (13 + 3))), block_size);
  }
  else
    if (block_size <= ((8 * (1 * (1UL << (13 + 3)))) / 8))
  {
    page_idx = mi_arenas_page_regular_alloc(heap, mi_slice_count_of_size(8 * (1 * (1UL << (13 + 3)))), block_size);
  }
  else
  {
    page_idx = mi_arenas_page_singleton_alloc(heap, block_size, block_alignment);
  }
  (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 799, __func__));
  (_mi_ptr_page(page) == (&page[page_idx])) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 800, __func__));
  (_mi_ptr_page(mi_page_start(page)) == (&page[page_idx])) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(mi_page_start(page))==page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 801, __func__));
  ((block_alignment <= (1UL << (13 + 3))) || _mi_is_aligned(mi_page_start(page), block_alignment)) ? ((void) 0) : (_mi_assert_fail("block_alignment <= MI_PAGE_MAX_OVERALLOC_ALIGN || _mi_is_aligned(mi_page_start(page), block_alignment)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena.c", 802, __func__));
  return page;
}


----------------------------
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
}


----------------------------
static bool mi_heap_contains_queue(const mi_heap_t *heap, const mi_page_queue_t *pq)
{
  return (pq >= (&heap->pages[0])) && (pq <= (&heap->pages[73U + 1]));
}


----------------------------
inline static bool mi_page_is_abandoned(const mi_page_t *page)
{
  return mi_page_thread_id(page) <= (0x03UL + 1);
}


----------------------------
None
----------------------------
***/


static mi_page_t *mi_huge_page_alloc(mi_heap_t *heap, size_t size, size_t page_alignment, mi_page_queue_t *pq)
{
  const size_t block_size = _mi_os_good_alloc_size(size);
  (mi_page_queue_is_huge(pq)) ? ((void) 0) : (_mi_assert_fail("mi_page_queue_is_huge(pq)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 894, __func__));
  mi_page_t *page = mi_page_fresh_alloc(heap, pq, block_size, page_alignment);
  if (page != 0)
  {
    (mi_page_block_size(page) >= size) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) >= size", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 898, __func__));
    (mi_page_immediate_available(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_immediate_available(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 899, __func__));
    (mi_page_is_huge(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_huge(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 900, __func__));
    (mi_page_is_singleton(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_singleton(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 901, __func__));
    __mi_stat_increase(&heap->tld->stats.malloc_huge, mi_page_block_size(page));
    __mi_stat_counter_increase(&heap->tld->stats.malloc_huge_count, 1);
  }
  return page;
}


/*** DEPENDENCIES:
None
----------------------------
static mi_page_t *mi_page_fresh_alloc(mi_heap_t *heap, mi_page_queue_t *pq, size_t block_size, size_t page_alignment)
{
  (pq != 0) ? ((void) 0) : (_mi_assert_fail("pq != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 301, __func__));
  (mi_heap_contains_queue(heap, pq)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap, pq)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 302, __func__));
  (((page_alignment > 0) || (block_size > ((8 * (1 * (1UL << (13 + 3)))) / 8))) || (block_size == pq->block_size)) ? ((void) 0) : (_mi_assert_fail("page_alignment > 0 || block_size > MI_LARGE_MAX_OBJ_SIZE || block_size == pq->block_size", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 303, __func__));
  mi_page_t *page = _mi_arenas_page_alloc(heap, block_size, page_alignment);
  if (page == 0)
  {
    return 0;
  }
  if (mi_page_is_abandoned(page))
  {
    _mi_heap_page_reclaim(heap, page);
    if (!mi_page_immediate_available(page))
    {
      if (mi_page_is_expandable(page))
      {
        mi_page_extend_free(heap, page);
      }
      else
      {
        (0) ? ((void) 0) : (_mi_assert_fail("false", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 317, __func__));
        return 0;
      }
    }
  }
  else
    if (pq != 0)
  {
    mi_page_queue_push(heap, pq, page);
  }
  ((pq != 0) || (mi_page_block_size(page) >= block_size)) ? ((void) 0) : (_mi_assert_fail("pq!=NULL || mi_page_block_size(page) >= block_size", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 325, __func__));
  ;
  return page;
}


----------------------------
void __mi_stat_counter_increase(mi_stat_counter_t *stat, size_t amount)
{
  stat->total += amount;
}


----------------------------
void __mi_stat_increase(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_update(stat, (int64_t) amount);
}


----------------------------
inline static bool mi_page_is_huge(const mi_page_t *page)
{
  return mi_page_is_singleton(page) && ((page->block_size > ((8 * (1 * (1UL << (13 + 3)))) / 8)) || (mi_memkind_is_os(page->memid.memkind) && (page->memid.mem.os.base < ((void *) page))));
}


----------------------------
inline static bool mi_page_is_singleton(const mi_page_t *page)
{
  return page->reserved == 1;
}


----------------------------
inline static bool mi_page_immediate_available(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 720, __func__));
  return page->free != 0;
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
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
}


----------------------------
inline static bool mi_page_queue_is_huge(const mi_page_queue_t *pq)
{
  return pq->block_size == (((8 * (1 * (1UL << (13 + 3)))) / 8) + (sizeof(uintptr_t)));
}


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
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 334, __func__));
  (from->count >= 1) ? ((void) 0) : (_mi_assert_fail("from->count >= 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 335, __func__));
  ;
  ;
  const size_t bsize = mi_page_block_size(page);
  (void) bsize;
  ((((((bsize == to->block_size) && (bsize == from->block_size)) || ((bsize == to->block_size) && mi_page_queue_is_full(from))) || ((bsize == from->block_size) && mi_page_queue_is_full(to))) || (mi_page_is_huge(page) && mi_page_queue_is_huge(to))) || (mi_page_is_huge(page) && mi_page_queue_is_full(to))) ? ((void) 0) : (_mi_assert_fail("(bsize == to->block_size && bsize == from->block_size) || (bsize == to->block_size && mi_page_queue_is_full(from)) || (bsize == from->block_size && mi_page_queue_is_full(to)) || (mi_page_is_huge(page) && mi_page_queue_is_huge(to)) || (mi_page_is_huge(page) && mi_page_queue_is_full(to))", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 340, __func__));
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
    (mi_heap_contains_queue(heap, from)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap, from)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 355, __func__));
    mi_heap_queue_first_update(heap, from);
  }
  from->count -= 1;
  to->count += 1;
  if (enqueue_at_end)
  {
    page->prev = to->last;
    page->next = 0;
    if (to->last != 0)
    {
      (heap == mi_page_heap(to->last)) ? ((void) 0) : (_mi_assert_fail("heap == mi_page_heap(to->last)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 367, __func__));
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
None
----------------------------
***/


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


/*** DEPENDENCIES:
None
----------------------------
inline static mi_heap_t *mi_page_heap(const mi_page_t *page)
{
  return page->heap;
}


----------------------------
static void mi_page_queue_enqueue_from(mi_page_queue_t *to, mi_page_queue_t *from, mi_page_t *page)
{
  mi_page_queue_enqueue_from_ex(to, from, 1, page);
}


----------------------------
void _mi_page_free_collect(mi_page_t *page, bool force)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 188, __func__));
  mi_page_thread_free_collect(page);
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
  ((!force) || (page->local_free == 0)) ? ((void) 0) : (_mi_assert_fail("!force || page->local_free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 215, __func__));
}


----------------------------
inline static bool mi_page_immediate_available(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 720, __func__));
  return page->free != 0;
}


----------------------------
inline static bool mi_page_is_in_full(const mi_page_t *page)
{
  return (mi_page_flags(page) & 0x01UL) != 0;
}


----------------------------
void _mi_page_abandon(mi_page_t *page, mi_page_queue_t *pq)
{
  _mi_page_free_collect(page, 0);
  if (mi_page_all_free(page))
  {
    _mi_page_free(page, pq);
  }
  else
  {
    mi_page_queue_remove(pq, page);
    mi_heap_t *heap = page->heap;
    mi_page_set_heap(page, 0);
    page->heap = heap;
    _mi_arenas_page_abandon(page, heap->tld);
    _mi_arenas_collect(0, 0, heap->tld);
  }
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


// hint:  ['count_ref is a mutable refrence to size_t', 'candidate_limit_ref is a mutable refrence to long', 'page_full_retain_ref is a mutable refrence to long', 'page_candidate_idx_ref is a mutable refrence to unsigned int', 'page_idx_ref is a mutable refrence to unsigned int']
void helper_mi_page_queue_find_free_ex_1(size_t * const count_ref, long * const candidate_limit_ref, long * const page_full_retain_ref, unsigned int * const page_candidate_idx_ref, unsigned int * const page_idx_ref, mi_page_queue_t * const pq, mi_page_t * const page_candidate, mi_page_t * const page)
{
  size_t count = *count_ref;
  long candidate_limit = *candidate_limit_ref;
  long page_full_retain = *page_full_retain_ref;
  unsigned int page_candidate_idx = *page_candidate_idx_ref;
  unsigned int page_idx = *page_idx_ref;
  mi_page_t *next = page->next;
  count += 1;
  candidate_limit -= 1;
  bool immediate_available = mi_page_immediate_available(page);
  if (!immediate_available)
  {
    _mi_page_free_collect(page, 0);
    immediate_available = mi_page_immediate_available(page);
  }
  if ((!immediate_available) && (!mi_page_is_expandable(page)))
  {
    page_full_retain -= 1;
    if (page_full_retain < 0)
    {
      ((!mi_page_is_in_full(page)) && (!mi_page_immediate_available(page))) ? ((void) 0) : (_mi_assert_fail("!mi_page_is_in_full(page) && !mi_page_immediate_available(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 749, __func__));
      mi_page_to_full(page, pq);
    }
  }
  else
  {
    if ((&page_candidate[page_candidate_idx]) == 0)
    {
      page_candidate_idx = &page[page_idx];
      candidate_limit = _mi_option_get_fast(mi_option_page_max_candidates);
    }
    else
      if (mi_page_all_free(page_candidate))
    {
      _mi_page_free(page_candidate, pq);
      page_candidate_idx = &page[page_idx];
    }
    else
      if ((page->used >= page_candidate->used) && (!mi_page_is_mostly_used(page)))
    {
      page_candidate_idx = &page[page_idx];
    }
    if (immediate_available || (candidate_limit <= 0))
    {
      ((&page_candidate[page_candidate_idx]) != 0) ? ((void) 0) : (_mi_assert_fail("page_candidate!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 770, __func__));
      break;
    }
  }
  page_idx = next;
  *count_ref = count;
  *candidate_limit_ref = candidate_limit;
  *page_full_retain_ref = page_full_retain;
  *page_candidate_idx_ref = page_candidate_idx;
  *page_idx_ref = page_idx;
}


/*** DEPENDENCIES:
None
----------------------------
inline static bool mi_page_is_expandable(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 727, __func__));
  (page->capacity <= page->reserved) ? ((void) 0) : (_mi_assert_fail("page->capacity <= page->reserved", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 728, __func__));
  return page->capacity < page->reserved;
}


----------------------------
void _mi_page_free(mi_page_t *page, mi_page_queue_t *pq)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 381, __func__));
  ;
  (pq == mi_page_queue_of(page)) ? ((void) 0) : (_mi_assert_fail("pq == mi_page_queue_of(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 383, __func__));
  (mi_page_all_free(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_all_free(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 384, __func__));
  mi_page_set_has_interior_pointers(page, 0);
  mi_page_queue_remove(pq, page);
  mi_tld_t * const tld = page->heap->tld;
  mi_page_set_heap(page, 0);
  _mi_arenas_page_free(page, tld);
  _mi_arenas_collect(0, 0, tld);
}


----------------------------
void _mi_page_free_collect(mi_page_t *page, bool force)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 188, __func__));
  mi_page_thread_free_collect(page);
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
  ((!force) || (page->local_free == 0)) ? ((void) 0) : (_mi_assert_fail("!force || page->local_free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 215, __func__));
}


----------------------------
long _mi_option_get_fast(mi_option_t option)
{
  ((option >= 0) && (option < _mi_option_last)) ? ((void) 0) : (_mi_assert_fail("option >= 0 && option < _mi_option_last", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/options.c", 249, __func__));
  mi_option_desc_t *desc = &mi_options[option];
  (desc->option == option) ? ((void) 0) : (_mi_assert_fail("desc->option == option", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/options.c", 251, __func__));
  return desc->value;
}


----------------------------
inline static bool mi_page_immediate_available(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 720, __func__));
  return page->free != 0;
}


----------------------------
inline static bool mi_page_all_free(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 714, __func__));
  return page->used == 0;
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
inline static bool mi_page_is_in_full(const mi_page_t *page)
{
  return (mi_page_flags(page) & 0x01UL) != 0;
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
None
----------------------------
***/


static void mi_page_queue_move_to_front(mi_heap_t *heap, mi_page_queue_t *queue, mi_page_t *page)
{
  (mi_page_heap(page) == heap) ? ((void) 0) : (_mi_assert_fail("mi_page_heap(page) == heap", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 325, __func__));
  (mi_page_queue_contains(queue, page)) ? ((void) 0) : (_mi_assert_fail("mi_page_queue_contains(queue, page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 326, __func__));
  if (queue->first == page)
  {
    return;
  }
  mi_page_queue_remove(queue, page);
  mi_page_queue_push(heap, queue, page);
  (queue->first == page) ? ((void) 0) : (_mi_assert_fail("queue->first == page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 330, __func__));
}


/*** DEPENDENCIES:
None
----------------------------
static bool mi_page_queue_contains(mi_page_queue_t *queue, const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 124, __func__));
  mi_page_t *list = queue->first;
  unsigned int list_idx = 0;
  while ((&list[list_idx]) != 0)
  {
    ((list->next == 0) || (list->next->prev == (&list[list_idx]))) ? ((void) 0) : (_mi_assert_fail("list->next == NULL || list->next->prev == list", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 127, __func__));
    ((list->prev == 0) || (list->prev->next == (&list[list_idx]))) ? ((void) 0) : (_mi_assert_fail("list->prev == NULL || list->prev->next == list", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 128, __func__));
    if ((&list[list_idx]) == page)
    {
      break;
    }
    list_idx = list_idx->next;
  }

  return (&list[list_idx]) == page;
}


----------------------------
inline static mi_heap_t *mi_page_heap(const mi_page_t *page)
{
  return page->heap;
}


----------------------------
static void mi_page_queue_remove(mi_page_queue_t *queue, mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 242, __func__));
  ;
  (queue->count >= 1) ? ((void) 0) : (_mi_assert_fail("queue->count >= 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 244, __func__));
  (((mi_page_block_size(page) == queue->block_size) || (mi_page_is_huge(page) && mi_page_queue_is_huge(queue))) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) == queue->block_size || (mi_page_is_huge(page) && mi_page_queue_is_huge(queue)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 245, __func__));
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
    (mi_heap_contains_queue(heap, queue)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap, queue)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 255, __func__));
    mi_heap_queue_first_update(heap, queue);
  }
  heap->page_count -= 1;
  queue->count -= 1;
  page->next = 0;
  page->prev = 0;
  mi_page_set_in_full(page, 0);
}


----------------------------
static void mi_page_queue_push(mi_heap_t *heap, mi_page_queue_t *queue, mi_page_t *page)
{
  (mi_page_heap(page) == heap) ? ((void) 0) : (_mi_assert_fail("mi_page_heap(page) == heap", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 267, __func__));
  (!mi_page_queue_contains(queue, page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_queue_contains(queue, page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 268, __func__));
  (((mi_page_block_size(page) == queue->block_size) || (mi_page_is_huge(page) && mi_page_queue_is_huge(queue))) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) == queue->block_size || (mi_page_is_huge(page) && mi_page_queue_is_huge(queue)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 272, __func__));
  mi_page_set_in_full(page, mi_page_queue_is_full(queue));
  page->next = queue->first;
  page->prev = 0;
  if (queue->first != 0)
  {
    (queue->first->prev == 0) ? ((void) 0) : (_mi_assert_fail("queue->first->prev == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 281, __func__));
    queue->first->prev = page;
    queue->first = page;
  }
  else
  {
    queue->first = (queue->last = page);
  }
  queue->count += 1;
  mi_heap_queue_first_update(heap, queue);
  heap->page_count += 1;
}


----------------------------
None
----------------------------
***/


static mi_page_t *mi_page_fresh(mi_heap_t *heap, mi_page_queue_t *pq)
{
  (mi_heap_contains_queue(heap, pq)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap, pq)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 332, __func__));
  mi_page_t *page = mi_page_fresh_alloc(heap, pq, pq->block_size, 0);
  if (page == 0)
  {
    return 0;
  }
  (pq->block_size == mi_page_block_size(page)) ? ((void) 0) : (_mi_assert_fail("pq->block_size==mi_page_block_size(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 335, __func__));
  (pq == mi_heap_page_queue_of(heap, page)) ? ((void) 0) : (_mi_assert_fail("pq==mi_heap_page_queue_of(heap, page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 336, __func__));
  return page;
}


/*** DEPENDENCIES:
None
----------------------------
static mi_page_t *mi_page_fresh_alloc(mi_heap_t *heap, mi_page_queue_t *pq, size_t block_size, size_t page_alignment)
{
  (pq != 0) ? ((void) 0) : (_mi_assert_fail("pq != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 301, __func__));
  (mi_heap_contains_queue(heap, pq)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap, pq)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 302, __func__));
  (((page_alignment > 0) || (block_size > ((8 * (1 * (1UL << (13 + 3)))) / 8))) || (block_size == pq->block_size)) ? ((void) 0) : (_mi_assert_fail("page_alignment > 0 || block_size > MI_LARGE_MAX_OBJ_SIZE || block_size == pq->block_size", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 303, __func__));
  mi_page_t *page = _mi_arenas_page_alloc(heap, block_size, page_alignment);
  if (page == 0)
  {
    return 0;
  }
  if (mi_page_is_abandoned(page))
  {
    _mi_heap_page_reclaim(heap, page);
    if (!mi_page_immediate_available(page))
    {
      if (mi_page_is_expandable(page))
      {
        mi_page_extend_free(heap, page);
      }
      else
      {
        (0) ? ((void) 0) : (_mi_assert_fail("false", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 317, __func__));
        return 0;
      }
    }
  }
  else
    if (pq != 0)
  {
    mi_page_queue_push(heap, pq, page);
  }
  ((pq != 0) || (mi_page_block_size(page) >= block_size)) ? ((void) 0) : (_mi_assert_fail("pq!=NULL || mi_page_block_size(page) >= block_size", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 325, __func__));
  ;
  return page;
}


----------------------------
static mi_page_queue_t *mi_heap_page_queue_of(mi_heap_t *heap, const mi_page_t *page)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 177, __func__));
  const size_t bin = _mi_page_bin(page);
  mi_page_queue_t *pq = &heap->pages[bin];
  (((mi_page_block_size(page) == pq->block_size) || (mi_page_is_huge(page) && mi_page_queue_is_huge(pq))) || (mi_page_is_in_full(page) && mi_page_queue_is_full(pq))) ? ((void) 0) : (_mi_assert_fail("(mi_page_block_size(page) == pq->block_size) || (mi_page_is_huge(page) && mi_page_queue_is_huge(pq)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(pq))", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 180, __func__));
  return pq;
}


----------------------------
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
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
***/


static mi_page_t *mi_page_queue_find_free_ex(mi_heap_t *heap, mi_page_queue_t *pq, bool first_try)
{
  size_t count = 0;
  long candidate_limit = 0;
  long page_full_retain = (pq->block_size > (((1 * (1UL << (13 + 3))) - ((3 + 2) * 32)) / 8)) ? (0) : (heap->page_full_retain);
  mi_page_t *page_candidate = 0;
  unsigned int page_candidate_idx = 0;
  mi_page_t *page = pq->first;
  unsigned int page_idx = 0;
  while ((&page[page_idx]) != 0)
  {
    helper_mi_page_queue_find_free_ex_1(&count, &candidate_limit, &page_full_retain, &page_candidate_idx, &page_idx, pq, page_candidate, page);
  }

  __mi_stat_counter_increase(&heap->tld->stats.page_searches, count);
  if ((&page_candidate[page_candidate_idx]) != 0)
  {
    page_idx = &page_candidate[page_candidate_idx];
  }
  if ((&page[page_idx]) != 0)
  {
    if (!mi_page_immediate_available(page))
    {
      (mi_page_is_expandable(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_expandable(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 799, __func__));
      if (!mi_page_extend_free(heap, page))
      {
        page_idx = 0;
      }
    }
    (((&page[page_idx]) == 0) || mi_page_immediate_available(page)) ? ((void) 0) : (_mi_assert_fail("page == NULL || mi_page_immediate_available(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 804, __func__));
  }
  if ((&page[page_idx]) == 0)
  {
    _mi_heap_collect_retired(heap, 0);
    page_idx = mi_page_fresh(heap, pq);
    (((&page[page_idx]) == 0) || mi_page_immediate_available(page)) ? ((void) 0) : (_mi_assert_fail("page == NULL || mi_page_immediate_available(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 810, __func__));
    if (((&page[page_idx]) == 0) && first_try)
    {
      page_idx = mi_page_queue_find_free_ex(heap, pq, 0);
      (((&page[page_idx]) == 0) || mi_page_immediate_available(page)) ? ((void) 0) : (_mi_assert_fail("page == NULL || mi_page_immediate_available(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 814, __func__));
    }
  }
  else
  {
    (((&page[page_idx]) == 0) || mi_page_immediate_available(page)) ? ((void) 0) : (_mi_assert_fail("page == NULL || mi_page_immediate_available(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 818, __func__));
    mi_page_queue_move_to_front(heap, pq, page);
    page->retire_expire = 0;
  }
  (((&page[page_idx]) == 0) || mi_page_immediate_available(page)) ? ((void) 0) : (_mi_assert_fail("page == NULL || mi_page_immediate_available(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 824, __func__));
  return page;
}


/*** DEPENDENCIES:
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
          _mi_page_free(pq->first, pq);
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
static mi_page_t *mi_page_fresh(mi_heap_t *heap, mi_page_queue_t *pq)
{
  (mi_heap_contains_queue(heap, pq)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap, pq)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 332, __func__));
  mi_page_t *page = mi_page_fresh_alloc(heap, pq, pq->block_size, 0);
  if (page == 0)
  {
    return 0;
  }
  (pq->block_size == mi_page_block_size(page)) ? ((void) 0) : (_mi_assert_fail("pq->block_size==mi_page_block_size(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 335, __func__));
  (pq == mi_heap_page_queue_of(heap, page)) ? ((void) 0) : (_mi_assert_fail("pq==mi_heap_page_queue_of(heap, page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 336, __func__));
  return page;
}


----------------------------
None
----------------------------
inline static bool mi_page_is_expandable(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 727, __func__));
  (page->capacity <= page->reserved) ? ((void) 0) : (_mi_assert_fail("page->capacity <= page->reserved", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 728, __func__));
  return page->capacity < page->reserved;
}


----------------------------
void __mi_stat_counter_increase(mi_stat_counter_t *stat, size_t amount)
{
  stat->total += amount;
}


----------------------------
static bool mi_page_extend_free(mi_heap_t *heap, mi_page_t *page)
{
  ;
  (page->free == 0) ? ((void) 0) : (_mi_assert_fail("page->free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 611, __func__));
  (page->local_free == 0) ? ((void) 0) : (_mi_assert_fail("page->local_free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 612, __func__));
  if (page->free != 0)
  {
    return 1;
  }
  if (page->capacity >= page->reserved)
  {
    return 1;
  }
  size_t page_size;
  mi_page_area(page, &page_size);
  __mi_stat_counter_increase(&heap->tld->stats.pages_extended, 1);
  const size_t bsize = mi_page_block_size(page);
  size_t extend = ((size_t) page->reserved) - page->capacity;
  (extend > 0) ? ((void) 0) : (_mi_assert_fail("extend > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 627, __func__));
  size_t max_extend = (bsize >= (4 * 1024)) ? (1) : ((4 * 1024) / bsize);
  if (max_extend < 1)
  {
    max_extend = 1;
  }
  (max_extend > 0) ? ((void) 0) : (_mi_assert_fail("max_extend > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 631, __func__));
  if (extend > max_extend)
  {
    extend = max_extend;
  }
  ((extend > 0) && ((extend + page->capacity) <= page->reserved)) ? ((void) 0) : (_mi_assert_fail("extend > 0 && extend + page->capacity <= page->reserved", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 639, __func__));
  (extend < (1UL << 16)) ? ((void) 0) : (_mi_assert_fail("extend < (1UL<<16)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 640, __func__));
  if (page->slice_committed > 0)
  {
    const size_t needed_size = (page->capacity + extend) * bsize;
    const size_t needed_commit = _mi_align_up(mi_page_slice_offset_of(page, needed_size), 1UL << (13 + 3));
    if (needed_commit > page->slice_committed)
    {
      (((needed_commit - page->slice_committed) % _mi_os_page_size()) == 0) ? ((void) 0) : (_mi_assert_fail("((needed_commit - page->slice_committed) % _mi_os_page_size()) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 647, __func__));
      if (!_mi_os_commit(mi_page_slice_start(page) + page->slice_committed, needed_commit - page->slice_committed, 0))
      {
        return 0;
      }
      page->slice_committed = needed_commit;
    }
  }
  if ((extend < 2) || (0 < 3))
  {
    mi_page_free_list_extend(page, bsize, extend, &heap->tld->stats);
  }
  else
  {
    mi_page_free_list_extend_secure(heap, page, bsize, extend, &heap->tld->stats);
  }
  page->capacity += (uint16_t) extend;
  __mi_stat_increase(&heap->tld->stats.page_committed, extend * bsize);
  ;
  return 1;
}


----------------------------
inline static bool mi_page_immediate_available(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 720, __func__));
  return page->free != 0;
}


----------------------------
static void mi_page_queue_move_to_front(mi_heap_t *heap, mi_page_queue_t *queue, mi_page_t *page)
{
  (mi_page_heap(page) == heap) ? ((void) 0) : (_mi_assert_fail("mi_page_heap(page) == heap", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 325, __func__));
  (mi_page_queue_contains(queue, page)) ? ((void) 0) : (_mi_assert_fail("mi_page_queue_contains(queue, page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 326, __func__));
  if (queue->first == page)
  {
    return;
  }
  mi_page_queue_remove(queue, page);
  mi_page_queue_push(heap, queue, page);
  (queue->first == page) ? ((void) 0) : (_mi_assert_fail("queue->first == page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 330, __func__));
}


----------------------------
void helper_mi_page_queue_find_free_ex_1(size_t * const count_ref, long * const candidate_limit_ref, long * const page_full_retain_ref, unsigned int * const page_candidate_idx_ref, unsigned int * const page_idx_ref, mi_page_queue_t * const pq, mi_page_t * const page_candidate, mi_page_t * const page)
{
  size_t count = *count_ref;
  long candidate_limit = *candidate_limit_ref;
  long page_full_retain = *page_full_retain_ref;
  unsigned int page_candidate_idx = *page_candidate_idx_ref;
  unsigned int page_idx = *page_idx_ref;
  mi_page_t *next = page->next;
  count += 1;
  candidate_limit -= 1;
  bool immediate_available = mi_page_immediate_available(page);
  if (!immediate_available)
  {
    _mi_page_free_collect(page, 0);
    immediate_available = mi_page_immediate_available(page);
  }
  if ((!immediate_available) && (!mi_page_is_expandable(page)))
  {
    page_full_retain -= 1;
    if (page_full_retain < 0)
    {
      ((!mi_page_is_in_full(page)) && (!mi_page_immediate_available(page))) ? ((void) 0) : (_mi_assert_fail("!mi_page_is_in_full(page) && !mi_page_immediate_available(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 749, __func__));
      mi_page_to_full(page, pq);
    }
  }
  else
  {
    if ((&page_candidate[page_candidate_idx]) == 0)
    {
      page_candidate_idx = &page[page_idx];
      candidate_limit = _mi_option_get_fast(mi_option_page_max_candidates);
    }
    else
      if (mi_page_all_free(page_candidate))
    {
      _mi_page_free(page_candidate, pq);
      page_candidate_idx = &page[page_idx];
    }
    else
      if ((page->used >= page_candidate->used) && (!mi_page_is_mostly_used(page)))
    {
      page_candidate_idx = &page[page_idx];
    }
    if (immediate_available || (candidate_limit <= 0))
    {
      ((&page_candidate[page_candidate_idx]) != 0) ? ((void) 0) : (_mi_assert_fail("page_candidate!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 770, __func__));
      break;
    }
  }
  page_idx = next;
  *count_ref = count;
  *candidate_limit_ref = candidate_limit;
  *page_full_retain_ref = page_full_retain;
  *page_candidate_idx_ref = page_candidate_idx;
  *page_idx_ref = page_idx;
}


----------------------------
None
----------------------------
***/


static mi_page_t *mi_find_free_page(mi_heap_t *heap, mi_page_queue_t *pq)
{
  (!mi_page_queue_is_huge(pq)) ? ((void) 0) : (_mi_assert_fail("!mi_page_queue_is_huge(pq)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 835, __func__));
  mi_page_t *page = pq->first;
  if (__builtin_expect(!(!((page != 0) && mi_page_immediate_available(page))), 1))
  {
    page->retire_expire = 0;
    return page;
  }
  else
  {
    return mi_page_queue_find_free_ex(heap, pq, 1);
  }
}


/*** DEPENDENCIES:
None
----------------------------
inline static bool mi_page_immediate_available(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 720, __func__));
  return page->free != 0;
}


----------------------------
static mi_page_t *mi_page_queue_find_free_ex(mi_heap_t *heap, mi_page_queue_t *pq, bool first_try)
{
  size_t count = 0;
  long candidate_limit = 0;
  long page_full_retain = (pq->block_size > (((1 * (1UL << (13 + 3))) - ((3 + 2) * 32)) / 8)) ? (0) : (heap->page_full_retain);
  mi_page_t *page_candidate = 0;
  unsigned int page_candidate_idx = 0;
  mi_page_t *page = pq->first;
  unsigned int page_idx = 0;
  while ((&page[page_idx]) != 0)
  {
    helper_mi_page_queue_find_free_ex_1(&count, &candidate_limit, &page_full_retain, &page_candidate_idx, &page_idx, pq, page_candidate, page);
  }

  __mi_stat_counter_increase(&heap->tld->stats.page_searches, count);
  if ((&page_candidate[page_candidate_idx]) != 0)
  {
    page_idx = &page_candidate[page_candidate_idx];
  }
  if ((&page[page_idx]) != 0)
  {
    if (!mi_page_immediate_available(page))
    {
      (mi_page_is_expandable(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_expandable(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 799, __func__));
      if (!mi_page_extend_free(heap, page))
      {
        page_idx = 0;
      }
    }
    (((&page[page_idx]) == 0) || mi_page_immediate_available(page)) ? ((void) 0) : (_mi_assert_fail("page == NULL || mi_page_immediate_available(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 804, __func__));
  }
  if ((&page[page_idx]) == 0)
  {
    _mi_heap_collect_retired(heap, 0);
    page_idx = mi_page_fresh(heap, pq);
    (((&page[page_idx]) == 0) || mi_page_immediate_available(page)) ? ((void) 0) : (_mi_assert_fail("page == NULL || mi_page_immediate_available(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 810, __func__));
    if (((&page[page_idx]) == 0) && first_try)
    {
      page_idx = mi_page_queue_find_free_ex(heap, pq, 0);
      (((&page[page_idx]) == 0) || mi_page_immediate_available(page)) ? ((void) 0) : (_mi_assert_fail("page == NULL || mi_page_immediate_available(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 814, __func__));
    }
  }
  else
  {
    (((&page[page_idx]) == 0) || mi_page_immediate_available(page)) ? ((void) 0) : (_mi_assert_fail("page == NULL || mi_page_immediate_available(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 818, __func__));
    mi_page_queue_move_to_front(heap, pq, page);
    page->retire_expire = 0;
  }
  (((&page[page_idx]) == 0) || mi_page_immediate_available(page)) ? ((void) 0) : (_mi_assert_fail("page == NULL || mi_page_immediate_available(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 824, __func__));
  return page;
}


----------------------------
inline static bool mi_page_queue_is_huge(const mi_page_queue_t *pq)
{
  return pq->block_size == (((8 * (1 * (1UL << (13 + 3)))) / 8) + (sizeof(uintptr_t)));
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
None
----------------------------
inline static mi_page_queue_t *mi_page_queue(const mi_heap_t *heap, size_t size)
{
  mi_page_queue_t * const pq = &((mi_heap_t *) heap)->pages[_mi_bin(size)];
  if (size <= ((8 * (1 * (1UL << (13 + 3)))) / 8))
  {
    (pq->block_size <= ((8 * (1 * (1UL << (13 + 3)))) / 8)) ? ((void) 0) : (_mi_assert_fail("pq->block_size <= MI_LARGE_MAX_OBJ_SIZE", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 762, __func__));
  }
  return pq;
}


----------------------------
static mi_page_t *mi_find_free_page(mi_heap_t *heap, mi_page_queue_t *pq)
{
  (!mi_page_queue_is_huge(pq)) ? ((void) 0) : (_mi_assert_fail("!mi_page_queue_is_huge(pq)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 835, __func__));
  mi_page_t *page = pq->first;
  if (__builtin_expect(!(!((page != 0) && mi_page_immediate_available(page))), 1))
  {
    page->retire_expire = 0;
    return page;
  }
  else
  {
    return mi_page_queue_find_free_ex(heap, pq, 1);
  }
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
inline static bool mi_page_queue_is_huge(const mi_page_queue_t *pq)
{
  return pq->block_size == (((8 * (1 * (1UL << (13 + 3)))) / 8) + (sizeof(uintptr_t)));
}


----------------------------
static mi_page_t *mi_huge_page_alloc(mi_heap_t *heap, size_t size, size_t page_alignment, mi_page_queue_t *pq)
{
  const size_t block_size = _mi_os_good_alloc_size(size);
  (mi_page_queue_is_huge(pq)) ? ((void) 0) : (_mi_assert_fail("mi_page_queue_is_huge(pq)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 894, __func__));
  mi_page_t *page = mi_page_fresh_alloc(heap, pq, block_size, page_alignment);
  if (page != 0)
  {
    (mi_page_block_size(page) >= size) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) >= size", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 898, __func__));
    (mi_page_immediate_available(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_immediate_available(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 899, __func__));
    (mi_page_is_huge(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_huge(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 900, __func__));
    (mi_page_is_singleton(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_singleton(page)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page.c", 901, __func__));
    __mi_stat_increase(&heap->tld->stats.malloc_huge, mi_page_block_size(page));
    __mi_stat_counter_increase(&heap->tld->stats.malloc_huge_count, 1);
  }
  return page;
}


----------------------------
None
----------------------------
***/


inline static size_t mi_page_queue_count(const mi_page_queue_t *pq)
{
  return pq->count;
}


/*** DEPENDENCIES:
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


size_t _mi_page_queue_append(mi_heap_t *heap, mi_page_queue_t *pq, mi_page_queue_t *append)
{
  (mi_heap_contains_queue(heap, pq)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap,pq)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 416, __func__));
  (pq->block_size == append->block_size) ? ((void) 0) : (_mi_assert_fail("pq->block_size == append->block_size", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 417, __func__));
  if (append->first == 0)
  {
    return 0;
  }
  size_t count = 0;
  for (mi_page_t *page = append->first; (&page[page_idx]) != 0; page_idx = page_idx->next)
  {
    mi_page_set_heap(page, heap);
    count += 1;
  }

  unsigned int page_idx = 0;
  (count == append->count) ? ((void) 0) : (_mi_assert_fail("count == append->count", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 427, __func__));
  if (pq->last == 0)
  {
    (pq->first == 0) ? ((void) 0) : (_mi_assert_fail("pq->first==NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 431, __func__));
    pq->first = append->first;
    pq->last = append->last;
    mi_heap_queue_first_update(heap, pq);
  }
  else
  {
    (pq->last != 0) ? ((void) 0) : (_mi_assert_fail("pq->last!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 438, __func__));
    (append->first != 0) ? ((void) 0) : (_mi_assert_fail("append->first!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 439, __func__));
    pq->last->next = append->first;
    append->first->prev = pq->last;
    pq->last = append->last;
  }
  pq->count += append->count;
  return count;
}


/*** DEPENDENCIES:
None
----------------------------
inline static void mi_heap_queue_first_update(mi_heap_t *heap, const mi_page_queue_t *pq)
{
  (mi_heap_contains_queue(heap, pq)) ? ((void) 0) : (_mi_assert_fail("mi_heap_contains_queue(heap,pq)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 199, __func__));
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
  (start <= idx) ? ((void) 0) : (_mi_assert_fail("start <= idx", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 229, __func__));
  for (size_t sz = start; sz <= idx; sz += 1)
  {
    pages_free[sz] = &page[page_idx];
  }

}


----------------------------
inline static void mi_page_set_heap(mi_page_t *page, mi_heap_t *heap)
{
  if (heap != 0)
  {
    page->heap = heap;
    page->heap_tag = heap->tag;
  }
  else
  {
    page->heap = 0;
  }
  const mi_threadid_t tid = (heap == 0) ? (0UL) : (heap->tld->thread_id);
  ((tid & 0x03UL) == 0) ? ((void) 0) : (_mi_assert_fail("(tid & MI_PAGE_FLAG_MASK) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 816, __func__));
  mi_threadid_t xtid_old = mi_page_xthread_id(page);
  mi_threadid_t xtid;
  do
  {
    xtid = tid | (xtid_old & 0x03UL);
  }
  while (!atomic_compare_exchange_weak_explicit(&page->xthread_id, &xtid_old, xtid, memory_order_release, memory_order_relaxed));
}


----------------------------
static bool mi_heap_contains_queue(const mi_heap_t *heap, const mi_page_queue_t *pq)
{
  return (pq >= (&heap->pages[0])) && (pq <= (&heap->pages[73U + 1]));
}


----------------------------
None
----------------------------
***/


bool _mi_page_queue_is_valid(mi_heap_t *heap, const mi_page_queue_t *pq)
{
  ;
  if (pq == 0)
  {
    return 0;
  }
  size_t count = 0;
  ;
  mi_page_t *prev = 0;
  unsigned int prev_idx = 0;
  ;
  for (mi_page_t *page = pq->first; (&page[page_idx]) != 0; page_idx = page_idx->next)
  {
    (page->prev == (&prev[prev_idx])) ? ((void) 0) : (_mi_assert_fail("page->prev == prev", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 149, __func__));
    if (mi_page_is_in_full(page))
    {
      (_mi_wsize_from_size(pq->block_size) == ((((8 * (1 * (1UL << (13 + 3)))) / 8) / (1 << 3)) + 2)) ? ((void) 0) : (_mi_assert_fail("_mi_wsize_from_size(pq->block_size) == MI_LARGE_MAX_OBJ_WSIZE + 2", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 151, __func__));
    }
    else
      if (mi_page_is_huge(page))
    {
      (_mi_wsize_from_size(pq->block_size) == ((((8 * (1 * (1UL << (13 + 3)))) / 8) / (1 << 3)) + 1)) ? ((void) 0) : (_mi_assert_fail("_mi_wsize_from_size(pq->block_size) == MI_LARGE_MAX_OBJ_WSIZE + 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 154, __func__));
    }
    else
    {
      (mi_page_block_size(page) == pq->block_size) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) == pq->block_size", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 157, __func__));
    }
    (page->heap == heap) ? ((void) 0) : (_mi_assert_fail("page->heap == heap", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 159, __func__));
    if (page->next == 0)
    {
      (pq->last == (&page[page_idx])) ? ((void) 0) : (_mi_assert_fail("pq->last == page", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 161, __func__));
    }
    count += 1;
    prev_idx = &page[page_idx];
  }

  unsigned int page_idx = 0;
  (pq->count == count) ? ((void) 0) : (_mi_assert_fail("pq->count == count", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-queue.c", 166, __func__));
  return 1;
}


/*** DEPENDENCIES:
None
----------------------------
inline static bool mi_page_is_huge(const mi_page_t *page)
{
  return mi_page_is_singleton(page) && ((page->block_size > ((8 * (1 * (1UL << (13 + 3)))) / 8)) || (mi_memkind_is_os(page->memid.memkind) && (page->memid.mem.os.base < ((void *) page))));
}


----------------------------
inline static size_t _mi_wsize_from_size(size_t size)
{
  (size <= (SIZE_MAX - (sizeof(uintptr_t)))) ? ((void) 0) : (_mi_assert_fail("size <= SIZE_MAX - sizeof(uintptr_t)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 486, __func__));
  return ((size + (sizeof(uintptr_t))) - 1) / (sizeof(uintptr_t));
}


----------------------------
inline static bool mi_page_is_in_full(const mi_page_t *page)
{
  return (mi_page_flags(page) & 0x01UL) != 0;
}


----------------------------
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
}


----------------------------
None
----------------------------
***/


