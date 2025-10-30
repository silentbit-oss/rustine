#include <assert.h>
#include <generate.c>
#include <heman.h>
#include <image.h>
#include <math.h>
#include <memory.h>
#include <noise.h>
#include <stdint.h>
#include <stdlib.h>
#include <utility.h>
#include <vec3.h>
typedef struct heman_image_s heman_image;
typedef struct heman_image_s heman_points;
typedef unsigned int heman_color;
typedef unsigned char heman_byte;
heman_image *heman_image_create(int width, int height, int nbands);
void heman_image_info(heman_image *, int *width, int *height, int *nbands);
float *heman_image_data(heman_image *);
void heman_image_array(heman_image *img, float **outview, int *n);
float *heman_image_texel(heman_image *, int x, int y);
void heman_image_sample(heman_image *, float u, float v, float *result);
void heman_image_clear(heman_image *, float value);
void heman_image_destroy(heman_image *);
heman_image *heman_image_extract_alpha(heman_image *);
heman_image *heman_image_extract_rgb(heman_image *);
heman_image *heman_color_create_gradient(int width, int num_colors, const int *cp_locations, const heman_color *cp_colors);
void heman_color_set_gamma(float f);
heman_image *heman_color_apply_gradient(heman_image *heightmap, float minheight, float maxheight, heman_image *gradient);
heman_image *heman_color_from_grayscale(heman_image *gray);
heman_image *heman_color_to_grayscale(heman_image *colorimg);
heman_image *heman_color_from_cpcf(heman_image *cfield, heman_image *texture);
heman_image *heman_generate_island_heightmap(int width, int height, int seed);
heman_image *heman_generate_rock_heightmap(int width, int height, int seed);
heman_image *heman_generate_planet_heightmap(int width, int height, int seed);
heman_image *heman_generate_archipelago_heightmap(int width, int height, heman_points *points, float noiseamt, int seed);
void heman_generate_archipelago_political(int width, int height, heman_points *points, const heman_color *colors, heman_color ocean, int seed, heman_image **elevation, heman_image **political, int elevation_mode);
heman_image *heman_generate_simplex_fbm(int width, int height, float frequency, float amplitude, int octaves, float lacunarity, float gain, int seed);
heman_image *heman_lighting_apply(heman_image *heightmap, heman_image *colorbuffer, float occlusion, float diffuse, float diffuse_softening, const float *light_position);
heman_image *heman_lighting_compute_normals(heman_image *heightmap);
heman_image *heman_lighting_compute_occlusion(heman_image *heightmap);
void heman_lighting_set_occlusion_scale(float s);
heman_image *heman_distance_create_sdf(heman_image *monochrome);
heman_image *heman_distance_create_df(heman_image *monochrome);
heman_image *heman_distance_create_cpcf(heman_image *seed);
heman_image *heman_distance_from_cpcf(heman_image *cf);
heman_image *heman_distance_identity_cpcf(int width, int height);
heman_image *heman_import_u8(int width, int height, int nbands, const heman_byte *source, float minval, float maxval);
void heman_export_ply(heman_image *, const char *filename);
void heman_export_with_colors_ply(heman_image *heightmap, heman_image *colors, const char *filename);
void heman_export_u8(heman_image *source, float minv, float maxv, heman_byte *outp);
heman_image *heman_ops_stitch_horizontal(heman_image **images, int count);
heman_image *heman_ops_stitch_vertical(heman_image **images, int count);
heman_image *heman_ops_normalize_f32(heman_image *source, float minval, float maxval);
heman_image *heman_ops_max(heman_image *imga, heman_image *imgb);
heman_image *heman_ops_step(heman_image *image, float threshold);
heman_image *heman_ops_stairstep(heman_image *image, int nsteps, heman_image *mask, heman_color mask_color, int invert_mask, float offset);
heman_image *heman_ops_percentiles(heman_image *image, int nsteps, heman_image *mask, heman_color mask_color, int invert_mask, float offset);
heman_image *heman_ops_sweep(heman_image *image);
heman_image *heman_ops_laplacian(heman_image *heightmap);
heman_image *heman_ops_sobel(heman_image *dst, heman_color edge_color);
void heman_ops_accumulate(heman_image *dst, heman_image *src);
heman_image *heman_ops_warp(heman_image *src, int seed, int octaves);
heman_image *heman_ops_warp_points(heman_image *src, int seed, int octaves, heman_points *pts);
heman_image *heman_ops_extract_mask(heman_image *src, heman_color color, int invert);
heman_image *heman_ops_replace_color(heman_image *src, heman_color color, heman_image *texture);
heman_image *heman_ops_merge_political(heman_image *elevation, heman_image *political, heman_color ocean_color);
heman_image *heman_ops_emboss(heman_image *elevation, int mode);
heman_image *heman_points_create(float *xy, int npoints, int nbands);
void heman_points_destroy(heman_points *);
heman_points *heman_points_from_grid(float width, float height, float cellsize, float jitter);
heman_points *heman_points_from_poisson(float width, float height, float mindist);
heman_points *heman_points_from_density(heman_image *density, float mindist, float maxdist);
void heman_draw_points(heman_image *target, heman_points *pts, float val);
void heman_draw_colored_points(heman_image *target, heman_points *coords, const heman_color *colors);
void heman_draw_colored_circles(heman_image *target, heman_points *pts, int radius, const heman_color *colors);
void heman_draw_splats(heman_image *target, heman_points *pts, int radius, int blend_mode);
void heman_draw_contour_from_points(heman_image *target, heman_points *coords, heman_color color, float mind, float maxd, int filterd);
int heman_get_num_threads();
struct heman_image_s
{
  int width;
  int height;
  int nbands;
  float *data;
};
extern float _gamma;
inline float smoothstep(float edge0, float edge1, float x)
{
  float t;
  t = (0.0f > ((1.0f > ((x - edge0) / (edge1 - edge0))) ? ((x - edge0) / (edge1 - edge0)) : (1.0f))) ? (0.0f) : ((1.0f > ((x - edge0) / (edge1 - edge0))) ? ((x - edge0) / (edge1 - edge0)) : (1.0f));
  return (t * t) * (3.0 - (2.0 * t));
}

void generate_gaussian_row(int *target, int fwidth);
void generate_gaussian_splat(float *target, int fwidth);

