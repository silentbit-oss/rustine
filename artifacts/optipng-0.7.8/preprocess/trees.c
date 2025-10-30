# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c"
# 37 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/deflate.h" 1
# 16 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/deflate.h"
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
# 17 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/deflate.h" 2
# 68 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/deflate.h"
typedef struct ct_data_s {
    union {
        ush freq;
        ush code;
    } fc;
    union {
        ush dad;
        ush len;
    } dl;
} ct_data;






typedef struct static_tree_desc_s static_tree_desc;

typedef struct tree_desc_s {
    ct_data *dyn_tree;
    int max_code;
    const static_tree_desc *stat_desc;
} tree_desc;

typedef ush Pos;
typedef Pos Posf;
typedef unsigned IPos;





typedef struct internal_state {
    z_streamp strm;
    int status;
    Bytef *pending_buf;
    ulg pending_buf_size;
    Bytef *pending_out;
    ulg pending;
    int wrap;
    gz_headerp gzhead;
    ulg gzindex;
    Byte method;
    int last_flush;



    uInt w_size;
    uInt w_bits;
    uInt w_mask;

    Bytef *window;
# 129 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/deflate.h"
    ulg window_size;




    Posf *prev;





    Posf *head;

    uInt ins_h;
    uInt hash_size;
    uInt hash_bits;
    uInt hash_mask;

    uInt hash_shift;






    long block_start;




    uInt match_length;
    IPos prev_match;
    int match_available;
    uInt strstart;
    uInt match_start;
    uInt lookahead;

    uInt prev_length;




    uInt max_chain_length;





    uInt max_lazy_match;
# 188 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/deflate.h"
    int level;
    int strategy;

    uInt good_match;


    int nice_match;



    struct ct_data_s dyn_ltree[(2*(256 +1+29)+1)];
    struct ct_data_s dyn_dtree[2*30 +1];
    struct ct_data_s bl_tree[2*19 +1];

    struct tree_desc_s l_desc;
    struct tree_desc_s d_desc;
    struct tree_desc_s bl_desc;

    ush bl_count[15 +1];


    int heap[2*(256 +1+29)+1];
    int heap_len;
    int heap_max;




    uch depth[2*(256 +1+29)+1];



    uchf *sym_buf;

    uInt lit_bufsize;
# 242 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/deflate.h"
    uInt sym_next;
    uInt sym_end;

    ulg opt_len;
    ulg static_len;
    uInt matches;
    uInt insert;






    ush bi_buf;



    int bi_valid;




    ulg high_water;






} deflate_state;
# 294 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/deflate.h"
void _tr_init(deflate_state *s);
int _tr_tally(deflate_state *s, unsigned dist, unsigned lc);
void _tr_flush_block(deflate_state *s, charf *buf,
                                   ulg stored_len, int last);
void _tr_flush_bits(deflate_state *s);
void _tr_align(deflate_state *s);
void _tr_stored_block(deflate_state *s, charf *buf,
                                    ulg stored_len, int last);
# 317 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/deflate.h"
  extern const uch _length_code[];
  extern const uch _dist_code[];
# 38 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c" 2
# 62 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c"
static const int extra_lbits[29]
   = {0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0};

static const int extra_dbits[30]
   = {0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13};

static const int extra_blbits[19]
   = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,7};

static const uch bl_order[19]
   = {16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15};
# 114 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.h" 1


static const ct_data static_ltree[(256 +1+29)+2] = {
{{ 12},{ 8}}, {{140},{ 8}}, {{ 76},{ 8}}, {{204},{ 8}}, {{ 44},{ 8}},
{{172},{ 8}}, {{108},{ 8}}, {{236},{ 8}}, {{ 28},{ 8}}, {{156},{ 8}},
{{ 92},{ 8}}, {{220},{ 8}}, {{ 60},{ 8}}, {{188},{ 8}}, {{124},{ 8}},
{{252},{ 8}}, {{ 2},{ 8}}, {{130},{ 8}}, {{ 66},{ 8}}, {{194},{ 8}},
{{ 34},{ 8}}, {{162},{ 8}}, {{ 98},{ 8}}, {{226},{ 8}}, {{ 18},{ 8}},
{{146},{ 8}}, {{ 82},{ 8}}, {{210},{ 8}}, {{ 50},{ 8}}, {{178},{ 8}},
{{114},{ 8}}, {{242},{ 8}}, {{ 10},{ 8}}, {{138},{ 8}}, {{ 74},{ 8}},
{{202},{ 8}}, {{ 42},{ 8}}, {{170},{ 8}}, {{106},{ 8}}, {{234},{ 8}},
{{ 26},{ 8}}, {{154},{ 8}}, {{ 90},{ 8}}, {{218},{ 8}}, {{ 58},{ 8}},
{{186},{ 8}}, {{122},{ 8}}, {{250},{ 8}}, {{ 6},{ 8}}, {{134},{ 8}},
{{ 70},{ 8}}, {{198},{ 8}}, {{ 38},{ 8}}, {{166},{ 8}}, {{102},{ 8}},
{{230},{ 8}}, {{ 22},{ 8}}, {{150},{ 8}}, {{ 86},{ 8}}, {{214},{ 8}},
{{ 54},{ 8}}, {{182},{ 8}}, {{118},{ 8}}, {{246},{ 8}}, {{ 14},{ 8}},
{{142},{ 8}}, {{ 78},{ 8}}, {{206},{ 8}}, {{ 46},{ 8}}, {{174},{ 8}},
{{110},{ 8}}, {{238},{ 8}}, {{ 30},{ 8}}, {{158},{ 8}}, {{ 94},{ 8}},
{{222},{ 8}}, {{ 62},{ 8}}, {{190},{ 8}}, {{126},{ 8}}, {{254},{ 8}},
{{ 1},{ 8}}, {{129},{ 8}}, {{ 65},{ 8}}, {{193},{ 8}}, {{ 33},{ 8}},
{{161},{ 8}}, {{ 97},{ 8}}, {{225},{ 8}}, {{ 17},{ 8}}, {{145},{ 8}},
{{ 81},{ 8}}, {{209},{ 8}}, {{ 49},{ 8}}, {{177},{ 8}}, {{113},{ 8}},
{{241},{ 8}}, {{ 9},{ 8}}, {{137},{ 8}}, {{ 73},{ 8}}, {{201},{ 8}},
{{ 41},{ 8}}, {{169},{ 8}}, {{105},{ 8}}, {{233},{ 8}}, {{ 25},{ 8}},
{{153},{ 8}}, {{ 89},{ 8}}, {{217},{ 8}}, {{ 57},{ 8}}, {{185},{ 8}},
{{121},{ 8}}, {{249},{ 8}}, {{ 5},{ 8}}, {{133},{ 8}}, {{ 69},{ 8}},
{{197},{ 8}}, {{ 37},{ 8}}, {{165},{ 8}}, {{101},{ 8}}, {{229},{ 8}},
{{ 21},{ 8}}, {{149},{ 8}}, {{ 85},{ 8}}, {{213},{ 8}}, {{ 53},{ 8}},
{{181},{ 8}}, {{117},{ 8}}, {{245},{ 8}}, {{ 13},{ 8}}, {{141},{ 8}},
{{ 77},{ 8}}, {{205},{ 8}}, {{ 45},{ 8}}, {{173},{ 8}}, {{109},{ 8}},
{{237},{ 8}}, {{ 29},{ 8}}, {{157},{ 8}}, {{ 93},{ 8}}, {{221},{ 8}},
{{ 61},{ 8}}, {{189},{ 8}}, {{125},{ 8}}, {{253},{ 8}}, {{ 19},{ 9}},
{{275},{ 9}}, {{147},{ 9}}, {{403},{ 9}}, {{ 83},{ 9}}, {{339},{ 9}},
{{211},{ 9}}, {{467},{ 9}}, {{ 51},{ 9}}, {{307},{ 9}}, {{179},{ 9}},
{{435},{ 9}}, {{115},{ 9}}, {{371},{ 9}}, {{243},{ 9}}, {{499},{ 9}},
{{ 11},{ 9}}, {{267},{ 9}}, {{139},{ 9}}, {{395},{ 9}}, {{ 75},{ 9}},
{{331},{ 9}}, {{203},{ 9}}, {{459},{ 9}}, {{ 43},{ 9}}, {{299},{ 9}},
{{171},{ 9}}, {{427},{ 9}}, {{107},{ 9}}, {{363},{ 9}}, {{235},{ 9}},
{{491},{ 9}}, {{ 27},{ 9}}, {{283},{ 9}}, {{155},{ 9}}, {{411},{ 9}},
{{ 91},{ 9}}, {{347},{ 9}}, {{219},{ 9}}, {{475},{ 9}}, {{ 59},{ 9}},
{{315},{ 9}}, {{187},{ 9}}, {{443},{ 9}}, {{123},{ 9}}, {{379},{ 9}},
{{251},{ 9}}, {{507},{ 9}}, {{ 7},{ 9}}, {{263},{ 9}}, {{135},{ 9}},
{{391},{ 9}}, {{ 71},{ 9}}, {{327},{ 9}}, {{199},{ 9}}, {{455},{ 9}},
{{ 39},{ 9}}, {{295},{ 9}}, {{167},{ 9}}, {{423},{ 9}}, {{103},{ 9}},
{{359},{ 9}}, {{231},{ 9}}, {{487},{ 9}}, {{ 23},{ 9}}, {{279},{ 9}},
{{151},{ 9}}, {{407},{ 9}}, {{ 87},{ 9}}, {{343},{ 9}}, {{215},{ 9}},
{{471},{ 9}}, {{ 55},{ 9}}, {{311},{ 9}}, {{183},{ 9}}, {{439},{ 9}},
{{119},{ 9}}, {{375},{ 9}}, {{247},{ 9}}, {{503},{ 9}}, {{ 15},{ 9}},
{{271},{ 9}}, {{143},{ 9}}, {{399},{ 9}}, {{ 79},{ 9}}, {{335},{ 9}},
{{207},{ 9}}, {{463},{ 9}}, {{ 47},{ 9}}, {{303},{ 9}}, {{175},{ 9}},
{{431},{ 9}}, {{111},{ 9}}, {{367},{ 9}}, {{239},{ 9}}, {{495},{ 9}},
{{ 31},{ 9}}, {{287},{ 9}}, {{159},{ 9}}, {{415},{ 9}}, {{ 95},{ 9}},
{{351},{ 9}}, {{223},{ 9}}, {{479},{ 9}}, {{ 63},{ 9}}, {{319},{ 9}},
{{191},{ 9}}, {{447},{ 9}}, {{127},{ 9}}, {{383},{ 9}}, {{255},{ 9}},
{{511},{ 9}}, {{ 0},{ 7}}, {{ 64},{ 7}}, {{ 32},{ 7}}, {{ 96},{ 7}},
{{ 16},{ 7}}, {{ 80},{ 7}}, {{ 48},{ 7}}, {{112},{ 7}}, {{ 8},{ 7}},
{{ 72},{ 7}}, {{ 40},{ 7}}, {{104},{ 7}}, {{ 24},{ 7}}, {{ 88},{ 7}},
{{ 56},{ 7}}, {{120},{ 7}}, {{ 4},{ 7}}, {{ 68},{ 7}}, {{ 36},{ 7}},
{{100},{ 7}}, {{ 20},{ 7}}, {{ 84},{ 7}}, {{ 52},{ 7}}, {{116},{ 7}},
{{ 3},{ 8}}, {{131},{ 8}}, {{ 67},{ 8}}, {{195},{ 8}}, {{ 35},{ 8}},
{{163},{ 8}}, {{ 99},{ 8}}, {{227},{ 8}}
};

