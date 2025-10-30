#include <assert.h>
#include <color.c>
#include <heman.h>
#include <image.h>
#include <math.h>
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

float _gamma = 2.2f;
void heman_color_set_gamma(float g)
{
  _gamma = g;
}

heman_image *heman_color_create_gradient(int width, int num_colors, const int *cp_locations, const heman_color *cp_values)
{
  assert((width > 0) && (num_colors >= 2));
  assert(cp_locations[0] == 0);
  assert(cp_locations[num_colors - 1] == (width - 1));
  float *f32colors = malloc(((sizeof(float)) * 3) * num_colors);
  float inv = 1.0f / 255.0f;
  float *f32color = f32colors;
  unsigned int f32color_idx = 0;
  const heman_color *u32color = cp_values;
  unsigned int u32color_idx = 0;
  for (int index = 0; index < num_colors; index += 1)
  {
    helper_heman_color_create_gradient_1(&f32color_idx, &u32color_idx, inv, f32color, u32color);
  }

  heman_image *result = heman_image_create(width, 1, 3);
  int index0 = 0;
  int index1 = 1;
  float *dst = result->data;
  unsigned int dst_idx = 0;
  float t;
  float invgamma = 1.0f / _gamma;
  for (int x = 0; x < width; x += 1)
  {
    helper_heman_color_create_gradient_2(&index0, &index1, &dst_idx, &t, &x, num_colors, cp_locations, f32colors, dst, invgamma);
  }

  free(f32colors);
  return result;
}

heman_image *heman_color_apply_gradient(heman_image *heightmap, float minheight, float maxheight, heman_image *gradient)
{
  assert(heightmap->nbands == 1);
  assert(gradient->height == 1);
  assert(gradient->nbands == 3);
  int w = heightmap->width;
  int h = heightmap->height;
  heman_image *result = heman_image_create(w, h, 3);
  int size = result->height * result->width;
  float *dst = result->data;
  unsigned int dst_idx = 0;
  const float *src = heightmap->data;
  unsigned int src_idx = 0;
  float scale = 1.0f / (maxheight - minheight);
  for (int i = 0; i < size; i += 1, dst_idx += 3, src_idx += 1)
  {
    float u = (0.0f > ((1.0f > ((src[src_idx] - minheight) * scale)) ? ((src[src_idx] - minheight) * scale) : (1.0f))) ? (0.0f) : ((1.0f > ((src[src_idx] - minheight) * scale)) ? ((src[src_idx] - minheight) * scale) : (1.0f));
    heman_image_sample(gradient, u, 0.5f, dst);
  }

  return result;
}

heman_image *heman_color_from_grayscale(heman_image *grayscale)
{
  assert(grayscale->nbands == 1);
  int w = grayscale->width;
  int h = grayscale->height;
  heman_image *result = heman_image_create(w, h, 3);
  int size = w * h;
  float *dst = result->data;
  unsigned int dst_idx = 0;
  const float *src = grayscale->data;
  unsigned int src_idx = 0;
  for (int i = 0; i < size; i += 1)
  {
    float v = src[src_idx];
    src_idx += 1;
    dst[dst_idx] = v;
    dst_idx += 1;
    dst[dst_idx] = v;
    dst_idx += 1;
    dst[dst_idx] = v;
    dst_idx += 1;
  }

  return result;
}

heman_image *heman_color_to_grayscale(heman_image *colorimg)
{
  assert(colorimg->nbands == 3);
  int w = colorimg->width;
  int h = colorimg->height;
  heman_image *result = heman_image_create(w, h, 1);
  int size = w * h;
  float *dst = result->data;
  unsigned int dst_idx = 0;
  const float *src = colorimg->data;
  unsigned int src_idx = 0;
  for (int i = 0; i < size; i += 1)
  {
    float r = src[src_idx];
    src_idx += 1;
    float g = src[src_idx];
    src_idx += 1;
    float b = src[src_idx];
    src_idx += 1;
    dst[dst_idx] = ((0.299 * r) + (0.587 * g)) + (0.114 * b);
    dst_idx += 1;
  }

  return result;
}

