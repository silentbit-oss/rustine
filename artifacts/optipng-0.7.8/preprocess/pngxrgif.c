# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxrgif.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxrgif.c"





# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxtern.h" 1
# 12 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxtern.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h" 1
# 330 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/pnglibconf.h" 1
# 331 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h" 2




# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/pngconf.h" 1
# 31 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/pngconf.h"
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
# 32 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/pngconf.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 33 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/pngconf.h" 2
# 46 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/pngconf.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 47 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/pngconf.h" 2
# 481 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/pngconf.h"
   typedef unsigned char png_byte;







   typedef short png_int_16;







   typedef unsigned short png_uint_16;





   typedef int png_int_32;







   typedef unsigned int png_uint_32;
# 523 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/pngconf.h"
typedef size_t png_size_t;
typedef ptrdiff_t png_ptrdiff_t;
# 557 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/pngconf.h"
   typedef size_t png_alloc_size_t;
# 574 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/pngconf.h"
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
# 606 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/pngconf.h"
typedef png_byte * * png_bytepp;
typedef png_uint_32 * * png_uint_32pp;
typedef png_int_32 * * png_int_32pp;
typedef png_uint_16 * * png_uint_16pp;
typedef png_int_16 * * png_int_16pp;
typedef const char * * png_const_charpp;
typedef char * * png_charpp;
typedef png_fixed_point * * png_fixed_point_pp;





typedef char * * * png_charppp;
# 336 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h" 2
# 431 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
typedef char* png_libpng_version_1_6_40;







typedef struct png_struct_def png_struct;
typedef const png_struct * png_const_structp;
typedef png_struct * png_structp;
typedef png_struct * * png_structpp;
# 453 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
typedef struct png_info_def png_info;
typedef png_info * png_infop;
typedef const png_info * png_const_infop;
typedef png_info * * png_infopp;
# 469 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
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
# 600 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
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
# 622 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
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
# 754 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
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
# 775 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
typedef void ( *png_error_ptr) (png_structp, png_const_charp);
typedef void ( *png_rw_ptr) (png_structp, png_bytep, size_t);
typedef void ( *png_flush_ptr) (png_structp);
typedef void ( *png_read_status_ptr) (png_structp, png_uint_32, int)
         ;
typedef void ( *png_write_status_ptr) (png_structp, png_uint_32, int)
         ;
# 867 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
typedef png_voidp ( *png_malloc_ptr) (png_structp, png_alloc_size_t)
                      ;
typedef void ( *png_free_ptr) (png_structp, png_voidp);
# 901 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
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
# 963 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern void ( png_longjmp) (png_const_structrp png_ptr, int val)
                 ;



extern int ( png_reset_zstream) (png_structrp png_ptr);
# 986 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
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
# 1285 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern int ( png_set_interlace_handling) (png_structrp png_ptr);
# 1358 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
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
# 1455 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern void ( png_set_filter) (png_structrp png_ptr, int method, int filters)
                 ;
# 1508 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
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
# 1560 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern void ( png_init_io) (png_structrp png_ptr, png_FILE_p fp);
# 1571 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern void ( png_set_error_fn) (png_structrp png_ptr, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warning_fn)
                                                                           ;


extern png_voidp ( png_get_error_ptr) (png_const_structrp png_ptr);
# 1587 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern void ( png_set_write_fn) (png_structrp png_ptr, png_voidp io_ptr, png_rw_ptr write_data_fn, png_flush_ptr output_flush_fn)
                                                             ;


extern void ( png_set_read_fn) (png_structrp png_ptr, png_voidp io_ptr, png_rw_ptr read_data_fn)
                             ;


extern png_voidp ( png_get_io_ptr) (png_const_structrp png_ptr);

extern void ( png_set_read_status_fn) (png_structrp png_ptr, png_read_status_ptr read_row_fn)
                                     ;

extern void ( png_set_write_status_fn) (png_structrp png_ptr, png_write_status_ptr write_row_fn)
                                       ;
# 1716 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern png_voidp ( png_malloc) (png_const_structrp png_ptr, png_alloc_size_t size)
                                          ;

extern png_voidp ( png_calloc) (png_const_structrp png_ptr, png_alloc_size_t size)
                                          ;


extern png_voidp ( png_malloc_warn) (png_const_structrp png_ptr, png_alloc_size_t size)
                                          ;


extern void ( png_free) (png_const_structrp png_ptr, png_voidp ptr);


extern void ( png_free_data) (png_const_structrp png_ptr, png_inforp info_ptr, png_uint_32 free_me, int num)
                                                       ;
# 1740 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern void ( png_data_freer) (png_const_structrp png_ptr, png_inforp info_ptr, int freer, png_uint_32 mask)
                                                      ;
