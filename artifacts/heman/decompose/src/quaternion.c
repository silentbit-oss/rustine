// hint:  ['x_ref is a mutable refrence to float', 'y_ref is a mutable refrence to float', 'z_ref is a mutable refrence to float', 'w_ref is a mutable refrence to float', 'scale_ref is a mutable refrence to float']
void helper_kmQuaternionRotationMatrix_1(float * const x_ref, float * const y_ref, float * const z_ref, float * const w_ref, float * const scale_ref, float * const pMatrix, unsigned int pMatrix_idx)
{
  float x = *x_ref;
  float y = *y_ref;
  float z = *z_ref;
  float w = *w_ref;
  float scale = *scale_ref;
  if ((pMatrix[0 + pMatrix_idx] > pMatrix[5 + pMatrix_idx]) && (pMatrix[0 + pMatrix_idx] > pMatrix[10 + pMatrix_idx]))
  {
    scale = ((float) sqrt(((1.0f + pMatrix[0 + pMatrix_idx]) - pMatrix[5 + pMatrix_idx]) - pMatrix[10 + pMatrix_idx])) * 2.0f;
    x = 0.25f * scale;
    y = (pMatrix[4 + pMatrix_idx] + pMatrix[1 + pMatrix_idx]) / scale;
    z = (pMatrix[2 + pMatrix_idx] + pMatrix[8 + pMatrix_idx]) / scale;
    w = (pMatrix[9 + pMatrix_idx] - pMatrix[6 + pMatrix_idx]) / scale;
  }
  else
    if (pMatrix[5 + pMatrix_idx] > pMatrix[10 + pMatrix_idx])
  {
    scale = ((float) sqrt(((1.0f + pMatrix[5 + pMatrix_idx]) - pMatrix[0 + pMatrix_idx]) - pMatrix[10 + pMatrix_idx])) * 2.0f;
    x = (pMatrix[4 + pMatrix_idx] + pMatrix[1 + pMatrix_idx]) / scale;
    y = 0.25f * scale;
    z = (pMatrix[9 + pMatrix_idx] + pMatrix[6 + pMatrix_idx]) / scale;
    w = (pMatrix[2 + pMatrix_idx] - pMatrix[8 + pMatrix_idx]) / scale;
  }
  else
  {
    scale = ((float) sqrt(((1.0f + pMatrix[10 + pMatrix_idx]) - pMatrix[0 + pMatrix_idx]) - pMatrix[5 + pMatrix_idx])) * 2.0f;
    x = (pMatrix[2 + pMatrix_idx] + pMatrix[8 + pMatrix_idx]) / scale;
    y = (pMatrix[9 + pMatrix_idx] + pMatrix[6 + pMatrix_idx]) / scale;
    z = 0.25f * scale;
    w = (pMatrix[4 + pMatrix_idx] - pMatrix[1 + pMatrix_idx]) / scale;
  }
  *x_ref = x;
  *y_ref = y;
  *z_ref = z;
  *w_ref = w;
  *scale_ref = scale;
}


/*** DEPENDENCIES:
***/


int kmQuaternionAreEqual(const kmQuaternion *p1, const kmQuaternion *p2)
{
  if (((((p1->x < (p2->x + 0.0001)) && (p1->x > (p2->x - 0.0001))) && ((p1->y < (p2->y + 0.0001)) && (p1->y > (p2->y - 0.0001)))) && ((p1->z < (p2->z + 0.0001)) && (p1->z > (p2->z - 0.0001)))) && ((p1->w < (p2->w + 0.0001)) && (p1->w > (p2->w - 0.0001))))
  {
    return 1;
  }
  return 0;
}


/*** DEPENDENCIES:
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion
----------------------------
***/


