# 0 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c"
# 14 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c"
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
# 15 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c" 2
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
# 16 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c" 2







# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c" 1
# 39 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c"
static inline bool mi_page_queue_is_huge(const mi_page_queue_t* pq) {
  return (pq->block_size == (((8*((1) * (1UL << (13 + (3)))))/8)+sizeof(uintptr_t)));
}

static inline bool mi_page_queue_is_full(const mi_page_queue_t* pq) {
  return (pq->block_size == (((8*((1) * (1UL << (13 + (3)))))/8)+(2*sizeof(uintptr_t))));
}

static inline bool mi_page_queue_is_special(const mi_page_queue_t* pq) {
  return (pq->block_size > ((8*((1) * (1UL << (13 + (3)))))/8));
}

static inline size_t mi_page_queue_count(const mi_page_queue_t* pq) {
  return pq->count;
}
# 63 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c"
static size_t mi_bin(size_t size) {
  size_t wsize = _mi_wsize_from_size(size);





  if (__builtin_expect(!!(wsize <= 8),1)) {
    return (wsize <= 1 ? 1 : (wsize+1)&~1);
  }





  else if (__builtin_expect(!!(wsize > (((8*((1) * (1UL << (13 + (3)))))/8)/(1<<(3)))),0)) {
    return (73U);
  }
  else {



    wsize--;

    const size_t b = (((1<<(3))*8) - 1 - mi_clz(wsize));



    const size_t bin = ((b << 2) + ((wsize >> (b - 2)) & 0x03)) - 3;
    ((bin > 0 && bin < (73U)) ? (void)0 : _mi_assert_fail("bin > 0 && bin < MI_BIN_HUGE","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",92,__func__));
    return bin;
  }
}







size_t _mi_bin(size_t size) {
  return mi_bin(size);
}

size_t _mi_bin_size(size_t bin) {
  ((bin <= (73U)) ? (void)0 : _mi_assert_fail("bin <= MI_BIN_HUGE","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",108,__func__));
  return _mi_heap_empty.pages[bin].block_size;
}


 size_t mi_good_size(size_t size) {
  if (size <= ((8*((1) * (1UL << (13 + (3)))))/8)) {
    return _mi_bin_size(mi_bin(size + (sizeof(mi_padding_t))));
  }
  else {
    return _mi_align_up(size + (sizeof(mi_padding_t)),_mi_os_page_size());
  }
}


static bool mi_page_queue_contains(mi_page_queue_t* queue, const mi_page_t* page) {
  ((page != 0) ? (void)0 : _mi_assert_fail("page != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",124,__func__));
  mi_page_t* list = queue->first;
  while (list != 0) {
    ((list->next == 0 || list->next->prev == list) ? (void)0 : _mi_assert_fail("list->next == NULL || list->next->prev == list","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",127,__func__));
    ((list->prev == 0 || list->prev->next == list) ? (void)0 : _mi_assert_fail("list->prev == NULL || list->prev->next == list","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",128,__func__));
    if (list == page) break;
    list = list->next;
  }
  return (list == page);
}




static bool mi_heap_contains_queue(const mi_heap_t* heap, const mi_page_queue_t* pq) {
  return (pq >= &heap->pages[0] && pq <= &heap->pages[((73U)+1)]);
}


bool _mi_page_queue_is_valid(mi_heap_t* heap, const mi_page_queue_t* pq) {
  ;
  if (pq==0) return 0;
  size_t count = 0; ;
  mi_page_t* prev = 0; ;
  for (mi_page_t* page = pq->first; page != 0; page = page->next) {
    ((page->prev == prev) ? (void)0 : _mi_assert_fail("page->prev == prev","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",149,__func__));
    if (mi_page_is_in_full(page)) {
      ((_mi_wsize_from_size(pq->block_size) == (((8*((1) * (1UL << (13 + (3)))))/8)/(1<<(3))) + 2) ? (void)0 : _mi_assert_fail("_mi_wsize_from_size(pq->block_size) == MI_LARGE_MAX_OBJ_WSIZE + 2","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",151,__func__));
    }
    else if (mi_page_is_huge(page)) {
      ((_mi_wsize_from_size(pq->block_size) == (((8*((1) * (1UL << (13 + (3)))))/8)/(1<<(3))) + 1) ? (void)0 : _mi_assert_fail("_mi_wsize_from_size(pq->block_size) == MI_LARGE_MAX_OBJ_WSIZE + 1","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",154,__func__));
    }
    else {
      ((mi_page_block_size(page) == pq->block_size) ? (void)0 : _mi_assert_fail("mi_page_block_size(page) == pq->block_size","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",157,__func__));
    }
    ((page->heap == heap) ? (void)0 : _mi_assert_fail("page->heap == heap","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",159,__func__));
    if (page->next == 0) {
      ((pq->last == page) ? (void)0 : _mi_assert_fail("pq->last == page","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",161,__func__));
    }
    count++;
    prev = page;
  }
  ((pq->count == count) ? (void)0 : _mi_assert_fail("pq->count == count","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",166,__func__));
  return 1;
}

size_t _mi_page_bin(const mi_page_t* page) {
  const size_t bin = (mi_page_is_in_full(page) ? ((73U)+1) : (mi_page_is_huge(page) ? (73U) : mi_bin(mi_page_block_size(page))));
  ((bin <= ((73U)+1)) ? (void)0 : _mi_assert_fail("bin <= MI_BIN_FULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",172,__func__));
  return bin;
}

static mi_page_queue_t* mi_heap_page_queue_of(mi_heap_t* heap, const mi_page_t* page) {
  ((heap!=0) ? (void)0 : _mi_assert_fail("heap!=NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",177,__func__));
  const size_t bin = _mi_page_bin(page);
  mi_page_queue_t* pq = &heap->pages[bin];
  (((mi_page_block_size(page) == pq->block_size) || (mi_page_is_huge(page) && mi_page_queue_is_huge(pq)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(pq))) ? (void)0 : _mi_assert_fail("(mi_page_block_size(page) == pq->block_size) || (mi_page_is_huge(page) && mi_page_queue_is_huge(pq)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(pq))","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",180,__func__))

                                                                                 ;
  return pq;
}

static mi_page_queue_t* mi_page_queue_of(const mi_page_t* page) {
  mi_heap_t* heap = mi_page_heap(page);
  mi_page_queue_t* pq = mi_heap_page_queue_of(heap, page);
  ;
  return pq;
}






static inline void mi_heap_queue_first_update(mi_heap_t* heap, const mi_page_queue_t* pq) {
  ((mi_heap_contains_queue(heap,pq)) ? (void)0 : _mi_assert_fail("mi_heap_contains_queue(heap,pq)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",199,__func__));
  size_t size = pq->block_size;
  if (size > ((128)*sizeof(void*))) return;

  mi_page_t* page = pq->first;
  if (pq->first == 0) page = (mi_page_t*)&_mi_page_empty;


  size_t start;
  size_t idx = _mi_wsize_from_size(size);
  mi_page_t** pages_free = heap->pages_free_direct;

  if (pages_free[idx] == page) return;


  if (idx<=1) {
    start = 0;
  }
  else {

    size_t bin = mi_bin(size);
    const mi_page_queue_t* prev = pq - 1;
    while( bin == mi_bin(prev->block_size) && prev > &heap->pages[0]) {
      prev--;
    }
    start = 1 + _mi_wsize_from_size(prev->block_size);
    if (start > idx) start = idx;
  }


  ((start <= idx) ? (void)0 : _mi_assert_fail("start <= idx","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",229,__func__));
  for (size_t sz = start; sz <= idx; sz++) {
    pages_free[sz] = page;
  }
}







