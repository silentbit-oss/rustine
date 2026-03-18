extern bool _mi_process_is_initialized
/*** DEPENDENCIES:
***/


static _Atomic size_t thread_count = 1
/*** DEPENDENCIES:
***/


static _Atomic size_t thread_total_count
/*** DEPENDENCIES:
***/


static bool os_preloading = 1
/*** DEPENDENCIES:
***/


bool _mi_cpu_has_fsrm = 0
/*** DEPENDENCIES:
***/


bool _mi_cpu_has_erms = 0
/*** DEPENDENCIES:
***/


bool _mi_cpu_has_popcnt = 0
/*** DEPENDENCIES:
***/


static long mi_max_error_count = 16
/*** DEPENDENCIES:
***/


static long mi_max_warning_count = 16
/*** DEPENDENCIES:
***/


static char mi_output_buffer[((size_t) (16 * 1024)) + 1]
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


static _Atomic uintptr_t mi_huge_start
/*** DEPENDENCIES:
***/


static _Atomic size_t mi_numa_node_count
/*** DEPENDENCIES:
***/


static void * _Atomic deferred_arg
/*** DEPENDENCIES:
***/


static size_t mi_page_map_count
/*** DEPENDENCIES:
***/


static void *mi_page_map_max_address
/*** DEPENDENCIES:
***/


extern char **environ
/*** DEPENDENCIES:
***/


pthread_key_t _mi_heap_default_key = (pthread_key_t) (-1)
/*** DEPENDENCIES:
***/


static int ok = 0
/*** DEPENDENCIES:
***/


static int failed = 0
/*** DEPENDENCIES:
***/


static int THREADS = 32
/*** DEPENDENCIES:
***/


static int SCALE = 50
/*** DEPENDENCIES:
***/


static int ITER = 50
/*** DEPENDENCIES:
***/


static bool allow_large_objects = 0
/*** DEPENDENCIES:
***/


static size_t use_one_size = 0
/*** DEPENDENCIES:
***/


static bool main_participates = 0
/*** DEPENDENCIES:
***/


static volatile void *transfer[1000]
/*** DEPENDENCIES:
***/


const uintptr_t cookie = 0x1ce4e5b9UL
/*** DEPENDENCIES:
***/


static void (*thread_entry_fun)(intptr_t) = &stress
/*** DEPENDENCIES:
***/


extern const mi_page_t _mi_page_empty
/*** DEPENDENCIES:
None
----------------------------
***/


extern const mi_heap_t _mi_heap_empty
/*** DEPENDENCIES:
None
----------------------------
***/


extern _Atomic mi_submap_t *_mi_page_map
/*** DEPENDENCIES:
typedef mi_page_t **mi_submap_t
----------------------------
***/


extern mi_heap_t *_mi_heap_default
/*** DEPENDENCIES:
None
----------------------------
***/


static mi_meta_page_t * _Atomic mi_meta_pages = 0
/*** DEPENDENCIES:
typedef struct mi_meta_page_s
{
  struct mi_meta_page_s * _Atomic next;
  mi_memid_t memid;
  mi_bbitmap_t blocks_free;
} mi_meta_page_t
----------------------------
***/


static mi_subproc_t subproc_main = {0}
/*** DEPENDENCIES:
None
----------------------------
***/


extern mi_heap_t heap_main
/*** DEPENDENCIES:
None
----------------------------
***/


mi_stats_t _mi_stats_main = {2, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0}, {0}, {0}, {0}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0}, {0}, {0}, {0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}}
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
  mi_stat_count_t chunk_bins[MI_CBIN_COUNT];
} mi_stats_t
----------------------------
***/


