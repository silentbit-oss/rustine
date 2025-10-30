#include <assert.h>
#include <distance.c>
#include <heman.h>
#include <image.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
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

const float INF = 1E20;
static void edt(float *f, float *d, float *z, uint16_t *w, int n)
{
  int k = 0;
  float s;
  w[0] = 0;
  z[0] = -INF;
  z[1] = +INF;
  for (int q = 1; q < n; q += 1)
  {
    s = ((f[q] + (q * q)) - (f[w[k]] + (w[k] * w[k]))) / ((2 * q) - (2 * w[k]));
    while (s <= z[k])
    {
      k -= 1;
      s = ((f[q] + (q * q)) - (f[w[k]] + (w[k] * w[k]))) / ((2 * q) - (2 * w[k]));
    }

    k += 1;
    w[k] = q;
    z[k] = s;
    z[k + 1] = +INF;
  }

  k = 0;
  for (int q = 0; q < n; q += 1)
  {
    while (z[k + 1] < q)
    {
      k += 1;
    }

    d[q] = ((q - w[k]) * (q - w[k])) + f[w[k]];
  }

}

static void edt_with_payload(float *f, float *d, float *z, uint16_t *w, int n, float *payload_in, float *payload_out)
{
  int k = 0;
  float s;
  w[0] = 0;
  z[0] = -INF;
  z[1] = +INF;
  for (int q = 1; q < n; q += 1)
  {
    s = ((f[q] + (q * q)) - (f[w[k]] + (w[k] * w[k]))) / ((2 * q) - (2 * w[k]));
    while (s <= z[k])
    {
      k -= 1;
      s = ((f[q] + (q * q)) - (f[w[k]] + (w[k] * w[k]))) / ((2 * q) - (2 * w[k]));
    }

    k += 1;
    w[k] = q;
    z[k] = s;
    z[k + 1] = +INF;
  }

  k = 0;
  for (int q = 0; q < n; q += 1)
  {
    while (z[k + 1] < q)
    {
      k += 1;
    }

    d[q] = ((q - w[k]) * (q - w[k])) + f[w[k]];
    payload_out[q * 2] = payload_in[w[k] * 2];
    payload_out[(q * 2) + 1] = payload_in[(w[k] * 2) + 1];
  }

}

static void transform_to_distance(heman_image *sdf)
{
  int width = sdf->width;
  int height = sdf->height;
  int size = width * height;
  float *ff = calloc(size, sizeof(float));
  float *dd = calloc(size, sizeof(float));
  float *zz = calloc((height + 1) * (width + 1), sizeof(float));
  uint16_t *ww = calloc(size, sizeof(uint16_t));
  int x;
  #pragma omp parallel for
  for (x = 0; x < width; x += 1)
  {
    float *f = ff + (height * x);
    float *d = dd + (height * x);
    float *z = zz + ((height + 1) * x);
    uint16_t *w = ww + (height * x);
    for (int y = 0; y < height; y += 1)
    {
      f[y] = *((sdf->data + (y * width)) + x);
    }

    edt(f, d, z, w, height);
    for (int y = 0; y < height; y += 1)
    {
      *((sdf->data + (y * width)) + x) = d[y];
    }

  }

  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    float *f = ff + (width * y);
    float *d = dd + (width * y);
    float *z = zz + ((width + 1) * y);
    uint16_t *w = ww + (width * y);
    for (int x = 0; x < width; x += 1)
    {
      f[x] = *((sdf->data + (y * width)) + x);
    }

    edt(f, d, z, w, width);
    for (int x = 0; x < width; x += 1)
    {
      *((sdf->data + (y * width)) + x) = d[x];
    }

  }

  free(ff);
  free(dd);
  free(zz);
  free(ww);
}

static void transform_to_coordfield(heman_image *sdf, heman_image *cf)
{
  int width = sdf->width;
  int height = sdf->height;
  int size = width * height;
  float *ff = calloc(size, sizeof(float));
  float *dd = calloc(size, sizeof(float));
  float *zz = calloc((height + 1) * (width + 1), sizeof(float));
  uint16_t *ww = calloc(size, sizeof(uint16_t));
  int x;
  #pragma omp parallel for
  for (x = 0; x < width; x += 1)
  {
    helper_transform_to_coordfield_1(&width, &x, &x, &x, sdf, cf, height, ff, dd, zz, ww);
  }

  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    helper_transform_to_coordfield_2(&width, &y, sdf, cf, ff, dd, zz, ww);
  }

  free(ff);
  free(dd);
  free(zz);
  free(ww);
}

