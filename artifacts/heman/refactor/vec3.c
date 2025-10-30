#include <assert.h>
#include <mat3.h>
#include <mat4.h>
#include <math.h>
#include <memory.h>
#include <plane.h>
#include <ray3.h>
#include <utility.h>
#include <vec3.c>
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
typedef struct kmRay3
{
  kmVec3 start;
  kmVec3 dir;
} kmRay3;
struct kmPlane;
kmRay3 *kmRay3Fill(kmRay3 *ray, float px, float py, float pz, float vx, float vy, float vz);
kmRay3 *kmRay3FromPointAndDirection(kmRay3 *ray, const kmVec3 *point, const kmVec3 *direction);
unsigned char kmRay3IntersectPlane(kmVec3 *pOut, const kmRay3 *ray, const struct kmPlane *plane);
const kmVec3 KM_VEC3_POS_Z = {0, 0, 1};
const kmVec3 KM_VEC3_NEG_Z = {0, 0, -1};
const kmVec3 KM_VEC3_POS_Y = {0, 1, 0};
const kmVec3 KM_VEC3_NEG_Y = {0, -1, 0};
const kmVec3 KM_VEC3_NEG_X = {-1, 0, 0};
const kmVec3 KM_VEC3_POS_X = {1, 0, 0};
const kmVec3 KM_VEC3_ZERO = {0, 0, 0};
kmVec3 *kmVec3Fill(kmVec3 *pOut, float x, float y, float z)
{
  pOut->x = x;
  pOut->y = y;
  pOut->z = z;
  return pOut;
}

float kmVec3Length(const kmVec3 *pIn)
{
  return sqrtf((kmSQR(pIn->x) + kmSQR(pIn->y)) + kmSQR(pIn->z));
}

float kmVec3LengthSq(const kmVec3 *pIn)
{
  return (kmSQR(pIn->x) + kmSQR(pIn->y)) + kmSQR(pIn->z);
}

kmVec3 *kmVec3Lerp(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2, float t)
{
  pOut->x = pV1->x + (t * (pV2->x - pV1->x));
  pOut->y = pV1->y + (t * (pV2->y - pV1->y));
  pOut->z = pV1->z + (t * (pV2->z - pV1->z));
  return pOut;
}

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

float kmVec3Dot(const kmVec3 *pV1, const kmVec3 *pV2)
{
  return ((pV1->x * pV2->x) + (pV1->y * pV2->y)) + (pV1->z * pV2->z);
}

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

kmVec3 *kmVec3Mul(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2)
{
  pOut->x = pV1->x * pV2->x;
  pOut->y = pV1->y * pV2->y;
  pOut->z = pV1->z * pV2->z;
  return pOut;
}

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

kmVec3 *kmVec3Transform(kmVec3 *pOut, const kmVec3 *pV, const kmMat4 *pM)
{
  return kmVec3MultiplyMat4(pOut, pV, pM);
}

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

kmVec3 *kmVec3Scale(kmVec3 *pOut, const kmVec3 *pIn, const float s)
{
  pOut->x = pIn->x * s;
  pOut->y = pIn->y * s;
  pOut->z = pIn->z * s;
  return pOut;
}

int kmVec3AreEqual(const kmVec3 *p1, const kmVec3 *p2)
{
  if ((((p1->x < (p2->x + 0.0001)) && (p1->x > (p2->x - 0.0001))) && ((p1->y < (p2->y + 0.0001)) && (p1->y > (p2->y - 0.0001)))) && ((p1->z < (p2->z + 0.0001)) && (p1->z > (p2->z - 0.0001))))
  {
    return 1;
  }
  return 0;
}

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

kmVec3 *kmVec3Zero(kmVec3 *pOut)
{
  pOut->x = 0.0f;
  pOut->y = 0.0f;
  pOut->z = 0.0f;
  return pOut;
}

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

