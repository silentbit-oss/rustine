# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/libzahl-1.0/src/ztrunc.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/libzahl-1.0/src/ztrunc.c"

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/libzahl-1.0/src/internals.h" 1

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/libzahl-1.0/src/../zahl.h" 1






# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1



typedef int START_DELIMETER;
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
# 8 "/home/enumclass/Documents/C2RustTranslation/bkp/libzahl-1.0/src/../zahl.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/setjmp.h" 1
# 9 "/home/enumclass/Documents/C2RustTranslation/bkp/libzahl-1.0/src/../zahl.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 10 "/home/enumclass/Documents/C2RustTranslation/bkp/libzahl-1.0/src/../zahl.h" 2




typedef uint32_t zahl_char_t;


typedef struct {
        int sign;
        size_t used;
        size_t alloced;
        zahl_char_t *chars;
} z_t[1];


enum zprimality { NONPRIME = 0, PROBABLY_PRIME, PRIME };
enum zranddev { FAST_RANDOM = 0, SECURE_RANDOM };
enum zranddist { QUASIUNIFORM = 0, UNIFORM };

enum zerror {
 ZERROR_ERRNO_SET = 0
};
# 40 "/home/enumclass/Documents/C2RustTranslation/bkp/libzahl-1.0/src/../zahl.h"
void zsetup(jmp_buf);
void zunsetup(void);




void zfree(z_t);
void zswap(z_t, z_t);
size_t zsave(z_t, void *);
size_t zload(z_t, const void *);





void zset(z_t, z_t);
void zseti(z_t, long long int);
void zsetu(z_t, unsigned long long int);





int zcmp(z_t, z_t);
int zcmpi(z_t, long long int);
int zcmpu(z_t, unsigned long long int);

int zcmpmag(z_t, z_t);




void zadd(z_t, z_t, z_t);
void zsub(z_t, z_t, z_t);
void zmul(z_t, z_t, z_t);
void zmodmul(z_t, z_t, z_t, z_t);
void zdiv(z_t, z_t, z_t);
void zdivmod(z_t, z_t, z_t, z_t);
void zmod(z_t, z_t, z_t);
void zsqr(z_t, z_t);
void zmodsqr(z_t, z_t, z_t);
void zneg(z_t, z_t);
void zabs(z_t, z_t);
void zpow(z_t, z_t, z_t);
void zmodpow(z_t, z_t, z_t, z_t);
void zpowu(z_t, z_t, unsigned long long int);
void zmodpowu(z_t, z_t, unsigned long long int, z_t);


void zadd_unsigned(z_t, z_t, z_t);
void zsub_unsigned(z_t, z_t, z_t);




void zand(z_t, z_t, z_t);
void zor(z_t, z_t, z_t);
void zxor(z_t, z_t, z_t);
void znot(z_t, z_t);
void zlsh(z_t, z_t, size_t);
void zrsh(z_t, z_t, size_t);
void ztrunc(z_t, z_t, size_t);
int zbtest(z_t, size_t);
void zsplit(z_t, z_t, z_t, size_t);
size_t zbits(z_t);
size_t zlsb(z_t);


void zbset(z_t, z_t, size_t, int);




void zgcd(z_t, z_t, z_t);



enum zprimality zptest(z_t, z_t, int);





void zrand(z_t, enum zranddev, enum zranddist, z_t);




char *zstr(z_t, char *);
int zsets(z_t, const char *);


size_t zstr_length(z_t, unsigned long long int);




enum zerror zerror(const char **);
void zperror(const char *);




static inline void zinit(z_t a) { a->alloced = 0; a->chars = 0; }
static inline int zeven(z_t a) { return !a->sign || !(a->chars[0] & 1); }
static inline int zodd(z_t a) { return a->sign && (a->chars[0] & 1); }
static inline int zeven_nonzero(z_t a) { return !(a->chars[0] & 1); }
static inline int zodd_nonzero(z_t a) { return (a->chars[0] & 1); }
static inline int zzero(z_t a) { return !a->sign; }
static inline int zsignum(z_t a) { return a->sign; }
# 3 "/home/enumclass/Documents/C2RustTranslation/bkp/libzahl-1.0/src/internals.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 5 "/home/enumclass/Documents/C2RustTranslation/bkp/libzahl-1.0/src/internals.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 6 "/home/enumclass/Documents/C2RustTranslation/bkp/libzahl-1.0/src/internals.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/errno.h" 1
# 7 "/home/enumclass/Documents/C2RustTranslation/bkp/libzahl-1.0/src/internals.h" 2
# 49 "/home/enumclass/Documents/C2RustTranslation/bkp/libzahl-1.0/src/internals.h"
extern z_t libzahl_tmp_cmp; extern z_t libzahl_tmp_str_num; extern z_t libzahl_tmp_str_mag; extern z_t libzahl_tmp_str_div; extern z_t libzahl_tmp_str_rem; extern z_t libzahl_tmp_gcd_u; extern z_t libzahl_tmp_gcd_v; extern z_t libzahl_tmp_sub; extern z_t libzahl_tmp_modmul; extern z_t libzahl_tmp_div; extern z_t libzahl_tmp_mod; extern z_t libzahl_tmp_pow_b; extern z_t libzahl_tmp_pow_c; extern z_t libzahl_tmp_pow_d; extern z_t libzahl_tmp_modsqr; extern z_t libzahl_tmp_divmod_a; extern z_t libzahl_tmp_divmod_b; extern z_t libzahl_tmp_divmod_d; extern z_t libzahl_tmp_ptest_x; extern z_t libzahl_tmp_ptest_a; extern z_t libzahl_tmp_ptest_d; extern z_t libzahl_tmp_ptest_n1; extern z_t libzahl_tmp_ptest_n4;


