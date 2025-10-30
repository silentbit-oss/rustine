#include <assert.h>
#include <mat4.h>
#include <math.h>
#include <plane.c>
#include <plane.h>
#include <stdlib.h>
#include <utility.h>
#include <vec3.h>
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
struct kmVec4;
struct kmMat4;
typedef struct kmPlane
{
  float a;
  float b;
  float c;
  float d;
} kmPlane;
typedef enum KM_POINT_CLASSIFICATION
{
  POINT_BEHIND_PLANE = -1,
  POINT_ON_PLANE = 0,
  POINT_INFRONT_OF_PLANE = 1
} KM_POINT_CLASSIFICATION;
kmPlane *kmPlaneFill(kmPlane *plane, float a, float b, float c, float d);
float kmPlaneDot(const kmPlane *pP, const struct kmVec4 *pV);
float kmPlaneDotCoord(const kmPlane *pP, const struct kmVec3 *pV);
float kmPlaneDotNormal(const kmPlane *pP, const struct kmVec3 *pV);
kmPlane *kmPlaneFromNormalAndDistance(kmPlane *plane, const struct kmVec3 *normal, const float dist);
kmPlane *kmPlaneFromPointAndNormal(kmPlane *pOut, const struct kmVec3 *pPoint, const struct kmVec3 *pNormal);
kmPlane *kmPlaneFromPoints(kmPlane *pOut, const struct kmVec3 *p1, const struct kmVec3 *p2, const struct kmVec3 *p3);
struct kmVec3 *kmPlaneIntersectLine(struct kmVec3 *pOut, const kmPlane *pP, const struct kmVec3 *pV1, const struct kmVec3 *pV2);
kmPlane *kmPlaneNormalize(kmPlane *pOut, const kmPlane *pP);
kmPlane *kmPlaneScale(kmPlane *pOut, const kmPlane *pP, float s);
KM_POINT_CLASSIFICATION kmPlaneClassifyPoint(const kmPlane *pIn, const struct kmVec3 *pP);
kmPlane *kmPlaneExtractFromMat4(kmPlane *pOut, const struct kmMat4 *pIn, int row);
struct kmVec3 *kmPlaneGetIntersection(struct kmVec3 *pOut, const kmPlane *p1, const kmPlane *p2, const kmPlane *p3);
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
float kmPlaneDot(const kmPlane *pP, const kmVec4 *pV)
{
  return (((pP->a * pV->x) + (pP->b * pV->y)) + (pP->c * pV->z)) + (pP->d * pV->w);
}

float kmPlaneDotCoord(const kmPlane *pP, const kmVec3 *pV)
{
  return (((pP->a * pV->x) + (pP->b * pV->y)) + (pP->c * pV->z)) + pP->d;
}

float kmPlaneDotNormal(const kmPlane *pP, const kmVec3 *pV)
{
  return ((pP->a * pV->x) + (pP->b * pV->y)) + (pP->c * pV->z);
}

kmPlane *kmPlaneFromNormalAndDistance(kmPlane *plane, const struct kmVec3 *normal, const float dist)
{
  plane->a = normal->x;
  plane->b = normal->y;
  plane->c = normal->z;
  plane->d = dist;
  return plane;
}

kmPlane *kmPlaneFromPointAndNormal(kmPlane *pOut, const kmVec3 *pPoint, const kmVec3 *pNormal)
{
  pOut->a = pNormal->x;
  pOut->b = pNormal->y;
  pOut->c = pNormal->z;
  pOut->d = -kmVec3Dot(pNormal, pPoint);
  return pOut;
}

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

kmPlane *kmPlaneScale(kmPlane *pOut, const kmPlane *pP, float s)
{
  assert(0 && "Not implemented");
  return 0;
}

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

kmPlane *kmPlaneFill(kmPlane *plane, float a, float b, float c, float d)
{
  plane->a = a;
  plane->b = b;
  plane->c = c;
  plane->d = d;
  return plane;
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
struct kmVec4;
struct kmMat4;
typedef struct kmPlane
{
  float a;
  float b;
  float c;
  float d;
} kmPlane;
typedef enum KM_POINT_CLASSIFICATION
{
  POINT_BEHIND_PLANE = -1,
  POINT_ON_PLANE = 0,
  POINT_INFRONT_OF_PLANE = 1
} KM_POINT_CLASSIFICATION;
kmPlane *kmPlaneFill(kmPlane *plane, float a, float b, float c, float d);
float kmPlaneDot(const kmPlane *pP, const struct kmVec4 *pV);
float kmPlaneDotCoord(const kmPlane *pP, const struct kmVec3 *pV);
float kmPlaneDotNormal(const kmPlane *pP, const struct kmVec3 *pV);
kmPlane *kmPlaneFromNormalAndDistance(kmPlane *plane, const struct kmVec3 *normal, const float dist);
kmPlane *kmPlaneFromPointAndNormal(kmPlane *pOut, const struct kmVec3 *pPoint, const struct kmVec3 *pNormal);
kmPlane *kmPlaneFromPoints(kmPlane *pOut, const struct kmVec3 *p1, const struct kmVec3 *p2, const struct kmVec3 *p3);
struct kmVec3 *kmPlaneIntersectLine(struct kmVec3 *pOut, const kmPlane *pP, const struct kmVec3 *pV1, const struct kmVec3 *pV2);
kmPlane *kmPlaneNormalize(kmPlane *pOut, const kmPlane *pP);
kmPlane *kmPlaneScale(kmPlane *pOut, const kmPlane *pP, float s);
KM_POINT_CLASSIFICATION kmPlaneClassifyPoint(const kmPlane *pIn, const struct kmVec3 *pP);
kmPlane *kmPlaneExtractFromMat4(kmPlane *pOut, const struct kmMat4 *pIn, int row);
struct kmVec3 *kmPlaneGetIntersection(struct kmVec3 *pOut, const kmPlane *p1, const kmPlane *p2, const kmPlane *p3);
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
float kmPlaneDot(const kmPlane *pP, const kmVec4 *pV)
{
  return (((pP->a * pV->x) + (pP->b * pV->y)) + (pP->c * pV->z)) + (pP->d * pV->w);
}

float kmPlaneDotCoord(const kmPlane *pP, const kmVec3 *pV)
{
  return (((pP->a * pV->x) + (pP->b * pV->y)) + (pP->c * pV->z)) + pP->d;
}

float kmPlaneDotNormal(const kmPlane *pP, const kmVec3 *pV)
{
  return ((pP->a * pV->x) + (pP->b * pV->y)) + (pP->c * pV->z);
}

kmPlane *kmPlaneFromNormalAndDistance(kmPlane *plane, const struct kmVec3 *normal, const float dist)
{
  plane->a = normal->x;
  plane->b = normal->y;
  plane->c = normal->z;
  plane->d = dist;
  return plane;
}

kmPlane *kmPlaneFromPointAndNormal(kmPlane *pOut, const kmVec3 *pPoint, const kmVec3 *pNormal)
{
  pOut->a = pNormal->x;
  pOut->b = pNormal->y;
  pOut->c = pNormal->z;
  pOut->d = -kmVec3Dot(pNormal, pPoint);
  return pOut;
}

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

kmPlane *kmPlaneScale(kmPlane *pOut, const kmPlane *pP, float s)
{
  assert(0 && "Not implemented");
  return 0;
}

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

kmPlane *kmPlaneFill(kmPlane *plane, float a, float b, float c, float d)
{
  plane->a = a;
  plane->b = b;
  plane->c = c;
  plane->d = d;
  return plane;
}

