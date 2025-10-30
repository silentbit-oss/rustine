#include <assert.h>
#include <heman.h>
#include <image.h>
#include <lighting.c>
#include <math.h>
#include <memory.h>
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
static float _occlusion_scale = 1.0f;
void heman_lighting_set_occlusion_scale(float s)
{
  _occlusion_scale = s;
}

heman_image *heman_lighting_compute_normals(heman_image *heightmap)
{
  assert(heightmap->nbands == 1);
  int width = heightmap->width;
  int height = heightmap->height;
  heman_image *result = heman_image_create(width, height, 3);
  float invh = 1.0f / height;
  float invw = 1.0f / width;
  int maxx = width - 1;
  int maxy = height - 1;
  kmVec3 *normals = (kmVec3 *) result->data;
  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    helper_heman_lighting_compute_normals_1(&y, heightmap, width, invh, invw, maxx, maxy, normals);
  }

  return result;
}

heman_image *heman_lighting_apply(heman_image *heightmap, heman_image *albedo, float occlusion, float diffuse, float diffuse_softening, const float *light_position)
{
  unsigned int light_position_idx = 0;
  assert(heightmap->nbands == 1);
  int width = heightmap->width;
  int height = heightmap->height;
  heman_image *final = heman_image_create(width, height, 3);
  heman_image *normals = heman_lighting_compute_normals(heightmap);
  heman_image *occ = heman_lighting_compute_occlusion(heightmap);
  if (albedo)
  {
    assert(albedo->nbands == 3);
    assert(albedo->width == width);
    assert(albedo->height == height);
  }
  static float default_pos[] = {-0.5f, 0.5f, 1.0f};
  if (!(&light_position[light_position_idx]))
  {
    light_position_idx = default_pos;
  }
  kmVec3 *colors = (kmVec3 *) final->data;
  float invgamma = 1.0f / _gamma;
  kmVec3 L;
  L.x = light_position[0 + light_position_idx];
  L.y = light_position[1 + light_position_idx];
  L.z = light_position[2 + light_position_idx];
  kmVec3Normalize(&L, &L);
  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    helper_heman_lighting_apply_1(&y, albedo, occlusion, diffuse, diffuse_softening, width, normals, occ, colors, invgamma, L);
  }

  heman_image_destroy(normals);
  heman_image_destroy(occ);
  return final;
}

static float azimuth_slope(kmVec3 a, kmVec3 b)
{
  kmVec3 d;
  kmVec3Subtract(&d, &a, &b);
  float x = kmVec3Length(&d);
  float y = b.z - a.z;
  return y / x;
}

static float compute_occlusion(kmVec3 thispt, kmVec3 horizonpt)
{
  kmVec3 direction;
  kmVec3Subtract(&direction, &horizonpt, &thispt);
  kmVec3Normalize(&direction, &direction);
  float dot = kmVec3Dot(&direction, &KM_VEC3_POS_Z);
  return atan((dot > 0.0f) ? (dot) : (0.0f)) * 0.63661977236;
}

static void horizon_scan(heman_image *heightmap, heman_image *result, int *startpts, int dx, int dy)
{
  int w = heightmap->width;
  int h = heightmap->height;
  int sx = (dx > 0) - (dx < 0);
  int sy = (dy > 0) - (dy < 0);
  int ax = abs(dx);
  int ay = abs(dy);
  int nsweeps = ((ay * w) + (ax * h)) - ((ax + ay) - 1);
  int *p = startpts;
  unsigned int p_idx = 0;
  for (int x = -ax; x < (w - ax); x += 1)
  {
    for (int y = -ay; y < (h - ay); y += 1)
    {
      if ((((x >= 0) && (x < w)) && (y >= 0)) && (y < h))
      {
        continue;
      }
      p[p_idx] = (sx < 0) ? ((w - x) - 1) : (x);
      p_idx += 1;
      p[p_idx] = (sy < 0) ? ((h - y) - 1) : (y);
      p_idx += 1;
    }

  }

  assert(nsweeps == (((&p[p_idx]) - startpts) / 2));
  int pathlen = 0;
  int i = startpts[0];
  int j = startpts[1];
  do
  {
    i += dx;
    j += dy;
    pathlen += 1;
  }
  while ((((i >= 0) && (i < w)) && (j >= 0)) && (j < h));
  float cellw = _occlusion_scale / ((w > h) ? (w) : (h));
  float cellh = _occlusion_scale / ((w > h) ? (w) : (h));
  kmVec3 *hull_buffer = malloc(((sizeof(kmVec3)) * pathlen) * nsweeps);
  int sweep;
  #pragma omp parallel for
  for (sweep = 0; sweep < nsweeps; sweep += 1)
  {
    helper_horizon_scan_1(heightmap, result, startpts, dx, dy, w, h, pathlen, cellw, cellh, hull_buffer, sweep);
  }

  free(hull_buffer);
}

