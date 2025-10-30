# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.c"
# 20 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.c"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.h"
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
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.h" 2
# 58 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.h"
void ZopfliDeflate(const ZopfliOptions* options, int btype, int final,
                   const unsigned char* in, size_t insize,
                   unsigned char* bp, unsigned char** out, size_t* outsize);






void ZopfliDeflatePart(const ZopfliOptions* options, int btype, int final,
                       const unsigned char* in, size_t instart, size_t inend,
                       unsigned char* bp, unsigned char** out,
                       size_t* outsize);
# 79 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.h"
double ZopfliCalculateBlockSize(const ZopfliLZ77Store* lz77,
                                size_t lstart, size_t lend, int btype);




double ZopfliCalculateBlockSizeAutoType(const ZopfliLZ77Store* lz77,
                                        size_t lstart, size_t lend);
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 1
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.h" 1
# 31 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 32 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.h" 2
# 42 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.h"
void ZopfliBlockSplitLZ77(const ZopfliOptions* options,
                          const ZopfliLZ77Store* lz77, size_t maxblocks,
                          size_t** splitpoints, size_t* npoints);
# 60 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.h"
void ZopfliBlockSplit(const ZopfliOptions* options,
                      const unsigned char* in, size_t instart, size_t inend,
                      size_t maxblocks, size_t** splitpoints, size_t* npoints);





void ZopfliBlockSplitSimple(const unsigned char* in,
                            size_t instart, size_t inend,
                            size_t blocksize,
                            size_t** splitpoints, size_t* npoints);
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/squeeze.h" 1
# 41 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/squeeze.h"
void ZopfliLZ77Optimal(ZopfliBlockState *s,
                       const unsigned char* in, size_t instart, size_t inend,
                       int numiterations,
                       ZopfliLZ77Store* store);
# 56 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/squeeze.h"
void ZopfliLZ77OptimalFixed(ZopfliBlockState *s,
                            const unsigned char* in,
                            size_t instart, size_t inend,
                            ZopfliLZ77Store* store);
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.c" 2
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
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/tree.h" 1
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/tree.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/tree.h" 2





void ZopfliCalculateBitLengths(const size_t* count, size_t n, int maxbits,
                               unsigned *bitlengths);




void ZopfliLengthsToSymbols(const unsigned* lengths, size_t n, unsigned maxbits,
                            unsigned* symbols);
# 49 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/tree.h"
void ZopfliCalculateEntropy(const size_t* count, size_t n, double* bitlengths);
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.c" 2
# 38 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.c"
static void AddBit(int bit,
                   unsigned char* bp, unsigned char** out, size_t* outsize) {
  if (*bp == 0) { if (!((*outsize) & ((*outsize) - 1))) { (*out) = (*outsize) == 0 ? malloc(sizeof(**out)) : realloc((*out), (*outsize) * 2 * sizeof(**out)); } (*out)[(*outsize)] = (0); (*outsize)++;};
  (*out)[*outsize - 1] |= bit << *bp;
  *bp = (*bp + 1) & 7;
}

static void AddBits(unsigned symbol, unsigned length,
                    unsigned char* bp, unsigned char** out, size_t* outsize) {

  unsigned i;
  for (i = 0; i < length; i++) {
    unsigned bit = (symbol >> i) & 1;
    if (*bp == 0) { if (!((*outsize) & ((*outsize) - 1))) { (*out) = (*outsize) == 0 ? malloc(sizeof(**out)) : realloc((*out), (*outsize) * 2 * sizeof(**out)); } (*out)[(*outsize)] = (0); (*outsize)++;};
    (*out)[*outsize - 1] |= bit << *bp;
    *bp = (*bp + 1) & 7;
  }
}





static void AddHuffmanBits(unsigned symbol, unsigned length,
                           unsigned char* bp, unsigned char** out,
                           size_t* outsize) {

  unsigned i;
  for (i = 0; i < length; i++) {
    unsigned bit = (symbol >> (length - i - 1)) & 1;
    if (*bp == 0) { if (!((*outsize) & ((*outsize) - 1))) { (*out) = (*outsize) == 0 ? malloc(sizeof(**out)) : realloc((*out), (*outsize) * 2 * sizeof(**out)); } (*out)[(*outsize)] = (0); (*outsize)++;};
    (*out)[*outsize - 1] |= bit << *bp;
    *bp = (*bp + 1) & 7;
  }
}
# 86 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.c"
static void PatchDistanceCodesForBuggyDecoders(unsigned* d_lengths) {
  int num_dist_codes = 0;
  int i;
  for (i = 0; i < 30 ; i++) {
    if (d_lengths[i]) num_dist_codes++;
    if (num_dist_codes >= 2) return;
  }

  if (num_dist_codes == 0) {
    d_lengths[0] = d_lengths[1] = 1;
  } else if (num_dist_codes == 1) {
    d_lengths[d_lengths[0] ? 1 : 0] = 1;
  }
}





static size_t EncodeTree(const unsigned* ll_lengths,
                         const unsigned* d_lengths,
                         int use_16, int use_17, int use_18,
                         unsigned char* bp,
                         unsigned char** out, size_t* outsize) {
  unsigned lld_total;

  unsigned* rle = 0;
  unsigned* rle_bits = 0;
  size_t rle_size = 0;
  size_t rle_bits_size = 0;
  unsigned hlit = 29;
  unsigned hdist = 29;
  unsigned hclen;
  unsigned hlit2;
  size_t i, j;
  size_t clcounts[19];
  unsigned clcl[19];
  unsigned clsymbols[19];

  static const unsigned order[19] = {
    16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15
  };
  int size_only = !out;
  size_t result_size = 0;

  for(i = 0; i < 19; i++) clcounts[i] = 0;


  while (hlit > 0 && ll_lengths[257 + hlit - 1] == 0) hlit--;
  while (hdist > 0 && d_lengths[1 + hdist - 1] == 0) hdist--;
  hlit2 = hlit + 257;

  lld_total = hlit2 + hdist + 1;

  for (i = 0; i < lld_total; i++) {

    unsigned char symbol = i < hlit2 ? ll_lengths[i] : d_lengths[i - hlit2];
    unsigned count = 1;
    if(use_16 || (symbol == 0 && (use_17 || use_18))) {
      for (j = i + 1; j < lld_total && symbol ==
          (j < hlit2 ? ll_lengths[j] : d_lengths[j - hlit2]); j++) {
        count++;
      }
    }
    i += count - 1;


    if (symbol == 0 && count >= 3) {
      if (use_18) {
        while (count >= 11) {
          unsigned count2 = count > 138 ? 138 : count;
          if (!size_only) {
            { if (!((*&rle_size) & ((*&rle_size) - 1))) { (*&rle) = (*&rle_size) == 0 ? malloc(sizeof(**&rle)) : realloc((*&rle), (*&rle_size) * 2 * sizeof(**&rle)); } (*&rle)[(*&rle_size)] = (18); (*&rle_size)++;};
            { if (!((*&rle_bits_size) & ((*&rle_bits_size) - 1))) { (*&rle_bits) = (*&rle_bits_size) == 0 ? malloc(sizeof(**&rle_bits)) : realloc((*&rle_bits), (*&rle_bits_size) * 2 * sizeof(**&rle_bits)); } (*&rle_bits)[(*&rle_bits_size)] = (count2 - 11); (*&rle_bits_size)++;};
          }
          clcounts[18]++;
          count -= count2;
        }
      }
      if (use_17) {
        while (count >= 3) {
          unsigned count2 = count > 10 ? 10 : count;
          if (!size_only) {
            { if (!((*&rle_size) & ((*&rle_size) - 1))) { (*&rle) = (*&rle_size) == 0 ? malloc(sizeof(**&rle)) : realloc((*&rle), (*&rle_size) * 2 * sizeof(**&rle)); } (*&rle)[(*&rle_size)] = (17); (*&rle_size)++;};
            { if (!((*&rle_bits_size) & ((*&rle_bits_size) - 1))) { (*&rle_bits) = (*&rle_bits_size) == 0 ? malloc(sizeof(**&rle_bits)) : realloc((*&rle_bits), (*&rle_bits_size) * 2 * sizeof(**&rle_bits)); } (*&rle_bits)[(*&rle_bits_size)] = (count2 - 3); (*&rle_bits_size)++;};
          }
          clcounts[17]++;
          count -= count2;
        }
      }
    }


    if (use_16 && count >= 4) {
      count--;
      clcounts[symbol]++;
      if (!size_only) {
        { if (!((*&rle_size) & ((*&rle_size) - 1))) { (*&rle) = (*&rle_size) == 0 ? malloc(sizeof(**&rle)) : realloc((*&rle), (*&rle_size) * 2 * sizeof(**&rle)); } (*&rle)[(*&rle_size)] = (symbol); (*&rle_size)++;};
        { if (!((*&rle_bits_size) & ((*&rle_bits_size) - 1))) { (*&rle_bits) = (*&rle_bits_size) == 0 ? malloc(sizeof(**&rle_bits)) : realloc((*&rle_bits), (*&rle_bits_size) * 2 * sizeof(**&rle_bits)); } (*&rle_bits)[(*&rle_bits_size)] = (0); (*&rle_bits_size)++;};
      }
      while (count >= 3) {
        unsigned count2 = count > 6 ? 6 : count;
        if (!size_only) {
          { if (!((*&rle_size) & ((*&rle_size) - 1))) { (*&rle) = (*&rle_size) == 0 ? malloc(sizeof(**&rle)) : realloc((*&rle), (*&rle_size) * 2 * sizeof(**&rle)); } (*&rle)[(*&rle_size)] = (16); (*&rle_size)++;};
          { if (!((*&rle_bits_size) & ((*&rle_bits_size) - 1))) { (*&rle_bits) = (*&rle_bits_size) == 0 ? malloc(sizeof(**&rle_bits)) : realloc((*&rle_bits), (*&rle_bits_size) * 2 * sizeof(**&rle_bits)); } (*&rle_bits)[(*&rle_bits_size)] = (count2 - 3); (*&rle_bits_size)++;};
        }
        clcounts[16]++;
        count -= count2;
      }
    }


    clcounts[symbol] += count;
    while (count > 0) {
      if (!size_only) {
        { if (!((*&rle_size) & ((*&rle_size) - 1))) { (*&rle) = (*&rle_size) == 0 ? malloc(sizeof(**&rle)) : realloc((*&rle), (*&rle_size) * 2 * sizeof(**&rle)); } (*&rle)[(*&rle_size)] = (symbol); (*&rle_size)++;};
        { if (!((*&rle_bits_size) & ((*&rle_bits_size) - 1))) { (*&rle_bits) = (*&rle_bits_size) == 0 ? malloc(sizeof(**&rle_bits)) : realloc((*&rle_bits), (*&rle_bits_size) * 2 * sizeof(**&rle_bits)); } (*&rle_bits)[(*&rle_bits_size)] = (0); (*&rle_bits_size)++;};
      }
      count--;
    }
  }

  ZopfliCalculateBitLengths(clcounts, 19, 7, clcl);
  if (!size_only) ZopfliLengthsToSymbols(clcl, 19, 7, clsymbols);

  hclen = 15;

  while (hclen > 0 && clcounts[order[hclen + 4 - 1]] == 0) hclen--;

  if (!size_only) {
    AddBits(hlit, 5, bp, out, outsize);
    AddBits(hdist, 5, bp, out, outsize);
    AddBits(hclen, 4, bp, out, outsize);

    for (i = 0; i < hclen + 4; i++) {
      AddBits(clcl[order[i]], 3, bp, out, outsize);
    }

    for (i = 0; i < rle_size; i++) {
      unsigned symbol = clsymbols[rle[i]];
      AddHuffmanBits(symbol, clcl[rle[i]], bp, out, outsize);

      if (rle[i] == 16) AddBits(rle_bits[i], 2, bp, out, outsize);
      else if (rle[i] == 17) AddBits(rle_bits[i], 3, bp, out, outsize);
      else if (rle[i] == 18) AddBits(rle_bits[i], 7, bp, out, outsize);
    }
  }

  result_size += 14;
  result_size += (hclen + 4) * 3;
  for(i = 0; i < 19; i++) {
    result_size += clcl[i] * clcounts[i];
  }

  result_size += clcounts[16] * 2;
  result_size += clcounts[17] * 3;
  result_size += clcounts[18] * 7;


  free(rle);
  free(rle_bits);

  return result_size;
}

