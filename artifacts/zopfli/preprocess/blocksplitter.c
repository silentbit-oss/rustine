# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.c"
# 20 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.c"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.h" 1
# 31 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.h"
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
# 32 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
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
# 34 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.h" 2
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
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 1
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.h" 1
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
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.c" 2
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
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.c" 2
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
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.c" 2







typedef double FindMinimumFun(size_t i, void* context);






static size_t FindMinimum(FindMinimumFun f, void* context,
                          size_t start, size_t end, double* smallest) {
  if (end - start < 1024) {
    double best = 1e30;
    size_t result = start;
    size_t i;
    for (i = start; i < end; i++) {
      double v = f(i, context);
      if (v < best) {
        best = v;
        result = i;
      }
    }
    *smallest = best;
    return result;
  } else {


    size_t i;
    size_t p[9];
    double vp[9];
    size_t besti;
    double best;
    double lastbest = 1e30;
    size_t pos = start;

    for (;;) {
      if (end - start <= 9) break;

      for (i = 0; i < 9; i++) {
        p[i] = start + (i + 1) * ((end - start) / (9 + 1));
        vp[i] = f(p[i], context);
      }
      besti = 0;
      best = vp[0];
      for (i = 1; i < 9; i++) {
        if (vp[i] < best) {
          best = vp[i];
          besti = i;
        }
      }
      if (best > lastbest) break;

      start = besti == 0 ? start : p[besti - 1];
      end = besti == 9 - 1 ? end : p[besti + 1];

      pos = p[besti];
      lastbest = best;
    }
    *smallest = lastbest;
    return pos;

  }
}
# 108 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.c"
static double EstimateCost(const ZopfliLZ77Store* lz77,
                           size_t lstart, size_t lend) {
  return ZopfliCalculateBlockSizeAutoType(lz77, lstart, lend);
}

typedef struct SplitCostContext {
  const ZopfliLZ77Store* lz77;
  size_t start;
  size_t end;
} SplitCostContext;







static double SplitCost(size_t i, void* context) {
  SplitCostContext* c = (SplitCostContext*)context;
  return EstimateCost(c->lz77, c->start, i) + EstimateCost(c->lz77, i, c->end);
}

static void AddSorted(size_t value, size_t** out, size_t* outsize) {
  size_t i;
  { if (!((*outsize) & ((*outsize) - 1))) { (*out) = (*outsize) == 0 ? malloc(sizeof(**out)) : realloc((*out), (*outsize) * 2 * sizeof(**out)); } (*out)[(*outsize)] = (value); (*outsize)++;};
  for (i = 0; i + 1 < *outsize; i++) {
    if ((*out)[i] > value) {
      size_t j;
      for (j = *outsize - 1; j > i; j--) {
        (*out)[j] = (*out)[j - 1];
      }
      (*out)[i] = value;
      break;
    }
  }
}




static void PrintBlockSplitPoints(const ZopfliLZ77Store* lz77,
                                  const size_t* lz77splitpoints,
                                  size_t nlz77points) {
  size_t* splitpoints = 0;
  size_t npoints = 0;
  size_t i;


  size_t pos = 0;
  if (nlz77points > 0) {
    for (i = 0; i < lz77->size; i++) {
      size_t length = lz77->dists[i] == 0 ? 1 : lz77->litlens[i];
      if (lz77splitpoints[npoints] == i) {
        { if (!((*&npoints) & ((*&npoints) - 1))) { (*&splitpoints) = (*&npoints) == 0 ? malloc(sizeof(**&splitpoints)) : realloc((*&splitpoints), (*&npoints) * 2 * sizeof(**&splitpoints)); } (*&splitpoints)[(*&npoints)] = (pos); (*&npoints)++;};
        if (npoints == nlz77points) break;
      }
      pos += length;
    }
  }
  assert(npoints == nlz77points);

  fprintf(stderr, "block split points: ");
  for (i = 0; i < npoints; i++) {
    fprintf(stderr, "%d ", (int)splitpoints[i]);
  }
  fprintf(stderr, "(hex:");
  for (i = 0; i < npoints; i++) {
    fprintf(stderr, " %x", (int)splitpoints[i]);
  }
  fprintf(stderr, ")\n");

  free(splitpoints);
}
# 195 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.c"
static int FindLargestSplittableBlock(
    size_t lz77size, const unsigned char* done,
    const size_t* splitpoints, size_t npoints,
    size_t* lstart, size_t* lend) {
  size_t longest = 0;
  int found = 0;
  size_t i;
  for (i = 0; i <= npoints; i++) {
    size_t start = i == 0 ? 0 : splitpoints[i - 1];
    size_t end = i == npoints ? lz77size - 1 : splitpoints[i];
    if (!done[start] && end - start > longest) {
      *lstart = start;
      *lend = end;
      found = 1;
      longest = end - start;
    }
  }
  return found;
}

