# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzread.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzread.c"





# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzguts.h" 1
# 20 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzguts.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 2
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
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 2
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzguts.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h" 1
# 56 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zconf.h" 1
# 254 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zconf.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 255 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zconf.h" 2
     typedef size_t z_size_t;
# 401 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zconf.h"
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
# 429 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zconf.h" 2
# 439 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zconf.h"
   typedef unsigned z_crc_t;
# 454 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zconf.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/types.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/types.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/types.h" 2
# 455 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zconf.h" 2





# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdarg.h" 1
# 461 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zconf.h" 2
# 492 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zconf.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/unistd.h" 1
# 493 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zconf.h" 2
# 57 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h" 2
# 103 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
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
# 242 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern const char * zlibVersion(void);
# 272 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int deflate(z_streamp strm, int flush);
# 385 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int deflateEnd(z_streamp strm);
# 423 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int inflate(z_streamp strm, int flush);
# 543 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int inflateEnd(z_streamp strm);
# 633 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int deflateSetDictionary(z_streamp strm,
                                         const Bytef *dictionary,
                                         uInt dictLength);
# 677 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int deflateGetDictionary(z_streamp strm,
                                         Bytef *dictionary,
                                         uInt *dictLength);
# 699 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int deflateCopy(z_streamp dest,
                                z_streamp source);
# 717 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int deflateReset(z_streamp strm);
# 728 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int deflateParams(z_streamp strm,
                                  int level,
                                  int strategy);
# 766 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int deflateTune(z_streamp strm,
                                int good_length,
                                int max_lazy,
                                int nice_length,
                                int max_chain);
# 783 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern uLong deflateBound(z_streamp strm,
                                   uLong sourceLen);
# 798 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int deflatePending(z_streamp strm,
                                   unsigned *pending,
                                   int *bits);
# 813 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int deflatePrime(z_streamp strm,
                                 int bits,
                                 int value);
# 830 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int deflateSetHeader(z_streamp strm,
                                     gz_headerp head);
# 910 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int inflateSetDictionary(z_streamp strm,
                                         const Bytef *dictionary,
                                         uInt dictLength);
# 933 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int inflateGetDictionary(z_streamp strm,
                                         Bytef *dictionary,
                                         uInt *dictLength);
# 948 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int inflateSync(z_streamp strm);
# 967 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int inflateCopy(z_streamp dest,
                                z_streamp source);
# 983 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int inflateReset(z_streamp strm);
# 994 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int inflateReset2(z_streamp strm,
                                  int windowBits);
# 1008 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int inflatePrime(z_streamp strm,
                                 int bits,
                                 int value);
# 1029 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern long inflateMark(z_streamp strm);
# 1057 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int inflateGetHeader(z_streamp strm,
                                     gz_headerp head);
# 1119 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
typedef unsigned (*in_func)(void *,
                            unsigned char * *);
typedef int (*out_func)(void *, unsigned char *, unsigned);

extern int inflateBack(z_streamp strm,
                                in_func in, void *in_desc,
                                out_func out, void *out_desc);
# 1193 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int inflateBackEnd(z_streamp strm);







extern uLong zlibCompileFlags(void);
# 1254 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int compress(Bytef *dest, uLongf *destLen,
                             const Bytef *source, uLong sourceLen);
# 1269 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int compress2(Bytef *dest, uLongf *destLen,
                              const Bytef *source, uLong sourceLen,
                              int level);
# 1285 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern uLong compressBound(uLong sourceLen);






extern int uncompress(Bytef *dest, uLongf *destLen,
                               const Bytef *source, uLong sourceLen);
# 1310 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int uncompress2(Bytef *dest, uLongf *destLen,
                                const Bytef *source, uLong *sourceLen);
# 1327 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
typedef struct gzFile_s *gzFile;
# 1367 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern gzFile gzdopen(int fd, const char *mode);
# 1390 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int gzbuffer(gzFile file, unsigned size);
# 1406 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int gzsetparams(gzFile file, int level, int strategy);
# 1417 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int gzread(gzFile file, voidp buf, unsigned len);
# 1447 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern z_size_t gzfread(voidp buf, z_size_t size, z_size_t nitems,
                                 gzFile file);
# 1473 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int gzwrite(gzFile file, voidpc buf, unsigned len);





extern z_size_t gzfwrite(voidpc buf, z_size_t size,
                                  z_size_t nitems, gzFile file);
# 1493 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int gzprintf(gzFile file, const char *format, ...);
# 1508 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int gzputs(gzFile file, const char *s);







extern char * gzgets(gzFile file, char *buf, int len);
# 1530 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int gzputc(gzFile file, int c);