static void AddDynamicTree(const unsigned* ll_lengths,
                           const unsigned* d_lengths,
                           unsigned char* bp,
                           unsigned char** out, size_t* outsize) {
  int i;
  int best = 0;
  size_t bestsize = 0;

  for(i = 0; i < 8; i++) {
    size_t size = EncodeTree(ll_lengths, d_lengths,
                             i & 1, i & 2, i & 4,
                             0, 0, 0);
    if (bestsize == 0 || size < bestsize) {
      bestsize = size;
      best = i;
    }
  }

  EncodeTree(ll_lengths, d_lengths,
             best & 1, best & 2, best & 4,
             bp, out, outsize);
}




static size_t CalculateTreeSize(const unsigned* ll_lengths,
                                const unsigned* d_lengths) {
  size_t result = 0;
  int i;

  for(i = 0; i < 8; i++) {
    size_t size = EncodeTree(ll_lengths, d_lengths,
                             i & 1, i & 2, i & 4,
                             0, 0, 0);
    if (result == 0 || size < result) result = size;
  }

  return result;
}






static void AddLZ77Data(const ZopfliLZ77Store* lz77,
                        size_t lstart, size_t lend,
                        size_t expected_data_size,
                        const unsigned* ll_symbols, const unsigned* ll_lengths,
                        const unsigned* d_symbols, const unsigned* d_lengths,
                        unsigned char* bp,
                        unsigned char** out, size_t* outsize) {
  size_t testlength = 0;
  size_t i;

  for (i = lstart; i < lend; i++) {
    unsigned dist = lz77->dists[i];
    unsigned litlen = lz77->litlens[i];
    if (dist == 0) {
      assert(litlen < 256);
      assert(ll_lengths[litlen] > 0);
      AddHuffmanBits(ll_symbols[litlen], ll_lengths[litlen], bp, out, outsize);
      testlength++;
    } else {
      unsigned lls = ZopfliGetLengthSymbol(litlen);
      unsigned ds = ZopfliGetDistSymbol(dist);
      assert(litlen >= 3 && litlen <= 288);
      assert(ll_lengths[lls] > 0);
      assert(d_lengths[ds] > 0);
      AddHuffmanBits(ll_symbols[lls], ll_lengths[lls], bp, out, outsize);
      AddBits(ZopfliGetLengthExtraBitsValue(litlen),
              ZopfliGetLengthExtraBits(litlen),
              bp, out, outsize);
      AddHuffmanBits(d_symbols[ds], d_lengths[ds], bp, out, outsize);
      AddBits(ZopfliGetDistExtraBitsValue(dist),
              ZopfliGetDistExtraBits(dist),
              bp, out, outsize);
      testlength += litlen;
    }
  }
  assert(expected_data_size == 0 || testlength == expected_data_size);
}

static void GetFixedTree(unsigned* ll_lengths, unsigned* d_lengths) {
  size_t i;
  for (i = 0; i < 144; i++) ll_lengths[i] = 8;
  for (i = 144; i < 256; i++) ll_lengths[i] = 9;
  for (i = 256; i < 280; i++) ll_lengths[i] = 7;
  for (i = 280; i < 288; i++) ll_lengths[i] = 8;
  for (i = 0; i < 32; i++) d_lengths[i] = 5;
}





static size_t CalculateBlockSymbolSizeSmall(const unsigned* ll_lengths,
                                            const unsigned* d_lengths,
                                            const ZopfliLZ77Store* lz77,
                                            size_t lstart, size_t lend) {
  size_t result = 0;
  size_t i;
  for (i = lstart; i < lend; i++) {
    assert(i < lz77->size);
    assert(lz77->litlens[i] < 259);
    if (lz77->dists[i] == 0) {
      result += ll_lengths[lz77->litlens[i]];
    } else {
      int ll_symbol = ZopfliGetLengthSymbol(lz77->litlens[i]);
      int d_symbol = ZopfliGetDistSymbol(lz77->dists[i]);
      result += ll_lengths[ll_symbol];
      result += d_lengths[d_symbol];
      result += ZopfliGetLengthSymbolExtraBits(ll_symbol);
      result += ZopfliGetDistSymbolExtraBits(d_symbol);
    }
  }
  result += ll_lengths[256];
  return result;
}




static size_t CalculateBlockSymbolSizeGivenCounts(const size_t* ll_counts,
                                                  const size_t* d_counts,
                                                  const unsigned* ll_lengths,
                                                  const unsigned* d_lengths,
                                                  const ZopfliLZ77Store* lz77,
                                                  size_t lstart, size_t lend) {
  size_t result = 0;
  size_t i;
  if (lstart + 288 * 3 > lend) {
    return CalculateBlockSymbolSizeSmall(
        ll_lengths, d_lengths, lz77, lstart, lend);
  } else {
    for (i = 0; i < 256; i++) {
      result += ll_lengths[i] * ll_counts[i];
    }
    for (i = 257; i < 286; i++) {
      result += ll_lengths[i] * ll_counts[i];
      result += ZopfliGetLengthSymbolExtraBits(i) * ll_counts[i];
    }
    for (i = 0; i < 30; i++) {
      result += d_lengths[i] * d_counts[i];
      result += ZopfliGetDistSymbolExtraBits(i) * d_counts[i];
    }
    result += ll_lengths[256];
    return result;
  }
}




