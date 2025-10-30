#include <assert.h>
#include <mat3.c>
#include <mat3.h>
#include <mat4.h>
#include <math.h>
#include <memory.h>
#include <quaternion.h>
#include <stdlib.h>
#include <utility.h>
#include <vec3.h>

extern float kmSQR(float s);
extern float kmDegreesToRadians(float degrees);
extern float kmRadiansToDegrees(float radians);
extern float kmMin(float lhs, float rhs);
extern float kmMax(float lhs, float rhs);
extern unsigned char kmAlmostEqual(float lhs, float rhs);
extern float kmClamp(float x, float min, float max);
extern float kmLerp(float x, float y, float factor);
struct kmMat4;
struct kmMat3;
struct kmPlane;
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3;
kmVec3 *kmVec3Fill(kmVec3 *pOut, float x, float y, float z);
float kmVec3Length(const kmVec3 *pIn);
float kmVec3LengthSq(const kmVec3 *pIn);
kmVec3 *kmVec3Lerp(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2, float t);
kmVec3 *kmVec3Normalize(kmVec3 *pOut, const kmVec3 *pIn);
kmVec3 *kmVec3Cross(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2);
float kmVec3Dot(const kmVec3 *pV1, const kmVec3 *pV2);
kmVec3 *kmVec3Add(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2);
kmVec3 *kmVec3Subtract(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2);
kmVec3 *kmVec3Mul(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2);
kmVec3 *kmVec3Div(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2);
kmVec3 *kmVec3MultiplyMat3(kmVec3 *pOut, const kmVec3 *pV, const struct kmMat3 *pM);
kmVec3 *kmVec3MultiplyMat4(kmVec3 *pOut, const kmVec3 *pV, const struct kmMat4 *pM);
kmVec3 *kmVec3Transform(kmVec3 *pOut, const kmVec3 *pV1, const struct kmMat4 *pM);
kmVec3 *kmVec3TransformNormal(kmVec3 *pOut, const kmVec3 *pV, const struct kmMat4 *pM);
kmVec3 *kmVec3TransformCoord(kmVec3 *pOut, const kmVec3 *pV, const struct kmMat4 *pM);
kmVec3 *kmVec3Scale(kmVec3 *pOut, const kmVec3 *pIn, const float s);
int kmVec3AreEqual(const kmVec3 *p1, const kmVec3 *p2);
kmVec3 *kmVec3InverseTransform(kmVec3 *pOut, const kmVec3 *pV, const struct kmMat4 *pM);
kmVec3 *kmVec3InverseTransformNormal(kmVec3 *pOut, const kmVec3 *pVect, const struct kmMat4 *pM);
kmVec3 *kmVec3Assign(kmVec3 *pOut, const kmVec3 *pIn);
kmVec3 *kmVec3Zero(kmVec3 *pOut);
kmVec3 *kmVec3GetHorizontalAngle(kmVec3 *pOut, const kmVec3 *pIn);
kmVec3 *kmVec3RotationToDirection(kmVec3 *pOut, const kmVec3 *pIn, const kmVec3 *forwards);
kmVec3 *kmVec3ProjectOnToPlane(kmVec3 *pOut, const kmVec3 *point, const struct kmPlane *plane);
kmVec3 *kmVec3Reflect(kmVec3 *pOut, const kmVec3 *pIn, const kmVec3 *normal);
extern const kmVec3 KM_VEC3_NEG_Z;
extern const kmVec3 KM_VEC3_POS_Z;
extern const kmVec3 KM_VEC3_POS_Y;
extern const kmVec3 KM_VEC3_NEG_Y;
extern const kmVec3 KM_VEC3_NEG_X;
extern const kmVec3 KM_VEC3_POS_X;
extern const kmVec3 KM_VEC3_ZERO;
struct kmVec3;
struct kmQuaternion;
struct kmMat4;
typedef struct kmMat3
{
  float mat[9];
} kmMat3;
kmMat3 *kmMat3Fill(kmMat3 *pOut, const float *pMat);
kmMat3 *kmMat3Adjugate(kmMat3 *pOut, const kmMat3 *pIn);
kmMat3 *kmMat3Identity(kmMat3 *pOut);
kmMat3 *kmMat3Inverse(kmMat3 *pOut, const kmMat3 *pM);
int kmMat3IsIdentity(const kmMat3 *pIn);
kmMat3 *kmMat3Transpose(kmMat3 *pOut, const kmMat3 *pIn);
float kmMat3Determinant(const kmMat3 *pIn);
kmMat3 *kmMat3Multiply(kmMat3 *pOut, const kmMat3 *pM1, const kmMat3 *pM2);
kmMat3 *kmMat3ScalarMultiply(kmMat3 *pOut, const kmMat3 *pM, const float pFactor);
kmMat3 *kmMat3Assign(kmMat3 *pOut, const kmMat3 *pIn);
kmMat3 *kmMat3AssignMat4(kmMat3 *pOut, const struct kmMat4 *pIn);
int kmMat3AreEqual(const kmMat3 *pM1, const kmMat3 *pM2);
struct kmVec3 *kmMat3GetUpVec3(struct kmVec3 *pOut, const kmMat3 *pIn);
struct kmVec3 *kmMat3GetRightVec3(struct kmVec3 *pOut, const kmMat3 *pIn);
struct kmVec3 *kmMat3GetForwardVec3(struct kmVec3 *pOut, const kmMat3 *pIn);
kmMat3 *kmMat3RotationX(kmMat3 *pOut, const float radians);
kmMat3 *kmMat3RotationY(kmMat3 *pOut, const float radians);
kmMat3 *kmMat3RotationZ(kmMat3 *pOut, const float radians);
kmMat3 *kmMat3Rotation(kmMat3 *pOut, const float radians);
kmMat3 *kmMat3Scaling(kmMat3 *pOut, const float x, const float y);
kmMat3 *kmMat3Translation(kmMat3 *pOut, const float x, const float y);
kmMat3 *kmMat3RotationQuaternion(kmMat3 *pOut, const struct kmQuaternion *pIn);
kmMat3 *kmMat3RotationAxisAngle(kmMat3 *pOut, const struct kmVec3 *axis, float radians);
struct kmVec3 *kmMat3RotationToAxisAngle(struct kmVec3 *pAxis, float *radians, const kmMat3 *pIn);
kmMat3 *kmMat3LookAt(kmMat3 *pOut, const struct kmVec3 *pEye, const struct kmVec3 *pCenter, const struct kmVec3 *pUp);
struct kmVec3;
struct kmMat3;
struct kmQuaternion;
struct kmPlane;
typedef struct kmMat4
{
  float mat[16];
} kmMat4;
kmMat4 *kmMat4Fill(kmMat4 *pOut, const float *pMat);
kmMat4 *kmMat4Identity(kmMat4 *pOut);
kmMat4 *kmMat4Inverse(kmMat4 *pOut, const kmMat4 *pM);
int kmMat4IsIdentity(const kmMat4 *pIn);
kmMat4 *kmMat4Transpose(kmMat4 *pOut, const kmMat4 *pIn);
kmMat4 *kmMat4Multiply(kmMat4 *pOut, const kmMat4 *pM1, const kmMat4 *pM2);
kmMat4 *kmMat4Assign(kmMat4 *pOut, const kmMat4 *pIn);
kmMat4 *kmMat4AssignMat3(kmMat4 *pOut, const struct kmMat3 *pIn);
int kmMat4AreEqual(const kmMat4 *pM1, const kmMat4 *pM2);
kmMat4 *kmMat4RotationX(kmMat4 *pOut, const float radians);
kmMat4 *kmMat4RotationY(kmMat4 *pOut, const float radians);
kmMat4 *kmMat4RotationZ(kmMat4 *pOut, const float radians);
kmMat4 *kmMat4RotationYawPitchRoll(kmMat4 *pOut, const float pitch, const float yaw, const float roll);
kmMat4 *kmMat4RotationQuaternion(kmMat4 *pOut, const struct kmQuaternion *pQ);
kmMat4 *kmMat4RotationTranslation(kmMat4 *pOut, const struct kmMat3 *rotation, const struct kmVec3 *translation);
kmMat4 *kmMat4Scaling(kmMat4 *pOut, const float x, const float y, const float z);
kmMat4 *kmMat4Translation(kmMat4 *pOut, const float x, const float y, const float z);
struct kmVec3 *kmMat4GetUpVec3(struct kmVec3 *pOut, const kmMat4 *pIn);
struct kmVec3 *kmMat4GetRightVec3(struct kmVec3 *pOut, const kmMat4 *pIn);
struct kmVec3 *kmMat4GetForwardVec3RH(struct kmVec3 *pOut, const kmMat4 *pIn);
struct kmVec3 *kmMat4GetForwardVec3LH(struct kmVec3 *pOut, const kmMat4 *pIn);
kmMat4 *kmMat4PerspectiveProjection(kmMat4 *pOut, float fovY, float aspect, float zNear, float zFar);
kmMat4 *kmMat4OrthographicProjection(kmMat4 *pOut, float left, float right, float bottom, float top, float nearVal, float farVal);
kmMat4 *kmMat4LookAt(kmMat4 *pOut, const struct kmVec3 *pEye, const struct kmVec3 *pCenter, const struct kmVec3 *pUp);
kmMat4 *kmMat4RotationAxisAngle(kmMat4 *pOut, const struct kmVec3 *axis, float radians);
struct kmMat3 *kmMat4ExtractRotation(struct kmMat3 *pOut, const kmMat4 *pIn);
struct kmPlane *kmMat4ExtractPlane(struct kmPlane *pOut, const kmMat4 *pIn, const unsigned int plane);
struct kmVec3 *kmMat4RotationToAxisAngle(struct kmVec3 *pAxis, float *radians, const kmMat4 *pIn);
struct kmMat4;
struct kmMat3;
struct kmVec3;
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion;
int kmQuaternionAreEqual(const kmQuaternion *p1, const kmQuaternion *p2);
kmQuaternion *kmQuaternionFill(kmQuaternion *pOut, float x, float y, float z, float w);
float kmQuaternionDot(const kmQuaternion *q1, const kmQuaternion *q2);
kmQuaternion *kmQuaternionExp(kmQuaternion *pOut, const kmQuaternion *pIn);
kmQuaternion *kmQuaternionIdentity(kmQuaternion *pOut);
kmQuaternion *kmQuaternionInverse(kmQuaternion *pOut, const kmQuaternion *pIn);
int kmQuaternionIsIdentity(const kmQuaternion *pIn);
float kmQuaternionLength(const kmQuaternion *pIn);
float kmQuaternionLengthSq(const kmQuaternion *pIn);
kmQuaternion *kmQuaternionLn(kmQuaternion *pOut, const kmQuaternion *pIn);
kmQuaternion *kmQuaternionMultiply(kmQuaternion *pOut, const kmQuaternion *q1, const kmQuaternion *q2);
kmQuaternion *kmQuaternionNormalize(kmQuaternion *pOut, const kmQuaternion *pIn);
kmQuaternion *kmQuaternionRotationAxisAngle(kmQuaternion *pOut, const struct kmVec3 *pV, float angle);
kmQuaternion *kmQuaternionRotationMatrix(kmQuaternion *pOut, const struct kmMat3 *pIn);
kmQuaternion *kmQuaternionRotationPitchYawRoll(kmQuaternion *pOut, float pitch, float yaw, float roll);
kmQuaternion *kmQuaternionSlerp(kmQuaternion *pOut, const kmQuaternion *q1, const kmQuaternion *q2, float t);
void kmQuaternionToAxisAngle(const kmQuaternion *pIn, struct kmVec3 *pVector, float *pAngle);
kmQuaternion *kmQuaternionScale(kmQuaternion *pOut, const kmQuaternion *pIn, float s);
kmQuaternion *kmQuaternionAssign(kmQuaternion *pOut, const kmQuaternion *pIn);
kmQuaternion *kmQuaternionAdd(kmQuaternion *pOut, const kmQuaternion *pQ1, const kmQuaternion *pQ2);
kmQuaternion *kmQuaternionSubtract(kmQuaternion *pOut, const kmQuaternion *pQ1, const kmQuaternion *pQ2);
kmQuaternion *kmQuaternionRotationBetweenVec3(kmQuaternion *pOut, const struct kmVec3 *vec1, const struct kmVec3 *vec2, const struct kmVec3 *fallback);
struct kmVec3 *kmQuaternionMultiplyVec3(struct kmVec3 *pOut, const kmQuaternion *q, const struct kmVec3 *v);
kmVec3 *kmQuaternionGetUpVec3(kmVec3 *pOut, const kmQuaternion *pIn);
kmVec3 *kmQuaternionGetRightVec3(kmVec3 *pOut, const kmQuaternion *pIn);
kmVec3 *kmQuaternionGetForwardVec3RH(kmVec3 *pOut, const kmQuaternion *pIn);
kmVec3 *kmQuaternionGetForwardVec3LH(kmVec3 *pOut, const kmQuaternion *pIn);
float kmQuaternionGetPitch(const kmQuaternion *q);
float kmQuaternionGetYaw(const kmQuaternion *q);
float kmQuaternionGetRoll(const kmQuaternion *q);
kmQuaternion *kmQuaternionLookRotation(kmQuaternion *pOut, const kmVec3 *direction, const kmVec3 *up);
kmMat3 *kmMat3Fill(kmMat3 *pOut, const float *pMat)
{
  memcpy(pOut->mat, pMat, (sizeof(float)) * 9);
  return pOut;
}

