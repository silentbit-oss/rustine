# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/state.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/state.c"






# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./state.h" 1
# 12 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./state.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/constants.h" 1
# 15 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/constants.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/./platform.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/./platform.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 2
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
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 2
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/./platform.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/port.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/./platform.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/types.h" 1
# 15 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/types.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 16 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/types.h" 2
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/types.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/types.h" 2
# 71 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/types.h"
typedef void* (*brotli_alloc_func)(void* opaque, size_t size);
# 81 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/types.h"
typedef void (*brotli_free_func)(void* opaque, void* address);
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/./platform.h" 2
# 340 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/./platform.h"
static inline uint16_t BrotliUnalignedRead16(const void* p) {
  return *(const uint16_t*)p;
}
static inline uint32_t BrotliUnalignedRead32(const void* p) {
  return *(const uint32_t*)p;
}

static inline uint64_t BrotliUnalignedRead64(const void* p) {
  return *(const uint64_t*)p;
}
static inline void BrotliUnalignedWrite64(void* p, uint64_t v) {
  *(uint64_t*)p = v;
}
# 502 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/./platform.h"
static inline void BrotliRBit(void) { }
# 516 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/./platform.h"
static inline double brotli_min_double (double a, double b) { return a < b ? a : b; } static inline double brotli_max_double (double a, double b) { return a > b ? a : b; } static inline float brotli_min_float (float a, float b) { return a < b ? a : b; } static inline float brotli_max_float (float a, float b) { return a > b ? a : b; } static inline int brotli_min_int (int a, int b) { return a < b ? a : b; } static inline int brotli_max_int (int a, int b) { return a > b ? a : b; }
static inline size_t brotli_min_size_t (size_t a, size_t b) { return a < b ? a : b; } static inline size_t brotli_max_size_t (size_t a, size_t b) { return a > b ? a : b; } static inline uint32_t brotli_min_uint32_t (uint32_t a, uint32_t b) { return a < b ? a : b; } static inline uint32_t brotli_max_uint32_t (uint32_t a, uint32_t b) { return a > b ? a : b; } static inline uint8_t brotli_min_uint8_t (uint8_t a, uint8_t b) { return a < b ? a : b; } static inline uint8_t brotli_max_uint8_t (uint8_t a, uint8_t b) { return a > b ? a : b; }
# 559 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/./platform.h"
 void* BrotliDefaultAllocFunc(void* opaque, size_t size);


 void BrotliDefaultFreeFunc(void* opaque, void* address);

static inline void BrotliSuppressUnusedFunctions(void) {
  (void)(&BrotliSuppressUnusedFunctions);
  (void)(&BrotliUnalignedRead16);
  (void)(&BrotliUnalignedRead32);
  (void)(&BrotliUnalignedRead64);
  (void)(&BrotliUnalignedWrite64);
  (void)(&BrotliUnalignedRead16);
  (void)(&BrotliUnalignedRead32);
  (void)(&BrotliUnalignedRead64);
  (void)(&BrotliUnalignedWrite64);
  (void)(&BrotliRBit);
  (void)(&brotli_min_double);
  (void)(&brotli_max_double);
  (void)(&brotli_min_float);
  (void)(&brotli_max_float);
  (void)(&brotli_min_int);
  (void)(&brotli_max_int);
  (void)(&brotli_min_size_t);
  (void)(&brotli_max_size_t);
  (void)(&brotli_min_uint32_t);
  (void)(&brotli_max_uint32_t);
  (void)(&brotli_min_uint8_t);
  (void)(&brotli_max_uint8_t);
  (void)(&BrotliDefaultAllocFunc);
  (void)(&BrotliDefaultFreeFunc);



}
# 16 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/constants.h" 2
# 105 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/constants.h"
typedef struct BrotliDistanceCodeLimit {
  uint32_t max_alphabet_size;
  uint32_t max_distance;
} BrotliDistanceCodeLimit;
# 127 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/constants.h"
static inline BrotliDistanceCodeLimit BrotliCalculateDistanceCodeLimit(
    uint32_t max_distance, uint32_t npostfix, uint32_t ndirect) {
  BrotliDistanceCodeLimit result;


  (void)(&BrotliCalculateDistanceCodeLimit);
  if (max_distance <= ndirect) {

    result.max_alphabet_size = max_distance + 16;
    result.max_distance = max_distance;
    return result;
  } else {

    uint32_t forbidden_distance = max_distance + 1;

    uint32_t offset = forbidden_distance - ndirect - 1;
    uint32_t ndistbits = 0;
    uint32_t tmp;
    uint32_t half;
    uint32_t group;

    uint32_t postfix = (1u << npostfix) - 1;
    uint32_t extra;
    uint32_t start;

    offset = (offset >> npostfix) + 4;

    tmp = offset / 2;

    while (tmp != 0) {ndistbits++; tmp = tmp >> 1;}

    ndistbits--;

    half = (offset >> ndistbits) & 1;

    group = ((ndistbits - 1) << 1) | half;

    if (group == 0) {

      result.max_alphabet_size = ndirect + 16;
      result.max_distance = ndirect;
      return result;
    }

    group--;

    ndistbits = (group >> 1) + 1;

    extra = (1u << ndistbits) - 1;

    start = (1u << (ndistbits + 1)) - 4;

    start += (group & 1) << ndistbits;

    result.max_alphabet_size = ((group << npostfix) | postfix) + ndirect +
        16 + 1;

    result.max_distance = ((start + extra) << npostfix) + postfix + ndirect + 1;
    return result;
  }
}



typedef struct {
  uint16_t offset;
  uint8_t nbits;
} BrotliPrefixCodeRange;


 extern const BrotliPrefixCodeRange
    _kBrotliPrefixCodeRanges[26];
# 13 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./state.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/dictionary.h" 1
# 19 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/dictionary.h"
typedef struct BrotliDictionary {
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/dictionary.h"
  uint8_t size_bits_by_length[32];


  uint32_t offsets_by_length[32];


  size_t data_size;




  const uint8_t* data;
} BrotliDictionary;

 const BrotliDictionary* BrotliGetDictionary(void);
# 55 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/dictionary.h"
 void BrotliSetDictionaryData(const uint8_t* data);
# 14 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./state.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/platform.h" 1
# 15 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./state.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/transform.h" 1
# 18 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/transform.h"
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
# 75 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/transform.h"
 const BrotliTransforms* BrotliGetTransforms(void);

 int BrotliTransformDictionaryWord(
    uint8_t* dst, const uint8_t* word, int len,
    const BrotliTransforms* transforms, int transform_idx);
# 16 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./state.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/././bit_reader.h" 1
# 12 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/././bit_reader.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 13 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/././bit_reader.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/././../common/constants.h" 1
# 15 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/././bit_reader.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/././../common/platform.h" 1
# 16 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/././bit_reader.h" 2
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/././bit_reader.h"
 extern const uint32_t kBrotliBitMask[33];

static inline uint32_t BitMask(uint32_t n) {
  if ((!!__builtin_constant_p(n)) || (!!0)) {


    return ~((0xFFFFFFFFu) << n);
  } else {
    return kBrotliBitMask[n];
  }
}

typedef struct {
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t* next_in;
  size_t avail_in;
} BrotliBitReader;

typedef struct {
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t* next_in;
  size_t avail_in;
} BrotliBitReaderState;


 void BrotliInitBitReader(BrotliBitReader* const br);






 int BrotliWarmupBitReader(BrotliBitReader* const br);




 int BrotliSafeReadBits32Slow(
    BrotliBitReader* const br, uint32_t n_bits, uint32_t* val);

static inline void BrotliBitReaderSaveState(
    BrotliBitReader* const from, BrotliBitReaderState* to) {
  to->val_ = from->val_;
  to->bit_pos_ = from->bit_pos_;
  to->next_in = from->next_in;
  to->avail_in = from->avail_in;
}

