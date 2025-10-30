unsigned int randhash(unsigned int seed)
{
  unsigned int i = (seed ^ 12345391u) * 2654435769u;
  i ^= (i << 6) ^ (i >> 26);
  i *= 2654435769u;
  i += (i << 5) ^ (i >> 12);
  return i;
}


/*** DEPENDENCIES:
***/


heman_image *heman_points_create(float *xy, int npoints, int nbands)
{
  heman_points *img = malloc(sizeof(heman_image));
  img->width = npoints;
  img->height = 1;
  img->nbands = nbands;
  int nbytes = ((sizeof(float)) * npoints) * nbands;
  img->data = malloc(nbytes);
  memcpy(img->data, xy, nbytes);
  return img;
}


/*** DEPENDENCIES:
typedef struct heman_image_s heman_points
----------------------------
***/


void heman_points_destroy(heman_points *img)
{
  free(img->data);
  free(img);
}


/*** DEPENDENCIES:
typedef struct heman_image_s heman_points
----------------------------
***/


float randhashf(unsigned int seed, float a, float b)
{
  return (((b - a) * randhash(seed)) / ((float) 4294967295U)) + a;
}


/*** DEPENDENCIES:
unsigned int randhash(unsigned int seed)
{
  unsigned int i = (seed ^ 12345391u) * 2654435769u;
  i ^= (i << 6) ^ (i >> 26);
  i *= 2654435769u;
  i += (i << 5) ^ (i >> 12);
  return i;
}


----------------------------
***/


heman_points *heman_points_from_grid(float width, float height, float cellsize, float jitter)
{
  int cols = width / cellsize;
  int rows = height / cellsize;
  int ncells = cols * rows;
  heman_points *result = heman_image_create(ncells, 1, 2);
  float rscale = (2.0 * jitter) / ((float) 32767);
  int j;
  #pragma omp parallel for
  for (j = 0; j < rows; j += 1)
  {
    float *dst = result->data + ((j * cols) * 2);
    unsigned int dst_idx = 0;
    float y = (cellsize * 0.5) + (cellsize * j);
    float x = cellsize * 0.5;
    for (int i = 0; i < cols; i += 1)
    {
      float rx = (rand() * rscale) - jitter;
      float ry = (rand() * rscale) - jitter;
      dst[dst_idx] = x + rx;
      dst_idx += 1;
      dst[dst_idx] = y + ry;
      dst_idx += 1;
      x += cellsize;
    }

  }

  return result;
}


/*** DEPENDENCIES:
typedef struct heman_image_s heman_points
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


kmVec2 sample_annulus(float radius, kmVec2 center, unsigned int *seedptr)
{
  unsigned int seed = *seedptr;
  kmVec2 r;
  float rscale = 1.0f / 4294967295U;
  while (1)
  {
    r.x = ((4 * rscale) * randhash(seed)) - 2;
    seed += 1;
    r.y = ((4 * rscale) * randhash(seed)) - 2;
    seed += 1;
    float r2 = kmVec2LengthSq(&r);
    if ((r2 > 1) && (r2 <= 4))
    {
      break;
    }
  }

  *seedptr = seed;
  kmVec2Scale(&r, &r, radius);
  kmVec2Add(&r, &r, &center);
  return r;
}


/*** DEPENDENCIES:
unsigned int randhash(unsigned int seed)
{
  unsigned int i = (seed ^ 12345391u) * 2654435769u;
  i ^= (i << 6) ^ (i >> 26);
  i *= 2654435769u;
  i += (i << 5) ^ (i >> 12);
  return i;
}


----------------------------
kmVec2 *kmVec2Scale(kmVec2 *pOut, const kmVec2 *pIn, const float s)
{
  pOut->x = pIn->x * s;
  pOut->y = pIn->y * s;
  return pOut;
}


----------------------------
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
float kmVec2LengthSq(const kmVec2 *pIn)
{
  return kmSQR(pIn->x) + kmSQR(pIn->y);
}


----------------------------
kmVec2 *kmVec2Add(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2)
{
  pOut->x = pV1->x + pV2->x;
  pOut->y = pV1->y + pV2->y;
  return pOut;
}


----------------------------
***/


