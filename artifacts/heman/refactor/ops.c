#include <assert.h>
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
int heman_get_num_threads()
{
  return omp_get_max_threads();
}

heman_image *heman_ops_step(heman_image *hmap, float threshold)
{
  assert(hmap->nbands == 1);
  heman_image *result = heman_image_create(hmap->width, hmap->height, 1);
  int size = hmap->height * hmap->width;
  float *src = hmap->data;
  float *dst = result->data;
  unsigned int dst_idx = 0;
  for (int i = 0; i < size; i += 1)
  {
    dst[dst_idx] = ((*(src++)) >= threshold) ? (1) : (0);
    dst_idx += 1;
  }

  return result;
}

heman_image *heman_ops_max(heman_image *imga, heman_image *imgb)
{
  assert(imga->width == imgb->width);
  assert(imga->height == imgb->height);
  assert(imga->nbands == imgb->nbands);
  heman_image *result = heman_image_create(imga->width, imga->height, imga->nbands);
  int size = (imga->height * imga->width) * imga->nbands;
  float *srca = imga->data;
  unsigned int srca_idx = 0;
  float *srcb = imgb->data;
  unsigned int srcb_idx = 0;
  float *dst = result->data;
  unsigned int dst_idx = 0;
  for (int i = 0; i < size; i += 1, dst_idx += 1, srca_idx += 1, srcb_idx += 1)
  {
    dst[dst_idx] = (srca[srca_idx] > srcb[srcb_idx]) ? (srca[srca_idx]) : (srcb[srcb_idx]);
  }

  return result;
}

heman_image *heman_ops_sweep(heman_image *hmap)
{
  assert(hmap->nbands == 1);
  heman_image *result = heman_image_create(hmap->height, 1, 1);
  float *dst = result->data;
  unsigned int dst_idx = 0;
  const float *src = hmap->data;
  unsigned int src_idx = 0;
  float invw = 1.0f / hmap->width;
  for (int y = 0; y < hmap->height; y += 1)
  {
    float acc = 0;
    for (int x = 0; x < hmap->width; x += 1)
    {
      acc += src[src_idx];
      src_idx += 1;
    }

    dst[dst_idx] = acc * invw;
    dst_idx += 1;
  }

  return result;
}

static void copy_row(heman_image *src, heman_image *dst, int dstx, int y)
{
  int width = src->width;
  if (src->nbands == 1)
  {
    for (int x = 0; x < width; x += 1)
    {
      float *srcp = heman_image_texel(src, x, y);
      unsigned int srcp_idx = 0;
      float *dstp = heman_image_texel(dst, dstx + x, y);
      unsigned int dstp_idx = 0;
      dstp[dstp_idx] = srcp[srcp_idx];
    }

    return;
  }
  for (int x = 0; x < width; x += 1)
  {
    float *srcp = heman_image_texel(src, x, y);
    unsigned int srcp_idx = 0;
    float *dstp = heman_image_texel(dst, dstx + x, y);
    unsigned int dstp_idx = 0;
    int nbands = src->nbands;
    while (nbands--)
    {
      dstp[dstp_idx] = srcp[srcp_idx];
      srcp_idx += 1;
      dstp_idx += 1;
    }

  }

}

heman_image *heman_ops_stitch_horizontal(heman_image **images, int count)
{
  assert(count > 0);
  int width = images[0]->width;
  int height = images[0]->height;
  int nbands = images[0]->nbands;
  for (int i = 1; i < count; i += 1)
  {
    assert(images[i]->width == width);
    assert(images[i]->height == height);
    assert(images[i]->nbands == nbands);
  }

  heman_image *result = heman_image_create(width * count, height, nbands);
  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    for (int tile = 0; tile < count; tile += 1)
    {
      copy_row(images[tile], result, tile * width, y);
    }

  }

  return result;
}

heman_image *heman_ops_stitch_vertical(heman_image **images, int count)
{
  assert(count > 0);
  int width = images[0]->width;
  int height = images[0]->height;
  int nbands = images[0]->nbands;
  for (int i = 1; i < count; i += 1)
  {
    assert(images[i]->width == width);
    assert(images[i]->height == height);
    assert(images[i]->nbands == nbands);
  }

  heman_image *result = heman_image_create(width, height * count, nbands);
  int size = (width * height) * nbands;
  float *dst = result->data;
  unsigned int dst_idx = 0;
  for (int tile = 0; tile < count; tile += 1)
  {
    memcpy(dst, images[tile]->data, size * (sizeof(float)));
    dst_idx += size;
  }

  return result;
}

