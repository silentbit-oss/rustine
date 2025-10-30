# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c"






# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/decode.h" 1
# 15 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/decode.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/port.h" 1
# 16 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/decode.h" 2
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
# 17 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/decode.h" 2
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/decode.h"
typedef struct BrotliDecoderStateStruct BrotliDecoderState;





typedef enum {

  BROTLI_DECODER_RESULT_ERROR = 0,

  BROTLI_DECODER_RESULT_SUCCESS = 1,

  BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT = 2,

  BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT = 3
} BrotliDecoderResult;
# 112 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/decode.h"
typedef enum {



  BROTLI_DECODER_NO_ERROR = 0 , BROTLI_DECODER_SUCCESS = 1 , BROTLI_DECODER_NEEDS_MORE_INPUT = 2 , BROTLI_DECODER_NEEDS_MORE_OUTPUT = 3 , BROTLI_DECODER_ERROR_FORMAT_EXUBERANT_NIBBLE = -1 , BROTLI_DECODER_ERROR_FORMAT_RESERVED = -2 , BROTLI_DECODER_ERROR_FORMAT_EXUBERANT_META_NIBBLE = -3 , BROTLI_DECODER_ERROR_FORMAT_SIMPLE_HUFFMAN_ALPHABET = -4 , BROTLI_DECODER_ERROR_FORMAT_SIMPLE_HUFFMAN_SAME = -5 , BROTLI_DECODER_ERROR_FORMAT_CL_SPACE = -6 , BROTLI_DECODER_ERROR_FORMAT_HUFFMAN_SPACE = -7 , BROTLI_DECODER_ERROR_FORMAT_CONTEXT_MAP_REPEAT = -8 , BROTLI_DECODER_ERROR_FORMAT_BLOCK_LENGTH_1 = -9 , BROTLI_DECODER_ERROR_FORMAT_BLOCK_LENGTH_2 = -10 , BROTLI_DECODER_ERROR_FORMAT_TRANSFORM = -11 , BROTLI_DECODER_ERROR_FORMAT_DICTIONARY = -12 , BROTLI_DECODER_ERROR_FORMAT_WINDOW_BITS = -13 , BROTLI_DECODER_ERROR_FORMAT_PADDING_1 = -14 , BROTLI_DECODER_ERROR_FORMAT_PADDING_2 = -15 , BROTLI_DECODER_ERROR_FORMAT_DISTANCE = -16 , BROTLI_DECODER_ERROR_DICTIONARY_NOT_SET = -19 , BROTLI_DECODER_ERROR_INVALID_ARGUMENTS = -20 , BROTLI_DECODER_ERROR_ALLOC_CONTEXT_MODES = -21 , BROTLI_DECODER_ERROR_ALLOC_TREE_GROUPS = -22 , BROTLI_DECODER_ERROR_ALLOC_CONTEXT_MAP = -25 , BROTLI_DECODER_ERROR_ALLOC_RING_BUFFER_1 = -26 , BROTLI_DECODER_ERROR_ALLOC_RING_BUFFER_2 = -27 , BROTLI_DECODER_ERROR_ALLOC_BLOCK_TYPE_TREES = -30 , BROTLI_DECODER_ERROR_UNREACHABLE = -31
} BrotliDecoderErrorCode;
# 131 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/decode.h"
typedef enum BrotliDecoderParameter {






  BROTLI_DECODER_PARAM_DISABLE_RING_BUFFER_REALLOCATION = 0,



  BROTLI_DECODER_PARAM_LARGE_WINDOW = 1
} BrotliDecoderParameter;
# 154 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/decode.h"
 int BrotliDecoderSetParameter(
    BrotliDecoderState* state, BrotliDecoderParameter param, uint32_t value);
# 175 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/decode.h"
 BrotliDecoderState* BrotliDecoderCreateInstance(
    brotli_alloc_func alloc_func, brotli_free_func free_func, void* opaque);






 void BrotliDecoderDestroyInstance(BrotliDecoderState* state);
# 202 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/decode.h"
 BrotliDecoderResult BrotliDecoderDecompress(
    size_t encoded_size,
    const uint8_t encoded_buffer[(encoded_size)],
    size_t* decoded_size,
    uint8_t decoded_buffer[(*decoded_size)]);
# 246 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/decode.h"
 BrotliDecoderResult BrotliDecoderDecompressStream(
  BrotliDecoderState* state, size_t* available_in, const uint8_t** next_in,
  size_t* available_out, uint8_t** next_out, size_t* total_out);
# 257 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/decode.h"
 int BrotliDecoderHasMoreOutput(
    const BrotliDecoderState* state);
# 288 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/decode.h"
 const uint8_t* BrotliDecoderTakeOutput(
    BrotliDecoderState* state, size_t* size);
# 301 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/decode.h"
 int BrotliDecoderIsUsed(const BrotliDecoderState* state);
# 311 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/decode.h"
 int BrotliDecoderIsFinished(
    const BrotliDecoderState* state);
# 325 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/decode.h"
 BrotliDecoderErrorCode BrotliDecoderGetErrorCode(
    const BrotliDecoderState* state);




 const char* BrotliDecoderErrorString(BrotliDecoderErrorCode c);






 uint32_t BrotliDecoderVersion(void);
# 8 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 10 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 11 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/constants.h" 1
# 15 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/constants.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/./platform.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/./platform.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/./platform.h" 2
# 340 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/./platform.h"
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
# 502 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/./platform.h"
static inline void BrotliRBit(void) { }
# 516 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/./platform.h"
static inline double brotli_min_double (double a, double b) { return a < b ? a : b; } static inline double brotli_max_double (double a, double b) { return a > b ? a : b; } static inline float brotli_min_float (float a, float b) { return a < b ? a : b; } static inline float brotli_max_float (float a, float b) { return a > b ? a : b; } static inline int brotli_min_int (int a, int b) { return a < b ? a : b; } static inline int brotli_max_int (int a, int b) { return a > b ? a : b; }
static inline size_t brotli_min_size_t (size_t a, size_t b) { return a < b ? a : b; } static inline size_t brotli_max_size_t (size_t a, size_t b) { return a > b ? a : b; } static inline uint32_t brotli_min_uint32_t (uint32_t a, uint32_t b) { return a < b ? a : b; } static inline uint32_t brotli_max_uint32_t (uint32_t a, uint32_t b) { return a > b ? a : b; } static inline uint8_t brotli_min_uint8_t (uint8_t a, uint8_t b) { return a < b ? a : b; } static inline uint8_t brotli_max_uint8_t (uint8_t a, uint8_t b) { return a > b ? a : b; }
# 559 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/./platform.h"
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
# 16 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/constants.h" 2
# 105 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/constants.h"
typedef struct BrotliDistanceCodeLimit {
  uint32_t max_alphabet_size;
  uint32_t max_distance;
} BrotliDistanceCodeLimit;
# 127 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/constants.h"
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
# 13 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/context.h" 1
# 94 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/context.h"
typedef enum ContextType {
  CONTEXT_LSB6 = 0,
  CONTEXT_MSB6 = 1,
  CONTEXT_UTF8 = 2,
  CONTEXT_SIGNED = 3
} ContextType;



 extern const uint8_t _kBrotliContextLookupTable[2048];

typedef const uint8_t* ContextLut;
# 14 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/dictionary.h" 1
# 19 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/dictionary.h"
typedef struct BrotliDictionary {
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/dictionary.h"
  uint8_t size_bits_by_length[32];


  uint32_t offsets_by_length[32];


  size_t data_size;




  const uint8_t* data;
} BrotliDictionary;

 const BrotliDictionary* BrotliGetDictionary(void);
# 55 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/dictionary.h"
 void BrotliSetDictionaryData(const uint8_t* data);
# 15 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/platform.h" 1
# 16 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/transform.h" 1
# 18 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/transform.h"
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
# 75 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/transform.h"
 const BrotliTransforms* BrotliGetTransforms(void);

 int BrotliTransformDictionaryWord(
    uint8_t* dst, const uint8_t* word, int len,
    const BrotliTransforms* transforms, int transform_idx);
# 17 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/version.h" 1
# 18 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./bit_reader.h" 1
# 12 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./bit_reader.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 13 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./bit_reader.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/constants.h" 1
# 15 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./bit_reader.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/platform.h" 1
# 16 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./bit_reader.h" 2
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./bit_reader.h"
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
# 155 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./bit_reader.h"
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
# 19 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./huffman.h" 1
# 38 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./huffman.h"
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
# 91 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./huffman.h"
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
# 20 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./prefix.h" 1
# 16 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./prefix.h"
typedef struct CmdLutElement {
  uint8_t insert_len_extra_bits;
  uint8_t copy_len_extra_bits;
  int8_t distance_code;
  uint8_t context;
  uint16_t insert_len_offset;
  uint16_t copy_len_offset;
} CmdLutElement;

static const CmdLutElement kCmdLut[704] = {
  { 0x00, 0x00, 0, 0x00, 0x0000, 0x0002 },
  { 0x00, 0x00, 0, 0x01, 0x0000, 0x0003 },
  { 0x00, 0x00, 0, 0x02, 0x0000, 0x0004 },
  { 0x00, 0x00, 0, 0x03, 0x0000, 0x0005 },
  { 0x00, 0x00, 0, 0x03, 0x0000, 0x0006 },
  { 0x00, 0x00, 0, 0x03, 0x0000, 0x0007 },
  { 0x00, 0x00, 0, 0x03, 0x0000, 0x0008 },
  { 0x00, 0x00, 0, 0x03, 0x0000, 0x0009 },
  { 0x00, 0x00, 0, 0x00, 0x0001, 0x0002 },
  { 0x00, 0x00, 0, 0x01, 0x0001, 0x0003 },
  { 0x00, 0x00, 0, 0x02, 0x0001, 0x0004 },
  { 0x00, 0x00, 0, 0x03, 0x0001, 0x0005 },
  { 0x00, 0x00, 0, 0x03, 0x0001, 0x0006 },
  { 0x00, 0x00, 0, 0x03, 0x0001, 0x0007 },
  { 0x00, 0x00, 0, 0x03, 0x0001, 0x0008 },
  { 0x00, 0x00, 0, 0x03, 0x0001, 0x0009 },
  { 0x00, 0x00, 0, 0x00, 0x0002, 0x0002 },
  { 0x00, 0x00, 0, 0x01, 0x0002, 0x0003 },
  { 0x00, 0x00, 0, 0x02, 0x0002, 0x0004 },
  { 0x00, 0x00, 0, 0x03, 0x0002, 0x0005 },
  { 0x00, 0x00, 0, 0x03, 0x0002, 0x0006 },
  { 0x00, 0x00, 0, 0x03, 0x0002, 0x0007 },
  { 0x00, 0x00, 0, 0x03, 0x0002, 0x0008 },
  { 0x00, 0x00, 0, 0x03, 0x0002, 0x0009 },
  { 0x00, 0x00, 0, 0x00, 0x0003, 0x0002 },
  { 0x00, 0x00, 0, 0x01, 0x0003, 0x0003 },
  { 0x00, 0x00, 0, 0x02, 0x0003, 0x0004 },
  { 0x00, 0x00, 0, 0x03, 0x0003, 0x0005 },
  { 0x00, 0x00, 0, 0x03, 0x0003, 0x0006 },
  { 0x00, 0x00, 0, 0x03, 0x0003, 0x0007 },
  { 0x00, 0x00, 0, 0x03, 0x0003, 0x0008 },
  { 0x00, 0x00, 0, 0x03, 0x0003, 0x0009 },
  { 0x00, 0x00, 0, 0x00, 0x0004, 0x0002 },
  { 0x00, 0x00, 0, 0x01, 0x0004, 0x0003 },
  { 0x00, 0x00, 0, 0x02, 0x0004, 0x0004 },
  { 0x00, 0x00, 0, 0x03, 0x0004, 0x0005 },
  { 0x00, 0x00, 0, 0x03, 0x0004, 0x0006 },
  { 0x00, 0x00, 0, 0x03, 0x0004, 0x0007 },
  { 0x00, 0x00, 0, 0x03, 0x0004, 0x0008 },
  { 0x00, 0x00, 0, 0x03, 0x0004, 0x0009 },
  { 0x00, 0x00, 0, 0x00, 0x0005, 0x0002 },
  { 0x00, 0x00, 0, 0x01, 0x0005, 0x0003 },
  { 0x00, 0x00, 0, 0x02, 0x0005, 0x0004 },
  { 0x00, 0x00, 0, 0x03, 0x0005, 0x0005 },
  { 0x00, 0x00, 0, 0x03, 0x0005, 0x0006 },
  { 0x00, 0x00, 0, 0x03, 0x0005, 0x0007 },
  { 0x00, 0x00, 0, 0x03, 0x0005, 0x0008 },
  { 0x00, 0x00, 0, 0x03, 0x0005, 0x0009 },
  { 0x01, 0x00, 0, 0x00, 0x0006, 0x0002 },
  { 0x01, 0x00, 0, 0x01, 0x0006, 0x0003 },
  { 0x01, 0x00, 0, 0x02, 0x0006, 0x0004 },
  { 0x01, 0x00, 0, 0x03, 0x0006, 0x0005 },
  { 0x01, 0x00, 0, 0x03, 0x0006, 0x0006 },
  { 0x01, 0x00, 0, 0x03, 0x0006, 0x0007 },
  { 0x01, 0x00, 0, 0x03, 0x0006, 0x0008 },
  { 0x01, 0x00, 0, 0x03, 0x0006, 0x0009 },
  { 0x01, 0x00, 0, 0x00, 0x0008, 0x0002 },
  { 0x01, 0x00, 0, 0x01, 0x0008, 0x0003 },
  { 0x01, 0x00, 0, 0x02, 0x0008, 0x0004 },
  { 0x01, 0x00, 0, 0x03, 0x0008, 0x0005 },
  { 0x01, 0x00, 0, 0x03, 0x0008, 0x0006 },
  { 0x01, 0x00, 0, 0x03, 0x0008, 0x0007 },
  { 0x01, 0x00, 0, 0x03, 0x0008, 0x0008 },
  { 0x01, 0x00, 0, 0x03, 0x0008, 0x0009 },
  { 0x00, 0x01, 0, 0x03, 0x0000, 0x000a },
  { 0x00, 0x01, 0, 0x03, 0x0000, 0x000c },
  { 0x00, 0x02, 0, 0x03, 0x0000, 0x000e },
  { 0x00, 0x02, 0, 0x03, 0x0000, 0x0012 },
  { 0x00, 0x03, 0, 0x03, 0x0000, 0x0016 },
  { 0x00, 0x03, 0, 0x03, 0x0000, 0x001e },
  { 0x00, 0x04, 0, 0x03, 0x0000, 0x0026 },
  { 0x00, 0x04, 0, 0x03, 0x0000, 0x0036 },
  { 0x00, 0x01, 0, 0x03, 0x0001, 0x000a },
  { 0x00, 0x01, 0, 0x03, 0x0001, 0x000c },
  { 0x00, 0x02, 0, 0x03, 0x0001, 0x000e },
  { 0x00, 0x02, 0, 0x03, 0x0001, 0x0012 },
  { 0x00, 0x03, 0, 0x03, 0x0001, 0x0016 },
  { 0x00, 0x03, 0, 0x03, 0x0001, 0x001e },
  { 0x00, 0x04, 0, 0x03, 0x0001, 0x0026 },
  { 0x00, 0x04, 0, 0x03, 0x0001, 0x0036 },
  { 0x00, 0x01, 0, 0x03, 0x0002, 0x000a },
  { 0x00, 0x01, 0, 0x03, 0x0002, 0x000c },
  { 0x00, 0x02, 0, 0x03, 0x0002, 0x000e },
  { 0x00, 0x02, 0, 0x03, 0x0002, 0x0012 },
  { 0x00, 0x03, 0, 0x03, 0x0002, 0x0016 },
  { 0x00, 0x03, 0, 0x03, 0x0002, 0x001e },
  { 0x00, 0x04, 0, 0x03, 0x0002, 0x0026 },
  { 0x00, 0x04, 0, 0x03, 0x0002, 0x0036 },
  { 0x00, 0x01, 0, 0x03, 0x0003, 0x000a },
  { 0x00, 0x01, 0, 0x03, 0x0003, 0x000c },
  { 0x00, 0x02, 0, 0x03, 0x0003, 0x000e },
  { 0x00, 0x02, 0, 0x03, 0x0003, 0x0012 },
  { 0x00, 0x03, 0, 0x03, 0x0003, 0x0016 },
  { 0x00, 0x03, 0, 0x03, 0x0003, 0x001e },
  { 0x00, 0x04, 0, 0x03, 0x0003, 0x0026 },
  { 0x00, 0x04, 0, 0x03, 0x0003, 0x0036 },
  { 0x00, 0x01, 0, 0x03, 0x0004, 0x000a },
  { 0x00, 0x01, 0, 0x03, 0x0004, 0x000c },
  { 0x00, 0x02, 0, 0x03, 0x0004, 0x000e },
  { 0x00, 0x02, 0, 0x03, 0x0004, 0x0012 },
  { 0x00, 0x03, 0, 0x03, 0x0004, 0x0016 },
  { 0x00, 0x03, 0, 0x03, 0x0004, 0x001e },
  { 0x00, 0x04, 0, 0x03, 0x0004, 0x0026 },
  { 0x00, 0x04, 0, 0x03, 0x0004, 0x0036 },
  { 0x00, 0x01, 0, 0x03, 0x0005, 0x000a },
  { 0x00, 0x01, 0, 0x03, 0x0005, 0x000c },
  { 0x00, 0x02, 0, 0x03, 0x0005, 0x000e },
  { 0x00, 0x02, 0, 0x03, 0x0005, 0x0012 },
  { 0x00, 0x03, 0, 0x03, 0x0005, 0x0016 },
  { 0x00, 0x03, 0, 0x03, 0x0005, 0x001e },
  { 0x00, 0x04, 0, 0x03, 0x0005, 0x0026 },
  { 0x00, 0x04, 0, 0x03, 0x0005, 0x0036 },
  { 0x01, 0x01, 0, 0x03, 0x0006, 0x000a },
  { 0x01, 0x01, 0, 0x03, 0x0006, 0x000c },
  { 0x01, 0x02, 0, 0x03, 0x0006, 0x000e },
  { 0x01, 0x02, 0, 0x03, 0x0006, 0x0012 },
  { 0x01, 0x03, 0, 0x03, 0x0006, 0x0016 },
  { 0x01, 0x03, 0, 0x03, 0x0006, 0x001e },
  { 0x01, 0x04, 0, 0x03, 0x0006, 0x0026 },
  { 0x01, 0x04, 0, 0x03, 0x0006, 0x0036 },
  { 0x01, 0x01, 0, 0x03, 0x0008, 0x000a },
  { 0x01, 0x01, 0, 0x03, 0x0008, 0x000c },
  { 0x01, 0x02, 0, 0x03, 0x0008, 0x000e },
  { 0x01, 0x02, 0, 0x03, 0x0008, 0x0012 },
  { 0x01, 0x03, 0, 0x03, 0x0008, 0x0016 },
  { 0x01, 0x03, 0, 0x03, 0x0008, 0x001e },
  { 0x01, 0x04, 0, 0x03, 0x0008, 0x0026 },
  { 0x01, 0x04, 0, 0x03, 0x0008, 0x0036 },
  { 0x00, 0x00, -1, 0x00, 0x0000, 0x0002 },
  { 0x00, 0x00, -1, 0x01, 0x0000, 0x0003 },
  { 0x00, 0x00, -1, 0x02, 0x0000, 0x0004 },
  { 0x00, 0x00, -1, 0x03, 0x0000, 0x0005 },
  { 0x00, 0x00, -1, 0x03, 0x0000, 0x0006 },
  { 0x00, 0x00, -1, 0x03, 0x0000, 0x0007 },
  { 0x00, 0x00, -1, 0x03, 0x0000, 0x0008 },
  { 0x00, 0x00, -1, 0x03, 0x0000, 0x0009 },
  { 0x00, 0x00, -1, 0x00, 0x0001, 0x0002 },
  { 0x00, 0x00, -1, 0x01, 0x0001, 0x0003 },
  { 0x00, 0x00, -1, 0x02, 0x0001, 0x0004 },
  { 0x00, 0x00, -1, 0x03, 0x0001, 0x0005 },
  { 0x00, 0x00, -1, 0x03, 0x0001, 0x0006 },
  { 0x00, 0x00, -1, 0x03, 0x0001, 0x0007 },
  { 0x00, 0x00, -1, 0x03, 0x0001, 0x0008 },
  { 0x00, 0x00, -1, 0x03, 0x0001, 0x0009 },
  { 0x00, 0x00, -1, 0x00, 0x0002, 0x0002 },
  { 0x00, 0x00, -1, 0x01, 0x0002, 0x0003 },
  { 0x00, 0x00, -1, 0x02, 0x0002, 0x0004 },
  { 0x00, 0x00, -1, 0x03, 0x0002, 0x0005 },
  { 0x00, 0x00, -1, 0x03, 0x0002, 0x0006 },
  { 0x00, 0x00, -1, 0x03, 0x0002, 0x0007 },
  { 0x00, 0x00, -1, 0x03, 0x0002, 0x0008 },
  { 0x00, 0x00, -1, 0x03, 0x0002, 0x0009 },
  { 0x00, 0x00, -1, 0x00, 0x0003, 0x0002 },
  { 0x00, 0x00, -1, 0x01, 0x0003, 0x0003 },
  { 0x00, 0x00, -1, 0x02, 0x0003, 0x0004 },
  { 0x00, 0x00, -1, 0x03, 0x0003, 0x0005 },
  { 0x00, 0x00, -1, 0x03, 0x0003, 0x0006 },
  { 0x00, 0x00, -1, 0x03, 0x0003, 0x0007 },
  { 0x00, 0x00, -1, 0x03, 0x0003, 0x0008 },
  { 0x00, 0x00, -1, 0x03, 0x0003, 0x0009 },
  { 0x00, 0x00, -1, 0x00, 0x0004, 0x0002 },
  { 0x00, 0x00, -1, 0x01, 0x0004, 0x0003 },
  { 0x00, 0x00, -1, 0x02, 0x0004, 0x0004 },
  { 0x00, 0x00, -1, 0x03, 0x0004, 0x0005 },
  { 0x00, 0x00, -1, 0x03, 0x0004, 0x0006 },
  { 0x00, 0x00, -1, 0x03, 0x0004, 0x0007 },
  { 0x00, 0x00, -1, 0x03, 0x0004, 0x0008 },
  { 0x00, 0x00, -1, 0x03, 0x0004, 0x0009 },
  { 0x00, 0x00, -1, 0x00, 0x0005, 0x0002 },
  { 0x00, 0x00, -1, 0x01, 0x0005, 0x0003 },
  { 0x00, 0x00, -1, 0x02, 0x0005, 0x0004 },
  { 0x00, 0x00, -1, 0x03, 0x0005, 0x0005 },
  { 0x00, 0x00, -1, 0x03, 0x0005, 0x0006 },
  { 0x00, 0x00, -1, 0x03, 0x0005, 0x0007 },
  { 0x00, 0x00, -1, 0x03, 0x0005, 0x0008 },
  { 0x00, 0x00, -1, 0x03, 0x0005, 0x0009 },
  { 0x01, 0x00, -1, 0x00, 0x0006, 0x0002 },
  { 0x01, 0x00, -1, 0x01, 0x0006, 0x0003 },
  { 0x01, 0x00, -1, 0x02, 0x0006, 0x0004 },
  { 0x01, 0x00, -1, 0x03, 0x0006, 0x0005 },
  { 0x01, 0x00, -1, 0x03, 0x0006, 0x0006 },
  { 0x01, 0x00, -1, 0x03, 0x0006, 0x0007 },
  { 0x01, 0x00, -1, 0x03, 0x0006, 0x0008 },
  { 0x01, 0x00, -1, 0x03, 0x0006, 0x0009 },
  { 0x01, 0x00, -1, 0x00, 0x0008, 0x0002 },
  { 0x01, 0x00, -1, 0x01, 0x0008, 0x0003 },
  { 0x01, 0x00, -1, 0x02, 0x0008, 0x0004 },
  { 0x01, 0x00, -1, 0x03, 0x0008, 0x0005 },
  { 0x01, 0x00, -1, 0x03, 0x0008, 0x0006 },
  { 0x01, 0x00, -1, 0x03, 0x0008, 0x0007 },
  { 0x01, 0x00, -1, 0x03, 0x0008, 0x0008 },
  { 0x01, 0x00, -1, 0x03, 0x0008, 0x0009 },
  { 0x00, 0x01, -1, 0x03, 0x0000, 0x000a },
  { 0x00, 0x01, -1, 0x03, 0x0000, 0x000c },
  { 0x00, 0x02, -1, 0x03, 0x0000, 0x000e },
  { 0x00, 0x02, -1, 0x03, 0x0000, 0x0012 },
  { 0x00, 0x03, -1, 0x03, 0x0000, 0x0016 },
  { 0x00, 0x03, -1, 0x03, 0x0000, 0x001e },
  { 0x00, 0x04, -1, 0x03, 0x0000, 0x0026 },
  { 0x00, 0x04, -1, 0x03, 0x0000, 0x0036 },
  { 0x00, 0x01, -1, 0x03, 0x0001, 0x000a },
  { 0x00, 0x01, -1, 0x03, 0x0001, 0x000c },
  { 0x00, 0x02, -1, 0x03, 0x0001, 0x000e },
  { 0x00, 0x02, -1, 0x03, 0x0001, 0x0012 },
  { 0x00, 0x03, -1, 0x03, 0x0001, 0x0016 },
  { 0x00, 0x03, -1, 0x03, 0x0001, 0x001e },
  { 0x00, 0x04, -1, 0x03, 0x0001, 0x0026 },
  { 0x00, 0x04, -1, 0x03, 0x0001, 0x0036 },
  { 0x00, 0x01, -1, 0x03, 0x0002, 0x000a },
  { 0x00, 0x01, -1, 0x03, 0x0002, 0x000c },
  { 0x00, 0x02, -1, 0x03, 0x0002, 0x000e },
  { 0x00, 0x02, -1, 0x03, 0x0002, 0x0012 },
  { 0x00, 0x03, -1, 0x03, 0x0002, 0x0016 },
  { 0x00, 0x03, -1, 0x03, 0x0002, 0x001e },
  { 0x00, 0x04, -1, 0x03, 0x0002, 0x0026 },
  { 0x00, 0x04, -1, 0x03, 0x0002, 0x0036 },
  { 0x00, 0x01, -1, 0x03, 0x0003, 0x000a },
  { 0x00, 0x01, -1, 0x03, 0x0003, 0x000c },
  { 0x00, 0x02, -1, 0x03, 0x0003, 0x000e },
  { 0x00, 0x02, -1, 0x03, 0x0003, 0x0012 },
  { 0x00, 0x03, -1, 0x03, 0x0003, 0x0016 },
  { 0x00, 0x03, -1, 0x03, 0x0003, 0x001e },
  { 0x00, 0x04, -1, 0x03, 0x0003, 0x0026 },
  { 0x00, 0x04, -1, 0x03, 0x0003, 0x0036 },
  { 0x00, 0x01, -1, 0x03, 0x0004, 0x000a },
  { 0x00, 0x01, -1, 0x03, 0x0004, 0x000c },
  { 0x00, 0x02, -1, 0x03, 0x0004, 0x000e },
  { 0x00, 0x02, -1, 0x03, 0x0004, 0x0012 },
  { 0x00, 0x03, -1, 0x03, 0x0004, 0x0016 },
  { 0x00, 0x03, -1, 0x03, 0x0004, 0x001e },
  { 0x00, 0x04, -1, 0x03, 0x0004, 0x0026 },
  { 0x00, 0x04, -1, 0x03, 0x0004, 0x0036 },
  { 0x00, 0x01, -1, 0x03, 0x0005, 0x000a },
  { 0x00, 0x01, -1, 0x03, 0x0005, 0x000c },
  { 0x00, 0x02, -1, 0x03, 0x0005, 0x000e },
  { 0x00, 0x02, -1, 0x03, 0x0005, 0x0012 },
  { 0x00, 0x03, -1, 0x03, 0x0005, 0x0016 },
  { 0x00, 0x03, -1, 0x03, 0x0005, 0x001e },
  { 0x00, 0x04, -1, 0x03, 0x0005, 0x0026 },
  { 0x00, 0x04, -1, 0x03, 0x0005, 0x0036 },
  { 0x01, 0x01, -1, 0x03, 0x0006, 0x000a },
  { 0x01, 0x01, -1, 0x03, 0x0006, 0x000c },
  { 0x01, 0x02, -1, 0x03, 0x0006, 0x000e },
  { 0x01, 0x02, -1, 0x03, 0x0006, 0x0012 },
  { 0x01, 0x03, -1, 0x03, 0x0006, 0x0016 },
  { 0x01, 0x03, -1, 0x03, 0x0006, 0x001e },
  { 0x01, 0x04, -1, 0x03, 0x0006, 0x0026 },
  { 0x01, 0x04, -1, 0x03, 0x0006, 0x0036 },
  { 0x01, 0x01, -1, 0x03, 0x0008, 0x000a },
  { 0x01, 0x01, -1, 0x03, 0x0008, 0x000c },
  { 0x01, 0x02, -1, 0x03, 0x0008, 0x000e },
  { 0x01, 0x02, -1, 0x03, 0x0008, 0x0012 },
  { 0x01, 0x03, -1, 0x03, 0x0008, 0x0016 },
  { 0x01, 0x03, -1, 0x03, 0x0008, 0x001e },
  { 0x01, 0x04, -1, 0x03, 0x0008, 0x0026 },
  { 0x01, 0x04, -1, 0x03, 0x0008, 0x0036 },
  { 0x02, 0x00, -1, 0x00, 0x000a, 0x0002 },
  { 0x02, 0x00, -1, 0x01, 0x000a, 0x0003 },
  { 0x02, 0x00, -1, 0x02, 0x000a, 0x0004 },
  { 0x02, 0x00, -1, 0x03, 0x000a, 0x0005 },
  { 0x02, 0x00, -1, 0x03, 0x000a, 0x0006 },
  { 0x02, 0x00, -1, 0x03, 0x000a, 0x0007 },
  { 0x02, 0x00, -1, 0x03, 0x000a, 0x0008 },
  { 0x02, 0x00, -1, 0x03, 0x000a, 0x0009 },
  { 0x02, 0x00, -1, 0x00, 0x000e, 0x0002 },
  { 0x02, 0x00, -1, 0x01, 0x000e, 0x0003 },
  { 0x02, 0x00, -1, 0x02, 0x000e, 0x0004 },
  { 0x02, 0x00, -1, 0x03, 0x000e, 0x0005 },
  { 0x02, 0x00, -1, 0x03, 0x000e, 0x0006 },
  { 0x02, 0x00, -1, 0x03, 0x000e, 0x0007 },
  { 0x02, 0x00, -1, 0x03, 0x000e, 0x0008 },
  { 0x02, 0x00, -1, 0x03, 0x000e, 0x0009 },
  { 0x03, 0x00, -1, 0x00, 0x0012, 0x0002 },
  { 0x03, 0x00, -1, 0x01, 0x0012, 0x0003 },
  { 0x03, 0x00, -1, 0x02, 0x0012, 0x0004 },
  { 0x03, 0x00, -1, 0x03, 0x0012, 0x0005 },
  { 0x03, 0x00, -1, 0x03, 0x0012, 0x0006 },
  { 0x03, 0x00, -1, 0x03, 0x0012, 0x0007 },
  { 0x03, 0x00, -1, 0x03, 0x0012, 0x0008 },
  { 0x03, 0x00, -1, 0x03, 0x0012, 0x0009 },
  { 0x03, 0x00, -1, 0x00, 0x001a, 0x0002 },
  { 0x03, 0x00, -1, 0x01, 0x001a, 0x0003 },
  { 0x03, 0x00, -1, 0x02, 0x001a, 0x0004 },
  { 0x03, 0x00, -1, 0x03, 0x001a, 0x0005 },
  { 0x03, 0x00, -1, 0x03, 0x001a, 0x0006 },
  { 0x03, 0x00, -1, 0x03, 0x001a, 0x0007 },
  { 0x03, 0x00, -1, 0x03, 0x001a, 0x0008 },
  { 0x03, 0x00, -1, 0x03, 0x001a, 0x0009 },
  { 0x04, 0x00, -1, 0x00, 0x0022, 0x0002 },
  { 0x04, 0x00, -1, 0x01, 0x0022, 0x0003 },
  { 0x04, 0x00, -1, 0x02, 0x0022, 0x0004 },
  { 0x04, 0x00, -1, 0x03, 0x0022, 0x0005 },
  { 0x04, 0x00, -1, 0x03, 0x0022, 0x0006 },
  { 0x04, 0x00, -1, 0x03, 0x0022, 0x0007 },
  { 0x04, 0x00, -1, 0x03, 0x0022, 0x0008 },
  { 0x04, 0x00, -1, 0x03, 0x0022, 0x0009 },
  { 0x04, 0x00, -1, 0x00, 0x0032, 0x0002 },
  { 0x04, 0x00, -1, 0x01, 0x0032, 0x0003 },
  { 0x04, 0x00, -1, 0x02, 0x0032, 0x0004 },
  { 0x04, 0x00, -1, 0x03, 0x0032, 0x0005 },
  { 0x04, 0x00, -1, 0x03, 0x0032, 0x0006 },
  { 0x04, 0x00, -1, 0x03, 0x0032, 0x0007 },
  { 0x04, 0x00, -1, 0x03, 0x0032, 0x0008 },
  { 0x04, 0x00, -1, 0x03, 0x0032, 0x0009 },
  { 0x05, 0x00, -1, 0x00, 0x0042, 0x0002 },
  { 0x05, 0x00, -1, 0x01, 0x0042, 0x0003 },
  { 0x05, 0x00, -1, 0x02, 0x0042, 0x0004 },
  { 0x05, 0x00, -1, 0x03, 0x0042, 0x0005 },
  { 0x05, 0x00, -1, 0x03, 0x0042, 0x0006 },
  { 0x05, 0x00, -1, 0x03, 0x0042, 0x0007 },
  { 0x05, 0x00, -1, 0x03, 0x0042, 0x0008 },
  { 0x05, 0x00, -1, 0x03, 0x0042, 0x0009 },
  { 0x05, 0x00, -1, 0x00, 0x0062, 0x0002 },
  { 0x05, 0x00, -1, 0x01, 0x0062, 0x0003 },
  { 0x05, 0x00, -1, 0x02, 0x0062, 0x0004 },
  { 0x05, 0x00, -1, 0x03, 0x0062, 0x0005 },
  { 0x05, 0x00, -1, 0x03, 0x0062, 0x0006 },
  { 0x05, 0x00, -1, 0x03, 0x0062, 0x0007 },
  { 0x05, 0x00, -1, 0x03, 0x0062, 0x0008 },
  { 0x05, 0x00, -1, 0x03, 0x0062, 0x0009 },
  { 0x02, 0x01, -1, 0x03, 0x000a, 0x000a },
  { 0x02, 0x01, -1, 0x03, 0x000a, 0x000c },
  { 0x02, 0x02, -1, 0x03, 0x000a, 0x000e },
  { 0x02, 0x02, -1, 0x03, 0x000a, 0x0012 },
  { 0x02, 0x03, -1, 0x03, 0x000a, 0x0016 },
  { 0x02, 0x03, -1, 0x03, 0x000a, 0x001e },
  { 0x02, 0x04, -1, 0x03, 0x000a, 0x0026 },
  { 0x02, 0x04, -1, 0x03, 0x000a, 0x0036 },
  { 0x02, 0x01, -1, 0x03, 0x000e, 0x000a },
  { 0x02, 0x01, -1, 0x03, 0x000e, 0x000c },
  { 0x02, 0x02, -1, 0x03, 0x000e, 0x000e },
  { 0x02, 0x02, -1, 0x03, 0x000e, 0x0012 },
  { 0x02, 0x03, -1, 0x03, 0x000e, 0x0016 },
  { 0x02, 0x03, -1, 0x03, 0x000e, 0x001e },
  { 0x02, 0x04, -1, 0x03, 0x000e, 0x0026 },
  { 0x02, 0x04, -1, 0x03, 0x000e, 0x0036 },
  { 0x03, 0x01, -1, 0x03, 0x0012, 0x000a },
  { 0x03, 0x01, -1, 0x03, 0x0012, 0x000c },
  { 0x03, 0x02, -1, 0x03, 0x0012, 0x000e },
  { 0x03, 0x02, -1, 0x03, 0x0012, 0x0012 },
  { 0x03, 0x03, -1, 0x03, 0x0012, 0x0016 },
  { 0x03, 0x03, -1, 0x03, 0x0012, 0x001e },
  { 0x03, 0x04, -1, 0x03, 0x0012, 0x0026 },
  { 0x03, 0x04, -1, 0x03, 0x0012, 0x0036 },
  { 0x03, 0x01, -1, 0x03, 0x001a, 0x000a },
  { 0x03, 0x01, -1, 0x03, 0x001a, 0x000c },
  { 0x03, 0x02, -1, 0x03, 0x001a, 0x000e },
  { 0x03, 0x02, -1, 0x03, 0x001a, 0x0012 },
  { 0x03, 0x03, -1, 0x03, 0x001a, 0x0016 },
  { 0x03, 0x03, -1, 0x03, 0x001a, 0x001e },
  { 0x03, 0x04, -1, 0x03, 0x001a, 0x0026 },
  { 0x03, 0x04, -1, 0x03, 0x001a, 0x0036 },
  { 0x04, 0x01, -1, 0x03, 0x0022, 0x000a },
  { 0x04, 0x01, -1, 0x03, 0x0022, 0x000c },
  { 0x04, 0x02, -1, 0x03, 0x0022, 0x000e },
  { 0x04, 0x02, -1, 0x03, 0x0022, 0x0012 },
  { 0x04, 0x03, -1, 0x03, 0x0022, 0x0016 },
  { 0x04, 0x03, -1, 0x03, 0x0022, 0x001e },
  { 0x04, 0x04, -1, 0x03, 0x0022, 0x0026 },
  { 0x04, 0x04, -1, 0x03, 0x0022, 0x0036 },
  { 0x04, 0x01, -1, 0x03, 0x0032, 0x000a },
  { 0x04, 0x01, -1, 0x03, 0x0032, 0x000c },
  { 0x04, 0x02, -1, 0x03, 0x0032, 0x000e },
  { 0x04, 0x02, -1, 0x03, 0x0032, 0x0012 },
  { 0x04, 0x03, -1, 0x03, 0x0032, 0x0016 },
  { 0x04, 0x03, -1, 0x03, 0x0032, 0x001e },
  { 0x04, 0x04, -1, 0x03, 0x0032, 0x0026 },
  { 0x04, 0x04, -1, 0x03, 0x0032, 0x0036 },
  { 0x05, 0x01, -1, 0x03, 0x0042, 0x000a },
  { 0x05, 0x01, -1, 0x03, 0x0042, 0x000c },
  { 0x05, 0x02, -1, 0x03, 0x0042, 0x000e },
  { 0x05, 0x02, -1, 0x03, 0x0042, 0x0012 },
  { 0x05, 0x03, -1, 0x03, 0x0042, 0x0016 },
  { 0x05, 0x03, -1, 0x03, 0x0042, 0x001e },
  { 0x05, 0x04, -1, 0x03, 0x0042, 0x0026 },
  { 0x05, 0x04, -1, 0x03, 0x0042, 0x0036 },
  { 0x05, 0x01, -1, 0x03, 0x0062, 0x000a },
  { 0x05, 0x01, -1, 0x03, 0x0062, 0x000c },
  { 0x05, 0x02, -1, 0x03, 0x0062, 0x000e },
  { 0x05, 0x02, -1, 0x03, 0x0062, 0x0012 },
  { 0x05, 0x03, -1, 0x03, 0x0062, 0x0016 },
  { 0x05, 0x03, -1, 0x03, 0x0062, 0x001e },
  { 0x05, 0x04, -1, 0x03, 0x0062, 0x0026 },
  { 0x05, 0x04, -1, 0x03, 0x0062, 0x0036 },
  { 0x00, 0x05, -1, 0x03, 0x0000, 0x0046 },
  { 0x00, 0x05, -1, 0x03, 0x0000, 0x0066 },
  { 0x00, 0x06, -1, 0x03, 0x0000, 0x0086 },
  { 0x00, 0x07, -1, 0x03, 0x0000, 0x00c6 },
  { 0x00, 0x08, -1, 0x03, 0x0000, 0x0146 },
  { 0x00, 0x09, -1, 0x03, 0x0000, 0x0246 },
  { 0x00, 0x0a, -1, 0x03, 0x0000, 0x0446 },
  { 0x00, 0x18, -1, 0x03, 0x0000, 0x0846 },
  { 0x00, 0x05, -1, 0x03, 0x0001, 0x0046 },
  { 0x00, 0x05, -1, 0x03, 0x0001, 0x0066 },
  { 0x00, 0x06, -1, 0x03, 0x0001, 0x0086 },
  { 0x00, 0x07, -1, 0x03, 0x0001, 0x00c6 },
  { 0x00, 0x08, -1, 0x03, 0x0001, 0x0146 },
  { 0x00, 0x09, -1, 0x03, 0x0001, 0x0246 },
  { 0x00, 0x0a, -1, 0x03, 0x0001, 0x0446 },
  { 0x00, 0x18, -1, 0x03, 0x0001, 0x0846 },
  { 0x00, 0x05, -1, 0x03, 0x0002, 0x0046 },
  { 0x00, 0x05, -1, 0x03, 0x0002, 0x0066 },
  { 0x00, 0x06, -1, 0x03, 0x0002, 0x0086 },
  { 0x00, 0x07, -1, 0x03, 0x0002, 0x00c6 },
  { 0x00, 0x08, -1, 0x03, 0x0002, 0x0146 },
  { 0x00, 0x09, -1, 0x03, 0x0002, 0x0246 },
  { 0x00, 0x0a, -1, 0x03, 0x0002, 0x0446 },
  { 0x00, 0x18, -1, 0x03, 0x0002, 0x0846 },
  { 0x00, 0x05, -1, 0x03, 0x0003, 0x0046 },
  { 0x00, 0x05, -1, 0x03, 0x0003, 0x0066 },
  { 0x00, 0x06, -1, 0x03, 0x0003, 0x0086 },
  { 0x00, 0x07, -1, 0x03, 0x0003, 0x00c6 },
  { 0x00, 0x08, -1, 0x03, 0x0003, 0x0146 },
  { 0x00, 0x09, -1, 0x03, 0x0003, 0x0246 },
  { 0x00, 0x0a, -1, 0x03, 0x0003, 0x0446 },
  { 0x00, 0x18, -1, 0x03, 0x0003, 0x0846 },
  { 0x00, 0x05, -1, 0x03, 0x0004, 0x0046 },
  { 0x00, 0x05, -1, 0x03, 0x0004, 0x0066 },
  { 0x00, 0x06, -1, 0x03, 0x0004, 0x0086 },
  { 0x00, 0x07, -1, 0x03, 0x0004, 0x00c6 },
  { 0x00, 0x08, -1, 0x03, 0x0004, 0x0146 },
  { 0x00, 0x09, -1, 0x03, 0x0004, 0x0246 },
  { 0x00, 0x0a, -1, 0x03, 0x0004, 0x0446 },
  { 0x00, 0x18, -1, 0x03, 0x0004, 0x0846 },
  { 0x00, 0x05, -1, 0x03, 0x0005, 0x0046 },
  { 0x00, 0x05, -1, 0x03, 0x0005, 0x0066 },
  { 0x00, 0x06, -1, 0x03, 0x0005, 0x0086 },
  { 0x00, 0x07, -1, 0x03, 0x0005, 0x00c6 },
  { 0x00, 0x08, -1, 0x03, 0x0005, 0x0146 },
  { 0x00, 0x09, -1, 0x03, 0x0005, 0x0246 },
  { 0x00, 0x0a, -1, 0x03, 0x0005, 0x0446 },
  { 0x00, 0x18, -1, 0x03, 0x0005, 0x0846 },
  { 0x01, 0x05, -1, 0x03, 0x0006, 0x0046 },
  { 0x01, 0x05, -1, 0x03, 0x0006, 0x0066 },
  { 0x01, 0x06, -1, 0x03, 0x0006, 0x0086 },
  { 0x01, 0x07, -1, 0x03, 0x0006, 0x00c6 },
  { 0x01, 0x08, -1, 0x03, 0x0006, 0x0146 },
  { 0x01, 0x09, -1, 0x03, 0x0006, 0x0246 },
  { 0x01, 0x0a, -1, 0x03, 0x0006, 0x0446 },
  { 0x01, 0x18, -1, 0x03, 0x0006, 0x0846 },
  { 0x01, 0x05, -1, 0x03, 0x0008, 0x0046 },
  { 0x01, 0x05, -1, 0x03, 0x0008, 0x0066 },
  { 0x01, 0x06, -1, 0x03, 0x0008, 0x0086 },
  { 0x01, 0x07, -1, 0x03, 0x0008, 0x00c6 },
  { 0x01, 0x08, -1, 0x03, 0x0008, 0x0146 },
  { 0x01, 0x09, -1, 0x03, 0x0008, 0x0246 },
  { 0x01, 0x0a, -1, 0x03, 0x0008, 0x0446 },
  { 0x01, 0x18, -1, 0x03, 0x0008, 0x0846 },
  { 0x06, 0x00, -1, 0x00, 0x0082, 0x0002 },
  { 0x06, 0x00, -1, 0x01, 0x0082, 0x0003 },
  { 0x06, 0x00, -1, 0x02, 0x0082, 0x0004 },
  { 0x06, 0x00, -1, 0x03, 0x0082, 0x0005 },
  { 0x06, 0x00, -1, 0x03, 0x0082, 0x0006 },
  { 0x06, 0x00, -1, 0x03, 0x0082, 0x0007 },
  { 0x06, 0x00, -1, 0x03, 0x0082, 0x0008 },
  { 0x06, 0x00, -1, 0x03, 0x0082, 0x0009 },
  { 0x07, 0x00, -1, 0x00, 0x00c2, 0x0002 },
  { 0x07, 0x00, -1, 0x01, 0x00c2, 0x0003 },
  { 0x07, 0x00, -1, 0x02, 0x00c2, 0x0004 },
  { 0x07, 0x00, -1, 0x03, 0x00c2, 0x0005 },
  { 0x07, 0x00, -1, 0x03, 0x00c2, 0x0006 },
  { 0x07, 0x00, -1, 0x03, 0x00c2, 0x0007 },
  { 0x07, 0x00, -1, 0x03, 0x00c2, 0x0008 },
  { 0x07, 0x00, -1, 0x03, 0x00c2, 0x0009 },
  { 0x08, 0x00, -1, 0x00, 0x0142, 0x0002 },
  { 0x08, 0x00, -1, 0x01, 0x0142, 0x0003 },
  { 0x08, 0x00, -1, 0x02, 0x0142, 0x0004 },
  { 0x08, 0x00, -1, 0x03, 0x0142, 0x0005 },
  { 0x08, 0x00, -1, 0x03, 0x0142, 0x0006 },
  { 0x08, 0x00, -1, 0x03, 0x0142, 0x0007 },
  { 0x08, 0x00, -1, 0x03, 0x0142, 0x0008 },
  { 0x08, 0x00, -1, 0x03, 0x0142, 0x0009 },
  { 0x09, 0x00, -1, 0x00, 0x0242, 0x0002 },
  { 0x09, 0x00, -1, 0x01, 0x0242, 0x0003 },
  { 0x09, 0x00, -1, 0x02, 0x0242, 0x0004 },
  { 0x09, 0x00, -1, 0x03, 0x0242, 0x0005 },
  { 0x09, 0x00, -1, 0x03, 0x0242, 0x0006 },
  { 0x09, 0x00, -1, 0x03, 0x0242, 0x0007 },
  { 0x09, 0x00, -1, 0x03, 0x0242, 0x0008 },
  { 0x09, 0x00, -1, 0x03, 0x0242, 0x0009 },
  { 0x0a, 0x00, -1, 0x00, 0x0442, 0x0002 },
  { 0x0a, 0x00, -1, 0x01, 0x0442, 0x0003 },
  { 0x0a, 0x00, -1, 0x02, 0x0442, 0x0004 },
  { 0x0a, 0x00, -1, 0x03, 0x0442, 0x0005 },
  { 0x0a, 0x00, -1, 0x03, 0x0442, 0x0006 },
  { 0x0a, 0x00, -1, 0x03, 0x0442, 0x0007 },
  { 0x0a, 0x00, -1, 0x03, 0x0442, 0x0008 },
  { 0x0a, 0x00, -1, 0x03, 0x0442, 0x0009 },
  { 0x0c, 0x00, -1, 0x00, 0x0842, 0x0002 },
  { 0x0c, 0x00, -1, 0x01, 0x0842, 0x0003 },
  { 0x0c, 0x00, -1, 0x02, 0x0842, 0x0004 },
  { 0x0c, 0x00, -1, 0x03, 0x0842, 0x0005 },
  { 0x0c, 0x00, -1, 0x03, 0x0842, 0x0006 },
  { 0x0c, 0x00, -1, 0x03, 0x0842, 0x0007 },
  { 0x0c, 0x00, -1, 0x03, 0x0842, 0x0008 },
  { 0x0c, 0x00, -1, 0x03, 0x0842, 0x0009 },
  { 0x0e, 0x00, -1, 0x00, 0x1842, 0x0002 },
  { 0x0e, 0x00, -1, 0x01, 0x1842, 0x0003 },
  { 0x0e, 0x00, -1, 0x02, 0x1842, 0x0004 },
  { 0x0e, 0x00, -1, 0x03, 0x1842, 0x0005 },
  { 0x0e, 0x00, -1, 0x03, 0x1842, 0x0006 },
  { 0x0e, 0x00, -1, 0x03, 0x1842, 0x0007 },
  { 0x0e, 0x00, -1, 0x03, 0x1842, 0x0008 },
  { 0x0e, 0x00, -1, 0x03, 0x1842, 0x0009 },
  { 0x18, 0x00, -1, 0x00, 0x5842, 0x0002 },
  { 0x18, 0x00, -1, 0x01, 0x5842, 0x0003 },
  { 0x18, 0x00, -1, 0x02, 0x5842, 0x0004 },
  { 0x18, 0x00, -1, 0x03, 0x5842, 0x0005 },
  { 0x18, 0x00, -1, 0x03, 0x5842, 0x0006 },
  { 0x18, 0x00, -1, 0x03, 0x5842, 0x0007 },
  { 0x18, 0x00, -1, 0x03, 0x5842, 0x0008 },
  { 0x18, 0x00, -1, 0x03, 0x5842, 0x0009 },
  { 0x02, 0x05, -1, 0x03, 0x000a, 0x0046 },
  { 0x02, 0x05, -1, 0x03, 0x000a, 0x0066 },
  { 0x02, 0x06, -1, 0x03, 0x000a, 0x0086 },
  { 0x02, 0x07, -1, 0x03, 0x000a, 0x00c6 },
  { 0x02, 0x08, -1, 0x03, 0x000a, 0x0146 },
  { 0x02, 0x09, -1, 0x03, 0x000a, 0x0246 },
  { 0x02, 0x0a, -1, 0x03, 0x000a, 0x0446 },
  { 0x02, 0x18, -1, 0x03, 0x000a, 0x0846 },
  { 0x02, 0x05, -1, 0x03, 0x000e, 0x0046 },
  { 0x02, 0x05, -1, 0x03, 0x000e, 0x0066 },
  { 0x02, 0x06, -1, 0x03, 0x000e, 0x0086 },
  { 0x02, 0x07, -1, 0x03, 0x000e, 0x00c6 },
  { 0x02, 0x08, -1, 0x03, 0x000e, 0x0146 },
  { 0x02, 0x09, -1, 0x03, 0x000e, 0x0246 },
  { 0x02, 0x0a, -1, 0x03, 0x000e, 0x0446 },
  { 0x02, 0x18, -1, 0x03, 0x000e, 0x0846 },
  { 0x03, 0x05, -1, 0x03, 0x0012, 0x0046 },
  { 0x03, 0x05, -1, 0x03, 0x0012, 0x0066 },
  { 0x03, 0x06, -1, 0x03, 0x0012, 0x0086 },
  { 0x03, 0x07, -1, 0x03, 0x0012, 0x00c6 },
  { 0x03, 0x08, -1, 0x03, 0x0012, 0x0146 },
  { 0x03, 0x09, -1, 0x03, 0x0012, 0x0246 },
  { 0x03, 0x0a, -1, 0x03, 0x0012, 0x0446 },
  { 0x03, 0x18, -1, 0x03, 0x0012, 0x0846 },
  { 0x03, 0x05, -1, 0x03, 0x001a, 0x0046 },
  { 0x03, 0x05, -1, 0x03, 0x001a, 0x0066 },
  { 0x03, 0x06, -1, 0x03, 0x001a, 0x0086 },
  { 0x03, 0x07, -1, 0x03, 0x001a, 0x00c6 },
  { 0x03, 0x08, -1, 0x03, 0x001a, 0x0146 },
  { 0x03, 0x09, -1, 0x03, 0x001a, 0x0246 },
  { 0x03, 0x0a, -1, 0x03, 0x001a, 0x0446 },
  { 0x03, 0x18, -1, 0x03, 0x001a, 0x0846 },
  { 0x04, 0x05, -1, 0x03, 0x0022, 0x0046 },
  { 0x04, 0x05, -1, 0x03, 0x0022, 0x0066 },
  { 0x04, 0x06, -1, 0x03, 0x0022, 0x0086 },
  { 0x04, 0x07, -1, 0x03, 0x0022, 0x00c6 },
  { 0x04, 0x08, -1, 0x03, 0x0022, 0x0146 },
  { 0x04, 0x09, -1, 0x03, 0x0022, 0x0246 },
  { 0x04, 0x0a, -1, 0x03, 0x0022, 0x0446 },
  { 0x04, 0x18, -1, 0x03, 0x0022, 0x0846 },
  { 0x04, 0x05, -1, 0x03, 0x0032, 0x0046 },
  { 0x04, 0x05, -1, 0x03, 0x0032, 0x0066 },
  { 0x04, 0x06, -1, 0x03, 0x0032, 0x0086 },
  { 0x04, 0x07, -1, 0x03, 0x0032, 0x00c6 },
  { 0x04, 0x08, -1, 0x03, 0x0032, 0x0146 },
  { 0x04, 0x09, -1, 0x03, 0x0032, 0x0246 },
  { 0x04, 0x0a, -1, 0x03, 0x0032, 0x0446 },
  { 0x04, 0x18, -1, 0x03, 0x0032, 0x0846 },
  { 0x05, 0x05, -1, 0x03, 0x0042, 0x0046 },
  { 0x05, 0x05, -1, 0x03, 0x0042, 0x0066 },
  { 0x05, 0x06, -1, 0x03, 0x0042, 0x0086 },
  { 0x05, 0x07, -1, 0x03, 0x0042, 0x00c6 },
  { 0x05, 0x08, -1, 0x03, 0x0042, 0x0146 },
  { 0x05, 0x09, -1, 0x03, 0x0042, 0x0246 },
  { 0x05, 0x0a, -1, 0x03, 0x0042, 0x0446 },
  { 0x05, 0x18, -1, 0x03, 0x0042, 0x0846 },
  { 0x05, 0x05, -1, 0x03, 0x0062, 0x0046 },
  { 0x05, 0x05, -1, 0x03, 0x0062, 0x0066 },
  { 0x05, 0x06, -1, 0x03, 0x0062, 0x0086 },
  { 0x05, 0x07, -1, 0x03, 0x0062, 0x00c6 },
  { 0x05, 0x08, -1, 0x03, 0x0062, 0x0146 },
  { 0x05, 0x09, -1, 0x03, 0x0062, 0x0246 },
  { 0x05, 0x0a, -1, 0x03, 0x0062, 0x0446 },
  { 0x05, 0x18, -1, 0x03, 0x0062, 0x0846 },
  { 0x06, 0x01, -1, 0x03, 0x0082, 0x000a },
  { 0x06, 0x01, -1, 0x03, 0x0082, 0x000c },
  { 0x06, 0x02, -1, 0x03, 0x0082, 0x000e },
  { 0x06, 0x02, -1, 0x03, 0x0082, 0x0012 },
  { 0x06, 0x03, -1, 0x03, 0x0082, 0x0016 },
  { 0x06, 0x03, -1, 0x03, 0x0082, 0x001e },
  { 0x06, 0x04, -1, 0x03, 0x0082, 0x0026 },
  { 0x06, 0x04, -1, 0x03, 0x0082, 0x0036 },
  { 0x07, 0x01, -1, 0x03, 0x00c2, 0x000a },
  { 0x07, 0x01, -1, 0x03, 0x00c2, 0x000c },
  { 0x07, 0x02, -1, 0x03, 0x00c2, 0x000e },
  { 0x07, 0x02, -1, 0x03, 0x00c2, 0x0012 },
  { 0x07, 0x03, -1, 0x03, 0x00c2, 0x0016 },
  { 0x07, 0x03, -1, 0x03, 0x00c2, 0x001e },
  { 0x07, 0x04, -1, 0x03, 0x00c2, 0x0026 },
  { 0x07, 0x04, -1, 0x03, 0x00c2, 0x0036 },
  { 0x08, 0x01, -1, 0x03, 0x0142, 0x000a },
  { 0x08, 0x01, -1, 0x03, 0x0142, 0x000c },
  { 0x08, 0x02, -1, 0x03, 0x0142, 0x000e },
  { 0x08, 0x02, -1, 0x03, 0x0142, 0x0012 },
  { 0x08, 0x03, -1, 0x03, 0x0142, 0x0016 },
  { 0x08, 0x03, -1, 0x03, 0x0142, 0x001e },
  { 0x08, 0x04, -1, 0x03, 0x0142, 0x0026 },
  { 0x08, 0x04, -1, 0x03, 0x0142, 0x0036 },
  { 0x09, 0x01, -1, 0x03, 0x0242, 0x000a },
  { 0x09, 0x01, -1, 0x03, 0x0242, 0x000c },
  { 0x09, 0x02, -1, 0x03, 0x0242, 0x000e },
  { 0x09, 0x02, -1, 0x03, 0x0242, 0x0012 },
  { 0x09, 0x03, -1, 0x03, 0x0242, 0x0016 },
  { 0x09, 0x03, -1, 0x03, 0x0242, 0x001e },
  { 0x09, 0x04, -1, 0x03, 0x0242, 0x0026 },
  { 0x09, 0x04, -1, 0x03, 0x0242, 0x0036 },
  { 0x0a, 0x01, -1, 0x03, 0x0442, 0x000a },
  { 0x0a, 0x01, -1, 0x03, 0x0442, 0x000c },
  { 0x0a, 0x02, -1, 0x03, 0x0442, 0x000e },
  { 0x0a, 0x02, -1, 0x03, 0x0442, 0x0012 },
  { 0x0a, 0x03, -1, 0x03, 0x0442, 0x0016 },
  { 0x0a, 0x03, -1, 0x03, 0x0442, 0x001e },
  { 0x0a, 0x04, -1, 0x03, 0x0442, 0x0026 },
  { 0x0a, 0x04, -1, 0x03, 0x0442, 0x0036 },
  { 0x0c, 0x01, -1, 0x03, 0x0842, 0x000a },
  { 0x0c, 0x01, -1, 0x03, 0x0842, 0x000c },
  { 0x0c, 0x02, -1, 0x03, 0x0842, 0x000e },
  { 0x0c, 0x02, -1, 0x03, 0x0842, 0x0012 },
  { 0x0c, 0x03, -1, 0x03, 0x0842, 0x0016 },
  { 0x0c, 0x03, -1, 0x03, 0x0842, 0x001e },
  { 0x0c, 0x04, -1, 0x03, 0x0842, 0x0026 },
  { 0x0c, 0x04, -1, 0x03, 0x0842, 0x0036 },
  { 0x0e, 0x01, -1, 0x03, 0x1842, 0x000a },
  { 0x0e, 0x01, -1, 0x03, 0x1842, 0x000c },
  { 0x0e, 0x02, -1, 0x03, 0x1842, 0x000e },
  { 0x0e, 0x02, -1, 0x03, 0x1842, 0x0012 },
  { 0x0e, 0x03, -1, 0x03, 0x1842, 0x0016 },
  { 0x0e, 0x03, -1, 0x03, 0x1842, 0x001e },
  { 0x0e, 0x04, -1, 0x03, 0x1842, 0x0026 },
  { 0x0e, 0x04, -1, 0x03, 0x1842, 0x0036 },
  { 0x18, 0x01, -1, 0x03, 0x5842, 0x000a },
  { 0x18, 0x01, -1, 0x03, 0x5842, 0x000c },
  { 0x18, 0x02, -1, 0x03, 0x5842, 0x000e },
  { 0x18, 0x02, -1, 0x03, 0x5842, 0x0012 },
  { 0x18, 0x03, -1, 0x03, 0x5842, 0x0016 },
  { 0x18, 0x03, -1, 0x03, 0x5842, 0x001e },
  { 0x18, 0x04, -1, 0x03, 0x5842, 0x0026 },
  { 0x18, 0x04, -1, 0x03, 0x5842, 0x0036 },
  { 0x06, 0x05, -1, 0x03, 0x0082, 0x0046 },
  { 0x06, 0x05, -1, 0x03, 0x0082, 0x0066 },
  { 0x06, 0x06, -1, 0x03, 0x0082, 0x0086 },
  { 0x06, 0x07, -1, 0x03, 0x0082, 0x00c6 },
  { 0x06, 0x08, -1, 0x03, 0x0082, 0x0146 },
  { 0x06, 0x09, -1, 0x03, 0x0082, 0x0246 },
  { 0x06, 0x0a, -1, 0x03, 0x0082, 0x0446 },
  { 0x06, 0x18, -1, 0x03, 0x0082, 0x0846 },
  { 0x07, 0x05, -1, 0x03, 0x00c2, 0x0046 },
  { 0x07, 0x05, -1, 0x03, 0x00c2, 0x0066 },
  { 0x07, 0x06, -1, 0x03, 0x00c2, 0x0086 },
  { 0x07, 0x07, -1, 0x03, 0x00c2, 0x00c6 },
  { 0x07, 0x08, -1, 0x03, 0x00c2, 0x0146 },
  { 0x07, 0x09, -1, 0x03, 0x00c2, 0x0246 },
  { 0x07, 0x0a, -1, 0x03, 0x00c2, 0x0446 },
  { 0x07, 0x18, -1, 0x03, 0x00c2, 0x0846 },
  { 0x08, 0x05, -1, 0x03, 0x0142, 0x0046 },
  { 0x08, 0x05, -1, 0x03, 0x0142, 0x0066 },
  { 0x08, 0x06, -1, 0x03, 0x0142, 0x0086 },
  { 0x08, 0x07, -1, 0x03, 0x0142, 0x00c6 },
  { 0x08, 0x08, -1, 0x03, 0x0142, 0x0146 },
  { 0x08, 0x09, -1, 0x03, 0x0142, 0x0246 },
  { 0x08, 0x0a, -1, 0x03, 0x0142, 0x0446 },
  { 0x08, 0x18, -1, 0x03, 0x0142, 0x0846 },
  { 0x09, 0x05, -1, 0x03, 0x0242, 0x0046 },
  { 0x09, 0x05, -1, 0x03, 0x0242, 0x0066 },
  { 0x09, 0x06, -1, 0x03, 0x0242, 0x0086 },
  { 0x09, 0x07, -1, 0x03, 0x0242, 0x00c6 },
  { 0x09, 0x08, -1, 0x03, 0x0242, 0x0146 },
  { 0x09, 0x09, -1, 0x03, 0x0242, 0x0246 },
  { 0x09, 0x0a, -1, 0x03, 0x0242, 0x0446 },
  { 0x09, 0x18, -1, 0x03, 0x0242, 0x0846 },
  { 0x0a, 0x05, -1, 0x03, 0x0442, 0x0046 },
  { 0x0a, 0x05, -1, 0x03, 0x0442, 0x0066 },
  { 0x0a, 0x06, -1, 0x03, 0x0442, 0x0086 },
  { 0x0a, 0x07, -1, 0x03, 0x0442, 0x00c6 },
  { 0x0a, 0x08, -1, 0x03, 0x0442, 0x0146 },
  { 0x0a, 0x09, -1, 0x03, 0x0442, 0x0246 },
  { 0x0a, 0x0a, -1, 0x03, 0x0442, 0x0446 },
  { 0x0a, 0x18, -1, 0x03, 0x0442, 0x0846 },
  { 0x0c, 0x05, -1, 0x03, 0x0842, 0x0046 },
  { 0x0c, 0x05, -1, 0x03, 0x0842, 0x0066 },
  { 0x0c, 0x06, -1, 0x03, 0x0842, 0x0086 },
  { 0x0c, 0x07, -1, 0x03, 0x0842, 0x00c6 },
  { 0x0c, 0x08, -1, 0x03, 0x0842, 0x0146 },
  { 0x0c, 0x09, -1, 0x03, 0x0842, 0x0246 },
  { 0x0c, 0x0a, -1, 0x03, 0x0842, 0x0446 },
  { 0x0c, 0x18, -1, 0x03, 0x0842, 0x0846 },
  { 0x0e, 0x05, -1, 0x03, 0x1842, 0x0046 },
  { 0x0e, 0x05, -1, 0x03, 0x1842, 0x0066 },
  { 0x0e, 0x06, -1, 0x03, 0x1842, 0x0086 },
  { 0x0e, 0x07, -1, 0x03, 0x1842, 0x00c6 },
  { 0x0e, 0x08, -1, 0x03, 0x1842, 0x0146 },
  { 0x0e, 0x09, -1, 0x03, 0x1842, 0x0246 },
  { 0x0e, 0x0a, -1, 0x03, 0x1842, 0x0446 },
  { 0x0e, 0x18, -1, 0x03, 0x1842, 0x0846 },
  { 0x18, 0x05, -1, 0x03, 0x5842, 0x0046 },
  { 0x18, 0x05, -1, 0x03, 0x5842, 0x0066 },
  { 0x18, 0x06, -1, 0x03, 0x5842, 0x0086 },
  { 0x18, 0x07, -1, 0x03, 0x5842, 0x00c6 },
  { 0x18, 0x08, -1, 0x03, 0x5842, 0x0146 },
  { 0x18, 0x09, -1, 0x03, 0x5842, 0x0246 },
  { 0x18, 0x0a, -1, 0x03, 0x5842, 0x0446 },
  { 0x18, 0x18, -1, 0x03, 0x5842, 0x0846 },
};
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./state.h" 1
# 13 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./state.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/dictionary.h" 1
# 14 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./state.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/transform.h" 1
# 16 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./state.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/././bit_reader.h" 1
# 18 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./state.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/././huffman.h" 1
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
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c" 2
# 46 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c"
static const uint32_t kRingBufferWriteAheadSlack = 42;