# 1774 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern void ( png_error) (png_const_structrp png_ptr, png_const_charp error_message)
                                                 ;


extern void ( png_chunk_error) (png_const_structrp png_ptr, png_const_charp error_message)
                                                 ;
# 1790 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern void ( png_warning) (png_const_structrp png_ptr, png_const_charp warning_message)
                                     ;


extern void ( png_chunk_warning) (png_const_structrp png_ptr, png_const_charp warning_message)
                                     ;
# 1804 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern void ( png_benign_error) (png_const_structrp png_ptr, png_const_charp warning_message)
                                     ;



extern void ( png_chunk_benign_error) (png_const_structrp png_ptr, png_const_charp warning_message)
                                     ;


extern void ( png_set_benign_errors) (png_structrp png_ptr, int allowed)
                                        ;
# 1838 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
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
# 2009 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern png_uint_32 ( png_get_hIST) (png_const_structrp png_ptr, png_inforp info_ptr, png_uint_16p *hist)
                                             ;
extern void ( png_set_hIST) (png_const_structrp png_ptr, png_inforp info_ptr, png_const_uint_16p hist)
                                                  ;


extern png_uint_32 ( png_get_IHDR) (png_const_structrp png_ptr, png_const_inforp info_ptr, png_uint_32 *width, png_uint_32 *height, int *bit_depth, int *color_type, int *interlace_method, int *compression_method, int *filter_method)


                                                 ;

extern void ( png_set_IHDR) (png_const_structrp png_ptr, png_inforp info_ptr, png_uint_32 width, png_uint_32 height, int bit_depth, int color_type, int interlace_method, int compression_method, int filter_method)


                       ;
# 2061 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern png_uint_32 ( png_get_PLTE) (png_const_structrp png_ptr, png_inforp info_ptr, png_colorp *palette, int *num_palette)
                                                               ;

extern void ( png_set_PLTE) (png_structrp png_ptr, png_inforp info_ptr, png_const_colorp palette, int num_palette)
                                                                    ;


extern png_uint_32 ( png_get_sBIT) (png_const_structrp png_ptr, png_inforp info_ptr, png_color_8p *sig_bit)
                                                ;



extern void ( png_set_sBIT) (png_const_structrp png_ptr, png_inforp info_ptr, png_const_color_8p sig_bit)
                                                     ;
# 2140 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern png_uint_32 ( png_get_tRNS) (png_const_structrp png_ptr, png_inforp info_ptr, png_bytep *trans_alpha, int *num_trans, png_color_16p *trans_color)

                                ;



extern void ( png_set_tRNS) (png_structrp png_ptr, png_inforp info_ptr, png_const_bytep trans_alpha, int num_trans, png_const_color_16p trans_color)

                                     ;
# 2279 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern void ( png_set_keep_unknown_chunks) (png_structrp png_ptr, int keep, png_const_bytep chunk_list, int num_chunks)
                                                          ;






extern int ( png_handle_as_unknown) (png_const_structrp png_ptr, png_const_bytep chunk_name)
                                ;



extern void ( png_set_unknown_chunks) (png_const_structrp png_ptr, png_inforp info_ptr, png_const_unknown_chunkp unknowns, int num_unknowns)

                      ;
# 2304 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
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
# 2361 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
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
# 2412 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern png_uint_32 ( png_get_io_state) (png_const_structrp png_ptr);





extern png_uint_32 ( png_get_io_chunk_type) (png_const_structrp png_ptr)
                                 ;
# 2544 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern png_uint_32 ( png_get_uint_32) (png_const_bytep buf);
extern png_uint_16 ( png_get_uint_16) (png_const_bytep buf);
extern png_int_32 ( png_get_int_32) (png_const_bytep buf);


extern png_uint_32 ( png_get_uint_31) (png_const_structrp png_ptr, png_const_bytep buf)
                         ;




extern void ( png_save_uint_32) (png_bytep buf, png_uint_32 i);


extern void ( png_save_int_32) (png_bytep buf, png_int_32 i);







extern void ( png_save_uint_16) (png_bytep buf, unsigned int i);
# 2612 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern void ( png_set_check_for_invalid_index) (png_structrp png_ptr, int allowed)
                                        ;

extern int ( png_get_palette_max) (png_const_structp png_ptr, png_const_infop info_ptr)
                              ;
# 13 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxtern.h" 2
# 47 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxtern.h"
int pngx_read_image(png_structp png_ptr, png_infop info_ptr,
                           png_const_charpp fmt_name_ptr,
                           png_const_charpp fmt_long_name_ptr);
# 7 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxrgif.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxutil.h" 1
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxutil.h"
void pngx_set_compression_type
   (png_structp png_ptr, png_infop info_ptr, int compression_type);
