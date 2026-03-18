# 0 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c"






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
# 109 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc.h"
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
# 177 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc.h"
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
# 233 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc.h"
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
 bool mi_manage_os_memory(void* start, size_t size, bool is_committed, bool is_pinned , bool is_zero, int numa_node) ;

 void mi_debug_show_arenas(void) ;
 void mi_arenas_print(void) ;
 size_t mi_arena_min_alignment(void);


typedef void* mi_arena_id_t;
 void* mi_arena_area(mi_arena_id_t arena_id, size_t* size);
 int mi_reserve_huge_os_pages_at_ex(size_t pages, int numa_node, size_t timeout_msecs, bool exclusive, mi_arena_id_t* arena_id) ;
 int mi_reserve_os_memory_ex(size_t size, bool commit, bool allow_large, bool exclusive, mi_arena_id_t* arena_id) ;
 bool mi_manage_os_memory_ex(void* start, size_t size, bool is_committed, bool is_pinned, bool is_zero, int numa_node, bool exclusive, mi_arena_id_t* arena_id) ;



 mi_heap_t* mi_heap_new_in_arena(mi_arena_id_t arena_id);





typedef void* mi_subproc_id_t;
 mi_subproc_id_t mi_subproc_main(void);
 mi_subproc_id_t mi_subproc_new(void);
 void mi_subproc_delete(mi_subproc_id_t subproc);
 void mi_subproc_add_current_thread(mi_subproc_id_t subproc);


 bool mi_abandoned_visit_blocks(mi_subproc_id_t subproc_id, int heap_tag, bool visit_blocks, mi_block_visit_fun* visitor, void* arg);


 void mi_heap_set_numa_affinity(mi_heap_t* heap, int numa_node);






 void mi_heap_guarded_set_sample_rate(mi_heap_t* heap, size_t sample_rate, size_t seed);
 void mi_heap_guarded_set_size_bound(mi_heap_t* heap, size_t min, size_t max);


 void mi_thread_set_in_threadpool(void) ;




 mi_heap_t* mi_heap_new_ex(int heap_tag, bool allow_destroy, mi_arena_id_t arena_id);


 int mi_reserve_huge_os_pages(size_t pages, double max_secs, size_t* pages_reserved) ;
 void mi_collect_reduce(size_t target_thread_owned) ;




typedef bool ( mi_commit_fun_t)(bool commit, void* start, size_t size, bool* is_zero, void* user_arg);
 bool mi_manage_memory(void* start, size_t size, bool is_committed, bool is_pinned, bool is_zero, int numa_node, bool exclusive,
                                      mi_commit_fun_t* commit_fun, void* commit_fun_arg, mi_arena_id_t* arena_id) ;

 bool mi_arena_unload(mi_arena_id_t arena_id, void** base, size_t* accessed_size, size_t* size);
 bool mi_arena_reload(void* start, size_t size, mi_commit_fun_t* commit_fun, void* commit_fun_arg, mi_arena_id_t* arena_id);
 bool mi_heap_reload(mi_heap_t* heap, mi_arena_id_t arena);
 void mi_heap_unload(mi_heap_t* heap);



 bool mi_arena_contains(mi_arena_id_t arena_id, const void* p);
# 374 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc.h"
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
# 450 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc.h"
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
# 8 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c" 2
# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h" 1






       
# 22 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
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
# 69 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc-stats.h"
typedef enum mi_chunkbin_e {
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

  mi_stat_count_t pages; mi_stat_count_t reserved; mi_stat_count_t committed; mi_stat_count_t reset; mi_stat_count_t purged; mi_stat_count_t page_committed; mi_stat_count_t pages_abandoned; mi_stat_count_t threads; mi_stat_count_t malloc_normal; mi_stat_count_t malloc_huge; mi_stat_count_t malloc_requested; mi_stat_counter_t mmap_calls; mi_stat_counter_t commit_calls; mi_stat_counter_t reset_calls; mi_stat_counter_t purge_calls; mi_stat_counter_t arena_count; mi_stat_counter_t malloc_normal_count; mi_stat_counter_t malloc_huge_count; mi_stat_counter_t malloc_guarded_count; mi_stat_counter_t arena_rollback_count; mi_stat_counter_t arena_purges; mi_stat_counter_t pages_extended; mi_stat_counter_t pages_retire; mi_stat_counter_t page_searches; mi_stat_count_t segments; mi_stat_count_t segments_abandoned; mi_stat_count_t segments_cache; mi_stat_count_t _segments_reserved; mi_stat_counter_t pages_reclaim_on_alloc; mi_stat_counter_t pages_reclaim_on_free; mi_stat_counter_t pages_reabandon_full; mi_stat_counter_t pages_unabandon_busy_wait;


  mi_stat_count_t _stat_reserved[4];
  mi_stat_counter_t _stat_counter_reserved[4];


  mi_stat_count_t malloc_bins[(73U)+1];
  mi_stat_count_t page_bins[(73U)+1];
  mi_stat_count_t chunk_bins[MI_CBIN_COUNT];
} mi_stats_t;
# 109 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc-stats.h"
 void mi_stats_get( size_t stats_size, mi_stats_t* stats ) ;
 char* mi_stats_get_json( size_t buf_size, char* buf ) ;
 size_t mi_stats_get_bin_size(size_t bin) ;
# 23 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 24 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 25 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdbool.h" 1
# 26 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 1
# 27 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/errno.h" 1
# 28 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h" 2
# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h" 1
# 12 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h"
       



# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 17 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 18 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdbool.h" 1
# 19 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h" 2
# 50 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h"
typedef int64_t mi_ssize_t;
# 176 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h"
size_t _mi_popcount_generic(size_t x);

static inline size_t mi_popcount(size_t x) {

    return __builtin_popcountll(x);
# 189 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h"
}







size_t _mi_clz_generic(size_t x);
size_t _mi_ctz_generic(size_t x);

static inline size_t mi_ctz(size_t x) {
# 211 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h"
    return (x!=0 ? (size_t)__builtin_ctzll(x) : ((1<<(3))*8));
# 222 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h"
}

static inline size_t mi_clz(size_t x) {
# 235 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h"
    return (x!=0 ? (size_t)__builtin_clzll(x) : ((1<<(3))*8));
# 245 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h"
}
# 258 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h"
static inline bool mi_bsf(size_t x, size_t* idx) {
# 268 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h"
    return (x!=0 ? (*idx = mi_ctz(x), 1) : 0);

}




static inline bool mi_bsr(size_t x, size_t* idx) {
# 285 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h"
    return (x!=0 ? (*idx = ((1<<(3))*8) - 1 - mi_clz(x), 1) : 0);

}






static inline size_t mi_rotr(size_t x, size_t r) {
# 306 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h"
    const unsigned int rshift = (unsigned int)(r) & (((1<<(3))*8)-1);
    return ((x >> rshift) | (x << ((-rshift) & (((1<<(3))*8)-1))));

}

