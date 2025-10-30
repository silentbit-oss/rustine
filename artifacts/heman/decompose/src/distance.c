static void edt(float *f, float *d, float *z, uint16_t *w, int n)
{
  int k = 0;
  float s;
  w[0] = 0;
  z[0] = -INF;
  z[1] = +INF;
  for (int q = 1; q < n; q += 1)
  {
    s = ((f[q] + (q * q)) - (f[w[k]] + (w[k] * w[k]))) / ((2 * q) - (2 * w[k]));
    while (s <= z[k])
    {
      k -= 1;
      s = ((f[q] + (q * q)) - (f[w[k]] + (w[k] * w[k]))) / ((2 * q) - (2 * w[k]));
    }

    k += 1;
    w[k] = q;
    z[k] = s;
    z[k + 1] = +INF;
  }

  k = 0;
  for (int q = 0; q < n; q += 1)
  {
    while (z[k + 1] < q)
    {
      k += 1;
    }

    d[q] = ((q - w[k]) * (q - w[k])) + f[w[k]];
  }

}


/*** DEPENDENCIES:
const float INF = 1E20
----------------------------
***/


static void edt_with_payload(float *f, float *d, float *z, uint16_t *w, int n, float *payload_in, float *payload_out)
{
  int k = 0;
  float s;
  w[0] = 0;
  z[0] = -INF;
  z[1] = +INF;
  for (int q = 1; q < n; q += 1)
  {
    s = ((f[q] + (q * q)) - (f[w[k]] + (w[k] * w[k]))) / ((2 * q) - (2 * w[k]));
    while (s <= z[k])
    {
      k -= 1;
      s = ((f[q] + (q * q)) - (f[w[k]] + (w[k] * w[k]))) / ((2 * q) - (2 * w[k]));
    }

    k += 1;
    w[k] = q;
    z[k] = s;
    z[k + 1] = +INF;
  }

  k = 0;
  for (int q = 0; q < n; q += 1)
  {
    while (z[k + 1] < q)
    {
      k += 1;
    }

    d[q] = ((q - w[k]) * (q - w[k])) + f[w[k]];
    payload_out[q * 2] = payload_in[w[k] * 2];
    payload_out[(q * 2) + 1] = payload_in[(w[k] * 2) + 1];
  }

}


/*** DEPENDENCIES:
const float INF = 1E20
----------------------------
***/