static size_t CalculateBlockSymbolSize(const unsigned* ll_lengths,
                                       const unsigned* d_lengths,
                                       const ZopfliLZ77Store* lz77,
                                       size_t lstart, size_t lend) {
  if (lstart + 288 * 3 > lend) {
    return CalculateBlockSymbolSizeSmall(
        ll_lengths, d_lengths, lz77, lstart, lend);
  } else {
    size_t ll_counts[288];
    size_t d_counts[32];
    ZopfliLZ77GetHistogram(lz77, lstart, lend, ll_counts, d_counts);
    return CalculateBlockSymbolSizeGivenCounts(
        ll_counts, d_counts, ll_lengths, d_lengths, lz77, lstart, lend);
  }
}

static size_t AbsDiff(size_t x, size_t y) {
  if (x > y)
    return x - y;
  else
    return y - x;
}






void OptimizeHuffmanForRle(int length, size_t* counts) {
  int i, k, stride;
  size_t symbol, sum, limit;
  int* good_for_rle;



  for (; length >= 0; --length) {
    if (length == 0) {
      return;
    }
    if (counts[length - 1] != 0) {

      break;
    }
  }


  good_for_rle = (int*)malloc((unsigned)length * sizeof(int));
  for (i = 0; i < length; ++i) good_for_rle[i] = 0;




  symbol = counts[0];
  stride = 0;
  for (i = 0; i < length + 1; ++i) {
    if (i == length || counts[i] != symbol) {
      if ((symbol == 0 && stride >= 5) || (symbol != 0 && stride >= 7)) {
        for (k = 0; k < stride; ++k) {
          good_for_rle[i - k - 1] = 1;
        }
      }
      stride = 1;
      if (i != length) {
        symbol = counts[i];
      }
    } else {
      ++stride;
    }
  }


  stride = 0;
  limit = counts[0];
  sum = 0;
  for (i = 0; i < length + 1; ++i) {
    if (i == length || good_for_rle[i]

        || AbsDiff(counts[i], limit) >= 4) {
      if (stride >= 4 || (stride >= 3 && sum == 0)) {

        int count = (sum + stride / 2) / stride;
        if (count < 1) count = 1;
        if (sum == 0) {

          count = 0;
        }
        for (k = 0; k < stride; ++k) {


          counts[i - k - 1] = count;
        }
      }
      stride = 0;
      sum = 0;
      if (i < length - 3) {


        limit = (counts[i] + counts[i + 1] +
                 counts[i + 2] + counts[i + 3] + 2) / 4;
      } else if (i < length) {
        limit = counts[i];
      } else {
        limit = 0;
      }
    }
    ++stride;
    if (i != length) {
      sum += counts[i];
    }
  }

  free(good_for_rle);
}






static double TryOptimizeHuffmanForRle(
    const ZopfliLZ77Store* lz77, size_t lstart, size_t lend,
    const size_t* ll_counts, const size_t* d_counts,
    unsigned* ll_lengths, unsigned* d_lengths) {
  size_t ll_counts2[288];
  size_t d_counts2[32];
  unsigned ll_lengths2[288];
  unsigned d_lengths2[32];
  double treesize;
  double datasize;
  double treesize2;
  double datasize2;

  treesize = CalculateTreeSize(ll_lengths, d_lengths);
  datasize = CalculateBlockSymbolSizeGivenCounts(ll_counts, d_counts,
      ll_lengths, d_lengths, lz77, lstart, lend);

  memcpy(ll_counts2, ll_counts, sizeof(ll_counts2));
  memcpy(d_counts2, d_counts, sizeof(d_counts2));
  OptimizeHuffmanForRle(288, ll_counts2);
  OptimizeHuffmanForRle(32, d_counts2);
  ZopfliCalculateBitLengths(ll_counts2, 288, 15, ll_lengths2);
  ZopfliCalculateBitLengths(d_counts2, 32, 15, d_lengths2);
  PatchDistanceCodesForBuggyDecoders(d_lengths2);

  treesize2 = CalculateTreeSize(ll_lengths2, d_lengths2);
  datasize2 = CalculateBlockSymbolSizeGivenCounts(ll_counts, d_counts,
      ll_lengths2, d_lengths2, lz77, lstart, lend);

  if (treesize2 + datasize2 < treesize + datasize) {
    memcpy(ll_lengths, ll_lengths2, sizeof(ll_lengths2));
    memcpy(d_lengths, d_lengths2, sizeof(d_lengths2));
    return treesize2 + datasize2;
  }
  return treesize + datasize;
}
# 569 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.c"
static double GetDynamicLengths(const ZopfliLZ77Store* lz77,
                                size_t lstart, size_t lend,
                                unsigned* ll_lengths, unsigned* d_lengths) {
  size_t ll_counts[288];
  size_t d_counts[32];

  ZopfliLZ77GetHistogram(lz77, lstart, lend, ll_counts, d_counts);
  ll_counts[256] = 1;
  ZopfliCalculateBitLengths(ll_counts, 288, 15, ll_lengths);
  ZopfliCalculateBitLengths(d_counts, 32, 15, d_lengths);
  PatchDistanceCodesForBuggyDecoders(d_lengths);
  return TryOptimizeHuffmanForRle(
      lz77, lstart, lend, ll_counts, d_counts, ll_lengths, d_lengths);
}

double ZopfliCalculateBlockSize(const ZopfliLZ77Store* lz77,
                                size_t lstart, size_t lend, int btype) {
  unsigned ll_lengths[288];
  unsigned d_lengths[32];

  double result = 3;

  if (btype == 0) {
    size_t length = ZopfliLZ77GetByteRange(lz77, lstart, lend);
    size_t rem = length % 65535;
    size_t blocks = length / 65535 + (rem ? 1 : 0);



    return blocks * 5 * 8 + length * 8;
  } if (btype == 1) {
    GetFixedTree(ll_lengths, d_lengths);
    result += CalculateBlockSymbolSize(
        ll_lengths, d_lengths, lz77, lstart, lend);
  } else {
    result += GetDynamicLengths(lz77, lstart, lend, ll_lengths, d_lengths);
  }

  return result;
}

double ZopfliCalculateBlockSizeAutoType(const ZopfliLZ77Store* lz77,
                                        size_t lstart, size_t lend) {
  double uncompressedcost = ZopfliCalculateBlockSize(lz77, lstart, lend, 0);


  double fixedcost = (lz77->size > 1000) ?
      uncompressedcost : ZopfliCalculateBlockSize(lz77, lstart, lend, 1);
  double dyncost = ZopfliCalculateBlockSize(lz77, lstart, lend, 2);
  return (uncompressedcost < fixedcost && uncompressedcost < dyncost)
      ? uncompressedcost
      : (fixedcost < dyncost ? fixedcost : dyncost);
}



static void AddNonCompressedBlock(const ZopfliOptions* options, int final,
                                  const unsigned char* in, size_t instart,
                                  size_t inend,
                                  unsigned char* bp,
                                  unsigned char** out, size_t* outsize) {
  size_t pos = instart;
  (void)options;
  for (;;) {
    size_t i;
    unsigned short blocksize = 65535;
    unsigned short nlen;
    int currentfinal;

    if (pos + blocksize > inend) blocksize = inend - pos;
    currentfinal = pos + blocksize >= inend;

    nlen = ~blocksize;

    AddBit(final && currentfinal, bp, out, outsize);

    AddBit(0, bp, out, outsize);
    AddBit(0, bp, out, outsize);


    *bp = 0;

    { if (!((*outsize) & ((*outsize) - 1))) { (*out) = (*outsize) == 0 ? malloc(sizeof(**out)) : realloc((*out), (*outsize) * 2 * sizeof(**out)); } (*out)[(*outsize)] = (blocksize % 256); (*outsize)++;};
    { if (!((*outsize) & ((*outsize) - 1))) { (*out) = (*outsize) == 0 ? malloc(sizeof(**out)) : realloc((*out), (*outsize) * 2 * sizeof(**out)); } (*out)[(*outsize)] = ((blocksize / 256) % 256); (*outsize)++;};
    { if (!((*outsize) & ((*outsize) - 1))) { (*out) = (*outsize) == 0 ? malloc(sizeof(**out)) : realloc((*out), (*outsize) * 2 * sizeof(**out)); } (*out)[(*outsize)] = (nlen % 256); (*outsize)++;};
    { if (!((*outsize) & ((*outsize) - 1))) { (*out) = (*outsize) == 0 ? malloc(sizeof(**out)) : realloc((*out), (*outsize) * 2 * sizeof(**out)); } (*out)[(*outsize)] = ((nlen / 256) % 256); (*outsize)++;};

    for (i = 0; i < blocksize; i++) {
      { if (!((*outsize) & ((*outsize) - 1))) { (*out) = (*outsize) == 0 ? malloc(sizeof(**out)) : realloc((*out), (*outsize) * 2 * sizeof(**out)); } (*out)[(*outsize)] = (in[pos + i]); (*outsize)++;};
    }

    if (currentfinal) break;
    pos += blocksize;
  }
}
# 682 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.c"
static void AddLZ77Block(const ZopfliOptions* options, int btype, int final,
                         const ZopfliLZ77Store* lz77,
                         size_t lstart, size_t lend,
                         size_t expected_data_size,
                         unsigned char* bp,
                         unsigned char** out, size_t* outsize) {
  unsigned ll_lengths[288];
  unsigned d_lengths[32];
  unsigned ll_symbols[288];
  unsigned d_symbols[32];
  size_t detect_block_size = *outsize;
  size_t compressed_size;
  size_t uncompressed_size = 0;
  size_t i;
  if (btype == 0) {
    size_t length = ZopfliLZ77GetByteRange(lz77, lstart, lend);
    size_t pos = lstart == lend ? 0 : lz77->pos[lstart];
    size_t end = pos + length;
    AddNonCompressedBlock(options, final,
                          lz77->data, pos, end, bp, out, outsize);
    return;
  }

  AddBit(final, bp, out, outsize);
  AddBit(btype & 1, bp, out, outsize);
  AddBit((btype & 2) >> 1, bp, out, outsize);

  if (btype == 1) {

    GetFixedTree(ll_lengths, d_lengths);
  } else {

    unsigned detect_tree_size;
    assert(btype == 2);

    GetDynamicLengths(lz77, lstart, lend, ll_lengths, d_lengths);

    detect_tree_size = *outsize;
    AddDynamicTree(ll_lengths, d_lengths, bp, out, outsize);
    if (options->verbose) {
      fprintf(stderr, "treesize: %d\n", (int)(*outsize - detect_tree_size));
    }
  }

  ZopfliLengthsToSymbols(ll_lengths, 288, 15, ll_symbols);
  ZopfliLengthsToSymbols(d_lengths, 32, 15, d_symbols);

  detect_block_size = *outsize;
  AddLZ77Data(lz77, lstart, lend, expected_data_size,
              ll_symbols, ll_lengths, d_symbols, d_lengths,
              bp, out, outsize);

  AddHuffmanBits(ll_symbols[256], ll_lengths[256], bp, out, outsize);

  for (i = lstart; i < lend; i++) {
    uncompressed_size += lz77->dists[i] == 0 ? 1 : lz77->litlens[i];
  }
  compressed_size = *outsize - detect_block_size;
  if (options->verbose) {
    fprintf(stderr, "compressed block size: %d (%dk) (unc: %d)\n",
           (int)compressed_size, (int)(compressed_size / 1024),
           (int)(uncompressed_size));
  }
}