void pngx_set_filter_type
   (png_structp png_ptr, png_infop info_ptr, int filter_type);
void pngx_set_interlace_type
   (png_structp png_ptr, png_infop info_ptr, int interlace_type);



typedef png_alloc_size_t pngx_alloc_size_t;
# 43 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxutil.h"
png_bytepp pngx_malloc_rows
   (png_structp png_ptr, png_infop info_ptr, int filler);
png_bytepp pngx_malloc_rows_extended
   (png_structp png_ptr, png_infop info_ptr,
    pngx_alloc_size_t min_row_size, int filler);
# 8 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxrgif.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../gifread/gifread.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../gifread/gifread.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../gifread/gifread.h" 2
# 54 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../gifread/gifread.h"
struct GIFScreen
{
    unsigned int Width;
    unsigned int Height;
    unsigned int GlobalColorFlag;
    unsigned int ColorResolution;
    unsigned int SortFlag;
    unsigned int GlobalNumColors;
    unsigned int Background;
    unsigned int PixelAspectRatio;
    unsigned char GlobalColorTable[256 * 3];
};




struct GIFImage
{
    struct GIFScreen *Screen;
    unsigned int LeftPos;
    unsigned int TopPos;
    unsigned int Width;
    unsigned int Height;
    unsigned int LocalColorFlag;
    unsigned int InterlaceFlag;
    unsigned int SortFlag;
    unsigned int LocalNumColors;
    unsigned char LocalColorTable[256 * 3];
    unsigned char **Rows;
};




struct GIFExtension
{
    struct GIFScreen *Screen;
    unsigned char *Buffer;
    unsigned int BufferSize;
    unsigned char Label;
};




struct GIFGraphicCtlExt
{
    unsigned int DisposalMethod;
    unsigned int InputFlag;
    unsigned int TransparentFlag;
    unsigned int DelayTime;
    unsigned int Transparent;
};







void GIFReadScreen(struct GIFScreen *screen, FILE *stream);







void GIFInitImage(struct GIFImage *image,
                  struct GIFScreen *screen, unsigned char **rows);





void GIFDestroyImage(struct GIFImage *image);
# 138 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../gifread/gifread.h"
int GIFReadNextBlock(struct GIFImage *image, struct GIFExtension *ext,
                     FILE *stream);
# 148 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../gifread/gifread.h"
void GIFGetColorTable(unsigned char **colors, unsigned int *numColors,
                      struct GIFImage *image);







void GIFInitExtension(struct GIFExtension *ext,
                      struct GIFScreen *screen, unsigned int initBufferSize);





void GIFDestroyExtension(struct GIFExtension *ext);







void GIFGetGraphicCtl(struct GIFGraphicCtlExt *graphicExt,
                      struct GIFExtension *ext);






extern void (*GIFError)(const char *message);





extern void (*GIFWarning)(const char *message);
# 9 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxrgif.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 10 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxrgif.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 11 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxrgif.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 12 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxrgif.c" 2


# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxpriv.h" 1
# 17 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxpriv.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 18 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxpriv.h" 2
# 33 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxpriv.h"
int pngx_sig_is_bmp(png_bytep sig, size_t sig_size,
                    png_const_charpp fmt_name_ptr,
                    png_const_charpp fmt_long_name_ptr);
int pngx_read_bmp(png_structp png_ptr, png_infop info_ptr, FILE *stream);


int pngx_sig_is_gif(png_bytep sig, size_t sig_size,
                    png_const_charpp fmt_name_ptr,
                    png_const_charpp fmt_long_name_ptr);
int pngx_read_gif(png_structp png_ptr, png_infop info_ptr, FILE *stream);


int pngx_sig_is_jpeg(png_bytep sig, size_t sig_size,
                     png_const_charpp fmt_name_ptr,
                     png_const_charpp fmt_long_name_ptr);
int pngx_read_jpeg(png_structp png_ptr, png_infop info_ptr, FILE *stream);


int pngx_sig_is_pnm(png_bytep sig, size_t sig_size,
                    png_const_charpp fmt_name_ptr,
                    png_const_charpp fmt_long_name_ptr);
int pngx_read_pnm(png_structp png_ptr, png_infop info_ptr, FILE *stream);


int pngx_sig_is_tiff(png_bytep sig, size_t sig_size,
                     png_const_charpp fmt_name_ptr,
                     png_const_charpp fmt_long_name_ptr);
int pngx_read_tiff(png_structp png_ptr, png_infop info_ptr, FILE *stream);
# 15 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxrgif.c" 2


static const char gif_fmt_name[] = "GIF";
static const char gif_fmt_long_name[] = "Graphics Interchange Format";

static const png_byte gif_sig_gif87a[6] =
   { 0x47, 0x49, 0x46, 0x38, 0x37, 0x61 };
