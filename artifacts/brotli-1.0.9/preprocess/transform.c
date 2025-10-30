# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/common/transform.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/common/transform.c"






# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/common/./transform.h" 1
# 11 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/common/./transform.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/port.h" 1
# 12 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/common/./transform.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/types.h" 1
# 15 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/types.h"
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
# 16 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/types.h" 2
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/types.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/types.h" 2
# 71 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/types.h"
typedef void* (*brotli_alloc_func)(void* opaque, size_t size);
# 81 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/types.h"
typedef void (*brotli_free_func)(void* opaque, void* address);
# 13 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/common/./transform.h" 2





enum BrotliWordTransformType {
  BROTLI_TRANSFORM_IDENTITY = 0,
  BROTLI_TRANSFORM_OMIT_LAST_1 = 1,
  BROTLI_TRANSFORM_OMIT_LAST_2 = 2,
  BROTLI_TRANSFORM_OMIT_LAST_3 = 3,
  BROTLI_TRANSFORM_OMIT_LAST_4 = 4,
  BROTLI_TRANSFORM_OMIT_LAST_5 = 5,
  BROTLI_TRANSFORM_OMIT_LAST_6 = 6,
  BROTLI_TRANSFORM_OMIT_LAST_7 = 7,
  BROTLI_TRANSFORM_OMIT_LAST_8 = 8,
  BROTLI_TRANSFORM_OMIT_LAST_9 = 9,
  BROTLI_TRANSFORM_UPPERCASE_FIRST = 10,
  BROTLI_TRANSFORM_UPPERCASE_ALL = 11,
  BROTLI_TRANSFORM_OMIT_FIRST_1 = 12,
  BROTLI_TRANSFORM_OMIT_FIRST_2 = 13,
  BROTLI_TRANSFORM_OMIT_FIRST_3 = 14,
  BROTLI_TRANSFORM_OMIT_FIRST_4 = 15,
  BROTLI_TRANSFORM_OMIT_FIRST_5 = 16,
  BROTLI_TRANSFORM_OMIT_FIRST_6 = 17,
  BROTLI_TRANSFORM_OMIT_FIRST_7 = 18,
  BROTLI_TRANSFORM_OMIT_FIRST_8 = 19,
  BROTLI_TRANSFORM_OMIT_FIRST_9 = 20,
  BROTLI_TRANSFORM_SHIFT_FIRST = 21,
  BROTLI_TRANSFORM_SHIFT_ALL = 22,
  BROTLI_NUM_TRANSFORM_TYPES
};



typedef struct BrotliTransforms {
  uint16_t prefix_suffix_size;

  const uint8_t* prefix_suffix;
  const uint16_t* prefix_suffix_map;
  uint32_t num_transforms;

  const uint8_t* transforms;


  const uint8_t* params;



  int16_t cutOffTransforms[BROTLI_TRANSFORM_OMIT_LAST_9 + 1];
} BrotliTransforms;
# 75 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/common/./transform.h"
 const BrotliTransforms* BrotliGetTransforms(void);

 int BrotliTransformDictionaryWord(
    uint8_t* dst, const uint8_t* word, int len,
    const BrotliTransforms* transforms, int transform_idx);
# 8 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/common/transform.c" 2






static const char kPrefixSuffix[217] =
      "\1 \2, \10 of the \4 of \2s \1.\5 and \4 "

      "in \1\"\4 to \2\">\1\n\2. \1]\5 for \3 a \6 "

      "that \1\'\6 with \6 from \4 by \1(\6. T"

      "he \4 on \4 as \4 is \4ing \2\n\t\1:\3ed "

      "\2=\"\4 at \3ly \1,\2=\'\5.com/\7. This \5"

      " not \3er \3al \4ful \4ive \5less \4es"

      "t \4ize \2\xc2\xa0\4ous \5 the \2e ";


static const uint16_t kPrefixSuffixMap[50] = {
  0x00, 0x02, 0x05, 0x0E, 0x13, 0x16, 0x18, 0x1E, 0x23, 0x25,
  0x2A, 0x2D, 0x2F, 0x32, 0x34, 0x3A, 0x3E, 0x45, 0x47, 0x4E,
  0x55, 0x5A, 0x5C, 0x63, 0x68, 0x6D, 0x72, 0x77, 0x7A, 0x7C,
  0x80, 0x83, 0x88, 0x8C, 0x8E, 0x91, 0x97, 0x9F, 0xA5, 0xA9,
  0xAD, 0xB2, 0xB7, 0xBD, 0xC2, 0xC7, 0xCA, 0xCF, 0xD5, 0xD8
};


