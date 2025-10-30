#include <assert.h>
#include <mat3.h>
#include <mat4.h>
#include <math.h>
#include <memory.h>
#include <quaternion.c>
#include <quaternion.h>
#include <string.h>
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
int kmQuaternionAreEqual(const kmQuaternion *p1, const kmQuaternion *p2)
{
  if (((((p1->x < (p2->x + 0.0001)) && (p1->x > (p2->x - 0.0001))) && ((p1->y < (p2->y + 0.0001)) && (p1->y > (p2->y - 0.0001)))) && ((p1->z < (p2->z + 0.0001)) && (p1->z > (p2->z - 0.0001)))) && ((p1->w < (p2->w + 0.0001)) && (p1->w > (p2->w - 0.0001))))
  {
    return 1;
  }
  return 0;
}

kmQuaternion *kmQuaternionFill(kmQuaternion *pOut, float x, float y, float z, float w)
{
  pOut->x = x;
  pOut->y = y;
  pOut->z = z;
  pOut->w = w;
  return pOut;
}

float kmQuaternionDot(const kmQuaternion *q1, const kmQuaternion *q2)
{
  return (((q1->w * q2->w) + (q1->x * q2->x)) + (q1->y * q2->y)) + (q1->z * q2->z);
}

kmQuaternion *kmQuaternionExp(kmQuaternion *pOut, const kmQuaternion *pIn)
{
  assert(0);
  return pOut;
}

kmQuaternion *kmQuaternionIdentity(kmQuaternion *pOut)
{
  pOut->x = 0.0;
  pOut->y = 0.0;
  pOut->z = 0.0;
  pOut->w = 1.0;
  return pOut;
}

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

int kmQuaternionIsIdentity(const kmQuaternion *pIn)
{
  return (((pIn->x == 0.0) && (pIn->y == 0.0)) && (pIn->z == 0.0)) && (pIn->w == 1.0);
}

float kmQuaternionLength(const kmQuaternion *pIn)
{
  return sqrt(kmQuaternionLengthSq(pIn));
}

float kmQuaternionLengthSq(const kmQuaternion *pIn)
{
  return (((pIn->x * pIn->x) + (pIn->y * pIn->y)) + (pIn->z * pIn->z)) + (pIn->w * pIn->w);
}

kmQuaternion *kmQuaternionLn(kmQuaternion *pOut, const kmQuaternion *pIn)
{
  assert(0);
  return pOut;
}

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

kmQuaternion *kmQuaternionScale(kmQuaternion *pOut, const kmQuaternion *pIn, float s)
{
  pOut->x = pIn->x * s;
  pOut->y = pIn->y * s;
  pOut->z = pIn->z * s;
  pOut->w = pIn->w * s;
  return pOut;
}

kmQuaternion *kmQuaternionAssign(kmQuaternion *pOut, const kmQuaternion *pIn)
{
  memcpy(pOut, pIn, (sizeof(float)) * 4);
  return pOut;
}

kmQuaternion *kmQuaternionSubtract(kmQuaternion *pOut, const kmQuaternion *pQ1, const kmQuaternion *pQ2)
{
  pOut->x = pQ1->x - pQ2->x;
  pOut->y = pQ1->y - pQ2->y;
  pOut->z = pQ1->z - pQ2->z;
  pOut->w = pQ1->w - pQ2->w;
  return pOut;
}

kmQuaternion *kmQuaternionAdd(kmQuaternion *pOut, const kmQuaternion *pQ1, const kmQuaternion *pQ2)
{
  pOut->x = pQ1->x + pQ2->x;
  pOut->y = pQ1->y + pQ2->y;
  pOut->z = pQ1->z + pQ2->z;
  pOut->w = pQ1->w + pQ2->w;
  return pOut;
}

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

kmVec3 *kmQuaternionGetUpVec3(kmVec3 *pOut, const kmQuaternion *pIn)
{
  return kmQuaternionMultiplyVec3(pOut, pIn, &KM_VEC3_POS_Y);
}

