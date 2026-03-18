#include <atomic.h>
#include <bitmap.h>
#include <bits.h>
#include <errno.h>
#include <internal.h>
#include <limits.h>
#include <mimalloc-stats.h>
#include <mimalloc.h>
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

mi_arena_id_t _mi_arena_id_none(void)
{
  return 0;
}

mi_arena_t *_mi_arena_from_id(mi_arena_id_t id)
{
  return (mi_arena_t *) id;
}

static bool mi_arena_id_is_suitable(mi_arena_t *arena, mi_arena_t *req_arena)
{
  return (arena == req_arena) || ((req_arena == 0) && (!arena->is_exclusive));
}

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

size_t mi_arenas_get_count(mi_subproc_t *subproc)
{
  return atomic_load_explicit(&subproc->arena_count, memory_order_relaxed);
}

mi_arena_t *mi_arena_from_index(mi_subproc_t *subproc, size_t idx)
{
  (idx < mi_arenas_get_count(subproc)) ? ((void) 0) : (_mi_assert_fail("idx < mi_arenas_get_count(subproc)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 59, __func__));
  return atomic_load_explicit(&subproc->arenas[idx], memory_order_relaxed);
}

static size_t mi_arena_info_slices(mi_arena_t *arena)
{
  return arena->info_slices;
}

static bool mi_arena_has_page(mi_arena_t *arena, mi_page_t *page)
{
  return ((page->memid.memkind == MI_MEM_ARENA) && (page->memid.mem.arena.arena == arena)) && mi_bitmap_is_setN(arena->pages, page->memid.mem.arena.slice_index, 1);
}

size_t mi_arena_min_alignment(void)
{
  return 1UL << (13 + 3);
}

static bool mi_arena_commit(mi_arena_t *arena, void *start, size_t size, bool *is_zero, size_t already_committed)
{
  if ((arena != 0) && (arena->commit_fun != 0))
  {
    return (*arena->commit_fun)(1, start, size, is_zero, arena->commit_fun_arg);
  }
  else
    if (already_committed > 0)
  {
    return _mi_os_commit_ex(start, size, is_zero, already_committed);
  }
  else
  {
    return _mi_os_commit(start, size, is_zero);
  }
}

static size_t mi_arena_size(mi_arena_t *arena)
{
  return mi_size_of_slices(arena->slice_count);
}

static uint8_t *mi_arena_start(mi_arena_t *arena)
{
  return (uint8_t *) arena;
}

uint8_t *mi_arena_slice_start(mi_arena_t *arena, size_t slice_index)
{
  return mi_arena_start(arena) + mi_size_of_slices(slice_index);
}

void *mi_arena_area(mi_arena_id_t arena_id, size_t *size)
{
  if (size != 0)
  {
    *size = 0;
  }
  mi_arena_t *arena = _mi_arena_from_id(arena_id);
  if (arena == 0)
  {
    return 0;
  }
  if (size != 0)
  {
    *size = mi_size_of_slices(arena->slice_count);
  }
  return mi_arena_start(arena);
}

static mi_memid_t mi_memid_create_arena(mi_arena_t *arena, size_t slice_index, size_t slice_count)
{
  (slice_index < UINT32_MAX) ? ((void) 0) : (_mi_assert_fail("slice_index < UINT32_MAX", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 125, __func__));
  (slice_count < UINT32_MAX) ? ((void) 0) : (_mi_assert_fail("slice_count < UINT32_MAX", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 126, __func__));
  (slice_count > 0) ? ((void) 0) : (_mi_assert_fail("slice_count > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 127, __func__));
  (slice_index < arena->slice_count) ? ((void) 0) : (_mi_assert_fail("slice_index < arena->slice_count", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 128, __func__));
  mi_memid_t memid = _mi_memid_create(MI_MEM_ARENA);
  memid.mem.arena.arena = arena;
  memid.mem.arena.slice_index = (uint32_t) slice_index;
  memid.mem.arena.slice_count = (uint32_t) slice_count;
  return memid;
}

static mi_arena_t *mi_arena_from_memid(mi_memid_t memid, size_t *slice_index, size_t *slice_count)
{
  (memid.memkind == MI_MEM_ARENA) ? ((void) 0) : (_mi_assert_fail("memid.memkind == MI_MEM_ARENA", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 138, __func__));
  mi_arena_t *arena = memid.mem.arena.arena;
  if (slice_index)
  {
    *slice_index = memid.mem.arena.slice_index;
  }
  if (slice_count)
  {
    *slice_count = memid.mem.arena.slice_count;
  }
  return arena;
}

static mi_arena_t *mi_page_arena(mi_page_t *page, size_t *slice_index, size_t *slice_count)
{
  return mi_arena_from_memid(page->memid, slice_index, slice_count);
}

static size_t mi_page_full_size(mi_page_t *page)
{
  if (page->memid.memkind == MI_MEM_ARENA)
  {
    return page->memid.mem.arena.slice_count * (1UL << (13 + 3));
  }
  else
    if (mi_memid_is_os(page->memid) || (page->memid.memkind == MI_MEM_EXTERNAL))
  {
    (((uint8_t *) page->memid.mem.os.base) <= ((uint8_t *) page)) ? ((void) 0) : (_mi_assert_fail("(uint8_t*)page->memid.mem.os.base <= (uint8_t*)page", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 155, __func__));
    const ptrdiff_t presize = ((uint8_t *) page) - ((uint8_t *) page->memid.mem.os.base);
    (((ptrdiff_t) page->memid.mem.os.size) >= presize) ? ((void) 0) : (_mi_assert_fail("(ptrdiff_t)page->memid.mem.os.size >= presize", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 157, __func__));
    return (presize > ((ptrdiff_t) page->memid.mem.os.size)) ? (0) : (page->memid.mem.os.size - presize);
  }
  else
  {
    return 0;
  }
}

static void *mi_arena_try_alloc_at(mi_arena_t *arena, size_t slice_count, bool commit, size_t tseq, mi_memid_t *memid)
{
  size_t slice_index;
  if (!mi_bbitmap_try_find_and_clearN(arena->slices_free, slice_count, tseq, &slice_index))
  {
    return 0;
  }
  void *p = mi_arena_slice_start(arena, slice_index);
  *memid = mi_memid_create_arena(arena, slice_index, slice_count);
  memid->is_pinned = arena->memid.is_pinned;
  size_t touched_slices = slice_count;
  if (arena->memid.initially_zero)
  {
    size_t already_dirty = 0;
    memid->initially_zero = mi_bitmap_setN(arena->slices_dirty, slice_index, slice_count, &already_dirty);
    (already_dirty <= touched_slices) ? ((void) 0) : (_mi_assert_fail("already_dirty <= touched_slices", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 186, __func__));
    touched_slices -= already_dirty;
  }
  if (commit)
  {
    const size_t already_committed = mi_bitmap_popcountN(arena->slices_committed, slice_index, slice_count);
    if (already_committed < slice_count)
    {
      bool commit_zero = 0;
      if (!_mi_os_commit_ex(p, mi_size_of_slices(slice_count), &commit_zero, mi_size_of_slices(slice_count - already_committed)))
      {
        mi_bbitmap_setN(arena->slices_free, slice_index, slice_count);
        return 0;
      }
      if (commit_zero)
      {
        memid->initially_zero = 1;
      }
      mi_bitmap_setN(arena->slices_committed, slice_index, slice_count, 0);
      if (memid->initially_zero)
      {
        if (!mi_mem_is_zero(p, mi_size_of_slices(slice_count)))
        {
          _mi_error_message(14, "interal error: arena allocation was not zero-initialized!\n");
          memid->initially_zero = 0;
        }
      }
    }
    else
    {
      _mi_os_reuse(p, mi_size_of_slices(slice_count));
      if (_mi_os_has_overcommit() && (touched_slices > 0))
      {
        __mi_stat_increase_mt(&arena->subproc->stats.committed, mi_size_of_slices(touched_slices));
      }
    }
    (mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 230, __func__));
    memid->initially_committed = 1;
    if (memid->initially_zero)
    {
      ;
    }
    else
    {
      ;
    }
  }
  else
  {
    memid->initially_committed = mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count);
    if (!memid->initially_committed)
    {
      size_t already_committed_count = 0;
      mi_bitmap_setN(arena->slices_committed, slice_index, slice_count, &already_committed_count);
      mi_bitmap_clearN(arena->slices_committed, slice_index, slice_count);
      __mi_stat_decrease_mt(&_mi_subproc()->stats.committed, mi_size_of_slices(already_committed_count));
    }
  }
  (mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 253, __func__));
  if (commit)
  {
    (mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 254, __func__));
  }
  if (commit)
  {
    (memid->initially_committed) ? ((void) 0) : (_mi_assert_fail("memid->initially_committed", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 255, __func__));
  }
  (mi_bitmap_is_setN(arena->slices_dirty, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_setN(arena->slices_dirty, slice_index, slice_count)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 256, __func__));
  return p;
}

static int mi_reserve_os_memory_ex2(mi_subproc_t *subproc, size_t size, bool commit, bool allow_large, bool exclusive, mi_arena_id_t *arena_id);
static bool mi_arena_reserve(mi_subproc_t *subproc, size_t req_size, bool allow_large, mi_arena_id_t *arena_id)
{
  const size_t arena_count = mi_arenas_get_count(subproc);
  if (arena_count > (160 - 4))
  {
    return 0;
  }
  size_t arena_reserve = mi_option_get_size(mi_option_arena_reserve);
  if (arena_reserve == 0)
  {
    return 0;
  }
  if (!_mi_os_has_virtual_reserve())
  {
    arena_reserve = arena_reserve / 4;
  }
  arena_reserve = _mi_align_up(arena_reserve, 1UL << (13 + 3));
  if ((arena_count >= 1) && (arena_count <= 128))
  {
    const size_t multiplier = ((size_t) 1) << _mi_clamp(arena_count / 4, 0, 16);
    size_t reserve = 0;
    if (!mi_mul_overflow(multiplier, arena_reserve, &reserve))
    {
      arena_reserve = reserve;
    }
  }
  const size_t min_reserve = (1 << (6 + 3)) * (1UL << (13 + 3));
  const size_t max_reserve = ((1 << (6 + 3)) * (1 << (6 + 3))) * (1UL << (13 + 3));
  if (arena_reserve < min_reserve)
  {
    arena_reserve = min_reserve;
  }
  else
    if (arena_reserve > max_reserve)
  {
    arena_reserve = max_reserve;
  }
  if (arena_reserve < req_size)
  {
    return 0;
  }
  bool arena_commit = 0;
  const bool overcommit = _mi_os_has_overcommit();
  if (mi_option_get(mi_option_arena_eager_commit) == 2)
  {
    arena_commit = overcommit;
  }
  else
    if (mi_option_get(mi_option_arena_eager_commit) == 1)
  {
    arena_commit = 1;
  }
  const bool adjust = overcommit && arena_commit;
  if (adjust)
  {
    __mi_stat_adjust_decrease_mt(&subproc->stats.committed, arena_reserve);
  }
  int err = mi_reserve_os_memory_ex2(subproc, arena_reserve, arena_commit, allow_large, 0, arena_id);
  if (err != 0)
  {
    if (adjust)
    {
      __mi_stat_adjust_increase_mt(&subproc->stats.committed, arena_reserve);
    }
    const size_t small_arena_reserve = (((1 << 3) * 8) == 32) ? (128 * (1024UL * 1024UL)) : (1 * ((1024UL * 1024UL) * 1024UL));
    if (adjust)
    {
      __mi_stat_adjust_decrease_mt(&subproc->stats.committed, arena_reserve);
    }
    if (arena_reserve > small_arena_reserve)
    {
      err = mi_reserve_os_memory_ex(small_arena_reserve, arena_commit, allow_large, 0, arena_id);
      if ((err != 0) && adjust)
      {
        __mi_stat_adjust_increase_mt(&subproc->stats.committed, arena_reserve);
      }
    }
  }
  return err == 0;
}

