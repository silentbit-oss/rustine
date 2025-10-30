# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.c"
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.c"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.h" 1
# 14 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/bitset.h" 1
# 14 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/bitset.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1



typedef int START_DELIMETER;
typedef unsigned chtype;
typedef chtype attr_t;
typedef int socklen_t;
typedef int size_t;
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
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 2
# 15 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/bitset.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 16 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/bitset.h" 2
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/bitset.h"
typedef unsigned int opng_bitset_t;
# 45 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/bitset.h"
enum
{
    OPNG_BITSET_ELT_MIN = 0,
    OPNG_BITSET_ELT_MAX = (int)((sizeof(opng_bitset_t) * 8) - 1)
};
# 174 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/bitset.h"
unsigned int
opng_bitset_count(opng_bitset_t set);







int
opng_bitset_find_first(opng_bitset_t set);







int
opng_bitset_find_next(opng_bitset_t set, int elt);







int
opng_bitset_find_last(opng_bitset_t set);







int
opng_bitset_find_prev(opng_bitset_t set, int elt);
# 241 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/bitset.h"
int
opng_strparse_rangeset_to_bitset(opng_bitset_t *out_set,
                                 const char *rangeset_str,
                                 opng_bitset_t mask_set);
# 253 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/bitset.h"
size_t
opng_strformat_bitset_as_rangeset(char *out_buf,
                                  size_t out_buf_size,
                                  opng_bitset_t bitset);
# 15 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.h" 2
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.h"
struct opng_options
{

    int backup;
    int clobber;
    int debug;
    int fix;
    int force;
    int full;
    int preserve;
    int quiet;
    int simulate;
    int verbose;
    const char *out_name;
    const char *dir_name;
    const char *log_name;


    int interlace;
    int nb, nc, np, nz;
    int optim_level;
    opng_bitset_t compr_level_set;
    opng_bitset_t mem_level_set;
    opng_bitset_t strategy_set;
    opng_bitset_t filter_set;
    int window_bits;


    int snip;
    int strip_all;
};





struct opng_ui
{
    void (*printf_fn)(const char *fmt, ...);
    void (*print_cntrl_fn)(int cntrl_code);
    void (*progress_fn)(unsigned long current_step, unsigned long total_steps);
    void (*panic_fn)(const char *msg);
};





int opng_initialize(const struct opng_options *options,
                    const struct opng_ui *ui);




int opng_optimize(const char *infile_name);




int opng_finalize(void);
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/proginfo.h" 1
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/ctype.h" 1
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/errno.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdarg.h" 1
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h" 1
# 330 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/pnglibconf.h" 1
# 331 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h" 2




# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/pngconf.h" 1
# 31 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/pngconf.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 1
# 32 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/pngconf.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 33 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/pngconf.h" 2
# 46 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/pngconf.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 47 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/pngconf.h" 2
# 481 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/pngconf.h"
   typedef unsigned char png_byte;







   typedef short png_int_16;







   typedef unsigned short png_uint_16;





   typedef int png_int_32;







   typedef unsigned int png_uint_32;
# 523 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/pngconf.h"
typedef size_t png_size_t;
typedef ptrdiff_t png_ptrdiff_t;
# 557 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/pngconf.h"
   typedef size_t png_alloc_size_t;
# 574 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/pngconf.h"
typedef png_int_32 png_fixed_point;


typedef void * png_voidp;
typedef const void * png_const_voidp;
typedef png_byte * png_bytep;
typedef const png_byte * png_const_bytep;
typedef png_uint_32 * png_uint_32p;
typedef const png_uint_32 * png_const_uint_32p;
typedef png_int_32 * png_int_32p;
typedef const png_int_32 * png_const_int_32p;
typedef png_uint_16 * png_uint_16p;
typedef const png_uint_16 * png_const_uint_16p;
typedef png_int_16 * png_int_16p;
typedef const png_int_16 * png_const_int_16p;
typedef char * png_charp;
typedef const char * png_const_charp;
typedef png_fixed_point * png_fixed_point_p;
typedef const png_fixed_point * png_const_fixed_point_p;
typedef size_t * png_size_tp;
typedef const size_t * png_const_size_tp;


typedef FILE * png_FILE_p;
# 606 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/pngconf.h"
typedef png_byte * * png_bytepp;
typedef png_uint_32 * * png_uint_32pp;
typedef png_int_32 * * png_int_32pp;
typedef png_uint_16 * * png_uint_16pp;
typedef png_int_16 * * png_int_16pp;
typedef const char * * png_const_charpp;
typedef char * * png_charpp;
typedef png_fixed_point * * png_fixed_point_pp;





typedef char * * * png_charppp;
# 336 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h" 2
# 431 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
typedef char* png_libpng_version_1_6_40;







typedef struct png_struct_def png_struct;
typedef const png_struct * png_const_structp;
typedef png_struct * png_structp;
typedef png_struct * * png_structpp;
# 453 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
typedef struct png_info_def png_info;
typedef png_info * png_infop;
typedef const png_info * png_const_infop;
typedef png_info * * png_infopp;
# 469 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
typedef png_struct * png_structrp;
typedef const png_struct * png_const_structrp;
typedef png_info * png_inforp;
typedef const png_info * png_const_inforp;





typedef struct png_color_struct
{
   png_byte red;
   png_byte green;
   png_byte blue;
} png_color;
typedef png_color * png_colorp;
typedef const png_color * png_const_colorp;
typedef png_color * * png_colorpp;

typedef struct png_color_16_struct
{
   png_byte index;
   png_uint_16 red;
   png_uint_16 green;
   png_uint_16 blue;
   png_uint_16 gray;
} png_color_16;
typedef png_color_16 * png_color_16p;
typedef const png_color_16 * png_const_color_16p;
typedef png_color_16 * * png_color_16pp;

typedef struct png_color_8_struct
{
   png_byte red;
   png_byte green;
   png_byte blue;
   png_byte gray;
   png_byte alpha;
} png_color_8;
typedef png_color_8 * png_color_8p;
typedef const png_color_8 * png_const_color_8p;
typedef png_color_8 * * png_color_8pp;





typedef struct png_sPLT_entry_struct
{
   png_uint_16 red;
   png_uint_16 green;
   png_uint_16 blue;
   png_uint_16 alpha;
   png_uint_16 frequency;
} png_sPLT_entry;
typedef png_sPLT_entry * png_sPLT_entryp;
typedef const png_sPLT_entry * png_const_sPLT_entryp;
typedef png_sPLT_entry * * png_sPLT_entrypp;






typedef struct png_sPLT_struct
{
   png_charp name;
   png_byte depth;
   png_sPLT_entryp entries;
   png_int_32 nentries;
} png_sPLT_t;
typedef png_sPLT_t * png_sPLT_tp;
typedef const png_sPLT_t * png_const_sPLT_tp;
typedef png_sPLT_t * * png_sPLT_tpp;
# 600 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
typedef struct png_time_struct
{
   png_uint_16 year;
   png_byte month;
   png_byte day;
   png_byte hour;
   png_byte minute;
   png_byte second;
} png_time;
typedef png_time * png_timep;
typedef const png_time * png_const_timep;
typedef png_time * * png_timepp;
# 622 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
typedef struct png_unknown_chunk_t
{
   png_byte name[5];
   png_byte *data;
   size_t size;







   png_byte location;
}
png_unknown_chunk;

typedef png_unknown_chunk * png_unknown_chunkp;
typedef const png_unknown_chunk * png_const_unknown_chunkp;
typedef png_unknown_chunk * * png_unknown_chunkpp;
# 754 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
typedef struct png_row_info_struct
{
   png_uint_32 width;
   size_t rowbytes;
   png_byte color_type;
   png_byte bit_depth;
   png_byte channels;
   png_byte pixel_depth;
} png_row_info;

typedef png_row_info * png_row_infop;
typedef png_row_info * * png_row_infopp;
# 775 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
typedef void ( *png_error_ptr) (png_structp, png_const_charp);
typedef void ( *png_rw_ptr) (png_structp, png_bytep, size_t);
typedef void ( *png_flush_ptr) (png_structp);
typedef void ( *png_read_status_ptr) (png_structp, png_uint_32, int)
         ;
typedef void ( *png_write_status_ptr) (png_structp, png_uint_32, int)
         ;
# 867 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
typedef png_voidp ( *png_malloc_ptr) (png_structp, png_alloc_size_t)
                      ;
typedef void ( *png_free_ptr) (png_structp, png_voidp);
# 901 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern png_uint_32 ( png_access_version_number) (void);




extern void ( png_set_sig_bytes) (png_structrp png_ptr, int num_bytes);






extern int ( png_sig_cmp) (png_const_bytep sig, size_t start, size_t num_to_check)
                         ;







extern png_structp ( png_create_read_struct) (png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn)


                  ;


extern png_structp ( png_create_write_struct) (png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn)


                  ;

extern size_t ( png_get_compression_buffer_size) (png_const_structrp png_ptr)
                                 ;

extern void ( png_set_compression_buffer_size) (png_structrp png_ptr, size_t size)
                 ;
# 963 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern void ( png_longjmp) (png_const_structrp png_ptr, int val)
                 ;



extern int ( png_reset_zstream) (png_structrp png_ptr);
# 986 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern void ( png_write_sig) (png_structrp png_ptr);


extern void ( png_write_chunk) (png_structrp png_ptr, png_const_bytep chunk_name, png_const_bytep data, size_t length)
                                                     ;


extern void ( png_write_chunk_start) (png_structrp png_ptr, png_const_bytep chunk_name, png_uint_32 length)
                                                    ;


extern void ( png_write_chunk_data) (png_structrp png_ptr, png_const_bytep data, size_t length)
                                         ;


extern void ( png_write_chunk_end) (png_structrp png_ptr);


extern png_infop ( png_create_info_struct) (png_const_structrp png_ptr)
                  ;





extern void ( png_info_init_3) (png_infopp info_ptr, size_t png_info_struct_size)
                                                 ;


extern void ( png_write_info_before_PLTE) (png_structrp png_ptr, png_const_inforp info_ptr)
                                                      ;
extern void ( png_write_info) (png_structrp png_ptr, png_const_inforp info_ptr)
                                                      ;



extern void ( png_read_info) (png_structrp png_ptr, png_inforp info_ptr)
                                                ;
# 1285 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern int ( png_set_interlace_handling) (png_structrp png_ptr);
# 1358 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern void ( png_set_flush) (png_structrp png_ptr, int nrows);

extern void ( png_write_flush) (png_structrp png_ptr);



extern void ( png_start_read_image) (png_structrp png_ptr);


extern void ( png_read_update_info) (png_structrp png_ptr, png_inforp info_ptr)
                         ;



extern void ( png_read_rows) (png_structrp png_ptr, png_bytepp row, png_bytepp display_row, png_uint_32 num_rows)
                                                  ;




extern void ( png_read_row) (png_structrp png_ptr, png_bytep row, png_bytep display_row)
                           ;




extern void ( png_read_image) (png_structrp png_ptr, png_bytepp image);



extern void ( png_write_row) (png_structrp png_ptr, png_const_bytep row)
                         ;






extern void ( png_write_rows) (png_structrp png_ptr, png_bytepp row, png_uint_32 num_rows)
                          ;


extern void ( png_write_image) (png_structrp png_ptr, png_bytepp image);


extern void ( png_write_end) (png_structrp png_ptr, png_inforp info_ptr)
                         ;



extern void ( png_read_end) (png_structrp png_ptr, png_inforp info_ptr);



extern void ( png_destroy_info_struct) (png_const_structrp png_ptr, png_infopp info_ptr_ptr)
                             ;


extern void ( png_destroy_read_struct) (png_structpp png_ptr_ptr, png_infopp info_ptr_ptr, png_infopp end_info_ptr_ptr)
                                                          ;


extern void ( png_destroy_write_struct) (png_structpp png_ptr_ptr, png_infopp info_ptr_ptr)
                             ;


extern void ( png_set_crc_action) (png_structrp png_ptr, int crit_action, int ancil_action)
                      ;
# 1455 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern void ( png_set_filter) (png_structrp png_ptr, int method, int filters)
                 ;
# 1508 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern void ( png_set_compression_level) (png_structrp png_ptr, int level)
               ;

extern void ( png_set_compression_mem_level) (png_structrp png_ptr, int mem_level)
                   ;

extern void ( png_set_compression_strategy) (png_structrp png_ptr, int strategy)
                  ;




extern void ( png_set_compression_window_bits) (png_structrp png_ptr, int window_bits)
                     ;

extern void ( png_set_compression_method) (png_structrp png_ptr, int method)
                ;
# 1560 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern void ( png_init_io) (png_structrp png_ptr, png_FILE_p fp);
# 1571 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern void ( png_set_error_fn) (png_structrp png_ptr, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warning_fn)
                                                                           ;


extern png_voidp ( png_get_error_ptr) (png_const_structrp png_ptr);
# 1587 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern void ( png_set_write_fn) (png_structrp png_ptr, png_voidp io_ptr, png_rw_ptr write_data_fn, png_flush_ptr output_flush_fn)
                                                             ;


extern void ( png_set_read_fn) (png_structrp png_ptr, png_voidp io_ptr, png_rw_ptr read_data_fn)
                             ;


extern png_voidp ( png_get_io_ptr) (png_const_structrp png_ptr);

extern void ( png_set_read_status_fn) (png_structrp png_ptr, png_read_status_ptr read_row_fn)
                                     ;

extern void ( png_set_write_status_fn) (png_structrp png_ptr, png_write_status_ptr write_row_fn)
                                       ;
