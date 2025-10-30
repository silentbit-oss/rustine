# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/noise.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/noise.c"
# 16 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/noise.c"
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
# 17 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/noise.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 18 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/noise.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 19 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/noise.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 20 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/noise.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/errno.h" 1
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/noise.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/noise.h" 1
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/noise.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/noise.h" 2

struct osn_context;

int open_simplex_noise(int64_t seed, struct osn_context** ctx);
void open_simplex_noise_free(struct osn_context* ctx);
int open_simplex_noise_init_perm(
    struct osn_context* ctx, int16_t p[], int nelements);
double open_simplex_noise2(struct osn_context* ctx, double x, double y);
double open_simplex_noise3(
    struct osn_context* ctx, double x, double y, double z);
double open_simplex_noise4(
    struct osn_context* ctx, double x, double y, double z, double w);
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/noise.c" 2
# 37 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/noise.c"
struct osn_context {
    int16_t* perm;
    int16_t* permGradIndex3D;
};







static const int8_t gradients2D[] = {
    5, 2, 2, 5, -5, 2, -2, 5, 5, -2, 2, -5, -5, -2, -2, -5,
};







static const signed char gradients3D[] = {
    -11, 4, 4, -4, 11, 4, -4, 4, 11, 11, 4, 4, 4, 11, 4, 4, 4, 11, -11, -4, 4,
    -4, -11, 4, -4, -4, 11, 11, -4, 4, 4, -11, 4, 4, -4, 11, -11, 4, -4, -4, 11,
    -4, -4, 4, -11, 11, 4, -4, 4, 11, -4, 4, 4, -11, -11, -4, -4, -4, -11, -4,
    -4, -4, -11, 11, -4, -4, 4, -11, -4, 4, -4, -11,
};







static const signed char gradients4D[] = {
    3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, -3, 1, 1, 1, -1, 3, 1, 1,
    -1, 1, 3, 1, -1, 1, 1, 3, 3, -1, 1, 1, 1, -3, 1, 1, 1, -1, 3, 1, 1, -1, 1,
    3, -3, -1, 1, 1, -1, -3, 1, 1, -1, -1, 3, 1, -1, -1, 1, 3, 3, 1, -1, 1, 1,
    3, -1, 1, 1, 1, -3, 1, 1, 1, -1, 3, -3, 1, -1, 1, -1, 3, -1, 1, -1, 1, -3,
    1, -1, 1, -1, 3, 3, -1, -1, 1, 1, -3, -1, 1, 1, -1, -3, 1, 1, -1, -1, 3, -3,
    -1, -1, 1, -1, -3, -1, 1, -1, -1, -3, 1, -1, -1, -1, 3, 3, 1, 1, -1, 1, 3,
    1, -1, 1, 1, 3, -1, 1, 1, 1, -3, -3, 1, 1, -1, -1, 3, 1, -1, -1, 1, 3, -1,
    -1, 1, 1, -3, 3, -1, 1, -1, 1, -3, 1, -1, 1, -1, 3, -1, 1, -1, 1, -3, -3,
    -1, 1, -1, -1, -3, 1, -1, -1, -1, 3, -1, -1, -1, 1, -3, 3, 1, -1, -1, 1, 3,
    -1, -1, 1, 1, -3, -1, 1, 1, -1, -3, -3, 1, -1, -1, -1, 3, -1, -1, -1, 1, -3,
    -1, -1, 1, -1, -3, 3, -1, -1, -1, 1, -3, -1, -1, 1, -1, -3, -1, 1, -1, -1,
    -3, -3, -1, -1, -1, -1, -3, -1, -1, -1, -1, -3, -1, -1, -1, -1, -3,
};

static double extrapolate2(
    struct osn_context* ctx, int xsb, int ysb, double dx, double dy)
{
    int16_t* perm = ctx->perm;
    int index = perm[(perm[xsb & 0xFF] + ysb) & 0xFF] & 0x0E;
    return gradients2D[index] * dx + gradients2D[index + 1] * dy;
}

static double extrapolate3(struct osn_context* ctx, int xsb, int ysb, int zsb,
    double dx, double dy, double dz)
{
    int16_t* perm = ctx->perm;
    int16_t* permGradIndex3D = ctx->permGradIndex3D;
    int index =
        permGradIndex3D[(perm[(perm[xsb & 0xFF] + ysb) & 0xFF] + zsb) & 0xFF];
    return gradients3D[index] * dx + gradients3D[index + 1] * dy +
           gradients3D[index + 2] * dz;
}

static double extrapolate4(struct osn_context* ctx, int xsb, int ysb, int zsb,
    int wsb, double dx, double dy, double dz, double dw)
{
    int16_t* perm = ctx->perm;
    int index =
        perm[(perm[(perm[(perm[xsb & 0xFF] + ysb) & 0xFF] + zsb) & 0xFF] +
                 wsb) &
             0xFF] &
        0xFC;
    return gradients4D[index] * dx + gradients4D[index + 1] * dy +
           gradients4D[index + 2] * dz + gradients4D[index + 3] * dw;
}

static inline int fastFloor(double x)
{
    int xi = (int) x;
    return x < xi ? xi - 1 : xi;
}

static int allocate_perm(struct osn_context* ctx, int nperm, int ngrad)
{
    if (ctx->perm)
        free(ctx->perm);
    if (ctx->permGradIndex3D)
        free(ctx->permGradIndex3D);
    ctx->perm = malloc(sizeof(*ctx->perm) * nperm);
    if (!ctx->perm)
        return -ENOMEM;
    ctx->permGradIndex3D = malloc(sizeof(*ctx->permGradIndex3D) * ngrad);
    if (!ctx->permGradIndex3D) {
        free(ctx->perm);
        return -ENOMEM;
    }
    return 0;
}

int open_simplex_noise_init_perm(
    struct osn_context* ctx, int16_t p[], int nelements)
{
    int i, rc;

    rc = allocate_perm(ctx, nelements, 256);
    if (rc)
        return rc;
    memcpy(ctx->perm, p, sizeof(*ctx->perm) * nelements);

    for (i = 0; i < 256; i++) {


        ctx->permGradIndex3D[i] =
            (int16_t)((ctx->perm[i] % ((sizeof((gradients3D)) / sizeof((gradients3D)[0])) / 3)) * 3);
    }
    return 0;
}






int open_simplex_noise(int64_t seed, struct osn_context** ctx)
{
    int rc;
    int16_t source[256];
    int i;
    int16_t* perm;
    int16_t* permGradIndex3D;

    *ctx = malloc(sizeof(**ctx));
    if (!(*ctx))
        return -ENOMEM;
    (*ctx)->perm = 0;
    (*ctx)->permGradIndex3D = 0;

    rc = allocate_perm(*ctx, 256, 256);
    if (rc) {
        free(*ctx);
        return rc;
    }

    perm = (*ctx)->perm;
    permGradIndex3D = (*ctx)->permGradIndex3D;

    for (i = 0; i < 256; i++)
        source[i] = (int16_t) i;
    seed = seed * 6364136223846793005LL + 1442695040888963407LL;
    seed = seed * 6364136223846793005LL + 1442695040888963407LL;
    seed = seed * 6364136223846793005LL + 1442695040888963407LL;
    for (i = 255; i >= 0; i--) {
        seed = seed * 6364136223846793005LL + 1442695040888963407LL;
        int r = (int) ((seed + 31) % (i + 1));
        if (r < 0)
            r += (i + 1);
        perm[i] = source[r];
        permGradIndex3D[i] =
            (short) ((perm[i] % ((sizeof((gradients3D)) / sizeof((gradients3D)[0])) / 3)) * 3);
        source[r] = source[i];
    }
    return 0;
}

void open_simplex_noise_free(struct osn_context* ctx)
{
    if (!ctx)
        return;
    if (ctx->perm) {
        free(ctx->perm);
        ctx->perm = 0;
    }
    if (ctx->permGradIndex3D) {
        free(ctx->permGradIndex3D);
        ctx->permGradIndex3D = 0;
    }
    free(ctx);
}


double open_simplex_noise2(struct osn_context* ctx, double x, double y)
{

    double stretchOffset = (x + y) * (-0.211324865405187);
    double xs = x + stretchOffset;
    double ys = y + stretchOffset;



    int xsb = fastFloor(xs);
    int ysb = fastFloor(ys);



    double squishOffset = (xsb + ysb) * (0.366025403784439);
    double xb = xsb + squishOffset;
    double yb = ysb + squishOffset;


    double xins = xs - xsb;
    double yins = ys - ysb;


    double inSum = xins + yins;


    double dx0 = x - xb;
    double dy0 = y - yb;


    double dx_ext, dy_ext;
    int xsv_ext, ysv_ext;

    double value = 0;


    double dx1 = dx0 - 1 - (0.366025403784439);
    double dy1 = dy0 - 0 - (0.366025403784439);
    double attn1 = 2 - dx1 * dx1 - dy1 * dy1;
    if (attn1 > 0) {
        attn1 *= attn1;
        value += attn1 * attn1 * extrapolate2(ctx, xsb + 1, ysb + 0, dx1, dy1);
    }


    double dx2 = dx0 - 0 - (0.366025403784439);
    double dy2 = dy0 - 1 - (0.366025403784439);
    double attn2 = 2 - dx2 * dx2 - dy2 * dy2;
    if (attn2 > 0) {
        attn2 *= attn2;
        value += attn2 * attn2 * extrapolate2(ctx, xsb + 0, ysb + 1, dx2, dy2);
    }

    if (inSum <= 1) {
        double zins = 1 - inSum;
        if (zins > xins ||
            zins >
                yins) {
            if (xins > yins) {
                xsv_ext = xsb + 1;
                ysv_ext = ysb - 1;
                dx_ext = dx0 - 1;
                dy_ext = dy0 + 1;
            } else {
                xsv_ext = xsb - 1;
                ysv_ext = ysb + 1;
                dx_ext = dx0 + 1;
                dy_ext = dy0 - 1;
            }
        } else {
            xsv_ext = xsb + 1;
            ysv_ext = ysb + 1;
            dx_ext = dx0 - 1 - 2 * (0.366025403784439);
            dy_ext = dy0 - 1 - 2 * (0.366025403784439);
        }
    } else {
        double zins = 2 - inSum;
        if (zins < xins ||
            zins <
                yins) {
            if (xins > yins) {
                xsv_ext = xsb + 2;
                ysv_ext = ysb + 0;
                dx_ext = dx0 - 2 - 2 * (0.366025403784439);
                dy_ext = dy0 + 0 - 2 * (0.366025403784439);
            } else {
                xsv_ext = xsb + 0;
                ysv_ext = ysb + 2;
                dx_ext = dx0 + 0 - 2 * (0.366025403784439);
                dy_ext = dy0 - 2 - 2 * (0.366025403784439);
            }
        } else {
            dx_ext = dx0;
            dy_ext = dy0;
            xsv_ext = xsb;
            ysv_ext = ysb;
        }
        xsb += 1;
        ysb += 1;
        dx0 = dx0 - 1 - 2 * (0.366025403784439);
        dy0 = dy0 - 1 - 2 * (0.366025403784439);
    }


    double attn0 = 2 - dx0 * dx0 - dy0 * dy0;
    if (attn0 > 0) {
        attn0 *= attn0;
        value += attn0 * attn0 * extrapolate2(ctx, xsb, ysb, dx0, dy0);
    }


    double attn_ext = 2 - dx_ext * dx_ext - dy_ext * dy_ext;
    if (attn_ext > 0) {
        attn_ext *= attn_ext;
        value += attn_ext * attn_ext *
                 extrapolate2(ctx, xsv_ext, ysv_ext, dx_ext, dy_ext);
    }

    return value / (47.0);
}




double open_simplex_noise3(
    struct osn_context* ctx, double x, double y, double z)
{

    double stretchOffset = (x + y + z) * (-1.0 / 6.0);
    double xs = x + stretchOffset;
    double ys = y + stretchOffset;
    double zs = z + stretchOffset;



    int xsb = fastFloor(xs);
    int ysb = fastFloor(ys);
    int zsb = fastFloor(zs);



    double squishOffset = (xsb + ysb + zsb) * (1.0 / 3.0);
    double xb = xsb + squishOffset;
    double yb = ysb + squishOffset;
    double zb = zsb + squishOffset;


    double xins = xs - xsb;
    double yins = ys - ysb;
    double zins = zs - zsb;


    double inSum = xins + yins + zins;


    double dx0 = x - xb;
    double dy0 = y - yb;
    double dz0 = z - zb;


    double dx_ext0, dy_ext0, dz_ext0;
    double dx_ext1, dy_ext1, dz_ext1;
    int xsv_ext0, ysv_ext0, zsv_ext0;
    int xsv_ext1, ysv_ext1, zsv_ext1;

