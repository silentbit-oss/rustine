#include <assert.h>
#include <mat3.h>
#include <mat4.c>
#include <mat4.h>
#include <math.h>
#include <memory.h>
#include <plane.h>
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
kmMat4 *kmMat4Fill(kmMat4 *pOut, const float *pMat)
{
  memcpy(pOut->mat, pMat, (sizeof(float)) * 16);
  return pOut;
}

kmMat4 *kmMat4Identity(kmMat4 *pOut)
{
  memset(pOut->mat, 0, (sizeof(float)) * 16);
  pOut->mat[0] = (pOut->mat[5] = (pOut->mat[10] = (pOut->mat[15] = 1.0f)));
  return pOut;
}

kmMat4 *kmMat4Inverse(kmMat4 *pOut, const kmMat4 *pM)
{
  kmMat4 tmp;
  double det;
  int i;
  tmp.mat[0] = ((((((pM->mat[5] * pM->mat[10]) * pM->mat[15]) - ((pM->mat[5] * pM->mat[11]) * pM->mat[14])) - ((pM->mat[9] * pM->mat[6]) * pM->mat[15])) + ((pM->mat[9] * pM->mat[7]) * pM->mat[14])) + ((pM->mat[13] * pM->mat[6]) * pM->mat[11])) - ((pM->mat[13] * pM->mat[7]) * pM->mat[10]);
  tmp.mat[4] = (((((((-pM->mat[4]) * pM->mat[10]) * pM->mat[15]) + ((pM->mat[4] * pM->mat[11]) * pM->mat[14])) + ((pM->mat[8] * pM->mat[6]) * pM->mat[15])) - ((pM->mat[8] * pM->mat[7]) * pM->mat[14])) - ((pM->mat[12] * pM->mat[6]) * pM->mat[11])) + ((pM->mat[12] * pM->mat[7]) * pM->mat[10]);
  tmp.mat[8] = ((((((pM->mat[4] * pM->mat[9]) * pM->mat[15]) - ((pM->mat[4] * pM->mat[11]) * pM->mat[13])) - ((pM->mat[8] * pM->mat[5]) * pM->mat[15])) + ((pM->mat[8] * pM->mat[7]) * pM->mat[13])) + ((pM->mat[12] * pM->mat[5]) * pM->mat[11])) - ((pM->mat[12] * pM->mat[7]) * pM->mat[9]);
  tmp.mat[12] = (((((((-pM->mat[4]) * pM->mat[9]) * pM->mat[14]) + ((pM->mat[4] * pM->mat[10]) * pM->mat[13])) + ((pM->mat[8] * pM->mat[5]) * pM->mat[14])) - ((pM->mat[8] * pM->mat[6]) * pM->mat[13])) - ((pM->mat[12] * pM->mat[5]) * pM->mat[10])) + ((pM->mat[12] * pM->mat[6]) * pM->mat[9]);
  tmp.mat[1] = (((((((-pM->mat[1]) * pM->mat[10]) * pM->mat[15]) + ((pM->mat[1] * pM->mat[11]) * pM->mat[14])) + ((pM->mat[9] * pM->mat[2]) * pM->mat[15])) - ((pM->mat[9] * pM->mat[3]) * pM->mat[14])) - ((pM->mat[13] * pM->mat[2]) * pM->mat[11])) + ((pM->mat[13] * pM->mat[3]) * pM->mat[10]);
  tmp.mat[5] = ((((((pM->mat[0] * pM->mat[10]) * pM->mat[15]) - ((pM->mat[0] * pM->mat[11]) * pM->mat[14])) - ((pM->mat[8] * pM->mat[2]) * pM->mat[15])) + ((pM->mat[8] * pM->mat[3]) * pM->mat[14])) + ((pM->mat[12] * pM->mat[2]) * pM->mat[11])) - ((pM->mat[12] * pM->mat[3]) * pM->mat[10]);
  tmp.mat[9] = (((((((-pM->mat[0]) * pM->mat[9]) * pM->mat[15]) + ((pM->mat[0] * pM->mat[11]) * pM->mat[13])) + ((pM->mat[8] * pM->mat[1]) * pM->mat[15])) - ((pM->mat[8] * pM->mat[3]) * pM->mat[13])) - ((pM->mat[12] * pM->mat[1]) * pM->mat[11])) + ((pM->mat[12] * pM->mat[3]) * pM->mat[9]);
  tmp.mat[13] = ((((((pM->mat[0] * pM->mat[9]) * pM->mat[14]) - ((pM->mat[0] * pM->mat[10]) * pM->mat[13])) - ((pM->mat[8] * pM->mat[1]) * pM->mat[14])) + ((pM->mat[8] * pM->mat[2]) * pM->mat[13])) + ((pM->mat[12] * pM->mat[1]) * pM->mat[10])) - ((pM->mat[12] * pM->mat[2]) * pM->mat[9]);
  tmp.mat[2] = ((((((pM->mat[1] * pM->mat[6]) * pM->mat[15]) - ((pM->mat[1] * pM->mat[7]) * pM->mat[14])) - ((pM->mat[5] * pM->mat[2]) * pM->mat[15])) + ((pM->mat[5] * pM->mat[3]) * pM->mat[14])) + ((pM->mat[13] * pM->mat[2]) * pM->mat[7])) - ((pM->mat[13] * pM->mat[3]) * pM->mat[6]);
  tmp.mat[6] = (((((((-pM->mat[0]) * pM->mat[6]) * pM->mat[15]) + ((pM->mat[0] * pM->mat[7]) * pM->mat[14])) + ((pM->mat[4] * pM->mat[2]) * pM->mat[15])) - ((pM->mat[4] * pM->mat[3]) * pM->mat[14])) - ((pM->mat[12] * pM->mat[2]) * pM->mat[7])) + ((pM->mat[12] * pM->mat[3]) * pM->mat[6]);
  tmp.mat[10] = ((((((pM->mat[0] * pM->mat[5]) * pM->mat[15]) - ((pM->mat[0] * pM->mat[7]) * pM->mat[13])) - ((pM->mat[4] * pM->mat[1]) * pM->mat[15])) + ((pM->mat[4] * pM->mat[3]) * pM->mat[13])) + ((pM->mat[12] * pM->mat[1]) * pM->mat[7])) - ((pM->mat[12] * pM->mat[3]) * pM->mat[5]);
  tmp.mat[14] = (((((((-pM->mat[0]) * pM->mat[5]) * pM->mat[14]) + ((pM->mat[0] * pM->mat[6]) * pM->mat[13])) + ((pM->mat[4] * pM->mat[1]) * pM->mat[14])) - ((pM->mat[4] * pM->mat[2]) * pM->mat[13])) - ((pM->mat[12] * pM->mat[1]) * pM->mat[6])) + ((pM->mat[12] * pM->mat[2]) * pM->mat[5]);
  tmp.mat[3] = (((((((-pM->mat[1]) * pM->mat[6]) * pM->mat[11]) + ((pM->mat[1] * pM->mat[7]) * pM->mat[10])) + ((pM->mat[5] * pM->mat[2]) * pM->mat[11])) - ((pM->mat[5] * pM->mat[3]) * pM->mat[10])) - ((pM->mat[9] * pM->mat[2]) * pM->mat[7])) + ((pM->mat[9] * pM->mat[3]) * pM->mat[6]);
  tmp.mat[7] = ((((((pM->mat[0] * pM->mat[6]) * pM->mat[11]) - ((pM->mat[0] * pM->mat[7]) * pM->mat[10])) - ((pM->mat[4] * pM->mat[2]) * pM->mat[11])) + ((pM->mat[4] * pM->mat[3]) * pM->mat[10])) + ((pM->mat[8] * pM->mat[2]) * pM->mat[7])) - ((pM->mat[8] * pM->mat[3]) * pM->mat[6]);
  tmp.mat[11] = (((((((-pM->mat[0]) * pM->mat[5]) * pM->mat[11]) + ((pM->mat[0] * pM->mat[7]) * pM->mat[9])) + ((pM->mat[4] * pM->mat[1]) * pM->mat[11])) - ((pM->mat[4] * pM->mat[3]) * pM->mat[9])) - ((pM->mat[8] * pM->mat[1]) * pM->mat[7])) + ((pM->mat[8] * pM->mat[3]) * pM->mat[5]);
  tmp.mat[15] = ((((((pM->mat[0] * pM->mat[5]) * pM->mat[10]) - ((pM->mat[0] * pM->mat[6]) * pM->mat[9])) - ((pM->mat[4] * pM->mat[1]) * pM->mat[10])) + ((pM->mat[4] * pM->mat[2]) * pM->mat[9])) + ((pM->mat[8] * pM->mat[1]) * pM->mat[6])) - ((pM->mat[8] * pM->mat[2]) * pM->mat[5]);
  det = (((pM->mat[0] * tmp.mat[0]) + (pM->mat[1] * tmp.mat[4])) + (pM->mat[2] * tmp.mat[8])) + (pM->mat[3] * tmp.mat[12]);
  if (det == 0)
  {
    return 0;
  }
  det = 1.0 / det;
  for (i = 0; i < 16; i += 1)
  {
    pOut->mat[i] = tmp.mat[i] * det;
  }

  return pOut;
}