# 1716 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern png_voidp ( png_malloc) (png_const_structrp png_ptr, png_alloc_size_t size)
                                          ;

extern png_voidp ( png_calloc) (png_const_structrp png_ptr, png_alloc_size_t size)
                                          ;


extern png_voidp ( png_malloc_warn) (png_const_structrp png_ptr, png_alloc_size_t size)
                                          ;


extern void ( png_free) (png_const_structrp png_ptr, png_voidp ptr);


extern void ( png_free_data) (png_const_structrp png_ptr, png_inforp info_ptr, png_uint_32 free_me, int num)
                                                       ;
# 1740 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern void ( png_data_freer) (png_const_structrp png_ptr, png_inforp info_ptr, int freer, png_uint_32 mask)
                                                      ;
# 1774 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern void ( png_error) (png_const_structrp png_ptr, png_const_charp error_message)
                                                 ;


extern void ( png_chunk_error) (png_const_structrp png_ptr, png_const_charp error_message)
                                                 ;
# 1790 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern void ( png_warning) (png_const_structrp png_ptr, png_const_charp warning_message)
                                     ;


extern void ( png_chunk_warning) (png_const_structrp png_ptr, png_const_charp warning_message)
                                     ;
# 1804 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern void ( png_benign_error) (png_const_structrp png_ptr, png_const_charp warning_message)
                                     ;



extern void ( png_chunk_benign_error) (png_const_structrp png_ptr, png_const_charp warning_message)
                                     ;


extern void ( png_set_benign_errors) (png_structrp png_ptr, int allowed)
                                        ;
# 1838 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern png_uint_32 ( png_get_valid) (png_const_structrp png_ptr, png_const_inforp info_ptr, png_uint_32 flag)
                                                 ;


extern size_t ( png_get_rowbytes) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                               ;





extern png_bytepp ( png_get_rows) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                               ;




extern void ( png_set_rows) (png_const_structrp png_ptr, png_inforp info_ptr, png_bytepp row_pointers)
                                                  ;



extern png_byte ( png_get_channels) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                               ;



extern png_uint_32 ( png_get_image_width) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                               ;


extern png_uint_32 ( png_get_image_height) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                               ;


extern png_byte ( png_get_bit_depth) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                               ;


extern png_byte ( png_get_color_type) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                               ;


extern png_byte ( png_get_filter_type) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                               ;


extern png_byte ( png_get_interlace_type) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                               ;


extern png_byte ( png_get_compression_type) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                               ;


extern png_uint_32 ( png_get_pixels_per_meter) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                                                            ;
extern png_uint_32 ( png_get_x_pixels_per_meter) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                                                            ;
extern png_uint_32 ( png_get_y_pixels_per_meter) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                                                            ;




extern png_fixed_point ( png_get_pixel_aspect_ratio_fixed) (png_const_structrp png_ptr, png_const_inforp info_ptr);



extern png_int_32 ( png_get_x_offset_pixels) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                                                            ;
extern png_int_32 ( png_get_y_offset_pixels) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                                                            ;
extern png_int_32 ( png_get_x_offset_microns) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                                                            ;
extern png_int_32 ( png_get_y_offset_microns) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                                                            ;





extern png_const_bytep ( png_get_signature) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                               ;



extern png_uint_32 ( png_get_bKGD) (png_const_structrp png_ptr, png_inforp info_ptr, png_color_16p *background)
                                                    ;



extern void ( png_set_bKGD) (png_const_structrp png_ptr, png_inforp info_ptr, png_const_color_16p background)
                                                         ;
# 2009 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern png_uint_32 ( png_get_hIST) (png_const_structrp png_ptr, png_inforp info_ptr, png_uint_16p *hist)
                                             ;
extern void ( png_set_hIST) (png_const_structrp png_ptr, png_inforp info_ptr, png_const_uint_16p hist)
                                                  ;


extern png_uint_32 ( png_get_IHDR) (png_const_structrp png_ptr, png_const_inforp info_ptr, png_uint_32 *width, png_uint_32 *height, int *bit_depth, int *color_type, int *interlace_method, int *compression_method, int *filter_method)


                                                 ;

extern void ( png_set_IHDR) (png_const_structrp png_ptr, png_inforp info_ptr, png_uint_32 width, png_uint_32 height, int bit_depth, int color_type, int interlace_method, int compression_method, int filter_method)


                       ;
# 2061 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern png_uint_32 ( png_get_PLTE) (png_const_structrp png_ptr, png_inforp info_ptr, png_colorp *palette, int *num_palette)
                                                               ;

extern void ( png_set_PLTE) (png_structrp png_ptr, png_inforp info_ptr, png_const_colorp palette, int num_palette)
                                                                    ;


extern png_uint_32 ( png_get_sBIT) (png_const_structrp png_ptr, png_inforp info_ptr, png_color_8p *sig_bit)
                                                ;



extern void ( png_set_sBIT) (png_const_structrp png_ptr, png_inforp info_ptr, png_const_color_8p sig_bit)
                                                     ;
# 2140 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern png_uint_32 ( png_get_tRNS) (png_const_structrp png_ptr, png_inforp info_ptr, png_bytep *trans_alpha, int *num_trans, png_color_16p *trans_color)

                                ;



extern void ( png_set_tRNS) (png_structrp png_ptr, png_inforp info_ptr, png_const_bytep trans_alpha, int num_trans, png_const_color_16p trans_color)

                                     ;
# 2279 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern void ( png_set_keep_unknown_chunks) (png_structrp png_ptr, int keep, png_const_bytep chunk_list, int num_chunks)
                                                          ;






extern int ( png_handle_as_unknown) (png_const_structrp png_ptr, png_const_bytep chunk_name)
                                ;



extern void ( png_set_unknown_chunks) (png_const_structrp png_ptr, png_inforp info_ptr, png_const_unknown_chunkp unknowns, int num_unknowns)

                      ;
# 2304 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern void ( png_set_unknown_chunk_location) (png_const_structrp png_ptr, png_inforp info_ptr, int chunk, int location)
                                                                               ;

extern int ( png_get_unknown_chunks) (png_const_structrp png_ptr, png_inforp info_ptr, png_unknown_chunkpp entries)
                                                      ;






extern void ( png_set_invalid) (png_const_structrp png_ptr, png_inforp info_ptr, int mask)
                                   ;




extern void ( png_read_png) (png_structrp png_ptr, png_inforp info_ptr, int transforms, png_voidp params)
                                      ;


extern void ( png_write_png) (png_structrp png_ptr, png_inforp info_ptr, int transforms, png_voidp params)
                                      ;



extern png_const_charp ( png_get_copyright) (png_const_structrp png_ptr)
                                 ;
extern png_const_charp ( png_get_header_ver) (png_const_structrp png_ptr)
                                 ;
extern png_const_charp ( png_get_header_version) (png_const_structrp png_ptr)
                                 ;
extern png_const_charp ( png_get_libpng_ver) (png_const_structrp png_ptr)
                                 ;
# 2361 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern void ( png_set_user_limits) (png_structrp png_ptr, png_uint_32 user_width_max, png_uint_32 user_height_max)
                                                             ;
extern png_uint_32 ( png_get_user_width_max) (png_const_structrp png_ptr)
                                 ;
extern png_uint_32 ( png_get_user_height_max) (png_const_structrp png_ptr)
                                 ;

extern void ( png_set_chunk_cache_max) (png_structrp png_ptr, png_uint_32 user_chunk_cache_max)
                                      ;
extern png_uint_32 ( png_get_chunk_cache_max) (png_const_structrp png_ptr)
                                 ;

extern void ( png_set_chunk_malloc_max) (png_structrp png_ptr, png_alloc_size_t user_chunk_cache_max)
                                           ;
extern png_alloc_size_t ( png_get_chunk_malloc_max) (png_const_structrp png_ptr)
                                 ;
# 2412 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern png_uint_32 ( png_get_io_state) (png_const_structrp png_ptr);





extern png_uint_32 ( png_get_io_chunk_type) (png_const_structrp png_ptr)
                                 ;
# 2544 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern png_uint_32 ( png_get_uint_32) (png_const_bytep buf);
extern png_uint_16 ( png_get_uint_16) (png_const_bytep buf);
extern png_int_32 ( png_get_int_32) (png_const_bytep buf);


extern png_uint_32 ( png_get_uint_31) (png_const_structrp png_ptr, png_const_bytep buf)
                         ;




extern void ( png_save_uint_32) (png_bytep buf, png_uint_32 i);


extern void ( png_save_int_32) (png_bytep buf, png_int_32 i);







extern void ( png_save_uint_16) (png_bytep buf, unsigned int i);
# 2612 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern void ( png_set_check_for_invalid_index) (png_structrp png_ptr, int allowed)
                                        ;

extern int ( png_get_palette_max) (png_const_structp png_ptr, png_const_infop info_ptr)
                              ;
# 32 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../src/pngxtern/pngxutil.h" 1
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../src/pngxtern/pngxutil.h"
void pngx_set_compression_type
   (png_structp png_ptr, png_infop info_ptr, int compression_type);
void pngx_set_filter_type
   (png_structp png_ptr, png_infop info_ptr, int filter_type);
void pngx_set_interlace_type
   (png_structp png_ptr, png_infop info_ptr, int interlace_type);



typedef png_alloc_size_t pngx_alloc_size_t;
# 43 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../src/pngxtern/pngxutil.h"
png_bytepp pngx_malloc_rows
   (png_structp png_ptr, png_infop info_ptr, int filler);
png_bytepp pngx_malloc_rows_extended
   (png_structp png_ptr, png_infop info_ptr,
    pngx_alloc_size_t min_row_size, int filler);
# 33 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h" 1
# 56 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zconf.h" 1
# 254 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zconf.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 255 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zconf.h" 2
     typedef size_t z_size_t;
# 401 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zconf.h"
typedef unsigned char Byte;

typedef unsigned int uInt;
typedef unsigned long uLong;





   typedef Byte Bytef;

typedef char charf;
typedef int intf;
typedef uInt uIntf;
typedef uLong uLongf;


   typedef void const *voidpc;
   typedef void *voidpf;
   typedef void *voidp;







# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 1
# 429 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zconf.h" 2
# 439 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zconf.h"
   typedef unsigned z_crc_t;
# 454 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zconf.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/types.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/types.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/types.h" 2
# 455 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zconf.h" 2





# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdarg.h" 1
# 461 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zconf.h" 2
# 492 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zconf.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/unistd.h" 1
# 493 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zconf.h" 2
# 57 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h" 2
# 103 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
typedef voidpf (*alloc_func)(voidpf opaque, uInt items, uInt size);
typedef void (*free_func)(voidpf opaque, voidpf address);

struct internal_state;

typedef struct z_stream_s {
    Bytef *next_in;
    uInt avail_in;
    uLong total_in;

    Bytef *next_out;
    uInt avail_out;
    uLong total_out;

    char *msg;
    struct internal_state *state;

    alloc_func zalloc;
    free_func zfree;
    voidpf opaque;

    int data_type;

    uLong adler;
    uLong reserved;
} z_stream;

typedef z_stream *z_streamp;





typedef struct gz_header_s {
    int text;
    uLong time;
    int xflags;
    int os;
    Bytef *extra;
    uInt extra_len;
    uInt extra_max;
    Bytef *name;
    uInt name_max;
    Bytef *comment;
    uInt comm_max;
    int hcrc;
    int done;

} gz_header;

typedef gz_header *gz_headerp;
# 242 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern const char * zlibVersion(void);
# 272 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int deflate(z_streamp strm, int flush);
# 385 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int deflateEnd(z_streamp strm);
# 423 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int inflate(z_streamp strm, int flush);
# 543 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int inflateEnd(z_streamp strm);
# 633 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int deflateSetDictionary(z_streamp strm,
                                         const Bytef *dictionary,
                                         uInt dictLength);
# 677 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int deflateGetDictionary(z_streamp strm,
                                         Bytef *dictionary,
                                         uInt *dictLength);
# 699 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int deflateCopy(z_streamp dest,
                                z_streamp source);
# 717 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int deflateReset(z_streamp strm);
# 728 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int deflateParams(z_streamp strm,
                                  int level,
                                  int strategy);
# 766 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int deflateTune(z_streamp strm,
                                int good_length,
                                int max_lazy,
                                int nice_length,
                                int max_chain);
# 783 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern uLong deflateBound(z_streamp strm,
                                   uLong sourceLen);
# 798 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int deflatePending(z_streamp strm,
                                   unsigned *pending,
                                   int *bits);
# 813 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int deflatePrime(z_streamp strm,
                                 int bits,
                                 int value);
# 830 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int deflateSetHeader(z_streamp strm,
                                     gz_headerp head);
# 910 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int inflateSetDictionary(z_streamp strm,
                                         const Bytef *dictionary,
                                         uInt dictLength);
# 933 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int inflateGetDictionary(z_streamp strm,
                                         Bytef *dictionary,
                                         uInt *dictLength);
# 948 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int inflateSync(z_streamp strm);
# 967 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int inflateCopy(z_streamp dest,
                                z_streamp source);
# 983 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int inflateReset(z_streamp strm);
# 994 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int inflateReset2(z_streamp strm,
                                  int windowBits);
# 1008 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int inflatePrime(z_streamp strm,
                                 int bits,
                                 int value);
# 1029 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern long inflateMark(z_streamp strm);
# 1057 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int inflateGetHeader(z_streamp strm,
                                     gz_headerp head);
