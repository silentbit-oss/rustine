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

static mi_os_mem_config_t mi_os_mem_config = {4096, 0, 4096, 32 * (1024UL * 1024UL), 48, 1, 0, 1};
bool _mi_os_has_overcommit(void)
{
  return mi_os_mem_config.has_overcommit;
}

bool _mi_os_has_virtual_reserve(void)
{
  return mi_os_mem_config.has_virtual_reserve;
}

size_t _mi_os_page_size(void)
{
  return mi_os_mem_config.page_size;
}

size_t _mi_os_large_page_size(void)
{
  return (mi_os_mem_config.large_page_size != 0) ? (mi_os_mem_config.large_page_size) : (_mi_os_page_size());
}

bool _mi_os_use_large_page(size_t size, size_t alignment)
{
  if ((mi_os_mem_config.large_page_size == 0) || (!mi_option_is_enabled(mi_option_allow_large_os_pages)))
  {
    return 0;
  }
  return ((size % mi_os_mem_config.large_page_size) == 0) && ((alignment % mi_os_mem_config.large_page_size) == 0);
}

size_t _mi_os_good_alloc_size(size_t size)
{
  size_t align_size;
  if (size < (512 * 1024UL))
  {
    align_size = _mi_os_page_size();
  }
  else
    if (size < (2 * (1024UL * 1024UL)))
  {
    align_size = 64 * 1024UL;
  }
  else
    if (size < (8 * (1024UL * 1024UL)))
  {
    align_size = 256 * 1024UL;
  }
  else
    if (size < (32 * (1024UL * 1024UL)))
  {
    align_size = 1 * (1024UL * 1024UL);
  }
  else
    align_size = 4 * (1024UL * 1024UL);
  if (__builtin_expect(!(!(size >= (SIZE_MAX - align_size))), 0))
  {
    return size;
  }
  return _mi_align_up(size, align_size);
}

void _mi_os_init(void)
{
  _mi_prim_mem_init(&mi_os_mem_config);
}

bool _mi_os_decommit(void *addr, size_t size);
bool _mi_os_commit(void *addr, size_t size, bool *is_zero);
static _Atomic uintptr_t aligned_base;
void *_mi_os_get_aligned_hint(size_t try_alignment, size_t size)
{
  if ((try_alignment <= 1) || (try_alignment > (1UL << (9 + (13 + 3)))))
  {
    return 0;
  }
  if (mi_os_mem_config.virtual_address_bits < 46)
  {
    return 0;
  }
  size = _mi_align_up(size, 1UL << (9 + (13 + 3)));
  if (size > (1 * ((1024UL * 1024UL) * 1024UL)))
  {
    return 0;
  }
  uintptr_t hint = atomic_fetch_add_explicit(&aligned_base, size, memory_order_acq_rel);
  if ((hint == 0) || (hint > (((uintptr_t) 30) << 40)))
  {
    uintptr_t init = ((uintptr_t) 2) << 40;
    uintptr_t expected = hint + size;
    atomic_compare_exchange_strong_explicit(&aligned_base, &expected, init, memory_order_acq_rel, memory_order_acquire);
    hint = atomic_fetch_add_explicit(&aligned_base, size, memory_order_acq_rel);
  }
  if ((hint % try_alignment) != 0)
  {
    return 0;
  }
  return (void *) hint;
}

