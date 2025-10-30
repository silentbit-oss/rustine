#include <aabb2.c>
#include <aabb2.h>
#include <math.h>
#include <utility.h>
#include <vec2.h>

extern float kmSQR(float s);
extern float kmDegreesToRadians(float degrees);
extern float kmRadiansToDegrees(float radians);
extern float kmMin(float lhs, float rhs);
extern float kmMax(float lhs, float rhs);
extern unsigned char kmAlmostEqual(float lhs, float rhs);
extern float kmClamp(float x, float min, float max);
extern float kmLerp(float x, float y, float factor);
struct kmMat3;
#pragma pack(push)
#pragma pack(1)
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2;
#pragma pack(pop)
kmVec2 *kmVec2Fill(kmVec2 *pOut, float x, float y);
float kmVec2Length(const kmVec2 *pIn);
float kmVec2LengthSq(const kmVec2 *pIn);
kmVec2 *kmVec2Normalize(kmVec2 *pOut, const kmVec2 *pIn);
kmVec2 *kmVec2Lerp(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2, float t);
kmVec2 *kmVec2Add(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2);
float kmVec2Dot(const kmVec2 *pV1, const kmVec2 *pV2);
float kmVec2Cross(const kmVec2 *pV1, const kmVec2 *pV2);
kmVec2 *kmVec2Subtract(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2);
kmVec2 *kmVec2Mul(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2);
kmVec2 *kmVec2Div(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2);
kmVec2 *kmVec2Transform(kmVec2 *pOut, const kmVec2 *pV1, const struct kmMat3 *pM);
kmVec2 *kmVec2TransformCoord(kmVec2 *pOut, const kmVec2 *pV, const struct kmMat3 *pM);
kmVec2 *kmVec2Scale(kmVec2 *pOut, const kmVec2 *pIn, const float s);
int kmVec2AreEqual(const kmVec2 *p1, const kmVec2 *p2);
kmVec2 *kmVec2Assign(kmVec2 *pOut, const kmVec2 *pIn);
kmVec2 *kmVec2RotateBy(kmVec2 *pOut, const kmVec2 *pIn, const float degrees, const kmVec2 *center);
float kmVec2DegreesBetween(const kmVec2 *v1, const kmVec2 *v2);
float kmVec2DistanceBetween(const kmVec2 *v1, const kmVec2 *v2);
kmVec2 *kmVec2MidPointBetween(kmVec2 *pOut, const kmVec2 *v1, const kmVec2 *v2);
kmVec2 *kmVec2Reflect(kmVec2 *pOut, const kmVec2 *pIn, const kmVec2 *normal);
extern const kmVec2 KM_VEC2_POS_Y;
extern const kmVec2 KM_VEC2_NEG_Y;
extern const kmVec2 KM_VEC2_NEG_X;
extern const kmVec2 KM_VEC2_POS_X;
extern const kmVec2 KM_VEC2_ZERO;
typedef struct kmAABB2
{
  kmVec2 min;
  kmVec2 max;
} kmAABB2;
kmAABB2 *kmAABB2Initialize(kmAABB2 *pBox, const kmVec2 *centre, const float width, const float height, const float depth);
kmAABB2 *kmAABB2Sanitize(kmAABB2 *pOut, const kmAABB2 *pIn);
int kmAABB2ContainsPoint(const kmAABB2 *pBox, const kmVec2 *pPoint);
kmAABB2 *kmAABB2Assign(kmAABB2 *pOut, const kmAABB2 *pIn);
kmAABB2 *kmAABB2Translate(kmAABB2 *pOut, const kmAABB2 *pIn, const kmVec2 *translation);
kmAABB2 *kmAABB2Scale(kmAABB2 *pOut, const kmAABB2 *pIn, float s);
kmAABB2 *kmAABB2ScaleWithPivot(kmAABB2 *pOut, const kmAABB2 *pIn, const kmVec2 *pivot, float s);
unsigned int kmAABB2ContainsAABB(const kmAABB2 *container, const kmAABB2 *to_check);
float kmAABB2DiameterX(const kmAABB2 *aabb);
float kmAABB2DiameterY(const kmAABB2 *aabb);
kmVec2 *kmAABB2Centre(const kmAABB2 *aabb, kmVec2 *pOut);
kmAABB2 *kmAABB2ExpandToContain(kmAABB2 *pOut, const kmAABB2 *pIn, const kmAABB2 *other);
kmAABB2 *kmAABB2Initialize(kmAABB2 *pBox, const kmVec2 *centre, const float width, const float height, const float depth)
{
  if (!pBox)
  {
    return 0;
  }
  kmVec2 origin;
  kmVec2 *point = (centre) ? ((kmVec2 *) centre) : (&origin);
  kmVec2Fill(&origin, .0f, .0f);
  pBox->min.x = point->x - (width / 2);
  pBox->min.y = point->y - (height / 2);
  pBox->max.x = point->x + (width / 2);
  pBox->max.y = point->y + (height / 2);
  return pBox;
}

