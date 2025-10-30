# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/literal_cost.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/literal_cost.c"
# 10 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/literal_cost.c"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./literal_cost.h" 1
# 13 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./literal_cost.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./../common/platform.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./../common/platform.h"
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
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./../common/platform.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/port.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./../common/platform.h" 2
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
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./../common/platform.h" 2
# 340 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./../common/platform.h"
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
# 502 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./../common/platform.h"
static inline void BrotliRBit(void) { }
# 516 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./../common/platform.h"
static inline double brotli_min_double (double a, double b) { return a < b ? a : b; } static inline double brotli_max_double (double a, double b) { return a > b ? a : b; } static inline float brotli_min_float (float a, float b) { return a < b ? a : b; } static inline float brotli_max_float (float a, float b) { return a > b ? a : b; } static inline int brotli_min_int (int a, int b) { return a < b ? a : b; } static inline int brotli_max_int (int a, int b) { return a > b ? a : b; }
static inline size_t brotli_min_size_t (size_t a, size_t b) { return a < b ? a : b; } static inline size_t brotli_max_size_t (size_t a, size_t b) { return a > b ? a : b; } static inline uint32_t brotli_min_uint32_t (uint32_t a, uint32_t b) { return a < b ? a : b; } static inline uint32_t brotli_max_uint32_t (uint32_t a, uint32_t b) { return a > b ? a : b; } static inline uint8_t brotli_min_uint8_t (uint8_t a, uint8_t b) { return a < b ? a : b; } static inline uint8_t brotli_max_uint8_t (uint8_t a, uint8_t b) { return a > b ? a : b; }
# 559 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./../common/platform.h"
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
# 14 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./literal_cost.h" 2
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./literal_cost.h"
 void BrotliEstimateBitCostsForLiterals(
    size_t pos, size_t len, size_t mask, const uint8_t* data, float* cost);
# 11 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/literal_cost.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/../common/platform.h" 1
# 13 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/literal_cost.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./fast_log.h" 1
# 12 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./fast_log.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/math.h" 1
# 13 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./fast_log.h" 2
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./fast_log.h"
static inline uint32_t Log2FloorNonZero(size_t n) {

  return (31u ^ (uint32_t)__builtin_clz((uint32_t)n));





}





 extern const double kBrotliLog2Table[256];
# 51 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./fast_log.h"
static inline double FastLog2(size_t v) {
  if (v < 256) {
    return kBrotliLog2Table[v];
  }



  return log2((double)v);

}
# 15 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/literal_cost.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./utf8_util.h" 1
# 19 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./utf8_util.h"
static const double kMinUTF8Ratio = 0.75;




 int BrotliIsMostlyUTF8(
    const uint8_t* data, const size_t pos, const size_t mask,
    const size_t length, const double min_fraction);
# 16 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/literal_cost.c" 2





static size_t UTF8Position(size_t last, size_t c, size_t clamp) {
  if (c < 128) {
    return 0;
  } else if (c >= 192) {
    return (brotli_min_size_t((1), (clamp)));
  } else {

    if (last < 0xE0) {
      return 0;
    } else {
      return (brotli_min_size_t((2), (clamp)));
    }
  }
}

static size_t DecideMultiByteStatsLevel(size_t pos, size_t len, size_t mask,
                                        const uint8_t* data) {
  size_t counts[3] = { 0 };
  size_t max_utf8 = 1;
  size_t last_c = 0;
  size_t i;
  for (i = 0; i < len; ++i) {
    size_t c = data[(pos + i) & mask];
    ++counts[UTF8Position(last_c, c, 2)];
    last_c = c;
  }
  if (counts[2] < 500) {
    max_utf8 = 1;
  }
  if (counts[1] + counts[2] < 25) {
    max_utf8 = 0;
  }
  return max_utf8;
}

