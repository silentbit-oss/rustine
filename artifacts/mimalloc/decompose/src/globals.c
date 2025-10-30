extern bool _mi_process_is_initialized
/*** DEPENDENCIES:
***/


static _Atomic size_t mi_arena_count
/*** DEPENDENCIES:
***/


static _Atomic int64_t mi_arenas_purge_expire
/*** DEPENDENCIES:
***/


static uint8_t mi_arena_static[((1 << 3) / 2) * 1024UL]
/*** DEPENDENCIES:
***/


static _Atomic size_t mi_arena_static_top
/*** DEPENDENCIES:
***/


static _Atomic size_t thread_count = 1
/*** DEPENDENCIES:
***/


static bool os_preloading = 1
/*** DEPENDENCIES:
***/


static long mi_max_error_count = 16
/*** DEPENDENCIES:
***/


static long mi_max_warning_count = 16
/*** DEPENDENCIES:
***/


static char out_buf[((size_t) (16 * 1024)) + 1]
/*** DEPENDENCIES:
***/


static _Atomic size_t out_len
/*** DEPENDENCIES:
***/


static void * _Atomic mi_out_arg
/*** DEPENDENCIES:
***/


static _Atomic size_t error_count
/*** DEPENDENCIES:
***/


static _Atomic size_t warning_count
/*** DEPENDENCIES:
***/


static bool recurse = 0
/*** DEPENDENCIES:
***/


static void * _Atomic mi_error_arg
/*** DEPENDENCIES:
***/


static _Atomic uintptr_t aligned_base
/*** DEPENDENCIES:
***/


static _Atomic uintptr_t mi_huge_start
/*** DEPENDENCIES:
***/


static _Atomic size_t mi_numa_node_count
/*** DEPENDENCIES:
***/


static void * _Atomic deferred_arg
/*** DEPENDENCIES:
***/


extern char **environ
/*** DEPENDENCIES:
***/


pthread_key_t _mi_heap_default_key = (pthread_key_t) (-1)
/*** DEPENDENCIES:
***/


extern mi_stats_t _mi_stats_main
/*** DEPENDENCIES:
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
} mi_stats_t
----------------------------
***/


extern const mi_page_t _mi_page_empty
/*** DEPENDENCIES:
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
} mi_page_t
----------------------------
***/


extern const mi_heap_t _mi_heap_empty
/*** DEPENDENCIES:
None
----------------------------
***/


extern mi_heap_t *_mi_heap_default
/*** DEPENDENCIES:
None
----------------------------
***/


static mi_arena_t * _Atomic mi_arenas[132]
/*** DEPENDENCIES:
typedef struct mi_arena_s
{
  mi_arena_id_t id;
  mi_memid_t memid;
  uint8_t * _Atomic start;
  size_t block_count;
  size_t field_count;
  size_t meta_size;
  mi_memid_t meta_memid;
  int numa_node;
  bool exclusive;
  bool is_large;
  pthread_mutex_t abandoned_visit_lock;
  _Atomic size_t search_idx;
  _Atomic mi_msecs_t purge_expire;
  mi_bitmap_field_t *blocks_dirty;
  mi_bitmap_field_t *blocks_committed;
  mi_bitmap_field_t *blocks_purge;
  mi_bitmap_field_t *blocks_abandoned;
  mi_bitmap_field_t blocks_inuse[1];
} mi_arena_t
----------------------------
***/


static mi_subproc_t mi_subproc_default
/*** DEPENDENCIES:
None
----------------------------
***/


