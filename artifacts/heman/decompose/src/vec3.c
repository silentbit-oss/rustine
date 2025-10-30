kmVec3 *kmVec3Fill(kmVec3 *pOut, float x, float y, float z)
{
  pOut->x = x;
  pOut->y = y;
  pOut->z = z;
  return pOut;
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


kmVec3 *kmVec3Lerp(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2, float t)
{
  pOut->x = pV1->x + (t * (pV2->x - pV1->x));
  pOut->y = pV1->y + (t * (pV2->y - pV1->y));
  pOut->z = pV1->z + (t * (pV2->z - pV1->z));
  return pOut;
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


/*** DEPENDENCIES:
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
***/


float kmVec3Dot(const kmVec3 *pV1, const kmVec3 *pV2)
{
  return ((pV1->x * pV2->x) + (pV1->y * pV2->y)) + (pV1->z * pV2->z);
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


/*** DEPENDENCIES:
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
***/


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


/*** DEPENDENCIES:
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
***/


kmVec3 *kmVec3Mul(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2)
{
  pOut->x = pV1->x * pV2->x;
  pOut->y = pV1->y * pV2->y;
  pOut->z = pV1->z * pV2->z;
  return pOut;
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


kmVec3 *kmVec3Div(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2)
{
  if ((pV2->x && pV2->y) && pV2->z)
  {
    pOut->x = pV1->x / pV2->x;
    pOut->y = pV1->y / pV2->y;
    pOut->z = pV1->z / pV2->z;
  }
  return pOut;
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


kmVec3 *kmVec3Scale(kmVec3 *pOut, const kmVec3 *pIn, const float s)
{
  pOut->x = pIn->x * s;
  pOut->y = pIn->y * s;
  pOut->z = pIn->z * s;
  return pOut;
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


int kmVec3AreEqual(const kmVec3 *p1, const kmVec3 *p2)
{
  if ((((p1->x < (p2->x + 0.0001)) && (p1->x > (p2->x - 0.0001))) && ((p1->y < (p2->y + 0.0001)) && (p1->y > (p2->y - 0.0001)))) && ((p1->z < (p2->z + 0.0001)) && (p1->z > (p2->z - 0.0001))))
  {
    return 1;
  }
  return 0;
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


/*** DEPENDENCIES:
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
***/


kmVec3 *kmVec3Zero(kmVec3 *pOut)
{
  pOut->x = 0.0f;
  pOut->y = 0.0f;
  pOut->z = 0.0f;
  return pOut;
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


float kmVec3Length(const kmVec3 *pIn)
{
  return sqrtf((kmSQR(pIn->x) + kmSQR(pIn->y)) + kmSQR(pIn->z));
}


/*** DEPENDENCIES:
float kmSQR(float s)
{
  return s * s;
}


----------------------------
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
***/


float kmVec3LengthSq(const kmVec3 *pIn)
{
  return (kmSQR(pIn->x) + kmSQR(pIn->y)) + kmSQR(pIn->z);
}


/*** DEPENDENCIES:
float kmSQR(float s)
{
  return s * s;
}


----------------------------
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
***/


kmVec3 *kmVec3MultiplyMat3(kmVec3 *pOut, const kmVec3 *pV, const kmMat3 *pM)
{
  kmVec3 v;
  v.x = ((pV->x * pM->mat[0]) + (pV->y * pM->mat[3])) + (pV->z * pM->mat[6]);
  v.y = ((pV->x * pM->mat[1]) + (pV->y * pM->mat[4])) + (pV->z * pM->mat[7]);
  v.z = ((pV->x * pM->mat[2]) + (pV->y * pM->mat[5])) + (pV->z * pM->mat[8]);
  pOut->x = v.x;
  pOut->y = v.y;
  pOut->z = v.z;
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmMat3
{
  float mat[9];
} kmMat3
----------------------------
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
***/


kmVec3 *kmVec3MultiplyMat4(kmVec3 *pOut, const kmVec3 *pV, const kmMat4 *pM)
{
  kmVec3 v;
  v.x = (((pV->x * pM->mat[0]) + (pV->y * pM->mat[4])) + (pV->z * pM->mat[8])) + pM->mat[12];
  v.y = (((pV->x * pM->mat[1]) + (pV->y * pM->mat[5])) + (pV->z * pM->mat[9])) + pM->mat[13];
  v.z = (((pV->x * pM->mat[2]) + (pV->y * pM->mat[6])) + (pV->z * pM->mat[10])) + pM->mat[14];
  pOut->x = v.x;
  pOut->y = v.y;
  pOut->z = v.z;
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
typedef struct kmMat4
{
  float mat[16];
} kmMat4
----------------------------
***/


kmVec3 *kmVec3TransformNormal(kmVec3 *pOut, const kmVec3 *pV, const kmMat4 *pM)
{
  kmVec3 v;
  v.x = ((pV->x * pM->mat[0]) + (pV->y * pM->mat[4])) + (pV->z * pM->mat[8]);
  v.y = ((pV->x * pM->mat[1]) + (pV->y * pM->mat[5])) + (pV->z * pM->mat[9]);
  v.z = ((pV->x * pM->mat[2]) + (pV->y * pM->mat[6])) + (pV->z * pM->mat[10]);
  pOut->x = v.x;
  pOut->y = v.y;
  pOut->z = v.z;
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
typedef struct kmMat4
{
  float mat[16];
} kmMat4
----------------------------
***/


kmVec3 *kmVec3InverseTransform(kmVec3 *pOut, const kmVec3 *pVect, const kmMat4 *pM)
{
  kmVec3 v1;
  kmVec3 v2;
  v1.x = pVect->x - pM->mat[12];
  v1.y = pVect->y - pM->mat[13];
  v1.z = pVect->z - pM->mat[14];
  v2.x = ((v1.x * pM->mat[0]) + (v1.y * pM->mat[1])) + (v1.z * pM->mat[2]);
  v2.y = ((v1.x * pM->mat[4]) + (v1.y * pM->mat[5])) + (v1.z * pM->mat[6]);
  v2.z = ((v1.x * pM->mat[8]) + (v1.y * pM->mat[9])) + (v1.z * pM->mat[10]);
  pOut->x = v2.x;
  pOut->y = v2.y;
  pOut->z = v2.z;
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
typedef struct kmMat4
{
  float mat[16];
} kmMat4
----------------------------
***/


kmVec3 *kmVec3InverseTransformNormal(kmVec3 *pOut, const kmVec3 *pVect, const kmMat4 *pM)
{
  kmVec3 v;
  v.x = ((pVect->x * pM->mat[0]) + (pVect->y * pM->mat[1])) + (pVect->z * pM->mat[2]);
  v.y = ((pVect->x * pM->mat[4]) + (pVect->y * pM->mat[5])) + (pVect->z * pM->mat[6]);
  v.z = ((pVect->x * pM->mat[8]) + (pVect->y * pM->mat[9])) + (pVect->z * pM->mat[10]);
  pOut->x = v.x;
  pOut->y = v.y;
  pOut->z = v.z;
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
typedef struct kmMat4
{
  float mat[16];
} kmMat4
----------------------------
***/


kmVec3 *kmVec3GetHorizontalAngle(kmVec3 *pOut, const kmVec3 *pIn)
{
  const float z1 = sqrt((pIn->x * pIn->x) + (pIn->z * pIn->z));
  pOut->y = kmRadiansToDegrees(atan2(pIn->x, pIn->z));
  if (pOut->y < 0)
  {
    pOut->y += 360;
  }
  if (pOut->y >= 360)
  {
    pOut->y -= 360;
  }
  pOut->x = kmRadiansToDegrees(atan2(z1, pIn->y)) - 90.0;
  if (pOut->x < 0)
  {
    pOut->x += 360;
  }
  if (pOut->x >= 360)
  {
    pOut->x -= 360;
  }
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
float kmRadiansToDegrees(float radians)
{
  return radians * (180.0 / 3.14159265358979323846f);
}


----------------------------
***/


kmVec3 *kmVec3RotationToDirection(kmVec3 *pOut, const kmVec3 *pIn, const kmVec3 *forwards)
{
  const float xr = kmDegreesToRadians(pIn->x);
  const float yr = kmDegreesToRadians(pIn->y);
  const float zr = kmDegreesToRadians(pIn->z);
  const float cr = cos(xr);
  const float sr = sin(xr);
  const float cp = cos(yr);
  const float sp = sin(yr);
  const float cy = cos(zr);
  const float sy = sin(zr);
  const float srsp = sr * sp;
  const float crsp = cr * sp;
  const float pseudoMatrix[] = {cp * cy, cp * sy, -sp, (srsp * cy) - (cr * sy), (srsp * sy) + (cr * cy), sr * cp, (crsp * cy) + (sr * sy), (crsp * sy) - (sr * cy), cr * cp};
  pOut->x = ((forwards->x * pseudoMatrix[0]) + (forwards->y * pseudoMatrix[3])) + (forwards->z * pseudoMatrix[6]);
  pOut->y = ((forwards->x * pseudoMatrix[1]) + (forwards->y * pseudoMatrix[4])) + (forwards->z * pseudoMatrix[7]);
  pOut->z = ((forwards->x * pseudoMatrix[2]) + (forwards->y * pseudoMatrix[5])) + (forwards->z * pseudoMatrix[8]);
  return pOut;
}


/*** DEPENDENCIES:
float kmDegreesToRadians(float degrees)
{
  return degrees * (3.14159265358979323846f / 180.0f);
}


----------------------------
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
***/


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


kmVec3 *kmVec3Transform(kmVec3 *pOut, const kmVec3 *pV, const kmMat4 *pM)
{
  return kmVec3MultiplyMat4(pOut, pV, pM);
}


/*** DEPENDENCIES:
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
typedef struct kmMat4
{
  float mat[16];
} kmMat4
----------------------------
kmVec3 *kmVec3MultiplyMat4(kmVec3 *pOut, const kmVec3 *pV, const kmMat4 *pM)
{
  kmVec3 v;
  v.x = (((pV->x * pM->mat[0]) + (pV->y * pM->mat[4])) + (pV->z * pM->mat[8])) + pM->mat[12];
  v.y = (((pV->x * pM->mat[1]) + (pV->y * pM->mat[5])) + (pV->z * pM->mat[9])) + pM->mat[13];
  v.z = (((pV->x * pM->mat[2]) + (pV->y * pM->mat[6])) + (pV->z * pM->mat[10])) + pM->mat[14];
  pOut->x = v.x;
  pOut->y = v.y;
  pOut->z = v.z;
  return pOut;
}


----------------------------
***/


kmVec3 *kmVec3Reflect(kmVec3 *pOut, const kmVec3 *pIn, const kmVec3 *normal)
{
  kmVec3 tmp;
  kmVec3Scale(&tmp, normal, 2.0f * kmVec3Dot(pIn, normal));
  kmVec3Subtract(pOut, pIn, &tmp);
  return pOut;
}


/*** DEPENDENCIES:
float kmVec3Dot(const kmVec3 *pV1, const kmVec3 *pV2)
{
  return ((pV1->x * pV2->x) + (pV1->y * pV2->y)) + (pV1->z * pV2->z);
}


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


kmVec3 *kmVec3TransformCoord(kmVec3 *pOut, const kmVec3 *pV, const kmMat4 *pM)
{
  kmVec4 v;
  kmVec4 inV;
  kmVec4Fill(&inV, pV->x, pV->y, pV->z, 1.0);
  kmVec4Transform(&v, &inV, pM);
  pOut->x = v.x / v.w;
  pOut->y = v.y / v.w;
  pOut->z = v.z / v.w;
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
kmVec4 *kmVec4Fill(kmVec4 *pOut, float x, float y, float z, float w)
{
  pOut->x = x;
  pOut->y = y;
  pOut->z = z;
  pOut->w = w;
  return pOut;
}


----------------------------
typedef struct kmVec4
{
  float x;
  float y;
  float z;
  float w;
} kmVec4
----------------------------
typedef struct kmMat4
{
  float mat[16];
} kmMat4
----------------------------
kmVec4 *kmVec4Transform(kmVec4 *pOut, const kmVec4 *pV, const kmMat4 *pM)
{
  return kmVec4MultiplyMat4(pOut, pV, pM);
}


----------------------------
***/


kmVec3 *kmVec3ProjectOnToPlane(kmVec3 *pOut, const kmVec3 *point, const struct kmPlane *plane)
{
  kmRay3 ray;
  kmVec3Assign(&ray.start, point);
  ray.dir.x = -plane->a;
  ray.dir.y = -plane->b;
  ray.dir.z = -plane->c;
  kmRay3IntersectPlane(pOut, &ray, plane);
  return pOut;
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