static void EstimateBitCostsForLiteralsUTF8(size_t pos, size_t len, size_t mask,
                                            const uint8_t* data, float* cost) {


  const size_t max_utf8 = DecideMultiByteStatsLevel(pos, len, mask, data);
  size_t histogram[3][256] = { { 0 } };
  size_t window_half = 495;
  size_t in_window = (brotli_min_size_t((window_half), (len)));
  size_t in_window_utf8[3] = { 0 };

  size_t i;
  {
    size_t last_c = 0;
    size_t utf8_pos = 0;
    for (i = 0; i < in_window; ++i) {
      size_t c = data[(pos + i) & mask];
      ++histogram[utf8_pos][c];
      ++in_window_utf8[utf8_pos];
      utf8_pos = UTF8Position(last_c, c, max_utf8);
      last_c = c;
    }
  }


  for (i = 0; i < len; ++i) {
    if (i >= window_half) {

      size_t c =
          i < window_half + 1 ? 0 : data[(pos + i - window_half - 1) & mask];
      size_t last_c =
          i < window_half + 2 ? 0 : data[(pos + i - window_half - 2) & mask];
      size_t utf8_pos2 = UTF8Position(last_c, c, max_utf8);
      --histogram[utf8_pos2][data[(pos + i - window_half) & mask]];
      --in_window_utf8[utf8_pos2];
    }
    if (i + window_half < len) {

      size_t c = data[(pos + i + window_half - 1) & mask];
      size_t last_c = data[(pos + i + window_half - 2) & mask];
      size_t utf8_pos2 = UTF8Position(last_c, c, max_utf8);
      ++histogram[utf8_pos2][data[(pos + i + window_half) & mask]];
      ++in_window_utf8[utf8_pos2];
    }
    {
      size_t c = i < 1 ? 0 : data[(pos + i - 1) & mask];
      size_t last_c = i < 2 ? 0 : data[(pos + i - 2) & mask];
      size_t utf8_pos = UTF8Position(last_c, c, max_utf8);
      size_t masked_pos = (pos + i) & mask;
      size_t histo = histogram[utf8_pos][data[masked_pos]];
      double lit_cost;
      if (histo == 0) {
        histo = 1;
      }
      lit_cost = FastLog2(in_window_utf8[utf8_pos]) - FastLog2(histo);
      lit_cost += 0.02905;
      if (lit_cost < 1.0) {
        lit_cost *= 0.5;
        lit_cost += 0.5;
      }




      if (i < 2000) {
        lit_cost += 0.7 - ((double)(2000 - i) / 2000.0 * 0.35);
      }
      cost[i] = (float)lit_cost;
    }
  }
}

