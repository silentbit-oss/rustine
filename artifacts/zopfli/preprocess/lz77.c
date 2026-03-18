# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.c"
# 20 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.c"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 2
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
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 2
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/cache.h" 1
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/cache.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/util.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/util.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/util.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/util.h" 2
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/cache.h" 2
# 39 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/cache.h"
typedef struct ZopfliLongestMatchCache {
  unsigned short* length;
  unsigned short* dist;
  unsigned char* sublen;
} ZopfliLongestMatchCache;


void ZopfliInitCache(size_t blocksize, ZopfliLongestMatchCache* lmc);


void ZopfliCleanCache(ZopfliLongestMatchCache* lmc);


void ZopfliSublenToCache(const unsigned short* sublen,
                         size_t pos, size_t length,
                         ZopfliLongestMatchCache* lmc);


void ZopfliCacheToSublen(const ZopfliLongestMatchCache* lmc,
                         size_t pos, size_t length,
                         unsigned short* sublen);

unsigned ZopfliMaxCachedSublen(const ZopfliLongestMatchCache* lmc,
                               size_t pos, size_t length);
# 31 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/hash.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/hash.h"
typedef struct ZopfliHash {
  int* head;
  unsigned short* prev;
  int* hashval;
  int val;




  int* head2;
  unsigned short* prev2;
  int* hashval2;
  int val2;



  unsigned short* same;

} ZopfliHash;


void ZopfliAllocHash(size_t window_size, ZopfliHash* h);


void ZopfliResetHash(size_t window_size, ZopfliHash* h);


void ZopfliCleanHash(ZopfliHash* h);





void ZopfliUpdateHash(const unsigned char* array, size_t pos, size_t end,
                      ZopfliHash* h);






void ZopfliWarmupHash(const unsigned char* array, size_t pos, size_t end,
                      ZopfliHash* h);
# 32 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/zopfli.h" 1
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/zopfli.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/zopfli.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/zopfli.h" 2
# 33 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/zopfli.h"
typedef struct ZopfliOptions {

  int verbose;


  int verbose_more;






  int numiterations;






  int blocksplitting;




  int blocksplittinglast;





  int blocksplittingmax;
} ZopfliOptions;


void ZopfliInitOptions(ZopfliOptions* options);


typedef enum {
  ZOPFLI_FORMAT_GZIP,
  ZOPFLI_FORMAT_ZLIB,
  ZOPFLI_FORMAT_DEFLATE
} ZopfliFormat;
# 86 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/zopfli.h"
void ZopfliCompress(const ZopfliOptions* options, ZopfliFormat output_type,
                    const unsigned char* in, size_t insize,
                    unsigned char** out, size_t* outsize);
# 33 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.h" 2
# 44 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.h"
typedef struct ZopfliLZ77Store {
  unsigned short* litlens;
  unsigned short* dists;

  size_t size;

  const unsigned char* data;
  size_t* pos;

  unsigned short* ll_symbol;
  unsigned short* d_symbol;





  size_t* ll_counts;
  size_t* d_counts;
} ZopfliLZ77Store;

void ZopfliInitLZ77Store(const unsigned char* data, ZopfliLZ77Store* store);
void ZopfliCleanLZ77Store(ZopfliLZ77Store* store);
void ZopfliCopyLZ77Store(const ZopfliLZ77Store* source, ZopfliLZ77Store* dest);
void ZopfliStoreLitLenDist(unsigned short length, unsigned short dist,
                           size_t pos, ZopfliLZ77Store* store);
void ZopfliAppendLZ77Store(const ZopfliLZ77Store* store,
                           ZopfliLZ77Store* target);

size_t ZopfliLZ77GetByteRange(const ZopfliLZ77Store* lz77,
                              size_t lstart, size_t lend);



void ZopfliLZ77GetHistogram(const ZopfliLZ77Store* lz77,
                            size_t lstart, size_t lend,
                            size_t* ll_counts, size_t* d_counts);






typedef struct ZopfliBlockState {
  const ZopfliOptions* options;



  ZopfliLongestMatchCache* lmc;



  size_t blockstart;
  size_t blockend;
} ZopfliBlockState;

void ZopfliInitBlockState(const ZopfliOptions* options,
                          size_t blockstart, size_t blockend, int add_lmc,
                          ZopfliBlockState* s);
void ZopfliCleanBlockState(ZopfliBlockState* s);
# 120 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.h"
void ZopfliFindLongestMatch(
    ZopfliBlockState *s, const ZopfliHash* h, const unsigned char* array,
    size_t pos, size_t size, size_t limit,
    unsigned short* sublen, unsigned short* distance, unsigned short* length);




void ZopfliVerifyLenDist(const unsigned char* data, size_t datasize, size_t pos,
                         unsigned short dist, unsigned short length);
# 138 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.h"
void ZopfliLZ77Greedy(ZopfliBlockState* s, const unsigned char* in,
                      size_t instart, size_t inend,
                      ZopfliLZ77Store* store, ZopfliHash* h);
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/symbols.h" 1
# 38 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/symbols.h"
static int ZopfliGetDistExtraBits(int dist) {

  if (dist < 5) return 0;
  return (31 ^ __builtin_clz(dist - 1)) - 1;
# 58 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/symbols.h"
}


static int ZopfliGetDistExtraBitsValue(int dist) {

  if (dist < 5) {
    return 0;
  } else {
    int l = 31 ^ __builtin_clz(dist - 1);
    return (dist - (1 + (1 << l))) & ((1 << (l - 1)) - 1);
  }
# 85 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/symbols.h"
}


static int ZopfliGetDistSymbol(int dist) {

  if (dist < 5) {
    return dist - 1;
  } else {
    int l = (31 ^ __builtin_clz(dist - 1));
    int r = ((dist - 1) >> (l - 1)) & 1;
    return l * 2 + r;
  }
# 135 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/symbols.h"
}


static int ZopfliGetLengthExtraBits(int l) {
  static const int table[259] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0
  };
  return table[l];
}


static int ZopfliGetLengthExtraBitsValue(int l) {
  static const int table[259] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 2, 3, 0,
    1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5,
    6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6,
    7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
    13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2,
    3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
    29, 30, 31, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
    18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 0, 1, 2, 3, 4, 5, 6,
    7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,
    27, 28, 29, 30, 31, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 0
  };
  return table[l];
}





