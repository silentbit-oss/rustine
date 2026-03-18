# 0 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c"
# 18 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c"
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 2
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
# 3 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 2
# 19 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 20 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 21 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdbool.h" 1
# 22 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 23 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 1
# 24 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c" 2
# 57 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c"
static int THREADS = 32;
static int SCALE = 50;
static int ITER = 50;
# 70 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c"
static bool allow_large_objects = 0;

static size_t use_one_size = 0;

static bool main_participates = 0;






# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc.h" 1






       
# 98 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc.h"
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
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
# 82 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c" 2
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
# 83 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c" 2
# 94 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c"
static volatile void* transfer[(1000)];





const uintptr_t cookie = 0x1ce4e5b9UL;


static void* atomic_exchange_ptr(volatile void** p, void* newval);

typedef uintptr_t* random_t;

static uintptr_t pick(random_t r) {
  uintptr_t x = *r;
# 118 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c"
  x ^= x >> 16;
  x *= 0x7feb352dUL;
  x ^= x >> 15;
  x *= 0x846ca68bUL;
  x ^= x >> 16;

  *r = x;
  return x;
}

static bool chance(size_t perc, random_t r) {
  return (pick(r) % 100 <= perc);
}

static void* alloc_items(size_t items, random_t r) {
  if (chance(1, r)) {
    if (chance(1, r) && allow_large_objects) items *= 10000;
    else if (chance(10, r) && allow_large_objects) items *= 1000;
    else items *= 100;
  }
  if (items>=32 && items<=40) items*=2;
  if (use_one_size > 0) items = (use_one_size / sizeof(uintptr_t));
  if (items==0) items = 1;
  uintptr_t* p = (uintptr_t*)mi_calloc(items,sizeof(uintptr_t));
  if (p != 0) {
    for (uintptr_t i = 0; i < items; i++) {
      assert(p[i] == 0);
      p[i] = (items - i) ^ cookie;
    }
  }
  return p;
}

static void free_items(void* p) {
  if (p != 0) {
    uintptr_t* q = (uintptr_t*)p;
    uintptr_t items = (q[0] ^ cookie);
    for (uintptr_t i = 0; i < items; i++) {
      if ((q[i] ^ cookie) != items - i) {
        fprintf(stderr, "memory corruption at block %p at %zu\n", p, i);
        abort();
      }
    }
  }
  mi_free(p);
}
# 176 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c"
static void stress(intptr_t tid) {

  uintptr_t r = ((tid + 1) * 43);
  const size_t max_item_shift = 5;
  const size_t max_item_retained_shift = max_item_shift + 2;
  size_t allocs = 100 * ((size_t)SCALE) * (tid % 8 + 1);
  size_t retain = allocs / 2;
  void** data = 0;
  size_t data_size = 0;
  size_t data_top = 0;
  void** retained = (void**)mi_calloc(retain,sizeof(void*));
  size_t retain_top = 0;

  while (allocs > 0 || retain > 0) {
    if (retain == 0 || (chance(50, &r) && allocs > 0)) {

      allocs--;
      if (data_top >= data_size) {
        data_size += 100000;
        data = (void**)mi_realloc(data,data_size * sizeof(void*));
      }
      data[data_top++] = alloc_items(1ULL << (pick(&r) % max_item_shift), &r);
    }
    else {

      retained[retain_top++] = alloc_items( 1ULL << (pick(&r) % max_item_retained_shift), &r);
      retain--;
    }
    if (chance(66, &r) && data_top > 0) {

      size_t idx = pick(&r) % data_top;
      free_items(data[idx]);
      data[idx] = 0;
    }
    if (chance(25, &r) && data_top > 0) {

      size_t data_idx = pick(&r) % data_top;
      size_t transfer_idx = pick(&r) % (1000);
      void* p = data[data_idx];
      void* q = atomic_exchange_ptr(&transfer[transfer_idx], p);
      data[data_idx] = q;
    }
  }
# 227 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c"
  for (size_t i = 0; i < retain_top; i++) {
    free_items(retained[i]);
  }
  for (size_t i = 0; i < data_top; i++) {
    free_items(data[i]);
  }
  mi_free(retained);
  mi_free(data);

}

static void run_os_threads(size_t nthreads, void (*entry)(intptr_t tid));