kmVec3 *kmQuaternionGetRightVec3(kmVec3 *pOut, const kmQuaternion *pIn)
{
  return kmQuaternionMultiplyVec3(pOut, pIn, &KM_VEC3_POS_X);
}

kmVec3 *kmQuaternionGetForwardVec3RH(kmVec3 *pOut, const kmQuaternion *pIn)
{
  return kmQuaternionMultiplyVec3(pOut, pIn, &KM_VEC3_NEG_Z);
}

kmVec3 *kmQuaternionGetForwardVec3LH(kmVec3 *pOut, const kmQuaternion *pIn)
{
  return kmQuaternionMultiplyVec3(pOut, pIn, &KM_VEC3_POS_Z);
}

float kmQuaternionGetPitch(const kmQuaternion *q)
{
  float result = atan2(2 * ((q->y * q->z) + (q->w * q->x)), (((q->w * q->w) - (q->x * q->x)) - (q->y * q->y)) + (q->z * q->z));
  return result;
}

float kmQuaternionGetYaw(const kmQuaternion *q)
{
  float result = asin((-2) * ((q->x * q->z) - (q->w * q->y)));
  return result;
}

float kmQuaternionGetRoll(const kmQuaternion *q)
{
  float result = atan2(2 * ((q->x * q->y) + (q->w * q->z)), (((q->w * q->w) + (q->x * q->x)) - (q->y * q->y)) - (q->z * q->z));
  return result;
}

kmQuaternion *kmQuaternionLookRotation(kmQuaternion *pOut, const kmVec3 *direction, const kmVec3 *up)
{
  kmMat3 tmp;
  kmMat3LookAt(&tmp, &KM_VEC3_ZERO, direction, up);
  return kmQuaternionNormalize(pOut, kmQuaternionRotationMatrix(pOut, &tmp));
}


extern float kmSQR(float s);
extern float kmDegreesToRadians(float degrees);
extern float kmRadiansToDegrees(float radians);
extern float kmMin(float lhs, float rhs);
extern float kmMax(float lhs, float rhs);
extern unsigned char kmAlmostEqual(float lhs, float rhs);
extern float kmClamp(float x, float min, float max);
extern float kmLerp(float x, float y, float factor);
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
int kmQuaternionAreEqual(const kmQuaternion *p1, const kmQuaternion *p2)
{
  if (((((p1->x < (p2->x + 0.0001)) && (p1->x > (p2->x - 0.0001))) && ((p1->y < (p2->y + 0.0001)) && (p1->y > (p2->y - 0.0001)))) && ((p1->z < (p2->z + 0.0001)) && (p1->z > (p2->z - 0.0001)))) && ((p1->w < (p2->w + 0.0001)) && (p1->w > (p2->w - 0.0001))))
  {
    return 1;
  }
  return 0;
}

kmQuaternion *kmQuaternionFill(kmQuaternion *pOut, float x, float y, float z, float w)
{
  pOut->x = x;
  pOut->y = y;
  pOut->z = z;
  pOut->w = w;
  return pOut;
}

float kmQuaternionDot(const kmQuaternion *q1, const kmQuaternion *q2)
{
  return (((q1->w * q2->w) + (q1->x * q2->x)) + (q1->y * q2->y)) + (q1->z * q2->z);
}

kmQuaternion *kmQuaternionExp(kmQuaternion *pOut, const kmQuaternion *pIn)
{
  assert(0);
  return pOut;
}

kmQuaternion *kmQuaternionIdentity(kmQuaternion *pOut)
{
  pOut->x = 0.0;
  pOut->y = 0.0;
  pOut->z = 0.0;
  pOut->w = 1.0;
  return pOut;
}

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

int kmQuaternionIsIdentity(const kmQuaternion *pIn)
{
  return (((pIn->x == 0.0) && (pIn->y == 0.0)) && (pIn->z == 0.0)) && (pIn->w == 1.0);
}

float kmQuaternionLength(const kmQuaternion *pIn)
{
  return sqrt(kmQuaternionLengthSq(pIn));
}