static const png_byte gif_sig_gif89a[6] =
   { 0x47, 0x49, 0x46, 0x38, 0x39, 0x61 };


int
pngx_sig_is_gif(png_bytep sig, size_t sig_size,
                png_const_charpp fmt_name_ptr,
                png_const_charpp fmt_long_name_ptr)
{

   if (sig_size < 6 + 7)
      return -1;
   if (memcmp(sig, gif_sig_gif87a, 6) != 0 &&
       memcmp(sig, gif_sig_gif89a, 6) != 0)
      return 0;


   if (fmt_name_ptr != 0)
      *fmt_name_ptr = gif_fmt_name;
   if (fmt_long_name_ptr != 0)
      *fmt_long_name_ptr = gif_fmt_long_name;
   return 1;
}



static png_structp err_png_ptr;
static struct GIFImage *err_gif_image_ptr;
static struct GIFExtension *err_gif_ext_ptr;

static void
pngx_gif_error(const char *msg)
{
   if (err_gif_image_ptr != 0)
      GIFDestroyImage(err_gif_image_ptr);
   if (err_gif_ext_ptr != 0)
      GIFDestroyExtension(err_gif_ext_ptr);
   png_error(err_png_ptr, msg);
}

static void
pngx_gif_warning(const char *msg)
{
   png_warning(err_png_ptr, msg);
}


static void
pngx_set_gif_palette(png_structp png_ptr, png_infop info_ptr,
   unsigned char *color_table, unsigned int num_colors)
{
   png_color palette[256];
   unsigned int i;

   ((void)0);
   ((void)0);

   for (i = 0; i < num_colors; ++i)
   {
      palette[i].red = color_table[3 * i];
      palette[i].green = color_table[3 * i + 1];
      palette[i].blue = color_table[3 * i + 2];
   }
   png_set_PLTE(png_ptr, info_ptr, palette, (int)num_colors);
}

static void
pngx_set_gif_transparent(png_structp png_ptr, png_infop info_ptr,
   unsigned int transparent)
{
   png_byte trans[256];
   unsigned int i;

   ((void)0);

   for (i = 0; i < transparent; ++i)
      trans[i] = 255;
   trans[transparent] = 0;
   png_set_tRNS(png_ptr, info_ptr, trans, (int)transparent + 1, 0);
}

int
pngx_read_gif(png_structp png_ptr, png_infop info_ptr, FILE *stream)
{

   struct GIFScreen screen;
   struct GIFImage image;
   struct GIFExtension ext;
   struct GIFGraphicCtlExt graphicExt;
   int blockCode;
   unsigned char *colorTable;
   unsigned int numColors;
   unsigned int transparent;
   unsigned int numImages;

   png_uint_32 width, height;
   png_bytepp row_pointers;


   GIFError = pngx_gif_error;
   GIFWarning = pngx_gif_warning;
   err_png_ptr = png_ptr;
   err_gif_image_ptr = 0;
   err_gif_ext_ptr = 0;


   GIFReadScreen(&screen, stream);
   width = screen.Width;
   height = screen.Height;


   png_set_IHDR(png_ptr, info_ptr,
      width, height, 8, (2 | 1),
      0, 0, 0);


   row_pointers = pngx_malloc_rows(png_ptr, info_ptr, (int)screen.Background);


   GIFInitImage(&image, &screen, row_pointers);
   err_gif_image_ptr = &image;
   GIFInitExtension(&ext, &screen, 256);
   err_gif_ext_ptr = &ext;
   numImages = 0;
   transparent = (unsigned int)(-1);


   for ( ; ; )
   {
      blockCode = GIFReadNextBlock(&image, &ext, stream);
      if (blockCode == 0x2c)
      {
         if (image.Rows != 0)
         {

            if (image.InterlaceFlag)
               pngx_set_interlace_type(png_ptr, info_ptr,
                  1);
            GIFGetColorTable(&colorTable, &numColors, &image);
            pngx_set_gif_palette(png_ptr, info_ptr, colorTable, numColors);
            if (transparent < 256)
               pngx_set_gif_transparent(png_ptr, info_ptr, transparent);


            image.Rows = 0;
         }
         ++numImages;
      }
      else if (blockCode == 0x21)
      {
         if (ext.Label == 0xf9)
         {
            GIFGetGraphicCtl(&graphicExt, &ext);
            if (image.Rows != 0 && graphicExt.TransparentFlag)
            {
               if (transparent >= 256)
                  transparent = graphicExt.Transparent;
            }
         }
      }
      else if (blockCode == 0x3b)
         break;
   }

   if (image.Rows != 0)
      png_error(png_ptr, "No image in GIF file");

   GIFDestroyImage(&image);
   GIFDestroyExtension(&ext);
   return numImages;
}
# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxrgif.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxrgif.c"





# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxtern.h" 1
# 12 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxtern.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h" 1
# 330 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/pnglibconf.h" 1
# 331 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h" 2




# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/pngconf.h" 1
# 31 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/pngconf.h"
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
# 32 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/pngconf.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 33 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/pngconf.h" 2
# 46 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/pngconf.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 47 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/pngconf.h" 2
# 481 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/pngconf.h"
   typedef unsigned char png_byte;







   typedef short png_int_16;







   typedef unsigned short png_uint_16;





   typedef int png_int_32;







   typedef unsigned int png_uint_32;
# 523 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/pngconf.h"
typedef size_t png_size_t;
typedef ptrdiff_t png_ptrdiff_t;
# 557 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/pngconf.h"
   typedef size_t png_alloc_size_t;
# 574 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/pngconf.h"
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
# 606 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/pngconf.h"
typedef png_byte * * png_bytepp;
typedef png_uint_32 * * png_uint_32pp;
typedef png_int_32 * * png_int_32pp;
typedef png_uint_16 * * png_uint_16pp;
typedef png_int_16 * * png_int_16pp;
typedef const char * * png_const_charpp;
typedef char * * png_charpp;
typedef png_fixed_point * * png_fixed_point_pp;





typedef char * * * png_charppp;
# 336 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h" 2
# 431 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
typedef char* png_libpng_version_1_6_40;







typedef struct png_struct_def png_struct;
typedef const png_struct * png_const_structp;
typedef png_struct * png_structp;
typedef png_struct * * png_structpp;
# 453 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
typedef struct png_info_def png_info;
typedef png_info * png_infop;
typedef const png_info * png_const_infop;
typedef png_info * * png_infopp;
# 469 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
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
# 600 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
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
# 622 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
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
# 754 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
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
# 775 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
typedef void ( *png_error_ptr) (png_structp, png_const_charp);
typedef void ( *png_rw_ptr) (png_structp, png_bytep, size_t);
typedef void ( *png_flush_ptr) (png_structp);
typedef void ( *png_read_status_ptr) (png_structp, png_uint_32, int)
         ;
typedef void ( *png_write_status_ptr) (png_structp, png_uint_32, int)
         ;
# 867 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
typedef png_voidp ( *png_malloc_ptr) (png_structp, png_alloc_size_t)
                      ;
typedef void ( *png_free_ptr) (png_structp, png_voidp);
# 901 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
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
# 963 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern void ( png_longjmp) (png_const_structrp png_ptr, int val)
                 ;



extern int ( png_reset_zstream) (png_structrp png_ptr);
# 986 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
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
# 1285 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern int ( png_set_interlace_handling) (png_structrp png_ptr);
# 1358 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
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
# 1455 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern void ( png_set_filter) (png_structrp png_ptr, int method, int filters)
                 ;
# 1508 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
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
# 1560 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern void ( png_init_io) (png_structrp png_ptr, png_FILE_p fp);
# 1571 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern void ( png_set_error_fn) (png_structrp png_ptr, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warning_fn)
                                                                           ;


extern png_voidp ( png_get_error_ptr) (png_const_structrp png_ptr);
# 1587 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern void ( png_set_write_fn) (png_structrp png_ptr, png_voidp io_ptr, png_rw_ptr write_data_fn, png_flush_ptr output_flush_fn)
                                                             ;


extern void ( png_set_read_fn) (png_structrp png_ptr, png_voidp io_ptr, png_rw_ptr read_data_fn)
                             ;


extern png_voidp ( png_get_io_ptr) (png_const_structrp png_ptr);

extern void ( png_set_read_status_fn) (png_structrp png_ptr, png_read_status_ptr read_row_fn)
                                     ;

extern void ( png_set_write_status_fn) (png_structrp png_ptr, png_write_status_ptr write_row_fn)
                                       ;
# 1716 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern png_voidp ( png_malloc) (png_const_structrp png_ptr, png_alloc_size_t size)
                                          ;

extern png_voidp ( png_calloc) (png_const_structrp png_ptr, png_alloc_size_t size)
                                          ;


extern png_voidp ( png_malloc_warn) (png_const_structrp png_ptr, png_alloc_size_t size)
                                          ;


extern void ( png_free) (png_const_structrp png_ptr, png_voidp ptr);


extern void ( png_free_data) (png_const_structrp png_ptr, png_inforp info_ptr, png_uint_32 free_me, int num)
                                                       ;
# 1740 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern void ( png_data_freer) (png_const_structrp png_ptr, png_inforp info_ptr, int freer, png_uint_32 mask)
                                                      ;
# 1774 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern void ( png_error) (png_const_structrp png_ptr, png_const_charp error_message)
                                                 ;


