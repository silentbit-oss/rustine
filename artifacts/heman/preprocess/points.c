# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/points.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/points.c"
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
# 2 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/points.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 2
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
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 2
# 3 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/points.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/memory.h" 1
# 4 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/points.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 1
# 5 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/points.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 1
# 6 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/points.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/./kazmath/vec2.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/./kazmath/vec2.h"
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
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/./kazmath/vec2.h" 2

struct kmMat3;

#pragma pack(push)
#pragma pack(1)
typedef struct kmVec2 {
    float x;
    float y;
} kmVec2;

#pragma pack(pop)





kmVec2* kmVec2Fill(kmVec2* pOut, float x, float y);
float kmVec2Length(const kmVec2* pIn);
float kmVec2LengthSq(const kmVec2* pIn);
kmVec2* kmVec2Normalize(kmVec2* pOut, const kmVec2* pIn);
kmVec2* kmVec2Lerp(kmVec2* pOut, const kmVec2* pV1, const kmVec2* pV2, float t);
kmVec2* kmVec2Add(kmVec2* pOut, const kmVec2* pV1, const kmVec2* pV2);
float kmVec2Dot(const kmVec2* pV1, const kmVec2* pV2);
float kmVec2Cross(const kmVec2* pV1, const kmVec2* pV2);
kmVec2* kmVec2Subtract(kmVec2* pOut, const kmVec2* pV1, const kmVec2* pV2);
kmVec2* kmVec2Mul( kmVec2* pOut,const kmVec2* pV1, const kmVec2* pV2 );
kmVec2* kmVec2Div( kmVec2* pOut,const kmVec2* pV1, const kmVec2* pV2 );
kmVec2* kmVec2Transform(kmVec2* pOut, const kmVec2* pV1, const struct kmMat3* pM);
kmVec2* kmVec2TransformCoord(kmVec2* pOut, const kmVec2* pV, const struct kmMat3* pM);
kmVec2* kmVec2Scale(kmVec2* pOut, const kmVec2* pIn, const float s);
int kmVec2AreEqual(const kmVec2* p1, const kmVec2* p2);
kmVec2* kmVec2Assign(kmVec2* pOut, const kmVec2* pIn);
kmVec2* kmVec2RotateBy(kmVec2* pOut, const kmVec2* pIn, const float degrees, const kmVec2* center);
float kmVec2DegreesBetween(const kmVec2* v1, const kmVec2* v2);
float kmVec2DistanceBetween(const kmVec2* v1, const kmVec2* v2);
kmVec2* kmVec2MidPointBetween(kmVec2* pOut, const kmVec2* v1, const kmVec2* v2);
kmVec2* kmVec2Reflect(kmVec2* pOut, const kmVec2* pIn, const kmVec2* normal);

extern const kmVec2 KM_VEC2_POS_Y;
extern const kmVec2 KM_VEC2_NEG_Y;
extern const kmVec2 KM_VEC2_NEG_X;
extern const kmVec2 KM_VEC2_POS_X;
extern const kmVec2 KM_VEC2_ZERO;
# 7 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/points.c" 2


unsigned int randhash(unsigned int seed)
{
    unsigned int i = (seed ^ 12345391u) * 2654435769u;
    i ^= (i << 6) ^ (i >> 26);
    i *= 2654435769u;
    i += (i << 5) ^ (i >> 12);
    return i;
}

float randhashf(unsigned int seed, float a, float b)
{
    return (b - a) * randhash(seed) / (float) 4294967295U + a;
}

heman_image* heman_points_create(float* xy, int npoints, int nbands)
{
    heman_points* img = malloc(sizeof(heman_image));
    img->width = npoints;
    img->height = 1;
    img->nbands = nbands;
    int nbytes = sizeof(float) * npoints * nbands;
    img->data = malloc(nbytes);
    memcpy(img->data, xy, nbytes);
    return img;
}

void heman_points_destroy(heman_points* img)
{
    free(img->data);
    free(img);
}

