inline float smoothstep(float edge0, float edge1, float x)
{
  float t;
  t = (0.0f > ((1.0f > ((x - edge0) / (edge1 - edge0))) ? ((x - edge0) / (edge1 - edge0)) : (1.0f))) ? (0.0f) : ((1.0f > ((x - edge0) / (edge1 - edge0))) ? ((x - edge0) / (edge1 - edge0)) : (1.0f));
  return (t * t) * (3.0 - (2.0 * t));
}


/*** DEPENDENCIES:
***/


// hint:  ['index0_ref is a mutable refrence to int', 'index1_ref is a mutable refrence to int', 'dst_idx_ref is a mutable refrence to unsigned int', 't_ref is a mutable refrence to float', 'x_ref is a mutable refrence to int']
void helper_heman_color_create_gradient_1(int * const index0_ref, int * const index1_ref, unsigned int * const dst_idx_ref, float * const t_ref, int * const x_ref, int num_colors, const int * const cp_locations, float * const f32colors, float * const dst, float invgamma)
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
  *((&dst[dst_idx])++) = pow(b, invgamma);
  *index0_ref = index0;
  *index1_ref = index1;
  *dst_idx_ref = dst_idx;
  *t_ref = t;
  *x_ref = x;
}


/*** DEPENDENCIES:
***/


void heman_color_set_gamma(float g)
{
  _gamma = g;
}


/*** DEPENDENCIES:
extern float _gamma
----------------------------
***/


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
    *((&dst[dst_idx])++) = v;
    *((&dst[dst_idx])++) = v;
  }

  return result;
}


/*** DEPENDENCIES:
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
typedef struct heman_image_s heman_image
----------------------------
***/


heman_image *heman_color_to_grayscale(heman_image *colorimg)
{
  assert(colorimg->nbands == 3);
  int w = colorimg->width;
  int h = colorimg->height;
  heman_image *result = heman_image_create(w, h, 1);
  int size = w * h;
  float *dst = result->data;
  const float *src = colorimg->data;
  unsigned int src_idx = 0;
  for (int i = 0; i < size; i += 1)
  {
    float r = src[src_idx];
    src_idx += 1;
    float g = src[src_idx];
    src_idx += 1;
    float b = *((&src[src_idx])++);
    *(dst++) = ((0.299 * r) + (0.587 * g)) + (0.114 * b);
  }

  return result;
}


/*** DEPENDENCIES:
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
typedef struct heman_image_s heman_image
----------------------------
***/


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
    *((&dst[dst_idx])++) = v;
    *((&dst[dst_idx])++) = 0;
  }

  return target;
}


/*** DEPENDENCIES:
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
typedef struct heman_image_s heman_image
----------------------------
***/


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


/*** DEPENDENCIES:
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
typedef struct heman_image_s heman_image
----------------------------
***/


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


/*** DEPENDENCIES:
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
    *((&dst[dst_idx])++) = v;
    *((&dst[dst_idx])++) = 0;
  }

  return target;
}


----------------------------
float *heman_image_texel(heman_image *img, int x, int y)
{
  return (img->data + ((y * img->width) * img->nbands)) + (x * img->nbands);
}


----------------------------
***/


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
    *((&f32color[f32color_idx])++) = pow(g, _gamma);
    *((&f32color[f32color_idx])++) = pow(b, _gamma);
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
    helper_heman_color_create_gradient_1(&index0, &index1, &dst_idx, &t, &x, num_colors, cp_locations, f32colors, dst, invgamma);
  }

  free(f32colors);
  return result;
}


/*** DEPENDENCIES:
typedef struct heman_image_s heman_image
----------------------------
extern float _gamma
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
void helper_heman_color_create_gradient_1(int * const index0_ref, int * const index1_ref, unsigned int * const dst_idx_ref, float * const t_ref, int * const x_ref, int num_colors, const int * const cp_locations, float * const f32colors, float * const dst, float invgamma)
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
  *((&dst[dst_idx])++) = pow(b, invgamma);
  *index0_ref = index0;
  *index1_ref = index1;
  *dst_idx_ref = dst_idx;
  *t_ref = t;
  *x_ref = x;
}


----------------------------
***/