kmMat3 *kmMat3Identity(kmMat3 *pOut)
{
  memset(pOut->mat, 0, (sizeof(float)) * 9);
  pOut->mat[0] = (pOut->mat[4] = (pOut->mat[8] = 1.0f));
  return pOut;
}

float kmMat3Determinant(const kmMat3 *pIn)
{
  float output;
  output = (((pIn->mat[0] * pIn->mat[4]) * pIn->mat[8]) + ((pIn->mat[1] * pIn->mat[5]) * pIn->mat[6])) + ((pIn->mat[2] * pIn->mat[3]) * pIn->mat[7]);
  output -= (((pIn->mat[2] * pIn->mat[4]) * pIn->mat[6]) + ((pIn->mat[0] * pIn->mat[5]) * pIn->mat[7])) + ((pIn->mat[1] * pIn->mat[3]) * pIn->mat[8]);
  return output;
}

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

int kmMat3IsIdentity(const kmMat3 *pIn)
{
  static float identity[] = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};
  return memcmp(identity, pIn->mat, (sizeof(float)) * 9) == 0;
}

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

kmMat3 *kmMat3Assign(kmMat3 *pOut, const kmMat3 *pIn)
{
  assert(pOut != pIn);
  memcpy(pOut->mat, pIn->mat, (sizeof(float)) * 9);
  return pOut;
}

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