struct osn_context;
int open_simplex_noise(int64_t seed, struct osn_context **ctx);
void open_simplex_noise_free(struct osn_context *ctx);
int open_simplex_noise_init_perm(struct osn_context *ctx, int16_t p[], int nelements);
double open_simplex_noise2(struct osn_context *ctx, double x, double y);
double open_simplex_noise3(struct osn_context *ctx, double x, double y, double z);
double open_simplex_noise4(struct osn_context *ctx, double x, double y, double z, double w);
extern float kmSQR(float s);
extern float kmDegreesToRadians(float degrees);
extern float kmRadiansToDegrees(float radians);
extern float kmMin(float lhs, float rhs);
extern float kmMax(float lhs, float rhs);
extern unsigned char kmAlmostEqual(float lhs, float rhs);
extern float kmClamp(float x, float min, float max);
extern float kmLerp(float x, float y, float factor);
struct kmMat4;
struct kmMat3;
struct kmPlane;
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3;
kmVec3 *kmVec3Fill(kmVec3 *pOut, float x, float y, float z);
float kmVec3Length(const kmVec3 *pIn);
float kmVec3LengthSq(const kmVec3 *pIn);
kmVec3 *kmVec3Lerp(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2, float t);
kmVec3 *kmVec3Normalize(kmVec3 *pOut, const kmVec3 *pIn);
kmVec3 *kmVec3Cross(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2);
float kmVec3Dot(const kmVec3 *pV1, const kmVec3 *pV2);
kmVec3 *kmVec3Add(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2);
kmVec3 *kmVec3Subtract(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2);
kmVec3 *kmVec3Mul(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2);
kmVec3 *kmVec3Div(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2);
kmVec3 *kmVec3MultiplyMat3(kmVec3 *pOut, const kmVec3 *pV, const struct kmMat3 *pM);
kmVec3 *kmVec3MultiplyMat4(kmVec3 *pOut, const kmVec3 *pV, const struct kmMat4 *pM);
kmVec3 *kmVec3Transform(kmVec3 *pOut, const kmVec3 *pV1, const struct kmMat4 *pM);
kmVec3 *kmVec3TransformNormal(kmVec3 *pOut, const kmVec3 *pV, const struct kmMat4 *pM);
kmVec3 *kmVec3TransformCoord(kmVec3 *pOut, const kmVec3 *pV, const struct kmMat4 *pM);
kmVec3 *kmVec3Scale(kmVec3 *pOut, const kmVec3 *pIn, const float s);
int kmVec3AreEqual(const kmVec3 *p1, const kmVec3 *p2);
kmVec3 *kmVec3InverseTransform(kmVec3 *pOut, const kmVec3 *pV, const struct kmMat4 *pM);
kmVec3 *kmVec3InverseTransformNormal(kmVec3 *pOut, const kmVec3 *pVect, const struct kmMat4 *pM);
kmVec3 *kmVec3Assign(kmVec3 *pOut, const kmVec3 *pIn);
kmVec3 *kmVec3Zero(kmVec3 *pOut);
kmVec3 *kmVec3GetHorizontalAngle(kmVec3 *pOut, const kmVec3 *pIn);
kmVec3 *kmVec3RotationToDirection(kmVec3 *pOut, const kmVec3 *pIn, const kmVec3 *forwards);
kmVec3 *kmVec3ProjectOnToPlane(kmVec3 *pOut, const kmVec3 *point, const struct kmPlane *plane);
kmVec3 *kmVec3Reflect(kmVec3 *pOut, const kmVec3 *pIn, const kmVec3 *normal);
extern const kmVec3 KM_VEC3_NEG_Z;
extern const kmVec3 KM_VEC3_POS_Z;
extern const kmVec3 KM_VEC3_POS_Y;
extern const kmVec3 KM_VEC3_NEG_Y;
extern const kmVec3 KM_VEC3_NEG_X;
extern const kmVec3 KM_VEC3_POS_X;
extern const kmVec3 KM_VEC3_ZERO;
static const float SEALEVEL = 0.5;
static const float DEFAULT_STRENGTH = 0.6;
heman_image *heman_internal_generate_island_noise(int width, int height, int seed)
{
  struct osn_context *ctx;
  open_simplex_noise(seed, &ctx);
  heman_image *img = heman_image_create(width, height, 3);
  float *data = img->data;
  float invh = 1.0f / ((width > height) ? (width) : (height));
  float invw = 1.0f / ((width > height) ? (width) : (height));
  float freqs[] = {4.0, 16.0, 32.0, 64.0, 128.0};
  float ampls[] = {0.2, 0.1, 0.05, 0.025, 0.0125};
  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    float v = y * invh;
    float *dst = data + ((y * width) * 3);
    unsigned int dst_idx = 0;
    for (int x = 0; x < width; x += 1)
    {
      float u = x * invw;
      dst[dst_idx] = ((ampls[0] * open_simplex_noise2(ctx, u * freqs[0], v * freqs[0])) + (ampls[1] * open_simplex_noise2(ctx, u * freqs[1], v * freqs[1]))) + (ampls[2] * open_simplex_noise2(ctx, u * freqs[2], v * freqs[2]));
      dst_idx += 1;
      dst[dst_idx] = (ampls[3] * open_simplex_noise2(ctx, u * freqs[3], v * freqs[3])) + (ampls[4] * open_simplex_noise2(ctx, u * freqs[4], v * freqs[4]));
      dst_idx += 1;
      u += 0.5;
      dst[dst_idx] = (ampls[3] * open_simplex_noise2(ctx, u * freqs[3], v * freqs[3])) + (ampls[4] * open_simplex_noise2(ctx, u * freqs[4], v * freqs[4]));
      dst_idx += 1;
    }

  }

  open_simplex_noise_free(ctx);
  return img;
}

heman_image *heman_internal_generate_rock_noise(int width, int height, int seed)
{
  struct osn_context *ctx;
  open_simplex_noise(seed, &ctx);
  heman_image *img = heman_image_create(width, height, 1);
  float *data = img->data;
  float invh = 1.0f / ((width > height) ? (width) : (height));
  float invw = 1.0f / ((width > height) ? (width) : (height));
  float freqs[] = {2.0, 4.0, 16.0};
  float ampls[] = {0.2, 0.05, 0.01};
  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    float v = y * invh;
    float *dst = data + (y * width);
    unsigned int dst_idx = 0;
    for (int x = 0; x < width; x += 1)
    {
      float u = x * invw;
      dst[dst_idx] = ((ampls[0] * open_simplex_noise2(ctx, u * freqs[0], v * freqs[0])) + (ampls[1] * open_simplex_noise2(ctx, u * freqs[1], v * freqs[1]))) + (ampls[2] * open_simplex_noise2(ctx, u * freqs[2], v * freqs[2]));
      dst_idx += 1;
    }

  }

  open_simplex_noise_free(ctx);
  return img;
}

heman_image *heman_generate_island_heightmap(int width, int height, int seed)
{
  heman_image *noisetex = heman_internal_generate_island_noise(width, height, seed);
  heman_image *coastmask = heman_image_create(width, height, 1);
  float *data = coastmask->data;
  unsigned int data_idx = 0;
  float invh = 1.0f / height;
  float invw = 1.0f / width;
  int hh = height / 2;
  int hw = width / 2;
  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    helper_heman_generate_island_heightmap_1(width, noisetex, data, data_idx, invh, invw, hh, hw, y);
  }

  heman_image *heightmap = heman_distance_create_sdf(coastmask);
  heman_image_destroy(coastmask);
  heman_image *result = heman_image_create(width, height, 1);
  data_idx = result->data_idx;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    helper_heman_generate_island_heightmap_2(width, noisetex, data, data_idx, invh, invw, y, heightmap);
  }

  heman_image_destroy(noisetex);
  heman_image_destroy(heightmap);
  return result;
}