heman_image *heman_lighting_compute_occlusion(heman_image *heightmap)
{
  assert(heightmap->nbands == 1);
  int width = heightmap->width;
  int height = heightmap->height;
  heman_image *result = heman_image_create(width, height, 1);
  memset(result->data, 0, ((sizeof(float)) * width) * height);
  const int scans[16 * 2] = {1, 0, 0, 1, -1, 0, 0, -1, 1, 1, -1, -1, 1, -1, -1, 1, 2, 1, 2, -1, -2, 1, -2, -1, 1, 2, 1, -2, -1, 2, -1, -2};
  int *startpts = malloc((((sizeof(int)) * 2) * 3) * kmMax(width, height));
  for (int i = 0; i < 16; i += 1)
  {
    int dx = scans[i * 2];
    int dy = scans[(i * 2) + 1];
    horizon_scan(heightmap, result, startpts, dx, dy);
  }

  for (int i = 0; i < (width * height); i += 1)
  {
    result->data[i] = 1.0f - result->data[i];
    assert((result->data[i] >= 0.0) && (result->data[i] <= 1.0f));
  }

  free(startpts);
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
static float _occlusion_scale = 1.0f;
void heman_lighting_set_occlusion_scale(float s)
{
  _occlusion_scale = s;
}

heman_image *heman_lighting_compute_normals(heman_image *heightmap)
{
  assert(heightmap->nbands == 1);
  int width = heightmap->width;
  int height = heightmap->height;
  heman_image *result = heman_image_create(width, height, 3);
  float invh = 1.0f / height;
  float invw = 1.0f / width;
  int maxx = width - 1;
  int maxy = height - 1;
  kmVec3 *normals = (kmVec3 *) result->data;
  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    float v = y * invh;
    int y1 = ((y + 1) > maxy) ? (maxy) : (y + 1);
    kmVec3 p;
    kmVec3 px;
    kmVec3 py;
    kmVec3 *n = normals + (y * width);
    unsigned int n_idx = 0;
    for (int x = 0; x < width; x += 1, n_idx += 1)
    {
      float u = x * invw;
      int x1 = ((x + 1) > maxx) ? (maxx) : (x + 1);
      p.x = u;
      p.y = v;
      p.z = *heman_image_texel(heightmap, x, y);
      px.x = u + invw;
      px.y = v;
      px.z = *heman_image_texel(heightmap, x1, y);
      py.x = u;
      py.y = v + invh;
      py.z = *heman_image_texel(heightmap, x, y1);
      kmVec3Subtract(&px, &px, &p);
      kmVec3Subtract(&py, &py, &p);
      kmVec3Cross(n, &px, &py);
      kmVec3Normalize(n, n);
      n->y *= -1;
    }

  }

  return result;
}