static const uint8_t kCodeLengthCodeOrder[(17 + 1)] = {
  1, 2, 3, 4, 0, 5, 17, 6, 16, 7, 8, 9, 10, 11, 12, 13, 14, 15,
};


static const uint8_t kCodeLengthPrefixLength[16] = {
  2, 2, 2, 3, 2, 2, 2, 4, 2, 2, 2, 3, 2, 2, 2, 4,
};

static const uint8_t kCodeLengthPrefixValue[16] = {
  0, 4, 3, 2, 0, 4, 3, 1, 0, 4, 3, 2, 0, 4, 3, 5,
};

int BrotliDecoderSetParameter(
    BrotliDecoderStateInternal* state, BrotliDecoderParameter p, uint32_t value) {
  if (state->state != BROTLI_STATE_UNINITED) return 0;
  switch (p) {
    case BROTLI_DECODER_PARAM_DISABLE_RING_BUFFER_REALLOCATION:
      state->canny_ringbuffer_allocation = !!value ? 0 : 1;
      return 1;

    case BROTLI_DECODER_PARAM_LARGE_WINDOW:
      state->large_window = (!!(!!value) ? 1 : 0);
      return 1;

    default: return 0;
  }
}

BrotliDecoderStateInternal* BrotliDecoderCreateInstance(
    brotli_alloc_func alloc_func, brotli_free_func free_func, void* opaque) {
  BrotliDecoderStateInternal* state = 0;
  if (!alloc_func && !free_func) {
    state = (BrotliDecoderStateInternal*)malloc(sizeof(BrotliDecoderStateInternal));
  } else if (alloc_func && free_func) {
    state = (BrotliDecoderStateInternal*)alloc_func(opaque, sizeof(BrotliDecoderStateInternal));
  }
  if (state == 0) {
    (void)(0);
    return 0;
  }
  if (!BrotliDecoderStateInit(state, alloc_func, free_func, opaque)) {
    (void)(0);
    if (!alloc_func && !free_func) {
      free(state);
    } else if (alloc_func && free_func) {
      free_func(opaque, state);
    }
    return 0;
  }
  return state;
}


void BrotliDecoderDestroyInstance(BrotliDecoderStateInternal* state) {
  if (!state) {
    return;
  } else {
    brotli_free_func free_func = state->free_func;
    void* opaque = state->memory_manager_opaque;
    BrotliDecoderStateCleanup(state);
    free_func(opaque, state);
  }
}


static BrotliDecoderResult SaveErrorCode(
    BrotliDecoderStateInternal* s, BrotliDecoderErrorCode e) {
  s->error_code = (int)e;
  switch (e) {
    case BROTLI_DECODER_SUCCESS:
      return BROTLI_DECODER_RESULT_SUCCESS;

    case BROTLI_DECODER_NEEDS_MORE_INPUT:
      return BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT;

    case BROTLI_DECODER_NEEDS_MORE_OUTPUT:
      return BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT;

    default:
      return BROTLI_DECODER_RESULT_ERROR;
  }
}



static BrotliDecoderErrorCode DecodeWindowBits(BrotliDecoderStateInternal* s,
                                               BrotliBitReader* br) {
  uint32_t n;
  int large_window = s->large_window;
  s->large_window = 0;
  BrotliTakeBits(br, 1, &n);
  if (n == 0) {
    s->window_bits = 16;
    return BROTLI_DECODER_SUCCESS;
  }
  BrotliTakeBits(br, 3, &n);
  if (n != 0) {
    s->window_bits = 17 + n;
    return BROTLI_DECODER_SUCCESS;
  }
  BrotliTakeBits(br, 3, &n);
  if (n == 1) {
    if (large_window) {
      BrotliTakeBits(br, 1, &n);
      if (n == 1) {
        return ((void)(0), BROTLI_DECODER_ERROR_FORMAT_WINDOW_BITS);
      }
      s->large_window = 1;
      return BROTLI_DECODER_SUCCESS;
    } else {
      return ((void)(0), BROTLI_DECODER_ERROR_FORMAT_WINDOW_BITS);
    }
  }
  if (n != 0) {
    s->window_bits = 8 + n;
    return BROTLI_DECODER_SUCCESS;
  }
  s->window_bits = 17;
  return BROTLI_DECODER_SUCCESS;
}

static inline void memmove16(uint8_t* dst, uint8_t* src) {



  uint32_t buffer[4];
  memcpy(buffer, src, 16);
  memcpy(dst, buffer, 16);

}


static BrotliDecoderErrorCode DecodeVarLenUint8(
    BrotliDecoderStateInternal* s, BrotliBitReader* br, uint32_t* value) {
  uint32_t bits;
  switch (s->substate_decode_uint8) {
    case BROTLI_STATE_DECODE_UINT8_NONE:
      if ((__builtin_expect(!BrotliSafeReadBits(br, 1, &bits), 0))) {
        return BROTLI_DECODER_NEEDS_MORE_INPUT;
      }
      if (bits == 0) {
        *value = 0;
        return BROTLI_DECODER_SUCCESS;
      }


    case BROTLI_STATE_DECODE_UINT8_SHORT:
      if ((__builtin_expect(!BrotliSafeReadBits(br, 3, &bits), 0))) {
        s->substate_decode_uint8 = BROTLI_STATE_DECODE_UINT8_SHORT;
        return BROTLI_DECODER_NEEDS_MORE_INPUT;
      }
      if (bits == 0) {
        *value = 1;
        s->substate_decode_uint8 = BROTLI_STATE_DECODE_UINT8_NONE;
        return BROTLI_DECODER_SUCCESS;
      }

      *value = bits;


    case BROTLI_STATE_DECODE_UINT8_LONG:
      if ((__builtin_expect(!BrotliSafeReadBits(br, *value, &bits), 0))) {
        s->substate_decode_uint8 = BROTLI_STATE_DECODE_UINT8_LONG;
        return BROTLI_DECODER_NEEDS_MORE_INPUT;
      }
      *value = (1U << *value) + bits;
      s->substate_decode_uint8 = BROTLI_STATE_DECODE_UINT8_NONE;
      return BROTLI_DECODER_SUCCESS;

    default:
      return
          ((void)(0), BROTLI_DECODER_ERROR_UNREACHABLE);
  }
}


static BrotliDecoderErrorCode DecodeMetaBlockLength(
    BrotliDecoderStateInternal* s, BrotliBitReader* br) {
  uint32_t bits;
  int i;
  for (;;) {
    switch (s->substate_metablock_header) {
      case BROTLI_STATE_METABLOCK_HEADER_NONE:
        if (!BrotliSafeReadBits(br, 1, &bits)) {
          return BROTLI_DECODER_NEEDS_MORE_INPUT;
        }
        s->is_last_metablock = bits ? 1 : 0;
        s->meta_block_remaining_len = 0;
        s->is_uncompressed = 0;
        s->is_metadata = 0;
        if (!s->is_last_metablock) {
          s->substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_NIBBLES;
          break;
        }
        s->substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_EMPTY;


      case BROTLI_STATE_METABLOCK_HEADER_EMPTY:
        if (!BrotliSafeReadBits(br, 1, &bits)) {
          return BROTLI_DECODER_NEEDS_MORE_INPUT;
        }
        if (bits) {
          s->substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_NONE;
          return BROTLI_DECODER_SUCCESS;
        }
        s->substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_NIBBLES;


      case BROTLI_STATE_METABLOCK_HEADER_NIBBLES:
        if (!BrotliSafeReadBits(br, 2, &bits)) {
          return BROTLI_DECODER_NEEDS_MORE_INPUT;
        }
        s->size_nibbles = (uint8_t)(bits + 4);
        s->loop_counter = 0;
        if (bits == 3) {
          s->is_metadata = 1;
          s->substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_RESERVED;
          break;
        }
        s->substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_SIZE;


      case BROTLI_STATE_METABLOCK_HEADER_SIZE:
        i = s->loop_counter;
        for (; i < (int)s->size_nibbles; ++i) {
          if (!BrotliSafeReadBits(br, 4, &bits)) {
            s->loop_counter = i;
            return BROTLI_DECODER_NEEDS_MORE_INPUT;
          }
          if (i + 1 == (int)s->size_nibbles && s->size_nibbles > 4 &&
              bits == 0) {
            return ((void)(0), BROTLI_DECODER_ERROR_FORMAT_EXUBERANT_NIBBLE);
          }
          s->meta_block_remaining_len |= (int)(bits << (i * 4));
        }
        s->substate_metablock_header =
            BROTLI_STATE_METABLOCK_HEADER_UNCOMPRESSED;


      case BROTLI_STATE_METABLOCK_HEADER_UNCOMPRESSED:
        if (!s->is_last_metablock) {
          if (!BrotliSafeReadBits(br, 1, &bits)) {
            return BROTLI_DECODER_NEEDS_MORE_INPUT;
          }
          s->is_uncompressed = bits ? 1 : 0;
        }
        ++s->meta_block_remaining_len;
        s->substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_NONE;
        return BROTLI_DECODER_SUCCESS;

      case BROTLI_STATE_METABLOCK_HEADER_RESERVED:
        if (!BrotliSafeReadBits(br, 1, &bits)) {
          return BROTLI_DECODER_NEEDS_MORE_INPUT;
        }
        if (bits != 0) {
          return ((void)(0), BROTLI_DECODER_ERROR_FORMAT_RESERVED);
        }
        s->substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_BYTES;


      case BROTLI_STATE_METABLOCK_HEADER_BYTES:
        if (!BrotliSafeReadBits(br, 2, &bits)) {
          return BROTLI_DECODER_NEEDS_MORE_INPUT;
        }
        if (bits == 0) {
          s->substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_NONE;
          return BROTLI_DECODER_SUCCESS;
        }
        s->size_nibbles = (uint8_t)bits;
        s->substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_METADATA;


      case BROTLI_STATE_METABLOCK_HEADER_METADATA:
        i = s->loop_counter;
        for (; i < (int)s->size_nibbles; ++i) {
          if (!BrotliSafeReadBits(br, 8, &bits)) {
            s->loop_counter = i;
            return BROTLI_DECODER_NEEDS_MORE_INPUT;
          }
          if (i + 1 == (int)s->size_nibbles && s->size_nibbles > 1 &&
              bits == 0) {
            return ((void)(0), BROTLI_DECODER_ERROR_FORMAT_EXUBERANT_META_NIBBLE)
                                                                  ;
          }
          s->meta_block_remaining_len |= (int)(bits << (i * 8));
        }
        ++s->meta_block_remaining_len;
        s->substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_NONE;
        return BROTLI_DECODER_SUCCESS;

      default:
        return
            ((void)(0), BROTLI_DECODER_ERROR_UNREACHABLE);
    }
  }
}