float kmQuaternionLengthSq(const kmQuaternion *pIn)
{
  return (((pIn->x * pIn->x) + (pIn->y * pIn->y)) + (pIn->z * pIn->z)) + (pIn->w * pIn->w);
}

kmQuaternion *kmQuaternionLn(kmQuaternion *pOut, const kmQuaternion *pIn)
{
  assert(0);
  return pOut;
}

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
  }
  pOut->x = x;
  pOut->y = y;
  pOut->z = z;
  pOut->w = w;
  return pOut;
}

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

kmQuaternion *kmQuaternionScale(kmQuaternion *pOut, const kmQuaternion *pIn, float s)
{
  pOut->x = pIn->x * s;
  pOut->y = pIn->y * s;
  pOut->z = pIn->z * s;
  pOut->w = pIn->w * s;
  return pOut;
}

kmQuaternion *kmQuaternionAssign(kmQuaternion *pOut, const kmQuaternion *pIn)
{
  memcpy(pOut, pIn, (sizeof(float)) * 4);
  return pOut;
}

kmQuaternion *kmQuaternionSubtract(kmQuaternion *pOut, const kmQuaternion *pQ1, const kmQuaternion *pQ2)
{
  pOut->x = pQ1->x - pQ2->x;
  pOut->y = pQ1->y - pQ2->y;
  pOut->z = pQ1->z - pQ2->z;
  pOut->w = pQ1->w - pQ2->w;
  return pOut;
}

kmQuaternion *kmQuaternionAdd(kmQuaternion *pOut, const kmQuaternion *pQ1, const kmQuaternion *pQ2)
{
  pOut->x = pQ1->x + pQ2->x;
  pOut->y = pQ1->y + pQ2->y;
  pOut->z = pQ1->z + pQ2->z;
  pOut->w = pQ1->w + pQ2->w;
  return pOut;
}

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

kmVec3 *kmQuaternionGetUpVec3(kmVec3 *pOut, const kmQuaternion *pIn)
{
  return kmQuaternionMultiplyVec3(pOut, pIn, &KM_VEC3_POS_Y);
}

kmVec3 *kmQuaternionGetRightVec3(kmVec3 *pOut, const kmQuaternion *pIn)
{
  return kmQuaternionMultiplyVec3(pOut, pIn, &KM_VEC3_POS_X);
}

kmVec3 *kmQuaternionGetForwardVec3RH(kmVec3 *pOut, const kmQuaternion *pIn)
{
  return kmQuaternionMultiplyVec3(pOut, pIn, &KM_VEC3_NEG_Z);
}

kmVec3 *kmQuaternionGetForwardVec3LH(kmVec3 *pOut, const kmQuaternion *pIn)
{
  return kmQuaternionMultiplyVec3(pOut, pIn, &KM_VEC3_POS_Z);
}

float kmQuaternionGetPitch(const kmQuaternion *q)
{
  float result = atan2(2 * ((q->y * q->z) + (q->w * q->x)), (((q->w * q->w) - (q->x * q->x)) - (q->y * q->y)) + (q->z * q->z));
  return result;
}

float kmQuaternionGetYaw(const kmQuaternion *q)
{
  float result = asin((-2) * ((q->x * q->z) - (q->w * q->y)));
  return result;
}

float kmQuaternionGetRoll(const kmQuaternion *q)
{
  float result = atan2(2 * ((q->x * q->y) + (q->w * q->z)), (((q->w * q->w) + (q->x * q->x)) - (q->y * q->y)) - (q->z * q->z));
  return result;
}

kmQuaternion *kmQuaternionLookRotation(kmQuaternion *pOut, const kmVec3 *direction, const kmVec3 *up)
{
  kmMat3 tmp;
  kmMat3LookAt(&tmp, &KM_VEC3_ZERO, direction, up);
  return kmQuaternionNormalize(pOut, kmQuaternionRotationMatrix(pOut, &tmp));
}

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

