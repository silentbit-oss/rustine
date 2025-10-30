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


/*** DEPENDENCIES:
typedef struct heman_image_s heman_image
----------------------------
typedef struct heman_image_s heman_points
----------------------------
float *heman_image_texel(heman_image *img, int x, int y)
{
  return (img->data + ((y * img->width) * img->nbands)) + (x * img->nbands);
}


----------------------------
***/


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


/*** DEPENDENCIES:
typedef struct heman_image_s heman_image
----------------------------
typedef struct heman_image_s heman_points
----------------------------
typedef unsigned int heman_color
----------------------------
float *heman_image_texel(heman_image *img, int x, int y)
{
  return (img->data + ((y * img->width) * img->nbands)) + (x * img->nbands);
}


----------------------------
***/


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


/*** DEPENDENCIES:
typedef struct heman_image_s heman_image
----------------------------
typedef struct heman_image_s heman_points
----------------------------
typedef unsigned int heman_color
----------------------------
float *heman_image_texel(heman_image *img, int x, int y)
{
  return (img->data + ((y * img->width) * img->nbands)) + (x * img->nbands);
}


----------------------------
***/


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
        for (int c = 0; c < target->nbands; c++)
        {
          *(texel++) += gaussian_splat[(kj * fwidth) + ki];
        }

      }

    }

  }

  free(gaussian_splat);
}


/*** DEPENDENCIES:
typedef struct heman_image_s heman_image
----------------------------
typedef struct heman_image_s heman_points
----------------------------
float *heman_image_texel(heman_image *img, int x, int y)
{
  return (img->data + ((y * img->width) * img->nbands)) + (x * img->nbands);
}


----------------------------
void generate_gaussian_splat(float *target, int fwidth)
{
  int *gaussian_row = malloc(fwidth * (sizeof(int)));
  generate_gaussian_row(gaussian_row, fwidth);
  int shift = 1 << (fwidth - 1);
  float scale = 1.0 / (shift * shift);
  float *gptr = target;
  unsigned int gptr_idx = 0;
  for (int j = 0; j < fwidth; j += 1)
  {
    for (int i = 0; i < fwidth; i += 1)
    {
      gptr[gptr_idx] = (gaussian_row[i] * gaussian_row[j]) * scale;
      gptr_idx += 1;
    }

  }

  free(gaussian_row);
}


----------------------------
***/


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
typedef unsigned int heman_color
----------------------------
float *heman_image_texel(heman_image *img, int x, int y)
{
  return (img->data + ((y * img->width) * img->nbands)) + (x * img->nbands);
}


----------------------------
void heman_points_destroy(heman_points *img)
{
  free(img->data);
  free(img);
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


