#include <assert.h>
#include <heman.h>
#include <image.h>
#include <limits.h>
#include <math.h>
#include <memory.h>
#include <points.c>
#include <stdlib.h>
#include <utility.h>
#include <vec2.h>
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

extern float kmSQR(float s);
extern float kmDegreesToRadians(float degrees);
extern float kmRadiansToDegrees(float radians);
extern float kmMin(float lhs, float rhs);
extern float kmMax(float lhs, float rhs);
extern unsigned char kmAlmostEqual(float lhs, float rhs);
extern float kmClamp(float x, float min, float max);
extern float kmLerp(float x, float y, float factor);
struct kmMat3;
#pragma pack(push)
#pragma pack(1)
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2;
#pragma pack(pop)
kmVec2 *kmVec2Fill(kmVec2 *pOut, float x, float y);
float kmVec2Length(const kmVec2 *pIn);
float kmVec2LengthSq(const kmVec2 *pIn);
kmVec2 *kmVec2Normalize(kmVec2 *pOut, const kmVec2 *pIn);
kmVec2 *kmVec2Lerp(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2, float t);
kmVec2 *kmVec2Add(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2);
float kmVec2Dot(const kmVec2 *pV1, const kmVec2 *pV2);
float kmVec2Cross(const kmVec2 *pV1, const kmVec2 *pV2);
kmVec2 *kmVec2Subtract(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2);
kmVec2 *kmVec2Mul(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2);
kmVec2 *kmVec2Div(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2);
kmVec2 *kmVec2Transform(kmVec2 *pOut, const kmVec2 *pV1, const struct kmMat3 *pM);
kmVec2 *kmVec2TransformCoord(kmVec2 *pOut, const kmVec2 *pV, const struct kmMat3 *pM);
kmVec2 *kmVec2Scale(kmVec2 *pOut, const kmVec2 *pIn, const float s);
int kmVec2AreEqual(const kmVec2 *p1, const kmVec2 *p2);
kmVec2 *kmVec2Assign(kmVec2 *pOut, const kmVec2 *pIn);
kmVec2 *kmVec2RotateBy(kmVec2 *pOut, const kmVec2 *pIn, const float degrees, const kmVec2 *center);
float kmVec2DegreesBetween(const kmVec2 *v1, const kmVec2 *v2);
float kmVec2DistanceBetween(const kmVec2 *v1, const kmVec2 *v2);
kmVec2 *kmVec2MidPointBetween(kmVec2 *pOut, const kmVec2 *v1, const kmVec2 *v2);
kmVec2 *kmVec2Reflect(kmVec2 *pOut, const kmVec2 *pIn, const kmVec2 *normal);
extern const kmVec2 KM_VEC2_POS_Y;
extern const kmVec2 KM_VEC2_NEG_Y;
extern const kmVec2 KM_VEC2_NEG_X;
extern const kmVec2 KM_VEC2_POS_X;
extern const kmVec2 KM_VEC2_ZERO;
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
  return (((b - a) * randhash(seed)) / ((float) 4294967295U)) + a;
}

heman_image *heman_points_create(float *xy, int npoints, int nbands)
{
  heman_points *img = malloc(sizeof(heman_image));
  img->width = npoints;
  img->height = 1;
  img->nbands = nbands;
  int nbytes = ((sizeof(float)) * npoints) * nbands;
  img->data = malloc(nbytes);
  memcpy(img->data, xy, nbytes);
  return img;
}

void heman_points_destroy(heman_points *img)
{
  free(img->data);
  free(img);
}

heman_points *heman_points_from_grid(float width, float height, float cellsize, float jitter)
{
  int cols = width / cellsize;
  int rows = height / cellsize;
  int ncells = cols * rows;
  heman_points *result = heman_image_create(ncells, 1, 2);
  float rscale = (2.0 * jitter) / ((float) 32767);
  int j;
  #pragma omp parallel for
  for (j = 0; j < rows; j += 1)
  {
    float *dst = result->data + ((j * cols) * 2);
    unsigned int dst_idx = 0;
    float y = (cellsize * 0.5) + (cellsize * j);
    float x = cellsize * 0.5;
    for (int i = 0; i < cols; i += 1)
    {
      float rx = (rand() * rscale) - jitter;
      float ry = (rand() * rscale) - jitter;
      dst[dst_idx] = x + rx;
      dst_idx += 1;
      dst[dst_idx] = y + ry;
      dst_idx += 1;
      x += cellsize;
    }

  }

  return result;
}