static inline size_t mi_rotl(size_t x, size_t r) {
# 323 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h"
    const unsigned int rshift = (unsigned int)(r) & (((1<<(3))*8)-1);
    return ((x << rshift) | (x >> ((-rshift) & (((1<<(3))*8)-1))));

}

static inline uint32_t mi_rotl32(uint32_t x, uint32_t r) {







    const unsigned int rshift = (unsigned int)(r) & 31;
    return ((x << rshift) | (x >> ((-rshift) & 31)));

}
# 29 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h" 2
# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/atomic.h" 1






       
# 19 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/atomic.h"
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/pthread.h" 1
# 20 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/atomic.h" 2
# 53 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/atomic.h"
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdatomic.h" 1
# 54 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/atomic.h" 2
# 101 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/atomic.h"
static inline void mi_atomic_yield(void);
static inline intptr_t mi_atomic_addi(_Atomic(intptr_t)*p, intptr_t add);
static inline intptr_t mi_atomic_subi(_Atomic(intptr_t)*p, intptr_t sub);
# 137 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/atomic.h"
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
# 330 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/atomic.h"
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
# 391 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/atomic.h"
static inline void mi_atomic_yield(void) {

}
# 489 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/atomic.h"
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
# 30 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h" 2
# 188 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
typedef struct mi_arena_s mi_arena_t;
# 197 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
typedef enum mi_memkind_e {
  MI_MEM_NONE,
  MI_MEM_EXTERNAL,
  MI_MEM_STATIC,
  MI_MEM_META,
  MI_MEM_OS,
  MI_MEM_OS_HUGE,
  MI_MEM_OS_REMAP,
  MI_MEM_ARENA
} mi_memkind_t;

static inline bool mi_memkind_is_os(mi_memkind_t memkind) {
  return (memkind >= MI_MEM_OS && memkind <= MI_MEM_OS_REMAP);
}

static inline bool mi_memkind_needs_no_free(mi_memkind_t memkind) {
  return (memkind <= MI_MEM_STATIC);
}


typedef struct mi_memid_os_info {
  void* base;
  size_t size;

} mi_memid_os_info_t;

typedef struct mi_memid_arena_info {
  mi_arena_t* arena;
  uint32_t slice_index;
  uint32_t slice_count;
} mi_memid_arena_info_t;

typedef struct mi_memid_meta_info {
  void* meta_page;
  uint32_t block_index;
  uint32_t block_count;
} mi_memid_meta_info_t;

typedef struct mi_memid_s {
  union {
    mi_memid_os_info_t os;
    mi_memid_arena_info_t arena;
    mi_memid_meta_info_t meta;
  } mem;
  mi_memkind_t memkind;
  bool is_pinned;
  bool initially_committed;
  bool initially_zero;
} mi_memid_t;


static inline bool mi_memid_is_os(mi_memid_t memid) {
  return mi_memkind_is_os(memid.memkind);
}

static inline bool mi_memid_needs_no_free(mi_memid_t memid) {
  return mi_memkind_needs_no_free(memid.memkind);
}

static inline mi_arena_t* mi_memid_arena(mi_memid_t memid) {
  return (memid.memkind == MI_MEM_ARENA ? memid.mem.arena.arena : 0);
}
# 267 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
typedef uintptr_t mi_encoded_t;


typedef size_t mi_threadid_t;


typedef struct mi_block_s {
  mi_encoded_t next;
} mi_block_t;
# 284 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
typedef size_t mi_page_flags_t;
# 297 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
typedef uintptr_t mi_thread_free_t;


typedef uint8_t mi_heaptag_t;
# 330 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
typedef struct mi_page_s {
  _Atomic(mi_threadid_t) xthread_id;

  mi_block_t* free;
  uint16_t used;
  uint16_t capacity;
  uint16_t reserved;
  uint8_t retire_expire;

  mi_block_t* local_free;
  _Atomic(mi_thread_free_t) xthread_free;

  size_t block_size;
  uint8_t* page_start;
  mi_heaptag_t heap_tag;
  bool free_is_zero;


  uintptr_t keys[2];


  mi_heap_t* heap;
  struct mi_page_s* next;
  struct mi_page_s* prev;
  size_t slice_committed;
  mi_memid_t memid;
} mi_page_t;
# 394 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
typedef enum mi_page_kind_e {
  MI_PAGE_SMALL,
  MI_PAGE_MEDIUM,
  MI_PAGE_LARGE,
  MI_PAGE_SINGLETON

} mi_page_kind_t;
# 419 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
typedef struct mi_tld_s mi_tld_t;


