# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/siphash.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/siphash.c"
# 37 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/siphash.c"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 2
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
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 2
# 38 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/siphash.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 39 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/siphash.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 40 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/siphash.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 41 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/siphash.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/ctype.h" 1
# 42 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/siphash.c" 2
# 89 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/siphash.c"
uint64_t siphash(const uint8_t *in, const size_t inlen, const uint8_t *k) {
    uint64_t hash;
    uint8_t *out = (uint8_t*) &hash;
    uint64_t v0 = 0x736f6d6570736575ULL;
    uint64_t v1 = 0x646f72616e646f6dULL;
    uint64_t v2 = 0x6c7967656e657261ULL;
    uint64_t v3 = 0x7465646279746573ULL;
    uint64_t k0 = (((uint64_t)((k)[0])) | ((uint64_t)((k)[1]) << 8) | ((uint64_t)((k)[2]) << 16) | ((uint64_t)((k)[3]) << 24) | ((uint64_t)((k)[4]) << 32) | ((uint64_t)((k)[5]) << 40) | ((uint64_t)((k)[6]) << 48) | ((uint64_t)((k)[7]) << 56));
    uint64_t k1 = (((uint64_t)((k + 8)[0])) | ((uint64_t)((k + 8)[1]) << 8) | ((uint64_t)((k + 8)[2]) << 16) | ((uint64_t)((k + 8)[3]) << 24) | ((uint64_t)((k + 8)[4]) << 32) | ((uint64_t)((k + 8)[5]) << 40) | ((uint64_t)((k + 8)[6]) << 48) | ((uint64_t)((k + 8)[7]) << 56));
    uint64_t m;
    const uint8_t *end = in + inlen - (inlen % sizeof(uint64_t));
    const int left = inlen & 7;
    uint64_t b = ((uint64_t)inlen) << 56;
    v3 ^= k1;
    v2 ^= k0;
    v1 ^= k1;
    v0 ^= k0;

    for (; in != end; in += 8) {
        m = (((uint64_t)((in)[0])) | ((uint64_t)((in)[1]) << 8) | ((uint64_t)((in)[2]) << 16) | ((uint64_t)((in)[3]) << 24) | ((uint64_t)((in)[4]) << 32) | ((uint64_t)((in)[5]) << 40) | ((uint64_t)((in)[6]) << 48) | ((uint64_t)((in)[7]) << 56));
        v3 ^= m;

        do { v0 += v1; v1 = (uint64_t)(((v1) << (13)) | ((v1) >> (64 - (13)))); v1 ^= v0; v0 = (uint64_t)(((v0) << (32)) | ((v0) >> (64 - (32)))); v2 += v3; v3 = (uint64_t)(((v3) << (16)) | ((v3) >> (64 - (16)))); v3 ^= v2; v0 += v3; v3 = (uint64_t)(((v3) << (21)) | ((v3) >> (64 - (21)))); v3 ^= v0; v2 += v1; v1 = (uint64_t)(((v1) << (17)) | ((v1) >> (64 - (17)))); v1 ^= v2; v2 = (uint64_t)(((v2) << (32)) | ((v2) >> (64 - (32)))); } while (0);
        do { v0 += v1; v1 = (uint64_t)(((v1) << (13)) | ((v1) >> (64 - (13)))); v1 ^= v0; v0 = (uint64_t)(((v0) << (32)) | ((v0) >> (64 - (32)))); v2 += v3; v3 = (uint64_t)(((v3) << (16)) | ((v3) >> (64 - (16)))); v3 ^= v2; v0 += v3; v3 = (uint64_t)(((v3) << (21)) | ((v3) >> (64 - (21)))); v3 ^= v0; v2 += v1; v1 = (uint64_t)(((v1) << (17)) | ((v1) >> (64 - (17)))); v1 ^= v2; v2 = (uint64_t)(((v2) << (32)) | ((v2) >> (64 - (32)))); } while (0);

        v0 ^= m;
    }

    switch (left) {
    case 7: b |= ((uint64_t)in[6]) << 48;
    case 6: b |= ((uint64_t)in[5]) << 40;
    case 5: b |= ((uint64_t)in[4]) << 32;
    case 4: b |= ((uint64_t)in[3]) << 24;
    case 3: b |= ((uint64_t)in[2]) << 16;
    case 2: b |= ((uint64_t)in[1]) << 8;
    case 1: b |= ((uint64_t)in[0]); break;
    case 0: break;
    }

    v3 ^= b;

    do { v0 += v1; v1 = (uint64_t)(((v1) << (13)) | ((v1) >> (64 - (13)))); v1 ^= v0; v0 = (uint64_t)(((v0) << (32)) | ((v0) >> (64 - (32)))); v2 += v3; v3 = (uint64_t)(((v3) << (16)) | ((v3) >> (64 - (16)))); v3 ^= v2; v0 += v3; v3 = (uint64_t)(((v3) << (21)) | ((v3) >> (64 - (21)))); v3 ^= v0; v2 += v1; v1 = (uint64_t)(((v1) << (17)) | ((v1) >> (64 - (17)))); v1 ^= v2; v2 = (uint64_t)(((v2) << (32)) | ((v2) >> (64 - (32)))); } while (0);
    do { v0 += v1; v1 = (uint64_t)(((v1) << (13)) | ((v1) >> (64 - (13)))); v1 ^= v0; v0 = (uint64_t)(((v0) << (32)) | ((v0) >> (64 - (32)))); v2 += v3; v3 = (uint64_t)(((v3) << (16)) | ((v3) >> (64 - (16)))); v3 ^= v2; v0 += v3; v3 = (uint64_t)(((v3) << (21)) | ((v3) >> (64 - (21)))); v3 ^= v0; v2 += v1; v1 = (uint64_t)(((v1) << (17)) | ((v1) >> (64 - (17)))); v1 ^= v2; v2 = (uint64_t)(((v2) << (32)) | ((v2) >> (64 - (32)))); } while (0);

    v0 ^= b;
    v2 ^= 0xff;

    do { v0 += v1; v1 = (uint64_t)(((v1) << (13)) | ((v1) >> (64 - (13)))); v1 ^= v0; v0 = (uint64_t)(((v0) << (32)) | ((v0) >> (64 - (32)))); v2 += v3; v3 = (uint64_t)(((v3) << (16)) | ((v3) >> (64 - (16)))); v3 ^= v2; v0 += v3; v3 = (uint64_t)(((v3) << (21)) | ((v3) >> (64 - (21)))); v3 ^= v0; v2 += v1; v1 = (uint64_t)(((v1) << (17)) | ((v1) >> (64 - (17)))); v1 ^= v2; v2 = (uint64_t)(((v2) << (32)) | ((v2) >> (64 - (32)))); } while (0);
    do { v0 += v1; v1 = (uint64_t)(((v1) << (13)) | ((v1) >> (64 - (13)))); v1 ^= v0; v0 = (uint64_t)(((v0) << (32)) | ((v0) >> (64 - (32)))); v2 += v3; v3 = (uint64_t)(((v3) << (16)) | ((v3) >> (64 - (16)))); v3 ^= v2; v0 += v3; v3 = (uint64_t)(((v3) << (21)) | ((v3) >> (64 - (21)))); v3 ^= v0; v2 += v1; v1 = (uint64_t)(((v1) << (17)) | ((v1) >> (64 - (17)))); v1 ^= v2; v2 = (uint64_t)(((v2) << (32)) | ((v2) >> (64 - (32)))); } while (0);
    do { v0 += v1; v1 = (uint64_t)(((v1) << (13)) | ((v1) >> (64 - (13)))); v1 ^= v0; v0 = (uint64_t)(((v0) << (32)) | ((v0) >> (64 - (32)))); v2 += v3; v3 = (uint64_t)(((v3) << (16)) | ((v3) >> (64 - (16)))); v3 ^= v2; v0 += v3; v3 = (uint64_t)(((v3) << (21)) | ((v3) >> (64 - (21)))); v3 ^= v0; v2 += v1; v1 = (uint64_t)(((v1) << (17)) | ((v1) >> (64 - (17)))); v1 ^= v2; v2 = (uint64_t)(((v2) << (32)) | ((v2) >> (64 - (32)))); } while (0);
    do { v0 += v1; v1 = (uint64_t)(((v1) << (13)) | ((v1) >> (64 - (13)))); v1 ^= v0; v0 = (uint64_t)(((v0) << (32)) | ((v0) >> (64 - (32)))); v2 += v3; v3 = (uint64_t)(((v3) << (16)) | ((v3) >> (64 - (16)))); v3 ^= v2; v0 += v3; v3 = (uint64_t)(((v3) << (21)) | ((v3) >> (64 - (21)))); v3 ^= v0; v2 += v1; v1 = (uint64_t)(((v1) << (17)) | ((v1) >> (64 - (17)))); v1 ^= v2; v2 = (uint64_t)(((v2) << (32)) | ((v2) >> (64 - (32)))); } while (0);

    b = v0 ^ v1 ^ v2 ^ v3;
    ((out))[0] = (uint8_t)(((uint32_t)((b)))); ((out))[1] = (uint8_t)(((uint32_t)((b))) >> 8); ((out))[2] = (uint8_t)(((uint32_t)((b))) >> 16); ((out))[3] = (uint8_t)(((uint32_t)((b))) >> 24);; ((out) + 4)[0] = (uint8_t)(((uint32_t)((b) >> 32))); ((out) + 4)[1] = (uint8_t)(((uint32_t)((b) >> 32)) >> 8); ((out) + 4)[2] = (uint8_t)(((uint32_t)((b) >> 32)) >> 16); ((out) + 4)[3] = (uint8_t)(((uint32_t)((b) >> 32)) >> 24);;;

    return hash;
}