heman_image *heman_distance_create_sdf(heman_image *src)
{
  assert((src->nbands == 1) && "Distance field input must have only 1 band.");
  heman_image *positive = heman_image_create(src->width, src->height, 1);
  heman_image *negative = heman_image_create(src->width, src->height, 1);
  int size = src->height * src->width;
  float *pptr = positive->data;
  unsigned int pptr_idx = 0;
  float *nptr = negative->data;
  unsigned int nptr_idx = 0;
  float *sptr = src->data;
  unsigned int sptr_idx = 0;
  for (int i = 0; i < size; i += 1, sptr_idx += 1)
  {
    pptr[pptr_idx] = (sptr[sptr_idx]) ? (INF) : (0);
    pptr_idx += 1;
    nptr[nptr_idx] = (sptr[sptr_idx]) ? (0) : (INF);
    nptr_idx += 1;
  }

  transform_to_distance(positive);
  transform_to_distance(negative);
  float inv = 1.0f / src->width;
  pptr_idx = positive->data;
  nptr_idx = negative->data;
  for (int i = 0; i < size; i += 1, pptr_idx += 1, nptr_idx += 1)
  {
    pptr[pptr_idx] = (sqrt(*(&pptr[pptr_idx])) - sqrt(*(&nptr[nptr_idx]))) * inv;
  }

  heman_image_destroy(negative);
  return positive;
}

heman_image *heman_distance_create_df(heman_image *src)
{
  assert((src->nbands == 1) && "Distance field input must have only 1 band.");
  heman_image *positive = heman_image_create(src->width, src->height, 1);
  int size = src->height * src->width;
  float *pptr = positive->data;
  unsigned int pptr_idx = 0;
  float *sptr = src->data;
  unsigned int sptr_idx = 0;
  for (int i = 0; i < size; i += 1, sptr_idx += 1)
  {
    pptr[pptr_idx] = (sptr[sptr_idx]) ? (0) : (INF);
    pptr_idx += 1;
  }

  transform_to_distance(positive);
  float inv = 1.0f / src->width;
  pptr_idx = positive->data;
  for (int i = 0; i < size; i += 1, pptr_idx += 1)
  {
    pptr[pptr_idx] = sqrt(*(&pptr[pptr_idx])) * inv;
  }

  return positive;
}

heman_image *heman_distance_identity_cpcf(int width, int height)
{
  heman_image *retval = heman_image_create(width, height, 2);
  float *cdata = retval->data;
  unsigned int cdata_idx = 0;
  for (int y = 0; y < height; y += 1)
  {
    for (int x = 0; x < width; x += 1)
    {
      cdata[cdata_idx] = x;
      cdata_idx += 1;
      cdata[cdata_idx] = y;
      cdata_idx += 1;
    }

  }

  return retval;
}

heman_image *heman_distance_create_cpcf(heman_image *src)
{
  heman_image *negative = heman_image_create(src->width, src->height, 1);
  int size = src->height * src->width;
  float *nptr = negative->data;
  unsigned int nptr_idx = 0;
  float *sptr = src->data;
  unsigned int sptr_idx = 0;
  for (int i = 0; i < size; i += 1)
  {
    float val = 0;
    for (int b = 0; b < src->nbands; b += 1)
    {
      val += sptr[sptr_idx];
      sptr_idx += 1;
    }

    nptr[nptr_idx] = (val) ? (0) : (INF);
    nptr_idx += 1;
  }

  heman_image *coordfield = heman_distance_identity_cpcf(src->width, src->height);
  transform_to_coordfield(negative, coordfield);
  heman_image_destroy(negative);
  return coordfield;
}