heman_image *heman_ops_normalize_f32(heman_image *source, float minv, float maxv)
{
  heman_image *result = heman_image_create(source->width, source->height, source->nbands);
  float *src = source->data;
  unsigned int src_idx = 0;
  float *dst = result->data;
  unsigned int dst_idx = 0;
  float scale = 1.0f / (maxv - minv);
  int size = (source->height * source->width) * source->nbands;
  for (int i = 0; i < size; i += 1)
  {
    float v = (src[src_idx] - minv) * scale;
    src_idx += 1;
    dst[dst_idx] = (0 > ((1 > v) ? (v) : (1))) ? (0) : ((1 > v) ? (v) : (1));
    dst_idx += 1;
  }

  return result;
}

heman_image *heman_ops_laplacian(heman_image *heightmap)
{
  assert(heightmap->nbands == 1);
  int width = heightmap->width;
  int height = heightmap->height;
  heman_image *result = heman_image_create(width, height, 1);
  int maxx = width - 1;
  int maxy = height - 1;
  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    int y1 = ((y + 1) > maxy) ? (maxy) : (y + 1);
    float *dst = result->data + (y * width);
    unsigned int dst_idx = 0;
    for (int x = 0; x < width; x += 1)
    {
      int x1 = ((x + 1) > maxx) ? (maxx) : (x + 1);
      float p = *heman_image_texel(heightmap, x, y);
      float px = *heman_image_texel(heightmap, x1, y);
      float py = *heman_image_texel(heightmap, x, y1);
      dst[dst_idx] = ((p - px) * (p - px)) + ((p - py) * (p - py));
      dst_idx += 1;
    }

  }

  return result;
}

void heman_ops_accumulate(heman_image *dst, heman_image *src)
{
  assert(dst->nbands == src->nbands);
  assert(dst->width == src->width);
  assert(dst->height == src->height);
  int size = dst->height * dst->width;
  float *sdata = src->data;
  unsigned int sdata_idx = 0;
  float *ddata = dst->data;
  unsigned int ddata_idx = 0;
  for (int i = 0; i < size; i += 1)
  {
    ddata[ddata_idx] += sdata[sdata_idx];
    sdata_idx += 1;
    ddata_idx += 1;
  }

}

heman_image *heman_ops_sobel(heman_image *img, heman_color rgb)
{
  int width = img->width;
  int height = img->height;
  assert(img->nbands == 3);
  heman_image *result = heman_image_create(width, height, 3);
  heman_image *gray = heman_color_to_grayscale(img);
  float inv = 1.0f / 255.0f;
  kmVec3 edge_rgb;
  edge_rgb.x = ((float) (rgb >> 16)) * inv;
  edge_rgb.y = ((float) ((rgb >> 8) & 0xff)) * inv;
  edge_rgb.z = ((float) (rgb & 0xff)) * inv;
  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    helper_heman_ops_sobel_1(img, width, height, result, gray, edge_rgb, y);
  }

  heman_image_destroy(gray);
  return result;
}

heman_image *heman_ops_warp_core(heman_image *img, heman_image *secondary, int seed, int octaves)
{
  struct osn_context *ctx;
  open_simplex_noise(seed, &ctx);
  int width = img->width;
  int height = img->height;
  int nbands = img->nbands;
  heman_image *result = heman_image_create(width, height, nbands);
  heman_image *result2 = (secondary) ? (heman_image_create(width, height, secondary->nbands)) : (0);
  float invw = 1.0 / width;
  float invh = 1.0 / height;
  float inv = (invw > invh) ? (invh) : (invw);
  float aspect = ((float) width) / height;
  float gain = 0.6;
  float lacunarity = 2.0;
  float initial_amplitude = 0.05;
  float initial_frequency = 8.0;
  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    helper_heman_ops_warp_core_1(img, secondary, octaves, ctx, width, height, nbands, result, result2, invw, invh, inv, aspect, gain, lacunarity, initial_amplitude, initial_frequency, y);
  }

  open_simplex_noise_free(ctx);
  if (secondary)
  {
    free(secondary->data);
    secondary->data = result2->data;
    free(result2);
  }
  return result;
}