kmAABB2 *kmAABB2Sanitize(kmAABB2 *pOut, const kmAABB2 *pIn)
{
  if (pIn->min.x <= pIn->max.x)
  {
    pOut->min.x = pIn->min.x;
    pOut->max.x = pIn->max.x;
  }
  else
  {
    pOut->min.x = pIn->max.x;
    pOut->max.x = pIn->min.x;
  }
  if (pIn->min.y <= pIn->max.y)
  {
    pOut->min.y = pIn->min.y;
    pOut->max.y = pIn->max.y;
  }
  else
  {
    pOut->min.y = pIn->max.y;
    pOut->max.y = pIn->min.y;
  }
  return pOut;
}

int kmAABB2ContainsPoint(const kmAABB2 *pBox, const kmVec2 *pPoint)
{
  if ((((pPoint->x >= pBox->min.x) && (pPoint->x <= pBox->max.x)) && (pPoint->y >= pBox->min.y)) && (pPoint->y <= pBox->max.y))
  {
    return 1;
  }
  return 0;
}

kmAABB2 *kmAABB2Assign(kmAABB2 *pOut, const kmAABB2 *pIn)
{
  kmVec2Assign(&pOut->min, &pIn->min);
  kmVec2Assign(&pOut->max, &pIn->max);
  return pOut;
}

kmAABB2 *kmAABB2Translate(kmAABB2 *pOut, const kmAABB2 *pIn, const kmVec2 *translation)
{
  kmVec2Add(&pOut->min, &pIn->min, translation);
  kmVec2Add(&pOut->max, &pIn->max, translation);
  return pOut;
}

kmAABB2 *kmAABB2Scale(kmAABB2 *pOut, const kmAABB2 *pIn, float s)
{
  kmVec2Scale(&pOut->max, &pIn->max, s);
  kmVec2Scale(&pOut->min, &pIn->min, s);
  return pOut;
}

kmAABB2 *kmAABB2ScaleWithPivot(kmAABB2 *pOut, const kmAABB2 *pIn, const kmVec2 *pivot, float s)
{
  kmVec2 translate;
  translate.x = -pivot->x;
  translate.y = -pivot->y;
  kmAABB2Translate(pOut, pIn, &translate);
  kmAABB2Scale(pOut, pIn, s);
  kmAABB2Translate(pOut, pIn, pivot);
  return pOut;
}

unsigned int kmAABB2ContainsAABB(const kmAABB2 *container, const kmAABB2 *to_check)
{
  kmVec2 corners[4];
  kmVec2Fill(&corners[0], to_check->min.x, to_check->min.y);
  kmVec2Fill(&corners[1], to_check->max.x, to_check->min.y);
  kmVec2Fill(&corners[2], to_check->max.x, to_check->max.y);
  kmVec2Fill(&corners[3], to_check->min.x, to_check->max.y);
  int nContains = ((kmAABB2ContainsPoint(container, &corners[0]) + kmAABB2ContainsPoint(container, &corners[1])) + kmAABB2ContainsPoint(container, &corners[2])) + kmAABB2ContainsPoint(container, &corners[3]);
  if (nContains == 0)
  {
    return (unsigned int) 0;
  }
  else
    if (nContains < 4)
  {
    return (unsigned int) 1;
  }
  else
  {
    return (unsigned int) 2;
  }
}

float kmAABB2DiameterX(const kmAABB2 *aabb)
{
  return aabb->max.x - aabb->min.x;
}

float kmAABB2DiameterY(const kmAABB2 *aabb)
{
  return aabb->max.y - aabb->min.y;
}

kmVec2 *kmAABB2Centre(const kmAABB2 *aabb, kmVec2 *pOut)
{
  kmVec2Add(pOut, &aabb->min, &aabb->max);
  kmVec2Scale(pOut, pOut, 0.5);
  return pOut;
}