int kmMat4IsIdentity(const kmMat4 *pIn)
{
  static float identity[] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
  return memcmp(identity, pIn->mat, (sizeof(float)) * 16) == 0;
}

kmMat4 *kmMat4Transpose(kmMat4 *pOut, const kmMat4 *pIn)
{
  int x;
  int z;
  for (z = 0; z < 4; z += 1)
  {
    for (x = 0; x < 4; x += 1)
    {
      pOut->mat[(z * 4) + x] = pIn->mat[(x * 4) + z];
    }

  }

  return pOut;
}

kmMat4 *kmMat4Multiply(kmMat4 *pOut, const kmMat4 *pM1, const kmMat4 *pM2)
{
  float mat[16];
  const float *m1 = pM1->mat;
  const float *m2 = pM2->mat;
  mat[0] = (((m1[0] * m2[0]) + (m1[4] * m2[1])) + (m1[8] * m2[2])) + (m1[12] * m2[3]);
  mat[1] = (((m1[1] * m2[0]) + (m1[5] * m2[1])) + (m1[9] * m2[2])) + (m1[13] * m2[3]);
  mat[2] = (((m1[2] * m2[0]) + (m1[6] * m2[1])) + (m1[10] * m2[2])) + (m1[14] * m2[3]);
  mat[3] = (((m1[3] * m2[0]) + (m1[7] * m2[1])) + (m1[11] * m2[2])) + (m1[15] * m2[3]);
  mat[4] = (((m1[0] * m2[4]) + (m1[4] * m2[5])) + (m1[8] * m2[6])) + (m1[12] * m2[7]);
  mat[5] = (((m1[1] * m2[4]) + (m1[5] * m2[5])) + (m1[9] * m2[6])) + (m1[13] * m2[7]);
  mat[6] = (((m1[2] * m2[4]) + (m1[6] * m2[5])) + (m1[10] * m2[6])) + (m1[14] * m2[7]);
  mat[7] = (((m1[3] * m2[4]) + (m1[7] * m2[5])) + (m1[11] * m2[6])) + (m1[15] * m2[7]);
  mat[8] = (((m1[0] * m2[8]) + (m1[4] * m2[9])) + (m1[8] * m2[10])) + (m1[12] * m2[11]);
  mat[9] = (((m1[1] * m2[8]) + (m1[5] * m2[9])) + (m1[9] * m2[10])) + (m1[13] * m2[11]);
  mat[10] = (((m1[2] * m2[8]) + (m1[6] * m2[9])) + (m1[10] * m2[10])) + (m1[14] * m2[11]);
  mat[11] = (((m1[3] * m2[8]) + (m1[7] * m2[9])) + (m1[11] * m2[10])) + (m1[15] * m2[11]);
  mat[12] = (((m1[0] * m2[12]) + (m1[4] * m2[13])) + (m1[8] * m2[14])) + (m1[12] * m2[15]);
  mat[13] = (((m1[1] * m2[12]) + (m1[5] * m2[13])) + (m1[9] * m2[14])) + (m1[13] * m2[15]);
  mat[14] = (((m1[2] * m2[12]) + (m1[6] * m2[13])) + (m1[10] * m2[14])) + (m1[14] * m2[15]);
  mat[15] = (((m1[3] * m2[12]) + (m1[7] * m2[13])) + (m1[11] * m2[14])) + (m1[15] * m2[15]);
  memcpy(pOut->mat, mat, (sizeof(float)) * 16);
  return pOut;
}

kmMat4 *kmMat4Assign(kmMat4 *pOut, const kmMat4 *pIn)
{
  assert((pOut != pIn) && "You have tried to self-assign!!");
  memcpy(pOut->mat, pIn->mat, (sizeof(float)) * 16);
  return pOut;
}

kmMat4 *kmMat4AssignMat3(kmMat4 *pOut, const kmMat3 *pIn)
{
  kmMat4Identity(pOut);
  pOut->mat[0] = pIn->mat[0];
  pOut->mat[1] = pIn->mat[1];
  pOut->mat[2] = pIn->mat[2];
  pOut->mat[3] = 0.0;
  pOut->mat[4] = pIn->mat[3];
  pOut->mat[5] = pIn->mat[4];
  pOut->mat[6] = pIn->mat[5];
  pOut->mat[7] = 0.0;
  pOut->mat[8] = pIn->mat[6];
  pOut->mat[9] = pIn->mat[7];
  pOut->mat[10] = pIn->mat[8];
  pOut->mat[11] = 0.0;
  return pOut;
}