static const mi_tld_t tld_empty = {0, 0, 0, 0, {{{0, 0, 1}, {0, 0, 1}, {0, 0, 2}, {0, 0, 3}, {0, 0, 4}, {0, 0, 5}, {0, 0, 6}, {0, 0, 7}, {0, 0, 10}, {0, 0, 12}, {0, 0, 14}, {0, 0, 16}, {0, 0, 20}, {0, 0, 24}, {0, 0, 28}, {0, 0, 32}, {0, 0, 40}, {0, 0, 48}, {0, 0, 56}, {0, 0, 64}, {0, 0, 80}, {0, 0, 96}, {0, 0, 112}, {0, 0, 128}, {0, 0, 160}, {0, 0, 192}, {0, 0, 224}, {0, 0, 256}, {0, 0, 320}, {0, 0, 384}, {0, 0, 448}, {0, 0, 512}, {0, 0, 640}, {0, 0, 768}, {0, 0, 896}, {0, 0, 1024}}, 0, 0, 0, 0, 0, &mi_subproc_default, (mi_stats_t *) (((uint8_t *) (&tld_empty)) + offsetof(mi_tld_t, stats))}, {1, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0}, {0}, {0}, {0}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0}, {0}, {0}, {0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}}}
/*** DEPENDENCIES:
None
----------------------------
***/


extern mi_heap_t _mi_heap_main
/*** DEPENDENCIES:
None
----------------------------
***/


static mi_tld_t tld_main = {0, 0, &_mi_heap_main, &_mi_heap_main, {{{0, 0, 1}, {0, 0, 1}, {0, 0, 2}, {0, 0, 3}, {0, 0, 4}, {0, 0, 5}, {0, 0, 6}, {0, 0, 7}, {0, 0, 10}, {0, 0, 12}, {0, 0, 14}, {0, 0, 16}, {0, 0, 20}, {0, 0, 24}, {0, 0, 28}, {0, 0, 32}, {0, 0, 40}, {0, 0, 48}, {0, 0, 56}, {0, 0, 64}, {0, 0, 80}, {0, 0, 96}, {0, 0, 112}, {0, 0, 128}, {0, 0, 160}, {0, 0, 192}, {0, 0, 224}, {0, 0, 256}, {0, 0, 320}, {0, 0, 384}, {0, 0, 448}, {0, 0, 512}, {0, 0, 640}, {0, 0, 768}, {0, 0, 896}, {0, 0, 1024}}, 0, 0, 0, 0, 0, &mi_subproc_default, &tld_main.stats}, {1, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0}, {0}, {0}, {0}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0}, {0}, {0}, {0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}}}
/*** DEPENDENCIES:
None
----------------------------
***/


static mi_thread_data_t * _Atomic td_cache[32]
/*** DEPENDENCIES:
typedef struct mi_thread_data_s
{
  mi_heap_t heap;
  mi_tld_t tld;
  mi_memid_t memid;
} mi_thread_data_t
----------------------------
***/


