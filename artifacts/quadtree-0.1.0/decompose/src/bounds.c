void quadtree_bounds_extend(quadtree_bounds_t *bounds, double x, double y)
{
  bounds->nw->x = fmin(x, bounds->nw->x);
  bounds->nw->y = fmax(y, bounds->nw->y);
  bounds->se->x = fmax(x, bounds->se->x);
  bounds->se->y = fmin(y, bounds->se->y);
  bounds->width = fabs(bounds->nw->x - bounds->se->x);
  bounds->height = fabs(bounds->nw->y - bounds->se->y);
}


/*** DEPENDENCIES:
typedef struct quadtree_bounds
{
  quadtree_point_t *nw;
  quadtree_point_t *se;
  double width;
  double height;
} quadtree_bounds_t
----------------------------
***/


void quadtree_bounds_free(quadtree_bounds_t *bounds)
{
  quadtree_point_free(bounds->nw);
  quadtree_point_free(bounds->se);
  free(bounds);
}


/*** DEPENDENCIES:
typedef struct quadtree_bounds
{
  quadtree_point_t *nw;
  quadtree_point_t *se;
  double width;
  double height;
} quadtree_bounds_t
----------------------------
void quadtree_point_free(quadtree_point_t *point)
{
  free(point);
}


----------------------------
***/


quadtree_bounds_t *quadtree_bounds_new()
{
  quadtree_bounds_t *bounds;
  unsigned int bounds_idx = 0;
  if ((bounds_idx = malloc(sizeof(*bounds_idx))) == 0)
  {
    return 0;
  }
  bounds->nw = quadtree_point_new(INFINITY, -INFINITY);
  bounds->se = quadtree_point_new(-INFINITY, INFINITY);
  bounds->width = 0;
  bounds->height = 0;
  return bounds;
}


/*** DEPENDENCIES:
typedef struct quadtree_bounds
{
  quadtree_point_t *nw;
  quadtree_point_t *se;
  double width;
  double height;
} quadtree_bounds_t
----------------------------
quadtree_point_t *quadtree_point_new(double x, double y)
{
  quadtree_point_t *point;
  unsigned int point_idx = 0;
  if (!(point_idx = malloc(sizeof(*point_idx))))
  {
    return 0;
  }
  point->x = x;
  point->y = y;
  return point;
}


----------------------------
***/


