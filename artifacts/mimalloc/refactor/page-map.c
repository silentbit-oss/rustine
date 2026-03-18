#include <atomic.h>
#include <bitmap.h>
#include <bits.h>
#include <errno.h>
#include <internal.h>
#include <limits.h>
#include <mimalloc-stats.h>
#include <mimalloc.h>
#include <page-map.c>
#include <pthread.h>
#include <stdarg.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <track.h>
#include <types.h>

void *mi_malloc(size_t size);
void *mi_calloc(size_t count, size_t size);
void *mi_realloc(void *p, size_t newsize);
void *mi_expand(void *p, size_t newsize);
void mi_free(void *p);
char *mi_strdup(const char *s);
char *mi_strndup(const char *s, size_t n);
char *mi_realpath(const char *fname, char *resolved_name);
void *mi_malloc_small(size_t size);
void *mi_zalloc_small(size_t size);
void *mi_zalloc(size_t size);
void *mi_mallocn(size_t count, size_t size);
void *mi_reallocn(void *p, size_t count, size_t size);
void *mi_reallocf(void *p, size_t newsize);
size_t mi_usable_size(const void *p);
size_t mi_good_size(size_t size);
typedef void mi_deferred_free_fun(bool force, unsigned long long heartbeat, void *arg);
void mi_register_deferred_free(mi_deferred_free_fun *deferred_free, void *arg);
typedef void mi_output_fun(const char *msg, void *arg);
void mi_register_output(mi_output_fun *out, void *arg);
typedef void mi_error_fun(int err, void *arg);
void mi_register_error(mi_error_fun *fun, void *arg);
void mi_collect(bool force);
int mi_version(void);
void mi_stats_reset(void);
void mi_stats_merge(void);
void mi_stats_print(void *out);
void mi_stats_print_out(mi_output_fun *out, void *arg);
void mi_thread_stats_print_out(mi_output_fun *out, void *arg);
void mi_options_print(void);
void mi_process_info(size_t *elapsed_msecs, size_t *user_msecs, size_t *system_msecs, size_t *current_rss, size_t *peak_rss, size_t *current_commit, size_t *peak_commit, size_t *page_faults);
void mi_process_init(void);
void mi_process_done(void);
void mi_thread_init(void);
void mi_thread_done(void);
void *mi_malloc_aligned(size_t size, size_t alignment);
void *mi_malloc_aligned_at(size_t size, size_t alignment, size_t offset);
void *mi_zalloc_aligned(size_t size, size_t alignment);
void *mi_zalloc_aligned_at(size_t size, size_t alignment, size_t offset);
void *mi_calloc_aligned(size_t count, size_t size, size_t alignment);
void *mi_calloc_aligned_at(size_t count, size_t size, size_t alignment, size_t offset);
void *mi_realloc_aligned(void *p, size_t newsize, size_t alignment);
void *mi_realloc_aligned_at(void *p, size_t newsize, size_t alignment, size_t offset);
struct mi_heap_s;
typedef struct mi_heap_s mi_heap_t;
mi_heap_t *mi_heap_new(void);
void mi_heap_delete(mi_heap_t *heap);
void mi_heap_destroy(mi_heap_t *heap);
mi_heap_t *mi_heap_set_default(mi_heap_t *heap);
mi_heap_t *mi_heap_get_default(void);
mi_heap_t *mi_heap_get_backing(void);
void mi_heap_collect(mi_heap_t *heap, bool force);
void *mi_heap_malloc(mi_heap_t *heap, size_t size);
void *mi_heap_zalloc(mi_heap_t *heap, size_t size);
void *mi_heap_calloc(mi_heap_t *heap, size_t count, size_t size);
void *mi_heap_mallocn(mi_heap_t *heap, size_t count, size_t size);
void *mi_heap_malloc_small(mi_heap_t *heap, size_t size);
void *mi_heap_realloc(mi_heap_t *heap, void *p, size_t newsize);
void *mi_heap_reallocn(mi_heap_t *heap, void *p, size_t count, size_t size);
void *mi_heap_reallocf(mi_heap_t *heap, void *p, size_t newsize);
char *mi_heap_strdup(mi_heap_t *heap, const char *s);
char *mi_heap_strndup(mi_heap_t *heap, const char *s, size_t n);
char *mi_heap_realpath(mi_heap_t *heap, const char *fname, char *resolved_name);
void *mi_heap_malloc_aligned(mi_heap_t *heap, size_t size, size_t alignment);
void *mi_heap_malloc_aligned_at(mi_heap_t *heap, size_t size, size_t alignment, size_t offset);
void *mi_heap_zalloc_aligned(mi_heap_t *heap, size_t size, size_t alignment);
void *mi_heap_zalloc_aligned_at(mi_heap_t *heap, size_t size, size_t alignment, size_t offset);
void *mi_heap_calloc_aligned(mi_heap_t *heap, size_t count, size_t size, size_t alignment);
void *mi_heap_calloc_aligned_at(mi_heap_t *heap, size_t count, size_t size, size_t alignment, size_t offset);
void *mi_heap_realloc_aligned(mi_heap_t *heap, void *p, size_t newsize, size_t alignment);
void *mi_heap_realloc_aligned_at(mi_heap_t *heap, void *p, size_t newsize, size_t alignment, size_t offset);
void *mi_rezalloc(void *p, size_t newsize);
void *mi_recalloc(void *p, size_t newcount, size_t size);
void *mi_rezalloc_aligned(void *p, size_t newsize, size_t alignment);
void *mi_rezalloc_aligned_at(void *p, size_t newsize, size_t alignment, size_t offset);
void *mi_recalloc_aligned(void *p, size_t newcount, size_t size, size_t alignment);
void *mi_recalloc_aligned_at(void *p, size_t newcount, size_t size, size_t alignment, size_t offset);
void *mi_heap_rezalloc(mi_heap_t *heap, void *p, size_t newsize);
void *mi_heap_recalloc(mi_heap_t *heap, void *p, size_t newcount, size_t size);
void *mi_heap_rezalloc_aligned(mi_heap_t *heap, void *p, size_t newsize, size_t alignment);
void *mi_heap_rezalloc_aligned_at(mi_heap_t *heap, void *p, size_t newsize, size_t alignment, size_t offset);
void *mi_heap_recalloc_aligned(mi_heap_t *heap, void *p, size_t newcount, size_t size, size_t alignment);
void *mi_heap_recalloc_aligned_at(mi_heap_t *heap, void *p, size_t newcount, size_t size, size_t alignment, size_t offset);
bool mi_heap_contains_block(mi_heap_t *heap, const void *p);
bool mi_heap_check_owned(mi_heap_t *heap, const void *p);
bool mi_check_owned(const void *p);
typedef struct mi_heap_area_s
{
  void *blocks;
  size_t reserved;
  size_t committed;
  size_t used;
  size_t block_size;
  size_t full_block_size;
  int heap_tag;
} mi_heap_area_t;
typedef bool mi_block_visit_fun(const mi_heap_t *heap, const mi_heap_area_t *area, void *block, size_t block_size, void *arg);
bool mi_heap_visit_blocks(const mi_heap_t *heap, bool visit_blocks, mi_block_visit_fun *visitor, void *arg);
bool mi_is_in_heap_region(const void *p);
bool mi_is_redirected(void);
int mi_reserve_huge_os_pages_interleave(size_t pages, size_t numa_nodes, size_t timeout_msecs);
int mi_reserve_huge_os_pages_at(size_t pages, int numa_node, size_t timeout_msecs);
int mi_reserve_os_memory(size_t size, bool commit, bool allow_large);
bool mi_manage_os_memory(void *start, size_t size, bool is_committed, bool is_pinned, bool is_zero, int numa_node);
void mi_debug_show_arenas(void);
void mi_arenas_print(void);
size_t mi_arena_min_alignment(void);
typedef void *mi_arena_id_t;
void *mi_arena_area(mi_arena_id_t arena_id, size_t *size);
int mi_reserve_huge_os_pages_at_ex(size_t pages, int numa_node, size_t timeout_msecs, bool exclusive, mi_arena_id_t *arena_id);
int mi_reserve_os_memory_ex(size_t size, bool commit, bool allow_large, bool exclusive, mi_arena_id_t *arena_id);
bool mi_manage_os_memory_ex(void *start, size_t size, bool is_committed, bool is_pinned, bool is_zero, int numa_node, bool exclusive, mi_arena_id_t *arena_id);
mi_heap_t *mi_heap_new_in_arena(mi_arena_id_t arena_id);
typedef void *mi_subproc_id_t;
mi_subproc_id_t mi_subproc_main(void);
mi_subproc_id_t mi_subproc_new(void);
void mi_subproc_delete(mi_subproc_id_t subproc);
void mi_subproc_add_current_thread(mi_subproc_id_t subproc);
bool mi_abandoned_visit_blocks(mi_subproc_id_t subproc_id, int heap_tag, bool visit_blocks, mi_block_visit_fun *visitor, void *arg);
void mi_heap_set_numa_affinity(mi_heap_t *heap, int numa_node);
void mi_heap_guarded_set_sample_rate(mi_heap_t *heap, size_t sample_rate, size_t seed);
void mi_heap_guarded_set_size_bound(mi_heap_t *heap, size_t min, size_t max);
void mi_thread_set_in_threadpool(void);
mi_heap_t *mi_heap_new_ex(int heap_tag, bool allow_destroy, mi_arena_id_t arena_id);
int mi_reserve_huge_os_pages(size_t pages, double max_secs, size_t *pages_reserved);
void mi_collect_reduce(size_t target_thread_owned);
typedef bool mi_commit_fun_t(bool commit, void *start, size_t size, bool *is_zero, void *user_arg);
bool mi_manage_memory(void *start, size_t size, bool is_committed, bool is_pinned, bool is_zero, int numa_node, bool exclusive, mi_commit_fun_t *commit_fun, void *commit_fun_arg, mi_arena_id_t *arena_id);
bool mi_arena_unload(mi_arena_id_t arena_id, void **base, size_t *accessed_size, size_t *size);
bool mi_arena_reload(void *start, size_t size, mi_commit_fun_t *commit_fun, void *commit_fun_arg, mi_arena_id_t *arena_id);
bool mi_heap_reload(mi_heap_t *heap, mi_arena_id_t arena);
void mi_heap_unload(mi_heap_t *heap);
bool mi_arena_contains(mi_arena_id_t arena_id, const void *p);
typedef enum mi_option_e
{
  mi_option_show_errors,
  mi_option_show_stats,
  mi_option_verbose,
  mi_option_eager_commit,
  mi_option_arena_eager_commit,
  mi_option_purge_decommits,
  mi_option_allow_large_os_pages,
  mi_option_reserve_huge_os_pages,
  mi_option_reserve_huge_os_pages_at,
  mi_option_reserve_os_memory,
  mi_option_deprecated_segment_cache,
  mi_option_deprecated_page_reset,
  mi_option_abandoned_page_purge,
  mi_option_deprecated_segment_reset,
  mi_option_eager_commit_delay,
  mi_option_purge_delay,
  mi_option_use_numa_nodes,
  mi_option_disallow_os_alloc,
  mi_option_os_tag,
  mi_option_max_errors,
  mi_option_max_warnings,
  mi_option_deprecated_max_segment_reclaim,
  mi_option_destroy_on_exit,
  mi_option_arena_reserve,
  mi_option_arena_purge_mult,
  mi_option_deprecated_purge_extend_delay,
  mi_option_disallow_arena_alloc,
  mi_option_retry_on_oom,
  mi_option_visit_abandoned,
  mi_option_guarded_min,
  mi_option_guarded_max,
  mi_option_guarded_precise,
  mi_option_guarded_sample_rate,
  mi_option_guarded_sample_seed,
  mi_option_generic_collect,
  mi_option_page_reclaim_on_free,
  mi_option_page_full_retain,
  mi_option_page_max_candidates,
  mi_option_max_vabits,
  mi_option_pagemap_commit,
  mi_option_page_commit_on_demand,
  mi_option_page_max_reclaim,
  mi_option_page_cross_thread_max_reclaim,
  _mi_option_last,
  mi_option_large_os_pages = mi_option_allow_large_os_pages,
  mi_option_eager_region_commit = mi_option_arena_eager_commit,
  mi_option_reset_decommits = mi_option_purge_decommits,
  mi_option_reset_delay = mi_option_purge_delay,
  mi_option_abandoned_page_reset = mi_option_abandoned_page_purge,
  mi_option_limit_os_alloc = mi_option_disallow_os_alloc
} mi_option_t;
bool mi_option_is_enabled(mi_option_t option);
void mi_option_enable(mi_option_t option);
void mi_option_disable(mi_option_t option);
void mi_option_set_enabled(mi_option_t option, bool enable);
void mi_option_set_enabled_default(mi_option_t option, bool enable);
long mi_option_get(mi_option_t option);
long mi_option_get_clamp(mi_option_t option, long min, long max);
size_t mi_option_get_size(mi_option_t option);
void mi_option_set(mi_option_t option, long value);
void mi_option_set_default(mi_option_t option, long value);
void mi_cfree(void *p);
void *mi__expand(void *p, size_t newsize);
size_t mi_malloc_size(const void *p);
size_t mi_malloc_good_size(size_t size);
size_t mi_malloc_usable_size(const void *p);
int mi_posix_memalign(void **p, size_t alignment, size_t size);
void *mi_memalign(size_t alignment, size_t size);
void *mi_valloc(size_t size);
void *mi_pvalloc(size_t size);
void *mi_aligned_alloc(size_t alignment, size_t size);
void *mi_reallocarray(void *p, size_t count, size_t size);
int mi_reallocarr(void *p, size_t count, size_t size);
void *mi_aligned_recalloc(void *p, size_t newcount, size_t size, size_t alignment);
void *mi_aligned_offset_recalloc(void *p, size_t newcount, size_t size, size_t alignment, size_t offset);
unsigned short *mi_wcsdup(const unsigned short *s);
unsigned char *mi_mbsdup(const unsigned char *s);
int mi_dupenv_s(char **buf, size_t *size, const char *name);
int mi_wdupenv_s(unsigned short **buf, size_t *size, const unsigned short *name);
void mi_free_size(void *p, size_t size);
void mi_free_size_aligned(void *p, size_t size, size_t alignment);
void mi_free_aligned(void *p, size_t alignment);
void *mi_new(size_t size);
void *mi_new_aligned(size_t size, size_t alignment);
void *mi_new_nothrow(size_t size);
void *mi_new_aligned_nothrow(size_t size, size_t alignment);
void *mi_new_n(size_t count, size_t size);
void *mi_new_realloc(void *p, size_t newsize);
void *mi_new_reallocn(void *p, size_t newcount, size_t size);
void *mi_heap_alloc_new(mi_heap_t *heap, size_t size);
void *mi_heap_alloc_new_n(mi_heap_t *heap, size_t count, size_t size);
typedef struct mi_stat_count_s
{
  int64_t total;
  int64_t peak;
  int64_t current;
} mi_stat_count_t;
typedef struct mi_stat_counter_s
{
  int64_t total;
} mi_stat_counter_t;
typedef enum mi_chunkbin_e
{
  MI_CBIN_SMALL,
  MI_CBIN_OTHER,
  MI_CBIN_MEDIUM,
  MI_CBIN_LARGE,
  MI_CBIN_NONE,
  MI_CBIN_COUNT
} mi_chunkbin_t;
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
} mi_stats_t;
void mi_stats_get(size_t stats_size, mi_stats_t *stats);
char *mi_stats_get_json(size_t buf_size, char *buf);
size_t mi_stats_get_bin_size(size_t bin);
typedef int64_t mi_ssize_t;
size_t _mi_popcount_generic(size_t x);
inline static size_t mi_popcount(size_t x)
{
  return __builtin_popcountll(x);
}

size_t _mi_clz_generic(size_t x);
size_t _mi_ctz_generic(size_t x);
inline static size_t mi_ctz(size_t x)
{
  return (x != 0) ? ((size_t) __builtin_ctzll(x)) : ((1 << 3) * 8);
}

inline static size_t mi_clz(size_t x)
{
  return (x != 0) ? ((size_t) __builtin_clzll(x)) : ((1 << 3) * 8);
}

inline static bool mi_bsf(size_t x, size_t *idx)
{
  return (x != 0) ? ((*idx = mi_ctz(x), 1)) : (0);
}

inline static bool mi_bsr(size_t x, size_t *idx)
{
  return (x != 0) ? ((*idx = (((1 << 3) * 8) - 1) - mi_clz(x), 1)) : (0);
}

inline static size_t mi_rotr(size_t x, size_t r)
{
  const unsigned int rshift = ((unsigned int) r) & (((1 << 3) * 8) - 1);
  return (x >> rshift) | (x << ((-rshift) & (((1 << 3) * 8) - 1)));
}

inline static size_t mi_rotl(size_t x, size_t r)
{
  const unsigned int rshift = ((unsigned int) r) & (((1 << 3) * 8) - 1);
  return (x << rshift) | (x >> ((-rshift) & (((1 << 3) * 8) - 1)));
}

inline static uint32_t mi_rotl32(uint32_t x, uint32_t r)
{
  const unsigned int rshift = ((unsigned int) r) & 31;
  return (x << rshift) | (x >> ((-rshift) & 31));
}

inline static void mi_atomic_yield(void);
inline static intptr_t mi_atomic_addi(_Atomic intptr_t *p, intptr_t add);
inline static intptr_t mi_atomic_subi(_Atomic intptr_t *p, intptr_t sub);
inline static int64_t mi_atomic_addi64_relaxed(volatile int64_t *p, int64_t add)
{
  return atomic_fetch_add_explicit((int64_t *) p, add, memory_order_relaxed);
}

inline static void mi_atomic_void_addi64_relaxed(volatile int64_t *p, const volatile int64_t *padd)
{
  const int64_t add = atomic_load_explicit((int64_t *) padd, memory_order_relaxed);
  if (add != 0)
  {
    atomic_fetch_add_explicit((int64_t *) p, add, memory_order_relaxed);
  }
}

inline static void mi_atomic_maxi64_relaxed(volatile int64_t *p, int64_t x)
{
  int64_t current = atomic_load_explicit((int64_t *) p, memory_order_relaxed);
  while ((current < x) && (!atomic_compare_exchange_weak_explicit((int64_t *) p, &current, x, memory_order_release, memory_order_relaxed)))
  {
  }

  ;
}

