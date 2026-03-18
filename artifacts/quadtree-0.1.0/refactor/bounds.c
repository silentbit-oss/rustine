#include <bounds.c>
#include <math.h>
#include <quadtree.h>
#include <stdlib.h>

typedef struct quadtree_point
{
  double x;
  double y;
} quadtree_point_t;
typedef struct quadtree_bounds
{
  quadtree_point_t *nw;
  quadtree_point_t *se;
  double width;
  double height;
} quadtree_bounds_t;
typedef struct quadtree_node
{
  struct quadtree_node *ne;
  struct quadtree_node *nw;
  struct quadtree_node *se;
  struct quadtree_node *sw;
  quadtree_bounds_t *bounds;
  quadtree_point_t *point;
  void *key;
} quadtree_node_t;
typedef struct quadtree
{
  quadtree_node_t *root;
  void (*key_free)(void *key);
  unsigned int length;
} quadtree_t;
quadtree_point_t *quadtree_point_new(double x, double y);
void quadtree_point_free(quadtree_point_t *point);
quadtree_bounds_t *quadtree_bounds_new();
void quadtree_bounds_extend(quadtree_bounds_t *bounds, double x, double y);
void quadtree_bounds_free(quadtree_bounds_t *bounds);
quadtree_node_t *quadtree_node_new();
void quadtree_node_free(quadtree_node_t *node, void (*value_free)(void *));
int quadtree_node_ispointer(quadtree_node_t *node);
int quadtree_node_isempty(quadtree_node_t *node);
int quadtree_node_isleaf(quadtree_node_t *node);
void quadtree_node_reset(quadtree_node_t *node, void (*key_free)(void *));
quadtree_node_t *quadtree_node_with_bounds(double minx, double miny, double maxx, double maxy);
quadtree_t *quadtree_new(double minx, double miny, double maxx, double maxy);
void quadtree_free(quadtree_t *tree);
quadtree_point_t *quadtree_search(quadtree_t *tree, double x, double y);
int quadtree_insert(quadtree_t *tree, double x, double y, void *key);
void quadtree_walk(quadtree_node_t *root, void (*descent)(quadtree_node_t *node), void (*ascent)(quadtree_node_t *node));
void quadtree_bounds_extend(quadtree_bounds_t *bounds, double x, double y)
{
  bounds->nw->x = fmin(x, bounds->nw->x);
  bounds->nw->y = fmax(y, bounds->nw->y);
  bounds->se->x = fmax(x, bounds->se->x);
  bounds->se->y = fmin(y, bounds->se->y);
  bounds->width = fabs(bounds->nw->x - bounds->se->x);
  bounds->height = fabs(bounds->nw->y - bounds->se->y);
}

void quadtree_bounds_free(quadtree_bounds_t *bounds)
{
  quadtree_point_free(bounds->nw);
  quadtree_point_free(bounds->se);
  free(bounds);
}

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


typedef struct quadtree_point
{
  double x;
  double y;
} quadtree_point_t;
typedef struct quadtree_bounds
{
  quadtree_point_t *nw;
  quadtree_point_t *se;
  double width;
  double height;
} quadtree_bounds_t;
typedef struct quadtree_node
{
  struct quadtree_node *ne;
  struct quadtree_node *nw;
  struct quadtree_node *se;
  struct quadtree_node *sw;
  quadtree_bounds_t *bounds;
  quadtree_point_t *point;
  void *key;
} quadtree_node_t;
typedef struct quadtree
{
  quadtree_node_t *root;
  void (*key_free)(void *key);
  unsigned int length;
} quadtree_t;
quadtree_point_t *quadtree_point_new(double x, double y);
void quadtree_point_free(quadtree_point_t *point);
quadtree_bounds_t *quadtree_bounds_new();
void quadtree_bounds_extend(quadtree_bounds_t *bounds, double x, double y);
void quadtree_bounds_free(quadtree_bounds_t *bounds);
quadtree_node_t *quadtree_node_new();
void quadtree_node_free(quadtree_node_t *node, void (*value_free)(void *));
int quadtree_node_ispointer(quadtree_node_t *node);
int quadtree_node_isempty(quadtree_node_t *node);
int quadtree_node_isleaf(quadtree_node_t *node);
void quadtree_node_reset(quadtree_node_t *node, void (*key_free)(void *));
quadtree_node_t *quadtree_node_with_bounds(double minx, double miny, double maxx, double maxy);
quadtree_t *quadtree_new(double minx, double miny, double maxx, double maxy);
void quadtree_free(quadtree_t *tree);
quadtree_point_t *quadtree_search(quadtree_t *tree, double x, double y);
int quadtree_insert(quadtree_t *tree, double x, double y, void *key);
void quadtree_walk(quadtree_node_t *root, void (*descent)(quadtree_node_t *node), void (*ascent)(quadtree_node_t *node));
void quadtree_bounds_extend(quadtree_bounds_t *bounds, double x, double y)
{
  bounds->nw->x = fmin(x, bounds->nw->x);
  bounds->nw->y = fmax(y, bounds->nw->y);
  bounds->se->x = fmax(x, bounds->se->x);
  bounds->se->y = fmin(y, bounds->se->y);
  bounds->width = fabs(bounds->nw->x - bounds->se->x);
  bounds->height = fabs(bounds->nw->y - bounds->se->y);
}

void quadtree_bounds_free(quadtree_bounds_t *bounds)
{
  quadtree_point_free(bounds->nw);
  quadtree_point_free(bounds->se);
  free(bounds);
}

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