typedef struct mi_page_queue_s {
  mi_page_t* first;
  mi_page_t* last;
  size_t count;
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
# 455 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
struct mi_heap_s {
  mi_tld_t* tld;
  mi_arena_t* exclusive_arena;
  int numa_node;
  uintptr_t cookie;
  mi_random_ctx_t random;
  size_t page_count;
  size_t page_retired_min;
  size_t page_retired_max;
  long generic_count;
  long generic_collect_count;
  mi_heap_t* next;
  long page_full_retain;
  bool allow_page_reclaim;
  bool allow_page_abandon;
  uint8_t tag;






  mi_page_t* pages_free_direct[((128) + (((sizeof(mi_padding_t)) + (1<<(3)) - 1) / (1<<(3))) + 1)];
  mi_page_queue_t pages[(((73U)+1)+1)];
  mi_memid_t memid;
};
# 494 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
typedef struct mi_subproc_s {
  _Atomic(size_t) arena_count;
  _Atomic(mi_arena_t*) arenas[(160)];
  pthread_mutex_t arena_reserve_lock;
  _Atomic(int64_t) purge_expire;

  _Atomic(size_t) abandoned_count[(((73U)+1)+1)];
  mi_page_t* os_abandoned_pages;
  pthread_mutex_t os_abandoned_pages_lock;

  mi_memid_t memid;
  mi_stats_t stats;
} mi_subproc_t;
# 515 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
typedef int64_t mi_msecs_t;


struct mi_tld_s {
  mi_threadid_t thread_id;
  size_t thread_seq;
  int numa_node;
  mi_subproc_t* subproc;
  mi_heap_t* heap_backing;
  mi_heap_t* heaps;
  unsigned long long heartbeat;
  bool recurse;
  bool is_in_threadpool;
  mi_stats_t stats;
  mi_memid_t memid;
};
# 549 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
typedef struct mi_bitmap_s mi_bitmap_t;
typedef struct mi_bbitmap_s mi_bbitmap_t;


typedef struct mi_arena_s {
  mi_memid_t memid;
  mi_subproc_t* subproc;

  size_t slice_count;
  size_t info_slices;
  int numa_node;
  bool is_exclusive;
  _Atomic(mi_msecs_t) purge_expire;
  mi_commit_fun_t* commit_fun;
  void* commit_fun_arg;

  mi_bbitmap_t* slices_free;
  mi_bitmap_t* slices_committed;
  mi_bitmap_t* slices_dirty;
  mi_bitmap_t* slices_purge;
  mi_bitmap_t* pages;
  mi_bitmap_t* pages_abandoned[((((73U)+1)+1))];



} mi_arena_t;
# 9 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c" 2

# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/testhelper.h" 1
# 10 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/testhelper.h"
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdbool.h" 1
# 11 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/testhelper.h" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 12 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/testhelper.h" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/errno.h" 1
# 13 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/testhelper.h" 2




static int ok = 0;
static int failed = 0;

static bool check_result(bool result, const char* testname, const char* fname, long lineno) {
  if (!(result)) {
    failed++;
    fprintf(stderr,"\n  FAILED: %s: %s:%ld\n", testname, fname, lineno);

  }
  else {
    ok++;
    fprintf(stderr, "ok.\n");
  }
  return 1;
}
# 41 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/testhelper.h"
static inline int print_test_summary(void)
{
  fprintf(stderr,"\n\n---------------------------------------------\n"
                 "succeeded: %i\n"
                 "failed   : %i\n\n", ok, failed);
  return failed;
}
# 11 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c" 2




bool check_zero_init(uint8_t* p, size_t size);

bool check_debug_fill_uninit(uint8_t* p, size_t size);
bool check_debug_fill_freed(uint8_t* p, size_t size);





int main(void) {
  mi_option_disable(mi_option_verbose);




  fprintf(stderr,"test: %s...  ", "zeroinit-zalloc-small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-zalloc-small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",30)) {
    size_t zalloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_zalloc(zalloc_size);
    result = check_zero_init(p, zalloc_size);
    mi_free(p);
  };
  fprintf(stderr,"test: %s...  ", "zeroinit-zalloc-large" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-zalloc-large","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",36)) {
    size_t zalloc_size = ((128)*sizeof(void*)) * 2;
    uint8_t* p = (uint8_t*)mi_zalloc(zalloc_size);
    result = check_zero_init(p, zalloc_size);
    mi_free(p);
  };
  fprintf(stderr,"test: %s...  ", "zeroinit-zalloc_small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-zalloc_small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",42)) {
    size_t zalloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_zalloc_small(zalloc_size);
    result = check_zero_init(p, zalloc_size);
    mi_free(p);
  };

  fprintf(stderr,"test: %s...  ", "zeroinit-calloc-small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-calloc-small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",49)) {
    size_t calloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_calloc(calloc_size, 1);
    result = check_zero_init(p, calloc_size);
    mi_free(p);
  };
  fprintf(stderr,"test: %s...  ", "zeroinit-calloc-large" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-calloc-large","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",55)) {
    size_t calloc_size = ((128)*sizeof(void*)) * 2;
    uint8_t* p = (uint8_t*)mi_calloc(calloc_size, 1);
    result = check_zero_init(p, calloc_size);
    mi_free(p);
  };

  fprintf(stderr,"test: %s...  ", "zeroinit-rezalloc-small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-rezalloc-small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",62)) {
    size_t zalloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_zalloc(zalloc_size);
    result = check_zero_init(p, zalloc_size);
    zalloc_size *= 3;
    p = (uint8_t*)mi_rezalloc(p, zalloc_size);
    result &= check_zero_init(p, zalloc_size);
    mi_free(p);
  };
  fprintf(stderr,"test: %s...  ", "zeroinit-rezalloc-large" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-rezalloc-large","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",71)) {
    size_t zalloc_size = ((128)*sizeof(void*)) * 2;
    uint8_t* p = (uint8_t*)mi_zalloc(zalloc_size);
    result = check_zero_init(p, zalloc_size);
    zalloc_size *= 3;
    p = (uint8_t*)mi_rezalloc(p, zalloc_size);
    result &= check_zero_init(p, zalloc_size);
    mi_free(p);
  };

  fprintf(stderr,"test: %s...  ", "zeroinit-recalloc-small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-recalloc-small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",81)) {
    size_t calloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_calloc(calloc_size, 1);
    result = check_zero_init(p, calloc_size);
    calloc_size *= 3;
    p = (uint8_t*)mi_recalloc(p, calloc_size, 1);
    result &= check_zero_init(p, calloc_size);
    mi_free(p);
  };
  fprintf(stderr,"test: %s...  ", "zeroinit-recalloc-large" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-recalloc-large","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",90)) {
    size_t calloc_size = ((128)*sizeof(void*)) * 2;
    uint8_t* p = (uint8_t*)mi_calloc(calloc_size, 1);
    result = check_zero_init(p, calloc_size);
    calloc_size *= 3;
    p = (uint8_t*)mi_recalloc(p, calloc_size, 1);
    result &= check_zero_init(p, calloc_size);
    mi_free(p);
  };




  fprintf(stderr,"test: %s...  ", "zeroinit-zalloc_aligned-small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-zalloc_aligned-small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",103)) {
    size_t zalloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_zalloc_aligned(zalloc_size, 16 * 2);
    result = check_zero_init(p, zalloc_size);
    mi_free(p);
  };
  fprintf(stderr,"test: %s...  ", "zeroinit-zalloc_aligned-large" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-zalloc_aligned-large","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",109)) {
    size_t zalloc_size = ((128)*sizeof(void*)) * 2;
    uint8_t* p = (uint8_t*)mi_zalloc_aligned(zalloc_size, 16 * 2);
    result = check_zero_init(p, zalloc_size);
    mi_free(p);
  };

  fprintf(stderr,"test: %s...  ", "zeroinit-calloc_aligned-small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-calloc_aligned-small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",116)) {
    size_t calloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_calloc_aligned(calloc_size, 1, 16 * 2);
    result = check_zero_init(p, calloc_size);
    mi_free(p);
  };
  fprintf(stderr,"test: %s...  ", "zeroinit-calloc_aligned-large" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-calloc_aligned-large","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",122)) {
    size_t calloc_size = ((128)*sizeof(void*)) * 2;
    uint8_t* p = (uint8_t*)mi_calloc_aligned(calloc_size, 1, 16 * 2);
    result = check_zero_init(p, calloc_size);
    mi_free(p);
  };

  fprintf(stderr,"test: %s...  ", "zeroinit-rezalloc_aligned-small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-rezalloc_aligned-small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",129)) {
    size_t zalloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_zalloc_aligned(zalloc_size, 16 * 2);
    result = check_zero_init(p, zalloc_size);
    zalloc_size *= 3;
    p = (uint8_t*)mi_rezalloc_aligned(p, zalloc_size, 16 * 2);
    result &= check_zero_init(p, zalloc_size);
    mi_free(p);
  };
  fprintf(stderr,"test: %s...  ", "zeroinit-rezalloc_aligned-large" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-rezalloc_aligned-large","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",138)) {
    size_t zalloc_size = ((128)*sizeof(void*)) * 2;
    uint8_t* p = (uint8_t*)mi_zalloc_aligned(zalloc_size, 16 * 2);
    result = check_zero_init(p, zalloc_size);
    zalloc_size *= 3;
    p = (uint8_t*)mi_rezalloc_aligned(p, zalloc_size, 16 * 2);
    result &= check_zero_init(p, zalloc_size);
    mi_free(p);
  };

  fprintf(stderr,"test: %s...  ", "zeroinit-recalloc_aligned-small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-recalloc_aligned-small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",148)) {
    size_t calloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_calloc_aligned(calloc_size, 1, 16 * 2);
    result = check_zero_init(p, calloc_size);
    calloc_size *= 3;
    p = (uint8_t*)mi_recalloc_aligned(p, calloc_size, 1, 16 * 2);
    result &= check_zero_init(p, calloc_size);
    mi_free(p);
  };
  fprintf(stderr,"test: %s...  ", "zeroinit-recalloc_aligned-large" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-recalloc_aligned-large","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",157)) {
    size_t calloc_size = ((128)*sizeof(void*)) * 2;
    uint8_t* p = (uint8_t*)mi_calloc_aligned(calloc_size, 1, 16 * 2);
    result = check_zero_init(p, calloc_size);
    calloc_size *= 3;
    p = (uint8_t*)mi_recalloc_aligned(p, calloc_size, 1, 16 * 2);
    result &= check_zero_init(p, calloc_size);
    mi_free(p);
  };





  fprintf(stderr,"test: %s...  ", "uninit-malloc-small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"uninit-malloc-small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",171)) {
    size_t malloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_malloc(malloc_size);
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  };
  fprintf(stderr,"test: %s...  ", "uninit-malloc-large" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"uninit-malloc-large","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",177)) {
    size_t malloc_size = ((128)*sizeof(void*)) * 2;
    uint8_t* p = (uint8_t*)mi_malloc(malloc_size);
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  };

  fprintf(stderr,"test: %s...  ", "uninit-malloc_small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"uninit-malloc_small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",184)) {
    size_t malloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_malloc_small(malloc_size);
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  };

  fprintf(stderr,"test: %s...  ", "uninit-realloc-small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"uninit-realloc-small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",191)) {
    size_t malloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_malloc(malloc_size);
    result = check_debug_fill_uninit(p, malloc_size);
    malloc_size *= 3;
    p = (uint8_t*)mi_realloc(p, malloc_size);
    result &= check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  };
  fprintf(stderr,"test: %s...  ", "uninit-realloc-large" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"uninit-realloc-large","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",200)) {
    size_t malloc_size = ((128)*sizeof(void*)) * 2;
    uint8_t* p = (uint8_t*)mi_malloc(malloc_size);
    result = check_debug_fill_uninit(p, malloc_size);
    malloc_size *= 3;
    p = (uint8_t*)mi_realloc(p, malloc_size);
    result &= check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  };

  fprintf(stderr,"test: %s...  ", "uninit-mallocn-small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"uninit-mallocn-small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",210)) {
    size_t malloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_mallocn(malloc_size, 1);
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  };
  fprintf(stderr,"test: %s...  ", "uninit-mallocn-large" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"uninit-mallocn-large","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",216)) {
    size_t malloc_size = ((128)*sizeof(void*)) * 2;
    uint8_t* p = (uint8_t*)mi_mallocn(malloc_size, 1);
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  };

  fprintf(stderr,"test: %s...  ", "uninit-reallocn-small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"uninit-reallocn-small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",223)) {
    size_t malloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_mallocn(malloc_size, 1);
    result = check_debug_fill_uninit(p, malloc_size);
    malloc_size *= 3;
    p = (uint8_t*)mi_reallocn(p, malloc_size, 1);
    result &= check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  };
  fprintf(stderr,"test: %s...  ", "uninit-reallocn-large" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"uninit-reallocn-large","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",232)) {
    size_t malloc_size = ((128)*sizeof(void*)) * 2;
    uint8_t* p = (uint8_t*)mi_mallocn(malloc_size, 1);
    result = check_debug_fill_uninit(p, malloc_size);
    malloc_size *= 3;
    p = (uint8_t*)mi_reallocn(p, malloc_size, 1);
    result &= check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  };

  fprintf(stderr,"test: %s...  ", "uninit-malloc_aligned-small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"uninit-malloc_aligned-small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",242)) {
    size_t malloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_malloc_aligned(malloc_size, 16 * 2);
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  };
  fprintf(stderr,"test: %s...  ", "uninit-malloc_aligned-large" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"uninit-malloc_aligned-large","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",248)) {
    size_t malloc_size = ((128)*sizeof(void*)) * 2;
    uint8_t* p = (uint8_t*)mi_malloc_aligned(malloc_size, 16 * 2);
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  };

  fprintf(stderr,"test: %s...  ", "uninit-realloc_aligned-small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"uninit-realloc_aligned-small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",255)) {
    size_t malloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_malloc_aligned(malloc_size, 16 * 2);
    result = check_debug_fill_uninit(p, malloc_size);
    malloc_size *= 3;
    p = (uint8_t*)mi_realloc_aligned(p, malloc_size, 16 * 2);
    result &= check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  };
  fprintf(stderr,"test: %s...  ", "uninit-realloc_aligned-large" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"uninit-realloc_aligned-large","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",264)) {
    size_t malloc_size = ((128)*sizeof(void*)) * 2;
    uint8_t* p = (uint8_t*)mi_malloc_aligned(malloc_size, 16 * 2);
    result = check_debug_fill_uninit(p, malloc_size);
    malloc_size *= 3;
    p = (uint8_t*)mi_realloc_aligned(p, malloc_size, 16 * 2);
    result &= check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  };


  fprintf(stderr,"test: %s...  ", "fill-freed-small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"fill-freed-small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",275)) {
    size_t malloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_malloc(malloc_size);
    mi_free(p);

    result = check_debug_fill_freed(p + sizeof(void*), malloc_size - sizeof(void*));
  };
  fprintf(stderr,"test: %s...  ", "fill-freed-large" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"fill-freed-large","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",282)) {
    size_t malloc_size = ((128)*sizeof(void*)) * 2;
    uint8_t* p = (uint8_t*)mi_malloc(malloc_size);
    mi_free(p);

    result = check_debug_fill_freed(p + sizeof(void*), malloc_size - sizeof(void*));
  };






  return print_test_summary();
}




