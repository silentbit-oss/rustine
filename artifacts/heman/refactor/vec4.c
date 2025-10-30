#include <assert.h>
#include <mat4.h>
#include <math.h>
#include <memory.h>
#include <utility.h>
#include <vec4.c>
#include <vec4.h>

extern float kmSQR(float s);
extern float kmDegreesToRadians(float degrees);
extern float kmRadiansToDegrees(float radians);
extern float kmMin(float lhs, float rhs);
extern float kmMax(float lhs, float rhs);
extern unsigned char kmAlmostEqual(float lhs, float rhs);
extern float kmClamp(float x, float min, float max);
extern float kmLerp(float x, float y, float factor);
struct kmMat4;
#pragma pack(push)
#pragma pack(1)
typedef struct kmVec4
{
  float x;
  float y;
  float z;
  float w;
} kmVec4;
#pragma pack(pop)
kmVec4 *kmVec4Fill(kmVec4 *pOut, float x, float y, float z, float w);
kmVec4 *kmVec4Add(kmVec4 *pOut, const kmVec4 *pV1, const kmVec4 *pV2);
float kmVec4Dot(const kmVec4 *pV1, const kmVec4 *pV2);
float kmVec4Length(const kmVec4 *pIn);
float kmVec4LengthSq(const kmVec4 *pIn);
kmVec4 *kmVec4Lerp(kmVec4 *pOut, const kmVec4 *pV1, const kmVec4 *pV2, float t);
kmVec4 *kmVec4Normalize(kmVec4 *pOut, const kmVec4 *pIn);
kmVec4 *kmVec4Scale(kmVec4 *pOut, const kmVec4 *pIn, const float s);
kmVec4 *kmVec4Subtract(kmVec4 *pOut, const kmVec4 *pV1, const kmVec4 *pV2);
kmVec4 *kmVec4Mul(kmVec4 *pOut, const kmVec4 *pV1, const kmVec4 *pV2);
kmVec4 *kmVec4Div(kmVec4 *pOut, const kmVec4 *pV1, const kmVec4 *pV2);
kmVec4 *kmVec4MultiplyMat4(kmVec4 *pOut, const kmVec4 *pV, const struct kmMat4 *pM);
kmVec4 *kmVec4Transform(kmVec4 *pOut, const kmVec4 *pV, const struct kmMat4 *pM);
kmVec4 *kmVec4TransformArray(kmVec4 *pOut, unsigned int outStride, const kmVec4 *pV, unsigned int vStride, const struct kmMat4 *pM, unsigned int count);
int kmVec4AreEqual(const kmVec4 *p1, const kmVec4 *p2);
kmVec4 *kmVec4Assign(kmVec4 *pOut, const kmVec4 *pIn);
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
kmVec4 *kmVec4Fill(kmVec4 *pOut, float x, float y, float z, float w)
{
  pOut->x = x;
  pOut->y = y;
  pOut->z = z;
  pOut->w = w;
  return pOut;
}

kmVec4 *kmVec4Add(kmVec4 *pOut, const kmVec4 *pV1, const kmVec4 *pV2)
{
  pOut->x = pV1->x + pV2->x;
  pOut->y = pV1->y + pV2->y;
  pOut->z = pV1->z + pV2->z;
  pOut->w = pV1->w + pV2->w;
  return pOut;
}

float kmVec4Dot(const kmVec4 *pV1, const kmVec4 *pV2)
{
  return (((pV1->x * pV2->x) + (pV1->y * pV2->y)) + (pV1->z * pV2->z)) + (pV1->w * pV2->w);
}

float kmVec4Length(const kmVec4 *pIn)
{
  return sqrtf(((kmSQR(pIn->x) + kmSQR(pIn->y)) + kmSQR(pIn->z)) + kmSQR(pIn->w));
}

float kmVec4LengthSq(const kmVec4 *pIn)
{
  return ((kmSQR(pIn->x) + kmSQR(pIn->y)) + kmSQR(pIn->z)) + kmSQR(pIn->w);
}