static int ZopfliGetLengthSymbol(int l) {
  static const int table[259] = {
    0, 0, 0, 257, 258, 259, 260, 261, 262, 263, 264,
    265, 265, 266, 266, 267, 267, 268, 268,
    269, 269, 269, 269, 270, 270, 270, 270,
    271, 271, 271, 271, 272, 272, 272, 272,
    273, 273, 273, 273, 273, 273, 273, 273,
    274, 274, 274, 274, 274, 274, 274, 274,
    275, 275, 275, 275, 275, 275, 275, 275,
    276, 276, 276, 276, 276, 276, 276, 276,
    277, 277, 277, 277, 277, 277, 277, 277,
    277, 277, 277, 277, 277, 277, 277, 277,
    278, 278, 278, 278, 278, 278, 278, 278,
    278, 278, 278, 278, 278, 278, 278, 278,
    279, 279, 279, 279, 279, 279, 279, 279,
    279, 279, 279, 279, 279, 279, 279, 279,
    280, 280, 280, 280, 280, 280, 280, 280,
    280, 280, 280, 280, 280, 280, 280, 280,
    281, 281, 281, 281, 281, 281, 281, 281,
    281, 281, 281, 281, 281, 281, 281, 281,
    281, 281, 281, 281, 281, 281, 281, 281,
    281, 281, 281, 281, 281, 281, 281, 281,
    282, 282, 282, 282, 282, 282, 282, 282,
    282, 282, 282, 282, 282, 282, 282, 282,
    282, 282, 282, 282, 282, 282, 282, 282,
    282, 282, 282, 282, 282, 282, 282, 282,
    283, 283, 283, 283, 283, 283, 283, 283,
    283, 283, 283, 283, 283, 283, 283, 283,
    283, 283, 283, 283, 283, 283, 283, 283,
    283, 283, 283, 283, 283, 283, 283, 283,
    284, 284, 284, 284, 284, 284, 284, 284,
    284, 284, 284, 284, 284, 284, 284, 284,
    284, 284, 284, 284, 284, 284, 284, 284,
    284, 284, 284, 284, 284, 284, 284, 285
  };
  return table[l];
}


static int ZopfliGetLengthSymbolExtraBits(int s) {
  static const int table[29] = {
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2,
    3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0
  };
  return table[s - 257];
}


static int ZopfliGetDistSymbolExtraBits(int s) {
  static const int table[30] = {
    0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8,
    9, 9, 10, 10, 11, 11, 12, 12, 13, 13
  };
  return table[s];
}
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.c" 2


# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 1
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.c" 2

void ZopfliInitLZ77Store(const unsigned char* data, ZopfliLZ77Store* store) {
  store->size = 0;
  store->litlens = 0;
  store->dists = 0;
  store->pos = 0;
  store->data = data;
  store->ll_symbol = 0;
  store->d_symbol = 0;
  store->ll_counts = 0;
  store->d_counts = 0;
}

void ZopfliCleanLZ77Store(ZopfliLZ77Store* store) {
  free(store->litlens);
  free(store->dists);
  free(store->pos);
  free(store->ll_symbol);
  free(store->d_symbol);
  free(store->ll_counts);
  free(store->d_counts);
}

static size_t CeilDiv(size_t a, size_t b) {
  return (a + b - 1) / b;
}

void ZopfliCopyLZ77Store(
    const ZopfliLZ77Store* source, ZopfliLZ77Store* dest) {
  size_t i;
  size_t llsize = 288 * CeilDiv(source->size, 288);
  size_t dsize = 32 * CeilDiv(source->size, 32);
  ZopfliCleanLZ77Store(dest);
  ZopfliInitLZ77Store(source->data, dest);
  dest->litlens =
      (unsigned short*)malloc(sizeof(*dest->litlens) * source->size);
  dest->dists = (unsigned short*)malloc(sizeof(*dest->dists) * source->size);
  dest->pos = (size_t*)malloc(sizeof(*dest->pos) * source->size);
  dest->ll_symbol =
      (unsigned short*)malloc(sizeof(*dest->ll_symbol) * source->size);
  dest->d_symbol =
      (unsigned short*)malloc(sizeof(*dest->d_symbol) * source->size);
  dest->ll_counts = (size_t*)malloc(sizeof(*dest->ll_counts) * llsize);
  dest->d_counts = (size_t*)malloc(sizeof(*dest->d_counts) * dsize);


  if (!dest->litlens || !dest->dists) exit(-1);
  if (!dest->pos) exit(-1);
  if (!dest->ll_symbol || !dest->d_symbol) exit(-1);
  if (!dest->ll_counts || !dest->d_counts) exit(-1);

  dest->size = source->size;
  for (i = 0; i < source->size; i++) {
    dest->litlens[i] = source->litlens[i];
    dest->dists[i] = source->dists[i];
    dest->pos[i] = source->pos[i];
    dest->ll_symbol[i] = source->ll_symbol[i];
    dest->d_symbol[i] = source->d_symbol[i];
  }
  for (i = 0; i < llsize; i++) {
    dest->ll_counts[i] = source->ll_counts[i];
  }
  for (i = 0; i < dsize; i++) {
    dest->d_counts[i] = source->d_counts[i];
  }
}





void ZopfliStoreLitLenDist(unsigned short length, unsigned short dist,
                           size_t pos, ZopfliLZ77Store* store) {
  size_t i;

  size_t origsize = store->size;
  size_t llstart = 288 * (origsize / 288);
  size_t dstart = 32 * (origsize / 32);




  if (origsize % 288 == 0) {
    size_t llsize = origsize;
    for (i = 0; i < 288; i++) {
      { if (!((*&llsize) & ((*&llsize) - 1))) { (*&store->ll_counts) = (*&llsize) == 0 ? malloc(sizeof(**&store->ll_counts)) : realloc((*&store->ll_counts), (*&llsize) * 2 * sizeof(**&store->ll_counts)); } (*&store->ll_counts)[(*&llsize)] = (origsize == 0 ? 0 : store->ll_counts[origsize - 288 + i]); (*&llsize)++;}

                                     ;
    }
  }
  if (origsize % 32 == 0) {
    size_t dsize = origsize;
    for (i = 0; i < 32; i++) {
      { if (!((*&dsize) & ((*&dsize) - 1))) { (*&store->d_counts) = (*&dsize) == 0 ? malloc(sizeof(**&store->d_counts)) : realloc((*&store->d_counts), (*&dsize) * 2 * sizeof(**&store->d_counts)); } (*&store->d_counts)[(*&dsize)] = (origsize == 0 ? 0 : store->d_counts[origsize - 32 + i]); (*&dsize)++;}

                                   ;
    }
  }

  { if (!((*&store->size) & ((*&store->size) - 1))) { (*&store->litlens) = (*&store->size) == 0 ? malloc(sizeof(**&store->litlens)) : realloc((*&store->litlens), (*&store->size) * 2 * sizeof(**&store->litlens)); } (*&store->litlens)[(*&store->size)] = (length); (*&store->size)++;};
  store->size = origsize;
  { if (!((*&store->size) & ((*&store->size) - 1))) { (*&store->dists) = (*&store->size) == 0 ? malloc(sizeof(**&store->dists)) : realloc((*&store->dists), (*&store->size) * 2 * sizeof(**&store->dists)); } (*&store->dists)[(*&store->size)] = (dist); (*&store->size)++;};
  store->size = origsize;
  { if (!((*&store->size) & ((*&store->size) - 1))) { (*&store->pos) = (*&store->size) == 0 ? malloc(sizeof(**&store->pos)) : realloc((*&store->pos), (*&store->size) * 2 * sizeof(**&store->pos)); } (*&store->pos)[(*&store->size)] = (pos); (*&store->size)++;};
  assert(length < 259);

  if (dist == 0) {
    store->size = origsize;
    { if (!((*&store->size) & ((*&store->size) - 1))) { (*&store->ll_symbol) = (*&store->size) == 0 ? malloc(sizeof(**&store->ll_symbol)) : realloc((*&store->ll_symbol), (*&store->size) * 2 * sizeof(**&store->ll_symbol)); } (*&store->ll_symbol)[(*&store->size)] = (length); (*&store->size)++;};
    store->size = origsize;
    { if (!((*&store->size) & ((*&store->size) - 1))) { (*&store->d_symbol) = (*&store->size) == 0 ? malloc(sizeof(**&store->d_symbol)) : realloc((*&store->d_symbol), (*&store->size) * 2 * sizeof(**&store->d_symbol)); } (*&store->d_symbol)[(*&store->size)] = (0); (*&store->size)++;};
    store->ll_counts[llstart + length]++;
  } else {
    store->size = origsize;
    { if (!((*&store->size) & ((*&store->size) - 1))) { (*&store->ll_symbol) = (*&store->size) == 0 ? malloc(sizeof(**&store->ll_symbol)) : realloc((*&store->ll_symbol), (*&store->size) * 2 * sizeof(**&store->ll_symbol)); } (*&store->ll_symbol)[(*&store->size)] = (ZopfliGetLengthSymbol(length)); (*&store->size)++;}
                                                       ;
    store->size = origsize;
    { if (!((*&store->size) & ((*&store->size) - 1))) { (*&store->d_symbol) = (*&store->size) == 0 ? malloc(sizeof(**&store->d_symbol)) : realloc((*&store->d_symbol), (*&store->size) * 2 * sizeof(**&store->d_symbol)); } (*&store->d_symbol)[(*&store->size)] = (ZopfliGetDistSymbol(dist)); (*&store->size)++;}
                                                      ;
    store->ll_counts[llstart + ZopfliGetLengthSymbol(length)]++;
    store->d_counts[dstart + ZopfliGetDistSymbol(dist)]++;
  }
}