kmVec2 sample_annulus(float radius, kmVec2 center, unsigned int *seedptr)
{
  unsigned int seed = *seedptr;
  kmVec2 r;
  float rscale = 1.0f / 4294967295U;
  while (1)
  {
    r.x = ((4 * rscale) * randhash(seed)) - 2;
    seed += 1;
    r.y = ((4 * rscale) * randhash(seed)) - 2;
    seed += 1;
    float r2 = kmVec2LengthSq(&r);
    if ((r2 > 1) && (r2 <= 4))
    {
      break;
    }
  }

  *seedptr = seed;
  kmVec2Scale(&r, &r, radius);
  kmVec2Add(&r, &r, &center);
  return r;
}

heman_points *heman_points_from_poisson(float width, float height, float radius)
{
  int maxattempts = 30;
  float rscale = 1.0f / 4294967295U;
  unsigned int seed = 0;
  kmVec2 rvec;
  rvec.x = (rvec.y = radius);
  float r2 = radius * radius;
  float cellsize = radius / sqrtf(2);
  float invcell = 1.0f / cellsize;
  int ncols = ceil(width * invcell);
  int nrows = ceil(height * invcell);
  int maxcol = ncols - 1;
  int maxrow = nrows - 1;
  int ncells = ncols * nrows;
  int *grid = malloc(ncells * (sizeof(int)));
  for (int i = 0; i < ncells; i += 1)
  {
    grid[i] = -1;
  }

  int *actives = malloc(ncells * (sizeof(int)));
  int nactives = 0;
  heman_points *result = heman_image_create(ncells, 1, 2);
  kmVec2 *samples = (kmVec2 *) result->data;
  int nsamples = 0;
  kmVec2 pt;
  pt.x = (width * randhash(seed)) * rscale;
  seed += 1;
  pt.y = (height * randhash(seed)) * rscale;
  seed += 1;
  grid[((int) (pt.x * invcell)) + (ncols * ((int) (pt.y * invcell)))] = (actives[nactives] = nsamples);
  nactives += 1;
  samples[nsamples] = pt;
  nsamples += 1;
  while (nsamples < ncells)
  {
    helper_heman_points_from_poisson_1(&invcell, &ncols, &nactives, &nsamples, &pt, width, height, radius, maxattempts, seed, rvec, r2, maxcol, maxrow, grid, actives, samples);
  }

  result->width = nsamples;
  free(grid);
  free(actives);
  return result;
}