heman_image *heman_generate_rock_heightmap(int width, int height, int seed)
{
  heman_image *noisetex = heman_internal_generate_rock_noise(width, height, seed);
  heman_image *heightmap = heman_image_create(width, height, 1);
  float *data = heightmap->data;
  float invh = 1.0f / height;
  float invw = 1.0f / width;
  int hh = height / 2;
  int hw = width / 2;
  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    float vv = (y - hh) * invh;
    float *dst = data + (y * width);
    unsigned int dst_idx = 0;
    for (int x = 0; x < width; x += 1)
    {
      float v = y * invh;
      float u = x * invw;
      float n;
      heman_image_sample(noisetex, u, v, &n);
      u = (x - hw) * invw;
      v = vv;
      float r = 0.3 + n;
      if (((u * u) + (v * v)) > (r * r))
      {
        dst[dst_idx] = 0;
        dst_idx += 1;
        continue;
      }
      float z = sqrt(((r * r) - (u * u)) - (v * v));
      dst[dst_idx] = z;
      dst_idx += 1;
    }

  }

  heman_image_destroy(noisetex);
  return heightmap;
}

heman_image *heman_generate_simplex_fbm(int width, int height, float frequency, float amplitude, int octaves, float lacunarity, float gain, int seed)
{
  struct osn_context *ctx;
  open_simplex_noise(seed, &ctx);
  heman_image *img = heman_image_create(width, height, 1);
  float *data = img->data;
  float invh = 1.0f / height;
  float invw = 1.0f / width;
  float ampl = amplitude;
  float freq = frequency;
  memset(data, 0, ((sizeof(float)) * width) * height);
  while (octaves--)
  {
    int y;
    #pragma omp parallel for
    for (y = 0; y < height; y += 1)
    {
      float v = y * invh;
      float *dst = data + (y * width);
      unsigned int dst_idx = 0;
      for (int x = 0; x < width; x += 1)
      {
        float u = x * invw;
        dst[dst_idx] += ampl * open_simplex_noise2(ctx, u * freq, v * freq);
        dst_idx += 1;
      }

    }

    ampl *= gain;
    freq *= lacunarity;
  }

  open_simplex_noise_free(ctx);
  return img;
}

static void sphere(float u, float v, float r, kmVec3 *dst)
{
  dst->x = (r * sin(v)) * cos(u);
  dst->y = r * cos(v);
  dst->z = (r * (-sin(v))) * sin(u);
}

heman_image *heman_generate_planet_heightmap(int width, int height, int seed)
{
  struct osn_context *ctx;
  open_simplex_noise(seed, &ctx);
  heman_image *result = heman_image_create(width, height, 1);
  float scalex = (2.0f * 3.1415926535) / width;
  float scaley = 3.1415926535 / height;
  float invh = 1.0f / height;
  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    helper_heman_generate_planet_heightmap_1(width, ctx, result, scalex, scaley, invh, y);
  }

  open_simplex_noise_free(ctx);
  return result;
}

void heman_internal_draw_seeds(heman_image *target, heman_points *pts, int filterd)
{
  int radius = target->width / filterd;
  int fwidth = (radius * 2) + 1;
  float *src = pts->data;
  unsigned int src_idx = 0;
  int w = target->width;
  int h = target->height;
  for (int i = 0; i < pts->width; i += 1)
  {
    float x = src[src_idx];
    src_idx += 1;
    float y = src[src_idx];
    src_idx += 1;
    float strength = DEFAULT_STRENGTH;
    if (pts->nbands == 3)
    {
      strength = src[src_idx];
      src_idx += 1;
    }
    strength = SEALEVEL + (strength * 0.1);
    int ix = x * w;
    int iy = y * h;
    int ii = ix - radius;
    int jj = iy - radius;
    for (int kj = 0; kj < fwidth; kj += 1)
    {
      for (int ki = 0; ki < fwidth; ki += 1)
      {
        int i = ii + ki;
        int j = jj + kj;
        if ((((i < 0) || (i >= w)) || (j < 0)) || (j >= h))
        {
          continue;
        }
        float *texel = heman_image_texel(target, i, j);
        int d2 = ((i - ix) * (i - ix)) + ((j - iy) * (j - iy));
        float dist = 1 - (sqrt(d2) / radius);
        *texel = ((*texel) > (strength * dist)) ? (*texel) : (strength * dist);
      }

    }

  }

}

heman_image *heman_generate_archipelago_heightmap(int width, int height, heman_points *points, float noiseamt, int seed)
{
  heman_image *noisetex = heman_internal_generate_island_noise(width, height, seed);
  heman_image *coastmask = heman_image_create(width, height, 1);
  heman_image_clear(coastmask, 0);
  heman_internal_draw_seeds(coastmask, points, 1);
  float *data = coastmask->data;
  unsigned int data_idx = 0;
  float invh = 1.0f / height;
  float invw = 1.0f / width;
  int hh = height / 2;
  int hw = width / 2;
  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    helper_heman_generate_archipelago_heightmap_1(width, noiseamt, noisetex, data, data_idx, invh, invw, hh, hw, y);
  }

  heman_image *heightmap = heman_distance_create_sdf(coastmask);
  heman_image_destroy(coastmask);
  heman_image *result = heman_image_create(width, height, 1);
  data_idx = result->data_idx;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    helper_heman_generate_archipelago_heightmap_2(width, noisetex, data, data_idx, invh, invw, y, heightmap);
  }

  heman_image_destroy(noisetex);
  heman_image_destroy(heightmap);
  return result;
}

heman_image *heman_generate_archipelago_political_1(int width, int height, heman_points *points, const heman_color *colors, heman_color ocean, int seed)
{
  heman_image *contour = heman_image_create(width, height, 3);
  heman_image_clear(contour, 0);
  heman_draw_contour_from_points(contour, points, ocean, 0.40, 0.41, 1);
  heman_draw_colored_points(contour, points, colors);
  heman_image *cf = heman_distance_create_cpcf(contour);
  heman_image *warped_cpcf = heman_ops_warp(cf, seed, 4);
  heman_image *political = heman_color_from_cpcf(warped_cpcf, contour);
  heman_image_destroy(warped_cpcf);
  heman_image_destroy(cf);
  heman_image_destroy(contour);
  return political;
}

