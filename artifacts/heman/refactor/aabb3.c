#include <aabb3.c>
#include <aabb3.h>
#include <assert.h>
#include <math.h>
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
typedef struct kmAABB3
{
  kmVec3 min;
  kmVec3 max;
} kmAABB3;
kmAABB3 *kmAABB3Initialize(kmAABB3 *pBox, const kmVec3 *centre, const float width, const float height, const float depth);
int kmAABB3ContainsPoint(const kmAABB3 *pBox, const kmVec3 *pPoint);
kmAABB3 *kmAABB3Assign(kmAABB3 *pOut, const kmAABB3 *pIn);
kmAABB3 *kmAABB3Scale(kmAABB3 *pOut, const kmAABB3 *pIn, float s);
unsigned char kmAABB3IntersectsTriangle(kmAABB3 *box, const kmVec3 *p1, const kmVec3 *p2, const kmVec3 *p3);
unsigned char kmAABB3IntersectsAABB(const kmAABB3 *box, const kmAABB3 *other);
unsigned int kmAABB3ContainsAABB(const kmAABB3 *container, const kmAABB3 *to_check);
float kmAABB3DiameterX(const kmAABB3 *aabb);
float kmAABB3DiameterY(const kmAABB3 *aabb);
float kmAABB3DiameterZ(const kmAABB3 *aabb);
kmVec3 *kmAABB3Centre(const kmAABB3 *aabb, kmVec3 *pOut);
kmAABB3 *kmAABB3ExpandToContain(kmAABB3 *pOut, const kmAABB3 *pIn, const kmAABB3 *other);
kmAABB3 *kmAABB3Initialize(kmAABB3 *pBox, const kmVec3 *centre, const float width, const float height, const float depth)
{
  if (!pBox)
  {
    return 0;
  }
  kmVec3 origin;
  kmVec3 *point = (centre) ? ((kmVec3 *) centre) : (&origin);
  kmVec3Zero(&origin);
  pBox->min.x = point->x - (width / 2);
  pBox->min.y = point->y - (height / 2);
  pBox->min.z = point->z - (depth / 2);
  pBox->max.x = point->x + (width / 2);
  pBox->max.y = point->y + (height / 2);
  pBox->max.z = point->z + (depth / 2);
  return pBox;
}

int kmAABB3ContainsPoint(const kmAABB3 *pBox, const kmVec3 *pPoint)
{
  if ((((((pPoint->x >= pBox->min.x) && (pPoint->x <= pBox->max.x)) && (pPoint->y >= pBox->min.y)) && (pPoint->y <= pBox->max.y)) && (pPoint->z >= pBox->min.z)) && (pPoint->z <= pBox->max.z))
  {
    return 1;
  }
  return 0;
}

kmAABB3 *kmAABB3Assign(kmAABB3 *pOut, const kmAABB3 *pIn)
{
  kmVec3Assign(&pOut->min, &pIn->min);
  kmVec3Assign(&pOut->max, &pIn->max);
  return pOut;
}

kmAABB3 *kmAABB3Scale(kmAABB3 *pOut, const kmAABB3 *pIn, float s)
{
  assert(0 && "Not implemented");
  return pOut;
}

unsigned char kmAABB3IntersectsTriangle(kmAABB3 *box, const kmVec3 *p1, const kmVec3 *p2, const kmVec3 *p3)
{
  assert(0 && "Not implemented");
  return 1;
}

unsigned char kmAABB3IntersectsAABB(const kmAABB3 *box, const kmAABB3 *other)
{
  return kmAABB3ContainsAABB(box, other) != ((unsigned int) 0);
}

unsigned int kmAABB3ContainsAABB(const kmAABB3 *container, const kmAABB3 *to_check)
{
  kmVec3 corners[8];
  unsigned int result = (unsigned int) 2;
  unsigned char found = 0;
  kmVec3Fill(&corners[0], to_check->min.x, to_check->min.y, to_check->min.z);
  kmVec3Fill(&corners[1], to_check->max.x, to_check->min.y, to_check->min.z);
  kmVec3Fill(&corners[2], to_check->max.x, to_check->max.y, to_check->min.z);
  kmVec3Fill(&corners[3], to_check->min.x, to_check->max.y, to_check->min.z);
  kmVec3Fill(&corners[4], to_check->min.x, to_check->min.y, to_check->max.z);
  kmVec3Fill(&corners[5], to_check->max.x, to_check->min.y, to_check->max.z);
  kmVec3Fill(&corners[6], to_check->max.x, to_check->max.y, to_check->max.z);
  kmVec3Fill(&corners[7], to_check->min.x, to_check->max.y, to_check->max.z);
  for (unsigned char i = 0; i < 8; i += 1)
  {
    if (!kmAABB3ContainsPoint(container, &corners[i]))
    {
      result = (unsigned int) 1;
      if (found)
      {
        return result;
      }
    }
    else
    {
      found = 1;
    }
  }

  if (!found)
  {
    result = (unsigned int) 0;
  }
  return result;
}