heman_points *heman_points_from_density(heman_image *density, float minradius, float maxradius)
{
  assert(density->nbands == 1);
  float width = 1;
  float height = 1;
  int maxattempts = 30;
  float rscale = 1.0f / 4294967295U;
  unsigned int seed = 0;
  kmVec2 rvec;
  rvec.x = (rvec.y = maxradius);
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
  int *grid = malloc((ncells * (sizeof(int))) * gcapacity);
  int *ngrid = malloc(ncells * (sizeof(int)));
  for (int i = 0; i < ncells; i += 1)
  {
    ngrid[i] = 0;
  }

  int *actives = malloc(ncells * (sizeof(int)));
  int nactives = 0;
  int maxsamples = ncells * gcapacity;
  heman_points *result = heman_image_create(maxsamples, 1, 2);
  kmVec2 *samples = (kmVec2 *) result->data;
  int nsamples = 0;
  kmVec2 pt;
  pt.x = (width * randhash(seed)) * rscale;
  seed += 1;
  pt.y = (height * randhash(seed)) * rscale;
  seed += 1;
  actives[nactives] = nsamples;
  nactives += 1;
  gindex = ((int) (pt.x * invcell)) + (ncols * ((int) (pt.y * invcell)));
  grid[(gcapacity * gindex) + ngrid[gindex]] = nsamples;
  ngrid[gindex] += 1;
  samples[nsamples] = pt;
  nsamples += 1;
  while (nsamples < maxsamples)
  {
    helper_heman_points_from_density_1(&gindex, &gcapacity, &nactives, &nsamples, &pt, density, minradius, maxradius, width, height, maxattempts, seed, rvec, invcell, ncols, maxcol, maxrow, grid, ngrid, actives, samples);
  }

  result->width = nsamples;
  free(grid);
  free(ngrid);
  free(actives);
  return result;
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

extern float kmSQR(float s);
extern float kmDegreesToRadians(float degrees);
extern float kmRadiansToDegrees(float radians);
extern float kmMin(float lhs, float rhs);
extern float kmMax(float lhs, float rhs);
extern unsigned char kmAlmostEqual(float lhs, float rhs);
extern float kmClamp(float x, float min, float max);
extern float kmLerp(float x, float y, float factor);
struct kmMat3;
#pragma pack(push)
#pragma pack(1)
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2;
#pragma pack(pop)
kmVec2 *kmVec2Fill(kmVec2 *pOut, float x, float y);
float kmVec2Length(const kmVec2 *pIn);
float kmVec2LengthSq(const kmVec2 *pIn);
kmVec2 *kmVec2Normalize(kmVec2 *pOut, const kmVec2 *pIn);
kmVec2 *kmVec2Lerp(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2, float t);
kmVec2 *kmVec2Add(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2);
float kmVec2Dot(const kmVec2 *pV1, const kmVec2 *pV2);
float kmVec2Cross(const kmVec2 *pV1, const kmVec2 *pV2);
kmVec2 *kmVec2Subtract(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2);
kmVec2 *kmVec2Mul(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2);
kmVec2 *kmVec2Div(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2);
kmVec2 *kmVec2Transform(kmVec2 *pOut, const kmVec2 *pV1, const struct kmMat3 *pM);
kmVec2 *kmVec2TransformCoord(kmVec2 *pOut, const kmVec2 *pV, const struct kmMat3 *pM);
kmVec2 *kmVec2Scale(kmVec2 *pOut, const kmVec2 *pIn, const float s);
int kmVec2AreEqual(const kmVec2 *p1, const kmVec2 *p2);
kmVec2 *kmVec2Assign(kmVec2 *pOut, const kmVec2 *pIn);
kmVec2 *kmVec2RotateBy(kmVec2 *pOut, const kmVec2 *pIn, const float degrees, const kmVec2 *center);
float kmVec2DegreesBetween(const kmVec2 *v1, const kmVec2 *v2);
float kmVec2DistanceBetween(const kmVec2 *v1, const kmVec2 *v2);
kmVec2 *kmVec2MidPointBetween(kmVec2 *pOut, const kmVec2 *v1, const kmVec2 *v2);
kmVec2 *kmVec2Reflect(kmVec2 *pOut, const kmVec2 *pIn, const kmVec2 *normal);
extern const kmVec2 KM_VEC2_POS_Y;
extern const kmVec2 KM_VEC2_NEG_Y;
extern const kmVec2 KM_VEC2_NEG_X;
extern const kmVec2 KM_VEC2_POS_X;
extern const kmVec2 KM_VEC2_ZERO;
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
  return (((b - a) * randhash(seed)) / ((float) 4294967295U)) + a;
}

heman_image *heman_points_create(float *xy, int npoints, int nbands)
{
  heman_points *img = malloc(sizeof(heman_image));
  img->width = npoints;
  img->height = 1;
  img->nbands = nbands;
  int nbytes = ((sizeof(float)) * npoints) * nbands;
  img->data = malloc(nbytes);
  memcpy(img->data, xy, nbytes);
  return img;
}

void heman_points_destroy(heman_points *img)
{
  free(img->data);
  free(img);
}