kmVec4 *kmVec4Lerp(kmVec4 *pOut, const kmVec4 *pV1, const kmVec4 *pV2, float t)
{
  pOut->x = pV1->x + (t * (pV2->x - pV1->x));
  pOut->y = pV1->y + (t * (pV2->y - pV1->y));
  pOut->z = pV1->z + (t * (pV2->z - pV1->z));
  pOut->w = pV1->w + (t * (pV2->w - pV1->w));
  return pOut;
}

kmVec4 *kmVec4Normalize(kmVec4 *pOut, const kmVec4 *pIn)
{
  if ((((!pIn->x) && (!pIn->y)) && (!pIn->z)) && (!pIn->w))
  {
    return kmVec4Assign(pOut, pIn);
  }
  float l = 1.0f / kmVec4Length(pIn);
  pOut->x = pIn->x * l;
  pOut->y = pIn->y * l;
  pOut->z = pIn->z * l;
  pOut->w = pIn->w * l;
  return pOut;
}

kmVec4 *kmVec4Scale(kmVec4 *pOut, const kmVec4 *pIn, const float s)
{
  kmVec4Normalize(pOut, pIn);
  pOut->x *= s;
  pOut->y *= s;
  pOut->z *= s;
  pOut->w *= s;
  return pOut;
}

kmVec4 *kmVec4Subtract(kmVec4 *pOut, const kmVec4 *pV1, const kmVec4 *pV2)
{
  pOut->x = pV1->x - pV2->x;
  pOut->y = pV1->y - pV2->y;
  pOut->z = pV1->z - pV2->z;
  pOut->w = pV1->w - pV2->w;
  return pOut;
}

kmVec4 *kmVec4Mul(kmVec4 *pOut, const kmVec4 *pV1, const kmVec4 *pV2)
{
  pOut->x = pV1->x * pV2->x;
  pOut->y = pV1->y * pV2->y;
  pOut->z = pV1->z * pV2->z;
  pOut->w = pV1->w * pV2->w;
  return pOut;
}

kmVec4 *kmVec4Div(kmVec4 *pOut, const kmVec4 *pV1, const kmVec4 *pV2)
{
  if (((pV2->x && pV2->y) && pV2->z) && pV2->w)
  {
    pOut->x = pV1->x / pV2->x;
    pOut->y = pV1->y / pV2->y;
    pOut->z = pV1->z / pV2->z;
    pOut->w = pV1->w / pV2->w;
  }
  return pOut;
}

kmVec4 *kmVec4MultiplyMat4(kmVec4 *pOut, const kmVec4 *pV, const struct kmMat4 *pM)
{
  pOut->x = (((pV->x * pM->mat[0]) + (pV->y * pM->mat[4])) + (pV->z * pM->mat[8])) + (pV->w * pM->mat[12]);
  pOut->y = (((pV->x * pM->mat[1]) + (pV->y * pM->mat[5])) + (pV->z * pM->mat[9])) + (pV->w * pM->mat[13]);
  pOut->z = (((pV->x * pM->mat[2]) + (pV->y * pM->mat[6])) + (pV->z * pM->mat[10])) + (pV->w * pM->mat[14]);
  pOut->w = (((pV->x * pM->mat[3]) + (pV->y * pM->mat[7])) + (pV->z * pM->mat[11])) + (pV->w * pM->mat[15]);
  return pOut;
}

kmVec4 *kmVec4Transform(kmVec4 *pOut, const kmVec4 *pV, const kmMat4 *pM)
{
  return kmVec4MultiplyMat4(pOut, pV, pM);
}

kmVec4 *kmVec4TransformArray(kmVec4 *pOut, unsigned int outStride, const kmVec4 *pV, unsigned int vStride, const kmMat4 *pM, unsigned int count)
{
  unsigned int i = 0;
  while (i < count)
  {
    const kmVec4 *in = pV + (i * vStride);
    kmVec4 *out = pOut + (i * outStride);
    kmVec4Transform(out, in, pM);
    i += 1;
  }

  return pOut;
}

int kmVec4AreEqual(const kmVec4 *p1, const kmVec4 *p2)
{
  return ((((p1->x < (p2->x + 0.0001)) && (p1->x > (p2->x - 0.0001))) && ((p1->y < (p2->y + 0.0001)) && (p1->y > (p2->y - 0.0001)))) && ((p1->z < (p2->z + 0.0001)) && (p1->z > (p2->z - 0.0001)))) && ((p1->w < (p2->w + 0.0001)) && (p1->w > (p2->w - 0.0001)));
}

