# 0 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c"
# 11 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c"
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
# 12 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c" 2
# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h" 1






       
# 16 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
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
# 17 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h" 2
# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/track.h" 1






       
# 18 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h" 2
# 120 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdarg.h" 1
# 121 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h" 2
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
void _mi_raw_message(const char* fmt, ...);
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

mi_subproc_t* _mi_subproc(void);
mi_subproc_t* _mi_subproc_main(void);
mi_subproc_t* _mi_subproc_from_id(mi_subproc_id_t subproc_id);
mi_threadid_t _mi_thread_id(void) ;
size_t _mi_thread_seq_id(void) ;
mi_tld_t* _mi_thread_tld(void) ;
void _mi_heap_guarded_init(mi_heap_t* heap);
mi_heap_t* _mi_heap_main_get(void);


void _mi_os_init(void);
void* _mi_os_alloc(size_t size, mi_memid_t* memid);
void* _mi_os_zalloc(size_t size, mi_memid_t* memid);
void _mi_os_free(void* p, size_t size, mi_memid_t memid);
void _mi_os_free_ex(void* p, size_t size, bool still_committed, mi_memid_t memid, mi_subproc_t* subproc );

size_t _mi_os_page_size(void);
size_t _mi_os_guard_page_size(void);
size_t _mi_os_good_alloc_size(size_t size);
bool _mi_os_has_overcommit(void);
bool _mi_os_has_virtual_reserve(void);
size_t _mi_os_virtual_address_bits(void);

bool _mi_os_reset(void* addr, size_t size);
bool _mi_os_decommit(void* addr, size_t size);
void _mi_os_reuse(void* p, size_t size);
 bool _mi_os_commit(void* p, size_t size, bool* is_zero);
 bool _mi_os_commit_ex(void* addr, size_t size, bool* is_zero, size_t stat_size);
 bool _mi_os_protect(void* addr, size_t size);
bool _mi_os_unprotect(void* addr, size_t size);
bool _mi_os_purge(void* p, size_t size);
bool _mi_os_purge_ex(void* p, size_t size, bool allow_reset, size_t stats_size, mi_commit_fun_t* commit_fun, void* commit_fun_arg);

size_t _mi_os_secure_guard_page_size(void);
bool _mi_os_secure_guard_page_set_at(void* addr, mi_memid_t memid);
bool _mi_os_secure_guard_page_set_before(void* addr, mi_memid_t memid);
bool _mi_os_secure_guard_page_reset_at(void* addr, mi_memid_t memid);
bool _mi_os_secure_guard_page_reset_before(void* addr, mi_memid_t memid);

int _mi_os_numa_node(void);
int _mi_os_numa_node_count(void);

void* _mi_os_alloc_aligned(size_t size, size_t alignment, bool commit, bool allow_large, mi_memid_t* memid);
void* _mi_os_alloc_aligned_at_offset(size_t size, size_t alignment, size_t align_offset, bool commit, bool allow_large, mi_memid_t* memid);

void* _mi_os_get_aligned_hint(size_t try_alignment, size_t size);
bool _mi_os_use_large_page(size_t size, size_t alignment);
size_t _mi_os_large_page_size(void);
void* _mi_os_alloc_huge_os_pages(size_t pages, int numa_node, mi_msecs_t max_secs, size_t* pages_reserved, size_t* psize, mi_memid_t* memid);



mi_arena_id_t _mi_arena_id_none(void);
mi_arena_t* _mi_arena_from_id(mi_arena_id_t id);
bool _mi_arena_memid_is_suitable(mi_memid_t memid, mi_arena_t* request_arena);

void* _mi_arenas_alloc(mi_subproc_t* subproc, size_t size, bool commit, bool allow_pinned, mi_arena_t* req_arena, size_t tseq, int numa_node, mi_memid_t* memid);
void* _mi_arenas_alloc_aligned(mi_subproc_t* subproc, size_t size, size_t alignment, size_t align_offset, bool commit, bool allow_pinned, mi_arena_t* req_arena, size_t tseq, int numa_node, mi_memid_t* memid);
void _mi_arenas_free(void* p, size_t size, mi_memid_t memid);
bool _mi_arenas_contain(const void* p);
void _mi_arenas_collect(bool force_purge, bool visit_all, mi_tld_t* tld);
void _mi_arenas_unsafe_destroy_all(mi_subproc_t* subproc);

mi_page_t* _mi_arenas_page_alloc(mi_heap_t* heap, size_t block_size, size_t page_alignment);
void _mi_arenas_page_free(mi_page_t* page, mi_tld_t* tld);
void _mi_arenas_page_abandon(mi_page_t* page, mi_tld_t* tld);
void _mi_arenas_page_unabandon(mi_page_t* page);
bool _mi_arenas_page_try_reabandon_to_mapped(mi_page_t* page);


void* _mi_meta_zalloc( size_t size, mi_memid_t* memid );
void _mi_meta_free(void* p, size_t size, mi_memid_t memid);
bool _mi_meta_is_meta_page(void* p);


bool _mi_page_map_init(void);
 bool _mi_page_map_register(mi_page_t* page);
void _mi_page_map_unregister(mi_page_t* page);
void _mi_page_map_unregister_range(void* start, size_t size);
mi_page_t* _mi_safe_ptr_page(const void* p);
void _mi_page_map_unsafe_destroy(mi_subproc_t* subproc);


void* _mi_malloc_generic(mi_heap_t* heap, size_t size, bool zero, size_t huge_alignment) ;

void _mi_page_retire(mi_page_t* page) ;
void _mi_page_unfull(mi_page_t* page);
void _mi_page_free(mi_page_t* page, mi_page_queue_t* pq);
void _mi_page_abandon(mi_page_t* page, mi_page_queue_t* pq);
void _mi_heap_collect_retired(mi_heap_t* heap, bool force);

size_t _mi_page_queue_append(mi_heap_t* heap, mi_page_queue_t* pq, mi_page_queue_t* append);
void _mi_deferred_free(mi_heap_t* heap, bool force);

void _mi_page_free_collect(mi_page_t* page, bool force);
void _mi_page_free_collect_partly(mi_page_t* page, mi_block_t* head);
 bool _mi_page_init(mi_heap_t* heap, mi_page_t* page);
bool _mi_page_queue_is_valid(mi_heap_t* heap, const mi_page_queue_t* pq);

size_t _mi_page_bin(const mi_page_t* page);
size_t _mi_bin_size(size_t bin);
size_t _mi_bin(size_t size);


mi_heap_t* _mi_heap_create(int heap_tag, bool allow_destroy, mi_arena_id_t arena_id, mi_tld_t* tld);
void _mi_heap_init(mi_heap_t* heap, mi_arena_id_t arena_id, bool noreclaim, uint8_t tag, mi_tld_t* tld);
void _mi_heap_destroy_pages(mi_heap_t* heap);
void _mi_heap_collect_abandon(mi_heap_t* heap);
void _mi_heap_set_default_direct(mi_heap_t* heap);
bool _mi_heap_memid_is_suitable(mi_heap_t* heap, mi_memid_t memid);
void _mi_heap_unsafe_destroy_all(mi_heap_t* heap);
mi_heap_t* _mi_heap_by_tag(mi_heap_t* heap, uint8_t tag);
void _mi_heap_area_init(mi_heap_area_t* area, mi_page_t* page);
bool _mi_heap_area_visit_blocks(const mi_heap_area_t* area, mi_page_t* page, mi_block_visit_fun* visitor, void* arg);
void _mi_heap_page_reclaim(mi_heap_t* heap, mi_page_t* page);


void _mi_stats_init(void);
void _mi_stats_done(mi_stats_t* stats);
void _mi_stats_print(mi_stats_t* stats, mi_output_fun* out, void* arg) ;
void _mi_stats_merge_thread(mi_tld_t* tld);
void _mi_stats_merge_from(mi_stats_t* to, mi_stats_t* from);
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
void _mi_padding_shrink(const mi_page_t* page, const mi_block_t* block, const size_t min_size);


bool _mi_page_is_valid(mi_page_t* page);
# 312 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
 void _mi_assert_fail(const char* assertion, const char* fname, unsigned int line, const char* func) ;
# 336 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
void __mi_stat_increase(mi_stat_count_t* stat, size_t amount);
void __mi_stat_decrease(mi_stat_count_t* stat, size_t amount);
void __mi_stat_increase_mt(mi_stat_count_t* stat, size_t amount);
void __mi_stat_decrease_mt(mi_stat_count_t* stat, size_t amount);


void __mi_stat_adjust_increase(mi_stat_count_t* stat, size_t amount);
void __mi_stat_adjust_decrease(mi_stat_count_t* stat, size_t amount);
void __mi_stat_adjust_increase_mt(mi_stat_count_t* stat, size_t amount);
void __mi_stat_adjust_decrease_mt(mi_stat_count_t* stat, size_t amount);


void __mi_stat_counter_increase(mi_stat_counter_t* stat, size_t amount);
void __mi_stat_counter_increase_mt(mi_stat_counter_t* stat, size_t amount);
# 375 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
typedef enum mi_option_init_e {
  MI_OPTION_UNINIT,
  MI_OPTION_DEFAULTED,
  MI_OPTION_INITIALIZED
} mi_option_init_t;

typedef struct mi_option_desc_s {
  long value;
  mi_option_init_t init;
  mi_option_t option;
  const char* name;
  const char* legacy_name;
} mi_option_desc_t;
# 412 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 413 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h" 2




static inline bool _mi_is_power_of_two(uintptr_t x) {
  return ((x & (x - 1)) == 0);
}


static inline bool _mi_is_aligned(void* p, size_t alignment) {
  ((alignment != 0) ? (void)0 : _mi_assert_fail("alignment != 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",423,__func__));
  return (((uintptr_t)p % alignment) == 0);
}


static inline uintptr_t _mi_align_up(uintptr_t sz, size_t alignment) {
  ((alignment != 0) ? (void)0 : _mi_assert_fail("alignment != 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",429,__func__));
  uintptr_t mask = alignment - 1;
  if ((alignment & mask) == 0) {
    return ((sz + mask) & ~mask);
  }
  else {
    return (((sz + mask)/alignment)*alignment);
  }
}



static inline uint8_t* _mi_align_up_ptr(void* p, size_t alignment) {
  return (uint8_t*)_mi_align_up((uintptr_t)p, alignment);
}


static inline uintptr_t _mi_align_down(uintptr_t sz, size_t alignment) {
  ((alignment != 0) ? (void)0 : _mi_assert_fail("alignment != 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",447,__func__));
  uintptr_t mask = alignment - 1;
  if ((alignment & mask) == 0) {
    return (sz & ~mask);
  }
  else {
    return ((sz / alignment) * alignment);
  }
}

static inline void* mi_align_down_ptr(void* p, size_t alignment) {
  return (void*)_mi_align_down((uintptr_t)p, alignment);
}


static inline uintptr_t _mi_divide_up(uintptr_t size, size_t divider) {
  ((divider != 0) ? (void)0 : _mi_assert_fail("divider != 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",463,__func__));
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
  ((size <= SIZE_MAX - sizeof(uintptr_t)) ? (void)0 : _mi_assert_fail("size <= SIZE_MAX - sizeof(uintptr_t)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",486,__func__));
  return (size + sizeof(uintptr_t) - 1) / sizeof(uintptr_t);
}



# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 1
# 493 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h" 2



static inline bool mi_mul_overflow(size_t count, size_t size, size_t* total) {





    return __builtin_umulll_overflow(count, size, (unsigned long long *)total);

}
# 515 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
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

static inline bool mi_heap_is_initialized(const mi_heap_t* heap) {
  ((heap != 0) ? (void)0 : _mi_assert_fail("heap != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",542,__func__));
  return (heap != 0 && heap != &_mi_heap_empty);
}

static inline mi_page_t* _mi_heap_get_free_small_page(mi_heap_t* heap, size_t size) {
  ((size <= (((128)*sizeof(void*)) + (sizeof(mi_padding_t)))) ? (void)0 : _mi_assert_fail("size <= (MI_SMALL_SIZE_MAX + MI_PADDING_SIZE)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",547,__func__));
  const size_t idx = _mi_wsize_from_size(size);
  ((idx < ((128) + (((sizeof(mi_padding_t)) + (1<<(3)) - 1) / (1<<(3))) + 1)) ? (void)0 : _mi_assert_fail("idx < MI_PAGES_DIRECT","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",549,__func__));
  return heap->pages_free_direct[idx];
}
# 607 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
typedef mi_page_t** mi_submap_t;
extern _Atomic(mi_submap_t)* _mi_page_map;

static inline size_t _mi_page_map_index(const void* p, size_t* sub_idx) {
  const size_t u = (size_t)((uintptr_t)p / (1UL << (13 + (3))));
  if (sub_idx != 0) { *sub_idx = u % (1UL << (13)); }
  return (u / (1UL << (13)));
}

static inline mi_submap_t _mi_page_map_at(size_t idx) {
  return atomic_load_explicit(&_mi_page_map[idx],memory_order_relaxed);
}

static inline mi_page_t* _mi_unchecked_ptr_page(const void* p) {
  size_t sub_idx;
  const size_t idx = _mi_page_map_index(p, &sub_idx);
  return (_mi_page_map_at(idx))[sub_idx];
}

static inline mi_page_t* _mi_checked_ptr_page(const void* p) {
  size_t sub_idx;
  const size_t idx = _mi_page_map_index(p, &sub_idx);
  mi_submap_t const sub = _mi_page_map_at(idx);
  if (__builtin_expect(!!(sub == 0),0)) return 0;
  return sub[sub_idx];
}




static inline mi_page_t* _mi_ptr_page(const void* p) {
  ((p==0 || mi_is_in_heap_region(p)) ? (void)0 : _mi_assert_fail("p==NULL || mi_is_in_heap_region(p)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",638,__func__));

  return _mi_checked_ptr_page(p);



}



static inline size_t mi_page_block_size(const mi_page_t* page) {
  ((page->block_size > 0) ? (void)0 : _mi_assert_fail("page->block_size > 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",649,__func__));
  return page->block_size;
}