void ZopfliAppendLZ77Store(const ZopfliLZ77Store* store,
                           ZopfliLZ77Store* target) {
  size_t i;
  for (i = 0; i < store->size; i++) {
    ZopfliStoreLitLenDist(store->litlens[i], store->dists[i],
                          store->pos[i], target);
  }
}

size_t ZopfliLZ77GetByteRange(const ZopfliLZ77Store* lz77,
                              size_t lstart, size_t lend) {
  size_t l = lend - 1;
  if (lstart == lend) return 0;
  return lz77->pos[l] + ((lz77->dists[l] == 0) ?
      1 : lz77->litlens[l]) - lz77->pos[lstart];
}

static void ZopfliLZ77GetHistogramAt(const ZopfliLZ77Store* lz77, size_t lpos,
                                     size_t* ll_counts, size_t* d_counts) {


  size_t llpos = 288 * (lpos / 288);
  size_t dpos = 32 * (lpos / 32);
  size_t i;
  for (i = 0; i < 288; i++) {
    ll_counts[i] = lz77->ll_counts[llpos + i];
  }
  for (i = lpos + 1; i < llpos + 288 && i < lz77->size; i++) {
    ll_counts[lz77->ll_symbol[i]]--;
  }
  for (i = 0; i < 32; i++) {
    d_counts[i] = lz77->d_counts[dpos + i];
  }
  for (i = lpos + 1; i < dpos + 32 && i < lz77->size; i++) {
    if (lz77->dists[i] != 0) d_counts[lz77->d_symbol[i]]--;
  }
}

void ZopfliLZ77GetHistogram(const ZopfliLZ77Store* lz77,
                           size_t lstart, size_t lend,
                           size_t* ll_counts, size_t* d_counts) {
  size_t i;
  if (lstart + 288 * 3 > lend) {
    memset(ll_counts, 0, sizeof(*ll_counts) * 288);
    memset(d_counts, 0, sizeof(*d_counts) * 32);
    for (i = lstart; i < lend; i++) {
      ll_counts[lz77->ll_symbol[i]]++;
      if (lz77->dists[i] != 0) d_counts[lz77->d_symbol[i]]++;
    }
  } else {


    ZopfliLZ77GetHistogramAt(lz77, lend - 1, ll_counts, d_counts);
    if (lstart > 0) {
      size_t ll_counts2[288];
      size_t d_counts2[32];
      ZopfliLZ77GetHistogramAt(lz77, lstart - 1, ll_counts2, d_counts2);

      for (i = 0; i < 288; i++) {
        ll_counts[i] -= ll_counts2[i];
      }
      for (i = 0; i < 32; i++) {
        d_counts[i] -= d_counts2[i];
      }
    }
  }
}

void ZopfliInitBlockState(const ZopfliOptions* options,
                          size_t blockstart, size_t blockend, int add_lmc,
                          ZopfliBlockState* s) {
  s->options = options;
  s->blockstart = blockstart;
  s->blockend = blockend;

  if (add_lmc) {
    s->lmc = (ZopfliLongestMatchCache*)malloc(sizeof(ZopfliLongestMatchCache));
    ZopfliInitCache(blockend - blockstart, s->lmc);
  } else {
    s->lmc = 0;
  }

}

void ZopfliCleanBlockState(ZopfliBlockState* s) {

  if (s->lmc) {
    ZopfliCleanCache(s->lmc);
    free(s->lmc);
  }

}
# 265 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.c"
static int GetLengthScore(int length, int distance) {




  return distance > 1024 ? length - 1 : length;
}

void ZopfliVerifyLenDist(const unsigned char* data, size_t datasize, size_t pos,
                         unsigned short dist, unsigned short length) {


  size_t i;

  assert(pos + length <= datasize);
  for (i = 0; i < length; i++) {
    if (data[pos - dist + i] != data[pos + i]) {
      assert(data[pos - dist + i] == data[pos + i]);
      break;
    }
  }
}
# 297 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.c"
static const unsigned char* GetMatch(const unsigned char* scan,
                                     const unsigned char* match,
                                     const unsigned char* end,
                                     const unsigned char* safe_end) {

  if (sizeof(size_t) == 8) {

    while (scan < safe_end && *((size_t*)scan) == *((size_t*)match)) {
      scan += 8;
      match += 8;
    }
  } else if (sizeof(unsigned int) == 4) {

    while (scan < safe_end
        && *((unsigned int*)scan) == *((unsigned int*)match)) {
      scan += 4;
      match += 4;
    }
  } else {

    while (scan < safe_end && *scan == *match && *++scan == *++match
          && *++scan == *++match && *++scan == *++match
          && *++scan == *++match && *++scan == *++match
          && *++scan == *++match && *++scan == *++match) {
      scan++; match++;
    }
  }


  while (scan != end && *scan == *match) {
    scan++; match++;
  }

  return scan;
}
# 340 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.c"
static int TryGetFromLongestMatchCache(ZopfliBlockState* s,
    size_t pos, size_t* limit,
    unsigned short* sublen, unsigned short* distance, unsigned short* length) {


  size_t lmcpos = pos - s->blockstart;



  unsigned char cache_available = s->lmc && (s->lmc->length[lmcpos] == 0 ||
      s->lmc->dist[lmcpos] != 0);
  unsigned char limit_ok_for_cache = cache_available &&
      (*limit == 258 || s->lmc->length[lmcpos] <= *limit ||
      (sublen && ZopfliMaxCachedSublen(s->lmc,
          lmcpos, s->lmc->length[lmcpos]) >= *limit));

  if (s->lmc && limit_ok_for_cache && cache_available) {
    if (!sublen || s->lmc->length[lmcpos]
        <= ZopfliMaxCachedSublen(s->lmc, lmcpos, s->lmc->length[lmcpos])) {
      *length = s->lmc->length[lmcpos];
      if (*length > *limit) *length = *limit;
      if (sublen) {
        ZopfliCacheToSublen(s->lmc, lmcpos, *length, sublen);
        *distance = sublen[*length];
        if (*limit == 258 && *length >= 3) {
          assert(sublen[*length] == s->lmc->dist[lmcpos]);
        }
      } else {
        *distance = s->lmc->dist[lmcpos];
      }
      return 1;
    }


    *limit = s->lmc->length[lmcpos];
  }

  return 0;
}





