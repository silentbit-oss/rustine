kmMat3 *kmMat3Fill(kmMat3 *pOut, const float *pMat)
{
  memcpy(pOut->mat, pMat, (sizeof(float)) * 9);
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmMat3
{
  float mat[9];
} kmMat3
----------------------------
***/


kmMat3 *kmMat3Adjugate(kmMat3 *pOut, const kmMat3 *pIn)
{
  pOut->mat[0] = (pIn->mat[4] * pIn->mat[8]) - (pIn->mat[5] * pIn->mat[7]);
  pOut->mat[1] = (pIn->mat[2] * pIn->mat[7]) - (pIn->mat[1] * pIn->mat[8]);
  pOut->mat[2] = (pIn->mat[1] * pIn->mat[5]) - (pIn->mat[2] * pIn->mat[4]);
  pOut->mat[3] = (pIn->mat[5] * pIn->mat[6]) - (pIn->mat[3] * pIn->mat[8]);
  pOut->mat[4] = (pIn->mat[0] * pIn->mat[8]) - (pIn->mat[2] * pIn->mat[6]);
  pOut->mat[5] = (pIn->mat[2] * pIn->mat[3]) - (pIn->mat[0] * pIn->mat[5]);
  pOut->mat[6] = (pIn->mat[3] * pIn->mat[7]) - (pIn->mat[4] * pIn->mat[6]);
  pOut->mat[7] = (pIn->mat[1] * pIn->mat[6]) - (pIn->mat[0] * pIn->mat[7]);
  pOut->mat[8] = (pIn->mat[0] * pIn->mat[4]) - (pIn->mat[1] * pIn->mat[3]);
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmMat3
{
  float mat[9];
} kmMat3
----------------------------
***/


kmMat3 *kmMat3Identity(kmMat3 *pOut)
{
  memset(pOut->mat, 0, (sizeof(float)) * 9);
  pOut->mat[0] = (pOut->mat[4] = (pOut->mat[8] = 1.0f));
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmMat3
{
  float mat[9];
} kmMat3
----------------------------
***/


int kmMat3IsIdentity(const kmMat3 *pIn)
{
  static float identity[] = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};
  return memcmp(identity, pIn->mat, (sizeof(float)) * 9) == 0;
}


/*** DEPENDENCIES:
typedef struct kmMat3
{
  float mat[9];
} kmMat3
----------------------------
***/


kmMat3 *kmMat3Transpose(kmMat3 *pOut, const kmMat3 *pIn)
{
  float temp[9];
  temp[0] = pIn->mat[0];
  temp[1] = pIn->mat[3];
  temp[2] = pIn->mat[6];
  temp[3] = pIn->mat[1];
  temp[4] = pIn->mat[4];
  temp[5] = pIn->mat[7];
  temp[6] = pIn->mat[2];
  temp[7] = pIn->mat[5];
  temp[8] = pIn->mat[8];
  memcpy(&pOut->mat, temp, (sizeof(float)) * 9);
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmMat3
{
  float mat[9];
} kmMat3
----------------------------
***/


float kmMat3Determinant(const kmMat3 *pIn)
{
  float output;
  output = (((pIn->mat[0] * pIn->mat[4]) * pIn->mat[8]) + ((pIn->mat[1] * pIn->mat[5]) * pIn->mat[6])) + ((pIn->mat[2] * pIn->mat[3]) * pIn->mat[7]);
  output -= (((pIn->mat[2] * pIn->mat[4]) * pIn->mat[6]) + ((pIn->mat[0] * pIn->mat[5]) * pIn->mat[7])) + ((pIn->mat[1] * pIn->mat[3]) * pIn->mat[8]);
  return output;
}


/*** DEPENDENCIES:
typedef struct kmMat3
{
  float mat[9];
} kmMat3
----------------------------
***/


kmMat3 *kmMat3Multiply(kmMat3 *pOut, const kmMat3 *pM1, const kmMat3 *pM2)
{
  float mat[9];
  const float *m1 = pM1->mat;
  const float *m2 = pM2->mat;
  mat[0] = ((m1[0] * m2[0]) + (m1[3] * m2[1])) + (m1[6] * m2[2]);
  mat[1] = ((m1[1] * m2[0]) + (m1[4] * m2[1])) + (m1[7] * m2[2]);
  mat[2] = ((m1[2] * m2[0]) + (m1[5] * m2[1])) + (m1[8] * m2[2]);
  mat[3] = ((m1[0] * m2[3]) + (m1[3] * m2[4])) + (m1[6] * m2[5]);
  mat[4] = ((m1[1] * m2[3]) + (m1[4] * m2[4])) + (m1[7] * m2[5]);
  mat[5] = ((m1[2] * m2[3]) + (m1[5] * m2[4])) + (m1[8] * m2[5]);
  mat[6] = ((m1[0] * m2[6]) + (m1[3] * m2[7])) + (m1[6] * m2[8]);
  mat[7] = ((m1[1] * m2[6]) + (m1[4] * m2[7])) + (m1[7] * m2[8]);
  mat[8] = ((m1[2] * m2[6]) + (m1[5] * m2[7])) + (m1[8] * m2[8]);
  memcpy(pOut->mat, mat, (sizeof(float)) * 9);
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmMat3
{
  float mat[9];
} kmMat3
----------------------------
***/


kmMat3 *kmMat3ScalarMultiply(kmMat3 *pOut, const kmMat3 *pM, const float pFactor)
{
  float mat[9];
  int i;
  for (i = 0; i < 9; i += 1)
  {
    mat[i] = pM->mat[i] * pFactor;
  }

  memcpy(pOut->mat, mat, (sizeof(float)) * 9);
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmMat3
{
  float mat[9];
} kmMat3
----------------------------
***/


kmMat3 *kmMat3Assign(kmMat3 *pOut, const kmMat3 *pIn)
{
  assert(pOut != pIn);
  memcpy(pOut->mat, pIn->mat, (sizeof(float)) * 9);
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmMat3
{
  float mat[9];
} kmMat3
----------------------------
***/


int kmMat3AreEqual(const kmMat3 *pMat1, const kmMat3 *pMat2)
{
  int i;
  if (pMat1 == pMat2)
  {
    return 1;
  }
  for (i = 0; i < 9; i += 1)
  {
    if (!(((pMat1->mat[i] + 0.0001) > pMat2->mat[i]) && ((pMat1->mat[i] - 0.0001) < pMat2->mat[i])))
    {
      return 0;
    }
  }

  return 1;
}


/*** DEPENDENCIES:
typedef struct kmMat3
{
  float mat[9];
} kmMat3
----------------------------
***/


kmMat3 *kmMat3RotationX(kmMat3 *pOut, const float radians)
{
  pOut->mat[0] = 1.0f;
  pOut->mat[1] = 0.0f;
  pOut->mat[2] = 0.0f;
  pOut->mat[3] = 0.0f;
  pOut->mat[4] = cosf(radians);
  pOut->mat[5] = sinf(radians);
  pOut->mat[6] = 0.0f;
  pOut->mat[7] = -sinf(radians);
  pOut->mat[8] = cosf(radians);
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmMat3
{
  float mat[9];
} kmMat3
----------------------------
***/


kmMat3 *kmMat3RotationY(kmMat3 *pOut, const float radians)
{
  pOut->mat[0] = cosf(radians);
  pOut->mat[1] = 0.0f;
  pOut->mat[2] = -sinf(radians);
  pOut->mat[3] = 0.0f;
  pOut->mat[4] = 1.0f;
  pOut->mat[5] = 0.0f;
  pOut->mat[6] = sinf(radians);
  pOut->mat[7] = 0.0f;
  pOut->mat[8] = cosf(radians);
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmMat3
{
  float mat[9];
} kmMat3
----------------------------
***/


kmMat3 *kmMat3RotationZ(kmMat3 *pOut, const float radians)
{
  pOut->mat[0] = cosf(radians);
  pOut->mat[1] = -sinf(radians);
  pOut->mat[2] = 0.0f;
  pOut->mat[3] = sinf(radians);
  pOut->mat[4] = cosf(radians);
  pOut->mat[5] = 0.0f;
  pOut->mat[6] = 0.0f;
  pOut->mat[7] = 0.0f;
  pOut->mat[8] = 1.0f;
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmMat3
{
  float mat[9];
} kmMat3
----------------------------
***/


kmMat3 *kmMat3Rotation(kmMat3 *pOut, const float radians)
{
  pOut->mat[0] = cosf(radians);
  pOut->mat[1] = sinf(radians);
  pOut->mat[2] = 0.0f;
  pOut->mat[3] = -sinf(radians);
  pOut->mat[4] = cosf(radians);
  pOut->mat[5] = 0.0f;
  pOut->mat[6] = 0.0f;
  pOut->mat[7] = 0.0f;
  pOut->mat[8] = 1.0f;
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmMat3
{
  float mat[9];
} kmMat3
----------------------------
***/


kmMat3 *kmMat3AssignMat4(kmMat3 *pOut, const kmMat4 *pIn)
{
  pOut->mat[0] = pIn->mat[0];
  pOut->mat[1] = pIn->mat[1];
  pOut->mat[2] = pIn->mat[2];
  pOut->mat[3] = pIn->mat[4];
  pOut->mat[4] = pIn->mat[5];
  pOut->mat[5] = pIn->mat[6];
  pOut->mat[6] = pIn->mat[8];
  pOut->mat[7] = pIn->mat[9];
  pOut->mat[8] = pIn->mat[10];
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmMat3
{
  float mat[9];
} kmMat3
----------------------------
typedef struct kmMat4
{
  float mat[16];
} kmMat4
----------------------------
***/


kmMat3 *kmMat3Scaling(kmMat3 *pOut, const float x, const float y)
{
  kmMat3Identity(pOut);
  pOut->mat[0] = x;
  pOut->mat[4] = y;
  return pOut;
}


/*** DEPENDENCIES:
kmMat3 *kmMat3Identity(kmMat3 *pOut)
{
  memset(pOut->mat, 0, (sizeof(float)) * 9);
  pOut->mat[0] = (pOut->mat[4] = (pOut->mat[8] = 1.0f));
  return pOut;
}


----------------------------
typedef struct kmMat3
{
  float mat[9];
} kmMat3
----------------------------
***/


kmMat3 *kmMat3Translation(kmMat3 *pOut, const float x, const float y)
{
  kmMat3Identity(pOut);
  pOut->mat[6] = x;
  pOut->mat[7] = y;
  return pOut;
}


/*** DEPENDENCIES:
kmMat3 *kmMat3Identity(kmMat3 *pOut)
{
  memset(pOut->mat, 0, (sizeof(float)) * 9);
  pOut->mat[0] = (pOut->mat[4] = (pOut->mat[8] = 1.0f));
  return pOut;
}


----------------------------
typedef struct kmMat3
{
  float mat[9];
} kmMat3
----------------------------
***/


kmMat3 *kmMat3RotationQuaternion(kmMat3 *pOut, const kmQuaternion *pIn)
{
  if ((!pIn) || (!pOut))
  {
    return 0;
  }
  pOut->mat[0] = 1.0f - (2.0f * ((pIn->y * pIn->y) + (pIn->z * pIn->z)));
  pOut->mat[1] = 2.0f * ((pIn->x * pIn->y) - (pIn->w * pIn->z));
  pOut->mat[2] = 2.0f * ((pIn->x * pIn->z) + (pIn->w * pIn->y));
  pOut->mat[3] = 2.0f * ((pIn->x * pIn->y) + (pIn->w * pIn->z));
  pOut->mat[4] = 1.0f - (2.0f * ((pIn->x * pIn->x) + (pIn->z * pIn->z)));
  pOut->mat[5] = 2.0f * ((pIn->y * pIn->z) - (pIn->w * pIn->x));
  pOut->mat[6] = 2.0f * ((pIn->x * pIn->z) - (pIn->w * pIn->y));
  pOut->mat[7] = 2.0f * ((pIn->y * pIn->z) + (pIn->w * pIn->x));
  pOut->mat[8] = 1.0f - (2.0f * ((pIn->x * pIn->x) + (pIn->y * pIn->y)));
  return pOut;
}


/*** DEPENDENCIES:
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


kmMat3 *kmMat3RotationAxisAngle(kmMat3 *pOut, const struct kmVec3 *axis, float radians)
{
  float rcos = cosf(radians);
  float rsin = sinf(radians);
  pOut->mat[0] = rcos + ((axis->x * axis->x) * (1 - rcos));
  pOut->mat[1] = (axis->z * rsin) + ((axis->y * axis->x) * (1 - rcos));
  pOut->mat[2] = ((-axis->y) * rsin) + ((axis->z * axis->x) * (1 - rcos));
  pOut->mat[3] = ((-axis->z) * rsin) + ((axis->x * axis->y) * (1 - rcos));
  pOut->mat[4] = rcos + ((axis->y * axis->y) * (1 - rcos));
  pOut->mat[5] = (axis->x * rsin) + ((axis->z * axis->y) * (1 - rcos));
  pOut->mat[6] = (axis->y * rsin) + ((axis->x * axis->z) * (1 - rcos));
  pOut->mat[7] = ((-axis->x) * rsin) + ((axis->y * axis->z) * (1 - rcos));
  pOut->mat[8] = rcos + ((axis->z * axis->z) * (1 - rcos));
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


kmVec3 *kmMat3GetUpVec3(kmVec3 *pOut, const kmMat3 *pIn)
{
  pOut->x = pIn->mat[3];
  pOut->y = pIn->mat[4];
  pOut->z = pIn->mat[5];
  kmVec3Normalize(pOut, pOut);
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


kmVec3 *kmMat3GetRightVec3(kmVec3 *pOut, const kmMat3 *pIn)
{
  pOut->x = pIn->mat[0];
  pOut->y = pIn->mat[1];
  pOut->z = pIn->mat[2];
  kmVec3Normalize(pOut, pOut);
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


kmVec3 *kmMat3GetForwardVec3(kmVec3 *pOut, const kmMat3 *pIn)
{
  pOut->x = pIn->mat[6];
  pOut->y = pIn->mat[7];
  pOut->z = pIn->mat[8];
  kmVec3Normalize(pOut, pOut);
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


kmMat3 *kmMat3Inverse(kmMat3 *pOut, const kmMat3 *pM)
{
  float determinate = kmMat3Determinant(pM);
  float detInv;
  kmMat3 adjugate;
  if (determinate == 0.0)
  {
    return 0;
  }
  detInv = 1.0 / determinate;
  kmMat3Adjugate(&adjugate, pM);
  kmMat3ScalarMultiply(pOut, &adjugate, detInv);
  return pOut;
}


/*** DEPENDENCIES:
kmMat3 *kmMat3ScalarMultiply(kmMat3 *pOut, const kmMat3 *pM, const float pFactor)
{
  float mat[9];
  int i;
  for (i = 0; i < 9; i += 1)
  {
    mat[i] = pM->mat[i] * pFactor;
  }

  memcpy(pOut->mat, mat, (sizeof(float)) * 9);
  return pOut;
}


----------------------------
float kmMat3Determinant(const kmMat3 *pIn)
{
  float output;
  output = (((pIn->mat[0] * pIn->mat[4]) * pIn->mat[8]) + ((pIn->mat[1] * pIn->mat[5]) * pIn->mat[6])) + ((pIn->mat[2] * pIn->mat[3]) * pIn->mat[7]);
  output -= (((pIn->mat[2] * pIn->mat[4]) * pIn->mat[6]) + ((pIn->mat[0] * pIn->mat[5]) * pIn->mat[7])) + ((pIn->mat[1] * pIn->mat[3]) * pIn->mat[8]);
  return output;
}


----------------------------
kmMat3 *kmMat3Adjugate(kmMat3 *pOut, const kmMat3 *pIn)
{
  pOut->mat[0] = (pIn->mat[4] * pIn->mat[8]) - (pIn->mat[5] * pIn->mat[7]);
  pOut->mat[1] = (pIn->mat[2] * pIn->mat[7]) - (pIn->mat[1] * pIn->mat[8]);
  pOut->mat[2] = (pIn->mat[1] * pIn->mat[5]) - (pIn->mat[2] * pIn->mat[4]);
  pOut->mat[3] = (pIn->mat[5] * pIn->mat[6]) - (pIn->mat[3] * pIn->mat[8]);
  pOut->mat[4] = (pIn->mat[0] * pIn->mat[8]) - (pIn->mat[2] * pIn->mat[6]);
  pOut->mat[5] = (pIn->mat[2] * pIn->mat[3]) - (pIn->mat[0] * pIn->mat[5]);
  pOut->mat[6] = (pIn->mat[3] * pIn->mat[7]) - (pIn->mat[4] * pIn->mat[6]);
  pOut->mat[7] = (pIn->mat[1] * pIn->mat[6]) - (pIn->mat[0] * pIn->mat[7]);
  pOut->mat[8] = (pIn->mat[0] * pIn->mat[4]) - (pIn->mat[1] * pIn->mat[3]);
  return pOut;
}


----------------------------
typedef struct kmMat3
{
  float mat[9];
} kmMat3
----------------------------
***/


kmVec3 *kmMat3RotationToAxisAngle(kmVec3 *pAxis, float *radians, const kmMat3 *pIn)
{
  kmQuaternion temp;
  kmQuaternionRotationMatrix(&temp, pIn);
  kmQuaternionToAxisAngle(&temp, pAxis, radians);
  return pAxis;
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
typedef struct kmMat3
{
  float mat[9];
} kmMat3
----------------------------
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


----------------------------
***/


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
typedef struct kmMat3
{
  float mat[9];
} kmMat3
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


