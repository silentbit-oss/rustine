# 0 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c"
# 22 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c"
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
# 23 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c" 2
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
# 24 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c" 2

# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.h" 1
# 19 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.h"
       
# 31 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.h"
typedef _Atomic(size_t) mi_bitmap_field_t;
typedef mi_bitmap_field_t* mi_bitmap_t;


typedef size_t mi_bitmap_index_t;


static inline mi_bitmap_index_t mi_bitmap_index_create_ex(size_t idx, size_t bitidx) {
  ((bitidx <= (8*(1<<(3)))) ? (void)0 : _mi_assert_fail("bitidx <= MI_BITMAP_FIELD_BITS","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.h",39,__func__));
  return (idx*(8*(1<<(3)))) + bitidx;
}
static inline mi_bitmap_index_t mi_bitmap_index_create(size_t idx, size_t bitidx) {
  ((bitidx < (8*(1<<(3)))) ? (void)0 : _mi_assert_fail("bitidx < MI_BITMAP_FIELD_BITS","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.h",43,__func__));
  return mi_bitmap_index_create_ex(idx,bitidx);
}


static inline mi_bitmap_index_t mi_bitmap_index_create_from_bit(size_t full_bitidx) {
  return mi_bitmap_index_create(full_bitidx / (8*(1<<(3))), full_bitidx % (8*(1<<(3))));
}


static inline size_t mi_bitmap_index_field(mi_bitmap_index_t bitmap_idx) {
  return (bitmap_idx / (8*(1<<(3))));
}


static inline size_t mi_bitmap_index_bit_in_field(mi_bitmap_index_t bitmap_idx) {
  return (bitmap_idx % (8*(1<<(3))));
}


static inline size_t mi_bitmap_index_bit(mi_bitmap_index_t bitmap_idx) {
  return bitmap_idx;
}







bool _mi_bitmap_try_find_claim_field(mi_bitmap_t bitmap, size_t idx, const size_t count, mi_bitmap_index_t* bitmap_idx);



bool _mi_bitmap_try_find_from_claim(mi_bitmap_t bitmap, const size_t bitmap_fields, const size_t start_field_idx, const size_t count, mi_bitmap_index_t* bitmap_idx);


typedef bool ( *mi_bitmap_pred_fun_t)(mi_bitmap_index_t bitmap_idx, void* pred_arg);
bool _mi_bitmap_try_find_from_claim_pred(mi_bitmap_t bitmap, const size_t bitmap_fields, const size_t start_field_idx, const size_t count, mi_bitmap_pred_fun_t pred_fun, void* pred_arg, mi_bitmap_index_t* bitmap_idx);



bool _mi_bitmap_unclaim(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx);



bool _mi_bitmap_try_claim(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx);



bool _mi_bitmap_claim(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx, bool* any_zero);

bool _mi_bitmap_is_claimed(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx);
bool _mi_bitmap_is_any_claimed(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx);
# 106 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.h"
bool _mi_bitmap_try_find_from_claim_across(mi_bitmap_t bitmap, const size_t bitmap_fields, const size_t start_field_idx, const size_t count, mi_bitmap_index_t* bitmap_idx);



bool _mi_bitmap_unclaim_across(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx);



bool _mi_bitmap_claim_across(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx, bool* pany_zero, size_t* already_set);

bool _mi_bitmap_is_claimed_across(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx, size_t* already_set);
bool _mi_bitmap_is_any_claimed_across(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx);
# 26 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c" 2







typedef struct mi_arena_s {
  mi_arena_id_t id;
  mi_memid_t memid;
  _Atomic(uint8_t*) start;
  size_t block_count;
  size_t field_count;
  size_t meta_size;
  mi_memid_t meta_memid;
  int numa_node;
  bool exclusive;
  bool is_large;
  pthread_mutex_t abandoned_visit_lock;
  _Atomic(size_t) search_idx;
  _Atomic(mi_msecs_t) purge_expire;

  mi_bitmap_field_t* blocks_dirty;
  mi_bitmap_field_t* blocks_committed;
  mi_bitmap_field_t* blocks_purge;
  mi_bitmap_field_t* blocks_abandoned;
  mi_bitmap_field_t blocks_inuse[1];

} mi_arena_t;







static _Atomic(mi_arena_t*) mi_arenas[(132)];
static _Atomic(size_t) mi_arena_count;
static _Atomic(int64_t) mi_arenas_purge_expire;


# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c" 1
# 16 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c"
size_t mi_arena_id_index(mi_arena_id_t id);
mi_arena_t* mi_arena_from_index(size_t idx);
size_t mi_arena_get_count(void);
void* mi_arena_block_start(mi_arena_t* arena, mi_bitmap_index_t bindex);
bool mi_arena_memid_indices(mi_memid_t memid, size_t* arena_index, mi_bitmap_index_t* bitmap_index);
# 50 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c"
static bool mi_arena_segment_os_clear_abandoned(mi_segment_t* segment, bool take_lock) {
  ((segment->memid.memkind != MI_MEM_ARENA) ? (void)0 : _mi_assert_fail("segment->memid.memkind != MI_MEM_ARENA","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",51,__func__));

  mi_subproc_t* const subproc = segment->subproc;
  if (take_lock && !mi_lock_try_acquire(&subproc->abandoned_os_lock)) {
    return 0;
  }

  bool reclaimed = 0;
  mi_segment_t* const next = segment->abandoned_os_next;
  mi_segment_t* const prev = segment->abandoned_os_prev;
  if (next != 0 || prev != 0 || subproc->abandoned_os_list == segment) {
# 74 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c"
    if (prev != 0) { prev->abandoned_os_next = next; }
    else { subproc->abandoned_os_list = next; }
    if (next != 0) { next->abandoned_os_prev = prev; }
    else { subproc->abandoned_os_list_tail = prev; }
    segment->abandoned_os_next = 0;
    segment->abandoned_os_prev = 0;
    atomic_fetch_sub_explicit(&subproc->abandoned_count,(uintptr_t)1,memory_order_relaxed);
    atomic_fetch_sub_explicit(&subproc->abandoned_os_list_count,(uintptr_t)1,memory_order_relaxed);
    if (take_lock) {
      atomic_store_explicit(&segment->thread_id,_mi_thread_id(),memory_order_release);
    }
    reclaimed = 1;
  }
  if (take_lock) { mi_lock_release(&segment->subproc->abandoned_os_lock); }
  return reclaimed;
}



bool _mi_arena_segment_clear_abandoned(mi_segment_t* segment) {
  if (__builtin_expect(!!(segment->memid.memkind != MI_MEM_ARENA),0)) {
    return mi_arena_segment_os_clear_abandoned(segment, 1 );
  }

  size_t arena_idx;
  size_t bitmap_idx;
  mi_arena_memid_indices(segment->memid, &arena_idx, &bitmap_idx);
  mi_arena_t* arena = mi_arena_from_index(arena_idx);
  ((arena != 0) ? (void)0 : _mi_assert_fail("arena != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",102,__func__));

  bool was_marked = _mi_bitmap_unclaim(arena->blocks_abandoned, arena->field_count, 1, bitmap_idx);
  if (was_marked) {
    ((atomic_load_explicit(&segment->thread_id,memory_order_acquire) == 0) ? (void)0 : _mi_assert_fail("mi_atomic_load_acquire(&segment->thread_id) == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",106,__func__));
    atomic_fetch_sub_explicit(&segment->subproc->abandoned_count,(uintptr_t)1,memory_order_relaxed);
    atomic_store_explicit(&segment->thread_id,_mi_thread_id(),memory_order_release);
  }

  ((!was_marked || _mi_bitmap_is_claimed(arena->blocks_inuse, arena->field_count, 1, bitmap_idx)) ? (void)0 : _mi_assert_fail("!was_marked || _mi_bitmap_is_claimed(arena->blocks_inuse, arena->field_count, 1, bitmap_idx)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",111,__func__));

  return was_marked;
}



static void mi_arena_segment_os_mark_abandoned(mi_segment_t* segment) {
  ((segment->memid.memkind != MI_MEM_ARENA) ? (void)0 : _mi_assert_fail("segment->memid.memkind != MI_MEM_ARENA","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",119,__func__));

  mi_subproc_t* const subproc = segment->subproc;
  for(bool _go = (mi_lock_acquire(&subproc->abandoned_os_lock),1); _go; (mi_lock_release(&subproc->abandoned_os_lock), _go=0) ) {

    mi_segment_t* prev = subproc->abandoned_os_list_tail;
    ((prev == 0 || prev->abandoned_os_next == 0) ? (void)0 : _mi_assert_fail("prev == NULL || prev->abandoned_os_next == NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",125,__func__));
    ((segment->abandoned_os_prev == 0) ? (void)0 : _mi_assert_fail("segment->abandoned_os_prev == NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",126,__func__));
    ((segment->abandoned_os_next == 0) ? (void)0 : _mi_assert_fail("segment->abandoned_os_next == NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",127,__func__));
    if (prev != 0) { prev->abandoned_os_next = segment; }
    else { subproc->abandoned_os_list = segment; }
    subproc->abandoned_os_list_tail = segment;
    segment->abandoned_os_prev = prev;
    segment->abandoned_os_next = 0;
    atomic_fetch_add_explicit(&subproc->abandoned_os_list_count,(uintptr_t)1,memory_order_relaxed);
    atomic_fetch_add_explicit(&subproc->abandoned_count,(uintptr_t)1,memory_order_relaxed);

  }
  return;
}