static const ct_data static_dtree[30] = {
{{ 0},{ 5}}, {{16},{ 5}}, {{ 8},{ 5}}, {{24},{ 5}}, {{ 4},{ 5}},
{{20},{ 5}}, {{12},{ 5}}, {{28},{ 5}}, {{ 2},{ 5}}, {{18},{ 5}},
{{10},{ 5}}, {{26},{ 5}}, {{ 6},{ 5}}, {{22},{ 5}}, {{14},{ 5}},
{{30},{ 5}}, {{ 1},{ 5}}, {{17},{ 5}}, {{ 9},{ 5}}, {{25},{ 5}},
{{ 5},{ 5}}, {{21},{ 5}}, {{13},{ 5}}, {{29},{ 5}}, {{ 3},{ 5}},
{{19},{ 5}}, {{11},{ 5}}, {{27},{ 5}}, {{ 7},{ 5}}, {{23},{ 5}}
};

const uch _dist_code[512] = {
 0, 1, 2, 3, 4, 4, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8,
 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10,
10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,
11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13,
13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15,
15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 16, 17,
18, 18, 19, 19, 20, 20, 20, 20, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22,
23, 23, 23, 23, 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27,
27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,
27, 27, 27, 27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
28, 28, 28, 28, 28, 28, 28, 28, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29
};

const uch _length_code[258 -3 +1]= {
 0, 1, 2, 3, 4, 5, 6, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 12, 12,
13, 13, 13, 13, 14, 14, 14, 14, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16,
17, 17, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19,
19, 19, 19, 19, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22,
22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 23, 23,
23, 23, 23, 23, 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 26, 26,
26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,
27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 28
};

static const int base_length[29] = {
0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 12, 14, 16, 20, 24, 28, 32, 40, 48, 56,
64, 80, 96, 112, 128, 160, 192, 224, 0
};

static const int base_dist[30] = {
    0, 1, 2, 3, 4, 6, 8, 12, 16, 24,
   32, 48, 64, 96, 128, 192, 256, 384, 512, 768,
 1024, 1536, 2048, 3072, 4096, 6144, 8192, 12288, 16384, 24576
};
# 115 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c" 2


struct static_tree_desc_s {
    const ct_data *static_tree;
    const intf *extra_bits;
    int extra_base;
    int elems;
    int max_length;
};







static const static_tree_desc static_l_desc =
{static_ltree, extra_lbits, 256 +1, (256 +1+29), 15};

static const static_tree_desc static_d_desc =
{static_dtree, extra_dbits, 0, 30, 15};

static const static_tree_desc static_bl_desc =
{(const ct_data *)0, extra_blbits, 0, 19, 7};
# 154 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c"
static unsigned bi_reverse(unsigned code, int len) {
    register unsigned res = 0;
    do {
        res |= code & 1;
        code >>= 1, res <<= 1;
    } while (--len > 0);
    return res >> 1;
}




static void bi_flush(deflate_state *s) {
    if (s->bi_valid == 16) {
        { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; };
        s->bi_buf = 0;
        s->bi_valid = 0;
    } else if (s->bi_valid >= 8) {
        {s->pending_buf[s->pending++] = (Bytef)((Byte)s->bi_buf);};
        s->bi_buf >>= 8;
        s->bi_valid -= 8;
    }
}




static void bi_windup(deflate_state *s) {
    if (s->bi_valid > 8) {
        { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; };
    } else if (s->bi_valid > 0) {
        {s->pending_buf[s->pending++] = (Bytef)((Byte)s->bi_buf);};
    }
    s->bi_buf = 0;
    s->bi_valid = 0;



}
# 202 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c"
static void gen_codes(ct_data *tree, int max_code, ushf *bl_count) {
    ush next_code[15 +1];
    unsigned code = 0;
    int bits;
    int n;




    for (bits = 1; bits <= 15; bits++) {
        code = (code + bl_count[bits - 1]) << 1;
        next_code[bits] = (ush)code;
    }



   
                                      ;
    ;

    for (n = 0; n <= max_code; n++) {
        int len = tree[n].dl.len;
        if (len == 0) continue;

        tree[n].fc.code = (ush)bi_reverse(next_code[len]++, len);

       
                                                                              ;
    }
}
# 294 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c"
static void tr_static_init(void) {
# 373 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c"
}
# 439 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c"
static void init_block(deflate_state *s) {
    int n;


    for (n = 0; n < (256 +1+29); n++) s->dyn_ltree[n].fc.freq = 0;
    for (n = 0; n < 30; n++) s->dyn_dtree[n].fc.freq = 0;
    for (n = 0; n < 19; n++) s->bl_tree[n].fc.freq = 0;

    s->dyn_ltree[256].fc.freq = 1;
    s->opt_len = s->static_len = 0L;
    s->sym_next = s->matches = 0;
}




