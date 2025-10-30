heman_image *heman_import_u8(int width, int height, int nbands, const heman_byte *source, float minval, float maxval)
{
  heman_image *result = heman_image_create(width, height, nbands);
  const heman_byte *inp = source;
  unsigned int inp_idx = 0;
  float *outp = result->data;
  float scale = (maxval - minval) / 255.0f;
  int size = (height * width) * nbands;
  for (int i = 0; i < size; i += 1)
  {
    float v = (inp[inp_idx] * scale) + minval;
    inp_idx += 1;
    *(outp++) = (minval > ((maxval > v) ? (v) : (maxval))) ? (minval) : ((maxval > v) ? (v) : (maxval));
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
typedef unsigned char heman_byte
----------------------------
typedef struct heman_image_s heman_image
----------------------------
***/


