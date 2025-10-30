# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/infback.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/infback.c"
# 13 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/infback.c"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zutil.h" 1
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zutil.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h" 1
# 56 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zconf.h" 1
# 254 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zconf.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 2
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
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 2
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
    const Bytef *next_in;
    uInt avail_in;
    uLong total_in;

    Bytef *next_out;
    uInt avail_out;
    uLong total_out;

    const char *msg;
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
                            const unsigned char * *);
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
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zutil.h" 2



# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zutil.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zutil.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zutil.h" 2
# 39 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zutil.h"
typedef unsigned char uch;
typedef uch uchf;
typedef unsigned short ush;
typedef ush ushf;
typedef unsigned long ulg;


# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 1
# 47 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zutil.h" 2
# 56 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zutil.h"
extern const char * const z_errmsg[10];
# 194 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zutil.h"
    extern uLong adler32_combine64(uLong, uLong, off_t);
    extern uLong crc32_combine64(uLong, uLong, off_t);
    extern uLong crc32_combine_gen64(off_t);
# 261 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zutil.h"
   voidpf zcalloc(voidpf opaque, unsigned items,
                                unsigned size);
   void zcfree(voidpf opaque, voidpf ptr);
# 14 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/infback.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/inftrees.h" 1
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/inftrees.h"
typedef struct {
    unsigned char op;
    unsigned char bits;
    unsigned short val;
} code;
# 54 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/inftrees.h"
typedef enum {
    CODES,
    LENS,
    DISTS
} codetype;

int inflate_table(codetype type, unsigned short *lens,
                                unsigned codes, code * *table,
                                unsigned *bits, unsigned short *work);
# 15 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/infback.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/inflate.h" 1
# 20 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/inflate.h"
typedef enum {
    HEAD = 16180,
    FLAGS,
    TIME,
    OS,
    EXLEN,
    EXTRA,
    NAME,
    COMMENT,
    HCRC,
    DICTID,
    DICT,
        TYPE,
        TYPEDO,
        STORED,
        COPY_,
        COPY,
        TABLE,
        LENLENS,
        CODELENS,
            LEN_,
            LEN,
            LENEXT,
            DIST,
            DISTEXT,
            MATCH,
            LIT,
    CHECK,
    LENGTH,
    DONE,
    BAD,
    MEM,
    SYNC
} inflate_mode;
# 82 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/inflate.h"
struct inflate_state {
    z_streamp strm;
    inflate_mode mode;
    int last;
    int wrap;

    int havedict;
    int flags;

    unsigned dmax;
    unsigned long check;
    unsigned long total;
    gz_headerp head;

    unsigned wbits;
    unsigned wsize;
    unsigned whave;
    unsigned wnext;
    unsigned char *window;

    unsigned long hold;
    unsigned bits;

    unsigned length;
    unsigned offset;

    unsigned extra;

    code const *lencode;
    code const *distcode;
    unsigned lenbits;
    unsigned distbits;

