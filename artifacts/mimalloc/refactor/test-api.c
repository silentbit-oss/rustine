#include <assert.h>
#include <atomic.h>
#include <bits.h>
#include <errno.h>
#include <limits.h>
#include <mimalloc-stats.h>
#include <mimalloc.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <test-api.c>
#include <testhelper.h>
#include <types.h>
#pragma GCC diagnostic ignored "-Walloc-size-larger-than="

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
static int ok = 0;
static int failed = 0;
static bool check_result(bool result, const char *testname, const char *fname, long lineno)
{
  if (!result)
  {
    failed += 1;
    fprintf(stderr, "\n  FAILED: %s: %s:%ld\n", testname, fname, lineno);
  }
  else
  {
    ok += 1;
    fprintf(stderr, "ok.\n");
  }
  return 1;
}

inline static int print_test_summary(void)
{
  fprintf(stderr, "\n\n---------------------------------------------\nsucceeded: %i\nfailed   : %i\n\n", ok, failed);
  return failed;
}

bool test_heap1(void);
bool test_heap2(void);
bool test_stl_allocator1(void);
bool test_stl_allocator2(void);
bool test_stl_heap_allocator1(void);
bool test_stl_heap_allocator2(void);
bool test_stl_heap_allocator3(void);
bool test_stl_heap_allocator4(void);
bool mem_is_zero(uint8_t *p, size_t size)
{
  if (p == 0)
  {
    return 0;
  }
  for (size_t i = 0; i < size; i += 1)
  {
    if (p[i] != 0)
    {
      return 0;
    }
  }

  return 1;
}