inline static bool mi_arena_is_suitable(mi_arena_t *arena, mi_arena_t *req_arena, bool match_numa, int numa_node, bool allow_pinned)
{
  if ((!allow_pinned) && arena->memid.is_pinned)
  {
    return 0;
  }
  if (!mi_arena_id_is_suitable(arena, req_arena))
  {
    return 0;
  }
  if (req_arena == 0)
  {
    const bool numa_suitable = ((numa_node < 0) || (arena->numa_node < 0)) || (arena->numa_node == numa_node);
    if (match_numa)
    {
      if (!numa_suitable)
      {
        return 0;
      }
    }
    else
    {
      if (numa_suitable)
      {
        return 0;
      }
    }
  }
  return 1;
}

static void *mi_arenas_try_find_free(mi_subproc_t *subproc, size_t slice_count, size_t alignment, bool commit, bool allow_large, mi_arena_t *req_arena, size_t tseq, int numa_node, mi_memid_t *memid)
{
  (slice_count <= mi_slice_count_of_size((1 << (6 + 3)) * (1UL << (13 + 3)))) ? ((void) 0) : (_mi_assert_fail("slice_count <= mi_slice_count_of_size(MI_ARENA_MAX_OBJ_SIZE)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 391, __func__));
  (alignment <= (1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("alignment <= MI_ARENA_SLICE_ALIGN", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 392, __func__));
  if (alignment > (1UL << (13 + 3)))
  {
    return 0;
  }
  {
    const size_t _arena_count = mi_arenas_get_count(subproc);
    const size_t _arena_cycle = (_arena_count == 0) ? (0) : (_arena_count - 1);
    size_t _start = (_arena_cycle <= 1) ? (0) : (tseq % _arena_cycle);
    for (size_t _i = 0; _i < _arena_count; _i += 1)
    {
      mi_arena_t *arena;
      unsigned int arena_idx = 0;
      if (req_arena != 0)
      {
        arena_idx = req_arena;
        if (_i > 0)
        {
          break;
        }
      }
      else
      {
        size_t _idx;
        if (_i < _arena_cycle)
        {
          _idx = _i + _start;
          if (_idx >= _arena_cycle)
          {
            _idx -= _arena_cycle;
          }
        }
        else
        {
          _idx = _i;
        }
        arena_idx = mi_arena_from_index(subproc, _idx);
      }
      if ((&arena[arena_idx]) != 0)
      {
        {
          if (mi_arena_is_suitable(arena, req_arena, 1, numa_node, allow_large))
          {
            {
              void *p = mi_arena_try_alloc_at(arena, slice_count, commit, tseq, memid);
              if (p != 0)
              {
                return p;
              }
            }
          }
        }
      }
    }

  }
  ;
  if (numa_node < 0)
  {
    return 0;
  }
  {
    const size_t _arena_count = mi_arenas_get_count(subproc);
    const size_t _arena_cycle = (_arena_count == 0) ? (0) : (_arena_count - 1);
    size_t _start = (_arena_cycle <= 1) ? (0) : (tseq % _arena_cycle);
    for (size_t _i = 0; _i < _arena_count; _i += 1)
    {
      mi_arena_t *arena;
      unsigned int arena_idx = 0;
      if (req_arena != 0)
      {
        arena_idx = req_arena;
        if (_i > 0)
        {
          break;
        }
      }
      else
      {
        size_t _idx;
        if (_i < _arena_cycle)
        {
          _idx = _i + _start;
          if (_idx >= _arena_cycle)
          {
            _idx -= _arena_cycle;
          }
        }
        else
        {
          _idx = _i;
        }
        arena_idx = mi_arena_from_index(subproc, _idx);
      }
      if ((&arena[arena_idx]) != 0)
      {
        {
          if (mi_arena_is_suitable(arena, req_arena, 0, numa_node, allow_large))
          {
            {
              void *p = mi_arena_try_alloc_at(arena, slice_count, commit, tseq, memid);
              if (p != 0)
              {
                return p;
              }
            }
          }
        }
      }
    }

  }
  ;
  return 0;
}

static void *mi_arenas_try_alloc(mi_subproc_t *subproc, size_t slice_count, size_t alignment, bool commit, bool allow_large, mi_arena_t *req_arena, size_t tseq, int numa_node, mi_memid_t *memid)
{
  (slice_count <= (1 << (6 + 3))) ? ((void) 0) : (_mi_assert_fail("slice_count <= MI_ARENA_MAX_OBJ_SLICES", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 421, __func__));
  (alignment <= (1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("alignment <= MI_ARENA_SLICE_ALIGN", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 422, __func__));
  void *p;
  unsigned int p_idx = 0;
  p_idx = mi_arenas_try_find_free(subproc, slice_count, alignment, commit, allow_large, req_arena, tseq, numa_node, memid);
  if ((&p[p_idx]) != 0)
  {
    return p;
  }
  if (req_arena != 0)
  {
    return 0;
  }
  if (_mi_preloading())
  {
    return 0;
  }
  const size_t arena_count = mi_arenas_get_count(subproc);
  for (bool _go = (mi_lock_acquire(&subproc->arena_reserve_lock), 1); _go; mi_lock_release(&subproc->arena_reserve_lock), _go = 0)
  {
    if (arena_count == mi_arenas_get_count(subproc))
    {
      mi_arena_id_t arena_id = 0;
      mi_arena_reserve(subproc, mi_size_of_slices(slice_count), allow_large, &arena_id);
    }
    else
    {
    }
  }

  (req_arena == 0) ? ((void) 0) : (_mi_assert_fail("req_arena == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 448, __func__));
  p_idx = mi_arenas_try_find_free(subproc, slice_count, alignment, commit, allow_large, req_arena, tseq, numa_node, memid);
  if ((&p[p_idx]) != 0)
  {
    return p;
  }
  return 0;
}

static void *mi_arena_os_alloc_aligned(size_t size, size_t alignment, size_t align_offset, bool commit, bool allow_large, mi_arena_id_t req_arena_id, mi_memid_t *memid)
{
  if (mi_option_is_enabled(mi_option_disallow_os_alloc) || (req_arena_id != _mi_arena_id_none()))
  {
    errno = 12;
    return 0;
  }
  if (align_offset > 0)
  {
    return _mi_os_alloc_aligned_at_offset(size, alignment, align_offset, commit, allow_large, memid);
  }
  else
  {
    return _mi_os_alloc_aligned(size, alignment, commit, allow_large, memid);
  }
}

void *_mi_arenas_alloc_aligned(mi_subproc_t *subproc, size_t size, size_t alignment, size_t align_offset, bool commit, bool allow_large, mi_arena_t *req_arena, size_t tseq, int numa_node, mi_memid_t *memid)
{
  (memid != 0) ? ((void) 0) : (_mi_assert_fail("memid != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 482, __func__));
  (size > 0) ? ((void) 0) : (_mi_assert_fail("size > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 483, __func__));
  if (((((!mi_option_is_enabled(mi_option_disallow_arena_alloc)) && (size >= (1 * (1UL << (13 + 3))))) && (size <= ((1 << (6 + 3)) * (1UL << (13 + 3))))) && (alignment <= (1UL << (13 + 3)))) && (align_offset == 0))
  {
    const size_t slice_count = mi_slice_count_of_size(size);
    void *p = mi_arenas_try_alloc(subproc, slice_count, alignment, commit, allow_large, req_arena, tseq, numa_node, memid);
    if (p != 0)
    {
      return p;
    }
  }
  void *p = mi_arena_os_alloc_aligned(size, alignment, align_offset, commit, allow_large, req_arena, memid);
  return p;
}

void *_mi_arenas_alloc(mi_subproc_t *subproc, size_t size, bool commit, bool allow_large, mi_arena_t *req_arena, size_t tseq, int numa_node, mi_memid_t *memid)
{
  return _mi_arenas_alloc_aligned(subproc, size, 1UL << (13 + 3), 0, commit, allow_large, req_arena, tseq, numa_node, memid);
}

static bool mi_arena_try_claim_abandoned(size_t slice_index, mi_arena_t *arena, mi_heaptag_t heap_tag, bool *keep_abandoned)
{
  mi_page_t * const page = (mi_page_t *) mi_arena_slice_start(arena, slice_index);
  if (!mi_page_try_claim_ownership(page))
  {
    *keep_abandoned = 1;
    return 0;
  }
  if (heap_tag != page->heap_tag)
  {
    const bool freed = _mi_page_unown(page);
    *keep_abandoned = !freed;
    return 0;
  }
  *keep_abandoned = 0;
  return 1;
}

static mi_page_t *mi_arenas_page_try_find_abandoned(mi_subproc_t *subproc, size_t slice_count, size_t block_size, mi_arena_t *req_arena, mi_heaptag_t heaptag, size_t tseq)
{
  (void) slice_count;
  const size_t bin = _mi_bin(block_size);
  (bin < ((73U + 1) + 1)) ? ((void) 0) : (_mi_assert_fail("bin < MI_BIN_COUNT", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 542, __func__));
  (subproc != 0) ? ((void) 0) : (_mi_assert_fail("subproc != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 545, __func__));
  if (atomic_load_explicit(&subproc->abandoned_count[bin], memory_order_relaxed) == 0)
  {
    return 0;
  }
  const bool allow_large = 1;
  const int any_numa = -1;
  const bool match_numa = 1;
  {
    const size_t _arena_count = mi_arenas_get_count(subproc);
    const size_t _arena_cycle = (_arena_count == 0) ? (0) : (_arena_count - 1);
    size_t _start = (_arena_cycle <= 1) ? (0) : (tseq % _arena_cycle);
    for (size_t _i = 0; _i < _arena_count; _i += 1)
    {
      mi_arena_t *arena;
      unsigned int arena_idx = 0;
      if (req_arena != 0)
      {
        arena_idx = req_arena;
        if (_i > 0)
        {
          break;
        }
      }
      else
      {
        size_t _idx;
        if (_i < _arena_cycle)
        {
          _idx = _i + _start;
          if (_idx >= _arena_cycle)
          {
            _idx -= _arena_cycle;
          }
        }
        else
        {
          _idx = _i;
        }
        arena_idx = mi_arena_from_index(subproc, _idx);
      }
      if ((&arena[arena_idx]) != 0)
      {
        {
          if (mi_arena_is_suitable(arena, req_arena, match_numa, any_numa, allow_large))
          {
            {
              size_t slice_index;
              mi_bitmap_t * const bitmap = arena->pages_abandoned[bin];
              if (mi_bitmap_try_find_and_claim(bitmap, tseq, &slice_index, &mi_arena_try_claim_abandoned, arena, heaptag))
              {
                mi_page_t *page = (mi_page_t *) mi_arena_slice_start(arena, slice_index);
                (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 563, __func__));
                (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 564, __func__));
                (mi_arena_has_page(arena, page)) ? ((void) 0) : (_mi_assert_fail("mi_arena_has_page(arena,page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 565, __func__));
                atomic_fetch_sub_explicit(&subproc->abandoned_count[bin], (uintptr_t) 1, memory_order_relaxed);
                mi_tld_t *tld = _mi_thread_tld();
                __mi_stat_decrease(&tld->stats.pages_abandoned, 1);
                __mi_stat_counter_increase(&tld->stats.pages_reclaim_on_alloc, 1);
                _mi_page_free_collect(page, 0);
                (mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 572, __func__));
                ((page->slice_committed > 0) || mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("page->slice_committed > 0 || mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 573, __func__));
                (mi_bitmap_is_setN(arena->slices_dirty, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_setN(arena->slices_dirty, slice_index, slice_count)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 574, __func__));
                (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 575, __func__));
                (_mi_ptr_page(page) == page) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 576, __func__));
                (_mi_ptr_page(mi_page_start(page)) == page) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(mi_page_start(page))==page", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 577, __func__));
                (mi_page_block_size(page) == block_size) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) == block_size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 578, __func__));
                (!mi_page_is_full(page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_is_full(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 579, __func__));
                return page;
              }
            }
          }
        }
      }
    }

  }
  ;
  return 0;
}

static mi_page_t *mi_arenas_page_alloc_fresh(size_t slice_count, size_t block_size, size_t block_alignment, mi_arena_t *req_arena, int numa_node, bool commit, mi_tld_t *tld)
{
  const bool allow_large = 0 < 2;
  const bool os_align = block_alignment > (1UL << (13 + 3));
  const size_t page_alignment = 1UL << (13 + 3);
  mi_memid_t memid = _mi_memid_none();
  mi_page_t *page = 0;
  unsigned int page_idx = 0;
  const size_t alloc_size = mi_size_of_slices(slice_count);
  if (((!mi_option_is_enabled(mi_option_disallow_arena_alloc)) && (!os_align)) && (slice_count <= (1 << (6 + 3))))
  {
    page_idx = (mi_page_t *) mi_arenas_try_alloc(tld->subproc, slice_count, page_alignment, commit, allow_large, req_arena, tld->thread_seq, numa_node, &memid);
    if ((&page[page_idx]) != 0)
    {
      (mi_bitmap_is_clearN(memid.mem.arena.arena->pages, memid.mem.arena.slice_index, memid.mem.arena.slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_clearN(memid.mem.arena.arena->pages, memid.mem.arena.slice_index, memid.mem.arena.slice_count)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 605, __func__));
      mi_bitmap_set(memid.mem.arena.arena->pages, memid.mem.arena.slice_index);
    }
  }
  if ((&page[page_idx]) == 0)
  {
    if (os_align)
    {
      (slice_count >= (mi_slice_count_of_size(block_size) + mi_slice_count_of_size(page_alignment))) ? ((void) 0) : (_mi_assert_fail("slice_count >= mi_slice_count_of_size(block_size) + mi_slice_count_of_size(page_alignment)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 614, __func__));
      page_idx = (mi_page_t *) mi_arena_os_alloc_aligned(alloc_size, block_alignment, page_alignment, commit, allow_large, req_arena, &memid);
    }
    else
    {
      page_idx = (mi_page_t *) mi_arena_os_alloc_aligned(alloc_size, page_alignment, 0, commit, allow_large, req_arena, &memid);
    }
  }
  if ((&page[page_idx]) == 0)
  {
    return 0;
  }
  (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 623, __func__));
  ((!os_align) || _mi_is_aligned(((uint8_t *) page) + page_alignment, block_alignment)) ? ((void) 0) : (_mi_assert_fail("!os_align || _mi_is_aligned((uint8_t*)page + page_alignment, block_alignment)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 624, __func__));
  const size_t page_noguard_size = alloc_size;
  if ((!memid.initially_zero) && memid.initially_committed)
  {
    ;
    _mi_memzero_aligned(page, sizeof(*(&page[page_idx])));
  }
  else
    if (memid.initially_committed)
  {
    ;
  }
  if (memid.initially_zero && memid.initially_committed)
  {
    if (!mi_mem_is_zero(page, page_noguard_size))
    {
      _mi_error_message(14, "internal error: page memory was not zero initialized.\n");
      memid.initially_zero = 0;
      _mi_memzero_aligned(page, sizeof(*(&page[page_idx])));
    }
  }
  (((3 + 2) * 32) >= mi_page_info_size()) ? ((void) 0) : (_mi_assert_fail("MI_PAGE_INFO_SIZE >= mi_page_info_size()", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 654, __func__));
  size_t block_start;
  if (os_align)
  {
    block_start = 1UL << (13 + 3);
  }
  else
    if (_mi_is_power_of_two(block_size) && (block_size <= 1024UL))
  {
    block_start = _mi_align_up(mi_page_info_size(), block_size);
  }
  else
  {
    block_start = mi_page_info_size();
  }
  const size_t reserved = (os_align) ? (1) : ((page_noguard_size - block_start) / block_size);
  ((reserved > 0) && (reserved <= UINT16_MAX)) ? ((void) 0) : (_mi_assert_fail("reserved > 0 && reserved <= UINT16_MAX", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 679, __func__));
  size_t commit_size = 0;
  if (!memid.initially_committed)
  {
    commit_size = _mi_align_up(block_start + block_size, 1UL << (13 + 3));
    if (commit_size > page_noguard_size)
    {
      commit_size = page_noguard_size;
    }
    bool is_zero;
    if (__builtin_expect(!(!(!mi_arena_commit(mi_memid_arena(memid), page, commit_size, &is_zero, 0))), 0))
    {
      _mi_arenas_free(page, alloc_size, memid);
      return 0;
    }
    if ((!memid.initially_zero) && (!is_zero))
    {
      _mi_memzero_aligned(page, commit_size);
    }
  }
  page->reserved = (uint16_t) reserved;
  page->page_start = ((uint8_t *) page) + block_start;
  page->block_size = block_size;
  page->slice_committed = commit_size;
  page->memid = memid;
  page->free_is_zero = memid.initially_zero;
  mi_page_try_claim_ownership(page);
  if (__builtin_expect(!(!(!_mi_page_map_register(page))), 0))
  {
    _mi_arenas_free(page, alloc_size, memid);
    return 0;
  }
  __mi_stat_increase(&tld->stats.pages, 1);
  __mi_stat_increase(&tld->stats.page_bins[_mi_page_bin(page)], 1);
  (_mi_ptr_page(page) == (&page[page_idx])) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 717, __func__));
  (_mi_ptr_page(mi_page_start(page)) == (&page[page_idx])) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(mi_page_start(page))==page", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 718, __func__));
  (mi_page_block_size(page) == block_size) ? ((void) 0) : (_mi_assert_fail("mi_page_block_size(page) == block_size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 719, __func__));
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 720, __func__));
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 721, __func__));
  return page;
}

static mi_page_t *mi_arenas_page_regular_alloc(mi_heap_t *heap, size_t slice_count, size_t block_size)
{
  mi_arena_t *req_arena = heap->exclusive_arena;
  mi_tld_t * const tld = heap->tld;
  mi_page_t *page = mi_arenas_page_try_find_abandoned(tld->subproc, slice_count, block_size, req_arena, heap->tag, tld->thread_seq);
  unsigned int page_idx = 0;
  if ((&page[page_idx]) != 0)
  {
    return page;
  }
  const long commit_on_demand = mi_option_get(mi_option_page_commit_on_demand);
  const bool commit = ((slice_count <= mi_slice_count_of_size(1UL << (13 + 3))) || ((commit_on_demand == 2) && _mi_os_has_overcommit())) || (commit_on_demand == 0);
  page_idx = mi_arenas_page_alloc_fresh(slice_count, block_size, 1, req_arena, heap->numa_node, commit, tld);
  if ((&page[page_idx]) == 0)
  {
    return 0;
  }
  ((page->memid.memkind != MI_MEM_ARENA) || (page->memid.mem.arena.slice_count == slice_count)) ? ((void) 0) : (_mi_assert_fail("page->memid.memkind != MI_MEM_ARENA || page->memid.mem.arena.slice_count == slice_count", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 744, __func__));
  if (!_mi_page_init(heap, page))
  {
    _mi_arenas_free(page, mi_page_full_size(page), page->memid);
    return 0;
  }
  return page;
}

static mi_page_t *mi_arenas_page_singleton_alloc(mi_heap_t *heap, size_t block_size, size_t block_alignment)
{
  mi_arena_t *req_arena = heap->exclusive_arena;
  mi_tld_t * const tld = heap->tld;
  const bool os_align = block_alignment > (1UL << (13 + 3));
  const size_t info_size = (os_align) ? (1UL << (13 + 3)) : (mi_page_info_size());
  const size_t slice_count = mi_slice_count_of_size(info_size + block_size);
  mi_page_t *page = mi_arenas_page_alloc_fresh(slice_count, block_size, block_alignment, req_arena, heap->numa_node, 1, tld);
  if (page == 0)
  {
    return 0;
  }
  (page->reserved == 1) ? ((void) 0) : (_mi_assert_fail("page->reserved == 1", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 768, __func__));
  if (!_mi_page_init(heap, page))
  {
    _mi_arenas_free(page, mi_page_full_size(page), page->memid);
    return 0;
  }
  return page;
}

mi_page_t *_mi_arenas_page_alloc(mi_heap_t *heap, size_t block_size, size_t block_alignment)
{
  mi_page_t *page;
  unsigned int page_idx = 0;
  if (__builtin_expect(!(!(block_alignment > (1UL << (13 + 3)))), 0))
  {
    (_mi_is_power_of_two(block_alignment)) ? ((void) 0) : (_mi_assert_fail("_mi_is_power_of_two(block_alignment)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 781, __func__));
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
  (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 799, __func__));
  (_mi_ptr_page(page) == (&page[page_idx])) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 800, __func__));
  (_mi_ptr_page(mi_page_start(page)) == (&page[page_idx])) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(mi_page_start(page))==page", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 801, __func__));
  ((block_alignment <= (1UL << (13 + 3))) || _mi_is_aligned(mi_page_start(page), block_alignment)) ? ((void) 0) : (_mi_assert_fail("block_alignment <= MI_PAGE_MAX_OVERALLOC_ALIGN || _mi_is_aligned(mi_page_start(page), block_alignment)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 802, __func__));
  return page;
}

void _mi_arenas_page_free(mi_page_t *page, mi_tld_t *stats_tld)
{
  (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 808, __func__));
  (_mi_ptr_page(page) == page) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 809, __func__));
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 810, __func__));
  (mi_page_all_free(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_all_free(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 811, __func__));
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 812, __func__));
  ((page->next == 0) && (page->prev == 0)) ? ((void) 0) : (_mi_assert_fail("page->next==NULL && page->prev==NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 813, __func__));
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
    (mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 830, __func__));
    ((page->slice_committed > 0) || mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("page->slice_committed > 0 || mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 831, __func__));
    (mi_bitmap_is_clearN(arena->pages_abandoned[bin], slice_index, 1)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_clearN(arena->pages_abandoned[bin], slice_index, 1)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 832, __func__));
    (mi_bitmap_is_setN(page->memid.mem.arena.arena->pages, page->memid.mem.arena.slice_index, 1)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_setN(page->memid.mem.arena.arena->pages, page->memid.mem.arena.slice_index, 1)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 833, __func__));
  }
  _mi_page_map_unregister(page);
  if (page->memid.memkind == MI_MEM_ARENA)
  {
    mi_arena_t * const arena = page->memid.mem.arena.arena;
    mi_bitmap_clear(arena->pages, page->memid.mem.arena.slice_index);
    if (page->slice_committed > 0)
    {
      (mi_page_full_size(page) >= page->slice_committed) ? ((void) 0) : (_mi_assert_fail("mi_page_full_size(page) >= page->slice_committed", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 855, __func__));
      const size_t total_slices = page->slice_committed / (1UL << (13 + 3));
      (page->memid.mem.arena.slice_count >= total_slices) ? ((void) 0) : (_mi_assert_fail("page->memid.mem.arena.slice_count >= total_slices", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 858, __func__));
      if (total_slices > 0)
      {
        mi_bitmap_setN(arena->slices_committed, page->memid.mem.arena.slice_index, total_slices, 0);
      }
      const size_t extra = page->slice_committed % (1UL << (13 + 3));
      if (extra > 0)
      {
        __mi_stat_decrease_mt(&_mi_subproc()->stats.committed, extra);
      }
    }
    else
    {
      (mi_bitmap_is_setN(arena->slices_committed, page->memid.mem.arena.slice_index, page->memid.mem.arena.slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_setN(arena->slices_committed, page->memid.mem.arena.slice_index, page->memid.mem.arena.slice_count)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 870, __func__));
    }
  }
  _mi_arenas_free(page, mi_page_full_size(page), page->memid);
}

void _mi_arenas_page_abandon(mi_page_t *page, mi_tld_t *tld)
{
  (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 881, __func__));
  (_mi_ptr_page(page) == page) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 882, __func__));
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 883, __func__));
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 884, __func__));
  (!mi_page_all_free(page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_all_free(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 885, __func__));
  ((page->next == 0) && (page->prev == 0)) ? ((void) 0) : (_mi_assert_fail("page->next==NULL && page->prev == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 886, __func__));
  if ((page->memid.memkind == MI_MEM_ARENA) && (!mi_page_is_full(page)))
  {
    size_t bin = _mi_bin(mi_page_block_size(page));
    size_t slice_index;
    size_t slice_count;
    mi_arena_t *arena = mi_page_arena(page, &slice_index, &slice_count);
    (!mi_page_is_singleton(page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_is_singleton(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 894, __func__));
    (mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 895, __func__));
    ((page->slice_committed > 0) || mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("page->slice_committed > 0 || mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 896, __func__));
    (mi_bitmap_is_setN(arena->slices_dirty, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_setN(arena->slices_dirty, slice_index, slice_count)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 897, __func__));
    mi_page_set_abandoned_mapped(page);
    const bool wasclear = mi_bitmap_set(arena->pages_abandoned[bin], slice_index);
    (void) wasclear;
    (wasclear) ? ((void) 0) : (_mi_assert_fail("wasclear", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 901, __func__));
    atomic_fetch_add_explicit(&arena->subproc->abandoned_count[bin], (uintptr_t) 1, memory_order_relaxed);
    __mi_stat_increase(&tld->stats.pages_abandoned, 1);
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

bool _mi_arenas_page_try_reabandon_to_mapped(mi_page_t *page)
{
  (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 925, __func__));
  (_mi_ptr_page(page) == page) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 926, __func__));
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 927, __func__));
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 928, __func__));
  (!mi_page_is_abandoned_mapped(page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_is_abandoned_mapped(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 929, __func__));
  (!mi_page_is_full(page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_is_full(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 930, __func__));
  (!mi_page_all_free(page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_all_free(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 931, __func__));
  (!mi_page_is_singleton(page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_is_singleton(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 932, __func__));
  if ((mi_page_is_full(page) || mi_page_is_abandoned_mapped(page)) || (page->memid.memkind != MI_MEM_ARENA))
  {
    return 0;
  }
  else
  {
    mi_tld_t *tld = _mi_thread_tld();
    __mi_stat_counter_increase(&tld->stats.pages_reabandon_full, 1);
    __mi_stat_adjust_decrease(&tld->stats.pages_abandoned, 1);
    _mi_arenas_page_abandon(page, tld);
    return 1;
  }
}

void _mi_arenas_page_unabandon(mi_page_t *page)
{
  (_mi_is_aligned(page, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 947, __func__));
  (_mi_ptr_page(page) == page) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 948, __func__));
  (mi_page_is_owned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_owned(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 949, __func__));
  (mi_page_is_abandoned(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 950, __func__));
  if (mi_page_is_abandoned_mapped(page))
  {
    (page->memid.memkind == MI_MEM_ARENA) ? ((void) 0) : (_mi_assert_fail("page->memid.memkind==MI_MEM_ARENA", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 953, __func__));
    size_t bin = _mi_bin(mi_page_block_size(page));
    size_t slice_index;
    size_t slice_count;
    mi_arena_t *arena = mi_page_arena(page, &slice_index, &slice_count);
    (mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 960, __func__));
    ((page->slice_committed > 0) || mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("page->slice_committed > 0 || mi_bitmap_is_setN(arena->slices_committed, slice_index, slice_count)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 961, __func__));
    mi_bitmap_clear_once_set(arena->pages_abandoned[bin], slice_index);
    mi_page_clear_abandoned_mapped(page);
    atomic_fetch_sub_explicit(&arena->subproc->abandoned_count[bin], (uintptr_t) 1, memory_order_relaxed);
    __mi_stat_decrease(&_mi_thread_tld()->stats.pages_abandoned, 1);
  }
  else
  {
    __mi_stat_decrease(&_mi_thread_tld()->stats.pages_abandoned, 1);
    if ((page->memid.memkind != MI_MEM_ARENA) && mi_option_is_enabled(mi_option_visit_abandoned))
    {
      mi_subproc_t *subproc = _mi_subproc();
      for (bool _go = (mi_lock_acquire(&subproc->os_abandoned_pages_lock), 1); _go; mi_lock_release(&subproc->os_abandoned_pages_lock), _go = 0)
      {
        if (page->prev != 0)
        {
          page->prev->next = page->next;
        }
        if (page->next != 0)
        {
          page->next->prev = page->prev;
        }
        if (subproc->os_abandoned_pages == page)
        {
          subproc->os_abandoned_pages = page->next;
        }
        page->next = 0;
        page->prev = 0;
      }

    }
  }
}

static void mi_arena_schedule_purge(mi_arena_t *arena, size_t slice_index, size_t slices);
static void mi_arenas_try_purge(bool force, bool visit_all, mi_subproc_t *subproc, size_t tseq);
void _mi_arenas_free(void *p, size_t size, mi_memid_t memid)
{
  if (p == 0)
  {
    return;
  }
  if (size == 0)
  {
    return;
  }
  ;
  if (mi_memkind_is_os(memid.memkind))
  {
    _mi_os_free(p, size, memid);
  }
  else
    if (memid.memkind == MI_MEM_ARENA)
  {
    size_t slice_count;
    size_t slice_index;
    mi_arena_t *arena = mi_arena_from_memid(memid, &slice_index, &slice_count);
    ((size % (1UL << (13 + 3))) == 0) ? ((void) 0) : (_mi_assert_fail("(size%MI_ARENA_SLICE_SIZE)==0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 1009, __func__));
    ((slice_count * (1UL << (13 + 3))) == size) ? ((void) 0) : (_mi_assert_fail("(slice_count*MI_ARENA_SLICE_SIZE)==size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 1010, __func__));
    (mi_arena_slice_start(arena, slice_index) <= ((uint8_t *) p)) ? ((void) 0) : (_mi_assert_fail("mi_arena_slice_start(arena,slice_index) <= (uint8_t*)p", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 1011, __func__));
    ((mi_arena_slice_start(arena, slice_index) + mi_size_of_slices(slice_count)) > ((uint8_t *) p)) ? ((void) 0) : (_mi_assert_fail("mi_arena_slice_start(arena,slice_index) + mi_size_of_slices(slice_count) > (uint8_t*)p", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 1012, __func__));
    if (arena == 0)
    {
      _mi_error_message(22, "trying to free from an invalid arena: %p, size %zu, memid: 0x%zx\n", p, size, memid);
      return;
    }
    (slice_index < arena->slice_count) ? ((void) 0) : (_mi_assert_fail("slice_index < arena->slice_count", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 1018, __func__));
    (slice_index >= mi_arena_info_slices(arena)) ? ((void) 0) : (_mi_assert_fail("slice_index >= mi_arena_info_slices(arena)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 1019, __func__));
    if ((slice_index < mi_arena_info_slices(arena)) || (slice_index > arena->slice_count))
    {
      _mi_error_message(22, "trying to free from an invalid arena block: %p, size %zu, memid: 0x%zx\n", p, size, memid);
      return;
    }
    if (!arena->memid.is_pinned)
    {
      mi_arena_schedule_purge(arena, slice_index, slice_count);
    }
    bool all_inuse = mi_bbitmap_setN(arena->slices_free, slice_index, slice_count);
    if (!all_inuse)
    {
      _mi_error_message(11, "trying to free an already freed arena block: %p, size %zu\n", mi_arena_slice_start(arena, slice_index), mi_size_of_slices(slice_count));
      return;
    }
    ;
  }
  else
    if (memid.memkind == MI_MEM_META)
  {
    _mi_meta_free(p, size, memid);
  }
  else
  {
    (mi_memid_needs_no_free(memid)) ? ((void) 0) : (_mi_assert_fail("mi_memid_needs_no_free(memid)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 1043, __func__));
  }
}

void _mi_arenas_collect(bool force_purge, bool visit_all, mi_tld_t *tld)
{
  mi_arenas_try_purge(force_purge, visit_all, tld->subproc, tld->thread_seq);
}

bool mi_arena_contains(mi_arena_id_t arena_id, const void *p)
{
  mi_arena_t *arena = _mi_arena_from_id(arena_id);
  return (mi_arena_start(arena) <= ((const uint8_t *) p)) && ((mi_arena_start(arena) + mi_size_of_slices(arena->slice_count)) > ((const uint8_t *) p));
}

bool _mi_arenas_contain(const void *p)
{
  mi_subproc_t *subproc = _mi_subproc();
  const size_t max_arena = mi_arenas_get_count(subproc);
  for (size_t i = 0; i < max_arena; i += 1)
  {
    mi_arena_t *arena = atomic_load_explicit(&subproc->arenas[i], memory_order_acquire);
    if ((arena != 0) && mi_arena_contains(arena, p))
    {
      return 1;
    }
  }

  return 0;
}

static void mi_arenas_unsafe_destroy(mi_subproc_t *subproc)
{
  (subproc != 0) ? ((void) 0) : (_mi_assert_fail("subproc != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 1085, __func__));
  const size_t arena_count = mi_arenas_get_count(subproc);
  for (size_t i = 0; i < arena_count; i += 1)
  {
    mi_arena_t *arena = atomic_load_explicit(&subproc->arenas[i], memory_order_acquire);
    if (arena != 0)
    {
      atomic_store_explicit(&subproc->arenas[i], 0, memory_order_release);
      if (mi_memkind_is_os(arena->memid.memkind))
      {
        _mi_os_free_ex(mi_arena_start(arena), mi_arena_size(arena), 1, arena->memid, subproc);
      }
    }
  }

  size_t expected = arena_count;
  atomic_compare_exchange_strong_explicit(&subproc->arena_count, &expected, 0, memory_order_acq_rel, memory_order_acquire);
}

void _mi_arenas_unsafe_destroy_all(mi_subproc_t *subproc)
{
  mi_arenas_unsafe_destroy(subproc);
}

static bool mi_arenas_add(mi_subproc_t *subproc, mi_arena_t *arena, mi_arena_id_t *arena_id)
{
  (arena != 0) ? ((void) 0) : (_mi_assert_fail("arena != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 1116, __func__));
  (arena->slice_count > 0) ? ((void) 0) : (_mi_assert_fail("arena->slice_count > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 1117, __func__));
  if (arena_id != 0)
  {
    *arena_id = 0;
  }
  const size_t count = mi_arenas_get_count(subproc);
  size_t i;
  for (i = 0; i < count; i += 1)
  {
    if (mi_arena_from_index(subproc, i) == 0)
    {
      mi_arena_t *expected = 0;
      if (atomic_compare_exchange_strong_explicit(&subproc->arenas[i], &expected, arena, memory_order_release, memory_order_relaxed))
      {
        if (arena_id != 0)
        {
          *arena_id = arena;
        }
        return 1;
      }
    }
  }

  i = atomic_fetch_add_explicit(&subproc->arena_count, (uintptr_t) 1, memory_order_acq_rel);
  if (i >= 160)
  {
    atomic_fetch_sub_explicit(&subproc->arena_count, (uintptr_t) 1, memory_order_acq_rel);
    arena->subproc = 0;
    return 0;
  }
  __mi_stat_counter_increase_mt(&arena->subproc->stats.arena_count, 1);
  atomic_store_explicit(&subproc->arenas[i], arena, memory_order_release);
  if (arena_id != 0)
  {
    *arena_id = arena;
  }
  return 1;
}

static size_t mi_arena_info_slices_needed(size_t slice_count, size_t *bitmap_base)
{
  if (slice_count == 0)
  {
    slice_count = 1 << (6 + 3);
  }
  ((slice_count % (1 << (6 + 3))) == 0) ? ((void) 0) : (_mi_assert_fail("(slice_count % MI_BCHUNK_BITS) == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 1150, __func__));
  const size_t base_size = _mi_align_up(sizeof(mi_arena_t), (1 << (6 + 3)) / 8);
  const size_t bitmaps_count = 4 + ((73U + 1) + 1);
  const size_t bitmaps_size = (bitmaps_count * mi_bitmap_size(slice_count, 0)) + mi_bbitmap_size(slice_count, 0);
  const size_t size = base_size + bitmaps_size;
  const size_t os_page_size = _mi_os_page_size();
  const size_t info_size = _mi_align_up(size, os_page_size) + _mi_os_secure_guard_page_size();
  const size_t info_slices = mi_slice_count_of_size(info_size);
  if (bitmap_base != 0)
  {
    *bitmap_base = base_size;
  }
  return info_slices;
}

static mi_bitmap_t *mi_arena_bitmap_init(size_t slice_count, uint8_t **base)
{
  mi_bitmap_t *bitmap = (mi_bitmap_t *) (*base);
  *base = (*base) + mi_bitmap_init(bitmap, slice_count, 1);
  return bitmap;
}

static mi_bbitmap_t *mi_arena_bbitmap_init(size_t slice_count, uint8_t **base)
{
  mi_bbitmap_t *bbitmap = (mi_bbitmap_t *) (*base);
  *base = (*base) + mi_bbitmap_init(bbitmap, slice_count, 1);
  return bbitmap;
}

static bool mi_manage_os_memory_ex2(mi_subproc_t *subproc, void *start, size_t size, int numa_node, bool exclusive, mi_memid_t memid, mi_commit_fun_t *commit_fun, void *commit_fun_arg, mi_arena_id_t *arena_id)
{
  unsigned int start_idx = 0;
  (_mi_is_aligned(start, 1UL << (13 + 3))) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(start,MI_ARENA_SLICE_SIZE)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 1180, __func__));
  ((&start[start_idx]) != 0) ? ((void) 0) : (_mi_assert_fail("start!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 1181, __func__));
  if (arena_id != 0)
  {
    *arena_id = _mi_arena_id_none();
  }
  if ((&start[start_idx]) == 0)
  {
    return 0;
  }
  if (!_mi_is_aligned(start, 1UL << (13 + 3)))
  {
    void * const aligned_start = _mi_align_up_ptr(start, 1UL << (13 + 3));
    const size_t diff = ((uint8_t *) aligned_start) - ((uint8_t *) start);
    if ((diff >= size) || ((size - diff) < (1UL << (13 + 3))))
    {
      _mi_warning_message("after alignment, the size of the arena becomes too small (memory at %p with size %zu)\n", start, size);
      return 0;
    }
    start_idx = aligned_start;
    size = size - diff;
  }
  const size_t slice_count = _mi_align_down(size / (1UL << (13 + 3)), 1 << (6 + 3));
  if (slice_count > ((1 << (6 + 3)) * (1 << (6 + 3))))
  {
    _mi_warning_message("cannot use OS memory since it is too large (size %zu MiB, maximum is %zu MiB)", size / (1024UL * 1024UL), mi_size_of_slices((1 << (6 + 3)) * (1 << (6 + 3))) / (1024UL * 1024UL));
    return 0;
  }
  size_t bitmap_base;
  const size_t info_slices = mi_arena_info_slices_needed(slice_count, &bitmap_base);
  if (slice_count < (info_slices + 1))
  {
    _mi_warning_message("cannot use OS memory since it is not large enough (size %zu KiB, minimum required is %zu KiB)", size / 1024UL, mi_size_of_slices(info_slices + 1) / 1024UL);
    return 0;
  }
  else
    if (info_slices >= (1 << (6 + 3)))
  {
    _mi_warning_message("cannot use OS memory since it is too large with respect to the maximum object size (size %zu MiB, meta-info slices %zu, maximum object slices are %zu)", size / (1024UL * 1024UL), info_slices, 1 << (6 + 3));
    return 0;
  }
  mi_arena_t *arena = (mi_arena_t *) start;
  if (!memid.initially_committed)
  {
    size_t commit_size = mi_size_of_slices(info_slices);
    if (!memid.is_pinned)
    {
      commit_size -= _mi_os_secure_guard_page_size();
    }
    bool ok = 0;
    if (commit_fun != 0)
    {
      ok = (*commit_fun)(1, arena, commit_size, 0, commit_fun_arg);
    }
    else
    {
      ok = _mi_os_commit(arena, commit_size, 0);
    }
    if (!ok)
    {
      _mi_warning_message("unable to commit meta-data for OS memory");
      return 0;
    }
  }
  else
    if (!memid.is_pinned)
  {
    _mi_os_secure_guard_page_set_before(((uint8_t *) arena) + mi_size_of_slices(info_slices), memid);
  }
  if (!memid.initially_zero)
  {
    _mi_memzero(arena, mi_size_of_slices(info_slices) - _mi_os_secure_guard_page_size());
  }
  arena->subproc = subproc;
  arena->memid = memid;
  arena->is_exclusive = exclusive;
  arena->slice_count = slice_count;
  arena->info_slices = info_slices;
  arena->numa_node = numa_node;
  arena->purge_expire = 0;
  arena->commit_fun = commit_fun;
  arena->commit_fun_arg = commit_fun_arg;
  uint8_t *base = mi_arena_start(arena) + bitmap_base;
  arena->slices_free = mi_arena_bbitmap_init(slice_count, &base);
  arena->slices_committed = mi_arena_bitmap_init(slice_count, &base);
  arena->slices_dirty = mi_arena_bitmap_init(slice_count, &base);
  arena->slices_purge = mi_arena_bitmap_init(slice_count, &base);
  arena->pages = mi_arena_bitmap_init(slice_count, &base);
  for (size_t i = 0; i < ((73U + 1) + 1); i += 1)
  {
    arena->pages_abandoned[i] = mi_arena_bitmap_init(slice_count, &base);
  }

  (mi_size_of_slices(info_slices) >= ((size_t) (base - mi_arena_start(arena)))) ? ((void) 0) : (_mi_assert_fail("mi_size_of_slices(info_slices) >= (size_t)(base - mi_arena_start(arena))", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 1263, __func__));
  mi_bbitmap_unsafe_setN(arena->slices_free, info_slices, arena->slice_count - info_slices);
  if (memid.initially_committed)
  {
    mi_bitmap_unsafe_setN(arena->slices_committed, 0, arena->slice_count);
  }
  else
  {
    mi_bitmap_setN(arena->slices_committed, 0, info_slices, 0);
  }
  if (!memid.initially_zero)
  {
    mi_bitmap_unsafe_setN(arena->slices_dirty, 0, arena->slice_count);
  }
  else
  {
    mi_bitmap_setN(arena->slices_dirty, 0, info_slices, 0);
  }
  return mi_arenas_add(subproc, arena, arena_id);
}

bool mi_manage_os_memory_ex(void *start, size_t size, bool is_committed, bool is_pinned, bool is_zero, int numa_node, bool exclusive, mi_arena_id_t *arena_id)
{
  mi_memid_t memid = _mi_memid_create(MI_MEM_EXTERNAL);
  memid.mem.os.base = start;
  memid.mem.os.size = size;
  memid.initially_committed = is_committed;
  memid.initially_zero = is_zero;
  memid.is_pinned = is_pinned;
  return mi_manage_os_memory_ex2(_mi_subproc(), start, size, numa_node, exclusive, memid, 0, 0, arena_id);
}

bool mi_manage_memory(void *start, size_t size, bool is_committed, bool is_zero, bool is_pinned, int numa_node, bool exclusive, mi_commit_fun_t *commit_fun, void *commit_fun_arg, mi_arena_id_t *arena_id)
{
  mi_memid_t memid = _mi_memid_create(MI_MEM_EXTERNAL);
  memid.mem.os.base = start;
  memid.mem.os.size = size;
  memid.initially_committed = is_committed;
  memid.initially_zero = is_zero;
  memid.is_pinned = is_pinned;
  return mi_manage_os_memory_ex2(_mi_subproc(), start, size, numa_node, exclusive, memid, commit_fun, commit_fun_arg, arena_id);
}

static int mi_reserve_os_memory_ex2(mi_subproc_t *subproc, size_t size, bool commit, bool allow_large, bool exclusive, mi_arena_id_t *arena_id)
{
  if (arena_id != 0)
  {
    *arena_id = _mi_arena_id_none();
  }
  size = _mi_align_up(size, 1UL << (13 + 3));
  mi_memid_t memid;
  void *start = _mi_os_alloc_aligned(size, 1UL << (13 + 3), commit, allow_large, &memid);
  if (start == 0)
  {
    return 12;
  }
  if (!mi_manage_os_memory_ex2(subproc, start, size, -1, exclusive, memid, 0, 0, arena_id))
  {
    _mi_os_free_ex(start, size, commit, memid, 0);
    _mi_verbose_message("failed to reserve %zu KiB memory\n", _mi_divide_up(size, 1024));
    return 12;
  }
  _mi_verbose_message("reserved %zu KiB memory%s\n", _mi_divide_up(size, 1024), (memid.is_pinned) ? (" (in large os pages)") : (""));
  return 0;
}

int mi_reserve_os_memory_ex(size_t size, bool commit, bool allow_large, bool exclusive, mi_arena_id_t *arena_id)
{
  return mi_reserve_os_memory_ex2(_mi_subproc(), size, commit, allow_large, exclusive, arena_id);
}

bool mi_manage_os_memory(void *start, size_t size, bool is_committed, bool is_large, bool is_zero, int numa_node)
{
  return mi_manage_os_memory_ex(start, size, is_committed, is_large, is_zero, numa_node, 0, 0);
}

int mi_reserve_os_memory(size_t size, bool commit, bool allow_large)
{
  return mi_reserve_os_memory_ex(size, commit, allow_large, 0, 0);
}

static size_t mi_arena_used_slices(mi_arena_t *arena)
{
  size_t idx;
  if (mi_bitmap_bsr(arena->pages, &idx))
  {
    mi_page_t *page = (mi_page_t *) mi_arena_slice_start(arena, idx);
    const size_t page_slice_count = page->memid.mem.arena.slice_count;
    return idx + page_slice_count;
  }
  else
  {
    return mi_arena_info_slices(arena);
  }
}

static size_t mi_debug_show_bfield(mi_bfield_t field, char *buf, size_t *k)
{
  unsigned int k_idx = 0;
  size_t bit_set_count = 0;
  for (int bit = 0; bit < (1 << (3 + 3)); bit += 1)
  {
    bool is_set = ((((mi_bfield_t) 1) << bit) & field) != 0;
    if (is_set)
    {
      bit_set_count += 1;
    }
    buf[k[k_idx]] = (is_set) ? ('x') : ('.');
    k_idx += 1;
  }

  return bit_set_count;
}

typedef enum mi_ansi_color_e
{
  MI_BLACK = 30,
  MI_MAROON,
  MI_DARKGREEN,
  MI_ORANGE,
  MI_NAVY,
  MI_PURPLE,
  MI_TEAL,
  MI_GRAY,
  MI_DARKGRAY = 90,
  MI_RED,
  MI_GREEN,
  MI_YELLOW,
  MI_BLUE,
  MI_MAGENTA,
  MI_CYAN,
  MI_WHITE
} mi_ansi_color_t;
static void mi_debug_color(char *buf, size_t *k, mi_ansi_color_t color)
{
  *k += _mi_snprintf(buf + (*k), 32, "\x1B[%dm", (int) color);
}

static int mi_page_commit_usage(mi_page_t *page)
{
  const size_t committed_size = mi_page_committed(page);
  const size_t used_size = page->used * mi_page_block_size(page);
  return (int) ((used_size * 100) / committed_size);
}

static size_t mi_debug_show_page_bfield(mi_bfield_t field, char *buf, size_t *k, mi_arena_t *arena, size_t slice_index, long *pbit_of_page, mi_ansi_color_t *pcolor_of_page)
{
  size_t bit_set_count = 0;
  long bit_of_page = *pbit_of_page;
  mi_ansi_color_t color = *pcolor_of_page;
  mi_ansi_color_t prev_color = MI_GRAY;
  for (int bit = 0; bit < (1 << (3 + 3)); bit += 1, bit_of_page -= 1)
  {
    bool is_set = ((((mi_bfield_t) 1) << bit) & field) != 0;
    void *start = mi_arena_slice_start(arena, slice_index + bit);
    char c = ' ';
    if (is_set)
    {
      (bit_of_page <= 0) ? ((void) 0) : (_mi_assert_fail("bit_of_page <= 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 1407, __func__));
      bit_set_count += 1;
      c = 'p';
      color = MI_GRAY;
      mi_page_t *page = (mi_page_t *) start;
      if (mi_page_is_singleton(page))
      {
        c = 's';
      }
      else
        if (mi_page_is_full(page))
      {
        c = 'f';
      }
      if (!mi_page_is_abandoned(page))
      {
        c = _mi_toupper(c);
      }
      int commit_usage = mi_page_commit_usage(page);
      if (commit_usage < 25)
      {
        color = MI_MAROON;
      }
      else
        if (commit_usage < 50)
      {
        color = MI_ORANGE;
      }
      else
        if (commit_usage < 75)
      {
        color = MI_TEAL;
      }
      else
        color = MI_DARKGREEN;
      bit_of_page = (long) page->memid.mem.arena.slice_count;
    }
    else
    {
      c = '?';
      if (bit_of_page > 0)
      {
        c = '-';
      }
      else
        if (_mi_meta_is_meta_page(start))
      {
        c = 'm';
        color = MI_GRAY;
      }
      else
        if ((slice_index + bit) < arena->info_slices)
      {
        c = 'i';
        color = MI_GRAY;
      }
      else
        if (mi_bbitmap_is_setN(arena->slices_free, slice_index + bit, 1))
      {
        if (mi_bitmap_is_set(arena->slices_purge, slice_index + bit))
        {
          c = '~';
          color = MI_ORANGE;
        }
        else
          if (mi_bitmap_is_setN(arena->slices_committed, slice_index + bit, 1))
        {
          c = '_';
          color = MI_GRAY;
        }
        else
        {
          c = '.';
          color = MI_GRAY;
        }
      }
      if ((bit == ((1 << (3 + 3)) - 1)) && (bit_of_page > 1))
      {
        c = '>';
      }
    }
    if (color != prev_color)
    {
      mi_debug_color(buf, k, color);
      prev_color = color;
    }
    buf[*k] = c;
    *k += 1;
  }

  mi_debug_color(buf, k, MI_GRAY);
  *pbit_of_page = bit_of_page;
  *pcolor_of_page = color;
  return bit_set_count;
}

static size_t mi_debug_show_chunks(const char *header1, const char *header2, const char *header3, size_t slice_count, size_t chunk_count, mi_bchunk_t *chunks, mi_bchunkmap_t *chunk_bins, bool invert, mi_arena_t *arena, bool narrow)
{
  _mi_raw_message("\x1B[37m%s%s%s (use/commit: \x1B[31m0 - 25%%\x1B[33m - 50%%\x1B[36m - 75%%\x1B[32m - 100%%\x1B[0m)\n", header1, header2, header3);
  const size_t fields_per_line = (narrow) ? (2) : (4);
  const size_t used_slice_count = mi_arena_used_slices(arena);
  size_t bit_count = 0;
  size_t bit_set_count = 0;
  for (size_t i = 0; (i < chunk_count) && (bit_count < slice_count); i += 1)
  {
    char buf[(5 * (1 << (6 + 3))) + 64];
    _mi_memzero(buf, sizeof(buf));
    if ((bit_count > used_slice_count) && ((i + 2) < chunk_count))
    {
      const size_t diff = (chunk_count - 1) - i;
      bit_count += diff * (1 << (6 + 3));
      _mi_raw_message("  |\n");
      i = chunk_count - 1;
    }
    size_t k = 0;
    mi_bchunk_t *chunk = &chunks[i];
    if (i < 10)
    {
      buf[k] = '0' + ((char) i);
      k += 1;
      buf[k] = ' ';
      k += 1;
      buf[k] = ' ';
      k += 1;
    }
    else
      if (i < 100)
    {
      buf[k] = '0' + ((char) (i / 10));
      k += 1;
      buf[k] = '0' + ((char) (i % 10));
      k += 1;
      buf[k] = ' ';
      k += 1;
    }
    else
      if (i < 1000)
    {
      buf[k] = '0' + ((char) (i / 100));
      k += 1;
      buf[k] = '0' + ((char) ((i % 100) / 10));
      k += 1;
      buf[k] = '0' + ((char) (i % 10));
      k += 1;
    }
    char chunk_kind = ' ';
    if (chunk_bins != 0)
    {
      switch (mi_bbitmap_debug_get_bin(chunk_bins, i))
      {
        case MI_CBIN_SMALL:
          chunk_kind = 'S';
          break;

        case MI_CBIN_MEDIUM:
          chunk_kind = 'M';
          break;

        case MI_CBIN_LARGE:
          chunk_kind = 'L';
          break;

        case MI_CBIN_OTHER:
          chunk_kind = 'X';
          break;

        default:
          chunk_kind = ' ';
          break;

      }

    }
    buf[k] = chunk_kind;
    k += 1;
    buf[k] = ' ';
    k += 1;
    long bit_of_page = 0;
    mi_ansi_color_t color_of_page = MI_GRAY;
    for (size_t j = 0; j < ((1 << (6 + 3)) / (1 << (3 + 3))); j += 1)
    {
      if ((j > 0) && ((j % fields_per_line) == 0))
      {
        _mi_raw_message("  %s\n\x1B[37m", buf);
        _mi_memzero(buf, sizeof(buf));
        _mi_memset(buf, ' ', 5);
        k = 5;
      }
      if (bit_count < slice_count)
      {
        mi_bfield_t bfield = chunk->bfields[j];
        if (invert)
        {
          bfield = ~bfield;
        }
        size_t xcount = (arena != 0) ? (mi_debug_show_page_bfield(bfield, buf, &k, arena, bit_count, &bit_of_page, &color_of_page)) : (mi_debug_show_bfield(bfield, buf, &k));
        if (invert)
        {
          xcount = (1 << (3 + 3)) - xcount;
        }
        bit_set_count += xcount;
        buf[k] = ' ';
        k += 1;
      }
      else
      {
        _mi_memset(buf + k, 'o', 1 << (3 + 3));
        k += 1 << (3 + 3);
      }
      bit_count += 1 << (3 + 3);
    }

    _mi_raw_message("  %s\n\x1B[37m", buf);
  }

  _mi_raw_message("\x1B[0m  total ('x'): %zu\n", bit_set_count);
  return bit_set_count;
}

static size_t mi_debug_show_bitmap_binned(const char *header1, const char *header2, const char *header3, size_t slice_count, mi_bitmap_t *bitmap, mi_bchunkmap_t *chunk_bins, bool invert, mi_arena_t *arena, bool narrow)
{
  return mi_debug_show_chunks(header1, header2, header3, slice_count, mi_bitmap_chunk_count(bitmap), &bitmap->chunks[0], chunk_bins, invert, arena, narrow);
}

static void mi_debug_show_arenas_ex(bool show_pages, bool narrow)
{
  mi_subproc_t *subproc = _mi_subproc();
  size_t max_arenas = mi_arenas_get_count(subproc);
  size_t page_total = 0;
  for (size_t i = 0; i < max_arenas; i += 1)
  {
    mi_arena_t *arena = atomic_load_explicit(&subproc->arenas[i], memory_order_acquire);
    if (arena == 0)
    {
      break;
    }
    (arena->subproc == subproc) ? ((void) 0) : (_mi_assert_fail("arena->subproc == subproc", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 1530, __func__));
    _mi_raw_message("arena %zu at %p: %zu slices (%zu MiB)%s, subproc: %p\n", i, arena, arena->slice_count, (size_t) (mi_size_of_slices(arena->slice_count) / (1024UL * 1024UL)), (arena->memid.is_pinned) ? (", pinned") : (""), arena->subproc);
    if (show_pages)
    {
      const char *header1 = "pages (p:page, f:full, s:singleton, P,F,S:not abandoned, i:arena-info, m:meta-data, ~:free-purgable, _:free-committed, .:free-reserved)";
      const char *header2 = (narrow) ? ("\n      ") : (" ");
      const char *header3 = "(chunk bin: S:small, M : medium, L : large, X : other)";
      page_total += mi_debug_show_bitmap_binned(header1, header2, header3, arena->slice_count, arena->pages, arena->slices_free->chunkmap_bins, 0, arena, narrow);
    }
  }

  if (show_pages)
  {
    _mi_raw_message("total pages in arenas: %zu\n", page_total);
  }
}

void mi_debug_show_arenas(void)
{
  mi_debug_show_arenas_ex(1, 0);
}

void mi_arenas_print(void)
{
  mi_debug_show_arenas();
}

int mi_reserve_huge_os_pages_at_ex(size_t pages, int numa_node, size_t timeout_msecs, bool exclusive, mi_arena_id_t *arena_id)
{
  if (arena_id != 0)
  {
    *arena_id = 0;
  }
  if (pages == 0)
  {
    return 0;
  }
  if (numa_node < (-1))
  {
    numa_node = -1;
  }
  if (numa_node >= 0)
  {
    numa_node = numa_node % _mi_os_numa_node_count();
  }
  size_t hsize = 0;
  size_t pages_reserved = 0;
  mi_memid_t memid;
  void *p = _mi_os_alloc_huge_os_pages(pages, numa_node, timeout_msecs, &pages_reserved, &hsize, &memid);
  if ((p == 0) || (pages_reserved == 0))
  {
    _mi_warning_message("failed to reserve %zu GiB huge pages\n", pages);
    return 12;
  }
  _mi_verbose_message("numa node %i: reserved %zu GiB huge pages (of the %zu GiB requested)\n", numa_node, pages_reserved, pages);
  if (!mi_manage_os_memory_ex2(_mi_subproc(), p, hsize, numa_node, exclusive, memid, 0, 0, arena_id))
  {
    _mi_os_free(p, hsize, memid);
    return 12;
  }
  return 0;
}

int mi_reserve_huge_os_pages_at(size_t pages, int numa_node, size_t timeout_msecs)
{
  return mi_reserve_huge_os_pages_at_ex(pages, numa_node, timeout_msecs, 0, 0);
}

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

int mi_reserve_huge_os_pages(size_t pages, double max_secs, size_t *pages_reserved)
{
  (void) max_secs;
  _mi_warning_message("mi_reserve_huge_os_pages is deprecated: use mi_reserve_huge_os_pages_interleave/at instead\n");
  if (pages_reserved != 0)
  {
    *pages_reserved = 0;
  }
  int err = mi_reserve_huge_os_pages_interleave(pages, 0, (size_t) (max_secs * 1000.0));
  if ((err == 0) && (pages_reserved != 0))
  {
    *pages_reserved = pages;
  }
  return err;
}

static long mi_arena_purge_delay(void)
{
  return mi_option_get(mi_option_purge_delay) * mi_option_get(mi_option_arena_purge_mult);
}

static bool mi_arena_purge(mi_arena_t *arena, size_t slice_index, size_t slice_count)
{
  (!arena->memid.is_pinned) ? ((void) 0) : (_mi_assert_fail("!arena->memid.is_pinned", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 1648, __func__));
  (mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 1649, __func__));
  const size_t size = mi_size_of_slices(slice_count);
  void * const p = mi_arena_slice_start(arena, slice_index);
  size_t already_committed;
  mi_bitmap_setN(arena->slices_committed, slice_index, slice_count, &already_committed);
  const bool all_committed = already_committed == slice_count;
  const bool needs_recommit = _mi_os_purge_ex(p, size, all_committed, mi_size_of_slices(already_committed), arena->commit_fun, arena->commit_fun_arg);
  if (needs_recommit)
  {
    mi_bitmap_clearN(arena->slices_committed, slice_index, slice_count);
  }
  else
    if (!all_committed)
  {
    mi_bitmap_clearN(arena->slices_committed, slice_index, slice_count);
  }
  return needs_recommit;
}

static void mi_arena_schedule_purge(mi_arena_t *arena, size_t slice_index, size_t slice_count)
{
  const long delay = mi_arena_purge_delay();
  if ((arena->memid.is_pinned || (delay < 0)) || _mi_preloading())
  {
    return;
  }
  (mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("mi_bbitmap_is_clearN(arena->slices_free, slice_index, slice_count)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 1682, __func__));
  if (delay == 0)
  {
    mi_arena_purge(arena, slice_index, slice_count);
  }
  else
  {
    const mi_msecs_t expire = _mi_clock_now() + delay;
    mi_msecs_t expire0 = 0;
    if (atomic_compare_exchange_strong_explicit(&arena->purge_expire, &expire0, expire, memory_order_acq_rel, memory_order_acquire))
    {
      (expire0 == 0) ? ((void) 0) : (_mi_assert_fail("expire0==0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 1694, __func__));
      atomic_compare_exchange_strong_explicit(&arena->subproc->purge_expire, &expire0, expire, memory_order_acq_rel, memory_order_acquire);
    }
    else
    {
    }
    mi_bitmap_setN(arena->slices_purge, slice_index, slice_count, 0);
  }
}

typedef struct mi_purge_visit_info_s
{
  mi_msecs_t now;
  mi_msecs_t delay;
  bool all_purged;
  bool any_purged;
} mi_purge_visit_info_t;
static bool mi_arena_try_purge_range(mi_arena_t *arena, size_t slice_index, size_t slice_count)
{
  if (mi_bbitmap_try_clearN(arena->slices_free, slice_index, slice_count))
  {
    bool decommitted = mi_arena_purge(arena, slice_index, slice_count);
    (void) decommitted;
    ((!decommitted) || mi_bitmap_is_clearN(arena->slices_committed, slice_index, slice_count)) ? ((void) 0) : (_mi_assert_fail("!decommitted || mi_bitmap_is_clearN(arena->slices_committed, slice_index, slice_count)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 1715, __func__));
    mi_bbitmap_setN(arena->slices_free, slice_index, slice_count);
    return 1;
  }
  else
  {
    return 0;
  }
}

static bool mi_arena_try_purge_visitor(size_t slice_index, size_t slice_count, mi_arena_t *arena, void *arg)
{
  mi_purge_visit_info_t *vinfo = (mi_purge_visit_info_t *) arg;
  if (mi_arena_try_purge_range(arena, slice_index, slice_count))
  {
    vinfo->any_purged = 1;
    vinfo->all_purged = 1;
  }
  else
    if (slice_count > 1)
  {
    for (size_t i = 0; i < slice_count; i += 1)
    {
      const bool purged = mi_arena_try_purge_range(arena, slice_index + i, 1);
      vinfo->any_purged = vinfo->any_purged || purged;
      vinfo->all_purged = vinfo->all_purged && purged;
    }

  }
  return 1;
}

static bool mi_arena_try_purge(mi_arena_t *arena, mi_msecs_t now, bool force)
{
  if (arena->memid.is_pinned)
  {
    return 0;
  }
  mi_msecs_t expire = atomic_load_explicit(&arena->purge_expire, memory_order_relaxed);
  if ((!force) && ((expire == 0) || (expire > now)))
  {
    return 0;
  }
  atomic_store_explicit(&arena->purge_expire, (mi_msecs_t) 0, memory_order_release);
  __mi_stat_counter_increase_mt(&arena->subproc->stats.arena_purges, 1);
  mi_purge_visit_info_t vinfo = {now, mi_arena_purge_delay(), 1, 0};
  _mi_bitmap_forall_setc_ranges(arena->slices_purge, &mi_arena_try_purge_visitor, arena, &vinfo);
  return vinfo.any_purged;
}

static void mi_arenas_try_purge(bool force, bool visit_all, mi_subproc_t *subproc, size_t tseq)
{
  const long delay = mi_arena_purge_delay();
  if (_mi_preloading() || (delay <= 0))
  {
    return;
  }
  const mi_msecs_t now = _mi_clock_now();
  const mi_msecs_t arenas_expire = atomic_load_explicit(&subproc->purge_expire, memory_order_acquire);
  if (((!visit_all) && (!force)) && ((arenas_expire == 0) || (arenas_expire > now)))
  {
    return;
  }
  const size_t max_arena = mi_arenas_get_count(subproc);
  if (max_arena == 0)
  {
    return;
  }
  static mi_atomic_guard_t purge_guard;
  uintptr_t _mi_guard_expected = 0;
  for (bool _mi_guard_once = 1; _mi_guard_once && atomic_compare_exchange_strong_explicit(&purge_guard, &_mi_guard_expected, (uintptr_t) 1, memory_order_acq_rel, memory_order_acquire); atomic_store_explicit(&purge_guard, (uintptr_t) 0, memory_order_release), _mi_guard_once = 0)
  {
    if (arenas_expire > now)
    {
      atomic_store_explicit(&subproc->purge_expire, now + (delay / 10), memory_order_release);
    }
    const size_t arena_start = tseq % max_arena;
    size_t max_purge_count = (visit_all) ? (max_arena) : ((max_arena / 4) + 1);
    bool all_visited = 1;
    bool any_purged = 0;
    for (size_t _i = 0; _i < max_arena; _i += 1)
    {
      size_t i = _i + arena_start;
      if (i >= max_arena)
      {
        i -= max_arena;
      }
      mi_arena_t *arena = mi_arena_from_index(subproc, i);
      if (arena != 0)
      {
        if (mi_arena_try_purge(arena, now, force))
        {
          any_purged = 1;
          if (max_purge_count <= 1)
          {
            all_visited = 0;
            break;
          }
          max_purge_count -= 1;
        }
      }
    }

    if (all_visited && (!any_purged))
    {
      atomic_store_explicit(&subproc->purge_expire, 0, memory_order_release);
    }
  }

}

typedef struct mi_abandoned_page_visit_info_s
{
  int heap_tag;
  mi_block_visit_fun *visitor;
  void *arg;
  bool visit_blocks;
} mi_abandoned_page_visit_info_t;
static bool abandoned_page_visit(mi_page_t *page, mi_abandoned_page_visit_info_t *vinfo)
{
  if (page->heap_tag != vinfo->heap_tag)
  {
    return 1;
  }
  mi_heap_area_t area;
  _mi_heap_area_init(&area, page);
  if (!vinfo->visitor(0, &area, 0, area.block_size, vinfo->arg))
  {
    return 0;
  }
  if (vinfo->visit_blocks)
  {
    return _mi_heap_area_visit_blocks(&area, page, vinfo->visitor, vinfo->arg);
  }
  else
  {
    return 1;
  }
}

static bool abandoned_page_visit_at(size_t slice_index, size_t slice_count, mi_arena_t *arena, void *arg)
{
  (void) slice_count;
  mi_abandoned_page_visit_info_t *vinfo = (mi_abandoned_page_visit_info_t *) arg;
  mi_page_t *page = (mi_page_t *) mi_arena_slice_start(arena, slice_index);
  (mi_page_is_abandoned_mapped(page)) ? ((void) 0) : (_mi_assert_fail("mi_page_is_abandoned_mapped(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 1846, __func__));
  return abandoned_page_visit(page, vinfo);
}

bool mi_abandoned_visit_blocks(mi_subproc_id_t subproc_id, int heap_tag, bool visit_blocks, mi_block_visit_fun *visitor, void *arg)
{
  mi_abandoned_page_visit_info_t visit_info = {heap_tag, visitor, arg, visit_blocks};
  (void) subproc_id;
  (void) heap_tag;
  (void) visit_blocks;
  (void) visitor;
  (void) arg;
  bool ok = 1;
  mi_subproc_t *subproc = _mi_subproc_from_id(subproc_id);
  {
    const size_t _arena_count = mi_arenas_get_count(subproc);
    const size_t _arena_cycle = (_arena_count == 0) ? (0) : (_arena_count - 1);
    size_t _start = (_arena_cycle <= 1) ? (0) : (0 % _arena_cycle);
    for (size_t _i = 0; _i < _arena_count; _i += 1)
    {
      mi_arena_t *arena;
      unsigned int arena_idx = 0;
      if (0 != 0)
      {
        arena_idx = 0;
        if (_i > 0)
        {
          break;
        }
      }
      else
      {
        size_t _idx;
        if (_i < _arena_cycle)
        {
          _idx = _i + _start;
          if (_idx >= _arena_cycle)
          {
            _idx -= _arena_cycle;
          }
        }
        else
        {
          _idx = _i;
        }
        arena_idx = mi_arena_from_index(subproc, _idx);
      }
      if ((&arena[arena_idx]) != 0)
      {
        {
          (arena->subproc == subproc) ? ((void) 0) : (_mi_assert_fail("arena->subproc == subproc", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 1861, __func__));
          for (size_t bin = 0; ok && (bin < ((73U + 1) + 1)); bin += 1)
          {
            if (atomic_load_explicit(&subproc->abandoned_count[bin], memory_order_relaxed) > 0)
            {
              ok = _mi_bitmap_forall_set(arena->pages_abandoned[bin], &abandoned_page_visit_at, arena, &visit_info);
            }
          }

        }
      }
    }

  }
  ;
  if (!ok)
  {
    return 0;
  }
  for (bool _go = (mi_lock_acquire(&subproc->os_abandoned_pages_lock), 1); _go; mi_lock_release(&subproc->os_abandoned_pages_lock), _go = 0)
  {
    for (mi_page_t *page = subproc->os_abandoned_pages; ok && ((&page[page_idx]) != 0); page_idx = page_idx->next)
    {
      ok = abandoned_page_visit(page, &visit_info);
    }

    unsigned int page_idx = 0;
  }

  return ok;
}

static bool mi_arena_page_register(size_t slice_index, size_t slice_count, mi_arena_t *arena, void *arg)
{
  (void) arg;
  (void) slice_count;
  (slice_count == 1) ? ((void) 0) : (_mi_assert_fail("slice_count == 1", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 1889, __func__));
  mi_page_t *page = (mi_page_t *) mi_arena_slice_start(arena, slice_index);
  (mi_bitmap_is_setN(page->memid.mem.arena.arena->pages, page->memid.mem.arena.slice_index, 1)) ? ((void) 0) : (_mi_assert_fail("mi_bitmap_is_setN(page->memid.mem.arena.arena->pages, page->memid.mem.arena.slice_index, 1)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 1891, __func__));
  if (!_mi_page_map_register(page))
  {
    return 0;
  }
  (_mi_ptr_page(page) == page) ? ((void) 0) : (_mi_assert_fail("_mi_ptr_page(page)==page", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c", 1893, __func__));
  return 1;
}

static bool mi_arena_pages_reregister(mi_arena_t *arena)
{
  return _mi_bitmap_forall_set(arena->pages, &mi_arena_page_register, arena, 0);
}

bool mi_arena_unload(mi_arena_id_t arena_id, void **base, size_t *accessed_size, size_t *full_size)
{
  mi_arena_t *arena = _mi_arena_from_id(arena_id);
  if (arena == 0)
  {
    return 0;
  }
  else
    if (!arena->is_exclusive)
  {
    _mi_warning_message("cannot unload a non-exclusive arena (id %zu at %p)\n", arena_id, arena);
    return 0;
  }
  else
    if (arena->memid.memkind != MI_MEM_EXTERNAL)
  {
    _mi_warning_message("can only unload managed arena's for external memory (id %zu at %p)\n", arena_id, arena);
    return 0;
  }
  const size_t asize = mi_size_of_slices(mi_arena_used_slices(arena));
  if (base != 0)
  {
    *base = (void *) arena;
  }
  if (full_size != 0)
  {
    *full_size = arena->memid.mem.os.size;
  }
  if (accessed_size != 0)
  {
    *accessed_size = asize;
  }
  mi_subproc_t * const subproc = arena->subproc;
  for (size_t bin = 0; bin < ((73U + 1) + 1); bin += 1)
  {
    const size_t count = mi_bitmap_popcount(arena->pages_abandoned[bin]);
    if (count > 0)
    {
      atomic_fetch_sub_explicit(&subproc->abandoned_count[bin], (uintptr_t) 1, memory_order_acq_rel);
    }
  }

  _mi_page_map_unregister_range(arena, asize);
  const size_t count = mi_arenas_get_count(subproc);
  for (size_t i = 0; i < count; i += 1)
  {
    if (mi_arena_from_index(subproc, i) == arena)
    {
      atomic_store_explicit(&subproc->arenas[i], 0, memory_order_release);
      if ((i + 1) == count)
      {
        size_t expected = count;
        atomic_compare_exchange_strong_explicit(&subproc->arena_count, &expected, count - 1, memory_order_acq_rel, memory_order_acquire);
      }
      break;
    }
  }

  return 1;
}

bool mi_arena_reload(void *start, size_t size, mi_commit_fun_t *commit_fun, void *commit_fun_arg, mi_arena_id_t *arena_id)
{
  if (arena_id != 0)
  {
    *arena_id = _mi_arena_id_none();
  }
  if ((start == 0) || (size == 0))
  {
    return 0;
  }
  mi_arena_t *arena = (mi_arena_t *) start;
  mi_memid_t memid = arena->memid;
  if (memid.memkind != MI_MEM_EXTERNAL)
  {
    _mi_warning_message("can only reload arena's from external memory (%p)\n", arena);
    return 0;
  }
  if (memid.mem.os.base != start)
  {
    _mi_warning_message("the reloaded arena base address differs from the external memory (arena: %p, external: %p)\n", arena, start);
    return 0;
  }
  if (memid.mem.os.size != size)
  {
    _mi_warning_message("the reloaded arena size differs from the external memory (arena size: %zu, external size: %zu)\n", arena->memid.mem.os.size, size);
    return 0;
  }
  if (!arena->is_exclusive)
  {
    _mi_warning_message("the reloaded arena is not exclusive\n");
    return 0;
  }
  arena->is_exclusive = 1;
  arena->commit_fun = commit_fun;
  arena->commit_fun_arg = commit_fun_arg;
  arena->subproc = _mi_subproc();
  if (!mi_arenas_add(arena->subproc, arena, arena_id))
  {
    return 0;
  }
  if (!mi_arena_pages_reregister(arena))
  {
    return 0;
  }
  for (size_t bin = 0; bin < ((73U + 1) + 1); bin += 1)
  {
    const size_t count = mi_bitmap_popcount(arena->pages_abandoned[bin]);
    if (count > 0)
    {
      atomic_fetch_sub_explicit(&arena->subproc->abandoned_count[bin], (uintptr_t) 1, memory_order_acq_rel);
    }
  }

  return 1;
}