heman_image *heman_ops_warp_points(heman_image *img, int seed, int octaves, heman_points *pts)
{
  int width = img->width;
  int height = img->height;
  heman_image *mapping = heman_distance_identity_cpcf(width, height);
  heman_image *retval = heman_ops_warp_core(img, mapping, seed, octaves);
  float *src = pts->data;
  unsigned int src_idx = 0;
  for (int k = 0; k < pts->width; k += 1, src_idx += pts->nbands)
  {
    float x = src[0 + src_idx];
    float y = src[1 + src_idx];
    int i = x * mapping->width;
    int j = y * mapping->height;
    if ((((i < 0) || (i >= mapping->width)) || (j < 0)) || (j >= mapping->height))
    {
      continue;
    }
    float *texel = heman_image_texel(mapping, i, j);
    src[0 + src_idx] = texel[0] / mapping->width;
    src[1 + src_idx] = texel[1] / mapping->height;
  }

  heman_image_destroy(mapping);
  return retval;
}

heman_image *heman_ops_warp(heman_image *img, int seed, int octaves)
{
  return heman_ops_warp_core(img, 0, seed, octaves);
}

heman_image *heman_ops_extract_mask(heman_image *source, heman_color color, int invert)
{
  assert(source->nbands == 3);
  float inv = 1.0f / 255.0f;
  float r = ((float) (color >> 16)) * inv;
  float g = ((float) ((color >> 8) & 0xff)) * inv;
  float b = ((float) (color & 0xff)) * inv;
  int height = source->height;
  int width = source->width;
  heman_image *result = heman_image_create(width, height, 1);
  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    float *dst = result->data + (y * width);
    unsigned int dst_idx = 0;
    float *src = source->data + ((y * width) * 3);
    unsigned int src_idx = 0;
    for (int x = 0; x < width; x += 1, src_idx += 3)
    {
      float val = ((src[0 + src_idx] == r) && (src[1 + src_idx] == g)) && (src[2 + src_idx] == b);
      if (!invert)
      {
        val = 1 - val;
      }
      dst[dst_idx] = val;
      dst_idx += 1;
    }

  }

  return result;
}

heman_image *heman_ops_replace_color(heman_image *source, heman_color color, heman_image *texture)
{
  assert(source->nbands == 3);
  assert(texture->nbands == 3);
  int height = source->height;
  int width = source->width;
  assert(texture->width == width);
  assert(texture->height == height);
  float inv = 1.0f / 255.0f;
  float r = ((float) (color >> 16)) * inv;
  float g = ((float) ((color >> 8) & 0xff)) * inv;
  float b = ((float) (color & 0xff)) * inv;
  heman_image *result = heman_image_create(width, height, 3);
  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    float *dst = result->data + ((y * width) * 3);
    unsigned int dst_idx = 0;
    float *src = source->data + ((y * width) * 3);
    unsigned int src_idx = 0;
    float *tex = texture->data + ((y * width) * 3);
    unsigned int tex_idx = 0;
    for (int x = 0; x < width; x += 1, src_idx += 3, dst_idx += 3, tex_idx += 3)
    {
      if (((src[0 + src_idx] == r) && (src[1 + src_idx] == g)) && (src[2 + src_idx] == b))
      {
        dst[0 + dst_idx] = tex[0 + tex_idx];
        dst[1 + dst_idx] = tex[1 + tex_idx];
        dst[2 + dst_idx] = tex[2 + tex_idx];
      }
      else
      {
        dst[0 + dst_idx] = src[0 + src_idx];
        dst[1 + dst_idx] = src[1 + src_idx];
        dst[2 + dst_idx] = src[2 + src_idx];
      }
    }

  }

  return result;
}

static int _match(heman_image *mask, heman_color mask_color, int invert_mask, int pixel_index)
{
  float *mcolor = mask->data + (pixel_index * 3);
  unsigned char r1 = mcolor[0] * 255;
  unsigned char g1 = mcolor[1] * 255;
  unsigned char b1 = mcolor[2] * 255;
  unsigned char r2 = mask_color >> 16;
  unsigned char g2 = (mask_color >> 8) & 0xff;
  unsigned char b2 = mask_color & 0xff;
  int retval = ((r1 == r2) && (g1 == g2)) && (b1 == b2);
  return (invert_mask) ? (1 - retval) : (retval);
}

static float qselect(float *v, int len, int k)
{
  int i;
  int st;
  for (st = (i = 0); i < (len - 1); i += 1)
  {
    if (v[i] > v[len - 1])
    {
      continue;
    }
    {
      float _ = v[i];
      v[i] = v[st];
      v[st] = _;
    }
    ;
    st += 1;
  }

  {
    float _ = v[len - 1];
    v[len - 1] = v[st];
    v[st] = _;
  }
  ;
  return (k == st) ? (v[st]) : ((st > k) ? (qselect(v, st, k)) : (qselect(v + st, len - st, k - st)));
}

