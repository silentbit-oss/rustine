uintptr_t _mi_heap_random_next(mi_heap_t *heap)
{
  return _mi_random_next(&heap->random);
}


/*** DEPENDENCIES:
uintptr_t _mi_random_next(mi_random_ctx_t *ctx)
{
  (mi_random_is_initialized(ctx)) ? ((void) 0) : (_mi_assert_fail("mi_random_is_initialized(ctx)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/random.c", 145, __func__));
  uintptr_t r;
  do
  {
    r = (((uintptr_t) chacha_next32(ctx)) << 32) | chacha_next32(ctx);
  }
  while (r == 0);
  return r;
}


----------------------------
None
----------------------------
***/


void _mi_heap_init(mi_heap_t *heap, mi_tld_t *tld, mi_arena_id_t arena_id, bool noreclaim, uint8_t tag)
{
  _mi_memcpy_aligned(heap, &_mi_heap_empty, sizeof(mi_heap_t));
  heap->tld = tld;
  heap->thread_id = _mi_thread_id();
  heap->arena_id = arena_id;
  heap->no_reclaim = noreclaim;
  heap->tag = tag;
  if (heap == tld->heap_backing)
  {
    _mi_random_init(&heap->random);
  }
  else
  {
    _mi_random_split(&tld->heap_backing->random, &heap->random);
  }
  heap->cookie = _mi_heap_random_next(heap) | 1;
  heap->keys[0] = _mi_heap_random_next(heap);
  heap->keys[1] = _mi_heap_random_next(heap);
  _mi_heap_guarded_init(heap);
  heap->next = heap->tld->heaps;
  heap->tld->heaps = heap;
}


/*** DEPENDENCIES:
void _mi_random_init(mi_random_ctx_t *ctx)
{
  mi_random_init_ex(ctx, 0);
}


----------------------------
void _mi_random_split(mi_random_ctx_t *ctx, mi_random_ctx_t *ctx_new)
{
  (mi_random_is_initialized(ctx)) ? ((void) 0) : (_mi_assert_fail("mi_random_is_initialized(ctx)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/random.c", 139, __func__));
  (ctx != ctx_new) ? ((void) 0) : (_mi_assert_fail("ctx != ctx_new", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/random.c", 140, __func__));
  chacha_split(ctx, (uintptr_t) ctx_new, ctx_new);
}


----------------------------
extern const mi_heap_t _mi_heap_empty
----------------------------
typedef int mi_arena_id_t
----------------------------
mi_threadid_t _mi_thread_id(void)
{
  return _mi_prim_thread_id();
}


----------------------------
void _mi_heap_guarded_init(mi_heap_t *heap)
{
  (void) heap;
}


----------------------------
uintptr_t _mi_heap_random_next(mi_heap_t *heap)
{
  return _mi_random_next(&heap->random);
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


static bool mi_heap_visit_pages(mi_heap_t *heap, heap_page_visitor_fun *fn, void *arg1, void *arg2)
{
  if ((heap == 0) || (heap->page_count == 0))
  {
    return 0;
  }
  size_t total = heap->page_count;
  size_t count = 0;
  for (size_t i = 0; i <= (73U + 1); i += 1)
  {
    mi_page_queue_t *pq = &heap->pages[i];
    mi_page_t *page = pq->first;
    unsigned int page_idx = 0;
    while ((&page[page_idx]) != 0)
    {
      mi_page_t *next = page->next;
      (mi_page_heap(page) == heap) ? ((void) 0) : (_mi_assert_fail("mi_page_heap(page) == heap", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 42, __func__));
      count += 1;
      if (!fn(heap, pq, page, arg1, arg2))
      {
        return 0;
      }
      page_idx = next;
    }

  }

  (count == total) ? ((void) 0) : (_mi_assert_fail("count == total", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 50, __func__));
  return 1;
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
typedef bool heap_page_visitor_fun(mi_heap_t *heap, mi_page_queue_t *pq, mi_page_t *page, void *arg1, void *arg2)
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


mi_heap_t *_mi_heap_by_tag(mi_heap_t *heap, uint8_t tag)
{
  if (heap->tag == tag)
  {
    return heap;
  }
  for (mi_heap_t *curr = heap->tld->heaps; (&curr[curr_idx]) != 0; curr_idx = curr_idx->next)
  {
    if (curr->tag == tag)
    {
      return curr;
    }
  }

  unsigned int curr_idx = 0;
  return 0;
}


/*** DEPENDENCIES:
None
----------------------------
***/