# 1119 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
typedef unsigned (*in_func)(void *,
                            unsigned char * *);
typedef int (*out_func)(void *, unsigned char *, unsigned);

extern int inflateBack(z_streamp strm,
                                in_func in, void *in_desc,
                                out_func out, void *out_desc);
# 1193 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int inflateBackEnd(z_streamp strm);







extern uLong zlibCompileFlags(void);
# 1254 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int compress(Bytef *dest, uLongf *destLen,
                             const Bytef *source, uLong sourceLen);
# 1269 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int compress2(Bytef *dest, uLongf *destLen,
                              const Bytef *source, uLong sourceLen,
                              int level);
# 1285 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern uLong compressBound(uLong sourceLen);






extern int uncompress(Bytef *dest, uLongf *destLen,
                               const Bytef *source, uLong sourceLen);
# 1310 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int uncompress2(Bytef *dest, uLongf *destLen,
                                const Bytef *source, uLong *sourceLen);
# 1327 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
typedef struct gzFile_s *gzFile;
# 1367 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern gzFile gzdopen(int fd, const char *mode);
# 1390 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int gzbuffer(gzFile file, unsigned size);
# 1406 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int gzsetparams(gzFile file, int level, int strategy);
# 1417 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int gzread(gzFile file, voidp buf, unsigned len);
# 1447 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern z_size_t gzfread(voidp buf, z_size_t size, z_size_t nitems,
                                 gzFile file);
# 1473 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int gzwrite(gzFile file, voidpc buf, unsigned len);





extern z_size_t gzfwrite(voidpc buf, z_size_t size,
                                  z_size_t nitems, gzFile file);
# 1493 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int gzprintf(gzFile file, const char *format, ...);
# 1508 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int gzputs(gzFile file, const char *s);







extern char * gzgets(gzFile file, char *buf, int len);
# 1530 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int gzputc(gzFile file, int c);





extern int gzgetc(gzFile file);
# 1545 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int gzungetc(int c, gzFile file);
# 1557 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int gzflush(gzFile file, int flush);
# 1592 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int gzrewind(gzFile file);
# 1620 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int gzeof(gzFile file);
# 1635 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int gzdirect(gzFile file);
# 1656 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int gzclose(gzFile file);
# 1669 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int gzclose_r(gzFile file);
extern int gzclose_w(gzFile file);
# 1681 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern const char * gzerror(gzFile file, int *errnum);
# 1697 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern void gzclearerr(gzFile file);
# 1714 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern uLong adler32(uLong adler, const Bytef *buf, uInt len);
# 1734 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern uLong adler32_z(uLong adler, const Bytef *buf,
                                z_size_t len);
# 1752 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern uLong crc32(uLong crc, const Bytef *buf, uInt len);
# 1770 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern uLong crc32_z(uLong crc, const Bytef *buf,
                              z_size_t len);
# 1793 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern uLong crc32_combine_op(uLong crc1, uLong crc2, uLong op);
# 1806 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int deflateInit_(z_streamp strm, int level,
                                 const char *version, int stream_size);
extern int inflateInit_(z_streamp strm,
                                 const char *version, int stream_size);
extern int deflateInit2_(z_streamp strm, int level, int method,
                                  int windowBits, int memLevel,
                                  int strategy, const char *version,
                                  int stream_size);
extern int inflateInit2_(z_streamp strm, int windowBits,
                                  const char *version, int stream_size);
extern int inflateBackInit_(z_streamp strm, int windowBits,
                                     unsigned char *window,
                                     const char *version,
                                     int stream_size);
# 1859 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
struct gzFile_s {
    unsigned have;
    unsigned char *next;
    off_t pos;
};
extern int gzgetc_(gzFile file);
# 1918 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
   extern gzFile gzopen(const char *, const char *);
   extern off_t gzseek(gzFile, off_t, int);
   extern off_t gztell(gzFile);
   extern off_t gzoffset(gzFile);
   extern uLong adler32_combine(uLong, uLong, off_t);
   extern uLong crc32_combine(uLong, uLong, off_t);
   extern uLong crc32_combine_gen(off_t);
# 1936 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern const char * zError(int);
extern int inflateSyncPoint(z_streamp);
extern const z_crc_t * get_crc_table(void);
extern int inflateUndermine(z_streamp, int);
extern int inflateValidate(z_streamp, int);
extern unsigned long inflateCodesUsed(z_streamp);
extern int inflateResetKeep(z_streamp);
extern int deflateResetKeep(z_streamp);






extern int gzvprintf(gzFile file,
                                           const char *format,
                                           va_list va);
# 34 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.c" 2




static const char *msg_intro =
    "OptiPNG" " version " "0.7.8" "\n"
    "Copyright (C) 2001-2023 Cosmin Truta and the Contributing Authors" ".\n";

static const char *msg_license =
    "This program is open-source software. See LICENSE for more details.\n"
    "\n"
    "Portions of this software are based in part on the work of:\n"
    "  Jean-loup Gailly and Mark Adler (zlib)\n"
    "  Glenn Randers-Pehrson and the PNG Development Group (libpng)\n"
    "  Miyasaka Masaru (BMP support)\n"
    "  David Koblas (GIF support)\n";

static const char *msg_help_synopsis =
    "Synopsis:\n"
    "    optipng [options] files ...\n"
    "Files:\n"
    "    Image files of type: PNG, BMP, GIF, PNM or TIFF\n";

static const char *msg_help_basic_options =
    "Basic options:\n"
    "    -?, -h, -help\tshow the extended help\n"
    "    -o <level>\t\toptimization level (0-7)\t\t[default: 2]\n"
    "    -v\t\t\trun in verbose mode / show copyright and version info\n";

static const char *msg_help_options =
    "Basic options:\n"
    "    -?, -h, -help\tshow this help\n"
    "    -o <level>\t\toptimization level (0-7)\t\t[default: 2]\n"
    "    -v\t\t\trun in verbose mode / show copyright and version info\n"
    "General options:\n"
    "    -backup, -keep\tkeep a backup of the modified files\n"
    "    -clobber\t\toverwrite existing files\n"



    "    -fix\t\tenable error recovery\n"
    "    -force\t\tenforce writing of a new output file\n"
    "    -preserve\t\tpreserve file attributes if possible\n"
    "    -quiet, -silent\trun in quiet mode\n"
    "    -simulate\t\trun in simulation mode\n"
    "    -out <file>\t\twrite output file to <file>\n"
    "    -dir <directory>\twrite output file(s) to <directory>\n"
    "    -log <file>\t\tlog messages to <file>\n"
    "    --\t\t\tstop option switch parsing\n"
    "Optimization options:\n"
    "    -f <filters>\tPNG delta filters (0-5)\t\t\t[default: 0,5]\n"
    "    -i <type>\t\tPNG interlace type (0-1)\n"
    "    -zc <levels>\tzlib compression levels (1-9)\t\t[default: 9]\n"
    "    -zm <levels>\tzlib memory levels (1-9)\t\t[default: 8]\n"
    "    -zs <strategies>\tzlib compression strategies (0-3)\t[default: 0-3]\n"
    "    -zw <size>\t\tzlib window size (256,512,1k,2k,4k,8k,16k,32k)\n"
    "    -full\t\tproduce a full report on IDAT (might reduce speed)\n"
    "    -nb\t\t\tno bit depth reduction\n"
    "    -nc\t\t\tno color type reduction\n"
    "    -np\t\t\tno palette reduction\n"
    "    -nx\t\t\tno reductions\n"
    "    -nz\t\t\tno IDAT recoding\n"
    "Editing options:\n"
    "    -snip\t\tcut one image out of multi-image or animation files\n"
    "    -strip <objects>\tstrip metadata objects (e.g. \"all\")\n"
    "Optimization levels:\n"
    "    -o0\t\t<=>\t-o1 -nx -nz\t\t\t\t(0 or 1 trials)\n"
    "    -o1\t\t<=>\t-zc9 -zm8 -zs0 -f0\t\t\t(1 trial)\n"
    "    \t\t(or...)\t-zc9 -zm8 -zs1 -f5\t\t\t(1 trial)\n"
    "    -o2\t\t<=>\t-zc9 -zm8 -zs0-3 -f0,5\t\t\t(8 trials)\n"
    "    -o3\t\t<=>\t-zc9 -zm8-9 -zs0-3 -f0,5\t\t(16 trials)\n"
    "    -o4\t\t<=>\t-zc9 -zm8 -zs0-3 -f0-5\t\t\t(24 trials)\n"
    "    -o5\t\t<=>\t-zc9 -zm8-9 -zs0-3 -f0-5\t\t(48 trials)\n"
    "    -o6\t\t<=>\t-zc1-9 -zm8 -zs0-3 -f0-5\t\t(120 trials)\n"
    "    -o7\t\t<=>\t-zc1-9 -zm8-9 -zs0-3 -f0-5\t\t(240 trials)\n"
    "    -o7 -zm1-9\t<=>\t-zc1-9 -zm1-9 -zs0-3 -f0-5\t\t(1080 trials)\n"
    "Notes:\n"
    "    The combination for -o1 is chosen heuristically.\n"
    "    Exhaustive combinations such as \"-o7 -zm1-9\" are not generally recommended.\n";

static const char *msg_help_examples =
    "Examples:\n"
    "    optipng file.png\t\t\t\t\t\t(default speed)\n"
    "    optipng -o5 file.png\t\t\t\t\t(slow)\n"
    "    optipng -o7 file.png\t\t\t\t\t(very slow)\n";

static const char *msg_help_more =
    "Type \"optipng -h\" for extended help.\n";


static enum
{
    OP_RUN,
    OP_SHOW_HELP,
    OP_SHOW_VERSION
} operation;

static struct
{
    int help;
    int version;
} local_options;

static struct opng_options options;

static FILE *con_file;
static FILE *log_file;

static int start_of_line;





static void
error(const char *fmt, ...)
{
    va_list arg_ptr;


    fprintf(stderr, "** Error: ");
    __builtin_va_start((arg_ptr));
    vfprintf(stderr, fmt, arg_ptr);
    ;
    fprintf(stderr, "\n");
    exit(1);
}




static void
panic(const char *msg)
{

    fprintf(stderr, "\n** INTERNAL ERROR: %s\n", msg);
    fprintf(stderr, "Please submit a defect report.\n" "http://optipng.sourceforge.net/" "\n\n");
    fflush(stderr);
    if (options.debug)
    {

        abort();
    }
    else
    {

        fprintf(stderr,
            "The execution of this program has been terminated abnormally.\n");
        exit(70);
    }
}




static int
opng_strcasecmp(const char *str1, const char *str2)
{
    int ch1, ch2;


    for ( ; ; )
    {
        ch1 = tolower(*str1++);
        ch2 = tolower(*str2++);
        if (ch1 != ch2)
            return ch1 - ch2;
        if (ch1 == '\0')
            return 0;
    }

}




static char *
opng_strltrim(const char *str)
{

    while (isspace(*str))
        ++str;
    return (char *)str;
}




static char *
opng_strtail(const char *str, size_t num)
{
    size_t len;


    len = strlen(str);
    if (len <= num)
        return (char *)str;
    return (char *)str + len - num;
}




static char *
opng_strpbrk_digit(const char *str)
{
    for ( ; ; )
    {
        if (*str == '\0')
            return 0;
        if (isdigit(*str))
            return (char *)str;
        ++str;
    }
}




static int
opng_str2ulong(unsigned long *out_val, const char *in_str,
               int allow_multiplier)
{
    const char *begin_ptr;
    char *end_ptr;
    unsigned long multiplier;



    begin_ptr = end_ptr = opng_strltrim(in_str);
    if (*begin_ptr >= '0' && *begin_ptr <= '9')
        *out_val = strtoul(begin_ptr, &end_ptr, 10);
    if (begin_ptr == end_ptr)
    {
        errno = EINVAL;
        *out_val = 0;
        return -1;
    }

    if (allow_multiplier)
    {





        if (*end_ptr == 'k' || *end_ptr == 'K')
        {
            ++end_ptr;
            multiplier = 1024UL;
        }
        else if (*end_ptr == 'M')
        {
            ++end_ptr;
            multiplier = 1024UL * 1024UL;
        }
        else if (*end_ptr == 'G')
        {
            ++end_ptr;
            multiplier = 1024UL * 1024UL * 1024UL;
        }
        else
            multiplier = 1;
        if (multiplier > 1)
        {
            if (*out_val > 18446744073709551615UL / multiplier)
            {
                errno = ERANGE;
                *out_val = 18446744073709551615UL;
            }
            else
                *out_val *= multiplier;
        }
    }


    if (*opng_strltrim(end_ptr) != '\0')
    {
        errno = EINVAL;
        return -1;
    }
    return 0;
}




static void
err_option_arg(const char *opt, const char *opt_arg)
{

    if (opt_arg == 0 || *opng_strltrim(opt_arg) == '\0')
        error("Missing argument for option %s", opt);
    else
        error("Invalid argument for option %s: %s", opt, opt_arg);
}




static int
check_num_option(const char *opt, const char *opt_arg,
                 int lowest, int highest)
{
    unsigned long value;


    if (opng_str2ulong(&value, opt_arg, 0) != 0 ||
        value > 2147483647 || (int)value < lowest || (int)value > highest)
        err_option_arg(opt, opt_arg);
    return (int)value;
}