void _tr_init(deflate_state *s) {
    tr_static_init();

    s->l_desc.dyn_tree = s->dyn_ltree;
    s->l_desc.stat_desc = &static_l_desc;

    s->d_desc.dyn_tree = s->dyn_dtree;
    s->d_desc.stat_desc = &static_d_desc;

    s->bl_desc.dyn_tree = s->bl_tree;
    s->bl_desc.stat_desc = &static_bl_desc;

    s->bi_buf = 0;
    s->bi_valid = 0;






    init_block(s);
}
# 507 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c"
static void pqdownheap(deflate_state *s, ct_data *tree, int k) {
    int v = s->heap[k];
    int j = k << 1;
    while (j <= s->heap_len) {

        if (j < s->heap_len &&
            (tree[s->heap[j + 1]].fc.freq < tree[s->heap[j]].fc.freq || (tree[s->heap[j + 1]].fc.freq == tree[s->heap[j]].fc.freq && s->depth[s->heap[j + 1]] <= s->depth[s->heap[j]]))) {
            j++;
        }

        if ((tree[v].fc.freq < tree[s->heap[j]].fc.freq || (tree[v].fc.freq == tree[s->heap[j]].fc.freq && s->depth[v] <= s->depth[s->heap[j]]))) break;


        s->heap[k] = s->heap[j]; k = j;


        j <<= 1;
    }
    s->heap[k] = v;
}
# 538 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c"
static void gen_bitlen(deflate_state *s, tree_desc *desc) {
    ct_data *tree = desc->dyn_tree;
    int max_code = desc->max_code;
    const ct_data *stree = desc->stat_desc->static_tree;
    const intf *extra = desc->stat_desc->extra_bits;
    int base = desc->stat_desc->extra_base;
    int max_length = desc->stat_desc->max_length;
    int h;
    int n, m;
    int bits;
    int xbits;
    ush f;
    int overflow = 0;

    for (bits = 0; bits <= 15; bits++) s->bl_count[bits] = 0;




    tree[s->heap[s->heap_max]].dl.len = 0;

    for (h = s->heap_max + 1; h < (2*(256 +1+29)+1); h++) {
        n = s->heap[h];
        bits = tree[tree[n].dl.dad].dl.len + 1;
        if (bits > max_length) bits = max_length, overflow++;
        tree[n].dl.len = (ush)bits;


        if (n > max_code) continue;

        s->bl_count[bits]++;
        xbits = 0;
        if (n >= base) xbits = extra[n - base];
        f = tree[n].fc.freq;
        s->opt_len += (ulg)f * (unsigned)(bits + xbits);
        if (stree) s->static_len += (ulg)f * (unsigned)(stree[n].dl.len + xbits);
    }
    if (overflow == 0) return;

    ;



    do {
        bits = max_length - 1;
        while (s->bl_count[bits] == 0) bits--;
        s->bl_count[bits]--;
        s->bl_count[bits + 1] += 2;
        s->bl_count[max_length]--;



        overflow -= 2;
    } while (overflow > 0);






    for (bits = max_length; bits != 0; bits--) {
        n = s->bl_count[bits];
        while (n != 0) {
            m = s->heap[--h];
            if (m > max_code) continue;
            if ((unsigned) tree[m].dl.len != (unsigned) bits) {
                ;
                s->opt_len += ((ulg)bits - tree[m].dl.len) * tree[m].fc.freq;
                tree[m].dl.len = (ush)bits;
            }
            n--;
        }
    }
}
# 625 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c"
static void build_tree(deflate_state *s, tree_desc *desc) {
    ct_data *tree = desc->dyn_tree;
    const ct_data *stree = desc->stat_desc->static_tree;
    int elems = desc->stat_desc->elems;
    int n, m;
    int max_code = -1;
    int node;





    s->heap_len = 0, s->heap_max = (2*(256 +1+29)+1);

    for (n = 0; n < elems; n++) {
        if (tree[n].fc.freq != 0) {
            s->heap[++(s->heap_len)] = max_code = n;
            s->depth[n] = 0;
        } else {
            tree[n].dl.len = 0;
        }
    }






    while (s->heap_len < 2) {
        node = s->heap[++(s->heap_len)] = (max_code < 2 ? ++max_code : 0);
        tree[node].fc.freq = 1;
        s->depth[node] = 0;
        s->opt_len--; if (stree) s->static_len -= stree[node].dl.len;

    }
    desc->max_code = max_code;




    for (n = s->heap_len/2; n >= 1; n--) pqdownheap(s, tree, n);




    node = elems;
    do {
        { n = s->heap[1]; s->heap[1] = s->heap[s->heap_len--]; pqdownheap(s, tree, 1); };
        m = s->heap[1];

        s->heap[--(s->heap_max)] = n;
        s->heap[--(s->heap_max)] = m;


        tree[node].fc.freq = tree[n].fc.freq + tree[m].fc.freq;
        s->depth[node] = (uch)((s->depth[n] >= s->depth[m] ?
                                s->depth[n] : s->depth[m]) + 1);
        tree[n].dl.dad = tree[m].dl.dad = (ush)node;







        s->heap[1] = node++;
        pqdownheap(s, tree, 1);

    } while (s->heap_len >= 2);

    s->heap[--(s->heap_max)] = s->heap[1];




    gen_bitlen(s, (tree_desc *)desc);


    gen_codes ((ct_data *)tree, max_code, s->bl_count);
}





static void scan_tree(deflate_state *s, ct_data *tree, int max_code) {
    int n;
    int prevlen = -1;
    int curlen;
    int nextlen = tree[0].dl.len;
    int count = 0;
    int max_count = 7;
    int min_count = 4;

    if (nextlen == 0) max_count = 138, min_count = 3;
    tree[max_code + 1].dl.len = (ush)0xffff;

    for (n = 0; n <= max_code; n++) {
        curlen = nextlen; nextlen = tree[n + 1].dl.len;
        if (++count < max_count && curlen == nextlen) {
            continue;
        } else if (count < min_count) {
            s->bl_tree[curlen].fc.freq += count;
        } else if (curlen != 0) {
            if (curlen != prevlen) s->bl_tree[curlen].fc.freq++;
            s->bl_tree[16].fc.freq++;
        } else if (count <= 10) {
            s->bl_tree[17].fc.freq++;
        } else {
            s->bl_tree[18].fc.freq++;
        }
        count = 0; prevlen = curlen;
        if (nextlen == 0) {
            max_count = 138, min_count = 3;
        } else if (curlen == nextlen) {
            max_count = 6, min_count = 3;
        } else {
            max_count = 7, min_count = 4;
        }
    }
}





static void send_tree(deflate_state *s, ct_data *tree, int max_code) {
    int n;
    int prevlen = -1;
    int curlen;
    int nextlen = tree[0].dl.len;
    int count = 0;
    int max_count = 7;
    int min_count = 4;


    if (nextlen == 0) max_count = 138, min_count = 3;

    for (n = 0; n <= max_code; n++) {
        curlen = nextlen; nextlen = tree[n + 1].dl.len;
        if (++count < max_count && curlen == nextlen) {
            continue;
        } else if (count < min_count) {
            do { { int len = s->bl_tree[curlen].dl.len; if (s->bi_valid > (int)16 - len) { int val = (int)s->bl_tree[curlen].fc.code; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(s->bl_tree[curlen].fc.code) << s->bi_valid; s->bi_valid += len; }}; } while (--count != 0);

        } else if (curlen != 0) {
            if (curlen != prevlen) {
                { int len = s->bl_tree[curlen].dl.len; if (s->bi_valid > (int)16 - len) { int val = (int)s->bl_tree[curlen].fc.code; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(s->bl_tree[curlen].fc.code) << s->bi_valid; s->bi_valid += len; }}; count--;
            }
            ;
            { int len = s->bl_tree[16].dl.len; if (s->bi_valid > (int)16 - len) { int val = (int)s->bl_tree[16].fc.code; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(s->bl_tree[16].fc.code) << s->bi_valid; s->bi_valid += len; }}; { int len = 2; if (s->bi_valid > (int)16 - len) { int val = (int)count - 3; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(count - 3) << s->bi_valid; s->bi_valid += len; }};

        } else if (count <= 10) {
            { int len = s->bl_tree[17].dl.len; if (s->bi_valid > (int)16 - len) { int val = (int)s->bl_tree[17].fc.code; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(s->bl_tree[17].fc.code) << s->bi_valid; s->bi_valid += len; }}; { int len = 3; if (s->bi_valid > (int)16 - len) { int val = (int)count - 3; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(count - 3) << s->bi_valid; s->bi_valid += len; }};

        } else {
            { int len = s->bl_tree[18].dl.len; if (s->bi_valid > (int)16 - len) { int val = (int)s->bl_tree[18].fc.code; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(s->bl_tree[18].fc.code) << s->bi_valid; s->bi_valid += len; }}; { int len = 7; if (s->bi_valid > (int)16 - len) { int val = (int)count - 11; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(count - 11) << s->bi_valid; s->bi_valid += len; }};
        }
        count = 0; prevlen = curlen;
        if (nextlen == 0) {
            max_count = 138, min_count = 3;
        } else if (curlen == nextlen) {
            max_count = 6, min_count = 3;
        } else {
            max_count = 7, min_count = 4;
        }
    }
}





static int build_bl_tree(deflate_state *s) {
    int max_blindex;


    scan_tree(s, (ct_data *)s->dyn_ltree, s->l_desc.max_code);
    scan_tree(s, (ct_data *)s->dyn_dtree, s->d_desc.max_code);


    build_tree(s, (tree_desc *)(&(s->bl_desc)));
# 815 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c"
    for (max_blindex = 19 -1; max_blindex >= 3; max_blindex--) {
        if (s->bl_tree[bl_order[max_blindex]].dl.len != 0) break;
    }

    s->opt_len += 3*((ulg)max_blindex + 1) + 5 + 5 + 4;
   
                                       ;

    return max_blindex;
}






