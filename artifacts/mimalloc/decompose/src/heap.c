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


static void mi_heap_free(mi_heap_t *heap, bool do_free_mem)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 281, __func__));
  (mi_heap_is_initialized(heap)) ? ((void) 0) : (_mi_assert_fail("mi_heap_is_initialized(heap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 282, __func__));
  if ((heap == 0) || (!mi_heap_is_initialized(heap)))
  {
    return;
  }
  if (mi_heap_is_backing(heap))
  {
    return;
  }
  if (mi_heap_is_default(heap))
  {
    _mi_heap_set_default_direct(heap->tld->heap_backing);
  }
  mi_heap_t *prev = 0;
  unsigned int prev_idx = 0;
  mi_heap_t *curr = heap->tld->heaps;
  unsigned int curr_idx = 0;
  while (((&curr[curr_idx]) != heap) && ((&curr[curr_idx]) != 0))
  {
    prev_idx = &curr[curr_idx];
    curr_idx = curr_idx->next;
  }

  ((&curr[curr_idx]) == heap) ? ((void) 0) : (_mi_assert_fail("curr == heap", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 299, __func__));
  if ((&curr[curr_idx]) == heap)
  {
    if ((&prev[prev_idx]) != 0)
    {
      prev->next = heap->next;
    }
    else
    {
      heap->tld->heaps = heap->next;
    }
  }
  (heap->tld->heaps != 0) ? ((void) 0) : (_mi_assert_fail("heap->tld->heaps != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 304, __func__));
  if (do_free_mem)
  {
    _mi_meta_free(heap, sizeof(*heap), heap->memid);
  }
}


/*** DEPENDENCIES:
None
----------------------------
inline static bool mi_heap_is_initialized(const mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 542, __func__));
  return (heap != 0) && (heap != (&_mi_heap_empty));
}


----------------------------
None
----------------------------
void _mi_heap_set_default_direct(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/init.c", 590, __func__));
  _mi_heap_default = heap;
  _mi_prim_thread_associate_default_heap(heap);
}


----------------------------
inline static bool mi_heap_is_backing(const mi_heap_t *heap)
{
  return heap->tld->heap_backing == heap;
}


----------------------------
static bool mi_heap_is_default(const mi_heap_t *heap)
{
  return heap == mi_prim_get_default_heap();
}


----------------------------
None
----------------------------
***/


static bool mi_heap_page_is_valid(mi_heap_t *heap, mi_page_queue_t *pq, mi_page_t *page, void *arg1, void *arg2)
{
  (void) arg1;
  (void) arg2;
  (void) pq;
  (mi_page_heap(page) == heap) ? ((void) 0) : (_mi_assert_fail("mi_page_heap(page) == heap", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 57, __func__));
  ;
  return 1;
}


/*** DEPENDENCIES:
None
----------------------------
inline static mi_heap_t *mi_page_heap(const mi_page_t *page)
{
  return page->heap;
}


----------------------------
None
----------------------------
***/


static bool mi_heap_page_collect(mi_heap_t *heap, mi_page_queue_t *pq, mi_page_t *page, void *arg_collect, void *arg2)
{
  (void) arg2;
  (void) heap;
  (mi_heap_page_is_valid(heap, pq, page, 0, 0)) ? ((void) 0) : (_mi_assert_fail("mi_heap_page_is_valid(heap, pq, page, NULL, NULL)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 93, __func__));
  mi_collect_t collect = *((mi_collect_t *) arg_collect);
  _mi_page_free_collect(page, collect >= MI_FORCE);
  if (mi_page_all_free(page))
  {
    _mi_page_free(page, pq);
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
static bool mi_heap_page_is_valid(mi_heap_t *heap, mi_page_queue_t *pq, mi_page_t *page, void *arg1, void *arg2)
{
  (void) arg1;
  (void) arg2;
  (void) pq;
  (mi_page_heap(page) == heap) ? ((void) 0) : (_mi_assert_fail("mi_page_heap(page) == heap", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 57, __func__));
  ;
  return 1;
}


----------------------------
inline static bool mi_page_all_free(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 714, __func__));
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
      (mi_page_heap(page) == heap) ? ((void) 0) : (_mi_assert_fail("mi_page_heap(page) == heap", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 39, __func__));
      count += 1;
      if (!fn(heap, pq, page, arg1, arg2))
      {
        return 0;
      }
      page_idx = next;
    }

  }

  (count == total) ? ((void) 0) : (_mi_assert_fail("count == total", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 47, __func__));
  return 1;
}


/*** DEPENDENCIES:
None
----------------------------
inline static mi_heap_t *mi_page_heap(const mi_page_t *page)
{
  return page->heap;
}


----------------------------
typedef bool heap_page_visitor_fun(mi_heap_t *heap, mi_page_queue_t *pq, mi_page_t *page, void *arg1, void *arg2)
----------------------------
None
----------------------------
***/


static void mi_heap_collect_ex(mi_heap_t *heap, mi_collect_t collect)
{
  if ((heap == 0) || (!mi_heap_is_initialized(heap)))
  {
    return;
  }
  ;
  const bool force = collect >= MI_FORCE;
  _mi_deferred_free(heap, force);
  _mi_heap_collect_retired(heap, force);
  mi_heap_visit_pages(heap, &mi_heap_page_collect, &collect, 0);
  _mi_arenas_collect(collect == MI_FORCE, collect >= MI_FORCE, heap->tld);
  if (collect <= MI_FORCE)
  {
    _mi_stats_merge_thread(heap->tld);
  }
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
      (mi_page_heap(page) == heap) ? ((void) 0) : (_mi_assert_fail("mi_page_heap(page) == heap", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 39, __func__));
      count += 1;
      if (!fn(heap, pq, page, arg1, arg2))
      {
        return 0;
      }
      page_idx = next;
    }

  }

  (count == total) ? ((void) 0) : (_mi_assert_fail("count == total", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 47, __func__));
  return 1;
}


----------------------------
inline static bool mi_heap_is_initialized(const mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 542, __func__));
  return (heap != 0) && (heap != (&_mi_heap_empty));
}