static int
check_power2_option(const char *opt, const char *opt_arg,
                    int lowest, int highest)
{
    unsigned long value;
    int result;



    if (opng_str2ulong(&value, opt_arg, 1) == 0)
    {
        if (lowest < 0)
            lowest = 0;
        if (highest > (int)(8 * sizeof(long) - 2))
            highest = (int)(8 * sizeof(long) - 2);
        for (result = lowest; result <= highest; ++result)
        {
            if ((1UL << result) == value)
                return result;
        }
    }
    err_option_arg(opt, opt_arg);
    return -1;
}




static opng_bitset_t
check_rangeset_option(const char *opt, const char *opt_arg,
                      opng_bitset_t result_mask)
{
    opng_bitset_t result;




    if (opng_strparse_rangeset_to_bitset(&result, opt_arg, result_mask) != 0)
        result = 0U;
    if ((result & result_mask) != result)
        result = 0U;
    if (result == 0U)
        err_option_arg(opt, opt_arg);
    return result;
}




static void
check_obj_option(const char *opt, const char *opt_arg)
{
    unsigned int i;

    if (strcmp("all", opt_arg) == 0)
        return;



    for (i = 0; i < 4; ++i)
    {

        if (!((opt_arg[i] >= 'A' && opt_arg[i] <= 'Z') ||
              (opt_arg[i] >= 'a' && opt_arg[i] <= 'z')))
            break;
    }
    if (i == 4 && opt_arg[i] == '\0')
        error("Manipulation of individual chunks is not implemented");
    else
        err_option_arg(opt, opt_arg);
}




static int
scan_option(const char *str,
            char opt_buf[], size_t opt_buf_size, const char **opt_arg_ptr)
{
    const char *ptr;
    unsigned int opt_len;


    if (str[0] != '-' || str[1] == '\0')
        return 0;


    opt_len = 0;
    ptr = str + 1;
    while (*ptr == '-')
        ++ptr;
    if (*ptr == '\0')
        --ptr;
    for ( ; ; )
    {
        if (opt_len < opt_buf_size)
            opt_buf[opt_len] = (char)tolower(*ptr);
        ++opt_len;
        ++ptr;
        if (*ptr == '\0' || isspace(*ptr))
        {
            while (isspace(*ptr))
                ++ptr;
            *opt_arg_ptr = (*ptr != '\0') ? ptr : 0;
            break;
        }
        if (*ptr == '=')
        {
            ++ptr;
            *opt_arg_ptr = ptr;
            break;
        }
    }


    if (opt_buf_size > 0)
    {
        if (opt_len < opt_buf_size)
            opt_buf[opt_len] = '\0';
        else
            opt_buf[opt_buf_size - 1] = '\0';
    }
    return 1;
}




static void
parse_args(int argc, char *argv[])
{
    char *arg;
    char opt[16];
    size_t opt_len;
    const char *xopt;
    int simple_opt, stop_switch;
    opng_bitset_t set;
    int val;
    unsigned int file_count;
    int i;


    memset(&options, 0, sizeof(options));
    options.optim_level = -1;
    options.interlace = -1;
    file_count = 0;


    stop_switch = 0;
    for (i = 1; i < argc; ++i)
    {
        arg = argv[i];
        if (stop_switch || scan_option(arg, opt, sizeof(opt), &xopt) < 1)
        {
            ++file_count;
            continue;
        }
        opt_len = strlen(opt);


        argv[i] = 0;


        if ((strchr("fio", opt[0]) != 0 && isdigit(opt[1])) ||
            (opt[0] == 'z' && isalpha(opt[1]) && isdigit(opt[2])))
        {



            opt_len = (size_t)(opng_strpbrk_digit(opt) - opt);
            opt[opt_len] = '\0';
            xopt = opng_strpbrk_digit(arg);
        }


        simple_opt = 1;
        if (strcmp("-", opt) == 0)
        {

            stop_switch = 1;
        }
        else if (strcmp("?", opt) == 0 ||
                 strncmp("help", opt, opt_len) == 0)
        {

            local_options.help = 1;
        }
        else if ((strncmp("backup", opt, opt_len) == 0) ||
                 (strncmp("keep", opt, opt_len) == 0))
        {

            options.backup = 1;
        }
        else if (strncmp("clobber", opt, opt_len) == 0)
        {

            options.clobber = 1;
        }
        else if (strcmp("debug", opt) == 0)
        {


            options.debug = 1;
        }
        else if (strncmp("fix", opt, opt_len) == 0 && opt_len >= 2)
        {

            options.fix = 1;
        }
        else if (strncmp("force", opt, opt_len) == 0 && opt_len >= 2)
        {

            options.force = 1;
        }
        else if (strncmp("full", opt, opt_len) == 0 && opt_len >= 2)
        {

            options.full = 1;
        }
        else if (strcmp("nb", opt) == 0)
        {

            options.nb = 1;
        }
        else if (strcmp("nc", opt) == 0)
        {

            options.nc = 1;
        }
        else if (strcmp("np", opt) == 0)
        {

            options.np = 1;
        }
        else if (strcmp("nx", opt) == 0)
        {

            options.nb = options.nc = options.np = 1;

        }
        else if (strcmp("nz", opt) == 0)
        {

            options.nz = 1;
        }
        else if (strncmp("preserve", opt, opt_len) == 0)
        {

            options.preserve = 1;
        }
        else if ((strncmp("quiet", opt, opt_len) == 0) ||
                 (strncmp("silent", opt, opt_len) == 0 && opt_len >= 3))
        {

            options.quiet = 1;
        }
        else if (strncmp("simulate", opt, opt_len) == 0 && opt_len >= 3)
        {

            options.simulate = 1;
        }
        else if (strncmp("snip", opt, opt_len) == 0 && opt_len >= 2)
        {

            options.snip = 1;
        }
        else if (strcmp("v", opt) == 0)
        {

            options.verbose = 1;
            local_options.version = 1;
        }
        else if (strncmp("verbose", opt, opt_len) == 0 && opt_len >= 4)
        {

            options.verbose = 1;
        }
        else if (strncmp("version", opt, opt_len) == 0 && opt_len >= 4)
        {

            local_options.version = 1;
        }
        else
        {
            simple_opt = 0;
            if (xopt == 0)
            {
                if (++i < argc)
                {
                    xopt = argv[i];

                    argv[i] = 0;
                }
                else
                {

                    xopt = "";
                }
            }
        }


        if (simple_opt)
        {
            if (xopt != 0)
                error("No argument allowed for option: %s", arg);
        }
        else if (strcmp("o", opt) == 0)
        {

            val = check_num_option("-o", xopt, 0, 2147483647);
            if (options.optim_level < 0)
                options.optim_level = val;
            else if (options.optim_level != val)
                error("Multiple optimization levels are not permitted");
        }
        else if (strcmp("i", opt) == 0)
        {

            val = check_num_option("-i", xopt, 0, 1);
            if (options.interlace < 0)
                options.interlace = val;
            else if (options.interlace != val)
                error("Multiple interlace types are not permitted");
        }
        else if (strcmp("f", opt) == 0)
        {

            set = check_rangeset_option("-f", xopt, ((1 << (5+1)) - (1 << 0)));
            options.filter_set |= set;
        }
        else if (strcmp("zc", opt) == 0)
        {

            set = check_rangeset_option("-zc", xopt, ((1 << (9+1)) - (1 << 1)));
            options.compr_level_set |= set;
        }
        else if (strcmp("zm", opt) == 0)
        {

            set = check_rangeset_option("-zm", xopt, ((1 << (9+1)) - (1 << 1)));
            options.mem_level_set |= set;
        }
        else if (strcmp("zs", opt) == 0)
        {

            set = check_rangeset_option("-zs", xopt, ((1 << (3+1)) - (1 << 0)));
            options.strategy_set |= set;
        }
        else if (strcmp("zw", opt) == 0)
        {

            val = check_power2_option("-zw", xopt, 8, 15);
            if (options.window_bits == 0)
                options.window_bits = val;
            else if (options.window_bits != val)
                error("Multiple window sizes are not permitted");
        }
        else if (strncmp("strip", opt, opt_len) == 0 && opt_len >= 2)
        {

            check_obj_option("-strip", xopt);
            options.strip_all = 1;
        }
        else if (strncmp("out", opt, opt_len) == 0 && opt_len >= 2)
        {

            if (options.out_name != 0)
                error("Multiple output file names are not permitted");
            if (xopt[0] == '\0')
                err_option_arg("-out", 0);
            options.out_name = xopt;
        }
        else if (strncmp("dir", opt, opt_len) == 0)
        {

            if (options.dir_name != 0)
                error("Multiple output dir names are not permitted");
            if (xopt[0] == '\0')
                err_option_arg("-dir", 0);
            options.dir_name = xopt;
        }
        else if (strncmp("log", opt, opt_len) == 0)
        {

            if (options.log_name != 0)
                error("Multiple log file names are not permitted");
            if (xopt[0] == '\0')
                err_option_arg("-log", 0);
            options.log_name = xopt;
        }
        else
        {
            error("Unrecognized option: %s", arg);
        }
    }


    if (options.out_name != 0)
    {
        if (file_count > 1)
            error("The option -out requires one input file");
        if (options.dir_name != 0)
            error("The options -out and -dir are mutually exclusive");
    }
    if (options.log_name != 0)
    {
        if (opng_strcasecmp(".log", opng_strtail(options.log_name, 4)) != 0)
            error("To prevent accidental data corruption, "
                  "the log file name must end with \".log\"");
    }
    if (local_options.help)
        operation = OP_SHOW_HELP;
    else if (file_count != 0)
        operation = OP_RUN;
    else if (local_options.version)
        operation = OP_SHOW_VERSION;
    else
        operation = OP_SHOW_HELP;
}




static void
app_printf(const char *fmt, ...)
{
    va_list arg_ptr;

    if (fmt[0] == '\0')
        return;
    start_of_line = (fmt[strlen(fmt) - 1] == '\n') ? 1 : 0;

    if (con_file != 0)
    {
        __builtin_va_start((arg_ptr));
        vfprintf(con_file, fmt, arg_ptr);
        ;
    }
    if (log_file != 0)
    {
        __builtin_va_start((arg_ptr));
        vfprintf(log_file, fmt, arg_ptr);
        ;
    }
}




static void
app_print_cntrl(int cntrl_code)
{
    const char *con_str, *log_str;
    int i;

    if (cntrl_code == '\r')
    {

        con_str = "\r";
        log_str = "\n";
        start_of_line = 1;
    }
    else if (cntrl_code == '\v')
    {

        if (!start_of_line)
        {
            con_str = log_str = "\n";
            start_of_line = 1;
        }
        else
            con_str = log_str = "";
    }
    else if (cntrl_code < 0 && cntrl_code > -80 && start_of_line)
    {

        if (con_file != 0)
        {
            for (i = 0; i > cntrl_code; --i)
                fputc(' ', con_file);
        }
        con_str = "\r";
        log_str = "";
    }
    else
    {

        con_str = log_str = "<?>";
    }

    if (con_file != 0)
        fputs(con_str, con_file);
    if (log_file != 0)
        fputs(log_str, log_file);
}




static void
app_progress(unsigned long current_step, unsigned long total_steps)
{

    if (con_file != 0)
        fflush(con_file);




    if (current_step && total_steps)
        return;
}




static void
app_init(void)
{
    start_of_line = 1;

    if (operation == OP_SHOW_HELP || operation == OP_SHOW_VERSION)
        con_file = stdout;
    else if (!options.quiet)
        con_file = stderr;
    else
        con_file = 0;

    if (options.log_name != 0)
    {

        if ((log_file = fopen(options.log_name, "a")) == 0)
            error("Can't open log file: %s\n", options.log_name);
        setvbuf(log_file, 0, _IOLBF, 1024);
        app_printf("** Warning: %s\n\n",
                   "The option -log is deprecated; use shell redirection");
    }
}




static void
app_finish(void)
{
    if (log_file != 0)
    {

        fclose(log_file);
    }
}




static int
process_files(int argc, char *argv[])
{
    int result;
    struct opng_ui ui;
    int i;


    ui.printf_fn = app_printf;
    ui.print_cntrl_fn = app_print_cntrl;
    ui.progress_fn = app_progress;
    ui.panic_fn = panic;
    if (opng_initialize(&options, &ui) != 0)
        panic("Can't initialize optimization engine");


    result = 0;
    for (i = 1; i < argc; ++i)
    {
        if (argv[i] == 0 || argv[i][0] == '\0')
            continue;
        if (opng_optimize(argv[i]) != 0)
            result = 1;
    }


    if (opng_finalize() != 0)
        panic("Can't finalize optimization engine");

    return result;
}




int
main(int argc, char *argv[])
{
    int result;


    parse_args(argc, argv);
    app_init();
    result = 0;

    if (local_options.version)
    {

        app_printf("%s\n", msg_intro);
    }

    switch (operation)
    {
    case OP_RUN:

        result = process_files(argc, argv);
        break;
    case OP_SHOW_HELP:
        if (local_options.help)
        {

            app_printf("%s%s%s",
                       msg_help_synopsis,
                       msg_help_options,
                       msg_help_examples);
        }
        else
        {

            app_printf("%s%s%s%s",
                       msg_help_synopsis,
                       msg_help_basic_options,
                       msg_help_examples,
                       msg_help_more);
        }
        break;
    case OP_SHOW_VERSION:

        app_printf("%s\n", msg_license);
        app_printf("Using libpng version %s and zlib version %s\n",
                   png_get_libpng_ver(0), zlibVersion());
        break;
    default:
        result = -1;
    }


    app_finish();
    return result;
}
# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.c"
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.c"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.h" 1
# 14 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/bitset.h" 1
# 14 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/bitset.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1