kmVec3 *kmVec3Reflect(kmVec3 *pOut, const kmVec3 *pIn, const kmVec3 *normal)
{
  kmVec3 tmp;
  kmVec3Scale(&tmp, normal, 2.0f * kmVec3Dot(pIn, normal));
  kmVec3Subtract(pOut, pIn, &tmp);
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
typedef struct kmRay3
{
  kmVec3 start;
  kmVec3 dir;
} kmRay3;
struct kmPlane;
kmRay3 *kmRay3Fill(kmRay3 *ray, float px, float py, float pz, float vx, float vy, float vz);
kmRay3 *kmRay3FromPointAndDirection(kmRay3 *ray, const kmVec3 *point, const kmVec3 *direction);
unsigned char kmRay3IntersectPlane(kmVec3 *pOut, const kmRay3 *ray, const struct kmPlane *plane);
const kmVec3 KM_VEC3_POS_Z = {0, 0, 1};
const kmVec3 KM_VEC3_NEG_Z = {0, 0, -1};
const kmVec3 KM_VEC3_POS_Y = {0, 1, 0};
const kmVec3 KM_VEC3_NEG_Y = {0, -1, 0};
const kmVec3 KM_VEC3_NEG_X = {-1, 0, 0};
const kmVec3 KM_VEC3_POS_X = {1, 0, 0};
const kmVec3 KM_VEC3_ZERO = {0, 0, 0};
kmVec3 *kmVec3Fill(kmVec3 *pOut, float x, float y, float z)
{
  pOut->x = x;
  pOut->y = y;
  pOut->z = z;
  return pOut;
}

float kmVec3Length(const kmVec3 *pIn)
{
  return sqrtf((kmSQR(pIn->x) + kmSQR(pIn->y)) + kmSQR(pIn->z));
}

float kmVec3LengthSq(const kmVec3 *pIn)
{
  return (kmSQR(pIn->x) + kmSQR(pIn->y)) + kmSQR(pIn->z);
}

kmVec3 *kmVec3Lerp(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2, float t)
{
  pOut->x = pV1->x + (t * (pV2->x - pV1->x));
  pOut->y = pV1->y + (t * (pV2->y - pV1->y));
  pOut->z = pV1->z + (t * (pV2->z - pV1->z));
  return pOut;
}

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

float kmVec3Dot(const kmVec3 *pV1, const kmVec3 *pV2)
{
  return ((pV1->x * pV2->x) + (pV1->y * pV2->y)) + (pV1->z * pV2->z);
}

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

kmVec3 *kmVec3Mul(kmVec3 *pOut, const kmVec3 *pV1, const kmVec3 *pV2)
{
  pOut->x = pV1->x * pV2->x;
  pOut->y = pV1->y * pV2->y;
  pOut->z = pV1->z * pV2->z;
  return pOut;
}

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

kmVec3 *kmVec3Transform(kmVec3 *pOut, const kmVec3 *pV, const kmMat4 *pM)
{
  return kmVec3MultiplyMat4(pOut, pV, pM);
}

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

kmVec3 *kmVec3Scale(kmVec3 *pOut, const kmVec3 *pIn, const float s)
{
  pOut->x = pIn->x * s;
  pOut->y = pIn->y * s;
  pOut->z = pIn->z * s;
  return pOut;
}

int kmVec3AreEqual(const kmVec3 *p1, const kmVec3 *p2)
{
  if ((((p1->x < (p2->x + 0.0001)) && (p1->x > (p2->x - 0.0001))) && ((p1->y < (p2->y + 0.0001)) && (p1->y > (p2->y - 0.0001)))) && ((p1->z < (p2->z + 0.0001)) && (p1->z > (p2->z - 0.0001))))
  {
    return 1;
  }
  return 0;
}

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

kmVec3 *kmVec3Zero(kmVec3 *pOut)
{
  pOut->x = 0.0f;
  pOut->y = 0.0f;
  pOut->z = 0.0f;
  return pOut;
}

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

kmVec3 *kmVec3Reflect(kmVec3 *pOut, const kmVec3 *pIn, const kmVec3 *normal)
{
  kmVec3 tmp;
  kmVec3Scale(&tmp, normal, 2.0f * kmVec3Dot(pIn, normal));
  kmVec3Subtract(pOut, pIn, &tmp);
  return pOut;
}