heman_points* heman_points_from_grid(float width, float height,
    float cellsize, float jitter)
{
    int cols = width / cellsize;
    int rows = height / cellsize;
    int ncells = cols * rows;
    heman_points* result = heman_image_create(ncells, 1, 2);
    float rscale = 2.0 * jitter / (float) 32767;





    int j;
#pragma omp parallel for
    for (j = 0; j < rows; j++) {
        float* dst = result->data + j * cols * 2;
        float y = cellsize * 0.5 + cellsize * j;
        float x = cellsize * 0.5;
        for (int i = 0; i < cols; i++) {
            float rx = rand() * rscale - jitter;
            float ry = rand() * rscale - jitter;
            *dst++ = x + rx;
            *dst++ = y + ry;
            x += cellsize;
        }
    }

    return result;
}

kmVec2 sample_annulus(float radius, kmVec2 center, unsigned int* seedptr)
{
    unsigned int seed = *seedptr;
    kmVec2 r;
    float rscale = 1.0f / 4294967295U;
    while (1) {
        r.x = 4 * rscale * randhash(seed++) - 2;
        r.y = 4 * rscale * randhash(seed++) - 2;
        float r2 = kmVec2LengthSq(&r);
        if (r2 > 1 && r2 <= 4) {
            break;
        }
    }
    *seedptr = seed;
    kmVec2Scale(&r, &r, radius);
    kmVec2Add(&r, &r, &center);
    return r;
}






