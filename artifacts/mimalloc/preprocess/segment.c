# 0 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c"






# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc.h" 1






       
# 98 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc.h"
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1



typedef int START_DELIMETER;
typedef unsigned chtype;
typedef chtype attr_t;
typedef int socklen_t;
typedef int size_t;
typedef struct __dirstream DIR;
typedef unsigned char cc_t;
typedef int __builtin_va_list;
typedef int __gnuc_va_list;
typedef int va_list;
typedef int __int8_t;
typedef int __uint8_t;
typedef int __int16_t;
typedef int __uint16_t;
typedef int __int_least16_t;
typedef int __uint_least16_t;
typedef int __int32_t;
typedef int __uint32_t;
typedef int __int64_t;
typedef int __uint64_t;
typedef int __int_least32_t;
typedef int __uint_least32_t;
typedef int __s8;
typedef int __u8;
typedef int __s16;
typedef int __u16;
typedef int __s32;
typedef int __u32;
typedef int __s64;
typedef int __u64;
typedef int _LOCK_T;
typedef int _LOCK_RECURSIVE_T;
typedef int _off_t;
typedef int __dev_t;
typedef int __uid_t;
typedef int __gid_t;
typedef int _off64_t;
typedef int _fpos_t;
typedef int _ssize_t;
typedef int wint_t;
typedef int _mbstate_t;
typedef int _flock_t;
typedef int _iconv_t;
typedef int __ULong;
typedef int __FILE;
typedef int ptrdiff_t;
typedef int wchar_t;
typedef int char16_t;
typedef int char32_t;
typedef int __off_t;
typedef int __pid_t;
typedef int __loff_t;
typedef int u_char;
typedef int u_short;
typedef int u_int;
typedef int u_long;
typedef int ushort;
typedef int uint;
typedef int clock_t;
typedef int time_t;
typedef int daddr_t;
typedef int caddr_t;
typedef int ino_t;
typedef int off_t;
typedef int dev_t;
typedef int uid_t;
typedef int gid_t;
typedef int pid_t;
typedef int key_t;
typedef int ssize_t;
typedef int mode_t;
typedef int nlink_t;
typedef int fd_mask;
typedef int _types_fd_set;
typedef int clockid_t;
typedef int timer_t;
typedef int useconds_t;
typedef int suseconds_t;
typedef int FILE;
typedef int fpos_t;
typedef int cookie_read_function_t;
typedef int cookie_write_function_t;
typedef int cookie_seek_function_t;
typedef int cookie_close_function_t;
typedef int cookie_io_functions_t;
typedef int div_t;
typedef int ldiv_t;
typedef int lldiv_t;
typedef int sigset_t;
typedef int __sigset_t;
typedef int _sig_func_ptr;
typedef int sig_atomic_t;
typedef int __tzrule_type;
typedef int __tzinfo_type;
typedef int mbstate_t;
typedef int sem_t;
typedef int pthread_t;
typedef int pthread_attr_t;
typedef int pthread_mutex_t;
typedef int pthread_mutexattr_t;
typedef int pthread_cond_t;
typedef int pthread_condattr_t;
typedef int pthread_key_t;
typedef int pthread_once_t;
typedef int pthread_rwlock_t;
typedef int pthread_rwlockattr_t;
typedef int pthread_spinlock_t;
typedef int pthread_barrier_t;
typedef int pthread_barrierattr_t;
typedef int jmp_buf;
typedef int rlim_t;
typedef int sa_family_t;
typedef int sigjmp_buf;
typedef int stack_t;
typedef int siginfo_t;
typedef int z_stream;


typedef int int8_t;
typedef int uint8_t;
typedef int int16_t;
typedef int uint16_t;
typedef int int32_t;
typedef int uint32_t;
typedef int int64_t;
typedef int uint64_t;


typedef int int_least8_t;
typedef int uint_least8_t;
typedef int int_least16_t;
typedef int uint_least16_t;
typedef int int_least32_t;
typedef int uint_least32_t;
typedef int int_least64_t;
typedef int uint_least64_t;


typedef int int_fast8_t;
typedef int uint_fast8_t;
typedef int int_fast16_t;
typedef int uint_fast16_t;
typedef int int_fast32_t;
typedef int uint_fast32_t;
typedef int int_fast64_t;
typedef int uint_fast64_t;


typedef int intptr_t;
typedef int uintptr_t;


typedef int intmax_t;
typedef int uintmax_t;


typedef _Bool bool;


typedef void* MirEGLNativeWindowType;
typedef void* MirEGLNativeDisplayType;
typedef struct MirConnection MirConnection;
typedef struct MirSurface MirSurface;
typedef struct MirSurfaceSpec MirSurfaceSpec;
typedef struct MirScreencast MirScreencast;
typedef struct MirPromptSession MirPromptSession;
typedef struct MirBufferStream MirBufferStream;
typedef struct MirPersistentId MirPersistentId;
typedef struct MirBlob MirBlob;
typedef struct MirDisplayConfig MirDisplayConfig;


typedef struct xcb_connection_t xcb_connection_t;
typedef uint32_t xcb_window_t;
typedef uint32_t xcb_visualid_t;


typedef _Atomic(_Bool) atomic_bool;
typedef _Atomic(char) atomic_char;
typedef _Atomic(signed char) atomic_schar;
typedef _Atomic(unsigned char) atomic_uchar;
typedef _Atomic(short) atomic_short;
typedef _Atomic(unsigned short) atomic_ushort;
typedef _Atomic(int) atomic_int;
typedef _Atomic(unsigned int) atomic_uint;
typedef _Atomic(long) atomic_long;
typedef _Atomic(unsigned long) atomic_ulong;
typedef _Atomic(long long) atomic_llong;
typedef _Atomic(unsigned long long) atomic_ullong;
typedef _Atomic(uint_least16_t) atomic_char16_t;
typedef _Atomic(uint_least32_t) atomic_char32_t;
typedef _Atomic(wchar_t) atomic_wchar_t;
typedef _Atomic(int_least8_t) atomic_int_least8_t;
typedef _Atomic(uint_least8_t) atomic_uint_least8_t;
typedef _Atomic(int_least16_t) atomic_int_least16_t;
typedef _Atomic(uint_least16_t) atomic_uint_least16_t;
typedef _Atomic(int_least32_t) atomic_int_least32_t;
typedef _Atomic(uint_least32_t) atomic_uint_least32_t;
typedef _Atomic(int_least64_t) atomic_int_least64_t;
typedef _Atomic(uint_least64_t) atomic_uint_least64_t;
typedef _Atomic(int_fast8_t) atomic_int_fast8_t;
typedef _Atomic(uint_fast8_t) atomic_uint_fast8_t;
typedef _Atomic(int_fast16_t) atomic_int_fast16_t;
typedef _Atomic(uint_fast16_t) atomic_uint_fast16_t;
typedef _Atomic(int_fast32_t) atomic_int_fast32_t;
typedef _Atomic(uint_fast32_t) atomic_uint_fast32_t;
typedef _Atomic(int_fast64_t) atomic_int_fast64_t;
typedef _Atomic(uint_fast64_t) atomic_uint_fast64_t;
typedef _Atomic(intptr_t) atomic_intptr_t;
typedef _Atomic(uintptr_t) atomic_uintptr_t;
typedef _Atomic(size_t) atomic_size_t;
typedef _Atomic(ptrdiff_t) atomic_ptrdiff_t;
typedef _Atomic(intmax_t) atomic_intmax_t;
typedef _Atomic(uintmax_t) atomic_uintmax_t;
typedef struct atomic_flag { atomic_bool _Value; } atomic_flag;
typedef enum memory_order {
  memory_order_relaxed,
  memory_order_consume,
  memory_order_acquire,
  memory_order_release,
  memory_order_acq_rel,
  memory_order_seq_cst
} memory_order;

typedef struct __locale_struct *__locale_t;
typedef __locale_t locale_t;
typedef int END_DELIMETER;
# 3 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 2
# 99 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc.h" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdbool.h" 1
# 100 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc.h" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 101 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc.h" 2
# 110 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc.h"
 void* mi_malloc(size_t size) ;
 void* mi_calloc(size_t count, size_t size) ;
 void* mi_realloc(void* p, size_t newsize) ;
 void* mi_expand(void* p, size_t newsize) ;

 void mi_free(void* p) ;
 char* mi_strdup(const char* s) ;
 char* mi_strndup(const char* s, size_t n) ;
 char* mi_realpath(const char* fname, char* resolved_name) ;







 void* mi_malloc_small(size_t size) ;
 void* mi_zalloc_small(size_t size) ;
 void* mi_zalloc(size_t size) ;

 void* mi_mallocn(size_t count, size_t size) ;
 void* mi_reallocn(void* p, size_t count, size_t size) ;
 void* mi_reallocf(void* p, size_t newsize) ;

 size_t mi_usable_size(const void* p) ;
 size_t mi_good_size(size_t size) ;






typedef void ( mi_deferred_free_fun)(bool force, unsigned long long heartbeat, void* arg);
 void mi_register_deferred_free(mi_deferred_free_fun* deferred_free, void* arg) ;

typedef void ( mi_output_fun)(const char* msg, void* arg);
 void mi_register_output(mi_output_fun* out, void* arg) ;

typedef void ( mi_error_fun)(int err, void* arg);
 void mi_register_error(mi_error_fun* fun, void* arg);

 void mi_collect(bool force) ;
 int mi_version(void) ;
 void mi_stats_reset(void) ;
 void mi_stats_merge(void) ;
 void mi_stats_print(void* out) ;
 void mi_stats_print_out(mi_output_fun* out, void* arg) ;
 void mi_thread_stats_print_out(mi_output_fun* out, void* arg) ;
 void mi_options_print(void) ;

 void mi_process_info(size_t* elapsed_msecs, size_t* user_msecs, size_t* system_msecs,
                                    size_t* current_rss, size_t* peak_rss,
                                    size_t* current_commit, size_t* peak_commit, size_t* page_faults) ;



 void mi_process_init(void) ;
 void mi_process_done(void) ;
 void mi_thread_init(void) ;
 void mi_thread_done(void) ;
# 178 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc.h"
 void* mi_malloc_aligned(size_t size, size_t alignment) ;
 void* mi_malloc_aligned_at(size_t size, size_t alignment, size_t offset) ;
 void* mi_zalloc_aligned(size_t size, size_t alignment) ;
 void* mi_zalloc_aligned_at(size_t size, size_t alignment, size_t offset) ;
 void* mi_calloc_aligned(size_t count, size_t size, size_t alignment) ;
 void* mi_calloc_aligned_at(size_t count, size_t size, size_t alignment, size_t offset) ;
 void* mi_realloc_aligned(void* p, size_t newsize, size_t alignment) ;
 void* mi_realloc_aligned_at(void* p, size_t newsize, size_t alignment, size_t offset) ;






struct mi_heap_s;
typedef struct mi_heap_s mi_heap_t;

 mi_heap_t* mi_heap_new(void);
 void mi_heap_delete(mi_heap_t* heap);
 void mi_heap_destroy(mi_heap_t* heap);
 mi_heap_t* mi_heap_set_default(mi_heap_t* heap);
 mi_heap_t* mi_heap_get_default(void);
 mi_heap_t* mi_heap_get_backing(void);
 void mi_heap_collect(mi_heap_t* heap, bool force) ;

 void* mi_heap_malloc(mi_heap_t* heap, size_t size) ;
 void* mi_heap_zalloc(mi_heap_t* heap, size_t size) ;
 void* mi_heap_calloc(mi_heap_t* heap, size_t count, size_t size) ;
 void* mi_heap_mallocn(mi_heap_t* heap, size_t count, size_t size) ;
 void* mi_heap_malloc_small(mi_heap_t* heap, size_t size) ;

 void* mi_heap_realloc(mi_heap_t* heap, void* p, size_t newsize) ;
 void* mi_heap_reallocn(mi_heap_t* heap, void* p, size_t count, size_t size) ;
 void* mi_heap_reallocf(mi_heap_t* heap, void* p, size_t newsize) ;

 char* mi_heap_strdup(mi_heap_t* heap, const char* s) ;
 char* mi_heap_strndup(mi_heap_t* heap, const char* s, size_t n) ;
 char* mi_heap_realpath(mi_heap_t* heap, const char* fname, char* resolved_name) ;

 void* mi_heap_malloc_aligned(mi_heap_t* heap, size_t size, size_t alignment) ;
 void* mi_heap_malloc_aligned_at(mi_heap_t* heap, size_t size, size_t alignment, size_t offset) ;
 void* mi_heap_zalloc_aligned(mi_heap_t* heap, size_t size, size_t alignment) ;
 void* mi_heap_zalloc_aligned_at(mi_heap_t* heap, size_t size, size_t alignment, size_t offset) ;
 void* mi_heap_calloc_aligned(mi_heap_t* heap, size_t count, size_t size, size_t alignment) ;
 void* mi_heap_calloc_aligned_at(mi_heap_t* heap, size_t count, size_t size, size_t alignment, size_t offset) ;
 void* mi_heap_realloc_aligned(mi_heap_t* heap, void* p, size_t newsize, size_t alignment) ;
 void* mi_heap_realloc_aligned_at(mi_heap_t* heap, void* p, size_t newsize, size_t alignment, size_t offset) ;
# 234 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc.h"
 void* mi_rezalloc(void* p, size_t newsize) ;
 void* mi_recalloc(void* p, size_t newcount, size_t size) ;

 void* mi_rezalloc_aligned(void* p, size_t newsize, size_t alignment) ;
 void* mi_rezalloc_aligned_at(void* p, size_t newsize, size_t alignment, size_t offset) ;
 void* mi_recalloc_aligned(void* p, size_t newcount, size_t size, size_t alignment) ;
 void* mi_recalloc_aligned_at(void* p, size_t newcount, size_t size, size_t alignment, size_t offset) ;

 void* mi_heap_rezalloc(mi_heap_t* heap, void* p, size_t newsize) ;
 void* mi_heap_recalloc(mi_heap_t* heap, void* p, size_t newcount, size_t size) ;

 void* mi_heap_rezalloc_aligned(mi_heap_t* heap, void* p, size_t newsize, size_t alignment) ;
 void* mi_heap_rezalloc_aligned_at(mi_heap_t* heap, void* p, size_t newsize, size_t alignment, size_t offset) ;
 void* mi_heap_recalloc_aligned(mi_heap_t* heap, void* p, size_t newcount, size_t size, size_t alignment) ;
 void* mi_heap_recalloc_aligned_at(mi_heap_t* heap, void* p, size_t newcount, size_t size, size_t alignment, size_t offset) ;






 bool mi_heap_contains_block(mi_heap_t* heap, const void* p);
 bool mi_heap_check_owned(mi_heap_t* heap, const void* p);
 bool mi_check_owned(const void* p);


typedef struct mi_heap_area_s {
  void* blocks;
  size_t reserved;
  size_t committed;
  size_t used;
  size_t block_size;
  size_t full_block_size;
  int heap_tag;
} mi_heap_area_t;

typedef bool ( mi_block_visit_fun)(const mi_heap_t* heap, const mi_heap_area_t* area, void* block, size_t block_size, void* arg);

 bool mi_heap_visit_blocks(const mi_heap_t* heap, bool visit_blocks, mi_block_visit_fun* visitor, void* arg);


 bool mi_is_in_heap_region(const void* p) ;
 bool mi_is_redirected(void) ;

 int mi_reserve_huge_os_pages_interleave(size_t pages, size_t numa_nodes, size_t timeout_msecs) ;
 int mi_reserve_huge_os_pages_at(size_t pages, int numa_node, size_t timeout_msecs) ;

 int mi_reserve_os_memory(size_t size, bool commit, bool allow_large) ;
 bool mi_manage_os_memory(void* start, size_t size, bool is_committed, bool is_large, bool is_zero, int numa_node) ;

 void mi_debug_show_arenas(void) ;
 void mi_arenas_print(void) ;


typedef int mi_arena_id_t;
 void* mi_arena_area(mi_arena_id_t arena_id, size_t* size);
 int mi_reserve_huge_os_pages_at_ex(size_t pages, int numa_node, size_t timeout_msecs, bool exclusive, mi_arena_id_t* arena_id) ;
 int mi_reserve_os_memory_ex(size_t size, bool commit, bool allow_large, bool exclusive, mi_arena_id_t* arena_id) ;
 bool mi_manage_os_memory_ex(void* start, size_t size, bool is_committed, bool is_large, bool is_zero, int numa_node, bool exclusive, mi_arena_id_t* arena_id) ;



 mi_heap_t* mi_heap_new_in_arena(mi_arena_id_t arena_id);