typedef int START_DELIMETER;
typedef unsigned chtype;
typedef chtype attr_t;
typedef int socklen_t;
typedef int size_t;
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
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 2
# 15 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/bitset.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 16 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/bitset.h" 2
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/bitset.h"
typedef unsigned int opng_bitset_t;
# 45 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/bitset.h"
enum
{
    OPNG_BITSET_ELT_MIN = 0,
    OPNG_BITSET_ELT_MAX = (int)((sizeof(opng_bitset_t) * 8) - 1)
};
# 174 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/bitset.h"
unsigned int
opng_bitset_count(opng_bitset_t set);







int
opng_bitset_find_first(opng_bitset_t set);







int
opng_bitset_find_next(opng_bitset_t set, int elt);







int
opng_bitset_find_last(opng_bitset_t set);







int
opng_bitset_find_prev(opng_bitset_t set, int elt);
# 241 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/bitset.h"
int
opng_strparse_rangeset_to_bitset(opng_bitset_t *out_set,
                                 const char *rangeset_str,
                                 opng_bitset_t mask_set);
# 253 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/bitset.h"
size_t
opng_strformat_bitset_as_rangeset(char *out_buf,
                                  size_t out_buf_size,
                                  opng_bitset_t bitset);
# 15 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.h" 2
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.h"
struct opng_options
{

    int backup;
    int clobber;
    int debug;
    int fix;
    int force;
    int full;
    int preserve;
    int quiet;
    int simulate;
    int verbose;
    const char *out_name;
    const char *dir_name;
    const char *log_name;


    int interlace;
    int nb, nc, np, nz;
    int optim_level;
    opng_bitset_t compr_level_set;
    opng_bitset_t mem_level_set;
    opng_bitset_t strategy_set;
    opng_bitset_t filter_set;
    int window_bits;


    int snip;
    int strip_all;
};





struct opng_ui
{
    void (*printf_fn)(const char *fmt, ...);
    void (*print_cntrl_fn)(int cntrl_code);
    void (*progress_fn)(unsigned long current_step, unsigned long total_steps);
    void (*panic_fn)(const char *msg);
};





int opng_initialize(const struct opng_options *options,
                    const struct opng_ui *ui);




int opng_optimize(const char *infile_name);




int opng_finalize(void);
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/proginfo.h" 1
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/ctype.h" 1
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/errno.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdarg.h" 1
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h" 1
# 330 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/pnglibconf.h" 1
# 331 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h" 2




# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/pngconf.h" 1
# 31 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/pngconf.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 1
# 32 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/pngconf.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 33 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/pngconf.h" 2
# 46 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/pngconf.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 47 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/pngconf.h" 2
# 481 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/pngconf.h"
   typedef unsigned char png_byte;







   typedef short png_int_16;







   typedef unsigned short png_uint_16;





   typedef int png_int_32;







   typedef unsigned int png_uint_32;
# 523 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/pngconf.h"
typedef size_t png_size_t;
typedef ptrdiff_t png_ptrdiff_t;
# 557 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/pngconf.h"
   typedef size_t png_alloc_size_t;
# 574 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/pngconf.h"
typedef png_int_32 png_fixed_point;


typedef void * png_voidp;
typedef const void * png_const_voidp;
typedef png_byte * png_bytep;
typedef const png_byte * png_const_bytep;
typedef png_uint_32 * png_uint_32p;
typedef const png_uint_32 * png_const_uint_32p;
typedef png_int_32 * png_int_32p;
typedef const png_int_32 * png_const_int_32p;
typedef png_uint_16 * png_uint_16p;
typedef const png_uint_16 * png_const_uint_16p;
typedef png_int_16 * png_int_16p;
typedef const png_int_16 * png_const_int_16p;
typedef char * png_charp;
typedef const char * png_const_charp;
typedef png_fixed_point * png_fixed_point_p;
typedef const png_fixed_point * png_const_fixed_point_p;
typedef size_t * png_size_tp;
typedef const size_t * png_const_size_tp;


typedef FILE * png_FILE_p;
# 606 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/pngconf.h"
typedef png_byte * * png_bytepp;
typedef png_uint_32 * * png_uint_32pp;
typedef png_int_32 * * png_int_32pp;
typedef png_uint_16 * * png_uint_16pp;
typedef png_int_16 * * png_int_16pp;
typedef const char * * png_const_charpp;
typedef char * * png_charpp;
typedef png_fixed_point * * png_fixed_point_pp;





typedef char * * * png_charppp;
# 336 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h" 2
# 431 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
typedef char* png_libpng_version_1_6_40;







typedef struct png_struct_def png_struct;
typedef const png_struct * png_const_structp;
typedef png_struct * png_structp;
typedef png_struct * * png_structpp;
# 453 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
typedef struct png_info_def png_info;
typedef png_info * png_infop;
typedef const png_info * png_const_infop;
typedef png_info * * png_infopp;
# 469 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
typedef png_struct * png_structrp;
typedef const png_struct * png_const_structrp;
typedef png_info * png_inforp;
typedef const png_info * png_const_inforp;





typedef struct png_color_struct
{
   png_byte red;
   png_byte green;
   png_byte blue;
} png_color;
typedef png_color * png_colorp;
typedef const png_color * png_const_colorp;
typedef png_color * * png_colorpp;

typedef struct png_color_16_struct
{
   png_byte index;
   png_uint_16 red;
   png_uint_16 green;
   png_uint_16 blue;
   png_uint_16 gray;
} png_color_16;
typedef png_color_16 * png_color_16p;
typedef const png_color_16 * png_const_color_16p;
typedef png_color_16 * * png_color_16pp;

typedef struct png_color_8_struct
{
   png_byte red;
   png_byte green;
   png_byte blue;
   png_byte gray;
   png_byte alpha;
} png_color_8;
typedef png_color_8 * png_color_8p;
typedef const png_color_8 * png_const_color_8p;
typedef png_color_8 * * png_color_8pp;





typedef struct png_sPLT_entry_struct
{
   png_uint_16 red;
   png_uint_16 green;
   png_uint_16 blue;
   png_uint_16 alpha;
   png_uint_16 frequency;
} png_sPLT_entry;
typedef png_sPLT_entry * png_sPLT_entryp;
typedef const png_sPLT_entry * png_const_sPLT_entryp;
typedef png_sPLT_entry * * png_sPLT_entrypp;






typedef struct png_sPLT_struct
{
   png_charp name;
   png_byte depth;
   png_sPLT_entryp entries;
   png_int_32 nentries;
} png_sPLT_t;
typedef png_sPLT_t * png_sPLT_tp;
typedef const png_sPLT_t * png_const_sPLT_tp;
typedef png_sPLT_t * * png_sPLT_tpp;
# 600 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
typedef struct png_time_struct
{
   png_uint_16 year;
   png_byte month;
   png_byte day;
   png_byte hour;
   png_byte minute;
   png_byte second;
} png_time;
typedef png_time * png_timep;
typedef const png_time * png_const_timep;
typedef png_time * * png_timepp;
# 622 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
typedef struct png_unknown_chunk_t
{
   png_byte name[5];
   png_byte *data;
   size_t size;







   png_byte location;
}
png_unknown_chunk;

typedef png_unknown_chunk * png_unknown_chunkp;
typedef const png_unknown_chunk * png_const_unknown_chunkp;
typedef png_unknown_chunk * * png_unknown_chunkpp;
# 754 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
typedef struct png_row_info_struct
{
   png_uint_32 width;
   size_t rowbytes;
   png_byte color_type;
   png_byte bit_depth;
   png_byte channels;
   png_byte pixel_depth;
} png_row_info;

typedef png_row_info * png_row_infop;
typedef png_row_info * * png_row_infopp;
# 775 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
typedef void ( *png_error_ptr) (png_structp, png_const_charp);
typedef void ( *png_rw_ptr) (png_structp, png_bytep, size_t);
typedef void ( *png_flush_ptr) (png_structp);
typedef void ( *png_read_status_ptr) (png_structp, png_uint_32, int)
         ;
typedef void ( *png_write_status_ptr) (png_structp, png_uint_32, int)
         ;
# 867 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
typedef png_voidp ( *png_malloc_ptr) (png_structp, png_alloc_size_t)
                      ;
typedef void ( *png_free_ptr) (png_structp, png_voidp);
# 901 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern png_uint_32 ( png_access_version_number) (void);




extern void ( png_set_sig_bytes) (png_structrp png_ptr, int num_bytes);






extern int ( png_sig_cmp) (png_const_bytep sig, size_t start, size_t num_to_check)
                         ;







extern png_structp ( png_create_read_struct) (png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn)


                  ;


extern png_structp ( png_create_write_struct) (png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn)


                  ;

extern size_t ( png_get_compression_buffer_size) (png_const_structrp png_ptr)
                                 ;

extern void ( png_set_compression_buffer_size) (png_structrp png_ptr, size_t size)
                 ;
# 963 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern void ( png_longjmp) (png_const_structrp png_ptr, int val)
                 ;



extern int ( png_reset_zstream) (png_structrp png_ptr);
# 986 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern void ( png_write_sig) (png_structrp png_ptr);


extern void ( png_write_chunk) (png_structrp png_ptr, png_const_bytep chunk_name, png_const_bytep data, size_t length)
                                                     ;


extern void ( png_write_chunk_start) (png_structrp png_ptr, png_const_bytep chunk_name, png_uint_32 length)
                                                    ;


extern void ( png_write_chunk_data) (png_structrp png_ptr, png_const_bytep data, size_t length)
                                         ;


extern void ( png_write_chunk_end) (png_structrp png_ptr);


extern png_infop ( png_create_info_struct) (png_const_structrp png_ptr)
                  ;





extern void ( png_info_init_3) (png_infopp info_ptr, size_t png_info_struct_size)
                                                 ;


extern void ( png_write_info_before_PLTE) (png_structrp png_ptr, png_const_inforp info_ptr)
                                                      ;
extern void ( png_write_info) (png_structrp png_ptr, png_const_inforp info_ptr)
                                                      ;



extern void ( png_read_info) (png_structrp png_ptr, png_inforp info_ptr)
                                                ;
# 1285 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern int ( png_set_interlace_handling) (png_structrp png_ptr);
# 1358 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern void ( png_set_flush) (png_structrp png_ptr, int nrows);

extern void ( png_write_flush) (png_structrp png_ptr);



extern void ( png_start_read_image) (png_structrp png_ptr);


extern void ( png_read_update_info) (png_structrp png_ptr, png_inforp info_ptr)
                         ;



extern void ( png_read_rows) (png_structrp png_ptr, png_bytepp row, png_bytepp display_row, png_uint_32 num_rows)
                                                  ;




extern void ( png_read_row) (png_structrp png_ptr, png_bytep row, png_bytep display_row)
                           ;




extern void ( png_read_image) (png_structrp png_ptr, png_bytepp image);



extern void ( png_write_row) (png_structrp png_ptr, png_const_bytep row)
                         ;






extern void ( png_write_rows) (png_structrp png_ptr, png_bytepp row, png_uint_32 num_rows)
                          ;


extern void ( png_write_image) (png_structrp png_ptr, png_bytepp image);


extern void ( png_write_end) (png_structrp png_ptr, png_inforp info_ptr)
                         ;



extern void ( png_read_end) (png_structrp png_ptr, png_inforp info_ptr);



extern void ( png_destroy_info_struct) (png_const_structrp png_ptr, png_infopp info_ptr_ptr)
                             ;


extern void ( png_destroy_read_struct) (png_structpp png_ptr_ptr, png_infopp info_ptr_ptr, png_infopp end_info_ptr_ptr)
                                                          ;


extern void ( png_destroy_write_struct) (png_structpp png_ptr_ptr, png_infopp info_ptr_ptr)
                             ;


extern void ( png_set_crc_action) (png_structrp png_ptr, int crit_action, int ancil_action)
                      ;
# 1455 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern void ( png_set_filter) (png_structrp png_ptr, int method, int filters)
                 ;
# 1508 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern void ( png_set_compression_level) (png_structrp png_ptr, int level)
               ;

extern void ( png_set_compression_mem_level) (png_structrp png_ptr, int mem_level)
                   ;

extern void ( png_set_compression_strategy) (png_structrp png_ptr, int strategy)
                  ;




extern void ( png_set_compression_window_bits) (png_structrp png_ptr, int window_bits)
                     ;

extern void ( png_set_compression_method) (png_structrp png_ptr, int method)
                ;
# 1560 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern void ( png_init_io) (png_structrp png_ptr, png_FILE_p fp);
# 1571 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern void ( png_set_error_fn) (png_structrp png_ptr, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warning_fn)
                                                                           ;


extern png_voidp ( png_get_error_ptr) (png_const_structrp png_ptr);
# 1587 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern void ( png_set_write_fn) (png_structrp png_ptr, png_voidp io_ptr, png_rw_ptr write_data_fn, png_flush_ptr output_flush_fn)
                                                             ;


extern void ( png_set_read_fn) (png_structrp png_ptr, png_voidp io_ptr, png_rw_ptr read_data_fn)
                             ;


extern png_voidp ( png_get_io_ptr) (png_const_structrp png_ptr);

extern void ( png_set_read_status_fn) (png_structrp png_ptr, png_read_status_ptr read_row_fn)
                                     ;

extern void ( png_set_write_status_fn) (png_structrp png_ptr, png_write_status_ptr write_row_fn)
                                       ;
