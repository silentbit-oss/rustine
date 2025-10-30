typedef struct quadtree_bounds
{
  quadtree_point_t *nw;
  quadtree_point_t *se;
  double width;
  double height;
} quadtree_bounds_t
/*** DEPENDENCIES:
typedef struct quadtree_point
{
  double x;
  double y;
} quadtree_point_t
----------------------------
***/


