#include <alloc-override.c>
#include <atomic.h>
#include <errno.h>
#include <free.c>
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

static void mi_check_padding(const mi_page_t *page, const mi_block_t *block);
static bool mi_check_is_double_free(const mi_page_t *page, const mi_block_t *block);
static size_t mi_page_usable_size_of(const mi_page_t *page, const mi_block_t *block);
static void mi_stat_free(const mi_page_t *page, const mi_block_t *block);
static void mi_free_block_mt(mi_page_t *page, mi_segment_t *segment, mi_block_t *block);
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

inline static void mi_block_check_unguard(mi_page_t *page, mi_block_t *block, void *p)
{
  (void) page;
  (void) block;
  (void) p;
}

static void mi_free_generic_local(mi_page_t *page, mi_segment_t *segment, void *p)
{
  (void) segment;
  mi_block_t * const block = (mi_page_has_aligned(page)) ? (_mi_page_ptr_unalign(page, p)) : ((mi_block_t *) p);
  mi_block_check_unguard(page, block, p);
  mi_free_block_local(page, block, 1, 1);
}

static void mi_free_generic_mt(mi_page_t *page, mi_segment_t *segment, void *p)
{
  mi_block_t * const block = _mi_page_ptr_unalign(page, p);
  mi_block_check_unguard(page, block, p);
  mi_free_block_mt(page, segment, block);
}

void _mi_free_generic(mi_segment_t *segment, mi_page_t *page, bool is_local, void *p)
{
  if (is_local)
  {
    mi_free_generic_local(page, segment, p);
  }
  else
    mi_free_generic_mt(page, segment, p);
}

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