// hint:  ['pt_ref is a mutable refrence to kmVec2', 'found_ref is a mutable refrence to int', 'j_ref is a mutable refrence to kmVec2', 'minj_ref is a mutable refrence to kmVec2', 'maxj_ref is a mutable refrence to kmVec2']
void helper_helper_heman_points_from_poisson_1_1(kmVec2 * const pt_ref, int * const found_ref, kmVec2 * const j_ref, kmVec2 * const minj_ref, kmVec2 * const maxj_ref, float width, float height, float radius, unsigned int seed, kmVec2 rvec, float r2, int maxcol, int maxrow, int * const grid, kmVec2 * const samples, float invcell, int ncols, int sindex, kmVec2 delta)
{
  kmVec2 pt = *pt_ref;
  int found = *found_ref;
  kmVec2 j = *j_ref;
  kmVec2 minj = *minj_ref;
  kmVec2 maxj = *maxj_ref;
  pt = sample_annulus(radius, samples[sindex], &seed);
  if ((((pt.x < 0) || (pt.x >= width)) || (pt.y < 0)) || (pt.y >= height))
  {
    continue;
  }
  minj = (maxj = pt);
  kmVec2Add(&maxj, &maxj, &rvec);
  kmVec2Subtract(&minj, &minj, &rvec);
  kmVec2Scale(&minj, &minj, invcell);
  kmVec2Scale(&maxj, &maxj, invcell);
  minj.x = (0 > ((maxcol > ((int) minj.x)) ? ((int) minj.x) : (maxcol))) ? (0) : ((maxcol > ((int) minj.x)) ? ((int) minj.x) : (maxcol));
  maxj.x = (0 > ((maxcol > ((int) maxj.x)) ? ((int) maxj.x) : (maxcol))) ? (0) : ((maxcol > ((int) maxj.x)) ? ((int) maxj.x) : (maxcol));
  minj.y = (0 > ((maxrow > ((int) minj.y)) ? ((int) minj.y) : (maxrow))) ? (0) : ((maxrow > ((int) minj.y)) ? ((int) minj.y) : (maxrow));
  maxj.y = (0 > ((maxrow > ((int) maxj.y)) ? ((int) maxj.y) : (maxrow))) ? (0) : ((maxrow > ((int) maxj.y)) ? ((int) maxj.y) : (maxrow));
  int reject = 0;
  for (j.y = minj.y; (j.y <= maxj.y) && (!reject); j.y += 1)
  {
    for (j.x = minj.x; (j.x <= maxj.x) && (!reject); j.x += 1)
    {
      int entry = grid[(((int) j.y) * ncols) + ((int) j.x)];
      if ((entry > (-1)) && (entry != sindex))
      {
        kmVec2Subtract(&delta, &samples[entry], &pt);
        if (kmVec2LengthSq(&delta) < r2)
        {
          reject = 1;
        }
      }
    }

  }

  if (reject)
  {
    continue;
  }
  found = 1;
  *pt_ref = pt;
  *found_ref = found;
  *j_ref = j;
  *minj_ref = minj;
  *maxj_ref = maxj;
}


/*** DEPENDENCIES:
kmVec2 *kmVec2Subtract(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2)
{
  pOut->x = pV1->x - pV2->x;
  pOut->y = pV1->y - pV2->y;
  return pOut;
}


----------------------------
kmVec2 sample_annulus(float radius, kmVec2 center, unsigned int *seedptr)
{
  unsigned int seed = *seedptr;
  kmVec2 r;
  float rscale = 1.0f / 4294967295U;
  while (1)
  {
    r.x = ((4 * rscale) * randhash(seed)) - 2;
    seed += 1;
    r.y = ((4 * rscale) * randhash(seed)) - 2;
    seed += 1;
    float r2 = kmVec2LengthSq(&r);
    if ((r2 > 1) && (r2 <= 4))
    {
      break;
    }
  }

  *seedptr = seed;
  kmVec2Scale(&r, &r, radius);
  kmVec2Add(&r, &r, &center);
  return r;
}


----------------------------
kmVec2 *kmVec2Scale(kmVec2 *pOut, const kmVec2 *pIn, const float s)
{
  pOut->x = pIn->x * s;
  pOut->y = pIn->y * s;
  return pOut;
}


----------------------------
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
float kmVec2LengthSq(const kmVec2 *pIn)
{
  return kmSQR(pIn->x) + kmSQR(pIn->y);
}


----------------------------
kmVec2 *kmVec2Add(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2)
{
  pOut->x = pV1->x + pV2->x;
  pOut->y = pV1->y + pV2->y;
  return pOut;
}


----------------------------
***/