extern int gzgetc(gzFile file);
# 1545 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int gzungetc(int c, gzFile file);
# 1557 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int gzflush(gzFile file, int flush);
# 1592 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int gzrewind(gzFile file);
# 1620 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int gzeof(gzFile file);
# 1635 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int gzdirect(gzFile file);
# 1656 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int gzclose(gzFile file);
# 1669 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int gzclose_r(gzFile file);
extern int gzclose_w(gzFile file);
# 1681 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern const char * gzerror(gzFile file, int *errnum);
# 1697 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern void gzclearerr(gzFile file);
# 1714 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern uLong adler32(uLong adler, const Bytef *buf, uInt len);
# 1734 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern uLong adler32_z(uLong adler, const Bytef *buf,
                                z_size_t len);
# 1752 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern uLong crc32(uLong crc, const Bytef *buf, uInt len);
# 1770 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern uLong crc32_z(uLong crc, const Bytef *buf,
                              z_size_t len);
# 1793 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern uLong crc32_combine_op(uLong crc1, uLong crc2, uLong op);
# 1806 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
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
# 1859 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
struct gzFile_s {
    unsigned have;
    unsigned char *next;
    off_t pos;
};
extern int gzgetc_(gzFile file);
# 1918 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
   extern gzFile gzopen(const char *, const char *);
   extern off_t gzseek(gzFile, off_t, int);
   extern off_t gztell(gzFile);
   extern off_t gzoffset(gzFile);
   extern uLong adler32_combine(uLong, uLong, off_t);
   extern uLong crc32_combine(uLong, uLong, off_t);
   extern uLong crc32_combine_gen(off_t);
# 1936 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
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
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzguts.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzguts.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzguts.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzguts.h" 2





# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/fcntl.h" 1
# 32 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzguts.h" 2
# 131 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzguts.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/errno.h" 1
# 132 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzguts.h" 2
# 140 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzguts.h"
    extern gzFile gzopen64(const char *, const char *);
    extern off_t gzseek64(gzFile, off_t, int);
    extern off_t gztell64(gzFile);
    extern off_t gzoffset64(gzFile);
# 169 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzguts.h"
typedef struct {

    struct gzFile_s x;




    int mode;
    int fd;
    char *path;
    unsigned size;
    unsigned want;
    unsigned char *in;
    unsigned char *out;
    int direct;

    int how;
    off_t start;
    int eof;
    int past;

    int level;
    int strategy;
    int reset;

    off_t skip;
    int seek;

    int err;
    char *msg;

    z_stream strm;
} gz_state;
typedef gz_state *gz_statep;


void gz_error(gz_statep, int, const char *);
# 7 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzread.c" 2





static int gz_load(gz_statep state, unsigned char *buf, unsigned len,
                  unsigned *have) {
    int ret;
    unsigned get, max = ((unsigned)-1 >> 2) + 1;

    *have = 0;
    do {
        get = len - *have;
        if (get > max)
            get = max;
        ret = read(state->fd, buf + *have, get);
        if (ret <= 0)
            break;
        *have += (unsigned)ret;
    } while (*have < len);
    if (ret < 0) {
        gz_error(state, (-1), strerror(errno));
        return -1;
    }
    if (ret == 0)
        state->eof = 1;
    return 0;
}
# 43 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzread.c"
static int gz_avail(gz_statep state) {
    unsigned got;
    z_streamp strm = &(state->strm);

    if (state->err != 0 && state->err != (-5))
        return -1;
    if (state->eof == 0) {
        if (strm->avail_in) {
            unsigned char *p = state->in;
            unsigned const char *q = strm->next_in;
            unsigned n = strm->avail_in;
            do {
                *p++ = *q++;
            } while (--n);
        }
        if (gz_load(state, state->in + strm->avail_in,
                    state->size - strm->avail_in, &got) == -1)
            return -1;
        strm->avail_in += got;
        strm->next_in = state->in;
    }
    return 0;
}
# 76 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzread.c"
static int gz_look(gz_statep state) {
    z_streamp strm = &(state->strm);


    if (state->size == 0) {

        state->in = (unsigned char *)malloc(state->want);
        state->out = (unsigned char *)malloc(state->want << 1);
        if (state->in == 0 || state->out == 0) {
            free(state->out);
            free(state->in);
            gz_error(state, (-4), "out of memory");
            return -1;
        }
        state->size = state->want;


        state->strm.zalloc = 0;
        state->strm.zfree = 0;
        state->strm.opaque = 0;
        state->strm.avail_in = 0;
        state->strm.next_in = 0;
        if (inflateInit2_((&(state->strm)), (15 + 16), "1.3-optipng", (int)sizeof(z_stream)) != 0) {
            free(state->out);
            free(state->in);
            state->size = 0;
            gz_error(state, (-4), "out of memory");
            return -1;
        }
    }


    if (strm->avail_in < 2) {
        if (gz_avail(state) == -1)
            return -1;
        if (strm->avail_in == 0)
            return 0;
    }
# 122 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzread.c"
    if (strm->avail_in > 1 &&
            strm->next_in[0] == 31 && strm->next_in[1] == 139) {
        inflateReset(strm);
        state->how = 2;
        state->direct = 0;
        return 0;
    }



    if (state->direct == 0) {
        strm->avail_in = 0;
        state->eof = 1;
        state->x.have = 0;
        return 0;
    }




    state->x.next = state->out;
    memcpy(state->x.next, strm->next_in, strm->avail_in);
    state->x.have = strm->avail_in;
    strm->avail_in = 0;
    state->how = 1;
    state->direct = 1;
    return 0;
}