static inline uint32_t DecodeSymbol(uint32_t bits,
                                           const HuffmanCode* table,
                                           BrotliBitReader* br) {
  ;
  table += (bits & 0xFF);
  if ((table->bits) > 8U) {
    uint32_t nbits = (table->bits) - 8U;
    BrotliDropBits(br, 8U);
    table += ((table->value) + ((bits >> 8U) & BitMask(nbits)))

                                                        ;
  }
  BrotliDropBits(br, (table->bits));
  return (table->value);
}



static inline uint32_t ReadSymbol(const HuffmanCode* table,
                                         BrotliBitReader* br) {
  return DecodeSymbol(BrotliGet16BitsUnmasked(br), table, br);
}



static int SafeDecodeSymbol(
    const HuffmanCode* table, BrotliBitReader* br, uint32_t* result) {
  uint32_t val;
  uint32_t available_bits = BrotliGetAvailableBits(br);
  ;
  if (available_bits == 0) {
    if ((table->bits) == 0) {
      *result = (table->value);
      return 1;
    }
    return 0;
  }
  val = (uint32_t)BrotliGetBitsUnmasked(br);
  table += (val & 0xFF);
  if ((table->bits) <= 8U) {
    if ((table->bits) <= available_bits) {
      BrotliDropBits(br, (table->bits));
      *result = (table->value);
      return 1;
    } else {
      return 0;
    }
  }
  if (available_bits <= 8U) {
    return 0;
  }


  val = (val & BitMask((table->bits))) >> 8U;
  available_bits -= 8U;
  table += ((table->value) + val);
  if (available_bits < (table->bits)) {
    return 0;
  }

  BrotliDropBits(br, 8U + (table->bits));
  *result = (table->value);
  return 1;
}

static inline int SafeReadSymbol(
    const HuffmanCode* table, BrotliBitReader* br, uint32_t* result) {
  uint32_t val;
  if ((__builtin_expect(!!(BrotliSafeGetBits(br, 15, &val)), 1))) {
    *result = DecodeSymbol(val, table, br);
    return 1;
  }
  return SafeDecodeSymbol(table, br, result);
}


static inline void PreloadSymbol(int safe,
                                        const HuffmanCode* table,
                                        BrotliBitReader* br,
                                        uint32_t* bits,
                                        uint32_t* value) {
  if (safe) {
    return;
  }
  ;
  table += (BrotliGetBits(br, 8U));
  *bits = (table->bits);
  *value = (table->value);
}



static inline uint32_t ReadPreloadedSymbol(const HuffmanCode* table,
                                                  BrotliBitReader* br,
                                                  uint32_t* bits,
                                                  uint32_t* value) {
  uint32_t result = *value;
  if ((__builtin_expect(*bits > 8U, 0))) {
    uint32_t val = BrotliGet16BitsUnmasked(br);
    const HuffmanCode* ext = table + (val & 0xFF) + *value;
    uint32_t mask = BitMask((*bits - 8U));
    ;
    BrotliDropBits(br, 8U);
    ext += ((val >> 8U) & mask);
    BrotliDropBits(br, (ext->bits));
    result = (ext->value);
  } else {
    BrotliDropBits(br, *bits);
  }
  PreloadSymbol(0, table, br, bits, value);
  return result;
}

static inline uint32_t Log2Floor(uint32_t x) {
  uint32_t result = 0;
  while (x) {
    x >>= 1;
    ++result;
  }
  return result;
}




static BrotliDecoderErrorCode ReadSimpleHuffmanSymbols(
    uint32_t alphabet_size_max, uint32_t alphabet_size_limit,
    BrotliDecoderStateInternal* s) {

  BrotliBitReader* br = &s->br;
  BrotliMetablockHeaderArena* h = &s->arena.header;
  uint32_t max_bits = Log2Floor(alphabet_size_max - 1);
  uint32_t i = h->sub_loop_counter;
  uint32_t num_symbols = h->symbol;
  while (i <= num_symbols) {
    uint32_t v;
    if ((__builtin_expect(!BrotliSafeReadBits(br, max_bits, &v), 0))) {
      h->sub_loop_counter = i;
      h->substate_huffman = BROTLI_STATE_HUFFMAN_SIMPLE_READ;
      return BROTLI_DECODER_NEEDS_MORE_INPUT;
    }
    if (v >= alphabet_size_limit) {
      return
          ((void)(0), BROTLI_DECODER_ERROR_FORMAT_SIMPLE_HUFFMAN_ALPHABET);
    }
    h->symbols_lists_array[i] = (uint16_t)v;
    ;
    ++i;
  }

  for (i = 0; i < num_symbols; ++i) {
    uint32_t k = i + 1;
    for (; k <= num_symbols; ++k) {
      if (h->symbols_lists_array[i] == h->symbols_lists_array[k]) {
        return ((void)(0), BROTLI_DECODER_ERROR_FORMAT_SIMPLE_HUFFMAN_SAME);
      }
    }
  }

  return BROTLI_DECODER_SUCCESS;
}







static inline void ProcessSingleCodeLength(uint32_t code_len,
    uint32_t* symbol, uint32_t* repeat, uint32_t* space,
    uint32_t* prev_code_len, uint16_t* symbol_lists,
    uint16_t* code_length_histo, int* next_symbol) {
  *repeat = 0;
  if (code_len != 0) {
    symbol_lists[next_symbol[code_len]] = (uint16_t)(*symbol);
    next_symbol[code_len] = (int)(*symbol);
    *prev_code_len = code_len;
    *space -= 32768U >> code_len;
    code_length_histo[code_len]++;
   
                                     ;
  }
  (*symbol)++;
}
# 545 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c"
static inline void ProcessRepeatedCodeLength(uint32_t code_len,
    uint32_t repeat_delta, uint32_t alphabet_size, uint32_t* symbol,
    uint32_t* repeat, uint32_t* space, uint32_t* prev_code_len,
    uint32_t* repeat_code_len, uint16_t* symbol_lists,
    uint16_t* code_length_histo, int* next_symbol) {
  uint32_t old_repeat;
  uint32_t extra_bits = 3;
  uint32_t new_len = 0;
  if (code_len == 16) {
    new_len = *prev_code_len;
    extra_bits = 2;
  }
  if (*repeat_code_len != new_len) {
    *repeat = 0;
    *repeat_code_len = new_len;
  }
  old_repeat = *repeat;
  if (*repeat > 0) {
    *repeat -= 2;
    *repeat <<= extra_bits;
  }
  *repeat += repeat_delta + 3U;
  repeat_delta = *repeat - old_repeat;
  if (*symbol + repeat_delta > alphabet_size) {
    (void)(0);
    *symbol = alphabet_size;
    *space = 0xFFFFF;
    return;
  }
 
                                                                              ;
  if (*repeat_code_len != 0) {
    unsigned last = *symbol + repeat_delta;
    int next = next_symbol[*repeat_code_len];
    do {
      symbol_lists[next] = (uint16_t)*symbol;
      next = (int)*symbol;
    } while (++(*symbol) != last);
    next_symbol[*repeat_code_len] = next;
    *space -= repeat_delta << (15 - *repeat_code_len);
    code_length_histo[*repeat_code_len] =
        (uint16_t)(code_length_histo[*repeat_code_len] + repeat_delta);
  } else {
    *symbol += repeat_delta;
  }
}


static BrotliDecoderErrorCode ReadSymbolCodeLengths(
    uint32_t alphabet_size, BrotliDecoderStateInternal* s) {
  BrotliBitReader* br = &s->br;
  BrotliMetablockHeaderArena* h = &s->arena.header;
  uint32_t symbol = h->symbol;
  uint32_t repeat = h->repeat;
  uint32_t space = h->space;
  uint32_t prev_code_len = h->prev_code_len;
  uint32_t repeat_code_len = h->repeat_code_len;
  uint16_t* symbol_lists = h->symbol_lists;
  uint16_t* code_length_histo = h->code_length_histo;
  int* next_symbol = h->next_symbol;
  if (!BrotliWarmupBitReader(br)) {
    return BROTLI_DECODER_NEEDS_MORE_INPUT;
  }
  while (symbol < alphabet_size && space > 0) {
    const HuffmanCode* p = h->table;
    uint32_t code_len;
    ;
    if (!BrotliCheckInputAmount(br, (sizeof(uint64_t) >> 1))) {
      h->symbol = symbol;
      h->repeat = repeat;
      h->prev_code_len = prev_code_len;
      h->repeat_code_len = repeat_code_len;
      h->space = space;
      return BROTLI_DECODER_NEEDS_MORE_INPUT;
    }
    BrotliFillBitWindow16(br);
    p += (BrotliGetBitsUnmasked(br) & BitMask(5))
                                                            ;
    BrotliDropBits(br, (p->bits));
    code_len = (p->value);
    if (code_len < 16) {
      ProcessSingleCodeLength(code_len, &symbol, &repeat, &space,
          &prev_code_len, symbol_lists, code_length_histo, next_symbol);
    } else {
      uint32_t extra_bits =
          (code_len == 16) ? 2 : 3;
      uint32_t repeat_delta =
          (uint32_t)BrotliGetBitsUnmasked(br) & BitMask(extra_bits);
      BrotliDropBits(br, extra_bits);
      ProcessRepeatedCodeLength(code_len, repeat_delta, alphabet_size,
          &symbol, &repeat, &space, &prev_code_len, &repeat_code_len,
          symbol_lists, code_length_histo, next_symbol);
    }
  }
  h->space = space;
  return BROTLI_DECODER_SUCCESS;
}

static BrotliDecoderErrorCode SafeReadSymbolCodeLengths(
    uint32_t alphabet_size, BrotliDecoderStateInternal* s) {
  BrotliBitReader* br = &s->br;
  BrotliMetablockHeaderArena* h = &s->arena.header;
  int get_byte = 0;
  while (h->symbol < alphabet_size && h->space > 0) {
    const HuffmanCode* p = h->table;
    uint32_t code_len;
    uint32_t available_bits;
    uint32_t bits = 0;
    ;
    if (get_byte && !BrotliPullByte(br)) return BROTLI_DECODER_NEEDS_MORE_INPUT;
    get_byte = 0;
    available_bits = BrotliGetAvailableBits(br);
    if (available_bits != 0) {
      bits = (uint32_t)BrotliGetBitsUnmasked(br);
    }
    p += (bits & BitMask(5))
                                                                   ;
    if ((p->bits) > available_bits) {
      get_byte = 1;
      continue;
    }
    code_len = (p->value);
    if (code_len < 16) {
      BrotliDropBits(br, (p->bits));
      ProcessSingleCodeLength(code_len, &h->symbol, &h->repeat, &h->space,
          &h->prev_code_len, h->symbol_lists, h->code_length_histo,
          h->next_symbol);
    } else {
      uint32_t extra_bits = code_len - 14U;
      uint32_t repeat_delta = (bits >> (p->bits)) &
          BitMask(extra_bits);
      if (available_bits < (p->bits) + extra_bits) {
        get_byte = 1;
        continue;
      }
      BrotliDropBits(br, (p->bits) + extra_bits);
      ProcessRepeatedCodeLength(code_len, repeat_delta, alphabet_size,
          &h->symbol, &h->repeat, &h->space, &h->prev_code_len,
          &h->repeat_code_len, h->symbol_lists, h->code_length_histo,
          h->next_symbol);
    }
  }
  return BROTLI_DECODER_SUCCESS;
}



static BrotliDecoderErrorCode ReadCodeLengthCodeLengths(BrotliDecoderStateInternal* s) {
  BrotliBitReader* br = &s->br;
  BrotliMetablockHeaderArena* h = &s->arena.header;
  uint32_t num_codes = h->repeat;
  unsigned space = h->space;
  uint32_t i = h->sub_loop_counter;
  for (; i < (17 + 1); ++i) {
    const uint8_t code_len_idx = kCodeLengthCodeOrder[i];
    uint32_t ix;
    uint32_t v;
    if ((__builtin_expect(!BrotliSafeGetBits(br, 4, &ix), 0))) {
      uint32_t available_bits = BrotliGetAvailableBits(br);
      if (available_bits != 0) {
        ix = BrotliGetBitsUnmasked(br) & 0xF;
      } else {
        ix = 0;
      }
      if (kCodeLengthPrefixLength[ix] > available_bits) {
        h->sub_loop_counter = i;
        h->repeat = num_codes;
        h->space = space;
        h->substate_huffman = BROTLI_STATE_HUFFMAN_COMPLEX;
        return BROTLI_DECODER_NEEDS_MORE_INPUT;
      }
    }
    v = kCodeLengthPrefixValue[ix];
    BrotliDropBits(br, kCodeLengthPrefixLength[ix]);
    h->code_length_code_lengths[code_len_idx] = (uint8_t)v;
    ;
    if (v != 0) {
      space = space - (32U >> v);
      ++num_codes;
      ++h->code_length_histo[v];
      if (space - 1U >= 32U) {

        break;
      }
    }
  }
  if (!(num_codes == 1 || space == 0)) {
    return ((void)(0), BROTLI_DECODER_ERROR_FORMAT_CL_SPACE);
  }
  return BROTLI_DECODER_SUCCESS;
}
# 748 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c"
static BrotliDecoderErrorCode ReadHuffmanCode(uint32_t alphabet_size_max,
                                              uint32_t alphabet_size_limit,
                                              HuffmanCode* table,
                                              uint32_t* opt_table_size,
                                              BrotliDecoderStateInternal* s) {
  BrotliBitReader* br = &s->br;
  BrotliMetablockHeaderArena* h = &s->arena.header;

  for (;;) {
    switch (h->substate_huffman) {
      case BROTLI_STATE_HUFFMAN_NONE:
        if (!BrotliSafeReadBits(br, 2, &h->sub_loop_counter)) {
          return BROTLI_DECODER_NEEDS_MORE_INPUT;
        }
        ;



        if (h->sub_loop_counter != 1) {
          h->space = 32;
          h->repeat = 0;
          memset(&h->code_length_histo[0], 0, sizeof(h->code_length_histo[0]) *
              (5 + 1));
          memset(&h->code_length_code_lengths[0], 0,
              sizeof(h->code_length_code_lengths));
          h->substate_huffman = BROTLI_STATE_HUFFMAN_COMPLEX;
          continue;
        }


      case BROTLI_STATE_HUFFMAN_SIMPLE_SIZE:

        if (!BrotliSafeReadBits(br, 2, &h->symbol)) {
          h->substate_huffman = BROTLI_STATE_HUFFMAN_SIMPLE_SIZE;
          return BROTLI_DECODER_NEEDS_MORE_INPUT;
        }
        h->sub_loop_counter = 0;


      case BROTLI_STATE_HUFFMAN_SIMPLE_READ: {
        BrotliDecoderErrorCode result =
            ReadSimpleHuffmanSymbols(alphabet_size_max, alphabet_size_limit, s);
        if (result != BROTLI_DECODER_SUCCESS) {
          return result;
        }
      }


      case BROTLI_STATE_HUFFMAN_SIMPLE_BUILD: {
        uint32_t table_size;
        if (h->symbol == 3) {
          uint32_t bits;
          if (!BrotliSafeReadBits(br, 1, &bits)) {
            h->substate_huffman = BROTLI_STATE_HUFFMAN_SIMPLE_BUILD;
            return BROTLI_DECODER_NEEDS_MORE_INPUT;
          }
          h->symbol += bits;
        }
        ;
        table_size = BrotliBuildSimpleHuffmanTable(
            table, 8U, h->symbols_lists_array, h->symbol);
        if (opt_table_size) {
          *opt_table_size = table_size;
        }
        h->substate_huffman = BROTLI_STATE_HUFFMAN_NONE;
        return BROTLI_DECODER_SUCCESS;
      }


      case BROTLI_STATE_HUFFMAN_COMPLEX: {
        uint32_t i;
        BrotliDecoderErrorCode result = ReadCodeLengthCodeLengths(s);
        if (result != BROTLI_DECODER_SUCCESS) {
          return result;
        }
        BrotliBuildCodeLengthsHuffmanTable(h->table,
                                           h->code_length_code_lengths,
                                           h->code_length_histo);
        memset(&h->code_length_histo[0], 0, sizeof(h->code_length_histo));
        for (i = 0; i <= 15; ++i) {
          h->next_symbol[i] = (int)i - (15 + 1);
          h->symbol_lists[h->next_symbol[i]] = 0xFFFF;
        }

        h->symbol = 0;
        h->prev_code_len = 8;
        h->repeat = 0;
        h->repeat_code_len = 0;
        h->space = 32768;
        h->substate_huffman = BROTLI_STATE_HUFFMAN_LENGTH_SYMBOLS;
      }


      case BROTLI_STATE_HUFFMAN_LENGTH_SYMBOLS: {
        uint32_t table_size;
        BrotliDecoderErrorCode result = ReadSymbolCodeLengths(
            alphabet_size_limit, s);
        if (result == BROTLI_DECODER_NEEDS_MORE_INPUT) {
          result = SafeReadSymbolCodeLengths(alphabet_size_limit, s);
        }
        if (result != BROTLI_DECODER_SUCCESS) {
          return result;
        }

        if (h->space != 0) {
          ;
          return ((void)(0), BROTLI_DECODER_ERROR_FORMAT_HUFFMAN_SPACE);
        }
        table_size = BrotliBuildHuffmanTable(
            table, 8U, h->symbol_lists, h->code_length_histo);
        if (opt_table_size) {
          *opt_table_size = table_size;
        }
        h->substate_huffman = BROTLI_STATE_HUFFMAN_NONE;
        return BROTLI_DECODER_SUCCESS;
      }

      default:
        return
            ((void)(0), BROTLI_DECODER_ERROR_UNREACHABLE);
    }
  }
}


static inline uint32_t ReadBlockLength(const HuffmanCode* table,
                                              BrotliBitReader* br) {
  uint32_t code;
  uint32_t nbits;
  code = ReadSymbol(table, br);
  nbits = _kBrotliPrefixCodeRanges[code].nbits;
  return _kBrotliPrefixCodeRanges[code].offset + BrotliReadBits24(br, nbits);
}



static inline int SafeReadBlockLength(
    BrotliDecoderStateInternal* s, uint32_t* result, const HuffmanCode* table,
    BrotliBitReader* br) {
  uint32_t index;
  if (s->substate_read_block_length == BROTLI_STATE_READ_BLOCK_LENGTH_NONE) {
    if (!SafeReadSymbol(table, br, &index)) {
      return 0;
    }
  } else {
    index = s->block_length_index;
  }
  {
    uint32_t bits;
    uint32_t nbits = _kBrotliPrefixCodeRanges[index].nbits;
    uint32_t offset = _kBrotliPrefixCodeRanges[index].offset;
    if (!BrotliSafeReadBits(br, nbits, &bits)) {
      s->block_length_index = index;
      s->substate_read_block_length = BROTLI_STATE_READ_BLOCK_LENGTH_SUFFIX;
      return 0;
    }
    *result = offset + bits;
    s->substate_read_block_length = BROTLI_STATE_READ_BLOCK_LENGTH_NONE;
    return 1;
  }
}
# 924 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c"
static void InverseMoveToFrontTransform(
    uint8_t* v, uint32_t v_len, BrotliDecoderStateInternal* state) {

  uint32_t i = 1;
  uint32_t upper_bound = state->mtf_upper_bound;
  uint32_t* mtf = &state->mtf[1];
  uint8_t* mtf_u8 = (uint8_t*)mtf;

  const uint8_t b0123[4] = {0, 1, 2, 3};
  uint32_t pattern;
  memcpy(&pattern, &b0123, 4);


  mtf[0] = pattern;
  do {
    pattern += 0x04040404;
    mtf[i] = pattern;
    i++;
  } while (i <= upper_bound);


  upper_bound = 0;
  for (i = 0; i < v_len; ++i) {
    int index = v[i];
    uint8_t value = mtf_u8[index];
    upper_bound |= v[i];
    v[i] = value;
    mtf_u8[-1] = value;
    do {
      index--;
      mtf_u8[index + 1] = mtf_u8[index];
    } while (index >= 0);
  }

  state->mtf_upper_bound = upper_bound >> 2;
}


static BrotliDecoderErrorCode HuffmanTreeGroupDecode(
    HuffmanTreeGroup* group, BrotliDecoderStateInternal* s) {
  BrotliMetablockHeaderArena* h = &s->arena.header;
  if (h->substate_tree_group != BROTLI_STATE_TREE_GROUP_LOOP) {
    h->next = group->codes;
    h->htree_index = 0;
    h->substate_tree_group = BROTLI_STATE_TREE_GROUP_LOOP;
  }
  while (h->htree_index < group->num_htrees) {
    uint32_t table_size;
    BrotliDecoderErrorCode result = ReadHuffmanCode(group->alphabet_size_max,
        group->alphabet_size_limit, h->next, &table_size, s);
    if (result != BROTLI_DECODER_SUCCESS) return result;
    group->htrees[h->htree_index] = h->next;
    h->next += table_size;
    ++h->htree_index;
  }
  h->substate_tree_group = BROTLI_STATE_TREE_GROUP_NONE;
  return BROTLI_DECODER_SUCCESS;
}
# 991 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c"
static BrotliDecoderErrorCode DecodeContextMap(uint32_t context_map_size,
                                               uint32_t* num_htrees,
                                               uint8_t** context_map_arg,
                                               BrotliDecoderStateInternal* s) {
  BrotliBitReader* br = &s->br;
  BrotliDecoderErrorCode result = BROTLI_DECODER_SUCCESS;
  BrotliMetablockHeaderArena* h = &s->arena.header;

  switch ((int)h->substate_context_map) {
    case BROTLI_STATE_CONTEXT_MAP_NONE:
      result = DecodeVarLenUint8(s, br, num_htrees);
      if (result != BROTLI_DECODER_SUCCESS) {
        return result;
      }
      (*num_htrees)++;
      h->context_index = 0;
      ;
      ;
      *context_map_arg =
          (uint8_t*)s->alloc_func(s->memory_manager_opaque, (size_t)context_map_size);
      if (*context_map_arg == 0) {
        return ((void)(0), BROTLI_DECODER_ERROR_ALLOC_CONTEXT_MAP);
      }
      if (*num_htrees <= 1) {
        memset(*context_map_arg, 0, (size_t)context_map_size);
        return BROTLI_DECODER_SUCCESS;
      }
      h->substate_context_map = BROTLI_STATE_CONTEXT_MAP_READ_PREFIX;


    case BROTLI_STATE_CONTEXT_MAP_READ_PREFIX: {
      uint32_t bits;


      if (!BrotliSafeGetBits(br, 5, &bits)) {
        return BROTLI_DECODER_NEEDS_MORE_INPUT;
      }
      if ((bits & 1) != 0) {
        h->max_run_length_prefix = (bits >> 1) + 1;
        BrotliDropBits(br, 5);
      } else {
        h->max_run_length_prefix = 0;
        BrotliDropBits(br, 1);
      }
      ;
      h->substate_context_map = BROTLI_STATE_CONTEXT_MAP_HUFFMAN;
    }


    case BROTLI_STATE_CONTEXT_MAP_HUFFMAN: {
      uint32_t alphabet_size = *num_htrees + h->max_run_length_prefix;
      result = ReadHuffmanCode(alphabet_size, alphabet_size,
                               h->context_map_table, 0, s);
      if (result != BROTLI_DECODER_SUCCESS) return result;
      h->code = 0xFFFF;
      h->substate_context_map = BROTLI_STATE_CONTEXT_MAP_DECODE;
    }


    case BROTLI_STATE_CONTEXT_MAP_DECODE: {
      uint32_t context_index = h->context_index;
      uint32_t max_run_length_prefix = h->max_run_length_prefix;
      uint8_t* context_map = *context_map_arg;
      uint32_t code = h->code;
      int skip_preamble = (code != 0xFFFF);
      while (context_index < context_map_size || skip_preamble) {
        if (!skip_preamble) {
          if (!SafeReadSymbol(h->context_map_table, br, &code)) {
            h->code = 0xFFFF;
            h->context_index = context_index;
            return BROTLI_DECODER_NEEDS_MORE_INPUT;
          }
          ;

          if (code == 0) {
            context_map[context_index++] = 0;
            continue;
          }
          if (code > max_run_length_prefix) {
            context_map[context_index++] =
                (uint8_t)(code - max_run_length_prefix);
            continue;
          }
        } else {
          skip_preamble = 0;
        }

        {
          uint32_t reps;
          if (!BrotliSafeReadBits(br, code, &reps)) {
            h->code = code;
            h->context_index = context_index;
            return BROTLI_DECODER_NEEDS_MORE_INPUT;
          }
          reps += 1U << code;
          ;
          if (context_index + reps > context_map_size) {
            return
                ((void)(0), BROTLI_DECODER_ERROR_FORMAT_CONTEXT_MAP_REPEAT);
          }
          do {
            context_map[context_index++] = 0;
          } while (--reps);
        }
      }
    }


    case BROTLI_STATE_CONTEXT_MAP_TRANSFORM: {
      uint32_t bits;
      if (!BrotliSafeReadBits(br, 1, &bits)) {
        h->substate_context_map = BROTLI_STATE_CONTEXT_MAP_TRANSFORM;
        return BROTLI_DECODER_NEEDS_MORE_INPUT;
      }
      if (bits != 0) {
        InverseMoveToFrontTransform(*context_map_arg, context_map_size, s);
      }
      h->substate_context_map = BROTLI_STATE_CONTEXT_MAP_NONE;
      return BROTLI_DECODER_SUCCESS;
    }

    default:
      return
          ((void)(0), BROTLI_DECODER_ERROR_UNREACHABLE);
  }
}



static inline int DecodeBlockTypeAndLength(
    int safe, BrotliDecoderStateInternal* s, int tree_type) {
  uint32_t max_block_type = s->num_block_types[tree_type];
  const HuffmanCode* type_tree = &s->block_type_trees[
      tree_type * 632];
  const HuffmanCode* len_tree = &s->block_len_trees[
      tree_type * 396];
  BrotliBitReader* br = &s->br;
  uint32_t* ringbuffer = &s->block_type_rb[tree_type * 2];
  uint32_t block_type;
  if (max_block_type <= 1) {
    return 0;
  }


  if (!safe) {
    block_type = ReadSymbol(type_tree, br);
    s->block_length[tree_type] = ReadBlockLength(len_tree, br);
  } else {
    BrotliBitReaderState memento;
    BrotliBitReaderSaveState(br, &memento);
    if (!SafeReadSymbol(type_tree, br, &block_type)) return 0;
    if (!SafeReadBlockLength(s, &s->block_length[tree_type], len_tree, br)) {
      s->substate_read_block_length = BROTLI_STATE_READ_BLOCK_LENGTH_NONE;
      BrotliBitReaderRestoreState(br, &memento);
      return 0;
    }
  }

  if (block_type == 1) {
    block_type = ringbuffer[1] + 1;
  } else if (block_type == 0) {
    block_type = ringbuffer[0];
  } else {
    block_type -= 2;
  }
  if (block_type >= max_block_type) {
    block_type -= max_block_type;
  }
  ringbuffer[0] = ringbuffer[1];
  ringbuffer[1] = block_type;
  return 1;
}

static inline void DetectTrivialLiteralBlockTypes(
    BrotliDecoderStateInternal* s) {
  size_t i;
  for (i = 0; i < 8; ++i) s->trivial_literal_contexts[i] = 0;
  for (i = 0; i < s->num_block_types[0]; i++) {
    size_t offset = i << 6;
    size_t error = 0;
    size_t sample = s->context_map[offset];
    size_t j;
    for (j = 0; j < (1u << 6);) {
      { if ((4 & 1) != 0) {error |= s->context_map[offset + j++] ^ sample;;} if ((4 & 2) != 0) {error |= s->context_map[offset + j++] ^ sample;; error |= s->context_map[offset + j++] ^ sample;;} if ((4 & 4) != 0) {error |= s->context_map[offset + j++] ^ sample;; error |= s->context_map[offset + j++] ^ sample;; error |= s->context_map[offset + j++] ^ sample;; error |= s->context_map[offset + j++] ^ sample;;} }
    }
    if (error == 0) {
      s->trivial_literal_contexts[i >> 5] |= 1u << (i & 31);
    }
  }
}

static inline void PrepareLiteralDecoding(BrotliDecoderStateInternal* s) {
  uint8_t context_mode;
  size_t trivial;
  uint32_t block_type = s->block_type_rb[1];
  uint32_t context_offset = block_type << 6;
  s->context_map_slice = s->context_map + context_offset;
  trivial = s->trivial_literal_contexts[block_type >> 5];
  s->trivial_literal_context = (trivial >> (block_type & 31)) & 1;
  s->literal_htree = s->literal_hgroup.htrees[s->context_map_slice[0]];
  context_mode = s->context_modes[block_type] & 3;
  s->context_lookup = (&_kBrotliContextLookupTable[(context_mode) << 9]);
}



static inline int DecodeLiteralBlockSwitchInternal(
    int safe, BrotliDecoderStateInternal* s) {
  if (!DecodeBlockTypeAndLength(safe, s, 0)) {
    return 0;
  }
  PrepareLiteralDecoding(s);
  return 1;
}

static void DecodeLiteralBlockSwitch(BrotliDecoderStateInternal* s) {
  DecodeLiteralBlockSwitchInternal(0, s);
}

static int SafeDecodeLiteralBlockSwitch(
    BrotliDecoderStateInternal* s) {
  return DecodeLiteralBlockSwitchInternal(1, s);
}



static inline int DecodeCommandBlockSwitchInternal(
    int safe, BrotliDecoderStateInternal* s) {
  if (!DecodeBlockTypeAndLength(safe, s, 1)) {
    return 0;
  }
  s->htree_command = s->insert_copy_hgroup.htrees[s->block_type_rb[3]];
  return 1;
}

static void DecodeCommandBlockSwitch(BrotliDecoderStateInternal* s) {
  DecodeCommandBlockSwitchInternal(0, s);
}

static int SafeDecodeCommandBlockSwitch(
    BrotliDecoderStateInternal* s) {
  return DecodeCommandBlockSwitchInternal(1, s);
}



static inline int DecodeDistanceBlockSwitchInternal(
    int safe, BrotliDecoderStateInternal* s) {
  if (!DecodeBlockTypeAndLength(safe, s, 2)) {
    return 0;
  }
  s->dist_context_map_slice = s->dist_context_map +
      (s->block_type_rb[5] << 2);
  s->dist_htree_index = s->dist_context_map_slice[s->distance_context];
  return 1;
}

static void DecodeDistanceBlockSwitch(BrotliDecoderStateInternal* s) {
  DecodeDistanceBlockSwitchInternal(0, s);
}

static int SafeDecodeDistanceBlockSwitch(
    BrotliDecoderStateInternal* s) {
  return DecodeDistanceBlockSwitchInternal(1, s);
}

static size_t UnwrittenBytes(const BrotliDecoderStateInternal* s, int wrap) {
  size_t pos = wrap && s->pos > s->ringbuffer_size ?
      (size_t)s->ringbuffer_size : (size_t)(s->pos);
  size_t partial_pos_rb = (s->rb_roundtrips * (size_t)s->ringbuffer_size) + pos;
  return partial_pos_rb - s->partial_pos_out;
}




static BrotliDecoderErrorCode WriteRingBuffer(
    BrotliDecoderStateInternal* s, size_t* available_out, uint8_t** next_out,
    size_t* total_out, int force) {
  uint8_t* start =
      s->ringbuffer + (s->partial_pos_out & (size_t)s->ringbuffer_mask);
  size_t to_write = UnwrittenBytes(s, 1);
  size_t num_written = *available_out;
  if (num_written > to_write) {
    num_written = to_write;
  }
  if (s->meta_block_remaining_len < 0) {
    return ((void)(0), BROTLI_DECODER_ERROR_FORMAT_BLOCK_LENGTH_1);
  }
  if (next_out && !*next_out) {
    *next_out = start;
  } else {
    if (next_out) {
      memcpy(*next_out, start, num_written);
      *next_out += num_written;
    }
  }
  *available_out -= num_written;
  ;
  ;
  s->partial_pos_out += num_written;
  if (total_out) {
    *total_out = s->partial_pos_out;
  }
  if (num_written < to_write) {
    if (s->ringbuffer_size == (1 << s->window_bits) || force) {
      return BROTLI_DECODER_NEEDS_MORE_OUTPUT;
    } else {
      return BROTLI_DECODER_SUCCESS;
    }
  }

  if (s->ringbuffer_size == (1 << s->window_bits) &&
      s->pos >= s->ringbuffer_size) {
    s->pos -= s->ringbuffer_size;
    s->rb_roundtrips++;
    s->should_wrap_ringbuffer = (size_t)s->pos != 0 ? 1 : 0;
  }
  return BROTLI_DECODER_SUCCESS;
}

static void WrapRingBuffer(BrotliDecoderStateInternal* s) {
  if (s->should_wrap_ringbuffer) {
    memcpy(s->ringbuffer, s->ringbuffer_end, (size_t)s->pos);
    s->should_wrap_ringbuffer = 0;
  }
}
# 1326 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c"
static int BrotliEnsureRingBuffer(
    BrotliDecoderStateInternal* s) {
  uint8_t* old_ringbuffer = s->ringbuffer;
  if (s->ringbuffer_size == s->new_ringbuffer_size) {
    return 1;
  }

  s->ringbuffer = (uint8_t*)s->alloc_func(s->memory_manager_opaque, (size_t)(s->new_ringbuffer_size) + kRingBufferWriteAheadSlack)
                                                                    ;
  if (s->ringbuffer == 0) {

    s->ringbuffer = old_ringbuffer;
    return 0;
  }
  s->ringbuffer[s->new_ringbuffer_size - 2] = 0;
  s->ringbuffer[s->new_ringbuffer_size - 1] = 0;

  if (!!old_ringbuffer) {
    memcpy(s->ringbuffer, old_ringbuffer, (size_t)s->pos);
    { s->free_func(s->memory_manager_opaque, old_ringbuffer); old_ringbuffer = 0; };
  }

  s->ringbuffer_size = s->new_ringbuffer_size;
  s->ringbuffer_mask = s->new_ringbuffer_size - 1;
  s->ringbuffer_end = s->ringbuffer + s->ringbuffer_size;

  return 1;
}

static BrotliDecoderErrorCode CopyUncompressedBlockToOutput(
    size_t* available_out, uint8_t** next_out, size_t* total_out,
    BrotliDecoderStateInternal* s) {

  if (!BrotliEnsureRingBuffer(s)) {
    return ((void)(0), BROTLI_DECODER_ERROR_ALLOC_RING_BUFFER_1);
  }


  for (;;) {
    switch (s->substate_uncompressed) {
      case BROTLI_STATE_UNCOMPRESSED_NONE: {
        int nbytes = (int)BrotliGetRemainingBytes(&s->br);
        if (nbytes > s->meta_block_remaining_len) {
          nbytes = s->meta_block_remaining_len;
        }
        if (s->pos + nbytes > s->ringbuffer_size) {
          nbytes = s->ringbuffer_size - s->pos;
        }

        BrotliCopyBytes(&s->ringbuffer[s->pos], &s->br, (size_t)nbytes);
        s->pos += nbytes;
        s->meta_block_remaining_len -= nbytes;
        if (s->pos < 1 << s->window_bits) {
          if (s->meta_block_remaining_len == 0) {
            return BROTLI_DECODER_SUCCESS;
          }
          return BROTLI_DECODER_NEEDS_MORE_INPUT;
        }
        s->substate_uncompressed = BROTLI_STATE_UNCOMPRESSED_WRITE;
      }


      case BROTLI_STATE_UNCOMPRESSED_WRITE: {
        BrotliDecoderErrorCode result;
        result = WriteRingBuffer(
            s, available_out, next_out, total_out, 0);
        if (result != BROTLI_DECODER_SUCCESS) {
          return result;
        }
        if (s->ringbuffer_size == 1 << s->window_bits) {
          s->max_distance = s->max_backward_distance;
        }
        s->substate_uncompressed = BROTLI_STATE_UNCOMPRESSED_NONE;
        break;
      }
    }
  }
  ;
}







static void BrotliCalculateRingBufferSize(
    BrotliDecoderStateInternal* s) {
  int window_size = 1 << s->window_bits;
  int new_ringbuffer_size = window_size;


  int min_size = s->ringbuffer_size ? s->ringbuffer_size : 1024;
  int output_size;


  if (s->ringbuffer_size == window_size) {
    return;
  }


  if (s->is_metadata) {
    return;
  }

  if (!s->ringbuffer) {
    output_size = 0;
  } else {
    output_size = s->pos;
  }
  output_size += s->meta_block_remaining_len;
  min_size = min_size < output_size ? output_size : min_size;

  if (!!s->canny_ringbuffer_allocation) {



    while ((new_ringbuffer_size >> 1) >= min_size) {
      new_ringbuffer_size >>= 1;
    }
  }

  s->new_ringbuffer_size = new_ringbuffer_size;
}


static BrotliDecoderErrorCode ReadContextModes(BrotliDecoderStateInternal* s) {
  BrotliBitReader* br = &s->br;
  int i = s->loop_counter;

  while (i < (int)s->num_block_types[0]) {
    uint32_t bits;
    if (!BrotliSafeReadBits(br, 2, &bits)) {
      s->loop_counter = i;
      return BROTLI_DECODER_NEEDS_MORE_INPUT;
    }
    s->context_modes[i] = (uint8_t)bits;
    ;
    i++;
  }
  return BROTLI_DECODER_SUCCESS;
}

static inline void TakeDistanceFromRingBuffer(BrotliDecoderStateInternal* s) {
  int offset = s->distance_code - 3;
  if (s->distance_code <= 3) {

    s->distance_context = 1 >> s->distance_code;
    s->distance_code = s->dist_rb[(s->dist_rb_idx - offset) & 3];
    s->dist_rb_idx -= s->distance_context;
  } else {
    int index_delta = 3;
    int delta;
    int base = s->distance_code - 10;
    if (s->distance_code < 10) {
      base = s->distance_code - 4;
    } else {
      index_delta = 2;
    }

    delta = ((0x605142 >> (4 * base)) & 0xF) - 3;
    s->distance_code = s->dist_rb[(s->dist_rb_idx + index_delta) & 0x3] + delta;
    if (s->distance_code <= 0) {


      s->distance_code = 0x7FFFFFFF;
    }
  }
}