heman_image *heman_generate_archipelago_political_2(int width, int height, heman_color ocean, int seed, heman_image *political, int invert)
{
  heman_image *coastmask = heman_ops_extract_mask(political, ocean, invert);
  heman_image *sdf = heman_distance_create_sdf(coastmask);
  heman_image_destroy(coastmask);
  heman_image *elevation = heman_image_create(width, height, 1);
  heman_image *noisetex = heman_internal_generate_island_noise(width, height, seed);
  float *data = elevation->data;
  float invw = 1.0 / width;
  float invh = 1.0 / height;
  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    helper_heman_generate_archipelago_political_2_1(width, sdf, noisetex, data, invw, invh, y);
  }

  heman_image_destroy(noisetex);
  heman_image_destroy(sdf);
  return elevation;
}

heman_image *heman_generate_archipelago_political_3(int width, int height, const heman_color *colors, int ncolors, heman_color ocean, int seed, heman_image *political)
{
  heman_image **elevations = malloc((sizeof(heman_image *)) * ncolors);
  for (int cindex = 0; cindex < ncolors; cindex += 1)
  {
    elevations[cindex] = heman_generate_archipelago_political_2(width, height, colors[cindex], seed, political, 1);
  }

  heman_image *elevation = heman_image_create(width, height, 1);
  heman_image_clear(elevation, 0);
  for (int cindex = 0; cindex < ncolors; cindex += 1)
  {
    int y;
    #pragma omp parallel for
    for (y = 0; y < height; y += 1)
    {
      float *dst = elevation->data + (y * width);
      unsigned int dst_idx = 0;
      float *src = elevations[cindex]->data + (y * width);
      unsigned int src_idx = 0;
      for (int x = 0; x < width; x += 1, dst_idx += 1, src_idx += 1)
      {
        dst[dst_idx] = (src[src_idx] > dst[dst_idx]) ? (src[src_idx]) : (dst[dst_idx]);
      }

    }

    heman_image_destroy(elevations[cindex]);
  }

  free(elevations);
  heman_image *ocean_elevation = heman_generate_archipelago_political_2(width, height, ocean, seed, political, 0);
  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    float *dst = elevation->data + (y * width);
    unsigned int dst_idx = 0;
    float *src = ocean_elevation->data + (y * width);
    unsigned int src_idx = 0;
    for (int x = 0; x < width; x += 1, dst_idx += 1, src_idx += 1)
    {
      if (src[src_idx] < 0)
      {
        dst[dst_idx] = src[src_idx];
      }
    }

  }

  heman_image_destroy(ocean_elevation);
  return elevation;
}

void heman_generate_archipelago_political(int width, int height, heman_points *points, const heman_color *colors, heman_color ocean, int seed, heman_image **elevation, heman_image **political, int elevation_mode)
{
  *political = heman_generate_archipelago_political_1(width, height, points, colors, ocean, seed);
  if (elevation_mode == 0)
  {
    *elevation = heman_generate_archipelago_political_2(width, height, ocean, seed, *political, 0);
  }
  else
  {
    int ncolors = points->width;
    *elevation = heman_generate_archipelago_political_3(width, height, colors, ncolors, ocean, seed, *political);
  }
}

typedef struct heman_image_s heman_image;
typedef struct heman_image_s heman_points;
typedef unsigned int heman_color;
typedef unsigned char heman_byte;
heman_image *heman_image_create(int width, int height, int nbands);
void heman_image_info(heman_image *, int *width, int *height, int *nbands);
float *heman_image_data(heman_image *);
void heman_image_array(heman_image *img, float **outview, int *n);
float *heman_image_texel(heman_image *, int x, int y);
void heman_image_sample(heman_image *, float u, float v, float *result);
void heman_image_clear(heman_image *, float value);
void heman_image_destroy(heman_image *);
heman_image *heman_image_extract_alpha(heman_image *);
heman_image *heman_image_extract_rgb(heman_image *);
heman_image *heman_color_create_gradient(int width, int num_colors, const int *cp_locations, const heman_color *cp_colors);
void heman_color_set_gamma(float f);
heman_image *heman_color_apply_gradient(heman_image *heightmap, float minheight, float maxheight, heman_image *gradient);
heman_image *heman_color_from_grayscale(heman_image *gray);
heman_image *heman_color_to_grayscale(heman_image *colorimg);
heman_image *heman_color_from_cpcf(heman_image *cfield, heman_image *texture);
heman_image *heman_generate_island_heightmap(int width, int height, int seed);
heman_image *heman_generate_rock_heightmap(int width, int height, int seed);
heman_image *heman_generate_planet_heightmap(int width, int height, int seed);
heman_image *heman_generate_archipelago_heightmap(int width, int height, heman_points *points, float noiseamt, int seed);
void heman_generate_archipelago_political(int width, int height, heman_points *points, const heman_color *colors, heman_color ocean, int seed, heman_image **elevation, heman_image **political, int elevation_mode);
heman_image *heman_generate_simplex_fbm(int width, int height, float frequency, float amplitude, int octaves, float lacunarity, float gain, int seed);
heman_image *heman_lighting_apply(heman_image *heightmap, heman_image *colorbuffer, float occlusion, float diffuse, float diffuse_softening, const float *light_position);
heman_image *heman_lighting_compute_normals(heman_image *heightmap);
heman_image *heman_lighting_compute_occlusion(heman_image *heightmap);
void heman_lighting_set_occlusion_scale(float s);
heman_image *heman_distance_create_sdf(heman_image *monochrome);
heman_image *heman_distance_create_df(heman_image *monochrome);
heman_image *heman_distance_create_cpcf(heman_image *seed);
heman_image *heman_distance_from_cpcf(heman_image *cf);
heman_image *heman_distance_identity_cpcf(int width, int height);
heman_image *heman_import_u8(int width, int height, int nbands, const heman_byte *source, float minval, float maxval);
void heman_export_ply(heman_image *, const char *filename);
void heman_export_with_colors_ply(heman_image *heightmap, heman_image *colors, const char *filename);
void heman_export_u8(heman_image *source, float minv, float maxv, heman_byte *outp);
heman_image *heman_ops_stitch_horizontal(heman_image **images, int count);
heman_image *heman_ops_stitch_vertical(heman_image **images, int count);
heman_image *heman_ops_normalize_f32(heman_image *source, float minval, float maxval);
heman_image *heman_ops_max(heman_image *imga, heman_image *imgb);
heman_image *heman_ops_step(heman_image *image, float threshold);
heman_image *heman_ops_stairstep(heman_image *image, int nsteps, heman_image *mask, heman_color mask_color, int invert_mask, float offset);
heman_image *heman_ops_percentiles(heman_image *image, int nsteps, heman_image *mask, heman_color mask_color, int invert_mask, float offset);
heman_image *heman_ops_sweep(heman_image *image);
heman_image *heman_ops_laplacian(heman_image *heightmap);
heman_image *heman_ops_sobel(heman_image *dst, heman_color edge_color);
void heman_ops_accumulate(heman_image *dst, heman_image *src);
heman_image *heman_ops_warp(heman_image *src, int seed, int octaves);
heman_image *heman_ops_warp_points(heman_image *src, int seed, int octaves, heman_points *pts);
heman_image *heman_ops_extract_mask(heman_image *src, heman_color color, int invert);
heman_image *heman_ops_replace_color(heman_image *src, heman_color color, heman_image *texture);
heman_image *heman_ops_merge_political(heman_image *elevation, heman_image *political, heman_color ocean_color);
heman_image *heman_ops_emboss(heman_image *elevation, int mode);
heman_image *heman_points_create(float *xy, int npoints, int nbands);
void heman_points_destroy(heman_points *);
heman_points *heman_points_from_grid(float width, float height, float cellsize, float jitter);
heman_points *heman_points_from_poisson(float width, float height, float mindist);
heman_points *heman_points_from_density(heman_image *density, float mindist, float maxdist);
void heman_draw_points(heman_image *target, heman_points *pts, float val);
void heman_draw_colored_points(heman_image *target, heman_points *coords, const heman_color *colors);
void heman_draw_colored_circles(heman_image *target, heman_points *pts, int radius, const heman_color *colors);
void heman_draw_splats(heman_image *target, heman_points *pts, int radius, int blend_mode);
void heman_draw_contour_from_points(heman_image *target, heman_points *coords, heman_color color, float mind, float maxd, int filterd);
int heman_get_num_threads();
struct heman_image_s
{
  int width;
  int height;
  int nbands;
  float *data;
};
extern float _gamma;
inline float smoothstep(float edge0, float edge1, float x)
{
  float t;
  t = (0.0f > ((1.0f > ((x - edge0) / (edge1 - edge0))) ? ((x - edge0) / (edge1 - edge0)) : (1.0f))) ? (0.0f) : ((1.0f > ((x - edge0) / (edge1 - edge0))) ? ((x - edge0) / (edge1 - edge0)) : (1.0f));
  return (t * t) * (3.0 - (2.0 * t));
}