kmVec4 *kmVec4Assign(kmVec4 *pOut, const kmVec4 *pIn)
{
  assert(pOut != pIn);
  memcpy(pOut, pIn, (sizeof(float)) * 4);
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
#pragma pack(push)
#pragma pack(1)
typedef struct kmVec4
{
  float x;
  float y;
  float z;
  float w;
} kmVec4;
#pragma pack(pop)
kmVec4 *kmVec4Fill(kmVec4 *pOut, float x, float y, float z, float w);
kmVec4 *kmVec4Add(kmVec4 *pOut, const kmVec4 *pV1, const kmVec4 *pV2);
float kmVec4Dot(const kmVec4 *pV1, const kmVec4 *pV2);
float kmVec4Length(const kmVec4 *pIn);
float kmVec4LengthSq(const kmVec4 *pIn);
kmVec4 *kmVec4Lerp(kmVec4 *pOut, const kmVec4 *pV1, const kmVec4 *pV2, float t);
kmVec4 *kmVec4Normalize(kmVec4 *pOut, const kmVec4 *pIn);
kmVec4 *kmVec4Scale(kmVec4 *pOut, const kmVec4 *pIn, const float s);
kmVec4 *kmVec4Subtract(kmVec4 *pOut, const kmVec4 *pV1, const kmVec4 *pV2);
kmVec4 *kmVec4Mul(kmVec4 *pOut, const kmVec4 *pV1, const kmVec4 *pV2);
kmVec4 *kmVec4Div(kmVec4 *pOut, const kmVec4 *pV1, const kmVec4 *pV2);
kmVec4 *kmVec4MultiplyMat4(kmVec4 *pOut, const kmVec4 *pV, const struct kmMat4 *pM);
kmVec4 *kmVec4Transform(kmVec4 *pOut, const kmVec4 *pV, const struct kmMat4 *pM);
kmVec4 *kmVec4TransformArray(kmVec4 *pOut, unsigned int outStride, const kmVec4 *pV, unsigned int vStride, const struct kmMat4 *pM, unsigned int count);
int kmVec4AreEqual(const kmVec4 *p1, const kmVec4 *p2);
kmVec4 *kmVec4Assign(kmVec4 *pOut, const kmVec4 *pIn);
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
kmVec4 *kmVec4Fill(kmVec4 *pOut, float x, float y, float z, float w)
{
  pOut->x = x;
  pOut->y = y;
  pOut->z = z;
  pOut->w = w;
  return pOut;
}

kmVec4 *kmVec4Add(kmVec4 *pOut, const kmVec4 *pV1, const kmVec4 *pV2)
{
  pOut->x = pV1->x + pV2->x;
  pOut->y = pV1->y + pV2->y;
  pOut->z = pV1->z + pV2->z;
  pOut->w = pV1->w + pV2->w;
  return pOut;
}

float kmVec4Dot(const kmVec4 *pV1, const kmVec4 *pV2)
{
  return (((pV1->x * pV2->x) + (pV1->y * pV2->y)) + (pV1->z * pV2->z)) + (pV1->w * pV2->w);
}

float kmVec4Length(const kmVec4 *pIn)
{
  return sqrtf(((kmSQR(pIn->x) + kmSQR(pIn->y)) + kmSQR(pIn->z)) + kmSQR(pIn->w));
}

float kmVec4LengthSq(const kmVec4 *pIn)
{
  return ((kmSQR(pIn->x) + kmSQR(pIn->y)) + kmSQR(pIn->z)) + kmSQR(pIn->w);
}

kmVec4 *kmVec4Lerp(kmVec4 *pOut, const kmVec4 *pV1, const kmVec4 *pV2, float t)
{
  pOut->x = pV1->x + (t * (pV2->x - pV1->x));
  pOut->y = pV1->y + (t * (pV2->y - pV1->y));
  pOut->z = pV1->z + (t * (pV2->z - pV1->z));
  pOut->w = pV1->w + (t * (pV2->w - pV1->w));
  return pOut;
}

kmVec4 *kmVec4Normalize(kmVec4 *pOut, const kmVec4 *pIn)
{
  if ((((!pIn->x) && (!pIn->y)) && (!pIn->z)) && (!pIn->w))
  {
    return kmVec4Assign(pOut, pIn);
  }
  float l = 1.0f / kmVec4Length(pIn);
  pOut->x = pIn->x * l;
  pOut->y = pIn->y * l;
  pOut->z = pIn->z * l;
  pOut->w = pIn->w * l;
  return pOut;
}

kmVec4 *kmVec4Scale(kmVec4 *pOut, const kmVec4 *pIn, const float s)
{
  kmVec4Normalize(pOut, pIn);
  pOut->x *= s;
  pOut->y *= s;
  pOut->z *= s;
  pOut->w *= s;
  return pOut;
}

kmVec4 *kmVec4Subtract(kmVec4 *pOut, const kmVec4 *pV1, const kmVec4 *pV2)
{
  pOut->x = pV1->x - pV2->x;
  pOut->y = pV1->y - pV2->y;
  pOut->z = pV1->z - pV2->z;
  pOut->w = pV1->w - pV2->w;
  return pOut;
}

kmVec4 *kmVec4Mul(kmVec4 *pOut, const kmVec4 *pV1, const kmVec4 *pV2)
{
  pOut->x = pV1->x * pV2->x;
  pOut->y = pV1->y * pV2->y;
  pOut->z = pV1->z * pV2->z;
  pOut->w = pV1->w * pV2->w;
  return pOut;
}

kmVec4 *kmVec4Div(kmVec4 *pOut, const kmVec4 *pV1, const kmVec4 *pV2)
{
  if (((pV2->x && pV2->y) && pV2->z) && pV2->w)
  {
    pOut->x = pV1->x / pV2->x;
    pOut->y = pV1->y / pV2->y;
    pOut->z = pV1->z / pV2->z;
    pOut->w = pV1->w / pV2->w;
  }
  return pOut;
}

kmVec4 *kmVec4MultiplyMat4(kmVec4 *pOut, const kmVec4 *pV, const struct kmMat4 *pM)
{
  pOut->x = (((pV->x * pM->mat[0]) + (pV->y * pM->mat[4])) + (pV->z * pM->mat[8])) + (pV->w * pM->mat[12]);
  pOut->y = (((pV->x * pM->mat[1]) + (pV->y * pM->mat[5])) + (pV->z * pM->mat[9])) + (pV->w * pM->mat[13]);
  pOut->z = (((pV->x * pM->mat[2]) + (pV->y * pM->mat[6])) + (pV->z * pM->mat[10])) + (pV->w * pM->mat[14]);
  pOut->w = (((pV->x * pM->mat[3]) + (pV->y * pM->mat[7])) + (pV->z * pM->mat[11])) + (pV->w * pM->mat[15]);
  return pOut;
}

kmVec4 *kmVec4Transform(kmVec4 *pOut, const kmVec4 *pV, const kmMat4 *pM)
{
  return kmVec4MultiplyMat4(pOut, pV, pM);
}

kmVec4 *kmVec4TransformArray(kmVec4 *pOut, unsigned int outStride, const kmVec4 *pV, unsigned int vStride, const kmMat4 *pM, unsigned int count)
{
  unsigned int i = 0;
  while (i < count)
  {
    const kmVec4 *in = pV + (i * vStride);
    kmVec4 *out = pOut + (i * outStride);
    kmVec4Transform(out, in, pM);
    i += 1;
  }

  return pOut;
}

int kmVec4AreEqual(const kmVec4 *p1, const kmVec4 *p2)
{
  return ((((p1->x < (p2->x + 0.0001)) && (p1->x > (p2->x - 0.0001))) && ((p1->y < (p2->y + 0.0001)) && (p1->y > (p2->y - 0.0001)))) && ((p1->z < (p2->z + 0.0001)) && (p1->z > (p2->z - 0.0001)))) && ((p1->w < (p2->w + 0.0001)) && (p1->w > (p2->w - 0.0001)));
}

kmVec4 *kmVec4Assign(kmVec4 *pOut, const kmVec4 *pIn)
{
  assert(pOut != pIn);
  memcpy(pOut, pIn, (sizeof(float)) * 4);
  return pOut;
}

