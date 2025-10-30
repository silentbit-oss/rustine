static void sphere(float u, float v, float r, kmVec3 *dst)
{
  dst->x = (r * sin(v)) * cos(u);
  dst->y = r * cos(v);
  dst->z = (r * (-sin(v))) * sin(u);
}


/*** DEPENDENCIES:
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
***/


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


/*** DEPENDENCIES:
void heman_image_sample(heman_image *img, float u, float v, float *result)
{
  unsigned int result_idx = 0;
  int x = (0 > (((img->width - 1) > (img->width * u)) ? (img->width * u) : (img->width - 1))) ? (0) : (((img->width - 1) > (img->width * u)) ? (img->width * u) : (img->width - 1));
  int y = (0 > (((img->height - 1) > (img->height * v)) ? (img->height * v) : (img->height - 1))) ? (0) : (((img->height - 1) > (img->height * v)) ? (img->height * v) : (img->height - 1));
  float *data = heman_image_texel(img, x, y);
  unsigned int data_idx = 0;
  for (int b = 0; b < img->nbands; b += 1)
  {
    result[result_idx] = data[data_idx];
    data_idx += 1;
    result_idx += 1;
  }

}


----------------------------
typedef struct heman_image_s heman_image
----------------------------
***/


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


/*** DEPENDENCIES:
void heman_image_sample(heman_image *img, float u, float v, float *result)
{
  unsigned int result_idx = 0;
  int x = (0 > (((img->width - 1) > (img->width * u)) ? (img->width * u) : (img->width - 1))) ? (0) : (((img->width - 1) > (img->width * u)) ? (img->width * u) : (img->width - 1));
  int y = (0 > (((img->height - 1) > (img->height * v)) ? (img->height * v) : (img->height - 1))) ? (0) : (((img->height - 1) > (img->height * v)) ? (img->height * v) : (img->height - 1));
  float *data = heman_image_texel(img, x, y);
  unsigned int data_idx = 0;
  for (int b = 0; b < img->nbands; b += 1)
  {
    result[result_idx] = data[data_idx];
    data_idx += 1;
    result_idx += 1;
  }

}


----------------------------
typedef struct heman_image_s heman_image
----------------------------
***/


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


/*** DEPENDENCIES:
void heman_image_sample(heman_image *img, float u, float v, float *result)
{
  unsigned int result_idx = 0;
  int x = (0 > (((img->width - 1) > (img->width * u)) ? (img->width * u) : (img->width - 1))) ? (0) : (((img->width - 1) > (img->width * u)) ? (img->width * u) : (img->width - 1));
  int y = (0 > (((img->height - 1) > (img->height * v)) ? (img->height * v) : (img->height - 1))) ? (0) : (((img->height - 1) > (img->height * v)) ? (img->height * v) : (img->height - 1));
  float *data = heman_image_texel(img, x, y);
  unsigned int data_idx = 0;
  for (int b = 0; b < img->nbands; b += 1)
  {
    result[result_idx] = data[data_idx];
    data_idx += 1;
    result_idx += 1;
  }

}


----------------------------
typedef struct heman_image_s heman_image
----------------------------
***/


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


/*** DEPENDENCIES:
static const float SEALEVEL = 0.5
----------------------------
void heman_image_sample(heman_image *img, float u, float v, float *result)
{
  unsigned int result_idx = 0;
  int x = (0 > (((img->width - 1) > (img->width * u)) ? (img->width * u) : (img->width - 1))) ? (0) : (((img->width - 1) > (img->width * u)) ? (img->width * u) : (img->width - 1));
  int y = (0 > (((img->height - 1) > (img->height * v)) ? (img->height * v) : (img->height - 1))) ? (0) : (((img->height - 1) > (img->height * v)) ? (img->height * v) : (img->height - 1));
  float *data = heman_image_texel(img, x, y);
  unsigned int data_idx = 0;
  for (int b = 0; b < img->nbands; b += 1)
  {
    result[result_idx] = data[data_idx];
    data_idx += 1;
    result_idx += 1;
  }

}


----------------------------
typedef struct heman_image_s heman_image
----------------------------
***/


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