void generate_gaussian_row(int *target, int fwidth);
void generate_gaussian_splat(float *target, int fwidth);

struct osn_context;
int open_simplex_noise(int64_t seed, struct osn_context **ctx);
void open_simplex_noise_free(struct osn_context *ctx);
int open_simplex_noise_init_perm(struct osn_context *ctx, int16_t p[], int nelements);
double open_simplex_noise2(struct osn_context *ctx, double x, double y);
double open_simplex_noise3(struct osn_context *ctx, double x, double y, double z);
double open_simplex_noise4(struct osn_context *ctx, double x, double y, double z, double w);
extern float kmSQR(float s);
extern float kmDegreesToRadians(float degrees);
extern float kmRadiansToDegrees(float radians);
extern float kmMin(float lhs, float rhs);
extern float kmMax(float lhs, float rhs);
extern unsigned char kmAlmostEqual(float lhs, float rhs);
extern float kmClamp(float x, float min, float max);
extern float kmLerp(float x, float y, float factor);
struct kmMat4;
struct kmMat3;
struct kmPlane;
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3;
kmVec3 *kmVec3Fill(kmVec3 *pOut, float x, float y, float z);
float kmVec3Length(const kmVec3 *pIn);
float kmVec3LengthSq(const kmVec3 *pIn);
kmVec3 *kmVec3Lerp(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2, float t);
kmVec3 *kmVec3Normalize(kmVec3 *pOut, const kmVec3 *pIn);
kmVec3 *kmVec3Cross(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2);
float kmVec3Dot(const kmVec3 *pV1, const kmVec3 *pV2);
kmVec3 *kmVec3Add(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2);
kmVec3 *kmVec3Subtract(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2);
kmVec3 *kmVec3Mul(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2);
kmVec3 *kmVec3Div(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2);
kmVec3 *kmVec3MultiplyMat3(kmVec3 *pOut, const kmVec3 *pV, const struct kmMat3 *pM);
kmVec3 *kmVec3MultiplyMat4(kmVec3 *pOut, const kmVec3 *pV, const struct kmMat4 *pM);
kmVec3 *kmVec3Transform(kmVec3 *pOut, const kmVec3 *pV1, const struct kmMat4 *pM);
kmVec3 *kmVec3TransformNormal(kmVec3 *pOut, const kmVec3 *pV, const struct kmMat4 *pM);
kmVec3 *kmVec3TransformCoord(kmVec3 *pOut, const kmVec3 *pV, const struct kmMat4 *pM);
kmVec3 *kmVec3Scale(kmVec3 *pOut, const kmVec3 *pIn, const float s);
int kmVec3AreEqual(const kmVec3 *p1, const kmVec3 *p2);
kmVec3 *kmVec3InverseTransform(kmVec3 *pOut, const kmVec3 *pV, const struct kmMat4 *pM);
kmVec3 *kmVec3InverseTransformNormal(kmVec3 *pOut, const kmVec3 *pVect, const struct kmMat4 *pM);
kmVec3 *kmVec3Assign(kmVec3 *pOut, const kmVec3 *pIn);
kmVec3 *kmVec3Zero(kmVec3 *pOut);
kmVec3 *kmVec3GetHorizontalAngle(kmVec3 *pOut, const kmVec3 *pIn);
kmVec3 *kmVec3RotationToDirection(kmVec3 *pOut, const kmVec3 *pIn, const kmVec3 *forwards);
kmVec3 *kmVec3ProjectOnToPlane(kmVec3 *pOut, const kmVec3 *point, const struct kmPlane *plane);
kmVec3 *kmVec3Reflect(kmVec3 *pOut, const kmVec3 *pIn, const kmVec3 *normal);
extern const kmVec3 KM_VEC3_NEG_Z;
extern const kmVec3 KM_VEC3_POS_Z;
extern const kmVec3 KM_VEC3_POS_Y;
extern const kmVec3 KM_VEC3_NEG_Y;
extern const kmVec3 KM_VEC3_NEG_X;
extern const kmVec3 KM_VEC3_POS_X;
extern const kmVec3 KM_VEC3_ZERO;
static const float SEALEVEL = 0.5;
static const float DEFAULT_STRENGTH = 0.6;
heman_image *heman_internal_generate_island_noise(int width, int height, int seed)
{
  struct osn_context *ctx;
  open_simplex_noise(seed, &ctx);
  heman_image *img = heman_image_create(width, height, 3);
  float *data = img->data;
  float invh = 1.0f / ((width > height) ? (width) : (height));
  float invw = 1.0f / ((width > height) ? (width) : (height));
  float freqs[] = {4.0, 16.0, 32.0, 64.0, 128.0};
  float ampls[] = {0.2, 0.1, 0.05, 0.025, 0.0125};
  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    float v = y * invh;
    float *dst = data + ((y * width) * 3);
    unsigned int dst_idx = 0;
    for (int x = 0; x < width; x += 1)
    {
      float u = x * invw;
      dst[dst_idx] = ((ampls[0] * open_simplex_noise2(ctx, u * freqs[0], v * freqs[0])) + (ampls[1] * open_simplex_noise2(ctx, u * freqs[1], v * freqs[1]))) + (ampls[2] * open_simplex_noise2(ctx, u * freqs[2], v * freqs[2]));
      dst_idx += 1;
      dst[dst_idx] = (ampls[3] * open_simplex_noise2(ctx, u * freqs[3], v * freqs[3])) + (ampls[4] * open_simplex_noise2(ctx, u * freqs[4], v * freqs[4]));
      dst_idx += 1;
      u += 0.5;
      dst[dst_idx] = (ampls[3] * open_simplex_noise2(ctx, u * freqs[3], v * freqs[3])) + (ampls[4] * open_simplex_noise2(ctx, u * freqs[4], v * freqs[4]));
      dst_idx += 1;
    }

  }

  open_simplex_noise_free(ctx);
  return img;
}