void _mi_arena_segment_mark_abandoned(mi_segment_t* segment)
{
  ((segment->used == segment->abandoned) ? (void)0 : _mi_assert_fail("segment->used == segment->abandoned","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",144,__func__));
  atomic_store_explicit(&segment->thread_id,(uintptr_t)0,memory_order_release);
  if (__builtin_expect(!!(segment->memid.memkind != MI_MEM_ARENA),0)) {
    mi_arena_segment_os_mark_abandoned(segment);
    return;
  }

  size_t arena_idx;
  size_t bitmap_idx;
  mi_arena_memid_indices(segment->memid, &arena_idx, &bitmap_idx);
  mi_arena_t* arena = mi_arena_from_index(arena_idx);
  ((arena != 0) ? (void)0 : _mi_assert_fail("arena != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",155,__func__));

  mi_subproc_t* const subproc = segment->subproc;
  const bool was_unmarked = _mi_bitmap_claim(arena->blocks_abandoned, arena->field_count, 1, bitmap_idx, 0);
  if (was_unmarked) { atomic_fetch_add_explicit(&subproc->abandoned_count,(uintptr_t)1,memory_order_relaxed); }
  ((was_unmarked) ? (void)0 : _mi_assert_fail("was_unmarked","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",160,__func__));
  ((_mi_bitmap_is_claimed(arena->blocks_inuse, arena->field_count, 1, bitmap_idx)) ? (void)0 : _mi_assert_fail("_mi_bitmap_is_claimed(arena->blocks_inuse, arena->field_count, 1, bitmap_idx)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",161,__func__));
}
# 171 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c"
void _mi_arena_field_cursor_init(mi_heap_t* heap, mi_subproc_t* subproc, bool visit_all, mi_arena_field_cursor_t* current) {
  ((heap == 0 || heap->tld->segments.subproc == subproc) ? (void)0 : _mi_assert_fail("heap == NULL || heap->tld->segments.subproc == subproc","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",172,__func__));
  current->bitmap_idx = 0;
  current->subproc = subproc;
  current->visit_all = visit_all;
  current->hold_visit_lock = 0;
  const size_t abandoned_count = atomic_load_explicit(&subproc->abandoned_count,memory_order_relaxed);
  const size_t abandoned_list_count = atomic_load_explicit(&subproc->abandoned_os_list_count,memory_order_relaxed);
  const size_t max_arena = mi_arena_get_count();
  if (heap != 0 && heap->arena_id != _mi_arena_id_none()) {

    current->start = mi_arena_id_index(heap->arena_id);
    current->end = current->start + 1;
    current->os_list_count = 0;
  }
  else {

    if (abandoned_count > abandoned_list_count && max_arena > 0) {
      current->start = (heap == 0 || max_arena == 0 ? 0 : (mi_arena_id_t)(_mi_heap_random_next(heap) % max_arena));
      current->end = current->start + max_arena;
    }
    else {
      current->start = 0;
      current->end = 0;
    }
    current->os_list_count = abandoned_list_count;
  }
  ((current->start <= max_arena) ? (void)0 : _mi_assert_fail("current->start <= max_arena","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",198,__func__));
}

void _mi_arena_field_cursor_done(mi_arena_field_cursor_t* current) {
  if (current->hold_visit_lock) {
    mi_lock_release(&current->subproc->abandoned_os_visit_lock);
    current->hold_visit_lock = 0;
  }
}

static mi_segment_t* mi_arena_segment_clear_abandoned_at(mi_arena_t* arena, mi_subproc_t* subproc, mi_bitmap_index_t bitmap_idx) {

  if (!_mi_bitmap_unclaim(arena->blocks_abandoned, arena->field_count, 1, bitmap_idx)) return 0;
  ((_mi_bitmap_is_claimed(arena->blocks_inuse, arena->field_count, 1, bitmap_idx)) ? (void)0 : _mi_assert_fail("_mi_bitmap_is_claimed(arena->blocks_inuse, arena->field_count, 1, bitmap_idx)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",211,__func__));
  mi_segment_t* segment = (mi_segment_t*)mi_arena_block_start(arena, bitmap_idx);
  ((atomic_load_explicit(&segment->thread_id,memory_order_relaxed) == 0) ? (void)0 : _mi_assert_fail("mi_atomic_load_relaxed(&segment->thread_id) == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",213,__func__));




  if (segment->subproc != subproc) {

    const bool was_zero = _mi_bitmap_claim(arena->blocks_abandoned, arena->field_count, 1, bitmap_idx, 0);
    ((was_zero) ? (void)0 : _mi_assert_fail("was_zero","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",221,__func__)); (void)(was_zero);
    return 0;
  }
  else {

    atomic_fetch_sub_explicit(&subproc->abandoned_count,(uintptr_t)1,memory_order_relaxed);
    return segment;
  }
}

static mi_segment_t* mi_arena_segment_clear_abandoned_next_field(mi_arena_field_cursor_t* previous) {
  const size_t max_arena = mi_arena_get_count();
  size_t field_idx = mi_bitmap_index_field(previous->bitmap_idx);
  size_t bit_idx = mi_bitmap_index_bit_in_field(previous->bitmap_idx);

  for (; previous->start < previous->end; previous->start++, field_idx = 0, bit_idx = 0) {

    size_t arena_idx = (previous->start >= max_arena ? previous->start % max_arena : previous->start);
    mi_arena_t* arena = mi_arena_from_index(arena_idx);
    if (arena != 0) {
      bool has_lock = 0;

      for (; field_idx < arena->field_count; field_idx++, bit_idx = 0) {
        size_t field = atomic_load_explicit(&arena->blocks_abandoned[field_idx],memory_order_relaxed);
        if (__builtin_expect(!!(field != 0),0)) {

          if (!has_lock && mi_option_is_enabled(mi_option_visit_abandoned)) {
            has_lock = (previous->visit_all ? (mi_lock_acquire(&arena->abandoned_visit_lock),1) : mi_lock_try_acquire(&arena->abandoned_visit_lock));
            if (!has_lock) {
              if (previous->visit_all) {
                _mi_error_message((14), "internal error: failed to visit all abandoned segments due to failure to acquire the visitor lock");
              }

              break;
            }
          }
          ((has_lock || !mi_option_is_enabled(mi_option_visit_abandoned)) ? (void)0 : _mi_assert_fail("has_lock || !mi_option_is_enabled(mi_option_visit_abandoned)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",257,__func__));

          for (; bit_idx < (8*(1<<(3))); bit_idx++) {

            size_t mask = ((size_t)1 << bit_idx);
            if (__builtin_expect(!!((field & mask) == mask),0)) {
              mi_bitmap_index_t bitmap_idx = mi_bitmap_index_create(field_idx, bit_idx);
              mi_segment_t* const segment = mi_arena_segment_clear_abandoned_at(arena, previous->subproc, bitmap_idx);
              if (segment != 0) {

                if (has_lock) { mi_lock_release(&arena->abandoned_visit_lock); }
                previous->bitmap_idx = mi_bitmap_index_create_ex(field_idx, bit_idx + 1);
                return segment;
              }
            }
          }
        }
      }
      if (has_lock) { mi_lock_release(&arena->abandoned_visit_lock); }
    }
  }
  return 0;
}

static mi_segment_t* mi_arena_segment_clear_abandoned_next_list(mi_arena_field_cursor_t* previous) {



  if (!previous->hold_visit_lock) {
    previous->hold_visit_lock = (previous->visit_all ? (mi_lock_acquire(&previous->subproc->abandoned_os_visit_lock),1)
                                                     : mi_lock_try_acquire(&previous->subproc->abandoned_os_visit_lock));
    if (!previous->hold_visit_lock) {
      if (previous->visit_all) {
        _mi_error_message((14), "internal error: failed to visit all abandoned segments due to failure to acquire the OS visitor lock");
      }
      return 0;
    }
  }

  while (previous->os_list_count > 0) {
    previous->os_list_count--;
    mi_lock_acquire(&previous->subproc->abandoned_os_lock);
    mi_segment_t* segment = previous->subproc->abandoned_os_list;

    if (segment == 0 || mi_arena_segment_os_clear_abandoned(segment, 0 )) {
      mi_lock_release(&previous->subproc->abandoned_os_lock);
      return segment;
    }

    mi_lock_release(&previous->subproc->abandoned_os_lock);
  }

  ((previous->os_list_count == 0) ? (void)0 : _mi_assert_fail("previous->os_list_count == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",309,__func__));
  return 0;
}




mi_segment_t* _mi_arena_segment_clear_abandoned_next(mi_arena_field_cursor_t* previous) {
  if (previous->start < previous->end) {

    mi_segment_t* segment = mi_arena_segment_clear_abandoned_next_field(previous);
    if (segment != 0) { return segment; }
  }

  ((previous->start == previous->end) ? (void)0 : _mi_assert_fail("previous->start == previous->end","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",323,__func__));
  return mi_arena_segment_clear_abandoned_next_list(previous);
}


bool mi_abandoned_visit_blocks(mi_subproc_id_t subproc_id, int heap_tag, bool visit_blocks, mi_block_visit_fun* visitor, void* arg) {


  if (!mi_option_is_enabled(mi_option_visit_abandoned)) {
    _mi_error_message((14), "internal error: can only visit abandoned blocks when MIMALLOC_VISIT_ABANDONED=ON");
    return 0;
  }
  mi_arena_field_cursor_t current;
  _mi_arena_field_cursor_init(0, _mi_subproc_from_id(subproc_id), 1 , &current);
  mi_segment_t* segment;
  bool ok = 1;
  while (ok && (segment = _mi_arena_segment_clear_abandoned_next(&current)) != 0) {
    ok = _mi_segment_visit_blocks(segment, heap_tag, visit_blocks, visitor, arg);
    _mi_arena_segment_mark_abandoned(segment);
  }
  _mi_arena_field_cursor_done(&current);
  return ok;
}
# 68 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c" 2







size_t mi_arena_id_index(mi_arena_id_t id) {
  return (size_t)(id <= 0 ? (132) : id - 1);
}