static const uint8_t kTransformsData[] = {
  49, BROTLI_TRANSFORM_IDENTITY, 49,
  49, BROTLI_TRANSFORM_IDENTITY, 0,
   0, BROTLI_TRANSFORM_IDENTITY, 0,
  49, BROTLI_TRANSFORM_OMIT_FIRST_1, 49,
  49, BROTLI_TRANSFORM_UPPERCASE_FIRST, 0,
  49, BROTLI_TRANSFORM_IDENTITY, 47,
   0, BROTLI_TRANSFORM_IDENTITY, 49,
   4, BROTLI_TRANSFORM_IDENTITY, 0,
  49, BROTLI_TRANSFORM_IDENTITY, 3,
  49, BROTLI_TRANSFORM_UPPERCASE_FIRST, 49,
  49, BROTLI_TRANSFORM_IDENTITY, 6,
  49, BROTLI_TRANSFORM_OMIT_FIRST_2, 49,
  49, BROTLI_TRANSFORM_OMIT_LAST_1, 49,
   1, BROTLI_TRANSFORM_IDENTITY, 0,
  49, BROTLI_TRANSFORM_IDENTITY, 1,
   0, BROTLI_TRANSFORM_UPPERCASE_FIRST, 0,
  49, BROTLI_TRANSFORM_IDENTITY, 7,
  49, BROTLI_TRANSFORM_IDENTITY, 9,
  48, BROTLI_TRANSFORM_IDENTITY, 0,
  49, BROTLI_TRANSFORM_IDENTITY, 8,
  49, BROTLI_TRANSFORM_IDENTITY, 5,
  49, BROTLI_TRANSFORM_IDENTITY, 10,
  49, BROTLI_TRANSFORM_IDENTITY, 11,
  49, BROTLI_TRANSFORM_OMIT_LAST_3, 49,
  49, BROTLI_TRANSFORM_IDENTITY, 13,
  49, BROTLI_TRANSFORM_IDENTITY, 14,
  49, BROTLI_TRANSFORM_OMIT_FIRST_3, 49,
  49, BROTLI_TRANSFORM_OMIT_LAST_2, 49,
  49, BROTLI_TRANSFORM_IDENTITY, 15,
  49, BROTLI_TRANSFORM_IDENTITY, 16,
   0, BROTLI_TRANSFORM_UPPERCASE_FIRST, 49,
  49, BROTLI_TRANSFORM_IDENTITY, 12,
   5, BROTLI_TRANSFORM_IDENTITY, 49,
   0, BROTLI_TRANSFORM_IDENTITY, 1,
  49, BROTLI_TRANSFORM_OMIT_FIRST_4, 49,
  49, BROTLI_TRANSFORM_IDENTITY, 18,
  49, BROTLI_TRANSFORM_IDENTITY, 17,
  49, BROTLI_TRANSFORM_IDENTITY, 19,
  49, BROTLI_TRANSFORM_IDENTITY, 20,
  49, BROTLI_TRANSFORM_OMIT_FIRST_5, 49,
  49, BROTLI_TRANSFORM_OMIT_FIRST_6, 49,
  47, BROTLI_TRANSFORM_IDENTITY, 49,
  49, BROTLI_TRANSFORM_OMIT_LAST_4, 49,
  49, BROTLI_TRANSFORM_IDENTITY, 22,
  49, BROTLI_TRANSFORM_UPPERCASE_ALL, 49,
  49, BROTLI_TRANSFORM_IDENTITY, 23,
  49, BROTLI_TRANSFORM_IDENTITY, 24,
  49, BROTLI_TRANSFORM_IDENTITY, 25,
  49, BROTLI_TRANSFORM_OMIT_LAST_7, 49,
  49, BROTLI_TRANSFORM_OMIT_LAST_1, 26,
  49, BROTLI_TRANSFORM_IDENTITY, 27,
  49, BROTLI_TRANSFORM_IDENTITY, 28,
   0, BROTLI_TRANSFORM_IDENTITY, 12,
  49, BROTLI_TRANSFORM_IDENTITY, 29,
  49, BROTLI_TRANSFORM_OMIT_FIRST_9, 49,
  49, BROTLI_TRANSFORM_OMIT_FIRST_7, 49,
  49, BROTLI_TRANSFORM_OMIT_LAST_6, 49,
  49, BROTLI_TRANSFORM_IDENTITY, 21,
  49, BROTLI_TRANSFORM_UPPERCASE_FIRST, 1,
  49, BROTLI_TRANSFORM_OMIT_LAST_8, 49,
  49, BROTLI_TRANSFORM_IDENTITY, 31,
  49, BROTLI_TRANSFORM_IDENTITY, 32,
  47, BROTLI_TRANSFORM_IDENTITY, 3,
  49, BROTLI_TRANSFORM_OMIT_LAST_5, 49,
  49, BROTLI_TRANSFORM_OMIT_LAST_9, 49,
   0, BROTLI_TRANSFORM_UPPERCASE_FIRST, 1,
  49, BROTLI_TRANSFORM_UPPERCASE_FIRST, 8,
   5, BROTLI_TRANSFORM_IDENTITY, 21,
  49, BROTLI_TRANSFORM_UPPERCASE_ALL, 0,
  49, BROTLI_TRANSFORM_UPPERCASE_FIRST, 10,
  49, BROTLI_TRANSFORM_IDENTITY, 30,
   0, BROTLI_TRANSFORM_IDENTITY, 5,
  35, BROTLI_TRANSFORM_IDENTITY, 49,
  47, BROTLI_TRANSFORM_IDENTITY, 2,
  49, BROTLI_TRANSFORM_UPPERCASE_FIRST, 17,
  49, BROTLI_TRANSFORM_IDENTITY, 36,
  49, BROTLI_TRANSFORM_IDENTITY, 33,
   5, BROTLI_TRANSFORM_IDENTITY, 0,
  49, BROTLI_TRANSFORM_UPPERCASE_FIRST, 21,
  49, BROTLI_TRANSFORM_UPPERCASE_FIRST, 5,
  49, BROTLI_TRANSFORM_IDENTITY, 37,
   0, BROTLI_TRANSFORM_IDENTITY, 30,
  49, BROTLI_TRANSFORM_IDENTITY, 38,
   0, BROTLI_TRANSFORM_UPPERCASE_ALL, 0,
  49, BROTLI_TRANSFORM_IDENTITY, 39,
   0, BROTLI_TRANSFORM_UPPERCASE_ALL, 49,
  49, BROTLI_TRANSFORM_IDENTITY, 34,
  49, BROTLI_TRANSFORM_UPPERCASE_ALL, 8,
  49, BROTLI_TRANSFORM_UPPERCASE_FIRST, 12,
   0, BROTLI_TRANSFORM_IDENTITY, 21,
  49, BROTLI_TRANSFORM_IDENTITY, 40,
   0, BROTLI_TRANSFORM_UPPERCASE_FIRST, 12,
  49, BROTLI_TRANSFORM_IDENTITY, 41,
  49, BROTLI_TRANSFORM_IDENTITY, 42,
  49, BROTLI_TRANSFORM_UPPERCASE_ALL, 17,
  49, BROTLI_TRANSFORM_IDENTITY, 43,
   0, BROTLI_TRANSFORM_UPPERCASE_FIRST, 5,
  49, BROTLI_TRANSFORM_UPPERCASE_ALL, 10,
   0, BROTLI_TRANSFORM_IDENTITY, 34,
  49, BROTLI_TRANSFORM_UPPERCASE_FIRST, 33,
  49, BROTLI_TRANSFORM_IDENTITY, 44,
  49, BROTLI_TRANSFORM_UPPERCASE_ALL, 5,
  45, BROTLI_TRANSFORM_IDENTITY, 49,
   0, BROTLI_TRANSFORM_IDENTITY, 33,
  49, BROTLI_TRANSFORM_UPPERCASE_FIRST, 30,
  49, BROTLI_TRANSFORM_UPPERCASE_ALL, 30,
  49, BROTLI_TRANSFORM_IDENTITY, 46,
  49, BROTLI_TRANSFORM_UPPERCASE_ALL, 1,
  49, BROTLI_TRANSFORM_UPPERCASE_FIRST, 34,
   0, BROTLI_TRANSFORM_UPPERCASE_FIRST, 33,
   0, BROTLI_TRANSFORM_UPPERCASE_ALL, 30,
   0, BROTLI_TRANSFORM_UPPERCASE_ALL, 1,
  49, BROTLI_TRANSFORM_UPPERCASE_ALL, 33,
  49, BROTLI_TRANSFORM_UPPERCASE_ALL, 21,
  49, BROTLI_TRANSFORM_UPPERCASE_ALL, 12,
   0, BROTLI_TRANSFORM_UPPERCASE_ALL, 5,
  49, BROTLI_TRANSFORM_UPPERCASE_ALL, 34,
   0, BROTLI_TRANSFORM_UPPERCASE_ALL, 12,
   0, BROTLI_TRANSFORM_UPPERCASE_FIRST, 30,
   0, BROTLI_TRANSFORM_UPPERCASE_ALL, 34,
   0, BROTLI_TRANSFORM_UPPERCASE_FIRST, 34,
};

