#include <atomic.h>
#include <errno.h>
#include <internal.h>
#include <limits.h>
#include <mimalloc-stats.h>
#include <mimalloc.h>
#include <prim.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
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
bool mi_manage_os_memory(void *start, size_t size, bool is_committed, bool is_large, bool is_zero, int numa_node);
void mi_debug_show_arenas(void);
void mi_arenas_print(void);
typedef int mi_arena_id_t;
void *mi_arena_area(mi_arena_id_t arena_id, size_t *size);
int mi_reserve_huge_os_pages_at_ex(size_t pages, int numa_node, size_t timeout_msecs, bool exclusive, mi_arena_id_t *arena_id);
int mi_reserve_os_memory_ex(size_t size, bool commit, bool allow_large, bool exclusive, mi_arena_id_t *arena_id);
bool mi_manage_os_memory_ex(void *start, size_t size, bool is_committed, bool is_large, bool is_zero, int numa_node, bool exclusive, mi_arena_id_t *arena_id);
mi_heap_t *mi_heap_new_in_arena(mi_arena_id_t arena_id);
typedef void *mi_subproc_id_t;
mi_subproc_id_t mi_subproc_main(void);
mi_subproc_id_t mi_subproc_new(void);
void mi_subproc_delete(mi_subproc_id_t subproc);
void mi_subproc_add_current_thread(mi_subproc_id_t subproc);
bool mi_abandoned_visit_blocks(mi_subproc_id_t subproc_id, int heap_tag, bool visit_blocks, mi_block_visit_fun *visitor, void *arg);
void mi_heap_guarded_set_sample_rate(mi_heap_t *heap, size_t sample_rate, size_t seed);
void mi_heap_guarded_set_size_bound(mi_heap_t *heap, size_t min, size_t max);
void mi_thread_set_in_threadpool(void);
mi_heap_t *mi_heap_new_ex(int heap_tag, bool allow_destroy, mi_arena_id_t arena_id);
int mi_reserve_huge_os_pages(size_t pages, double max_secs, size_t *pages_reserved);
void mi_collect_reduce(size_t target_thread_owned);
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
  mi_option_max_segment_reclaim,
  mi_option_destroy_on_exit,
  mi_option_arena_reserve,
  mi_option_arena_purge_mult,
  mi_option_purge_extend_delay,
  mi_option_abandoned_reclaim_on_free,
  mi_option_disallow_arena_alloc,
  mi_option_retry_on_oom,
  mi_option_visit_abandoned,
  mi_option_guarded_min,
  mi_option_guarded_max,
  mi_option_guarded_precise,
  mi_option_guarded_sample_rate,
  mi_option_guarded_sample_seed,
  mi_option_target_segments_per_thread,
  mi_option_generic_collect,
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
} mi_stats_t;
void mi_stats_get(size_t stats_size, mi_stats_t *stats);
char *mi_stats_get_json(size_t buf_size, char *buf);
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

typedef int64_t mi_ssize_t;
typedef uintptr_t mi_encoded_t;
typedef size_t mi_threadid_t;
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t;
typedef enum mi_delayed_e
{
  MI_USE_DELAYED_FREE = 0,
  MI_DELAYED_FREEING = 1,
  MI_NO_DELAYED_FREE = 2,
  MI_NEVER_DELAYED_FREE = 3
} mi_delayed_t;
typedef union mi_page_flags_s
{
  uint8_t full_aligned;
  struct 
  {
    uint8_t in_full : 1;
    uint8_t has_aligned : 1;
  } x;
} mi_page_flags_t;
typedef uintptr_t mi_thread_free_t;
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
} mi_page_t;
typedef enum mi_page_kind_e
{
  MI_PAGE_SMALL,
  MI_PAGE_MEDIUM,
  MI_PAGE_LARGE,
  MI_PAGE_HUGE
} mi_page_kind_t;
typedef enum mi_segment_kind_e
{
  MI_SEGMENT_NORMAL,
  MI_SEGMENT_HUGE
} mi_segment_kind_t;
typedef struct mi_commit_mask_s
{
  size_t mask[((1UL << (9 + (13 + 3))) / (1UL << (13 + 3))) / ((1 << 3) * 8)];
} mi_commit_mask_t;
typedef mi_page_t mi_slice_t;
typedef int64_t mi_msecs_t;
typedef enum mi_memkind_e
{
  MI_MEM_NONE,
  MI_MEM_EXTERNAL,
  MI_MEM_STATIC,
  MI_MEM_OS,
  MI_MEM_OS_HUGE,
  MI_MEM_OS_REMAP,
  MI_MEM_ARENA
} mi_memkind_t;
inline static bool mi_memkind_is_os(mi_memkind_t memkind)
{
  return (memkind >= MI_MEM_OS) && (memkind <= MI_MEM_OS_REMAP);
}