/*** DEPENDENCIES:
static const float SEALEVEL = 0.5
----------------------------
void heman_image_sample(heman_image *img, float u, float v, float *result)
{
  unsigned int result_idx = 0;
  int x = (0 > (((img->width - 1) > (img->width * u)) ? (img->width * u) : (img->width - 1))) ? (0) : (((img->width - 1) > (img->width * u)) ? (img->width * u) : (img->width - 1));
  int y = (0 > (((img->height - 1) > (img->height * v)) ? (img->height * v) : (img->height - 1))) ? (0) : (((img->height - 1) > (img->height * v)) ? (img->height * v) : (img->height - 1));
  float *data = heman_image_texel(img, x, y);
  unsigned int data_idx = 0;
  for (int b = 0; b < img->nbands; b += 1)
  {
    result[result_idx] = data[data_idx];
    data_idx += 1;
    result_idx += 1;
  }

}


----------------------------
typedef struct heman_image_s heman_image
----------------------------
***/


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


/*** DEPENDENCIES:
double open_simplex_noise2(struct osn_context *ctx, double x, double y)
{
  double stretchOffset = (x + y) * (-0.211324865405187);
  double xs = x + stretchOffset;
  double ys = y + stretchOffset;
  int xsb = fastFloor(xs);
  int ysb = fastFloor(ys);
  double squishOffset = (xsb + ysb) * 0.366025403784439;
  double xb = xsb + squishOffset;
  double yb = ysb + squishOffset;
  double xins = xs - xsb;
  double yins = ys - ysb;
  double inSum = xins + yins;
  double dx0 = x - xb;
  double dy0 = y - yb;
  double dx_ext;
  double dy_ext;
  int xsv_ext;
  int ysv_ext;
  double value = 0;
  double dx1 = (dx0 - 1) - 0.366025403784439;
  double dy1 = (dy0 - 0) - 0.366025403784439;
  double attn1 = (2 - (dx1 * dx1)) - (dy1 * dy1);
  if (attn1 > 0)
  {
    attn1 *= attn1;
    value += (attn1 * attn1) * extrapolate2(ctx, xsb + 1, ysb + 0, dx1, dy1);
  }
  double dx2 = (dx0 - 0) - 0.366025403784439;
  double dy2 = (dy0 - 1) - 0.366025403784439;
  double attn2 = (2 - (dx2 * dx2)) - (dy2 * dy2);
  if (attn2 > 0)
  {
    attn2 *= attn2;
    value += (attn2 * attn2) * extrapolate2(ctx, xsb + 0, ysb + 1, dx2, dy2);
  }
  if (inSum <= 1)
  {
    helper_open_simplex_noise2_1(&dx_ext, &dy_ext, &xsv_ext, &ysv_ext, xsb, ysb, xins, yins, inSum, dx0, dy0);
  }
  else
  {
    helper_open_simplex_noise2_2(&xsb, &ysb, &dx0, &dy0, &dx_ext, &dy_ext, &xsv_ext, &ysv_ext, xins, yins, inSum);
  }
  double attn0 = (2 - (dx0 * dx0)) - (dy0 * dy0);
  if (attn0 > 0)
  {
    attn0 *= attn0;
    value += (attn0 * attn0) * extrapolate2(ctx, xsb, ysb, dx0, dy0);
  }
  double attn_ext = (2 - (dx_ext * dx_ext)) - (dy_ext * dy_ext);
  if (attn_ext > 0)
  {
    attn_ext *= attn_ext;
    value += (attn_ext * attn_ext) * extrapolate2(ctx, xsv_ext, ysv_ext, dx_ext, dy_ext);
  }
  return value / 47.0;
}


----------------------------
void open_simplex_noise_free(struct osn_context *ctx)
{
  if (!ctx)
  {
    return;
  }
  if (ctx->perm)
  {
    free(ctx->perm);
    ctx->perm = 0;
  }
  if (ctx->permGradIndex3D)
  {
    free(ctx->permGradIndex3D);
    ctx->permGradIndex3D = 0;
  }
  free(ctx);
}


----------------------------
typedef struct heman_image_s heman_image
----------------------------
heman_image *heman_image_create(int width, int height, int nbands)
{
  heman_image *img = malloc(sizeof(heman_image));
  img->width = width;
  img->height = height;
  img->nbands = nbands;
  img->data = malloc((((sizeof(float)) * width) * height) * nbands);
  return img;
}


----------------------------
int open_simplex_noise(int64_t seed, struct osn_context **ctx)
{
  int rc;
  int16_t source[256];
  int i;
  int16_t *perm;
  unsigned int perm_idx = 0;
  int16_t *permGradIndex3D;
  unsigned int permGradIndex3D_idx = 0;
  *ctx = malloc(sizeof(*(*ctx)));
  if (!(*ctx))
  {
    return -ENOMEM;
  }
  (*ctx)->perm = 0;
  (*ctx)->permGradIndex3D = 0;
  rc = allocate_perm(*ctx, 256, 256);
  if (rc)
  {
    free(*ctx);
    return rc;
  }
  perm_idx = (*ctx)->perm_idx;
  permGradIndex3D_idx = (*ctx)->permGradIndex3D_idx;
  for (i = 0; i < 256; i += 1)
    source[i] = (int16_t) i;

  seed = (seed * 6364136223846793005LL) + 1442695040888963407LL;
  seed = (seed * 6364136223846793005LL) + 1442695040888963407LL;
  seed = (seed * 6364136223846793005LL) + 1442695040888963407LL;
  for (i = 255; i >= 0; i -= 1)
  {
    seed = (seed * 6364136223846793005LL) + 1442695040888963407LL;
    int r = (int) ((seed + 31) % (i + 1));
    if (r < 0)
    {
      r += i + 1;
    }
    perm[i + perm_idx] = source[r];
    permGradIndex3D[i + permGradIndex3D_idx] = (short) ((perm[i + perm_idx] % (((sizeof(gradients3D)) / (sizeof(gradients3D[0]))) / 3)) * 3);
    source[r] = source[i];
  }

  return 0;
}


----------------------------
struct osn_context
{
  int16_t *perm;
  int16_t *permGradIndex3D;
}
----------------------------
***/


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