static void AddLZ77BlockAutoType(const ZopfliOptions* options, int final,
                                 const ZopfliLZ77Store* lz77,
                                 size_t lstart, size_t lend,
                                 size_t expected_data_size,
                                 unsigned char* bp,
                                 unsigned char** out, size_t* outsize) {
  double uncompressedcost = ZopfliCalculateBlockSize(lz77, lstart, lend, 0);
  double fixedcost = ZopfliCalculateBlockSize(lz77, lstart, lend, 1);
  double dyncost = ZopfliCalculateBlockSize(lz77, lstart, lend, 2);




  int expensivefixed = (lz77->size < 1000) || fixedcost <= dyncost * 1.1;

  ZopfliLZ77Store fixedstore;
  if (lstart == lend) {

    AddBits(final, 1, bp, out, outsize);
    AddBits(1, 2, bp, out, outsize);
    AddBits(0, 7, bp, out, outsize);
    return;
  }
  ZopfliInitLZ77Store(lz77->data, &fixedstore);
  if (expensivefixed) {

    size_t instart = lz77->pos[lstart];
    size_t inend = instart + ZopfliLZ77GetByteRange(lz77, lstart, lend);

    ZopfliBlockState s;
    ZopfliInitBlockState(options, instart, inend, 1, &s);
    ZopfliLZ77OptimalFixed(&s, lz77->data, instart, inend, &fixedstore);
    fixedcost = ZopfliCalculateBlockSize(&fixedstore, 0, fixedstore.size, 1);
    ZopfliCleanBlockState(&s);
  }

  if (uncompressedcost < fixedcost && uncompressedcost < dyncost) {
    AddLZ77Block(options, 0, final, lz77, lstart, lend,
                 expected_data_size, bp, out, outsize);
  } else if (fixedcost < dyncost) {
    if (expensivefixed) {
      AddLZ77Block(options, 1, final, &fixedstore, 0, fixedstore.size,
                   expected_data_size, bp, out, outsize);
    } else {
      AddLZ77Block(options, 1, final, lz77, lstart, lend,
                   expected_data_size, bp, out, outsize);
    }
  } else {
    AddLZ77Block(options, 2, final, lz77, lstart, lend,
                 expected_data_size, bp, out, outsize);
  }

  ZopfliCleanLZ77Store(&fixedstore);
}
# 811 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.c"
void ZopfliDeflatePart(const ZopfliOptions* options, int btype, int final,
                       const unsigned char* in, size_t instart, size_t inend,
                       unsigned char* bp, unsigned char** out,
                       size_t* outsize) {
  size_t i;

  size_t* splitpoints_uncompressed = 0;
  size_t npoints = 0;
  size_t* splitpoints = 0;
  double totalcost = 0;
  ZopfliLZ77Store lz77;




  if (btype == 0) {
    AddNonCompressedBlock(options, final, in, instart, inend, bp, out, outsize);
    return;
  } else if (btype == 1) {
    ZopfliLZ77Store store;
    ZopfliBlockState s;
    ZopfliInitLZ77Store(in, &store);
    ZopfliInitBlockState(options, instart, inend, 1, &s);

    ZopfliLZ77OptimalFixed(&s, in, instart, inend, &store);
    AddLZ77Block(options, btype, final, &store, 0, store.size, 0,
                 bp, out, outsize);

    ZopfliCleanBlockState(&s);
    ZopfliCleanLZ77Store(&store);
    return;
  }


  if (options->blocksplitting) {
    ZopfliBlockSplit(options, in, instart, inend,
                     options->blocksplittingmax,
                     &splitpoints_uncompressed, &npoints);
    splitpoints = (size_t*)malloc(sizeof(*splitpoints) * npoints);
  }

  ZopfliInitLZ77Store(in, &lz77);

  for (i = 0; i <= npoints; i++) {
    size_t start = i == 0 ? instart : splitpoints_uncompressed[i - 1];
    size_t end = i == npoints ? inend : splitpoints_uncompressed[i];
    ZopfliBlockState s;
    ZopfliLZ77Store store;
    ZopfliInitLZ77Store(in, &store);
    ZopfliInitBlockState(options, start, end, 1, &s);
    ZopfliLZ77Optimal(&s, in, start, end, options->numiterations, &store);
    totalcost += ZopfliCalculateBlockSizeAutoType(&store, 0, store.size);

    ZopfliAppendLZ77Store(&store, &lz77);
    if (i < npoints) splitpoints[i] = lz77.size;

    ZopfliCleanBlockState(&s);
    ZopfliCleanLZ77Store(&store);
  }


  if (options->blocksplitting && npoints > 1) {
    size_t* splitpoints2 = 0;
    size_t npoints2 = 0;
    double totalcost2 = 0;

    ZopfliBlockSplitLZ77(options, &lz77,
                         options->blocksplittingmax, &splitpoints2, &npoints2);

    for (i = 0; i <= npoints2; i++) {
      size_t start = i == 0 ? 0 : splitpoints2[i - 1];
      size_t end = i == npoints2 ? lz77.size : splitpoints2[i];
      totalcost2 += ZopfliCalculateBlockSizeAutoType(&lz77, start, end);
    }

    if (totalcost2 < totalcost) {
      free(splitpoints);
      splitpoints = splitpoints2;
      npoints = npoints2;
    } else {
      free(splitpoints2);
    }
  }

  for (i = 0; i <= npoints; i++) {
    size_t start = i == 0 ? 0 : splitpoints[i - 1];
    size_t end = i == npoints ? lz77.size : splitpoints[i];
    AddLZ77BlockAutoType(options, i == npoints && final,
                         &lz77, start, end, 0,
                         bp, out, outsize);
  }

  ZopfliCleanLZ77Store(&lz77);
  free(splitpoints);
  free(splitpoints_uncompressed);
}

void ZopfliDeflate(const ZopfliOptions* options, int btype, int final,
                   const unsigned char* in, size_t insize,
                   unsigned char* bp, unsigned char** out, size_t* outsize) {
 size_t offset = *outsize;



  size_t i = 0;
  do {
    int masterfinal = (i + 1000000 >= insize);
    int final2 = final && masterfinal;
    size_t size = masterfinal ? insize - i : 1000000;
    ZopfliDeflatePart(options, btype, final2,
                      in, i, i + size, bp, out, outsize);
    i += size;
  } while (i < insize);

  if (options->verbose) {
    fprintf(stderr,
            "Original Size: %lu, Deflate: %lu, Compression: %f%% Removed\n",
            (unsigned long)insize, (unsigned long)(*outsize - offset),
            100.0 * (double)(insize - (*outsize - offset)) / (double)insize);
  }
}
# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.c"
# 20 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.c"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.h"
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
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.h" 2
# 58 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.h"
void ZopfliDeflate(const ZopfliOptions* options, int btype, int final,
                   const unsigned char* in, size_t insize,
                   unsigned char* bp, unsigned char** out, size_t* outsize);