# 1716 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern png_voidp ( png_malloc) (png_const_structrp png_ptr, png_alloc_size_t size)
                                          ;

extern png_voidp ( png_calloc) (png_const_structrp png_ptr, png_alloc_size_t size)
                                          ;


extern png_voidp ( png_malloc_warn) (png_const_structrp png_ptr, png_alloc_size_t size)
                                          ;


extern void ( png_free) (png_const_structrp png_ptr, png_voidp ptr);


extern void ( png_free_data) (png_const_structrp png_ptr, png_inforp info_ptr, png_uint_32 free_me, int num)
                                                       ;
# 1740 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern void ( png_data_freer) (png_const_structrp png_ptr, png_inforp info_ptr, int freer, png_uint_32 mask)
                                                      ;
# 1774 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern void ( png_error) (png_const_structrp png_ptr, png_const_charp error_message)
                                                 ;


extern void ( png_chunk_error) (png_const_structrp png_ptr, png_const_charp error_message)
                                                 ;
# 1790 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern void ( png_warning) (png_const_structrp png_ptr, png_const_charp warning_message)
                                     ;


extern void ( png_chunk_warning) (png_const_structrp png_ptr, png_const_charp warning_message)
                                     ;
# 1804 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern void ( png_benign_error) (png_const_structrp png_ptr, png_const_charp warning_message)
                                     ;



extern void ( png_chunk_benign_error) (png_const_structrp png_ptr, png_const_charp warning_message)
                                     ;


extern void ( png_set_benign_errors) (png_structrp png_ptr, int allowed)
                                        ;
# 1838 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern png_uint_32 ( png_get_valid) (png_const_structrp png_ptr, png_const_inforp info_ptr, png_uint_32 flag)
                                                 ;


extern size_t ( png_get_rowbytes) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                               ;





extern png_bytepp ( png_get_rows) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                               ;




extern void ( png_set_rows) (png_const_structrp png_ptr, png_inforp info_ptr, png_bytepp row_pointers)
                                                  ;



extern png_byte ( png_get_channels) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                               ;



extern png_uint_32 ( png_get_image_width) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                               ;


extern png_uint_32 ( png_get_image_height) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                               ;


extern png_byte ( png_get_bit_depth) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                               ;


extern png_byte ( png_get_color_type) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                               ;


extern png_byte ( png_get_filter_type) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                               ;


extern png_byte ( png_get_interlace_type) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                               ;


extern png_byte ( png_get_compression_type) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                               ;


extern png_uint_32 ( png_get_pixels_per_meter) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                                                            ;
extern png_uint_32 ( png_get_x_pixels_per_meter) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                                                            ;
extern png_uint_32 ( png_get_y_pixels_per_meter) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                                                            ;




extern png_fixed_point ( png_get_pixel_aspect_ratio_fixed) (png_const_structrp png_ptr, png_const_inforp info_ptr);



extern png_int_32 ( png_get_x_offset_pixels) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                                                            ;
extern png_int_32 ( png_get_y_offset_pixels) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                                                            ;
extern png_int_32 ( png_get_x_offset_microns) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                                                            ;
extern png_int_32 ( png_get_y_offset_microns) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                                                            ;





extern png_const_bytep ( png_get_signature) (png_const_structrp png_ptr, png_const_inforp info_ptr)
                               ;



extern png_uint_32 ( png_get_bKGD) (png_const_structrp png_ptr, png_inforp info_ptr, png_color_16p *background)
                                                    ;



extern void ( png_set_bKGD) (png_const_structrp png_ptr, png_inforp info_ptr, png_const_color_16p background)
                                                         ;
# 2009 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern png_uint_32 ( png_get_hIST) (png_const_structrp png_ptr, png_inforp info_ptr, png_uint_16p *hist)
                                             ;
extern void ( png_set_hIST) (png_const_structrp png_ptr, png_inforp info_ptr, png_const_uint_16p hist)
                                                  ;


extern png_uint_32 ( png_get_IHDR) (png_const_structrp png_ptr, png_const_inforp info_ptr, png_uint_32 *width, png_uint_32 *height, int *bit_depth, int *color_type, int *interlace_method, int *compression_method, int *filter_method)


                                                 ;

extern void ( png_set_IHDR) (png_const_structrp png_ptr, png_inforp info_ptr, png_uint_32 width, png_uint_32 height, int bit_depth, int color_type, int interlace_method, int compression_method, int filter_method)


                       ;
# 2061 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern png_uint_32 ( png_get_PLTE) (png_const_structrp png_ptr, png_inforp info_ptr, png_colorp *palette, int *num_palette)
                                                               ;

extern void ( png_set_PLTE) (png_structrp png_ptr, png_inforp info_ptr, png_const_colorp palette, int num_palette)
                                                                    ;


extern png_uint_32 ( png_get_sBIT) (png_const_structrp png_ptr, png_inforp info_ptr, png_color_8p *sig_bit)
                                                ;



extern void ( png_set_sBIT) (png_const_structrp png_ptr, png_inforp info_ptr, png_const_color_8p sig_bit)
                                                     ;
# 2140 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern png_uint_32 ( png_get_tRNS) (png_const_structrp png_ptr, png_inforp info_ptr, png_bytep *trans_alpha, int *num_trans, png_color_16p *trans_color)

                                ;



extern void ( png_set_tRNS) (png_structrp png_ptr, png_inforp info_ptr, png_const_bytep trans_alpha, int num_trans, png_const_color_16p trans_color)

                                     ;
# 2279 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern void ( png_set_keep_unknown_chunks) (png_structrp png_ptr, int keep, png_const_bytep chunk_list, int num_chunks)
                                                          ;






extern int ( png_handle_as_unknown) (png_const_structrp png_ptr, png_const_bytep chunk_name)
                                ;



extern void ( png_set_unknown_chunks) (png_const_structrp png_ptr, png_inforp info_ptr, png_const_unknown_chunkp unknowns, int num_unknowns)

                      ;
# 2304 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern void ( png_set_unknown_chunk_location) (png_const_structrp png_ptr, png_inforp info_ptr, int chunk, int location)
                                                                               ;

extern int ( png_get_unknown_chunks) (png_const_structrp png_ptr, png_inforp info_ptr, png_unknown_chunkpp entries)
                                                      ;






extern void ( png_set_invalid) (png_const_structrp png_ptr, png_inforp info_ptr, int mask)
                                   ;




extern void ( png_read_png) (png_structrp png_ptr, png_inforp info_ptr, int transforms, png_voidp params)
                                      ;


extern void ( png_write_png) (png_structrp png_ptr, png_inforp info_ptr, int transforms, png_voidp params)
                                      ;



extern png_const_charp ( png_get_copyright) (png_const_structrp png_ptr)
                                 ;
extern png_const_charp ( png_get_header_ver) (png_const_structrp png_ptr)
                                 ;
extern png_const_charp ( png_get_header_version) (png_const_structrp png_ptr)
                                 ;
extern png_const_charp ( png_get_libpng_ver) (png_const_structrp png_ptr)
                                 ;
# 2361 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern void ( png_set_user_limits) (png_structrp png_ptr, png_uint_32 user_width_max, png_uint_32 user_height_max)
                                                             ;
extern png_uint_32 ( png_get_user_width_max) (png_const_structrp png_ptr)
                                 ;
extern png_uint_32 ( png_get_user_height_max) (png_const_structrp png_ptr)
                                 ;

extern void ( png_set_chunk_cache_max) (png_structrp png_ptr, png_uint_32 user_chunk_cache_max)
                                      ;
extern png_uint_32 ( png_get_chunk_cache_max) (png_const_structrp png_ptr)
                                 ;

extern void ( png_set_chunk_malloc_max) (png_structrp png_ptr, png_alloc_size_t user_chunk_cache_max)
                                           ;
extern png_alloc_size_t ( png_get_chunk_malloc_max) (png_const_structrp png_ptr)
                                 ;
# 2412 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern png_uint_32 ( png_get_io_state) (png_const_structrp png_ptr);





extern png_uint_32 ( png_get_io_chunk_type) (png_const_structrp png_ptr)
                                 ;
# 2544 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern png_uint_32 ( png_get_uint_32) (png_const_bytep buf);
extern png_uint_16 ( png_get_uint_16) (png_const_bytep buf);
extern png_int_32 ( png_get_int_32) (png_const_bytep buf);


extern png_uint_32 ( png_get_uint_31) (png_const_structrp png_ptr, png_const_bytep buf)
                         ;




extern void ( png_save_uint_32) (png_bytep buf, png_uint_32 i);


extern void ( png_save_int_32) (png_bytep buf, png_int_32 i);







extern void ( png_save_uint_16) (png_bytep buf, unsigned int i);
# 2612 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/libpng/png.h"
extern void ( png_set_check_for_invalid_index) (png_structrp png_ptr, int allowed)
                                        ;

extern int ( png_get_palette_max) (png_const_structp png_ptr, png_const_infop info_ptr)
                              ;
# 32 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../src/pngxtern/pngxutil.h" 1
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../src/pngxtern/pngxutil.h"
void pngx_set_compression_type
   (png_structp png_ptr, png_infop info_ptr, int compression_type);
void pngx_set_filter_type
   (png_structp png_ptr, png_infop info_ptr, int filter_type);
void pngx_set_interlace_type
   (png_structp png_ptr, png_infop info_ptr, int interlace_type);



typedef png_alloc_size_t pngx_alloc_size_t;
# 43 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../src/pngxtern/pngxutil.h"
png_bytepp pngx_malloc_rows
   (png_structp png_ptr, png_infop info_ptr, int filler);
png_bytepp pngx_malloc_rows_extended
   (png_structp png_ptr, png_infop info_ptr,
    pngx_alloc_size_t min_row_size, int filler);
# 33 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h" 1
# 56 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zconf.h" 1
# 254 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zconf.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 255 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zconf.h" 2
     typedef size_t z_size_t;
# 401 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zconf.h"
typedef unsigned char Byte;

typedef unsigned int uInt;
typedef unsigned long uLong;





   typedef Byte Bytef;

typedef char charf;
typedef int intf;
typedef uInt uIntf;
typedef uLong uLongf;


   typedef void const *voidpc;
   typedef void *voidpf;
   typedef void *voidp;







# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 1
# 429 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zconf.h" 2
# 439 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zconf.h"
   typedef unsigned z_crc_t;
# 454 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zconf.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/types.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/types.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/types.h" 2
# 455 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zconf.h" 2





# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdarg.h" 1
# 461 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zconf.h" 2
# 492 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zconf.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/unistd.h" 1
# 493 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zconf.h" 2
# 57 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h" 2
# 103 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
typedef voidpf (*alloc_func)(voidpf opaque, uInt items, uInt size);
typedef void (*free_func)(voidpf opaque, voidpf address);

struct internal_state;

typedef struct z_stream_s {
    Bytef *next_in;
    uInt avail_in;
    uLong total_in;

    Bytef *next_out;
    uInt avail_out;
    uLong total_out;

    char *msg;
    struct internal_state *state;

    alloc_func zalloc;
    free_func zfree;
    voidpf opaque;

    int data_type;

    uLong adler;
    uLong reserved;
} z_stream;

typedef z_stream *z_streamp;





typedef struct gz_header_s {
    int text;
    uLong time;
    int xflags;
    int os;
    Bytef *extra;
    uInt extra_len;
    uInt extra_max;
    Bytef *name;
    uInt name_max;
    Bytef *comment;
    uInt comm_max;
    int hcrc;
    int done;

} gz_header;

typedef gz_header *gz_headerp;
# 242 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern const char * zlibVersion(void);
# 272 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int deflate(z_streamp strm, int flush);
# 385 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int deflateEnd(z_streamp strm);
# 423 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int inflate(z_streamp strm, int flush);
# 543 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int inflateEnd(z_streamp strm);
# 633 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int deflateSetDictionary(z_streamp strm,
                                         const Bytef *dictionary,
                                         uInt dictLength);
# 677 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int deflateGetDictionary(z_streamp strm,
                                         Bytef *dictionary,
                                         uInt *dictLength);
# 699 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int deflateCopy(z_streamp dest,
                                z_streamp source);
# 717 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int deflateReset(z_streamp strm);
# 728 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int deflateParams(z_streamp strm,
                                  int level,
                                  int strategy);
# 766 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int deflateTune(z_streamp strm,
                                int good_length,
                                int max_lazy,
                                int nice_length,
                                int max_chain);
# 783 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern uLong deflateBound(z_streamp strm,
                                   uLong sourceLen);
# 798 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int deflatePending(z_streamp strm,
                                   unsigned *pending,
                                   int *bits);
# 813 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int deflatePrime(z_streamp strm,
                                 int bits,
                                 int value);
# 830 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int deflateSetHeader(z_streamp strm,
                                     gz_headerp head);
# 910 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int inflateSetDictionary(z_streamp strm,
                                         const Bytef *dictionary,
                                         uInt dictLength);
# 933 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int inflateGetDictionary(z_streamp strm,
                                         Bytef *dictionary,
                                         uInt *dictLength);
# 948 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int inflateSync(z_streamp strm);
# 967 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int inflateCopy(z_streamp dest,
                                z_streamp source);
# 983 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int inflateReset(z_streamp strm);
# 994 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int inflateReset2(z_streamp strm,
                                  int windowBits);
# 1008 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int inflatePrime(z_streamp strm,
                                 int bits,
                                 int value);
# 1029 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern long inflateMark(z_streamp strm);
# 1057 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int inflateGetHeader(z_streamp strm,
                                     gz_headerp head);