heman_image *heman_distance_from_cpcf(heman_image *cf)
{
  assert((cf->nbands == 2) && "Coordinate field input must have 2 bands.");
  heman_image *udf = heman_image_create(cf->width, cf->height, 1);
  float *dptr = udf->data;
  unsigned int dptr_idx = 0;
  float *sptr = cf->data;
  unsigned int sptr_idx = 0;
  float scale = 1.0f / sqrt((cf->width * cf->width) + (cf->height * cf->height));
  for (int y = 0; y < cf->height; y += 1)
  {
    for (int x = 0; x < cf->width; x += 1)
    {
      float u = sptr[sptr_idx];
      sptr_idx += 1;
      float v = sptr[sptr_idx];
      sptr_idx += 1;
      float dist = sqrt(((u - x) * (u - x)) + ((v - y) * (v - y))) * scale;
      dptr[dptr_idx] = dist;
      dptr_idx += 1;
    }

  }

  return udf;
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

const float INF = 1E20;
static void edt(float *f, float *d, float *z, uint16_t *w, int n)
{
  int k = 0;
  float s;
  w[0] = 0;
  z[0] = -INF;
  z[1] = +INF;
  for (int q = 1; q < n; q += 1)
  {
    s = ((f[q] + (q * q)) - (f[w[k]] + (w[k] * w[k]))) / ((2 * q) - (2 * w[k]));
    while (s <= z[k])
    {
      k -= 1;
      s = ((f[q] + (q * q)) - (f[w[k]] + (w[k] * w[k]))) / ((2 * q) - (2 * w[k]));
    }

    k += 1;
    w[k] = q;
    z[k] = s;
    z[k + 1] = +INF;
  }

  k = 0;
  for (int q = 0; q < n; q += 1)
  {
    while (z[k + 1] < q)
    {
      k += 1;
    }

    d[q] = ((q - w[k]) * (q - w[k])) + f[w[k]];
  }

}

static void edt_with_payload(float *f, float *d, float *z, uint16_t *w, int n, float *payload_in, float *payload_out)
{
  int k = 0;
  float s;
  w[0] = 0;
  z[0] = -INF;
  z[1] = +INF;
  for (int q = 1; q < n; q += 1)
  {
    s = ((f[q] + (q * q)) - (f[w[k]] + (w[k] * w[k]))) / ((2 * q) - (2 * w[k]));
    while (s <= z[k])
    {
      k -= 1;
      s = ((f[q] + (q * q)) - (f[w[k]] + (w[k] * w[k]))) / ((2 * q) - (2 * w[k]));
    }

    k += 1;
    w[k] = q;
    z[k] = s;
    z[k + 1] = +INF;
  }

  k = 0;
  for (int q = 0; q < n; q += 1)
  {
    while (z[k + 1] < q)
    {
      k += 1;
    }

    d[q] = ((q - w[k]) * (q - w[k])) + f[w[k]];
    payload_out[q * 2] = payload_in[w[k] * 2];
    payload_out[(q * 2) + 1] = payload_in[(w[k] * 2) + 1];
  }

}

static void transform_to_distance(heman_image *sdf)
{
  int width = sdf->width;
  int height = sdf->height;
  int size = width * height;
  float *ff = calloc(size, sizeof(float));
  float *dd = calloc(size, sizeof(float));
  float *zz = calloc((height + 1) * (width + 1), sizeof(float));
  uint16_t *ww = calloc(size, sizeof(uint16_t));
  int x;
  #pragma omp parallel for
  for (x = 0; x < width; x += 1)
  {
    float *f = ff + (height * x);
    float *d = dd + (height * x);
    float *z = zz + ((height + 1) * x);
    uint16_t *w = ww + (height * x);
    for (int y = 0; y < height; y += 1)
    {
      f[y] = *((sdf->data + (y * width)) + x);
    }

    edt(f, d, z, w, height);
    for (int y = 0; y < height; y += 1)
    {
      *((sdf->data + (y * width)) + x) = d[y];
    }

  }

  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    float *f = ff + (width * y);
    float *d = dd + (width * y);
    float *z = zz + ((width + 1) * y);
    uint16_t *w = ww + (width * y);
    for (int x = 0; x < width; x += 1)
    {
      f[x] = *((sdf->data + (y * width)) + x);
    }

    edt(f, d, z, w, width);
    for (int x = 0; x < width; x += 1)
    {
      *((sdf->data + (y * width)) + x) = d[x];
    }

  }

  free(ff);
  free(dd);
  free(zz);
  free(ww);
}