inline static intptr_t mi_atomic_addi(_Atomic intptr_t *p, intptr_t add)
{
  return (intptr_t) atomic_fetch_add_explicit((uintptr_t *) p, (uintptr_t) add, memory_order_acq_rel);
}

inline static intptr_t mi_atomic_subi(_Atomic intptr_t *p, intptr_t sub)
{
  return (intptr_t) mi_atomic_addi(p, -sub);
}

typedef _Atomic uintptr_t mi_atomic_once_t;
inline static bool mi_atomic_once(mi_atomic_once_t *once)
{
  if (atomic_load_explicit(once, memory_order_relaxed) != 0)
  {
    return 0;
  }
  uintptr_t expected = 0;
  return atomic_compare_exchange_strong_explicit(once, &expected, (uintptr_t) 1, memory_order_acq_rel, memory_order_acquire);
}

typedef _Atomic uintptr_t mi_atomic_guard_t;
inline static void mi_atomic_yield(void)
{
}

void _mi_error_message(int err, const char *fmt, ...);
inline static bool mi_lock_try_acquire(pthread_mutex_t *lock)
{
  return pthread_mutex_trylock(lock) == 0;
}

inline static void mi_lock_acquire(pthread_mutex_t *lock)
{
  const int err = pthread_mutex_lock(lock);
  if (err != 0)
  {
    _mi_error_message(err, "internal error: lock cannot be acquired\n");
  }
}

inline static void mi_lock_release(pthread_mutex_t *lock)
{
  pthread_mutex_unlock(lock);
}

inline static void mi_lock_init(pthread_mutex_t *lock)
{
  pthread_mutex_init(lock, 0);
}

inline static void mi_lock_done(pthread_mutex_t *lock)
{
  pthread_mutex_destroy(lock);
}

typedef struct mi_arena_s mi_arena_t;
typedef enum mi_memkind_e
{
  MI_MEM_NONE,
  MI_MEM_EXTERNAL,
  MI_MEM_STATIC,
  MI_MEM_META,
  MI_MEM_OS,
  MI_MEM_OS_HUGE,
  MI_MEM_OS_REMAP,
  MI_MEM_ARENA
} mi_memkind_t;
inline static bool mi_memkind_is_os(mi_memkind_t memkind)
{
  return (memkind >= MI_MEM_OS) && (memkind <= MI_MEM_OS_REMAP);
}

inline static bool mi_memkind_needs_no_free(mi_memkind_t memkind)
{
  return memkind <= MI_MEM_STATIC;
}

typedef struct mi_memid_os_info
{
  void *base;
  size_t size;
} mi_memid_os_info_t;
typedef struct mi_memid_arena_info
{
  mi_arena_t *arena;
  uint32_t slice_index;
  uint32_t slice_count;
} mi_memid_arena_info_t;
typedef struct mi_memid_meta_info
{
  void *meta_page;
  uint32_t block_index;
  uint32_t block_count;
} mi_memid_meta_info_t;
typedef struct mi_memid_s
{
  union 
  {
    mi_memid_os_info_t os;
    mi_memid_arena_info_t arena;
    mi_memid_meta_info_t meta;
  } mem;
  mi_memkind_t memkind;
  bool is_pinned;
  bool initially_committed;
  bool initially_zero;
} mi_memid_t;
inline static bool mi_memid_is_os(mi_memid_t memid)
{
  return mi_memkind_is_os(memid.memkind);
}

inline static bool mi_memid_needs_no_free(mi_memid_t memid)
{
  return mi_memkind_needs_no_free(memid.memkind);
}

inline static mi_arena_t *mi_memid_arena(mi_memid_t memid)
{
  return (memid.memkind == MI_MEM_ARENA) ? (memid.mem.arena.arena) : (0);
}

typedef uintptr_t mi_encoded_t;
typedef size_t mi_threadid_t;
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t;
typedef size_t mi_page_flags_t;
typedef uintptr_t mi_thread_free_t;
typedef uint8_t mi_heaptag_t;
typedef struct mi_page_s
{
  _Atomic mi_threadid_t xthread_id;
  mi_block_t *free;
  uint16_t used;
  uint16_t capacity;
  uint16_t reserved;
  uint8_t retire_expire;
  mi_block_t *local_free;
  _Atomic mi_thread_free_t xthread_free;
  size_t block_size;
  uint8_t *page_start;
  mi_heaptag_t heap_tag;
  bool free_is_zero;
  uintptr_t keys[2];
  mi_heap_t *heap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  size_t slice_committed;
  mi_memid_t memid;
} mi_page_t;
typedef enum mi_page_kind_e
{
  MI_PAGE_SMALL,
  MI_PAGE_MEDIUM,
  MI_PAGE_LARGE,
  MI_PAGE_SINGLETON
} mi_page_kind_t;
typedef struct mi_tld_s mi_tld_t;
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t count;
  size_t block_size;
} mi_page_queue_t;
typedef struct mi_random_cxt_s
{
  uint32_t input[16];
  uint32_t output[16];
  int output_available;
  bool weak;
} mi_random_ctx_t;
typedef struct mi_padding_s
{
  uint32_t canary;
  uint32_t delta;
} mi_padding_t;
struct mi_heap_s
{
  mi_tld_t *tld;
  mi_arena_t *exclusive_arena;
  int numa_node;
  uintptr_t cookie;
  mi_random_ctx_t random;
  size_t page_count;
  size_t page_retired_min;
  size_t page_retired_max;
  long generic_count;
  long generic_collect_count;
  mi_heap_t *next;
  long page_full_retain;
  bool allow_page_reclaim;
  bool allow_page_abandon;
  uint8_t tag;
  mi_page_t *pages_free_direct[(128 + ((((sizeof(mi_padding_t)) + (1 << 3)) - 1) / (1 << 3))) + 1];
  mi_page_queue_t pages[(73U + 1) + 1];
  mi_memid_t memid;
};
typedef struct mi_subproc_s
{
  _Atomic size_t arena_count;
  mi_arena_t * _Atomic arenas[160];
  pthread_mutex_t arena_reserve_lock;
  _Atomic int64_t purge_expire;
  _Atomic size_t abandoned_count[(73U + 1) + 1];
  mi_page_t *os_abandoned_pages;
  pthread_mutex_t os_abandoned_pages_lock;
  mi_memid_t memid;
  mi_stats_t stats;
} mi_subproc_t;
typedef int64_t mi_msecs_t;
struct mi_tld_s
{
  mi_threadid_t thread_id;
  size_t thread_seq;
  int numa_node;
  mi_subproc_t *subproc;
  mi_heap_t *heap_backing;
  mi_heap_t *heaps;
  unsigned long long heartbeat;
  bool recurse;
  bool is_in_threadpool;
  mi_stats_t stats;
  mi_memid_t memid;
};
typedef struct mi_bitmap_s mi_bitmap_t;
typedef struct mi_bbitmap_s mi_bbitmap_t;
typedef struct mi_arena_s
{
  mi_memid_t memid;
  mi_subproc_t *subproc;
  size_t slice_count;
  size_t info_slices;
  int numa_node;
  bool is_exclusive;
  _Atomic mi_msecs_t purge_expire;
  mi_commit_fun_t *commit_fun;
  void *commit_fun_arg;
  mi_bbitmap_t *slices_free;
  mi_bitmap_t *slices_committed;
  mi_bitmap_t *slices_dirty;
  mi_bitmap_t *slices_purge;
  mi_bitmap_t *pages;
  mi_bitmap_t *pages_abandoned[(73U + 1) + 1];
} mi_arena_t;
int _mi_vsnprintf(char *buf, size_t bufsize, const char *fmt, va_list args);
int _mi_snprintf(char *buf, size_t buflen, const char *fmt, ...);
char _mi_toupper(char c);
int _mi_strnicmp(const char *s, const char *t, size_t n);
void _mi_strlcpy(char *dest, const char *src, size_t dest_size);
void _mi_strlcat(char *dest, const char *src, size_t dest_size);
size_t _mi_strlen(const char *s);
size_t _mi_strnlen(const char *s, size_t max_len);
bool _mi_getenv(const char *name, char *result, size_t result_size);
void _mi_fputs(mi_output_fun *out, void *arg, const char *prefix, const char *message);
void _mi_fprintf(mi_output_fun *out, void *arg, const char *fmt, ...);
void _mi_raw_message(const char *fmt, ...);
void _mi_message(const char *fmt, ...);
void _mi_warning_message(const char *fmt, ...);
void _mi_verbose_message(const char *fmt, ...);
void _mi_trace_message(const char *fmt, ...);
void _mi_options_init(void);
long _mi_option_get_fast(mi_option_t option);
void _mi_error_message(int err, const char *fmt, ...);
void _mi_random_init(mi_random_ctx_t *ctx);
void _mi_random_init_weak(mi_random_ctx_t *ctx);
void _mi_random_reinit_if_weak(mi_random_ctx_t *ctx);
void _mi_random_split(mi_random_ctx_t *ctx, mi_random_ctx_t *new_ctx);
uintptr_t _mi_random_next(mi_random_ctx_t *ctx);
uintptr_t _mi_heap_random_next(mi_heap_t *heap);
uintptr_t _mi_os_random_weak(uintptr_t extra_seed);
inline static uintptr_t _mi_random_shuffle(uintptr_t x);
extern const mi_page_t _mi_page_empty;
void _mi_auto_process_init(void);
void _mi_auto_process_done(void);
bool _mi_is_redirected(void);
bool _mi_allocator_init(const char **message);
void _mi_allocator_done(void);
bool _mi_is_main_thread(void);
size_t _mi_current_thread_count(void);
bool _mi_preloading(void);
void _mi_thread_done(mi_heap_t *heap);
mi_subproc_t *_mi_subproc(void);
mi_subproc_t *_mi_subproc_main(void);
mi_subproc_t *_mi_subproc_from_id(mi_subproc_id_t subproc_id);
mi_threadid_t _mi_thread_id(void);
size_t _mi_thread_seq_id(void);
mi_tld_t *_mi_thread_tld(void);
void _mi_heap_guarded_init(mi_heap_t *heap);
mi_heap_t *_mi_heap_main_get(void);
void _mi_os_init(void);
void *_mi_os_alloc(size_t size, mi_memid_t *memid);
void *_mi_os_zalloc(size_t size, mi_memid_t *memid);
void _mi_os_free(void *p, size_t size, mi_memid_t memid);
void _mi_os_free_ex(void *p, size_t size, bool still_committed, mi_memid_t memid, mi_subproc_t *subproc);
size_t _mi_os_page_size(void);
size_t _mi_os_guard_page_size(void);
size_t _mi_os_good_alloc_size(size_t size);
bool _mi_os_has_overcommit(void);
bool _mi_os_has_virtual_reserve(void);
size_t _mi_os_virtual_address_bits(void);
bool _mi_os_reset(void *addr, size_t size);
bool _mi_os_decommit(void *addr, size_t size);
void _mi_os_reuse(void *p, size_t size);
bool _mi_os_commit(void *p, size_t size, bool *is_zero);
bool _mi_os_commit_ex(void *addr, size_t size, bool *is_zero, size_t stat_size);
bool _mi_os_protect(void *addr, size_t size);
bool _mi_os_unprotect(void *addr, size_t size);
bool _mi_os_purge(void *p, size_t size);
bool _mi_os_purge_ex(void *p, size_t size, bool allow_reset, size_t stats_size, mi_commit_fun_t *commit_fun, void *commit_fun_arg);
size_t _mi_os_secure_guard_page_size(void);
bool _mi_os_secure_guard_page_set_at(void *addr, mi_memid_t memid);
bool _mi_os_secure_guard_page_set_before(void *addr, mi_memid_t memid);
bool _mi_os_secure_guard_page_reset_at(void *addr, mi_memid_t memid);
bool _mi_os_secure_guard_page_reset_before(void *addr, mi_memid_t memid);
int _mi_os_numa_node(void);
int _mi_os_numa_node_count(void);
void *_mi_os_alloc_aligned(size_t size, size_t alignment, bool commit, bool allow_large, mi_memid_t *memid);
void *_mi_os_alloc_aligned_at_offset(size_t size, size_t alignment, size_t align_offset, bool commit, bool allow_large, mi_memid_t *memid);
void *_mi_os_get_aligned_hint(size_t try_alignment, size_t size);
bool _mi_os_use_large_page(size_t size, size_t alignment);
size_t _mi_os_large_page_size(void);
void *_mi_os_alloc_huge_os_pages(size_t pages, int numa_node, mi_msecs_t max_secs, size_t *pages_reserved, size_t *psize, mi_memid_t *memid);
mi_arena_id_t _mi_arena_id_none(void);
mi_arena_t *_mi_arena_from_id(mi_arena_id_t id);
bool _mi_arena_memid_is_suitable(mi_memid_t memid, mi_arena_t *request_arena);
void *_mi_arenas_alloc(mi_subproc_t *subproc, size_t size, bool commit, bool allow_pinned, mi_arena_t *req_arena, size_t tseq, int numa_node, mi_memid_t *memid);
void *_mi_arenas_alloc_aligned(mi_subproc_t *subproc, size_t size, size_t alignment, size_t align_offset, bool commit, bool allow_pinned, mi_arena_t *req_arena, size_t tseq, int numa_node, mi_memid_t *memid);
void _mi_arenas_free(void *p, size_t size, mi_memid_t memid);
bool _mi_arenas_contain(const void *p);
void _mi_arenas_collect(bool force_purge, bool visit_all, mi_tld_t *tld);
void _mi_arenas_unsafe_destroy_all(mi_subproc_t *subproc);
mi_page_t *_mi_arenas_page_alloc(mi_heap_t *heap, size_t block_size, size_t page_alignment);
void _mi_arenas_page_free(mi_page_t *page, mi_tld_t *tld);
void _mi_arenas_page_abandon(mi_page_t *page, mi_tld_t *tld);
void _mi_arenas_page_unabandon(mi_page_t *page);
bool _mi_arenas_page_try_reabandon_to_mapped(mi_page_t *page);
void *_mi_meta_zalloc(size_t size, mi_memid_t *memid);
void _mi_meta_free(void *p, size_t size, mi_memid_t memid);
bool _mi_meta_is_meta_page(void *p);
bool _mi_page_map_init(void);
bool _mi_page_map_register(mi_page_t *page);
void _mi_page_map_unregister(mi_page_t *page);
void _mi_page_map_unregister_range(void *start, size_t size);
mi_page_t *_mi_safe_ptr_page(const void *p);
void _mi_page_map_unsafe_destroy(mi_subproc_t *subproc);
void *_mi_malloc_generic(mi_heap_t *heap, size_t size, bool zero, size_t huge_alignment);
void _mi_page_retire(mi_page_t *page);
void _mi_page_unfull(mi_page_t *page);
void _mi_page_free(mi_page_t *page, mi_page_queue_t *pq);
void _mi_page_abandon(mi_page_t *page, mi_page_queue_t *pq);
void _mi_heap_collect_retired(mi_heap_t *heap, bool force);
size_t _mi_page_queue_append(mi_heap_t *heap, mi_page_queue_t *pq, mi_page_queue_t *append);
void _mi_deferred_free(mi_heap_t *heap, bool force);
void _mi_page_free_collect(mi_page_t *page, bool force);
void _mi_page_free_collect_partly(mi_page_t *page, mi_block_t *head);
bool _mi_page_init(mi_heap_t *heap, mi_page_t *page);
bool _mi_page_queue_is_valid(mi_heap_t *heap, const mi_page_queue_t *pq);
size_t _mi_page_bin(const mi_page_t *page);
size_t _mi_bin_size(size_t bin);
size_t _mi_bin(size_t size);
mi_heap_t *_mi_heap_create(int heap_tag, bool allow_destroy, mi_arena_id_t arena_id, mi_tld_t *tld);
void _mi_heap_init(mi_heap_t *heap, mi_arena_id_t arena_id, bool noreclaim, uint8_t tag, mi_tld_t *tld);
void _mi_heap_destroy_pages(mi_heap_t *heap);
void _mi_heap_collect_abandon(mi_heap_t *heap);
void _mi_heap_set_default_direct(mi_heap_t *heap);
bool _mi_heap_memid_is_suitable(mi_heap_t *heap, mi_memid_t memid);
void _mi_heap_unsafe_destroy_all(mi_heap_t *heap);
mi_heap_t *_mi_heap_by_tag(mi_heap_t *heap, uint8_t tag);
void _mi_heap_area_init(mi_heap_area_t *area, mi_page_t *page);
bool _mi_heap_area_visit_blocks(const mi_heap_area_t *area, mi_page_t *page, mi_block_visit_fun *visitor, void *arg);
void _mi_heap_page_reclaim(mi_heap_t *heap, mi_page_t *page);
void _mi_stats_init(void);
void _mi_stats_done(mi_stats_t *stats);
void _mi_stats_print(mi_stats_t *stats, mi_output_fun *out, void *arg);
void _mi_stats_merge_thread(mi_tld_t *tld);
void _mi_stats_merge_from(mi_stats_t *to, mi_stats_t *from);
mi_msecs_t _mi_clock_now(void);
mi_msecs_t _mi_clock_end(mi_msecs_t start);
mi_msecs_t _mi_clock_start(void);
void *_mi_page_malloc_zero(mi_heap_t *heap, mi_page_t *page, size_t size, bool zero);
void *_mi_page_malloc(mi_heap_t *heap, mi_page_t *page, size_t size);
void *_mi_page_malloc_zeroed(mi_heap_t *heap, mi_page_t *page, size_t size);
void *_mi_heap_malloc_zero(mi_heap_t *heap, size_t size, bool zero);
void *_mi_heap_malloc_zero_ex(mi_heap_t *heap, size_t size, bool zero, size_t huge_alignment);
void *_mi_heap_realloc_zero(mi_heap_t *heap, void *p, size_t newsize, bool zero);
mi_block_t *_mi_page_ptr_unalign(const mi_page_t *page, const void *p);
void _mi_padding_shrink(const mi_page_t *page, const mi_block_t *block, const size_t min_size);
bool _mi_page_is_valid(mi_page_t *page);
void _mi_assert_fail(const char *assertion, const char *fname, unsigned int line, const char *func);
void __mi_stat_increase(mi_stat_count_t *stat, size_t amount);
void __mi_stat_decrease(mi_stat_count_t *stat, size_t amount);
void __mi_stat_increase_mt(mi_stat_count_t *stat, size_t amount);
void __mi_stat_decrease_mt(mi_stat_count_t *stat, size_t amount);
void __mi_stat_adjust_increase(mi_stat_count_t *stat, size_t amount);
void __mi_stat_adjust_decrease(mi_stat_count_t *stat, size_t amount);
void __mi_stat_adjust_increase_mt(mi_stat_count_t *stat, size_t amount);
void __mi_stat_adjust_decrease_mt(mi_stat_count_t *stat, size_t amount);
void __mi_stat_counter_increase(mi_stat_counter_t *stat, size_t amount);
void __mi_stat_counter_increase_mt(mi_stat_counter_t *stat, size_t amount);
typedef enum mi_option_init_e
{
  MI_OPTION_UNINIT,
  MI_OPTION_DEFAULTED,
  MI_OPTION_INITIALIZED
} mi_option_init_t;
typedef struct mi_option_desc_s
{
  long value;
  mi_option_init_t init;
  mi_option_t option;
  const char *name;
  const char *legacy_name;
} mi_option_desc_t;
inline static bool _mi_is_power_of_two(uintptr_t x)
{
  return (x & (x - 1)) == 0;
}