static void StoreInLongestMatchCache(ZopfliBlockState* s,
    size_t pos, size_t limit,
    const unsigned short* sublen,
    unsigned short distance, unsigned short length) {


  size_t lmcpos = pos - s->blockstart;



  unsigned char cache_available = s->lmc && (s->lmc->length[lmcpos] == 0 ||
      s->lmc->dist[lmcpos] != 0);

  if (s->lmc && limit == 258 && sublen && !cache_available) {
    assert(s->lmc->length[lmcpos] == 1 && s->lmc->dist[lmcpos] == 0);
    s->lmc->dist[lmcpos] = length < 3 ? 0 : distance;
    s->lmc->length[lmcpos] = length < 3 ? 0 : length;
    assert(!(s->lmc->length[lmcpos] == 1 && s->lmc->dist[lmcpos] == 0));
    ZopfliSublenToCache(sublen, lmcpos, length, s->lmc);
  }
}


void ZopfliFindLongestMatch(ZopfliBlockState* s, const ZopfliHash* h,
    const unsigned char* array,
    size_t pos, size_t size, size_t limit,
    unsigned short* sublen, unsigned short* distance, unsigned short* length) {
  unsigned short hpos = pos & (32768 - 1), p, pp;
  unsigned short bestdist = 0;
  unsigned short bestlength = 1;
  const unsigned char* scan;
  const unsigned char* match;
  const unsigned char* arrayend;
  const unsigned char* arrayend_safe;

  int chain_counter = 8192;


  unsigned dist = 0;

  int* hhead = h->head;
  unsigned short* hprev = h->prev;
  int* hhashval = h->hashval;
  int hval = h->val;


  if (TryGetFromLongestMatchCache(s, pos, &limit, sublen, distance, length)) {
    assert(pos + *length <= size);
    return;
  }


  assert(limit <= 258);
  assert(limit >= 3);
  assert(pos < size);

  if (size - pos < 3) {


    *length = 0;
    *distance = 0;
    return;
  }

  if (pos + limit > size) {
    limit = size - pos;
  }
  arrayend = &array[pos] + limit;
  arrayend_safe = arrayend - 8;

  assert(hval < 65536);

  pp = hhead[hval];
  p = hprev[pp];

  assert(pp == hpos);

  dist = p < pp ? pp - p : ((32768 - p) + pp);


  while (dist < 32768) {
    unsigned short currentlength = 0;

    assert(p < 32768);
    assert(p == hprev[pp]);
    assert(hhashval[p] == hval);

    if (dist > 0) {
      assert(pos < size);
      assert(dist <= pos);
      scan = &array[pos];
      match = &array[pos - dist];


      if (pos + bestlength >= size
          || *(scan + bestlength) == *(match + bestlength)) {


        unsigned short same0 = h->same[pos & (32768 - 1)];
        if (same0 > 2 && *scan == *match) {
          unsigned short same1 = h->same[(pos - dist) & (32768 - 1)];
          unsigned short same = same0 < same1 ? same0 : same1;
          if (same > limit) same = limit;
          scan += same;
          match += same;
        }

        scan = GetMatch(scan, match, arrayend, arrayend_safe);
        currentlength = scan - &array[pos];
      }

      if (currentlength > bestlength) {
        if (sublen) {
          unsigned short j;
          for (j = bestlength + 1; j <= currentlength; j++) {
            sublen[j] = dist;
          }
        }
        bestdist = dist;
        bestlength = currentlength;
        if (currentlength >= limit) break;
      }
    }




    if (hhead != h->head2 && bestlength >= h->same[hpos] &&
        h->val2 == h->hashval2[p]) {

      hhead = h->head2;
      hprev = h->prev2;
      hhashval = h->hashval2;
      hval = h->val2;
    }


    pp = p;
    p = hprev[p];
    if (p == pp) break;

    dist += p < pp ? pp - p : ((32768 - p) + pp);


    chain_counter--;
    if (chain_counter <= 0) break;

  }


  StoreInLongestMatchCache(s, pos, limit, sublen, bestdist, bestlength);


  assert(bestlength <= limit);

  *distance = bestdist;
  *length = bestlength;
  assert(pos + *length <= size);
}

void ZopfliLZ77Greedy(ZopfliBlockState* s, const unsigned char* in,
                      size_t instart, size_t inend,
                      ZopfliLZ77Store* store, ZopfliHash* h) {
  size_t i = 0, j;
  unsigned short leng;
  unsigned short dist;
  int lengthscore;
  size_t windowstart = instart > 32768
      ? instart - 32768 : 0;
  unsigned short dummysublen[259];



  unsigned prev_length = 0;
  unsigned prev_match = 0;
  int prevlengthscore;
  int match_available = 0;


  if (instart == inend) return;

  ZopfliResetHash(32768, h);
  ZopfliWarmupHash(in, windowstart, inend, h);
  for (i = windowstart; i < instart; i++) {
    ZopfliUpdateHash(in, i, inend, h);
  }

  for (i = instart; i < inend; i++) {
    ZopfliUpdateHash(in, i, inend, h);

    ZopfliFindLongestMatch(s, h, in, i, inend, 258, dummysublen,
                           &dist, &leng);
    lengthscore = GetLengthScore(leng, dist);



    prevlengthscore = GetLengthScore(prev_length, prev_match);
    if (match_available) {
      match_available = 0;
      if (lengthscore > prevlengthscore + 1) {
        ZopfliStoreLitLenDist(in[i - 1], 0, i - 1, store);
        if (lengthscore >= 3 && leng < 258) {
          match_available = 1;
          prev_length = leng;
          prev_match = dist;
          continue;
        }
      } else {

        leng = prev_length;
        dist = prev_match;
        lengthscore = prevlengthscore;

        ZopfliVerifyLenDist(in, inend, i - 1, dist, leng);
        ZopfliStoreLitLenDist(leng, dist, i - 1, store);
        for (j = 2; j < leng; j++) {
          assert(i < inend);
          i++;
          ZopfliUpdateHash(in, i, inend, h);
        }
        continue;
      }
    }
    else if (lengthscore >= 3 && leng < 258) {
      match_available = 1;
      prev_length = leng;
      prev_match = dist;
      continue;
    }




    if (lengthscore >= 3) {
      ZopfliVerifyLenDist(in, inend, i, dist, leng);
      ZopfliStoreLitLenDist(leng, dist, i, store);
    } else {
      leng = 1;
      ZopfliStoreLitLenDist(in[i], 0, i, store);
    }
    for (j = 1; j < leng; j++) {
      assert(i < inend);
      i++;
      ZopfliUpdateHash(in, i, inend, h);
    }
  }
}
# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.c"
# 20 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.c"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 2
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
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 2
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/cache.h" 1
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/cache.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/util.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/util.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/util.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/util.h" 2
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/cache.h" 2
# 39 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/cache.h"
typedef struct ZopfliLongestMatchCache {
  unsigned short* length;
  unsigned short* dist;
  unsigned char* sublen;
} ZopfliLongestMatchCache;


