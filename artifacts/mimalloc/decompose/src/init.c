mi_subproc_id_t mi_subproc_main(void)
{
  return 0;
}


/*** DEPENDENCIES:
typedef void *mi_subproc_id_t
----------------------------
***/


bool _mi_preloading(void)
{
  return os_preloading;
}


/*** DEPENDENCIES:
static bool os_preloading = 1
----------------------------
***/


mi_threadid_t _mi_thread_id(void)
{
  return _mi_prim_thread_id();
}


/*** DEPENDENCIES:
inline static mi_threadid_t _mi_prim_thread_id(void)
{
  const mi_threadid_t tid = __mi_prim_thread_id();
  (tid > 1) ? ((void) 0) : (_mi_assert_fail("tid > 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/prim.h", 284, __func__));
  ((tid & 0x03UL) == 0) ? ((void) 0) : (_mi_assert_fail("(tid & MI_PAGE_FLAG_MASK) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/prim.h", 285, __func__));
  return tid;
}


----------------------------
typedef size_t mi_threadid_t
----------------------------
***/


bool _mi_is_main_thread(void)
{
  return (tld_main.thread_id == 0) || (tld_main.thread_id == _mi_thread_id());
}


/*** DEPENDENCIES:
mi_threadid_t _mi_thread_id(void)
{
  return _mi_prim_thread_id();
}


----------------------------
static mi_tld_t tld_main = {0, 0, 0, &subproc_main, &heap_main, &heap_main, 0, 0, 0, {2, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0}, {0}, {0}, {0}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0}, {0}, {0}, {0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}}, {{{0, 0}}, MI_MEM_STATIC, 1, 1, 0}}
----------------------------
***/


mi_subproc_t *_mi_subproc_main(void)
{
  return &subproc_main;
}


/*** DEPENDENCIES:
static mi_subproc_t subproc_main = {0}
----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
mi_subproc_t *_mi_subproc_main(void)
{
  return &subproc_main;
}


----------------------------
None
----------------------------
***/


void _mi_heap_set_default_direct(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/init.c", 590, __func__));
  _mi_heap_default = heap;
  _mi_prim_thread_associate_default_heap(heap);
}


/*** DEPENDENCIES:
None
----------------------------
extern mi_heap_t *_mi_heap_default
----------------------------
void _mi_prim_thread_associate_default_heap(mi_heap_t *heap)
{
  if (_mi_heap_default_key != ((pthread_key_t) (-1)))
  {
    pthread_setspecific(_mi_heap_default_key, heap);
  }
}


----------------------------
None
----------------------------
***/


mi_tld_t *_mi_thread_tld(void)
{
  mi_heap_t *heap = mi_prim_get_default_heap();
  if (heap == 0)
  {
    return &tld_empty;
  }
  else
  {
    return heap->tld;
  }
}


/*** DEPENDENCIES:
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
static mi_tld_t tld_empty = {0, 0, 0, &subproc_main, 0, 0, 0, 0, 0, {2, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0}, {0}, {0}, {0}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0}, {0}, {0}, {0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}}, {{{0, 0}}, MI_MEM_STATIC, 1, 1, 0}}
----------------------------
None
----------------------------
***/


static bool _mi_thread_heap_done(mi_heap_t *heap)
{
  unsigned int heap_idx = 0;
  if (!mi_heap_is_initialized(heap))
  {
    return 1;
  }
  _mi_heap_set_default_direct((_mi_is_main_thread()) ? (&heap_main) : ((mi_heap_t *) (&_mi_heap_empty)));
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
      (!mi_heap_is_backing(curr)) ? ((void) 0) : (_mi_assert_fail("!mi_heap_is_backing(curr)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/init.c", 481, __func__));
      mi_heap_delete(curr);
    }
    curr_idx = next;
  }

  ((heap->tld->heaps == (&heap[heap_idx])) && (heap->next == 0)) ? ((void) 0) : (_mi_assert_fail("heap->tld->heaps == heap && heap->next == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/init.c", 486, __func__));
  (mi_heap_is_backing(heap)) ? ((void) 0) : (_mi_assert_fail("mi_heap_is_backing(heap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/init.c", 487, __func__));
  if ((&heap[heap_idx]) != (&heap_main))
  {
    _mi_heap_collect_abandon(heap);
  }
  _mi_meta_free(heap, sizeof(mi_heap_t), heap->memid);
  if ((&heap[heap_idx]) == (&heap_main))
  {
  }
  return 0;
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
extern mi_heap_t heap_main
----------------------------
void _mi_heap_collect_abandon(mi_heap_t *heap)
{
  mi_heap_collect_ex(heap, MI_ABANDON);
}