# 1119 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
typedef unsigned (*in_func)(void *,
                            unsigned char * *);
typedef int (*out_func)(void *, unsigned char *, unsigned);

extern int inflateBack(z_streamp strm,
                                in_func in, void *in_desc,
                                out_func out, void *out_desc);
# 1193 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int inflateBackEnd(z_streamp strm);







extern uLong zlibCompileFlags(void);
# 1254 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int compress(Bytef *dest, uLongf *destLen,
                             const Bytef *source, uLong sourceLen);
# 1269 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int compress2(Bytef *dest, uLongf *destLen,
                              const Bytef *source, uLong sourceLen,
                              int level);
# 1285 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern uLong compressBound(uLong sourceLen);






extern int uncompress(Bytef *dest, uLongf *destLen,
                               const Bytef *source, uLong sourceLen);
# 1310 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int uncompress2(Bytef *dest, uLongf *destLen,
                                const Bytef *source, uLong *sourceLen);
# 1327 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
typedef struct gzFile_s *gzFile;
# 1367 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern gzFile gzdopen(int fd, const char *mode);
# 1390 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int gzbuffer(gzFile file, unsigned size);
# 1406 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int gzsetparams(gzFile file, int level, int strategy);
# 1417 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int gzread(gzFile file, voidp buf, unsigned len);
# 1447 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern z_size_t gzfread(voidp buf, z_size_t size, z_size_t nitems,
                                 gzFile file);
# 1473 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int gzwrite(gzFile file, voidpc buf, unsigned len);





extern z_size_t gzfwrite(voidpc buf, z_size_t size,
                                  z_size_t nitems, gzFile file);
# 1493 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int gzprintf(gzFile file, const char *format, ...);
# 1508 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int gzputs(gzFile file, const char *s);







extern char * gzgets(gzFile file, char *buf, int len);
# 1530 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int gzputc(gzFile file, int c);





extern int gzgetc(gzFile file);
# 1545 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int gzungetc(int c, gzFile file);
# 1557 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int gzflush(gzFile file, int flush);
# 1592 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int gzrewind(gzFile file);
# 1620 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int gzeof(gzFile file);
# 1635 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int gzdirect(gzFile file);
# 1656 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int gzclose(gzFile file);
# 1669 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int gzclose_r(gzFile file);
extern int gzclose_w(gzFile file);
# 1681 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern const char * gzerror(gzFile file, int *errnum);
# 1697 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern void gzclearerr(gzFile file);
# 1714 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern uLong adler32(uLong adler, const Bytef *buf, uInt len);
# 1734 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern uLong adler32_z(uLong adler, const Bytef *buf,
                                z_size_t len);
# 1752 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern uLong crc32(uLong crc, const Bytef *buf, uInt len);
# 1770 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern uLong crc32_z(uLong crc, const Bytef *buf,
                              z_size_t len);
# 1793 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern uLong crc32_combine_op(uLong crc1, uLong crc2, uLong op);
# 1806 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern int deflateInit_(z_streamp strm, int level,
                                 const char *version, int stream_size);
extern int inflateInit_(z_streamp strm,
                                 const char *version, int stream_size);
extern int deflateInit2_(z_streamp strm, int level, int method,
                                  int windowBits, int memLevel,
                                  int strategy, const char *version,
                                  int stream_size);
extern int inflateInit2_(z_streamp strm, int windowBits,
                                  const char *version, int stream_size);
extern int inflateBackInit_(z_streamp strm, int windowBits,
                                     unsigned char *window,
                                     const char *version,
                                     int stream_size);
# 1859 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
struct gzFile_s {
    unsigned have;
    unsigned char *next;
    off_t pos;
};
extern int gzgetc_(gzFile file);
# 1918 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
   extern gzFile gzopen(const char *, const char *);
   extern off_t gzseek(gzFile, off_t, int);
   extern off_t gztell(gzFile);
   extern off_t gzoffset(gzFile);
   extern uLong adler32_combine(uLong, uLong, off_t);
   extern uLong crc32_combine(uLong, uLong, off_t);
   extern uLong crc32_combine_gen(off_t);
# 1936 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/../../third_party/zlib/zlib.h"
extern const char * zError(int);
extern int inflateSyncPoint(z_streamp);
extern const z_crc_t * get_crc_table(void);
extern int inflateUndermine(z_streamp, int);
extern int inflateValidate(z_streamp, int);
extern unsigned long inflateCodesUsed(z_streamp);
extern int inflateResetKeep(z_streamp);
extern int deflateResetKeep(z_streamp);






extern int gzvprintf(gzFile file,
                                           const char *format,
                                           va_list va);
# 34 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/optipng/optipng.c" 2




static const char *msg_intro =
    "OptiPNG" " version " "0.7.8" "\n"
    "Copyright (C) 2001-2023 Cosmin Truta and the Contributing Authors" ".\n";

static const char *msg_license =
    "This program is open-source software. See LICENSE for more details.\n"
    "\n"
    "Portions of this software are based in part on the work of:\n"
    "  Jean-loup Gailly and Mark Adler (zlib)\n"
    "  Glenn Randers-Pehrson and the PNG Development Group (libpng)\n"
    "  Miyasaka Masaru (BMP support)\n"
    "  David Koblas (GIF support)\n";

static const char *msg_help_synopsis =
    "Synopsis:\n"
    "    optipng [options] files ...\n"
    "Files:\n"
    "    Image files of type: PNG, BMP, GIF, PNM or TIFF\n";

static const char *msg_help_basic_options =
    "Basic options:\n"
    "    -?, -h, -help\tshow the extended help\n"
    "    -o <level>\t\toptimization level (0-7)\t\t[default: 2]\n"
    "    -v\t\t\trun in verbose mode / show copyright and version info\n";

static const char *msg_help_options =
    "Basic options:\n"
    "    -?, -h, -help\tshow this help\n"
    "    -o <level>\t\toptimization level (0-7)\t\t[default: 2]\n"
    "    -v\t\t\trun in verbose mode / show copyright and version info\n"
    "General options:\n"
    "    -backup, -keep\tkeep a backup of the modified files\n"
    "    -clobber\t\toverwrite existing files\n"



    "    -fix\t\tenable error recovery\n"
    "    -force\t\tenforce writing of a new output file\n"
    "    -preserve\t\tpreserve file attributes if possible\n"
    "    -quiet, -silent\trun in quiet mode\n"
    "    -simulate\t\trun in simulation mode\n"
    "    -out <file>\t\twrite output file to <file>\n"
    "    -dir <directory>\twrite output file(s) to <directory>\n"
    "    -log <file>\t\tlog messages to <file>\n"
    "    --\t\t\tstop option switch parsing\n"
    "Optimization options:\n"
    "    -f <filters>\tPNG delta filters (0-5)\t\t\t[default: 0,5]\n"
    "    -i <type>\t\tPNG interlace type (0-1)\n"
    "    -zc <levels>\tzlib compression levels (1-9)\t\t[default: 9]\n"
    "    -zm <levels>\tzlib memory levels (1-9)\t\t[default: 8]\n"
    "    -zs <strategies>\tzlib compression strategies (0-3)\t[default: 0-3]\n"
    "    -zw <size>\t\tzlib window size (256,512,1k,2k,4k,8k,16k,32k)\n"
    "    -full\t\tproduce a full report on IDAT (might reduce speed)\n"
    "    -nb\t\t\tno bit depth reduction\n"
    "    -nc\t\t\tno color type reduction\n"
    "    -np\t\t\tno palette reduction\n"
    "    -nx\t\t\tno reductions\n"
    "    -nz\t\t\tno IDAT recoding\n"
    "Editing options:\n"
    "    -snip\t\tcut one image out of multi-image or animation files\n"
    "    -strip <objects>\tstrip metadata objects (e.g. \"all\")\n"
    "Optimization levels:\n"
    "    -o0\t\t<=>\t-o1 -nx -nz\t\t\t\t(0 or 1 trials)\n"
    "    -o1\t\t<=>\t-zc9 -zm8 -zs0 -f0\t\t\t(1 trial)\n"
    "    \t\t(or...)\t-zc9 -zm8 -zs1 -f5\t\t\t(1 trial)\n"
    "    -o2\t\t<=>\t-zc9 -zm8 -zs0-3 -f0,5\t\t\t(8 trials)\n"
    "    -o3\t\t<=>\t-zc9 -zm8-9 -zs0-3 -f0,5\t\t(16 trials)\n"
    "    -o4\t\t<=>\t-zc9 -zm8 -zs0-3 -f0-5\t\t\t(24 trials)\n"
    "    -o5\t\t<=>\t-zc9 -zm8-9 -zs0-3 -f0-5\t\t(48 trials)\n"
    "    -o6\t\t<=>\t-zc1-9 -zm8 -zs0-3 -f0-5\t\t(120 trials)\n"
    "    -o7\t\t<=>\t-zc1-9 -zm8-9 -zs0-3 -f0-5\t\t(240 trials)\n"
    "    -o7 -zm1-9\t<=>\t-zc1-9 -zm1-9 -zs0-3 -f0-5\t\t(1080 trials)\n"
    "Notes:\n"
    "    The combination for -o1 is chosen heuristically.\n"
    "    Exhaustive combinations such as \"-o7 -zm1-9\" are not generally recommended.\n";

static const char *msg_help_examples =
    "Examples:\n"
    "    optipng file.png\t\t\t\t\t\t(default speed)\n"
    "    optipng -o5 file.png\t\t\t\t\t(slow)\n"
    "    optipng -o7 file.png\t\t\t\t\t(very slow)\n";

static const char *msg_help_more =
    "Type \"optipng -h\" for extended help.\n";


static enum
{
    OP_RUN,
    OP_SHOW_HELP,
    OP_SHOW_VERSION
} operation;

static struct
{
    int help;
    int version;
} local_options;

static struct opng_options options;

static FILE *con_file;
static FILE *log_file;

static int start_of_line;





static void
error(const char *fmt, ...)
{
    va_list arg_ptr;


    fprintf(stderr, "** Error: ");
    __builtin_va_start((arg_ptr));
    vfprintf(stderr, fmt, arg_ptr);
    ;
    fprintf(stderr, "\n");
    exit(1);
}




static void
panic(const char *msg)
{

    fprintf(stderr, "\n** INTERNAL ERROR: %s\n", msg);
    fprintf(stderr, "Please submit a defect report.\n" "http://optipng.sourceforge.net/" "\n\n");
    fflush(stderr);
    if (options.debug)
    {

        abort();
    }
    else
    {

        fprintf(stderr,
            "The execution of this program has been terminated abnormally.\n");
        exit(70);
    }
}




static int
opng_strcasecmp(const char *str1, const char *str2)
{
    int ch1, ch2;


    for ( ; ; )
    {
        ch1 = tolower(*str1++);
        ch2 = tolower(*str2++);
        if (ch1 != ch2)
            return ch1 - ch2;
        if (ch1 == '\0')
            return 0;
    }

}




static char *
opng_strltrim(const char *str)
{

    while (isspace(*str))
        ++str;
    return (char *)str;
}




static char *
opng_strtail(const char *str, size_t num)
{
    size_t len;


    len = strlen(str);
    if (len <= num)
        return (char *)str;
    return (char *)str + len - num;
}




static char *
opng_strpbrk_digit(const char *str)
{
    for ( ; ; )
    {
        if (*str == '\0')
            return 0;
        if (isdigit(*str))
            return (char *)str;
        ++str;
    }
}




static int
opng_str2ulong(unsigned long *out_val, const char *in_str,
               int allow_multiplier)
{
    const char *begin_ptr;
    char *end_ptr;
    unsigned long multiplier;



    begin_ptr = end_ptr = opng_strltrim(in_str);
    if (*begin_ptr >= '0' && *begin_ptr <= '9')
        *out_val = strtoul(begin_ptr, &end_ptr, 10);
    if (begin_ptr == end_ptr)
    {
        errno = EINVAL;
        *out_val = 0;
        return -1;
    }

    if (allow_multiplier)
    {





        if (*end_ptr == 'k' || *end_ptr == 'K')
        {
            ++end_ptr;
            multiplier = 1024UL;
        }
        else if (*end_ptr == 'M')
        {
            ++end_ptr;
            multiplier = 1024UL * 1024UL;
        }
        else if (*end_ptr == 'G')
        {
            ++end_ptr;
            multiplier = 1024UL * 1024UL * 1024UL;
        }
        else
            multiplier = 1;
        if (multiplier > 1)
        {
            if (*out_val > 18446744073709551615UL / multiplier)
            {
                errno = ERANGE;
                *out_val = 18446744073709551615UL;
            }
            else
                *out_val *= multiplier;
        }
    }


    if (*opng_strltrim(end_ptr) != '\0')
    {
        errno = EINVAL;
        return -1;
    }
    return 0;
}




static void
err_option_arg(const char *opt, const char *opt_arg)
{

    if (opt_arg == 0 || *opng_strltrim(opt_arg) == '\0')
        error("Missing argument for option %s", opt);
    else
        error("Invalid argument for option %s: %s", opt, opt_arg);
}




static int
check_num_option(const char *opt, const char *opt_arg,
                 int lowest, int highest)
{
    unsigned long value;


    if (opng_str2ulong(&value, opt_arg, 0) != 0 ||
        value > 2147483647 || (int)value < lowest || (int)value > highest)
        err_option_arg(opt, opt_arg);
    return (int)value;
}