static void send_all_trees(deflate_state *s, int lcodes, int dcodes,
                          int blcodes) {
    int rank;

    ;
   
                             ;
    ;
    { int len = 5; if (s->bi_valid > (int)16 - len) { int val = (int)lcodes - 257; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(lcodes - 257) << s->bi_valid; s->bi_valid += len; }};
    { int len = 5; if (s->bi_valid > (int)16 - len) { int val = (int)dcodes - 1; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(dcodes - 1) << s->bi_valid; s->bi_valid += len; }};
    { int len = 4; if (s->bi_valid > (int)16 - len) { int val = (int)blcodes - 4; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(blcodes - 4) << s->bi_valid; s->bi_valid += len; }};
    for (rank = 0; rank < blcodes; rank++) {
        ;
        { int len = 3; if (s->bi_valid > (int)16 - len) { int val = (int)s->bl_tree[bl_order[rank]].dl.len; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(s->bl_tree[bl_order[rank]].dl.len) << s->bi_valid; s->bi_valid += len; }};
    }
    ;

    send_tree(s, (ct_data *)s->dyn_ltree, lcodes - 1);
    ;

    send_tree(s, (ct_data *)s->dyn_dtree, dcodes - 1);
    ;
}




void _tr_stored_block(deflate_state *s, charf *buf,
                                    ulg stored_len, int last) {
    { int len = 3; if (s->bi_valid > (int)16 - len) { int val = (int)(0<<1) + last; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)((0<<1) + last) << s->bi_valid; s->bi_valid += len; }};
    bi_windup(s);
    { {s->pending_buf[s->pending++] = (Bytef)((uch)(((ush)stored_len) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)((ush)stored_len) >> 8));}; };
    { {s->pending_buf[s->pending++] = (Bytef)((uch)(((ush)~stored_len) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)((ush)~stored_len) >> 8));}; };
    if (stored_len)
        memcpy(s->pending_buf + s->pending, (Bytef *)buf, stored_len);
    s->pending += stored_len;






}




void _tr_flush_bits(deflate_state *s) {
    bi_flush(s);
}





void _tr_align(deflate_state *s) {
    { int len = 3; if (s->bi_valid > (int)16 - len) { int val = (int)1<<1; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(1<<1) << s->bi_valid; s->bi_valid += len; }};
    { int len = static_ltree[256].dl.len; if (s->bi_valid > (int)16 - len) { int val = (int)static_ltree[256].fc.code; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(static_ltree[256].fc.code) << s->bi_valid; s->bi_valid += len; }};



    bi_flush(s);
}




static void compress_block(deflate_state *s, const ct_data *ltree,
                          const ct_data *dtree) {
    unsigned dist;
    int lc;
    unsigned sx = 0;
    unsigned code;
    int extra;

    if (s->sym_next != 0) do {
        dist = s->sym_buf[sx++] & 0xff;
        dist += (unsigned)(s->sym_buf[sx++] & 0xff) << 8;
        lc = s->sym_buf[sx++];
        if (dist == 0) {
            { int len = ltree[lc].dl.len; if (s->bi_valid > (int)16 - len) { int val = (int)ltree[lc].fc.code; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(ltree[lc].fc.code) << s->bi_valid; s->bi_valid += len; }};
            ;
        } else {

            code = _length_code[lc];
            { int len = ltree[code + 256 + 1].dl.len; if (s->bi_valid > (int)16 - len) { int val = (int)ltree[code + 256 + 1].fc.code; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(ltree[code + 256 + 1].fc.code) << s->bi_valid; s->bi_valid += len; }};
            extra = extra_lbits[code];
            if (extra != 0) {
                lc -= base_length[code];
                { int len = extra; if (s->bi_valid > (int)16 - len) { int val = (int)lc; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(lc) << s->bi_valid; s->bi_valid += len; }};
            }
            dist--;
            code = ((dist) < 256 ? _dist_code[dist] : _dist_code[256+((dist)>>7)]);
            ;

            { int len = dtree[code].dl.len; if (s->bi_valid > (int)16 - len) { int val = (int)dtree[code].fc.code; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(dtree[code].fc.code) << s->bi_valid; s->bi_valid += len; }};
            extra = extra_dbits[code];
            if (extra != 0) {
                dist -= (unsigned)base_dist[code];
                { int len = extra; if (s->bi_valid > (int)16 - len) { int val = (int)dist; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(dist) << s->bi_valid; s->bi_valid += len; }};
            }
        }


        ;

    } while (sx < s->sym_next);

    { int len = ltree[256].dl.len; if (s->bi_valid > (int)16 - len) { int val = (int)ltree[256].fc.code; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(ltree[256].fc.code) << s->bi_valid; s->bi_valid += len; }};
}
# 955 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c"
static int detect_data_type(deflate_state *s) {




    unsigned long block_mask = 0xf3ffc07fUL;
    int n;


    for (n = 0; n <= 31; n++, block_mask >>= 1)
        if ((block_mask & 1) && (s->dyn_ltree[n].fc.freq != 0))
            return 0;


    if (s->dyn_ltree[9].fc.freq != 0 || s->dyn_ltree[10].fc.freq != 0
            || s->dyn_ltree[13].fc.freq != 0)
        return 1;
    for (n = 32; n < 256; n++)
        if (s->dyn_ltree[n].fc.freq != 0)
            return 1;




    return 0;
}





void _tr_flush_block(deflate_state *s, charf *buf,
                                   ulg stored_len, int last) {
    ulg opt_lenb, static_lenb;
    int max_blindex = 0;


    if (s->level > 0) {


        if (s->strm->data_type == 2)
            s->strm->data_type = detect_data_type(s);


        build_tree(s, (tree_desc *)(&(s->l_desc)));
       
                               ;

        build_tree(s, (tree_desc *)(&(s->d_desc)));
       
                               ;







        max_blindex = build_bl_tree(s);


        opt_lenb = (s->opt_len + 3 + 7) >> 3;
        static_lenb = (s->static_len + 3 + 7) >> 3;

       

                                 ;


        if (static_lenb <= opt_lenb || s->strategy == 4)

            opt_lenb = static_lenb;

    } else {
        ;
        opt_lenb = static_lenb = stored_len + 5;
    }




    if (stored_len + 4 <= opt_lenb && buf != (char*)0) {
# 1045 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c"
        _tr_stored_block(s, buf, stored_len, last);

    } else if (static_lenb == opt_lenb) {
        { int len = 3; if (s->bi_valid > (int)16 - len) { int val = (int)(1<<1) + last; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)((1<<1) + last) << s->bi_valid; s->bi_valid += len; }};
        compress_block(s, (const ct_data *)static_ltree,
                       (const ct_data *)static_dtree);



    } else {
        { int len = 3; if (s->bi_valid > (int)16 - len) { int val = (int)(2<<1) + last; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)((2<<1) + last) << s->bi_valid; s->bi_valid += len; }};
        send_all_trees(s, s->l_desc.max_code + 1, s->d_desc.max_code + 1,
                       max_blindex + 1);
        compress_block(s, (const ct_data *)s->dyn_ltree,
                       (const ct_data *)s->dyn_dtree);



    }
    ;



    init_block(s);

    if (last) {
        bi_windup(s);



    }
   
                                       ;
}





int _tr_tally(deflate_state *s, unsigned dist, unsigned lc) {
    s->sym_buf[s->sym_next++] = (uch)dist;
    s->sym_buf[s->sym_next++] = (uch)(dist >> 8);
    s->sym_buf[s->sym_next++] = (uch)lc;
    if (dist == 0) {

        s->dyn_ltree[lc].fc.freq++;
    } else {
        s->matches++;

        dist--;
       

                                                                         ;

        s->dyn_ltree[_length_code[lc] + 256 + 1].fc.freq++;
        s->dyn_dtree[((dist) < 256 ? _dist_code[dist] : _dist_code[256+((dist)>>7)])].fc.freq++;
    }
    return (s->sym_next == s->sym_end);
}
# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c"
# 37 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/deflate.h" 1
# 16 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/deflate.h"
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
# 17 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/deflate.h" 2
# 68 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/deflate.h"
typedef struct ct_data_s {
    union {
        ush freq;
        ush code;
    } fc;
    union {
        ush dad;
        ush len;
    } dl;
} ct_data;






typedef struct static_tree_desc_s static_tree_desc;

typedef struct tree_desc_s {
    ct_data *dyn_tree;
    int max_code;
    const static_tree_desc *stat_desc;
} tree_desc;

typedef ush Pos;
typedef Pos Posf;
typedef unsigned IPos;





