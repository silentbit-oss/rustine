# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/fast_log.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/fast_log.c"






# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./fast_log.h" 1
# 12 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./fast_log.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/math.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/math.h" 2
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
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/math.h" 2
# 13 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./fast_log.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./../common/platform.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./../common/platform.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
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
# 15 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./fast_log.h" 2






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
# 8 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/fast_log.c" 2






const double kBrotliLog2Table[256] = {
  0.0000000000000000f, 0.0000000000000000f, 1.0000000000000000f,
  1.5849625007211563f, 2.0000000000000000f, 2.3219280948873622f,
  2.5849625007211561f, 2.8073549220576042f, 3.0000000000000000f,
  3.1699250014423126f, 3.3219280948873626f, 3.4594316186372978f,
  3.5849625007211565f, 3.7004397181410922f, 3.8073549220576037f,
  3.9068905956085187f, 4.0000000000000000f, 4.0874628412503400f,
  4.1699250014423122f, 4.2479275134435852f, 4.3219280948873626f,
  4.3923174227787607f, 4.4594316186372973f, 4.5235619560570131f,
  4.5849625007211570f, 4.6438561897747244f, 4.7004397181410926f,
  4.7548875021634691f, 4.8073549220576037f, 4.8579809951275728f,
  4.9068905956085187f, 4.9541963103868758f, 5.0000000000000000f,
  5.0443941193584534f, 5.0874628412503400f, 5.1292830169449664f,
  5.1699250014423122f, 5.2094533656289501f, 5.2479275134435852f,
  5.2854022188622487f, 5.3219280948873626f, 5.3575520046180838f,
  5.3923174227787607f, 5.4262647547020979f, 5.4594316186372973f,
  5.4918530963296748f, 5.5235619560570131f, 5.5545888516776376f,
  5.5849625007211570f, 5.6147098441152083f, 5.6438561897747244f,
  5.6724253419714961f, 5.7004397181410926f, 5.7279204545631996f,
  5.7548875021634691f, 5.7813597135246599f, 5.8073549220576046f,
  5.8328900141647422f, 5.8579809951275719f, 5.8826430493618416f,
  5.9068905956085187f, 5.9307373375628867f, 5.9541963103868758f,
  5.9772799234999168f, 6.0000000000000000f, 6.0223678130284544f,
  6.0443941193584534f, 6.0660891904577721f, 6.0874628412503400f,
  6.1085244567781700f, 6.1292830169449672f, 6.1497471195046822f,
  6.1699250014423122f, 6.1898245588800176f, 6.2094533656289510f,
  6.2288186904958804f, 6.2479275134435861f, 6.2667865406949019f,
  6.2854022188622487f, 6.3037807481771031f, 6.3219280948873617f,
  6.3398500028846252f, 6.3575520046180847f, 6.3750394313469254f,
  6.3923174227787598f, 6.4093909361377026f, 6.4262647547020979f,
  6.4429434958487288f, 6.4594316186372982f, 6.4757334309663976f,
  6.4918530963296748f, 6.5077946401986964f, 6.5235619560570131f,
  6.5391588111080319f, 6.5545888516776376f, 6.5698556083309478f,
  6.5849625007211561f, 6.5999128421871278f, 6.6147098441152092f,
  6.6293566200796095f, 6.6438561897747253f, 6.6582114827517955f,
  6.6724253419714952f, 6.6865005271832185f, 6.7004397181410917f,
  6.7142455176661224f, 6.7279204545631988f, 6.7414669864011465f,
  6.7548875021634691f, 6.7681843247769260f, 6.7813597135246599f,
  6.7944158663501062f, 6.8073549220576037f, 6.8201789624151887f,
  6.8328900141647422f, 6.8454900509443757f, 6.8579809951275719f,
  6.8703647195834048f, 6.8826430493618416f, 6.8948177633079437f,
  6.9068905956085187f, 6.9188632372745955f, 6.9307373375628867f,
  6.9425145053392399f, 6.9541963103868758f, 6.9657842846620879f,
  6.9772799234999168f, 6.9886846867721664f, 7.0000000000000000f,
  7.0112272554232540f, 7.0223678130284544f, 7.0334230015374501f,
  7.0443941193584534f, 7.0552824355011898f, 7.0660891904577721f,
  7.0768155970508317f, 7.0874628412503400f, 7.0980320829605272f,
  7.1085244567781700f, 7.1189410727235076f, 7.1292830169449664f,
  7.1395513523987937f, 7.1497471195046822f, 7.1598713367783891f,
  7.1699250014423130f, 7.1799090900149345f, 7.1898245588800176f,
  7.1996723448363644f, 7.2094533656289492f, 7.2191685204621621f,
  7.2288186904958804f, 7.2384047393250794f, 7.2479275134435861f,
  7.2573878426926521f, 7.2667865406949019f, 7.2761244052742384f,
  7.2854022188622487f, 7.2946207488916270f, 7.3037807481771031f,
  7.3128829552843557f, 7.3219280948873617f, 7.3309168781146177f,
  7.3398500028846243f, 7.3487281542310781f, 7.3575520046180847f,
  7.3663222142458151f, 7.3750394313469254f, 7.3837042924740528f,
  7.3923174227787607f, 7.4008794362821844f, 7.4093909361377026f,
  7.4178525148858991f, 7.4262647547020979f, 7.4346282276367255f,
  7.4429434958487288f, 7.4512111118323299f, 7.4594316186372973f,
  7.4676055500829976f, 7.4757334309663976f, 7.4838157772642564f,
  7.4918530963296748f, 7.4998458870832057f, 7.5077946401986964f,
  7.5156998382840436f, 7.5235619560570131f, 7.5313814605163119f,
  7.5391588111080319f, 7.5468944598876373f, 7.5545888516776376f,
  7.5622424242210728f, 7.5698556083309478f, 7.5774288280357487f,
  7.5849625007211561f, 7.5924570372680806f, 7.5999128421871278f,
  7.6073303137496113f, 7.6147098441152075f, 7.6220518194563764f,
  7.6293566200796095f, 7.6366246205436488f, 7.6438561897747244f,
  7.6510516911789290f, 7.6582114827517955f, 7.6653359171851765f,
  7.6724253419714952f, 7.6794800995054464f, 7.6865005271832185f,
  7.6934869574993252f, 7.7004397181410926f, 7.7073591320808825f,
  7.7142455176661224f, 7.7210991887071856f, 7.7279204545631996f,
  7.7347096202258392f, 7.7414669864011465f, 7.7481928495894596f,
  7.7548875021634691f, 7.7615512324444795f, 7.7681843247769260f,
  7.7747870596011737f, 7.7813597135246608f, 7.7879025593914317f,
  7.7944158663501062f, 7.8008998999203047f, 7.8073549220576037f,
  7.8137811912170374f, 7.8201789624151887f, 7.8265484872909159f,
  7.8328900141647422f, 7.8392037880969445f, 7.8454900509443757f,
  7.8517490414160571f, 7.8579809951275719f, 7.8641861446542798f,
  7.8703647195834048f, 7.8765169465650002f, 7.8826430493618425f,
  7.8887432488982601f, 7.8948177633079446f, 7.9008668079807496f,
  7.9068905956085187f, 7.9128893362299619f, 7.9188632372745955f,
  7.9248125036057813f, 7.9307373375628867f, 7.9366379390025719f,
  7.9425145053392399f, 7.9483672315846778f, 7.9541963103868758f,
  7.9600019320680806f, 7.9657842846620870f, 7.9715435539507720f,
  7.9772799234999168f, 7.9829935746943104f, 7.9886846867721664f,
  7.9943534368588578f
};
# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/fast_log.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/fast_log.c"






# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./fast_log.h" 1
# 12 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./fast_log.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/math.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/math.h" 2
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
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/math.h" 2
# 13 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./fast_log.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./../common/platform.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./../common/platform.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
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
# 15 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/./fast_log.h" 2






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
# 8 "/home/enumclass/Documents/C2RustTranslation/bkp/brotli-1.0.9/c/enc/fast_log.c" 2






const double kBrotliLog2Table[256] = {
  0.0000000000000000f, 0.0000000000000000f, 1.0000000000000000f,
  1.5849625007211563f, 2.0000000000000000f, 2.3219280948873622f,
  2.5849625007211561f, 2.8073549220576042f, 3.0000000000000000f,
  3.1699250014423126f, 3.3219280948873626f, 3.4594316186372978f,
  3.5849625007211565f, 3.7004397181410922f, 3.8073549220576037f,
  3.9068905956085187f, 4.0000000000000000f, 4.0874628412503400f,
  4.1699250014423122f, 4.2479275134435852f, 4.3219280948873626f,
  4.3923174227787607f, 4.4594316186372973f, 4.5235619560570131f,
  4.5849625007211570f, 4.6438561897747244f, 4.7004397181410926f,
  4.7548875021634691f, 4.8073549220576037f, 4.8579809951275728f,
  4.9068905956085187f, 4.9541963103868758f, 5.0000000000000000f,
  5.0443941193584534f, 5.0874628412503400f, 5.1292830169449664f,
  5.1699250014423122f, 5.2094533656289501f, 5.2479275134435852f,
  5.2854022188622487f, 5.3219280948873626f, 5.3575520046180838f,
  5.3923174227787607f, 5.4262647547020979f, 5.4594316186372973f,
  5.4918530963296748f, 5.5235619560570131f, 5.5545888516776376f,
  5.5849625007211570f, 5.6147098441152083f, 5.6438561897747244f,
  5.6724253419714961f, 5.7004397181410926f, 5.7279204545631996f,
  5.7548875021634691f, 5.7813597135246599f, 5.8073549220576046f,
  5.8328900141647422f, 5.8579809951275719f, 5.8826430493618416f,
  5.9068905956085187f, 5.9307373375628867f, 5.9541963103868758f,
  5.9772799234999168f, 6.0000000000000000f, 6.0223678130284544f,
  6.0443941193584534f, 6.0660891904577721f, 6.0874628412503400f,
  6.1085244567781700f, 6.1292830169449672f, 6.1497471195046822f,
  6.1699250014423122f, 6.1898245588800176f, 6.2094533656289510f,
  6.2288186904958804f, 6.2479275134435861f, 6.2667865406949019f,
  6.2854022188622487f, 6.3037807481771031f, 6.3219280948873617f,
  6.3398500028846252f, 6.3575520046180847f, 6.3750394313469254f,
  6.3923174227787598f, 6.4093909361377026f, 6.4262647547020979f,
  6.4429434958487288f, 6.4594316186372982f, 6.4757334309663976f,
  6.4918530963296748f, 6.5077946401986964f, 6.5235619560570131f,
  6.5391588111080319f, 6.5545888516776376f, 6.5698556083309478f,
  6.5849625007211561f, 6.5999128421871278f, 6.6147098441152092f,
  6.6293566200796095f, 6.6438561897747253f, 6.6582114827517955f,
  6.6724253419714952f, 6.6865005271832185f, 6.7004397181410917f,
  6.7142455176661224f, 6.7279204545631988f, 6.7414669864011465f,
  6.7548875021634691f, 6.7681843247769260f, 6.7813597135246599f,
  6.7944158663501062f, 6.8073549220576037f, 6.8201789624151887f,
  6.8328900141647422f, 6.8454900509443757f, 6.8579809951275719f,
  6.8703647195834048f, 6.8826430493618416f, 6.8948177633079437f,
  6.9068905956085187f, 6.9188632372745955f, 6.9307373375628867f,
  6.9425145053392399f, 6.9541963103868758f, 6.9657842846620879f,
  6.9772799234999168f, 6.9886846867721664f, 7.0000000000000000f,
  7.0112272554232540f, 7.0223678130284544f, 7.0334230015374501f,
  7.0443941193584534f, 7.0552824355011898f, 7.0660891904577721f,
  7.0768155970508317f, 7.0874628412503400f, 7.0980320829605272f,
  7.1085244567781700f, 7.1189410727235076f, 7.1292830169449664f,
  7.1395513523987937f, 7.1497471195046822f, 7.1598713367783891f,
  7.1699250014423130f, 7.1799090900149345f, 7.1898245588800176f,
  7.1996723448363644f, 7.2094533656289492f, 7.2191685204621621f,
  7.2288186904958804f, 7.2384047393250794f, 7.2479275134435861f,
  7.2573878426926521f, 7.2667865406949019f, 7.2761244052742384f,
  7.2854022188622487f, 7.2946207488916270f, 7.3037807481771031f,
  7.3128829552843557f, 7.3219280948873617f, 7.3309168781146177f,
  7.3398500028846243f, 7.3487281542310781f, 7.3575520046180847f,
  7.3663222142458151f, 7.3750394313469254f, 7.3837042924740528f,
  7.3923174227787607f, 7.4008794362821844f, 7.4093909361377026f,
  7.4178525148858991f, 7.4262647547020979f, 7.4346282276367255f,
  7.4429434958487288f, 7.4512111118323299f, 7.4594316186372973f,
  7.4676055500829976f, 7.4757334309663976f, 7.4838157772642564f,
  7.4918530963296748f, 7.4998458870832057f, 7.5077946401986964f,
  7.5156998382840436f, 7.5235619560570131f, 7.5313814605163119f,
  7.5391588111080319f, 7.5468944598876373f, 7.5545888516776376f,
  7.5622424242210728f, 7.5698556083309478f, 7.5774288280357487f,
  7.5849625007211561f, 7.5924570372680806f, 7.5999128421871278f,
  7.6073303137496113f, 7.6147098441152075f, 7.6220518194563764f,
  7.6293566200796095f, 7.6366246205436488f, 7.6438561897747244f,
  7.6510516911789290f, 7.6582114827517955f, 7.6653359171851765f,
  7.6724253419714952f, 7.6794800995054464f, 7.6865005271832185f,
  7.6934869574993252f, 7.7004397181410926f, 7.7073591320808825f,
  7.7142455176661224f, 7.7210991887071856f, 7.7279204545631996f,
  7.7347096202258392f, 7.7414669864011465f, 7.7481928495894596f,
  7.7548875021634691f, 7.7615512324444795f, 7.7681843247769260f,
  7.7747870596011737f, 7.7813597135246608f, 7.7879025593914317f,
  7.7944158663501062f, 7.8008998999203047f, 7.8073549220576037f,
  7.8137811912170374f, 7.8201789624151887f, 7.8265484872909159f,
  7.8328900141647422f, 7.8392037880969445f, 7.8454900509443757f,
  7.8517490414160571f, 7.8579809951275719f, 7.8641861446542798f,
  7.8703647195834048f, 7.8765169465650002f, 7.8826430493618425f,
  7.8887432488982601f, 7.8948177633079446f, 7.9008668079807496f,
  7.9068905956085187f, 7.9128893362299619f, 7.9188632372745955f,
  7.9248125036057813f, 7.9307373375628867f, 7.9366379390025719f,
  7.9425145053392399f, 7.9483672315846778f, 7.9541963103868758f,
  7.9600019320680806f, 7.9657842846620870f, 7.9715435539507720f,
  7.9772799234999168f, 7.9829935746943104f, 7.9886846867721664f,
  7.9943534368588578f
};