static inline int SafeReadBits(
    BrotliBitReader* const br, uint32_t n_bits, uint32_t* val) {
  if (n_bits != 0) {
    return BrotliSafeReadBits(br, n_bits, val);
  } else {
    *val = 0;
    return 1;
  }
}

static inline int SafeReadBits32(
    BrotliBitReader* const br, uint32_t n_bits, uint32_t* val) {
  if (n_bits != 0) {
    return BrotliSafeReadBits32(br, n_bits, val);
  } else {
    *val = 0;
    return 1;
  }
}
# 1583 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c"
static void CalculateDistanceLut(BrotliDecoderStateInternal* s) {
  BrotliMetablockBodyArena* b = &s->arena.body;
  uint32_t npostfix = s->distance_postfix_bits;
  uint32_t ndirect = s->num_direct_distance_codes;
  uint32_t alphabet_size_limit = s->distance_hgroup.alphabet_size_limit;
  uint32_t postfix = 1u << npostfix;
  uint32_t j;
  uint32_t bits = 1;
  uint32_t half = 0;


  uint32_t i = 16;


  for (j = 0; j < ndirect; ++j) {
    b->dist_extra_bits[i] = 0;
    b->dist_offset[i] = j + 1;
    ++i;
  }


  while (i < alphabet_size_limit) {
    uint32_t base = ndirect + ((((2 + half) << bits) - 4) << npostfix) + 1;

    for (j = 0; j < postfix; ++j) {
      b->dist_extra_bits[i] = (uint8_t)bits;
      b->dist_offset[i] = base + j;
      ++i;
    }
    bits = bits + half;
    half = half ^ 1;
  }
}


static inline int ReadDistanceInternal(
    int safe, BrotliDecoderStateInternal* s, BrotliBitReader* br) {
  BrotliMetablockBodyArena* b = &s->arena.body;
  uint32_t code;
  uint32_t bits;
  BrotliBitReaderState memento;
  HuffmanCode* distance_tree = s->distance_hgroup.htrees[s->dist_htree_index];
  if (!safe) {
    code = ReadSymbol(distance_tree, br);
  } else {
    BrotliBitReaderSaveState(br, &memento);
    if (!SafeReadSymbol(distance_tree, br, &code)) {
      return 0;
    }
  }
  --s->block_length[2];


  s->distance_context = 0;
  if ((code & ~0xFu) == 0) {
    s->distance_code = (int)code;
    TakeDistanceFromRingBuffer(s);
    return 1;
  }
  if (!safe) {
    bits = BrotliReadBits32(br, b->dist_extra_bits[code]);
  } else {
    if (!SafeReadBits32(br, b->dist_extra_bits[code], &bits)) {
      ++s->block_length[2];
      BrotliBitReaderRestoreState(br, &memento);
      return 0;
    }
  }
  s->distance_code =
      (int)(b->dist_offset[code] + (bits << s->distance_postfix_bits));
  return 1;
}

static inline void ReadDistance(
    BrotliDecoderStateInternal* s, BrotliBitReader* br) {
  ReadDistanceInternal(0, s, br);
}

static inline int SafeReadDistance(
    BrotliDecoderStateInternal* s, BrotliBitReader* br) {
  return ReadDistanceInternal(1, s, br);
}

static inline int ReadCommandInternal(
    int safe, BrotliDecoderStateInternal* s, BrotliBitReader* br, int* insert_length) {
  uint32_t cmd_code;
  uint32_t insert_len_extra = 0;
  uint32_t copy_length;
  CmdLutElement v;
  BrotliBitReaderState memento;
  if (!safe) {
    cmd_code = ReadSymbol(s->htree_command, br);
  } else {
    BrotliBitReaderSaveState(br, &memento);
    if (!SafeReadSymbol(s->htree_command, br, &cmd_code)) {
      return 0;
    }
  }
  v = kCmdLut[cmd_code];
  s->distance_code = v.distance_code;
  s->distance_context = v.context;
  s->dist_htree_index = s->dist_context_map_slice[s->distance_context];
  *insert_length = v.insert_len_offset;
  if (!safe) {
    if ((__builtin_expect(v.insert_len_extra_bits != 0, 0))) {
      insert_len_extra = BrotliReadBits24(br, v.insert_len_extra_bits);
    }
    copy_length = BrotliReadBits24(br, v.copy_len_extra_bits);
  } else {
    if (!SafeReadBits(br, v.insert_len_extra_bits, &insert_len_extra) ||
        !SafeReadBits(br, v.copy_len_extra_bits, &copy_length)) {
      BrotliBitReaderRestoreState(br, &memento);
      return 0;
    }
  }
  s->copy_length = (int)copy_length + v.copy_len_offset;
  --s->block_length[1];
  *insert_length += (int)insert_len_extra;
  return 1;
}

static inline void ReadCommand(
    BrotliDecoderStateInternal* s, BrotliBitReader* br, int* insert_length) {
  ReadCommandInternal(0, s, br, insert_length);
}

static inline int SafeReadCommand(
    BrotliDecoderStateInternal* s, BrotliBitReader* br, int* insert_length) {
  return ReadCommandInternal(1, s, br, insert_length);
}

static inline int CheckInputAmount(
    int safe, BrotliBitReader* const br, size_t num) {
  if (safe) {
    return 1;
  }
  return BrotliCheckInputAmount(br, num);
}
# 1734 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c"
static inline BrotliDecoderErrorCode ProcessCommandsInternal(
    int safe, BrotliDecoderStateInternal* s) {
  int pos = s->pos;
  int i = s->loop_counter;
  BrotliDecoderErrorCode result = BROTLI_DECODER_SUCCESS;
  BrotliBitReader* br = &s->br;

  if (!CheckInputAmount(safe, br, 28)) {
    result = BROTLI_DECODER_NEEDS_MORE_INPUT;
    goto saveStateAndReturn;
  }
  if (!safe) {
    (void)(BrotliWarmupBitReader(br));
  }


  if (s->state == BROTLI_STATE_COMMAND_BEGIN) {
    goto CommandBegin;
  } else if (s->state == BROTLI_STATE_COMMAND_INNER) {
    goto CommandInner;
  } else if (s->state == BROTLI_STATE_COMMAND_POST_DECODE_LITERALS) {
    goto CommandPostDecodeLiterals;
  } else if (s->state == BROTLI_STATE_COMMAND_POST_WRAP_COPY) {
    goto CommandPostWrapCopy;
  } else {
    return ((void)(0), BROTLI_DECODER_ERROR_UNREACHABLE);
  }

CommandBegin:
  if (safe) {
    s->state = BROTLI_STATE_COMMAND_BEGIN;
  }
  if (!CheckInputAmount(safe, br, 28)) {
    s->state = BROTLI_STATE_COMMAND_BEGIN;
    result = BROTLI_DECODER_NEEDS_MORE_INPUT;
    goto saveStateAndReturn;
  }
  if ((__builtin_expect(s->block_length[1] == 0, 0))) {
    { if (safe) { if (!SafeDecodeCommandBlockSwitch(s)) { result = BROTLI_DECODER_NEEDS_MORE_INPUT; goto saveStateAndReturn; } } else { DecodeCommandBlockSwitch(s); } };
    goto CommandBegin;
  }

  { if (safe) { if (!SafeReadCommand(s, br, &i)) { result = BROTLI_DECODER_NEEDS_MORE_INPUT; goto saveStateAndReturn; } } else { ReadCommand(s, br, &i); } };
 
                                      ;
  if (i == 0) {
    goto CommandPostDecodeLiterals;
  }
  s->meta_block_remaining_len -= i;

CommandInner:
  if (safe) {
    s->state = BROTLI_STATE_COMMAND_INNER;
  }

  if (s->trivial_literal_context) {
    uint32_t bits;
    uint32_t value;
    PreloadSymbol(safe, s->literal_htree, br, &bits, &value);
    do {
      if (!CheckInputAmount(safe, br, 28)) {
        s->state = BROTLI_STATE_COMMAND_INNER;
        result = BROTLI_DECODER_NEEDS_MORE_INPUT;
        goto saveStateAndReturn;
      }
      if ((__builtin_expect(s->block_length[0] == 0, 0))) {
        { if (safe) { if (!SafeDecodeLiteralBlockSwitch(s)) { result = BROTLI_DECODER_NEEDS_MORE_INPUT; goto saveStateAndReturn; } } else { DecodeLiteralBlockSwitch(s); } };
        PreloadSymbol(safe, s->literal_htree, br, &bits, &value);
        if (!s->trivial_literal_context) goto CommandInner;
      }
      if (!safe) {
        s->ringbuffer[pos] =
            (uint8_t)ReadPreloadedSymbol(s->literal_htree, br, &bits, &value);
      } else {
        uint32_t literal;
        if (!SafeReadSymbol(s->literal_htree, br, &literal)) {
          result = BROTLI_DECODER_NEEDS_MORE_INPUT;
          goto saveStateAndReturn;
        }
        s->ringbuffer[pos] = (uint8_t)literal;
      }
      --s->block_length[0];
      ;
      ++pos;
      if ((__builtin_expect(pos == s->ringbuffer_size, 0))) {
        s->state = BROTLI_STATE_COMMAND_INNER_WRITE;
        --i;
        goto saveStateAndReturn;
      }
    } while (--i != 0);
  } else {
    uint8_t p1 = s->ringbuffer[(pos - 1) & s->ringbuffer_mask];
    uint8_t p2 = s->ringbuffer[(pos - 2) & s->ringbuffer_mask];
    do {
      const HuffmanCode* hc;
      uint8_t context;
      if (!CheckInputAmount(safe, br, 28)) {
        s->state = BROTLI_STATE_COMMAND_INNER;
        result = BROTLI_DECODER_NEEDS_MORE_INPUT;
        goto saveStateAndReturn;
      }
      if ((__builtin_expect(s->block_length[0] == 0, 0))) {
        { if (safe) { if (!SafeDecodeLiteralBlockSwitch(s)) { result = BROTLI_DECODER_NEEDS_MORE_INPUT; goto saveStateAndReturn; } } else { DecodeLiteralBlockSwitch(s); } };
        if (s->trivial_literal_context) goto CommandInner;
      }
      context = ((s->context_lookup)[p1] | ((s->context_lookup) + 256)[p2]);
      ;
      hc = s->literal_hgroup.htrees[s->context_map_slice[context]];
      p2 = p1;
      if (!safe) {
        p1 = (uint8_t)ReadSymbol(hc, br);
      } else {
        uint32_t literal;
        if (!SafeReadSymbol(hc, br, &literal)) {
          result = BROTLI_DECODER_NEEDS_MORE_INPUT;
          goto saveStateAndReturn;
        }
        p1 = (uint8_t)literal;
      }
      s->ringbuffer[pos] = p1;
      --s->block_length[0];
      ;
      ;
      ++pos;
      if ((__builtin_expect(pos == s->ringbuffer_size, 0))) {
        s->state = BROTLI_STATE_COMMAND_INNER_WRITE;
        --i;
        goto saveStateAndReturn;
      }
    } while (--i != 0);
  }
  ;
  if ((__builtin_expect(s->meta_block_remaining_len <= 0, 0))) {
    s->state = BROTLI_STATE_METABLOCK_DONE;
    goto saveStateAndReturn;
  }

CommandPostDecodeLiterals:
  if (safe) {
    s->state = BROTLI_STATE_COMMAND_POST_DECODE_LITERALS;
  }
  if (s->distance_code >= 0) {

    s->distance_context = s->distance_code ? 0 : 1;
    --s->dist_rb_idx;
    s->distance_code = s->dist_rb[s->dist_rb_idx & 3];
  } else {

    if ((__builtin_expect(s->block_length[2] == 0, 0))) {
      { if (safe) { if (!SafeDecodeDistanceBlockSwitch(s)) { result = BROTLI_DECODER_NEEDS_MORE_INPUT; goto saveStateAndReturn; } } else { DecodeDistanceBlockSwitch(s); } };
    }
    { if (safe) { if (!SafeReadDistance(s, br)) { result = BROTLI_DECODER_NEEDS_MORE_INPUT; goto saveStateAndReturn; } } else { ReadDistance(s, br); } };
  }
 
                                     ;
  if (s->max_distance != s->max_backward_distance) {
    s->max_distance =
        (pos < s->max_backward_distance) ? pos : s->max_backward_distance;
  }
  i = s->copy_length;


  if (s->distance_code > s->max_distance) {



    if (s->distance_code > 0x7FFFFFFC) {
     

                                                                 ;
      return ((void)(0), BROTLI_DECODER_ERROR_FORMAT_DISTANCE);
    }
    if (i >= 4 &&
        i <= 24) {
      int address = s->distance_code - s->max_distance - 1;
      const BrotliDictionary* words = s->dictionary;
      const BrotliTransforms* transforms = s->transforms;
      int offset = (int)s->dictionary->offsets_by_length[i];
      uint32_t shift = s->dictionary->size_bits_by_length[i];

      int mask = (int)BitMask(shift);
      int word_idx = address & mask;
      int transform_idx = address >> shift;

      s->dist_rb_idx += s->distance_context;
      offset += word_idx * i;
      if ((__builtin_expect(!words->data, 0))) {
        return ((void)(0), BROTLI_DECODER_ERROR_DICTIONARY_NOT_SET);
      }
      if (transform_idx < (int)transforms->num_transforms) {
        const uint8_t* word = &words->data[offset];
        int len = i;
        if (transform_idx == transforms->cutOffTransforms[0]) {
          memcpy(&s->ringbuffer[pos], word, (size_t)len);
         
                                 ;
        } else {
          len = BrotliTransformDictionaryWord(&s->ringbuffer[pos], word, len,
              transforms, transform_idx);
         

                                                                        ;
        }
        pos += len;
        s->meta_block_remaining_len -= len;
        if (pos >= s->ringbuffer_size) {
          s->state = BROTLI_STATE_COMMAND_POST_WRITE_1;
          goto saveStateAndReturn;
        }
      } else {
       

                                                                   ;
        return ((void)(0), BROTLI_DECODER_ERROR_FORMAT_TRANSFORM);
      }
    } else {
     

                                                                 ;
      return ((void)(0), BROTLI_DECODER_ERROR_FORMAT_DICTIONARY);
    }
  } else {
    int src_start = (pos - s->distance_code) & s->ringbuffer_mask;
    uint8_t* copy_dst = &s->ringbuffer[pos];
    uint8_t* copy_src = &s->ringbuffer[src_start];
    int dst_end = pos + i;
    int src_end = src_start + i;

    s->dist_rb[s->dist_rb_idx & 3] = s->distance_code;
    ++s->dist_rb_idx;
    s->meta_block_remaining_len -= i;



    memmove16(copy_dst, copy_src);
    if (src_end > pos && dst_end > src_start) {

      goto CommandPostWrapCopy;
    }
    if (dst_end >= s->ringbuffer_size || src_end >= s->ringbuffer_size) {

      goto CommandPostWrapCopy;
    }
    pos += i;
    if (i > 16) {
      if (i > 32) {
        memcpy(copy_dst + 16, copy_src + 16, (size_t)(i - 16));
      } else {


        memmove16(copy_dst + 16, copy_src + 16);
      }
    }
  }
  ;
  if (s->meta_block_remaining_len <= 0) {

    s->state = BROTLI_STATE_METABLOCK_DONE;
    goto saveStateAndReturn;
  } else {
    goto CommandBegin;
  }
CommandPostWrapCopy:
  {
    int wrap_guard = s->ringbuffer_size - pos;
    while (--i >= 0) {
      s->ringbuffer[pos] =
          s->ringbuffer[(pos - s->distance_code) & s->ringbuffer_mask];
      ++pos;
      if ((__builtin_expect(--wrap_guard == 0, 0))) {
        s->state = BROTLI_STATE_COMMAND_POST_WRITE_2;
        goto saveStateAndReturn;
      }
    }
  }
  if (s->meta_block_remaining_len <= 0) {

    s->state = BROTLI_STATE_METABLOCK_DONE;
    goto saveStateAndReturn;
  } else {
    goto CommandBegin;
  }

saveStateAndReturn:
  s->pos = pos;
  s->loop_counter = i;
  return result;
}



static BrotliDecoderErrorCode ProcessCommands(
    BrotliDecoderStateInternal* s) {
  return ProcessCommandsInternal(0, s);
}

static BrotliDecoderErrorCode SafeProcessCommands(
    BrotliDecoderStateInternal* s) {
  return ProcessCommandsInternal(1, s);
}

BrotliDecoderResult BrotliDecoderDecompress(
    size_t encoded_size, const uint8_t* encoded_buffer, size_t* decoded_size,
    uint8_t* decoded_buffer) {
  BrotliDecoderStateInternal s;
  BrotliDecoderResult result;
  size_t total_out = 0;
  size_t available_in = encoded_size;
  const uint8_t* next_in = encoded_buffer;
  size_t available_out = *decoded_size;
  uint8_t* next_out = decoded_buffer;
  if (!BrotliDecoderStateInit(&s, 0, 0, 0)) {
    return BROTLI_DECODER_RESULT_ERROR;
  }
  result = BrotliDecoderDecompressStream(
      &s, &available_in, &next_in, &available_out, &next_out, &total_out);
  *decoded_size = total_out;
  BrotliDecoderStateCleanup(&s);
  if (result != BROTLI_DECODER_RESULT_SUCCESS) {
    result = BROTLI_DECODER_RESULT_ERROR;
  }
  return result;
}
# 2069 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c"
BrotliDecoderResult BrotliDecoderDecompressStream(
    BrotliDecoderStateInternal* s, size_t* available_in, const uint8_t** next_in,
    size_t* available_out, uint8_t** next_out, size_t* total_out) {
  BrotliDecoderErrorCode result = BROTLI_DECODER_SUCCESS;
  BrotliBitReader* br = &s->br;

  if (total_out) {
    *total_out = s->partial_pos_out;
  }

  if ((int)s->error_code < 0) {
    return BROTLI_DECODER_RESULT_ERROR;
  }
  if (*available_out && (!next_out || !*next_out)) {
    return SaveErrorCode(
        s, ((void)(0), BROTLI_DECODER_ERROR_INVALID_ARGUMENTS));
  }
  if (!*available_out) next_out = 0;
  if (s->buffer_length == 0) {
    br->avail_in = *available_in;
    br->next_in = *next_in;
  } else {



    result = BROTLI_DECODER_NEEDS_MORE_INPUT;
    br->next_in = &s->buffer.u8[0];
  }

  for (;;) {
    if (result != BROTLI_DECODER_SUCCESS) {

      if (result == BROTLI_DECODER_NEEDS_MORE_INPUT) {
        if (s->ringbuffer != 0) {
          BrotliDecoderErrorCode intermediate_result = WriteRingBuffer(s,
              available_out, next_out, total_out, 1);

          if ((int)intermediate_result < 0) {
            result = intermediate_result;
            break;
          }
        }
        if (s->buffer_length != 0) {
          if (br->avail_in == 0) {



            s->buffer_length = 0;

            result = BROTLI_DECODER_SUCCESS;
            br->avail_in = *available_in;
            br->next_in = *next_in;
            continue;
          } else if (*available_in != 0) {


            result = BROTLI_DECODER_SUCCESS;
            s->buffer.u8[s->buffer_length] = **next_in;
            s->buffer_length++;
            br->avail_in = s->buffer_length;
            (*next_in)++;
            (*available_in)--;

            continue;
          }

          break;
        } else {

          *next_in = br->next_in;
          *available_in = br->avail_in;
          while (*available_in) {
            s->buffer.u8[s->buffer_length] = **next_in;
            s->buffer_length++;
            (*next_in)++;
            (*available_in)--;
          }
          break;
        }

      }



      if (s->buffer_length != 0) {


        s->buffer_length = 0;
      } else {



        BrotliBitReaderUnload(br);
        *available_in = br->avail_in;
        *next_in = br->next_in;
      }
      break;
    }
    switch (s->state) {
      case BROTLI_STATE_UNINITED:

        if (!BrotliWarmupBitReader(br)) {
          result = BROTLI_DECODER_NEEDS_MORE_INPUT;
          break;
        }

        result = DecodeWindowBits(s, br);
        if (result != BROTLI_DECODER_SUCCESS) {
          break;
        }
        if (s->large_window) {
          s->state = BROTLI_STATE_LARGE_WINDOW_BITS;
          break;
        }
        s->state = BROTLI_STATE_INITIALIZE;
        break;

      case BROTLI_STATE_LARGE_WINDOW_BITS:
        if (!BrotliSafeReadBits(br, 6, &s->window_bits)) {
          result = BROTLI_DECODER_NEEDS_MORE_INPUT;
          break;
        }
        if (s->window_bits < 10 ||
            s->window_bits > 30) {
          result = ((void)(0), BROTLI_DECODER_ERROR_FORMAT_WINDOW_BITS);
          break;
        }
        s->state = BROTLI_STATE_INITIALIZE;


      case BROTLI_STATE_INITIALIZE:
        ;

        s->max_backward_distance = (1 << s->window_bits) - 16;


        s->block_type_trees = (HuffmanCode*)s->alloc_func(s->memory_manager_opaque, sizeof(HuffmanCode) * 3 * (632 + 396))

                                                                           ;
        if (s->block_type_trees == 0) {
          result = ((void)(0), BROTLI_DECODER_ERROR_ALLOC_BLOCK_TYPE_TREES);
          break;
        }
        s->block_len_trees =
            s->block_type_trees + 3 * 632;

        s->state = BROTLI_STATE_METABLOCK_BEGIN;


      case BROTLI_STATE_METABLOCK_BEGIN:
        BrotliDecoderStateMetablockBegin(s);
        ;
        s->state = BROTLI_STATE_METABLOCK_HEADER;


      case BROTLI_STATE_METABLOCK_HEADER:
        result = DecodeMetaBlockLength(s, br);
        if (result != BROTLI_DECODER_SUCCESS) {
          break;
        }
        ;
        ;
        ;
        ;
        if (s->is_metadata || s->is_uncompressed) {
          if (!BrotliJumpToByteBoundary(br)) {
            result = ((void)(0), BROTLI_DECODER_ERROR_FORMAT_PADDING_1);
            break;
          }
        }
        if (s->is_metadata) {
          s->state = BROTLI_STATE_METADATA;
          break;
        }
        if (s->meta_block_remaining_len == 0) {
          s->state = BROTLI_STATE_METABLOCK_DONE;
          break;
        }
        BrotliCalculateRingBufferSize(s);
        if (s->is_uncompressed) {
          s->state = BROTLI_STATE_UNCOMPRESSED;
          break;
        }
        s->state = BROTLI_STATE_BEFORE_COMPRESSED_METABLOCK_HEADER;


      case BROTLI_STATE_BEFORE_COMPRESSED_METABLOCK_HEADER: {
        BrotliMetablockHeaderArena* h = &s->arena.header;
        s->loop_counter = 0;

        h->sub_loop_counter = 0;

        h->symbol_lists =
            &h->symbols_lists_array[15 + 1];
        h->substate_huffman = BROTLI_STATE_HUFFMAN_NONE;
        h->substate_tree_group = BROTLI_STATE_TREE_GROUP_NONE;
        h->substate_context_map = BROTLI_STATE_CONTEXT_MAP_NONE;
        s->state = BROTLI_STATE_HUFFMAN_CODE_0;
      }


      case BROTLI_STATE_HUFFMAN_CODE_0:
        if (s->loop_counter >= 3) {
          s->state = BROTLI_STATE_METABLOCK_HEADER_2;
          break;
        }

        result = DecodeVarLenUint8(s, br, &s->num_block_types[s->loop_counter]);
        if (result != BROTLI_DECODER_SUCCESS) {
          break;
        }
        s->num_block_types[s->loop_counter]++;
        ;
        if (s->num_block_types[s->loop_counter] < 2) {
          s->loop_counter++;
          break;
        }
        s->state = BROTLI_STATE_HUFFMAN_CODE_1;


      case BROTLI_STATE_HUFFMAN_CODE_1: {
        uint32_t alphabet_size = s->num_block_types[s->loop_counter] + 2;
        int tree_offset = s->loop_counter * 632;
        result = ReadHuffmanCode(alphabet_size, alphabet_size,
            &s->block_type_trees[tree_offset], 0, s);
        if (result != BROTLI_DECODER_SUCCESS) break;
        s->state = BROTLI_STATE_HUFFMAN_CODE_2;
      }


      case BROTLI_STATE_HUFFMAN_CODE_2: {
        uint32_t alphabet_size = 26;
        int tree_offset = s->loop_counter * 396;
        result = ReadHuffmanCode(alphabet_size, alphabet_size,
            &s->block_len_trees[tree_offset], 0, s);
        if (result != BROTLI_DECODER_SUCCESS) break;
        s->state = BROTLI_STATE_HUFFMAN_CODE_3;
      }


      case BROTLI_STATE_HUFFMAN_CODE_3: {
        int tree_offset = s->loop_counter * 396;
        if (!SafeReadBlockLength(s, &s->block_length[s->loop_counter],
            &s->block_len_trees[tree_offset], br)) {
          result = BROTLI_DECODER_NEEDS_MORE_INPUT;
          break;
        }
        ;
        s->loop_counter++;
        s->state = BROTLI_STATE_HUFFMAN_CODE_0;
        break;
      }

      case BROTLI_STATE_UNCOMPRESSED: {
        result = CopyUncompressedBlockToOutput(
            available_out, next_out, total_out, s);
        if (result != BROTLI_DECODER_SUCCESS) {
          break;
        }
        s->state = BROTLI_STATE_METABLOCK_DONE;
        break;
      }

      case BROTLI_STATE_METADATA:
        for (; s->meta_block_remaining_len > 0; --s->meta_block_remaining_len) {
          uint32_t bits;

          if (!BrotliSafeReadBits(br, 8, &bits)) {
            result = BROTLI_DECODER_NEEDS_MORE_INPUT;
            break;
          }
        }
        if (result == BROTLI_DECODER_SUCCESS) {
          s->state = BROTLI_STATE_METABLOCK_DONE;
        }
        break;

      case BROTLI_STATE_METABLOCK_HEADER_2: {
        uint32_t bits;
        if (!BrotliSafeReadBits(br, 6, &bits)) {
          result = BROTLI_DECODER_NEEDS_MORE_INPUT;
          break;
        }
        s->distance_postfix_bits = bits & BitMask(2);
        bits >>= 2;
        s->num_direct_distance_codes = bits << s->distance_postfix_bits;
        ;
        ;
        s->context_modes =
            (uint8_t*)s->alloc_func(s->memory_manager_opaque, (size_t)s->num_block_types[0]);
        if (s->context_modes == 0) {
          result = ((void)(0), BROTLI_DECODER_ERROR_ALLOC_CONTEXT_MODES);
          break;
        }
        s->loop_counter = 0;
        s->state = BROTLI_STATE_CONTEXT_MODES;
      }


      case BROTLI_STATE_CONTEXT_MODES:
        result = ReadContextModes(s);
        if (result != BROTLI_DECODER_SUCCESS) {
          break;
        }
        s->state = BROTLI_STATE_CONTEXT_MAP_1;


      case BROTLI_STATE_CONTEXT_MAP_1:
        result = DecodeContextMap(
            s->num_block_types[0] << 6,
            &s->num_literal_htrees, &s->context_map, s);
        if (result != BROTLI_DECODER_SUCCESS) {
          break;
        }
        DetectTrivialLiteralBlockTypes(s);
        s->state = BROTLI_STATE_CONTEXT_MAP_2;


      case BROTLI_STATE_CONTEXT_MAP_2: {
        uint32_t npostfix = s->distance_postfix_bits;
        uint32_t ndirect = s->num_direct_distance_codes;
        uint32_t distance_alphabet_size_max = ( 16 + (ndirect) + ((24U) << ((npostfix) + 1)))
                                                        ;
        uint32_t distance_alphabet_size_limit = distance_alphabet_size_max;
        int allocation_success = 1;
        if (s->large_window) {
          BrotliDistanceCodeLimit limit = BrotliCalculateDistanceCodeLimit(
              0x7FFFFFFC, npostfix, ndirect);
          distance_alphabet_size_max = ( 16 + (ndirect) + ((62U) << ((npostfix) + 1)))
                                                                ;
          distance_alphabet_size_limit = limit.max_alphabet_size;
        }
        result = DecodeContextMap(
            s->num_block_types[2] << 2,
            &s->num_dist_htrees, &s->dist_context_map, s);
        if (result != BROTLI_DECODER_SUCCESS) {
          break;
        }
        allocation_success &= BrotliDecoderHuffmanTreeGroupInit(
            s, &s->literal_hgroup, 256,
            256, s->num_literal_htrees);
        allocation_success &= BrotliDecoderHuffmanTreeGroupInit(
            s, &s->insert_copy_hgroup, 704,
            704, s->num_block_types[1]);
        allocation_success &= BrotliDecoderHuffmanTreeGroupInit(
            s, &s->distance_hgroup, distance_alphabet_size_max,
            distance_alphabet_size_limit, s->num_dist_htrees);
        if (!allocation_success) {
          return SaveErrorCode(s,
              ((void)(0), BROTLI_DECODER_ERROR_ALLOC_TREE_GROUPS));
        }
        s->loop_counter = 0;
        s->state = BROTLI_STATE_TREE_GROUP;
      }


      case BROTLI_STATE_TREE_GROUP: {
        HuffmanTreeGroup* hgroup = 0;
        switch (s->loop_counter) {
          case 0: hgroup = &s->literal_hgroup; break;
          case 1: hgroup = &s->insert_copy_hgroup; break;
          case 2: hgroup = &s->distance_hgroup; break;
          default: return SaveErrorCode(s, ((void)(0), BROTLI_DECODER_ERROR_UNREACHABLE)
                                               );
        }
        result = HuffmanTreeGroupDecode(hgroup, s);
        if (result != BROTLI_DECODER_SUCCESS) break;
        s->loop_counter++;
        if (s->loop_counter < 3) {
          break;
        }
        s->state = BROTLI_STATE_BEFORE_COMPRESSED_METABLOCK_BODY;
      }


      case BROTLI_STATE_BEFORE_COMPRESSED_METABLOCK_BODY:
        PrepareLiteralDecoding(s);
        s->dist_context_map_slice = s->dist_context_map;
        s->htree_command = s->insert_copy_hgroup.htrees[0];
        if (!BrotliEnsureRingBuffer(s)) {
          result = ((void)(0), BROTLI_DECODER_ERROR_ALLOC_RING_BUFFER_2);
          break;
        }
        CalculateDistanceLut(s);
        s->state = BROTLI_STATE_COMMAND_BEGIN;


      case BROTLI_STATE_COMMAND_BEGIN:

      case BROTLI_STATE_COMMAND_INNER:

      case BROTLI_STATE_COMMAND_POST_DECODE_LITERALS:

      case BROTLI_STATE_COMMAND_POST_WRAP_COPY:
        result = ProcessCommands(s);
        if (result == BROTLI_DECODER_NEEDS_MORE_INPUT) {
          result = SafeProcessCommands(s);
        }
        break;

      case BROTLI_STATE_COMMAND_INNER_WRITE:

      case BROTLI_STATE_COMMAND_POST_WRITE_1:

      case BROTLI_STATE_COMMAND_POST_WRITE_2:
        result = WriteRingBuffer(
            s, available_out, next_out, total_out, 0);
        if (result != BROTLI_DECODER_SUCCESS) {
          break;
        }
        WrapRingBuffer(s);
        if (s->ringbuffer_size == 1 << s->window_bits) {
          s->max_distance = s->max_backward_distance;
        }
        if (s->state == BROTLI_STATE_COMMAND_POST_WRITE_1) {
          if (s->meta_block_remaining_len == 0) {

            s->state = BROTLI_STATE_METABLOCK_DONE;
          } else {
            s->state = BROTLI_STATE_COMMAND_BEGIN;
          }
          break;
        } else if (s->state == BROTLI_STATE_COMMAND_POST_WRITE_2) {
          s->state = BROTLI_STATE_COMMAND_POST_WRAP_COPY;
        } else {
          if (s->loop_counter == 0) {
            if (s->meta_block_remaining_len == 0) {
              s->state = BROTLI_STATE_METABLOCK_DONE;
            } else {
              s->state = BROTLI_STATE_COMMAND_POST_DECODE_LITERALS;
            }
            break;
          }
          s->state = BROTLI_STATE_COMMAND_INNER;
        }
        break;

      case BROTLI_STATE_METABLOCK_DONE:
        if (s->meta_block_remaining_len < 0) {
          result = ((void)(0), BROTLI_DECODER_ERROR_FORMAT_BLOCK_LENGTH_2);
          break;
        }
        BrotliDecoderStateCleanupAfterMetablock(s);
        if (!s->is_last_metablock) {
          s->state = BROTLI_STATE_METABLOCK_BEGIN;
          break;
        }
        if (!BrotliJumpToByteBoundary(br)) {
          result = ((void)(0), BROTLI_DECODER_ERROR_FORMAT_PADDING_2);
          break;
        }
        if (s->buffer_length == 0) {
          BrotliBitReaderUnload(br);
          *available_in = br->avail_in;
          *next_in = br->next_in;
        }
        s->state = BROTLI_STATE_DONE;


      case BROTLI_STATE_DONE:
        if (s->ringbuffer != 0) {
          result = WriteRingBuffer(
              s, available_out, next_out, total_out, 1);
          if (result != BROTLI_DECODER_SUCCESS) {
            break;
          }
        }
        return SaveErrorCode(s, result);
    }
  }
  return SaveErrorCode(s, result);
}

int BrotliDecoderHasMoreOutput(const BrotliDecoderStateInternal* s) {

  if ((int)s->error_code < 0) {
    return 0;
  }
  return (!!(s->ringbuffer != 0 && UnwrittenBytes(s, 0) != 0) ? 1 : 0)
                                                                 ;
}

const uint8_t* BrotliDecoderTakeOutput(BrotliDecoderStateInternal* s, size_t* size) {
  uint8_t* result = 0;
  size_t available_out = *size ? *size : 1u << 24;
  size_t requested_out = available_out;
  BrotliDecoderErrorCode status;
  if ((s->ringbuffer == 0) || ((int)s->error_code < 0)) {
    *size = 0;
    return 0;
  }
  WrapRingBuffer(s);
  status = WriteRingBuffer(s, &available_out, &result, 0, 1);

  if (status == BROTLI_DECODER_SUCCESS ||
      status == BROTLI_DECODER_NEEDS_MORE_OUTPUT) {
    *size = requested_out - available_out;
  } else {


    if ((int)status < 0) SaveErrorCode(s, status);
    *size = 0;
    result = 0;
  }
  return result;
}

int BrotliDecoderIsUsed(const BrotliDecoderStateInternal* s) {
  return (!!(s->state != BROTLI_STATE_UNINITED || BrotliGetAvailableBits(&s->br) != 0) ? 1 : 0)
                                          ;
}

int BrotliDecoderIsFinished(const BrotliDecoderStateInternal* s) {
  return (!!(s->state == BROTLI_STATE_DONE) ? 1 : 0) &&
      !BrotliDecoderHasMoreOutput(s);
}

BrotliDecoderErrorCode BrotliDecoderGetErrorCode(const BrotliDecoderStateInternal* s) {
  return (BrotliDecoderErrorCode)s->error_code;
}

const char* BrotliDecoderErrorString(BrotliDecoderErrorCode c) {
  switch (c) {



    case BROTLI_DECODER_NO_ERROR: return "NO_ERROR"; case BROTLI_DECODER_SUCCESS: return "SUCCESS"; case BROTLI_DECODER_NEEDS_MORE_INPUT: return "NEEDS_MORE_INPUT"; case BROTLI_DECODER_NEEDS_MORE_OUTPUT: return "NEEDS_MORE_OUTPUT"; case BROTLI_DECODER_ERROR_FORMAT_EXUBERANT_NIBBLE: return "EXUBERANT_NIBBLE"; case BROTLI_DECODER_ERROR_FORMAT_RESERVED: return "RESERVED"; case BROTLI_DECODER_ERROR_FORMAT_EXUBERANT_META_NIBBLE: return "EXUBERANT_META_NIBBLE"; case BROTLI_DECODER_ERROR_FORMAT_SIMPLE_HUFFMAN_ALPHABET: return "SIMPLE_HUFFMAN_ALPHABET"; case BROTLI_DECODER_ERROR_FORMAT_SIMPLE_HUFFMAN_SAME: return "SIMPLE_HUFFMAN_SAME"; case BROTLI_DECODER_ERROR_FORMAT_CL_SPACE: return "CL_SPACE"; case BROTLI_DECODER_ERROR_FORMAT_HUFFMAN_SPACE: return "HUFFMAN_SPACE"; case BROTLI_DECODER_ERROR_FORMAT_CONTEXT_MAP_REPEAT: return "CONTEXT_MAP_REPEAT"; case BROTLI_DECODER_ERROR_FORMAT_BLOCK_LENGTH_1: return "BLOCK_LENGTH_1"; case BROTLI_DECODER_ERROR_FORMAT_BLOCK_LENGTH_2: return "BLOCK_LENGTH_2"; case BROTLI_DECODER_ERROR_FORMAT_TRANSFORM: return "TRANSFORM"; case BROTLI_DECODER_ERROR_FORMAT_DICTIONARY: return "DICTIONARY"; case BROTLI_DECODER_ERROR_FORMAT_WINDOW_BITS: return "WINDOW_BITS"; case BROTLI_DECODER_ERROR_FORMAT_PADDING_1: return "PADDING_1"; case BROTLI_DECODER_ERROR_FORMAT_PADDING_2: return "PADDING_2"; case BROTLI_DECODER_ERROR_FORMAT_DISTANCE: return "DISTANCE"; case BROTLI_DECODER_ERROR_DICTIONARY_NOT_SET: return "DICTIONARY_NOT_SET"; case BROTLI_DECODER_ERROR_INVALID_ARGUMENTS: return "INVALID_ARGUMENTS"; case BROTLI_DECODER_ERROR_ALLOC_CONTEXT_MODES: return "CONTEXT_MODES"; case BROTLI_DECODER_ERROR_ALLOC_TREE_GROUPS: return "TREE_GROUPS"; case BROTLI_DECODER_ERROR_ALLOC_CONTEXT_MAP: return "CONTEXT_MAP"; case BROTLI_DECODER_ERROR_ALLOC_RING_BUFFER_1: return "RING_BUFFER_1"; case BROTLI_DECODER_ERROR_ALLOC_RING_BUFFER_2: return "RING_BUFFER_2"; case BROTLI_DECODER_ERROR_ALLOC_BLOCK_TYPE_TREES: return "BLOCK_TYPE_TREES"; case BROTLI_DECODER_ERROR_UNREACHABLE: return "UNREACHABLE";


    default: return "INVALID";
  }
}

uint32_t BrotliDecoderVersion() {
  return 0x1000009;
}
# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c"






# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/decode.h" 1
# 15 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/decode.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/port.h" 1
# 16 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/decode.h" 2
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
# 17 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/decode.h" 2
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/decode.h"
typedef struct BrotliDecoderStateStruct BrotliDecoderState;





typedef enum {

  BROTLI_DECODER_RESULT_ERROR = 0,

  BROTLI_DECODER_RESULT_SUCCESS = 1,

  BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT = 2,

  BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT = 3
} BrotliDecoderResult;
# 112 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/decode.h"
typedef enum {



  BROTLI_DECODER_NO_ERROR = 0 , BROTLI_DECODER_SUCCESS = 1 , BROTLI_DECODER_NEEDS_MORE_INPUT = 2 , BROTLI_DECODER_NEEDS_MORE_OUTPUT = 3 , BROTLI_DECODER_ERROR_FORMAT_EXUBERANT_NIBBLE = -1 , BROTLI_DECODER_ERROR_FORMAT_RESERVED = -2 , BROTLI_DECODER_ERROR_FORMAT_EXUBERANT_META_NIBBLE = -3 , BROTLI_DECODER_ERROR_FORMAT_SIMPLE_HUFFMAN_ALPHABET = -4 , BROTLI_DECODER_ERROR_FORMAT_SIMPLE_HUFFMAN_SAME = -5 , BROTLI_DECODER_ERROR_FORMAT_CL_SPACE = -6 , BROTLI_DECODER_ERROR_FORMAT_HUFFMAN_SPACE = -7 , BROTLI_DECODER_ERROR_FORMAT_CONTEXT_MAP_REPEAT = -8 , BROTLI_DECODER_ERROR_FORMAT_BLOCK_LENGTH_1 = -9 , BROTLI_DECODER_ERROR_FORMAT_BLOCK_LENGTH_2 = -10 , BROTLI_DECODER_ERROR_FORMAT_TRANSFORM = -11 , BROTLI_DECODER_ERROR_FORMAT_DICTIONARY = -12 , BROTLI_DECODER_ERROR_FORMAT_WINDOW_BITS = -13 , BROTLI_DECODER_ERROR_FORMAT_PADDING_1 = -14 , BROTLI_DECODER_ERROR_FORMAT_PADDING_2 = -15 , BROTLI_DECODER_ERROR_FORMAT_DISTANCE = -16 , BROTLI_DECODER_ERROR_DICTIONARY_NOT_SET = -19 , BROTLI_DECODER_ERROR_INVALID_ARGUMENTS = -20 , BROTLI_DECODER_ERROR_ALLOC_CONTEXT_MODES = -21 , BROTLI_DECODER_ERROR_ALLOC_TREE_GROUPS = -22 , BROTLI_DECODER_ERROR_ALLOC_CONTEXT_MAP = -25 , BROTLI_DECODER_ERROR_ALLOC_RING_BUFFER_1 = -26 , BROTLI_DECODER_ERROR_ALLOC_RING_BUFFER_2 = -27 , BROTLI_DECODER_ERROR_ALLOC_BLOCK_TYPE_TREES = -30 , BROTLI_DECODER_ERROR_UNREACHABLE = -31
} BrotliDecoderErrorCode;
# 131 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/decode.h"
typedef enum BrotliDecoderParameter {






  BROTLI_DECODER_PARAM_DISABLE_RING_BUFFER_REALLOCATION = 0,



  BROTLI_DECODER_PARAM_LARGE_WINDOW = 1
} BrotliDecoderParameter;
# 154 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/decode.h"
 int BrotliDecoderSetParameter(
    BrotliDecoderState* state, BrotliDecoderParameter param, uint32_t value);
# 175 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/decode.h"
 BrotliDecoderState* BrotliDecoderCreateInstance(
    brotli_alloc_func alloc_func, brotli_free_func free_func, void* opaque);






 void BrotliDecoderDestroyInstance(BrotliDecoderState* state);
# 202 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/decode.h"
 BrotliDecoderResult BrotliDecoderDecompress(
    size_t encoded_size,
    const uint8_t encoded_buffer[(encoded_size)],
    size_t* decoded_size,
    uint8_t decoded_buffer[(*decoded_size)]);
# 246 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/decode.h"
 BrotliDecoderResult BrotliDecoderDecompressStream(
  BrotliDecoderState* state, size_t* available_in, const uint8_t** next_in,
  size_t* available_out, uint8_t** next_out, size_t* total_out);
# 257 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/decode.h"
 int BrotliDecoderHasMoreOutput(
    const BrotliDecoderState* state);
# 288 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/decode.h"
 const uint8_t* BrotliDecoderTakeOutput(
    BrotliDecoderState* state, size_t* size);
# 301 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/decode.h"
 int BrotliDecoderIsUsed(const BrotliDecoderState* state);
# 311 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/decode.h"
 int BrotliDecoderIsFinished(
    const BrotliDecoderState* state);
# 325 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/decode.h"
 BrotliDecoderErrorCode BrotliDecoderGetErrorCode(
    const BrotliDecoderState* state);




 const char* BrotliDecoderErrorString(BrotliDecoderErrorCode c);






 uint32_t BrotliDecoderVersion(void);
# 8 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 10 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 11 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/constants.h" 1
# 15 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/constants.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/./platform.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/./platform.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/./platform.h" 2
# 340 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/./platform.h"
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
# 502 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/./platform.h"
static inline void BrotliRBit(void) { }
# 516 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/./platform.h"
static inline double brotli_min_double (double a, double b) { return a < b ? a : b; } static inline double brotli_max_double (double a, double b) { return a > b ? a : b; } static inline float brotli_min_float (float a, float b) { return a < b ? a : b; } static inline float brotli_max_float (float a, float b) { return a > b ? a : b; } static inline int brotli_min_int (int a, int b) { return a < b ? a : b; } static inline int brotli_max_int (int a, int b) { return a > b ? a : b; }
static inline size_t brotli_min_size_t (size_t a, size_t b) { return a < b ? a : b; } static inline size_t brotli_max_size_t (size_t a, size_t b) { return a > b ? a : b; } static inline uint32_t brotli_min_uint32_t (uint32_t a, uint32_t b) { return a < b ? a : b; } static inline uint32_t brotli_max_uint32_t (uint32_t a, uint32_t b) { return a > b ? a : b; } static inline uint8_t brotli_min_uint8_t (uint8_t a, uint8_t b) { return a < b ? a : b; } static inline uint8_t brotli_max_uint8_t (uint8_t a, uint8_t b) { return a > b ? a : b; }
# 559 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/./platform.h"
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
# 16 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/constants.h" 2
# 105 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/constants.h"
typedef struct BrotliDistanceCodeLimit {
  uint32_t max_alphabet_size;
  uint32_t max_distance;
} BrotliDistanceCodeLimit;
# 127 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/constants.h"
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
# 13 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/context.h" 1
# 94 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/context.h"
typedef enum ContextType {
  CONTEXT_LSB6 = 0,
  CONTEXT_MSB6 = 1,
  CONTEXT_UTF8 = 2,
  CONTEXT_SIGNED = 3
} ContextType;



 extern const uint8_t _kBrotliContextLookupTable[2048];

typedef const uint8_t* ContextLut;
# 14 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/dictionary.h" 1
# 19 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/dictionary.h"
typedef struct BrotliDictionary {
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/dictionary.h"
  uint8_t size_bits_by_length[32];


  uint32_t offsets_by_length[32];


  size_t data_size;




  const uint8_t* data;
} BrotliDictionary;

 const BrotliDictionary* BrotliGetDictionary(void);
# 55 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/dictionary.h"
 void BrotliSetDictionaryData(const uint8_t* data);
# 15 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/platform.h" 1
# 16 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/transform.h" 1
# 18 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/transform.h"
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
# 75 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/transform.h"
 const BrotliTransforms* BrotliGetTransforms(void);

 int BrotliTransformDictionaryWord(
    uint8_t* dst, const uint8_t* word, int len,
    const BrotliTransforms* transforms, int transform_idx);
# 17 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/../common/version.h" 1
# 18 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./bit_reader.h" 1
# 12 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./bit_reader.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 13 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./bit_reader.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/constants.h" 1
# 15 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./bit_reader.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/platform.h" 1
# 16 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./bit_reader.h" 2
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./bit_reader.h"
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
# 155 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./bit_reader.h"
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
# 19 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./huffman.h" 1
# 38 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./huffman.h"
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
# 91 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./huffman.h"
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
# 20 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./prefix.h" 1
# 16 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./prefix.h"
typedef struct CmdLutElement {
  uint8_t insert_len_extra_bits;
  uint8_t copy_len_extra_bits;
  int8_t distance_code;
  uint8_t context;
  uint16_t insert_len_offset;
  uint16_t copy_len_offset;
} CmdLutElement;

static const CmdLutElement kCmdLut[704] = {
  { 0x00, 0x00, 0, 0x00, 0x0000, 0x0002 },
  { 0x00, 0x00, 0, 0x01, 0x0000, 0x0003 },
  { 0x00, 0x00, 0, 0x02, 0x0000, 0x0004 },
  { 0x00, 0x00, 0, 0x03, 0x0000, 0x0005 },
  { 0x00, 0x00, 0, 0x03, 0x0000, 0x0006 },
  { 0x00, 0x00, 0, 0x03, 0x0000, 0x0007 },
  { 0x00, 0x00, 0, 0x03, 0x0000, 0x0008 },
  { 0x00, 0x00, 0, 0x03, 0x0000, 0x0009 },
  { 0x00, 0x00, 0, 0x00, 0x0001, 0x0002 },
  { 0x00, 0x00, 0, 0x01, 0x0001, 0x0003 },
  { 0x00, 0x00, 0, 0x02, 0x0001, 0x0004 },
  { 0x00, 0x00, 0, 0x03, 0x0001, 0x0005 },
  { 0x00, 0x00, 0, 0x03, 0x0001, 0x0006 },
  { 0x00, 0x00, 0, 0x03, 0x0001, 0x0007 },
  { 0x00, 0x00, 0, 0x03, 0x0001, 0x0008 },
  { 0x00, 0x00, 0, 0x03, 0x0001, 0x0009 },
  { 0x00, 0x00, 0, 0x00, 0x0002, 0x0002 },
  { 0x00, 0x00, 0, 0x01, 0x0002, 0x0003 },
  { 0x00, 0x00, 0, 0x02, 0x0002, 0x0004 },
  { 0x00, 0x00, 0, 0x03, 0x0002, 0x0005 },
  { 0x00, 0x00, 0, 0x03, 0x0002, 0x0006 },
  { 0x00, 0x00, 0, 0x03, 0x0002, 0x0007 },
  { 0x00, 0x00, 0, 0x03, 0x0002, 0x0008 },
  { 0x00, 0x00, 0, 0x03, 0x0002, 0x0009 },
  { 0x00, 0x00, 0, 0x00, 0x0003, 0x0002 },
  { 0x00, 0x00, 0, 0x01, 0x0003, 0x0003 },
  { 0x00, 0x00, 0, 0x02, 0x0003, 0x0004 },
  { 0x00, 0x00, 0, 0x03, 0x0003, 0x0005 },
  { 0x00, 0x00, 0, 0x03, 0x0003, 0x0006 },
  { 0x00, 0x00, 0, 0x03, 0x0003, 0x0007 },
  { 0x00, 0x00, 0, 0x03, 0x0003, 0x0008 },
  { 0x00, 0x00, 0, 0x03, 0x0003, 0x0009 },
  { 0x00, 0x00, 0, 0x00, 0x0004, 0x0002 },
  { 0x00, 0x00, 0, 0x01, 0x0004, 0x0003 },
  { 0x00, 0x00, 0, 0x02, 0x0004, 0x0004 },
  { 0x00, 0x00, 0, 0x03, 0x0004, 0x0005 },
  { 0x00, 0x00, 0, 0x03, 0x0004, 0x0006 },
  { 0x00, 0x00, 0, 0x03, 0x0004, 0x0007 },
  { 0x00, 0x00, 0, 0x03, 0x0004, 0x0008 },
  { 0x00, 0x00, 0, 0x03, 0x0004, 0x0009 },
  { 0x00, 0x00, 0, 0x00, 0x0005, 0x0002 },
  { 0x00, 0x00, 0, 0x01, 0x0005, 0x0003 },
  { 0x00, 0x00, 0, 0x02, 0x0005, 0x0004 },
  { 0x00, 0x00, 0, 0x03, 0x0005, 0x0005 },
  { 0x00, 0x00, 0, 0x03, 0x0005, 0x0006 },
  { 0x00, 0x00, 0, 0x03, 0x0005, 0x0007 },
  { 0x00, 0x00, 0, 0x03, 0x0005, 0x0008 },
  { 0x00, 0x00, 0, 0x03, 0x0005, 0x0009 },
  { 0x01, 0x00, 0, 0x00, 0x0006, 0x0002 },
  { 0x01, 0x00, 0, 0x01, 0x0006, 0x0003 },
  { 0x01, 0x00, 0, 0x02, 0x0006, 0x0004 },
  { 0x01, 0x00, 0, 0x03, 0x0006, 0x0005 },
  { 0x01, 0x00, 0, 0x03, 0x0006, 0x0006 },
  { 0x01, 0x00, 0, 0x03, 0x0006, 0x0007 },
  { 0x01, 0x00, 0, 0x03, 0x0006, 0x0008 },
  { 0x01, 0x00, 0, 0x03, 0x0006, 0x0009 },
  { 0x01, 0x00, 0, 0x00, 0x0008, 0x0002 },
  { 0x01, 0x00, 0, 0x01, 0x0008, 0x0003 },
  { 0x01, 0x00, 0, 0x02, 0x0008, 0x0004 },
  { 0x01, 0x00, 0, 0x03, 0x0008, 0x0005 },
  { 0x01, 0x00, 0, 0x03, 0x0008, 0x0006 },
  { 0x01, 0x00, 0, 0x03, 0x0008, 0x0007 },
  { 0x01, 0x00, 0, 0x03, 0x0008, 0x0008 },
  { 0x01, 0x00, 0, 0x03, 0x0008, 0x0009 },
  { 0x00, 0x01, 0, 0x03, 0x0000, 0x000a },
  { 0x00, 0x01, 0, 0x03, 0x0000, 0x000c },
  { 0x00, 0x02, 0, 0x03, 0x0000, 0x000e },
  { 0x00, 0x02, 0, 0x03, 0x0000, 0x0012 },
  { 0x00, 0x03, 0, 0x03, 0x0000, 0x0016 },
  { 0x00, 0x03, 0, 0x03, 0x0000, 0x001e },
  { 0x00, 0x04, 0, 0x03, 0x0000, 0x0026 },
  { 0x00, 0x04, 0, 0x03, 0x0000, 0x0036 },
  { 0x00, 0x01, 0, 0x03, 0x0001, 0x000a },
  { 0x00, 0x01, 0, 0x03, 0x0001, 0x000c },
  { 0x00, 0x02, 0, 0x03, 0x0001, 0x000e },
  { 0x00, 0x02, 0, 0x03, 0x0001, 0x0012 },
  { 0x00, 0x03, 0, 0x03, 0x0001, 0x0016 },
  { 0x00, 0x03, 0, 0x03, 0x0001, 0x001e },
  { 0x00, 0x04, 0, 0x03, 0x0001, 0x0026 },
  { 0x00, 0x04, 0, 0x03, 0x0001, 0x0036 },
  { 0x00, 0x01, 0, 0x03, 0x0002, 0x000a },
  { 0x00, 0x01, 0, 0x03, 0x0002, 0x000c },
  { 0x00, 0x02, 0, 0x03, 0x0002, 0x000e },
  { 0x00, 0x02, 0, 0x03, 0x0002, 0x0012 },
  { 0x00, 0x03, 0, 0x03, 0x0002, 0x0016 },
  { 0x00, 0x03, 0, 0x03, 0x0002, 0x001e },
  { 0x00, 0x04, 0, 0x03, 0x0002, 0x0026 },
  { 0x00, 0x04, 0, 0x03, 0x0002, 0x0036 },
  { 0x00, 0x01, 0, 0x03, 0x0003, 0x000a },
  { 0x00, 0x01, 0, 0x03, 0x0003, 0x000c },
  { 0x00, 0x02, 0, 0x03, 0x0003, 0x000e },
  { 0x00, 0x02, 0, 0x03, 0x0003, 0x0012 },
  { 0x00, 0x03, 0, 0x03, 0x0003, 0x0016 },
  { 0x00, 0x03, 0, 0x03, 0x0003, 0x001e },
  { 0x00, 0x04, 0, 0x03, 0x0003, 0x0026 },
  { 0x00, 0x04, 0, 0x03, 0x0003, 0x0036 },
  { 0x00, 0x01, 0, 0x03, 0x0004, 0x000a },
  { 0x00, 0x01, 0, 0x03, 0x0004, 0x000c },
  { 0x00, 0x02, 0, 0x03, 0x0004, 0x000e },
  { 0x00, 0x02, 0, 0x03, 0x0004, 0x0012 },
  { 0x00, 0x03, 0, 0x03, 0x0004, 0x0016 },
  { 0x00, 0x03, 0, 0x03, 0x0004, 0x001e },
  { 0x00, 0x04, 0, 0x03, 0x0004, 0x0026 },
  { 0x00, 0x04, 0, 0x03, 0x0004, 0x0036 },
  { 0x00, 0x01, 0, 0x03, 0x0005, 0x000a },
  { 0x00, 0x01, 0, 0x03, 0x0005, 0x000c },
  { 0x00, 0x02, 0, 0x03, 0x0005, 0x000e },
  { 0x00, 0x02, 0, 0x03, 0x0005, 0x0012 },
  { 0x00, 0x03, 0, 0x03, 0x0005, 0x0016 },
  { 0x00, 0x03, 0, 0x03, 0x0005, 0x001e },
  { 0x00, 0x04, 0, 0x03, 0x0005, 0x0026 },
  { 0x00, 0x04, 0, 0x03, 0x0005, 0x0036 },
  { 0x01, 0x01, 0, 0x03, 0x0006, 0x000a },
  { 0x01, 0x01, 0, 0x03, 0x0006, 0x000c },
  { 0x01, 0x02, 0, 0x03, 0x0006, 0x000e },
  { 0x01, 0x02, 0, 0x03, 0x0006, 0x0012 },
  { 0x01, 0x03, 0, 0x03, 0x0006, 0x0016 },
  { 0x01, 0x03, 0, 0x03, 0x0006, 0x001e },
  { 0x01, 0x04, 0, 0x03, 0x0006, 0x0026 },
  { 0x01, 0x04, 0, 0x03, 0x0006, 0x0036 },
  { 0x01, 0x01, 0, 0x03, 0x0008, 0x000a },
  { 0x01, 0x01, 0, 0x03, 0x0008, 0x000c },
  { 0x01, 0x02, 0, 0x03, 0x0008, 0x000e },
  { 0x01, 0x02, 0, 0x03, 0x0008, 0x0012 },
  { 0x01, 0x03, 0, 0x03, 0x0008, 0x0016 },
  { 0x01, 0x03, 0, 0x03, 0x0008, 0x001e },
  { 0x01, 0x04, 0, 0x03, 0x0008, 0x0026 },
  { 0x01, 0x04, 0, 0x03, 0x0008, 0x0036 },
  { 0x00, 0x00, -1, 0x00, 0x0000, 0x0002 },
  { 0x00, 0x00, -1, 0x01, 0x0000, 0x0003 },
  { 0x00, 0x00, -1, 0x02, 0x0000, 0x0004 },
  { 0x00, 0x00, -1, 0x03, 0x0000, 0x0005 },
  { 0x00, 0x00, -1, 0x03, 0x0000, 0x0006 },
  { 0x00, 0x00, -1, 0x03, 0x0000, 0x0007 },
  { 0x00, 0x00, -1, 0x03, 0x0000, 0x0008 },
  { 0x00, 0x00, -1, 0x03, 0x0000, 0x0009 },
  { 0x00, 0x00, -1, 0x00, 0x0001, 0x0002 },
  { 0x00, 0x00, -1, 0x01, 0x0001, 0x0003 },
  { 0x00, 0x00, -1, 0x02, 0x0001, 0x0004 },
  { 0x00, 0x00, -1, 0x03, 0x0001, 0x0005 },
  { 0x00, 0x00, -1, 0x03, 0x0001, 0x0006 },
  { 0x00, 0x00, -1, 0x03, 0x0001, 0x0007 },
  { 0x00, 0x00, -1, 0x03, 0x0001, 0x0008 },
  { 0x00, 0x00, -1, 0x03, 0x0001, 0x0009 },
  { 0x00, 0x00, -1, 0x00, 0x0002, 0x0002 },
  { 0x00, 0x00, -1, 0x01, 0x0002, 0x0003 },
  { 0x00, 0x00, -1, 0x02, 0x0002, 0x0004 },
  { 0x00, 0x00, -1, 0x03, 0x0002, 0x0005 },
  { 0x00, 0x00, -1, 0x03, 0x0002, 0x0006 },
  { 0x00, 0x00, -1, 0x03, 0x0002, 0x0007 },
  { 0x00, 0x00, -1, 0x03, 0x0002, 0x0008 },
  { 0x00, 0x00, -1, 0x03, 0x0002, 0x0009 },
  { 0x00, 0x00, -1, 0x00, 0x0003, 0x0002 },
  { 0x00, 0x00, -1, 0x01, 0x0003, 0x0003 },
  { 0x00, 0x00, -1, 0x02, 0x0003, 0x0004 },
  { 0x00, 0x00, -1, 0x03, 0x0003, 0x0005 },
  { 0x00, 0x00, -1, 0x03, 0x0003, 0x0006 },
  { 0x00, 0x00, -1, 0x03, 0x0003, 0x0007 },
  { 0x00, 0x00, -1, 0x03, 0x0003, 0x0008 },
  { 0x00, 0x00, -1, 0x03, 0x0003, 0x0009 },
  { 0x00, 0x00, -1, 0x00, 0x0004, 0x0002 },
  { 0x00, 0x00, -1, 0x01, 0x0004, 0x0003 },
  { 0x00, 0x00, -1, 0x02, 0x0004, 0x0004 },
  { 0x00, 0x00, -1, 0x03, 0x0004, 0x0005 },
  { 0x00, 0x00, -1, 0x03, 0x0004, 0x0006 },
  { 0x00, 0x00, -1, 0x03, 0x0004, 0x0007 },
  { 0x00, 0x00, -1, 0x03, 0x0004, 0x0008 },
  { 0x00, 0x00, -1, 0x03, 0x0004, 0x0009 },
  { 0x00, 0x00, -1, 0x00, 0x0005, 0x0002 },
  { 0x00, 0x00, -1, 0x01, 0x0005, 0x0003 },
  { 0x00, 0x00, -1, 0x02, 0x0005, 0x0004 },
  { 0x00, 0x00, -1, 0x03, 0x0005, 0x0005 },
  { 0x00, 0x00, -1, 0x03, 0x0005, 0x0006 },
  { 0x00, 0x00, -1, 0x03, 0x0005, 0x0007 },
  { 0x00, 0x00, -1, 0x03, 0x0005, 0x0008 },
  { 0x00, 0x00, -1, 0x03, 0x0005, 0x0009 },
  { 0x01, 0x00, -1, 0x00, 0x0006, 0x0002 },
  { 0x01, 0x00, -1, 0x01, 0x0006, 0x0003 },
  { 0x01, 0x00, -1, 0x02, 0x0006, 0x0004 },
  { 0x01, 0x00, -1, 0x03, 0x0006, 0x0005 },
  { 0x01, 0x00, -1, 0x03, 0x0006, 0x0006 },
  { 0x01, 0x00, -1, 0x03, 0x0006, 0x0007 },
  { 0x01, 0x00, -1, 0x03, 0x0006, 0x0008 },
  { 0x01, 0x00, -1, 0x03, 0x0006, 0x0009 },
  { 0x01, 0x00, -1, 0x00, 0x0008, 0x0002 },
  { 0x01, 0x00, -1, 0x01, 0x0008, 0x0003 },
  { 0x01, 0x00, -1, 0x02, 0x0008, 0x0004 },
  { 0x01, 0x00, -1, 0x03, 0x0008, 0x0005 },
  { 0x01, 0x00, -1, 0x03, 0x0008, 0x0006 },
  { 0x01, 0x00, -1, 0x03, 0x0008, 0x0007 },
  { 0x01, 0x00, -1, 0x03, 0x0008, 0x0008 },
  { 0x01, 0x00, -1, 0x03, 0x0008, 0x0009 },
  { 0x00, 0x01, -1, 0x03, 0x0000, 0x000a },
  { 0x00, 0x01, -1, 0x03, 0x0000, 0x000c },
  { 0x00, 0x02, -1, 0x03, 0x0000, 0x000e },
  { 0x00, 0x02, -1, 0x03, 0x0000, 0x0012 },
  { 0x00, 0x03, -1, 0x03, 0x0000, 0x0016 },
  { 0x00, 0x03, -1, 0x03, 0x0000, 0x001e },
  { 0x00, 0x04, -1, 0x03, 0x0000, 0x0026 },
  { 0x00, 0x04, -1, 0x03, 0x0000, 0x0036 },
  { 0x00, 0x01, -1, 0x03, 0x0001, 0x000a },
  { 0x00, 0x01, -1, 0x03, 0x0001, 0x000c },
  { 0x00, 0x02, -1, 0x03, 0x0001, 0x000e },
  { 0x00, 0x02, -1, 0x03, 0x0001, 0x0012 },
  { 0x00, 0x03, -1, 0x03, 0x0001, 0x0016 },
  { 0x00, 0x03, -1, 0x03, 0x0001, 0x001e },
  { 0x00, 0x04, -1, 0x03, 0x0001, 0x0026 },
  { 0x00, 0x04, -1, 0x03, 0x0001, 0x0036 },
  { 0x00, 0x01, -1, 0x03, 0x0002, 0x000a },
  { 0x00, 0x01, -1, 0x03, 0x0002, 0x000c },
  { 0x00, 0x02, -1, 0x03, 0x0002, 0x000e },
  { 0x00, 0x02, -1, 0x03, 0x0002, 0x0012 },
  { 0x00, 0x03, -1, 0x03, 0x0002, 0x0016 },
  { 0x00, 0x03, -1, 0x03, 0x0002, 0x001e },
  { 0x00, 0x04, -1, 0x03, 0x0002, 0x0026 },
  { 0x00, 0x04, -1, 0x03, 0x0002, 0x0036 },
  { 0x00, 0x01, -1, 0x03, 0x0003, 0x000a },
  { 0x00, 0x01, -1, 0x03, 0x0003, 0x000c },
  { 0x00, 0x02, -1, 0x03, 0x0003, 0x000e },
  { 0x00, 0x02, -1, 0x03, 0x0003, 0x0012 },
  { 0x00, 0x03, -1, 0x03, 0x0003, 0x0016 },
  { 0x00, 0x03, -1, 0x03, 0x0003, 0x001e },
  { 0x00, 0x04, -1, 0x03, 0x0003, 0x0026 },
  { 0x00, 0x04, -1, 0x03, 0x0003, 0x0036 },
  { 0x00, 0x01, -1, 0x03, 0x0004, 0x000a },
  { 0x00, 0x01, -1, 0x03, 0x0004, 0x000c },
  { 0x00, 0x02, -1, 0x03, 0x0004, 0x000e },
  { 0x00, 0x02, -1, 0x03, 0x0004, 0x0012 },
  { 0x00, 0x03, -1, 0x03, 0x0004, 0x0016 },
  { 0x00, 0x03, -1, 0x03, 0x0004, 0x001e },
  { 0x00, 0x04, -1, 0x03, 0x0004, 0x0026 },
  { 0x00, 0x04, -1, 0x03, 0x0004, 0x0036 },
  { 0x00, 0x01, -1, 0x03, 0x0005, 0x000a },
  { 0x00, 0x01, -1, 0x03, 0x0005, 0x000c },
  { 0x00, 0x02, -1, 0x03, 0x0005, 0x000e },
  { 0x00, 0x02, -1, 0x03, 0x0005, 0x0012 },
  { 0x00, 0x03, -1, 0x03, 0x0005, 0x0016 },
  { 0x00, 0x03, -1, 0x03, 0x0005, 0x001e },
  { 0x00, 0x04, -1, 0x03, 0x0005, 0x0026 },
  { 0x00, 0x04, -1, 0x03, 0x0005, 0x0036 },
  { 0x01, 0x01, -1, 0x03, 0x0006, 0x000a },
  { 0x01, 0x01, -1, 0x03, 0x0006, 0x000c },
  { 0x01, 0x02, -1, 0x03, 0x0006, 0x000e },
  { 0x01, 0x02, -1, 0x03, 0x0006, 0x0012 },
  { 0x01, 0x03, -1, 0x03, 0x0006, 0x0016 },
  { 0x01, 0x03, -1, 0x03, 0x0006, 0x001e },
  { 0x01, 0x04, -1, 0x03, 0x0006, 0x0026 },
  { 0x01, 0x04, -1, 0x03, 0x0006, 0x0036 },
  { 0x01, 0x01, -1, 0x03, 0x0008, 0x000a },
  { 0x01, 0x01, -1, 0x03, 0x0008, 0x000c },
  { 0x01, 0x02, -1, 0x03, 0x0008, 0x000e },
  { 0x01, 0x02, -1, 0x03, 0x0008, 0x0012 },
  { 0x01, 0x03, -1, 0x03, 0x0008, 0x0016 },
  { 0x01, 0x03, -1, 0x03, 0x0008, 0x001e },
  { 0x01, 0x04, -1, 0x03, 0x0008, 0x0026 },
  { 0x01, 0x04, -1, 0x03, 0x0008, 0x0036 },
  { 0x02, 0x00, -1, 0x00, 0x000a, 0x0002 },
  { 0x02, 0x00, -1, 0x01, 0x000a, 0x0003 },
  { 0x02, 0x00, -1, 0x02, 0x000a, 0x0004 },
  { 0x02, 0x00, -1, 0x03, 0x000a, 0x0005 },
  { 0x02, 0x00, -1, 0x03, 0x000a, 0x0006 },
  { 0x02, 0x00, -1, 0x03, 0x000a, 0x0007 },
  { 0x02, 0x00, -1, 0x03, 0x000a, 0x0008 },
  { 0x02, 0x00, -1, 0x03, 0x000a, 0x0009 },
  { 0x02, 0x00, -1, 0x00, 0x000e, 0x0002 },
  { 0x02, 0x00, -1, 0x01, 0x000e, 0x0003 },
  { 0x02, 0x00, -1, 0x02, 0x000e, 0x0004 },
  { 0x02, 0x00, -1, 0x03, 0x000e, 0x0005 },
  { 0x02, 0x00, -1, 0x03, 0x000e, 0x0006 },
  { 0x02, 0x00, -1, 0x03, 0x000e, 0x0007 },
  { 0x02, 0x00, -1, 0x03, 0x000e, 0x0008 },
  { 0x02, 0x00, -1, 0x03, 0x000e, 0x0009 },
  { 0x03, 0x00, -1, 0x00, 0x0012, 0x0002 },
  { 0x03, 0x00, -1, 0x01, 0x0012, 0x0003 },
  { 0x03, 0x00, -1, 0x02, 0x0012, 0x0004 },
  { 0x03, 0x00, -1, 0x03, 0x0012, 0x0005 },
  { 0x03, 0x00, -1, 0x03, 0x0012, 0x0006 },
  { 0x03, 0x00, -1, 0x03, 0x0012, 0x0007 },
  { 0x03, 0x00, -1, 0x03, 0x0012, 0x0008 },
  { 0x03, 0x00, -1, 0x03, 0x0012, 0x0009 },
  { 0x03, 0x00, -1, 0x00, 0x001a, 0x0002 },
  { 0x03, 0x00, -1, 0x01, 0x001a, 0x0003 },
  { 0x03, 0x00, -1, 0x02, 0x001a, 0x0004 },
  { 0x03, 0x00, -1, 0x03, 0x001a, 0x0005 },
  { 0x03, 0x00, -1, 0x03, 0x001a, 0x0006 },
  { 0x03, 0x00, -1, 0x03, 0x001a, 0x0007 },
  { 0x03, 0x00, -1, 0x03, 0x001a, 0x0008 },
  { 0x03, 0x00, -1, 0x03, 0x001a, 0x0009 },
  { 0x04, 0x00, -1, 0x00, 0x0022, 0x0002 },
  { 0x04, 0x00, -1, 0x01, 0x0022, 0x0003 },
  { 0x04, 0x00, -1, 0x02, 0x0022, 0x0004 },
  { 0x04, 0x00, -1, 0x03, 0x0022, 0x0005 },
  { 0x04, 0x00, -1, 0x03, 0x0022, 0x0006 },
  { 0x04, 0x00, -1, 0x03, 0x0022, 0x0007 },
  { 0x04, 0x00, -1, 0x03, 0x0022, 0x0008 },
  { 0x04, 0x00, -1, 0x03, 0x0022, 0x0009 },
  { 0x04, 0x00, -1, 0x00, 0x0032, 0x0002 },
  { 0x04, 0x00, -1, 0x01, 0x0032, 0x0003 },
  { 0x04, 0x00, -1, 0x02, 0x0032, 0x0004 },
  { 0x04, 0x00, -1, 0x03, 0x0032, 0x0005 },
  { 0x04, 0x00, -1, 0x03, 0x0032, 0x0006 },
  { 0x04, 0x00, -1, 0x03, 0x0032, 0x0007 },
  { 0x04, 0x00, -1, 0x03, 0x0032, 0x0008 },
  { 0x04, 0x00, -1, 0x03, 0x0032, 0x0009 },
  { 0x05, 0x00, -1, 0x00, 0x0042, 0x0002 },
  { 0x05, 0x00, -1, 0x01, 0x0042, 0x0003 },
  { 0x05, 0x00, -1, 0x02, 0x0042, 0x0004 },
  { 0x05, 0x00, -1, 0x03, 0x0042, 0x0005 },
  { 0x05, 0x00, -1, 0x03, 0x0042, 0x0006 },
  { 0x05, 0x00, -1, 0x03, 0x0042, 0x0007 },
  { 0x05, 0x00, -1, 0x03, 0x0042, 0x0008 },
  { 0x05, 0x00, -1, 0x03, 0x0042, 0x0009 },
  { 0x05, 0x00, -1, 0x00, 0x0062, 0x0002 },
  { 0x05, 0x00, -1, 0x01, 0x0062, 0x0003 },
  { 0x05, 0x00, -1, 0x02, 0x0062, 0x0004 },
  { 0x05, 0x00, -1, 0x03, 0x0062, 0x0005 },
  { 0x05, 0x00, -1, 0x03, 0x0062, 0x0006 },
  { 0x05, 0x00, -1, 0x03, 0x0062, 0x0007 },
  { 0x05, 0x00, -1, 0x03, 0x0062, 0x0008 },
  { 0x05, 0x00, -1, 0x03, 0x0062, 0x0009 },
  { 0x02, 0x01, -1, 0x03, 0x000a, 0x000a },
  { 0x02, 0x01, -1, 0x03, 0x000a, 0x000c },
  { 0x02, 0x02, -1, 0x03, 0x000a, 0x000e },
  { 0x02, 0x02, -1, 0x03, 0x000a, 0x0012 },
  { 0x02, 0x03, -1, 0x03, 0x000a, 0x0016 },
  { 0x02, 0x03, -1, 0x03, 0x000a, 0x001e },
  { 0x02, 0x04, -1, 0x03, 0x000a, 0x0026 },
  { 0x02, 0x04, -1, 0x03, 0x000a, 0x0036 },
  { 0x02, 0x01, -1, 0x03, 0x000e, 0x000a },
  { 0x02, 0x01, -1, 0x03, 0x000e, 0x000c },
  { 0x02, 0x02, -1, 0x03, 0x000e, 0x000e },
  { 0x02, 0x02, -1, 0x03, 0x000e, 0x0012 },
  { 0x02, 0x03, -1, 0x03, 0x000e, 0x0016 },
  { 0x02, 0x03, -1, 0x03, 0x000e, 0x001e },
  { 0x02, 0x04, -1, 0x03, 0x000e, 0x0026 },
  { 0x02, 0x04, -1, 0x03, 0x000e, 0x0036 },
  { 0x03, 0x01, -1, 0x03, 0x0012, 0x000a },
  { 0x03, 0x01, -1, 0x03, 0x0012, 0x000c },
  { 0x03, 0x02, -1, 0x03, 0x0012, 0x000e },
  { 0x03, 0x02, -1, 0x03, 0x0012, 0x0012 },
  { 0x03, 0x03, -1, 0x03, 0x0012, 0x0016 },
  { 0x03, 0x03, -1, 0x03, 0x0012, 0x001e },
  { 0x03, 0x04, -1, 0x03, 0x0012, 0x0026 },
  { 0x03, 0x04, -1, 0x03, 0x0012, 0x0036 },
  { 0x03, 0x01, -1, 0x03, 0x001a, 0x000a },
  { 0x03, 0x01, -1, 0x03, 0x001a, 0x000c },
  { 0x03, 0x02, -1, 0x03, 0x001a, 0x000e },
  { 0x03, 0x02, -1, 0x03, 0x001a, 0x0012 },
  { 0x03, 0x03, -1, 0x03, 0x001a, 0x0016 },
  { 0x03, 0x03, -1, 0x03, 0x001a, 0x001e },
  { 0x03, 0x04, -1, 0x03, 0x001a, 0x0026 },
  { 0x03, 0x04, -1, 0x03, 0x001a, 0x0036 },
  { 0x04, 0x01, -1, 0x03, 0x0022, 0x000a },
  { 0x04, 0x01, -1, 0x03, 0x0022, 0x000c },
  { 0x04, 0x02, -1, 0x03, 0x0022, 0x000e },
  { 0x04, 0x02, -1, 0x03, 0x0022, 0x0012 },
  { 0x04, 0x03, -1, 0x03, 0x0022, 0x0016 },
  { 0x04, 0x03, -1, 0x03, 0x0022, 0x001e },
  { 0x04, 0x04, -1, 0x03, 0x0022, 0x0026 },
  { 0x04, 0x04, -1, 0x03, 0x0022, 0x0036 },
  { 0x04, 0x01, -1, 0x03, 0x0032, 0x000a },
  { 0x04, 0x01, -1, 0x03, 0x0032, 0x000c },
  { 0x04, 0x02, -1, 0x03, 0x0032, 0x000e },
  { 0x04, 0x02, -1, 0x03, 0x0032, 0x0012 },
  { 0x04, 0x03, -1, 0x03, 0x0032, 0x0016 },
  { 0x04, 0x03, -1, 0x03, 0x0032, 0x001e },
  { 0x04, 0x04, -1, 0x03, 0x0032, 0x0026 },
  { 0x04, 0x04, -1, 0x03, 0x0032, 0x0036 },
  { 0x05, 0x01, -1, 0x03, 0x0042, 0x000a },
  { 0x05, 0x01, -1, 0x03, 0x0042, 0x000c },
  { 0x05, 0x02, -1, 0x03, 0x0042, 0x000e },
  { 0x05, 0x02, -1, 0x03, 0x0042, 0x0012 },
  { 0x05, 0x03, -1, 0x03, 0x0042, 0x0016 },
  { 0x05, 0x03, -1, 0x03, 0x0042, 0x001e },
  { 0x05, 0x04, -1, 0x03, 0x0042, 0x0026 },
  { 0x05, 0x04, -1, 0x03, 0x0042, 0x0036 },
  { 0x05, 0x01, -1, 0x03, 0x0062, 0x000a },
  { 0x05, 0x01, -1, 0x03, 0x0062, 0x000c },
  { 0x05, 0x02, -1, 0x03, 0x0062, 0x000e },
  { 0x05, 0x02, -1, 0x03, 0x0062, 0x0012 },
  { 0x05, 0x03, -1, 0x03, 0x0062, 0x0016 },
  { 0x05, 0x03, -1, 0x03, 0x0062, 0x001e },
  { 0x05, 0x04, -1, 0x03, 0x0062, 0x0026 },
  { 0x05, 0x04, -1, 0x03, 0x0062, 0x0036 },
  { 0x00, 0x05, -1, 0x03, 0x0000, 0x0046 },
  { 0x00, 0x05, -1, 0x03, 0x0000, 0x0066 },
  { 0x00, 0x06, -1, 0x03, 0x0000, 0x0086 },
  { 0x00, 0x07, -1, 0x03, 0x0000, 0x00c6 },
  { 0x00, 0x08, -1, 0x03, 0x0000, 0x0146 },
  { 0x00, 0x09, -1, 0x03, 0x0000, 0x0246 },
  { 0x00, 0x0a, -1, 0x03, 0x0000, 0x0446 },
  { 0x00, 0x18, -1, 0x03, 0x0000, 0x0846 },
  { 0x00, 0x05, -1, 0x03, 0x0001, 0x0046 },
  { 0x00, 0x05, -1, 0x03, 0x0001, 0x0066 },
  { 0x00, 0x06, -1, 0x03, 0x0001, 0x0086 },
  { 0x00, 0x07, -1, 0x03, 0x0001, 0x00c6 },
  { 0x00, 0x08, -1, 0x03, 0x0001, 0x0146 },
  { 0x00, 0x09, -1, 0x03, 0x0001, 0x0246 },
  { 0x00, 0x0a, -1, 0x03, 0x0001, 0x0446 },
  { 0x00, 0x18, -1, 0x03, 0x0001, 0x0846 },
  { 0x00, 0x05, -1, 0x03, 0x0002, 0x0046 },
  { 0x00, 0x05, -1, 0x03, 0x0002, 0x0066 },
  { 0x00, 0x06, -1, 0x03, 0x0002, 0x0086 },
  { 0x00, 0x07, -1, 0x03, 0x0002, 0x00c6 },
  { 0x00, 0x08, -1, 0x03, 0x0002, 0x0146 },
  { 0x00, 0x09, -1, 0x03, 0x0002, 0x0246 },
  { 0x00, 0x0a, -1, 0x03, 0x0002, 0x0446 },
  { 0x00, 0x18, -1, 0x03, 0x0002, 0x0846 },
  { 0x00, 0x05, -1, 0x03, 0x0003, 0x0046 },
  { 0x00, 0x05, -1, 0x03, 0x0003, 0x0066 },
  { 0x00, 0x06, -1, 0x03, 0x0003, 0x0086 },
  { 0x00, 0x07, -1, 0x03, 0x0003, 0x00c6 },
  { 0x00, 0x08, -1, 0x03, 0x0003, 0x0146 },
  { 0x00, 0x09, -1, 0x03, 0x0003, 0x0246 },
  { 0x00, 0x0a, -1, 0x03, 0x0003, 0x0446 },
  { 0x00, 0x18, -1, 0x03, 0x0003, 0x0846 },
  { 0x00, 0x05, -1, 0x03, 0x0004, 0x0046 },
  { 0x00, 0x05, -1, 0x03, 0x0004, 0x0066 },
  { 0x00, 0x06, -1, 0x03, 0x0004, 0x0086 },
  { 0x00, 0x07, -1, 0x03, 0x0004, 0x00c6 },
  { 0x00, 0x08, -1, 0x03, 0x0004, 0x0146 },
  { 0x00, 0x09, -1, 0x03, 0x0004, 0x0246 },
  { 0x00, 0x0a, -1, 0x03, 0x0004, 0x0446 },
  { 0x00, 0x18, -1, 0x03, 0x0004, 0x0846 },
  { 0x00, 0x05, -1, 0x03, 0x0005, 0x0046 },
  { 0x00, 0x05, -1, 0x03, 0x0005, 0x0066 },
  { 0x00, 0x06, -1, 0x03, 0x0005, 0x0086 },
  { 0x00, 0x07, -1, 0x03, 0x0005, 0x00c6 },
  { 0x00, 0x08, -1, 0x03, 0x0005, 0x0146 },
  { 0x00, 0x09, -1, 0x03, 0x0005, 0x0246 },
  { 0x00, 0x0a, -1, 0x03, 0x0005, 0x0446 },
  { 0x00, 0x18, -1, 0x03, 0x0005, 0x0846 },
  { 0x01, 0x05, -1, 0x03, 0x0006, 0x0046 },
  { 0x01, 0x05, -1, 0x03, 0x0006, 0x0066 },
  { 0x01, 0x06, -1, 0x03, 0x0006, 0x0086 },
  { 0x01, 0x07, -1, 0x03, 0x0006, 0x00c6 },
  { 0x01, 0x08, -1, 0x03, 0x0006, 0x0146 },
  { 0x01, 0x09, -1, 0x03, 0x0006, 0x0246 },
  { 0x01, 0x0a, -1, 0x03, 0x0006, 0x0446 },
  { 0x01, 0x18, -1, 0x03, 0x0006, 0x0846 },
  { 0x01, 0x05, -1, 0x03, 0x0008, 0x0046 },
  { 0x01, 0x05, -1, 0x03, 0x0008, 0x0066 },
  { 0x01, 0x06, -1, 0x03, 0x0008, 0x0086 },
  { 0x01, 0x07, -1, 0x03, 0x0008, 0x00c6 },
  { 0x01, 0x08, -1, 0x03, 0x0008, 0x0146 },
  { 0x01, 0x09, -1, 0x03, 0x0008, 0x0246 },
  { 0x01, 0x0a, -1, 0x03, 0x0008, 0x0446 },
  { 0x01, 0x18, -1, 0x03, 0x0008, 0x0846 },
  { 0x06, 0x00, -1, 0x00, 0x0082, 0x0002 },
  { 0x06, 0x00, -1, 0x01, 0x0082, 0x0003 },
  { 0x06, 0x00, -1, 0x02, 0x0082, 0x0004 },
  { 0x06, 0x00, -1, 0x03, 0x0082, 0x0005 },
  { 0x06, 0x00, -1, 0x03, 0x0082, 0x0006 },
  { 0x06, 0x00, -1, 0x03, 0x0082, 0x0007 },
  { 0x06, 0x00, -1, 0x03, 0x0082, 0x0008 },
  { 0x06, 0x00, -1, 0x03, 0x0082, 0x0009 },
  { 0x07, 0x00, -1, 0x00, 0x00c2, 0x0002 },
  { 0x07, 0x00, -1, 0x01, 0x00c2, 0x0003 },
  { 0x07, 0x00, -1, 0x02, 0x00c2, 0x0004 },
  { 0x07, 0x00, -1, 0x03, 0x00c2, 0x0005 },
  { 0x07, 0x00, -1, 0x03, 0x00c2, 0x0006 },
  { 0x07, 0x00, -1, 0x03, 0x00c2, 0x0007 },
  { 0x07, 0x00, -1, 0x03, 0x00c2, 0x0008 },
  { 0x07, 0x00, -1, 0x03, 0x00c2, 0x0009 },
  { 0x08, 0x00, -1, 0x00, 0x0142, 0x0002 },
  { 0x08, 0x00, -1, 0x01, 0x0142, 0x0003 },
  { 0x08, 0x00, -1, 0x02, 0x0142, 0x0004 },
  { 0x08, 0x00, -1, 0x03, 0x0142, 0x0005 },
  { 0x08, 0x00, -1, 0x03, 0x0142, 0x0006 },
  { 0x08, 0x00, -1, 0x03, 0x0142, 0x0007 },
  { 0x08, 0x00, -1, 0x03, 0x0142, 0x0008 },
  { 0x08, 0x00, -1, 0x03, 0x0142, 0x0009 },
  { 0x09, 0x00, -1, 0x00, 0x0242, 0x0002 },
  { 0x09, 0x00, -1, 0x01, 0x0242, 0x0003 },
  { 0x09, 0x00, -1, 0x02, 0x0242, 0x0004 },
  { 0x09, 0x00, -1, 0x03, 0x0242, 0x0005 },
  { 0x09, 0x00, -1, 0x03, 0x0242, 0x0006 },
  { 0x09, 0x00, -1, 0x03, 0x0242, 0x0007 },
  { 0x09, 0x00, -1, 0x03, 0x0242, 0x0008 },
  { 0x09, 0x00, -1, 0x03, 0x0242, 0x0009 },
  { 0x0a, 0x00, -1, 0x00, 0x0442, 0x0002 },
  { 0x0a, 0x00, -1, 0x01, 0x0442, 0x0003 },
  { 0x0a, 0x00, -1, 0x02, 0x0442, 0x0004 },
  { 0x0a, 0x00, -1, 0x03, 0x0442, 0x0005 },
  { 0x0a, 0x00, -1, 0x03, 0x0442, 0x0006 },
  { 0x0a, 0x00, -1, 0x03, 0x0442, 0x0007 },
  { 0x0a, 0x00, -1, 0x03, 0x0442, 0x0008 },
  { 0x0a, 0x00, -1, 0x03, 0x0442, 0x0009 },
  { 0x0c, 0x00, -1, 0x00, 0x0842, 0x0002 },
  { 0x0c, 0x00, -1, 0x01, 0x0842, 0x0003 },
  { 0x0c, 0x00, -1, 0x02, 0x0842, 0x0004 },
  { 0x0c, 0x00, -1, 0x03, 0x0842, 0x0005 },
  { 0x0c, 0x00, -1, 0x03, 0x0842, 0x0006 },
  { 0x0c, 0x00, -1, 0x03, 0x0842, 0x0007 },
  { 0x0c, 0x00, -1, 0x03, 0x0842, 0x0008 },
  { 0x0c, 0x00, -1, 0x03, 0x0842, 0x0009 },
  { 0x0e, 0x00, -1, 0x00, 0x1842, 0x0002 },
  { 0x0e, 0x00, -1, 0x01, 0x1842, 0x0003 },
  { 0x0e, 0x00, -1, 0x02, 0x1842, 0x0004 },
  { 0x0e, 0x00, -1, 0x03, 0x1842, 0x0005 },
  { 0x0e, 0x00, -1, 0x03, 0x1842, 0x0006 },
  { 0x0e, 0x00, -1, 0x03, 0x1842, 0x0007 },
  { 0x0e, 0x00, -1, 0x03, 0x1842, 0x0008 },
  { 0x0e, 0x00, -1, 0x03, 0x1842, 0x0009 },
  { 0x18, 0x00, -1, 0x00, 0x5842, 0x0002 },
  { 0x18, 0x00, -1, 0x01, 0x5842, 0x0003 },
  { 0x18, 0x00, -1, 0x02, 0x5842, 0x0004 },
  { 0x18, 0x00, -1, 0x03, 0x5842, 0x0005 },
  { 0x18, 0x00, -1, 0x03, 0x5842, 0x0006 },
  { 0x18, 0x00, -1, 0x03, 0x5842, 0x0007 },
  { 0x18, 0x00, -1, 0x03, 0x5842, 0x0008 },
  { 0x18, 0x00, -1, 0x03, 0x5842, 0x0009 },
  { 0x02, 0x05, -1, 0x03, 0x000a, 0x0046 },
  { 0x02, 0x05, -1, 0x03, 0x000a, 0x0066 },
  { 0x02, 0x06, -1, 0x03, 0x000a, 0x0086 },
  { 0x02, 0x07, -1, 0x03, 0x000a, 0x00c6 },
  { 0x02, 0x08, -1, 0x03, 0x000a, 0x0146 },
  { 0x02, 0x09, -1, 0x03, 0x000a, 0x0246 },
  { 0x02, 0x0a, -1, 0x03, 0x000a, 0x0446 },
  { 0x02, 0x18, -1, 0x03, 0x000a, 0x0846 },
  { 0x02, 0x05, -1, 0x03, 0x000e, 0x0046 },
  { 0x02, 0x05, -1, 0x03, 0x000e, 0x0066 },
  { 0x02, 0x06, -1, 0x03, 0x000e, 0x0086 },
  { 0x02, 0x07, -1, 0x03, 0x000e, 0x00c6 },
  { 0x02, 0x08, -1, 0x03, 0x000e, 0x0146 },
  { 0x02, 0x09, -1, 0x03, 0x000e, 0x0246 },
  { 0x02, 0x0a, -1, 0x03, 0x000e, 0x0446 },
  { 0x02, 0x18, -1, 0x03, 0x000e, 0x0846 },
  { 0x03, 0x05, -1, 0x03, 0x0012, 0x0046 },
  { 0x03, 0x05, -1, 0x03, 0x0012, 0x0066 },
  { 0x03, 0x06, -1, 0x03, 0x0012, 0x0086 },
  { 0x03, 0x07, -1, 0x03, 0x0012, 0x00c6 },
  { 0x03, 0x08, -1, 0x03, 0x0012, 0x0146 },
  { 0x03, 0x09, -1, 0x03, 0x0012, 0x0246 },
  { 0x03, 0x0a, -1, 0x03, 0x0012, 0x0446 },
  { 0x03, 0x18, -1, 0x03, 0x0012, 0x0846 },
  { 0x03, 0x05, -1, 0x03, 0x001a, 0x0046 },
  { 0x03, 0x05, -1, 0x03, 0x001a, 0x0066 },
  { 0x03, 0x06, -1, 0x03, 0x001a, 0x0086 },
  { 0x03, 0x07, -1, 0x03, 0x001a, 0x00c6 },
  { 0x03, 0x08, -1, 0x03, 0x001a, 0x0146 },
  { 0x03, 0x09, -1, 0x03, 0x001a, 0x0246 },
  { 0x03, 0x0a, -1, 0x03, 0x001a, 0x0446 },
  { 0x03, 0x18, -1, 0x03, 0x001a, 0x0846 },
  { 0x04, 0x05, -1, 0x03, 0x0022, 0x0046 },
  { 0x04, 0x05, -1, 0x03, 0x0022, 0x0066 },
  { 0x04, 0x06, -1, 0x03, 0x0022, 0x0086 },
  { 0x04, 0x07, -1, 0x03, 0x0022, 0x00c6 },
  { 0x04, 0x08, -1, 0x03, 0x0022, 0x0146 },
  { 0x04, 0x09, -1, 0x03, 0x0022, 0x0246 },
  { 0x04, 0x0a, -1, 0x03, 0x0022, 0x0446 },
  { 0x04, 0x18, -1, 0x03, 0x0022, 0x0846 },
  { 0x04, 0x05, -1, 0x03, 0x0032, 0x0046 },
  { 0x04, 0x05, -1, 0x03, 0x0032, 0x0066 },
  { 0x04, 0x06, -1, 0x03, 0x0032, 0x0086 },
  { 0x04, 0x07, -1, 0x03, 0x0032, 0x00c6 },
  { 0x04, 0x08, -1, 0x03, 0x0032, 0x0146 },
  { 0x04, 0x09, -1, 0x03, 0x0032, 0x0246 },
  { 0x04, 0x0a, -1, 0x03, 0x0032, 0x0446 },
  { 0x04, 0x18, -1, 0x03, 0x0032, 0x0846 },
  { 0x05, 0x05, -1, 0x03, 0x0042, 0x0046 },
  { 0x05, 0x05, -1, 0x03, 0x0042, 0x0066 },
  { 0x05, 0x06, -1, 0x03, 0x0042, 0x0086 },
  { 0x05, 0x07, -1, 0x03, 0x0042, 0x00c6 },
  { 0x05, 0x08, -1, 0x03, 0x0042, 0x0146 },
  { 0x05, 0x09, -1, 0x03, 0x0042, 0x0246 },
  { 0x05, 0x0a, -1, 0x03, 0x0042, 0x0446 },
  { 0x05, 0x18, -1, 0x03, 0x0042, 0x0846 },
  { 0x05, 0x05, -1, 0x03, 0x0062, 0x0046 },
  { 0x05, 0x05, -1, 0x03, 0x0062, 0x0066 },
  { 0x05, 0x06, -1, 0x03, 0x0062, 0x0086 },
  { 0x05, 0x07, -1, 0x03, 0x0062, 0x00c6 },
  { 0x05, 0x08, -1, 0x03, 0x0062, 0x0146 },
  { 0x05, 0x09, -1, 0x03, 0x0062, 0x0246 },
  { 0x05, 0x0a, -1, 0x03, 0x0062, 0x0446 },
  { 0x05, 0x18, -1, 0x03, 0x0062, 0x0846 },
  { 0x06, 0x01, -1, 0x03, 0x0082, 0x000a },
  { 0x06, 0x01, -1, 0x03, 0x0082, 0x000c },
  { 0x06, 0x02, -1, 0x03, 0x0082, 0x000e },
  { 0x06, 0x02, -1, 0x03, 0x0082, 0x0012 },
  { 0x06, 0x03, -1, 0x03, 0x0082, 0x0016 },
  { 0x06, 0x03, -1, 0x03, 0x0082, 0x001e },
  { 0x06, 0x04, -1, 0x03, 0x0082, 0x0026 },
  { 0x06, 0x04, -1, 0x03, 0x0082, 0x0036 },
  { 0x07, 0x01, -1, 0x03, 0x00c2, 0x000a },
  { 0x07, 0x01, -1, 0x03, 0x00c2, 0x000c },
  { 0x07, 0x02, -1, 0x03, 0x00c2, 0x000e },
  { 0x07, 0x02, -1, 0x03, 0x00c2, 0x0012 },
  { 0x07, 0x03, -1, 0x03, 0x00c2, 0x0016 },
  { 0x07, 0x03, -1, 0x03, 0x00c2, 0x001e },
  { 0x07, 0x04, -1, 0x03, 0x00c2, 0x0026 },
  { 0x07, 0x04, -1, 0x03, 0x00c2, 0x0036 },
  { 0x08, 0x01, -1, 0x03, 0x0142, 0x000a },
  { 0x08, 0x01, -1, 0x03, 0x0142, 0x000c },
  { 0x08, 0x02, -1, 0x03, 0x0142, 0x000e },
  { 0x08, 0x02, -1, 0x03, 0x0142, 0x0012 },
  { 0x08, 0x03, -1, 0x03, 0x0142, 0x0016 },
  { 0x08, 0x03, -1, 0x03, 0x0142, 0x001e },
  { 0x08, 0x04, -1, 0x03, 0x0142, 0x0026 },
  { 0x08, 0x04, -1, 0x03, 0x0142, 0x0036 },
  { 0x09, 0x01, -1, 0x03, 0x0242, 0x000a },
  { 0x09, 0x01, -1, 0x03, 0x0242, 0x000c },
  { 0x09, 0x02, -1, 0x03, 0x0242, 0x000e },
  { 0x09, 0x02, -1, 0x03, 0x0242, 0x0012 },
  { 0x09, 0x03, -1, 0x03, 0x0242, 0x0016 },
  { 0x09, 0x03, -1, 0x03, 0x0242, 0x001e },
  { 0x09, 0x04, -1, 0x03, 0x0242, 0x0026 },
  { 0x09, 0x04, -1, 0x03, 0x0242, 0x0036 },
  { 0x0a, 0x01, -1, 0x03, 0x0442, 0x000a },
  { 0x0a, 0x01, -1, 0x03, 0x0442, 0x000c },
  { 0x0a, 0x02, -1, 0x03, 0x0442, 0x000e },
  { 0x0a, 0x02, -1, 0x03, 0x0442, 0x0012 },
  { 0x0a, 0x03, -1, 0x03, 0x0442, 0x0016 },
  { 0x0a, 0x03, -1, 0x03, 0x0442, 0x001e },
  { 0x0a, 0x04, -1, 0x03, 0x0442, 0x0026 },
  { 0x0a, 0x04, -1, 0x03, 0x0442, 0x0036 },
  { 0x0c, 0x01, -1, 0x03, 0x0842, 0x000a },
  { 0x0c, 0x01, -1, 0x03, 0x0842, 0x000c },
  { 0x0c, 0x02, -1, 0x03, 0x0842, 0x000e },
  { 0x0c, 0x02, -1, 0x03, 0x0842, 0x0012 },
  { 0x0c, 0x03, -1, 0x03, 0x0842, 0x0016 },
  { 0x0c, 0x03, -1, 0x03, 0x0842, 0x001e },
  { 0x0c, 0x04, -1, 0x03, 0x0842, 0x0026 },
  { 0x0c, 0x04, -1, 0x03, 0x0842, 0x0036 },
  { 0x0e, 0x01, -1, 0x03, 0x1842, 0x000a },
  { 0x0e, 0x01, -1, 0x03, 0x1842, 0x000c },
  { 0x0e, 0x02, -1, 0x03, 0x1842, 0x000e },
  { 0x0e, 0x02, -1, 0x03, 0x1842, 0x0012 },
  { 0x0e, 0x03, -1, 0x03, 0x1842, 0x0016 },
  { 0x0e, 0x03, -1, 0x03, 0x1842, 0x001e },
  { 0x0e, 0x04, -1, 0x03, 0x1842, 0x0026 },
  { 0x0e, 0x04, -1, 0x03, 0x1842, 0x0036 },
  { 0x18, 0x01, -1, 0x03, 0x5842, 0x000a },
  { 0x18, 0x01, -1, 0x03, 0x5842, 0x000c },
  { 0x18, 0x02, -1, 0x03, 0x5842, 0x000e },
  { 0x18, 0x02, -1, 0x03, 0x5842, 0x0012 },
  { 0x18, 0x03, -1, 0x03, 0x5842, 0x0016 },
  { 0x18, 0x03, -1, 0x03, 0x5842, 0x001e },
  { 0x18, 0x04, -1, 0x03, 0x5842, 0x0026 },
  { 0x18, 0x04, -1, 0x03, 0x5842, 0x0036 },
  { 0x06, 0x05, -1, 0x03, 0x0082, 0x0046 },
  { 0x06, 0x05, -1, 0x03, 0x0082, 0x0066 },
  { 0x06, 0x06, -1, 0x03, 0x0082, 0x0086 },
  { 0x06, 0x07, -1, 0x03, 0x0082, 0x00c6 },
  { 0x06, 0x08, -1, 0x03, 0x0082, 0x0146 },
  { 0x06, 0x09, -1, 0x03, 0x0082, 0x0246 },
  { 0x06, 0x0a, -1, 0x03, 0x0082, 0x0446 },
  { 0x06, 0x18, -1, 0x03, 0x0082, 0x0846 },
  { 0x07, 0x05, -1, 0x03, 0x00c2, 0x0046 },
  { 0x07, 0x05, -1, 0x03, 0x00c2, 0x0066 },
  { 0x07, 0x06, -1, 0x03, 0x00c2, 0x0086 },
  { 0x07, 0x07, -1, 0x03, 0x00c2, 0x00c6 },
  { 0x07, 0x08, -1, 0x03, 0x00c2, 0x0146 },
  { 0x07, 0x09, -1, 0x03, 0x00c2, 0x0246 },
  { 0x07, 0x0a, -1, 0x03, 0x00c2, 0x0446 },
  { 0x07, 0x18, -1, 0x03, 0x00c2, 0x0846 },
  { 0x08, 0x05, -1, 0x03, 0x0142, 0x0046 },
  { 0x08, 0x05, -1, 0x03, 0x0142, 0x0066 },
  { 0x08, 0x06, -1, 0x03, 0x0142, 0x0086 },
  { 0x08, 0x07, -1, 0x03, 0x0142, 0x00c6 },
  { 0x08, 0x08, -1, 0x03, 0x0142, 0x0146 },
  { 0x08, 0x09, -1, 0x03, 0x0142, 0x0246 },
  { 0x08, 0x0a, -1, 0x03, 0x0142, 0x0446 },
  { 0x08, 0x18, -1, 0x03, 0x0142, 0x0846 },
  { 0x09, 0x05, -1, 0x03, 0x0242, 0x0046 },
  { 0x09, 0x05, -1, 0x03, 0x0242, 0x0066 },
  { 0x09, 0x06, -1, 0x03, 0x0242, 0x0086 },
  { 0x09, 0x07, -1, 0x03, 0x0242, 0x00c6 },
  { 0x09, 0x08, -1, 0x03, 0x0242, 0x0146 },
  { 0x09, 0x09, -1, 0x03, 0x0242, 0x0246 },
  { 0x09, 0x0a, -1, 0x03, 0x0242, 0x0446 },
  { 0x09, 0x18, -1, 0x03, 0x0242, 0x0846 },
  { 0x0a, 0x05, -1, 0x03, 0x0442, 0x0046 },
  { 0x0a, 0x05, -1, 0x03, 0x0442, 0x0066 },
  { 0x0a, 0x06, -1, 0x03, 0x0442, 0x0086 },
  { 0x0a, 0x07, -1, 0x03, 0x0442, 0x00c6 },
  { 0x0a, 0x08, -1, 0x03, 0x0442, 0x0146 },
  { 0x0a, 0x09, -1, 0x03, 0x0442, 0x0246 },
  { 0x0a, 0x0a, -1, 0x03, 0x0442, 0x0446 },
  { 0x0a, 0x18, -1, 0x03, 0x0442, 0x0846 },
  { 0x0c, 0x05, -1, 0x03, 0x0842, 0x0046 },
  { 0x0c, 0x05, -1, 0x03, 0x0842, 0x0066 },
  { 0x0c, 0x06, -1, 0x03, 0x0842, 0x0086 },
  { 0x0c, 0x07, -1, 0x03, 0x0842, 0x00c6 },
  { 0x0c, 0x08, -1, 0x03, 0x0842, 0x0146 },
  { 0x0c, 0x09, -1, 0x03, 0x0842, 0x0246 },
  { 0x0c, 0x0a, -1, 0x03, 0x0842, 0x0446 },
  { 0x0c, 0x18, -1, 0x03, 0x0842, 0x0846 },
  { 0x0e, 0x05, -1, 0x03, 0x1842, 0x0046 },
  { 0x0e, 0x05, -1, 0x03, 0x1842, 0x0066 },
  { 0x0e, 0x06, -1, 0x03, 0x1842, 0x0086 },
  { 0x0e, 0x07, -1, 0x03, 0x1842, 0x00c6 },
  { 0x0e, 0x08, -1, 0x03, 0x1842, 0x0146 },
  { 0x0e, 0x09, -1, 0x03, 0x1842, 0x0246 },
  { 0x0e, 0x0a, -1, 0x03, 0x1842, 0x0446 },
  { 0x0e, 0x18, -1, 0x03, 0x1842, 0x0846 },
  { 0x18, 0x05, -1, 0x03, 0x5842, 0x0046 },
  { 0x18, 0x05, -1, 0x03, 0x5842, 0x0066 },
  { 0x18, 0x06, -1, 0x03, 0x5842, 0x0086 },
  { 0x18, 0x07, -1, 0x03, 0x5842, 0x00c6 },
  { 0x18, 0x08, -1, 0x03, 0x5842, 0x0146 },
  { 0x18, 0x09, -1, 0x03, 0x5842, 0x0246 },
  { 0x18, 0x0a, -1, 0x03, 0x5842, 0x0446 },
  { 0x18, 0x18, -1, 0x03, 0x5842, 0x0846 },
};
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./state.h" 1
# 13 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./state.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/dictionary.h" 1
# 14 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./state.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./../common/transform.h" 1
# 16 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./state.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/././bit_reader.h" 1
# 18 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/./state.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/././huffman.h" 1
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
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c" 2
# 46 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c"
static const uint32_t kRingBufferWriteAheadSlack = 42;