static void test_stress(void) {
  uintptr_t r = rand();
  for (int n = 0; n < ITER; n++) {
    run_os_threads(THREADS, &stress);
# 252 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c"
    for (int i = 0; i < (1000); i++) {
      if (chance(50, &r) || n + 1 == ITER) {
        void* p = atomic_exchange_ptr(&transfer[i], 0);
        free_items(p);
      }
    }





    if ((n + 1) % 10 == 0) {
      printf("- iterations left: %3d\n", ITER - (n + 1));

      mi_debug_show_arenas();



    }

  }

  for (int i = 0; i < (1000); i++) {
    void* p = atomic_exchange_ptr(&transfer[i], 0);
    if (p != 0) {
      free_items(p);
    }
  }
}
# 311 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c"
int main(int argc, char** argv) {
# 328 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c"
  if (argc >= 2) {
    char* end;
    long n = strtol(argv[1], &end, 10);
    if (n > 0) THREADS = n;
  }
  if (argc >= 3) {
    char* end;
    long n = (strtol(argv[2], &end, 10));
    if (n > 0) SCALE = n;
  }
  if (argc >= 4) {
    char* end;
    long n = (strtol(argv[3], &end, 10));
    if (n > 0) ITER = n;
  }
  if (SCALE > 100) {
    allow_large_objects = 1;
  }
  printf("Using %d threads with a %d%% load-per-thread and %d iterations %s\n", THREADS, SCALE, ITER, (allow_large_objects ? "(allow large objects)" : ""));


  mi_stats_reset();
# 359 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c"
  srand(0x7feb352d);


    test_stress();






  mi_debug_show_arenas();
  mi_collect(1);
  char* json = mi_stats_get_json(0, 0);
  if (json != 0) {
    fputs(json,stderr);
    mi_free(json);
  }

  mi_collect(1);
  mi_stats_print(0);


  return 0;
}


static void (*thread_entry_fun)(intptr_t) = &stress;
# 425 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c"
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/pthread.h" 1
# 426 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c" 2

static void* thread_entry(void* param) {
  thread_entry_fun((uintptr_t)param);
  return 0;
}

static void run_os_threads(size_t nthreads, void (*fun)(intptr_t)) {
  thread_entry_fun = fun;
  pthread_t* threads = (pthread_t*)mi_calloc(nthreads,sizeof(pthread_t));
  memset(threads, 0, sizeof(pthread_t) * nthreads);
  const size_t start = (main_participates ? 1 : 0);

  for (size_t i = start; i < nthreads; i++) {
    pthread_create(&threads[i], 0, &thread_entry, (void*)i);
  }
  if (main_participates) fun(0);
  for (size_t i = start; i < nthreads; i++) {
    pthread_join(threads[i], 0);
  }
  mi_free(threads);
}







# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdatomic.h" 1
# 455 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c" 2
static void* atomic_exchange_ptr(volatile void** p, void* newval) {
  return atomic_exchange((volatile _Atomic(void*)*)p, newval);
}
# 0 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c"
# 18 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c"
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 2
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
# 3 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 2
# 19 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 20 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 21 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdbool.h" 1
# 22 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 23 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c" 2
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 1
# 24 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c" 2
# 57 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c"
static int THREADS = 32;
static int SCALE = 50;
static int ITER = 50;
# 70 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c"
static bool allow_large_objects = 0;

static size_t use_one_size = 0;

static bool main_participates = 0;






# 1 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc.h" 1






       
# 98 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/include/mimalloc.h"
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
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
# 82 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c" 2
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
# 83 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c" 2
# 94 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c"
static volatile void* transfer[(1000)];





const uintptr_t cookie = 0x1ce4e5b9UL;


static void* atomic_exchange_ptr(volatile void** p, void* newval);

typedef uintptr_t* random_t;

static uintptr_t pick(random_t r) {
  uintptr_t x = *r;
# 118 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c"
  x ^= x >> 16;
  x *= 0x7feb352dUL;
  x ^= x >> 15;
  x *= 0x846ca68bUL;
  x ^= x >> 16;

  *r = x;
  return x;
}

static bool chance(size_t perc, random_t r) {
  return (pick(r) % 100 <= perc);
}

static void* alloc_items(size_t items, random_t r) {
  if (chance(1, r)) {
    if (chance(1, r) && allow_large_objects) items *= 10000;
    else if (chance(10, r) && allow_large_objects) items *= 1000;
    else items *= 100;
  }
  if (items>=32 && items<=40) items*=2;
  if (use_one_size > 0) items = (use_one_size / sizeof(uintptr_t));
  if (items==0) items = 1;
  uintptr_t* p = (uintptr_t*)mi_calloc(items,sizeof(uintptr_t));
  if (p != 0) {
    for (uintptr_t i = 0; i < items; i++) {
      assert(p[i] == 0);
      p[i] = (items - i) ^ cookie;
    }
  }
  return p;
}