bool check_zero_init(uint8_t* p, size_t size) {
  if(!p)
    return 0;
  bool result = 1;
  for (size_t i = 0; i < size; ++i) {
    result &= p[i] == 0;
  }
  return result;
}


bool check_debug_fill_uninit(uint8_t* p, size_t size) {




  if(!p)
    return 0;

  bool result = 1;
  for (size_t i = 0; i < size; ++i) {
    result &= p[i] == (0xD0);
  }
  return result;

}

bool check_debug_fill_freed(uint8_t* p, size_t size) {




  if(!p)
    return 0;

  bool result = 1;
  for (size_t i = 0; i < size; ++i) {
    result &= p[i] == (0xDF);
  }
  return result;

}
# 0 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c"






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
# 109 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc.h"
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
# 177 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc.h"
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
# 233 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc.h"
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
 bool mi_manage_os_memory(void* start, size_t size, bool is_committed, bool is_pinned , bool is_zero, int numa_node) ;

 void mi_debug_show_arenas(void) ;
 void mi_arenas_print(void) ;
 size_t mi_arena_min_alignment(void);


typedef void* mi_arena_id_t;
 void* mi_arena_area(mi_arena_id_t arena_id, size_t* size);
 int mi_reserve_huge_os_pages_at_ex(size_t pages, int numa_node, size_t timeout_msecs, bool exclusive, mi_arena_id_t* arena_id) ;
 int mi_reserve_os_memory_ex(size_t size, bool commit, bool allow_large, bool exclusive, mi_arena_id_t* arena_id) ;
 bool mi_manage_os_memory_ex(void* start, size_t size, bool is_committed, bool is_pinned, bool is_zero, int numa_node, bool exclusive, mi_arena_id_t* arena_id) ;



 mi_heap_t* mi_heap_new_in_arena(mi_arena_id_t arena_id);