static void transform_to_coordfield(heman_image *sdf, heman_image *cf)
{
  int width = sdf->width;
  int height = sdf->height;
  int size = width * height;
  float *ff = calloc(size, sizeof(float));
  float *dd = calloc(size, sizeof(float));
  float *zz = calloc((height + 1) * (width + 1), sizeof(float));
  uint16_t *ww = calloc(size, sizeof(uint16_t));
  int x;
  #pragma omp parallel for
  for (x = 0; x < width; x += 1)
  {
    float *pl1 = calloc(height * 2, sizeof(float));
    float *pl2 = calloc(height * 2, sizeof(float));
    float *f = ff + (height * x);
    float *d = dd + (height * x);
    float *z = zz + ((height + 1) * x);
    uint16_t *w = ww + (height * x);
    for (int y = 0; y < height; y += 1)
    {
      f[y] = *((sdf->data + (y * width)) + x);
      pl1[y * 2] = *((cf->data + (2 * ((y * width) + x))) + 0);
      pl1[(y * 2) + 1] = *((cf->data + (2 * ((y * width) + x))) + 1);
    }

    edt_with_payload(f, d, z, w, height, pl1, pl2);
    for (int y = 0; y < height; y += 1)
    {
      *((sdf->data + (y * width)) + x) = d[y];
      *((cf->data + (2 * ((y * width) + x))) + 0) = pl2[2 * y];
      *((cf->data + (2 * ((y * width) + x))) + 1) = pl2[(2 * y) + 1];
    }

    free(pl1);
    free(pl2);
  }

  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    float *pl1 = calloc(width * 2, sizeof(float));
    float *pl2 = calloc(width * 2, sizeof(float));
    float *f = ff + (width * y);
    float *d = dd + (width * y);
    float *z = zz + ((width + 1) * y);
    uint16_t *w = ww + (width * y);
    for (int x = 0; x < width; x += 1)
    {
      f[x] = *((sdf->data + (y * width)) + x);
      pl1[x * 2] = *((cf->data + (2 * ((y * width) + x))) + 0);
      pl1[(x * 2) + 1] = *((cf->data + (2 * ((y * width) + x))) + 1);
    }

    edt_with_payload(f, d, z, w, width, pl1, pl2);
    for (int x = 0; x < width; x += 1)
    {
      *((sdf->data + (y * width)) + x) = d[x];
      *((cf->data + (2 * ((y * width) + x))) + 0) = pl2[2 * x];
      *((cf->data + (2 * ((y * width) + x))) + 1) = pl2[(2 * x) + 1];
    }

    free(pl1);
    free(pl2);
  }

  free(ff);
  free(dd);
  free(zz);
  free(ww);
}

heman_image *heman_distance_create_sdf(heman_image *src)
{
  assert((src->nbands == 1) && "Distance field input must have only 1 band.");
  heman_image *positive = heman_image_create(src->width, src->height, 1);
  heman_image *negative = heman_image_create(src->width, src->height, 1);
  int size = src->height * src->width;
  float *pptr = positive->data;
  unsigned int pptr_idx = 0;
  float *nptr = negative->data;
  unsigned int nptr_idx = 0;
  float *sptr = src->data;
  unsigned int sptr_idx = 0;
  for (int i = 0; i < size; i += 1, sptr_idx += 1)
  {
    pptr[pptr_idx] = (sptr[sptr_idx]) ? (INF) : (0);
    pptr_idx += 1;
    nptr[nptr_idx] = (sptr[sptr_idx]) ? (0) : (INF);
    nptr_idx += 1;
  }

  transform_to_distance(positive);
  transform_to_distance(negative);
  float inv = 1.0f / src->width;
  pptr_idx = positive->data;
  nptr_idx = negative->data;
  for (int i = 0; i < size; i += 1, pptr_idx += 1, nptr_idx += 1)
  {
    pptr[pptr_idx] = (sqrt(*(&pptr[pptr_idx])) - sqrt(*(&nptr[nptr_idx]))) * inv;
  }

  heman_image_destroy(negative);
  return positive;
}

heman_image *heman_distance_create_df(heman_image *src)
{
  assert((src->nbands == 1) && "Distance field input must have only 1 band.");
  heman_image *positive = heman_image_create(src->width, src->height, 1);
  int size = src->height * src->width;
  float *pptr = positive->data;
  unsigned int pptr_idx = 0;
  float *sptr = src->data;
  unsigned int sptr_idx = 0;
  for (int i = 0; i < size; i += 1, sptr_idx += 1)
  {
    pptr[pptr_idx] = (sptr[sptr_idx]) ? (0) : (INF);
    pptr_idx += 1;
  }

  transform_to_distance(positive);
  float inv = 1.0f / src->width;
  pptr_idx = positive->data;
  for (int i = 0; i < size; i += 1, pptr_idx += 1)
  {
    pptr[pptr_idx] = sqrt(*(&pptr[pptr_idx])) * inv;
  }

  return positive;
}

heman_image *heman_distance_identity_cpcf(int width, int height)
{
  heman_image *retval = heman_image_create(width, height, 2);
  float *cdata = retval->data;
  unsigned int cdata_idx = 0;
  for (int y = 0; y < height; y += 1)
  {
    for (int x = 0; x < width; x += 1)
    {
      cdata[cdata_idx] = x;
      cdata_idx += 1;
      cdata[cdata_idx] = y;
      cdata_idx += 1;
    }

  }

  return retval;
}