static void mi_page_queue_remove(mi_page_queue_t* queue, mi_page_t* page) {
  ((page != 0) ? (void)0 : _mi_assert_fail("page != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",242,__func__));
  ;
  ((queue->count >= 1) ? (void)0 : _mi_assert_fail("queue->count >= 1","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",244,__func__));
  ((mi_page_block_size(page) == queue->block_size || (mi_page_is_huge(page) && mi_page_queue_is_huge(queue)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))) ? (void)0 : _mi_assert_fail("mi_page_block_size(page) == queue->block_size || (mi_page_is_huge(page) && mi_page_queue_is_huge(queue)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",245,__func__))

                                                                                   ;
  mi_heap_t* heap = mi_page_heap(page);
  if (page->prev != 0) page->prev->next = page->next;
  if (page->next != 0) page->next->prev = page->prev;
  if (page == queue->last) queue->last = page->prev;
  if (page == queue->first) {
    queue->first = page->next;

    ((mi_heap_contains_queue(heap, queue)) ? (void)0 : _mi_assert_fail("mi_heap_contains_queue(heap, queue)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",255,__func__));
    mi_heap_queue_first_update(heap,queue);
  }
  heap->page_count--;
  queue->count--;
  page->next = 0;
  page->prev = 0;
  mi_page_set_in_full(page,0);
}


static void mi_page_queue_push(mi_heap_t* heap, mi_page_queue_t* queue, mi_page_t* page) {
  ((mi_page_heap(page) == heap) ? (void)0 : _mi_assert_fail("mi_page_heap(page) == heap","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",267,__func__));
  ((!mi_page_queue_contains(queue, page)) ? (void)0 : _mi_assert_fail("!mi_page_queue_contains(queue, page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",268,__func__));



  ((mi_page_block_size(page) == queue->block_size || (mi_page_is_huge(page) && mi_page_queue_is_huge(queue)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))) ? (void)0 : _mi_assert_fail("mi_page_block_size(page) == queue->block_size || (mi_page_is_huge(page) && mi_page_queue_is_huge(queue)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",272,__func__))

                                                                                   ;

  mi_page_set_in_full(page, mi_page_queue_is_full(queue));

  page->next = queue->first;
  page->prev = 0;
  if (queue->first != 0) {
    ((queue->first->prev == 0) ? (void)0 : _mi_assert_fail("queue->first->prev == NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",281,__func__));
    queue->first->prev = page;
    queue->first = page;
  }
  else {
    queue->first = queue->last = page;
  }
  queue->count++;


  mi_heap_queue_first_update(heap, queue);
  heap->page_count++;
}

static void mi_page_queue_push_at_end(mi_heap_t* heap, mi_page_queue_t* queue, mi_page_t* page) {
  ((mi_page_heap(page) == heap) ? (void)0 : _mi_assert_fail("mi_page_heap(page) == heap","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",296,__func__));
  ((!mi_page_queue_contains(queue, page)) ? (void)0 : _mi_assert_fail("!mi_page_queue_contains(queue, page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",297,__func__));

  ((mi_page_block_size(page) == queue->block_size || (mi_page_is_huge(page) && mi_page_queue_is_huge(queue)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))) ? (void)0 : _mi_assert_fail("mi_page_block_size(page) == queue->block_size || (mi_page_is_huge(page) && mi_page_queue_is_huge(queue)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",299,__func__))

                                                                                  ;

  mi_page_set_in_full(page, mi_page_queue_is_full(queue));

  page->prev = queue->last;
  page->next = 0;
  if (queue->last != 0) {
    ((queue->last->next == 0) ? (void)0 : _mi_assert_fail("queue->last->next == NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",308,__func__));
    queue->last->next = page;
    queue->last = page;
  }
  else {
    queue->first = queue->last = page;
  }
  queue->count++;


  if (queue->first == page) {
    mi_heap_queue_first_update(heap, queue);
  }
  heap->page_count++;
}

static void mi_page_queue_move_to_front(mi_heap_t* heap, mi_page_queue_t* queue, mi_page_t* page) {
  ((mi_page_heap(page) == heap) ? (void)0 : _mi_assert_fail("mi_page_heap(page) == heap","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",325,__func__));
  ((mi_page_queue_contains(queue, page)) ? (void)0 : _mi_assert_fail("mi_page_queue_contains(queue, page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",326,__func__));
  if (queue->first == page) return;
  mi_page_queue_remove(queue, page);
  mi_page_queue_push(heap, queue, page);
  ((queue->first == page) ? (void)0 : _mi_assert_fail("queue->first == page","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",330,__func__));
}

static void mi_page_queue_enqueue_from_ex(mi_page_queue_t* to, mi_page_queue_t* from, bool enqueue_at_end, mi_page_t* page) {
  ((page != 0) ? (void)0 : _mi_assert_fail("page != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",334,__func__));
  ((from->count >= 1) ? (void)0 : _mi_assert_fail("from->count >= 1","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",335,__func__));
  ;
  ;
  const size_t bsize = mi_page_block_size(page);
  (void)(bsize);
  (((bsize == to->block_size && bsize == from->block_size) || (bsize == to->block_size && mi_page_queue_is_full(from)) || (bsize == from->block_size && mi_page_queue_is_full(to)) || (mi_page_is_huge(page) && mi_page_queue_is_huge(to)) || (mi_page_is_huge(page) && mi_page_queue_is_full(to))) ? (void)0 : _mi_assert_fail("(bsize == to->block_size && bsize == from->block_size) || (bsize == to->block_size && mi_page_queue_is_full(from)) || (bsize == from->block_size && mi_page_queue_is_full(to)) || (mi_page_is_huge(page) && mi_page_queue_is_huge(to)) || (mi_page_is_huge(page) && mi_page_queue_is_full(to))","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",340,__func__))



                                                                          ;

  mi_heap_t* heap = mi_page_heap(page);


  if (page->prev != 0) page->prev->next = page->next;
  if (page->next != 0) page->next->prev = page->prev;
  if (page == from->last) from->last = page->prev;
  if (page == from->first) {
    from->first = page->next;

    ((mi_heap_contains_queue(heap, from)) ? (void)0 : _mi_assert_fail("mi_heap_contains_queue(heap, from)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",355,__func__));
    mi_heap_queue_first_update(heap, from);
  }
  from->count--;


  to->count++;
  if (enqueue_at_end) {

    page->prev = to->last;
    page->next = 0;
    if (to->last != 0) {
      ((heap == mi_page_heap(to->last)) ? (void)0 : _mi_assert_fail("heap == mi_page_heap(to->last)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",367,__func__));
      to->last->next = page;
      to->last = page;
    }
    else {
      to->first = page;
      to->last = page;
      mi_heap_queue_first_update(heap, to);
    }
  }
  else {
    if (to->first != 0) {

      ((heap == mi_page_heap(to->first)) ? (void)0 : _mi_assert_fail("heap == mi_page_heap(to->first)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",380,__func__));
      mi_page_t* next = to->first->next;
      page->prev = to->first;
      page->next = next;
      to->first->next = page;
      if (next != 0) {
        next->prev = page;
      }
      else {
        to->last = page;
      }
    }
    else {

      page->prev = 0;
      page->next = 0;
      to->first = page;
      to->last = page;
      mi_heap_queue_first_update(heap, to);
    }
  }

  mi_page_set_in_full(page, mi_page_queue_is_full(to));
}

static void mi_page_queue_enqueue_from(mi_page_queue_t* to, mi_page_queue_t* from, mi_page_t* page) {
  mi_page_queue_enqueue_from_ex(to, from, 1 , page);
}

static void mi_page_queue_enqueue_from_full(mi_page_queue_t* to, mi_page_queue_t* from, mi_page_t* page) {

  mi_page_queue_enqueue_from_ex(to, from, 1 , page);
}