    unsigned ncode;
    unsigned nlen;
    unsigned ndist;
    unsigned have;
    code *next;
    unsigned short lens[320];
    unsigned short work[288];
    code codes[(852 +592)];
    int sane;
    int back;
    unsigned was;
};
# 16 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/infback.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/inffast.h" 1
# 11 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/inffast.h"
void inflate_fast(z_streamp strm, unsigned start);
# 17 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/infback.c" 2
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/infback.c"
int inflateBackInit_(z_streamp strm, int windowBits,
                             unsigned char *window, const char *version,
                             int stream_size) {
    struct inflate_state *state;

    if (version == 0 || version[0] != "1.3-optipng"[0] ||
        stream_size != (int)(sizeof(z_stream)))
        return (-6);
    if (strm == 0 || window == 0 ||
        windowBits < 8 || windowBits > 15)
        return (-2);
    strm->msg = 0;
    if (strm->zalloc == (alloc_func)0) {



        strm->zalloc = zcalloc;
        strm->opaque = (voidpf)0;

    }
    if (strm->zfree == (free_func)0)



    strm->zfree = zcfree;

    state = (struct inflate_state *)(*((strm)->zalloc))((strm)->opaque, (1), (sizeof(struct inflate_state)))
                                                                            ;
    if (state == 0) return (-4);
    ;
    strm->state = (struct internal_state *)state;
    state->dmax = 32768U;
    state->wbits = (uInt)windowBits;
    state->wsize = 1U << windowBits;
    state->window = window;
    state->wnext = 0;
    state->whave = 0;
    state->sane = 1;
    return 0;
}
# 76 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/infback.c"
static void fixedtables(struct inflate_state *state) {
# 109 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/infback.c"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/inffixed.h" 1
# 10 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/inffixed.h"
    static const code lenfix[512] = {
        {96,7,0},{0,8,80},{0,8,16},{20,8,115},{18,7,31},{0,8,112},{0,8,48},
        {0,9,192},{16,7,10},{0,8,96},{0,8,32},{0,9,160},{0,8,0},{0,8,128},
        {0,8,64},{0,9,224},{16,7,6},{0,8,88},{0,8,24},{0,9,144},{19,7,59},
        {0,8,120},{0,8,56},{0,9,208},{17,7,17},{0,8,104},{0,8,40},{0,9,176},
        {0,8,8},{0,8,136},{0,8,72},{0,9,240},{16,7,4},{0,8,84},{0,8,20},
        {21,8,227},{19,7,43},{0,8,116},{0,8,52},{0,9,200},{17,7,13},{0,8,100},
        {0,8,36},{0,9,168},{0,8,4},{0,8,132},{0,8,68},{0,9,232},{16,7,8},
        {0,8,92},{0,8,28},{0,9,152},{20,7,83},{0,8,124},{0,8,60},{0,9,216},
        {18,7,23},{0,8,108},{0,8,44},{0,9,184},{0,8,12},{0,8,140},{0,8,76},
        {0,9,248},{16,7,3},{0,8,82},{0,8,18},{21,8,163},{19,7,35},{0,8,114},
        {0,8,50},{0,9,196},{17,7,11},{0,8,98},{0,8,34},{0,9,164},{0,8,2},
        {0,8,130},{0,8,66},{0,9,228},{16,7,7},{0,8,90},{0,8,26},{0,9,148},
        {20,7,67},{0,8,122},{0,8,58},{0,9,212},{18,7,19},{0,8,106},{0,8,42},
        {0,9,180},{0,8,10},{0,8,138},{0,8,74},{0,9,244},{16,7,5},{0,8,86},
        {0,8,22},{64,8,0},{19,7,51},{0,8,118},{0,8,54},{0,9,204},{17,7,15},
        {0,8,102},{0,8,38},{0,9,172},{0,8,6},{0,8,134},{0,8,70},{0,9,236},
        {16,7,9},{0,8,94},{0,8,30},{0,9,156},{20,7,99},{0,8,126},{0,8,62},
        {0,9,220},{18,7,27},{0,8,110},{0,8,46},{0,9,188},{0,8,14},{0,8,142},
        {0,8,78},{0,9,252},{96,7,0},{0,8,81},{0,8,17},{21,8,131},{18,7,31},
        {0,8,113},{0,8,49},{0,9,194},{16,7,10},{0,8,97},{0,8,33},{0,9,162},
        {0,8,1},{0,8,129},{0,8,65},{0,9,226},{16,7,6},{0,8,89},{0,8,25},
        {0,9,146},{19,7,59},{0,8,121},{0,8,57},{0,9,210},{17,7,17},{0,8,105},
        {0,8,41},{0,9,178},{0,8,9},{0,8,137},{0,8,73},{0,9,242},{16,7,4},
        {0,8,85},{0,8,21},{16,8,258},{19,7,43},{0,8,117},{0,8,53},{0,9,202},
        {17,7,13},{0,8,101},{0,8,37},{0,9,170},{0,8,5},{0,8,133},{0,8,69},
        {0,9,234},{16,7,8},{0,8,93},{0,8,29},{0,9,154},{20,7,83},{0,8,125},
        {0,8,61},{0,9,218},{18,7,23},{0,8,109},{0,8,45},{0,9,186},{0,8,13},
        {0,8,141},{0,8,77},{0,9,250},{16,7,3},{0,8,83},{0,8,19},{21,8,195},
        {19,7,35},{0,8,115},{0,8,51},{0,9,198},{17,7,11},{0,8,99},{0,8,35},
        {0,9,166},{0,8,3},{0,8,131},{0,8,67},{0,9,230},{16,7,7},{0,8,91},
        {0,8,27},{0,9,150},{20,7,67},{0,8,123},{0,8,59},{0,9,214},{18,7,19},
        {0,8,107},{0,8,43},{0,9,182},{0,8,11},{0,8,139},{0,8,75},{0,9,246},
        {16,7,5},{0,8,87},{0,8,23},{64,8,0},{19,7,51},{0,8,119},{0,8,55},
        {0,9,206},{17,7,15},{0,8,103},{0,8,39},{0,9,174},{0,8,7},{0,8,135},
        {0,8,71},{0,9,238},{16,7,9},{0,8,95},{0,8,31},{0,9,158},{20,7,99},
        {0,8,127},{0,8,63},{0,9,222},{18,7,27},{0,8,111},{0,8,47},{0,9,190},
        {0,8,15},{0,8,143},{0,8,79},{0,9,254},{96,7,0},{0,8,80},{0,8,16},
        {20,8,115},{18,7,31},{0,8,112},{0,8,48},{0,9,193},{16,7,10},{0,8,96},
        {0,8,32},{0,9,161},{0,8,0},{0,8,128},{0,8,64},{0,9,225},{16,7,6},
        {0,8,88},{0,8,24},{0,9,145},{19,7,59},{0,8,120},{0,8,56},{0,9,209},
        {17,7,17},{0,8,104},{0,8,40},{0,9,177},{0,8,8},{0,8,136},{0,8,72},
        {0,9,241},{16,7,4},{0,8,84},{0,8,20},{21,8,227},{19,7,43},{0,8,116},
        {0,8,52},{0,9,201},{17,7,13},{0,8,100},{0,8,36},{0,9,169},{0,8,4},
        {0,8,132},{0,8,68},{0,9,233},{16,7,8},{0,8,92},{0,8,28},{0,9,153},
        {20,7,83},{0,8,124},{0,8,60},{0,9,217},{18,7,23},{0,8,108},{0,8,44},
        {0,9,185},{0,8,12},{0,8,140},{0,8,76},{0,9,249},{16,7,3},{0,8,82},
        {0,8,18},{21,8,163},{19,7,35},{0,8,114},{0,8,50},{0,9,197},{17,7,11},
        {0,8,98},{0,8,34},{0,9,165},{0,8,2},{0,8,130},{0,8,66},{0,9,229},
        {16,7,7},{0,8,90},{0,8,26},{0,9,149},{20,7,67},{0,8,122},{0,8,58},
        {0,9,213},{18,7,19},{0,8,106},{0,8,42},{0,9,181},{0,8,10},{0,8,138},
        {0,8,74},{0,9,245},{16,7,5},{0,8,86},{0,8,22},{64,8,0},{19,7,51},
        {0,8,118},{0,8,54},{0,9,205},{17,7,15},{0,8,102},{0,8,38},{0,9,173},
        {0,8,6},{0,8,134},{0,8,70},{0,9,237},{16,7,9},{0,8,94},{0,8,30},
        {0,9,157},{20,7,99},{0,8,126},{0,8,62},{0,9,221},{18,7,27},{0,8,110},
        {0,8,46},{0,9,189},{0,8,14},{0,8,142},{0,8,78},{0,9,253},{96,7,0},
        {0,8,81},{0,8,17},{21,8,131},{18,7,31},{0,8,113},{0,8,49},{0,9,195},
        {16,7,10},{0,8,97},{0,8,33},{0,9,163},{0,8,1},{0,8,129},{0,8,65},
        {0,9,227},{16,7,6},{0,8,89},{0,8,25},{0,9,147},{19,7,59},{0,8,121},
        {0,8,57},{0,9,211},{17,7,17},{0,8,105},{0,8,41},{0,9,179},{0,8,9},
        {0,8,137},{0,8,73},{0,9,243},{16,7,4},{0,8,85},{0,8,21},{16,8,258},
        {19,7,43},{0,8,117},{0,8,53},{0,9,203},{17,7,13},{0,8,101},{0,8,37},
        {0,9,171},{0,8,5},{0,8,133},{0,8,69},{0,9,235},{16,7,8},{0,8,93},
        {0,8,29},{0,9,155},{20,7,83},{0,8,125},{0,8,61},{0,9,219},{18,7,23},
        {0,8,109},{0,8,45},{0,9,187},{0,8,13},{0,8,141},{0,8,77},{0,9,251},
        {16,7,3},{0,8,83},{0,8,19},{21,8,195},{19,7,35},{0,8,115},{0,8,51},
        {0,9,199},{17,7,11},{0,8,99},{0,8,35},{0,9,167},{0,8,3},{0,8,131},
        {0,8,67},{0,9,231},{16,7,7},{0,8,91},{0,8,27},{0,9,151},{20,7,67},
        {0,8,123},{0,8,59},{0,9,215},{18,7,19},{0,8,107},{0,8,43},{0,9,183},
        {0,8,11},{0,8,139},{0,8,75},{0,9,247},{16,7,5},{0,8,87},{0,8,23},
        {64,8,0},{19,7,51},{0,8,119},{0,8,55},{0,9,207},{17,7,15},{0,8,103},
        {0,8,39},{0,9,175},{0,8,7},{0,8,135},{0,8,71},{0,9,239},{16,7,9},
        {0,8,95},{0,8,31},{0,9,159},{20,7,99},{0,8,127},{0,8,63},{0,9,223},
        {18,7,27},{0,8,111},{0,8,47},{0,9,191},{0,8,15},{0,8,143},{0,8,79},
        {0,9,255}
    };

    static const code distfix[32] = {
        {16,5,1},{23,5,257},{19,5,17},{27,5,4097},{17,5,5},{25,5,1025},
        {21,5,65},{29,5,16385},{16,5,3},{24,5,513},{20,5,33},{28,5,8193},
        {18,5,9},{26,5,2049},{22,5,129},{64,5,0},{16,5,2},{23,5,385},
        {19,5,25},{27,5,6145},{17,5,7},{25,5,1537},{21,5,97},{29,5,24577},
        {16,5,4},{24,5,769},{20,5,49},{28,5,12289},{18,5,13},{26,5,3073},
        {22,5,193},{64,5,0}
    };
# 110 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/infback.c" 2

    state->lencode = lenfix;
    state->lenbits = 9;
    state->distcode = distfix;
    state->distbits = 5;
}
# 242 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/infback.c"
int inflateBack(z_streamp strm, in_func in, void *in_desc,
                        out_func out, void *out_desc) {
    struct inflate_state *state;
    const unsigned char *next;
    unsigned char *put;
    unsigned have, left;
    unsigned long hold;
    unsigned bits;
    unsigned copy;
    unsigned char *from;
    code here;
    code last;
    unsigned len;
    int ret;
    static const unsigned short order[19] =
        {16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15};


    if (strm == 0 || strm->state == 0)
        return (-2);
    state = (struct inflate_state *)strm->state;


    strm->msg = 0;
    state->mode = TYPE;
    state->last = 0;
    state->whave = 0;
    next = strm->next_in;
    have = next != 0 ? strm->avail_in : 0;
    hold = 0;
    bits = 0;
    put = state->window;
    left = state->wsize;


    for (;;)
        switch (state->mode) {
        case TYPE:

            if (state->last) {
                do { hold >>= bits & 7; bits -= bits & 7; } while (0);
                state->mode = DONE;
                break;
            }
            do { while (bits < (unsigned)(3)) do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0); } while (0);
            state->last = ((unsigned)hold & ((1U << (1)) - 1));
            do { hold >>= (1); bits -= (unsigned)(1); } while (0);
            switch (((unsigned)hold & ((1U << (2)) - 1))) {
            case 0:
               
                                                      ;
                state->mode = STORED;
                break;
            case 1:
                fixedtables(state);
               
                                                      ;
                state->mode = LEN;
                break;
            case 2:
               
                                                      ;
                state->mode = TABLE;
                break;
            case 3:
                strm->msg = (char *)"invalid block type";
                state->mode = BAD;
            }
            do { hold >>= (2); bits -= (unsigned)(2); } while (0);
            break;

        case STORED:

            do { hold >>= bits & 7; bits -= bits & 7; } while (0);
            do { while (bits < (unsigned)(32)) do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0); } while (0);
            if ((hold & 0xffff) != ((hold >> 16) ^ 0xffff)) {
                strm->msg = (char *)"invalid stored block lengths";
                state->mode = BAD;
                break;
            }
            state->length = (unsigned)hold & 0xffff;
           
                                   ;
            do { hold = 0; bits = 0; } while (0);


            while (state->length != 0) {
                copy = state->length;
                do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0);
                do { if (left == 0) { put = state->window; left = state->wsize; state->whave = left; if (out(out_desc, put, left)) { ret = (-5); goto inf_leave; } } } while (0);
                if (copy > have) copy = have;
                if (copy > left) copy = left;
                memcpy(put, next, copy);
                have -= copy;
                next += copy;
                left -= copy;
                put += copy;
                state->length -= copy;
            }
            ;
            state->mode = TYPE;
            break;

        case TABLE:

            do { while (bits < (unsigned)(14)) do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0); } while (0);
            state->nlen = ((unsigned)hold & ((1U << (5)) - 1)) + 257;
            do { hold >>= (5); bits -= (unsigned)(5); } while (0);
            state->ndist = ((unsigned)hold & ((1U << (5)) - 1)) + 1;
            do { hold >>= (5); bits -= (unsigned)(5); } while (0);
            state->ncode = ((unsigned)hold & ((1U << (4)) - 1)) + 4;
            do { hold >>= (4); bits -= (unsigned)(4); } while (0);

            if (state->nlen > 286 || state->ndist > 30) {
                strm->msg = (char *)"too many length or distance symbols";
                state->mode = BAD;
                break;
            }

            ;


            state->have = 0;
            while (state->have < state->ncode) {
                do { while (bits < (unsigned)(3)) do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0); } while (0);
                state->lens[order[state->have++]] = (unsigned short)((unsigned)hold & ((1U << (3)) - 1));
                do { hold >>= (3); bits -= (unsigned)(3); } while (0);
            }
            while (state->have < 19)
                state->lens[order[state->have++]] = 0;
            state->next = state->codes;
            state->lencode = (code const *)(state->next);
            state->lenbits = 7;
            ret = inflate_table(CODES, state->lens, 19, &(state->next),
                                &(state->lenbits), state->work);
            if (ret) {
                strm->msg = (char *)"invalid code lengths set";
                state->mode = BAD;
                break;
            }
            ;


            state->have = 0;
            while (state->have < state->nlen + state->ndist) {
                for (;;) {
                    here = state->lencode[((unsigned)hold & ((1U << (state->lenbits)) - 1))];
                    if ((unsigned)(here.bits) <= bits) break;
                    do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0);
                }
                if (here.val < 16) {
                    do { hold >>= (here.bits); bits -= (unsigned)(here.bits); } while (0);
                    state->lens[state->have++] = here.val;
                }
                else {
                    if (here.val == 16) {
                        do { while (bits < (unsigned)(here.bits + 2)) do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0); } while (0);
                        do { hold >>= (here.bits); bits -= (unsigned)(here.bits); } while (0);
                        if (state->have == 0) {
                            strm->msg = (char *)"invalid bit length repeat";
                            state->mode = BAD;
                            break;
                        }
                        len = (unsigned)(state->lens[state->have - 1]);
                        copy = 3 + ((unsigned)hold & ((1U << (2)) - 1));
                        do { hold >>= (2); bits -= (unsigned)(2); } while (0);
                    }
                    else if (here.val == 17) {
                        do { while (bits < (unsigned)(here.bits + 3)) do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0); } while (0);
                        do { hold >>= (here.bits); bits -= (unsigned)(here.bits); } while (0);
                        len = 0;
                        copy = 3 + ((unsigned)hold & ((1U << (3)) - 1));
                        do { hold >>= (3); bits -= (unsigned)(3); } while (0);
                    }
                    else {
                        do { while (bits < (unsigned)(here.bits + 7)) do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0); } while (0);
                        do { hold >>= (here.bits); bits -= (unsigned)(here.bits); } while (0);
                        len = 0;
                        copy = 11 + ((unsigned)hold & ((1U << (7)) - 1));
                        do { hold >>= (7); bits -= (unsigned)(7); } while (0);
                    }
                    if (state->have + copy > state->nlen + state->ndist) {
                        strm->msg = (char *)"invalid bit length repeat";
                        state->mode = BAD;
                        break;
                    }
                    while (copy--)
                        state->lens[state->have++] = (unsigned short)len;
                }
            }


            if (state->mode == BAD) break;


            if (state->lens[256] == 0) {
                strm->msg = (char *)"invalid code -- missing end-of-block";
                state->mode = BAD;
                break;
            }




            state->next = state->codes;
            state->lencode = (code const *)(state->next);
            state->lenbits = 9;
            ret = inflate_table(LENS, state->lens, state->nlen, &(state->next),
                                &(state->lenbits), state->work);
            if (ret) {
                strm->msg = (char *)"invalid literal/lengths set";
                state->mode = BAD;
                break;
            }
            state->distcode = (code const *)(state->next);
            state->distbits = 6;
            ret = inflate_table(DISTS, state->lens + state->nlen, state->ndist,
                            &(state->next), &(state->distbits), state->work);
            if (ret) {
                strm->msg = (char *)"invalid distances set";
                state->mode = BAD;
                break;
            }
            ;
            state->mode = LEN;


        case LEN:

            if (have >= 6 && left >= 258) {
                do { strm->next_out = put; strm->avail_out = left; strm->next_in = next; strm->avail_in = have; state->hold = hold; state->bits = bits; } while (0);
                if (state->whave < state->wsize)
                    state->whave = state->wsize - left;
                inflate_fast(strm, state->wsize);
                do { put = strm->next_out; left = strm->avail_out; next = strm->next_in; have = strm->avail_in; hold = state->hold; bits = state->bits; } while (0);
                break;
            }


            for (;;) {
                here = state->lencode[((unsigned)hold & ((1U << (state->lenbits)) - 1))];
                if ((unsigned)(here.bits) <= bits) break;
                do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0);
            }
            if (here.op && (here.op & 0xf0) == 0) {
                last = here;
                for (;;) {
                    here = state->lencode[last.val +
                            (((unsigned)hold & ((1U << (last.bits + last.op)) - 1)) >> last.bits)];
                    if ((unsigned)(last.bits + here.bits) <= bits) break;
                    do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0);
                }
                do { hold >>= (last.bits); bits -= (unsigned)(last.bits); } while (0);
            }
            do { hold >>= (here.bits); bits -= (unsigned)(here.bits); } while (0);
            state->length = (unsigned)here.val;


            if (here.op == 0) {
               

                                                                       ;
                do { if (left == 0) { put = state->window; left = state->wsize; state->whave = left; if (out(out_desc, put, left)) { ret = (-5); goto inf_leave; } } } while (0);
                *put++ = (unsigned char)(state->length);
                left--;
                state->mode = LEN;
                break;
            }


            if (here.op & 32) {
                ;
                state->mode = TYPE;
                break;
            }


            if (here.op & 64) {
                strm->msg = (char *)"invalid literal/length code";
                state->mode = BAD;
                break;
            }


            state->extra = (unsigned)(here.op) & 15;
            if (state->extra != 0) {
                do { while (bits < (unsigned)(state->extra)) do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0); } while (0);
                state->length += ((unsigned)hold & ((1U << (state->extra)) - 1));
                do { hold >>= (state->extra); bits -= (unsigned)(state->extra); } while (0);
            }
            ;


            for (;;) {
                here = state->distcode[((unsigned)hold & ((1U << (state->distbits)) - 1))];
                if ((unsigned)(here.bits) <= bits) break;
                do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0);
            }
            if ((here.op & 0xf0) == 0) {
                last = here;
                for (;;) {
                    here = state->distcode[last.val +
                            (((unsigned)hold & ((1U << (last.bits + last.op)) - 1)) >> last.bits)];
                    if ((unsigned)(last.bits + here.bits) <= bits) break;
                    do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0);
                }
                do { hold >>= (last.bits); bits -= (unsigned)(last.bits); } while (0);
            }
            do { hold >>= (here.bits); bits -= (unsigned)(here.bits); } while (0);
            if (here.op & 64) {
                strm->msg = (char *)"invalid distance code";
                state->mode = BAD;
                break;
            }
            state->offset = (unsigned)here.val;


            state->extra = (unsigned)(here.op) & 15;
            if (state->extra != 0) {
                do { while (bits < (unsigned)(state->extra)) do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0); } while (0);
                state->offset += ((unsigned)hold & ((1U << (state->extra)) - 1));
                do { hold >>= (state->extra); bits -= (unsigned)(state->extra); } while (0);
            }
            if (state->offset > state->wsize - (state->whave < state->wsize ?
                                                left : 0)) {
                strm->msg = (char *)"invalid distance too far back";
                state->mode = BAD;
                break;
            }
            ;


            do {
                do { if (left == 0) { put = state->window; left = state->wsize; state->whave = left; if (out(out_desc, put, left)) { ret = (-5); goto inf_leave; } } } while (0);
                copy = state->wsize - state->offset;
                if (copy < left) {
                    from = put + copy;
                    copy = left - copy;
                }
                else {
                    from = put - state->offset;
                    copy = left;
                }
                if (copy > state->length) copy = state->length;
                state->length -= copy;
                left -= copy;
                do {
                    *put++ = *from++;
                } while (--copy);
            } while (state->length != 0);
            break;

        case DONE:

            ret = 1;
            goto inf_leave;

        case BAD:
            ret = (-3);
            goto inf_leave;

        default:

            ret = (-2);
            goto inf_leave;
        }


  inf_leave:
    if (left < state->wsize) {
        if (out(out_desc, state->window, state->wsize - left) &&
            ret == 1)
            ret = (-5);
    }
    strm->next_in = next;
    strm->avail_in = have;
    return ret;
}