kmMat3 *kmMat3Scaling(kmMat3 *pOut, const float x, const float y)
{
  kmMat3Identity(pOut);
  pOut->mat[0] = x;
  pOut->mat[4] = y;
  return pOut;
}

kmMat3 *kmMat3Translation(kmMat3 *pOut, const float x, const float y)
{
  kmMat3Identity(pOut);
  pOut->mat[6] = x;
  pOut->mat[7] = y;
  return pOut;
}

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

kmVec3 *kmMat3RotationToAxisAngle(kmVec3 *pAxis, float *radians, const kmMat3 *pIn)
{
  kmQuaternion temp;
  kmQuaternionRotationMatrix(&temp, pIn);
  kmQuaternionToAxisAngle(&temp, pAxis, radians);
  return pAxis;
}

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

kmVec3 *kmMat3GetUpVec3(kmVec3 *pOut, const kmMat3 *pIn)
{
  pOut->x = pIn->mat[3];
  pOut->y = pIn->mat[4];
  pOut->z = pIn->mat[5];
  kmVec3Normalize(pOut, pOut);
  return pOut;
}

kmVec3 *kmMat3GetRightVec3(kmVec3 *pOut, const kmMat3 *pIn)
{
  pOut->x = pIn->mat[0];
  pOut->y = pIn->mat[1];
  pOut->z = pIn->mat[2];
  kmVec3Normalize(pOut, pOut);
  return pOut;
}