static mi_option_desc_t mi_options[_mi_option_last] = {{1, MI_OPTION_UNINIT, mi_option_show_errors, "show_errors", 0}, {0, MI_OPTION_UNINIT, mi_option_show_stats, "show_stats", 0}, {0, MI_OPTION_UNINIT, mi_option_verbose, "verbose", 0}, {1, MI_OPTION_UNINIT, mi_option_eager_commit, "eager_commit", 0}, {2, MI_OPTION_UNINIT, mi_option_arena_eager_commit, "arena_eager_commit", "eager_region_commit"}, {1, MI_OPTION_UNINIT, mi_option_purge_decommits, "purge_decommits", "reset_decommits"}, {2, MI_OPTION_UNINIT, mi_option_allow_large_os_pages, "allow_large_os_pages", "large_os_pages"}, {0, MI_OPTION_UNINIT, mi_option_reserve_huge_os_pages, "reserve_huge_os_pages", 0}, {-1, MI_OPTION_UNINIT, mi_option_reserve_huge_os_pages_at, "reserve_huge_os_pages_at", 0}, {0, MI_OPTION_UNINIT, mi_option_reserve_os_memory, "reserve_os_memory", 0}, {0, MI_OPTION_UNINIT, mi_option_deprecated_segment_cache, "deprecated_segment_cache", 0}, {0, MI_OPTION_UNINIT, mi_option_deprecated_page_reset, "deprecated_page_reset", 0}, {0, MI_OPTION_UNINIT, mi_option_abandoned_page_purge, "abandoned_page_purge", 0}, {0, MI_OPTION_UNINIT, mi_option_deprecated_segment_reset, "deprecated_segment_reset", 0}, {1, MI_OPTION_UNINIT, mi_option_eager_commit_delay, "eager_commit_delay", 0}, {1000, MI_OPTION_UNINIT, mi_option_purge_delay, "purge_delay", "reset_delay"}, {0, MI_OPTION_UNINIT, mi_option_use_numa_nodes, "use_numa_nodes", 0}, {0, MI_OPTION_UNINIT, mi_option_disallow_os_alloc, "disallow_os_alloc", "limit_os_alloc"}, {100, MI_OPTION_UNINIT, mi_option_os_tag, "os_tag", 0}, {32, MI_OPTION_UNINIT, mi_option_max_errors, "max_errors", 0}, {32, MI_OPTION_UNINIT, mi_option_max_warnings, "max_warnings", 0}, {10, MI_OPTION_UNINIT, mi_option_deprecated_max_segment_reclaim, "deprecated_max_segment_reclaim", 0}, {0, MI_OPTION_UNINIT, mi_option_destroy_on_exit, "destroy_on_exit", 0}, {1024L * 1024L, MI_OPTION_UNINIT, mi_option_arena_reserve, "arena_reserve", 0}, {1, MI_OPTION_UNINIT, mi_option_arena_purge_mult, "arena_purge_mult", 0}, {1, MI_OPTION_UNINIT, mi_option_deprecated_purge_extend_delay, "deprecated_purge_extend_delay", "decommit_extend_delay"}, {0, MI_OPTION_UNINIT, mi_option_disallow_arena_alloc, "disallow_arena_alloc", 0}, {400, MI_OPTION_UNINIT, mi_option_retry_on_oom, "retry_on_oom", 0}, {0, MI_OPTION_UNINIT, mi_option_visit_abandoned, "visit_abandoned", 0}, {0, MI_OPTION_UNINIT, mi_option_guarded_min, "guarded_min", 0}, {(1024UL * 1024UL) * 1024UL, MI_OPTION_UNINIT, mi_option_guarded_max, "guarded_max", 0}, {0, MI_OPTION_UNINIT, mi_option_guarded_precise, "guarded_precise", 0}, {0, MI_OPTION_UNINIT, mi_option_guarded_sample_rate, "guarded_sample_rate", 0}, {0, MI_OPTION_UNINIT, mi_option_guarded_sample_seed, "guarded_sample_seed", 0}, {10000, MI_OPTION_UNINIT, mi_option_generic_collect, "generic_collect", 0}, {0, MI_OPTION_UNINIT, mi_option_page_reclaim_on_free, "page_reclaim_on_free", "abandoned_reclaim_on_free"}, {2, MI_OPTION_UNINIT, mi_option_page_full_retain, "page_full_retain", 0}, {4, MI_OPTION_UNINIT, mi_option_page_max_candidates, "page_max_candidates", 0}, {0, MI_OPTION_UNINIT, mi_option_max_vabits, "max_vabits", 0}, {0, MI_OPTION_UNINIT, mi_option_pagemap_commit, "pagemap_commit", 0}, {0, MI_OPTION_UNINIT, mi_option_page_commit_on_demand, "page_commit_on_demand", 0}, {-1, MI_OPTION_UNINIT, mi_option_page_max_reclaim, "page_max_reclaim", 0}, {32, MI_OPTION_UNINIT, mi_option_page_cross_thread_max_reclaim, "page_cross_thread_max_reclaim", 0}}
/*** DEPENDENCIES:
typedef struct mi_option_desc_s
{
  long value;
  mi_option_init_t init;
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


static mi_memid_t mi_page_map_memid
/*** DEPENDENCIES:
None
----------------------------
***/


static _Atomic mi_bfield_t mi_page_map_commit
/*** DEPENDENCIES:
typedef size_t mi_bfield_t
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


static mi_tld_t tld_main = {0, 0, 0, &subproc_main, &heap_main, &heap_main, 0, 0, 0, {2, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0}, {0}, {0}, {0}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0}, {0}, {0}, {0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}}, {{{0, 0}}, MI_MEM_STATIC, 1, 1, 0}}
/*** DEPENDENCIES:
extern mi_heap_t heap_main
----------------------------
static mi_subproc_t subproc_main = {0}
----------------------------
None
----------------------------
***/


static mi_tld_t tld_empty = {0, 0, 0, &subproc_main, 0, 0, 0, 0, 0, {2, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0}, {0}, {0}, {0}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0}, {0}, {0}, {0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}}, {{{0, 0}}, MI_MEM_STATIC, 1, 1, 0}}
/*** DEPENDENCIES:
static mi_subproc_t subproc_main = {0}
----------------------------
None
----------------------------
***/


mi_tld_t *thread_tld = &tld_empty
/*** DEPENDENCIES:
static mi_tld_t tld_empty = {0, 0, 0, &subproc_main, 0, 0, 0, 0, 0, {2, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0}, {0}, {0}, {0}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0}, {0}, {0}, {0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}, {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}, {0, 0, 0}}}, {{{0, 0}}, MI_MEM_STATIC, 1, 1, 0}}
----------------------------
None
----------------------------
***/