static mi_arena_id_t mi_arena_id_create(size_t arena_index) {
  ((arena_index < (132)) ? (void)0 : _mi_assert_fail("arena_index < MI_MAX_ARENAS","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",80,__func__));
  return (int)arena_index + 1;
}

mi_arena_id_t _mi_arena_id_none(void) {
  return 0;
}

static bool mi_arena_id_is_suitable(mi_arena_id_t arena_id, bool arena_is_exclusive, mi_arena_id_t req_arena_id) {
  return ((!arena_is_exclusive && req_arena_id == _mi_arena_id_none()) ||
          (arena_id == req_arena_id));
}

bool _mi_arena_memid_is_suitable(mi_memid_t memid, mi_arena_id_t request_arena_id) {
  if (memid.memkind == MI_MEM_ARENA) {
    return mi_arena_id_is_suitable(memid.mem.arena.id, memid.mem.arena.is_exclusive, request_arena_id);
  }
  else {
    return mi_arena_id_is_suitable(_mi_arena_id_none(), 0, request_arena_id);
  }
}

bool _mi_arena_memid_is_os_allocated(mi_memid_t memid) {
  return (memid.memkind == MI_MEM_OS);
}

size_t mi_arena_get_count(void) {
  return atomic_load_explicit(&mi_arena_count,memory_order_relaxed);
}

mi_arena_t* mi_arena_from_index(size_t idx) {
  ((idx < mi_arena_get_count()) ? (void)0 : _mi_assert_fail("idx < mi_arena_get_count()","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",111,__func__));
  return atomic_load_explicit(&mi_arenas[idx],memory_order_acquire);
}







static size_t mi_block_count_of_size(size_t size) {
  return _mi_divide_up(size, ((1UL<<( 9 + (13 + (3))))));
}

static size_t mi_arena_block_size(size_t bcount) {
  return (bcount * ((1UL<<( 9 + (13 + (3))))));
}

static size_t mi_arena_size(mi_arena_t* arena) {
  return mi_arena_block_size(arena->block_count);
}

static mi_memid_t mi_memid_create_arena(mi_arena_id_t id, bool is_exclusive, mi_bitmap_index_t bitmap_index) {
  mi_memid_t memid = _mi_memid_create(MI_MEM_ARENA);
  memid.mem.arena.id = id;
  memid.mem.arena.block_index = bitmap_index;
  memid.mem.arena.is_exclusive = is_exclusive;
  return memid;
}

bool mi_arena_memid_indices(mi_memid_t memid, size_t* arena_index, mi_bitmap_index_t* bitmap_index) {
  ((memid.memkind == MI_MEM_ARENA) ? (void)0 : _mi_assert_fail("memid.memkind == MI_MEM_ARENA","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",142,__func__));
  *arena_index = mi_arena_id_index(memid.mem.arena.id);
  *bitmap_index = memid.mem.arena.block_index;
  return memid.mem.arena.is_exclusive;
}
# 157 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c"
static uint8_t mi_arena_static[(((1<<(3))/2)*(1024UL))];
static _Atomic(size_t) mi_arena_static_top;

static void* mi_arena_static_zalloc(size_t size, size_t alignment, mi_memid_t* memid) {
  *memid = _mi_memid_none();
  if (size == 0 || size > (((1<<(3))/2)*(1024UL))) return 0;
  const size_t toplow = atomic_load_explicit(&mi_arena_static_top,memory_order_relaxed);
  if ((toplow + size) > (((1<<(3))/2)*(1024UL))) return 0;


  if (alignment < 16) { alignment = 16; }
  const size_t oversize = size + alignment - 1;
  if (toplow + oversize > (((1<<(3))/2)*(1024UL))) return 0;
  const size_t oldtop = atomic_fetch_add_explicit(&mi_arena_static_top,oversize,memory_order_acq_rel);
  size_t top = oldtop + oversize;
  if (top > (((1<<(3))/2)*(1024UL))) {

    atomic_compare_exchange_strong_explicit(&mi_arena_static_top,&top,oldtop,memory_order_acq_rel,memory_order_acquire);
    return 0;
  }


  *memid = _mi_memid_create(MI_MEM_STATIC);
  memid->initially_zero = 1;
  const size_t start = _mi_align_up(oldtop, alignment);
  uint8_t* const p = &mi_arena_static[start];
  _mi_memzero_aligned(p, size);
  return p;
}

void* _mi_arena_meta_zalloc(size_t size, mi_memid_t* memid) {
  *memid = _mi_memid_none();


  void* p = mi_arena_static_zalloc(size, 16, memid);
  if (p != 0) return p;


  p = _mi_os_zalloc(size, memid);
  if (p == 0) return 0;

  return p;
}

void _mi_arena_meta_free(void* p, mi_memid_t memid, size_t size) {
  if (mi_memkind_is_os(memid.memkind)) {
    _mi_os_free(p, size, memid);
  }
  else {
    ((memid.memkind == MI_MEM_STATIC) ? (void)0 : _mi_assert_fail("memid.memkind == MI_MEM_STATIC","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",206,__func__));
  }
}

void* mi_arena_block_start(mi_arena_t* arena, mi_bitmap_index_t bindex) {
  return (arena->start + mi_arena_block_size(mi_bitmap_index_bit(bindex)));
}







static bool mi_arena_try_claim(mi_arena_t* arena, size_t blocks, mi_bitmap_index_t* bitmap_idx)
{
  size_t idx = 0;
  if (_mi_bitmap_try_find_from_claim_across(arena->blocks_inuse, arena->field_count, idx, blocks, bitmap_idx)) {
    atomic_store_explicit(&arena->search_idx,mi_bitmap_index_field(*bitmap_idx),memory_order_relaxed);
    return 1;
  };
  return 0;
}






static void* mi_arena_try_alloc_at(mi_arena_t* arena, size_t arena_index, size_t needed_bcount,
                                                    bool commit, mi_memid_t* memid)
{
  (void)(arena_index);
  ((mi_arena_id_index(arena->id) == arena_index) ? (void)0 : _mi_assert_fail("mi_arena_id_index(arena->id) == arena_index","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",239,__func__));

  mi_bitmap_index_t bitmap_index;
  if (!mi_arena_try_claim(arena, needed_bcount, &bitmap_index)) return 0;


  void* p = mi_arena_block_start(arena, bitmap_index);
  *memid = mi_memid_create_arena(arena->id, arena->exclusive, bitmap_index);
  memid->is_pinned = arena->memid.is_pinned;


  if (arena->blocks_purge != 0) {

    _mi_bitmap_unclaim_across(arena->blocks_purge, arena->field_count, needed_bcount, bitmap_index);
  }


  if (arena->memid.initially_zero && arena->blocks_dirty != 0) {
    memid->initially_zero = _mi_bitmap_claim_across(arena->blocks_dirty, arena->field_count, needed_bcount, bitmap_index, 0, 0);
  }


  if (arena->blocks_committed == 0) {

    memid->initially_committed = 1;
  }
  else if (commit) {

    memid->initially_committed = 1;
    const size_t commit_size = mi_arena_block_size(needed_bcount);
    bool any_uncommitted;
    size_t already_committed = 0;
    _mi_bitmap_claim_across(arena->blocks_committed, arena->field_count, needed_bcount, bitmap_index, &any_uncommitted, &already_committed);
    if (any_uncommitted) {
      ((already_committed < needed_bcount) ? (void)0 : _mi_assert_fail("already_committed < needed_bcount","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",273,__func__));
      const size_t stat_commit_size = commit_size - mi_arena_block_size(already_committed);
      bool commit_zero = 0;
      if (!_mi_os_commit_ex(p, commit_size, &commit_zero, stat_commit_size)) {
        memid->initially_committed = 0;
      }
      else {
        if (commit_zero) { memid->initially_zero = 1; }
      }
    }
    else {

      _mi_os_reuse( p, commit_size );
    }
  }
  else {

    size_t already_committed = 0;
    memid->initially_committed = _mi_bitmap_is_claimed_across(arena->blocks_committed, arena->field_count, needed_bcount, bitmap_index, &already_committed);
    if (!memid->initially_committed && already_committed > 0) {

      ((already_committed < needed_bcount) ? (void)0 : _mi_assert_fail("already_committed < needed_bcount","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",294,__func__));
      _mi_stat_decrease(&_mi_stats_main.committed, mi_arena_block_size(already_committed));
      _mi_bitmap_unclaim_across(arena->blocks_committed, arena->field_count, needed_bcount, bitmap_index);
    }
  }

  return p;
}


static void* mi_arena_try_alloc_at_id(mi_arena_id_t arena_id, bool match_numa_node, int numa_node, size_t size, size_t alignment,
                                       bool commit, bool allow_large, mi_arena_id_t req_arena_id, mi_memid_t* memid )
{
  ;
  ((alignment <= (1UL<<( 9 + (13 + (3))))) ? (void)0 : _mi_assert_fail("alignment <= MI_SEGMENT_ALIGN","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",308,__func__));
  const size_t bcount = mi_block_count_of_size(size);
  const size_t arena_index = mi_arena_id_index(arena_id);
  ((arena_index < atomic_load_explicit(&mi_arena_count,memory_order_relaxed)) ? (void)0 : _mi_assert_fail("arena_index < mi_atomic_load_relaxed(&mi_arena_count)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",311,__func__));
  ((size <= mi_arena_block_size(bcount)) ? (void)0 : _mi_assert_fail("size <= mi_arena_block_size(bcount)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",312,__func__));


  mi_arena_t* arena = mi_arena_from_index(arena_index);
  if (arena == 0) return 0;
  if (!allow_large && arena->is_large) return 0;
  if (!mi_arena_id_is_suitable(arena->id, arena->exclusive, req_arena_id)) return 0;
  if (req_arena_id == _mi_arena_id_none()) {
    const bool numa_suitable = (numa_node < 0 || arena->numa_node < 0 || arena->numa_node == numa_node);
    if (match_numa_node) { if (!numa_suitable) return 0; }
                    else { if (numa_suitable) return 0; }
  }


  void* p = mi_arena_try_alloc_at(arena, arena_index, bcount, commit, memid);
  ((p == 0 || _mi_is_aligned(p, alignment)) ? (void)0 : _mi_assert_fail("p == NULL || _mi_is_aligned(p, alignment)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",327,__func__));
  return p;
}