    double value = 0;
    if (inSum <= 1) {


        int8_t aPoint = 0x01;
        double aScore = xins;
        int8_t bPoint = 0x02;
        double bScore = yins;
        if (aScore >= bScore && zins > bScore) {
            bScore = zins;
            bPoint = 0x04;
        } else if (aScore < bScore && zins > aScore) {
            aScore = zins;
            aPoint = 0x04;
        }





        double wins = 1 - inSum;
        if (wins > aScore || wins > bScore) {

            int8_t c = (bScore > aScore ? bPoint : aPoint);




            if ((c & 0x01) == 0) {
                xsv_ext0 = xsb - 1;
                xsv_ext1 = xsb;
                dx_ext0 = dx0 + 1;
                dx_ext1 = dx0;
            } else {
                xsv_ext0 = xsv_ext1 = xsb + 1;
                dx_ext0 = dx_ext1 = dx0 - 1;
            }

            if ((c & 0x02) == 0) {
                ysv_ext0 = ysv_ext1 = ysb;
                dy_ext0 = dy_ext1 = dy0;
                if ((c & 0x01) == 0) {
                    ysv_ext1 -= 1;
                    dy_ext1 += 1;
                } else {
                    ysv_ext0 -= 1;
                    dy_ext0 += 1;
                }
            } else {
                ysv_ext0 = ysv_ext1 = ysb + 1;
                dy_ext0 = dy_ext1 = dy0 - 1;
            }

            if ((c & 0x04) == 0) {
                zsv_ext0 = zsb;
                zsv_ext1 = zsb - 1;
                dz_ext0 = dz0;
                dz_ext1 = dz0 + 1;
            } else {
                zsv_ext0 = zsv_ext1 = zsb + 1;
                dz_ext0 = dz_ext1 = dz0 - 1;
            }
        } else {
            int8_t c = (int8_t)(aPoint | bPoint);



            if ((c & 0x01) == 0) {
                xsv_ext0 = xsb;
                xsv_ext1 = xsb - 1;
                dx_ext0 = dx0 - 2 * (1.0 / 3.0);
                dx_ext1 = dx0 + 1 - (1.0 / 3.0);
            } else {
                xsv_ext0 = xsv_ext1 = xsb + 1;
                dx_ext0 = dx0 - 1 - 2 * (1.0 / 3.0);
                dx_ext1 = dx0 - 1 - (1.0 / 3.0);
            }

            if ((c & 0x02) == 0) {
                ysv_ext0 = ysb;
                ysv_ext1 = ysb - 1;
                dy_ext0 = dy0 - 2 * (1.0 / 3.0);
                dy_ext1 = dy0 + 1 - (1.0 / 3.0);
            } else {
                ysv_ext0 = ysv_ext1 = ysb + 1;
                dy_ext0 = dy0 - 1 - 2 * (1.0 / 3.0);
                dy_ext1 = dy0 - 1 - (1.0 / 3.0);
            }

            if ((c & 0x04) == 0) {
                zsv_ext0 = zsb;
                zsv_ext1 = zsb - 1;
                dz_ext0 = dz0 - 2 * (1.0 / 3.0);
                dz_ext1 = dz0 + 1 - (1.0 / 3.0);
            } else {
                zsv_ext0 = zsv_ext1 = zsb + 1;
                dz_ext0 = dz0 - 1 - 2 * (1.0 / 3.0);
                dz_ext1 = dz0 - 1 - (1.0 / 3.0);
            }
        }


        double attn0 = 2 - dx0 * dx0 - dy0 * dy0 - dz0 * dz0;
        if (attn0 > 0) {
            attn0 *= attn0;
            value += attn0 * attn0 * extrapolate3(ctx, xsb + 0, ysb + 0,
                                         zsb + 0, dx0, dy0, dz0);
        }


        double dx1 = dx0 - 1 - (1.0 / 3.0);
        double dy1 = dy0 - 0 - (1.0 / 3.0);
        double dz1 = dz0 - 0 - (1.0 / 3.0);
        double attn1 = 2 - dx1 * dx1 - dy1 * dy1 - dz1 * dz1;
        if (attn1 > 0) {
            attn1 *= attn1;
            value += attn1 * attn1 * extrapolate3(ctx, xsb + 1, ysb + 0,
                                         zsb + 0, dx1, dy1, dz1);
        }


        double dx2 = dx0 - 0 - (1.0 / 3.0);
        double dy2 = dy0 - 1 - (1.0 / 3.0);
        double dz2 = dz1;
        double attn2 = 2 - dx2 * dx2 - dy2 * dy2 - dz2 * dz2;
        if (attn2 > 0) {
            attn2 *= attn2;
            value += attn2 * attn2 * extrapolate3(ctx, xsb + 0, ysb + 1,
                                         zsb + 0, dx2, dy2, dz2);
        }


        double dx3 = dx2;
        double dy3 = dy1;
        double dz3 = dz0 - 1 - (1.0 / 3.0);
        double attn3 = 2 - dx3 * dx3 - dy3 * dy3 - dz3 * dz3;
        if (attn3 > 0) {
            attn3 *= attn3;
            value += attn3 * attn3 * extrapolate3(ctx, xsb + 0, ysb + 0,
                                         zsb + 1, dx3, dy3, dz3);
        }
    } else if (inSum >=
               2) {



        int8_t aPoint = 0x06;
        double aScore = xins;
        int8_t bPoint = 0x05;
        double bScore = yins;
        if (aScore <= bScore && zins < bScore) {
            bScore = zins;
            bPoint = 0x03;
        } else if (aScore > bScore && zins < aScore) {
            aScore = zins;
            aPoint = 0x03;
        }





        double wins = 3 - inSum;
        if (wins < aScore || wins < bScore) {

            int8_t c = (bScore < aScore ? bPoint : aPoint);




            if ((c & 0x01) != 0) {
                xsv_ext0 = xsb + 2;
                xsv_ext1 = xsb + 1;
                dx_ext0 = dx0 - 2 - 3 * (1.0 / 3.0);
                dx_ext1 = dx0 - 1 - 3 * (1.0 / 3.0);
            } else {
                xsv_ext0 = xsv_ext1 = xsb;
                dx_ext0 = dx_ext1 = dx0 - 3 * (1.0 / 3.0);
            }

            if ((c & 0x02) != 0) {
                ysv_ext0 = ysv_ext1 = ysb + 1;
                dy_ext0 = dy_ext1 = dy0 - 1 - 3 * (1.0 / 3.0);
                if ((c & 0x01) != 0) {
                    ysv_ext1 += 1;
                    dy_ext1 -= 1;
                } else {
                    ysv_ext0 += 1;
                    dy_ext0 -= 1;
                }
            } else {
                ysv_ext0 = ysv_ext1 = ysb;
                dy_ext0 = dy_ext1 = dy0 - 3 * (1.0 / 3.0);
            }

            if ((c & 0x04) != 0) {
                zsv_ext0 = zsb + 1;
                zsv_ext1 = zsb + 2;
                dz_ext0 = dz0 - 1 - 3 * (1.0 / 3.0);
                dz_ext1 = dz0 - 2 - 3 * (1.0 / 3.0);
            } else {
                zsv_ext0 = zsv_ext1 = zsb;
                dz_ext0 = dz_ext1 = dz0 - 3 * (1.0 / 3.0);
            }
        } else {
            int8_t c = (int8_t)(aPoint & bPoint);



            if ((c & 0x01) != 0) {
                xsv_ext0 = xsb + 1;
                xsv_ext1 = xsb + 2;
                dx_ext0 = dx0 - 1 - (1.0 / 3.0);
                dx_ext1 = dx0 - 2 - 2 * (1.0 / 3.0);
            } else {
                xsv_ext0 = xsv_ext1 = xsb;
                dx_ext0 = dx0 - (1.0 / 3.0);
                dx_ext1 = dx0 - 2 * (1.0 / 3.0);
            }

            if ((c & 0x02) != 0) {
                ysv_ext0 = ysb + 1;
                ysv_ext1 = ysb + 2;
                dy_ext0 = dy0 - 1 - (1.0 / 3.0);
                dy_ext1 = dy0 - 2 - 2 * (1.0 / 3.0);
            } else {
                ysv_ext0 = ysv_ext1 = ysb;
                dy_ext0 = dy0 - (1.0 / 3.0);
                dy_ext1 = dy0 - 2 * (1.0 / 3.0);
            }

            if ((c & 0x04) != 0) {
                zsv_ext0 = zsb + 1;
                zsv_ext1 = zsb + 2;
                dz_ext0 = dz0 - 1 - (1.0 / 3.0);
                dz_ext1 = dz0 - 2 - 2 * (1.0 / 3.0);
            } else {
                zsv_ext0 = zsv_ext1 = zsb;
                dz_ext0 = dz0 - (1.0 / 3.0);
                dz_ext1 = dz0 - 2 * (1.0 / 3.0);
            }
        }


        double dx3 = dx0 - 1 - 2 * (1.0 / 3.0);
        double dy3 = dy0 - 1 - 2 * (1.0 / 3.0);
        double dz3 = dz0 - 0 - 2 * (1.0 / 3.0);
        double attn3 = 2 - dx3 * dx3 - dy3 * dy3 - dz3 * dz3;
        if (attn3 > 0) {
            attn3 *= attn3;
            value += attn3 * attn3 * extrapolate3(ctx, xsb + 1, ysb + 1,
                                         zsb + 0, dx3, dy3, dz3);
        }


        double dx2 = dx3;
        double dy2 = dy0 - 0 - 2 * (1.0 / 3.0);
        double dz2 = dz0 - 1 - 2 * (1.0 / 3.0);
        double attn2 = 2 - dx2 * dx2 - dy2 * dy2 - dz2 * dz2;
        if (attn2 > 0) {
            attn2 *= attn2;
            value += attn2 * attn2 * extrapolate3(ctx, xsb + 1, ysb + 0,
                                         zsb + 1, dx2, dy2, dz2);
        }


        double dx1 = dx0 - 0 - 2 * (1.0 / 3.0);
        double dy1 = dy3;
        double dz1 = dz2;
        double attn1 = 2 - dx1 * dx1 - dy1 * dy1 - dz1 * dz1;
        if (attn1 > 0) {
            attn1 *= attn1;
            value += attn1 * attn1 * extrapolate3(ctx, xsb + 0, ysb + 1,
                                         zsb + 1, dx1, dy1, dz1);
        }


        dx0 = dx0 - 1 - 3 * (1.0 / 3.0);
        dy0 = dy0 - 1 - 3 * (1.0 / 3.0);
        dz0 = dz0 - 1 - 3 * (1.0 / 3.0);
        double attn0 = 2 - dx0 * dx0 - dy0 * dy0 - dz0 * dz0;
        if (attn0 > 0) {
            attn0 *= attn0;
            value += attn0 * attn0 * extrapolate3(ctx, xsb + 1, ysb + 1,
                                         zsb + 1, dx0, dy0, dz0);
        }
    } else {
        double aScore;
        int8_t aPoint;
        int aIsFurtherSide;
        double bScore;
        int8_t bPoint;
        int bIsFurtherSide;


        double p1 = xins + yins;
        if (p1 > 1) {
            aScore = p1 - 1;
            aPoint = 0x03;
            aIsFurtherSide = 1;
        } else {
            aScore = 1 - p1;
            aPoint = 0x04;
            aIsFurtherSide = 0;
        }


        double p2 = xins + zins;
        if (p2 > 1) {
            bScore = p2 - 1;
            bPoint = 0x05;
            bIsFurtherSide = 1;
        } else {
            bScore = 1 - p2;
            bPoint = 0x02;
            bIsFurtherSide = 0;
        }



        double p3 = yins + zins;
        if (p3 > 1) {
            double score = p3 - 1;
            if (aScore <= bScore && aScore < score) {
                aScore = score;
                aPoint = 0x06;
                aIsFurtherSide = 1;
            } else if (aScore > bScore && bScore < score) {
                bScore = score;
                bPoint = 0x06;
                bIsFurtherSide = 1;
            }
        } else {
            double score = 1 - p3;
            if (aScore <= bScore && aScore < score) {
                aScore = score;
                aPoint = 0x01;
                aIsFurtherSide = 0;
            } else if (aScore > bScore && bScore < score) {
                bScore = score;
                bPoint = 0x01;
                bIsFurtherSide = 0;
            }
        }



        if (aIsFurtherSide == bIsFurtherSide) {
            if (aIsFurtherSide) {


                dx_ext0 = dx0 - 1 - 3 * (1.0 / 3.0);
                dy_ext0 = dy0 - 1 - 3 * (1.0 / 3.0);
                dz_ext0 = dz0 - 1 - 3 * (1.0 / 3.0);
                xsv_ext0 = xsb + 1;
                ysv_ext0 = ysb + 1;
                zsv_ext0 = zsb + 1;


                int8_t c = (int8_t)(aPoint & bPoint);
                if ((c & 0x01) != 0) {
                    dx_ext1 = dx0 - 2 - 2 * (1.0 / 3.0);
                    dy_ext1 = dy0 - 2 * (1.0 / 3.0);
                    dz_ext1 = dz0 - 2 * (1.0 / 3.0);
                    xsv_ext1 = xsb + 2;
                    ysv_ext1 = ysb;
                    zsv_ext1 = zsb;
                } else if ((c & 0x02) != 0) {
                    dx_ext1 = dx0 - 2 * (1.0 / 3.0);
                    dy_ext1 = dy0 - 2 - 2 * (1.0 / 3.0);
                    dz_ext1 = dz0 - 2 * (1.0 / 3.0);
                    xsv_ext1 = xsb;
                    ysv_ext1 = ysb + 2;
                    zsv_ext1 = zsb;
                } else {
                    dx_ext1 = dx0 - 2 * (1.0 / 3.0);
                    dy_ext1 = dy0 - 2 * (1.0 / 3.0);
                    dz_ext1 = dz0 - 2 - 2 * (1.0 / 3.0);
                    xsv_ext1 = xsb;
                    ysv_ext1 = ysb;
                    zsv_ext1 = zsb + 2;
                }
            } else {


                dx_ext0 = dx0;
                dy_ext0 = dy0;
                dz_ext0 = dz0;
                xsv_ext0 = xsb;
                ysv_ext0 = ysb;
                zsv_ext0 = zsb;


                int8_t c = (int8_t)(aPoint | bPoint);
                if ((c & 0x01) == 0) {
                    dx_ext1 = dx0 + 1 - (1.0 / 3.0);
                    dy_ext1 = dy0 - 1 - (1.0 / 3.0);
                    dz_ext1 = dz0 - 1 - (1.0 / 3.0);
                    xsv_ext1 = xsb - 1;
                    ysv_ext1 = ysb + 1;
                    zsv_ext1 = zsb + 1;
                } else if ((c & 0x02) == 0) {
                    dx_ext1 = dx0 - 1 - (1.0 / 3.0);
                    dy_ext1 = dy0 + 1 - (1.0 / 3.0);
                    dz_ext1 = dz0 - 1 - (1.0 / 3.0);
                    xsv_ext1 = xsb + 1;
                    ysv_ext1 = ysb - 1;
                    zsv_ext1 = zsb + 1;
                } else {
                    dx_ext1 = dx0 - 1 - (1.0 / 3.0);
                    dy_ext1 = dy0 - 1 - (1.0 / 3.0);
                    dz_ext1 = dz0 + 1 - (1.0 / 3.0);
                    xsv_ext1 = xsb + 1;
                    ysv_ext1 = ysb + 1;
                    zsv_ext1 = zsb - 1;
                }
            }
        } else {
            int8_t c1, c2;
            if (aIsFurtherSide) {
                c1 = aPoint;
                c2 = bPoint;
            } else {
                c1 = bPoint;
                c2 = aPoint;
            }


            if ((c1 & 0x01) == 0) {
                dx_ext0 = dx0 + 1 - (1.0 / 3.0);
                dy_ext0 = dy0 - 1 - (1.0 / 3.0);
                dz_ext0 = dz0 - 1 - (1.0 / 3.0);
                xsv_ext0 = xsb - 1;
                ysv_ext0 = ysb + 1;
                zsv_ext0 = zsb + 1;
            } else if ((c1 & 0x02) == 0) {
                dx_ext0 = dx0 - 1 - (1.0 / 3.0);
                dy_ext0 = dy0 + 1 - (1.0 / 3.0);
                dz_ext0 = dz0 - 1 - (1.0 / 3.0);
                xsv_ext0 = xsb + 1;
                ysv_ext0 = ysb - 1;
                zsv_ext0 = zsb + 1;
            } else {
                dx_ext0 = dx0 - 1 - (1.0 / 3.0);
                dy_ext0 = dy0 - 1 - (1.0 / 3.0);
                dz_ext0 = dz0 + 1 - (1.0 / 3.0);
                xsv_ext0 = xsb + 1;
                ysv_ext0 = ysb + 1;
                zsv_ext0 = zsb - 1;
            }


            dx_ext1 = dx0 - 2 * (1.0 / 3.0);
            dy_ext1 = dy0 - 2 * (1.0 / 3.0);
            dz_ext1 = dz0 - 2 * (1.0 / 3.0);
            xsv_ext1 = xsb;
            ysv_ext1 = ysb;
            zsv_ext1 = zsb;
            if ((c2 & 0x01) != 0) {
                dx_ext1 -= 2;
                xsv_ext1 += 2;
            } else if ((c2 & 0x02) != 0) {
                dy_ext1 -= 2;
                ysv_ext1 += 2;
            } else {
                dz_ext1 -= 2;
                zsv_ext1 += 2;
            }
        }


        double dx1 = dx0 - 1 - (1.0 / 3.0);
        double dy1 = dy0 - 0 - (1.0 / 3.0);
        double dz1 = dz0 - 0 - (1.0 / 3.0);
        double attn1 = 2 - dx1 * dx1 - dy1 * dy1 - dz1 * dz1;
        if (attn1 > 0) {
            attn1 *= attn1;
            value += attn1 * attn1 * extrapolate3(ctx, xsb + 1, ysb + 0,
                                         zsb + 0, dx1, dy1, dz1);
        }


        double dx2 = dx0 - 0 - (1.0 / 3.0);
        double dy2 = dy0 - 1 - (1.0 / 3.0);
        double dz2 = dz1;
        double attn2 = 2 - dx2 * dx2 - dy2 * dy2 - dz2 * dz2;
        if (attn2 > 0) {
            attn2 *= attn2;
            value += attn2 * attn2 * extrapolate3(ctx, xsb + 0, ysb + 1,
                                         zsb + 0, dx2, dy2, dz2);
        }


        double dx3 = dx2;
        double dy3 = dy1;
        double dz3 = dz0 - 1 - (1.0 / 3.0);
        double attn3 = 2 - dx3 * dx3 - dy3 * dy3 - dz3 * dz3;
        if (attn3 > 0) {
            attn3 *= attn3;
            value += attn3 * attn3 * extrapolate3(ctx, xsb + 0, ysb + 0,
                                         zsb + 1, dx3, dy3, dz3);
        }


        double dx4 = dx0 - 1 - 2 * (1.0 / 3.0);
        double dy4 = dy0 - 1 - 2 * (1.0 / 3.0);
        double dz4 = dz0 - 0 - 2 * (1.0 / 3.0);
        double attn4 = 2 - dx4 * dx4 - dy4 * dy4 - dz4 * dz4;
        if (attn4 > 0) {
            attn4 *= attn4;
            value += attn4 * attn4 * extrapolate3(ctx, xsb + 1, ysb + 1,
                                         zsb + 0, dx4, dy4, dz4);
        }


        double dx5 = dx4;
        double dy5 = dy0 - 0 - 2 * (1.0 / 3.0);
        double dz5 = dz0 - 1 - 2 * (1.0 / 3.0);
        double attn5 = 2 - dx5 * dx5 - dy5 * dy5 - dz5 * dz5;
        if (attn5 > 0) {
            attn5 *= attn5;
            value += attn5 * attn5 * extrapolate3(ctx, xsb + 1, ysb + 0,
                                         zsb + 1, dx5, dy5, dz5);
        }


        double dx6 = dx0 - 0 - 2 * (1.0 / 3.0);
        double dy6 = dy4;
        double dz6 = dz5;
        double attn6 = 2 - dx6 * dx6 - dy6 * dy6 - dz6 * dz6;
        if (attn6 > 0) {
            attn6 *= attn6;
            value += attn6 * attn6 * extrapolate3(ctx, xsb + 0, ysb + 1,
                                         zsb + 1, dx6, dy6, dz6);
        }
    }


    double attn_ext0 =
        2 - dx_ext0 * dx_ext0 - dy_ext0 * dy_ext0 - dz_ext0 * dz_ext0;
    if (attn_ext0 > 0) {
        attn_ext0 *= attn_ext0;
        value +=
            attn_ext0 * attn_ext0 * extrapolate3(ctx, xsv_ext0, ysv_ext0,
                                        zsv_ext0, dx_ext0, dy_ext0, dz_ext0);
    }


    double attn_ext1 =
        2 - dx_ext1 * dx_ext1 - dy_ext1 * dy_ext1 - dz_ext1 * dz_ext1;
    if (attn_ext1 > 0) {
        attn_ext1 *= attn_ext1;
        value +=
            attn_ext1 * attn_ext1 * extrapolate3(ctx, xsv_ext1, ysv_ext1,
                                        zsv_ext1, dx_ext1, dy_ext1, dz_ext1);
    }

    return value / (103.0);
}




double open_simplex_noise4(
    struct osn_context* ctx, double x, double y, double z, double w)
{

    double stretchOffset = (x + y + z + w) * (-0.138196601125011);
    double xs = x + stretchOffset;
    double ys = y + stretchOffset;
    double zs = z + stretchOffset;
    double ws = w + stretchOffset;



    int xsb = fastFloor(xs);
    int ysb = fastFloor(ys);
    int zsb = fastFloor(zs);
    int wsb = fastFloor(ws);



    double squishOffset = (xsb + ysb + zsb + wsb) * (0.309016994374947);
    double xb = xsb + squishOffset;
    double yb = ysb + squishOffset;
    double zb = zsb + squishOffset;
    double wb = wsb + squishOffset;



    double xins = xs - xsb;
    double yins = ys - ysb;
    double zins = zs - zsb;
    double wins = ws - wsb;


    double inSum = xins + yins + zins + wins;


    double dx0 = x - xb;
    double dy0 = y - yb;
    double dz0 = z - zb;
    double dw0 = w - wb;


    double dx_ext0, dy_ext0, dz_ext0, dw_ext0;
    double dx_ext1, dy_ext1, dz_ext1, dw_ext1;
    double dx_ext2, dy_ext2, dz_ext2, dw_ext2;
    int xsv_ext0, ysv_ext0, zsv_ext0, wsv_ext0;
    int xsv_ext1, ysv_ext1, zsv_ext1, wsv_ext1;
    int xsv_ext2, ysv_ext2, zsv_ext2, wsv_ext2;