static inline void BrotliBitReaderRestoreState(
    BrotliBitReader* const to, BrotliBitReaderState* from) {
  to->val_ = from->val_;
  to->bit_pos_ = from->bit_pos_;
  to->next_in = from->next_in;
  to->avail_in = from->avail_in;
}

static inline uint32_t BrotliGetAvailableBits(
    const BrotliBitReader* br) {
  return (1 ? 64 : 32) - br->bit_pos_;
}




static inline size_t BrotliGetRemainingBytes(BrotliBitReader* br) {
  static const size_t kCap = (size_t)1 << 30;
  if (br->avail_in > kCap) return kCap;
  return br->avail_in + (BrotliGetAvailableBits(br) >> 3);
}



static inline int BrotliCheckInputAmount(
    BrotliBitReader* const br, size_t num) {
  return (!!(br->avail_in >= num) ? 1 : 0);
}





static inline void BrotliFillBitWindow(
    BrotliBitReader* const br, uint32_t n_bits) {

  if (!(!!0) && (!!__builtin_constant_p(n_bits)) && (n_bits <= 8)) {
    if (br->bit_pos_ >= 56) {
      br->val_ >>= 56;
      br->bit_pos_ ^= 56;
      br->val_ |= BrotliUnalignedRead64(br->next_in) << 8;
      br->avail_in -= 7;
      br->next_in += 7;
    }
  } else if (
      !(!!0) && (!!__builtin_constant_p(n_bits)) && (n_bits <= 16)) {
    if (br->bit_pos_ >= 48) {
      br->val_ >>= 48;
      br->bit_pos_ ^= 48;
      br->val_ |= BrotliUnalignedRead64(br->next_in) << 16;
      br->avail_in -= 6;
      br->next_in += 6;
    }
  } else {
    if (br->bit_pos_ >= 32) {
      br->val_ >>= 32;
      br->bit_pos_ ^= 32;
      br->val_ |= ((uint64_t)BrotliUnalignedRead32(br->next_in)) << 32;
      br->avail_in -= (sizeof(uint64_t) >> 1);
      br->next_in += (sizeof(uint64_t) >> 1);
    }
  }
# 155 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/././bit_reader.h"
}



static inline void BrotliFillBitWindow16(BrotliBitReader* const br) {
  BrotliFillBitWindow(br, 17);
}



static inline int BrotliPullByte(BrotliBitReader* const br) {
  if (br->avail_in == 0) {
    return 0;
  }
  br->val_ >>= 8;

  br->val_ |= ((uint64_t)*br->next_in) << 56;



  br->bit_pos_ -= 8;
  --br->avail_in;
  ++br->next_in;
  return 1;
}



static inline uint64_t BrotliGetBitsUnmasked(
    BrotliBitReader* const br) {
  return br->val_ >> br->bit_pos_;
}



static inline uint32_t BrotliGet16BitsUnmasked(
    BrotliBitReader* const br) {
  BrotliFillBitWindow(br, 16);
  return (uint32_t)BrotliGetBitsUnmasked(br);
}



static inline uint32_t BrotliGetBits(
    BrotliBitReader* const br, uint32_t n_bits) {
  BrotliFillBitWindow(br, n_bits);
  return (uint32_t)BrotliGetBitsUnmasked(br) & BitMask(n_bits);
}



static inline int BrotliSafeGetBits(
    BrotliBitReader* const br, uint32_t n_bits, uint32_t* val) {
  while (BrotliGetAvailableBits(br) < n_bits) {
    if (!BrotliPullByte(br)) {
      return 0;
    }
  }
  *val = (uint32_t)BrotliGetBitsUnmasked(br) & BitMask(n_bits);
  return 1;
}


static inline void BrotliDropBits(
    BrotliBitReader* const br, uint32_t n_bits) {
  br->bit_pos_ += n_bits;
}

static inline void BrotliBitReaderUnload(BrotliBitReader* br) {
  uint32_t unused_bytes = BrotliGetAvailableBits(br) >> 3;
  uint32_t unused_bits = unused_bytes << 3;
  br->avail_in += unused_bytes;
  br->next_in -= unused_bytes;
  if (unused_bits == sizeof(br->val_) << 3) {
    br->val_ = 0;
  } else {
    br->val_ <<= unused_bits;
  }
  br->bit_pos_ += unused_bits;
}



static inline void BrotliTakeBits(
  BrotliBitReader* const br, uint32_t n_bits, uint32_t* val) {
  *val = (uint32_t)BrotliGetBitsUnmasked(br) & BitMask(n_bits);
 
                                                                    ;
  BrotliDropBits(br, n_bits);
}




static inline uint32_t BrotliReadBits24(
    BrotliBitReader* const br, uint32_t n_bits) {
  ;
  if (1 || (n_bits <= 16)) {
    uint32_t val;
    BrotliFillBitWindow(br, n_bits);
    BrotliTakeBits(br, n_bits, &val);
    return val;
  } else {
    uint32_t low_val;
    uint32_t high_val;
    BrotliFillBitWindow(br, 16);
    BrotliTakeBits(br, 16, &low_val);
    BrotliFillBitWindow(br, 8);
    BrotliTakeBits(br, n_bits - 16, &high_val);
    return low_val | (high_val << 16);
  }
}


static inline uint32_t BrotliReadBits32(
    BrotliBitReader* const br, uint32_t n_bits) {
  ;
  if (1 || (n_bits <= 16)) {
    uint32_t val;
    BrotliFillBitWindow(br, n_bits);
    BrotliTakeBits(br, n_bits, &val);
    return val;
  } else {
    uint32_t low_val;
    uint32_t high_val;
    BrotliFillBitWindow(br, 16);
    BrotliTakeBits(br, 16, &low_val);
    BrotliFillBitWindow(br, 16);
    BrotliTakeBits(br, n_bits - 16, &high_val);
    return low_val | (high_val << 16);
  }
}




static inline int BrotliSafeReadBits(
    BrotliBitReader* const br, uint32_t n_bits, uint32_t* val) {
  ;
  while (BrotliGetAvailableBits(br) < n_bits) {
    if (!BrotliPullByte(br)) {
      return 0;
    }
  }
  BrotliTakeBits(br, n_bits, val);
  return 1;
}


static inline int BrotliSafeReadBits32(
    BrotliBitReader* const br, uint32_t n_bits, uint32_t* val) {
  ;
  if (1 || (n_bits <= 24)) {
    while (BrotliGetAvailableBits(br) < n_bits) {
      if (!BrotliPullByte(br)) {
        return 0;
      }
    }
    BrotliTakeBits(br, n_bits, val);
    return 1;
  } else {
    return BrotliSafeReadBits32Slow(br, n_bits, val);
  }
}



static inline int BrotliJumpToByteBoundary(BrotliBitReader* br) {
  uint32_t pad_bits_count = BrotliGetAvailableBits(br) & 0x7;
  uint32_t pad_bits = 0;
  if (pad_bits_count != 0) {
    BrotliTakeBits(br, pad_bits_count, &pad_bits);
  }
  return (!!(pad_bits == 0) ? 1 : 0);
}




static inline void BrotliCopyBytes(uint8_t* dest,
                                          BrotliBitReader* br, size_t num) {
  while (BrotliGetAvailableBits(br) >= 8 && num > 0) {
    *dest = (uint8_t)BrotliGetBitsUnmasked(br);
    BrotliDropBits(br, 8);
    ++dest;
    --num;
  }
  memcpy(dest, br->next_in, num);
  br->avail_in -= num;
  br->next_in += num;
}
# 18 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./state.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/././huffman.h" 1
# 38 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/././huffman.h"
typedef struct {
  uint8_t bits;
  uint16_t value;
} HuffmanCode;

