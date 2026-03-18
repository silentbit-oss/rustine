static void elision_(void *key)
{
}


/*** DEPENDENCIES:
***/


void quadtree_free(quadtree_t *tree)
{
  if (tree->key_free != 0)
  {
    quadtree_node_free(tree->root, tree->key_free);
  }
  else
  {
    quadtree_node_free(tree->root, elision_);
  }
  free(tree);
}


/*** DEPENDENCIES:
typedef struct quadtree
{
  quadtree_node_t *root;
  void (*key_free)(void *key);
  unsigned int length;
} quadtree_t
----------------------------
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


----------------------------
static void elision_(void *key)
{
}


----------------------------
***/


static int node_contains_(quadtree_node_t *outer, quadtree_point_t *it)
{
  return ((((outer->bounds != 0) && (outer->bounds->nw->x < it->x)) && (outer->bounds->nw->y > it->y)) && (outer->bounds->se->x > it->x)) && (outer->bounds->se->y < it->y);
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
typedef struct quadtree_point
{
  double x;
  double y;
} quadtree_point_t
----------------------------
***/


static void reset_node_(quadtree_t *tree, quadtree_node_t *node)
{
  if (tree->key_free != 0)
  {
    quadtree_node_reset(node, tree->key_free);
  }
  else
  {
    quadtree_node_reset(node, elision_);
  }
}


/*** DEPENDENCIES:
typedef struct quadtree
{
  quadtree_node_t *root;
  void (*key_free)(void *key);
  unsigned int length;
} quadtree_t
----------------------------
static void elision_(void *key)
{
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
void quadtree_node_reset(quadtree_node_t *node, void (*key_free)(void *))
{
  quadtree_point_free(node->point);
  (*key_free)(node->key);
}


----------------------------
***/


static quadtree_node_t *get_quadrant_(quadtree_node_t *root, quadtree_point_t *point)
{
  if (node_contains_(root->nw, point))
  {
    return root->nw;
  }
  if (node_contains_(root->ne, point))
  {
    return root->ne;
  }
  if (node_contains_(root->sw, point))
  {
    return root->sw;
  }
  if (node_contains_(root->se, point))
  {
    return root->se;
  }
  return 0;
}


/*** DEPENDENCIES:
static int node_contains_(quadtree_node_t *outer, quadtree_point_t *it)
{
  return ((((outer->bounds != 0) && (outer->bounds->nw->x < it->x)) && (outer->bounds->nw->y > it->y)) && (outer->bounds->se->x > it->x)) && (outer->bounds->se->y < it->y);
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
typedef struct quadtree_point
{
  double x;
  double y;
} quadtree_point_t
----------------------------
***/


// element in merge of:  insert_,split_node_
static int insert_(quadtree_t *tree, quadtree_node_t *root, quadtree_point_t *point, void *key)
{
  if (quadtree_node_isempty(root))
  {
    root->point = point;
    root->key = key;
    return 1;
  }
  else
    if (quadtree_node_isleaf(root))
  {
    if ((root->point->x == point->x) && (root->point->y == point->y))
    {
      reset_node_(tree, root);
      root->point = point;
      root->key = key;
      return 0;
    }
    else
    {
      if (!split_node_(tree, root))
      {
        return 0;
      }
      return insert_(tree, root, point, key);
    }
    return 1;
  }
  else
    if (quadtree_node_ispointer(root))
  {
    quadtree_node_t *quadrant = get_quadrant_(root, point);
    return (quadrant == 0) ? (0) : (insert_(tree, quadrant, point, key));
  }
  return 0;
}


/*** DEPENDENCIES:
int quadtree_node_isempty(quadtree_node_t *node)
{
  return ((((node->nw == 0) && (node->ne == 0)) && (node->sw == 0)) && (node->se == 0)) && (!quadtree_node_isleaf(node));
}


----------------------------
int quadtree_node_ispointer(quadtree_node_t *node)
{
  return ((((node->nw != 0) && (node->ne != 0)) && (node->sw != 0)) && (node->se != 0)) && (!quadtree_node_isleaf(node));
}


----------------------------
static void reset_node_(quadtree_t *tree, quadtree_node_t *node)
{
  if (tree->key_free != 0)
  {
    quadtree_node_reset(node, tree->key_free);
  }
  else
  {
    quadtree_node_reset(node, elision_);
  }
}


----------------------------
typedef struct quadtree
{
  quadtree_node_t *root;
  void (*key_free)(void *key);
  unsigned int length;
} quadtree_t
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
typedef struct quadtree_point
{
  double x;
  double y;
} quadtree_point_t
----------------------------
int quadtree_node_isleaf(quadtree_node_t *node)
{
  return node->point != 0;
}


----------------------------
static quadtree_node_t *get_quadrant_(quadtree_node_t *root, quadtree_point_t *point)
{
  if (node_contains_(root->nw, point))
  {
    return root->nw;
  }
  if (node_contains_(root->ne, point))
  {
    return root->ne;
  }
  if (node_contains_(root->sw, point))
  {
    return root->sw;
  }
  if (node_contains_(root->se, point))
  {
    return root->se;
  }
  return 0;
}


----------------------------
None
----------------------------
***/


// element in merge of:  insert_,split_node_
static int split_node_(quadtree_t *tree, quadtree_node_t *node)
{
  quadtree_node_t *nw;
  unsigned int nw_idx = 0;
  quadtree_node_t *ne;
  unsigned int ne_idx = 0;
  quadtree_node_t *sw;
  unsigned int sw_idx = 0;
  quadtree_node_t *se;
  unsigned int se_idx = 0;
  double x = node->bounds->nw->x;
  double y = node->bounds->nw->y;
  double hw = node->bounds->width / 2;
  double hh = node->bounds->height / 2;
  if (!(nw_idx = quadtree_node_with_bounds(x, y - hh, x + hw, y)))
  {
    return 0;
  }
  if (!(ne_idx = quadtree_node_with_bounds(x + hw, y - hh, x + (hw * 2), y)))
  {
    return 0;
  }
  if (!(sw_idx = quadtree_node_with_bounds(x, y - (hh * 2), x + hw, y - hh)))
  {
    return 0;
  }
  if (!(se_idx = quadtree_node_with_bounds(x + hw, y - (hh * 2), x + (hw * 2), y - hh)))
  {
    return 0;
  }
  node->nw = &nw[nw_idx];
  node->ne = &ne[ne_idx];
  node->sw = &sw[sw_idx];
  node->se = &se[se_idx];
  quadtree_point_t *old = node->point;
  void *key = node->key;
  node->point = 0;
  node->key = 0;
  return insert_(tree, node, old, key);
}


/*** DEPENDENCIES:
typedef struct quadtree
{
  quadtree_node_t *root;
  void (*key_free)(void *key);
  unsigned int length;
} quadtree_t
----------------------------
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
typedef struct quadtree_point
{
  double x;
  double y;
} quadtree_point_t
----------------------------
None
----------------------------
***/


int quadtree_insert(quadtree_t *tree, double x, double y, void *key)
{
  quadtree_point_t *point;
  unsigned int point_idx = 0;
  if (!(point_idx = quadtree_point_new(x, y)))
  {
    return 0;
  }
  if (!node_contains_(tree->root, point))
  {
    return 0;
  }
  if (!insert_(tree, tree->root, point, key))
  {
    return 0;
  }
  tree->length += 1;
  return 1;
}


/*** DEPENDENCIES:
typedef struct quadtree
{
  quadtree_node_t *root;
  void (*key_free)(void *key);
  unsigned int length;
} quadtree_t
----------------------------
static int node_contains_(quadtree_node_t *outer, quadtree_point_t *it)
{
  return ((((outer->bounds != 0) && (outer->bounds->nw->x < it->x)) && (outer->bounds->nw->y > it->y)) && (outer->bounds->se->x > it->x)) && (outer->bounds->se->y < it->y);
}


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
typedef struct quadtree_point
{
  double x;
  double y;
} quadtree_point_t
----------------------------
None
----------------------------
***/


quadtree_t *quadtree_new(double minx, double miny, double maxx, double maxy)
{
  quadtree_t *tree;
  unsigned int tree_idx = 0;
  if (!(tree_idx = malloc(sizeof(*tree_idx))))
  {
    return 0;
  }
  tree->root = quadtree_node_with_bounds(minx, miny, maxx, maxy);
  if (!tree->root)
  {
    return 0;
  }
  tree->key_free = 0;
  tree->length = 0;
  return tree;
}


/*** DEPENDENCIES:
typedef struct quadtree
{
  quadtree_node_t *root;
  void (*key_free)(void *key);
  unsigned int length;
} quadtree_t
----------------------------
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


----------------------------
***/


static quadtree_point_t *find_(quadtree_node_t *node, double x, double y)
{
  if (quadtree_node_isleaf(node))
  {
    if ((node->point->x == x) && (node->point->y == y))
    {
      return node->point;
    }
  }
  else
  {
    quadtree_point_t test;
    test.x = x;
    test.y = y;
    return find_(get_quadrant_(node, &test), x, y);
  }
  return 0;
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
typedef struct quadtree_point
{
  double x;
  double y;
} quadtree_point_t
----------------------------
int quadtree_node_isleaf(quadtree_node_t *node)
{
  return node->point != 0;
}


----------------------------
static quadtree_node_t *get_quadrant_(quadtree_node_t *root, quadtree_point_t *point)
{
  if (node_contains_(root->nw, point))
  {
    return root->nw;
  }
  if (node_contains_(root->ne, point))
  {
    return root->ne;
  }
  if (node_contains_(root->sw, point))
  {
    return root->sw;
  }
  if (node_contains_(root->se, point))
  {
    return root->se;
  }
  return 0;
}


----------------------------
***/


quadtree_point_t *quadtree_search(quadtree_t *tree, double x, double y)
{
  return find_(tree->root, x, y);
}


/*** DEPENDENCIES:
typedef struct quadtree
{
  quadtree_node_t *root;
  void (*key_free)(void *key);
  unsigned int length;
} quadtree_t
----------------------------
static quadtree_point_t *find_(quadtree_node_t *node, double x, double y)
{
  if (quadtree_node_isleaf(node))
  {
    if ((node->point->x == x) && (node->point->y == y))
    {
      return node->point;
    }
  }
  else
  {
    quadtree_point_t test;
    test.x = x;
    test.y = y;
    return find_(get_quadrant_(node, &test), x, y);
  }
  return 0;
}


----------------------------
***/


void quadtree_walk(quadtree_node_t *root, void (*descent)(quadtree_node_t *node), void (*ascent)(quadtree_node_t *node))
{
  (*descent)(root);
  if (root->nw != 0)
  {
    quadtree_walk(root->nw, descent, ascent);
  }
  if (root->ne != 0)
  {
    quadtree_walk(root->ne, descent, ascent);
  }
  if (root->sw != 0)
  {
    quadtree_walk(root->sw, descent, ascent);
  }
  if (root->se != 0)
  {
    quadtree_walk(root->se, descent, ascent);
  }
  (*ascent)(root);
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