typedef struct internal_state {
    z_streamp strm;
    int status;
    Bytef *pending_buf;
    ulg pending_buf_size;
    Bytef *pending_out;
    ulg pending;
    int wrap;
    gz_headerp gzhead;
    ulg gzindex;
    Byte method;
    int last_flush;



    uInt w_size;
    uInt w_bits;
    uInt w_mask;

    Bytef *window;
# 129 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/deflate.h"
    ulg window_size;




    Posf *prev;





    Posf *head;

    uInt ins_h;
    uInt hash_size;
    uInt hash_bits;
    uInt hash_mask;

    uInt hash_shift;






    long block_start;




    uInt match_length;
    IPos prev_match;
    int match_available;
    uInt strstart;
    uInt match_start;
    uInt lookahead;

    uInt prev_length;




    uInt max_chain_length;





    uInt max_lazy_match;
# 188 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/deflate.h"
    int level;
    int strategy;

    uInt good_match;


    int nice_match;



    struct ct_data_s dyn_ltree[(2*(256 +1+29)+1)];
    struct ct_data_s dyn_dtree[2*30 +1];
    struct ct_data_s bl_tree[2*19 +1];

    struct tree_desc_s l_desc;
    struct tree_desc_s d_desc;
    struct tree_desc_s bl_desc;

    ush bl_count[15 +1];


    int heap[2*(256 +1+29)+1];
    int heap_len;
    int heap_max;




    uch depth[2*(256 +1+29)+1];



    uchf *sym_buf;

    uInt lit_bufsize;
# 242 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/deflate.h"
    uInt sym_next;
    uInt sym_end;

    ulg opt_len;
    ulg static_len;
    uInt matches;
    uInt insert;






    ush bi_buf;



    int bi_valid;




    ulg high_water;






} deflate_state;
# 294 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/deflate.h"
void _tr_init(deflate_state *s);
int _tr_tally(deflate_state *s, unsigned dist, unsigned lc);
void _tr_flush_block(deflate_state *s, charf *buf,
                                   ulg stored_len, int last);
void _tr_flush_bits(deflate_state *s);
void _tr_align(deflate_state *s);
void _tr_stored_block(deflate_state *s, charf *buf,
                                    ulg stored_len, int last);
# 317 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/deflate.h"
  extern const uch _length_code[];
  extern const uch _dist_code[];
# 38 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c" 2
# 62 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c"
static const int extra_lbits[29]
   = {0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0};

static const int extra_dbits[30]
   = {0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12,12,13,13};

static const int extra_blbits[19]
   = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,3,7};

static const uch bl_order[19]
   = {16,17,18,0,8,7,9,6,10,5,11,4,12,3,13,2,14,1,15};
# 114 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.h" 1


static const ct_data static_ltree[(256 +1+29)+2] = {
{{ 12},{ 8}}, {{140},{ 8}}, {{ 76},{ 8}}, {{204},{ 8}}, {{ 44},{ 8}},
{{172},{ 8}}, {{108},{ 8}}, {{236},{ 8}}, {{ 28},{ 8}}, {{156},{ 8}},
{{ 92},{ 8}}, {{220},{ 8}}, {{ 60},{ 8}}, {{188},{ 8}}, {{124},{ 8}},
{{252},{ 8}}, {{ 2},{ 8}}, {{130},{ 8}}, {{ 66},{ 8}}, {{194},{ 8}},
{{ 34},{ 8}}, {{162},{ 8}}, {{ 98},{ 8}}, {{226},{ 8}}, {{ 18},{ 8}},
{{146},{ 8}}, {{ 82},{ 8}}, {{210},{ 8}}, {{ 50},{ 8}}, {{178},{ 8}},
{{114},{ 8}}, {{242},{ 8}}, {{ 10},{ 8}}, {{138},{ 8}}, {{ 74},{ 8}},
{{202},{ 8}}, {{ 42},{ 8}}, {{170},{ 8}}, {{106},{ 8}}, {{234},{ 8}},
{{ 26},{ 8}}, {{154},{ 8}}, {{ 90},{ 8}}, {{218},{ 8}}, {{ 58},{ 8}},
{{186},{ 8}}, {{122},{ 8}}, {{250},{ 8}}, {{ 6},{ 8}}, {{134},{ 8}},
{{ 70},{ 8}}, {{198},{ 8}}, {{ 38},{ 8}}, {{166},{ 8}}, {{102},{ 8}},
{{230},{ 8}}, {{ 22},{ 8}}, {{150},{ 8}}, {{ 86},{ 8}}, {{214},{ 8}},
{{ 54},{ 8}}, {{182},{ 8}}, {{118},{ 8}}, {{246},{ 8}}, {{ 14},{ 8}},
{{142},{ 8}}, {{ 78},{ 8}}, {{206},{ 8}}, {{ 46},{ 8}}, {{174},{ 8}},
{{110},{ 8}}, {{238},{ 8}}, {{ 30},{ 8}}, {{158},{ 8}}, {{ 94},{ 8}},
{{222},{ 8}}, {{ 62},{ 8}}, {{190},{ 8}}, {{126},{ 8}}, {{254},{ 8}},
{{ 1},{ 8}}, {{129},{ 8}}, {{ 65},{ 8}}, {{193},{ 8}}, {{ 33},{ 8}},
{{161},{ 8}}, {{ 97},{ 8}}, {{225},{ 8}}, {{ 17},{ 8}}, {{145},{ 8}},
{{ 81},{ 8}}, {{209},{ 8}}, {{ 49},{ 8}}, {{177},{ 8}}, {{113},{ 8}},
{{241},{ 8}}, {{ 9},{ 8}}, {{137},{ 8}}, {{ 73},{ 8}}, {{201},{ 8}},
{{ 41},{ 8}}, {{169},{ 8}}, {{105},{ 8}}, {{233},{ 8}}, {{ 25},{ 8}},
{{153},{ 8}}, {{ 89},{ 8}}, {{217},{ 8}}, {{ 57},{ 8}}, {{185},{ 8}},
{{121},{ 8}}, {{249},{ 8}}, {{ 5},{ 8}}, {{133},{ 8}}, {{ 69},{ 8}},
{{197},{ 8}}, {{ 37},{ 8}}, {{165},{ 8}}, {{101},{ 8}}, {{229},{ 8}},
{{ 21},{ 8}}, {{149},{ 8}}, {{ 85},{ 8}}, {{213},{ 8}}, {{ 53},{ 8}},
{{181},{ 8}}, {{117},{ 8}}, {{245},{ 8}}, {{ 13},{ 8}}, {{141},{ 8}},
{{ 77},{ 8}}, {{205},{ 8}}, {{ 45},{ 8}}, {{173},{ 8}}, {{109},{ 8}},
{{237},{ 8}}, {{ 29},{ 8}}, {{157},{ 8}}, {{ 93},{ 8}}, {{221},{ 8}},
{{ 61},{ 8}}, {{189},{ 8}}, {{125},{ 8}}, {{253},{ 8}}, {{ 19},{ 9}},
{{275},{ 9}}, {{147},{ 9}}, {{403},{ 9}}, {{ 83},{ 9}}, {{339},{ 9}},
{{211},{ 9}}, {{467},{ 9}}, {{ 51},{ 9}}, {{307},{ 9}}, {{179},{ 9}},
{{435},{ 9}}, {{115},{ 9}}, {{371},{ 9}}, {{243},{ 9}}, {{499},{ 9}},
{{ 11},{ 9}}, {{267},{ 9}}, {{139},{ 9}}, {{395},{ 9}}, {{ 75},{ 9}},
{{331},{ 9}}, {{203},{ 9}}, {{459},{ 9}}, {{ 43},{ 9}}, {{299},{ 9}},
{{171},{ 9}}, {{427},{ 9}}, {{107},{ 9}}, {{363},{ 9}}, {{235},{ 9}},
{{491},{ 9}}, {{ 27},{ 9}}, {{283},{ 9}}, {{155},{ 9}}, {{411},{ 9}},
{{ 91},{ 9}}, {{347},{ 9}}, {{219},{ 9}}, {{475},{ 9}}, {{ 59},{ 9}},
{{315},{ 9}}, {{187},{ 9}}, {{443},{ 9}}, {{123},{ 9}}, {{379},{ 9}},
{{251},{ 9}}, {{507},{ 9}}, {{ 7},{ 9}}, {{263},{ 9}}, {{135},{ 9}},
{{391},{ 9}}, {{ 71},{ 9}}, {{327},{ 9}}, {{199},{ 9}}, {{455},{ 9}},
{{ 39},{ 9}}, {{295},{ 9}}, {{167},{ 9}}, {{423},{ 9}}, {{103},{ 9}},
{{359},{ 9}}, {{231},{ 9}}, {{487},{ 9}}, {{ 23},{ 9}}, {{279},{ 9}},
{{151},{ 9}}, {{407},{ 9}}, {{ 87},{ 9}}, {{343},{ 9}}, {{215},{ 9}},
{{471},{ 9}}, {{ 55},{ 9}}, {{311},{ 9}}, {{183},{ 9}}, {{439},{ 9}},
{{119},{ 9}}, {{375},{ 9}}, {{247},{ 9}}, {{503},{ 9}}, {{ 15},{ 9}},
{{271},{ 9}}, {{143},{ 9}}, {{399},{ 9}}, {{ 79},{ 9}}, {{335},{ 9}},
{{207},{ 9}}, {{463},{ 9}}, {{ 47},{ 9}}, {{303},{ 9}}, {{175},{ 9}},
{{431},{ 9}}, {{111},{ 9}}, {{367},{ 9}}, {{239},{ 9}}, {{495},{ 9}},
{{ 31},{ 9}}, {{287},{ 9}}, {{159},{ 9}}, {{415},{ 9}}, {{ 95},{ 9}},
{{351},{ 9}}, {{223},{ 9}}, {{479},{ 9}}, {{ 63},{ 9}}, {{319},{ 9}},
{{191},{ 9}}, {{447},{ 9}}, {{127},{ 9}}, {{383},{ 9}}, {{255},{ 9}},
{{511},{ 9}}, {{ 0},{ 7}}, {{ 64},{ 7}}, {{ 32},{ 7}}, {{ 96},{ 7}},
{{ 16},{ 7}}, {{ 80},{ 7}}, {{ 48},{ 7}}, {{112},{ 7}}, {{ 8},{ 7}},
{{ 72},{ 7}}, {{ 40},{ 7}}, {{104},{ 7}}, {{ 24},{ 7}}, {{ 88},{ 7}},
{{ 56},{ 7}}, {{120},{ 7}}, {{ 4},{ 7}}, {{ 68},{ 7}}, {{ 36},{ 7}},
{{100},{ 7}}, {{ 20},{ 7}}, {{ 84},{ 7}}, {{ 52},{ 7}}, {{116},{ 7}},
{{ 3},{ 8}}, {{131},{ 8}}, {{ 67},{ 8}}, {{195},{ 8}}, {{ 35},{ 8}},
{{163},{ 8}}, {{ 99},{ 8}}, {{227},{ 8}}
};