heman_image *heman_ops_percentiles(heman_image *hmap, int nsteps, heman_image *mask, heman_color mask_color, int invert_mask, float offset)
{
  assert(hmap->nbands == 1);
  assert((!mask) || (mask->nbands == 3));
  int size = hmap->height * hmap->width;
  float *src = hmap->data;
  unsigned int src_idx = 0;
  float minv = 1000;
  float maxv = -1000;
  int npixels = 0;
  for (int i = 0; i < size; i += 1)
  {
    if ((!mask) || _match(mask, mask_color, invert_mask, i))
    {
      minv = (minv > src[i + src_idx]) ? (src[i + src_idx]) : (minv);
      maxv = (maxv > src[i + src_idx]) ? (maxv) : (src[i + src_idx]);
      npixels += 1;
    }
  }

  float *vals = malloc((sizeof(float)) * npixels);
  npixels = 0;
  for (int i = 0; i < size; i += 1)
  {
    if ((!mask) || _match(mask, mask_color, invert_mask, i))
    {
      vals[npixels] = src[i + src_idx];
      npixels += 1;
    }
  }

  float *percentiles = malloc((sizeof(float)) * nsteps);
  for (int tier = 0; tier < nsteps; tier += 1)
  {
    float height = qselect(vals, npixels, (tier * npixels) / nsteps);
    percentiles[tier] = height;
  }

  free(vals);
  for (int i = 0; i < size; i += 1)
  {
    float e = src[src_idx];
    if ((!mask) || _match(mask, mask_color, invert_mask, i))
    {
      for (int tier = nsteps - 1; tier >= 0; tier -= 1)
      {
        if (e > percentiles[tier])
        {
          e = percentiles[tier];
          break;
        }
      }

    }
    src[src_idx] = e + offset;
    src_idx += 1;
  }

  free(percentiles);
  return hmap;
}

heman_image *heman_ops_stairstep(heman_image *hmap, int nsteps, heman_image *mask, heman_color mask_color, int invert_mask, float offset)
{
  assert(hmap->nbands == 1);
  assert((!mask) || (mask->nbands == 3));
  int size = hmap->height * hmap->width;
  float *src = hmap->data;
  unsigned int src_idx = 0;
  float minv = 1000;
  float maxv = -1000;
  for (int i = 0; i < size; i += 1)
  {
    if ((!mask) || _match(mask, mask_color, invert_mask, i))
    {
      minv = (minv > src[i + src_idx]) ? (src[i + src_idx]) : (minv);
      maxv = (maxv > src[i + src_idx]) ? (maxv) : (src[i + src_idx]);
    }
  }

  float range = maxv - minv;
  for (int i = 0; i < size; i += 1)
  {
    float e = src[src_idx];
    if ((!mask) || _match(mask, mask_color, invert_mask, i))
    {
      e = e - minv;
      e /= range;
      e = floor(e * nsteps) / nsteps;
      e = (e * range) + minv;
    }
    src[src_idx] = e + offset;
    src_idx += 1;
  }

  return hmap;
}

heman_image *heman_ops_merge_political(heman_image *hmap, heman_image *cmap, heman_color ocean)
{
  assert(hmap->nbands == 1);
  assert(cmap->nbands == 3);
  heman_image *result = heman_image_create(hmap->width, hmap->height, 4);
  float *pheight = hmap->data;
  unsigned int pheight_idx = 0;
  float *pcolour = cmap->data;
  unsigned int pcolour_idx = 0;
  float *pmerged = result->data;
  unsigned int pmerged_idx = 0;
  float inv = 1.0f / 255.0f;
  float oceanr = ((float) (ocean >> 16)) * inv;
  float oceang = ((float) ((ocean >> 8) & 0xff)) * inv;
  float oceanb = ((float) (ocean & 0xff)) * inv;
  int size = hmap->height * hmap->width;
  float minh = 1000;
  float maxh = -1000;
  for (int i = 0; i < size; i += 1)
  {
    minh = (minh > pheight[i + pheight_idx]) ? (pheight[i + pheight_idx]) : (minh);
    maxh = (maxh > pheight[i + pheight_idx]) ? (pheight[i + pheight_idx]) : (maxh);
  }

  for (int i = 0; i < size; i += 1)
  {
    helper_heman_ops_merge_political_1(&pheight_idx, &pcolour_idx, &pmerged_idx, pheight, pcolour, pmerged, oceanr, oceang, oceanb, minh, maxh);
  }

  return result;
}

