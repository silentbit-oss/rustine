# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/ops.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/ops.c"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/image.h" 1


       
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/include/heman.h" 1
       
# 10 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/include/heman.h"
typedef struct heman_image_s heman_image;



typedef struct heman_image_s heman_points;
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/include/heman.h"
typedef unsigned int heman_color;
typedef unsigned char heman_byte;


heman_image* heman_image_create(int width, int height, int nbands);


void heman_image_info(heman_image*, int* width, int* height, int* nbands);


float* heman_image_data(heman_image*);


void heman_image_array(heman_image* img, float** outview, int* n);


float* heman_image_texel(heman_image*, int x, int y);


void heman_image_sample(heman_image*, float u, float v, float* result);


void heman_image_clear(heman_image*, float value);


void heman_image_destroy(heman_image*);


heman_image* heman_image_extract_alpha(heman_image*);


heman_image* heman_image_extract_rgb(heman_image*);





heman_image* heman_color_create_gradient(int width, int num_colors,
    const int* cp_locations, const heman_color* cp_colors);



void heman_color_set_gamma(float f);




heman_image* heman_color_apply_gradient(heman_image* heightmap,
    float minheight, float maxheight, heman_image* gradient);


heman_image* heman_color_from_grayscale(heman_image* gray);


heman_image* heman_color_to_grayscale(heman_image* colorimg);



heman_image* heman_color_from_cpcf(heman_image* cfield, heman_image* texture);



heman_image* heman_generate_island_heightmap(int width, int height, int seed);


heman_image* heman_generate_rock_heightmap(int width, int height, int seed);



heman_image* heman_generate_planet_heightmap(int width, int height, int seed);





heman_image* heman_generate_archipelago_heightmap(
    int width, int height, heman_points* points, float noiseamt, int seed);





void heman_generate_archipelago_political(int width, int height,
    heman_points* points, const heman_color* colors, heman_color ocean,
    int seed, heman_image** elevation, heman_image** political,
    int elevation_mode);





heman_image* heman_generate_simplex_fbm(int width, int height, float frequency,
    float amplitude, int octaves, float lacunarity, float gain, int seed);


heman_image* heman_lighting_apply(heman_image* heightmap,
    heman_image* colorbuffer, float occlusion, float diffuse,
    float diffuse_softening, const float* light_position);



heman_image* heman_lighting_compute_normals(heman_image* heightmap);



heman_image* heman_lighting_compute_occlusion(heman_image* heightmap);


void heman_lighting_set_occlusion_scale(float s);



heman_image* heman_distance_create_sdf(heman_image* monochrome);



heman_image* heman_distance_create_df(heman_image* monochrome);




heman_image* heman_distance_create_cpcf(heman_image* seed);


heman_image* heman_distance_from_cpcf(heman_image* cf);


heman_image* heman_distance_identity_cpcf(int width, int height);



heman_image* heman_import_u8(int width, int height, int nbands,
    const heman_byte* source, float minval, float maxval);


void heman_export_ply(heman_image*, const char* filename);


void heman_export_with_colors_ply(
    heman_image* heightmap, heman_image* colors, const char* filename);



void heman_export_u8(
    heman_image* source, float minv, float maxv, heman_byte* outp);


heman_image* heman_ops_stitch_horizontal(heman_image** images, int count);


heman_image* heman_ops_stitch_vertical(heman_image** images, int count);




heman_image* heman_ops_normalize_f32(
    heman_image* source, float minval, float maxval);


heman_image* heman_ops_max(heman_image* imga, heman_image* imgb);


heman_image* heman_ops_step(heman_image* image, float threshold);




heman_image* heman_ops_stairstep(heman_image* image, int nsteps,
    heman_image* mask, heman_color mask_color, int invert_mask,
    float offset);



heman_image* heman_ops_percentiles(heman_image* image, int nsteps,
    heman_image* mask, heman_color mask_color, int invert_mask,
    float offset);


heman_image* heman_ops_sweep(heman_image* image);



heman_image* heman_ops_laplacian(heman_image* heightmap);


heman_image* heman_ops_sobel(heman_image* dst, heman_color edge_color);


void heman_ops_accumulate(heman_image* dst, heman_image* src);


heman_image* heman_ops_warp(heman_image* src, int seed, int octaves);


heman_image* heman_ops_warp_points(heman_image* src, int seed, int octaves,
    heman_points* pts);