kmVec3 *kmMat3GetForwardVec3(kmVec3 *pOut, const kmMat3 *pIn)
{
  pOut->x = pIn->mat[6];
  pOut->y = pIn->mat[7];
  pOut->z = pIn->mat[8];
  kmVec3Normalize(pOut, pOut);
  return pOut;
}

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


extern float kmSQR(float s);
extern float kmDegreesToRadians(float degrees);
extern float kmRadiansToDegrees(float radians);
extern float kmMin(float lhs, float rhs);
extern float kmMax(float lhs, float rhs);
extern unsigned char kmAlmostEqual(float lhs, float rhs);
extern float kmClamp(float x, float min, float max);
extern float kmLerp(float x, float y, float factor);
struct kmMat4;
struct kmMat3;
struct kmPlane;
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3;
kmVec3 *kmVec3Fill(kmVec3 *pOut, float x, float y, float z);
float kmVec3Length(const kmVec3 *pIn);
float kmVec3LengthSq(const kmVec3 *pIn);
kmVec3 *kmVec3Lerp(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2, float t);
kmVec3 *kmVec3Normalize(kmVec3 *pOut, const kmVec3 *pIn);
kmVec3 *kmVec3Cross(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2);
float kmVec3Dot(const kmVec3 *pV1, const kmVec3 *pV2);
kmVec3 *kmVec3Add(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2);
kmVec3 *kmVec3Subtract(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2);
kmVec3 *kmVec3Mul(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2);
kmVec3 *kmVec3Div(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2);
kmVec3 *kmVec3MultiplyMat3(kmVec3 *pOut, const kmVec3 *pV, const struct kmMat3 *pM);
kmVec3 *kmVec3MultiplyMat4(kmVec3 *pOut, const kmVec3 *pV, const struct kmMat4 *pM);
kmVec3 *kmVec3Transform(kmVec3 *pOut, const kmVec3 *pV1, const struct kmMat4 *pM);
kmVec3 *kmVec3TransformNormal(kmVec3 *pOut, const kmVec3 *pV, const struct kmMat4 *pM);
kmVec3 *kmVec3TransformCoord(kmVec3 *pOut, const kmVec3 *pV, const struct kmMat4 *pM);
kmVec3 *kmVec3Scale(kmVec3 *pOut, const kmVec3 *pIn, const float s);
int kmVec3AreEqual(const kmVec3 *p1, const kmVec3 *p2);
kmVec3 *kmVec3InverseTransform(kmVec3 *pOut, const kmVec3 *pV, const struct kmMat4 *pM);
kmVec3 *kmVec3InverseTransformNormal(kmVec3 *pOut, const kmVec3 *pVect, const struct kmMat4 *pM);
kmVec3 *kmVec3Assign(kmVec3 *pOut, const kmVec3 *pIn);
kmVec3 *kmVec3Zero(kmVec3 *pOut);
kmVec3 *kmVec3GetHorizontalAngle(kmVec3 *pOut, const kmVec3 *pIn);
kmVec3 *kmVec3RotationToDirection(kmVec3 *pOut, const kmVec3 *pIn, const kmVec3 *forwards);
kmVec3 *kmVec3ProjectOnToPlane(kmVec3 *pOut, const kmVec3 *point, const struct kmPlane *plane);
kmVec3 *kmVec3Reflect(kmVec3 *pOut, const kmVec3 *pIn, const kmVec3 *normal);
extern const kmVec3 KM_VEC3_NEG_Z;
extern const kmVec3 KM_VEC3_POS_Z;
extern const kmVec3 KM_VEC3_POS_Y;
extern const kmVec3 KM_VEC3_NEG_Y;
extern const kmVec3 KM_VEC3_NEG_X;
extern const kmVec3 KM_VEC3_POS_X;
extern const kmVec3 KM_VEC3_ZERO;
struct kmVec3;
struct kmQuaternion;
struct kmMat4;
typedef struct kmMat3
{
  float mat[9];
} kmMat3;
kmMat3 *kmMat3Fill(kmMat3 *pOut, const float *pMat);
kmMat3 *kmMat3Adjugate(kmMat3 *pOut, const kmMat3 *pIn);
kmMat3 *kmMat3Identity(kmMat3 *pOut);
kmMat3 *kmMat3Inverse(kmMat3 *pOut, const kmMat3 *pM);
int kmMat3IsIdentity(const kmMat3 *pIn);
kmMat3 *kmMat3Transpose(kmMat3 *pOut, const kmMat3 *pIn);
float kmMat3Determinant(const kmMat3 *pIn);
kmMat3 *kmMat3Multiply(kmMat3 *pOut, const kmMat3 *pM1, const kmMat3 *pM2);
kmMat3 *kmMat3ScalarMultiply(kmMat3 *pOut, const kmMat3 *pM, const float pFactor);
kmMat3 *kmMat3Assign(kmMat3 *pOut, const kmMat3 *pIn);
kmMat3 *kmMat3AssignMat4(kmMat3 *pOut, const struct kmMat4 *pIn);
int kmMat3AreEqual(const kmMat3 *pM1, const kmMat3 *pM2);
struct kmVec3 *kmMat3GetUpVec3(struct kmVec3 *pOut, const kmMat3 *pIn);
struct kmVec3 *kmMat3GetRightVec3(struct kmVec3 *pOut, const kmMat3 *pIn);
struct kmVec3 *kmMat3GetForwardVec3(struct kmVec3 *pOut, const kmMat3 *pIn);
kmMat3 *kmMat3RotationX(kmMat3 *pOut, const float radians);
kmMat3 *kmMat3RotationY(kmMat3 *pOut, const float radians);
kmMat3 *kmMat3RotationZ(kmMat3 *pOut, const float radians);
kmMat3 *kmMat3Rotation(kmMat3 *pOut, const float radians);
kmMat3 *kmMat3Scaling(kmMat3 *pOut, const float x, const float y);
kmMat3 *kmMat3Translation(kmMat3 *pOut, const float x, const float y);
kmMat3 *kmMat3RotationQuaternion(kmMat3 *pOut, const struct kmQuaternion *pIn);
kmMat3 *kmMat3RotationAxisAngle(kmMat3 *pOut, const struct kmVec3 *axis, float radians);
struct kmVec3 *kmMat3RotationToAxisAngle(struct kmVec3 *pAxis, float *radians, const kmMat3 *pIn);
kmMat3 *kmMat3LookAt(kmMat3 *pOut, const struct kmVec3 *pEye, const struct kmVec3 *pCenter, const struct kmVec3 *pUp);
struct kmVec3;
struct kmMat3;
struct kmQuaternion;
struct kmPlane;
typedef struct kmMat4
{
  float mat[16];
} kmMat4;
kmMat4 *kmMat4Fill(kmMat4 *pOut, const float *pMat);
kmMat4 *kmMat4Identity(kmMat4 *pOut);
kmMat4 *kmMat4Inverse(kmMat4 *pOut, const kmMat4 *pM);
int kmMat4IsIdentity(const kmMat4 *pIn);
kmMat4 *kmMat4Transpose(kmMat4 *pOut, const kmMat4 *pIn);
kmMat4 *kmMat4Multiply(kmMat4 *pOut, const kmMat4 *pM1, const kmMat4 *pM2);
kmMat4 *kmMat4Assign(kmMat4 *pOut, const kmMat4 *pIn);
kmMat4 *kmMat4AssignMat3(kmMat4 *pOut, const struct kmMat3 *pIn);
int kmMat4AreEqual(const kmMat4 *pM1, const kmMat4 *pM2);
kmMat4 *kmMat4RotationX(kmMat4 *pOut, const float radians);
kmMat4 *kmMat4RotationY(kmMat4 *pOut, const float radians);
kmMat4 *kmMat4RotationZ(kmMat4 *pOut, const float radians);
kmMat4 *kmMat4RotationYawPitchRoll(kmMat4 *pOut, const float pitch, const float yaw, const float roll);
kmMat4 *kmMat4RotationQuaternion(kmMat4 *pOut, const struct kmQuaternion *pQ);
kmMat4 *kmMat4RotationTranslation(kmMat4 *pOut, const struct kmMat3 *rotation, const struct kmVec3 *translation);
kmMat4 *kmMat4Scaling(kmMat4 *pOut, const float x, const float y, const float z);
kmMat4 *kmMat4Translation(kmMat4 *pOut, const float x, const float y, const float z);
struct kmVec3 *kmMat4GetUpVec3(struct kmVec3 *pOut, const kmMat4 *pIn);
struct kmVec3 *kmMat4GetRightVec3(struct kmVec3 *pOut, const kmMat4 *pIn);
struct kmVec3 *kmMat4GetForwardVec3RH(struct kmVec3 *pOut, const kmMat4 *pIn);
struct kmVec3 *kmMat4GetForwardVec3LH(struct kmVec3 *pOut, const kmMat4 *pIn);
kmMat4 *kmMat4PerspectiveProjection(kmMat4 *pOut, float fovY, float aspect, float zNear, float zFar);
kmMat4 *kmMat4OrthographicProjection(kmMat4 *pOut, float left, float right, float bottom, float top, float nearVal, float farVal);
kmMat4 *kmMat4LookAt(kmMat4 *pOut, const struct kmVec3 *pEye, const struct kmVec3 *pCenter, const struct kmVec3 *pUp);
kmMat4 *kmMat4RotationAxisAngle(kmMat4 *pOut, const struct kmVec3 *axis, float radians);
struct kmMat3 *kmMat4ExtractRotation(struct kmMat3 *pOut, const kmMat4 *pIn);
struct kmPlane *kmMat4ExtractPlane(struct kmPlane *pOut, const kmMat4 *pIn, const unsigned int plane);
struct kmVec3 *kmMat4RotationToAxisAngle(struct kmVec3 *pAxis, float *radians, const kmMat4 *pIn);
struct kmMat4;
struct kmMat3;
struct kmVec3;
typedef struct kmQuaternion
{
  float x;
  float y;
  float z;
  float w;
} kmQuaternion;
int kmQuaternionAreEqual(const kmQuaternion *p1, const kmQuaternion *p2);
kmQuaternion *kmQuaternionFill(kmQuaternion *pOut, float x, float y, float z, float w);
float kmQuaternionDot(const kmQuaternion *q1, const kmQuaternion *q2);
kmQuaternion *kmQuaternionExp(kmQuaternion *pOut, const kmQuaternion *pIn);
kmQuaternion *kmQuaternionIdentity(kmQuaternion *pOut);
kmQuaternion *kmQuaternionInverse(kmQuaternion *pOut, const kmQuaternion *pIn);
int kmQuaternionIsIdentity(const kmQuaternion *pIn);
float kmQuaternionLength(const kmQuaternion *pIn);
float kmQuaternionLengthSq(const kmQuaternion *pIn);
kmQuaternion *kmQuaternionLn(kmQuaternion *pOut, const kmQuaternion *pIn);
kmQuaternion *kmQuaternionMultiply(kmQuaternion *pOut, const kmQuaternion *q1, const kmQuaternion *q2);
kmQuaternion *kmQuaternionNormalize(kmQuaternion *pOut, const kmQuaternion *pIn);
kmQuaternion *kmQuaternionRotationAxisAngle(kmQuaternion *pOut, const struct kmVec3 *pV, float angle);
kmQuaternion *kmQuaternionRotationMatrix(kmQuaternion *pOut, const struct kmMat3 *pIn);
kmQuaternion *kmQuaternionRotationPitchYawRoll(kmQuaternion *pOut, float pitch, float yaw, float roll);
kmQuaternion *kmQuaternionSlerp(kmQuaternion *pOut, const kmQuaternion *q1, const kmQuaternion *q2, float t);
void kmQuaternionToAxisAngle(const kmQuaternion *pIn, struct kmVec3 *pVector, float *pAngle);
kmQuaternion *kmQuaternionScale(kmQuaternion *pOut, const kmQuaternion *pIn, float s);
kmQuaternion *kmQuaternionAssign(kmQuaternion *pOut, const kmQuaternion *pIn);
kmQuaternion *kmQuaternionAdd(kmQuaternion *pOut, const kmQuaternion *pQ1, const kmQuaternion *pQ2);
kmQuaternion *kmQuaternionSubtract(kmQuaternion *pOut, const kmQuaternion *pQ1, const kmQuaternion *pQ2);
kmQuaternion *kmQuaternionRotationBetweenVec3(kmQuaternion *pOut, const struct kmVec3 *vec1, const struct kmVec3 *vec2, const struct kmVec3 *fallback);
struct kmVec3 *kmQuaternionMultiplyVec3(struct kmVec3 *pOut, const kmQuaternion *q, const struct kmVec3 *v);
kmVec3 *kmQuaternionGetUpVec3(kmVec3 *pOut, const kmQuaternion *pIn);
kmVec3 *kmQuaternionGetRightVec3(kmVec3 *pOut, const kmQuaternion *pIn);
kmVec3 *kmQuaternionGetForwardVec3RH(kmVec3 *pOut, const kmQuaternion *pIn);
kmVec3 *kmQuaternionGetForwardVec3LH(kmVec3 *pOut, const kmQuaternion *pIn);
float kmQuaternionGetPitch(const kmQuaternion *q);
float kmQuaternionGetYaw(const kmQuaternion *q);
float kmQuaternionGetRoll(const kmQuaternion *q);
kmQuaternion *kmQuaternionLookRotation(kmQuaternion *pOut, const kmVec3 *direction, const kmVec3 *up);
kmMat3 *kmMat3Fill(kmMat3 *pOut, const float *pMat)
{
  memcpy(pOut->mat, pMat, (sizeof(float)) * 9);
  return pOut;
}