heman_image *heman_ops_emboss(heman_image *img, int mode)
{
  int seed = 1;
  int octaves = 4;
  struct osn_context *ctx;
  open_simplex_noise(seed, &ctx);
  int width = img->width;
  int height = img->height;
  assert(img->nbands == 1);
  heman_image *result = heman_image_create(width, height, 1);
  float invw = 1.0 / width;
  float invh = 1.0 / height;
  float inv = (invw > invh) ? (invh) : (invw);
  float gain = 0.6;
  float lacunarity = 2.0;
  float land_amplitude = 0.0005;
  float land_frequency = 256.0;
  float ocean_amplitude = 0.5;
  float ocean_frequency = 1.0;
  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    helper_heman_ops_emboss_1(img, mode, octaves, ctx, width, result, inv, gain, lacunarity, land_amplitude, land_frequency, ocean_amplitude, ocean_frequency, y);
  }

  open_simplex_noise_free(ctx);
  return result;
}

void helper_heman_ops_sobel_1(heman_image * const img, int width, int height, heman_image * const result, heman_image * const gray, kmVec3 edge_rgb, int y)
{
  kmVec3 *dst = ((kmVec3 *) result->data) + (y * width);
  unsigned int dst_idx = 0;
  const kmVec3 *src = ((kmVec3 *) img->data) + (y * width);
  unsigned int src_idx = 0;
  for (int x = 0; x < width; x += 1)
  {
    int xm1 = ((x - 1) > 0) ? (x - 1) : (0);
    int xp1 = ((x + 1) > (width - 1)) ? (width - 1) : (x + 1);
    int ym1 = ((y - 1) > 0) ? (y - 1) : (0);
    int yp1 = ((y + 1) > (height - 1)) ? (height - 1) : (y + 1);
    float t00 = *heman_image_texel(gray, xm1, ym1);
    float t10 = *heman_image_texel(gray, x, ym1);
    float t20 = *heman_image_texel(gray, xp1, ym1);
    float t01 = *heman_image_texel(gray, xm1, 0);
    float t21 = *heman_image_texel(gray, xp1, 0);
    float t02 = *heman_image_texel(gray, xm1, yp1);
    float t12 = *heman_image_texel(gray, x, yp1);
    float t22 = *heman_image_texel(gray, xp1, yp1);
    float gx = ((((t00 + (2.0 * t01)) + t02) - t20) - (2.0 * t21)) - t22;
    float gy = ((((t00 + (2.0 * t10)) + t20) - t02) - (2.0 * t12)) - t22;
    float is_edge = ((gx * gx) + (gy * gy)) > 1e-5;
    kmVec3Lerp(dst, src, &edge_rgb, is_edge);
    src_idx += 1;
    dst_idx += 1;
  }

}

void helper_heman_ops_warp_core_1(heman_image * const img, heman_image * const secondary, int octaves, struct osn_context * const ctx, int width, int height, int nbands, heman_image * const result, heman_image * const result2, float invw, float invh, float inv, float aspect, float gain, float lacunarity, float initial_amplitude, float initial_frequency, int y)
{
  float *dst = result->data + ((y * width) * nbands);
  unsigned int dst_idx = 0;
  for (int x = 0; x < width; x += 1)
  {
    helper_helper_heman_ops_warp_core_1_1(&dst_idx, img, secondary, octaves, ctx, width, height, nbands, result2, invw, invh, inv, aspect, gain, lacunarity, initial_amplitude, initial_frequency, y, dst, x);
  }

}