static bool mi_heap_page_is_valid(mi_heap_t *heap, mi_page_queue_t *pq, mi_page_t *page, void *arg1, void *arg2)
{
  (void) arg1;
  (void) arg2;
  (void) pq;
  (mi_page_heap(page) == heap) ? ((void) 0) : (_mi_assert_fail("mi_page_heap(page) == heap", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 60, __func__));
  mi_segment_t *segment = _mi_page_segment(page);
  (atomic_load_explicit(&segment->thread_id, memory_order_relaxed) == heap->thread_id) ? ((void) 0) : (_mi_assert_fail("mi_atomic_load_relaxed(&segment->thread_id) == heap->thread_id", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 62, __func__));
  ;
  return 1;
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


static bool mi_heap_page_collect(mi_heap_t *heap, mi_page_queue_t *pq, mi_page_t *page, void *arg_collect, void *arg2)
{
  (void) arg2;
  (void) heap;
  (mi_heap_page_is_valid(heap, pq, page, 0, 0)) ? ((void) 0) : (_mi_assert_fail("mi_heap_page_is_valid(heap, pq, page, NULL, NULL)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 95, __func__));
  mi_collect_t collect = *((mi_collect_t *) arg_collect);
  _mi_page_free_collect(page, collect >= MI_FORCE);
  if (collect == MI_FORCE)
  {
    mi_segment_t *segment = _mi_page_segment(page);
    _mi_segment_collect(segment, 1);
  }
  if (mi_page_all_free(page))
  {
    _mi_page_free(page, pq, collect >= MI_FORCE);
  }
  else
    if (collect == MI_ABANDON)
  {
    _mi_page_abandon(page, pq);
  }
  return 1;
}


/*** DEPENDENCIES:
None
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
inline static mi_segment_t *_mi_page_segment(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 548, __func__));
  mi_segment_t *segment = _mi_ptr_segment(page);
  ((segment == 0) || ((((mi_slice_t *) page) >= segment->slices) && (((mi_slice_t *) page) < (segment->slices + segment->slice_entries)))) ? ((void) 0) : (_mi_assert_fail("segment == NULL || ((mi_slice_t*)page >= segment->slices && (mi_slice_t*)page < segment->slices + segment->slice_entries)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 550, __func__));
  return segment;
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
None
----------------------------
inline static bool mi_page_all_free(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 656, __func__));
  return page->used == 0;
}


----------------------------
typedef enum mi_collect_e
{
  MI_NORMAL,
  MI_FORCE,
  MI_ABANDON
} mi_collect_t
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
void _mi_segment_collect(mi_segment_t *segment, bool force)
{
  mi_segment_try_purge(segment, force);
}


----------------------------
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t block_size;
} mi_page_queue_t
----------------------------
static bool mi_heap_page_is_valid(mi_heap_t *heap, mi_page_queue_t *pq, mi_page_t *page, void *arg1, void *arg2)
{
  (void) arg1;
  (void) arg2;
  (void) pq;
  (mi_page_heap(page) == heap) ? ((void) 0) : (_mi_assert_fail("mi_page_heap(page) == heap", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 60, __func__));
  mi_segment_t *segment = _mi_page_segment(page);
  (atomic_load_explicit(&segment->thread_id, memory_order_relaxed) == heap->thread_id) ? ((void) 0) : (_mi_assert_fail("mi_atomic_load_relaxed(&segment->thread_id) == heap->thread_id", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 62, __func__));
  ;
  return 1;
}


----------------------------
None
----------------------------
***/


static bool mi_heap_page_never_delayed_free(mi_heap_t *heap, mi_page_queue_t *pq, mi_page_t *page, void *arg1, void *arg2)
{
  (void) arg1;
  (void) arg2;
  (void) heap;
  (void) pq;
  _mi_page_use_delayed_free(page, MI_NEVER_DELAYED_FREE, 0);
  return 1;
}


/*** DEPENDENCIES:
void _mi_page_use_delayed_free(mi_page_t *page, mi_delayed_t delay, bool override_never)
{
  while (!_mi_page_try_use_delayed_free(page, delay, override_never))
  {
    mi_atomic_yield();
  }

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


static void mi_heap_reset_pages(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 268, __func__));
  (mi_heap_is_initialized(heap)) ? ((void) 0) : (_mi_assert_fail("mi_heap_is_initialized(heap)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 269, __func__));
  memset(&heap->pages_free_direct, 0, sizeof(heap->pages_free_direct));
  _mi_memcpy_aligned(&heap->pages, &_mi_heap_empty.pages, sizeof(heap->pages));
  heap->thread_delayed_free = 0;
  heap->page_count = 0;
}


/*** DEPENDENCIES:
None
----------------------------
extern const mi_heap_t _mi_heap_empty
----------------------------
inline static bool mi_heap_is_initialized(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 501, __func__));
  return (heap != 0) && (heap != (&_mi_heap_empty));
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


static void mi_heap_absorb(mi_heap_t *heap, mi_heap_t *from)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 434, __func__));
  if ((from == 0) || (from->page_count == 0))
  {
    return;
  }
  _mi_heap_delayed_free_partial(from);
  for (size_t i = 0; i <= (73U + 1); i += 1)
  {
    mi_page_queue_t *pq = &heap->pages[i];
    mi_page_queue_t *append = &from->pages[i];
    size_t pcount = _mi_page_queue_append(heap, pq, append);
    heap->page_count += pcount;
    from->page_count -= pcount;
  }

  (from->page_count == 0) ? ((void) 0) : (_mi_assert_fail("from->page_count == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 451, __func__));
  _mi_heap_delayed_free_all(from);
  (atomic_load_explicit(&from->thread_delayed_free, memory_order_relaxed) == 0) ? ((void) 0) : (_mi_assert_fail("mi_atomic_load_ptr_relaxed(mi_block_t,&from->thread_delayed_free) == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 459, __func__));
  mi_heap_reset_pages(from);
}


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
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


----------------------------
static void mi_heap_reset_pages(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 268, __func__));
  (mi_heap_is_initialized(heap)) ? ((void) 0) : (_mi_assert_fail("mi_heap_is_initialized(heap)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 269, __func__));
  memset(&heap->pages_free_direct, 0, sizeof(heap->pages_free_direct));
  _mi_memcpy_aligned(&heap->pages, &_mi_heap_empty.pages, sizeof(heap->pages));
  heap->thread_delayed_free = 0;
  heap->page_count = 0;
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


static bool mi_heaps_are_compatible(mi_heap_t *heap1, mi_heap_t *heap2)
{
  return (heap1->tag == heap2->tag) && (heap1->arena_id == heap2->arena_id);
}


/*** DEPENDENCIES:
None
----------------------------
***/


static bool mi_heap_is_default(const mi_heap_t *heap)
{
  return heap == mi_prim_get_default_heap();
}


/*** DEPENDENCIES:
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
None
----------------------------
***/


bool _mi_heap_memid_is_suitable(mi_heap_t *heap, mi_memid_t memid)
{
  return _mi_arena_memid_is_suitable(memid, heap->arena_id);
}


/*** DEPENDENCIES:
bool _mi_arena_memid_is_suitable(mi_memid_t memid, mi_arena_id_t request_arena_id)
{
  if (memid.memkind == MI_MEM_ARENA)
  {
    return mi_arena_id_is_suitable(memid.mem.arena.id, memid.mem.arena.is_exclusive, request_arena_id);
  }
  else
  {
    return mi_arena_id_is_suitable(_mi_arena_id_none(), 0, request_arena_id);
  }
}


----------------------------
typedef struct mi_memid_s
{
  union 
  {
    mi_memid_os_info_t os;
    mi_memid_arena_info_t arena;
  } mem;
  bool is_pinned;
  bool initially_committed;
  bool initially_zero;
  mi_memkind_t memkind;
} mi_memid_t
----------------------------
None
----------------------------
***/


void mi_heap_collect(mi_heap_t *heap, bool force)
{
  mi_heap_collect_ex(heap, (force) ? (MI_FORCE) : (MI_NORMAL));
}


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
***/


static size_t mi_fast_divide(size_t n, uint64_t magic, size_t shift)
{
  (n <= UINT32_MAX) ? ((void) 0) : (_mi_assert_fail("n <= UINT32_MAX", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 576, __func__));
  const uint64_t hi = (((uint64_t) n) * magic) >> 32;
  return (size_t) ((hi + n) >> shift);
}


/*** DEPENDENCIES:
None
----------------------------
***/


static bool _mi_heap_page_destroy(mi_heap_t *heap, mi_page_queue_t *pq, mi_page_t *page, void *arg1, void *arg2)
{
  (void) arg1;
  (void) arg2;
  (void) heap;
  (void) pq;
  _mi_page_use_delayed_free(page, MI_NEVER_DELAYED_FREE, 0);
  const size_t bsize = mi_page_block_size(page);
  if (bsize > ((1UL << (3 + (13 + 3))) / 8))
  {
    {
      _mi_stat_decrease(&heap->tld->stats.malloc_huge, bsize);
    }
  }
  _mi_page_free_collect(page, 0);
  const size_t inuse = page->used;
  if (bsize <= ((1UL << (9 + (13 + 3))) / 2))
  {
    _mi_stat_decrease(&heap->tld->stats.malloc_normal, bsize * inuse);
    _mi_stat_decrease(&heap->tld->stats.malloc_bins[_mi_bin(bsize)], inuse);
  }
  (mi_page_thread_free(page) == 0) ? ((void) 0) : (_mi_assert_fail("mi_page_thread_free(page) == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 358, __func__));
  page->used = 0;
  page->next = 0;
  page->prev = 0;
  _mi_segment_page_free(page, 0, &heap->tld->segments);
  return 1;
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
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 591, __func__));
  return page->block_size;
}


----------------------------
None
----------------------------
void _mi_page_use_delayed_free(mi_page_t *page, mi_delayed_t delay, bool override_never)
{
  while (!_mi_page_try_use_delayed_free(page, delay, override_never))
  {
    mi_atomic_yield();
  }

}


----------------------------
inline static mi_block_t *mi_page_thread_free(const mi_page_t *page)
{
  return (mi_block_t *) (atomic_load_explicit(&((mi_page_t *) page)->xthread_free, memory_order_relaxed) & (~3));
}


----------------------------
size_t _mi_bin(size_t size)
{
  return mi_bin(size);
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
void _mi_stat_decrease(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_update(stat, -((int64_t) amount));
}


----------------------------
None
----------------------------
***/


void _mi_heap_destroy_pages(mi_heap_t *heap)
{
  mi_heap_visit_pages(heap, &_mi_heap_page_destroy, 0, 0);
  mi_heap_reset_pages(heap);
}


/*** DEPENDENCIES:
static void mi_heap_reset_pages(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 268, __func__));
  (mi_heap_is_initialized(heap)) ? ((void) 0) : (_mi_assert_fail("mi_heap_is_initialized(heap)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 269, __func__));
  memset(&heap->pages_free_direct, 0, sizeof(heap->pages_free_direct));
  _mi_memcpy_aligned(&heap->pages, &_mi_heap_empty.pages, sizeof(heap->pages));
  heap->thread_delayed_free = 0;
  heap->page_count = 0;
}


----------------------------
static bool mi_heap_visit_pages(mi_heap_t *heap, heap_page_visitor_fun *fn, void *arg1, void *arg2)
{
  if ((heap == 0) || (heap->page_count == 0))
  {
    return 0;
  }
  size_t total = heap->page_count;
  size_t count = 0;
  for (size_t i = 0; i <= (73U + 1); i += 1)
  {
    mi_page_queue_t *pq = &heap->pages[i];
    mi_page_t *page = pq->first;
    unsigned int page_idx = 0;
    while ((&page[page_idx]) != 0)
    {
      mi_page_t *next = page->next;
      (mi_page_heap(page) == heap) ? ((void) 0) : (_mi_assert_fail("mi_page_heap(page) == heap", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 42, __func__));
      count += 1;
      if (!fn(heap, pq, page, arg1, arg2))
      {
        return 0;
      }
      page_idx = next;
    }

  }

  (count == total) ? ((void) 0) : (_mi_assert_fail("count == total", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 50, __func__));
  return 1;
}


----------------------------
static bool _mi_heap_page_destroy(mi_heap_t *heap, mi_page_queue_t *pq, mi_page_t *page, void *arg1, void *arg2)
{
  (void) arg1;
  (void) arg2;
  (void) heap;
  (void) pq;
  _mi_page_use_delayed_free(page, MI_NEVER_DELAYED_FREE, 0);
  const size_t bsize = mi_page_block_size(page);
  if (bsize > ((1UL << (3 + (13 + 3))) / 8))
  {
    {
      _mi_stat_decrease(&heap->tld->stats.malloc_huge, bsize);
    }
  }
  _mi_page_free_collect(page, 0);
  const size_t inuse = page->used;
  if (bsize <= ((1UL << (9 + (13 + 3))) / 2))
  {
    _mi_stat_decrease(&heap->tld->stats.malloc_normal, bsize * inuse);
    _mi_stat_decrease(&heap->tld->stats.malloc_bins[_mi_bin(bsize)], inuse);
  }
  (mi_page_thread_free(page) == 0) ? ((void) 0) : (_mi_assert_fail("mi_page_thread_free(page) == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 358, __func__));
  page->used = 0;
  page->next = 0;
  page->prev = 0;
  _mi_segment_page_free(page, 0, &heap->tld->segments);
  return 1;
}


----------------------------
None
----------------------------
***/


void mi_heap_destroy(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 384, __func__));
  (mi_heap_is_initialized(heap)) ? ((void) 0) : (_mi_assert_fail("mi_heap_is_initialized(heap)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 385, __func__));
  (heap->no_reclaim) ? ((void) 0) : (_mi_assert_fail("heap->no_reclaim", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 386, __func__));
  ;
  if ((heap == 0) || (!mi_heap_is_initialized(heap)))
  {
    return;
  }
  if (!heap->no_reclaim)
  {
    _mi_warning_message("'mi_heap_destroy' called but ignored as the heap was not created with 'allow_destroy' (heap at %p)\n", heap);
    mi_heap_delete(heap);
  }
  else
  {
    _mi_heap_destroy_pages(heap);
    mi_heap_free(heap);
  }
}


/*** DEPENDENCIES:
inline static bool mi_heap_is_initialized(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 501, __func__));
  return (heap != 0) && (heap != (&_mi_heap_empty));
}


----------------------------
None
----------------------------
None
----------------------------
void _mi_heap_destroy_pages(mi_heap_t *heap)
{
  mi_heap_visit_pages(heap, &_mi_heap_page_destroy, 0, 0);
  mi_heap_reset_pages(heap);
}


----------------------------
None
----------------------------
None
----------------------------
***/


void _mi_heap_unsafe_destroy_all(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 413, __func__));
  if (heap == 0)
  {
    return;
  }
  mi_heap_t *curr = heap->tld->heaps;
  unsigned int curr_idx = 0;
  while ((&curr[curr_idx]) != 0)
  {
    mi_heap_t *next = curr->next;
    if (curr->no_reclaim)
    {
      mi_heap_destroy(curr);
    }
    else
    {
      _mi_heap_destroy_pages(curr);
    }
    curr_idx = next;
  }

}


/*** DEPENDENCIES:
None
----------------------------
void mi_heap_destroy(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 384, __func__));
  (mi_heap_is_initialized(heap)) ? ((void) 0) : (_mi_assert_fail("mi_heap_is_initialized(heap)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 385, __func__));
  (heap->no_reclaim) ? ((void) 0) : (_mi_assert_fail("heap->no_reclaim", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 386, __func__));
  ;
  if ((heap == 0) || (!mi_heap_is_initialized(heap)))
  {
    return;
  }
  if (!heap->no_reclaim)
  {
    _mi_warning_message("'mi_heap_destroy' called but ignored as the heap was not created with 'allow_destroy' (heap at %p)\n", heap);
    mi_heap_delete(heap);
  }
  else
  {
    _mi_heap_destroy_pages(heap);
    mi_heap_free(heap);
  }
}


----------------------------
void _mi_heap_destroy_pages(mi_heap_t *heap)
{
  mi_heap_visit_pages(heap, &_mi_heap_page_destroy, 0, 0);
  mi_heap_reset_pages(heap);
}


----------------------------
None
----------------------------
***/


void mi_collect(bool force)
{
  mi_heap_collect(mi_prim_get_default_heap(), force);
}


/*** DEPENDENCIES:
void mi_heap_collect(mi_heap_t *heap, bool force)
{
  mi_heap_collect_ex(heap, (force) ? (MI_FORCE) : (MI_NORMAL));
}


----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
***/


static bool mi_heap_page_check_owned(mi_heap_t *heap, mi_page_queue_t *pq, mi_page_t *page, void *p, void *vfound)
{
  (void) heap;
  (void) pq;
  bool *found = (bool *) vfound;
  void *start = mi_page_start(page);
  void *end = ((uint8_t *) start) + (page->capacity * mi_page_block_size(page));
  *found = (p >= start) && (p < end);
  return !(*found);
}


/*** DEPENDENCIES:
inline static uint8_t *mi_page_start(const mi_page_t *page)
{
  (page->page_start != 0) ? ((void) 0) : (_mi_assert_fail("page->page_start != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 578, __func__));
  ;
  return page->page_start;
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
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 591, __func__));
  return page->block_size;
}


----------------------------
None
----------------------------
***/


bool mi_heap_check_owned(mi_heap_t *heap, const void *p)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 538, __func__));
  if ((heap == 0) || (!mi_heap_is_initialized(heap)))
  {
    return 0;
  }
  if ((((uintptr_t) p) & ((1 << 3) - 1)) != 0)
  {
    return 0;
  }
  bool found = 0;
  mi_heap_visit_pages(heap, &mi_heap_page_check_owned, (void *) p, &found);
  return found;
}


