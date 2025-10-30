mi_subproc_id_t mi_subproc_main(void)
{
  return 0;
}


/*** DEPENDENCIES:
***/


void mi_thread_set_in_threadpool(void)
{
}


/*** DEPENDENCIES:
***/


static void mi_detect_cpu_features(void)
{
}


/*** DEPENDENCIES:
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
  return (uintptr_t) __builtin_thread_pointer();
}


----------------------------
***/


bool _mi_is_main_thread(void)
{
  return (_mi_heap_main.thread_id == 0) || (_mi_heap_main.thread_id == _mi_thread_id());
}


/*** DEPENDENCIES:
extern mi_heap_t _mi_heap_main
----------------------------
mi_threadid_t _mi_thread_id(void)
{
  return _mi_prim_thread_id();
}


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


void _mi_tld_init(mi_tld_t *tld, mi_heap_t *bheap)
{
  _mi_memcpy_aligned(tld, &tld_empty, sizeof(mi_tld_t));
  tld->heap_backing = bheap;
  tld->heaps = 0;
  tld->segments.subproc = &mi_subproc_default;
  tld->segments.stats = &tld->stats;
}


/*** DEPENDENCIES:
static const mi_tld_t tld_empty = {0, 0, 0, 0, {{{0, 0, 1}, {0, 0, 1}, {0, 0, 2}, {0, 0, 3}, {0, 0, 4}, {0, 0, 5}, {0, 0, 6}, {0, 0, 7}, {0, 0, 10}, {0, 0, 12}, {0, 0, 14}, {0, 0, 16}, {0, 0, 20}, {0, 0, 24}, {0, 0, 28}, {0, 0, 32}, {0, 0, 40}, {0, 0, 48}, {0, 0, 56}, {0, 0, 64}, {0, 0, 80}, {0, 0, 96}, {0, 0, 112}, {0, 0, 128}, {0, 0, 160}, {0, 0, 192}, {0, 0, 224}, {0, 0, 256}, {0, 0, 320}, {0, 0, 384}, {0, 0, 448}, {0, 0, 512}, {0, 0, 640}, {0, 0, 768}, {0, 0, 896}, {0, 0, 1024}}, 0, 0, 0, 0, 0, &mi_subproc_default, (mi_stats_t *) (((uint8_t *) (&tld_empty)) + offsetof(mi_tld_t, stats))}, {1, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0}, {0}, {0}, {0}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0}, {0}, {0}, {0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}}}
----------------------------
static mi_subproc_t mi_subproc_default
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


void _mi_heap_guarded_init(mi_heap_t *heap)
{
  (void) heap;
}


/*** DEPENDENCIES:
None
----------------------------
***/