static inline uint8_t* mi_page_start(const mi_page_t* page) {
  return page->page_start;
}

static inline size_t mi_page_size(const mi_page_t* page) {
  return mi_page_block_size(page) * page->reserved;
}

static inline uint8_t* mi_page_area(const mi_page_t* page, size_t* size) {
  if (size) { *size = mi_page_size(page); }
  return mi_page_start(page);
}

static inline size_t mi_page_info_size(void) {
  return _mi_align_up(sizeof(mi_page_t), 16);
}

static inline bool mi_page_contains_address(const mi_page_t* page, const void* p) {
  size_t psize;
  uint8_t* start = mi_page_area(page, &psize);
  return (start <= (uint8_t*)p && (uint8_t*)p < start + psize);
}

static inline bool mi_page_is_in_arena(const mi_page_t* page) {
  return (page->memid.memkind == MI_MEM_ARENA);
}

static inline bool mi_page_is_singleton(const mi_page_t* page) {
  return (page->reserved == 1);
}



static inline size_t mi_page_usable_block_size(const mi_page_t* page) {
  return mi_page_block_size(page) - (sizeof(mi_padding_t));
}


static inline uint8_t* mi_page_slice_start(const mi_page_t* page) {
  return (uint8_t*)page;
}



static inline size_t mi_page_slice_offset_of(const mi_page_t* page, size_t offset_relative_to_page_start) {
  return (page->page_start - mi_page_slice_start(page)) + offset_relative_to_page_start;
}

static inline size_t mi_page_committed(const mi_page_t* page) {
  return (page->slice_committed == 0 ? mi_page_size(page) : page->slice_committed - (page->page_start - mi_page_slice_start(page)));
}

static inline mi_heap_t* mi_page_heap(const mi_page_t* page) {
  return page->heap;
}




static inline bool mi_page_all_free(const mi_page_t* page) {
  ((page != 0) ? (void)0 : _mi_assert_fail("page != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",714,__func__));
  return (page->used == 0);
}


static inline bool mi_page_immediate_available(const mi_page_t* page) {
  ((page != 0) ? (void)0 : _mi_assert_fail("page != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",720,__func__));
  return (page->free != 0);
}



static inline bool mi_page_is_expandable(const mi_page_t* page) {
  ((page != 0) ? (void)0 : _mi_assert_fail("page != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",727,__func__));
  ((page->capacity <= page->reserved) ? (void)0 : _mi_assert_fail("page->capacity <= page->reserved","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",728,__func__));
  return (page->capacity < page->reserved);
}


static inline bool mi_page_is_full(mi_page_t* page) {
  const bool full = (page->reserved == page->used);
  ((!full || page->free == 0) ? (void)0 : _mi_assert_fail("!full || page->free == NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",735,__func__));
  return full;
}


static inline bool mi_page_is_mostly_used(const mi_page_t* page) {
  if (page==0) return 1;
  uint16_t frac = page->reserved / 8U;
  return (page->reserved - page->used <= frac);
}


static inline bool mi_page_is_used_at_frac(const mi_page_t* page, uint16_t n) {
  if (page==0) return 1;
  uint16_t frac = page->reserved / n;
  return (page->reserved - page->used <= frac);
}


static inline bool mi_page_is_huge(const mi_page_t* page) {
  return (mi_page_is_singleton(page) &&
          (page->block_size > ((8*((1) * (1UL << (13 + (3)))))/8) ||
           (mi_memkind_is_os(page->memid.memkind) && page->memid.mem.os.base < (void*)page)));
}

static inline mi_page_queue_t* mi_page_queue(const mi_heap_t* heap, size_t size) {
  mi_page_queue_t* const pq = &((mi_heap_t*)heap)->pages[_mi_bin(size)];
  if (size <= ((8*((1) * (1UL << (13 + (3)))))/8)) { ((pq->block_size <= ((8*((1) * (1UL << (13 + (3)))))/8)) ? (void)0 : _mi_assert_fail("pq->block_size <= MI_LARGE_MAX_OBJ_SIZE","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",762,__func__)); }
  return pq;
}







static inline mi_threadid_t mi_page_xthread_id(const mi_page_t* page) {
  return atomic_load_explicit(&((mi_page_t*)page)->xthread_id,memory_order_relaxed);
}


static inline mi_threadid_t mi_page_thread_id(const mi_page_t* page) {
  return (mi_page_xthread_id(page) & ~0x03UL);
}

static inline mi_page_flags_t mi_page_flags(const mi_page_t* page) {
  return (mi_page_xthread_id(page) & 0x03UL);
}

static inline void mi_page_flags_set(mi_page_t* page, bool set, mi_page_flags_t newflag) {
  if (set) { atomic_fetch_or_explicit(&page->xthread_id,newflag,memory_order_relaxed); }
      else { atomic_fetch_and_explicit(&page->xthread_id,~newflag,memory_order_relaxed); }
}

static inline bool mi_page_is_in_full(const mi_page_t* page) {
  return ((mi_page_flags(page) & 0x01UL) != 0);
}

static inline void mi_page_set_in_full(mi_page_t* page, bool in_full) {
  mi_page_flags_set(page, in_full, 0x01UL);
}

static inline bool mi_page_has_interior_pointers(const mi_page_t* page) {
  return ((mi_page_flags(page) & 0x02UL) != 0);
}

static inline void mi_page_set_has_interior_pointers(mi_page_t* page, bool has_aligned) {
  mi_page_flags_set(page, has_aligned, 0x02UL);
}

static inline void mi_page_set_heap(mi_page_t* page, mi_heap_t* heap) {

  if (heap != 0) {
    page->heap = heap;
    page->heap_tag = heap->tag;
  }
  else {
    page->heap = 0;
  }
  const mi_threadid_t tid = (heap == 0 ? 0UL : heap->tld->thread_id);
  (((tid & 0x03UL) == 0) ? (void)0 : _mi_assert_fail("(tid & MI_PAGE_FLAG_MASK) == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",816,__func__));


  mi_threadid_t xtid_old = mi_page_xthread_id(page);
  mi_threadid_t xtid;
  do {
    xtid = tid | (xtid_old & 0x03UL);
  } while (!atomic_compare_exchange_weak_explicit(&page->xthread_id,&xtid_old,xtid,memory_order_release,memory_order_relaxed));
}

static inline bool mi_page_is_abandoned(const mi_page_t* page) {

  return (mi_page_thread_id(page) <= (0x03UL + 1));
}

static inline bool mi_page_is_abandoned_mapped(const mi_page_t* page) {
  return (mi_page_thread_id(page) == (0x03UL + 1));
}

static inline void mi_page_set_abandoned_mapped(mi_page_t* page) {
  ((mi_page_is_abandoned(page)) ? (void)0 : _mi_assert_fail("mi_page_is_abandoned(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",836,__func__));
  atomic_fetch_or_explicit(&page->xthread_id,(0x03UL + 1),memory_order_relaxed);
}

static inline void mi_page_clear_abandoned_mapped(mi_page_t* page) {
  ((mi_page_is_abandoned_mapped(page)) ? (void)0 : _mi_assert_fail("mi_page_is_abandoned_mapped(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",841,__func__));
  atomic_fetch_and_explicit(&page->xthread_id,0x03UL,memory_order_relaxed);
}






static inline mi_block_t* mi_tf_block(mi_thread_free_t tf) {
  return (mi_block_t*)(tf & ~1);
}
static inline bool mi_tf_is_owned(mi_thread_free_t tf) {
  return ((tf & 1) == 1);
}
static inline mi_thread_free_t mi_tf_create(mi_block_t* block, bool owned) {
  return (mi_thread_free_t)((uintptr_t)block | (owned ? 1 : 0));
}


static inline mi_block_t* mi_page_thread_free(const mi_page_t* page) {
  return mi_tf_block(atomic_load_explicit(&((mi_page_t*)page)->xthread_free,memory_order_relaxed));
}


static inline bool mi_page_has_any_available(const mi_page_t* page) {
  ((page != 0 && page->reserved > 0) ? (void)0 : _mi_assert_fail("page != NULL && page->reserved > 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",867,__func__));
  return (page->used < page->reserved || (mi_page_thread_free(page) != 0));
}



static inline bool mi_page_is_owned(const mi_page_t* page) {
  return mi_tf_is_owned(atomic_load_explicit(&((mi_page_t*)page)->xthread_free,memory_order_relaxed));
}


static inline void _mi_page_unown_unconditional(mi_page_t* page) {
  ((mi_page_is_owned(page)) ? (void)0 : _mi_assert_fail("mi_page_is_owned(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",879,__func__));
  ((mi_page_thread_id(page)==0) ? (void)0 : _mi_assert_fail("mi_page_thread_id(page)==0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",880,__func__));
  const uintptr_t old = atomic_fetch_and_explicit(&page->xthread_free,~((uintptr_t)1),memory_order_acq_rel);
  (((old&1)==1) ? (void)0 : _mi_assert_fail("(old&1)==1","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",882,__func__)); (void)(old);
}


static inline bool mi_page_try_claim_ownership(mi_page_t* page) {
  const uintptr_t old = atomic_fetch_or_explicit(&page->xthread_free,1,memory_order_acq_rel);
  return ((old&1)==0);
}