/*** DEPENDENCIES:
static bool mi_heap_page_check_owned(mi_heap_t *heap, mi_page_queue_t *pq, mi_page_t *page, void *p, void *vfound)
{
  (void) heap;
  (void) pq;
  bool *found = (bool *) vfound;
  void *start = mi_page_start(page);
  void *end = ((uint8_t *) start) + (page->capacity * mi_page_block_size(page));
  *found = (p >= start) && (p < end);
  return !(*found);
}


----------------------------
None
----------------------------
inline static bool mi_heap_is_initialized(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 501, __func__));
  return (heap != 0) && (heap != (&_mi_heap_empty));
}


----------------------------
static bool mi_heap_visit_pages(mi_heap_t *heap, heap_page_visitor_fun *fn, void *arg1, void *arg2)
{
  if ((heap == 0) || (heap->page_count == 0))
  {
    return 0;
  }
  size_t total = heap->page_count;
  size_t count = 0;
  for (size_t i = 0; i <= (73U + 1); i += 1)
  {
    mi_page_queue_t *pq = &heap->pages[i];
    mi_page_t *page = pq->first;
    unsigned int page_idx = 0;
    while ((&page[page_idx]) != 0)
    {
      mi_page_t *next = page->next;
      (mi_page_heap(page) == heap) ? ((void) 0) : (_mi_assert_fail("mi_page_heap(page) == heap", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 42, __func__));
      count += 1;
      if (!fn(heap, pq, page, arg1, arg2))
      {
        return 0;
      }
      page_idx = next;
    }

  }

  (count == total) ? ((void) 0) : (_mi_assert_fail("count == total", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 50, __func__));
  return 1;
}


----------------------------
None
----------------------------
***/