size_t _mi_page_queue_append(mi_heap_t* heap, mi_page_queue_t* pq, mi_page_queue_t* append) {
  ((mi_heap_contains_queue(heap,pq)) ? (void)0 : _mi_assert_fail("mi_heap_contains_queue(heap,pq)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",416,__func__));
  ((pq->block_size == append->block_size) ? (void)0 : _mi_assert_fail("pq->block_size == append->block_size","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",417,__func__));

  if (append->first==0) return 0;


  size_t count = 0;
  for (mi_page_t* page = append->first; page != 0; page = page->next) {
    mi_page_set_heap(page, heap);
    count++;
  }
  ((count == append->count) ? (void)0 : _mi_assert_fail("count == append->count","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",427,__func__));

  if (pq->last==0) {

    ((pq->first==0) ? (void)0 : _mi_assert_fail("pq->first==NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",431,__func__));
    pq->first = append->first;
    pq->last = append->last;
    mi_heap_queue_first_update(heap, pq);
  }
  else {

    ((pq->last!=0) ? (void)0 : _mi_assert_fail("pq->last!=NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",438,__func__));
    ((append->first!=0) ? (void)0 : _mi_assert_fail("append->first!=NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",439,__func__));
    pq->last->next = append->first;
    append->first->prev = pq->last;
    pq->last = append->last;
  }
  pq->count += append->count;

  return count;
}
# 24 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c" 2
# 32 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c"
static inline mi_block_t* mi_page_block_at(const mi_page_t* page, void* page_start, size_t block_size, size_t i) {
  (void)(page);
  ((page != 0) ? (void)0 : _mi_assert_fail("page != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",34,__func__));
  ((i <= page->reserved) ? (void)0 : _mi_assert_fail("i <= page->reserved","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",35,__func__));
  return (mi_block_t*)((uint8_t*)page_start + (i * block_size));
}


static bool mi_page_extend_free(mi_heap_t* heap, mi_page_t* page);
# 140 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c"
static void mi_page_thread_collect_to_local(mi_page_t* page, mi_block_t* head)
{
  if (head == 0) return;


  size_t max_count = page->capacity;
  size_t count = 1;
  mi_block_t* last = head;
  mi_block_t* next;
  while ((next = mi_block_next(page, last)) != 0 && count <= max_count) {
    count++;
    last = next;
  }


  if (count > max_count) {
    _mi_error_message((14), "corrupted thread-free list\n");
    return;
  }


  mi_block_set_next(page, last, page->local_free);
  page->local_free = head;


  ((count <= UINT16_MAX) ? (void)0 : _mi_assert_fail("count <= UINT16_MAX","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",165,__func__));
  page->used = page->used - (uint16_t)count;
}


static void mi_page_thread_free_collect(mi_page_t* page)
{

  mi_block_t* head;
  mi_thread_free_t tfreex;
  mi_thread_free_t tfree = atomic_load_explicit(&page->xthread_free,memory_order_relaxed);
  do {
    head = mi_tf_block(tfree);
    if (__builtin_expect(!!(head == 0),1)) return;
    tfreex = mi_tf_create(0,mi_tf_is_owned(tfree));
  } while (!atomic_compare_exchange_weak_explicit(&page->xthread_free,&tfree,tfreex,memory_order_acq_rel,memory_order_acquire));
  ((head != 0) ? (void)0 : _mi_assert_fail("head != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",181,__func__));


  mi_page_thread_collect_to_local(page, head);
}

void _mi_page_free_collect(mi_page_t* page, bool force) {
  ((page!=0) ? (void)0 : _mi_assert_fail("page!=NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",188,__func__));


  mi_page_thread_free_collect(page);


  if (page->local_free != 0) {
    if (__builtin_expect(!!(page->free == 0),1)) {

      page->free = page->local_free;
      page->local_free = 0;
      page->free_is_zero = 0;
    }
    else if (force) {

      mi_block_t* tail = page->local_free;
      mi_block_t* next;
      while ((next = mi_block_next(page, tail)) != 0) {
        tail = next;
      }
      mi_block_set_next(page, tail, page->free);
      page->free = page->local_free;
      page->local_free = 0;
      page->free_is_zero = 0;
    }
  }

  ((!force || page->local_free == 0) ? (void)0 : _mi_assert_fail("!force || page->local_free == NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",215,__func__));
}