typedef void* mi_subproc_id_t;
 mi_subproc_id_t mi_subproc_main(void);
 mi_subproc_id_t mi_subproc_new(void);
 void mi_subproc_delete(mi_subproc_id_t subproc);
 void mi_subproc_add_current_thread(mi_subproc_id_t subproc);


 bool mi_abandoned_visit_blocks(mi_subproc_id_t subproc_id, int heap_tag, bool visit_blocks, mi_block_visit_fun* visitor, void* arg);


 void mi_heap_set_numa_affinity(mi_heap_t* heap, int numa_node);






 void mi_heap_guarded_set_sample_rate(mi_heap_t* heap, size_t sample_rate, size_t seed);
 void mi_heap_guarded_set_size_bound(mi_heap_t* heap, size_t min, size_t max);


 void mi_thread_set_in_threadpool(void) ;




 mi_heap_t* mi_heap_new_ex(int heap_tag, bool allow_destroy, mi_arena_id_t arena_id);


 int mi_reserve_huge_os_pages(size_t pages, double max_secs, size_t* pages_reserved) ;
 void mi_collect_reduce(size_t target_thread_owned) ;




typedef bool ( mi_commit_fun_t)(bool commit, void* start, size_t size, bool* is_zero, void* user_arg);
 bool mi_manage_memory(void* start, size_t size, bool is_committed, bool is_pinned, bool is_zero, int numa_node, bool exclusive,
                                      mi_commit_fun_t* commit_fun, void* commit_fun_arg, mi_arena_id_t* arena_id) ;

 bool mi_arena_unload(mi_arena_id_t arena_id, void** base, size_t* accessed_size, size_t* size);
 bool mi_arena_reload(void* start, size_t size, mi_commit_fun_t* commit_fun, void* commit_fun_arg, mi_arena_id_t* arena_id);
 bool mi_heap_reload(mi_heap_t* heap, mi_arena_id_t arena);
 void mi_heap_unload(mi_heap_t* heap);



 bool mi_arena_contains(mi_arena_id_t arena_id, const void* p);
# 374 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc.h"
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
# 450 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc.h"
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
# 8 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c" 2
# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h" 1






       
# 22 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
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
# 69 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc-stats.h"
typedef enum mi_chunkbin_e {
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

  mi_stat_count_t pages; mi_stat_count_t reserved; mi_stat_count_t committed; mi_stat_count_t reset; mi_stat_count_t purged; mi_stat_count_t page_committed; mi_stat_count_t pages_abandoned; mi_stat_count_t threads; mi_stat_count_t malloc_normal; mi_stat_count_t malloc_huge; mi_stat_count_t malloc_requested; mi_stat_counter_t mmap_calls; mi_stat_counter_t commit_calls; mi_stat_counter_t reset_calls; mi_stat_counter_t purge_calls; mi_stat_counter_t arena_count; mi_stat_counter_t malloc_normal_count; mi_stat_counter_t malloc_huge_count; mi_stat_counter_t malloc_guarded_count; mi_stat_counter_t arena_rollback_count; mi_stat_counter_t arena_purges; mi_stat_counter_t pages_extended; mi_stat_counter_t pages_retire; mi_stat_counter_t page_searches; mi_stat_count_t segments; mi_stat_count_t segments_abandoned; mi_stat_count_t segments_cache; mi_stat_count_t _segments_reserved; mi_stat_counter_t pages_reclaim_on_alloc; mi_stat_counter_t pages_reclaim_on_free; mi_stat_counter_t pages_reabandon_full; mi_stat_counter_t pages_unabandon_busy_wait;


  mi_stat_count_t _stat_reserved[4];
  mi_stat_counter_t _stat_counter_reserved[4];


  mi_stat_count_t malloc_bins[(73U)+1];
  mi_stat_count_t page_bins[(73U)+1];
  mi_stat_count_t chunk_bins[MI_CBIN_COUNT];
} mi_stats_t;
# 109 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc-stats.h"
 void mi_stats_get( size_t stats_size, mi_stats_t* stats ) ;
 char* mi_stats_get_json( size_t buf_size, char* buf ) ;
 size_t mi_stats_get_bin_size(size_t bin) ;
# 23 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 24 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 25 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdbool.h" 1
# 26 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 1
# 27 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/errno.h" 1
# 28 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h" 2
# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h" 1
# 12 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h"
       



# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 17 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 18 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdbool.h" 1
# 19 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h" 2
# 50 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h"
typedef int64_t mi_ssize_t;
# 176 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h"
size_t _mi_popcount_generic(size_t x);

static inline size_t mi_popcount(size_t x) {

    return __builtin_popcountll(x);
# 189 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h"
}







size_t _mi_clz_generic(size_t x);
size_t _mi_ctz_generic(size_t x);

static inline size_t mi_ctz(size_t x) {
# 211 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h"
    return (x!=0 ? (size_t)__builtin_ctzll(x) : ((1<<(3))*8));
# 222 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h"
}

static inline size_t mi_clz(size_t x) {
# 235 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h"
    return (x!=0 ? (size_t)__builtin_clzll(x) : ((1<<(3))*8));
# 245 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h"
}
# 258 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h"
static inline bool mi_bsf(size_t x, size_t* idx) {
# 268 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h"
    return (x!=0 ? (*idx = mi_ctz(x), 1) : 0);

}




static inline bool mi_bsr(size_t x, size_t* idx) {
# 285 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h"
    return (x!=0 ? (*idx = ((1<<(3))*8) - 1 - mi_clz(x), 1) : 0);

}






static inline size_t mi_rotr(size_t x, size_t r) {
# 306 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h"
    const unsigned int rshift = (unsigned int)(r) & (((1<<(3))*8)-1);
    return ((x >> rshift) | (x << ((-rshift) & (((1<<(3))*8)-1))));

}

static inline size_t mi_rotl(size_t x, size_t r) {
# 323 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/bits.h"
    const unsigned int rshift = (unsigned int)(r) & (((1<<(3))*8)-1);
    return ((x << rshift) | (x >> ((-rshift) & (((1<<(3))*8)-1))));

}

