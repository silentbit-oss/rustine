#include <assert.h>
#include <math.h>
#include <ray2.c>
#include <ray2.h>
#include <stdio.h>
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
typedef struct kmRay2
{
  kmVec2 start;
  kmVec2 dir;
} kmRay2;
void kmRay2Fill(kmRay2 *ray, float px, float py, float vx, float vy);
void kmRay2FillWithEndpoints(kmRay2 *ray, const kmVec2 *start, const kmVec2 *end);
unsigned char kmLine2WithLineIntersection(const kmVec2 *ptA, const kmVec2 *vecA, const kmVec2 *ptB, const kmVec2 *vecB, float *outTA, float *outTB, kmVec2 *outIntersection);
unsigned char kmSegment2WithSegmentIntersection(const kmRay2 *segmentA, const kmRay2 *segmentB, kmVec2 *intersection);
unsigned char kmRay2IntersectLineSegment(const kmRay2 *ray, const kmVec2 *p1, const kmVec2 *p2, kmVec2 *intersection);
unsigned char kmRay2IntersectTriangle(const kmRay2 *ray, const kmVec2 *p1, const kmVec2 *p2, const kmVec2 *p3, kmVec2 *intersection, kmVec2 *normal_out, float *distance);
unsigned char kmRay2IntersectBox(const kmRay2 *ray, const kmVec2 *p1, const kmVec2 *p2, const kmVec2 *p3, const kmVec2 *p4, kmVec2 *intersection, kmVec2 *normal_out);
unsigned char kmRay2IntersectCircle(const kmRay2 *ray, const kmVec2 centre, const float radius, kmVec2 *intersection);
void kmRay2Fill(kmRay2 *ray, float px, float py, float vx, float vy)
{
  ray->start.x = px;
  ray->start.y = py;
  ray->dir.x = vx;
  ray->dir.y = vy;
}

void kmRay2FillWithEndpoints(kmRay2 *ray, const kmVec2 *start, const kmVec2 *end)
{
  ray->start.x = start->x;
  ray->start.y = start->y;
  ray->dir.x = end->x - start->x;
  ray->dir.y = end->y - start->y;
}

unsigned char kmLine2WithLineIntersection(const kmVec2 *ptA, const kmVec2 *vecA, const kmVec2 *ptB, const kmVec2 *vecB, float *outTA, float *outTB, kmVec2 *outIntersection)
{
  float x1 = ptA->x;
  float y1 = ptA->y;
  float x2 = x1 + vecA->x;
  float y2 = y1 + vecA->y;
  float x3 = ptB->x;
  float y3 = ptB->y;
  float x4 = x3 + vecB->x;
  float y4 = y3 + vecB->y;
  float denom = ((y4 - y3) * (x2 - x1)) - ((x4 - x3) * (y2 - y1));
  if ((denom > (-0.0001)) && (denom < 0.0001))
  {
    return 0;
  }
  float ua = (((x4 - x3) * (y1 - y3)) - ((y4 - y3) * (x1 - x3))) / denom;
  float ub = (((x2 - x1) * (y1 - y3)) - ((y2 - y1) * (x1 - x3))) / denom;
  float x = x1 + (ua * (x2 - x1));
  float y = y1 + (ua * (y2 - y1));
  if (outTA)
  {
    *outTA = ua;
  }
  if (outTB)
  {
    *outTB = ub;
  }
  if (outIntersection)
  {
    outIntersection->x = x;
    outIntersection->y = y;
  }
  return 1;
}

unsigned char kmSegment2WithSegmentIntersection(const kmRay2 *segmentA, const kmRay2 *segmentB, kmVec2 *intersection)
{
  float ua;
  float ub;
  kmVec2 pt;
  if ((((kmLine2WithLineIntersection(&segmentA->start, &segmentA->dir, &segmentB->start, &segmentB->start, &ua, &ub, &pt) && (0.0 <= ua)) && (ua <= 1.0)) && (0.0 <= ub)) && (ub <= 1.0))
  {
    intersection->x = pt.x;
    intersection->y = pt.y;
    return 1;
  }
  return 0;
}