heman_image* heman_ops_extract_mask(heman_image* src, heman_color color, int invert);


heman_image* heman_ops_replace_color(
    heman_image* src, heman_color color, heman_image* texture);



heman_image* heman_ops_merge_political(
    heman_image* elevation, heman_image* political, heman_color ocean_color);


heman_image* heman_ops_emboss(heman_image* elevation, int mode);


heman_image* heman_points_create(float* xy, int npoints, int nbands);


void heman_points_destroy(heman_points*);



heman_points* heman_points_from_grid(float width, float height,
    float cellsize, float jitter);



heman_points* heman_points_from_poisson(
    float width, float height, float mindist);




heman_points* heman_points_from_density(
    heman_image* density, float mindist, float maxdist);


void heman_draw_points(heman_image* target, heman_points* pts, float val);


void heman_draw_colored_points(
    heman_image* target, heman_points* coords, const heman_color* colors);


void heman_draw_colored_circles(heman_image* target, heman_points* pts,
    int radius, const heman_color* colors);



void heman_draw_splats(
    heman_image* target, heman_points* pts, int radius, int blend_mode);



void heman_draw_contour_from_points(heman_image* target, heman_points* coords,
    heman_color color, float mind, float maxd, int filterd);


int heman_get_num_threads();
# 5 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/image.h" 2

struct heman_image_s {
    int width;
    int height;
    int nbands;
    float* data;
};

extern float _gamma;
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/image.h"
inline float smoothstep(
    float edge0, float edge1, float x)
{
    float t;
    t = (0.0f > (1.0f > (x - edge0) / (edge1 - edge0) ? (x - edge0) / (edge1 - edge0) : 1.0f) ? 0.0f : (1.0f > (x - edge0) / (edge1 - edge0) ? (x - edge0) / (edge1 - edge0) : 1.0f));
    return t * t * (3.0 - 2.0 * t);
}

void generate_gaussian_row(int* target, int fwidth);
void generate_gaussian_splat(float* target, int fwidth);
# 2 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/ops.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/noise.h" 1
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/noise.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 2
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
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 2
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
# 3 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/ops.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 1
# 4 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/ops.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/./kazmath/vec3.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/./kazmath/vec3.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 1
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/./kazmath/vec3.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/./kazmath/utility.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/./kazmath/utility.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/math.h" 1
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/./kazmath/utility.h" 2
# 81 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/./kazmath/utility.h"
extern float kmSQR(float s);
extern float kmDegreesToRadians(float degrees);
extern float kmRadiansToDegrees(float radians);

extern float kmMin(float lhs, float rhs);
extern float kmMax(float lhs, float rhs);
extern unsigned char kmAlmostEqual(float lhs, float rhs);

extern float kmClamp(float x, float min, float max);
extern float kmLerp(float x, float y, float factor);
# 31 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/./kazmath/vec3.h" 2

struct kmMat4;
struct kmMat3;
struct kmPlane;

typedef struct kmVec3 {
 float x;
 float y;
 float z;
} kmVec3;





kmVec3* kmVec3Fill(kmVec3* pOut, float x, float y, float z);
float kmVec3Length(const kmVec3* pIn);
float kmVec3LengthSq(const kmVec3* pIn);
kmVec3* kmVec3Lerp(kmVec3* pOut, const kmVec3* pV1, const kmVec3* pV2, float t);
kmVec3* kmVec3Normalize(kmVec3* pOut, const kmVec3* pIn);
kmVec3* kmVec3Cross(kmVec3* pOut, const kmVec3* pV1, const kmVec3* pV2);
float kmVec3Dot(const kmVec3* pV1, const kmVec3* pV2);
kmVec3* kmVec3Add(kmVec3* pOut, const kmVec3* pV1, const kmVec3* pV2);
kmVec3* kmVec3Subtract(kmVec3* pOut, const kmVec3* pV1, const kmVec3* pV2);
kmVec3* kmVec3Mul( kmVec3* pOut,const kmVec3* pV1, const kmVec3* pV2 );
kmVec3* kmVec3Div( kmVec3* pOut,const kmVec3* pV1, const kmVec3* pV2 );

kmVec3* kmVec3MultiplyMat3(kmVec3 *pOut, const kmVec3 *pV, const struct kmMat3* pM);
kmVec3* kmVec3MultiplyMat4(kmVec3* pOut, const kmVec3* pV, const struct kmMat4* pM);

