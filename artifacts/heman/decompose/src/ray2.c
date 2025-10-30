void kmRay2Fill(kmRay2 *ray, float px, float py, float vx, float vy)
{
  ray->start.x = px;
  ray->start.y = py;
  ray->dir.x = vx;
  ray->dir.y = vy;
}


/*** DEPENDENCIES:
typedef struct kmRay2
{
  kmVec2 start;
  kmVec2 dir;
} kmRay2
----------------------------
***/


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


/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
***/


void kmRay2FillWithEndpoints(kmRay2 *ray, const kmVec2 *start, const kmVec2 *end)
{
  ray->start.x = start->x;
  ray->start.y = start->y;
  ray->dir.x = end->x - start->x;
  ray->dir.y = end->y - start->y;
}


/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
typedef struct kmRay2
{
  kmVec2 start;
  kmVec2 dir;
} kmRay2
----------------------------
***/


unsigned char kmRay2IntersectCircle(const kmRay2 *ray, const kmVec2 centre, const float radius, kmVec2 *intersection)
{
  assert(0 && "Not implemented");
  return 1;
}


/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
typedef struct kmRay2
{
  kmVec2 start;
  kmVec2 dir;
} kmRay2
----------------------------
***/


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


/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
typedef struct kmRay2
{
  kmVec2 start;
  kmVec2 dir;
} kmRay2
----------------------------
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


----------------------------
***/


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


/*** DEPENDENCIES:
float kmVec2Dot(const kmVec2 *pV1, const kmVec2 *pV2)
{
  return (pV1->x * pV2->x) + (pV1->y * pV2->y);
}


----------------------------
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
kmVec2 *kmVec2Subtract(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2)
{
  pOut->x = pV1->x - pV2->x;
  pOut->y = pV1->y - pV2->y;
  return pOut;
}


----------------------------
kmVec2 *kmVec2Normalize(kmVec2 *pOut, const kmVec2 *pIn)
{
  if ((!pIn->x) && (!pIn->y))
  {
    return kmVec2Assign(pOut, pIn);
  }
  float l = 1.0f / kmVec2Length(pIn);
  kmVec2 v;
  v.x = pIn->x * l;
  v.y = pIn->y * l;
  pOut->x = v.x;
  pOut->y = v.y;
  return pOut;
}


----------------------------
***/


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


/*** DEPENDENCIES:
void kmRay2FillWithEndpoints(kmRay2 *ray, const kmVec2 *start, const kmVec2 *end)
{
  ray->start.x = start->x;
  ray->start.y = start->y;
  ray->dir.x = end->x - start->x;
  ray->dir.y = end->y - start->y;
}


----------------------------
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
typedef struct kmRay2
{
  kmVec2 start;
  kmVec2 dir;
} kmRay2
----------------------------
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


----------------------------
***/


// hint:  ['intersected_ref is a mutable refrence to unsigned char', 'distance_ref is a mutable refrence to float']
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


/*** DEPENDENCIES:
kmVec2 *kmVec2Subtract(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2)
{
  pOut->x = pV1->x - pV2->x;
  pOut->y = pV1->y - pV2->y;
  return pOut;
}


----------------------------
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


----------------------------
typedef struct kmRay2
{
  kmVec2 start;
  kmVec2 dir;
} kmRay2
----------------------------
kmVec2 *kmVec2Assign(kmVec2 *pOut, const kmVec2 *pIn)
{
  if (pOut == pIn)
  {
    return pOut;
  }
  pOut->x = pIn->x;
  pOut->y = pIn->y;
  return pOut;
}


----------------------------
float kmVec2Dot(const kmVec2 *pV1, const kmVec2 *pV2)
{
  return (pV1->x * pV2->x) + (pV1->y * pV2->y);
}


----------------------------
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
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


----------------------------
float kmVec2Length(const kmVec2 *pIn)
{
  return sqrtf(kmSQR(pIn->x) + kmSQR(pIn->y));
}


----------------------------
***/


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


/*** DEPENDENCIES:
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


----------------------------
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
typedef struct kmRay2
{
  kmVec2 start;
  kmVec2 dir;
} kmRay2
----------------------------
***/


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


/*** DEPENDENCIES:
kmVec2 *kmVec2Subtract(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2)
{
  pOut->x = pV1->x - pV2->x;
  pOut->y = pV1->y - pV2->y;
  return pOut;
}


----------------------------
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


----------------------------
typedef struct kmRay2
{
  kmVec2 start;
  kmVec2 dir;
} kmRay2
----------------------------
kmVec2 *kmVec2Assign(kmVec2 *pOut, const kmVec2 *pIn)
{
  if (pOut == pIn)
  {
    return pOut;
  }
  pOut->x = pIn->x;
  pOut->y = pIn->y;
  return pOut;
}


----------------------------
float kmVec2Dot(const kmVec2 *pV1, const kmVec2 *pV2)
{
  return (pV1->x * pV2->x) + (pV1->y * pV2->y);
}


----------------------------
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
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


----------------------------
float kmVec2Length(const kmVec2 *pIn)
{
  return sqrtf(kmSQR(pIn->x) + kmSQR(pIn->y));
}


----------------------------
***/