void ZopfliDeflatePart(const ZopfliOptions* options, int btype, int final,
                       const unsigned char* in, size_t instart, size_t inend,
                       unsigned char* bp, unsigned char** out,
                       size_t* outsize);
# 79 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.h"
double ZopfliCalculateBlockSize(const ZopfliLZ77Store* lz77,
                                size_t lstart, size_t lend, int btype);




double ZopfliCalculateBlockSizeAutoType(const ZopfliLZ77Store* lz77,
                                        size_t lstart, size_t lend);
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 1
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.h" 1
# 31 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 32 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.h" 2
# 42 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.h"
void ZopfliBlockSplitLZ77(const ZopfliOptions* options,
                          const ZopfliLZ77Store* lz77, size_t maxblocks,
                          size_t** splitpoints, size_t* npoints);
# 60 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.h"
void ZopfliBlockSplit(const ZopfliOptions* options,
                      const unsigned char* in, size_t instart, size_t inend,
                      size_t maxblocks, size_t** splitpoints, size_t* npoints);





void ZopfliBlockSplitSimple(const unsigned char* in,
                            size_t instart, size_t inend,
                            size_t blocksize,
                            size_t** splitpoints, size_t* npoints);
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/squeeze.h" 1
# 41 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/squeeze.h"
void ZopfliLZ77Optimal(ZopfliBlockState *s,
                       const unsigned char* in, size_t instart, size_t inend,
                       int numiterations,
                       ZopfliLZ77Store* store);
# 56 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/squeeze.h"
void ZopfliLZ77OptimalFixed(ZopfliBlockState *s,
                            const unsigned char* in,
                            size_t instart, size_t inend,
                            ZopfliLZ77Store* store);
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.c" 2
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
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/tree.h" 1
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/tree.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/tree.h" 2





void ZopfliCalculateBitLengths(const size_t* count, size_t n, int maxbits,
                               unsigned *bitlengths);




void ZopfliLengthsToSymbols(const unsigned* lengths, size_t n, unsigned maxbits,
                            unsigned* symbols);
# 49 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/tree.h"
void ZopfliCalculateEntropy(const size_t* count, size_t n, double* bitlengths);
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.c" 2
# 38 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.c"
static void AddBit(int bit,
                   unsigned char* bp, unsigned char** out, size_t* outsize) {
  if (*bp == 0) { if (!((*outsize) & ((*outsize) - 1))) { (*out) = (*outsize) == 0 ? malloc(sizeof(**out)) : realloc((*out), (*outsize) * 2 * sizeof(**out)); } (*out)[(*outsize)] = (0); (*outsize)++;};
  (*out)[*outsize - 1] |= bit << *bp;
  *bp = (*bp + 1) & 7;
}

static void AddBits(unsigned symbol, unsigned length,
                    unsigned char* bp, unsigned char** out, size_t* outsize) {

  unsigned i;
  for (i = 0; i < length; i++) {
    unsigned bit = (symbol >> i) & 1;
    if (*bp == 0) { if (!((*outsize) & ((*outsize) - 1))) { (*out) = (*outsize) == 0 ? malloc(sizeof(**out)) : realloc((*out), (*outsize) * 2 * sizeof(**out)); } (*out)[(*outsize)] = (0); (*outsize)++;};
    (*out)[*outsize - 1] |= bit << *bp;
    *bp = (*bp + 1) & 7;
  }
}





static void AddHuffmanBits(unsigned symbol, unsigned length,
                           unsigned char* bp, unsigned char** out,
                           size_t* outsize) {

  unsigned i;
  for (i = 0; i < length; i++) {
    unsigned bit = (symbol >> (length - i - 1)) & 1;
    if (*bp == 0) { if (!((*outsize) & ((*outsize) - 1))) { (*out) = (*outsize) == 0 ? malloc(sizeof(**out)) : realloc((*out), (*outsize) * 2 * sizeof(**out)); } (*out)[(*outsize)] = (0); (*outsize)++;};
    (*out)[*outsize - 1] |= bit << *bp;
    *bp = (*bp + 1) & 7;
  }
}
# 86 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.c"
static void PatchDistanceCodesForBuggyDecoders(unsigned* d_lengths) {
  int num_dist_codes = 0;
  int i;
  for (i = 0; i < 30 ; i++) {
    if (d_lengths[i]) num_dist_codes++;
    if (num_dist_codes >= 2) return;
  }

  if (num_dist_codes == 0) {
    d_lengths[0] = d_lengths[1] = 1;
  } else if (num_dist_codes == 1) {
    d_lengths[d_lengths[0] ? 1 : 0] = 1;
  }
}





static size_t EncodeTree(const unsigned* ll_lengths,
                         const unsigned* d_lengths,
                         int use_16, int use_17, int use_18,
                         unsigned char* bp,
                         unsigned char** out, size_t* outsize) {
  unsigned lld_total;

  unsigned* rle = 0;
  unsigned* rle_bits = 0;
  size_t rle_size = 0;
  size_t rle_bits_size = 0;
  unsigned hlit = 29;
  unsigned hdist = 29;
  unsigned hclen;
  unsigned hlit2;
  size_t i, j;
  size_t clcounts[19];
  unsigned clcl[19];
  unsigned clsymbols[19];

  static const unsigned order[19] = {
    16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15
  };
  int size_only = !out;
  size_t result_size = 0;

  for(i = 0; i < 19; i++) clcounts[i] = 0;


  while (hlit > 0 && ll_lengths[257 + hlit - 1] == 0) hlit--;
  while (hdist > 0 && d_lengths[1 + hdist - 1] == 0) hdist--;
  hlit2 = hlit + 257;

  lld_total = hlit2 + hdist + 1;

  for (i = 0; i < lld_total; i++) {

    unsigned char symbol = i < hlit2 ? ll_lengths[i] : d_lengths[i - hlit2];
    unsigned count = 1;
    if(use_16 || (symbol == 0 && (use_17 || use_18))) {
      for (j = i + 1; j < lld_total && symbol ==
          (j < hlit2 ? ll_lengths[j] : d_lengths[j - hlit2]); j++) {
        count++;
      }
    }
    i += count - 1;


    if (symbol == 0 && count >= 3) {
      if (use_18) {
        while (count >= 11) {
          unsigned count2 = count > 138 ? 138 : count;
          if (!size_only) {
            { if (!((*&rle_size) & ((*&rle_size) - 1))) { (*&rle) = (*&rle_size) == 0 ? malloc(sizeof(**&rle)) : realloc((*&rle), (*&rle_size) * 2 * sizeof(**&rle)); } (*&rle)[(*&rle_size)] = (18); (*&rle_size)++;};
            { if (!((*&rle_bits_size) & ((*&rle_bits_size) - 1))) { (*&rle_bits) = (*&rle_bits_size) == 0 ? malloc(sizeof(**&rle_bits)) : realloc((*&rle_bits), (*&rle_bits_size) * 2 * sizeof(**&rle_bits)); } (*&rle_bits)[(*&rle_bits_size)] = (count2 - 11); (*&rle_bits_size)++;};
          }
          clcounts[18]++;
          count -= count2;
        }
      }
      if (use_17) {
        while (count >= 3) {
          unsigned count2 = count > 10 ? 10 : count;
          if (!size_only) {
            { if (!((*&rle_size) & ((*&rle_size) - 1))) { (*&rle) = (*&rle_size) == 0 ? malloc(sizeof(**&rle)) : realloc((*&rle), (*&rle_size) * 2 * sizeof(**&rle)); } (*&rle)[(*&rle_size)] = (17); (*&rle_size)++;};
            { if (!((*&rle_bits_size) & ((*&rle_bits_size) - 1))) { (*&rle_bits) = (*&rle_bits_size) == 0 ? malloc(sizeof(**&rle_bits)) : realloc((*&rle_bits), (*&rle_bits_size) * 2 * sizeof(**&rle_bits)); } (*&rle_bits)[(*&rle_bits_size)] = (count2 - 3); (*&rle_bits_size)++;};
          }
          clcounts[17]++;
          count -= count2;
        }
      }
    }


    if (use_16 && count >= 4) {
      count--;
      clcounts[symbol]++;
      if (!size_only) {
        { if (!((*&rle_size) & ((*&rle_size) - 1))) { (*&rle) = (*&rle_size) == 0 ? malloc(sizeof(**&rle)) : realloc((*&rle), (*&rle_size) * 2 * sizeof(**&rle)); } (*&rle)[(*&rle_size)] = (symbol); (*&rle_size)++;};
        { if (!((*&rle_bits_size) & ((*&rle_bits_size) - 1))) { (*&rle_bits) = (*&rle_bits_size) == 0 ? malloc(sizeof(**&rle_bits)) : realloc((*&rle_bits), (*&rle_bits_size) * 2 * sizeof(**&rle_bits)); } (*&rle_bits)[(*&rle_bits_size)] = (0); (*&rle_bits_size)++;};
      }
      while (count >= 3) {
        unsigned count2 = count > 6 ? 6 : count;
        if (!size_only) {
          { if (!((*&rle_size) & ((*&rle_size) - 1))) { (*&rle) = (*&rle_size) == 0 ? malloc(sizeof(**&rle)) : realloc((*&rle), (*&rle_size) * 2 * sizeof(**&rle)); } (*&rle)[(*&rle_size)] = (16); (*&rle_size)++;};
          { if (!((*&rle_bits_size) & ((*&rle_bits_size) - 1))) { (*&rle_bits) = (*&rle_bits_size) == 0 ? malloc(sizeof(**&rle_bits)) : realloc((*&rle_bits), (*&rle_bits_size) * 2 * sizeof(**&rle_bits)); } (*&rle_bits)[(*&rle_bits_size)] = (count2 - 3); (*&rle_bits_size)++;};
        }
        clcounts[16]++;
        count -= count2;
      }
    }


    clcounts[symbol] += count;
    while (count > 0) {
      if (!size_only) {
        { if (!((*&rle_size) & ((*&rle_size) - 1))) { (*&rle) = (*&rle_size) == 0 ? malloc(sizeof(**&rle)) : realloc((*&rle), (*&rle_size) * 2 * sizeof(**&rle)); } (*&rle)[(*&rle_size)] = (symbol); (*&rle_size)++;};
        { if (!((*&rle_bits_size) & ((*&rle_bits_size) - 1))) { (*&rle_bits) = (*&rle_bits_size) == 0 ? malloc(sizeof(**&rle_bits)) : realloc((*&rle_bits), (*&rle_bits_size) * 2 * sizeof(**&rle_bits)); } (*&rle_bits)[(*&rle_bits_size)] = (0); (*&rle_bits_size)++;};
      }
      count--;
    }
  }

  ZopfliCalculateBitLengths(clcounts, 19, 7, clcl);
  if (!size_only) ZopfliLengthsToSymbols(clcl, 19, 7, clsymbols);

  hclen = 15;

  while (hclen > 0 && clcounts[order[hclen + 4 - 1]] == 0) hclen--;

  if (!size_only) {
    AddBits(hlit, 5, bp, out, outsize);
    AddBits(hdist, 5, bp, out, outsize);
    AddBits(hclen, 4, bp, out, outsize);

    for (i = 0; i < hclen + 4; i++) {
      AddBits(clcl[order[i]], 3, bp, out, outsize);
    }

    for (i = 0; i < rle_size; i++) {
      unsigned symbol = clsymbols[rle[i]];
      AddHuffmanBits(symbol, clcl[rle[i]], bp, out, outsize);

      if (rle[i] == 16) AddBits(rle_bits[i], 2, bp, out, outsize);
      else if (rle[i] == 17) AddBits(rle_bits[i], 3, bp, out, outsize);
      else if (rle[i] == 18) AddBits(rle_bits[i], 7, bp, out, outsize);
    }
  }

  result_size += 14;
  result_size += (hclen + 4) * 3;
  for(i = 0; i < 19; i++) {
    result_size += clcl[i] * clcounts[i];
  }

  result_size += clcounts[16] * 2;
  result_size += clcounts[17] * 3;
  result_size += clcounts[18] * 7;


  free(rle);
  free(rle_bits);

  return result_size;
}

