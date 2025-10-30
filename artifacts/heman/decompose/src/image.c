heman_image *heman_image_create(int width, int height, int nbands)
{
  heman_image *img = malloc(sizeof(heman_image));
  img->width = width;
  img->height = height;
  img->nbands = nbands;
  img->data = malloc((((sizeof(float)) * width) * height) * nbands);
  return img;
}


/*** DEPENDENCIES:
typedef struct heman_image_s heman_image
----------------------------
***/


void heman_image_info(heman_image *img, int *width, int *height, int *nbands)
{
  *width = img->width;
  *height = img->height;
  *nbands = img->nbands;
}


/*** DEPENDENCIES:
typedef struct heman_image_s heman_image
----------------------------
***/


float *heman_image_data(heman_image *img)
{
  return img->data;
}


/*** DEPENDENCIES:
typedef struct heman_image_s heman_image
----------------------------
***/


void heman_image_array(heman_image *img, float **data, int *nfloats)
{
  *data = img->data;
  *nfloats = (img->width * img->height) * img->nbands;
}


/*** DEPENDENCIES:
typedef struct heman_image_s heman_image
----------------------------
***/


float *heman_image_texel(heman_image *img, int x, int y)
{
  return (img->data + ((y * img->width) * img->nbands)) + (x * img->nbands);
}


/*** DEPENDENCIES:
typedef struct heman_image_s heman_image
----------------------------
***/


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


/*** DEPENDENCIES:
typedef struct heman_image_s heman_image
----------------------------
***/


void heman_image_destroy(heman_image *img)
{
  free(img->data);
  free(img);
}


/*** DEPENDENCIES:
typedef struct heman_image_s heman_image
----------------------------
***/


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


/*** DEPENDENCIES:
typedef struct heman_image_s heman_image
----------------------------
float *heman_image_texel(heman_image *img, int x, int y)
{
  return (img->data + ((y * img->width) * img->nbands)) + (x * img->nbands);
}


----------------------------
***/


heman_image *heman_image_extract_alpha(heman_image *img)
{
  assert(img->nbands == 4);
  heman_image *retval = heman_image_create(img->width, img->height, 1);
  int size = img->width * img->height;
  float *src = img->data;
  unsigned int src_idx = 0;
  float *dst = retval->data;
  unsigned int dst_idx = 0;
  while (size--)
  {
    src_idx += 3;
    dst[dst_idx] = src[src_idx];
    src_idx += 1;
    dst_idx += 1;
  }

  return retval;
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


heman_image *heman_image_extract_rgb(heman_image *img)
{
  assert(img->nbands == 4);
  heman_image *retval = heman_image_create(img->width, img->height, 3);
  int size = img->width * img->height;
  float *src = img->data;
  unsigned int src_idx = 0;
  float *dst = retval->data;
  unsigned int dst_idx = 0;
  while (size--)
  {
    dst[dst_idx] = src[src_idx];
    src_idx += 1;
    dst_idx += 1;
    dst[dst_idx] = src[src_idx];
    src_idx += 1;
    dst_idx += 1;
    *((&dst[dst_idx])++) = *((&src[src_idx])++);
    ++(&src[src_idx]);
  }

  return retval;
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