void ZopfliBlockSplitLZ77(const ZopfliOptions* options,
                          const ZopfliLZ77Store* lz77, size_t maxblocks,
                          size_t** splitpoints, size_t* npoints) {
  size_t lstart, lend;
  size_t i;
  size_t llpos = 0;
  size_t numblocks = 1;
  unsigned char* done;
  double splitcost, origcost;

  if (lz77->size < 10) return;

  done = (unsigned char*)malloc(lz77->size);
  if (!done) exit(-1);
  for (i = 0; i < lz77->size; i++) done[i] = 0;

  lstart = 0;
  lend = lz77->size;
  for (;;) {
    SplitCostContext c;

    if (maxblocks > 0 && numblocks >= maxblocks) {
      break;
    }

    c.lz77 = lz77;
    c.start = lstart;
    c.end = lend;
    assert(lstart < lend);
    llpos = FindMinimum(SplitCost, &c, lstart + 1, lend, &splitcost);

    assert(llpos > lstart);
    assert(llpos < lend);

    origcost = EstimateCost(lz77, lstart, lend);

    if (splitcost > origcost || llpos == lstart + 1 || llpos == lend) {
      done[lstart] = 1;
    } else {
      AddSorted(llpos, splitpoints, npoints);
      numblocks++;
    }

    if (!FindLargestSplittableBlock(
        lz77->size, done, *splitpoints, *npoints, &lstart, &lend)) {
      break;
    }

    if (lend - lstart < 10) {
      break;
    }
  }

  if (options->verbose) {
    PrintBlockSplitPoints(lz77, *splitpoints, *npoints);
  }

  free(done);
}

void ZopfliBlockSplit(const ZopfliOptions* options,
                      const unsigned char* in, size_t instart, size_t inend,
                      size_t maxblocks, size_t** splitpoints, size_t* npoints) {
  size_t pos = 0;
  size_t i;
  ZopfliBlockState s;
  size_t* lz77splitpoints = 0;
  size_t nlz77points = 0;
  ZopfliLZ77Store store;
  ZopfliHash hash;
  ZopfliHash* h = &hash;

  ZopfliInitLZ77Store(in, &store);
  ZopfliInitBlockState(options, instart, inend, 0, &s);
  ZopfliAllocHash(32768, h);

  *npoints = 0;
  *splitpoints = 0;



  ZopfliLZ77Greedy(&s, in, instart, inend, &store, h);

  ZopfliBlockSplitLZ77(options,
                       &store, maxblocks,
                       &lz77splitpoints, &nlz77points);


  pos = instart;
  if (nlz77points > 0) {
    for (i = 0; i < store.size; i++) {
      size_t length = store.dists[i] == 0 ? 1 : store.litlens[i];
      if (lz77splitpoints[*npoints] == i) {
        { if (!((*npoints) & ((*npoints) - 1))) { (*splitpoints) = (*npoints) == 0 ? malloc(sizeof(**splitpoints)) : realloc((*splitpoints), (*npoints) * 2 * sizeof(**splitpoints)); } (*splitpoints)[(*npoints)] = (pos); (*npoints)++;};
        if (*npoints == nlz77points) break;
      }
      pos += length;
    }
  }
  assert(*npoints == nlz77points);

  free(lz77splitpoints);
  ZopfliCleanBlockState(&s);
  ZopfliCleanLZ77Store(&store);
  ZopfliCleanHash(h);
}

void ZopfliBlockSplitSimple(const unsigned char* in,
                            size_t instart, size_t inend,
                            size_t blocksize,
                            size_t** splitpoints, size_t* npoints) {
  size_t i = instart;
  while (i < inend) {
    { if (!((*npoints) & ((*npoints) - 1))) { (*splitpoints) = (*npoints) == 0 ? malloc(sizeof(**splitpoints)) : realloc((*splitpoints), (*npoints) * 2 * sizeof(**splitpoints)); } (*splitpoints)[(*npoints)] = (i); (*npoints)++;};
    i += blocksize;
  }
  (void)in;
}
# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.c"
# 20 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.c"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.h" 1
# 31 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.h"
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
# 32 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/lz77.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
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
# 34 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.h" 2
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
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 1
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/deflate.h" 1
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
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.c" 2
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
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.c" 2
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
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.c" 2