extern void ( png_chunk_error) (png_const_structrp png_ptr, png_const_charp error_message)
                                                 ;
# 1790 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern void ( png_warning) (png_const_structrp png_ptr, png_const_charp warning_message)
                                     ;


extern void ( png_chunk_warning) (png_const_structrp png_ptr, png_const_charp warning_message)
                                     ;
# 1804 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern void ( png_benign_error) (png_const_structrp png_ptr, png_const_charp warning_message)
                                     ;



extern void ( png_chunk_benign_error) (png_const_structrp png_ptr, png_const_charp warning_message)
                                     ;


extern void ( png_set_benign_errors) (png_structrp png_ptr, int allowed)
                                        ;
# 1838 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
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
# 2009 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern png_uint_32 ( png_get_hIST) (png_const_structrp png_ptr, png_inforp info_ptr, png_uint_16p *hist)
                                             ;
extern void ( png_set_hIST) (png_const_structrp png_ptr, png_inforp info_ptr, png_const_uint_16p hist)
                                                  ;


extern png_uint_32 ( png_get_IHDR) (png_const_structrp png_ptr, png_const_inforp info_ptr, png_uint_32 *width, png_uint_32 *height, int *bit_depth, int *color_type, int *interlace_method, int *compression_method, int *filter_method)


                                                 ;

extern void ( png_set_IHDR) (png_const_structrp png_ptr, png_inforp info_ptr, png_uint_32 width, png_uint_32 height, int bit_depth, int color_type, int interlace_method, int compression_method, int filter_method)


                       ;
# 2061 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern png_uint_32 ( png_get_PLTE) (png_const_structrp png_ptr, png_inforp info_ptr, png_colorp *palette, int *num_palette)
                                                               ;

extern void ( png_set_PLTE) (png_structrp png_ptr, png_inforp info_ptr, png_const_colorp palette, int num_palette)
                                                                    ;


extern png_uint_32 ( png_get_sBIT) (png_const_structrp png_ptr, png_inforp info_ptr, png_color_8p *sig_bit)
                                                ;



extern void ( png_set_sBIT) (png_const_structrp png_ptr, png_inforp info_ptr, png_const_color_8p sig_bit)
                                                     ;
# 2140 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern png_uint_32 ( png_get_tRNS) (png_const_structrp png_ptr, png_inforp info_ptr, png_bytep *trans_alpha, int *num_trans, png_color_16p *trans_color)

                                ;



extern void ( png_set_tRNS) (png_structrp png_ptr, png_inforp info_ptr, png_const_bytep trans_alpha, int num_trans, png_const_color_16p trans_color)

                                     ;
# 2279 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern void ( png_set_keep_unknown_chunks) (png_structrp png_ptr, int keep, png_const_bytep chunk_list, int num_chunks)
                                                          ;






extern int ( png_handle_as_unknown) (png_const_structrp png_ptr, png_const_bytep chunk_name)
                                ;



extern void ( png_set_unknown_chunks) (png_const_structrp png_ptr, png_inforp info_ptr, png_const_unknown_chunkp unknowns, int num_unknowns)

                      ;
# 2304 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
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
# 2361 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
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
# 2412 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern png_uint_32 ( png_get_io_state) (png_const_structrp png_ptr);





extern png_uint_32 ( png_get_io_chunk_type) (png_const_structrp png_ptr)
                                 ;
# 2544 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern png_uint_32 ( png_get_uint_32) (png_const_bytep buf);
extern png_uint_16 ( png_get_uint_16) (png_const_bytep buf);
extern png_int_32 ( png_get_int_32) (png_const_bytep buf);


extern png_uint_32 ( png_get_uint_31) (png_const_structrp png_ptr, png_const_bytep buf)
                         ;




extern void ( png_save_uint_32) (png_bytep buf, png_uint_32 i);


extern void ( png_save_int_32) (png_bytep buf, png_int_32 i);







extern void ( png_save_uint_16) (png_bytep buf, unsigned int i);
# 2612 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../../third_party/libpng/png.h"
extern void ( png_set_check_for_invalid_index) (png_structrp png_ptr, int allowed)
                                        ;

extern int ( png_get_palette_max) (png_const_structp png_ptr, png_const_infop info_ptr)
                              ;
# 13 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxtern.h" 2
# 47 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxtern.h"
int pngx_read_image(png_structp png_ptr, png_infop info_ptr,
                           png_const_charpp fmt_name_ptr,
                           png_const_charpp fmt_long_name_ptr);
# 7 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxrgif.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxutil.h" 1
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxutil.h"
void pngx_set_compression_type
   (png_structp png_ptr, png_infop info_ptr, int compression_type);
void pngx_set_filter_type
   (png_structp png_ptr, png_infop info_ptr, int filter_type);