static void AddDynamicTree(const unsigned* ll_lengths,
                           const unsigned* d_lengths,
                           unsigned char* bp,
                           unsigned char** out, size_t* outsize) {
  int i;
  int best = 0;
  size_t bestsize = 0;

  for(i = 0; i < 8; i++) {
    size_t size = EncodeTree(ll_lengths, d_lengths,
                             i & 1, i & 2, i & 4,
                             0, 0, 0);
    if (bestsize == 0 || size < bestsize) {
      bestsize = size;
      best = i;
    }
  }

  EncodeTree(ll_lengths, d_lengths,
             best & 1, best & 2, best & 4,
             bp, out, outsize);
}




static size_t CalculateTreeSize(const unsigned* ll_lengths,
                                const unsigned* d_lengths) {
  size_t result = 0;
  int i;

  for(i = 0; i < 8; i++) {
    size_t size = EncodeTree(ll_lengths, d_lengths,
                             i & 1, i & 2, i & 4,
                             0, 0, 0);
    if (result == 0 || size < result) result = size;
  }

  return result;
}






static void AddLZ77Data(const ZopfliLZ77Store* lz77,
                        size_t lstart, size_t lend,
                        size_t expected_data_size,
                        const unsigned* ll_symbols, const unsigned* ll_lengths,
                        const unsigned* d_symbols, const unsigned* d_lengths,
                        unsigned char* bp,
                        unsigned char** out, size_t* outsize) {
  size_t testlength = 0;
  size_t i;

  for (i = lstart; i < lend; i++) {
    unsigned dist = lz77->dists[i];
    unsigned litlen = lz77->litlens[i];
    if (dist == 0) {
      assert(litlen < 256);
      assert(ll_lengths[litlen] > 0);
      AddHuffmanBits(ll_symbols[litlen], ll_lengths[litlen], bp, out, outsize);
      testlength++;
    } else {
      unsigned lls = ZopfliGetLengthSymbol(litlen);
      unsigned ds = ZopfliGetDistSymbol(dist);
      assert(litlen >= 3 && litlen <= 288);
      assert(ll_lengths[lls] > 0);
      assert(d_lengths[ds] > 0);
      AddHuffmanBits(ll_symbols[lls], ll_lengths[lls], bp, out, outsize);
      AddBits(ZopfliGetLengthExtraBitsValue(litlen),
              ZopfliGetLengthExtraBits(litlen),
              bp, out, outsize);
      AddHuffmanBits(d_symbols[ds], d_lengths[ds], bp, out, outsize);
      AddBits(ZopfliGetDistExtraBitsValue(dist),
              ZopfliGetDistExtraBits(dist),
              bp, out, outsize);
      testlength += litlen;
    }
  }
  assert(expected_data_size == 0 || testlength == expected_data_size);
}

static void GetFixedTree(unsigned* ll_lengths, unsigned* d_lengths) {
  size_t i;
  for (i = 0; i < 144; i++) ll_lengths[i] = 8;
  for (i = 144; i < 256; i++) ll_lengths[i] = 9;
  for (i = 256; i < 280; i++) ll_lengths[i] = 7;
  for (i = 280; i < 288; i++) ll_lengths[i] = 8;
  for (i = 0; i < 32; i++) d_lengths[i] = 5;
}





static size_t CalculateBlockSymbolSizeSmall(const unsigned* ll_lengths,
                                            const unsigned* d_lengths,
                                            const ZopfliLZ77Store* lz77,
                                            size_t lstart, size_t lend) {
  size_t result = 0;
  size_t i;
  for (i = lstart; i < lend; i++) {
    assert(i < lz77->size);
    assert(lz77->litlens[i] < 259);
    if (lz77->dists[i] == 0) {
      result += ll_lengths[lz77->litlens[i]];
    } else {
      int ll_symbol = ZopfliGetLengthSymbol(lz77->litlens[i]);
      int d_symbol = ZopfliGetDistSymbol(lz77->dists[i]);
      result += ll_lengths[ll_symbol];
      result += d_lengths[d_symbol];
      result += ZopfliGetLengthSymbolExtraBits(ll_symbol);
      result += ZopfliGetDistSymbolExtraBits(d_symbol);
    }
  }
  result += ll_lengths[256];
  return result;
}




static size_t CalculateBlockSymbolSizeGivenCounts(const size_t* ll_counts,
                                                  const size_t* d_counts,
                                                  const unsigned* ll_lengths,
                                                  const unsigned* d_lengths,
                                                  const ZopfliLZ77Store* lz77,
                                                  size_t lstart, size_t lend) {
  size_t result = 0;
  size_t i;
  if (lstart + 288 * 3 > lend) {
    return CalculateBlockSymbolSizeSmall(
        ll_lengths, d_lengths, lz77, lstart, lend);
  } else {
    for (i = 0; i < 256; i++) {
      result += ll_lengths[i] * ll_counts[i];
    }
    for (i = 257; i < 286; i++) {
      result += ll_lengths[i] * ll_counts[i];
      result += ZopfliGetLengthSymbolExtraBits(i) * ll_counts[i];
    }
    for (i = 0; i < 30; i++) {
      result += d_lengths[i] * d_counts[i];
      result += ZopfliGetDistSymbolExtraBits(i) * d_counts[i];
    }
    result += ll_lengths[256];
    return result;
  }
}