kmVec3* kmVec3Transform(kmVec3* pOut, const kmVec3* pV1, const struct kmMat4* pM);
kmVec3* kmVec3TransformNormal(kmVec3* pOut, const kmVec3* pV, const struct kmMat4* pM);
kmVec3* kmVec3TransformCoord(kmVec3* pOut, const kmVec3* pV, const struct kmMat4* pM);

kmVec3* kmVec3Scale(kmVec3* pOut, const kmVec3* pIn, const float s);
int kmVec3AreEqual(const kmVec3* p1, const kmVec3* p2);
kmVec3* kmVec3InverseTransform(kmVec3* pOut, const kmVec3* pV, const struct kmMat4* pM);
kmVec3* kmVec3InverseTransformNormal(kmVec3* pOut, const kmVec3* pVect, const struct kmMat4* pM);
kmVec3* kmVec3Assign(kmVec3* pOut, const kmVec3* pIn);
kmVec3* kmVec3Zero(kmVec3* pOut);
kmVec3* kmVec3GetHorizontalAngle(kmVec3* pOut, const kmVec3 *pIn);
kmVec3* kmVec3RotationToDirection(kmVec3* pOut, const kmVec3* pIn, const kmVec3* forwards);

kmVec3* kmVec3ProjectOnToPlane(kmVec3* pOut, const kmVec3* point, const struct kmPlane* plane);

kmVec3* kmVec3Reflect(kmVec3* pOut, const kmVec3* pIn, const kmVec3* normal);

extern const kmVec3 KM_VEC3_NEG_Z;
extern const kmVec3 KM_VEC3_POS_Z;
extern const kmVec3 KM_VEC3_POS_Y;
extern const kmVec3 KM_VEC3_NEG_Y;
extern const kmVec3 KM_VEC3_NEG_X;
extern const kmVec3 KM_VEC3_POS_X;
extern const kmVec3 KM_VEC3_ZERO;
# 5 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/ops.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/memory.h" 1
# 6 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/ops.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 7 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/ops.c" 2





int heman_get_num_threads() { return omp_get_max_threads(); }

heman_image* heman_ops_step(heman_image* hmap, float threshold)
{
    assert(hmap->nbands == 1);
    heman_image* result = heman_image_create(hmap->width, hmap->height, 1);
    int size = hmap->height * hmap->width;
    float* src = hmap->data;
    float* dst = result->data;
    for (int i = 0; i < size; ++i) {
        *dst++ = (*src++) >= threshold ? 1 : 0;
    }
    return result;
}

heman_image* heman_ops_max(heman_image* imga, heman_image* imgb)
{
    assert(imga->width == imgb->width);
    assert(imga->height == imgb->height);
    assert(imga->nbands == imgb->nbands);
    heman_image* result =
        heman_image_create(imga->width, imga->height, imga->nbands);
    int size = imga->height * imga->width * imga->nbands;
    float* srca = imga->data;
    float* srcb = imgb->data;
    float* dst = result->data;
    for (int i = 0; i < size; ++i, ++dst, ++srca, ++srcb) {
        *dst = (*srca > *srcb ? *srca : *srcb);
    }
    return result;
}

heman_image* heman_ops_sweep(heman_image* hmap)
{
    assert(hmap->nbands == 1);
    heman_image* result = heman_image_create(hmap->height, 1, 1);
    float* dst = result->data;
    const float* src = hmap->data;
    float invw = 1.0f / hmap->width;
    for (int y = 0; y < hmap->height; y++) {
        float acc = 0;
        for (int x = 0; x < hmap->width; x++) {
            acc += *src++;
        }
        *dst++ = (acc * invw);
    }
    return result;
}

static void copy_row(heman_image* src, heman_image* dst, int dstx, int y)
{
    int width = src->width;
    if (src->nbands == 1) {
        for (int x = 0; x < width; x++) {
            float* srcp = heman_image_texel(src, x, y);
            float* dstp = heman_image_texel(dst, dstx + x, y);
            *dstp = *srcp;
        }
        return;
    }
    for (int x = 0; x < width; x++) {
        float* srcp = heman_image_texel(src, x, y);
        float* dstp = heman_image_texel(dst, dstx + x, y);
        int nbands = src->nbands;
        while (nbands--) {
            *dstp++ = *srcp++;
        }
    }
}