bool mi_check_owned(const void *p)
{
  return mi_heap_check_owned(mi_prim_get_default_heap(), p);
}


/*** DEPENDENCIES:
bool mi_heap_check_owned(mi_heap_t *heap, const void *p)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 538, __func__));
  if ((heap == 0) || (!mi_heap_is_initialized(heap)))
  {
    return 0;
  }
  if ((((uintptr_t) p) & ((1 << 3) - 1)) != 0)
  {
    return 0;
  }
  bool found = 0;
  mi_heap_visit_pages(heap, &mi_heap_page_check_owned, (void *) p, &found);
  return found;
}


----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
***/


static void mi_get_fast_divisor(size_t divisor, uint64_t *magic, size_t *shift)
{
  ((divisor > 0) && (divisor <= UINT32_MAX)) ? ((void) 0) : (_mi_assert_fail("divisor > 0 && divisor <= UINT32_MAX", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 570, __func__));
  *shift = ((1 << 3) * 8) - mi_clz(divisor - 1);
  *magic = (((((uint64_t) 1) << 32) * ((((uint64_t) 1) << (*shift)) - divisor)) / divisor) + 1;
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
None
----------------------------
***/


// hint:  ['free_count_ref is a mutable refrence to size_t']
void helper__mi_heap_area_visit_blocks_1(size_t * const free_count_ref, size_t psize, uint8_t * const pstart, const size_t bsize, uint8_t * const block, uintptr_t free_map[((1UL << (13 + 3)) / (sizeof(void *))) / ((1 << 3) * 8)], size_t shift, uint64_t magic, size_t shift, mi_block_t * const block, uint8_t * const block)
{
  size_t free_count = *free_count_ref;
  free_count += 1;
  ((((uint8_t *) block) >= pstart) && (((uint8_t *) block) < (pstart + psize))) ? ((void) 0) : (_mi_assert_fail("(uint8_t*)block >= pstart && (uint8_t*)block < (pstart + psize)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 638, __func__));
  size_t offset = ((uint8_t *) block) - pstart;
  ((offset % bsize) == 0) ? ((void) 0) : (_mi_assert_fail("offset % bsize == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 640, __func__));
  (offset <= UINT32_MAX) ? ((void) 0) : (_mi_assert_fail("offset <= UINT32_MAX", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 641, __func__));
  size_t blockidx = mi_fast_divide(offset, magic, shift);
  (blockidx == (offset / bsize)) ? ((void) 0) : (_mi_assert_fail("blockidx == offset / bsize", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 643, __func__));
  (blockidx < ((1UL << (13 + 3)) / (sizeof(void *)))) ? ((void) 0) : (_mi_assert_fail("blockidx < MI_MAX_BLOCKS", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 644, __func__));
  size_t bitidx = blockidx / ((1 << 3) * 8);
  size_t bit = blockidx - (bitidx * ((1 << 3) * 8));
  free_map[bitidx] |= ((uintptr_t) 1) << bit;
  *free_count_ref = free_count;
}


/*** DEPENDENCIES:
static size_t mi_fast_divide(size_t n, uint64_t magic, size_t shift)
{
  (n <= UINT32_MAX) ? ((void) 0) : (_mi_assert_fail("n <= UINT32_MAX", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 576, __func__));
  const uint64_t hi = (((uint64_t) n) * magic) >> 32;
  return (size_t) ((hi + n) >> shift);
}


----------------------------
None
----------------------------
***/


mi_heap_t *mi_heap_get_backing(void)
{
  mi_heap_t *heap = mi_heap_get_default();
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 211, __func__));
  mi_heap_t *bheap = heap->tld->heap_backing;
  (bheap != 0) ? ((void) 0) : (_mi_assert_fail("bheap!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 213, __func__));
  (bheap->thread_id == _mi_thread_id()) ? ((void) 0) : (_mi_assert_fail("bheap->thread_id == _mi_thread_id()", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 214, __func__));
  return bheap;
}


/*** DEPENDENCIES:
mi_threadid_t _mi_thread_id(void)
{
  return _mi_prim_thread_id();
}


----------------------------
None
----------------------------
None
----------------------------
None
----------------------------
***/


mi_heap_t *mi_heap_new_ex(int heap_tag, bool allow_destroy, mi_arena_id_t arena_id)
{
  mi_heap_t *bheap = mi_heap_get_backing();
  mi_heap_t *heap = (mi_heap_t *) mi_heap_malloc(bheap, sizeof(mi_heap_t));
  if (heap == 0)
  {
    return 0;
  }
  ((heap_tag >= 0) && (heap_tag < 256)) ? ((void) 0) : (_mi_assert_fail("heap_tag >= 0 && heap_tag < 256", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 244, __func__));
  _mi_heap_init(heap, bheap->tld, arena_id, allow_destroy, (uint8_t) heap_tag);
  return heap;
}


/*** DEPENDENCIES:
mi_heap_t *mi_heap_get_backing(void)
{
  mi_heap_t *heap = mi_heap_get_default();
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 211, __func__));
  mi_heap_t *bheap = heap->tld->heap_backing;
  (bheap != 0) ? ((void) 0) : (_mi_assert_fail("bheap!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 213, __func__));
  (bheap->thread_id == _mi_thread_id()) ? ((void) 0) : (_mi_assert_fail("bheap->thread_id == _mi_thread_id()", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 214, __func__));
  return bheap;
}


----------------------------
None
----------------------------
inline extern void *mi_heap_malloc(mi_heap_t *heap, size_t size)
{
  return _mi_heap_malloc_zero(heap, size, 0);
}


----------------------------
typedef int mi_arena_id_t
----------------------------
void _mi_heap_init(mi_heap_t *heap, mi_tld_t *tld, mi_arena_id_t arena_id, bool noreclaim, uint8_t tag)
{
  _mi_memcpy_aligned(heap, &_mi_heap_empty, sizeof(mi_heap_t));
  heap->tld = tld;
  heap->thread_id = _mi_thread_id();
  heap->arena_id = arena_id;
  heap->no_reclaim = noreclaim;
  heap->tag = tag;
  if (heap == tld->heap_backing)
  {
    _mi_random_init(&heap->random);
  }
  else
  {
    _mi_random_split(&tld->heap_backing->random, &heap->random);
  }
  heap->cookie = _mi_heap_random_next(heap) | 1;
  heap->keys[0] = _mi_heap_random_next(heap);
  heap->keys[1] = _mi_heap_random_next(heap);
  _mi_heap_guarded_init(heap);
  heap->next = heap->tld->heaps;
  heap->tld->heaps = heap;
}


----------------------------
None
----------------------------
***/


mi_heap_t *mi_heap_new(void)
{
  return mi_heap_new_ex(0, 1, _mi_arena_id_none());
}


/*** DEPENDENCIES:
mi_arena_id_t _mi_arena_id_none(void)
{
  return 0;
}


----------------------------
mi_heap_t *mi_heap_new_ex(int heap_tag, bool allow_destroy, mi_arena_id_t arena_id)
{
  mi_heap_t *bheap = mi_heap_get_backing();
  mi_heap_t *heap = (mi_heap_t *) mi_heap_malloc(bheap, sizeof(mi_heap_t));
  if (heap == 0)
  {
    return 0;
  }
  ((heap_tag >= 0) && (heap_tag < 256)) ? ((void) 0) : (_mi_assert_fail("heap_tag >= 0 && heap_tag < 256", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 244, __func__));
  _mi_heap_init(heap, bheap->tld, arena_id, allow_destroy, (uint8_t) heap_tag);
  return heap;
}


----------------------------
None
----------------------------
***/


mi_heap_t *mi_heap_new_in_arena(mi_arena_id_t arena_id)
{
  return mi_heap_new_ex(0, 0, arena_id);
}


/*** DEPENDENCIES:
typedef int mi_arena_id_t
----------------------------
mi_heap_t *mi_heap_new_ex(int heap_tag, bool allow_destroy, mi_arena_id_t arena_id)
{
  mi_heap_t *bheap = mi_heap_get_backing();
  mi_heap_t *heap = (mi_heap_t *) mi_heap_malloc(bheap, sizeof(mi_heap_t));
  if (heap == 0)
  {
    return 0;
  }
  ((heap_tag >= 0) && (heap_tag < 256)) ? ((void) 0) : (_mi_assert_fail("heap_tag >= 0 && heap_tag < 256", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 244, __func__));
  _mi_heap_init(heap, bheap->tld, arena_id, allow_destroy, (uint8_t) heap_tag);
  return heap;
}


----------------------------
None
----------------------------
***/


// hint:  ['block_idx_ref is a mutable refrence to unsigned int', 'block_idx_ref is a mutable refrence to unsigned int', 'used_count_ref is a mutable refrence to size_t', 'block_idx_ref is a mutable refrence to unsigned int']
bool helper__mi_heap_area_visit_blocks_2(unsigned int * const block_idx_ref, unsigned int * const block_idx_ref, size_t * const used_count_ref, unsigned int * const block_idx_ref, const mi_heap_area_t * const area, void * const arg, mi_heap_t * const heap, const size_t bsize, const size_t ubsize, uint8_t * const block, size_t i, uintptr_t free_map[((1UL << (13 + 3)) / (sizeof(void *))) / ((1 << 3) * 8)], mi_block_t * const block, uint8_t * const block, size_t i)
{
  unsigned int block_idx = *block_idx_ref;
  unsigned int block_idx = *block_idx_ref;
  size_t used_count = *used_count_ref;
  unsigned int block_idx = *block_idx_ref;
  if (free_map[i] == 0)
  {
    for (size_t j = 0; j < ((1 << 3) * 8); j += 1)
    {
      used_count += 1;
      if (!visitor(heap, area, block, ubsize, arg))
      {
        return 0;
      }
      block_idx += bsize;
    }

  }
  else
  {
    uintptr_t m = ~free_map[i];
    while (m != 0)
    {
      used_count += 1;
      size_t bitidx = mi_ctz(m);
      if (!visitor(heap, area, (&block[block_idx]) + (bitidx * bsize), ubsize, arg))
      {
        return 0;
      }
      m &= m - 1;
    }

    block_idx += bsize * ((1 << 3) * 8);
  }
  *block_idx_ref = block_idx;
  *block_idx_ref = block_idx;
  *used_count_ref = used_count;
  *block_idx_ref = block_idx;
}


/*** DEPENDENCIES:
inline static size_t mi_ctz(size_t x)
{
  if (x == 0)
  {
    return (1 << 3) * 8;
  }
  return __builtin_ctzll(x);
}


----------------------------
typedef struct mi_heap_area_s
{
  void *blocks;
  size_t reserved;
  size_t committed;
  size_t used;
  size_t block_size;
  size_t full_block_size;
  int heap_tag;
} mi_heap_area_t
----------------------------
None
----------------------------
***/


static mi_heap_t *mi_heap_of_block(const void *p)
{
  if (p == 0)
  {
    return 0;
  }
  mi_segment_t *segment = _mi_ptr_segment(p);
  bool valid = _mi_ptr_cookie(segment) == segment->cookie;
  (valid) ? ((void) 0) : (_mi_assert_fail("valid", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 515, __func__));
  if (__builtin_expect(!(!(!valid)), 0))
  {
    return 0;
  }
  return mi_page_heap(_mi_segment_page_of(segment, p));
}


/*** DEPENDENCIES:
None
----------------------------
inline static uintptr_t _mi_ptr_cookie(const void *p)
{
  extern mi_heap_t _mi_heap_main;
  (_mi_heap_main.cookie != 0) ? ((void) 0) : (_mi_assert_fail("_mi_heap_main.cookie != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 507, __func__));
  return ((uintptr_t) p) ^ _mi_heap_main.cookie;
}


----------------------------
inline static mi_segment_t *_mi_ptr_segment(const void *p)
{
  mi_segment_t * const segment = (mi_segment_t *) ((((uintptr_t) p) - 1) & (~((uintptr_t) ((1UL << (9 + (13 + 3))) - 1))));
  return (((intptr_t) segment) <= 0) ? (0) : (segment);
}


----------------------------
None
----------------------------
inline static mi_heap_t *mi_page_heap(const mi_page_t *page)
{
  return (mi_heap_t *) atomic_load_explicit(&((mi_page_t *) page)->xheap, memory_order_relaxed);
}


----------------------------
inline static mi_page_t *_mi_segment_page_of(const mi_segment_t *segment, const void *p)
{
  (p > ((void *) segment)) ? ((void) 0) : (_mi_assert_fail("p > (void*)segment", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 564, __func__));
  ptrdiff_t diff = ((uint8_t *) p) - ((uint8_t *) segment);
  ((diff > 0) && (diff <= ((ptrdiff_t) (1UL << (9 + (13 + 3)))))) ? ((void) 0) : (_mi_assert_fail("diff > 0 && diff <= (ptrdiff_t)MI_SEGMENT_SIZE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 566, __func__));
  size_t idx = ((size_t) diff) >> (13 + 3);
  (idx <= segment->slice_entries) ? ((void) 0) : (_mi_assert_fail("idx <= segment->slice_entries", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 568, __func__));
  mi_slice_t *slice0 = (mi_slice_t *) (&segment->slices[idx]);
  mi_slice_t *slice = mi_slice_first(slice0);
  (slice->slice_offset == 0) ? ((void) 0) : (_mi_assert_fail("slice->slice_offset == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 571, __func__));
  ((slice >= segment->slices) && (slice < (segment->slices + segment->slice_entries))) ? ((void) 0) : (_mi_assert_fail("slice >= segment->slices && slice < segment->slices + segment->slice_entries", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 572, __func__));
  return mi_slice_to_page(slice);
}


----------------------------
None
----------------------------
***/


bool mi_heap_contains_block(mi_heap_t *heap, const void *p)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 521, __func__));
  if ((heap == 0) || (!mi_heap_is_initialized(heap)))
  {
    return 0;
  }
  return heap == mi_heap_of_block(p);
}


/*** DEPENDENCIES:
static mi_heap_t *mi_heap_of_block(const void *p)
{
  if (p == 0)
  {
    return 0;
  }
  mi_segment_t *segment = _mi_ptr_segment(p);
  bool valid = _mi_ptr_cookie(segment) == segment->cookie;
  (valid) ? ((void) 0) : (_mi_assert_fail("valid", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 515, __func__));
  if (__builtin_expect(!(!(!valid)), 0))
  {
    return 0;
  }
  return mi_page_heap(_mi_segment_page_of(segment, p));
}


----------------------------
None
----------------------------
inline static bool mi_heap_is_initialized(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 501, __func__));
  return (heap != 0) && (heap != (&_mi_heap_empty));
}


----------------------------
None
----------------------------
***/


void _mi_heap_area_init(mi_heap_area_t *area, mi_page_t *page)
{
  const size_t bsize = mi_page_block_size(page);
  const size_t ubsize = mi_page_usable_block_size(page);
  area->reserved = page->reserved * bsize;
  area->committed = page->capacity * bsize;
  area->blocks = mi_page_start(page);
  area->used = page->used;
  area->block_size = ubsize;
  area->full_block_size = bsize;
  area->heap_tag = page->heap_tag;
}


/*** DEPENDENCIES:
typedef struct mi_heap_area_s
{
  void *blocks;
  size_t reserved;
  size_t committed;
  size_t used;
  size_t block_size;
  size_t full_block_size;
  int heap_tag;
} mi_heap_area_t
----------------------------
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 591, __func__));
  return page->block_size;
}


----------------------------
inline static uint8_t *mi_page_start(const mi_page_t *page)
{
  (page->page_start != 0) ? ((void) 0) : (_mi_assert_fail("page->page_start != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 578, __func__));
  ;
  return page->page_start;
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
inline static size_t mi_page_usable_block_size(const mi_page_t *page)
{
  return mi_page_block_size(page) - (sizeof(mi_padding_t));
}


----------------------------
***/


static bool mi_heap_visit_areas_page(mi_heap_t *heap, mi_page_queue_t *pq, mi_page_t *page, void *vfun, void *arg)
{
  (void) heap;
  (void) pq;
  mi_heap_area_visit_fun *fun = (mi_heap_area_visit_fun *) vfun;
  mi_heap_area_ex_t xarea;
  xarea.page = page;
  _mi_heap_area_init(&xarea.area, page);
  return fun(heap, &xarea, arg);
}


/*** DEPENDENCIES:
typedef struct mi_heap_area_ex_s
{
  mi_heap_area_t area;
  mi_page_t *page;
} mi_heap_area_ex_t
----------------------------
void _mi_heap_area_init(mi_heap_area_t *area, mi_page_t *page)
{
  const size_t bsize = mi_page_block_size(page);
  const size_t ubsize = mi_page_usable_block_size(page);
  area->reserved = page->reserved * bsize;
  area->committed = page->capacity * bsize;
  area->blocks = mi_page_start(page);
  area->used = page->used;
  area->block_size = ubsize;
  area->full_block_size = bsize;
  area->heap_tag = page->heap_tag;
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
typedef bool mi_heap_area_visit_fun(const mi_heap_t *heap, const mi_heap_area_ex_t *area, void *arg)
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


static bool mi_heap_visit_areas(const mi_heap_t *heap, mi_heap_area_visit_fun *visitor, void *arg)
{
  if (visitor == 0)
  {
    return 0;
  }
  return mi_heap_visit_pages((mi_heap_t *) heap, &mi_heap_visit_areas_page, (void *) visitor, arg);
}


/*** DEPENDENCIES:
typedef bool mi_heap_area_visit_fun(const mi_heap_t *heap, const mi_heap_area_ex_t *area, void *arg)
----------------------------
static bool mi_heap_visit_areas_page(mi_heap_t *heap, mi_page_queue_t *pq, mi_page_t *page, void *vfun, void *arg)
{
  (void) heap;
  (void) pq;
  mi_heap_area_visit_fun *fun = (mi_heap_area_visit_fun *) vfun;
  mi_heap_area_ex_t xarea;
  xarea.page = page;
  _mi_heap_area_init(&xarea.area, page);
  return fun(heap, &xarea, arg);
}


----------------------------
static bool mi_heap_visit_pages(mi_heap_t *heap, heap_page_visitor_fun *fn, void *arg1, void *arg2)
{
  if ((heap == 0) || (heap->page_count == 0))
  {
    return 0;
  }
  size_t total = heap->page_count;
  size_t count = 0;
  for (size_t i = 0; i <= (73U + 1); i += 1)
  {
    mi_page_queue_t *pq = &heap->pages[i];
    mi_page_t *page = pq->first;
    unsigned int page_idx = 0;
    while ((&page[page_idx]) != 0)
    {
      mi_page_t *next = page->next;
      (mi_page_heap(page) == heap) ? ((void) 0) : (_mi_assert_fail("mi_page_heap(page) == heap", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 42, __func__));
      count += 1;
      if (!fn(heap, pq, page, arg1, arg2))
      {
        return 0;
      }
      page_idx = next;
    }

  }

  (count == total) ? ((void) 0) : (_mi_assert_fail("count == total", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 50, __func__));
  return 1;
}


----------------------------
None
----------------------------
***/


bool _mi_heap_area_visit_blocks(const mi_heap_area_t *area, mi_page_t *page, mi_block_visit_fun *visitor, void *arg)
{
  (area != 0) ? ((void) 0) : (_mi_assert_fail("area != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 582, __func__));
  if (area == 0)
  {
    return 1;
  }
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 584, __func__));
  if (page == 0)
  {
    return 1;
  }
  _mi_page_free_collect(page, 1);
  (page->local_free == 0) ? ((void) 0) : (_mi_assert_fail("page->local_free == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 588, __func__));
  if (page->used == 0)
  {
    return 1;
  }
  size_t psize;
  uint8_t * const pstart = _mi_segment_page_start(_mi_page_segment(page), page, &psize);
  mi_heap_t * const heap = mi_page_heap(page);
  const size_t bsize = mi_page_block_size(page);
  const size_t ubsize = mi_page_usable_block_size(page);
  if (page->capacity == 1)
  {
    ((page->used == 1) && (page->free == 0)) ? ((void) 0) : (_mi_assert_fail("page->used == 1 && page->free == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 599, __func__));
    return visitor(mi_page_heap(page), area, pstart, ubsize, arg);
  }
  (bsize <= UINT32_MAX) ? ((void) 0) : (_mi_assert_fail("bsize <= UINT32_MAX", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 602, __func__));
  if (page->used == page->capacity)
  {
    uint8_t *block = pstart;
    unsigned int block_idx = 0;
    for (size_t i = 0; i < page->capacity; i += 1)
    {
      if (!visitor(heap, area, block, ubsize, arg))
      {
        return 0;
      }
      block_idx += bsize;
    }

    return 1;
  }
  uintptr_t free_map[((1UL << (13 + 3)) / (sizeof(void *))) / ((1 << 3) * 8)];
  const uintptr_t bmapsize = _mi_divide_up(page->capacity, (1 << 3) * 8);
  memset(free_map, 0, bmapsize * (sizeof(intptr_t)));
  if ((page->capacity % ((1 << 3) * 8)) != 0)
  {
    size_t shift = page->capacity % ((1 << 3) * 8);
    uintptr_t mask = UINTPTR_MAX << shift;
    free_map[bmapsize - 1] = mask;
  }
  uint64_t magic;
  size_t shift;
  mi_get_fast_divisor(bsize, &magic, &shift);
  size_t free_count = 0;
  for (mi_block_t *block = page->free; (&block[block_idx]) != 0; block_idx = mi_block_next(page, block_idx))
  {
    helper__mi_heap_area_visit_blocks_1(&free_count, psize, pstart, bsize, block, free_map, shift, magic, shift, block, block);
  }

  unsigned int block_idx = 0;
  (page->capacity == (free_count + page->used)) ? ((void) 0) : (_mi_assert_fail("page->capacity == (free_count + page->used)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 649, __func__));
  size_t used_count = 0;
  uint8_t *block = pstart;
  unsigned int block_idx = 0;
  for (size_t i = 0; i < bmapsize; i += 1)
  {
    helper__mi_heap_area_visit_blocks_2(&block_idx, &block_idx, &used_count, &block_idx, area, arg, heap, bsize, ubsize, block, i, free_map, block, block, i);
  }

  (page->used == used_count) ? ((void) 0) : (_mi_assert_fail("page->used == used_count", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 681, __func__));
  return 1;
}


/*** DEPENDENCIES:
inline static uintptr_t _mi_divide_up(uintptr_t size, size_t divider)
{
  (divider != 0) ? ((void) 0) : (_mi_assert_fail("divider != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 421, __func__));
  return (divider == 0) ? (size) : (((size + divider) - 1) / divider);
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
typedef bool mi_block_visit_fun(const mi_heap_t *heap, const mi_heap_area_t *area, void *block, size_t block_size, void *arg)
----------------------------
inline static mi_segment_t *_mi_page_segment(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 548, __func__));
  mi_segment_t *segment = _mi_ptr_segment(page);
  ((segment == 0) || ((((mi_slice_t *) page) >= segment->slices) && (((mi_slice_t *) page) < (segment->slices + segment->slice_entries)))) ? ((void) 0) : (_mi_assert_fail("segment == NULL || ((mi_slice_t*)page >= segment->slices && (mi_slice_t*)page < segment->slices + segment->slice_entries)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 550, __func__));
  return segment;
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
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 591, __func__));
  return page->block_size;
}


----------------------------
None
----------------------------
static void mi_get_fast_divisor(size_t divisor, uint64_t *magic, size_t *shift)
{
  ((divisor > 0) && (divisor <= UINT32_MAX)) ? ((void) 0) : (_mi_assert_fail("divisor > 0 && divisor <= UINT32_MAX", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 570, __func__));
  *shift = ((1 << 3) * 8) - mi_clz(divisor - 1);
  *magic = (((((uint64_t) 1) << 32) * ((((uint64_t) 1) << (*shift)) - divisor)) / divisor) + 1;
}


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
uint8_t *_mi_segment_page_start(const mi_segment_t *segment, const mi_page_t *page, size_t *page_size)
{
  const mi_slice_t *slice = mi_page_to_slice((mi_page_t *) page);
  uint8_t *p = _mi_segment_page_start_from_slice(segment, slice, mi_page_block_size(page), page_size);
  ((mi_page_block_size(page) > 0) || (_mi_ptr_page(p) == page)) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) > 0 || _mi_ptr_page(p) == page", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c", 364, __func__));
  (_mi_ptr_segment(p) == segment) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_segment(p) == segment", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c", 365, __func__));
  return p;
}


----------------------------
void helper__mi_heap_area_visit_blocks_1(size_t * const free_count_ref, size_t psize, uint8_t * const pstart, const size_t bsize, uint8_t * const block, uintptr_t free_map[((1UL << (13 + 3)) / (sizeof(void *))) / ((1 << 3) * 8)], size_t shift, uint64_t magic, size_t shift, mi_block_t * const block, uint8_t * const block)
{
  size_t free_count = *free_count_ref;
  free_count += 1;
  ((((uint8_t *) block) >= pstart) && (((uint8_t *) block) < (pstart + psize))) ? ((void) 0) : (_mi_assert_fail("(uint8_t*)block >= pstart && (uint8_t*)block < (pstart + psize)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 638, __func__));
  size_t offset = ((uint8_t *) block) - pstart;
  ((offset % bsize) == 0) ? ((void) 0) : (_mi_assert_fail("offset % bsize == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 640, __func__));
  (offset <= UINT32_MAX) ? ((void) 0) : (_mi_assert_fail("offset <= UINT32_MAX", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 641, __func__));
  size_t blockidx = mi_fast_divide(offset, magic, shift);
  (blockidx == (offset / bsize)) ? ((void) 0) : (_mi_assert_fail("blockidx == offset / bsize", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 643, __func__));
  (blockidx < ((1UL << (13 + 3)) / (sizeof(void *)))) ? ((void) 0) : (_mi_assert_fail("blockidx < MI_MAX_BLOCKS", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 644, __func__));
  size_t bitidx = blockidx / ((1 << 3) * 8);
  size_t bit = blockidx - (bitidx * ((1 << 3) * 8));
  free_map[bitidx] |= ((uintptr_t) 1) << bit;
  *free_count_ref = free_count;
}


----------------------------
typedef struct mi_heap_area_s
{
  void *blocks;
  size_t reserved;
  size_t committed;
  size_t used;
  size_t block_size;
  size_t full_block_size;
  int heap_tag;
} mi_heap_area_t
----------------------------
inline static size_t mi_page_usable_block_size(const mi_page_t *page)
{
  return mi_page_block_size(page) - (sizeof(mi_padding_t));
}


----------------------------
bool helper__mi_heap_area_visit_blocks_2(unsigned int * const block_idx_ref, unsigned int * const block_idx_ref, size_t * const used_count_ref, unsigned int * const block_idx_ref, const mi_heap_area_t * const area, void * const arg, mi_heap_t * const heap, const size_t bsize, const size_t ubsize, uint8_t * const block, size_t i, uintptr_t free_map[((1UL << (13 + 3)) / (sizeof(void *))) / ((1 << 3) * 8)], mi_block_t * const block, uint8_t * const block, size_t i)
{
  unsigned int block_idx = *block_idx_ref;
  unsigned int block_idx = *block_idx_ref;
  size_t used_count = *used_count_ref;
  unsigned int block_idx = *block_idx_ref;
  if (free_map[i] == 0)
  {
    for (size_t j = 0; j < ((1 << 3) * 8); j += 1)
    {
      used_count += 1;
      if (!visitor(heap, area, block, ubsize, arg))
      {
        return 0;
      }
      block_idx += bsize;
    }

  }
  else
  {
    uintptr_t m = ~free_map[i];
    while (m != 0)
    {
      used_count += 1;
      size_t bitidx = mi_ctz(m);
      if (!visitor(heap, area, (&block[block_idx]) + (bitidx * bsize), ubsize, arg))
      {
        return 0;
      }
      m &= m - 1;
    }

    block_idx += bsize * ((1 << 3) * 8);
  }
  *block_idx_ref = block_idx;
  *block_idx_ref = block_idx;
  *used_count_ref = used_count;
  *block_idx_ref = block_idx;
}


----------------------------
None
----------------------------
***/


static bool mi_heap_area_visitor(const mi_heap_t *heap, const mi_heap_area_ex_t *xarea, void *arg)
{
  mi_visit_blocks_args_t *args = (mi_visit_blocks_args_t *) arg;
  if (!args->visitor(heap, &xarea->area, 0, xarea->area.block_size, args->arg))
  {
    return 0;
  }
  if (args->visit_blocks)
  {
    return _mi_heap_area_visit_blocks(&xarea->area, xarea->page, args->visitor, args->arg);
  }
  else
  {
    return 1;
  }
}


/*** DEPENDENCIES:
typedef struct mi_visit_blocks_args_s
{
  bool visit_blocks;
  mi_block_visit_fun *visitor;
  void *arg;
} mi_visit_blocks_args_t
----------------------------
typedef struct mi_heap_area_ex_s
{
  mi_heap_area_t area;
  mi_page_t *page;
} mi_heap_area_ex_t
----------------------------
bool _mi_heap_area_visit_blocks(const mi_heap_area_t *area, mi_page_t *page, mi_block_visit_fun *visitor, void *arg)
{
  (area != 0) ? ((void) 0) : (_mi_assert_fail("area != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 582, __func__));
  if (area == 0)
  {
    return 1;
  }
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 584, __func__));
  if (page == 0)
  {
    return 1;
  }
  _mi_page_free_collect(page, 1);
  (page->local_free == 0) ? ((void) 0) : (_mi_assert_fail("page->local_free == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 588, __func__));
  if (page->used == 0)
  {
    return 1;
  }
  size_t psize;
  uint8_t * const pstart = _mi_segment_page_start(_mi_page_segment(page), page, &psize);
  mi_heap_t * const heap = mi_page_heap(page);
  const size_t bsize = mi_page_block_size(page);
  const size_t ubsize = mi_page_usable_block_size(page);
  if (page->capacity == 1)
  {
    ((page->used == 1) && (page->free == 0)) ? ((void) 0) : (_mi_assert_fail("page->used == 1 && page->free == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 599, __func__));
    return visitor(mi_page_heap(page), area, pstart, ubsize, arg);
  }
  (bsize <= UINT32_MAX) ? ((void) 0) : (_mi_assert_fail("bsize <= UINT32_MAX", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 602, __func__));
  if (page->used == page->capacity)
  {
    uint8_t *block = pstart;
    unsigned int block_idx = 0;
    for (size_t i = 0; i < page->capacity; i += 1)
    {
      if (!visitor(heap, area, block, ubsize, arg))
      {
        return 0;
      }
      block_idx += bsize;
    }

    return 1;
  }
  uintptr_t free_map[((1UL << (13 + 3)) / (sizeof(void *))) / ((1 << 3) * 8)];
  const uintptr_t bmapsize = _mi_divide_up(page->capacity, (1 << 3) * 8);
  memset(free_map, 0, bmapsize * (sizeof(intptr_t)));
  if ((page->capacity % ((1 << 3) * 8)) != 0)
  {
    size_t shift = page->capacity % ((1 << 3) * 8);
    uintptr_t mask = UINTPTR_MAX << shift;
    free_map[bmapsize - 1] = mask;
  }
  uint64_t magic;
  size_t shift;
  mi_get_fast_divisor(bsize, &magic, &shift);
  size_t free_count = 0;
  for (mi_block_t *block = page->free; (&block[block_idx]) != 0; block_idx = mi_block_next(page, block_idx))
  {
    helper__mi_heap_area_visit_blocks_1(&free_count, psize, pstart, bsize, block, free_map, shift, magic, shift, block, block);
  }

  unsigned int block_idx = 0;
  (page->capacity == (free_count + page->used)) ? ((void) 0) : (_mi_assert_fail("page->capacity == (free_count + page->used)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 649, __func__));
  size_t used_count = 0;
  uint8_t *block = pstart;
  unsigned int block_idx = 0;
  for (size_t i = 0; i < bmapsize; i += 1)
  {
    helper__mi_heap_area_visit_blocks_2(&block_idx, &block_idx, &used_count, &block_idx, area, arg, heap, bsize, ubsize, block, i, free_map, block, block, i);
  }

  (page->used == used_count) ? ((void) 0) : (_mi_assert_fail("page->used == used_count", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 681, __func__));
  return 1;
}


----------------------------
None
----------------------------
***/


mi_heap_t *mi_heap_set_default(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 494, __func__));
  (mi_heap_is_initialized(heap)) ? ((void) 0) : (_mi_assert_fail("mi_heap_is_initialized(heap)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 495, __func__));
  if ((heap == 0) || (!mi_heap_is_initialized(heap)))
  {
    return 0;
  }
  ;
  mi_heap_t *old = mi_prim_get_default_heap();
  _mi_heap_set_default_direct(heap);
  return old;
}


/*** DEPENDENCIES:
void _mi_heap_set_default_direct(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/init.c", 544, __func__));
  _mi_heap_default = heap;
  _mi_prim_thread_associate_default_heap(heap);
}


----------------------------
None
----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
inline static bool mi_heap_is_initialized(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 501, __func__));
  return (heap != 0) && (heap != (&_mi_heap_empty));
}


----------------------------
None
----------------------------
***/


bool mi_heap_visit_blocks(const mi_heap_t *heap, bool visit_blocks, mi_block_visit_fun *visitor, void *arg)
{
  mi_visit_blocks_args_t args = {visit_blocks, visitor, arg};
  return mi_heap_visit_areas(heap, &mi_heap_area_visitor, &args);
}


/*** DEPENDENCIES:
typedef bool mi_block_visit_fun(const mi_heap_t *heap, const mi_heap_area_t *area, void *block, size_t block_size, void *arg)
----------------------------
static bool mi_heap_visit_areas(const mi_heap_t *heap, mi_heap_area_visit_fun *visitor, void *arg)
{
  if (visitor == 0)
  {
    return 0;
  }
  return mi_heap_visit_pages((mi_heap_t *) heap, &mi_heap_visit_areas_page, (void *) visitor, arg);
}


----------------------------
static bool mi_heap_area_visitor(const mi_heap_t *heap, const mi_heap_area_ex_t *xarea, void *arg)
{
  mi_visit_blocks_args_t *args = (mi_visit_blocks_args_t *) arg;
  if (!args->visitor(heap, &xarea->area, 0, xarea->area.block_size, args->arg))
  {
    return 0;
  }
  if (args->visit_blocks)
  {
    return _mi_heap_area_visit_blocks(&xarea->area, xarea->page, args->visitor, args->arg);
  }
  else
  {
    return 1;
  }
}


----------------------------
typedef struct mi_visit_blocks_args_s
{
  bool visit_blocks;
  mi_block_visit_fun *visitor;
  void *arg;
} mi_visit_blocks_args_t
----------------------------
None
----------------------------
***/