/*** DEPENDENCIES:
void heman_image_destroy(heman_image *img)
{
  free(img->data);
  free(img);
}


----------------------------
typedef struct heman_image_s heman_image
----------------------------
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


----------------------------
heman_image *heman_image_create(int width, int height, int nbands)
{
  heman_image *img = malloc(sizeof(heman_image));
  img->width = width;
  img->height = height;
  img->nbands = nbands;
  img->data = malloc((((sizeof(float)) * width) * height) * nbands);
  return img;
}


----------------------------
void heman_image_sample(heman_image *img, float u, float v, float *result)
{
  unsigned int result_idx = 0;
  int x = (0 > (((img->width - 1) > (img->width * u)) ? (img->width * u) : (img->width - 1))) ? (0) : (((img->width - 1) > (img->width * u)) ? (img->width * u) : (img->width - 1));
  int y = (0 > (((img->height - 1) > (img->height * v)) ? (img->height * v) : (img->height - 1))) ? (0) : (((img->height - 1) > (img->height * v)) ? (img->height * v) : (img->height - 1));
  float *data = heman_image_texel(img, x, y);
  unsigned int data_idx = 0;
  for (int b = 0; b < img->nbands; b += 1)
  {
    result[result_idx] = data[data_idx];
    data_idx += 1;
    result_idx += 1;
  }

}


----------------------------
***/


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
    for (int kj = 0; kj < fwidth; kj++)
    {
      for (int ki = 0; ki < fwidth; ki++)
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


/*** DEPENDENCIES:
typedef struct heman_image_s heman_points
----------------------------
typedef struct heman_image_s heman_image
----------------------------
static const float SEALEVEL = 0.5
----------------------------
float *heman_image_texel(heman_image *img, int x, int y)
{
  return (img->data + ((y * img->width) * img->nbands)) + (x * img->nbands);
}


----------------------------
static const float DEFAULT_STRENGTH = 0.6
----------------------------
***/


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


/*** DEPENDENCIES:
static void sphere(float u, float v, float r, kmVec3 *dst)
{
  dst->x = (r * sin(v)) * cos(u);
  dst->y = r * cos(v);
  dst->z = (r * (-sin(v))) * sin(u);
}


----------------------------
typedef struct heman_image_s heman_image
----------------------------
double open_simplex_noise3(struct osn_context *ctx, double x, double y, double z)
{
  double stretchOffset = ((x + y) + z) * ((-1.0) / 6.0);
  double xs = x + stretchOffset;
  double ys = y + stretchOffset;
  double zs = z + stretchOffset;
  int xsb = fastFloor(xs);
  int ysb = fastFloor(ys);
  int zsb = fastFloor(zs);
  double squishOffset = ((xsb + ysb) + zsb) * (1.0 / 3.0);
  double xb = xsb + squishOffset;
  double yb = ysb + squishOffset;
  double zb = zsb + squishOffset;
  double xins = xs - xsb;
  double yins = ys - ysb;
  double zins = zs - zsb;
  double inSum = (xins + yins) + zins;
  double dx0 = x - xb;
  double dy0 = y - yb;
  double dz0 = z - zb;
  double dx_ext0;
  double dy_ext0;
  double dz_ext0;
  double dx_ext1;
  double dy_ext1;
  double dz_ext1;
  int xsv_ext0;
  int ysv_ext0;
  int zsv_ext0;
  int xsv_ext1;
  int ysv_ext1;
  int zsv_ext1;
  double value = 0;
  if (inSum <= 1)
  {
    helper_open_simplex_noise3_1(&dx_ext0, &dy_ext0, &dz_ext0, &dx_ext1, &dy_ext1, &dz_ext1, &xsv_ext0, &ysv_ext0, &zsv_ext0, &xsv_ext1, &ysv_ext1, &zsv_ext1, &value, ctx, xsb, ysb, zsb, xins, yins, zins, inSum, dx0, dy0, dz0);
  }
  else
    if (inSum >= 2)
  {
    helper_open_simplex_noise3_2(&dx0, &dy0, &dz0, &dx_ext0, &dy_ext0, &dz_ext0, &dx_ext1, &dy_ext1, &dz_ext1, &xsv_ext0, &ysv_ext0, &zsv_ext0, &xsv_ext1, &ysv_ext1, &zsv_ext1, &value, ctx, xsb, ysb, zsb, xins, yins, zins, inSum);
  }
  else
  {
    helper_open_simplex_noise3_3(&dx_ext0, &dy_ext0, &dz_ext0, &dx_ext1, &dy_ext1, &dz_ext1, &xsv_ext0, &ysv_ext0, &zsv_ext0, &xsv_ext1, &ysv_ext1, &zsv_ext1, &value, ctx, xsb, ysb, zsb, xins, yins, zins, dx0, dy0, dz0);
  }
  double attn_ext0 = ((2 - (dx_ext0 * dx_ext0)) - (dy_ext0 * dy_ext0)) - (dz_ext0 * dz_ext0);
  if (attn_ext0 > 0)
  {
    attn_ext0 *= attn_ext0;
    value += (attn_ext0 * attn_ext0) * extrapolate3(ctx, xsv_ext0, ysv_ext0, zsv_ext0, dx_ext0, dy_ext0, dz_ext0);
  }
  double attn_ext1 = ((2 - (dx_ext1 * dx_ext1)) - (dy_ext1 * dy_ext1)) - (dz_ext1 * dz_ext1);
  if (attn_ext1 > 0)
  {
    attn_ext1 *= attn_ext1;
    value += (attn_ext1 * attn_ext1) * extrapolate3(ctx, xsv_ext1, ysv_ext1, zsv_ext1, dx_ext1, dy_ext1, dz_ext1);
  }
  return value / 103.0;
}


----------------------------
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
struct osn_context
{
  int16_t *perm;
  int16_t *permGradIndex3D;
}
----------------------------
***/


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


/*** DEPENDENCIES:
void open_simplex_noise_free(struct osn_context *ctx)
{
  if (!ctx)
  {
    return;
  }
  if (ctx->perm)
  {
    free(ctx->perm);
    ctx->perm = 0;
  }
  if (ctx->permGradIndex3D)
  {
    free(ctx->permGradIndex3D);
    ctx->permGradIndex3D = 0;
  }
  free(ctx);
}


----------------------------
typedef struct heman_image_s heman_image
----------------------------
heman_image *heman_image_create(int width, int height, int nbands)
{
  heman_image *img = malloc(sizeof(heman_image));
  img->width = width;
  img->height = height;
  img->nbands = nbands;
  img->data = malloc((((sizeof(float)) * width) * height) * nbands);
  return img;
}


----------------------------
int open_simplex_noise(int64_t seed, struct osn_context **ctx)
{
  int rc;
  int16_t source[256];
  int i;
  int16_t *perm;
  unsigned int perm_idx = 0;
  int16_t *permGradIndex3D;
  unsigned int permGradIndex3D_idx = 0;
  *ctx = malloc(sizeof(*(*ctx)));
  if (!(*ctx))
  {
    return -ENOMEM;
  }
  (*ctx)->perm = 0;
  (*ctx)->permGradIndex3D = 0;
  rc = allocate_perm(*ctx, 256, 256);
  if (rc)
  {
    free(*ctx);
    return rc;
  }
  perm_idx = (*ctx)->perm_idx;
  permGradIndex3D_idx = (*ctx)->permGradIndex3D_idx;
  for (i = 0; i < 256; i += 1)
    source[i] = (int16_t) i;

  seed = (seed * 6364136223846793005LL) + 1442695040888963407LL;
  seed = (seed * 6364136223846793005LL) + 1442695040888963407LL;
  seed = (seed * 6364136223846793005LL) + 1442695040888963407LL;
  for (i = 255; i >= 0; i -= 1)
  {
    seed = (seed * 6364136223846793005LL) + 1442695040888963407LL;
    int r = (int) ((seed + 31) % (i + 1));
    if (r < 0)
    {
      r += i + 1;
    }
    perm[i + perm_idx] = source[r];
    permGradIndex3D[i + permGradIndex3D_idx] = (short) ((perm[i + perm_idx] % (((sizeof(gradients3D)) / (sizeof(gradients3D[0]))) / 3)) * 3);
    source[r] = source[i];
  }

  return 0;
}


----------------------------
struct osn_context
{
  int16_t *perm;
  int16_t *permGradIndex3D;
}
----------------------------
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


----------------------------
***/


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


/*** DEPENDENCIES:
heman_image *heman_ops_warp(heman_image *img, int seed, int octaves)
{
  return heman_ops_warp_core(img, 0, seed, octaves);
}


----------------------------
typedef struct heman_image_s heman_points
----------------------------
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


----------------------------
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
    for (int c = 0; c < texture->nbands; c++)
    {
      *(dst++) = *(texel++);
    }

  }

  return target;
}


----------------------------
typedef struct heman_image_s heman_image
----------------------------
void heman_image_destroy(heman_image *img)
{
  free(img->data);
  free(img);
}


----------------------------
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
    *((&texel[texel_idx])++) = ((float) (rgb & 0xff)) * inv;
    if (target->nbands == 4)
    {
      texel[texel_idx] = ((float) (rgb >> 24)) * inv;
    }
  }

}


----------------------------
heman_image *heman_image_create(int width, int height, int nbands)
{
  heman_image *img = malloc(sizeof(heman_image));
  img->width = width;
  img->height = height;
  img->nbands = nbands;
  img->data = malloc((((sizeof(float)) * width) * height) * nbands);
  return img;
}


----------------------------
typedef unsigned int heman_color
----------------------------
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


----------------------------
void heman_image_clear(heman_image *img, float value)
{
  int size = (img->width * img->height) * img->nbands;
  float *dst = img->data;
  unsigned int dst_idx = 0;
  while (size--)
  {
    dst[dst_idx] = value;
    dst_idx += 1;
  }

}


----------------------------
***/


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
      *((&dst[dst_idx])++) = (ampls[3] * open_simplex_noise2(ctx, u * freqs[3], v * freqs[3])) + (ampls[4] * open_simplex_noise2(ctx, u * freqs[4], v * freqs[4]));
    }

  }

  open_simplex_noise_free(ctx);
  return img;
}