heman_image *heman_internal_generate_rock_noise(int width, int height, int seed)
{
  struct osn_context *ctx;
  open_simplex_noise(seed, &ctx);
  heman_image *img = heman_image_create(width, height, 1);
  float *data = img->data;
  float invh = 1.0f / ((width > height) ? (width) : (height));
  float invw = 1.0f / ((width > height) ? (width) : (height));
  float freqs[] = {2.0, 4.0, 16.0};
  float ampls[] = {0.2, 0.05, 0.01};
  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    float v = y * invh;
    float *dst = data + (y * width);
    unsigned int dst_idx = 0;
    for (int x = 0; x < width; x += 1)
    {
      float u = x * invw;
      dst[dst_idx] = ((ampls[0] * open_simplex_noise2(ctx, u * freqs[0], v * freqs[0])) + (ampls[1] * open_simplex_noise2(ctx, u * freqs[1], v * freqs[1]))) + (ampls[2] * open_simplex_noise2(ctx, u * freqs[2], v * freqs[2]));
      dst_idx += 1;
    }

  }

  open_simplex_noise_free(ctx);
  return img;
}

heman_image *heman_generate_island_heightmap(int width, int height, int seed)
{
  heman_image *noisetex = heman_internal_generate_island_noise(width, height, seed);
  heman_image *coastmask = heman_image_create(width, height, 1);
  float *data = coastmask->data;
  unsigned int data_idx = 0;
  float invh = 1.0f / height;
  float invw = 1.0f / width;
  int hh = height / 2;
  int hw = width / 2;
  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    float vv = (y - hh) * invh;
    float *dst = (&data[data_idx]) + (y * width);
    unsigned int dst_idx = 0;
    for (int x = 0; x < width; x += 1)
    {
      float n[3];
      float v = y * invh;
      float u = x * invw;
      heman_image_sample(noisetex, u, v, n);
      u = (x - hw) * invw;
      v = vv;
      u += n[1];
      v += n[2];
      float m = 0.707 - sqrt((u * u) + (v * v));
      m += n[0];
      dst[dst_idx] = (m < SEALEVEL) ? (0) : (1);
      dst_idx += 1;
    }

  }

  heman_image *heightmap = heman_distance_create_sdf(coastmask);
  heman_image_destroy(coastmask);
  heman_image *result = heman_image_create(width, height, 1);
  data_idx = result->data_idx;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    float *dst = (&data[data_idx]) + (y * width);
    unsigned int dst_idx = 0;
    for (int x = 0; x < width; x += 1)
    {
      float n[3];
      float u = x * invw;
      float v = y * invh;
      heman_image_sample(noisetex, u, v, n);
      float z;
      heman_image_sample(heightmap, u, v, &z);
      if (z > 0.0)
      {
        float influence = z;
        u += influence * n[1];
        v += influence * n[2];
        heman_image_sample(heightmap, u, v, &z);
        z += (6 * influence) * n[0];
      }
      dst[dst_idx] = z;
      dst_idx += 1;
    }

  }

  heman_image_destroy(noisetex);
  heman_image_destroy(heightmap);
  return result;
}

heman_image *heman_generate_rock_heightmap(int width, int height, int seed)
{
  heman_image *noisetex = heman_internal_generate_rock_noise(width, height, seed);
  heman_image *heightmap = heman_image_create(width, height, 1);
  float *data = heightmap->data;
  float invh = 1.0f / height;
  float invw = 1.0f / width;
  int hh = height / 2;
  int hw = width / 2;
  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    float vv = (y - hh) * invh;
    float *dst = data + (y * width);
    unsigned int dst_idx = 0;
    for (int x = 0; x < width; x += 1)
    {
      float v = y * invh;
      float u = x * invw;
      float n;
      heman_image_sample(noisetex, u, v, &n);
      u = (x - hw) * invw;
      v = vv;
      float r = 0.3 + n;
      if (((u * u) + (v * v)) > (r * r))
      {
        dst[dst_idx] = 0;
        dst_idx += 1;
        continue;
      }
      float z = sqrt(((r * r) - (u * u)) - (v * v));
      dst[dst_idx] = z;
      dst_idx += 1;
    }

  }

  heman_image_destroy(noisetex);
  return heightmap;
}

heman_image *heman_generate_simplex_fbm(int width, int height, float frequency, float amplitude, int octaves, float lacunarity, float gain, int seed)
{
  struct osn_context *ctx;
  open_simplex_noise(seed, &ctx);
  heman_image *img = heman_image_create(width, height, 1);
  float *data = img->data;
  float invh = 1.0f / height;
  float invw = 1.0f / width;
  float ampl = amplitude;
  float freq = frequency;
  memset(data, 0, ((sizeof(float)) * width) * height);
  while (octaves--)
  {
    int y;
    #pragma omp parallel for
    for (y = 0; y < height; y += 1)
    {
      float v = y * invh;
      float *dst = data + (y * width);
      unsigned int dst_idx = 0;
      for (int x = 0; x < width; x += 1)
      {
        float u = x * invw;
        dst[dst_idx] += ampl * open_simplex_noise2(ctx, u * freq, v * freq);
        dst_idx += 1;
      }

    }

    ampl *= gain;
    freq *= lacunarity;
  }

  open_simplex_noise_free(ctx);
  return img;
}

static void sphere(float u, float v, float r, kmVec3 *dst)
{
  dst->x = (r * sin(v)) * cos(u);
  dst->y = r * cos(v);
  dst->z = (r * (-sin(v))) * sin(u);
}