static const uint8_t kCodeLengthCodeOrder[(17 + 1)] = {
  1, 2, 3, 4, 0, 5, 17, 6, 16, 7, 8, 9, 10, 11, 12, 13, 14, 15,
};


static const uint8_t kCodeLengthPrefixLength[16] = {
  2, 2, 2, 3, 2, 2, 2, 4, 2, 2, 2, 3, 2, 2, 2, 4,
};

static const uint8_t kCodeLengthPrefixValue[16] = {
  0, 4, 3, 2, 0, 4, 3, 1, 0, 4, 3, 2, 0, 4, 3, 5,
};

int BrotliDecoderSetParameter(
    BrotliDecoderStateInternal* state, BrotliDecoderParameter p, uint32_t value) {
  if (state->state != BROTLI_STATE_UNINITED) return 0;
  switch (p) {
    case BROTLI_DECODER_PARAM_DISABLE_RING_BUFFER_REALLOCATION:
      state->canny_ringbuffer_allocation = !!value ? 0 : 1;
      return 1;

    case BROTLI_DECODER_PARAM_LARGE_WINDOW:
      state->large_window = (!!(!!value) ? 1 : 0);
      return 1;

    default: return 0;
  }
}

BrotliDecoderStateInternal* BrotliDecoderCreateInstance(
    brotli_alloc_func alloc_func, brotli_free_func free_func, void* opaque) {
  BrotliDecoderStateInternal* state = 0;
  if (!alloc_func && !free_func) {
    state = (BrotliDecoderStateInternal*)malloc(sizeof(BrotliDecoderStateInternal));
  } else if (alloc_func && free_func) {
    state = (BrotliDecoderStateInternal*)alloc_func(opaque, sizeof(BrotliDecoderStateInternal));
  }
  if (state == 0) {
    (void)(0);
    return 0;
  }
  if (!BrotliDecoderStateInit(state, alloc_func, free_func, opaque)) {
    (void)(0);
    if (!alloc_func && !free_func) {
      free(state);
    } else if (alloc_func && free_func) {
      free_func(opaque, state);
    }
    return 0;
  }
  return state;
}


void BrotliDecoderDestroyInstance(BrotliDecoderStateInternal* state) {
  if (!state) {
    return;
  } else {
    brotli_free_func free_func = state->free_func;
    void* opaque = state->memory_manager_opaque;
    BrotliDecoderStateCleanup(state);
    free_func(opaque, state);
  }
}


static BrotliDecoderResult SaveErrorCode(
    BrotliDecoderStateInternal* s, BrotliDecoderErrorCode e) {
  s->error_code = (int)e;
  switch (e) {
    case BROTLI_DECODER_SUCCESS:
      return BROTLI_DECODER_RESULT_SUCCESS;

    case BROTLI_DECODER_NEEDS_MORE_INPUT:
      return BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT;

    case BROTLI_DECODER_NEEDS_MORE_OUTPUT:
      return BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT;

    default:
      return BROTLI_DECODER_RESULT_ERROR;
  }
}



static BrotliDecoderErrorCode DecodeWindowBits(BrotliDecoderStateInternal* s,
                                               BrotliBitReader* br) {
  uint32_t n;
  int large_window = s->large_window;
  s->large_window = 0;
  BrotliTakeBits(br, 1, &n);
  if (n == 0) {
    s->window_bits = 16;
    return BROTLI_DECODER_SUCCESS;
  }
  BrotliTakeBits(br, 3, &n);
  if (n != 0) {
    s->window_bits = 17 + n;
    return BROTLI_DECODER_SUCCESS;
  }
  BrotliTakeBits(br, 3, &n);
  if (n == 1) {
    if (large_window) {
      BrotliTakeBits(br, 1, &n);
      if (n == 1) {
        return ((void)(0), BROTLI_DECODER_ERROR_FORMAT_WINDOW_BITS);
      }
      s->large_window = 1;
      return BROTLI_DECODER_SUCCESS;
    } else {
      return ((void)(0), BROTLI_DECODER_ERROR_FORMAT_WINDOW_BITS);
    }
  }
  if (n != 0) {
    s->window_bits = 8 + n;
    return BROTLI_DECODER_SUCCESS;
  }
  s->window_bits = 17;
  return BROTLI_DECODER_SUCCESS;
}

static inline void memmove16(uint8_t* dst, uint8_t* src) {



  uint32_t buffer[4];
  memcpy(buffer, src, 16);
  memcpy(dst, buffer, 16);

}


static BrotliDecoderErrorCode DecodeVarLenUint8(
    BrotliDecoderStateInternal* s, BrotliBitReader* br, uint32_t* value) {
  uint32_t bits;
  switch (s->substate_decode_uint8) {
    case BROTLI_STATE_DECODE_UINT8_NONE:
      if ((__builtin_expect(!BrotliSafeReadBits(br, 1, &bits), 0))) {
        return BROTLI_DECODER_NEEDS_MORE_INPUT;
      }
      if (bits == 0) {
        *value = 0;
        return BROTLI_DECODER_SUCCESS;
      }


    case BROTLI_STATE_DECODE_UINT8_SHORT:
      if ((__builtin_expect(!BrotliSafeReadBits(br, 3, &bits), 0))) {
        s->substate_decode_uint8 = BROTLI_STATE_DECODE_UINT8_SHORT;
        return BROTLI_DECODER_NEEDS_MORE_INPUT;
      }
      if (bits == 0) {
        *value = 1;
        s->substate_decode_uint8 = BROTLI_STATE_DECODE_UINT8_NONE;
        return BROTLI_DECODER_SUCCESS;
      }

      *value = bits;


    case BROTLI_STATE_DECODE_UINT8_LONG:
      if ((__builtin_expect(!BrotliSafeReadBits(br, *value, &bits), 0))) {
        s->substate_decode_uint8 = BROTLI_STATE_DECODE_UINT8_LONG;
        return BROTLI_DECODER_NEEDS_MORE_INPUT;
      }
      *value = (1U << *value) + bits;
      s->substate_decode_uint8 = BROTLI_STATE_DECODE_UINT8_NONE;
      return BROTLI_DECODER_SUCCESS;

    default:
      return
          ((void)(0), BROTLI_DECODER_ERROR_UNREACHABLE);
  }
}


static BrotliDecoderErrorCode DecodeMetaBlockLength(
    BrotliDecoderStateInternal* s, BrotliBitReader* br) {
  uint32_t bits;
  int i;
  for (;;) {
    switch (s->substate_metablock_header) {
      case BROTLI_STATE_METABLOCK_HEADER_NONE:
        if (!BrotliSafeReadBits(br, 1, &bits)) {
          return BROTLI_DECODER_NEEDS_MORE_INPUT;
        }
        s->is_last_metablock = bits ? 1 : 0;
        s->meta_block_remaining_len = 0;
        s->is_uncompressed = 0;
        s->is_metadata = 0;
        if (!s->is_last_metablock) {
          s->substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_NIBBLES;
          break;
        }
        s->substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_EMPTY;


      case BROTLI_STATE_METABLOCK_HEADER_EMPTY:
        if (!BrotliSafeReadBits(br, 1, &bits)) {
          return BROTLI_DECODER_NEEDS_MORE_INPUT;
        }
        if (bits) {
          s->substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_NONE;
          return BROTLI_DECODER_SUCCESS;
        }
        s->substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_NIBBLES;


      case BROTLI_STATE_METABLOCK_HEADER_NIBBLES:
        if (!BrotliSafeReadBits(br, 2, &bits)) {
          return BROTLI_DECODER_NEEDS_MORE_INPUT;
        }
        s->size_nibbles = (uint8_t)(bits + 4);
        s->loop_counter = 0;
        if (bits == 3) {
          s->is_metadata = 1;
          s->substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_RESERVED;
          break;
        }
        s->substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_SIZE;


      case BROTLI_STATE_METABLOCK_HEADER_SIZE:
        i = s->loop_counter;
        for (; i < (int)s->size_nibbles; ++i) {
          if (!BrotliSafeReadBits(br, 4, &bits)) {
            s->loop_counter = i;
            return BROTLI_DECODER_NEEDS_MORE_INPUT;
          }
          if (i + 1 == (int)s->size_nibbles && s->size_nibbles > 4 &&
              bits == 0) {
            return ((void)(0), BROTLI_DECODER_ERROR_FORMAT_EXUBERANT_NIBBLE);
          }
          s->meta_block_remaining_len |= (int)(bits << (i * 4));
        }
        s->substate_metablock_header =
            BROTLI_STATE_METABLOCK_HEADER_UNCOMPRESSED;


      case BROTLI_STATE_METABLOCK_HEADER_UNCOMPRESSED:
        if (!s->is_last_metablock) {
          if (!BrotliSafeReadBits(br, 1, &bits)) {
            return BROTLI_DECODER_NEEDS_MORE_INPUT;
          }
          s->is_uncompressed = bits ? 1 : 0;
        }
        ++s->meta_block_remaining_len;
        s->substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_NONE;
        return BROTLI_DECODER_SUCCESS;

      case BROTLI_STATE_METABLOCK_HEADER_RESERVED:
        if (!BrotliSafeReadBits(br, 1, &bits)) {
          return BROTLI_DECODER_NEEDS_MORE_INPUT;
        }
        if (bits != 0) {
          return ((void)(0), BROTLI_DECODER_ERROR_FORMAT_RESERVED);
        }
        s->substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_BYTES;


      case BROTLI_STATE_METABLOCK_HEADER_BYTES:
        if (!BrotliSafeReadBits(br, 2, &bits)) {
          return BROTLI_DECODER_NEEDS_MORE_INPUT;
        }
        if (bits == 0) {
          s->substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_NONE;
          return BROTLI_DECODER_SUCCESS;
        }
        s->size_nibbles = (uint8_t)bits;
        s->substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_METADATA;


      case BROTLI_STATE_METABLOCK_HEADER_METADATA:
        i = s->loop_counter;
        for (; i < (int)s->size_nibbles; ++i) {
          if (!BrotliSafeReadBits(br, 8, &bits)) {
            s->loop_counter = i;
            return BROTLI_DECODER_NEEDS_MORE_INPUT;
          }
          if (i + 1 == (int)s->size_nibbles && s->size_nibbles > 1 &&
              bits == 0) {
            return ((void)(0), BROTLI_DECODER_ERROR_FORMAT_EXUBERANT_META_NIBBLE)
                                                                  ;
          }
          s->meta_block_remaining_len |= (int)(bits << (i * 8));
        }
        ++s->meta_block_remaining_len;
        s->substate_metablock_header = BROTLI_STATE_METABLOCK_HEADER_NONE;
        return BROTLI_DECODER_SUCCESS;

      default:
        return
            ((void)(0), BROTLI_DECODER_ERROR_UNREACHABLE);
    }
  }
}