/*** DEPENDENCIES:
double open_simplex_noise2(struct osn_context *ctx, double x, double y)
{
  double stretchOffset = (x + y) * (-0.211324865405187);
  double xs = x + stretchOffset;
  double ys = y + stretchOffset;
  int xsb = fastFloor(xs);
  int ysb = fastFloor(ys);
  double squishOffset = (xsb + ysb) * 0.366025403784439;
  double xb = xsb + squishOffset;
  double yb = ysb + squishOffset;
  double xins = xs - xsb;
  double yins = ys - ysb;
  double inSum = xins + yins;
  double dx0 = x - xb;
  double dy0 = y - yb;
  double dx_ext;
  double dy_ext;
  int xsv_ext;
  int ysv_ext;
  double value = 0;
  double dx1 = (dx0 - 1) - 0.366025403784439;
  double dy1 = (dy0 - 0) - 0.366025403784439;
  double attn1 = (2 - (dx1 * dx1)) - (dy1 * dy1);
  if (attn1 > 0)
  {
    attn1 *= attn1;
    value += (attn1 * attn1) * extrapolate2(ctx, xsb + 1, ysb + 0, dx1, dy1);
  }
  double dx2 = (dx0 - 0) - 0.366025403784439;
  double dy2 = (dy0 - 1) - 0.366025403784439;
  double attn2 = (2 - (dx2 * dx2)) - (dy2 * dy2);
  if (attn2 > 0)
  {
    attn2 *= attn2;
    value += (attn2 * attn2) * extrapolate2(ctx, xsb + 0, ysb + 1, dx2, dy2);
  }
  if (inSum <= 1)
  {
    helper_open_simplex_noise2_1(&dx_ext, &dy_ext, &xsv_ext, &ysv_ext, xsb, ysb, xins, yins, inSum, dx0, dy0);
  }
  else
  {
    helper_open_simplex_noise2_2(&xsb, &ysb, &dx0, &dy0, &dx_ext, &dy_ext, &xsv_ext, &ysv_ext, xins, yins, inSum);
  }
  double attn0 = (2 - (dx0 * dx0)) - (dy0 * dy0);
  if (attn0 > 0)
  {
    attn0 *= attn0;
    value += (attn0 * attn0) * extrapolate2(ctx, xsb, ysb, dx0, dy0);
  }
  double attn_ext = (2 - (dx_ext * dx_ext)) - (dy_ext * dy_ext);
  if (attn_ext > 0)
  {
    attn_ext *= attn_ext;
    value += (attn_ext * attn_ext) * extrapolate2(ctx, xsv_ext, ysv_ext, dx_ext, dy_ext);
  }
  return value / 47.0;
}


----------------------------
void open_simplex_noise_free(struct osn_context *ctx)
{
  if (!ctx)
  {
    return;
  }
  if (ctx->perm)
  {
    free(ctx->perm);
    ctx->perm = 0;
  }
  if (ctx->permGradIndex3D)
  {
    free(ctx->permGradIndex3D);
    ctx->permGradIndex3D = 0;
  }
  free(ctx);
}


----------------------------
typedef struct heman_image_s heman_image
----------------------------
heman_image *heman_image_create(int width, int height, int nbands)
{
  heman_image *img = malloc(sizeof(heman_image));
  img->width = width;
  img->height = height;
  img->nbands = nbands;
  img->data = malloc((((sizeof(float)) * width) * height) * nbands);
  return img;
}


----------------------------
int open_simplex_noise(int64_t seed, struct osn_context **ctx)
{
  int rc;
  int16_t source[256];
  int i;
  int16_t *perm;
  unsigned int perm_idx = 0;
  int16_t *permGradIndex3D;
  unsigned int permGradIndex3D_idx = 0;
  *ctx = malloc(sizeof(*(*ctx)));
  if (!(*ctx))
  {
    return -ENOMEM;
  }
  (*ctx)->perm = 0;
  (*ctx)->permGradIndex3D = 0;
  rc = allocate_perm(*ctx, 256, 256);
  if (rc)
  {
    free(*ctx);
    return rc;
  }
  perm_idx = (*ctx)->perm_idx;
  permGradIndex3D_idx = (*ctx)->permGradIndex3D_idx;
  for (i = 0; i < 256; i += 1)
    source[i] = (int16_t) i;

  seed = (seed * 6364136223846793005LL) + 1442695040888963407LL;
  seed = (seed * 6364136223846793005LL) + 1442695040888963407LL;
  seed = (seed * 6364136223846793005LL) + 1442695040888963407LL;
  for (i = 255; i >= 0; i -= 1)
  {
    seed = (seed * 6364136223846793005LL) + 1442695040888963407LL;
    int r = (int) ((seed + 31) % (i + 1));
    if (r < 0)
    {
      r += i + 1;
    }
    perm[i + perm_idx] = source[r];
    permGradIndex3D[i + permGradIndex3D_idx] = (short) ((perm[i + perm_idx] % (((sizeof(gradients3D)) / (sizeof(gradients3D[0]))) / 3)) * 3);
    source[r] = source[i];
  }

  return 0;
}


----------------------------
struct osn_context
{
  int16_t *perm;
  int16_t *permGradIndex3D;
}
----------------------------
***/


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


