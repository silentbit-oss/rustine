// element in merge of:  mi_process_init,mi_thread_init
void mi_thread_init(void)
{
  mi_process_init();
  if (_mi_thread_heap_init())
  {
    return;
  }
  __mi_stat_increase_mt(&_mi_subproc_main()->stats.threads, 1);
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
    _mi_heap_set_default_direct(&heap_main);
  }
  else
  {
    mi_tld_t *tld = mi_tld_alloc();
    mi_heap_t *heap = _mi_heap_create(0, 0, _mi_arena_id_none(), tld);
    _mi_heap_set_default_direct(heap);
    thread_tld = tld;
  }
  return 0;
}


----------------------------
mi_subproc_t *_mi_subproc_main(void)
{
  return &subproc_main;
}


----------------------------
void __mi_stat_increase_mt(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_update_mt(stat, (int64_t) amount);
}


----------------------------
None
----------------------------
***/


// element in merge of:  mi_process_init,mi_thread_init
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
  mi_detect_cpu_features();
  _mi_stats_init();
  _mi_os_init();
  _mi_page_map_init();
  mi_heap_main_init();
  mi_tld_main_init();
  mi_subproc_main_init();
  mi_process_setup_auto_thread_done();
  mi_thread_init();
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
long mi_option_get_clamp(mi_option_t option, long min, long max)
{
  long x = mi_option_get(option);
  return (x < min) ? (min) : ((x > max) ? (max) : (x));
}


----------------------------
void _mi_stats_init(void)
{
  if (mi_process_start == 0)
  {
    mi_process_start = _mi_clock_start();
  }
  ;
}


----------------------------
void _mi_os_init(void)
{
  _mi_prim_mem_init(&mi_os_mem_config);
}


----------------------------
extern bool _mi_process_is_initialized
----------------------------
int mi_reserve_huge_os_pages_at(size_t pages, int numa_node, size_t timeout_msecs)
{
  return mi_reserve_huge_os_pages_at_ex(pages, numa_node, timeout_msecs, 0, 0);
}


----------------------------
None
----------------------------
mi_threadid_t _mi_thread_id(void)
{
  return _mi_prim_thread_id();
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
typedef _Atomic uintptr_t mi_atomic_once_t
----------------------------
static void mi_detect_cpu_features(void)
{
  _mi_cpu_has_popcnt = 1;
}


----------------------------
int mi_reserve_huge_os_pages_interleave(size_t pages, size_t numa_nodes, size_t timeout_msecs)
{
  if (pages == 0)
  {
    return 0;
  }
  int numa_count = ((numa_nodes > 0) && (numa_nodes <= 2147483647)) ? ((int) numa_nodes) : (_mi_os_numa_node_count());
  if (numa_count <= 0)
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
static void mi_process_setup_auto_thread_done(void)
{
  static bool tls_initialized = 0;
  if (tls_initialized)
  {
    return;
  }
  tls_initialized = 1;
  _mi_prim_thread_init_auto_done();
  _mi_heap_set_default_direct(&heap_main);
}


----------------------------
bool _mi_page_map_init(void)
{
  size_t vbits = (size_t) mi_option_get_clamp(mi_option_max_vabits, 0, (1 << 3) * 8);
  if (vbits == 0)
  {
    vbits = _mi_os_virtual_address_bits();
  }
  (48 >= vbits) ? ((void) 0) : (_mi_assert_fail("MI_MAX_VABITS >= vbits", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 240, __func__));
  mi_page_map_max_address = (void *) ((vbits >= ((1 << 3) * 8)) ? ((SIZE_MAX - (1UL << (13 + 3))) + 1) : (1UL << vbits));
  mi_page_map_count = 1UL << ((vbits - 13) - (13 + 3));
  (mi_page_map_count <= (1UL << ((48 - 13) - (13 + 3)))) ? ((void) 0) : (_mi_assert_fail("mi_page_map_count <= MI_PAGE_MAP_COUNT", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 243, __func__));
  const size_t os_page_size = _mi_os_page_size();
  const size_t page_map_size = _mi_align_up(mi_page_map_count * (sizeof(mi_page_t **)), os_page_size);
  const size_t submap_size = (1UL << 13) * (sizeof(mi_page_t *));
  const size_t reserve_size = page_map_size + submap_size;
  const bool commit = ((page_map_size <= (64 * 1024UL)) || mi_option_is_enabled(mi_option_pagemap_commit)) || _mi_os_has_overcommit();
  _mi_page_map = (mi_page_t ** *) _mi_os_alloc_aligned(reserve_size, 1, commit, 1, &mi_page_map_memid);
  if (_mi_page_map == 0)
  {
    _mi_error_message(12, "unable to reserve virtual memory for the page map (%zu KiB)\n", page_map_size / 1024UL);
    return 0;
  }
  if (mi_page_map_memid.initially_committed && (!mi_page_map_memid.initially_zero))
  {
    _mi_warning_message("internal: the page map was committed but not zero initialized!\n");
    _mi_memzero_aligned(_mi_page_map, page_map_size);
  }
  atomic_store_explicit(&mi_page_map_commit, (mi_page_map_memid.initially_committed) ? (~0UL) : (0UL), memory_order_release);
  mi_page_t ** const sub0 = (mi_page_t **) (((uint8_t *) _mi_page_map) + page_map_size);
  if (!mi_page_map_memid.initially_committed)
  {
    if (!_mi_os_commit(sub0, submap_size, 0))
    {
      mi_page_map_cannot_commit();
      return 0;
    }
  }
  if (!mi_page_map_memid.initially_zero)
  {
    _mi_memzero_aligned(sub0, submap_size);
  }
  mi_submap_t nullsub = 0;
  if (!mi_page_map_ensure_committed(0, &nullsub))
  {
    mi_page_map_cannot_commit();
    return 0;
  }
  atomic_store_explicit(&_mi_page_map[0], sub0, memory_order_release);
  (_mi_ptr_page(0) == 0) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(NULL)==NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 283, __func__));
  return 1;
}


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
static void mi_heap_main_init(void)
{
  if (heap_main.cookie == 0)
  {
    heap_main.cookie = 1;
    _mi_random_init(&heap_main.random);
    heap_main.cookie = _mi_heap_random_next(&heap_main);
    _mi_heap_guarded_init(&heap_main);
    heap_main.allow_page_reclaim = mi_option_get(mi_option_page_reclaim_on_free) >= 0;
    heap_main.allow_page_abandon = mi_option_get(mi_option_page_full_retain) >= 0;
    heap_main.page_full_retain = mi_option_get_clamp(mi_option_page_full_retain, -1, 32);
    mi_subproc_main_init();
    mi_tld_main_init();
  }
}


----------------------------
int mi_reserve_os_memory(size_t size, bool commit, bool allow_large)
{
  return mi_reserve_os_memory_ex(size, commit, allow_large, 0, 0);
}


----------------------------
static void mi_subproc_main_init(void)
{
  if (subproc_main.memid.memkind != MI_MEM_STATIC)
  {
    subproc_main.memid = _mi_memid_create(MI_MEM_STATIC);
    mi_lock_init(&subproc_main.os_abandoned_pages_lock);
    mi_lock_init(&subproc_main.arena_reserve_lock);
  }
}


----------------------------
static void mi_tld_main_init(void)
{
  if (tld_main.thread_id == 0)
  {
    tld_main.thread_id = _mi_prim_thread_id();
  }
}


----------------------------
None
----------------------------
***/