extern z_t libzahl_const_1e19; extern z_t libzahl_const_1e9; extern z_t libzahl_const_1; extern z_t libzahl_const_2; extern z_t libzahl_const_4;


extern z_t libzahl_tmp_divmod_ds[32];
extern jmp_buf libzahl_jmp_buf;
extern int libzahl_set_up;
extern int libzahl_error;
extern zahl_char_t **libzahl_pool[sizeof(size_t) * 8];
extern size_t libzahl_pool_n[sizeof(size_t) * 8];
extern size_t libzahl_pool_alloc[sizeof(size_t) * 8];
# 76 "/home/enumclass/Documents/C2RustTranslation/bkp/libzahl-1.0/src/internals.h"
void libzahl_realloc(z_t a, size_t need);
# 3 "/home/enumclass/Documents/C2RustTranslation/bkp/libzahl-1.0/src/ztrunc.c" 2


void
ztrunc(z_t a, z_t b, size_t bits)
{
 zahl_char_t mask = 1;
 size_t chars, i;

 if (zzero(b)) {
  ((a)->sign = (0));
  return;
 }

 chars = (((bits) + (32 - 1)) >> 5);
 a->sign = b->sign;
 a->used = ((chars) < (b->used) ? (chars) : (b->used));
 if (a->used < chars)
  bits = 0;
 if (a != b) {
  do { if ((a)->alloced < (a->used)) libzahl_realloc(a, (a->used)); } while (0);
  memcpy(a->chars, b->chars, (a->used) * sizeof(zahl_char_t));
 }
 bits = ((bits) & (32 - 1));
 if (bits) {
  mask <<= bits;
  mask -= 1;
  a->chars[a->used - 1] &= mask;
 }

 for (i = a->used; i--;)
  if (a->chars[i])
   return;
 ((a)->sign = (0));
}
# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/libzahl-1.0/src/ztrunc.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/libzahl-1.0/src/ztrunc.c"

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/libzahl-1.0/src/internals.h" 1

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/libzahl-1.0/src/../zahl.h" 1






# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1



typedef int START_DELIMETER;
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
# 8 "/home/enumclass/Documents/C2RustTranslation/bkp/libzahl-1.0/src/../zahl.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/setjmp.h" 1
# 9 "/home/enumclass/Documents/C2RustTranslation/bkp/libzahl-1.0/src/../zahl.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 10 "/home/enumclass/Documents/C2RustTranslation/bkp/libzahl-1.0/src/../zahl.h" 2




typedef uint32_t zahl_char_t;


typedef struct {
        int sign;
        size_t used;
        size_t alloced;
        zahl_char_t *chars;
} z_t[1];


enum zprimality { NONPRIME = 0, PROBABLY_PRIME, PRIME };
enum zranddev { FAST_RANDOM = 0, SECURE_RANDOM };
enum zranddist { QUASIUNIFORM = 0, UNIFORM };

enum zerror {
 ZERROR_ERRNO_SET = 0
};
# 40 "/home/enumclass/Documents/C2RustTranslation/bkp/libzahl-1.0/src/../zahl.h"
void zsetup(jmp_buf);
void zunsetup(void);




void zfree(z_t);
void zswap(z_t, z_t);
size_t zsave(z_t, void *);
size_t zload(z_t, const void *);





void zset(z_t, z_t);
void zseti(z_t, long long int);
void zsetu(z_t, unsigned long long int);





int zcmp(z_t, z_t);
int zcmpi(z_t, long long int);
int zcmpu(z_t, unsigned long long int);

int zcmpmag(z_t, z_t);




void zadd(z_t, z_t, z_t);
void zsub(z_t, z_t, z_t);
void zmul(z_t, z_t, z_t);
void zmodmul(z_t, z_t, z_t, z_t);
void zdiv(z_t, z_t, z_t);
void zdivmod(z_t, z_t, z_t, z_t);
void zmod(z_t, z_t, z_t);
void zsqr(z_t, z_t);
void zmodsqr(z_t, z_t, z_t);
void zneg(z_t, z_t);
void zabs(z_t, z_t);
void zpow(z_t, z_t, z_t);
void zmodpow(z_t, z_t, z_t, z_t);
void zpowu(z_t, z_t, unsigned long long int);
void zmodpowu(z_t, z_t, unsigned long long int, z_t);