kmQuaternion *kmQuaternionFill(kmQuaternion *pOut, float x, float y, float z, float w)
{
  pOut->x = x;
  pOut->y = y;
  pOut->z = z;
  pOut->w = w;
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion
----------------------------
***/


float kmQuaternionDot(const kmQuaternion *q1, const kmQuaternion *q2)
{
  return (((q1->w * q2->w) + (q1->x * q2->x)) + (q1->y * q2->y)) + (q1->z * q2->z);
}


/*** DEPENDENCIES:
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion
----------------------------
***/


kmQuaternion *kmQuaternionExp(kmQuaternion *pOut, const kmQuaternion *pIn)
{
  assert(0);
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion
----------------------------
***/


kmQuaternion *kmQuaternionIdentity(kmQuaternion *pOut)
{
  pOut->x = 0.0;
  pOut->y = 0.0;
  pOut->z = 0.0;
  pOut->w = 1.0;
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion
----------------------------
***/


int kmQuaternionIsIdentity(const kmQuaternion *pIn)
{
  return (((pIn->x == 0.0) && (pIn->y == 0.0)) && (pIn->z == 0.0)) && (pIn->w == 1.0);
}


/*** DEPENDENCIES:
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion
----------------------------
***/


float kmQuaternionLengthSq(const kmQuaternion *pIn)
{
  return (((pIn->x * pIn->x) + (pIn->y * pIn->y)) + (pIn->z * pIn->z)) + (pIn->w * pIn->w);
}


/*** DEPENDENCIES:
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion
----------------------------
***/


kmQuaternion *kmQuaternionLn(kmQuaternion *pOut, const kmQuaternion *pIn)
{
  assert(0);
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion
----------------------------
***/


kmQuaternion *kmQuaternionRotationPitchYawRoll(kmQuaternion *pOut, float pitch, float yaw, float roll)
{
  assert(pitch <= (2 * 3.14159265358979323846f));
  assert(yaw <= (2 * 3.14159265358979323846f));
  assert(roll <= (2 * 3.14159265358979323846f));
  float sY = sinf(yaw * 0.5);
  float cY = cosf(yaw * 0.5);
  float sZ = sinf(roll * 0.5);
  float cZ = cosf(roll * 0.5);
  float sX = sinf(pitch * 0.5);
  float cX = cosf(pitch * 0.5);
  pOut->w = ((cY * cZ) * cX) - ((sY * sZ) * sX);
  pOut->x = ((sY * sZ) * cX) + ((cY * cZ) * sX);
  pOut->y = ((sY * cZ) * cX) + ((cY * sZ) * sX);
  pOut->z = ((cY * sZ) * cX) - ((sY * cZ) * sX);
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion
----------------------------
***/


kmQuaternion *kmQuaternionScale(kmQuaternion *pOut, const kmQuaternion *pIn, float s)
{
  pOut->x = pIn->x * s;
  pOut->y = pIn->y * s;
  pOut->z = pIn->z * s;
  pOut->w = pIn->w * s;
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion
----------------------------
***/


kmQuaternion *kmQuaternionAssign(kmQuaternion *pOut, const kmQuaternion *pIn)
{
  memcpy(pOut, pIn, (sizeof(float)) * 4);
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion
----------------------------
***/


kmQuaternion *kmQuaternionAdd(kmQuaternion *pOut, const kmQuaternion *pQ1, const kmQuaternion *pQ2)
{
  pOut->x = pQ1->x + pQ2->x;
  pOut->y = pQ1->y + pQ2->y;
  pOut->z = pQ1->z + pQ2->z;
  pOut->w = pQ1->w + pQ2->w;
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion
----------------------------
***/


kmQuaternion *kmQuaternionSubtract(kmQuaternion *pOut, const kmQuaternion *pQ1, const kmQuaternion *pQ2)
{
  pOut->x = pQ1->x - pQ2->x;
  pOut->y = pQ1->y - pQ2->y;
  pOut->z = pQ1->z - pQ2->z;
  pOut->w = pQ1->w - pQ2->w;
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion
----------------------------
***/


float kmQuaternionGetPitch(const kmQuaternion *q)
{
  float result = atan2(2 * ((q->y * q->z) + (q->w * q->x)), (((q->w * q->w) - (q->x * q->x)) - (q->y * q->y)) + (q->z * q->z));
  return result;
}


/*** DEPENDENCIES:
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion
----------------------------
***/


float kmQuaternionGetYaw(const kmQuaternion *q)
{
  float result = asin((-2) * ((q->x * q->z) - (q->w * q->y)));
  return result;
}


/*** DEPENDENCIES:
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion
----------------------------
***/


float kmQuaternionGetRoll(const kmQuaternion *q)
{
  float result = atan2(2 * ((q->x * q->y) + (q->w * q->z)), (((q->w * q->w) + (q->x * q->x)) - (q->y * q->y)) - (q->z * q->z));
  return result;
}


/*** DEPENDENCIES:
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion
----------------------------
***/


float kmQuaternionLength(const kmQuaternion *pIn)
{
  return sqrt(kmQuaternionLengthSq(pIn));
}


/*** DEPENDENCIES:
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion
----------------------------
float kmQuaternionLengthSq(const kmQuaternion *pIn)
{
  return (((pIn->x * pIn->x) + (pIn->y * pIn->y)) + (pIn->z * pIn->z)) + (pIn->w * pIn->w);
}


----------------------------
***/


kmQuaternion *kmQuaternionInverse(kmQuaternion *pOut, const kmQuaternion *pIn)
{
  float l = kmQuaternionLength(pIn);
  if (fabs(l) < 0.0001)
  {
    pOut->x = 0.0;
    pOut->y = 0.0;
    pOut->z = 0.0;
    pOut->w = 0.0;
    return pOut;
  }
  pOut->x = -pIn->x;
  pOut->y = -pIn->y;
  pOut->z = -pIn->z;
  pOut->w = pIn->w;
  return pOut;
}


/*** DEPENDENCIES:
float kmQuaternionLength(const kmQuaternion *pIn)
{
  return sqrt(kmQuaternionLengthSq(pIn));
}


----------------------------
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion
----------------------------
***/


extern kmQuaternion *kmQuaternionMultiply(kmQuaternion *pOut, const kmQuaternion *qu1, const kmQuaternion *qu2)
{
  kmQuaternion tmp1;
  kmQuaternion tmp2;
  kmQuaternionAssign(&tmp1, qu1);
  kmQuaternionAssign(&tmp2, qu2);
  kmQuaternion *q1 = &tmp1;
  kmQuaternion *q2 = &tmp2;
  pOut->x = (((q1->w * q2->x) + (q1->x * q2->w)) + (q1->y * q2->z)) - (q1->z * q2->y);
  pOut->y = (((q1->w * q2->y) + (q1->y * q2->w)) + (q1->z * q2->x)) - (q1->x * q2->z);
  pOut->z = (((q1->w * q2->z) + (q1->z * q2->w)) + (q1->x * q2->y)) - (q1->y * q2->x);
  pOut->w = (((q1->w * q2->w) - (q1->x * q2->x)) - (q1->y * q2->y)) - (q1->z * q2->z);
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion
----------------------------
kmQuaternion *kmQuaternionAssign(kmQuaternion *pOut, const kmQuaternion *pIn)
{
  memcpy(pOut, pIn, (sizeof(float)) * 4);
  return pOut;
}


----------------------------
***/


kmQuaternion *kmQuaternionNormalize(kmQuaternion *pOut, const kmQuaternion *pIn)
{
  float length = kmQuaternionLength(pIn);
  if (fabs(length) < 0.0001)
  {
    pOut->x = 0.0;
    pOut->y = 0.0;
    pOut->z = 0.0;
    pOut->w = 0.0;
    return pOut;
  }
  kmQuaternionFill(pOut, pOut->x / length, pOut->y / length, pOut->z / length, pOut->w / length);
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion
----------------------------
float kmQuaternionLength(const kmQuaternion *pIn)
{
  return sqrt(kmQuaternionLengthSq(pIn));
}


----------------------------
kmQuaternion *kmQuaternionFill(kmQuaternion *pOut, float x, float y, float z, float w)
{
  pOut->x = x;
  pOut->y = y;
  pOut->z = z;
  pOut->w = w;
  return pOut;
}


----------------------------
***/


kmQuaternion *kmQuaternionRotationAxisAngle(kmQuaternion *pOut, const kmVec3 *pV, float angle)
{
  float rad = angle * 0.5f;
  float scale = sinf(rad);
  pOut->x = pV->x * scale;
  pOut->y = pV->y * scale;
  pOut->z = pV->z * scale;
  pOut->w = cosf(rad);
  kmQuaternionNormalize(pOut, pOut);
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
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion
----------------------------
kmQuaternion *kmQuaternionNormalize(kmQuaternion *pOut, const kmQuaternion *pIn)
{
  float length = kmQuaternionLength(pIn);
  if (fabs(length) < 0.0001)
  {
    pOut->x = 0.0;
    pOut->y = 0.0;
    pOut->z = 0.0;
    pOut->w = 0.0;
    return pOut;
  }
  kmQuaternionFill(pOut, pOut->x / length, pOut->y / length, pOut->z / length, pOut->w / length);
  return pOut;
}


----------------------------
***/


kmQuaternion *kmQuaternionRotationMatrix(kmQuaternion *pOut, const kmMat3 *pIn)
{
  float x;
  float y;
  float z;
  float w;
  float *pMatrix = 0;
  unsigned int pMatrix_idx = 0;
  float m4x4[16] = {0};
  float scale = 0.0f;
  float diagonal = 0.0f;
  if (!pIn)
  {
    return 0;
  }
  m4x4[0] = pIn->mat[0];
  m4x4[1] = pIn->mat[3];
  m4x4[2] = pIn->mat[6];
  m4x4[4] = pIn->mat[1];
  m4x4[5] = pIn->mat[4];
  m4x4[6] = pIn->mat[7];
  m4x4[8] = pIn->mat[2];
  m4x4[9] = pIn->mat[5];
  m4x4[10] = pIn->mat[8];
  m4x4[15] = 1;
  pMatrix_idx = &m4x4[0];
  diagonal = ((pMatrix[0 + pMatrix_idx] + pMatrix[5 + pMatrix_idx]) + pMatrix[10 + pMatrix_idx]) + 1;
  if (diagonal > 0.0001)
  {
    scale = ((float) sqrt(diagonal)) * 2;
    x = (pMatrix[9 + pMatrix_idx] - pMatrix[6 + pMatrix_idx]) / scale;
    y = (pMatrix[2 + pMatrix_idx] - pMatrix[8 + pMatrix_idx]) / scale;
    z = (pMatrix[4 + pMatrix_idx] - pMatrix[1 + pMatrix_idx]) / scale;
    w = 0.25f * scale;
  }
  else
  {
    helper_kmQuaternionRotationMatrix_1(&x, &y, &z, &w, &scale, pMatrix, pMatrix_idx);
  }
  pOut->x = x;
  pOut->y = y;
  pOut->z = z;
  pOut->w = w;
  return pOut;
}


/*** DEPENDENCIES:
void helper_kmQuaternionRotationMatrix_1(float * const x_ref, float * const y_ref, float * const z_ref, float * const w_ref, float * const scale_ref, float * const pMatrix, unsigned int pMatrix_idx)
{
  float x = *x_ref;
  float y = *y_ref;
  float z = *z_ref;
  float w = *w_ref;
  float scale = *scale_ref;
  if ((pMatrix[0 + pMatrix_idx] > pMatrix[5 + pMatrix_idx]) && (pMatrix[0 + pMatrix_idx] > pMatrix[10 + pMatrix_idx]))
  {
    scale = ((float) sqrt(((1.0f + pMatrix[0 + pMatrix_idx]) - pMatrix[5 + pMatrix_idx]) - pMatrix[10 + pMatrix_idx])) * 2.0f;
    x = 0.25f * scale;
    y = (pMatrix[4 + pMatrix_idx] + pMatrix[1 + pMatrix_idx]) / scale;
    z = (pMatrix[2 + pMatrix_idx] + pMatrix[8 + pMatrix_idx]) / scale;
    w = (pMatrix[9 + pMatrix_idx] - pMatrix[6 + pMatrix_idx]) / scale;
  }
  else
    if (pMatrix[5 + pMatrix_idx] > pMatrix[10 + pMatrix_idx])
  {
    scale = ((float) sqrt(((1.0f + pMatrix[5 + pMatrix_idx]) - pMatrix[0 + pMatrix_idx]) - pMatrix[10 + pMatrix_idx])) * 2.0f;
    x = (pMatrix[4 + pMatrix_idx] + pMatrix[1 + pMatrix_idx]) / scale;
    y = 0.25f * scale;
    z = (pMatrix[9 + pMatrix_idx] + pMatrix[6 + pMatrix_idx]) / scale;
    w = (pMatrix[2 + pMatrix_idx] - pMatrix[8 + pMatrix_idx]) / scale;
  }
  else
  {
    scale = ((float) sqrt(((1.0f + pMatrix[10 + pMatrix_idx]) - pMatrix[0 + pMatrix_idx]) - pMatrix[5 + pMatrix_idx])) * 2.0f;
    x = (pMatrix[2 + pMatrix_idx] + pMatrix[8 + pMatrix_idx]) / scale;
    y = (pMatrix[9 + pMatrix_idx] + pMatrix[6 + pMatrix_idx]) / scale;
    z = 0.25f * scale;
    w = (pMatrix[4 + pMatrix_idx] - pMatrix[1 + pMatrix_idx]) / scale;
  }
  *x_ref = x;
  *y_ref = y;
  *z_ref = z;
  *w_ref = w;
  *scale_ref = scale;
}


----------------------------
typedef struct kmMat3
{
  float mat[9];
} kmMat3
----------------------------
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion
----------------------------
***/


void kmQuaternionToAxisAngle(const kmQuaternion *pIn, kmVec3 *pAxis, float *pAngle)
{
  float tempAngle;
  float scale;
  tempAngle = acosf(pIn->w);
  scale = sqrtf((kmSQR(pIn->x) + kmSQR(pIn->y)) + kmSQR(pIn->z));
  if (((scale > (-0.0001)) && (scale < 0.0001)) || ((scale < ((2 * 3.14159265358979323846f) + 0.0001)) && (scale > ((2 * 3.14159265358979323846f) - 0.0001))))
  {
    *pAngle = 0.0f;
    pAxis->x = 0.0f;
    pAxis->y = 0.0f;
    pAxis->z = 1.0f;
  }
  else
  {
    *pAngle = tempAngle * 2.0f;
    pAxis->x = pIn->x / scale;
    pAxis->y = pIn->y / scale;
    pAxis->z = pIn->z / scale;
    kmVec3Normalize(pAxis, pAxis);
  }
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
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion
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
***/


kmVec3 *kmQuaternionMultiplyVec3(kmVec3 *pOut, const kmQuaternion *q, const kmVec3 *v)
{
  kmVec3 uv;
  kmVec3 uuv;
  kmVec3 qvec;
  qvec.x = q->x;
  qvec.y = q->y;
  qvec.z = q->z;
  kmVec3Cross(&uv, &qvec, v);
  kmVec3Cross(&uuv, &qvec, &uv);
  kmVec3Scale(&uv, &uv, 2.0f * q->w);
  kmVec3Scale(&uuv, &uuv, 2.0f);
  kmVec3Add(pOut, v, &uv);
  kmVec3Add(pOut, pOut, &uuv);
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion
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


kmVec3 *kmQuaternionGetUpVec3(kmVec3 *pOut, const kmQuaternion *pIn)
{
  return kmQuaternionMultiplyVec3(pOut, pIn, &KM_VEC3_POS_Y);
}


/*** DEPENDENCIES:
kmVec3 *kmQuaternionMultiplyVec3(kmVec3 *pOut, const kmQuaternion *q, const kmVec3 *v)
{
  kmVec3 uv;
  kmVec3 uuv;
  kmVec3 qvec;
  qvec.x = q->x;
  qvec.y = q->y;
  qvec.z = q->z;
  kmVec3Cross(&uv, &qvec, v);
  kmVec3Cross(&uuv, &qvec, &uv);
  kmVec3Scale(&uv, &uv, 2.0f * q->w);
  kmVec3Scale(&uuv, &uuv, 2.0f);
  kmVec3Add(pOut, v, &uv);
  kmVec3Add(pOut, pOut, &uuv);
  return pOut;
}


----------------------------
extern const kmVec3 KM_VEC3_POS_Y
----------------------------
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion
----------------------------
***/


kmVec3 *kmQuaternionGetRightVec3(kmVec3 *pOut, const kmQuaternion *pIn)
{
  return kmQuaternionMultiplyVec3(pOut, pIn, &KM_VEC3_POS_X);
}


/*** DEPENDENCIES:
kmVec3 *kmQuaternionMultiplyVec3(kmVec3 *pOut, const kmQuaternion *q, const kmVec3 *v)
{
  kmVec3 uv;
  kmVec3 uuv;
  kmVec3 qvec;
  qvec.x = q->x;
  qvec.y = q->y;
  qvec.z = q->z;
  kmVec3Cross(&uv, &qvec, v);
  kmVec3Cross(&uuv, &qvec, &uv);
  kmVec3Scale(&uv, &uv, 2.0f * q->w);
  kmVec3Scale(&uuv, &uuv, 2.0f);
  kmVec3Add(pOut, v, &uv);
  kmVec3Add(pOut, pOut, &uuv);
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
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion
----------------------------
extern const kmVec3 KM_VEC3_POS_X
----------------------------
***/


kmVec3 *kmQuaternionGetForwardVec3RH(kmVec3 *pOut, const kmQuaternion *pIn)
{
  return kmQuaternionMultiplyVec3(pOut, pIn, &KM_VEC3_NEG_Z);
}


/*** DEPENDENCIES:
kmVec3 *kmQuaternionMultiplyVec3(kmVec3 *pOut, const kmQuaternion *q, const kmVec3 *v)
{
  kmVec3 uv;
  kmVec3 uuv;
  kmVec3 qvec;
  qvec.x = q->x;
  qvec.y = q->y;
  qvec.z = q->z;
  kmVec3Cross(&uv, &qvec, v);
  kmVec3Cross(&uuv, &qvec, &uv);
  kmVec3Scale(&uv, &uv, 2.0f * q->w);
  kmVec3Scale(&uuv, &uuv, 2.0f);
  kmVec3Add(pOut, v, &uv);
  kmVec3Add(pOut, pOut, &uuv);
  return pOut;
}


----------------------------
extern const kmVec3 KM_VEC3_NEG_Z
----------------------------
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion
----------------------------
***/


kmVec3 *kmQuaternionGetForwardVec3LH(kmVec3 *pOut, const kmQuaternion *pIn)
{
  return kmQuaternionMultiplyVec3(pOut, pIn, &KM_VEC3_POS_Z);
}


/*** DEPENDENCIES:
extern const kmVec3 KM_VEC3_POS_Z
----------------------------
kmVec3 *kmQuaternionMultiplyVec3(kmVec3 *pOut, const kmQuaternion *q, const kmVec3 *v)
{
  kmVec3 uv;
  kmVec3 uuv;
  kmVec3 qvec;
  qvec.x = q->x;
  qvec.y = q->y;
  qvec.z = q->z;
  kmVec3Cross(&uv, &qvec, v);
  kmVec3Cross(&uuv, &qvec, &uv);
  kmVec3Scale(&uv, &uv, 2.0f * q->w);
  kmVec3Scale(&uuv, &uuv, 2.0f);
  kmVec3Add(pOut, v, &uv);
  kmVec3Add(pOut, pOut, &uuv);
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
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion
----------------------------
***/


void helper_kmQuaternionRotationBetweenVec3_1(kmQuaternion * const pOut, const kmVec3 * const vec1, const kmVec3 * const fallback)
{
  if (fabs(kmVec3LengthSq(fallback)) < 0.0001)
  {
    kmQuaternionRotationAxisAngle(pOut, fallback, 3.14159265358979323846f);
  }
  else
  {
    kmVec3 axis;
    kmVec3 X;
    X.x = 1.0;
    X.y = 0.0;
    X.z = 0.0;
    kmVec3Cross(&axis, &X, vec1);
    if (fabs(kmVec3LengthSq(&axis)) < 0.0001)
    {
      kmVec3 Y;
      Y.x = 0.0;
      Y.y = 1.0;
      Y.z = 0.0;
      kmVec3Cross(&axis, &Y, vec1);
    }
    kmVec3Normalize(&axis, &axis);
    kmQuaternionRotationAxisAngle(pOut, &axis, 3.14159265358979323846f);
  }
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
kmQuaternion *kmQuaternionRotationAxisAngle(kmQuaternion *pOut, const kmVec3 *pV, float angle)
{
  float rad = angle * 0.5f;
  float scale = sinf(rad);
  pOut->x = pV->x * scale;
  pOut->y = pV->y * scale;
  pOut->z = pV->z * scale;
  pOut->w = cosf(rad);
  kmQuaternionNormalize(pOut, pOut);
  return pOut;
}


----------------------------
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion
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
float kmVec3LengthSq(const kmVec3 *pIn)
{
  return (kmSQR(pIn->x) + kmSQR(pIn->y)) + kmSQR(pIn->z);
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


kmQuaternion *kmQuaternionSlerp(kmQuaternion *pOut, const kmQuaternion *q1, const kmQuaternion *q2, float t)
{
  float dot = kmQuaternionDot(q1, q2);
  const double DOT_THRESHOLD = 0.9995;
  if (dot > DOT_THRESHOLD)
  {
    kmQuaternion diff;
    kmQuaternionSubtract(&diff, q2, q1);
    kmQuaternionScale(&diff, &diff, t);
    kmQuaternionAdd(pOut, q1, &diff);
    kmQuaternionNormalize(pOut, pOut);
    return pOut;
  }
  dot = kmClamp(dot, -1, 1);
  float theta_0 = acos(dot);
  float theta = theta_0 * t;
  kmQuaternion tmp;
  kmQuaternionScale(&tmp, q1, dot);
  kmQuaternionSubtract(&tmp, q2, &tmp);
  kmQuaternionNormalize(&tmp, &tmp);
  kmQuaternion t1;
  kmQuaternion t2;
  kmQuaternionScale(&t1, q1, cos(theta));
  kmQuaternionScale(&t2, &tmp, sin(theta));
  kmQuaternionAdd(pOut, &t1, &t2);
  return pOut;
}


/*** DEPENDENCIES:
kmQuaternion *kmQuaternionSubtract(kmQuaternion *pOut, const kmQuaternion *pQ1, const kmQuaternion *pQ2)
{
  pOut->x = pQ1->x - pQ2->x;
  pOut->y = pQ1->y - pQ2->y;
  pOut->z = pQ1->z - pQ2->z;
  pOut->w = pQ1->w - pQ2->w;
  return pOut;
}


----------------------------
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion
----------------------------
kmQuaternion *kmQuaternionAdd(kmQuaternion *pOut, const kmQuaternion *pQ1, const kmQuaternion *pQ2)
{
  pOut->x = pQ1->x + pQ2->x;
  pOut->y = pQ1->y + pQ2->y;
  pOut->z = pQ1->z + pQ2->z;
  pOut->w = pQ1->w + pQ2->w;
  return pOut;
}


----------------------------
float kmQuaternionDot(const kmQuaternion *q1, const kmQuaternion *q2)
{
  return (((q1->w * q2->w) + (q1->x * q2->x)) + (q1->y * q2->y)) + (q1->z * q2->z);
}


----------------------------
kmQuaternion *kmQuaternionScale(kmQuaternion *pOut, const kmQuaternion *pIn, float s)
{
  pOut->x = pIn->x * s;
  pOut->y = pIn->y * s;
  pOut->z = pIn->z * s;
  pOut->w = pIn->w * s;
  return pOut;
}


----------------------------
float kmClamp(float x, float min, float max)
{
  return (x < min) ? (min) : ((x > max) ? (max) : (x));
}


----------------------------
kmQuaternion *kmQuaternionNormalize(kmQuaternion *pOut, const kmQuaternion *pIn)
{
  float length = kmQuaternionLength(pIn);
  if (fabs(length) < 0.0001)
  {
    pOut->x = 0.0;
    pOut->y = 0.0;
    pOut->z = 0.0;
    pOut->w = 0.0;
    return pOut;
  }
  kmQuaternionFill(pOut, pOut->x / length, pOut->y / length, pOut->z / length, pOut->w / length);
  return pOut;
}


----------------------------
***/


kmQuaternion *kmQuaternionLookRotation(kmQuaternion *pOut, const kmVec3 *direction, const kmVec3 *up)
{
  kmMat3 tmp;
  kmMat3LookAt(&tmp, &KM_VEC3_ZERO, direction, up);
  return kmQuaternionNormalize(pOut, kmQuaternionRotationMatrix(pOut, &tmp));
}


/*** DEPENDENCIES:
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion
----------------------------
extern const kmVec3 KM_VEC3_ZERO
----------------------------
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
kmQuaternion *kmQuaternionRotationMatrix(kmQuaternion *pOut, const kmMat3 *pIn)
{
  float x;
  float y;
  float z;
  float w;
  float *pMatrix = 0;
  unsigned int pMatrix_idx = 0;
  float m4x4[16] = {0};
  float scale = 0.0f;
  float diagonal = 0.0f;
  if (!pIn)
  {
    return 0;
  }
  m4x4[0] = pIn->mat[0];
  m4x4[1] = pIn->mat[3];
  m4x4[2] = pIn->mat[6];
  m4x4[4] = pIn->mat[1];
  m4x4[5] = pIn->mat[4];
  m4x4[6] = pIn->mat[7];
  m4x4[8] = pIn->mat[2];
  m4x4[9] = pIn->mat[5];
  m4x4[10] = pIn->mat[8];
  m4x4[15] = 1;
  pMatrix_idx = &m4x4[0];
  diagonal = ((pMatrix[0 + pMatrix_idx] + pMatrix[5 + pMatrix_idx]) + pMatrix[10 + pMatrix_idx]) + 1;
  if (diagonal > 0.0001)
  {
    scale = ((float) sqrt(diagonal)) * 2;
    x = (pMatrix[9 + pMatrix_idx] - pMatrix[6 + pMatrix_idx]) / scale;
    y = (pMatrix[2 + pMatrix_idx] - pMatrix[8 + pMatrix_idx]) / scale;
    z = (pMatrix[4 + pMatrix_idx] - pMatrix[1 + pMatrix_idx]) / scale;
    w = 0.25f * scale;
  }
  else
  {
    helper_kmQuaternionRotationMatrix_1(&x, &y, &z, &w, &scale, pMatrix, pMatrix_idx);
  }
  pOut->x = x;
  pOut->y = y;
  pOut->z = z;
  pOut->w = w;
  return pOut;
}


----------------------------
kmMat3 *kmMat3LookAt(kmMat3 *pOut, const kmVec3 *pEye, const kmVec3 *pCenter, const kmVec3 *pUp)
{
  kmVec3 f;
  kmVec3 up;
  kmVec3 s;
  kmVec3 u;
  kmVec3Subtract(&f, pCenter, pEye);
  kmVec3Normalize(&f, &f);
  kmVec3Assign(&up, pUp);
  kmVec3Normalize(&up, &up);
  kmVec3Cross(&s, &f, &up);
  kmVec3Normalize(&s, &s);
  kmVec3Cross(&u, &s, &f);
  kmVec3Normalize(&s, &s);
  pOut->mat[0] = s.x;
  pOut->mat[3] = s.y;
  pOut->mat[6] = s.z;
  pOut->mat[1] = u.x;
  pOut->mat[4] = u.y;
  pOut->mat[7] = u.z;
  pOut->mat[2] = -f.x;
  pOut->mat[5] = -f.y;
  pOut->mat[8] = -f.z;
  return pOut;
}


----------------------------
typedef struct kmMat3
{
  float mat[9];
} kmMat3
----------------------------
kmQuaternion *kmQuaternionNormalize(kmQuaternion *pOut, const kmQuaternion *pIn)
{
  float length = kmQuaternionLength(pIn);
  if (fabs(length) < 0.0001)
  {
    pOut->x = 0.0;
    pOut->y = 0.0;
    pOut->z = 0.0;
    pOut->w = 0.0;
    return pOut;
  }
  kmQuaternionFill(pOut, pOut->x / length, pOut->y / length, pOut->z / length, pOut->w / length);
  return pOut;
}


----------------------------
***/


kmQuaternion *kmQuaternionRotationBetweenVec3(kmQuaternion *pOut, const kmVec3 *vec1, const kmVec3 *vec2, const kmVec3 *fallback)
{
  kmVec3 v1;
  kmVec3 v2;
  float a;
  kmVec3Assign(&v1, vec1);
  kmVec3Assign(&v2, vec2);
  kmVec3Normalize(&v1, &v1);
  kmVec3Normalize(&v2, &v2);
  a = kmVec3Dot(&v1, &v2);
  if (a >= 1.0)
  {
    kmQuaternionIdentity(pOut);
    return pOut;
  }
  if (a < (1e-6f - 1.0f))
  {
    helper_kmQuaternionRotationBetweenVec3_1(pOut, vec1, fallback);
  }
  else
  {
    float s = sqrtf((1 + a) * 2);
    float invs = 1 / s;
    kmVec3 c;
    kmVec3Cross(&c, &v1, &v2);
    pOut->x = c.x * invs;
    pOut->y = c.y * invs;
    pOut->z = c.z * invs;
    pOut->w = s * 0.5f;
    kmQuaternionNormalize(pOut, pOut);
  }
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
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion
----------------------------
void helper_kmQuaternionRotationBetweenVec3_1(kmQuaternion * const pOut, const kmVec3 * const vec1, const kmVec3 * const fallback)
{
  if (fabs(kmVec3LengthSq(fallback)) < 0.0001)
  {
    kmQuaternionRotationAxisAngle(pOut, fallback, 3.14159265358979323846f);
  }
  else
  {
    kmVec3 axis;
    kmVec3 X;
    X.x = 1.0;
    X.y = 0.0;
    X.z = 0.0;
    kmVec3Cross(&axis, &X, vec1);
    if (fabs(kmVec3LengthSq(&axis)) < 0.0001)
    {
      kmVec3 Y;
      Y.x = 0.0;
      Y.y = 1.0;
      Y.z = 0.0;
      kmVec3Cross(&axis, &Y, vec1);
    }
    kmVec3Normalize(&axis, &axis);
    kmQuaternionRotationAxisAngle(pOut, &axis, 3.14159265358979323846f);
  }
}


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
kmQuaternion *kmQuaternionIdentity(kmQuaternion *pOut)
{
  pOut->x = 0.0;
  pOut->y = 0.0;
  pOut->z = 0.0;
  pOut->w = 1.0;
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
kmQuaternion *kmQuaternionNormalize(kmQuaternion *pOut, const kmQuaternion *pIn)
{
  float length = kmQuaternionLength(pIn);
  if (fabs(length) < 0.0001)
  {
    pOut->x = 0.0;
    pOut->y = 0.0;
    pOut->z = 0.0;
    pOut->w = 0.0;
    return pOut;
  }
  kmQuaternionFill(pOut, pOut->x / length, pOut->y / length, pOut->z / length, pOut->w / length);
  return pOut;
}


----------------------------
***/


