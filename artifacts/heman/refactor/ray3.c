#include <assert.h>
#include <math.h>
#include <plane.h>
#include <ray3.c>
#include <ray3.h>
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
typedef struct kmRay3
{
  kmVec3 start;
  kmVec3 dir;
} kmRay3;
struct kmPlane;
kmRay3 *kmRay3Fill(kmRay3 *ray, float px, float py, float pz, float vx, float vy, float vz);
kmRay3 *kmRay3FromPointAndDirection(kmRay3 *ray, const kmVec3 *point, const kmVec3 *direction);
unsigned char kmRay3IntersectPlane(kmVec3 *pOut, const kmRay3 *ray, const struct kmPlane *plane);
kmRay3 *kmRay3Fill(kmRay3 *ray, float px, float py, float pz, float vx, float vy, float vz)
{
  ray->start.x = px;
  ray->start.y = py;
  ray->start.z = pz;
  ray->dir.x = vx;
  ray->dir.y = vy;
  ray->dir.z = vz;
  return ray;
}

kmRay3 *kmRay3FromPointAndDirection(kmRay3 *ray, const kmVec3 *point, const kmVec3 *direction)
{
  kmVec3Assign(&ray->start, point);
  kmVec3Assign(&ray->dir, direction);
  return ray;
}

unsigned char kmRay3IntersectPlane(kmVec3 *pOut, const kmRay3 *ray, const kmPlane *plane)
{
  float d = ((plane->a * ray->dir.x) + (plane->b * ray->dir.y)) + (plane->c * ray->dir.z);
  if (d == 0)
  {
    return 0;
  }
  float t = (-((((plane->a * ray->start.x) + (plane->b * ray->start.y)) + (plane->c * ray->start.z)) + plane->d)) / d;
  if (t < 0)
  {
    return 0;
  }
  kmVec3 scaled_dir;
  kmVec3Scale(&scaled_dir, &ray->dir, t);
  kmVec3Add(pOut, &ray->start, &scaled_dir);
  return 1;
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
typedef struct kmRay3
{
  kmVec3 start;
  kmVec3 dir;
} kmRay3;
struct kmPlane;
kmRay3 *kmRay3Fill(kmRay3 *ray, float px, float py, float pz, float vx, float vy, float vz);
kmRay3 *kmRay3FromPointAndDirection(kmRay3 *ray, const kmVec3 *point, const kmVec3 *direction);
unsigned char kmRay3IntersectPlane(kmVec3 *pOut, const kmRay3 *ray, const struct kmPlane *plane);
kmRay3 *kmRay3Fill(kmRay3 *ray, float px, float py, float pz, float vx, float vy, float vz)
{
  ray->start.x = px;
  ray->start.y = py;
  ray->start.z = pz;
  ray->dir.x = vx;
  ray->dir.y = vy;
  ray->dir.z = vz;
  return ray;
}

kmRay3 *kmRay3FromPointAndDirection(kmRay3 *ray, const kmVec3 *point, const kmVec3 *direction)
{
  kmVec3Assign(&ray->start, point);
  kmVec3Assign(&ray->dir, direction);
  return ray;
}

unsigned char kmRay3IntersectPlane(kmVec3 *pOut, const kmRay3 *ray, const kmPlane *plane)
{
  float d = ((plane->a * ray->dir.x) + (plane->b * ray->dir.y)) + (plane->c * ray->dir.z);
  if (d == 0)
  {
    return 0;
  }
  float t = (-((((plane->a * ray->start.x) + (plane->b * ray->start.y)) + (plane->c * ray->start.z)) + plane->d)) / d;
  if (t < 0)
  {
    return 0;
  }
  kmVec3 scaled_dir;
  kmVec3Scale(&scaled_dir, &ray->dir, t);
  kmVec3Add(pOut, &ray->start, &scaled_dir);
  return 1;
}