// hint:  ['invcell_ref is a mutable refrence to float', 'ncols_ref is a mutable refrence to int', 'nactives_ref is a mutable refrence to int', 'nsamples_ref is a mutable refrence to int', 'pt_ref is a mutable refrence to kmVec2']
void helper_heman_points_from_poisson_1(float * const invcell_ref, int * const ncols_ref, int * const nactives_ref, int * const nsamples_ref, kmVec2 * const pt_ref, float width, float height, float radius, int maxattempts, unsigned int seed, kmVec2 rvec, float r2, int maxcol, int maxrow, int * const grid, int * const actives, kmVec2 * const samples)
{
  float invcell = *invcell_ref;
  int ncols = *ncols_ref;
  int nactives = *nactives_ref;
  int nsamples = *nsamples_ref;
  kmVec2 pt = *pt_ref;
  int aindex = (randhashf(seed++, 0, nactives) > (nactives - 1)) ? (nactives - 1) : (randhashf(seed++, 0, nactives));
  int sindex = actives[aindex];
  int found = 0;
  kmVec2 j;
  kmVec2 minj;
  kmVec2 maxj;
  kmVec2 delta;
  int attempt;
  for (attempt = 0; (attempt < maxattempts) && (!found); attempt += 1)
  {
    helper_helper_heman_points_from_poisson_1_1(&pt, &found, &j, &minj, &maxj, width, height, radius, seed, rvec, r2, maxcol, maxrow, grid, samples, invcell, ncols, sindex, delta);
  }

  if (found)
  {
    grid[((int) (pt.x * invcell)) + (ncols * ((int) (pt.y * invcell)))] = (actives[nactives] = nsamples);
    nactives += 1;
    samples[nsamples++] = pt;
  }
  else
  {
    if ((--nactives) <= 0)
    {
      break;
    }
    actives[aindex] = actives[nactives];
  }
  *invcell_ref = invcell;
  *ncols_ref = ncols;
  *nactives_ref = nactives;
  *nsamples_ref = nsamples;
  *pt_ref = pt;
}


/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
void helper_helper_heman_points_from_poisson_1_1(kmVec2 * const pt_ref, int * const found_ref, kmVec2 * const j_ref, kmVec2 * const minj_ref, kmVec2 * const maxj_ref, float width, float height, float radius, unsigned int seed, kmVec2 rvec, float r2, int maxcol, int maxrow, int * const grid, kmVec2 * const samples, float invcell, int ncols, int sindex, kmVec2 delta)
{
  kmVec2 pt = *pt_ref;
  int found = *found_ref;
  kmVec2 j = *j_ref;
  kmVec2 minj = *minj_ref;
  kmVec2 maxj = *maxj_ref;
  pt = sample_annulus(radius, samples[sindex], &seed);
  if ((((pt.x < 0) || (pt.x >= width)) || (pt.y < 0)) || (pt.y >= height))
  {
    continue;
  }
  minj = (maxj = pt);
  kmVec2Add(&maxj, &maxj, &rvec);
  kmVec2Subtract(&minj, &minj, &rvec);
  kmVec2Scale(&minj, &minj, invcell);
  kmVec2Scale(&maxj, &maxj, invcell);
  minj.x = (0 > ((maxcol > ((int) minj.x)) ? ((int) minj.x) : (maxcol))) ? (0) : ((maxcol > ((int) minj.x)) ? ((int) minj.x) : (maxcol));
  maxj.x = (0 > ((maxcol > ((int) maxj.x)) ? ((int) maxj.x) : (maxcol))) ? (0) : ((maxcol > ((int) maxj.x)) ? ((int) maxj.x) : (maxcol));
  minj.y = (0 > ((maxrow > ((int) minj.y)) ? ((int) minj.y) : (maxrow))) ? (0) : ((maxrow > ((int) minj.y)) ? ((int) minj.y) : (maxrow));
  maxj.y = (0 > ((maxrow > ((int) maxj.y)) ? ((int) maxj.y) : (maxrow))) ? (0) : ((maxrow > ((int) maxj.y)) ? ((int) maxj.y) : (maxrow));
  int reject = 0;
  for (j.y = minj.y; (j.y <= maxj.y) && (!reject); j.y += 1)
  {
    for (j.x = minj.x; (j.x <= maxj.x) && (!reject); j.x += 1)
    {
      int entry = grid[(((int) j.y) * ncols) + ((int) j.x)];
      if ((entry > (-1)) && (entry != sindex))
      {
        kmVec2Subtract(&delta, &samples[entry], &pt);
        if (kmVec2LengthSq(&delta) < r2)
        {
          reject = 1;
        }
      }
    }

  }

  if (reject)
  {
    continue;
  }
  found = 1;
  *pt_ref = pt;
  *found_ref = found;
  *j_ref = j;
  *minj_ref = minj;
  *maxj_ref = maxj;
}