static void* mi_arena_try_alloc(int numa_node, size_t size, size_t alignment,
                                                  bool commit, bool allow_large,
                                                  mi_arena_id_t req_arena_id, mi_memid_t* memid )
{
  (void)(alignment);
  ((alignment <= (1UL<<( 9 + (13 + (3))))) ? (void)0 : _mi_assert_fail("alignment <= MI_SEGMENT_ALIGN","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",338,__func__));
  const size_t max_arena = atomic_load_explicit(&mi_arena_count,memory_order_relaxed);
  if (__builtin_expect(!!(max_arena == 0),1)) return 0;

  if (req_arena_id != _mi_arena_id_none()) {

    if (mi_arena_id_index(req_arena_id) < max_arena) {
      void* p = mi_arena_try_alloc_at_id(req_arena_id, 1, numa_node, size, alignment, commit, allow_large, req_arena_id, memid);
      if (p != 0) return p;
    }
  }
  else {

    for (size_t i = 0; i < max_arena; i++) {
      void* p = mi_arena_try_alloc_at_id(mi_arena_id_create(i), 1, numa_node, size, alignment, commit, allow_large, req_arena_id, memid);
      if (p != 0) return p;
    }


    if (numa_node >= 0) {
      for (size_t i = 0; i < max_arena; i++) {
        void* p = mi_arena_try_alloc_at_id(mi_arena_id_create(i), 0 , numa_node, size, alignment, commit, allow_large, req_arena_id, memid);
        if (p != 0) return p;
      }
    }
  }
  return 0;
}


static bool mi_arena_reserve(size_t req_size, bool allow_large, mi_arena_id_t *arena_id)
{
  if (_mi_preloading()) return 0;

  const size_t arena_count = atomic_load_explicit(&mi_arena_count,memory_order_acquire);
  if (arena_count > ((132) - 4)) return 0;

  size_t arena_reserve = mi_option_get_size(mi_option_arena_reserve);
  if (arena_reserve == 0) return 0;

  if (!_mi_os_has_virtual_reserve()) {
    arena_reserve = arena_reserve/4;
  }
  arena_reserve = _mi_align_up(arena_reserve, ((1UL<<( 9 + (13 + (3))))));
  arena_reserve = _mi_align_up(arena_reserve, (1UL<<( 9 + (13 + (3)))));
  if (arena_count >= 8 && arena_count <= 128) {

    const size_t multiplier = (size_t)1 << _mi_clamp(arena_count/8, 0, 16 );
    size_t reserve = 0;
    if (!mi_mul_overflow(multiplier, arena_reserve, &reserve)) {
      arena_reserve = reserve;
    }
  }
  if (arena_reserve < req_size) return 0;


  bool arena_commit = 0;
  if (mi_option_get(mi_option_arena_eager_commit) == 2) { arena_commit = _mi_os_has_overcommit(); }
  else if (mi_option_get(mi_option_arena_eager_commit) == 1) { arena_commit = 1; }

  return (mi_reserve_os_memory_ex(arena_reserve, arena_commit, allow_large, 0 , arena_id) == 0);
}


void* _mi_arena_alloc_aligned(size_t size, size_t alignment, size_t align_offset, bool commit, bool allow_large,
                              mi_arena_id_t req_arena_id, mi_memid_t* memid)
{
  ((memid != 0) ? (void)0 : _mi_assert_fail("memid != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",405,__func__));
  ((size > 0) ? (void)0 : _mi_assert_fail("size > 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",406,__func__));
  *memid = _mi_memid_none();

  const int numa_node = _mi_os_numa_node();


  if (!mi_option_is_enabled(mi_option_disallow_arena_alloc)) {
    if (size >= (((1UL<<( 9 + (13 + (3)))))/2) && alignment <= (1UL<<( 9 + (13 + (3)))) && align_offset == 0)
    {
      void* p = mi_arena_try_alloc(numa_node, size, alignment, commit, allow_large, req_arena_id, memid);
      if (p != 0) return p;


      if (req_arena_id == _mi_arena_id_none()) {
        mi_arena_id_t arena_id = 0;
        if (mi_arena_reserve(size, allow_large, &arena_id)) {

          ((req_arena_id == _mi_arena_id_none()) ? (void)0 : _mi_assert_fail("req_arena_id == _mi_arena_id_none()","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",423,__func__));
          p = mi_arena_try_alloc_at_id(arena_id, 1, numa_node, size, alignment, commit, allow_large, req_arena_id, memid);
          if (p != 0) return p;
        }
      }
    }
  }


  if (mi_option_is_enabled(mi_option_disallow_os_alloc) || req_arena_id != _mi_arena_id_none()) {
    errno = (12);
    return 0;
  }


  if (align_offset > 0) {
    return _mi_os_alloc_aligned_at_offset(size, alignment, align_offset, commit, allow_large, memid);
  }
  else {
    return _mi_os_alloc_aligned(size, alignment, commit, allow_large, memid);
  }
}

void* _mi_arena_alloc(size_t size, bool commit, bool allow_large, mi_arena_id_t req_arena_id, mi_memid_t* memid)
{
  return _mi_arena_alloc_aligned(size, ((1UL<<( 9 + (13 + (3))))), 0, commit, allow_large, req_arena_id, memid);
}


void* mi_arena_area(mi_arena_id_t arena_id, size_t* size) {
  if (size != 0) *size = 0;
  size_t arena_index = mi_arena_id_index(arena_id);
  if (arena_index >= (132)) return 0;
  mi_arena_t* arena = atomic_load_explicit(&mi_arenas[arena_index],memory_order_acquire);
  if (arena == 0) return 0;
  if (size != 0) { *size = mi_arena_block_size(arena->block_count); }
  return arena->start;
}






static long mi_arena_purge_delay(void) {

  return (mi_option_get(mi_option_purge_delay) * mi_option_get(mi_option_arena_purge_mult));
}



static void mi_arena_purge(mi_arena_t* arena, size_t bitmap_idx, size_t blocks) {
  ((arena->blocks_committed != 0) ? (void)0 : _mi_assert_fail("arena->blocks_committed != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",475,__func__));
  ((arena->blocks_purge != 0) ? (void)0 : _mi_assert_fail("arena->blocks_purge != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",476,__func__));
  ((!arena->memid.is_pinned) ? (void)0 : _mi_assert_fail("!arena->memid.is_pinned","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",477,__func__));
  const size_t size = mi_arena_block_size(blocks);
  void* const p = mi_arena_block_start(arena, bitmap_idx);
  bool needs_recommit;
  size_t already_committed = 0;
  if (_mi_bitmap_is_claimed_across(arena->blocks_committed, arena->field_count, blocks, bitmap_idx, &already_committed)) {

    ((already_committed == blocks) ? (void)0 : _mi_assert_fail("already_committed == blocks","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",484,__func__));
    needs_recommit = _mi_os_purge(p, size);
  }
  else {



    ((already_committed < blocks) ? (void)0 : _mi_assert_fail("already_committed < blocks","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",491,__func__));
    ((mi_option_is_enabled(mi_option_purge_decommits)) ? (void)0 : _mi_assert_fail("mi_option_is_enabled(mi_option_purge_decommits)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",492,__func__));
    needs_recommit = _mi_os_purge_ex(p, size, 0 , mi_arena_block_size(already_committed));
  }


  _mi_bitmap_unclaim_across(arena->blocks_purge, arena->field_count, blocks, bitmap_idx);

  if (needs_recommit) {
    _mi_bitmap_unclaim_across(arena->blocks_committed, arena->field_count, blocks, bitmap_idx);
  }
}



static void mi_arena_schedule_purge(mi_arena_t* arena, size_t bitmap_idx, size_t blocks) {
  ((arena->blocks_purge != 0) ? (void)0 : _mi_assert_fail("arena->blocks_purge != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",507,__func__));
  const long delay = mi_arena_purge_delay();
  if (delay < 0) return;

  if (_mi_preloading() || delay == 0) {

    mi_arena_purge(arena, bitmap_idx, blocks);
  }
  else {

    const mi_msecs_t expire = _mi_clock_now() + delay;
    mi_msecs_t expire0 = 0;
    if (atomic_compare_exchange_strong_explicit(&arena->purge_expire,&expire0,expire,memory_order_acq_rel,memory_order_acquire)) {


      atomic_compare_exchange_strong_explicit(&mi_arenas_purge_expire,&expire0,expire,memory_order_acq_rel,memory_order_acquire);
    }
    else {

    }
    _mi_bitmap_claim_across(arena->blocks_purge, arena->field_count, blocks, bitmap_idx, 0, 0);
  }
}




static bool mi_arena_purge_range(mi_arena_t* arena, size_t idx, size_t startidx, size_t bitlen, size_t purge) {
  const size_t endidx = startidx + bitlen;
  size_t bitidx = startidx;
  bool all_purged = 0;
  while (bitidx < endidx) {

    size_t count = 0;
    while (bitidx + count < endidx && (purge & ((size_t)1 << (bitidx + count))) != 0) {
      count++;
    }
    if (count > 0) {

      const mi_bitmap_index_t range_idx = mi_bitmap_index_create(idx, bitidx);
      mi_arena_purge(arena, range_idx, count);
      if (count == bitlen) {
        all_purged = 1;
      }
    }
    bitidx += (count+1);
  }
  return all_purged;
}