inline static bool _mi_is_aligned(void *p, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 423, __func__));
  return (((uintptr_t) p) % alignment) == 0;
}

inline static uintptr_t _mi_align_up(uintptr_t sz, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 429, __func__));
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

inline static uint8_t *_mi_align_up_ptr(void *p, size_t alignment)
{
  return (uint8_t *) _mi_align_up((uintptr_t) p, alignment);
}

inline static uintptr_t _mi_align_down(uintptr_t sz, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 447, __func__));
  uintptr_t mask = alignment - 1;
  if ((alignment & mask) == 0)
  {
    return sz & (~mask);
  }
  else
  {
    return (sz / alignment) * alignment;
  }
}

inline static void *mi_align_down_ptr(void *p, size_t alignment)
{
  return (void *) _mi_align_down((uintptr_t) p, alignment);
}

inline static uintptr_t _mi_divide_up(uintptr_t size, size_t divider)
{
  (divider != 0) ? ((void) 0) : (_mi_assert_fail("divider != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 463, __func__));
  return (divider == 0) ? (size) : (((size + divider) - 1) / divider);
}

inline static size_t _mi_clamp(size_t sz, size_t min, size_t max)
{
  if (sz < min)
  {
    return min;
  }
  else
    if (sz > max)
  {
    return max;
  }
  else
    return sz;
}

inline static bool mi_mem_is_zero(const void *p, size_t size)
{
  for (size_t i = 0; i < size; i += 1)
  {
    if (((uint8_t *) p)[i] != 0)
    {
      return 0;
    }
  }

  return 1;
}

inline static size_t _mi_wsize_from_size(size_t size)
{
  (size <= (SIZE_MAX - (sizeof(uintptr_t)))) ? ((void) 0) : (_mi_assert_fail("size <= SIZE_MAX - sizeof(uintptr_t)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 486, __func__));
  return ((size + (sizeof(uintptr_t))) - 1) / (sizeof(uintptr_t));
}

inline static bool mi_mul_overflow(size_t count, size_t size, size_t *total)
{
  return __builtin_umulll_overflow(count, size, (unsigned long long *) total);
}

inline static bool mi_count_size_overflow(size_t count, size_t size, size_t *total)
{
  if (count == 1)
  {
    *total = size;
    return 0;
  }
  else
    if (__builtin_expect(!(!mi_mul_overflow(count, size, total)), 0))
  {
    _mi_error_message(75, "allocation request is too large (%zu * %zu bytes)\n", count, size);
    *total = SIZE_MAX;
    return 1;
  }
  else
    return 0;
}

extern const mi_heap_t _mi_heap_empty;
inline static bool mi_heap_is_backing(const mi_heap_t *heap)
{
  return heap->tld->heap_backing == heap;
}

inline static bool mi_heap_is_initialized(const mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 542, __func__));
  return (heap != 0) && (heap != (&_mi_heap_empty));
}

inline static mi_page_t *_mi_heap_get_free_small_page(mi_heap_t *heap, size_t size)
{
  (size <= ((128 * (sizeof(void *))) + (sizeof(mi_padding_t)))) ? ((void) 0) : (_mi_assert_fail("size <= (MI_SMALL_SIZE_MAX + MI_PADDING_SIZE)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 547, __func__));
  const size_t idx = _mi_wsize_from_size(size);
  (idx < ((128 + ((((sizeof(mi_padding_t)) + (1 << 3)) - 1) / (1 << 3))) + 1)) ? ((void) 0) : (_mi_assert_fail("idx < MI_PAGES_DIRECT", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 549, __func__));
  return heap->pages_free_direct[idx];
}

typedef mi_page_t **mi_submap_t;
extern _Atomic mi_submap_t *_mi_page_map;
inline static size_t _mi_page_map_index(const void *p, size_t *sub_idx)
{
  const size_t u = (size_t) (((uintptr_t) p) / (1UL << (13 + 3)));
  if (sub_idx != 0)
  {
    *sub_idx = u % (1UL << 13);
  }
  return u / (1UL << 13);
}

inline static mi_submap_t _mi_page_map_at(size_t idx)
{
  return atomic_load_explicit(&_mi_page_map[idx], memory_order_relaxed);
}

inline static mi_page_t *_mi_unchecked_ptr_page(const void *p)
{
  size_t sub_idx;
  const size_t idx = _mi_page_map_index(p, &sub_idx);
  return _mi_page_map_at(idx)[sub_idx];
}

inline static mi_page_t *_mi_checked_ptr_page(const void *p)
{
  size_t sub_idx;
  const size_t idx = _mi_page_map_index(p, &sub_idx);
  const mi_submap_t sub = _mi_page_map_at(idx);
  if (__builtin_expect(!(!(sub == 0)), 0))
  {
    return 0;
  }
  return sub[sub_idx];
}

inline static mi_page_t *_mi_ptr_page(const void *p)
{
  ((p == 0) || mi_is_in_heap_region(p)) ? ((void) 0) : (_mi_assert_fail("p==NULL || mi_is_in_heap_region(p)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 638, __func__));
  return _mi_checked_ptr_page(p);
}

inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
}

inline static uint8_t *mi_page_start(const mi_page_t *page)
{
  return page->page_start;
}

inline static size_t mi_page_size(const mi_page_t *page)
{
  return mi_page_block_size(page) * page->reserved;
}

inline static uint8_t *mi_page_area(const mi_page_t *page, size_t *size)
{
  if (size)
  {
    *size = mi_page_size(page);
  }
  return mi_page_start(page);
}

inline static size_t mi_page_info_size(void)
{
  return _mi_align_up(sizeof(mi_page_t), 16);
}

inline static bool mi_page_contains_address(const mi_page_t *page, const void *p)
{
  size_t psize;
  uint8_t *start = mi_page_area(page, &psize);
  return (start <= ((uint8_t *) p)) && (((uint8_t *) p) < (start + psize));
}

inline static bool mi_page_is_in_arena(const mi_page_t *page)
{
  return page->memid.memkind == MI_MEM_ARENA;
}

inline static bool mi_page_is_singleton(const mi_page_t *page)
{
  return page->reserved == 1;
}

inline static size_t mi_page_usable_block_size(const mi_page_t *page)
{
  return mi_page_block_size(page) - (sizeof(mi_padding_t));
}

inline static uint8_t *mi_page_slice_start(const mi_page_t *page)
{
  return (uint8_t *) page;
}

inline static size_t mi_page_slice_offset_of(const mi_page_t *page, size_t offset_relative_to_page_start)
{
  return (page->page_start - mi_page_slice_start(page)) + offset_relative_to_page_start;
}

inline static size_t mi_page_committed(const mi_page_t *page)
{
  return (page->slice_committed == 0) ? (mi_page_size(page)) : (page->slice_committed - (page->page_start - mi_page_slice_start(page)));
}

inline static mi_heap_t *mi_page_heap(const mi_page_t *page)
{
  return page->heap;
}

inline static bool mi_page_all_free(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 714, __func__));
  return page->used == 0;
}

inline static bool mi_page_immediate_available(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 720, __func__));
  return page->free != 0;
}

inline static bool mi_page_is_expandable(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 727, __func__));
  (page->capacity <= page->reserved) ? ((void) 0) : (_mi_assert_fail("page->capacity <= page->reserved", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 728, __func__));
  return page->capacity < page->reserved;
}