static inline HuffmanCode ConstructHuffmanCode(const uint8_t bits,
    const uint16_t value) {
  HuffmanCode h;
  h.bits = bits;
  h.value = value;
  return h;
}
# 91 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/././huffman.h"
 void BrotliBuildCodeLengthsHuffmanTable(HuffmanCode* root_table,
    const uint8_t* const code_lengths, uint16_t* count);



 uint32_t BrotliBuildHuffmanTable(HuffmanCode* root_table,
    int root_bits, const uint16_t* const symbol_lists, uint16_t* count);





 uint32_t BrotliBuildSimpleHuffmanTable(HuffmanCode* table,
    int root_bits, uint16_t* symbols, uint32_t num_symbols);




typedef struct {
  HuffmanCode** htrees;
  HuffmanCode* codes;
  uint16_t alphabet_size_max;
  uint16_t alphabet_size_limit;
  uint16_t num_htrees;
} HuffmanTreeGroup;
# 19 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./state.h" 2
# 113 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./state.h"
typedef enum {
  BROTLI_STATE_UNINITED,
  BROTLI_STATE_LARGE_WINDOW_BITS,
  BROTLI_STATE_INITIALIZE,
  BROTLI_STATE_METABLOCK_BEGIN,
  BROTLI_STATE_METABLOCK_HEADER,
  BROTLI_STATE_METABLOCK_HEADER_2,
  BROTLI_STATE_CONTEXT_MODES,
  BROTLI_STATE_COMMAND_BEGIN,
  BROTLI_STATE_COMMAND_INNER,
  BROTLI_STATE_COMMAND_POST_DECODE_LITERALS,
  BROTLI_STATE_COMMAND_POST_WRAP_COPY,
  BROTLI_STATE_UNCOMPRESSED,
  BROTLI_STATE_METADATA,
  BROTLI_STATE_COMMAND_INNER_WRITE,
  BROTLI_STATE_METABLOCK_DONE,
  BROTLI_STATE_COMMAND_POST_WRITE_1,
  BROTLI_STATE_COMMAND_POST_WRITE_2,
  BROTLI_STATE_BEFORE_COMPRESSED_METABLOCK_HEADER,
  BROTLI_STATE_HUFFMAN_CODE_0,
  BROTLI_STATE_HUFFMAN_CODE_1,
  BROTLI_STATE_HUFFMAN_CODE_2,
  BROTLI_STATE_HUFFMAN_CODE_3,
  BROTLI_STATE_CONTEXT_MAP_1,
  BROTLI_STATE_CONTEXT_MAP_2,
  BROTLI_STATE_TREE_GROUP,
  BROTLI_STATE_BEFORE_COMPRESSED_METABLOCK_BODY,
  BROTLI_STATE_DONE
} BrotliRunningState;

typedef enum {
  BROTLI_STATE_METABLOCK_HEADER_NONE,
  BROTLI_STATE_METABLOCK_HEADER_EMPTY,
  BROTLI_STATE_METABLOCK_HEADER_NIBBLES,
  BROTLI_STATE_METABLOCK_HEADER_SIZE,
  BROTLI_STATE_METABLOCK_HEADER_UNCOMPRESSED,
  BROTLI_STATE_METABLOCK_HEADER_RESERVED,
  BROTLI_STATE_METABLOCK_HEADER_BYTES,
  BROTLI_STATE_METABLOCK_HEADER_METADATA
} BrotliRunningMetablockHeaderState;

typedef enum {
  BROTLI_STATE_UNCOMPRESSED_NONE,
  BROTLI_STATE_UNCOMPRESSED_WRITE
} BrotliRunningUncompressedState;

typedef enum {
  BROTLI_STATE_TREE_GROUP_NONE,
  BROTLI_STATE_TREE_GROUP_LOOP
} BrotliRunningTreeGroupState;

typedef enum {
  BROTLI_STATE_CONTEXT_MAP_NONE,
  BROTLI_STATE_CONTEXT_MAP_READ_PREFIX,
  BROTLI_STATE_CONTEXT_MAP_HUFFMAN,
  BROTLI_STATE_CONTEXT_MAP_DECODE,
  BROTLI_STATE_CONTEXT_MAP_TRANSFORM
} BrotliRunningContextMapState;

typedef enum {
  BROTLI_STATE_HUFFMAN_NONE,
  BROTLI_STATE_HUFFMAN_SIMPLE_SIZE,
  BROTLI_STATE_HUFFMAN_SIMPLE_READ,
  BROTLI_STATE_HUFFMAN_SIMPLE_BUILD,
  BROTLI_STATE_HUFFMAN_COMPLEX,
  BROTLI_STATE_HUFFMAN_LENGTH_SYMBOLS
} BrotliRunningHuffmanState;

typedef enum {
  BROTLI_STATE_DECODE_UINT8_NONE,
  BROTLI_STATE_DECODE_UINT8_SHORT,
  BROTLI_STATE_DECODE_UINT8_LONG
} BrotliRunningDecodeUint8State;

typedef enum {
  BROTLI_STATE_READ_BLOCK_LENGTH_NONE,
  BROTLI_STATE_READ_BLOCK_LENGTH_SUFFIX
} BrotliRunningReadBlockLengthState;

typedef struct BrotliMetablockHeaderArena {
  BrotliRunningTreeGroupState substate_tree_group;
  BrotliRunningContextMapState substate_context_map;
  BrotliRunningHuffmanState substate_huffman;

  uint32_t sub_loop_counter;

  uint32_t repeat_code_len;
  uint32_t prev_code_len;


  uint32_t symbol;
  uint32_t repeat;
  uint32_t space;


  HuffmanCode table[32];

  uint16_t* symbol_lists;

  uint16_t symbols_lists_array[15 + 1 +
                               704];

  int next_symbol[32];
  uint8_t code_length_code_lengths[(17 + 1)];

  uint16_t code_length_histo[16];


  int htree_index;
  HuffmanCode* next;


  uint32_t context_index;
  uint32_t max_run_length_prefix;
  uint32_t code;
  HuffmanCode context_map_table[646];
} BrotliMetablockHeaderArena;

typedef struct BrotliMetablockBodyArena {
  uint8_t dist_extra_bits[544];
  uint32_t dist_offset[544];
} BrotliMetablockBodyArena;

struct BrotliDecoderStateStruct {
  BrotliRunningState state;


  int loop_counter;

  BrotliBitReader br;

  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void* memory_manager_opaque;



  union {
    uint64_t u64;
    uint8_t u8[8];
  } buffer;
  uint32_t buffer_length;

  int pos;
  int max_backward_distance;
  int max_distance;
  int ringbuffer_size;
  int ringbuffer_mask;
  int dist_rb_idx;
  int dist_rb[4];
  int error_code;
  uint8_t* ringbuffer;
  uint8_t* ringbuffer_end;
  HuffmanCode* htree_command;
  const uint8_t* context_lookup;
  uint8_t* context_map_slice;
  uint8_t* dist_context_map_slice;



  HuffmanTreeGroup literal_hgroup;
  HuffmanTreeGroup insert_copy_hgroup;
  HuffmanTreeGroup distance_hgroup;
  HuffmanCode* block_type_trees;
  HuffmanCode* block_len_trees;


  int trivial_literal_context;


  int distance_context;
  int meta_block_remaining_len;
  uint32_t block_length_index;
  uint32_t block_length[3];
  uint32_t num_block_types[3];
  uint32_t block_type_rb[6];
  uint32_t distance_postfix_bits;
  uint32_t num_direct_distance_codes;
  uint32_t num_dist_htrees;
  uint8_t* dist_context_map;
  HuffmanCode* literal_htree;
  uint8_t dist_htree_index;

  int copy_length;
  int distance_code;


  size_t rb_roundtrips;
  size_t partial_pos_out;


  uint32_t mtf_upper_bound;
  uint32_t mtf[64 + 1];