heman_points *heman_points_from_grid(float width, float height, float cellsize, float jitter)
{
  int cols = width / cellsize;
  int rows = height / cellsize;
  int ncells = cols * rows;
  heman_points *result = heman_image_create(ncells, 1, 2);
  float rscale = (2.0 * jitter) / ((float) 32767);
  int j;
  #pragma omp parallel for
  for (j = 0; j < rows; j += 1)
  {
    float *dst = result->data + ((j * cols) * 2);
    unsigned int dst_idx = 0;
    float y = (cellsize * 0.5) + (cellsize * j);
    float x = cellsize * 0.5;
    for (int i = 0; i < cols; i += 1)
    {
      float rx = (rand() * rscale) - jitter;
      float ry = (rand() * rscale) - jitter;
      dst[dst_idx] = x + rx;
      dst_idx += 1;
      dst[dst_idx] = y + ry;
      dst_idx += 1;
      x += cellsize;
    }

  }

  return result;
}

kmVec2 sample_annulus(float radius, kmVec2 center, unsigned int *seedptr)
{
  unsigned int seed = *seedptr;
  kmVec2 r;
  float rscale = 1.0f / 4294967295U;
  while (1)
  {
    r.x = ((4 * rscale) * randhash(seed)) - 2;
    seed += 1;
    r.y = ((4 * rscale) * randhash(seed)) - 2;
    seed += 1;
    float r2 = kmVec2LengthSq(&r);
    if ((r2 > 1) && (r2 <= 4))
    {
      break;
    }
  }

  *seedptr = seed;
  kmVec2Scale(&r, &r, radius);
  kmVec2Add(&r, &r, &center);
  return r;
}