static bool mi_arena_try_purge(mi_arena_t* arena, mi_msecs_t now, bool force)
{

  if (arena->memid.is_pinned) return 0;


  mi_msecs_t expire = atomic_load_explicit(&arena->purge_expire,memory_order_relaxed);
  if (!force && (expire == 0 || expire > now)) return 0;


  atomic_compare_exchange_strong_explicit(&arena->purge_expire,&expire,(mi_msecs_t)0,memory_order_acq_rel,memory_order_acquire);
  _mi_stat_counter_increase(&_mi_stats_main.arena_purges, 1);


  bool any_purged = 0;
  bool full_purge = 1;
  for (size_t i = 0; i < arena->field_count; i++) {
    size_t purge = atomic_load_explicit(&arena->blocks_purge[i],memory_order_relaxed);
    if (purge != 0) {
      size_t bitidx = 0;
      while (bitidx < (8*(1<<(3)))) {

        size_t bitlen = 0;
        while (bitidx + bitlen < (8*(1<<(3))) && (purge & ((size_t)1 << (bitidx + bitlen))) != 0) {
          bitlen++;
        }


        const mi_bitmap_index_t bitmap_index = mi_bitmap_index_create(i, bitidx);
        while( bitlen > 0 ) {
          if (_mi_bitmap_try_claim(arena->blocks_inuse, arena->field_count, bitlen, bitmap_index)) {
            break;
          }
          bitlen--;
        }

        if (bitlen > 0) {

          purge = atomic_load_explicit(&arena->blocks_purge[i],memory_order_acquire);
          if (!mi_arena_purge_range(arena, i, bitidx, bitlen, purge)) {
            full_purge = 0;
          }
          any_purged = 1;

          _mi_bitmap_unclaim(arena->blocks_inuse, arena->field_count, bitlen, bitmap_index);
        }
        bitidx += (bitlen+1);
      }
    }
  }

  if (!full_purge) {
    const long delay = mi_arena_purge_delay();
    mi_msecs_t expected = 0;
    atomic_compare_exchange_strong_explicit(&arena->purge_expire,&expected,_mi_clock_now() + delay,memory_order_acq_rel,memory_order_acquire);
  }
  return any_purged;
}

static void mi_arenas_try_purge( bool force, bool visit_all )
{
  if (_mi_preloading() || mi_arena_purge_delay() <= 0) return;


  const mi_msecs_t now = _mi_clock_now();
  mi_msecs_t arenas_expire = atomic_load_explicit(&mi_arenas_purge_expire,memory_order_acquire);
  if (!force && (arenas_expire == 0 || arenas_expire < now)) return;

  const size_t max_arena = atomic_load_explicit(&mi_arena_count,memory_order_acquire);
  if (max_arena == 0) return;


  static mi_atomic_guard_t purge_guard;
  uintptr_t _mi_guard_expected = 0; for(bool _mi_guard_once = 1; _mi_guard_once && atomic_compare_exchange_strong_explicit(&purge_guard,&_mi_guard_expected,(uintptr_t)1,memory_order_acq_rel,memory_order_acquire); (atomic_store_explicit(&purge_guard,(uintptr_t)0,memory_order_release), _mi_guard_once = 0) )
  {

    atomic_store_explicit(&mi_arenas_purge_expire,now + mi_arena_purge_delay(),memory_order_release);
    size_t max_purge_count = (visit_all ? max_arena : 2);
    bool all_visited = 1;
    for (size_t i = 0; i < max_arena; i++) {
      mi_arena_t* arena = atomic_load_explicit(&mi_arenas[i],memory_order_acquire);
      if (arena != 0) {
        if (mi_arena_try_purge(arena, now, force)) {
          if (max_purge_count <= 1) {
            all_visited = 0;
            break;
          }
          max_purge_count--;
        }
      }
    }
    if (all_visited) {

      atomic_store_explicit(&mi_arenas_purge_expire,0,memory_order_release);
    }
  }
}






void _mi_arena_free(void* p, size_t size, size_t committed_size, mi_memid_t memid) {
  ((size > 0) ? (void)0 : _mi_assert_fail("size > 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",662,__func__));
  ((committed_size <= size) ? (void)0 : _mi_assert_fail("committed_size <= size","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",663,__func__));
  if (p==0) return;
  if (size==0) return;
  const bool all_committed = (committed_size == size);
  const size_t decommitted_size = (committed_size <= size ? size - committed_size : 0);


  ;

  if (mi_memkind_is_os(memid.memkind)) {

    if (!all_committed && decommitted_size > 0) {

      _mi_stat_increase(&_mi_stats_main.committed, decommitted_size);
    }
    _mi_os_free(p, size, memid);
  }
  else if (memid.memkind == MI_MEM_ARENA) {

    size_t arena_idx;
    size_t bitmap_idx;
    mi_arena_memid_indices(memid, &arena_idx, &bitmap_idx);
    ((arena_idx < (132)) ? (void)0 : _mi_assert_fail("arena_idx < MI_MAX_ARENAS","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",685,__func__));
    mi_arena_t* arena = atomic_load_explicit(&mi_arenas[arena_idx],memory_order_acquire);
    ((arena != 0) ? (void)0 : _mi_assert_fail("arena != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",687,__func__));
    const size_t blocks = mi_block_count_of_size(size);


    if (arena == 0) {
      _mi_error_message((22), "trying to free from an invalid arena: %p, size %zu, memid: 0x%zx\n", p, size, memid);
      return;
    }
    ((arena->field_count > mi_bitmap_index_field(bitmap_idx)) ? (void)0 : _mi_assert_fail("arena->field_count > mi_bitmap_index_field(bitmap_idx)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",695,__func__));
    if (arena->field_count <= mi_bitmap_index_field(bitmap_idx)) {
      _mi_error_message((22), "trying to free from an invalid arena block: %p, size %zu, memid: 0x%zx\n", p, size, memid);
      return;
    }


    if (arena->memid.is_pinned || arena->blocks_committed == 0) {
      ((all_committed) ? (void)0 : _mi_assert_fail("all_committed","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",703,__func__));
    }
    else {
      ((arena->blocks_committed != 0) ? (void)0 : _mi_assert_fail("arena->blocks_committed != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",706,__func__));
      ((arena->blocks_purge != 0) ? (void)0 : _mi_assert_fail("arena->blocks_purge != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",707,__func__));

      if (!all_committed) {

        _mi_bitmap_unclaim_across(arena->blocks_committed, arena->field_count, blocks, bitmap_idx);
        ;



          _mi_stat_decrease(&_mi_stats_main.committed, committed_size);




      }

      mi_arena_schedule_purge(arena, bitmap_idx, blocks);
    }


    bool all_inuse = _mi_bitmap_unclaim_across(arena->blocks_inuse, arena->field_count, blocks, bitmap_idx);
    if (!all_inuse) {
      _mi_error_message((11), "trying to free an already freed arena block: %p, size %zu\n", p, size);
      return;
    };
  }
  else {

    ((memid.memkind < MI_MEM_OS) ? (void)0 : _mi_assert_fail("memid.memkind < MI_MEM_OS","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",735,__func__));
  }


  mi_arenas_try_purge(0, 0);
}



static void mi_arenas_unsafe_destroy(void) {
  const size_t max_arena = atomic_load_explicit(&mi_arena_count,memory_order_relaxed);
  size_t new_max_arena = 0;
  for (size_t i = 0; i < max_arena; i++) {
    mi_arena_t* arena = atomic_load_explicit(&mi_arenas[i],memory_order_acquire);
    if (arena != 0) {
      mi_lock_done(&arena->abandoned_visit_lock);
      if (arena->start != 0 && mi_memkind_is_os(arena->memid.memkind)) {
        atomic_store_explicit(&mi_arenas[i],0,memory_order_release);
        _mi_os_free(arena->start, mi_arena_size(arena), arena->memid);
      }
      else {
        new_max_arena = i;
      }
      _mi_arena_meta_free(arena, arena->meta_memid, arena->meta_size);
    }
  }


  size_t expected = max_arena;
  atomic_compare_exchange_strong_explicit(&mi_arena_count,&expected,new_max_arena,memory_order_acq_rel,memory_order_acquire);
}


void _mi_arenas_collect(bool force_purge) {
  mi_arenas_try_purge(force_purge, force_purge );
}



void _mi_arena_unsafe_destroy_all(void) {
  mi_arenas_unsafe_destroy();
  _mi_arenas_collect(1 );
}


bool _mi_arena_contains(const void* p) {
  const size_t max_arena = atomic_load_explicit(&mi_arena_count,memory_order_relaxed);
  for (size_t i = 0; i < max_arena; i++) {
    mi_arena_t* arena = atomic_load_explicit(&mi_arenas[i],memory_order_relaxed);
    if (arena != 0 && arena->start <= (const uint8_t*)p && arena->start + mi_arena_block_size(arena->block_count) > (const uint8_t*)p) {
      return 1;
    }
  }
  return 0;
}





static bool mi_arena_add(mi_arena_t* arena, mi_arena_id_t* arena_id, mi_stats_t* stats) {
  ((arena != 0) ? (void)0 : _mi_assert_fail("arena != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",796,__func__));
  (((uintptr_t)atomic_load_explicit(&arena->start,memory_order_relaxed) % (1UL<<( 9 + (13 + (3)))) == 0) ? (void)0 : _mi_assert_fail("(uintptr_t)mi_atomic_load_ptr_relaxed(uint8_t,&arena->start) % MI_SEGMENT_ALIGN == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",797,__func__));
  ((arena->block_count > 0) ? (void)0 : _mi_assert_fail("arena->block_count > 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",798,__func__));
  if (arena_id != 0) { *arena_id = -1; }

  size_t i = atomic_fetch_add_explicit(&mi_arena_count,(uintptr_t)1,memory_order_acq_rel);
  if (i >= (132)) {
    atomic_fetch_sub_explicit(&mi_arena_count,(uintptr_t)1,memory_order_acq_rel);
    return 0;
  }
  _mi_stat_counter_increase(&stats->arena_count,1);
  arena->id = mi_arena_id_create(i);
  atomic_store_explicit(&mi_arenas[i],arena,memory_order_release);
  if (arena_id != 0) { *arena_id = arena->id; }
  return 1;
}