  BrotliRunningMetablockHeaderState substate_metablock_header;
  BrotliRunningUncompressedState substate_uncompressed;
  BrotliRunningDecodeUint8State substate_decode_uint8;
  BrotliRunningReadBlockLengthState substate_read_block_length;

  unsigned int is_last_metablock : 1;
  unsigned int is_uncompressed : 1;
  unsigned int is_metadata : 1;
  unsigned int should_wrap_ringbuffer : 1;
  unsigned int canny_ringbuffer_allocation : 1;
  unsigned int large_window : 1;
  unsigned int size_nibbles : 8;
  uint32_t window_bits;

  int new_ringbuffer_size;

  uint32_t num_literal_htrees;
  uint8_t* context_map;
  uint8_t* context_modes;

  const BrotliDictionary* dictionary;
  const BrotliTransforms* transforms;

  uint32_t trivial_literal_contexts[8];

  union {
    BrotliMetablockHeaderArena header;
    BrotliMetablockBodyArena body;
  } arena;
};

typedef struct BrotliDecoderStateStruct BrotliDecoderStateInternal;


 int BrotliDecoderStateInit(BrotliDecoderStateInternal* s,
    brotli_alloc_func alloc_func, brotli_free_func free_func, void* opaque);
 void BrotliDecoderStateCleanup(BrotliDecoderStateInternal* s);
 void BrotliDecoderStateMetablockBegin(BrotliDecoderStateInternal* s);
 void BrotliDecoderStateCleanupAfterMetablock(
    BrotliDecoderStateInternal* s);
 int BrotliDecoderHuffmanTreeGroupInit(
    BrotliDecoderStateInternal* s, HuffmanTreeGroup* group, uint32_t alphabet_size_max,
    uint32_t alphabet_size_limit, uint32_t ntrees);
# 8 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/state.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 10 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/state.c" 2


# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./huffman.h" 1
# 13 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/state.c" 2





int BrotliDecoderStateInit(BrotliDecoderStateInternal* s,
    brotli_alloc_func alloc_func, brotli_free_func free_func, void* opaque) {
  if (!alloc_func) {
    s->alloc_func = BrotliDefaultAllocFunc;
    s->free_func = BrotliDefaultFreeFunc;
    s->memory_manager_opaque = 0;
  } else {
    s->alloc_func = alloc_func;
    s->free_func = free_func;
    s->memory_manager_opaque = opaque;
  }

  s->error_code = 0;

  BrotliInitBitReader(&s->br);
  s->state = BROTLI_STATE_UNINITED;
  s->large_window = 0;
  s->substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_NONE;
  s->substate_uncompressed = BROTLI_STATE_UNCOMPRESSED_NONE;
  s->substate_decode_uint8 = BROTLI_STATE_DECODE_UINT8_NONE;
  s->substate_read_block_length = BROTLI_STATE_READ_BLOCK_LENGTH_NONE;

  s->buffer_length = 0;
  s->loop_counter = 0;
  s->pos = 0;
  s->rb_roundtrips = 0;
  s->partial_pos_out = 0;

  s->block_type_trees = 0;
  s->block_len_trees = 0;
  s->ringbuffer = 0;
  s->ringbuffer_size = 0;
  s->new_ringbuffer_size = 0;
  s->ringbuffer_mask = 0;

  s->context_map = 0;
  s->context_modes = 0;
  s->dist_context_map = 0;
  s->context_map_slice = 0;
  s->dist_context_map_slice = 0;

  s->literal_hgroup.codes = 0;
  s->literal_hgroup.htrees = 0;
  s->insert_copy_hgroup.codes = 0;
  s->insert_copy_hgroup.htrees = 0;
  s->distance_hgroup.codes = 0;
  s->distance_hgroup.htrees = 0;

  s->is_last_metablock = 0;
  s->is_uncompressed = 0;
  s->is_metadata = 0;
  s->should_wrap_ringbuffer = 0;
  s->canny_ringbuffer_allocation = 1;

  s->window_bits = 0;
  s->max_distance = 0;
  s->dist_rb[0] = 16;
  s->dist_rb[1] = 15;
  s->dist_rb[2] = 11;
  s->dist_rb[3] = 4;
  s->dist_rb_idx = 0;
  s->block_type_trees = 0;
  s->block_len_trees = 0;

  s->mtf_upper_bound = 63;

  s->dictionary = BrotliGetDictionary();
  s->transforms = BrotliGetTransforms();

  return 1;
}

void BrotliDecoderStateMetablockBegin(BrotliDecoderStateInternal* s) {
  s->meta_block_remaining_len = 0;
  s->block_length[0] = 1U << 24;
  s->block_length[1] = 1U << 24;
  s->block_length[2] = 1U << 24;
  s->num_block_types[0] = 1;
  s->num_block_types[1] = 1;
  s->num_block_types[2] = 1;
  s->block_type_rb[0] = 1;
  s->block_type_rb[1] = 0;
  s->block_type_rb[2] = 1;
  s->block_type_rb[3] = 0;
  s->block_type_rb[4] = 1;
  s->block_type_rb[5] = 0;
  s->context_map = 0;
  s->context_modes = 0;
  s->dist_context_map = 0;
  s->context_map_slice = 0;
  s->literal_htree = 0;
  s->dist_context_map_slice = 0;
  s->dist_htree_index = 0;
  s->context_lookup = 0;
  s->literal_hgroup.codes = 0;
  s->literal_hgroup.htrees = 0;
  s->insert_copy_hgroup.codes = 0;
  s->insert_copy_hgroup.htrees = 0;
  s->distance_hgroup.codes = 0;
  s->distance_hgroup.htrees = 0;
}

void BrotliDecoderStateCleanupAfterMetablock(BrotliDecoderStateInternal* s) {
  { s->free_func(s->memory_manager_opaque, s->context_modes); s->context_modes = 0; };
  { s->free_func(s->memory_manager_opaque, s->context_map); s->context_map = 0; };
  { s->free_func(s->memory_manager_opaque, s->dist_context_map); s->dist_context_map = 0; };
  { s->free_func(s->memory_manager_opaque, s->literal_hgroup.htrees); s->literal_hgroup.htrees = 0; };
  { s->free_func(s->memory_manager_opaque, s->insert_copy_hgroup.htrees); s->insert_copy_hgroup.htrees = 0; };
  { s->free_func(s->memory_manager_opaque, s->distance_hgroup.htrees); s->distance_hgroup.htrees = 0; };
}

void BrotliDecoderStateCleanup(BrotliDecoderStateInternal* s) {
  BrotliDecoderStateCleanupAfterMetablock(s);

  { s->free_func(s->memory_manager_opaque, s->ringbuffer); s->ringbuffer = 0; };
  { s->free_func(s->memory_manager_opaque, s->block_type_trees); s->block_type_trees = 0; };
}

int BrotliDecoderHuffmanTreeGroupInit(BrotliDecoderStateInternal* s,
    HuffmanTreeGroup* group, uint32_t alphabet_size_max,
    uint32_t alphabet_size_limit, uint32_t ntrees) {




  const size_t max_table_size = alphabet_size_limit + 376;
  const size_t code_size = sizeof(HuffmanCode) * ntrees * max_table_size;
  const size_t htree_size = sizeof(HuffmanCode*) * ntrees;

  HuffmanCode** p = (HuffmanCode**)s->alloc_func(s->memory_manager_opaque, code_size + htree_size)
                             ;
  group->alphabet_size_max = (uint16_t)alphabet_size_max;
  group->alphabet_size_limit = (uint16_t)alphabet_size_limit;
  group->num_htrees = (uint16_t)ntrees;
  group->htrees = p;
  group->codes = (HuffmanCode*)(&p[ntrees]);
  return !!p;
}
# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/state.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/state.c"






# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./state.h" 1
# 12 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./state.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/constants.h" 1
# 15 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/constants.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/./platform.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/./platform.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 2
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
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 2
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/./platform.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/port.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/./platform.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/types.h" 1
# 15 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/types.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 16 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/types.h" 2
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/types.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/types.h" 2
# 71 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/types.h"
typedef void* (*brotli_alloc_func)(void* opaque, size_t size);
# 81 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/types.h"
typedef void (*brotli_free_func)(void* opaque, void* address);
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/./platform.h" 2
# 340 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/./platform.h"
static inline uint16_t BrotliUnalignedRead16(const void* p) {
  return *(const uint16_t*)p;
}
static inline uint32_t BrotliUnalignedRead32(const void* p) {
  return *(const uint32_t*)p;
}

static inline uint64_t BrotliUnalignedRead64(const void* p) {
  return *(const uint64_t*)p;
}
static inline void BrotliUnalignedWrite64(void* p, uint64_t v) {
  *(uint64_t*)p = v;
}
# 502 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/./platform.h"
static inline void BrotliRBit(void) { }
# 516 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/./platform.h"
static inline double brotli_min_double (double a, double b) { return a < b ? a : b; } static inline double brotli_max_double (double a, double b) { return a > b ? a : b; } static inline float brotli_min_float (float a, float b) { return a < b ? a : b; } static inline float brotli_max_float (float a, float b) { return a > b ? a : b; } static inline int brotli_min_int (int a, int b) { return a < b ? a : b; } static inline int brotli_max_int (int a, int b) { return a > b ? a : b; }
static inline size_t brotli_min_size_t (size_t a, size_t b) { return a < b ? a : b; } static inline size_t brotli_max_size_t (size_t a, size_t b) { return a > b ? a : b; } static inline uint32_t brotli_min_uint32_t (uint32_t a, uint32_t b) { return a < b ? a : b; } static inline uint32_t brotli_max_uint32_t (uint32_t a, uint32_t b) { return a > b ? a : b; } static inline uint8_t brotli_min_uint8_t (uint8_t a, uint8_t b) { return a < b ? a : b; } static inline uint8_t brotli_max_uint8_t (uint8_t a, uint8_t b) { return a > b ? a : b; }
# 559 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/./platform.h"
 void* BrotliDefaultAllocFunc(void* opaque, size_t size);


 void BrotliDefaultFreeFunc(void* opaque, void* address);

static inline void BrotliSuppressUnusedFunctions(void) {
  (void)(&BrotliSuppressUnusedFunctions);
  (void)(&BrotliUnalignedRead16);
  (void)(&BrotliUnalignedRead32);
  (void)(&BrotliUnalignedRead64);
  (void)(&BrotliUnalignedWrite64);
  (void)(&BrotliUnalignedRead16);
  (void)(&BrotliUnalignedRead32);
  (void)(&BrotliUnalignedRead64);
  (void)(&BrotliUnalignedWrite64);
  (void)(&BrotliRBit);
  (void)(&brotli_min_double);
  (void)(&brotli_max_double);
  (void)(&brotli_min_float);
  (void)(&brotli_max_float);
  (void)(&brotli_min_int);
  (void)(&brotli_max_int);
  (void)(&brotli_min_size_t);
  (void)(&brotli_max_size_t);
  (void)(&brotli_min_uint32_t);
  (void)(&brotli_max_uint32_t);
  (void)(&brotli_min_uint8_t);
  (void)(&brotli_max_uint8_t);
  (void)(&BrotliDefaultAllocFunc);
  (void)(&BrotliDefaultFreeFunc);



}
# 16 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/constants.h" 2
# 105 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/constants.h"
typedef struct BrotliDistanceCodeLimit {
  uint32_t max_alphabet_size;
  uint32_t max_distance;
} BrotliDistanceCodeLimit;
# 127 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/constants.h"
static inline BrotliDistanceCodeLimit BrotliCalculateDistanceCodeLimit(
    uint32_t max_distance, uint32_t npostfix, uint32_t ndirect) {
  BrotliDistanceCodeLimit result;


  (void)(&BrotliCalculateDistanceCodeLimit);
  if (max_distance <= ndirect) {

    result.max_alphabet_size = max_distance + 16;
    result.max_distance = max_distance;
    return result;
  } else {

    uint32_t forbidden_distance = max_distance + 1;

    uint32_t offset = forbidden_distance - ndirect - 1;
    uint32_t ndistbits = 0;
    uint32_t tmp;
    uint32_t half;
    uint32_t group;

    uint32_t postfix = (1u << npostfix) - 1;
    uint32_t extra;
    uint32_t start;

    offset = (offset >> npostfix) + 4;

    tmp = offset / 2;

    while (tmp != 0) {ndistbits++; tmp = tmp >> 1;}

    ndistbits--;

    half = (offset >> ndistbits) & 1;

    group = ((ndistbits - 1) << 1) | half;

    if (group == 0) {

      result.max_alphabet_size = ndirect + 16;
      result.max_distance = ndirect;
      return result;
    }

    group--;

    ndistbits = (group >> 1) + 1;

    extra = (1u << ndistbits) - 1;

    start = (1u << (ndistbits + 1)) - 4;

    start += (group & 1) << ndistbits;

    result.max_alphabet_size = ((group << npostfix) | postfix) + ndirect +
        16 + 1;

    result.max_distance = ((start + extra) << npostfix) + postfix + ndirect + 1;
    return result;
  }
}



typedef struct {
  uint16_t offset;
  uint8_t nbits;
} BrotliPrefixCodeRange;


 extern const BrotliPrefixCodeRange
    _kBrotliPrefixCodeRanges[26];
# 13 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./state.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/dictionary.h" 1
# 19 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/dictionary.h"
typedef struct BrotliDictionary {
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/dictionary.h"
  uint8_t size_bits_by_length[32];


  uint32_t offsets_by_length[32];


  size_t data_size;




  const uint8_t* data;
} BrotliDictionary;

 const BrotliDictionary* BrotliGetDictionary(void);
# 55 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/dictionary.h"
 void BrotliSetDictionaryData(const uint8_t* data);
# 14 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./state.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/platform.h" 1
# 15 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./state.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/transform.h" 1
# 18 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/transform.h"
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
# 75 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/transform.h"
 const BrotliTransforms* BrotliGetTransforms(void);

 int BrotliTransformDictionaryWord(
    uint8_t* dst, const uint8_t* word, int len,
    const BrotliTransforms* transforms, int transform_idx);
# 16 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./state.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/././bit_reader.h" 1
# 12 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/././bit_reader.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 13 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/././bit_reader.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/././../common/constants.h" 1
# 15 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/././bit_reader.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/././../common/platform.h" 1
# 16 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/././bit_reader.h" 2
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/././bit_reader.h"
 extern const uint32_t kBrotliBitMask[33];

static inline uint32_t BitMask(uint32_t n) {
  if ((!!__builtin_constant_p(n)) || (!!0)) {


    return ~((0xFFFFFFFFu) << n);
  } else {
    return kBrotliBitMask[n];
  }
}

typedef struct {
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t* next_in;
  size_t avail_in;
} BrotliBitReader;

typedef struct {
  uint64_t val_;
  uint32_t bit_pos_;
  const uint8_t* next_in;
  size_t avail_in;
} BrotliBitReaderState;


 void BrotliInitBitReader(BrotliBitReader* const br);






 int BrotliWarmupBitReader(BrotliBitReader* const br);




 int BrotliSafeReadBits32Slow(
    BrotliBitReader* const br, uint32_t n_bits, uint32_t* val);

static inline void BrotliBitReaderSaveState(
    BrotliBitReader* const from, BrotliBitReaderState* to) {
  to->val_ = from->val_;
  to->bit_pos_ = from->bit_pos_;
  to->next_in = from->next_in;
  to->avail_in = from->avail_in;
}