void _mi_page_free_collect_partly(mi_page_t* page, mi_block_t* head) {
  if (head == 0) return;
  mi_block_t* next = mi_block_next(page,head);
  if (next != 0) {
    mi_block_set_next(page, head, 0);
    mi_page_thread_collect_to_local(page, next);
    if (page->local_free != 0 && page->free == 0) {
      page->free = page->local_free;
      page->local_free = 0;
      page->free_is_zero = 0;
    }
  }
  if (page->used == 1) {

    ((mi_tf_block(atomic_load_explicit(&page->xthread_free,memory_order_relaxed)) == head) ? (void)0 : _mi_assert_fail("mi_tf_block(mi_atomic_load_relaxed(&page->xthread_free)) == head","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",238,__func__));
    ((mi_block_next(page,head) == 0) ? (void)0 : _mi_assert_fail("mi_block_next(page,head) == NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",239,__func__));
    _mi_page_free_collect(page, 0);
  }
}
# 268 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c"
void _mi_heap_page_reclaim(mi_heap_t* heap, mi_page_t* page)
{
  ((_mi_is_aligned(page, ((1UL << (13 + (3)))))) ? (void)0 : _mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",270,__func__));
  ((_mi_ptr_page(page)==page) ? (void)0 : _mi_assert_fail("_mi_ptr_page(page)==page","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",271,__func__));
  ((mi_page_is_owned(page)) ? (void)0 : _mi_assert_fail("mi_page_is_owned(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",272,__func__));
  ((mi_page_is_abandoned(page)) ? (void)0 : _mi_assert_fail("mi_page_is_abandoned(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",273,__func__));

  mi_page_set_heap(page,heap);
  _mi_page_free_collect(page, 0);
  mi_page_queue_t* pq = mi_heap_page_queue_of(heap, page);
  mi_page_queue_push_at_end(heap, pq, page);
  ;
}

void _mi_page_abandon(mi_page_t* page, mi_page_queue_t* pq) {
  _mi_page_free_collect(page, 0);
  if (mi_page_all_free(page)) {
    _mi_page_free(page, pq);
  }
  else {
    mi_page_queue_remove(pq, page);
    mi_heap_t* heap = page->heap;
    mi_page_set_heap(page, 0);
    page->heap = heap;
    _mi_arenas_page_abandon(page, heap->tld);
    _mi_arenas_collect(0, 0, heap->tld);
  }
}



static mi_page_t* mi_page_fresh_alloc(mi_heap_t* heap, mi_page_queue_t* pq, size_t block_size, size_t page_alignment) {

  ((pq != 0) ? (void)0 : _mi_assert_fail("pq != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",301,__func__));
  ((mi_heap_contains_queue(heap, pq)) ? (void)0 : _mi_assert_fail("mi_heap_contains_queue(heap, pq)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",302,__func__));
  ((page_alignment > 0 || block_size > ((8*((1) * (1UL << (13 + (3)))))/8) || block_size == pq->block_size) ? (void)0 : _mi_assert_fail("page_alignment > 0 || block_size > MI_LARGE_MAX_OBJ_SIZE || block_size == pq->block_size","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",303,__func__));

  mi_page_t* page = _mi_arenas_page_alloc(heap, block_size, page_alignment);
  if (page == 0) {

    return 0;
  }
  if (mi_page_is_abandoned(page)) {
    _mi_heap_page_reclaim(heap, page);
    if (!mi_page_immediate_available(page)) {
      if (mi_page_is_expandable(page)) {
        mi_page_extend_free(heap, page);
      }
      else {
        ((0) ? (void)0 : _mi_assert_fail("false","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",317,__func__));
        return 0;
      }
    }
  }
  else if (pq != 0) {
    mi_page_queue_push(heap, pq, page);
  }
  ((pq!=0 || mi_page_block_size(page) >= block_size) ? (void)0 : _mi_assert_fail("pq!=NULL || mi_page_block_size(page) >= block_size","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",325,__func__));
  ;
  return page;
}


static mi_page_t* mi_page_fresh(mi_heap_t* heap, mi_page_queue_t* pq) {
  ((mi_heap_contains_queue(heap, pq)) ? (void)0 : _mi_assert_fail("mi_heap_contains_queue(heap, pq)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",332,__func__));
  mi_page_t* page = mi_page_fresh_alloc(heap, pq, pq->block_size, 0);
  if (page==0) return 0;
  ((pq->block_size==mi_page_block_size(page)) ? (void)0 : _mi_assert_fail("pq->block_size==mi_page_block_size(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",335,__func__));
  ((pq==mi_heap_page_queue_of(heap, page)) ? (void)0 : _mi_assert_fail("pq==mi_heap_page_queue_of(heap, page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",336,__func__));
  return page;
}







void _mi_page_unfull(mi_page_t* page) {
  ((page != 0) ? (void)0 : _mi_assert_fail("page != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",347,__func__));
  ;
  ((mi_page_is_in_full(page)) ? (void)0 : _mi_assert_fail("mi_page_is_in_full(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",349,__func__));
  ((!mi_page_heap(page)->allow_page_abandon) ? (void)0 : _mi_assert_fail("!mi_page_heap(page)->allow_page_abandon","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",350,__func__));
  if (!mi_page_is_in_full(page)) return;

  mi_heap_t* heap = mi_page_heap(page);
  mi_page_queue_t* pqfull = &heap->pages[((73U)+1)];
  mi_page_set_in_full(page, 0);
  mi_page_queue_t* pq = mi_heap_page_queue_of(heap, page);
  mi_page_set_in_full(page, 1);
  mi_page_queue_enqueue_from_full(pq, pqfull, page);
}

static void mi_page_to_full(mi_page_t* page, mi_page_queue_t* pq) {
  ((pq == mi_page_queue_of(page)) ? (void)0 : _mi_assert_fail("pq == mi_page_queue_of(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",362,__func__));
  ((!mi_page_immediate_available(page)) ? (void)0 : _mi_assert_fail("!mi_page_immediate_available(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",363,__func__));
  ((!mi_page_is_in_full(page)) ? (void)0 : _mi_assert_fail("!mi_page_is_in_full(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",364,__func__));

  mi_heap_t* heap = mi_page_heap(page);
  if (heap->allow_page_abandon) {

    _mi_page_abandon(page, pq);
  }
  else if (!mi_page_is_in_full(page)) {

    mi_page_queue_enqueue_from(&mi_page_heap(page)->pages[((73U)+1)], pq, page);
    _mi_page_free_collect(page, 0);
  }
}



void _mi_page_free(mi_page_t* page, mi_page_queue_t* pq) {
  ((page != 0) ? (void)0 : _mi_assert_fail("page != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",381,__func__));
  ;
  ((pq == mi_page_queue_of(page)) ? (void)0 : _mi_assert_fail("pq == mi_page_queue_of(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",383,__func__));
  ((mi_page_all_free(page)) ? (void)0 : _mi_assert_fail("mi_page_all_free(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",384,__func__));



  mi_page_set_has_interior_pointers(page, 0);



  mi_page_queue_remove(pq, page);


  mi_tld_t* const tld = page->heap->tld;
  mi_page_set_heap(page,0);
  _mi_arenas_page_free(page,tld);
  _mi_arenas_collect(0, 0, tld);
}
# 410 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c"
void _mi_page_retire(mi_page_t* page) {
  ((page != 0) ? (void)0 : _mi_assert_fail("page != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",411,__func__));
  ;
  ((mi_page_all_free(page)) ? (void)0 : _mi_assert_fail("mi_page_all_free(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",413,__func__));

  mi_page_set_has_interior_pointers(page, 0);







  mi_page_queue_t* pq = mi_page_queue_of(page);

  const size_t bsize = mi_page_block_size(page);
  if (__builtin_expect(!!(!mi_page_queue_is_special(pq)),1)) {
    if (pq->last==page && pq->first==page) {
      mi_heap_t* heap = mi_page_heap(page);

      __mi_stat_counter_increase( &(heap->tld)->stats.pages_retire, 1);

      page->retire_expire = (bsize <= ((((1) * (1UL << (13 + (3))))-(((3)+2)*32))/8) ? (16) : (16)/4);
      ((pq >= heap->pages) ? (void)0 : _mi_assert_fail("pq >= heap->pages","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",433,__func__));
      const size_t index = pq - heap->pages;
      ((index < ((73U)+1) && index < (73U)) ? (void)0 : _mi_assert_fail("index < MI_BIN_FULL && index < MI_BIN_HUGE","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",435,__func__));
      if (index < heap->page_retired_min) heap->page_retired_min = index;
      if (index > heap->page_retired_max) heap->page_retired_max = index;
      ((mi_page_all_free(page)) ? (void)0 : _mi_assert_fail("mi_page_all_free(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",438,__func__));
      return;
    }
  }

  _mi_page_free(page, pq);
}



void _mi_heap_collect_retired(mi_heap_t* heap, bool force) {
  size_t min = ((73U)+1);
  size_t max = 0;
  for(size_t bin = heap->page_retired_min; bin <= heap->page_retired_max; bin++) {
    mi_page_queue_t* pq = &heap->pages[bin];
    mi_page_t* page = pq->first;
    if (page != 0 && page->retire_expire != 0) {
      if (mi_page_all_free(page)) {
        page->retire_expire--;
        if (force || page->retire_expire == 0) {
          _mi_page_free(pq->first, pq);
        }
        else {

          if (bin < min) min = bin;
          if (bin > max) max = bin;
        }
      }
      else {
        page->retire_expire = 0;
      }
    }
  }
  heap->page_retired_min = min;
  heap->page_retired_max = max;
}
# 509 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c"
static void mi_page_free_list_extend_secure(mi_heap_t* const heap, mi_page_t* const page, const size_t bsize, const size_t extend, mi_stats_t* const stats) {
  (void)(stats);

  ((page->free == 0) ? (void)0 : _mi_assert_fail("page->free == NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",512,__func__));
  ((page->local_free == 0) ? (void)0 : _mi_assert_fail("page->local_free == NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",513,__func__));

  ((page->capacity + extend <= page->reserved) ? (void)0 : _mi_assert_fail("page->capacity + extend <= page->reserved","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",515,__func__));
  ((bsize == mi_page_block_size(page)) ? (void)0 : _mi_assert_fail("bsize == mi_page_block_size(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",516,__func__));
  void* const page_area = mi_page_start(page);



  size_t shift = (6);
  while ((extend >> shift) == 0) {
    shift--;
  }
  const size_t slice_count = (size_t)1U << shift;
  const size_t slice_extend = extend / slice_count;
  ((slice_extend >= 1) ? (void)0 : _mi_assert_fail("slice_extend >= 1","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",527,__func__));
  mi_block_t* blocks[(1UL << (6))];
  size_t counts[(1UL << (6))];
  for (size_t i = 0; i < slice_count; i++) {
    blocks[i] = mi_page_block_at(page, page_area, bsize, page->capacity + i*slice_extend);
    counts[i] = slice_extend;
  }
  counts[slice_count-1] += (extend % slice_count);



  const uintptr_t r = _mi_heap_random_next(heap);
  size_t current = r % slice_count;
  counts[current]--;
  mi_block_t* const free_start = blocks[current];

  uintptr_t rnd = _mi_random_shuffle(r|1);
  for (size_t i = 1; i < extend; i++) {

    const size_t round = i%(1<<(3));
    if (round == 0) rnd = _mi_random_shuffle(rnd);

    size_t next = ((rnd >> 8*round) & (slice_count-1));
    while (counts[next]==0) {
      next++;
      if (next==slice_count) next = 0;
    }

    counts[next]--;
    mi_block_t* const block = blocks[current];
    blocks[current] = (mi_block_t*)((uint8_t*)block + bsize);
    mi_block_set_next(page, block, blocks[next]);
    current = next;
  }

  mi_block_set_next(page, blocks[current], page->free);
  page->free = free_start;
}

static void mi_page_free_list_extend( mi_page_t* const page, const size_t bsize, const size_t extend, mi_stats_t* const stats)
{
  (void)(stats);

  ((page->free == 0) ? (void)0 : _mi_assert_fail("page->free == NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",570,__func__));
  ((page->local_free == 0) ? (void)0 : _mi_assert_fail("page->local_free == NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",571,__func__));

  ((page->capacity + extend <= page->reserved) ? (void)0 : _mi_assert_fail("page->capacity + extend <= page->reserved","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",573,__func__));
  ((bsize == mi_page_block_size(page)) ? (void)0 : _mi_assert_fail("bsize == mi_page_block_size(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",574,__func__));
  void* const page_area = mi_page_start(page);

  mi_block_t* const start = mi_page_block_at(page, page_area, bsize, page->capacity);


  mi_block_t* const last = mi_page_block_at(page, page_area, bsize, page->capacity + extend - 1);
  mi_block_t* block = start;
  while(block <= last) {
    mi_block_t* next = (mi_block_t*)((uint8_t*)block + bsize);
    mi_block_set_next(page,block,next);
    block = next;
  }

  mi_block_set_next(page, last, page->free);
  page->free = start;
}
# 608 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c"
static bool mi_page_extend_free(mi_heap_t* heap, mi_page_t* page) {
  ;

  ((page->free == 0) ? (void)0 : _mi_assert_fail("page->free == NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",611,__func__));
  ((page->local_free == 0) ? (void)0 : _mi_assert_fail("page->local_free == NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",612,__func__));
  if (page->free != 0) return 1;

  if (page->capacity >= page->reserved) return 1;

  size_t page_size;

  mi_page_area(page, &page_size);

  __mi_stat_counter_increase( &(heap->tld)->stats.pages_extended, 1);



  const size_t bsize = mi_page_block_size(page);
  size_t extend = (size_t)page->reserved - page->capacity;
  ((extend > 0) ? (void)0 : _mi_assert_fail("extend > 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",627,__func__));

  size_t max_extend = (bsize >= (4*1024) ? (1) : (4*1024)/bsize);
  if (max_extend < (1)) { max_extend = (1); }
  ((max_extend > 0) ? (void)0 : _mi_assert_fail("max_extend > 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",631,__func__));

  if (extend > max_extend) {


    extend = max_extend;
  }

  ((extend > 0 && extend + page->capacity <= page->reserved) ? (void)0 : _mi_assert_fail("extend > 0 && extend + page->capacity <= page->reserved","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",639,__func__));
  ((extend < (1UL<<16)) ? (void)0 : _mi_assert_fail("extend < (1UL<<16)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",640,__func__));


  if (page->slice_committed > 0) {
    const size_t needed_size = (page->capacity + extend)*bsize;
    const size_t needed_commit = _mi_align_up( mi_page_slice_offset_of(page, needed_size), (1UL << (13 + (3))) );
    if (needed_commit > page->slice_committed) {
      ((((needed_commit - page->slice_committed) % _mi_os_page_size()) == 0) ? (void)0 : _mi_assert_fail("((needed_commit - page->slice_committed) % _mi_os_page_size()) == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",647,__func__));
      if (!_mi_os_commit(mi_page_slice_start(page) + page->slice_committed, needed_commit - page->slice_committed, 0)) {
        return 0;
      }
      page->slice_committed = needed_commit;
    }
  }


  if (extend < (2) || 0<3) {
    mi_page_free_list_extend(page, bsize, extend, &heap->tld->stats );
  }
  else {
    mi_page_free_list_extend_secure(heap, page, bsize, extend, &heap->tld->stats);
  }

  page->capacity += (uint16_t)extend;

  __mi_stat_increase( &(heap->tld)->stats.page_committed, extend * bsize);

  ;
  return 1;
}


 bool _mi_page_init(mi_heap_t* heap, mi_page_t* page) {
  ((page != 0) ? (void)0 : _mi_assert_fail("page != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",673,__func__));
  mi_page_set_heap(page, heap);

  size_t page_size;
  uint8_t* page_start = mi_page_area(page, &page_size); (void)(page_start);
  ;
  ((page_size / mi_page_block_size(page) < (1L<<16)) ? (void)0 : _mi_assert_fail("page_size / mi_page_block_size(page) < (1L<<16)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",679,__func__));
  ((page->reserved > 0) ? (void)0 : _mi_assert_fail("page->reserved > 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",680,__func__));

  page->keys[0] = _mi_heap_random_next(heap);
  page->keys[1] = _mi_heap_random_next(heap);
# 692 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c"
  ((page->capacity == 0) ? (void)0 : _mi_assert_fail("page->capacity == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",692,__func__));
  ((page->free == 0) ? (void)0 : _mi_assert_fail("page->free == NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",693,__func__));
  ((page->used == 0) ? (void)0 : _mi_assert_fail("page->used == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",694,__func__));
  ((mi_page_is_owned(page)) ? (void)0 : _mi_assert_fail("mi_page_is_owned(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",695,__func__));
  ((page->xthread_free == 1) ? (void)0 : _mi_assert_fail("page->xthread_free == 1","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",696,__func__));
  ((page->next == 0) ? (void)0 : _mi_assert_fail("page->next == NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",697,__func__));
  ((page->prev == 0) ? (void)0 : _mi_assert_fail("page->prev == NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",698,__func__));
  ((page->retire_expire == 0) ? (void)0 : _mi_assert_fail("page->retire_expire == 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",699,__func__));
  ((!mi_page_has_interior_pointers(page)) ? (void)0 : _mi_assert_fail("!mi_page_has_interior_pointers(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",700,__func__));

  ((page->keys[0] != 0) ? (void)0 : _mi_assert_fail("page->keys[0] != 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",702,__func__));
  ((page->keys[1] != 0) ? (void)0 : _mi_assert_fail("page->keys[1] != 0","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",703,__func__));

  ;


  if (!mi_page_extend_free(heap,page)) return 0;
  ((mi_page_immediate_available(page)) ? (void)0 : _mi_assert_fail("mi_page_immediate_available(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",709,__func__));
  return 1;
}







static mi_page_t* mi_page_queue_find_free_ex(mi_heap_t* heap, mi_page_queue_t* pq, bool first_try)
{

  size_t count = 0;
  long candidate_limit = 0;
  long page_full_retain = (pq->block_size > ((((1) * (1UL << (13 + (3))))-(((3)+2)*32))/8) ? 0 : heap->page_full_retain);
  mi_page_t* page_candidate = 0;
  mi_page_t* page = pq->first;

  while (page != 0)
  {
    mi_page_t* next = page->next;
    count++;
    candidate_limit--;




    bool immediate_available = mi_page_immediate_available(page);
    if (!immediate_available) {

      _mi_page_free_collect(page, 0);
      immediate_available = mi_page_immediate_available(page);
    }



    if (!immediate_available && !mi_page_is_expandable(page)) {
      page_full_retain--;
      if (page_full_retain < 0) {
        ((!mi_page_is_in_full(page) && !mi_page_immediate_available(page)) ? (void)0 : _mi_assert_fail("!mi_page_is_in_full(page) && !mi_page_immediate_available(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",749,__func__));
        mi_page_to_full(page, pq);
      }
    }
    else {


      if (page_candidate == 0) {
        page_candidate = page;
        candidate_limit = _mi_option_get_fast(mi_option_page_max_candidates);
      }
      else if (mi_page_all_free(page_candidate)) {
        _mi_page_free(page_candidate, pq);
        page_candidate = page;
      }

      else if (page->used >= page_candidate->used && !mi_page_is_mostly_used(page)) {
        page_candidate = page;
      }

      if (immediate_available || candidate_limit <= 0) {
        ((page_candidate!=0) ? (void)0 : _mi_assert_fail("page_candidate!=NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",770,__func__));
        break;
      }
    }
# 788 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c"
    page = next;
  }

  __mi_stat_counter_increase( &(heap->tld)->stats.page_searches, count);


  if (page_candidate != 0) {
    page = page_candidate;
  }
  if (page != 0) {
    if (!mi_page_immediate_available(page)) {
      ((mi_page_is_expandable(page)) ? (void)0 : _mi_assert_fail("mi_page_is_expandable(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",799,__func__));
      if (!mi_page_extend_free(heap, page)) {
        page = 0;
      }
    }
    ((page == 0 || mi_page_immediate_available(page)) ? (void)0 : _mi_assert_fail("page == NULL || mi_page_immediate_available(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",804,__func__));
  }

  if (page == 0) {
    _mi_heap_collect_retired(heap, 0);
    page = mi_page_fresh(heap, pq);
    ((page == 0 || mi_page_immediate_available(page)) ? (void)0 : _mi_assert_fail("page == NULL || mi_page_immediate_available(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",810,__func__));
    if (page == 0 && first_try) {

      page = mi_page_queue_find_free_ex(heap, pq, 0);
      ((page == 0 || mi_page_immediate_available(page)) ? (void)0 : _mi_assert_fail("page == NULL || mi_page_immediate_available(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",814,__func__));
    }
  }
  else {
    ((page == 0 || mi_page_immediate_available(page)) ? (void)0 : _mi_assert_fail("page == NULL || mi_page_immediate_available(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",818,__func__));

    mi_page_queue_move_to_front(heap, pq, page);
    page->retire_expire = 0;

  }
  ((page == 0 || mi_page_immediate_available(page)) ? (void)0 : _mi_assert_fail("page == NULL || mi_page_immediate_available(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",824,__func__));


  return page;
}




static mi_page_t* mi_find_free_page(mi_heap_t* heap, mi_page_queue_t* pq) {

  ((!mi_page_queue_is_huge(pq)) ? (void)0 : _mi_assert_fail("!mi_page_queue_is_huge(pq)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",835,__func__));


  mi_page_t* page = pq->first;
  if (__builtin_expect(!!(page != 0 && mi_page_immediate_available(page)),1)) {






    page->retire_expire = 0;
    return page;
  }
  else {
    return mi_page_queue_find_free_ex(heap, pq, 1);
  }
}
# 862 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c"
static mi_deferred_free_fun* volatile deferred_free = 0;
static _Atomic(void*) deferred_arg;

void _mi_deferred_free(mi_heap_t* heap, bool force) {
  heap->tld->heartbeat++;
  if (deferred_free != 0 && !heap->tld->recurse) {
    heap->tld->recurse = 1;
    deferred_free(force, heap->tld->heartbeat, atomic_load_explicit(&deferred_arg,memory_order_relaxed));
    heap->tld->recurse = 0;
  }
}

void mi_register_deferred_free(mi_deferred_free_fun* fn, void* arg) {
  deferred_free = fn;
  atomic_store_explicit(&deferred_arg,arg,memory_order_release);
}
# 887 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c"
static mi_page_t* mi_huge_page_alloc(mi_heap_t* heap, size_t size, size_t page_alignment, mi_page_queue_t* pq) {
  const size_t block_size = _mi_os_good_alloc_size(size);





  ((mi_page_queue_is_huge(pq)) ? (void)0 : _mi_assert_fail("mi_page_queue_is_huge(pq)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",894,__func__));

  mi_page_t* page = mi_page_fresh_alloc(heap, pq, block_size, page_alignment);
  if (page != 0) {
    ((mi_page_block_size(page) >= size) ? (void)0 : _mi_assert_fail("mi_page_block_size(page) >= size","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",898,__func__));
    ((mi_page_immediate_available(page)) ? (void)0 : _mi_assert_fail("mi_page_immediate_available(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",899,__func__));
    ((mi_page_is_huge(page)) ? (void)0 : _mi_assert_fail("mi_page_is_huge(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",900,__func__));
    ((mi_page_is_singleton(page)) ? (void)0 : _mi_assert_fail("mi_page_is_singleton(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",901,__func__));




    __mi_stat_increase( &(heap->tld)->stats.malloc_huge, mi_page_block_size(page));
    __mi_stat_counter_increase( &(heap->tld)->stats.malloc_huge_count, 1);
  }
  return page;
}




static mi_page_t* mi_find_page(mi_heap_t* heap, size_t size, size_t huge_alignment) {
  const size_t req_size = size - (sizeof(mi_padding_t));
  if (__builtin_expect(!!(req_size > PTRDIFF_MAX),0)) {
    _mi_error_message((75), "allocation request is too large (%zu bytes)\n", req_size);
    return 0;
  }
  mi_page_queue_t* pq = mi_page_queue(heap, (huge_alignment > 0 ? ((8*((1) * (1UL << (13 + (3)))))/8)+1 : size));

  if (__builtin_expect(!!(mi_page_queue_is_huge(pq) || req_size > PTRDIFF_MAX),0)) {
    return mi_huge_page_alloc(heap,size,huge_alignment,pq);
  }
  else {


    ((size >= (sizeof(mi_padding_t))) ? (void)0 : _mi_assert_fail("size >= MI_PADDING_SIZE","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",929,__func__));

    return mi_find_free_page(heap, pq);
  }
}






void* _mi_malloc_generic(mi_heap_t* heap, size_t size, bool zero, size_t huge_alignment)
{
  ((heap != 0) ? (void)0 : _mi_assert_fail("heap != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",942,__func__));


  if (__builtin_expect(!!(!mi_heap_is_initialized(heap)),0)) {
    heap = mi_heap_get_default();
    if (__builtin_expect(!!(!mi_heap_is_initialized(heap)),0)) { return 0; }
  }
  ((mi_heap_is_initialized(heap)) ? (void)0 : _mi_assert_fail("mi_heap_is_initialized(heap)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",949,__func__));


  if (__builtin_expect(!!(++heap->generic_count >= 1000),0)) {
    heap->generic_collect_count += heap->generic_count;
    heap->generic_count = 0;

    _mi_deferred_free(heap, 0);


    const long generic_collect = mi_option_get_clamp(mi_option_generic_collect, 1, 1000000L);
    if (heap->generic_collect_count >= generic_collect) {
      heap->generic_collect_count = 0;
      mi_heap_collect(heap, 0 );
    }
  }


  mi_page_t* page = mi_find_page(heap, size, huge_alignment);
  if (__builtin_expect(!!(page == 0),0)) {
    mi_heap_collect(heap, 1 );
    page = mi_find_page(heap, size, huge_alignment);
  }

  if (__builtin_expect(!!(page == 0),0)) {
    const size_t req_size = size - (sizeof(mi_padding_t));
    _mi_error_message((12), "unable to allocate memory (%zu bytes)\n", req_size);
    return 0;
  }

  ((mi_page_immediate_available(page)) ? (void)0 : _mi_assert_fail("mi_page_immediate_available(page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",979,__func__));
  ((mi_page_block_size(page) >= size) ? (void)0 : _mi_assert_fail("mi_page_block_size(page) >= size","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",980,__func__));
  ((_mi_is_aligned(page, ((1UL << (13 + (3)))))) ? (void)0 : _mi_assert_fail("_mi_is_aligned(page, MI_PAGE_ALIGN)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",981,__func__));
  ((_mi_ptr_page(page)==page) ? (void)0 : _mi_assert_fail("_mi_ptr_page(page)==page","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",982,__func__));


  void* const p = _mi_page_malloc_zero(heap, page, size, zero);
  ((p != 0) ? (void)0 : _mi_assert_fail("p != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page.c",986,__func__));


  if (mi_page_is_full(page)) {
    mi_page_to_full(page, mi_page_queue_of(page));
  }
  return p;
}
# 0 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c"
# 14 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c"
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
# 15 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c" 2
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
# 16 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c" 2
# 39 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c"
static inline bool mi_page_queue_is_huge(const mi_page_queue_t* pq) {
  return (pq->block_size == (((8*((1) * (1UL << (13 + (3)))))/8)+sizeof(uintptr_t)));
}

static inline bool mi_page_queue_is_full(const mi_page_queue_t* pq) {
  return (pq->block_size == (((8*((1) * (1UL << (13 + (3)))))/8)+(2*sizeof(uintptr_t))));
}

static inline bool mi_page_queue_is_special(const mi_page_queue_t* pq) {
  return (pq->block_size > ((8*((1) * (1UL << (13 + (3)))))/8));
}

static inline size_t mi_page_queue_count(const mi_page_queue_t* pq) {
  return pq->count;
}
# 63 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c"
static size_t mi_bin(size_t size) {
  size_t wsize = _mi_wsize_from_size(size);





  if (__builtin_expect(!!(wsize <= 8),1)) {
    return (wsize <= 1 ? 1 : (wsize+1)&~1);
  }





  else if (__builtin_expect(!!(wsize > (((8*((1) * (1UL << (13 + (3)))))/8)/(1<<(3)))),0)) {
    return (73U);
  }
  else {



    wsize--;

    const size_t b = (((1<<(3))*8) - 1 - mi_clz(wsize));



    const size_t bin = ((b << 2) + ((wsize >> (b - 2)) & 0x03)) - 3;
    ((bin > 0 && bin < (73U)) ? (void)0 : _mi_assert_fail("bin > 0 && bin < MI_BIN_HUGE","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",92,__func__));
    return bin;
  }
}







size_t _mi_bin(size_t size) {
  return mi_bin(size);
}

size_t _mi_bin_size(size_t bin) {
  ((bin <= (73U)) ? (void)0 : _mi_assert_fail("bin <= MI_BIN_HUGE","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",108,__func__));
  return _mi_heap_empty.pages[bin].block_size;
}


 size_t mi_good_size(size_t size) {
  if (size <= ((8*((1) * (1UL << (13 + (3)))))/8)) {
    return _mi_bin_size(mi_bin(size + (sizeof(mi_padding_t))));
  }
  else {
    return _mi_align_up(size + (sizeof(mi_padding_t)),_mi_os_page_size());
  }
}


static bool mi_page_queue_contains(mi_page_queue_t* queue, const mi_page_t* page) {
  ((page != 0) ? (void)0 : _mi_assert_fail("page != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",124,__func__));
  mi_page_t* list = queue->first;
  while (list != 0) {
    ((list->next == 0 || list->next->prev == list) ? (void)0 : _mi_assert_fail("list->next == NULL || list->next->prev == list","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",127,__func__));
    ((list->prev == 0 || list->prev->next == list) ? (void)0 : _mi_assert_fail("list->prev == NULL || list->prev->next == list","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",128,__func__));
    if (list == page) break;
    list = list->next;
  }
  return (list == page);
}




static bool mi_heap_contains_queue(const mi_heap_t* heap, const mi_page_queue_t* pq) {
  return (pq >= &heap->pages[0] && pq <= &heap->pages[((73U)+1)]);
}


bool _mi_page_queue_is_valid(mi_heap_t* heap, const mi_page_queue_t* pq) {
  ;
  if (pq==0) return 0;
  size_t count = 0; ;
  mi_page_t* prev = 0; ;
  for (mi_page_t* page = pq->first; page != 0; page = page->next) {
    ((page->prev == prev) ? (void)0 : _mi_assert_fail("page->prev == prev","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",149,__func__));
    if (mi_page_is_in_full(page)) {
      ((_mi_wsize_from_size(pq->block_size) == (((8*((1) * (1UL << (13 + (3)))))/8)/(1<<(3))) + 2) ? (void)0 : _mi_assert_fail("_mi_wsize_from_size(pq->block_size) == MI_LARGE_MAX_OBJ_WSIZE + 2","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",151,__func__));
    }
    else if (mi_page_is_huge(page)) {
      ((_mi_wsize_from_size(pq->block_size) == (((8*((1) * (1UL << (13 + (3)))))/8)/(1<<(3))) + 1) ? (void)0 : _mi_assert_fail("_mi_wsize_from_size(pq->block_size) == MI_LARGE_MAX_OBJ_WSIZE + 1","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",154,__func__));
    }
    else {
      ((mi_page_block_size(page) == pq->block_size) ? (void)0 : _mi_assert_fail("mi_page_block_size(page) == pq->block_size","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",157,__func__));
    }
    ((page->heap == heap) ? (void)0 : _mi_assert_fail("page->heap == heap","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",159,__func__));
    if (page->next == 0) {
      ((pq->last == page) ? (void)0 : _mi_assert_fail("pq->last == page","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",161,__func__));
    }
    count++;
    prev = page;
  }
  ((pq->count == count) ? (void)0 : _mi_assert_fail("pq->count == count","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",166,__func__));
  return 1;
}

size_t _mi_page_bin(const mi_page_t* page) {
  const size_t bin = (mi_page_is_in_full(page) ? ((73U)+1) : (mi_page_is_huge(page) ? (73U) : mi_bin(mi_page_block_size(page))));
  ((bin <= ((73U)+1)) ? (void)0 : _mi_assert_fail("bin <= MI_BIN_FULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",172,__func__));
  return bin;
}

static mi_page_queue_t* mi_heap_page_queue_of(mi_heap_t* heap, const mi_page_t* page) {
  ((heap!=0) ? (void)0 : _mi_assert_fail("heap!=NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",177,__func__));
  const size_t bin = _mi_page_bin(page);
  mi_page_queue_t* pq = &heap->pages[bin];
  (((mi_page_block_size(page) == pq->block_size) || (mi_page_is_huge(page) && mi_page_queue_is_huge(pq)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(pq))) ? (void)0 : _mi_assert_fail("(mi_page_block_size(page) == pq->block_size) || (mi_page_is_huge(page) && mi_page_queue_is_huge(pq)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(pq))","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",180,__func__))

                                                                                 ;
  return pq;
}

static mi_page_queue_t* mi_page_queue_of(const mi_page_t* page) {
  mi_heap_t* heap = mi_page_heap(page);
  mi_page_queue_t* pq = mi_heap_page_queue_of(heap, page);
  ;
  return pq;
}






static inline void mi_heap_queue_first_update(mi_heap_t* heap, const mi_page_queue_t* pq) {
  ((mi_heap_contains_queue(heap,pq)) ? (void)0 : _mi_assert_fail("mi_heap_contains_queue(heap,pq)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",199,__func__));
  size_t size = pq->block_size;
  if (size > ((128)*sizeof(void*))) return;

  mi_page_t* page = pq->first;
  if (pq->first == 0) page = (mi_page_t*)&_mi_page_empty;


  size_t start;
  size_t idx = _mi_wsize_from_size(size);
  mi_page_t** pages_free = heap->pages_free_direct;

  if (pages_free[idx] == page) return;


  if (idx<=1) {
    start = 0;
  }
  else {

    size_t bin = mi_bin(size);
    const mi_page_queue_t* prev = pq - 1;
    while( bin == mi_bin(prev->block_size) && prev > &heap->pages[0]) {
      prev--;
    }
    start = 1 + _mi_wsize_from_size(prev->block_size);
    if (start > idx) start = idx;
  }


  ((start <= idx) ? (void)0 : _mi_assert_fail("start <= idx","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",229,__func__));
  for (size_t sz = start; sz <= idx; sz++) {
    pages_free[sz] = page;
  }
}







static void mi_page_queue_remove(mi_page_queue_t* queue, mi_page_t* page) {
  ((page != 0) ? (void)0 : _mi_assert_fail("page != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",242,__func__));
  ;
  ((queue->count >= 1) ? (void)0 : _mi_assert_fail("queue->count >= 1","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",244,__func__));
  ((mi_page_block_size(page) == queue->block_size || (mi_page_is_huge(page) && mi_page_queue_is_huge(queue)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))) ? (void)0 : _mi_assert_fail("mi_page_block_size(page) == queue->block_size || (mi_page_is_huge(page) && mi_page_queue_is_huge(queue)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",245,__func__))

                                                                                   ;
  mi_heap_t* heap = mi_page_heap(page);
  if (page->prev != 0) page->prev->next = page->next;
  if (page->next != 0) page->next->prev = page->prev;
  if (page == queue->last) queue->last = page->prev;
  if (page == queue->first) {
    queue->first = page->next;

    ((mi_heap_contains_queue(heap, queue)) ? (void)0 : _mi_assert_fail("mi_heap_contains_queue(heap, queue)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",255,__func__));
    mi_heap_queue_first_update(heap,queue);
  }
  heap->page_count--;
  queue->count--;
  page->next = 0;
  page->prev = 0;
  mi_page_set_in_full(page,0);
}