static const BrotliTransforms kBrotliTransforms = {
  sizeof(kPrefixSuffix),
  (const uint8_t*)kPrefixSuffix,
  kPrefixSuffixMap,
  sizeof(kTransformsData) / (3 * sizeof(kTransformsData[0])),
  kTransformsData,
  0,
  {0, 12, 27, 23, 42, 63, 56, 48, 59, 64}
};

const BrotliTransforms* BrotliGetTransforms(void) {
  return &kBrotliTransforms;
}

static int ToUpperCase(uint8_t* p) {
  if (p[0] < 0xC0) {
    if (p[0] >= 'a' && p[0] <= 'z') {
      p[0] ^= 32;
    }
    return 1;
  }

  if (p[0] < 0xE0) {
    p[1] ^= 32;
    return 2;
  }

  p[2] ^= 5;
  return 3;
}

static int Shift(uint8_t* word, int word_len, uint16_t parameter) {

  uint32_t scalar =
      (parameter & 0x7FFFu) + (0x1000000u - (parameter & 0x8000u));
  if (word[0] < 0x80) {

    scalar += (uint32_t)word[0];
    word[0] = (uint8_t)(scalar & 0x7Fu);
    return 1;
  } else if (word[0] < 0xC0) {

    return 1;
  } else if (word[0] < 0xE0) {

    if (word_len < 2) return 1;
    scalar += (uint32_t)((word[1] & 0x3Fu) | ((word[0] & 0x1Fu) << 6u));
    word[0] = (uint8_t)(0xC0 | ((scalar >> 6u) & 0x1F));
    word[1] = (uint8_t)((word[1] & 0xC0) | (scalar & 0x3F));
    return 2;
  } else if (word[0] < 0xF0) {

    if (word_len < 3) return word_len;
    scalar += (uint32_t)((word[2] & 0x3Fu) | ((word[1] & 0x3Fu) << 6u) |
        ((word[0] & 0x0Fu) << 12u));
    word[0] = (uint8_t)(0xE0 | ((scalar >> 12u) & 0x0F));
    word[1] = (uint8_t)((word[1] & 0xC0) | ((scalar >> 6u) & 0x3F));
    word[2] = (uint8_t)((word[2] & 0xC0) | (scalar & 0x3F));
    return 3;
  } else if (word[0] < 0xF8) {

    if (word_len < 4) return word_len;
    scalar += (uint32_t)((word[3] & 0x3Fu) | ((word[2] & 0x3Fu) << 6u) |
        ((word[1] & 0x3Fu) << 12u) | ((word[0] & 0x07u) << 18u));
    word[0] = (uint8_t)(0xF0 | ((scalar >> 18u) & 0x07));
    word[1] = (uint8_t)((word[1] & 0xC0) | ((scalar >> 12u) & 0x3F));
    word[2] = (uint8_t)((word[2] & 0xC0) | ((scalar >> 6u) & 0x3F));
    word[3] = (uint8_t)((word[3] & 0xC0) | (scalar & 0x3F));
    return 4;
  }
  return 1;
}