int kmMat4AreEqual(const kmMat4 *pMat1, const kmMat4 *pMat2)
{
  int i = 0;
  assert((pMat1 != pMat2) && "You are comparing the same thing!");
  for (i = 0; i < 16; i += 1)
  {
    if (!(((pMat1->mat[i] + 0.0001) > pMat2->mat[i]) && ((pMat1->mat[i] - 0.0001) < pMat2->mat[i])))
    {
      return 0;
    }
  }

  return 1;
}

kmMat4 *kmMat4RotationAxisAngle(kmMat4 *pOut, const kmVec3 *axis, float radians)
{
  kmQuaternion quat;
  kmQuaternionRotationAxisAngle(&quat, axis, radians);
  kmMat4RotationQuaternion(pOut, &quat);
  return pOut;
}

kmMat4 *kmMat4RotationX(kmMat4 *pOut, const float radians)
{
  pOut->mat[0] = 1.0f;
  pOut->mat[1] = 0.0f;
  pOut->mat[2] = 0.0f;
  pOut->mat[3] = 0.0f;
  pOut->mat[4] = 0.0f;
  pOut->mat[5] = cosf(radians);
  pOut->mat[6] = sinf(radians);
  pOut->mat[7] = 0.0f;
  pOut->mat[8] = 0.0f;
  pOut->mat[9] = -sinf(radians);
  pOut->mat[10] = cosf(radians);
  pOut->mat[11] = 0.0f;
  pOut->mat[12] = 0.0f;
  pOut->mat[13] = 0.0f;
  pOut->mat[14] = 0.0f;
  pOut->mat[15] = 1.0f;
  return pOut;
}

kmMat4 *kmMat4RotationY(kmMat4 *pOut, const float radians)
{
  pOut->mat[0] = cosf(radians);
  pOut->mat[1] = 0.0f;
  pOut->mat[2] = -sinf(radians);
  pOut->mat[3] = 0.0f;
  pOut->mat[4] = 0.0f;
  pOut->mat[5] = 1.0f;
  pOut->mat[6] = 0.0f;
  pOut->mat[7] = 0.0f;
  pOut->mat[8] = sinf(radians);
  pOut->mat[9] = 0.0f;
  pOut->mat[10] = cosf(radians);
  pOut->mat[11] = 0.0f;
  pOut->mat[12] = 0.0f;
  pOut->mat[13] = 0.0f;
  pOut->mat[14] = 0.0f;
  pOut->mat[15] = 1.0f;
  return pOut;
}

kmMat4 *kmMat4RotationZ(kmMat4 *pOut, const float radians)
{
  pOut->mat[0] = cosf(radians);
  pOut->mat[1] = sinf(radians);
  pOut->mat[2] = 0.0f;
  pOut->mat[3] = 0.0f;
  pOut->mat[4] = -sinf(radians);
  pOut->mat[5] = cosf(radians);
  pOut->mat[6] = 0.0f;
  pOut->mat[7] = 0.0f;
  pOut->mat[8] = 0.0f;
  pOut->mat[9] = 0.0f;
  pOut->mat[10] = 1.0f;
  pOut->mat[11] = 0.0f;
  pOut->mat[12] = 0.0f;
  pOut->mat[13] = 0.0f;
  pOut->mat[14] = 0.0f;
  pOut->mat[15] = 1.0f;
  return pOut;
}

kmMat4 *kmMat4RotationYawPitchRoll(kmMat4 *pOut, const float pitch, const float yaw, const float roll)
{
  kmMat4 yaw_matrix;
  kmMat4RotationY(&yaw_matrix, yaw);
  kmMat4 pitch_matrix;
  kmMat4RotationX(&pitch_matrix, pitch);
  kmMat4 roll_matrix;
  kmMat4RotationZ(&roll_matrix, roll);
  kmMat4Multiply(pOut, &pitch_matrix, &roll_matrix);
  kmMat4Multiply(pOut, &yaw_matrix, pOut);
  return pOut;
}

kmMat4 *kmMat4RotationQuaternion(kmMat4 *pOut, const kmQuaternion *pQ)
{
  double xx = pQ->x * pQ->x;
  double xy = pQ->x * pQ->y;
  double xz = pQ->x * pQ->z;
  double xw = pQ->x * pQ->w;
  double yy = pQ->y * pQ->y;
  double yz = pQ->y * pQ->z;
  double yw = pQ->y * pQ->w;
  double zz = pQ->z * pQ->z;
  double zw = pQ->z * pQ->w;
  pOut->mat[0] = 1 - (2 * (yy + zz));
  pOut->mat[1] = 2 * (xy + zw);
  pOut->mat[2] = 2 * (xz - yw);
  pOut->mat[3] = 0;
  pOut->mat[4] = 2 * (xy - zw);
  pOut->mat[5] = 1 - (2 * (xx + zz));
  pOut->mat[6] = 2 * (yz + xw);
  pOut->mat[7] = 0.0;
  pOut->mat[8] = 2 * (xz + yw);
  pOut->mat[9] = 2 * (yz - xw);
  pOut->mat[10] = 1 - (2 * (xx + yy));
  pOut->mat[11] = 0.0;
  pOut->mat[12] = 0.0;
  pOut->mat[13] = 0.0;
  pOut->mat[14] = 0.0;
  pOut->mat[15] = 1.0;
  return pOut;
}

kmMat4 *kmMat4Scaling(kmMat4 *pOut, const float x, const float y, float z)
{
  memset(pOut->mat, 0, (sizeof(float)) * 16);
  pOut->mat[0] = x;
  pOut->mat[5] = y;
  pOut->mat[10] = z;
  pOut->mat[15] = 1.0f;
  return pOut;
}

kmMat4 *kmMat4Translation(kmMat4 *pOut, const float x, float y, const float z)
{
  memset(pOut->mat, 0, (sizeof(float)) * 16);
  pOut->mat[0] = 1.0f;
  pOut->mat[5] = 1.0f;
  pOut->mat[10] = 1.0f;
  pOut->mat[12] = x;
  pOut->mat[13] = y;
  pOut->mat[14] = z;
  pOut->mat[15] = 1.0f;
  return pOut;
}

kmVec3 *kmMat4GetUpVec3(kmVec3 *pOut, const kmMat4 *pIn)
{
  kmVec3MultiplyMat4(pOut, &KM_VEC3_POS_Y, pIn);
  kmVec3Normalize(pOut, pOut);
  return pOut;
}

kmVec3 *kmMat4GetRightVec3(kmVec3 *pOut, const kmMat4 *pIn)
{
  kmVec3MultiplyMat4(pOut, &KM_VEC3_POS_X, pIn);
  kmVec3Normalize(pOut, pOut);
  return pOut;
}

kmVec3 *kmMat4GetForwardVec3RH(kmVec3 *pOut, const kmMat4 *pIn)
{
  kmVec3MultiplyMat4(pOut, &KM_VEC3_NEG_Z, pIn);
  kmVec3Normalize(pOut, pOut);
  return pOut;
}