heman_points* heman_points_from_poisson(
    float width, float height, float radius)
{
    int maxattempts = 30;
    float rscale = 1.0f / 4294967295U;
    unsigned int seed = 0;
    kmVec2 rvec;
    rvec.x = rvec.y = radius;
    float r2 = radius * radius;


    float cellsize = radius / sqrtf(2);
    float invcell = 1.0f / cellsize;
    int ncols = ceil(width * invcell);
    int nrows = ceil(height * invcell);
    int maxcol = ncols - 1;
    int maxrow = nrows - 1;
    int ncells = ncols * nrows;
    int* grid = malloc(ncells * sizeof(int));
    for (int i = 0; i < ncells; i++) {
        grid[i] = -1;
    }


    int* actives = malloc(ncells * sizeof(int));
    int nactives = 0;
    heman_points* result = heman_image_create(ncells, 1, 2);
    kmVec2* samples = (kmVec2*) result->data;
    int nsamples = 0;


    kmVec2 pt;
    pt.x = width * randhash(seed++) * rscale;
    pt.y = height * randhash(seed++) * rscale;
    grid[(int) (pt.x * invcell) + ncols * (int) (pt.y * invcell)] = actives[nactives++] = nsamples;
    samples[nsamples++] = pt;

    while (nsamples < ncells) {
        int aindex = (randhashf(seed++, 0, nactives) > nactives - 1 ? nactives - 1 : randhashf(seed++, 0, nactives));
        int sindex = actives[aindex];
        int found = 0;
        kmVec2 j, minj, maxj, delta;
        int attempt;
        for (attempt = 0; attempt < maxattempts && !found; attempt++) {
            pt = sample_annulus(radius, samples[sindex], &seed);


            if (pt.x < 0 || pt.x >= width || pt.y < 0 || pt.y >= height) {
                continue;
            }


            minj = maxj = pt;
            kmVec2Add(&maxj, &maxj, &rvec);
            kmVec2Subtract(&minj, &minj, &rvec);
            kmVec2Scale(&minj, &minj, invcell);
            kmVec2Scale(&maxj, &maxj, invcell);
            minj.x = (0 > (maxcol > (int) minj.x ? (int) minj.x : maxcol) ? 0 : (maxcol > (int) minj.x ? (int) minj.x : maxcol));
            maxj.x = (0 > (maxcol > (int) maxj.x ? (int) maxj.x : maxcol) ? 0 : (maxcol > (int) maxj.x ? (int) maxj.x : maxcol));
            minj.y = (0 > (maxrow > (int) minj.y ? (int) minj.y : maxrow) ? 0 : (maxrow > (int) minj.y ? (int) minj.y : maxrow));
            maxj.y = (0 > (maxrow > (int) maxj.y ? (int) maxj.y : maxrow) ? 0 : (maxrow > (int) maxj.y ? (int) maxj.y : maxrow));
            int reject = 0;
            for (j.y = minj.y; j.y <= maxj.y && !reject; j.y++) {
                for (j.x = minj.x; j.x <= maxj.x && !reject; j.x++) {
                    int entry = grid[(int) j.y * ncols + (int) j.x];
                    if (entry > -1 && entry != sindex) {
                        kmVec2Subtract(&delta, &samples[entry], &pt);
                        if (kmVec2LengthSq(&delta) < r2) {
                            reject = 1;
                        }
                    }
                }
            }
            if (reject) {
                continue;
            }
            found = 1;
        }
        if (found) {
            grid[(int) (pt.x * invcell) + ncols * (int) (pt.y * invcell)] = actives[nactives++] = nsamples;
            samples[nsamples++] = pt;
        } else {
            if (--nactives <= 0) {
                break;
            }
            actives[aindex] = actives[nactives];
        }
    }


    result->width = nsamples;

    free(grid);
    free(actives);
    return result;
}
# 212 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/points.c"
heman_points* heman_points_from_density(
    heman_image* density, float minradius, float maxradius)
{
    assert(density->nbands == 1);
    float width = 1, height = 1;
    int maxattempts = 30;
    float rscale = 1.0f / 4294967295U;
    unsigned int seed = 0;
    kmVec2 rvec;
    rvec.x = rvec.y = maxradius;
    int gindex;


    float cellsize = maxradius / sqrtf(2);
    float invcell = 1.0f / cellsize;
    int ncols = ceil(width * invcell);
    int nrows = ceil(height * invcell);
    int maxcol = ncols - 1;
    int maxrow = nrows - 1;
    int ncells = ncols * nrows;
    int ntexels = cellsize * density->width;
    int gcapacity = ntexels * ntexels;
    int* grid = malloc(ncells * sizeof(int) * gcapacity);
    int* ngrid = malloc(ncells * sizeof(int));
    for (int i = 0; i < ncells; i++) {
        ngrid[i] = 0;
    }


    int* actives = malloc(ncells * sizeof(int));
    int nactives = 0;
    int maxsamples = ncells * gcapacity;
    heman_points* result = heman_image_create(maxsamples, 1, 2);
    kmVec2* samples = (kmVec2*) result->data;
    int nsamples = 0;


    kmVec2 pt;
    pt.x = width * randhash(seed++) * rscale;
    pt.y = height * randhash(seed++) * rscale;
    actives[nactives++] = nsamples;
    gindex = ((int) (pt.x * invcell) + ncols * (int) (pt.y * invcell)); grid[gcapacity * gindex + ngrid[gindex]] = nsamples; ngrid[gindex]++;
    samples[nsamples++] = pt;

    while (nsamples < maxsamples) {
        int aindex = (randhashf(seed++, 0, nactives) > nactives - 1 ? nactives - 1 : randhashf(seed++, 0, nactives));
        int sindex = actives[aindex];
        int found = 0;
        kmVec2 j, minj, maxj, delta;
        int attempt;
        for (attempt = 0; attempt < maxattempts && !found; attempt++) {
            pt = sample_annulus(maxradius, samples[sindex], &seed);


            if (pt.x < 0 || pt.x >= width || pt.y < 0 || pt.y >= height) {
                continue;
            }


            minj = maxj = pt;
            kmVec2Add(&maxj, &maxj, &rvec);
            kmVec2Subtract(&minj, &minj, &rvec);
            kmVec2Scale(&minj, &minj, invcell);
            kmVec2Scale(&maxj, &maxj, invcell);
            minj.x = (0 > (maxcol > (int) minj.x ? (int) minj.x : maxcol) ? 0 : (maxcol > (int) minj.x ? (int) minj.x : maxcol));
            maxj.x = (0 > (maxcol > (int) maxj.x ? (int) maxj.x : maxcol) ? 0 : (maxcol > (int) maxj.x ? (int) maxj.x : maxcol));
            minj.y = (0 > (maxrow > (int) minj.y ? (int) minj.y : maxrow) ? 0 : (maxrow > (int) minj.y ? (int) minj.y : maxrow));
            maxj.y = (0 > (maxrow > (int) maxj.y ? (int) maxj.y : maxrow) ? 0 : (maxrow > (int) maxj.y ? (int) maxj.y : maxrow));
            int reject = 0;

            float densityval;
            heman_image_sample(density, pt.x, pt.y, &densityval);



            densityval = sqrt(densityval);

            float mindist = maxradius - densityval * (maxradius - minradius);
            float r2 = mindist * mindist;

            for (j.y = minj.y; j.y <= maxj.y && !reject; j.y++) {
                for (j.x = minj.x; j.x <= maxj.x && !reject; j.x++) {
                    for (int g = (((int) j.y * ncols + (int) j.x) * gcapacity); g < ((((int) j.y * ncols + (int) j.x) * gcapacity) + ngrid[((int) j.y * ncols + (int) j.x)]); ++g) {
                        int entry = grid[g];
                        if (entry != sindex) {
                            kmVec2Subtract(&delta, &samples[entry], &pt);
                            if (kmVec2LengthSq(&delta) < r2) {
                                reject = 1;
                            }
                        }
                    }
                }
            }
            if (reject) {
                continue;
            }
            found = 1;
        }
        if (found && ngrid[((int) (pt.x * invcell) + ncols * (int) (pt.y * invcell))] >= gcapacity) {
            found = 0;
        }
        if (found) {
            actives[nactives++] = nsamples;
            gindex = ((int) (pt.x * invcell) + ncols * (int) (pt.y * invcell)); grid[gcapacity * gindex + ngrid[gindex]] = nsamples; ngrid[gindex]++;
            samples[nsamples++] = pt;
        } else {
            if (--nactives <= 0) {
                break;
            }
            actives[aindex] = actives[nactives];
        }
    }



    result->width = nsamples;

    free(grid);
    free(ngrid);
    free(actives);
    return result;
}
# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/points.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/points.c"
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
# 2 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/points.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 2
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
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 2
# 3 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/points.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/memory.h" 1
# 4 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/points.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 1
# 5 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/points.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 1
# 6 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/points.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/./kazmath/vec2.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/./kazmath/vec2.h"
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
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/./kazmath/vec2.h" 2

