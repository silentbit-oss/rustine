#include <assert.h>
#include <export.c>
#include <heman.h>
#include <image.h>
#include <stdio.h>
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

void heman_export_ply(heman_image *img, const char *filename)
{
  assert(img->nbands == 1);
  FILE *fout = fopen(filename, "wb");
  int ncols = img->width - 1;
  int nrows = img->height - 1;
  int ncells = ncols * nrows;
  int nverts = img->width * img->height;
  fprintf(fout, "ply\nformat binary_little_endian 1.0\ncomment heman\nelement vertex %d\nproperty float32 x\nproperty float32 y\nproperty float32 z\nelement face %d\nproperty list int32 int32 vertex_indices\nend_header\n", nverts, ncells);
  float invw = 2.0f / img->width;
  float invh = 2.0f / img->height;
  float vert[3];
  for (int j = 0; j < img->height; j += 1)
  {
    for (int i = 0; i < img->width; i += 1)
    {
      vert[0] = (-1) + (i * invw);
      vert[1] = (-1) + (j * invh);
      vert[2] = *heman_image_texel(img, i, j);
      fwrite(vert, sizeof(vert), 1, fout);
    }

  }

  int face[5];
  face[0] = 4;
  for (int j = 0; j < nrows; j += 1)
  {
    int p = j * img->width;
    for (int i = 0; i < ncols; i += 1, p += 1)
    {
      face[1] = p;
      face[2] = p + 1;
      face[3] = (p + img->width) + 1;
      face[4] = p + img->width;
      fwrite(face, sizeof(face), 1, fout);
    }

  }

  fclose(fout);
}

void heman_export_with_colors_ply(heman_image *hmap, heman_image *colors, const char *filename)
{
  int width = hmap->width;
  int height = hmap->height;
  assert(hmap->nbands == 1);
  assert(colors->nbands == 3);
  assert(colors->width == width);
  assert(colors->height == height);
  FILE *fout = fopen(filename, "wb");
  int ncols = hmap->width - 1;
  int nrows = hmap->height - 1;
  int ncells = ncols * nrows;
  int nverts = hmap->width * hmap->height;
  unsigned char *colordata = malloc((width * height) * 3);
  heman_export_u8(colors, 0.0, 1.0, colordata);
  fprintf(fout, "ply\nformat binary_little_endian 1.0\ncomment heman\nelement vertex %d\nproperty float32 x\nproperty float32 y\nproperty float32 z\nproperty uchar red\nproperty uchar green\nproperty uchar blue\nproperty uchar alpha\nelement face %d\nproperty list int32 int32 vertex_indices\nend_header\n", nverts, ncells);
  float invw = 2.0f / width;
  float invh = 2.0f / height;
  heman_byte *pcolor = colordata;
  unsigned int pcolor_idx = 0;
  float vert[3];
  for (int j = 0; j < height; j += 1)
  {
    for (int i = 0; i < width; i += 1)
    {
      vert[0] = (-1) + (i * invw);
      vert[1] = (-1) + (j * invh);
      vert[2] = *heman_image_texel(hmap, i, j);
      fwrite(vert, sizeof(vert), 1, fout);
      fwrite(pcolor, 3, 1, fout);
      pcolor_idx += 3;
      fputc(255, fout);
    }

  }

  int face[5];
  face[0] = 4;
  for (int j = 0; j < nrows; j += 1)
  {
    int p = j * width;
    for (int i = 0; i < ncols; i += 1, p += 1)
    {
      face[1] = p;
      face[2] = p + 1;
      face[3] = (p + hmap->width) + 1;
      face[4] = p + hmap->width;
      fwrite(face, sizeof(face), 1, fout);
    }

  }

  fclose(fout);
  free(colordata);
}