int BrotliTransformDictionaryWord(uint8_t* dst, const uint8_t* word, int len,
    const BrotliTransforms* transforms, int transform_idx) {
  int idx = 0;
  const uint8_t* prefix = (&(transforms)->prefix_suffix[ (transforms)->prefix_suffix_map[((transforms)->transforms[((transform_idx) * 3) + 0])]]);
  uint8_t type = ((transforms)->transforms[((transform_idx) * 3) + 1]);
  const uint8_t* suffix = (&(transforms)->prefix_suffix[ (transforms)->prefix_suffix_map[((transforms)->transforms[((transform_idx) * 3) + 2])]]);
  {
    int prefix_len = *prefix++;
    while (prefix_len--) { dst[idx++] = *prefix++; }
  }
  {
    const int t = type;
    int i = 0;
    if (t <= BROTLI_TRANSFORM_OMIT_LAST_9) {
      len -= t;
    } else if (t >= BROTLI_TRANSFORM_OMIT_FIRST_1
        && t <= BROTLI_TRANSFORM_OMIT_FIRST_9) {
      int skip = t - (BROTLI_TRANSFORM_OMIT_FIRST_1 - 1);
      word += skip;
      len -= skip;
    }
    while (i < len) { dst[idx++] = word[i++]; }
    if (t == BROTLI_TRANSFORM_UPPERCASE_FIRST) {
      ToUpperCase(&dst[idx - len]);
    } else if (t == BROTLI_TRANSFORM_UPPERCASE_ALL) {
      uint8_t* uppercase = &dst[idx - len];
      while (len > 0) {
        int step = ToUpperCase(uppercase);
        uppercase += step;
        len -= step;
      }
    } else if (t == BROTLI_TRANSFORM_SHIFT_FIRST) {
      uint16_t param = (uint16_t)(transforms->params[transform_idx * 2]
          + (transforms->params[transform_idx * 2 + 1] << 8u));
      Shift(&dst[idx - len], len, param);
    } else if (t == BROTLI_TRANSFORM_SHIFT_ALL) {
      uint16_t param = (uint16_t)(transforms->params[transform_idx * 2]
          + (transforms->params[transform_idx * 2 + 1] << 8u));
      uint8_t* shift = &dst[idx - len];
      while (len > 0) {
        int step = Shift(shift, len, param);
        shift += step;
        len -= step;
      }
    }
  }
  {
    int suffix_len = *suffix++;
    while (suffix_len--) { dst[idx++] = *suffix++; }
    return idx;
  }
}
# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/common/transform.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/common/transform.c"






# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/common/./transform.h" 1
# 11 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/common/./transform.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/port.h" 1
# 12 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/common/./transform.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/types.h" 1
# 15 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/types.h"
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
# 16 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/types.h" 2
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/types.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/types.h" 2
# 71 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/types.h"
typedef void* (*brotli_alloc_func)(void* opaque, size_t size);
# 81 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/types.h"
typedef void (*brotli_free_func)(void* opaque, void* address);
# 13 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/common/./transform.h" 2





enum BrotliWordTransformType {
  BROTLI_TRANSFORM_IDENTITY = 0,
  BROTLI_TRANSFORM_OMIT_LAST_1 = 1,
  BROTLI_TRANSFORM_OMIT_LAST_2 = 2,
  BROTLI_TRANSFORM_OMIT_LAST_3 = 3,
  BROTLI_TRANSFORM_OMIT_LAST_4 = 4,
  BROTLI_TRANSFORM_OMIT_LAST_5 = 5,
  BROTLI_TRANSFORM_OMIT_LAST_6 = 6,
  BROTLI_TRANSFORM_OMIT_LAST_7 = 7,
  BROTLI_TRANSFORM_OMIT_LAST_8 = 8,
  BROTLI_TRANSFORM_OMIT_LAST_9 = 9,
  BROTLI_TRANSFORM_UPPERCASE_FIRST = 10,
  BROTLI_TRANSFORM_UPPERCASE_ALL = 11,
  BROTLI_TRANSFORM_OMIT_FIRST_1 = 12,
  BROTLI_TRANSFORM_OMIT_FIRST_2 = 13,
  BROTLI_TRANSFORM_OMIT_FIRST_3 = 14,
  BROTLI_TRANSFORM_OMIT_FIRST_4 = 15,
  BROTLI_TRANSFORM_OMIT_FIRST_5 = 16,
  BROTLI_TRANSFORM_OMIT_FIRST_6 = 17,
  BROTLI_TRANSFORM_OMIT_FIRST_7 = 18,
  BROTLI_TRANSFORM_OMIT_FIRST_8 = 19,
  BROTLI_TRANSFORM_OMIT_FIRST_9 = 20,
  BROTLI_TRANSFORM_SHIFT_FIRST = 21,
  BROTLI_TRANSFORM_SHIFT_ALL = 22,
  BROTLI_NUM_TRANSFORM_TYPES
};



typedef struct BrotliTransforms {
  uint16_t prefix_suffix_size;

  const uint8_t* prefix_suffix;
  const uint16_t* prefix_suffix_map;
  uint32_t num_transforms;

  const uint8_t* transforms;


  const uint8_t* params;



  int16_t cutOffTransforms[BROTLI_TRANSFORM_OMIT_LAST_9 + 1];
} BrotliTransforms;
# 75 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/common/./transform.h"
 const BrotliTransforms* BrotliGetTransforms(void);

 int BrotliTransformDictionaryWord(
    uint8_t* dst, const uint8_t* word, int len,
    const BrotliTransforms* transforms, int transform_idx);
# 8 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/common/transform.c" 2






static const char kPrefixSuffix[217] =
      "\1 \2, \10 of the \4 of \2s \1.\5 and \4 "

      "in \1\"\4 to \2\">\1\n\2. \1]\5 for \3 a \6 "

      "that \1\'\6 with \6 from \4 by \1(\6. T"

      "he \4 on \4 as \4 is \4ing \2\n\t\1:\3ed "

      "\2=\"\4 at \3ly \1,\2=\'\5.com/\7. This \5"

      " not \3er \3al \4ful \4ive \5less \4es"

      "t \4ize \2\xc2\xa0\4ous \5 the \2e ";


static const uint16_t kPrefixSuffixMap[50] = {
  0x00, 0x02, 0x05, 0x0E, 0x13, 0x16, 0x18, 0x1E, 0x23, 0x25,
  0x2A, 0x2D, 0x2F, 0x32, 0x34, 0x3A, 0x3E, 0x45, 0x47, 0x4E,
  0x55, 0x5A, 0x5C, 0x63, 0x68, 0x6D, 0x72, 0x77, 0x7A, 0x7C,
  0x80, 0x83, 0x88, 0x8C, 0x8E, 0x91, 0x97, 0x9F, 0xA5, 0xA9,
  0xAD, 0xB2, 0xB7, 0xBD, 0xC2, 0xC7, 0xCA, 0xCF, 0xD5, 0xD8
};


