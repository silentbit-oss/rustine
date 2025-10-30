#include <assert.h>
#include <heman.h>
#include <image.h>
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

void heman_draw_points(heman_image *target, heman_points *pts, float val)
{
  float *src = pts->data;
  unsigned int src_idx = 0;
  for (int k = 0; k < pts->width; k += 1)
  {
    float x = src[0 + src_idx];
    float y = src[1 + src_idx];
    src_idx += pts->nbands;
    int i = x * target->width;
    int j = y * target->height;
    if ((((i < 0) || (i >= target->width)) || (j < 0)) || (j >= target->height))
    {
      continue;
    }
    float *texel = heman_image_texel(target, i, j);
    unsigned int texel_idx = 0;
    for (int c = 0; c < target->nbands; c += 1)
    {
      texel[texel_idx] = val;
      texel_idx += 1;
    }

  }

}

void heman_draw_colored_points(heman_image *target, heman_points *pts, const heman_color *colors)
{
  assert((target->nbands == 3) || (target->nbands == 4));
  float *src = pts->data;
  unsigned int src_idx = 0;
  float inv = 1.0f / 255.0f;
  for (int k = 0; k < pts->width; k += 1)
  {
    float x = src[0 + src_idx];
    float y = src[1 + src_idx];
    src_idx += pts->nbands;
    int i = x * target->width;
    int j = y * target->height;
    if ((((i < 0) || (i >= target->width)) || (j < 0)) || (j >= target->height))
    {
      continue;
    }
    float *texel = heman_image_texel(target, i, j);
    unsigned int texel_idx = 0;
    heman_color rgb = colors[k];
    texel[texel_idx] = ((float) ((rgb >> 16) & 0xff)) * inv;
    texel_idx += 1;
    texel[texel_idx] = ((float) ((rgb >> 8) & 0xff)) * inv;
    texel_idx += 1;
    texel[texel_idx] = ((float) (rgb & 0xff)) * inv;
    texel_idx += 1;
    if (target->nbands == 4)
    {
      texel[texel_idx] = ((float) (rgb >> 24)) * inv;
    }
  }

}

void heman_draw_colored_circles(heman_image *target, heman_points *pts, int radius, const heman_color *colors)
{
  int fwidth = (radius * 2) + 1;
  int radius2 = radius * radius;
  float *src = pts->data;
  unsigned int src_idx = 0;
  float inv = 1.0f / 255.0f;
  int w = target->width;
  int h = target->height;
  for (int k = 0; k < pts->width; k += 1)
  {
    float x = src[0 + src_idx];
    float y = src[1 + src_idx];
    src_idx += pts->nbands;
    int ii = (x * w) - radius;
    int jj = (y * h) - radius;
    for (int kj = 0; kj < fwidth; kj += 1)
    {
      for (int ki = 0; ki < fwidth; ki += 1)
      {
        int i = ii + ki;
        int j = jj + kj;
        int r2 = ((i - (x * w)) * (i - (x * w))) + ((j - (y * h)) * (j - (y * h)));
        if (r2 > radius2)
        {
          continue;
        }
        float *texel = heman_image_texel(target, i, j);
        unsigned int texel_idx = 0;
        heman_color rgb = colors[k];
        texel[texel_idx] = ((float) (rgb >> 16)) * inv;
        texel_idx += 1;
        texel[texel_idx] = ((float) ((rgb >> 8) & 0xff)) * inv;
        texel_idx += 1;
        texel[texel_idx] = ((float) (rgb & 0xff)) * inv;
      }

    }

  }

}

void heman_draw_splats(heman_image *target, heman_points *pts, int radius, int blend_mode)
{
  int fwidth = (radius * 2) + 1;
  float *gaussian_splat = malloc((fwidth * fwidth) * (sizeof(float)));
  generate_gaussian_splat(gaussian_splat, fwidth);
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
    int ii = (x * w) - radius;
    int jj = (y * h) - radius;
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
        unsigned int texel_idx = 0;
        for (int c = 0; c < target->nbands; c += 1)
        {
          texel[texel_idx] += gaussian_splat[(kj * fwidth) + ki];
          texel_idx += 1;
        }

      }

    }

  }

  free(gaussian_splat);
}

void heman_internal_draw_seeds(heman_image *target, heman_points *pts, int filterd);
void heman_draw_contour_from_points(heman_image *target, heman_points *coords, heman_color rgb, float mind, float maxd, int filterd)
{
  assert((target->nbands == 3) || (target->nbands == 4));
  int width = target->width;
  int height = target->height;
  heman_image *seed = heman_image_create(width, height, 1);
  heman_image_clear(seed, 0);
  heman_internal_draw_seeds(seed, coords, filterd);
  float inv = 1.0f / 255.0f;
  float r = ((float) ((rgb >> 16) & 0xff)) * inv;
  float g = ((float) ((rgb >> 8) & 0xff)) * inv;
  float b = ((float) (rgb & 0xff)) * inv;
  float a = 1;
  if (target->nbands == 4)
  {
    a = ((float) (rgb >> 24)) * inv;
  }
  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    float *dst = target->data + ((y * width) * target->nbands);
    unsigned int dst_idx = 0;
    for (int x = 0; x < width; x += 1)
    {
      float dist = *heman_image_texel(seed, x, y);
      if ((dist > mind) && (dist < maxd))
      {
        dst[0 + dst_idx] = r;
        dst[1 + dst_idx] = g;
        dst[2 + dst_idx] = b;
        if (target->nbands == 4)
        {
          dst[3 + dst_idx] = a;
        }
      }
      dst_idx += target->nbands;
    }

  }

  heman_points_destroy(seed);
}