void heman_export_u8(heman_image *source, float minv, float maxv, heman_byte *outp)
{
  unsigned int outp_idx = 0;
  const float *inp = source->data;
  unsigned int inp_idx = 0;
  float scale = 1.0f / (maxv - minv);
  int size = (source->height * source->width) * source->nbands;
  for (int i = 0; i < size; i += 1)
  {
    float v = (255 * (inp[inp_idx] - minv)) * scale;
    inp_idx += 1;
    outp[outp_idx] = (0 > ((255 > v) ? (v) : (255))) ? (0) : ((255 > v) ? (v) : (255));
    outp_idx += 1;
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

void heman_export_ply(heman_image *img, const char *filename)
{
  assert(img->nbands == 1);
  FILE *fout = fopen(filename, "wb");
  int ncols = img->width - 1;
  int nrows = img->height - 1;
  int ncells = ncols * nrows;
  int nverts = img->width * img->height;
  fprintf(fout, "ply\nformat binary_little_endian 1.0\ncomment heman\nelement vertex %d\nproperty float32 x\nproperty float32 y\nproperty float32 z\nelement face %d\nproperty list int32 int32 vertex_indices\nend_header\n", nverts, ncells);
  float invw = 2.0f / img->width;
  float invh = 2.0f / img->height;
  float vert[3];
  for (int j = 0; j < img->height; j += 1)
  {
    for (int i = 0; i < img->width; i += 1)
    {
      vert[0] = (-1) + (i * invw);
      vert[1] = (-1) + (j * invh);
      vert[2] = *heman_image_texel(img, i, j);
      fwrite(vert, sizeof(vert), 1, fout);
    }

  }

  int face[5];
  face[0] = 4;
  for (int j = 0; j < nrows; j += 1)
  {
    int p = j * img->width;
    for (int i = 0; i < ncols; i += 1, p += 1)
    {
      face[1] = p;
      face[2] = p + 1;
      face[3] = (p + img->width) + 1;
      face[4] = p + img->width;
      fwrite(face, sizeof(face), 1, fout);
    }

  }

  fclose(fout);
}

void heman_export_with_colors_ply(heman_image *hmap, heman_image *colors, const char *filename)
{
  int width = hmap->width;
  int height = hmap->height;
  assert(hmap->nbands == 1);
  assert(colors->nbands == 3);
  assert(colors->width == width);
  assert(colors->height == height);
  FILE *fout = fopen(filename, "wb");
  int ncols = hmap->width - 1;
  int nrows = hmap->height - 1;
  int ncells = ncols * nrows;
  int nverts = hmap->width * hmap->height;
  unsigned char *colordata = malloc((width * height) * 3);
  heman_export_u8(colors, 0.0, 1.0, colordata);
  fprintf(fout, "ply\nformat binary_little_endian 1.0\ncomment heman\nelement vertex %d\nproperty float32 x\nproperty float32 y\nproperty float32 z\nproperty uchar red\nproperty uchar green\nproperty uchar blue\nproperty uchar alpha\nelement face %d\nproperty list int32 int32 vertex_indices\nend_header\n", nverts, ncells);
  float invw = 2.0f / width;
  float invh = 2.0f / height;
  heman_byte *pcolor = colordata;
  unsigned int pcolor_idx = 0;
  float vert[3];
  for (int j = 0; j < height; j += 1)
  {
    for (int i = 0; i < width; i += 1)
    {
      vert[0] = (-1) + (i * invw);
      vert[1] = (-1) + (j * invh);
      vert[2] = *heman_image_texel(hmap, i, j);
      fwrite(vert, sizeof(vert), 1, fout);
      fwrite(pcolor, 3, 1, fout);
      pcolor_idx += 3;
      fputc(255, fout);
    }

  }

  int face[5];
  face[0] = 4;
  for (int j = 0; j < nrows; j += 1)
  {
    int p = j * width;
    for (int i = 0; i < ncols; i += 1, p += 1)
    {
      face[1] = p;
      face[2] = p + 1;
      face[3] = (p + hmap->width) + 1;
      face[4] = p + hmap->width;
      fwrite(face, sizeof(face), 1, fout);
    }

  }

  fclose(fout);
  free(colordata);
}

void heman_export_u8(heman_image *source, float minv, float maxv, heman_byte *outp)
{
  unsigned int outp_idx = 0;
  const float *inp = source->data;
  unsigned int inp_idx = 0;
  float scale = 1.0f / (maxv - minv);
  int size = (source->height * source->width) * source->nbands;
  for (int i = 0; i < size; i += 1)
  {
    float v = (255 * (inp[inp_idx] - minv)) * scale;
    inp_idx += 1;
    outp[outp_idx] = (0 > ((255 > v) ? (v) : (255))) ? (0) : ((255 > v) ? (v) : (255));
    outp_idx += 1;
  }

}