static size_t CalculateBlockSymbolSize(const unsigned* ll_lengths,
                                       const unsigned* d_lengths,
                                       const ZopfliLZ77Store* lz77,
                                       size_t lstart, size_t lend) {
  if (lstart + 288 * 3 > lend) {
    return CalculateBlockSymbolSizeSmall(
        ll_lengths, d_lengths, lz77, lstart, lend);
  } else {
    size_t ll_counts[288];
    size_t d_counts[32];
    ZopfliLZ77GetHistogram(lz77, lstart, lend, ll_counts, d_counts);
    return CalculateBlockSymbolSizeGivenCounts(
        ll_counts, d_counts, ll_lengths, d_lengths, lz77, lstart, lend);
  }
}

static size_t AbsDiff(size_t x, size_t y) {
  if (x > y)
    return x - y;
  else
    return y - x;
}






void OptimizeHuffmanForRle(int length, size_t* counts) {
  int i, k, stride;
  size_t symbol, sum, limit;
  int* good_for_rle;



  for (; length >= 0; --length) {
    if (length == 0) {
      return;
    }
    if (counts[length - 1] != 0) {

      break;
    }
  }


  good_for_rle = (int*)malloc((unsigned)length * sizeof(int));
  for (i = 0; i < length; ++i) good_for_rle[i] = 0;




  symbol = counts[0];
  stride = 0;
  for (i = 0; i < length + 1; ++i) {
    if (i == length || counts[i] != symbol) {
      if ((symbol == 0 && stride >= 5) || (symbol != 0 && stride >= 7)) {
        for (k = 0; k < stride; ++k) {
          good_for_rle[i - k - 1] = 1;
        }
      }
      stride = 1;
      if (i != length) {
        symbol = counts[i];
      }
    } else {
      ++stride;
    }
  }


  stride = 0;
  limit = counts[0];
  sum = 0;
  for (i = 0; i < length + 1; ++i) {
    if (i == length || good_for_rle[i]

        || AbsDiff(counts[i], limit) >= 4) {
      if (stride >= 4 || (stride >= 3 && sum == 0)) {

        int count = (sum + stride / 2) / stride;
        if (count < 1) count = 1;
        if (sum == 0) {

          count = 0;
        }
        for (k = 0; k < stride; ++k) {


          counts[i - k - 1] = count;
        }
      }
      stride = 0;
      sum = 0;
      if (i < length - 3) {


        limit = (counts[i] + counts[i + 1] +
                 counts[i + 2] + counts[i + 3] + 2) / 4;
      } else if (i < length) {
        limit = counts[i];
      } else {
        limit = 0;
      }
    }
    ++stride;
    if (i != length) {
      sum += counts[i];
    }
  }

  free(good_for_rle);
}






static double TryOptimizeHuffmanForRle(
    const ZopfliLZ77Store* lz77, size_t lstart, size_t lend,
    const size_t* ll_counts, const size_t* d_counts,
    unsigned* ll_lengths, unsigned* d_lengths) {
  size_t ll_counts2[288];
  size_t d_counts2[32];
  unsigned ll_lengths2[288];
  unsigned d_lengths2[32];
  double treesize;
  double datasize;
  double treesize2;
  double datasize2;

  treesize = CalculateTreeSize(ll_lengths, d_lengths);
  datasize = CalculateBlockSymbolSizeGivenCounts(ll_counts, d_counts,
      ll_lengths, d_lengths, lz77, lstart, lend);

  memcpy(ll_counts2, ll_counts, sizeof(ll_counts2));
  memcpy(d_counts2, d_counts, sizeof(d_counts2));
  OptimizeHuffmanForRle(288, ll_counts2);
  OptimizeHuffmanForRle(32, d_counts2);
  ZopfliCalculateBitLengths(ll_counts2, 288, 15, ll_lengths2);
  ZopfliCalculateBitLengths(d_counts2, 32, 15, d_lengths2);
  PatchDistanceCodesForBuggyDecoders(d_lengths2);

  treesize2 = CalculateTreeSize(ll_lengths2, d_lengths2);
  datasize2 = CalculateBlockSymbolSizeGivenCounts(ll_counts, d_counts,
      ll_lengths2, d_lengths2, lz77, lstart, lend);

  if (treesize2 + datasize2 < treesize + datasize) {
    memcpy(ll_lengths, ll_lengths2, sizeof(ll_lengths2));
    memcpy(d_lengths, d_lengths2, sizeof(d_lengths2));
    return treesize2 + datasize2;
  }
  return treesize + datasize;
}
# 569 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.c"
static double GetDynamicLengths(const ZopfliLZ77Store* lz77,
                                size_t lstart, size_t lend,
                                unsigned* ll_lengths, unsigned* d_lengths) {
  size_t ll_counts[288];
  size_t d_counts[32];

  ZopfliLZ77GetHistogram(lz77, lstart, lend, ll_counts, d_counts);
  ll_counts[256] = 1;
  ZopfliCalculateBitLengths(ll_counts, 288, 15, ll_lengths);
  ZopfliCalculateBitLengths(d_counts, 32, 15, d_lengths);
  PatchDistanceCodesForBuggyDecoders(d_lengths);
  return TryOptimizeHuffmanForRle(
      lz77, lstart, lend, ll_counts, d_counts, ll_lengths, d_lengths);
}

double ZopfliCalculateBlockSize(const ZopfliLZ77Store* lz77,
                                size_t lstart, size_t lend, int btype) {
  unsigned ll_lengths[288];
  unsigned d_lengths[32];

  double result = 3;

  if (btype == 0) {
    size_t length = ZopfliLZ77GetByteRange(lz77, lstart, lend);
    size_t rem = length % 65535;
    size_t blocks = length / 65535 + (rem ? 1 : 0);



    return blocks * 5 * 8 + length * 8;
  } if (btype == 1) {
    GetFixedTree(ll_lengths, d_lengths);
    result += CalculateBlockSymbolSize(
        ll_lengths, d_lengths, lz77, lstart, lend);
  } else {
    result += GetDynamicLengths(lz77, lstart, lend, ll_lengths, d_lengths);
  }

  return result;
}

double ZopfliCalculateBlockSizeAutoType(const ZopfliLZ77Store* lz77,
                                        size_t lstart, size_t lend) {
  double uncompressedcost = ZopfliCalculateBlockSize(lz77, lstart, lend, 0);


  double fixedcost = (lz77->size > 1000) ?
      uncompressedcost : ZopfliCalculateBlockSize(lz77, lstart, lend, 1);
  double dyncost = ZopfliCalculateBlockSize(lz77, lstart, lend, 2);
  return (uncompressedcost < fixedcost && uncompressedcost < dyncost)
      ? uncompressedcost
      : (fixedcost < dyncost ? fixedcost : dyncost);
}



static void AddNonCompressedBlock(const ZopfliOptions* options, int final,
                                  const unsigned char* in, size_t instart,
                                  size_t inend,
                                  unsigned char* bp,
                                  unsigned char** out, size_t* outsize) {
  size_t pos = instart;
  (void)options;
  for (;;) {
    size_t i;
    unsigned short blocksize = 65535;
    unsigned short nlen;
    int currentfinal;

    if (pos + blocksize > inend) blocksize = inend - pos;
    currentfinal = pos + blocksize >= inend;

    nlen = ~blocksize;

    AddBit(final && currentfinal, bp, out, outsize);

    AddBit(0, bp, out, outsize);
    AddBit(0, bp, out, outsize);


    *bp = 0;

    { if (!((*outsize) & ((*outsize) - 1))) { (*out) = (*outsize) == 0 ? malloc(sizeof(**out)) : realloc((*out), (*outsize) * 2 * sizeof(**out)); } (*out)[(*outsize)] = (blocksize % 256); (*outsize)++;};
    { if (!((*outsize) & ((*outsize) - 1))) { (*out) = (*outsize) == 0 ? malloc(sizeof(**out)) : realloc((*out), (*outsize) * 2 * sizeof(**out)); } (*out)[(*outsize)] = ((blocksize / 256) % 256); (*outsize)++;};
    { if (!((*outsize) & ((*outsize) - 1))) { (*out) = (*outsize) == 0 ? malloc(sizeof(**out)) : realloc((*out), (*outsize) * 2 * sizeof(**out)); } (*out)[(*outsize)] = (nlen % 256); (*outsize)++;};
    { if (!((*outsize) & ((*outsize) - 1))) { (*out) = (*outsize) == 0 ? malloc(sizeof(**out)) : realloc((*out), (*outsize) * 2 * sizeof(**out)); } (*out)[(*outsize)] = ((nlen / 256) % 256); (*outsize)++;};

    for (i = 0; i < blocksize; i++) {
      { if (!((*outsize) & ((*outsize) - 1))) { (*out) = (*outsize) == 0 ? malloc(sizeof(**out)) : realloc((*out), (*outsize) * 2 * sizeof(**out)); } (*out)[(*outsize)] = (in[pos + i]); (*outsize)++;};
    }

    if (currentfinal) break;
    pos += blocksize;
  }
}
# 682 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.c"
static void AddLZ77Block(const ZopfliOptions* options, int btype, int final,
                         const ZopfliLZ77Store* lz77,
                         size_t lstart, size_t lend,
                         size_t expected_data_size,
                         unsigned char* bp,
                         unsigned char** out, size_t* outsize) {
  unsigned ll_lengths[288];
  unsigned d_lengths[32];
  unsigned ll_symbols[288];
  unsigned d_symbols[32];
  size_t detect_block_size = *outsize;
  size_t compressed_size;
  size_t uncompressed_size = 0;
  size_t i;
  if (btype == 0) {
    size_t length = ZopfliLZ77GetByteRange(lz77, lstart, lend);
    size_t pos = lstart == lend ? 0 : lz77->pos[lstart];
    size_t end = pos + length;
    AddNonCompressedBlock(options, final,
                          lz77->data, pos, end, bp, out, outsize);
    return;
  }

  AddBit(final, bp, out, outsize);
  AddBit(btype & 1, bp, out, outsize);
  AddBit((btype & 2) >> 1, bp, out, outsize);

  if (btype == 1) {

    GetFixedTree(ll_lengths, d_lengths);
  } else {

    unsigned detect_tree_size;
    assert(btype == 2);

    GetDynamicLengths(lz77, lstart, lend, ll_lengths, d_lengths);

    detect_tree_size = *outsize;
    AddDynamicTree(ll_lengths, d_lengths, bp, out, outsize);
    if (options->verbose) {
      fprintf(stderr, "treesize: %d\n", (int)(*outsize - detect_tree_size));
    }
  }

  ZopfliLengthsToSymbols(ll_lengths, 288, 15, ll_symbols);
  ZopfliLengthsToSymbols(d_lengths, 32, 15, d_symbols);

  detect_block_size = *outsize;
  AddLZ77Data(lz77, lstart, lend, expected_data_size,
              ll_symbols, ll_lengths, d_symbols, d_lengths,
              bp, out, outsize);

  AddHuffmanBits(ll_symbols[256], ll_lengths[256], bp, out, outsize);

  for (i = lstart; i < lend; i++) {
    uncompressed_size += lz77->dists[i] == 0 ? 1 : lz77->litlens[i];
  }
  compressed_size = *outsize - detect_block_size;
  if (options->verbose) {
    fprintf(stderr, "compressed block size: %d (%dk) (unc: %d)\n",
           (int)compressed_size, (int)(compressed_size / 1024),
           (int)(uncompressed_size));
  }
}