heman_image* heman_ops_stitch_horizontal(heman_image** images, int count)
{
    assert(count > 0);
    int width = images[0]->width;
    int height = images[0]->height;
    int nbands = images[0]->nbands;
    for (int i = 1; i < count; i++) {
        assert(images[i]->width == width);
        assert(images[i]->height == height);
        assert(images[i]->nbands == nbands);
    }
    heman_image* result = heman_image_create(width * count, height, nbands);

    int y;
#pragma omp parallel for
    for (y = 0; y < height; y++) {
        for (int tile = 0; tile < count; tile++) {
            copy_row(images[tile], result, tile * width, y);
        }
    }

    return result;
}

heman_image* heman_ops_stitch_vertical(heman_image** images, int count)
{
    assert(count > 0);
    int width = images[0]->width;
    int height = images[0]->height;
    int nbands = images[0]->nbands;
    for (int i = 1; i < count; i++) {
        assert(images[i]->width == width);
        assert(images[i]->height == height);
        assert(images[i]->nbands == nbands);
    }
    heman_image* result = heman_image_create(width, height * count, nbands);
    int size = width * height * nbands;
    float* dst = result->data;
    for (int tile = 0; tile < count; tile++) {
        memcpy(dst, images[tile]->data, size * sizeof(float));
        dst += size;
    }
    return result;
}

heman_image* heman_ops_normalize_f32(
    heman_image* source, float minv, float maxv)
{
    heman_image* result =
        heman_image_create(source->width, source->height, source->nbands);
    float* src = source->data;
    float* dst = result->data;
    float scale = 1.0f / (maxv - minv);
    int size = source->height * source->width * source->nbands;
    for (int i = 0; i < size; ++i) {
        float v = (*src++ - minv) * scale;
        *dst++ = (0 > (1 > v ? v : 1) ? 0 : (1 > v ? v : 1));
    }
    return result;
}

heman_image* heman_ops_laplacian(heman_image* heightmap)
{
    assert(heightmap->nbands == 1);
    int width = heightmap->width;
    int height = heightmap->height;
    heman_image* result = heman_image_create(width, height, 1);
    int maxx = width - 1;
    int maxy = height - 1;

    int y;
#pragma omp parallel for
    for (y = 0; y < height; y++) {
        int y1 = (y + 1 > maxy ? maxy : y + 1);
        float* dst = result->data + y * width;
        for (int x = 0; x < width; x++) {
            int x1 = (x + 1 > maxx ? maxx : x + 1);
            float p = *heman_image_texel(heightmap, x, y);
            float px = *heman_image_texel(heightmap, x1, y);
            float py = *heman_image_texel(heightmap, x, y1);
            *dst++ = (p - px) * (p - px) + (p - py) * (p - py);
        }
    }

    return result;
}

void heman_ops_accumulate(heman_image* dst, heman_image* src)
{
    assert(dst->nbands == src->nbands);
    assert(dst->width == src->width);
    assert(dst->height == src->height);
    int size = dst->height * dst->width;
    float* sdata = src->data;
    float* ddata = dst->data;
    for (int i = 0; i < size; ++i) {
        *ddata++ += (*sdata++);
    }
}

heman_image* heman_ops_sobel(heman_image* img, heman_color rgb)
{
    int width = img->width;
    int height = img->height;
    assert(img->nbands == 3);
    heman_image* result = heman_image_create(width, height, 3);
    heman_image* gray = heman_color_to_grayscale(img);
    float inv = 1.0f / 255.0f;

    kmVec3 edge_rgb;
    edge_rgb.x = (float)(rgb >> 16) * inv;
    edge_rgb.y = (float)((rgb >> 8) & 0xff) * inv;
    edge_rgb.z = (float)(rgb & 0xff) * inv;

    int y;
#pragma omp parallel for
    for (y = 0; y < height; y++) {
        kmVec3* dst = (kmVec3*) result->data + y * width;
        const kmVec3* src = (kmVec3*) img->data + y * width;
        for (int x = 0; x < width; x++) {
            int xm1 = (x - 1 > 0 ? x - 1 : 0);
            int xp1 = (x + 1 > width - 1 ? width - 1 : x + 1);
            int ym1 = (y - 1 > 0 ? y - 1 : 0);
            int yp1 = (y + 1 > height - 1 ? height - 1 : y + 1);
            float t00 = *heman_image_texel(gray, xm1, ym1);
            float t10 = *heman_image_texel(gray, x, ym1);
            float t20 = *heman_image_texel(gray, xp1, ym1);
            float t01 = *heman_image_texel(gray, xm1, 0);
            float t21 = *heman_image_texel(gray, xp1, 0);
            float t02 = *heman_image_texel(gray, xm1, yp1);
            float t12 = *heman_image_texel(gray, x, yp1);
            float t22 = *heman_image_texel(gray, xp1, yp1);
            float gx = t00 + 2.0 * t01 + t02 - t20 - 2.0 * t21 - t22;
            float gy = t00 + 2.0 * t10 + t20 - t02 - 2.0 * t12 - t22;
            float is_edge = gx * gx + gy * gy > 1e-5;
            kmVec3Lerp(dst++, src++, &edge_rgb, is_edge);
        }
    }

    heman_image_destroy(gray);
    return result;
}