heman_image *heman_generate_planet_heightmap(int width, int height, int seed)
{
  struct osn_context *ctx;
  open_simplex_noise(seed, &ctx);
  heman_image *result = heman_image_create(width, height, 1);
  float scalex = (2.0f * 3.1415926535) / width;
  float scaley = 3.1415926535 / height;
  float invh = 1.0f / height;
  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    float *dst = result->data + (y * width);
    unsigned int dst_idx = 0;
    kmVec3 p;
    float v = y * invh;
    float s = 0.95;
    float antarctic_influence = (((10 * (v - s)) / s) > (-0.5)) ? ((10 * (v - s)) / s) : (-0.5);
    v = fabs(v - 0.5);
    v = 1.5 * (0.5 - v);
    float equatorial_influence = v * v;
    v = y * scaley;
    for (int x = 0; x < width; x += 1)
    {
      float u = x * scalex;
      float freq = 1;
      float amp = 1;
      float h = antarctic_influence + equatorial_influence;
      for (int oct = 0; oct < 6; oct += 1)
      {
        sphere(u, v, freq, &p);
        h += amp * open_simplex_noise3(ctx, p.x, p.y, p.z);
        amp *= 0.5;
        freq *= 2;
      }

      dst[dst_idx] = h;
      dst_idx += 1;
    }

  }

  open_simplex_noise_free(ctx);
  return result;
}

void heman_internal_draw_seeds(heman_image *target, heman_points *pts, int filterd)
{
  int radius = target->width / filterd;
  int fwidth = (radius * 2) + 1;
  float *src = pts->data;
  unsigned int src_idx = 0;
  int w = target->width;
  int h = target->height;
  for (int i = 0; i < pts->width; i += 1)
  {
    float x = src[src_idx];
    src_idx += 1;
    float y = src[src_idx];
    src_idx += 1;
    float strength = DEFAULT_STRENGTH;
    if (pts->nbands == 3)
    {
      strength = src[src_idx];
      src_idx += 1;
    }
    strength = SEALEVEL + (strength * 0.1);
    int ix = x * w;
    int iy = y * h;
    int ii = ix - radius;
    int jj = iy - radius;
    for (int kj = 0; kj < fwidth; kj += 1)
    {
      for (int ki = 0; ki < fwidth; ki += 1)
      {
        int i = ii + ki;
        int j = jj + kj;
        if ((((i < 0) || (i >= w)) || (j < 0)) || (j >= h))
        {
          continue;
        }
        float *texel = heman_image_texel(target, i, j);
        int d2 = ((i - ix) * (i - ix)) + ((j - iy) * (j - iy));
        float dist = 1 - (sqrt(d2) / radius);
        *texel = ((*texel) > (strength * dist)) ? (*texel) : (strength * dist);
      }

    }

  }

}

heman_image *heman_generate_archipelago_heightmap(int width, int height, heman_points *points, float noiseamt, int seed)
{
  heman_image *noisetex = heman_internal_generate_island_noise(width, height, seed);
  heman_image *coastmask = heman_image_create(width, height, 1);
  heman_image_clear(coastmask, 0);
  heman_internal_draw_seeds(coastmask, points, 1);
  float *data = coastmask->data;
  unsigned int data_idx = 0;
  float invh = 1.0f / height;
  float invw = 1.0f / width;
  int hh = height / 2;
  int hw = width / 2;
  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    float vv = (y - hh) * invh;
    float *dst = (&data[data_idx]) + (y * width);
    unsigned int dst_idx = 0;
    for (int x = 0; x < width; x += 1)
    {
      float n[3] = {0};
      float v = y * invh;
      float u = x * invw;
      heman_image_sample(noisetex, u, v, n);
      u = (x - hw) * invw;
      v = vv;
      u += noiseamt * n[1];
      v += noiseamt * n[2];
      float m = dst[dst_idx];
      m += noiseamt * n[0];
      dst[dst_idx] = (m < SEALEVEL) ? (0) : (1);
      dst_idx += 1;
    }

  }

  heman_image *heightmap = heman_distance_create_sdf(coastmask);
  heman_image_destroy(coastmask);
  heman_image *result = heman_image_create(width, height, 1);
  data_idx = result->data_idx;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    float *dst = (&data[data_idx]) + (y * width);
    unsigned int dst_idx = 0;
    for (int x = 0; x < width; x += 1)
    {
      float n[3];
      float u = x * invw;
      float v = y * invh;
      heman_image_sample(noisetex, u, v, n);
      float z;
      heman_image_sample(heightmap, u, v, &z);
      if (z > 0.0)
      {
        float influence = z;
        u += influence * n[1];
        v += influence * n[2];
        heman_image_sample(heightmap, u, v, &z);
        z += (6 * influence) * n[0];
      }
      dst[dst_idx] = z;
      dst_idx += 1;
    }

  }

  heman_image_destroy(noisetex);
  heman_image_destroy(heightmap);
  return result;
}

heman_image *heman_generate_archipelago_political_1(int width, int height, heman_points *points, const heman_color *colors, heman_color ocean, int seed)
{
  heman_image *contour = heman_image_create(width, height, 3);
  heman_image_clear(contour, 0);
  heman_draw_contour_from_points(contour, points, ocean, 0.40, 0.41, 1);
  heman_draw_colored_points(contour, points, colors);
  heman_image *cf = heman_distance_create_cpcf(contour);
  heman_image *warped_cpcf = heman_ops_warp(cf, seed, 4);
  heman_image *political = heman_color_from_cpcf(warped_cpcf, contour);
  heman_image_destroy(warped_cpcf);
  heman_image_destroy(cf);
  heman_image_destroy(contour);
  return political;
}

heman_image *heman_generate_archipelago_political_2(int width, int height, heman_color ocean, int seed, heman_image *political, int invert)
{
  heman_image *coastmask = heman_ops_extract_mask(political, ocean, invert);
  heman_image *sdf = heman_distance_create_sdf(coastmask);
  heman_image_destroy(coastmask);
  heman_image *elevation = heman_image_create(width, height, 1);
  heman_image *noisetex = heman_internal_generate_island_noise(width, height, seed);
  float *data = elevation->data;
  float invw = 1.0 / width;
  float invh = 1.0 / height;
  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    float *dst = data + (y * width);
    unsigned int dst_idx = 0;
    for (int x = 0; x < width; x += 1)
    {
      float n[3];
      float u = x * invw;
      float v = y * invh;
      heman_image_sample(noisetex, u, v, n);
      float z;
      heman_image_sample(sdf, u, v, &z);
      if (z > 0.0)
      {
        float influence = z;
        u += influence * n[1];
        v += influence * n[2];
        heman_image_sample(sdf, u, v, &z);
        z += (6 * influence) * n[0];
      }
      dst[dst_idx] = z;
      dst_idx += 1;
    }

  }

  heman_image_destroy(noisetex);
  heman_image_destroy(sdf);
  return elevation;
}