int main(void)
{
  mi_option_disable(mi_option_verbose);
  fprintf(stderr, "test: %s...  ", "malloc-aligned9a");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned9a", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 68))
  {
    void *p = mi_zalloc_aligned(1024 * 1024, 2);
    unsigned int p_idx = 0;
    mi_free(p);
    p_idx = mi_zalloc_aligned(1024 * 1024, 2);
    mi_free(p);
    result = 1;
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-zero");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-zero", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 81))
  {
    void *p = mi_malloc(0);
    unsigned int p_idx = 0;
    result = (&p[p_idx]) != 0;
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-nomem1");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-nomem1", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 86))
  {
    result = mi_malloc(((size_t) PTRDIFF_MAX) + ((size_t) 1)) == 0;
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-free-null");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-free-null", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 89))
  {
    mi_free(0);
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-free-invalid-low");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-free-invalid-low", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 93))
  {
    mi_free((void *) 0x0000000003990080UL);
  }

  ;
  fprintf(stderr, "test: %s...  ", "calloc-overflow");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "calloc-overflow", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 97))
  {
    result = mi_calloc((size_t) (&mi_calloc), SIZE_MAX / 1000) == 0;
  }

  ;
  fprintf(stderr, "test: %s...  ", "calloc0");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "calloc0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 101))
  {
    void *p = mi_calloc(0, 1000);
    unsigned int p_idx = 0;
    result = mi_usable_size(p) <= 16;
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 106))
  {
    void *p = mi_malloc(67108872);
    unsigned int p_idx = 0;
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "posix_memalign1");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "posix_memalign1", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 114))
  {
    void *p = &(&p[p_idx]);
    unsigned int p_idx = 0;
    int err = mi_posix_memalign(&(&p[p_idx]), sizeof(void *), 32);
    result = ((err == 0) && ((((uintptr_t) p) % (sizeof(void *))) == 0)) || ((&p[p_idx]) == (&(&p[p_idx])));
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "posix_memalign_no_align");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "posix_memalign_no_align", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 120))
  {
    void *p = &(&p[p_idx]);
    unsigned int p_idx = 0;
    int err = mi_posix_memalign(&(&p[p_idx]), 3, 32);
    result = (err == 22) && ((&p[p_idx]) == (&(&p[p_idx])));
  }

  ;
  fprintf(stderr, "test: %s...  ", "posix_memalign_zero");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "posix_memalign_zero", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 125))
  {
    void *p = &(&p[p_idx]);
    unsigned int p_idx = 0;
    int err = mi_posix_memalign(&(&p[p_idx]), sizeof(void *), 0);
    mi_free(p);
    result = err == 0;
  }

  ;
  fprintf(stderr, "test: %s...  ", "posix_memalign_nopow2");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "posix_memalign_nopow2", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 131))
  {
    void *p = &(&p[p_idx]);
    unsigned int p_idx = 0;
    int err = mi_posix_memalign(&(&p[p_idx]), 3 * (sizeof(void *)), 32);
    result = (err == 22) && ((&p[p_idx]) == (&(&p[p_idx])));
  }

  ;
  fprintf(stderr, "test: %s...  ", "posix_memalign_nomem");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "posix_memalign_nomem", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 136))
  {
    void *p = &(&p[p_idx]);
    unsigned int p_idx = 0;
    int err = mi_posix_memalign(&(&p[p_idx]), sizeof(void *), SIZE_MAX);
    result = (err == 12) && ((&p[p_idx]) == (&(&p[p_idx])));
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-aligned1");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned1", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 145))
  {
    void *p = mi_malloc_aligned(32, 32);
    unsigned int p_idx = 0;
    result = ((&p[p_idx]) != 0) && ((((uintptr_t) p) % 32) == 0);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-aligned2");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned2", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 148))
  {
    void *p = mi_malloc_aligned(48, 32);
    unsigned int p_idx = 0;
    result = ((&p[p_idx]) != 0) && ((((uintptr_t) p) % 32) == 0);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-aligned3");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned3", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 151))
  {
    void *p1 = mi_malloc_aligned(48, 32);
    bool result1 = (p1 != 0) && ((((uintptr_t) p1) % 32) == 0);
    void *p2 = mi_malloc_aligned(48, 32);
    bool result2 = (p2 != 0) && ((((uintptr_t) p2) % 32) == 0);
    mi_free(p2);
    mi_free(p1);
    result = result1 && result2;
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-aligned4");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned4", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 158))
  {
    void *p;
    unsigned int p_idx = 0;
    bool ok = 1;
    for (int i = 0; (i < 8) && ok; i += 1)
    {
      p_idx = mi_malloc_aligned(8, 16);
      ok = ((&p[p_idx]) != 0) && ((((uintptr_t) p) % 16) == 0);
      mi_free(p);
    }

    result = ok;
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-aligned5");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned5", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 167))
  {
    void *p = mi_malloc_aligned(4097, 4096);
    unsigned int p_idx = 0;
    size_t usable = mi_usable_size(p);
    result = (usable >= 4097) && (usable < 16000);
    fprintf(stderr, "malloc_aligned5: usable size: %zi.  ", usable);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-aligned7");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned7", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 193))
  {
    void *p = mi_malloc_aligned(1024, 1UL << (13 + 3));
    unsigned int p_idx = 0;
    mi_free(p);
    result = (((uintptr_t) p) % (1UL << (13 + 3))) == 0;
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-aligned8");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned8", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 198))
  {
    bool ok = 1;
    for (int i = 0; (i < 5) && ok; i += 1)
    {
      int n = 1 << i;
      void *p = mi_malloc_aligned(1024, n * (1UL << (13 + 3)));
      unsigned int p_idx = 0;
      ok = (((uintptr_t) p) % (n * (1UL << (13 + 3)))) == 0;
      mi_free(p);
    }

    result = ok;
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-aligned9");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned9", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 208))
  {
    helper_main_2(&result, &p_idx, &result, &p_idx, &result, &result, &result, &result, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &result, &result, &p_idx, &result, &p_idx, &result, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &result, &result, &result, &result, &result, &result, &result, &result);
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-aligned10");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned10", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 231))
  {
    bool ok = 1;
    void *p[10 + 1];
    int align;
    int j;
    for (j = 0, align = 1; (j <= 10) && ok; align *= 2, j += 1)
    {
      p[j + p_idx] = mi_malloc_aligned(43 + align, align);
      ok = (((uintptr_t) p[j + p_idx]) % align) == 0;
    }

    for (; j > 0; j -= 1)
    {
      mi_free(p[(j - 1) + p_idx]);
    }

    result = ok;
  }

  fprintf(stderr, "test: %s...  ", "malloc_aligned11");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc_aligned11", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 245))
  {
    mi_heap_t *heap = mi_heap_new();
    void *p = mi_heap_malloc_aligned(heap, 33554426, 8);
    unsigned int p_idx = 0;
    result = mi_heap_contains_block(heap, p);
    mi_heap_destroy(heap);
  }

  fprintf(stderr, "test: %s...  ", "mimalloc-aligned12");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "mimalloc-aligned12", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 251))
  {
    void *p = mi_malloc_aligned(0x100, 0x100);
    unsigned int p_idx = 0;
    result = (((uintptr_t) p) % 0x100) == 0;
    mi_free(p);
  }

  fprintf(stderr, "test: %s...  ", "mimalloc-aligned13");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "mimalloc-aligned13", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 256))
  {
    helper_main_1(&result, &p_idx, &result, &p_idx, &result, &result, &result, &result, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &result, &result, &p_idx, &result, &p_idx, &result, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &p_idx, &result, &result, &result, &result, &result, &result, &result, &result, &result);
  }

  fprintf(stderr, "test: %s...  ", "malloc-aligned-at1");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned-at1", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 278))
  {
    void *p = mi_malloc_aligned_at(48, 32, 0);
    unsigned int p_idx = 0;
    result = ((&p[p_idx]) != 0) && (((((uintptr_t) p) + 0) % 32) == 0);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-aligned-at2");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned-at2", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 281))
  {
    void *p = mi_malloc_aligned_at(50, 32, 8);
    unsigned int p_idx = 0;
    result = ((&p[p_idx]) != 0) && (((((uintptr_t) p) + 8) % 32) == 0);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "memalign1");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "memalign1", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 284))
  {
    void *p;
    unsigned int p_idx = 0;
    bool ok = 1;
    for (int i = 0; (i < 8) && ok; i += 1)
    {
      p_idx = mi_memalign(16, 8);
      ok = ((&p[p_idx]) != 0) && ((((uintptr_t) p) % 16) == 0);
      mi_free(p);
    }

    result = ok;
  }

  ;
  fprintf(stderr, "test: %s...  ", "zalloc-aligned-small1");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zalloc-aligned-small1", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 293))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_zalloc_aligned(zalloc_size, 16 * 2);
    unsigned int p_idx = 0;
    result = mem_is_zero(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "rezalloc_aligned-small1");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "rezalloc_aligned-small1", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 299))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_zalloc_aligned(zalloc_size, 16 * 2);
    unsigned int p_idx = 0;
    result = mem_is_zero(p, zalloc_size);
    zalloc_size *= 3;
    p_idx = (uint8_t *) mi_rezalloc_aligned(p_idx, zalloc_size, 16 * 2);
    result = result && mem_is_zero(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "realloc-null");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "realloc-null", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 312))
  {
    void *p = mi_realloc(0, 4);
    unsigned int p_idx = 0;
    result = (&p[p_idx]) != 0;
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "realloc-null-sizezero");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "realloc-null-sizezero", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 318))
  {
    void *p = mi_realloc(0, 0);
    unsigned int p_idx = 0;
    result = (&p[p_idx]) != 0;
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "realloc-sizezero");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "realloc-sizezero", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 324))
  {
    void *p = mi_malloc(4);
    unsigned int p_idx = 0;
    void *q = mi_realloc(p, 0);
    result = q != 0;
    mi_free(q);
  }

  ;
  fprintf(stderr, "test: %s...  ", "reallocarray-null-sizezero");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "reallocarray-null-sizezero", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 331))
  {
    void *p = mi_reallocarray(0, 0, 16);
    unsigned int p_idx = 0;
    result = ((&p[p_idx]) != 0) && (errno == 0);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "heap_destroy");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "heap_destroy", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 340))
  {
    result = test_heap1();
  }

  ;
  fprintf(stderr, "test: %s...  ", "heap_delete");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "heap_delete", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 341))
  {
    result = test_heap2();
  }

  ;
  fprintf(stderr, "test: %s...  ", "realpath");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "realpath", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 349))
  {
    char *s = mi_realpath(".", 0);
    mi_free(s);
  }

  ;
  fprintf(stderr, "test: %s...  ", "stl_allocator1");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "stl_allocator1", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 356))
  {
    result = test_stl_allocator1();
  }

  ;
  fprintf(stderr, "test: %s...  ", "stl_allocator2");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "stl_allocator2", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 357))
  {
    result = test_stl_allocator2();
  }

  ;
  fprintf(stderr, "test: %s...  ", "stl_heap_allocator1");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "stl_heap_allocator1", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 359))
  {
    result = test_stl_heap_allocator1();
  }

  ;
  fprintf(stderr, "test: %s...  ", "stl_heap_allocator2");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "stl_heap_allocator2", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 360))
  {
    result = test_stl_heap_allocator2();
  }

  ;
  fprintf(stderr, "test: %s...  ", "stl_heap_allocator3");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "stl_heap_allocator3", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 361))
  {
    result = test_stl_heap_allocator3();
  }

  ;
  fprintf(stderr, "test: %s...  ", "stl_heap_allocator4");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "stl_heap_allocator4", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 362))
  {
    result = test_stl_heap_allocator4();
  }

  ;
  return print_test_summary();
}

