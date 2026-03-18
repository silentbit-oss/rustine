// element in merge of:  mi_arena_t,mi_heap_s,mi_heap_t,mi_memid_arena_info_t,mi_memid_t,mi_page_queue_t,mi_page_t,mi_subproc_t,mi_tld_s,mi_tld_t
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
} mi_subproc_t
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
None
----------------------------
***/


// element in merge of:  mi_arena_t,mi_heap_s,mi_heap_t,mi_memid_arena_info_t,mi_memid_t,mi_page_queue_t,mi_page_t,mi_subproc_t,mi_tld_s,mi_tld_t
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
} mi_memid_t
/*** DEPENDENCIES:
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
} mi_memkind_t
----------------------------
typedef struct mi_memid_meta_info
{
  void *meta_page;
  uint32_t block_index;
  uint32_t block_count;
} mi_memid_meta_info_t
----------------------------
typedef struct mi_memid_os_info
{
  void *base;
  size_t size;
} mi_memid_os_info_t
----------------------------
None
----------------------------
***/


// element in merge of:  mi_arena_t,mi_heap_s,mi_heap_t,mi_memid_arena_info_t,mi_memid_t,mi_page_queue_t,mi_page_t,mi_subproc_t,mi_tld_s,mi_tld_t
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
} mi_page_t
/*** DEPENDENCIES:
typedef size_t mi_threadid_t
----------------------------
typedef uint8_t mi_heaptag_t
----------------------------
typedef uintptr_t mi_thread_free_t
----------------------------
typedef struct mi_block_s
{
  mi_encoded_t next;
} mi_block_t
----------------------------
None
----------------------------
***/


// element in merge of:  mi_arena_t,mi_heap_s,mi_heap_t,mi_memid_arena_info_t,mi_memid_t,mi_page_queue_t,mi_page_t,mi_subproc_t,mi_tld_s,mi_tld_t
typedef struct mi_tld_s mi_tld_t
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  mi_arena_t,mi_heap_s,mi_heap_t,mi_memid_arena_info_t,mi_memid_t,mi_page_queue_t,mi_page_t,mi_subproc_t,mi_tld_s,mi_tld_t
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
}
/*** DEPENDENCIES:
typedef struct mi_padding_s
{
  uint32_t canary;
  uint32_t delta;
} mi_padding_t
----------------------------
typedef struct mi_random_cxt_s
{
  uint32_t input[16];
  uint32_t output[16];
  int output_available;
  bool weak;
} mi_random_ctx_t
----------------------------
None
----------------------------
***/


// element in merge of:  mi_arena_t,mi_heap_s,mi_heap_t,mi_memid_arena_info_t,mi_memid_t,mi_page_queue_t,mi_page_t,mi_subproc_t,mi_tld_s,mi_tld_t
typedef struct mi_heap_s mi_heap_t
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  mi_arena_t,mi_heap_s,mi_heap_t,mi_memid_arena_info_t,mi_memid_t,mi_page_queue_t,mi_page_t,mi_subproc_t,mi_tld_s,mi_tld_t
typedef struct mi_memid_arena_info
{
  mi_arena_t *arena;
  uint32_t slice_index;
  uint32_t slice_count;
} mi_memid_arena_info_t
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  mi_arena_t,mi_heap_s,mi_heap_t,mi_memid_arena_info_t,mi_memid_t,mi_page_queue_t,mi_page_t,mi_subproc_t,mi_tld_s,mi_tld_t
typedef struct mi_page_queue_s
{
  mi_page_t *first;
  mi_page_t *last;
  size_t count;
  size_t block_size;
} mi_page_queue_t
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  mi_arena_t,mi_heap_s,mi_heap_t,mi_memid_arena_info_t,mi_memid_t,mi_page_queue_t,mi_page_t,mi_subproc_t,mi_tld_s,mi_tld_t
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
} mi_arena_t
/*** DEPENDENCIES:
typedef bool mi_commit_fun_t(bool commit, void *start, size_t size, bool *is_zero, void *user_arg)
----------------------------
typedef struct mi_bbitmap_s
{
  _Atomic size_t chunk_count;
  _Atomic size_t chunk_max_accessed;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 2];
  mi_bchunkmap_t chunkmap;
  mi_bchunkmap_t chunkmap_bins[MI_CBIN_COUNT - 1];
  mi_bchunk_t chunks[64];
} mi_bbitmap_t
----------------------------
typedef struct mi_bitmap_s
{
  _Atomic size_t chunk_count;
  size_t _padding[(((1 << (6 + 3)) / 8) / (1 << 3)) - 1];
  mi_bchunkmap_t chunkmap;
  mi_bchunk_t chunks[64];
} mi_bitmap_t
----------------------------
typedef int64_t mi_msecs_t
----------------------------
None
----------------------------
***/


// element in merge of:  mi_arena_t,mi_heap_s,mi_heap_t,mi_memid_arena_info_t,mi_memid_t,mi_page_queue_t,mi_page_t,mi_subproc_t,mi_tld_s,mi_tld_t
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
}
/*** DEPENDENCIES:
typedef size_t mi_threadid_t
----------------------------
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
None
----------------------------
***/