heman_image *heman_generate_archipelago_political_3(int width, int height, const heman_color *colors, int ncolors, heman_color ocean, int seed, heman_image *political)
{
  heman_image **elevations = malloc((sizeof(heman_image *)) * ncolors);
  for (int cindex = 0; cindex < ncolors; cindex += 1)
  {
    elevations[cindex] = heman_generate_archipelago_political_2(width, height, colors[cindex], seed, political, 1);
  }

  heman_image *elevation = heman_image_create(width, height, 1);
  heman_image_clear(elevation, 0);
  for (int cindex = 0; cindex < ncolors; cindex += 1)
  {
    int y;
    #pragma omp parallel for
    for (y = 0; y < height; y += 1)
    {
      float *dst = elevation->data + (y * width);
      unsigned int dst_idx = 0;
      float *src = elevations[cindex]->data + (y * width);
      unsigned int src_idx = 0;
      for (int x = 0; x < width; x += 1, dst_idx += 1, src_idx += 1)
      {
        dst[dst_idx] = (src[src_idx] > dst[dst_idx]) ? (src[src_idx]) : (dst[dst_idx]);
      }

    }

    heman_image_destroy(elevations[cindex]);
  }

  free(elevations);
  heman_image *ocean_elevation = heman_generate_archipelago_political_2(width, height, ocean, seed, political, 0);
  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    float *dst = elevation->data + (y * width);
    unsigned int dst_idx = 0;
    float *src = ocean_elevation->data + (y * width);
    unsigned int src_idx = 0;
    for (int x = 0; x < width; x += 1, dst_idx += 1, src_idx += 1)
    {
      if (src[src_idx] < 0)
      {
        dst[dst_idx] = src[src_idx];
      }
    }

  }

  heman_image_destroy(ocean_elevation);
  return elevation;
}

void heman_generate_archipelago_political(int width, int height, heman_points *points, const heman_color *colors, heman_color ocean, int seed, heman_image **elevation, heman_image **political, int elevation_mode)
{
  *political = heman_generate_archipelago_political_1(width, height, points, colors, ocean, seed);
  if (elevation_mode == 0)
  {
    *elevation = heman_generate_archipelago_political_2(width, height, ocean, seed, *political, 0);
  }
  else
  {
    int ncolors = points->width;
    *elevation = heman_generate_archipelago_political_3(width, height, colors, ncolors, ocean, seed, *political);
  }
}

void helper_heman_generate_island_heightmap_1(int width, heman_image * const noisetex, float * const data, unsigned int data_idx, float invh, float invw, int hh, int hw, int y)
{
  float vv = (y - hh) * invh;
  float *dst = (&data[data_idx]) + (y * width);
  unsigned int dst_idx = 0;
  for (int x = 0; x < width; x += 1)
  {
    float n[3];
    float v = y * invh;
    float u = x * invw;
    heman_image_sample(noisetex, u, v, n);
    u = (x - hw) * invw;
    v = vv;
    u += n[1];
    v += n[2];
    float m = 0.707 - sqrt((u * u) + (v * v));
    m += n[0];
    dst[dst_idx] = (m < SEALEVEL) ? (0) : (1);
    dst_idx += 1;
  }

}

void helper_heman_generate_island_heightmap_2(int width, heman_image * const noisetex, float * const data, unsigned int data_idx, float invh, float invw, int y, heman_image * const heightmap)
{
  float *dst = (&data[data_idx]) + (y * width);
  unsigned int dst_idx = 0;
  for (int x = 0; x < width; x += 1)
  {
    float n[3];
    float u = x * invw;
    float v = y * invh;
    heman_image_sample(noisetex, u, v, n);
    float z;
    heman_image_sample(heightmap, u, v, &z);
    if (z > 0.0)
    {
      float influence = z;
      u += influence * n[1];
      v += influence * n[2];
      heman_image_sample(heightmap, u, v, &z);
      z += (6 * influence) * n[0];
    }
    dst[dst_idx] = z;
    dst_idx += 1;
  }

}

void helper_heman_generate_planet_heightmap_1(int width, struct osn_context * const ctx, heman_image * const result, float scalex, float scaley, float invh, int y)
{
  float *dst = result->data + (y * width);
  unsigned int dst_idx = 0;
  kmVec3 p;
  float v = y * invh;
  float s = 0.95;
  float antarctic_influence = (((10 * (v - s)) / s) > (-0.5)) ? ((10 * (v - s)) / s) : (-0.5);
  v = fabs(v - 0.5);
  v = 1.5 * (0.5 - v);
  float equatorial_influence = v * v;
  v = y * scaley;
  for (int x = 0; x < width; x += 1)
  {
    float u = x * scalex;
    float freq = 1;
    float amp = 1;
    float h = antarctic_influence + equatorial_influence;
    for (int oct = 0; oct < 6; oct += 1)
    {
      sphere(u, v, freq, &p);
      h += amp * open_simplex_noise3(ctx, p.x, p.y, p.z);
      amp *= 0.5;
      freq *= 2;
    }

    dst[dst_idx] = h;
    dst_idx += 1;
  }

}

void helper_heman_generate_archipelago_heightmap_1(int width, float noiseamt, heman_image * const noisetex, float * const data, unsigned int data_idx, float invh, float invw, int hh, int hw, int y)
{
  float vv = (y - hh) * invh;
  float *dst = (&data[data_idx]) + (y * width);
  unsigned int dst_idx = 0;
  for (int x = 0; x < width; x += 1)
  {
    float n[3] = {0};
    float v = y * invh;
    float u = x * invw;
    heman_image_sample(noisetex, u, v, n);
    u = (x - hw) * invw;
    v = vv;
    u += noiseamt * n[1];
    v += noiseamt * n[2];
    float m = dst[dst_idx];
    m += noiseamt * n[0];
    dst[dst_idx] = (m < SEALEVEL) ? (0) : (1);
    dst_idx += 1;
  }

}

void helper_heman_generate_archipelago_heightmap_2(int width, heman_image * const noisetex, float * const data, unsigned int data_idx, float invh, float invw, int y, heman_image * const heightmap)
{
  float *dst = (&data[data_idx]) + (y * width);
  unsigned int dst_idx = 0;
  for (int x = 0; x < width; x += 1)
  {
    float n[3];
    float u = x * invw;
    float v = y * invh;
    heman_image_sample(noisetex, u, v, n);
    float z;
    heman_image_sample(heightmap, u, v, &z);
    if (z > 0.0)
    {
      float influence = z;
      u += influence * n[1];
      v += influence * n[2];
      heman_image_sample(heightmap, u, v, &z);
      z += (6 * influence) * n[0];
    }
    dst[dst_idx] = z;
    dst_idx += 1;
  }

}

void helper_heman_generate_archipelago_political_2_1(int width, heman_image * const sdf, heman_image * const noisetex, float * const data, float invw, float invh, int y)
{
  float *dst = data + (y * width);
  unsigned int dst_idx = 0;
  for (int x = 0; x < width; x += 1)
  {
    float n[3];
    float u = x * invw;
    float v = y * invh;
    heman_image_sample(noisetex, u, v, n);
    float z;
    heman_image_sample(sdf, u, v, &z);
    if (z > 0.0)
    {
      float influence = z;
      u += influence * n[1];
      v += influence * n[2];
      heman_image_sample(sdf, u, v, &z);
      z += (6 * influence) * n[0];
    }
    dst[dst_idx] = z;
    dst_idx += 1;
  }

}