void pngx_set_interlace_type
   (png_structp png_ptr, png_infop info_ptr, int interlace_type);



typedef png_alloc_size_t pngx_alloc_size_t;
# 43 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxutil.h"
png_bytepp pngx_malloc_rows
   (png_structp png_ptr, png_infop info_ptr, int filler);
png_bytepp pngx_malloc_rows_extended
   (png_structp png_ptr, png_infop info_ptr,
    pngx_alloc_size_t min_row_size, int filler);
# 8 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxrgif.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../gifread/gifread.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../gifread/gifread.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../gifread/gifread.h" 2
# 54 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../gifread/gifread.h"
struct GIFScreen
{
    unsigned int Width;
    unsigned int Height;
    unsigned int GlobalColorFlag;
    unsigned int ColorResolution;
    unsigned int SortFlag;
    unsigned int GlobalNumColors;
    unsigned int Background;
    unsigned int PixelAspectRatio;
    unsigned char GlobalColorTable[256 * 3];
};




struct GIFImage
{
    struct GIFScreen *Screen;
    unsigned int LeftPos;
    unsigned int TopPos;
    unsigned int Width;
    unsigned int Height;
    unsigned int LocalColorFlag;
    unsigned int InterlaceFlag;
    unsigned int SortFlag;
    unsigned int LocalNumColors;
    unsigned char LocalColorTable[256 * 3];
    unsigned char **Rows;
};




struct GIFExtension
{
    struct GIFScreen *Screen;
    unsigned char *Buffer;
    unsigned int BufferSize;
    unsigned char Label;
};




struct GIFGraphicCtlExt
{
    unsigned int DisposalMethod;
    unsigned int InputFlag;
    unsigned int TransparentFlag;
    unsigned int DelayTime;
    unsigned int Transparent;
};







void GIFReadScreen(struct GIFScreen *screen, FILE *stream);







void GIFInitImage(struct GIFImage *image,
                  struct GIFScreen *screen, unsigned char **rows);





void GIFDestroyImage(struct GIFImage *image);
# 138 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../gifread/gifread.h"
int GIFReadNextBlock(struct GIFImage *image, struct GIFExtension *ext,
                     FILE *stream);
# 148 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/../gifread/gifread.h"
void GIFGetColorTable(unsigned char **colors, unsigned int *numColors,
                      struct GIFImage *image);







void GIFInitExtension(struct GIFExtension *ext,
                      struct GIFScreen *screen, unsigned int initBufferSize);





void GIFDestroyExtension(struct GIFExtension *ext);







void GIFGetGraphicCtl(struct GIFGraphicCtlExt *graphicExt,
                      struct GIFExtension *ext);






extern void (*GIFError)(const char *message);





extern void (*GIFWarning)(const char *message);
# 9 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxrgif.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 10 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxrgif.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 11 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxrgif.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 12 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxrgif.c" 2


# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxpriv.h" 1
# 17 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxpriv.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 18 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxpriv.h" 2
# 33 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxpriv.h"
int pngx_sig_is_bmp(png_bytep sig, size_t sig_size,
                    png_const_charpp fmt_name_ptr,
                    png_const_charpp fmt_long_name_ptr);
int pngx_read_bmp(png_structp png_ptr, png_infop info_ptr, FILE *stream);


int pngx_sig_is_gif(png_bytep sig, size_t sig_size,
                    png_const_charpp fmt_name_ptr,
                    png_const_charpp fmt_long_name_ptr);
int pngx_read_gif(png_structp png_ptr, png_infop info_ptr, FILE *stream);


int pngx_sig_is_jpeg(png_bytep sig, size_t sig_size,
                     png_const_charpp fmt_name_ptr,
                     png_const_charpp fmt_long_name_ptr);
int pngx_read_jpeg(png_structp png_ptr, png_infop info_ptr, FILE *stream);


int pngx_sig_is_pnm(png_bytep sig, size_t sig_size,
                    png_const_charpp fmt_name_ptr,
                    png_const_charpp fmt_long_name_ptr);
int pngx_read_pnm(png_structp png_ptr, png_infop info_ptr, FILE *stream);


int pngx_sig_is_tiff(png_bytep sig, size_t sig_size,
                     png_const_charpp fmt_name_ptr,
                     png_const_charpp fmt_long_name_ptr);
int pngx_read_tiff(png_structp png_ptr, png_infop info_ptr, FILE *stream);
# 15 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/src/pngxtern/pngxrgif.c" 2


static const char gif_fmt_name[] = "GIF";
static const char gif_fmt_long_name[] = "Graphics Interchange Format";

static const png_byte gif_sig_gif87a[6] =
   { 0x47, 0x49, 0x46, 0x38, 0x37, 0x61 };