typedef double FindMinimumFun(size_t i, void* context);






static size_t FindMinimum(FindMinimumFun f, void* context,
                          size_t start, size_t end, double* smallest) {
  if (end - start < 1024) {
    double best = 1e30;
    size_t result = start;
    size_t i;
    for (i = start; i < end; i++) {
      double v = f(i, context);
      if (v < best) {
        best = v;
        result = i;
      }
    }
    *smallest = best;
    return result;
  } else {


    size_t i;
    size_t p[9];
    double vp[9];
    size_t besti;
    double best;
    double lastbest = 1e30;
    size_t pos = start;

    for (;;) {
      if (end - start <= 9) break;

      for (i = 0; i < 9; i++) {
        p[i] = start + (i + 1) * ((end - start) / (9 + 1));
        vp[i] = f(p[i], context);
      }
      besti = 0;
      best = vp[0];
      for (i = 1; i < 9; i++) {
        if (vp[i] < best) {
          best = vp[i];
          besti = i;
        }
      }
      if (best > lastbest) break;

      start = besti == 0 ? start : p[besti - 1];
      end = besti == 9 - 1 ? end : p[besti + 1];

      pos = p[besti];
      lastbest = best;
    }
    *smallest = lastbest;
    return pos;

  }
}
# 108 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.c"
static double EstimateCost(const ZopfliLZ77Store* lz77,
                           size_t lstart, size_t lend) {
  return ZopfliCalculateBlockSizeAutoType(lz77, lstart, lend);
}

typedef struct SplitCostContext {
  const ZopfliLZ77Store* lz77;
  size_t start;
  size_t end;
} SplitCostContext;







static double SplitCost(size_t i, void* context) {
  SplitCostContext* c = (SplitCostContext*)context;
  return EstimateCost(c->lz77, c->start, i) + EstimateCost(c->lz77, i, c->end);
}

static void AddSorted(size_t value, size_t** out, size_t* outsize) {
  size_t i;
  { if (!((*outsize) & ((*outsize) - 1))) { (*out) = (*outsize) == 0 ? malloc(sizeof(**out)) : realloc((*out), (*outsize) * 2 * sizeof(**out)); } (*out)[(*outsize)] = (value); (*outsize)++;};
  for (i = 0; i + 1 < *outsize; i++) {
    if ((*out)[i] > value) {
      size_t j;
      for (j = *outsize - 1; j > i; j--) {
        (*out)[j] = (*out)[j - 1];
      }
      (*out)[i] = value;
      break;
    }
  }
}




static void PrintBlockSplitPoints(const ZopfliLZ77Store* lz77,
                                  const size_t* lz77splitpoints,
                                  size_t nlz77points) {
  size_t* splitpoints = 0;
  size_t npoints = 0;
  size_t i;


  size_t pos = 0;
  if (nlz77points > 0) {
    for (i = 0; i < lz77->size; i++) {
      size_t length = lz77->dists[i] == 0 ? 1 : lz77->litlens[i];
      if (lz77splitpoints[npoints] == i) {
        { if (!((*&npoints) & ((*&npoints) - 1))) { (*&splitpoints) = (*&npoints) == 0 ? malloc(sizeof(**&splitpoints)) : realloc((*&splitpoints), (*&npoints) * 2 * sizeof(**&splitpoints)); } (*&splitpoints)[(*&npoints)] = (pos); (*&npoints)++;};
        if (npoints == nlz77points) break;
      }
      pos += length;
    }
  }
  assert(npoints == nlz77points);

  fprintf(stderr, "block split points: ");
  for (i = 0; i < npoints; i++) {
    fprintf(stderr, "%d ", (int)splitpoints[i]);
  }
  fprintf(stderr, "(hex:");
  for (i = 0; i < npoints; i++) {
    fprintf(stderr, " %x", (int)splitpoints[i]);
  }
  fprintf(stderr, ")\n");

  free(splitpoints);
}
# 195 "/home/enumclass/Documents/C2RustTranslation/bkp/zopfli/src/zopfli/blocksplitter.c"
static int FindLargestSplittableBlock(
    size_t lz77size, const unsigned char* done,
    const size_t* splitpoints, size_t npoints,
    size_t* lstart, size_t* lend) {
  size_t longest = 0;
  int found = 0;
  size_t i;
  for (i = 0; i <= npoints; i++) {
    size_t start = i == 0 ? 0 : splitpoints[i - 1];
    size_t end = i == npoints ? lz77size - 1 : splitpoints[i];
    if (!done[start] && end - start > longest) {
      *lstart = start;
      *lend = end;
      found = 1;
      longest = end - start;
    }
  }
  return found;
}