----------------------------
None
----------------------------
bool _mi_is_main_thread(void)
{
  return (tld_main.thread_id == 0) || (tld_main.thread_id == _mi_thread_id());
}


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
extern const mi_heap_t _mi_heap_empty
----------------------------
None
----------------------------
***/


static void mi_tld_free(mi_tld_t *tld)
{
  if ((tld != 0) && (tld != ((mi_tld_t *) 1)))
  {
    _mi_stats_done(&tld->stats);
    _mi_meta_free(tld, sizeof(mi_tld_t), tld->memid);
  }
  atomic_fetch_sub_explicit(&thread_count, (uintptr_t) 1, memory_order_relaxed);
}


/*** DEPENDENCIES:
void _mi_stats_done(mi_stats_t *stats)
{
  _mi_stats_merge_from(&_mi_subproc()->stats, stats);
}


----------------------------
static _Atomic size_t thread_count = 1
----------------------------
None
----------------------------
None
----------------------------
***/


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
  __mi_stat_decrease_mt(&_mi_subproc_main()->stats.threads, 1);
  if (heap->tld->thread_id != _mi_prim_thread_id())
  {
    return;
  }
  mi_tld_t *tld = heap->tld;
  _mi_thread_heap_done(heap);
  mi_tld_free(tld);
}


/*** DEPENDENCIES:
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
inline static mi_threadid_t _mi_prim_thread_id(void)
{
  const mi_threadid_t tid = __mi_prim_thread_id();
  (tid > 1) ? ((void) 0) : (_mi_assert_fail("tid > 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/prim.h", 284, __func__));
  ((tid & 0x03UL) == 0) ? ((void) 0) : (_mi_assert_fail("(tid & MI_PAGE_FLAG_MASK) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/prim.h", 285, __func__));
  return tid;
}


----------------------------
inline static bool mi_heap_is_initialized(const mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/internal.h", 542, __func__));
  return (heap != 0) && (heap != (&_mi_heap_empty));
}


----------------------------
void __mi_stat_decrease_mt(mi_stat_count_t *stat, size_t amount)
{
  mi_stat_update_mt(stat, -((int64_t) amount));
}


----------------------------
static void mi_tld_free(mi_tld_t *tld)
{
  if ((tld != 0) && (tld != ((mi_tld_t *) 1)))
  {
    _mi_stats_done(&tld->stats);
    _mi_meta_free(tld, sizeof(mi_tld_t), tld->memid);
  }
  atomic_fetch_sub_explicit(&thread_count, (uintptr_t) 1, memory_order_relaxed);
}


----------------------------
mi_subproc_t *_mi_subproc_main(void)
{
  return &subproc_main;
}


----------------------------
static bool _mi_thread_heap_done(mi_heap_t *heap)
{
  unsigned int heap_idx = 0;
  if (!mi_heap_is_initialized(heap))
  {
    return 1;
  }
  _mi_heap_set_default_direct((_mi_is_main_thread()) ? (&heap_main) : ((mi_heap_t *) (&_mi_heap_empty)));
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
      (!mi_heap_is_backing(curr)) ? ((void) 0) : (_mi_assert_fail("!mi_heap_is_backing(curr)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/init.c", 481, __func__));
      mi_heap_delete(curr);
    }
    curr_idx = next;
  }

  ((heap->tld->heaps == (&heap[heap_idx])) && (heap->next == 0)) ? ((void) 0) : (_mi_assert_fail("heap->tld->heaps == heap && heap->next == NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/init.c", 486, __func__));
  (mi_heap_is_backing(heap)) ? ((void) 0) : (_mi_assert_fail("mi_heap_is_backing(heap)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/init.c", 487, __func__));
  if ((&heap[heap_idx]) != (&heap_main))
  {
    _mi_heap_collect_abandon(heap);
  }
  _mi_meta_free(heap, sizeof(mi_heap_t), heap->memid);
  if ((&heap[heap_idx]) == (&heap_main))
  {
  }
  return 0;
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
void _mi_heap_set_default_direct(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/init.c", 590, __func__));
  _mi_heap_default = heap;
  _mi_prim_thread_associate_default_heap(heap);
}


----------------------------
void _mi_prim_thread_init_auto_done(void)
{
  (_mi_heap_default_key == ((pthread_key_t) (-1))) ? ((void) 0) : (_mi_assert_fail("_mi_heap_default_key == (pthread_key_t)(-1)", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/prim/unix/prim.c", 939, __func__));
  pthread_key_create(&_mi_heap_default_key, &mi_pthread_done);
}


----------------------------
extern mi_heap_t heap_main
----------------------------
***/


