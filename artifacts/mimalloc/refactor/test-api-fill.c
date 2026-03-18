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
#include <test-api-fill.c>
#include <testhelper.h>
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

bool check_zero_init(uint8_t *p, size_t size);
bool check_debug_fill_uninit(uint8_t *p, size_t size);
bool check_debug_fill_freed(uint8_t *p, size_t size);
int main(void)
{
  mi_option_disable(mi_option_verbose);
  fprintf(stderr, "test: %s...  ", "zeroinit-zalloc-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-zalloc-small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 30))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_zalloc(zalloc_size);
    unsigned int p_idx = 0;
    result = check_zero_init(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-zalloc-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-zalloc-large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 36))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_zalloc(zalloc_size);
    unsigned int p_idx = 0;
    result = check_zero_init(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-zalloc_small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-zalloc_small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 42))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_zalloc_small(zalloc_size);
    unsigned int p_idx = 0;
    result = check_zero_init(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-calloc-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-calloc-small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 49))
  {
    size_t calloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_calloc(calloc_size, 1);
    unsigned int p_idx = 0;
    result = check_zero_init(p, calloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-calloc-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-calloc-large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 55))
  {
    size_t calloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_calloc(calloc_size, 1);
    unsigned int p_idx = 0;
    result = check_zero_init(p, calloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-rezalloc-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-rezalloc-small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 62))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_zalloc(zalloc_size);
    unsigned int p_idx = 0;
    result = check_zero_init(p, zalloc_size);
    zalloc_size *= 3;
    p_idx = (uint8_t *) mi_rezalloc(p_idx, zalloc_size);
    result &= check_zero_init(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-rezalloc-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-rezalloc-large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 71))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_zalloc(zalloc_size);
    unsigned int p_idx = 0;
    result = check_zero_init(p, zalloc_size);
    zalloc_size *= 3;
    p_idx = (uint8_t *) mi_rezalloc(p_idx, zalloc_size);
    result &= check_zero_init(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-recalloc-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-recalloc-small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 81))
  {
    size_t calloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_calloc(calloc_size, 1);
    unsigned int p_idx = 0;
    result = check_zero_init(p, calloc_size);
    calloc_size *= 3;
    p_idx = (uint8_t *) mi_recalloc(p_idx, calloc_size, 1);
    result &= check_zero_init(p, calloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-recalloc-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-recalloc-large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 90))
  {
    size_t calloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_calloc(calloc_size, 1);
    unsigned int p_idx = 0;
    result = check_zero_init(p, calloc_size);
    calloc_size *= 3;
    p_idx = (uint8_t *) mi_recalloc(p_idx, calloc_size, 1);
    result &= check_zero_init(p, calloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-zalloc_aligned-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-zalloc_aligned-small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 103))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_zalloc_aligned(zalloc_size, 16 * 2);
    unsigned int p_idx = 0;
    result = check_zero_init(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-zalloc_aligned-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-zalloc_aligned-large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 109))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_zalloc_aligned(zalloc_size, 16 * 2);
    unsigned int p_idx = 0;
    result = check_zero_init(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-calloc_aligned-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-calloc_aligned-small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 116))
  {
    size_t calloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_calloc_aligned(calloc_size, 1, 16 * 2);
    unsigned int p_idx = 0;
    result = check_zero_init(p, calloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-calloc_aligned-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-calloc_aligned-large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 122))
  {
    size_t calloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_calloc_aligned(calloc_size, 1, 16 * 2);
    unsigned int p_idx = 0;
    result = check_zero_init(p, calloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-rezalloc_aligned-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-rezalloc_aligned-small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 129))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_zalloc_aligned(zalloc_size, 16 * 2);
    unsigned int p_idx = 0;
    result = check_zero_init(p, zalloc_size);
    zalloc_size *= 3;
    p_idx = (uint8_t *) mi_rezalloc_aligned(p_idx, zalloc_size, 16 * 2);
    result &= check_zero_init(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-rezalloc_aligned-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-rezalloc_aligned-large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 138))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_zalloc_aligned(zalloc_size, 16 * 2);
    unsigned int p_idx = 0;
    result = check_zero_init(p, zalloc_size);
    zalloc_size *= 3;
    p_idx = (uint8_t *) mi_rezalloc_aligned(p_idx, zalloc_size, 16 * 2);
    result &= check_zero_init(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-recalloc_aligned-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-recalloc_aligned-small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 148))
  {
    size_t calloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_calloc_aligned(calloc_size, 1, 16 * 2);
    unsigned int p_idx = 0;
    result = check_zero_init(p, calloc_size);
    calloc_size *= 3;
    p_idx = (uint8_t *) mi_recalloc_aligned(p_idx, calloc_size, 1, 16 * 2);
    result &= check_zero_init(p, calloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-recalloc_aligned-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-recalloc_aligned-large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 157))
  {
    size_t calloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_calloc_aligned(calloc_size, 1, 16 * 2);
    unsigned int p_idx = 0;
    result = check_zero_init(p, calloc_size);
    calloc_size *= 3;
    p_idx = (uint8_t *) mi_recalloc_aligned(p_idx, calloc_size, 1, 16 * 2);
    result &= check_zero_init(p, calloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-malloc-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-malloc-small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 171))
  {
    size_t malloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_malloc(malloc_size);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-malloc-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-malloc-large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 177))
  {
    size_t malloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_malloc(malloc_size);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-malloc_small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-malloc_small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 184))
  {
    size_t malloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_malloc_small(malloc_size);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-realloc-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-realloc-small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 191))
  {
    size_t malloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_malloc(malloc_size);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    malloc_size *= 3;
    p_idx = (uint8_t *) mi_realloc(p_idx, malloc_size);
    result &= check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-realloc-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-realloc-large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 200))
  {
    size_t malloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_malloc(malloc_size);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    malloc_size *= 3;
    p_idx = (uint8_t *) mi_realloc(p_idx, malloc_size);
    result &= check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-mallocn-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-mallocn-small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 210))
  {
    size_t malloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_mallocn(malloc_size, 1);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-mallocn-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-mallocn-large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 216))
  {
    size_t malloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_mallocn(malloc_size, 1);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-reallocn-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-reallocn-small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 223))
  {
    size_t malloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_mallocn(malloc_size, 1);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    malloc_size *= 3;
    p_idx = (uint8_t *) mi_reallocn(p_idx, malloc_size, 1);
    result &= check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-reallocn-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-reallocn-large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 232))
  {
    size_t malloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_mallocn(malloc_size, 1);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    malloc_size *= 3;
    p_idx = (uint8_t *) mi_reallocn(p_idx, malloc_size, 1);
    result &= check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-malloc_aligned-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-malloc_aligned-small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 242))
  {
    size_t malloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_malloc_aligned(malloc_size, 16 * 2);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-malloc_aligned-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-malloc_aligned-large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 248))
  {
    size_t malloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_malloc_aligned(malloc_size, 16 * 2);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-realloc_aligned-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-realloc_aligned-small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 255))
  {
    size_t malloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_malloc_aligned(malloc_size, 16 * 2);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    malloc_size *= 3;
    p_idx = (uint8_t *) mi_realloc_aligned(p_idx, malloc_size, 16 * 2);
    result &= check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-realloc_aligned-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-realloc_aligned-large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 264))
  {
    size_t malloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_malloc_aligned(malloc_size, 16 * 2);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    malloc_size *= 3;
    p_idx = (uint8_t *) mi_realloc_aligned(p_idx, malloc_size, 16 * 2);
    result &= check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "fill-freed-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "fill-freed-small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 275))
  {
    size_t malloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_malloc(malloc_size);
    unsigned int p_idx = 0;
    mi_free(p);
    result = check_debug_fill_freed((&p[p_idx]) + (sizeof(void *)), malloc_size - (sizeof(void *)));
  }

  ;
  fprintf(stderr, "test: %s...  ", "fill-freed-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "fill-freed-large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 282))
  {
    size_t malloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_malloc(malloc_size);
    unsigned int p_idx = 0;
    mi_free(p);
    result = check_debug_fill_freed((&p[p_idx]) + (sizeof(void *)), malloc_size - (sizeof(void *)));
  }

  ;
  return print_test_summary();
}

