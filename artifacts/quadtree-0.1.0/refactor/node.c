#include <math.h>
#include <node.c>
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
int quadtree_node_ispointer(quadtree_node_t *node)
{
  return ((((node->nw != 0) && (node->ne != 0)) && (node->sw != 0)) && (node->se != 0)) && (!quadtree_node_isleaf(node));
}

int quadtree_node_isempty(quadtree_node_t *node)
{
  return ((((node->nw == 0) && (node->ne == 0)) && (node->sw == 0)) && (node->se == 0)) && (!quadtree_node_isleaf(node));
}

int quadtree_node_isleaf(quadtree_node_t *node)
{
  return node->point != 0;
}

void quadtree_node_reset(quadtree_node_t *node, void (*key_free)(void *))
{
  quadtree_point_free(node->point);
  (*key_free)(node->key);
}

quadtree_node_t *quadtree_node_new()
{
  quadtree_node_t *node;
  unsigned int node_idx = 0;
  if (!(node_idx = malloc(sizeof(*node_idx))))
  {
    return 0;
  }
  node->ne = 0;
  node->nw = 0;
  node->se = 0;
  node->sw = 0;
  node->point = 0;
  node->bounds = 0;
  node->key = 0;
  return node;
}

quadtree_node_t *quadtree_node_with_bounds(double minx, double miny, double maxx, double maxy)
{
  quadtree_node_t *node;
  unsigned int node_idx = 0;
  if (!(node_idx = quadtree_node_new()))
  {
    return 0;
  }
  if (!(node->bounds = quadtree_bounds_new()))
  {
    return 0;
  }
  quadtree_bounds_extend(node->bounds, maxx, maxy);
  quadtree_bounds_extend(node->bounds, minx, miny);
  return node;
}

void quadtree_node_free(quadtree_node_t *node, void (*key_free)(void *))
{
  if (node->nw != 0)
  {
    quadtree_node_free(node->nw, key_free);
  }
  if (node->ne != 0)
  {
    quadtree_node_free(node->ne, key_free);
  }
  if (node->sw != 0)
  {
    quadtree_node_free(node->sw, key_free);
  }
  if (node->se != 0)
  {
    quadtree_node_free(node->se, key_free);
  }
  quadtree_bounds_free(node->bounds);
  quadtree_node_reset(node, key_free);
  free(node);
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
int quadtree_node_ispointer(quadtree_node_t *node)
{
  return ((((node->nw != 0) && (node->ne != 0)) && (node->sw != 0)) && (node->se != 0)) && (!quadtree_node_isleaf(node));
}

int quadtree_node_isempty(quadtree_node_t *node)
{
  return ((((node->nw == 0) && (node->ne == 0)) && (node->sw == 0)) && (node->se == 0)) && (!quadtree_node_isleaf(node));
}

int quadtree_node_isleaf(quadtree_node_t *node)
{
  return node->point != 0;
}

void quadtree_node_reset(quadtree_node_t *node, void (*key_free)(void *))
{
  quadtree_point_free(node->point);
  (*key_free)(node->key);
}

quadtree_node_t *quadtree_node_new()
{
  quadtree_node_t *node;
  unsigned int node_idx = 0;
  if (!(node_idx = malloc(sizeof(*node_idx))))
  {
    return 0;
  }
  node->ne = 0;
  node->nw = 0;
  node->se = 0;
  node->sw = 0;
  node->point = 0;
  node->bounds = 0;
  node->key = 0;
  return node;
}

quadtree_node_t *quadtree_node_with_bounds(double minx, double miny, double maxx, double maxy)
{
  quadtree_node_t *node;
  unsigned int node_idx = 0;
  if (!(node_idx = quadtree_node_new()))
  {
    return 0;
  }
  if (!(node->bounds = quadtree_bounds_new()))
  {
    return 0;
  }
  quadtree_bounds_extend(node->bounds, maxx, maxy);
  quadtree_bounds_extend(node->bounds, minx, miny);
  return node;
}

void quadtree_node_free(quadtree_node_t *node, void (*key_free)(void *))
{
  if (node->nw != 0)
  {
    quadtree_node_free(node->nw, key_free);
  }
  if (node->ne != 0)
  {
    quadtree_node_free(node->ne, key_free);
  }
  if (node->sw != 0)
  {
    quadtree_node_free(node->sw, key_free);
  }
  if (node->se != 0)
  {
    quadtree_node_free(node->se, key_free);
  }
  quadtree_bounds_free(node->bounds);
  quadtree_node_reset(node, key_free);
  free(node);
}