static int gz_decomp(gz_statep state) {
    int ret = 0;
    unsigned had;
    z_streamp strm = &(state->strm);


    had = strm->avail_out;
    do {

        if (strm->avail_in == 0 && gz_avail(state) == -1)
            return -1;
        if (strm->avail_in == 0) {
            gz_error(state, (-5), "unexpected end of file");
            break;
        }


        ret = inflate(strm, 0);
        if (ret == (-2) || ret == 2) {
            gz_error(state, (-2),
                     "internal error: inflate stream corrupt");
            return -1;
        }
        if (ret == (-4)) {
            gz_error(state, (-4), "out of memory");
            return -1;
        }
        if (ret == (-3)) {
            gz_error(state, (-3),
                     strm->msg == 0 ? "compressed data error" : strm->msg);
            return -1;
        }
    } while (strm->avail_out && ret != 1);


    state->x.have = had - strm->avail_out;
    state->x.next = strm->next_out - state->x.have;


    if (ret == 1)
        state->how = 0;


    return 0;
}







static int gz_fetch(gz_statep state) {
    z_streamp strm = &(state->strm);

    do {
        switch(state->how) {
        case 0:
            if (gz_look(state) == -1)
                return -1;
            if (state->how == 0)
                return 0;
            break;
        case 1:
            if (gz_load(state, state->out, state->size << 1, &(state->x.have))
                    == -1)
                return -1;
            state->x.next = state->out;
            return 0;
        case 2:
            strm->avail_out = state->size << 1;
            strm->next_out = state->out;
            if (gz_decomp(state) == -1)
                return -1;
        }
    } while (state->x.have == 0 && (!state->eof || strm->avail_in));
    return 0;
}


static int gz_skip(gz_statep state, off_t len) {
    unsigned n;


    while (len)

        if (state->x.have) {
            n = (sizeof(int) == sizeof(off_t) && (state->x.have) > 2147483647) || (off_t)state->x.have > len ?
                (unsigned)len : state->x.have;
            state->x.have -= n;
            state->x.next += n;
            state->x.pos += n;
            len -= n;
        }


        else if (state->eof && state->strm.avail_in == 0)
            break;


        else {

            if (gz_fetch(state) == -1)
                return -1;
        }
    return 0;
}





static z_size_t gz_read(gz_statep state, voidp buf, z_size_t len) {
    z_size_t got;
    unsigned n;


    if (len == 0)
        return 0;


    if (state->seek) {
        state->seek = 0;
        if (gz_skip(state, state->skip) == -1)
            return 0;
    }


    got = 0;
    do {

        n = (unsigned)-1;
        if (n > len)
            n = (unsigned)len;


        if (state->x.have) {
            if (state->x.have < n)
                n = state->x.have;
            memcpy(buf, state->x.next, n);
            state->x.next += n;
            state->x.have -= n;
        }


        else if (state->eof && state->strm.avail_in == 0) {
            state->past = 1;
            break;
        }



        else if (state->how == 0 || n < (state->size << 1)) {

            if (gz_fetch(state) == -1)
                return 0;
            continue;


        }


        else if (state->how == 1) {
            if (gz_load(state, (unsigned char *)buf, n, &n) == -1)
                return 0;
        }


        else {
            state->strm.avail_out = n;
            state->strm.next_out = (unsigned char *)buf;
            if (gz_decomp(state) == -1)
                return 0;
            n = state->x.have;
            state->x.have = 0;
        }


        len -= n;
        buf = (char *)buf + n;
        got += n;
        state->x.pos += n;
    } while (len);


    return got;
}