heman_image *heman_lighting_apply(heman_image *heightmap, heman_image *albedo, float occlusion, float diffuse, float diffuse_softening, const float *light_position)
{
  unsigned int light_position_idx = 0;
  assert(heightmap->nbands == 1);
  int width = heightmap->width;
  int height = heightmap->height;
  heman_image *final = heman_image_create(width, height, 3);
  heman_image *normals = heman_lighting_compute_normals(heightmap);
  heman_image *occ = heman_lighting_compute_occlusion(heightmap);
  if (albedo)
  {
    assert(albedo->nbands == 3);
    assert(albedo->width == width);
    assert(albedo->height == height);
  }
  static float default_pos[] = {-0.5f, 0.5f, 1.0f};
  if (!(&light_position[light_position_idx]))
  {
    light_position_idx = default_pos;
  }
  kmVec3 *colors = (kmVec3 *) final->data;
  float invgamma = 1.0f / _gamma;
  kmVec3 L;
  L.x = light_position[0 + light_position_idx];
  L.y = light_position[1 + light_position_idx];
  L.z = light_position[2 + light_position_idx];
  kmVec3Normalize(&L, &L);
  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    kmVec3 *color = colors + (y * width);
    unsigned int color_idx = 0;
    for (int x = 0; x < width; x += 1, color_idx += 1)
    {
      kmVec3 *N = (kmVec3 *) heman_image_texel(normals, x, y);
      kmVec3Lerp(N, N, &KM_VEC3_POS_Z, diffuse_softening);
      float df = 1 - (diffuse * (1 - kmClamp(kmVec3Dot(N, &L), 0, 1)));
      float of = 1 - (occlusion * (1 - (*heman_image_texel(occ, x, y))));
      if (albedo)
      {
        color[color_idx] = *((kmVec3 *) heman_image_texel(albedo, x, y));
      }
      else
      {
        color->x = (color->y = (color->z = 1));
      }
      color->x = pow(color->x, _gamma);
      color->y = pow(color->y, _gamma);
      color->z = pow(color->z, _gamma);
      kmVec3Scale(color, color, df * of);
      color->x = pow(color->x, invgamma);
      color->y = pow(color->y, invgamma);
      color->z = pow(color->z, invgamma);
    }

  }

  heman_image_destroy(normals);
  heman_image_destroy(occ);
  return final;
}

static float azimuth_slope(kmVec3 a, kmVec3 b)
{
  kmVec3 d;
  kmVec3Subtract(&d, &a, &b);
  float x = kmVec3Length(&d);
  float y = b.z - a.z;
  return y / x;
}

static float compute_occlusion(kmVec3 thispt, kmVec3 horizonpt)
{
  kmVec3 direction;
  kmVec3Subtract(&direction, &horizonpt, &thispt);
  kmVec3Normalize(&direction, &direction);
  float dot = kmVec3Dot(&direction, &KM_VEC3_POS_Z);
  return atan((dot > 0.0f) ? (dot) : (0.0f)) * 0.63661977236;
}

static void horizon_scan(heman_image *heightmap, heman_image *result, int *startpts, int dx, int dy)
{
  int w = heightmap->width;
  int h = heightmap->height;
  int sx = (dx > 0) - (dx < 0);
  int sy = (dy > 0) - (dy < 0);
  int ax = abs(dx);
  int ay = abs(dy);
  int nsweeps = ((ay * w) + (ax * h)) - ((ax + ay) - 1);
  int *p = startpts;
  unsigned int p_idx = 0;
  for (int x = -ax; x < (w - ax); x += 1)
  {
    for (int y = -ay; y < (h - ay); y += 1)
    {
      if ((((x >= 0) && (x < w)) && (y >= 0)) && (y < h))
      {
        continue;
      }
      p[p_idx] = (sx < 0) ? ((w - x) - 1) : (x);
      p_idx += 1;
      p[p_idx] = (sy < 0) ? ((h - y) - 1) : (y);
      p_idx += 1;
    }

  }

  assert(nsweeps == (((&p[p_idx]) - startpts) / 2));
  int pathlen = 0;
  int i = startpts[0];
  int j = startpts[1];
  do
  {
    i += dx;
    j += dy;
    pathlen += 1;
  }
  while ((((i >= 0) && (i < w)) && (j >= 0)) && (j < h));
  float cellw = _occlusion_scale / ((w > h) ? (w) : (h));
  float cellh = _occlusion_scale / ((w > h) ? (w) : (h));
  kmVec3 *hull_buffer = malloc(((sizeof(kmVec3)) * pathlen) * nsweeps);
  int sweep;
  #pragma omp parallel for
  for (sweep = 0; sweep < nsweeps; sweep += 1)
  {
    kmVec3 *convex_hull = hull_buffer + (sweep * pathlen);
    int *p = startpts + (sweep * 2);
    unsigned int p_idx = 0;
    int i = p[0 + p_idx];
    int j = p[1 + p_idx];
    kmVec3 thispt;
    kmVec3 horizonpt;
    thispt.x = i * cellw;
    thispt.y = j * cellh;
    thispt.z = *heman_image_texel(heightmap, (0 > (((w - 1) > i) ? (i) : (w - 1))) ? (0) : (((w - 1) > i) ? (i) : (w - 1)), (0 > (((h - 1) > j) ? (j) : (h - 1))) ? (0) : (((h - 1) > j) ? (j) : (h - 1)));
    int stack_top = 0;
    convex_hull[0] = thispt;
    i += dx, j += dy;
    while ((((i >= 0) && (i < w)) && (j >= 0)) && (j < h))
    {
      thispt.x = i * cellw;
      thispt.y = j * cellh;
      thispt.z = *heman_image_texel(heightmap, i, j);
      while (stack_top > 0)
      {
        float s1 = azimuth_slope(thispt, convex_hull[stack_top]);
        float s2 = azimuth_slope(thispt, convex_hull[stack_top - 1]);
        if (s1 >= s2)
        {
          break;
        }
        stack_top -= 1;
      }

      horizonpt = convex_hull[stack_top];
      stack_top += 1;
      assert(stack_top < pathlen);
      convex_hull[stack_top] = thispt;
      float occlusion = compute_occlusion(thispt, horizonpt);
      *heman_image_texel(result, i, j) += (1.0f / 16.0f) * occlusion;
      i += dx;
      j += dy;
    }

  }

  free(hull_buffer);
}