int inflateBackEnd(z_streamp strm) {
    if (strm == 0 || strm->state == 0 || strm->zfree == (free_func)0)
        return (-2);
    (*((strm)->zfree))((strm)->opaque, (voidpf)(strm->state));
    strm->state = 0;
    ;
    return 0;
}
# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/infback.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/infback.c"
# 13 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/infback.c"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zutil.h" 1
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zutil.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h" 1
# 56 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zlib.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zconf.h" 1
# 254 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zconf.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 2
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
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 2
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
    const Bytef *next_in;
    uInt avail_in;
    uLong total_in;

    Bytef *next_out;
    uInt avail_out;
    uLong total_out;

    const char *msg;
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
                            const unsigned char * *);
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
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zutil.h" 2



# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zutil.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zutil.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zutil.h" 2
# 39 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zutil.h"
typedef unsigned char uch;
typedef uch uchf;
typedef unsigned short ush;
typedef ush ushf;
typedef unsigned long ulg;


# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 1
# 47 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zutil.h" 2
# 56 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zutil.h"
extern const char * const z_errmsg[10];
# 194 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zutil.h"
    extern uLong adler32_combine64(uLong, uLong, off_t);
    extern uLong crc32_combine64(uLong, uLong, off_t);
    extern uLong crc32_combine_gen64(off_t);