int gzread(gzFile file, voidp buf, unsigned len) {
    gz_statep state;


    if (file == 0)
        return -1;
    state = (gz_statep)file;


    if (state->mode != 7247 ||
            (state->err != 0 && state->err != (-5)))
        return -1;



    if ((int)len < 0) {
        gz_error(state, (-2), "request does not fit in an int");
        return -1;
    }


    len = (unsigned)gz_read(state, buf, len);


    if (len == 0 && state->err != 0 && state->err != (-5))
        return -1;


    return (int)len;
}


z_size_t gzfread(voidp buf, z_size_t size, z_size_t nitems, gzFile file) {
    z_size_t len;
    gz_statep state;


    if (file == 0)
        return 0;
    state = (gz_statep)file;


    if (state->mode != 7247 ||
            (state->err != 0 && state->err != (-5)))
        return 0;


    len = nitems * size;
    if (size && len / size != nitems) {
        gz_error(state, (-2), "request does not fit in a size_t");
        return 0;
    }


    return len ? gz_read(state, buf, len) / size : 0;
}







int gzgetc(gzFile file) {
    unsigned char buf[1];
    gz_statep state;


    if (file == 0)
        return -1;
    state = (gz_statep)file;


    if (state->mode != 7247 ||
        (state->err != 0 && state->err != (-5)))
        return -1;


    if (state->x.have) {
        state->x.have--;
        state->x.pos++;
        return *(state->x.next)++;
    }


    return gz_read(state, buf, 1) < 1 ? -1 : buf[0];
}

int gzgetc_(gzFile file) {
    return gzgetc(file);
}


int gzungetc(int c, gzFile file) {
    gz_statep state;


    if (file == 0)
        return -1;
    state = (gz_statep)file;


    if (state->mode == 7247 && state->how == 0 && state->x.have == 0)
        (void)gz_look(state);


    if (state->mode != 7247 ||
        (state->err != 0 && state->err != (-5)))
        return -1;


    if (state->seek) {
        state->seek = 0;
        if (gz_skip(state, state->skip) == -1)
            return -1;
    }


    if (c < 0)
        return -1;


    if (state->x.have == 0) {
        state->x.have = 1;
        state->x.next = state->out + (state->size << 1) - 1;
        state->x.next[0] = (unsigned char)c;
        state->x.pos--;
        state->past = 0;
        return c;
    }


    if (state->x.have == (state->size << 1)) {
        gz_error(state, (-3), "out of room to push characters");
        return -1;
    }


    if (state->x.next == state->out) {
        unsigned char *src = state->out + state->x.have;
        unsigned char *dest = state->out + (state->size << 1);
        while (src > state->out)
            *--dest = *--src;
        state->x.next = dest;
    }
    state->x.have++;
    state->x.next--;
    state->x.next[0] = (unsigned char)c;
    state->x.pos--;
    state->past = 0;
    return c;
}


char * gzgets(gzFile file, char *buf, int len) {
    unsigned left, n;
    char *str;
    unsigned char *eol;
    gz_statep state;


    if (file == 0 || buf == 0 || len < 1)
        return 0;
    state = (gz_statep)file;


    if (state->mode != 7247 ||
        (state->err != 0 && state->err != (-5)))
        return 0;


    if (state->seek) {
        state->seek = 0;
        if (gz_skip(state, state->skip) == -1)
            return 0;
    }




    str = buf;
    left = (unsigned)len - 1;
    if (left) do {

        if (state->x.have == 0 && gz_fetch(state) == -1)
            return 0;
        if (state->x.have == 0) {
            state->past = 1;
            break;
        }


        n = state->x.have > left ? left : state->x.have;
        eol = (unsigned char *)memchr(state->x.next, '\n', n);
        if (eol != 0)
            n = (unsigned)(eol - state->x.next) + 1;


        memcpy(buf, state->x.next, n);
        state->x.have -= n;
        state->x.next += n;
        state->x.pos += n;
        left -= n;
        buf += n;
    } while (left && eol == 0);


    if (buf == str)
        return 0;
    buf[0] = 0;
    return str;
}


int gzdirect(gzFile file) {
    gz_statep state;


    if (file == 0)
        return 0;
    state = (gz_statep)file;



    if (state->mode == 7247 && state->how == 0 && state->x.have == 0)
        (void)gz_look(state);


    return state->direct;
}


int gzclose_r(gzFile file) {
    int ret, err;
    gz_statep state;


    if (file == 0)
        return (-2);
    state = (gz_statep)file;


    if (state->mode != 7247)
        return (-2);


    if (state->size) {
        inflateEnd(&(state->strm));
        free(state->out);
        free(state->in);
    }
    err = state->err == (-5) ? (-5) : 0;
    gz_error(state, 0, 0);
    free(state->path);
    ret = close(state->fd);
    free(state);
    return ret ? (-1) : err;
}
# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzread.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzread.c"





# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzguts.h" 1
# 20 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzguts.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 2
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
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 2
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzguts.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h" 1
# 56 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zconf.h" 1
# 254 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zconf.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 255 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zconf.h" 2
     typedef size_t z_size_t;
# 401 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zconf.h"
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
# 429 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zconf.h" 2
# 439 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zconf.h"
   typedef unsigned z_crc_t;
# 454 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zconf.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/types.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/types.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/types.h" 2
# 455 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zconf.h" 2





# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdarg.h" 1
# 461 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zconf.h" 2
# 492 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zconf.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/unistd.h" 1
# 493 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zconf.h" 2
# 57 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h" 2
# 103 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
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
# 242 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern const char * zlibVersion(void);
# 272 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int deflate(z_streamp strm, int flush);
# 385 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int deflateEnd(z_streamp strm);
# 423 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int inflate(z_streamp strm, int flush);
# 543 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int inflateEnd(z_streamp strm);
# 633 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int deflateSetDictionary(z_streamp strm,
                                         const Bytef *dictionary,
                                         uInt dictLength);
# 677 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int deflateGetDictionary(z_streamp strm,
                                         Bytef *dictionary,
                                         uInt *dictLength);
# 699 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int deflateCopy(z_streamp dest,
                                z_streamp source);
# 717 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int deflateReset(z_streamp strm);
# 728 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int deflateParams(z_streamp strm,
                                  int level,
                                  int strategy);
# 766 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int deflateTune(z_streamp strm,
                                int good_length,
                                int max_lazy,
                                int nice_length,
                                int max_chain);
# 783 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern uLong deflateBound(z_streamp strm,
                                   uLong sourceLen);
# 798 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int deflatePending(z_streamp strm,
                                   unsigned *pending,
                                   int *bits);
# 813 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int deflatePrime(z_streamp strm,
                                 int bits,
                                 int value);
# 830 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int deflateSetHeader(z_streamp strm,
                                     gz_headerp head);
# 910 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int inflateSetDictionary(z_streamp strm,
                                         const Bytef *dictionary,
                                         uInt dictLength);
# 933 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int inflateGetDictionary(z_streamp strm,
                                         Bytef *dictionary,
                                         uInt *dictLength);
# 948 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int inflateSync(z_streamp strm);
# 967 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int inflateCopy(z_streamp dest,
                                z_streamp source);
# 983 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int inflateReset(z_streamp strm);
# 994 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int inflateReset2(z_streamp strm,
                                  int windowBits);
# 1008 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int inflatePrime(z_streamp strm,
                                 int bits,
                                 int value);
# 1029 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern long inflateMark(z_streamp strm);
# 1057 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int inflateGetHeader(z_streamp strm,
                                     gz_headerp head);
# 1119 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
typedef unsigned (*in_func)(void *,
                            unsigned char * *);
typedef int (*out_func)(void *, unsigned char *, unsigned);

extern int inflateBack(z_streamp strm,
                                in_func in, void *in_desc,
                                out_func out, void *out_desc);
# 1193 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int inflateBackEnd(z_streamp strm);







extern uLong zlibCompileFlags(void);
# 1254 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int compress(Bytef *dest, uLongf *destLen,
                             const Bytef *source, uLong sourceLen);
# 1269 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int compress2(Bytef *dest, uLongf *destLen,
                              const Bytef *source, uLong sourceLen,
                              int level);
# 1285 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern uLong compressBound(uLong sourceLen);






extern int uncompress(Bytef *dest, uLongf *destLen,
                               const Bytef *source, uLong sourceLen);
# 1310 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int uncompress2(Bytef *dest, uLongf *destLen,
                                const Bytef *source, uLong *sourceLen);
# 1327 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
typedef struct gzFile_s *gzFile;
# 1367 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern gzFile gzdopen(int fd, const char *mode);
# 1390 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int gzbuffer(gzFile file, unsigned size);
# 1406 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int gzsetparams(gzFile file, int level, int strategy);
# 1417 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int gzread(gzFile file, voidp buf, unsigned len);
# 1447 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern z_size_t gzfread(voidp buf, z_size_t size, z_size_t nitems,
                                 gzFile file);
# 1473 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int gzwrite(gzFile file, voidpc buf, unsigned len);





extern z_size_t gzfwrite(voidpc buf, z_size_t size,
                                  z_size_t nitems, gzFile file);
# 1493 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int gzprintf(gzFile file, const char *format, ...);
# 1508 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int gzputs(gzFile file, const char *s);







extern char * gzgets(gzFile file, char *buf, int len);
# 1530 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int gzputc(gzFile file, int c);