/*** DEPENDENCIES:
void heman_image_destroy(heman_image *img)
{
  free(img->data);
  free(img);
}


----------------------------
typedef struct heman_image_s heman_image
----------------------------
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
      *((&dst[dst_idx])++) = (ampls[3] * open_simplex_noise2(ctx, u * freqs[3], v * freqs[3])) + (ampls[4] * open_simplex_noise2(ctx, u * freqs[4], v * freqs[4]));
    }

  }

  open_simplex_noise_free(ctx);
  return img;
}


----------------------------
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
    *((&nptr[nptr_idx])++) = (sptr[sptr_idx]) ? (0) : (INF);
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


----------------------------
heman_image *heman_image_create(int width, int height, int nbands)
{
  heman_image *img = malloc(sizeof(heman_image));
  img->width = width;
  img->height = height;
  img->nbands = nbands;
  img->data = malloc((((sizeof(float)) * width) * height) * nbands);
  return img;
}


----------------------------
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


----------------------------
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


----------------------------
typedef unsigned int heman_color
----------------------------
***/


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


/*** DEPENDENCIES:
void heman_image_destroy(heman_image *img)
{
  free(img->data);
  free(img);
}


----------------------------
typedef struct heman_image_s heman_image
----------------------------
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


----------------------------
heman_image *heman_image_create(int width, int height, int nbands)
{
  heman_image *img = malloc(sizeof(heman_image));
  img->width = width;
  img->height = height;
  img->nbands = nbands;
  img->data = malloc((((sizeof(float)) * width) * height) * nbands);
  return img;
}


----------------------------
typedef unsigned int heman_color
----------------------------
void heman_image_clear(heman_image *img, float value)
{
  int size = (img->width * img->height) * img->nbands;
  float *dst = img->data;
  unsigned int dst_idx = 0;
  while (size--)
  {
    dst[dst_idx] = value;
    dst_idx += 1;
  }

}


----------------------------
***/


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