kmVec3 *kmMat4GetForwardVec3LH(kmVec3 *pOut, const kmMat4 *pIn)
{
  kmVec3MultiplyMat4(pOut, &KM_VEC3_POS_Z, pIn);
  kmVec3Normalize(pOut, pOut);
  return pOut;
}

kmMat4 *kmMat4PerspectiveProjection(kmMat4 *pOut, float fovY, float aspect, float zNear, float zFar)
{
  float r = kmDegreesToRadians(fovY / 2);
  float deltaZ = zFar - zNear;
  float s = sin(r);
  float cotangent = 0;
  if (((deltaZ == 0) || (s == 0)) || (aspect == 0))
  {
    return 0;
  }
  cotangent = cos(r) / s;
  kmMat4Identity(pOut);
  pOut->mat[0] = cotangent / aspect;
  pOut->mat[5] = cotangent;
  pOut->mat[10] = (-(zFar + zNear)) / deltaZ;
  pOut->mat[11] = -1;
  pOut->mat[14] = (((-2) * zNear) * zFar) / deltaZ;
  pOut->mat[15] = 0;
  return pOut;
}

kmMat4 *kmMat4OrthographicProjection(kmMat4 *pOut, float left, float right, float bottom, float top, float nearVal, float farVal)
{
  float tx = -((right + left) / (right - left));
  float ty = -((top + bottom) / (top - bottom));
  float tz = -((farVal + nearVal) / (farVal - nearVal));
  kmMat4Identity(pOut);
  pOut->mat[0] = 2 / (right - left);
  pOut->mat[5] = 2 / (top - bottom);
  pOut->mat[10] = (-2) / (farVal - nearVal);
  pOut->mat[12] = tx;
  pOut->mat[13] = ty;
  pOut->mat[14] = tz;
  return pOut;
}

kmMat4 *kmMat4LookAt(kmMat4 *pOut, const kmVec3 *pEye, const kmVec3 *pCenter, const kmVec3 *pUp)
{
  kmVec3 f;
  kmVec3 up;
  kmVec3 s;
  kmVec3 u;
  kmMat4 translate;
  kmVec3Subtract(&f, pCenter, pEye);
  kmVec3Normalize(&f, &f);
  kmVec3Assign(&up, pUp);
  kmVec3Normalize(&up, &up);
  kmVec3Cross(&s, &f, &up);
  kmVec3Normalize(&s, &s);
  kmVec3Cross(&u, &s, &f);
  kmVec3Normalize(&s, &s);
  kmMat4Identity(pOut);
  pOut->mat[0] = s.x;
  pOut->mat[4] = s.y;
  pOut->mat[8] = s.z;
  pOut->mat[1] = u.x;
  pOut->mat[5] = u.y;
  pOut->mat[9] = u.z;
  pOut->mat[2] = -f.x;
  pOut->mat[6] = -f.y;
  pOut->mat[10] = -f.z;
  kmMat4Translation(&translate, -pEye->x, -pEye->y, -pEye->z);
  kmMat4Multiply(pOut, pOut, &translate);
  return pOut;
}

kmMat3 *kmMat4ExtractRotation(kmMat3 *pOut, const kmMat4 *pIn)
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

kmVec3 *kmMat4RotationToAxisAngle(kmVec3 *pAxis, float *radians, const kmMat4 *pIn)
{
  kmQuaternion temp;
  kmMat3 rotation;
  kmMat4ExtractRotation(&rotation, pIn);
  kmQuaternionRotationMatrix(&temp, &rotation);
  kmQuaternionToAxisAngle(&temp, pAxis, radians);
  return pAxis;
}

kmMat4 *kmMat4RotationTranslation(kmMat4 *pOut, const kmMat3 *rotation, const kmVec3 *translation)
{
  pOut->mat[0] = rotation->mat[0];
  pOut->mat[1] = rotation->mat[1];
  pOut->mat[2] = rotation->mat[2];
  pOut->mat[3] = 0.0f;
  pOut->mat[4] = rotation->mat[3];
  pOut->mat[5] = rotation->mat[4];
  pOut->mat[6] = rotation->mat[5];
  pOut->mat[7] = 0.0f;
  pOut->mat[8] = rotation->mat[6];
  pOut->mat[9] = rotation->mat[7];
  pOut->mat[10] = rotation->mat[8];
  pOut->mat[11] = 0.0f;
  pOut->mat[12] = translation->x;
  pOut->mat[13] = translation->y;
  pOut->mat[14] = translation->z;
  pOut->mat[15] = 1.0f;
  return pOut;
}