----------------------------
float randhashf(unsigned int seed, float a, float b)
{
  return (((b - a) * randhash(seed)) / ((float) 4294967295U)) + a;
}


----------------------------
***/


// hint:  ['pt_ref is a mutable refrence to kmVec2', 'found_ref is a mutable refrence to int', 'j_ref is a mutable refrence to kmVec2', 'minj_ref is a mutable refrence to kmVec2', 'maxj_ref is a mutable refrence to kmVec2']
void helper_helper_heman_points_from_density_1_1(kmVec2 * const pt_ref, int * const found_ref, kmVec2 * const j_ref, kmVec2 * const minj_ref, kmVec2 * const maxj_ref, heman_image * const density, float minradius, float maxradius, float width, float height, unsigned int seed, kmVec2 rvec, float invcell, int ncols, int maxcol, int maxrow, int * const grid, int * const ngrid, kmVec2 * const samples, int gcapacity, int sindex, kmVec2 delta)
{
  kmVec2 pt = *pt_ref;
  int found = *found_ref;
  kmVec2 j = *j_ref;
  kmVec2 minj = *minj_ref;
  kmVec2 maxj = *maxj_ref;
  pt = sample_annulus(maxradius, samples[sindex], &seed);
  if ((((pt.x < 0) || (pt.x >= width)) || (pt.y < 0)) || (pt.y >= height))
  {
    continue;
  }
  minj = (maxj = pt);
  kmVec2Add(&maxj, &maxj, &rvec);
  kmVec2Subtract(&minj, &minj, &rvec);
  kmVec2Scale(&minj, &minj, invcell);
  kmVec2Scale(&maxj, &maxj, invcell);
  minj.x = (0 > ((maxcol > ((int) minj.x)) ? ((int) minj.x) : (maxcol))) ? (0) : ((maxcol > ((int) minj.x)) ? ((int) minj.x) : (maxcol));
  maxj.x = (0 > ((maxcol > ((int) maxj.x)) ? ((int) maxj.x) : (maxcol))) ? (0) : ((maxcol > ((int) maxj.x)) ? ((int) maxj.x) : (maxcol));
  minj.y = (0 > ((maxrow > ((int) minj.y)) ? ((int) minj.y) : (maxrow))) ? (0) : ((maxrow > ((int) minj.y)) ? ((int) minj.y) : (maxrow));
  maxj.y = (0 > ((maxrow > ((int) maxj.y)) ? ((int) maxj.y) : (maxrow))) ? (0) : ((maxrow > ((int) maxj.y)) ? ((int) maxj.y) : (maxrow));
  int reject = 0;
  float densityval;
  heman_image_sample(density, pt.x, pt.y, &densityval);
  densityval = sqrt(densityval);
  float mindist = maxradius - (densityval * (maxradius - minradius));
  float r2 = mindist * mindist;
  for (j.y = minj.y; (j.y <= maxj.y) && (!reject); j.y += 1)
  {
    for (j.x = minj.x; (j.x <= maxj.x) && (!reject); j.x += 1)
    {
      for (int g = ((((int) j.y) * ncols) + ((int) j.x)) * gcapacity; g < ((((((int) j.y) * ncols) + ((int) j.x)) * gcapacity) + ngrid[(((int) j.y) * ncols) + ((int) j.x)]); g += 1)
      {
        int entry = grid[g];
        if (entry != sindex)
        {
          kmVec2Subtract(&delta, &samples[entry], &pt);
          if (kmVec2LengthSq(&delta) < r2)
          {
            reject = 1;
          }
        }
      }

    }

  }

  if (reject)
  {
    continue;
  }
  found = 1;
  *pt_ref = pt;
  *found_ref = found;
  *j_ref = j;
  *minj_ref = minj;
  *maxj_ref = maxj;
}