static inline void BrotliBitReaderRestoreState(
    BrotliBitReader* const to, BrotliBitReaderState* from) {
  to->val_ = from->val_;
  to->bit_pos_ = from->bit_pos_;
  to->next_in = from->next_in;
  to->avail_in = from->avail_in;
}

static inline uint32_t BrotliGetAvailableBits(
    const BrotliBitReader* br) {
  return (1 ? 64 : 32) - br->bit_pos_;
}




static inline size_t BrotliGetRemainingBytes(BrotliBitReader* br) {
  static const size_t kCap = (size_t)1 << 30;
  if (br->avail_in > kCap) return kCap;
  return br->avail_in + (BrotliGetAvailableBits(br) >> 3);
}



static inline int BrotliCheckInputAmount(
    BrotliBitReader* const br, size_t num) {
  return (!!(br->avail_in >= num) ? 1 : 0);
}





static inline void BrotliFillBitWindow(
    BrotliBitReader* const br, uint32_t n_bits) {

  if (!(!!0) && (!!__builtin_constant_p(n_bits)) && (n_bits <= 8)) {
    if (br->bit_pos_ >= 56) {
      br->val_ >>= 56;
      br->bit_pos_ ^= 56;
      br->val_ |= BrotliUnalignedRead64(br->next_in) << 8;
      br->avail_in -= 7;
      br->next_in += 7;
    }
  } else if (
      !(!!0) && (!!__builtin_constant_p(n_bits)) && (n_bits <= 16)) {
    if (br->bit_pos_ >= 48) {
      br->val_ >>= 48;
      br->bit_pos_ ^= 48;
      br->val_ |= BrotliUnalignedRead64(br->next_in) << 16;
      br->avail_in -= 6;
      br->next_in += 6;
    }
  } else {
    if (br->bit_pos_ >= 32) {
      br->val_ >>= 32;
      br->bit_pos_ ^= 32;
      br->val_ |= ((uint64_t)BrotliUnalignedRead32(br->next_in)) << 32;
      br->avail_in -= (sizeof(uint64_t) >> 1);
      br->next_in += (sizeof(uint64_t) >> 1);
    }
  }
# 155 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/././bit_reader.h"
}



static inline void BrotliFillBitWindow16(BrotliBitReader* const br) {
  BrotliFillBitWindow(br, 17);
}



static inline int BrotliPullByte(BrotliBitReader* const br) {
  if (br->avail_in == 0) {
    return 0;
  }
  br->val_ >>= 8;

  br->val_ |= ((uint64_t)*br->next_in) << 56;



  br->bit_pos_ -= 8;
  --br->avail_in;
  ++br->next_in;
  return 1;
}



static inline uint64_t BrotliGetBitsUnmasked(
    BrotliBitReader* const br) {
  return br->val_ >> br->bit_pos_;
}



static inline uint32_t BrotliGet16BitsUnmasked(
    BrotliBitReader* const br) {
  BrotliFillBitWindow(br, 16);
  return (uint32_t)BrotliGetBitsUnmasked(br);
}



static inline uint32_t BrotliGetBits(
    BrotliBitReader* const br, uint32_t n_bits) {
  BrotliFillBitWindow(br, n_bits);
  return (uint32_t)BrotliGetBitsUnmasked(br) & BitMask(n_bits);
}



static inline int BrotliSafeGetBits(
    BrotliBitReader* const br, uint32_t n_bits, uint32_t* val) {
  while (BrotliGetAvailableBits(br) < n_bits) {
    if (!BrotliPullByte(br)) {
      return 0;
    }
  }
  *val = (uint32_t)BrotliGetBitsUnmasked(br) & BitMask(n_bits);
  return 1;
}


static inline void BrotliDropBits(
    BrotliBitReader* const br, uint32_t n_bits) {
  br->bit_pos_ += n_bits;
}

static inline void BrotliBitReaderUnload(BrotliBitReader* br) {
  uint32_t unused_bytes = BrotliGetAvailableBits(br) >> 3;
  uint32_t unused_bits = unused_bytes << 3;
  br->avail_in += unused_bytes;
  br->next_in -= unused_bytes;
  if (unused_bits == sizeof(br->val_) << 3) {
    br->val_ = 0;
  } else {
    br->val_ <<= unused_bits;
  }
  br->bit_pos_ += unused_bits;
}



static inline void BrotliTakeBits(
  BrotliBitReader* const br, uint32_t n_bits, uint32_t* val) {
  *val = (uint32_t)BrotliGetBitsUnmasked(br) & BitMask(n_bits);
 
                                                                    ;
  BrotliDropBits(br, n_bits);
}




static inline uint32_t BrotliReadBits24(
    BrotliBitReader* const br, uint32_t n_bits) {
  ;
  if (1 || (n_bits <= 16)) {
    uint32_t val;
    BrotliFillBitWindow(br, n_bits);
    BrotliTakeBits(br, n_bits, &val);
    return val;
  } else {
    uint32_t low_val;
    uint32_t high_val;
    BrotliFillBitWindow(br, 16);
    BrotliTakeBits(br, 16, &low_val);
    BrotliFillBitWindow(br, 8);
    BrotliTakeBits(br, n_bits - 16, &high_val);
    return low_val | (high_val << 16);
  }
}


static inline uint32_t BrotliReadBits32(
    BrotliBitReader* const br, uint32_t n_bits) {
  ;
  if (1 || (n_bits <= 16)) {
    uint32_t val;
    BrotliFillBitWindow(br, n_bits);
    BrotliTakeBits(br, n_bits, &val);
    return val;
  } else {
    uint32_t low_val;
    uint32_t high_val;
    BrotliFillBitWindow(br, 16);
    BrotliTakeBits(br, 16, &low_val);
    BrotliFillBitWindow(br, 16);
    BrotliTakeBits(br, n_bits - 16, &high_val);
    return low_val | (high_val << 16);
  }
}




static inline int BrotliSafeReadBits(
    BrotliBitReader* const br, uint32_t n_bits, uint32_t* val) {
  ;
  while (BrotliGetAvailableBits(br) < n_bits) {
    if (!BrotliPullByte(br)) {
      return 0;
    }
  }
  BrotliTakeBits(br, n_bits, val);
  return 1;
}


static inline int BrotliSafeReadBits32(
    BrotliBitReader* const br, uint32_t n_bits, uint32_t* val) {
  ;
  if (1 || (n_bits <= 24)) {
    while (BrotliGetAvailableBits(br) < n_bits) {
      if (!BrotliPullByte(br)) {
        return 0;
      }
    }
    BrotliTakeBits(br, n_bits, val);
    return 1;
  } else {
    return BrotliSafeReadBits32Slow(br, n_bits, val);
  }
}



static inline int BrotliJumpToByteBoundary(BrotliBitReader* br) {
  uint32_t pad_bits_count = BrotliGetAvailableBits(br) & 0x7;
  uint32_t pad_bits = 0;
  if (pad_bits_count != 0) {
    BrotliTakeBits(br, pad_bits_count, &pad_bits);
  }
  return (!!(pad_bits == 0) ? 1 : 0);
}




static inline void BrotliCopyBytes(uint8_t* dest,
                                          BrotliBitReader* br, size_t num) {
  while (BrotliGetAvailableBits(br) >= 8 && num > 0) {
    *dest = (uint8_t)BrotliGetBitsUnmasked(br);
    BrotliDropBits(br, 8);
    ++dest;
    --num;
  }
  memcpy(dest, br->next_in, num);
  br->avail_in -= num;
  br->next_in += num;
}
# 18 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./state.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/././huffman.h" 1
# 38 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/././huffman.h"
typedef struct {
  uint8_t bits;
  uint16_t value;
} HuffmanCode;