heman_image *heman_distance_from_cpcf(heman_image *cf)
{
  assert((cf->nbands == 2) && "Coordinate field input must have 2 bands.");
  heman_image *udf = heman_image_create(cf->width, cf->height, 1);
  float *dptr = udf->data;
  float *sptr = cf->data;
  unsigned int sptr_idx = 0;
  float scale = 1.0f / sqrt((cf->width * cf->width) + (cf->height * cf->height));
  for (int y = 0; y < cf->height; y += 1)
  {
    for (int x = 0; x < cf->width; x += 1)
    {
      float u = sptr[sptr_idx];
      sptr_idx += 1;
      float v = sptr[sptr_idx];
      sptr_idx += 1;
      float dist = sqrt(((u - x) * (u - x)) + ((v - y) * (v - y))) * scale;
      *(dptr++) = dist;
    }

  }

  return udf;
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


heman_image *heman_distance_identity_cpcf(int width, int height)
{
  heman_image *retval = heman_image_create(width, height, 2);
  float *cdata = retval->data;
  unsigned int cdata_idx = 0;
  for (int y = 0; y < height; y += 1)
  {
    for (int x = 0; x < width; x += 1)
    {
      cdata[cdata_idx] = x;
      cdata_idx += 1;
      *((&cdata[cdata_idx])++) = y;
    }

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


static void transform_to_distance(heman_image *sdf)
{
  int width = sdf->width;
  int height = sdf->height;
  int size = width * height;
  float *ff = calloc(size, sizeof(float));
  float *dd = calloc(size, sizeof(float));
  float *zz = calloc((height + 1) * (width + 1), sizeof(float));
  uint16_t *ww = calloc(size, sizeof(uint16_t));
  int x;
  #pragma omp parallel for
  for (x = 0; x < width; x += 1)
  {
    float *f = ff + (height * x);
    float *d = dd + (height * x);
    float *z = zz + ((height + 1) * x);
    uint16_t *w = ww + (height * x);
    for (int y = 0; y < height; y += 1)
    {
      f[y] = *((sdf->data + (y * width)) + x);
    }

    edt(f, d, z, w, height);
    for (int y = 0; y < height; y += 1)
    {
      *((sdf->data + (y * width)) + x) = d[y];
    }

  }

  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    float *f = ff + (width * y);
    float *d = dd + (width * y);
    float *z = zz + ((width + 1) * y);
    uint16_t *w = ww + (width * y);
    for (int x = 0; x < width; x += 1)
    {
      f[x] = *((sdf->data + (y * width)) + x);
    }

    edt(f, d, z, w, width);
    for (int x = 0; x < width; x += 1)
    {
      *((sdf->data + (y * width)) + x) = d[x];
    }

  }

  free(ff);
  free(dd);
  free(zz);
  free(ww);
}


/*** DEPENDENCIES:
static void edt(float *f, float *d, float *z, uint16_t *w, int n)
{
  int k = 0;
  float s;
  w[0] = 0;
  z[0] = -INF;
  z[1] = +INF;
  for (int q = 1; q < n; q += 1)
  {
    s = ((f[q] + (q * q)) - (f[w[k]] + (w[k] * w[k]))) / ((2 * q) - (2 * w[k]));
    while (s <= z[k])
    {
      k -= 1;
      s = ((f[q] + (q * q)) - (f[w[k]] + (w[k] * w[k]))) / ((2 * q) - (2 * w[k]));
    }

    k += 1;
    w[k] = q;
    z[k] = s;
    z[k + 1] = +INF;
  }

  k = 0;
  for (int q = 0; q < n; q += 1)
  {
    while (z[k + 1] < q)
    {
      k += 1;
    }

    d[q] = ((q - w[k]) * (q - w[k])) + f[w[k]];
  }

}


----------------------------
typedef struct heman_image_s heman_image
----------------------------
***/


// hint:  ['width_ref is a mutable refrence to int', 'x_ref is a mutable refrence to int', 'x_ref is a mutable refrence to int', 'x_ref is a mutable refrence to int']
void helper_transform_to_coordfield_1(int * const width_ref, int * const x_ref, int * const x_ref, int * const x_ref, heman_image * const sdf, heman_image * const cf, int height, float * const ff, float * const dd, float * const zz, uint16_t * const ww)
{
  int width = *width_ref;
  int x = *x_ref;
  int x = *x_ref;
  int x = *x_ref;
  float *pl1 = calloc(height * 2, sizeof(float));
  float *pl2 = calloc(height * 2, sizeof(float));
  float *f = ff + (height * x);
  float *d = dd + (height * x);
  float *z = zz + ((height + 1) * x);
  uint16_t *w = ww + (height * x);
  for (int y = 0; y < height; y += 1)
  {
    f[y] = *((sdf->data + (y * width)) + x);
    pl1[y * 2] = *((cf->data + (2 * ((y * width) + x))) + 0);
    pl1[(y * 2) + 1] = *((cf->data + (2 * ((y * width) + x))) + 1);
  }

  edt_with_payload(f, d, z, w, height, pl1, pl2);
  for (int y = 0; y < height; y += 1)
  {
    *((sdf->data + (y * width)) + x) = d[y];
    *((cf->data + (2 * ((y * width) + x))) + 0) = pl2[2 * y];
    *((cf->data + (2 * ((y * width) + x))) + 1) = pl2[(2 * y) + 1];
  }

  free(pl1);
  free(pl2);
  *width_ref = width;
  *x_ref = x;
  *x_ref = x;
  *x_ref = x;
}


/*** DEPENDENCIES:
static void edt_with_payload(float *f, float *d, float *z, uint16_t *w, int n, float *payload_in, float *payload_out)
{
  int k = 0;
  float s;
  w[0] = 0;
  z[0] = -INF;
  z[1] = +INF;
  for (int q = 1; q < n; q += 1)
  {
    s = ((f[q] + (q * q)) - (f[w[k]] + (w[k] * w[k]))) / ((2 * q) - (2 * w[k]));
    while (s <= z[k])
    {
      k -= 1;
      s = ((f[q] + (q * q)) - (f[w[k]] + (w[k] * w[k]))) / ((2 * q) - (2 * w[k]));
    }

    k += 1;
    w[k] = q;
    z[k] = s;
    z[k + 1] = +INF;
  }

  k = 0;
  for (int q = 0; q < n; q += 1)
  {
    while (z[k + 1] < q)
    {
      k += 1;
    }

    d[q] = ((q - w[k]) * (q - w[k])) + f[w[k]];
    payload_out[q * 2] = payload_in[w[k] * 2];
    payload_out[(q * 2) + 1] = payload_in[(w[k] * 2) + 1];
  }

}


----------------------------
typedef struct heman_image_s heman_image
----------------------------
***/


// hint:  ['width_ref is a mutable refrence to int', 'y_ref is a mutable refrence to int']
void helper_transform_to_coordfield_2(int * const width_ref, int * const y_ref, heman_image * const sdf, heman_image * const cf, float * const ff, float * const dd, float * const zz, uint16_t * const ww)
{
  int width = *width_ref;
  int y = *y_ref;
  float *pl1 = calloc(width * 2, sizeof(float));
  float *pl2 = calloc(width * 2, sizeof(float));
  float *f = ff + (width * y);
  float *d = dd + (width * y);
  float *z = zz + ((width + 1) * y);
  uint16_t *w = ww + (width * y);
  for (int x = 0; x < width; x += 1)
  {
    f[x] = *((sdf->data + (y * width)) + x);
    pl1[x * 2] = *((cf->data + (2 * ((y * width) + x))) + 0);
    pl1[(x * 2) + 1] = *((cf->data + (2 * ((y * width) + x))) + 1);
  }

  edt_with_payload(f, d, z, w, width, pl1, pl2);
  for (int x = 0; x < width; x += 1)
  {
    *((sdf->data + (y * width)) + x) = d[x];
    *((cf->data + (2 * ((y * width) + x))) + 0) = pl2[2 * x];
    *((cf->data + (2 * ((y * width) + x))) + 1) = pl2[(2 * x) + 1];
  }

  free(pl1);
  free(pl2);
  *width_ref = width;
  *y_ref = y;
}


/*** DEPENDENCIES:
static void edt_with_payload(float *f, float *d, float *z, uint16_t *w, int n, float *payload_in, float *payload_out)
{
  int k = 0;
  float s;
  w[0] = 0;
  z[0] = -INF;
  z[1] = +INF;
  for (int q = 1; q < n; q += 1)
  {
    s = ((f[q] + (q * q)) - (f[w[k]] + (w[k] * w[k]))) / ((2 * q) - (2 * w[k]));
    while (s <= z[k])
    {
      k -= 1;
      s = ((f[q] + (q * q)) - (f[w[k]] + (w[k] * w[k]))) / ((2 * q) - (2 * w[k]));
    }

    k += 1;
    w[k] = q;
    z[k] = s;
    z[k + 1] = +INF;
  }

  k = 0;
  for (int q = 0; q < n; q += 1)
  {
    while (z[k + 1] < q)
    {
      k += 1;
    }

    d[q] = ((q - w[k]) * (q - w[k])) + f[w[k]];
    payload_out[q * 2] = payload_in[w[k] * 2];
    payload_out[(q * 2) + 1] = payload_in[(w[k] * 2) + 1];
  }

}


----------------------------
typedef struct heman_image_s heman_image
----------------------------
***/


static void transform_to_coordfield(heman_image *sdf, heman_image *cf)
{
  int width = sdf->width;
  int height = sdf->height;
  int size = width * height;
  float *ff = calloc(size, sizeof(float));
  float *dd = calloc(size, sizeof(float));
  float *zz = calloc((height + 1) * (width + 1), sizeof(float));
  uint16_t *ww = calloc(size, sizeof(uint16_t));
  int x;
  #pragma omp parallel for
  for (x = 0; x < width; x += 1)
  {
    helper_transform_to_coordfield_1(&width, &x, &x, &x, sdf, cf, height, ff, dd, zz, ww);
  }

  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    helper_transform_to_coordfield_2(&width, &y, sdf, cf, ff, dd, zz, ww);
  }

  free(ff);
  free(dd);
  free(zz);
  free(ww);
}


/*** DEPENDENCIES:
void helper_transform_to_coordfield_1(int * const width_ref, int * const x_ref, int * const x_ref, int * const x_ref, heman_image * const sdf, heman_image * const cf, int height, float * const ff, float * const dd, float * const zz, uint16_t * const ww)
{
  int width = *width_ref;
  int x = *x_ref;
  int x = *x_ref;
  int x = *x_ref;
  float *pl1 = calloc(height * 2, sizeof(float));
  float *pl2 = calloc(height * 2, sizeof(float));
  float *f = ff + (height * x);
  float *d = dd + (height * x);
  float *z = zz + ((height + 1) * x);
  uint16_t *w = ww + (height * x);
  for (int y = 0; y < height; y += 1)
  {
    f[y] = *((sdf->data + (y * width)) + x);
    pl1[y * 2] = *((cf->data + (2 * ((y * width) + x))) + 0);
    pl1[(y * 2) + 1] = *((cf->data + (2 * ((y * width) + x))) + 1);
  }

  edt_with_payload(f, d, z, w, height, pl1, pl2);
  for (int y = 0; y < height; y += 1)
  {
    *((sdf->data + (y * width)) + x) = d[y];
    *((cf->data + (2 * ((y * width) + x))) + 0) = pl2[2 * y];
    *((cf->data + (2 * ((y * width) + x))) + 1) = pl2[(2 * y) + 1];
  }

  free(pl1);
  free(pl2);
  *width_ref = width;
  *x_ref = x;
  *x_ref = x;
  *x_ref = x;
}


----------------------------
void helper_transform_to_coordfield_2(int * const width_ref, int * const y_ref, heman_image * const sdf, heman_image * const cf, float * const ff, float * const dd, float * const zz, uint16_t * const ww)
{
  int width = *width_ref;
  int y = *y_ref;
  float *pl1 = calloc(width * 2, sizeof(float));
  float *pl2 = calloc(width * 2, sizeof(float));
  float *f = ff + (width * y);
  float *d = dd + (width * y);
  float *z = zz + ((width + 1) * y);
  uint16_t *w = ww + (width * y);
  for (int x = 0; x < width; x += 1)
  {
    f[x] = *((sdf->data + (y * width)) + x);
    pl1[x * 2] = *((cf->data + (2 * ((y * width) + x))) + 0);
    pl1[(x * 2) + 1] = *((cf->data + (2 * ((y * width) + x))) + 1);
  }

  edt_with_payload(f, d, z, w, width, pl1, pl2);
  for (int x = 0; x < width; x += 1)
  {
    *((sdf->data + (y * width)) + x) = d[x];
    *((cf->data + (2 * ((y * width) + x))) + 0) = pl2[2 * x];
    *((cf->data + (2 * ((y * width) + x))) + 1) = pl2[(2 * x) + 1];
  }

  free(pl1);
  free(pl2);
  *width_ref = width;
  *y_ref = y;
}


----------------------------
typedef struct heman_image_s heman_image
----------------------------
***/


heman_image *heman_distance_create_df(heman_image *src)
{
  assert((src->nbands == 1) && "Distance field input must have only 1 band.");
  heman_image *positive = heman_image_create(src->width, src->height, 1);
  int size = src->height * src->width;
  float *pptr = positive->data;
  unsigned int pptr_idx = 0;
  float *sptr = src->data;
  unsigned int sptr_idx = 0;
  for (int i = 0; i < size; i += 1, sptr_idx += 1)
  {
    pptr[pptr_idx] = (sptr[sptr_idx]) ? (0) : (INF);
    pptr_idx += 1;
  }

  transform_to_distance(positive);
  float inv = 1.0f / src->width;
  pptr_idx = positive->data;
  for (int i = 0; i < size; i += 1, pptr_idx += 1)
  {
    pptr[pptr_idx] = sqrt(*(&pptr[pptr_idx])) * inv;
  }

  return positive;
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
const float INF = 1E20
----------------------------
static void transform_to_distance(heman_image *sdf)
{
  int width = sdf->width;
  int height = sdf->height;
  int size = width * height;
  float *ff = calloc(size, sizeof(float));
  float *dd = calloc(size, sizeof(float));
  float *zz = calloc((height + 1) * (width + 1), sizeof(float));
  uint16_t *ww = calloc(size, sizeof(uint16_t));
  int x;
  #pragma omp parallel for
  for (x = 0; x < width; x += 1)
  {
    float *f = ff + (height * x);
    float *d = dd + (height * x);
    float *z = zz + ((height + 1) * x);
    uint16_t *w = ww + (height * x);
    for (int y = 0; y < height; y += 1)
    {
      f[y] = *((sdf->data + (y * width)) + x);
    }

    edt(f, d, z, w, height);
    for (int y = 0; y < height; y += 1)
    {
      *((sdf->data + (y * width)) + x) = d[y];
    }

  }

  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    float *f = ff + (width * y);
    float *d = dd + (width * y);
    float *z = zz + ((width + 1) * y);
    uint16_t *w = ww + (width * y);
    for (int x = 0; x < width; x += 1)
    {
      f[x] = *((sdf->data + (y * width)) + x);
    }

    edt(f, d, z, w, width);
    for (int x = 0; x < width; x += 1)
    {
      *((sdf->data + (y * width)) + x) = d[x];
    }

  }

  free(ff);
  free(dd);
  free(zz);
  free(ww);
}


----------------------------
typedef struct heman_image_s heman_image
----------------------------
***/


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


/*** DEPENDENCIES:
const float INF = 1E20
----------------------------
void heman_image_destroy(heman_image *img)
{
  free(img->data);
  free(img);
}


----------------------------
typedef struct heman_image_s heman_image
----------------------------
static void transform_to_distance(heman_image *sdf)
{
  int width = sdf->width;
  int height = sdf->height;
  int size = width * height;
  float *ff = calloc(size, sizeof(float));
  float *dd = calloc(size, sizeof(float));
  float *zz = calloc((height + 1) * (width + 1), sizeof(float));
  uint16_t *ww = calloc(size, sizeof(uint16_t));
  int x;
  #pragma omp parallel for
  for (x = 0; x < width; x += 1)
  {
    float *f = ff + (height * x);
    float *d = dd + (height * x);
    float *z = zz + ((height + 1) * x);
    uint16_t *w = ww + (height * x);
    for (int y = 0; y < height; y += 1)
    {
      f[y] = *((sdf->data + (y * width)) + x);
    }

    edt(f, d, z, w, height);
    for (int y = 0; y < height; y += 1)
    {
      *((sdf->data + (y * width)) + x) = d[y];
    }

  }

  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    float *f = ff + (width * y);
    float *d = dd + (width * y);
    float *z = zz + ((width + 1) * y);
    uint16_t *w = ww + (width * y);
    for (int x = 0; x < width; x += 1)
    {
      f[x] = *((sdf->data + (y * width)) + x);
    }

    edt(f, d, z, w, width);
    for (int x = 0; x < width; x += 1)
    {
      *((sdf->data + (y * width)) + x) = d[x];
    }

  }

  free(ff);
  free(dd);
  free(zz);
  free(ww);
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


/*** DEPENDENCIES:
const float INF = 1E20
----------------------------
void heman_image_destroy(heman_image *img)
{
  free(img->data);
  free(img);
}


----------------------------
typedef struct heman_image_s heman_image
----------------------------
heman_image *heman_distance_identity_cpcf(int width, int height)
{
  heman_image *retval = heman_image_create(width, height, 2);
  float *cdata = retval->data;
  unsigned int cdata_idx = 0;
  for (int y = 0; y < height; y += 1)
  {
    for (int x = 0; x < width; x += 1)
    {
      cdata[cdata_idx] = x;
      cdata_idx += 1;
      *((&cdata[cdata_idx])++) = y;
    }

  }

  return retval;
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
static void transform_to_coordfield(heman_image *sdf, heman_image *cf)
{
  int width = sdf->width;
  int height = sdf->height;
  int size = width * height;
  float *ff = calloc(size, sizeof(float));
  float *dd = calloc(size, sizeof(float));
  float *zz = calloc((height + 1) * (width + 1), sizeof(float));
  uint16_t *ww = calloc(size, sizeof(uint16_t));
  int x;
  #pragma omp parallel for
  for (x = 0; x < width; x += 1)
  {
    helper_transform_to_coordfield_1(&width, &x, &x, &x, sdf, cf, height, ff, dd, zz, ww);
  }

  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    helper_transform_to_coordfield_2(&width, &y, sdf, cf, ff, dd, zz, ww);
  }

  free(ff);
  free(dd);
  free(zz);
  free(ww);
}


----------------------------
***/