bool test_heap1(void)
{
  mi_heap_t *heap = mi_heap_new();
  int *p1 = (int *) mi_heap_malloc(heap, sizeof(int));
  int *p2 = (int *) mi_heap_malloc(heap, sizeof(int));
  *p1 = (*p2 = 43);
  mi_heap_destroy(heap);
  return 1;
}

bool test_heap2(void)
{
  mi_heap_t *heap = mi_heap_new();
  int *p1 = (int *) mi_heap_malloc(heap, sizeof(int));
  int *p2 = (int *) mi_heap_malloc(heap, sizeof(int));
  mi_heap_delete(heap);
  *p1 = 42;
  mi_free(p1);
  mi_free(p2);
  return 1;
}

bool test_stl_allocator1(void)
{
  return 1;
}

struct some_struct
{
  int i;
  int j;
  double z;
};
bool test_stl_allocator2(void)
{
  return 1;
}

bool test_stl_heap_allocator1(void)
{
  return 1;
}

bool test_stl_heap_allocator2(void)
{
  return 1;
}

bool test_stl_heap_allocator3(void)
{
  return 1;
}

bool test_stl_heap_allocator4(void)
{
  return 1;
}

#pragma GCC diagnostic ignored "-Walloc-size-larger-than="

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
static int ok = 0;
static int failed = 0;
static bool check_result(bool result, const char *testname, const char *fname, long lineno)
{
  if (!result)
  {
    failed += 1;
    fprintf(stderr, "\n  FAILED: %s: %s:%ld\n", testname, fname, lineno);
  }
  else
  {
    ok += 1;
    fprintf(stderr, "ok.\n");
  }
  return 1;
}