static inline uint32_t DecodeSymbol(uint32_t bits,
                                           const HuffmanCode* table,
                                           BrotliBitReader* br) {
  ;
  table += (bits & 0xFF);
  if ((table->bits) > 8U) {
    uint32_t nbits = (table->bits) - 8U;
    BrotliDropBits(br, 8U);
    table += ((table->value) + ((bits >> 8U) & BitMask(nbits)))

                                                        ;
  }
  BrotliDropBits(br, (table->bits));
  return (table->value);
}



static inline uint32_t ReadSymbol(const HuffmanCode* table,
                                         BrotliBitReader* br) {
  return DecodeSymbol(BrotliGet16BitsUnmasked(br), table, br);
}



static int SafeDecodeSymbol(
    const HuffmanCode* table, BrotliBitReader* br, uint32_t* result) {
  uint32_t val;
  uint32_t available_bits = BrotliGetAvailableBits(br);
  ;
  if (available_bits == 0) {
    if ((table->bits) == 0) {
      *result = (table->value);
      return 1;
    }
    return 0;
  }
  val = (uint32_t)BrotliGetBitsUnmasked(br);
  table += (val & 0xFF);
  if ((table->bits) <= 8U) {
    if ((table->bits) <= available_bits) {
      BrotliDropBits(br, (table->bits));
      *result = (table->value);
      return 1;
    } else {
      return 0;
    }
  }
  if (available_bits <= 8U) {
    return 0;
  }


  val = (val & BitMask((table->bits))) >> 8U;
  available_bits -= 8U;
  table += ((table->value) + val);
  if (available_bits < (table->bits)) {
    return 0;
  }

  BrotliDropBits(br, 8U + (table->bits));
  *result = (table->value);
  return 1;
}

static inline int SafeReadSymbol(
    const HuffmanCode* table, BrotliBitReader* br, uint32_t* result) {
  uint32_t val;
  if ((__builtin_expect(!!(BrotliSafeGetBits(br, 15, &val)), 1))) {
    *result = DecodeSymbol(val, table, br);
    return 1;
  }
  return SafeDecodeSymbol(table, br, result);
}


static inline void PreloadSymbol(int safe,
                                        const HuffmanCode* table,
                                        BrotliBitReader* br,
                                        uint32_t* bits,
                                        uint32_t* value) {
  if (safe) {
    return;
  }
  ;
  table += (BrotliGetBits(br, 8U));
  *bits = (table->bits);
  *value = (table->value);
}



static inline uint32_t ReadPreloadedSymbol(const HuffmanCode* table,
                                                  BrotliBitReader* br,
                                                  uint32_t* bits,
                                                  uint32_t* value) {
  uint32_t result = *value;
  if ((__builtin_expect(*bits > 8U, 0))) {
    uint32_t val = BrotliGet16BitsUnmasked(br);
    const HuffmanCode* ext = table + (val & 0xFF) + *value;
    uint32_t mask = BitMask((*bits - 8U));
    ;
    BrotliDropBits(br, 8U);
    ext += ((val >> 8U) & mask);
    BrotliDropBits(br, (ext->bits));
    result = (ext->value);
  } else {
    BrotliDropBits(br, *bits);
  }
  PreloadSymbol(0, table, br, bits, value);
  return result;
}

static inline uint32_t Log2Floor(uint32_t x) {
  uint32_t result = 0;
  while (x) {
    x >>= 1;
    ++result;
  }
  return result;
}




static BrotliDecoderErrorCode ReadSimpleHuffmanSymbols(
    uint32_t alphabet_size_max, uint32_t alphabet_size_limit,
    BrotliDecoderStateInternal* s) {

  BrotliBitReader* br = &s->br;
  BrotliMetablockHeaderArena* h = &s->arena.header;
  uint32_t max_bits = Log2Floor(alphabet_size_max - 1);
  uint32_t i = h->sub_loop_counter;
  uint32_t num_symbols = h->symbol;
  while (i <= num_symbols) {
    uint32_t v;
    if ((__builtin_expect(!BrotliSafeReadBits(br, max_bits, &v), 0))) {
      h->sub_loop_counter = i;
      h->substate_huffman = BROTLI_STATE_HUFFMAN_SIMPLE_READ;
      return BROTLI_DECODER_NEEDS_MORE_INPUT;
    }
    if (v >= alphabet_size_limit) {
      return
          ((void)(0), BROTLI_DECODER_ERROR_FORMAT_SIMPLE_HUFFMAN_ALPHABET);
    }
    h->symbols_lists_array[i] = (uint16_t)v;
    ;
    ++i;
  }

  for (i = 0; i < num_symbols; ++i) {
    uint32_t k = i + 1;
    for (; k <= num_symbols; ++k) {
      if (h->symbols_lists_array[i] == h->symbols_lists_array[k]) {
        return ((void)(0), BROTLI_DECODER_ERROR_FORMAT_SIMPLE_HUFFMAN_SAME);
      }
    }
  }

  return BROTLI_DECODER_SUCCESS;
}







static inline void ProcessSingleCodeLength(uint32_t code_len,
    uint32_t* symbol, uint32_t* repeat, uint32_t* space,
    uint32_t* prev_code_len, uint16_t* symbol_lists,
    uint16_t* code_length_histo, int* next_symbol) {
  *repeat = 0;
  if (code_len != 0) {
    symbol_lists[next_symbol[code_len]] = (uint16_t)(*symbol);
    next_symbol[code_len] = (int)(*symbol);
    *prev_code_len = code_len;
    *space -= 32768U >> code_len;
    code_length_histo[code_len]++;
   
                                     ;
  }
  (*symbol)++;
}
# 545 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c"
static inline void ProcessRepeatedCodeLength(uint32_t code_len,
    uint32_t repeat_delta, uint32_t alphabet_size, uint32_t* symbol,
    uint32_t* repeat, uint32_t* space, uint32_t* prev_code_len,
    uint32_t* repeat_code_len, uint16_t* symbol_lists,
    uint16_t* code_length_histo, int* next_symbol) {
  uint32_t old_repeat;
  uint32_t extra_bits = 3;
  uint32_t new_len = 0;
  if (code_len == 16) {
    new_len = *prev_code_len;
    extra_bits = 2;
  }
  if (*repeat_code_len != new_len) {
    *repeat = 0;
    *repeat_code_len = new_len;
  }
  old_repeat = *repeat;
  if (*repeat > 0) {
    *repeat -= 2;
    *repeat <<= extra_bits;
  }
  *repeat += repeat_delta + 3U;
  repeat_delta = *repeat - old_repeat;
  if (*symbol + repeat_delta > alphabet_size) {
    (void)(0);
    *symbol = alphabet_size;
    *space = 0xFFFFF;
    return;
  }
 
                                                                              ;
  if (*repeat_code_len != 0) {
    unsigned last = *symbol + repeat_delta;
    int next = next_symbol[*repeat_code_len];
    do {
      symbol_lists[next] = (uint16_t)*symbol;
      next = (int)*symbol;
    } while (++(*symbol) != last);
    next_symbol[*repeat_code_len] = next;
    *space -= repeat_delta << (15 - *repeat_code_len);
    code_length_histo[*repeat_code_len] =
        (uint16_t)(code_length_histo[*repeat_code_len] + repeat_delta);
  } else {
    *symbol += repeat_delta;
  }
}


static BrotliDecoderErrorCode ReadSymbolCodeLengths(
    uint32_t alphabet_size, BrotliDecoderStateInternal* s) {
  BrotliBitReader* br = &s->br;
  BrotliMetablockHeaderArena* h = &s->arena.header;
  uint32_t symbol = h->symbol;
  uint32_t repeat = h->repeat;
  uint32_t space = h->space;
  uint32_t prev_code_len = h->prev_code_len;
  uint32_t repeat_code_len = h->repeat_code_len;
  uint16_t* symbol_lists = h->symbol_lists;
  uint16_t* code_length_histo = h->code_length_histo;
  int* next_symbol = h->next_symbol;
  if (!BrotliWarmupBitReader(br)) {
    return BROTLI_DECODER_NEEDS_MORE_INPUT;
  }
  while (symbol < alphabet_size && space > 0) {
    const HuffmanCode* p = h->table;
    uint32_t code_len;
    ;
    if (!BrotliCheckInputAmount(br, (sizeof(uint64_t) >> 1))) {
      h->symbol = symbol;
      h->repeat = repeat;
      h->prev_code_len = prev_code_len;
      h->repeat_code_len = repeat_code_len;
      h->space = space;
      return BROTLI_DECODER_NEEDS_MORE_INPUT;
    }
    BrotliFillBitWindow16(br);
    p += (BrotliGetBitsUnmasked(br) & BitMask(5))
                                                            ;
    BrotliDropBits(br, (p->bits));
    code_len = (p->value);
    if (code_len < 16) {
      ProcessSingleCodeLength(code_len, &symbol, &repeat, &space,
          &prev_code_len, symbol_lists, code_length_histo, next_symbol);
    } else {
      uint32_t extra_bits =
          (code_len == 16) ? 2 : 3;
      uint32_t repeat_delta =
          (uint32_t)BrotliGetBitsUnmasked(br) & BitMask(extra_bits);
      BrotliDropBits(br, extra_bits);
      ProcessRepeatedCodeLength(code_len, repeat_delta, alphabet_size,
          &symbol, &repeat, &space, &prev_code_len, &repeat_code_len,
          symbol_lists, code_length_histo, next_symbol);
    }
  }
  h->space = space;
  return BROTLI_DECODER_SUCCESS;
}

static BrotliDecoderErrorCode SafeReadSymbolCodeLengths(
    uint32_t alphabet_size, BrotliDecoderStateInternal* s) {
  BrotliBitReader* br = &s->br;
  BrotliMetablockHeaderArena* h = &s->arena.header;
  int get_byte = 0;
  while (h->symbol < alphabet_size && h->space > 0) {
    const HuffmanCode* p = h->table;
    uint32_t code_len;
    uint32_t available_bits;
    uint32_t bits = 0;
    ;
    if (get_byte && !BrotliPullByte(br)) return BROTLI_DECODER_NEEDS_MORE_INPUT;
    get_byte = 0;
    available_bits = BrotliGetAvailableBits(br);
    if (available_bits != 0) {
      bits = (uint32_t)BrotliGetBitsUnmasked(br);
    }
    p += (bits & BitMask(5))
                                                                   ;
    if ((p->bits) > available_bits) {
      get_byte = 1;
      continue;
    }
    code_len = (p->value);
    if (code_len < 16) {
      BrotliDropBits(br, (p->bits));
      ProcessSingleCodeLength(code_len, &h->symbol, &h->repeat, &h->space,
          &h->prev_code_len, h->symbol_lists, h->code_length_histo,
          h->next_symbol);
    } else {
      uint32_t extra_bits = code_len - 14U;
      uint32_t repeat_delta = (bits >> (p->bits)) &
          BitMask(extra_bits);
      if (available_bits < (p->bits) + extra_bits) {
        get_byte = 1;
        continue;
      }
      BrotliDropBits(br, (p->bits) + extra_bits);
      ProcessRepeatedCodeLength(code_len, repeat_delta, alphabet_size,
          &h->symbol, &h->repeat, &h->space, &h->prev_code_len,
          &h->repeat_code_len, h->symbol_lists, h->code_length_histo,
          h->next_symbol);
    }
  }
  return BROTLI_DECODER_SUCCESS;
}



static BrotliDecoderErrorCode ReadCodeLengthCodeLengths(BrotliDecoderStateInternal* s) {
  BrotliBitReader* br = &s->br;
  BrotliMetablockHeaderArena* h = &s->arena.header;
  uint32_t num_codes = h->repeat;
  unsigned space = h->space;
  uint32_t i = h->sub_loop_counter;
  for (; i < (17 + 1); ++i) {
    const uint8_t code_len_idx = kCodeLengthCodeOrder[i];
    uint32_t ix;
    uint32_t v;
    if ((__builtin_expect(!BrotliSafeGetBits(br, 4, &ix), 0))) {
      uint32_t available_bits = BrotliGetAvailableBits(br);
      if (available_bits != 0) {
        ix = BrotliGetBitsUnmasked(br) & 0xF;
      } else {
        ix = 0;
      }
      if (kCodeLengthPrefixLength[ix] > available_bits) {
        h->sub_loop_counter = i;
        h->repeat = num_codes;
        h->space = space;
        h->substate_huffman = BROTLI_STATE_HUFFMAN_COMPLEX;
        return BROTLI_DECODER_NEEDS_MORE_INPUT;
      }
    }
    v = kCodeLengthPrefixValue[ix];
    BrotliDropBits(br, kCodeLengthPrefixLength[ix]);
    h->code_length_code_lengths[code_len_idx] = (uint8_t)v;
    ;
    if (v != 0) {
      space = space - (32U >> v);
      ++num_codes;
      ++h->code_length_histo[v];
      if (space - 1U >= 32U) {

        break;
      }
    }
  }
  if (!(num_codes == 1 || space == 0)) {
    return ((void)(0), BROTLI_DECODER_ERROR_FORMAT_CL_SPACE);
  }
  return BROTLI_DECODER_SUCCESS;
}
# 748 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c"
static BrotliDecoderErrorCode ReadHuffmanCode(uint32_t alphabet_size_max,
                                              uint32_t alphabet_size_limit,
                                              HuffmanCode* table,
                                              uint32_t* opt_table_size,
                                              BrotliDecoderStateInternal* s) {
  BrotliBitReader* br = &s->br;
  BrotliMetablockHeaderArena* h = &s->arena.header;

  for (;;) {
    switch (h->substate_huffman) {
      case BROTLI_STATE_HUFFMAN_NONE:
        if (!BrotliSafeReadBits(br, 2, &h->sub_loop_counter)) {
          return BROTLI_DECODER_NEEDS_MORE_INPUT;
        }
        ;



        if (h->sub_loop_counter != 1) {
          h->space = 32;
          h->repeat = 0;
          memset(&h->code_length_histo[0], 0, sizeof(h->code_length_histo[0]) *
              (5 + 1));
          memset(&h->code_length_code_lengths[0], 0,
              sizeof(h->code_length_code_lengths));
          h->substate_huffman = BROTLI_STATE_HUFFMAN_COMPLEX;
          continue;
        }


      case BROTLI_STATE_HUFFMAN_SIMPLE_SIZE:

        if (!BrotliSafeReadBits(br, 2, &h->symbol)) {
          h->substate_huffman = BROTLI_STATE_HUFFMAN_SIMPLE_SIZE;
          return BROTLI_DECODER_NEEDS_MORE_INPUT;
        }
        h->sub_loop_counter = 0;


      case BROTLI_STATE_HUFFMAN_SIMPLE_READ: {
        BrotliDecoderErrorCode result =
            ReadSimpleHuffmanSymbols(alphabet_size_max, alphabet_size_limit, s);
        if (result != BROTLI_DECODER_SUCCESS) {
          return result;
        }
      }


      case BROTLI_STATE_HUFFMAN_SIMPLE_BUILD: {
        uint32_t table_size;
        if (h->symbol == 3) {
          uint32_t bits;
          if (!BrotliSafeReadBits(br, 1, &bits)) {
            h->substate_huffman = BROTLI_STATE_HUFFMAN_SIMPLE_BUILD;
            return BROTLI_DECODER_NEEDS_MORE_INPUT;
          }
          h->symbol += bits;
        }
        ;
        table_size = BrotliBuildSimpleHuffmanTable(
            table, 8U, h->symbols_lists_array, h->symbol);
        if (opt_table_size) {
          *opt_table_size = table_size;
        }
        h->substate_huffman = BROTLI_STATE_HUFFMAN_NONE;
        return BROTLI_DECODER_SUCCESS;
      }


      case BROTLI_STATE_HUFFMAN_COMPLEX: {
        uint32_t i;
        BrotliDecoderErrorCode result = ReadCodeLengthCodeLengths(s);
        if (result != BROTLI_DECODER_SUCCESS) {
          return result;
        }
        BrotliBuildCodeLengthsHuffmanTable(h->table,
                                           h->code_length_code_lengths,
                                           h->code_length_histo);
        memset(&h->code_length_histo[0], 0, sizeof(h->code_length_histo));
        for (i = 0; i <= 15; ++i) {
          h->next_symbol[i] = (int)i - (15 + 1);
          h->symbol_lists[h->next_symbol[i]] = 0xFFFF;
        }

        h->symbol = 0;
        h->prev_code_len = 8;
        h->repeat = 0;
        h->repeat_code_len = 0;
        h->space = 32768;
        h->substate_huffman = BROTLI_STATE_HUFFMAN_LENGTH_SYMBOLS;
      }


      case BROTLI_STATE_HUFFMAN_LENGTH_SYMBOLS: {
        uint32_t table_size;
        BrotliDecoderErrorCode result = ReadSymbolCodeLengths(
            alphabet_size_limit, s);
        if (result == BROTLI_DECODER_NEEDS_MORE_INPUT) {
          result = SafeReadSymbolCodeLengths(alphabet_size_limit, s);
        }
        if (result != BROTLI_DECODER_SUCCESS) {
          return result;
        }

        if (h->space != 0) {
          ;
          return ((void)(0), BROTLI_DECODER_ERROR_FORMAT_HUFFMAN_SPACE);
        }
        table_size = BrotliBuildHuffmanTable(
            table, 8U, h->symbol_lists, h->code_length_histo);
        if (opt_table_size) {
          *opt_table_size = table_size;
        }
        h->substate_huffman = BROTLI_STATE_HUFFMAN_NONE;
        return BROTLI_DECODER_SUCCESS;
      }

      default:
        return
            ((void)(0), BROTLI_DECODER_ERROR_UNREACHABLE);
    }
  }
}


static inline uint32_t ReadBlockLength(const HuffmanCode* table,
                                              BrotliBitReader* br) {
  uint32_t code;
  uint32_t nbits;
  code = ReadSymbol(table, br);
  nbits = _kBrotliPrefixCodeRanges[code].nbits;
  return _kBrotliPrefixCodeRanges[code].offset + BrotliReadBits24(br, nbits);
}



static inline int SafeReadBlockLength(
    BrotliDecoderStateInternal* s, uint32_t* result, const HuffmanCode* table,
    BrotliBitReader* br) {
  uint32_t index;
  if (s->substate_read_block_length == BROTLI_STATE_READ_BLOCK_LENGTH_NONE) {
    if (!SafeReadSymbol(table, br, &index)) {
      return 0;
    }
  } else {
    index = s->block_length_index;
  }
  {
    uint32_t bits;
    uint32_t nbits = _kBrotliPrefixCodeRanges[index].nbits;
    uint32_t offset = _kBrotliPrefixCodeRanges[index].offset;
    if (!BrotliSafeReadBits(br, nbits, &bits)) {
      s->block_length_index = index;
      s->substate_read_block_length = BROTLI_STATE_READ_BLOCK_LENGTH_SUFFIX;
      return 0;
    }
    *result = offset + bits;
    s->substate_read_block_length = BROTLI_STATE_READ_BLOCK_LENGTH_NONE;
    return 1;
  }
}
# 924 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c"
static void InverseMoveToFrontTransform(
    uint8_t* v, uint32_t v_len, BrotliDecoderStateInternal* state) {

  uint32_t i = 1;
  uint32_t upper_bound = state->mtf_upper_bound;
  uint32_t* mtf = &state->mtf[1];
  uint8_t* mtf_u8 = (uint8_t*)mtf;

  const uint8_t b0123[4] = {0, 1, 2, 3};
  uint32_t pattern;
  memcpy(&pattern, &b0123, 4);


  mtf[0] = pattern;
  do {
    pattern += 0x04040404;
    mtf[i] = pattern;
    i++;
  } while (i <= upper_bound);


  upper_bound = 0;
  for (i = 0; i < v_len; ++i) {
    int index = v[i];
    uint8_t value = mtf_u8[index];
    upper_bound |= v[i];
    v[i] = value;
    mtf_u8[-1] = value;
    do {
      index--;
      mtf_u8[index + 1] = mtf_u8[index];
    } while (index >= 0);
  }

  state->mtf_upper_bound = upper_bound >> 2;
}


static BrotliDecoderErrorCode HuffmanTreeGroupDecode(
    HuffmanTreeGroup* group, BrotliDecoderStateInternal* s) {
  BrotliMetablockHeaderArena* h = &s->arena.header;
  if (h->substate_tree_group != BROTLI_STATE_TREE_GROUP_LOOP) {
    h->next = group->codes;
    h->htree_index = 0;
    h->substate_tree_group = BROTLI_STATE_TREE_GROUP_LOOP;
  }
  while (h->htree_index < group->num_htrees) {
    uint32_t table_size;
    BrotliDecoderErrorCode result = ReadHuffmanCode(group->alphabet_size_max,
        group->alphabet_size_limit, h->next, &table_size, s);
    if (result != BROTLI_DECODER_SUCCESS) return result;
    group->htrees[h->htree_index] = h->next;
    h->next += table_size;
    ++h->htree_index;
  }
  h->substate_tree_group = BROTLI_STATE_TREE_GROUP_NONE;
  return BROTLI_DECODER_SUCCESS;
}
# 991 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c"
static BrotliDecoderErrorCode DecodeContextMap(uint32_t context_map_size,
                                               uint32_t* num_htrees,
                                               uint8_t** context_map_arg,
                                               BrotliDecoderStateInternal* s) {
  BrotliBitReader* br = &s->br;
  BrotliDecoderErrorCode result = BROTLI_DECODER_SUCCESS;
  BrotliMetablockHeaderArena* h = &s->arena.header;

  switch ((int)h->substate_context_map) {
    case BROTLI_STATE_CONTEXT_MAP_NONE:
      result = DecodeVarLenUint8(s, br, num_htrees);
      if (result != BROTLI_DECODER_SUCCESS) {
        return result;
      }
      (*num_htrees)++;
      h->context_index = 0;
      ;
      ;
      *context_map_arg =
          (uint8_t*)s->alloc_func(s->memory_manager_opaque, (size_t)context_map_size);
      if (*context_map_arg == 0) {
        return ((void)(0), BROTLI_DECODER_ERROR_ALLOC_CONTEXT_MAP);
      }
      if (*num_htrees <= 1) {
        memset(*context_map_arg, 0, (size_t)context_map_size);
        return BROTLI_DECODER_SUCCESS;
      }
      h->substate_context_map = BROTLI_STATE_CONTEXT_MAP_READ_PREFIX;


    case BROTLI_STATE_CONTEXT_MAP_READ_PREFIX: {
      uint32_t bits;


      if (!BrotliSafeGetBits(br, 5, &bits)) {
        return BROTLI_DECODER_NEEDS_MORE_INPUT;
      }
      if ((bits & 1) != 0) {
        h->max_run_length_prefix = (bits >> 1) + 1;
        BrotliDropBits(br, 5);
      } else {
        h->max_run_length_prefix = 0;
        BrotliDropBits(br, 1);
      }
      ;
      h->substate_context_map = BROTLI_STATE_CONTEXT_MAP_HUFFMAN;
    }


    case BROTLI_STATE_CONTEXT_MAP_HUFFMAN: {
      uint32_t alphabet_size = *num_htrees + h->max_run_length_prefix;
      result = ReadHuffmanCode(alphabet_size, alphabet_size,
                               h->context_map_table, 0, s);
      if (result != BROTLI_DECODER_SUCCESS) return result;
      h->code = 0xFFFF;
      h->substate_context_map = BROTLI_STATE_CONTEXT_MAP_DECODE;
    }


    case BROTLI_STATE_CONTEXT_MAP_DECODE: {
      uint32_t context_index = h->context_index;
      uint32_t max_run_length_prefix = h->max_run_length_prefix;
      uint8_t* context_map = *context_map_arg;
      uint32_t code = h->code;
      int skip_preamble = (code != 0xFFFF);
      while (context_index < context_map_size || skip_preamble) {
        if (!skip_preamble) {
          if (!SafeReadSymbol(h->context_map_table, br, &code)) {
            h->code = 0xFFFF;
            h->context_index = context_index;
            return BROTLI_DECODER_NEEDS_MORE_INPUT;
          }
          ;

          if (code == 0) {
            context_map[context_index++] = 0;
            continue;
          }
          if (code > max_run_length_prefix) {
            context_map[context_index++] =
                (uint8_t)(code - max_run_length_prefix);
            continue;
          }
        } else {
          skip_preamble = 0;
        }

        {
          uint32_t reps;
          if (!BrotliSafeReadBits(br, code, &reps)) {
            h->code = code;
            h->context_index = context_index;
            return BROTLI_DECODER_NEEDS_MORE_INPUT;
          }
          reps += 1U << code;
          ;
          if (context_index + reps > context_map_size) {
            return
                ((void)(0), BROTLI_DECODER_ERROR_FORMAT_CONTEXT_MAP_REPEAT);
          }
          do {
            context_map[context_index++] = 0;
          } while (--reps);
        }
      }
    }


    case BROTLI_STATE_CONTEXT_MAP_TRANSFORM: {
      uint32_t bits;
      if (!BrotliSafeReadBits(br, 1, &bits)) {
        h->substate_context_map = BROTLI_STATE_CONTEXT_MAP_TRANSFORM;
        return BROTLI_DECODER_NEEDS_MORE_INPUT;
      }
      if (bits != 0) {
        InverseMoveToFrontTransform(*context_map_arg, context_map_size, s);
      }
      h->substate_context_map = BROTLI_STATE_CONTEXT_MAP_NONE;
      return BROTLI_DECODER_SUCCESS;
    }

    default:
      return
          ((void)(0), BROTLI_DECODER_ERROR_UNREACHABLE);
  }
}



static inline int DecodeBlockTypeAndLength(
    int safe, BrotliDecoderStateInternal* s, int tree_type) {
  uint32_t max_block_type = s->num_block_types[tree_type];
  const HuffmanCode* type_tree = &s->block_type_trees[
      tree_type * 632];
  const HuffmanCode* len_tree = &s->block_len_trees[
      tree_type * 396];
  BrotliBitReader* br = &s->br;
  uint32_t* ringbuffer = &s->block_type_rb[tree_type * 2];
  uint32_t block_type;
  if (max_block_type <= 1) {
    return 0;
  }


  if (!safe) {
    block_type = ReadSymbol(type_tree, br);
    s->block_length[tree_type] = ReadBlockLength(len_tree, br);
  } else {
    BrotliBitReaderState memento;
    BrotliBitReaderSaveState(br, &memento);
    if (!SafeReadSymbol(type_tree, br, &block_type)) return 0;
    if (!SafeReadBlockLength(s, &s->block_length[tree_type], len_tree, br)) {
      s->substate_read_block_length = BROTLI_STATE_READ_BLOCK_LENGTH_NONE;
      BrotliBitReaderRestoreState(br, &memento);
      return 0;
    }
  }

  if (block_type == 1) {
    block_type = ringbuffer[1] + 1;
  } else if (block_type == 0) {
    block_type = ringbuffer[0];
  } else {
    block_type -= 2;
  }
  if (block_type >= max_block_type) {
    block_type -= max_block_type;
  }
  ringbuffer[0] = ringbuffer[1];
  ringbuffer[1] = block_type;
  return 1;
}

static inline void DetectTrivialLiteralBlockTypes(
    BrotliDecoderStateInternal* s) {
  size_t i;
  for (i = 0; i < 8; ++i) s->trivial_literal_contexts[i] = 0;
  for (i = 0; i < s->num_block_types[0]; i++) {
    size_t offset = i << 6;
    size_t error = 0;
    size_t sample = s->context_map[offset];
    size_t j;
    for (j = 0; j < (1u << 6);) {
      { if ((4 & 1) != 0) {error |= s->context_map[offset + j++] ^ sample;;} if ((4 & 2) != 0) {error |= s->context_map[offset + j++] ^ sample;; error |= s->context_map[offset + j++] ^ sample;;} if ((4 & 4) != 0) {error |= s->context_map[offset + j++] ^ sample;; error |= s->context_map[offset + j++] ^ sample;; error |= s->context_map[offset + j++] ^ sample;; error |= s->context_map[offset + j++] ^ sample;;} }
    }
    if (error == 0) {
      s->trivial_literal_contexts[i >> 5] |= 1u << (i & 31);
    }
  }
}

static inline void PrepareLiteralDecoding(BrotliDecoderStateInternal* s) {
  uint8_t context_mode;
  size_t trivial;
  uint32_t block_type = s->block_type_rb[1];
  uint32_t context_offset = block_type << 6;
  s->context_map_slice = s->context_map + context_offset;
  trivial = s->trivial_literal_contexts[block_type >> 5];
  s->trivial_literal_context = (trivial >> (block_type & 31)) & 1;
  s->literal_htree = s->literal_hgroup.htrees[s->context_map_slice[0]];
  context_mode = s->context_modes[block_type] & 3;
  s->context_lookup = (&_kBrotliContextLookupTable[(context_mode) << 9]);
}



static inline int DecodeLiteralBlockSwitchInternal(
    int safe, BrotliDecoderStateInternal* s) {
  if (!DecodeBlockTypeAndLength(safe, s, 0)) {
    return 0;
  }
  PrepareLiteralDecoding(s);
  return 1;
}

static void DecodeLiteralBlockSwitch(BrotliDecoderStateInternal* s) {
  DecodeLiteralBlockSwitchInternal(0, s);
}

static int SafeDecodeLiteralBlockSwitch(
    BrotliDecoderStateInternal* s) {
  return DecodeLiteralBlockSwitchInternal(1, s);
}



static inline int DecodeCommandBlockSwitchInternal(
    int safe, BrotliDecoderStateInternal* s) {
  if (!DecodeBlockTypeAndLength(safe, s, 1)) {
    return 0;
  }
  s->htree_command = s->insert_copy_hgroup.htrees[s->block_type_rb[3]];
  return 1;
}

static void DecodeCommandBlockSwitch(BrotliDecoderStateInternal* s) {
  DecodeCommandBlockSwitchInternal(0, s);
}

static int SafeDecodeCommandBlockSwitch(
    BrotliDecoderStateInternal* s) {
  return DecodeCommandBlockSwitchInternal(1, s);
}



static inline int DecodeDistanceBlockSwitchInternal(
    int safe, BrotliDecoderStateInternal* s) {
  if (!DecodeBlockTypeAndLength(safe, s, 2)) {
    return 0;
  }
  s->dist_context_map_slice = s->dist_context_map +
      (s->block_type_rb[5] << 2);
  s->dist_htree_index = s->dist_context_map_slice[s->distance_context];
  return 1;
}

static void DecodeDistanceBlockSwitch(BrotliDecoderStateInternal* s) {
  DecodeDistanceBlockSwitchInternal(0, s);
}

static int SafeDecodeDistanceBlockSwitch(
    BrotliDecoderStateInternal* s) {
  return DecodeDistanceBlockSwitchInternal(1, s);
}

static size_t UnwrittenBytes(const BrotliDecoderStateInternal* s, int wrap) {
  size_t pos = wrap && s->pos > s->ringbuffer_size ?
      (size_t)s->ringbuffer_size : (size_t)(s->pos);
  size_t partial_pos_rb = (s->rb_roundtrips * (size_t)s->ringbuffer_size) + pos;
  return partial_pos_rb - s->partial_pos_out;
}




static BrotliDecoderErrorCode WriteRingBuffer(
    BrotliDecoderStateInternal* s, size_t* available_out, uint8_t** next_out,
    size_t* total_out, int force) {
  uint8_t* start =
      s->ringbuffer + (s->partial_pos_out & (size_t)s->ringbuffer_mask);
  size_t to_write = UnwrittenBytes(s, 1);
  size_t num_written = *available_out;
  if (num_written > to_write) {
    num_written = to_write;
  }
  if (s->meta_block_remaining_len < 0) {
    return ((void)(0), BROTLI_DECODER_ERROR_FORMAT_BLOCK_LENGTH_1);
  }
  if (next_out && !*next_out) {
    *next_out = start;
  } else {
    if (next_out) {
      memcpy(*next_out, start, num_written);
      *next_out += num_written;
    }
  }
  *available_out -= num_written;
  ;
  ;
  s->partial_pos_out += num_written;
  if (total_out) {
    *total_out = s->partial_pos_out;
  }
  if (num_written < to_write) {
    if (s->ringbuffer_size == (1 << s->window_bits) || force) {
      return BROTLI_DECODER_NEEDS_MORE_OUTPUT;
    } else {
      return BROTLI_DECODER_SUCCESS;
    }
  }

  if (s->ringbuffer_size == (1 << s->window_bits) &&
      s->pos >= s->ringbuffer_size) {
    s->pos -= s->ringbuffer_size;
    s->rb_roundtrips++;
    s->should_wrap_ringbuffer = (size_t)s->pos != 0 ? 1 : 0;
  }
  return BROTLI_DECODER_SUCCESS;
}

static void WrapRingBuffer(BrotliDecoderStateInternal* s) {
  if (s->should_wrap_ringbuffer) {
    memcpy(s->ringbuffer, s->ringbuffer_end, (size_t)s->pos);
    s->should_wrap_ringbuffer = 0;
  }
}
# 1326 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c"
static int BrotliEnsureRingBuffer(
    BrotliDecoderStateInternal* s) {
  uint8_t* old_ringbuffer = s->ringbuffer;
  if (s->ringbuffer_size == s->new_ringbuffer_size) {
    return 1;
  }

  s->ringbuffer = (uint8_t*)s->alloc_func(s->memory_manager_opaque, (size_t)(s->new_ringbuffer_size) + kRingBufferWriteAheadSlack)
                                                                    ;
  if (s->ringbuffer == 0) {

    s->ringbuffer = old_ringbuffer;
    return 0;
  }
  s->ringbuffer[s->new_ringbuffer_size - 2] = 0;
  s->ringbuffer[s->new_ringbuffer_size - 1] = 0;

  if (!!old_ringbuffer) {
    memcpy(s->ringbuffer, old_ringbuffer, (size_t)s->pos);
    { s->free_func(s->memory_manager_opaque, old_ringbuffer); old_ringbuffer = 0; };
  }

  s->ringbuffer_size = s->new_ringbuffer_size;
  s->ringbuffer_mask = s->new_ringbuffer_size - 1;
  s->ringbuffer_end = s->ringbuffer + s->ringbuffer_size;

  return 1;
}

static BrotliDecoderErrorCode CopyUncompressedBlockToOutput(
    size_t* available_out, uint8_t** next_out, size_t* total_out,
    BrotliDecoderStateInternal* s) {

  if (!BrotliEnsureRingBuffer(s)) {
    return ((void)(0), BROTLI_DECODER_ERROR_ALLOC_RING_BUFFER_1);
  }


  for (;;) {
    switch (s->substate_uncompressed) {
      case BROTLI_STATE_UNCOMPRESSED_NONE: {
        int nbytes = (int)BrotliGetRemainingBytes(&s->br);
        if (nbytes > s->meta_block_remaining_len) {
          nbytes = s->meta_block_remaining_len;
        }
        if (s->pos + nbytes > s->ringbuffer_size) {
          nbytes = s->ringbuffer_size - s->pos;
        }

        BrotliCopyBytes(&s->ringbuffer[s->pos], &s->br, (size_t)nbytes);
        s->pos += nbytes;
        s->meta_block_remaining_len -= nbytes;
        if (s->pos < 1 << s->window_bits) {
          if (s->meta_block_remaining_len == 0) {
            return BROTLI_DECODER_SUCCESS;
          }
          return BROTLI_DECODER_NEEDS_MORE_INPUT;
        }
        s->substate_uncompressed = BROTLI_STATE_UNCOMPRESSED_WRITE;
      }


      case BROTLI_STATE_UNCOMPRESSED_WRITE: {
        BrotliDecoderErrorCode result;
        result = WriteRingBuffer(
            s, available_out, next_out, total_out, 0);
        if (result != BROTLI_DECODER_SUCCESS) {
          return result;
        }
        if (s->ringbuffer_size == 1 << s->window_bits) {
          s->max_distance = s->max_backward_distance;
        }
        s->substate_uncompressed = BROTLI_STATE_UNCOMPRESSED_NONE;
        break;
      }
    }
  }
  ;
}







static void BrotliCalculateRingBufferSize(
    BrotliDecoderStateInternal* s) {
  int window_size = 1 << s->window_bits;
  int new_ringbuffer_size = window_size;


  int min_size = s->ringbuffer_size ? s->ringbuffer_size : 1024;
  int output_size;


  if (s->ringbuffer_size == window_size) {
    return;
  }


  if (s->is_metadata) {
    return;
  }

  if (!s->ringbuffer) {
    output_size = 0;
  } else {
    output_size = s->pos;
  }
  output_size += s->meta_block_remaining_len;
  min_size = min_size < output_size ? output_size : min_size;

  if (!!s->canny_ringbuffer_allocation) {



    while ((new_ringbuffer_size >> 1) >= min_size) {
      new_ringbuffer_size >>= 1;
    }
  }

  s->new_ringbuffer_size = new_ringbuffer_size;
}


static BrotliDecoderErrorCode ReadContextModes(BrotliDecoderStateInternal* s) {
  BrotliBitReader* br = &s->br;
  int i = s->loop_counter;

  while (i < (int)s->num_block_types[0]) {
    uint32_t bits;
    if (!BrotliSafeReadBits(br, 2, &bits)) {
      s->loop_counter = i;
      return BROTLI_DECODER_NEEDS_MORE_INPUT;
    }
    s->context_modes[i] = (uint8_t)bits;
    ;
    i++;
  }
  return BROTLI_DECODER_SUCCESS;
}

static inline void TakeDistanceFromRingBuffer(BrotliDecoderStateInternal* s) {
  int offset = s->distance_code - 3;
  if (s->distance_code <= 3) {

    s->distance_context = 1 >> s->distance_code;
    s->distance_code = s->dist_rb[(s->dist_rb_idx - offset) & 3];
    s->dist_rb_idx -= s->distance_context;
  } else {
    int index_delta = 3;
    int delta;
    int base = s->distance_code - 10;
    if (s->distance_code < 10) {
      base = s->distance_code - 4;
    } else {
      index_delta = 2;
    }

    delta = ((0x605142 >> (4 * base)) & 0xF) - 3;
    s->distance_code = s->dist_rb[(s->dist_rb_idx + index_delta) & 0x3] + delta;
    if (s->distance_code <= 0) {


      s->distance_code = 0x7FFFFFFF;
    }
  }
}