heman_points *heman_points_from_poisson(float width, float height, float radius)
{
  int maxattempts = 30;
  float rscale = 1.0f / 4294967295U;
  unsigned int seed = 0;
  kmVec2 rvec;
  rvec.x = (rvec.y = radius);
  float r2 = radius * radius;
  float cellsize = radius / sqrtf(2);
  float invcell = 1.0f / cellsize;
  int ncols = ceil(width * invcell);
  int nrows = ceil(height * invcell);
  int maxcol = ncols - 1;
  int maxrow = nrows - 1;
  int ncells = ncols * nrows;
  int *grid = malloc(ncells * (sizeof(int)));
  for (int i = 0; i < ncells; i += 1)
  {
    grid[i] = -1;
  }

  int *actives = malloc(ncells * (sizeof(int)));
  int nactives = 0;
  heman_points *result = heman_image_create(ncells, 1, 2);
  kmVec2 *samples = (kmVec2 *) result->data;
  int nsamples = 0;
  kmVec2 pt;
  pt.x = (width * randhash(seed)) * rscale;
  seed += 1;
  pt.y = (height * randhash(seed)) * rscale;
  seed += 1;
  grid[((int) (pt.x * invcell)) + (ncols * ((int) (pt.y * invcell)))] = (actives[nactives] = nsamples);
  nactives += 1;
  samples[nsamples] = pt;
  nsamples += 1;
  while (nsamples < ncells)
  {
    int aindex = (randhashf(seed++, 0, nactives) > (nactives - 1)) ? (nactives - 1) : (randhashf(seed++, 0, nactives));
    int sindex = actives[aindex];
    int found = 0;
    kmVec2 j;
    kmVec2 minj;
    kmVec2 maxj;
    kmVec2 delta;
    int attempt;
    for (attempt = 0; (attempt < maxattempts) && (!found); attempt += 1)
    {
      pt = sample_annulus(radius, samples[sindex], &seed);
      if ((((pt.x < 0) || (pt.x >= width)) || (pt.y < 0)) || (pt.y >= height))
      {
        continue;
      }
      minj = (maxj = pt);
      kmVec2Add(&maxj, &maxj, &rvec);
      kmVec2Subtract(&minj, &minj, &rvec);
      kmVec2Scale(&minj, &minj, invcell);
      kmVec2Scale(&maxj, &maxj, invcell);
      minj.x = (0 > ((maxcol > ((int) minj.x)) ? ((int) minj.x) : (maxcol))) ? (0) : ((maxcol > ((int) minj.x)) ? ((int) minj.x) : (maxcol));
      maxj.x = (0 > ((maxcol > ((int) maxj.x)) ? ((int) maxj.x) : (maxcol))) ? (0) : ((maxcol > ((int) maxj.x)) ? ((int) maxj.x) : (maxcol));
      minj.y = (0 > ((maxrow > ((int) minj.y)) ? ((int) minj.y) : (maxrow))) ? (0) : ((maxrow > ((int) minj.y)) ? ((int) minj.y) : (maxrow));
      maxj.y = (0 > ((maxrow > ((int) maxj.y)) ? ((int) maxj.y) : (maxrow))) ? (0) : ((maxrow > ((int) maxj.y)) ? ((int) maxj.y) : (maxrow));
      int reject = 0;
      for (j.y = minj.y; (j.y <= maxj.y) && (!reject); j.y += 1)
      {
        for (j.x = minj.x; (j.x <= maxj.x) && (!reject); j.x += 1)
        {
          int entry = grid[(((int) j.y) * ncols) + ((int) j.x)];
          if ((entry > (-1)) && (entry != sindex))
          {
            kmVec2Subtract(&delta, &samples[entry], &pt);
            if (kmVec2LengthSq(&delta) < r2)
            {
              reject = 1;
            }
          }
        }

      }

      if (reject)
      {
        continue;
      }
      found = 1;
    }

    if (found)
    {
      grid[((int) (pt.x * invcell)) + (ncols * ((int) (pt.y * invcell)))] = (actives[nactives] = nsamples);
      nactives += 1;
      samples[nsamples] = pt;
      nsamples += 1;
    }
    else
    {
      if ((--nactives) <= 0)
      {
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

heman_points *heman_points_from_density(heman_image *density, float minradius, float maxradius)
{
  assert(density->nbands == 1);
  float width = 1;
  float height = 1;
  int maxattempts = 30;
  float rscale = 1.0f / 4294967295U;
  unsigned int seed = 0;
  kmVec2 rvec;
  rvec.x = (rvec.y = maxradius);
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
  int *grid = malloc((ncells * (sizeof(int))) * gcapacity);
  int *ngrid = malloc(ncells * (sizeof(int)));
  for (int i = 0; i < ncells; i += 1)
  {
    ngrid[i] = 0;
  }

  int *actives = malloc(ncells * (sizeof(int)));
  int nactives = 0;
  int maxsamples = ncells * gcapacity;
  heman_points *result = heman_image_create(maxsamples, 1, 2);
  kmVec2 *samples = (kmVec2 *) result->data;
  int nsamples = 0;
  kmVec2 pt;
  pt.x = (width * randhash(seed)) * rscale;
  seed += 1;
  pt.y = (height * randhash(seed)) * rscale;
  seed += 1;
  actives[nactives] = nsamples;
  nactives += 1;
  gindex = ((int) (pt.x * invcell)) + (ncols * ((int) (pt.y * invcell)));
  grid[(gcapacity * gindex) + ngrid[gindex]] = nsamples;
  ngrid[gindex] += 1;
  samples[nsamples] = pt;
  nsamples += 1;
  while (nsamples < maxsamples)
  {
    int aindex = (randhashf(seed++, 0, nactives) > (nactives - 1)) ? (nactives - 1) : (randhashf(seed++, 0, nactives));
    int sindex = actives[aindex];
    int found = 0;
    kmVec2 j;
    kmVec2 minj;
    kmVec2 maxj;
    kmVec2 delta;
    int attempt;
    for (attempt = 0; (attempt < maxattempts) && (!found); attempt += 1)
    {
      pt = sample_annulus(maxradius, samples[sindex], &seed);
      if ((((pt.x < 0) || (pt.x >= width)) || (pt.y < 0)) || (pt.y >= height))
      {
        continue;
      }
      minj = (maxj = pt);
      kmVec2Add(&maxj, &maxj, &rvec);
      kmVec2Subtract(&minj, &minj, &rvec);
      kmVec2Scale(&minj, &minj, invcell);
      kmVec2Scale(&maxj, &maxj, invcell);
      minj.x = (0 > ((maxcol > ((int) minj.x)) ? ((int) minj.x) : (maxcol))) ? (0) : ((maxcol > ((int) minj.x)) ? ((int) minj.x) : (maxcol));
      maxj.x = (0 > ((maxcol > ((int) maxj.x)) ? ((int) maxj.x) : (maxcol))) ? (0) : ((maxcol > ((int) maxj.x)) ? ((int) maxj.x) : (maxcol));
      minj.y = (0 > ((maxrow > ((int) minj.y)) ? ((int) minj.y) : (maxrow))) ? (0) : ((maxrow > ((int) minj.y)) ? ((int) minj.y) : (maxrow));
      maxj.y = (0 > ((maxrow > ((int) maxj.y)) ? ((int) maxj.y) : (maxrow))) ? (0) : ((maxrow > ((int) maxj.y)) ? ((int) maxj.y) : (maxrow));
      int reject = 0;
      float densityval;
      heman_image_sample(density, pt.x, pt.y, &densityval);
      densityval = sqrt(densityval);
      float mindist = maxradius - (densityval * (maxradius - minradius));
      float r2 = mindist * mindist;
      for (j.y = minj.y; (j.y <= maxj.y) && (!reject); j.y += 1)
      {
        for (j.x = minj.x; (j.x <= maxj.x) && (!reject); j.x += 1)
        {
          for (int g = ((((int) j.y) * ncols) + ((int) j.x)) * gcapacity; g < ((((((int) j.y) * ncols) + ((int) j.x)) * gcapacity) + ngrid[(((int) j.y) * ncols) + ((int) j.x)]); g += 1)
          {
            int entry = grid[g];
            if (entry != sindex)
            {
              kmVec2Subtract(&delta, &samples[entry], &pt);
              if (kmVec2LengthSq(&delta) < r2)
              {
                reject = 1;
              }
            }
          }

        }

      }

      if (reject)
      {
        continue;
      }
      found = 1;
    }

    if (found && (ngrid[((int) (pt.x * invcell)) + (ncols * ((int) (pt.y * invcell)))] >= gcapacity))
    {
      found = 0;
    }
    if (found)
    {
      actives[nactives] = nsamples;
      nactives += 1;
      gindex = ((int) (pt.x * invcell)) + (ncols * ((int) (pt.y * invcell)));
      grid[(gcapacity * gindex) + ngrid[gindex]] = nsamples;
      ngrid[gindex] += 1;
      samples[nsamples] = pt;
      nsamples += 1;
    }
    else
    {
      if ((--nactives) <= 0)
      {
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

void helper_heman_points_from_poisson_1(float * const invcell_ref, int * const ncols_ref, int * const nactives_ref, int * const nsamples_ref, kmVec2 * const pt_ref, float width, float height, float radius, int maxattempts, unsigned int seed, kmVec2 rvec, float r2, int maxcol, int maxrow, int * const grid, int * const actives, kmVec2 * const samples)
{
  float invcell = *invcell_ref;
  int ncols = *ncols_ref;
  int nactives = *nactives_ref;
  int nsamples = *nsamples_ref;
  kmVec2 pt = *pt_ref;
  int aindex = (randhashf(seed++, 0, nactives) > (nactives - 1)) ? (nactives - 1) : (randhashf(seed++, 0, nactives));
  int sindex = actives[aindex];
  int found = 0;
  kmVec2 j;
  kmVec2 minj;
  kmVec2 maxj;
  kmVec2 delta;
  int attempt;
  for (attempt = 0; (attempt < maxattempts) && (!found); attempt += 1)
  {
    helper_helper_heman_points_from_poisson_1_1(&pt, &found, &j, &minj, &maxj, width, height, radius, seed, rvec, r2, maxcol, maxrow, grid, samples, invcell, ncols, sindex, delta);
  }

  if (found)
  {
    grid[((int) (pt.x * invcell)) + (ncols * ((int) (pt.y * invcell)))] = (actives[nactives] = nsamples);
    nactives += 1;
    samples[nsamples] = pt;
    nsamples += 1;
  }
  else
  {
    if ((--nactives) <= 0)
    {
      break;
    }
    actives[aindex] = actives[nactives];
  }
  *invcell_ref = invcell;
  *ncols_ref = ncols;
  *nactives_ref = nactives;
  *nsamples_ref = nsamples;
  *pt_ref = pt;
}

void helper_heman_points_from_density_1(int * const gindex_ref, int * const gcapacity_ref, int * const nactives_ref, int * const nsamples_ref, kmVec2 * const pt_ref, heman_image * const density, float minradius, float maxradius, float width, float height, int maxattempts, unsigned int seed, kmVec2 rvec, float invcell, int ncols, int maxcol, int maxrow, int * const grid, int * const ngrid, int * const actives, kmVec2 * const samples)
{
  int gindex = *gindex_ref;
  int gcapacity = *gcapacity_ref;
  int nactives = *nactives_ref;
  int nsamples = *nsamples_ref;
  kmVec2 pt = *pt_ref;
  int aindex = (randhashf(seed++, 0, nactives) > (nactives - 1)) ? (nactives - 1) : (randhashf(seed++, 0, nactives));
  int sindex = actives[aindex];
  int found = 0;
  kmVec2 j;
  kmVec2 minj;
  kmVec2 maxj;
  kmVec2 delta;
  int attempt;
  for (attempt = 0; (attempt < maxattempts) && (!found); attempt += 1)
  {
    helper_helper_heman_points_from_density_1_1(&pt, &found, &j, &minj, &maxj, density, minradius, maxradius, width, height, seed, rvec, invcell, ncols, maxcol, maxrow, grid, ngrid, samples, gcapacity, sindex, delta);
  }

  if (found && (ngrid[((int) (pt.x * invcell)) + (ncols * ((int) (pt.y * invcell)))] >= gcapacity))
  {
    found = 0;
  }
  if (found)
  {
    actives[nactives] = nsamples;
    nactives += 1;
    gindex = ((int) (pt.x * invcell)) + (ncols * ((int) (pt.y * invcell)));
    grid[(gcapacity * gindex) + ngrid[gindex]] = nsamples;
    ngrid[gindex] += 1;
    samples[nsamples] = pt;
    nsamples += 1;
  }
  else
  {
    if ((--nactives) <= 0)
    {
      break;
    }
    actives[aindex] = actives[nactives];
  }
  *gindex_ref = gindex;
  *gcapacity_ref = gcapacity;
  *nactives_ref = nactives;
  *nsamples_ref = nsamples;
  *pt_ref = pt;
}

void helper_helper_heman_points_from_poisson_1_1(kmVec2 * const pt_ref, int * const found_ref, kmVec2 * const j_ref, kmVec2 * const minj_ref, kmVec2 * const maxj_ref, float width, float height, float radius, unsigned int seed, kmVec2 rvec, float r2, int maxcol, int maxrow, int * const grid, kmVec2 * const samples, float invcell, int ncols, int sindex, kmVec2 delta)
{
  kmVec2 pt = *pt_ref;
  int found = *found_ref;
  kmVec2 j = *j_ref;
  kmVec2 minj = *minj_ref;
  kmVec2 maxj = *maxj_ref;
  pt = sample_annulus(radius, samples[sindex], &seed);
  if ((((pt.x < 0) || (pt.x >= width)) || (pt.y < 0)) || (pt.y >= height))
  {
    continue;
  }
  minj = (maxj = pt);
  kmVec2Add(&maxj, &maxj, &rvec);
  kmVec2Subtract(&minj, &minj, &rvec);
  kmVec2Scale(&minj, &minj, invcell);
  kmVec2Scale(&maxj, &maxj, invcell);
  minj.x = (0 > ((maxcol > ((int) minj.x)) ? ((int) minj.x) : (maxcol))) ? (0) : ((maxcol > ((int) minj.x)) ? ((int) minj.x) : (maxcol));
  maxj.x = (0 > ((maxcol > ((int) maxj.x)) ? ((int) maxj.x) : (maxcol))) ? (0) : ((maxcol > ((int) maxj.x)) ? ((int) maxj.x) : (maxcol));
  minj.y = (0 > ((maxrow > ((int) minj.y)) ? ((int) minj.y) : (maxrow))) ? (0) : ((maxrow > ((int) minj.y)) ? ((int) minj.y) : (maxrow));
  maxj.y = (0 > ((maxrow > ((int) maxj.y)) ? ((int) maxj.y) : (maxrow))) ? (0) : ((maxrow > ((int) maxj.y)) ? ((int) maxj.y) : (maxrow));
  int reject = 0;
  for (j.y = minj.y; (j.y <= maxj.y) && (!reject); j.y += 1)
  {
    for (j.x = minj.x; (j.x <= maxj.x) && (!reject); j.x += 1)
    {
      int entry = grid[(((int) j.y) * ncols) + ((int) j.x)];
      if ((entry > (-1)) && (entry != sindex))
      {
        kmVec2Subtract(&delta, &samples[entry], &pt);
        if (kmVec2LengthSq(&delta) < r2)
        {
          reject = 1;
        }
      }
    }

  }

  if (reject)
  {
    continue;
  }
  found = 1;
  *pt_ref = pt;
  *found_ref = found;
  *j_ref = j;
  *minj_ref = minj;
  *maxj_ref = maxj;
}

void helper_helper_heman_points_from_density_1_1(kmVec2 * const pt_ref, int * const found_ref, kmVec2 * const j_ref, kmVec2 * const minj_ref, kmVec2 * const maxj_ref, heman_image * const density, float minradius, float maxradius, float width, float height, unsigned int seed, kmVec2 rvec, float invcell, int ncols, int maxcol, int maxrow, int * const grid, int * const ngrid, kmVec2 * const samples, int gcapacity, int sindex, kmVec2 delta)
{
  kmVec2 pt = *pt_ref;
  int found = *found_ref;
  kmVec2 j = *j_ref;
  kmVec2 minj = *minj_ref;
  kmVec2 maxj = *maxj_ref;
  pt = sample_annulus(maxradius, samples[sindex], &seed);
  if ((((pt.x < 0) || (pt.x >= width)) || (pt.y < 0)) || (pt.y >= height))
  {
    continue;
  }
  minj = (maxj = pt);
  kmVec2Add(&maxj, &maxj, &rvec);
  kmVec2Subtract(&minj, &minj, &rvec);
  kmVec2Scale(&minj, &minj, invcell);
  kmVec2Scale(&maxj, &maxj, invcell);
  minj.x = (0 > ((maxcol > ((int) minj.x)) ? ((int) minj.x) : (maxcol))) ? (0) : ((maxcol > ((int) minj.x)) ? ((int) minj.x) : (maxcol));
  maxj.x = (0 > ((maxcol > ((int) maxj.x)) ? ((int) maxj.x) : (maxcol))) ? (0) : ((maxcol > ((int) maxj.x)) ? ((int) maxj.x) : (maxcol));
  minj.y = (0 > ((maxrow > ((int) minj.y)) ? ((int) minj.y) : (maxrow))) ? (0) : ((maxrow > ((int) minj.y)) ? ((int) minj.y) : (maxrow));
  maxj.y = (0 > ((maxrow > ((int) maxj.y)) ? ((int) maxj.y) : (maxrow))) ? (0) : ((maxrow > ((int) maxj.y)) ? ((int) maxj.y) : (maxrow));
  int reject = 0;
  float densityval;
  heman_image_sample(density, pt.x, pt.y, &densityval);
  densityval = sqrt(densityval);
  float mindist = maxradius - (densityval * (maxradius - minradius));
  float r2 = mindist * mindist;
  for (j.y = minj.y; (j.y <= maxj.y) && (!reject); j.y += 1)
  {
    for (j.x = minj.x; (j.x <= maxj.x) && (!reject); j.x += 1)
    {
      for (int g = ((((int) j.y) * ncols) + ((int) j.x)) * gcapacity; g < ((((((int) j.y) * ncols) + ((int) j.x)) * gcapacity) + ngrid[(((int) j.y) * ncols) + ((int) j.x)]); g += 1)
      {
        int entry = grid[g];
        if (entry != sindex)
        {
          kmVec2Subtract(&delta, &samples[entry], &pt);
          if (kmVec2LengthSq(&delta) < r2)
          {
            reject = 1;
          }
        }
      }

    }

  }

  if (reject)
  {
    continue;
  }
  found = 1;
  *pt_ref = pt;
  *found_ref = found;
  *j_ref = j;
  *minj_ref = minj;
  *maxj_ref = maxj;
}