heman_image* heman_ops_warp_core(
    heman_image* img, heman_image* secondary, int seed, int octaves)
{
    struct osn_context* ctx;
    open_simplex_noise(seed, &ctx);
    int width = img->width;
    int height = img->height;
    int nbands = img->nbands;
    heman_image* result = heman_image_create(width, height, nbands);
    heman_image* result2 =
        secondary ? heman_image_create(width, height, secondary->nbands) : 0;
    float invw = 1.0 / width;
    float invh = 1.0 / height;
    float inv = (invw > invh ? invh : invw);
    float aspect = (float) width / height;
    float gain = 0.6;
    float lacunarity = 2.0;
    float initial_amplitude = 0.05;
    float initial_frequency = 8.0;

    int y;
#pragma omp parallel for
    for (y = 0; y < height; y++) {
        float* dst = result->data + y * width * nbands;
        for (int x = 0; x < width; x++) {
            float a = initial_amplitude;
            float f = initial_frequency;

            float* src;



            if (nbands == 4) {
                src = heman_image_texel(img, x, y);
                float elev = 1 - src[3];
                a *= pow(elev, 4);
            }

            float s = x * inv;
            float t = y * inv;
            float u = x * invw;
            float v = y * invh;
            for (int i = 0; i < octaves; i++) {
                u += (a * open_simplex_noise2(ctx, s * f, t * f));
                v += aspect * (a * open_simplex_noise2(ctx, s * f + 0.5, t * f));
                a *= gain;
                f *= lacunarity;
            }
            int i = (0 > (width - 1 > u * width ? u * width : width - 1) ? 0 : (width - 1 > u * width ? u * width : width - 1));
            int j = (0 > (height - 1 > v * height ? v * height : height - 1) ? 0 : (height - 1 > v * height ? v * height : height - 1));
            src = heman_image_texel(img, i, j);
            for (int n = 0; n < nbands; n++) {
                *dst++ = *src++;
            }
            if (secondary) {
                src = heman_image_texel(secondary, x, y);
                float* dst2 = heman_image_texel(result2, i, j);
                for (int n = 0; n < secondary->nbands; n++) {
                    *dst2++ = *src++;
                }
            }
        }
    }
    open_simplex_noise_free(ctx);
    if (secondary) {
        free(secondary->data);
        secondary->data = result2->data;
        free(result2);
    }
    return result;
}

heman_image* heman_ops_warp_points(
    heman_image* img, int seed, int octaves, heman_points* pts)
{
    int width = img->width;
    int height = img->height;
    heman_image* mapping = heman_distance_identity_cpcf(width, height);
    heman_image* retval = heman_ops_warp_core(img, mapping, seed, octaves);
    float* src = pts->data;
    for (int k = 0; k < pts->width; k++, src += pts->nbands) {
        float x = src[0];
        float y = src[1];
        int i = x * mapping->width;
        int j = y * mapping->height;
        if (i < 0 || i >= mapping->width || j < 0 || j >= mapping->height) {
            continue;
        }
        float* texel = heman_image_texel(mapping, i, j);
        src[0] = texel[0] / mapping->width;
        src[1] = texel[1] / mapping->height;
    }
    heman_image_destroy(mapping);
    return retval;
}

heman_image* heman_ops_warp(heman_image* img, int seed, int octaves)
{
    return heman_ops_warp_core(img, 0, seed, octaves);
}

