void heman_lighting_set_occlusion_scale(float s)
{
  _occlusion_scale = s;
}


/*** DEPENDENCIES:
static float _occlusion_scale = 1.0f
----------------------------
***/


static float azimuth_slope(kmVec3 a, kmVec3 b)
{
  kmVec3 d;
  kmVec3Subtract(&d, &a, &b);
  float x = kmVec3Length(&d);
  float y = b.z - a.z;
  return y / x;
}


/*** DEPENDENCIES:
float kmVec3Length(const kmVec3 *pIn)
{
  return sqrtf((kmSQR(pIn->x) + kmSQR(pIn->y)) + kmSQR(pIn->z));
}


----------------------------
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
kmVec3 *kmVec3Subtract(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2)
{
  kmVec3 v;
  v.x = pV1->x - pV2->x;
  v.y = pV1->y - pV2->y;
  v.z = pV1->z - pV2->z;
  pOut->x = v.x;
  pOut->y = v.y;
  pOut->z = v.z;
  return pOut;
}


----------------------------
***/


// hint:  ['y_ref is a mutable refrence to int']
void helper_heman_lighting_compute_normals_1(int * const y_ref, heman_image * const heightmap, int width, float invh, float invw, int maxx, int maxy, kmVec3 * const normals)
{
  int y = *y_ref;
  float v = y * invh;
  int y1 = ((y + 1) > maxy) ? (maxy) : (y + 1);
  kmVec3 p;
  kmVec3 px;
  kmVec3 py;
  kmVec3 *n = normals + (y * width);
  unsigned int n_idx = 0;
  for (int x = 0; x < width; x += 1, n_idx += 1)
  {
    float u = x * invw;
    int x1 = ((x + 1) > maxx) ? (maxx) : (x + 1);
    p.x = u;
    p.y = v;
    p.z = *heman_image_texel(heightmap, x, y);
    px.x = u + invw;
    px.y = v;
    px.z = *heman_image_texel(heightmap, x1, y);
    py.x = u;
    py.y = v + invh;
    py.z = *heman_image_texel(heightmap, x, y1);
    kmVec3Subtract(&px, &px, &p);
    kmVec3Subtract(&py, &py, &p);
    kmVec3Cross(n, &px, &py);
    kmVec3Normalize(n, n);
    n->y *= -1;
  }

  *y_ref = y;
}


/*** DEPENDENCIES:
kmVec3 *kmVec3Normalize(kmVec3 *pOut, const kmVec3 *pIn)
{
  if (((!pIn->x) && (!pIn->y)) && (!pIn->z))
  {
    return kmVec3Assign(pOut, pIn);
  }
  float l = 1.0f / kmVec3Length(pIn);
  kmVec3 v;
  v.x = pIn->x * l;
  v.y = pIn->y * l;
  v.z = pIn->z * l;
  pOut->x = v.x;
  pOut->y = v.y;
  pOut->z = v.z;
  return pOut;
}


----------------------------
typedef struct heman_image_s heman_image
----------------------------
kmVec3 *kmVec3Cross(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2)
{
  kmVec3 v;
  v.x = (pV1->y * pV2->z) - (pV1->z * pV2->y);
  v.y = (pV1->z * pV2->x) - (pV1->x * pV2->z);
  v.z = (pV1->x * pV2->y) - (pV1->y * pV2->x);
  pOut->x = v.x;
  pOut->y = v.y;
  pOut->z = v.z;
  return pOut;
}


----------------------------
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
float *heman_image_texel(heman_image *img, int x, int y)
{
  return (img->data + ((y * img->width) * img->nbands)) + (x * img->nbands);
}


----------------------------
kmVec3 *kmVec3Subtract(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2)
{
  kmVec3 v;
  v.x = pV1->x - pV2->x;
  v.y = pV1->y - pV2->y;
  v.z = pV1->z - pV2->z;
  pOut->x = v.x;
  pOut->y = v.y;
  pOut->z = v.z;
  return pOut;
}


----------------------------
***/