static bool mi_manage_os_memory_ex2(void* start, size_t size, bool is_large, int numa_node, bool exclusive, mi_memid_t memid, mi_arena_id_t* arena_id)
{
  if (arena_id != 0) *arena_id = _mi_arena_id_none();
  if (size < ((1UL<<( 9 + (13 + (3)))))) {
    _mi_warning_message("the arena size is too small (memory at %p with size %zu)\n", start, size);
    return 0;
  }
  if (is_large) {
    ((memid.initially_committed && memid.is_pinned) ? (void)0 : _mi_assert_fail("memid.initially_committed && memid.is_pinned","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",821,__func__));
  }
  if (!_mi_is_aligned(start, (1UL<<( 9 + (13 + (3)))))) {
    void* const aligned_start = mi_align_up_ptr(start, (1UL<<( 9 + (13 + (3)))));
    const size_t diff = (uint8_t*)aligned_start - (uint8_t*)start;
    if (diff >= size || (size - diff) < ((1UL<<( 9 + (13 + (3)))))) {
      _mi_warning_message("after alignment, the size of the arena becomes too small (memory at %p with size %zu)\n", start, size);
      return 0;
    }
    start = aligned_start;
    size = size - diff;
  }

  const size_t bcount = size / ((1UL<<( 9 + (13 + (3)))));
  const size_t fields = _mi_divide_up(bcount, (8*(1<<(3))));
  const size_t bitmaps = (memid.is_pinned ? 3 : 5);
  const size_t asize = sizeof(mi_arena_t) + (bitmaps*fields*sizeof(mi_bitmap_field_t));
  mi_memid_t meta_memid;
  mi_arena_t* arena = (mi_arena_t*)_mi_arena_meta_zalloc(asize, &meta_memid);
  if (arena == 0) return 0;



  arena->id = _mi_arena_id_none();
  arena->memid = memid;
  arena->exclusive = exclusive;
  arena->meta_size = asize;
  arena->meta_memid = meta_memid;
  arena->block_count = bcount;
  arena->field_count = fields;
  arena->start = (uint8_t*)start;
  arena->numa_node = numa_node;
  arena->is_large = is_large;
  arena->purge_expire = 0;
  arena->search_idx = 0;
  mi_lock_init(&arena->abandoned_visit_lock);

  arena->blocks_dirty = &arena->blocks_inuse[fields];
  arena->blocks_abandoned = &arena->blocks_inuse[2 * fields];
  arena->blocks_committed = (arena->memid.is_pinned ? 0 : &arena->blocks_inuse[3*fields]);
  arena->blocks_purge = (arena->memid.is_pinned ? 0 : &arena->blocks_inuse[4*fields]);

  if (arena->blocks_committed != 0 && arena->memid.initially_committed) {
    memset((void*)arena->blocks_committed, 0xFF, fields*sizeof(mi_bitmap_field_t));
  }


  ptrdiff_t post = (fields * (8*(1<<(3)))) - bcount;
  ((post >= 0) ? (void)0 : _mi_assert_fail("post >= 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena.c",869,__func__));
  if (post > 0) {

    mi_bitmap_index_t postidx = mi_bitmap_index_create(fields - 1, (8*(1<<(3))) - post);
    _mi_bitmap_claim(arena->blocks_inuse, fields, post, postidx, 0);
  }
  return mi_arena_add(arena, arena_id, &_mi_stats_main);

}

bool mi_manage_os_memory_ex(void* start, size_t size, bool is_committed, bool is_large, bool is_zero, int numa_node, bool exclusive, mi_arena_id_t* arena_id) {
  mi_memid_t memid = _mi_memid_create(MI_MEM_EXTERNAL);
  memid.initially_committed = is_committed;
  memid.initially_zero = is_zero;
  memid.is_pinned = is_large;
  return mi_manage_os_memory_ex2(start,size,is_large,numa_node,exclusive,memid, arena_id);
}


int mi_reserve_os_memory_ex(size_t size, bool commit, bool allow_large, bool exclusive, mi_arena_id_t* arena_id) {
  if (arena_id != 0) *arena_id = _mi_arena_id_none();
  size = _mi_align_up(size, ((1UL<<( 9 + (13 + (3))))));
  mi_memid_t memid;
  void* start = _mi_os_alloc_aligned(size, (1UL<<( 9 + (13 + (3)))), commit, allow_large, &memid);
  if (start == 0) return (12);
  const bool is_large = memid.is_pinned;
  if (!mi_manage_os_memory_ex2(start, size, is_large, -1 , exclusive, memid, arena_id)) {
    _mi_os_free_ex(start, size, commit, memid);
    _mi_verbose_message("failed to reserve %zu KiB memory\n", _mi_divide_up(size, 1024));
    return (12);
  }
  _mi_verbose_message("reserved %zu KiB memory%s\n", _mi_divide_up(size, 1024), is_large ? " (in large os pages)" : "");
  return 0;
}



bool mi_manage_os_memory(void* start, size_t size, bool is_committed, bool is_large, bool is_zero, int numa_node) {
  return mi_manage_os_memory_ex(start, size, is_committed, is_large, is_zero, numa_node, 0 , 0);
}


int mi_reserve_os_memory(size_t size, bool commit, bool allow_large) {
  return mi_reserve_os_memory_ex(size, commit, allow_large, 0, 0);
}






static size_t mi_debug_show_bitmap(const char* prefix, const char* header, size_t block_count, mi_bitmap_field_t* fields, size_t field_count ) {
  _mi_message("%s%s:\n", prefix, header);
  size_t bcount = 0;
  size_t inuse_count = 0;
  for (size_t i = 0; i < field_count; i++) {
    char buf[(8*(1<<(3))) + 1];
    uintptr_t field = atomic_load_explicit(&fields[i],memory_order_relaxed);
    for (size_t bit = 0; bit < (8*(1<<(3))); bit++, bcount++) {
      if (bcount < block_count) {
        bool inuse = ((((uintptr_t)1 << bit) & field) != 0);
        if (inuse) inuse_count++;
        buf[bit] = (inuse ? 'x' : '.');
      }
      else {
        buf[bit] = ' ';
      }
    }
    buf[(8*(1<<(3)))] = 0;
    _mi_message("%s  %s\n", prefix, buf);
  }
  _mi_message("%s  total ('x'): %zu\n", prefix, inuse_count);
  return inuse_count;
}

void mi_debug_show_arenas(void) {
  const bool show_inuse = 1;
  size_t max_arenas = atomic_load_explicit(&mi_arena_count,memory_order_relaxed);
  size_t inuse_total = 0;


  for (size_t i = 0; i < max_arenas; i++) {
    mi_arena_t* arena = atomic_load_explicit(&mi_arenas[i],memory_order_relaxed);
    if (arena == 0) break;
    _mi_message("arena %zu: %zu blocks of size %zuMiB (in %zu fields) %s\n", i, arena->block_count, (size_t)(((1UL<<( 9 + (13 + (3))))) / ((1024UL)*(1024UL))), arena->field_count, (arena->memid.is_pinned ? ", pinned" : ""));
    if (show_inuse) {
      inuse_total += mi_debug_show_bitmap("  ", "inuse blocks", arena->block_count, arena->blocks_inuse, arena->field_count);
    }
    if (arena->blocks_committed != 0) {
      mi_debug_show_bitmap("  ", "committed blocks", arena->block_count, arena->blocks_committed, arena->field_count);
    }






  }
  if (show_inuse) _mi_message("total inuse blocks    : %zu\n", inuse_total);


}


void mi_arenas_print(void) {
  mi_debug_show_arenas();
}






int mi_reserve_huge_os_pages_at_ex(size_t pages, int numa_node, size_t timeout_msecs, bool exclusive, mi_arena_id_t* arena_id) {
  if (arena_id != 0) *arena_id = -1;
  if (pages==0) return 0;
  if (numa_node < -1) numa_node = -1;
  if (numa_node >= 0) numa_node = numa_node % _mi_os_numa_node_count();
  size_t hsize = 0;
  size_t pages_reserved = 0;
  mi_memid_t memid;
  void* p = _mi_os_alloc_huge_os_pages(pages, numa_node, timeout_msecs, &pages_reserved, &hsize, &memid);
  if (p==0 || pages_reserved==0) {
    _mi_warning_message("failed to reserve %zu GiB huge pages\n", pages);
    return (12);
  }
  _mi_verbose_message("numa node %i: reserved %zu GiB huge pages (of the %zu GiB requested)\n", numa_node, pages_reserved, pages);

  if (!mi_manage_os_memory_ex2(p, hsize, 1, numa_node, exclusive, memid, arena_id)) {
    _mi_os_free(p, hsize, memid);
    return (12);
  }
  return 0;
}

int mi_reserve_huge_os_pages_at(size_t pages, int numa_node, size_t timeout_msecs) {
  return mi_reserve_huge_os_pages_at_ex(pages, numa_node, timeout_msecs, 0, 0);
}