struct kmMat3;

#pragma pack(push)
#pragma pack(1)
typedef struct kmVec2 {
    float x;
    float y;
} kmVec2;

#pragma pack(pop)





kmVec2* kmVec2Fill(kmVec2* pOut, float x, float y);
float kmVec2Length(const kmVec2* pIn);
float kmVec2LengthSq(const kmVec2* pIn);
kmVec2* kmVec2Normalize(kmVec2* pOut, const kmVec2* pIn);
kmVec2* kmVec2Lerp(kmVec2* pOut, const kmVec2* pV1, const kmVec2* pV2, float t);
kmVec2* kmVec2Add(kmVec2* pOut, const kmVec2* pV1, const kmVec2* pV2);
float kmVec2Dot(const kmVec2* pV1, const kmVec2* pV2);
float kmVec2Cross(const kmVec2* pV1, const kmVec2* pV2);
kmVec2* kmVec2Subtract(kmVec2* pOut, const kmVec2* pV1, const kmVec2* pV2);
kmVec2* kmVec2Mul( kmVec2* pOut,const kmVec2* pV1, const kmVec2* pV2 );
kmVec2* kmVec2Div( kmVec2* pOut,const kmVec2* pV1, const kmVec2* pV2 );
kmVec2* kmVec2Transform(kmVec2* pOut, const kmVec2* pV1, const struct kmMat3* pM);
kmVec2* kmVec2TransformCoord(kmVec2* pOut, const kmVec2* pV, const struct kmMat3* pM);
kmVec2* kmVec2Scale(kmVec2* pOut, const kmVec2* pIn, const float s);
int kmVec2AreEqual(const kmVec2* p1, const kmVec2* p2);
kmVec2* kmVec2Assign(kmVec2* pOut, const kmVec2* pIn);
kmVec2* kmVec2RotateBy(kmVec2* pOut, const kmVec2* pIn, const float degrees, const kmVec2* center);
float kmVec2DegreesBetween(const kmVec2* v1, const kmVec2* v2);
float kmVec2DistanceBetween(const kmVec2* v1, const kmVec2* v2);
kmVec2* kmVec2MidPointBetween(kmVec2* pOut, const kmVec2* v1, const kmVec2* v2);
kmVec2* kmVec2Reflect(kmVec2* pOut, const kmVec2* pIn, const kmVec2* normal);