----------------------------
static bool mi_heap_page_collect(mi_heap_t *heap, mi_page_queue_t *pq, mi_page_t *page, void *arg_collect, void *arg2)
{
  (void) arg2;
  (void) heap;
  (mi_heap_page_is_valid(heap, pq, page, 0, 0)) ? ((void) 0) : (_mi_assert_fail("mi_heap_page_is_valid(heap, pq, page, NULL, NULL)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 93, __func__));
  mi_collect_t collect = *((mi_collect_t *) arg_collect);
  _mi_page_free_collect(page, collect >= MI_FORCE);
  if (mi_page_all_free(page))
  {
    _mi_page_free(page, pq);
  }
  else
    if (collect == MI_ABANDON)
  {
    _mi_page_abandon(page, pq);
  }
  return 1;
}


----------------------------
void _mi_stats_merge_thread(mi_tld_t *tld)
{
  ((tld != 0) && (tld->subproc != 0)) ? ((void) 0) : (_mi_assert_fail("tld != NULL && tld->subproc != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/stats.c", 422, __func__));
  _mi_stats_merge_from(&tld->subproc->stats, &tld->stats);
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
void _mi_arenas_collect(bool force_purge, bool visit_all, mi_tld_t *tld)
{
  mi_arenas_try_purge(force_purge, visit_all, tld->subproc, tld->thread_seq);
}


----------------------------
typedef enum mi_collect_e
{
  MI_NORMAL,
  MI_FORCE,
  MI_ABANDON
} mi_collect_t
----------------------------
None
----------------------------
***/


void _mi_heap_collect_abandon(mi_heap_t *heap)
{
  mi_heap_collect_ex(heap, MI_ABANDON);
}


/*** DEPENDENCIES:
static void mi_heap_collect_ex(mi_heap_t *heap, mi_collect_t collect)
{
  if ((heap == 0) || (!mi_heap_is_initialized(heap)))
  {
    return;
  }
  ;
  const bool force = collect >= MI_FORCE;
  _mi_deferred_free(heap, force);
  _mi_heap_collect_retired(heap, force);
  mi_heap_visit_pages(heap, &mi_heap_page_collect, &collect, 0);
  _mi_arenas_collect(collect == MI_FORCE, collect >= MI_FORCE, heap->tld);
  if (collect <= MI_FORCE)
  {
    _mi_stats_merge_thread(heap->tld);
  }
}


----------------------------
None
----------------------------
***/


void mi_heap_delete(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 460, __func__));
  (mi_heap_is_initialized(heap)) ? ((void) 0) : (_mi_assert_fail("mi_heap_is_initialized(heap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 461, __func__));
  ;
  if ((heap == 0) || (!mi_heap_is_initialized(heap)))
  {
    return;
  }
  _mi_heap_collect_abandon(heap);
  (heap->page_count == 0) ? ((void) 0) : (_mi_assert_fail("heap->page_count==0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 468, __func__));
  mi_heap_free(heap, 1);
}


/*** DEPENDENCIES:
None
----------------------------
void _mi_heap_collect_abandon(mi_heap_t *heap)
{
  mi_heap_collect_ex(heap, MI_ABANDON);
}


----------------------------
inline static bool mi_heap_is_initialized(const mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 542, __func__));
  return (heap != 0) && (heap != (&_mi_heap_empty));
}


----------------------------
static void mi_heap_free(mi_heap_t *heap, bool do_free_mem)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 281, __func__));
  (mi_heap_is_initialized(heap)) ? ((void) 0) : (_mi_assert_fail("mi_heap_is_initialized(heap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 282, __func__));
  if ((heap == 0) || (!mi_heap_is_initialized(heap)))
  {
    return;
  }
  if (mi_heap_is_backing(heap))
  {
    return;
  }
  if (mi_heap_is_default(heap))
  {
    _mi_heap_set_default_direct(heap->tld->heap_backing);
  }
  mi_heap_t *prev = 0;
  unsigned int prev_idx = 0;
  mi_heap_t *curr = heap->tld->heaps;
  unsigned int curr_idx = 0;
  while (((&curr[curr_idx]) != heap) && ((&curr[curr_idx]) != 0))
  {
    prev_idx = &curr[curr_idx];
    curr_idx = curr_idx->next;
  }

  ((&curr[curr_idx]) == heap) ? ((void) 0) : (_mi_assert_fail("curr == heap", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 299, __func__));
  if ((&curr[curr_idx]) == heap)
  {
    if ((&prev[prev_idx]) != 0)
    {
      prev->next = heap->next;
    }
    else
    {
      heap->tld->heaps = heap->next;
    }
  }
  (heap->tld->heaps != 0) ? ((void) 0) : (_mi_assert_fail("heap->tld->heaps != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 304, __func__));
  if (do_free_mem)
  {
    _mi_meta_free(heap, sizeof(*heap), heap->memid);
  }
}


----------------------------
None
----------------------------
***/


uintptr_t _mi_heap_random_next(mi_heap_t *heap)
{
  return _mi_random_next(&heap->random);
}


/*** DEPENDENCIES:
uintptr_t _mi_random_next(mi_random_ctx_t *ctx)
{
  (mi_random_is_initialized(ctx)) ? ((void) 0) : (_mi_assert_fail("mi_random_is_initialized(ctx)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/random.c", 140, __func__));
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


void _mi_heap_init(mi_heap_t *heap, mi_arena_id_t arena_id, bool allow_destroy, uint8_t heap_tag, mi_tld_t *tld)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 179, __func__));
  mi_memid_t memid = heap->memid;
  _mi_memcpy_aligned(heap, &_mi_heap_empty, sizeof(mi_heap_t));
  heap->memid = memid;
  heap->tld = tld;
  heap->tag = heap_tag;
  heap->numa_node = tld->numa_node;
  heap->exclusive_arena = _mi_arena_from_id(arena_id);
  heap->allow_page_reclaim = (!allow_destroy) && (mi_option_get(mi_option_page_reclaim_on_free) >= 0);
  heap->allow_page_abandon = (!allow_destroy) && (mi_option_get(mi_option_page_full_retain) >= 0);
  heap->page_full_retain = mi_option_get_clamp(mi_option_page_full_retain, -1, 32);
  if (heap->tld->is_in_threadpool)
  {
    if (heap->page_full_retain > 0)
    {
      heap->page_full_retain = heap->page_full_retain / 4;
    }
  }
  if (heap->tld->heap_backing == 0)
  {
    heap->tld->heap_backing = heap;
    _mi_random_init(&heap->random);
  }
  else
  {
    _mi_random_split(&heap->tld->heap_backing->random, &heap->random);
  }
  heap->cookie = _mi_heap_random_next(heap) | 1;
  _mi_heap_guarded_init(heap);
  heap->next = heap->tld->heaps;
  heap->tld->heaps = heap;
}


/*** DEPENDENCIES:
void _mi_random_split(mi_random_ctx_t *ctx, mi_random_ctx_t *ctx_new)
{
  (mi_random_is_initialized(ctx)) ? ((void) 0) : (_mi_assert_fail("mi_random_is_initialized(ctx)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/random.c", 134, __func__));
  (ctx != ctx_new) ? ((void) 0) : (_mi_assert_fail("ctx != ctx_new", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/random.c", 135, __func__));
  chacha_split(ctx, (uintptr_t) ctx_new, ctx_new);
}


----------------------------
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
void _mi_random_init(mi_random_ctx_t *ctx)
{
  mi_random_init_ex(ctx, 0);
}


----------------------------
mi_arena_t *_mi_arena_from_id(mi_arena_id_t id)
{
  return (mi_arena_t *) id;
}


----------------------------
typedef void *mi_arena_id_t
----------------------------
uintptr_t _mi_heap_random_next(mi_heap_t *heap)
{
  return _mi_random_next(&heap->random);
}


----------------------------
inline static void _mi_memcpy_aligned(void *dst, const void *src, size_t n)
{
  (((((uintptr_t) dst) % (1 << 3)) == 0) && ((((uintptr_t) src) % (1 << 3)) == 0)) ? ((void) 0) : (_mi_assert_fail("((uintptr_t)dst % MI_INTPTR_SIZE == 0) && ((uintptr_t)src % MI_INTPTR_SIZE == 0)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 1178, __func__));
  void *adst = __builtin_assume_aligned(dst, 1 << 3);
  const void *asrc = __builtin_assume_aligned(src, 1 << 3);
  _mi_memcpy(adst, asrc, n);
}


----------------------------
extern const mi_heap_t _mi_heap_empty
----------------------------
void _mi_heap_guarded_init(mi_heap_t *heap)
{
  (void) heap;
}


----------------------------
None
----------------------------
***/


mi_heap_t *_mi_heap_create(int heap_tag, bool allow_destroy, mi_arena_id_t arena_id, mi_tld_t *tld)
{
  (tld != 0) ? ((void) 0) : (_mi_assert_fail("tld!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 218, __func__));
  ((heap_tag >= 0) && (heap_tag < 256)) ? ((void) 0) : (_mi_assert_fail("heap_tag >= 0 && heap_tag < 256", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 219, __func__));
  mi_memid_t memid;
  mi_heap_t *heap;
  unsigned int heap_idx = 0;
  if (arena_id == _mi_arena_id_none())
  {
    heap_idx = (mi_heap_t *) _mi_meta_zalloc(sizeof(mi_heap_t), &memid);
  }
  else
  {
    heap_idx = (mi_heap_t *) _mi_arenas_alloc(_mi_subproc(), _mi_align_up(sizeof(mi_heap_t), 1 * (1UL << (13 + 3))), 1, 1, _mi_arena_from_id(arena_id), tld->thread_seq, tld->numa_node, &memid);
  }
  if ((&heap[heap_idx]) == 0)
  {
    _mi_error_message(12, "unable to allocate heap meta-data\n");
    return 0;
  }
  heap->memid = memid;
  _mi_heap_init(heap, arena_id, allow_destroy, (uint8_t) heap_tag, tld);
  return heap;
}


/*** DEPENDENCIES:
None
----------------------------
mi_arena_id_t _mi_arena_id_none(void)
{
  return 0;
}


----------------------------
mi_subproc_t *_mi_subproc(void)
{
  mi_heap_t *heap = mi_prim_get_default_heap();
  if (heap == 0)
  {
    return _mi_subproc_main();
  }
  else
  {
    return heap->tld->subproc;
  }
}


----------------------------
mi_arena_t *_mi_arena_from_id(mi_arena_id_t id)
{
  return (mi_arena_t *) id;
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
void _mi_heap_init(mi_heap_t *heap, mi_arena_id_t arena_id, bool allow_destroy, uint8_t heap_tag, mi_tld_t *tld)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 179, __func__));
  mi_memid_t memid = heap->memid;
  _mi_memcpy_aligned(heap, &_mi_heap_empty, sizeof(mi_heap_t));
  heap->memid = memid;
  heap->tld = tld;
  heap->tag = heap_tag;
  heap->numa_node = tld->numa_node;
  heap->exclusive_arena = _mi_arena_from_id(arena_id);
  heap->allow_page_reclaim = (!allow_destroy) && (mi_option_get(mi_option_page_reclaim_on_free) >= 0);
  heap->allow_page_abandon = (!allow_destroy) && (mi_option_get(mi_option_page_full_retain) >= 0);
  heap->page_full_retain = mi_option_get_clamp(mi_option_page_full_retain, -1, 32);
  if (heap->tld->is_in_threadpool)
  {
    if (heap->page_full_retain > 0)
    {
      heap->page_full_retain = heap->page_full_retain / 4;
    }
  }
  if (heap->tld->heap_backing == 0)
  {
    heap->tld->heap_backing = heap;
    _mi_random_init(&heap->random);
  }
  else
  {
    _mi_random_split(&heap->tld->heap_backing->random, &heap->random);
  }
  heap->cookie = _mi_heap_random_next(heap) | 1;
  _mi_heap_guarded_init(heap);
  heap->next = heap->tld->heaps;
  heap->tld->heaps = heap;
}


----------------------------
typedef void *mi_arena_id_t
----------------------------
void *_mi_arenas_alloc(mi_subproc_t *subproc, size_t size, bool commit, bool allow_large, mi_arena_t *req_arena, size_t tseq, int numa_node, mi_memid_t *memid)
{
  return _mi_arenas_alloc_aligned(subproc, size, 1UL << (13 + 3), 0, commit, allow_large, req_arena, tseq, numa_node, memid);
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
void *_mi_meta_zalloc(size_t size, mi_memid_t *pmemid)
{
  (pmemid != 0) ? ((void) 0) : (_mi_assert_fail("pmemid != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena-meta.c", 112, __func__));
  size = _mi_align_up(size, 1 << (16 - (6 + 3)));
  if ((size == 0) || (size > (((1 << (6 + 3)) / 8) * (1 << (16 - (6 + 3))))))
  {
    return 0;
  }
  const size_t block_count = _mi_divide_up(size, 1 << (16 - (6 + 3)));
  ((block_count > 0) && (block_count < (1 << (6 + 3)))) ? ((void) 0) : (_mi_assert_fail("block_count > 0 && block_count < MI_BCHUNK_BITS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/arena-meta.c", 116, __func__));
  mi_meta_page_t *mpage0 = atomic_load_explicit(&mi_meta_pages, memory_order_acquire);
  mi_meta_page_t *mpage = mpage0;
  unsigned int mpage_idx = 0;
  while ((&mpage[mpage_idx]) != 0)
  {
    size_t block_idx;
    if (mi_bbitmap_try_find_and_clearN(&mpage->blocks_free, block_count, 0, &block_idx))
    {
      *pmemid = _mi_memid_create_meta(mpage, block_idx, block_count);
      return mi_meta_block_start(mpage, block_idx);
    }
    else
    {
      mpage_idx = mi_meta_page_next(mpage_idx);
    }
  }

  if (atomic_load_explicit(&mi_meta_pages, memory_order_acquire) != mpage0)
  {
    return _mi_meta_zalloc(size, pmemid);
  }
  mpage_idx = mi_meta_page_zalloc();
  if ((&mpage[mpage_idx]) != 0)
  {
    size_t block_idx;
    if (mi_bbitmap_try_find_and_clearN(&mpage->blocks_free, block_count, 0, &block_idx))
    {
      *pmemid = _mi_memid_create_meta(mpage, block_idx, block_count);
      return mi_meta_block_start(mpage, block_idx);
    }
  }
  return _mi_os_alloc(size, pmemid);
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
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


void mi_heap_collect(mi_heap_t *heap, bool force)
{
  mi_heap_collect_ex(heap, (force) ? (MI_FORCE) : (MI_NORMAL));
}


/*** DEPENDENCIES:
static void mi_heap_collect_ex(mi_heap_t *heap, mi_collect_t collect)
{
  if ((heap == 0) || (!mi_heap_is_initialized(heap)))
  {
    return;
  }
  ;
  const bool force = collect >= MI_FORCE;
  _mi_deferred_free(heap, force);
  _mi_heap_collect_retired(heap, force);
  mi_heap_visit_pages(heap, &mi_heap_page_collect, &collect, 0);
  _mi_arenas_collect(collect == MI_FORCE, collect >= MI_FORCE, heap->tld);
  if (collect <= MI_FORCE)
  {
    _mi_stats_merge_thread(heap->tld);
  }
}


----------------------------
None
----------------------------
***/


static size_t mi_fast_divide(size_t n, uint64_t magic, size_t shift)
{
  (n <= UINT32_MAX) ? ((void) 0) : (_mi_assert_fail("n <= UINT32_MAX", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 608, __func__));
  const uint64_t hi = (((uint64_t) n) * magic) >> 32;
  return (size_t) ((hi + n) >> shift);
}


/*** DEPENDENCIES:
None
----------------------------
***/


static void mi_heap_reset_pages(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 270, __func__));
  (mi_heap_is_initialized(heap)) ? ((void) 0) : (_mi_assert_fail("mi_heap_is_initialized(heap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 271, __func__));
  _mi_memset(&heap->pages_free_direct, 0, sizeof(heap->pages_free_direct));
  _mi_memcpy_aligned(&heap->pages, &_mi_heap_empty.pages, sizeof(heap->pages));
  heap->page_count = 0;
}


/*** DEPENDENCIES:
None
----------------------------
inline static void _mi_memset(void *dst, int val, size_t n)
{
  memset(dst, val, n);
}


----------------------------
inline static bool mi_heap_is_initialized(const mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 542, __func__));
  return (heap != 0) && (heap != (&_mi_heap_empty));
}


----------------------------
inline static void _mi_memcpy_aligned(void *dst, const void *src, size_t n)
{
  (((((uintptr_t) dst) % (1 << 3)) == 0) && ((((uintptr_t) src) % (1 << 3)) == 0)) ? ((void) 0) : (_mi_assert_fail("((uintptr_t)dst % MI_INTPTR_SIZE == 0) && ((uintptr_t)src % MI_INTPTR_SIZE == 0)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 1178, __func__));
  void *adst = __builtin_assume_aligned(dst, 1 << 3);
  const void *asrc = __builtin_assume_aligned(src, 1 << 3);
  _mi_memcpy(adst, asrc, n);
}


----------------------------
extern const mi_heap_t _mi_heap_empty
----------------------------
None
----------------------------
***/


static bool _mi_heap_page_destroy(mi_heap_t *heap, mi_page_queue_t *pq, mi_page_t *page, void *arg1, void *arg2)
{
  (void) arg1;
  (void) arg2;
  (void) pq;
  const size_t bsize = mi_page_block_size(page);
  if (bsize > ((8 * (1 * (1UL << (13 + 3)))) / 8))
  {
    __mi_stat_decrease(&heap->tld->stats.malloc_huge, bsize);
  }
  _mi_page_free_collect(page, 0);
  const size_t inuse = page->used;
  if (bsize <= ((8 * (1 * (1UL << (13 + 3)))) / 8))
  {
    __mi_stat_decrease(&heap->tld->stats.malloc_normal, bsize * inuse);
    __mi_stat_decrease(&heap->tld->stats.malloc_bins[_mi_bin(bsize)], inuse);
  }
  (mi_page_thread_free(page) == 0) ? ((void) 0) : (_mi_assert_fail("mi_page_thread_free(page) == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 355, __func__));
  page->used = 0;
  page->next = 0;
  page->prev = 0;
  mi_page_set_heap(page, 0);
  _mi_arenas_page_free(page, heap->tld);
  return 1;
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
size_t _mi_bin(size_t size)
{
  return mi_bin(size);
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
void __mi_stat_decrease(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_update(stat, -((int64_t) amount));
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
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
}


----------------------------
inline static mi_block_t *mi_page_thread_free(const mi_page_t *page)
{
  return mi_tf_block(atomic_load_explicit(&((mi_page_t *) page)->xthread_free, memory_order_relaxed));
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
      (mi_page_heap(page) == heap) ? ((void) 0) : (_mi_assert_fail("mi_page_heap(page) == heap", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 39, __func__));
      count += 1;
      if (!fn(heap, pq, page, arg1, arg2))
      {
        return 0;
      }
      page_idx = next;
    }

  }

  (count == total) ? ((void) 0) : (_mi_assert_fail("count == total", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 47, __func__));
  return 1;
}


----------------------------
static bool _mi_heap_page_destroy(mi_heap_t *heap, mi_page_queue_t *pq, mi_page_t *page, void *arg1, void *arg2)
{
  (void) arg1;
  (void) arg2;
  (void) pq;
  const size_t bsize = mi_page_block_size(page);
  if (bsize > ((8 * (1 * (1UL << (13 + 3)))) / 8))
  {
    __mi_stat_decrease(&heap->tld->stats.malloc_huge, bsize);
  }
  _mi_page_free_collect(page, 0);
  const size_t inuse = page->used;
  if (bsize <= ((8 * (1 * (1UL << (13 + 3)))) / 8))
  {
    __mi_stat_decrease(&heap->tld->stats.malloc_normal, bsize * inuse);
    __mi_stat_decrease(&heap->tld->stats.malloc_bins[_mi_bin(bsize)], inuse);
  }
  (mi_page_thread_free(page) == 0) ? ((void) 0) : (_mi_assert_fail("mi_page_thread_free(page) == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 355, __func__));
  page->used = 0;
  page->next = 0;
  page->prev = 0;
  mi_page_set_heap(page, 0);
  _mi_arenas_page_free(page, heap->tld);
  return 1;
}


----------------------------
static void mi_heap_reset_pages(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 270, __func__));
  (mi_heap_is_initialized(heap)) ? ((void) 0) : (_mi_assert_fail("mi_heap_is_initialized(heap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 271, __func__));
  _mi_memset(&heap->pages_free_direct, 0, sizeof(heap->pages_free_direct));
  _mi_memcpy_aligned(&heap->pages, &_mi_heap_empty.pages, sizeof(heap->pages));
  heap->page_count = 0;
}


----------------------------
None
----------------------------
***/


void mi_heap_destroy(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 382, __func__));
  (mi_heap_is_initialized(heap)) ? ((void) 0) : (_mi_assert_fail("mi_heap_is_initialized(heap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 383, __func__));
  (!heap->allow_page_reclaim) ? ((void) 0) : (_mi_assert_fail("!heap->allow_page_reclaim", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 384, __func__));
  (!heap->allow_page_abandon) ? ((void) 0) : (_mi_assert_fail("!heap->allow_page_abandon", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 385, __func__));
  ;
  if ((heap == 0) || (!mi_heap_is_initialized(heap)))
  {
    return;
  }
  if (heap->allow_page_reclaim)
  {
    _mi_warning_message("'mi_heap_destroy' called but ignored as the heap was not created with 'allow_destroy' (heap at %p)\n", heap);
    mi_heap_delete(heap);
  }
  else
  {
    _mi_heap_destroy_pages(heap);
    mi_heap_free(heap, 1);
  }
}


/*** DEPENDENCIES:
None
----------------------------
void _mi_heap_destroy_pages(mi_heap_t *heap)
{
  mi_heap_visit_pages(heap, &_mi_heap_page_destroy, 0, 0);
  mi_heap_reset_pages(heap);
}


----------------------------
inline static bool mi_heap_is_initialized(const mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 542, __func__));
  return (heap != 0) && (heap != (&_mi_heap_empty));
}


----------------------------
None
----------------------------
static void mi_heap_free(mi_heap_t *heap, bool do_free_mem)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 281, __func__));
  (mi_heap_is_initialized(heap)) ? ((void) 0) : (_mi_assert_fail("mi_heap_is_initialized(heap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 282, __func__));
  if ((heap == 0) || (!mi_heap_is_initialized(heap)))
  {
    return;
  }
  if (mi_heap_is_backing(heap))
  {
    return;
  }
  if (mi_heap_is_default(heap))
  {
    _mi_heap_set_default_direct(heap->tld->heap_backing);
  }
  mi_heap_t *prev = 0;
  unsigned int prev_idx = 0;
  mi_heap_t *curr = heap->tld->heaps;
  unsigned int curr_idx = 0;
  while (((&curr[curr_idx]) != heap) && ((&curr[curr_idx]) != 0))
  {
    prev_idx = &curr[curr_idx];
    curr_idx = curr_idx->next;
  }

  ((&curr[curr_idx]) == heap) ? ((void) 0) : (_mi_assert_fail("curr == heap", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 299, __func__));
  if ((&curr[curr_idx]) == heap)
  {
    if ((&prev[prev_idx]) != 0)
    {
      prev->next = heap->next;
    }
    else
    {
      heap->tld->heaps = heap->next;
    }
  }
  (heap->tld->heaps != 0) ? ((void) 0) : (_mi_assert_fail("heap->tld->heaps != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 304, __func__));
  if (do_free_mem)
  {
    _mi_meta_free(heap, sizeof(*heap), heap->memid);
  }
}


----------------------------
void mi_heap_delete(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 460, __func__));
  (mi_heap_is_initialized(heap)) ? ((void) 0) : (_mi_assert_fail("mi_heap_is_initialized(heap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 461, __func__));
  ;
  if ((heap == 0) || (!mi_heap_is_initialized(heap)))
  {
    return;
  }
  _mi_heap_collect_abandon(heap);
  (heap->page_count == 0) ? ((void) 0) : (_mi_assert_fail("heap->page_count==0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 468, __func__));
  mi_heap_free(heap, 1);
}


----------------------------
None
----------------------------
***/


void _mi_heap_unsafe_destroy_all(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 412, __func__));
  if (heap == 0)
  {
    return;
  }
  mi_heap_t *curr = heap->tld->heaps;
  unsigned int curr_idx = 0;
  while ((&curr[curr_idx]) != 0)
  {
    mi_heap_t *next = curr->next;
    if (!curr->allow_page_reclaim)
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
void _mi_heap_destroy_pages(mi_heap_t *heap)
{
  mi_heap_visit_pages(heap, &_mi_heap_page_destroy, 0, 0);
  mi_heap_reset_pages(heap);
}


----------------------------
void mi_heap_destroy(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 382, __func__));
  (mi_heap_is_initialized(heap)) ? ((void) 0) : (_mi_assert_fail("mi_heap_is_initialized(heap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 383, __func__));
  (!heap->allow_page_reclaim) ? ((void) 0) : (_mi_assert_fail("!heap->allow_page_reclaim", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 384, __func__));
  (!heap->allow_page_abandon) ? ((void) 0) : (_mi_assert_fail("!heap->allow_page_abandon", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 385, __func__));
  ;
  if ((heap == 0) || (!mi_heap_is_initialized(heap)))
  {
    return;
  }
  if (heap->allow_page_reclaim)
  {
    _mi_warning_message("'mi_heap_destroy' called but ignored as the heap was not created with 'allow_destroy' (heap at %p)\n", heap);
    mi_heap_delete(heap);
  }
  else
  {
    _mi_heap_destroy_pages(heap);
    mi_heap_free(heap, 1);
  }
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
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
}


----------------------------
inline static uint8_t *mi_page_start(const mi_page_t *page)
{
  return page->page_start;
}


----------------------------
None
----------------------------
***/


bool mi_heap_check_owned(mi_heap_t *heap, const void *p)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 570, __func__));
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
      (mi_page_heap(page) == heap) ? ((void) 0) : (_mi_assert_fail("mi_page_heap(page) == heap", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 39, __func__));
      count += 1;
      if (!fn(heap, pq, page, arg1, arg2))
      {
        return 0;
      }
      page_idx = next;
    }

  }

  (count == total) ? ((void) 0) : (_mi_assert_fail("count == total", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 47, __func__));
  return 1;
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
***/


bool mi_check_owned(const void *p)
{
  return mi_heap_check_owned(mi_prim_get_default_heap(), p);
}


/*** DEPENDENCIES:
bool mi_heap_check_owned(mi_heap_t *heap, const void *p)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 570, __func__));
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


void mi_heap_set_numa_affinity(mi_heap_t *heap, int numa_node)
{
  if (heap == 0)
  {
    return;
  }
  heap->numa_node = (numa_node < 0) ? (-1) : (numa_node % _mi_os_numa_node_count());
}


/*** DEPENDENCIES:
int _mi_os_numa_node_count(void)
{
  size_t count = atomic_load_explicit(&mi_numa_node_count, memory_order_acquire);
  if (__builtin_expect(!(!(count == 0)), 0))
  {
    long ncount = mi_option_get(mi_option_use_numa_nodes);
    if ((ncount > 0) && (ncount < 2147483647))
    {
      count = (size_t) ncount;
    }
    else
    {
      const size_t n = _mi_prim_numa_node_count();
      if ((n == 0) || (n > 2147483647))
      {
        count = 1;
      }
      else
      {
        count = n;
      }
    }
    atomic_store_explicit(&mi_numa_node_count, count, memory_order_release);
    _mi_verbose_message("using %zd numa regions\n", count);
  }
  ((count > 0) && (count <= 2147483647)) ? ((void) 0) : (_mi_assert_fail("count > 0 && count <= INT_MAX", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/os.c", 776, __func__));
  return (int) count;
}


----------------------------
None
----------------------------
***/


static void mi_get_fast_divisor(size_t divisor, uint64_t *magic, size_t *shift)
{
  ((divisor > 0) && (divisor <= UINT32_MAX)) ? ((void) 0) : (_mi_assert_fail("divisor > 0 && divisor <= UINT32_MAX", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 602, __func__));
  *shift = ((1 << 3) * 8) - mi_clz(divisor - 1);
  *magic = (((((uint64_t) 1) << 32) * ((((uint64_t) 1) << (*shift)) - divisor)) / divisor) + 1;
}


/*** DEPENDENCIES:
inline static size_t mi_clz(size_t x)
{
  return (x != 0) ? ((size_t) __builtin_clzll(x)) : ((1 << 3) * 8);
}


----------------------------
None
----------------------------
***/


bool _mi_heap_memid_is_suitable(mi_heap_t *heap, mi_memid_t memid)
{
  return _mi_arena_memid_is_suitable(memid, heap->exclusive_arena);
}


/*** DEPENDENCIES:
bool _mi_arena_memid_is_suitable(mi_memid_t memid, mi_arena_t *request_arena)
{
  if (memid.memkind == MI_MEM_ARENA)
  {
    return mi_arena_id_is_suitable(memid.mem.arena.arena, request_arena);
  }
  else
  {
    return mi_arena_id_is_suitable(0, request_arena);
  }
}


----------------------------
None
----------------------------
***/


// hint:  ['free_count_ref is a mutable refrence to size_t']
void helper__mi_heap_area_visit_blocks_1(size_t * const free_count_ref, size_t psize, uint8_t * const pstart, const size_t bsize, uint8_t * const block, uintptr_t free_map[((1 * (1UL << (13 + 3))) / (sizeof(void *))) / ((1 << 3) * 8)], size_t shift, uint64_t magic, size_t shift, mi_block_t * const block, uint8_t * const block)
{
  size_t free_count = *free_count_ref;
  free_count += 1;
  ((((uint8_t *) block) >= pstart) && (((uint8_t *) block) < (pstart + psize))) ? ((void) 0) : (_mi_assert_fail("(uint8_t*)block >= pstart && (uint8_t*)block < (pstart + psize)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 670, __func__));
  size_t offset = ((uint8_t *) block) - pstart;
  ((offset % bsize) == 0) ? ((void) 0) : (_mi_assert_fail("offset % bsize == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 672, __func__));
  (offset <= UINT32_MAX) ? ((void) 0) : (_mi_assert_fail("offset <= UINT32_MAX", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 673, __func__));
  size_t blockidx = mi_fast_divide(offset, magic, shift);
  (blockidx == (offset / bsize)) ? ((void) 0) : (_mi_assert_fail("blockidx == offset / bsize", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 675, __func__));
  (blockidx < ((1 * (1UL << (13 + 3))) / (sizeof(void *)))) ? ((void) 0) : (_mi_assert_fail("blockidx < MI_MAX_BLOCKS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 676, __func__));
  size_t bitidx = blockidx / ((1 << 3) * 8);
  size_t bit = blockidx - (bitidx * ((1 << 3) * 8));
  free_map[bitidx] |= ((uintptr_t) 1) << bit;
  *free_count_ref = free_count;
}


/*** DEPENDENCIES:
static size_t mi_fast_divide(size_t n, uint64_t magic, size_t shift)
{
  (n <= UINT32_MAX) ? ((void) 0) : (_mi_assert_fail("n <= UINT32_MAX", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 608, __func__));
  const uint64_t hi = (((uint64_t) n) * magic) >> 32;
  return (size_t) ((hi + n) >> shift);
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
None
----------------------------
***/


mi_heap_t *mi_heap_get_backing(void)
{
  mi_heap_t *heap = mi_heap_get_default();
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 169, __func__));
  mi_heap_t *bheap = heap->tld->heap_backing;
  (bheap != 0) ? ((void) 0) : (_mi_assert_fail("bheap!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 171, __func__));
  (bheap->tld->thread_id == _mi_thread_id()) ? ((void) 0) : (_mi_assert_fail("bheap->tld->thread_id == _mi_thread_id()", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 172, __func__));
  return bheap;
}


/*** DEPENDENCIES:
None
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
mi_threadid_t _mi_thread_id(void)
{
  return _mi_prim_thread_id();
}


----------------------------
None
----------------------------
***/


mi_heap_t *mi_heap_new_ex(int heap_tag, bool allow_destroy, mi_arena_id_t arena_id)
{
  mi_heap_t *bheap = mi_heap_get_backing();
  (bheap != 0) ? ((void) 0) : (_mi_assert_fail("bheap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 242, __func__));
  return _mi_heap_create(heap_tag, allow_destroy, arena_id, bheap->tld);
}


/*** DEPENDENCIES:
None
----------------------------
typedef void *mi_arena_id_t
----------------------------
mi_heap_t *mi_heap_get_backing(void)
{
  mi_heap_t *heap = mi_heap_get_default();
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 169, __func__));
  mi_heap_t *bheap = heap->tld->heap_backing;
  (bheap != 0) ? ((void) 0) : (_mi_assert_fail("bheap!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 171, __func__));
  (bheap->tld->thread_id == _mi_thread_id()) ? ((void) 0) : (_mi_assert_fail("bheap->tld->thread_id == _mi_thread_id()", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 172, __func__));
  return bheap;
}


----------------------------
mi_heap_t *_mi_heap_create(int heap_tag, bool allow_destroy, mi_arena_id_t arena_id, mi_tld_t *tld)
{
  (tld != 0) ? ((void) 0) : (_mi_assert_fail("tld!=NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 218, __func__));
  ((heap_tag >= 0) && (heap_tag < 256)) ? ((void) 0) : (_mi_assert_fail("heap_tag >= 0 && heap_tag < 256", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 219, __func__));
  mi_memid_t memid;
  mi_heap_t *heap;
  unsigned int heap_idx = 0;
  if (arena_id == _mi_arena_id_none())
  {
    heap_idx = (mi_heap_t *) _mi_meta_zalloc(sizeof(mi_heap_t), &memid);
  }
  else
  {
    heap_idx = (mi_heap_t *) _mi_arenas_alloc(_mi_subproc(), _mi_align_up(sizeof(mi_heap_t), 1 * (1UL << (13 + 3))), 1, 1, _mi_arena_from_id(arena_id), tld->thread_seq, tld->numa_node, &memid);
  }
  if ((&heap[heap_idx]) == 0)
  {
    _mi_error_message(12, "unable to allocate heap meta-data\n");
    return 0;
  }
  heap->memid = memid;
  _mi_heap_init(heap, arena_id, allow_destroy, (uint8_t) heap_tag, tld);
  return heap;
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
mi_heap_t *mi_heap_new_ex(int heap_tag, bool allow_destroy, mi_arena_id_t arena_id)
{
  mi_heap_t *bheap = mi_heap_get_backing();
  (bheap != 0) ? ((void) 0) : (_mi_assert_fail("bheap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 242, __func__));
  return _mi_heap_create(heap_tag, allow_destroy, arena_id, bheap->tld);
}


----------------------------
mi_arena_id_t _mi_arena_id_none(void)
{
  return 0;
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
mi_heap_t *mi_heap_new_ex(int heap_tag, bool allow_destroy, mi_arena_id_t arena_id)
{
  mi_heap_t *bheap = mi_heap_get_backing();
  (bheap != 0) ? ((void) 0) : (_mi_assert_fail("bheap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 242, __func__));
  return _mi_heap_create(heap_tag, allow_destroy, arena_id, bheap->tld);
}


----------------------------
typedef void *mi_arena_id_t
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
  mi_page_t *page = _mi_ptr_page(p);
  return mi_page_heap(page);
}


/*** DEPENDENCIES:
inline static mi_page_t *_mi_ptr_page(const void *p)
{
  ((p == 0) || mi_is_in_heap_region(p)) ? ((void) 0) : (_mi_assert_fail("p==NULL || mi_is_in_heap_region(p)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 638, __func__));
  return _mi_checked_ptr_page(p);
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


// hint:  ['block_idx_ref is a mutable refrence to unsigned int', 'block_idx_ref is a mutable refrence to unsigned int', 'used_count_ref is a mutable refrence to size_t', 'block_idx_ref is a mutable refrence to unsigned int']
bool helper__mi_heap_area_visit_blocks_2(unsigned int * const block_idx_ref, unsigned int * const block_idx_ref, size_t * const used_count_ref, unsigned int * const block_idx_ref, const mi_heap_area_t * const area, void * const arg, mi_heap_t * const heap, const size_t bsize, const size_t ubsize, uint8_t * const block, size_t i, uintptr_t free_map[((1 * (1UL << (13 + 3))) / (sizeof(void *))) / ((1 << 3) * 8)], mi_block_t * const block, uint8_t * const block, size_t i)
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
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
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
inline static size_t mi_ctz(size_t x)
{
  return (x != 0) ? ((size_t) __builtin_ctzll(x)) : ((1 << 3) * 8);
}


----------------------------
None
----------------------------
***/


bool mi_heap_contains_block(mi_heap_t *heap, const void *p)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 553, __func__));
  if ((heap == 0) || (!mi_heap_is_initialized(heap)))
  {
    return 0;
  }
  return heap == mi_heap_of_block(p);
}


/*** DEPENDENCIES:
None
----------------------------
inline static bool mi_heap_is_initialized(const mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 542, __func__));
  return (heap != 0) && (heap != (&_mi_heap_empty));
}


----------------------------
static mi_heap_t *mi_heap_of_block(const void *p)
{
  if (p == 0)
  {
    return 0;
  }
  mi_page_t *page = _mi_ptr_page(p);
  return mi_page_heap(page);
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
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
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
inline static uint8_t *mi_page_start(const mi_page_t *page)
{
  return page->page_start;
}


----------------------------
None
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
typedef struct mi_heap_area_ex_s
{
  mi_heap_area_t area;
  mi_page_t *page;
} mi_heap_area_ex_t
----------------------------
typedef bool mi_heap_area_visit_fun(const mi_heap_t *heap, const mi_heap_area_ex_t *area, void *arg)
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
      (mi_page_heap(page) == heap) ? ((void) 0) : (_mi_assert_fail("mi_page_heap(page) == heap", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 39, __func__));
      count += 1;
      if (!fn(heap, pq, page, arg1, arg2))
      {
        return 0;
      }
      page_idx = next;
    }

  }

  (count == total) ? ((void) 0) : (_mi_assert_fail("count == total", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 47, __func__));
  return 1;
}


----------------------------
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
None
----------------------------
***/


bool _mi_heap_area_visit_blocks(const mi_heap_area_t *area, mi_page_t *page, mi_block_visit_fun *visitor, void *arg)
{
  (area != 0) ? ((void) 0) : (_mi_assert_fail("area != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 614, __func__));
  if (area == 0)
  {
    return 1;
  }
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 616, __func__));
  if (page == 0)
  {
    return 1;
  }
  _mi_page_free_collect(page, 1);
  (page->local_free == 0) ? ((void) 0) : (_mi_assert_fail("page->local_free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 620, __func__));
  if (page->used == 0)
  {
    return 1;
  }
  size_t psize;
  uint8_t * const pstart = mi_page_area(page, &psize);
  mi_heap_t * const heap = mi_page_heap(page);
  const size_t bsize = mi_page_block_size(page);
  const size_t ubsize = mi_page_usable_block_size(page);
  if (page->capacity == 1)
  {
    ((page->used == 1) && (page->free == 0)) ? ((void) 0) : (_mi_assert_fail("page->used == 1 && page->free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 631, __func__));
    return visitor(mi_page_heap(page), area, pstart, ubsize, arg);
  }
  (bsize <= UINT32_MAX) ? ((void) 0) : (_mi_assert_fail("bsize <= UINT32_MAX", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 634, __func__));
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
  uintptr_t free_map[((1 * (1UL << (13 + 3))) / (sizeof(void *))) / ((1 << 3) * 8)];
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
  (page->capacity == (free_count + page->used)) ? ((void) 0) : (_mi_assert_fail("page->capacity == (free_count + page->used)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 681, __func__));
  size_t used_count = 0;
  uint8_t *block = pstart;
  unsigned int block_idx = 0;
  for (size_t i = 0; i < bmapsize; i += 1)
  {
    helper__mi_heap_area_visit_blocks_2(&block_idx, &block_idx, &used_count, &block_idx, area, arg, heap, bsize, ubsize, block, i, free_map, block, block, i);
  }

  (page->used == used_count) ? ((void) 0) : (_mi_assert_fail("page->used == used_count", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 713, __func__));
  return 1;
}


/*** DEPENDENCIES:
None
----------------------------
inline static uintptr_t _mi_divide_up(uintptr_t size, size_t divider)
{
  (divider != 0) ? ((void) 0) : (_mi_assert_fail("divider != 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 463, __func__));
  return (divider == 0) ? (size) : (((size + divider) - 1) / divider);
}


----------------------------
inline static size_t mi_page_usable_block_size(const mi_page_t *page)
{
  return mi_page_block_size(page) - (sizeof(mi_padding_t));
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
inline static mi_heap_t *mi_page_heap(const mi_page_t *page)
{
  return page->heap;
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
typedef bool mi_block_visit_fun(const mi_heap_t *heap, const mi_heap_area_t *area, void *block, size_t block_size, void *arg)
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
inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
}


----------------------------
bool helper__mi_heap_area_visit_blocks_2(unsigned int * const block_idx_ref, unsigned int * const block_idx_ref, size_t * const used_count_ref, unsigned int * const block_idx_ref, const mi_heap_area_t * const area, void * const arg, mi_heap_t * const heap, const size_t bsize, const size_t ubsize, uint8_t * const block, size_t i, uintptr_t free_map[((1 * (1UL << (13 + 3))) / (sizeof(void *))) / ((1 << 3) * 8)], mi_block_t * const block, uint8_t * const block, size_t i)
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
static void mi_get_fast_divisor(size_t divisor, uint64_t *magic, size_t *shift)
{
  ((divisor > 0) && (divisor <= UINT32_MAX)) ? ((void) 0) : (_mi_assert_fail("divisor > 0 && divisor <= UINT32_MAX", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 602, __func__));
  *shift = ((1 << 3) * 8) - mi_clz(divisor - 1);
  *magic = (((((uint64_t) 1) << 32) * ((((uint64_t) 1) << (*shift)) - divisor)) / divisor) + 1;
}


----------------------------
void helper__mi_heap_area_visit_blocks_1(size_t * const free_count_ref, size_t psize, uint8_t * const pstart, const size_t bsize, uint8_t * const block, uintptr_t free_map[((1 * (1UL << (13 + 3))) / (sizeof(void *))) / ((1 << 3) * 8)], size_t shift, uint64_t magic, size_t shift, mi_block_t * const block, uint8_t * const block)
{
  size_t free_count = *free_count_ref;
  free_count += 1;
  ((((uint8_t *) block) >= pstart) && (((uint8_t *) block) < (pstart + psize))) ? ((void) 0) : (_mi_assert_fail("(uint8_t*)block >= pstart && (uint8_t*)block < (pstart + psize)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 670, __func__));
  size_t offset = ((uint8_t *) block) - pstart;
  ((offset % bsize) == 0) ? ((void) 0) : (_mi_assert_fail("offset % bsize == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 672, __func__));
  (offset <= UINT32_MAX) ? ((void) 0) : (_mi_assert_fail("offset <= UINT32_MAX", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 673, __func__));
  size_t blockidx = mi_fast_divide(offset, magic, shift);
  (blockidx == (offset / bsize)) ? ((void) 0) : (_mi_assert_fail("blockidx == offset / bsize", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 675, __func__));
  (blockidx < ((1 * (1UL << (13 + 3))) / (sizeof(void *)))) ? ((void) 0) : (_mi_assert_fail("blockidx < MI_MAX_BLOCKS", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 676, __func__));
  size_t bitidx = blockidx / ((1 << 3) * 8);
  size_t bit = blockidx - (bitidx * ((1 << 3) * 8));
  free_map[bitidx] |= ((uintptr_t) 1) << bit;
  *free_count_ref = free_count;
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
bool _mi_heap_area_visit_blocks(const mi_heap_area_t *area, mi_page_t *page, mi_block_visit_fun *visitor, void *arg)
{
  (area != 0) ? ((void) 0) : (_mi_assert_fail("area != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 614, __func__));
  if (area == 0)
  {
    return 1;
  }
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 616, __func__));
  if (page == 0)
  {
    return 1;
  }
  _mi_page_free_collect(page, 1);
  (page->local_free == 0) ? ((void) 0) : (_mi_assert_fail("page->local_free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 620, __func__));
  if (page->used == 0)
  {
    return 1;
  }
  size_t psize;
  uint8_t * const pstart = mi_page_area(page, &psize);
  mi_heap_t * const heap = mi_page_heap(page);
  const size_t bsize = mi_page_block_size(page);
  const size_t ubsize = mi_page_usable_block_size(page);
  if (page->capacity == 1)
  {
    ((page->used == 1) && (page->free == 0)) ? ((void) 0) : (_mi_assert_fail("page->used == 1 && page->free == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 631, __func__));
    return visitor(mi_page_heap(page), area, pstart, ubsize, arg);
  }
  (bsize <= UINT32_MAX) ? ((void) 0) : (_mi_assert_fail("bsize <= UINT32_MAX", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 634, __func__));
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
  uintptr_t free_map[((1 * (1UL << (13 + 3))) / (sizeof(void *))) / ((1 << 3) * 8)];
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
  (page->capacity == (free_count + page->used)) ? ((void) 0) : (_mi_assert_fail("page->capacity == (free_count + page->used)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 681, __func__));
  size_t used_count = 0;
  uint8_t *block = pstart;
  unsigned int block_idx = 0;
  for (size_t i = 0; i < bmapsize; i += 1)
  {
    helper__mi_heap_area_visit_blocks_2(&block_idx, &block_idx, &used_count, &block_idx, area, arg, heap, bsize, ubsize, block, i, free_map, block, block, i);
  }

  (page->used == used_count) ? ((void) 0) : (_mi_assert_fail("page->used == used_count", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 713, __func__));
  return 1;
}


----------------------------
typedef struct mi_heap_area_ex_s
{
  mi_heap_area_t area;
  mi_page_t *page;
} mi_heap_area_ex_t
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


mi_heap_t *mi_heap_set_default(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 473, __func__));
  (mi_heap_is_initialized(heap)) ? ((void) 0) : (_mi_assert_fail("mi_heap_is_initialized(heap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 474, __func__));
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
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
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
void _mi_heap_set_default_direct(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/init.c", 590, __func__));
  _mi_heap_default = heap;
  _mi_prim_thread_associate_default_heap(heap);
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
typedef bool mi_block_visit_fun(const mi_heap_t *heap, const mi_heap_area_t *area, void *block, size_t block_size, void *arg)
----------------------------
typedef struct mi_visit_blocks_args_s
{
  bool visit_blocks;
  mi_block_visit_fun *visitor;
  void *arg;
} mi_visit_blocks_args_t
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
None
----------------------------
***/


void mi_heap_unload(mi_heap_t *heap)
{
  (mi_heap_is_initialized(heap)) ? ((void) 0) : (_mi_assert_fail("mi_heap_is_initialized(heap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 487, __func__));
  ;
  if ((heap == 0) || (!mi_heap_is_initialized(heap)))
  {
    return;
  }
  if (heap->exclusive_arena == 0)
  {
    _mi_warning_message("cannot unload heaps that are not associated with an exclusive arena\n");
    return;
  }
  _mi_heap_collect_abandon(heap);
  (heap->page_count == 0) ? ((void) 0) : (_mi_assert_fail("heap->page_count==0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 497, __func__));
  mi_heap_free(heap, 0);
  heap->tld = 0;
  return;
}


/*** DEPENDENCIES:
None
----------------------------
inline static bool mi_heap_is_initialized(const mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 542, __func__));
  return (heap != 0) && (heap != (&_mi_heap_empty));
}


----------------------------
None
----------------------------
void _mi_heap_collect_abandon(mi_heap_t *heap)
{
  mi_heap_collect_ex(heap, MI_ABANDON);
}


----------------------------
static void mi_heap_free(mi_heap_t *heap, bool do_free_mem)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 281, __func__));
  (mi_heap_is_initialized(heap)) ? ((void) 0) : (_mi_assert_fail("mi_heap_is_initialized(heap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 282, __func__));
  if ((heap == 0) || (!mi_heap_is_initialized(heap)))
  {
    return;
  }
  if (mi_heap_is_backing(heap))
  {
    return;
  }
  if (mi_heap_is_default(heap))
  {
    _mi_heap_set_default_direct(heap->tld->heap_backing);
  }
  mi_heap_t *prev = 0;
  unsigned int prev_idx = 0;
  mi_heap_t *curr = heap->tld->heaps;
  unsigned int curr_idx = 0;
  while (((&curr[curr_idx]) != heap) && ((&curr[curr_idx]) != 0))
  {
    prev_idx = &curr[curr_idx];
    curr_idx = curr_idx->next;
  }

  ((&curr[curr_idx]) == heap) ? ((void) 0) : (_mi_assert_fail("curr == heap", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 299, __func__));
  if ((&curr[curr_idx]) == heap)
  {
    if ((&prev[prev_idx]) != 0)
    {
      prev->next = heap->next;
    }
    else
    {
      heap->tld->heaps = heap->next;
    }
  }
  (heap->tld->heaps != 0) ? ((void) 0) : (_mi_assert_fail("heap->tld->heaps != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 304, __func__));
  if (do_free_mem)
  {
    _mi_meta_free(heap, sizeof(*heap), heap->memid);
  }
}


----------------------------
None
----------------------------
***/


bool mi_heap_reload(mi_heap_t *heap, mi_arena_id_t arena_id)
{
  (mi_heap_is_initialized(heap)) ? ((void) 0) : (_mi_assert_fail("mi_heap_is_initialized(heap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 508, __func__));
  if ((heap == 0) || (!mi_heap_is_initialized(heap)))
  {
    return 0;
  }
  if (heap->exclusive_arena == 0)
  {
    _mi_warning_message("cannot reload heaps that were not associated with an exclusive arena\n");
    return 0;
  }
  if (heap->tld != 0)
  {
    _mi_warning_message("cannot reload heaps that were not unloaded first\n");
    return 0;
  }
  mi_arena_t *arena = _mi_arena_from_id(arena_id);
  if (heap->exclusive_arena != arena)
  {
    _mi_warning_message("trying to reload a heap at a different arena address: %p vs %p\n", heap->exclusive_arena, arena);
    return 0;
  }
  (heap->page_count == 0) ? ((void) 0) : (_mi_assert_fail("heap->page_count==0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 524, __func__));
  heap->tld = mi_heap_get_default()->tld;
  (heap->page_count == 0) ? ((void) 0) : (_mi_assert_fail("heap->page_count == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/heap.c", 530, __func__));
  for (size_t i = 0; i < ((128 + ((((sizeof(mi_padding_t)) + (1 << 3)) - 1) / (1 << 3))) + 1); i += 1)
  {
    heap->pages_free_direct[i] = (mi_page_t *) (&_mi_page_empty);
  }

  heap->next = heap->tld->heaps;
  heap->tld->heaps = heap;
  return 1;
}


/*** DEPENDENCIES:
None
----------------------------
inline static bool mi_heap_is_initialized(const mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 542, __func__));
  return (heap != 0) && (heap != (&_mi_heap_empty));
}


----------------------------
None
----------------------------
typedef void *mi_arena_id_t
----------------------------
mi_arena_t *_mi_arena_from_id(mi_arena_id_t id)
{
  return (mi_arena_t *) id;
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
extern const mi_page_t _mi_page_empty
----------------------------
None
----------------------------
***/