inline static int print_test_summary(void)
{
  fprintf(stderr, "\n\n---------------------------------------------\nsucceeded: %i\nfailed   : %i\n\n", ok, failed);
  return failed;
}

bool test_heap1(void);
bool test_heap2(void);
bool test_stl_allocator1(void);
bool test_stl_allocator2(void);
bool test_stl_heap_allocator1(void);
bool test_stl_heap_allocator2(void);
bool test_stl_heap_allocator3(void);
bool test_stl_heap_allocator4(void);
bool mem_is_zero(uint8_t *p, size_t size)
{
  if (p == 0)
  {
    return 0;
  }
  for (size_t i = 0; i < size; i += 1)
  {
    if (p[i] != 0)
    {
      return 0;
    }
  }

  return 1;
}

int main(void)
{
  mi_option_disable(mi_option_verbose);
  fprintf(stderr, "test: %s...  ", "malloc-aligned9a");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned9a", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 68))
  {
    void *p = mi_zalloc_aligned(1024 * 1024, 2);
    unsigned int p_idx = 0;
    mi_free(p);
    p_idx = mi_zalloc_aligned(1024 * 1024, 2);
    mi_free(p);
    result = 1;
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-zero");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-zero", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 81))
  {
    void *p = mi_malloc(0);
    unsigned int p_idx = 0;
    result = (&p[p_idx]) != 0;
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-nomem1");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-nomem1", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 86))
  {
    result = mi_malloc(((size_t) PTRDIFF_MAX) + ((size_t) 1)) == 0;
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-free-null");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-free-null", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 89))
  {
    mi_free(0);
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-free-invalid-low");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-free-invalid-low", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 93))
  {
    mi_free((void *) 0x0000000003990080UL);
  }

  ;
  fprintf(stderr, "test: %s...  ", "calloc-overflow");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "calloc-overflow", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 97))
  {
    result = mi_calloc((size_t) (&mi_calloc), SIZE_MAX / 1000) == 0;
  }

  ;
  fprintf(stderr, "test: %s...  ", "calloc0");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "calloc0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 101))
  {
    void *p = mi_calloc(0, 1000);
    unsigned int p_idx = 0;
    result = mi_usable_size(p) <= 16;
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 106))
  {
    void *p = mi_malloc(67108872);
    unsigned int p_idx = 0;
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "posix_memalign1");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "posix_memalign1", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 114))
  {
    void *p = &(&p[p_idx]);
    unsigned int p_idx = 0;
    int err = mi_posix_memalign(&(&p[p_idx]), sizeof(void *), 32);
    result = ((err == 0) && ((((uintptr_t) p) % (sizeof(void *))) == 0)) || ((&p[p_idx]) == (&(&p[p_idx])));
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "posix_memalign_no_align");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "posix_memalign_no_align", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 120))
  {
    void *p = &(&p[p_idx]);
    unsigned int p_idx = 0;
    int err = mi_posix_memalign(&(&p[p_idx]), 3, 32);
    result = (err == 22) && ((&p[p_idx]) == (&(&p[p_idx])));
  }

  ;
  fprintf(stderr, "test: %s...  ", "posix_memalign_zero");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "posix_memalign_zero", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 125))
  {
    void *p = &(&p[p_idx]);
    unsigned int p_idx = 0;
    int err = mi_posix_memalign(&(&p[p_idx]), sizeof(void *), 0);
    mi_free(p);
    result = err == 0;
  }

  ;
  fprintf(stderr, "test: %s...  ", "posix_memalign_nopow2");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "posix_memalign_nopow2", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 131))
  {
    void *p = &(&p[p_idx]);
    unsigned int p_idx = 0;
    int err = mi_posix_memalign(&(&p[p_idx]), 3 * (sizeof(void *)), 32);
    result = (err == 22) && ((&p[p_idx]) == (&(&p[p_idx])));
  }

  ;
  fprintf(stderr, "test: %s...  ", "posix_memalign_nomem");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "posix_memalign_nomem", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 136))
  {
    void *p = &(&p[p_idx]);
    unsigned int p_idx = 0;
    int err = mi_posix_memalign(&(&p[p_idx]), sizeof(void *), SIZE_MAX);
    result = (err == 12) && ((&p[p_idx]) == (&(&p[p_idx])));
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-aligned1");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned1", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 145))
  {
    void *p = mi_malloc_aligned(32, 32);
    unsigned int p_idx = 0;
    result = ((&p[p_idx]) != 0) && ((((uintptr_t) p) % 32) == 0);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-aligned2");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned2", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 148))
  {
    void *p = mi_malloc_aligned(48, 32);
    unsigned int p_idx = 0;
    result = ((&p[p_idx]) != 0) && ((((uintptr_t) p) % 32) == 0);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-aligned3");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned3", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 151))
  {
    void *p1 = mi_malloc_aligned(48, 32);
    bool result1 = (p1 != 0) && ((((uintptr_t) p1) % 32) == 0);
    void *p2 = mi_malloc_aligned(48, 32);
    bool result2 = (p2 != 0) && ((((uintptr_t) p2) % 32) == 0);
    mi_free(p2);
    mi_free(p1);
    result = result1 && result2;
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-aligned4");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned4", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 158))
  {
    void *p;
    unsigned int p_idx = 0;
    bool ok = 1;
    for (int i = 0; (i < 8) && ok; i += 1)
    {
      p_idx = mi_malloc_aligned(8, 16);
      ok = ((&p[p_idx]) != 0) && ((((uintptr_t) p) % 16) == 0);
      mi_free(p);
    }

    result = ok;
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-aligned5");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned5", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 167))
  {
    void *p = mi_malloc_aligned(4097, 4096);
    unsigned int p_idx = 0;
    size_t usable = mi_usable_size(p);
    result = (usable >= 4097) && (usable < 16000);
    fprintf(stderr, "malloc_aligned5: usable size: %zi.  ", usable);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-aligned7");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned7", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 193))
  {
    void *p = mi_malloc_aligned(1024, 1UL << (13 + 3));
    unsigned int p_idx = 0;
    mi_free(p);
    result = (((uintptr_t) p) % (1UL << (13 + 3))) == 0;
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-aligned8");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned8", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 198))
  {
    bool ok = 1;
    for (int i = 0; (i < 5) && ok; i += 1)
    {
      int n = 1 << i;
      void *p = mi_malloc_aligned(1024, n * (1UL << (13 + 3)));
      unsigned int p_idx = 0;
      ok = (((uintptr_t) p) % (n * (1UL << (13 + 3)))) == 0;
      mi_free(p);
    }

    result = ok;
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-aligned9");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned9", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 208))
  {
    bool ok = 1;
    void *p[8];
    const int max_align_shift = 20;
    size_t sizes[8] = {8, 512, 1024 * 1024, 1UL << (13 + 3), (1UL << (13 + 3)) + 1, 2 * (1UL << (13 + 3)), 8 * (1UL << (13 + 3)), 0};
    for (int i = 0; (i < max_align_shift) && ok; i += 1)
    {
      int align = 1 << i;
      for (int j = 0; (j < 8) && ok; j += 1)
      {
        p[j + p_idx] = mi_zalloc_aligned(sizes[j], align);
        ok = (((uintptr_t) p[j + p_idx]) % align) == 0;
      }

      for (int j = 0; j < 8; j += 1)
      {
        mi_free(p[j + p_idx]);
      }

    }

    result = ok;
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-aligned10");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned10", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 231))
  {
    bool ok = 1;
    void *p[10 + 1];
    int align;
    int j;
    for (j = 0, align = 1; (j <= 10) && ok; align *= 2, j += 1)
    {
      p[j + p_idx] = mi_malloc_aligned(43 + align, align);
      ok = (((uintptr_t) p[j + p_idx]) % align) == 0;
    }

    for (; j > 0; j -= 1)
    {
      mi_free(p[(j - 1) + p_idx]);
    }

    result = ok;
  }

  fprintf(stderr, "test: %s...  ", "malloc_aligned11");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc_aligned11", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 245))
  {
    mi_heap_t *heap = mi_heap_new();
    void *p = mi_heap_malloc_aligned(heap, 33554426, 8);
    unsigned int p_idx = 0;
    result = mi_heap_contains_block(heap, p);
    mi_heap_destroy(heap);
  }

  fprintf(stderr, "test: %s...  ", "mimalloc-aligned12");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "mimalloc-aligned12", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 251))
  {
    void *p = mi_malloc_aligned(0x100, 0x100);
    unsigned int p_idx = 0;
    result = (((uintptr_t) p) % 0x100) == 0;
    mi_free(p);
  }

  fprintf(stderr, "test: %s...  ", "mimalloc-aligned13");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "mimalloc-aligned13", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 256))
  {
    bool ok = 1;
    for (size_t size = 1; (size <= ((128 * (sizeof(void *))) * 2)) && ok; size += 1)
    {
      for (size_t align = 1; (align <= size) && ok; align *= 2)
      {
        void *p[10];
        for (int i = 0; (i < 10) && ok; i += 1)
        {
          p[i + p_idx] = mi_malloc_aligned(size, align);
          ;
          ok = (p[i + p_idx] != 0) && ((((uintptr_t) p[i + p_idx]) % align) == 0);
        }

        for (int i = 0; (i < 10) && ok; i += 1)
        {
          mi_free(p[i + p_idx]);
        }

      }

    }

    result = ok;
  }

  fprintf(stderr, "test: %s...  ", "malloc-aligned-at1");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned-at1", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 278))
  {
    void *p = mi_malloc_aligned_at(48, 32, 0);
    unsigned int p_idx = 0;
    result = ((&p[p_idx]) != 0) && (((((uintptr_t) p) + 0) % 32) == 0);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "malloc-aligned-at2");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "malloc-aligned-at2", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 281))
  {
    void *p = mi_malloc_aligned_at(50, 32, 8);
    unsigned int p_idx = 0;
    result = ((&p[p_idx]) != 0) && (((((uintptr_t) p) + 8) % 32) == 0);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "memalign1");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "memalign1", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 284))
  {
    void *p;
    unsigned int p_idx = 0;
    bool ok = 1;
    for (int i = 0; (i < 8) && ok; i += 1)
    {
      p_idx = mi_memalign(16, 8);
      ok = ((&p[p_idx]) != 0) && ((((uintptr_t) p) % 16) == 0);
      mi_free(p);
    }

    result = ok;
  }

  ;
  fprintf(stderr, "test: %s...  ", "zalloc-aligned-small1");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zalloc-aligned-small1", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 293))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_zalloc_aligned(zalloc_size, 16 * 2);
    unsigned int p_idx = 0;
    result = mem_is_zero(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "rezalloc_aligned-small1");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "rezalloc_aligned-small1", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 299))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_zalloc_aligned(zalloc_size, 16 * 2);
    unsigned int p_idx = 0;
    result = mem_is_zero(p, zalloc_size);
    zalloc_size *= 3;
    p_idx = (uint8_t *) mi_rezalloc_aligned(p_idx, zalloc_size, 16 * 2);
    result = result && mem_is_zero(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "realloc-null");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "realloc-null", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 312))
  {
    void *p = mi_realloc(0, 4);
    unsigned int p_idx = 0;
    result = (&p[p_idx]) != 0;
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "realloc-null-sizezero");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "realloc-null-sizezero", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 318))
  {
    void *p = mi_realloc(0, 0);
    unsigned int p_idx = 0;
    result = (&p[p_idx]) != 0;
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "realloc-sizezero");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "realloc-sizezero", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 324))
  {
    void *p = mi_malloc(4);
    unsigned int p_idx = 0;
    void *q = mi_realloc(p, 0);
    result = q != 0;
    mi_free(q);
  }

  ;
  fprintf(stderr, "test: %s...  ", "reallocarray-null-sizezero");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "reallocarray-null-sizezero", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 331))
  {
    void *p = mi_reallocarray(0, 0, 16);
    unsigned int p_idx = 0;
    result = ((&p[p_idx]) != 0) && (errno == 0);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "heap_destroy");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "heap_destroy", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 340))
  {
    result = test_heap1();
  }

  ;
  fprintf(stderr, "test: %s...  ", "heap_delete");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "heap_delete", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 341))
  {
    result = test_heap2();
  }

  ;
  fprintf(stderr, "test: %s...  ", "realpath");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "realpath", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 349))
  {
    char *s = mi_realpath(".", 0);
    mi_free(s);
  }

  ;
  fprintf(stderr, "test: %s...  ", "stl_allocator1");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "stl_allocator1", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 356))
  {
    result = test_stl_allocator1();
  }

  ;
  fprintf(stderr, "test: %s...  ", "stl_allocator2");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "stl_allocator2", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 357))
  {
    result = test_stl_allocator2();
  }

  ;
  fprintf(stderr, "test: %s...  ", "stl_heap_allocator1");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "stl_heap_allocator1", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 359))
  {
    result = test_stl_heap_allocator1();
  }

  ;
  fprintf(stderr, "test: %s...  ", "stl_heap_allocator2");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "stl_heap_allocator2", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 360))
  {
    result = test_stl_heap_allocator2();
  }

  ;
  fprintf(stderr, "test: %s...  ", "stl_heap_allocator3");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "stl_heap_allocator3", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 361))
  {
    result = test_stl_heap_allocator3();
  }

  ;
  fprintf(stderr, "test: %s...  ", "stl_heap_allocator4");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "stl_heap_allocator4", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api.c", 362))
  {
    result = test_stl_heap_allocator4();
  }

  ;
  return print_test_summary();
}