typedef struct mi_memid_os_info
{
  void *base;
  size_t size;
} mi_memid_os_info_t;
typedef struct mi_memid_arena_info
{
  size_t block_index;
  mi_arena_id_t id;
  bool is_exclusive;
} mi_memid_arena_info_t;
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
} mi_memid_t;
typedef struct mi_subproc_s mi_subproc_t;
typedef struct mi_segment_s
{
  mi_memid_t memid;
  bool allow_decommit;
  bool allow_purge;
  size_t segment_size;
  mi_subproc_t *subproc;
  mi_msecs_t purge_expire;
  mi_commit_mask_t purge_mask;
  mi_commit_mask_t commit_mask;
  struct mi_segment_s *next;
  bool was_reclaimed;
  bool dont_free;
  size_t abandoned;
  size_t abandoned_visits;
  size_t used;
  uintptr_t cookie;
  struct mi_segment_s *abandoned_os_next;
  struct mi_segment_s *abandoned_os_prev;
  size_t segment_slices;
  size_t segment_info_slices;
  mi_segment_kind_t kind;
  size_t slice_entries;
  _Atomic mi_threadid_t thread_id;
  mi_slice_t slices[((1UL << (9 + (13 + 3))) / (1UL << (13 + 3))) + 1];
} mi_segment_t;
typedef struct mi_tld_s mi_tld_t;
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
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
  mi_block_t * _Atomic thread_delayed_free;
  mi_threadid_t thread_id;
  mi_arena_id_t arena_id;
  uintptr_t cookie;
  uintptr_t keys[2];
  mi_random_ctx_t random;
  size_t page_count;
  size_t page_retired_min;
  size_t page_retired_max;
  long generic_count;
  long generic_collect_count;
  mi_heap_t *next;
  bool no_reclaim;
  uint8_t tag;
  mi_page_t *pages_free_direct[(128 + ((((sizeof(mi_padding_t)) + (1 << 3)) - 1) / (1 << 3))) + 1];
  mi_page_queue_t pages[(73U + 1) + 1];
};
struct mi_subproc_s
{
  _Atomic size_t abandoned_count;
  _Atomic size_t abandoned_os_list_count;
  pthread_mutex_t abandoned_os_lock;
  pthread_mutex_t abandoned_os_visit_lock;
  mi_segment_t *abandoned_os_list;
  mi_segment_t *abandoned_os_list_tail;
  mi_memid_t memid;
};
typedef struct mi_span_queue_s
{
  mi_slice_t *first;
  mi_slice_t *last;
  size_t slice_count;
} mi_span_queue_t;
typedef struct mi_segments_tld_s
{
  mi_span_queue_t spans[35 + 1];
  size_t count;
  size_t peak_count;
  size_t current_size;
  size_t peak_size;
  size_t reclaim_count;
  mi_subproc_t *subproc;
  mi_stats_t *stats;
} mi_segments_tld_t;
struct mi_tld_s
{
  unsigned long long heartbeat;
  bool recurse;
  mi_heap_t *heap_backing;
  mi_heap_t *heaps;
  mi_segments_tld_t segments;
  mi_stats_t stats;
};
void _mi_stat_increase(mi_stat_count_t *stat, size_t amount);
void _mi_stat_decrease(mi_stat_count_t *stat, size_t amount);
void _mi_stat_adjust_decrease(mi_stat_count_t *stat, size_t amount);
void _mi_stat_counter_increase(mi_stat_counter_t *stat, size_t amount);
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
extern mi_stats_t _mi_stats_main;
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
void _mi_thread_data_collect(void);
void _mi_tld_init(mi_tld_t *tld, mi_heap_t *bheap);
mi_threadid_t _mi_thread_id(void);
mi_heap_t *_mi_heap_main_get(void);
mi_subproc_t *_mi_subproc_from_id(mi_subproc_id_t subproc_id);
void _mi_heap_guarded_init(mi_heap_t *heap);
void _mi_os_init(void);
void *_mi_os_alloc(size_t size, mi_memid_t *memid);
void *_mi_os_zalloc(size_t size, mi_memid_t *memid);
void _mi_os_free(void *p, size_t size, mi_memid_t memid);
void _mi_os_free_ex(void *p, size_t size, bool still_committed, mi_memid_t memid);
size_t _mi_os_page_size(void);
size_t _mi_os_good_alloc_size(size_t size);
bool _mi_os_has_overcommit(void);
bool _mi_os_has_virtual_reserve(void);
bool _mi_os_reset(void *addr, size_t size);
bool _mi_os_decommit(void *addr, size_t size);
bool _mi_os_unprotect(void *addr, size_t size);
bool _mi_os_purge(void *p, size_t size);
bool _mi_os_purge_ex(void *p, size_t size, bool allow_reset, size_t stat_size);
void _mi_os_reuse(void *p, size_t size);
bool _mi_os_commit(void *p, size_t size, bool *is_zero);
bool _mi_os_commit_ex(void *addr, size_t size, bool *is_zero, size_t stat_size);
bool _mi_os_protect(void *addr, size_t size);
void *_mi_os_alloc_aligned(size_t size, size_t alignment, bool commit, bool allow_large, mi_memid_t *memid);
void *_mi_os_alloc_aligned_at_offset(size_t size, size_t alignment, size_t align_offset, bool commit, bool allow_large, mi_memid_t *memid);
void *_mi_os_get_aligned_hint(size_t try_alignment, size_t size);
bool _mi_os_use_large_page(size_t size, size_t alignment);
size_t _mi_os_large_page_size(void);
void *_mi_os_alloc_huge_os_pages(size_t pages, int numa_node, mi_msecs_t max_secs, size_t *pages_reserved, size_t *psize, mi_memid_t *memid);
int _mi_os_numa_node_count(void);
int _mi_os_numa_node(void);
mi_arena_id_t _mi_arena_id_none(void);
void _mi_arena_free(void *p, size_t size, size_t still_committed_size, mi_memid_t memid);
void *_mi_arena_alloc(size_t size, bool commit, bool allow_large, mi_arena_id_t req_arena_id, mi_memid_t *memid);
void *_mi_arena_alloc_aligned(size_t size, size_t alignment, size_t align_offset, bool commit, bool allow_large, mi_arena_id_t req_arena_id, mi_memid_t *memid);
bool _mi_arena_memid_is_suitable(mi_memid_t memid, mi_arena_id_t request_arena_id);
bool _mi_arena_contains(const void *p);
void _mi_arenas_collect(bool force_purge);
void _mi_arena_unsafe_destroy_all(void);
bool _mi_arena_segment_clear_abandoned(mi_segment_t *segment);
void _mi_arena_segment_mark_abandoned(mi_segment_t *segment);
void *_mi_arena_meta_zalloc(size_t size, mi_memid_t *memid);
void _mi_arena_meta_free(void *p, mi_memid_t memid, size_t size);
typedef struct mi_arena_field_cursor_s
{
  size_t os_list_count;
  size_t start;
  size_t end;
  size_t bitmap_idx;
  mi_subproc_t *subproc;
  bool visit_all;
  bool hold_visit_lock;
} mi_arena_field_cursor_t;
void _mi_arena_field_cursor_init(mi_heap_t *heap, mi_subproc_t *subproc, bool visit_all, mi_arena_field_cursor_t *current);
mi_segment_t *_mi_arena_segment_clear_abandoned_next(mi_arena_field_cursor_t *previous);
void _mi_arena_field_cursor_done(mi_arena_field_cursor_t *current);
void _mi_segment_map_allocated_at(const mi_segment_t *segment);
void _mi_segment_map_freed_at(const mi_segment_t *segment);
void _mi_segment_map_unsafe_destroy(void);
mi_page_t *_mi_segment_page_alloc(mi_heap_t *heap, size_t block_size, size_t page_alignment, mi_segments_tld_t *tld);
void _mi_segment_page_free(mi_page_t *page, bool force, mi_segments_tld_t *tld);
void _mi_segment_page_abandon(mi_page_t *page, mi_segments_tld_t *tld);
bool _mi_segment_try_reclaim_abandoned(mi_heap_t *heap, bool try_all, mi_segments_tld_t *tld);
void _mi_segment_collect(mi_segment_t *segment, bool force);
void _mi_segment_huge_page_reset(mi_segment_t *segment, mi_page_t *page, mi_block_t *block);
uint8_t *_mi_segment_page_start(const mi_segment_t *segment, const mi_page_t *page, size_t *page_size);
void _mi_abandoned_reclaim_all(mi_heap_t *heap, mi_segments_tld_t *tld);
void _mi_abandoned_collect(mi_heap_t *heap, bool force, mi_segments_tld_t *tld);
bool _mi_segment_attempt_reclaim(mi_heap_t *heap, mi_segment_t *segment);
bool _mi_segment_visit_blocks(mi_segment_t *segment, int heap_tag, bool visit_blocks, mi_block_visit_fun *visitor, void *arg);
void *_mi_malloc_generic(mi_heap_t *heap, size_t size, bool zero, size_t huge_alignment);
void _mi_page_retire(mi_page_t *page);
void _mi_page_unfull(mi_page_t *page);
void _mi_page_free(mi_page_t *page, mi_page_queue_t *pq, bool force);
void _mi_page_abandon(mi_page_t *page, mi_page_queue_t *pq);
void _mi_page_force_abandon(mi_page_t *page);
void _mi_heap_delayed_free_all(mi_heap_t *heap);
bool _mi_heap_delayed_free_partial(mi_heap_t *heap);
void _mi_heap_collect_retired(mi_heap_t *heap, bool force);
void _mi_page_use_delayed_free(mi_page_t *page, mi_delayed_t delay, bool override_never);
bool _mi_page_try_use_delayed_free(mi_page_t *page, mi_delayed_t delay, bool override_never);
size_t _mi_page_queue_append(mi_heap_t *heap, mi_page_queue_t *pq, mi_page_queue_t *append);
void _mi_deferred_free(mi_heap_t *heap, bool force);
void _mi_page_free_collect(mi_page_t *page, bool force);
void _mi_page_reclaim(mi_heap_t *heap, mi_page_t *page);
size_t _mi_page_bin(const mi_page_t *page);
size_t _mi_bin_size(size_t bin);
size_t _mi_bin(size_t size);
void _mi_heap_init(mi_heap_t *heap, mi_tld_t *tld, mi_arena_id_t arena_id, bool noreclaim, uint8_t tag);
void _mi_heap_destroy_pages(mi_heap_t *heap);
void _mi_heap_collect_abandon(mi_heap_t *heap);
void _mi_heap_set_default_direct(mi_heap_t *heap);
bool _mi_heap_memid_is_suitable(mi_heap_t *heap, mi_memid_t memid);
void _mi_heap_unsafe_destroy_all(mi_heap_t *heap);
mi_heap_t *_mi_heap_by_tag(mi_heap_t *heap, uint8_t tag);
void _mi_heap_area_init(mi_heap_area_t *area, mi_page_t *page);
bool _mi_heap_area_visit_blocks(const mi_heap_area_t *area, mi_page_t *page, mi_block_visit_fun *visitor, void *arg);
void _mi_stats_done(mi_stats_t *stats);
void _mi_stats_merge_thread(mi_tld_t *tld);
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
bool _mi_free_delayed_block(mi_block_t *block);
void _mi_free_generic(mi_segment_t *segment, mi_page_t *page, bool is_local, void *p);
void _mi_padding_shrink(const mi_page_t *page, const mi_block_t *block, const size_t min_size);
bool _mi_page_is_valid(mi_page_t *page);
void _mi_assert_fail(const char *assertion, const char *fname, unsigned int line, const char *func);
inline static bool _mi_is_power_of_two(uintptr_t x)
{
  return (x & (x - 1)) == 0;
}