int mi_reserve_huge_os_pages_interleave(size_t pages, size_t numa_nodes, size_t timeout_msecs) {
  if (pages == 0) return 0;


  int numa_count = (numa_nodes > 0 && numa_nodes <= 2147483647 ? (int)numa_nodes : _mi_os_numa_node_count());
  if (numa_count == 0) numa_count = 1;
  const size_t pages_per = pages / numa_count;
  const size_t pages_mod = pages % numa_count;
  const size_t timeout_per = (timeout_msecs==0 ? 0 : (timeout_msecs / numa_count) + 50);


  for (int numa_node = 0; numa_node < numa_count && pages > 0; numa_node++) {
    size_t node_pages = pages_per;
    if ((size_t)numa_node < pages_mod) node_pages++;
    int err = mi_reserve_huge_os_pages_at(node_pages, numa_node, timeout_per);
    if (err) return err;
    if (pages < node_pages) {
      pages = 0;
    }
    else {
      pages -= node_pages;
    }
  }

  return 0;
}

int mi_reserve_huge_os_pages(size_t pages, double max_secs, size_t* pages_reserved) {
  (void)(max_secs);
  _mi_warning_message("mi_reserve_huge_os_pages is deprecated: use mi_reserve_huge_os_pages_interleave/at instead\n");
  if (pages_reserved != 0) *pages_reserved = 0;
  int err = mi_reserve_huge_os_pages_interleave(pages, 0, (size_t)(max_secs * 1000.0));
  if (err==0 && pages_reserved!=0) *pages_reserved = pages;
  return err;
}
# 0 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c"
# 10 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c"
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
# 11 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c" 2
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
# 12 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c" 2
# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.h" 1
# 19 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.h"
       
# 31 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.h"
typedef _Atomic(size_t) mi_bitmap_field_t;
typedef mi_bitmap_field_t* mi_bitmap_t;


typedef size_t mi_bitmap_index_t;


static inline mi_bitmap_index_t mi_bitmap_index_create_ex(size_t idx, size_t bitidx) {
  ((bitidx <= (8*(1<<(3)))) ? (void)0 : _mi_assert_fail("bitidx <= MI_BITMAP_FIELD_BITS","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.h",39,__func__));
  return (idx*(8*(1<<(3)))) + bitidx;
}
static inline mi_bitmap_index_t mi_bitmap_index_create(size_t idx, size_t bitidx) {
  ((bitidx < (8*(1<<(3)))) ? (void)0 : _mi_assert_fail("bitidx < MI_BITMAP_FIELD_BITS","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.h",43,__func__));
  return mi_bitmap_index_create_ex(idx,bitidx);
}


static inline mi_bitmap_index_t mi_bitmap_index_create_from_bit(size_t full_bitidx) {
  return mi_bitmap_index_create(full_bitidx / (8*(1<<(3))), full_bitidx % (8*(1<<(3))));
}


static inline size_t mi_bitmap_index_field(mi_bitmap_index_t bitmap_idx) {
  return (bitmap_idx / (8*(1<<(3))));
}


static inline size_t mi_bitmap_index_bit_in_field(mi_bitmap_index_t bitmap_idx) {
  return (bitmap_idx % (8*(1<<(3))));
}


static inline size_t mi_bitmap_index_bit(mi_bitmap_index_t bitmap_idx) {
  return bitmap_idx;
}







bool _mi_bitmap_try_find_claim_field(mi_bitmap_t bitmap, size_t idx, const size_t count, mi_bitmap_index_t* bitmap_idx);



bool _mi_bitmap_try_find_from_claim(mi_bitmap_t bitmap, const size_t bitmap_fields, const size_t start_field_idx, const size_t count, mi_bitmap_index_t* bitmap_idx);


typedef bool ( *mi_bitmap_pred_fun_t)(mi_bitmap_index_t bitmap_idx, void* pred_arg);
bool _mi_bitmap_try_find_from_claim_pred(mi_bitmap_t bitmap, const size_t bitmap_fields, const size_t start_field_idx, const size_t count, mi_bitmap_pred_fun_t pred_fun, void* pred_arg, mi_bitmap_index_t* bitmap_idx);



bool _mi_bitmap_unclaim(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx);



bool _mi_bitmap_try_claim(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx);



bool _mi_bitmap_claim(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx, bool* any_zero);

bool _mi_bitmap_is_claimed(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx);
bool _mi_bitmap_is_any_claimed(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx);
# 106 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/bitmap.h"
bool _mi_bitmap_try_find_from_claim_across(mi_bitmap_t bitmap, const size_t bitmap_fields, const size_t start_field_idx, const size_t count, mi_bitmap_index_t* bitmap_idx);



bool _mi_bitmap_unclaim_across(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx);



bool _mi_bitmap_claim_across(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx, bool* pany_zero, size_t* already_set);

bool _mi_bitmap_is_claimed_across(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx, size_t* already_set);
bool _mi_bitmap_is_any_claimed_across(mi_bitmap_t bitmap, size_t bitmap_fields, size_t count, mi_bitmap_index_t bitmap_idx);
# 13 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c" 2



size_t mi_arena_id_index(mi_arena_id_t id);
mi_arena_t* mi_arena_from_index(size_t idx);
size_t mi_arena_get_count(void);
void* mi_arena_block_start(mi_arena_t* arena, mi_bitmap_index_t bindex);
bool mi_arena_memid_indices(mi_memid_t memid, size_t* arena_index, mi_bitmap_index_t* bitmap_index);
# 50 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c"
static bool mi_arena_segment_os_clear_abandoned(mi_segment_t* segment, bool take_lock) {
  ((segment->memid.memkind != MI_MEM_ARENA) ? (void)0 : _mi_assert_fail("segment->memid.memkind != MI_MEM_ARENA","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",51,__func__));

  mi_subproc_t* const subproc = segment->subproc;
  if (take_lock && !mi_lock_try_acquire(&subproc->abandoned_os_lock)) {
    return 0;
  }

  bool reclaimed = 0;
  mi_segment_t* const next = segment->abandoned_os_next;
  mi_segment_t* const prev = segment->abandoned_os_prev;
  if (next != 0 || prev != 0 || subproc->abandoned_os_list == segment) {
# 74 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c"
    if (prev != 0) { prev->abandoned_os_next = next; }
    else { subproc->abandoned_os_list = next; }
    if (next != 0) { next->abandoned_os_prev = prev; }
    else { subproc->abandoned_os_list_tail = prev; }
    segment->abandoned_os_next = 0;
    segment->abandoned_os_prev = 0;
    atomic_fetch_sub_explicit(&subproc->abandoned_count,(uintptr_t)1,memory_order_relaxed);
    atomic_fetch_sub_explicit(&subproc->abandoned_os_list_count,(uintptr_t)1,memory_order_relaxed);
    if (take_lock) {
      atomic_store_explicit(&segment->thread_id,_mi_thread_id(),memory_order_release);
    }
    reclaimed = 1;
  }
  if (take_lock) { mi_lock_release(&segment->subproc->abandoned_os_lock); }
  return reclaimed;
}



bool _mi_arena_segment_clear_abandoned(mi_segment_t* segment) {
  if (__builtin_expect(!!(segment->memid.memkind != MI_MEM_ARENA),0)) {
    return mi_arena_segment_os_clear_abandoned(segment, 1 );
  }

  size_t arena_idx;
  size_t bitmap_idx;
  mi_arena_memid_indices(segment->memid, &arena_idx, &bitmap_idx);
  mi_arena_t* arena = mi_arena_from_index(arena_idx);
  ((arena != 0) ? (void)0 : _mi_assert_fail("arena != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",102,__func__));

  bool was_marked = _mi_bitmap_unclaim(arena->blocks_abandoned, arena->field_count, 1, bitmap_idx);
  if (was_marked) {
    ((atomic_load_explicit(&segment->thread_id,memory_order_acquire) == 0) ? (void)0 : _mi_assert_fail("mi_atomic_load_acquire(&segment->thread_id) == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",106,__func__));
    atomic_fetch_sub_explicit(&segment->subproc->abandoned_count,(uintptr_t)1,memory_order_relaxed);
    atomic_store_explicit(&segment->thread_id,_mi_thread_id(),memory_order_release);
  }

  ((!was_marked || _mi_bitmap_is_claimed(arena->blocks_inuse, arena->field_count, 1, bitmap_idx)) ? (void)0 : _mi_assert_fail("!was_marked || _mi_bitmap_is_claimed(arena->blocks_inuse, arena->field_count, 1, bitmap_idx)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",111,__func__));

  return was_marked;
}



static void mi_arena_segment_os_mark_abandoned(mi_segment_t* segment) {
  ((segment->memid.memkind != MI_MEM_ARENA) ? (void)0 : _mi_assert_fail("segment->memid.memkind != MI_MEM_ARENA","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",119,__func__));

  mi_subproc_t* const subproc = segment->subproc;
  for(bool _go = (mi_lock_acquire(&subproc->abandoned_os_lock),1); _go; (mi_lock_release(&subproc->abandoned_os_lock), _go=0) ) {

    mi_segment_t* prev = subproc->abandoned_os_list_tail;
    ((prev == 0 || prev->abandoned_os_next == 0) ? (void)0 : _mi_assert_fail("prev == NULL || prev->abandoned_os_next == NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",125,__func__));
    ((segment->abandoned_os_prev == 0) ? (void)0 : _mi_assert_fail("segment->abandoned_os_prev == NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",126,__func__));
    ((segment->abandoned_os_next == 0) ? (void)0 : _mi_assert_fail("segment->abandoned_os_next == NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",127,__func__));
    if (prev != 0) { prev->abandoned_os_next = segment; }
    else { subproc->abandoned_os_list = segment; }
    subproc->abandoned_os_list_tail = segment;
    segment->abandoned_os_prev = prev;
    segment->abandoned_os_next = 0;
    atomic_fetch_add_explicit(&subproc->abandoned_os_list_count,(uintptr_t)1,memory_order_relaxed);
    atomic_fetch_add_explicit(&subproc->abandoned_count,(uintptr_t)1,memory_order_relaxed);

  }
  return;
}