static mi_thread_data_t *mi_thread_data_zalloc(void)
{
  mi_thread_data_t *td = 0;
  unsigned int td_idx = 0;
  for (int i = 0; i < 32; i += 1)
  {
    td_idx = atomic_load_explicit(&td_cache[i], memory_order_relaxed);
    if ((&td[td_idx]) != 0)
    {
      td_idx = atomic_exchange_explicit(&td_cache[i], 0, memory_order_acq_rel);
      if ((&td[td_idx]) != 0)
      {
        _mi_memzero(td, offsetof(mi_thread_data_t, memid));
        return td;
      }
    }
  }

  mi_memid_t memid;
  td_idx = (mi_thread_data_t *) _mi_os_zalloc(sizeof(mi_thread_data_t), &memid);
  if ((&td[td_idx]) == 0)
  {
    td_idx = (mi_thread_data_t *) _mi_os_zalloc(sizeof(mi_thread_data_t), &memid);
    if ((&td[td_idx]) == 0)
    {
      _mi_error_message(12, "unable to allocate thread local heap metadata (%zu bytes)\n", sizeof(mi_thread_data_t));
      return 0;
    }
  }
  td->memid = memid;
  return td;
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
inline static void _mi_memzero(void *dst, size_t n)
{
  memset(dst, 0, n);
}


----------------------------
void *_mi_os_zalloc(size_t size, mi_memid_t *memid)
{
  void *p = _mi_os_alloc(size, memid);
  return mi_os_ensure_zero(p, size, memid);
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
typedef struct mi_thread_data_s
{
  mi_heap_t heap;
  mi_tld_t tld;
  mi_memid_t memid;
} mi_thread_data_t
----------------------------
static mi_thread_data_t * _Atomic td_cache[32]
----------------------------
***/


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


/*** DEPENDENCIES:
void _mi_heap_guarded_init(mi_heap_t *heap)
{
  (void) heap;
}


----------------------------
extern mi_heap_t _mi_heap_main
----------------------------
uintptr_t _mi_heap_random_next(mi_heap_t *heap)
{
  return _mi_random_next(&heap->random);
}


----------------------------
void _mi_random_init(mi_random_ctx_t *ctx)
{
  mi_random_init_ex(ctx, 0);
}


----------------------------
mi_threadid_t _mi_thread_id(void)
{
  return _mi_prim_thread_id();
}


----------------------------
inline static void mi_lock_init(pthread_mutex_t *lock)
{
  pthread_mutex_init(lock, 0);
}


----------------------------
static mi_subproc_t mi_subproc_default
----------------------------
***/


void _mi_heap_set_default_direct(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/init.c", 544, __func__));
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


/*** DEPENDENCIES:
static mi_thread_data_t *mi_thread_data_zalloc(void)
{
  mi_thread_data_t *td = 0;
  unsigned int td_idx = 0;
  for (int i = 0; i < 32; i += 1)
  {
    td_idx = atomic_load_explicit(&td_cache[i], memory_order_relaxed);
    if ((&td[td_idx]) != 0)
    {
      td_idx = atomic_exchange_explicit(&td_cache[i], 0, memory_order_acq_rel);
      if ((&td[td_idx]) != 0)
      {
        _mi_memzero(td, offsetof(mi_thread_data_t, memid));
        return td;
      }
    }
  }

  mi_memid_t memid;
  td_idx = (mi_thread_data_t *) _mi_os_zalloc(sizeof(mi_thread_data_t), &memid);
  if ((&td[td_idx]) == 0)
  {
    td_idx = (mi_thread_data_t *) _mi_os_zalloc(sizeof(mi_thread_data_t), &memid);
    if ((&td[td_idx]) == 0)
    {
      _mi_error_message(12, "unable to allocate thread local heap metadata (%zu bytes)\n", sizeof(mi_thread_data_t));
      return 0;
    }
  }
  td->memid = memid;
  return td;
}


----------------------------
typedef struct mi_thread_data_s
{
  mi_heap_t heap;
  mi_tld_t tld;
  mi_memid_t memid;
} mi_thread_data_t
----------------------------
inline static bool mi_heap_is_initialized(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 501, __func__));
  return (heap != 0) && (heap != (&_mi_heap_empty));
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
extern mi_heap_t _mi_heap_main
----------------------------
void _mi_heap_set_default_direct(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/init.c", 544, __func__));
  _mi_heap_default = heap;
  _mi_prim_thread_associate_default_heap(heap);
}


----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


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
void _mi_tld_init(mi_tld_t *tld, mi_heap_t *bheap)
{
  _mi_memcpy_aligned(tld, &tld_empty, sizeof(mi_tld_t));
  tld->heap_backing = bheap;
  tld->heaps = 0;
  tld->segments.subproc = &mi_subproc_default;
  tld->segments.stats = &tld->stats;
}


----------------------------
mi_arena_id_t _mi_arena_id_none(void)
{
  return 0;
}


----------------------------
bool _mi_is_main_thread(void)
{
  return (_mi_heap_main.thread_id == 0) || (_mi_heap_main.thread_id == _mi_thread_id());
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
void _mi_os_free(void *p, size_t size, mi_memid_t memid)
{
  _mi_os_free_ex(p, size, 1, memid);
}


----------------------------
typedef struct mi_thread_data_s
{
  mi_heap_t heap;
  mi_tld_t tld;
  mi_memid_t memid;
} mi_thread_data_t
----------------------------
static mi_thread_data_t * _Atomic td_cache[32]
----------------------------
***/


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


/*** DEPENDENCIES:
void _mi_os_free(void *p, size_t size, mi_memid_t memid)
{
  _mi_os_free_ex(p, size, 1, memid);
}


----------------------------
typedef struct mi_thread_data_s
{
  mi_heap_t heap;
  mi_tld_t tld;
  mi_memid_t memid;
} mi_thread_data_t
----------------------------
static mi_thread_data_t * _Atomic td_cache[32]
----------------------------
***/


void mi_thread_done(void)
{
  _mi_thread_done(0);
}


/*** DEPENDENCIES:
None
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


void _mi_auto_process_init(void)
{
  mi_heap_main_init();
  os_preloading = 0;
  (_mi_is_main_thread()) ? ((void) 0) : (_mi_assert_fail("_mi_is_main_thread()", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/init.c", 587, __func__));
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
  _mi_random_reinit_if_weak(&_mi_heap_main.random);
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
None
----------------------------
void _mi_fputs(mi_output_fun *out, void *arg, const char *prefix, const char *message)
{
  unsigned int out_idx = 0;
  if ((((&out[out_idx]) == 0) || (((void *) out) == ((void *) stdout))) || (((void *) out) == ((void *) stderr)))
  {
    if (!mi_recurse_enter())
    {
      return;
    }
    out_idx = mi_out_get_default(&arg);
    if (prefix != 0)
    {
      out(prefix, arg);
    }
    out(message, arg);
    mi_recurse_exit();
  }
  else
  {
    if (prefix != 0)
    {
      out(prefix, arg);
    }
    out(message, arg);
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
bool _mi_is_redirected(void)
{
  return 0;
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
extern mi_heap_t _mi_heap_main
----------------------------
static bool os_preloading = 1
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
bool _mi_is_main_thread(void)
{
  return (_mi_heap_main.thread_id == 0) || (_mi_heap_main.thread_id == _mi_thread_id());
}


----------------------------
None
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
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/init.c", 678, __func__));
  _mi_prim_thread_done_auto_done();
  mi_heap_collect(heap, 1);
  if (mi_option_is_enabled(mi_option_destroy_on_exit))
  {
    mi_heap_collect(heap, 1);
    _mi_heap_unsafe_destroy_all(heap);
    _mi_arena_unsafe_destroy_all();
    _mi_segment_map_unsafe_destroy();
  }
  if (mi_option_is_enabled(mi_option_show_stats) || mi_option_is_enabled(mi_option_verbose))
  {
    mi_stats_print(0);
  }
  _mi_allocator_done();
  _mi_verbose_message("process done: 0x%zx\n", _mi_heap_main.thread_id);
  os_preloading = 1;
}


/*** DEPENDENCIES:
void _mi_arena_unsafe_destroy_all(void)
{
  mi_arenas_unsafe_destroy();
  _mi_arenas_collect(1);
}


----------------------------
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
void mi_heap_collect(mi_heap_t *heap, bool force)
{
  mi_heap_collect_ex(heap, (force) ? (MI_FORCE) : (MI_NORMAL));
}


----------------------------
extern mi_heap_t _mi_heap_main
----------------------------
extern bool _mi_process_is_initialized
----------------------------
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}


----------------------------
void _mi_prim_thread_done_auto_done(void)
{
  if (_mi_heap_default_key != ((pthread_key_t) (-1)))
  {
    pthread_key_delete(_mi_heap_default_key);
  }
}


----------------------------
static bool os_preloading = 1
----------------------------
void _mi_segment_map_unsafe_destroy(void)
{
  for (size_t i = 0; i < ((((48 * 1024ULL) * ((1024UL * 1024UL) * 1024UL)) / ((8 * (((1 << 3) * 1024UL) - 128)) * (1UL << (9 + (13 + 3))))) + 1); i += 1)
  {
    mi_segmap_part_t *part = atomic_exchange_explicit(&mi_segment_map[i], 0, memory_order_relaxed);
    if (part != 0)
    {
      _mi_os_free(part, sizeof(mi_segmap_part_t), part->memid);
    }
  }

}


----------------------------
void _mi_allocator_done(void)
{
}


----------------------------
None
----------------------------
void mi_stats_print(void *out)
{
  mi_stats_print_out((mi_output_fun *) out, 0);
}


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
  ((option >= 0) && (option < _mi_option_last)) ? ((void) 0) : (_mi_assert_fail("option >= 0 && option < _mi_option_last", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/options.c", 238, __func__));
  mi_option_desc_t *desc = &options[option];
  (desc->option == option) ? ((void) 0) : (_mi_assert_fail("desc->option == option", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/options.c", 240, __func__));
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
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/init.c", 678, __func__));
  _mi_prim_thread_done_auto_done();
  mi_heap_collect(heap, 1);
  if (mi_option_is_enabled(mi_option_destroy_on_exit))
  {
    mi_heap_collect(heap, 1);
    _mi_heap_unsafe_destroy_all(heap);
    _mi_arena_unsafe_destroy_all();
    _mi_segment_map_unsafe_destroy();
  }
  if (mi_option_is_enabled(mi_option_show_stats) || mi_option_is_enabled(mi_option_verbose))
  {
    mi_stats_print(0);
  }
  _mi_allocator_done();
  _mi_verbose_message("process done: 0x%zx\n", _mi_heap_main.thread_id);
  os_preloading = 1;
}


----------------------------
***/


mi_heap_t *_mi_heap_main_get(void)
{
  mi_heap_main_init();
  return &_mi_heap_main;
}


/*** DEPENDENCIES:
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
extern mi_heap_t _mi_heap_main
----------------------------
None
----------------------------
***/


mi_subproc_t *_mi_subproc_from_id(mi_subproc_id_t subproc_id)
{
  return (subproc_id == 0) ? (&mi_subproc_default) : ((mi_subproc_t *) subproc_id);
}


/*** DEPENDENCIES:
static mi_subproc_t mi_subproc_default
----------------------------
typedef void *mi_subproc_id_t
----------------------------
None
----------------------------
***/


mi_subproc_id_t mi_subproc_new(void)
{
  mi_memid_t memid = _mi_memid_none();
  mi_subproc_t *subproc = (mi_subproc_t *) _mi_arena_meta_zalloc(sizeof(mi_subproc_t), &memid);
  if (subproc == 0)
  {
    return 0;
  }
  subproc->memid = memid;
  subproc->abandoned_os_list = 0;
  mi_lock_init(&subproc->abandoned_os_lock);
  mi_lock_init(&subproc->abandoned_os_visit_lock);
  return subproc;
}


/*** DEPENDENCIES:
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
void *_mi_arena_meta_zalloc(size_t size, mi_memid_t *memid)
{
  *memid = _mi_memid_none();
  void *p = mi_arena_static_zalloc(size, 16, memid);
  unsigned int p_idx = 0;
  if ((&p[p_idx]) != 0)
  {
    return p;
  }
  p_idx = _mi_os_zalloc(size, memid);
  if ((&p[p_idx]) == 0)
  {
    return 0;
  }
  return p;
}


----------------------------
inline static void mi_lock_init(pthread_mutex_t *lock)
{
  pthread_mutex_init(lock, 0);
}


----------------------------
inline static mi_memid_t _mi_memid_none(void)
{
  return _mi_memid_create(MI_MEM_NONE);
}


----------------------------
None
----------------------------
***/


void mi_subproc_add_current_thread(mi_subproc_id_t subproc_id)
{
  mi_heap_t *heap = mi_heap_get_default();
  if (heap == 0)
  {
    return;
  }
  (heap->tld->segments.subproc == (&mi_subproc_default)) ? ((void) 0) : (_mi_assert_fail("heap->tld->segments.subproc == &mi_subproc_default", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/init.c", 291, __func__));
  if (heap->tld->segments.subproc != (&mi_subproc_default))
  {
    return;
  }
  heap->tld->segments.subproc = _mi_subproc_from_id(subproc_id);
}


/*** DEPENDENCIES:
typedef void *mi_subproc_id_t
----------------------------
None
----------------------------
None
----------------------------
mi_subproc_t *_mi_subproc_from_id(mi_subproc_id_t subproc_id)
{
  return (subproc_id == 0) ? (&mi_subproc_default) : ((mi_subproc_t *) subproc_id);
}


----------------------------
static mi_subproc_t mi_subproc_default
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
  for (bool _go = (mi_lock_acquire(&subproc->abandoned_os_lock), 1); _go; mi_lock_release(&subproc->abandoned_os_lock), _go = 0)
  {
    if (subproc->abandoned_os_list == 0)
    {
      safe_to_delete = 1;
    }
  }

  if (!safe_to_delete)
  {
    return;
  }
  mi_lock_done(&subproc->abandoned_os_lock);
  mi_lock_done(&subproc->abandoned_os_visit_lock);
  _mi_arena_meta_free(subproc, subproc->memid, sizeof(mi_subproc_t));
}


/*** DEPENDENCIES:
typedef void *mi_subproc_id_t
----------------------------
void _mi_arena_meta_free(void *p, mi_memid_t memid, size_t size)
{
  if (mi_memkind_is_os(memid.memkind))
  {
    _mi_os_free(p, size, memid);
  }
  else
  {
    (memid.memkind == MI_MEM_STATIC) ? ((void) 0) : (_mi_assert_fail("memid.memkind == MI_MEM_STATIC", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 206, __func__));
  }
}


----------------------------
inline static void mi_lock_done(pthread_mutex_t *lock)
{
  pthread_mutex_destroy(lock);
}


----------------------------
mi_subproc_t *_mi_subproc_from_id(mi_subproc_id_t subproc_id)
{
  return (subproc_id == 0) ? (&mi_subproc_default) : ((mi_subproc_t *) subproc_id);
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