static const uint8_t kTransformsData[] = {
  49, BROTLI_TRANSFORM_IDENTITY, 49,
  49, BROTLI_TRANSFORM_IDENTITY, 0,
   0, BROTLI_TRANSFORM_IDENTITY, 0,
  49, BROTLI_TRANSFORM_OMIT_FIRST_1, 49,
  49, BROTLI_TRANSFORM_UPPERCASE_FIRST, 0,
  49, BROTLI_TRANSFORM_IDENTITY, 47,
   0, BROTLI_TRANSFORM_IDENTITY, 49,
   4, BROTLI_TRANSFORM_IDENTITY, 0,
  49, BROTLI_TRANSFORM_IDENTITY, 3,
  49, BROTLI_TRANSFORM_UPPERCASE_FIRST, 49,
  49, BROTLI_TRANSFORM_IDENTITY, 6,
  49, BROTLI_TRANSFORM_OMIT_FIRST_2, 49,
  49, BROTLI_TRANSFORM_OMIT_LAST_1, 49,
   1, BROTLI_TRANSFORM_IDENTITY, 0,
  49, BROTLI_TRANSFORM_IDENTITY, 1,
   0, BROTLI_TRANSFORM_UPPERCASE_FIRST, 0,
  49, BROTLI_TRANSFORM_IDENTITY, 7,
  49, BROTLI_TRANSFORM_IDENTITY, 9,
  48, BROTLI_TRANSFORM_IDENTITY, 0,
  49, BROTLI_TRANSFORM_IDENTITY, 8,
  49, BROTLI_TRANSFORM_IDENTITY, 5,
  49, BROTLI_TRANSFORM_IDENTITY, 10,
  49, BROTLI_TRANSFORM_IDENTITY, 11,
  49, BROTLI_TRANSFORM_OMIT_LAST_3, 49,
  49, BROTLI_TRANSFORM_IDENTITY, 13,
  49, BROTLI_TRANSFORM_IDENTITY, 14,
  49, BROTLI_TRANSFORM_OMIT_FIRST_3, 49,
  49, BROTLI_TRANSFORM_OMIT_LAST_2, 49,
  49, BROTLI_TRANSFORM_IDENTITY, 15,
  49, BROTLI_TRANSFORM_IDENTITY, 16,
   0, BROTLI_TRANSFORM_UPPERCASE_FIRST, 49,
  49, BROTLI_TRANSFORM_IDENTITY, 12,
   5, BROTLI_TRANSFORM_IDENTITY, 49,
   0, BROTLI_TRANSFORM_IDENTITY, 1,
  49, BROTLI_TRANSFORM_OMIT_FIRST_4, 49,
  49, BROTLI_TRANSFORM_IDENTITY, 18,
  49, BROTLI_TRANSFORM_IDENTITY, 17,
  49, BROTLI_TRANSFORM_IDENTITY, 19,
  49, BROTLI_TRANSFORM_IDENTITY, 20,
  49, BROTLI_TRANSFORM_OMIT_FIRST_5, 49,
  49, BROTLI_TRANSFORM_OMIT_FIRST_6, 49,
  47, BROTLI_TRANSFORM_IDENTITY, 49,
  49, BROTLI_TRANSFORM_OMIT_LAST_4, 49,
  49, BROTLI_TRANSFORM_IDENTITY, 22,
  49, BROTLI_TRANSFORM_UPPERCASE_ALL, 49,
  49, BROTLI_TRANSFORM_IDENTITY, 23,
  49, BROTLI_TRANSFORM_IDENTITY, 24,
  49, BROTLI_TRANSFORM_IDENTITY, 25,
  49, BROTLI_TRANSFORM_OMIT_LAST_7, 49,
  49, BROTLI_TRANSFORM_OMIT_LAST_1, 26,
  49, BROTLI_TRANSFORM_IDENTITY, 27,
  49, BROTLI_TRANSFORM_IDENTITY, 28,
   0, BROTLI_TRANSFORM_IDENTITY, 12,
  49, BROTLI_TRANSFORM_IDENTITY, 29,
  49, BROTLI_TRANSFORM_OMIT_FIRST_9, 49,
  49, BROTLI_TRANSFORM_OMIT_FIRST_7, 49,
  49, BROTLI_TRANSFORM_OMIT_LAST_6, 49,
  49, BROTLI_TRANSFORM_IDENTITY, 21,
  49, BROTLI_TRANSFORM_UPPERCASE_FIRST, 1,
  49, BROTLI_TRANSFORM_OMIT_LAST_8, 49,
  49, BROTLI_TRANSFORM_IDENTITY, 31,
  49, BROTLI_TRANSFORM_IDENTITY, 32,
  47, BROTLI_TRANSFORM_IDENTITY, 3,
  49, BROTLI_TRANSFORM_OMIT_LAST_5, 49,
  49, BROTLI_TRANSFORM_OMIT_LAST_9, 49,
   0, BROTLI_TRANSFORM_UPPERCASE_FIRST, 1,
  49, BROTLI_TRANSFORM_UPPERCASE_FIRST, 8,
   5, BROTLI_TRANSFORM_IDENTITY, 21,
  49, BROTLI_TRANSFORM_UPPERCASE_ALL, 0,
  49, BROTLI_TRANSFORM_UPPERCASE_FIRST, 10,
  49, BROTLI_TRANSFORM_IDENTITY, 30,
   0, BROTLI_TRANSFORM_IDENTITY, 5,
  35, BROTLI_TRANSFORM_IDENTITY, 49,
  47, BROTLI_TRANSFORM_IDENTITY, 2,
  49, BROTLI_TRANSFORM_UPPERCASE_FIRST, 17,
  49, BROTLI_TRANSFORM_IDENTITY, 36,
  49, BROTLI_TRANSFORM_IDENTITY, 33,
   5, BROTLI_TRANSFORM_IDENTITY, 0,
  49, BROTLI_TRANSFORM_UPPERCASE_FIRST, 21,
  49, BROTLI_TRANSFORM_UPPERCASE_FIRST, 5,
  49, BROTLI_TRANSFORM_IDENTITY, 37,
   0, BROTLI_TRANSFORM_IDENTITY, 30,
  49, BROTLI_TRANSFORM_IDENTITY, 38,
   0, BROTLI_TRANSFORM_UPPERCASE_ALL, 0,
  49, BROTLI_TRANSFORM_IDENTITY, 39,
   0, BROTLI_TRANSFORM_UPPERCASE_ALL, 49,
  49, BROTLI_TRANSFORM_IDENTITY, 34,
  49, BROTLI_TRANSFORM_UPPERCASE_ALL, 8,
  49, BROTLI_TRANSFORM_UPPERCASE_FIRST, 12,
   0, BROTLI_TRANSFORM_IDENTITY, 21,
  49, BROTLI_TRANSFORM_IDENTITY, 40,
   0, BROTLI_TRANSFORM_UPPERCASE_FIRST, 12,
  49, BROTLI_TRANSFORM_IDENTITY, 41,
  49, BROTLI_TRANSFORM_IDENTITY, 42,
  49, BROTLI_TRANSFORM_UPPERCASE_ALL, 17,
  49, BROTLI_TRANSFORM_IDENTITY, 43,
   0, BROTLI_TRANSFORM_UPPERCASE_FIRST, 5,
  49, BROTLI_TRANSFORM_UPPERCASE_ALL, 10,
   0, BROTLI_TRANSFORM_IDENTITY, 34,
  49, BROTLI_TRANSFORM_UPPERCASE_FIRST, 33,
  49, BROTLI_TRANSFORM_IDENTITY, 44,
  49, BROTLI_TRANSFORM_UPPERCASE_ALL, 5,
  45, BROTLI_TRANSFORM_IDENTITY, 49,
   0, BROTLI_TRANSFORM_IDENTITY, 33,
  49, BROTLI_TRANSFORM_UPPERCASE_FIRST, 30,
  49, BROTLI_TRANSFORM_UPPERCASE_ALL, 30,
  49, BROTLI_TRANSFORM_IDENTITY, 46,
  49, BROTLI_TRANSFORM_UPPERCASE_ALL, 1,
  49, BROTLI_TRANSFORM_UPPERCASE_FIRST, 34,
   0, BROTLI_TRANSFORM_UPPERCASE_FIRST, 33,
   0, BROTLI_TRANSFORM_UPPERCASE_ALL, 30,
   0, BROTLI_TRANSFORM_UPPERCASE_ALL, 1,
  49, BROTLI_TRANSFORM_UPPERCASE_ALL, 33,
  49, BROTLI_TRANSFORM_UPPERCASE_ALL, 21,
  49, BROTLI_TRANSFORM_UPPERCASE_ALL, 12,
   0, BROTLI_TRANSFORM_UPPERCASE_ALL, 5,
  49, BROTLI_TRANSFORM_UPPERCASE_ALL, 34,
   0, BROTLI_TRANSFORM_UPPERCASE_ALL, 12,
   0, BROTLI_TRANSFORM_UPPERCASE_FIRST, 30,
   0, BROTLI_TRANSFORM_UPPERCASE_ALL, 34,
   0, BROTLI_TRANSFORM_UPPERCASE_FIRST, 34,
};