static void AddLZ77BlockAutoType(const ZopfliOptions* options, int final,
                                 const ZopfliLZ77Store* lz77,
                                 size_t lstart, size_t lend,
                                 size_t expected_data_size,
                                 unsigned char* bp,
                                 unsigned char** out, size_t* outsize) {
  double uncompressedcost = ZopfliCalculateBlockSize(lz77, lstart, lend, 0);
  double fixedcost = ZopfliCalculateBlockSize(lz77, lstart, lend, 1);
  double dyncost = ZopfliCalculateBlockSize(lz77, lstart, lend, 2);




  int expensivefixed = (lz77->size < 1000) || fixedcost <= dyncost * 1.1;

  ZopfliLZ77Store fixedstore;
  if (lstart == lend) {

    AddBits(final, 1, bp, out, outsize);
    AddBits(1, 2, bp, out, outsize);
    AddBits(0, 7, bp, out, outsize);
    return;
  }
  ZopfliInitLZ77Store(lz77->data, &fixedstore);
  if (expensivefixed) {

    size_t instart = lz77->pos[lstart];
    size_t inend = instart + ZopfliLZ77GetByteRange(lz77, lstart, lend);

    ZopfliBlockState s;
    ZopfliInitBlockState(options, instart, inend, 1, &s);
    ZopfliLZ77OptimalFixed(&s, lz77->data, instart, inend, &fixedstore);
    fixedcost = ZopfliCalculateBlockSize(&fixedstore, 0, fixedstore.size, 1);
    ZopfliCleanBlockState(&s);
  }

  if (uncompressedcost < fixedcost && uncompressedcost < dyncost) {
    AddLZ77Block(options, 0, final, lz77, lstart, lend,
                 expected_data_size, bp, out, outsize);
  } else if (fixedcost < dyncost) {
    if (expensivefixed) {
      AddLZ77Block(options, 1, final, &fixedstore, 0, fixedstore.size,
                   expected_data_size, bp, out, outsize);
    } else {
      AddLZ77Block(options, 1, final, lz77, lstart, lend,
                   expected_data_size, bp, out, outsize);
    }
  } else {
    AddLZ77Block(options, 2, final, lz77, lstart, lend,
                 expected_data_size, bp, out, outsize);
  }

  ZopfliCleanLZ77Store(&fixedstore);
}
# 811 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.c"
void ZopfliDeflatePart(const ZopfliOptions* options, int btype, int final,
                       const unsigned char* in, size_t instart, size_t inend,
                       unsigned char* bp, unsigned char** out,
                       size_t* outsize) {
  size_t i;

  size_t* splitpoints_uncompressed = 0;
  size_t npoints = 0;
  size_t* splitpoints = 0;
  double totalcost = 0;
  ZopfliLZ77Store lz77;




  if (btype == 0) {
    AddNonCompressedBlock(options, final, in, instart, inend, bp, out, outsize);
    return;
  } else if (btype == 1) {
    ZopfliLZ77Store store;
    ZopfliBlockState s;
    ZopfliInitLZ77Store(in, &store);
    ZopfliInitBlockState(options, instart, inend, 1, &s);

    ZopfliLZ77OptimalFixed(&s, in, instart, inend, &store);
    AddLZ77Block(options, btype, final, &store, 0, store.size, 0,
                 bp, out, outsize);

    ZopfliCleanBlockState(&s);
    ZopfliCleanLZ77Store(&store);
    return;
  }


  if (options->blocksplitting) {
    ZopfliBlockSplit(options, in, instart, inend,
                     options->blocksplittingmax,
                     &splitpoints_uncompressed, &npoints);
    splitpoints = (size_t*)malloc(sizeof(*splitpoints) * npoints);
  }

  ZopfliInitLZ77Store(in, &lz77);

  for (i = 0; i <= npoints; i++) {
    size_t start = i == 0 ? instart : splitpoints_uncompressed[i - 1];
    size_t end = i == npoints ? inend : splitpoints_uncompressed[i];
    ZopfliBlockState s;
    ZopfliLZ77Store store;
    ZopfliInitLZ77Store(in, &store);
    ZopfliInitBlockState(options, start, end, 1, &s);
    ZopfliLZ77Optimal(&s, in, start, end, options->numiterations, &store);
    totalcost += ZopfliCalculateBlockSizeAutoType(&store, 0, store.size);

    ZopfliAppendLZ77Store(&store, &lz77);
    if (i < npoints) splitpoints[i] = lz77.size;

    ZopfliCleanBlockState(&s);
    ZopfliCleanLZ77Store(&store);
  }


  if (options->blocksplitting && npoints > 1) {
    size_t* splitpoints2 = 0;
    size_t npoints2 = 0;
    double totalcost2 = 0;

    ZopfliBlockSplitLZ77(options, &lz77,
                         options->blocksplittingmax, &splitpoints2, &npoints2);

    for (i = 0; i <= npoints2; i++) {
      size_t start = i == 0 ? 0 : splitpoints2[i - 1];
      size_t end = i == npoints2 ? lz77.size : splitpoints2[i];
      totalcost2 += ZopfliCalculateBlockSizeAutoType(&lz77, start, end);
    }

    if (totalcost2 < totalcost) {
      free(splitpoints);
      splitpoints = splitpoints2;
      npoints = npoints2;
    } else {
      free(splitpoints2);
    }
  }

  for (i = 0; i <= npoints; i++) {
    size_t start = i == 0 ? 0 : splitpoints[i - 1];
    size_t end = i == npoints ? lz77.size : splitpoints[i];
    AddLZ77BlockAutoType(options, i == npoints && final,
                         &lz77, start, end, 0,
                         bp, out, outsize);
  }

  ZopfliCleanLZ77Store(&lz77);
  free(splitpoints);
  free(splitpoints_uncompressed);
}

void ZopfliDeflate(const ZopfliOptions* options, int btype, int final,
                   const unsigned char* in, size_t insize,
                   unsigned char* bp, unsigned char** out, size_t* outsize) {
 size_t offset = *outsize;



  size_t i = 0;
  do {
    int masterfinal = (i + 1000000 >= insize);
    int final2 = final && masterfinal;
    size_t size = masterfinal ? insize - i : 1000000;
    ZopfliDeflatePart(options, btype, final2,
                      in, i, i + size, bp, out, outsize);
    i += size;
  } while (i < insize);

  if (options->verbose) {
    fprintf(stderr,
            "Original Size: %lu, Deflate: %lu, Compression: %f%% Removed\n",
            (unsigned long)insize, (unsigned long)(*outsize - offset),
            100.0 * (double)(insize - (*outsize - offset)) / (double)insize);
  }
}
