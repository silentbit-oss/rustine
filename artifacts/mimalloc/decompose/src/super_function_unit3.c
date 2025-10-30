// element in merge of:  _mi_free_delayed_block,_mi_heap_collect_abandon,_mi_heap_delayed_free_all,_mi_heap_delayed_free_partial,_mi_prim_thread_init_auto_done,_mi_thread_done,_mi_thread_heap_done,mi_free,mi_free_block_local,mi_free_block_mt,mi_free_generic_mt,mi_heap_collect_ex,mi_heap_delete,mi_heap_free,mi_heap_get_default,mi_process_init,mi_process_setup_auto_thread_done,mi_pthread_done,mi_stat_free,mi_stats_get_default,mi_stats_reset,mi_thread_init
void _mi_heap_collect_abandon(mi_heap_t *heap)
{
  mi_heap_collect_ex(heap, MI_ABANDON);
}


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
***/


// element in merge of:  _mi_free_delayed_block,_mi_heap_collect_abandon,_mi_heap_delayed_free_all,_mi_heap_delayed_free_partial,_mi_prim_thread_init_auto_done,_mi_thread_done,_mi_thread_heap_done,mi_free,mi_free_block_local,mi_free_block_mt,mi_free_generic_mt,mi_heap_collect_ex,mi_heap_delete,mi_heap_free,mi_heap_get_default,mi_process_init,mi_process_setup_auto_thread_done,mi_pthread_done,mi_stat_free,mi_stats_get_default,mi_stats_reset,mi_thread_init
static void mi_free_block_mt(mi_page_t *page, mi_segment_t *segment, mi_block_t *block)
{
  if (((_mi_option_get_fast(mi_option_abandoned_reclaim_on_free) != 0) && (atomic_load_explicit(&segment->thread_id, memory_order_relaxed) == 0)) && (mi_prim_get_default_heap() != ((mi_heap_t *) (&_mi_heap_empty))))
  {
    if (_mi_segment_attempt_reclaim(mi_heap_get_default(), segment))
    {
      (_mi_thread_id() == atomic_load_explicit(&segment->thread_id, memory_order_relaxed)) ? ((void) 0) : (_mi_assert_fail("_mi_thread_id() == mi_atomic_load_relaxed(&segment->thread_id)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 264, __func__));
      (mi_heap_get_default()->tld->segments.subproc == segment->subproc) ? ((void) 0) : (_mi_assert_fail("mi_heap_get_default()->tld->segments.subproc == segment->subproc", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 265, __func__));
      mi_free(block);
      return;
    }
  }
  mi_check_padding(page, block);
  mi_stat_free(page, block);
  ;
  _mi_padding_shrink(page, block, sizeof(mi_block_t));
  if (segment->kind == MI_SEGMENT_HUGE)
  {
    _mi_segment_huge_page_reset(segment, page, block);
  }
  else
  {
    memset(block, 0xDF, mi_usable_size(block));
  }
  mi_free_block_delayed_mt(page, block);
}


/*** DEPENDENCIES:
static void mi_free_block_delayed_mt(mi_page_t *page, mi_block_t *block)
{
  mi_thread_free_t tfreex;
  bool use_delayed;
  mi_thread_free_t tfree = atomic_load_explicit(&page->xthread_free, memory_order_relaxed);
  do
  {
    use_delayed = mi_tf_delayed(tfree) == MI_USE_DELAYED_FREE;
    if (__builtin_expect(!(!use_delayed), 0))
    {
      tfreex = mi_tf_set_delayed(tfree, MI_DELAYED_FREEING);
    }
    else
    {
      mi_block_set_next(page, block, mi_tf_block(tfree));
      tfreex = mi_tf_set_block(tfree, block);
    }
  }
  while (!atomic_compare_exchange_weak_explicit(&page->xthread_free, &tfree, tfreex, memory_order_release, memory_order_relaxed));
  if (__builtin_expect(!(!use_delayed), 0))
  {
    mi_heap_t * const heap = (mi_heap_t *) atomic_load_explicit(&page->xheap, memory_order_acquire);
    (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 232, __func__));
    if (heap != 0)
    {
      mi_block_t *dfree = atomic_load_explicit(&heap->thread_delayed_free, memory_order_relaxed);
      do
      {
        mi_block_set_nextx(heap, block, dfree, heap->keys);
      }
      while (!atomic_compare_exchange_weak_explicit(&heap->thread_delayed_free, &dfree, block, memory_order_release, memory_order_relaxed));
    }
    tfree = atomic_load_explicit(&page->xthread_free, memory_order_relaxed);
    do
    {
      tfreex = tfree;
      (mi_tf_delayed(tfree) == MI_DELAYED_FREEING) ? ((void) 0) : (_mi_assert_fail("mi_tf_delayed(tfree) == MI_DELAYED_FREEING", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 245, __func__));
      tfreex = mi_tf_set_delayed(tfree, MI_NO_DELAYED_FREE);
    }
    while (!atomic_compare_exchange_weak_explicit(&page->xthread_free, &tfree, tfreex, memory_order_release, memory_order_relaxed));
  }
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
None
----------------------------
void _mi_segment_huge_page_reset(mi_segment_t *segment, mi_page_t *page, mi_block_t *block)
{
  (void) page;
  (segment->kind == MI_SEGMENT_HUGE) ? ((void) 0) : (_mi_assert_fail("segment->kind == MI_SEGMENT_HUGE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c", 1628, __func__));
  (segment == _mi_page_segment(page)) ? ((void) 0) : (_mi_assert_fail("segment == _mi_page_segment(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c", 1629, __func__));
  (page->used == 1) ? ((void) 0) : (_mi_assert_fail("page->used == 1", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c", 1630, __func__));
  (page->free == 0) ? ((void) 0) : (_mi_assert_fail("page->free == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c", 1631, __func__));
  if (segment->allow_decommit)
  {
    size_t csize = mi_usable_size(block);
    if (csize > (sizeof(mi_block_t)))
    {
      csize = csize - (sizeof(mi_block_t));
      uint8_t *p = ((uint8_t *) block) + (sizeof(mi_block_t));
      _mi_os_reset(p, csize);
    }
  }
}


----------------------------
extern const mi_heap_t _mi_heap_empty
----------------------------
bool _mi_segment_attempt_reclaim(mi_heap_t *heap, mi_segment_t *segment)
{
  if (atomic_load_explicit(&segment->thread_id, memory_order_relaxed) != 0)
  {
    return 0;
  }
  if (segment->subproc != heap->tld->segments.subproc)
  {
    return 0;
  }
  if (!_mi_heap_memid_is_suitable(heap, segment->memid))
  {
    return 0;
  }
  const long target = _mi_option_get_fast(mi_option_target_segments_per_thread);
  if ((target > 0) && (((size_t) target) <= heap->tld->segments.count))
  {
    return 0;
  }
  if ((segment->memid.memkind == MI_MEM_ARENA) && ((heap->tld->segments.reclaim_count * 2) > heap->tld->segments.count))
  {
    return 0;
  }
  if (_mi_arena_segment_clear_abandoned(segment))
  {
    mi_segment_t *res = mi_segment_reclaim(segment, heap, 0, 0, &heap->tld->segments);
    (res == segment) ? ((void) 0) : (_mi_assert_fail("res == segment", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c", 1296, __func__));
    return res != 0;
  }
  return 0;
}


----------------------------
None
----------------------------
long _mi_option_get_fast(mi_option_t option)
{
  ((option >= 0) && (option < _mi_option_last)) ? ((void) 0) : (_mi_assert_fail("option >= 0 && option < _mi_option_last", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/options.c", 238, __func__));
  mi_option_desc_t *desc = &options[option];
  (desc->option == option) ? ((void) 0) : (_mi_assert_fail("desc->option == option", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/options.c", 240, __func__));
  return desc->value;
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
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
static void mi_check_padding(const mi_page_t *page, const mi_block_t *block)
{
  size_t size;
  size_t wrong;
  if (!mi_verify_padding(page, block, &size, &wrong))
  {
    _mi_error_message(14, "buffer overflow in heap block %p of size %zu: write after %zu bytes\n", block, size, wrong);
  }
}


----------------------------
size_t mi_usable_size(const void *p)
{
  return _mi_usable_size(p, "mi_usable_size");
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


// element in merge of:  _mi_free_delayed_block,_mi_heap_collect_abandon,_mi_heap_delayed_free_all,_mi_heap_delayed_free_partial,_mi_prim_thread_init_auto_done,_mi_thread_done,_mi_thread_heap_done,mi_free,mi_free_block_local,mi_free_block_mt,mi_free_generic_mt,mi_heap_collect_ex,mi_heap_delete,mi_heap_free,mi_heap_get_default,mi_process_init,mi_process_setup_auto_thread_done,mi_pthread_done,mi_stat_free,mi_stats_get_default,mi_stats_reset,mi_thread_init
static void mi_free_generic_mt(mi_page_t *page, mi_segment_t *segment, void *p)
{
  mi_block_t * const block = _mi_page_ptr_unalign(page, p);
  mi_block_check_unguard(page, block, p);
  mi_free_block_mt(page, segment, block);
}


/*** DEPENDENCIES:
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
None
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
inline static void mi_block_check_unguard(mi_page_t *page, mi_block_t *block, void *p)
{
  (void) page;
  (void) block;
  (void) p;
}


----------------------------
None
----------------------------
***/


// element in merge of:  _mi_free_delayed_block,_mi_heap_collect_abandon,_mi_heap_delayed_free_all,_mi_heap_delayed_free_partial,_mi_prim_thread_init_auto_done,_mi_thread_done,_mi_thread_heap_done,mi_free,mi_free_block_local,mi_free_block_mt,mi_free_generic_mt,mi_heap_collect_ex,mi_heap_delete,mi_heap_free,mi_heap_get_default,mi_process_init,mi_process_setup_auto_thread_done,mi_pthread_done,mi_stat_free,mi_stats_get_default,mi_stats_reset,mi_thread_init
static void mi_process_setup_auto_thread_done(void)
{
  static bool tls_initialized = 0;
  if (tls_initialized)
  {
    return;
  }
  tls_initialized = 1;
  _mi_prim_thread_init_auto_done();
  _mi_heap_set_default_direct(&_mi_heap_main);
}


/*** DEPENDENCIES:
void _mi_heap_set_default_direct(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/init.c", 544, __func__));
  _mi_heap_default = heap;
  _mi_prim_thread_associate_default_heap(heap);
}


----------------------------
extern mi_heap_t _mi_heap_main
----------------------------
None
----------------------------
***/


// element in merge of:  _mi_free_delayed_block,_mi_heap_collect_abandon,_mi_heap_delayed_free_all,_mi_heap_delayed_free_partial,_mi_prim_thread_init_auto_done,_mi_thread_done,_mi_thread_heap_done,mi_free,mi_free_block_local,mi_free_block_mt,mi_free_generic_mt,mi_heap_collect_ex,mi_heap_delete,mi_heap_free,mi_heap_get_default,mi_process_init,mi_process_setup_auto_thread_done,mi_pthread_done,mi_stat_free,mi_stats_get_default,mi_stats_reset,mi_thread_init
static void mi_heap_free(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 279, __func__));
  (mi_heap_is_initialized(heap)) ? ((void) 0) : (_mi_assert_fail("mi_heap_is_initialized(heap)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 280, __func__));
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

  ((&curr[curr_idx]) == heap) ? ((void) 0) : (_mi_assert_fail("curr == heap", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 297, __func__));
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
  (heap->tld->heaps != 0) ? ((void) 0) : (_mi_assert_fail("heap->tld->heaps != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 302, __func__));
  mi_free(heap);
}


/*** DEPENDENCIES:
inline static bool mi_heap_is_backing(const mi_heap_t *heap)
{
  return heap->tld->heap_backing == heap;
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
static bool mi_heap_is_default(const mi_heap_t *heap)
{
  return heap == mi_prim_get_default_heap();
}


----------------------------
None
----------------------------
void _mi_heap_set_default_direct(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/init.c", 544, __func__));
  _mi_heap_default = heap;
  _mi_prim_thread_associate_default_heap(heap);
}


----------------------------
None
----------------------------
***/


// element in merge of:  _mi_free_delayed_block,_mi_heap_collect_abandon,_mi_heap_delayed_free_all,_mi_heap_delayed_free_partial,_mi_prim_thread_init_auto_done,_mi_thread_done,_mi_thread_heap_done,mi_free,mi_free_block_local,mi_free_block_mt,mi_free_generic_mt,mi_heap_collect_ex,mi_heap_delete,mi_heap_free,mi_heap_get_default,mi_process_init,mi_process_setup_auto_thread_done,mi_pthread_done,mi_stat_free,mi_stats_get_default,mi_stats_reset,mi_thread_init
void mi_process_init(void)
{
  static mi_atomic_once_t process_init;
  mi_heap_main_init();
  if (!mi_atomic_once(&process_init))
  {
    return;
  }
  _mi_process_is_initialized = 1;
  _mi_verbose_message("process init: 0x%zx\n", _mi_thread_id());
  mi_process_setup_auto_thread_done();
  mi_detect_cpu_features();
  _mi_os_init();
  mi_heap_main_init();
  mi_thread_init();
  mi_stats_reset();
  ;
  if (mi_option_is_enabled(mi_option_reserve_huge_os_pages))
  {
    size_t pages = mi_option_get_clamp(mi_option_reserve_huge_os_pages, 0, 128 * 1024);
    long reserve_at = mi_option_get(mi_option_reserve_huge_os_pages_at);
    if (reserve_at != (-1))
    {
      mi_reserve_huge_os_pages_at(pages, reserve_at, pages * 500);
    }
    else
    {
      mi_reserve_huge_os_pages_interleave(pages, 0, pages * 500);
    }
  }
  if (mi_option_is_enabled(mi_option_reserve_os_memory))
  {
    long ksize = mi_option_get(mi_option_reserve_os_memory);
    if (ksize > 0)
    {
      mi_reserve_os_memory(((size_t) ksize) * 1024UL, 1, 1);
    }
  }
}


/*** DEPENDENCIES:
void _mi_os_init(void)
{
  _mi_prim_mem_init(&mi_os_mem_config);
}


----------------------------
typedef _Atomic uintptr_t mi_atomic_once_t
----------------------------
inline static bool mi_atomic_once(mi_atomic_once_t *once)
{
  if (atomic_load_explicit(once, memory_order_relaxed) != 0)
  {
    return 0;
  }
  uintptr_t expected = 0;
  return atomic_compare_exchange_strong_explicit(once, &expected, (uintptr_t) 1, memory_order_acq_rel, memory_order_acquire);
}


----------------------------
void _mi_verbose_message(const char *fmt, ...)
{
  if (!mi_option_is_enabled(mi_option_verbose))
  {
    return;
  }
  va_list args;
  __builtin_va_start(args);
  mi_vfprintf(0, 0, "mimalloc: ", fmt, args);
  ;
}


----------------------------
static void mi_heap_main_init(void)
{
  if (_mi_heap_main.cookie == 0)
  {
    _mi_heap_main.thread_id = _mi_thread_id();
    _mi_heap_main.cookie = 1;
    _mi_random_init(&_mi_heap_main.random);
    _mi_heap_main.cookie = _mi_heap_random_next(&_mi_heap_main);
    _mi_heap_main.keys[0] = _mi_heap_random_next(&_mi_heap_main);
    _mi_heap_main.keys[1] = _mi_heap_random_next(&_mi_heap_main);
    mi_lock_init(&mi_subproc_default.abandoned_os_lock);
    mi_lock_init(&mi_subproc_default.abandoned_os_visit_lock);
    _mi_heap_guarded_init(&_mi_heap_main);
  }
}


----------------------------
extern bool _mi_process_is_initialized
----------------------------
int mi_reserve_os_memory(size_t size, bool commit, bool allow_large)
{
  return mi_reserve_os_memory_ex(size, commit, allow_large, 0, 0);
}


----------------------------
long mi_option_get_clamp(mi_option_t option, long min, long max)
{
  long x = mi_option_get(option);
  return (x < min) ? (min) : ((x > max) ? (max) : (x));
}


----------------------------
int mi_reserve_huge_os_pages_at(size_t pages, int numa_node, size_t timeout_msecs)
{
  return mi_reserve_huge_os_pages_at_ex(pages, numa_node, timeout_msecs, 0, 0);
}


----------------------------
mi_threadid_t _mi_thread_id(void)
{
  return _mi_prim_thread_id();
}


----------------------------
int mi_reserve_huge_os_pages_interleave(size_t pages, size_t numa_nodes, size_t timeout_msecs)
{
  if (pages == 0)
  {
    return 0;
  }
  int numa_count = ((numa_nodes > 0) && (numa_nodes <= 2147483647)) ? ((int) numa_nodes) : (_mi_os_numa_node_count());
  if (numa_count == 0)
  {
    numa_count = 1;
  }
  const size_t pages_per = pages / numa_count;
  const size_t pages_mod = pages % numa_count;
  const size_t timeout_per = (timeout_msecs == 0) ? (0) : ((timeout_msecs / numa_count) + 50);
  for (int numa_node = 0; (numa_node < numa_count) && (pages > 0); numa_node += 1)
  {
    size_t node_pages = pages_per;
    if (((size_t) numa_node) < pages_mod)
    {
      node_pages += 1;
    }
    int err = mi_reserve_huge_os_pages_at(node_pages, numa_node, timeout_per);
    if (err)
    {
      return err;
    }
    if (pages < node_pages)
    {
      pages = 0;
    }
    else
    {
      pages -= node_pages;
    }
  }

  return 0;
}


----------------------------
static void mi_detect_cpu_features(void)
{
}


----------------------------
None
----------------------------
None
----------------------------
***/


// element in merge of:  _mi_free_delayed_block,_mi_heap_collect_abandon,_mi_heap_delayed_free_all,_mi_heap_delayed_free_partial,_mi_prim_thread_init_auto_done,_mi_thread_done,_mi_thread_heap_done,mi_free,mi_free_block_local,mi_free_block_mt,mi_free_generic_mt,mi_heap_collect_ex,mi_heap_delete,mi_heap_free,mi_heap_get_default,mi_process_init,mi_process_setup_auto_thread_done,mi_pthread_done,mi_stat_free,mi_stats_get_default,mi_stats_reset,mi_thread_init
inline static void mi_free_block_local(mi_page_t *page, mi_block_t *block, bool track_stats, bool check_full)
{
  if (__builtin_expect(!(!mi_check_is_double_free(page, block)), 0))
  {
    return;
  }
  mi_check_padding(page, block);
  if (track_stats)
  {
    mi_stat_free(page, block);
  }
  if (!mi_page_is_huge(page))
  {
    memset(block, 0xDF, mi_page_block_size(page));
  }
  if (track_stats)
  {
    ;
  }
  mi_block_set_next(page, block, page->local_free);
  page->local_free = block;
  if (__builtin_expect(!(!((--page->used) == 0)), 0))
  {
    _mi_page_retire(page);
  }
  else
    if (__builtin_expect(!(!(check_full && mi_page_is_in_full(page))), 0))
  {
    _mi_page_unfull(page);
  }
}


/*** DEPENDENCIES:
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
inline static void mi_block_set_next(const mi_page_t *page, mi_block_t *block, const mi_block_t *next)
{
  mi_block_set_nextx(page, block, next, page->keys);
}


----------------------------
inline static bool mi_check_is_double_free(const mi_page_t *page, const mi_block_t *block)
{
  bool is_double_free = 0;
  mi_block_t *n = mi_block_nextx(page, block, page->keys);
  if (((((uintptr_t) n) & ((1 << 3) - 1)) == 0) && ((n == 0) || mi_is_in_same_page(block, n)))
  {
    is_double_free = mi_check_is_double_freex(page, block);
  }
  return is_double_free;
}


----------------------------
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


----------------------------
inline static bool mi_page_is_in_full(const mi_page_t *page)
{
  return page->flags.x.in_full;
}


----------------------------
static void mi_check_padding(const mi_page_t *page, const mi_block_t *block)
{
  size_t size;
  size_t wrong;
  if (!mi_verify_padding(page, block, &size, &wrong))
  {
    _mi_error_message(14, "buffer overflow in heap block %p of size %zu: write after %zu bytes\n", block, size, wrong);
  }
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


// element in merge of:  _mi_free_delayed_block,_mi_heap_collect_abandon,_mi_heap_delayed_free_all,_mi_heap_delayed_free_partial,_mi_prim_thread_init_auto_done,_mi_thread_done,_mi_thread_heap_done,mi_free,mi_free_block_local,mi_free_block_mt,mi_free_generic_mt,mi_heap_collect_ex,mi_heap_delete,mi_heap_free,mi_heap_get_default,mi_process_init,mi_process_setup_auto_thread_done,mi_pthread_done,mi_stat_free,mi_stats_get_default,mi_stats_reset,mi_thread_init
static mi_stats_t *mi_stats_get_default(void)
{
  mi_heap_t *heap = mi_heap_get_default();
  return &heap->tld->stats;
}


/*** DEPENDENCIES:
None
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
} mi_stats_t
----------------------------
None
----------------------------
***/


// element in merge of:  _mi_free_delayed_block,_mi_heap_collect_abandon,_mi_heap_delayed_free_all,_mi_heap_delayed_free_partial,_mi_prim_thread_init_auto_done,_mi_thread_done,_mi_thread_heap_done,mi_free,mi_free_block_local,mi_free_block_mt,mi_free_generic_mt,mi_heap_collect_ex,mi_heap_delete,mi_heap_free,mi_heap_get_default,mi_process_init,mi_process_setup_auto_thread_done,mi_pthread_done,mi_stat_free,mi_stats_get_default,mi_stats_reset,mi_thread_init
bool _mi_free_delayed_block(mi_block_t *block)
{
  (block != 0) ? ((void) 0) : (_mi_assert_fail("block!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 178, __func__));
  const mi_segment_t * const segment = _mi_ptr_segment(block);
  (_mi_ptr_cookie(segment) == segment->cookie) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_cookie(segment) == segment->cookie", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 180, __func__));
  (_mi_thread_id() == segment->thread_id) ? ((void) 0) : (_mi_assert_fail("_mi_thread_id() == segment->thread_id", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 181, __func__));
  mi_page_t * const page = _mi_segment_page_of(segment, block);
  if (!_mi_page_try_use_delayed_free(page, MI_USE_DELAYED_FREE, 0))
  {
    return 0;
  }
  _mi_page_free_collect(page, 0);
  mi_free_block_local(page, block, 0, 1);
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
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
inline static mi_segment_t *_mi_ptr_segment(const void *p)
{
  mi_segment_t * const segment = (mi_segment_t *) ((((uintptr_t) p) - 1) & (~((uintptr_t) ((1UL << (9 + (13 + 3))) - 1))));
  return (((intptr_t) segment) <= 0) ? (0) : (segment);
}


----------------------------
None
----------------------------
inline static uintptr_t _mi_ptr_cookie(const void *p)
{
  extern mi_heap_t _mi_heap_main;
  (_mi_heap_main.cookie != 0) ? ((void) 0) : (_mi_assert_fail("_mi_heap_main.cookie != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 507, __func__));
  return ((uintptr_t) p) ^ _mi_heap_main.cookie;
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
mi_threadid_t _mi_thread_id(void)
{
  return _mi_prim_thread_id();
}


----------------------------
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
None
----------------------------
***/


// element in merge of:  _mi_free_delayed_block,_mi_heap_collect_abandon,_mi_heap_delayed_free_all,_mi_heap_delayed_free_partial,_mi_prim_thread_init_auto_done,_mi_thread_done,_mi_thread_heap_done,mi_free,mi_free_block_local,mi_free_block_mt,mi_free_generic_mt,mi_heap_collect_ex,mi_heap_delete,mi_heap_free,mi_heap_get_default,mi_process_init,mi_process_setup_auto_thread_done,mi_pthread_done,mi_stat_free,mi_stats_get_default,mi_stats_reset,mi_thread_init
void _mi_thread_done(mi_heap_t *heap)
{
  unsigned int heap_idx = 0;
  if ((&heap[heap_idx]) == 0)
  {
    heap_idx = mi_prim_get_default_heap();
    if ((&heap[heap_idx]) == 0)
    {
      return;
    }
  }
  if (!mi_heap_is_initialized(heap))
  {
    return;
  }
  atomic_fetch_sub_explicit(&thread_count, (uintptr_t) 1, memory_order_relaxed);
  _mi_stat_decrease(&_mi_stats_main.threads, 1);
  if (heap->thread_id != _mi_thread_id())
  {
    return;
  }
  if (_mi_thread_heap_done(heap))
  {
    return;
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
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
static _Atomic size_t thread_count = 1
----------------------------
extern mi_stats_t _mi_stats_main
----------------------------
mi_threadid_t _mi_thread_id(void)
{
  return _mi_prim_thread_id();
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


// element in merge of:  _mi_free_delayed_block,_mi_heap_collect_abandon,_mi_heap_delayed_free_all,_mi_heap_delayed_free_partial,_mi_prim_thread_init_auto_done,_mi_thread_done,_mi_thread_heap_done,mi_free,mi_free_block_local,mi_free_block_mt,mi_free_generic_mt,mi_heap_collect_ex,mi_heap_delete,mi_heap_free,mi_heap_get_default,mi_process_init,mi_process_setup_auto_thread_done,mi_pthread_done,mi_stat_free,mi_stats_get_default,mi_stats_reset,mi_thread_init
void mi_stats_reset(void)
{
  mi_stats_t *stats = mi_stats_get_default();
  if (stats != (&_mi_stats_main))
  {
    memset(stats, 0, sizeof(mi_stats_t));
  }
  memset(&_mi_stats_main, 0, sizeof(mi_stats_t));
  if (mi_process_start == 0)
  {
    mi_process_start = _mi_clock_start();
  }
  ;
}


/*** DEPENDENCIES:
static mi_msecs_t mi_process_start
----------------------------
mi_msecs_t _mi_clock_start(void)
{
  if (mi_clock_diff == 0.0)
  {
    mi_msecs_t t0 = _mi_clock_now();
    mi_clock_diff = _mi_clock_now() - t0;
  }
  return _mi_clock_now();
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
} mi_stats_t
----------------------------
extern mi_stats_t _mi_stats_main
----------------------------
None
----------------------------
***/


// element in merge of:  _mi_free_delayed_block,_mi_heap_collect_abandon,_mi_heap_delayed_free_all,_mi_heap_delayed_free_partial,_mi_prim_thread_init_auto_done,_mi_thread_done,_mi_thread_heap_done,mi_free,mi_free_block_local,mi_free_block_mt,mi_free_generic_mt,mi_heap_collect_ex,mi_heap_delete,mi_heap_free,mi_heap_get_default,mi_process_init,mi_process_setup_auto_thread_done,mi_pthread_done,mi_stat_free,mi_stats_get_default,mi_stats_reset,mi_thread_init
void mi_heap_delete(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 475, __func__));
  (mi_heap_is_initialized(heap)) ? ((void) 0) : (_mi_assert_fail("mi_heap_is_initialized(heap)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 476, __func__));
  ;
  if ((heap == 0) || (!mi_heap_is_initialized(heap)))
  {
    return;
  }
  mi_heap_t *bheap = heap->tld->heap_backing;
  if ((bheap != heap) && mi_heaps_are_compatible(bheap, heap))
  {
    mi_heap_absorb(bheap, heap);
  }
  else
  {
    _mi_heap_collect_abandon(heap);
  }
  (heap->page_count == 0) ? ((void) 0) : (_mi_assert_fail("heap->page_count==0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 489, __func__));
  mi_heap_free(heap);
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
static bool mi_heaps_are_compatible(mi_heap_t *heap1, mi_heap_t *heap2)
{
  return (heap1->tag == heap2->tag) && (heap1->arena_id == heap2->arena_id);
}


----------------------------
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


----------------------------
None
----------------------------
***/


// element in merge of:  _mi_free_delayed_block,_mi_heap_collect_abandon,_mi_heap_delayed_free_all,_mi_heap_delayed_free_partial,_mi_prim_thread_init_auto_done,_mi_thread_done,_mi_thread_heap_done,mi_free,mi_free_block_local,mi_free_block_mt,mi_free_generic_mt,mi_heap_collect_ex,mi_heap_delete,mi_heap_free,mi_heap_get_default,mi_process_init,mi_process_setup_auto_thread_done,mi_pthread_done,mi_stat_free,mi_stats_get_default,mi_stats_reset,mi_thread_init
void mi_free(void *p)
{
  mi_segment_t * const segment = mi_checked_ptr_segment(p, "mi_free");
  if (__builtin_expect(!(!(segment == 0)), 0))
  {
    return;
  }
  const bool is_local = _mi_prim_thread_id() == atomic_load_explicit(&segment->thread_id, memory_order_relaxed);
  mi_page_t * const page = _mi_segment_page_of(segment, p);
  if (__builtin_expect(!(!is_local), 1))
  {
    if (__builtin_expect(!(!(page->flags.full_aligned == 0)), 1))
    {
      mi_block_t * const block = (mi_block_t *) p;
      mi_free_block_local(page, block, 1, 0);
    }
    else
    {
      mi_free_generic_local(page, segment, p);
    }
  }
  else
  {
    mi_free_generic_mt(page, segment, p);
  }
}


/*** DEPENDENCIES:
static void mi_free_generic_local(mi_page_t *page, mi_segment_t *segment, void *p)
{
  (void) segment;
  mi_block_t * const block = (mi_page_has_aligned(page)) ? (_mi_page_ptr_unalign(page, p)) : ((mi_block_t *) p);
  mi_block_check_unguard(page, block, p);
  mi_free_block_local(page, block, 1, 1);
}


----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
None
----------------------------
inline static mi_threadid_t _mi_prim_thread_id(void)
{
  return (uintptr_t) __builtin_thread_pointer();
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
inline static mi_segment_t *mi_checked_ptr_segment(const void *p, const char *msg)
{
  (void) msg;
  if (__builtin_expect(!(!(((((uintptr_t) p) & ((1 << 3) - 1)) != 0) && (!mi_option_is_enabled(mi_option_guarded_precise)))), 0))
  {
    _mi_error_message(22, "%s: invalid (unaligned) pointer: %p\n", msg, p);
    return 0;
  }
  mi_segment_t * const segment = _mi_ptr_segment(p);
  if (__builtin_expect(!(!(segment == 0)), 0))
  {
    return segment;
  }
  if (__builtin_expect(!(!(!mi_is_in_heap_region(p))), 0))
  {
    if ((((uintptr_t) p) >> 40) != 0x7F)
    {
      _mi_warning_message("%s: pointer might not point to a valid heap region: %p\n(this may still be a valid very large allocation (over 64MiB))\n", msg, p);
      if (__builtin_expect(!(!(_mi_ptr_cookie(segment) == segment->cookie)), 1))
      {
        _mi_warning_message("(yes, the previous pointer %p was valid after all)\n", p);
      }
    }
  }
  if (__builtin_expect(!(!(_mi_ptr_cookie(segment) != segment->cookie)), 0))
  {
    _mi_error_message(22, "%s: pointer does not point to a valid heap space: %p\n", msg, p);
    return 0;
  }
  return segment;
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


// element in merge of:  _mi_free_delayed_block,_mi_heap_collect_abandon,_mi_heap_delayed_free_all,_mi_heap_delayed_free_partial,_mi_prim_thread_init_auto_done,_mi_thread_done,_mi_thread_heap_done,mi_free,mi_free_block_local,mi_free_block_mt,mi_free_generic_mt,mi_heap_collect_ex,mi_heap_delete,mi_heap_free,mi_heap_get_default,mi_process_init,mi_process_setup_auto_thread_done,mi_pthread_done,mi_stat_free,mi_stats_get_default,mi_stats_reset,mi_thread_init
static void mi_heap_collect_ex(mi_heap_t *heap, mi_collect_t collect)
{
  if ((heap == 0) || (!mi_heap_is_initialized(heap)))
  {
    return;
  }
  const bool force = collect >= MI_FORCE;
  _mi_deferred_free(heap, force);
  const bool is_main_thread = _mi_is_main_thread() && (heap->thread_id == _mi_thread_id());
  const bool force_main = (((collect >= MI_FORCE) && is_main_thread) && mi_heap_is_backing(heap)) && (!heap->no_reclaim);
  if (force_main)
  {
    _mi_abandoned_reclaim_all(heap, &heap->tld->segments);
  }
  if (collect == MI_ABANDON)
  {
    mi_heap_visit_pages(heap, &mi_heap_page_never_delayed_free, 0, 0);
  }
  _mi_heap_delayed_free_all(heap);
  _mi_heap_collect_retired(heap, force);
  mi_heap_visit_pages(heap, &mi_heap_page_collect, &collect, 0);
  ((collect != MI_ABANDON) || (atomic_load_explicit(&heap->thread_delayed_free, memory_order_acquire) == 0)) ? ((void) 0) : (_mi_assert_fail("collect != MI_ABANDON || mi_atomic_load_ptr_acquire(mi_block_t,&heap->thread_delayed_free) == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/heap.c", 164, __func__));
  _mi_abandoned_collect(heap, collect == MI_FORCE, &heap->tld->segments);
  if ((force && is_main_thread) && mi_heap_is_backing(heap))
  {
    _mi_thread_data_collect();
  }
  _mi_arenas_collect(collect == MI_FORCE);
  if (collect <= MI_FORCE)
  {
    _mi_stats_merge_thread(heap->tld);
  }
}


/*** DEPENDENCIES:
void _mi_stats_merge_thread(mi_tld_t *tld)
{
  mi_stats_merge_from(&tld->stats);
}


----------------------------
static bool mi_heap_page_never_delayed_free(mi_heap_t *heap, mi_page_queue_t *pq, mi_page_t *page, void *arg1, void *arg2)
{
  (void) arg1;
  (void) arg2;
  (void) heap;
  (void) pq;
  _mi_page_use_delayed_free(page, MI_NEVER_DELAYED_FREE, 0);
  return 1;
}


----------------------------
inline static bool mi_heap_is_backing(const mi_heap_t *heap)
{
  return heap->tld->heap_backing == heap;
}


----------------------------
inline static bool mi_heap_is_initialized(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 501, __func__));
  return (heap != 0) && (heap != (&_mi_heap_empty));
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
None
----------------------------
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


----------------------------
void _mi_abandoned_collect(mi_heap_t *heap, bool force, mi_segments_tld_t *tld)
{
  mi_segment_t *segment;
  unsigned int segment_idx = 0;
  mi_arena_field_cursor_t current;
  _mi_arena_field_cursor_init(heap, tld->subproc, force, &current);
  long max_tries = (force) ? ((long) atomic_load_explicit(&tld->subproc->abandoned_count, memory_order_relaxed)) : (1024);
  while (((max_tries--) > 0) && ((segment_idx = _mi_arena_segment_clear_abandoned_next(&current)) != 0))
  {
    mi_segment_check_free(segment, 0, 0, tld);
    if (segment->used == 0)
    {
      mi_segment_reclaim(segment, heap, 0, 0, tld);
    }
    else
    {
      mi_segment_try_purge(segment, force);
      _mi_arena_segment_mark_abandoned(segment);
    }
  }

  _mi_arena_field_cursor_done(&current);
}


----------------------------
bool _mi_is_main_thread(void)
{
  return (_mi_heap_main.thread_id == 0) || (_mi_heap_main.thread_id == _mi_thread_id());
}


----------------------------
typedef enum mi_collect_e
{
  MI_NORMAL,
  MI_FORCE,
  MI_ABANDON
} mi_collect_t
----------------------------
void _mi_arenas_collect(bool force_purge)
{
  mi_arenas_try_purge(force_purge, force_purge);
}


----------------------------
void _mi_abandoned_reclaim_all(mi_heap_t *heap, mi_segments_tld_t *tld)
{
  mi_segment_t *segment;
  unsigned int segment_idx = 0;
  mi_arena_field_cursor_t current;
  _mi_arena_field_cursor_init(heap, tld->subproc, 1, &current);
  while ((segment_idx = _mi_arena_segment_clear_abandoned_next(&current)) != 0)
  {
    mi_segment_reclaim(segment, heap, 0, 0, tld);
  }

  _mi_arena_field_cursor_done(&current);
}


----------------------------
void _mi_thread_data_collect(void)
{
  for (int i = 0; i < 32; i += 1)
  {
    mi_thread_data_t *td = atomic_load_explicit(&td_cache[i], memory_order_relaxed);
    unsigned int td_idx = 0;
    if ((&td[td_idx]) != 0)
    {
      td_idx = atomic_exchange_explicit(&td_cache[i], 0, memory_order_acq_rel);
      if ((&td[td_idx]) != 0)
      {
        _mi_os_free(td, sizeof(mi_thread_data_t), td->memid);
      }
    }
  }

}


----------------------------
mi_threadid_t _mi_thread_id(void)
{
  return _mi_prim_thread_id();
}


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


// element in merge of:  _mi_free_delayed_block,_mi_heap_collect_abandon,_mi_heap_delayed_free_all,_mi_heap_delayed_free_partial,_mi_prim_thread_init_auto_done,_mi_thread_done,_mi_thread_heap_done,mi_free,mi_free_block_local,mi_free_block_mt,mi_free_generic_mt,mi_heap_collect_ex,mi_heap_delete,mi_heap_free,mi_heap_get_default,mi_process_init,mi_process_setup_auto_thread_done,mi_pthread_done,mi_stat_free,mi_stats_get_default,mi_stats_reset,mi_thread_init
void _mi_heap_delayed_free_all(mi_heap_t *heap)
{
  while (!_mi_heap_delayed_free_partial(heap))
  {
    mi_atomic_yield();
  }

}


/*** DEPENDENCIES:
None
----------------------------
inline static void mi_atomic_yield(void)
{
}


----------------------------
None
----------------------------
***/


// element in merge of:  _mi_free_delayed_block,_mi_heap_collect_abandon,_mi_heap_delayed_free_all,_mi_heap_delayed_free_partial,_mi_prim_thread_init_auto_done,_mi_thread_done,_mi_thread_heap_done,mi_free,mi_free_block_local,mi_free_block_mt,mi_free_generic_mt,mi_heap_collect_ex,mi_heap_delete,mi_heap_free,mi_heap_get_default,mi_process_init,mi_process_setup_auto_thread_done,mi_pthread_done,mi_stat_free,mi_stats_get_default,mi_stats_reset,mi_thread_init
static void mi_pthread_done(void *value)
{
  if (value != 0)
  {
    _mi_thread_done((mi_heap_t *) value);
  }
}


/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  _mi_free_delayed_block,_mi_heap_collect_abandon,_mi_heap_delayed_free_all,_mi_heap_delayed_free_partial,_mi_prim_thread_init_auto_done,_mi_thread_done,_mi_thread_heap_done,mi_free,mi_free_block_local,mi_free_block_mt,mi_free_generic_mt,mi_heap_collect_ex,mi_heap_delete,mi_heap_free,mi_heap_get_default,mi_process_init,mi_process_setup_auto_thread_done,mi_pthread_done,mi_stat_free,mi_stats_get_default,mi_stats_reset,mi_thread_init
void _mi_prim_thread_init_auto_done(void)
{
  (_mi_heap_default_key == ((pthread_key_t) (-1))) ? ((void) 0) : (_mi_assert_fail("_mi_heap_default_key == (pthread_key_t)(-1)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/prim/unix/prim.c", 904, __func__));
  pthread_key_create(&_mi_heap_default_key, &mi_pthread_done);
}


/*** DEPENDENCIES:
None
----------------------------
pthread_key_t _mi_heap_default_key = (pthread_key_t) (-1)
----------------------------
None
----------------------------
***/


// element in merge of:  _mi_free_delayed_block,_mi_heap_collect_abandon,_mi_heap_delayed_free_all,_mi_heap_delayed_free_partial,_mi_prim_thread_init_auto_done,_mi_thread_done,_mi_thread_heap_done,mi_free,mi_free_block_local,mi_free_block_mt,mi_free_generic_mt,mi_heap_collect_ex,mi_heap_delete,mi_heap_free,mi_heap_get_default,mi_process_init,mi_process_setup_auto_thread_done,mi_pthread_done,mi_stat_free,mi_stats_get_default,mi_stats_reset,mi_thread_init
mi_heap_t *mi_heap_get_default(void)
{
  mi_thread_init();
  return mi_prim_get_default_heap();
}


/*** DEPENDENCIES:
None
----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
None
----------------------------
***/


// element in merge of:  _mi_free_delayed_block,_mi_heap_collect_abandon,_mi_heap_delayed_free_all,_mi_heap_delayed_free_partial,_mi_prim_thread_init_auto_done,_mi_thread_done,_mi_thread_heap_done,mi_free,mi_free_block_local,mi_free_block_mt,mi_free_generic_mt,mi_heap_collect_ex,mi_heap_delete,mi_heap_free,mi_heap_get_default,mi_process_init,mi_process_setup_auto_thread_done,mi_pthread_done,mi_stat_free,mi_stats_get_default,mi_stats_reset,mi_thread_init
bool _mi_heap_delayed_free_partial(mi_heap_t *heap)
{
  mi_block_t *block = atomic_load_explicit(&heap->thread_delayed_free, memory_order_relaxed);
  unsigned int block_idx = 0;
  while (((&block[block_idx]) != 0) && (!atomic_compare_exchange_weak_explicit(&heap->thread_delayed_free, &(&block[block_idx]), 0, memory_order_acq_rel, memory_order_acquire)))
  {
  }

  ;
  bool all_freed = 1;
  while ((&block[block_idx]) != 0)
  {
    mi_block_t *next = mi_block_nextx(heap, block, heap->keys);
    if (!_mi_free_delayed_block(block))
    {
      all_freed = 0;
      mi_block_t *dfree = atomic_load_explicit(&heap->thread_delayed_free, memory_order_relaxed);
      do
      {
        mi_block_set_nextx(heap, block, dfree, heap->keys);
      }
      while (!atomic_compare_exchange_weak_explicit(&heap->thread_delayed_free, &dfree, block, memory_order_release, memory_order_relaxed));
    }
    block_idx = next;
  }

  return all_freed;
}


/*** DEPENDENCIES:
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
None
----------------------------
inline static void mi_block_set_nextx(const void *null, mi_block_t *block, const mi_block_t *next, const uintptr_t *keys)
{
  ;
  block->next = mi_ptr_encode(null, next, keys);
  ;
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
None
----------------------------
***/


// element in merge of:  _mi_free_delayed_block,_mi_heap_collect_abandon,_mi_heap_delayed_free_all,_mi_heap_delayed_free_partial,_mi_prim_thread_init_auto_done,_mi_thread_done,_mi_thread_heap_done,mi_free,mi_free_block_local,mi_free_block_mt,mi_free_generic_mt,mi_heap_collect_ex,mi_heap_delete,mi_heap_free,mi_heap_get_default,mi_process_init,mi_process_setup_auto_thread_done,mi_pthread_done,mi_stat_free,mi_stats_get_default,mi_stats_reset,mi_thread_init
static bool _mi_thread_heap_done(mi_heap_t *heap)
{
  unsigned int heap_idx = 0;
  if (!mi_heap_is_initialized(heap))
  {
    return 1;
  }
  _mi_heap_set_default_direct((_mi_is_main_thread()) ? (&_mi_heap_main) : ((mi_heap_t *) (&_mi_heap_empty)));
  heap_idx = heap_idx->tld->heap_backing;
  if (!mi_heap_is_initialized(heap))
  {
    return 0;
  }
  mi_heap_t *curr = heap->tld->heaps;
  unsigned int curr_idx = 0;
  while ((&curr[curr_idx]) != 0)
  {
    mi_heap_t *next = curr->next;
    if ((&curr[curr_idx]) != (&heap[heap_idx]))
    {
      (!mi_heap_is_backing(curr)) ? ((void) 0) : (_mi_assert_fail("!mi_heap_is_backing(curr)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/init.c", 426, __func__));
      mi_heap_delete(curr);
    }
    curr_idx = next;
  }

  ((heap->tld->heaps == (&heap[heap_idx])) && (heap->next == 0)) ? ((void) 0) : (_mi_assert_fail("heap->tld->heaps == heap && heap->next == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/init.c", 431, __func__));
  (mi_heap_is_backing(heap)) ? ((void) 0) : (_mi_assert_fail("mi_heap_is_backing(heap)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/init.c", 432, __func__));
  if ((&heap[heap_idx]) != (&_mi_heap_main))
  {
    _mi_heap_collect_abandon(heap);
  }
  _mi_stats_done(&heap->tld->stats);
  if ((&heap[heap_idx]) != (&_mi_heap_main))
  {
    mi_thread_data_free((mi_thread_data_t *) heap);
  }
  else
  {
  }
  return 0;
}


/*** DEPENDENCIES:
inline static bool mi_heap_is_backing(const mi_heap_t *heap)
{
  return heap->tld->heap_backing == heap;
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
None
----------------------------
extern const mi_heap_t _mi_heap_empty
----------------------------
static void mi_thread_data_free(mi_thread_data_t *tdfree)
{
  for (int i = 0; i < 32; i += 1)
  {
    mi_thread_data_t *td = atomic_load_explicit(&td_cache[i], memory_order_relaxed);
    if (td == 0)
    {
      mi_thread_data_t *expected = 0;
      if (atomic_compare_exchange_weak_explicit(&td_cache[i], &expected, tdfree, memory_order_acq_rel, memory_order_acquire))
      {
        return;
      }
    }
  }

  _mi_os_free(tdfree, sizeof(mi_thread_data_t), tdfree->memid);
}


----------------------------
extern mi_heap_t _mi_heap_main
----------------------------
void _mi_heap_set_default_direct(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/init.c", 544, __func__));
  _mi_heap_default = heap;
  _mi_prim_thread_associate_default_heap(heap);
}


----------------------------
bool _mi_is_main_thread(void)
{
  return (_mi_heap_main.thread_id == 0) || (_mi_heap_main.thread_id == _mi_thread_id());
}


----------------------------
void _mi_stats_done(mi_stats_t *stats)
{
  mi_stats_merge_from(stats);
}


----------------------------
None
----------------------------
***/


// element in merge of:  _mi_free_delayed_block,_mi_heap_collect_abandon,_mi_heap_delayed_free_all,_mi_heap_delayed_free_partial,_mi_prim_thread_init_auto_done,_mi_thread_done,_mi_thread_heap_done,mi_free,mi_free_block_local,mi_free_block_mt,mi_free_generic_mt,mi_heap_collect_ex,mi_heap_delete,mi_heap_free,mi_heap_get_default,mi_process_init,mi_process_setup_auto_thread_done,mi_pthread_done,mi_stat_free,mi_stats_get_default,mi_stats_reset,mi_thread_init
void mi_thread_init(void)
{
  mi_process_init();
  if (_mi_thread_heap_init())
  {
    return;
  }
  _mi_stat_increase(&_mi_stats_main.threads, 1);
  atomic_fetch_add_explicit(&thread_count, (uintptr_t) 1, memory_order_relaxed);
}


/*** DEPENDENCIES:
static bool _mi_thread_heap_init(void)
{
  if (mi_heap_is_initialized(mi_prim_get_default_heap()))
  {
    return 1;
  }
  if (_mi_is_main_thread())
  {
    mi_heap_main_init();
    _mi_heap_set_default_direct(&_mi_heap_main);
  }
  else
  {
    mi_thread_data_t *td = mi_thread_data_zalloc();
    if (td == 0)
    {
      return 0;
    }
    mi_tld_t *tld = &td->tld;
    mi_heap_t *heap = &td->heap;
    _mi_tld_init(tld, heap);
    _mi_heap_init(heap, tld, _mi_arena_id_none(), 0, 0);
    _mi_heap_set_default_direct(heap);
  }
  return 0;
}


----------------------------
static _Atomic size_t thread_count = 1
----------------------------
void _mi_stat_increase(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_update(stat, (int64_t) amount);
}


----------------------------
extern mi_stats_t _mi_stats_main
----------------------------
None
----------------------------
***/


// element in merge of:  _mi_free_delayed_block,_mi_heap_collect_abandon,_mi_heap_delayed_free_all,_mi_heap_delayed_free_partial,_mi_prim_thread_init_auto_done,_mi_thread_done,_mi_thread_heap_done,mi_free,mi_free_block_local,mi_free_block_mt,mi_free_generic_mt,mi_heap_collect_ex,mi_heap_delete,mi_heap_free,mi_heap_get_default,mi_process_init,mi_process_setup_auto_thread_done,mi_pthread_done,mi_stat_free,mi_stats_get_default,mi_stats_reset,mi_thread_init
static void mi_stat_free(const mi_page_t *page, const mi_block_t *block)
{
  (void) block;
  mi_heap_t * const heap = mi_heap_get_default();
  const size_t bsize = mi_page_usable_block_size(page);
  if (bsize <= ((1UL << (3 + (13 + 3))) / 8))
  {
    _mi_stat_decrease(&heap->tld->stats.malloc_normal, bsize);
    _mi_stat_decrease(&heap->tld->stats.malloc_bins[_mi_bin(bsize)], 1);
  }
  else
  {
    _mi_stat_decrease(&heap->tld->stats.malloc_huge, bsize);
  }
}


/*** DEPENDENCIES:
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
None
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
inline static size_t mi_page_usable_block_size(const mi_page_t *page)
{
  return mi_page_block_size(page) - (sizeof(mi_padding_t));
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