/*** DEPENDENCIES:
kmVec2 *kmVec2Subtract(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2)
{
  pOut->x = pV1->x - pV2->x;
  pOut->y = pV1->y - pV2->y;
  return pOut;
}


----------------------------
kmVec2 sample_annulus(float radius, kmVec2 center, unsigned int *seedptr)
{
  unsigned int seed = *seedptr;
  kmVec2 r;
  float rscale = 1.0f / 4294967295U;
  while (1)
  {
    r.x = ((4 * rscale) * randhash(seed)) - 2;
    seed += 1;
    r.y = ((4 * rscale) * randhash(seed)) - 2;
    seed += 1;
    float r2 = kmVec2LengthSq(&r);
    if ((r2 > 1) && (r2 <= 4))
    {
      break;
    }
  }

  *seedptr = seed;
  kmVec2Scale(&r, &r, radius);
  kmVec2Add(&r, &r, &center);
  return r;
}


----------------------------
typedef struct heman_image_s heman_image
----------------------------
kmVec2 *kmVec2Scale(kmVec2 *pOut, const kmVec2 *pIn, const float s)
{
  pOut->x = pIn->x * s;
  pOut->y = pIn->y * s;
  return pOut;
}


----------------------------
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
float kmVec2LengthSq(const kmVec2 *pIn)
{
  return kmSQR(pIn->x) + kmSQR(pIn->y);
}


----------------------------
kmVec2 *kmVec2Add(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2)
{
  pOut->x = pV1->x + pV2->x;
  pOut->y = pV1->y + pV2->y;
  return pOut;
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


// hint:  ['gindex_ref is a mutable refrence to int', 'gcapacity_ref is a mutable refrence to int', 'nactives_ref is a mutable refrence to int', 'nsamples_ref is a mutable refrence to int', 'pt_ref is a mutable refrence to kmVec2']
void helper_heman_points_from_density_1(int * const gindex_ref, int * const gcapacity_ref, int * const nactives_ref, int * const nsamples_ref, kmVec2 * const pt_ref, heman_image * const density, float minradius, float maxradius, float width, float height, int maxattempts, unsigned int seed, kmVec2 rvec, float invcell, int ncols, int maxcol, int maxrow, int * const grid, int * const ngrid, int * const actives, kmVec2 * const samples)
{
  int gindex = *gindex_ref;
  int gcapacity = *gcapacity_ref;
  int nactives = *nactives_ref;
  int nsamples = *nsamples_ref;
  kmVec2 pt = *pt_ref;
  int aindex = (randhashf(seed++, 0, nactives) > (nactives - 1)) ? (nactives - 1) : (randhashf(seed++, 0, nactives));
  int sindex = actives[aindex];
  int found = 0;
  kmVec2 j;
  kmVec2 minj;
  kmVec2 maxj;
  kmVec2 delta;
  int attempt;
  for (attempt = 0; (attempt < maxattempts) && (!found); attempt += 1)
  {
    helper_helper_heman_points_from_density_1_1(&pt, &found, &j, &minj, &maxj, density, minradius, maxradius, width, height, seed, rvec, invcell, ncols, maxcol, maxrow, grid, ngrid, samples, gcapacity, sindex, delta);
  }

  if (found && (ngrid[((int) (pt.x * invcell)) + (ncols * ((int) (pt.y * invcell)))] >= gcapacity))
  {
    found = 0;
  }
  if (found)
  {
    actives[nactives] = nsamples;
    nactives += 1;
    gindex = ((int) (pt.x * invcell)) + (ncols * ((int) (pt.y * invcell)));
    grid[(gcapacity * gindex) + ngrid[gindex]] = nsamples;
    ngrid[gindex] += 1;
    samples[nsamples++] = pt;
  }
  else
  {
    if ((--nactives) <= 0)
    {
      break;
    }
    actives[aindex] = actives[nactives];
  }
  *gindex_ref = gindex;
  *gcapacity_ref = gcapacity;
  *nactives_ref = nactives;
  *nsamples_ref = nsamples;
  *pt_ref = pt;
}


/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
void helper_helper_heman_points_from_density_1_1(kmVec2 * const pt_ref, int * const found_ref, kmVec2 * const j_ref, kmVec2 * const minj_ref, kmVec2 * const maxj_ref, heman_image * const density, float minradius, float maxradius, float width, float height, unsigned int seed, kmVec2 rvec, float invcell, int ncols, int maxcol, int maxrow, int * const grid, int * const ngrid, kmVec2 * const samples, int gcapacity, int sindex, kmVec2 delta)
{
  kmVec2 pt = *pt_ref;
  int found = *found_ref;
  kmVec2 j = *j_ref;
  kmVec2 minj = *minj_ref;
  kmVec2 maxj = *maxj_ref;
  pt = sample_annulus(maxradius, samples[sindex], &seed);
  if ((((pt.x < 0) || (pt.x >= width)) || (pt.y < 0)) || (pt.y >= height))
  {
    continue;
  }
  minj = (maxj = pt);
  kmVec2Add(&maxj, &maxj, &rvec);
  kmVec2Subtract(&minj, &minj, &rvec);
  kmVec2Scale(&minj, &minj, invcell);
  kmVec2Scale(&maxj, &maxj, invcell);
  minj.x = (0 > ((maxcol > ((int) minj.x)) ? ((int) minj.x) : (maxcol))) ? (0) : ((maxcol > ((int) minj.x)) ? ((int) minj.x) : (maxcol));
  maxj.x = (0 > ((maxcol > ((int) maxj.x)) ? ((int) maxj.x) : (maxcol))) ? (0) : ((maxcol > ((int) maxj.x)) ? ((int) maxj.x) : (maxcol));
  minj.y = (0 > ((maxrow > ((int) minj.y)) ? ((int) minj.y) : (maxrow))) ? (0) : ((maxrow > ((int) minj.y)) ? ((int) minj.y) : (maxrow));
  maxj.y = (0 > ((maxrow > ((int) maxj.y)) ? ((int) maxj.y) : (maxrow))) ? (0) : ((maxrow > ((int) maxj.y)) ? ((int) maxj.y) : (maxrow));
  int reject = 0;
  float densityval;
  heman_image_sample(density, pt.x, pt.y, &densityval);
  densityval = sqrt(densityval);
  float mindist = maxradius - (densityval * (maxradius - minradius));
  float r2 = mindist * mindist;
  for (j.y = minj.y; (j.y <= maxj.y) && (!reject); j.y += 1)
  {
    for (j.x = minj.x; (j.x <= maxj.x) && (!reject); j.x += 1)
    {
      for (int g = ((((int) j.y) * ncols) + ((int) j.x)) * gcapacity; g < ((((((int) j.y) * ncols) + ((int) j.x)) * gcapacity) + ngrid[(((int) j.y) * ncols) + ((int) j.x)]); g += 1)
      {
        int entry = grid[g];
        if (entry != sindex)
        {
          kmVec2Subtract(&delta, &samples[entry], &pt);
          if (kmVec2LengthSq(&delta) < r2)
          {
            reject = 1;
          }
        }
      }

    }

  }

  if (reject)
  {
    continue;
  }
  found = 1;
  *pt_ref = pt;
  *found_ref = found;
  *j_ref = j;
  *minj_ref = minj;
  *maxj_ref = maxj;
}


----------------------------
float randhashf(unsigned int seed, float a, float b)
{
  return (((b - a) * randhash(seed)) / ((float) 4294967295U)) + a;
}


----------------------------
typedef struct heman_image_s heman_image
----------------------------
***/