void helper_heman_ops_merge_political_1(unsigned int * const pheight_idx_ref, unsigned int * const pcolour_idx_ref, unsigned int * const pmerged_idx_ref, float * const pheight, float * const pcolour, float * const pmerged, float oceanr, float oceang, float oceanb, float minh, float maxh)
{
  unsigned int pheight_idx = *pheight_idx_ref;
  unsigned int pcolour_idx = *pcolour_idx_ref;
  unsigned int pmerged_idx = *pmerged_idx_ref;
  float h = pheight[pheight_idx];
  pheight_idx += 1;
  if (h < 0)
  {
    pmerged[pmerged_idx] = oceanr;
    pmerged_idx += 1;
    pmerged[pmerged_idx] = oceang;
    pmerged_idx += 1;
    pmerged[pmerged_idx] = oceanb;
    pmerged_idx += 1;
    pcolour_idx += 3;
  }
  else
  {
    pmerged[pmerged_idx] = pcolour[pcolour_idx];
    pcolour_idx += 1;
    pmerged_idx += 1;
    pmerged[pmerged_idx] = pcolour[pcolour_idx];
    pcolour_idx += 1;
    pmerged_idx += 1;
    pmerged[pmerged_idx] = pcolour[pcolour_idx];
    pcolour_idx += 1;
    pmerged_idx += 1;
  }
  pmerged[pmerged_idx] = (h - minh) / (maxh - minh);
  pmerged_idx += 1;
  *pheight_idx_ref = pheight_idx;
  *pcolour_idx_ref = pcolour_idx;
  *pmerged_idx_ref = pmerged_idx;
}

void helper_heman_ops_emboss_1(heman_image * const img, int mode, int octaves, struct osn_context * const ctx, int width, heman_image * const result, float inv, float gain, float lacunarity, float land_amplitude, float land_frequency, float ocean_amplitude, float ocean_frequency, int y)
{
  float *dst = result->data + (y * width);
  unsigned int dst_idx = 0;
  for (int x = 0; x < width; x += 1)
  {
    float z = *heman_image_texel(img, x, y);
    if ((z > 0) && (mode == 1))
    {
      float s = x * inv;
      float t = y * inv;
      float a = land_amplitude;
      float f = land_frequency;
      for (int i = 0; i < octaves; i += 1)
      {
        z += a * open_simplex_noise2(ctx, s * f, t * f);
        a *= gain;
        f *= lacunarity;
      }

    }
    else
      if ((z <= 0) && (mode == (-1)))
    {
      z = (z > (-0.1)) ? (z) : (-0.1);
      float soften = fabsf(z);
      float s = x * inv;
      float t = y * inv;
      float a = ocean_amplitude;
      float f = ocean_frequency;
      for (int i = 0; i < octaves; i += 1)
      {
        z += soften * (a * open_simplex_noise2(ctx, s * f, t * f));
        a *= gain;
        f *= lacunarity;
      }

    }
    dst[dst_idx] = z;
    dst_idx += 1;
  }

}

void helper_helper_heman_ops_warp_core_1_1(unsigned int * const dst_idx_ref, heman_image * const img, heman_image * const secondary, int octaves, struct osn_context * const ctx, int width, int height, int nbands, heman_image * const result2, float invw, float invh, float inv, float aspect, float gain, float lacunarity, float initial_amplitude, float initial_frequency, int y, float * const dst, int x)
{
  unsigned int dst_idx = *dst_idx_ref;
  float a = initial_amplitude;
  float f = initial_frequency;
  float *src;
  unsigned int src_idx = 0;
  if (nbands == 4)
  {
    src_idx = heman_image_texel(img, x, y);
    float elev = 1 - src[3 + src_idx];
    a *= pow(elev, 4);
  }
  float s = x * inv;
  float t = y * inv;
  float u = x * invw;
  float v = y * invh;
  for (int i = 0; i < octaves; i += 1)
  {
    u += a * open_simplex_noise2(ctx, s * f, t * f);
    v += aspect * (a * open_simplex_noise2(ctx, (s * f) + 0.5, t * f));
    a *= gain;
    f *= lacunarity;
  }

  int i = (0 > (((width - 1) > (u * width)) ? (u * width) : (width - 1))) ? (0) : (((width - 1) > (u * width)) ? (u * width) : (width - 1));
  int j = (0 > (((height - 1) > (v * height)) ? (v * height) : (height - 1))) ? (0) : (((height - 1) > (v * height)) ? (v * height) : (height - 1));
  src_idx = heman_image_texel(img, i, j);
  for (int n = 0; n < nbands; n += 1)
  {
    dst[dst_idx] = src[src_idx];
    src_idx += 1;
    dst_idx += 1;
  }

  if (secondary)
  {
    src_idx = heman_image_texel(secondary, x, y);
    float *dst2 = heman_image_texel(result2, i, j);
    unsigned int dst2_idx = 0;
    for (int n = 0; n < secondary->nbands; n += 1)
    {
      dst2[dst2_idx] = src[src_idx];
      src_idx += 1;
      dst2_idx += 1;
    }

  }
  *dst_idx_ref = dst_idx;
}