static void mi_page_queue_push(mi_heap_t* heap, mi_page_queue_t* queue, mi_page_t* page) {
  ((mi_page_heap(page) == heap) ? (void)0 : _mi_assert_fail("mi_page_heap(page) == heap","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",267,__func__));
  ((!mi_page_queue_contains(queue, page)) ? (void)0 : _mi_assert_fail("!mi_page_queue_contains(queue, page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",268,__func__));



  ((mi_page_block_size(page) == queue->block_size || (mi_page_is_huge(page) && mi_page_queue_is_huge(queue)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))) ? (void)0 : _mi_assert_fail("mi_page_block_size(page) == queue->block_size || (mi_page_is_huge(page) && mi_page_queue_is_huge(queue)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",272,__func__))

                                                                                   ;

  mi_page_set_in_full(page, mi_page_queue_is_full(queue));

  page->next = queue->first;
  page->prev = 0;
  if (queue->first != 0) {
    ((queue->first->prev == 0) ? (void)0 : _mi_assert_fail("queue->first->prev == NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",281,__func__));
    queue->first->prev = page;
    queue->first = page;
  }
  else {
    queue->first = queue->last = page;
  }
  queue->count++;


  mi_heap_queue_first_update(heap, queue);
  heap->page_count++;
}

static void mi_page_queue_push_at_end(mi_heap_t* heap, mi_page_queue_t* queue, mi_page_t* page) {
  ((mi_page_heap(page) == heap) ? (void)0 : _mi_assert_fail("mi_page_heap(page) == heap","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",296,__func__));
  ((!mi_page_queue_contains(queue, page)) ? (void)0 : _mi_assert_fail("!mi_page_queue_contains(queue, page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",297,__func__));

  ((mi_page_block_size(page) == queue->block_size || (mi_page_is_huge(page) && mi_page_queue_is_huge(queue)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))) ? (void)0 : _mi_assert_fail("mi_page_block_size(page) == queue->block_size || (mi_page_is_huge(page) && mi_page_queue_is_huge(queue)) || (mi_page_is_in_full(page) && mi_page_queue_is_full(queue))","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",299,__func__))

                                                                                  ;

  mi_page_set_in_full(page, mi_page_queue_is_full(queue));

  page->prev = queue->last;
  page->next = 0;
  if (queue->last != 0) {
    ((queue->last->next == 0) ? (void)0 : _mi_assert_fail("queue->last->next == NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",308,__func__));
    queue->last->next = page;
    queue->last = page;
  }
  else {
    queue->first = queue->last = page;
  }
  queue->count++;


  if (queue->first == page) {
    mi_heap_queue_first_update(heap, queue);
  }
  heap->page_count++;
}