extern int gzgetc(gzFile file);
# 1545 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int gzungetc(int c, gzFile file);
# 1557 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int gzflush(gzFile file, int flush);
# 1592 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int gzrewind(gzFile file);
# 1620 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int gzeof(gzFile file);
# 1635 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int gzdirect(gzFile file);
# 1656 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int gzclose(gzFile file);
# 1669 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern int gzclose_r(gzFile file);
extern int gzclose_w(gzFile file);
# 1681 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern const char * gzerror(gzFile file, int *errnum);
# 1697 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern void gzclearerr(gzFile file);
# 1714 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern uLong adler32(uLong adler, const Bytef *buf, uInt len);
# 1734 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern uLong adler32_z(uLong adler, const Bytef *buf,
                                z_size_t len);
# 1752 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern uLong crc32(uLong crc, const Bytef *buf, uInt len);
# 1770 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern uLong crc32_z(uLong crc, const Bytef *buf,
                              z_size_t len);
# 1793 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
extern uLong crc32_combine_op(uLong crc1, uLong crc2, uLong op);
# 1806 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
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
# 1859 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
struct gzFile_s {
    unsigned have;
    unsigned char *next;
    off_t pos;
};
extern int gzgetc_(gzFile file);
# 1918 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
   extern gzFile gzopen(const char *, const char *);
   extern off_t gzseek(gzFile, off_t, int);
   extern off_t gztell(gzFile);
   extern off_t gzoffset(gzFile);
   extern uLong adler32_combine(uLong, uLong, off_t);
   extern uLong crc32_combine(uLong, uLong, off_t);
   extern uLong crc32_combine_gen(off_t);
# 1936 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
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
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzguts.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzguts.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzguts.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzguts.h" 2





# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/fcntl.h" 1
# 32 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzguts.h" 2
# 131 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzguts.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/errno.h" 1
# 132 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzguts.h" 2
# 140 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzguts.h"
    extern gzFile gzopen64(const char *, const char *);
    extern off_t gzseek64(gzFile, off_t, int);
    extern off_t gztell64(gzFile);
    extern off_t gzoffset64(gzFile);
# 169 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzguts.h"
typedef struct {

    struct gzFile_s x;




    int mode;
    int fd;
    char *path;
    unsigned size;
    unsigned want;
    unsigned char *in;
    unsigned char *out;
    int direct;

    int how;
    off_t start;
    int eof;
    int past;

    int level;
    int strategy;
    int reset;

    off_t skip;
    int seek;

    int err;
    char *msg;

    z_stream strm;
} gz_state;
typedef gz_state *gz_statep;


void gz_error(gz_statep, int, const char *);
# 7 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzread.c" 2





static int gz_load(gz_statep state, unsigned char *buf, unsigned len,
                  unsigned *have) {
    int ret;
    unsigned get, max = ((unsigned)-1 >> 2) + 1;

    *have = 0;
    do {
        get = len - *have;
        if (get > max)
            get = max;
        ret = read(state->fd, buf + *have, get);
        if (ret <= 0)
            break;
        *have += (unsigned)ret;
    } while (*have < len);
    if (ret < 0) {
        gz_error(state, (-1), strerror(errno));
        return -1;
    }
    if (ret == 0)
        state->eof = 1;
    return 0;
}
# 43 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzread.c"
static int gz_avail(gz_statep state) {
    unsigned got;
    z_streamp strm = &(state->strm);

    if (state->err != 0 && state->err != (-5))
        return -1;
    if (state->eof == 0) {
        if (strm->avail_in) {
            unsigned char *p = state->in;
            unsigned const char *q = strm->next_in;
            unsigned n = strm->avail_in;
            do {
                *p++ = *q++;
            } while (--n);
        }
        if (gz_load(state, state->in + strm->avail_in,
                    state->size - strm->avail_in, &got) == -1)
            return -1;
        strm->avail_in += got;
        strm->next_in = state->in;
    }
    return 0;
}
# 76 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzread.c"
static int gz_look(gz_statep state) {
    z_streamp strm = &(state->strm);


    if (state->size == 0) {

        state->in = (unsigned char *)malloc(state->want);
        state->out = (unsigned char *)malloc(state->want << 1);
        if (state->in == 0 || state->out == 0) {
            free(state->out);
            free(state->in);
            gz_error(state, (-4), "out of memory");
            return -1;
        }
        state->size = state->want;


        state->strm.zalloc = 0;
        state->strm.zfree = 0;
        state->strm.opaque = 0;
        state->strm.avail_in = 0;
        state->strm.next_in = 0;
        if (inflateInit2_((&(state->strm)), (15 + 16), "1.3-optipng", (int)sizeof(z_stream)) != 0) {
            free(state->out);
            free(state->in);
            state->size = 0;
            gz_error(state, (-4), "out of memory");
            return -1;
        }
    }


    if (strm->avail_in < 2) {
        if (gz_avail(state) == -1)
            return -1;
        if (strm->avail_in == 0)
            return 0;
    }
# 122 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/gzread.c"
    if (strm->avail_in > 1 &&
            strm->next_in[0] == 31 && strm->next_in[1] == 139) {
        inflateReset(strm);
        state->how = 2;
        state->direct = 0;
        return 0;
    }



    if (state->direct == 0) {
        strm->avail_in = 0;
        state->eof = 1;
        state->x.have = 0;
        return 0;
    }




    state->x.next = state->out;
    memcpy(state->x.next, strm->next_in, strm->avail_in);
    state->x.have = strm->avail_in;
    strm->avail_in = 0;
    state->how = 1;
    state->direct = 1;
    return 0;
}