heman_points *heman_points_from_poisson(float width, float height, float radius)
{
  int maxattempts = 30;
  float rscale = 1.0f / 4294967295U;
  unsigned int seed = 0;
  kmVec2 rvec;
  rvec.x = (rvec.y = radius);
  float r2 = radius * radius;
  float cellsize = radius / sqrtf(2);
  float invcell = 1.0f / cellsize;
  int ncols = ceil(width * invcell);
  int nrows = ceil(height * invcell);
  int maxcol = ncols - 1;
  int maxrow = nrows - 1;
  int ncells = ncols * nrows;
  int *grid = malloc(ncells * (sizeof(int)));
  for (int i = 0; i < ncells; i += 1)
  {
    grid[i] = -1;
  }

  int *actives = malloc(ncells * (sizeof(int)));
  int nactives = 0;
  heman_points *result = heman_image_create(ncells, 1, 2);
  kmVec2 *samples = (kmVec2 *) result->data;
  int nsamples = 0;
  kmVec2 pt;
  pt.x = (width * randhash(seed)) * rscale;
  seed += 1;
  pt.y = (height * randhash(seed)) * rscale;
  seed += 1;
  grid[((int) (pt.x * invcell)) + (ncols * ((int) (pt.y * invcell)))] = (actives[nactives] = nsamples);
  nactives += 1;
  samples[nsamples] = pt;
  nsamples += 1;
  while (nsamples < ncells)
  {
    helper_heman_points_from_poisson_1(&invcell, &ncols, &nactives, &nsamples, &pt, width, height, radius, maxattempts, seed, rvec, r2, maxcol, maxrow, grid, actives, samples);
  }

  result->width = nsamples;
  free(grid);
  free(actives);
  return result;
}