void BrotliEstimateBitCostsForLiterals(size_t pos, size_t len, size_t mask,
                                       const uint8_t* data, float* cost) {
  if (BrotliIsMostlyUTF8(data, pos, mask, len, kMinUTF8Ratio)) {
    EstimateBitCostsForLiteralsUTF8(pos, len, mask, data, cost);
    return;
  } else {
    size_t histogram[256] = { 0 };
    size_t window_half = 2000;
    size_t in_window = (brotli_min_size_t((window_half), (len)));


    size_t i;
    for (i = 0; i < in_window; ++i) {
      ++histogram[data[(pos + i) & mask]];
    }


    for (i = 0; i < len; ++i) {
      size_t histo;
      if (i >= window_half) {

        --histogram[data[(pos + i - window_half) & mask]];
        --in_window;
      }
      if (i + window_half < len) {

        ++histogram[data[(pos + i + window_half) & mask]];
        ++in_window;
      }
      histo = histogram[data[(pos + i) & mask]];
      if (histo == 0) {
        histo = 1;
      }
      {
        double lit_cost = FastLog2(in_window) - FastLog2(histo);
        lit_cost += 0.029;
        if (lit_cost < 1.0) {
          lit_cost *= 0.5;
          lit_cost += 0.5;
        }
        cost[i] = (float)lit_cost;
      }
    }
  }
}
# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/literal_cost.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/literal_cost.c"
# 10 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/literal_cost.c"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./literal_cost.h" 1
# 13 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./literal_cost.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./../common/platform.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./../common/platform.h"
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
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./../common/platform.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/include/brotli/port.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./../common/platform.h" 2
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
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./../common/platform.h" 2
# 340 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./../common/platform.h"
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
# 502 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./../common/platform.h"
static inline void BrotliRBit(void) { }
# 516 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./../common/platform.h"
static inline double brotli_min_double (double a, double b) { return a < b ? a : b; } static inline double brotli_max_double (double a, double b) { return a > b ? a : b; } static inline float brotli_min_float (float a, float b) { return a < b ? a : b; } static inline float brotli_max_float (float a, float b) { return a > b ? a : b; } static inline int brotli_min_int (int a, int b) { return a < b ? a : b; } static inline int brotli_max_int (int a, int b) { return a > b ? a : b; }
static inline size_t brotli_min_size_t (size_t a, size_t b) { return a < b ? a : b; } static inline size_t brotli_max_size_t (size_t a, size_t b) { return a > b ? a : b; } static inline uint32_t brotli_min_uint32_t (uint32_t a, uint32_t b) { return a < b ? a : b; } static inline uint32_t brotli_max_uint32_t (uint32_t a, uint32_t b) { return a > b ? a : b; } static inline uint8_t brotli_min_uint8_t (uint8_t a, uint8_t b) { return a < b ? a : b; } static inline uint8_t brotli_max_uint8_t (uint8_t a, uint8_t b) { return a > b ? a : b; }
# 559 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./../common/platform.h"
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
# 14 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./literal_cost.h" 2
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./literal_cost.h"
 void BrotliEstimateBitCostsForLiterals(
    size_t pos, size_t len, size_t mask, const uint8_t* data, float* cost);
# 11 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/literal_cost.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/../common/platform.h" 1
# 13 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/literal_cost.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./fast_log.h" 1
# 12 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./fast_log.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/math.h" 1
# 13 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./fast_log.h" 2
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./fast_log.h"
static inline uint32_t Log2FloorNonZero(size_t n) {

  return (31u ^ (uint32_t)__builtin_clz((uint32_t)n));





}





 extern const double kBrotliLog2Table[256];
# 51 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./fast_log.h"
static inline double FastLog2(size_t v) {
  if (v < 256) {
    return kBrotliLog2Table[v];
  }



  return log2((double)v);

}
# 15 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/literal_cost.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./utf8_util.h" 1
# 19 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./utf8_util.h"
static const double kMinUTF8Ratio = 0.75;




 int BrotliIsMostlyUTF8(
    const uint8_t* data, const size_t pos, const size_t mask,
    const size_t length, const double min_fraction);
# 16 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/literal_cost.c" 2





static size_t UTF8Position(size_t last, size_t c, size_t clamp) {
  if (c < 128) {
    return 0;
  } else if (c >= 192) {
    return (brotli_min_size_t((1), (clamp)));
  } else {

    if (last < 0xE0) {
      return 0;
    } else {
      return (brotli_min_size_t((2), (clamp)));
    }
  }
}

static size_t DecideMultiByteStatsLevel(size_t pos, size_t len, size_t mask,
                                        const uint8_t* data) {
  size_t counts[3] = { 0 };
  size_t max_utf8 = 1;
  size_t last_c = 0;
  size_t i;
  for (i = 0; i < len; ++i) {
    size_t c = data[(pos + i) & mask];
    ++counts[UTF8Position(last_c, c, 2)];
    last_c = c;
  }
  if (counts[2] < 500) {
    max_utf8 = 1;
  }
  if (counts[1] + counts[2] < 25) {
    max_utf8 = 0;
  }
  return max_utf8;
}