static int gz_decomp(gz_statep state) {
    int ret = 0;
    unsigned had;
    z_streamp strm = &(state->strm);


    had = strm->avail_out;
    do {

        if (strm->avail_in == 0 && gz_avail(state) == -1)
            return -1;
        if (strm->avail_in == 0) {
            gz_error(state, (-5), "unexpected end of file");
            break;
        }


        ret = inflate(strm, 0);
        if (ret == (-2) || ret == 2) {
            gz_error(state, (-2),
                     "internal error: inflate stream corrupt");
            return -1;
        }
        if (ret == (-4)) {
            gz_error(state, (-4), "out of memory");
            return -1;
        }
        if (ret == (-3)) {
            gz_error(state, (-3),
                     strm->msg == 0 ? "compressed data error" : strm->msg);
            return -1;
        }
    } while (strm->avail_out && ret != 1);


    state->x.have = had - strm->avail_out;
    state->x.next = strm->next_out - state->x.have;


    if (ret == 1)
        state->how = 0;


    return 0;
}







static int gz_fetch(gz_statep state) {
    z_streamp strm = &(state->strm);

    do {
        switch(state->how) {
        case 0:
            if (gz_look(state) == -1)
                return -1;
            if (state->how == 0)
                return 0;
            break;
        case 1:
            if (gz_load(state, state->out, state->size << 1, &(state->x.have))
                    == -1)
                return -1;
            state->x.next = state->out;
            return 0;
        case 2:
            strm->avail_out = state->size << 1;
            strm->next_out = state->out;
            if (gz_decomp(state) == -1)
                return -1;
        }
    } while (state->x.have == 0 && (!state->eof || strm->avail_in));
    return 0;
}


static int gz_skip(gz_statep state, off_t len) {
    unsigned n;


    while (len)

        if (state->x.have) {
            n = (sizeof(int) == sizeof(off_t) && (state->x.have) > 2147483647) || (off_t)state->x.have > len ?
                (unsigned)len : state->x.have;
            state->x.have -= n;
            state->x.next += n;
            state->x.pos += n;
            len -= n;
        }


        else if (state->eof && state->strm.avail_in == 0)
            break;


        else {

            if (gz_fetch(state) == -1)
                return -1;
        }
    return 0;
}





static z_size_t gz_read(gz_statep state, voidp buf, z_size_t len) {
    z_size_t got;
    unsigned n;


    if (len == 0)
        return 0;


    if (state->seek) {
        state->seek = 0;
        if (gz_skip(state, state->skip) == -1)
            return 0;
    }


    got = 0;
    do {

        n = (unsigned)-1;
        if (n > len)
            n = (unsigned)len;


        if (state->x.have) {
            if (state->x.have < n)
                n = state->x.have;
            memcpy(buf, state->x.next, n);
            state->x.next += n;
            state->x.have -= n;
        }


        else if (state->eof && state->strm.avail_in == 0) {
            state->past = 1;
            break;
        }



        else if (state->how == 0 || n < (state->size << 1)) {

            if (gz_fetch(state) == -1)
                return 0;
            continue;


        }


        else if (state->how == 1) {
            if (gz_load(state, (unsigned char *)buf, n, &n) == -1)
                return 0;
        }


        else {
            state->strm.avail_out = n;
            state->strm.next_out = (unsigned char *)buf;
            if (gz_decomp(state) == -1)
                return 0;
            n = state->x.have;
            state->x.have = 0;
        }


        len -= n;
        buf = (char *)buf + n;
        got += n;
        state->x.pos += n;
    } while (len);


    return got;
}


