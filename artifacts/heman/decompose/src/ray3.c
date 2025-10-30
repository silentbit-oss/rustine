kmRay3 *kmRay3Fill(kmRay3 *ray, float px, float py, float pz, float vx, float vy, float vz)
{
  ray->start.x = px;
  ray->start.y = py;
  ray->start.z = pz;
  ray->dir.x = vx;
  ray->dir.y = vy;
  ray->dir.z = vz;
  return ray;
}


/*** DEPENDENCIES:
typedef struct kmRay3
{
  kmVec3 start;
  kmVec3 dir;
} kmRay3
----------------------------
***/


kmRay3 *kmRay3FromPointAndDirection(kmRay3 *ray, const kmVec3 *point, const kmVec3 *direction)
{
  kmVec3Assign(&ray->start, point);
  kmVec3Assign(&ray->dir, direction);
  return ray;
}


/*** DEPENDENCIES:
typedef struct kmRay3
{
  kmVec3 start;
  kmVec3 dir;
} kmRay3
----------------------------
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
kmVec3 *kmVec3Assign(kmVec3 *pOut, const kmVec3 *pIn)
{
  if (pOut == pIn)
  {
    return pOut;
  }
  pOut->x = pIn->x;
  pOut->y = pIn->y;
  pOut->z = pIn->z;
  return pOut;
}


----------------------------
***/


unsigned char kmRay3IntersectPlane(kmVec3 *pOut, const kmRay3 *ray, const kmPlane *plane)
{
  float d = ((plane->a * ray->dir.x) + (plane->b * ray->dir.y)) + (plane->c * ray->dir.z);
  if (d == 0)
  {
    return 0;
  }
  float t = (-((((plane->a * ray->start.x) + (plane->b * ray->start.y)) + (plane->c * ray->start.z)) + plane->d)) / d;
  if (t < 0)
  {
    return 0;
  }
  kmVec3 scaled_dir;
  kmVec3Scale(&scaled_dir, &ray->dir, t);
  kmVec3Add(pOut, &ray->start, &scaled_dir);
  return 1;
}


/*** DEPENDENCIES:
typedef struct kmPlane
{
  float a;
  float b;
  float c;
  float d;
} kmPlane
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
typedef struct kmRay3
{
  kmVec3 start;
  kmVec3 dir;
} kmRay3
----------------------------
kmVec3 *kmVec3Add(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2)
{
  kmVec3 v;
  v.x = pV1->x + pV2->x;
  v.y = pV1->y + pV2->y;
  v.z = pV1->z + pV2->z;
  pOut->x = v.x;
  pOut->y = v.y;
  pOut->z = v.z;
  return pOut;
}


----------------------------
***/