    double value = 0;
    if (inSum <= 1) {



        int8_t aPoint = 0x01;
        double aScore = xins;
        int8_t bPoint = 0x02;
        double bScore = yins;
        if (aScore >= bScore && zins > bScore) {
            bScore = zins;
            bPoint = 0x04;
        } else if (aScore < bScore && zins > aScore) {
            aScore = zins;
            aPoint = 0x04;
        }
        if (aScore >= bScore && wins > bScore) {
            bScore = wins;
            bPoint = 0x08;
        } else if (aScore < bScore && wins > aScore) {
            aScore = wins;
            aPoint = 0x08;
        }





        double uins = 1 - inSum;
        if (uins > aScore || uins > bScore) {

            int8_t c = (bScore > aScore ? bPoint : aPoint);



            if ((c & 0x01) == 0) {
                xsv_ext0 = xsb - 1;
                xsv_ext1 = xsv_ext2 = xsb;
                dx_ext0 = dx0 + 1;
                dx_ext1 = dx_ext2 = dx0;
            } else {
                xsv_ext0 = xsv_ext1 = xsv_ext2 = xsb + 1;
                dx_ext0 = dx_ext1 = dx_ext2 = dx0 - 1;
            }

            if ((c & 0x02) == 0) {
                ysv_ext0 = ysv_ext1 = ysv_ext2 = ysb;
                dy_ext0 = dy_ext1 = dy_ext2 = dy0;
                if ((c & 0x01) == 0x01) {
                    ysv_ext0 -= 1;
                    dy_ext0 += 1;
                } else {
                    ysv_ext1 -= 1;
                    dy_ext1 += 1;
                }
            } else {
                ysv_ext0 = ysv_ext1 = ysv_ext2 = ysb + 1;
                dy_ext0 = dy_ext1 = dy_ext2 = dy0 - 1;
            }

            if ((c & 0x04) == 0) {
                zsv_ext0 = zsv_ext1 = zsv_ext2 = zsb;
                dz_ext0 = dz_ext1 = dz_ext2 = dz0;
                if ((c & 0x03) != 0) {
                    if ((c & 0x03) == 0x03) {
                        zsv_ext0 -= 1;
                        dz_ext0 += 1;
                    } else {
                        zsv_ext1 -= 1;
                        dz_ext1 += 1;
                    }
                } else {
                    zsv_ext2 -= 1;
                    dz_ext2 += 1;
                }
            } else {
                zsv_ext0 = zsv_ext1 = zsv_ext2 = zsb + 1;
                dz_ext0 = dz_ext1 = dz_ext2 = dz0 - 1;
            }

            if ((c & 0x08) == 0) {
                wsv_ext0 = wsv_ext1 = wsb;
                wsv_ext2 = wsb - 1;
                dw_ext0 = dw_ext1 = dw0;
                dw_ext2 = dw0 + 1;
            } else {
                wsv_ext0 = wsv_ext1 = wsv_ext2 = wsb + 1;
                dw_ext0 = dw_ext1 = dw_ext2 = dw0 - 1;
            }
        } else {

            int8_t c = (int8_t)(aPoint | bPoint);



            if ((c & 0x01) == 0) {
                xsv_ext0 = xsv_ext2 = xsb;
                xsv_ext1 = xsb - 1;
                dx_ext0 = dx0 - 2 * (0.309016994374947);
                dx_ext1 = dx0 + 1 - (0.309016994374947);
                dx_ext2 = dx0 - (0.309016994374947);
            } else {
                xsv_ext0 = xsv_ext1 = xsv_ext2 = xsb + 1;
                dx_ext0 = dx0 - 1 - 2 * (0.309016994374947);
                dx_ext1 = dx_ext2 = dx0 - 1 - (0.309016994374947);
            }

            if ((c & 0x02) == 0) {
                ysv_ext0 = ysv_ext1 = ysv_ext2 = ysb;
                dy_ext0 = dy0 - 2 * (0.309016994374947);
                dy_ext1 = dy_ext2 = dy0 - (0.309016994374947);
                if ((c & 0x01) == 0x01) {
                    ysv_ext1 -= 1;
                    dy_ext1 += 1;
                } else {
                    ysv_ext2 -= 1;
                    dy_ext2 += 1;
                }
            } else {
                ysv_ext0 = ysv_ext1 = ysv_ext2 = ysb + 1;
                dy_ext0 = dy0 - 1 - 2 * (0.309016994374947);
                dy_ext1 = dy_ext2 = dy0 - 1 - (0.309016994374947);
            }

            if ((c & 0x04) == 0) {
                zsv_ext0 = zsv_ext1 = zsv_ext2 = zsb;
                dz_ext0 = dz0 - 2 * (0.309016994374947);
                dz_ext1 = dz_ext2 = dz0 - (0.309016994374947);
                if ((c & 0x03) == 0x03) {
                    zsv_ext1 -= 1;
                    dz_ext1 += 1;
                } else {
                    zsv_ext2 -= 1;
                    dz_ext2 += 1;
                }
            } else {
                zsv_ext0 = zsv_ext1 = zsv_ext2 = zsb + 1;
                dz_ext0 = dz0 - 1 - 2 * (0.309016994374947);
                dz_ext1 = dz_ext2 = dz0 - 1 - (0.309016994374947);
            }

            if ((c & 0x08) == 0) {
                wsv_ext0 = wsv_ext1 = wsb;
                wsv_ext2 = wsb - 1;
                dw_ext0 = dw0 - 2 * (0.309016994374947);
                dw_ext1 = dw0 - (0.309016994374947);
                dw_ext2 = dw0 + 1 - (0.309016994374947);
            } else {
                wsv_ext0 = wsv_ext1 = wsv_ext2 = wsb + 1;
                dw_ext0 = dw0 - 1 - 2 * (0.309016994374947);
                dw_ext1 = dw_ext2 = dw0 - 1 - (0.309016994374947);
            }
        }


        double attn0 = 2 - dx0 * dx0 - dy0 * dy0 - dz0 * dz0 - dw0 * dw0;
        if (attn0 > 0) {
            attn0 *= attn0;
            value += attn0 * attn0 * extrapolate4(ctx, xsb + 0, ysb + 0,
                                         zsb + 0, wsb + 0, dx0, dy0, dz0, dw0);
        }


        double dx1 = dx0 - 1 - (0.309016994374947);
        double dy1 = dy0 - 0 - (0.309016994374947);
        double dz1 = dz0 - 0 - (0.309016994374947);
        double dw1 = dw0 - 0 - (0.309016994374947);
        double attn1 = 2 - dx1 * dx1 - dy1 * dy1 - dz1 * dz1 - dw1 * dw1;
        if (attn1 > 0) {
            attn1 *= attn1;
            value += attn1 * attn1 * extrapolate4(ctx, xsb + 1, ysb + 0,
                                         zsb + 0, wsb + 0, dx1, dy1, dz1, dw1);
        }


        double dx2 = dx0 - 0 - (0.309016994374947);
        double dy2 = dy0 - 1 - (0.309016994374947);
        double dz2 = dz1;
        double dw2 = dw1;
        double attn2 = 2 - dx2 * dx2 - dy2 * dy2 - dz2 * dz2 - dw2 * dw2;
        if (attn2 > 0) {
            attn2 *= attn2;
            value += attn2 * attn2 * extrapolate4(ctx, xsb + 0, ysb + 1,
                                         zsb + 0, wsb + 0, dx2, dy2, dz2, dw2);
        }


        double dx3 = dx2;
        double dy3 = dy1;
        double dz3 = dz0 - 1 - (0.309016994374947);
        double dw3 = dw1;
        double attn3 = 2 - dx3 * dx3 - dy3 * dy3 - dz3 * dz3 - dw3 * dw3;
        if (attn3 > 0) {
            attn3 *= attn3;
            value += attn3 * attn3 * extrapolate4(ctx, xsb + 0, ysb + 0,
                                         zsb + 1, wsb + 0, dx3, dy3, dz3, dw3);
        }


        double dx4 = dx2;
        double dy4 = dy1;
        double dz4 = dz1;
        double dw4 = dw0 - 1 - (0.309016994374947);
        double attn4 = 2 - dx4 * dx4 - dy4 * dy4 - dz4 * dz4 - dw4 * dw4;
        if (attn4 > 0) {
            attn4 *= attn4;
            value += attn4 * attn4 * extrapolate4(ctx, xsb + 0, ysb + 0,
                                         zsb + 0, wsb + 1, dx4, dy4, dz4, dw4);
        }
    } else if (inSum >=
               3) {


        int8_t aPoint = 0x0E;
        double aScore = xins;
        int8_t bPoint = 0x0D;
        double bScore = yins;
        if (aScore <= bScore && zins < bScore) {
            bScore = zins;
            bPoint = 0x0B;
        } else if (aScore > bScore && zins < aScore) {
            aScore = zins;
            aPoint = 0x0B;
        }
        if (aScore <= bScore && wins < bScore) {
            bScore = wins;
            bPoint = 0x07;
        } else if (aScore > bScore && wins < aScore) {
            aScore = wins;
            aPoint = 0x07;
        }





        double uins = 4 - inSum;
        if (uins < aScore || uins < bScore) {

            int8_t c = (bScore < aScore ? bPoint : aPoint);




            if ((c & 0x01) != 0) {
                xsv_ext0 = xsb + 2;
                xsv_ext1 = xsv_ext2 = xsb + 1;
                dx_ext0 = dx0 - 2 - 4 * (0.309016994374947);
                dx_ext1 = dx_ext2 = dx0 - 1 - 4 * (0.309016994374947);
            } else {
                xsv_ext0 = xsv_ext1 = xsv_ext2 = xsb;
                dx_ext0 = dx_ext1 = dx_ext2 = dx0 - 4 * (0.309016994374947);
            }

            if ((c & 0x02) != 0) {
                ysv_ext0 = ysv_ext1 = ysv_ext2 = ysb + 1;
                dy_ext0 = dy_ext1 = dy_ext2 = dy0 - 1 - 4 * (0.309016994374947);
                if ((c & 0x01) != 0) {
                    ysv_ext1 += 1;
                    dy_ext1 -= 1;
                } else {
                    ysv_ext0 += 1;
                    dy_ext0 -= 1;
                }
            } else {
                ysv_ext0 = ysv_ext1 = ysv_ext2 = ysb;
                dy_ext0 = dy_ext1 = dy_ext2 = dy0 - 4 * (0.309016994374947);
            }

            if ((c & 0x04) != 0) {
                zsv_ext0 = zsv_ext1 = zsv_ext2 = zsb + 1;
                dz_ext0 = dz_ext1 = dz_ext2 = dz0 - 1 - 4 * (0.309016994374947);
                if ((c & 0x03) != 0x03) {
                    if ((c & 0x03) == 0) {
                        zsv_ext0 += 1;
                        dz_ext0 -= 1;
                    } else {
                        zsv_ext1 += 1;
                        dz_ext1 -= 1;
                    }
                } else {
                    zsv_ext2 += 1;
                    dz_ext2 -= 1;
                }
            } else {
                zsv_ext0 = zsv_ext1 = zsv_ext2 = zsb;
                dz_ext0 = dz_ext1 = dz_ext2 = dz0 - 4 * (0.309016994374947);
            }

            if ((c & 0x08) != 0) {
                wsv_ext0 = wsv_ext1 = wsb + 1;
                wsv_ext2 = wsb + 2;
                dw_ext0 = dw_ext1 = dw0 - 1 - 4 * (0.309016994374947);
                dw_ext2 = dw0 - 2 - 4 * (0.309016994374947);
            } else {
                wsv_ext0 = wsv_ext1 = wsv_ext2 = wsb;
                dw_ext0 = dw_ext1 = dw_ext2 = dw0 - 4 * (0.309016994374947);
            }
        } else {

            int8_t c = (int8_t)(aPoint & bPoint);



            if ((c & 0x01) != 0) {
                xsv_ext0 = xsv_ext2 = xsb + 1;
                xsv_ext1 = xsb + 2;
                dx_ext0 = dx0 - 1 - 2 * (0.309016994374947);
                dx_ext1 = dx0 - 2 - 3 * (0.309016994374947);
                dx_ext2 = dx0 - 1 - 3 * (0.309016994374947);
            } else {
                xsv_ext0 = xsv_ext1 = xsv_ext2 = xsb;
                dx_ext0 = dx0 - 2 * (0.309016994374947);
                dx_ext1 = dx_ext2 = dx0 - 3 * (0.309016994374947);
            }

            if ((c & 0x02) != 0) {
                ysv_ext0 = ysv_ext1 = ysv_ext2 = ysb + 1;
                dy_ext0 = dy0 - 1 - 2 * (0.309016994374947);
                dy_ext1 = dy_ext2 = dy0 - 1 - 3 * (0.309016994374947);
                if ((c & 0x01) != 0) {
                    ysv_ext2 += 1;
                    dy_ext2 -= 1;
                } else {
                    ysv_ext1 += 1;
                    dy_ext1 -= 1;
                }
            } else {
                ysv_ext0 = ysv_ext1 = ysv_ext2 = ysb;
                dy_ext0 = dy0 - 2 * (0.309016994374947);
                dy_ext1 = dy_ext2 = dy0 - 3 * (0.309016994374947);
            }

            if ((c & 0x04) != 0) {
                zsv_ext0 = zsv_ext1 = zsv_ext2 = zsb + 1;
                dz_ext0 = dz0 - 1 - 2 * (0.309016994374947);
                dz_ext1 = dz_ext2 = dz0 - 1 - 3 * (0.309016994374947);
                if ((c & 0x03) != 0) {
                    zsv_ext2 += 1;
                    dz_ext2 -= 1;
                } else {
                    zsv_ext1 += 1;
                    dz_ext1 -= 1;
                }
            } else {
                zsv_ext0 = zsv_ext1 = zsv_ext2 = zsb;
                dz_ext0 = dz0 - 2 * (0.309016994374947);
                dz_ext1 = dz_ext2 = dz0 - 3 * (0.309016994374947);
            }

            if ((c & 0x08) != 0) {
                wsv_ext0 = wsv_ext1 = wsb + 1;
                wsv_ext2 = wsb + 2;
                dw_ext0 = dw0 - 1 - 2 * (0.309016994374947);
                dw_ext1 = dw0 - 1 - 3 * (0.309016994374947);
                dw_ext2 = dw0 - 2 - 3 * (0.309016994374947);
            } else {
                wsv_ext0 = wsv_ext1 = wsv_ext2 = wsb;
                dw_ext0 = dw0 - 2 * (0.309016994374947);
                dw_ext1 = dw_ext2 = dw0 - 3 * (0.309016994374947);
            }
        }


        double dx4 = dx0 - 1 - 3 * (0.309016994374947);
        double dy4 = dy0 - 1 - 3 * (0.309016994374947);
        double dz4 = dz0 - 1 - 3 * (0.309016994374947);
        double dw4 = dw0 - 3 * (0.309016994374947);
        double attn4 = 2 - dx4 * dx4 - dy4 * dy4 - dz4 * dz4 - dw4 * dw4;
        if (attn4 > 0) {
            attn4 *= attn4;
            value += attn4 * attn4 * extrapolate4(ctx, xsb + 1, ysb + 1,
                                         zsb + 1, wsb + 0, dx4, dy4, dz4, dw4);
        }


        double dx3 = dx4;
        double dy3 = dy4;
        double dz3 = dz0 - 3 * (0.309016994374947);
        double dw3 = dw0 - 1 - 3 * (0.309016994374947);
        double attn3 = 2 - dx3 * dx3 - dy3 * dy3 - dz3 * dz3 - dw3 * dw3;
        if (attn3 > 0) {
            attn3 *= attn3;
            value += attn3 * attn3 * extrapolate4(ctx, xsb + 1, ysb + 1,
                                         zsb + 0, wsb + 1, dx3, dy3, dz3, dw3);
        }


        double dx2 = dx4;
        double dy2 = dy0 - 3 * (0.309016994374947);
        double dz2 = dz4;
        double dw2 = dw3;
        double attn2 = 2 - dx2 * dx2 - dy2 * dy2 - dz2 * dz2 - dw2 * dw2;
        if (attn2 > 0) {
            attn2 *= attn2;
            value += attn2 * attn2 * extrapolate4(ctx, xsb + 1, ysb + 0,
                                         zsb + 1, wsb + 1, dx2, dy2, dz2, dw2);
        }


        double dx1 = dx0 - 3 * (0.309016994374947);
        double dz1 = dz4;
        double dy1 = dy4;
        double dw1 = dw3;
        double attn1 = 2 - dx1 * dx1 - dy1 * dy1 - dz1 * dz1 - dw1 * dw1;
        if (attn1 > 0) {
            attn1 *= attn1;
            value += attn1 * attn1 * extrapolate4(ctx, xsb + 0, ysb + 1,
                                         zsb + 1, wsb + 1, dx1, dy1, dz1, dw1);
        }


        dx0 = dx0 - 1 - 4 * (0.309016994374947);
        dy0 = dy0 - 1 - 4 * (0.309016994374947);
        dz0 = dz0 - 1 - 4 * (0.309016994374947);
        dw0 = dw0 - 1 - 4 * (0.309016994374947);
        double attn0 = 2 - dx0 * dx0 - dy0 * dy0 - dz0 * dz0 - dw0 * dw0;
        if (attn0 > 0) {
            attn0 *= attn0;
            value += attn0 * attn0 * extrapolate4(ctx, xsb + 1, ysb + 1,
                                         zsb + 1, wsb + 1, dx0, dy0, dz0, dw0);
        }
    } else if (inSum <= 2) {

        double aScore;
        int8_t aPoint;
        int aIsBiggerSide = 1;
        double bScore;
        int8_t bPoint;
        int bIsBiggerSide = 1;


        if (xins + yins > zins + wins) {
            aScore = xins + yins;
            aPoint = 0x03;
        } else {
            aScore = zins + wins;
            aPoint = 0x0C;
        }


        if (xins + zins > yins + wins) {
            bScore = xins + zins;
            bPoint = 0x05;
        } else {
            bScore = yins + wins;
            bPoint = 0x0A;
        }



        if (xins + wins > yins + zins) {
            double score = xins + wins;
            if (aScore >= bScore && score > bScore) {
                bScore = score;
                bPoint = 0x09;
            } else if (aScore < bScore && score > aScore) {
                aScore = score;
                aPoint = 0x09;
            }
        } else {
            double score = yins + zins;
            if (aScore >= bScore && score > bScore) {
                bScore = score;
                bPoint = 0x06;
            } else if (aScore < bScore && score > aScore) {
                aScore = score;
                aPoint = 0x06;
            }
        }


        double p1 = 2 - inSum + xins;
        if (aScore >= bScore && p1 > bScore) {
            bScore = p1;
            bPoint = 0x01;
            bIsBiggerSide = 0;
        } else if (aScore < bScore && p1 > aScore) {
            aScore = p1;
            aPoint = 0x01;
            aIsBiggerSide = 0;
        }


        double p2 = 2 - inSum + yins;
        if (aScore >= bScore && p2 > bScore) {
            bScore = p2;
            bPoint = 0x02;
            bIsBiggerSide = 0;
        } else if (aScore < bScore && p2 > aScore) {
            aScore = p2;
            aPoint = 0x02;
            aIsBiggerSide = 0;
        }


        double p3 = 2 - inSum + zins;
        if (aScore >= bScore && p3 > bScore) {
            bScore = p3;
            bPoint = 0x04;
            bIsBiggerSide = 0;
        } else if (aScore < bScore && p3 > aScore) {
            aScore = p3;
            aPoint = 0x04;
            aIsBiggerSide = 0;
        }


        double p4 = 2 - inSum + wins;
        if (aScore >= bScore && p4 > bScore) {
            bScore = p4;
            bPoint = 0x08;
            bIsBiggerSide = 0;
        } else if (aScore < bScore && p4 > aScore) {
            aScore = p4;
            aPoint = 0x08;
            aIsBiggerSide = 0;
        }



        if (aIsBiggerSide == bIsBiggerSide) {
            if (aIsBiggerSide) {
                int8_t c1 = (int8_t)(aPoint | bPoint);
                int8_t c2 = (int8_t)(aPoint & bPoint);
                if ((c1 & 0x01) == 0) {
                    xsv_ext0 = xsb;
                    xsv_ext1 = xsb - 1;
                    dx_ext0 = dx0 - 3 * (0.309016994374947);
                    dx_ext1 = dx0 + 1 - 2 * (0.309016994374947);
                } else {
                    xsv_ext0 = xsv_ext1 = xsb + 1;
                    dx_ext0 = dx0 - 1 - 3 * (0.309016994374947);
                    dx_ext1 = dx0 - 1 - 2 * (0.309016994374947);
                }

                if ((c1 & 0x02) == 0) {
                    ysv_ext0 = ysb;
                    ysv_ext1 = ysb - 1;
                    dy_ext0 = dy0 - 3 * (0.309016994374947);
                    dy_ext1 = dy0 + 1 - 2 * (0.309016994374947);
                } else {
                    ysv_ext0 = ysv_ext1 = ysb + 1;
                    dy_ext0 = dy0 - 1 - 3 * (0.309016994374947);
                    dy_ext1 = dy0 - 1 - 2 * (0.309016994374947);
                }

                if ((c1 & 0x04) == 0) {
                    zsv_ext0 = zsb;
                    zsv_ext1 = zsb - 1;
                    dz_ext0 = dz0 - 3 * (0.309016994374947);
                    dz_ext1 = dz0 + 1 - 2 * (0.309016994374947);
                } else {
                    zsv_ext0 = zsv_ext1 = zsb + 1;
                    dz_ext0 = dz0 - 1 - 3 * (0.309016994374947);
                    dz_ext1 = dz0 - 1 - 2 * (0.309016994374947);
                }

                if ((c1 & 0x08) == 0) {
                    wsv_ext0 = wsb;
                    wsv_ext1 = wsb - 1;
                    dw_ext0 = dw0 - 3 * (0.309016994374947);
                    dw_ext1 = dw0 + 1 - 2 * (0.309016994374947);
                } else {
                    wsv_ext0 = wsv_ext1 = wsb + 1;
                    dw_ext0 = dw0 - 1 - 3 * (0.309016994374947);
                    dw_ext1 = dw0 - 1 - 2 * (0.309016994374947);
                }


                xsv_ext2 = xsb;
                ysv_ext2 = ysb;
                zsv_ext2 = zsb;
                wsv_ext2 = wsb;
                dx_ext2 = dx0 - 2 * (0.309016994374947);
                dy_ext2 = dy0 - 2 * (0.309016994374947);
                dz_ext2 = dz0 - 2 * (0.309016994374947);
                dw_ext2 = dw0 - 2 * (0.309016994374947);
                if ((c2 & 0x01) != 0) {
                    xsv_ext2 += 2;
                    dx_ext2 -= 2;
                } else if ((c2 & 0x02) != 0) {
                    ysv_ext2 += 2;
                    dy_ext2 -= 2;
                } else if ((c2 & 0x04) != 0) {
                    zsv_ext2 += 2;
                    dz_ext2 -= 2;
                } else {
                    wsv_ext2 += 2;
                    dw_ext2 -= 2;
                }

            } else {

                xsv_ext2 = xsb;
                ysv_ext2 = ysb;
                zsv_ext2 = zsb;
                wsv_ext2 = wsb;
                dx_ext2 = dx0;
                dy_ext2 = dy0;
                dz_ext2 = dz0;
                dw_ext2 = dw0;


                int8_t c = (int8_t)(aPoint | bPoint);

                if ((c & 0x01) == 0) {
                    xsv_ext0 = xsb - 1;
                    xsv_ext1 = xsb;
                    dx_ext0 = dx0 + 1 - (0.309016994374947);
                    dx_ext1 = dx0 - (0.309016994374947);
                } else {
                    xsv_ext0 = xsv_ext1 = xsb + 1;
                    dx_ext0 = dx_ext1 = dx0 - 1 - (0.309016994374947);
                }

                if ((c & 0x02) == 0) {
                    ysv_ext0 = ysv_ext1 = ysb;
                    dy_ext0 = dy_ext1 = dy0 - (0.309016994374947);
                    if ((c & 0x01) == 0x01) {
                        ysv_ext0 -= 1;
                        dy_ext0 += 1;
                    } else {
                        ysv_ext1 -= 1;
                        dy_ext1 += 1;
                    }
                } else {
                    ysv_ext0 = ysv_ext1 = ysb + 1;
                    dy_ext0 = dy_ext1 = dy0 - 1 - (0.309016994374947);
                }

                if ((c & 0x04) == 0) {
                    zsv_ext0 = zsv_ext1 = zsb;
                    dz_ext0 = dz_ext1 = dz0 - (0.309016994374947);
                    if ((c & 0x03) == 0x03) {
                        zsv_ext0 -= 1;
                        dz_ext0 += 1;
                    } else {
                        zsv_ext1 -= 1;
                        dz_ext1 += 1;
                    }
                } else {
                    zsv_ext0 = zsv_ext1 = zsb + 1;
                    dz_ext0 = dz_ext1 = dz0 - 1 - (0.309016994374947);
                }

                if ((c & 0x08) == 0) {
                    wsv_ext0 = wsb;
                    wsv_ext1 = wsb - 1;
                    dw_ext0 = dw0 - (0.309016994374947);
                    dw_ext1 = dw0 + 1 - (0.309016994374947);
                } else {
                    wsv_ext0 = wsv_ext1 = wsb + 1;
                    dw_ext0 = dw_ext1 = dw0 - 1 - (0.309016994374947);
                }
            }
        } else {
            int8_t c1, c2;
            if (aIsBiggerSide) {
                c1 = aPoint;
                c2 = bPoint;
            } else {
                c1 = bPoint;
                c2 = aPoint;
            }



            if ((c1 & 0x01) == 0) {
                xsv_ext0 = xsb - 1;
                xsv_ext1 = xsb;
                dx_ext0 = dx0 + 1 - (0.309016994374947);
                dx_ext1 = dx0 - (0.309016994374947);
            } else {
                xsv_ext0 = xsv_ext1 = xsb + 1;
                dx_ext0 = dx_ext1 = dx0 - 1 - (0.309016994374947);
            }

            if ((c1 & 0x02) == 0) {
                ysv_ext0 = ysv_ext1 = ysb;
                dy_ext0 = dy_ext1 = dy0 - (0.309016994374947);
                if ((c1 & 0x01) == 0x01) {
                    ysv_ext0 -= 1;
                    dy_ext0 += 1;
                } else {
                    ysv_ext1 -= 1;
                    dy_ext1 += 1;
                }
            } else {
                ysv_ext0 = ysv_ext1 = ysb + 1;
                dy_ext0 = dy_ext1 = dy0 - 1 - (0.309016994374947);
            }

            if ((c1 & 0x04) == 0) {
                zsv_ext0 = zsv_ext1 = zsb;
                dz_ext0 = dz_ext1 = dz0 - (0.309016994374947);
                if ((c1 & 0x03) == 0x03) {
                    zsv_ext0 -= 1;
                    dz_ext0 += 1;
                } else {
                    zsv_ext1 -= 1;
                    dz_ext1 += 1;
                }
            } else {
                zsv_ext0 = zsv_ext1 = zsb + 1;
                dz_ext0 = dz_ext1 = dz0 - 1 - (0.309016994374947);
            }

            if ((c1 & 0x08) == 0) {
                wsv_ext0 = wsb;
                wsv_ext1 = wsb - 1;
                dw_ext0 = dw0 - (0.309016994374947);
                dw_ext1 = dw0 + 1 - (0.309016994374947);
            } else {
                wsv_ext0 = wsv_ext1 = wsb + 1;
                dw_ext0 = dw_ext1 = dw0 - 1 - (0.309016994374947);
            }



            xsv_ext2 = xsb;
            ysv_ext2 = ysb;
            zsv_ext2 = zsb;
            wsv_ext2 = wsb;
            dx_ext2 = dx0 - 2 * (0.309016994374947);
            dy_ext2 = dy0 - 2 * (0.309016994374947);
            dz_ext2 = dz0 - 2 * (0.309016994374947);
            dw_ext2 = dw0 - 2 * (0.309016994374947);
            if ((c2 & 0x01) != 0) {
                xsv_ext2 += 2;
                dx_ext2 -= 2;
            } else if ((c2 & 0x02) != 0) {
                ysv_ext2 += 2;
                dy_ext2 -= 2;
            } else if ((c2 & 0x04) != 0) {
                zsv_ext2 += 2;
                dz_ext2 -= 2;
            } else {
                wsv_ext2 += 2;
                dw_ext2 -= 2;
            }
        }


        double dx1 = dx0 - 1 - (0.309016994374947);
        double dy1 = dy0 - 0 - (0.309016994374947);
        double dz1 = dz0 - 0 - (0.309016994374947);
        double dw1 = dw0 - 0 - (0.309016994374947);
        double attn1 = 2 - dx1 * dx1 - dy1 * dy1 - dz1 * dz1 - dw1 * dw1;
        if (attn1 > 0) {
            attn1 *= attn1;
            value += attn1 * attn1 * extrapolate4(ctx, xsb + 1, ysb + 0,
                                         zsb + 0, wsb + 0, dx1, dy1, dz1, dw1);
        }


        double dx2 = dx0 - 0 - (0.309016994374947);
        double dy2 = dy0 - 1 - (0.309016994374947);
        double dz2 = dz1;
        double dw2 = dw1;
        double attn2 = 2 - dx2 * dx2 - dy2 * dy2 - dz2 * dz2 - dw2 * dw2;
        if (attn2 > 0) {
            attn2 *= attn2;
            value += attn2 * attn2 * extrapolate4(ctx, xsb + 0, ysb + 1,
                                         zsb + 0, wsb + 0, dx2, dy2, dz2, dw2);
        }


        double dx3 = dx2;
        double dy3 = dy1;
        double dz3 = dz0 - 1 - (0.309016994374947);
        double dw3 = dw1;
        double attn3 = 2 - dx3 * dx3 - dy3 * dy3 - dz3 * dz3 - dw3 * dw3;
        if (attn3 > 0) {
            attn3 *= attn3;
            value += attn3 * attn3 * extrapolate4(ctx, xsb + 0, ysb + 0,
                                         zsb + 1, wsb + 0, dx3, dy3, dz3, dw3);
        }


        double dx4 = dx2;
        double dy4 = dy1;
        double dz4 = dz1;
        double dw4 = dw0 - 1 - (0.309016994374947);
        double attn4 = 2 - dx4 * dx4 - dy4 * dy4 - dz4 * dz4 - dw4 * dw4;
        if (attn4 > 0) {
            attn4 *= attn4;
            value += attn4 * attn4 * extrapolate4(ctx, xsb + 0, ysb + 0,
                                         zsb + 0, wsb + 1, dx4, dy4, dz4, dw4);
        }


        double dx5 = dx0 - 1 - 2 * (0.309016994374947);
        double dy5 = dy0 - 1 - 2 * (0.309016994374947);
        double dz5 = dz0 - 0 - 2 * (0.309016994374947);
        double dw5 = dw0 - 0 - 2 * (0.309016994374947);
        double attn5 = 2 - dx5 * dx5 - dy5 * dy5 - dz5 * dz5 - dw5 * dw5;
        if (attn5 > 0) {
            attn5 *= attn5;
            value += attn5 * attn5 * extrapolate4(ctx, xsb + 1, ysb + 1,
                                         zsb + 0, wsb + 0, dx5, dy5, dz5, dw5);
        }


        double dx6 = dx0 - 1 - 2 * (0.309016994374947);
        double dy6 = dy0 - 0 - 2 * (0.309016994374947);
        double dz6 = dz0 - 1 - 2 * (0.309016994374947);
        double dw6 = dw0 - 0 - 2 * (0.309016994374947);
        double attn6 = 2 - dx6 * dx6 - dy6 * dy6 - dz6 * dz6 - dw6 * dw6;
        if (attn6 > 0) {
            attn6 *= attn6;
            value += attn6 * attn6 * extrapolate4(ctx, xsb + 1, ysb + 0,
                                         zsb + 1, wsb + 0, dx6, dy6, dz6, dw6);
        }


        double dx7 = dx0 - 1 - 2 * (0.309016994374947);
        double dy7 = dy0 - 0 - 2 * (0.309016994374947);
        double dz7 = dz0 - 0 - 2 * (0.309016994374947);
        double dw7 = dw0 - 1 - 2 * (0.309016994374947);
        double attn7 = 2 - dx7 * dx7 - dy7 * dy7 - dz7 * dz7 - dw7 * dw7;
        if (attn7 > 0) {
            attn7 *= attn7;
            value += attn7 * attn7 * extrapolate4(ctx, xsb + 1, ysb + 0,
                                         zsb + 0, wsb + 1, dx7, dy7, dz7, dw7);
        }


        double dx8 = dx0 - 0 - 2 * (0.309016994374947);
        double dy8 = dy0 - 1 - 2 * (0.309016994374947);
        double dz8 = dz0 - 1 - 2 * (0.309016994374947);
        double dw8 = dw0 - 0 - 2 * (0.309016994374947);
        double attn8 = 2 - dx8 * dx8 - dy8 * dy8 - dz8 * dz8 - dw8 * dw8;
        if (attn8 > 0) {
            attn8 *= attn8;
            value += attn8 * attn8 * extrapolate4(ctx, xsb + 0, ysb + 1,
                                         zsb + 1, wsb + 0, dx8, dy8, dz8, dw8);
        }


        double dx9 = dx0 - 0 - 2 * (0.309016994374947);
        double dy9 = dy0 - 1 - 2 * (0.309016994374947);
        double dz9 = dz0 - 0 - 2 * (0.309016994374947);
        double dw9 = dw0 - 1 - 2 * (0.309016994374947);
        double attn9 = 2 - dx9 * dx9 - dy9 * dy9 - dz9 * dz9 - dw9 * dw9;
        if (attn9 > 0) {
            attn9 *= attn9;
            value += attn9 * attn9 * extrapolate4(ctx, xsb + 0, ysb + 1,
                                         zsb + 0, wsb + 1, dx9, dy9, dz9, dw9);
        }


        double dx10 = dx0 - 0 - 2 * (0.309016994374947);
        double dy10 = dy0 - 0 - 2 * (0.309016994374947);
        double dz10 = dz0 - 1 - 2 * (0.309016994374947);
        double dw10 = dw0 - 1 - 2 * (0.309016994374947);
        double attn10 =
            2 - dx10 * dx10 - dy10 * dy10 - dz10 * dz10 - dw10 * dw10;
        if (attn10 > 0) {
            attn10 *= attn10;
            value +=
                attn10 * attn10 * extrapolate4(ctx, xsb + 0, ysb + 0, zsb + 1,
                                      wsb + 1, dx10, dy10, dz10, dw10);
        }
    } else {
        double aScore;
        int8_t aPoint;
        int aIsBiggerSide = 1;
        double bScore;
        int8_t bPoint;
        int bIsBiggerSide = 1;


        if (xins + yins < zins + wins) {
            aScore = xins + yins;
            aPoint = 0x0C;
        } else {
            aScore = zins + wins;
            aPoint = 0x03;
        }


        if (xins + zins < yins + wins) {
            bScore = xins + zins;
            bPoint = 0x0A;
        } else {
            bScore = yins + wins;
            bPoint = 0x05;
        }



        if (xins + wins < yins + zins) {
            double score = xins + wins;
            if (aScore <= bScore && score < bScore) {
                bScore = score;
                bPoint = 0x06;
            } else if (aScore > bScore && score < aScore) {
                aScore = score;
                aPoint = 0x06;
            }
        } else {
            double score = yins + zins;
            if (aScore <= bScore && score < bScore) {
                bScore = score;
                bPoint = 0x09;
            } else if (aScore > bScore && score < aScore) {
                aScore = score;
                aPoint = 0x09;
            }
        }


        double p1 = 3 - inSum + xins;
        if (aScore <= bScore && p1 < bScore) {
            bScore = p1;
            bPoint = 0x0E;
            bIsBiggerSide = 0;
        } else if (aScore > bScore && p1 < aScore) {
            aScore = p1;
            aPoint = 0x0E;
            aIsBiggerSide = 0;
        }


        double p2 = 3 - inSum + yins;
        if (aScore <= bScore && p2 < bScore) {
            bScore = p2;
            bPoint = 0x0D;
            bIsBiggerSide = 0;
        } else if (aScore > bScore && p2 < aScore) {
            aScore = p2;
            aPoint = 0x0D;
            aIsBiggerSide = 0;
        }


        double p3 = 3 - inSum + zins;
        if (aScore <= bScore && p3 < bScore) {
            bScore = p3;
            bPoint = 0x0B;
            bIsBiggerSide = 0;
        } else if (aScore > bScore && p3 < aScore) {
            aScore = p3;
            aPoint = 0x0B;
            aIsBiggerSide = 0;
        }


        double p4 = 3 - inSum + wins;
        if (aScore <= bScore && p4 < bScore) {
            bScore = p4;
            bPoint = 0x07;
            bIsBiggerSide = 0;
        } else if (aScore > bScore && p4 < aScore) {
            aScore = p4;
            aPoint = 0x07;
            aIsBiggerSide = 0;
        }



        if (aIsBiggerSide == bIsBiggerSide) {
            if (aIsBiggerSide) {
                int8_t c1 = (int8_t)(aPoint & bPoint);
                int8_t c2 = (int8_t)(aPoint | bPoint);



                xsv_ext0 = xsv_ext1 = xsb;
                ysv_ext0 = ysv_ext1 = ysb;
                zsv_ext0 = zsv_ext1 = zsb;
                wsv_ext0 = wsv_ext1 = wsb;
                dx_ext0 = dx0 - (0.309016994374947);
                dy_ext0 = dy0 - (0.309016994374947);
                dz_ext0 = dz0 - (0.309016994374947);
                dw_ext0 = dw0 - (0.309016994374947);
                dx_ext1 = dx0 - 2 * (0.309016994374947);
                dy_ext1 = dy0 - 2 * (0.309016994374947);
                dz_ext1 = dz0 - 2 * (0.309016994374947);
                dw_ext1 = dw0 - 2 * (0.309016994374947);
                if ((c1 & 0x01) != 0) {
                    xsv_ext0 += 1;
                    dx_ext0 -= 1;
                    xsv_ext1 += 2;
                    dx_ext1 -= 2;
                } else if ((c1 & 0x02) != 0) {
                    ysv_ext0 += 1;
                    dy_ext0 -= 1;
                    ysv_ext1 += 2;
                    dy_ext1 -= 2;
                } else if ((c1 & 0x04) != 0) {
                    zsv_ext0 += 1;
                    dz_ext0 -= 1;
                    zsv_ext1 += 2;
                    dz_ext1 -= 2;
                } else {
                    wsv_ext0 += 1;
                    dw_ext0 -= 1;
                    wsv_ext1 += 2;
                    dw_ext1 -= 2;
                }


                xsv_ext2 = xsb + 1;
                ysv_ext2 = ysb + 1;
                zsv_ext2 = zsb + 1;
                wsv_ext2 = wsb + 1;
                dx_ext2 = dx0 - 1 - 2 * (0.309016994374947);
                dy_ext2 = dy0 - 1 - 2 * (0.309016994374947);
                dz_ext2 = dz0 - 1 - 2 * (0.309016994374947);
                dw_ext2 = dw0 - 1 - 2 * (0.309016994374947);
                if ((c2 & 0x01) == 0) {
                    xsv_ext2 -= 2;
                    dx_ext2 += 2;
                } else if ((c2 & 0x02) == 0) {
                    ysv_ext2 -= 2;
                    dy_ext2 += 2;
                } else if ((c2 & 0x04) == 0) {
                    zsv_ext2 -= 2;
                    dz_ext2 += 2;
                } else {
                    wsv_ext2 -= 2;
                    dw_ext2 += 2;
                }
            } else {

                xsv_ext2 = xsb + 1;
                ysv_ext2 = ysb + 1;
                zsv_ext2 = zsb + 1;
                wsv_ext2 = wsb + 1;
                dx_ext2 = dx0 - 1 - 4 * (0.309016994374947);
                dy_ext2 = dy0 - 1 - 4 * (0.309016994374947);
                dz_ext2 = dz0 - 1 - 4 * (0.309016994374947);
                dw_ext2 = dw0 - 1 - 4 * (0.309016994374947);


                int8_t c = (int8_t)(aPoint & bPoint);

                if ((c & 0x01) != 0) {
                    xsv_ext0 = xsb + 2;
                    xsv_ext1 = xsb + 1;
                    dx_ext0 = dx0 - 2 - 3 * (0.309016994374947);
                    dx_ext1 = dx0 - 1 - 3 * (0.309016994374947);
                } else {
                    xsv_ext0 = xsv_ext1 = xsb;
                    dx_ext0 = dx_ext1 = dx0 - 3 * (0.309016994374947);
                }

                if ((c & 0x02) != 0) {
                    ysv_ext0 = ysv_ext1 = ysb + 1;
                    dy_ext0 = dy_ext1 = dy0 - 1 - 3 * (0.309016994374947);
                    if ((c & 0x01) == 0) {
                        ysv_ext0 += 1;
                        dy_ext0 -= 1;
                    } else {
                        ysv_ext1 += 1;
                        dy_ext1 -= 1;
                    }
                } else {
                    ysv_ext0 = ysv_ext1 = ysb;
                    dy_ext0 = dy_ext1 = dy0 - 3 * (0.309016994374947);
                }

                if ((c & 0x04) != 0) {
                    zsv_ext0 = zsv_ext1 = zsb + 1;
                    dz_ext0 = dz_ext1 = dz0 - 1 - 3 * (0.309016994374947);
                    if ((c & 0x03) == 0) {
                        zsv_ext0 += 1;
                        dz_ext0 -= 1;
                    } else {
                        zsv_ext1 += 1;
                        dz_ext1 -= 1;
                    }
                } else {
                    zsv_ext0 = zsv_ext1 = zsb;
                    dz_ext0 = dz_ext1 = dz0 - 3 * (0.309016994374947);
                }

                if ((c & 0x08) != 0) {
                    wsv_ext0 = wsb + 1;
                    wsv_ext1 = wsb + 2;
                    dw_ext0 = dw0 - 1 - 3 * (0.309016994374947);
                    dw_ext1 = dw0 - 2 - 3 * (0.309016994374947);
                } else {
                    wsv_ext0 = wsv_ext1 = wsb;
                    dw_ext0 = dw_ext1 = dw0 - 3 * (0.309016994374947);
                }
            }
        } else {
            int8_t c1, c2;
            if (aIsBiggerSide) {
                c1 = aPoint;
                c2 = bPoint;
            } else {
                c1 = bPoint;
                c2 = aPoint;
            }



            if ((c1 & 0x01) != 0) {
                xsv_ext0 = xsb + 2;
                xsv_ext1 = xsb + 1;
                dx_ext0 = dx0 - 2 - 3 * (0.309016994374947);
                dx_ext1 = dx0 - 1 - 3 * (0.309016994374947);
            } else {
                xsv_ext0 = xsv_ext1 = xsb;
                dx_ext0 = dx_ext1 = dx0 - 3 * (0.309016994374947);
            }

            if ((c1 & 0x02) != 0) {
                ysv_ext0 = ysv_ext1 = ysb + 1;
                dy_ext0 = dy_ext1 = dy0 - 1 - 3 * (0.309016994374947);
                if ((c1 & 0x01) == 0) {
                    ysv_ext0 += 1;
                    dy_ext0 -= 1;
                } else {
                    ysv_ext1 += 1;
                    dy_ext1 -= 1;
                }
            } else {
                ysv_ext0 = ysv_ext1 = ysb;
                dy_ext0 = dy_ext1 = dy0 - 3 * (0.309016994374947);
            }

            if ((c1 & 0x04) != 0) {
                zsv_ext0 = zsv_ext1 = zsb + 1;
                dz_ext0 = dz_ext1 = dz0 - 1 - 3 * (0.309016994374947);
                if ((c1 & 0x03) == 0) {
                    zsv_ext0 += 1;
                    dz_ext0 -= 1;
                } else {
                    zsv_ext1 += 1;
                    dz_ext1 -= 1;
                }
            } else {
                zsv_ext0 = zsv_ext1 = zsb;
                dz_ext0 = dz_ext1 = dz0 - 3 * (0.309016994374947);
            }

            if ((c1 & 0x08) != 0) {
                wsv_ext0 = wsb + 1;
                wsv_ext1 = wsb + 2;
                dw_ext0 = dw0 - 1 - 3 * (0.309016994374947);
                dw_ext1 = dw0 - 2 - 3 * (0.309016994374947);
            } else {
                wsv_ext0 = wsv_ext1 = wsb;
                dw_ext0 = dw_ext1 = dw0 - 3 * (0.309016994374947);
            }



            xsv_ext2 = xsb + 1;
            ysv_ext2 = ysb + 1;
            zsv_ext2 = zsb + 1;
            wsv_ext2 = wsb + 1;
            dx_ext2 = dx0 - 1 - 2 * (0.309016994374947);
            dy_ext2 = dy0 - 1 - 2 * (0.309016994374947);
            dz_ext2 = dz0 - 1 - 2 * (0.309016994374947);
            dw_ext2 = dw0 - 1 - 2 * (0.309016994374947);
            if ((c2 & 0x01) == 0) {
                xsv_ext2 -= 2;
                dx_ext2 += 2;
            } else if ((c2 & 0x02) == 0) {
                ysv_ext2 -= 2;
                dy_ext2 += 2;
            } else if ((c2 & 0x04) == 0) {
                zsv_ext2 -= 2;
                dz_ext2 += 2;
            } else {
                wsv_ext2 -= 2;
                dw_ext2 += 2;
            }
        }


        double dx4 = dx0 - 1 - 3 * (0.309016994374947);
        double dy4 = dy0 - 1 - 3 * (0.309016994374947);
        double dz4 = dz0 - 1 - 3 * (0.309016994374947);
        double dw4 = dw0 - 3 * (0.309016994374947);
        double attn4 = 2 - dx4 * dx4 - dy4 * dy4 - dz4 * dz4 - dw4 * dw4;
        if (attn4 > 0) {
            attn4 *= attn4;
            value += attn4 * attn4 * extrapolate4(ctx, xsb + 1, ysb + 1,
                                         zsb + 1, wsb + 0, dx4, dy4, dz4, dw4);
        }


        double dx3 = dx4;
        double dy3 = dy4;
        double dz3 = dz0 - 3 * (0.309016994374947);
        double dw3 = dw0 - 1 - 3 * (0.309016994374947);
        double attn3 = 2 - dx3 * dx3 - dy3 * dy3 - dz3 * dz3 - dw3 * dw3;
        if (attn3 > 0) {
            attn3 *= attn3;
            value += attn3 * attn3 * extrapolate4(ctx, xsb + 1, ysb + 1,
                                         zsb + 0, wsb + 1, dx3, dy3, dz3, dw3);
        }


        double dx2 = dx4;
        double dy2 = dy0 - 3 * (0.309016994374947);
        double dz2 = dz4;
        double dw2 = dw3;
        double attn2 = 2 - dx2 * dx2 - dy2 * dy2 - dz2 * dz2 - dw2 * dw2;
        if (attn2 > 0) {
            attn2 *= attn2;
            value += attn2 * attn2 * extrapolate4(ctx, xsb + 1, ysb + 0,
                                         zsb + 1, wsb + 1, dx2, dy2, dz2, dw2);
        }


        double dx1 = dx0 - 3 * (0.309016994374947);
        double dz1 = dz4;
        double dy1 = dy4;
        double dw1 = dw3;
        double attn1 = 2 - dx1 * dx1 - dy1 * dy1 - dz1 * dz1 - dw1 * dw1;
        if (attn1 > 0) {
            attn1 *= attn1;
            value += attn1 * attn1 * extrapolate4(ctx, xsb + 0, ysb + 1,
                                         zsb + 1, wsb + 1, dx1, dy1, dz1, dw1);
        }


        double dx5 = dx0 - 1 - 2 * (0.309016994374947);
        double dy5 = dy0 - 1 - 2 * (0.309016994374947);
        double dz5 = dz0 - 0 - 2 * (0.309016994374947);
        double dw5 = dw0 - 0 - 2 * (0.309016994374947);
        double attn5 = 2 - dx5 * dx5 - dy5 * dy5 - dz5 * dz5 - dw5 * dw5;
        if (attn5 > 0) {
            attn5 *= attn5;
            value += attn5 * attn5 * extrapolate4(ctx, xsb + 1, ysb + 1,
                                         zsb + 0, wsb + 0, dx5, dy5, dz5, dw5);
        }


        double dx6 = dx0 - 1 - 2 * (0.309016994374947);
        double dy6 = dy0 - 0 - 2 * (0.309016994374947);
        double dz6 = dz0 - 1 - 2 * (0.309016994374947);
        double dw6 = dw0 - 0 - 2 * (0.309016994374947);
        double attn6 = 2 - dx6 * dx6 - dy6 * dy6 - dz6 * dz6 - dw6 * dw6;
        if (attn6 > 0) {
            attn6 *= attn6;
            value += attn6 * attn6 * extrapolate4(ctx, xsb + 1, ysb + 0,
                                         zsb + 1, wsb + 0, dx6, dy6, dz6, dw6);
        }


        double dx7 = dx0 - 1 - 2 * (0.309016994374947);
        double dy7 = dy0 - 0 - 2 * (0.309016994374947);
        double dz7 = dz0 - 0 - 2 * (0.309016994374947);
        double dw7 = dw0 - 1 - 2 * (0.309016994374947);
        double attn7 = 2 - dx7 * dx7 - dy7 * dy7 - dz7 * dz7 - dw7 * dw7;
        if (attn7 > 0) {
            attn7 *= attn7;
            value += attn7 * attn7 * extrapolate4(ctx, xsb + 1, ysb + 0,
                                         zsb + 0, wsb + 1, dx7, dy7, dz7, dw7);
        }


        double dx8 = dx0 - 0 - 2 * (0.309016994374947);
        double dy8 = dy0 - 1 - 2 * (0.309016994374947);
        double dz8 = dz0 - 1 - 2 * (0.309016994374947);
        double dw8 = dw0 - 0 - 2 * (0.309016994374947);
        double attn8 = 2 - dx8 * dx8 - dy8 * dy8 - dz8 * dz8 - dw8 * dw8;
        if (attn8 > 0) {
            attn8 *= attn8;
            value += attn8 * attn8 * extrapolate4(ctx, xsb + 0, ysb + 1,
                                         zsb + 1, wsb + 0, dx8, dy8, dz8, dw8);
        }


        double dx9 = dx0 - 0 - 2 * (0.309016994374947);
        double dy9 = dy0 - 1 - 2 * (0.309016994374947);
        double dz9 = dz0 - 0 - 2 * (0.309016994374947);
        double dw9 = dw0 - 1 - 2 * (0.309016994374947);
        double attn9 = 2 - dx9 * dx9 - dy9 * dy9 - dz9 * dz9 - dw9 * dw9;
        if (attn9 > 0) {
            attn9 *= attn9;
            value += attn9 * attn9 * extrapolate4(ctx, xsb + 0, ysb + 1,
                                         zsb + 0, wsb + 1, dx9, dy9, dz9, dw9);
        }


        double dx10 = dx0 - 0 - 2 * (0.309016994374947);
        double dy10 = dy0 - 0 - 2 * (0.309016994374947);
        double dz10 = dz0 - 1 - 2 * (0.309016994374947);
        double dw10 = dw0 - 1 - 2 * (0.309016994374947);
        double attn10 =
            2 - dx10 * dx10 - dy10 * dy10 - dz10 * dz10 - dw10 * dw10;
        if (attn10 > 0) {
            attn10 *= attn10;
            value +=
                attn10 * attn10 * extrapolate4(ctx, xsb + 0, ysb + 0, zsb + 1,
                                      wsb + 1, dx10, dy10, dz10, dw10);
        }
    }


