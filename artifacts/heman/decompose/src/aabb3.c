kmAABB3 *kmAABB3Scale(kmAABB3 *pOut, const kmAABB3 *pIn, float s)
{
  assert(0 && "Not implemented");
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmAABB3
{
  kmVec3 min;
  kmVec3 max;
} kmAABB3
----------------------------
***/


float kmAABB3DiameterX(const kmAABB3 *aabb)
{
  return fabs(aabb->max.x - aabb->min.x);
}


/*** DEPENDENCIES:
typedef struct kmAABB3
{
  kmVec3 min;
  kmVec3 max;
} kmAABB3
----------------------------
***/


float kmAABB3DiameterY(const kmAABB3 *aabb)
{
  return fabs(aabb->max.y - aabb->min.y);
}


/*** DEPENDENCIES:
typedef struct kmAABB3
{
  kmVec3 min;
  kmVec3 max;
} kmAABB3
----------------------------
***/


float kmAABB3DiameterZ(const kmAABB3 *aabb)
{
  return fabs(aabb->max.z - aabb->min.z);
}


/*** DEPENDENCIES:
typedef struct kmAABB3
{
  kmVec3 min;
  kmVec3 max;
} kmAABB3
----------------------------
***/


int kmAABB3ContainsPoint(const kmAABB3 *pBox, const kmVec3 *pPoint)
{
  if ((((((pPoint->x >= pBox->min.x) && (pPoint->x <= pBox->max.x)) && (pPoint->y >= pBox->min.y)) && (pPoint->y <= pBox->max.y)) && (pPoint->z >= pBox->min.z)) && (pPoint->z <= pBox->max.z))
  {
    return 1;
  }
  return 0;
}


/*** DEPENDENCIES:
typedef struct kmAABB3
{
  kmVec3 min;
  kmVec3 max;
} kmAABB3
----------------------------
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
***/


kmAABB3 *kmAABB3Assign(kmAABB3 *pOut, const kmAABB3 *pIn)
{
  kmVec3Assign(&pOut->min, &pIn->min);
  kmVec3Assign(&pOut->max, &pIn->max);
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmAABB3
{
  kmVec3 min;
  kmVec3 max;
} kmAABB3
----------------------------
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


----------------------------
***/


unsigned char kmAABB3IntersectsTriangle(kmAABB3 *box, const kmVec3 *p1, const kmVec3 *p2, const kmVec3 *p3)
{
  assert(0 && "Not implemented");
  return 1;
}


/*** DEPENDENCIES:
typedef struct kmAABB3
{
  kmVec3 min;
  kmVec3 max;
} kmAABB3
----------------------------
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
***/


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


/*** DEPENDENCIES:
int kmAABB3ContainsPoint(const kmAABB3 *pBox, const kmVec3 *pPoint)
{
  if ((((((pPoint->x >= pBox->min.x) && (pPoint->x <= pBox->max.x)) && (pPoint->y >= pBox->min.y)) && (pPoint->y <= pBox->max.y)) && (pPoint->z >= pBox->min.z)) && (pPoint->z <= pBox->max.z))
  {
    return 1;
  }
  return 0;
}


----------------------------
typedef struct kmAABB3
{
  kmVec3 min;
  kmVec3 max;
} kmAABB3
----------------------------
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
kmVec3 *kmVec3Fill(kmVec3 *pOut, float x, float y, float z)
{
  pOut->x = x;
  pOut->y = y;
  pOut->z = z;
  return pOut;
}


----------------------------
***/


unsigned char kmAABB3IntersectsAABB(const kmAABB3 *box, const kmAABB3 *other)
{
  return kmAABB3ContainsAABB(box, other) != ((unsigned int) 0);
}


/*** DEPENDENCIES:
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


----------------------------
typedef struct kmAABB3
{
  kmVec3 min;
  kmVec3 max;
} kmAABB3
----------------------------
***/


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


/*** DEPENDENCIES:
typedef struct kmAABB3
{
  kmVec3 min;
  kmVec3 max;
} kmAABB3
----------------------------
kmAABB3 *kmAABB3Assign(kmAABB3 *pOut, const kmAABB3 *pIn)
{
  kmVec3Assign(&pOut->min, &pIn->min);
  kmVec3Assign(&pOut->max, &pIn->max);
  return pOut;
}


----------------------------
***/


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


/*** DEPENDENCIES:
kmVec3 *kmVec3Zero(kmVec3 *pOut)
{
  pOut->x = 0.0f;
  pOut->y = 0.0f;
  pOut->z = 0.0f;
  return pOut;
}


----------------------------
typedef struct kmAABB3
{
  kmVec3 min;
  kmVec3 max;
} kmAABB3
----------------------------
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
***/


kmVec3 *kmAABB3Centre(const kmAABB3 *aabb, kmVec3 *pOut)
{
  kmVec3Add(pOut, &aabb->min, &aabb->max);
  kmVec3Scale(pOut, pOut, 0.5);
  return pOut;
}


/*** DEPENDENCIES:
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


----------------------------
kmVec3 *kmVec3Scale(kmVec3 *pOut, const kmVec3 *pIn, const float s)
{
  pOut->x = pIn->x * s;
  pOut->y = pIn->y * s;
  pOut->z = pIn->z * s;
  return pOut;
}


----------------------------
typedef struct kmAABB3
{
  kmVec3 min;
  kmVec3 max;
} kmAABB3
----------------------------
typedef struct kmVec3
{
  float x;
  float y;
  float z;
} kmVec3
----------------------------
***/