static void mi_detect_cpu_features(void)
{
  _mi_cpu_has_popcnt = 1;
}


/*** DEPENDENCIES:
bool _mi_cpu_has_popcnt = 0
----------------------------
***/


static void mi_tld_main_init(void)
{
  if (tld_main.thread_id == 0)
  {
    tld_main.thread_id = _mi_prim_thread_id();
  }
}


/*** DEPENDENCIES:
inline static mi_threadid_t _mi_prim_thread_id(void)
{
  const mi_threadid_t tid = __mi_prim_thread_id();
  (tid > 1) ? ((void) 0) : (_mi_assert_fail("tid > 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/prim.h", 284, __func__));
  ((tid & 0x03UL) == 0) ? ((void) 0) : (_mi_assert_fail("(tid & MI_PAGE_FLAG_MASK) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/prim.h", 285, __func__));
  return tid;
}


----------------------------
static mi_tld_t tld_main = {0, 0, 0, &subproc_main, &heap_main, &heap_main, 0, 0, 0, {2, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0}, {0}, {0}, {0}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0}, {0}, {0}, {0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}}, {{{0, 0}}, MI_MEM_STATIC, 1, 1, 0}}
----------------------------
***/


static void mi_subproc_main_init(void)
{
  if (subproc_main.memid.memkind != MI_MEM_STATIC)
  {
    subproc_main.memid = _mi_memid_create(MI_MEM_STATIC);
    mi_lock_init(&subproc_main.os_abandoned_pages_lock);
    mi_lock_init(&subproc_main.arena_reserve_lock);
  }
}


/*** DEPENDENCIES:
inline static mi_memid_t _mi_memid_create(mi_memkind_t memkind)
{
  mi_memid_t memid;
  memset(&memid, 0, sizeof(memid));
  memid.memkind = memkind;
  return memid;
}


----------------------------
inline static void mi_lock_init(pthread_mutex_t *lock)
{
  pthread_mutex_init(lock, 0);
}


----------------------------
static mi_subproc_t subproc_main = {0}
----------------------------
***/


void _mi_heap_guarded_init(mi_heap_t *heap)
{
  (void) heap;
}


/*** DEPENDENCIES:
None
----------------------------
***/


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


/*** DEPENDENCIES:
long mi_option_get_clamp(mi_option_t option, long min, long max)
{
  long x = mi_option_get(option);
  return (x < min) ? (min) : ((x > max) ? (max) : (x));
}


----------------------------
void _mi_random_init(mi_random_ctx_t *ctx)
{
  mi_random_init_ex(ctx, 0);
}


----------------------------
uintptr_t _mi_heap_random_next(mi_heap_t *heap)
{
  return _mi_random_next(&heap->random);
}


----------------------------
extern mi_heap_t heap_main
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
void _mi_heap_guarded_init(mi_heap_t *heap)
{
  (void) heap;
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


static mi_tld_t *mi_tld_alloc(void)
{
  atomic_fetch_add_explicit(&thread_count, (uintptr_t) 1, memory_order_relaxed);
  if (_mi_is_main_thread())
  {
    return &tld_main;
  }
  else
  {
    mi_memid_t memid;
    mi_tld_t *tld = (mi_tld_t *) _mi_meta_zalloc(sizeof(mi_tld_t), &memid);
    if (tld == 0)
    {
      _mi_error_message(12, "unable to allocate memory for thread local data\n");
      return 0;
    }
    tld->memid = memid;
    tld->heap_backing = 0;
    tld->heaps = 0;
    tld->subproc = &subproc_main;
    tld->numa_node = _mi_os_numa_node();
    tld->thread_id = _mi_prim_thread_id();
    tld->thread_seq = atomic_fetch_add_explicit(&thread_total_count, 1, memory_order_acq_rel);
    tld->is_in_threadpool = _mi_prim_thread_is_in_threadpool();
    return tld;
  }
}


/*** DEPENDENCIES:
int _mi_os_numa_node(void)
{
  if (__builtin_expect(!(!(atomic_load_explicit(&mi_numa_node_count, memory_order_relaxed) == 1)), 1))
  {
    return 0;
  }
  else
  {
    return mi_os_numa_node_get();
  }
}


----------------------------
inline static mi_threadid_t _mi_prim_thread_id(void)
{
  const mi_threadid_t tid = __mi_prim_thread_id();
  (tid > 1) ? ((void) 0) : (_mi_assert_fail("tid > 1", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/prim.h", 284, __func__));
  ((tid & 0x03UL) == 0) ? ((void) 0) : (_mi_assert_fail("(tid & MI_PAGE_FLAG_MASK) == 0", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/include/mimalloc/prim.h", 285, __func__));
  return tid;
}


----------------------------
static mi_subproc_t subproc_main = {0}
----------------------------
static mi_tld_t tld_main = {0, 0, 0, &subproc_main, &heap_main, &heap_main, 0, 0, 0, {2, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0}, {0}, {0}, {0}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0}, {0}, {0}, {0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}}, {{{0, 0}}, MI_MEM_STATIC, 1, 1, 0}}
----------------------------
bool _mi_prim_thread_is_in_threadpool(void)
{
  return 0;
}


----------------------------
bool _mi_is_main_thread(void)
{
  return (tld_main.thread_id == 0) || (tld_main.thread_id == _mi_thread_id());
}


----------------------------
static _Atomic size_t thread_total_count
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
static _Atomic size_t thread_count = 1
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


/*** DEPENDENCIES:
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


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
mi_arena_id_t _mi_arena_id_none(void)
{
  return 0;
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
static mi_tld_t *mi_tld_alloc(void)
{
  atomic_fetch_add_explicit(&thread_count, (uintptr_t) 1, memory_order_relaxed);
  if (_mi_is_main_thread())
  {
    return &tld_main;
  }
  else
  {
    mi_memid_t memid;
    mi_tld_t *tld = (mi_tld_t *) _mi_meta_zalloc(sizeof(mi_tld_t), &memid);
    if (tld == 0)
    {
      _mi_error_message(12, "unable to allocate memory for thread local data\n");
      return 0;
    }
    tld->memid = memid;
    tld->heap_backing = 0;
    tld->heaps = 0;
    tld->subproc = &subproc_main;
    tld->numa_node = _mi_os_numa_node();
    tld->thread_id = _mi_prim_thread_id();
    tld->thread_seq = atomic_fetch_add_explicit(&thread_total_count, 1, memory_order_acq_rel);
    tld->is_in_threadpool = _mi_prim_thread_is_in_threadpool();
    return tld;
  }
}


----------------------------
mi_tld_t *thread_tld = &tld_empty
----------------------------
bool _mi_is_main_thread(void)
{
  return (tld_main.thread_id == 0) || (tld_main.thread_id == _mi_thread_id());
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
extern mi_heap_t heap_main
----------------------------
None
----------------------------
***/


