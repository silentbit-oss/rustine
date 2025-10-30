void descent(quadtree_node_t *node)
{
  if (node->bounds != 0)
  {
    printf("{ nw.x:%f, nw.y:%f, se.x:%f, se.y:%f }: ", node->bounds->nw->x, node->bounds->nw->y, node->bounds->se->x, node->bounds->se->y);
  }
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


void ascent(quadtree_node_t *node)
{
  printf("\n");
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


static void test_points()
{
  quadtree_point_t *point = quadtree_point_new(5, 6);
  assert(point->x == 5);
  assert(point->y == 6);
  quadtree_point_free(point);
}


/*** DEPENDENCIES:
void quadtree_point_free(quadtree_point_t *point)
{
  free(point);
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
***/


static void test_bounds()
{
  quadtree_bounds_t *bounds = quadtree_bounds_new();
  assert(bounds);
  assert(bounds->nw->x == INFINITY);
  assert(bounds->se->x == (-INFINITY));
  quadtree_bounds_extend(bounds, 5.0, 5.0);
  assert(bounds->nw->x == 5.0);
  assert(bounds->se->x == 5.0);
  quadtree_bounds_extend(bounds, 10.0, 10.0);
  assert(bounds->nw->y == 10.0);
  assert(bounds->nw->y == 10.0);
  assert(bounds->se->y == 5.0);
  assert(bounds->se->y == 5.0);
  assert(bounds->width == 5.0);
  assert(bounds->height == 5.0);
  quadtree_bounds_free(bounds);
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
void quadtree_bounds_free(quadtree_bounds_t *bounds)
{
  quadtree_point_free(bounds->nw);
  quadtree_point_free(bounds->se);
  free(bounds);
}


----------------------------
***/


static void test_node()
{
  quadtree_node_t *node = quadtree_node_new();
  assert(!quadtree_node_isleaf(node));
  assert(quadtree_node_isempty(node));
  assert(!quadtree_node_ispointer(node));
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
int quadtree_node_isleaf(quadtree_node_t *node)
{
  return node->point != 0;
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


static void test_tree()
{
  int val = 10;
  quadtree_t *tree = quadtree_new(1, 1, 10, 10);
  assert(tree->root->bounds->nw->x == 1);
  assert(tree->root->bounds->nw->y == 10.0);
  assert(tree->root->bounds->se->x == 10.0);
  assert(tree->root->bounds->se->y == 1);
  assert(quadtree_insert(tree, 0, 0, &val) == 0);
  assert(quadtree_insert(tree, 10, 10, &val) == 0);
  assert(quadtree_insert(tree, 110.0, 110.0, &val) == 0);
  assert(quadtree_insert(tree, 8.0, 2.0, &val) != 0);
  assert(tree->length == 1);
  assert(tree->root->point->x == 8.0);
  assert(tree->root->point->y == 2.0);
  assert(quadtree_insert(tree, 2.0, 3.0, &val) != 0);
  assert(quadtree_insert(tree, 2.0, 3.0, &val) == 0);
  assert(tree->length == 2);
  assert(tree->root->point == 0);
  assert(quadtree_insert(tree, 3.0, 1.1, &val) == 1);
  assert(tree->length == 3);
  assert(quadtree_search(tree, 3.0, 1.1)->x == 3.0);
  quadtree_walk(tree->root, ascent, descent);
  quadtree_free(tree);
}


/*** DEPENDENCIES:
void ascent(quadtree_node_t *node)
{
  printf("\n");
}


----------------------------
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


----------------------------
quadtree_point_t *quadtree_search(quadtree_t *tree, double x, double y)
{
  return find_(tree->root, x, y);
}


----------------------------
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


----------------------------
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


----------------------------
typedef struct quadtree
{
  quadtree_node_t *root;
  void (*key_free)(void *key);
  unsigned int length;
} quadtree_t
----------------------------
void descent(quadtree_node_t *node)
{
  if (node->bounds != 0)
  {
    printf("{ nw.x:%f, nw.y:%f, se.x:%f, se.y:%f }: ", node->bounds->nw->x, node->bounds->nw->y, node->bounds->se->x, node->bounds->se->y);
  }
}


----------------------------
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


----------------------------
***/


int main(int argc, const char *argv[])
{
  printf("\nquadtree_t: %ld\n", sizeof(quadtree_t));
  printf("quadtree_node_t: %ld\n", sizeof(quadtree_node_t));
  printf("quadtree_bounds_t: %ld\n", sizeof(quadtree_bounds_t));
  printf("quadtree_point_t: %ld\n", sizeof(quadtree_point_t));
  printf("\x1b[33mtree\x1b[0m ");
  test_tree();
  puts("\x1b[1;32m ✓ \x1b[0m");
  ;
  printf("\x1b[33mnode\x1b[0m ");
  test_node();
  puts("\x1b[1;32m ✓ \x1b[0m");
  ;
  printf("\x1b[33mbounds\x1b[0m ");
  test_bounds();
  puts("\x1b[1;32m ✓ \x1b[0m");
  ;
  printf("\x1b[33mpoints\x1b[0m ");
  test_points();
  puts("\x1b[1;32m ✓ \x1b[0m");
  ;
}


/*** DEPENDENCIES:
static void test_bounds()
{
  quadtree_bounds_t *bounds = quadtree_bounds_new();
  assert(bounds);
  assert(bounds->nw->x == INFINITY);
  assert(bounds->se->x == (-INFINITY));
  quadtree_bounds_extend(bounds, 5.0, 5.0);
  assert(bounds->nw->x == 5.0);
  assert(bounds->se->x == 5.0);
  quadtree_bounds_extend(bounds, 10.0, 10.0);
  assert(bounds->nw->y == 10.0);
  assert(bounds->nw->y == 10.0);
  assert(bounds->se->y == 5.0);
  assert(bounds->se->y == 5.0);
  assert(bounds->width == 5.0);
  assert(bounds->height == 5.0);
  quadtree_bounds_free(bounds);
}


----------------------------
static void test_node()
{
  quadtree_node_t *node = quadtree_node_new();
  assert(!quadtree_node_isleaf(node));
  assert(quadtree_node_isempty(node));
  assert(!quadtree_node_ispointer(node));
}


----------------------------
static void test_points()
{
  quadtree_point_t *point = quadtree_point_new(5, 6);
  assert(point->x == 5);
  assert(point->y == 6);
  quadtree_point_free(point);
}


----------------------------
static void test_tree()
{
  int val = 10;
  quadtree_t *tree = quadtree_new(1, 1, 10, 10);
  assert(tree->root->bounds->nw->x == 1);
  assert(tree->root->bounds->nw->y == 10.0);
  assert(tree->root->bounds->se->x == 10.0);
  assert(tree->root->bounds->se->y == 1);
  assert(quadtree_insert(tree, 0, 0, &val) == 0);
  assert(quadtree_insert(tree, 10, 10, &val) == 0);
  assert(quadtree_insert(tree, 110.0, 110.0, &val) == 0);
  assert(quadtree_insert(tree, 8.0, 2.0, &val) != 0);
  assert(tree->length == 1);
  assert(tree->root->point->x == 8.0);
  assert(tree->root->point->y == 2.0);
  assert(quadtree_insert(tree, 2.0, 3.0, &val) != 0);
  assert(quadtree_insert(tree, 2.0, 3.0, &val) == 0);
  assert(tree->length == 2);
  assert(tree->root->point == 0);
  assert(quadtree_insert(tree, 3.0, 1.1, &val) == 1);
  assert(tree->length == 3);
  assert(quadtree_search(tree, 3.0, 1.1)->x == 3.0);
  quadtree_walk(tree->root, ascent, descent);
  quadtree_free(tree);
}


----------------------------
***/