static const BrotliTransforms kBrotliTransforms = {
  sizeof(kPrefixSuffix),
  (const uint8_t*)kPrefixSuffix,
  kPrefixSuffixMap,
  sizeof(kTransformsData) / (3 * sizeof(kTransformsData[0])),
  kTransformsData,
  0,
  {0, 12, 27, 23, 42, 63, 56, 48, 59, 64}
};

const BrotliTransforms* BrotliGetTransforms(void) {
  return &kBrotliTransforms;
}

static int ToUpperCase(uint8_t* p) {
  if (p[0] < 0xC0) {
    if (p[0] >= 'a' && p[0] <= 'z') {
      p[0] ^= 32;
    }
    return 1;
  }

  if (p[0] < 0xE0) {
    p[1] ^= 32;
    return 2;
  }

  p[2] ^= 5;
  return 3;
}

static int Shift(uint8_t* word, int word_len, uint16_t parameter) {

  uint32_t scalar =
      (parameter & 0x7FFFu) + (0x1000000u - (parameter & 0x8000u));
  if (word[0] < 0x80) {

    scalar += (uint32_t)word[0];
    word[0] = (uint8_t)(scalar & 0x7Fu);
    return 1;
  } else if (word[0] < 0xC0) {

    return 1;
  } else if (word[0] < 0xE0) {

    if (word_len < 2) return 1;
    scalar += (uint32_t)((word[1] & 0x3Fu) | ((word[0] & 0x1Fu) << 6u));
    word[0] = (uint8_t)(0xC0 | ((scalar >> 6u) & 0x1F));
    word[1] = (uint8_t)((word[1] & 0xC0) | (scalar & 0x3F));
    return 2;
  } else if (word[0] < 0xF0) {

    if (word_len < 3) return word_len;
    scalar += (uint32_t)((word[2] & 0x3Fu) | ((word[1] & 0x3Fu) << 6u) |
        ((word[0] & 0x0Fu) << 12u));
    word[0] = (uint8_t)(0xE0 | ((scalar >> 12u) & 0x0F));
    word[1] = (uint8_t)((word[1] & 0xC0) | ((scalar >> 6u) & 0x3F));
    word[2] = (uint8_t)((word[2] & 0xC0) | (scalar & 0x3F));
    return 3;
  } else if (word[0] < 0xF8) {

    if (word_len < 4) return word_len;
    scalar += (uint32_t)((word[3] & 0x3Fu) | ((word[2] & 0x3Fu) << 6u) |
        ((word[1] & 0x3Fu) << 12u) | ((word[0] & 0x07u) << 18u));
    word[0] = (uint8_t)(0xF0 | ((scalar >> 18u) & 0x07));
    word[1] = (uint8_t)((word[1] & 0xC0) | ((scalar >> 12u) & 0x3F));
    word[2] = (uint8_t)((word[2] & 0xC0) | ((scalar >> 6u) & 0x3F));
    word[3] = (uint8_t)((word[3] & 0xC0) | (scalar & 0x3F));
    return 4;
  }
  return 1;
}