static const ct_data static_dtree[30] = {
{{ 0},{ 5}}, {{16},{ 5}}, {{ 8},{ 5}}, {{24},{ 5}}, {{ 4},{ 5}},
{{20},{ 5}}, {{12},{ 5}}, {{28},{ 5}}, {{ 2},{ 5}}, {{18},{ 5}},
{{10},{ 5}}, {{26},{ 5}}, {{ 6},{ 5}}, {{22},{ 5}}, {{14},{ 5}},
{{30},{ 5}}, {{ 1},{ 5}}, {{17},{ 5}}, {{ 9},{ 5}}, {{25},{ 5}},
{{ 5},{ 5}}, {{21},{ 5}}, {{13},{ 5}}, {{29},{ 5}}, {{ 3},{ 5}},
{{19},{ 5}}, {{11},{ 5}}, {{27},{ 5}}, {{ 7},{ 5}}, {{23},{ 5}}
};

const uch _dist_code[512] = {
 0, 1, 2, 3, 4, 4, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8,
 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 10, 10, 10,
10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11,
11, 11, 11, 11, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12,
12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13,
13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13,
13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14,
14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 15, 15, 15, 15, 15, 15, 15, 15,
15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 0, 0, 16, 17,
18, 18, 19, 19, 20, 20, 20, 20, 21, 21, 21, 21, 22, 22, 22, 22, 22, 22, 22, 22,
23, 23, 23, 23, 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
24, 24, 24, 24, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27,
27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,
27, 27, 27, 27, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28, 28,
28, 28, 28, 28, 28, 28, 28, 28, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29,
29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29, 29
};

const uch _length_code[258 -3 +1]= {
 0, 1, 2, 3, 4, 5, 6, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 12, 12,
13, 13, 13, 13, 14, 14, 14, 14, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16,
17, 17, 17, 17, 17, 17, 17, 17, 18, 18, 18, 18, 18, 18, 18, 18, 19, 19, 19, 19,
19, 19, 19, 19, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20,
21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 22, 22, 22, 22,
22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 23, 23, 23, 23, 23, 23, 23,
23, 23, 23, 23, 23, 23, 23, 23, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24,
25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25,
25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 26, 26, 26, 26, 26, 26, 26, 26,
26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26,
26, 26, 26, 26, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27,
27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 28
};

static const int base_length[29] = {
0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 12, 14, 16, 20, 24, 28, 32, 40, 48, 56,
64, 80, 96, 112, 128, 160, 192, 224, 0
};

static const int base_dist[30] = {
    0, 1, 2, 3, 4, 6, 8, 12, 16, 24,
   32, 48, 64, 96, 128, 192, 256, 384, 512, 768,
 1024, 1536, 2048, 3072, 4096, 6144, 8192, 12288, 16384, 24576
};
# 115 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c" 2


struct static_tree_desc_s {
    const ct_data *static_tree;
    const intf *extra_bits;
    int extra_base;
    int elems;
    int max_length;
};







static const static_tree_desc static_l_desc =
{static_ltree, extra_lbits, 256 +1, (256 +1+29), 15};

static const static_tree_desc static_d_desc =
{static_dtree, extra_dbits, 0, 30, 15};

static const static_tree_desc static_bl_desc =
{(const ct_data *)0, extra_blbits, 0, 19, 7};
# 154 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c"
static unsigned bi_reverse(unsigned code, int len) {
    register unsigned res = 0;
    do {
        res |= code & 1;
        code >>= 1, res <<= 1;
    } while (--len > 0);
    return res >> 1;
}




static void bi_flush(deflate_state *s) {
    if (s->bi_valid == 16) {
        { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; };
        s->bi_buf = 0;
        s->bi_valid = 0;
    } else if (s->bi_valid >= 8) {
        {s->pending_buf[s->pending++] = (Bytef)((Byte)s->bi_buf);};
        s->bi_buf >>= 8;
        s->bi_valid -= 8;
    }
}




static void bi_windup(deflate_state *s) {
    if (s->bi_valid > 8) {
        { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; };
    } else if (s->bi_valid > 0) {
        {s->pending_buf[s->pending++] = (Bytef)((Byte)s->bi_buf);};
    }
    s->bi_buf = 0;
    s->bi_valid = 0;



}
# 202 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c"
static void gen_codes(ct_data *tree, int max_code, ushf *bl_count) {
    ush next_code[15 +1];
    unsigned code = 0;
    int bits;
    int n;




    for (bits = 1; bits <= 15; bits++) {
        code = (code + bl_count[bits - 1]) << 1;
        next_code[bits] = (ush)code;
    }



   
                                      ;
    ;

    for (n = 0; n <= max_code; n++) {
        int len = tree[n].dl.len;
        if (len == 0) continue;

        tree[n].fc.code = (ush)bi_reverse(next_code[len]++, len);

       
                                                                              ;
    }
}
# 294 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c"
static void tr_static_init(void) {
# 373 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c"
}
# 439 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c"
static void init_block(deflate_state *s) {
    int n;


    for (n = 0; n < (256 +1+29); n++) s->dyn_ltree[n].fc.freq = 0;
    for (n = 0; n < 30; n++) s->dyn_dtree[n].fc.freq = 0;
    for (n = 0; n < 19; n++) s->bl_tree[n].fc.freq = 0;

    s->dyn_ltree[256].fc.freq = 1;
    s->opt_len = s->static_len = 0L;
    s->sym_next = s->matches = 0;
}




