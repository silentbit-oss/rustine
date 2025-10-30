kmVec2 *kmVec2Fill(kmVec2 *pOut, float x, float y)
{
  pOut->x = x;
  pOut->y = y;
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
***/


kmVec2 *kmVec2Lerp(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2, float t)
{
  pOut->x = pV1->x + (t * (pV2->x - pV1->x));
  pOut->y = pV1->y + (t * (pV2->y - pV1->y));
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
***/


kmVec2 *kmVec2Add(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2)
{
  pOut->x = pV1->x + pV2->x;
  pOut->y = pV1->y + pV2->y;
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
***/


float kmVec2Dot(const kmVec2 *pV1, const kmVec2 *pV2)
{
  return (pV1->x * pV2->x) + (pV1->y * pV2->y);
}


/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
***/


float kmVec2Cross(const kmVec2 *pV1, const kmVec2 *pV2)
{
  return (pV1->x * pV2->y) - (pV1->y * pV2->x);
}


/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
***/


kmVec2 *kmVec2Subtract(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2)
{
  pOut->x = pV1->x - pV2->x;
  pOut->y = pV1->y - pV2->y;
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
***/


kmVec2 *kmVec2Mul(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2)
{
  pOut->x = pV1->x * pV2->x;
  pOut->y = pV1->y * pV2->y;
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
***/


kmVec2 *kmVec2Div(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2)
{
  if (pV2->x && pV2->y)
  {
    pOut->x = pV1->x / pV2->x;
    pOut->y = pV1->y / pV2->y;
  }
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
***/


kmVec2 *kmVec2Scale(kmVec2 *pOut, const kmVec2 *pIn, const float s)
{
  pOut->x = pIn->x * s;
  pOut->y = pIn->y * s;
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
***/


int kmVec2AreEqual(const kmVec2 *p1, const kmVec2 *p2)
{
  return ((p1->x < (p2->x + 0.0001)) && (p1->x > (p2->x - 0.0001))) && ((p1->y < (p2->y + 0.0001)) && (p1->y > (p2->y - 0.0001)));
}


/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
***/


kmVec2 *kmVec2Assign(kmVec2 *pOut, const kmVec2 *pIn)
{
  if (pOut == pIn)
  {
    return pOut;
  }
  pOut->x = pIn->x;
  pOut->y = pIn->y;
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
***/


float kmVec2Length(const kmVec2 *pIn)
{
  return sqrtf(kmSQR(pIn->x) + kmSQR(pIn->y));
}


/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
float kmSQR(float s)
{
  return s * s;
}


----------------------------
***/


float kmVec2LengthSq(const kmVec2 *pIn)
{
  return kmSQR(pIn->x) + kmSQR(pIn->y);
}


/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
float kmSQR(float s)
{
  return s * s;
}


----------------------------
***/


kmVec2 *kmVec2Transform(kmVec2 *pOut, const kmVec2 *pV, const kmMat3 *pM)
{
  kmVec2 v;
  v.x = ((pV->x * pM->mat[0]) + (pV->y * pM->mat[3])) + pM->mat[6];
  v.y = ((pV->x * pM->mat[1]) + (pV->y * pM->mat[4])) + pM->mat[7];
  pOut->x = v.x;
  pOut->y = v.y;
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
typedef struct kmMat3
{
  float mat[9];
} kmMat3
----------------------------
***/


kmVec2 *kmVec2TransformCoord(kmVec2 *pOut, const kmVec2 *pV, const kmMat3 *pM)
{
  assert(0);
  return 0;
}


/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
typedef struct kmMat3
{
  float mat[9];
} kmMat3
----------------------------
***/


kmVec2 *kmVec2RotateBy(kmVec2 *pOut, const kmVec2 *pIn, const float degrees, const kmVec2 *center)
{
  float x;
  float y;
  const float radians = kmDegreesToRadians(degrees);
  const float cs = cosf(radians);
  const float sn = sinf(radians);
  pOut->x = pIn->x - center->x;
  pOut->y = pIn->y - center->y;
  x = (pOut->x * cs) - (pOut->y * sn);
  y = (pOut->x * sn) + (pOut->y * cs);
  pOut->x = x + center->x;
  pOut->y = y + center->y;
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
float kmDegreesToRadians(float degrees)
{
  return degrees * (3.14159265358979323846f / 180.0f);
}


----------------------------
***/


kmVec2 *kmVec2MidPointBetween(kmVec2 *pOut, const kmVec2 *v1, const kmVec2 *v2)
{
  kmVec2 sum;
  kmVec2Add(&sum, v1, v2);
  pOut->x = sum.x / 2.0f;
  pOut->y = sum.y / 2.0f;
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
kmVec2 *kmVec2Add(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2)
{
  pOut->x = pV1->x + pV2->x;
  pOut->y = pV1->y + pV2->y;
  return pOut;
}


----------------------------
***/


kmVec2 *kmVec2Normalize(kmVec2 *pOut, const kmVec2 *pIn)
{
  if ((!pIn->x) && (!pIn->y))
  {
    return kmVec2Assign(pOut, pIn);
  }
  float l = 1.0f / kmVec2Length(pIn);
  kmVec2 v;
  v.x = pIn->x * l;
  v.y = pIn->y * l;
  pOut->x = v.x;
  pOut->y = v.y;
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
float kmVec2Length(const kmVec2 *pIn)
{
  return sqrtf(kmSQR(pIn->x) + kmSQR(pIn->y));
}


----------------------------
kmVec2 *kmVec2Assign(kmVec2 *pOut, const kmVec2 *pIn)
{
  if (pOut == pIn)
  {
    return pOut;
  }
  pOut->x = pIn->x;
  pOut->y = pIn->y;
  return pOut;
}


----------------------------
***/


float kmVec2DistanceBetween(const kmVec2 *v1, const kmVec2 *v2)
{
  kmVec2 diff;
  kmVec2Subtract(&diff, v2, v1);
  return fabs(kmVec2Length(&diff));
}


/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
kmVec2 *kmVec2Subtract(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2)
{
  pOut->x = pV1->x - pV2->x;
  pOut->y = pV1->y - pV2->y;
  return pOut;
}


----------------------------
float kmVec2Length(const kmVec2 *pIn)
{
  return sqrtf(kmSQR(pIn->x) + kmSQR(pIn->y));
}


----------------------------
***/


kmVec2 *kmVec2Reflect(kmVec2 *pOut, const kmVec2 *pIn, const kmVec2 *normal)
{
  kmVec2 tmp;
  kmVec2Scale(&tmp, normal, 2.0f * kmVec2Dot(pIn, normal));
  kmVec2Subtract(pOut, pIn, &tmp);
  return pOut;
}


/*** DEPENDENCIES:
float kmVec2Dot(const kmVec2 *pV1, const kmVec2 *pV2)
{
  return (pV1->x * pV2->x) + (pV1->y * pV2->y);
}


----------------------------
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
kmVec2 *kmVec2Scale(kmVec2 *pOut, const kmVec2 *pIn, const float s)
{
  pOut->x = pIn->x * s;
  pOut->y = pIn->y * s;
  return pOut;
}


----------------------------
kmVec2 *kmVec2Subtract(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2)
{
  pOut->x = pV1->x - pV2->x;
  pOut->y = pV1->y - pV2->y;
  return pOut;
}


----------------------------
***/


float kmVec2DegreesBetween(const kmVec2 *v1, const kmVec2 *v2)
{
  if (kmVec2AreEqual(v1, v2))
  {
    return 0.0;
  }
  kmVec2 t1;
  kmVec2 t2;
  kmVec2Normalize(&t1, v1);
  kmVec2Normalize(&t2, v2);
  float cross = kmVec2Cross(&t1, &t2);
  float dot = kmVec2Dot(&t1, &t2);
  if (dot > 1.0)
  {
    dot = 1.0;
  }
  if (dot < (-1.0))
  {
    dot = -1.0;
  }
  return kmRadiansToDegrees(atan2(cross, dot));
}


/*** DEPENDENCIES:
int kmVec2AreEqual(const kmVec2 *p1, const kmVec2 *p2)
{
  return ((p1->x < (p2->x + 0.0001)) && (p1->x > (p2->x - 0.0001))) && ((p1->y < (p2->y + 0.0001)) && (p1->y > (p2->y - 0.0001)));
}


----------------------------
float kmVec2Cross(const kmVec2 *pV1, const kmVec2 *pV2)
{
  return (pV1->x * pV2->y) - (pV1->y * pV2->x);
}


----------------------------
kmVec2 *kmVec2Normalize(kmVec2 *pOut, const kmVec2 *pIn)
{
  if ((!pIn->x) && (!pIn->y))
  {
    return kmVec2Assign(pOut, pIn);
  }
  float l = 1.0f / kmVec2Length(pIn);
  kmVec2 v;
  v.x = pIn->x * l;
  v.y = pIn->y * l;
  pOut->x = v.x;
  pOut->y = v.y;
  return pOut;
}


----------------------------
float kmRadiansToDegrees(float radians)
{
  return radians * (180.0 / 3.14159265358979323846f);
}


----------------------------
float kmVec2Dot(const kmVec2 *pV1, const kmVec2 *pV2)
{
  return (pV1->x * pV2->x) + (pV1->y * pV2->y);
}


----------------------------
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
***/