static inline int SafeReadBits(
    BrotliBitReader* const br, uint32_t n_bits, uint32_t* val) {
  if (n_bits != 0) {
    return BrotliSafeReadBits(br, n_bits, val);
  } else {
    *val = 0;
    return 1;
  }
}

static inline int SafeReadBits32(
    BrotliBitReader* const br, uint32_t n_bits, uint32_t* val) {
  if (n_bits != 0) {
    return BrotliSafeReadBits32(br, n_bits, val);
  } else {
    *val = 0;
    return 1;
  }
}
# 1583 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c"
static void CalculateDistanceLut(BrotliDecoderStateInternal* s) {
  BrotliMetablockBodyArena* b = &s->arena.body;
  uint32_t npostfix = s->distance_postfix_bits;
  uint32_t ndirect = s->num_direct_distance_codes;
  uint32_t alphabet_size_limit = s->distance_hgroup.alphabet_size_limit;
  uint32_t postfix = 1u << npostfix;
  uint32_t j;
  uint32_t bits = 1;
  uint32_t half = 0;


  uint32_t i = 16;


  for (j = 0; j < ndirect; ++j) {
    b->dist_extra_bits[i] = 0;
    b->dist_offset[i] = j + 1;
    ++i;
  }


  while (i < alphabet_size_limit) {
    uint32_t base = ndirect + ((((2 + half) << bits) - 4) << npostfix) + 1;

    for (j = 0; j < postfix; ++j) {
      b->dist_extra_bits[i] = (uint8_t)bits;
      b->dist_offset[i] = base + j;
      ++i;
    }
    bits = bits + half;
    half = half ^ 1;
  }
}


static inline int ReadDistanceInternal(
    int safe, BrotliDecoderStateInternal* s, BrotliBitReader* br) {
  BrotliMetablockBodyArena* b = &s->arena.body;
  uint32_t code;
  uint32_t bits;
  BrotliBitReaderState memento;
  HuffmanCode* distance_tree = s->distance_hgroup.htrees[s->dist_htree_index];
  if (!safe) {
    code = ReadSymbol(distance_tree, br);
  } else {
    BrotliBitReaderSaveState(br, &memento);
    if (!SafeReadSymbol(distance_tree, br, &code)) {
      return 0;
    }
  }
  --s->block_length[2];


  s->distance_context = 0;
  if ((code & ~0xFu) == 0) {
    s->distance_code = (int)code;
    TakeDistanceFromRingBuffer(s);
    return 1;
  }
  if (!safe) {
    bits = BrotliReadBits32(br, b->dist_extra_bits[code]);
  } else {
    if (!SafeReadBits32(br, b->dist_extra_bits[code], &bits)) {
      ++s->block_length[2];
      BrotliBitReaderRestoreState(br, &memento);
      return 0;
    }
  }
  s->distance_code =
      (int)(b->dist_offset[code] + (bits << s->distance_postfix_bits));
  return 1;
}

static inline void ReadDistance(
    BrotliDecoderStateInternal* s, BrotliBitReader* br) {
  ReadDistanceInternal(0, s, br);
}

static inline int SafeReadDistance(
    BrotliDecoderStateInternal* s, BrotliBitReader* br) {
  return ReadDistanceInternal(1, s, br);
}

static inline int ReadCommandInternal(
    int safe, BrotliDecoderStateInternal* s, BrotliBitReader* br, int* insert_length) {
  uint32_t cmd_code;
  uint32_t insert_len_extra = 0;
  uint32_t copy_length;
  CmdLutElement v;
  BrotliBitReaderState memento;
  if (!safe) {
    cmd_code = ReadSymbol(s->htree_command, br);
  } else {
    BrotliBitReaderSaveState(br, &memento);
    if (!SafeReadSymbol(s->htree_command, br, &cmd_code)) {
      return 0;
    }
  }
  v = kCmdLut[cmd_code];
  s->distance_code = v.distance_code;
  s->distance_context = v.context;
  s->dist_htree_index = s->dist_context_map_slice[s->distance_context];
  *insert_length = v.insert_len_offset;
  if (!safe) {
    if ((__builtin_expect(v.insert_len_extra_bits != 0, 0))) {
      insert_len_extra = BrotliReadBits24(br, v.insert_len_extra_bits);
    }
    copy_length = BrotliReadBits24(br, v.copy_len_extra_bits);
  } else {
    if (!SafeReadBits(br, v.insert_len_extra_bits, &insert_len_extra) ||
        !SafeReadBits(br, v.copy_len_extra_bits, &copy_length)) {
      BrotliBitReaderRestoreState(br, &memento);
      return 0;
    }
  }
  s->copy_length = (int)copy_length + v.copy_len_offset;
  --s->block_length[1];
  *insert_length += (int)insert_len_extra;
  return 1;
}

static inline void ReadCommand(
    BrotliDecoderStateInternal* s, BrotliBitReader* br, int* insert_length) {
  ReadCommandInternal(0, s, br, insert_length);
}

static inline int SafeReadCommand(
    BrotliDecoderStateInternal* s, BrotliBitReader* br, int* insert_length) {
  return ReadCommandInternal(1, s, br, insert_length);
}

static inline int CheckInputAmount(
    int safe, BrotliBitReader* const br, size_t num) {
  if (safe) {
    return 1;
  }
  return BrotliCheckInputAmount(br, num);
}
# 1734 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c"
static inline BrotliDecoderErrorCode ProcessCommandsInternal(
    int safe, BrotliDecoderStateInternal* s) {
  int pos = s->pos;
  int i = s->loop_counter;
  BrotliDecoderErrorCode result = BROTLI_DECODER_SUCCESS;
  BrotliBitReader* br = &s->br;

  if (!CheckInputAmount(safe, br, 28)) {
    result = BROTLI_DECODER_NEEDS_MORE_INPUT;
    goto saveStateAndReturn;
  }
  if (!safe) {
    (void)(BrotliWarmupBitReader(br));
  }


  if (s->state == BROTLI_STATE_COMMAND_BEGIN) {
    goto CommandBegin;
  } else if (s->state == BROTLI_STATE_COMMAND_INNER) {
    goto CommandInner;
  } else if (s->state == BROTLI_STATE_COMMAND_POST_DECODE_LITERALS) {
    goto CommandPostDecodeLiterals;
  } else if (s->state == BROTLI_STATE_COMMAND_POST_WRAP_COPY) {
    goto CommandPostWrapCopy;
  } else {
    return ((void)(0), BROTLI_DECODER_ERROR_UNREACHABLE);
  }

CommandBegin:
  if (safe) {
    s->state = BROTLI_STATE_COMMAND_BEGIN;
  }
  if (!CheckInputAmount(safe, br, 28)) {
    s->state = BROTLI_STATE_COMMAND_BEGIN;
    result = BROTLI_DECODER_NEEDS_MORE_INPUT;
    goto saveStateAndReturn;
  }
  if ((__builtin_expect(s->block_length[1] == 0, 0))) {
    { if (safe) { if (!SafeDecodeCommandBlockSwitch(s)) { result = BROTLI_DECODER_NEEDS_MORE_INPUT; goto saveStateAndReturn; } } else { DecodeCommandBlockSwitch(s); } };
    goto CommandBegin;
  }

  { if (safe) { if (!SafeReadCommand(s, br, &i)) { result = BROTLI_DECODER_NEEDS_MORE_INPUT; goto saveStateAndReturn; } } else { ReadCommand(s, br, &i); } };
 
                                      ;
  if (i == 0) {
    goto CommandPostDecodeLiterals;
  }
  s->meta_block_remaining_len -= i;

CommandInner:
  if (safe) {
    s->state = BROTLI_STATE_COMMAND_INNER;
  }

  if (s->trivial_literal_context) {
    uint32_t bits;
    uint32_t value;
    PreloadSymbol(safe, s->literal_htree, br, &bits, &value);
    do {
      if (!CheckInputAmount(safe, br, 28)) {
        s->state = BROTLI_STATE_COMMAND_INNER;
        result = BROTLI_DECODER_NEEDS_MORE_INPUT;
        goto saveStateAndReturn;
      }
      if ((__builtin_expect(s->block_length[0] == 0, 0))) {
        { if (safe) { if (!SafeDecodeLiteralBlockSwitch(s)) { result = BROTLI_DECODER_NEEDS_MORE_INPUT; goto saveStateAndReturn; } } else { DecodeLiteralBlockSwitch(s); } };
        PreloadSymbol(safe, s->literal_htree, br, &bits, &value);
        if (!s->trivial_literal_context) goto CommandInner;
      }
      if (!safe) {
        s->ringbuffer[pos] =
            (uint8_t)ReadPreloadedSymbol(s->literal_htree, br, &bits, &value);
      } else {
        uint32_t literal;
        if (!SafeReadSymbol(s->literal_htree, br, &literal)) {
          result = BROTLI_DECODER_NEEDS_MORE_INPUT;
          goto saveStateAndReturn;
        }
        s->ringbuffer[pos] = (uint8_t)literal;
      }
      --s->block_length[0];
      ;
      ++pos;
      if ((__builtin_expect(pos == s->ringbuffer_size, 0))) {
        s->state = BROTLI_STATE_COMMAND_INNER_WRITE;
        --i;
        goto saveStateAndReturn;
      }
    } while (--i != 0);
  } else {
    uint8_t p1 = s->ringbuffer[(pos - 1) & s->ringbuffer_mask];
    uint8_t p2 = s->ringbuffer[(pos - 2) & s->ringbuffer_mask];
    do {
      const HuffmanCode* hc;
      uint8_t context;
      if (!CheckInputAmount(safe, br, 28)) {
        s->state = BROTLI_STATE_COMMAND_INNER;
        result = BROTLI_DECODER_NEEDS_MORE_INPUT;
        goto saveStateAndReturn;
      }
      if ((__builtin_expect(s->block_length[0] == 0, 0))) {
        { if (safe) { if (!SafeDecodeLiteralBlockSwitch(s)) { result = BROTLI_DECODER_NEEDS_MORE_INPUT; goto saveStateAndReturn; } } else { DecodeLiteralBlockSwitch(s); } };
        if (s->trivial_literal_context) goto CommandInner;
      }
      context = ((s->context_lookup)[p1] | ((s->context_lookup) + 256)[p2]);
      ;
      hc = s->literal_hgroup.htrees[s->context_map_slice[context]];
      p2 = p1;
      if (!safe) {
        p1 = (uint8_t)ReadSymbol(hc, br);
      } else {
        uint32_t literal;
        if (!SafeReadSymbol(hc, br, &literal)) {
          result = BROTLI_DECODER_NEEDS_MORE_INPUT;
          goto saveStateAndReturn;
        }
        p1 = (uint8_t)literal;
      }
      s->ringbuffer[pos] = p1;
      --s->block_length[0];
      ;
      ;
      ++pos;
      if ((__builtin_expect(pos == s->ringbuffer_size, 0))) {
        s->state = BROTLI_STATE_COMMAND_INNER_WRITE;
        --i;
        goto saveStateAndReturn;
      }
    } while (--i != 0);
  }
  ;
  if ((__builtin_expect(s->meta_block_remaining_len <= 0, 0))) {
    s->state = BROTLI_STATE_METABLOCK_DONE;
    goto saveStateAndReturn;
  }

CommandPostDecodeLiterals:
  if (safe) {
    s->state = BROTLI_STATE_COMMAND_POST_DECODE_LITERALS;
  }
  if (s->distance_code >= 0) {

    s->distance_context = s->distance_code ? 0 : 1;
    --s->dist_rb_idx;
    s->distance_code = s->dist_rb[s->dist_rb_idx & 3];
  } else {

    if ((__builtin_expect(s->block_length[2] == 0, 0))) {
      { if (safe) { if (!SafeDecodeDistanceBlockSwitch(s)) { result = BROTLI_DECODER_NEEDS_MORE_INPUT; goto saveStateAndReturn; } } else { DecodeDistanceBlockSwitch(s); } };
    }
    { if (safe) { if (!SafeReadDistance(s, br)) { result = BROTLI_DECODER_NEEDS_MORE_INPUT; goto saveStateAndReturn; } } else { ReadDistance(s, br); } };
  }
 
                                     ;
  if (s->max_distance != s->max_backward_distance) {
    s->max_distance =
        (pos < s->max_backward_distance) ? pos : s->max_backward_distance;
  }
  i = s->copy_length;


  if (s->distance_code > s->max_distance) {



    if (s->distance_code > 0x7FFFFFFC) {
     

                                                                 ;
      return ((void)(0), BROTLI_DECODER_ERROR_FORMAT_DISTANCE);
    }
    if (i >= 4 &&
        i <= 24) {
      int address = s->distance_code - s->max_distance - 1;
      const BrotliDictionary* words = s->dictionary;
      const BrotliTransforms* transforms = s->transforms;
      int offset = (int)s->dictionary->offsets_by_length[i];
      uint32_t shift = s->dictionary->size_bits_by_length[i];

      int mask = (int)BitMask(shift);
      int word_idx = address & mask;
      int transform_idx = address >> shift;

      s->dist_rb_idx += s->distance_context;
      offset += word_idx * i;
      if ((__builtin_expect(!words->data, 0))) {
        return ((void)(0), BROTLI_DECODER_ERROR_DICTIONARY_NOT_SET);
      }
      if (transform_idx < (int)transforms->num_transforms) {
        const uint8_t* word = &words->data[offset];
        int len = i;
        if (transform_idx == transforms->cutOffTransforms[0]) {
          memcpy(&s->ringbuffer[pos], word, (size_t)len);
         
                                 ;
        } else {
          len = BrotliTransformDictionaryWord(&s->ringbuffer[pos], word, len,
              transforms, transform_idx);
         

                                                                        ;
        }
        pos += len;
        s->meta_block_remaining_len -= len;
        if (pos >= s->ringbuffer_size) {
          s->state = BROTLI_STATE_COMMAND_POST_WRITE_1;
          goto saveStateAndReturn;
        }
      } else {
       

                                                                   ;
        return ((void)(0), BROTLI_DECODER_ERROR_FORMAT_TRANSFORM);
      }
    } else {
     

                                                                 ;
      return ((void)(0), BROTLI_DECODER_ERROR_FORMAT_DICTIONARY);
    }
  } else {
    int src_start = (pos - s->distance_code) & s->ringbuffer_mask;
    uint8_t* copy_dst = &s->ringbuffer[pos];
    uint8_t* copy_src = &s->ringbuffer[src_start];
    int dst_end = pos + i;
    int src_end = src_start + i;

    s->dist_rb[s->dist_rb_idx & 3] = s->distance_code;
    ++s->dist_rb_idx;
    s->meta_block_remaining_len -= i;



    memmove16(copy_dst, copy_src);
    if (src_end > pos && dst_end > src_start) {

      goto CommandPostWrapCopy;
    }
    if (dst_end >= s->ringbuffer_size || src_end >= s->ringbuffer_size) {

      goto CommandPostWrapCopy;
    }
    pos += i;
    if (i > 16) {
      if (i > 32) {
        memcpy(copy_dst + 16, copy_src + 16, (size_t)(i - 16));
      } else {


        memmove16(copy_dst + 16, copy_src + 16);
      }
    }
  }
  ;
  if (s->meta_block_remaining_len <= 0) {

    s->state = BROTLI_STATE_METABLOCK_DONE;
    goto saveStateAndReturn;
  } else {
    goto CommandBegin;
  }
CommandPostWrapCopy:
  {
    int wrap_guard = s->ringbuffer_size - pos;
    while (--i >= 0) {
      s->ringbuffer[pos] =
          s->ringbuffer[(pos - s->distance_code) & s->ringbuffer_mask];
      ++pos;
      if ((__builtin_expect(--wrap_guard == 0, 0))) {
        s->state = BROTLI_STATE_COMMAND_POST_WRITE_2;
        goto saveStateAndReturn;
      }
    }
  }
  if (s->meta_block_remaining_len <= 0) {

    s->state = BROTLI_STATE_METABLOCK_DONE;
    goto saveStateAndReturn;
  } else {
    goto CommandBegin;
  }

saveStateAndReturn:
  s->pos = pos;
  s->loop_counter = i;
  return result;
}



static BrotliDecoderErrorCode ProcessCommands(
    BrotliDecoderStateInternal* s) {
  return ProcessCommandsInternal(0, s);
}

static BrotliDecoderErrorCode SafeProcessCommands(
    BrotliDecoderStateInternal* s) {
  return ProcessCommandsInternal(1, s);
}

BrotliDecoderResult BrotliDecoderDecompress(
    size_t encoded_size, const uint8_t* encoded_buffer, size_t* decoded_size,
    uint8_t* decoded_buffer) {
  BrotliDecoderStateInternal s;
  BrotliDecoderResult result;
  size_t total_out = 0;
  size_t available_in = encoded_size;
  const uint8_t* next_in = encoded_buffer;
  size_t available_out = *decoded_size;
  uint8_t* next_out = decoded_buffer;
  if (!BrotliDecoderStateInit(&s, 0, 0, 0)) {
    return BROTLI_DECODER_RESULT_ERROR;
  }
  result = BrotliDecoderDecompressStream(
      &s, &available_in, &next_in, &available_out, &next_out, &total_out);
  *decoded_size = total_out;
  BrotliDecoderStateCleanup(&s);
  if (result != BROTLI_DECODER_RESULT_SUCCESS) {
    result = BROTLI_DECODER_RESULT_ERROR;
  }
  return result;
}
# 2069 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/dec/decode.c"
BrotliDecoderResult BrotliDecoderDecompressStream(
    BrotliDecoderStateInternal* s, size_t* available_in, const uint8_t** next_in,
    size_t* available_out, uint8_t** next_out, size_t* total_out) {
  BrotliDecoderErrorCode result = BROTLI_DECODER_SUCCESS;
  BrotliBitReader* br = &s->br;

  if (total_out) {
    *total_out = s->partial_pos_out;
  }

  if ((int)s->error_code < 0) {
    return BROTLI_DECODER_RESULT_ERROR;
  }
  if (*available_out && (!next_out || !*next_out)) {
    return SaveErrorCode(
        s, ((void)(0), BROTLI_DECODER_ERROR_INVALID_ARGUMENTS));
  }
  if (!*available_out) next_out = 0;
  if (s->buffer_length == 0) {
    br->avail_in = *available_in;
    br->next_in = *next_in;
  } else {



    result = BROTLI_DECODER_NEEDS_MORE_INPUT;
    br->next_in = &s->buffer.u8[0];
  }

  for (;;) {
    if (result != BROTLI_DECODER_SUCCESS) {

      if (result == BROTLI_DECODER_NEEDS_MORE_INPUT) {
        if (s->ringbuffer != 0) {
          BrotliDecoderErrorCode intermediate_result = WriteRingBuffer(s,
              available_out, next_out, total_out, 1);

          if ((int)intermediate_result < 0) {
            result = intermediate_result;
            break;
          }
        }
        if (s->buffer_length != 0) {
          if (br->avail_in == 0) {



            s->buffer_length = 0;

            result = BROTLI_DECODER_SUCCESS;
            br->avail_in = *available_in;
            br->next_in = *next_in;
            continue;
          } else if (*available_in != 0) {


            result = BROTLI_DECODER_SUCCESS;
            s->buffer.u8[s->buffer_length] = **next_in;
            s->buffer_length++;
            br->avail_in = s->buffer_length;
            (*next_in)++;
            (*available_in)--;

            continue;
          }

          break;
        } else {

          *next_in = br->next_in;
          *available_in = br->avail_in;
          while (*available_in) {
            s->buffer.u8[s->buffer_length] = **next_in;
            s->buffer_length++;
            (*next_in)++;
            (*available_in)--;
          }
          break;
        }

      }



      if (s->buffer_length != 0) {


        s->buffer_length = 0;
      } else {



        BrotliBitReaderUnload(br);
        *available_in = br->avail_in;
        *next_in = br->next_in;
      }
      break;
    }
    switch (s->state) {
      case BROTLI_STATE_UNINITED:

        if (!BrotliWarmupBitReader(br)) {
          result = BROTLI_DECODER_NEEDS_MORE_INPUT;
          break;
        }

        result = DecodeWindowBits(s, br);
        if (result != BROTLI_DECODER_SUCCESS) {
          break;
        }
        if (s->large_window) {
          s->state = BROTLI_STATE_LARGE_WINDOW_BITS;
          break;
        }
        s->state = BROTLI_STATE_INITIALIZE;
        break;

      case BROTLI_STATE_LARGE_WINDOW_BITS:
        if (!BrotliSafeReadBits(br, 6, &s->window_bits)) {
          result = BROTLI_DECODER_NEEDS_MORE_INPUT;
          break;
        }
        if (s->window_bits < 10 ||
            s->window_bits > 30) {
          result = ((void)(0), BROTLI_DECODER_ERROR_FORMAT_WINDOW_BITS);
          break;
        }
        s->state = BROTLI_STATE_INITIALIZE;


      case BROTLI_STATE_INITIALIZE:
        ;

        s->max_backward_distance = (1 << s->window_bits) - 16;


        s->block_type_trees = (HuffmanCode*)s->alloc_func(s->memory_manager_opaque, sizeof(HuffmanCode) * 3 * (632 + 396))

                                                                           ;
        if (s->block_type_trees == 0) {
          result = ((void)(0), BROTLI_DECODER_ERROR_ALLOC_BLOCK_TYPE_TREES);
          break;
        }
        s->block_len_trees =
            s->block_type_trees + 3 * 632;

        s->state = BROTLI_STATE_METABLOCK_BEGIN;


      case BROTLI_STATE_METABLOCK_BEGIN:
        BrotliDecoderStateMetablockBegin(s);
        ;
        s->state = BROTLI_STATE_METABLOCK_HEADER;


      case BROTLI_STATE_METABLOCK_HEADER:
        result = DecodeMetaBlockLength(s, br);
        if (result != BROTLI_DECODER_SUCCESS) {
          break;
        }
        ;
        ;
        ;
        ;
        if (s->is_metadata || s->is_uncompressed) {
          if (!BrotliJumpToByteBoundary(br)) {
            result = ((void)(0), BROTLI_DECODER_ERROR_FORMAT_PADDING_1);
            break;
          }
        }
        if (s->is_metadata) {
          s->state = BROTLI_STATE_METADATA;
          break;
        }
        if (s->meta_block_remaining_len == 0) {
          s->state = BROTLI_STATE_METABLOCK_DONE;
          break;
        }
        BrotliCalculateRingBufferSize(s);
        if (s->is_uncompressed) {
          s->state = BROTLI_STATE_UNCOMPRESSED;
          break;
        }
        s->state = BROTLI_STATE_BEFORE_COMPRESSED_METABLOCK_HEADER;


      case BROTLI_STATE_BEFORE_COMPRESSED_METABLOCK_HEADER: {
        BrotliMetablockHeaderArena* h = &s->arena.header;
        s->loop_counter = 0;

        h->sub_loop_counter = 0;

        h->symbol_lists =
            &h->symbols_lists_array[15 + 1];
        h->substate_huffman = BROTLI_STATE_HUFFMAN_NONE;
        h->substate_tree_group = BROTLI_STATE_TREE_GROUP_NONE;
        h->substate_context_map = BROTLI_STATE_CONTEXT_MAP_NONE;
        s->state = BROTLI_STATE_HUFFMAN_CODE_0;
      }


      case BROTLI_STATE_HUFFMAN_CODE_0:
        if (s->loop_counter >= 3) {
          s->state = BROTLI_STATE_METABLOCK_HEADER_2;
          break;
        }

        result = DecodeVarLenUint8(s, br, &s->num_block_types[s->loop_counter]);
        if (result != BROTLI_DECODER_SUCCESS) {
          break;
        }
        s->num_block_types[s->loop_counter]++;
        ;
        if (s->num_block_types[s->loop_counter] < 2) {
          s->loop_counter++;
          break;
        }
        s->state = BROTLI_STATE_HUFFMAN_CODE_1;


      case BROTLI_STATE_HUFFMAN_CODE_1: {
        uint32_t alphabet_size = s->num_block_types[s->loop_counter] + 2;
        int tree_offset = s->loop_counter * 632;
        result = ReadHuffmanCode(alphabet_size, alphabet_size,
            &s->block_type_trees[tree_offset], 0, s);
        if (result != BROTLI_DECODER_SUCCESS) break;
        s->state = BROTLI_STATE_HUFFMAN_CODE_2;
      }


      case BROTLI_STATE_HUFFMAN_CODE_2: {
        uint32_t alphabet_size = 26;
        int tree_offset = s->loop_counter * 396;
        result = ReadHuffmanCode(alphabet_size, alphabet_size,
            &s->block_len_trees[tree_offset], 0, s);
        if (result != BROTLI_DECODER_SUCCESS) break;
        s->state = BROTLI_STATE_HUFFMAN_CODE_3;
      }


      case BROTLI_STATE_HUFFMAN_CODE_3: {
        int tree_offset = s->loop_counter * 396;
        if (!SafeReadBlockLength(s, &s->block_length[s->loop_counter],
            &s->block_len_trees[tree_offset], br)) {
          result = BROTLI_DECODER_NEEDS_MORE_INPUT;
          break;
        }
        ;
        s->loop_counter++;
        s->state = BROTLI_STATE_HUFFMAN_CODE_0;
        break;
      }

      case BROTLI_STATE_UNCOMPRESSED: {
        result = CopyUncompressedBlockToOutput(
            available_out, next_out, total_out, s);
        if (result != BROTLI_DECODER_SUCCESS) {
          break;
        }
        s->state = BROTLI_STATE_METABLOCK_DONE;
        break;
      }

      case BROTLI_STATE_METADATA:
        for (; s->meta_block_remaining_len > 0; --s->meta_block_remaining_len) {
          uint32_t bits;

          if (!BrotliSafeReadBits(br, 8, &bits)) {
            result = BROTLI_DECODER_NEEDS_MORE_INPUT;
            break;
          }
        }
        if (result == BROTLI_DECODER_SUCCESS) {
          s->state = BROTLI_STATE_METABLOCK_DONE;
        }
        break;

      case BROTLI_STATE_METABLOCK_HEADER_2: {
        uint32_t bits;
        if (!BrotliSafeReadBits(br, 6, &bits)) {
          result = BROTLI_DECODER_NEEDS_MORE_INPUT;
          break;
        }
        s->distance_postfix_bits = bits & BitMask(2);
        bits >>= 2;
        s->num_direct_distance_codes = bits << s->distance_postfix_bits;
        ;
        ;
        s->context_modes =
            (uint8_t*)s->alloc_func(s->memory_manager_opaque, (size_t)s->num_block_types[0]);
        if (s->context_modes == 0) {
          result = ((void)(0), BROTLI_DECODER_ERROR_ALLOC_CONTEXT_MODES);
          break;
        }
        s->loop_counter = 0;
        s->state = BROTLI_STATE_CONTEXT_MODES;
      }


      case BROTLI_STATE_CONTEXT_MODES:
        result = ReadContextModes(s);
        if (result != BROTLI_DECODER_SUCCESS) {
          break;
        }
        s->state = BROTLI_STATE_CONTEXT_MAP_1;


      case BROTLI_STATE_CONTEXT_MAP_1:
        result = DecodeContextMap(
            s->num_block_types[0] << 6,
            &s->num_literal_htrees, &s->context_map, s);
        if (result != BROTLI_DECODER_SUCCESS) {
          break;
        }
        DetectTrivialLiteralBlockTypes(s);
        s->state = BROTLI_STATE_CONTEXT_MAP_2;


      case BROTLI_STATE_CONTEXT_MAP_2: {
        uint32_t npostfix = s->distance_postfix_bits;
        uint32_t ndirect = s->num_direct_distance_codes;
        uint32_t distance_alphabet_size_max = ( 16 + (ndirect) + ((24U) << ((npostfix) + 1)))
                                                        ;
        uint32_t distance_alphabet_size_limit = distance_alphabet_size_max;
        int allocation_success = 1;
        if (s->large_window) {
          BrotliDistanceCodeLimit limit = BrotliCalculateDistanceCodeLimit(
              0x7FFFFFFC, npostfix, ndirect);
          distance_alphabet_size_max = ( 16 + (ndirect) + ((62U) << ((npostfix) + 1)))
                                                                ;
          distance_alphabet_size_limit = limit.max_alphabet_size;
        }
        result = DecodeContextMap(
            s->num_block_types[2] << 2,
            &s->num_dist_htrees, &s->dist_context_map, s);
        if (result != BROTLI_DECODER_SUCCESS) {
          break;
        }
        allocation_success &= BrotliDecoderHuffmanTreeGroupInit(
            s, &s->literal_hgroup, 256,
            256, s->num_literal_htrees);
        allocation_success &= BrotliDecoderHuffmanTreeGroupInit(
            s, &s->insert_copy_hgroup, 704,
            704, s->num_block_types[1]);
        allocation_success &= BrotliDecoderHuffmanTreeGroupInit(
            s, &s->distance_hgroup, distance_alphabet_size_max,
            distance_alphabet_size_limit, s->num_dist_htrees);
        if (!allocation_success) {
          return SaveErrorCode(s,
              ((void)(0), BROTLI_DECODER_ERROR_ALLOC_TREE_GROUPS));
        }
        s->loop_counter = 0;
        s->state = BROTLI_STATE_TREE_GROUP;
      }


      case BROTLI_STATE_TREE_GROUP: {
        HuffmanTreeGroup* hgroup = 0;
        switch (s->loop_counter) {
          case 0: hgroup = &s->literal_hgroup; break;
          case 1: hgroup = &s->insert_copy_hgroup; break;
          case 2: hgroup = &s->distance_hgroup; break;
          default: return SaveErrorCode(s, ((void)(0), BROTLI_DECODER_ERROR_UNREACHABLE)
                                               );
        }
        result = HuffmanTreeGroupDecode(hgroup, s);
        if (result != BROTLI_DECODER_SUCCESS) break;
        s->loop_counter++;
        if (s->loop_counter < 3) {
          break;
        }
        s->state = BROTLI_STATE_BEFORE_COMPRESSED_METABLOCK_BODY;
      }


      case BROTLI_STATE_BEFORE_COMPRESSED_METABLOCK_BODY:
        PrepareLiteralDecoding(s);
        s->dist_context_map_slice = s->dist_context_map;
        s->htree_command = s->insert_copy_hgroup.htrees[0];
        if (!BrotliEnsureRingBuffer(s)) {
          result = ((void)(0), BROTLI_DECODER_ERROR_ALLOC_RING_BUFFER_2);
          break;
        }
        CalculateDistanceLut(s);
        s->state = BROTLI_STATE_COMMAND_BEGIN;


      case BROTLI_STATE_COMMAND_BEGIN:

      case BROTLI_STATE_COMMAND_INNER:

      case BROTLI_STATE_COMMAND_POST_DECODE_LITERALS:

      case BROTLI_STATE_COMMAND_POST_WRAP_COPY:
        result = ProcessCommands(s);
        if (result == BROTLI_DECODER_NEEDS_MORE_INPUT) {
          result = SafeProcessCommands(s);
        }
        break;

      case BROTLI_STATE_COMMAND_INNER_WRITE:

      case BROTLI_STATE_COMMAND_POST_WRITE_1:

      case BROTLI_STATE_COMMAND_POST_WRITE_2:
        result = WriteRingBuffer(
            s, available_out, next_out, total_out, 0);
        if (result != BROTLI_DECODER_SUCCESS) {
          break;
        }
        WrapRingBuffer(s);
        if (s->ringbuffer_size == 1 << s->window_bits) {
          s->max_distance = s->max_backward_distance;
        }
        if (s->state == BROTLI_STATE_COMMAND_POST_WRITE_1) {
          if (s->meta_block_remaining_len == 0) {

            s->state = BROTLI_STATE_METABLOCK_DONE;
          } else {
            s->state = BROTLI_STATE_COMMAND_BEGIN;
          }
          break;
        } else if (s->state == BROTLI_STATE_COMMAND_POST_WRITE_2) {
          s->state = BROTLI_STATE_COMMAND_POST_WRAP_COPY;
        } else {
          if (s->loop_counter == 0) {
            if (s->meta_block_remaining_len == 0) {
              s->state = BROTLI_STATE_METABLOCK_DONE;
            } else {
              s->state = BROTLI_STATE_COMMAND_POST_DECODE_LITERALS;
            }
            break;
          }
          s->state = BROTLI_STATE_COMMAND_INNER;
        }
        break;

      case BROTLI_STATE_METABLOCK_DONE:
        if (s->meta_block_remaining_len < 0) {
          result = ((void)(0), BROTLI_DECODER_ERROR_FORMAT_BLOCK_LENGTH_2);
          break;
        }
        BrotliDecoderStateCleanupAfterMetablock(s);
        if (!s->is_last_metablock) {
          s->state = BROTLI_STATE_METABLOCK_BEGIN;
          break;
        }
        if (!BrotliJumpToByteBoundary(br)) {
          result = ((void)(0), BROTLI_DECODER_ERROR_FORMAT_PADDING_2);
          break;
        }
        if (s->buffer_length == 0) {
          BrotliBitReaderUnload(br);
          *available_in = br->avail_in;
          *next_in = br->next_in;
        }
        s->state = BROTLI_STATE_DONE;


      case BROTLI_STATE_DONE:
        if (s->ringbuffer != 0) {
          result = WriteRingBuffer(
              s, available_out, next_out, total_out, 1);
          if (result != BROTLI_DECODER_SUCCESS) {
            break;
          }
        }
        return SaveErrorCode(s, result);
    }
  }
  return SaveErrorCode(s, result);
}

int BrotliDecoderHasMoreOutput(const BrotliDecoderStateInternal* s) {

  if ((int)s->error_code < 0) {
    return 0;
  }
  return (!!(s->ringbuffer != 0 && UnwrittenBytes(s, 0) != 0) ? 1 : 0)
                                                                 ;
}

const uint8_t* BrotliDecoderTakeOutput(BrotliDecoderStateInternal* s, size_t* size) {
  uint8_t* result = 0;
  size_t available_out = *size ? *size : 1u << 24;
  size_t requested_out = available_out;
  BrotliDecoderErrorCode status;
  if ((s->ringbuffer == 0) || ((int)s->error_code < 0)) {
    *size = 0;
    return 0;
  }
  WrapRingBuffer(s);
  status = WriteRingBuffer(s, &available_out, &result, 0, 1);

  if (status == BROTLI_DECODER_SUCCESS ||
      status == BROTLI_DECODER_NEEDS_MORE_OUTPUT) {
    *size = requested_out - available_out;
  } else {


    if ((int)status < 0) SaveErrorCode(s, status);
    *size = 0;
    result = 0;
  }
  return result;
}

int BrotliDecoderIsUsed(const BrotliDecoderStateInternal* s) {
  return (!!(s->state != BROTLI_STATE_UNINITED || BrotliGetAvailableBits(&s->br) != 0) ? 1 : 0)
                                          ;
}

int BrotliDecoderIsFinished(const BrotliDecoderStateInternal* s) {
  return (!!(s->state == BROTLI_STATE_DONE) ? 1 : 0) &&
      !BrotliDecoderHasMoreOutput(s);
}

BrotliDecoderErrorCode BrotliDecoderGetErrorCode(const BrotliDecoderStateInternal* s) {
  return (BrotliDecoderErrorCode)s->error_code;
}

const char* BrotliDecoderErrorString(BrotliDecoderErrorCode c) {
  switch (c) {



    case BROTLI_DECODER_NO_ERROR: return "NO_ERROR"; case BROTLI_DECODER_SUCCESS: return "SUCCESS"; case BROTLI_DECODER_NEEDS_MORE_INPUT: return "NEEDS_MORE_INPUT"; case BROTLI_DECODER_NEEDS_MORE_OUTPUT: return "NEEDS_MORE_OUTPUT"; case BROTLI_DECODER_ERROR_FORMAT_EXUBERANT_NIBBLE: return "EXUBERANT_NIBBLE"; case BROTLI_DECODER_ERROR_FORMAT_RESERVED: return "RESERVED"; case BROTLI_DECODER_ERROR_FORMAT_EXUBERANT_META_NIBBLE: return "EXUBERANT_META_NIBBLE"; case BROTLI_DECODER_ERROR_FORMAT_SIMPLE_HUFFMAN_ALPHABET: return "SIMPLE_HUFFMAN_ALPHABET"; case BROTLI_DECODER_ERROR_FORMAT_SIMPLE_HUFFMAN_SAME: return "SIMPLE_HUFFMAN_SAME"; case BROTLI_DECODER_ERROR_FORMAT_CL_SPACE: return "CL_SPACE"; case BROTLI_DECODER_ERROR_FORMAT_HUFFMAN_SPACE: return "HUFFMAN_SPACE"; case BROTLI_DECODER_ERROR_FORMAT_CONTEXT_MAP_REPEAT: return "CONTEXT_MAP_REPEAT"; case BROTLI_DECODER_ERROR_FORMAT_BLOCK_LENGTH_1: return "BLOCK_LENGTH_1"; case BROTLI_DECODER_ERROR_FORMAT_BLOCK_LENGTH_2: return "BLOCK_LENGTH_2"; case BROTLI_DECODER_ERROR_FORMAT_TRANSFORM: return "TRANSFORM"; case BROTLI_DECODER_ERROR_FORMAT_DICTIONARY: return "DICTIONARY"; case BROTLI_DECODER_ERROR_FORMAT_WINDOW_BITS: return "WINDOW_BITS"; case BROTLI_DECODER_ERROR_FORMAT_PADDING_1: return "PADDING_1"; case BROTLI_DECODER_ERROR_FORMAT_PADDING_2: return "PADDING_2"; case BROTLI_DECODER_ERROR_FORMAT_DISTANCE: return "DISTANCE"; case BROTLI_DECODER_ERROR_DICTIONARY_NOT_SET: return "DICTIONARY_NOT_SET"; case BROTLI_DECODER_ERROR_INVALID_ARGUMENTS: return "INVALID_ARGUMENTS"; case BROTLI_DECODER_ERROR_ALLOC_CONTEXT_MODES: return "CONTEXT_MODES"; case BROTLI_DECODER_ERROR_ALLOC_TREE_GROUPS: return "TREE_GROUPS"; case BROTLI_DECODER_ERROR_ALLOC_CONTEXT_MAP: return "CONTEXT_MAP"; case BROTLI_DECODER_ERROR_ALLOC_RING_BUFFER_1: return "RING_BUFFER_1"; case BROTLI_DECODER_ERROR_ALLOC_RING_BUFFER_2: return "RING_BUFFER_2"; case BROTLI_DECODER_ERROR_ALLOC_BLOCK_TYPE_TREES: return "BLOCK_TYPE_TREES"; case BROTLI_DECODER_ERROR_UNREACHABLE: return "UNREACHABLE";


    default: return "INVALID";
  }
}

uint32_t BrotliDecoderVersion() {
  return 0x1000009;
}