static void mi_page_queue_move_to_front(mi_heap_t* heap, mi_page_queue_t* queue, mi_page_t* page) {
  ((mi_page_heap(page) == heap) ? (void)0 : _mi_assert_fail("mi_page_heap(page) == heap","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",325,__func__));
  ((mi_page_queue_contains(queue, page)) ? (void)0 : _mi_assert_fail("mi_page_queue_contains(queue, page)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",326,__func__));
  if (queue->first == page) return;
  mi_page_queue_remove(queue, page);
  mi_page_queue_push(heap, queue, page);
  ((queue->first == page) ? (void)0 : _mi_assert_fail("queue->first == page","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",330,__func__));
}

static void mi_page_queue_enqueue_from_ex(mi_page_queue_t* to, mi_page_queue_t* from, bool enqueue_at_end, mi_page_t* page) {
  ((page != 0) ? (void)0 : _mi_assert_fail("page != NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",334,__func__));
  ((from->count >= 1) ? (void)0 : _mi_assert_fail("from->count >= 1","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",335,__func__));
  ;
  ;
  const size_t bsize = mi_page_block_size(page);
  (void)(bsize);
  (((bsize == to->block_size && bsize == from->block_size) || (bsize == to->block_size && mi_page_queue_is_full(from)) || (bsize == from->block_size && mi_page_queue_is_full(to)) || (mi_page_is_huge(page) && mi_page_queue_is_huge(to)) || (mi_page_is_huge(page) && mi_page_queue_is_full(to))) ? (void)0 : _mi_assert_fail("(bsize == to->block_size && bsize == from->block_size) || (bsize == to->block_size && mi_page_queue_is_full(from)) || (bsize == from->block_size && mi_page_queue_is_full(to)) || (mi_page_is_huge(page) && mi_page_queue_is_huge(to)) || (mi_page_is_huge(page) && mi_page_queue_is_full(to))","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",340,__func__))



                                                                          ;

  mi_heap_t* heap = mi_page_heap(page);


  if (page->prev != 0) page->prev->next = page->next;
  if (page->next != 0) page->next->prev = page->prev;
  if (page == from->last) from->last = page->prev;
  if (page == from->first) {
    from->first = page->next;

    ((mi_heap_contains_queue(heap, from)) ? (void)0 : _mi_assert_fail("mi_heap_contains_queue(heap, from)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",355,__func__));
    mi_heap_queue_first_update(heap, from);
  }
  from->count--;


  to->count++;
  if (enqueue_at_end) {

    page->prev = to->last;
    page->next = 0;
    if (to->last != 0) {
      ((heap == mi_page_heap(to->last)) ? (void)0 : _mi_assert_fail("heap == mi_page_heap(to->last)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",367,__func__));
      to->last->next = page;
      to->last = page;
    }
    else {
      to->first = page;
      to->last = page;
      mi_heap_queue_first_update(heap, to);
    }
  }
  else {
    if (to->first != 0) {

      ((heap == mi_page_heap(to->first)) ? (void)0 : _mi_assert_fail("heap == mi_page_heap(to->first)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",380,__func__));
      mi_page_t* next = to->first->next;
      page->prev = to->first;
      page->next = next;
      to->first->next = page;
      if (next != 0) {
        next->prev = page;
      }
      else {
        to->last = page;
      }
    }
    else {

      page->prev = 0;
      page->next = 0;
      to->first = page;
      to->last = page;
      mi_heap_queue_first_update(heap, to);
    }
  }

  mi_page_set_in_full(page, mi_page_queue_is_full(to));
}