void _tr_init(deflate_state *s) {
    tr_static_init();

    s->l_desc.dyn_tree = s->dyn_ltree;
    s->l_desc.stat_desc = &static_l_desc;

    s->d_desc.dyn_tree = s->dyn_dtree;
    s->d_desc.stat_desc = &static_d_desc;

    s->bl_desc.dyn_tree = s->bl_tree;
    s->bl_desc.stat_desc = &static_bl_desc;

    s->bi_buf = 0;
    s->bi_valid = 0;






    init_block(s);
}
# 507 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c"
static void pqdownheap(deflate_state *s, ct_data *tree, int k) {
    int v = s->heap[k];
    int j = k << 1;
    while (j <= s->heap_len) {

        if (j < s->heap_len &&
            (tree[s->heap[j + 1]].fc.freq < tree[s->heap[j]].fc.freq || (tree[s->heap[j + 1]].fc.freq == tree[s->heap[j]].fc.freq && s->depth[s->heap[j + 1]] <= s->depth[s->heap[j]]))) {
            j++;
        }

        if ((tree[v].fc.freq < tree[s->heap[j]].fc.freq || (tree[v].fc.freq == tree[s->heap[j]].fc.freq && s->depth[v] <= s->depth[s->heap[j]]))) break;


        s->heap[k] = s->heap[j]; k = j;


        j <<= 1;
    }
    s->heap[k] = v;
}
# 538 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c"
static void gen_bitlen(deflate_state *s, tree_desc *desc) {
    ct_data *tree = desc->dyn_tree;
    int max_code = desc->max_code;
    const ct_data *stree = desc->stat_desc->static_tree;
    const intf *extra = desc->stat_desc->extra_bits;
    int base = desc->stat_desc->extra_base;
    int max_length = desc->stat_desc->max_length;
    int h;
    int n, m;
    int bits;
    int xbits;
    ush f;
    int overflow = 0;

    for (bits = 0; bits <= 15; bits++) s->bl_count[bits] = 0;




    tree[s->heap[s->heap_max]].dl.len = 0;

    for (h = s->heap_max + 1; h < (2*(256 +1+29)+1); h++) {
        n = s->heap[h];
        bits = tree[tree[n].dl.dad].dl.len + 1;
        if (bits > max_length) bits = max_length, overflow++;
        tree[n].dl.len = (ush)bits;


        if (n > max_code) continue;

        s->bl_count[bits]++;
        xbits = 0;
        if (n >= base) xbits = extra[n - base];
        f = tree[n].fc.freq;
        s->opt_len += (ulg)f * (unsigned)(bits + xbits);
        if (stree) s->static_len += (ulg)f * (unsigned)(stree[n].dl.len + xbits);
    }
    if (overflow == 0) return;

    ;



    do {
        bits = max_length - 1;
        while (s->bl_count[bits] == 0) bits--;
        s->bl_count[bits]--;
        s->bl_count[bits + 1] += 2;
        s->bl_count[max_length]--;



        overflow -= 2;
    } while (overflow > 0);






    for (bits = max_length; bits != 0; bits--) {
        n = s->bl_count[bits];
        while (n != 0) {
            m = s->heap[--h];
            if (m > max_code) continue;
            if ((unsigned) tree[m].dl.len != (unsigned) bits) {
                ;
                s->opt_len += ((ulg)bits - tree[m].dl.len) * tree[m].fc.freq;
                tree[m].dl.len = (ush)bits;
            }
            n--;
        }
    }
}
# 625 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c"
static void build_tree(deflate_state *s, tree_desc *desc) {
    ct_data *tree = desc->dyn_tree;
    const ct_data *stree = desc->stat_desc->static_tree;
    int elems = desc->stat_desc->elems;
    int n, m;
    int max_code = -1;
    int node;





    s->heap_len = 0, s->heap_max = (2*(256 +1+29)+1);

    for (n = 0; n < elems; n++) {
        if (tree[n].fc.freq != 0) {
            s->heap[++(s->heap_len)] = max_code = n;
            s->depth[n] = 0;
        } else {
            tree[n].dl.len = 0;
        }
    }






    while (s->heap_len < 2) {
        node = s->heap[++(s->heap_len)] = (max_code < 2 ? ++max_code : 0);
        tree[node].fc.freq = 1;
        s->depth[node] = 0;
        s->opt_len--; if (stree) s->static_len -= stree[node].dl.len;

    }
    desc->max_code = max_code;




    for (n = s->heap_len/2; n >= 1; n--) pqdownheap(s, tree, n);




    node = elems;
    do {
        { n = s->heap[1]; s->heap[1] = s->heap[s->heap_len--]; pqdownheap(s, tree, 1); };
        m = s->heap[1];

        s->heap[--(s->heap_max)] = n;
        s->heap[--(s->heap_max)] = m;


        tree[node].fc.freq = tree[n].fc.freq + tree[m].fc.freq;
        s->depth[node] = (uch)((s->depth[n] >= s->depth[m] ?
                                s->depth[n] : s->depth[m]) + 1);
        tree[n].dl.dad = tree[m].dl.dad = (ush)node;







        s->heap[1] = node++;
        pqdownheap(s, tree, 1);

    } while (s->heap_len >= 2);

    s->heap[--(s->heap_max)] = s->heap[1];




    gen_bitlen(s, (tree_desc *)desc);


    gen_codes ((ct_data *)tree, max_code, s->bl_count);
}





static void scan_tree(deflate_state *s, ct_data *tree, int max_code) {
    int n;
    int prevlen = -1;
    int curlen;
    int nextlen = tree[0].dl.len;
    int count = 0;
    int max_count = 7;
    int min_count = 4;

    if (nextlen == 0) max_count = 138, min_count = 3;
    tree[max_code + 1].dl.len = (ush)0xffff;

    for (n = 0; n <= max_code; n++) {
        curlen = nextlen; nextlen = tree[n + 1].dl.len;
        if (++count < max_count && curlen == nextlen) {
            continue;
        } else if (count < min_count) {
            s->bl_tree[curlen].fc.freq += count;
        } else if (curlen != 0) {
            if (curlen != prevlen) s->bl_tree[curlen].fc.freq++;
            s->bl_tree[16].fc.freq++;
        } else if (count <= 10) {
            s->bl_tree[17].fc.freq++;
        } else {
            s->bl_tree[18].fc.freq++;
        }
        count = 0; prevlen = curlen;
        if (nextlen == 0) {
            max_count = 138, min_count = 3;
        } else if (curlen == nextlen) {
            max_count = 6, min_count = 3;
        } else {
            max_count = 7, min_count = 4;
        }
    }
}





static void send_tree(deflate_state *s, ct_data *tree, int max_code) {
    int n;
    int prevlen = -1;
    int curlen;
    int nextlen = tree[0].dl.len;
    int count = 0;
    int max_count = 7;
    int min_count = 4;


    if (nextlen == 0) max_count = 138, min_count = 3;

    for (n = 0; n <= max_code; n++) {
        curlen = nextlen; nextlen = tree[n + 1].dl.len;
        if (++count < max_count && curlen == nextlen) {
            continue;
        } else if (count < min_count) {
            do { { int len = s->bl_tree[curlen].dl.len; if (s->bi_valid > (int)16 - len) { int val = (int)s->bl_tree[curlen].fc.code; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(s->bl_tree[curlen].fc.code) << s->bi_valid; s->bi_valid += len; }}; } while (--count != 0);

        } else if (curlen != 0) {
            if (curlen != prevlen) {
                { int len = s->bl_tree[curlen].dl.len; if (s->bi_valid > (int)16 - len) { int val = (int)s->bl_tree[curlen].fc.code; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(s->bl_tree[curlen].fc.code) << s->bi_valid; s->bi_valid += len; }}; count--;
            }
            ;
            { int len = s->bl_tree[16].dl.len; if (s->bi_valid > (int)16 - len) { int val = (int)s->bl_tree[16].fc.code; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(s->bl_tree[16].fc.code) << s->bi_valid; s->bi_valid += len; }}; { int len = 2; if (s->bi_valid > (int)16 - len) { int val = (int)count - 3; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(count - 3) << s->bi_valid; s->bi_valid += len; }};

        } else if (count <= 10) {
            { int len = s->bl_tree[17].dl.len; if (s->bi_valid > (int)16 - len) { int val = (int)s->bl_tree[17].fc.code; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(s->bl_tree[17].fc.code) << s->bi_valid; s->bi_valid += len; }}; { int len = 3; if (s->bi_valid > (int)16 - len) { int val = (int)count - 3; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(count - 3) << s->bi_valid; s->bi_valid += len; }};

        } else {
            { int len = s->bl_tree[18].dl.len; if (s->bi_valid > (int)16 - len) { int val = (int)s->bl_tree[18].fc.code; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(s->bl_tree[18].fc.code) << s->bi_valid; s->bi_valid += len; }}; { int len = 7; if (s->bi_valid > (int)16 - len) { int val = (int)count - 11; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(count - 11) << s->bi_valid; s->bi_valid += len; }};
        }
        count = 0; prevlen = curlen;
        if (nextlen == 0) {
            max_count = 138, min_count = 3;
        } else if (curlen == nextlen) {
            max_count = 6, min_count = 3;
        } else {
            max_count = 7, min_count = 4;
        }
    }
}





static int build_bl_tree(deflate_state *s) {
    int max_blindex;


    scan_tree(s, (ct_data *)s->dyn_ltree, s->l_desc.max_code);
    scan_tree(s, (ct_data *)s->dyn_dtree, s->d_desc.max_code);


    build_tree(s, (tree_desc *)(&(s->bl_desc)));
# 815 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c"
    for (max_blindex = 19 -1; max_blindex >= 3; max_blindex--) {
        if (s->bl_tree[bl_order[max_blindex]].dl.len != 0) break;
    }

    s->opt_len += 3*((ulg)max_blindex + 1) + 5 + 5 + 4;
   
                                       ;

    return max_blindex;
}