static size_t mi_page_usable_aligned_size_of(const mi_page_t *page, const void *p)
{
  const mi_block_t *block = _mi_page_ptr_unalign(page, p);
  const size_t size = mi_page_usable_size_of(page, block);
  const ptrdiff_t adjust = ((uint8_t *) p) - ((uint8_t *) block);
  ((adjust >= 0) && (((size_t) adjust) <= size)) ? ((void) 0) : (_mi_assert_fail("adjust >= 0 && (size_t)adjust <= size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 315, __func__));
  const size_t aligned_size = size - adjust;
  return aligned_size;
}

inline static size_t _mi_usable_size(const void *p, const char *msg)
{
  const mi_segment_t * const segment = mi_checked_ptr_segment(p, msg);
  if (__builtin_expect(!(!(segment == 0)), 0))
  {
    return 0;
  }
  const mi_page_t * const page = _mi_segment_page_of(segment, p);
  if (__builtin_expect(!(!(!mi_page_has_aligned(page))), 1))
  {
    const mi_block_t *block = (const mi_block_t *) p;
    return mi_page_usable_size_of(page, block);
  }
  else
  {
    return mi_page_usable_aligned_size_of(page, p);
  }
}

size_t mi_usable_size(const void *p)
{
  return _mi_usable_size(p, "mi_usable_size");
}

void mi_free_size(void *p, size_t size)
{
  ;
  const size_t available = _mi_usable_size(p, "mi_free_size");
  (((p == 0) || (size <= available)) || (available == 0)) ? ((void) 0) : (_mi_assert_fail("p == NULL || size <= available || available == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 352, __func__));
  mi_free(p);
}

void mi_free_size_aligned(void *p, size_t size, size_t alignment)
{
  ;
  ((((uintptr_t) p) % alignment) == 0) ? ((void) 0) : (_mi_assert_fail("((uintptr_t)p % alignment) == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 359, __func__));
  mi_free_size(p, size);
}

void mi_free_aligned(void *p, size_t alignment)
{
  ;
  ((((uintptr_t) p) % alignment) == 0) ? ((void) 0) : (_mi_assert_fail("((uintptr_t)p % alignment) == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 365, __func__));
  mi_free(p);
}

static bool mi_list_contains(const mi_page_t *page, const mi_block_t *list, const mi_block_t *elem)
{
  unsigned int list_idx = 0;
  while ((&list[list_idx]) != 0)
  {
    if (elem == (&list[list_idx]))
    {
      return 1;
    }
    list_idx = mi_block_next(page, list_idx);
  }

  return 0;
}

static bool mi_check_is_double_freex(const mi_page_t *page, const mi_block_t *block)
{
  if ((mi_list_contains(page, page->free, block) || mi_list_contains(page, page->local_free, block)) || mi_list_contains(page, mi_page_thread_free(page), block))
  {
    _mi_error_message(11, "double free detected of block %p with size %zu\n", block, mi_page_block_size(page));
    return 1;
  }
  return 0;
}

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

static bool mi_page_decode_padding(const mi_page_t *page, const mi_block_t *block, size_t *delta, size_t *bsize)
{
  *bsize = mi_page_usable_block_size(page);
  const mi_padding_t * const padding = (mi_padding_t *) (((uint8_t *) block) + (*bsize));
  ;
  *delta = padding->delta;
  uint32_t canary = padding->canary;
  uintptr_t keys[2];
  keys[0] = page->keys[0];
  keys[1] = page->keys[1];
  bool ok = (mi_ptr_encode_canary(page, block, keys) == canary) && ((*delta) <= (*bsize));
  ;
  return ok;
}

static size_t mi_page_usable_size_of(const mi_page_t *page, const mi_block_t *block)
{
  size_t bsize;
  size_t delta;
  bool ok = mi_page_decode_padding(page, block, &delta, &bsize);
  (ok) ? ((void) 0) : (_mi_assert_fail("ok", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 445, __func__));
  (delta <= bsize) ? ((void) 0) : (_mi_assert_fail("delta <= bsize", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 445, __func__));
  return (ok) ? (bsize - delta) : (0);
}

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

static bool mi_verify_padding(const mi_page_t *page, const mi_block_t *block, size_t *size, size_t *wrong)
{
  size_t bsize;
  size_t delta;
  bool ok = mi_page_decode_padding(page, block, &delta, &bsize);
  *size = (*wrong = bsize);
  if (!ok)
  {
    return 0;
  }
  (bsize >= delta) ? ((void) 0) : (_mi_assert_fail("bsize >= delta", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 489, __func__));
  *size = bsize - delta;
  if (!mi_page_is_huge(page))
  {
    uint8_t *fill = (((uint8_t *) block) + bsize) - delta;
    const size_t maxpad = (delta > 16) ? (16) : (delta);
    ;
    for (size_t i = 0; i < maxpad; i += 1)
    {
      if (fill[i] != 0xDE)
      {
        *wrong = (bsize - delta) + i;
        ok = 0;
        break;
      }
    }

    ;
  }
  return ok;
}

static void mi_check_padding(const mi_page_t *page, const mi_block_t *block)
{
  size_t size;
  size_t wrong;
  if (!mi_verify_padding(page, block, &size, &wrong))
  {
    _mi_error_message(14, "buffer overflow in heap block %p of size %zu: write after %zu bytes\n", block, size, wrong);
  }
}

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

inline extern void *_mi_page_malloc_zero(mi_heap_t *heap, mi_page_t *page, size_t size, bool zero)
{
  (size >= (sizeof(mi_padding_t))) ? ((void) 0) : (_mi_assert_fail("size >= MI_PADDING_SIZE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 33, __func__));
  ((page->block_size == 0) || (mi_page_block_size(page) >= size)) ? ((void) 0) : (_mi_assert_fail("page->block_size == 0 || mi_page_block_size(page) >= size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 34, __func__));
  mi_block_t * const block = page->free;
  if (__builtin_expect(!(!(block == 0)), 0))
  {
    return _mi_malloc_generic(heap, size, zero, 0);
  }
  ((block != 0) && (_mi_ptr_page(block) == page)) ? ((void) 0) : (_mi_assert_fail("block != NULL && _mi_ptr_page(block) == page", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 41, __func__));
  page->free = mi_block_next(page, block);
  page->used += 1;
  ((page->free == 0) || (_mi_ptr_page(page->free) == page)) ? ((void) 0) : (_mi_assert_fail("page->free == NULL || _mi_ptr_page(page->free) == page", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 46, __func__));
  ((page->block_size < 16) || _mi_is_aligned(block, 16)) ? ((void) 0) : (_mi_assert_fail("page->block_size < MI_MAX_ALIGN_SIZE || _mi_is_aligned(block, MI_MAX_ALIGN_SIZE)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 47, __func__));
  ;
  if (__builtin_expect(!(!zero), 0))
  {
    (page->block_size != 0) ? ((void) 0) : (_mi_assert_fail("page->block_size != 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 62, __func__));
    (!mi_page_is_huge(page)) ? ((void) 0) : (_mi_assert_fail("!mi_page_is_huge(page)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 63, __func__));
    (page->block_size >= (sizeof(mi_padding_t))) ? ((void) 0) : (_mi_assert_fail("page->block_size >= MI_PADDING_SIZE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 65, __func__));
    if (page->free_is_zero)
    {
      block->next = 0;
      ;
    }
    else
    {
      _mi_memzero_aligned(block, page->block_size - (sizeof(mi_padding_t)));
    }
  }
  if ((!zero) && (!mi_page_is_huge(page)))
  {
    memset(block, 0xD0, mi_page_usable_block_size(page));
  }
  const size_t bsize = mi_page_usable_block_size(page);
  if (bsize <= ((1UL << (3 + (13 + 3))) / 8))
  {
    _mi_stat_increase(&heap->tld->stats.malloc_normal, bsize);
    _mi_stat_counter_increase(&heap->tld->stats.malloc_normal_count, 1);
    const size_t bin = _mi_bin(bsize);
    _mi_stat_increase(&heap->tld->stats.malloc_bins[bin], 1);
    _mi_stat_increase(&heap->tld->stats.malloc_requested, size - (sizeof(mi_padding_t)));
  }
  mi_padding_t * const padding = (mi_padding_t *) (((uint8_t *) block) + mi_page_usable_block_size(page));
  ptrdiff_t delta = (((uint8_t *) padding) - ((uint8_t *) block)) - (size - (sizeof(mi_padding_t)));
  ((delta >= 0) && (mi_page_usable_block_size(page) >= ((size - (sizeof(mi_padding_t))) + delta))) ? ((void) 0) : (_mi_assert_fail("delta >= 0 && mi_page_usable_block_size(page) >= (size - MI_PADDING_SIZE + delta)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 101, __func__));
  ;
  padding->canary = mi_ptr_encode_canary(page, block, page->keys);
  padding->delta = (uint32_t) delta;
  if (!mi_page_is_huge(page))
  {
    uint8_t *fill = ((uint8_t *) padding) - delta;
    const size_t maxpad = (delta > 16) ? (16) : (delta);
    for (size_t i = 0; i < maxpad; i += 1)
    {
      fill[i] = 0xDE;
    }

  }
  return block;
}

extern void *_mi_page_malloc(mi_heap_t *heap, mi_page_t *page, size_t size)
{
  return _mi_page_malloc_zero(heap, page, size, 0);
}

extern void *_mi_page_malloc_zeroed(mi_heap_t *heap, mi_page_t *page, size_t size)
{
  return _mi_page_malloc_zero(heap, page, size, 1);
}

inline static void *mi_heap_malloc_small_zero(mi_heap_t *heap, size_t size, bool zero)
{
  (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 131, __func__));
  (size <= (128 * (sizeof(void *)))) ? ((void) 0) : (_mi_assert_fail("size <= MI_SMALL_SIZE_MAX", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 132, __func__));
  const uintptr_t tid = _mi_thread_id();
  ((heap->thread_id == 0) || (heap->thread_id == tid)) ? ((void) 0) : (_mi_assert_fail("heap->thread_id == 0 || heap->thread_id == tid", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 135, __func__));
  if (size == 0)
  {
    size = sizeof(void *);
  }
  mi_page_t *page = _mi_heap_get_free_small_page(heap, size + (sizeof(mi_padding_t)));
  void * const p = _mi_page_malloc_zero(heap, page, size + (sizeof(mi_padding_t)), zero);
  if (p != 0)
  {
    (mi_usable_size(p) == size) ? ((void) 0) : (_mi_assert_fail("mi_usable_size(p)==(size)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 149, __func__));
    ;
  }
  ;
  return p;
}

inline extern void *mi_heap_malloc_small(mi_heap_t *heap, size_t size)
{
  return mi_heap_malloc_small_zero(heap, size, 0);
}

inline extern void *mi_malloc_small(size_t size)
{
  return mi_heap_malloc_small(mi_prim_get_default_heap(), size);
}

inline extern void *_mi_heap_malloc_zero_ex(mi_heap_t *heap, size_t size, bool zero, size_t huge_alignment)
{
  if (__builtin_expect(!(!(size <= (128 * (sizeof(void *))))), 1))
  {
    (huge_alignment == 0) ? ((void) 0) : (_mi_assert_fail("huge_alignment == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 172, __func__));
    return mi_heap_malloc_small_zero(heap, size, zero);
  }
  else
  {
    (heap != 0) ? ((void) 0) : (_mi_assert_fail("heap!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 182, __func__));
    ((heap->thread_id == 0) || (heap->thread_id == _mi_thread_id())) ? ((void) 0) : (_mi_assert_fail("heap->thread_id == 0 || heap->thread_id == _mi_thread_id()", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 183, __func__));
    void * const p = _mi_malloc_generic(heap, size + (sizeof(mi_padding_t)), zero, huge_alignment);
    if (p != 0)
    {
      (mi_usable_size(p) == size) ? ((void) 0) : (_mi_assert_fail("mi_usable_size(p)==(size)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 185, __func__));
      ;
    }
    ;
    return p;
  }
}

inline extern void *_mi_heap_malloc_zero(mi_heap_t *heap, size_t size, bool zero)
{
  return _mi_heap_malloc_zero_ex(heap, size, zero, 0);
}

inline extern void *mi_heap_malloc(mi_heap_t *heap, size_t size)
{
  return _mi_heap_malloc_zero(heap, size, 0);
}

inline extern void *mi_malloc(size_t size)
{
  return mi_heap_malloc(mi_prim_get_default_heap(), size);
}

void *mi_zalloc_small(size_t size)
{
  return mi_heap_malloc_small_zero(mi_prim_get_default_heap(), size, 1);
}

inline extern void *mi_heap_zalloc(mi_heap_t *heap, size_t size)
{
  return _mi_heap_malloc_zero(heap, size, 1);
}

void *mi_zalloc(size_t size)
{
  return mi_heap_zalloc(mi_prim_get_default_heap(), size);
}

inline extern void *mi_heap_calloc(mi_heap_t *heap, size_t count, size_t size)
{
  size_t total;
  if (mi_count_size_overflow(count, size, &total))
  {
    return 0;
  }
  return mi_heap_zalloc(heap, total);
}

void *mi_calloc(size_t count, size_t size)
{
  return mi_heap_calloc(mi_prim_get_default_heap(), count, size);
}

extern void *mi_heap_mallocn(mi_heap_t *heap, size_t count, size_t size)
{
  size_t total;
  if (mi_count_size_overflow(count, size, &total))
  {
    return 0;
  }
  return mi_heap_malloc(heap, total);
}

void *mi_mallocn(size_t count, size_t size)
{
  return mi_heap_mallocn(mi_prim_get_default_heap(), count, size);
}

void *mi_expand(void *p, size_t newsize)
{
  (void) p;
  (void) newsize;
  return 0;
}

void *_mi_heap_realloc_zero(mi_heap_t *heap, void *p, size_t newsize, bool zero)
{
  const size_t size = _mi_usable_size(p, "mi_realloc");
  if (__builtin_expect(!(!(((newsize <= size) && (newsize >= (size / 2))) && (newsize > 0))), 0))
  {
    (p != 0) ? ((void) 0) : (_mi_assert_fail("p!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c", 263, __func__));
    return p;
  }
  void *newp = mi_heap_malloc(heap, newsize);
  if (__builtin_expect(!(!(newp != 0)), 1))
  {
    if (zero && (newsize > size))
    {
      const size_t start = (size >= (sizeof(intptr_t))) ? (size - (sizeof(intptr_t))) : (0);
      _mi_memzero(((uint8_t *) newp) + start, newsize - start);
    }
    else
      if (newsize == 0)
    {
      ((uint8_t *) newp)[0] = 0;
    }
    if (__builtin_expect(!(!(p != 0)), 1))
    {
      const size_t copysize = (newsize > size) ? (size) : (newsize);
      ;
      _mi_memcpy(newp, p, copysize);
      mi_free(p);
    }
  }
  return newp;
}

void *mi_heap_realloc(mi_heap_t *heap, void *p, size_t newsize)
{
  return _mi_heap_realloc_zero(heap, p, newsize, 0);
}

void *mi_heap_reallocn(mi_heap_t *heap, void *p, size_t count, size_t size)
{
  size_t total;
  if (mi_count_size_overflow(count, size, &total))
  {
    return 0;
  }
  return mi_heap_realloc(heap, p, total);
}

void *mi_heap_reallocf(mi_heap_t *heap, void *p, size_t newsize)
{
  void *newp = mi_heap_realloc(heap, p, newsize);
  if ((newp == 0) && (p != 0))
  {
    mi_free(p);
  }
  return newp;
}

void *mi_heap_rezalloc(mi_heap_t *heap, void *p, size_t newsize)
{
  return _mi_heap_realloc_zero(heap, p, newsize, 1);
}

void *mi_heap_recalloc(mi_heap_t *heap, void *p, size_t count, size_t size)
{
  size_t total;
  if (mi_count_size_overflow(count, size, &total))
  {
    return 0;
  }
  return mi_heap_rezalloc(heap, p, total);
}

void *mi_realloc(void *p, size_t newsize)
{
  return mi_heap_realloc(mi_prim_get_default_heap(), p, newsize);
}

void *mi_reallocn(void *p, size_t count, size_t size)
{
  return mi_heap_reallocn(mi_prim_get_default_heap(), p, count, size);
}

void *mi_reallocf(void *p, size_t newsize)
{
  return mi_heap_reallocf(mi_prim_get_default_heap(), p, newsize);
}

void *mi_rezalloc(void *p, size_t newsize)
{
  return mi_heap_rezalloc(mi_prim_get_default_heap(), p, newsize);
}

void *mi_recalloc(void *p, size_t count, size_t size)
{
  return mi_heap_recalloc(mi_prim_get_default_heap(), p, count, size);
}

char *mi_heap_strdup(mi_heap_t *heap, const char *s)
{
  if (s == 0)
  {
    return 0;
  }
  size_t len = _mi_strlen(s);
  char *t = (char *) mi_heap_malloc(heap, len + 1);
  if (t == 0)
  {
    return 0;
  }
  _mi_memcpy(t, s, len);
  t[len] = 0;
  return t;
}

char *mi_strdup(const char *s)
{
  return mi_heap_strdup(mi_prim_get_default_heap(), s);
}

char *mi_heap_strndup(mi_heap_t *heap, const char *s, size_t n)
{
  if (s == 0)
  {
    return 0;
  }
  const size_t len = _mi_strnlen(s, n);
  char *t = (char *) mi_heap_malloc(heap, len + 1);
  if (t == 0)
  {
    return 0;
  }
  _mi_memcpy(t, s, len);
  t[len] = 0;
  return t;
}

char *mi_strndup(const char *s, size_t n)
{
  return mi_heap_strndup(mi_prim_get_default_heap(), s, n);
}

char *mi_heap_realpath(mi_heap_t *heap, const char *fname, char *resolved_name)
{
  if (resolved_name != 0)
  {
    return realpath(fname, resolved_name);
  }
  else
  {
    char *rname = realpath(fname, 0);
    if (rname == 0)
    {
      return 0;
    }
    char *result = mi_heap_strdup(heap, rname);
    mi_cfree(rname);
    return result;
  }
}

char *mi_realpath(const char *fname, char *resolved_name)
{
  return mi_heap_realpath(mi_prim_get_default_heap(), fname, resolved_name);
}

typedef void (*std_new_handler_t)(void);
std_new_handler_t _ZSt15get_new_handlerv(void)
{
  return 0;
}

static std_new_handler_t mi_get_new_handler(void)
{
  return _ZSt15get_new_handlerv();
}

static bool mi_try_new_handler(bool nothrow)
{
  std_new_handler_t h = mi_get_new_handler();
  if (h == 0)
  {
    _mi_error_message(12, "out of memory in 'new'");
    if (!nothrow)
    {
      abort();
    }
    return 0;
  }
  else
  {
    h();
    return 1;
  }
}

void *mi_heap_try_new(mi_heap_t *heap, size_t size, bool nothrow)
{
  void *p = 0;
  unsigned int p_idx = 0;
  while (((&p[p_idx]) == 0) && mi_try_new_handler(nothrow))
  {
    p_idx = mi_heap_malloc(heap, size);
  }

  return p;
}

static void *mi_try_new(size_t size, bool nothrow)
{
  return mi_heap_try_new(mi_prim_get_default_heap(), size, nothrow);
}

void *mi_heap_alloc_new(mi_heap_t *heap, size_t size)
{
  void *p = mi_heap_malloc(heap, size);
  if (__builtin_expect(!(!(p == 0)), 0))
  {
    return mi_heap_try_new(heap, size, 0);
  }
  return p;
}

void *mi_new(size_t size)
{
  return mi_heap_alloc_new(mi_prim_get_default_heap(), size);
}

void *mi_heap_alloc_new_n(mi_heap_t *heap, size_t count, size_t size)
{
  size_t total;
  if (__builtin_expect(!(!mi_count_size_overflow(count, size, &total)), 0))
  {
    mi_try_new_handler(0);
    return 0;
  }
  else
  {
    return mi_heap_alloc_new(heap, total);
  }
}

void *mi_new_n(size_t count, size_t size)
{
  return mi_heap_alloc_new_n(mi_prim_get_default_heap(), count, size);
}

void *mi_new_nothrow(size_t size)
{
  void *p = mi_malloc(size);
  if (__builtin_expect(!(!(p == 0)), 0))
  {
    return mi_try_new(size, 1);
  }
  return p;
}

void *mi_new_aligned(size_t size, size_t alignment)
{
  void *p;
  unsigned int p_idx = 0;
  do
  {
    p_idx = mi_malloc_aligned(size, alignment);
  }
  while (((&p[p_idx]) == 0) && mi_try_new_handler(0));
  return p;
}

void *mi_new_aligned_nothrow(size_t size, size_t alignment)
{
  void *p;
  unsigned int p_idx = 0;
  do
  {
    p_idx = mi_malloc_aligned(size, alignment);
  }
  while (((&p[p_idx]) == 0) && mi_try_new_handler(1));
  return p;
}

void *mi_new_realloc(void *p, size_t newsize)
{
  void *q;
  unsigned int q_idx = 0;
  do
  {
    q_idx = mi_realloc(p, newsize);
  }
  while (((&q[q_idx]) == 0) && mi_try_new_handler(0));
  return q;
}

void *mi_new_reallocn(void *p, size_t newcount, size_t size)
{
  size_t total;
  if (__builtin_expect(!(!mi_count_size_overflow(newcount, size, &total)), 0))
  {
    mi_try_new_handler(0);
    return 0;
  }
  else
  {
    return mi_new_realloc(p, total);
  }
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

static void mi_check_padding(const mi_page_t *page, const mi_block_t *block);
static bool mi_check_is_double_free(const mi_page_t *page, const mi_block_t *block);
static size_t mi_page_usable_size_of(const mi_page_t *page, const mi_block_t *block);
static void mi_stat_free(const mi_page_t *page, const mi_block_t *block);
static void mi_free_block_mt(mi_page_t *page, mi_segment_t *segment, mi_block_t *block);
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

inline static void mi_block_check_unguard(mi_page_t *page, mi_block_t *block, void *p)
{
  (void) page;
  (void) block;
  (void) p;
}

static void mi_free_generic_local(mi_page_t *page, mi_segment_t *segment, void *p)
{
  (void) segment;
  mi_block_t * const block = (mi_page_has_aligned(page)) ? (_mi_page_ptr_unalign(page, p)) : ((mi_block_t *) p);
  mi_block_check_unguard(page, block, p);
  mi_free_block_local(page, block, 1, 1);
}

static void mi_free_generic_mt(mi_page_t *page, mi_segment_t *segment, void *p)
{
  mi_block_t * const block = _mi_page_ptr_unalign(page, p);
  mi_block_check_unguard(page, block, p);
  mi_free_block_mt(page, segment, block);
}

void _mi_free_generic(mi_segment_t *segment, mi_page_t *page, bool is_local, void *p)
{
  if (is_local)
  {
    mi_free_generic_local(page, segment, p);
  }
  else
    mi_free_generic_mt(page, segment, p);
}

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

static size_t mi_page_usable_aligned_size_of(const mi_page_t *page, const void *p)
{
  const mi_block_t *block = _mi_page_ptr_unalign(page, p);
  const size_t size = mi_page_usable_size_of(page, block);
  const ptrdiff_t adjust = ((uint8_t *) p) - ((uint8_t *) block);
  ((adjust >= 0) && (((size_t) adjust) <= size)) ? ((void) 0) : (_mi_assert_fail("adjust >= 0 && (size_t)adjust <= size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 315, __func__));
  const size_t aligned_size = size - adjust;
  return aligned_size;
}

inline static size_t _mi_usable_size(const void *p, const char *msg)
{
  const mi_segment_t * const segment = mi_checked_ptr_segment(p, msg);
  if (__builtin_expect(!(!(segment == 0)), 0))
  {
    return 0;
  }
  const mi_page_t * const page = _mi_segment_page_of(segment, p);
  if (__builtin_expect(!(!(!mi_page_has_aligned(page))), 1))
  {
    const mi_block_t *block = (const mi_block_t *) p;
    return mi_page_usable_size_of(page, block);
  }
  else
  {
    return mi_page_usable_aligned_size_of(page, p);
  }
}

size_t mi_usable_size(const void *p)
{
  return _mi_usable_size(p, "mi_usable_size");
}

void mi_free_size(void *p, size_t size)
{
  ;
  const size_t available = _mi_usable_size(p, "mi_free_size");
  (((p == 0) || (size <= available)) || (available == 0)) ? ((void) 0) : (_mi_assert_fail("p == NULL || size <= available || available == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 352, __func__));
  mi_free(p);
}

void mi_free_size_aligned(void *p, size_t size, size_t alignment)
{
  ;
  ((((uintptr_t) p) % alignment) == 0) ? ((void) 0) : (_mi_assert_fail("((uintptr_t)p % alignment) == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 359, __func__));
  mi_free_size(p, size);
}

void mi_free_aligned(void *p, size_t alignment)
{
  ;
  ((((uintptr_t) p) % alignment) == 0) ? ((void) 0) : (_mi_assert_fail("((uintptr_t)p % alignment) == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 365, __func__));
  mi_free(p);
}

static bool mi_list_contains(const mi_page_t *page, const mi_block_t *list, const mi_block_t *elem)
{
  unsigned int list_idx = 0;
  while ((&list[list_idx]) != 0)
  {
    if (elem == (&list[list_idx]))
    {
      return 1;
    }
    list_idx = mi_block_next(page, list_idx);
  }

  return 0;
}

static bool mi_check_is_double_freex(const mi_page_t *page, const mi_block_t *block)
{
  if ((mi_list_contains(page, page->free, block) || mi_list_contains(page, page->local_free, block)) || mi_list_contains(page, mi_page_thread_free(page), block))
  {
    _mi_error_message(11, "double free detected of block %p with size %zu\n", block, mi_page_block_size(page));
    return 1;
  }
  return 0;
}

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

static bool mi_page_decode_padding(const mi_page_t *page, const mi_block_t *block, size_t *delta, size_t *bsize)
{
  *bsize = mi_page_usable_block_size(page);
  const mi_padding_t * const padding = (mi_padding_t *) (((uint8_t *) block) + (*bsize));
  ;
  *delta = padding->delta;
  uint32_t canary = padding->canary;
  uintptr_t keys[2];
  keys[0] = page->keys[0];
  keys[1] = page->keys[1];
  bool ok = (mi_ptr_encode_canary(page, block, keys) == canary) && ((*delta) <= (*bsize));
  ;
  return ok;
}

static size_t mi_page_usable_size_of(const mi_page_t *page, const mi_block_t *block)
{
  size_t bsize;
  size_t delta;
  bool ok = mi_page_decode_padding(page, block, &delta, &bsize);
  (ok) ? ((void) 0) : (_mi_assert_fail("ok", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 445, __func__));
  (delta <= bsize) ? ((void) 0) : (_mi_assert_fail("delta <= bsize", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 445, __func__));
  return (ok) ? (bsize - delta) : (0);
}

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

static bool mi_verify_padding(const mi_page_t *page, const mi_block_t *block, size_t *size, size_t *wrong)
{
  size_t bsize;
  size_t delta;
  bool ok = mi_page_decode_padding(page, block, &delta, &bsize);
  *size = (*wrong = bsize);
  if (!ok)
  {
    return 0;
  }
  (bsize >= delta) ? ((void) 0) : (_mi_assert_fail("bsize >= delta", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c", 489, __func__));
  *size = bsize - delta;
  if (!mi_page_is_huge(page))
  {
    uint8_t *fill = (((uint8_t *) block) + bsize) - delta;
    const size_t maxpad = (delta > 16) ? (16) : (delta);
    ;
    for (size_t i = 0; i < maxpad; i += 1)
    {
      if (fill[i] != 0xDE)
      {
        *wrong = (bsize - delta) + i;
        ok = 0;
        break;
      }
    }

    ;
  }
  return ok;
}

static void mi_check_padding(const mi_page_t *page, const mi_block_t *block)
{
  size_t size;
  size_t wrong;
  if (!mi_verify_padding(page, block, &size, &wrong))
  {
    _mi_error_message(14, "buffer overflow in heap block %p of size %zu: write after %zu bytes\n", block, size, wrong);
  }
}

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