void ZopfliInitCache(size_t blocksize, ZopfliLongestMatchCache* lmc);


void ZopfliCleanCache(ZopfliLongestMatchCache* lmc);


void ZopfliSublenToCache(const unsigned short* sublen,
                         size_t pos, size_t length,
                         ZopfliLongestMatchCache* lmc);


void ZopfliCacheToSublen(const ZopfliLongestMatchCache* lmc,
                         size_t pos, size_t length,
                         unsigned short* sublen);

unsigned ZopfliMaxCachedSublen(const ZopfliLongestMatchCache* lmc,
                               size_t pos, size_t length);
# 31 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/hash.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/hash.h"
typedef struct ZopfliHash {
  int* head;
  unsigned short* prev;
  int* hashval;
  int val;




  int* head2;
  unsigned short* prev2;
  int* hashval2;
  int val2;



  unsigned short* same;

} ZopfliHash;


void ZopfliAllocHash(size_t window_size, ZopfliHash* h);


void ZopfliResetHash(size_t window_size, ZopfliHash* h);


void ZopfliCleanHash(ZopfliHash* h);





void ZopfliUpdateHash(const unsigned char* array, size_t pos, size_t end,
                      ZopfliHash* h);






void ZopfliWarmupHash(const unsigned char* array, size_t pos, size_t end,
                      ZopfliHash* h);
# 32 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/zopfli.h" 1
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/zopfli.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/zopfli.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/zopfli.h" 2
# 33 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/zopfli.h"
typedef struct ZopfliOptions {

  int verbose;


  int verbose_more;






  int numiterations;






  int blocksplitting;




  int blocksplittinglast;





  int blocksplittingmax;
} ZopfliOptions;


void ZopfliInitOptions(ZopfliOptions* options);


typedef enum {
  ZOPFLI_FORMAT_GZIP,
  ZOPFLI_FORMAT_ZLIB,
  ZOPFLI_FORMAT_DEFLATE
} ZopfliFormat;
# 86 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/zopfli.h"
void ZopfliCompress(const ZopfliOptions* options, ZopfliFormat output_type,
                    const unsigned char* in, size_t insize,
                    unsigned char** out, size_t* outsize);
# 33 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.h" 2
# 44 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.h"
typedef struct ZopfliLZ77Store {
  unsigned short* litlens;
  unsigned short* dists;

  size_t size;

  const unsigned char* data;
  size_t* pos;

  unsigned short* ll_symbol;
  unsigned short* d_symbol;





  size_t* ll_counts;
  size_t* d_counts;
} ZopfliLZ77Store;

void ZopfliInitLZ77Store(const unsigned char* data, ZopfliLZ77Store* store);
void ZopfliCleanLZ77Store(ZopfliLZ77Store* store);
void ZopfliCopyLZ77Store(const ZopfliLZ77Store* source, ZopfliLZ77Store* dest);
void ZopfliStoreLitLenDist(unsigned short length, unsigned short dist,
                           size_t pos, ZopfliLZ77Store* store);
void ZopfliAppendLZ77Store(const ZopfliLZ77Store* store,
                           ZopfliLZ77Store* target);

size_t ZopfliLZ77GetByteRange(const ZopfliLZ77Store* lz77,
                              size_t lstart, size_t lend);



void ZopfliLZ77GetHistogram(const ZopfliLZ77Store* lz77,
                            size_t lstart, size_t lend,
                            size_t* ll_counts, size_t* d_counts);






typedef struct ZopfliBlockState {
  const ZopfliOptions* options;



  ZopfliLongestMatchCache* lmc;



  size_t blockstart;
  size_t blockend;
} ZopfliBlockState;

void ZopfliInitBlockState(const ZopfliOptions* options,
                          size_t blockstart, size_t blockend, int add_lmc,
                          ZopfliBlockState* s);
void ZopfliCleanBlockState(ZopfliBlockState* s);
# 120 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.h"
void ZopfliFindLongestMatch(
    ZopfliBlockState *s, const ZopfliHash* h, const unsigned char* array,
    size_t pos, size_t size, size_t limit,
    unsigned short* sublen, unsigned short* distance, unsigned short* length);




void ZopfliVerifyLenDist(const unsigned char* data, size_t datasize, size_t pos,
                         unsigned short dist, unsigned short length);
# 138 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.h"
void ZopfliLZ77Greedy(ZopfliBlockState* s, const unsigned char* in,
                      size_t instart, size_t inend,
                      ZopfliLZ77Store* store, ZopfliHash* h);
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/symbols.h" 1
# 38 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/symbols.h"
static int ZopfliGetDistExtraBits(int dist) {

  if (dist < 5) return 0;
  return (31 ^ __builtin_clz(dist - 1)) - 1;
# 58 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/symbols.h"
}


static int ZopfliGetDistExtraBitsValue(int dist) {

  if (dist < 5) {
    return 0;
  } else {
    int l = 31 ^ __builtin_clz(dist - 1);
    return (dist - (1 + (1 << l))) & ((1 << (l - 1)) - 1);
  }
# 85 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/symbols.h"
}


static int ZopfliGetDistSymbol(int dist) {

  if (dist < 5) {
    return dist - 1;
  } else {
    int l = (31 ^ __builtin_clz(dist - 1));
    int r = ((dist - 1) >> (l - 1)) & 1;
    return l * 2 + r;
  }
# 135 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/symbols.h"
}


static int ZopfliGetLengthExtraBits(int l) {
  static const int table[259] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0
  };
  return table[l];
}


static int ZopfliGetLengthExtraBitsValue(int l) {
  static const int table[259] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 2, 3, 0,
    1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5,
    6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6,
    7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
    13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2,
    3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
    29, 30, 31, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
    18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 0, 1, 2, 3, 4, 5, 6,
    7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26,
    27, 28, 29, 30, 31, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 0
  };
  return table[l];
}