void _mi_arena_segment_mark_abandoned(mi_segment_t* segment)
{
  ((segment->used == segment->abandoned) ? (void)0 : _mi_assert_fail("segment->used == segment->abandoned","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",144,__func__));
  atomic_store_explicit(&segment->thread_id,(uintptr_t)0,memory_order_release);
  if (__builtin_expect(!!(segment->memid.memkind != MI_MEM_ARENA),0)) {
    mi_arena_segment_os_mark_abandoned(segment);
    return;
  }

  size_t arena_idx;
  size_t bitmap_idx;
  mi_arena_memid_indices(segment->memid, &arena_idx, &bitmap_idx);
  mi_arena_t* arena = mi_arena_from_index(arena_idx);
  ((arena != 0) ? (void)0 : _mi_assert_fail("arena != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",155,__func__));

  mi_subproc_t* const subproc = segment->subproc;
  const bool was_unmarked = _mi_bitmap_claim(arena->blocks_abandoned, arena->field_count, 1, bitmap_idx, 0);
  if (was_unmarked) { atomic_fetch_add_explicit(&subproc->abandoned_count,(uintptr_t)1,memory_order_relaxed); }
  ((was_unmarked) ? (void)0 : _mi_assert_fail("was_unmarked","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",160,__func__));
  ((_mi_bitmap_is_claimed(arena->blocks_inuse, arena->field_count, 1, bitmap_idx)) ? (void)0 : _mi_assert_fail("_mi_bitmap_is_claimed(arena->blocks_inuse, arena->field_count, 1, bitmap_idx)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",161,__func__));
}
# 171 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c"
void _mi_arena_field_cursor_init(mi_heap_t* heap, mi_subproc_t* subproc, bool visit_all, mi_arena_field_cursor_t* current) {
  ((heap == 0 || heap->tld->segments.subproc == subproc) ? (void)0 : _mi_assert_fail("heap == NULL || heap->tld->segments.subproc == subproc","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",172,__func__));
  current->bitmap_idx = 0;
  current->subproc = subproc;
  current->visit_all = visit_all;
  current->hold_visit_lock = 0;
  const size_t abandoned_count = atomic_load_explicit(&subproc->abandoned_count,memory_order_relaxed);
  const size_t abandoned_list_count = atomic_load_explicit(&subproc->abandoned_os_list_count,memory_order_relaxed);
  const size_t max_arena = mi_arena_get_count();
  if (heap != 0 && heap->arena_id != _mi_arena_id_none()) {

    current->start = mi_arena_id_index(heap->arena_id);
    current->end = current->start + 1;
    current->os_list_count = 0;
  }
  else {

    if (abandoned_count > abandoned_list_count && max_arena > 0) {
      current->start = (heap == 0 || max_arena == 0 ? 0 : (mi_arena_id_t)(_mi_heap_random_next(heap) % max_arena));
      current->end = current->start + max_arena;
    }
    else {
      current->start = 0;
      current->end = 0;
    }
    current->os_list_count = abandoned_list_count;
  }
  ((current->start <= max_arena) ? (void)0 : _mi_assert_fail("current->start <= max_arena","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",198,__func__));
}

void _mi_arena_field_cursor_done(mi_arena_field_cursor_t* current) {
  if (current->hold_visit_lock) {
    mi_lock_release(&current->subproc->abandoned_os_visit_lock);
    current->hold_visit_lock = 0;
  }
}

static mi_segment_t* mi_arena_segment_clear_abandoned_at(mi_arena_t* arena, mi_subproc_t* subproc, mi_bitmap_index_t bitmap_idx) {

  if (!_mi_bitmap_unclaim(arena->blocks_abandoned, arena->field_count, 1, bitmap_idx)) return 0;
  ((_mi_bitmap_is_claimed(arena->blocks_inuse, arena->field_count, 1, bitmap_idx)) ? (void)0 : _mi_assert_fail("_mi_bitmap_is_claimed(arena->blocks_inuse, arena->field_count, 1, bitmap_idx)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",211,__func__));
  mi_segment_t* segment = (mi_segment_t*)mi_arena_block_start(arena, bitmap_idx);
  ((atomic_load_explicit(&segment->thread_id,memory_order_relaxed) == 0) ? (void)0 : _mi_assert_fail("mi_atomic_load_relaxed(&segment->thread_id) == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",213,__func__));




  if (segment->subproc != subproc) {

    const bool was_zero = _mi_bitmap_claim(arena->blocks_abandoned, arena->field_count, 1, bitmap_idx, 0);
    ((was_zero) ? (void)0 : _mi_assert_fail("was_zero","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",221,__func__)); (void)(was_zero);
    return 0;
  }
  else {

    atomic_fetch_sub_explicit(&subproc->abandoned_count,(uintptr_t)1,memory_order_relaxed);
    return segment;
  }
}

static mi_segment_t* mi_arena_segment_clear_abandoned_next_field(mi_arena_field_cursor_t* previous) {
  const size_t max_arena = mi_arena_get_count();
  size_t field_idx = mi_bitmap_index_field(previous->bitmap_idx);
  size_t bit_idx = mi_bitmap_index_bit_in_field(previous->bitmap_idx);

  for (; previous->start < previous->end; previous->start++, field_idx = 0, bit_idx = 0) {

    size_t arena_idx = (previous->start >= max_arena ? previous->start % max_arena : previous->start);
    mi_arena_t* arena = mi_arena_from_index(arena_idx);
    if (arena != 0) {
      bool has_lock = 0;

      for (; field_idx < arena->field_count; field_idx++, bit_idx = 0) {
        size_t field = atomic_load_explicit(&arena->blocks_abandoned[field_idx],memory_order_relaxed);
        if (__builtin_expect(!!(field != 0),0)) {

          if (!has_lock && mi_option_is_enabled(mi_option_visit_abandoned)) {
            has_lock = (previous->visit_all ? (mi_lock_acquire(&arena->abandoned_visit_lock),1) : mi_lock_try_acquire(&arena->abandoned_visit_lock));
            if (!has_lock) {
              if (previous->visit_all) {
                _mi_error_message((14), "internal error: failed to visit all abandoned segments due to failure to acquire the visitor lock");
              }

              break;
            }
          }
          ((has_lock || !mi_option_is_enabled(mi_option_visit_abandoned)) ? (void)0 : _mi_assert_fail("has_lock || !mi_option_is_enabled(mi_option_visit_abandoned)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",257,__func__));

          for (; bit_idx < (8*(1<<(3))); bit_idx++) {

            size_t mask = ((size_t)1 << bit_idx);
            if (__builtin_expect(!!((field & mask) == mask),0)) {
              mi_bitmap_index_t bitmap_idx = mi_bitmap_index_create(field_idx, bit_idx);
              mi_segment_t* const segment = mi_arena_segment_clear_abandoned_at(arena, previous->subproc, bitmap_idx);
              if (segment != 0) {

                if (has_lock) { mi_lock_release(&arena->abandoned_visit_lock); }
                previous->bitmap_idx = mi_bitmap_index_create_ex(field_idx, bit_idx + 1);
                return segment;
              }
            }
          }
        }
      }
      if (has_lock) { mi_lock_release(&arena->abandoned_visit_lock); }
    }
  }
  return 0;
}

static mi_segment_t* mi_arena_segment_clear_abandoned_next_list(mi_arena_field_cursor_t* previous) {



  if (!previous->hold_visit_lock) {
    previous->hold_visit_lock = (previous->visit_all ? (mi_lock_acquire(&previous->subproc->abandoned_os_visit_lock),1)
                                                     : mi_lock_try_acquire(&previous->subproc->abandoned_os_visit_lock));
    if (!previous->hold_visit_lock) {
      if (previous->visit_all) {
        _mi_error_message((14), "internal error: failed to visit all abandoned segments due to failure to acquire the OS visitor lock");
      }
      return 0;
    }
  }

  while (previous->os_list_count > 0) {
    previous->os_list_count--;
    mi_lock_acquire(&previous->subproc->abandoned_os_lock);
    mi_segment_t* segment = previous->subproc->abandoned_os_list;

    if (segment == 0 || mi_arena_segment_os_clear_abandoned(segment, 0 )) {
      mi_lock_release(&previous->subproc->abandoned_os_lock);
      return segment;
    }

    mi_lock_release(&previous->subproc->abandoned_os_lock);
  }

  ((previous->os_list_count == 0) ? (void)0 : _mi_assert_fail("previous->os_list_count == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",309,__func__));
  return 0;
}




mi_segment_t* _mi_arena_segment_clear_abandoned_next(mi_arena_field_cursor_t* previous) {
  if (previous->start < previous->end) {

    mi_segment_t* segment = mi_arena_segment_clear_abandoned_next_field(previous);
    if (segment != 0) { return segment; }
  }

  ((previous->start == previous->end) ? (void)0 : _mi_assert_fail("previous->start == previous->end","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/arena-abandon.c",323,__func__));
  return mi_arena_segment_clear_abandoned_next_list(previous);
}


bool mi_abandoned_visit_blocks(mi_subproc_id_t subproc_id, int heap_tag, bool visit_blocks, mi_block_visit_fun* visitor, void* arg) {


  if (!mi_option_is_enabled(mi_option_visit_abandoned)) {
    _mi_error_message((14), "internal error: can only visit abandoned blocks when MIMALLOC_VISIT_ABANDONED=ON");
    return 0;
  }
  mi_arena_field_cursor_t current;
  _mi_arena_field_cursor_init(0, _mi_subproc_from_id(subproc_id), 1 , &current);
  mi_segment_t* segment;
  bool ok = 1;
  while (ok && (segment = _mi_arena_segment_clear_abandoned_next(&current)) != 0) {
    ok = _mi_segment_visit_blocks(segment, heap_tag, visit_blocks, visitor, arg);
    _mi_arena_segment_mark_abandoned(segment);
  }
  _mi_arena_field_cursor_done(&current);
  return ok;
}