uint64_t siphash_nocase(const uint8_t *in, const size_t inlen, const uint8_t *k)
{
    uint64_t hash;
    uint8_t *out = (uint8_t*) &hash;
    uint64_t v0 = 0x736f6d6570736575ULL;
    uint64_t v1 = 0x646f72616e646f6dULL;
    uint64_t v2 = 0x6c7967656e657261ULL;
    uint64_t v3 = 0x7465646279746573ULL;
    uint64_t k0 = (((uint64_t)((k)[0])) | ((uint64_t)((k)[1]) << 8) | ((uint64_t)((k)[2]) << 16) | ((uint64_t)((k)[3]) << 24) | ((uint64_t)((k)[4]) << 32) | ((uint64_t)((k)[5]) << 40) | ((uint64_t)((k)[6]) << 48) | ((uint64_t)((k)[7]) << 56));
    uint64_t k1 = (((uint64_t)((k + 8)[0])) | ((uint64_t)((k + 8)[1]) << 8) | ((uint64_t)((k + 8)[2]) << 16) | ((uint64_t)((k + 8)[3]) << 24) | ((uint64_t)((k + 8)[4]) << 32) | ((uint64_t)((k + 8)[5]) << 40) | ((uint64_t)((k + 8)[6]) << 48) | ((uint64_t)((k + 8)[7]) << 56));
    uint64_t m;
    const uint8_t *end = in + inlen - (inlen % sizeof(uint64_t));
    const int left = inlen & 7;
    uint64_t b = ((uint64_t)inlen) << 56;
    v3 ^= k1;
    v2 ^= k0;
    v1 ^= k1;
    v0 ^= k0;

    for (; in != end; in += 8) {
        m = (((uint64_t)(tolower((in)[0]))) | ((uint64_t)(tolower((in)[1])) << 8) | ((uint64_t)(tolower((in)[2])) << 16) | ((uint64_t)(tolower((in)[3])) << 24) | ((uint64_t)(tolower((in)[4])) << 32) | ((uint64_t)(tolower((in)[5])) << 40) | ((uint64_t)(tolower((in)[6])) << 48) | ((uint64_t)(tolower((in)[7])) << 56));
        v3 ^= m;

        do { v0 += v1; v1 = (uint64_t)(((v1) << (13)) | ((v1) >> (64 - (13)))); v1 ^= v0; v0 = (uint64_t)(((v0) << (32)) | ((v0) >> (64 - (32)))); v2 += v3; v3 = (uint64_t)(((v3) << (16)) | ((v3) >> (64 - (16)))); v3 ^= v2; v0 += v3; v3 = (uint64_t)(((v3) << (21)) | ((v3) >> (64 - (21)))); v3 ^= v0; v2 += v1; v1 = (uint64_t)(((v1) << (17)) | ((v1) >> (64 - (17)))); v1 ^= v2; v2 = (uint64_t)(((v2) << (32)) | ((v2) >> (64 - (32)))); } while (0);
        do { v0 += v1; v1 = (uint64_t)(((v1) << (13)) | ((v1) >> (64 - (13)))); v1 ^= v0; v0 = (uint64_t)(((v0) << (32)) | ((v0) >> (64 - (32)))); v2 += v3; v3 = (uint64_t)(((v3) << (16)) | ((v3) >> (64 - (16)))); v3 ^= v2; v0 += v3; v3 = (uint64_t)(((v3) << (21)) | ((v3) >> (64 - (21)))); v3 ^= v0; v2 += v1; v1 = (uint64_t)(((v1) << (17)) | ((v1) >> (64 - (17)))); v1 ^= v2; v2 = (uint64_t)(((v2) << (32)) | ((v2) >> (64 - (32)))); } while (0);

        v0 ^= m;
    }

    switch (left) {
    case 7: b |= ((uint64_t)tolower(in[6])) << 48;
    case 6: b |= ((uint64_t)tolower(in[5])) << 40;
    case 5: b |= ((uint64_t)tolower(in[4])) << 32;
    case 4: b |= ((uint64_t)tolower(in[3])) << 24;
    case 3: b |= ((uint64_t)tolower(in[2])) << 16;
    case 2: b |= ((uint64_t)tolower(in[1])) << 8;
    case 1: b |= ((uint64_t)tolower(in[0])); break;
    case 0: break;
    }

    v3 ^= b;

    do { v0 += v1; v1 = (uint64_t)(((v1) << (13)) | ((v1) >> (64 - (13)))); v1 ^= v0; v0 = (uint64_t)(((v0) << (32)) | ((v0) >> (64 - (32)))); v2 += v3; v3 = (uint64_t)(((v3) << (16)) | ((v3) >> (64 - (16)))); v3 ^= v2; v0 += v3; v3 = (uint64_t)(((v3) << (21)) | ((v3) >> (64 - (21)))); v3 ^= v0; v2 += v1; v1 = (uint64_t)(((v1) << (17)) | ((v1) >> (64 - (17)))); v1 ^= v2; v2 = (uint64_t)(((v2) << (32)) | ((v2) >> (64 - (32)))); } while (0);
    do { v0 += v1; v1 = (uint64_t)(((v1) << (13)) | ((v1) >> (64 - (13)))); v1 ^= v0; v0 = (uint64_t)(((v0) << (32)) | ((v0) >> (64 - (32)))); v2 += v3; v3 = (uint64_t)(((v3) << (16)) | ((v3) >> (64 - (16)))); v3 ^= v2; v0 += v3; v3 = (uint64_t)(((v3) << (21)) | ((v3) >> (64 - (21)))); v3 ^= v0; v2 += v1; v1 = (uint64_t)(((v1) << (17)) | ((v1) >> (64 - (17)))); v1 ^= v2; v2 = (uint64_t)(((v2) << (32)) | ((v2) >> (64 - (32)))); } while (0);

    v0 ^= b;
    v2 ^= 0xff;

    do { v0 += v1; v1 = (uint64_t)(((v1) << (13)) | ((v1) >> (64 - (13)))); v1 ^= v0; v0 = (uint64_t)(((v0) << (32)) | ((v0) >> (64 - (32)))); v2 += v3; v3 = (uint64_t)(((v3) << (16)) | ((v3) >> (64 - (16)))); v3 ^= v2; v0 += v3; v3 = (uint64_t)(((v3) << (21)) | ((v3) >> (64 - (21)))); v3 ^= v0; v2 += v1; v1 = (uint64_t)(((v1) << (17)) | ((v1) >> (64 - (17)))); v1 ^= v2; v2 = (uint64_t)(((v2) << (32)) | ((v2) >> (64 - (32)))); } while (0);
    do { v0 += v1; v1 = (uint64_t)(((v1) << (13)) | ((v1) >> (64 - (13)))); v1 ^= v0; v0 = (uint64_t)(((v0) << (32)) | ((v0) >> (64 - (32)))); v2 += v3; v3 = (uint64_t)(((v3) << (16)) | ((v3) >> (64 - (16)))); v3 ^= v2; v0 += v3; v3 = (uint64_t)(((v3) << (21)) | ((v3) >> (64 - (21)))); v3 ^= v0; v2 += v1; v1 = (uint64_t)(((v1) << (17)) | ((v1) >> (64 - (17)))); v1 ^= v2; v2 = (uint64_t)(((v2) << (32)) | ((v2) >> (64 - (32)))); } while (0);
    do { v0 += v1; v1 = (uint64_t)(((v1) << (13)) | ((v1) >> (64 - (13)))); v1 ^= v0; v0 = (uint64_t)(((v0) << (32)) | ((v0) >> (64 - (32)))); v2 += v3; v3 = (uint64_t)(((v3) << (16)) | ((v3) >> (64 - (16)))); v3 ^= v2; v0 += v3; v3 = (uint64_t)(((v3) << (21)) | ((v3) >> (64 - (21)))); v3 ^= v0; v2 += v1; v1 = (uint64_t)(((v1) << (17)) | ((v1) >> (64 - (17)))); v1 ^= v2; v2 = (uint64_t)(((v2) << (32)) | ((v2) >> (64 - (32)))); } while (0);
    do { v0 += v1; v1 = (uint64_t)(((v1) << (13)) | ((v1) >> (64 - (13)))); v1 ^= v0; v0 = (uint64_t)(((v0) << (32)) | ((v0) >> (64 - (32)))); v2 += v3; v3 = (uint64_t)(((v3) << (16)) | ((v3) >> (64 - (16)))); v3 ^= v2; v0 += v3; v3 = (uint64_t)(((v3) << (21)) | ((v3) >> (64 - (21)))); v3 ^= v0; v2 += v1; v1 = (uint64_t)(((v1) << (17)) | ((v1) >> (64 - (17)))); v1 ^= v2; v2 = (uint64_t)(((v2) << (32)) | ((v2) >> (64 - (32)))); } while (0);

    b = v0 ^ v1 ^ v2 ^ v3;
    ((out))[0] = (uint8_t)(((uint32_t)((b)))); ((out))[1] = (uint8_t)(((uint32_t)((b))) >> 8); ((out))[2] = (uint8_t)(((uint32_t)((b))) >> 16); ((out))[3] = (uint8_t)(((uint32_t)((b))) >> 24);; ((out) + 4)[0] = (uint8_t)(((uint32_t)((b) >> 32))); ((out) + 4)[1] = (uint8_t)(((uint32_t)((b) >> 32)) >> 8); ((out) + 4)[2] = (uint8_t)(((uint32_t)((b) >> 32)) >> 16); ((out) + 4)[3] = (uint8_t)(((uint32_t)((b) >> 32)) >> 24);;;

    return hash;
}
# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/siphash.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/siphash.c"
# 37 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/siphash.c"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 2
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
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 2
# 38 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/siphash.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 39 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/siphash.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 40 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/siphash.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 41 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/siphash.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/ctype.h" 1
# 42 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/siphash.c" 2
# 89 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/siphash.c"
uint64_t siphash(const uint8_t *in, const size_t inlen, const uint8_t *k) {
    uint64_t hash;
    uint8_t *out = (uint8_t*) &hash;
    uint64_t v0 = 0x736f6d6570736575ULL;
    uint64_t v1 = 0x646f72616e646f6dULL;
    uint64_t v2 = 0x6c7967656e657261ULL;
    uint64_t v3 = 0x7465646279746573ULL;
    uint64_t k0 = (((uint64_t)((k)[0])) | ((uint64_t)((k)[1]) << 8) | ((uint64_t)((k)[2]) << 16) | ((uint64_t)((k)[3]) << 24) | ((uint64_t)((k)[4]) << 32) | ((uint64_t)((k)[5]) << 40) | ((uint64_t)((k)[6]) << 48) | ((uint64_t)((k)[7]) << 56));
    uint64_t k1 = (((uint64_t)((k + 8)[0])) | ((uint64_t)((k + 8)[1]) << 8) | ((uint64_t)((k + 8)[2]) << 16) | ((uint64_t)((k + 8)[3]) << 24) | ((uint64_t)((k + 8)[4]) << 32) | ((uint64_t)((k + 8)[5]) << 40) | ((uint64_t)((k + 8)[6]) << 48) | ((uint64_t)((k + 8)[7]) << 56));
    uint64_t m;
    const uint8_t *end = in + inlen - (inlen % sizeof(uint64_t));
    const int left = inlen & 7;
    uint64_t b = ((uint64_t)inlen) << 56;
    v3 ^= k1;
    v2 ^= k0;
    v1 ^= k1;
    v0 ^= k0;

    for (; in != end; in += 8) {
        m = (((uint64_t)((in)[0])) | ((uint64_t)((in)[1]) << 8) | ((uint64_t)((in)[2]) << 16) | ((uint64_t)((in)[3]) << 24) | ((uint64_t)((in)[4]) << 32) | ((uint64_t)((in)[5]) << 40) | ((uint64_t)((in)[6]) << 48) | ((uint64_t)((in)[7]) << 56));
        v3 ^= m;

        do { v0 += v1; v1 = (uint64_t)(((v1) << (13)) | ((v1) >> (64 - (13)))); v1 ^= v0; v0 = (uint64_t)(((v0) << (32)) | ((v0) >> (64 - (32)))); v2 += v3; v3 = (uint64_t)(((v3) << (16)) | ((v3) >> (64 - (16)))); v3 ^= v2; v0 += v3; v3 = (uint64_t)(((v3) << (21)) | ((v3) >> (64 - (21)))); v3 ^= v0; v2 += v1; v1 = (uint64_t)(((v1) << (17)) | ((v1) >> (64 - (17)))); v1 ^= v2; v2 = (uint64_t)(((v2) << (32)) | ((v2) >> (64 - (32)))); } while (0);
        do { v0 += v1; v1 = (uint64_t)(((v1) << (13)) | ((v1) >> (64 - (13)))); v1 ^= v0; v0 = (uint64_t)(((v0) << (32)) | ((v0) >> (64 - (32)))); v2 += v3; v3 = (uint64_t)(((v3) << (16)) | ((v3) >> (64 - (16)))); v3 ^= v2; v0 += v3; v3 = (uint64_t)(((v3) << (21)) | ((v3) >> (64 - (21)))); v3 ^= v0; v2 += v1; v1 = (uint64_t)(((v1) << (17)) | ((v1) >> (64 - (17)))); v1 ^= v2; v2 = (uint64_t)(((v2) << (32)) | ((v2) >> (64 - (32)))); } while (0);

        v0 ^= m;
    }

    switch (left) {
    case 7: b |= ((uint64_t)in[6]) << 48;
    case 6: b |= ((uint64_t)in[5]) << 40;
    case 5: b |= ((uint64_t)in[4]) << 32;
    case 4: b |= ((uint64_t)in[3]) << 24;
    case 3: b |= ((uint64_t)in[2]) << 16;
    case 2: b |= ((uint64_t)in[1]) << 8;
    case 1: b |= ((uint64_t)in[0]); break;
    case 0: break;
    }

    v3 ^= b;

    do { v0 += v1; v1 = (uint64_t)(((v1) << (13)) | ((v1) >> (64 - (13)))); v1 ^= v0; v0 = (uint64_t)(((v0) << (32)) | ((v0) >> (64 - (32)))); v2 += v3; v3 = (uint64_t)(((v3) << (16)) | ((v3) >> (64 - (16)))); v3 ^= v2; v0 += v3; v3 = (uint64_t)(((v3) << (21)) | ((v3) >> (64 - (21)))); v3 ^= v0; v2 += v1; v1 = (uint64_t)(((v1) << (17)) | ((v1) >> (64 - (17)))); v1 ^= v2; v2 = (uint64_t)(((v2) << (32)) | ((v2) >> (64 - (32)))); } while (0);
    do { v0 += v1; v1 = (uint64_t)(((v1) << (13)) | ((v1) >> (64 - (13)))); v1 ^= v0; v0 = (uint64_t)(((v0) << (32)) | ((v0) >> (64 - (32)))); v2 += v3; v3 = (uint64_t)(((v3) << (16)) | ((v3) >> (64 - (16)))); v3 ^= v2; v0 += v3; v3 = (uint64_t)(((v3) << (21)) | ((v3) >> (64 - (21)))); v3 ^= v0; v2 += v1; v1 = (uint64_t)(((v1) << (17)) | ((v1) >> (64 - (17)))); v1 ^= v2; v2 = (uint64_t)(((v2) << (32)) | ((v2) >> (64 - (32)))); } while (0);

    v0 ^= b;
    v2 ^= 0xff;

    do { v0 += v1; v1 = (uint64_t)(((v1) << (13)) | ((v1) >> (64 - (13)))); v1 ^= v0; v0 = (uint64_t)(((v0) << (32)) | ((v0) >> (64 - (32)))); v2 += v3; v3 = (uint64_t)(((v3) << (16)) | ((v3) >> (64 - (16)))); v3 ^= v2; v0 += v3; v3 = (uint64_t)(((v3) << (21)) | ((v3) >> (64 - (21)))); v3 ^= v0; v2 += v1; v1 = (uint64_t)(((v1) << (17)) | ((v1) >> (64 - (17)))); v1 ^= v2; v2 = (uint64_t)(((v2) << (32)) | ((v2) >> (64 - (32)))); } while (0);
    do { v0 += v1; v1 = (uint64_t)(((v1) << (13)) | ((v1) >> (64 - (13)))); v1 ^= v0; v0 = (uint64_t)(((v0) << (32)) | ((v0) >> (64 - (32)))); v2 += v3; v3 = (uint64_t)(((v3) << (16)) | ((v3) >> (64 - (16)))); v3 ^= v2; v0 += v3; v3 = (uint64_t)(((v3) << (21)) | ((v3) >> (64 - (21)))); v3 ^= v0; v2 += v1; v1 = (uint64_t)(((v1) << (17)) | ((v1) >> (64 - (17)))); v1 ^= v2; v2 = (uint64_t)(((v2) << (32)) | ((v2) >> (64 - (32)))); } while (0);
    do { v0 += v1; v1 = (uint64_t)(((v1) << (13)) | ((v1) >> (64 - (13)))); v1 ^= v0; v0 = (uint64_t)(((v0) << (32)) | ((v0) >> (64 - (32)))); v2 += v3; v3 = (uint64_t)(((v3) << (16)) | ((v3) >> (64 - (16)))); v3 ^= v2; v0 += v3; v3 = (uint64_t)(((v3) << (21)) | ((v3) >> (64 - (21)))); v3 ^= v0; v2 += v1; v1 = (uint64_t)(((v1) << (17)) | ((v1) >> (64 - (17)))); v1 ^= v2; v2 = (uint64_t)(((v2) << (32)) | ((v2) >> (64 - (32)))); } while (0);
    do { v0 += v1; v1 = (uint64_t)(((v1) << (13)) | ((v1) >> (64 - (13)))); v1 ^= v0; v0 = (uint64_t)(((v0) << (32)) | ((v0) >> (64 - (32)))); v2 += v3; v3 = (uint64_t)(((v3) << (16)) | ((v3) >> (64 - (16)))); v3 ^= v2; v0 += v3; v3 = (uint64_t)(((v3) << (21)) | ((v3) >> (64 - (21)))); v3 ^= v0; v2 += v1; v1 = (uint64_t)(((v1) << (17)) | ((v1) >> (64 - (17)))); v1 ^= v2; v2 = (uint64_t)(((v2) << (32)) | ((v2) >> (64 - (32)))); } while (0);

    b = v0 ^ v1 ^ v2 ^ v3;
    ((out))[0] = (uint8_t)(((uint32_t)((b)))); ((out))[1] = (uint8_t)(((uint32_t)((b))) >> 8); ((out))[2] = (uint8_t)(((uint32_t)((b))) >> 16); ((out))[3] = (uint8_t)(((uint32_t)((b))) >> 24);; ((out) + 4)[0] = (uint8_t)(((uint32_t)((b) >> 32))); ((out) + 4)[1] = (uint8_t)(((uint32_t)((b) >> 32)) >> 8); ((out) + 4)[2] = (uint8_t)(((uint32_t)((b) >> 32)) >> 16); ((out) + 4)[3] = (uint8_t)(((uint32_t)((b) >> 32)) >> 24);;;

    return hash;
}