/*** DEPENDENCIES:
typedef struct heman_image_s heman_points
----------------------------
unsigned int randhash(unsigned int seed)
{
  unsigned int i = (seed ^ 12345391u) * 2654435769u;
  i ^= (i << 6) ^ (i >> 26);
  i *= 2654435769u;
  i += (i << 5) ^ (i >> 12);
  return i;
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
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
void helper_heman_points_from_poisson_1(float * const invcell_ref, int * const ncols_ref, int * const nactives_ref, int * const nsamples_ref, kmVec2 * const pt_ref, float width, float height, float radius, int maxattempts, unsigned int seed, kmVec2 rvec, float r2, int maxcol, int maxrow, int * const grid, int * const actives, kmVec2 * const samples)
{
  float invcell = *invcell_ref;
  int ncols = *ncols_ref;
  int nactives = *nactives_ref;
  int nsamples = *nsamples_ref;
  kmVec2 pt = *pt_ref;
  int aindex = (randhashf(seed++, 0, nactives) > (nactives - 1)) ? (nactives - 1) : (randhashf(seed++, 0, nactives));
  int sindex = actives[aindex];
  int found = 0;
  kmVec2 j;
  kmVec2 minj;
  kmVec2 maxj;
  kmVec2 delta;
  int attempt;
  for (attempt = 0; (attempt < maxattempts) && (!found); attempt += 1)
  {
    helper_helper_heman_points_from_poisson_1_1(&pt, &found, &j, &minj, &maxj, width, height, radius, seed, rvec, r2, maxcol, maxrow, grid, samples, invcell, ncols, sindex, delta);
  }

  if (found)
  {
    grid[((int) (pt.x * invcell)) + (ncols * ((int) (pt.y * invcell)))] = (actives[nactives] = nsamples);
    nactives += 1;
    samples[nsamples++] = pt;
  }
  else
  {
    if ((--nactives) <= 0)
    {
      break;
    }
    actives[aindex] = actives[nactives];
  }
  *invcell_ref = invcell;
  *ncols_ref = ncols;
  *nactives_ref = nactives;
  *nsamples_ref = nsamples;
  *pt_ref = pt;
}


----------------------------
***/