static mi_option_desc_t options[_mi_option_last] = {{1, UNINIT, mi_option_show_errors, "show_errors", 0}, {0, UNINIT, mi_option_show_stats, "show_stats", 0}, {0, UNINIT, mi_option_verbose, "verbose", 0}, {1, UNINIT, mi_option_eager_commit, "eager_commit", 0}, {2, UNINIT, mi_option_arena_eager_commit, "arena_eager_commit", "eager_region_commit"}, {1, UNINIT, mi_option_purge_decommits, "purge_decommits", "reset_decommits"}, {2, UNINIT, mi_option_allow_large_os_pages, "allow_large_os_pages", "large_os_pages"}, {0, UNINIT, mi_option_reserve_huge_os_pages, "reserve_huge_os_pages", 0}, {-1, UNINIT, mi_option_reserve_huge_os_pages_at, "reserve_huge_os_pages_at", 0}, {0, UNINIT, mi_option_reserve_os_memory, "reserve_os_memory", 0}, {0, UNINIT, mi_option_deprecated_segment_cache, "deprecated_segment_cache", 0}, {0, UNINIT, mi_option_deprecated_page_reset, "deprecated_page_reset", 0}, {0, UNINIT, mi_option_abandoned_page_purge, "abandoned_page_purge", "abandoned_page_reset"}, {0, UNINIT, mi_option_deprecated_segment_reset, "deprecated_segment_reset", 0}, {1, UNINIT, mi_option_eager_commit_delay, "eager_commit_delay", 0}, {10, UNINIT, mi_option_purge_delay, "purge_delay", "reset_delay"}, {0, UNINIT, mi_option_use_numa_nodes, "use_numa_nodes", 0}, {0, UNINIT, mi_option_disallow_os_alloc, "disallow_os_alloc", "limit_os_alloc"}, {100, UNINIT, mi_option_os_tag, "os_tag", 0}, {32, UNINIT, mi_option_max_errors, "max_errors", 0}, {32, UNINIT, mi_option_max_warnings, "max_warnings", 0}, {10, UNINIT, mi_option_max_segment_reclaim, "max_segment_reclaim", 0}, {0, UNINIT, mi_option_destroy_on_exit, "destroy_on_exit", 0}, {1024L * 1024L, UNINIT, mi_option_arena_reserve, "arena_reserve", 0}, {10, UNINIT, mi_option_arena_purge_mult, "arena_purge_mult", 0}, {1, UNINIT, mi_option_purge_extend_delay, "purge_extend_delay", "decommit_extend_delay"}, {0, UNINIT, mi_option_abandoned_reclaim_on_free, "abandoned_reclaim_on_free", 0}, {0, UNINIT, mi_option_disallow_arena_alloc, "disallow_arena_alloc", 0}, {400, UNINIT, mi_option_retry_on_oom, "retry_on_oom", 0}, {0, UNINIT, mi_option_visit_abandoned, "visit_abandoned", 0}, {0, UNINIT, mi_option_guarded_min, "guarded_min", 0}, {(1024UL * 1024UL) * 1024UL, UNINIT, mi_option_guarded_max, "guarded_max", 0}, {0, UNINIT, mi_option_guarded_precise, "guarded_precise", 0}, {0, UNINIT, mi_option_guarded_sample_rate, "guarded_sample_rate", 0}, {0, UNINIT, mi_option_guarded_sample_seed, "guarded_sample_seed", 0}, {0, UNINIT, mi_option_target_segments_per_thread, "target_segments_per_thread", 0}, {10000, UNINIT, mi_option_generic_collect, "generic_collect", 0}}
/*** DEPENDENCIES:
typedef struct mi_option_desc_s
{
  long value;
  mi_init_t init;
  mi_option_t option;
  const char *name;
  const char *legacy_name;
} mi_option_desc_t
----------------------------
***/


static mi_output_fun * volatile mi_out_default
/*** DEPENDENCIES:
typedef void mi_output_fun(const char *msg, void *arg)
----------------------------
***/


static mi_error_fun * volatile mi_error_handler
/*** DEPENDENCIES:
typedef void mi_error_fun(int err, void *arg)
----------------------------
***/


static mi_os_mem_config_t mi_os_mem_config = {4096, 0, 4096, 32 * (1024UL * 1024UL), 48, 1, 0, 1}
/*** DEPENDENCIES:
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
} mi_os_mem_config_t
----------------------------
***/


static mi_deferred_free_fun * volatile deferred_free = 0
/*** DEPENDENCIES:
typedef void mi_deferred_free_fun(bool force, unsigned long long heartbeat, void *arg)
----------------------------
***/


static mi_segmap_part_t * _Atomic mi_segment_map[(((48 * 1024ULL) * ((1024UL * 1024UL) * 1024UL)) / ((8 * (((1 << 3) * 1024UL) - 128)) * (1UL << (9 + (13 + 3))))) + 1]
/*** DEPENDENCIES:
typedef struct mi_segmap_part_s
{
  mi_memid_t memid;
  _Atomic uintptr_t map[(((1 << 3) * 1024UL) - 128) / (1 << 3)];
} mi_segmap_part_t
----------------------------
***/


static mi_msecs_t mi_process_start
/*** DEPENDENCIES:
typedef int64_t mi_msecs_t
----------------------------
***/


static mi_msecs_t mi_clock_diff
/*** DEPENDENCIES:
typedef int64_t mi_msecs_t
----------------------------
***/