static inline HuffmanCode ConstructHuffmanCode(const uint8_t bits,
    const uint16_t value) {
  HuffmanCode h;
  h.bits = bits;
  h.value = value;
  return h;
}
# 91 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/././huffman.h"
 void BrotliBuildCodeLengthsHuffmanTable(HuffmanCode* root_table,
    const uint8_t* const code_lengths, uint16_t* count);



 uint32_t BrotliBuildHuffmanTable(HuffmanCode* root_table,
    int root_bits, const uint16_t* const symbol_lists, uint16_t* count);





 uint32_t BrotliBuildSimpleHuffmanTable(HuffmanCode* table,
    int root_bits, uint16_t* symbols, uint32_t num_symbols);




typedef struct {
  HuffmanCode** htrees;
  HuffmanCode* codes;
  uint16_t alphabet_size_max;
  uint16_t alphabet_size_limit;
  uint16_t num_htrees;
} HuffmanTreeGroup;
# 19 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./state.h" 2
# 113 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./state.h"
typedef enum {
  BROTLI_STATE_UNINITED,
  BROTLI_STATE_LARGE_WINDOW_BITS,
  BROTLI_STATE_INITIALIZE,
  BROTLI_STATE_METABLOCK_BEGIN,
  BROTLI_STATE_METABLOCK_HEADER,
  BROTLI_STATE_METABLOCK_HEADER_2,
  BROTLI_STATE_CONTEXT_MODES,
  BROTLI_STATE_COMMAND_BEGIN,
  BROTLI_STATE_COMMAND_INNER,
  BROTLI_STATE_COMMAND_POST_DECODE_LITERALS,
  BROTLI_STATE_COMMAND_POST_WRAP_COPY,
  BROTLI_STATE_UNCOMPRESSED,
  BROTLI_STATE_METADATA,
  BROTLI_STATE_COMMAND_INNER_WRITE,
  BROTLI_STATE_METABLOCK_DONE,
  BROTLI_STATE_COMMAND_POST_WRITE_1,
  BROTLI_STATE_COMMAND_POST_WRITE_2,
  BROTLI_STATE_BEFORE_COMPRESSED_METABLOCK_HEADER,
  BROTLI_STATE_HUFFMAN_CODE_0,
  BROTLI_STATE_HUFFMAN_CODE_1,
  BROTLI_STATE_HUFFMAN_CODE_2,
  BROTLI_STATE_HUFFMAN_CODE_3,
  BROTLI_STATE_CONTEXT_MAP_1,
  BROTLI_STATE_CONTEXT_MAP_2,
  BROTLI_STATE_TREE_GROUP,
  BROTLI_STATE_BEFORE_COMPRESSED_METABLOCK_BODY,
  BROTLI_STATE_DONE
} BrotliRunningState;

typedef enum {
  BROTLI_STATE_METABLOCK_HEADER_NONE,
  BROTLI_STATE_METABLOCK_HEADER_EMPTY,
  BROTLI_STATE_METABLOCK_HEADER_NIBBLES,
  BROTLI_STATE_METABLOCK_HEADER_SIZE,
  BROTLI_STATE_METABLOCK_HEADER_UNCOMPRESSED,
  BROTLI_STATE_METABLOCK_HEADER_RESERVED,
  BROTLI_STATE_METABLOCK_HEADER_BYTES,
  BROTLI_STATE_METABLOCK_HEADER_METADATA
} BrotliRunningMetablockHeaderState;

typedef enum {
  BROTLI_STATE_UNCOMPRESSED_NONE,
  BROTLI_STATE_UNCOMPRESSED_WRITE
} BrotliRunningUncompressedState;

typedef enum {
  BROTLI_STATE_TREE_GROUP_NONE,
  BROTLI_STATE_TREE_GROUP_LOOP
} BrotliRunningTreeGroupState;

typedef enum {
  BROTLI_STATE_CONTEXT_MAP_NONE,
  BROTLI_STATE_CONTEXT_MAP_READ_PREFIX,
  BROTLI_STATE_CONTEXT_MAP_HUFFMAN,
  BROTLI_STATE_CONTEXT_MAP_DECODE,
  BROTLI_STATE_CONTEXT_MAP_TRANSFORM
} BrotliRunningContextMapState;

typedef enum {
  BROTLI_STATE_HUFFMAN_NONE,
  BROTLI_STATE_HUFFMAN_SIMPLE_SIZE,
  BROTLI_STATE_HUFFMAN_SIMPLE_READ,
  BROTLI_STATE_HUFFMAN_SIMPLE_BUILD,
  BROTLI_STATE_HUFFMAN_COMPLEX,
  BROTLI_STATE_HUFFMAN_LENGTH_SYMBOLS
} BrotliRunningHuffmanState;

typedef enum {
  BROTLI_STATE_DECODE_UINT8_NONE,
  BROTLI_STATE_DECODE_UINT8_SHORT,
  BROTLI_STATE_DECODE_UINT8_LONG
} BrotliRunningDecodeUint8State;

typedef enum {
  BROTLI_STATE_READ_BLOCK_LENGTH_NONE,
  BROTLI_STATE_READ_BLOCK_LENGTH_SUFFIX
} BrotliRunningReadBlockLengthState;

typedef struct BrotliMetablockHeaderArena {
  BrotliRunningTreeGroupState substate_tree_group;
  BrotliRunningContextMapState substate_context_map;
  BrotliRunningHuffmanState substate_huffman;

  uint32_t sub_loop_counter;

  uint32_t repeat_code_len;
  uint32_t prev_code_len;


  uint32_t symbol;
  uint32_t repeat;
  uint32_t space;


  HuffmanCode table[32];

  uint16_t* symbol_lists;

  uint16_t symbols_lists_array[15 + 1 +
                               704];

  int next_symbol[32];
  uint8_t code_length_code_lengths[(17 + 1)];

  uint16_t code_length_histo[16];


  int htree_index;
  HuffmanCode* next;


  uint32_t context_index;
  uint32_t max_run_length_prefix;
  uint32_t code;
  HuffmanCode context_map_table[646];
} BrotliMetablockHeaderArena;

typedef struct BrotliMetablockBodyArena {
  uint8_t dist_extra_bits[544];
  uint32_t dist_offset[544];
} BrotliMetablockBodyArena;

struct BrotliDecoderStateStruct {
  BrotliRunningState state;


  int loop_counter;

  BrotliBitReader br;

  brotli_alloc_func alloc_func;
  brotli_free_func free_func;
  void* memory_manager_opaque;



  union {
    uint64_t u64;
    uint8_t u8[8];
  } buffer;
  uint32_t buffer_length;

  int pos;
  int max_backward_distance;
  int max_distance;
  int ringbuffer_size;
  int ringbuffer_mask;
  int dist_rb_idx;
  int dist_rb[4];
  int error_code;
  uint8_t* ringbuffer;
  uint8_t* ringbuffer_end;
  HuffmanCode* htree_command;
  const uint8_t* context_lookup;
  uint8_t* context_map_slice;
  uint8_t* dist_context_map_slice;



  HuffmanTreeGroup literal_hgroup;
  HuffmanTreeGroup insert_copy_hgroup;
  HuffmanTreeGroup distance_hgroup;
  HuffmanCode* block_type_trees;
  HuffmanCode* block_len_trees;


  int trivial_literal_context;


  int distance_context;
  int meta_block_remaining_len;
  uint32_t block_length_index;
  uint32_t block_length[3];
  uint32_t num_block_types[3];
  uint32_t block_type_rb[6];
  uint32_t distance_postfix_bits;
  uint32_t num_direct_distance_codes;
  uint32_t num_dist_htrees;
  uint8_t* dist_context_map;
  HuffmanCode* literal_htree;
  uint8_t dist_htree_index;

  int copy_length;
  int distance_code;


  size_t rb_roundtrips;
  size_t partial_pos_out;