void mi_thread_done(void)
{
  _mi_thread_done(0);
}


/*** DEPENDENCIES:
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
  __mi_stat_decrease_mt(&_mi_subproc_main()->stats.threads, 1);
  if (heap->tld->thread_id != _mi_prim_thread_id())
  {
    return;
  }
  mi_tld_t *tld = heap->tld;
  _mi_thread_heap_done(heap);
  mi_tld_free(tld);
}


----------------------------
***/


bool mi_is_redirected(void)
{
  return _mi_is_redirected();
}


/*** DEPENDENCIES:
bool _mi_is_redirected(void)
{
  return 0;
}


----------------------------
***/


void mi_heap_guarded_set_sample_rate(mi_heap_t *heap, size_t sample_rate, size_t seed)
{
  (void) heap;
  (void) sample_rate;
  (void) seed;
}


/*** DEPENDENCIES:
None
----------------------------
***/


void mi_heap_guarded_set_size_bound(mi_heap_t *heap, size_t min, size_t max)
{
  (void) heap;
  (void) min;
  (void) max;
}


/*** DEPENDENCIES:
None
----------------------------
***/


size_t _mi_current_thread_count(void)
{
  return atomic_load_explicit(&thread_count, memory_order_relaxed);
}


/*** DEPENDENCIES:
static _Atomic size_t thread_count = 1
----------------------------
***/