heman_image *heman_internal_rg(heman_image *cfield)
{
  assert(cfield->nbands == 2);
  int w = cfield->width;
  int h = cfield->height;
  heman_image *target = heman_image_create(w, h, 3);
  float *dst = target->data;
  unsigned int dst_idx = 0;
  float *src = cfield->data;
  unsigned int src_idx = 0;
  int size = w * h;
  for (int i = 0; i < size; i += 1)
  {
    float u = src[src_idx] / w;
    src_idx += 1;
    float v = src[src_idx] / h;
    src_idx += 1;
    dst[dst_idx] = u;
    dst_idx += 1;
    dst[dst_idx] = v;
    dst_idx += 1;
    dst[dst_idx] = 0;
    dst_idx += 1;
  }

  return target;
}

heman_image *heman_color_from_cpcf(heman_image *cfield, heman_image *texture)
{
  if (!texture)
  {
    return heman_internal_rg(cfield);
  }
  assert(cfield->nbands == 2);
  assert((texture->nbands == 3) || (texture->nbands == 4));
  assert(cfield->width == texture->width);
  assert(cfield->height == texture->height);
  int w = cfield->width;
  int h = cfield->height;
  heman_image *target = heman_image_create(w, h, texture->nbands);
  float *dst = target->data;
  unsigned int dst_idx = 0;
  float *src = cfield->data;
  unsigned int src_idx = 0;
  int size = w * h;
  for (int i = 0; i < size; i += 1)
  {
    float u = src[src_idx];
    src_idx += 1;
    float v = src[src_idx];
    src_idx += 1;
    float *texel = heman_image_texel(texture, u, v);
    unsigned int texel_idx = 0;
    for (int c = 0; c < texture->nbands; c += 1)
    {
      dst[dst_idx] = texel[texel_idx];
      texel_idx += 1;
      dst_idx += 1;
    }

  }

  return target;
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

float _gamma = 2.2f;
void heman_color_set_gamma(float g)
{
  _gamma = g;
}

heman_image *heman_color_create_gradient(int width, int num_colors, const int *cp_locations, const heman_color *cp_values)
{
  assert((width > 0) && (num_colors >= 2));
  assert(cp_locations[0] == 0);
  assert(cp_locations[num_colors - 1] == (width - 1));
  float *f32colors = malloc(((sizeof(float)) * 3) * num_colors);
  float inv = 1.0f / 255.0f;
  float *f32color = f32colors;
  unsigned int f32color_idx = 0;
  const heman_color *u32color = cp_values;
  unsigned int u32color_idx = 0;
  for (int index = 0; index < num_colors; index += 1)
  {
    heman_color rgb = u32color[u32color_idx];
    u32color_idx += 1;
    float r = ((float) (rgb >> 16)) * inv;
    float g = ((float) ((rgb >> 8) & 0xff)) * inv;
    float b = ((float) (rgb & 0xff)) * inv;
    f32color[f32color_idx] = pow(r, _gamma);
    f32color_idx += 1;
    f32color[f32color_idx] = pow(g, _gamma);
    f32color_idx += 1;
    f32color[f32color_idx] = pow(b, _gamma);
    f32color_idx += 1;
  }

  heman_image *result = heman_image_create(width, 1, 3);
  int index0 = 0;
  int index1 = 1;
  float *dst = result->data;
  unsigned int dst_idx = 0;
  float t;
  float invgamma = 1.0f / _gamma;
  for (int x = 0; x < width; x += 1)
  {
    int loc0 = cp_locations[index0];
    int loc1 = cp_locations[index1];
    if (loc0 == loc1)
    {
      t = 0;
    }
    else
    {
      t = (x - loc0) / ((float) (loc1 - loc0));
      if (t >= 1)
      {
        x -= 1;
        index0 += 1;
        index1 = ((index1 + 1) > (num_colors - 1)) ? (num_colors - 1) : (index1 + 1);
        continue;
      }
    }
    float r0 = f32colors[index0 * 3];
    float g0 = f32colors[(index0 * 3) + 1];
    float b0 = f32colors[(index0 * 3) + 2];
    float r1 = f32colors[index1 * 3];
    float g1 = f32colors[(index1 * 3) + 1];
    float b1 = f32colors[(index1 * 3) + 2];
    float invt = 1.0f - t;
    float r = (r0 * invt) + (r1 * t);
    float g = (g0 * invt) + (g1 * t);
    float b = (b0 * invt) + (b1 * t);
    dst[dst_idx] = pow(r, invgamma);
    dst_idx += 1;
    dst[dst_idx] = pow(g, invgamma);
    dst_idx += 1;
    dst[dst_idx] = pow(b, invgamma);
    dst_idx += 1;
  }

  free(f32colors);
  return result;
}

heman_image *heman_color_apply_gradient(heman_image *heightmap, float minheight, float maxheight, heman_image *gradient)
{
  assert(heightmap->nbands == 1);
  assert(gradient->height == 1);
  assert(gradient->nbands == 3);
  int w = heightmap->width;
  int h = heightmap->height;
  heman_image *result = heman_image_create(w, h, 3);
  int size = result->height * result->width;
  float *dst = result->data;
  unsigned int dst_idx = 0;
  const float *src = heightmap->data;
  unsigned int src_idx = 0;
  float scale = 1.0f / (maxheight - minheight);
  for (int i = 0; i < size; i += 1, dst_idx += 3, src_idx += 1)
  {
    float u = (0.0f > ((1.0f > ((src[src_idx] - minheight) * scale)) ? ((src[src_idx] - minheight) * scale) : (1.0f))) ? (0.0f) : ((1.0f > ((src[src_idx] - minheight) * scale)) ? ((src[src_idx] - minheight) * scale) : (1.0f));
    heman_image_sample(gradient, u, 0.5f, dst);
  }

  return result;
}

heman_image *heman_color_from_grayscale(heman_image *grayscale)
{
  assert(grayscale->nbands == 1);
  int w = grayscale->width;
  int h = grayscale->height;
  heman_image *result = heman_image_create(w, h, 3);
  int size = w * h;
  float *dst = result->data;
  unsigned int dst_idx = 0;
  const float *src = grayscale->data;
  unsigned int src_idx = 0;
  for (int i = 0; i < size; i += 1)
  {
    float v = src[src_idx];
    src_idx += 1;
    dst[dst_idx] = v;
    dst_idx += 1;
    dst[dst_idx] = v;
    dst_idx += 1;
    dst[dst_idx] = v;
    dst_idx += 1;
  }

  return result;
}

heman_image *heman_color_to_grayscale(heman_image *colorimg)
{
  assert(colorimg->nbands == 3);
  int w = colorimg->width;
  int h = colorimg->height;
  heman_image *result = heman_image_create(w, h, 1);
  int size = w * h;
  float *dst = result->data;
  unsigned int dst_idx = 0;
  const float *src = colorimg->data;
  unsigned int src_idx = 0;
  for (int i = 0; i < size; i += 1)
  {
    float r = src[src_idx];
    src_idx += 1;
    float g = src[src_idx];
    src_idx += 1;
    float b = src[src_idx];
    src_idx += 1;
    dst[dst_idx] = ((0.299 * r) + (0.587 * g)) + (0.114 * b);
    dst_idx += 1;
  }

  return result;
}

heman_image *heman_internal_rg(heman_image *cfield)
{
  assert(cfield->nbands == 2);
  int w = cfield->width;
  int h = cfield->height;
  heman_image *target = heman_image_create(w, h, 3);
  float *dst = target->data;
  unsigned int dst_idx = 0;
  float *src = cfield->data;
  unsigned int src_idx = 0;
  int size = w * h;
  for (int i = 0; i < size; i += 1)
  {
    float u = src[src_idx] / w;
    src_idx += 1;
    float v = src[src_idx] / h;
    src_idx += 1;
    dst[dst_idx] = u;
    dst_idx += 1;
    dst[dst_idx] = v;
    dst_idx += 1;
    dst[dst_idx] = 0;
    dst_idx += 1;
  }

  return target;
}

heman_image *heman_color_from_cpcf(heman_image *cfield, heman_image *texture)
{
  if (!texture)
  {
    return heman_internal_rg(cfield);
  }
  assert(cfield->nbands == 2);
  assert((texture->nbands == 3) || (texture->nbands == 4));
  assert(cfield->width == texture->width);
  assert(cfield->height == texture->height);
  int w = cfield->width;
  int h = cfield->height;
  heman_image *target = heman_image_create(w, h, texture->nbands);
  float *dst = target->data;
  unsigned int dst_idx = 0;
  float *src = cfield->data;
  unsigned int src_idx = 0;
  int size = w * h;
  for (int i = 0; i < size; i += 1)
  {
    float u = src[src_idx];
    src_idx += 1;
    float v = src[src_idx];
    src_idx += 1;
    float *texel = heman_image_texel(texture, u, v);
    unsigned int texel_idx = 0;
    for (int c = 0; c < texture->nbands; c += 1)
    {
      dst[dst_idx] = texel[texel_idx];
      texel_idx += 1;
      dst_idx += 1;
    }

  }

  return target;
}

void helper_heman_color_create_gradient_1(unsigned int * const f32color_idx_ref, unsigned int * const u32color_idx_ref, float inv, float * const f32color, const heman_color * const u32color)
{
  unsigned int f32color_idx = *f32color_idx_ref;
  unsigned int u32color_idx = *u32color_idx_ref;
  heman_color rgb = u32color[u32color_idx];
  u32color_idx += 1;
  float r = ((float) (rgb >> 16)) * inv;
  float g = ((float) ((rgb >> 8) & 0xff)) * inv;
  float b = ((float) (rgb & 0xff)) * inv;
  f32color[f32color_idx] = pow(r, _gamma);
  f32color_idx += 1;
  f32color[f32color_idx] = pow(g, _gamma);
  f32color_idx += 1;
  f32color[f32color_idx] = pow(b, _gamma);
  f32color_idx += 1;
  *f32color_idx_ref = f32color_idx;
  *u32color_idx_ref = u32color_idx;
}

void helper_heman_color_create_gradient_2(int * const index0_ref, int * const index1_ref, unsigned int * const dst_idx_ref, float * const t_ref, int * const x_ref, int num_colors, const int * const cp_locations, float * const f32colors, float * const dst, float invgamma)
{
  int index0 = *index0_ref;
  int index1 = *index1_ref;
  unsigned int dst_idx = *dst_idx_ref;
  float t = *t_ref;
  int x = *x_ref;
  int loc0 = cp_locations[index0];
  int loc1 = cp_locations[index1];
  if (loc0 == loc1)
  {
    t = 0;
  }
  else
  {
    t = (x - loc0) / ((float) (loc1 - loc0));
    if (t >= 1)
    {
      x -= 1;
      index0 += 1;
      index1 = ((index1 + 1) > (num_colors - 1)) ? (num_colors - 1) : (index1 + 1);
      continue;
    }
  }
  float r0 = f32colors[index0 * 3];
  float g0 = f32colors[(index0 * 3) + 1];
  float b0 = f32colors[(index0 * 3) + 2];
  float r1 = f32colors[index1 * 3];
  float g1 = f32colors[(index1 * 3) + 1];
  float b1 = f32colors[(index1 * 3) + 2];
  float invt = 1.0f - t;
  float r = (r0 * invt) + (r1 * t);
  float g = (g0 * invt) + (g1 * t);
  float b = (b0 * invt) + (b1 * t);
  dst[dst_idx] = pow(r, invgamma);
  dst_idx += 1;
  dst[dst_idx] = pow(g, invgamma);
  dst_idx += 1;
  dst[dst_idx] = pow(b, invgamma);
  dst_idx += 1;
  *index0_ref = index0;
  *index1_ref = index1;
  *dst_idx_ref = dst_idx;
  *t_ref = t;
  *x_ref = x;
}