  uint32_t mtf_upper_bound;
  uint32_t mtf[64 + 1];




  BrotliRunningMetablockHeaderState substate_metablock_header;
  BrotliRunningUncompressedState substate_uncompressed;
  BrotliRunningDecodeUint8State substate_decode_uint8;
  BrotliRunningReadBlockLengthState substate_read_block_length;

  unsigned int is_last_metablock : 1;
  unsigned int is_uncompressed : 1;
  unsigned int is_metadata : 1;
  unsigned int should_wrap_ringbuffer : 1;
  unsigned int canny_ringbuffer_allocation : 1;
  unsigned int large_window : 1;
  unsigned int size_nibbles : 8;
  uint32_t window_bits;

  int new_ringbuffer_size;

  uint32_t num_literal_htrees;
  uint8_t* context_map;
  uint8_t* context_modes;

  const BrotliDictionary* dictionary;
  const BrotliTransforms* transforms;

  uint32_t trivial_literal_contexts[8];

  union {
    BrotliMetablockHeaderArena header;
    BrotliMetablockBodyArena body;
  } arena;
};

typedef struct BrotliDecoderStateStruct BrotliDecoderStateInternal;


 int BrotliDecoderStateInit(BrotliDecoderStateInternal* s,
    brotli_alloc_func alloc_func, brotli_free_func free_func, void* opaque);
 void BrotliDecoderStateCleanup(BrotliDecoderStateInternal* s);
 void BrotliDecoderStateMetablockBegin(BrotliDecoderStateInternal* s);
 void BrotliDecoderStateCleanupAfterMetablock(
    BrotliDecoderStateInternal* s);
 int BrotliDecoderHuffmanTreeGroupInit(
    BrotliDecoderStateInternal* s, HuffmanTreeGroup* group, uint32_t alphabet_size_max,
    uint32_t alphabet_size_limit, uint32_t ntrees);
# 8 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/state.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 10 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/state.c" 2


# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./huffman.h" 1
# 13 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/state.c" 2





int BrotliDecoderStateInit(BrotliDecoderStateInternal* s,
    brotli_alloc_func alloc_func, brotli_free_func free_func, void* opaque) {
  if (!alloc_func) {
    s->alloc_func = BrotliDefaultAllocFunc;
    s->free_func = BrotliDefaultFreeFunc;
    s->memory_manager_opaque = 0;
  } else {
    s->alloc_func = alloc_func;
    s->free_func = free_func;
    s->memory_manager_opaque = opaque;
  }

  s->error_code = 0;

  BrotliInitBitReader(&s->br);
  s->state = BROTLI_STATE_UNINITED;
  s->large_window = 0;
  s->substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_NONE;
  s->substate_uncompressed = BROTLI_STATE_UNCOMPRESSED_NONE;
  s->substate_decode_uint8 = BROTLI_STATE_DECODE_UINT8_NONE;
  s->substate_read_block_length = BROTLI_STATE_READ_BLOCK_LENGTH_NONE;

  s->buffer_length = 0;
  s->loop_counter = 0;
  s->pos = 0;
  s->rb_roundtrips = 0;
  s->partial_pos_out = 0;

  s->block_type_trees = 0;
  s->block_len_trees = 0;
  s->ringbuffer = 0;
  s->ringbuffer_size = 0;
  s->new_ringbuffer_size = 0;
  s->ringbuffer_mask = 0;

  s->context_map = 0;
  s->context_modes = 0;
  s->dist_context_map = 0;
  s->context_map_slice = 0;
  s->dist_context_map_slice = 0;

  s->literal_hgroup.codes = 0;
  s->literal_hgroup.htrees = 0;
  s->insert_copy_hgroup.codes = 0;
  s->insert_copy_hgroup.htrees = 0;
  s->distance_hgroup.codes = 0;
  s->distance_hgroup.htrees = 0;

  s->is_last_metablock = 0;
  s->is_uncompressed = 0;
  s->is_metadata = 0;
  s->should_wrap_ringbuffer = 0;
  s->canny_ringbuffer_allocation = 1;

  s->window_bits = 0;
  s->max_distance = 0;
  s->dist_rb[0] = 16;
  s->dist_rb[1] = 15;
  s->dist_rb[2] = 11;
  s->dist_rb[3] = 4;
  s->dist_rb_idx = 0;
  s->block_type_trees = 0;
  s->block_len_trees = 0;

  s->mtf_upper_bound = 63;

  s->dictionary = BrotliGetDictionary();
  s->transforms = BrotliGetTransforms();

  return 1;
}

void BrotliDecoderStateMetablockBegin(BrotliDecoderStateInternal* s) {
  s->meta_block_remaining_len = 0;
  s->block_length[0] = 1U << 24;
  s->block_length[1] = 1U << 24;
  s->block_length[2] = 1U << 24;
  s->num_block_types[0] = 1;
  s->num_block_types[1] = 1;
  s->num_block_types[2] = 1;
  s->block_type_rb[0] = 1;
  s->block_type_rb[1] = 0;
  s->block_type_rb[2] = 1;
  s->block_type_rb[3] = 0;
  s->block_type_rb[4] = 1;
  s->block_type_rb[5] = 0;
  s->context_map = 0;
  s->context_modes = 0;
  s->dist_context_map = 0;
  s->context_map_slice = 0;
  s->literal_htree = 0;
  s->dist_context_map_slice = 0;
  s->dist_htree_index = 0;
  s->context_lookup = 0;
  s->literal_hgroup.codes = 0;
  s->literal_hgroup.htrees = 0;
  s->insert_copy_hgroup.codes = 0;
  s->insert_copy_hgroup.htrees = 0;
  s->distance_hgroup.codes = 0;
  s->distance_hgroup.htrees = 0;
}

void BrotliDecoderStateCleanupAfterMetablock(BrotliDecoderStateInternal* s) {
  { s->free_func(s->memory_manager_opaque, s->context_modes); s->context_modes = 0; };
  { s->free_func(s->memory_manager_opaque, s->context_map); s->context_map = 0; };
  { s->free_func(s->memory_manager_opaque, s->dist_context_map); s->dist_context_map = 0; };
  { s->free_func(s->memory_manager_opaque, s->literal_hgroup.htrees); s->literal_hgroup.htrees = 0; };
  { s->free_func(s->memory_manager_opaque, s->insert_copy_hgroup.htrees); s->insert_copy_hgroup.htrees = 0; };
  { s->free_func(s->memory_manager_opaque, s->distance_hgroup.htrees); s->distance_hgroup.htrees = 0; };
}

void BrotliDecoderStateCleanup(BrotliDecoderStateInternal* s) {
  BrotliDecoderStateCleanupAfterMetablock(s);

  { s->free_func(s->memory_manager_opaque, s->ringbuffer); s->ringbuffer = 0; };
  { s->free_func(s->memory_manager_opaque, s->block_type_trees); s->block_type_trees = 0; };
}

int BrotliDecoderHuffmanTreeGroupInit(BrotliDecoderStateInternal* s,
    HuffmanTreeGroup* group, uint32_t alphabet_size_max,
    uint32_t alphabet_size_limit, uint32_t ntrees) {




  const size_t max_table_size = alphabet_size_limit + 376;
  const size_t code_size = sizeof(HuffmanCode) * ntrees * max_table_size;
  const size_t htree_size = sizeof(HuffmanCode*) * ntrees;

  HuffmanCode** p = (HuffmanCode**)s->alloc_func(s->memory_manager_opaque, code_size + htree_size)
                             ;
  group->alphabet_size_max = (uint16_t)alphabet_size_max;
  group->alphabet_size_limit = (uint16_t)alphabet_size_limit;
  group->num_htrees = (uint16_t)ntrees;
  group->htrees = p;
  group->codes = (HuffmanCode*)(&p[ntrees]);
  return !!p;
}