static int ZopfliGetLengthSymbol(int l) {
  static const int table[259] = {
    0, 0, 0, 257, 258, 259, 260, 261, 262, 263, 264,
    265, 265, 266, 266, 267, 267, 268, 268,
    269, 269, 269, 269, 270, 270, 270, 270,
    271, 271, 271, 271, 272, 272, 272, 272,
    273, 273, 273, 273, 273, 273, 273, 273,
    274, 274, 274, 274, 274, 274, 274, 274,
    275, 275, 275, 275, 275, 275, 275, 275,
    276, 276, 276, 276, 276, 276, 276, 276,
    277, 277, 277, 277, 277, 277, 277, 277,
    277, 277, 277, 277, 277, 277, 277, 277,
    278, 278, 278, 278, 278, 278, 278, 278,
    278, 278, 278, 278, 278, 278, 278, 278,
    279, 279, 279, 279, 279, 279, 279, 279,
    279, 279, 279, 279, 279, 279, 279, 279,
    280, 280, 280, 280, 280, 280, 280, 280,
    280, 280, 280, 280, 280, 280, 280, 280,
    281, 281, 281, 281, 281, 281, 281, 281,
    281, 281, 281, 281, 281, 281, 281, 281,
    281, 281, 281, 281, 281, 281, 281, 281,
    281, 281, 281, 281, 281, 281, 281, 281,
    282, 282, 282, 282, 282, 282, 282, 282,
    282, 282, 282, 282, 282, 282, 282, 282,
    282, 282, 282, 282, 282, 282, 282, 282,
    282, 282, 282, 282, 282, 282, 282, 282,
    283, 283, 283, 283, 283, 283, 283, 283,
    283, 283, 283, 283, 283, 283, 283, 283,
    283, 283, 283, 283, 283, 283, 283, 283,
    283, 283, 283, 283, 283, 283, 283, 283,
    284, 284, 284, 284, 284, 284, 284, 284,
    284, 284, 284, 284, 284, 284, 284, 284,
    284, 284, 284, 284, 284, 284, 284, 284,
    284, 284, 284, 284, 284, 284, 284, 285
  };
  return table[l];
}


static int ZopfliGetLengthSymbolExtraBits(int s) {
  static const int table[29] = {
    0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2,
    3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0
  };
  return table[s - 257];
}


static int ZopfliGetDistSymbolExtraBits(int s) {
  static const int table[30] = {
    0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8,
    9, 9, 10, 10, 11, 11, 12, 12, 13, 13
  };
  return table[s];
}
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.c" 2


# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 1
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.c" 2

void ZopfliInitLZ77Store(const unsigned char* data, ZopfliLZ77Store* store) {
  store->size = 0;
  store->litlens = 0;
  store->dists = 0;
  store->pos = 0;
  store->data = data;
  store->ll_symbol = 0;
  store->d_symbol = 0;
  store->ll_counts = 0;
  store->d_counts = 0;
}

void ZopfliCleanLZ77Store(ZopfliLZ77Store* store) {
  free(store->litlens);
  free(store->dists);
  free(store->pos);
  free(store->ll_symbol);
  free(store->d_symbol);
  free(store->ll_counts);
  free(store->d_counts);
}

static size_t CeilDiv(size_t a, size_t b) {
  return (a + b - 1) / b;
}

void ZopfliCopyLZ77Store(
    const ZopfliLZ77Store* source, ZopfliLZ77Store* dest) {
  size_t i;
  size_t llsize = 288 * CeilDiv(source->size, 288);
  size_t dsize = 32 * CeilDiv(source->size, 32);
  ZopfliCleanLZ77Store(dest);
  ZopfliInitLZ77Store(source->data, dest);
  dest->litlens =
      (unsigned short*)malloc(sizeof(*dest->litlens) * source->size);
  dest->dists = (unsigned short*)malloc(sizeof(*dest->dists) * source->size);
  dest->pos = (size_t*)malloc(sizeof(*dest->pos) * source->size);
  dest->ll_symbol =
      (unsigned short*)malloc(sizeof(*dest->ll_symbol) * source->size);
  dest->d_symbol =
      (unsigned short*)malloc(sizeof(*dest->d_symbol) * source->size);
  dest->ll_counts = (size_t*)malloc(sizeof(*dest->ll_counts) * llsize);
  dest->d_counts = (size_t*)malloc(sizeof(*dest->d_counts) * dsize);


  if (!dest->litlens || !dest->dists) exit(-1);
  if (!dest->pos) exit(-1);
  if (!dest->ll_symbol || !dest->d_symbol) exit(-1);
  if (!dest->ll_counts || !dest->d_counts) exit(-1);

  dest->size = source->size;
  for (i = 0; i < source->size; i++) {
    dest->litlens[i] = source->litlens[i];
    dest->dists[i] = source->dists[i];
    dest->pos[i] = source->pos[i];
    dest->ll_symbol[i] = source->ll_symbol[i];
    dest->d_symbol[i] = source->d_symbol[i];
  }
  for (i = 0; i < llsize; i++) {
    dest->ll_counts[i] = source->ll_counts[i];
  }
  for (i = 0; i < dsize; i++) {
    dest->d_counts[i] = source->d_counts[i];
  }
}





void ZopfliStoreLitLenDist(unsigned short length, unsigned short dist,
                           size_t pos, ZopfliLZ77Store* store) {
  size_t i;

  size_t origsize = store->size;
  size_t llstart = 288 * (origsize / 288);
  size_t dstart = 32 * (origsize / 32);




  if (origsize % 288 == 0) {
    size_t llsize = origsize;
    for (i = 0; i < 288; i++) {
      { if (!((*&llsize) & ((*&llsize) - 1))) { (*&store->ll_counts) = (*&llsize) == 0 ? malloc(sizeof(**&store->ll_counts)) : realloc((*&store->ll_counts), (*&llsize) * 2 * sizeof(**&store->ll_counts)); } (*&store->ll_counts)[(*&llsize)] = (origsize == 0 ? 0 : store->ll_counts[origsize - 288 + i]); (*&llsize)++;}

                                     ;
    }
  }
  if (origsize % 32 == 0) {
    size_t dsize = origsize;
    for (i = 0; i < 32; i++) {
      { if (!((*&dsize) & ((*&dsize) - 1))) { (*&store->d_counts) = (*&dsize) == 0 ? malloc(sizeof(**&store->d_counts)) : realloc((*&store->d_counts), (*&dsize) * 2 * sizeof(**&store->d_counts)); } (*&store->d_counts)[(*&dsize)] = (origsize == 0 ? 0 : store->d_counts[origsize - 32 + i]); (*&dsize)++;}

                                   ;
    }
  }

  { if (!((*&store->size) & ((*&store->size) - 1))) { (*&store->litlens) = (*&store->size) == 0 ? malloc(sizeof(**&store->litlens)) : realloc((*&store->litlens), (*&store->size) * 2 * sizeof(**&store->litlens)); } (*&store->litlens)[(*&store->size)] = (length); (*&store->size)++;};
  store->size = origsize;
  { if (!((*&store->size) & ((*&store->size) - 1))) { (*&store->dists) = (*&store->size) == 0 ? malloc(sizeof(**&store->dists)) : realloc((*&store->dists), (*&store->size) * 2 * sizeof(**&store->dists)); } (*&store->dists)[(*&store->size)] = (dist); (*&store->size)++;};
  store->size = origsize;
  { if (!((*&store->size) & ((*&store->size) - 1))) { (*&store->pos) = (*&store->size) == 0 ? malloc(sizeof(**&store->pos)) : realloc((*&store->pos), (*&store->size) * 2 * sizeof(**&store->pos)); } (*&store->pos)[(*&store->size)] = (pos); (*&store->size)++;};
  assert(length < 259);

  if (dist == 0) {
    store->size = origsize;
    { if (!((*&store->size) & ((*&store->size) - 1))) { (*&store->ll_symbol) = (*&store->size) == 0 ? malloc(sizeof(**&store->ll_symbol)) : realloc((*&store->ll_symbol), (*&store->size) * 2 * sizeof(**&store->ll_symbol)); } (*&store->ll_symbol)[(*&store->size)] = (length); (*&store->size)++;};
    store->size = origsize;
    { if (!((*&store->size) & ((*&store->size) - 1))) { (*&store->d_symbol) = (*&store->size) == 0 ? malloc(sizeof(**&store->d_symbol)) : realloc((*&store->d_symbol), (*&store->size) * 2 * sizeof(**&store->d_symbol)); } (*&store->d_symbol)[(*&store->size)] = (0); (*&store->size)++;};
    store->ll_counts[llstart + length]++;
  } else {
    store->size = origsize;
    { if (!((*&store->size) & ((*&store->size) - 1))) { (*&store->ll_symbol) = (*&store->size) == 0 ? malloc(sizeof(**&store->ll_symbol)) : realloc((*&store->ll_symbol), (*&store->size) * 2 * sizeof(**&store->ll_symbol)); } (*&store->ll_symbol)[(*&store->size)] = (ZopfliGetLengthSymbol(length)); (*&store->size)++;}
                                                       ;
    store->size = origsize;
    { if (!((*&store->size) & ((*&store->size) - 1))) { (*&store->d_symbol) = (*&store->size) == 0 ? malloc(sizeof(**&store->d_symbol)) : realloc((*&store->d_symbol), (*&store->size) * 2 * sizeof(**&store->d_symbol)); } (*&store->d_symbol)[(*&store->size)] = (ZopfliGetDistSymbol(dist)); (*&store->size)++;}
                                                      ;
    store->ll_counts[llstart + ZopfliGetLengthSymbol(length)]++;
    store->d_counts[dstart + ZopfliGetDistSymbol(dist)]++;
  }
}