    double attn_ext0 = 2 - dx_ext0 * dx_ext0 - dy_ext0 * dy_ext0 -
                       dz_ext0 * dz_ext0 - dw_ext0 * dw_ext0;
    if (attn_ext0 > 0) {
        attn_ext0 *= attn_ext0;
        value += attn_ext0 * attn_ext0 * extrapolate4(ctx, xsv_ext0, ysv_ext0,
                                             zsv_ext0, wsv_ext0, dx_ext0,
                                             dy_ext0, dz_ext0, dw_ext0);
    }


    double attn_ext1 = 2 - dx_ext1 * dx_ext1 - dy_ext1 * dy_ext1 -
                       dz_ext1 * dz_ext1 - dw_ext1 * dw_ext1;
    if (attn_ext1 > 0) {
        attn_ext1 *= attn_ext1;
        value += attn_ext1 * attn_ext1 * extrapolate4(ctx, xsv_ext1, ysv_ext1,
                                             zsv_ext1, wsv_ext1, dx_ext1,
                                             dy_ext1, dz_ext1, dw_ext1);
    }


    double attn_ext2 = 2 - dx_ext2 * dx_ext2 - dy_ext2 * dy_ext2 -
                       dz_ext2 * dz_ext2 - dw_ext2 * dw_ext2;
    if (attn_ext2 > 0) {
        attn_ext2 *= attn_ext2;
        value += attn_ext2 * attn_ext2 * extrapolate4(ctx, xsv_ext2, ysv_ext2,
                                             zsv_ext2, wsv_ext2, dx_ext2,
                                             dy_ext2, dz_ext2, dw_ext2);
    }

