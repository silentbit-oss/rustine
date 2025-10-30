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


/*** DEPENDENCIES:
typedef struct quadtree_node
{
  struct quadtree_node *ne;
  struct quadtree_node *nw;
  struct quadtree_node *se;
  struct quadtree_node *sw;
  quadtree_bounds_t *bounds;
  quadtree_point_t *point;
  void *key;
} quadtree_node_t
----------------------------
***/


int quadtree_node_isleaf(quadtree_node_t *node)
{
  return node->point != 0;
}


/*** DEPENDENCIES:
typedef struct quadtree_node
{
  struct quadtree_node *ne;
  struct quadtree_node *nw;
  struct quadtree_node *se;
  struct quadtree_node *sw;
  quadtree_bounds_t *bounds;
  quadtree_point_t *point;
  void *key;
} quadtree_node_t
----------------------------
***/


void quadtree_node_reset(quadtree_node_t *node, void (*key_free)(void *))
{
  quadtree_point_free(node->point);
  (*key_free)(node->key);
}


/*** DEPENDENCIES:
void quadtree_point_free(quadtree_point_t *point)
{
  free(point);
}


----------------------------
typedef struct quadtree_node
{
  struct quadtree_node *ne;
  struct quadtree_node *nw;
  struct quadtree_node *se;
  struct quadtree_node *sw;
  quadtree_bounds_t *bounds;
  quadtree_point_t *point;
  void *key;
} quadtree_node_t
----------------------------
***/


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


/*** DEPENDENCIES:
typedef struct quadtree_node
{
  struct quadtree_node *ne;
  struct quadtree_node *nw;
  struct quadtree_node *se;
  struct quadtree_node *sw;
  quadtree_bounds_t *bounds;
  quadtree_point_t *point;
  void *key;
} quadtree_node_t
----------------------------
void quadtree_node_reset(quadtree_node_t *node, void (*key_free)(void *))
{
  quadtree_point_free(node->point);
  (*key_free)(node->key);
}


----------------------------
void quadtree_bounds_free(quadtree_bounds_t *bounds)
{
  quadtree_point_free(bounds->nw);
  quadtree_point_free(bounds->se);
  free(bounds);
}


----------------------------
***/


int quadtree_node_isempty(quadtree_node_t *node)
{
  return ((((node->nw == 0) && (node->ne == 0)) && (node->sw == 0)) && (node->se == 0)) && (!quadtree_node_isleaf(node));
}


/*** DEPENDENCIES:
int quadtree_node_isleaf(quadtree_node_t *node)
{
  return node->point != 0;
}


----------------------------
typedef struct quadtree_node
{
  struct quadtree_node *ne;
  struct quadtree_node *nw;
  struct quadtree_node *se;
  struct quadtree_node *sw;
  quadtree_bounds_t *bounds;
  quadtree_point_t *point;
  void *key;
} quadtree_node_t
----------------------------
***/


int quadtree_node_ispointer(quadtree_node_t *node)
{
  return ((((node->nw != 0) && (node->ne != 0)) && (node->sw != 0)) && (node->se != 0)) && (!quadtree_node_isleaf(node));
}


/*** DEPENDENCIES:
int quadtree_node_isleaf(quadtree_node_t *node)
{
  return node->point != 0;
}


----------------------------
typedef struct quadtree_node
{
  struct quadtree_node *ne;
  struct quadtree_node *nw;
  struct quadtree_node *se;
  struct quadtree_node *sw;
  quadtree_bounds_t *bounds;
  quadtree_point_t *point;
  void *key;
} quadtree_node_t
----------------------------
***/


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


/*** DEPENDENCIES:
typedef struct quadtree_node
{
  struct quadtree_node *ne;
  struct quadtree_node *nw;
  struct quadtree_node *se;
  struct quadtree_node *sw;
  quadtree_bounds_t *bounds;
  quadtree_point_t *point;
  void *key;
} quadtree_node_t
----------------------------
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


----------------------------
void quadtree_bounds_extend(quadtree_bounds_t *bounds, double x, double y)
{
  bounds->nw->x = fmin(x, bounds->nw->x);
  bounds->nw->y = fmax(y, bounds->nw->y);
  bounds->se->x = fmax(x, bounds->se->x);
  bounds->se->y = fmin(y, bounds->se->y);
  bounds->width = fabs(bounds->nw->x - bounds->se->x);
  bounds->height = fabs(bounds->nw->y - bounds->se->y);
}


----------------------------
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


----------------------------
***/


