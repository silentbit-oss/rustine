# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/draw.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/draw.c"
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
# 2 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/draw.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 2
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
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 2
# 3 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/draw.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 4 "/home/enumclass/Documents/C2RustTranslation/bkp/heman/src/draw.c" 2

void heman_draw_points(heman_image* target, heman_points* pts, float val)
{
    float* src = pts->data;
    for (int k = 0; k < pts->width; k++) {
        float x = src[0];
        float y = src[1];
        src += pts->nbands;
        int i = x * target->width;
        int j = y * target->height;
        if (i < 0 || i >= target->width || j < 0 || j >= target->height) {
            continue;
        }
        float* texel = heman_image_texel(target, i, j);
        for (int c = 0; c < target->nbands; c++) {
            *texel++ = val;
        }
    }
}

void heman_draw_colored_points(
    heman_image* target, heman_points* pts, const heman_color* colors)
{
    assert(target->nbands == 3 || target->nbands == 4);
    float* src = pts->data;
    float inv = 1.0f / 255.0f;
    for (int k = 0; k < pts->width; k++) {
        float x = src[0];
        float y = src[1];
        src += pts->nbands;
        int i = x * target->width;
        int j = y * target->height;
        if (i < 0 || i >= target->width || j < 0 || j >= target->height) {
            continue;
        }
        float* texel = heman_image_texel(target, i, j);
        heman_color rgb = colors[k];
        *texel++ = (float)((rgb >> 16) & 0xff) * inv;
        *texel++ = (float)((rgb >> 8) & 0xff) * inv;
        *texel++ = (float)(rgb & 0xff) * inv;
        if (target->nbands == 4) {
            *texel = (float)(rgb >> 24) * inv;
        }
    }
}

void heman_draw_colored_circles(heman_image* target, heman_points* pts,
    int radius, const heman_color* colors)
{
    int fwidth = radius * 2 + 1;
    int radius2 = radius * radius;
    float* src = pts->data;
    float inv = 1.0f / 255.0f;
    int w = target->width;
    int h = target->height;
    for (int k = 0; k < pts->width; k++) {
        float x = src[0];
        float y = src[1];
        src += pts->nbands;
        int ii = x * w - radius;
        int jj = y * h - radius;
        for (int kj = 0; kj < fwidth; kj++) {
            for (int ki = 0; ki < fwidth; ki++) {
                int i = ii + ki;
                int j = jj + kj;
                int r2 = ((i - x * w) * (i - x * w)) + ((j - y * h) * (j - y * h));
                if (r2 > radius2) {
                    continue;
                }
                float* texel = heman_image_texel(target, i, j);
                heman_color rgb = colors[k];
                *texel++ = (float)(rgb >> 16) * inv;
                *texel++ = (float)((rgb >> 8) & 0xff) * inv;
                *texel = (float)(rgb & 0xff) * inv;
            }
        }
    }
}

void heman_draw_splats(
    heman_image* target, heman_points* pts, int radius, int blend_mode)
{
    int fwidth = radius * 2 + 1;
    float* gaussian_splat = malloc(fwidth * fwidth * sizeof(float));
    generate_gaussian_splat(gaussian_splat, fwidth);
    float* src = pts->data;
    int w = target->width;
    int h = target->height;
    for (int i = 0; i < pts->width; i++) {
        float x = *src++;
        float y = *src++;
        int ii = x * w - radius;
        int jj = y * h - radius;
        for (int kj = 0; kj < fwidth; kj++) {
            for (int ki = 0; ki < fwidth; ki++) {
                int i = ii + ki;
                int j = jj + kj;
                if (i < 0 || i >= w || j < 0 || j >= h) {
                    continue;
                }
                float* texel = heman_image_texel(target, i, j);
                for (int c = 0; c < target->nbands; c++) {
                    *texel++ += gaussian_splat[kj * fwidth + ki];
                }
            }
        }
    }
    free(gaussian_splat);
}

void heman_internal_draw_seeds(heman_image* target, heman_points* pts, int filterd);

void heman_draw_contour_from_points(heman_image* target, heman_points* coords,
    heman_color rgb, float mind, float maxd, int filterd)
{
    assert(target->nbands == 3 || target->nbands == 4);
    int width = target->width;
    int height = target->height;
    heman_image* seed = heman_image_create(width, height, 1);
    heman_image_clear(seed, 0);

    heman_internal_draw_seeds(seed, coords, filterd);

    float inv = 1.0f / 255.0f;
    float r = (float)((rgb >> 16) & 0xff) * inv;
    float g = (float)((rgb >> 8) & 0xff) * inv;
    float b = (float)(rgb & 0xff) * inv;
    float a = 1;
    if (target->nbands == 4) {
        a = (float)(rgb >> 24) * inv;
    }

    int y;
#pragma omp parallel for
    for (y = 0; y < height; y++) {
        float* dst = target->data + y * width * target->nbands;
        for (int x = 0; x < width; x++) {
            float dist = *heman_image_texel(seed, x, y);
            if (dist > mind && dist < maxd) {
                dst[0] = r;
                dst[1] = g;
                dst[2] = b;
                if (target->nbands == 4) {
                    dst[3] = a;
                }
            }
            dst += target->nbands;
        }
    }

    heman_points_destroy(seed);
}
