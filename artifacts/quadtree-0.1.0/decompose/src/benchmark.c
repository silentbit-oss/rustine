static void bench(void (*bm)(), char *label)
{
  printf(" %18s", label);
  fflush(stdout);
  bm();
}


/*** DEPENDENCIES:
***/


static void start()
{
  startTime = clock();
}


/*** DEPENDENCIES:
static clock_t startTime
----------------------------
***/


static void stop()
{
  float duration = ((float) (clock() - startTime)) / CLOCKS_PER_SEC;
  printf(": \e[32m%.4f\e[0ms\n", duration);
}


/*** DEPENDENCIES:
static clock_t startTime
----------------------------
***/


static void mark_insert()
{
  int n = nodes;
  int val = 10;
  quadtree_t *tree = quadtree_new(0, 0, 1000, 1000);
  double x;
  double y;
  start();
  while (n--)
  {
    x = (double) (rand() % 1000);
    y = (double) (rand() % 1000);
    quadtree_insert(tree, x, y, &val);
  }

  stop();
  printf("  %18s %i\n", "length:", tree->length);
  quadtree_free(tree);
}


/*** DEPENDENCIES:
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
static void start()
{
  startTime = clock();
}


----------------------------
static void stop()
{
  float duration = ((float) (clock() - startTime)) / CLOCKS_PER_SEC;
  printf(": \e[32m%.4f\e[0ms\n", duration);
}


----------------------------
static int nodes = 10000
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
  srand(time(0));
  bench(mark_insert, "insertion");
  return 0;
}


/*** DEPENDENCIES:
static void mark_insert()
{
  int n = nodes;
  int val = 10;
  quadtree_t *tree = quadtree_new(0, 0, 1000, 1000);
  double x;
  double y;
  start();
  while (n--)
  {
    x = (double) (rand() % 1000);
    y = (double) (rand() % 1000);
    quadtree_insert(tree, x, y, &val);
  }

  stop();
  printf("  %18s %i\n", "length:", tree->length);
  quadtree_free(tree);
}


----------------------------
static void bench(void (*bm)(), char *label)
{
  printf(" %18s", label);
  fflush(stdout);
  bm();
}


----------------------------
pub time: Time
----------------------------
***/