/*** DEPENDENCIES:
typedef struct heman_image_s heman_points
----------------------------
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


----------------------------
typedef struct heman_image_s heman_image
----------------------------
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


----------------------------
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


----------------------------
typedef unsigned int heman_color
----------------------------
***/


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


/*** DEPENDENCIES:
double open_simplex_noise2(struct osn_context *ctx, double x, double y)
{
  double stretchOffset = (x + y) * (-0.211324865405187);
  double xs = x + stretchOffset;
  double ys = y + stretchOffset;
  int xsb = fastFloor(xs);
  int ysb = fastFloor(ys);
  double squishOffset = (xsb + ysb) * 0.366025403784439;
  double xb = xsb + squishOffset;
  double yb = ysb + squishOffset;
  double xins = xs - xsb;
  double yins = ys - ysb;
  double inSum = xins + yins;
  double dx0 = x - xb;
  double dy0 = y - yb;
  double dx_ext;
  double dy_ext;
  int xsv_ext;
  int ysv_ext;
  double value = 0;
  double dx1 = (dx0 - 1) - 0.366025403784439;
  double dy1 = (dy0 - 0) - 0.366025403784439;
  double attn1 = (2 - (dx1 * dx1)) - (dy1 * dy1);
  if (attn1 > 0)
  {
    attn1 *= attn1;
    value += (attn1 * attn1) * extrapolate2(ctx, xsb + 1, ysb + 0, dx1, dy1);
  }
  double dx2 = (dx0 - 0) - 0.366025403784439;
  double dy2 = (dy0 - 1) - 0.366025403784439;
  double attn2 = (2 - (dx2 * dx2)) - (dy2 * dy2);
  if (attn2 > 0)
  {
    attn2 *= attn2;
    value += (attn2 * attn2) * extrapolate2(ctx, xsb + 0, ysb + 1, dx2, dy2);
  }
  if (inSum <= 1)
  {
    helper_open_simplex_noise2_1(&dx_ext, &dy_ext, &xsv_ext, &ysv_ext, xsb, ysb, xins, yins, inSum, dx0, dy0);
  }
  else
  {
    helper_open_simplex_noise2_2(&xsb, &ysb, &dx0, &dy0, &dx_ext, &dy_ext, &xsv_ext, &ysv_ext, xins, yins, inSum);
  }
  double attn0 = (2 - (dx0 * dx0)) - (dy0 * dy0);
  if (attn0 > 0)
  {
    attn0 *= attn0;
    value += (attn0 * attn0) * extrapolate2(ctx, xsb, ysb, dx0, dy0);
  }
  double attn_ext = (2 - (dx_ext * dx_ext)) - (dy_ext * dy_ext);
  if (attn_ext > 0)
  {
    attn_ext *= attn_ext;
    value += (attn_ext * attn_ext) * extrapolate2(ctx, xsv_ext, ysv_ext, dx_ext, dy_ext);
  }
  return value / 47.0;
}


----------------------------
void open_simplex_noise_free(struct osn_context *ctx)
{
  if (!ctx)
  {
    return;
  }
  if (ctx->perm)
  {
    free(ctx->perm);
    ctx->perm = 0;
  }
  if (ctx->permGradIndex3D)
  {
    free(ctx->permGradIndex3D);
    ctx->permGradIndex3D = 0;
  }
  free(ctx);
}


----------------------------
typedef struct heman_image_s heman_image
----------------------------
heman_image *heman_image_create(int width, int height, int nbands)
{
  heman_image *img = malloc(sizeof(heman_image));
  img->width = width;
  img->height = height;
  img->nbands = nbands;
  img->data = malloc((((sizeof(float)) * width) * height) * nbands);
  return img;
}


----------------------------
int open_simplex_noise(int64_t seed, struct osn_context **ctx)
{
  int rc;
  int16_t source[256];
  int i;
  int16_t *perm;
  unsigned int perm_idx = 0;
  int16_t *permGradIndex3D;
  unsigned int permGradIndex3D_idx = 0;
  *ctx = malloc(sizeof(*(*ctx)));
  if (!(*ctx))
  {
    return -ENOMEM;
  }
  (*ctx)->perm = 0;
  (*ctx)->permGradIndex3D = 0;
  rc = allocate_perm(*ctx, 256, 256);
  if (rc)
  {
    free(*ctx);
    return rc;
  }
  perm_idx = (*ctx)->perm_idx;
  permGradIndex3D_idx = (*ctx)->permGradIndex3D_idx;
  for (i = 0; i < 256; i += 1)
    source[i] = (int16_t) i;

  seed = (seed * 6364136223846793005LL) + 1442695040888963407LL;
  seed = (seed * 6364136223846793005LL) + 1442695040888963407LL;
  seed = (seed * 6364136223846793005LL) + 1442695040888963407LL;
  for (i = 255; i >= 0; i -= 1)
  {
    seed = (seed * 6364136223846793005LL) + 1442695040888963407LL;
    int r = (int) ((seed + 31) % (i + 1));
    if (r < 0)
    {
      r += i + 1;
    }
    perm[i + perm_idx] = source[r];
    permGradIndex3D[i + permGradIndex3D_idx] = (short) ((perm[i + perm_idx] % (((sizeof(gradients3D)) / (sizeof(gradients3D[0]))) / 3)) * 3);
    source[r] = source[i];
  }

  return 0;
}


----------------------------
struct osn_context
{
  int16_t *perm;
  int16_t *permGradIndex3D;
}
----------------------------
***/


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