heman_image* heman_ops_extract_mask(
    heman_image* source, heman_color color, int invert)
{
    assert(source->nbands == 3);
    float inv = 1.0f / 255.0f;
    float r = (float)(color >> 16) * inv;
    float g = (float)((color >> 8) & 0xff) * inv;
    float b = (float)(color & 0xff) * inv;
    int height = source->height;
    int width = source->width;
    heman_image* result = heman_image_create(width, height, 1);

    int y;
#pragma omp parallel for
    for (y = 0; y < height; y++) {
        float* dst = result->data + y * width;
        float* src = source->data + y * width * 3;
        for (int x = 0; x < width; x++, src += 3) {
            float val = ((src[0] == r) && (src[1] == g) && (src[2] == b));
            if (!invert) {
                val = 1 - val;
            }
            *dst++ = val;
        }
    }

    return result;
}

heman_image* heman_ops_replace_color(
    heman_image* source, heman_color color, heman_image* texture)
{
    assert(source->nbands == 3);
    assert(texture->nbands == 3);
    int height = source->height;
    int width = source->width;
    assert(texture->width == width);
    assert(texture->height == height);
    float inv = 1.0f / 255.0f;
    float r = (float)(color >> 16) * inv;
    float g = (float)((color >> 8) & 0xff) * inv;
    float b = (float)(color & 0xff) * inv;
    heman_image* result = heman_image_create(width, height, 3);

    int y;
#pragma omp parallel for
    for (y = 0; y < height; y++) {
        float* dst = result->data + y * width * 3;
        float* src = source->data + y * width * 3;
        float* tex = texture->data + y * width * 3;
        for (int x = 0; x < width; x++, src += 3, dst += 3, tex += 3) {
            if ((src[0] == r) && (src[1] == g) && (src[2] == b)) {
                dst[0] = tex[0];
                dst[1] = tex[1];
                dst[2] = tex[2];
            } else {
                dst[0] = src[0];
                dst[1] = src[1];
                dst[2] = src[2];
            }
        }
    }

    return result;
}

static int _match(
    heman_image* mask, heman_color mask_color, int invert_mask, int pixel_index)
{
    float* mcolor = mask->data + pixel_index * 3;
    unsigned char r1 = mcolor[0] * 255;
    unsigned char g1 = mcolor[1] * 255;
    unsigned char b1 = mcolor[2] * 255;
    unsigned char r2 = mask_color >> 16;
    unsigned char g2 = (mask_color >> 8) & 0xff;
    unsigned char b2 = (mask_color & 0xff);
    int retval = r1 == r2 && g1 == g2 && b1 == b2;
    return invert_mask ? (1 - retval) : retval;
}

static float qselect(float* v, int len, int k)
{
    int i, st;
    for (st = i = 0; i < len - 1; i++) {
        if (v[i] > v[len - 1]) {
            continue;
        }
        {float _=v[i];v[i]=v[st];v[st]=_;};
        st++;
    }
    {float _=v[len - 1];v[len - 1]=v[st];v[st]=_;};
    return k == st ? v[st]
           : st > k ? qselect(v, st, k)
                    : qselect(v + st, len - st, k - st);
}

heman_image* heman_ops_percentiles(heman_image* hmap, int nsteps,
    heman_image* mask, heman_color mask_color, int invert_mask,
    float offset)
{
    assert(hmap->nbands == 1);
    assert(!mask || mask->nbands == 3);
    int size = hmap->height * hmap->width;
    float* src = hmap->data;
    float minv = 1000;
    float maxv = -1000;
    int npixels = 0;
    for (int i = 0; i < size; ++i) {
        if (!mask || _match(mask, mask_color, invert_mask, i)) {
            minv = (minv > src[i] ? src[i] : minv);
            maxv = (maxv > src[i] ? maxv : src[i]);
            npixels++;
        }
    }

    float* vals = malloc(sizeof(float) * npixels);
    npixels = 0;
    for (int i = 0; i < size; ++i) {
        if (!mask || _match(mask, mask_color, invert_mask, i)) {
            vals[npixels++] = src[i];
        }
    }
    float* percentiles = malloc(sizeof(float) * nsteps);
    for (int tier = 0; tier < nsteps; tier++) {
        float height = qselect(vals, npixels, tier * npixels / nsteps);
        percentiles[tier] = height;
    }
    free(vals);

    for (int i = 0; i < size; ++i) {
        float e = *src;
        if (!mask || _match(mask, mask_color, invert_mask, i)) {
            for (int tier = nsteps - 1; tier >= 0; tier--) {
                if (e > percentiles[tier]) {
                    e = percentiles[tier];
                    break;
                }
            }
        }
        *src++ = e + offset;
    }
    free(percentiles);

    return hmap;
}