heman_image *heman_lighting_compute_occlusion(heman_image *heightmap)
{
  assert(heightmap->nbands == 1);
  int width = heightmap->width;
  int height = heightmap->height;
  heman_image *result = heman_image_create(width, height, 1);
  memset(result->data, 0, ((sizeof(float)) * width) * height);
  const int scans[16 * 2] = {1, 0, 0, 1, -1, 0, 0, -1, 1, 1, -1, -1, 1, -1, -1, 1, 2, 1, 2, -1, -2, 1, -2, -1, 1, 2, 1, -2, -1, 2, -1, -2};
  int *startpts = malloc((((sizeof(int)) * 2) * 3) * kmMax(width, height));
  for (int i = 0; i < 16; i += 1)
  {
    int dx = scans[i * 2];
    int dy = scans[(i * 2) + 1];
    horizon_scan(heightmap, result, startpts, dx, dy);
  }

  for (int i = 0; i < (width * height); i += 1)
  {
    result->data[i] = 1.0f - result->data[i];
    assert((result->data[i] >= 0.0) && (result->data[i] <= 1.0f));
  }

  free(startpts);
  return result;
}

void helper_heman_lighting_compute_normals_1(int * const y_ref, heman_image * const heightmap, int width, float invh, float invw, int maxx, int maxy, kmVec3 * const normals)
{
  int y = *y_ref;
  float v = y * invh;
  int y1 = ((y + 1) > maxy) ? (maxy) : (y + 1);
  kmVec3 p;
  kmVec3 px;
  kmVec3 py;
  kmVec3 *n = normals + (y * width);
  unsigned int n_idx = 0;
  for (int x = 0; x < width; x += 1, n_idx += 1)
  {
    float u = x * invw;
    int x1 = ((x + 1) > maxx) ? (maxx) : (x + 1);
    p.x = u;
    p.y = v;
    p.z = *heman_image_texel(heightmap, x, y);
    px.x = u + invw;
    px.y = v;
    px.z = *heman_image_texel(heightmap, x1, y);
    py.x = u;
    py.y = v + invh;
    py.z = *heman_image_texel(heightmap, x, y1);
    kmVec3Subtract(&px, &px, &p);
    kmVec3Subtract(&py, &py, &p);
    kmVec3Cross(n, &px, &py);
    kmVec3Normalize(n, n);
    n->y *= -1;
  }

  *y_ref = y;
}