static void mi_page_queue_enqueue_from(mi_page_queue_t* to, mi_page_queue_t* from, mi_page_t* page) {
  mi_page_queue_enqueue_from_ex(to, from, 1 , page);
}

static void mi_page_queue_enqueue_from_full(mi_page_queue_t* to, mi_page_queue_t* from, mi_page_t* page) {

  mi_page_queue_enqueue_from_ex(to, from, 1 , page);
}


size_t _mi_page_queue_append(mi_heap_t* heap, mi_page_queue_t* pq, mi_page_queue_t* append) {
  ((mi_heap_contains_queue(heap,pq)) ? (void)0 : _mi_assert_fail("mi_heap_contains_queue(heap,pq)","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",416,__func__));
  ((pq->block_size == append->block_size) ? (void)0 : _mi_assert_fail("pq->block_size == append->block_size","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",417,__func__));

  if (append->first==0) return 0;


  size_t count = 0;
  for (mi_page_t* page = append->first; page != 0; page = page->next) {
    mi_page_set_heap(page, heap);
    count++;
  }
  ((count == append->count) ? (void)0 : _mi_assert_fail("count == append->count","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",427,__func__));

  if (pq->last==0) {

    ((pq->first==0) ? (void)0 : _mi_assert_fail("pq->first==NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",431,__func__));
    pq->first = append->first;
    pq->last = append->last;
    mi_heap_queue_first_update(heap, pq);
  }
  else {

    ((pq->last!=0) ? (void)0 : _mi_assert_fail("pq->last!=NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",438,__func__));
    ((append->first!=0) ? (void)0 : _mi_assert_fail("append->first!=NULL","/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/page-queue.c",439,__func__));
    pq->last->next = append->first;
    append->first->prev = pq->last;
    pq->last = append->last;
  }
  pq->count += append->count;

  return count;
}