static int
check_power2_option(const char *opt, const char *opt_arg,
                    int lowest, int highest)
{
    unsigned long value;
    int result;



    if (opng_str2ulong(&value, opt_arg, 1) == 0)
    {
        if (lowest < 0)
            lowest = 0;
        if (highest > (int)(8 * sizeof(long) - 2))
            highest = (int)(8 * sizeof(long) - 2);
        for (result = lowest; result <= highest; ++result)
        {
            if ((1UL << result) == value)
                return result;
        }
    }
    err_option_arg(opt, opt_arg);
    return -1;
}




static opng_bitset_t
check_rangeset_option(const char *opt, const char *opt_arg,
                      opng_bitset_t result_mask)
{
    opng_bitset_t result;




    if (opng_strparse_rangeset_to_bitset(&result, opt_arg, result_mask) != 0)
        result = 0U;
    if ((result & result_mask) != result)
        result = 0U;
    if (result == 0U)
        err_option_arg(opt, opt_arg);
    return result;
}




static void
check_obj_option(const char *opt, const char *opt_arg)
{
    unsigned int i;

    if (strcmp("all", opt_arg) == 0)
        return;



    for (i = 0; i < 4; ++i)
    {

        if (!((opt_arg[i] >= 'A' && opt_arg[i] <= 'Z') ||
              (opt_arg[i] >= 'a' && opt_arg[i] <= 'z')))
            break;
    }
    if (i == 4 && opt_arg[i] == '\0')
        error("Manipulation of individual chunks is not implemented");
    else
        err_option_arg(opt, opt_arg);
}




static int
scan_option(const char *str,
            char opt_buf[], size_t opt_buf_size, const char **opt_arg_ptr)
{
    const char *ptr;
    unsigned int opt_len;


    if (str[0] != '-' || str[1] == '\0')
        return 0;


    opt_len = 0;
    ptr = str + 1;
    while (*ptr == '-')
        ++ptr;
    if (*ptr == '\0')
        --ptr;
    for ( ; ; )
    {
        if (opt_len < opt_buf_size)
            opt_buf[opt_len] = (char)tolower(*ptr);
        ++opt_len;
        ++ptr;
        if (*ptr == '\0' || isspace(*ptr))
        {
            while (isspace(*ptr))
                ++ptr;
            *opt_arg_ptr = (*ptr != '\0') ? ptr : 0;
            break;
        }
        if (*ptr == '=')
        {
            ++ptr;
            *opt_arg_ptr = ptr;
            break;
        }
    }


    if (opt_buf_size > 0)
    {
        if (opt_len < opt_buf_size)
            opt_buf[opt_len] = '\0';
        else
            opt_buf[opt_buf_size - 1] = '\0';
    }
    return 1;
}




static void
parse_args(int argc, char *argv[])
{
    char *arg;
    char opt[16];
    size_t opt_len;
    const char *xopt;
    int simple_opt, stop_switch;
    opng_bitset_t set;
    int val;
    unsigned int file_count;
    int i;


    memset(&options, 0, sizeof(options));
    options.optim_level = -1;
    options.interlace = -1;
    file_count = 0;


    stop_switch = 0;
    for (i = 1; i < argc; ++i)
    {
        arg = argv[i];
        if (stop_switch || scan_option(arg, opt, sizeof(opt), &xopt) < 1)
        {
            ++file_count;
            continue;
        }
        opt_len = strlen(opt);


        argv[i] = 0;


        if ((strchr("fio", opt[0]) != 0 && isdigit(opt[1])) ||
            (opt[0] == 'z' && isalpha(opt[1]) && isdigit(opt[2])))
        {



            opt_len = (size_t)(opng_strpbrk_digit(opt) - opt);
            opt[opt_len] = '\0';
            xopt = opng_strpbrk_digit(arg);
        }


        simple_opt = 1;
        if (strcmp("-", opt) == 0)
        {

            stop_switch = 1;
        }
        else if (strcmp("?", opt) == 0 ||
                 strncmp("help", opt, opt_len) == 0)
        {

            local_options.help = 1;
        }
        else if ((strncmp("backup", opt, opt_len) == 0) ||
                 (strncmp("keep", opt, opt_len) == 0))
        {

            options.backup = 1;
        }
        else if (strncmp("clobber", opt, opt_len) == 0)
        {

            options.clobber = 1;
        }
        else if (strcmp("debug", opt) == 0)
        {


            options.debug = 1;
        }
        else if (strncmp("fix", opt, opt_len) == 0 && opt_len >= 2)
        {

            options.fix = 1;
        }
        else if (strncmp("force", opt, opt_len) == 0 && opt_len >= 2)
        {

            options.force = 1;
        }
        else if (strncmp("full", opt, opt_len) == 0 && opt_len >= 2)
        {

            options.full = 1;
        }
        else if (strcmp("nb", opt) == 0)
        {

            options.nb = 1;
        }
        else if (strcmp("nc", opt) == 0)
        {

            options.nc = 1;
        }
        else if (strcmp("np", opt) == 0)
        {

            options.np = 1;
        }
        else if (strcmp("nx", opt) == 0)
        {

            options.nb = options.nc = options.np = 1;

        }
        else if (strcmp("nz", opt) == 0)
        {

            options.nz = 1;
        }
        else if (strncmp("preserve", opt, opt_len) == 0)
        {

            options.preserve = 1;
        }
        else if ((strncmp("quiet", opt, opt_len) == 0) ||
                 (strncmp("silent", opt, opt_len) == 0 && opt_len >= 3))
        {

            options.quiet = 1;
        }
        else if (strncmp("simulate", opt, opt_len) == 0 && opt_len >= 3)
        {

            options.simulate = 1;
        }
        else if (strncmp("snip", opt, opt_len) == 0 && opt_len >= 2)
        {

            options.snip = 1;
        }
        else if (strcmp("v", opt) == 0)
        {

            options.verbose = 1;
            local_options.version = 1;
        }
        else if (strncmp("verbose", opt, opt_len) == 0 && opt_len >= 4)
        {

            options.verbose = 1;
        }
        else if (strncmp("version", opt, opt_len) == 0 && opt_len >= 4)
        {

            local_options.version = 1;
        }
        else
        {
            simple_opt = 0;
            if (xopt == 0)
            {
                if (++i < argc)
                {
                    xopt = argv[i];

                    argv[i] = 0;
                }
                else
                {

                    xopt = "";
                }
            }
        }


        if (simple_opt)
        {
            if (xopt != 0)
                error("No argument allowed for option: %s", arg);
        }
        else if (strcmp("o", opt) == 0)
        {

            val = check_num_option("-o", xopt, 0, 2147483647);
            if (options.optim_level < 0)
                options.optim_level = val;
            else if (options.optim_level != val)
                error("Multiple optimization levels are not permitted");
        }
        else if (strcmp("i", opt) == 0)
        {

            val = check_num_option("-i", xopt, 0, 1);
            if (options.interlace < 0)
                options.interlace = val;
            else if (options.interlace != val)
                error("Multiple interlace types are not permitted");
        }
        else if (strcmp("f", opt) == 0)
        {

            set = check_rangeset_option("-f", xopt, ((1 << (5+1)) - (1 << 0)));
            options.filter_set |= set;
        }
        else if (strcmp("zc", opt) == 0)
        {

            set = check_rangeset_option("-zc", xopt, ((1 << (9+1)) - (1 << 1)));
            options.compr_level_set |= set;
        }
        else if (strcmp("zm", opt) == 0)
        {

            set = check_rangeset_option("-zm", xopt, ((1 << (9+1)) - (1 << 1)));
            options.mem_level_set |= set;
        }
        else if (strcmp("zs", opt) == 0)
        {

            set = check_rangeset_option("-zs", xopt, ((1 << (3+1)) - (1 << 0)));
            options.strategy_set |= set;
        }
        else if (strcmp("zw", opt) == 0)
        {

            val = check_power2_option("-zw", xopt, 8, 15);
            if (options.window_bits == 0)
                options.window_bits = val;
            else if (options.window_bits != val)
                error("Multiple window sizes are not permitted");
        }
        else if (strncmp("strip", opt, opt_len) == 0 && opt_len >= 2)
        {

            check_obj_option("-strip", xopt);
            options.strip_all = 1;
        }
        else if (strncmp("out", opt, opt_len) == 0 && opt_len >= 2)
        {

            if (options.out_name != 0)
                error("Multiple output file names are not permitted");
            if (xopt[0] == '\0')
                err_option_arg("-out", 0);
            options.out_name = xopt;
        }
        else if (strncmp("dir", opt, opt_len) == 0)
        {

            if (options.dir_name != 0)
                error("Multiple output dir names are not permitted");
            if (xopt[0] == '\0')
                err_option_arg("-dir", 0);
            options.dir_name = xopt;
        }
        else if (strncmp("log", opt, opt_len) == 0)
        {

            if (options.log_name != 0)
                error("Multiple log file names are not permitted");
            if (xopt[0] == '\0')
                err_option_arg("-log", 0);
            options.log_name = xopt;
        }
        else
        {
            error("Unrecognized option: %s", arg);
        }
    }


    if (options.out_name != 0)
    {
        if (file_count > 1)
            error("The option -out requires one input file");
        if (options.dir_name != 0)
            error("The options -out and -dir are mutually exclusive");
    }
    if (options.log_name != 0)
    {
        if (opng_strcasecmp(".log", opng_strtail(options.log_name, 4)) != 0)
            error("To prevent accidental data corruption, "
                  "the log file name must end with \".log\"");
    }
    if (local_options.help)
        operation = OP_SHOW_HELP;
    else if (file_count != 0)
        operation = OP_RUN;
    else if (local_options.version)
        operation = OP_SHOW_VERSION;
    else
        operation = OP_SHOW_HELP;
}




static void
app_printf(const char *fmt, ...)
{
    va_list arg_ptr;

    if (fmt[0] == '\0')
        return;
    start_of_line = (fmt[strlen(fmt) - 1] == '\n') ? 1 : 0;

    if (con_file != 0)
    {
        __builtin_va_start((arg_ptr));
        vfprintf(con_file, fmt, arg_ptr);
        ;
    }
    if (log_file != 0)
    {
        __builtin_va_start((arg_ptr));
        vfprintf(log_file, fmt, arg_ptr);
        ;
    }
}




static void
app_print_cntrl(int cntrl_code)
{
    const char *con_str, *log_str;
    int i;

    if (cntrl_code == '\r')
    {

        con_str = "\r";
        log_str = "\n";
        start_of_line = 1;
    }
    else if (cntrl_code == '\v')
    {

        if (!start_of_line)
        {
            con_str = log_str = "\n";
            start_of_line = 1;
        }
        else
            con_str = log_str = "";
    }
    else if (cntrl_code < 0 && cntrl_code > -80 && start_of_line)
    {

        if (con_file != 0)
        {
            for (i = 0; i > cntrl_code; --i)
                fputc(' ', con_file);
        }
        con_str = "\r";
        log_str = "";
    }
    else
    {

        con_str = log_str = "<?>";
    }

    if (con_file != 0)
        fputs(con_str, con_file);
    if (log_file != 0)
        fputs(log_str, log_file);
}




static void
app_progress(unsigned long current_step, unsigned long total_steps)
{

    if (con_file != 0)
        fflush(con_file);




    if (current_step && total_steps)
        return;
}




static void
app_init(void)
{
    start_of_line = 1;

    if (operation == OP_SHOW_HELP || operation == OP_SHOW_VERSION)
        con_file = stdout;
    else if (!options.quiet)
        con_file = stderr;
    else
        con_file = 0;

    if (options.log_name != 0)
    {

        if ((log_file = fopen(options.log_name, "a")) == 0)
            error("Can't open log file: %s\n", options.log_name);
        setvbuf(log_file, 0, _IOLBF, 1024);
        app_printf("** Warning: %s\n\n",
                   "The option -log is deprecated; use shell redirection");
    }
}




static void
app_finish(void)
{
    if (log_file != 0)
    {

        fclose(log_file);
    }
}




static int
process_files(int argc, char *argv[])
{
    int result;
    struct opng_ui ui;
    int i;


    ui.printf_fn = app_printf;
    ui.print_cntrl_fn = app_print_cntrl;
    ui.progress_fn = app_progress;
    ui.panic_fn = panic;
    if (opng_initialize(&options, &ui) != 0)
        panic("Can't initialize optimization engine");


    result = 0;
    for (i = 1; i < argc; ++i)
    {
        if (argv[i] == 0 || argv[i][0] == '\0')
            continue;
        if (opng_optimize(argv[i]) != 0)
            result = 1;
    }


    if (opng_finalize() != 0)
        panic("Can't finalize optimization engine");

    return result;
}




int
main(int argc, char *argv[])
{
    int result;


    parse_args(argc, argv);
    app_init();
    result = 0;

    if (local_options.version)
    {

        app_printf("%s\n", msg_intro);
    }

    switch (operation)
    {
    case OP_RUN:

        result = process_files(argc, argv);
        break;
    case OP_SHOW_HELP:
        if (local_options.help)
        {

            app_printf("%s%s%s",
                       msg_help_synopsis,
                       msg_help_options,
                       msg_help_examples);
        }
        else
        {

            app_printf("%s%s%s%s",
                       msg_help_synopsis,
                       msg_help_basic_options,
                       msg_help_examples,
                       msg_help_more);
        }
        break;
    case OP_SHOW_VERSION:

        app_printf("%s\n", msg_license);
        app_printf("Using libpng version %s and zlib version %s\n",
                   png_get_libpng_ver(0), zlibVersion());
        break;
    default:
        result = -1;
    }


    app_finish();
    return result;
}