void ZopfliBlockSplitLZ77(const ZopfliOptions* options,
                          const ZopfliLZ77Store* lz77, size_t maxblocks,
                          size_t** splitpoints, size_t* npoints) {
  size_t lstart, lend;
  size_t i;
  size_t llpos = 0;
  size_t numblocks = 1;
  unsigned char* done;
  double splitcost, origcost;

  if (lz77->size < 10) return;

  done = (unsigned char*)malloc(lz77->size);
  if (!done) exit(-1);
  for (i = 0; i < lz77->size; i++) done[i] = 0;

  lstart = 0;
  lend = lz77->size;
  for (;;) {
    SplitCostContext c;

    if (maxblocks > 0 && numblocks >= maxblocks) {
      break;
    }

    c.lz77 = lz77;
    c.start = lstart;
    c.end = lend;
    assert(lstart < lend);
    llpos = FindMinimum(SplitCost, &c, lstart + 1, lend, &splitcost);

    assert(llpos > lstart);
    assert(llpos < lend);

    origcost = EstimateCost(lz77, lstart, lend);

    if (splitcost > origcost || llpos == lstart + 1 || llpos == lend) {
      done[lstart] = 1;
    } else {
      AddSorted(llpos, splitpoints, npoints);
      numblocks++;
    }

    if (!FindLargestSplittableBlock(
        lz77->size, done, *splitpoints, *npoints, &lstart, &lend)) {
      break;
    }

    if (lend - lstart < 10) {
      break;
    }
  }

  if (options->verbose) {
    PrintBlockSplitPoints(lz77, *splitpoints, *npoints);
  }

  free(done);
}

void ZopfliBlockSplit(const ZopfliOptions* options,
                      const unsigned char* in, size_t instart, size_t inend,
                      size_t maxblocks, size_t** splitpoints, size_t* npoints) {
  size_t pos = 0;
  size_t i;
  ZopfliBlockState s;
  size_t* lz77splitpoints = 0;
  size_t nlz77points = 0;
  ZopfliLZ77Store store;
  ZopfliHash hash;
  ZopfliHash* h = &hash;

  ZopfliInitLZ77Store(in, &store);
  ZopfliInitBlockState(options, instart, inend, 0, &s);
  ZopfliAllocHash(32768, h);

  *npoints = 0;
  *splitpoints = 0;



  ZopfliLZ77Greedy(&s, in, instart, inend, &store, h);

  ZopfliBlockSplitLZ77(options,
                       &store, maxblocks,
                       &lz77splitpoints, &nlz77points);


  pos = instart;
  if (nlz77points > 0) {
    for (i = 0; i < store.size; i++) {
      size_t length = store.dists[i] == 0 ? 1 : store.litlens[i];
      if (lz77splitpoints[*npoints] == i) {
        { if (!((*npoints) & ((*npoints) - 1))) { (*splitpoints) = (*npoints) == 0 ? malloc(sizeof(**splitpoints)) : realloc((*splitpoints), (*npoints) * 2 * sizeof(**splitpoints)); } (*splitpoints)[(*npoints)] = (pos); (*npoints)++;};
        if (*npoints == nlz77points) break;
      }
      pos += length;
    }
  }
  assert(*npoints == nlz77points);

  free(lz77splitpoints);
  ZopfliCleanBlockState(&s);
  ZopfliCleanLZ77Store(&store);
  ZopfliCleanHash(h);
}

void ZopfliBlockSplitSimple(const unsigned char* in,
                            size_t instart, size_t inend,
                            size_t blocksize,
                            size_t** splitpoints, size_t* npoints) {
  size_t i = instart;
  while (i < inend) {
    { if (!((*npoints) & ((*npoints) - 1))) { (*splitpoints) = (*npoints) == 0 ? malloc(sizeof(**splitpoints)) : realloc((*splitpoints), (*npoints) * 2 * sizeof(**splitpoints)); } (*splitpoints)[(*npoints)] = (i); (*npoints)++;};
    i += blocksize;
  }
  (void)in;
}