# 261 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/zutil.h"
   voidpf zcalloc(voidpf opaque, unsigned items,
                                unsigned size);
   void zcfree(voidpf opaque, voidpf ptr);
# 14 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/infback.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/inftrees.h" 1
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/inftrees.h"
typedef struct {
    unsigned char op;
    unsigned char bits;
    unsigned short val;
} code;
# 54 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/inftrees.h"
typedef enum {
    CODES,
    LENS,
    DISTS
} codetype;

int inflate_table(codetype type, unsigned short *lens,
                                unsigned codes, code * *table,
                                unsigned *bits, unsigned short *work);
# 15 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/infback.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/inflate.h" 1
# 20 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/inflate.h"
typedef enum {
    HEAD = 16180,
    FLAGS,
    TIME,
    OS,
    EXLEN,
    EXTRA,
    NAME,
    COMMENT,
    HCRC,
    DICTID,
    DICT,
        TYPE,
        TYPEDO,
        STORED,
        COPY_,
        COPY,
        TABLE,
        LENLENS,
        CODELENS,
            LEN_,
            LEN,
            LENEXT,
            DIST,
            DISTEXT,
            MATCH,
            LIT,
    CHECK,
    LENGTH,
    DONE,
    BAD,
    MEM,
    SYNC
} inflate_mode;
# 82 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/inflate.h"
struct inflate_state {
    z_streamp strm;
    inflate_mode mode;
    int last;
    int wrap;