inline static bool mi_page_is_full(mi_page_t *page)
{
  const bool full = page->reserved == page->used;
  ((!full) || (page->free == 0)) ? ((void) 0) : (_mi_assert_fail("!full || page->free == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 735, __func__));
  return full;
}

inline static bool mi_page_is_mostly_used(const mi_page_t *page)
{
  if (page == 0)
  {
    return 1;
  }
  uint16_t frac = page->reserved / 8U;
  return (page->reserved - page->used) <= frac;
}

inline static bool mi_page_is_used_at_frac(const mi_page_t *page, uint16_t n)
{
  if (page == 0)
  {
    return 1;
  }
  uint16_t frac = page->reserved / n;
  return (page->reserved - page->used) <= frac;
}

inline static bool mi_page_is_huge(const mi_page_t *page)
{
  return mi_page_is_singleton(page) && ((page->block_size > ((8 * (1 * (1UL << (13 + 3)))) / 8)) || (mi_memkind_is_os(page->memid.memkind) && (page->memid.mem.os.base < ((void *) page))));
}

inline static mi_page_queue_t *mi_page_queue(const mi_heap_t *heap, size_t size)
{
  mi_page_queue_t * const pq = &((mi_heap_t *) heap)->pages[_mi_bin(size)];
  if (size <= ((8 * (1 * (1UL << (13 + 3)))) / 8))
  {
    (pq->block_size <= ((8 * (1 * (1UL << (13 + 3)))) / 8)) ? ((void) 0) : (_mi_assert_fail("pq->block_size <= MI_LARGE_MAX_OBJ_SIZE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 762, __func__));
  }
  return pq;
}

inline static mi_threadid_t mi_page_xthread_id(const mi_page_t *page)
{
  return atomic_load_explicit(&((mi_page_t *) page)->xthread_id, memory_order_relaxed);
}

inline static mi_threadid_t mi_page_thread_id(const mi_page_t *page)
{
  return mi_page_xthread_id(page) & (~0x03UL);
}

inline static mi_page_flags_t mi_page_flags(const mi_page_t *page)
{
  return mi_page_xthread_id(page) & 0x03UL;
}

inline static void mi_page_flags_set(mi_page_t *page, bool set, mi_page_flags_t newflag)
{
  if (set)
  {
    atomic_fetch_or_explicit(&page->xthread_id, newflag, memory_order_relaxed);
  }
  else
  {
    atomic_fetch_and_explicit(&page->xthread_id, ~newflag, memory_order_relaxed);
  }
}

inline static bool mi_page_is_in_full(const mi_page_t *page)
{
  return (mi_page_flags(page) & 0x01UL) != 0;
}

inline static void mi_page_set_in_full(mi_page_t *page, bool in_full)
{
  mi_page_flags_set(page, in_full, 0x01UL);
}

inline static bool mi_page_has_interior_pointers(const mi_page_t *page)
{
  return (mi_page_flags(page) & 0x02UL) != 0;
}

inline static void mi_page_set_has_interior_pointers(mi_page_t *page, bool has_aligned)
{
  mi_page_flags_set(page, has_aligned, 0x02UL);
}

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
  ((tid & 0x03UL) == 0) ? ((void) 0) : (_mi_assert_fail("(tid & MI_PAGE_FLAG_MASK) == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 816, __func__));
  mi_threadid_t xtid_old = mi_page_xthread_id(page);
  mi_threadid_t xtid;
  do
  {
    xtid = tid | (xtid_old & 0x03UL);
  }
  while (!atomic_compare_exchange_weak_explicit(&page->xthread_id, &xtid_old, xtid, memory_order_release, memory_order_relaxed));
}

inline static bool mi_page_is_abandoned(const mi_page_t *page)
{
  return mi_page_thread_id(page) <= (0x03UL + 1);
}

inline static bool mi_page_is_abandoned_mapped(const mi_page_t *page)
{
  return mi_page_thread_id(page) == (0x03UL + 1);
}

inline static void mi_page_set_abandoned_mapped(mi_page_t *page)
{
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 836, __func__));
  atomic_fetch_or_explicit(&page->xthread_id, 0x03UL + 1, memory_order_relaxed);
}

inline static void mi_page_clear_abandoned_mapped(mi_page_t *page)
{
  (mi_page_is_abandoned_mapped(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned_mapped(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 841, __func__));
  atomic_fetch_and_explicit(&page->xthread_id, 0x03UL, memory_order_relaxed);
}

inline static mi_block_t *mi_tf_block(mi_thread_free_t tf)
{
  return (mi_block_t *) (tf & (~1));
}

inline static bool mi_tf_is_owned(mi_thread_free_t tf)
{
  return (tf & 1) == 1;
}

inline static mi_thread_free_t mi_tf_create(mi_block_t *block, bool owned)
{
  return (mi_thread_free_t) (((uintptr_t) block) | ((owned) ? (1) : (0)));
}

inline static mi_block_t *mi_page_thread_free(const mi_page_t *page)
{
  return mi_tf_block(atomic_load_explicit(&((mi_page_t *) page)->xthread_free, memory_order_relaxed));
}

inline static bool mi_page_has_any_available(const mi_page_t *page)
{
  ((page != 0) && (page->reserved > 0)) ? ((void) 0) : (_mi_assert_fail("page != NULL && page->reserved > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 867, __func__));
  return (page->used < page->reserved) || (mi_page_thread_free(page) != 0);
}

inline static bool mi_page_is_owned(const mi_page_t *page)
{
  return mi_tf_is_owned(atomic_load_explicit(&((mi_page_t *) page)->xthread_free, memory_order_relaxed));
}

inline static void _mi_page_unown_unconditional(mi_page_t *page)
{
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 879, __func__));
  (mi_page_thread_id(page) == 0) ? ((void) 0) : (_mi_assert_fail("mi_page_thread_id(page)==0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 880, __func__));
  const uintptr_t old = atomic_fetch_and_explicit(&page->xthread_free, ~((uintptr_t) 1), memory_order_acq_rel);
  ((old & 1) == 1) ? ((void) 0) : (_mi_assert_fail("(old&1)==1", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 882, __func__));
  (void) old;
}

inline static bool mi_page_try_claim_ownership(mi_page_t *page)
{
  const uintptr_t old = atomic_fetch_or_explicit(&page->xthread_free, 1, memory_order_acq_rel);
  return (old & 1) == 0;
}

inline static bool _mi_page_unown(mi_page_t *page)
{
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 894, __func__));
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 895, __func__));
  mi_thread_free_t tf_new;
  mi_thread_free_t tf_old = atomic_load_explicit(&page->xthread_free, memory_order_relaxed);
  do
  {
    (mi_tf_is_owned(tf_old)) ? ((void) 0) : (_mi_assert_fail("mi_tf_is_owned(tf_old)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 899, __func__));
    while (__builtin_expect(!(!(mi_tf_block(tf_old) != 0)), 0))
    {
      _mi_page_free_collect(page, 0);
      if (mi_page_all_free(page))
      {
        _mi_arenas_page_unabandon(page);
        _mi_arenas_page_free(page, 0);
        return 1;
      }
      tf_old = atomic_load_explicit(&page->xthread_free, memory_order_relaxed);
    }

    (mi_tf_block(tf_old) == 0) ? ((void) 0) : (_mi_assert_fail("mi_tf_block(tf_old)==NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 909, __func__));
    tf_new = mi_tf_create(0, 0);
  }
  while (!atomic_compare_exchange_weak_explicit(&page->xthread_free, &tf_old, tf_new, memory_order_acq_rel, memory_order_acquire));
  return 0;
}

inline static bool mi_is_in_same_page(const void *p, const void *q)
{
  mi_page_t *page = _mi_ptr_page(p);
  return mi_page_contains_address(page, q);
}

inline static void *mi_ptr_decode(const void *null, const mi_encoded_t x, const uintptr_t *keys)
{
  void *p = (void *) (mi_rotr(x - keys[0], keys[0]) ^ keys[1]);
  return (p == null) ? (0) : (p);
}

inline static mi_encoded_t mi_ptr_encode(const void *null, const void *p, const uintptr_t *keys)
{
  uintptr_t x = (uintptr_t) ((p == 0) ? (null) : (p));
  return mi_rotl(x ^ keys[1], keys[0]) + keys[0];
}

inline static uint32_t mi_ptr_encode_canary(const void *null, const void *p, const uintptr_t *keys)
{
  const uint32_t x = (uint32_t) mi_ptr_encode(null, p, keys);
  return x & 0xFFFFFF00;
}

inline static mi_block_t *mi_block_nextx(const void *null, const mi_block_t *block, const uintptr_t *keys)
{
  ;
  mi_block_t *next;
  unsigned int next_idx = 0;
  next_idx = (mi_block_t *) mi_ptr_decode(null, block->next_idx, keys);
  ;
  return next;
}

inline static void mi_block_set_nextx(const void *null, mi_block_t *block, const mi_block_t *next, const uintptr_t *keys)
{
  ;
  block->next = mi_ptr_encode(null, next, keys);
  ;
}

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

inline static void mi_block_set_next(const mi_page_t *page, mi_block_t *block, const mi_block_t *next)
{
  mi_block_set_nextx(page, block, next, page->keys);
}

inline static size_t mi_slice_count_of_size(size_t size)
{
  return _mi_divide_up(size, 1UL << (13 + 3));
}

inline static size_t mi_size_of_slices(size_t bcount)
{
  return bcount * (1UL << (13 + 3));
}

inline static mi_memid_t _mi_memid_create(mi_memkind_t memkind)
{
  mi_memid_t memid;
  memset(&memid, 0, sizeof(memid));
  memid.memkind = memkind;
  return memid;
}

inline static mi_memid_t _mi_memid_none(void)
{
  return _mi_memid_create(MI_MEM_NONE);
}

inline static mi_memid_t _mi_memid_create_os(void *base, size_t size, bool committed, bool is_zero, bool is_large)
{
  mi_memid_t memid = _mi_memid_create(MI_MEM_OS);
  memid.mem.os.base = base;
  memid.mem.os.size = size;
  memid.initially_committed = committed;
  memid.initially_zero = is_zero;
  memid.is_pinned = is_large;
  return memid;
}

inline static mi_memid_t _mi_memid_create_meta(void *mpage, size_t block_idx, size_t block_count)
{
  mi_memid_t memid = _mi_memid_create(MI_MEM_META);
  memid.mem.meta.meta_page = mpage;
  memid.mem.meta.block_index = (uint32_t) block_idx;
  memid.mem.meta.block_count = (uint32_t) block_count;
  memid.initially_committed = 1;
  memid.initially_zero = 1;
  memid.is_pinned = 1;
  return memid;
}

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

inline static void _mi_memcpy(void *dst, const void *src, size_t n)
{
  memcpy(dst, src, n);
}

inline static void _mi_memset(void *dst, int val, size_t n)
{
  memset(dst, val, n);
}

inline static void _mi_memcpy_aligned(void *dst, const void *src, size_t n)
{
  (((((uintptr_t) dst) % (1 << 3)) == 0) && ((((uintptr_t) src) % (1 << 3)) == 0)) ? ((void) 0) : (_mi_assert_fail("((uintptr_t)dst % MI_INTPTR_SIZE == 0) && ((uintptr_t)src % MI_INTPTR_SIZE == 0)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 1178, __func__));
  void *adst = __builtin_assume_aligned(dst, 1 << 3);
  const void *asrc = __builtin_assume_aligned(src, 1 << 3);
  _mi_memcpy(adst, asrc, n);
}

inline static void _mi_memset_aligned(void *dst, int val, size_t n)
{
  ((((uintptr_t) dst) % (1 << 3)) == 0) ? ((void) 0) : (_mi_assert_fail("(uintptr_t)dst % MI_INTPTR_SIZE == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 1185, __func__));
  void *adst = __builtin_assume_aligned(dst, 1 << 3);
  _mi_memset(adst, val, n);
}

inline static void _mi_memzero(void *dst, size_t n)
{
  _mi_memset(dst, 0, n);
}

inline static void _mi_memzero_aligned(void *dst, size_t n)
{
  _mi_memset_aligned(dst, 0, n);
}

typedef size_t mi_bfield_t;
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t;
typedef mi_bchunk_t mi_bchunkmap_t;
typedef struct mi_bitmap_s
{
  _Atomic size_t chunk_count;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 1];
  mi_bchunkmap_t chunkmap;
  mi_bchunk_t chunks[64];
} mi_bitmap_t;
inline static size_t mi_bitmap_chunk_count(const mi_bitmap_t *bitmap)
{
  return atomic_load_explicit(&((mi_bitmap_t *) bitmap)->chunk_count, memory_order_relaxed);
}

inline static size_t mi_bitmap_max_bits(const mi_bitmap_t *bitmap)
{
  return mi_bitmap_chunk_count(bitmap) * (1 << (6 + 3));
}

typedef bool mi_xset_t;
size_t mi_bitmap_size(size_t bit_count, size_t *chunk_count);
size_t mi_bitmap_init(mi_bitmap_t *bitmap, size_t bit_count, bool already_zero);
void mi_bitmap_unsafe_setN(mi_bitmap_t *bitmap, size_t idx, size_t n);
bool mi_bitmap_set(mi_bitmap_t *bitmap, size_t idx);
bool mi_bitmap_clear(mi_bitmap_t *bitmap, size_t idx);
bool mi_bitmap_setN(mi_bitmap_t *bitmap, size_t idx, size_t n, size_t *already_set);
bool mi_bitmap_clearN(mi_bitmap_t *bitmap, size_t idx, size_t n);
bool mi_bitmap_is_xsetN(mi_xset_t set, mi_bitmap_t *bitmap, size_t idx, size_t n);
inline static bool mi_bitmap_is_setN(mi_bitmap_t *bitmap, size_t idx, size_t n)
{
  return mi_bitmap_is_xsetN(1, bitmap, idx, n);
}

inline static bool mi_bitmap_is_clearN(mi_bitmap_t *bitmap, size_t idx, size_t n)
{
  return mi_bitmap_is_xsetN(0, bitmap, idx, n);
}

inline static bool mi_bitmap_is_set(mi_bitmap_t *bitmap, size_t idx)
{
  return mi_bitmap_is_setN(bitmap, idx, 1);
}

inline static bool mi_bitmap_is_clear(mi_bitmap_t *bitmap, size_t idx)
{
  return mi_bitmap_is_clearN(bitmap, idx, 1);
}

typedef bool mi_claim_fun_t(size_t slice_index, mi_arena_t *arena, mi_heaptag_t heap_tag, bool *keep_set);
bool mi_bitmap_try_find_and_claim(mi_bitmap_t *bitmap, size_t tseq, size_t *pidx, mi_claim_fun_t *claim, mi_arena_t *arena, mi_heaptag_t heap_tag);
void mi_bitmap_clear_once_set(mi_bitmap_t *bitmap, size_t idx);
bool mi_bitmap_bsr(mi_bitmap_t *bitmap, size_t *idx);
size_t mi_bitmap_popcount(mi_bitmap_t *bitmap);
typedef bool mi_forall_set_fun_t(size_t slice_index, size_t slice_count, mi_arena_t *arena, void *arg2);
bool _mi_bitmap_forall_set(mi_bitmap_t *bitmap, mi_forall_set_fun_t *visit, mi_arena_t *arena, void *arg);
bool _mi_bitmap_forall_setc_ranges(mi_bitmap_t *bitmap, mi_forall_set_fun_t *visit, mi_arena_t *arena, void *arg);
size_t mi_bitmap_popcountN(mi_bitmap_t *bitmap, size_t idx, size_t n);
inline static mi_chunkbin_t mi_chunkbin_inc(mi_chunkbin_t bbin)
{
  (bbin < MI_CBIN_COUNT) ? ((void) 0) : (_mi_assert_fail("bbin < MI_CBIN_COUNT", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.h", 234, __func__));
  return (mi_chunkbin_t) (((int) bbin) + 1);
}

inline static mi_chunkbin_t mi_chunkbin_dec(mi_chunkbin_t bbin)
{
  (bbin > MI_CBIN_NONE) ? ((void) 0) : (_mi_assert_fail("bbin > MI_CBIN_NONE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.h", 239, __func__));
  return (mi_chunkbin_t) (((int) bbin) - 1);
}

inline static mi_chunkbin_t mi_chunkbin_of(size_t slice_count)
{
  if (slice_count == 1)
  {
    return MI_CBIN_SMALL;
  }
  if (slice_count == 8)
  {
    return MI_CBIN_MEDIUM;
  }
  return MI_CBIN_OTHER;
}

typedef struct mi_bbitmap_s
{
  _Atomic size_t chunk_count;
  _Atomic size_t chunk_max_accessed;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 2];
  mi_bchunkmap_t chunkmap;
  mi_bchunkmap_t chunkmap_bins[MI_CBIN_COUNT - 1];
  mi_bchunk_t chunks[64];
} mi_bbitmap_t;
inline static size_t mi_bbitmap_chunk_count(const mi_bbitmap_t *bbitmap)
{
  return atomic_load_explicit(&((mi_bbitmap_t *) bbitmap)->chunk_count, memory_order_relaxed);
}

inline static size_t mi_bbitmap_max_bits(const mi_bbitmap_t *bbitmap)
{
  return mi_bbitmap_chunk_count(bbitmap) * (1 << (6 + 3));
}

mi_chunkbin_t mi_bbitmap_debug_get_bin(const mi_bchunk_t *chunkmap_bins, size_t chunk_idx);
size_t mi_bbitmap_size(size_t bit_count, size_t *chunk_count);
size_t mi_bbitmap_init(mi_bbitmap_t *bbitmap, size_t bit_count, bool already_zero);
void mi_bbitmap_unsafe_setN(mi_bbitmap_t *bbitmap, size_t idx, size_t n);
bool mi_bbitmap_setN(mi_bbitmap_t *bbitmap, size_t idx, size_t n);
bool mi_bbitmap_is_xsetN(mi_xset_t set, mi_bbitmap_t *bbitmap, size_t idx, size_t n);
inline static bool mi_bbitmap_is_setN(mi_bbitmap_t *bbitmap, size_t idx, size_t n)
{
  return mi_bbitmap_is_xsetN(1, bbitmap, idx, n);
}

inline static bool mi_bbitmap_is_clearN(mi_bbitmap_t *bbitmap, size_t idx, size_t n)
{
  return mi_bbitmap_is_xsetN(0, bbitmap, idx, n);
}

bool mi_bbitmap_try_clearN(mi_bbitmap_t *bbitmap, size_t idx, size_t n);
bool mi_bbitmap_try_find_and_clear(mi_bbitmap_t *bbitmap, size_t tseq, size_t *pidx);
bool mi_bbitmap_try_find_and_clear8(mi_bbitmap_t *bbitmap, size_t tseq, size_t *pidx);
bool mi_bbitmap_try_find_and_clearNX(mi_bbitmap_t *bbitmap, size_t n, size_t tseq, size_t *pidx);
bool mi_bbitmap_try_find_and_clearN_(mi_bbitmap_t *bbitmap, size_t n, size_t tseq, size_t *pidx);
inline static bool mi_bbitmap_try_find_and_clearN(mi_bbitmap_t *bbitmap, size_t n, size_t tseq, size_t *pidx)
{
  if (n == 1)
  {
    return mi_bbitmap_try_find_and_clear(bbitmap, tseq, pidx);
  }
  if (n == 8)
  {
    return mi_bbitmap_try_find_and_clear8(bbitmap, tseq, pidx);
  }
  if ((n == 0) || (n > (1 << (6 + 3))))
  {
    return 0;
  }
  if (n <= (1 << (3 + 3)))
  {
    return mi_bbitmap_try_find_and_clearNX(bbitmap, tseq, n, pidx);
  }
  return mi_bbitmap_try_find_and_clearN_(bbitmap, tseq, n, pidx);
}

static void mi_page_map_cannot_commit(void)
{
  _mi_warning_message("unable to commit the allocation page-map on-demand\n");
}

_Atomic mi_submap_t *_mi_page_map;
static size_t mi_page_map_count;
static void *mi_page_map_max_address;
static mi_memid_t mi_page_map_memid;
static _Atomic mi_bfield_t mi_page_map_commit;
inline static bool mi_page_map_is_committed(size_t idx, size_t *pbit_idx)
{
  mi_bfield_t commit = atomic_load_explicit(&mi_page_map_commit, memory_order_relaxed);
  const size_t bit_idx = idx / ((1UL << ((48 - 13) - (13 + 3))) / (1 << (3 + 3)));
  (bit_idx < (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("bit_idx < MI_BFIELD_BITS", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 209, __func__));
  if (pbit_idx != 0)
  {
    *pbit_idx = bit_idx;
  }
  return (commit & (1UL << bit_idx)) != 0;
}

static bool mi_page_map_ensure_committed(size_t idx, mi_submap_t *submap)
{
  ((submap != 0) && ((*submap) == 0)) ? ((void) 0) : (_mi_assert_fail("submap!=NULL && *submap==NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 215, __func__));
  size_t bit_idx;
  if (__builtin_expect(!(!(!mi_page_map_is_committed(idx, &bit_idx))), 0))
  {
    uint8_t *start = (uint8_t *) (&_mi_page_map[bit_idx * ((1UL << ((48 - 13) - (13 + 3))) / (1 << (3 + 3)))]);
    if (!_mi_os_commit(start, ((1UL << ((48 - 13) - (13 + 3))) / (1 << (3 + 3))) * (sizeof(mi_submap_t)), 0))
    {
      mi_page_map_cannot_commit();
      return 0;
    }
    atomic_fetch_or_explicit(&mi_page_map_commit, 1UL << bit_idx, memory_order_acq_rel);
  }
  *submap = atomic_load_explicit(&_mi_page_map[idx], memory_order_acquire);
  return 1;
}

bool _mi_page_map_init(void)
{
  size_t vbits = (size_t) mi_option_get_clamp(mi_option_max_vabits, 0, (1 << 3) * 8);
  if (vbits == 0)
  {
    vbits = _mi_os_virtual_address_bits();
  }
  (48 >= vbits) ? ((void) 0) : (_mi_assert_fail("MI_MAX_VABITS >= vbits", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 240, __func__));
  mi_page_map_max_address = (void *) ((vbits >= ((1 << 3) * 8)) ? ((SIZE_MAX - (1UL << (13 + 3))) + 1) : (1UL << vbits));
  mi_page_map_count = 1UL << ((vbits - 13) - (13 + 3));
  (mi_page_map_count <= (1UL << ((48 - 13) - (13 + 3)))) ? ((void) 0) : (_mi_assert_fail("mi_page_map_count <= MI_PAGE_MAP_COUNT", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 243, __func__));
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
  (_mi_ptr_page(0) == 0) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(NULL)==NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 283, __func__));
  return 1;
}

void _mi_page_map_unsafe_destroy(mi_subproc_t *subproc)
{
  (subproc != 0) ? ((void) 0) : (_mi_assert_fail("subproc != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 289, __func__));
  (_mi_page_map != 0) ? ((void) 0) : (_mi_assert_fail("_mi_page_map != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 290, __func__));
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

static bool mi_page_map_ensure_submap_at(size_t idx, mi_submap_t *submap)
{
  ((submap != 0) && ((*submap) == 0)) ? ((void) 0) : (_mi_assert_fail("submap!=NULL && *submap==NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 313, __func__));
  mi_submap_t sub = 0;
  if (!mi_page_map_ensure_committed(idx, &sub))
  {
    return 0;
  }
  if (__builtin_expect(!(!(sub == 0)), 0))
  {
    mi_memid_t memid;
    const size_t submap_size = (1UL << 13) * (sizeof(mi_page_t *));
    sub = (mi_submap_t) _mi_os_zalloc(submap_size, &memid);
    if (sub == 0)
    {
      _mi_warning_message("internal error: unable to extend the page map\n");
      return 0;
    }
    mi_submap_t expect = 0;
    if (!atomic_compare_exchange_strong_explicit(&_mi_page_map[idx], &expect, sub, memory_order_acq_rel, memory_order_acquire))
    {
      _mi_os_free(sub, submap_size, memid);
      sub = expect;
    }
  }
  (sub != 0) ? ((void) 0) : (_mi_assert_fail("sub!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 334, __func__));
  *submap = sub;
  return 1;
}

static bool mi_page_map_set_range_prim(mi_page_t *page, size_t idx, size_t sub_idx, size_t slice_count)
{
  while (slice_count > 0)
  {
    mi_submap_t sub = 0;
    if (!mi_page_map_ensure_submap_at(idx, &sub))
    {
      return 0;
    }
    ;
    (sub != 0) ? ((void) 0) : (_mi_assert_fail("sub!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 346, __func__));
    while ((slice_count > 0) && (sub_idx < (1UL << 13)))
    {
      sub[sub_idx] = page;
      slice_count -= 1;
      sub_idx += 1;
    }

    idx += 1;
    sub_idx = 0;
  }

  return 1;
}

static bool mi_page_map_set_range(mi_page_t *page, size_t idx, size_t sub_idx, size_t slice_count)
{
  if (__builtin_expect(!(!(!mi_page_map_set_range_prim(page, idx, sub_idx, slice_count))), 0))
  {
    if (page != 0)
    {
      mi_page_map_set_range_prim(0, idx, sub_idx, slice_count);
    }
    return 0;
  }
  return 1;
}

static size_t mi_page_map_get_idx(mi_page_t *page, size_t *sub_idx, size_t *slice_count)
{
  size_t page_size;
  uint8_t *page_start = mi_page_area(page, &page_size);
  if (page_size > ((1 << 3) * (8 * (1 * (1UL << (13 + 3))))))
  {
    page_size = ((1 << 3) * (8 * (1 * (1UL << (13 + 3))))) - (1UL << (13 + 3));
  }
  *slice_count = mi_slice_count_of_size(page_size) + ((page_start - ((uint8_t *) page)) / (1UL << (13 + 3)));
  return _mi_page_map_index(page, sub_idx);
}

bool _mi_page_map_register(mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 379, __func__));
  (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 380, __func__));
  (_mi_page_map != 0) ? ((void) 0) : (_mi_assert_fail("_mi_page_map != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 381, __func__));
  if (__builtin_expect(!(!(_mi_page_map == 0)), 0))
  {
    if (!_mi_page_map_init())
    {
      return 0;
    }
  }
  (_mi_page_map != 0) ? ((void) 0) : (_mi_assert_fail("_mi_page_map!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 385, __func__));
  size_t slice_count;
  size_t sub_idx;
  const size_t idx = mi_page_map_get_idx(page, &sub_idx, &slice_count);
  return mi_page_map_set_range(page, idx, sub_idx, slice_count);
}

void _mi_page_map_unregister(mi_page_t *page)
{
  (_mi_page_map != 0) ? ((void) 0) : (_mi_assert_fail("_mi_page_map != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 393, __func__));
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 394, __func__));
  (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 395, __func__));
  if (__builtin_expect(!(!(_mi_page_map == 0)), 0))
  {
    return;
  }
  size_t slice_count;
  size_t sub_idx;
  const size_t idx = mi_page_map_get_idx(page, &sub_idx, &slice_count);
  mi_page_map_set_range(0, idx, sub_idx, slice_count);
}

void _mi_page_map_unregister_range(void *start, size_t size)
{
  if (__builtin_expect(!(!(_mi_page_map == 0)), 0))
  {
    return;
  }
  const size_t slice_count = _mi_divide_up(size, 1UL << (13 + 3));
  size_t sub_idx;
  const uintptr_t idx = _mi_page_map_index(start, &sub_idx);
  mi_page_map_set_range(0, idx, sub_idx, slice_count);
}

mi_page_t *_mi_safe_ptr_page(const void *p)
{
  if (p == 0)
  {
    return 0;
  }
  if (__builtin_expect(!(!(p >= mi_page_map_max_address)), 0))
  {
    return 0;
  }
  size_t sub_idx;
  const size_t idx = _mi_page_map_index(p, &sub_idx);
  if (__builtin_expect(!(!(!mi_page_map_is_committed(idx, 0))), 0))
  {
    return 0;
  }
  mi_page_t ** const sub = _mi_page_map[idx];
  if (__builtin_expect(!(!(sub == 0)), 0))
  {
    return 0;
  }
  return sub[sub_idx];
}

bool mi_is_in_heap_region(const void *p)
{
  return _mi_safe_ptr_page(p) != 0;
}


void *mi_malloc(size_t size);
void *mi_calloc(size_t count, size_t size);
void *mi_realloc(void *p, size_t newsize);
void *mi_expand(void *p, size_t newsize);
void mi_free(void *p);
char *mi_strdup(const char *s);
char *mi_strndup(const char *s, size_t n);
char *mi_realpath(const char *fname, char *resolved_name);
void *mi_malloc_small(size_t size);
void *mi_zalloc_small(size_t size);
void *mi_zalloc(size_t size);
void *mi_mallocn(size_t count, size_t size);
void *mi_reallocn(void *p, size_t count, size_t size);
void *mi_reallocf(void *p, size_t newsize);
size_t mi_usable_size(const void *p);
size_t mi_good_size(size_t size);
typedef void mi_deferred_free_fun(bool force, unsigned long long heartbeat, void *arg);
void mi_register_deferred_free(mi_deferred_free_fun *deferred_free, void *arg);
typedef void mi_output_fun(const char *msg, void *arg);
void mi_register_output(mi_output_fun *out, void *arg);
typedef void mi_error_fun(int err, void *arg);
void mi_register_error(mi_error_fun *fun, void *arg);
void mi_collect(bool force);
int mi_version(void);
void mi_stats_reset(void);
void mi_stats_merge(void);
void mi_stats_print(void *out);
void mi_stats_print_out(mi_output_fun *out, void *arg);
void mi_thread_stats_print_out(mi_output_fun *out, void *arg);
void mi_options_print(void);
void mi_process_info(size_t *elapsed_msecs, size_t *user_msecs, size_t *system_msecs, size_t *current_rss, size_t *peak_rss, size_t *current_commit, size_t *peak_commit, size_t *page_faults);
void mi_process_init(void);
void mi_process_done(void);
void mi_thread_init(void);
void mi_thread_done(void);
void *mi_malloc_aligned(size_t size, size_t alignment);
void *mi_malloc_aligned_at(size_t size, size_t alignment, size_t offset);
void *mi_zalloc_aligned(size_t size, size_t alignment);
void *mi_zalloc_aligned_at(size_t size, size_t alignment, size_t offset);
void *mi_calloc_aligned(size_t count, size_t size, size_t alignment);
void *mi_calloc_aligned_at(size_t count, size_t size, size_t alignment, size_t offset);
void *mi_realloc_aligned(void *p, size_t newsize, size_t alignment);
void *mi_realloc_aligned_at(void *p, size_t newsize, size_t alignment, size_t offset);
struct mi_heap_s;
typedef struct mi_heap_s mi_heap_t;
mi_heap_t *mi_heap_new(void);
void mi_heap_delete(mi_heap_t *heap);
void mi_heap_destroy(mi_heap_t *heap);
mi_heap_t *mi_heap_set_default(mi_heap_t *heap);
mi_heap_t *mi_heap_get_default(void);
mi_heap_t *mi_heap_get_backing(void);
void mi_heap_collect(mi_heap_t *heap, bool force);
void *mi_heap_malloc(mi_heap_t *heap, size_t size);
void *mi_heap_zalloc(mi_heap_t *heap, size_t size);
void *mi_heap_calloc(mi_heap_t *heap, size_t count, size_t size);
void *mi_heap_mallocn(mi_heap_t *heap, size_t count, size_t size);
void *mi_heap_malloc_small(mi_heap_t *heap, size_t size);
void *mi_heap_realloc(mi_heap_t *heap, void *p, size_t newsize);
void *mi_heap_reallocn(mi_heap_t *heap, void *p, size_t count, size_t size);
void *mi_heap_reallocf(mi_heap_t *heap, void *p, size_t newsize);
char *mi_heap_strdup(mi_heap_t *heap, const char *s);
char *mi_heap_strndup(mi_heap_t *heap, const char *s, size_t n);
char *mi_heap_realpath(mi_heap_t *heap, const char *fname, char *resolved_name);
void *mi_heap_malloc_aligned(mi_heap_t *heap, size_t size, size_t alignment);
void *mi_heap_malloc_aligned_at(mi_heap_t *heap, size_t size, size_t alignment, size_t offset);
void *mi_heap_zalloc_aligned(mi_heap_t *heap, size_t size, size_t alignment);
void *mi_heap_zalloc_aligned_at(mi_heap_t *heap, size_t size, size_t alignment, size_t offset);
void *mi_heap_calloc_aligned(mi_heap_t *heap, size_t count, size_t size, size_t alignment);
void *mi_heap_calloc_aligned_at(mi_heap_t *heap, size_t count, size_t size, size_t alignment, size_t offset);
void *mi_heap_realloc_aligned(mi_heap_t *heap, void *p, size_t newsize, size_t alignment);
void *mi_heap_realloc_aligned_at(mi_heap_t *heap, void *p, size_t newsize, size_t alignment, size_t offset);
void *mi_rezalloc(void *p, size_t newsize);
void *mi_recalloc(void *p, size_t newcount, size_t size);
void *mi_rezalloc_aligned(void *p, size_t newsize, size_t alignment);
void *mi_rezalloc_aligned_at(void *p, size_t newsize, size_t alignment, size_t offset);
void *mi_recalloc_aligned(void *p, size_t newcount, size_t size, size_t alignment);
void *mi_recalloc_aligned_at(void *p, size_t newcount, size_t size, size_t alignment, size_t offset);
void *mi_heap_rezalloc(mi_heap_t *heap, void *p, size_t newsize);
void *mi_heap_recalloc(mi_heap_t *heap, void *p, size_t newcount, size_t size);
void *mi_heap_rezalloc_aligned(mi_heap_t *heap, void *p, size_t newsize, size_t alignment);
void *mi_heap_rezalloc_aligned_at(mi_heap_t *heap, void *p, size_t newsize, size_t alignment, size_t offset);
void *mi_heap_recalloc_aligned(mi_heap_t *heap, void *p, size_t newcount, size_t size, size_t alignment);
void *mi_heap_recalloc_aligned_at(mi_heap_t *heap, void *p, size_t newcount, size_t size, size_t alignment, size_t offset);
bool mi_heap_contains_block(mi_heap_t *heap, const void *p);
bool mi_heap_check_owned(mi_heap_t *heap, const void *p);
bool mi_check_owned(const void *p);
typedef struct mi_heap_area_s
{
  void *blocks;
  size_t reserved;
  size_t committed;
  size_t used;
  size_t block_size;
  size_t full_block_size;
  int heap_tag;
} mi_heap_area_t;
typedef bool mi_block_visit_fun(const mi_heap_t *heap, const mi_heap_area_t *area, void *block, size_t block_size, void *arg);
bool mi_heap_visit_blocks(const mi_heap_t *heap, bool visit_blocks, mi_block_visit_fun *visitor, void *arg);
bool mi_is_in_heap_region(const void *p);
bool mi_is_redirected(void);
int mi_reserve_huge_os_pages_interleave(size_t pages, size_t numa_nodes, size_t timeout_msecs);
int mi_reserve_huge_os_pages_at(size_t pages, int numa_node, size_t timeout_msecs);
int mi_reserve_os_memory(size_t size, bool commit, bool allow_large);
bool mi_manage_os_memory(void *start, size_t size, bool is_committed, bool is_pinned, bool is_zero, int numa_node);
void mi_debug_show_arenas(void);
void mi_arenas_print(void);
size_t mi_arena_min_alignment(void);
typedef void *mi_arena_id_t;
void *mi_arena_area(mi_arena_id_t arena_id, size_t *size);
int mi_reserve_huge_os_pages_at_ex(size_t pages, int numa_node, size_t timeout_msecs, bool exclusive, mi_arena_id_t *arena_id);
int mi_reserve_os_memory_ex(size_t size, bool commit, bool allow_large, bool exclusive, mi_arena_id_t *arena_id);
bool mi_manage_os_memory_ex(void *start, size_t size, bool is_committed, bool is_pinned, bool is_zero, int numa_node, bool exclusive, mi_arena_id_t *arena_id);
mi_heap_t *mi_heap_new_in_arena(mi_arena_id_t arena_id);
typedef void *mi_subproc_id_t;
mi_subproc_id_t mi_subproc_main(void);
mi_subproc_id_t mi_subproc_new(void);
void mi_subproc_delete(mi_subproc_id_t subproc);
void mi_subproc_add_current_thread(mi_subproc_id_t subproc);
bool mi_abandoned_visit_blocks(mi_subproc_id_t subproc_id, int heap_tag, bool visit_blocks, mi_block_visit_fun *visitor, void *arg);
void mi_heap_set_numa_affinity(mi_heap_t *heap, int numa_node);
void mi_heap_guarded_set_sample_rate(mi_heap_t *heap, size_t sample_rate, size_t seed);
void mi_heap_guarded_set_size_bound(mi_heap_t *heap, size_t min, size_t max);
void mi_thread_set_in_threadpool(void);
mi_heap_t *mi_heap_new_ex(int heap_tag, bool allow_destroy, mi_arena_id_t arena_id);
int mi_reserve_huge_os_pages(size_t pages, double max_secs, size_t *pages_reserved);
void mi_collect_reduce(size_t target_thread_owned);
typedef bool mi_commit_fun_t(bool commit, void *start, size_t size, bool *is_zero, void *user_arg);
bool mi_manage_memory(void *start, size_t size, bool is_committed, bool is_pinned, bool is_zero, int numa_node, bool exclusive, mi_commit_fun_t *commit_fun, void *commit_fun_arg, mi_arena_id_t *arena_id);
bool mi_arena_unload(mi_arena_id_t arena_id, void **base, size_t *accessed_size, size_t *size);
bool mi_arena_reload(void *start, size_t size, mi_commit_fun_t *commit_fun, void *commit_fun_arg, mi_arena_id_t *arena_id);
bool mi_heap_reload(mi_heap_t *heap, mi_arena_id_t arena);
void mi_heap_unload(mi_heap_t *heap);
bool mi_arena_contains(mi_arena_id_t arena_id, const void *p);
typedef enum mi_option_e
{
  mi_option_show_errors,
  mi_option_show_stats,
  mi_option_verbose,
  mi_option_eager_commit,
  mi_option_arena_eager_commit,
  mi_option_purge_decommits,
  mi_option_allow_large_os_pages,
  mi_option_reserve_huge_os_pages,
  mi_option_reserve_huge_os_pages_at,
  mi_option_reserve_os_memory,
  mi_option_deprecated_segment_cache,
  mi_option_deprecated_page_reset,
  mi_option_abandoned_page_purge,
  mi_option_deprecated_segment_reset,
  mi_option_eager_commit_delay,
  mi_option_purge_delay,
  mi_option_use_numa_nodes,
  mi_option_disallow_os_alloc,
  mi_option_os_tag,
  mi_option_max_errors,
  mi_option_max_warnings,
  mi_option_deprecated_max_segment_reclaim,
  mi_option_destroy_on_exit,
  mi_option_arena_reserve,
  mi_option_arena_purge_mult,
  mi_option_deprecated_purge_extend_delay,
  mi_option_disallow_arena_alloc,
  mi_option_retry_on_oom,
  mi_option_visit_abandoned,
  mi_option_guarded_min,
  mi_option_guarded_max,
  mi_option_guarded_precise,
  mi_option_guarded_sample_rate,
  mi_option_guarded_sample_seed,
  mi_option_generic_collect,
  mi_option_page_reclaim_on_free,
  mi_option_page_full_retain,
  mi_option_page_max_candidates,
  mi_option_max_vabits,
  mi_option_pagemap_commit,
  mi_option_page_commit_on_demand,
  mi_option_page_max_reclaim,
  mi_option_page_cross_thread_max_reclaim,
  _mi_option_last,
  mi_option_large_os_pages = mi_option_allow_large_os_pages,
  mi_option_eager_region_commit = mi_option_arena_eager_commit,
  mi_option_reset_decommits = mi_option_purge_decommits,
  mi_option_reset_delay = mi_option_purge_delay,
  mi_option_abandoned_page_reset = mi_option_abandoned_page_purge,
  mi_option_limit_os_alloc = mi_option_disallow_os_alloc
} mi_option_t;
bool mi_option_is_enabled(mi_option_t option);
void mi_option_enable(mi_option_t option);
void mi_option_disable(mi_option_t option);
void mi_option_set_enabled(mi_option_t option, bool enable);
void mi_option_set_enabled_default(mi_option_t option, bool enable);
long mi_option_get(mi_option_t option);
long mi_option_get_clamp(mi_option_t option, long min, long max);
size_t mi_option_get_size(mi_option_t option);
void mi_option_set(mi_option_t option, long value);
void mi_option_set_default(mi_option_t option, long value);
void mi_cfree(void *p);
void *mi__expand(void *p, size_t newsize);
size_t mi_malloc_size(const void *p);
size_t mi_malloc_good_size(size_t size);
size_t mi_malloc_usable_size(const void *p);
int mi_posix_memalign(void **p, size_t alignment, size_t size);
void *mi_memalign(size_t alignment, size_t size);
void *mi_valloc(size_t size);
void *mi_pvalloc(size_t size);
void *mi_aligned_alloc(size_t alignment, size_t size);
void *mi_reallocarray(void *p, size_t count, size_t size);
int mi_reallocarr(void *p, size_t count, size_t size);
void *mi_aligned_recalloc(void *p, size_t newcount, size_t size, size_t alignment);
void *mi_aligned_offset_recalloc(void *p, size_t newcount, size_t size, size_t alignment, size_t offset);
unsigned short *mi_wcsdup(const unsigned short *s);
unsigned char *mi_mbsdup(const unsigned char *s);
int mi_dupenv_s(char **buf, size_t *size, const char *name);
int mi_wdupenv_s(unsigned short **buf, size_t *size, const unsigned short *name);
void mi_free_size(void *p, size_t size);
void mi_free_size_aligned(void *p, size_t size, size_t alignment);
void mi_free_aligned(void *p, size_t alignment);
void *mi_new(size_t size);
void *mi_new_aligned(size_t size, size_t alignment);
void *mi_new_nothrow(size_t size);
void *mi_new_aligned_nothrow(size_t size, size_t alignment);
void *mi_new_n(size_t count, size_t size);
void *mi_new_realloc(void *p, size_t newsize);
void *mi_new_reallocn(void *p, size_t newcount, size_t size);
void *mi_heap_alloc_new(mi_heap_t *heap, size_t size);
void *mi_heap_alloc_new_n(mi_heap_t *heap, size_t count, size_t size);
typedef struct mi_stat_count_s
{
  int64_t total;
  int64_t peak;
  int64_t current;
} mi_stat_count_t;
typedef struct mi_stat_counter_s
{
  int64_t total;
} mi_stat_counter_t;
typedef enum mi_chunkbin_e
{
  MI_CBIN_SMALL,
  MI_CBIN_OTHER,
  MI_CBIN_MEDIUM,
  MI_CBIN_LARGE,
  MI_CBIN_NONE,
  MI_CBIN_COUNT
} mi_chunkbin_t;
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
} mi_stats_t;
void mi_stats_get(size_t stats_size, mi_stats_t *stats);
char *mi_stats_get_json(size_t buf_size, char *buf);
size_t mi_stats_get_bin_size(size_t bin);
typedef int64_t mi_ssize_t;
size_t _mi_popcount_generic(size_t x);
inline static size_t mi_popcount(size_t x)
{
  return __builtin_popcountll(x);
}

size_t _mi_clz_generic(size_t x);
size_t _mi_ctz_generic(size_t x);
inline static size_t mi_ctz(size_t x)
{
  return (x != 0) ? ((size_t) __builtin_ctzll(x)) : ((1 << 3) * 8);
}

inline static size_t mi_clz(size_t x)
{
  return (x != 0) ? ((size_t) __builtin_clzll(x)) : ((1 << 3) * 8);
}

inline static bool mi_bsf(size_t x, size_t *idx)
{
  return (x != 0) ? ((*idx = mi_ctz(x), 1)) : (0);
}

inline static bool mi_bsr(size_t x, size_t *idx)
{
  return (x != 0) ? ((*idx = (((1 << 3) * 8) - 1) - mi_clz(x), 1)) : (0);
}

inline static size_t mi_rotr(size_t x, size_t r)
{
  const unsigned int rshift = ((unsigned int) r) & (((1 << 3) * 8) - 1);
  return (x >> rshift) | (x << ((-rshift) & (((1 << 3) * 8) - 1)));
}

inline static size_t mi_rotl(size_t x, size_t r)
{
  const unsigned int rshift = ((unsigned int) r) & (((1 << 3) * 8) - 1);
  return (x << rshift) | (x >> ((-rshift) & (((1 << 3) * 8) - 1)));
}

inline static uint32_t mi_rotl32(uint32_t x, uint32_t r)
{
  const unsigned int rshift = ((unsigned int) r) & 31;
  return (x << rshift) | (x >> ((-rshift) & 31));
}

inline static void mi_atomic_yield(void);
inline static intptr_t mi_atomic_addi(_Atomic intptr_t *p, intptr_t add);
inline static intptr_t mi_atomic_subi(_Atomic intptr_t *p, intptr_t sub);
inline static int64_t mi_atomic_addi64_relaxed(volatile int64_t *p, int64_t add)
{
  return atomic_fetch_add_explicit((int64_t *) p, add, memory_order_relaxed);
}

inline static void mi_atomic_void_addi64_relaxed(volatile int64_t *p, const volatile int64_t *padd)
{
  const int64_t add = atomic_load_explicit((int64_t *) padd, memory_order_relaxed);
  if (add != 0)
  {
    atomic_fetch_add_explicit((int64_t *) p, add, memory_order_relaxed);
  }
}

inline static void mi_atomic_maxi64_relaxed(volatile int64_t *p, int64_t x)
{
  int64_t current = atomic_load_explicit((int64_t *) p, memory_order_relaxed);
  while ((current < x) && (!atomic_compare_exchange_weak_explicit((int64_t *) p, &current, x, memory_order_release, memory_order_relaxed)))
  {
  }

  ;
}

inline static intptr_t mi_atomic_addi(_Atomic intptr_t *p, intptr_t add)
{
  return (intptr_t) atomic_fetch_add_explicit((uintptr_t *) p, (uintptr_t) add, memory_order_acq_rel);
}

inline static intptr_t mi_atomic_subi(_Atomic intptr_t *p, intptr_t sub)
{
  return (intptr_t) mi_atomic_addi(p, -sub);
}

typedef _Atomic uintptr_t mi_atomic_once_t;
inline static bool mi_atomic_once(mi_atomic_once_t *once)
{
  if (atomic_load_explicit(once, memory_order_relaxed) != 0)
  {
    return 0;
  }
  uintptr_t expected = 0;
  return atomic_compare_exchange_strong_explicit(once, &expected, (uintptr_t) 1, memory_order_acq_rel, memory_order_acquire);
}

typedef _Atomic uintptr_t mi_atomic_guard_t;
inline static void mi_atomic_yield(void)
{
}

void _mi_error_message(int err, const char *fmt, ...);
inline static bool mi_lock_try_acquire(pthread_mutex_t *lock)
{
  return pthread_mutex_trylock(lock) == 0;
}

inline static void mi_lock_acquire(pthread_mutex_t *lock)
{
  const int err = pthread_mutex_lock(lock);
  if (err != 0)
  {
    _mi_error_message(err, "internal error: lock cannot be acquired\n");
  }
}

inline static void mi_lock_release(pthread_mutex_t *lock)
{
  pthread_mutex_unlock(lock);
}

inline static void mi_lock_init(pthread_mutex_t *lock)
{
  pthread_mutex_init(lock, 0);
}

inline static void mi_lock_done(pthread_mutex_t *lock)
{
  pthread_mutex_destroy(lock);
}

typedef struct mi_arena_s mi_arena_t;
typedef enum mi_memkind_e
{
  MI_MEM_NONE,
  MI_MEM_EXTERNAL,
  MI_MEM_STATIC,
  MI_MEM_META,
  MI_MEM_OS,
  MI_MEM_OS_HUGE,
  MI_MEM_OS_REMAP,
  MI_MEM_ARENA
} mi_memkind_t;
inline static bool mi_memkind_is_os(mi_memkind_t memkind)
{
  return (memkind >= MI_MEM_OS) && (memkind <= MI_MEM_OS_REMAP);
}

inline static bool mi_memkind_needs_no_free(mi_memkind_t memkind)
{
  return memkind <= MI_MEM_STATIC;
}

typedef struct mi_memid_os_info
{
  void *base;
  size_t size;
} mi_memid_os_info_t;
typedef struct mi_memid_arena_info
{
  mi_arena_t *arena;
  uint32_t slice_index;
  uint32_t slice_count;
} mi_memid_arena_info_t;
typedef struct mi_memid_meta_info
{
  void *meta_page;
  uint32_t block_index;
  uint32_t block_count;
} mi_memid_meta_info_t;
typedef struct mi_memid_s
{
  union 
  {
    mi_memid_os_info_t os;
    mi_memid_arena_info_t arena;
    mi_memid_meta_info_t meta;
  } mem;
  mi_memkind_t memkind;
  bool is_pinned;
  bool initially_committed;
  bool initially_zero;
} mi_memid_t;
inline static bool mi_memid_is_os(mi_memid_t memid)
{
  return mi_memkind_is_os(memid.memkind);
}

inline static bool mi_memid_needs_no_free(mi_memid_t memid)
{
  return mi_memkind_needs_no_free(memid.memkind);
}

inline static mi_arena_t *mi_memid_arena(mi_memid_t memid)
{
  return (memid.memkind == MI_MEM_ARENA) ? (memid.mem.arena.arena) : (0);
}

typedef uintptr_t mi_encoded_t;
typedef size_t mi_threadid_t;
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t;
typedef size_t mi_page_flags_t;
typedef uintptr_t mi_thread_free_t;
typedef uint8_t mi_heaptag_t;
typedef struct mi_page_s
{
  _Atomic mi_threadid_t xthread_id;
  mi_block_t *free;
  uint16_t used;
  uint16_t capacity;
  uint16_t reserved;
  uint8_t retire_expire;
  mi_block_t *local_free;
  _Atomic mi_thread_free_t xthread_free;
  size_t block_size;
  uint8_t *page_start;
  mi_heaptag_t heap_tag;
  bool free_is_zero;
  uintptr_t keys[2];
  mi_heap_t *heap;
  struct mi_page_s *next;
  struct mi_page_s *prev;
  size_t slice_committed;
  mi_memid_t memid;
} mi_page_t;
typedef enum mi_page_kind_e
{
  MI_PAGE_SMALL,
  MI_PAGE_MEDIUM,
  MI_PAGE_LARGE,
  MI_PAGE_SINGLETON
} mi_page_kind_t;
typedef struct mi_tld_s mi_tld_t;
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t count;
  size_t block_size;
} mi_page_queue_t;
typedef struct mi_random_cxt_s
{
  uint32_t input[16];
  uint32_t output[16];
  int output_available;
  bool weak;
} mi_random_ctx_t;
typedef struct mi_padding_s
{
  uint32_t canary;
  uint32_t delta;
} mi_padding_t;
struct mi_heap_s
{
  mi_tld_t *tld;
  mi_arena_t *exclusive_arena;
  int numa_node;
  uintptr_t cookie;
  mi_random_ctx_t random;
  size_t page_count;
  size_t page_retired_min;
  size_t page_retired_max;
  long generic_count;
  long generic_collect_count;
  mi_heap_t *next;
  long page_full_retain;
  bool allow_page_reclaim;
  bool allow_page_abandon;
  uint8_t tag;
  mi_page_t *pages_free_direct[(128 + ((((sizeof(mi_padding_t)) + (1 << 3)) - 1) / (1 << 3))) + 1];
  mi_page_queue_t pages[(73U + 1) + 1];
  mi_memid_t memid;
};
typedef struct mi_subproc_s
{
  _Atomic size_t arena_count;
  mi_arena_t * _Atomic arenas[160];
  pthread_mutex_t arena_reserve_lock;
  _Atomic int64_t purge_expire;
  _Atomic size_t abandoned_count[(73U + 1) + 1];
  mi_page_t *os_abandoned_pages;
  pthread_mutex_t os_abandoned_pages_lock;
  mi_memid_t memid;
  mi_stats_t stats;
} mi_subproc_t;
typedef int64_t mi_msecs_t;
struct mi_tld_s
{
  mi_threadid_t thread_id;
  size_t thread_seq;
  int numa_node;
  mi_subproc_t *subproc;
  mi_heap_t *heap_backing;
  mi_heap_t *heaps;
  unsigned long long heartbeat;
  bool recurse;
  bool is_in_threadpool;
  mi_stats_t stats;
  mi_memid_t memid;
};
typedef struct mi_bitmap_s mi_bitmap_t;
typedef struct mi_bbitmap_s mi_bbitmap_t;
typedef struct mi_arena_s
{
  mi_memid_t memid;
  mi_subproc_t *subproc;
  size_t slice_count;
  size_t info_slices;
  int numa_node;
  bool is_exclusive;
  _Atomic mi_msecs_t purge_expire;
  mi_commit_fun_t *commit_fun;
  void *commit_fun_arg;
  mi_bbitmap_t *slices_free;
  mi_bitmap_t *slices_committed;
  mi_bitmap_t *slices_dirty;
  mi_bitmap_t *slices_purge;
  mi_bitmap_t *pages;
  mi_bitmap_t *pages_abandoned[(73U + 1) + 1];
} mi_arena_t;
int _mi_vsnprintf(char *buf, size_t bufsize, const char *fmt, va_list args);
int _mi_snprintf(char *buf, size_t buflen, const char *fmt, ...);
char _mi_toupper(char c);
int _mi_strnicmp(const char *s, const char *t, size_t n);
void _mi_strlcpy(char *dest, const char *src, size_t dest_size);
void _mi_strlcat(char *dest, const char *src, size_t dest_size);
size_t _mi_strlen(const char *s);
size_t _mi_strnlen(const char *s, size_t max_len);
bool _mi_getenv(const char *name, char *result, size_t result_size);
void _mi_fputs(mi_output_fun *out, void *arg, const char *prefix, const char *message);
void _mi_fprintf(mi_output_fun *out, void *arg, const char *fmt, ...);
void _mi_raw_message(const char *fmt, ...);
void _mi_message(const char *fmt, ...);
void _mi_warning_message(const char *fmt, ...);
void _mi_verbose_message(const char *fmt, ...);
void _mi_trace_message(const char *fmt, ...);
void _mi_options_init(void);
long _mi_option_get_fast(mi_option_t option);
void _mi_error_message(int err, const char *fmt, ...);
void _mi_random_init(mi_random_ctx_t *ctx);
void _mi_random_init_weak(mi_random_ctx_t *ctx);
void _mi_random_reinit_if_weak(mi_random_ctx_t *ctx);
void _mi_random_split(mi_random_ctx_t *ctx, mi_random_ctx_t *new_ctx);
uintptr_t _mi_random_next(mi_random_ctx_t *ctx);
uintptr_t _mi_heap_random_next(mi_heap_t *heap);
uintptr_t _mi_os_random_weak(uintptr_t extra_seed);
inline static uintptr_t _mi_random_shuffle(uintptr_t x);
extern const mi_page_t _mi_page_empty;
void _mi_auto_process_init(void);
void _mi_auto_process_done(void);
bool _mi_is_redirected(void);
bool _mi_allocator_init(const char **message);
void _mi_allocator_done(void);
bool _mi_is_main_thread(void);
size_t _mi_current_thread_count(void);
bool _mi_preloading(void);
void _mi_thread_done(mi_heap_t *heap);
mi_subproc_t *_mi_subproc(void);
mi_subproc_t *_mi_subproc_main(void);
mi_subproc_t *_mi_subproc_from_id(mi_subproc_id_t subproc_id);
mi_threadid_t _mi_thread_id(void);
size_t _mi_thread_seq_id(void);
mi_tld_t *_mi_thread_tld(void);
void _mi_heap_guarded_init(mi_heap_t *heap);
mi_heap_t *_mi_heap_main_get(void);
void _mi_os_init(void);
void *_mi_os_alloc(size_t size, mi_memid_t *memid);
void *_mi_os_zalloc(size_t size, mi_memid_t *memid);
void _mi_os_free(void *p, size_t size, mi_memid_t memid);
void _mi_os_free_ex(void *p, size_t size, bool still_committed, mi_memid_t memid, mi_subproc_t *subproc);
size_t _mi_os_page_size(void);
size_t _mi_os_guard_page_size(void);
size_t _mi_os_good_alloc_size(size_t size);
bool _mi_os_has_overcommit(void);
bool _mi_os_has_virtual_reserve(void);
size_t _mi_os_virtual_address_bits(void);
bool _mi_os_reset(void *addr, size_t size);
bool _mi_os_decommit(void *addr, size_t size);
void _mi_os_reuse(void *p, size_t size);
bool _mi_os_commit(void *p, size_t size, bool *is_zero);
bool _mi_os_commit_ex(void *addr, size_t size, bool *is_zero, size_t stat_size);
bool _mi_os_protect(void *addr, size_t size);
bool _mi_os_unprotect(void *addr, size_t size);
bool _mi_os_purge(void *p, size_t size);
bool _mi_os_purge_ex(void *p, size_t size, bool allow_reset, size_t stats_size, mi_commit_fun_t *commit_fun, void *commit_fun_arg);
size_t _mi_os_secure_guard_page_size(void);
bool _mi_os_secure_guard_page_set_at(void *addr, mi_memid_t memid);
bool _mi_os_secure_guard_page_set_before(void *addr, mi_memid_t memid);
bool _mi_os_secure_guard_page_reset_at(void *addr, mi_memid_t memid);
bool _mi_os_secure_guard_page_reset_before(void *addr, mi_memid_t memid);
int _mi_os_numa_node(void);
int _mi_os_numa_node_count(void);
void *_mi_os_alloc_aligned(size_t size, size_t alignment, bool commit, bool allow_large, mi_memid_t *memid);
void *_mi_os_alloc_aligned_at_offset(size_t size, size_t alignment, size_t align_offset, bool commit, bool allow_large, mi_memid_t *memid);
void *_mi_os_get_aligned_hint(size_t try_alignment, size_t size);
bool _mi_os_use_large_page(size_t size, size_t alignment);
size_t _mi_os_large_page_size(void);
void *_mi_os_alloc_huge_os_pages(size_t pages, int numa_node, mi_msecs_t max_secs, size_t *pages_reserved, size_t *psize, mi_memid_t *memid);
mi_arena_id_t _mi_arena_id_none(void);
mi_arena_t *_mi_arena_from_id(mi_arena_id_t id);
bool _mi_arena_memid_is_suitable(mi_memid_t memid, mi_arena_t *request_arena);
void *_mi_arenas_alloc(mi_subproc_t *subproc, size_t size, bool commit, bool allow_pinned, mi_arena_t *req_arena, size_t tseq, int numa_node, mi_memid_t *memid);
void *_mi_arenas_alloc_aligned(mi_subproc_t *subproc, size_t size, size_t alignment, size_t align_offset, bool commit, bool allow_pinned, mi_arena_t *req_arena, size_t tseq, int numa_node, mi_memid_t *memid);
void _mi_arenas_free(void *p, size_t size, mi_memid_t memid);
bool _mi_arenas_contain(const void *p);
void _mi_arenas_collect(bool force_purge, bool visit_all, mi_tld_t *tld);
void _mi_arenas_unsafe_destroy_all(mi_subproc_t *subproc);
mi_page_t *_mi_arenas_page_alloc(mi_heap_t *heap, size_t block_size, size_t page_alignment);
void _mi_arenas_page_free(mi_page_t *page, mi_tld_t *tld);
void _mi_arenas_page_abandon(mi_page_t *page, mi_tld_t *tld);
void _mi_arenas_page_unabandon(mi_page_t *page);
bool _mi_arenas_page_try_reabandon_to_mapped(mi_page_t *page);
void *_mi_meta_zalloc(size_t size, mi_memid_t *memid);
void _mi_meta_free(void *p, size_t size, mi_memid_t memid);
bool _mi_meta_is_meta_page(void *p);
bool _mi_page_map_init(void);
bool _mi_page_map_register(mi_page_t *page);
void _mi_page_map_unregister(mi_page_t *page);
void _mi_page_map_unregister_range(void *start, size_t size);
mi_page_t *_mi_safe_ptr_page(const void *p);
void _mi_page_map_unsafe_destroy(mi_subproc_t *subproc);
void *_mi_malloc_generic(mi_heap_t *heap, size_t size, bool zero, size_t huge_alignment);
void _mi_page_retire(mi_page_t *page);
void _mi_page_unfull(mi_page_t *page);
void _mi_page_free(mi_page_t *page, mi_page_queue_t *pq);
void _mi_page_abandon(mi_page_t *page, mi_page_queue_t *pq);
void _mi_heap_collect_retired(mi_heap_t *heap, bool force);
size_t _mi_page_queue_append(mi_heap_t *heap, mi_page_queue_t *pq, mi_page_queue_t *append);
void _mi_deferred_free(mi_heap_t *heap, bool force);
void _mi_page_free_collect(mi_page_t *page, bool force);
void _mi_page_free_collect_partly(mi_page_t *page, mi_block_t *head);
bool _mi_page_init(mi_heap_t *heap, mi_page_t *page);
bool _mi_page_queue_is_valid(mi_heap_t *heap, const mi_page_queue_t *pq);
size_t _mi_page_bin(const mi_page_t *page);
size_t _mi_bin_size(size_t bin);
size_t _mi_bin(size_t size);
mi_heap_t *_mi_heap_create(int heap_tag, bool allow_destroy, mi_arena_id_t arena_id, mi_tld_t *tld);
void _mi_heap_init(mi_heap_t *heap, mi_arena_id_t arena_id, bool noreclaim, uint8_t tag, mi_tld_t *tld);
void _mi_heap_destroy_pages(mi_heap_t *heap);
void _mi_heap_collect_abandon(mi_heap_t *heap);
void _mi_heap_set_default_direct(mi_heap_t *heap);
bool _mi_heap_memid_is_suitable(mi_heap_t *heap, mi_memid_t memid);
void _mi_heap_unsafe_destroy_all(mi_heap_t *heap);
mi_heap_t *_mi_heap_by_tag(mi_heap_t *heap, uint8_t tag);
void _mi_heap_area_init(mi_heap_area_t *area, mi_page_t *page);
bool _mi_heap_area_visit_blocks(const mi_heap_area_t *area, mi_page_t *page, mi_block_visit_fun *visitor, void *arg);
void _mi_heap_page_reclaim(mi_heap_t *heap, mi_page_t *page);
void _mi_stats_init(void);
void _mi_stats_done(mi_stats_t *stats);
void _mi_stats_print(mi_stats_t *stats, mi_output_fun *out, void *arg);
void _mi_stats_merge_thread(mi_tld_t *tld);
void _mi_stats_merge_from(mi_stats_t *to, mi_stats_t *from);
mi_msecs_t _mi_clock_now(void);
mi_msecs_t _mi_clock_end(mi_msecs_t start);
mi_msecs_t _mi_clock_start(void);
void *_mi_page_malloc_zero(mi_heap_t *heap, mi_page_t *page, size_t size, bool zero);
void *_mi_page_malloc(mi_heap_t *heap, mi_page_t *page, size_t size);
void *_mi_page_malloc_zeroed(mi_heap_t *heap, mi_page_t *page, size_t size);
void *_mi_heap_malloc_zero(mi_heap_t *heap, size_t size, bool zero);
void *_mi_heap_malloc_zero_ex(mi_heap_t *heap, size_t size, bool zero, size_t huge_alignment);
void *_mi_heap_realloc_zero(mi_heap_t *heap, void *p, size_t newsize, bool zero);
mi_block_t *_mi_page_ptr_unalign(const mi_page_t *page, const void *p);
void _mi_padding_shrink(const mi_page_t *page, const mi_block_t *block, const size_t min_size);
bool _mi_page_is_valid(mi_page_t *page);
void _mi_assert_fail(const char *assertion, const char *fname, unsigned int line, const char *func);
void __mi_stat_increase(mi_stat_count_t *stat, size_t amount);
void __mi_stat_decrease(mi_stat_count_t *stat, size_t amount);
void __mi_stat_increase_mt(mi_stat_count_t *stat, size_t amount);
void __mi_stat_decrease_mt(mi_stat_count_t *stat, size_t amount);
void __mi_stat_adjust_increase(mi_stat_count_t *stat, size_t amount);
void __mi_stat_adjust_decrease(mi_stat_count_t *stat, size_t amount);
void __mi_stat_adjust_increase_mt(mi_stat_count_t *stat, size_t amount);
void __mi_stat_adjust_decrease_mt(mi_stat_count_t *stat, size_t amount);
void __mi_stat_counter_increase(mi_stat_counter_t *stat, size_t amount);
void __mi_stat_counter_increase_mt(mi_stat_counter_t *stat, size_t amount);
typedef enum mi_option_init_e
{
  MI_OPTION_UNINIT,
  MI_OPTION_DEFAULTED,
  MI_OPTION_INITIALIZED
} mi_option_init_t;
typedef struct mi_option_desc_s
{
  long value;
  mi_option_init_t init;
  mi_option_t option;
  const char *name;
  const char *legacy_name;
} mi_option_desc_t;
inline static bool _mi_is_power_of_two(uintptr_t x)
{
  return (x & (x - 1)) == 0;
}

inline static bool _mi_is_aligned(void *p, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 423, __func__));
  return (((uintptr_t) p) % alignment) == 0;
}

inline static uintptr_t _mi_align_up(uintptr_t sz, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 429, __func__));
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

inline static uint8_t *_mi_align_up_ptr(void *p, size_t alignment)
{
  return (uint8_t *) _mi_align_up((uintptr_t) p, alignment);
}

inline static uintptr_t _mi_align_down(uintptr_t sz, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 447, __func__));
  uintptr_t mask = alignment - 1;
  if ((alignment & mask) == 0)
  {
    return sz & (~mask);
  }
  else
  {
    return (sz / alignment) * alignment;
  }
}

inline static void *mi_align_down_ptr(void *p, size_t alignment)
{
  return (void *) _mi_align_down((uintptr_t) p, alignment);
}

inline static uintptr_t _mi_divide_up(uintptr_t size, size_t divider)
{
  (divider != 0) ? ((void) 0) : (_mi_assert_fail("divider != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 463, __func__));
  return (divider == 0) ? (size) : (((size + divider) - 1) / divider);
}

inline static size_t _mi_clamp(size_t sz, size_t min, size_t max)
{
  if (sz < min)
  {
    return min;
  }
  else
    if (sz > max)
  {
    return max;
  }
  else
    return sz;
}

inline static bool mi_mem_is_zero(const void *p, size_t size)
{
  for (size_t i = 0; i < size; i += 1)
  {
    if (((uint8_t *) p)[i] != 0)
    {
      return 0;
    }
  }

  return 1;
}

inline static size_t _mi_wsize_from_size(size_t size)
{
  (size <= (SIZE_MAX - (sizeof(uintptr_t)))) ? ((void) 0) : (_mi_assert_fail("size <= SIZE_MAX - sizeof(uintptr_t)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 486, __func__));
  return ((size + (sizeof(uintptr_t))) - 1) / (sizeof(uintptr_t));
}

inline static bool mi_mul_overflow(size_t count, size_t size, size_t *total)
{
  return __builtin_umulll_overflow(count, size, (unsigned long long *) total);
}

inline static bool mi_count_size_overflow(size_t count, size_t size, size_t *total)
{
  if (count == 1)
  {
    *total = size;
    return 0;
  }
  else
    if (__builtin_expect(!(!mi_mul_overflow(count, size, total)), 0))
  {
    _mi_error_message(75, "allocation request is too large (%zu * %zu bytes)\n", count, size);
    *total = SIZE_MAX;
    return 1;
  }
  else
    return 0;
}

extern const mi_heap_t _mi_heap_empty;
inline static bool mi_heap_is_backing(const mi_heap_t *heap)
{
  return heap->tld->heap_backing == heap;
}

inline static bool mi_heap_is_initialized(const mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 542, __func__));
  return (heap != 0) && (heap != (&_mi_heap_empty));
}

inline static mi_page_t *_mi_heap_get_free_small_page(mi_heap_t *heap, size_t size)
{
  (size <= ((128 * (sizeof(void *))) + (sizeof(mi_padding_t)))) ? ((void) 0) : (_mi_assert_fail("size <= (MI_SMALL_SIZE_MAX + MI_PADDING_SIZE)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 547, __func__));
  const size_t idx = _mi_wsize_from_size(size);
  (idx < ((128 + ((((sizeof(mi_padding_t)) + (1 << 3)) - 1) / (1 << 3))) + 1)) ? ((void) 0) : (_mi_assert_fail("idx < MI_PAGES_DIRECT", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 549, __func__));
  return heap->pages_free_direct[idx];
}

typedef mi_page_t **mi_submap_t;
extern _Atomic mi_submap_t *_mi_page_map;
inline static size_t _mi_page_map_index(const void *p, size_t *sub_idx)
{
  const size_t u = (size_t) (((uintptr_t) p) / (1UL << (13 + 3)));
  if (sub_idx != 0)
  {
    *sub_idx = u % (1UL << 13);
  }
  return u / (1UL << 13);
}

inline static mi_submap_t _mi_page_map_at(size_t idx)
{
  return atomic_load_explicit(&_mi_page_map[idx], memory_order_relaxed);
}

inline static mi_page_t *_mi_unchecked_ptr_page(const void *p)
{
  size_t sub_idx;
  const size_t idx = _mi_page_map_index(p, &sub_idx);
  return _mi_page_map_at(idx)[sub_idx];
}

inline static mi_page_t *_mi_checked_ptr_page(const void *p)
{
  size_t sub_idx;
  const size_t idx = _mi_page_map_index(p, &sub_idx);
  const mi_submap_t sub = _mi_page_map_at(idx);
  if (__builtin_expect(!(!(sub == 0)), 0))
  {
    return 0;
  }
  return sub[sub_idx];
}

inline static mi_page_t *_mi_ptr_page(const void *p)
{
  ((p == 0) || mi_is_in_heap_region(p)) ? ((void) 0) : (_mi_assert_fail("p==NULL || mi_is_in_heap_region(p)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 638, __func__));
  return _mi_checked_ptr_page(p);
}

inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 649, __func__));
  return page->block_size;
}

inline static uint8_t *mi_page_start(const mi_page_t *page)
{
  return page->page_start;
}

inline static size_t mi_page_size(const mi_page_t *page)
{
  return mi_page_block_size(page) * page->reserved;
}

inline static uint8_t *mi_page_area(const mi_page_t *page, size_t *size)
{
  if (size)
  {
    *size = mi_page_size(page);
  }
  return mi_page_start(page);
}

inline static size_t mi_page_info_size(void)
{
  return _mi_align_up(sizeof(mi_page_t), 16);
}

inline static bool mi_page_contains_address(const mi_page_t *page, const void *p)
{
  size_t psize;
  uint8_t *start = mi_page_area(page, &psize);
  return (start <= ((uint8_t *) p)) && (((uint8_t *) p) < (start + psize));
}

inline static bool mi_page_is_in_arena(const mi_page_t *page)
{
  return page->memid.memkind == MI_MEM_ARENA;
}

inline static bool mi_page_is_singleton(const mi_page_t *page)
{
  return page->reserved == 1;
}

inline static size_t mi_page_usable_block_size(const mi_page_t *page)
{
  return mi_page_block_size(page) - (sizeof(mi_padding_t));
}

inline static uint8_t *mi_page_slice_start(const mi_page_t *page)
{
  return (uint8_t *) page;
}

inline static size_t mi_page_slice_offset_of(const mi_page_t *page, size_t offset_relative_to_page_start)
{
  return (page->page_start - mi_page_slice_start(page)) + offset_relative_to_page_start;
}

inline static size_t mi_page_committed(const mi_page_t *page)
{
  return (page->slice_committed == 0) ? (mi_page_size(page)) : (page->slice_committed - (page->page_start - mi_page_slice_start(page)));
}

inline static mi_heap_t *mi_page_heap(const mi_page_t *page)
{
  return page->heap;
}

inline static bool mi_page_all_free(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 714, __func__));
  return page->used == 0;
}

inline static bool mi_page_immediate_available(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 720, __func__));
  return page->free != 0;
}

inline static bool mi_page_is_expandable(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 727, __func__));
  (page->capacity <= page->reserved) ? ((void) 0) : (_mi_assert_fail("page->capacity <= page->reserved", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 728, __func__));
  return page->capacity < page->reserved;
}

inline static bool mi_page_is_full(mi_page_t *page)
{
  const bool full = page->reserved == page->used;
  ((!full) || (page->free == 0)) ? ((void) 0) : (_mi_assert_fail("!full || page->free == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 735, __func__));
  return full;
}

inline static bool mi_page_is_mostly_used(const mi_page_t *page)
{
  if (page == 0)
  {
    return 1;
  }
  uint16_t frac = page->reserved / 8U;
  return (page->reserved - page->used) <= frac;
}

inline static bool mi_page_is_used_at_frac(const mi_page_t *page, uint16_t n)
{
  if (page == 0)
  {
    return 1;
  }
  uint16_t frac = page->reserved / n;
  return (page->reserved - page->used) <= frac;
}

inline static bool mi_page_is_huge(const mi_page_t *page)
{
  return mi_page_is_singleton(page) && ((page->block_size > ((8 * (1 * (1UL << (13 + 3)))) / 8)) || (mi_memkind_is_os(page->memid.memkind) && (page->memid.mem.os.base < ((void *) page))));
}

inline static mi_page_queue_t *mi_page_queue(const mi_heap_t *heap, size_t size)
{
  mi_page_queue_t * const pq = &((mi_heap_t *) heap)->pages[_mi_bin(size)];
  if (size <= ((8 * (1 * (1UL << (13 + 3)))) / 8))
  {
    (pq->block_size <= ((8 * (1 * (1UL << (13 + 3)))) / 8)) ? ((void) 0) : (_mi_assert_fail("pq->block_size <= MI_LARGE_MAX_OBJ_SIZE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 762, __func__));
  }
  return pq;
}

inline static mi_threadid_t mi_page_xthread_id(const mi_page_t *page)
{
  return atomic_load_explicit(&((mi_page_t *) page)->xthread_id, memory_order_relaxed);
}

inline static mi_threadid_t mi_page_thread_id(const mi_page_t *page)
{
  return mi_page_xthread_id(page) & (~0x03UL);
}

inline static mi_page_flags_t mi_page_flags(const mi_page_t *page)
{
  return mi_page_xthread_id(page) & 0x03UL;
}

inline static void mi_page_flags_set(mi_page_t *page, bool set, mi_page_flags_t newflag)
{
  if (set)
  {
    atomic_fetch_or_explicit(&page->xthread_id, newflag, memory_order_relaxed);
  }
  else
  {
    atomic_fetch_and_explicit(&page->xthread_id, ~newflag, memory_order_relaxed);
  }
}

inline static bool mi_page_is_in_full(const mi_page_t *page)
{
  return (mi_page_flags(page) & 0x01UL) != 0;
}

inline static void mi_page_set_in_full(mi_page_t *page, bool in_full)
{
  mi_page_flags_set(page, in_full, 0x01UL);
}

inline static bool mi_page_has_interior_pointers(const mi_page_t *page)
{
  return (mi_page_flags(page) & 0x02UL) != 0;
}

inline static void mi_page_set_has_interior_pointers(mi_page_t *page, bool has_aligned)
{
  mi_page_flags_set(page, has_aligned, 0x02UL);
}

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
  ((tid & 0x03UL) == 0) ? ((void) 0) : (_mi_assert_fail("(tid & MI_PAGE_FLAG_MASK) == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 816, __func__));
  mi_threadid_t xtid_old = mi_page_xthread_id(page);
  mi_threadid_t xtid;
  do
  {
    xtid = tid | (xtid_old & 0x03UL);
  }
  while (!atomic_compare_exchange_weak_explicit(&page->xthread_id, &xtid_old, xtid, memory_order_release, memory_order_relaxed));
}

inline static bool mi_page_is_abandoned(const mi_page_t *page)
{
  return mi_page_thread_id(page) <= (0x03UL + 1);
}

inline static bool mi_page_is_abandoned_mapped(const mi_page_t *page)
{
  return mi_page_thread_id(page) == (0x03UL + 1);
}

inline static void mi_page_set_abandoned_mapped(mi_page_t *page)
{
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 836, __func__));
  atomic_fetch_or_explicit(&page->xthread_id, 0x03UL + 1, memory_order_relaxed);
}

inline static void mi_page_clear_abandoned_mapped(mi_page_t *page)
{
  (mi_page_is_abandoned_mapped(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned_mapped(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 841, __func__));
  atomic_fetch_and_explicit(&page->xthread_id, 0x03UL, memory_order_relaxed);
}

inline static mi_block_t *mi_tf_block(mi_thread_free_t tf)
{
  return (mi_block_t *) (tf & (~1));
}

inline static bool mi_tf_is_owned(mi_thread_free_t tf)
{
  return (tf & 1) == 1;
}

inline static mi_thread_free_t mi_tf_create(mi_block_t *block, bool owned)
{
  return (mi_thread_free_t) (((uintptr_t) block) | ((owned) ? (1) : (0)));
}

inline static mi_block_t *mi_page_thread_free(const mi_page_t *page)
{
  return mi_tf_block(atomic_load_explicit(&((mi_page_t *) page)->xthread_free, memory_order_relaxed));
}

inline static bool mi_page_has_any_available(const mi_page_t *page)
{
  ((page != 0) && (page->reserved > 0)) ? ((void) 0) : (_mi_assert_fail("page != NULL && page->reserved > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 867, __func__));
  return (page->used < page->reserved) || (mi_page_thread_free(page) != 0);
}

inline static bool mi_page_is_owned(const mi_page_t *page)
{
  return mi_tf_is_owned(atomic_load_explicit(&((mi_page_t *) page)->xthread_free, memory_order_relaxed));
}

inline static void _mi_page_unown_unconditional(mi_page_t *page)
{
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 879, __func__));
  (mi_page_thread_id(page) == 0) ? ((void) 0) : (_mi_assert_fail("mi_page_thread_id(page)==0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 880, __func__));
  const uintptr_t old = atomic_fetch_and_explicit(&page->xthread_free, ~((uintptr_t) 1), memory_order_acq_rel);
  ((old & 1) == 1) ? ((void) 0) : (_mi_assert_fail("(old&1)==1", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 882, __func__));
  (void) old;
}

inline static bool mi_page_try_claim_ownership(mi_page_t *page)
{
  const uintptr_t old = atomic_fetch_or_explicit(&page->xthread_free, 1, memory_order_acq_rel);
  return (old & 1) == 0;
}

inline static bool _mi_page_unown(mi_page_t *page)
{
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 894, __func__));
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 895, __func__));
  mi_thread_free_t tf_new;
  mi_thread_free_t tf_old = atomic_load_explicit(&page->xthread_free, memory_order_relaxed);
  do
  {
    (mi_tf_is_owned(tf_old)) ? ((void) 0) : (_mi_assert_fail("mi_tf_is_owned(tf_old)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 899, __func__));
    while (__builtin_expect(!(!(mi_tf_block(tf_old) != 0)), 0))
    {
      _mi_page_free_collect(page, 0);
      if (mi_page_all_free(page))
      {
        _mi_arenas_page_unabandon(page);
        _mi_arenas_page_free(page, 0);
        return 1;
      }
      tf_old = atomic_load_explicit(&page->xthread_free, memory_order_relaxed);
    }

    (mi_tf_block(tf_old) == 0) ? ((void) 0) : (_mi_assert_fail("mi_tf_block(tf_old)==NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 909, __func__));
    tf_new = mi_tf_create(0, 0);
  }
  while (!atomic_compare_exchange_weak_explicit(&page->xthread_free, &tf_old, tf_new, memory_order_acq_rel, memory_order_acquire));
  return 0;
}

inline static bool mi_is_in_same_page(const void *p, const void *q)
{
  mi_page_t *page = _mi_ptr_page(p);
  return mi_page_contains_address(page, q);
}

inline static void *mi_ptr_decode(const void *null, const mi_encoded_t x, const uintptr_t *keys)
{
  void *p = (void *) (mi_rotr(x - keys[0], keys[0]) ^ keys[1]);
  return (p == null) ? (0) : (p);
}

inline static mi_encoded_t mi_ptr_encode(const void *null, const void *p, const uintptr_t *keys)
{
  uintptr_t x = (uintptr_t) ((p == 0) ? (null) : (p));
  return mi_rotl(x ^ keys[1], keys[0]) + keys[0];
}

inline static uint32_t mi_ptr_encode_canary(const void *null, const void *p, const uintptr_t *keys)
{
  const uint32_t x = (uint32_t) mi_ptr_encode(null, p, keys);
  return x & 0xFFFFFF00;
}

inline static mi_block_t *mi_block_nextx(const void *null, const mi_block_t *block, const uintptr_t *keys)
{
  ;
  mi_block_t *next;
  unsigned int next_idx = 0;
  next_idx = (mi_block_t *) mi_ptr_decode(null, block->next_idx, keys);
  ;
  return next;
}

inline static void mi_block_set_nextx(const void *null, mi_block_t *block, const mi_block_t *next, const uintptr_t *keys)
{
  ;
  block->next = mi_ptr_encode(null, next, keys);
  ;
}

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

inline static void mi_block_set_next(const mi_page_t *page, mi_block_t *block, const mi_block_t *next)
{
  mi_block_set_nextx(page, block, next, page->keys);
}

inline static size_t mi_slice_count_of_size(size_t size)
{
  return _mi_divide_up(size, 1UL << (13 + 3));
}

inline static size_t mi_size_of_slices(size_t bcount)
{
  return bcount * (1UL << (13 + 3));
}

inline static mi_memid_t _mi_memid_create(mi_memkind_t memkind)
{
  mi_memid_t memid;
  memset(&memid, 0, sizeof(memid));
  memid.memkind = memkind;
  return memid;
}

inline static mi_memid_t _mi_memid_none(void)
{
  return _mi_memid_create(MI_MEM_NONE);
}

inline static mi_memid_t _mi_memid_create_os(void *base, size_t size, bool committed, bool is_zero, bool is_large)
{
  mi_memid_t memid = _mi_memid_create(MI_MEM_OS);
  memid.mem.os.base = base;
  memid.mem.os.size = size;
  memid.initially_committed = committed;
  memid.initially_zero = is_zero;
  memid.is_pinned = is_large;
  return memid;
}

inline static mi_memid_t _mi_memid_create_meta(void *mpage, size_t block_idx, size_t block_count)
{
  mi_memid_t memid = _mi_memid_create(MI_MEM_META);
  memid.mem.meta.meta_page = mpage;
  memid.mem.meta.block_index = (uint32_t) block_idx;
  memid.mem.meta.block_count = (uint32_t) block_count;
  memid.initially_committed = 1;
  memid.initially_zero = 1;
  memid.is_pinned = 1;
  return memid;
}

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

inline static void _mi_memcpy(void *dst, const void *src, size_t n)
{
  memcpy(dst, src, n);
}

inline static void _mi_memset(void *dst, int val, size_t n)
{
  memset(dst, val, n);
}

inline static void _mi_memcpy_aligned(void *dst, const void *src, size_t n)
{
  (((((uintptr_t) dst) % (1 << 3)) == 0) && ((((uintptr_t) src) % (1 << 3)) == 0)) ? ((void) 0) : (_mi_assert_fail("((uintptr_t)dst % MI_INTPTR_SIZE == 0) && ((uintptr_t)src % MI_INTPTR_SIZE == 0)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 1178, __func__));
  void *adst = __builtin_assume_aligned(dst, 1 << 3);
  const void *asrc = __builtin_assume_aligned(src, 1 << 3);
  _mi_memcpy(adst, asrc, n);
}

inline static void _mi_memset_aligned(void *dst, int val, size_t n)
{
  ((((uintptr_t) dst) % (1 << 3)) == 0) ? ((void) 0) : (_mi_assert_fail("(uintptr_t)dst % MI_INTPTR_SIZE == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 1185, __func__));
  void *adst = __builtin_assume_aligned(dst, 1 << 3);
  _mi_memset(adst, val, n);
}

inline static void _mi_memzero(void *dst, size_t n)
{
  _mi_memset(dst, 0, n);
}

inline static void _mi_memzero_aligned(void *dst, size_t n)
{
  _mi_memset_aligned(dst, 0, n);
}

typedef size_t mi_bfield_t;
typedef struct mi_bchunk_s
{
  _Atomic mi_bfield_t bfields[(1 << (6 + 3)) / (1 << (3 + 3))];
} mi_bchunk_t;
typedef mi_bchunk_t mi_bchunkmap_t;
typedef struct mi_bitmap_s
{
  _Atomic size_t chunk_count;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 1];
  mi_bchunkmap_t chunkmap;
  mi_bchunk_t chunks[64];
} mi_bitmap_t;
inline static size_t mi_bitmap_chunk_count(const mi_bitmap_t *bitmap)
{
  return atomic_load_explicit(&((mi_bitmap_t *) bitmap)->chunk_count, memory_order_relaxed);
}

inline static size_t mi_bitmap_max_bits(const mi_bitmap_t *bitmap)
{
  return mi_bitmap_chunk_count(bitmap) * (1 << (6 + 3));
}

typedef bool mi_xset_t;
size_t mi_bitmap_size(size_t bit_count, size_t *chunk_count);
size_t mi_bitmap_init(mi_bitmap_t *bitmap, size_t bit_count, bool already_zero);
void mi_bitmap_unsafe_setN(mi_bitmap_t *bitmap, size_t idx, size_t n);
bool mi_bitmap_set(mi_bitmap_t *bitmap, size_t idx);
bool mi_bitmap_clear(mi_bitmap_t *bitmap, size_t idx);
bool mi_bitmap_setN(mi_bitmap_t *bitmap, size_t idx, size_t n, size_t *already_set);
bool mi_bitmap_clearN(mi_bitmap_t *bitmap, size_t idx, size_t n);
bool mi_bitmap_is_xsetN(mi_xset_t set, mi_bitmap_t *bitmap, size_t idx, size_t n);
inline static bool mi_bitmap_is_setN(mi_bitmap_t *bitmap, size_t idx, size_t n)
{
  return mi_bitmap_is_xsetN(1, bitmap, idx, n);
}

inline static bool mi_bitmap_is_clearN(mi_bitmap_t *bitmap, size_t idx, size_t n)
{
  return mi_bitmap_is_xsetN(0, bitmap, idx, n);
}

inline static bool mi_bitmap_is_set(mi_bitmap_t *bitmap, size_t idx)
{
  return mi_bitmap_is_setN(bitmap, idx, 1);
}

inline static bool mi_bitmap_is_clear(mi_bitmap_t *bitmap, size_t idx)
{
  return mi_bitmap_is_clearN(bitmap, idx, 1);
}

typedef bool mi_claim_fun_t(size_t slice_index, mi_arena_t *arena, mi_heaptag_t heap_tag, bool *keep_set);
bool mi_bitmap_try_find_and_claim(mi_bitmap_t *bitmap, size_t tseq, size_t *pidx, mi_claim_fun_t *claim, mi_arena_t *arena, mi_heaptag_t heap_tag);
void mi_bitmap_clear_once_set(mi_bitmap_t *bitmap, size_t idx);
bool mi_bitmap_bsr(mi_bitmap_t *bitmap, size_t *idx);
size_t mi_bitmap_popcount(mi_bitmap_t *bitmap);
typedef bool mi_forall_set_fun_t(size_t slice_index, size_t slice_count, mi_arena_t *arena, void *arg2);
bool _mi_bitmap_forall_set(mi_bitmap_t *bitmap, mi_forall_set_fun_t *visit, mi_arena_t *arena, void *arg);
bool _mi_bitmap_forall_setc_ranges(mi_bitmap_t *bitmap, mi_forall_set_fun_t *visit, mi_arena_t *arena, void *arg);
size_t mi_bitmap_popcountN(mi_bitmap_t *bitmap, size_t idx, size_t n);
inline static mi_chunkbin_t mi_chunkbin_inc(mi_chunkbin_t bbin)
{
  (bbin < MI_CBIN_COUNT) ? ((void) 0) : (_mi_assert_fail("bbin < MI_CBIN_COUNT", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.h", 234, __func__));
  return (mi_chunkbin_t) (((int) bbin) + 1);
}

inline static mi_chunkbin_t mi_chunkbin_dec(mi_chunkbin_t bbin)
{
  (bbin > MI_CBIN_NONE) ? ((void) 0) : (_mi_assert_fail("bbin > MI_CBIN_NONE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.h", 239, __func__));
  return (mi_chunkbin_t) (((int) bbin) - 1);
}

inline static mi_chunkbin_t mi_chunkbin_of(size_t slice_count)
{
  if (slice_count == 1)
  {
    return MI_CBIN_SMALL;
  }
  if (slice_count == 8)
  {
    return MI_CBIN_MEDIUM;
  }
  return MI_CBIN_OTHER;
}

typedef struct mi_bbitmap_s
{
  _Atomic size_t chunk_count;
  _Atomic size_t chunk_max_accessed;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 2];
  mi_bchunkmap_t chunkmap;
  mi_bchunkmap_t chunkmap_bins[MI_CBIN_COUNT - 1];
  mi_bchunk_t chunks[64];
} mi_bbitmap_t;
inline static size_t mi_bbitmap_chunk_count(const mi_bbitmap_t *bbitmap)
{
  return atomic_load_explicit(&((mi_bbitmap_t *) bbitmap)->chunk_count, memory_order_relaxed);
}

inline static size_t mi_bbitmap_max_bits(const mi_bbitmap_t *bbitmap)
{
  return mi_bbitmap_chunk_count(bbitmap) * (1 << (6 + 3));
}

mi_chunkbin_t mi_bbitmap_debug_get_bin(const mi_bchunk_t *chunkmap_bins, size_t chunk_idx);
size_t mi_bbitmap_size(size_t bit_count, size_t *chunk_count);
size_t mi_bbitmap_init(mi_bbitmap_t *bbitmap, size_t bit_count, bool already_zero);
void mi_bbitmap_unsafe_setN(mi_bbitmap_t *bbitmap, size_t idx, size_t n);
bool mi_bbitmap_setN(mi_bbitmap_t *bbitmap, size_t idx, size_t n);
bool mi_bbitmap_is_xsetN(mi_xset_t set, mi_bbitmap_t *bbitmap, size_t idx, size_t n);
inline static bool mi_bbitmap_is_setN(mi_bbitmap_t *bbitmap, size_t idx, size_t n)
{
  return mi_bbitmap_is_xsetN(1, bbitmap, idx, n);
}

inline static bool mi_bbitmap_is_clearN(mi_bbitmap_t *bbitmap, size_t idx, size_t n)
{
  return mi_bbitmap_is_xsetN(0, bbitmap, idx, n);
}

bool mi_bbitmap_try_clearN(mi_bbitmap_t *bbitmap, size_t idx, size_t n);
bool mi_bbitmap_try_find_and_clear(mi_bbitmap_t *bbitmap, size_t tseq, size_t *pidx);
bool mi_bbitmap_try_find_and_clear8(mi_bbitmap_t *bbitmap, size_t tseq, size_t *pidx);
bool mi_bbitmap_try_find_and_clearNX(mi_bbitmap_t *bbitmap, size_t n, size_t tseq, size_t *pidx);
bool mi_bbitmap_try_find_and_clearN_(mi_bbitmap_t *bbitmap, size_t n, size_t tseq, size_t *pidx);
inline static bool mi_bbitmap_try_find_and_clearN(mi_bbitmap_t *bbitmap, size_t n, size_t tseq, size_t *pidx)
{
  if (n == 1)
  {
    return mi_bbitmap_try_find_and_clear(bbitmap, tseq, pidx);
  }
  if (n == 8)
  {
    return mi_bbitmap_try_find_and_clear8(bbitmap, tseq, pidx);
  }
  if ((n == 0) || (n > (1 << (6 + 3))))
  {
    return 0;
  }
  if (n <= (1 << (3 + 3)))
  {
    return mi_bbitmap_try_find_and_clearNX(bbitmap, tseq, n, pidx);
  }
  return mi_bbitmap_try_find_and_clearN_(bbitmap, tseq, n, pidx);
}

static void mi_page_map_cannot_commit(void)
{
  _mi_warning_message("unable to commit the allocation page-map on-demand\n");
}

_Atomic mi_submap_t *_mi_page_map;
static size_t mi_page_map_count;
static void *mi_page_map_max_address;
static mi_memid_t mi_page_map_memid;
static _Atomic mi_bfield_t mi_page_map_commit;
inline static bool mi_page_map_is_committed(size_t idx, size_t *pbit_idx)
{
  mi_bfield_t commit = atomic_load_explicit(&mi_page_map_commit, memory_order_relaxed);
  const size_t bit_idx = idx / ((1UL << ((48 - 13) - (13 + 3))) / (1 << (3 + 3)));
  (bit_idx < (1 << (3 + 3))) ? ((void) 0) : (_mi_assert_fail("bit_idx < MI_BFIELD_BITS", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 209, __func__));
  if (pbit_idx != 0)
  {
    *pbit_idx = bit_idx;
  }
  return (commit & (1UL << bit_idx)) != 0;
}

static bool mi_page_map_ensure_committed(size_t idx, mi_submap_t *submap)
{
  ((submap != 0) && ((*submap) == 0)) ? ((void) 0) : (_mi_assert_fail("submap!=NULL && *submap==NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 215, __func__));
  size_t bit_idx;
  if (__builtin_expect(!(!(!mi_page_map_is_committed(idx, &bit_idx))), 0))
  {
    uint8_t *start = (uint8_t *) (&_mi_page_map[bit_idx * ((1UL << ((48 - 13) - (13 + 3))) / (1 << (3 + 3)))]);
    if (!_mi_os_commit(start, ((1UL << ((48 - 13) - (13 + 3))) / (1 << (3 + 3))) * (sizeof(mi_submap_t)), 0))
    {
      mi_page_map_cannot_commit();
      return 0;
    }
    atomic_fetch_or_explicit(&mi_page_map_commit, 1UL << bit_idx, memory_order_acq_rel);
  }
  *submap = atomic_load_explicit(&_mi_page_map[idx], memory_order_acquire);
  return 1;
}

bool _mi_page_map_init(void)
{
  size_t vbits = (size_t) mi_option_get_clamp(mi_option_max_vabits, 0, (1 << 3) * 8);
  if (vbits == 0)
  {
    vbits = _mi_os_virtual_address_bits();
  }
  (48 >= vbits) ? ((void) 0) : (_mi_assert_fail("MI_MAX_VABITS >= vbits", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 240, __func__));
  mi_page_map_max_address = (void *) ((vbits >= ((1 << 3) * 8)) ? ((SIZE_MAX - (1UL << (13 + 3))) + 1) : (1UL << vbits));
  mi_page_map_count = 1UL << ((vbits - 13) - (13 + 3));
  (mi_page_map_count <= (1UL << ((48 - 13) - (13 + 3)))) ? ((void) 0) : (_mi_assert_fail("mi_page_map_count <= MI_PAGE_MAP_COUNT", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 243, __func__));
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
  (_mi_ptr_page(0) == 0) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(NULL)==NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 283, __func__));
  return 1;
}

void _mi_page_map_unsafe_destroy(mi_subproc_t *subproc)
{
  (subproc != 0) ? ((void) 0) : (_mi_assert_fail("subproc != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 289, __func__));
  (_mi_page_map != 0) ? ((void) 0) : (_mi_assert_fail("_mi_page_map != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 290, __func__));
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

static bool mi_page_map_ensure_submap_at(size_t idx, mi_submap_t *submap)
{
  ((submap != 0) && ((*submap) == 0)) ? ((void) 0) : (_mi_assert_fail("submap!=NULL && *submap==NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 313, __func__));
  mi_submap_t sub = 0;
  if (!mi_page_map_ensure_committed(idx, &sub))
  {
    return 0;
  }
  if (__builtin_expect(!(!(sub == 0)), 0))
  {
    mi_memid_t memid;
    const size_t submap_size = (1UL << 13) * (sizeof(mi_page_t *));
    sub = (mi_submap_t) _mi_os_zalloc(submap_size, &memid);
    if (sub == 0)
    {
      _mi_warning_message("internal error: unable to extend the page map\n");
      return 0;
    }
    mi_submap_t expect = 0;
    if (!atomic_compare_exchange_strong_explicit(&_mi_page_map[idx], &expect, sub, memory_order_acq_rel, memory_order_acquire))
    {
      _mi_os_free(sub, submap_size, memid);
      sub = expect;
    }
  }
  (sub != 0) ? ((void) 0) : (_mi_assert_fail("sub!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 334, __func__));
  *submap = sub;
  return 1;
}

static bool mi_page_map_set_range_prim(mi_page_t *page, size_t idx, size_t sub_idx, size_t slice_count)
{
  while (slice_count > 0)
  {
    mi_submap_t sub = 0;
    if (!mi_page_map_ensure_submap_at(idx, &sub))
    {
      return 0;
    }
    ;
    (sub != 0) ? ((void) 0) : (_mi_assert_fail("sub!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 346, __func__));
    while ((slice_count > 0) && (sub_idx < (1UL << 13)))
    {
      sub[sub_idx] = page;
      slice_count -= 1;
      sub_idx += 1;
    }

    idx += 1;
    sub_idx = 0;
  }

  return 1;
}

static bool mi_page_map_set_range(mi_page_t *page, size_t idx, size_t sub_idx, size_t slice_count)
{
  if (__builtin_expect(!(!(!mi_page_map_set_range_prim(page, idx, sub_idx, slice_count))), 0))
  {
    if (page != 0)
    {
      mi_page_map_set_range_prim(0, idx, sub_idx, slice_count);
    }
    return 0;
  }
  return 1;
}

static size_t mi_page_map_get_idx(mi_page_t *page, size_t *sub_idx, size_t *slice_count)
{
  size_t page_size;
  uint8_t *page_start = mi_page_area(page, &page_size);
  if (page_size > ((1 << 3) * (8 * (1 * (1UL << (13 + 3))))))
  {
    page_size = ((1 << 3) * (8 * (1 * (1UL << (13 + 3))))) - (1UL << (13 + 3));
  }
  *slice_count = mi_slice_count_of_size(page_size) + ((page_start - ((uint8_t *) page)) / (1UL << (13 + 3)));
  return _mi_page_map_index(page, sub_idx);
}

bool _mi_page_map_register(mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 379, __func__));
  (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 380, __func__));
  (_mi_page_map != 0) ? ((void) 0) : (_mi_assert_fail("_mi_page_map != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 381, __func__));
  if (__builtin_expect(!(!(_mi_page_map == 0)), 0))
  {
    if (!_mi_page_map_init())
    {
      return 0;
    }
  }
  (_mi_page_map != 0) ? ((void) 0) : (_mi_assert_fail("_mi_page_map!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 385, __func__));
  size_t slice_count;
  size_t sub_idx;
  const size_t idx = mi_page_map_get_idx(page, &sub_idx, &slice_count);
  return mi_page_map_set_range(page, idx, sub_idx, slice_count);
}

void _mi_page_map_unregister(mi_page_t *page)
{
  (_mi_page_map != 0) ? ((void) 0) : (_mi_assert_fail("_mi_page_map != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 393, __func__));
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 394, __func__));
  (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-map.c", 395, __func__));
  if (__builtin_expect(!(!(_mi_page_map == 0)), 0))
  {
    return;
  }
  size_t slice_count;
  size_t sub_idx;
  const size_t idx = mi_page_map_get_idx(page, &sub_idx, &slice_count);
  mi_page_map_set_range(0, idx, sub_idx, slice_count);
}

void _mi_page_map_unregister_range(void *start, size_t size)
{
  if (__builtin_expect(!(!(_mi_page_map == 0)), 0))
  {
    return;
  }
  const size_t slice_count = _mi_divide_up(size, 1UL << (13 + 3));
  size_t sub_idx;
  const uintptr_t idx = _mi_page_map_index(start, &sub_idx);
  mi_page_map_set_range(0, idx, sub_idx, slice_count);
}

mi_page_t *_mi_safe_ptr_page(const void *p)
{
  if (p == 0)
  {
    return 0;
  }
  if (__builtin_expect(!(!(p >= mi_page_map_max_address)), 0))
  {
    return 0;
  }
  size_t sub_idx;
  const size_t idx = _mi_page_map_index(p, &sub_idx);
  if (__builtin_expect(!(!(!mi_page_map_is_committed(idx, 0))), 0))
  {
    return 0;
  }
  mi_page_t ** const sub = _mi_page_map[idx];
  if (__builtin_expect(!(!(sub == 0)), 0))
  {
    return 0;
  }
  return sub[sub_idx];
}

bool mi_is_in_heap_region(const void *p)
{
  return _mi_safe_ptr_page(p) != 0;
}