    return value / (30.0);
}
# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/noise.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/noise.c"
# 16 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/noise.c"
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
# 17 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/noise.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 18 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/noise.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 19 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/noise.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 20 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/noise.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/errno.h" 1
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/noise.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/noise.h" 1
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/noise.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/noise.h" 2

struct osn_context;

int open_simplex_noise(int64_t seed, struct osn_context** ctx);
void open_simplex_noise_free(struct osn_context* ctx);
int open_simplex_noise_init_perm(
    struct osn_context* ctx, int16_t p[], int nelements);
double open_simplex_noise2(struct osn_context* ctx, double x, double y);
double open_simplex_noise3(
    struct osn_context* ctx, double x, double y, double z);
double open_simplex_noise4(
    struct osn_context* ctx, double x, double y, double z, double w);
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/noise.c" 2
# 37 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/noise.c"
struct osn_context {
    int16_t* perm;
    int16_t* permGradIndex3D;
};







static const int8_t gradients2D[] = {
    5, 2, 2, 5, -5, 2, -2, 5, 5, -2, 2, -5, -5, -2, -2, -5,
};







static const signed char gradients3D[] = {
    -11, 4, 4, -4, 11, 4, -4, 4, 11, 11, 4, 4, 4, 11, 4, 4, 4, 11, -11, -4, 4,
    -4, -11, 4, -4, -4, 11, 11, -4, 4, 4, -11, 4, 4, -4, 11, -11, 4, -4, -4, 11,
    -4, -4, 4, -11, 11, 4, -4, 4, 11, -4, 4, 4, -11, -11, -4, -4, -4, -11, -4,
    -4, -4, -11, 11, -4, -4, 4, -11, -4, 4, -4, -11,
};







static const signed char gradients4D[] = {
    3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, 1, 1, 1, 1, 3, -3, 1, 1, 1, -1, 3, 1, 1,
    -1, 1, 3, 1, -1, 1, 1, 3, 3, -1, 1, 1, 1, -3, 1, 1, 1, -1, 3, 1, 1, -1, 1,
    3, -3, -1, 1, 1, -1, -3, 1, 1, -1, -1, 3, 1, -1, -1, 1, 3, 3, 1, -1, 1, 1,
    3, -1, 1, 1, 1, -3, 1, 1, 1, -1, 3, -3, 1, -1, 1, -1, 3, -1, 1, -1, 1, -3,
    1, -1, 1, -1, 3, 3, -1, -1, 1, 1, -3, -1, 1, 1, -1, -3, 1, 1, -1, -1, 3, -3,
    -1, -1, 1, -1, -3, -1, 1, -1, -1, -3, 1, -1, -1, -1, 3, 3, 1, 1, -1, 1, 3,
    1, -1, 1, 1, 3, -1, 1, 1, 1, -3, -3, 1, 1, -1, -1, 3, 1, -1, -1, 1, 3, -1,
    -1, 1, 1, -3, 3, -1, 1, -1, 1, -3, 1, -1, 1, -1, 3, -1, 1, -1, 1, -3, -3,
    -1, 1, -1, -1, -3, 1, -1, -1, -1, 3, -1, -1, -1, 1, -3, 3, 1, -1, -1, 1, 3,
    -1, -1, 1, 1, -3, -1, 1, 1, -1, -3, -3, 1, -1, -1, -1, 3, -1, -1, -1, 1, -3,
    -1, -1, 1, -1, -3, 3, -1, -1, -1, 1, -3, -1, -1, 1, -1, -3, -1, 1, -1, -1,
    -3, -3, -1, -1, -1, -1, -3, -1, -1, -1, -1, -3, -1, -1, -1, -1, -3,
};

static double extrapolate2(
    struct osn_context* ctx, int xsb, int ysb, double dx, double dy)
{
    int16_t* perm = ctx->perm;
    int index = perm[(perm[xsb & 0xFF] + ysb) & 0xFF] & 0x0E;
    return gradients2D[index] * dx + gradients2D[index + 1] * dy;
}

static double extrapolate3(struct osn_context* ctx, int xsb, int ysb, int zsb,
    double dx, double dy, double dz)
{
    int16_t* perm = ctx->perm;
    int16_t* permGradIndex3D = ctx->permGradIndex3D;
    int index =
        permGradIndex3D[(perm[(perm[xsb & 0xFF] + ysb) & 0xFF] + zsb) & 0xFF];
    return gradients3D[index] * dx + gradients3D[index + 1] * dy +
           gradients3D[index + 2] * dz;
}

static double extrapolate4(struct osn_context* ctx, int xsb, int ysb, int zsb,
    int wsb, double dx, double dy, double dz, double dw)
{
    int16_t* perm = ctx->perm;
    int index =
        perm[(perm[(perm[(perm[xsb & 0xFF] + ysb) & 0xFF] + zsb) & 0xFF] +
                 wsb) &
             0xFF] &
        0xFC;
    return gradients4D[index] * dx + gradients4D[index + 1] * dy +
           gradients4D[index + 2] * dz + gradients4D[index + 3] * dw;
}

static inline int fastFloor(double x)
{
    int xi = (int) x;
    return x < xi ? xi - 1 : xi;
}

static int allocate_perm(struct osn_context* ctx, int nperm, int ngrad)
{
    if (ctx->perm)
        free(ctx->perm);
    if (ctx->permGradIndex3D)
        free(ctx->permGradIndex3D);
    ctx->perm = malloc(sizeof(*ctx->perm) * nperm);
    if (!ctx->perm)
        return -ENOMEM;
    ctx->permGradIndex3D = malloc(sizeof(*ctx->permGradIndex3D) * ngrad);
    if (!ctx->permGradIndex3D) {
        free(ctx->perm);
        return -ENOMEM;
    }
    return 0;
}

int open_simplex_noise_init_perm(
    struct osn_context* ctx, int16_t p[], int nelements)
{
    int i, rc;

    rc = allocate_perm(ctx, nelements, 256);
    if (rc)
        return rc;
    memcpy(ctx->perm, p, sizeof(*ctx->perm) * nelements);

    for (i = 0; i < 256; i++) {


        ctx->permGradIndex3D[i] =
            (int16_t)((ctx->perm[i] % ((sizeof((gradients3D)) / sizeof((gradients3D)[0])) / 3)) * 3);
    }
    return 0;
}






int open_simplex_noise(int64_t seed, struct osn_context** ctx)
{
    int rc;
    int16_t source[256];
    int i;
    int16_t* perm;
    int16_t* permGradIndex3D;

    *ctx = malloc(sizeof(**ctx));
    if (!(*ctx))
        return -ENOMEM;
    (*ctx)->perm = 0;
    (*ctx)->permGradIndex3D = 0;

    rc = allocate_perm(*ctx, 256, 256);
    if (rc) {
        free(*ctx);
        return rc;
    }

    perm = (*ctx)->perm;
    permGradIndex3D = (*ctx)->permGradIndex3D;

    for (i = 0; i < 256; i++)
        source[i] = (int16_t) i;
    seed = seed * 6364136223846793005LL + 1442695040888963407LL;
    seed = seed * 6364136223846793005LL + 1442695040888963407LL;
    seed = seed * 6364136223846793005LL + 1442695040888963407LL;
    for (i = 255; i >= 0; i--) {
        seed = seed * 6364136223846793005LL + 1442695040888963407LL;
        int r = (int) ((seed + 31) % (i + 1));
        if (r < 0)
            r += (i + 1);
        perm[i] = source[r];
        permGradIndex3D[i] =
            (short) ((perm[i] % ((sizeof((gradients3D)) / sizeof((gradients3D)[0])) / 3)) * 3);
        source[r] = source[i];
    }
    return 0;
}

void open_simplex_noise_free(struct osn_context* ctx)
{
    if (!ctx)
        return;
    if (ctx->perm) {
        free(ctx->perm);
        ctx->perm = 0;
    }
    if (ctx->permGradIndex3D) {
        free(ctx->permGradIndex3D);
        ctx->permGradIndex3D = 0;
    }
    free(ctx);
}


double open_simplex_noise2(struct osn_context* ctx, double x, double y)
{

    double stretchOffset = (x + y) * (-0.211324865405187);
    double xs = x + stretchOffset;
    double ys = y + stretchOffset;



    int xsb = fastFloor(xs);
    int ysb = fastFloor(ys);



    double squishOffset = (xsb + ysb) * (0.366025403784439);
    double xb = xsb + squishOffset;
    double yb = ysb + squishOffset;


    double xins = xs - xsb;
    double yins = ys - ysb;


    double inSum = xins + yins;


    double dx0 = x - xb;
    double dy0 = y - yb;


    double dx_ext, dy_ext;
    int xsv_ext, ysv_ext;

    double value = 0;


    double dx1 = dx0 - 1 - (0.366025403784439);
    double dy1 = dy0 - 0 - (0.366025403784439);
    double attn1 = 2 - dx1 * dx1 - dy1 * dy1;
    if (attn1 > 0) {
        attn1 *= attn1;
        value += attn1 * attn1 * extrapolate2(ctx, xsb + 1, ysb + 0, dx1, dy1);
    }


    double dx2 = dx0 - 0 - (0.366025403784439);
    double dy2 = dy0 - 1 - (0.366025403784439);
    double attn2 = 2 - dx2 * dx2 - dy2 * dy2;
    if (attn2 > 0) {
        attn2 *= attn2;
        value += attn2 * attn2 * extrapolate2(ctx, xsb + 0, ysb + 1, dx2, dy2);
    }

    if (inSum <= 1) {
        double zins = 1 - inSum;
        if (zins > xins ||
            zins >
                yins) {
            if (xins > yins) {
                xsv_ext = xsb + 1;
                ysv_ext = ysb - 1;
                dx_ext = dx0 - 1;
                dy_ext = dy0 + 1;
            } else {
                xsv_ext = xsb - 1;
                ysv_ext = ysb + 1;
                dx_ext = dx0 + 1;
                dy_ext = dy0 - 1;
            }
        } else {
            xsv_ext = xsb + 1;
            ysv_ext = ysb + 1;
            dx_ext = dx0 - 1 - 2 * (0.366025403784439);
            dy_ext = dy0 - 1 - 2 * (0.366025403784439);
        }
    } else {
        double zins = 2 - inSum;
        if (zins < xins ||
            zins <
                yins) {
            if (xins > yins) {
                xsv_ext = xsb + 2;
                ysv_ext = ysb + 0;
                dx_ext = dx0 - 2 - 2 * (0.366025403784439);
                dy_ext = dy0 + 0 - 2 * (0.366025403784439);
            } else {
                xsv_ext = xsb + 0;
                ysv_ext = ysb + 2;
                dx_ext = dx0 + 0 - 2 * (0.366025403784439);
                dy_ext = dy0 - 2 - 2 * (0.366025403784439);
            }
        } else {
            dx_ext = dx0;
            dy_ext = dy0;
            xsv_ext = xsb;
            ysv_ext = ysb;
        }
        xsb += 1;
        ysb += 1;
        dx0 = dx0 - 1 - 2 * (0.366025403784439);
        dy0 = dy0 - 1 - 2 * (0.366025403784439);
    }


    double attn0 = 2 - dx0 * dx0 - dy0 * dy0;
    if (attn0 > 0) {
        attn0 *= attn0;
        value += attn0 * attn0 * extrapolate2(ctx, xsb, ysb, dx0, dy0);
    }


    double attn_ext = 2 - dx_ext * dx_ext - dy_ext * dy_ext;
    if (attn_ext > 0) {
        attn_ext *= attn_ext;
        value += attn_ext * attn_ext *
                 extrapolate2(ctx, xsv_ext, ysv_ext, dx_ext, dy_ext);
    }

    return value / (47.0);
}




double open_simplex_noise3(
    struct osn_context* ctx, double x, double y, double z)
{

    double stretchOffset = (x + y + z) * (-1.0 / 6.0);
    double xs = x + stretchOffset;
    double ys = y + stretchOffset;
    double zs = z + stretchOffset;



    int xsb = fastFloor(xs);
    int ysb = fastFloor(ys);
    int zsb = fastFloor(zs);



    double squishOffset = (xsb + ysb + zsb) * (1.0 / 3.0);
    double xb = xsb + squishOffset;
    double yb = ysb + squishOffset;
    double zb = zsb + squishOffset;


    double xins = xs - xsb;
    double yins = ys - ysb;
    double zins = zs - zsb;


    double inSum = xins + yins + zins;


    double dx0 = x - xb;
    double dy0 = y - yb;
    double dz0 = z - zb;


    double dx_ext0, dy_ext0, dz_ext0;
    double dx_ext1, dy_ext1, dz_ext1;
    int xsv_ext0, ysv_ext0, zsv_ext0;
    int xsv_ext1, ysv_ext1, zsv_ext1;