bool check_zero_init(uint8_t *p, size_t size)
{
  if (!p)
  {
    return 0;
  }
  bool result = 1;
  for (size_t i = 0; i < size; i += 1)
  {
    result &= p[i] == 0;
  }

  return result;
}

bool check_debug_fill_uninit(uint8_t *p, size_t size)
{
  if (!p)
  {
    return 0;
  }
  bool result = 1;
  for (size_t i = 0; i < size; i += 1)
  {
    result &= p[i] == 0xD0;
  }

  return result;
}

bool check_debug_fill_freed(uint8_t *p, size_t size)
{
  if (!p)
  {
    return 0;
  }
  bool result = 1;
  for (size_t i = 0; i < size; i += 1)
  {
    result &= p[i] == 0xDF;
  }

  return result;
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

bool check_zero_init(uint8_t *p, size_t size);
bool check_debug_fill_uninit(uint8_t *p, size_t size);
bool check_debug_fill_freed(uint8_t *p, size_t size);
int main(void)
{
  mi_option_disable(mi_option_verbose);
  fprintf(stderr, "test: %s...  ", "zeroinit-zalloc-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-zalloc-small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 30))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_zalloc(zalloc_size);
    unsigned int p_idx = 0;
    result = check_zero_init(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-zalloc-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-zalloc-large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 36))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_zalloc(zalloc_size);
    unsigned int p_idx = 0;
    result = check_zero_init(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-zalloc_small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-zalloc_small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 42))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_zalloc_small(zalloc_size);
    unsigned int p_idx = 0;
    result = check_zero_init(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-calloc-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-calloc-small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 49))
  {
    size_t calloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_calloc(calloc_size, 1);
    unsigned int p_idx = 0;
    result = check_zero_init(p, calloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-calloc-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-calloc-large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 55))
  {
    size_t calloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_calloc(calloc_size, 1);
    unsigned int p_idx = 0;
    result = check_zero_init(p, calloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-rezalloc-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-rezalloc-small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 62))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_zalloc(zalloc_size);
    unsigned int p_idx = 0;
    result = check_zero_init(p, zalloc_size);
    zalloc_size *= 3;
    p_idx = (uint8_t *) mi_rezalloc(p_idx, zalloc_size);
    result &= check_zero_init(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-rezalloc-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-rezalloc-large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 71))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_zalloc(zalloc_size);
    unsigned int p_idx = 0;
    result = check_zero_init(p, zalloc_size);
    zalloc_size *= 3;
    p_idx = (uint8_t *) mi_rezalloc(p_idx, zalloc_size);
    result &= check_zero_init(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-recalloc-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-recalloc-small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 81))
  {
    size_t calloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_calloc(calloc_size, 1);
    unsigned int p_idx = 0;
    result = check_zero_init(p, calloc_size);
    calloc_size *= 3;
    p_idx = (uint8_t *) mi_recalloc(p_idx, calloc_size, 1);
    result &= check_zero_init(p, calloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-recalloc-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-recalloc-large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 90))
  {
    size_t calloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_calloc(calloc_size, 1);
    unsigned int p_idx = 0;
    result = check_zero_init(p, calloc_size);
    calloc_size *= 3;
    p_idx = (uint8_t *) mi_recalloc(p_idx, calloc_size, 1);
    result &= check_zero_init(p, calloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-zalloc_aligned-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-zalloc_aligned-small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 103))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_zalloc_aligned(zalloc_size, 16 * 2);
    unsigned int p_idx = 0;
    result = check_zero_init(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-zalloc_aligned-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-zalloc_aligned-large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 109))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_zalloc_aligned(zalloc_size, 16 * 2);
    unsigned int p_idx = 0;
    result = check_zero_init(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-calloc_aligned-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-calloc_aligned-small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 116))
  {
    size_t calloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_calloc_aligned(calloc_size, 1, 16 * 2);
    unsigned int p_idx = 0;
    result = check_zero_init(p, calloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-calloc_aligned-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-calloc_aligned-large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 122))
  {
    size_t calloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_calloc_aligned(calloc_size, 1, 16 * 2);
    unsigned int p_idx = 0;
    result = check_zero_init(p, calloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-rezalloc_aligned-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-rezalloc_aligned-small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 129))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_zalloc_aligned(zalloc_size, 16 * 2);
    unsigned int p_idx = 0;
    result = check_zero_init(p, zalloc_size);
    zalloc_size *= 3;
    p_idx = (uint8_t *) mi_rezalloc_aligned(p_idx, zalloc_size, 16 * 2);
    result &= check_zero_init(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-rezalloc_aligned-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-rezalloc_aligned-large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 138))
  {
    size_t zalloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_zalloc_aligned(zalloc_size, 16 * 2);
    unsigned int p_idx = 0;
    result = check_zero_init(p, zalloc_size);
    zalloc_size *= 3;
    p_idx = (uint8_t *) mi_rezalloc_aligned(p_idx, zalloc_size, 16 * 2);
    result &= check_zero_init(p, zalloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-recalloc_aligned-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-recalloc_aligned-small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 148))
  {
    size_t calloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_calloc_aligned(calloc_size, 1, 16 * 2);
    unsigned int p_idx = 0;
    result = check_zero_init(p, calloc_size);
    calloc_size *= 3;
    p_idx = (uint8_t *) mi_recalloc_aligned(p_idx, calloc_size, 1, 16 * 2);
    result &= check_zero_init(p, calloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "zeroinit-recalloc_aligned-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "zeroinit-recalloc_aligned-large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 157))
  {
    size_t calloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_calloc_aligned(calloc_size, 1, 16 * 2);
    unsigned int p_idx = 0;
    result = check_zero_init(p, calloc_size);
    calloc_size *= 3;
    p_idx = (uint8_t *) mi_recalloc_aligned(p_idx, calloc_size, 1, 16 * 2);
    result &= check_zero_init(p, calloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-malloc-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-malloc-small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 171))
  {
    size_t malloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_malloc(malloc_size);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-malloc-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-malloc-large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 177))
  {
    size_t malloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_malloc(malloc_size);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-malloc_small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-malloc_small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 184))
  {
    size_t malloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_malloc_small(malloc_size);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-realloc-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-realloc-small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 191))
  {
    size_t malloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_malloc(malloc_size);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    malloc_size *= 3;
    p_idx = (uint8_t *) mi_realloc(p_idx, malloc_size);
    result &= check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-realloc-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-realloc-large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 200))
  {
    size_t malloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_malloc(malloc_size);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    malloc_size *= 3;
    p_idx = (uint8_t *) mi_realloc(p_idx, malloc_size);
    result &= check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-mallocn-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-mallocn-small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 210))
  {
    size_t malloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_mallocn(malloc_size, 1);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-mallocn-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-mallocn-large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 216))
  {
    size_t malloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_mallocn(malloc_size, 1);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-reallocn-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-reallocn-small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 223))
  {
    size_t malloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_mallocn(malloc_size, 1);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    malloc_size *= 3;
    p_idx = (uint8_t *) mi_reallocn(p_idx, malloc_size, 1);
    result &= check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-reallocn-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-reallocn-large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 232))
  {
    size_t malloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_mallocn(malloc_size, 1);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    malloc_size *= 3;
    p_idx = (uint8_t *) mi_reallocn(p_idx, malloc_size, 1);
    result &= check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-malloc_aligned-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-malloc_aligned-small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 242))
  {
    size_t malloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_malloc_aligned(malloc_size, 16 * 2);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-malloc_aligned-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-malloc_aligned-large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 248))
  {
    size_t malloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_malloc_aligned(malloc_size, 16 * 2);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-realloc_aligned-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-realloc_aligned-small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 255))
  {
    size_t malloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_malloc_aligned(malloc_size, 16 * 2);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    malloc_size *= 3;
    p_idx = (uint8_t *) mi_realloc_aligned(p_idx, malloc_size, 16 * 2);
    result &= check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "uninit-realloc_aligned-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "uninit-realloc_aligned-large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 264))
  {
    size_t malloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_malloc_aligned(malloc_size, 16 * 2);
    unsigned int p_idx = 0;
    result = check_debug_fill_uninit(p, malloc_size);
    malloc_size *= 3;
    p_idx = (uint8_t *) mi_realloc_aligned(p_idx, malloc_size, 16 * 2);
    result &= check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  }

  ;
  fprintf(stderr, "test: %s...  ", "fill-freed-small");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "fill-freed-small", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 275))
  {
    size_t malloc_size = (128 * (sizeof(void *))) / 2;
    uint8_t *p = (uint8_t *) mi_malloc(malloc_size);
    unsigned int p_idx = 0;
    mi_free(p);
    result = check_debug_fill_freed((&p[p_idx]) + (sizeof(void *)), malloc_size - (sizeof(void *)));
  }

  ;
  fprintf(stderr, "test: %s...  ", "fill-freed-large");
  errno = 0;
  for (bool done = 0, result = 1; !done; done = check_result(result, "fill-freed-large", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c", 282))
  {
    size_t malloc_size = (128 * (sizeof(void *))) * 2;
    uint8_t *p = (uint8_t *) mi_malloc(malloc_size);
    unsigned int p_idx = 0;
    mi_free(p);
    result = check_debug_fill_freed((&p[p_idx]) + (sizeof(void *)), malloc_size - (sizeof(void *)));
  }

  ;
  return print_test_summary();
}

bool check_zero_init(uint8_t *p, size_t size)
{
  if (!p)
  {
    return 0;
  }
  bool result = 1;
  for (size_t i = 0; i < size; i += 1)
  {
    result &= p[i] == 0;
  }

  return result;
}

bool check_debug_fill_uninit(uint8_t *p, size_t size)
{
  if (!p)
  {
    return 0;
  }
  bool result = 1;
  for (size_t i = 0; i < size; i += 1)
  {
    result &= p[i] == 0xD0;
  }

  return result;
}

bool check_debug_fill_freed(uint8_t *p, size_t size)
{
  if (!p)
  {
    return 0;
  }
  bool result = 1;
  for (size_t i = 0; i < size; i += 1)
  {
    result &= p[i] == 0xDF;
  }

  return result;
}

