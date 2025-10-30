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


/*** DEPENDENCIES:
typedef struct heman_image_s heman_image
----------------------------
float *heman_image_texel(heman_image *img, int x, int y)
{
  return (img->data + ((y * img->width) * img->nbands)) + (x * img->nbands);
}


----------------------------
***/


void heman_export_u8(heman_image *source, float minv, float maxv, heman_byte *outp)
{
  const float *inp = source->data;
  unsigned int inp_idx = 0;
  float scale = 1.0f / (maxv - minv);
  int size = (source->height * source->width) * source->nbands;
  for (int i = 0; i < size; i += 1)
  {
    float v = (255 * (inp[inp_idx] - minv)) * scale;
    inp_idx += 1;
    *(outp++) = (0 > ((255 > v) ? (v) : (255))) ? (0) : ((255 > v) ? (v) : (255));
  }

}


/*** DEPENDENCIES:
typedef unsigned char heman_byte
----------------------------
typedef struct heman_image_s heman_image
----------------------------
***/


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


/*** DEPENDENCIES:
typedef struct heman_image_s heman_image
----------------------------
void heman_export_u8(heman_image *source, float minv, float maxv, heman_byte *outp)
{
  const float *inp = source->data;
  unsigned int inp_idx = 0;
  float scale = 1.0f / (maxv - minv);
  int size = (source->height * source->width) * source->nbands;
  for (int i = 0; i < size; i += 1)
  {
    float v = (255 * (inp[inp_idx] - minv)) * scale;
    inp_idx += 1;
    *(outp++) = (0 > ((255 > v) ? (v) : (255))) ? (0) : ((255 > v) ? (v) : (255));
  }

}


----------------------------
typedef unsigned char heman_byte
----------------------------
float *heman_image_texel(heman_image *img, int x, int y)
{
  return (img->data + ((y * img->width) * img->nbands)) + (x * img->nbands);
}


----------------------------
***/