    double value = 0;
    if (inSum <= 1) {


        int8_t aPoint = 0x01;
        double aScore = xins;
        int8_t bPoint = 0x02;
        double bScore = yins;
        if (aScore >= bScore && zins > bScore) {
            bScore = zins;
            bPoint = 0x04;
        } else if (aScore < bScore && zins > aScore) {
            aScore = zins;
            aPoint = 0x04;
        }





        double wins = 1 - inSum;
        if (wins > aScore || wins > bScore) {

            int8_t c = (bScore > aScore ? bPoint : aPoint);




            if ((c & 0x01) == 0) {
                xsv_ext0 = xsb - 1;
                xsv_ext1 = xsb;
                dx_ext0 = dx0 + 1;
                dx_ext1 = dx0;
            } else {
                xsv_ext0 = xsv_ext1 = xsb + 1;
                dx_ext0 = dx_ext1 = dx0 - 1;
            }

            if ((c & 0x02) == 0) {
                ysv_ext0 = ysv_ext1 = ysb;
                dy_ext0 = dy_ext1 = dy0;
                if ((c & 0x01) == 0) {
                    ysv_ext1 -= 1;
                    dy_ext1 += 1;
                } else {
                    ysv_ext0 -= 1;
                    dy_ext0 += 1;
                }
            } else {
                ysv_ext0 = ysv_ext1 = ysb + 1;
                dy_ext0 = dy_ext1 = dy0 - 1;
            }

            if ((c & 0x04) == 0) {
                zsv_ext0 = zsb;
                zsv_ext1 = zsb - 1;
                dz_ext0 = dz0;
                dz_ext1 = dz0 + 1;
            } else {
                zsv_ext0 = zsv_ext1 = zsb + 1;
                dz_ext0 = dz_ext1 = dz0 - 1;
            }
        } else {
            int8_t c = (int8_t)(aPoint | bPoint);



            if ((c & 0x01) == 0) {
                xsv_ext0 = xsb;
                xsv_ext1 = xsb - 1;
                dx_ext0 = dx0 - 2 * (1.0 / 3.0);
                dx_ext1 = dx0 + 1 - (1.0 / 3.0);
            } else {
                xsv_ext0 = xsv_ext1 = xsb + 1;
                dx_ext0 = dx0 - 1 - 2 * (1.0 / 3.0);
                dx_ext1 = dx0 - 1 - (1.0 / 3.0);
            }

            if ((c & 0x02) == 0) {
                ysv_ext0 = ysb;
                ysv_ext1 = ysb - 1;
                dy_ext0 = dy0 - 2 * (1.0 / 3.0);
                dy_ext1 = dy0 + 1 - (1.0 / 3.0);
            } else {
                ysv_ext0 = ysv_ext1 = ysb + 1;
                dy_ext0 = dy0 - 1 - 2 * (1.0 / 3.0);
                dy_ext1 = dy0 - 1 - (1.0 / 3.0);
            }

            if ((c & 0x04) == 0) {
                zsv_ext0 = zsb;
                zsv_ext1 = zsb - 1;
                dz_ext0 = dz0 - 2 * (1.0 / 3.0);
                dz_ext1 = dz0 + 1 - (1.0 / 3.0);
            } else {
                zsv_ext0 = zsv_ext1 = zsb + 1;
                dz_ext0 = dz0 - 1 - 2 * (1.0 / 3.0);
                dz_ext1 = dz0 - 1 - (1.0 / 3.0);
            }
        }


        double attn0 = 2 - dx0 * dx0 - dy0 * dy0 - dz0 * dz0;
        if (attn0 > 0) {
            attn0 *= attn0;
            value += attn0 * attn0 * extrapolate3(ctx, xsb + 0, ysb + 0,
                                         zsb + 0, dx0, dy0, dz0);
        }


        double dx1 = dx0 - 1 - (1.0 / 3.0);
        double dy1 = dy0 - 0 - (1.0 / 3.0);
        double dz1 = dz0 - 0 - (1.0 / 3.0);
        double attn1 = 2 - dx1 * dx1 - dy1 * dy1 - dz1 * dz1;
        if (attn1 > 0) {
            attn1 *= attn1;
            value += attn1 * attn1 * extrapolate3(ctx, xsb + 1, ysb + 0,
                                         zsb + 0, dx1, dy1, dz1);
        }


        double dx2 = dx0 - 0 - (1.0 / 3.0);
        double dy2 = dy0 - 1 - (1.0 / 3.0);
        double dz2 = dz1;
        double attn2 = 2 - dx2 * dx2 - dy2 * dy2 - dz2 * dz2;
        if (attn2 > 0) {
            attn2 *= attn2;
            value += attn2 * attn2 * extrapolate3(ctx, xsb + 0, ysb + 1,
                                         zsb + 0, dx2, dy2, dz2);
        }


        double dx3 = dx2;
        double dy3 = dy1;
        double dz3 = dz0 - 1 - (1.0 / 3.0);
        double attn3 = 2 - dx3 * dx3 - dy3 * dy3 - dz3 * dz3;
        if (attn3 > 0) {
            attn3 *= attn3;
            value += attn3 * attn3 * extrapolate3(ctx, xsb + 0, ysb + 0,
                                         zsb + 1, dx3, dy3, dz3);
        }
    } else if (inSum >=
               2) {



        int8_t aPoint = 0x06;
        double aScore = xins;
        int8_t bPoint = 0x05;
        double bScore = yins;
        if (aScore <= bScore && zins < bScore) {
            bScore = zins;
            bPoint = 0x03;
        } else if (aScore > bScore && zins < aScore) {
            aScore = zins;
            aPoint = 0x03;
        }





        double wins = 3 - inSum;
        if (wins < aScore || wins < bScore) {

            int8_t c = (bScore < aScore ? bPoint : aPoint);




            if ((c & 0x01) != 0) {
                xsv_ext0 = xsb + 2;
                xsv_ext1 = xsb + 1;
                dx_ext0 = dx0 - 2 - 3 * (1.0 / 3.0);
                dx_ext1 = dx0 - 1 - 3 * (1.0 / 3.0);
            } else {
                xsv_ext0 = xsv_ext1 = xsb;
                dx_ext0 = dx_ext1 = dx0 - 3 * (1.0 / 3.0);
            }

            if ((c & 0x02) != 0) {
                ysv_ext0 = ysv_ext1 = ysb + 1;
                dy_ext0 = dy_ext1 = dy0 - 1 - 3 * (1.0 / 3.0);
                if ((c & 0x01) != 0) {
                    ysv_ext1 += 1;
                    dy_ext1 -= 1;
                } else {
                    ysv_ext0 += 1;
                    dy_ext0 -= 1;
                }
            } else {
                ysv_ext0 = ysv_ext1 = ysb;
                dy_ext0 = dy_ext1 = dy0 - 3 * (1.0 / 3.0);
            }

            if ((c & 0x04) != 0) {
                zsv_ext0 = zsb + 1;
                zsv_ext1 = zsb + 2;
                dz_ext0 = dz0 - 1 - 3 * (1.0 / 3.0);
                dz_ext1 = dz0 - 2 - 3 * (1.0 / 3.0);
            } else {
                zsv_ext0 = zsv_ext1 = zsb;
                dz_ext0 = dz_ext1 = dz0 - 3 * (1.0 / 3.0);
            }
        } else {
            int8_t c = (int8_t)(aPoint & bPoint);



            if ((c & 0x01) != 0) {
                xsv_ext0 = xsb + 1;
                xsv_ext1 = xsb + 2;
                dx_ext0 = dx0 - 1 - (1.0 / 3.0);
                dx_ext1 = dx0 - 2 - 2 * (1.0 / 3.0);
            } else {
                xsv_ext0 = xsv_ext1 = xsb;
                dx_ext0 = dx0 - (1.0 / 3.0);
                dx_ext1 = dx0 - 2 * (1.0 / 3.0);
            }

            if ((c & 0x02) != 0) {
                ysv_ext0 = ysb + 1;
                ysv_ext1 = ysb + 2;
                dy_ext0 = dy0 - 1 - (1.0 / 3.0);
                dy_ext1 = dy0 - 2 - 2 * (1.0 / 3.0);
            } else {
                ysv_ext0 = ysv_ext1 = ysb;
                dy_ext0 = dy0 - (1.0 / 3.0);
                dy_ext1 = dy0 - 2 * (1.0 / 3.0);
            }

            if ((c & 0x04) != 0) {
                zsv_ext0 = zsb + 1;
                zsv_ext1 = zsb + 2;
                dz_ext0 = dz0 - 1 - (1.0 / 3.0);
                dz_ext1 = dz0 - 2 - 2 * (1.0 / 3.0);
            } else {
                zsv_ext0 = zsv_ext1 = zsb;
                dz_ext0 = dz0 - (1.0 / 3.0);
                dz_ext1 = dz0 - 2 * (1.0 / 3.0);
            }
        }


        double dx3 = dx0 - 1 - 2 * (1.0 / 3.0);
        double dy3 = dy0 - 1 - 2 * (1.0 / 3.0);
        double dz3 = dz0 - 0 - 2 * (1.0 / 3.0);
        double attn3 = 2 - dx3 * dx3 - dy3 * dy3 - dz3 * dz3;
        if (attn3 > 0) {
            attn3 *= attn3;
            value += attn3 * attn3 * extrapolate3(ctx, xsb + 1, ysb + 1,
                                         zsb + 0, dx3, dy3, dz3);
        }


        double dx2 = dx3;
        double dy2 = dy0 - 0 - 2 * (1.0 / 3.0);
        double dz2 = dz0 - 1 - 2 * (1.0 / 3.0);
        double attn2 = 2 - dx2 * dx2 - dy2 * dy2 - dz2 * dz2;
        if (attn2 > 0) {
            attn2 *= attn2;
            value += attn2 * attn2 * extrapolate3(ctx, xsb + 1, ysb + 0,
                                         zsb + 1, dx2, dy2, dz2);
        }


        double dx1 = dx0 - 0 - 2 * (1.0 / 3.0);
        double dy1 = dy3;
        double dz1 = dz2;
        double attn1 = 2 - dx1 * dx1 - dy1 * dy1 - dz1 * dz1;
        if (attn1 > 0) {
            attn1 *= attn1;
            value += attn1 * attn1 * extrapolate3(ctx, xsb + 0, ysb + 1,
                                         zsb + 1, dx1, dy1, dz1);
        }


        dx0 = dx0 - 1 - 3 * (1.0 / 3.0);
        dy0 = dy0 - 1 - 3 * (1.0 / 3.0);
        dz0 = dz0 - 1 - 3 * (1.0 / 3.0);
        double attn0 = 2 - dx0 * dx0 - dy0 * dy0 - dz0 * dz0;
        if (attn0 > 0) {
            attn0 *= attn0;
            value += attn0 * attn0 * extrapolate3(ctx, xsb + 1, ysb + 1,
                                         zsb + 1, dx0, dy0, dz0);
        }
    } else {
        double aScore;
        int8_t aPoint;
        int aIsFurtherSide;
        double bScore;
        int8_t bPoint;
        int bIsFurtherSide;


        double p1 = xins + yins;
        if (p1 > 1) {
            aScore = p1 - 1;
            aPoint = 0x03;
            aIsFurtherSide = 1;
        } else {
            aScore = 1 - p1;
            aPoint = 0x04;
            aIsFurtherSide = 0;
        }


        double p2 = xins + zins;
        if (p2 > 1) {
            bScore = p2 - 1;
            bPoint = 0x05;
            bIsFurtherSide = 1;
        } else {
            bScore = 1 - p2;
            bPoint = 0x02;
            bIsFurtherSide = 0;
        }



        double p3 = yins + zins;
        if (p3 > 1) {
            double score = p3 - 1;
            if (aScore <= bScore && aScore < score) {
                aScore = score;
                aPoint = 0x06;
                aIsFurtherSide = 1;
            } else if (aScore > bScore && bScore < score) {
                bScore = score;
                bPoint = 0x06;
                bIsFurtherSide = 1;
            }
        } else {
            double score = 1 - p3;
            if (aScore <= bScore && aScore < score) {
                aScore = score;
                aPoint = 0x01;
                aIsFurtherSide = 0;
            } else if (aScore > bScore && bScore < score) {
                bScore = score;
                bPoint = 0x01;
                bIsFurtherSide = 0;
            }
        }



        if (aIsFurtherSide == bIsFurtherSide) {
            if (aIsFurtherSide) {


                dx_ext0 = dx0 - 1 - 3 * (1.0 / 3.0);
                dy_ext0 = dy0 - 1 - 3 * (1.0 / 3.0);
                dz_ext0 = dz0 - 1 - 3 * (1.0 / 3.0);
                xsv_ext0 = xsb + 1;
                ysv_ext0 = ysb + 1;
                zsv_ext0 = zsb + 1;


                int8_t c = (int8_t)(aPoint & bPoint);
                if ((c & 0x01) != 0) {
                    dx_ext1 = dx0 - 2 - 2 * (1.0 / 3.0);
                    dy_ext1 = dy0 - 2 * (1.0 / 3.0);
                    dz_ext1 = dz0 - 2 * (1.0 / 3.0);
                    xsv_ext1 = xsb + 2;
                    ysv_ext1 = ysb;
                    zsv_ext1 = zsb;
                } else if ((c & 0x02) != 0) {
                    dx_ext1 = dx0 - 2 * (1.0 / 3.0);
                    dy_ext1 = dy0 - 2 - 2 * (1.0 / 3.0);
                    dz_ext1 = dz0 - 2 * (1.0 / 3.0);
                    xsv_ext1 = xsb;
                    ysv_ext1 = ysb + 2;
                    zsv_ext1 = zsb;
                } else {
                    dx_ext1 = dx0 - 2 * (1.0 / 3.0);
                    dy_ext1 = dy0 - 2 * (1.0 / 3.0);
                    dz_ext1 = dz0 - 2 - 2 * (1.0 / 3.0);
                    xsv_ext1 = xsb;
                    ysv_ext1 = ysb;
                    zsv_ext1 = zsb + 2;
                }
            } else {


                dx_ext0 = dx0;
                dy_ext0 = dy0;
                dz_ext0 = dz0;
                xsv_ext0 = xsb;
                ysv_ext0 = ysb;
                zsv_ext0 = zsb;


                int8_t c = (int8_t)(aPoint | bPoint);
                if ((c & 0x01) == 0) {
                    dx_ext1 = dx0 + 1 - (1.0 / 3.0);
                    dy_ext1 = dy0 - 1 - (1.0 / 3.0);
                    dz_ext1 = dz0 - 1 - (1.0 / 3.0);
                    xsv_ext1 = xsb - 1;
                    ysv_ext1 = ysb + 1;
                    zsv_ext1 = zsb + 1;
                } else if ((c & 0x02) == 0) {
                    dx_ext1 = dx0 - 1 - (1.0 / 3.0);
                    dy_ext1 = dy0 + 1 - (1.0 / 3.0);
                    dz_ext1 = dz0 - 1 - (1.0 / 3.0);
                    xsv_ext1 = xsb + 1;
                    ysv_ext1 = ysb - 1;
                    zsv_ext1 = zsb + 1;
                } else {
                    dx_ext1 = dx0 - 1 - (1.0 / 3.0);
                    dy_ext1 = dy0 - 1 - (1.0 / 3.0);
                    dz_ext1 = dz0 + 1 - (1.0 / 3.0);
                    xsv_ext1 = xsb + 1;
                    ysv_ext1 = ysb + 1;
                    zsv_ext1 = zsb - 1;
                }
            }
        } else {
            int8_t c1, c2;
            if (aIsFurtherSide) {
                c1 = aPoint;
                c2 = bPoint;
            } else {
                c1 = bPoint;
                c2 = aPoint;
            }


            if ((c1 & 0x01) == 0) {
                dx_ext0 = dx0 + 1 - (1.0 / 3.0);
                dy_ext0 = dy0 - 1 - (1.0 / 3.0);
                dz_ext0 = dz0 - 1 - (1.0 / 3.0);
                xsv_ext0 = xsb - 1;
                ysv_ext0 = ysb + 1;
                zsv_ext0 = zsb + 1;
            } else if ((c1 & 0x02) == 0) {
                dx_ext0 = dx0 - 1 - (1.0 / 3.0);
                dy_ext0 = dy0 + 1 - (1.0 / 3.0);
                dz_ext0 = dz0 - 1 - (1.0 / 3.0);
                xsv_ext0 = xsb + 1;
                ysv_ext0 = ysb - 1;
                zsv_ext0 = zsb + 1;
            } else {
                dx_ext0 = dx0 - 1 - (1.0 / 3.0);
                dy_ext0 = dy0 - 1 - (1.0 / 3.0);
                dz_ext0 = dz0 + 1 - (1.0 / 3.0);
                xsv_ext0 = xsb + 1;
                ysv_ext0 = ysb + 1;
                zsv_ext0 = zsb - 1;
            }


            dx_ext1 = dx0 - 2 * (1.0 / 3.0);
            dy_ext1 = dy0 - 2 * (1.0 / 3.0);
            dz_ext1 = dz0 - 2 * (1.0 / 3.0);
            xsv_ext1 = xsb;
            ysv_ext1 = ysb;
            zsv_ext1 = zsb;
            if ((c2 & 0x01) != 0) {
                dx_ext1 -= 2;
                xsv_ext1 += 2;
            } else if ((c2 & 0x02) != 0) {
                dy_ext1 -= 2;
                ysv_ext1 += 2;
            } else {
                dz_ext1 -= 2;
                zsv_ext1 += 2;
            }
        }


        double dx1 = dx0 - 1 - (1.0 / 3.0);
        double dy1 = dy0 - 0 - (1.0 / 3.0);
        double dz1 = dz0 - 0 - (1.0 / 3.0);
        double attn1 = 2 - dx1 * dx1 - dy1 * dy1 - dz1 * dz1;
        if (attn1 > 0) {
            attn1 *= attn1;
            value += attn1 * attn1 * extrapolate3(ctx, xsb + 1, ysb + 0,
                                         zsb + 0, dx1, dy1, dz1);
        }


        double dx2 = dx0 - 0 - (1.0 / 3.0);
        double dy2 = dy0 - 1 - (1.0 / 3.0);
        double dz2 = dz1;
        double attn2 = 2 - dx2 * dx2 - dy2 * dy2 - dz2 * dz2;
        if (attn2 > 0) {
            attn2 *= attn2;
            value += attn2 * attn2 * extrapolate3(ctx, xsb + 0, ysb + 1,
                                         zsb + 0, dx2, dy2, dz2);
        }


        double dx3 = dx2;
        double dy3 = dy1;
        double dz3 = dz0 - 1 - (1.0 / 3.0);
        double attn3 = 2 - dx3 * dx3 - dy3 * dy3 - dz3 * dz3;
        if (attn3 > 0) {
            attn3 *= attn3;
            value += attn3 * attn3 * extrapolate3(ctx, xsb + 0, ysb + 0,
                                         zsb + 1, dx3, dy3, dz3);
        }


        double dx4 = dx0 - 1 - 2 * (1.0 / 3.0);
        double dy4 = dy0 - 1 - 2 * (1.0 / 3.0);
        double dz4 = dz0 - 0 - 2 * (1.0 / 3.0);
        double attn4 = 2 - dx4 * dx4 - dy4 * dy4 - dz4 * dz4;
        if (attn4 > 0) {
            attn4 *= attn4;
            value += attn4 * attn4 * extrapolate3(ctx, xsb + 1, ysb + 1,
                                         zsb + 0, dx4, dy4, dz4);
        }


        double dx5 = dx4;
        double dy5 = dy0 - 0 - 2 * (1.0 / 3.0);
        double dz5 = dz0 - 1 - 2 * (1.0 / 3.0);
        double attn5 = 2 - dx5 * dx5 - dy5 * dy5 - dz5 * dz5;
        if (attn5 > 0) {
            attn5 *= attn5;
            value += attn5 * attn5 * extrapolate3(ctx, xsb + 1, ysb + 0,
                                         zsb + 1, dx5, dy5, dz5);
        }


        double dx6 = dx0 - 0 - 2 * (1.0 / 3.0);
        double dy6 = dy4;
        double dz6 = dz5;
        double attn6 = 2 - dx6 * dx6 - dy6 * dy6 - dz6 * dz6;
        if (attn6 > 0) {
            attn6 *= attn6;
            value += attn6 * attn6 * extrapolate3(ctx, xsb + 0, ysb + 1,
                                         zsb + 1, dx6, dy6, dz6);
        }
    }


    double attn_ext0 =
        2 - dx_ext0 * dx_ext0 - dy_ext0 * dy_ext0 - dz_ext0 * dz_ext0;
    if (attn_ext0 > 0) {
        attn_ext0 *= attn_ext0;
        value +=
            attn_ext0 * attn_ext0 * extrapolate3(ctx, xsv_ext0, ysv_ext0,
                                        zsv_ext0, dx_ext0, dy_ext0, dz_ext0);
    }


    double attn_ext1 =
        2 - dx_ext1 * dx_ext1 - dy_ext1 * dy_ext1 - dz_ext1 * dz_ext1;
    if (attn_ext1 > 0) {
        attn_ext1 *= attn_ext1;
        value +=
            attn_ext1 * attn_ext1 * extrapolate3(ctx, xsv_ext1, ysv_ext1,
                                        zsv_ext1, dx_ext1, dy_ext1, dz_ext1);
    }

    return value / (103.0);
}




double open_simplex_noise4(
    struct osn_context* ctx, double x, double y, double z, double w)
{

    double stretchOffset = (x + y + z + w) * (-0.138196601125011);
    double xs = x + stretchOffset;
    double ys = y + stretchOffset;
    double zs = z + stretchOffset;
    double ws = w + stretchOffset;



    int xsb = fastFloor(xs);
    int ysb = fastFloor(ys);
    int zsb = fastFloor(zs);
    int wsb = fastFloor(ws);



    double squishOffset = (xsb + ysb + zsb + wsb) * (0.309016994374947);
    double xb = xsb + squishOffset;
    double yb = ysb + squishOffset;
    double zb = zsb + squishOffset;
    double wb = wsb + squishOffset;



    double xins = xs - xsb;
    double yins = ys - ysb;
    double zins = zs - zsb;
    double wins = ws - wsb;


    double inSum = xins + yins + zins + wins;


    double dx0 = x - xb;
    double dy0 = y - yb;
    double dz0 = z - zb;
    double dw0 = w - wb;


    double dx_ext0, dy_ext0, dz_ext0, dw_ext0;
    double dx_ext1, dy_ext1, dz_ext1, dw_ext1;
    double dx_ext2, dy_ext2, dz_ext2, dw_ext2;
    int xsv_ext0, ysv_ext0, zsv_ext0, wsv_ext0;
    int xsv_ext1, ysv_ext1, zsv_ext1, wsv_ext1;
    int xsv_ext2, ysv_ext2, zsv_ext2, wsv_ext2;