float kmAABB3DiameterX(const kmAABB3 *aabb)
{
  return fabs(aabb->max.x - aabb->min.x);
}

float kmAABB3DiameterY(const kmAABB3 *aabb)
{
  return fabs(aabb->max.y - aabb->min.y);
}

float kmAABB3DiameterZ(const kmAABB3 *aabb)
{
  return fabs(aabb->max.z - aabb->min.z);
}

kmVec3 *kmAABB3Centre(const kmAABB3 *aabb, kmVec3 *pOut)
{
  kmVec3Add(pOut, &aabb->min, &aabb->max);
  kmVec3Scale(pOut, pOut, 0.5);
  return pOut;
}

kmAABB3 *kmAABB3ExpandToContain(kmAABB3 *pOut, const kmAABB3 *pIn, const kmAABB3 *other)
{
  kmAABB3 result;
  result.min.x = (pIn->min.x < other->min.x) ? (pIn->min.x) : (other->min.x);
  result.max.x = (pIn->max.x > other->max.x) ? (pIn->max.x) : (other->max.x);
  result.min.y = (pIn->min.y < other->min.y) ? (pIn->min.y) : (other->min.y);
  result.max.y = (pIn->max.y > other->max.y) ? (pIn->max.y) : (other->max.y);
  result.min.z = (pIn->min.z < other->min.z) ? (pIn->min.z) : (other->min.z);
  result.max.z = (pIn->max.z > other->max.z) ? (pIn->max.z) : (other->max.z);
  kmAABB3Assign(pOut, &result);
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
typedef struct kmAABB3
{
  kmVec3 min;
  kmVec3 max;
} kmAABB3;
kmAABB3 *kmAABB3Initialize(kmAABB3 *pBox, const kmVec3 *centre, const float width, const float height, const float depth);
int kmAABB3ContainsPoint(const kmAABB3 *pBox, const kmVec3 *pPoint);
kmAABB3 *kmAABB3Assign(kmAABB3 *pOut, const kmAABB3 *pIn);
kmAABB3 *kmAABB3Scale(kmAABB3 *pOut, const kmAABB3 *pIn, float s);
unsigned char kmAABB3IntersectsTriangle(kmAABB3 *box, const kmVec3 *p1, const kmVec3 *p2, const kmVec3 *p3);
unsigned char kmAABB3IntersectsAABB(const kmAABB3 *box, const kmAABB3 *other);
unsigned int kmAABB3ContainsAABB(const kmAABB3 *container, const kmAABB3 *to_check);
float kmAABB3DiameterX(const kmAABB3 *aabb);
float kmAABB3DiameterY(const kmAABB3 *aabb);
float kmAABB3DiameterZ(const kmAABB3 *aabb);
kmVec3 *kmAABB3Centre(const kmAABB3 *aabb, kmVec3 *pOut);
kmAABB3 *kmAABB3ExpandToContain(kmAABB3 *pOut, const kmAABB3 *pIn, const kmAABB3 *other);
kmAABB3 *kmAABB3Initialize(kmAABB3 *pBox, const kmVec3 *centre, const float width, const float height, const float depth)
{
  if (!pBox)
  {
    return 0;
  }
  kmVec3 origin;
  kmVec3 *point = (centre) ? ((kmVec3 *) centre) : (&origin);
  kmVec3Zero(&origin);
  pBox->min.x = point->x - (width / 2);
  pBox->min.y = point->y - (height / 2);
  pBox->min.z = point->z - (depth / 2);
  pBox->max.x = point->x + (width / 2);
  pBox->max.y = point->y + (height / 2);
  pBox->max.z = point->z + (depth / 2);
  return pBox;
}

int kmAABB3ContainsPoint(const kmAABB3 *pBox, const kmVec3 *pPoint)
{
  if ((((((pPoint->x >= pBox->min.x) && (pPoint->x <= pBox->max.x)) && (pPoint->y >= pBox->min.y)) && (pPoint->y <= pBox->max.y)) && (pPoint->z >= pBox->min.z)) && (pPoint->z <= pBox->max.z))
  {
    return 1;
  }
  return 0;
}

kmAABB3 *kmAABB3Assign(kmAABB3 *pOut, const kmAABB3 *pIn)
{
  kmVec3Assign(&pOut->min, &pIn->min);
  kmVec3Assign(&pOut->max, &pIn->max);
  return pOut;
}

kmAABB3 *kmAABB3Scale(kmAABB3 *pOut, const kmAABB3 *pIn, float s)
{
  assert(0 && "Not implemented");
  return pOut;
}

unsigned char kmAABB3IntersectsTriangle(kmAABB3 *box, const kmVec3 *p1, const kmVec3 *p2, const kmVec3 *p3)
{
  assert(0 && "Not implemented");
  return 1;
}

unsigned char kmAABB3IntersectsAABB(const kmAABB3 *box, const kmAABB3 *other)
{
  return kmAABB3ContainsAABB(box, other) != ((unsigned int) 0);
}

unsigned int kmAABB3ContainsAABB(const kmAABB3 *container, const kmAABB3 *to_check)
{
  kmVec3 corners[8];
  unsigned int result = (unsigned int) 2;
  unsigned char found = 0;
  kmVec3Fill(&corners[0], to_check->min.x, to_check->min.y, to_check->min.z);
  kmVec3Fill(&corners[1], to_check->max.x, to_check->min.y, to_check->min.z);
  kmVec3Fill(&corners[2], to_check->max.x, to_check->max.y, to_check->min.z);
  kmVec3Fill(&corners[3], to_check->min.x, to_check->max.y, to_check->min.z);
  kmVec3Fill(&corners[4], to_check->min.x, to_check->min.y, to_check->max.z);
  kmVec3Fill(&corners[5], to_check->max.x, to_check->min.y, to_check->max.z);
  kmVec3Fill(&corners[6], to_check->max.x, to_check->max.y, to_check->max.z);
  kmVec3Fill(&corners[7], to_check->min.x, to_check->max.y, to_check->max.z);
  for (unsigned char i = 0; i < 8; i += 1)
  {
    if (!kmAABB3ContainsPoint(container, &corners[i]))
    {
      result = (unsigned int) 1;
      if (found)
      {
        return result;
      }
    }
    else
    {
      found = 1;
    }
  }

  if (!found)
  {
    result = (unsigned int) 0;
  }
  return result;
}

float kmAABB3DiameterX(const kmAABB3 *aabb)
{
  return fabs(aabb->max.x - aabb->min.x);
}

float kmAABB3DiameterY(const kmAABB3 *aabb)
{
  return fabs(aabb->max.y - aabb->min.y);
}

float kmAABB3DiameterZ(const kmAABB3 *aabb)
{
  return fabs(aabb->max.z - aabb->min.z);
}

kmVec3 *kmAABB3Centre(const kmAABB3 *aabb, kmVec3 *pOut)
{
  kmVec3Add(pOut, &aabb->min, &aabb->max);
  kmVec3Scale(pOut, pOut, 0.5);
  return pOut;
}

kmAABB3 *kmAABB3ExpandToContain(kmAABB3 *pOut, const kmAABB3 *pIn, const kmAABB3 *other)
{
  kmAABB3 result;
  result.min.x = (pIn->min.x < other->min.x) ? (pIn->min.x) : (other->min.x);
  result.max.x = (pIn->max.x > other->max.x) ? (pIn->max.x) : (other->max.x);
  result.min.y = (pIn->min.y < other->min.y) ? (pIn->min.y) : (other->min.y);
  result.max.y = (pIn->max.y > other->max.y) ? (pIn->max.y) : (other->max.y);
  result.min.z = (pIn->min.z < other->min.z) ? (pIn->min.z) : (other->min.z);
  result.max.z = (pIn->max.z > other->max.z) ? (pIn->max.z) : (other->max.z);
  kmAABB3Assign(pOut, &result);
  return pOut;
}