static inline uint32_t mi_rotl32(uint32_t x, uint32_t r) {







    const unsigned int rshift = (unsigned int)(r) & 31;
    return ((x << rshift) | (x >> ((-rshift) & 31)));

}
# 29 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h" 2
# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/atomic.h" 1






       
# 19 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/atomic.h"
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/pthread.h" 1
# 20 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/atomic.h" 2
# 53 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/atomic.h"
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdatomic.h" 1
# 54 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/atomic.h" 2
# 101 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/atomic.h"
static inline void mi_atomic_yield(void);
static inline intptr_t mi_atomic_addi(_Atomic(intptr_t)*p, intptr_t add);
static inline intptr_t mi_atomic_subi(_Atomic(intptr_t)*p, intptr_t sub);
# 137 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/atomic.h"
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
# 330 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/atomic.h"
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
# 391 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/atomic.h"
static inline void mi_atomic_yield(void) {

}
# 489 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/atomic.h"
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
# 30 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h" 2
# 188 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
typedef struct mi_arena_s mi_arena_t;
# 197 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
typedef enum mi_memkind_e {
  MI_MEM_NONE,
  MI_MEM_EXTERNAL,
  MI_MEM_STATIC,
  MI_MEM_META,
  MI_MEM_OS,
  MI_MEM_OS_HUGE,
  MI_MEM_OS_REMAP,
  MI_MEM_ARENA
} mi_memkind_t;

static inline bool mi_memkind_is_os(mi_memkind_t memkind) {
  return (memkind >= MI_MEM_OS && memkind <= MI_MEM_OS_REMAP);
}

static inline bool mi_memkind_needs_no_free(mi_memkind_t memkind) {
  return (memkind <= MI_MEM_STATIC);
}


typedef struct mi_memid_os_info {
  void* base;
  size_t size;

} mi_memid_os_info_t;

typedef struct mi_memid_arena_info {
  mi_arena_t* arena;
  uint32_t slice_index;
  uint32_t slice_count;
} mi_memid_arena_info_t;

typedef struct mi_memid_meta_info {
  void* meta_page;
  uint32_t block_index;
  uint32_t block_count;
} mi_memid_meta_info_t;

typedef struct mi_memid_s {
  union {
    mi_memid_os_info_t os;
    mi_memid_arena_info_t arena;
    mi_memid_meta_info_t meta;
  } mem;
  mi_memkind_t memkind;
  bool is_pinned;
  bool initially_committed;
  bool initially_zero;
} mi_memid_t;


static inline bool mi_memid_is_os(mi_memid_t memid) {
  return mi_memkind_is_os(memid.memkind);
}

static inline bool mi_memid_needs_no_free(mi_memid_t memid) {
  return mi_memkind_needs_no_free(memid.memkind);
}

static inline mi_arena_t* mi_memid_arena(mi_memid_t memid) {
  return (memid.memkind == MI_MEM_ARENA ? memid.mem.arena.arena : 0);
}
# 267 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
typedef uintptr_t mi_encoded_t;


typedef size_t mi_threadid_t;


typedef struct mi_block_s {
  mi_encoded_t next;
} mi_block_t;
# 284 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
typedef size_t mi_page_flags_t;
# 297 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
typedef uintptr_t mi_thread_free_t;


typedef uint8_t mi_heaptag_t;
# 330 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
typedef struct mi_page_s {
  _Atomic(mi_threadid_t) xthread_id;

  mi_block_t* free;
  uint16_t used;
  uint16_t capacity;
  uint16_t reserved;
  uint8_t retire_expire;

  mi_block_t* local_free;
  _Atomic(mi_thread_free_t) xthread_free;

  size_t block_size;
  uint8_t* page_start;
  mi_heaptag_t heap_tag;
  bool free_is_zero;


  uintptr_t keys[2];


  mi_heap_t* heap;
  struct mi_page_s* next;
  struct mi_page_s* prev;
  size_t slice_committed;
  mi_memid_t memid;
} mi_page_t;
# 394 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
typedef enum mi_page_kind_e {
  MI_PAGE_SMALL,
  MI_PAGE_MEDIUM,
  MI_PAGE_LARGE,
  MI_PAGE_SINGLETON

} mi_page_kind_t;
# 419 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
typedef struct mi_tld_s mi_tld_t;


