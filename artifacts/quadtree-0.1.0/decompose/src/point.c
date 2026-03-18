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


/*** DEPENDENCIES:
typedef struct quadtree_point
{
  double x;
  double y;
} quadtree_point_t
----------------------------
***/


void quadtree_point_free(quadtree_point_t *point)
{
  free(point);
}


/*** DEPENDENCIES:
typedef struct quadtree_point
{
  double x;
  double y;
} quadtree_point_t
----------------------------
***/