uint64_t siphash_nocase(const uint8_t *in, const size_t inlen, const uint8_t *k)
{
    uint64_t hash;
    uint8_t *out = (uint8_t*) &hash;
    uint64_t v0 = 0x736f6d6570736575ULL;
    uint64_t v1 = 0x646f72616e646f6dULL;
    uint64_t v2 = 0x6c7967656e657261ULL;
    uint64_t v3 = 0x7465646279746573ULL;
    uint64_t k0 = (((uint64_t)((k)[0])) | ((uint64_t)((k)[1]) << 8) | ((uint64_t)((k)[2]) << 16) | ((uint64_t)((k)[3]) << 24) | ((uint64_t)((k)[4]) << 32) | ((uint64_t)((k)[5]) << 40) | ((uint64_t)((k)[6]) << 48) | ((uint64_t)((k)[7]) << 56));
    uint64_t k1 = (((uint64_t)((k + 8)[0])) | ((uint64_t)((k + 8)[1]) << 8) | ((uint64_t)((k + 8)[2]) << 16) | ((uint64_t)((k + 8)[3]) << 24) | ((uint64_t)((k + 8)[4]) << 32) | ((uint64_t)((k + 8)[5]) << 40) | ((uint64_t)((k + 8)[6]) << 48) | ((uint64_t)((k + 8)[7]) << 56));
    uint64_t m;
    const uint8_t *end = in + inlen - (inlen % sizeof(uint64_t));
    const int left = inlen & 7;
    uint64_t b = ((uint64_t)inlen) << 56;
    v3 ^= k1;
    v2 ^= k0;
    v1 ^= k1;
    v0 ^= k0;

    for (; in != end; in += 8) {
        m = (((uint64_t)(tolower((in)[0]))) | ((uint64_t)(tolower((in)[1])) << 8) | ((uint64_t)(tolower((in)[2])) << 16) | ((uint64_t)(tolower((in)[3])) << 24) | ((uint64_t)(tolower((in)[4])) << 32) | ((uint64_t)(tolower((in)[5])) << 40) | ((uint64_t)(tolower((in)[6])) << 48) | ((uint64_t)(tolower((in)[7])) << 56));
        v3 ^= m;

        do { v0 += v1; v1 = (uint64_t)(((v1) << (13)) | ((v1) >> (64 - (13)))); v1 ^= v0; v0 = (uint64_t)(((v0) << (32)) | ((v0) >> (64 - (32)))); v2 += v3; v3 = (uint64_t)(((v3) << (16)) | ((v3) >> (64 - (16)))); v3 ^= v2; v0 += v3; v3 = (uint64_t)(((v3) << (21)) | ((v3) >> (64 - (21)))); v3 ^= v0; v2 += v1; v1 = (uint64_t)(((v1) << (17)) | ((v1) >> (64 - (17)))); v1 ^= v2; v2 = (uint64_t)(((v2) << (32)) | ((v2) >> (64 - (32)))); } while (0);
        do { v0 += v1; v1 = (uint64_t)(((v1) << (13)) | ((v1) >> (64 - (13)))); v1 ^= v0; v0 = (uint64_t)(((v0) << (32)) | ((v0) >> (64 - (32)))); v2 += v3; v3 = (uint64_t)(((v3) << (16)) | ((v3) >> (64 - (16)))); v3 ^= v2; v0 += v3; v3 = (uint64_t)(((v3) << (21)) | ((v3) >> (64 - (21)))); v3 ^= v0; v2 += v1; v1 = (uint64_t)(((v1) << (17)) | ((v1) >> (64 - (17)))); v1 ^= v2; v2 = (uint64_t)(((v2) << (32)) | ((v2) >> (64 - (32)))); } while (0);

        v0 ^= m;
    }

    switch (left) {
    case 7: b |= ((uint64_t)tolower(in[6])) << 48;
    case 6: b |= ((uint64_t)tolower(in[5])) << 40;
    case 5: b |= ((uint64_t)tolower(in[4])) << 32;
    case 4: b |= ((uint64_t)tolower(in[3])) << 24;
    case 3: b |= ((uint64_t)tolower(in[2])) << 16;
    case 2: b |= ((uint64_t)tolower(in[1])) << 8;
    case 1: b |= ((uint64_t)tolower(in[0])); break;
    case 0: break;
    }

    v3 ^= b;

    do { v0 += v1; v1 = (uint64_t)(((v1) << (13)) | ((v1) >> (64 - (13)))); v1 ^= v0; v0 = (uint64_t)(((v0) << (32)) | ((v0) >> (64 - (32)))); v2 += v3; v3 = (uint64_t)(((v3) << (16)) | ((v3) >> (64 - (16)))); v3 ^= v2; v0 += v3; v3 = (uint64_t)(((v3) << (21)) | ((v3) >> (64 - (21)))); v3 ^= v0; v2 += v1; v1 = (uint64_t)(((v1) << (17)) | ((v1) >> (64 - (17)))); v1 ^= v2; v2 = (uint64_t)(((v2) << (32)) | ((v2) >> (64 - (32)))); } while (0);
    do { v0 += v1; v1 = (uint64_t)(((v1) << (13)) | ((v1) >> (64 - (13)))); v1 ^= v0; v0 = (uint64_t)(((v0) << (32)) | ((v0) >> (64 - (32)))); v2 += v3; v3 = (uint64_t)(((v3) << (16)) | ((v3) >> (64 - (16)))); v3 ^= v2; v0 += v3; v3 = (uint64_t)(((v3) << (21)) | ((v3) >> (64 - (21)))); v3 ^= v0; v2 += v1; v1 = (uint64_t)(((v1) << (17)) | ((v1) >> (64 - (17)))); v1 ^= v2; v2 = (uint64_t)(((v2) << (32)) | ((v2) >> (64 - (32)))); } while (0);

    v0 ^= b;
    v2 ^= 0xff;

    do { v0 += v1; v1 = (uint64_t)(((v1) << (13)) | ((v1) >> (64 - (13)))); v1 ^= v0; v0 = (uint64_t)(((v0) << (32)) | ((v0) >> (64 - (32)))); v2 += v3; v3 = (uint64_t)(((v3) << (16)) | ((v3) >> (64 - (16)))); v3 ^= v2; v0 += v3; v3 = (uint64_t)(((v3) << (21)) | ((v3) >> (64 - (21)))); v3 ^= v0; v2 += v1; v1 = (uint64_t)(((v1) << (17)) | ((v1) >> (64 - (17)))); v1 ^= v2; v2 = (uint64_t)(((v2) << (32)) | ((v2) >> (64 - (32)))); } while (0);
    do { v0 += v1; v1 = (uint64_t)(((v1) << (13)) | ((v1) >> (64 - (13)))); v1 ^= v0; v0 = (uint64_t)(((v0) << (32)) | ((v0) >> (64 - (32)))); v2 += v3; v3 = (uint64_t)(((v3) << (16)) | ((v3) >> (64 - (16)))); v3 ^= v2; v0 += v3; v3 = (uint64_t)(((v3) << (21)) | ((v3) >> (64 - (21)))); v3 ^= v0; v2 += v1; v1 = (uint64_t)(((v1) << (17)) | ((v1) >> (64 - (17)))); v1 ^= v2; v2 = (uint64_t)(((v2) << (32)) | ((v2) >> (64 - (32)))); } while (0);
    do { v0 += v1; v1 = (uint64_t)(((v1) << (13)) | ((v1) >> (64 - (13)))); v1 ^= v0; v0 = (uint64_t)(((v0) << (32)) | ((v0) >> (64 - (32)))); v2 += v3; v3 = (uint64_t)(((v3) << (16)) | ((v3) >> (64 - (16)))); v3 ^= v2; v0 += v3; v3 = (uint64_t)(((v3) << (21)) | ((v3) >> (64 - (21)))); v3 ^= v0; v2 += v1; v1 = (uint64_t)(((v1) << (17)) | ((v1) >> (64 - (17)))); v1 ^= v2; v2 = (uint64_t)(((v2) << (32)) | ((v2) >> (64 - (32)))); } while (0);
    do { v0 += v1; v1 = (uint64_t)(((v1) << (13)) | ((v1) >> (64 - (13)))); v1 ^= v0; v0 = (uint64_t)(((v0) << (32)) | ((v0) >> (64 - (32)))); v2 += v3; v3 = (uint64_t)(((v3) << (16)) | ((v3) >> (64 - (16)))); v3 ^= v2; v0 += v3; v3 = (uint64_t)(((v3) << (21)) | ((v3) >> (64 - (21)))); v3 ^= v0; v2 += v1; v1 = (uint64_t)(((v1) << (17)) | ((v1) >> (64 - (17)))); v1 ^= v2; v2 = (uint64_t)(((v2) << (32)) | ((v2) >> (64 - (32)))); } while (0);

    b = v0 ^ v1 ^ v2 ^ v3;
    ((out))[0] = (uint8_t)(((uint32_t)((b)))); ((out))[1] = (uint8_t)(((uint32_t)((b))) >> 8); ((out))[2] = (uint8_t)(((uint32_t)((b))) >> 16); ((out))[3] = (uint8_t)(((uint32_t)((b))) >> 24);; ((out) + 4)[0] = (uint8_t)(((uint32_t)((b) >> 32))); ((out) + 4)[1] = (uint8_t)(((uint32_t)((b) >> 32)) >> 8); ((out) + 4)[2] = (uint8_t)(((uint32_t)((b) >> 32)) >> 16); ((out) + 4)[3] = (uint8_t)(((uint32_t)((b) >> 32)) >> 24);;;

    return hash;
}