    double value = 0;
    if (inSum <= 1) {



        int8_t aPoint = 0x01;
        double aScore = xins;
        int8_t bPoint = 0x02;
        double bScore = yins;
        if (aScore >= bScore && zins > bScore) {
            bScore = zins;
            bPoint = 0x04;
        } else if (aScore < bScore && zins > aScore) {
            aScore = zins;
            aPoint = 0x04;
        }
        if (aScore >= bScore && wins > bScore) {
            bScore = wins;
            bPoint = 0x08;
        } else if (aScore < bScore && wins > aScore) {
            aScore = wins;
            aPoint = 0x08;
        }





        double uins = 1 - inSum;
        if (uins > aScore || uins > bScore) {

            int8_t c = (bScore > aScore ? bPoint : aPoint);



            if ((c & 0x01) == 0) {
                xsv_ext0 = xsb - 1;
                xsv_ext1 = xsv_ext2 = xsb;
                dx_ext0 = dx0 + 1;
                dx_ext1 = dx_ext2 = dx0;
            } else {
                xsv_ext0 = xsv_ext1 = xsv_ext2 = xsb + 1;
                dx_ext0 = dx_ext1 = dx_ext2 = dx0 - 1;
            }

            if ((c & 0x02) == 0) {
                ysv_ext0 = ysv_ext1 = ysv_ext2 = ysb;
                dy_ext0 = dy_ext1 = dy_ext2 = dy0;
                if ((c & 0x01) == 0x01) {
                    ysv_ext0 -= 1;
                    dy_ext0 += 1;
                } else {
                    ysv_ext1 -= 1;
                    dy_ext1 += 1;
                }
            } else {
                ysv_ext0 = ysv_ext1 = ysv_ext2 = ysb + 1;
                dy_ext0 = dy_ext1 = dy_ext2 = dy0 - 1;
            }

            if ((c & 0x04) == 0) {
                zsv_ext0 = zsv_ext1 = zsv_ext2 = zsb;
                dz_ext0 = dz_ext1 = dz_ext2 = dz0;
                if ((c & 0x03) != 0) {
                    if ((c & 0x03) == 0x03) {
                        zsv_ext0 -= 1;
                        dz_ext0 += 1;
                    } else {
                        zsv_ext1 -= 1;
                        dz_ext1 += 1;
                    }
                } else {
                    zsv_ext2 -= 1;
                    dz_ext2 += 1;
                }
            } else {
                zsv_ext0 = zsv_ext1 = zsv_ext2 = zsb + 1;
                dz_ext0 = dz_ext1 = dz_ext2 = dz0 - 1;
            }

            if ((c & 0x08) == 0) {
                wsv_ext0 = wsv_ext1 = wsb;
                wsv_ext2 = wsb - 1;
                dw_ext0 = dw_ext1 = dw0;
                dw_ext2 = dw0 + 1;
            } else {
                wsv_ext0 = wsv_ext1 = wsv_ext2 = wsb + 1;
                dw_ext0 = dw_ext1 = dw_ext2 = dw0 - 1;
            }
        } else {

            int8_t c = (int8_t)(aPoint | bPoint);



            if ((c & 0x01) == 0) {
                xsv_ext0 = xsv_ext2 = xsb;
                xsv_ext1 = xsb - 1;
                dx_ext0 = dx0 - 2 * (0.309016994374947);
                dx_ext1 = dx0 + 1 - (0.309016994374947);
                dx_ext2 = dx0 - (0.309016994374947);
            } else {
                xsv_ext0 = xsv_ext1 = xsv_ext2 = xsb + 1;
                dx_ext0 = dx0 - 1 - 2 * (0.309016994374947);
                dx_ext1 = dx_ext2 = dx0 - 1 - (0.309016994374947);
            }

            if ((c & 0x02) == 0) {
                ysv_ext0 = ysv_ext1 = ysv_ext2 = ysb;
                dy_ext0 = dy0 - 2 * (0.309016994374947);
                dy_ext1 = dy_ext2 = dy0 - (0.309016994374947);
                if ((c & 0x01) == 0x01) {
                    ysv_ext1 -= 1;
                    dy_ext1 += 1;
                } else {
                    ysv_ext2 -= 1;
                    dy_ext2 += 1;
                }
            } else {
                ysv_ext0 = ysv_ext1 = ysv_ext2 = ysb + 1;
                dy_ext0 = dy0 - 1 - 2 * (0.309016994374947);
                dy_ext1 = dy_ext2 = dy0 - 1 - (0.309016994374947);
            }

            if ((c & 0x04) == 0) {
                zsv_ext0 = zsv_ext1 = zsv_ext2 = zsb;
                dz_ext0 = dz0 - 2 * (0.309016994374947);
                dz_ext1 = dz_ext2 = dz0 - (0.309016994374947);
                if ((c & 0x03) == 0x03) {
                    zsv_ext1 -= 1;
                    dz_ext1 += 1;
                } else {
                    zsv_ext2 -= 1;
                    dz_ext2 += 1;
                }
            } else {
                zsv_ext0 = zsv_ext1 = zsv_ext2 = zsb + 1;
                dz_ext0 = dz0 - 1 - 2 * (0.309016994374947);
                dz_ext1 = dz_ext2 = dz0 - 1 - (0.309016994374947);
            }

            if ((c & 0x08) == 0) {
                wsv_ext0 = wsv_ext1 = wsb;
                wsv_ext2 = wsb - 1;
                dw_ext0 = dw0 - 2 * (0.309016994374947);
                dw_ext1 = dw0 - (0.309016994374947);
                dw_ext2 = dw0 + 1 - (0.309016994374947);
            } else {
                wsv_ext0 = wsv_ext1 = wsv_ext2 = wsb + 1;
                dw_ext0 = dw0 - 1 - 2 * (0.309016994374947);
                dw_ext1 = dw_ext2 = dw0 - 1 - (0.309016994374947);
            }
        }


        double attn0 = 2 - dx0 * dx0 - dy0 * dy0 - dz0 * dz0 - dw0 * dw0;
        if (attn0 > 0) {
            attn0 *= attn0;
            value += attn0 * attn0 * extrapolate4(ctx, xsb + 0, ysb + 0,
                                         zsb + 0, wsb + 0, dx0, dy0, dz0, dw0);
        }


        double dx1 = dx0 - 1 - (0.309016994374947);
        double dy1 = dy0 - 0 - (0.309016994374947);
        double dz1 = dz0 - 0 - (0.309016994374947);
        double dw1 = dw0 - 0 - (0.309016994374947);
        double attn1 = 2 - dx1 * dx1 - dy1 * dy1 - dz1 * dz1 - dw1 * dw1;
        if (attn1 > 0) {
            attn1 *= attn1;
            value += attn1 * attn1 * extrapolate4(ctx, xsb + 1, ysb + 0,
                                         zsb + 0, wsb + 0, dx1, dy1, dz1, dw1);
        }


        double dx2 = dx0 - 0 - (0.309016994374947);
        double dy2 = dy0 - 1 - (0.309016994374947);
        double dz2 = dz1;
        double dw2 = dw1;
        double attn2 = 2 - dx2 * dx2 - dy2 * dy2 - dz2 * dz2 - dw2 * dw2;
        if (attn2 > 0) {
            attn2 *= attn2;
            value += attn2 * attn2 * extrapolate4(ctx, xsb + 0, ysb + 1,
                                         zsb + 0, wsb + 0, dx2, dy2, dz2, dw2);
        }


        double dx3 = dx2;
        double dy3 = dy1;
        double dz3 = dz0 - 1 - (0.309016994374947);
        double dw3 = dw1;
        double attn3 = 2 - dx3 * dx3 - dy3 * dy3 - dz3 * dz3 - dw3 * dw3;
        if (attn3 > 0) {
            attn3 *= attn3;
            value += attn3 * attn3 * extrapolate4(ctx, xsb + 0, ysb + 0,
                                         zsb + 1, wsb + 0, dx3, dy3, dz3, dw3);
        }


        double dx4 = dx2;
        double dy4 = dy1;
        double dz4 = dz1;
        double dw4 = dw0 - 1 - (0.309016994374947);
        double attn4 = 2 - dx4 * dx4 - dy4 * dy4 - dz4 * dz4 - dw4 * dw4;
        if (attn4 > 0) {
            attn4 *= attn4;
            value += attn4 * attn4 * extrapolate4(ctx, xsb + 0, ysb + 0,
                                         zsb + 0, wsb + 1, dx4, dy4, dz4, dw4);
        }
    } else if (inSum >=
               3) {


        int8_t aPoint = 0x0E;
        double aScore = xins;
        int8_t bPoint = 0x0D;
        double bScore = yins;
        if (aScore <= bScore && zins < bScore) {
            bScore = zins;
            bPoint = 0x0B;
        } else if (aScore > bScore && zins < aScore) {
            aScore = zins;
            aPoint = 0x0B;
        }
        if (aScore <= bScore && wins < bScore) {
            bScore = wins;
            bPoint = 0x07;
        } else if (aScore > bScore && wins < aScore) {
            aScore = wins;
            aPoint = 0x07;
        }





        double uins = 4 - inSum;
        if (uins < aScore || uins < bScore) {

            int8_t c = (bScore < aScore ? bPoint : aPoint);




            if ((c & 0x01) != 0) {
                xsv_ext0 = xsb + 2;
                xsv_ext1 = xsv_ext2 = xsb + 1;
                dx_ext0 = dx0 - 2 - 4 * (0.309016994374947);
                dx_ext1 = dx_ext2 = dx0 - 1 - 4 * (0.309016994374947);
            } else {
                xsv_ext0 = xsv_ext1 = xsv_ext2 = xsb;
                dx_ext0 = dx_ext1 = dx_ext2 = dx0 - 4 * (0.309016994374947);
            }

            if ((c & 0x02) != 0) {
                ysv_ext0 = ysv_ext1 = ysv_ext2 = ysb + 1;
                dy_ext0 = dy_ext1 = dy_ext2 = dy0 - 1 - 4 * (0.309016994374947);
                if ((c & 0x01) != 0) {
                    ysv_ext1 += 1;
                    dy_ext1 -= 1;
                } else {
                    ysv_ext0 += 1;
                    dy_ext0 -= 1;
                }
            } else {
                ysv_ext0 = ysv_ext1 = ysv_ext2 = ysb;
                dy_ext0 = dy_ext1 = dy_ext2 = dy0 - 4 * (0.309016994374947);
            }

            if ((c & 0x04) != 0) {
                zsv_ext0 = zsv_ext1 = zsv_ext2 = zsb + 1;
                dz_ext0 = dz_ext1 = dz_ext2 = dz0 - 1 - 4 * (0.309016994374947);
                if ((c & 0x03) != 0x03) {
                    if ((c & 0x03) == 0) {
                        zsv_ext0 += 1;
                        dz_ext0 -= 1;
                    } else {
                        zsv_ext1 += 1;
                        dz_ext1 -= 1;
                    }
                } else {
                    zsv_ext2 += 1;
                    dz_ext2 -= 1;
                }
            } else {
                zsv_ext0 = zsv_ext1 = zsv_ext2 = zsb;
                dz_ext0 = dz_ext1 = dz_ext2 = dz0 - 4 * (0.309016994374947);
            }

            if ((c & 0x08) != 0) {
                wsv_ext0 = wsv_ext1 = wsb + 1;
                wsv_ext2 = wsb + 2;
                dw_ext0 = dw_ext1 = dw0 - 1 - 4 * (0.309016994374947);
                dw_ext2 = dw0 - 2 - 4 * (0.309016994374947);
            } else {
                wsv_ext0 = wsv_ext1 = wsv_ext2 = wsb;
                dw_ext0 = dw_ext1 = dw_ext2 = dw0 - 4 * (0.309016994374947);
            }
        } else {

            int8_t c = (int8_t)(aPoint & bPoint);



            if ((c & 0x01) != 0) {
                xsv_ext0 = xsv_ext2 = xsb + 1;
                xsv_ext1 = xsb + 2;
                dx_ext0 = dx0 - 1 - 2 * (0.309016994374947);
                dx_ext1 = dx0 - 2 - 3 * (0.309016994374947);
                dx_ext2 = dx0 - 1 - 3 * (0.309016994374947);
            } else {
                xsv_ext0 = xsv_ext1 = xsv_ext2 = xsb;
                dx_ext0 = dx0 - 2 * (0.309016994374947);
                dx_ext1 = dx_ext2 = dx0 - 3 * (0.309016994374947);
            }

            if ((c & 0x02) != 0) {
                ysv_ext0 = ysv_ext1 = ysv_ext2 = ysb + 1;
                dy_ext0 = dy0 - 1 - 2 * (0.309016994374947);
                dy_ext1 = dy_ext2 = dy0 - 1 - 3 * (0.309016994374947);
                if ((c & 0x01) != 0) {
                    ysv_ext2 += 1;
                    dy_ext2 -= 1;
                } else {
                    ysv_ext1 += 1;
                    dy_ext1 -= 1;
                }
            } else {
                ysv_ext0 = ysv_ext1 = ysv_ext2 = ysb;
                dy_ext0 = dy0 - 2 * (0.309016994374947);
                dy_ext1 = dy_ext2 = dy0 - 3 * (0.309016994374947);
            }

            if ((c & 0x04) != 0) {
                zsv_ext0 = zsv_ext1 = zsv_ext2 = zsb + 1;
                dz_ext0 = dz0 - 1 - 2 * (0.309016994374947);
                dz_ext1 = dz_ext2 = dz0 - 1 - 3 * (0.309016994374947);
                if ((c & 0x03) != 0) {
                    zsv_ext2 += 1;
                    dz_ext2 -= 1;
                } else {
                    zsv_ext1 += 1;
                    dz_ext1 -= 1;
                }
            } else {
                zsv_ext0 = zsv_ext1 = zsv_ext2 = zsb;
                dz_ext0 = dz0 - 2 * (0.309016994374947);
                dz_ext1 = dz_ext2 = dz0 - 3 * (0.309016994374947);
            }

            if ((c & 0x08) != 0) {
                wsv_ext0 = wsv_ext1 = wsb + 1;
                wsv_ext2 = wsb + 2;
                dw_ext0 = dw0 - 1 - 2 * (0.309016994374947);
                dw_ext1 = dw0 - 1 - 3 * (0.309016994374947);
                dw_ext2 = dw0 - 2 - 3 * (0.309016994374947);
            } else {
                wsv_ext0 = wsv_ext1 = wsv_ext2 = wsb;
                dw_ext0 = dw0 - 2 * (0.309016994374947);
                dw_ext1 = dw_ext2 = dw0 - 3 * (0.309016994374947);
            }
        }


        double dx4 = dx0 - 1 - 3 * (0.309016994374947);
        double dy4 = dy0 - 1 - 3 * (0.309016994374947);
        double dz4 = dz0 - 1 - 3 * (0.309016994374947);
        double dw4 = dw0 - 3 * (0.309016994374947);
        double attn4 = 2 - dx4 * dx4 - dy4 * dy4 - dz4 * dz4 - dw4 * dw4;
        if (attn4 > 0) {
            attn4 *= attn4;
            value += attn4 * attn4 * extrapolate4(ctx, xsb + 1, ysb + 1,
                                         zsb + 1, wsb + 0, dx4, dy4, dz4, dw4);
        }


        double dx3 = dx4;
        double dy3 = dy4;
        double dz3 = dz0 - 3 * (0.309016994374947);
        double dw3 = dw0 - 1 - 3 * (0.309016994374947);
        double attn3 = 2 - dx3 * dx3 - dy3 * dy3 - dz3 * dz3 - dw3 * dw3;
        if (attn3 > 0) {
            attn3 *= attn3;
            value += attn3 * attn3 * extrapolate4(ctx, xsb + 1, ysb + 1,
                                         zsb + 0, wsb + 1, dx3, dy3, dz3, dw3);
        }


        double dx2 = dx4;
        double dy2 = dy0 - 3 * (0.309016994374947);
        double dz2 = dz4;
        double dw2 = dw3;
        double attn2 = 2 - dx2 * dx2 - dy2 * dy2 - dz2 * dz2 - dw2 * dw2;
        if (attn2 > 0) {
            attn2 *= attn2;
            value += attn2 * attn2 * extrapolate4(ctx, xsb + 1, ysb + 0,
                                         zsb + 1, wsb + 1, dx2, dy2, dz2, dw2);
        }


        double dx1 = dx0 - 3 * (0.309016994374947);
        double dz1 = dz4;
        double dy1 = dy4;
        double dw1 = dw3;
        double attn1 = 2 - dx1 * dx1 - dy1 * dy1 - dz1 * dz1 - dw1 * dw1;
        if (attn1 > 0) {
            attn1 *= attn1;
            value += attn1 * attn1 * extrapolate4(ctx, xsb + 0, ysb + 1,
                                         zsb + 1, wsb + 1, dx1, dy1, dz1, dw1);
        }


        dx0 = dx0 - 1 - 4 * (0.309016994374947);
        dy0 = dy0 - 1 - 4 * (0.309016994374947);
        dz0 = dz0 - 1 - 4 * (0.309016994374947);
        dw0 = dw0 - 1 - 4 * (0.309016994374947);
        double attn0 = 2 - dx0 * dx0 - dy0 * dy0 - dz0 * dz0 - dw0 * dw0;
        if (attn0 > 0) {
            attn0 *= attn0;
            value += attn0 * attn0 * extrapolate4(ctx, xsb + 1, ysb + 1,
                                         zsb + 1, wsb + 1, dx0, dy0, dz0, dw0);
        }
    } else if (inSum <= 2) {

        double aScore;
        int8_t aPoint;
        int aIsBiggerSide = 1;
        double bScore;
        int8_t bPoint;
        int bIsBiggerSide = 1;


        if (xins + yins > zins + wins) {
            aScore = xins + yins;
            aPoint = 0x03;
        } else {
            aScore = zins + wins;
            aPoint = 0x0C;
        }


        if (xins + zins > yins + wins) {
            bScore = xins + zins;
            bPoint = 0x05;
        } else {
            bScore = yins + wins;
            bPoint = 0x0A;
        }



        if (xins + wins > yins + zins) {
            double score = xins + wins;
            if (aScore >= bScore && score > bScore) {
                bScore = score;
                bPoint = 0x09;
            } else if (aScore < bScore && score > aScore) {
                aScore = score;
                aPoint = 0x09;
            }
        } else {
            double score = yins + zins;
            if (aScore >= bScore && score > bScore) {
                bScore = score;
                bPoint = 0x06;
            } else if (aScore < bScore && score > aScore) {
                aScore = score;
                aPoint = 0x06;
            }
        }


        double p1 = 2 - inSum + xins;
        if (aScore >= bScore && p1 > bScore) {
            bScore = p1;
            bPoint = 0x01;
            bIsBiggerSide = 0;
        } else if (aScore < bScore && p1 > aScore) {
            aScore = p1;
            aPoint = 0x01;
            aIsBiggerSide = 0;
        }


        double p2 = 2 - inSum + yins;
        if (aScore >= bScore && p2 > bScore) {
            bScore = p2;
            bPoint = 0x02;
            bIsBiggerSide = 0;
        } else if (aScore < bScore && p2 > aScore) {
            aScore = p2;
            aPoint = 0x02;
            aIsBiggerSide = 0;
        }


        double p3 = 2 - inSum + zins;
        if (aScore >= bScore && p3 > bScore) {
            bScore = p3;
            bPoint = 0x04;
            bIsBiggerSide = 0;
        } else if (aScore < bScore && p3 > aScore) {
            aScore = p3;
            aPoint = 0x04;
            aIsBiggerSide = 0;
        }


        double p4 = 2 - inSum + wins;
        if (aScore >= bScore && p4 > bScore) {
            bScore = p4;
            bPoint = 0x08;
            bIsBiggerSide = 0;
        } else if (aScore < bScore && p4 > aScore) {
            aScore = p4;
            aPoint = 0x08;
            aIsBiggerSide = 0;
        }



        if (aIsBiggerSide == bIsBiggerSide) {
            if (aIsBiggerSide) {
                int8_t c1 = (int8_t)(aPoint | bPoint);
                int8_t c2 = (int8_t)(aPoint & bPoint);
                if ((c1 & 0x01) == 0) {
                    xsv_ext0 = xsb;
                    xsv_ext1 = xsb - 1;
                    dx_ext0 = dx0 - 3 * (0.309016994374947);
                    dx_ext1 = dx0 + 1 - 2 * (0.309016994374947);
                } else {
                    xsv_ext0 = xsv_ext1 = xsb + 1;
                    dx_ext0 = dx0 - 1 - 3 * (0.309016994374947);
                    dx_ext1 = dx0 - 1 - 2 * (0.309016994374947);
                }

                if ((c1 & 0x02) == 0) {
                    ysv_ext0 = ysb;
                    ysv_ext1 = ysb - 1;
                    dy_ext0 = dy0 - 3 * (0.309016994374947);
                    dy_ext1 = dy0 + 1 - 2 * (0.309016994374947);
                } else {
                    ysv_ext0 = ysv_ext1 = ysb + 1;
                    dy_ext0 = dy0 - 1 - 3 * (0.309016994374947);
                    dy_ext1 = dy0 - 1 - 2 * (0.309016994374947);
                }

                if ((c1 & 0x04) == 0) {
                    zsv_ext0 = zsb;
                    zsv_ext1 = zsb - 1;
                    dz_ext0 = dz0 - 3 * (0.309016994374947);
                    dz_ext1 = dz0 + 1 - 2 * (0.309016994374947);
                } else {
                    zsv_ext0 = zsv_ext1 = zsb + 1;
                    dz_ext0 = dz0 - 1 - 3 * (0.309016994374947);
                    dz_ext1 = dz0 - 1 - 2 * (0.309016994374947);
                }

                if ((c1 & 0x08) == 0) {
                    wsv_ext0 = wsb;
                    wsv_ext1 = wsb - 1;
                    dw_ext0 = dw0 - 3 * (0.309016994374947);
                    dw_ext1 = dw0 + 1 - 2 * (0.309016994374947);
                } else {
                    wsv_ext0 = wsv_ext1 = wsb + 1;
                    dw_ext0 = dw0 - 1 - 3 * (0.309016994374947);
                    dw_ext1 = dw0 - 1 - 2 * (0.309016994374947);
                }


                xsv_ext2 = xsb;
                ysv_ext2 = ysb;
                zsv_ext2 = zsb;
                wsv_ext2 = wsb;
                dx_ext2 = dx0 - 2 * (0.309016994374947);
                dy_ext2 = dy0 - 2 * (0.309016994374947);
                dz_ext2 = dz0 - 2 * (0.309016994374947);
                dw_ext2 = dw0 - 2 * (0.309016994374947);
                if ((c2 & 0x01) != 0) {
                    xsv_ext2 += 2;
                    dx_ext2 -= 2;
                } else if ((c2 & 0x02) != 0) {
                    ysv_ext2 += 2;
                    dy_ext2 -= 2;
                } else if ((c2 & 0x04) != 0) {
                    zsv_ext2 += 2;
                    dz_ext2 -= 2;
                } else {
                    wsv_ext2 += 2;
                    dw_ext2 -= 2;
                }

            } else {

                xsv_ext2 = xsb;
                ysv_ext2 = ysb;
                zsv_ext2 = zsb;
                wsv_ext2 = wsb;
                dx_ext2 = dx0;
                dy_ext2 = dy0;
                dz_ext2 = dz0;
                dw_ext2 = dw0;


                int8_t c = (int8_t)(aPoint | bPoint);

                if ((c & 0x01) == 0) {
                    xsv_ext0 = xsb - 1;
                    xsv_ext1 = xsb;
                    dx_ext0 = dx0 + 1 - (0.309016994374947);
                    dx_ext1 = dx0 - (0.309016994374947);
                } else {
                    xsv_ext0 = xsv_ext1 = xsb + 1;
                    dx_ext0 = dx_ext1 = dx0 - 1 - (0.309016994374947);
                }

                if ((c & 0x02) == 0) {
                    ysv_ext0 = ysv_ext1 = ysb;
                    dy_ext0 = dy_ext1 = dy0 - (0.309016994374947);
                    if ((c & 0x01) == 0x01) {
                        ysv_ext0 -= 1;
                        dy_ext0 += 1;
                    } else {
                        ysv_ext1 -= 1;
                        dy_ext1 += 1;
                    }
                } else {
                    ysv_ext0 = ysv_ext1 = ysb + 1;
                    dy_ext0 = dy_ext1 = dy0 - 1 - (0.309016994374947);
                }

                if ((c & 0x04) == 0) {
                    zsv_ext0 = zsv_ext1 = zsb;
                    dz_ext0 = dz_ext1 = dz0 - (0.309016994374947);
                    if ((c & 0x03) == 0x03) {
                        zsv_ext0 -= 1;
                        dz_ext0 += 1;
                    } else {
                        zsv_ext1 -= 1;
                        dz_ext1 += 1;
                    }
                } else {
                    zsv_ext0 = zsv_ext1 = zsb + 1;
                    dz_ext0 = dz_ext1 = dz0 - 1 - (0.309016994374947);
                }

                if ((c & 0x08) == 0) {
                    wsv_ext0 = wsb;
                    wsv_ext1 = wsb - 1;
                    dw_ext0 = dw0 - (0.309016994374947);
                    dw_ext1 = dw0 + 1 - (0.309016994374947);
                } else {
                    wsv_ext0 = wsv_ext1 = wsb + 1;
                    dw_ext0 = dw_ext1 = dw0 - 1 - (0.309016994374947);
                }
            }
        } else {
            int8_t c1, c2;
            if (aIsBiggerSide) {
                c1 = aPoint;
                c2 = bPoint;
            } else {
                c1 = bPoint;
                c2 = aPoint;
            }



            if ((c1 & 0x01) == 0) {
                xsv_ext0 = xsb - 1;
                xsv_ext1 = xsb;
                dx_ext0 = dx0 + 1 - (0.309016994374947);
                dx_ext1 = dx0 - (0.309016994374947);
            } else {
                xsv_ext0 = xsv_ext1 = xsb + 1;
                dx_ext0 = dx_ext1 = dx0 - 1 - (0.309016994374947);
            }

            if ((c1 & 0x02) == 0) {
                ysv_ext0 = ysv_ext1 = ysb;
                dy_ext0 = dy_ext1 = dy0 - (0.309016994374947);
                if ((c1 & 0x01) == 0x01) {
                    ysv_ext0 -= 1;
                    dy_ext0 += 1;
                } else {
                    ysv_ext1 -= 1;
                    dy_ext1 += 1;
                }
            } else {
                ysv_ext0 = ysv_ext1 = ysb + 1;
                dy_ext0 = dy_ext1 = dy0 - 1 - (0.309016994374947);
            }

            if ((c1 & 0x04) == 0) {
                zsv_ext0 = zsv_ext1 = zsb;
                dz_ext0 = dz_ext1 = dz0 - (0.309016994374947);
                if ((c1 & 0x03) == 0x03) {
                    zsv_ext0 -= 1;
                    dz_ext0 += 1;
                } else {
                    zsv_ext1 -= 1;
                    dz_ext1 += 1;
                }
            } else {
                zsv_ext0 = zsv_ext1 = zsb + 1;
                dz_ext0 = dz_ext1 = dz0 - 1 - (0.309016994374947);
            }

            if ((c1 & 0x08) == 0) {
                wsv_ext0 = wsb;
                wsv_ext1 = wsb - 1;
                dw_ext0 = dw0 - (0.309016994374947);
                dw_ext1 = dw0 + 1 - (0.309016994374947);
            } else {
                wsv_ext0 = wsv_ext1 = wsb + 1;
                dw_ext0 = dw_ext1 = dw0 - 1 - (0.309016994374947);
            }



            xsv_ext2 = xsb;
            ysv_ext2 = ysb;
            zsv_ext2 = zsb;
            wsv_ext2 = wsb;
            dx_ext2 = dx0 - 2 * (0.309016994374947);
            dy_ext2 = dy0 - 2 * (0.309016994374947);
            dz_ext2 = dz0 - 2 * (0.309016994374947);
            dw_ext2 = dw0 - 2 * (0.309016994374947);
            if ((c2 & 0x01) != 0) {
                xsv_ext2 += 2;
                dx_ext2 -= 2;
            } else if ((c2 & 0x02) != 0) {
                ysv_ext2 += 2;
                dy_ext2 -= 2;
            } else if ((c2 & 0x04) != 0) {
                zsv_ext2 += 2;
                dz_ext2 -= 2;
            } else {
                wsv_ext2 += 2;
                dw_ext2 -= 2;
            }
        }


        double dx1 = dx0 - 1 - (0.309016994374947);
        double dy1 = dy0 - 0 - (0.309016994374947);
        double dz1 = dz0 - 0 - (0.309016994374947);
        double dw1 = dw0 - 0 - (0.309016994374947);
        double attn1 = 2 - dx1 * dx1 - dy1 * dy1 - dz1 * dz1 - dw1 * dw1;
        if (attn1 > 0) {
            attn1 *= attn1;
            value += attn1 * attn1 * extrapolate4(ctx, xsb + 1, ysb + 0,
                                         zsb + 0, wsb + 0, dx1, dy1, dz1, dw1);
        }


        double dx2 = dx0 - 0 - (0.309016994374947);
        double dy2 = dy0 - 1 - (0.309016994374947);
        double dz2 = dz1;
        double dw2 = dw1;
        double attn2 = 2 - dx2 * dx2 - dy2 * dy2 - dz2 * dz2 - dw2 * dw2;
        if (attn2 > 0) {
            attn2 *= attn2;
            value += attn2 * attn2 * extrapolate4(ctx, xsb + 0, ysb + 1,
                                         zsb + 0, wsb + 0, dx2, dy2, dz2, dw2);
        }


        double dx3 = dx2;
        double dy3 = dy1;
        double dz3 = dz0 - 1 - (0.309016994374947);
        double dw3 = dw1;
        double attn3 = 2 - dx3 * dx3 - dy3 * dy3 - dz3 * dz3 - dw3 * dw3;
        if (attn3 > 0) {
            attn3 *= attn3;
            value += attn3 * attn3 * extrapolate4(ctx, xsb + 0, ysb + 0,
                                         zsb + 1, wsb + 0, dx3, dy3, dz3, dw3);
        }


        double dx4 = dx2;
        double dy4 = dy1;
        double dz4 = dz1;
        double dw4 = dw0 - 1 - (0.309016994374947);
        double attn4 = 2 - dx4 * dx4 - dy4 * dy4 - dz4 * dz4 - dw4 * dw4;
        if (attn4 > 0) {
            attn4 *= attn4;
            value += attn4 * attn4 * extrapolate4(ctx, xsb + 0, ysb + 0,
                                         zsb + 0, wsb + 1, dx4, dy4, dz4, dw4);
        }


        double dx5 = dx0 - 1 - 2 * (0.309016994374947);
        double dy5 = dy0 - 1 - 2 * (0.309016994374947);
        double dz5 = dz0 - 0 - 2 * (0.309016994374947);
        double dw5 = dw0 - 0 - 2 * (0.309016994374947);
        double attn5 = 2 - dx5 * dx5 - dy5 * dy5 - dz5 * dz5 - dw5 * dw5;
        if (attn5 > 0) {
            attn5 *= attn5;
            value += attn5 * attn5 * extrapolate4(ctx, xsb + 1, ysb + 1,
                                         zsb + 0, wsb + 0, dx5, dy5, dz5, dw5);
        }


        double dx6 = dx0 - 1 - 2 * (0.309016994374947);
        double dy6 = dy0 - 0 - 2 * (0.309016994374947);
        double dz6 = dz0 - 1 - 2 * (0.309016994374947);
        double dw6 = dw0 - 0 - 2 * (0.309016994374947);
        double attn6 = 2 - dx6 * dx6 - dy6 * dy6 - dz6 * dz6 - dw6 * dw6;
        if (attn6 > 0) {
            attn6 *= attn6;
            value += attn6 * attn6 * extrapolate4(ctx, xsb + 1, ysb + 0,
                                         zsb + 1, wsb + 0, dx6, dy6, dz6, dw6);
        }


        double dx7 = dx0 - 1 - 2 * (0.309016994374947);
        double dy7 = dy0 - 0 - 2 * (0.309016994374947);
        double dz7 = dz0 - 0 - 2 * (0.309016994374947);
        double dw7 = dw0 - 1 - 2 * (0.309016994374947);
        double attn7 = 2 - dx7 * dx7 - dy7 * dy7 - dz7 * dz7 - dw7 * dw7;
        if (attn7 > 0) {
            attn7 *= attn7;
            value += attn7 * attn7 * extrapolate4(ctx, xsb + 1, ysb + 0,
                                         zsb + 0, wsb + 1, dx7, dy7, dz7, dw7);
        }


        double dx8 = dx0 - 0 - 2 * (0.309016994374947);
        double dy8 = dy0 - 1 - 2 * (0.309016994374947);
        double dz8 = dz0 - 1 - 2 * (0.309016994374947);
        double dw8 = dw0 - 0 - 2 * (0.309016994374947);
        double attn8 = 2 - dx8 * dx8 - dy8 * dy8 - dz8 * dz8 - dw8 * dw8;
        if (attn8 > 0) {
            attn8 *= attn8;
            value += attn8 * attn8 * extrapolate4(ctx, xsb + 0, ysb + 1,
                                         zsb + 1, wsb + 0, dx8, dy8, dz8, dw8);
        }


        double dx9 = dx0 - 0 - 2 * (0.309016994374947);
        double dy9 = dy0 - 1 - 2 * (0.309016994374947);
        double dz9 = dz0 - 0 - 2 * (0.309016994374947);
        double dw9 = dw0 - 1 - 2 * (0.309016994374947);
        double attn9 = 2 - dx9 * dx9 - dy9 * dy9 - dz9 * dz9 - dw9 * dw9;
        if (attn9 > 0) {
            attn9 *= attn9;
            value += attn9 * attn9 * extrapolate4(ctx, xsb + 0, ysb + 1,
                                         zsb + 0, wsb + 1, dx9, dy9, dz9, dw9);
        }


        double dx10 = dx0 - 0 - 2 * (0.309016994374947);
        double dy10 = dy0 - 0 - 2 * (0.309016994374947);
        double dz10 = dz0 - 1 - 2 * (0.309016994374947);
        double dw10 = dw0 - 1 - 2 * (0.309016994374947);
        double attn10 =
            2 - dx10 * dx10 - dy10 * dy10 - dz10 * dz10 - dw10 * dw10;
        if (attn10 > 0) {
            attn10 *= attn10;
            value +=
                attn10 * attn10 * extrapolate4(ctx, xsb + 0, ysb + 0, zsb + 1,
                                      wsb + 1, dx10, dy10, dz10, dw10);
        }
    } else {
        double aScore;
        int8_t aPoint;
        int aIsBiggerSide = 1;
        double bScore;
        int8_t bPoint;
        int bIsBiggerSide = 1;


        if (xins + yins < zins + wins) {
            aScore = xins + yins;
            aPoint = 0x0C;
        } else {
            aScore = zins + wins;
            aPoint = 0x03;
        }


        if (xins + zins < yins + wins) {
            bScore = xins + zins;
            bPoint = 0x0A;
        } else {
            bScore = yins + wins;
            bPoint = 0x05;
        }



        if (xins + wins < yins + zins) {
            double score = xins + wins;
            if (aScore <= bScore && score < bScore) {
                bScore = score;
                bPoint = 0x06;
            } else if (aScore > bScore && score < aScore) {
                aScore = score;
                aPoint = 0x06;
            }
        } else {
            double score = yins + zins;
            if (aScore <= bScore && score < bScore) {
                bScore = score;
                bPoint = 0x09;
            } else if (aScore > bScore && score < aScore) {
                aScore = score;
                aPoint = 0x09;
            }
        }


        double p1 = 3 - inSum + xins;
        if (aScore <= bScore && p1 < bScore) {
            bScore = p1;
            bPoint = 0x0E;
            bIsBiggerSide = 0;
        } else if (aScore > bScore && p1 < aScore) {
            aScore = p1;
            aPoint = 0x0E;
            aIsBiggerSide = 0;
        }


        double p2 = 3 - inSum + yins;
        if (aScore <= bScore && p2 < bScore) {
            bScore = p2;
            bPoint = 0x0D;
            bIsBiggerSide = 0;
        } else if (aScore > bScore && p2 < aScore) {
            aScore = p2;
            aPoint = 0x0D;
            aIsBiggerSide = 0;
        }


        double p3 = 3 - inSum + zins;
        if (aScore <= bScore && p3 < bScore) {
            bScore = p3;
            bPoint = 0x0B;
            bIsBiggerSide = 0;
        } else if (aScore > bScore && p3 < aScore) {
            aScore = p3;
            aPoint = 0x0B;
            aIsBiggerSide = 0;
        }


        double p4 = 3 - inSum + wins;
        if (aScore <= bScore && p4 < bScore) {
            bScore = p4;
            bPoint = 0x07;
            bIsBiggerSide = 0;
        } else if (aScore > bScore && p4 < aScore) {
            aScore = p4;
            aPoint = 0x07;
            aIsBiggerSide = 0;
        }



        if (aIsBiggerSide == bIsBiggerSide) {
            if (aIsBiggerSide) {
                int8_t c1 = (int8_t)(aPoint & bPoint);
                int8_t c2 = (int8_t)(aPoint | bPoint);



                xsv_ext0 = xsv_ext1 = xsb;
                ysv_ext0 = ysv_ext1 = ysb;
                zsv_ext0 = zsv_ext1 = zsb;
                wsv_ext0 = wsv_ext1 = wsb;
                dx_ext0 = dx0 - (0.309016994374947);
                dy_ext0 = dy0 - (0.309016994374947);
                dz_ext0 = dz0 - (0.309016994374947);
                dw_ext0 = dw0 - (0.309016994374947);
                dx_ext1 = dx0 - 2 * (0.309016994374947);
                dy_ext1 = dy0 - 2 * (0.309016994374947);
                dz_ext1 = dz0 - 2 * (0.309016994374947);
                dw_ext1 = dw0 - 2 * (0.309016994374947);
                if ((c1 & 0x01) != 0) {
                    xsv_ext0 += 1;
                    dx_ext0 -= 1;
                    xsv_ext1 += 2;
                    dx_ext1 -= 2;
                } else if ((c1 & 0x02) != 0) {
                    ysv_ext0 += 1;
                    dy_ext0 -= 1;
                    ysv_ext1 += 2;
                    dy_ext1 -= 2;
                } else if ((c1 & 0x04) != 0) {
                    zsv_ext0 += 1;
                    dz_ext0 -= 1;
                    zsv_ext1 += 2;
                    dz_ext1 -= 2;
                } else {
                    wsv_ext0 += 1;
                    dw_ext0 -= 1;
                    wsv_ext1 += 2;
                    dw_ext1 -= 2;
                }


                xsv_ext2 = xsb + 1;
                ysv_ext2 = ysb + 1;
                zsv_ext2 = zsb + 1;
                wsv_ext2 = wsb + 1;
                dx_ext2 = dx0 - 1 - 2 * (0.309016994374947);
                dy_ext2 = dy0 - 1 - 2 * (0.309016994374947);
                dz_ext2 = dz0 - 1 - 2 * (0.309016994374947);
                dw_ext2 = dw0 - 1 - 2 * (0.309016994374947);
                if ((c2 & 0x01) == 0) {
                    xsv_ext2 -= 2;
                    dx_ext2 += 2;
                } else if ((c2 & 0x02) == 0) {
                    ysv_ext2 -= 2;
                    dy_ext2 += 2;
                } else if ((c2 & 0x04) == 0) {
                    zsv_ext2 -= 2;
                    dz_ext2 += 2;
                } else {
                    wsv_ext2 -= 2;
                    dw_ext2 += 2;
                }
            } else {

                xsv_ext2 = xsb + 1;
                ysv_ext2 = ysb + 1;
                zsv_ext2 = zsb + 1;
                wsv_ext2 = wsb + 1;
                dx_ext2 = dx0 - 1 - 4 * (0.309016994374947);
                dy_ext2 = dy0 - 1 - 4 * (0.309016994374947);
                dz_ext2 = dz0 - 1 - 4 * (0.309016994374947);
                dw_ext2 = dw0 - 1 - 4 * (0.309016994374947);


                int8_t c = (int8_t)(aPoint & bPoint);

                if ((c & 0x01) != 0) {
                    xsv_ext0 = xsb + 2;
                    xsv_ext1 = xsb + 1;
                    dx_ext0 = dx0 - 2 - 3 * (0.309016994374947);
                    dx_ext1 = dx0 - 1 - 3 * (0.309016994374947);
                } else {
                    xsv_ext0 = xsv_ext1 = xsb;
                    dx_ext0 = dx_ext1 = dx0 - 3 * (0.309016994374947);
                }

                if ((c & 0x02) != 0) {
                    ysv_ext0 = ysv_ext1 = ysb + 1;
                    dy_ext0 = dy_ext1 = dy0 - 1 - 3 * (0.309016994374947);
                    if ((c & 0x01) == 0) {
                        ysv_ext0 += 1;
                        dy_ext0 -= 1;
                    } else {
                        ysv_ext1 += 1;
                        dy_ext1 -= 1;
                    }
                } else {
                    ysv_ext0 = ysv_ext1 = ysb;
                    dy_ext0 = dy_ext1 = dy0 - 3 * (0.309016994374947);
                }

                if ((c & 0x04) != 0) {
                    zsv_ext0 = zsv_ext1 = zsb + 1;
                    dz_ext0 = dz_ext1 = dz0 - 1 - 3 * (0.309016994374947);
                    if ((c & 0x03) == 0) {
                        zsv_ext0 += 1;
                        dz_ext0 -= 1;
                    } else {
                        zsv_ext1 += 1;
                        dz_ext1 -= 1;
                    }
                } else {
                    zsv_ext0 = zsv_ext1 = zsb;
                    dz_ext0 = dz_ext1 = dz0 - 3 * (0.309016994374947);
                }

                if ((c & 0x08) != 0) {
                    wsv_ext0 = wsb + 1;
                    wsv_ext1 = wsb + 2;
                    dw_ext0 = dw0 - 1 - 3 * (0.309016994374947);
                    dw_ext1 = dw0 - 2 - 3 * (0.309016994374947);
                } else {
                    wsv_ext0 = wsv_ext1 = wsb;
                    dw_ext0 = dw_ext1 = dw0 - 3 * (0.309016994374947);
                }
            }
        } else {
            int8_t c1, c2;
            if (aIsBiggerSide) {
                c1 = aPoint;
                c2 = bPoint;
            } else {
                c1 = bPoint;
                c2 = aPoint;
            }



            if ((c1 & 0x01) != 0) {
                xsv_ext0 = xsb + 2;
                xsv_ext1 = xsb + 1;
                dx_ext0 = dx0 - 2 - 3 * (0.309016994374947);
                dx_ext1 = dx0 - 1 - 3 * (0.309016994374947);
            } else {
                xsv_ext0 = xsv_ext1 = xsb;
                dx_ext0 = dx_ext1 = dx0 - 3 * (0.309016994374947);
            }

            if ((c1 & 0x02) != 0) {
                ysv_ext0 = ysv_ext1 = ysb + 1;
                dy_ext0 = dy_ext1 = dy0 - 1 - 3 * (0.309016994374947);
                if ((c1 & 0x01) == 0) {
                    ysv_ext0 += 1;
                    dy_ext0 -= 1;
                } else {
                    ysv_ext1 += 1;
                    dy_ext1 -= 1;
                }
            } else {
                ysv_ext0 = ysv_ext1 = ysb;
                dy_ext0 = dy_ext1 = dy0 - 3 * (0.309016994374947);
            }

            if ((c1 & 0x04) != 0) {
                zsv_ext0 = zsv_ext1 = zsb + 1;
                dz_ext0 = dz_ext1 = dz0 - 1 - 3 * (0.309016994374947);
                if ((c1 & 0x03) == 0) {
                    zsv_ext0 += 1;
                    dz_ext0 -= 1;
                } else {
                    zsv_ext1 += 1;
                    dz_ext1 -= 1;
                }
            } else {
                zsv_ext0 = zsv_ext1 = zsb;
                dz_ext0 = dz_ext1 = dz0 - 3 * (0.309016994374947);
            }

            if ((c1 & 0x08) != 0) {
                wsv_ext0 = wsb + 1;
                wsv_ext1 = wsb + 2;
                dw_ext0 = dw0 - 1 - 3 * (0.309016994374947);
                dw_ext1 = dw0 - 2 - 3 * (0.309016994374947);
            } else {
                wsv_ext0 = wsv_ext1 = wsb;
                dw_ext0 = dw_ext1 = dw0 - 3 * (0.309016994374947);
            }



            xsv_ext2 = xsb + 1;
            ysv_ext2 = ysb + 1;
            zsv_ext2 = zsb + 1;
            wsv_ext2 = wsb + 1;
            dx_ext2 = dx0 - 1 - 2 * (0.309016994374947);
            dy_ext2 = dy0 - 1 - 2 * (0.309016994374947);
            dz_ext2 = dz0 - 1 - 2 * (0.309016994374947);
            dw_ext2 = dw0 - 1 - 2 * (0.309016994374947);
            if ((c2 & 0x01) == 0) {
                xsv_ext2 -= 2;
                dx_ext2 += 2;
            } else if ((c2 & 0x02) == 0) {
                ysv_ext2 -= 2;
                dy_ext2 += 2;
            } else if ((c2 & 0x04) == 0) {
                zsv_ext2 -= 2;
                dz_ext2 += 2;
            } else {
                wsv_ext2 -= 2;
                dw_ext2 += 2;
            }
        }


        double dx4 = dx0 - 1 - 3 * (0.309016994374947);
        double dy4 = dy0 - 1 - 3 * (0.309016994374947);
        double dz4 = dz0 - 1 - 3 * (0.309016994374947);
        double dw4 = dw0 - 3 * (0.309016994374947);
        double attn4 = 2 - dx4 * dx4 - dy4 * dy4 - dz4 * dz4 - dw4 * dw4;
        if (attn4 > 0) {
            attn4 *= attn4;
            value += attn4 * attn4 * extrapolate4(ctx, xsb + 1, ysb + 1,
                                         zsb + 1, wsb + 0, dx4, dy4, dz4, dw4);
        }


        double dx3 = dx4;
        double dy3 = dy4;
        double dz3 = dz0 - 3 * (0.309016994374947);
        double dw3 = dw0 - 1 - 3 * (0.309016994374947);
        double attn3 = 2 - dx3 * dx3 - dy3 * dy3 - dz3 * dz3 - dw3 * dw3;
        if (attn3 > 0) {
            attn3 *= attn3;
            value += attn3 * attn3 * extrapolate4(ctx, xsb + 1, ysb + 1,
                                         zsb + 0, wsb + 1, dx3, dy3, dz3, dw3);
        }


        double dx2 = dx4;
        double dy2 = dy0 - 3 * (0.309016994374947);
        double dz2 = dz4;
        double dw2 = dw3;
        double attn2 = 2 - dx2 * dx2 - dy2 * dy2 - dz2 * dz2 - dw2 * dw2;
        if (attn2 > 0) {
            attn2 *= attn2;
            value += attn2 * attn2 * extrapolate4(ctx, xsb + 1, ysb + 0,
                                         zsb + 1, wsb + 1, dx2, dy2, dz2, dw2);
        }


        double dx1 = dx0 - 3 * (0.309016994374947);
        double dz1 = dz4;
        double dy1 = dy4;
        double dw1 = dw3;
        double attn1 = 2 - dx1 * dx1 - dy1 * dy1 - dz1 * dz1 - dw1 * dw1;
        if (attn1 > 0) {
            attn1 *= attn1;
            value += attn1 * attn1 * extrapolate4(ctx, xsb + 0, ysb + 1,
                                         zsb + 1, wsb + 1, dx1, dy1, dz1, dw1);
        }


        double dx5 = dx0 - 1 - 2 * (0.309016994374947);
        double dy5 = dy0 - 1 - 2 * (0.309016994374947);
        double dz5 = dz0 - 0 - 2 * (0.309016994374947);
        double dw5 = dw0 - 0 - 2 * (0.309016994374947);
        double attn5 = 2 - dx5 * dx5 - dy5 * dy5 - dz5 * dz5 - dw5 * dw5;
        if (attn5 > 0) {
            attn5 *= attn5;
            value += attn5 * attn5 * extrapolate4(ctx, xsb + 1, ysb + 1,
                                         zsb + 0, wsb + 0, dx5, dy5, dz5, dw5);
        }


        double dx6 = dx0 - 1 - 2 * (0.309016994374947);
        double dy6 = dy0 - 0 - 2 * (0.309016994374947);
        double dz6 = dz0 - 1 - 2 * (0.309016994374947);
        double dw6 = dw0 - 0 - 2 * (0.309016994374947);
        double attn6 = 2 - dx6 * dx6 - dy6 * dy6 - dz6 * dz6 - dw6 * dw6;
        if (attn6 > 0) {
            attn6 *= attn6;
            value += attn6 * attn6 * extrapolate4(ctx, xsb + 1, ysb + 0,
                                         zsb + 1, wsb + 0, dx6, dy6, dz6, dw6);
        }


        double dx7 = dx0 - 1 - 2 * (0.309016994374947);
        double dy7 = dy0 - 0 - 2 * (0.309016994374947);
        double dz7 = dz0 - 0 - 2 * (0.309016994374947);
        double dw7 = dw0 - 1 - 2 * (0.309016994374947);
        double attn7 = 2 - dx7 * dx7 - dy7 * dy7 - dz7 * dz7 - dw7 * dw7;
        if (attn7 > 0) {
            attn7 *= attn7;
            value += attn7 * attn7 * extrapolate4(ctx, xsb + 1, ysb + 0,
                                         zsb + 0, wsb + 1, dx7, dy7, dz7, dw7);
        }


        double dx8 = dx0 - 0 - 2 * (0.309016994374947);
        double dy8 = dy0 - 1 - 2 * (0.309016994374947);
        double dz8 = dz0 - 1 - 2 * (0.309016994374947);
        double dw8 = dw0 - 0 - 2 * (0.309016994374947);
        double attn8 = 2 - dx8 * dx8 - dy8 * dy8 - dz8 * dz8 - dw8 * dw8;
        if (attn8 > 0) {
            attn8 *= attn8;
            value += attn8 * attn8 * extrapolate4(ctx, xsb + 0, ysb + 1,
                                         zsb + 1, wsb + 0, dx8, dy8, dz8, dw8);
        }


        double dx9 = dx0 - 0 - 2 * (0.309016994374947);
        double dy9 = dy0 - 1 - 2 * (0.309016994374947);
        double dz9 = dz0 - 0 - 2 * (0.309016994374947);
        double dw9 = dw0 - 1 - 2 * (0.309016994374947);
        double attn9 = 2 - dx9 * dx9 - dy9 * dy9 - dz9 * dz9 - dw9 * dw9;
        if (attn9 > 0) {
            attn9 *= attn9;
            value += attn9 * attn9 * extrapolate4(ctx, xsb + 0, ysb + 1,
                                         zsb + 0, wsb + 1, dx9, dy9, dz9, dw9);
        }


        double dx10 = dx0 - 0 - 2 * (0.309016994374947);
        double dy10 = dy0 - 0 - 2 * (0.309016994374947);
        double dz10 = dz0 - 1 - 2 * (0.309016994374947);
        double dw10 = dw0 - 1 - 2 * (0.309016994374947);
        double attn10 =
            2 - dx10 * dx10 - dy10 * dy10 - dz10 * dz10 - dw10 * dw10;
        if (attn10 > 0) {
            attn10 *= attn10;
            value +=
                attn10 * attn10 * extrapolate4(ctx, xsb + 0, ysb + 0, zsb + 1,
                                      wsb + 1, dx10, dy10, dz10, dw10);
        }
    }