heman_points *heman_points_from_density(heman_image *density, float minradius, float maxradius)
{
  assert(density->nbands == 1);
  float width = 1;
  float height = 1;
  int maxattempts = 30;
  float rscale = 1.0f / 4294967295U;
  unsigned int seed = 0;
  kmVec2 rvec;
  rvec.x = (rvec.y = maxradius);
  int gindex;
  float cellsize = maxradius / sqrtf(2);
  float invcell = 1.0f / cellsize;
  int ncols = ceil(width * invcell);
  int nrows = ceil(height * invcell);
  int maxcol = ncols - 1;
  int maxrow = nrows - 1;
  int ncells = ncols * nrows;
  int ntexels = cellsize * density->width;
  int gcapacity = ntexels * ntexels;
  int *grid = malloc((ncells * (sizeof(int))) * gcapacity);
  int *ngrid = malloc(ncells * (sizeof(int)));
  for (int i = 0; i < ncells; i += 1)
  {
    ngrid[i] = 0;
  }

  int *actives = malloc(ncells * (sizeof(int)));
  int nactives = 0;
  int maxsamples = ncells * gcapacity;
  heman_points *result = heman_image_create(maxsamples, 1, 2);
  kmVec2 *samples = (kmVec2 *) result->data;
  int nsamples = 0;
  kmVec2 pt;
  pt.x = (width * randhash(seed)) * rscale;
  seed += 1;
  pt.y = (height * randhash(seed)) * rscale;
  seed += 1;
  actives[nactives] = nsamples;
  nactives += 1;
  gindex = ((int) (pt.x * invcell)) + (ncols * ((int) (pt.y * invcell)));
  grid[(gcapacity * gindex) + ngrid[gindex]] = nsamples;
  ngrid[gindex] += 1;
  samples[nsamples] = pt;
  nsamples += 1;
  while (nsamples < maxsamples)
  {
    helper_heman_points_from_density_1(&gindex, &gcapacity, &nactives, &nsamples, &pt, density, minradius, maxradius, width, height, maxattempts, seed, rvec, invcell, ncols, maxcol, maxrow, grid, ngrid, actives, samples);
  }

  result->width = nsamples;
  free(grid);
  free(ngrid);
  free(actives);
  return result;
}


/*** DEPENDENCIES:
typedef struct heman_image_s heman_points
----------------------------
unsigned int randhash(unsigned int seed)
{
  unsigned int i = (seed ^ 12345391u) * 2654435769u;
  i ^= (i << 6) ^ (i >> 26);
  i *= 2654435769u;
  i += (i << 5) ^ (i >> 12);
  return i;
}


----------------------------
typedef struct heman_image_s heman_image
----------------------------
void helper_heman_points_from_density_1(int * const gindex_ref, int * const gcapacity_ref, int * const nactives_ref, int * const nsamples_ref, kmVec2 * const pt_ref, heman_image * const density, float minradius, float maxradius, float width, float height, int maxattempts, unsigned int seed, kmVec2 rvec, float invcell, int ncols, int maxcol, int maxrow, int * const grid, int * const ngrid, int * const actives, kmVec2 * const samples)
{
  int gindex = *gindex_ref;
  int gcapacity = *gcapacity_ref;
  int nactives = *nactives_ref;
  int nsamples = *nsamples_ref;
  kmVec2 pt = *pt_ref;
  int aindex = (randhashf(seed++, 0, nactives) > (nactives - 1)) ? (nactives - 1) : (randhashf(seed++, 0, nactives));
  int sindex = actives[aindex];
  int found = 0;
  kmVec2 j;
  kmVec2 minj;
  kmVec2 maxj;
  kmVec2 delta;
  int attempt;
  for (attempt = 0; (attempt < maxattempts) && (!found); attempt += 1)
  {
    helper_helper_heman_points_from_density_1_1(&pt, &found, &j, &minj, &maxj, density, minradius, maxradius, width, height, seed, rvec, invcell, ncols, maxcol, maxrow, grid, ngrid, samples, gcapacity, sindex, delta);
  }

  if (found && (ngrid[((int) (pt.x * invcell)) + (ncols * ((int) (pt.y * invcell)))] >= gcapacity))
  {
    found = 0;
  }
  if (found)
  {
    actives[nactives] = nsamples;
    nactives += 1;
    gindex = ((int) (pt.x * invcell)) + (ncols * ((int) (pt.y * invcell)));
    grid[(gcapacity * gindex) + ngrid[gindex]] = nsamples;
    ngrid[gindex] += 1;
    samples[nsamples++] = pt;
  }
  else
  {
    if ((--nactives) <= 0)
    {
      break;
    }
    actives[aindex] = actives[nactives];
  }
  *gindex_ref = gindex;
  *gcapacity_ref = gcapacity;
  *nactives_ref = nactives;
  *nsamples_ref = nsamples;
  *pt_ref = pt;
}


----------------------------
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
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