void helper_heman_lighting_apply_1(int * const y_ref, heman_image * const albedo, float occlusion, float diffuse, float diffuse_softening, int width, heman_image * const normals, heman_image * const occ, kmVec3 * const colors, float invgamma, kmVec3 L)
{
  int y = *y_ref;
  kmVec3 *color = colors + (y * width);
  unsigned int color_idx = 0;
  for (int x = 0; x < width; x += 1, color_idx += 1)
  {
    kmVec3 *N = (kmVec3 *) heman_image_texel(normals, x, y);
    kmVec3Lerp(N, N, &KM_VEC3_POS_Z, diffuse_softening);
    float df = 1 - (diffuse * (1 - kmClamp(kmVec3Dot(N, &L), 0, 1)));
    float of = 1 - (occlusion * (1 - (*heman_image_texel(occ, x, y))));
    if (albedo)
    {
      color[color_idx] = *((kmVec3 *) heman_image_texel(albedo, x, y));
    }
    else
    {
      color->x = (color->y = (color->z = 1));
    }
    color->x = pow(color->x, _gamma);
    color->y = pow(color->y, _gamma);
    color->z = pow(color->z, _gamma);
    kmVec3Scale(color, color, df * of);
    color->x = pow(color->x, invgamma);
    color->y = pow(color->y, invgamma);
    color->z = pow(color->z, invgamma);
  }

  *y_ref = y;
}

void helper_horizon_scan_1(heman_image * const heightmap, heman_image * const result, int * const startpts, int dx, int dy, int w, int h, int pathlen, float cellw, float cellh, kmVec3 * const hull_buffer, int sweep)
{
  kmVec3 *convex_hull = hull_buffer + (sweep * pathlen);
  int *p = startpts + (sweep * 2);
  unsigned int p_idx = 0;
  int i = p[0 + p_idx];
  int j = p[1 + p_idx];
  kmVec3 thispt;
  kmVec3 horizonpt;
  thispt.x = i * cellw;
  thispt.y = j * cellh;
  thispt.z = *heman_image_texel(heightmap, (0 > (((w - 1) > i) ? (i) : (w - 1))) ? (0) : (((w - 1) > i) ? (i) : (w - 1)), (0 > (((h - 1) > j) ? (j) : (h - 1))) ? (0) : (((h - 1) > j) ? (j) : (h - 1)));
  int stack_top = 0;
  convex_hull[0] = thispt;
  i += dx, j += dy;
  while ((((i >= 0) && (i < w)) && (j >= 0)) && (j < h))
  {
    helper_helper_horizon_scan_1_1(&i, &j, &thispt, &horizonpt, &stack_top, heightmap, result, dx, dy, pathlen, cellw, cellh, convex_hull);
  }

}

void helper_helper_horizon_scan_1_1(int * const i_ref, int * const j_ref, kmVec3 * const thispt_ref, kmVec3 * const horizonpt_ref, int * const stack_top_ref, heman_image * const heightmap, heman_image * const result, int dx, int dy, int pathlen, float cellw, float cellh, kmVec3 * const convex_hull)
{
  int i = *i_ref;
  int j = *j_ref;
  kmVec3 thispt = *thispt_ref;
  kmVec3 horizonpt = *horizonpt_ref;
  int stack_top = *stack_top_ref;
  thispt.x = i * cellw;
  thispt.y = j * cellh;
  thispt.z = *heman_image_texel(heightmap, i, j);
  while (stack_top > 0)
  {
    float s1 = azimuth_slope(thispt, convex_hull[stack_top]);
    float s2 = azimuth_slope(thispt, convex_hull[stack_top - 1]);
    if (s1 >= s2)
    {
      break;
    }
    stack_top -= 1;
  }

  horizonpt = convex_hull[stack_top];
  stack_top += 1;
  assert(stack_top < pathlen);
  convex_hull[stack_top] = thispt;
  float occlusion = compute_occlusion(thispt, horizonpt);
  *heman_image_texel(result, i, j) += (1.0f / 16.0f) * occlusion;
  i += dx;
  j += dy;
  *i_ref = i;
  *j_ref = j;
  *thispt_ref = thispt;
  *horizonpt_ref = horizonpt;
  *stack_top_ref = stack_top;
}