extern const kmVec2 KM_VEC2_POS_Y;
extern const kmVec2 KM_VEC2_NEG_Y;
extern const kmVec2 KM_VEC2_NEG_X;
extern const kmVec2 KM_VEC2_POS_X;
extern const kmVec2 KM_VEC2_ZERO;
# 7 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/points.c" 2


unsigned int randhash(unsigned int seed)
{
    unsigned int i = (seed ^ 12345391u) * 2654435769u;
    i ^= (i << 6) ^ (i >> 26);
    i *= 2654435769u;
    i += (i << 5) ^ (i >> 12);
    return i;
}

float randhashf(unsigned int seed, float a, float b)
{
    return (b - a) * randhash(seed) / (float) 4294967295U + a;
}

heman_image* heman_points_create(float* xy, int npoints, int nbands)
{
    heman_points* img = malloc(sizeof(heman_image));
    img->width = npoints;
    img->height = 1;
    img->nbands = nbands;
    int nbytes = sizeof(float) * npoints * nbands;
    img->data = malloc(nbytes);
    memcpy(img->data, xy, nbytes);
    return img;
}

void heman_points_destroy(heman_points* img)
{
    free(img->data);
    free(img);
}

heman_points* heman_points_from_grid(float width, float height,
    float cellsize, float jitter)
{
    int cols = width / cellsize;
    int rows = height / cellsize;
    int ncells = cols * rows;
    heman_points* result = heman_image_create(ncells, 1, 2);
    float rscale = 2.0 * jitter / (float) 32767;





    int j;
#pragma omp parallel for
    for (j = 0; j < rows; j++) {
        float* dst = result->data + j * cols * 2;
        float y = cellsize * 0.5 + cellsize * j;
        float x = cellsize * 0.5;
        for (int i = 0; i < cols; i++) {
            float rx = rand() * rscale - jitter;
            float ry = rand() * rscale - jitter;
            *dst++ = x + rx;
            *dst++ = y + ry;
            x += cellsize;
        }
    }

    return result;
}

kmVec2 sample_annulus(float radius, kmVec2 center, unsigned int* seedptr)
{
    unsigned int seed = *seedptr;
    kmVec2 r;
    float rscale = 1.0f / 4294967295U;
    while (1) {
        r.x = 4 * rscale * randhash(seed++) - 2;
        r.y = 4 * rscale * randhash(seed++) - 2;
        float r2 = kmVec2LengthSq(&r);
        if (r2 > 1 && r2 <= 4) {
            break;
        }
    }
    *seedptr = seed;
    kmVec2Scale(&r, &r, radius);
    kmVec2Add(&r, &r, &center);
    return r;
}