typedef void* mi_subproc_id_t;
 mi_subproc_id_t mi_subproc_main(void);
 mi_subproc_id_t mi_subproc_new(void);
 void mi_subproc_delete(mi_subproc_id_t subproc);
 void mi_subproc_add_current_thread(mi_subproc_id_t subproc);


 bool mi_abandoned_visit_blocks(mi_subproc_id_t subproc_id, int heap_tag, bool visit_blocks, mi_block_visit_fun* visitor, void* arg);




 void mi_heap_guarded_set_sample_rate(mi_heap_t* heap, size_t sample_rate, size_t seed);
 void mi_heap_guarded_set_size_bound(mi_heap_t* heap, size_t min, size_t max);


 void mi_thread_set_in_threadpool(void) ;




 mi_heap_t* mi_heap_new_ex(int heap_tag, bool allow_destroy, mi_arena_id_t arena_id);


 int mi_reserve_huge_os_pages(size_t pages, double max_secs, size_t* pages_reserved) ;
 void mi_collect_reduce(size_t target_thread_owned) ;
# 354 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc.h"
typedef enum mi_option_e {

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
# 424 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc.h"
 void mi_cfree(void* p) ;
 void* mi__expand(void* p, size_t newsize) ;
 size_t mi_malloc_size(const void* p) ;
 size_t mi_malloc_good_size(size_t size) ;
 size_t mi_malloc_usable_size(const void *p) ;

 int mi_posix_memalign(void** p, size_t alignment, size_t size) ;
 void* mi_memalign(size_t alignment, size_t size) ;
 void* mi_valloc(size_t size) ;
 void* mi_pvalloc(size_t size) ;
 void* mi_aligned_alloc(size_t alignment, size_t size) ;

 void* mi_reallocarray(void* p, size_t count, size_t size) ;
 int mi_reallocarr(void* p, size_t count, size_t size) ;
 void* mi_aligned_recalloc(void* p, size_t newcount, size_t size, size_t alignment) ;
 void* mi_aligned_offset_recalloc(void* p, size_t newcount, size_t size, size_t alignment, size_t offset) ;

 unsigned short* mi_wcsdup(const unsigned short* s) ;
 unsigned char* mi_mbsdup(const unsigned char* s) ;
 int mi_dupenv_s(char** buf, size_t* size, const char* name) ;
 int mi_wdupenv_s(unsigned short** buf, size_t* size, const unsigned short* name) ;

 void mi_free_size(void* p, size_t size) ;
 void mi_free_size_aligned(void* p, size_t size, size_t alignment) ;
 void mi_free_aligned(void* p, size_t alignment) ;



 void* mi_new(size_t size) ;
 void* mi_new_aligned(size_t size, size_t alignment) ;
 void* mi_new_nothrow(size_t size) ;
 void* mi_new_aligned_nothrow(size_t size, size_t alignment) ;
 void* mi_new_n(size_t count, size_t size) ;
 void* mi_new_realloc(void* p, size_t newsize) ;
 void* mi_new_reallocn(void* p, size_t newcount, size_t size) ;

 void* mi_heap_alloc_new(mi_heap_t* heap, size_t size) ;
 void* mi_heap_alloc_new_n(mi_heap_t* heap, size_t count, size_t size) ;
# 8 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c" 2
# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h" 1






       
# 16 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h" 1






       
# 25 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc-stats.h" 1






       




# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 13 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc-stats.h" 2




typedef struct mi_stat_count_s {
  int64_t total;
  int64_t peak;
  int64_t current;
} mi_stat_count_t;


typedef struct mi_stat_counter_s {
  int64_t total;
} mi_stat_counter_t;
# 73 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc-stats.h"
typedef struct mi_stats_s
{
  int version;

  mi_stat_count_t pages; mi_stat_count_t reserved; mi_stat_count_t committed; mi_stat_count_t reset; mi_stat_count_t purged; mi_stat_count_t page_committed; mi_stat_count_t pages_abandoned; mi_stat_count_t threads; mi_stat_count_t malloc_normal; mi_stat_count_t malloc_huge; mi_stat_count_t malloc_requested; mi_stat_counter_t mmap_calls; mi_stat_counter_t commit_calls; mi_stat_counter_t reset_calls; mi_stat_counter_t purge_calls; mi_stat_counter_t arena_count; mi_stat_counter_t malloc_normal_count; mi_stat_counter_t malloc_huge_count; mi_stat_counter_t malloc_guarded_count; mi_stat_counter_t arena_rollback_count; mi_stat_counter_t arena_purges; mi_stat_counter_t pages_extended; mi_stat_counter_t pages_retire; mi_stat_counter_t page_searches; mi_stat_count_t segments; mi_stat_count_t segments_abandoned; mi_stat_count_t segments_cache; mi_stat_count_t _segments_reserved; mi_stat_counter_t pages_reclaim_on_alloc; mi_stat_counter_t pages_reclaim_on_free; mi_stat_counter_t pages_reabandon_full; mi_stat_counter_t pages_unabandon_busy_wait;


  mi_stat_count_t _stat_reserved[4];
  mi_stat_counter_t _stat_counter_reserved[4];


  mi_stat_count_t malloc_bins[(73U)+1];
  mi_stat_count_t page_bins[(73U)+1];
} mi_stats_t;
# 96 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc-stats.h"
 void mi_stats_get( size_t stats_size, mi_stats_t* stats ) ;
 char* mi_stats_get_json( size_t buf_size, char* buf ) ;
# 26 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 27 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 28 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h" 2
# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/atomic.h" 1






       
# 19 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/atomic.h"
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/pthread.h" 1
# 20 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/atomic.h" 2
# 52 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/atomic.h"
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdatomic.h" 1
# 53 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/atomic.h" 2
# 95 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/atomic.h"
static inline void mi_atomic_yield(void);
static inline intptr_t mi_atomic_addi(_Atomic(intptr_t)*p, intptr_t add);
static inline intptr_t mi_atomic_subi(_Atomic(intptr_t)*p, intptr_t sub);
# 131 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/atomic.h"
static inline int64_t mi_atomic_addi64_relaxed(volatile int64_t* p, int64_t add) {
  return atomic_fetch_add_explicit((_Atomic(int64_t)*)p, add, memory_order_relaxed);
}
static inline void mi_atomic_void_addi64_relaxed(volatile int64_t* p, const volatile int64_t* padd) {
  const int64_t add = atomic_load_explicit((_Atomic(int64_t)*)padd,memory_order_relaxed);
  if (add != 0) {
    atomic_fetch_add_explicit((_Atomic(int64_t)*)p, add, memory_order_relaxed);
  }
}
static inline void mi_atomic_maxi64_relaxed(volatile int64_t* p, int64_t x) {
  int64_t current = atomic_load_explicit((_Atomic(int64_t)*)p,memory_order_relaxed);
  while (current < x && !atomic_compare_exchange_weak_explicit((_Atomic(int64_t)*)p,&current,x,memory_order_release,memory_order_relaxed)) { };
}
# 323 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/atomic.h"
static inline intptr_t mi_atomic_addi(_Atomic(intptr_t)*p, intptr_t add) {
  return (intptr_t)atomic_fetch_add_explicit((_Atomic(uintptr_t)*)p,(uintptr_t)add,memory_order_acq_rel);
}


static inline intptr_t mi_atomic_subi(_Atomic(intptr_t)*p, intptr_t sub) {
  return (intptr_t)mi_atomic_addi(p, -sub);
}






typedef _Atomic(uintptr_t) mi_atomic_once_t;


static inline bool mi_atomic_once( mi_atomic_once_t* once ) {
  if (atomic_load_explicit(once,memory_order_relaxed) != 0) return 0;
  uintptr_t expected = 0;
  return atomic_compare_exchange_strong_explicit(once,&expected,(uintptr_t)1,memory_order_acq_rel,memory_order_acquire);
}

typedef _Atomic(uintptr_t) mi_atomic_guard_t;
# 384 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/atomic.h"
static inline void mi_atomic_yield(void) {

}
# 483 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/atomic.h"
void _mi_error_message(int err, const char* fmt, ...);



static inline bool mi_lock_try_acquire(pthread_mutex_t* lock) {
  return (pthread_mutex_trylock(lock) == 0);
}
static inline void mi_lock_acquire(pthread_mutex_t* lock) {
  const int err = pthread_mutex_lock(lock);
  if (err != 0) {
    _mi_error_message(err, "internal error: lock cannot be acquired\n");
  }
}
static inline void mi_lock_release(pthread_mutex_t* lock) {
  pthread_mutex_unlock(lock);
}
static inline void mi_lock_init(pthread_mutex_t* lock) {
  pthread_mutex_init(lock, 0);
}
static inline void mi_lock_done(pthread_mutex_t* lock) {
  pthread_mutex_destroy(lock);
}
# 29 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h" 2
# 139 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
typedef int64_t mi_ssize_t;
# 240 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
typedef uintptr_t mi_encoded_t;


typedef size_t mi_threadid_t;


typedef struct mi_block_s {
  mi_encoded_t next;
} mi_block_t;
# 259 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
typedef enum mi_delayed_e {
  MI_USE_DELAYED_FREE = 0,
  MI_DELAYED_FREEING = 1,
  MI_NO_DELAYED_FREE = 2,
  MI_NEVER_DELAYED_FREE = 3
} mi_delayed_t;





typedef union mi_page_flags_s {
  uint8_t full_aligned;
  struct {
    uint8_t in_full : 1;
    uint8_t has_aligned : 1;
  } x;
} mi_page_flags_t;
# 290 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
typedef uintptr_t mi_thread_free_t;
# 320 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
typedef struct mi_page_s {

  uint32_t slice_count;
  uint32_t slice_offset;
  uint8_t is_committed:1;
  uint8_t is_zero_init:1;
  uint8_t is_huge:1;


  uint16_t capacity;
  uint16_t reserved;
  mi_page_flags_t flags;
  uint8_t free_is_zero:1;
  uint8_t retire_expire:7;

  mi_block_t* free;
  mi_block_t* local_free;
  uint16_t used;
  uint8_t block_size_shift;
  uint8_t heap_tag;

  size_t block_size;
  uint8_t* page_start;


  uintptr_t keys[2];


  _Atomic(mi_thread_free_t) xthread_free;
  _Atomic(uintptr_t) xheap;

  struct mi_page_s* next;
  struct mi_page_s* prev;


  void* padding[1];
} mi_page_t;







typedef enum mi_page_kind_e {
  MI_PAGE_SMALL,
  MI_PAGE_MEDIUM,
  MI_PAGE_LARGE,
  MI_PAGE_HUGE

} mi_page_kind_t;

typedef enum mi_segment_kind_e {
  MI_SEGMENT_NORMAL,
  MI_SEGMENT_HUGE,
} mi_segment_kind_t;
# 399 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
typedef struct mi_commit_mask_s {
  size_t mask[(((1UL<<( 9 + (13 + (3)))) / ((1UL<< (13 + (3))))) / ((1<<(3))*8))];
} mi_commit_mask_t;

typedef mi_page_t mi_slice_t;
typedef int64_t mi_msecs_t;







typedef enum mi_memkind_e {
  MI_MEM_NONE,
  MI_MEM_EXTERNAL,
  MI_MEM_STATIC,
  MI_MEM_OS,
  MI_MEM_OS_HUGE,
  MI_MEM_OS_REMAP,
  MI_MEM_ARENA
} mi_memkind_t;

static inline bool mi_memkind_is_os(mi_memkind_t memkind) {
  return (memkind >= MI_MEM_OS && memkind <= MI_MEM_OS_REMAP);
}

typedef struct mi_memid_os_info {
  void* base;
  size_t size;
} mi_memid_os_info_t;

typedef struct mi_memid_arena_info {
  size_t block_index;
  mi_arena_id_t id;
  bool is_exclusive;
} mi_memid_arena_info_t;

typedef struct mi_memid_s {
  union {
    mi_memid_os_info_t os;
    mi_memid_arena_info_t arena;
  } mem;
  bool is_pinned;
  bool initially_committed;
  bool initially_zero;
  mi_memkind_t memkind;
} mi_memid_t;
# 463 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
typedef struct mi_subproc_s mi_subproc_t;

typedef struct mi_segment_s {

  mi_memid_t memid;
  bool allow_decommit;
  bool allow_purge;
  size_t segment_size;
  mi_subproc_t* subproc;


  mi_msecs_t purge_expire;
  mi_commit_mask_t purge_mask;
  mi_commit_mask_t commit_mask;


  struct mi_segment_s* next;
  bool was_reclaimed;
  bool dont_free;

  size_t abandoned;
  size_t abandoned_visits;
  size_t used;
  uintptr_t cookie;

  struct mi_segment_s* abandoned_os_next;
  struct mi_segment_s* abandoned_os_prev;

  size_t segment_slices;
  size_t segment_info_slices;


  mi_segment_kind_t kind;
  size_t slice_entries;
  _Atomic(mi_threadid_t) thread_id;

  mi_slice_t slices[((1UL<<( 9 + (13 + (3)))) / (1UL<< (13 + (3))))+1];
} mi_segment_t;
# 517 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
typedef struct mi_tld_s mi_tld_t;


typedef struct mi_page_queue_s {
  mi_page_t* first;
  mi_page_t* last;
  size_t block_size;
} mi_page_queue_t;




typedef struct mi_random_cxt_s {
  uint32_t input[16];
  uint32_t output[16];
  int output_available;
  bool weak;
} mi_random_ctx_t;




typedef struct mi_padding_s {
  uint32_t canary;
  uint32_t delta;
} mi_padding_t;
# 554 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
struct mi_heap_s {
  mi_tld_t* tld;
  _Atomic(mi_block_t*) thread_delayed_free;
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
  mi_heap_t* next;
  bool no_reclaim;
  uint8_t tag;






  mi_page_t* pages_free_direct[((128) + (((sizeof(mi_padding_t)) + (1<<(3)) - 1) / (1<<(3))) + 1)];
  mi_page_queue_t pages[((73U)+1) + 1];
};
# 587 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
struct mi_subproc_s {
  _Atomic(size_t) abandoned_count;
  _Atomic(size_t) abandoned_os_list_count;
  pthread_mutex_t abandoned_os_lock;
  pthread_mutex_t abandoned_os_visit_lock;
  mi_segment_t* abandoned_os_list;
  mi_segment_t* abandoned_os_list_tail;
  mi_memid_t memid;
};
# 604 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
typedef struct mi_span_queue_s {
  mi_slice_t* first;
  mi_slice_t* last;
  size_t slice_count;
} mi_span_queue_t;




typedef struct mi_segments_tld_s {
  mi_span_queue_t spans[(35)+1];
  size_t count;
  size_t peak_count;
  size_t current_size;
  size_t peak_size;
  size_t reclaim_count;
  mi_subproc_t* subproc;
  mi_stats_t* stats;
} mi_segments_tld_t;


struct mi_tld_s {
  unsigned long long heartbeat;
  bool recurse;
  mi_heap_t* heap_backing;
  mi_heap_t* heaps;
  mi_segments_tld_t segments;
  mi_stats_t stats;
};
# 662 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
void _mi_stat_increase(mi_stat_count_t* stat, size_t amount);
void _mi_stat_decrease(mi_stat_count_t* stat, size_t amount);
void _mi_stat_adjust_decrease(mi_stat_count_t* stat, size_t amount);

void _mi_stat_counter_increase(mi_stat_counter_t* stat, size_t amount);
# 17 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h" 2
# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/track.h" 1






       
# 18 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h" 2
# 103 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdarg.h" 1
# 104 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h" 2
int _mi_vsnprintf(char* buf, size_t bufsize, const char* fmt, va_list args);
int _mi_snprintf(char* buf, size_t buflen, const char* fmt, ...);
char _mi_toupper(char c);
int _mi_strnicmp(const char* s, const char* t, size_t n);
void _mi_strlcpy(char* dest, const char* src, size_t dest_size);
void _mi_strlcat(char* dest, const char* src, size_t dest_size);
size_t _mi_strlen(const char* s);
size_t _mi_strnlen(const char* s, size_t max_len);
bool _mi_getenv(const char* name, char* result, size_t result_size);


void _mi_fputs(mi_output_fun* out, void* arg, const char* prefix, const char* message);
void _mi_fprintf(mi_output_fun* out, void* arg, const char* fmt, ...);
void _mi_message(const char* fmt, ...);
void _mi_warning_message(const char* fmt, ...);
void _mi_verbose_message(const char* fmt, ...);
void _mi_trace_message(const char* fmt, ...);
void _mi_options_init(void);
long _mi_option_get_fast(mi_option_t option);
void _mi_error_message(int err, const char* fmt, ...);


void _mi_random_init(mi_random_ctx_t* ctx);
void _mi_random_init_weak(mi_random_ctx_t* ctx);
void _mi_random_reinit_if_weak(mi_random_ctx_t * ctx);
void _mi_random_split(mi_random_ctx_t* ctx, mi_random_ctx_t* new_ctx);
uintptr_t _mi_random_next(mi_random_ctx_t* ctx);
uintptr_t _mi_heap_random_next(mi_heap_t* heap);
uintptr_t _mi_os_random_weak(uintptr_t extra_seed);
static inline uintptr_t _mi_random_shuffle(uintptr_t x);


extern mi_stats_t _mi_stats_main;
extern const mi_page_t _mi_page_empty;
void _mi_auto_process_init(void);
void _mi_auto_process_done(void) ;
bool _mi_is_redirected(void);
bool _mi_allocator_init(const char** message);
void _mi_allocator_done(void);
bool _mi_is_main_thread(void);
size_t _mi_current_thread_count(void);
bool _mi_preloading(void);
void _mi_thread_done(mi_heap_t* heap);
void _mi_thread_data_collect(void);
void _mi_tld_init(mi_tld_t* tld, mi_heap_t* bheap);
mi_threadid_t _mi_thread_id(void) ;
mi_heap_t* _mi_heap_main_get(void);
mi_subproc_t* _mi_subproc_from_id(mi_subproc_id_t subproc_id);
void _mi_heap_guarded_init(mi_heap_t* heap);


void _mi_os_init(void);
void* _mi_os_alloc(size_t size, mi_memid_t* memid);
void* _mi_os_zalloc(size_t size, mi_memid_t* memid);
void _mi_os_free(void* p, size_t size, mi_memid_t memid);
void _mi_os_free_ex(void* p, size_t size, bool still_committed, mi_memid_t memid);

size_t _mi_os_page_size(void);
size_t _mi_os_good_alloc_size(size_t size);
bool _mi_os_has_overcommit(void);
bool _mi_os_has_virtual_reserve(void);

bool _mi_os_reset(void* addr, size_t size);
bool _mi_os_decommit(void* addr, size_t size);
bool _mi_os_unprotect(void* addr, size_t size);
bool _mi_os_purge(void* p, size_t size);
bool _mi_os_purge_ex(void* p, size_t size, bool allow_reset, size_t stat_size);
void _mi_os_reuse(void* p, size_t size);
 bool _mi_os_commit(void* p, size_t size, bool* is_zero);
 bool _mi_os_commit_ex(void* addr, size_t size, bool* is_zero, size_t stat_size);
bool _mi_os_protect(void* addr, size_t size);

void* _mi_os_alloc_aligned(size_t size, size_t alignment, bool commit, bool allow_large, mi_memid_t* memid);
void* _mi_os_alloc_aligned_at_offset(size_t size, size_t alignment, size_t align_offset, bool commit, bool allow_large, mi_memid_t* memid);

void* _mi_os_get_aligned_hint(size_t try_alignment, size_t size);
bool _mi_os_use_large_page(size_t size, size_t alignment);
size_t _mi_os_large_page_size(void);
void* _mi_os_alloc_huge_os_pages(size_t pages, int numa_node, mi_msecs_t max_secs, size_t* pages_reserved, size_t* psize, mi_memid_t* memid);

int _mi_os_numa_node_count(void);
int _mi_os_numa_node(void);


mi_arena_id_t _mi_arena_id_none(void);
void _mi_arena_free(void* p, size_t size, size_t still_committed_size, mi_memid_t memid);
void* _mi_arena_alloc(size_t size, bool commit, bool allow_large, mi_arena_id_t req_arena_id, mi_memid_t* memid);
void* _mi_arena_alloc_aligned(size_t size, size_t alignment, size_t align_offset, bool commit, bool allow_large, mi_arena_id_t req_arena_id, mi_memid_t* memid);
bool _mi_arena_memid_is_suitable(mi_memid_t memid, mi_arena_id_t request_arena_id);
bool _mi_arena_contains(const void* p);
void _mi_arenas_collect(bool force_purge);
void _mi_arena_unsafe_destroy_all(void);

bool _mi_arena_segment_clear_abandoned(mi_segment_t* segment);
void _mi_arena_segment_mark_abandoned(mi_segment_t* segment);

void* _mi_arena_meta_zalloc(size_t size, mi_memid_t* memid);
void _mi_arena_meta_free(void* p, mi_memid_t memid, size_t size);

typedef struct mi_arena_field_cursor_s {
  size_t os_list_count;
  size_t start;
  size_t end;
  size_t bitmap_idx;
  mi_subproc_t* subproc;
  bool visit_all;
  bool hold_visit_lock;
} mi_arena_field_cursor_t;
void _mi_arena_field_cursor_init(mi_heap_t* heap, mi_subproc_t* subproc, bool visit_all, mi_arena_field_cursor_t* current);
mi_segment_t* _mi_arena_segment_clear_abandoned_next(mi_arena_field_cursor_t* previous);
void _mi_arena_field_cursor_done(mi_arena_field_cursor_t* current);


void _mi_segment_map_allocated_at(const mi_segment_t* segment);
void _mi_segment_map_freed_at(const mi_segment_t* segment);
void _mi_segment_map_unsafe_destroy(void);


mi_page_t* _mi_segment_page_alloc(mi_heap_t* heap, size_t block_size, size_t page_alignment, mi_segments_tld_t* tld);
void _mi_segment_page_free(mi_page_t* page, bool force, mi_segments_tld_t* tld);
void _mi_segment_page_abandon(mi_page_t* page, mi_segments_tld_t* tld);
bool _mi_segment_try_reclaim_abandoned( mi_heap_t* heap, bool try_all, mi_segments_tld_t* tld);
void _mi_segment_collect(mi_segment_t* segment, bool force);




void _mi_segment_huge_page_reset(mi_segment_t* segment, mi_page_t* page, mi_block_t* block);


uint8_t* _mi_segment_page_start(const mi_segment_t* segment, const mi_page_t* page, size_t* page_size);
void _mi_abandoned_reclaim_all(mi_heap_t* heap, mi_segments_tld_t* tld);
void _mi_abandoned_collect(mi_heap_t* heap, bool force, mi_segments_tld_t* tld);
bool _mi_segment_attempt_reclaim(mi_heap_t* heap, mi_segment_t* segment);
bool _mi_segment_visit_blocks(mi_segment_t* segment, int heap_tag, bool visit_blocks, mi_block_visit_fun* visitor, void* arg);


void* _mi_malloc_generic(mi_heap_t* heap, size_t size, bool zero, size_t huge_alignment) ;

void _mi_page_retire(mi_page_t* page) ;
void _mi_page_unfull(mi_page_t* page);
void _mi_page_free(mi_page_t* page, mi_page_queue_t* pq, bool force);
void _mi_page_abandon(mi_page_t* page, mi_page_queue_t* pq);
void _mi_page_force_abandon(mi_page_t* page);

void _mi_heap_delayed_free_all(mi_heap_t* heap);
bool _mi_heap_delayed_free_partial(mi_heap_t* heap);
void _mi_heap_collect_retired(mi_heap_t* heap, bool force);

void _mi_page_use_delayed_free(mi_page_t* page, mi_delayed_t delay, bool override_never);
bool _mi_page_try_use_delayed_free(mi_page_t* page, mi_delayed_t delay, bool override_never);
size_t _mi_page_queue_append(mi_heap_t* heap, mi_page_queue_t* pq, mi_page_queue_t* append);
void _mi_deferred_free(mi_heap_t* heap, bool force);

void _mi_page_free_collect(mi_page_t* page,bool force);
void _mi_page_reclaim(mi_heap_t* heap, mi_page_t* page);

size_t _mi_page_bin(const mi_page_t* page);
size_t _mi_bin_size(size_t bin);
size_t _mi_bin(size_t size);


void _mi_heap_init(mi_heap_t* heap, mi_tld_t* tld, mi_arena_id_t arena_id, bool noreclaim, uint8_t tag);
void _mi_heap_destroy_pages(mi_heap_t* heap);
void _mi_heap_collect_abandon(mi_heap_t* heap);
void _mi_heap_set_default_direct(mi_heap_t* heap);
bool _mi_heap_memid_is_suitable(mi_heap_t* heap, mi_memid_t memid);
void _mi_heap_unsafe_destroy_all(mi_heap_t* heap);
mi_heap_t* _mi_heap_by_tag(mi_heap_t* heap, uint8_t tag);
void _mi_heap_area_init(mi_heap_area_t* area, mi_page_t* page);
bool _mi_heap_area_visit_blocks(const mi_heap_area_t* area, mi_page_t* page, mi_block_visit_fun* visitor, void* arg);


void _mi_stats_done(mi_stats_t* stats);
void _mi_stats_merge_thread(mi_tld_t* tld);
mi_msecs_t _mi_clock_now(void);
mi_msecs_t _mi_clock_end(mi_msecs_t start);
mi_msecs_t _mi_clock_start(void);


void* _mi_page_malloc_zero(mi_heap_t* heap, mi_page_t* page, size_t size, bool zero) ;
void* _mi_page_malloc(mi_heap_t* heap, mi_page_t* page, size_t size) ;
void* _mi_page_malloc_zeroed(mi_heap_t* heap, mi_page_t* page, size_t size) ;
void* _mi_heap_malloc_zero(mi_heap_t* heap, size_t size, bool zero) ;
void* _mi_heap_malloc_zero_ex(mi_heap_t* heap, size_t size, bool zero, size_t huge_alignment) ;
void* _mi_heap_realloc_zero(mi_heap_t* heap, void* p, size_t newsize, bool zero) ;
mi_block_t* _mi_page_ptr_unalign(const mi_page_t* page, const void* p);
bool _mi_free_delayed_block(mi_block_t* block);
void _mi_free_generic(mi_segment_t* segment, mi_page_t* page, bool is_local, void* p) ;
void _mi_padding_shrink(const mi_page_t* page, const mi_block_t* block, const size_t min_size);


bool _mi_page_is_valid(mi_page_t* page);
# 306 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/errno.h" 1
# 307 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h" 2
# 330 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
 void _mi_assert_fail(const char* assertion, const char* fname, unsigned int line, const char* func) ;
# 369 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 370 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h" 2




static inline bool _mi_is_power_of_two(uintptr_t x) {
  return ((x & (x - 1)) == 0);
}


static inline bool _mi_is_aligned(void* p, size_t alignment) {
  ((alignment != 0) ? (void)0 : _mi_assert_fail("alignment != 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",380,__func__));
  return (((uintptr_t)p % alignment) == 0);
}


static inline uintptr_t _mi_align_up(uintptr_t sz, size_t alignment) {
  ((alignment != 0) ? (void)0 : _mi_assert_fail("alignment != 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",386,__func__));
  uintptr_t mask = alignment - 1;
  if ((alignment & mask) == 0) {
    return ((sz + mask) & ~mask);
  }
  else {
    return (((sz + mask)/alignment)*alignment);
  }
}


static inline uintptr_t _mi_align_down(uintptr_t sz, size_t alignment) {
  ((alignment != 0) ? (void)0 : _mi_assert_fail("alignment != 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",398,__func__));
  uintptr_t mask = alignment - 1;
  if ((alignment & mask) == 0) {
    return (sz & ~mask);
  }
  else {
    return ((sz / alignment) * alignment);
  }
}


static inline void* mi_align_up_ptr(void* p, size_t alignment) {
  return (void*)_mi_align_up((uintptr_t)p, alignment);
}


static inline void* mi_align_down_ptr(void* p, size_t alignment) {
  return (void*)_mi_align_down((uintptr_t)p, alignment);
}



static inline uintptr_t _mi_divide_up(uintptr_t size, size_t divider) {
  ((divider != 0) ? (void)0 : _mi_assert_fail("divider != 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",421,__func__));
  return (divider == 0 ? size : ((size + divider - 1) / divider));
}



static inline size_t _mi_clamp(size_t sz, size_t min, size_t max) {
  if (sz < min) return min;
  else if (sz > max) return max;
  else return sz;
}


static inline bool mi_mem_is_zero(const void* p, size_t size) {
  for (size_t i = 0; i < size; i++) {
    if (((uint8_t*)p)[i] != 0) return 0;
  }
  return 1;
}




static inline size_t _mi_wsize_from_size(size_t size) {
  ((size <= SIZE_MAX - sizeof(uintptr_t)) ? (void)0 : _mi_assert_fail("size <= SIZE_MAX - sizeof(uintptr_t)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",445,__func__));
  return (size + sizeof(uintptr_t) - 1) / sizeof(uintptr_t);
}



# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 1
# 452 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h" 2



static inline bool mi_mul_overflow(size_t count, size_t size, size_t* total) {





    return __builtin_umulll_overflow(count, size, (unsigned long long *)total);

}
# 474 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
static inline bool mi_count_size_overflow(size_t count, size_t size, size_t* total) {
  if (count==1) {
    *total = size;
    return 0;
  }
  else if (__builtin_expect(!!(mi_mul_overflow(count, size, total)),0)) {

    _mi_error_message((75), "allocation request is too large (%zu * %zu bytes)\n", count, size);

    *total = SIZE_MAX;
    return 1;
  }
  else return 0;
}






extern const mi_heap_t _mi_heap_empty;

static inline bool mi_heap_is_backing(const mi_heap_t* heap) {
  return (heap->tld->heap_backing == heap);
}

static inline bool mi_heap_is_initialized(mi_heap_t* heap) {
  ((heap != 0) ? (void)0 : _mi_assert_fail("heap != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",501,__func__));
  return (heap != 0 && heap != &_mi_heap_empty);
}

static inline uintptr_t _mi_ptr_cookie(const void* p) {
  extern mi_heap_t _mi_heap_main;
  ((_mi_heap_main.cookie != 0) ? (void)0 : _mi_assert_fail("_mi_heap_main.cookie != 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",507,__func__));
  return ((uintptr_t)p ^ _mi_heap_main.cookie);
}





static inline mi_page_t* _mi_heap_get_free_small_page(mi_heap_t* heap, size_t size) {
  ((size <= (((128)*sizeof(void*)) + (sizeof(mi_padding_t)))) ? (void)0 : _mi_assert_fail("size <= (MI_SMALL_SIZE_MAX + MI_PADDING_SIZE)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",516,__func__));
  const size_t idx = _mi_wsize_from_size(size);
  ((idx < ((128) + (((sizeof(mi_padding_t)) + (1<<(3)) - 1) / (1<<(3))) + 1)) ? (void)0 : _mi_assert_fail("idx < MI_PAGES_DIRECT","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",518,__func__));
  return heap->pages_free_direct[idx];
}






static inline mi_segment_t* _mi_ptr_segment(const void* p) {
  mi_segment_t* const segment = (mi_segment_t*)(((uintptr_t)p - 1) & ~((uintptr_t)((1UL<<( 9 + (13 + (3)))) - 1)));



  return ((intptr_t)segment <= 0 ? 0 : segment);

}

static inline mi_page_t* mi_slice_to_page(mi_slice_t* s) {
  ((s->slice_offset== 0 && s->slice_count > 0) ? (void)0 : _mi_assert_fail("s->slice_offset== 0 && s->slice_count > 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",537,__func__));
  return (mi_page_t*)(s);
}

static inline mi_slice_t* mi_page_to_slice(mi_page_t* p) {
  ((p->slice_offset== 0 && p->slice_count > 0) ? (void)0 : _mi_assert_fail("p->slice_offset== 0 && p->slice_count > 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",542,__func__));
  return (mi_slice_t*)(p);
}


static inline mi_segment_t* _mi_page_segment(const mi_page_t* page) {
  ((page!=0) ? (void)0 : _mi_assert_fail("page!=NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",548,__func__));
  mi_segment_t* segment = _mi_ptr_segment(page);
  ((segment == 0 || ((mi_slice_t*)page >= segment->slices && (mi_slice_t*)page < segment->slices + segment->slice_entries)) ? (void)0 : _mi_assert_fail("segment == NULL || ((mi_slice_t*)page >= segment->slices && (mi_slice_t*)page < segment->slices + segment->slice_entries)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",550,__func__));
  return segment;
}

static inline mi_slice_t* mi_slice_first(const mi_slice_t* slice) {
  mi_slice_t* start = (mi_slice_t*)((uint8_t*)slice - slice->slice_offset);
  ((start >= _mi_ptr_segment(slice)->slices) ? (void)0 : _mi_assert_fail("start >= _mi_ptr_segment(slice)->slices","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",556,__func__));
  ((start->slice_offset == 0) ? (void)0 : _mi_assert_fail("start->slice_offset == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",557,__func__));
  ((start + start->slice_count > slice) ? (void)0 : _mi_assert_fail("start + start->slice_count > slice","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",558,__func__));
  return start;
}


static inline mi_page_t* _mi_segment_page_of(const mi_segment_t* segment, const void* p) {
  ((p > (void*)segment) ? (void)0 : _mi_assert_fail("p > (void*)segment","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",564,__func__));
  ptrdiff_t diff = (uint8_t*)p - (uint8_t*)segment;
  ((diff > 0 && diff <= (ptrdiff_t)(1UL<<( 9 + (13 + (3))))) ? (void)0 : _mi_assert_fail("diff > 0 && diff <= (ptrdiff_t)MI_SEGMENT_SIZE","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",566,__func__));
  size_t idx = (size_t)diff >> (13 + (3));
  ((idx <= segment->slice_entries) ? (void)0 : _mi_assert_fail("idx <= segment->slice_entries","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",568,__func__));
  mi_slice_t* slice0 = (mi_slice_t*)&segment->slices[idx];
  mi_slice_t* slice = mi_slice_first(slice0);
  ((slice->slice_offset == 0) ? (void)0 : _mi_assert_fail("slice->slice_offset == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",571,__func__));
  ((slice >= segment->slices && slice < segment->slices + segment->slice_entries) ? (void)0 : _mi_assert_fail("slice >= segment->slices && slice < segment->slices + segment->slice_entries","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",572,__func__));
  return mi_slice_to_page(slice);
}


static inline uint8_t* mi_page_start(const mi_page_t* page) {
  ((page->page_start != 0) ? (void)0 : _mi_assert_fail("page->page_start != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",578,__func__));
  ;
  return page->page_start;
}


static inline mi_page_t* _mi_ptr_page(void* p) {
  ((p!=0) ? (void)0 : _mi_assert_fail("p!=NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",585,__func__));
  return _mi_segment_page_of(_mi_ptr_segment(p), p);
}


static inline size_t mi_page_block_size(const mi_page_t* page) {
  ((page->block_size > 0) ? (void)0 : _mi_assert_fail("page->block_size > 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",591,__func__));
  return page->block_size;
}

static inline bool mi_page_is_huge(const mi_page_t* page) {
  (((page->is_huge && _mi_page_segment(page)->kind == MI_SEGMENT_HUGE) || (!page->is_huge && _mi_page_segment(page)->kind != MI_SEGMENT_HUGE)) ? (void)0 : _mi_assert_fail("(page->is_huge && _mi_page_segment(page)->kind == MI_SEGMENT_HUGE) || (!page->is_huge && _mi_page_segment(page)->kind != MI_SEGMENT_HUGE)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",596,__func__))
                                                                                         ;
  return page->is_huge;
}



static inline size_t mi_page_usable_block_size(const mi_page_t* page) {
  return mi_page_block_size(page) - (sizeof(mi_padding_t));
}


static inline size_t mi_segment_size(mi_segment_t* segment) {
  return segment->segment_slices * (1UL<< (13 + (3)));
}

static inline uint8_t* mi_segment_end(mi_segment_t* segment) {
  return (uint8_t*)segment + mi_segment_size(segment);
}


static inline mi_block_t* mi_page_thread_free(const mi_page_t* page) {
  return (mi_block_t*)(atomic_load_explicit(&((mi_page_t*)page)->xthread_free,memory_order_relaxed) & ~3);
}

static inline mi_delayed_t mi_page_thread_free_flag(const mi_page_t* page) {
  return (mi_delayed_t)(atomic_load_explicit(&((mi_page_t*)page)->xthread_free,memory_order_relaxed) & 3);
}


static inline mi_heap_t* mi_page_heap(const mi_page_t* page) {
  return (mi_heap_t*)(atomic_load_explicit(&((mi_page_t*)page)->xheap,memory_order_relaxed));
}

static inline void mi_page_set_heap(mi_page_t* page, mi_heap_t* heap) {
  ((mi_page_thread_free_flag(page) != MI_DELAYED_FREEING) ? (void)0 : _mi_assert_fail("mi_page_thread_free_flag(page) != MI_DELAYED_FREEING","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",631,__func__));
  atomic_store_explicit(&page->xheap,(uintptr_t)heap,memory_order_release);
  if (heap != 0) { page->heap_tag = heap->tag; }
}


static inline mi_block_t* mi_tf_block(mi_thread_free_t tf) {
  return (mi_block_t*)(tf & ~0x03);
}
static inline mi_delayed_t mi_tf_delayed(mi_thread_free_t tf) {
  return (mi_delayed_t)(tf & 0x03);
}
static inline mi_thread_free_t mi_tf_make(mi_block_t* block, mi_delayed_t delayed) {
  return (mi_thread_free_t)((uintptr_t)block | (uintptr_t)delayed);
}
static inline mi_thread_free_t mi_tf_set_delayed(mi_thread_free_t tf, mi_delayed_t delayed) {
  return mi_tf_make(mi_tf_block(tf),delayed);
}
static inline mi_thread_free_t mi_tf_set_block(mi_thread_free_t tf, mi_block_t* block) {
  return mi_tf_make(block, mi_tf_delayed(tf));
}



static inline bool mi_page_all_free(const mi_page_t* page) {
  ((page != 0) ? (void)0 : _mi_assert_fail("page != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",656,__func__));
  return (page->used == 0);
}


static inline bool mi_page_has_any_available(const mi_page_t* page) {
  ((page != 0 && page->reserved > 0) ? (void)0 : _mi_assert_fail("page != NULL && page->reserved > 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",662,__func__));
  return (page->used < page->reserved || (mi_page_thread_free(page) != 0));
}


static inline bool mi_page_immediate_available(const mi_page_t* page) {
  ((page != 0) ? (void)0 : _mi_assert_fail("page != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",668,__func__));
  return (page->free != 0);
}


static inline bool mi_page_is_mostly_used(const mi_page_t* page) {
  if (page==0) return 1;
  uint16_t frac = page->reserved / 8U;
  return (page->reserved - page->used <= frac);
}

static inline mi_page_queue_t* mi_page_queue(const mi_heap_t* heap, size_t size) {
  return &((mi_heap_t*)heap)->pages[_mi_bin(size)];
}






static inline bool mi_page_is_in_full(const mi_page_t* page) {
  return page->flags.x.in_full;
}

static inline void mi_page_set_in_full(mi_page_t* page, bool in_full) {
  page->flags.x.in_full = in_full;
}

static inline bool mi_page_has_aligned(const mi_page_t* page) {
  return page->flags.x.has_aligned;
}

static inline void mi_page_set_has_aligned(mi_page_t* page, bool has_aligned) {
  page->flags.x.has_aligned = has_aligned;
}
# 763 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
static inline bool mi_is_in_same_segment(const void* p, const void* q) {
  return (_mi_ptr_segment(p) == _mi_ptr_segment(q));
}

static inline bool mi_is_in_same_page(const void* p, const void* q) {
  mi_segment_t* segment = _mi_ptr_segment(p);
  if (_mi_ptr_segment(q) != segment) return 0;

  mi_page_t* page = _mi_segment_page_of(segment, p);
  size_t psize;
  uint8_t* start = _mi_segment_page_start(segment, page, &psize);
  return (start <= (uint8_t*)q && (uint8_t*)q < start + psize);
}

static inline uintptr_t mi_rotl(uintptr_t x, uintptr_t shift) {
  shift %= ((1<<(3))*8);
  return (shift==0 ? x : ((x << shift) | (x >> (((1<<(3))*8) - shift))));
}
static inline uintptr_t mi_rotr(uintptr_t x, uintptr_t shift) {
  shift %= ((1<<(3))*8);
  return (shift==0 ? x : ((x >> shift) | (x << (((1<<(3))*8) - shift))));
}

static inline void* mi_ptr_decode(const void* null, const mi_encoded_t x, const uintptr_t* keys) {
  void* p = (void*)(mi_rotr(x - keys[0], keys[0]) ^ keys[1]);
  return (p==null ? 0 : p);
}

static inline mi_encoded_t mi_ptr_encode(const void* null, const void* p, const uintptr_t* keys) {
  uintptr_t x = (uintptr_t)(p==0 ? null : p);
  return mi_rotl(x ^ keys[1], keys[0]) + keys[0];
}

static inline uint32_t mi_ptr_encode_canary(const void* null, const void* p, const uintptr_t* keys) {
  const uint32_t x = (uint32_t)(mi_ptr_encode(null,p,keys));




  return (x & 0xFFFFFF00);

}

static inline mi_block_t* mi_block_nextx( const void* null, const mi_block_t* block, const uintptr_t* keys ) {
  ;
  mi_block_t* next;

  next = (mi_block_t*)mi_ptr_decode(null, block->next, keys);




  ;
  return next;
}

static inline void mi_block_set_nextx(const void* null, mi_block_t* block, const mi_block_t* next, const uintptr_t* keys) {
  ;

  block->next = mi_ptr_encode(null, next, keys);




  ;
}

static inline mi_block_t* mi_block_next(const mi_page_t* page, const mi_block_t* block) {

  mi_block_t* next = mi_block_nextx(page,block,page->keys);


  if (__builtin_expect(!!(next!=0 && !mi_is_in_same_page(block, next)),0)) {
    _mi_error_message((14), "corrupted free list entry of size %zub at %p: value 0x%zx\n", mi_page_block_size(page), block, (uintptr_t)next);
    next = 0;
  }
  return next;




}

static inline void mi_block_set_next(const mi_page_t* page, mi_block_t* block, const mi_block_t* next) {

  mi_block_set_nextx(page,block,next, page->keys);




}






static inline void mi_commit_mask_create_empty(mi_commit_mask_t* cm) {
  for (size_t i = 0; i < (((1UL<<( 9 + (13 + (3)))) / ((1UL<< (13 + (3))))) / ((1<<(3))*8)); i++) {
    cm->mask[i] = 0;
  }
}

static inline void mi_commit_mask_create_full(mi_commit_mask_t* cm) {
  for (size_t i = 0; i < (((1UL<<( 9 + (13 + (3)))) / ((1UL<< (13 + (3))))) / ((1<<(3))*8)); i++) {
    cm->mask[i] = ~((size_t)0);
  }
}

static inline bool mi_commit_mask_is_empty(const mi_commit_mask_t* cm) {
  for (size_t i = 0; i < (((1UL<<( 9 + (13 + (3)))) / ((1UL<< (13 + (3))))) / ((1<<(3))*8)); i++) {
    if (cm->mask[i] != 0) return 0;
  }
  return 1;
}

static inline bool mi_commit_mask_is_full(const mi_commit_mask_t* cm) {
  for (size_t i = 0; i < (((1UL<<( 9 + (13 + (3)))) / ((1UL<< (13 + (3))))) / ((1<<(3))*8)); i++) {
    if (cm->mask[i] != ~((size_t)0)) return 0;
  }
  return 1;
}


size_t _mi_commit_mask_committed_size(const mi_commit_mask_t* cm, size_t total);
size_t _mi_commit_mask_next_run(const mi_commit_mask_t* cm, size_t* idx);
# 904 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
static inline mi_memid_t _mi_memid_create(mi_memkind_t memkind) {
  mi_memid_t memid;
  memset(&memid,0,sizeof(memid));
  memid.memkind = memkind;
  return memid;
}

static inline mi_memid_t _mi_memid_none(void) {
  return _mi_memid_create(MI_MEM_NONE);
}

static inline mi_memid_t _mi_memid_create_os(void* base, size_t size, bool committed, bool is_zero, bool is_large) {
  mi_memid_t memid = _mi_memid_create(MI_MEM_OS);
  memid.mem.os.base = base;
  memid.mem.os.size = size;
  memid.initially_committed = committed;
  memid.initially_zero = is_zero;
  memid.is_pinned = is_large;
  return memid;
}






static inline uintptr_t _mi_random_shuffle(uintptr_t x) {
  if (x==0) { x = 17; }


  x ^= x >> 30;
  x *= 0xbf58476d1ce4e5b9UL;
  x ^= x >> 27;
  x *= 0x94d049bb133111ebUL;
  x ^= x >> 31;
# 947 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
  return x;
}
# 958 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 1
# 959 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h" 2

static inline size_t mi_clz(size_t x) {
  if (x==0) return ((1<<(3))*8);



    return __builtin_clzll(x);

}
static inline size_t mi_ctz(size_t x) {
  if (x==0) return ((1<<(3))*8);



    return __builtin_ctzll(x);

}
# 1063 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
static inline size_t mi_bsr(size_t x) {
  return (x==0 ? ((1<<(3))*8) : ((1<<(3))*8) - 1 - mi_clz(x));
}

size_t _mi_popcount_generic(size_t x);

static inline size_t mi_popcount(size_t x) {
  if (x<=1) return x;
  if (x==SIZE_MAX) return ((1<<(3))*8);




      return __builtin_popcountll(x);




}
# 1112 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
static inline void _mi_memcpy(void* dst, const void* src, size_t n) {
  memcpy(dst, src, n);
}
static inline void _mi_memzero(void* dst, size_t n) {
  memset(dst, 0, n);
}
# 1127 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
static inline void _mi_memcpy_aligned(void* dst, const void* src, size_t n) {
  ((((uintptr_t)dst % (1<<(3)) == 0) && ((uintptr_t)src % (1<<(3)) == 0)) ? (void)0 : _mi_assert_fail("((uintptr_t)dst % MI_INTPTR_SIZE == 0) && ((uintptr_t)src % MI_INTPTR_SIZE == 0)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",1128,__func__));
  void* adst = __builtin_assume_aligned(dst, (1<<(3)));
  const void* asrc = __builtin_assume_aligned(src, (1<<(3)));
  _mi_memcpy(adst, asrc, n);
}

static inline void _mi_memzero_aligned(void* dst, size_t n) {
  (((uintptr_t)dst % (1<<(3)) == 0) ? (void)0 : _mi_assert_fail("(uintptr_t)dst % MI_INTPTR_SIZE == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",1135,__func__));
  void* adst = __builtin_assume_aligned(dst, (1<<(3)));
  _mi_memzero(adst, n);
}
# 9 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c" 2


# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 12 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 13 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c" 2







static void mi_segment_try_purge(mi_segment_t* segment, bool force);






static bool mi_commit_mask_all_set(const mi_commit_mask_t* commit, const mi_commit_mask_t* cm) {
  for (size_t i = 0; i < (((1UL<<( 9 + (13 + (3)))) / ((1UL<< (13 + (3))))) / ((1<<(3))*8)); i++) {
    if ((commit->mask[i] & cm->mask[i]) != cm->mask[i]) return 0;
  }
  return 1;
}

static bool mi_commit_mask_any_set(const mi_commit_mask_t* commit, const mi_commit_mask_t* cm) {
  for (size_t i = 0; i < (((1UL<<( 9 + (13 + (3)))) / ((1UL<< (13 + (3))))) / ((1<<(3))*8)); i++) {
    if ((commit->mask[i] & cm->mask[i]) != 0) return 1;
  }
  return 0;
}

static void mi_commit_mask_create_intersect(const mi_commit_mask_t* commit, const mi_commit_mask_t* cm, mi_commit_mask_t* res) {
  for (size_t i = 0; i < (((1UL<<( 9 + (13 + (3)))) / ((1UL<< (13 + (3))))) / ((1<<(3))*8)); i++) {
    res->mask[i] = (commit->mask[i] & cm->mask[i]);
  }
}

static void mi_commit_mask_clear(mi_commit_mask_t* res, const mi_commit_mask_t* cm) {
  for (size_t i = 0; i < (((1UL<<( 9 + (13 + (3)))) / ((1UL<< (13 + (3))))) / ((1<<(3))*8)); i++) {
    res->mask[i] &= ~(cm->mask[i]);
  }
}

static void mi_commit_mask_set(mi_commit_mask_t* res, const mi_commit_mask_t* cm) {
  for (size_t i = 0; i < (((1UL<<( 9 + (13 + (3)))) / ((1UL<< (13 + (3))))) / ((1<<(3))*8)); i++) {
    res->mask[i] |= cm->mask[i];
  }
}

static void mi_commit_mask_create(size_t bitidx, size_t bitcount, mi_commit_mask_t* cm) {
  ((bitidx < ((1UL<<( 9 + (13 + (3)))) / ((1UL<< (13 + (3)))))) ? (void)0 : _mi_assert_fail("bitidx < MI_COMMIT_MASK_BITS","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",60,__func__));
  (((bitidx + bitcount) <= ((1UL<<( 9 + (13 + (3)))) / ((1UL<< (13 + (3)))))) ? (void)0 : _mi_assert_fail("(bitidx + bitcount) <= MI_COMMIT_MASK_BITS","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",61,__func__));
  if (bitcount == ((1UL<<( 9 + (13 + (3)))) / ((1UL<< (13 + (3)))))) {
    ((bitidx==0) ? (void)0 : _mi_assert_fail("bitidx==0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",63,__func__));
    mi_commit_mask_create_full(cm);
  }
  else if (bitcount == 0) {
    mi_commit_mask_create_empty(cm);
  }
  else {
    mi_commit_mask_create_empty(cm);
    size_t i = bitidx / ((1<<(3))*8);
    size_t ofs = bitidx % ((1<<(3))*8);
    while (bitcount > 0) {
      ((i < (((1UL<<( 9 + (13 + (3)))) / ((1UL<< (13 + (3))))) / ((1<<(3))*8))) ? (void)0 : _mi_assert_fail("i < MI_COMMIT_MASK_FIELD_COUNT","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",74,__func__));
      size_t avail = ((1<<(3))*8) - ofs;
      size_t count = (bitcount > avail ? avail : bitcount);
      size_t mask = (count >= ((1<<(3))*8) ? ~((size_t)0) : (((size_t)1 << count) - 1) << ofs);
      cm->mask[i] = mask;
      bitcount -= count;
      ofs = 0;
      i++;
    }
  }
}

size_t _mi_commit_mask_committed_size(const mi_commit_mask_t* cm, size_t total) {
  (((total%((1UL<<( 9 + (13 + (3)))) / ((1UL<< (13 + (3))))))==0) ? (void)0 : _mi_assert_fail("(total%MI_COMMIT_MASK_BITS)==0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",87,__func__));
  size_t count = 0;
  for (size_t i = 0; i < (((1UL<<( 9 + (13 + (3)))) / ((1UL<< (13 + (3))))) / ((1<<(3))*8)); i++) {
    size_t mask = cm->mask[i];
    if (~mask == 0) {
      count += ((1<<(3))*8);
    }
    else {
      for (; mask != 0; mask >>= 1) {
        if ((mask&1)!=0) count++;
      }
    }
  }

  return ((total / ((1UL<<( 9 + (13 + (3)))) / ((1UL<< (13 + (3)))))) * count);
}


size_t _mi_commit_mask_next_run(const mi_commit_mask_t* cm, size_t* idx) {
  size_t i = (*idx) / ((1<<(3))*8);
  size_t ofs = (*idx) % ((1<<(3))*8);
  size_t mask = 0;

  while (i < (((1UL<<( 9 + (13 + (3)))) / ((1UL<< (13 + (3))))) / ((1<<(3))*8))) {
    mask = cm->mask[i];
    mask >>= ofs;
    if (mask != 0) {
      while ((mask&1) == 0) {
        mask >>= 1;
        ofs++;
      }
      break;
    }
    i++;
    ofs = 0;
  }
  if (i >= (((1UL<<( 9 + (13 + (3)))) / ((1UL<< (13 + (3))))) / ((1<<(3))*8))) {

    *idx = ((1UL<<( 9 + (13 + (3)))) / ((1UL<< (13 + (3)))));
    return 0;
  }
  else {

    size_t count = 0;
    *idx = (i*((1<<(3))*8)) + ofs;
    do {
      ((ofs < ((1<<(3))*8) && (mask&1) == 1) ? (void)0 : _mi_assert_fail("ofs < MI_COMMIT_MASK_FIELD_BITS && (mask&1) == 1","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",133,__func__));
      do {
        count++;
        mask >>= 1;
      } while ((mask&1) == 1);
      if ((((*idx + count) % ((1<<(3))*8)) == 0)) {
        i++;
        if (i >= (((1UL<<( 9 + (13 + (3)))) / ((1UL<< (13 + (3))))) / ((1<<(3))*8))) break;
        mask = cm->mask[i];
        ofs = 0;
      }
    } while ((mask&1) == 1);
    ((count > 0) ? (void)0 : _mi_assert_fail("count > 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",145,__func__));
    return count;
  }
}
# 178 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c"
static const mi_slice_t* mi_segment_slices_end(const mi_segment_t* segment) {
  return &segment->slices[segment->slice_entries];
}

static uint8_t* mi_slice_start(const mi_slice_t* slice) {
  mi_segment_t* segment = _mi_ptr_segment(slice);
  ((slice >= segment->slices && slice < mi_segment_slices_end(segment)) ? (void)0 : _mi_assert_fail("slice >= segment->slices && slice < mi_segment_slices_end(segment)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",184,__func__));
  return ((uint8_t*)segment + ((slice - segment->slices)*(1UL<< (13 + (3)))));
}







static inline size_t mi_slice_bin8(size_t slice_count) {
  if (slice_count<=1) return slice_count;
  ((slice_count <= ((1UL<<( 9 + (13 + (3)))) / (1UL<< (13 + (3))))) ? (void)0 : _mi_assert_fail("slice_count <= MI_SLICES_PER_SEGMENT","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",196,__func__));
  slice_count--;
  size_t s = mi_bsr(slice_count);
  if (s <= 2) return slice_count + 1;
  size_t bin = ((s << 2) | ((slice_count >> (s - 2))&0x03)) - 4;
  return bin;
}

static inline size_t mi_slice_bin(size_t slice_count) {
  ((slice_count*(1UL<< (13 + (3))) <= (1UL<<( 9 + (13 + (3))))) ? (void)0 : _mi_assert_fail("slice_count*MI_SEGMENT_SLICE_SIZE <= MI_SEGMENT_SIZE","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",205,__func__));
  ((mi_slice_bin8(((1UL<<( 9 + (13 + (3)))) / (1UL<< (13 + (3))))) <= (35)) ? (void)0 : _mi_assert_fail("mi_slice_bin8(MI_SLICES_PER_SEGMENT) <= MI_SEGMENT_BIN_MAX","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",206,__func__));
  size_t bin = mi_slice_bin8(slice_count);
  ((bin <= (35)) ? (void)0 : _mi_assert_fail("bin <= MI_SEGMENT_BIN_MAX","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",208,__func__));
  return bin;
}

static inline size_t mi_slice_index(const mi_slice_t* slice) {
  mi_segment_t* segment = _mi_ptr_segment(slice);
  ptrdiff_t index = slice - segment->slices;
  ((index >= 0 && index < (ptrdiff_t)segment->slice_entries) ? (void)0 : _mi_assert_fail("index >= 0 && index < (ptrdiff_t)segment->slice_entries","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",215,__func__));
  return index;
}






static void mi_span_queue_push(mi_span_queue_t* sq, mi_slice_t* slice) {

  ((slice->prev == 0 && slice->next==0) ? (void)0 : _mi_assert_fail("slice->prev == NULL && slice->next==NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",226,__func__));
  slice->prev = 0;
  slice->next = sq->first;
  sq->first = slice;
  if (slice->next != 0) slice->next->prev = slice;
                     else sq->last = slice;
  slice->block_size = 0;
}

static mi_span_queue_t* mi_span_queue_for(size_t slice_count, mi_segments_tld_t* tld) {
  size_t bin = mi_slice_bin(slice_count);
  mi_span_queue_t* sq = &tld->spans[bin];
  ((sq->slice_count >= slice_count) ? (void)0 : _mi_assert_fail("sq->slice_count >= slice_count","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",238,__func__));
  return sq;
}

static void mi_span_queue_delete(mi_span_queue_t* sq, mi_slice_t* slice) {
  ((slice->block_size==0 && slice->slice_count>0 && slice->slice_offset==0) ? (void)0 : _mi_assert_fail("slice->block_size==0 && slice->slice_count>0 && slice->slice_offset==0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",243,__func__));

  if (slice->prev != 0) slice->prev->next = slice->next;
  if (slice == sq->first) sq->first = slice->next;
  if (slice->next != 0) slice->next->prev = slice->prev;
  if (slice == sq->last) sq->last = slice->prev;
  slice->prev = 0;
  slice->next = 0;
  slice->block_size = 1;
}






static bool mi_slice_is_used(const mi_slice_t* slice) {
  return (slice->block_size > 0);
}
# 328 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c"
static size_t mi_segment_info_size(mi_segment_t* segment) {
  return segment->segment_info_slices * (1UL<< (13 + (3)));
}

static uint8_t* _mi_segment_page_start_from_slice(const mi_segment_t* segment, const mi_slice_t* slice, size_t block_size, size_t* page_size)
{
  const ptrdiff_t idx = slice - segment->slices;
  const size_t psize = (size_t)slice->slice_count * (1UL<< (13 + (3)));
  uint8_t* const pstart = (uint8_t*)segment + (idx*(1UL<< (13 + (3))));



  size_t start_offset = 0;
  if (block_size > 0 && block_size <= (((1UL<<( 3 + ((13 + (3)))))/8))) {

    const size_t adjust = block_size - ((uintptr_t)pstart % block_size);
    if (adjust < block_size && psize >= block_size + adjust) {
      start_offset += adjust;
    }
  }
  if (block_size >= (1<<(3))) {
    if (block_size <= 64) { start_offset += 3*block_size; }
    else if (block_size <= 512) { start_offset += block_size; }
  }
  start_offset = _mi_align_up(start_offset, 16);
  ((_mi_is_aligned(pstart + start_offset, 16)) ? (void)0 : _mi_assert_fail("_mi_is_aligned(pstart + start_offset, MI_MAX_ALIGN_SIZE)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",353,__func__));
  ((block_size == 0 || block_size > (((1UL<<( 3 + ((13 + (3)))))/8)) || _mi_is_aligned(pstart + start_offset,block_size)) ? (void)0 : _mi_assert_fail("block_size == 0 || block_size > MI_MAX_ALIGN_GUARANTEE || _mi_is_aligned(pstart + start_offset,block_size)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",354,__func__));
  if (page_size != 0) { *page_size = psize - start_offset; }
  return (pstart + start_offset);
}


uint8_t* _mi_segment_page_start(const mi_segment_t* segment, const mi_page_t* page, size_t* page_size)
{
  const mi_slice_t* slice = mi_page_to_slice((mi_page_t*)page);
  uint8_t* p = _mi_segment_page_start_from_slice(segment, slice, mi_page_block_size(page), page_size);
  ((mi_page_block_size(page) > 0 || _mi_ptr_page(p) == page) ? (void)0 : _mi_assert_fail("mi_page_block_size(page) > 0 || _mi_ptr_page(p) == page","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",364,__func__));
  ((_mi_ptr_segment(p) == segment) ? (void)0 : _mi_assert_fail("_mi_ptr_segment(p) == segment","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",365,__func__));
  return p;
}


static size_t mi_segment_calculate_slices(size_t required, size_t* info_slices) {
  size_t page_size = _mi_os_page_size();
  size_t isize = _mi_align_up(sizeof(mi_segment_t), page_size);
  size_t guardsize = 0;

  if (0>0) {


    guardsize = page_size;
    if (required > 0) {
      required = _mi_align_up(required, (1UL<< (13 + (3)))) + page_size;
    }
  }

  isize = _mi_align_up(isize + guardsize, (1UL<< (13 + (3))));
  if (info_slices != 0) *info_slices = isize / (1UL<< (13 + (3)));
  size_t segment_size = (required==0 ? (1UL<<( 9 + (13 + (3)))) : _mi_align_up( required + isize + guardsize, (1UL<< (13 + (3)))) );
  ((segment_size % (1UL<< (13 + (3))) == 0) ? (void)0 : _mi_assert_fail("segment_size % MI_SEGMENT_SLICE_SIZE == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",387,__func__));
  return (segment_size / (1UL<< (13 + (3))));
}
# 398 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c"
static void mi_segments_track_size(long segment_size, mi_segments_tld_t* tld) {
  if (segment_size>=0) _mi_stat_increase(&tld->stats->segments,1);
                  else _mi_stat_decrease(&tld->stats->segments,1);
  tld->count += (segment_size >= 0 ? 1 : -1);
  if (tld->count > tld->peak_count) tld->peak_count = tld->count;
  tld->current_size += segment_size;
  if (tld->current_size > tld->peak_size) tld->peak_size = tld->current_size;
}

static void mi_segment_os_free(mi_segment_t* segment, mi_segments_tld_t* tld) {
  segment->thread_id = 0;
  _mi_segment_map_freed_at(segment);
  mi_segments_track_size(-((long)mi_segment_size(segment)),tld);
  if (segment->was_reclaimed) {
    tld->reclaim_count--;
    segment->was_reclaimed = 0;
  }
  if (0>0) {


    size_t os_pagesize = _mi_os_page_size();
    _mi_os_unprotect((uint8_t*)segment + mi_segment_info_size(segment) - os_pagesize, os_pagesize);
    uint8_t* end = (uint8_t*)segment + mi_segment_size(segment) - os_pagesize;
    _mi_os_unprotect(end, os_pagesize);
  }




  const size_t size = mi_segment_size(segment);
  const size_t csize = _mi_commit_mask_committed_size(&segment->commit_mask, size);

  _mi_arena_free(segment, mi_segment_size(segment), csize, segment->memid);
}





static void mi_segment_commit_mask(mi_segment_t* segment, bool conservative, uint8_t* p, size_t size, uint8_t** start_p, size_t* full_size, mi_commit_mask_t* cm) {
  ((_mi_ptr_segment(p + 1) == segment) ? (void)0 : _mi_assert_fail("_mi_ptr_segment(p + 1) == segment","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",438,__func__));
  ((segment->kind != MI_SEGMENT_HUGE) ? (void)0 : _mi_assert_fail("segment->kind != MI_SEGMENT_HUGE","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",439,__func__));
  mi_commit_mask_create_empty(cm);
  if (size == 0 || size > (1UL<<( 9 + (13 + (3)))) || segment->kind == MI_SEGMENT_HUGE) return;
  const size_t segstart = mi_segment_info_size(segment);
  const size_t segsize = mi_segment_size(segment);
  if (p >= (uint8_t*)segment + segsize) return;

  size_t pstart = (p - (uint8_t*)segment);
  ((pstart + size <= segsize) ? (void)0 : _mi_assert_fail("pstart + size <= segsize","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",447,__func__));

  size_t start;
  size_t end;
  if (conservative) {

    start = _mi_align_up(pstart, ((1UL<< (13 + (3)))));
    end = _mi_align_down(pstart + size, ((1UL<< (13 + (3)))));
    ((start >= segstart) ? (void)0 : _mi_assert_fail("start >= segstart","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",455,__func__));
    ((end <= segsize) ? (void)0 : _mi_assert_fail("end <= segsize","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",456,__func__));
  }
  else {

    start = _mi_align_down(pstart, (1*(1UL<< (13 + (3)))));
    end = _mi_align_up(pstart + size, (1*(1UL<< (13 + (3)))));
  }
  if (pstart >= segstart && start < segstart) {
    start = segstart;
  }
  if (end > segsize) {
    end = segsize;
  }

  ((start <= pstart && (pstart + size) <= end) ? (void)0 : _mi_assert_fail("start <= pstart && (pstart + size) <= end","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",470,__func__));
  ((start % ((1UL<< (13 + (3))))==0 && end % ((1UL<< (13 + (3)))) == 0) ? (void)0 : _mi_assert_fail("start % MI_COMMIT_SIZE==0 && end % MI_COMMIT_SIZE == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",471,__func__));
  *start_p = (uint8_t*)segment + start;
  *full_size = (end > start ? end - start : 0);
  if (*full_size == 0) return;

  size_t bitidx = start / ((1UL<< (13 + (3))));
  ((bitidx < ((1UL<<( 9 + (13 + (3)))) / ((1UL<< (13 + (3)))))) ? (void)0 : _mi_assert_fail("bitidx < MI_COMMIT_MASK_BITS","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",477,__func__));

  size_t bitcount = *full_size / ((1UL<< (13 + (3))));
  if (bitidx + bitcount > ((1UL<<( 9 + (13 + (3)))) / ((1UL<< (13 + (3)))))) {
    _mi_warning_message("commit mask overflow: idx=%zu count=%zu start=%zx end=%zx p=0x%p size=%zu fullsize=%zu\n", bitidx, bitcount, start, end, p, size, *full_size);
  }
  (((bitidx + bitcount) <= ((1UL<<( 9 + (13 + (3)))) / ((1UL<< (13 + (3)))))) ? (void)0 : _mi_assert_fail("(bitidx + bitcount) <= MI_COMMIT_MASK_BITS","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",483,__func__));
  mi_commit_mask_create(bitidx, bitcount, cm);
}

static bool mi_segment_commit(mi_segment_t* segment, uint8_t* p, size_t size) {
  ((mi_commit_mask_all_set(&segment->commit_mask, &segment->purge_mask)) ? (void)0 : _mi_assert_fail("mi_commit_mask_all_set(&segment->commit_mask, &segment->purge_mask)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",488,__func__));


  uint8_t* start = 0;
  size_t full_size = 0;
  mi_commit_mask_t mask;
  mi_segment_commit_mask(segment, 0 , p, size, &start, &full_size, &mask);
  if (mi_commit_mask_is_empty(&mask) || full_size == 0) return 1;

  if (!mi_commit_mask_all_set(&segment->commit_mask, &mask)) {

    bool is_zero = 0;
    mi_commit_mask_t cmask;
    mi_commit_mask_create_intersect(&segment->commit_mask, &mask, &cmask);
    _mi_stat_decrease(&_mi_stats_main.committed, _mi_commit_mask_committed_size(&cmask, (1UL<<( 9 + (13 + (3))))));
    if (!_mi_os_commit(start, full_size, &is_zero)) return 0;
    mi_commit_mask_set(&segment->commit_mask, &mask);
  }


  if (mi_commit_mask_any_set(&segment->purge_mask, &mask)) {
    segment->purge_expire = _mi_clock_now() + mi_option_get(mi_option_purge_delay);
  }


  mi_commit_mask_clear(&segment->purge_mask, &mask);
  return 1;
}

static bool mi_segment_ensure_committed(mi_segment_t* segment, uint8_t* p, size_t size) {
  ((mi_commit_mask_all_set(&segment->commit_mask, &segment->purge_mask)) ? (void)0 : _mi_assert_fail("mi_commit_mask_all_set(&segment->commit_mask, &segment->purge_mask)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",518,__func__));

  if (mi_commit_mask_is_full(&segment->commit_mask) && mi_commit_mask_is_empty(&segment->purge_mask)) return 1;
  ((segment->kind != MI_SEGMENT_HUGE) ? (void)0 : _mi_assert_fail("segment->kind != MI_SEGMENT_HUGE","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",521,__func__));
  return mi_segment_commit(segment, p, size);
}

static bool mi_segment_purge(mi_segment_t* segment, uint8_t* p, size_t size) {
  ((mi_commit_mask_all_set(&segment->commit_mask, &segment->purge_mask)) ? (void)0 : _mi_assert_fail("mi_commit_mask_all_set(&segment->commit_mask, &segment->purge_mask)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",526,__func__));
  if (!segment->allow_purge) return 1;


  uint8_t* start = 0;
  size_t full_size = 0;
  mi_commit_mask_t mask;
  mi_segment_commit_mask(segment, 1 , p, size, &start, &full_size, &mask);
  if (mi_commit_mask_is_empty(&mask) || full_size==0) return 1;

  if (mi_commit_mask_any_set(&segment->commit_mask, &mask)) {

    (((void*)start != (void*)segment) ? (void)0 : _mi_assert_fail("(void*)start != (void*)segment","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",538,__func__));
    ((segment->allow_decommit) ? (void)0 : _mi_assert_fail("segment->allow_decommit","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",539,__func__));
    const bool decommitted = _mi_os_purge(start, full_size);
    if (decommitted) {
      mi_commit_mask_t cmask;
      mi_commit_mask_create_intersect(&segment->commit_mask, &mask, &cmask);
      _mi_stat_increase(&_mi_stats_main.committed, full_size - _mi_commit_mask_committed_size(&cmask, (1UL<<( 9 + (13 + (3))))));
      mi_commit_mask_clear(&segment->commit_mask, &mask);
    }
  }


  mi_commit_mask_clear(&segment->purge_mask, &mask);
  return 1;
}

static void mi_segment_schedule_purge(mi_segment_t* segment, uint8_t* p, size_t size) {
  if (!segment->allow_purge) return;

  if (mi_option_get(mi_option_purge_delay) == 0) {
    mi_segment_purge(segment, p, size);
  }
  else {

    uint8_t* start = 0;
    size_t full_size = 0;
    mi_commit_mask_t mask;
    mi_segment_commit_mask(segment, 1 , p, size, &start, &full_size, &mask);
    if (mi_commit_mask_is_empty(&mask) || full_size==0) return;


    ((segment->purge_expire > 0 || mi_commit_mask_is_empty(&segment->purge_mask)) ? (void)0 : _mi_assert_fail("segment->purge_expire > 0 || mi_commit_mask_is_empty(&segment->purge_mask)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",569,__func__));
    mi_commit_mask_t cmask;
    mi_commit_mask_create_intersect(&segment->commit_mask, &mask, &cmask);
    mi_commit_mask_set(&segment->purge_mask, &cmask);
    mi_msecs_t now = _mi_clock_now();
    if (segment->purge_expire == 0) {

      segment->purge_expire = now + mi_option_get(mi_option_purge_delay);
    }
    else if (segment->purge_expire <= now) {

      if (segment->purge_expire + mi_option_get(mi_option_purge_extend_delay) <= now) {
        mi_segment_try_purge(segment, 1);
      }
      else {
        segment->purge_expire = now + mi_option_get(mi_option_purge_extend_delay);
      }
    }
    else {

      segment->purge_expire += mi_option_get(mi_option_purge_extend_delay);
    }
  }
}

static void mi_segment_try_purge(mi_segment_t* segment, bool force) {
  if (!segment->allow_purge || segment->purge_expire == 0 || mi_commit_mask_is_empty(&segment->purge_mask)) return;
  mi_msecs_t now = _mi_clock_now();
  if (!force && now < segment->purge_expire) return;

  mi_commit_mask_t mask = segment->purge_mask;
  segment->purge_expire = 0;
  mi_commit_mask_create_empty(&segment->purge_mask);

  size_t idx;
  size_t count;
  idx = 0; while ((count = _mi_commit_mask_next_run(&mask,&idx)) > 0) { {

    if (count > 0) {
      uint8_t* p = (uint8_t*)segment + (idx*((1UL<< (13 + (3)))));
      size_t size = count * ((1UL<< (13 + (3))));
      mi_segment_purge(segment, p, size);
    }
  }
  idx += count; }
  ((mi_commit_mask_is_empty(&segment->purge_mask)) ? (void)0 : _mi_assert_fail("mi_commit_mask_is_empty(&segment->purge_mask)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",614,__func__));
}



void _mi_segment_collect(mi_segment_t* segment, bool force) {
  mi_segment_try_purge(segment, force);
}





static bool mi_segment_is_abandoned(mi_segment_t* segment) {
  return (atomic_load_explicit(&segment->thread_id,memory_order_relaxed) == 0);
}


static void mi_segment_span_free(mi_segment_t* segment, size_t slice_index, size_t slice_count, bool allow_purge, mi_segments_tld_t* tld) {
  ((slice_index < segment->slice_entries) ? (void)0 : _mi_assert_fail("slice_index < segment->slice_entries","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",633,__func__));
  mi_span_queue_t* sq = (segment->kind == MI_SEGMENT_HUGE || mi_segment_is_abandoned(segment)
                          ? 0 : mi_span_queue_for(slice_count,tld));
  if (slice_count==0) slice_count = 1;
  ((slice_index + slice_count - 1 < segment->slice_entries) ? (void)0 : _mi_assert_fail("slice_index + slice_count - 1 < segment->slice_entries","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",637,__func__));


  mi_slice_t* slice = &segment->slices[slice_index];
  slice->slice_count = (uint32_t)slice_count;
  ((slice->slice_count == slice_count) ? (void)0 : _mi_assert_fail("slice->slice_count == slice_count","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",642,__func__));
  slice->slice_offset = 0;
  if (slice_count > 1) {
    mi_slice_t* last = slice + slice_count - 1;
    mi_slice_t* end = (mi_slice_t*)mi_segment_slices_end(segment);
    if (last > end) { last = end; }
    last->slice_count = 0;
    last->slice_offset = (uint32_t)(sizeof(mi_page_t)*(slice_count - 1));
    last->block_size = 0;
  }


  if (allow_purge) {
    mi_segment_schedule_purge(segment, mi_slice_start(slice), slice_count * (1UL<< (13 + (3))));
  }


  if (sq != 0) mi_span_queue_push( sq, slice );
             else slice->block_size = 0;
}
# 673 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c"
static void mi_segment_span_remove_from_queue(mi_slice_t* slice, mi_segments_tld_t* tld) {
  ((slice->slice_count > 0 && slice->slice_offset==0 && slice->block_size==0) ? (void)0 : _mi_assert_fail("slice->slice_count > 0 && slice->slice_offset==0 && slice->block_size==0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",674,__func__));
  ((_mi_ptr_segment(slice)->kind != MI_SEGMENT_HUGE) ? (void)0 : _mi_assert_fail("_mi_ptr_segment(slice)->kind != MI_SEGMENT_HUGE","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",675,__func__));
  mi_span_queue_t* sq = mi_span_queue_for(slice->slice_count, tld);
  mi_span_queue_delete(sq, slice);
}


static mi_slice_t* mi_segment_span_free_coalesce(mi_slice_t* slice, mi_segments_tld_t* tld) {
  ((slice != 0 && slice->slice_count > 0 && slice->slice_offset == 0) ? (void)0 : _mi_assert_fail("slice != NULL && slice->slice_count > 0 && slice->slice_offset == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",682,__func__));
  mi_segment_t* const segment = _mi_ptr_segment(slice);


  if (segment->kind == MI_SEGMENT_HUGE) {

    (((segment->used==0 && slice->block_size==0) || segment->used == 1) ? (void)0 : _mi_assert_fail("(segment->used==0 && slice->block_size==0) || segment->used == 1","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",688,__func__));
    slice->block_size = 0;


    return slice;
  }


  const bool is_abandoned = (segment->thread_id == 0);
  size_t slice_count = slice->slice_count;
  mi_slice_t* next = slice + slice->slice_count;
  ((next <= mi_segment_slices_end(segment)) ? (void)0 : _mi_assert_fail("next <= mi_segment_slices_end(segment)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",699,__func__));
  if (next < mi_segment_slices_end(segment) && next->block_size==0) {

    ((next->slice_count > 0 && next->slice_offset==0) ? (void)0 : _mi_assert_fail("next->slice_count > 0 && next->slice_offset==0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",702,__func__));
    slice_count += next->slice_count;
    if (!is_abandoned) { mi_segment_span_remove_from_queue(next, tld); }
  }
  if (slice > segment->slices) {
    mi_slice_t* prev = mi_slice_first(slice - 1);
    ((prev >= segment->slices) ? (void)0 : _mi_assert_fail("prev >= segment->slices","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",708,__func__));
    if (prev->block_size==0) {

      ((prev->slice_count > 0 && prev->slice_offset==0) ? (void)0 : _mi_assert_fail("prev->slice_count > 0 && prev->slice_offset==0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",711,__func__));
      slice_count += prev->slice_count;
      slice->slice_count = 0;
      slice->slice_offset = (uint32_t)((uint8_t*)slice - (uint8_t*)prev);
      if (!is_abandoned) { mi_segment_span_remove_from_queue(prev, tld); }
      slice = prev;
    }
  }


  mi_segment_span_free(segment, mi_slice_index(slice), slice_count, 1, tld);
  return slice;
}
# 732 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c"
static mi_page_t* mi_segment_span_allocate(mi_segment_t* segment, size_t slice_index, size_t slice_count) {
  ((slice_index < segment->slice_entries) ? (void)0 : _mi_assert_fail("slice_index < segment->slice_entries","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",733,__func__));
  mi_slice_t* const slice = &segment->slices[slice_index];
  ((slice->block_size==0 || slice->block_size==1) ? (void)0 : _mi_assert_fail("slice->block_size==0 || slice->block_size==1","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",735,__func__));


  if (!mi_segment_ensure_committed(segment, _mi_segment_page_start_from_slice(segment, slice, 0, 0), slice_count * (1UL<< (13 + (3))))) {
    return 0;
  }


  slice->slice_offset = 0;
  slice->slice_count = (uint32_t)slice_count;
  ((slice->slice_count == slice_count) ? (void)0 : _mi_assert_fail("slice->slice_count == slice_count","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",745,__func__));
  const size_t bsize = slice_count * (1UL<< (13 + (3)));
  slice->block_size = bsize;
  mi_page_t* page = mi_slice_to_page(slice);
  ((mi_page_block_size(page) == bsize) ? (void)0 : _mi_assert_fail("mi_page_block_size(page) == bsize","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",749,__func__));


  size_t extra = slice_count-1;
  if (extra > ((((1UL<<( 9 + (13 + (3)))) >> 1) / (1UL<< (13 + (3)))) - 1)) extra = ((((1UL<<( 9 + (13 + (3)))) >> 1) / (1UL<< (13 + (3)))) - 1);
  if (slice_index + extra >= segment->slice_entries) extra = segment->slice_entries - slice_index - 1;

  mi_slice_t* slice_next = slice + 1;
  for (size_t i = 1; i <= extra; i++, slice_next++) {
    slice_next->slice_offset = (uint32_t)(sizeof(mi_slice_t)*i);
    slice_next->slice_count = 0;
    slice_next->block_size = 1;
  }



  mi_slice_t* last = slice + slice_count - 1;
  mi_slice_t* end = (mi_slice_t*)mi_segment_slices_end(segment);
  if (last > end) last = end;
  if (last > slice) {
    last->slice_offset = (uint32_t)(sizeof(mi_slice_t) * (last - slice));
    last->slice_count = 0;
    last->block_size = 1;
  }


  page->is_committed = 1;
  page->is_huge = (segment->kind == MI_SEGMENT_HUGE);
  segment->used++;
  return page;
}

static void mi_segment_slice_split(mi_segment_t* segment, mi_slice_t* slice, size_t slice_count, mi_segments_tld_t* tld) {
  ((_mi_ptr_segment(slice) == segment) ? (void)0 : _mi_assert_fail("_mi_ptr_segment(slice) == segment","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",782,__func__));
  ((slice->slice_count >= slice_count) ? (void)0 : _mi_assert_fail("slice->slice_count >= slice_count","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",783,__func__));
  ((slice->block_size > 0) ? (void)0 : _mi_assert_fail("slice->block_size > 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",784,__func__));
  if (slice->slice_count <= slice_count) return;
  ((segment->kind != MI_SEGMENT_HUGE) ? (void)0 : _mi_assert_fail("segment->kind != MI_SEGMENT_HUGE","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",786,__func__));
  size_t next_index = mi_slice_index(slice) + slice_count;
  size_t next_count = slice->slice_count - slice_count;
  mi_segment_span_free(segment, next_index, next_count, 0 , tld);
  slice->slice_count = (uint32_t)slice_count;
}

static mi_page_t* mi_segments_page_find_and_allocate(size_t slice_count, mi_arena_id_t req_arena_id, mi_segments_tld_t* tld) {
  ((slice_count*(1UL<< (13 + (3))) <= ((1UL<<( 9 + (13 + (3))))/2)) ? (void)0 : _mi_assert_fail("slice_count*MI_SEGMENT_SLICE_SIZE <= MI_LARGE_OBJ_SIZE_MAX","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",794,__func__));

  mi_span_queue_t* sq = mi_span_queue_for(slice_count, tld);
  if (slice_count == 0) slice_count = 1;
  while (sq <= &tld->spans[(35)]) {
    for (mi_slice_t* slice = sq->first; slice != 0; slice = slice->next) {
      if (slice->slice_count >= slice_count) {

        mi_segment_t* segment = _mi_ptr_segment(slice);
        if (_mi_arena_memid_is_suitable(segment->memid, req_arena_id)) {

          mi_span_queue_delete(sq, slice);

          if (slice->slice_count > slice_count) {
            mi_segment_slice_split(segment, slice, slice_count, tld);
          }
          ((slice != 0 && slice->slice_count == slice_count && slice->block_size > 0) ? (void)0 : _mi_assert_fail("slice != NULL && slice->slice_count == slice_count && slice->block_size > 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",810,__func__));
          mi_page_t* page = mi_segment_span_allocate(segment, mi_slice_index(slice), slice->slice_count);
          if (page == 0) {

            mi_segment_span_free_coalesce(slice, tld);
            return 0;
          }
          return page;
        }
      }
    }
    sq++;
  }

  return 0;
}






static mi_segment_t* mi_segment_os_alloc( size_t required, size_t page_alignment, bool eager_delayed, mi_arena_id_t req_arena_id,
                                          size_t* psegment_slices, size_t* pinfo_slices,
                                          bool commit, mi_segments_tld_t* tld)

{
  mi_memid_t memid;
  bool allow_large = (!eager_delayed && (0 == 0));
  size_t align_offset = 0;
  size_t alignment = (1UL<<( 9 + (13 + (3))));

  if (page_alignment > 0) {

    ((page_alignment >= (1UL<<( 9 + (13 + (3))))) ? (void)0 : _mi_assert_fail("page_alignment >= MI_SEGMENT_ALIGN","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",844,__func__));
    alignment = page_alignment;
    const size_t info_size = (*pinfo_slices) * (1UL<< (13 + (3)));
    align_offset = _mi_align_up( info_size, (1UL<<( 9 + (13 + (3)))) );
    const size_t extra = align_offset - info_size;

    *psegment_slices = mi_segment_calculate_slices(required + extra, pinfo_slices);
    ((*psegment_slices > 0 && *psegment_slices <= UINT32_MAX) ? (void)0 : _mi_assert_fail("*psegment_slices > 0 && *psegment_slices <= UINT32_MAX","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",851,__func__));
  }

  const size_t segment_size = (*psegment_slices) * (1UL<< (13 + (3)));
  mi_segment_t* segment = (mi_segment_t*)_mi_arena_alloc_aligned(segment_size, alignment, align_offset, commit, allow_large, req_arena_id, &memid);
  if (segment == 0) {
    return 0;
  }


  mi_commit_mask_t commit_mask;
  if (memid.initially_committed) {
    mi_commit_mask_create_full(&commit_mask);
  }
  else {

    const size_t commit_needed = _mi_divide_up((*pinfo_slices)*(1UL<< (13 + (3))), ((1UL<< (13 + (3)))));
    ((commit_needed>0) ? (void)0 : _mi_assert_fail("commit_needed>0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",868,__func__));
    mi_commit_mask_create(0, commit_needed, &commit_mask);
    ((commit_needed*((1UL<< (13 + (3)))) >= (*pinfo_slices)*(1UL<< (13 + (3)))) ? (void)0 : _mi_assert_fail("commit_needed*MI_COMMIT_SIZE >= (*pinfo_slices)*MI_SEGMENT_SLICE_SIZE","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",870,__func__));
    if (!_mi_os_commit(segment, commit_needed*((1UL<< (13 + (3)))), 0)) {
      _mi_arena_free(segment,segment_size,0,memid);
      return 0;
    }
  }
  ((segment != 0 && (uintptr_t)segment % (1UL<<( 9 + (13 + (3)))) == 0) ? (void)0 : _mi_assert_fail("segment != NULL && (uintptr_t)segment % MI_SEGMENT_SIZE == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",876,__func__));

  segment->memid = memid;
  segment->allow_decommit = !memid.is_pinned;
  segment->allow_purge = segment->allow_decommit && (mi_option_get(mi_option_purge_delay) >= 0);
  segment->segment_size = segment_size;
  segment->subproc = tld->subproc;
  segment->commit_mask = commit_mask;
  segment->purge_expire = 0;
  mi_commit_mask_create_empty(&segment->purge_mask);

  mi_segments_track_size((long)(segment_size), tld);
  _mi_segment_map_allocated_at(segment);
  return segment;
}



static mi_segment_t* mi_segment_alloc(size_t required, size_t page_alignment, mi_arena_id_t req_arena_id, mi_segments_tld_t* tld, mi_page_t** huge_page)
{
  (((required==0 && huge_page==0) || (required>0 && huge_page != 0)) ? (void)0 : _mi_assert_fail("(required==0 && huge_page==NULL) || (required>0 && huge_page != NULL)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",896,__func__));


  size_t info_slices;
  size_t segment_slices = mi_segment_calculate_slices(required, &info_slices);
  ((segment_slices > 0 && segment_slices <= UINT32_MAX) ? (void)0 : _mi_assert_fail("segment_slices > 0 && segment_slices <= UINT32_MAX","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",901,__func__));


  const bool eager_delay = (
                            _mi_current_thread_count() > 1 &&
                            tld->peak_count < (size_t)mi_option_get(mi_option_eager_commit_delay));
  const bool eager = !eager_delay && mi_option_is_enabled(mi_option_eager_commit);
  bool commit = eager || (required > 0);


  mi_segment_t* segment = mi_segment_os_alloc(required, page_alignment, eager_delay, req_arena_id,
                                              &segment_slices, &info_slices, commit, tld);
  if (segment == 0) return 0;


  if (!segment->memid.initially_zero) {
    ptrdiff_t ofs = offsetof(mi_segment_t, next);
    size_t prefix = offsetof(mi_segment_t, slices) - ofs;
    size_t zsize = prefix + (sizeof(mi_slice_t) * (segment_slices + 1));
    _mi_memzero((uint8_t*)segment + ofs, zsize);
  }


  const size_t slice_entries = (segment_slices > ((1UL<<( 9 + (13 + (3)))) / (1UL<< (13 + (3)))) ? ((1UL<<( 9 + (13 + (3)))) / (1UL<< (13 + (3)))) : segment_slices);
  segment->segment_slices = segment_slices;
  segment->segment_info_slices = info_slices;
  segment->thread_id = _mi_thread_id();
  segment->cookie = _mi_ptr_cookie(segment);
  segment->slice_entries = slice_entries;
  segment->kind = (required == 0 ? MI_SEGMENT_NORMAL : MI_SEGMENT_HUGE);


  _mi_stat_increase(&tld->stats->page_committed, mi_segment_info_size(segment));


  size_t guard_slices = 0;
  if (0>0) {


    size_t os_pagesize = _mi_os_page_size();
    _mi_os_protect((uint8_t*)segment + mi_segment_info_size(segment) - os_pagesize, os_pagesize);
    uint8_t* end = (uint8_t*)segment + mi_segment_size(segment) - os_pagesize;
    mi_segment_ensure_committed(segment, end, os_pagesize);
    _mi_os_protect(end, os_pagesize);
    if (slice_entries == segment_slices) segment->slice_entries--;
    guard_slices = 1;
  }


  mi_page_t* page0 = mi_segment_span_allocate(segment, 0, info_slices);
  ((page0!=0) ? (void)0 : _mi_assert_fail("page0!=NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",951,__func__)); if (page0==0) return 0;
  ((segment->used == 1) ? (void)0 : _mi_assert_fail("segment->used == 1","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",952,__func__));
  segment->used = 0;


  if (segment->kind == MI_SEGMENT_NORMAL) {
    ((huge_page==0) ? (void)0 : _mi_assert_fail("huge_page==NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",957,__func__));
    mi_segment_span_free(segment, info_slices, segment->slice_entries - info_slices, 0 , tld);
  }
  else {
    ((huge_page!=0) ? (void)0 : _mi_assert_fail("huge_page!=NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",961,__func__));
    ((mi_commit_mask_is_empty(&segment->purge_mask)) ? (void)0 : _mi_assert_fail("mi_commit_mask_is_empty(&segment->purge_mask)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",962,__func__));
    ((mi_commit_mask_is_full(&segment->commit_mask)) ? (void)0 : _mi_assert_fail("mi_commit_mask_is_full(&segment->commit_mask)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",963,__func__));
    *huge_page = mi_segment_span_allocate(segment, info_slices, segment_slices - info_slices - guard_slices);
    ((*huge_page != 0) ? (void)0 : _mi_assert_fail("*huge_page != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",965,__func__));
  }

  ;
  return segment;
}


static void mi_segment_free(mi_segment_t* segment, bool force, mi_segments_tld_t* tld) {
  (void)(force);
  ((segment != 0) ? (void)0 : _mi_assert_fail("segment != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",975,__func__));
  ((segment->next == 0) ? (void)0 : _mi_assert_fail("segment->next == NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",976,__func__));
  ((segment->used == 0) ? (void)0 : _mi_assert_fail("segment->used == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",977,__func__));


  if (segment->dont_free) return;


  mi_slice_t* slice = &segment->slices[0];
  const mi_slice_t* end = mi_segment_slices_end(segment);

  size_t page_count = 0;

  while (slice < end) {
    ((slice->slice_count > 0) ? (void)0 : _mi_assert_fail("slice->slice_count > 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",989,__func__));
    ((slice->slice_offset == 0) ? (void)0 : _mi_assert_fail("slice->slice_offset == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",990,__func__));
    ((mi_slice_index(slice)==0 || slice->block_size == 0) ? (void)0 : _mi_assert_fail("mi_slice_index(slice)==0 || slice->block_size == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",991,__func__));
    if (slice->block_size == 0 && segment->kind != MI_SEGMENT_HUGE) {
      mi_segment_span_remove_from_queue(slice, tld);
    }

    page_count++;

    slice = slice + slice->slice_count;
  }
  ((page_count == 2) ? (void)0 : _mi_assert_fail("page_count == 2","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1000,__func__));





  mi_segment_os_free(segment, tld);
}






static void mi_segment_abandon(mi_segment_t* segment, mi_segments_tld_t* tld);


static mi_slice_t* mi_segment_page_clear(mi_page_t* page, mi_segments_tld_t* tld) {
  ((page->block_size > 0) ? (void)0 : _mi_assert_fail("page->block_size > 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1018,__func__));
  ((mi_page_all_free(page)) ? (void)0 : _mi_assert_fail("mi_page_all_free(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1019,__func__));
  mi_segment_t* segment = _mi_ptr_segment(page);
  ((segment->used > 0) ? (void)0 : _mi_assert_fail("segment->used > 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1021,__func__));

  size_t inuse = page->capacity * mi_page_block_size(page);
  _mi_stat_decrease(&tld->stats->page_committed, inuse);
  _mi_stat_decrease(&tld->stats->pages, 1);
  _mi_stat_decrease(&tld->stats->page_bins[_mi_page_bin(page)], 1);


  if (segment->allow_decommit && mi_option_is_enabled(mi_option_deprecated_page_reset)) {
    size_t psize;
    uint8_t* start = _mi_segment_page_start(segment, page, &psize);
    _mi_os_reset(start, psize);
  }


  page->is_zero_init = 0;
  uint8_t heap_tag = page->heap_tag;
  ptrdiff_t ofs = offsetof(mi_page_t, capacity);
  _mi_memzero((uint8_t*)page + ofs, sizeof(*page) - ofs);
  page->block_size = 1;
  page->heap_tag = heap_tag;


  mi_slice_t* slice = mi_segment_span_free_coalesce(mi_page_to_slice(page), tld);
  segment->used--;


  return slice;
}

void _mi_segment_page_free(mi_page_t* page, bool force, mi_segments_tld_t* tld)
{
  ((page != 0) ? (void)0 : _mi_assert_fail("page != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1053,__func__));
  mi_segment_t* segment = _mi_page_segment(page);
  ;


  mi_segment_page_clear(page, tld);
  ;

  if (segment->used == 0) {

    mi_segment_free(segment, force, tld);
  }
  else if (segment->used == segment->abandoned) {

    mi_segment_abandon(segment,tld);
  }
  else {

    mi_segment_try_purge(segment, 0 );
  }
}
# 1098 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c"
static void mi_segment_abandon(mi_segment_t* segment, mi_segments_tld_t* tld) {
  ((segment->used == segment->abandoned) ? (void)0 : _mi_assert_fail("segment->used == segment->abandoned","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1099,__func__));
  ((segment->used > 0) ? (void)0 : _mi_assert_fail("segment->used > 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1100,__func__));
  ((segment->abandoned_visits == 0) ? (void)0 : _mi_assert_fail("segment->abandoned_visits == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1101,__func__));
  ;


  mi_slice_t* slice = &segment->slices[0];
  const mi_slice_t* end = mi_segment_slices_end(segment);
  while (slice < end) {
    ((slice->slice_count > 0) ? (void)0 : _mi_assert_fail("slice->slice_count > 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1108,__func__));
    ((slice->slice_offset == 0) ? (void)0 : _mi_assert_fail("slice->slice_offset == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1109,__func__));
    if (slice->block_size == 0) {
      mi_segment_span_remove_from_queue(slice,tld);
      slice->block_size = 0;
    }
    slice = slice + slice->slice_count;
  }




  const bool force_purge = (segment->memid.memkind != MI_MEM_ARENA) || mi_option_is_enabled(mi_option_abandoned_page_purge);
  mi_segment_try_purge(segment, force_purge);


  _mi_stat_increase(&tld->stats->segments_abandoned, 1);
  mi_segments_track_size(-((long)mi_segment_size(segment)), tld);
  segment->thread_id = 0;
  segment->abandoned_visits = 1;
  if (segment->was_reclaimed) {
    tld->reclaim_count--;
    segment->was_reclaimed = 0;
  }
  _mi_arena_segment_mark_abandoned(segment);
}

void _mi_segment_page_abandon(mi_page_t* page, mi_segments_tld_t* tld) {
  ((page != 0) ? (void)0 : _mi_assert_fail("page != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1136,__func__));
  ((mi_page_thread_free_flag(page)==MI_NEVER_DELAYED_FREE) ? (void)0 : _mi_assert_fail("mi_page_thread_free_flag(page)==MI_NEVER_DELAYED_FREE","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1137,__func__));
  ((mi_page_heap(page) == 0) ? (void)0 : _mi_assert_fail("mi_page_heap(page) == NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1138,__func__));
  mi_segment_t* segment = _mi_page_segment(page);

  ;
  segment->abandoned++;

  _mi_stat_increase(&tld->stats->pages_abandoned, 1);
  ((segment->abandoned <= segment->used) ? (void)0 : _mi_assert_fail("segment->abandoned <= segment->used","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1145,__func__));
  if (segment->used == segment->abandoned) {

    mi_segment_abandon(segment, tld);
  }
}





static mi_slice_t* mi_slices_start_iterate(mi_segment_t* segment, const mi_slice_t** end) {
  mi_slice_t* slice = &segment->slices[0];
  *end = mi_segment_slices_end(segment);
  ((slice->slice_count>0 && slice->block_size>0) ? (void)0 : _mi_assert_fail("slice->slice_count>0 && slice->block_size>0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1159,__func__));
  slice = slice + slice->slice_count;
  return slice;
}


static bool mi_segment_check_free(mi_segment_t* segment, size_t slices_needed, size_t block_size, mi_segments_tld_t* tld)
{
  ((mi_segment_is_abandoned(segment)) ? (void)0 : _mi_assert_fail("mi_segment_is_abandoned(segment)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1167,__func__));
  bool has_page = 0;


  const mi_slice_t* end;
  mi_slice_t* slice = mi_slices_start_iterate(segment, &end);
  while (slice < end) {
    ((slice->slice_count > 0) ? (void)0 : _mi_assert_fail("slice->slice_count > 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1174,__func__));
    ((slice->slice_offset == 0) ? (void)0 : _mi_assert_fail("slice->slice_offset == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1175,__func__));
    if (mi_slice_is_used(slice)) {

      mi_page_t* const page = mi_slice_to_page(slice);
      _mi_page_free_collect(page, 0);
      if (mi_page_all_free(page)) {

        ((page->next == 0 && page->prev==0) ? (void)0 : _mi_assert_fail("page->next == NULL && page->prev==NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1182,__func__));
        _mi_stat_decrease(&tld->stats->pages_abandoned, 1);
        segment->abandoned--;
        slice = mi_segment_page_clear(page, tld);
        ((!mi_slice_is_used(slice)) ? (void)0 : _mi_assert_fail("!mi_slice_is_used(slice)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1186,__func__));
        if (slice->slice_count >= slices_needed) {
          has_page = 1;
        }
      }
      else if (mi_page_block_size(page) == block_size && mi_page_has_any_available(page)) {

        has_page = 1;
      }
    }
    else {

      if (slice->slice_count >= slices_needed) {
        has_page = 1;
      }
    }
    slice = slice + slice->slice_count;
  }
  return has_page;
}



static mi_segment_t* mi_segment_reclaim(mi_segment_t* segment, mi_heap_t* heap, size_t requested_block_size, bool* right_page_reclaimed, mi_segments_tld_t* tld) {
  if (right_page_reclaimed != 0) { *right_page_reclaimed = 0; }

  ((atomic_load_explicit(&segment->thread_id,memory_order_relaxed) == 0 || atomic_load_explicit(&segment->thread_id,memory_order_relaxed) == _mi_thread_id()) ? (void)0 : _mi_assert_fail("mi_atomic_load_relaxed(&segment->thread_id) == 0 || mi_atomic_load_relaxed(&segment->thread_id) == _mi_thread_id()","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1212,__func__));
  ((segment->subproc == heap->tld->segments.subproc) ? (void)0 : _mi_assert_fail("segment->subproc == heap->tld->segments.subproc","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1213,__func__));
  atomic_store_explicit(&segment->thread_id,_mi_thread_id(),memory_order_release);
  segment->abandoned_visits = 0;
  segment->was_reclaimed = 1;
  tld->reclaim_count++;
  mi_segments_track_size((long)mi_segment_size(segment), tld);
  ((segment->next == 0) ? (void)0 : _mi_assert_fail("segment->next == NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1219,__func__));
  _mi_stat_decrease(&tld->stats->segments_abandoned, 1);


  const mi_slice_t* end;
  mi_slice_t* slice = mi_slices_start_iterate(segment, &end);
  while (slice < end) {
    ((slice->slice_count > 0) ? (void)0 : _mi_assert_fail("slice->slice_count > 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1226,__func__));
    ((slice->slice_offset == 0) ? (void)0 : _mi_assert_fail("slice->slice_offset == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1227,__func__));
    if (mi_slice_is_used(slice)) {

      mi_page_t* page = mi_slice_to_page(slice);
      ((page->is_committed) ? (void)0 : _mi_assert_fail("page->is_committed","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1231,__func__));
      ((mi_page_thread_free_flag(page)==MI_NEVER_DELAYED_FREE) ? (void)0 : _mi_assert_fail("mi_page_thread_free_flag(page)==MI_NEVER_DELAYED_FREE","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1232,__func__));
      ((mi_page_heap(page) == 0) ? (void)0 : _mi_assert_fail("mi_page_heap(page) == NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1233,__func__));
      ((page->next == 0 && page->prev==0) ? (void)0 : _mi_assert_fail("page->next == NULL && page->prev==NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1234,__func__));
      _mi_stat_decrease(&tld->stats->pages_abandoned, 1);
      segment->abandoned--;

      mi_heap_t* target_heap = _mi_heap_by_tag(heap, page->heap_tag);
      if (target_heap == 0) {
        target_heap = heap;
        _mi_error_message((14), "page with tag %u cannot be reclaimed by a heap with the same tag (using heap tag %u instead)\n", page->heap_tag, heap->tag );
      }

      mi_page_set_heap(page, target_heap);
      _mi_page_use_delayed_free(page, MI_USE_DELAYED_FREE, 1);
      _mi_page_free_collect(page, 0);
      if (mi_page_all_free(page)) {

        slice = mi_segment_page_clear(page, tld);
      }
      else {

        _mi_page_reclaim(target_heap, page);
        if (requested_block_size == mi_page_block_size(page) && mi_page_has_any_available(page) && heap == target_heap) {
          if (right_page_reclaimed != 0) { *right_page_reclaimed = 1; }
        }
      }
    }
    else {

      slice = mi_segment_span_free_coalesce(slice, tld);
    }
    ((slice->slice_count>0 && slice->slice_offset==0) ? (void)0 : _mi_assert_fail("slice->slice_count>0 && slice->slice_offset==0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1263,__func__));
    slice = slice + slice->slice_count;
  }

  ((segment->abandoned == 0) ? (void)0 : _mi_assert_fail("segment->abandoned == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1267,__func__));
  ;
  if (segment->used == 0) {
    ((right_page_reclaimed == 0 || !(*right_page_reclaimed)) ? (void)0 : _mi_assert_fail("right_page_reclaimed == NULL || !(*right_page_reclaimed)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1270,__func__));
    mi_segment_free(segment, 0, tld);
    return 0;
  }
  else {
    return segment;
  }
}



bool _mi_segment_attempt_reclaim(mi_heap_t* heap, mi_segment_t* segment) {
  if (atomic_load_explicit(&segment->thread_id,memory_order_relaxed) != 0) return 0;
  if (segment->subproc != heap->tld->segments.subproc) return 0;
  if (!_mi_heap_memid_is_suitable(heap,segment->memid)) return 0;
  const long target = _mi_option_get_fast(mi_option_target_segments_per_thread);
  if (target > 0 && (size_t)target <= heap->tld->segments.count) return 0;




  if (segment->memid.memkind == MI_MEM_ARENA && heap->tld->segments.reclaim_count * 2 > heap->tld->segments.count) {
    return 0;
  }
  if (_mi_arena_segment_clear_abandoned(segment)) {
    mi_segment_t* res = mi_segment_reclaim(segment, heap, 0, 0, &heap->tld->segments);
    ((res == segment) ? (void)0 : _mi_assert_fail("res == segment","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1296,__func__));
    return (res != 0);
  }
  return 0;
}

void _mi_abandoned_reclaim_all(mi_heap_t* heap, mi_segments_tld_t* tld) {
  mi_segment_t* segment;
  mi_arena_field_cursor_t current;
  _mi_arena_field_cursor_init(heap, tld->subproc, 1 , &current);
  while ((segment = _mi_arena_segment_clear_abandoned_next(&current)) != 0) {
    mi_segment_reclaim(segment, heap, 0, 0, tld);
  }
  _mi_arena_field_cursor_done(&current);
}


static bool segment_count_is_within_target(mi_segments_tld_t* tld, size_t* ptarget) {
  const size_t target = (size_t)mi_option_get_clamp(mi_option_target_segments_per_thread, 0, 1024);
  if (ptarget != 0) { *ptarget = target; }
  return (target == 0 || tld->count < target);
}

static long mi_segment_get_reclaim_tries(mi_segments_tld_t* tld) {

  const size_t perc = (size_t)mi_option_get_clamp(mi_option_max_segment_reclaim, 0, 100);
  if (perc <= 0) return 0;
  const size_t total_count = atomic_load_explicit(&tld->subproc->abandoned_count,memory_order_relaxed);
  if (total_count == 0) return 0;
  const size_t relative_count = (total_count > 10000 ? (total_count / 100) * perc : (total_count * perc) / 100);
  long max_tries = (long)(relative_count <= 1 ? 1 : (relative_count > 1024 ? 1024 : relative_count));
  if (max_tries < 8 && total_count > 8) { max_tries = 8; }
  return max_tries;
}

static mi_segment_t* mi_segment_try_reclaim(mi_heap_t* heap, size_t needed_slices, size_t block_size, bool* reclaimed, mi_segments_tld_t* tld)
{
  *reclaimed = 0;
  long max_tries = mi_segment_get_reclaim_tries(tld);
  if (max_tries <= 0) return 0;

  mi_segment_t* result = 0;
  mi_segment_t* segment = 0;
  mi_arena_field_cursor_t current;
  _mi_arena_field_cursor_init(heap, tld->subproc, 0 , &current);
  while (segment_count_is_within_target(tld,0) && (max_tries-- > 0) && ((segment = _mi_arena_segment_clear_abandoned_next(&current)) != 0))
  {
    ((segment->subproc == heap->tld->segments.subproc) ? (void)0 : _mi_assert_fail("segment->subproc == heap->tld->segments.subproc","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1343,__func__));
    segment->abandoned_visits++;



    bool is_suitable = _mi_heap_memid_is_suitable(heap, segment->memid);
    bool has_page = mi_segment_check_free(segment,needed_slices,block_size,tld);
    if (segment->used == 0) {





      mi_segment_reclaim(segment, heap, 0, 0, tld);
    }
    else if (has_page && is_suitable) {



      result = mi_segment_reclaim(segment, heap, block_size, reclaimed, tld);
      break;
    }
    else if (segment->abandoned_visits > 3 && is_suitable) {

      mi_segment_reclaim(segment, heap, 0, 0, tld);
    }
    else {

      max_tries++;
      mi_segment_try_purge(segment, 0 );
      _mi_arena_segment_mark_abandoned(segment);
    }
  }
  _mi_arena_field_cursor_done(&current);
  return result;
}


void _mi_abandoned_collect(mi_heap_t* heap, bool force, mi_segments_tld_t* tld)
{
  mi_segment_t* segment;
  mi_arena_field_cursor_t current; _mi_arena_field_cursor_init(heap, tld->subproc, force , &current);
  long max_tries = (force ? (long)atomic_load_explicit(&tld->subproc->abandoned_count,memory_order_relaxed) : 1024);
  while ((max_tries-- > 0) && ((segment = _mi_arena_segment_clear_abandoned_next(&current)) != 0)) {
    mi_segment_check_free(segment,0,0,tld);
    if (segment->used == 0) {



      mi_segment_reclaim(segment, heap, 0, 0, tld);
    }
    else {


      mi_segment_try_purge(segment, force);
      _mi_arena_segment_mark_abandoned(segment);
    }
  }
  _mi_arena_field_cursor_done(&current);
}






static void mi_segment_force_abandon(mi_segment_t* segment, mi_segments_tld_t* tld)
{
  ((!mi_segment_is_abandoned(segment)) ? (void)0 : _mi_assert_fail("!mi_segment_is_abandoned(segment)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1411,__func__));
  ((!segment->dont_free) ? (void)0 : _mi_assert_fail("!segment->dont_free","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1412,__func__));


  segment->dont_free = 1;


  const mi_slice_t* end;
  mi_slice_t* slice = mi_slices_start_iterate(segment, &end);
  while (slice < end) {
    ((slice->slice_count > 0) ? (void)0 : _mi_assert_fail("slice->slice_count > 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1421,__func__));
    ((slice->slice_offset == 0) ? (void)0 : _mi_assert_fail("slice->slice_offset == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1422,__func__));
    if (mi_slice_is_used(slice)) {

      mi_page_t* const page = mi_slice_to_page(slice);
      _mi_page_free_collect(page, 0);
      {

        ((segment->used > 0) ? (void)0 : _mi_assert_fail("segment->used > 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1429,__func__));
        if (segment->used == segment->abandoned+1) {


          segment->dont_free = 0;
          _mi_page_force_abandon(page);
          return;
        }
        else {

          _mi_page_force_abandon(page);

          slice = mi_slice_first(slice);
        }
      }
    }
    slice = slice + slice->slice_count;
  }
  segment->dont_free = 0;
  ((segment->used == segment->abandoned) ? (void)0 : _mi_assert_fail("segment->used == segment->abandoned","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1448,__func__));
  ((segment->used == 0) ? (void)0 : _mi_assert_fail("segment->used == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1449,__func__));
  if (segment->used == 0) {

    mi_segment_free(segment, 0, tld);
  }
  else {

    mi_segment_try_purge(segment, 0 );
  }
}




static void mi_segments_try_abandon_to_target(mi_heap_t* heap, size_t target, mi_segments_tld_t* tld) {
  if (target <= 1) return;
  const size_t min_target = (target > 4 ? (target*3)/4 : target);

  for (int i = 0; i < 64 && tld->count >= min_target; i++) {
    mi_page_t* page = heap->pages[((73U)+1)].first;
    while (page != 0 && mi_page_block_size(page) > ((1UL<<( 9 + (13 + (3))))/2)) {
      page = page->next;
    }
    if (page==0) {
      break;
    }
    mi_segment_t* segment = _mi_page_segment(page);
    mi_segment_force_abandon(segment, tld);
    ((page != heap->pages[((73U)+1)].first) ? (void)0 : _mi_assert_fail("page != heap->pages[MI_BIN_FULL].first","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1477,__func__));
  }
}



static void mi_segments_try_abandon(mi_heap_t* heap, mi_segments_tld_t* tld) {

  size_t target = 0;
  if (segment_count_is_within_target(tld, &target)) return;
  mi_segments_try_abandon_to_target(heap, target, tld);
}

void mi_collect_reduce(size_t target_size) {
  mi_collect(1);
  mi_heap_t* heap = mi_heap_get_default();
  mi_segments_tld_t* tld = &heap->tld->segments;
  size_t target = target_size / (1UL<<( 9 + (13 + (3))));
  if (target == 0) {
    target = (size_t)mi_option_get_clamp(mi_option_target_segments_per_thread, 1, 1024);
  }
  mi_segments_try_abandon_to_target(heap, target, tld);
}





static mi_segment_t* mi_segment_reclaim_or_alloc(mi_heap_t* heap, size_t needed_slices, size_t block_size, mi_segments_tld_t* tld)
{
  ((block_size <= ((1UL<<( 9 + (13 + (3))))/2)) ? (void)0 : _mi_assert_fail("block_size <= MI_LARGE_OBJ_SIZE_MAX","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1507,__func__));


  mi_segments_try_abandon(heap,tld);


  bool reclaimed;
  mi_segment_t* segment = mi_segment_try_reclaim(heap, needed_slices, block_size, &reclaimed, tld);
  if (reclaimed) {

    ((segment != 0) ? (void)0 : _mi_assert_fail("segment != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1517,__func__));
    return 0;
  }
  else if (segment != 0) {

    return segment;
  }

  return mi_segment_alloc(0, 0, heap->arena_id, tld, 0);
}






static mi_page_t* mi_segments_page_alloc(mi_heap_t* heap, mi_page_kind_t page_kind, size_t required, size_t block_size, mi_segments_tld_t* tld)
{
  ((required <= ((1UL<<( 9 + (13 + (3))))/2) && page_kind <= MI_PAGE_LARGE) ? (void)0 : _mi_assert_fail("required <= MI_LARGE_OBJ_SIZE_MAX && page_kind <= MI_PAGE_LARGE","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1535,__func__));


  size_t page_size = _mi_align_up(required, (required > (1UL<<( 3 + ((13 + (3))))) ? (1UL<<( 3 + ((13 + (3))))) : (1UL<< (13 + (3)))));
  size_t slices_needed = page_size / (1UL<< (13 + (3)));
  ((slices_needed * (1UL<< (13 + (3))) == page_size) ? (void)0 : _mi_assert_fail("slices_needed * MI_SEGMENT_SLICE_SIZE == page_size","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1540,__func__));
  mi_page_t* page = mi_segments_page_find_and_allocate(slices_needed, heap->arena_id, tld);
  if (page==0) {

    if (mi_segment_reclaim_or_alloc(heap, slices_needed, block_size, tld) == 0) {

      return 0;
    }
    else {

      return mi_segments_page_alloc(heap, page_kind, required, block_size, tld);
    }
  }
  ((page != 0 && page->slice_count*(1UL<< (13 + (3))) == page_size) ? (void)0 : _mi_assert_fail("page != NULL && page->slice_count*MI_SEGMENT_SLICE_SIZE == page_size","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1553,__func__));
  ((_mi_ptr_segment(page)->thread_id == _mi_thread_id()) ? (void)0 : _mi_assert_fail("_mi_ptr_segment(page)->thread_id == _mi_thread_id()","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1554,__func__));
  mi_segment_try_purge(_mi_ptr_segment(page), 0);
  return page;
}







static mi_page_t* mi_segment_huge_page_alloc(size_t size, size_t page_alignment, mi_arena_id_t req_arena_id, mi_segments_tld_t* tld)
{
  mi_page_t* page = 0;
  mi_segment_t* segment = mi_segment_alloc(size,page_alignment,req_arena_id,tld,&page);
  if (segment == 0 || page==0) return 0;
  ((segment->used==1) ? (void)0 : _mi_assert_fail("segment->used==1","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1570,__func__));
  ((mi_page_block_size(page) >= size) ? (void)0 : _mi_assert_fail("mi_page_block_size(page) >= size","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1571,__func__));






  size_t psize;
  uint8_t* start = _mi_segment_page_start(segment, page, &psize);
  page->block_size = psize;
  ((page->is_huge) ? (void)0 : _mi_assert_fail("page->is_huge","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1581,__func__));


  if (page_alignment > 0 && segment->allow_decommit) {
    uint8_t* aligned_p = (uint8_t*)_mi_align_up((uintptr_t)start, page_alignment);
    ((_mi_is_aligned(aligned_p, page_alignment)) ? (void)0 : _mi_assert_fail("_mi_is_aligned(aligned_p, page_alignment)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1586,__func__));
    ((psize - (aligned_p - start) >= size) ? (void)0 : _mi_assert_fail("psize - (aligned_p - start) >= size","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1587,__func__));
    uint8_t* decommit_start = start + sizeof(mi_block_t);
    ptrdiff_t decommit_size = aligned_p - decommit_start;
    _mi_os_reset(decommit_start, decommit_size);
  }

  return page;
}
# 1626 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c"
void _mi_segment_huge_page_reset(mi_segment_t* segment, mi_page_t* page, mi_block_t* block) {
  (void)(page);
  ((segment->kind == MI_SEGMENT_HUGE) ? (void)0 : _mi_assert_fail("segment->kind == MI_SEGMENT_HUGE","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1628,__func__));
  ((segment == _mi_page_segment(page)) ? (void)0 : _mi_assert_fail("segment == _mi_page_segment(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1629,__func__));
  ((page->used == 1) ? (void)0 : _mi_assert_fail("page->used == 1","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1630,__func__));
  ((page->free == 0) ? (void)0 : _mi_assert_fail("page->free == NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1631,__func__));
  if (segment->allow_decommit) {
    size_t csize = mi_usable_size(block);
    if (csize > sizeof(mi_block_t)) {
      csize = csize - sizeof(mi_block_t);
      uint8_t* p = (uint8_t*)block + sizeof(mi_block_t);
      _mi_os_reset(p, csize);
    }
  }
}





mi_page_t* _mi_segment_page_alloc(mi_heap_t* heap, size_t block_size, size_t page_alignment, mi_segments_tld_t* tld) {
  mi_page_t* page;
  if (__builtin_expect(!!(page_alignment > ((1UL<<( 9 + (13 + (3)))) >> 1)),0)) {
    ((_mi_is_power_of_two(page_alignment)) ? (void)0 : _mi_assert_fail("_mi_is_power_of_two(page_alignment)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1649,__func__));
    ((page_alignment >= (1UL<<( 9 + (13 + (3))))) ? (void)0 : _mi_assert_fail("page_alignment >= MI_SEGMENT_SIZE","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1650,__func__));
    if (page_alignment < (1UL<<( 9 + (13 + (3))))) { page_alignment = (1UL<<( 9 + (13 + (3)))); }
    page = mi_segment_huge_page_alloc(block_size,page_alignment,heap->arena_id,tld);
  }
  else if (block_size <= ((1UL<<((13 + (3))))/8)) {
    page = mi_segments_page_alloc(heap,MI_PAGE_SMALL,block_size,block_size,tld);
  }
  else if (block_size <= ((1UL<<( 3 + ((13 + (3)))))/8)) {
    page = mi_segments_page_alloc(heap,MI_PAGE_MEDIUM,(1UL<<( 3 + ((13 + (3))))),block_size,tld);
  }
  else if (block_size <= ((1UL<<( 9 + (13 + (3))))/2)) {
    page = mi_segments_page_alloc(heap,MI_PAGE_LARGE,block_size,block_size,tld);
  }
  else {
    page = mi_segment_huge_page_alloc(block_size,page_alignment,heap->arena_id,tld);
  }
  ((page == 0 || _mi_heap_memid_is_suitable(heap, _mi_page_segment(page)->memid)) ? (void)0 : _mi_assert_fail("page == NULL || _mi_heap_memid_is_suitable(heap, _mi_page_segment(page)->memid)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1666,__func__));
  ;
  ((page == 0 || _mi_page_segment(page)->subproc == tld->subproc) ? (void)0 : _mi_assert_fail("page == NULL || _mi_page_segment(page)->subproc == tld->subproc","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/segment.c",1668,__func__));
  return page;
}






static bool mi_segment_visit_page(mi_page_t* page, bool visit_blocks, mi_block_visit_fun* visitor, void* arg) {
  mi_heap_area_t area;
  _mi_heap_area_init(&area, page);
  if (!visitor(0, &area, 0, area.block_size, arg)) return 0;
  if (visit_blocks) {
    return _mi_heap_area_visit_blocks(&area, page, visitor, arg);
  }
  else {
    return 1;
  }
}

bool _mi_segment_visit_blocks(mi_segment_t* segment, int heap_tag, bool visit_blocks, mi_block_visit_fun* visitor, void* arg) {
  const mi_slice_t* end;
  mi_slice_t* slice = mi_slices_start_iterate(segment, &end);
  while (slice < end) {
    if (mi_slice_is_used(slice)) {
      mi_page_t* const page = mi_slice_to_page(slice);
      if (heap_tag < 0 || (int)page->heap_tag == heap_tag) {
        if (!mi_segment_visit_page(page, visit_blocks, visitor, arg)) return 0;
      }
    }
    slice = slice + slice->slice_count;
  }
  return 1;
}