heman_image *heman_distance_create_cpcf(heman_image *src)
{
  heman_image *negative = heman_image_create(src->width, src->height, 1);
  int size = src->height * src->width;
  float *nptr = negative->data;
  unsigned int nptr_idx = 0;
  float *sptr = src->data;
  unsigned int sptr_idx = 0;
  for (int i = 0; i < size; i += 1)
  {
    float val = 0;
    for (int b = 0; b < src->nbands; b += 1)
    {
      val += sptr[sptr_idx];
      sptr_idx += 1;
    }

    nptr[nptr_idx] = (val) ? (0) : (INF);
    nptr_idx += 1;
  }

  heman_image *coordfield = heman_distance_identity_cpcf(src->width, src->height);
  transform_to_coordfield(negative, coordfield);
  heman_image_destroy(negative);
  return coordfield;
}

heman_image *heman_distance_from_cpcf(heman_image *cf)
{
  assert((cf->nbands == 2) && "Coordinate field input must have 2 bands.");
  heman_image *udf = heman_image_create(cf->width, cf->height, 1);
  float *dptr = udf->data;
  unsigned int dptr_idx = 0;
  float *sptr = cf->data;
  unsigned int sptr_idx = 0;
  float scale = 1.0f / sqrt((cf->width * cf->width) + (cf->height * cf->height));
  for (int y = 0; y < cf->height; y += 1)
  {
    for (int x = 0; x < cf->width; x += 1)
    {
      float u = sptr[sptr_idx];
      sptr_idx += 1;
      float v = sptr[sptr_idx];
      sptr_idx += 1;
      float dist = sqrt(((u - x) * (u - x)) + ((v - y) * (v - y))) * scale;
      dptr[dptr_idx] = dist;
      dptr_idx += 1;
    }

  }

  return udf;
}

void helper_transform_to_coordfield_1(int * const width_ref, int * const x_ref, int * const x_ref, int * const x_ref, heman_image * const sdf, heman_image * const cf, int height, float * const ff, float * const dd, float * const zz, uint16_t * const ww)
{
  int width = *width_ref;
  int x = *x_ref;
  int x = *x_ref;
  int x = *x_ref;
  float *pl1 = calloc(height * 2, sizeof(float));
  float *pl2 = calloc(height * 2, sizeof(float));
  float *f = ff + (height * x);
  float *d = dd + (height * x);
  float *z = zz + ((height + 1) * x);
  uint16_t *w = ww + (height * x);
  for (int y = 0; y < height; y += 1)
  {
    f[y] = *((sdf->data + (y * width)) + x);
    pl1[y * 2] = *((cf->data + (2 * ((y * width) + x))) + 0);
    pl1[(y * 2) + 1] = *((cf->data + (2 * ((y * width) + x))) + 1);
  }

  edt_with_payload(f, d, z, w, height, pl1, pl2);
  for (int y = 0; y < height; y += 1)
  {
    *((sdf->data + (y * width)) + x) = d[y];
    *((cf->data + (2 * ((y * width) + x))) + 0) = pl2[2 * y];
    *((cf->data + (2 * ((y * width) + x))) + 1) = pl2[(2 * y) + 1];
  }

  free(pl1);
  free(pl2);
  *width_ref = width;
  *x_ref = x;
  *x_ref = x;
  *x_ref = x;
}

void helper_transform_to_coordfield_2(int * const width_ref, int * const y_ref, heman_image * const sdf, heman_image * const cf, float * const ff, float * const dd, float * const zz, uint16_t * const ww)
{
  int width = *width_ref;
  int y = *y_ref;
  float *pl1 = calloc(width * 2, sizeof(float));
  float *pl2 = calloc(width * 2, sizeof(float));
  float *f = ff + (width * y);
  float *d = dd + (width * y);
  float *z = zz + ((width + 1) * y);
  uint16_t *w = ww + (width * y);
  for (int x = 0; x < width; x += 1)
  {
    f[x] = *((sdf->data + (y * width)) + x);
    pl1[x * 2] = *((cf->data + (2 * ((y * width) + x))) + 0);
    pl1[(x * 2) + 1] = *((cf->data + (2 * ((y * width) + x))) + 1);
  }

  edt_with_payload(f, d, z, w, width, pl1, pl2);
  for (int x = 0; x < width; x += 1)
  {
    *((sdf->data + (y * width)) + x) = d[x];
    *((cf->data + (2 * ((y * width) + x))) + 0) = pl2[2 * x];
    *((cf->data + (2 * ((y * width) + x))) + 1) = pl2[(2 * x) + 1];
  }

  free(pl1);
  free(pl2);
  *width_ref = width;
  *y_ref = y;
}