int BrotliTransformDictionaryWord(uint8_t* dst, const uint8_t* word, int len,
    const BrotliTransforms* transforms, int transform_idx) {
  int idx = 0;
  const uint8_t* prefix = (&(transforms)->prefix_suffix[ (transforms)->prefix_suffix_map[((transforms)->transforms[((transform_idx) * 3) + 0])]]);
  uint8_t type = ((transforms)->transforms[((transform_idx) * 3) + 1]);
  const uint8_t* suffix = (&(transforms)->prefix_suffix[ (transforms)->prefix_suffix_map[((transforms)->transforms[((transform_idx) * 3) + 2])]]);
  {
    int prefix_len = *prefix++;
    while (prefix_len--) { dst[idx++] = *prefix++; }
  }
  {
    const int t = type;
    int i = 0;
    if (t <= BROTLI_TRANSFORM_OMIT_LAST_9) {
      len -= t;
    } else if (t >= BROTLI_TRANSFORM_OMIT_FIRST_1
        && t <= BROTLI_TRANSFORM_OMIT_FIRST_9) {
      int skip = t - (BROTLI_TRANSFORM_OMIT_FIRST_1 - 1);
      word += skip;
      len -= skip;
    }
    while (i < len) { dst[idx++] = word[i++]; }
    if (t == BROTLI_TRANSFORM_UPPERCASE_FIRST) {
      ToUpperCase(&dst[idx - len]);
    } else if (t == BROTLI_TRANSFORM_UPPERCASE_ALL) {
      uint8_t* uppercase = &dst[idx - len];
      while (len > 0) {
        int step = ToUpperCase(uppercase);
        uppercase += step;
        len -= step;
      }
    } else if (t == BROTLI_TRANSFORM_SHIFT_FIRST) {
      uint16_t param = (uint16_t)(transforms->params[transform_idx * 2]
          + (transforms->params[transform_idx * 2 + 1] << 8u));
      Shift(&dst[idx - len], len, param);
    } else if (t == BROTLI_TRANSFORM_SHIFT_ALL) {
      uint16_t param = (uint16_t)(transforms->params[transform_idx * 2]
          + (transforms->params[transform_idx * 2 + 1] << 8u));
      uint8_t* shift = &dst[idx - len];
      while (len > 0) {
        int step = Shift(shift, len, param);
        shift += step;
        len -= step;
      }
    }
  }
  {
    int suffix_len = *suffix++;
    while (suffix_len--) { dst[idx++] = *suffix++; }
    return idx;
  }
}