bool test_heap1(void)
{
  mi_heap_t *heap = mi_heap_new();
  int *p1 = (int *) mi_heap_malloc(heap, sizeof(int));
  int *p2 = (int *) mi_heap_malloc(heap, sizeof(int));
  *p1 = (*p2 = 43);
  mi_heap_destroy(heap);
  return 1;
}

bool test_heap2(void)
{
  mi_heap_t *heap = mi_heap_new();
  int *p1 = (int *) mi_heap_malloc(heap, sizeof(int));
  int *p2 = (int *) mi_heap_malloc(heap, sizeof(int));
  mi_heap_delete(heap);
  *p1 = 42;
  mi_free(p1);
  mi_free(p2);
  return 1;
}

bool test_stl_allocator1(void)
{
  return 1;
}

struct some_struct
{
  int i;
  int j;
  double z;
};
bool test_stl_allocator2(void)
{
  return 1;
}

bool test_stl_heap_allocator1(void)
{
  return 1;
}

bool test_stl_heap_allocator2(void)
{
  return 1;
}

bool test_stl_heap_allocator3(void)
{
  return 1;
}

bool test_stl_heap_allocator4(void)
{
  return 1;
}

void helper_main_1(bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref)
{
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool ok = 1;
  for (size_t size = 1; (size <= ((128 * (sizeof(void *))) * 2)) && ok; size += 1)
  {
    for (size_t align = 1; (align <= size) && ok; align *= 2)
    {
      void *p[10];
      for (int i = 0; (i < 10) && ok; i += 1)
      {
        p[i + p_idx] = mi_malloc_aligned(size, align);
        ;
        ok = (p[i + p_idx] != 0) && ((((uintptr_t) p[i + p_idx]) % align) == 0);
      }

      for (int i = 0; (i < 10) && ok; i += 1)
      {
        mi_free(p[i + p_idx]);
      }

    }

  }

  result = ok;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
}

void helper_main_2(bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, unsigned int * const p_idx_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref, bool * const result_ref)
{
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  unsigned int p_idx = *p_idx_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool result = *result_ref;
  bool ok = 1;
  void *p[8];
  const int max_align_shift = 20;
  size_t sizes[8] = {8, 512, 1024 * 1024, 1UL << (13 + 3), (1UL << (13 + 3)) + 1, 2 * (1UL << (13 + 3)), 8 * (1UL << (13 + 3)), 0};
  for (int i = 0; (i < max_align_shift) && ok; i += 1)
  {
    int align = 1 << i;
    for (int j = 0; (j < 8) && ok; j += 1)
    {
      p[j + p_idx] = mi_zalloc_aligned(sizes[j], align);
      ok = (((uintptr_t) p[j + p_idx]) % align) == 0;
    }

    for (int j = 0; j < 8; j += 1)
    {
      mi_free(p[j + p_idx]);
    }

  }

  result = ok;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *p_idx_ref = p_idx;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
  *result_ref = result;
}