kmMat3 *kmMat3Identity(kmMat3 *pOut)
{
  memset(pOut->mat, 0, (sizeof(float)) * 9);
  pOut->mat[0] = (pOut->mat[4] = (pOut->mat[8] = 1.0f));
  return pOut;
}

float kmMat3Determinant(const kmMat3 *pIn)
{
  float output;
  output = (((pIn->mat[0] * pIn->mat[4]) * pIn->mat[8]) + ((pIn->mat[1] * pIn->mat[5]) * pIn->mat[6])) + ((pIn->mat[2] * pIn->mat[3]) * pIn->mat[7]);
  output -= (((pIn->mat[2] * pIn->mat[4]) * pIn->mat[6]) + ((pIn->mat[0] * pIn->mat[5]) * pIn->mat[7])) + ((pIn->mat[1] * pIn->mat[3]) * pIn->mat[8]);
  return output;
}

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

int kmMat3IsIdentity(const kmMat3 *pIn)
{
  static float identity[] = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};
  return memcmp(identity, pIn->mat, (sizeof(float)) * 9) == 0;
}

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

kmMat3 *kmMat3Assign(kmMat3 *pOut, const kmMat3 *pIn)
{
  assert(pOut != pIn);
  memcpy(pOut->mat, pIn->mat, (sizeof(float)) * 9);
  return pOut;
}

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

