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


/*** DEPENDENCIES:
typedef struct kmAABB2
{
  kmVec2 min;
  kmVec2 max;
} kmAABB2
----------------------------
***/


float kmAABB2DiameterX(const kmAABB2 *aabb)
{
  return aabb->max.x - aabb->min.x;
}


/*** DEPENDENCIES:
typedef struct kmAABB2
{
  kmVec2 min;
  kmVec2 max;
} kmAABB2
----------------------------
***/


float kmAABB2DiameterY(const kmAABB2 *aabb)
{
  return aabb->max.y - aabb->min.y;
}


/*** DEPENDENCIES:
typedef struct kmAABB2
{
  kmVec2 min;
  kmVec2 max;
} kmAABB2
----------------------------
***/


int kmAABB2ContainsPoint(const kmAABB2 *pBox, const kmVec2 *pPoint)
{
  if ((((pPoint->x >= pBox->min.x) && (pPoint->x <= pBox->max.x)) && (pPoint->y >= pBox->min.y)) && (pPoint->y <= pBox->max.y))
  {
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
typedef struct kmAABB2
{
  kmVec2 min;
  kmVec2 max;
} kmAABB2
----------------------------
***/


kmAABB2 *kmAABB2Assign(kmAABB2 *pOut, const kmAABB2 *pIn)
{
  kmVec2Assign(&pOut->min, &pIn->min);
  kmVec2Assign(&pOut->max, &pIn->max);
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmAABB2
{
  kmVec2 min;
  kmVec2 max;
} kmAABB2
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
***/


kmAABB2 *kmAABB2Scale(kmAABB2 *pOut, const kmAABB2 *pIn, float s)
{
  kmVec2Scale(&pOut->max, &pIn->max, s);
  kmVec2Scale(&pOut->min, &pIn->min, s);
  return pOut;
}


/*** DEPENDENCIES:
kmVec2 *kmVec2Scale(kmVec2 *pOut, const kmVec2 *pIn, const float s)
{
  pOut->x = pIn->x * s;
  pOut->y = pIn->y * s;
  return pOut;
}


----------------------------
typedef struct kmAABB2
{
  kmVec2 min;
  kmVec2 max;
} kmAABB2
----------------------------
***/


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


/*** DEPENDENCIES:
typedef struct kmAABB2
{
  kmVec2 min;
  kmVec2 max;
} kmAABB2
----------------------------
kmAABB2 *kmAABB2Assign(kmAABB2 *pOut, const kmAABB2 *pIn)
{
  kmVec2Assign(&pOut->min, &pIn->min);
  kmVec2Assign(&pOut->max, &pIn->max);
  return pOut;
}


----------------------------
***/


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


/*** DEPENDENCIES:
kmVec2 *kmVec2Fill(kmVec2 *pOut, float x, float y)
{
  pOut->x = x;
  pOut->y = y;
  return pOut;
}


----------------------------
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
typedef struct kmAABB2
{
  kmVec2 min;
  kmVec2 max;
} kmAABB2
----------------------------
***/


kmAABB2 *kmAABB2Translate(kmAABB2 *pOut, const kmAABB2 *pIn, const kmVec2 *translation)
{
  kmVec2Add(&pOut->min, &pIn->min, translation);
  kmVec2Add(&pOut->max, &pIn->max, translation);
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
typedef struct kmAABB2
{
  kmVec2 min;
  kmVec2 max;
} kmAABB2
----------------------------
kmVec2 *kmVec2Add(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2)
{
  pOut->x = pV1->x + pV2->x;
  pOut->y = pV1->y + pV2->y;
  return pOut;
}


----------------------------
***/


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


/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
typedef struct kmAABB2
{
  kmVec2 min;
  kmVec2 max;
} kmAABB2
----------------------------
kmAABB2 *kmAABB2Translate(kmAABB2 *pOut, const kmAABB2 *pIn, const kmVec2 *translation)
{
  kmVec2Add(&pOut->min, &pIn->min, translation);
  kmVec2Add(&pOut->max, &pIn->max, translation);
  return pOut;
}


----------------------------
kmAABB2 *kmAABB2Scale(kmAABB2 *pOut, const kmAABB2 *pIn, float s)
{
  kmVec2Scale(&pOut->max, &pIn->max, s);
  kmVec2Scale(&pOut->min, &pIn->min, s);
  return pOut;
}


----------------------------
***/


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


/*** DEPENDENCIES:
kmVec2 *kmVec2Fill(kmVec2 *pOut, float x, float y)
{
  pOut->x = x;
  pOut->y = y;
  return pOut;
}


----------------------------
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
int kmAABB2ContainsPoint(const kmAABB2 *pBox, const kmVec2 *pPoint)
{
  if ((((pPoint->x >= pBox->min.x) && (pPoint->x <= pBox->max.x)) && (pPoint->y >= pBox->min.y)) && (pPoint->y <= pBox->max.y))
  {
    return 1;
  }
  return 0;
}


----------------------------
typedef struct kmAABB2
{
  kmVec2 min;
  kmVec2 max;
} kmAABB2
----------------------------
***/


kmVec2 *kmAABB2Centre(const kmAABB2 *aabb, kmVec2 *pOut)
{
  kmVec2Add(pOut, &aabb->min, &aabb->max);
  kmVec2Scale(pOut, pOut, 0.5);
  return pOut;
}


/*** DEPENDENCIES:
typedef struct kmVec2
{
  float x;
  float y;
} kmVec2
----------------------------
kmVec2 *kmVec2Scale(kmVec2 *pOut, const kmVec2 *pIn, const float s)
{
  pOut->x = pIn->x * s;
  pOut->y = pIn->y * s;
  return pOut;
}


----------------------------
typedef struct kmAABB2
{
  kmVec2 min;
  kmVec2 max;
} kmAABB2
----------------------------
kmVec2 *kmVec2Add(kmVec2 *pOut, const kmVec2 *pV1, const kmVec2 *pV2)
{
  pOut->x = pV1->x + pV2->x;
  pOut->y = pV1->y + pV2->y;
  return pOut;
}


----------------------------
***/