unsigned char kmRay2IntersectLineSegment(const kmRay2 *ray, const kmVec2 *p1, const kmVec2 *p2, kmVec2 *intersection)
{
  float ua;
  float ub;
  kmVec2 pt;
  kmRay2 otherSegment;
  kmRay2FillWithEndpoints(&otherSegment, p1, p2);
  if (((kmLine2WithLineIntersection(&ray->start, &ray->dir, &otherSegment.start, &otherSegment.dir, &ua, &ub, &pt) && (0.0 <= ua)) && (0.0 <= ub)) && (ub <= 1.0))
  {
    intersection->x = pt.x;
    intersection->y = pt.y;
    return 1;
  }
  return 0;
}

void calculate_line_normal(kmVec2 p1, kmVec2 p2, kmVec2 other_point, kmVec2 *normal_out)
{
  kmVec2 edge;
  kmVec2 other_edge;
  kmVec2Subtract(&edge, &p2, &p1);
  kmVec2Subtract(&other_edge, &other_point, &p1);
  kmVec2Normalize(&edge, &edge);
  kmVec2Normalize(&other_edge, &other_edge);
  kmVec2 n;
  n.x = edge.y;
  n.y = -edge.x;
  float d = kmVec2Dot(&n, &other_edge);
  if (d > 0.0f)
  {
    n.x = -n.x;
    n.y = -n.y;
  }
  normal_out->x = n.x;
  normal_out->y = n.y;
  kmVec2Normalize(normal_out, normal_out);
}

unsigned char kmRay2IntersectTriangle(const kmRay2 *ray, const kmVec2 *p1, const kmVec2 *p2, const kmVec2 *p3, kmVec2 *intersection, kmVec2 *normal_out, float *distance_out)
{
  kmVec2 intersect;
  kmVec2 final_intersect;
  kmVec2 normal;
  float distance = 10000.0f;
  unsigned char intersected = 0;
  if (kmRay2IntersectLineSegment(ray, p1, p2, &intersect))
  {
    kmVec2 tmp;
    float this_distance = kmVec2Length(kmVec2Subtract(&tmp, &intersect, &ray->start));
    kmVec2 this_normal;
    calculate_line_normal(*p1, *p2, *p3, &this_normal);
    if ((this_distance < distance) && (kmVec2Dot(&this_normal, &ray->dir) < 0.0f))
    {
      final_intersect.x = intersect.x;
      final_intersect.y = intersect.y;
      distance = this_distance;
      kmVec2Assign(&normal, &this_normal);
      intersected = 1;
    }
  }
  if (kmRay2IntersectLineSegment(ray, p2, p3, &intersect))
  {
    kmVec2 tmp;
    float this_distance = kmVec2Length(kmVec2Subtract(&tmp, &intersect, &ray->start));
    kmVec2 this_normal;
    calculate_line_normal(*p2, *p3, *p1, &this_normal);
    if ((this_distance < distance) && (kmVec2Dot(&this_normal, &ray->dir) < 0.0f))
    {
      final_intersect.x = intersect.x;
      final_intersect.y = intersect.y;
      distance = this_distance;
      kmVec2Assign(&normal, &this_normal);
      intersected = 1;
    }
  }
  if (kmRay2IntersectLineSegment(ray, p3, p1, &intersect))
  {
    kmVec2 tmp;
    float this_distance = kmVec2Length(kmVec2Subtract(&tmp, &intersect, &ray->start));
    kmVec2 this_normal;
    calculate_line_normal(*p3, *p1, *p2, &this_normal);
    if ((this_distance < distance) && (kmVec2Dot(&this_normal, &ray->dir) < 0.0f))
    {
      final_intersect.x = intersect.x;
      final_intersect.y = intersect.y;
      distance = this_distance;
      kmVec2Assign(&normal, &this_normal);
      intersected = 1;
    }
  }
  if (intersected)
  {
    intersection->x = final_intersect.x;
    intersection->y = final_intersect.y;
    if (normal_out)
    {
      normal_out->x = normal.x;
      normal_out->y = normal.y;
    }
    if (distance)
    {
      *distance_out = distance;
    }
  }
  return intersected;
}