inline static bool _mi_is_aligned(void *p, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 380, __func__));
  return (((uintptr_t) p) % alignment) == 0;
}

inline static uintptr_t _mi_align_up(uintptr_t sz, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 386, __func__));
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

inline static uintptr_t _mi_align_down(uintptr_t sz, size_t alignment)
{
  (alignment != 0) ? ((void) 0) : (_mi_assert_fail("alignment != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 398, __func__));
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

inline static void *mi_align_up_ptr(void *p, size_t alignment)
{
  return (void *) _mi_align_up((uintptr_t) p, alignment);
}

inline static void *mi_align_down_ptr(void *p, size_t alignment)
{
  return (void *) _mi_align_down((uintptr_t) p, alignment);
}

inline static uintptr_t _mi_divide_up(uintptr_t size, size_t divider)
{
  (divider != 0) ? ((void) 0) : (_mi_assert_fail("divider != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 421, __func__));
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
  (size <= (SIZE_MAX - (sizeof(uintptr_t)))) ? ((void) 0) : (_mi_assert_fail("size <= SIZE_MAX - sizeof(uintptr_t)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 445, __func__));
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

inline static bool mi_heap_is_initialized(mi_heap_t *heap)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 501, __func__));
  return (heap != 0) && (heap != (&_mi_heap_empty));
}

inline static uintptr_t _mi_ptr_cookie(const void *p)
{
  extern mi_heap_t _mi_heap_main;
  (_mi_heap_main.cookie != 0) ? ((void) 0) : (_mi_assert_fail("_mi_heap_main.cookie != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 507, __func__));
  return ((uintptr_t) p) ^ _mi_heap_main.cookie;
}

inline static mi_page_t *_mi_heap_get_free_small_page(mi_heap_t *heap, size_t size)
{
  (size <= ((128 * (sizeof(void *))) + (sizeof(mi_padding_t)))) ? ((void) 0) : (_mi_assert_fail("size <= (MI_SMALL_SIZE_MAX + MI_PADDING_SIZE)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 516, __func__));
  const size_t idx = _mi_wsize_from_size(size);
  (idx < ((128 + ((((sizeof(mi_padding_t)) + (1 << 3)) - 1) / (1 << 3))) + 1)) ? ((void) 0) : (_mi_assert_fail("idx < MI_PAGES_DIRECT", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 518, __func__));
  return heap->pages_free_direct[idx];
}

inline static mi_segment_t *_mi_ptr_segment(const void *p)
{
  mi_segment_t * const segment = (mi_segment_t *) ((((uintptr_t) p) - 1) & (~((uintptr_t) ((1UL << (9 + (13 + 3))) - 1))));
  return (((intptr_t) segment) <= 0) ? (0) : (segment);
}

inline static mi_page_t *mi_slice_to_page(mi_slice_t *s)
{
  ((s->slice_offset == 0) && (s->slice_count > 0)) ? ((void) 0) : (_mi_assert_fail("s->slice_offset== 0 && s->slice_count > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 537, __func__));
  return (mi_page_t *) s;
}

inline static mi_slice_t *mi_page_to_slice(mi_page_t *p)
{
  ((p->slice_offset == 0) && (p->slice_count > 0)) ? ((void) 0) : (_mi_assert_fail("p->slice_offset== 0 && p->slice_count > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 542, __func__));
  return (mi_slice_t *) p;
}

inline static mi_segment_t *_mi_page_segment(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 548, __func__));
  mi_segment_t *segment = _mi_ptr_segment(page);
  ((segment == 0) || ((((mi_slice_t *) page) >= segment->slices) && (((mi_slice_t *) page) < (segment->slices + segment->slice_entries)))) ? ((void) 0) : (_mi_assert_fail("segment == NULL || ((mi_slice_t*)page >= segment->slices && (mi_slice_t*)page < segment->slices + segment->slice_entries)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 550, __func__));
  return segment;
}

inline static mi_slice_t *mi_slice_first(const mi_slice_t *slice)
{
  mi_slice_t *start = (mi_slice_t *) (((uint8_t *) slice) - slice->slice_offset);
  (start >= _mi_ptr_segment(slice)->slices) ? ((void) 0) : (_mi_assert_fail("start >= _mi_ptr_segment(slice)->slices", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 556, __func__));
  (start->slice_offset == 0) ? ((void) 0) : (_mi_assert_fail("start->slice_offset == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 557, __func__));
  ((start + start->slice_count) > slice) ? ((void) 0) : (_mi_assert_fail("start + start->slice_count > slice", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 558, __func__));
  return start;
}

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

inline static uint8_t *mi_page_start(const mi_page_t *page)
{
  (page->page_start != 0) ? ((void) 0) : (_mi_assert_fail("page->page_start != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 578, __func__));
  ;
  return page->page_start;
}

inline static mi_page_t *_mi_ptr_page(void *p)
{
  (p != 0) ? ((void) 0) : (_mi_assert_fail("p!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 585, __func__));
  return _mi_segment_page_of(_mi_ptr_segment(p), p);
}

inline static size_t mi_page_block_size(const mi_page_t *page)
{
  (page->block_size > 0) ? ((void) 0) : (_mi_assert_fail("page->block_size > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 591, __func__));
  return page->block_size;
}

inline static bool mi_page_is_huge(const mi_page_t *page)
{
  ((page->is_huge && (_mi_page_segment(page)->kind == MI_SEGMENT_HUGE)) || ((!page->is_huge) && (_mi_page_segment(page)->kind != MI_SEGMENT_HUGE))) ? ((void) 0) : (_mi_assert_fail("(page->is_huge && _mi_page_segment(page)->kind == MI_SEGMENT_HUGE) || (!page->is_huge && _mi_page_segment(page)->kind != MI_SEGMENT_HUGE)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 596, __func__));
  return page->is_huge;
}

inline static size_t mi_page_usable_block_size(const mi_page_t *page)
{
  return mi_page_block_size(page) - (sizeof(mi_padding_t));
}

inline static size_t mi_segment_size(mi_segment_t *segment)
{
  return segment->segment_slices * (1UL << (13 + 3));
}

inline static uint8_t *mi_segment_end(mi_segment_t *segment)
{
  return ((uint8_t *) segment) + mi_segment_size(segment);
}

inline static mi_block_t *mi_page_thread_free(const mi_page_t *page)
{
  return (mi_block_t *) (atomic_load_explicit(&((mi_page_t *) page)->xthread_free, memory_order_relaxed) & (~3));
}

inline static mi_delayed_t mi_page_thread_free_flag(const mi_page_t *page)
{
  return (mi_delayed_t) (atomic_load_explicit(&((mi_page_t *) page)->xthread_free, memory_order_relaxed) & 3);
}

inline static mi_heap_t *mi_page_heap(const mi_page_t *page)
{
  return (mi_heap_t *) atomic_load_explicit(&((mi_page_t *) page)->xheap, memory_order_relaxed);
}

inline static void mi_page_set_heap(mi_page_t *page, mi_heap_t *heap)
{
  (mi_page_thread_free_flag(page) != MI_DELAYED_FREEING) ? ((void) 0) : (_mi_assert_fail("mi_page_thread_free_flag(page) != MI_DELAYED_FREEING", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 631, __func__));
  atomic_store_explicit(&page->xheap, (uintptr_t) heap, memory_order_release);
  if (heap != 0)
  {
    page->heap_tag = heap->tag;
  }
}

inline static mi_block_t *mi_tf_block(mi_thread_free_t tf)
{
  return (mi_block_t *) (tf & (~0x03));
}

inline static mi_delayed_t mi_tf_delayed(mi_thread_free_t tf)
{
  return (mi_delayed_t) (tf & 0x03);
}

inline static mi_thread_free_t mi_tf_make(mi_block_t *block, mi_delayed_t delayed)
{
  return (mi_thread_free_t) (((uintptr_t) block) | ((uintptr_t) delayed));
}

inline static mi_thread_free_t mi_tf_set_delayed(mi_thread_free_t tf, mi_delayed_t delayed)
{
  return mi_tf_make(mi_tf_block(tf), delayed);
}

inline static mi_thread_free_t mi_tf_set_block(mi_thread_free_t tf, mi_block_t *block)
{
  return mi_tf_make(block, mi_tf_delayed(tf));
}

inline static bool mi_page_all_free(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 656, __func__));
  return page->used == 0;
}

inline static bool mi_page_has_any_available(const mi_page_t *page)
{
  ((page != 0) && (page->reserved > 0)) ? ((void) 0) : (_mi_assert_fail("page != NULL && page->reserved > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 662, __func__));
  return (page->used < page->reserved) || (mi_page_thread_free(page) != 0);
}

inline static bool mi_page_immediate_available(const mi_page_t *page)
{
  (page != 0) ? ((void) 0) : (_mi_assert_fail("page != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 668, __func__));
  return page->free != 0;
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

inline static mi_page_queue_t *mi_page_queue(const mi_heap_t *heap, size_t size)
{
  return &((mi_heap_t *) heap)->pages[_mi_bin(size)];
}

inline static bool mi_page_is_in_full(const mi_page_t *page)
{
  return page->flags.x.in_full;
}

inline static void mi_page_set_in_full(mi_page_t *page, bool in_full)
{
  page->flags.x.in_full = in_full;
}

inline static bool mi_page_has_aligned(const mi_page_t *page)
{
  return page->flags.x.has_aligned;
}

inline static void mi_page_set_has_aligned(mi_page_t *page, bool has_aligned)
{
  page->flags.x.has_aligned = has_aligned;
}

inline static bool mi_is_in_same_segment(const void *p, const void *q)
{
  return _mi_ptr_segment(p) == _mi_ptr_segment(q);
}

inline static bool mi_is_in_same_page(const void *p, const void *q)
{
  mi_segment_t *segment = _mi_ptr_segment(p);
  if (_mi_ptr_segment(q) != segment)
  {
    return 0;
  }
  mi_page_t *page = _mi_segment_page_of(segment, p);
  size_t psize;
  uint8_t *start = _mi_segment_page_start(segment, page, &psize);
  return (start <= ((uint8_t *) q)) && (((uint8_t *) q) < (start + psize));
}

inline static uintptr_t mi_rotl(uintptr_t x, uintptr_t shift)
{
  shift %= (1 << 3) * 8;
  return (shift == 0) ? (x) : ((x << shift) | (x >> (((1 << 3) * 8) - shift)));
}

inline static uintptr_t mi_rotr(uintptr_t x, uintptr_t shift)
{
  shift %= (1 << 3) * 8;
  return (shift == 0) ? (x) : ((x >> shift) | (x << (((1 << 3) * 8) - shift)));
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

inline static void mi_commit_mask_create_empty(mi_commit_mask_t *cm)
{
  for (size_t i = 0; i < (((1UL << (9 + (13 + 3))) / (1UL << (13 + 3))) / ((1 << 3) * 8)); i += 1)
  {
    cm->mask[i] = 0;
  }

}

inline static void mi_commit_mask_create_full(mi_commit_mask_t *cm)
{
  for (size_t i = 0; i < (((1UL << (9 + (13 + 3))) / (1UL << (13 + 3))) / ((1 << 3) * 8)); i += 1)
  {
    cm->mask[i] = ~((size_t) 0);
  }

}

inline static bool mi_commit_mask_is_empty(const mi_commit_mask_t *cm)
{
  for (size_t i = 0; i < (((1UL << (9 + (13 + 3))) / (1UL << (13 + 3))) / ((1 << 3) * 8)); i += 1)
  {
    if (cm->mask[i] != 0)
    {
      return 0;
    }
  }

  return 1;
}

inline static bool mi_commit_mask_is_full(const mi_commit_mask_t *cm)
{
  for (size_t i = 0; i < (((1UL << (9 + (13 + 3))) / (1UL << (13 + 3))) / ((1 << 3) * 8)); i += 1)
  {
    if (cm->mask[i] != (~((size_t) 0)))
    {
      return 0;
    }
  }

  return 1;
}

size_t _mi_commit_mask_committed_size(const mi_commit_mask_t *cm, size_t total);
size_t _mi_commit_mask_next_run(const mi_commit_mask_t *cm, size_t *idx);
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

inline static size_t mi_clz(size_t x)
{
  if (x == 0)
  {
    return (1 << 3) * 8;
  }
  return __builtin_clzll(x);
}

inline static size_t mi_ctz(size_t x)
{
  if (x == 0)
  {
    return (1 << 3) * 8;
  }
  return __builtin_ctzll(x);
}

inline static size_t mi_bsr(size_t x)
{
  return (x == 0) ? ((1 << 3) * 8) : ((((1 << 3) * 8) - 1) - mi_clz(x));
}

size_t _mi_popcount_generic(size_t x);
inline static size_t mi_popcount(size_t x)
{
  if (x <= 1)
  {
    return x;
  }
  if (x == SIZE_MAX)
  {
    return (1 << 3) * 8;
  }
  return __builtin_popcountll(x);
}

inline static void _mi_memcpy(void *dst, const void *src, size_t n)
{
  memcpy(dst, src, n);
}

inline static void _mi_memzero(void *dst, size_t n)
{
  memset(dst, 0, n);
}

inline static void _mi_memcpy_aligned(void *dst, const void *src, size_t n)
{
  (((((uintptr_t) dst) % (1 << 3)) == 0) && ((((uintptr_t) src) % (1 << 3)) == 0)) ? ((void) 0) : (_mi_assert_fail("((uintptr_t)dst % MI_INTPTR_SIZE == 0) && ((uintptr_t)src % MI_INTPTR_SIZE == 0)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 1128, __func__));
  void *adst = __builtin_assume_aligned(dst, 1 << 3);
  const void *asrc = __builtin_assume_aligned(src, 1 << 3);
  _mi_memcpy(adst, asrc, n);
}

inline static void _mi_memzero_aligned(void *dst, size_t n)
{
  ((((uintptr_t) dst) % (1 << 3)) == 0) ? ((void) 0) : (_mi_assert_fail("(uintptr_t)dst % MI_INTPTR_SIZE == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h", 1135, __func__));
  void *adst = __builtin_assume_aligned(dst, 1 << 3);
  _mi_memzero(adst, n);
}

typedef struct mi_os_mem_config_s
{
  size_t page_size;
  size_t large_page_size;
  size_t alloc_granularity;
  size_t physical_memory_in_kib;
  size_t virtual_address_bits;
  bool has_overcommit;
  bool has_partial_free;
  bool has_virtual_reserve;
} mi_os_mem_config_t;
void _mi_prim_mem_init(mi_os_mem_config_t *config);
int _mi_prim_free(void *addr, size_t size);
int _mi_prim_alloc(void *hint_addr, size_t size, size_t try_alignment, bool commit, bool allow_large, bool *is_large, bool *is_zero, void **addr);
int _mi_prim_commit(void *addr, size_t size, bool *is_zero);
int _mi_prim_decommit(void *addr, size_t size, bool *needs_recommit);
int _mi_prim_reset(void *addr, size_t size);
int _mi_prim_reuse(void *addr, size_t size);
int _mi_prim_protect(void *addr, size_t size, bool protect);
int _mi_prim_alloc_huge_os_pages(void *hint_addr, size_t size, int numa_node, bool *is_zero, void **addr);
size_t _mi_prim_numa_node(void);
size_t _mi_prim_numa_node_count(void);
mi_msecs_t _mi_prim_clock_now(void);
typedef struct mi_process_info_s
{
  mi_msecs_t elapsed;
  mi_msecs_t utime;
  mi_msecs_t stime;
  size_t current_rss;
  size_t peak_rss;
  size_t current_commit;
  size_t peak_commit;
  size_t page_faults;
} mi_process_info_t;
void _mi_prim_process_info(mi_process_info_t *pinfo);
void _mi_prim_out_stderr(const char *msg);
bool _mi_prim_getenv(const char *name, char *result, size_t result_size);
bool _mi_prim_random_buf(void *buf, size_t buf_len);
void _mi_prim_thread_init_auto_done(void);
void _mi_prim_thread_done_auto_done(void);
void _mi_prim_thread_associate_default_heap(mi_heap_t *heap);
extern mi_heap_t *_mi_heap_default;
extern bool _mi_process_is_initialized;
inline static mi_threadid_t _mi_prim_thread_id(void);
inline static mi_threadid_t _mi_prim_thread_id(void)
{
  return (uintptr_t) __builtin_thread_pointer();
}

inline static mi_heap_t *mi_prim_get_default_heap(void);
inline static mi_heap_t *mi_prim_get_default_heap(void)
{
  return _mi_heap_default;
}

static long mi_max_error_count = 16;
static long mi_max_warning_count = 16;
static void mi_add_stderr_output(void);
int mi_version(void)
{
  return 225;
}

typedef enum mi_init_e
{
  UNINIT,
  DEFAULTED,
  INITIALIZED
} mi_init_t;
typedef struct mi_option_desc_s
{
  long value;
  mi_init_t init;
  mi_option_t option;
  const char *name;
  const char *legacy_name;
} mi_option_desc_t;
static mi_option_desc_t options[_mi_option_last] = {{1, UNINIT, mi_option_show_errors, "show_errors", 0}, {0, UNINIT, mi_option_show_stats, "show_stats", 0}, {0, UNINIT, mi_option_verbose, "verbose", 0}, {1, UNINIT, mi_option_eager_commit, "eager_commit", 0}, {2, UNINIT, mi_option_arena_eager_commit, "arena_eager_commit", "eager_region_commit"}, {1, UNINIT, mi_option_purge_decommits, "purge_decommits", "reset_decommits"}, {2, UNINIT, mi_option_allow_large_os_pages, "allow_large_os_pages", "large_os_pages"}, {0, UNINIT, mi_option_reserve_huge_os_pages, "reserve_huge_os_pages", 0}, {-1, UNINIT, mi_option_reserve_huge_os_pages_at, "reserve_huge_os_pages_at", 0}, {0, UNINIT, mi_option_reserve_os_memory, "reserve_os_memory", 0}, {0, UNINIT, mi_option_deprecated_segment_cache, "deprecated_segment_cache", 0}, {0, UNINIT, mi_option_deprecated_page_reset, "deprecated_page_reset", 0}, {0, UNINIT, mi_option_abandoned_page_purge, "abandoned_page_purge", "abandoned_page_reset"}, {0, UNINIT, mi_option_deprecated_segment_reset, "deprecated_segment_reset", 0}, {1, UNINIT, mi_option_eager_commit_delay, "eager_commit_delay", 0}, {10, UNINIT, mi_option_purge_delay, "purge_delay", "reset_delay"}, {0, UNINIT, mi_option_use_numa_nodes, "use_numa_nodes", 0}, {0, UNINIT, mi_option_disallow_os_alloc, "disallow_os_alloc", "limit_os_alloc"}, {100, UNINIT, mi_option_os_tag, "os_tag", 0}, {32, UNINIT, mi_option_max_errors, "max_errors", 0}, {32, UNINIT, mi_option_max_warnings, "max_warnings", 0}, {10, UNINIT, mi_option_max_segment_reclaim, "max_segment_reclaim", 0}, {0, UNINIT, mi_option_destroy_on_exit, "destroy_on_exit", 0}, {1024L * 1024L, UNINIT, mi_option_arena_reserve, "arena_reserve", 0}, {10, UNINIT, mi_option_arena_purge_mult, "arena_purge_mult", 0}, {1, UNINIT, mi_option_purge_extend_delay, "purge_extend_delay", "decommit_extend_delay"}, {0, UNINIT, mi_option_abandoned_reclaim_on_free, "abandoned_reclaim_on_free", 0}, {0, UNINIT, mi_option_disallow_arena_alloc, "disallow_arena_alloc", 0}, {400, UNINIT, mi_option_retry_on_oom, "retry_on_oom", 0}, {0, UNINIT, mi_option_visit_abandoned, "visit_abandoned", 0}, {0, UNINIT, mi_option_guarded_min, "guarded_min", 0}, {(1024UL * 1024UL) * 1024UL, UNINIT, mi_option_guarded_max, "guarded_max", 0}, {0, UNINIT, mi_option_guarded_precise, "guarded_precise", 0}, {0, UNINIT, mi_option_guarded_sample_rate, "guarded_sample_rate", 0}, {0, UNINIT, mi_option_guarded_sample_seed, "guarded_sample_seed", 0}, {0, UNINIT, mi_option_target_segments_per_thread, "target_segments_per_thread", 0}, {10000, UNINIT, mi_option_generic_collect, "generic_collect", 0}};
static void mi_option_init(mi_option_desc_t *desc);
static bool mi_option_has_size_in_kib(mi_option_t option)
{
  return (option == mi_option_reserve_os_memory) || (option == mi_option_arena_reserve);
}

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

void mi_options_print(void)
{
  const int vermajor = 225 / 100;
  const int verminor = (225 % 100) / 10;
  const int verpatch = 225 % 10;
  _mi_message("v%i.%i.%i%s%s (built on %s, %s)\n", vermajor, verminor, verpatch, "", "", "Oct 23 2025", "11:20:56");
  for (int i = 0; i < _mi_option_last; i += 1)
  {
    mi_option_t option = (mi_option_t) i;
    long l = mi_option_get(option);
    (void) l;
    mi_option_desc_t *desc = &options[option];
    _mi_message("option '%s': %ld %s\n", desc->name, desc->value, (mi_option_has_size_in_kib(option)) ? ("KiB") : (""));
  }

  _mi_message("debug level : %d\n", 2);
  _mi_message("secure level: %d\n", 0);
  _mi_message("mem tracking: %s\n", "none");
}

long _mi_option_get_fast(mi_option_t option)
{
  ((option >= 0) && (option < _mi_option_last)) ? ((void) 0) : (_mi_assert_fail("option >= 0 && option < _mi_option_last", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/options.c", 238, __func__));
  mi_option_desc_t *desc = &options[option];
  (desc->option == option) ? ((void) 0) : (_mi_assert_fail("desc->option == option", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/options.c", 240, __func__));
  return desc->value;
}

long mi_option_get(mi_option_t option)
{
  ((option >= 0) && (option < _mi_option_last)) ? ((void) 0) : (_mi_assert_fail("option >= 0 && option < _mi_option_last", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/options.c", 247, __func__));
  if ((option < 0) || (option >= _mi_option_last))
  {
    return 0;
  }
  mi_option_desc_t *desc = &options[option];
  (desc->option == option) ? ((void) 0) : (_mi_assert_fail("desc->option == option", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/options.c", 250, __func__));
  if (__builtin_expect(!(!(desc->init == UNINIT)), 0))
  {
    mi_option_init(desc);
  }
  return desc->value;
}

long mi_option_get_clamp(mi_option_t option, long min, long max)
{
  long x = mi_option_get(option);
  return (x < min) ? (min) : ((x > max) ? (max) : (x));
}

size_t mi_option_get_size(mi_option_t option)
{
  const long x = mi_option_get(option);
  size_t size = (x < 0) ? (0) : ((size_t) x);
  if (mi_option_has_size_in_kib(option))
  {
    size *= 1024UL;
  }
  return size;
}

void mi_option_set(mi_option_t option, long value)
{
  ((option >= 0) && (option < _mi_option_last)) ? ((void) 0) : (_mi_assert_fail("option >= 0 && option < _mi_option_last", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/options.c", 272, __func__));
  if ((option < 0) || (option >= _mi_option_last))
  {
    return;
  }
  mi_option_desc_t *desc = &options[option];
  (desc->option == option) ? ((void) 0) : (_mi_assert_fail("desc->option == option", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/options.c", 275, __func__));
  desc->value = value;
  desc->init = INITIALIZED;
  if ((desc->option == mi_option_guarded_min) && (_mi_option_get_fast(mi_option_guarded_max) < value))
  {
    mi_option_set(mi_option_guarded_max, value);
  }
  else
    if ((desc->option == mi_option_guarded_max) && (_mi_option_get_fast(mi_option_guarded_min) > value))
  {
    mi_option_set(mi_option_guarded_min, value);
  }
}

void mi_option_set_default(mi_option_t option, long value)
{
  ((option >= 0) && (option < _mi_option_last)) ? ((void) 0) : (_mi_assert_fail("option >= 0 && option < _mi_option_last", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/options.c", 288, __func__));
  if ((option < 0) || (option >= _mi_option_last))
  {
    return;
  }
  mi_option_desc_t *desc = &options[option];
  if (desc->init != INITIALIZED)
  {
    desc->value = value;
  }
}

bool mi_option_is_enabled(mi_option_t option)
{
  return mi_option_get(option) != 0;
}

void mi_option_set_enabled(mi_option_t option, bool enable)
{
  mi_option_set(option, (enable) ? (1) : (0));
}

void mi_option_set_enabled_default(mi_option_t option, bool enable)
{
  mi_option_set_default(option, (enable) ? (1) : (0));
}

void mi_option_enable(mi_option_t option)
{
  mi_option_set_enabled(option, 1);
}

void mi_option_disable(mi_option_t option)
{
  mi_option_set_enabled(option, 0);
}

static void mi_out_stderr(const char *msg, void *arg)
{
  (void) arg;
  if ((msg != 0) && (msg[0] != 0))
  {
    _mi_prim_out_stderr(msg);
  }
}

static char out_buf[((size_t) (16 * 1024)) + 1];
static _Atomic size_t out_len;
static void mi_out_buf(const char *msg, void *arg)
{
  (void) arg;
  if (msg == 0)
  {
    return;
  }
  if (atomic_load_explicit(&out_len, memory_order_relaxed) >= ((size_t) (16 * 1024)))
  {
    return;
  }
  size_t n = _mi_strlen(msg);
  if (n == 0)
  {
    return;
  }
  size_t start = atomic_fetch_add_explicit(&out_len, n, memory_order_acq_rel);
  if (start >= ((size_t) (16 * 1024)))
  {
    return;
  }
  if ((start + n) >= ((size_t) (16 * 1024)))
  {
    n = (((size_t) (16 * 1024)) - start) - 1;
  }
  _mi_memcpy(&out_buf[start], msg, n);
}

static void mi_out_buf_flush(mi_output_fun *out, bool no_more_buf, void *arg)
{
  if (out == 0)
  {
    return;
  }
  size_t count = atomic_fetch_add_explicit(&out_len, (no_more_buf) ? ((size_t) (16 * 1024)) : (1), memory_order_acq_rel);
  if (count > ((size_t) (16 * 1024)))
  {
    count = (size_t) (16 * 1024);
  }
  out_buf[count] = 0;
  out(out_buf, arg);
  if (!no_more_buf)
  {
    out_buf[count] = '\n';
  }
}

static void mi_out_buf_stderr(const char *msg, void *arg)
{
  mi_out_stderr(msg, arg);
  mi_out_buf(msg, arg);
}

static mi_output_fun * volatile mi_out_default;
static void * _Atomic mi_out_arg;
static mi_output_fun *mi_out_get_default(void **parg)
{
  if (parg != 0)
  {
    *parg = atomic_load_explicit(&mi_out_arg, memory_order_acquire);
  }
  mi_output_fun *out = mi_out_default;
  return (out == 0) ? (&mi_out_buf) : (out);
}

void mi_register_output(mi_output_fun *out, void *arg)
{
  mi_out_default = (out == 0) ? (&mi_out_stderr) : (out);
  atomic_store_explicit(&mi_out_arg, arg, memory_order_release);
  if (out != 0)
  {
    mi_out_buf_flush(out, 1, arg);
  }
}

static void mi_add_stderr_output(void)
{
  (mi_out_default == 0) ? ((void) 0) : (_mi_assert_fail("mi_out_default == NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/options.c", 395, __func__));
  mi_out_buf_flush(&mi_out_stderr, 0, 0);
  mi_out_default = &mi_out_buf_stderr;
}

static _Atomic size_t error_count;
static _Atomic size_t warning_count;
static bool recurse = 0;
static bool mi_recurse_enter_prim(void)
{
  if (recurse)
  {
    return 0;
  }
  recurse = 1;
  return 1;
}

static void mi_recurse_exit_prim(void)
{
  recurse = 0;
}

static bool mi_recurse_enter(void)
{
  return mi_recurse_enter_prim();
}

static void mi_recurse_exit(void)
{
  mi_recurse_exit_prim();
}

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

static void mi_vfprintf(mi_output_fun *out, void *arg, const char *prefix, const char *fmt, va_list args)
{
  char buf[512];
  if (fmt == 0)
  {
    return;
  }
  if (!mi_recurse_enter())
  {
    return;
  }
  _mi_vsnprintf(buf, (sizeof(buf)) - 1, fmt, args);
  mi_recurse_exit();
  _mi_fputs(out, arg, prefix, buf);
}

void _mi_fprintf(mi_output_fun *out, void *arg, const char *fmt, ...)
{
  va_list args;
  __builtin_va_start(args);
  mi_vfprintf(out, arg, 0, fmt, args);
  ;
}

static void mi_vfprintf_thread(mi_output_fun *out, void *arg, const char *prefix, const char *fmt, va_list args)
{
  if (((prefix != 0) && (_mi_strnlen(prefix, 33) <= 32)) && (!_mi_is_main_thread()))
  {
    char tprefix[64];
    _mi_snprintf(tprefix, sizeof(tprefix), "%sthread 0x%tx: ", prefix, (uintptr_t) _mi_thread_id());
    mi_vfprintf(out, arg, tprefix, fmt, args);
  }
  else
  {
    mi_vfprintf(out, arg, prefix, fmt, args);
  }
}

void _mi_message(const char *fmt, ...)
{
  va_list args;
  __builtin_va_start(args);
  mi_vfprintf_thread(0, 0, "mimalloc: ", fmt, args);
  ;
}

void _mi_trace_message(const char *fmt, ...)
{
  if (mi_option_get(mi_option_verbose) <= 1)
  {
    return;
  }
  va_list args;
  __builtin_va_start(args);
  mi_vfprintf_thread(0, 0, "mimalloc: ", fmt, args);
  ;
}

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

static void mi_show_error_message(const char *fmt, va_list args)
{
  if (!mi_option_is_enabled(mi_option_verbose))
  {
    if (!mi_option_is_enabled(mi_option_show_errors))
    {
      return;
    }
    if ((mi_max_error_count >= 0) && (((long) atomic_fetch_add_explicit(&error_count, (uintptr_t) 1, memory_order_acq_rel)) > mi_max_error_count))
    {
      return;
    }
  }
  mi_vfprintf_thread(0, 0, "mimalloc: error: ", fmt, args);
}

void _mi_warning_message(const char *fmt, ...)
{
  if (!mi_option_is_enabled(mi_option_verbose))
  {
    if (!mi_option_is_enabled(mi_option_show_errors))
    {
      return;
    }
    if ((mi_max_warning_count >= 0) && (((long) atomic_fetch_add_explicit(&warning_count, (uintptr_t) 1, memory_order_acq_rel)) > mi_max_warning_count))
    {
      return;
    }
  }
  va_list args;
  __builtin_va_start(args);
  mi_vfprintf_thread(0, 0, "mimalloc: warning: ", fmt, args);
  ;
}

void _mi_assert_fail(const char *assertion, const char *fname, unsigned line, const char *func)
{
  _mi_fprintf(0, 0, "mimalloc: assertion failed: at \"%s\":%u, %s\n  assertion: \"%s\"\n", fname, line, (func == 0) ? ("") : (func), assertion);
  abort();
}

static mi_error_fun * volatile mi_error_handler;
static void * _Atomic mi_error_arg;
static void mi_error_default(int err)
{
  (void) err;
  if (err == 14)
  {
    abort();
  }
}

void mi_register_error(mi_error_fun *fun, void *arg)
{
  mi_error_handler = fun;
  atomic_store_explicit(&mi_error_arg, arg, memory_order_release);
}

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

static void mi_option_init(mi_option_desc_t *desc)
{
  char s[64 + 1];
  char buf[64 + 1];
  _mi_strlcpy(buf, "mimalloc_", sizeof(buf));
  _mi_strlcat(buf, desc->name, sizeof(buf));
  bool found = _mi_getenv(buf, s, sizeof(s));
  if ((!found) && (desc->legacy_name != 0))
  {
    _mi_strlcpy(buf, "mimalloc_", sizeof(buf));
    _mi_strlcat(buf, desc->legacy_name, sizeof(buf));
    found = _mi_getenv(buf, s, sizeof(s));
    if (found)
    {
      _mi_warning_message("environment option \"mimalloc_%s\" is deprecated -- use \"mimalloc_%s\" instead.\n", desc->legacy_name, desc->name);
    }
  }
  if (found)
  {
    helper_mi_option_init_1(desc, s, buf);
  }
  else
    if (!_mi_preloading())
  {
    desc->init = DEFAULTED;
  }
}

void helper_mi_option_init_1(mi_option_desc_t * const desc, char s[64 + 1], char buf[64 + 1])
{
  size_t len = _mi_strnlen(s, (sizeof(buf)) - 1);
  for (size_t i = 0; i < len; i += 1)
  {
    buf[i] = _mi_toupper(s[i]);
  }

  buf[len] = 0;
  if ((buf[0] == 0) || (strstr("1;TRUE;YES;ON", buf) != 0))
  {
    desc->value = 1;
    desc->init = INITIALIZED;
  }
  else
    if (strstr("0;FALSE;NO;OFF", buf) != 0)
  {
    desc->value = 0;
    desc->init = INITIALIZED;
  }
  else
  {
    helper_helper_mi_option_init_1_1(desc, buf);
  }
  (desc->init != UNINIT) ? ((void) 0) : (_mi_assert_fail("desc->init != UNINIT", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/options.c", 658, __func__));
}

void helper_helper_mi_option_init_1_1(mi_option_desc_t * const desc, char buf[64 + 1])
{
  char *end = buf;
  unsigned int end_idx = 0;
  long value = strtol(buf, &(&end[end_idx]), 10);
  if (mi_option_has_size_in_kib(desc->option))
  {
    size_t size = (value < 0) ? (0) : ((size_t) value);
    bool overflow = 0;
    if (end[end_idx] == 'K')
    {
      end_idx += 1;
    }
    else
      if (end[end_idx] == 'M')
    {
      overflow = mi_mul_overflow(size, 1024UL, &size);
      end_idx += 1;
    }
    else
      if (end[end_idx] == 'G')
    {
      overflow = mi_mul_overflow(size, 1024UL * 1024UL, &size);
      end_idx += 1;
    }
    else
      if (end[end_idx] == 'T')
    {
      overflow = mi_mul_overflow(size, (1024UL * 1024UL) * 1024UL, &size);
      end_idx += 1;
    }
    else
    {
      size = ((size + 1024UL) - 1) / 1024UL;
    }
    if ((end[0 + end_idx] == 'I') && (end[1 + end_idx] == 'B'))
    {
      end_idx += 2;
    }
    else
      if (end[end_idx] == 'B')
    {
      end_idx += 1;
    }
    if (overflow || (size > PTRDIFF_MAX))
    {
      size = PTRDIFF_MAX / 1024UL;
    }
    value = (size > 9223372036854775807L) ? (9223372036854775807L) : ((long) size);
  }
  if (end[end_idx] == 0)
  {
    mi_option_set(desc->option, value);
  }
  else
  {
    desc->init = DEFAULTED;
    if ((desc->option == mi_option_verbose) && (desc->value == 0))
    {
      desc->value = 1;
      _mi_warning_message("environment option mimalloc_%s has an invalid value.\n", desc->name);
      desc->value = 0;
    }
    else
    {
      _mi_warning_message("environment option mimalloc_%s has an invalid value.\n", desc->name);
    }
  }
}