kmMat3 *kmMat3Scaling(kmMat3 *pOut, const float x, const float y)
{
  kmMat3Identity(pOut);
  pOut->mat[0] = x;
  pOut->mat[4] = y;
  return pOut;
}

kmMat3 *kmMat3Translation(kmMat3 *pOut, const float x, const float y)
{
  kmMat3Identity(pOut);
  pOut->mat[6] = x;
  pOut->mat[7] = y;
  return pOut;
}

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

kmVec3 *kmMat3RotationToAxisAngle(kmVec3 *pAxis, float *radians, const kmMat3 *pIn)
{
  kmQuaternion temp;
  kmQuaternionRotationMatrix(&temp, pIn);
  kmQuaternionToAxisAngle(&temp, pAxis, radians);
  return pAxis;
}

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

kmVec3 *kmMat3GetUpVec3(kmVec3 *pOut, const kmMat3 *pIn)
{
  pOut->x = pIn->mat[3];
  pOut->y = pIn->mat[4];
  pOut->z = pIn->mat[5];
  kmVec3Normalize(pOut, pOut);
  return pOut;
}

kmVec3 *kmMat3GetRightVec3(kmVec3 *pOut, const kmMat3 *pIn)
{
  pOut->x = pIn->mat[0];
  pOut->y = pIn->mat[1];
  pOut->z = pIn->mat[2];
  kmVec3Normalize(pOut, pOut);
  return pOut;
}

kmVec3 *kmMat3GetForwardVec3(kmVec3 *pOut, const kmMat3 *pIn)
{
  pOut->x = pIn->mat[6];
  pOut->y = pIn->mat[7];
  pOut->z = pIn->mat[8];
  kmVec3Normalize(pOut, pOut);
  return pOut;
}

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