unsigned char kmRay2IntersectBox(const kmRay2 *ray, const kmVec2 *p1, const kmVec2 *p2, const kmVec2 *p3, const kmVec2 *p4, kmVec2 *intersection, kmVec2 *normal_out)
{
  unsigned char intersected = 0;
  kmVec2 intersect;
  kmVec2 final_intersect;
  kmVec2 normal;
  float distance = 10000.0f;
  const kmVec2 *points[4];
  points[0] = p1;
  points[1] = p2;
  points[2] = p3;
  points[3] = p4;
  unsigned int i = 0;
  for (; i < 4; i += 1)
  {
    helper_kmRay2IntersectBox_1(&intersected, &distance, ray, intersect, final_intersect, normal, points, i);
  }

  if (intersected)
  {
    intersection->x = final_intersect.x;
    intersection->y = final_intersect.y;
    if (normal_out)
    {
      normal_out->x = normal.x;
      normal_out->y = normal.y;
    }
  }
  return intersected;
}

unsigned char kmRay2IntersectCircle(const kmRay2 *ray, const kmVec2 centre, const float radius, kmVec2 *intersection)
{
  assert(0 && "Not implemented");
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
typedef struct kmRay2
{
  kmVec2 start;
  kmVec2 dir;
} kmRay2;
void kmRay2Fill(kmRay2 *ray, float px, float py, float vx, float vy);
void kmRay2FillWithEndpoints(kmRay2 *ray, const kmVec2 *start, const kmVec2 *end);
unsigned char kmLine2WithLineIntersection(const kmVec2 *ptA, const kmVec2 *vecA, const kmVec2 *ptB, const kmVec2 *vecB, float *outTA, float *outTB, kmVec2 *outIntersection);
unsigned char kmSegment2WithSegmentIntersection(const kmRay2 *segmentA, const kmRay2 *segmentB, kmVec2 *intersection);
unsigned char kmRay2IntersectLineSegment(const kmRay2 *ray, const kmVec2 *p1, const kmVec2 *p2, kmVec2 *intersection);
unsigned char kmRay2IntersectTriangle(const kmRay2 *ray, const kmVec2 *p1, const kmVec2 *p2, const kmVec2 *p3, kmVec2 *intersection, kmVec2 *normal_out, float *distance);
unsigned char kmRay2IntersectBox(const kmRay2 *ray, const kmVec2 *p1, const kmVec2 *p2, const kmVec2 *p3, const kmVec2 *p4, kmVec2 *intersection, kmVec2 *normal_out);
unsigned char kmRay2IntersectCircle(const kmRay2 *ray, const kmVec2 centre, const float radius, kmVec2 *intersection);
void kmRay2Fill(kmRay2 *ray, float px, float py, float vx, float vy)
{
  ray->start.x = px;
  ray->start.y = py;
  ray->dir.x = vx;
  ray->dir.y = vy;
}

void kmRay2FillWithEndpoints(kmRay2 *ray, const kmVec2 *start, const kmVec2 *end)
{
  ray->start.x = start->x;
  ray->start.y = start->y;
  ray->dir.x = end->x - start->x;
  ray->dir.y = end->y - start->y;
}

unsigned char kmLine2WithLineIntersection(const kmVec2 *ptA, const kmVec2 *vecA, const kmVec2 *ptB, const kmVec2 *vecB, float *outTA, float *outTB, kmVec2 *outIntersection)
{
  float x1 = ptA->x;
  float y1 = ptA->y;
  float x2 = x1 + vecA->x;
  float y2 = y1 + vecA->y;
  float x3 = ptB->x;
  float y3 = ptB->y;
  float x4 = x3 + vecB->x;
  float y4 = y3 + vecB->y;
  float denom = ((y4 - y3) * (x2 - x1)) - ((x4 - x3) * (y2 - y1));
  if ((denom > (-0.0001)) && (denom < 0.0001))
  {
    return 0;
  }
  float ua = (((x4 - x3) * (y1 - y3)) - ((y4 - y3) * (x1 - x3))) / denom;
  float ub = (((x2 - x1) * (y1 - y3)) - ((y2 - y1) * (x1 - x3))) / denom;
  float x = x1 + (ua * (x2 - x1));
  float y = y1 + (ua * (y2 - y1));
  if (outTA)
  {
    *outTA = ua;
  }
  if (outTB)
  {
    *outTB = ub;
  }
  if (outIntersection)
  {
    outIntersection->x = x;
    outIntersection->y = y;
  }
  return 1;
}

unsigned char kmSegment2WithSegmentIntersection(const kmRay2 *segmentA, const kmRay2 *segmentB, kmVec2 *intersection)
{
  float ua;
  float ub;
  kmVec2 pt;
  if ((((kmLine2WithLineIntersection(&segmentA->start, &segmentA->dir, &segmentB->start, &segmentB->start, &ua, &ub, &pt) && (0.0 <= ua)) && (ua <= 1.0)) && (0.0 <= ub)) && (ub <= 1.0))
  {
    intersection->x = pt.x;
    intersection->y = pt.y;
    return 1;
  }
  return 0;
}

unsigned char kmRay2IntersectLineSegment(const kmRay2 *ray, const kmVec2 *p1, const kmVec2 *p2, kmVec2 *intersection)
{
  float ua;
  float ub;
  kmVec2 pt;
  kmRay2 otherSegment;
  kmRay2FillWithEndpoints(&otherSegment, p1, p2);
  if (((kmLine2WithLineIntersection(&ray->start, &ray->dir, &otherSegment.start, &otherSegment.dir, &ua, &ub, &pt) && (0.0 <= ua)) && (0.0 <= ub)) && (ub <= 1.0))
  {
    intersection->x = pt.x;
    intersection->y = pt.y;
    return 1;
  }
  return 0;
}

void calculate_line_normal(kmVec2 p1, kmVec2 p2, kmVec2 other_point, kmVec2 *normal_out)
{
  kmVec2 edge;
  kmVec2 other_edge;
  kmVec2Subtract(&edge, &p2, &p1);
  kmVec2Subtract(&other_edge, &other_point, &p1);
  kmVec2Normalize(&edge, &edge);
  kmVec2Normalize(&other_edge, &other_edge);
  kmVec2 n;
  n.x = edge.y;
  n.y = -edge.x;
  float d = kmVec2Dot(&n, &other_edge);
  if (d > 0.0f)
  {
    n.x = -n.x;
    n.y = -n.y;
  }
  normal_out->x = n.x;
  normal_out->y = n.y;
  kmVec2Normalize(normal_out, normal_out);
}

unsigned char kmRay2IntersectTriangle(const kmRay2 *ray, const kmVec2 *p1, const kmVec2 *p2, const kmVec2 *p3, kmVec2 *intersection, kmVec2 *normal_out, float *distance_out)
{
  kmVec2 intersect;
  kmVec2 final_intersect;
  kmVec2 normal;
  float distance = 10000.0f;
  unsigned char intersected = 0;
  if (kmRay2IntersectLineSegment(ray, p1, p2, &intersect))
  {
    kmVec2 tmp;
    float this_distance = kmVec2Length(kmVec2Subtract(&tmp, &intersect, &ray->start));
    kmVec2 this_normal;
    calculate_line_normal(*p1, *p2, *p3, &this_normal);
    if ((this_distance < distance) && (kmVec2Dot(&this_normal, &ray->dir) < 0.0f))
    {
      final_intersect.x = intersect.x;
      final_intersect.y = intersect.y;
      distance = this_distance;
      kmVec2Assign(&normal, &this_normal);
      intersected = 1;
    }
  }
  if (kmRay2IntersectLineSegment(ray, p2, p3, &intersect))
  {
    kmVec2 tmp;
    float this_distance = kmVec2Length(kmVec2Subtract(&tmp, &intersect, &ray->start));
    kmVec2 this_normal;
    calculate_line_normal(*p2, *p3, *p1, &this_normal);
    if ((this_distance < distance) && (kmVec2Dot(&this_normal, &ray->dir) < 0.0f))
    {
      final_intersect.x = intersect.x;
      final_intersect.y = intersect.y;
      distance = this_distance;
      kmVec2Assign(&normal, &this_normal);
      intersected = 1;
    }
  }
  if (kmRay2IntersectLineSegment(ray, p3, p1, &intersect))
  {
    kmVec2 tmp;
    float this_distance = kmVec2Length(kmVec2Subtract(&tmp, &intersect, &ray->start));
    kmVec2 this_normal;
    calculate_line_normal(*p3, *p1, *p2, &this_normal);
    if ((this_distance < distance) && (kmVec2Dot(&this_normal, &ray->dir) < 0.0f))
    {
      final_intersect.x = intersect.x;
      final_intersect.y = intersect.y;
      distance = this_distance;
      kmVec2Assign(&normal, &this_normal);
      intersected = 1;
    }
  }
  if (intersected)
  {
    intersection->x = final_intersect.x;
    intersection->y = final_intersect.y;
    if (normal_out)
    {
      normal_out->x = normal.x;
      normal_out->y = normal.y;
    }
    if (distance)
    {
      *distance_out = distance;
    }
  }
  return intersected;
}

unsigned char kmRay2IntersectBox(const kmRay2 *ray, const kmVec2 *p1, const kmVec2 *p2, const kmVec2 *p3, const kmVec2 *p4, kmVec2 *intersection, kmVec2 *normal_out)
{
  unsigned char intersected = 0;
  kmVec2 intersect;
  kmVec2 final_intersect;
  kmVec2 normal;
  float distance = 10000.0f;
  const kmVec2 *points[4];
  points[0] = p1;
  points[1] = p2;
  points[2] = p3;
  points[3] = p4;
  unsigned int i = 0;
  for (; i < 4; i += 1)
  {
    const kmVec2 *this_point = points[i];
    const kmVec2 *next_point = (i == 3) ? (points[0]) : (points[i + 1]);
    const kmVec2 *other_point = ((i == 3) || (i == 0)) ? (points[1]) : (points[0]);
    if (kmRay2IntersectLineSegment(ray, this_point, next_point, &intersect))
    {
      kmVec2 tmp;
      float this_distance = kmVec2Length(kmVec2Subtract(&tmp, &intersect, &ray->start));
      kmVec2 this_normal;
      calculate_line_normal(*this_point, *next_point, *other_point, &this_normal);
      if ((this_distance < distance) && (kmVec2Dot(&this_normal, &ray->dir) < 0.0f))
      {
        kmVec2Assign(&final_intersect, &intersect);
        distance = this_distance;
        intersected = 1;
        kmVec2Assign(&normal, &this_normal);
      }
    }
  }

  if (intersected)
  {
    intersection->x = final_intersect.x;
    intersection->y = final_intersect.y;
    if (normal_out)
    {
      normal_out->x = normal.x;
      normal_out->y = normal.y;
    }
  }
  return intersected;
}

unsigned char kmRay2IntersectCircle(const kmRay2 *ray, const kmVec2 centre, const float radius, kmVec2 *intersection)
{
  assert(0 && "Not implemented");
  return 1;
}

void helper_kmRay2IntersectBox_1(unsigned char * const intersected_ref, float * const distance_ref, const kmRay2 * const ray, kmVec2 intersect, kmVec2 final_intersect, kmVec2 normal, const kmVec2 *points[4], unsigned int i)
{
  unsigned char intersected = *intersected_ref;
  float distance = *distance_ref;
  const kmVec2 *this_point = points[i];
  const kmVec2 *next_point = (i == 3) ? (points[0]) : (points[i + 1]);
  const kmVec2 *other_point = ((i == 3) || (i == 0)) ? (points[1]) : (points[0]);
  if (kmRay2IntersectLineSegment(ray, this_point, next_point, &intersect))
  {
    kmVec2 tmp;
    float this_distance = kmVec2Length(kmVec2Subtract(&tmp, &intersect, &ray->start));
    kmVec2 this_normal;
    calculate_line_normal(*this_point, *next_point, *other_point, &this_normal);
    if ((this_distance < distance) && (kmVec2Dot(&this_normal, &ray->dir) < 0.0f))
    {
      kmVec2Assign(&final_intersect, &intersect);
      distance = this_distance;
      intersected = 1;
      kmVec2Assign(&normal, &this_normal);
    }
  }
  *intersected_ref = intersected;
  *distance_ref = distance;
}