static void EstimateBitCostsForLiteralsUTF8(size_t pos, size_t len, size_t mask,
                                            const uint8_t* data, float* cost) {


  const size_t max_utf8 = DecideMultiByteStatsLevel(pos, len, mask, data);
  size_t histogram[3][256] = { { 0 } };
  size_t window_half = 495;
  size_t in_window = (brotli_min_size_t((window_half), (len)));
  size_t in_window_utf8[3] = { 0 };

  size_t i;
  {
    size_t last_c = 0;
    size_t utf8_pos = 0;
    for (i = 0; i < in_window; ++i) {
      size_t c = data[(pos + i) & mask];
      ++histogram[utf8_pos][c];
      ++in_window_utf8[utf8_pos];
      utf8_pos = UTF8Position(last_c, c, max_utf8);
      last_c = c;
    }
  }


  for (i = 0; i < len; ++i) {
    if (i >= window_half) {

      size_t c =
          i < window_half + 1 ? 0 : data[(pos + i - window_half - 1) & mask];
      size_t last_c =
          i < window_half + 2 ? 0 : data[(pos + i - window_half - 2) & mask];
      size_t utf8_pos2 = UTF8Position(last_c, c, max_utf8);
      --histogram[utf8_pos2][data[(pos + i - window_half) & mask]];
      --in_window_utf8[utf8_pos2];
    }
    if (i + window_half < len) {

      size_t c = data[(pos + i + window_half - 1) & mask];
      size_t last_c = data[(pos + i + window_half - 2) & mask];
      size_t utf8_pos2 = UTF8Position(last_c, c, max_utf8);
      ++histogram[utf8_pos2][data[(pos + i + window_half) & mask]];
      ++in_window_utf8[utf8_pos2];
    }
    {
      size_t c = i < 1 ? 0 : data[(pos + i - 1) & mask];
      size_t last_c = i < 2 ? 0 : data[(pos + i - 2) & mask];
      size_t utf8_pos = UTF8Position(last_c, c, max_utf8);
      size_t masked_pos = (pos + i) & mask;
      size_t histo = histogram[utf8_pos][data[masked_pos]];
      double lit_cost;
      if (histo == 0) {
        histo = 1;
      }
      lit_cost = FastLog2(in_window_utf8[utf8_pos]) - FastLog2(histo);
      lit_cost += 0.02905;
      if (lit_cost < 1.0) {
        lit_cost *= 0.5;
        lit_cost += 0.5;
      }




      if (i < 2000) {
        lit_cost += 0.7 - ((double)(2000 - i) / 2000.0 * 0.35);
      }
      cost[i] = (float)lit_cost;
    }
  }
}

void BrotliEstimateBitCostsForLiterals(size_t pos, size_t len, size_t mask,
                                       const uint8_t* data, float* cost) {
  if (BrotliIsMostlyUTF8(data, pos, mask, len, kMinUTF8Ratio)) {
    EstimateBitCostsForLiteralsUTF8(pos, len, mask, data, cost);
    return;
  } else {
    size_t histogram[256] = { 0 };
    size_t window_half = 2000;
    size_t in_window = (brotli_min_size_t((window_half), (len)));


    size_t i;
    for (i = 0; i < in_window; ++i) {
      ++histogram[data[(pos + i) & mask]];
    }


    for (i = 0; i < len; ++i) {
      size_t histo;
      if (i >= window_half) {

        --histogram[data[(pos + i - window_half) & mask]];
        --in_window;
      }
      if (i + window_half < len) {

        ++histogram[data[(pos + i + window_half) & mask]];
        ++in_window;
      }
      histo = histogram[data[(pos + i) & mask]];
      if (histo == 0) {
        histo = 1;
      }
      {
        double lit_cost = FastLog2(in_window) - FastLog2(histo);
        lit_cost += 0.029;
        if (lit_cost < 1.0) {
          lit_cost *= 0.5;
          lit_cost += 0.5;
        }
        cost[i] = (float)lit_cost;
      }
    }
  }
}