int gzread(gzFile file, voidp buf, unsigned len) {
    gz_statep state;


    if (file == 0)
        return -1;
    state = (gz_statep)file;


    if (state->mode != 7247 ||
            (state->err != 0 && state->err != (-5)))
        return -1;



    if ((int)len < 0) {
        gz_error(state, (-2), "request does not fit in an int");
        return -1;
    }


    len = (unsigned)gz_read(state, buf, len);


    if (len == 0 && state->err != 0 && state->err != (-5))
        return -1;


    return (int)len;
}


z_size_t gzfread(voidp buf, z_size_t size, z_size_t nitems, gzFile file) {
    z_size_t len;
    gz_statep state;


    if (file == 0)
        return 0;
    state = (gz_statep)file;


    if (state->mode != 7247 ||
            (state->err != 0 && state->err != (-5)))
        return 0;


    len = nitems * size;
    if (size && len / size != nitems) {
        gz_error(state, (-2), "request does not fit in a size_t");
        return 0;
    }


    return len ? gz_read(state, buf, len) / size : 0;
}







int gzgetc(gzFile file) {
    unsigned char buf[1];
    gz_statep state;


    if (file == 0)
        return -1;
    state = (gz_statep)file;


    if (state->mode != 7247 ||
        (state->err != 0 && state->err != (-5)))
        return -1;


    if (state->x.have) {
        state->x.have--;
        state->x.pos++;
        return *(state->x.next)++;
    }


    return gz_read(state, buf, 1) < 1 ? -1 : buf[0];
}

int gzgetc_(gzFile file) {
    return gzgetc(file);
}


int gzungetc(int c, gzFile file) {
    gz_statep state;


    if (file == 0)
        return -1;
    state = (gz_statep)file;


    if (state->mode == 7247 && state->how == 0 && state->x.have == 0)
        (void)gz_look(state);


    if (state->mode != 7247 ||
        (state->err != 0 && state->err != (-5)))
        return -1;


    if (state->seek) {
        state->seek = 0;
        if (gz_skip(state, state->skip) == -1)
            return -1;
    }


    if (c < 0)
        return -1;


    if (state->x.have == 0) {
        state->x.have = 1;
        state->x.next = state->out + (state->size << 1) - 1;
        state->x.next[0] = (unsigned char)c;
        state->x.pos--;
        state->past = 0;
        return c;
    }


    if (state->x.have == (state->size << 1)) {
        gz_error(state, (-3), "out of room to push characters");
        return -1;
    }


    if (state->x.next == state->out) {
        unsigned char *src = state->out + state->x.have;
        unsigned char *dest = state->out + (state->size << 1);
        while (src > state->out)
            *--dest = *--src;
        state->x.next = dest;
    }
    state->x.have++;
    state->x.next--;
    state->x.next[0] = (unsigned char)c;
    state->x.pos--;
    state->past = 0;
    return c;
}


char * gzgets(gzFile file, char *buf, int len) {
    unsigned left, n;
    char *str;
    unsigned char *eol;
    gz_statep state;


    if (file == 0 || buf == 0 || len < 1)
        return 0;
    state = (gz_statep)file;


    if (state->mode != 7247 ||
        (state->err != 0 && state->err != (-5)))
        return 0;


    if (state->seek) {
        state->seek = 0;
        if (gz_skip(state, state->skip) == -1)
            return 0;
    }




    str = buf;
    left = (unsigned)len - 1;
    if (left) do {

        if (state->x.have == 0 && gz_fetch(state) == -1)
            return 0;
        if (state->x.have == 0) {
            state->past = 1;
            break;
        }


        n = state->x.have > left ? left : state->x.have;
        eol = (unsigned char *)memchr(state->x.next, '\n', n);
        if (eol != 0)
            n = (unsigned)(eol - state->x.next) + 1;


        memcpy(buf, state->x.next, n);
        state->x.have -= n;
        state->x.next += n;
        state->x.pos += n;
        left -= n;
        buf += n;
    } while (left && eol == 0);


    if (buf == str)
        return 0;
    buf[0] = 0;
    return str;
}


int gzdirect(gzFile file) {
    gz_statep state;


    if (file == 0)
        return 0;
    state = (gz_statep)file;



    if (state->mode == 7247 && state->how == 0 && state->x.have == 0)
        (void)gz_look(state);


    return state->direct;
}


int gzclose_r(gzFile file) {
    int ret, err;
    gz_statep state;


    if (file == 0)
        return (-2);
    state = (gz_statep)file;


    if (state->mode != 7247)
        return (-2);


    if (state->size) {
        inflateEnd(&(state->strm));
        free(state->out);
        free(state->in);
    }
    err = state->err == (-5) ? (-5) : 0;
    gz_error(state, 0, 0);
    free(state->path);
    ret = close(state->fd);
    free(state);
    return ret ? (-1) : err;
}