void ZopfliAppendLZ77Store(const ZopfliLZ77Store* store,
                           ZopfliLZ77Store* target) {
  size_t i;
  for (i = 0; i < store->size; i++) {
    ZopfliStoreLitLenDist(store->litlens[i], store->dists[i],
                          store->pos[i], target);
  }
}

size_t ZopfliLZ77GetByteRange(const ZopfliLZ77Store* lz77,
                              size_t lstart, size_t lend) {
  size_t l = lend - 1;
  if (lstart == lend) return 0;
  return lz77->pos[l] + ((lz77->dists[l] == 0) ?
      1 : lz77->litlens[l]) - lz77->pos[lstart];
}

static void ZopfliLZ77GetHistogramAt(const ZopfliLZ77Store* lz77, size_t lpos,
                                     size_t* ll_counts, size_t* d_counts) {


  size_t llpos = 288 * (lpos / 288);
  size_t dpos = 32 * (lpos / 32);
  size_t i;
  for (i = 0; i < 288; i++) {
    ll_counts[i] = lz77->ll_counts[llpos + i];
  }
  for (i = lpos + 1; i < llpos + 288 && i < lz77->size; i++) {
    ll_counts[lz77->ll_symbol[i]]--;
  }
  for (i = 0; i < 32; i++) {
    d_counts[i] = lz77->d_counts[dpos + i];
  }
  for (i = lpos + 1; i < dpos + 32 && i < lz77->size; i++) {
    if (lz77->dists[i] != 0) d_counts[lz77->d_symbol[i]]--;
  }
}

void ZopfliLZ77GetHistogram(const ZopfliLZ77Store* lz77,
                           size_t lstart, size_t lend,
                           size_t* ll_counts, size_t* d_counts) {
  size_t i;
  if (lstart + 288 * 3 > lend) {
    memset(ll_counts, 0, sizeof(*ll_counts) * 288);
    memset(d_counts, 0, sizeof(*d_counts) * 32);
    for (i = lstart; i < lend; i++) {
      ll_counts[lz77->ll_symbol[i]]++;
      if (lz77->dists[i] != 0) d_counts[lz77->d_symbol[i]]++;
    }
  } else {


    ZopfliLZ77GetHistogramAt(lz77, lend - 1, ll_counts, d_counts);
    if (lstart > 0) {
      size_t ll_counts2[288];
      size_t d_counts2[32];
      ZopfliLZ77GetHistogramAt(lz77, lstart - 1, ll_counts2, d_counts2);

      for (i = 0; i < 288; i++) {
        ll_counts[i] -= ll_counts2[i];
      }
      for (i = 0; i < 32; i++) {
        d_counts[i] -= d_counts2[i];
      }
    }
  }
}

void ZopfliInitBlockState(const ZopfliOptions* options,
                          size_t blockstart, size_t blockend, int add_lmc,
                          ZopfliBlockState* s) {
  s->options = options;
  s->blockstart = blockstart;
  s->blockend = blockend;

  if (add_lmc) {
    s->lmc = (ZopfliLongestMatchCache*)malloc(sizeof(ZopfliLongestMatchCache));
    ZopfliInitCache(blockend - blockstart, s->lmc);
  } else {
    s->lmc = 0;
  }

}

void ZopfliCleanBlockState(ZopfliBlockState* s) {

  if (s->lmc) {
    ZopfliCleanCache(s->lmc);
    free(s->lmc);
  }

}
# 265 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.c"
static int GetLengthScore(int length, int distance) {




  return distance > 1024 ? length - 1 : length;
}

void ZopfliVerifyLenDist(const unsigned char* data, size_t datasize, size_t pos,
                         unsigned short dist, unsigned short length) {


  size_t i;

  assert(pos + length <= datasize);
  for (i = 0; i < length; i++) {
    if (data[pos - dist + i] != data[pos + i]) {
      assert(data[pos - dist + i] == data[pos + i]);
      break;
    }
  }
}
# 297 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.c"
static const unsigned char* GetMatch(const unsigned char* scan,
                                     const unsigned char* match,
                                     const unsigned char* end,
                                     const unsigned char* safe_end) {

  if (sizeof(size_t) == 8) {

    while (scan < safe_end && *((size_t*)scan) == *((size_t*)match)) {
      scan += 8;
      match += 8;
    }
  } else if (sizeof(unsigned int) == 4) {

    while (scan < safe_end
        && *((unsigned int*)scan) == *((unsigned int*)match)) {
      scan += 4;
      match += 4;
    }
  } else {

    while (scan < safe_end && *scan == *match && *++scan == *++match
          && *++scan == *++match && *++scan == *++match
          && *++scan == *++match && *++scan == *++match
          && *++scan == *++match && *++scan == *++match) {
      scan++; match++;
    }
  }


  while (scan != end && *scan == *match) {
    scan++; match++;
  }

  return scan;
}
# 340 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.c"
static int TryGetFromLongestMatchCache(ZopfliBlockState* s,
    size_t pos, size_t* limit,
    unsigned short* sublen, unsigned short* distance, unsigned short* length) {


  size_t lmcpos = pos - s->blockstart;



  unsigned char cache_available = s->lmc && (s->lmc->length[lmcpos] == 0 ||
      s->lmc->dist[lmcpos] != 0);
  unsigned char limit_ok_for_cache = cache_available &&
      (*limit == 258 || s->lmc->length[lmcpos] <= *limit ||
      (sublen && ZopfliMaxCachedSublen(s->lmc,
          lmcpos, s->lmc->length[lmcpos]) >= *limit));

  if (s->lmc && limit_ok_for_cache && cache_available) {
    if (!sublen || s->lmc->length[lmcpos]
        <= ZopfliMaxCachedSublen(s->lmc, lmcpos, s->lmc->length[lmcpos])) {
      *length = s->lmc->length[lmcpos];
      if (*length > *limit) *length = *limit;
      if (sublen) {
        ZopfliCacheToSublen(s->lmc, lmcpos, *length, sublen);
        *distance = sublen[*length];
        if (*limit == 258 && *length >= 3) {
          assert(sublen[*length] == s->lmc->dist[lmcpos]);
        }
      } else {
        *distance = s->lmc->dist[lmcpos];
      }
      return 1;
    }


    *limit = s->lmc->length[lmcpos];
  }

  return 0;
}