heman_image* heman_ops_stairstep(heman_image* hmap, int nsteps,
    heman_image* mask, heman_color mask_color, int invert_mask,
    float offset)
{
    assert(hmap->nbands == 1);
    assert(!mask || mask->nbands == 3);
    int size = hmap->height * hmap->width;
    float* src = hmap->data;
    float minv = 1000;
    float maxv = -1000;
    for (int i = 0; i < size; ++i) {
        if (!mask || _match(mask, mask_color, invert_mask, i)) {
            minv = (minv > src[i] ? src[i] : minv);
            maxv = (maxv > src[i] ? maxv : src[i]);
        }
    }
    float range = maxv - minv;
    for (int i = 0; i < size; ++i) {
        float e = *src;
        if (!mask || _match(mask, mask_color, invert_mask, i)) {
            e = e - minv;
            e /= range;
            e = floor(e * nsteps) / nsteps;
            e = e * range + minv;
        }
        *src++ = e + offset;
    }
    return hmap;
}

heman_image* heman_ops_merge_political(
    heman_image* hmap, heman_image* cmap, heman_color ocean)
{
    assert(hmap->nbands == 1);
    assert(cmap->nbands == 3);
    heman_image* result = heman_image_create(hmap->width, hmap->height, 4);
    float* pheight = hmap->data;
    float* pcolour = cmap->data;
    float* pmerged = result->data;
    float inv = 1.0f / 255.0f;
    float oceanr = (float)(ocean >> 16) * inv;
    float oceang = (float)((ocean >> 8) & 0xff) * inv;
    float oceanb = (float)(ocean & 0xff) * inv;
    int size = hmap->height * hmap->width;
    float minh = 1000;
    float maxh = -1000;
    for (int i = 0; i < size; ++i) {
        minh = (minh > pheight[i] ? pheight[i] : minh);
        maxh = (maxh > pheight[i] ? pheight[i] : maxh);
    }
    for (int i = 0; i < size; ++i) {
        float h = *pheight++;
        if (h < 0) {
            *pmerged++ = oceanr;
            *pmerged++ = oceang;
            *pmerged++ = oceanb;
            pcolour += 3;
        } else {
            *pmerged++ = *pcolour++;
            *pmerged++ = *pcolour++;
            *pmerged++ = *pcolour++;
        }
        *pmerged++ = (h - minh) / (maxh - minh);
    }
    return result;
}

heman_image* heman_ops_emboss(heman_image* img, int mode)
{
    int seed = 1;
    int octaves = 4;

    struct osn_context* ctx;
    open_simplex_noise(seed, &ctx);
    int width = img->width;
    int height = img->height;
    assert(img->nbands == 1);
    heman_image* result = heman_image_create(width, height, 1);
    float invw = 1.0 / width;
    float invh = 1.0 / height;
    float inv = (invw > invh ? invh : invw);
    float gain = 0.6;
    float lacunarity = 2.0;
    float land_amplitude = 0.0005;
    float land_frequency = 256.0;
    float ocean_amplitude = 0.5;
    float ocean_frequency = 1.0;

    int y;
#pragma omp parallel for
    for (y = 0; y < height; y++) {
        float* dst = result->data + y * width;
        for (int x = 0; x < width; x++) {
            float z = *heman_image_texel(img, x, y);
            if (z > 0 && mode == 1) {
                float s = x * inv;
                float t = y * inv;
                float a = land_amplitude;
                float f = land_frequency;
                for (int i = 0; i < octaves; i++) {
                    z += (a * open_simplex_noise2(ctx, s * f, t * f));
                    a *= gain;
                    f *= lacunarity;
                }
            } else if (z <= 0 && mode == -1) {
                z = (z > -0.1 ? z : -0.1);
                float soften = fabsf(z);
                float s = x * inv;
                float t = y * inv;
                float a = ocean_amplitude;
                float f = ocean_frequency;
                for (int i = 0; i < octaves; i++) {
                    z += soften * (a * open_simplex_noise2(ctx, s * f, t * f));
                    a *= gain;
                    f *= lacunarity;
                }
            }
            *dst++ = z;
        }
    }

    open_simplex_noise_free(ctx);
    return result;
}