static void mi_os_free_huge_os_pages(void *p, size_t size);
static void mi_os_prim_free(void *addr, size_t size, size_t commit_size)
{
  ((size % _mi_os_page_size()) == 0) ? ((void) 0) : (_mi_assert_fail("(size % _mi_os_page_size()) == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 154, __func__));
  if (addr == 0)
  {
    return;
  }
  int err = _mi_prim_free(addr, size);
  if (err != 0)
  {
    _mi_warning_message("unable to free OS memory (error: %d (0x%x), size: 0x%zx bytes, address: %p)\n", err, err, size, addr);
  }
  if (commit_size > 0)
  {
    _mi_stat_decrease(&_mi_stats_main.committed, commit_size);
  }
  _mi_stat_decrease(&_mi_stats_main.reserved, size);
}

void _mi_os_free_ex(void *addr, size_t size, bool still_committed, mi_memid_t memid)
{
  if (mi_memkind_is_os(memid.memkind))
  {
    size_t csize = memid.mem.os.size;
    if (csize == 0)
    {
      csize = _mi_os_good_alloc_size(size);
    }
    (csize >= size) ? ((void) 0) : (_mi_assert_fail("csize >= size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 170, __func__));
    size_t commit_size = (still_committed) ? (csize) : (0);
    void *base = addr;
    unsigned int base_idx = 0;
    if (memid.mem.os.base != (&base[base_idx]))
    {
      (memid.mem.os.base <= addr) ? ((void) 0) : (_mi_assert_fail("memid.mem.os.base <= addr", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 175, __func__));
      base_idx = memid.mem.os.base_idx;
      const size_t diff = ((uint8_t *) addr) - ((uint8_t *) memid.mem.os.base);
      if (memid.mem.os.size == 0)
      {
        csize += diff;
      }
      if (still_committed)
      {
        commit_size -= diff;
      }
    }
    if (memid.memkind == MI_MEM_OS_HUGE)
    {
      (memid.is_pinned) ? ((void) 0) : (_mi_assert_fail("memid.is_pinned", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 187, __func__));
      mi_os_free_huge_os_pages(base, csize);
    }
    else
    {
      mi_os_prim_free(base, csize, (still_committed) ? (commit_size) : (0));
    }
  }
  else
  {
    (memid.memkind < MI_MEM_OS) ? ((void) 0) : (_mi_assert_fail("memid.memkind < MI_MEM_OS", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 196, __func__));
  }
}

void _mi_os_free(void *p, size_t size, mi_memid_t memid)
{
  _mi_os_free_ex(p, size, 1, memid);
}

static void *mi_os_prim_alloc_at(void *hint_addr, size_t size, size_t try_alignment, bool commit, bool allow_large, bool *is_large, bool *is_zero)
{
  ((size > 0) && ((size % _mi_os_page_size()) == 0)) ? ((void) 0) : (_mi_assert_fail("size > 0 && (size % _mi_os_page_size()) == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 212, __func__));
  (is_zero != 0) ? ((void) 0) : (_mi_assert_fail("is_zero != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 213, __func__));
  (is_large != 0) ? ((void) 0) : (_mi_assert_fail("is_large != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 214, __func__));
  if (size == 0)
  {
    return 0;
  }
  if (!commit)
  {
    allow_large = 0;
  }
  if (try_alignment == 0)
  {
    try_alignment = 1;
  }
  *is_zero = 0;
  void *p = 0;
  int err = _mi_prim_alloc(hint_addr, size, try_alignment, commit, allow_large, is_large, is_zero, &p);
  if (err != 0)
  {
    _mi_warning_message("unable to allocate OS memory (error: %d (0x%x), addr: %p, size: 0x%zx bytes, align: 0x%zx, commit: %d, allow large: %d)\n", err, err, hint_addr, size, try_alignment, commit, allow_large);
  }
  _mi_stat_counter_increase(&_mi_stats_main.mmap_calls, 1);
  if (p != 0)
  {
    _mi_stat_increase(&_mi_stats_main.reserved, size);
    if (commit)
    {
      _mi_stat_increase(&_mi_stats_main.committed, size);
    }
  }
  return p;
}

static void *mi_os_prim_alloc(size_t size, size_t try_alignment, bool commit, bool allow_large, bool *is_large, bool *is_zero)
{
  return mi_os_prim_alloc_at(0, size, try_alignment, commit, allow_large, is_large, is_zero);
}

static void *mi_os_prim_alloc_aligned(size_t size, size_t alignment, bool commit, bool allow_large, bool *is_large, bool *is_zero, void **base)
{
  ((alignment >= _mi_os_page_size()) && ((alignment & (alignment - 1)) == 0)) ? ((void) 0) : (_mi_assert_fail("alignment >= _mi_os_page_size() && ((alignment & (alignment - 1)) == 0)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 250, __func__));
  ((size > 0) && ((size % _mi_os_page_size()) == 0)) ? ((void) 0) : (_mi_assert_fail("size > 0 && (size % _mi_os_page_size()) == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 251, __func__));
  (is_large != 0) ? ((void) 0) : (_mi_assert_fail("is_large != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 252, __func__));
  (is_zero != 0) ? ((void) 0) : (_mi_assert_fail("is_zero != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 253, __func__));
  (base != 0) ? ((void) 0) : (_mi_assert_fail("base != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 254, __func__));
  if (!commit)
  {
    allow_large = 0;
  }
  if (!((alignment >= _mi_os_page_size()) && ((alignment & (alignment - 1)) == 0)))
  {
    return 0;
  }
  size = _mi_align_up(size, _mi_os_page_size());
  void *p = mi_os_prim_alloc(size, alignment, commit, allow_large, is_large, is_zero);
  unsigned int p_idx = 0;
  if ((&p[p_idx]) == 0)
  {
    return 0;
  }
  if ((((uintptr_t) p) % alignment) == 0)
  {
    *base = &p[p_idx];
  }
  else
  {
    helper_mi_os_prim_alloc_aligned_1(&p_idx, size, alignment, commit, is_large, is_zero, base, p);
  }
  (((&p[p_idx]) == 0) || ((((&p[p_idx]) != 0) && ((*base) != 0)) && ((((uintptr_t) p) % alignment) == 0))) ? ((void) 0) : (_mi_assert_fail("p == NULL || (p != NULL && *base != NULL && ((uintptr_t)p % alignment) == 0)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 314, __func__));
  return p;
}

void *_mi_os_alloc(size_t size, mi_memid_t *memid)
{
  *memid = _mi_memid_none();
  if (size == 0)
  {
    return 0;
  }
  size = _mi_os_good_alloc_size(size);
  bool os_is_large = 0;
  bool os_is_zero = 0;
  void *p = mi_os_prim_alloc(size, 0, 1, 0, &os_is_large, &os_is_zero);
  if (p == 0)
  {
    return 0;
  }
  *memid = _mi_memid_create_os(p, size, 1, os_is_zero, os_is_large);
  (memid->mem.os.size >= size) ? ((void) 0) : (_mi_assert_fail("memid->mem.os.size >= size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 333, __func__));
  (memid->initially_committed) ? ((void) 0) : (_mi_assert_fail("memid->initially_committed", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 334, __func__));
  return p;
}

void *_mi_os_alloc_aligned(size_t size, size_t alignment, bool commit, bool allow_large, mi_memid_t *memid)
{
  (void) (&_mi_os_get_aligned_hint);
  *memid = _mi_memid_none();
  if (size == 0)
  {
    return 0;
  }
  size = _mi_os_good_alloc_size(size);
  alignment = _mi_align_up(alignment, _mi_os_page_size());
  bool os_is_large = 0;
  bool os_is_zero = 0;
  void *os_base = 0;
  void *p = mi_os_prim_alloc_aligned(size, alignment, commit, allow_large, &os_is_large, &os_is_zero, &os_base);
  if (p == 0)
  {
    return 0;
  }
  *memid = _mi_memid_create_os(p, size, commit, os_is_zero, os_is_large);
  memid->mem.os.base = os_base;
  memid->mem.os.size += ((uint8_t *) p) - ((uint8_t *) os_base);
  (memid->mem.os.size >= size) ? ((void) 0) : (_mi_assert_fail("memid->mem.os.size >= size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 356, __func__));
  (_mi_is_aligned(p, alignment)) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned(p,alignment)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 357, __func__));
  if (commit)
  {
    (memid->initially_committed) ? ((void) 0) : (_mi_assert_fail("memid->initially_committed", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 358, __func__));
  }
  return p;
}

static void *mi_os_ensure_zero(void *p, size_t size, mi_memid_t *memid)
{
  if ((p == 0) || (size == 0))
  {
    return p;
  }
  if (!memid->initially_committed)
  {
    bool is_zero = 0;
    if (!_mi_os_commit(p, size, &is_zero))
    {
      _mi_os_free(p, size, *memid);
      return 0;
    }
    memid->initially_committed = 1;
  }
  if (memid->initially_zero)
  {
    return p;
  }
  _mi_memzero_aligned(p, size);
  memid->initially_zero = 1;
  return p;
}

void *_mi_os_zalloc(size_t size, mi_memid_t *memid)
{
  void *p = _mi_os_alloc(size, memid);
  return mi_os_ensure_zero(p, size, memid);
}

void *_mi_os_alloc_aligned_at_offset(size_t size, size_t alignment, size_t offset, bool commit, bool allow_large, mi_memid_t *memid)
{
  (offset <= (1UL << (9 + (13 + 3)))) ? ((void) 0) : (_mi_assert_fail("offset <= MI_SEGMENT_SIZE", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 395, __func__));
  (offset <= size) ? ((void) 0) : (_mi_assert_fail("offset <= size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 396, __func__));
  ((alignment % _mi_os_page_size()) == 0) ? ((void) 0) : (_mi_assert_fail("(alignment % _mi_os_page_size()) == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 397, __func__));
  *memid = _mi_memid_none();
  if (offset > (1UL << (9 + (13 + 3))))
  {
    return 0;
  }
  if (offset == 0)
  {
    return _mi_os_alloc_aligned(size, alignment, commit, allow_large, memid);
  }
  else
  {
    const size_t extra = _mi_align_up(offset, alignment) - offset;
    const size_t oversize = size + extra;
    void * const start = _mi_os_alloc_aligned(oversize, alignment, commit, allow_large, memid);
    if (start == 0)
    {
      return 0;
    }
    void * const p = ((uint8_t *) start) + extra;
    (_mi_is_aligned(((uint8_t *) p) + offset, alignment)) ? ((void) 0) : (_mi_assert_fail("_mi_is_aligned((uint8_t*)p + offset, alignment)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 412, __func__));
    if (commit && (extra > _mi_os_page_size()))
    {
      _mi_os_decommit(start, extra);
    }
    return p;
  }
}

static void *mi_os_page_align_areax(bool conservative, void *addr, size_t size, size_t *newsize)
{
  ((addr != 0) && (size > 0)) ? ((void) 0) : (_mi_assert_fail("addr != NULL && size > 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 428, __func__));
  if (newsize != 0)
  {
    *newsize = 0;
  }
  if ((size == 0) || (addr == 0))
  {
    return 0;
  }
  void *start = (conservative) ? (mi_align_up_ptr(addr, _mi_os_page_size())) : (mi_align_down_ptr(addr, _mi_os_page_size()));
  void *end = (conservative) ? (mi_align_down_ptr(((uint8_t *) addr) + size, _mi_os_page_size())) : (mi_align_up_ptr(((uint8_t *) addr) + size, _mi_os_page_size()));
  ptrdiff_t diff = ((uint8_t *) end) - ((uint8_t *) start);
  if (diff <= 0)
  {
    return 0;
  }
  ((conservative && (((size_t) diff) <= size)) || ((!conservative) && (((size_t) diff) >= size))) ? ((void) 0) : (_mi_assert_fail("(conservative && (size_t)diff <= size) || (!conservative && (size_t)diff >= size)", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 440, __func__));
  if (newsize != 0)
  {
    *newsize = (size_t) diff;
  }
  return start;
}

static void *mi_os_page_align_area_conservative(void *addr, size_t size, size_t *newsize)
{
  return mi_os_page_align_areax(1, addr, size, newsize);
}

bool _mi_os_commit_ex(void *addr, size_t size, bool *is_zero, size_t stat_size)
{
  if (is_zero != 0)
  {
    *is_zero = 0;
  }
  _mi_stat_increase(&_mi_stats_main.committed, stat_size);
  _mi_stat_counter_increase(&_mi_stats_main.commit_calls, 1);
  size_t csize;
  void *start = mi_os_page_align_areax(0, addr, size, &csize);
  if (csize == 0)
  {
    return 1;
  }
  bool os_is_zero = 0;
  int err = _mi_prim_commit(start, csize, &os_is_zero);
  if (err != 0)
  {
    _mi_warning_message("cannot commit OS memory (error: %d (0x%x), address: %p, size: 0x%zx bytes)\n", err, err, start, csize);
    return 0;
  }
  if (os_is_zero && (is_zero != 0))
  {
    *is_zero = 1;
    ;
  }
  return 1;
}

bool _mi_os_commit(void *addr, size_t size, bool *is_zero)
{
  return _mi_os_commit_ex(addr, size, is_zero, size);
}

static bool mi_os_decommit_ex(void *addr, size_t size, bool *needs_recommit, size_t stat_size)
{
  (needs_recommit != 0) ? ((void) 0) : (_mi_assert_fail("needs_recommit!=NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 483, __func__));
  _mi_stat_decrease(&_mi_stats_main.committed, stat_size);
  size_t csize;
  void *start = mi_os_page_align_area_conservative(addr, size, &csize);
  if (csize == 0)
  {
    return 1;
  }
  *needs_recommit = 1;
  int err = _mi_prim_decommit(start, csize, needs_recommit);
  if (err != 0)
  {
    _mi_warning_message("cannot decommit OS memory (error: %d (0x%x), address: %p, size: 0x%zx bytes)\n", err, err, start, csize);
  }
  (err == 0) ? ((void) 0) : (_mi_assert_fail("err == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 497, __func__));
  return err == 0;
}

bool _mi_os_decommit(void *addr, size_t size)
{
  bool needs_recommit;
  return mi_os_decommit_ex(addr, size, &needs_recommit, size);
}

bool _mi_os_reset(void *addr, size_t size)
{
  size_t csize;
  void *start = mi_os_page_align_area_conservative(addr, size, &csize);
  if (csize == 0)
  {
    return 1;
  }
  _mi_stat_increase(&_mi_stats_main.reset, csize);
  _mi_stat_counter_increase(&_mi_stats_main.reset_calls, 1);
  memset(start, 0, csize);
  int err = _mi_prim_reset(start, csize);
  if (err != 0)
  {
    _mi_warning_message("cannot reset OS memory (error: %d (0x%x), address: %p, size: 0x%zx bytes)\n", err, err, start, csize);
  }
  return err == 0;
}

void _mi_os_reuse(void *addr, size_t size)
{
  size_t csize = 0;
  void * const start = mi_os_page_align_area_conservative(addr, size, &csize);
  if (csize == 0)
  {
    return;
  }
  const int err = _mi_prim_reuse(start, csize);
  if (err != 0)
  {
    _mi_warning_message("cannot reuse OS memory (error: %d (0x%x), address: %p, size: 0x%zx bytes)\n", err, err, start, csize);
  }
}

bool _mi_os_purge_ex(void *p, size_t size, bool allow_reset, size_t stat_size)
{
  if (mi_option_get(mi_option_purge_delay) < 0)
  {
    return 0;
  }
  _mi_stat_counter_increase(&_mi_stats_main.purge_calls, 1);
  _mi_stat_increase(&_mi_stats_main.purged, size);
  if (mi_option_is_enabled(mi_option_purge_decommits) && (!_mi_preloading()))
  {
    bool needs_recommit = 1;
    mi_os_decommit_ex(p, size, &needs_recommit, stat_size);
    return needs_recommit;
  }
  else
  {
    if (allow_reset)
    {
      _mi_os_reset(p, size);
    }
    return 0;
  }
}

bool _mi_os_purge(void *p, size_t size)
{
  return _mi_os_purge_ex(p, size, 1, size);
}

static bool mi_os_protectx(void *addr, size_t size, bool protect)
{
  size_t csize = 0;
  void *start = mi_os_page_align_area_conservative(addr, size, &csize);
  if (csize == 0)
  {
    return 0;
  }
  int err = _mi_prim_protect(start, csize, protect);
  if (err != 0)
  {
    _mi_warning_message("cannot %s OS memory (error: %d (0x%x), address: %p, size: 0x%zx bytes)\n", (protect) ? ("protect") : ("unprotect"), err, err, start, csize);
  }
  return err == 0;
}

bool _mi_os_protect(void *addr, size_t size)
{
  return mi_os_protectx(addr, size, 1);
}

bool _mi_os_unprotect(void *addr, size_t size)
{
  return mi_os_protectx(addr, size, 0);
}

static _Atomic uintptr_t mi_huge_start;
static uint8_t *mi_os_claim_huge_pages(size_t pages, size_t *total_size)
{
  if (total_size != 0)
  {
    *total_size = 0;
  }
  const size_t size = pages * ((1024UL * 1024UL) * 1024UL);
  uintptr_t start = 0;
  uintptr_t end = 0;
  uintptr_t huge_start = atomic_load_explicit(&mi_huge_start, memory_order_relaxed);
  do
  {
    start = huge_start;
    if (start == 0)
    {
      start = ((uintptr_t) 32) << 40;
    }
    end = start + size;
    ((end % (1UL << (9 + (13 + 3)))) == 0) ? ((void) 0) : (_mi_assert_fail("end % MI_SEGMENT_SIZE == 0", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 629, __func__));
  }
  while (!atomic_compare_exchange_strong_explicit(&mi_huge_start, &huge_start, end, memory_order_acq_rel, memory_order_acquire));
  if (total_size != 0)
  {
    *total_size = size;
  }
  return (uint8_t *) start;
}

void *_mi_os_alloc_huge_os_pages(size_t pages, int numa_node, mi_msecs_t max_msecs, size_t *pages_reserved, size_t *psize, mi_memid_t *memid)
{
  *memid = _mi_memid_none();
  if (psize != 0)
  {
    *psize = 0;
  }
  if (pages_reserved != 0)
  {
    *pages_reserved = 0;
  }
  size_t size = 0;
  uint8_t * const start = mi_os_claim_huge_pages(pages, &size);
  if (start == 0)
  {
    return 0;
  }
  mi_msecs_t start_t = _mi_clock_start();
  size_t page = 0;
  bool all_zero = 1;
  while (page < pages)
  {
    helper__mi_os_alloc_huge_os_pages_1(&page, &all_zero, pages, numa_node, max_msecs, start, start_t);
  }

  ((page * ((1024UL * 1024UL) * 1024UL)) <= size) ? ((void) 0) : (_mi_assert_fail("page*MI_HUGE_OS_PAGE_SIZE <= size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 700, __func__));
  if (pages_reserved != 0)
  {
    *pages_reserved = page;
  }
  if (psize != 0)
  {
    *psize = page * ((1024UL * 1024UL) * 1024UL);
  }
  if (page != 0)
  {
    (start != 0) ? ((void) 0) : (_mi_assert_fail("start != NULL", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 704, __func__));
    *memid = _mi_memid_create_os(start, size, 1, all_zero, 1);
    memid->memkind = MI_MEM_OS_HUGE;
    (memid->is_pinned) ? ((void) 0) : (_mi_assert_fail("memid->is_pinned", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 707, __func__));
  }
  return (page == 0) ? (0) : (start);
}

static void mi_os_free_huge_os_pages(void *p, size_t size)
{
  if ((p == 0) || (size == 0))
  {
    return;
  }
  uint8_t *base = (uint8_t *) p;
  unsigned int base_idx = 0;
  while (size >= ((1024UL * 1024UL) * 1024UL))
  {
    mi_os_prim_free(base, (1024UL * 1024UL) * 1024UL, (1024UL * 1024UL) * 1024UL);
    size -= (1024UL * 1024UL) * 1024UL;
    base_idx += (1024UL * 1024UL) * 1024UL;
  }

}

static _Atomic size_t mi_numa_node_count;
int _mi_os_numa_node_count(void)
{
  size_t count = atomic_load_explicit(&mi_numa_node_count, memory_order_acquire);
  if (__builtin_expect(!(!(count == 0)), 0))
  {
    long ncount = mi_option_get(mi_option_use_numa_nodes);
    if ((ncount > 0) && (ncount < 2147483647))
    {
      count = (size_t) ncount;
    }
    else
    {
      const size_t n = _mi_prim_numa_node_count();
      if ((n == 0) || (n > 2147483647))
      {
        count = 1;
      }
      else
      {
        count = n;
      }
    }
    atomic_store_explicit(&mi_numa_node_count, count, memory_order_release);
    _mi_verbose_message("using %zd numa regions\n", count);
  }
  ((count > 0) && (count <= 2147483647)) ? ((void) 0) : (_mi_assert_fail("count > 0 && count <= INT_MAX", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 749, __func__));
  return (int) count;
}

static int mi_os_numa_node_get(void)
{
  int numa_count = _mi_os_numa_node_count();
  if (numa_count <= 1)
  {
    return 0;
  }
  const size_t n = _mi_prim_numa_node();
  int numa_node = (n < 2147483647) ? ((int) n) : (0);
  if (numa_node >= numa_count)
  {
    numa_node = numa_node % numa_count;
  }
  return numa_node;
}

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

void *helper_mi_os_prim_alloc_aligned_1(unsigned int * const p_idx_ref, size_t size, size_t alignment, bool commit, bool * const is_large, bool * const is_zero, void ** const base, void * const p)
{
  unsigned int p_idx = *p_idx_ref;
  _mi_warning_message("unable to allocate aligned OS memory directly, fall back to over-allocation (size: 0x%zx bytes, address: %p, alignment: 0x%zx, commit: %d)\n", size, p, alignment, commit);
  if ((&p[p_idx]) != 0)
  {
    mi_os_prim_free(p, size, (commit) ? (size) : (0));
  }
  if (size >= (SIZE_MAX - alignment))
  {
    return 0;
  }
  const size_t over_size = size + alignment;
  if (!mi_os_mem_config.has_partial_free)
  {
    p_idx = mi_os_prim_alloc(over_size, 1, 0, 0, is_large, is_zero);
    if ((&p[p_idx]) == 0)
    {
      return 0;
    }
    *base = &p[p_idx];
    p_idx = mi_align_up_ptr(p_idx, alignment);
    if (commit)
    {
      if (!_mi_os_commit(p, size, 0))
      {
        mi_os_prim_free(*base, over_size, 0);
        return 0;
      }
    }
  }
  else
  {
    helper_helper_mi_os_prim_alloc_aligned_1_1(&p_idx, size, alignment, commit, is_large, is_zero, base, p, over_size);
  }
  *p_idx_ref = p_idx;
}

void helper__mi_os_alloc_huge_os_pages_1(size_t * const page_ref, bool * const all_zero_ref, size_t pages, int numa_node, mi_msecs_t max_msecs, uint8_t * const start, mi_msecs_t start_t)
{
  size_t page = *page_ref;
  bool all_zero = *all_zero_ref;
  bool is_zero = 0;
  void *addr = start + (page * ((1024UL * 1024UL) * 1024UL));
  void *p = 0;
  int err = _mi_prim_alloc_huge_os_pages(addr, (1024UL * 1024UL) * 1024UL, numa_node, &is_zero, &p);
  if (!is_zero)
  {
    all_zero = 0;
  }
  if (err != 0)
  {
    _mi_warning_message("unable to allocate huge OS page (error: %d (0x%x), address: %p, size: %zx bytes)\n", err, err, addr, (1024UL * 1024UL) * 1024UL);
    break;
  }
  if (p != addr)
  {
    if (p != 0)
    {
      _mi_warning_message("could not allocate contiguous huge OS page %zu at %p\n", page, addr);
      mi_os_prim_free(p, (1024UL * 1024UL) * 1024UL, (1024UL * 1024UL) * 1024UL);
    }
    break;
  }
  page += 1;
  _mi_stat_increase(&_mi_stats_main.committed, (1024UL * 1024UL) * 1024UL);
  _mi_stat_increase(&_mi_stats_main.reserved, (1024UL * 1024UL) * 1024UL);
  if (max_msecs > 0)
  {
    mi_msecs_t elapsed = _mi_clock_end(start_t);
    if (page >= 1)
    {
      mi_msecs_t estimate = (elapsed / (page + 1)) * pages;
      if (estimate > (2 * max_msecs))
      {
        elapsed = max_msecs + 1;
      }
    }
    if (elapsed > max_msecs)
    {
      _mi_warning_message("huge OS page allocation timed out (after allocating %zu page(s))\n", page);
      break;
    }
  }
  *page_ref = page;
  *all_zero_ref = all_zero;
}

void *helper_helper_mi_os_prim_alloc_aligned_1_1(unsigned int * const p_idx_ref, size_t size, size_t alignment, bool commit, bool * const is_large, bool * const is_zero, void ** const base, void * const p, const size_t over_size)
{
  unsigned int p_idx = *p_idx_ref;
  p_idx = mi_os_prim_alloc(over_size, 1, commit, 0, is_large, is_zero);
  if ((&p[p_idx]) == 0)
  {
    return 0;
  }
  void *aligned_p = mi_align_up_ptr(p, alignment);
  size_t pre_size = ((uint8_t *) aligned_p) - ((uint8_t *) p);
  size_t mid_size = _mi_align_up(size, _mi_os_page_size());
  size_t post_size = (over_size - pre_size) - mid_size;
  (((pre_size < over_size) && (post_size < over_size)) && (mid_size >= size)) ? ((void) 0) : (_mi_assert_fail("pre_size < over_size&& post_size < over_size&& mid_size >= size", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/os.c", 305, __func__));
  if (pre_size > 0)
  {
    mi_os_prim_free(p, pre_size, (commit) ? (pre_size) : (0));
  }
  if (post_size > 0)
  {
    mi_os_prim_free(((uint8_t *) aligned_p) + mid_size, post_size, (commit) ? (post_size) : (0));
  }
  p_idx = aligned_p;
  *base = aligned_p;
  *p_idx_ref = p_idx;
}