kmPlane *kmMat4ExtractPlane(kmPlane *pOut, const kmMat4 *pIn, const unsigned int plane)
{
  float t = 1.0f;
  switch (plane)
  {
    case 1:
    {
      pOut->a = pIn->mat[3] - pIn->mat[0];
      pOut->b = pIn->mat[7] - pIn->mat[4];
      pOut->c = pIn->mat[11] - pIn->mat[8];
      pOut->d = pIn->mat[15] - pIn->mat[12];
      break;
    }

    case 0:
    {
      pOut->a = pIn->mat[3] + pIn->mat[0];
      pOut->b = pIn->mat[7] + pIn->mat[4];
      pOut->c = pIn->mat[11] + pIn->mat[8];
      pOut->d = pIn->mat[15] + pIn->mat[12];
      break;
    }

    case 2:
    {
      pOut->a = pIn->mat[3] + pIn->mat[1];
      pOut->b = pIn->mat[7] + pIn->mat[5];
      pOut->c = pIn->mat[11] + pIn->mat[9];
      pOut->d = pIn->mat[15] + pIn->mat[13];
      break;
    }

    case 3:
    {
      pOut->a = pIn->mat[3] - pIn->mat[1];
      pOut->b = pIn->mat[7] - pIn->mat[5];
      pOut->c = pIn->mat[11] - pIn->mat[9];
      pOut->d = pIn->mat[15] - pIn->mat[13];
      break;
    }

    case 5:
    {
      pOut->a = pIn->mat[3] - pIn->mat[2];
      pOut->b = pIn->mat[7] - pIn->mat[6];
      pOut->c = pIn->mat[11] - pIn->mat[10];
      pOut->d = pIn->mat[15] - pIn->mat[14];
      break;
    }

    case 4:
    {
      pOut->a = pIn->mat[3] + pIn->mat[2];
      pOut->b = pIn->mat[7] + pIn->mat[6];
      pOut->c = pIn->mat[11] + pIn->mat[10];
      pOut->d = pIn->mat[15] + pIn->mat[14];
      break;
    }

    default:
    {
      assert(0 && "Invalid plane index");
    }

  }

  t = sqrtf(((pOut->a * pOut->a) + (pOut->b * pOut->b)) + (pOut->c * pOut->c));
  pOut->a /= t;
  pOut->b /= t;
  pOut->c /= t;
  pOut->d /= t;
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
kmMat4 *kmMat4Fill(kmMat4 *pOut, const float *pMat)
{
  memcpy(pOut->mat, pMat, (sizeof(float)) * 16);
  return pOut;
}

kmMat4 *kmMat4Identity(kmMat4 *pOut)
{
  memset(pOut->mat, 0, (sizeof(float)) * 16);
  pOut->mat[0] = (pOut->mat[5] = (pOut->mat[10] = (pOut->mat[15] = 1.0f)));
  return pOut;
}

kmMat4 *kmMat4Inverse(kmMat4 *pOut, const kmMat4 *pM)
{
  kmMat4 tmp;
  double det;
  int i;
  tmp.mat[0] = ((((((pM->mat[5] * pM->mat[10]) * pM->mat[15]) - ((pM->mat[5] * pM->mat[11]) * pM->mat[14])) - ((pM->mat[9] * pM->mat[6]) * pM->mat[15])) + ((pM->mat[9] * pM->mat[7]) * pM->mat[14])) + ((pM->mat[13] * pM->mat[6]) * pM->mat[11])) - ((pM->mat[13] * pM->mat[7]) * pM->mat[10]);
  tmp.mat[4] = (((((((-pM->mat[4]) * pM->mat[10]) * pM->mat[15]) + ((pM->mat[4] * pM->mat[11]) * pM->mat[14])) + ((pM->mat[8] * pM->mat[6]) * pM->mat[15])) - ((pM->mat[8] * pM->mat[7]) * pM->mat[14])) - ((pM->mat[12] * pM->mat[6]) * pM->mat[11])) + ((pM->mat[12] * pM->mat[7]) * pM->mat[10]);
  tmp.mat[8] = ((((((pM->mat[4] * pM->mat[9]) * pM->mat[15]) - ((pM->mat[4] * pM->mat[11]) * pM->mat[13])) - ((pM->mat[8] * pM->mat[5]) * pM->mat[15])) + ((pM->mat[8] * pM->mat[7]) * pM->mat[13])) + ((pM->mat[12] * pM->mat[5]) * pM->mat[11])) - ((pM->mat[12] * pM->mat[7]) * pM->mat[9]);
  tmp.mat[12] = (((((((-pM->mat[4]) * pM->mat[9]) * pM->mat[14]) + ((pM->mat[4] * pM->mat[10]) * pM->mat[13])) + ((pM->mat[8] * pM->mat[5]) * pM->mat[14])) - ((pM->mat[8] * pM->mat[6]) * pM->mat[13])) - ((pM->mat[12] * pM->mat[5]) * pM->mat[10])) + ((pM->mat[12] * pM->mat[6]) * pM->mat[9]);
  tmp.mat[1] = (((((((-pM->mat[1]) * pM->mat[10]) * pM->mat[15]) + ((pM->mat[1] * pM->mat[11]) * pM->mat[14])) + ((pM->mat[9] * pM->mat[2]) * pM->mat[15])) - ((pM->mat[9] * pM->mat[3]) * pM->mat[14])) - ((pM->mat[13] * pM->mat[2]) * pM->mat[11])) + ((pM->mat[13] * pM->mat[3]) * pM->mat[10]);
  tmp.mat[5] = ((((((pM->mat[0] * pM->mat[10]) * pM->mat[15]) - ((pM->mat[0] * pM->mat[11]) * pM->mat[14])) - ((pM->mat[8] * pM->mat[2]) * pM->mat[15])) + ((pM->mat[8] * pM->mat[3]) * pM->mat[14])) + ((pM->mat[12] * pM->mat[2]) * pM->mat[11])) - ((pM->mat[12] * pM->mat[3]) * pM->mat[10]);
  tmp.mat[9] = (((((((-pM->mat[0]) * pM->mat[9]) * pM->mat[15]) + ((pM->mat[0] * pM->mat[11]) * pM->mat[13])) + ((pM->mat[8] * pM->mat[1]) * pM->mat[15])) - ((pM->mat[8] * pM->mat[3]) * pM->mat[13])) - ((pM->mat[12] * pM->mat[1]) * pM->mat[11])) + ((pM->mat[12] * pM->mat[3]) * pM->mat[9]);
  tmp.mat[13] = ((((((pM->mat[0] * pM->mat[9]) * pM->mat[14]) - ((pM->mat[0] * pM->mat[10]) * pM->mat[13])) - ((pM->mat[8] * pM->mat[1]) * pM->mat[14])) + ((pM->mat[8] * pM->mat[2]) * pM->mat[13])) + ((pM->mat[12] * pM->mat[1]) * pM->mat[10])) - ((pM->mat[12] * pM->mat[2]) * pM->mat[9]);
  tmp.mat[2] = ((((((pM->mat[1] * pM->mat[6]) * pM->mat[15]) - ((pM->mat[1] * pM->mat[7]) * pM->mat[14])) - ((pM->mat[5] * pM->mat[2]) * pM->mat[15])) + ((pM->mat[5] * pM->mat[3]) * pM->mat[14])) + ((pM->mat[13] * pM->mat[2]) * pM->mat[7])) - ((pM->mat[13] * pM->mat[3]) * pM->mat[6]);
  tmp.mat[6] = (((((((-pM->mat[0]) * pM->mat[6]) * pM->mat[15]) + ((pM->mat[0] * pM->mat[7]) * pM->mat[14])) + ((pM->mat[4] * pM->mat[2]) * pM->mat[15])) - ((pM->mat[4] * pM->mat[3]) * pM->mat[14])) - ((pM->mat[12] * pM->mat[2]) * pM->mat[7])) + ((pM->mat[12] * pM->mat[3]) * pM->mat[6]);
  tmp.mat[10] = ((((((pM->mat[0] * pM->mat[5]) * pM->mat[15]) - ((pM->mat[0] * pM->mat[7]) * pM->mat[13])) - ((pM->mat[4] * pM->mat[1]) * pM->mat[15])) + ((pM->mat[4] * pM->mat[3]) * pM->mat[13])) + ((pM->mat[12] * pM->mat[1]) * pM->mat[7])) - ((pM->mat[12] * pM->mat[3]) * pM->mat[5]);
  tmp.mat[14] = (((((((-pM->mat[0]) * pM->mat[5]) * pM->mat[14]) + ((pM->mat[0] * pM->mat[6]) * pM->mat[13])) + ((pM->mat[4] * pM->mat[1]) * pM->mat[14])) - ((pM->mat[4] * pM->mat[2]) * pM->mat[13])) - ((pM->mat[12] * pM->mat[1]) * pM->mat[6])) + ((pM->mat[12] * pM->mat[2]) * pM->mat[5]);
  tmp.mat[3] = (((((((-pM->mat[1]) * pM->mat[6]) * pM->mat[11]) + ((pM->mat[1] * pM->mat[7]) * pM->mat[10])) + ((pM->mat[5] * pM->mat[2]) * pM->mat[11])) - ((pM->mat[5] * pM->mat[3]) * pM->mat[10])) - ((pM->mat[9] * pM->mat[2]) * pM->mat[7])) + ((pM->mat[9] * pM->mat[3]) * pM->mat[6]);
  tmp.mat[7] = ((((((pM->mat[0] * pM->mat[6]) * pM->mat[11]) - ((pM->mat[0] * pM->mat[7]) * pM->mat[10])) - ((pM->mat[4] * pM->mat[2]) * pM->mat[11])) + ((pM->mat[4] * pM->mat[3]) * pM->mat[10])) + ((pM->mat[8] * pM->mat[2]) * pM->mat[7])) - ((pM->mat[8] * pM->mat[3]) * pM->mat[6]);
  tmp.mat[11] = (((((((-pM->mat[0]) * pM->mat[5]) * pM->mat[11]) + ((pM->mat[0] * pM->mat[7]) * pM->mat[9])) + ((pM->mat[4] * pM->mat[1]) * pM->mat[11])) - ((pM->mat[4] * pM->mat[3]) * pM->mat[9])) - ((pM->mat[8] * pM->mat[1]) * pM->mat[7])) + ((pM->mat[8] * pM->mat[3]) * pM->mat[5]);
  tmp.mat[15] = ((((((pM->mat[0] * pM->mat[5]) * pM->mat[10]) - ((pM->mat[0] * pM->mat[6]) * pM->mat[9])) - ((pM->mat[4] * pM->mat[1]) * pM->mat[10])) + ((pM->mat[4] * pM->mat[2]) * pM->mat[9])) + ((pM->mat[8] * pM->mat[1]) * pM->mat[6])) - ((pM->mat[8] * pM->mat[2]) * pM->mat[5]);
  det = (((pM->mat[0] * tmp.mat[0]) + (pM->mat[1] * tmp.mat[4])) + (pM->mat[2] * tmp.mat[8])) + (pM->mat[3] * tmp.mat[12]);
  if (det == 0)
  {
    return 0;
  }
  det = 1.0 / det;
  for (i = 0; i < 16; i += 1)
  {
    pOut->mat[i] = tmp.mat[i] * det;
  }

  return pOut;
}

int kmMat4IsIdentity(const kmMat4 *pIn)
{
  static float identity[] = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
  return memcmp(identity, pIn->mat, (sizeof(float)) * 16) == 0;
}

kmMat4 *kmMat4Transpose(kmMat4 *pOut, const kmMat4 *pIn)
{
  int x;
  int z;
  for (z = 0; z < 4; z += 1)
  {
    for (x = 0; x < 4; x += 1)
    {
      pOut->mat[(z * 4) + x] = pIn->mat[(x * 4) + z];
    }

  }

  return pOut;
}

kmMat4 *kmMat4Multiply(kmMat4 *pOut, const kmMat4 *pM1, const kmMat4 *pM2)
{
  float mat[16];
  const float *m1 = pM1->mat;
  const float *m2 = pM2->mat;
  mat[0] = (((m1[0] * m2[0]) + (m1[4] * m2[1])) + (m1[8] * m2[2])) + (m1[12] * m2[3]);
  mat[1] = (((m1[1] * m2[0]) + (m1[5] * m2[1])) + (m1[9] * m2[2])) + (m1[13] * m2[3]);
  mat[2] = (((m1[2] * m2[0]) + (m1[6] * m2[1])) + (m1[10] * m2[2])) + (m1[14] * m2[3]);
  mat[3] = (((m1[3] * m2[0]) + (m1[7] * m2[1])) + (m1[11] * m2[2])) + (m1[15] * m2[3]);
  mat[4] = (((m1[0] * m2[4]) + (m1[4] * m2[5])) + (m1[8] * m2[6])) + (m1[12] * m2[7]);
  mat[5] = (((m1[1] * m2[4]) + (m1[5] * m2[5])) + (m1[9] * m2[6])) + (m1[13] * m2[7]);
  mat[6] = (((m1[2] * m2[4]) + (m1[6] * m2[5])) + (m1[10] * m2[6])) + (m1[14] * m2[7]);
  mat[7] = (((m1[3] * m2[4]) + (m1[7] * m2[5])) + (m1[11] * m2[6])) + (m1[15] * m2[7]);
  mat[8] = (((m1[0] * m2[8]) + (m1[4] * m2[9])) + (m1[8] * m2[10])) + (m1[12] * m2[11]);
  mat[9] = (((m1[1] * m2[8]) + (m1[5] * m2[9])) + (m1[9] * m2[10])) + (m1[13] * m2[11]);
  mat[10] = (((m1[2] * m2[8]) + (m1[6] * m2[9])) + (m1[10] * m2[10])) + (m1[14] * m2[11]);
  mat[11] = (((m1[3] * m2[8]) + (m1[7] * m2[9])) + (m1[11] * m2[10])) + (m1[15] * m2[11]);
  mat[12] = (((m1[0] * m2[12]) + (m1[4] * m2[13])) + (m1[8] * m2[14])) + (m1[12] * m2[15]);
  mat[13] = (((m1[1] * m2[12]) + (m1[5] * m2[13])) + (m1[9] * m2[14])) + (m1[13] * m2[15]);
  mat[14] = (((m1[2] * m2[12]) + (m1[6] * m2[13])) + (m1[10] * m2[14])) + (m1[14] * m2[15]);
  mat[15] = (((m1[3] * m2[12]) + (m1[7] * m2[13])) + (m1[11] * m2[14])) + (m1[15] * m2[15]);
  memcpy(pOut->mat, mat, (sizeof(float)) * 16);
  return pOut;
}

kmMat4 *kmMat4Assign(kmMat4 *pOut, const kmMat4 *pIn)
{
  assert((pOut != pIn) && "You have tried to self-assign!!");
  memcpy(pOut->mat, pIn->mat, (sizeof(float)) * 16);
  return pOut;
}

kmMat4 *kmMat4AssignMat3(kmMat4 *pOut, const kmMat3 *pIn)
{
  kmMat4Identity(pOut);
  pOut->mat[0] = pIn->mat[0];
  pOut->mat[1] = pIn->mat[1];
  pOut->mat[2] = pIn->mat[2];
  pOut->mat[3] = 0.0;
  pOut->mat[4] = pIn->mat[3];
  pOut->mat[5] = pIn->mat[4];
  pOut->mat[6] = pIn->mat[5];
  pOut->mat[7] = 0.0;
  pOut->mat[8] = pIn->mat[6];
  pOut->mat[9] = pIn->mat[7];
  pOut->mat[10] = pIn->mat[8];
  pOut->mat[11] = 0.0;
  return pOut;
}

int kmMat4AreEqual(const kmMat4 *pMat1, const kmMat4 *pMat2)
{
  int i = 0;
  assert((pMat1 != pMat2) && "You are comparing the same thing!");
  for (i = 0; i < 16; i += 1)
  {
    if (!(((pMat1->mat[i] + 0.0001) > pMat2->mat[i]) && ((pMat1->mat[i] - 0.0001) < pMat2->mat[i])))
    {
      return 0;
    }
  }

  return 1;
}

kmMat4 *kmMat4RotationAxisAngle(kmMat4 *pOut, const kmVec3 *axis, float radians)
{
  kmQuaternion quat;
  kmQuaternionRotationAxisAngle(&quat, axis, radians);
  kmMat4RotationQuaternion(pOut, &quat);
  return pOut;
}

kmMat4 *kmMat4RotationX(kmMat4 *pOut, const float radians)
{
  pOut->mat[0] = 1.0f;
  pOut->mat[1] = 0.0f;
  pOut->mat[2] = 0.0f;
  pOut->mat[3] = 0.0f;
  pOut->mat[4] = 0.0f;
  pOut->mat[5] = cosf(radians);
  pOut->mat[6] = sinf(radians);
  pOut->mat[7] = 0.0f;
  pOut->mat[8] = 0.0f;
  pOut->mat[9] = -sinf(radians);
  pOut->mat[10] = cosf(radians);
  pOut->mat[11] = 0.0f;
  pOut->mat[12] = 0.0f;
  pOut->mat[13] = 0.0f;
  pOut->mat[14] = 0.0f;
  pOut->mat[15] = 1.0f;
  return pOut;
}

kmMat4 *kmMat4RotationY(kmMat4 *pOut, const float radians)
{
  pOut->mat[0] = cosf(radians);
  pOut->mat[1] = 0.0f;
  pOut->mat[2] = -sinf(radians);
  pOut->mat[3] = 0.0f;
  pOut->mat[4] = 0.0f;
  pOut->mat[5] = 1.0f;
  pOut->mat[6] = 0.0f;
  pOut->mat[7] = 0.0f;
  pOut->mat[8] = sinf(radians);
  pOut->mat[9] = 0.0f;
  pOut->mat[10] = cosf(radians);
  pOut->mat[11] = 0.0f;
  pOut->mat[12] = 0.0f;
  pOut->mat[13] = 0.0f;
  pOut->mat[14] = 0.0f;
  pOut->mat[15] = 1.0f;
  return pOut;
}

kmMat4 *kmMat4RotationZ(kmMat4 *pOut, const float radians)
{
  pOut->mat[0] = cosf(radians);
  pOut->mat[1] = sinf(radians);
  pOut->mat[2] = 0.0f;
  pOut->mat[3] = 0.0f;
  pOut->mat[4] = -sinf(radians);
  pOut->mat[5] = cosf(radians);
  pOut->mat[6] = 0.0f;
  pOut->mat[7] = 0.0f;
  pOut->mat[8] = 0.0f;
  pOut->mat[9] = 0.0f;
  pOut->mat[10] = 1.0f;
  pOut->mat[11] = 0.0f;
  pOut->mat[12] = 0.0f;
  pOut->mat[13] = 0.0f;
  pOut->mat[14] = 0.0f;
  pOut->mat[15] = 1.0f;
  return pOut;
}

kmMat4 *kmMat4RotationYawPitchRoll(kmMat4 *pOut, const float pitch, const float yaw, const float roll)
{
  kmMat4 yaw_matrix;
  kmMat4RotationY(&yaw_matrix, yaw);
  kmMat4 pitch_matrix;
  kmMat4RotationX(&pitch_matrix, pitch);
  kmMat4 roll_matrix;
  kmMat4RotationZ(&roll_matrix, roll);
  kmMat4Multiply(pOut, &pitch_matrix, &roll_matrix);
  kmMat4Multiply(pOut, &yaw_matrix, pOut);
  return pOut;
}

kmMat4 *kmMat4RotationQuaternion(kmMat4 *pOut, const kmQuaternion *pQ)
{
  double xx = pQ->x * pQ->x;
  double xy = pQ->x * pQ->y;
  double xz = pQ->x * pQ->z;
  double xw = pQ->x * pQ->w;
  double yy = pQ->y * pQ->y;
  double yz = pQ->y * pQ->z;
  double yw = pQ->y * pQ->w;
  double zz = pQ->z * pQ->z;
  double zw = pQ->z * pQ->w;
  pOut->mat[0] = 1 - (2 * (yy + zz));
  pOut->mat[1] = 2 * (xy + zw);
  pOut->mat[2] = 2 * (xz - yw);
  pOut->mat[3] = 0;
  pOut->mat[4] = 2 * (xy - zw);
  pOut->mat[5] = 1 - (2 * (xx + zz));
  pOut->mat[6] = 2 * (yz + xw);
  pOut->mat[7] = 0.0;
  pOut->mat[8] = 2 * (xz + yw);
  pOut->mat[9] = 2 * (yz - xw);
  pOut->mat[10] = 1 - (2 * (xx + yy));
  pOut->mat[11] = 0.0;
  pOut->mat[12] = 0.0;
  pOut->mat[13] = 0.0;
  pOut->mat[14] = 0.0;
  pOut->mat[15] = 1.0;
  return pOut;
}

kmMat4 *kmMat4Scaling(kmMat4 *pOut, const float x, const float y, float z)
{
  memset(pOut->mat, 0, (sizeof(float)) * 16);
  pOut->mat[0] = x;
  pOut->mat[5] = y;
  pOut->mat[10] = z;
  pOut->mat[15] = 1.0f;
  return pOut;
}

kmMat4 *kmMat4Translation(kmMat4 *pOut, const float x, float y, const float z)
{
  memset(pOut->mat, 0, (sizeof(float)) * 16);
  pOut->mat[0] = 1.0f;
  pOut->mat[5] = 1.0f;
  pOut->mat[10] = 1.0f;
  pOut->mat[12] = x;
  pOut->mat[13] = y;
  pOut->mat[14] = z;
  pOut->mat[15] = 1.0f;
  return pOut;
}

kmVec3 *kmMat4GetUpVec3(kmVec3 *pOut, const kmMat4 *pIn)
{
  kmVec3MultiplyMat4(pOut, &KM_VEC3_POS_Y, pIn);
  kmVec3Normalize(pOut, pOut);
  return pOut;
}

kmVec3 *kmMat4GetRightVec3(kmVec3 *pOut, const kmMat4 *pIn)
{
  kmVec3MultiplyMat4(pOut, &KM_VEC3_POS_X, pIn);
  kmVec3Normalize(pOut, pOut);
  return pOut;
}

kmVec3 *kmMat4GetForwardVec3RH(kmVec3 *pOut, const kmMat4 *pIn)
{
  kmVec3MultiplyMat4(pOut, &KM_VEC3_NEG_Z, pIn);
  kmVec3Normalize(pOut, pOut);
  return pOut;
}

kmVec3 *kmMat4GetForwardVec3LH(kmVec3 *pOut, const kmMat4 *pIn)
{
  kmVec3MultiplyMat4(pOut, &KM_VEC3_POS_Z, pIn);
  kmVec3Normalize(pOut, pOut);
  return pOut;
}

kmMat4 *kmMat4PerspectiveProjection(kmMat4 *pOut, float fovY, float aspect, float zNear, float zFar)
{
  float r = kmDegreesToRadians(fovY / 2);
  float deltaZ = zFar - zNear;
  float s = sin(r);
  float cotangent = 0;
  if (((deltaZ == 0) || (s == 0)) || (aspect == 0))
  {
    return 0;
  }
  cotangent = cos(r) / s;
  kmMat4Identity(pOut);
  pOut->mat[0] = cotangent / aspect;
  pOut->mat[5] = cotangent;
  pOut->mat[10] = (-(zFar + zNear)) / deltaZ;
  pOut->mat[11] = -1;
  pOut->mat[14] = (((-2) * zNear) * zFar) / deltaZ;
  pOut->mat[15] = 0;
  return pOut;
}

kmMat4 *kmMat4OrthographicProjection(kmMat4 *pOut, float left, float right, float bottom, float top, float nearVal, float farVal)
{
  float tx = -((right + left) / (right - left));
  float ty = -((top + bottom) / (top - bottom));
  float tz = -((farVal + nearVal) / (farVal - nearVal));
  kmMat4Identity(pOut);
  pOut->mat[0] = 2 / (right - left);
  pOut->mat[5] = 2 / (top - bottom);
  pOut->mat[10] = (-2) / (farVal - nearVal);
  pOut->mat[12] = tx;
  pOut->mat[13] = ty;
  pOut->mat[14] = tz;
  return pOut;
}

kmMat4 *kmMat4LookAt(kmMat4 *pOut, const kmVec3 *pEye, const kmVec3 *pCenter, const kmVec3 *pUp)
{
  kmVec3 f;
  kmVec3 up;
  kmVec3 s;
  kmVec3 u;
  kmMat4 translate;
  kmVec3Subtract(&f, pCenter, pEye);
  kmVec3Normalize(&f, &f);
  kmVec3Assign(&up, pUp);
  kmVec3Normalize(&up, &up);
  kmVec3Cross(&s, &f, &up);
  kmVec3Normalize(&s, &s);
  kmVec3Cross(&u, &s, &f);
  kmVec3Normalize(&s, &s);
  kmMat4Identity(pOut);
  pOut->mat[0] = s.x;
  pOut->mat[4] = s.y;
  pOut->mat[8] = s.z;
  pOut->mat[1] = u.x;
  pOut->mat[5] = u.y;
  pOut->mat[9] = u.z;
  pOut->mat[2] = -f.x;
  pOut->mat[6] = -f.y;
  pOut->mat[10] = -f.z;
  kmMat4Translation(&translate, -pEye->x, -pEye->y, -pEye->z);
  kmMat4Multiply(pOut, pOut, &translate);
  return pOut;
}

kmMat3 *kmMat4ExtractRotation(kmMat3 *pOut, const kmMat4 *pIn)
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

kmVec3 *kmMat4RotationToAxisAngle(kmVec3 *pAxis, float *radians, const kmMat4 *pIn)
{
  kmQuaternion temp;
  kmMat3 rotation;
  kmMat4ExtractRotation(&rotation, pIn);
  kmQuaternionRotationMatrix(&temp, &rotation);
  kmQuaternionToAxisAngle(&temp, pAxis, radians);
  return pAxis;
}

kmMat4 *kmMat4RotationTranslation(kmMat4 *pOut, const kmMat3 *rotation, const kmVec3 *translation)
{
  pOut->mat[0] = rotation->mat[0];
  pOut->mat[1] = rotation->mat[1];
  pOut->mat[2] = rotation->mat[2];
  pOut->mat[3] = 0.0f;
  pOut->mat[4] = rotation->mat[3];
  pOut->mat[5] = rotation->mat[4];
  pOut->mat[6] = rotation->mat[5];
  pOut->mat[7] = 0.0f;
  pOut->mat[8] = rotation->mat[6];
  pOut->mat[9] = rotation->mat[7];
  pOut->mat[10] = rotation->mat[8];
  pOut->mat[11] = 0.0f;
  pOut->mat[12] = translation->x;
  pOut->mat[13] = translation->y;
  pOut->mat[14] = translation->z;
  pOut->mat[15] = 1.0f;
  return pOut;
}

kmPlane *kmMat4ExtractPlane(kmPlane *pOut, const kmMat4 *pIn, const unsigned int plane)
{
  float t = 1.0f;
  switch (plane)
  {
    case 1:
      pOut->a = pIn->mat[3] - pIn->mat[0];
      pOut->b = pIn->mat[7] - pIn->mat[4];
      pOut->c = pIn->mat[11] - pIn->mat[8];
      pOut->d = pIn->mat[15] - pIn->mat[12];
      break;

    case 0:
      pOut->a = pIn->mat[3] + pIn->mat[0];
      pOut->b = pIn->mat[7] + pIn->mat[4];
      pOut->c = pIn->mat[11] + pIn->mat[8];
      pOut->d = pIn->mat[15] + pIn->mat[12];
      break;

    case 2:
      pOut->a = pIn->mat[3] + pIn->mat[1];
      pOut->b = pIn->mat[7] + pIn->mat[5];
      pOut->c = pIn->mat[11] + pIn->mat[9];
      pOut->d = pIn->mat[15] + pIn->mat[13];
      break;

    case 3:
      pOut->a = pIn->mat[3] - pIn->mat[1];
      pOut->b = pIn->mat[7] - pIn->mat[5];
      pOut->c = pIn->mat[11] - pIn->mat[9];
      pOut->d = pIn->mat[15] - pIn->mat[13];
      break;

    case 5:
      pOut->a = pIn->mat[3] - pIn->mat[2];
      pOut->b = pIn->mat[7] - pIn->mat[6];
      pOut->c = pIn->mat[11] - pIn->mat[10];
      pOut->d = pIn->mat[15] - pIn->mat[14];
      break;

    case 4:
      pOut->a = pIn->mat[3] + pIn->mat[2];
      pOut->b = pIn->mat[7] + pIn->mat[6];
      pOut->c = pIn->mat[11] + pIn->mat[10];
      pOut->d = pIn->mat[15] + pIn->mat[14];
      break;

    default:
      assert(0 && "Invalid plane index");

  }

  t = sqrtf(((pOut->a * pOut->a) + (pOut->b * pOut->b)) + (pOut->c * pOut->c));
  pOut->a /= t;
  pOut->b /= t;
  pOut->c /= t;
  pOut->d /= t;
  return pOut;
}