static void StoreInLongestMatchCache(ZopfliBlockState* s,
    size_t pos, size_t limit,
    const unsigned short* sublen,
    unsigned short distance, unsigned short length) {


  size_t lmcpos = pos - s->blockstart;



  unsigned char cache_available = s->lmc && (s->lmc->length[lmcpos] == 0 ||
      s->lmc->dist[lmcpos] != 0);

  if (s->lmc && limit == 258 && sublen && !cache_available) {
    assert(s->lmc->length[lmcpos] == 1 && s->lmc->dist[lmcpos] == 0);
    s->lmc->dist[lmcpos] = length < 3 ? 0 : distance;
    s->lmc->length[lmcpos] = length < 3 ? 0 : length;
    assert(!(s->lmc->length[lmcpos] == 1 && s->lmc->dist[lmcpos] == 0));
    ZopfliSublenToCache(sublen, lmcpos, length, s->lmc);
  }
}


void ZopfliFindLongestMatch(ZopfliBlockState* s, const ZopfliHash* h,
    const unsigned char* array,
    size_t pos, size_t size, size_t limit,
    unsigned short* sublen, unsigned short* distance, unsigned short* length) {
  unsigned short hpos = pos & (32768 - 1), p, pp;
  unsigned short bestdist = 0;
  unsigned short bestlength = 1;
  const unsigned char* scan;
  const unsigned char* match;
  const unsigned char* arrayend;
  const unsigned char* arrayend_safe;

  int chain_counter = 8192;


  unsigned dist = 0;

  int* hhead = h->head;
  unsigned short* hprev = h->prev;
  int* hhashval = h->hashval;
  int hval = h->val;


  if (TryGetFromLongestMatchCache(s, pos, &limit, sublen, distance, length)) {
    assert(pos + *length <= size);
    return;
  }


  assert(limit <= 258);
  assert(limit >= 3);
  assert(pos < size);

  if (size - pos < 3) {


    *length = 0;
    *distance = 0;
    return;
  }

  if (pos + limit > size) {
    limit = size - pos;
  }
  arrayend = &array[pos] + limit;
  arrayend_safe = arrayend - 8;

  assert(hval < 65536);

  pp = hhead[hval];
  p = hprev[pp];

  assert(pp == hpos);

  dist = p < pp ? pp - p : ((32768 - p) + pp);


  while (dist < 32768) {
    unsigned short currentlength = 0;

    assert(p < 32768);
    assert(p == hprev[pp]);
    assert(hhashval[p] == hval);

    if (dist > 0) {
      assert(pos < size);
      assert(dist <= pos);
      scan = &array[pos];
      match = &array[pos - dist];


      if (pos + bestlength >= size
          || *(scan + bestlength) == *(match + bestlength)) {


        unsigned short same0 = h->same[pos & (32768 - 1)];
        if (same0 > 2 && *scan == *match) {
          unsigned short same1 = h->same[(pos - dist) & (32768 - 1)];
          unsigned short same = same0 < same1 ? same0 : same1;
          if (same > limit) same = limit;
          scan += same;
          match += same;
        }

        scan = GetMatch(scan, match, arrayend, arrayend_safe);
        currentlength = scan - &array[pos];
      }

      if (currentlength > bestlength) {
        if (sublen) {
          unsigned short j;
          for (j = bestlength + 1; j <= currentlength; j++) {
            sublen[j] = dist;
          }
        }
        bestdist = dist;
        bestlength = currentlength;
        if (currentlength >= limit) break;
      }
    }




    if (hhead != h->head2 && bestlength >= h->same[hpos] &&
        h->val2 == h->hashval2[p]) {

      hhead = h->head2;
      hprev = h->prev2;
      hhashval = h->hashval2;
      hval = h->val2;
    }


    pp = p;
    p = hprev[p];
    if (p == pp) break;

    dist += p < pp ? pp - p : ((32768 - p) + pp);


    chain_counter--;
    if (chain_counter <= 0) break;

  }


  StoreInLongestMatchCache(s, pos, limit, sublen, bestdist, bestlength);


  assert(bestlength <= limit);

  *distance = bestdist;
  *length = bestlength;
  assert(pos + *length <= size);
}

void ZopfliLZ77Greedy(ZopfliBlockState* s, const unsigned char* in,
                      size_t instart, size_t inend,
                      ZopfliLZ77Store* store, ZopfliHash* h) {
  size_t i = 0, j;
  unsigned short leng;
  unsigned short dist;
  int lengthscore;
  size_t windowstart = instart > 32768
      ? instart - 32768 : 0;
  unsigned short dummysublen[259];



  unsigned prev_length = 0;
  unsigned prev_match = 0;
  int prevlengthscore;
  int match_available = 0;


  if (instart == inend) return;

  ZopfliResetHash(32768, h);
  ZopfliWarmupHash(in, windowstart, inend, h);
  for (i = windowstart; i < instart; i++) {
    ZopfliUpdateHash(in, i, inend, h);
  }

  for (i = instart; i < inend; i++) {
    ZopfliUpdateHash(in, i, inend, h);

    ZopfliFindLongestMatch(s, h, in, i, inend, 258, dummysublen,
                           &dist, &leng);
    lengthscore = GetLengthScore(leng, dist);



    prevlengthscore = GetLengthScore(prev_length, prev_match);
    if (match_available) {
      match_available = 0;
      if (lengthscore > prevlengthscore + 1) {
        ZopfliStoreLitLenDist(in[i - 1], 0, i - 1, store);
        if (lengthscore >= 3 && leng < 258) {
          match_available = 1;
          prev_length = leng;
          prev_match = dist;
          continue;
        }
      } else {

        leng = prev_length;
        dist = prev_match;
        lengthscore = prevlengthscore;

        ZopfliVerifyLenDist(in, inend, i - 1, dist, leng);
        ZopfliStoreLitLenDist(leng, dist, i - 1, store);
        for (j = 2; j < leng; j++) {
          assert(i < inend);
          i++;
          ZopfliUpdateHash(in, i, inend, h);
        }
        continue;
      }
    }
    else if (lengthscore >= 3 && leng < 258) {
      match_available = 1;
      prev_length = leng;
      prev_match = dist;
      continue;
    }




    if (lengthscore >= 3) {
      ZopfliVerifyLenDist(in, inend, i, dist, leng);
      ZopfliStoreLitLenDist(leng, dist, i, store);
    } else {
      leng = 1;
      ZopfliStoreLitLenDist(in[i], 0, i, store);
    }
    for (j = 1; j < leng; j++) {
      assert(i < inend);
      i++;
      ZopfliUpdateHash(in, i, inend, h);
    }
  }
}