static const png_byte gif_sig_gif89a[6] =
   { 0x47, 0x49, 0x46, 0x38, 0x39, 0x61 };


int
pngx_sig_is_gif(png_bytep sig, size_t sig_size,
                png_const_charpp fmt_name_ptr,
                png_const_charpp fmt_long_name_ptr)
{

   if (sig_size < 6 + 7)
      return -1;
   if (memcmp(sig, gif_sig_gif87a, 6) != 0 &&
       memcmp(sig, gif_sig_gif89a, 6) != 0)
      return 0;


   if (fmt_name_ptr != 0)
      *fmt_name_ptr = gif_fmt_name;
   if (fmt_long_name_ptr != 0)
      *fmt_long_name_ptr = gif_fmt_long_name;
   return 1;
}



static png_structp err_png_ptr;
static struct GIFImage *err_gif_image_ptr;
static struct GIFExtension *err_gif_ext_ptr;

static void
pngx_gif_error(const char *msg)
{
   if (err_gif_image_ptr != 0)
      GIFDestroyImage(err_gif_image_ptr);
   if (err_gif_ext_ptr != 0)
      GIFDestroyExtension(err_gif_ext_ptr);
   png_error(err_png_ptr, msg);
}

static void
pngx_gif_warning(const char *msg)
{
   png_warning(err_png_ptr, msg);
}


static void
pngx_set_gif_palette(png_structp png_ptr, png_infop info_ptr,
   unsigned char *color_table, unsigned int num_colors)
{
   png_color palette[256];
   unsigned int i;

   ((void)0);
   ((void)0);

   for (i = 0; i < num_colors; ++i)
   {
      palette[i].red = color_table[3 * i];
      palette[i].green = color_table[3 * i + 1];
      palette[i].blue = color_table[3 * i + 2];
   }
   png_set_PLTE(png_ptr, info_ptr, palette, (int)num_colors);
}

static void
pngx_set_gif_transparent(png_structp png_ptr, png_infop info_ptr,
   unsigned int transparent)
{
   png_byte trans[256];
   unsigned int i;

   ((void)0);

   for (i = 0; i < transparent; ++i)
      trans[i] = 255;
   trans[transparent] = 0;
   png_set_tRNS(png_ptr, info_ptr, trans, (int)transparent + 1, 0);
}

int
pngx_read_gif(png_structp png_ptr, png_infop info_ptr, FILE *stream)
{

   struct GIFScreen screen;
   struct GIFImage image;
   struct GIFExtension ext;
   struct GIFGraphicCtlExt graphicExt;
   int blockCode;
   unsigned char *colorTable;
   unsigned int numColors;
   unsigned int transparent;
   unsigned int numImages;

   png_uint_32 width, height;
   png_bytepp row_pointers;


   GIFError = pngx_gif_error;
   GIFWarning = pngx_gif_warning;
   err_png_ptr = png_ptr;
   err_gif_image_ptr = 0;
   err_gif_ext_ptr = 0;


   GIFReadScreen(&screen, stream);
   width = screen.Width;
   height = screen.Height;


   png_set_IHDR(png_ptr, info_ptr,
      width, height, 8, (2 | 1),
      0, 0, 0);


   row_pointers = pngx_malloc_rows(png_ptr, info_ptr, (int)screen.Background);


   GIFInitImage(&image, &screen, row_pointers);
   err_gif_image_ptr = &image;
   GIFInitExtension(&ext, &screen, 256);
   err_gif_ext_ptr = &ext;
   numImages = 0;
   transparent = (unsigned int)(-1);


   for ( ; ; )
   {
      blockCode = GIFReadNextBlock(&image, &ext, stream);
      if (blockCode == 0x2c)
      {
         if (image.Rows != 0)
         {

            if (image.InterlaceFlag)
               pngx_set_interlace_type(png_ptr, info_ptr,
                  1);
            GIFGetColorTable(&colorTable, &numColors, &image);
            pngx_set_gif_palette(png_ptr, info_ptr, colorTable, numColors);
            if (transparent < 256)
               pngx_set_gif_transparent(png_ptr, info_ptr, transparent);


            image.Rows = 0;
         }
         ++numImages;
      }
      else if (blockCode == 0x21)
      {
         if (ext.Label == 0xf9)
         {
            GIFGetGraphicCtl(&graphicExt, &ext);
            if (image.Rows != 0 && graphicExt.TransparentFlag)
            {
               if (transparent >= 256)
                  transparent = graphicExt.Transparent;
            }
         }
      }
      else if (blockCode == 0x3b)
         break;
   }

   if (image.Rows != 0)
      png_error(png_ptr, "No image in GIF file");

   GIFDestroyImage(&image);
   GIFDestroyExtension(&ext);
   return numImages;
}