static void send_all_trees(deflate_state *s, int lcodes, int dcodes,
                          int blcodes) {
    int rank;

    ;
   
                             ;
    ;
    { int len = 5; if (s->bi_valid > (int)16 - len) { int val = (int)lcodes - 257; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(lcodes - 257) << s->bi_valid; s->bi_valid += len; }};
    { int len = 5; if (s->bi_valid > (int)16 - len) { int val = (int)dcodes - 1; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(dcodes - 1) << s->bi_valid; s->bi_valid += len; }};
    { int len = 4; if (s->bi_valid > (int)16 - len) { int val = (int)blcodes - 4; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(blcodes - 4) << s->bi_valid; s->bi_valid += len; }};
    for (rank = 0; rank < blcodes; rank++) {
        ;
        { int len = 3; if (s->bi_valid > (int)16 - len) { int val = (int)s->bl_tree[bl_order[rank]].dl.len; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(s->bl_tree[bl_order[rank]].dl.len) << s->bi_valid; s->bi_valid += len; }};
    }
    ;

    send_tree(s, (ct_data *)s->dyn_ltree, lcodes - 1);
    ;

    send_tree(s, (ct_data *)s->dyn_dtree, dcodes - 1);
    ;
}




void _tr_stored_block(deflate_state *s, charf *buf,
                                    ulg stored_len, int last) {
    { int len = 3; if (s->bi_valid > (int)16 - len) { int val = (int)(0<<1) + last; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)((0<<1) + last) << s->bi_valid; s->bi_valid += len; }};
    bi_windup(s);
    { {s->pending_buf[s->pending++] = (Bytef)((uch)(((ush)stored_len) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)((ush)stored_len) >> 8));}; };
    { {s->pending_buf[s->pending++] = (Bytef)((uch)(((ush)~stored_len) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)((ush)~stored_len) >> 8));}; };
    if (stored_len)
        memcpy(s->pending_buf + s->pending, (Bytef *)buf, stored_len);
    s->pending += stored_len;






}




void _tr_flush_bits(deflate_state *s) {
    bi_flush(s);
}





void _tr_align(deflate_state *s) {
    { int len = 3; if (s->bi_valid > (int)16 - len) { int val = (int)1<<1; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(1<<1) << s->bi_valid; s->bi_valid += len; }};
    { int len = static_ltree[256].dl.len; if (s->bi_valid > (int)16 - len) { int val = (int)static_ltree[256].fc.code; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(static_ltree[256].fc.code) << s->bi_valid; s->bi_valid += len; }};



    bi_flush(s);
}




static void compress_block(deflate_state *s, const ct_data *ltree,
                          const ct_data *dtree) {
    unsigned dist;
    int lc;
    unsigned sx = 0;
    unsigned code;
    int extra;

    if (s->sym_next != 0) do {
        dist = s->sym_buf[sx++] & 0xff;
        dist += (unsigned)(s->sym_buf[sx++] & 0xff) << 8;
        lc = s->sym_buf[sx++];
        if (dist == 0) {
            { int len = ltree[lc].dl.len; if (s->bi_valid > (int)16 - len) { int val = (int)ltree[lc].fc.code; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(ltree[lc].fc.code) << s->bi_valid; s->bi_valid += len; }};
            ;
        } else {

            code = _length_code[lc];
            { int len = ltree[code + 256 + 1].dl.len; if (s->bi_valid > (int)16 - len) { int val = (int)ltree[code + 256 + 1].fc.code; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(ltree[code + 256 + 1].fc.code) << s->bi_valid; s->bi_valid += len; }};
            extra = extra_lbits[code];
            if (extra != 0) {
                lc -= base_length[code];
                { int len = extra; if (s->bi_valid > (int)16 - len) { int val = (int)lc; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(lc) << s->bi_valid; s->bi_valid += len; }};
            }
            dist--;
            code = ((dist) < 256 ? _dist_code[dist] : _dist_code[256+((dist)>>7)]);
            ;

            { int len = dtree[code].dl.len; if (s->bi_valid > (int)16 - len) { int val = (int)dtree[code].fc.code; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(dtree[code].fc.code) << s->bi_valid; s->bi_valid += len; }};
            extra = extra_dbits[code];
            if (extra != 0) {
                dist -= (unsigned)base_dist[code];
                { int len = extra; if (s->bi_valid > (int)16 - len) { int val = (int)dist; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(dist) << s->bi_valid; s->bi_valid += len; }};
            }
        }


        ;

    } while (sx < s->sym_next);

    { int len = ltree[256].dl.len; if (s->bi_valid > (int)16 - len) { int val = (int)ltree[256].fc.code; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)(ltree[256].fc.code) << s->bi_valid; s->bi_valid += len; }};
}
# 955 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c"
static int detect_data_type(deflate_state *s) {




    unsigned long block_mask = 0xf3ffc07fUL;
    int n;


    for (n = 0; n <= 31; n++, block_mask >>= 1)
        if ((block_mask & 1) && (s->dyn_ltree[n].fc.freq != 0))
            return 0;


    if (s->dyn_ltree[9].fc.freq != 0 || s->dyn_ltree[10].fc.freq != 0
            || s->dyn_ltree[13].fc.freq != 0)
        return 1;
    for (n = 32; n < 256; n++)
        if (s->dyn_ltree[n].fc.freq != 0)
            return 1;




    return 0;
}





void _tr_flush_block(deflate_state *s, charf *buf,
                                   ulg stored_len, int last) {
    ulg opt_lenb, static_lenb;
    int max_blindex = 0;


    if (s->level > 0) {


        if (s->strm->data_type == 2)
            s->strm->data_type = detect_data_type(s);


        build_tree(s, (tree_desc *)(&(s->l_desc)));
       
                               ;

        build_tree(s, (tree_desc *)(&(s->d_desc)));
       
                               ;







        max_blindex = build_bl_tree(s);


        opt_lenb = (s->opt_len + 3 + 7) >> 3;
        static_lenb = (s->static_len + 3 + 7) >> 3;

       

                                 ;


        if (static_lenb <= opt_lenb || s->strategy == 4)

            opt_lenb = static_lenb;

    } else {
        ;
        opt_lenb = static_lenb = stored_len + 5;
    }




    if (stored_len + 4 <= opt_lenb && buf != (char*)0) {
# 1045 "/home/enumclass/Documents/C2RustTranslation/bkp/optipng-0.7.8/third_party/zlib/trees.c"
        _tr_stored_block(s, buf, stored_len, last);

    } else if (static_lenb == opt_lenb) {
        { int len = 3; if (s->bi_valid > (int)16 - len) { int val = (int)(1<<1) + last; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)((1<<1) + last) << s->bi_valid; s->bi_valid += len; }};
        compress_block(s, (const ct_data *)static_ltree,
                       (const ct_data *)static_dtree);



    } else {
        { int len = 3; if (s->bi_valid > (int)16 - len) { int val = (int)(2<<1) + last; s->bi_buf |= (ush)val << s->bi_valid; { {s->pending_buf[s->pending++] = (Bytef)((uch)((s->bi_buf) & 0xff));}; {s->pending_buf[s->pending++] = (Bytef)((uch)((ush)(s->bi_buf) >> 8));}; }; s->bi_buf = (ush)val >> (16 - s->bi_valid); s->bi_valid += len - 16; } else { s->bi_buf |= (ush)((2<<1) + last) << s->bi_valid; s->bi_valid += len; }};
        send_all_trees(s, s->l_desc.max_code + 1, s->d_desc.max_code + 1,
                       max_blindex + 1);
        compress_block(s, (const ct_data *)s->dyn_ltree,
                       (const ct_data *)s->dyn_dtree);



    }
    ;



    init_block(s);

    if (last) {
        bi_windup(s);



    }
   
                                       ;
}





int _tr_tally(deflate_state *s, unsigned dist, unsigned lc) {
    s->sym_buf[s->sym_next++] = (uch)dist;
    s->sym_buf[s->sym_next++] = (uch)(dist >> 8);
    s->sym_buf[s->sym_next++] = (uch)lc;
    if (dist == 0) {

        s->dyn_ltree[lc].fc.freq++;
    } else {
        s->matches++;

        dist--;
       

                                                                         ;

        s->dyn_ltree[_length_code[lc] + 256 + 1].fc.freq++;
        s->dyn_dtree[((dist) < 256 ? _dist_code[dist] : _dist_code[256+((dist)>>7)])].fc.freq++;
    }
    return (s->sym_next == s->sym_end);
}