static inline bool _mi_page_unown(mi_page_t* page) {
  ((mi_page_is_owned(page)) ? (void)0 : _mi_assert_fail("mi_page_is_owned(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",894,__func__));
  ((mi_page_is_abandoned(page)) ? (void)0 : _mi_assert_fail("mi_page_is_abandoned(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",895,__func__));
  mi_thread_free_t tf_new;
  mi_thread_free_t tf_old = atomic_load_explicit(&page->xthread_free,memory_order_relaxed);
  do {
    ((mi_tf_is_owned(tf_old)) ? (void)0 : _mi_assert_fail("mi_tf_is_owned(tf_old)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",899,__func__));
    while (__builtin_expect(!!(mi_tf_block(tf_old) != 0),0)) {
      _mi_page_free_collect(page, 0);
      if (mi_page_all_free(page)) {
        _mi_arenas_page_unabandon(page);
        _mi_arenas_page_free(page,0);
        return 1;
      }
      tf_old = atomic_load_explicit(&page->xthread_free,memory_order_relaxed);
    }
    ((mi_tf_block(tf_old)==0) ? (void)0 : _mi_assert_fail("mi_tf_block(tf_old)==NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",909,__func__));
    tf_new = mi_tf_create(0, 0);
  } while (!atomic_compare_exchange_weak_explicit(&page->xthread_free,&tf_old,tf_new,memory_order_acq_rel,memory_order_acquire));
  return 0;
}
# 981 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
static inline bool mi_is_in_same_page(const void* p, const void* q) {
  mi_page_t* page = _mi_ptr_page(p);
  return mi_page_contains_address(page,q);

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






static inline size_t mi_slice_count_of_size(size_t size) {
  return _mi_divide_up(size, (1UL << (13 + (3))));
}


static inline size_t mi_size_of_slices(size_t bcount) {
  return (bcount * (1UL << (13 + (3))));
}






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

static inline mi_memid_t _mi_memid_create_meta(void* mpage, size_t block_idx, size_t block_count) {
  mi_memid_t memid = _mi_memid_create(MI_MEM_META);
  memid.mem.meta.meta_page = mpage;
  memid.mem.meta.block_index = (uint32_t)block_idx;
  memid.mem.meta.block_count = (uint32_t)block_count;
  memid.initially_committed = 1;
  memid.initially_zero = 1;
  memid.is_pinned = 1;
  return memid;
}






static inline uintptr_t _mi_random_shuffle(uintptr_t x) {
  if (x==0) { x = 17; }


  x ^= x >> 30;
  x *= 0xbf58476d1ce4e5b9UL;
  x ^= x >> 27;
  x *= 0x94d049bb133111ebUL;
  x ^= x >> 31;
# 1129 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
  return x;
}
# 1162 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
static inline void _mi_memcpy(void* dst, const void* src, size_t n) {
  memcpy(dst, src, n);
}
static inline void _mi_memset(void* dst, int val, size_t n) {
  memset(dst, val, n);
}
# 1177 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
static inline void _mi_memcpy_aligned(void* dst, const void* src, size_t n) {
  ((((uintptr_t)dst % (1<<(3)) == 0) && ((uintptr_t)src % (1<<(3)) == 0)) ? (void)0 : _mi_assert_fail("((uintptr_t)dst % MI_INTPTR_SIZE == 0) && ((uintptr_t)src % MI_INTPTR_SIZE == 0)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",1178,__func__));
  void* adst = __builtin_assume_aligned(dst, (1<<(3)));
  const void* asrc = __builtin_assume_aligned(src, (1<<(3)));
  _mi_memcpy(adst, asrc, n);
}

static inline void _mi_memset_aligned(void* dst, int val, size_t n) {
  (((uintptr_t)dst % (1<<(3)) == 0) ? (void)0 : _mi_assert_fail("(uintptr_t)dst % MI_INTPTR_SIZE == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",1185,__func__));
  void* adst = __builtin_assume_aligned(dst, (1<<(3)));
  _mi_memset(adst, val, n);
}
# 1202 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
static inline void _mi_memzero(void* dst, size_t n) {
  _mi_memset(dst, 0, n);
}

static inline void _mi_memzero_aligned(void* dst, size_t n) {
  _mi_memset_aligned(dst, 0, n);
}
# 13 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c" 2

# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/prim.h" 1






       
# 24 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/prim.h"
typedef struct mi_os_mem_config_s {
  size_t page_size;
  size_t large_page_size;
  size_t alloc_granularity;
  size_t physical_memory_in_kib;
  size_t virtual_address_bits;
  bool has_overcommit;
  bool has_partial_free;
  bool has_virtual_reserve;
} mi_os_mem_config_t;


void _mi_prim_mem_init( mi_os_mem_config_t* config );


int _mi_prim_free(void* addr, size_t size );
# 49 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/prim.h"
int _mi_prim_alloc(void* hint_addr, size_t size, size_t try_alignment, bool commit, bool allow_large, bool* is_large, bool* is_zero, void** addr);




int _mi_prim_commit(void* addr, size_t size, bool* is_zero);





int _mi_prim_decommit(void* addr, size_t size, bool* needs_recommit);



int _mi_prim_reset(void* addr, size_t size);




int _mi_prim_reuse(void* addr, size_t size);


int _mi_prim_protect(void* addr, size_t size, bool protect);





int _mi_prim_alloc_huge_os_pages(void* hint_addr, size_t size, int numa_node, bool* is_zero, void** addr);


size_t _mi_prim_numa_node(void);


size_t _mi_prim_numa_node_count(void);


mi_msecs_t _mi_prim_clock_now(void);


typedef struct mi_process_info_s {
  mi_msecs_t elapsed;
  mi_msecs_t utime;
  mi_msecs_t stime;
  size_t current_rss;
  size_t peak_rss;
  size_t current_commit;
  size_t peak_commit;
  size_t page_faults;
} mi_process_info_t;

void _mi_prim_process_info(mi_process_info_t* pinfo);



void _mi_prim_out_stderr( const char* msg );



bool _mi_prim_getenv(const char* name, char* result, size_t result_size);




bool _mi_prim_random_buf(void* buf, size_t buf_len);


void _mi_prim_thread_init_auto_done(void);


void _mi_prim_thread_done_auto_done(void);


void _mi_prim_thread_associate_default_heap(mi_heap_t* heap);


bool _mi_prim_thread_is_in_threadpool(void);
# 277 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/prim.h"
extern mi_heap_t* _mi_heap_default;
extern bool _mi_process_is_initialized;

static inline mi_threadid_t __mi_prim_thread_id(void) ;

static inline mi_threadid_t _mi_prim_thread_id(void) {
  const mi_threadid_t tid = __mi_prim_thread_id();
  ((tid > 1) ? (void)0 : _mi_assert_fail("tid > 1","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/prim.h",284,__func__));
  (((tid & 0x03UL) == 0) ? (void)0 : _mi_assert_fail("(tid & MI_PAGE_FLAG_MASK) == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/prim.h",285,__func__));
  return tid;
}
# 305 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/prim.h"
static inline mi_threadid_t __mi_prim_thread_id(void) {

  return (uintptr_t)__builtin_thread_pointer();
}
# 354 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/prim.h"
static inline mi_heap_t* mi_prim_get_default_heap(void);
# 421 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/prim.h"
static inline mi_heap_t* mi_prim_get_default_heap(void) {



  return _mi_heap_default;
}
# 15 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c" 2

# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 17 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 18 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c" 2


# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-override.c" 1
# 21 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c" 2
# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c" 1
# 15 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c"
static void mi_check_padding(const mi_page_t* page, const mi_block_t* block);
static bool mi_check_is_double_free(const mi_page_t* page, const mi_block_t* block);
static size_t mi_page_usable_size_of(const mi_page_t* page, const mi_block_t* block);
static void mi_stat_free(const mi_page_t* page, const mi_block_t* block);
# 27 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c"
static inline void mi_free_block_local(mi_page_t* page, mi_block_t* block, bool track_stats, bool check_full)
{

  if (__builtin_expect(!!(mi_check_is_double_free(page, block)),0)) return;
  mi_check_padding(page, block);
  if (track_stats) { mi_stat_free(page, block); }

  memset(block, (0xDF), mi_page_block_size(page));

  if (track_stats) { ; }


  mi_block_set_next(page, block, page->local_free);
  page->local_free = block;
  if (__builtin_expect(!!(--page->used == 0),0)) {
    _mi_page_retire(page);
  }
  else if (__builtin_expect(!!(check_full && mi_page_is_in_full(page)),0)) {
    _mi_page_unfull(page);
  }
}


static void mi_free_try_collect_mt(mi_page_t* page, mi_block_t* mt_free) ;


static inline void mi_free_block_mt(mi_page_t* page, mi_block_t* block)
{

  mi_stat_free(page, block);
  ;



  size_t dbgsize = mi_usable_size(block);
  if (dbgsize > ((1024UL)*(1024UL))) { dbgsize = ((1024UL)*(1024UL)); }
  _mi_memset_aligned(block, (0xDF), dbgsize);



  mi_thread_free_t tf_new;
  mi_thread_free_t tf_old = atomic_load_explicit(&page->xthread_free,memory_order_relaxed);
  do {
    mi_block_set_next(page, block, mi_tf_block(tf_old));
    tf_new = mi_tf_create(block, 1 );
  } while (!atomic_compare_exchange_weak_explicit(&page->xthread_free,&tf_old,tf_new,memory_order_acq_rel,memory_order_acquire));


  const bool is_owned_now = !mi_tf_is_owned(tf_old);
  if (is_owned_now) {
    ((mi_page_is_abandoned(page)) ? (void)0 : _mi_assert_fail("mi_page_is_abandoned(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",77,__func__));
    mi_free_try_collect_mt(page,block);
  }
}






mi_block_t* _mi_page_ptr_unalign(const mi_page_t* page, const void* p) {
  ((page!=0 && p!=0) ? (void)0 : _mi_assert_fail("page!=NULL && p!=NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",88,__func__));

  const size_t diff = (uint8_t*)p - mi_page_start(page);
  const size_t block_size = mi_page_block_size(page);
  const size_t adjust = (_mi_is_power_of_two(block_size) ? diff & (block_size - 1) : diff % block_size);
  return (mi_block_t*)((uintptr_t)p - adjust);
}
# 103 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c"
static inline void mi_block_check_unguard(mi_page_t* page, mi_block_t* block, void* p) {
  (void)(page); (void)(block); (void)(p);
}


static inline mi_block_t* mi_validate_block_from_ptr( const mi_page_t* page, void* p ) {
  ((_mi_page_ptr_unalign(page,p) == (mi_block_t*)p) ? (void)0 : _mi_assert_fail("_mi_page_ptr_unalign(page,p) == (mi_block_t*)p","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",109,__func__));




  (void)(page);
  return (mi_block_t*)p;

}



static void mi_free_generic_local(mi_page_t* page, void* p) {
  ((p!=0 && page != 0) ? (void)0 : _mi_assert_fail("p!=NULL && page != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",122,__func__));
  mi_block_t* const block = (mi_page_has_interior_pointers(page) ? _mi_page_ptr_unalign(page, p) : mi_validate_block_from_ptr(page,p));
  mi_block_check_unguard(page, block, p);
  mi_free_block_local(page, block, 1 , 1 );
}


static void mi_free_generic_mt(mi_page_t* page, void* p) {
  ((p!=0 && page != 0) ? (void)0 : _mi_assert_fail("p!=NULL && page != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",130,__func__));
  mi_block_t* const block = (mi_page_has_interior_pointers(page) ? _mi_page_ptr_unalign(page, p) : mi_validate_block_from_ptr(page,p));
  mi_block_check_unguard(page, block, p);
  mi_free_block_mt(page, block);
}


void _mi_free_generic(mi_page_t* page, bool is_local, void* p) {
  if (is_local) mi_free_generic_local(page,p);
           else mi_free_generic_mt(page,p);
}




static inline mi_page_t* mi_validate_ptr_page(const void* p, const char* msg)
{
  ;

  if (__builtin_expect(!!(((uintptr_t)p & ((1<<(3)) - 1)) != 0 && !mi_option_is_enabled(mi_option_guarded_precise)),0)) {
    _mi_error_message((22), "%s: invalid (unaligned) pointer: %p\n", msg, p);
    return 0;
  }
  mi_page_t* page = _mi_safe_ptr_page(p);
  if (p != 0 && page == 0) {
    _mi_error_message((22), "%s: invalid pointer: %p\n", msg, p);
  }
  return page;



}



void mi_free(void* p)
{
  mi_page_t* const page = mi_validate_ptr_page(p,"mi_free");
  if (__builtin_expect(!!(page==0),0)) return;
  ((p!=0 && page!=0) ? (void)0 : _mi_assert_fail("p!=NULL && page!=NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",169,__func__));

  const mi_threadid_t xtid = (_mi_prim_thread_id() ^ mi_page_xthread_id(page));
  if (__builtin_expect(!!(xtid == 0),1)) {

    mi_block_t* const block = mi_validate_block_from_ptr(page,p);
    mi_free_block_local(page, block, 1 , 0 );
  }
  else if (xtid <= 0x03UL) {

    mi_free_generic_local(page, p);
  }

  else if ((xtid & 0x03UL) == 0) {

    mi_block_t* const block = mi_validate_block_from_ptr(page,p);
    mi_free_block_mt(page,block);
  }
  else {

    mi_free_generic_mt(page, p);
  }
}





static bool mi_page_unown_from_free(mi_page_t* page, mi_block_t* mt_free);

static inline bool mi_page_queue_len_is_atmost( mi_heap_t* heap, size_t block_size, long atmost) {
  mi_page_queue_t* const pq = mi_page_queue(heap,block_size);
  ((pq!=0) ? (void)0 : _mi_assert_fail("pq!=NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",201,__func__));
  return (pq->count <= (size_t)atmost);
}

static void mi_free_try_collect_mt(mi_page_t* page, mi_block_t* mt_free) {
  ((mi_page_is_owned(page)) ? (void)0 : _mi_assert_fail("mi_page_is_owned(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",206,__func__));
  ((mi_page_is_abandoned(page)) ? (void)0 : _mi_assert_fail("mi_page_is_abandoned(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",207,__func__));




  _mi_page_free_collect_partly(page, mt_free);


  if (mi_page_is_singleton(page)) { ((mi_page_all_free(page)) ? (void)0 : _mi_assert_fail("mi_page_all_free(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",215,__func__)); }



  if (mi_page_all_free(page))
  {

    _mi_arenas_page_unabandon(page);

    _mi_arenas_page_free(page,0);
    return;
  }
# 235 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c"
  if (page->block_size <= ((((1) * (1UL << (13 + (3))))-(((3)+2)*32))/8))
  {
    const long reclaim_on_free = _mi_option_get_fast(mi_option_page_reclaim_on_free);
    if (reclaim_on_free >= 0) {



      mi_heap_t* heap = mi_prim_get_default_heap();
      if (heap != page->heap) {
        if (mi_heap_is_initialized(heap)) {
          heap = _mi_heap_by_tag(heap, page->heap_tag);
        }
      }

      if (heap != 0 && heap->allow_page_reclaim)
      {
        long max_reclaim = 0;
        if (__builtin_expect(!!(heap == page->heap),1)) {

          max_reclaim = _mi_option_get_fast(heap->tld->is_in_threadpool ? mi_option_page_cross_thread_max_reclaim : mi_option_page_max_reclaim);
        }
        else if (reclaim_on_free == 1 &&
                 !heap->tld->is_in_threadpool &&
                 !mi_page_is_used_at_frac(page,8) &&
                 _mi_arena_memid_is_suitable(page->memid, heap->exclusive_arena)) {

          max_reclaim = _mi_option_get_fast(mi_option_page_cross_thread_max_reclaim);
        }

        if (max_reclaim < 0 || mi_page_queue_len_is_atmost(heap, page->block_size, max_reclaim)) {


          _mi_arenas_page_unabandon(page);
          _mi_heap_page_reclaim(heap, page);
          __mi_stat_counter_increase( &(heap->tld)->stats.pages_reclaim_on_free, 1);
          return;
        }
      }
    }
  }


  if (!mi_page_is_used_at_frac(page, 8) &&
      !mi_page_is_abandoned_mapped(page) && page->memid.memkind == MI_MEM_ARENA &&
      _mi_arenas_page_try_reabandon_to_mapped(page))
  {
    return;
  }




  mi_page_unown_from_free(page, mt_free);
}





static bool mi_page_unown_from_free(mi_page_t* page, mi_block_t* mt_free) {
  ((mi_page_is_owned(page)) ? (void)0 : _mi_assert_fail("mi_page_is_owned(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",295,__func__));
  ((mi_page_is_abandoned(page)) ? (void)0 : _mi_assert_fail("mi_page_is_abandoned(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",296,__func__));
  ((mt_free != 0) ? (void)0 : _mi_assert_fail("mt_free != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",297,__func__));
  ((page->used > 1) ? (void)0 : _mi_assert_fail("page->used > 1","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",298,__func__));
  mi_thread_free_t tf_expect = mi_tf_create(mt_free, 1);
  mi_thread_free_t tf_new = mi_tf_create(mt_free, 0);
  while (__builtin_expect(!!(!atomic_compare_exchange_weak_explicit(&page->xthread_free,&tf_expect,tf_new,memory_order_acq_rel,memory_order_acquire)),0)) {
    ((mi_tf_is_owned(tf_expect)) ? (void)0 : _mi_assert_fail("mi_tf_is_owned(tf_expect)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",302,__func__));
    while (mi_tf_block(tf_expect) != 0) {
      _mi_page_free_collect(page,0);
      if (mi_page_all_free(page)) {
        _mi_arenas_page_unabandon(page);
        _mi_arenas_page_free(page,0);
        return 1;
      }
      tf_expect = atomic_load_explicit(&page->xthread_free,memory_order_relaxed);
    }
    ((mi_tf_block(tf_expect)==0) ? (void)0 : _mi_assert_fail("mi_tf_block(tf_expect)==NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",312,__func__));
    tf_new = mi_tf_create(0, 0);
  }
  return 0;
}







static size_t mi_page_usable_aligned_size_of(const mi_page_t* page, const void* p) {
  const mi_block_t* block = _mi_page_ptr_unalign(page, p);
  const size_t size = mi_page_usable_size_of(page, block);
  const ptrdiff_t adjust = (uint8_t*)p - (uint8_t*)block;
  ((adjust >= 0 && (size_t)adjust <= size) ? (void)0 : _mi_assert_fail("adjust >= 0 && (size_t)adjust <= size","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",328,__func__));
  const size_t aligned_size = (size - adjust);





  return aligned_size;
}

static inline size_t _mi_usable_size(const void* p, const char* msg) {
  const mi_page_t* const page = mi_validate_ptr_page(p,msg);
  if (__builtin_expect(!!(page==0),0)) return 0;
  if (__builtin_expect(!!(!mi_page_has_interior_pointers(page)),1)) {
    const mi_block_t* block = (const mi_block_t*)p;
    return mi_page_usable_size_of(page, block);
  }
  else {

    return mi_page_usable_aligned_size_of(page, p);
  }
}

 size_t mi_usable_size(const void* p) {
  return _mi_usable_size(p, "mi_usable_size");
}






void mi_free_size(void* p, size_t size) {
  ;

  const size_t available = _mi_usable_size(p,"mi_free_size");
  ((p == 0 || size <= available || available == 0) ? (void)0 : _mi_assert_fail("p == NULL || size <= available || available == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",364,__func__));

  mi_free(p);
}

void mi_free_size_aligned(void* p, size_t size, size_t alignment) {
  ;
  ((((uintptr_t)p % alignment) == 0) ? (void)0 : _mi_assert_fail("((uintptr_t)p % alignment) == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",371,__func__));
  mi_free_size(p,size);
}

void mi_free_aligned(void* p, size_t alignment) {
  ;
  ((((uintptr_t)p % alignment) == 0) ? (void)0 : _mi_assert_fail("((uintptr_t)p % alignment) == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",377,__func__));
  mi_free(p);
}
# 389 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c"
static bool mi_list_contains(const mi_page_t* page, const mi_block_t* list, const mi_block_t* elem) {
  while (list != 0) {
    if (elem==list) return 1;
    list = mi_block_next(page, list);
  }
  return 0;
}

static bool mi_check_is_double_freex(const mi_page_t* page, const mi_block_t* block) {


  if (mi_list_contains(page, page->free, block) ||
      mi_list_contains(page, page->local_free, block) ||
      mi_list_contains(page, mi_page_thread_free(page), block))
  {
    _mi_error_message((11), "double free detected of block %p with size %zu\n", block, mi_page_block_size(page));
    return 1;
  }
  return 0;
}



static inline bool mi_check_is_double_free(const mi_page_t* page, const mi_block_t* block) {
  bool is_double_free = 0;
  mi_block_t* n = mi_block_nextx(page, block, page->keys);
  if (((uintptr_t)n & ((1<<(3))-1))==0 &&
      (n==0 || mi_is_in_same_page(block, n)))
  {


    is_double_free = mi_check_is_double_freex(page, block);
  }
  return is_double_free;
}
# 438 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c"
static bool mi_page_decode_padding(const mi_page_t* page, const mi_block_t* block, size_t* delta, size_t* bsize) {
  *bsize = mi_page_usable_block_size(page);
  const mi_padding_t* const padding = (mi_padding_t*)((uint8_t*)block + *bsize);
  ;
  *delta = padding->delta;
  uint32_t canary = padding->canary;
  uintptr_t keys[2];
  keys[0] = page->keys[0];
  keys[1] = page->keys[1];
  bool ok = (mi_ptr_encode_canary(page,block,keys) == canary && *delta <= *bsize);
  ;
  return ok;
}


static size_t mi_page_usable_size_of(const mi_page_t* page, const mi_block_t* block) {
  size_t bsize;
  size_t delta;
  bool ok = mi_page_decode_padding(page, block, &delta, &bsize);
  ((ok) ? (void)0 : _mi_assert_fail("ok","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",457,__func__)); ((delta <= bsize) ? (void)0 : _mi_assert_fail("delta <= bsize","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",457,__func__));
  return (ok ? bsize - delta : 0);
}





void _mi_padding_shrink(const mi_page_t* page, const mi_block_t* block, const size_t min_size) {
  size_t bsize;
  size_t delta;
  bool ok = mi_page_decode_padding(page, block, &delta, &bsize);
  ((ok) ? (void)0 : _mi_assert_fail("ok","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",469,__func__));
  if (!ok || (bsize - delta) >= min_size) return;
  ((bsize >= min_size) ? (void)0 : _mi_assert_fail("bsize >= min_size","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",471,__func__));
  if (bsize < min_size) return;
  size_t new_delta = (bsize - min_size);
  ((new_delta < bsize) ? (void)0 : _mi_assert_fail("new_delta < bsize","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",474,__func__));
  mi_padding_t* padding = (mi_padding_t*)((uint8_t*)block + bsize);
  ;
  padding->delta = (uint32_t)new_delta;
  ;
}
# 495 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c"
static bool mi_verify_padding(const mi_page_t* page, const mi_block_t* block, size_t* size, size_t* wrong) {
  size_t bsize;
  size_t delta;
  bool ok = mi_page_decode_padding(page, block, &delta, &bsize);
  *size = *wrong = bsize;
  if (!ok) return 0;
  ((bsize >= delta) ? (void)0 : _mi_assert_fail("bsize >= delta","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",501,__func__));
  *size = bsize - delta;
  if (!mi_page_is_huge(page)) {
    uint8_t* fill = (uint8_t*)block + bsize - delta;
    const size_t maxpad = (delta > 16 ? 16 : delta);
    ;
    for (size_t i = 0; i < maxpad; i++) {
      if (fill[i] != (0xDE)) {
        *wrong = bsize - delta + i;
        ok = 0;
        break;
      }
    }
    ;
  }
  return ok;
}

static void mi_check_padding(const mi_page_t* page, const mi_block_t* block) {
  size_t size;
  size_t wrong;
  if (!mi_verify_padding(page,block,&size,&wrong)) {
    _mi_error_message((14), "buffer overflow in heap block %p of size %zu: write after %zu bytes\n", block, size, wrong );
  }
}
# 538 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c"
static void mi_stat_free(const mi_page_t* page, const mi_block_t* block) {
  (void)(block);
  mi_heap_t* const heap = mi_heap_get_default();
  const size_t bsize = mi_page_usable_block_size(page);




  if (bsize <= ((8*((1) * (1UL << (13 + (3)))))/8)) {
    __mi_stat_decrease( &(heap->tld)->stats.malloc_normal, bsize);

    __mi_stat_decrease( &(heap->tld)->stats.malloc_bins[_mi_bin(bsize)], 1);

  }
  else {
    const size_t bpsize = mi_page_block_size(page);
    __mi_stat_decrease( &(heap->tld)->stats.malloc_huge, bpsize);
  }
}
# 22 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c" 2
# 31 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c"
extern inline void* _mi_page_malloc_zero(mi_heap_t* heap, mi_page_t* page, size_t size, bool zero)
{
  if (page->block_size != 0) {
    ((mi_page_block_size(page) >= size) ? (void)0 : _mi_assert_fail("mi_page_block_size(page) >= size","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c",34,__func__));
    ((_mi_is_aligned(page, ((1UL << (13 + (3)))))) ? (void)0 : _mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c",35,__func__));
    ((_mi_ptr_page(page)==page) ? (void)0 : _mi_assert_fail("_mi_ptr_page(page)==page","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c",36,__func__));
  }


  mi_block_t* const block = page->free;
  if (__builtin_expect(!!(block == 0),0)) {
    return _mi_malloc_generic(heap, size, zero, 0);
  }
  ((block != 0 && _mi_ptr_page(block) == page) ? (void)0 : _mi_assert_fail("block != NULL && _mi_ptr_page(block) == page","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c",44,__func__));


  page->free = mi_block_next(page, block);
  page->used++;
  ((page->free == 0 || _mi_ptr_page(page->free) == page) ? (void)0 : _mi_assert_fail("page->free == NULL || _mi_ptr_page(page->free) == page","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c",49,__func__));
  ((page->block_size < 16 || _mi_is_aligned(block, 16)) ? (void)0 : _mi_assert_fail("page->block_size < MI_MAX_ALIGN_SIZE || _mi_is_aligned(block, MI_MAX_ALIGN_SIZE)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c",50,__func__));
# 61 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c"
  const size_t bsize = mi_page_usable_block_size(page);
  ;


  if (__builtin_expect(!!(zero),0)) {
    if (page->free_is_zero) {
      block->next = 0;
      ;
    }
    else {
      _mi_memzero_aligned(block, bsize);
    }
  }


  if (!zero && !mi_page_is_huge(page)) {
    memset(block, (0xD0), bsize);
  }





  if (bsize <= ((8*((1) * (1UL << (13 + (3)))))/8)) {
    __mi_stat_increase( &(heap->tld)->stats.malloc_normal, bsize);
    __mi_stat_counter_increase( &(heap->tld)->stats.malloc_normal_count, 1);

    const size_t bin = _mi_bin(bsize);
    __mi_stat_increase( &(heap->tld)->stats.malloc_bins[bin], 1);
    __mi_stat_increase( &(heap->tld)->stats.malloc_requested, size - (sizeof(mi_padding_t)));

  }



    mi_padding_t* const padding = (mi_padding_t*)((uint8_t*)block + bsize);
    ptrdiff_t delta = ((uint8_t*)padding - (uint8_t*)block - (size - (sizeof(mi_padding_t))));

    ((delta >= 0 && bsize >= (size - (sizeof(mi_padding_t)) + delta)) ? (void)0 : _mi_assert_fail("delta >= 0 && bsize >= (size - MI_PADDING_SIZE + delta)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c",99,__func__));

    ;
    padding->canary = mi_ptr_encode_canary(page,block,page->keys);
    padding->delta = (uint32_t)(delta);

    if (!mi_page_is_huge(page)) {
      uint8_t* fill = (uint8_t*)padding - delta;
      const size_t maxpad = (delta > 16 ? 16 : delta);
      for (size_t i = 0; i < maxpad; i++) { fill[i] = (0xDE); }
    }



  return block;
}


extern void* _mi_page_malloc(mi_heap_t* heap, mi_page_t* page, size_t size) {
  return _mi_page_malloc_zero(heap,page,size,0);
}
extern void* _mi_page_malloc_zeroed(mi_heap_t* heap, mi_page_t* page, size_t size) {
  return _mi_page_malloc_zero(heap,page,size,1);
}





static inline void* mi_heap_malloc_small_zero(mi_heap_t* heap, size_t size, bool zero) {
  ((heap != 0) ? (void)0 : _mi_assert_fail("heap != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c",129,__func__));
  ((size <= ((128)*sizeof(void*))) ? (void)0 : _mi_assert_fail("size <= MI_SMALL_SIZE_MAX","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c",130,__func__));

  const uintptr_t tid = _mi_thread_id();
  ((heap->tld->thread_id == 0 || heap->tld->thread_id == tid) ? (void)0 : _mi_assert_fail("heap->tld->thread_id == 0 || heap->tld->thread_id == tid","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c",133,__func__));


  if (size == 0) { size = sizeof(void*); }
# 145 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c"
  mi_page_t* page = _mi_heap_get_free_small_page(heap, size + (sizeof(mi_padding_t)));
  void* const p = _mi_page_malloc_zero(heap, page, size + (sizeof(mi_padding_t)), zero);
  if ((p)!=0) { ((mi_usable_size(p)==(size)) ? (void)0 : _mi_assert_fail("mi_usable_size(p)==(size)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c",147,__func__)); ; };






  return p;
}


 extern inline void* mi_heap_malloc_small(mi_heap_t* heap, size_t size) {
  return mi_heap_malloc_small_zero(heap, size, 0);
}

 extern inline void* mi_malloc_small(size_t size) {
  return mi_heap_malloc_small(mi_prim_get_default_heap(), size);
}


extern inline void* _mi_heap_malloc_zero_ex(mi_heap_t* heap, size_t size, bool zero, size_t huge_alignment) {

  if (__builtin_expect(!!(size <= ((128)*sizeof(void*))),1)) {
    ((huge_alignment == 0) ? (void)0 : _mi_assert_fail("huge_alignment == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c",170,__func__));
    return mi_heap_malloc_small_zero(heap, size, zero);
  }





  else {

    ((heap!=0) ? (void)0 : _mi_assert_fail("heap!=NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c",180,__func__));
    ((heap->tld->thread_id == 0 || heap->tld->thread_id == _mi_thread_id()) ? (void)0 : _mi_assert_fail("heap->tld->thread_id == 0 || heap->tld->thread_id == _mi_thread_id()","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c",181,__func__));
    void* const p = _mi_malloc_generic(heap, size + (sizeof(mi_padding_t)), zero, huge_alignment);
    if ((p)!=0) { ((mi_usable_size(p)==(size)) ? (void)0 : _mi_assert_fail("mi_usable_size(p)==(size)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c",183,__func__)); ; };






    return p;
  }
}

extern inline void* _mi_heap_malloc_zero(mi_heap_t* heap, size_t size, bool zero) {
  return _mi_heap_malloc_zero_ex(heap, size, zero, 0);
}

 extern inline void* mi_heap_malloc(mi_heap_t* heap, size_t size) {
  return _mi_heap_malloc_zero(heap, size, 0);
}

 extern inline void* mi_malloc(size_t size) {
  return mi_heap_malloc(mi_prim_get_default_heap(), size);
}


 void* mi_zalloc_small(size_t size) {
  return mi_heap_malloc_small_zero(mi_prim_get_default_heap(), size, 1);
}

 extern inline void* mi_heap_zalloc(mi_heap_t* heap, size_t size) {
  return _mi_heap_malloc_zero(heap, size, 1);
}

 void* mi_zalloc(size_t size) {
  return mi_heap_zalloc(mi_prim_get_default_heap(),size);
}


 extern inline void* mi_heap_calloc(mi_heap_t* heap, size_t count, size_t size) {
  size_t total;
  if (mi_count_size_overflow(count,size,&total)) return 0;
  return mi_heap_zalloc(heap,total);
}

 void* mi_calloc(size_t count, size_t size) {
  return mi_heap_calloc(mi_prim_get_default_heap(),count,size);
}


 extern void* mi_heap_mallocn(mi_heap_t* heap, size_t count, size_t size) {
  size_t total;
  if (mi_count_size_overflow(count, size, &total)) return 0;
  return mi_heap_malloc(heap, total);
}

 void* mi_mallocn(size_t count, size_t size) {
  return mi_heap_mallocn(mi_prim_get_default_heap(),count,size);
}


void* mi_expand(void* p, size_t newsize) {


  (void)(p); (void)(newsize);
  return 0;






}

void* _mi_heap_realloc_zero(mi_heap_t* heap, void* p, size_t newsize, bool zero) {



  const size_t size = (p==0 ? 0 : _mi_usable_size(p,"mi_realloc"));
  if (__builtin_expect(!!(newsize <= size && newsize >= (size / 2) && newsize > 0),0)) {
    ((p!=0) ? (void)0 : _mi_assert_fail("p!=NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c",261,__func__));



    return p;
  }
  void* newp = mi_heap_malloc(heap,newsize);
  if (__builtin_expect(!!(newp != 0),1)) {
    if (zero && newsize > size) {

      const size_t start = (size >= sizeof(intptr_t) ? size - sizeof(intptr_t) : 0);
      _mi_memzero((uint8_t*)newp + start, newsize - start);
    }
    else if (newsize == 0) {
      ((uint8_t*)newp)[0] = 0;
    }
    if (__builtin_expect(!!(p != 0),1)) {
      const size_t copysize = (newsize > size ? size : newsize);
      ;
      _mi_memcpy(newp, p, copysize);
      mi_free(p);
    }
  }
  return newp;
}

 void* mi_heap_realloc(mi_heap_t* heap, void* p, size_t newsize) {
  return _mi_heap_realloc_zero(heap, p, newsize, 0);
}

 void* mi_heap_reallocn(mi_heap_t* heap, void* p, size_t count, size_t size) {
  size_t total;
  if (mi_count_size_overflow(count, size, &total)) return 0;
  return mi_heap_realloc(heap, p, total);
}



 void* mi_heap_reallocf(mi_heap_t* heap, void* p, size_t newsize) {
  void* newp = mi_heap_realloc(heap, p, newsize);
  if (newp==0 && p!=0) mi_free(p);
  return newp;
}

 void* mi_heap_rezalloc(mi_heap_t* heap, void* p, size_t newsize) {
  return _mi_heap_realloc_zero(heap, p, newsize, 1);
}

 void* mi_heap_recalloc(mi_heap_t* heap, void* p, size_t count, size_t size) {
  size_t total;
  if (mi_count_size_overflow(count, size, &total)) return 0;
  return mi_heap_rezalloc(heap, p, total);
}


 void* mi_realloc(void* p, size_t newsize) {
  return mi_heap_realloc(mi_prim_get_default_heap(),p,newsize);
}

 void* mi_reallocn(void* p, size_t count, size_t size) {
  return mi_heap_reallocn(mi_prim_get_default_heap(),p,count,size);
}


 void* mi_reallocf(void* p, size_t newsize) {
  return mi_heap_reallocf(mi_prim_get_default_heap(),p,newsize);
}

 void* mi_rezalloc(void* p, size_t newsize) {
  return mi_heap_rezalloc(mi_prim_get_default_heap(), p, newsize);
}

 void* mi_recalloc(void* p, size_t count, size_t size) {
  return mi_heap_recalloc(mi_prim_get_default_heap(), p, count, size);
}
# 344 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c"
 char* mi_heap_strdup(mi_heap_t* heap, const char* s) {
  if (s == 0) return 0;
  size_t len = _mi_strlen(s);
  char* t = (char*)mi_heap_malloc(heap,len+1);
  if (t == 0) return 0;
  _mi_memcpy(t, s, len);
  t[len] = 0;
  return t;
}

 char* mi_strdup(const char* s) {
  return mi_heap_strdup(mi_prim_get_default_heap(), s);
}


 char* mi_heap_strndup(mi_heap_t* heap, const char* s, size_t n) {
  if (s == 0) return 0;
  const size_t len = _mi_strnlen(s,n);
  char* t = (char*)mi_heap_malloc(heap, len+1);
  if (t == 0) return 0;
  _mi_memcpy(t, s, len);
  t[len] = 0;
  return t;
}

 char* mi_strndup(const char* s, size_t n) {
  return mi_heap_strndup(mi_prim_get_default_heap(),s,n);
}
# 411 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c"
char* mi_heap_realpath(mi_heap_t* heap, const char* fname, char* resolved_name) {
  if (resolved_name != 0) {
    return realpath(fname,resolved_name);
  }
  else {
    char* rname = realpath(fname, 0);
    if (rname == 0) return 0;
    char* result = mi_heap_strdup(heap, rname);
    mi_cfree(rname);

    return result;
  }
# 436 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c"
}


 char* mi_realpath(const char* fname, char* resolved_name) {
  return mi_heap_realpath(mi_prim_get_default_heap(),fname,resolved_name);
}
# 479 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc.c"
typedef void (*std_new_handler_t)(void);


std_new_handler_t _ZSt15get_new_handlerv(void) {
  return 0;
}
static std_new_handler_t mi_get_new_handler(void) {
  return _ZSt15get_new_handlerv();
}







static bool mi_try_new_handler(bool nothrow) {
  std_new_handler_t h = mi_get_new_handler();
  if (h==0) {
    _mi_error_message((12), "out of memory in 'new'");
    if (!nothrow) {
      abort();
    }
    return 0;
  }
  else {
    h();
    return 1;
  }
}


 void* mi_heap_try_new(mi_heap_t* heap, size_t size, bool nothrow ) {
  void* p = 0;
  while(p == 0 && mi_try_new_handler(nothrow)) {
    p = mi_heap_malloc(heap,size);
  }
  return p;
}

static void* mi_try_new(size_t size, bool nothrow) {
  return mi_heap_try_new(mi_prim_get_default_heap(), size, nothrow);
}


 void* mi_heap_alloc_new(mi_heap_t* heap, size_t size) {
  void* p = mi_heap_malloc(heap,size);
  if (__builtin_expect(!!(p == 0),0)) return mi_heap_try_new(heap, size, 0);
  return p;
}

 void* mi_new(size_t size) {
  return mi_heap_alloc_new(mi_prim_get_default_heap(), size);
}


 void* mi_heap_alloc_new_n(mi_heap_t* heap, size_t count, size_t size) {
  size_t total;
  if (__builtin_expect(!!(mi_count_size_overflow(count, size, &total)),0)) {
    mi_try_new_handler(0);
    return 0;
  }
  else {
    return mi_heap_alloc_new(heap,total);
  }
}

 void* mi_new_n(size_t count, size_t size) {
  return mi_heap_alloc_new_n(mi_prim_get_default_heap(), count, size);
}


 void* mi_new_nothrow(size_t size) {
  void* p = mi_malloc(size);
  if (__builtin_expect(!!(p == 0),0)) return mi_try_new(size, 1);
  return p;
}

 void* mi_new_aligned(size_t size, size_t alignment) {
  void* p;
  do {
    p = mi_malloc_aligned(size, alignment);
  }
  while(p == 0 && mi_try_new_handler(0));
  return p;
}

 void* mi_new_aligned_nothrow(size_t size, size_t alignment) {
  void* p;
  do {
    p = mi_malloc_aligned(size, alignment);
  }
  while(p == 0 && mi_try_new_handler(1));
  return p;
}

 void* mi_new_realloc(void* p, size_t newsize) {
  void* q;
  do {
    q = mi_realloc(p, newsize);
  } while (q == 0 && mi_try_new_handler(0));
  return q;
}

 void* mi_new_reallocn(void* p, size_t newcount, size_t size) {
  size_t total;
  if (__builtin_expect(!!(mi_count_size_overflow(newcount, size, &total)),0)) {
    mi_try_new_handler(0);
    return 0;
  }
  else {
    return mi_new_realloc(p, total);
  }
}
# 0 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-override.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/alloc-override.c"
# 0 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c"
# 9 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c"
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
# 10 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c" 2
# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h" 1






       
# 16 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
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
# 17 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h" 2
# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/track.h" 1






       
# 18 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h" 2
# 120 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdarg.h" 1
# 121 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h" 2
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
void _mi_raw_message(const char* fmt, ...);
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

mi_subproc_t* _mi_subproc(void);
mi_subproc_t* _mi_subproc_main(void);
mi_subproc_t* _mi_subproc_from_id(mi_subproc_id_t subproc_id);
mi_threadid_t _mi_thread_id(void) ;
size_t _mi_thread_seq_id(void) ;
mi_tld_t* _mi_thread_tld(void) ;
void _mi_heap_guarded_init(mi_heap_t* heap);
mi_heap_t* _mi_heap_main_get(void);


void _mi_os_init(void);
void* _mi_os_alloc(size_t size, mi_memid_t* memid);
void* _mi_os_zalloc(size_t size, mi_memid_t* memid);
void _mi_os_free(void* p, size_t size, mi_memid_t memid);
void _mi_os_free_ex(void* p, size_t size, bool still_committed, mi_memid_t memid, mi_subproc_t* subproc );

size_t _mi_os_page_size(void);
size_t _mi_os_guard_page_size(void);
size_t _mi_os_good_alloc_size(size_t size);
bool _mi_os_has_overcommit(void);
bool _mi_os_has_virtual_reserve(void);
size_t _mi_os_virtual_address_bits(void);

bool _mi_os_reset(void* addr, size_t size);
bool _mi_os_decommit(void* addr, size_t size);
void _mi_os_reuse(void* p, size_t size);
 bool _mi_os_commit(void* p, size_t size, bool* is_zero);
 bool _mi_os_commit_ex(void* addr, size_t size, bool* is_zero, size_t stat_size);
 bool _mi_os_protect(void* addr, size_t size);
bool _mi_os_unprotect(void* addr, size_t size);
bool _mi_os_purge(void* p, size_t size);
bool _mi_os_purge_ex(void* p, size_t size, bool allow_reset, size_t stats_size, mi_commit_fun_t* commit_fun, void* commit_fun_arg);

size_t _mi_os_secure_guard_page_size(void);
bool _mi_os_secure_guard_page_set_at(void* addr, mi_memid_t memid);
bool _mi_os_secure_guard_page_set_before(void* addr, mi_memid_t memid);
bool _mi_os_secure_guard_page_reset_at(void* addr, mi_memid_t memid);
bool _mi_os_secure_guard_page_reset_before(void* addr, mi_memid_t memid);

int _mi_os_numa_node(void);
int _mi_os_numa_node_count(void);

void* _mi_os_alloc_aligned(size_t size, size_t alignment, bool commit, bool allow_large, mi_memid_t* memid);
void* _mi_os_alloc_aligned_at_offset(size_t size, size_t alignment, size_t align_offset, bool commit, bool allow_large, mi_memid_t* memid);

void* _mi_os_get_aligned_hint(size_t try_alignment, size_t size);
bool _mi_os_use_large_page(size_t size, size_t alignment);
size_t _mi_os_large_page_size(void);
void* _mi_os_alloc_huge_os_pages(size_t pages, int numa_node, mi_msecs_t max_secs, size_t* pages_reserved, size_t* psize, mi_memid_t* memid);



mi_arena_id_t _mi_arena_id_none(void);
mi_arena_t* _mi_arena_from_id(mi_arena_id_t id);
bool _mi_arena_memid_is_suitable(mi_memid_t memid, mi_arena_t* request_arena);

void* _mi_arenas_alloc(mi_subproc_t* subproc, size_t size, bool commit, bool allow_pinned, mi_arena_t* req_arena, size_t tseq, int numa_node, mi_memid_t* memid);
void* _mi_arenas_alloc_aligned(mi_subproc_t* subproc, size_t size, size_t alignment, size_t align_offset, bool commit, bool allow_pinned, mi_arena_t* req_arena, size_t tseq, int numa_node, mi_memid_t* memid);
void _mi_arenas_free(void* p, size_t size, mi_memid_t memid);
bool _mi_arenas_contain(const void* p);
void _mi_arenas_collect(bool force_purge, bool visit_all, mi_tld_t* tld);
void _mi_arenas_unsafe_destroy_all(mi_subproc_t* subproc);

mi_page_t* _mi_arenas_page_alloc(mi_heap_t* heap, size_t block_size, size_t page_alignment);
void _mi_arenas_page_free(mi_page_t* page, mi_tld_t* tld);
void _mi_arenas_page_abandon(mi_page_t* page, mi_tld_t* tld);
void _mi_arenas_page_unabandon(mi_page_t* page);
bool _mi_arenas_page_try_reabandon_to_mapped(mi_page_t* page);


void* _mi_meta_zalloc( size_t size, mi_memid_t* memid );
void _mi_meta_free(void* p, size_t size, mi_memid_t memid);
bool _mi_meta_is_meta_page(void* p);


bool _mi_page_map_init(void);
 bool _mi_page_map_register(mi_page_t* page);
void _mi_page_map_unregister(mi_page_t* page);
void _mi_page_map_unregister_range(void* start, size_t size);
mi_page_t* _mi_safe_ptr_page(const void* p);
void _mi_page_map_unsafe_destroy(mi_subproc_t* subproc);


void* _mi_malloc_generic(mi_heap_t* heap, size_t size, bool zero, size_t huge_alignment) ;

void _mi_page_retire(mi_page_t* page) ;
void _mi_page_unfull(mi_page_t* page);
void _mi_page_free(mi_page_t* page, mi_page_queue_t* pq);
void _mi_page_abandon(mi_page_t* page, mi_page_queue_t* pq);
void _mi_heap_collect_retired(mi_heap_t* heap, bool force);

size_t _mi_page_queue_append(mi_heap_t* heap, mi_page_queue_t* pq, mi_page_queue_t* append);
void _mi_deferred_free(mi_heap_t* heap, bool force);

void _mi_page_free_collect(mi_page_t* page, bool force);
void _mi_page_free_collect_partly(mi_page_t* page, mi_block_t* head);
 bool _mi_page_init(mi_heap_t* heap, mi_page_t* page);
bool _mi_page_queue_is_valid(mi_heap_t* heap, const mi_page_queue_t* pq);

size_t _mi_page_bin(const mi_page_t* page);
size_t _mi_bin_size(size_t bin);
size_t _mi_bin(size_t size);


mi_heap_t* _mi_heap_create(int heap_tag, bool allow_destroy, mi_arena_id_t arena_id, mi_tld_t* tld);
void _mi_heap_init(mi_heap_t* heap, mi_arena_id_t arena_id, bool noreclaim, uint8_t tag, mi_tld_t* tld);
void _mi_heap_destroy_pages(mi_heap_t* heap);
void _mi_heap_collect_abandon(mi_heap_t* heap);
void _mi_heap_set_default_direct(mi_heap_t* heap);
bool _mi_heap_memid_is_suitable(mi_heap_t* heap, mi_memid_t memid);
void _mi_heap_unsafe_destroy_all(mi_heap_t* heap);
mi_heap_t* _mi_heap_by_tag(mi_heap_t* heap, uint8_t tag);
void _mi_heap_area_init(mi_heap_area_t* area, mi_page_t* page);
bool _mi_heap_area_visit_blocks(const mi_heap_area_t* area, mi_page_t* page, mi_block_visit_fun* visitor, void* arg);
void _mi_heap_page_reclaim(mi_heap_t* heap, mi_page_t* page);


void _mi_stats_init(void);
void _mi_stats_done(mi_stats_t* stats);
void _mi_stats_print(mi_stats_t* stats, mi_output_fun* out, void* arg) ;
void _mi_stats_merge_thread(mi_tld_t* tld);
void _mi_stats_merge_from(mi_stats_t* to, mi_stats_t* from);
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
void _mi_padding_shrink(const mi_page_t* page, const mi_block_t* block, const size_t min_size);


bool _mi_page_is_valid(mi_page_t* page);
# 312 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
 void _mi_assert_fail(const char* assertion, const char* fname, unsigned int line, const char* func) ;
# 336 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
void __mi_stat_increase(mi_stat_count_t* stat, size_t amount);
void __mi_stat_decrease(mi_stat_count_t* stat, size_t amount);
void __mi_stat_increase_mt(mi_stat_count_t* stat, size_t amount);
void __mi_stat_decrease_mt(mi_stat_count_t* stat, size_t amount);


void __mi_stat_adjust_increase(mi_stat_count_t* stat, size_t amount);
void __mi_stat_adjust_decrease(mi_stat_count_t* stat, size_t amount);
void __mi_stat_adjust_increase_mt(mi_stat_count_t* stat, size_t amount);
void __mi_stat_adjust_decrease_mt(mi_stat_count_t* stat, size_t amount);


void __mi_stat_counter_increase(mi_stat_counter_t* stat, size_t amount);
void __mi_stat_counter_increase_mt(mi_stat_counter_t* stat, size_t amount);
# 375 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
typedef enum mi_option_init_e {
  MI_OPTION_UNINIT,
  MI_OPTION_DEFAULTED,
  MI_OPTION_INITIALIZED
} mi_option_init_t;

typedef struct mi_option_desc_s {
  long value;
  mi_option_init_t init;
  mi_option_t option;
  const char* name;
  const char* legacy_name;
} mi_option_desc_t;
# 412 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 413 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h" 2




static inline bool _mi_is_power_of_two(uintptr_t x) {
  return ((x & (x - 1)) == 0);
}


static inline bool _mi_is_aligned(void* p, size_t alignment) {
  ((alignment != 0) ? (void)0 : _mi_assert_fail("alignment != 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",423,__func__));
  return (((uintptr_t)p % alignment) == 0);
}


static inline uintptr_t _mi_align_up(uintptr_t sz, size_t alignment) {
  ((alignment != 0) ? (void)0 : _mi_assert_fail("alignment != 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",429,__func__));
  uintptr_t mask = alignment - 1;
  if ((alignment & mask) == 0) {
    return ((sz + mask) & ~mask);
  }
  else {
    return (((sz + mask)/alignment)*alignment);
  }
}



static inline uint8_t* _mi_align_up_ptr(void* p, size_t alignment) {
  return (uint8_t*)_mi_align_up((uintptr_t)p, alignment);
}


static inline uintptr_t _mi_align_down(uintptr_t sz, size_t alignment) {
  ((alignment != 0) ? (void)0 : _mi_assert_fail("alignment != 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",447,__func__));
  uintptr_t mask = alignment - 1;
  if ((alignment & mask) == 0) {
    return (sz & ~mask);
  }
  else {
    return ((sz / alignment) * alignment);
  }
}

static inline void* mi_align_down_ptr(void* p, size_t alignment) {
  return (void*)_mi_align_down((uintptr_t)p, alignment);
}


static inline uintptr_t _mi_divide_up(uintptr_t size, size_t divider) {
  ((divider != 0) ? (void)0 : _mi_assert_fail("divider != 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",463,__func__));
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
  ((size <= SIZE_MAX - sizeof(uintptr_t)) ? (void)0 : _mi_assert_fail("size <= SIZE_MAX - sizeof(uintptr_t)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",486,__func__));
  return (size + sizeof(uintptr_t) - 1) / sizeof(uintptr_t);
}



# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 1
# 493 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h" 2



static inline bool mi_mul_overflow(size_t count, size_t size, size_t* total) {





    return __builtin_umulll_overflow(count, size, (unsigned long long *)total);

}
# 515 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
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

static inline bool mi_heap_is_initialized(const mi_heap_t* heap) {
  ((heap != 0) ? (void)0 : _mi_assert_fail("heap != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",542,__func__));
  return (heap != 0 && heap != &_mi_heap_empty);
}

static inline mi_page_t* _mi_heap_get_free_small_page(mi_heap_t* heap, size_t size) {
  ((size <= (((128)*sizeof(void*)) + (sizeof(mi_padding_t)))) ? (void)0 : _mi_assert_fail("size <= (MI_SMALL_SIZE_MAX + MI_PADDING_SIZE)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",547,__func__));
  const size_t idx = _mi_wsize_from_size(size);
  ((idx < ((128) + (((sizeof(mi_padding_t)) + (1<<(3)) - 1) / (1<<(3))) + 1)) ? (void)0 : _mi_assert_fail("idx < MI_PAGES_DIRECT","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",549,__func__));
  return heap->pages_free_direct[idx];
}
# 607 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
typedef mi_page_t** mi_submap_t;
extern _Atomic(mi_submap_t)* _mi_page_map;

static inline size_t _mi_page_map_index(const void* p, size_t* sub_idx) {
  const size_t u = (size_t)((uintptr_t)p / (1UL << (13 + (3))));
  if (sub_idx != 0) { *sub_idx = u % (1UL << (13)); }
  return (u / (1UL << (13)));
}

static inline mi_submap_t _mi_page_map_at(size_t idx) {
  return atomic_load_explicit(&_mi_page_map[idx],memory_order_relaxed);
}

static inline mi_page_t* _mi_unchecked_ptr_page(const void* p) {
  size_t sub_idx;
  const size_t idx = _mi_page_map_index(p, &sub_idx);
  return (_mi_page_map_at(idx))[sub_idx];
}

static inline mi_page_t* _mi_checked_ptr_page(const void* p) {
  size_t sub_idx;
  const size_t idx = _mi_page_map_index(p, &sub_idx);
  mi_submap_t const sub = _mi_page_map_at(idx);
  if (__builtin_expect(!!(sub == 0),0)) return 0;
  return sub[sub_idx];
}




static inline mi_page_t* _mi_ptr_page(const void* p) {
  ((p==0 || mi_is_in_heap_region(p)) ? (void)0 : _mi_assert_fail("p==NULL || mi_is_in_heap_region(p)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",638,__func__));

  return _mi_checked_ptr_page(p);



}



static inline size_t mi_page_block_size(const mi_page_t* page) {
  ((page->block_size > 0) ? (void)0 : _mi_assert_fail("page->block_size > 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",649,__func__));
  return page->block_size;
}


static inline uint8_t* mi_page_start(const mi_page_t* page) {
  return page->page_start;
}

static inline size_t mi_page_size(const mi_page_t* page) {
  return mi_page_block_size(page) * page->reserved;
}

static inline uint8_t* mi_page_area(const mi_page_t* page, size_t* size) {
  if (size) { *size = mi_page_size(page); }
  return mi_page_start(page);
}

static inline size_t mi_page_info_size(void) {
  return _mi_align_up(sizeof(mi_page_t), 16);
}

static inline bool mi_page_contains_address(const mi_page_t* page, const void* p) {
  size_t psize;
  uint8_t* start = mi_page_area(page, &psize);
  return (start <= (uint8_t*)p && (uint8_t*)p < start + psize);
}

static inline bool mi_page_is_in_arena(const mi_page_t* page) {
  return (page->memid.memkind == MI_MEM_ARENA);
}

static inline bool mi_page_is_singleton(const mi_page_t* page) {
  return (page->reserved == 1);
}



static inline size_t mi_page_usable_block_size(const mi_page_t* page) {
  return mi_page_block_size(page) - (sizeof(mi_padding_t));
}


static inline uint8_t* mi_page_slice_start(const mi_page_t* page) {
  return (uint8_t*)page;
}



static inline size_t mi_page_slice_offset_of(const mi_page_t* page, size_t offset_relative_to_page_start) {
  return (page->page_start - mi_page_slice_start(page)) + offset_relative_to_page_start;
}

static inline size_t mi_page_committed(const mi_page_t* page) {
  return (page->slice_committed == 0 ? mi_page_size(page) : page->slice_committed - (page->page_start - mi_page_slice_start(page)));
}

static inline mi_heap_t* mi_page_heap(const mi_page_t* page) {
  return page->heap;
}




static inline bool mi_page_all_free(const mi_page_t* page) {
  ((page != 0) ? (void)0 : _mi_assert_fail("page != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",714,__func__));
  return (page->used == 0);
}


static inline bool mi_page_immediate_available(const mi_page_t* page) {
  ((page != 0) ? (void)0 : _mi_assert_fail("page != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",720,__func__));
  return (page->free != 0);
}



static inline bool mi_page_is_expandable(const mi_page_t* page) {
  ((page != 0) ? (void)0 : _mi_assert_fail("page != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",727,__func__));
  ((page->capacity <= page->reserved) ? (void)0 : _mi_assert_fail("page->capacity <= page->reserved","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",728,__func__));
  return (page->capacity < page->reserved);
}


static inline bool mi_page_is_full(mi_page_t* page) {
  const bool full = (page->reserved == page->used);
  ((!full || page->free == 0) ? (void)0 : _mi_assert_fail("!full || page->free == NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",735,__func__));
  return full;
}


static inline bool mi_page_is_mostly_used(const mi_page_t* page) {
  if (page==0) return 1;
  uint16_t frac = page->reserved / 8U;
  return (page->reserved - page->used <= frac);
}


static inline bool mi_page_is_used_at_frac(const mi_page_t* page, uint16_t n) {
  if (page==0) return 1;
  uint16_t frac = page->reserved / n;
  return (page->reserved - page->used <= frac);
}


static inline bool mi_page_is_huge(const mi_page_t* page) {
  return (mi_page_is_singleton(page) &&
          (page->block_size > ((8*((1) * (1UL << (13 + (3)))))/8) ||
           (mi_memkind_is_os(page->memid.memkind) && page->memid.mem.os.base < (void*)page)));
}

static inline mi_page_queue_t* mi_page_queue(const mi_heap_t* heap, size_t size) {
  mi_page_queue_t* const pq = &((mi_heap_t*)heap)->pages[_mi_bin(size)];
  if (size <= ((8*((1) * (1UL << (13 + (3)))))/8)) { ((pq->block_size <= ((8*((1) * (1UL << (13 + (3)))))/8)) ? (void)0 : _mi_assert_fail("pq->block_size <= MI_LARGE_MAX_OBJ_SIZE","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",762,__func__)); }
  return pq;
}







static inline mi_threadid_t mi_page_xthread_id(const mi_page_t* page) {
  return atomic_load_explicit(&((mi_page_t*)page)->xthread_id,memory_order_relaxed);
}


static inline mi_threadid_t mi_page_thread_id(const mi_page_t* page) {
  return (mi_page_xthread_id(page) & ~0x03UL);
}

static inline mi_page_flags_t mi_page_flags(const mi_page_t* page) {
  return (mi_page_xthread_id(page) & 0x03UL);
}

static inline void mi_page_flags_set(mi_page_t* page, bool set, mi_page_flags_t newflag) {
  if (set) { atomic_fetch_or_explicit(&page->xthread_id,newflag,memory_order_relaxed); }
      else { atomic_fetch_and_explicit(&page->xthread_id,~newflag,memory_order_relaxed); }
}

static inline bool mi_page_is_in_full(const mi_page_t* page) {
  return ((mi_page_flags(page) & 0x01UL) != 0);
}

static inline void mi_page_set_in_full(mi_page_t* page, bool in_full) {
  mi_page_flags_set(page, in_full, 0x01UL);
}

static inline bool mi_page_has_interior_pointers(const mi_page_t* page) {
  return ((mi_page_flags(page) & 0x02UL) != 0);
}

static inline void mi_page_set_has_interior_pointers(mi_page_t* page, bool has_aligned) {
  mi_page_flags_set(page, has_aligned, 0x02UL);
}

static inline void mi_page_set_heap(mi_page_t* page, mi_heap_t* heap) {

  if (heap != 0) {
    page->heap = heap;
    page->heap_tag = heap->tag;
  }
  else {
    page->heap = 0;
  }
  const mi_threadid_t tid = (heap == 0 ? 0UL : heap->tld->thread_id);
  (((tid & 0x03UL) == 0) ? (void)0 : _mi_assert_fail("(tid & MI_PAGE_FLAG_MASK) == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",816,__func__));


  mi_threadid_t xtid_old = mi_page_xthread_id(page);
  mi_threadid_t xtid;
  do {
    xtid = tid | (xtid_old & 0x03UL);
  } while (!atomic_compare_exchange_weak_explicit(&page->xthread_id,&xtid_old,xtid,memory_order_release,memory_order_relaxed));
}

static inline bool mi_page_is_abandoned(const mi_page_t* page) {

  return (mi_page_thread_id(page) <= (0x03UL + 1));
}

static inline bool mi_page_is_abandoned_mapped(const mi_page_t* page) {
  return (mi_page_thread_id(page) == (0x03UL + 1));
}

static inline void mi_page_set_abandoned_mapped(mi_page_t* page) {
  ((mi_page_is_abandoned(page)) ? (void)0 : _mi_assert_fail("mi_page_is_abandoned(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",836,__func__));
  atomic_fetch_or_explicit(&page->xthread_id,(0x03UL + 1),memory_order_relaxed);
}

static inline void mi_page_clear_abandoned_mapped(mi_page_t* page) {
  ((mi_page_is_abandoned_mapped(page)) ? (void)0 : _mi_assert_fail("mi_page_is_abandoned_mapped(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",841,__func__));
  atomic_fetch_and_explicit(&page->xthread_id,0x03UL,memory_order_relaxed);
}






static inline mi_block_t* mi_tf_block(mi_thread_free_t tf) {
  return (mi_block_t*)(tf & ~1);
}
static inline bool mi_tf_is_owned(mi_thread_free_t tf) {
  return ((tf & 1) == 1);
}
static inline mi_thread_free_t mi_tf_create(mi_block_t* block, bool owned) {
  return (mi_thread_free_t)((uintptr_t)block | (owned ? 1 : 0));
}


static inline mi_block_t* mi_page_thread_free(const mi_page_t* page) {
  return mi_tf_block(atomic_load_explicit(&((mi_page_t*)page)->xthread_free,memory_order_relaxed));
}


static inline bool mi_page_has_any_available(const mi_page_t* page) {
  ((page != 0 && page->reserved > 0) ? (void)0 : _mi_assert_fail("page != NULL && page->reserved > 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",867,__func__));
  return (page->used < page->reserved || (mi_page_thread_free(page) != 0));
}



static inline bool mi_page_is_owned(const mi_page_t* page) {
  return mi_tf_is_owned(atomic_load_explicit(&((mi_page_t*)page)->xthread_free,memory_order_relaxed));
}


static inline void _mi_page_unown_unconditional(mi_page_t* page) {
  ((mi_page_is_owned(page)) ? (void)0 : _mi_assert_fail("mi_page_is_owned(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",879,__func__));
  ((mi_page_thread_id(page)==0) ? (void)0 : _mi_assert_fail("mi_page_thread_id(page)==0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",880,__func__));
  const uintptr_t old = atomic_fetch_and_explicit(&page->xthread_free,~((uintptr_t)1),memory_order_acq_rel);
  (((old&1)==1) ? (void)0 : _mi_assert_fail("(old&1)==1","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",882,__func__)); (void)(old);
}


static inline bool mi_page_try_claim_ownership(mi_page_t* page) {
  const uintptr_t old = atomic_fetch_or_explicit(&page->xthread_free,1,memory_order_acq_rel);
  return ((old&1)==0);
}



static inline bool _mi_page_unown(mi_page_t* page) {
  ((mi_page_is_owned(page)) ? (void)0 : _mi_assert_fail("mi_page_is_owned(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",894,__func__));
  ((mi_page_is_abandoned(page)) ? (void)0 : _mi_assert_fail("mi_page_is_abandoned(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",895,__func__));
  mi_thread_free_t tf_new;
  mi_thread_free_t tf_old = atomic_load_explicit(&page->xthread_free,memory_order_relaxed);
  do {
    ((mi_tf_is_owned(tf_old)) ? (void)0 : _mi_assert_fail("mi_tf_is_owned(tf_old)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",899,__func__));
    while (__builtin_expect(!!(mi_tf_block(tf_old) != 0),0)) {
      _mi_page_free_collect(page, 0);
      if (mi_page_all_free(page)) {
        _mi_arenas_page_unabandon(page);
        _mi_arenas_page_free(page,0);
        return 1;
      }
      tf_old = atomic_load_explicit(&page->xthread_free,memory_order_relaxed);
    }
    ((mi_tf_block(tf_old)==0) ? (void)0 : _mi_assert_fail("mi_tf_block(tf_old)==NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",909,__func__));
    tf_new = mi_tf_create(0, 0);
  } while (!atomic_compare_exchange_weak_explicit(&page->xthread_free,&tf_old,tf_new,memory_order_acq_rel,memory_order_acquire));
  return 0;
}
# 981 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
static inline bool mi_is_in_same_page(const void* p, const void* q) {
  mi_page_t* page = _mi_ptr_page(p);
  return mi_page_contains_address(page,q);

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






static inline size_t mi_slice_count_of_size(size_t size) {
  return _mi_divide_up(size, (1UL << (13 + (3))));
}


static inline size_t mi_size_of_slices(size_t bcount) {
  return (bcount * (1UL << (13 + (3))));
}






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

static inline mi_memid_t _mi_memid_create_meta(void* mpage, size_t block_idx, size_t block_count) {
  mi_memid_t memid = _mi_memid_create(MI_MEM_META);
  memid.mem.meta.meta_page = mpage;
  memid.mem.meta.block_index = (uint32_t)block_idx;
  memid.mem.meta.block_count = (uint32_t)block_count;
  memid.initially_committed = 1;
  memid.initially_zero = 1;
  memid.is_pinned = 1;
  return memid;
}






static inline uintptr_t _mi_random_shuffle(uintptr_t x) {
  if (x==0) { x = 17; }


  x ^= x >> 30;
  x *= 0xbf58476d1ce4e5b9UL;
  x ^= x >> 27;
  x *= 0x94d049bb133111ebUL;
  x ^= x >> 31;
# 1129 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
  return x;
}
# 1162 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
static inline void _mi_memcpy(void* dst, const void* src, size_t n) {
  memcpy(dst, src, n);
}
static inline void _mi_memset(void* dst, int val, size_t n) {
  memset(dst, val, n);
}
# 1177 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
static inline void _mi_memcpy_aligned(void* dst, const void* src, size_t n) {
  ((((uintptr_t)dst % (1<<(3)) == 0) && ((uintptr_t)src % (1<<(3)) == 0)) ? (void)0 : _mi_assert_fail("((uintptr_t)dst % MI_INTPTR_SIZE == 0) && ((uintptr_t)src % MI_INTPTR_SIZE == 0)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",1178,__func__));
  void* adst = __builtin_assume_aligned(dst, (1<<(3)));
  const void* asrc = __builtin_assume_aligned(src, (1<<(3)));
  _mi_memcpy(adst, asrc, n);
}

static inline void _mi_memset_aligned(void* dst, int val, size_t n) {
  (((uintptr_t)dst % (1<<(3)) == 0) ? (void)0 : _mi_assert_fail("(uintptr_t)dst % MI_INTPTR_SIZE == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h",1185,__func__));
  void* adst = __builtin_assume_aligned(dst, (1<<(3)));
  _mi_memset(adst, val, n);
}
# 1202 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/internal.h"
static inline void _mi_memzero(void* dst, size_t n) {
  _mi_memset(dst, 0, n);
}

static inline void _mi_memzero_aligned(void* dst, size_t n) {
  _mi_memset_aligned(dst, 0, n);
}
# 11 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c" 2
# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/prim.h" 1






       
# 24 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/prim.h"
typedef struct mi_os_mem_config_s {
  size_t page_size;
  size_t large_page_size;
  size_t alloc_granularity;
  size_t physical_memory_in_kib;
  size_t virtual_address_bits;
  bool has_overcommit;
  bool has_partial_free;
  bool has_virtual_reserve;
} mi_os_mem_config_t;


void _mi_prim_mem_init( mi_os_mem_config_t* config );


int _mi_prim_free(void* addr, size_t size );
# 49 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/prim.h"
int _mi_prim_alloc(void* hint_addr, size_t size, size_t try_alignment, bool commit, bool allow_large, bool* is_large, bool* is_zero, void** addr);




int _mi_prim_commit(void* addr, size_t size, bool* is_zero);





int _mi_prim_decommit(void* addr, size_t size, bool* needs_recommit);



int _mi_prim_reset(void* addr, size_t size);




int _mi_prim_reuse(void* addr, size_t size);


int _mi_prim_protect(void* addr, size_t size, bool protect);





int _mi_prim_alloc_huge_os_pages(void* hint_addr, size_t size, int numa_node, bool* is_zero, void** addr);


size_t _mi_prim_numa_node(void);


size_t _mi_prim_numa_node_count(void);


mi_msecs_t _mi_prim_clock_now(void);


typedef struct mi_process_info_s {
  mi_msecs_t elapsed;
  mi_msecs_t utime;
  mi_msecs_t stime;
  size_t current_rss;
  size_t peak_rss;
  size_t current_commit;
  size_t peak_commit;
  size_t page_faults;
} mi_process_info_t;

void _mi_prim_process_info(mi_process_info_t* pinfo);



void _mi_prim_out_stderr( const char* msg );



bool _mi_prim_getenv(const char* name, char* result, size_t result_size);




bool _mi_prim_random_buf(void* buf, size_t buf_len);


void _mi_prim_thread_init_auto_done(void);


void _mi_prim_thread_done_auto_done(void);


void _mi_prim_thread_associate_default_heap(mi_heap_t* heap);


bool _mi_prim_thread_is_in_threadpool(void);
# 277 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/prim.h"
extern mi_heap_t* _mi_heap_default;
extern bool _mi_process_is_initialized;

static inline mi_threadid_t __mi_prim_thread_id(void) ;

static inline mi_threadid_t _mi_prim_thread_id(void) {
  const mi_threadid_t tid = __mi_prim_thread_id();
  ((tid > 1) ? (void)0 : _mi_assert_fail("tid > 1","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/prim.h",284,__func__));
  (((tid & 0x03UL) == 0) ? (void)0 : _mi_assert_fail("(tid & MI_PAGE_FLAG_MASK) == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/prim.h",285,__func__));
  return tid;
}
# 305 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/prim.h"
static inline mi_threadid_t __mi_prim_thread_id(void) {

  return (uintptr_t)__builtin_thread_pointer();
}
# 354 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/prim.h"
static inline mi_heap_t* mi_prim_get_default_heap(void);
# 421 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc/prim.h"
static inline mi_heap_t* mi_prim_get_default_heap(void) {



  return _mi_heap_default;
}
# 12 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c" 2



static void mi_check_padding(const mi_page_t* page, const mi_block_t* block);
static bool mi_check_is_double_free(const mi_page_t* page, const mi_block_t* block);
static size_t mi_page_usable_size_of(const mi_page_t* page, const mi_block_t* block);
static void mi_stat_free(const mi_page_t* page, const mi_block_t* block);
# 27 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c"
static inline void mi_free_block_local(mi_page_t* page, mi_block_t* block, bool track_stats, bool check_full)
{

  if (__builtin_expect(!!(mi_check_is_double_free(page, block)),0)) return;
  mi_check_padding(page, block);
  if (track_stats) { mi_stat_free(page, block); }

  memset(block, (0xDF), mi_page_block_size(page));

  if (track_stats) { ; }


  mi_block_set_next(page, block, page->local_free);
  page->local_free = block;
  if (__builtin_expect(!!(--page->used == 0),0)) {
    _mi_page_retire(page);
  }
  else if (__builtin_expect(!!(check_full && mi_page_is_in_full(page)),0)) {
    _mi_page_unfull(page);
  }
}


static void mi_free_try_collect_mt(mi_page_t* page, mi_block_t* mt_free) ;


static inline void mi_free_block_mt(mi_page_t* page, mi_block_t* block)
{

  mi_stat_free(page, block);
  ;



  size_t dbgsize = mi_usable_size(block);
  if (dbgsize > ((1024UL)*(1024UL))) { dbgsize = ((1024UL)*(1024UL)); }
  _mi_memset_aligned(block, (0xDF), dbgsize);



  mi_thread_free_t tf_new;
  mi_thread_free_t tf_old = atomic_load_explicit(&page->xthread_free,memory_order_relaxed);
  do {
    mi_block_set_next(page, block, mi_tf_block(tf_old));
    tf_new = mi_tf_create(block, 1 );
  } while (!atomic_compare_exchange_weak_explicit(&page->xthread_free,&tf_old,tf_new,memory_order_acq_rel,memory_order_acquire));


  const bool is_owned_now = !mi_tf_is_owned(tf_old);
  if (is_owned_now) {
    ((mi_page_is_abandoned(page)) ? (void)0 : _mi_assert_fail("mi_page_is_abandoned(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",77,__func__));
    mi_free_try_collect_mt(page,block);
  }
}






mi_block_t* _mi_page_ptr_unalign(const mi_page_t* page, const void* p) {
  ((page!=0 && p!=0) ? (void)0 : _mi_assert_fail("page!=NULL && p!=NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",88,__func__));

  const size_t diff = (uint8_t*)p - mi_page_start(page);
  const size_t block_size = mi_page_block_size(page);
  const size_t adjust = (_mi_is_power_of_two(block_size) ? diff & (block_size - 1) : diff % block_size);
  return (mi_block_t*)((uintptr_t)p - adjust);
}
# 103 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c"
static inline void mi_block_check_unguard(mi_page_t* page, mi_block_t* block, void* p) {
  (void)(page); (void)(block); (void)(p);
}


static inline mi_block_t* mi_validate_block_from_ptr( const mi_page_t* page, void* p ) {
  ((_mi_page_ptr_unalign(page,p) == (mi_block_t*)p) ? (void)0 : _mi_assert_fail("_mi_page_ptr_unalign(page,p) == (mi_block_t*)p","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",109,__func__));




  (void)(page);
  return (mi_block_t*)p;

}



static void mi_free_generic_local(mi_page_t* page, void* p) {
  ((p!=0 && page != 0) ? (void)0 : _mi_assert_fail("p!=NULL && page != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",122,__func__));
  mi_block_t* const block = (mi_page_has_interior_pointers(page) ? _mi_page_ptr_unalign(page, p) : mi_validate_block_from_ptr(page,p));
  mi_block_check_unguard(page, block, p);
  mi_free_block_local(page, block, 1 , 1 );
}


static void mi_free_generic_mt(mi_page_t* page, void* p) {
  ((p!=0 && page != 0) ? (void)0 : _mi_assert_fail("p!=NULL && page != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",130,__func__));
  mi_block_t* const block = (mi_page_has_interior_pointers(page) ? _mi_page_ptr_unalign(page, p) : mi_validate_block_from_ptr(page,p));
  mi_block_check_unguard(page, block, p);
  mi_free_block_mt(page, block);
}


void _mi_free_generic(mi_page_t* page, bool is_local, void* p) {
  if (is_local) mi_free_generic_local(page,p);
           else mi_free_generic_mt(page,p);
}




static inline mi_page_t* mi_validate_ptr_page(const void* p, const char* msg)
{
  ;

  if (__builtin_expect(!!(((uintptr_t)p & ((1<<(3)) - 1)) != 0 && !mi_option_is_enabled(mi_option_guarded_precise)),0)) {
    _mi_error_message((22), "%s: invalid (unaligned) pointer: %p\n", msg, p);
    return 0;
  }
  mi_page_t* page = _mi_safe_ptr_page(p);
  if (p != 0 && page == 0) {
    _mi_error_message((22), "%s: invalid pointer: %p\n", msg, p);
  }
  return page;



}



void mi_free(void* p)
{
  mi_page_t* const page = mi_validate_ptr_page(p,"mi_free");
  if (__builtin_expect(!!(page==0),0)) return;
  ((p!=0 && page!=0) ? (void)0 : _mi_assert_fail("p!=NULL && page!=NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",169,__func__));

  const mi_threadid_t xtid = (_mi_prim_thread_id() ^ mi_page_xthread_id(page));
  if (__builtin_expect(!!(xtid == 0),1)) {

    mi_block_t* const block = mi_validate_block_from_ptr(page,p);
    mi_free_block_local(page, block, 1 , 0 );
  }
  else if (xtid <= 0x03UL) {

    mi_free_generic_local(page, p);
  }

  else if ((xtid & 0x03UL) == 0) {

    mi_block_t* const block = mi_validate_block_from_ptr(page,p);
    mi_free_block_mt(page,block);
  }
  else {

    mi_free_generic_mt(page, p);
  }
}





static bool mi_page_unown_from_free(mi_page_t* page, mi_block_t* mt_free);

static inline bool mi_page_queue_len_is_atmost( mi_heap_t* heap, size_t block_size, long atmost) {
  mi_page_queue_t* const pq = mi_page_queue(heap,block_size);
  ((pq!=0) ? (void)0 : _mi_assert_fail("pq!=NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",201,__func__));
  return (pq->count <= (size_t)atmost);
}

static void mi_free_try_collect_mt(mi_page_t* page, mi_block_t* mt_free) {
  ((mi_page_is_owned(page)) ? (void)0 : _mi_assert_fail("mi_page_is_owned(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",206,__func__));
  ((mi_page_is_abandoned(page)) ? (void)0 : _mi_assert_fail("mi_page_is_abandoned(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",207,__func__));




  _mi_page_free_collect_partly(page, mt_free);


  if (mi_page_is_singleton(page)) { ((mi_page_all_free(page)) ? (void)0 : _mi_assert_fail("mi_page_all_free(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",215,__func__)); }



  if (mi_page_all_free(page))
  {

    _mi_arenas_page_unabandon(page);

    _mi_arenas_page_free(page,0);
    return;
  }
# 235 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c"
  if (page->block_size <= ((((1) * (1UL << (13 + (3))))-(((3)+2)*32))/8))
  {
    const long reclaim_on_free = _mi_option_get_fast(mi_option_page_reclaim_on_free);
    if (reclaim_on_free >= 0) {



      mi_heap_t* heap = mi_prim_get_default_heap();
      if (heap != page->heap) {
        if (mi_heap_is_initialized(heap)) {
          heap = _mi_heap_by_tag(heap, page->heap_tag);
        }
      }

      if (heap != 0 && heap->allow_page_reclaim)
      {
        long max_reclaim = 0;
        if (__builtin_expect(!!(heap == page->heap),1)) {

          max_reclaim = _mi_option_get_fast(heap->tld->is_in_threadpool ? mi_option_page_cross_thread_max_reclaim : mi_option_page_max_reclaim);
        }
        else if (reclaim_on_free == 1 &&
                 !heap->tld->is_in_threadpool &&
                 !mi_page_is_used_at_frac(page,8) &&
                 _mi_arena_memid_is_suitable(page->memid, heap->exclusive_arena)) {

          max_reclaim = _mi_option_get_fast(mi_option_page_cross_thread_max_reclaim);
        }

        if (max_reclaim < 0 || mi_page_queue_len_is_atmost(heap, page->block_size, max_reclaim)) {


          _mi_arenas_page_unabandon(page);
          _mi_heap_page_reclaim(heap, page);
          __mi_stat_counter_increase( &(heap->tld)->stats.pages_reclaim_on_free, 1);
          return;
        }
      }
    }
  }


  if (!mi_page_is_used_at_frac(page, 8) &&
      !mi_page_is_abandoned_mapped(page) && page->memid.memkind == MI_MEM_ARENA &&
      _mi_arenas_page_try_reabandon_to_mapped(page))
  {
    return;
  }




  mi_page_unown_from_free(page, mt_free);
}





static bool mi_page_unown_from_free(mi_page_t* page, mi_block_t* mt_free) {
  ((mi_page_is_owned(page)) ? (void)0 : _mi_assert_fail("mi_page_is_owned(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",295,__func__));
  ((mi_page_is_abandoned(page)) ? (void)0 : _mi_assert_fail("mi_page_is_abandoned(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",296,__func__));
  ((mt_free != 0) ? (void)0 : _mi_assert_fail("mt_free != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",297,__func__));
  ((page->used > 1) ? (void)0 : _mi_assert_fail("page->used > 1","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",298,__func__));
  mi_thread_free_t tf_expect = mi_tf_create(mt_free, 1);
  mi_thread_free_t tf_new = mi_tf_create(mt_free, 0);
  while (__builtin_expect(!!(!atomic_compare_exchange_weak_explicit(&page->xthread_free,&tf_expect,tf_new,memory_order_acq_rel,memory_order_acquire)),0)) {
    ((mi_tf_is_owned(tf_expect)) ? (void)0 : _mi_assert_fail("mi_tf_is_owned(tf_expect)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",302,__func__));
    while (mi_tf_block(tf_expect) != 0) {
      _mi_page_free_collect(page,0);
      if (mi_page_all_free(page)) {
        _mi_arenas_page_unabandon(page);
        _mi_arenas_page_free(page,0);
        return 1;
      }
      tf_expect = atomic_load_explicit(&page->xthread_free,memory_order_relaxed);
    }
    ((mi_tf_block(tf_expect)==0) ? (void)0 : _mi_assert_fail("mi_tf_block(tf_expect)==NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",312,__func__));
    tf_new = mi_tf_create(0, 0);
  }
  return 0;
}







static size_t mi_page_usable_aligned_size_of(const mi_page_t* page, const void* p) {
  const mi_block_t* block = _mi_page_ptr_unalign(page, p);
  const size_t size = mi_page_usable_size_of(page, block);
  const ptrdiff_t adjust = (uint8_t*)p - (uint8_t*)block;
  ((adjust >= 0 && (size_t)adjust <= size) ? (void)0 : _mi_assert_fail("adjust >= 0 && (size_t)adjust <= size","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",328,__func__));
  const size_t aligned_size = (size - adjust);





  return aligned_size;
}

static inline size_t _mi_usable_size(const void* p, const char* msg) {
  const mi_page_t* const page = mi_validate_ptr_page(p,msg);
  if (__builtin_expect(!!(page==0),0)) return 0;
  if (__builtin_expect(!!(!mi_page_has_interior_pointers(page)),1)) {
    const mi_block_t* block = (const mi_block_t*)p;
    return mi_page_usable_size_of(page, block);
  }
  else {

    return mi_page_usable_aligned_size_of(page, p);
  }
}

 size_t mi_usable_size(const void* p) {
  return _mi_usable_size(p, "mi_usable_size");
}






void mi_free_size(void* p, size_t size) {
  ;

  const size_t available = _mi_usable_size(p,"mi_free_size");
  ((p == 0 || size <= available || available == 0) ? (void)0 : _mi_assert_fail("p == NULL || size <= available || available == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",364,__func__));

  mi_free(p);
}

void mi_free_size_aligned(void* p, size_t size, size_t alignment) {
  ;
  ((((uintptr_t)p % alignment) == 0) ? (void)0 : _mi_assert_fail("((uintptr_t)p % alignment) == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",371,__func__));
  mi_free_size(p,size);
}

void mi_free_aligned(void* p, size_t alignment) {
  ;
  ((((uintptr_t)p % alignment) == 0) ? (void)0 : _mi_assert_fail("((uintptr_t)p % alignment) == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",377,__func__));
  mi_free(p);
}
# 389 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c"
static bool mi_list_contains(const mi_page_t* page, const mi_block_t* list, const mi_block_t* elem) {
  while (list != 0) {
    if (elem==list) return 1;
    list = mi_block_next(page, list);
  }
  return 0;
}

static bool mi_check_is_double_freex(const mi_page_t* page, const mi_block_t* block) {


  if (mi_list_contains(page, page->free, block) ||
      mi_list_contains(page, page->local_free, block) ||
      mi_list_contains(page, mi_page_thread_free(page), block))
  {
    _mi_error_message((11), "double free detected of block %p with size %zu\n", block, mi_page_block_size(page));
    return 1;
  }
  return 0;
}



static inline bool mi_check_is_double_free(const mi_page_t* page, const mi_block_t* block) {
  bool is_double_free = 0;
  mi_block_t* n = mi_block_nextx(page, block, page->keys);
  if (((uintptr_t)n & ((1<<(3))-1))==0 &&
      (n==0 || mi_is_in_same_page(block, n)))
  {


    is_double_free = mi_check_is_double_freex(page, block);
  }
  return is_double_free;
}
# 438 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c"
static bool mi_page_decode_padding(const mi_page_t* page, const mi_block_t* block, size_t* delta, size_t* bsize) {
  *bsize = mi_page_usable_block_size(page);
  const mi_padding_t* const padding = (mi_padding_t*)((uint8_t*)block + *bsize);
  ;
  *delta = padding->delta;
  uint32_t canary = padding->canary;
  uintptr_t keys[2];
  keys[0] = page->keys[0];
  keys[1] = page->keys[1];
  bool ok = (mi_ptr_encode_canary(page,block,keys) == canary && *delta <= *bsize);
  ;
  return ok;
}


static size_t mi_page_usable_size_of(const mi_page_t* page, const mi_block_t* block) {
  size_t bsize;
  size_t delta;
  bool ok = mi_page_decode_padding(page, block, &delta, &bsize);
  ((ok) ? (void)0 : _mi_assert_fail("ok","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",457,__func__)); ((delta <= bsize) ? (void)0 : _mi_assert_fail("delta <= bsize","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",457,__func__));
  return (ok ? bsize - delta : 0);
}





void _mi_padding_shrink(const mi_page_t* page, const mi_block_t* block, const size_t min_size) {
  size_t bsize;
  size_t delta;
  bool ok = mi_page_decode_padding(page, block, &delta, &bsize);
  ((ok) ? (void)0 : _mi_assert_fail("ok","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",469,__func__));
  if (!ok || (bsize - delta) >= min_size) return;
  ((bsize >= min_size) ? (void)0 : _mi_assert_fail("bsize >= min_size","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",471,__func__));
  if (bsize < min_size) return;
  size_t new_delta = (bsize - min_size);
  ((new_delta < bsize) ? (void)0 : _mi_assert_fail("new_delta < bsize","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",474,__func__));
  mi_padding_t* padding = (mi_padding_t*)((uint8_t*)block + bsize);
  ;
  padding->delta = (uint32_t)new_delta;
  ;
}
# 495 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c"
static bool mi_verify_padding(const mi_page_t* page, const mi_block_t* block, size_t* size, size_t* wrong) {
  size_t bsize;
  size_t delta;
  bool ok = mi_page_decode_padding(page, block, &delta, &bsize);
  *size = *wrong = bsize;
  if (!ok) return 0;
  ((bsize >= delta) ? (void)0 : _mi_assert_fail("bsize >= delta","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c",501,__func__));
  *size = bsize - delta;
  if (!mi_page_is_huge(page)) {
    uint8_t* fill = (uint8_t*)block + bsize - delta;
    const size_t maxpad = (delta > 16 ? 16 : delta);
    ;
    for (size_t i = 0; i < maxpad; i++) {
      if (fill[i] != (0xDE)) {
        *wrong = bsize - delta + i;
        ok = 0;
        break;
      }
    }
    ;
  }
  return ok;
}

static void mi_check_padding(const mi_page_t* page, const mi_block_t* block) {
  size_t size;
  size_t wrong;
  if (!mi_verify_padding(page,block,&size,&wrong)) {
    _mi_error_message((14), "buffer overflow in heap block %p of size %zu: write after %zu bytes\n", block, size, wrong );
  }
}
# 538 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/free.c"
static void mi_stat_free(const mi_page_t* page, const mi_block_t* block) {
  (void)(block);
  mi_heap_t* const heap = mi_heap_get_default();
  const size_t bsize = mi_page_usable_block_size(page);




  if (bsize <= ((8*((1) * (1UL << (13 + (3)))))/8)) {
    __mi_stat_decrease( &(heap->tld)->stats.malloc_normal, bsize);

    __mi_stat_decrease( &(heap->tld)->stats.malloc_bins[_mi_bin(bsize)], 1);

  }
  else {
    const size_t bpsize = mi_page_block_size(page);
    __mi_stat_decrease( &(heap->tld)->stats.malloc_huge, bpsize);
  }
}