static void free_items(void* p) {
  if (p != 0) {
    uintptr_t* q = (uintptr_t*)p;
    uintptr_t items = (q[0] ^ cookie);
    for (uintptr_t i = 0; i < items; i++) {
      if ((q[i] ^ cookie) != items - i) {
        fprintf(stderr, "memory corruption at block %p at %zu\n", p, i);
        abort();
      }
    }
  }
  mi_free(p);
}
# 176 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c"
static void stress(intptr_t tid) {

  uintptr_t r = ((tid + 1) * 43);
  const size_t max_item_shift = 5;
  const size_t max_item_retained_shift = max_item_shift + 2;
  size_t allocs = 100 * ((size_t)SCALE) * (tid % 8 + 1);
  size_t retain = allocs / 2;
  void** data = 0;
  size_t data_size = 0;
  size_t data_top = 0;
  void** retained = (void**)mi_calloc(retain,sizeof(void*));
  size_t retain_top = 0;

  while (allocs > 0 || retain > 0) {
    if (retain == 0 || (chance(50, &r) && allocs > 0)) {

      allocs--;
      if (data_top >= data_size) {
        data_size += 100000;
        data = (void**)mi_realloc(data,data_size * sizeof(void*));
      }
      data[data_top++] = alloc_items(1ULL << (pick(&r) % max_item_shift), &r);
    }
    else {

      retained[retain_top++] = alloc_items( 1ULL << (pick(&r) % max_item_retained_shift), &r);
      retain--;
    }
    if (chance(66, &r) && data_top > 0) {

      size_t idx = pick(&r) % data_top;
      free_items(data[idx]);
      data[idx] = 0;
    }
    if (chance(25, &r) && data_top > 0) {

      size_t data_idx = pick(&r) % data_top;
      size_t transfer_idx = pick(&r) % (1000);
      void* p = data[data_idx];
      void* q = atomic_exchange_ptr(&transfer[transfer_idx], p);
      data[data_idx] = q;
    }
  }
# 227 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c"
  for (size_t i = 0; i < retain_top; i++) {
    free_items(retained[i]);
  }
  for (size_t i = 0; i < data_top; i++) {
    free_items(data[i]);
  }
  mi_free(retained);
  mi_free(data);

}

static void run_os_threads(size_t nthreads, void (*entry)(intptr_t tid));

static void test_stress(void) {
  uintptr_t r = rand();
  for (int n = 0; n < ITER; n++) {
    run_os_threads(THREADS, &stress);
# 252 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c"
    for (int i = 0; i < (1000); i++) {
      if (chance(50, &r) || n + 1 == ITER) {
        void* p = atomic_exchange_ptr(&transfer[i], 0);
        free_items(p);
      }
    }





    if ((n + 1) % 10 == 0) {
      printf("- iterations left: %3d\n", ITER - (n + 1));

      mi_debug_show_arenas();



    }

  }

  for (int i = 0; i < (1000); i++) {
    void* p = atomic_exchange_ptr(&transfer[i], 0);
    if (p != 0) {
      free_items(p);
    }
  }
}
# 311 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c"
int main(int argc, char** argv) {
# 328 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c"
  if (argc >= 2) {
    char* end;
    long n = strtol(argv[1], &end, 10);
    if (n > 0) THREADS = n;
  }
  if (argc >= 3) {
    char* end;
    long n = (strtol(argv[2], &end, 10));
    if (n > 0) SCALE = n;
  }
  if (argc >= 4) {
    char* end;
    long n = (strtol(argv[3], &end, 10));
    if (n > 0) ITER = n;
  }
  if (SCALE > 100) {
    allow_large_objects = 1;
  }
  printf("Using %d threads with a %d%% load-per-thread and %d iterations %s\n", THREADS, SCALE, ITER, (allow_large_objects ? "(allow large objects)" : ""));


  mi_stats_reset();
# 359 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c"
  srand(0x7feb352d);


    test_stress();






  mi_debug_show_arenas();
  mi_collect(1);
  char* json = mi_stats_get_json(0, 0);
  if (json != 0) {
    fputs(json,stderr);
    mi_free(json);
  }

  mi_collect(1);
  mi_stats_print(0);


  return 0;
}


static void (*thread_entry_fun)(intptr_t) = &stress;
# 425 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c"
# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/pthread.h" 1
# 426 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c" 2

static void* thread_entry(void* param) {
  thread_entry_fun((uintptr_t)param);
  return 0;
}

static void run_os_threads(size_t nthreads, void (*fun)(intptr_t)) {
  thread_entry_fun = fun;
  pthread_t* threads = (pthread_t*)mi_calloc(nthreads,sizeof(pthread_t));
  memset(threads, 0, sizeof(pthread_t) * nthreads);
  const size_t start = (main_participates ? 1 : 0);

  for (size_t i = start; i < nthreads; i++) {
    pthread_create(&threads[i], 0, &thread_entry, (void*)i);
  }
  if (main_participates) fun(0);
  for (size_t i = start; i < nthreads; i++) {
    pthread_join(threads[i], 0);
  }
  mi_free(threads);
}







# 1 "/home/ubuntu/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdatomic.h" 1
# 455 "/home/ubuntu/C2RustTranslation/subjects/mimalloc/test/test-stress.c" 2
static void* atomic_exchange_ptr(volatile void** p, void* newval) {
  return atomic_exchange((volatile _Atomic(void*)*)p, newval);
}