    int havedict;
    int flags;

    unsigned dmax;
    unsigned long check;
    unsigned long total;
    gz_headerp head;

    unsigned wbits;
    unsigned wsize;
    unsigned whave;
    unsigned wnext;
    unsigned char *window;

    unsigned long hold;
    unsigned bits;

    unsigned length;
    unsigned offset;

    unsigned extra;

    code const *lencode;
    code const *distcode;
    unsigned lenbits;
    unsigned distbits;

    unsigned ncode;
    unsigned nlen;
    unsigned ndist;
    unsigned have;
    code *next;
    unsigned short lens[320];
    unsigned short work[288];
    code codes[(852 +592)];
    int sane;
    int back;
    unsigned was;
};
# 16 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/infback.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/inffast.h" 1
# 11 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/inffast.h"
void inflate_fast(z_streamp strm, unsigned start);
# 17 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/infback.c" 2
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/infback.c"
int inflateBackInit_(z_streamp strm, int windowBits,
                             unsigned char *window, const char *version,
                             int stream_size) {
    struct inflate_state *state;

    if (version == 0 || version[0] != "1.3-optipng"[0] ||
        stream_size != (int)(sizeof(z_stream)))
        return (-6);
    if (strm == 0 || window == 0 ||
        windowBits < 8 || windowBits > 15)
        return (-2);
    strm->msg = 0;
    if (strm->zalloc == (alloc_func)0) {



        strm->zalloc = zcalloc;
        strm->opaque = (voidpf)0;

    }
    if (strm->zfree == (free_func)0)



    strm->zfree = zcfree;

    state = (struct inflate_state *)(*((strm)->zalloc))((strm)->opaque, (1), (sizeof(struct inflate_state)))
                                                                            ;
    if (state == 0) return (-4);
    ;
    strm->state = (struct internal_state *)state;
    state->dmax = 32768U;
    state->wbits = (uInt)windowBits;
    state->wsize = 1U << windowBits;
    state->window = window;
    state->wnext = 0;
    state->whave = 0;
    state->sane = 1;
    return 0;
}
# 76 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/infback.c"
static void fixedtables(struct inflate_state *state) {
# 109 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/infback.c"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/inffixed.h" 1
# 10 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/inffixed.h"
    static const code lenfix[512] = {
        {96,7,0},{0,8,80},{0,8,16},{20,8,115},{18,7,31},{0,8,112},{0,8,48},
        {0,9,192},{16,7,10},{0,8,96},{0,8,32},{0,9,160},{0,8,0},{0,8,128},
        {0,8,64},{0,9,224},{16,7,6},{0,8,88},{0,8,24},{0,9,144},{19,7,59},
        {0,8,120},{0,8,56},{0,9,208},{17,7,17},{0,8,104},{0,8,40},{0,9,176},
        {0,8,8},{0,8,136},{0,8,72},{0,9,240},{16,7,4},{0,8,84},{0,8,20},
        {21,8,227},{19,7,43},{0,8,116},{0,8,52},{0,9,200},{17,7,13},{0,8,100},
        {0,8,36},{0,9,168},{0,8,4},{0,8,132},{0,8,68},{0,9,232},{16,7,8},
        {0,8,92},{0,8,28},{0,9,152},{20,7,83},{0,8,124},{0,8,60},{0,9,216},
        {18,7,23},{0,8,108},{0,8,44},{0,9,184},{0,8,12},{0,8,140},{0,8,76},
        {0,9,248},{16,7,3},{0,8,82},{0,8,18},{21,8,163},{19,7,35},{0,8,114},
        {0,8,50},{0,9,196},{17,7,11},{0,8,98},{0,8,34},{0,9,164},{0,8,2},
        {0,8,130},{0,8,66},{0,9,228},{16,7,7},{0,8,90},{0,8,26},{0,9,148},
        {20,7,67},{0,8,122},{0,8,58},{0,9,212},{18,7,19},{0,8,106},{0,8,42},
        {0,9,180},{0,8,10},{0,8,138},{0,8,74},{0,9,244},{16,7,5},{0,8,86},
        {0,8,22},{64,8,0},{19,7,51},{0,8,118},{0,8,54},{0,9,204},{17,7,15},
        {0,8,102},{0,8,38},{0,9,172},{0,8,6},{0,8,134},{0,8,70},{0,9,236},
        {16,7,9},{0,8,94},{0,8,30},{0,9,156},{20,7,99},{0,8,126},{0,8,62},
        {0,9,220},{18,7,27},{0,8,110},{0,8,46},{0,9,188},{0,8,14},{0,8,142},
        {0,8,78},{0,9,252},{96,7,0},{0,8,81},{0,8,17},{21,8,131},{18,7,31},
        {0,8,113},{0,8,49},{0,9,194},{16,7,10},{0,8,97},{0,8,33},{0,9,162},
        {0,8,1},{0,8,129},{0,8,65},{0,9,226},{16,7,6},{0,8,89},{0,8,25},
        {0,9,146},{19,7,59},{0,8,121},{0,8,57},{0,9,210},{17,7,17},{0,8,105},
        {0,8,41},{0,9,178},{0,8,9},{0,8,137},{0,8,73},{0,9,242},{16,7,4},
        {0,8,85},{0,8,21},{16,8,258},{19,7,43},{0,8,117},{0,8,53},{0,9,202},
        {17,7,13},{0,8,101},{0,8,37},{0,9,170},{0,8,5},{0,8,133},{0,8,69},
        {0,9,234},{16,7,8},{0,8,93},{0,8,29},{0,9,154},{20,7,83},{0,8,125},
        {0,8,61},{0,9,218},{18,7,23},{0,8,109},{0,8,45},{0,9,186},{0,8,13},
        {0,8,141},{0,8,77},{0,9,250},{16,7,3},{0,8,83},{0,8,19},{21,8,195},
        {19,7,35},{0,8,115},{0,8,51},{0,9,198},{17,7,11},{0,8,99},{0,8,35},
        {0,9,166},{0,8,3},{0,8,131},{0,8,67},{0,9,230},{16,7,7},{0,8,91},
        {0,8,27},{0,9,150},{20,7,67},{0,8,123},{0,8,59},{0,9,214},{18,7,19},
        {0,8,107},{0,8,43},{0,9,182},{0,8,11},{0,8,139},{0,8,75},{0,9,246},
        {16,7,5},{0,8,87},{0,8,23},{64,8,0},{19,7,51},{0,8,119},{0,8,55},
        {0,9,206},{17,7,15},{0,8,103},{0,8,39},{0,9,174},{0,8,7},{0,8,135},
        {0,8,71},{0,9,238},{16,7,9},{0,8,95},{0,8,31},{0,9,158},{20,7,99},
        {0,8,127},{0,8,63},{0,9,222},{18,7,27},{0,8,111},{0,8,47},{0,9,190},
        {0,8,15},{0,8,143},{0,8,79},{0,9,254},{96,7,0},{0,8,80},{0,8,16},
        {20,8,115},{18,7,31},{0,8,112},{0,8,48},{0,9,193},{16,7,10},{0,8,96},
        {0,8,32},{0,9,161},{0,8,0},{0,8,128},{0,8,64},{0,9,225},{16,7,6},
        {0,8,88},{0,8,24},{0,9,145},{19,7,59},{0,8,120},{0,8,56},{0,9,209},
        {17,7,17},{0,8,104},{0,8,40},{0,9,177},{0,8,8},{0,8,136},{0,8,72},
        {0,9,241},{16,7,4},{0,8,84},{0,8,20},{21,8,227},{19,7,43},{0,8,116},
        {0,8,52},{0,9,201},{17,7,13},{0,8,100},{0,8,36},{0,9,169},{0,8,4},
        {0,8,132},{0,8,68},{0,9,233},{16,7,8},{0,8,92},{0,8,28},{0,9,153},
        {20,7,83},{0,8,124},{0,8,60},{0,9,217},{18,7,23},{0,8,108},{0,8,44},
        {0,9,185},{0,8,12},{0,8,140},{0,8,76},{0,9,249},{16,7,3},{0,8,82},
        {0,8,18},{21,8,163},{19,7,35},{0,8,114},{0,8,50},{0,9,197},{17,7,11},
        {0,8,98},{0,8,34},{0,9,165},{0,8,2},{0,8,130},{0,8,66},{0,9,229},
        {16,7,7},{0,8,90},{0,8,26},{0,9,149},{20,7,67},{0,8,122},{0,8,58},
        {0,9,213},{18,7,19},{0,8,106},{0,8,42},{0,9,181},{0,8,10},{0,8,138},
        {0,8,74},{0,9,245},{16,7,5},{0,8,86},{0,8,22},{64,8,0},{19,7,51},
        {0,8,118},{0,8,54},{0,9,205},{17,7,15},{0,8,102},{0,8,38},{0,9,173},
        {0,8,6},{0,8,134},{0,8,70},{0,9,237},{16,7,9},{0,8,94},{0,8,30},
        {0,9,157},{20,7,99},{0,8,126},{0,8,62},{0,9,221},{18,7,27},{0,8,110},
        {0,8,46},{0,9,189},{0,8,14},{0,8,142},{0,8,78},{0,9,253},{96,7,0},
        {0,8,81},{0,8,17},{21,8,131},{18,7,31},{0,8,113},{0,8,49},{0,9,195},
        {16,7,10},{0,8,97},{0,8,33},{0,9,163},{0,8,1},{0,8,129},{0,8,65},
        {0,9,227},{16,7,6},{0,8,89},{0,8,25},{0,9,147},{19,7,59},{0,8,121},
        {0,8,57},{0,9,211},{17,7,17},{0,8,105},{0,8,41},{0,9,179},{0,8,9},
        {0,8,137},{0,8,73},{0,9,243},{16,7,4},{0,8,85},{0,8,21},{16,8,258},
        {19,7,43},{0,8,117},{0,8,53},{0,9,203},{17,7,13},{0,8,101},{0,8,37},
        {0,9,171},{0,8,5},{0,8,133},{0,8,69},{0,9,235},{16,7,8},{0,8,93},
        {0,8,29},{0,9,155},{20,7,83},{0,8,125},{0,8,61},{0,9,219},{18,7,23},
        {0,8,109},{0,8,45},{0,9,187},{0,8,13},{0,8,141},{0,8,77},{0,9,251},
        {16,7,3},{0,8,83},{0,8,19},{21,8,195},{19,7,35},{0,8,115},{0,8,51},
        {0,9,199},{17,7,11},{0,8,99},{0,8,35},{0,9,167},{0,8,3},{0,8,131},
        {0,8,67},{0,9,231},{16,7,7},{0,8,91},{0,8,27},{0,9,151},{20,7,67},
        {0,8,123},{0,8,59},{0,9,215},{18,7,19},{0,8,107},{0,8,43},{0,9,183},
        {0,8,11},{0,8,139},{0,8,75},{0,9,247},{16,7,5},{0,8,87},{0,8,23},
        {64,8,0},{19,7,51},{0,8,119},{0,8,55},{0,9,207},{17,7,15},{0,8,103},
        {0,8,39},{0,9,175},{0,8,7},{0,8,135},{0,8,71},{0,9,239},{16,7,9},
        {0,8,95},{0,8,31},{0,9,159},{20,7,99},{0,8,127},{0,8,63},{0,9,223},
        {18,7,27},{0,8,111},{0,8,47},{0,9,191},{0,8,15},{0,8,143},{0,8,79},
        {0,9,255}
    };

    static const code distfix[32] = {
        {16,5,1},{23,5,257},{19,5,17},{27,5,4097},{17,5,5},{25,5,1025},
        {21,5,65},{29,5,16385},{16,5,3},{24,5,513},{20,5,33},{28,5,8193},
        {18,5,9},{26,5,2049},{22,5,129},{64,5,0},{16,5,2},{23,5,385},
        {19,5,25},{27,5,6145},{17,5,7},{25,5,1537},{21,5,97},{29,5,24577},
        {16,5,4},{24,5,769},{20,5,49},{28,5,12289},{18,5,13},{26,5,3073},
        {22,5,193},{64,5,0}
    };
# 110 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/infback.c" 2

    state->lencode = lenfix;
    state->lenbits = 9;
    state->distcode = distfix;
    state->distbits = 5;
}
# 242 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/infback.c"
int inflateBack(z_streamp strm, in_func in, void *in_desc,
                        out_func out, void *out_desc) {
    struct inflate_state *state;
    const unsigned char *next;
    unsigned char *put;
    unsigned have, left;
    unsigned long hold;
    unsigned bits;
    unsigned copy;
    unsigned char *from;
    code here;
    code last;
    unsigned len;
    int ret;
    static const unsigned short order[19] =
        {16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15};


    if (strm == 0 || strm->state == 0)
        return (-2);
    state = (struct inflate_state *)strm->state;


    strm->msg = 0;
    state->mode = TYPE;
    state->last = 0;
    state->whave = 0;
    next = strm->next_in;
    have = next != 0 ? strm->avail_in : 0;
    hold = 0;
    bits = 0;
    put = state->window;
    left = state->wsize;


    for (;;)
        switch (state->mode) {
        case TYPE:

            if (state->last) {
                do { hold >>= bits & 7; bits -= bits & 7; } while (0);
                state->mode = DONE;
                break;
            }
            do { while (bits < (unsigned)(3)) do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0); } while (0);
            state->last = ((unsigned)hold & ((1U << (1)) - 1));
            do { hold >>= (1); bits -= (unsigned)(1); } while (0);
            switch (((unsigned)hold & ((1U << (2)) - 1))) {
            case 0:
               
                                                      ;
                state->mode = STORED;
                break;
            case 1:
                fixedtables(state);
               
                                                      ;
                state->mode = LEN;
                break;
            case 2:
               
                                                      ;
                state->mode = TABLE;
                break;
            case 3:
                strm->msg = (char *)"invalid block type";
                state->mode = BAD;
            }
            do { hold >>= (2); bits -= (unsigned)(2); } while (0);
            break;

        case STORED:

            do { hold >>= bits & 7; bits -= bits & 7; } while (0);
            do { while (bits < (unsigned)(32)) do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0); } while (0);
            if ((hold & 0xffff) != ((hold >> 16) ^ 0xffff)) {
                strm->msg = (char *)"invalid stored block lengths";
                state->mode = BAD;
                break;
            }
            state->length = (unsigned)hold & 0xffff;
           
                                   ;
            do { hold = 0; bits = 0; } while (0);


            while (state->length != 0) {
                copy = state->length;
                do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0);
                do { if (left == 0) { put = state->window; left = state->wsize; state->whave = left; if (out(out_desc, put, left)) { ret = (-5); goto inf_leave; } } } while (0);
                if (copy > have) copy = have;
                if (copy > left) copy = left;
                memcpy(put, next, copy);
                have -= copy;
                next += copy;
                left -= copy;
                put += copy;
                state->length -= copy;
            }
            ;
            state->mode = TYPE;
            break;

        case TABLE:

            do { while (bits < (unsigned)(14)) do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0); } while (0);
            state->nlen = ((unsigned)hold & ((1U << (5)) - 1)) + 257;
            do { hold >>= (5); bits -= (unsigned)(5); } while (0);
            state->ndist = ((unsigned)hold & ((1U << (5)) - 1)) + 1;
            do { hold >>= (5); bits -= (unsigned)(5); } while (0);
            state->ncode = ((unsigned)hold & ((1U << (4)) - 1)) + 4;
            do { hold >>= (4); bits -= (unsigned)(4); } while (0);

            if (state->nlen > 286 || state->ndist > 30) {
                strm->msg = (char *)"too many length or distance symbols";
                state->mode = BAD;
                break;
            }

            ;


            state->have = 0;
            while (state->have < state->ncode) {
                do { while (bits < (unsigned)(3)) do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0); } while (0);
                state->lens[order[state->have++]] = (unsigned short)((unsigned)hold & ((1U << (3)) - 1));
                do { hold >>= (3); bits -= (unsigned)(3); } while (0);
            }
            while (state->have < 19)
                state->lens[order[state->have++]] = 0;
            state->next = state->codes;
            state->lencode = (code const *)(state->next);
            state->lenbits = 7;
            ret = inflate_table(CODES, state->lens, 19, &(state->next),
                                &(state->lenbits), state->work);
            if (ret) {
                strm->msg = (char *)"invalid code lengths set";
                state->mode = BAD;
                break;
            }
            ;


            state->have = 0;
            while (state->have < state->nlen + state->ndist) {
                for (;;) {
                    here = state->lencode[((unsigned)hold & ((1U << (state->lenbits)) - 1))];
                    if ((unsigned)(here.bits) <= bits) break;
                    do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0);
                }
                if (here.val < 16) {
                    do { hold >>= (here.bits); bits -= (unsigned)(here.bits); } while (0);
                    state->lens[state->have++] = here.val;
                }
                else {
                    if (here.val == 16) {
                        do { while (bits < (unsigned)(here.bits + 2)) do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0); } while (0);
                        do { hold >>= (here.bits); bits -= (unsigned)(here.bits); } while (0);
                        if (state->have == 0) {
                            strm->msg = (char *)"invalid bit length repeat";
                            state->mode = BAD;
                            break;
                        }
                        len = (unsigned)(state->lens[state->have - 1]);
                        copy = 3 + ((unsigned)hold & ((1U << (2)) - 1));
                        do { hold >>= (2); bits -= (unsigned)(2); } while (0);
                    }
                    else if (here.val == 17) {
                        do { while (bits < (unsigned)(here.bits + 3)) do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0); } while (0);
                        do { hold >>= (here.bits); bits -= (unsigned)(here.bits); } while (0);
                        len = 0;
                        copy = 3 + ((unsigned)hold & ((1U << (3)) - 1));
                        do { hold >>= (3); bits -= (unsigned)(3); } while (0);
                    }
                    else {
                        do { while (bits < (unsigned)(here.bits + 7)) do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0); } while (0);
                        do { hold >>= (here.bits); bits -= (unsigned)(here.bits); } while (0);
                        len = 0;
                        copy = 11 + ((unsigned)hold & ((1U << (7)) - 1));
                        do { hold >>= (7); bits -= (unsigned)(7); } while (0);
                    }
                    if (state->have + copy > state->nlen + state->ndist) {
                        strm->msg = (char *)"invalid bit length repeat";
                        state->mode = BAD;
                        break;
                    }
                    while (copy--)
                        state->lens[state->have++] = (unsigned short)len;
                }
            }


            if (state->mode == BAD) break;


            if (state->lens[256] == 0) {
                strm->msg = (char *)"invalid code -- missing end-of-block";
                state->mode = BAD;
                break;
            }




            state->next = state->codes;
            state->lencode = (code const *)(state->next);
            state->lenbits = 9;
            ret = inflate_table(LENS, state->lens, state->nlen, &(state->next),
                                &(state->lenbits), state->work);
            if (ret) {
                strm->msg = (char *)"invalid literal/lengths set";
                state->mode = BAD;
                break;
            }
            state->distcode = (code const *)(state->next);
            state->distbits = 6;
            ret = inflate_table(DISTS, state->lens + state->nlen, state->ndist,
                            &(state->next), &(state->distbits), state->work);
            if (ret) {
                strm->msg = (char *)"invalid distances set";
                state->mode = BAD;
                break;
            }
            ;
            state->mode = LEN;


        case LEN:

            if (have >= 6 && left >= 258) {
                do { strm->next_out = put; strm->avail_out = left; strm->next_in = next; strm->avail_in = have; state->hold = hold; state->bits = bits; } while (0);
                if (state->whave < state->wsize)
                    state->whave = state->wsize - left;
                inflate_fast(strm, state->wsize);
                do { put = strm->next_out; left = strm->avail_out; next = strm->next_in; have = strm->avail_in; hold = state->hold; bits = state->bits; } while (0);
                break;
            }


            for (;;) {
                here = state->lencode[((unsigned)hold & ((1U << (state->lenbits)) - 1))];
                if ((unsigned)(here.bits) <= bits) break;
                do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0);
            }
            if (here.op && (here.op & 0xf0) == 0) {
                last = here;
                for (;;) {
                    here = state->lencode[last.val +
                            (((unsigned)hold & ((1U << (last.bits + last.op)) - 1)) >> last.bits)];
                    if ((unsigned)(last.bits + here.bits) <= bits) break;
                    do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0);
                }
                do { hold >>= (last.bits); bits -= (unsigned)(last.bits); } while (0);
            }
            do { hold >>= (here.bits); bits -= (unsigned)(here.bits); } while (0);
            state->length = (unsigned)here.val;


            if (here.op == 0) {
               

                                                                       ;
                do { if (left == 0) { put = state->window; left = state->wsize; state->whave = left; if (out(out_desc, put, left)) { ret = (-5); goto inf_leave; } } } while (0);
                *put++ = (unsigned char)(state->length);
                left--;
                state->mode = LEN;
                break;
            }


            if (here.op & 32) {
                ;
                state->mode = TYPE;
                break;
            }


            if (here.op & 64) {
                strm->msg = (char *)"invalid literal/length code";
                state->mode = BAD;
                break;
            }


            state->extra = (unsigned)(here.op) & 15;
            if (state->extra != 0) {
                do { while (bits < (unsigned)(state->extra)) do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0); } while (0);
                state->length += ((unsigned)hold & ((1U << (state->extra)) - 1));
                do { hold >>= (state->extra); bits -= (unsigned)(state->extra); } while (0);
            }
            ;


            for (;;) {
                here = state->distcode[((unsigned)hold & ((1U << (state->distbits)) - 1))];
                if ((unsigned)(here.bits) <= bits) break;
                do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0);
            }
            if ((here.op & 0xf0) == 0) {
                last = here;
                for (;;) {
                    here = state->distcode[last.val +
                            (((unsigned)hold & ((1U << (last.bits + last.op)) - 1)) >> last.bits)];
                    if ((unsigned)(last.bits + here.bits) <= bits) break;
                    do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0);
                }
                do { hold >>= (last.bits); bits -= (unsigned)(last.bits); } while (0);
            }
            do { hold >>= (here.bits); bits -= (unsigned)(here.bits); } while (0);
            if (here.op & 64) {
                strm->msg = (char *)"invalid distance code";
                state->mode = BAD;
                break;
            }
            state->offset = (unsigned)here.val;


            state->extra = (unsigned)(here.op) & 15;
            if (state->extra != 0) {
                do { while (bits < (unsigned)(state->extra)) do { do { if (have == 0) { have = in(in_desc, &next); if (have == 0) { next = 0; ret = (-5); goto inf_leave; } } } while (0); have--; hold += (unsigned long)(*next++) << bits; bits += 8; } while (0); } while (0);
                state->offset += ((unsigned)hold & ((1U << (state->extra)) - 1));
                do { hold >>= (state->extra); bits -= (unsigned)(state->extra); } while (0);
            }
            if (state->offset > state->wsize - (state->whave < state->wsize ?
                                                left : 0)) {
                strm->msg = (char *)"invalid distance too far back";
                state->mode = BAD;
                break;
            }
            ;


            do {
                do { if (left == 0) { put = state->window; left = state->wsize; state->whave = left; if (out(out_desc, put, left)) { ret = (-5); goto inf_leave; } } } while (0);
                copy = state->wsize - state->offset;
                if (copy < left) {
                    from = put + copy;
                    copy = left - copy;
                }
                else {
                    from = put - state->offset;
                    copy = left;
                }
                if (copy > state->length) copy = state->length;
                state->length -= copy;
                left -= copy;
                do {
                    *put++ = *from++;
                } while (--copy);
            } while (state->length != 0);
            break;

        case DONE:

            ret = 1;
            goto inf_leave;

        case BAD:
            ret = (-3);
            goto inf_leave;

        default:

            ret = (-2);
            goto inf_leave;
        }


  inf_leave:
    if (left < state->wsize) {
        if (out(out_desc, state->window, state->wsize - left) &&
            ret == 1)
            ret = (-5);
    }
    strm->next_in = next;
    strm->avail_in = have;
    return ret;
}

int inflateBackEnd(z_streamp strm) {
    if (strm == 0 || strm->state == 0 || strm->zfree == (free_func)0)
        return (-2);
    (*((strm)->zfree))((strm)->opaque, (voidpf)(strm->state));
    strm->state = 0;
    ;
    return 0;
}