heman_points* heman_points_from_poisson(
    float width, float height, float radius)
{
    int maxattempts = 30;
    float rscale = 1.0f / 4294967295U;
    unsigned int seed = 0;
    kmVec2 rvec;
    rvec.x = rvec.y = radius;
    float r2 = radius * radius;


    float cellsize = radius / sqrtf(2);
    float invcell = 1.0f / cellsize;
    int ncols = ceil(width * invcell);
    int nrows = ceil(height * invcell);
    int maxcol = ncols - 1;
    int maxrow = nrows - 1;
    int ncells = ncols * nrows;
    int* grid = malloc(ncells * sizeof(int));
    for (int i = 0; i < ncells; i++) {
        grid[i] = -1;
    }


    int* actives = malloc(ncells * sizeof(int));
    int nactives = 0;
    heman_points* result = heman_image_create(ncells, 1, 2);
    kmVec2* samples = (kmVec2*) result->data;
    int nsamples = 0;


    kmVec2 pt;
    pt.x = width * randhash(seed++) * rscale;
    pt.y = height * randhash(seed++) * rscale;
    grid[(int) (pt.x * invcell) + ncols * (int) (pt.y * invcell)] = actives[nactives++] = nsamples;
    samples[nsamples++] = pt;

    while (nsamples < ncells) {
        int aindex = (randhashf(seed++, 0, nactives) > nactives - 1 ? nactives - 1 : randhashf(seed++, 0, nactives));
        int sindex = actives[aindex];
        int found = 0;
        kmVec2 j, minj, maxj, delta;
        int attempt;
        for (attempt = 0; attempt < maxattempts && !found; attempt++) {
            pt = sample_annulus(radius, samples[sindex], &seed);


            if (pt.x < 0 || pt.x >= width || pt.y < 0 || pt.y >= height) {
                continue;
            }


            minj = maxj = pt;
            kmVec2Add(&maxj, &maxj, &rvec);
            kmVec2Subtract(&minj, &minj, &rvec);
            kmVec2Scale(&minj, &minj, invcell);
            kmVec2Scale(&maxj, &maxj, invcell);
            minj.x = (0 > (maxcol > (int) minj.x ? (int) minj.x : maxcol) ? 0 : (maxcol > (int) minj.x ? (int) minj.x : maxcol));
            maxj.x = (0 > (maxcol > (int) maxj.x ? (int) maxj.x : maxcol) ? 0 : (maxcol > (int) maxj.x ? (int) maxj.x : maxcol));
            minj.y = (0 > (maxrow > (int) minj.y ? (int) minj.y : maxrow) ? 0 : (maxrow > (int) minj.y ? (int) minj.y : maxrow));
            maxj.y = (0 > (maxrow > (int) maxj.y ? (int) maxj.y : maxrow) ? 0 : (maxrow > (int) maxj.y ? (int) maxj.y : maxrow));
            int reject = 0;
            for (j.y = minj.y; j.y <= maxj.y && !reject; j.y++) {
                for (j.x = minj.x; j.x <= maxj.x && !reject; j.x++) {
                    int entry = grid[(int) j.y * ncols + (int) j.x];
                    if (entry > -1 && entry != sindex) {
                        kmVec2Subtract(&delta, &samples[entry], &pt);
                        if (kmVec2LengthSq(&delta) < r2) {
                            reject = 1;
                        }
                    }
                }
            }
            if (reject) {
                continue;
            }
            found = 1;
        }
        if (found) {
            grid[(int) (pt.x * invcell) + ncols * (int) (pt.y * invcell)] = actives[nactives++] = nsamples;
            samples[nsamples++] = pt;
        } else {
            if (--nactives <= 0) {
                break;
            }
            actives[aindex] = actives[nactives];
        }
    }


    result->width = nsamples;

    free(grid);
    free(actives);
    return result;
}
# 212 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/points.c"
heman_points* heman_points_from_density(
    heman_image* density, float minradius, float maxradius)
{
    assert(density->nbands == 1);
    float width = 1, height = 1;
    int maxattempts = 30;
    float rscale = 1.0f / 4294967295U;
    unsigned int seed = 0;
    kmVec2 rvec;
    rvec.x = rvec.y = maxradius;
    int gindex;


    float cellsize = maxradius / sqrtf(2);
    float invcell = 1.0f / cellsize;
    int ncols = ceil(width * invcell);
    int nrows = ceil(height * invcell);
    int maxcol = ncols - 1;
    int maxrow = nrows - 1;
    int ncells = ncols * nrows;
    int ntexels = cellsize * density->width;
    int gcapacity = ntexels * ntexels;
    int* grid = malloc(ncells * sizeof(int) * gcapacity);
    int* ngrid = malloc(ncells * sizeof(int));
    for (int i = 0; i < ncells; i++) {
        ngrid[i] = 0;
    }


    int* actives = malloc(ncells * sizeof(int));
    int nactives = 0;
    int maxsamples = ncells * gcapacity;
    heman_points* result = heman_image_create(maxsamples, 1, 2);
    kmVec2* samples = (kmVec2*) result->data;
    int nsamples = 0;


    kmVec2 pt;
    pt.x = width * randhash(seed++) * rscale;
    pt.y = height * randhash(seed++) * rscale;
    actives[nactives++] = nsamples;
    gindex = ((int) (pt.x * invcell) + ncols * (int) (pt.y * invcell)); grid[gcapacity * gindex + ngrid[gindex]] = nsamples; ngrid[gindex]++;
    samples[nsamples++] = pt;

    while (nsamples < maxsamples) {
        int aindex = (randhashf(seed++, 0, nactives) > nactives - 1 ? nactives - 1 : randhashf(seed++, 0, nactives));
        int sindex = actives[aindex];
        int found = 0;
        kmVec2 j, minj, maxj, delta;
        int attempt;
        for (attempt = 0; attempt < maxattempts && !found; attempt++) {
            pt = sample_annulus(maxradius, samples[sindex], &seed);


            if (pt.x < 0 || pt.x >= width || pt.y < 0 || pt.y >= height) {
                continue;
            }


            minj = maxj = pt;
            kmVec2Add(&maxj, &maxj, &rvec);
            kmVec2Subtract(&minj, &minj, &rvec);
            kmVec2Scale(&minj, &minj, invcell);
            kmVec2Scale(&maxj, &maxj, invcell);
            minj.x = (0 > (maxcol > (int) minj.x ? (int) minj.x : maxcol) ? 0 : (maxcol > (int) minj.x ? (int) minj.x : maxcol));
            maxj.x = (0 > (maxcol > (int) maxj.x ? (int) maxj.x : maxcol) ? 0 : (maxcol > (int) maxj.x ? (int) maxj.x : maxcol));
            minj.y = (0 > (maxrow > (int) minj.y ? (int) minj.y : maxrow) ? 0 : (maxrow > (int) minj.y ? (int) minj.y : maxrow));
            maxj.y = (0 > (maxrow > (int) maxj.y ? (int) maxj.y : maxrow) ? 0 : (maxrow > (int) maxj.y ? (int) maxj.y : maxrow));
            int reject = 0;

            float densityval;
            heman_image_sample(density, pt.x, pt.y, &densityval);



            densityval = sqrt(densityval);

            float mindist = maxradius - densityval * (maxradius - minradius);
            float r2 = mindist * mindist;

            for (j.y = minj.y; j.y <= maxj.y && !reject; j.y++) {
                for (j.x = minj.x; j.x <= maxj.x && !reject; j.x++) {
                    for (int g = (((int) j.y * ncols + (int) j.x) * gcapacity); g < ((((int) j.y * ncols + (int) j.x) * gcapacity) + ngrid[((int) j.y * ncols + (int) j.x)]); ++g) {
                        int entry = grid[g];
                        if (entry != sindex) {
                            kmVec2Subtract(&delta, &samples[entry], &pt);
                            if (kmVec2LengthSq(&delta) < r2) {
                                reject = 1;
                            }
                        }
                    }
                }
            }
            if (reject) {
                continue;
            }
            found = 1;
        }
        if (found && ngrid[((int) (pt.x * invcell) + ncols * (int) (pt.y * invcell))] >= gcapacity) {
            found = 0;
        }
        if (found) {
            actives[nactives++] = nsamples;
            gindex = ((int) (pt.x * invcell) + ncols * (int) (pt.y * invcell)); grid[gcapacity * gindex + ngrid[gindex]] = nsamples; ngrid[gindex]++;
            samples[nsamples++] = pt;
        } else {
            if (--nactives <= 0) {
                break;
            }
            actives[aindex] = actives[nactives];
        }
    }



    result->width = nsamples;

    free(grid);
    free(ngrid);
    free(actives);
    return result;
}