kmAABB2 *kmAABB2ExpandToContain(kmAABB2 *pOut, const kmAABB2 *pIn, const kmAABB2 *other)
{
  kmAABB2 result;
  result.min.x = (pIn->min.x < other->min.x) ? (pIn->min.x) : (other->min.x);
  result.max.x = (pIn->max.x > other->max.x) ? (pIn->max.x) : (other->max.x);
  result.min.y = (pIn->min.y < other->min.y) ? (pIn->min.y) : (other->min.y);
  result.max.y = (pIn->max.y > other->max.y) ? (pIn->max.y) : (other->max.y);
  kmAABB2Assign(pOut, &result);
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
struct kmMat3;
#pragma pack(push)
#pragma pack(1)
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2;
#pragma pack(pop)
kmVec2 *kmVec2Fill(kmVec2 *pOut, float x, float y);
float kmVec2Length(const kmVec2 *pIn);
float kmVec2LengthSq(const kmVec2 *pIn);
kmVec2 *kmVec2Normalize(kmVec2 *pOut, const kmVec2 *pIn);
kmVec2 *kmVec2Lerp(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2, float t);
kmVec2 *kmVec2Add(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2);
float kmVec2Dot(const kmVec2 *pV1, const kmVec2 *pV2);
float kmVec2Cross(const kmVec2 *pV1, const kmVec2 *pV2);
kmVec2 *kmVec2Subtract(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2);
kmVec2 *kmVec2Mul(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2);
kmVec2 *kmVec2Div(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2);
kmVec2 *kmVec2Transform(kmVec2 *pOut, const kmVec2 *pV1, const struct kmMat3 *pM);
kmVec2 *kmVec2TransformCoord(kmVec2 *pOut, const kmVec2 *pV, const struct kmMat3 *pM);
kmVec2 *kmVec2Scale(kmVec2 *pOut, const kmVec2 *pIn, const float s);
int kmVec2AreEqual(const kmVec2 *p1, const kmVec2 *p2);
kmVec2 *kmVec2Assign(kmVec2 *pOut, const kmVec2 *pIn);
kmVec2 *kmVec2RotateBy(kmVec2 *pOut, const kmVec2 *pIn, const float degrees, const kmVec2 *center);
float kmVec2DegreesBetween(const kmVec2 *v1, const kmVec2 *v2);
float kmVec2DistanceBetween(const kmVec2 *v1, const kmVec2 *v2);
kmVec2 *kmVec2MidPointBetween(kmVec2 *pOut, const kmVec2 *v1, const kmVec2 *v2);
kmVec2 *kmVec2Reflect(kmVec2 *pOut, const kmVec2 *pIn, const kmVec2 *normal);
extern const kmVec2 KM_VEC2_POS_Y;
extern const kmVec2 KM_VEC2_NEG_Y;
extern const kmVec2 KM_VEC2_NEG_X;
extern const kmVec2 KM_VEC2_POS_X;
extern const kmVec2 KM_VEC2_ZERO;
typedef struct kmAABB2
{
  kmVec2 min;
  kmVec2 max;
} kmAABB2;
kmAABB2 *kmAABB2Initialize(kmAABB2 *pBox, const kmVec2 *centre, const float width, const float height, const float depth);
kmAABB2 *kmAABB2Sanitize(kmAABB2 *pOut, const kmAABB2 *pIn);
int kmAABB2ContainsPoint(const kmAABB2 *pBox, const kmVec2 *pPoint);
kmAABB2 *kmAABB2Assign(kmAABB2 *pOut, const kmAABB2 *pIn);
kmAABB2 *kmAABB2Translate(kmAABB2 *pOut, const kmAABB2 *pIn, const kmVec2 *translation);
kmAABB2 *kmAABB2Scale(kmAABB2 *pOut, const kmAABB2 *pIn, float s);
kmAABB2 *kmAABB2ScaleWithPivot(kmAABB2 *pOut, const kmAABB2 *pIn, const kmVec2 *pivot, float s);
unsigned int kmAABB2ContainsAABB(const kmAABB2 *container, const kmAABB2 *to_check);
float kmAABB2DiameterX(const kmAABB2 *aabb);
float kmAABB2DiameterY(const kmAABB2 *aabb);
kmVec2 *kmAABB2Centre(const kmAABB2 *aabb, kmVec2 *pOut);
kmAABB2 *kmAABB2ExpandToContain(kmAABB2 *pOut, const kmAABB2 *pIn, const kmAABB2 *other);
kmAABB2 *kmAABB2Initialize(kmAABB2 *pBox, const kmVec2 *centre, const float width, const float height, const float depth)
{
  if (!pBox)
  {
    return 0;
  }
  kmVec2 origin;
  kmVec2 *point = (centre) ? ((kmVec2 *) centre) : (&origin);
  kmVec2Fill(&origin, .0f, .0f);
  pBox->min.x = point->x - (width / 2);
  pBox->min.y = point->y - (height / 2);
  pBox->max.x = point->x + (width / 2);
  pBox->max.y = point->y + (height / 2);
  return pBox;
}

kmAABB2 *kmAABB2Sanitize(kmAABB2 *pOut, const kmAABB2 *pIn)
{
  if (pIn->min.x <= pIn->max.x)
  {
    pOut->min.x = pIn->min.x;
    pOut->max.x = pIn->max.x;
  }
  else
  {
    pOut->min.x = pIn->max.x;
    pOut->max.x = pIn->min.x;
  }
  if (pIn->min.y <= pIn->max.y)
  {
    pOut->min.y = pIn->min.y;
    pOut->max.y = pIn->max.y;
  }
  else
  {
    pOut->min.y = pIn->max.y;
    pOut->max.y = pIn->min.y;
  }
  return pOut;
}

int kmAABB2ContainsPoint(const kmAABB2 *pBox, const kmVec2 *pPoint)
{
  if ((((pPoint->x >= pBox->min.x) && (pPoint->x <= pBox->max.x)) && (pPoint->y >= pBox->min.y)) && (pPoint->y <= pBox->max.y))
  {
    return 1;
  }
  return 0;
}

kmAABB2 *kmAABB2Assign(kmAABB2 *pOut, const kmAABB2 *pIn)
{
  kmVec2Assign(&pOut->min, &pIn->min);
  kmVec2Assign(&pOut->max, &pIn->max);
  return pOut;
}

kmAABB2 *kmAABB2Translate(kmAABB2 *pOut, const kmAABB2 *pIn, const kmVec2 *translation)
{
  kmVec2Add(&pOut->min, &pIn->min, translation);
  kmVec2Add(&pOut->max, &pIn->max, translation);
  return pOut;
}

kmAABB2 *kmAABB2Scale(kmAABB2 *pOut, const kmAABB2 *pIn, float s)
{
  kmVec2Scale(&pOut->max, &pIn->max, s);
  kmVec2Scale(&pOut->min, &pIn->min, s);
  return pOut;
}

kmAABB2 *kmAABB2ScaleWithPivot(kmAABB2 *pOut, const kmAABB2 *pIn, const kmVec2 *pivot, float s)
{
  kmVec2 translate;
  translate.x = -pivot->x;
  translate.y = -pivot->y;
  kmAABB2Translate(pOut, pIn, &translate);
  kmAABB2Scale(pOut, pIn, s);
  kmAABB2Translate(pOut, pIn, pivot);
  return pOut;
}

unsigned int kmAABB2ContainsAABB(const kmAABB2 *container, const kmAABB2 *to_check)
{
  kmVec2 corners[4];
  kmVec2Fill(&corners[0], to_check->min.x, to_check->min.y);
  kmVec2Fill(&corners[1], to_check->max.x, to_check->min.y);
  kmVec2Fill(&corners[2], to_check->max.x, to_check->max.y);
  kmVec2Fill(&corners[3], to_check->min.x, to_check->max.y);
  int nContains = ((kmAABB2ContainsPoint(container, &corners[0]) + kmAABB2ContainsPoint(container, &corners[1])) + kmAABB2ContainsPoint(container, &corners[2])) + kmAABB2ContainsPoint(container, &corners[3]);
  if (nContains == 0)
  {
    return (unsigned int) 0;
  }
  else
    if (nContains < 4)
  {
    return (unsigned int) 1;
  }
  else
  {
    return (unsigned int) 2;
  }
}

float kmAABB2DiameterX(const kmAABB2 *aabb)
{
  return aabb->max.x - aabb->min.x;
}

float kmAABB2DiameterY(const kmAABB2 *aabb)
{
  return aabb->max.y - aabb->min.y;
}

kmVec2 *kmAABB2Centre(const kmAABB2 *aabb, kmVec2 *pOut)
{
  kmVec2Add(pOut, &aabb->min, &aabb->max);
  kmVec2Scale(pOut, pOut, 0.5);
  return pOut;
}

kmAABB2 *kmAABB2ExpandToContain(kmAABB2 *pOut, const kmAABB2 *pIn, const kmAABB2 *other)
{
  kmAABB2 result;
  result.min.x = (pIn->min.x < other->min.x) ? (pIn->min.x) : (other->min.x);
  result.max.x = (pIn->max.x > other->max.x) ? (pIn->max.x) : (other->max.x);
  result.min.y = (pIn->min.y < other->min.y) ? (pIn->min.y) : (other->min.y);
  result.max.y = (pIn->max.y > other->max.y) ? (pIn->max.y) : (other->max.y);
  kmAABB2Assign(pOut, &result);
  return pOut;
}