void zadd_unsigned(z_t, z_t, z_t);
void zsub_unsigned(z_t, z_t, z_t);




void zand(z_t, z_t, z_t);
void zor(z_t, z_t, z_t);
void zxor(z_t, z_t, z_t);
void znot(z_t, z_t);
void zlsh(z_t, z_t, size_t);
void zrsh(z_t, z_t, size_t);
void ztrunc(z_t, z_t, size_t);
int zbtest(z_t, size_t);
void zsplit(z_t, z_t, z_t, size_t);
size_t zbits(z_t);
size_t zlsb(z_t);


void zbset(z_t, z_t, size_t, int);




void zgcd(z_t, z_t, z_t);



enum zprimality zptest(z_t, z_t, int);





void zrand(z_t, enum zranddev, enum zranddist, z_t);




char *zstr(z_t, char *);
int zsets(z_t, const char *);


size_t zstr_length(z_t, unsigned long long int);




enum zerror zerror(const char **);
void zperror(const char *);




static inline void zinit(z_t a) { a->alloced = 0; a->chars = 0; }
static inline int zeven(z_t a) { return !a->sign || !(a->chars[0] & 1); }
static inline int zodd(z_t a) { return a->sign && (a->chars[0] & 1); }
static inline int zeven_nonzero(z_t a) { return !(a->chars[0] & 1); }
static inline int zodd_nonzero(z_t a) { return (a->chars[0] & 1); }
static inline int zzero(z_t a) { return !a->sign; }
static inline int zsignum(z_t a) { return a->sign; }
# 3 "/home/enumclass/Documents/C2RustTranslation/bkp/libzahl-1.0/src/internals.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 5 "/home/enumclass/Documents/C2RustTranslation/bkp/libzahl-1.0/src/internals.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 6 "/home/enumclass/Documents/C2RustTranslation/bkp/libzahl-1.0/src/internals.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/errno.h" 1
# 7 "/home/enumclass/Documents/C2RustTranslation/bkp/libzahl-1.0/src/internals.h" 2
# 49 "/home/enumclass/Documents/C2RustTranslation/bkp/libzahl-1.0/src/internals.h"
extern z_t libzahl_tmp_cmp; extern z_t libzahl_tmp_str_num; extern z_t libzahl_tmp_str_mag; extern z_t libzahl_tmp_str_div; extern z_t libzahl_tmp_str_rem; extern z_t libzahl_tmp_gcd_u; extern z_t libzahl_tmp_gcd_v; extern z_t libzahl_tmp_sub; extern z_t libzahl_tmp_modmul; extern z_t libzahl_tmp_div; extern z_t libzahl_tmp_mod; extern z_t libzahl_tmp_pow_b; extern z_t libzahl_tmp_pow_c; extern z_t libzahl_tmp_pow_d; extern z_t libzahl_tmp_modsqr; extern z_t libzahl_tmp_divmod_a; extern z_t libzahl_tmp_divmod_b; extern z_t libzahl_tmp_divmod_d; extern z_t libzahl_tmp_ptest_x; extern z_t libzahl_tmp_ptest_a; extern z_t libzahl_tmp_ptest_d; extern z_t libzahl_tmp_ptest_n1; extern z_t libzahl_tmp_ptest_n4;


extern z_t libzahl_const_1e19; extern z_t libzahl_const_1e9; extern z_t libzahl_const_1; extern z_t libzahl_const_2; extern z_t libzahl_const_4;


extern z_t libzahl_tmp_divmod_ds[32];
extern jmp_buf libzahl_jmp_buf;
extern int libzahl_set_up;
extern int libzahl_error;
extern zahl_char_t **libzahl_pool[sizeof(size_t) * 8];
extern size_t libzahl_pool_n[sizeof(size_t) * 8];
extern size_t libzahl_pool_alloc[sizeof(size_t) * 8];
# 76 "/home/enumclass/Documents/C2RustTranslation/bkp/libzahl-1.0/src/internals.h"
void libzahl_realloc(z_t a, size_t need);
# 3 "/home/enumclass/Documents/C2RustTranslation/bkp/libzahl-1.0/src/ztrunc.c" 2


void
ztrunc(z_t a, z_t b, size_t bits)
{
 zahl_char_t mask = 1;
 size_t chars, i;

 if (zzero(b)) {
  ((a)->sign = (0));
  return;
 }

 chars = (((bits) + (32 - 1)) >> 5);
 a->sign = b->sign;
 a->used = ((chars) < (b->used) ? (chars) : (b->used));
 if (a->used < chars)
  bits = 0;
 if (a != b) {
  do { if ((a)->alloced < (a->used)) libzahl_realloc(a, (a->used)); } while (0);
  memcpy(a->chars, b->chars, (a->used) * sizeof(zahl_char_t));
 }
 bits = ((bits) & (32 - 1));
 if (bits) {
  mask <<= bits;
  mask -= 1;
  a->chars[a->used - 1] &= mask;
 }

 for (i = a->used; i--;)
  if (a->chars[i])
   return;
 ((a)->sign = (0));
}