void _mi_auto_process_init(void)
{
  mi_heap_main_init();
  os_preloading = 0;
  (_mi_is_main_thread()) ? ((void) 0) : (_mi_assert_fail("_mi_is_main_thread()", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/init.c", 636, __func__));
  _mi_options_init();
  mi_process_setup_auto_thread_done();
  mi_process_init();
  if (_mi_is_redirected())
  {
    _mi_verbose_message("malloc is redirected.\n");
  }
  const char *msg = 0;
  _mi_allocator_init(&msg);
  if ((msg != 0) && (mi_option_is_enabled(mi_option_verbose) || mi_option_is_enabled(mi_option_show_errors)))
  {
    _mi_fputs(0, 0, 0, msg);
  }
  _mi_random_reinit_if_weak(&heap_main.random);
}


/*** DEPENDENCIES:
void _mi_random_reinit_if_weak(mi_random_ctx_t *ctx)
{
  if (ctx->weak)
  {
    _mi_random_init(ctx);
  }
}


----------------------------
None
----------------------------
bool _mi_allocator_init(const char **message)
{
  if (message != 0)
  {
    *message = 0;
  }
  return 1;
}


----------------------------
None
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
bool _mi_is_main_thread(void)
{
  return (tld_main.thread_id == 0) || (tld_main.thread_id == _mi_thread_id());
}


----------------------------
void _mi_options_init(void)
{
  mi_add_stderr_output();
  for (int i = 0; i < _mi_option_last; i += 1)
  {
    mi_option_t option = (mi_option_t) i;
    long l = mi_option_get(option);
    (void) l;
  }

  mi_max_error_count = mi_option_get(mi_option_max_errors);
  mi_max_warning_count = mi_option_get(mi_option_max_warnings);
  if (mi_option_is_enabled(mi_option_verbose))
  {
    mi_options_print();
  }
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
extern mi_heap_t heap_main
----------------------------
bool _mi_is_redirected(void)
{
  return 0;
}


----------------------------
static bool os_preloading = 1
----------------------------
None
----------------------------
***/


void mi_process_done(void)
{
  if (!_mi_process_is_initialized)
  {
    return;
  }
  static bool process_done = 0;
  if (process_done)
  {
    return;
  }
  process_done = 1;
  mi_heap_t *heap = mi_prim_get_default_heap();
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/init.c", 759, __func__));
  _mi_prim_thread_done_auto_done();
  mi_heap_collect(heap, 1);
  if (mi_option_is_enabled(mi_option_destroy_on_exit))
  {
    mi_heap_collect(heap, 1);
    _mi_heap_unsafe_destroy_all(heap);
    _mi_arenas_unsafe_destroy_all(_mi_subproc_main());
    _mi_page_map_unsafe_destroy(_mi_subproc_main());
  }
  if (mi_option_is_enabled(mi_option_show_stats) || mi_option_is_enabled(mi_option_verbose))
  {
    _mi_stats_print(&_mi_subproc_main()->stats, 0, 0);
  }
  _mi_allocator_done();
  _mi_verbose_message("process done: 0x%zx\n", tld_main.thread_id);
  os_preloading = 1;
}


/*** DEPENDENCIES:
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
None
----------------------------
None
----------------------------
static mi_tld_t tld_main = {0, 0, 0, &subproc_main, &heap_main, &heap_main, 0, 0, 0, {2, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0}, {0}, {0}, {0}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0}, {0}, {0}, {0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}}, {{{0, 0}}, MI_MEM_STATIC, 1, 1, 0}}
----------------------------
extern bool _mi_process_is_initialized
----------------------------
void _mi_prim_thread_done_auto_done(void)
{
  if (_mi_heap_default_key != ((pthread_key_t) (-1)))
  {
    pthread_key_delete(_mi_heap_default_key);
  }
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
mi_subproc_t *_mi_subproc_main(void)
{
  return &subproc_main;
}


----------------------------
void _mi_allocator_done(void)
{
}


----------------------------
void _mi_stats_print(mi_stats_t *stats, mi_output_fun *out0, void *arg0)
{
  char buf[256];
  memset(&buf, 0, sizeof(buf));
  buffered_t buffer = {out0, arg0, 0, 0, 255};
  buffer.buf = buf;
  mi_output_fun *out = &mi_buffered_out;
  void *arg = &buffer;
  mi_print_header(out, arg);
  mi_stats_print_bins(stats->malloc_bins, 73U, "bin", out, arg);
  mi_stat_print(&stats->malloc_normal, "binned", (stats->malloc_normal_count.total == 0) ? (1) : (-1), out, arg);
  mi_stat_print(&stats->malloc_huge, "huge", (stats->malloc_huge_count.total == 0) ? (1) : (-1), out, arg);
  mi_stat_count_t total = {0, 0, 0};
  mi_stat_count_add_mt(&total, &stats->malloc_normal);
  mi_stat_count_add_mt(&total, &stats->malloc_huge);
  mi_stat_print_ex(&total, "total", 1, out, arg, "");
  mi_stat_total_print(&stats->malloc_requested, "malloc req", 1, out, arg);
  _mi_fprintf(out, arg, "\n");
  mi_stat_print_ex(&stats->reserved, "reserved", 1, out, arg, "");
  mi_stat_print_ex(&stats->committed, "committed", 1, out, arg, "");
  mi_stat_peak_print(&stats->reset, "reset", 1, out, arg);
  mi_stat_peak_print(&stats->purged, "purged", 1, out, arg);
  mi_stat_print_ex(&stats->page_committed, "touched", 1, out, arg, "");
  mi_stat_print(&stats->pages, "pages", -1, out, arg);
  mi_stat_print(&stats->pages_abandoned, "-abandoned", -1, out, arg);
  mi_stat_counter_print(&stats->pages_reclaim_on_alloc, "-reclaima", out, arg);
  mi_stat_counter_print(&stats->pages_reclaim_on_free, "-reclaimf", out, arg);
  mi_stat_counter_print(&stats->pages_reabandon_full, "-reabandon", out, arg);
  mi_stat_counter_print(&stats->pages_unabandon_busy_wait, "-waits", out, arg);
  mi_stat_counter_print(&stats->pages_extended, "-extended", out, arg);
  mi_stat_counter_print(&stats->pages_retire, "-retire", out, arg);
  mi_stat_counter_print(&stats->arena_count, "arenas", out, arg);
  mi_stat_counter_print(&stats->arena_rollback_count, "-rollback", out, arg);
  mi_stat_counter_print(&stats->mmap_calls, "mmaps", out, arg);
  mi_stat_counter_print(&stats->commit_calls, "commits", out, arg);
  mi_stat_counter_print(&stats->reset_calls, "resets", out, arg);
  mi_stat_counter_print(&stats->purge_calls, "purges", out, arg);
  mi_stat_counter_print(&stats->malloc_guarded_count, "guarded", out, arg);
  mi_stat_print(&stats->threads, "threads", -1, out, arg);
  mi_stat_counter_print_avg(&stats->page_searches, "searches", out, arg);
  _mi_fprintf(out, arg, "%10s: %5i\n", "numa nodes", _mi_os_numa_node_count());
  size_t elapsed;
  size_t user_time;
  size_t sys_time;
  size_t current_rss;
  size_t peak_rss;
  size_t current_commit;
  size_t peak_commit;
  size_t page_faults;
  mi_process_info(&elapsed, &user_time, &sys_time, &current_rss, &peak_rss, &current_commit, &peak_commit, &page_faults);
  _mi_fprintf(out, arg, "%10s: %5zu.%03zu s\n", "elapsed", elapsed / 1000, elapsed % 1000);
  _mi_fprintf(out, arg, "%10s: user: %zu.%03zu s, system: %zu.%03zu s, faults: %zu, rss: ", "process", user_time / 1000, user_time % 1000, sys_time / 1000, sys_time % 1000, page_faults);
  mi_printf_amount((int64_t) peak_rss, 1, out, arg, "%s");
  if (peak_commit > 0)
  {
    _mi_fprintf(out, arg, ", commit: ");
    mi_printf_amount((int64_t) peak_commit, 1, out, arg, "%s");
  }
  _mi_fprintf(out, arg, "\n");
}


----------------------------
void _mi_page_map_unsafe_destroy(mi_subproc_t *subproc)
{
  (subproc != 0) ? ((void) 0) : (_mi_assert_fail("subproc != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 289, __func__));
  (_mi_page_map != 0) ? ((void) 0) : (_mi_assert_fail("_mi_page_map != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/page-map.c", 290, __func__));
  if (_mi_page_map == 0)
  {
    return;
  }
  for (size_t idx = 1; idx < mi_page_map_count; idx += 1)
  {
    if (mi_page_map_is_committed(idx, 0))
    {
      mi_submap_t sub = _mi_page_map_at(idx);
      if (sub != 0)
      {
        mi_memid_t memid = _mi_memid_create_os(sub, (1UL << 13) * (sizeof(mi_page_t *)), 1, 0, 0);
        _mi_os_free_ex(memid.mem.os.base, memid.mem.os.size, 1, memid, subproc);
        atomic_store_explicit(&_mi_page_map[idx], 0, memory_order_release);
      }
    }
  }

  _mi_os_free_ex(_mi_page_map, mi_page_map_memid.mem.os.size, 1, mi_page_map_memid, subproc);
  _mi_page_map = 0;
  mi_page_map_count = 0;
  mi_page_map_memid = _mi_memid_none();
  mi_page_map_max_address = 0;
  atomic_store_explicit(&mi_page_map_commit, 0, memory_order_release);
}


----------------------------
void mi_heap_collect(mi_heap_t *heap, bool force)
{
  mi_heap_collect_ex(heap, (force) ? (MI_FORCE) : (MI_NORMAL));
}


----------------------------
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


----------------------------
void _mi_arenas_unsafe_destroy_all(mi_subproc_t *subproc)
{
  mi_arenas_unsafe_destroy(subproc);
}


----------------------------
static bool os_preloading = 1
----------------------------
None
----------------------------
***/


void _mi_auto_process_done(void)
{
  if (_mi_option_get_fast(mi_option_destroy_on_exit) > 1)
  {
    return;
  }
  mi_process_done();
}


/*** DEPENDENCIES:
long _mi_option_get_fast(mi_option_t option)
{
  ((option >= 0) && (option < _mi_option_last)) ? ((void) 0) : (_mi_assert_fail("option >= 0 && option < _mi_option_last", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/options.c", 249, __func__));
  mi_option_desc_t *desc = &mi_options[option];
  (desc->option == option) ? ((void) 0) : (_mi_assert_fail("desc->option == option", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/options.c", 251, __func__));
  return desc->value;
}


----------------------------
void mi_process_done(void)
{
  if (!_mi_process_is_initialized)
  {
    return;
  }
  static bool process_done = 0;
  if (process_done)
  {
    return;
  }
  process_done = 1;
  mi_heap_t *heap = mi_prim_get_default_heap();
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/init.c", 759, __func__));
  _mi_prim_thread_done_auto_done();
  mi_heap_collect(heap, 1);
  if (mi_option_is_enabled(mi_option_destroy_on_exit))
  {
    mi_heap_collect(heap, 1);
    _mi_heap_unsafe_destroy_all(heap);
    _mi_arenas_unsafe_destroy_all(_mi_subproc_main());
    _mi_page_map_unsafe_destroy(_mi_subproc_main());
  }
  if (mi_option_is_enabled(mi_option_show_stats) || mi_option_is_enabled(mi_option_verbose))
  {
    _mi_stats_print(&_mi_subproc_main()->stats, 0, 0);
  }
  _mi_allocator_done();
  _mi_verbose_message("process done: 0x%zx\n", tld_main.thread_id);
  os_preloading = 1;
}


----------------------------
***/


static mi_tld_t *mi_tld(void)
{
  mi_tld_t *tld = thread_tld;
  if (tld == ((mi_tld_t *) 1))
  {
    _mi_error_message(14, "internal error: tld is accessed after the thread terminated\n");
    thread_tld = &tld_empty;
  }
  if (tld == (&tld_empty))
  {
    thread_tld = (tld = mi_tld_alloc());
  }
  return tld;
}


/*** DEPENDENCIES:
mi_tld_t *thread_tld = &tld_empty
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
static mi_tld_t tld_empty = {0, 0, 0, &subproc_main, 0, 0, 0, 0, 0, {2, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0}, {0}, {0}, {0}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0}, {0}, {0}, {0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}}, {{{0, 0}}, MI_MEM_STATIC, 1, 1, 0}}
----------------------------
static mi_tld_t *mi_tld_alloc(void)
{
  atomic_fetch_add_explicit(&thread_count, (uintptr_t) 1, memory_order_relaxed);
  if (_mi_is_main_thread())
  {
    return &tld_main;
  }
  else
  {
    mi_memid_t memid;
    mi_tld_t *tld = (mi_tld_t *) _mi_meta_zalloc(sizeof(mi_tld_t), &memid);
    if (tld == 0)
    {
      _mi_error_message(12, "unable to allocate memory for thread local data\n");
      return 0;
    }
    tld->memid = memid;
    tld->heap_backing = 0;
    tld->heaps = 0;
    tld->subproc = &subproc_main;
    tld->numa_node = _mi_os_numa_node();
    tld->thread_id = _mi_prim_thread_id();
    tld->thread_seq = atomic_fetch_add_explicit(&thread_total_count, 1, memory_order_acq_rel);
    tld->is_in_threadpool = _mi_prim_thread_is_in_threadpool();
    return tld;
  }
}


----------------------------
None
----------------------------
***/


void mi_thread_set_in_threadpool(void)
{
  mi_tld_t *tld = mi_tld();
  if (tld != 0)
  {
    tld->is_in_threadpool = 1;
  }
}


/*** DEPENDENCIES:
static mi_tld_t *mi_tld(void)
{
  mi_tld_t *tld = thread_tld;
  if (tld == ((mi_tld_t *) 1))
  {
    _mi_error_message(14, "internal error: tld is accessed after the thread terminated\n");
    thread_tld = &tld_empty;
  }
  if (tld == (&tld_empty))
  {
    thread_tld = (tld = mi_tld_alloc());
  }
  return tld;
}


----------------------------
None
----------------------------
***/


mi_subproc_t *_mi_subproc_from_id(mi_subproc_id_t subproc_id)
{
  return (subproc_id == 0) ? (&subproc_main) : ((mi_subproc_t *) subproc_id);
}


/*** DEPENDENCIES:
typedef void *mi_subproc_id_t
----------------------------
static mi_subproc_t subproc_main = {0}
----------------------------
None
----------------------------
***/


mi_heap_t *_mi_heap_main_get(void)
{
  mi_heap_main_init();
  return &heap_main;
}


/*** DEPENDENCIES:
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
extern mi_heap_t heap_main
----------------------------
None
----------------------------
***/


mi_subproc_id_t mi_subproc_new(void)
{
  mi_memid_t memid;
  mi_subproc_t *subproc = (mi_subproc_t *) _mi_meta_zalloc(sizeof(mi_subproc_t), &memid);
  if (subproc == 0)
  {
    return 0;
  }
  subproc->memid = memid;
  mi_lock_init(&subproc->os_abandoned_pages_lock);
  mi_lock_init(&subproc->arena_reserve_lock);
  return subproc;
}


/*** DEPENDENCIES:
inline static void mi_lock_init(pthread_mutex_t *lock)
{
  pthread_mutex_init(lock, 0);
}


----------------------------
typedef void *mi_subproc_id_t
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


void mi_subproc_add_current_thread(mi_subproc_id_t subproc_id)
{
  mi_tld_t *tld = mi_tld();
  if (tld == 0)
  {
    return;
  }
  (tld->subproc == (&subproc_main)) ? ((void) 0) : (_mi_assert_fail("tld->subproc == &subproc_main", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/init.c", 425, __func__));
  if (tld->subproc != (&subproc_main))
  {
    return;
  }
  tld->subproc = _mi_subproc_from_id(subproc_id);
}


/*** DEPENDENCIES:
None
----------------------------
static mi_subproc_t subproc_main = {0}
----------------------------
typedef void *mi_subproc_id_t
----------------------------
mi_subproc_t *_mi_subproc_from_id(mi_subproc_id_t subproc_id)
{
  return (subproc_id == 0) ? (&subproc_main) : ((mi_subproc_t *) subproc_id);
}


----------------------------
static mi_tld_t *mi_tld(void)
{
  mi_tld_t *tld = thread_tld;
  if (tld == ((mi_tld_t *) 1))
  {
    _mi_error_message(14, "internal error: tld is accessed after the thread terminated\n");
    thread_tld = &tld_empty;
  }
  if (tld == (&tld_empty))
  {
    thread_tld = (tld = mi_tld_alloc());
  }
  return tld;
}


----------------------------
None
----------------------------
***/


void mi_subproc_delete(mi_subproc_id_t subproc_id)
{
  if (subproc_id == 0)
  {
    return;
  }
  mi_subproc_t *subproc = _mi_subproc_from_id(subproc_id);
  bool safe_to_delete = 0;
  for (bool _go = (mi_lock_acquire(&subproc->os_abandoned_pages_lock), 1); _go; mi_lock_release(&subproc->os_abandoned_pages_lock), _go = 0)
  {
    if (subproc->os_abandoned_pages == 0)
    {
      safe_to_delete = 1;
    }
  }

  if (!safe_to_delete)
  {
    return;
  }
  _mi_stats_merge_from(&_mi_subproc_main()->stats, &subproc->stats);
  mi_lock_done(&subproc->os_abandoned_pages_lock);
  mi_lock_done(&subproc->arena_reserve_lock);
  _mi_meta_free(subproc, sizeof(mi_subproc_t), subproc->memid);
}


/*** DEPENDENCIES:
void _mi_stats_merge_from(mi_stats_t *to, mi_stats_t *from)
{
  ((to != 0) && (from != 0)) ? ((void) 0) : (_mi_assert_fail("to != NULL && from != NULL", "/home/ubuntu/tmp/Rustine-Dev/subjects/mimalloc/src/stats.c", 410, __func__));
  if (to != from)
  {
    mi_stats_add(to, from);
    _mi_memzero(from, sizeof(mi_stats_t));
  }
}


----------------------------
typedef void *mi_subproc_id_t
----------------------------
None
----------------------------
mi_subproc_t *_mi_subproc_from_id(mi_subproc_id_t subproc_id)
{
  return (subproc_id == 0) ? (&subproc_main) : ((mi_subproc_t *) subproc_id);
}


----------------------------
inline static void mi_lock_done(pthread_mutex_t *lock)
{
  pthread_mutex_destroy(lock);
}


----------------------------
mi_subproc_t *_mi_subproc_main(void)
{
  return &subproc_main;
}


----------------------------
inline static void mi_lock_release(pthread_mutex_t *lock)
{
  pthread_mutex_unlock(lock);
}


----------------------------
inline static void mi_lock_acquire(pthread_mutex_t *lock)
{
  const int err = pthread_mutex_lock(lock);
  if (err != 0)
  {
    _mi_error_message(err, "internal error: lock cannot be acquired\n");
  }
}


----------------------------
None
----------------------------
***/