    double attn_ext0 = 2 - dx_ext0 * dx_ext0 - dy_ext0 * dy_ext0 -
                       dz_ext0 * dz_ext0 - dw_ext0 * dw_ext0;
    if (attn_ext0 > 0) {
        attn_ext0 *= attn_ext0;
        value += attn_ext0 * attn_ext0 * extrapolate4(ctx, xsv_ext0, ysv_ext0,
                                             zsv_ext0, wsv_ext0, dx_ext0,
                                             dy_ext0, dz_ext0, dw_ext0);
    }


    double attn_ext1 = 2 - dx_ext1 * dx_ext1 - dy_ext1 * dy_ext1 -
                       dz_ext1 * dz_ext1 - dw_ext1 * dw_ext1;
    if (attn_ext1 > 0) {
        attn_ext1 *= attn_ext1;
        value += attn_ext1 * attn_ext1 * extrapolate4(ctx, xsv_ext1, ysv_ext1,
                                             zsv_ext1, wsv_ext1, dx_ext1,
                                             dy_ext1, dz_ext1, dw_ext1);
    }


    double attn_ext2 = 2 - dx_ext2 * dx_ext2 - dy_ext2 * dy_ext2 -
                       dz_ext2 * dz_ext2 - dw_ext2 * dw_ext2;
    if (attn_ext2 > 0) {
        attn_ext2 *= attn_ext2;
        value += attn_ext2 * attn_ext2 * extrapolate4(ctx, xsv_ext2, ysv_ext2,
                                             zsv_ext2, wsv_ext2, dx_ext2,
                                             dy_ext2, dz_ext2, dw_ext2);
    }

    return value / (30.0);
}