/*** DEPENDENCIES:
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


----------------------------
void heman_image_destroy(heman_image *img)
{
  free(img->data);
  free(img);
}


----------------------------
typedef struct heman_image_s heman_image
----------------------------
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
      *((&dst[dst_idx])++) = (ampls[3] * open_simplex_noise2(ctx, u * freqs[3], v * freqs[3])) + (ampls[4] * open_simplex_noise2(ctx, u * freqs[4], v * freqs[4]));
    }

  }

  open_simplex_noise_free(ctx);
  return img;
}


----------------------------
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


----------------------------
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
    *((&nptr[nptr_idx])++) = (sptr[sptr_idx]) ? (0) : (INF);
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


----------------------------
heman_image *heman_image_create(int width, int height, int nbands)
{
  heman_image *img = malloc(sizeof(heman_image));
  img->width = width;
  img->height = height;
  img->nbands = nbands;
  img->data = malloc((((sizeof(float)) * width) * height) * nbands);
  return img;
}


----------------------------
***/


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


/*** DEPENDENCIES:
typedef struct heman_image_s heman_points
----------------------------
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
    for (int kj = 0; kj < fwidth; kj++)
    {
      for (int ki = 0; ki < fwidth; ki++)
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


----------------------------
void heman_image_destroy(heman_image *img)
{
  free(img->data);
  free(img);
}


----------------------------
typedef struct heman_image_s heman_image
----------------------------
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
      *((&dst[dst_idx])++) = (ampls[3] * open_simplex_noise2(ctx, u * freqs[3], v * freqs[3])) + (ampls[4] * open_simplex_noise2(ctx, u * freqs[4], v * freqs[4]));
    }

  }

  open_simplex_noise_free(ctx);
  return img;
}


----------------------------
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


----------------------------
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
    *((&nptr[nptr_idx])++) = (sptr[sptr_idx]) ? (0) : (INF);
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


----------------------------
heman_image *heman_image_create(int width, int height, int nbands)
{
  heman_image *img = malloc(sizeof(heman_image));
  img->width = width;
  img->height = height;
  img->nbands = nbands;
  img->data = malloc((((sizeof(float)) * width) * height) * nbands);
  return img;
}


----------------------------
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


----------------------------
void heman_image_clear(heman_image *img, float value)
{
  int size = (img->width * img->height) * img->nbands;
  float *dst = img->data;
  unsigned int dst_idx = 0;
  while (size--)
  {
    dst[dst_idx] = value;
    dst_idx += 1;
  }

}


----------------------------
***/