typedef struct mi_page_queue_s {
  mi_page_t* first;
  mi_page_t* last;
  size_t count;
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
# 455 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
struct mi_heap_s {
  mi_tld_t* tld;
  mi_arena_t* exclusive_arena;
  int numa_node;
  uintptr_t cookie;
  mi_random_ctx_t random;
  size_t page_count;
  size_t page_retired_min;
  size_t page_retired_max;
  long generic_count;
  long generic_collect_count;
  mi_heap_t* next;
  long page_full_retain;
  bool allow_page_reclaim;
  bool allow_page_abandon;
  uint8_t tag;






  mi_page_t* pages_free_direct[((128) + (((sizeof(mi_padding_t)) + (1<<(3)) - 1) / (1<<(3))) + 1)];
  mi_page_queue_t pages[(((73U)+1)+1)];
  mi_memid_t memid;
};
# 494 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
typedef struct mi_subproc_s {
  _Atomic(size_t) arena_count;
  _Atomic(mi_arena_t*) arenas[(160)];
  pthread_mutex_t arena_reserve_lock;
  _Atomic(int64_t) purge_expire;

  _Atomic(size_t) abandoned_count[(((73U)+1)+1)];
  mi_page_t* os_abandoned_pages;
  pthread_mutex_t os_abandoned_pages_lock;

  mi_memid_t memid;
  mi_stats_t stats;
} mi_subproc_t;
# 515 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
typedef int64_t mi_msecs_t;


struct mi_tld_s {
  mi_threadid_t thread_id;
  size_t thread_seq;
  int numa_node;
  mi_subproc_t* subproc;
  mi_heap_t* heap_backing;
  mi_heap_t* heaps;
  unsigned long long heartbeat;
  bool recurse;
  bool is_in_threadpool;
  mi_stats_t stats;
  mi_memid_t memid;
};
# 549 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/types.h"
typedef struct mi_bitmap_s mi_bitmap_t;
typedef struct mi_bbitmap_s mi_bbitmap_t;


typedef struct mi_arena_s {
  mi_memid_t memid;
  mi_subproc_t* subproc;

  size_t slice_count;
  size_t info_slices;
  int numa_node;
  bool is_exclusive;
  _Atomic(mi_msecs_t) purge_expire;
  mi_commit_fun_t* commit_fun;
  void* commit_fun_arg;

  mi_bbitmap_t* slices_free;
  mi_bitmap_t* slices_committed;
  mi_bitmap_t* slices_dirty;
  mi_bitmap_t* slices_purge;
  mi_bitmap_t* pages;
  mi_bitmap_t* pages_abandoned[((((73U)+1)+1))];



} mi_arena_t;
# 9 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c" 2

# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/testhelper.h" 1
# 10 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/testhelper.h"
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdbool.h" 1
# 11 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/testhelper.h" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 12 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/testhelper.h" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/errno.h" 1
# 13 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/testhelper.h" 2




static int ok = 0;
static int failed = 0;

static bool check_result(bool result, const char* testname, const char* fname, long lineno) {
  if (!(result)) {
    failed++;
    fprintf(stderr,"\n  FAILED: %s: %s:%ld\n", testname, fname, lineno);

  }
  else {
    ok++;
    fprintf(stderr, "ok.\n");
  }
  return 1;
}
# 41 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/testhelper.h"
static inline int print_test_summary(void)
{
  fprintf(stderr,"\n\n---------------------------------------------\n"
                 "succeeded: %i\n"
                 "failed   : %i\n\n", ok, failed);
  return failed;
}
# 11 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c" 2




bool check_zero_init(uint8_t* p, size_t size);

bool check_debug_fill_uninit(uint8_t* p, size_t size);
bool check_debug_fill_freed(uint8_t* p, size_t size);





int main(void) {
  mi_option_disable(mi_option_verbose);




  fprintf(stderr,"test: %s...  ", "zeroinit-zalloc-small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-zalloc-small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",30)) {
    size_t zalloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_zalloc(zalloc_size);
    result = check_zero_init(p, zalloc_size);
    mi_free(p);
  };
  fprintf(stderr,"test: %s...  ", "zeroinit-zalloc-large" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-zalloc-large","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",36)) {
    size_t zalloc_size = ((128)*sizeof(void*)) * 2;
    uint8_t* p = (uint8_t*)mi_zalloc(zalloc_size);
    result = check_zero_init(p, zalloc_size);
    mi_free(p);
  };
  fprintf(stderr,"test: %s...  ", "zeroinit-zalloc_small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-zalloc_small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",42)) {
    size_t zalloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_zalloc_small(zalloc_size);
    result = check_zero_init(p, zalloc_size);
    mi_free(p);
  };

  fprintf(stderr,"test: %s...  ", "zeroinit-calloc-small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-calloc-small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",49)) {
    size_t calloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_calloc(calloc_size, 1);
    result = check_zero_init(p, calloc_size);
    mi_free(p);
  };
  fprintf(stderr,"test: %s...  ", "zeroinit-calloc-large" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-calloc-large","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",55)) {
    size_t calloc_size = ((128)*sizeof(void*)) * 2;
    uint8_t* p = (uint8_t*)mi_calloc(calloc_size, 1);
    result = check_zero_init(p, calloc_size);
    mi_free(p);
  };

  fprintf(stderr,"test: %s...  ", "zeroinit-rezalloc-small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-rezalloc-small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",62)) {
    size_t zalloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_zalloc(zalloc_size);
    result = check_zero_init(p, zalloc_size);
    zalloc_size *= 3;
    p = (uint8_t*)mi_rezalloc(p, zalloc_size);
    result &= check_zero_init(p, zalloc_size);
    mi_free(p);
  };
  fprintf(stderr,"test: %s...  ", "zeroinit-rezalloc-large" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-rezalloc-large","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",71)) {
    size_t zalloc_size = ((128)*sizeof(void*)) * 2;
    uint8_t* p = (uint8_t*)mi_zalloc(zalloc_size);
    result = check_zero_init(p, zalloc_size);
    zalloc_size *= 3;
    p = (uint8_t*)mi_rezalloc(p, zalloc_size);
    result &= check_zero_init(p, zalloc_size);
    mi_free(p);
  };

  fprintf(stderr,"test: %s...  ", "zeroinit-recalloc-small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-recalloc-small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",81)) {
    size_t calloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_calloc(calloc_size, 1);
    result = check_zero_init(p, calloc_size);
    calloc_size *= 3;
    p = (uint8_t*)mi_recalloc(p, calloc_size, 1);
    result &= check_zero_init(p, calloc_size);
    mi_free(p);
  };
  fprintf(stderr,"test: %s...  ", "zeroinit-recalloc-large" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-recalloc-large","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",90)) {
    size_t calloc_size = ((128)*sizeof(void*)) * 2;
    uint8_t* p = (uint8_t*)mi_calloc(calloc_size, 1);
    result = check_zero_init(p, calloc_size);
    calloc_size *= 3;
    p = (uint8_t*)mi_recalloc(p, calloc_size, 1);
    result &= check_zero_init(p, calloc_size);
    mi_free(p);
  };




  fprintf(stderr,"test: %s...  ", "zeroinit-zalloc_aligned-small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-zalloc_aligned-small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",103)) {
    size_t zalloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_zalloc_aligned(zalloc_size, 16 * 2);
    result = check_zero_init(p, zalloc_size);
    mi_free(p);
  };
  fprintf(stderr,"test: %s...  ", "zeroinit-zalloc_aligned-large" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-zalloc_aligned-large","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",109)) {
    size_t zalloc_size = ((128)*sizeof(void*)) * 2;
    uint8_t* p = (uint8_t*)mi_zalloc_aligned(zalloc_size, 16 * 2);
    result = check_zero_init(p, zalloc_size);
    mi_free(p);
  };

  fprintf(stderr,"test: %s...  ", "zeroinit-calloc_aligned-small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-calloc_aligned-small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",116)) {
    size_t calloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_calloc_aligned(calloc_size, 1, 16 * 2);
    result = check_zero_init(p, calloc_size);
    mi_free(p);
  };
  fprintf(stderr,"test: %s...  ", "zeroinit-calloc_aligned-large" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-calloc_aligned-large","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",122)) {
    size_t calloc_size = ((128)*sizeof(void*)) * 2;
    uint8_t* p = (uint8_t*)mi_calloc_aligned(calloc_size, 1, 16 * 2);
    result = check_zero_init(p, calloc_size);
    mi_free(p);
  };

  fprintf(stderr,"test: %s...  ", "zeroinit-rezalloc_aligned-small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-rezalloc_aligned-small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",129)) {
    size_t zalloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_zalloc_aligned(zalloc_size, 16 * 2);
    result = check_zero_init(p, zalloc_size);
    zalloc_size *= 3;
    p = (uint8_t*)mi_rezalloc_aligned(p, zalloc_size, 16 * 2);
    result &= check_zero_init(p, zalloc_size);
    mi_free(p);
  };
  fprintf(stderr,"test: %s...  ", "zeroinit-rezalloc_aligned-large" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-rezalloc_aligned-large","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",138)) {
    size_t zalloc_size = ((128)*sizeof(void*)) * 2;
    uint8_t* p = (uint8_t*)mi_zalloc_aligned(zalloc_size, 16 * 2);
    result = check_zero_init(p, zalloc_size);
    zalloc_size *= 3;
    p = (uint8_t*)mi_rezalloc_aligned(p, zalloc_size, 16 * 2);
    result &= check_zero_init(p, zalloc_size);
    mi_free(p);
  };

  fprintf(stderr,"test: %s...  ", "zeroinit-recalloc_aligned-small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-recalloc_aligned-small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",148)) {
    size_t calloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_calloc_aligned(calloc_size, 1, 16 * 2);
    result = check_zero_init(p, calloc_size);
    calloc_size *= 3;
    p = (uint8_t*)mi_recalloc_aligned(p, calloc_size, 1, 16 * 2);
    result &= check_zero_init(p, calloc_size);
    mi_free(p);
  };
  fprintf(stderr,"test: %s...  ", "zeroinit-recalloc_aligned-large" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"zeroinit-recalloc_aligned-large","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",157)) {
    size_t calloc_size = ((128)*sizeof(void*)) * 2;
    uint8_t* p = (uint8_t*)mi_calloc_aligned(calloc_size, 1, 16 * 2);
    result = check_zero_init(p, calloc_size);
    calloc_size *= 3;
    p = (uint8_t*)mi_recalloc_aligned(p, calloc_size, 1, 16 * 2);
    result &= check_zero_init(p, calloc_size);
    mi_free(p);
  };





  fprintf(stderr,"test: %s...  ", "uninit-malloc-small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"uninit-malloc-small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",171)) {
    size_t malloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_malloc(malloc_size);
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  };
  fprintf(stderr,"test: %s...  ", "uninit-malloc-large" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"uninit-malloc-large","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",177)) {
    size_t malloc_size = ((128)*sizeof(void*)) * 2;
    uint8_t* p = (uint8_t*)mi_malloc(malloc_size);
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  };

  fprintf(stderr,"test: %s...  ", "uninit-malloc_small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"uninit-malloc_small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",184)) {
    size_t malloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_malloc_small(malloc_size);
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  };

  fprintf(stderr,"test: %s...  ", "uninit-realloc-small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"uninit-realloc-small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",191)) {
    size_t malloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_malloc(malloc_size);
    result = check_debug_fill_uninit(p, malloc_size);
    malloc_size *= 3;
    p = (uint8_t*)mi_realloc(p, malloc_size);
    result &= check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  };
  fprintf(stderr,"test: %s...  ", "uninit-realloc-large" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"uninit-realloc-large","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",200)) {
    size_t malloc_size = ((128)*sizeof(void*)) * 2;
    uint8_t* p = (uint8_t*)mi_malloc(malloc_size);
    result = check_debug_fill_uninit(p, malloc_size);
    malloc_size *= 3;
    p = (uint8_t*)mi_realloc(p, malloc_size);
    result &= check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  };

  fprintf(stderr,"test: %s...  ", "uninit-mallocn-small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"uninit-mallocn-small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",210)) {
    size_t malloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_mallocn(malloc_size, 1);
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  };
  fprintf(stderr,"test: %s...  ", "uninit-mallocn-large" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"uninit-mallocn-large","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",216)) {
    size_t malloc_size = ((128)*sizeof(void*)) * 2;
    uint8_t* p = (uint8_t*)mi_mallocn(malloc_size, 1);
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  };

  fprintf(stderr,"test: %s...  ", "uninit-reallocn-small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"uninit-reallocn-small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",223)) {
    size_t malloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_mallocn(malloc_size, 1);
    result = check_debug_fill_uninit(p, malloc_size);
    malloc_size *= 3;
    p = (uint8_t*)mi_reallocn(p, malloc_size, 1);
    result &= check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  };
  fprintf(stderr,"test: %s...  ", "uninit-reallocn-large" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"uninit-reallocn-large","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",232)) {
    size_t malloc_size = ((128)*sizeof(void*)) * 2;
    uint8_t* p = (uint8_t*)mi_mallocn(malloc_size, 1);
    result = check_debug_fill_uninit(p, malloc_size);
    malloc_size *= 3;
    p = (uint8_t*)mi_reallocn(p, malloc_size, 1);
    result &= check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  };

  fprintf(stderr,"test: %s...  ", "uninit-malloc_aligned-small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"uninit-malloc_aligned-small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",242)) {
    size_t malloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_malloc_aligned(malloc_size, 16 * 2);
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  };
  fprintf(stderr,"test: %s...  ", "uninit-malloc_aligned-large" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"uninit-malloc_aligned-large","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",248)) {
    size_t malloc_size = ((128)*sizeof(void*)) * 2;
    uint8_t* p = (uint8_t*)mi_malloc_aligned(malloc_size, 16 * 2);
    result = check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  };

  fprintf(stderr,"test: %s...  ", "uninit-realloc_aligned-small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"uninit-realloc_aligned-small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",255)) {
    size_t malloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_malloc_aligned(malloc_size, 16 * 2);
    result = check_debug_fill_uninit(p, malloc_size);
    malloc_size *= 3;
    p = (uint8_t*)mi_realloc_aligned(p, malloc_size, 16 * 2);
    result &= check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  };
  fprintf(stderr,"test: %s...  ", "uninit-realloc_aligned-large" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"uninit-realloc_aligned-large","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",264)) {
    size_t malloc_size = ((128)*sizeof(void*)) * 2;
    uint8_t* p = (uint8_t*)mi_malloc_aligned(malloc_size, 16 * 2);
    result = check_debug_fill_uninit(p, malloc_size);
    malloc_size *= 3;
    p = (uint8_t*)mi_realloc_aligned(p, malloc_size, 16 * 2);
    result &= check_debug_fill_uninit(p, malloc_size);
    mi_free(p);
  };


  fprintf(stderr,"test: %s...  ", "fill-freed-small" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"fill-freed-small","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",275)) {
    size_t malloc_size = ((128)*sizeof(void*)) / 2;
    uint8_t* p = (uint8_t*)mi_malloc(malloc_size);
    mi_free(p);

    result = check_debug_fill_freed(p + sizeof(void*), malloc_size - sizeof(void*));
  };
  fprintf(stderr,"test: %s...  ", "fill-freed-large" ); errno = 0; for(bool done = 0, result = 1; !done; done = check_result(result,"fill-freed-large","/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-api-fill.c",282)) {
    size_t malloc_size = ((128)*sizeof(void*)) * 2;
    uint8_t* p = (uint8_t*)mi_malloc(malloc_size);
    mi_free(p);

    result = check_debug_fill_freed(p + sizeof(void*), malloc_size - sizeof(void*));
  };






  return print_test_summary();
}




bool check_zero_init(uint8_t* p, size_t size) {
  if(!p)
    return 0;
  bool result = 1;
  for (size_t i = 0; i < size; ++i) {
    result &= p[i] == 0;
  }
  return result;
}


bool check_debug_fill_uninit(uint8_t* p, size_t size) {




  if(!p)
    return 0;

  bool result = 1;
  for (size_t i = 0; i < size; ++i) {
    result &= p[i] == (0xD0);
  }
  return result;

}

bool check_debug_fill_freed(uint8_t* p, size_t size) {




  if(!p)
    return 0;

  bool result = 1;
  for (size_t i = 0; i < size; ++i) {
    result &= p[i] == (0xDF);
  }
  return result;

}
