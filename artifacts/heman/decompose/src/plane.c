kmPlane *kmPlaneFill(kmPlane *plane, float a, float b, float c, float d)
{
  plane->a = a;
  plane->b = b;
  plane->c = c;
  plane->d = d;
  return plane;
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
***/


kmPlane *kmPlaneScale(kmPlane *pOut, const kmPlane *pP, float s)
{
  assert(0 && "Not implemented");
  return 0;
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
***/


float kmPlaneDot(const kmPlane *pP, const kmVec4 *pV)
{
  return (((pP->a * pV->x) + (pP->b * pV->y)) + (pP->c * pV->z)) + (pP->d * pV->w);
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
typedef struct kmVec4
{
  float x;
  float y;
  float z;
  float w;
} kmVec4
----------------------------
***/


float kmPlaneDotCoord(const kmPlane *pP, const kmVec3 *pV)
{
  return (((pP->a * pV->x) + (pP->b * pV->y)) + (pP->c * pV->z)) + pP->d;
}


/*** DEPENDENCIES:
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
typedef struct kmPlane
{
  float a;
  float b;
  float c;
  float d;
} kmPlane
----------------------------
***/


float kmPlaneDotNormal(const kmPlane *pP, const kmVec3 *pV)
{
  return ((pP->a * pV->x) + (pP->b * pV->y)) + (pP->c * pV->z);
}


/*** DEPENDENCIES:
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
typedef struct kmPlane
{
  float a;
  float b;
  float c;
  float d;
} kmPlane
----------------------------
***/


kmPlane *kmPlaneFromNormalAndDistance(kmPlane *plane, const struct kmVec3 *normal, const float dist)
{
  plane->a = normal->x;
  plane->b = normal->y;
  plane->c = normal->z;
  plane->d = dist;
  return plane;
}


/*** DEPENDENCIES:
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
typedef struct kmPlane
{
  float a;
  float b;
  float c;
  float d;
} kmPlane
----------------------------
***/


KM_POINT_CLASSIFICATION kmPlaneClassifyPoint(const kmPlane *pIn, const kmVec3 *pP)
{
  float distance = (((pIn->a * pP->x) + (pIn->b * pP->y)) + (pIn->c * pP->z)) + pIn->d;
  if (distance > 0.0001)
  {
    return POINT_INFRONT_OF_PLANE;
  }
  if (distance < (-0.0001))
  {
    return POINT_BEHIND_PLANE;
  }
  return POINT_ON_PLANE;
}


/*** DEPENDENCIES:
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
typedef struct kmPlane
{
  float a;
  float b;
  float c;
  float d;
} kmPlane
----------------------------
***/


kmPlane *kmPlaneFromPointAndNormal(kmPlane *pOut, const kmVec3 *pPoint, const kmVec3 *pNormal)
{
  pOut->a = pNormal->x;
  pOut->b = pNormal->y;
  pOut->c = pNormal->z;
  pOut->d = -kmVec3Dot(pNormal, pPoint);
  return pOut;
}


/*** DEPENDENCIES:
float kmVec3Dot(const kmVec3 *pV1, const kmVec3 *pV2)
{
  return ((pV1->x * pV2->x) + (pV1->y * pV2->y)) + (pV1->z * pV2->z);
}


----------------------------
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
typedef struct kmPlane
{
  float a;
  float b;
  float c;
  float d;
} kmPlane
----------------------------
***/


kmPlane *kmPlaneNormalize(kmPlane *pOut, const kmPlane *pP)
{
  kmVec3 n;
  float l = 0;
  if (((!pP->a) && (!pP->b)) && (!pP->c))
  {
    pOut->a = pP->a;
    pOut->b = pP->b;
    pOut->c = pP->c;
    pOut->d = pP->d;
    return pOut;
  }
  n.x = pP->a;
  n.y = pP->b;
  n.z = pP->c;
  l = 1.0f / kmVec3Length(&n);
  kmVec3Normalize(&n, &n);
  pOut->a = n.x;
  pOut->b = n.y;
  pOut->c = n.z;
  pOut->d = pP->d * l;
  return pOut;
}


/*** DEPENDENCIES:
float kmVec3Length(const kmVec3 *pIn)
{
  return sqrtf((kmSQR(pIn->x) + kmSQR(pIn->y)) + kmSQR(pIn->z));
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
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
typedef struct kmPlane
{
  float a;
  float b;
  float c;
  float d;
} kmPlane
----------------------------
***/


kmPlane *kmPlaneExtractFromMat4(kmPlane *pOut, const struct kmMat4 *pIn, int row)
{
  int scale = (row < 0) ? (-1) : (1);
  row = abs(row) - 1;
  pOut->a = pIn->mat[3] + (scale * pIn->mat[row]);
  pOut->b = pIn->mat[7] + (scale * pIn->mat[row + 4]);
  pOut->c = pIn->mat[11] + (scale * pIn->mat[row + 8]);
  pOut->d = pIn->mat[15] + (scale * pIn->mat[row + 12]);
  return kmPlaneNormalize(pOut, pOut);
}


/*** DEPENDENCIES:
typedef struct kmMat4
{
  float mat[16];
} kmMat4
----------------------------
kmPlane *kmPlaneNormalize(kmPlane *pOut, const kmPlane *pP)
{
  kmVec3 n;
  float l = 0;
  if (((!pP->a) && (!pP->b)) && (!pP->c))
  {
    pOut->a = pP->a;
    pOut->b = pP->b;
    pOut->c = pP->c;
    pOut->d = pP->d;
    return pOut;
  }
  n.x = pP->a;
  n.y = pP->b;
  n.z = pP->c;
  l = 1.0f / kmVec3Length(&n);
  kmVec3Normalize(&n, &n);
  pOut->a = n.x;
  pOut->b = n.y;
  pOut->c = n.z;
  pOut->d = pP->d * l;
  return pOut;
}


----------------------------
typedef struct kmPlane
{
  float a;
  float b;
  float c;
  float d;
} kmPlane
----------------------------
***/


kmVec3 *kmPlaneIntersectLine(kmVec3 *pOut, const kmPlane *pP, const kmVec3 *pV1, const kmVec3 *pV2)
{
  unsigned int pOut_idx = 0;
  kmVec3 d;
  kmVec3Subtract(&d, pV2, pV1);
  kmVec3 n;
  n.x = pP->a;
  n.y = pP->b;
  n.z = pP->c;
  kmVec3Normalize(&n, &n);
  float nt = -((((n.x * pV1->x) + (n.y * pV1->y)) + (n.z * pV1->z)) + pP->d);
  float dt = ((n.x * d.x) + (n.y * d.y)) + (n.z * d.z);
  if (fabs(dt) < 0.0001)
  {
    pOut_idx = 0;
    return pOut;
  }
  float t = nt / dt;
  pOut->x = pV1->x + (d.x * t);
  pOut->y = pV1->y + (d.y * t);
  pOut->z = pV1->z + (d.z * t);
  return pOut;
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


kmPlane *kmPlaneFromPoints(kmPlane *pOut, const kmVec3 *p1, const kmVec3 *p2, const kmVec3 *p3)
{
  kmVec3 n;
  kmVec3 v1;
  kmVec3 v2;
  kmVec3Subtract(&v1, p2, p1);
  kmVec3Subtract(&v2, p3, p1);
  kmVec3Cross(&n, &v1, &v2);
  kmVec3Normalize(&n, &n);
  pOut->a = n.x;
  pOut->b = n.y;
  pOut->c = n.z;
  pOut->d = kmVec3Dot(kmVec3Scale(&n, &n, -1.0), p1);
  return pOut;
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
typedef struct kmPlane
{
  float a;
  float b;
  float c;
  float d;
} kmPlane
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


kmVec3 *kmPlaneGetIntersection(kmVec3 *pOut, const kmPlane *p1, const kmPlane *p2, const kmPlane *p3)
{
  kmVec3 n1;
  kmVec3 n2;
  kmVec3 n3;
  kmVec3 cross;
  kmVec3 r1;
  kmVec3 r2;
  kmVec3 r3;
  double denom = 0;
  kmVec3Fill(&n1, p1->a, p1->b, p1->c);
  kmVec3Fill(&n2, p2->a, p2->b, p2->c);
  kmVec3Fill(&n3, p3->a, p3->b, p3->c);
  kmVec3Cross(&cross, &n2, &n3);
  denom = kmVec3Dot(&n1, &cross);
  if (kmAlmostEqual(denom, 0.0))
  {
    return 0;
  }
  kmVec3Cross(&r1, &n2, &n3);
  kmVec3Cross(&r2, &n3, &n1);
  kmVec3Cross(&r3, &n1, &n2);
  kmVec3Scale(&r1, &r1, -p1->d);
  kmVec3Scale(&r2, &r2, p2->d);
  kmVec3Scale(&r3, &r3, p3->d);
  kmVec3Subtract(pOut, &r1, &r2);
  kmVec3Subtract(pOut, pOut, &r3);
  kmVec3Scale(pOut, pOut, 1.0 / denom);
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
kmVec3 *kmVec3Fill(kmVec3 *pOut, float x, float y, float z)
{
  pOut->x = x;
  pOut->y = y;
  pOut->z = z;
  return pOut;
}


----------------------------
unsigned char kmAlmostEqual(float lhs, float rhs)
{
  return ((lhs + 0.0001) > rhs) && ((lhs - 0.0001) < rhs);
}


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