heman_image *heman_lighting_compute_normals(heman_image *heightmap)
{
  assert(heightmap->nbands == 1);
  int width = heightmap->width;
  int height = heightmap->height;
  heman_image *result = heman_image_create(width, height, 3);
  float invh = 1.0f / height;
  float invw = 1.0f / width;
  int maxx = width - 1;
  int maxy = height - 1;
  kmVec3 *normals = (kmVec3 *) result->data;
  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    helper_heman_lighting_compute_normals_1(&y, heightmap, width, invh, invw, maxx, maxy, normals);
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
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
void helper_heman_lighting_compute_normals_1(int * const y_ref, heman_image * const heightmap, int width, float invh, float invw, int maxx, int maxy, kmVec3 * const normals)
{
  int y = *y_ref;
  float v = y * invh;
  int y1 = ((y + 1) > maxy) ? (maxy) : (y + 1);
  kmVec3 p;
  kmVec3 px;
  kmVec3 py;
  kmVec3 *n = normals + (y * width);
  unsigned int n_idx = 0;
  for (int x = 0; x < width; x += 1, n_idx += 1)
  {
    float u = x * invw;
    int x1 = ((x + 1) > maxx) ? (maxx) : (x + 1);
    p.x = u;
    p.y = v;
    p.z = *heman_image_texel(heightmap, x, y);
    px.x = u + invw;
    px.y = v;
    px.z = *heman_image_texel(heightmap, x1, y);
    py.x = u;
    py.y = v + invh;
    py.z = *heman_image_texel(heightmap, x, y1);
    kmVec3Subtract(&px, &px, &p);
    kmVec3Subtract(&py, &py, &p);
    kmVec3Cross(n, &px, &py);
    kmVec3Normalize(n, n);
    n->y *= -1;
  }

  *y_ref = y;
}


----------------------------
typedef struct heman_image_s heman_image
----------------------------
***/


static float compute_occlusion(kmVec3 thispt, kmVec3 horizonpt)
{
  kmVec3 direction;
  kmVec3Subtract(&direction, &horizonpt, &thispt);
  kmVec3Normalize(&direction, &direction);
  float dot = kmVec3Dot(&direction, &KM_VEC3_POS_Z);
  return atan((dot > 0.0f) ? (dot) : (0.0f)) * 0.63661977236;
}


/*** DEPENDENCIES:
kmVec3 *kmVec3Normalize(kmVec3 *pOut, const kmVec3 *pIn)
{
  if (((!pIn->x) && (!pIn->y)) && (!pIn->z))
  {
    return kmVec3Assign(pOut, pIn);
  }
  float l = 1.0f / kmVec3Length(pIn);
  kmVec3 v;
  v.x = pIn->x * l;
  v.y = pIn->y * l;
  v.z = pIn->z * l;
  pOut->x = v.x;
  pOut->y = v.y;
  pOut->z = v.z;
  return pOut;
}


----------------------------
extern const kmVec3 KM_VEC3_POS_Z
----------------------------
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
float kmVec3Dot(const kmVec3 *pV1, const kmVec3 *pV2)
{
  return ((pV1->x * pV2->x) + (pV1->y * pV2->y)) + (pV1->z * pV2->z);
}


----------------------------
kmVec3 *kmVec3Subtract(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2)
{
  kmVec3 v;
  v.x = pV1->x - pV2->x;
  v.y = pV1->y - pV2->y;
  v.z = pV1->z - pV2->z;
  pOut->x = v.x;
  pOut->y = v.y;
  pOut->z = v.z;
  return pOut;
}


----------------------------
***/


// hint:  ['i_ref is a mutable refrence to int', 'j_ref is a mutable refrence to int', 'thispt_ref is a mutable refrence to kmVec3', 'horizonpt_ref is a mutable refrence to kmVec3', 'stack_top_ref is a mutable refrence to int']
void helper_helper_horizon_scan_1_1(int * const i_ref, int * const j_ref, kmVec3 * const thispt_ref, kmVec3 * const horizonpt_ref, int * const stack_top_ref, heman_image * const heightmap, heman_image * const result, int dx, int dy, int pathlen, float cellw, float cellh, kmVec3 * const convex_hull)
{
  int i = *i_ref;
  int j = *j_ref;
  kmVec3 thispt = *thispt_ref;
  kmVec3 horizonpt = *horizonpt_ref;
  int stack_top = *stack_top_ref;
  thispt.x = i * cellw;
  thispt.y = j * cellh;
  thispt.z = *heman_image_texel(heightmap, i, j);
  while (stack_top > 0)
  {
    float s1 = azimuth_slope(thispt, convex_hull[stack_top]);
    float s2 = azimuth_slope(thispt, convex_hull[stack_top - 1]);
    if (s1 >= s2)
    {
      break;
    }
    stack_top -= 1;
  }

  horizonpt = convex_hull[stack_top];
  stack_top += 1;
  assert(stack_top < pathlen);
  convex_hull[stack_top] = thispt;
  float occlusion = compute_occlusion(thispt, horizonpt);
  *heman_image_texel(result, i, j) += (1.0f / 16.0f) * occlusion;
  i += dx;
  j += dy;
  *i_ref = i;
  *j_ref = j;
  *thispt_ref = thispt;
  *horizonpt_ref = horizonpt;
  *stack_top_ref = stack_top;
}


/*** DEPENDENCIES:
typedef struct heman_image_s heman_image
----------------------------
static float azimuth_slope(kmVec3 a, kmVec3 b)
{
  kmVec3 d;
  kmVec3Subtract(&d, &a, &b);
  float x = kmVec3Length(&d);
  float y = b.z - a.z;
  return y / x;
}


----------------------------
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
float *heman_image_texel(heman_image *img, int x, int y)
{
  return (img->data + ((y * img->width) * img->nbands)) + (x * img->nbands);
}


----------------------------
static float compute_occlusion(kmVec3 thispt, kmVec3 horizonpt)
{
  kmVec3 direction;
  kmVec3Subtract(&direction, &horizonpt, &thispt);
  kmVec3Normalize(&direction, &direction);
  float dot = kmVec3Dot(&direction, &KM_VEC3_POS_Z);
  return atan((dot > 0.0f) ? (dot) : (0.0f)) * 0.63661977236;
}


----------------------------
***/


void helper_horizon_scan_1(heman_image * const heightmap, heman_image * const result, int * const startpts, int dx, int dy, int w, int h, int pathlen, float cellw, float cellh, kmVec3 * const hull_buffer, int sweep)
{
  kmVec3 *convex_hull = hull_buffer + (sweep * pathlen);
  int *p = startpts + (sweep * 2);
  unsigned int p_idx = 0;
  int i = p[0 + p_idx];
  int j = p[1 + p_idx];
  kmVec3 thispt;
  kmVec3 horizonpt;
  thispt.x = i * cellw;
  thispt.y = j * cellh;
  thispt.z = *heman_image_texel(heightmap, (0 > (((w - 1) > i) ? (i) : (w - 1))) ? (0) : (((w - 1) > i) ? (i) : (w - 1)), (0 > (((h - 1) > j) ? (j) : (h - 1))) ? (0) : (((h - 1) > j) ? (j) : (h - 1)));
  int stack_top = 0;
  convex_hull[0] = thispt;
  i += dx, j += dy;
  while ((((i >= 0) && (i < w)) && (j >= 0)) && (j < h))
  {
    helper_helper_horizon_scan_1_1(&i, &j, &thispt, &horizonpt, &stack_top, heightmap, result, dx, dy, pathlen, cellw, cellh, convex_hull);
  }

}


/*** DEPENDENCIES:
typedef struct heman_image_s heman_image
----------------------------
void helper_helper_horizon_scan_1_1(int * const i_ref, int * const j_ref, kmVec3 * const thispt_ref, kmVec3 * const horizonpt_ref, int * const stack_top_ref, heman_image * const heightmap, heman_image * const result, int dx, int dy, int pathlen, float cellw, float cellh, kmVec3 * const convex_hull)
{
  int i = *i_ref;
  int j = *j_ref;
  kmVec3 thispt = *thispt_ref;
  kmVec3 horizonpt = *horizonpt_ref;
  int stack_top = *stack_top_ref;
  thispt.x = i * cellw;
  thispt.y = j * cellh;
  thispt.z = *heman_image_texel(heightmap, i, j);
  while (stack_top > 0)
  {
    float s1 = azimuth_slope(thispt, convex_hull[stack_top]);
    float s2 = azimuth_slope(thispt, convex_hull[stack_top - 1]);
    if (s1 >= s2)
    {
      break;
    }
    stack_top -= 1;
  }

  horizonpt = convex_hull[stack_top];
  stack_top += 1;
  assert(stack_top < pathlen);
  convex_hull[stack_top] = thispt;
  float occlusion = compute_occlusion(thispt, horizonpt);
  *heman_image_texel(result, i, j) += (1.0f / 16.0f) * occlusion;
  i += dx;
  j += dy;
  *i_ref = i;
  *j_ref = j;
  *thispt_ref = thispt;
  *horizonpt_ref = horizonpt;
  *stack_top_ref = stack_top;
}


----------------------------
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
float *heman_image_texel(heman_image *img, int x, int y)
{
  return (img->data + ((y * img->width) * img->nbands)) + (x * img->nbands);
}


----------------------------
***/


static void horizon_scan(heman_image *heightmap, heman_image *result, int *startpts, int dx, int dy)
{
  int w = heightmap->width;
  int h = heightmap->height;
  int sx = (dx > 0) - (dx < 0);
  int sy = (dy > 0) - (dy < 0);
  int ax = abs(dx);
  int ay = abs(dy);
  int nsweeps = ((ay * w) + (ax * h)) - ((ax + ay) - 1);
  int *p = startpts;
  unsigned int p_idx = 0;
  for (int x = -ax; x < (w - ax); x += 1)
  {
    for (int y = -ay; y < (h - ay); y += 1)
    {
      if ((((x >= 0) && (x < w)) && (y >= 0)) && (y < h))
      {
        continue;
      }
      p[p_idx] = (sx < 0) ? ((w - x) - 1) : (x);
      p_idx += 1;
      *((&p[p_idx])++) = (sy < 0) ? ((h - y) - 1) : (y);
    }

  }

  assert(nsweeps == (((&p[p_idx]) - startpts) / 2));
  int pathlen = 0;
  int i = startpts[0];
  int j = startpts[1];
  do
  {
    i += dx;
    j += dy;
    pathlen += 1;
  }
  while ((((i >= 0) && (i < w)) && (j >= 0)) && (j < h));
  float cellw = _occlusion_scale / ((w > h) ? (w) : (h));
  float cellh = _occlusion_scale / ((w > h) ? (w) : (h));
  kmVec3 *hull_buffer = malloc(((sizeof(kmVec3)) * pathlen) * nsweeps);
  int sweep;
  #pragma omp parallel for
  for (sweep = 0; sweep < nsweeps; sweep += 1)
  {
    helper_horizon_scan_1(heightmap, result, startpts, dx, dy, w, h, pathlen, cellw, cellh, hull_buffer, sweep);
  }

  free(hull_buffer);
}


/*** DEPENDENCIES:
static float _occlusion_scale = 1.0f
----------------------------
void helper_horizon_scan_1(heman_image * const heightmap, heman_image * const result, int * const startpts, int dx, int dy, int w, int h, int pathlen, float cellw, float cellh, kmVec3 * const hull_buffer, int sweep)
{
  kmVec3 *convex_hull = hull_buffer + (sweep * pathlen);
  int *p = startpts + (sweep * 2);
  unsigned int p_idx = 0;
  int i = p[0 + p_idx];
  int j = p[1 + p_idx];
  kmVec3 thispt;
  kmVec3 horizonpt;
  thispt.x = i * cellw;
  thispt.y = j * cellh;
  thispt.z = *heman_image_texel(heightmap, (0 > (((w - 1) > i) ? (i) : (w - 1))) ? (0) : (((w - 1) > i) ? (i) : (w - 1)), (0 > (((h - 1) > j) ? (j) : (h - 1))) ? (0) : (((h - 1) > j) ? (j) : (h - 1)));
  int stack_top = 0;
  convex_hull[0] = thispt;
  i += dx, j += dy;
  while ((((i >= 0) && (i < w)) && (j >= 0)) && (j < h))
  {
    helper_helper_horizon_scan_1_1(&i, &j, &thispt, &horizonpt, &stack_top, heightmap, result, dx, dy, pathlen, cellw, cellh, convex_hull);
  }

}


----------------------------
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
typedef struct heman_image_s heman_image
----------------------------
***/


heman_image *heman_lighting_compute_occlusion(heman_image *heightmap)
{
  assert(heightmap->nbands == 1);
  int width = heightmap->width;
  int height = heightmap->height;
  heman_image *result = heman_image_create(width, height, 1);
  memset(result->data, 0, ((sizeof(float)) * width) * height);
  const int scans[16 * 2] = {1, 0, 0, 1, -1, 0, 0, -1, 1, 1, -1, -1, 1, -1, -1, 1, 2, 1, 2, -1, -2, 1, -2, -1, 1, 2, 1, -2, -1, 2, -1, -2};
  int *startpts = malloc((((sizeof(int)) * 2) * 3) * kmMax(width, height));
  for (int i = 0; i < 16; i += 1)
  {
    int dx = scans[i * 2];
    int dy = scans[(i * 2) + 1];
    horizon_scan(heightmap, result, startpts, dx, dy);
  }

  for (int i = 0; i < (width * height); i += 1)
  {
    result->data[i] = 1.0f - result->data[i];
    assert((result->data[i] >= 0.0) && (result->data[i] <= 1.0f));
  }

  free(startpts);
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
static void horizon_scan(heman_image *heightmap, heman_image *result, int *startpts, int dx, int dy)
{
  int w = heightmap->width;
  int h = heightmap->height;
  int sx = (dx > 0) - (dx < 0);
  int sy = (dy > 0) - (dy < 0);
  int ax = abs(dx);
  int ay = abs(dy);
  int nsweeps = ((ay * w) + (ax * h)) - ((ax + ay) - 1);
  int *p = startpts;
  unsigned int p_idx = 0;
  for (int x = -ax; x < (w - ax); x += 1)
  {
    for (int y = -ay; y < (h - ay); y += 1)
    {
      if ((((x >= 0) && (x < w)) && (y >= 0)) && (y < h))
      {
        continue;
      }
      p[p_idx] = (sx < 0) ? ((w - x) - 1) : (x);
      p_idx += 1;
      *((&p[p_idx])++) = (sy < 0) ? ((h - y) - 1) : (y);
    }

  }

  assert(nsweeps == (((&p[p_idx]) - startpts) / 2));
  int pathlen = 0;
  int i = startpts[0];
  int j = startpts[1];
  do
  {
    i += dx;
    j += dy;
    pathlen += 1;
  }
  while ((((i >= 0) && (i < w)) && (j >= 0)) && (j < h));
  float cellw = _occlusion_scale / ((w > h) ? (w) : (h));
  float cellh = _occlusion_scale / ((w > h) ? (w) : (h));
  kmVec3 *hull_buffer = malloc(((sizeof(kmVec3)) * pathlen) * nsweeps);
  int sweep;
  #pragma omp parallel for
  for (sweep = 0; sweep < nsweeps; sweep += 1)
  {
    helper_horizon_scan_1(heightmap, result, startpts, dx, dy, w, h, pathlen, cellw, cellh, hull_buffer, sweep);
  }

  free(hull_buffer);
}


----------------------------
float kmMax(float lhs, float rhs)
{
  return (lhs > rhs) ? (lhs) : (rhs);
}


----------------------------
typedef struct heman_image_s heman_image
----------------------------
***/


// hint:  ['y_ref is a mutable refrence to int']
void helper_heman_lighting_apply_1(int * const y_ref, heman_image * const albedo, float occlusion, float diffuse, float diffuse_softening, int width, heman_image * const normals, heman_image * const occ, kmVec3 * const colors, float invgamma, kmVec3 L)
{
  int y = *y_ref;
  kmVec3 *color = colors + (y * width);
  unsigned int color_idx = 0;
  for (int x = 0; x < width; x += 1, color_idx += 1)
  {
    kmVec3 *N = (kmVec3 *) heman_image_texel(normals, x, y);
    kmVec3Lerp(N, N, &KM_VEC3_POS_Z, diffuse_softening);
    float df = 1 - (diffuse * (1 - kmClamp(kmVec3Dot(N, &L), 0, 1)));
    float of = 1 - (occlusion * (1 - (*heman_image_texel(occ, x, y))));
    if (albedo)
    {
      color[color_idx] = *((kmVec3 *) heman_image_texel(albedo, x, y));
    }
    else
    {
      color->x = (color->y = (color->z = 1));
    }
    color->x = pow(color->x, _gamma);
    color->y = pow(color->y, _gamma);
    color->z = pow(color->z, _gamma);
    kmVec3Scale(color, color, df * of);
    color->x = pow(color->x, invgamma);
    color->y = pow(color->y, invgamma);
    color->z = pow(color->z, invgamma);
  }

  *y_ref = y;
}


/*** DEPENDENCIES:
kmVec3 *kmVec3Lerp(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2, float t)
{
  pOut->x = pV1->x + (t * (pV2->x - pV1->x));
  pOut->y = pV1->y + (t * (pV2->y - pV1->y));
  pOut->z = pV1->z + (t * (pV2->z - pV1->z));
  return pOut;
}


----------------------------
typedef struct heman_image_s heman_image
----------------------------
extern const kmVec3 KM_VEC3_POS_Z
----------------------------
extern float _gamma
----------------------------
kmVec3 *kmVec3Scale(kmVec3 *pOut, const kmVec3 *pIn, const float s)
{
  pOut->x = pIn->x * s;
  pOut->y = pIn->y * s;
  pOut->z = pIn->z * s;
  return pOut;
}


----------------------------
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
float *heman_image_texel(heman_image *img, int x, int y)
{
  return (img->data + ((y * img->width) * img->nbands)) + (x * img->nbands);
}


----------------------------
float kmVec3Dot(const kmVec3 *pV1, const kmVec3 *pV2)
{
  return ((pV1->x * pV2->x) + (pV1->y * pV2->y)) + (pV1->z * pV2->z);
}


----------------------------
float kmClamp(float x, float min, float max)
{
  return (x < min) ? (min) : ((x > max) ? (max) : (x));
}


----------------------------
***/


heman_image *heman_lighting_apply(heman_image *heightmap, heman_image *albedo, float occlusion, float diffuse, float diffuse_softening, const float *light_position)
{
  unsigned int light_position_idx = 0;
  assert(heightmap->nbands == 1);
  int width = heightmap->width;
  int height = heightmap->height;
  heman_image *final = heman_image_create(width, height, 3);
  heman_image *normals = heman_lighting_compute_normals(heightmap);
  heman_image *occ = heman_lighting_compute_occlusion(heightmap);
  if (albedo)
  {
    assert(albedo->nbands == 3);
    assert(albedo->width == width);
    assert(albedo->height == height);
  }
  static float default_pos[] = {-0.5f, 0.5f, 1.0f};
  if (!(&light_position[light_position_idx]))
  {
    light_position_idx = default_pos;
  }
  kmVec3 *colors = (kmVec3 *) final->data;
  float invgamma = 1.0f / _gamma;
  kmVec3 L;
  L.x = light_position[0 + light_position_idx];
  L.y = light_position[1 + light_position_idx];
  L.z = light_position[2 + light_position_idx];
  kmVec3Normalize(&L, &L);
  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    helper_heman_lighting_apply_1(&y, albedo, occlusion, diffuse, diffuse_softening, width, normals, occ, colors, invgamma, L);
  }

  heman_image_destroy(normals);
  heman_image_destroy(occ);
  return final;
}


/*** DEPENDENCIES:
heman_image *heman_lighting_compute_normals(heman_image *heightmap)
{
  assert(heightmap->nbands == 1);
  int width = heightmap->width;
  int height = heightmap->height;
  heman_image *result = heman_image_create(width, height, 3);
  float invh = 1.0f / height;
  float invw = 1.0f / width;
  int maxx = width - 1;
  int maxy = height - 1;
  kmVec3 *normals = (kmVec3 *) result->data;
  int y;
  #pragma omp parallel for
  for (y = 0; y < height; y += 1)
  {
    helper_heman_lighting_compute_normals_1(&y, heightmap, width, invh, invw, maxx, maxy, normals);
  }

  return result;
}


----------------------------
kmVec3 *kmVec3Normalize(kmVec3 *pOut, const kmVec3 *pIn)
{
  if (((!pIn->x) && (!pIn->y)) && (!pIn->z))
  {
    return kmVec3Assign(pOut, pIn);
  }
  float l = 1.0f / kmVec3Length(pIn);
  kmVec3 v;
  v.x = pIn->x * l;
  v.y = pIn->y * l;
  v.z = pIn->z * l;
  pOut->x = v.x;
  pOut->y = v.y;
  pOut->z = v.z;
  return pOut;
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
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
void helper_heman_lighting_apply_1(int * const y_ref, heman_image * const albedo, float occlusion, float diffuse, float diffuse_softening, int width, heman_image * const normals, heman_image * const occ, kmVec3 * const colors, float invgamma, kmVec3 L)
{
  int y = *y_ref;
  kmVec3 *color = colors + (y * width);
  unsigned int color_idx = 0;
  for (int x = 0; x < width; x += 1, color_idx += 1)
  {
    kmVec3 *N = (kmVec3 *) heman_image_texel(normals, x, y);
    kmVec3Lerp(N, N, &KM_VEC3_POS_Z, diffuse_softening);
    float df = 1 - (diffuse * (1 - kmClamp(kmVec3Dot(N, &L), 0, 1)));
    float of = 1 - (occlusion * (1 - (*heman_image_texel(occ, x, y))));
    if (albedo)
    {
      color[color_idx] = *((kmVec3 *) heman_image_texel(albedo, x, y));
    }
    else
    {
      color->x = (color->y = (color->z = 1));
    }
    color->x = pow(color->x, _gamma);
    color->y = pow(color->y, _gamma);
    color->z = pow(color->z, _gamma);
    kmVec3Scale(color, color, df * of);
    color->x = pow(color->x, invgamma);
    color->y = pow(color->y, invgamma);
    color->z = pow(color->z, invgamma);
  }

  *y_ref = y;
}


----------------------------
heman_image *heman_lighting_compute_occlusion(heman_image *heightmap)
{
  assert(heightmap->nbands == 1);
  int width = heightmap->width;
  int height = heightmap->height;
  heman_image *result = heman_image_create(width, height, 1);
  memset(result->data, 0, ((sizeof(float)) * width) * height);
  const int scans[16 * 2] = {1, 0, 0, 1, -1, 0, 0, -1, 1, 1, -1, -1, 1, -1, -1, 1, 2, 1, 2, -1, -2, 1, -2, -1, 1, 2, 1, -2, -1, 2, -1, -2};
  int *startpts = malloc((((sizeof(int)) * 2) * 3) * kmMax(width, height));
  for (int i = 0; i < 16; i += 1)
  {
    int dx = scans[i * 2];
    int dy = scans[(i * 2) + 1];
    horizon_scan(heightmap, result, startpts, dx, dy);
  }

  for (int i = 0; i < (width * height); i += 1)
  {
    result->data[i] = 1.0f - result->data[i];
    assert((result->data[i] >= 0.0) && (result->data[i] <= 1.0f));
  }

  free(startpts);
  return result;
}


----------------------------
***/


