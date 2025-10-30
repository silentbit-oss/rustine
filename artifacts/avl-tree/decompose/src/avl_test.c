void swap(char *x, char *y)
{
  char temp;
  temp = *x;
  *x = *y;
  *y = temp;
}


/*** DEPENDENCIES:
***/


void permute(char *a, int start, int end, void func(char *))
{
  if (start == end)
  {
    func(a);
    return;
  }
  int i;
  for (i = start; i <= end; i += 1)
  {
    swap(a + start, a + i);
    permute(a, start + 1, end, func);
    swap(a + start, a + i);
  }

}


/*** DEPENDENCIES:
void swap(char *x, char *y)
{
  char temp;
  temp = *x;
  *x = *y;
  *y = temp;
}


----------------------------
***/


avltree *tree_create()
{
  return avl_create(compare_func, destroy_func);
}


/*** DEPENDENCIES:
void destroy_func(void *d)
{
  mydata *p;
  unsigned int p_idx = 0;
  assert(d != 0);
  p_idx = (mydata *) d;
  free(p);
}


----------------------------
avltree *avl_create(int (*compare_func)(const void *, const void *), void (*destroy_func)(void *))
{
  avltree *avlt;
  unsigned int avlt_idx = 0;
  avlt_idx = (avltree *) malloc(sizeof(avltree));
  if ((&avlt[avlt_idx]) == 0)
  {
    return 0;
  }
  avlt->compare = compare_func;
  avlt->destroy = destroy_func;
  avlt->nil.left = (avlt->nil.right = (avlt->nil.parent = &avlt->nil));
  avlt->nil.bf = 0;
  avlt->nil.data = 0;
  avlt->root.left = (avlt->root.right = (avlt->root.parent = &avlt->nil));
  avlt->root.bf = 0;
  avlt->root.data = 0;
  avlt->min = 0;
  return avlt;
}


----------------------------
int compare_func(const void *d1, const void *d2)
{
  mydata *p1;
  unsigned int p1_idx = 0;
  mydata *p2;
  unsigned int p2_idx = 0;
  assert(d1 != 0);
  assert(d2 != 0);
  p1_idx = (mydata *) d1;
  p2_idx = (mydata *) d2;
  if (p1->key == p2->key)
  {
    return 0;
  }
  else
    if (p1->key > p2->key)
  {
    return 1;
  }
  else
    return -1;
}


----------------------------
***/


avlnode *tree_find(avltree *avlt, int key)
{
  mydata query;
  query.key = key;
  return avl_find(avlt, &query);
}


/*** DEPENDENCIES:
typedef struct 
{
  int (*compare)(const void *, const void *);
  void (*print)(void *);
  void (*destroy)(void *);
  avlnode root;
  avlnode nil;
  avlnode *min;
} avltree
----------------------------
avlnode *avl_find(avltree *avlt, void *data)
{
  avlnode *p;
  unsigned int p_idx = 0;
  p_idx = avlt->root.left;
  while ((&p[p_idx]) != (&avlt->nil))
  {
    int cmp;
    cmp = avlt->compare(data, p->data);
    if (cmp == 0)
    {
      return p;
    }
    p_idx = (cmp < 0) ? (p_idx->left) : (p_idx->right);
  }

  return 0;
}


----------------------------
typedef struct 
{
  int key;
} mydata
----------------------------
***/


void tree_print(avltree *avlt)
{
  avl_print(avlt, print_func);
}


/*** DEPENDENCIES:
typedef struct 
{
  int (*compare)(const void *, const void *);
  void (*print)(void *);
  void (*destroy)(void *);
  avlnode root;
  avlnode nil;
  avlnode *min;
} avltree
----------------------------
void avl_print(avltree *avlt, void (*print_func)(void *))
{
  printf("\n--\n");
  print(avlt, avlt->root.left, print_func, 0, "T");
  printf("\nheight = %d\n", check_height(avlt, avlt->root.left));
}


----------------------------
void print_func(void *d)
{
  mydata *p;
  unsigned int p_idx = 0;
  assert(d != 0);
  p_idx = (mydata *) d;
  printf("%d", p->key);
}


----------------------------
***/


int tree_check(avltree *avlt)
{
  mydata min;
  mydata max;
  int rc;
  min.key = -2147483648;
  max.key = 2147483647;
  rc = 1;
  if (avl_check_order(avlt, &min, &max) != 1)
  {
    fprintf(stdout, "tree_check: invalid order\n");
    rc = 0;
  }
  if (avl_check_height(avlt) != 1)
  {
    fprintf(stdout, "tree_check: invalid height\n");
    rc = 0;
  }
  return rc;
}


/*** DEPENDENCIES:
typedef struct 
{
  int (*compare)(const void *, const void *);
  void (*print)(void *);
  void (*destroy)(void *);
  avlnode root;
  avlnode nil;
  avlnode *min;
} avltree
----------------------------
typedef struct 
{
  int key;
} mydata
----------------------------
int avl_check_order(avltree *avlt, void *min, void *max)
{
  return check_order(avlt, avlt->root.left, min, max);
}


----------------------------
int avl_check_height(avltree *avlt)
{
  int height;
  height = check_height(avlt, avlt->root.left);
  return (height < 0) ? (0) : (1);
}


----------------------------
***/


avlnode *tree_insert(avltree *avlt, int key)
{
  avlnode *node;
  unsigned int node_idx = 0;
  mydata *data;
  unsigned int data_idx = 0;
  if ((key < (-2147483648)) || (key > 2147483647))
  {
    fprintf(stdout, "tree_insert: invalid key %d\n", key);
    return 0;
  }
  if (((data_idx = makedata(key)) == 0) || ((node_idx = avl_insert(avlt, data)) == 0))
  {
    fprintf(stdout, "tree_insert: insert %d failed\n", key);
    free(data);
    return 0;
  }
  return node;
}


/*** DEPENDENCIES:
typedef struct avlnode
{
  struct avlnode *left;
  struct avlnode *right;
  struct avlnode *parent;
  char bf;
  void *data;
} avlnode
----------------------------
mydata *makedata(int key)
{
  mydata *p;
  unsigned int p_idx = 0;
  p_idx = (mydata *) malloc(sizeof(mydata));
  if ((&p[p_idx]) != 0)
  {
    p->key = key;
  }
  return p;
}


----------------------------
typedef struct 
{
  int (*compare)(const void *, const void *);
  void (*print)(void *);
  void (*destroy)(void *);
  avlnode root;
  avlnode nil;
  avlnode *min;
} avltree
----------------------------
typedef struct 
{
  int key;
} mydata
----------------------------
avlnode *avl_insert(avltree *avlt, void *data)
{
  avlnode *current;
  unsigned int current_idx = 0;
  avlnode *parent;
  unsigned int parent_idx = 0;
  avlnode *new_node;
  current_idx = avlt->root.left;
  parent_idx = &avlt->root;
  while ((&current[current_idx]) != (&avlt->nil))
  {
    int cmp;
    cmp = avlt->compare(data, current->data);
    parent_idx = &current[current_idx];
    current_idx = (cmp < 0) ? (current_idx->left) : (current_idx->right);
  }

  current_idx = (new_node = (avlnode *) malloc(sizeof(avlnode)));
  if ((&current[current_idx]) == 0)
  {
    return 0;
  }
  current->left = (current->right = &avlt->nil);
  current->parent = &parent[parent_idx];
  current->bf = 0;
  current->data = data;
  if (((&parent[parent_idx]) == (&avlt->root)) || (avlt->compare(data, parent->data) < 0))
  {
    parent->left = &current[current_idx];
  }
  else
    parent->right = &current[current_idx];
  if ((avlt->min == 0) || (avlt->compare(current->data, avlt->min->data) < 0))
  {
    avlt->min = &current[current_idx];
  }
  while ((&current[current_idx]) != avlt->root.left)
  {
    if ((&current[current_idx]) == parent->left)
    {
      if (parent->bf == 1)
      {
        parent->bf = 0;
        break;
      }
      else
        if (parent->bf == 0)
      {
        parent->bf = -1;
      }
      else
        if (parent->bf == (-1))
      {
        fix_insert_leftimbalance(avlt, parent);
        break;
      }
    }
    else
    {
      if (parent->bf == (-1))
      {
        parent->bf = 0;
        break;
      }
      else
        if (parent->bf == 0)
      {
        parent->bf = 1;
      }
      else
        if (parent->bf == 1)
      {
        fix_insert_rightimbalance(avlt, parent);
        break;
      }
    }
    current_idx = &parent[parent_idx];
    parent_idx = current->parent_idx;
  }

  return new_node;
}


----------------------------
***/


void permutation_insert(char *a)
{
  avltree *avlt;
  unsigned int avlt_idx = 0;
  avlnode *node;
  unsigned int node_idx = 0;
  int i;
  if ((avlt_idx = tree_create()) == 0)
  {
    fprintf(stdout, "create AVL tree failed\n");
    permutation_error += 1;
    return;
  }
  for (i = 0; i < strlen(a); i += 1)
  {
    if ((((node_idx = tree_insert(avlt, a[i])) == 0) || (tree_find(avlt, a[i]) != (&node[node_idx]))) || (tree_check(avlt) != 1))
    {
      fprintf(stdout, "insert %c failed\n", a[i]);
      permutation_error += 1;
      return;
    }
  }

  avl_destroy(avlt);
}


/*** DEPENDENCIES:
int tree_check(avltree *avlt)
{
  mydata min;
  mydata max;
  int rc;
  min.key = -2147483648;
  max.key = 2147483647;
  rc = 1;
  if (avl_check_order(avlt, &min, &max) != 1)
  {
    fprintf(stdout, "tree_check: invalid order\n");
    rc = 0;
  }
  if (avl_check_height(avlt) != 1)
  {
    fprintf(stdout, "tree_check: invalid height\n");
    rc = 0;
  }
  return rc;
}


----------------------------
typedef struct avlnode
{
  struct avlnode *left;
  struct avlnode *right;
  struct avlnode *parent;
  char bf;
  void *data;
} avlnode
----------------------------
int permutation_error = 0
----------------------------
avltree *tree_create()
{
  return avl_create(compare_func, destroy_func);
}


----------------------------
typedef struct 
{
  int (*compare)(const void *, const void *);
  void (*print)(void *);
  void (*destroy)(void *);
  avlnode root;
  avlnode nil;
  avlnode *min;
} avltree
----------------------------
void avl_destroy(avltree *avlt)
{
  destroy(avlt, avlt->root.left);
  free(avlt);
}


----------------------------
avlnode *tree_insert(avltree *avlt, int key)
{
  avlnode *node;
  unsigned int node_idx = 0;
  mydata *data;
  unsigned int data_idx = 0;
  if ((key < (-2147483648)) || (key > 2147483647))
  {
    fprintf(stdout, "tree_insert: invalid key %d\n", key);
    return 0;
  }
  if (((data_idx = makedata(key)) == 0) || ((node_idx = avl_insert(avlt, data)) == 0))
  {
    fprintf(stdout, "tree_insert: insert %d failed\n", key);
    free(data);
    return 0;
  }
  return node;
}


----------------------------
avlnode *tree_find(avltree *avlt, int key)
{
  mydata query;
  query.key = key;
  return avl_find(avlt, &query);
}


----------------------------
***/


int unit_test_permutation_insertion()
{
  char a[] = "ABCDEFGHIJ";
  permutation_error = 0;
  permute(a, 0, strlen(a) - 1, permutation_insert);
  return permutation_error == 0;
}


/*** DEPENDENCIES:
int permutation_error = 0
----------------------------
void permutation_insert(char *a)
{
  avltree *avlt;
  unsigned int avlt_idx = 0;
  avlnode *node;
  unsigned int node_idx = 0;
  int i;
  if ((avlt_idx = tree_create()) == 0)
  {
    fprintf(stdout, "create AVL tree failed\n");
    permutation_error += 1;
    return;
  }
  for (i = 0; i < strlen(a); i += 1)
  {
    if ((((node_idx = tree_insert(avlt, a[i])) == 0) || (tree_find(avlt, a[i]) != (&node[node_idx]))) || (tree_check(avlt) != 1))
    {
      fprintf(stdout, "insert %c failed\n", a[i]);
      permutation_error += 1;
      return;
    }
  }

  avl_destroy(avlt);
}


----------------------------
void permute(char *a, int start, int end, void func(char *))
{
  if (start == end)
  {
    func(a);
    return;
  }
  int i;
  for (i = start; i <= end; i += 1)
  {
    swap(a + start, a + i);
    permute(a, start + 1, end, func);
    swap(a + start, a + i);
  }

}


----------------------------
***/


int tree_delete(avltree *avlt, int key)
{
  avlnode *node;
  unsigned int node_idx = 0;
  if ((node_idx = tree_find(avlt, key)) == 0)
  {
    fprintf(stdout, "tree_delete: %d not found\n", key);
    return 0;
  }
  avl_delete(avlt, node, 0);
  if (tree_find(avlt, key) == (&node[node_idx]))
  {
    fprintf(stdout, "tree_delete: delete %d failed\n", key);
    return 0;
  }
  return 1;
}


/*** DEPENDENCIES:
typedef struct 
{
  int (*compare)(const void *, const void *);
  void (*print)(void *);
  void (*destroy)(void *);
  avlnode root;
  avlnode nil;
  avlnode *min;
} avltree
----------------------------
typedef struct avlnode
{
  struct avlnode *left;
  struct avlnode *right;
  struct avlnode *parent;
  char bf;
  void *data;
} avlnode
----------------------------
void *avl_delete(avltree *avlt, avlnode *node, int keep)
{
  avlnode *current;
  unsigned int current_idx = 0;
  avlnode *parent;
  unsigned int parent_idx = 0;
  avlnode *target;
  unsigned int target_idx = 0;
  void *data;
  unsigned int data_idx = 0;
  data_idx = node->data_idx;
  if ((node->left == (&avlt->nil)) || (node->right == (&avlt->nil)))
  {
    target_idx = node;
    if (avlt->min == (&target[target_idx]))
    {
      avlt->min = avl_successor(avlt, target);
    }
  }
  else
  {
    target_idx = avl_successor(avlt, node);
    node->data = target->data;
  }
  current_idx = &target[target_idx];
  parent_idx = current->parent_idx;
  while ((&current[current_idx]) != avlt->root.left)
  {
    helper_avl_delete_1(&current_idx, &parent_idx, avlt, current, parent);
  }

  avlnode *child;
  unsigned int child_idx = 0;
  child_idx = (target->left == (&avlt->nil)) ? (target->right) : (target->left);
  if ((&child[child_idx]) != (&avlt->nil))
  {
    child->parent = target->parent;
  }
  if ((&target[target_idx]) == target->parent->left)
  {
    target->parent->left = &child[child_idx];
  }
  else
    target->parent->right = &child[child_idx];
  free(target);
  if (keep == 0)
  {
    avlt->destroy(data);
    data_idx = 0;
  }
  return data;
}


----------------------------
avlnode *tree_find(avltree *avlt, int key)
{
  mydata query;
  query.key = key;
  return avl_find(avlt, &query);
}


----------------------------
***/


void permutation_delete(char *a)
{
  avltree *avlt;
  unsigned int avlt_idx = 0;
  avlnode *node;
  unsigned int node_idx = 0;
  int i;
  if ((avlt_idx = tree_create()) == 0)
  {
    fprintf(stdout, "create AVL tree failed\n");
    permutation_error += 1;
    return;
  }
  char b[] = "ABCDEFGHIJ";
  for (i = 0; i < strlen(b); i += 1)
  {
    if ((((node_idx = tree_insert(avlt, b[i])) == 0) || (tree_find(avlt, b[i]) != (&node[node_idx]))) || (tree_check(avlt) != 1))
    {
      fprintf(stdout, "insert %c failed\n", b[i]);
      permutation_error += 1;
      return;
    }
  }

  for (i = 0; i < strlen(a); i += 1)
  {
    if ((tree_delete(avlt, a[i]) != 1) || (tree_check(avlt) != 1))
    {
      fprintf(stdout, "delete %c failed\n", a[i]);
      permutation_error += 1;
      return;
    }
  }

  avl_destroy(avlt);
}


/*** DEPENDENCIES:
int tree_check(avltree *avlt)
{
  mydata min;
  mydata max;
  int rc;
  min.key = -2147483648;
  max.key = 2147483647;
  rc = 1;
  if (avl_check_order(avlt, &min, &max) != 1)
  {
    fprintf(stdout, "tree_check: invalid order\n");
    rc = 0;
  }
  if (avl_check_height(avlt) != 1)
  {
    fprintf(stdout, "tree_check: invalid height\n");
    rc = 0;
  }
  return rc;
}


----------------------------
typedef struct avlnode
{
  struct avlnode *left;
  struct avlnode *right;
  struct avlnode *parent;
  char bf;
  void *data;
} avlnode
----------------------------
int permutation_error = 0
----------------------------
avltree *tree_create()
{
  return avl_create(compare_func, destroy_func);
}


----------------------------
typedef struct 
{
  int (*compare)(const void *, const void *);
  void (*print)(void *);
  void (*destroy)(void *);
  avlnode root;
  avlnode nil;
  avlnode *min;
} avltree
----------------------------
void avl_destroy(avltree *avlt)
{
  destroy(avlt, avlt->root.left);
  free(avlt);
}


----------------------------
int tree_delete(avltree *avlt, int key)
{
  avlnode *node;
  unsigned int node_idx = 0;
  if ((node_idx = tree_find(avlt, key)) == 0)
  {
    fprintf(stdout, "tree_delete: %d not found\n", key);
    return 0;
  }
  avl_delete(avlt, node, 0);
  if (tree_find(avlt, key) == (&node[node_idx]))
  {
    fprintf(stdout, "tree_delete: delete %d failed\n", key);
    return 0;
  }
  return 1;
}


----------------------------
avlnode *tree_insert(avltree *avlt, int key)
{
  avlnode *node;
  unsigned int node_idx = 0;
  mydata *data;
  unsigned int data_idx = 0;
  if ((key < (-2147483648)) || (key > 2147483647))
  {
    fprintf(stdout, "tree_insert: invalid key %d\n", key);
    return 0;
  }
  if (((data_idx = makedata(key)) == 0) || ((node_idx = avl_insert(avlt, data)) == 0))
  {
    fprintf(stdout, "tree_insert: insert %d failed\n", key);
    free(data);
    return 0;
  }
  return node;
}


----------------------------
avlnode *tree_find(avltree *avlt, int key)
{
  mydata query;
  query.key = key;
  return avl_find(avlt, &query);
}


----------------------------
***/


int unit_test_permutation_deletion()
{
  char a[] = "ABCDEFGHIJ";
  permutation_error = 0;
  permute(a, 0, strlen(a) - 1, permutation_delete);
  return permutation_error == 0;
}


/*** DEPENDENCIES:
int permutation_error = 0
----------------------------
void permutation_delete(char *a)
{
  avltree *avlt;
  unsigned int avlt_idx = 0;
  avlnode *node;
  unsigned int node_idx = 0;
  int i;
  if ((avlt_idx = tree_create()) == 0)
  {
    fprintf(stdout, "create AVL tree failed\n");
    permutation_error += 1;
    return;
  }
  char b[] = "ABCDEFGHIJ";
  for (i = 0; i < strlen(b); i += 1)
  {
    if ((((node_idx = tree_insert(avlt, b[i])) == 0) || (tree_find(avlt, b[i]) != (&node[node_idx]))) || (tree_check(avlt) != 1))
    {
      fprintf(stdout, "insert %c failed\n", b[i]);
      permutation_error += 1;
      return;
    }
  }

  for (i = 0; i < strlen(a); i += 1)
  {
    if ((tree_delete(avlt, a[i]) != 1) || (tree_check(avlt) != 1))
    {
      fprintf(stdout, "delete %c failed\n", a[i]);
      permutation_error += 1;
      return;
    }
  }

  avl_destroy(avlt);
}


----------------------------
void permute(char *a, int start, int end, void func(char *))
{
  if (start == end)
  {
    func(a);
    return;
  }
  int i;
  for (i = start; i <= end; i += 1)
  {
    swap(a + start, a + i);
    permute(a, start + 1, end, func);
    swap(a + start, a + i);
  }

}


----------------------------
***/


int unit_test_random_insertion_deletion()
{
  avltree *avlt;
  unsigned int avlt_idx = 0;
  int ninsert;
  int ndelete;
  int i;
  int key;
  int max;
  if ((avlt_idx = tree_create()) == 0)
  {
    fprintf(stdout, "create AVL tree failed\n");
    goto err0;
  }
  ninsert = 0;
  ndelete = 0;
  max = 9999;
  srand((unsigned int) time(0));
  for (i = 1; i <= 1999; i += 1)
  {
    key = rand() % max;
    if (tree_find(avlt, key) != 0)
    {
      continue;
    }
    ninsert += 1;
    if ((tree_insert(avlt, key) == 0) || (tree_check(avlt) != 1))
    {
      fprintf(stdout, "insert %d failed\n", key);
      goto err;
    }
  }

  for (i = 1; i < max; i += 1)
  {
    key = rand() % max;
    if (tree_find(avlt, key) == 0)
    {
      continue;
    }
    ndelete += 1;
    if ((tree_delete(avlt, key) != 1) || (tree_check(avlt) != 1))
    {
      fprintf(stdout, "delete %d failed\n", key);
      goto err;
    }
  }

  printf("\tstat: ninsert=%d, ndelete=%d\n", ninsert, ndelete);
  avl_destroy(avlt);
  return 1;
  err:
  avl_destroy(avlt);

  err0:
  return 0;

}


/*** DEPENDENCIES:
int tree_check(avltree *avlt)
{
  mydata min;
  mydata max;
  int rc;
  min.key = -2147483648;
  max.key = 2147483647;
  rc = 1;
  if (avl_check_order(avlt, &min, &max) != 1)
  {
    fprintf(stdout, "tree_check: invalid order\n");
    rc = 0;
  }
  if (avl_check_height(avlt) != 1)
  {
    fprintf(stdout, "tree_check: invalid height\n");
    rc = 0;
  }
  return rc;
}


----------------------------
avltree *tree_create()
{
  return avl_create(compare_func, destroy_func);
}


----------------------------
typedef struct 
{
  int (*compare)(const void *, const void *);
  void (*print)(void *);
  void (*destroy)(void *);
  avlnode root;
  avlnode nil;
  avlnode *min;
} avltree
----------------------------
void avl_destroy(avltree *avlt)
{
  destroy(avlt, avlt->root.left);
  free(avlt);
}


----------------------------
int tree_delete(avltree *avlt, int key)
{
  avlnode *node;
  unsigned int node_idx = 0;
  if ((node_idx = tree_find(avlt, key)) == 0)
  {
    fprintf(stdout, "tree_delete: %d not found\n", key);
    return 0;
  }
  avl_delete(avlt, node, 0);
  if (tree_find(avlt, key) == (&node[node_idx]))
  {
    fprintf(stdout, "tree_delete: delete %d failed\n", key);
    return 0;
  }
  return 1;
}


----------------------------
avlnode *tree_insert(avltree *avlt, int key)
{
  avlnode *node;
  unsigned int node_idx = 0;
  mydata *data;
  unsigned int data_idx = 0;
  if ((key < (-2147483648)) || (key > 2147483647))
  {
    fprintf(stdout, "tree_insert: invalid key %d\n", key);
    return 0;
  }
  if (((data_idx = makedata(key)) == 0) || ((node_idx = avl_insert(avlt, data)) == 0))
  {
    fprintf(stdout, "tree_insert: insert %d failed\n", key);
    free(data);
    return 0;
  }
  return node;
}


----------------------------
avlnode *tree_find(avltree *avlt, int key)
{
  mydata query;
  query.key = key;
  return avl_find(avlt, &query);
}


----------------------------
pub time: Time
----------------------------
***/


int unit_test_min()
{
  avltree *avlt;
  unsigned int avlt_idx = 0;
  if ((avlt_idx = tree_create()) == 0)
  {
    fprintf(stdout, "create AVL tree failed\n");
    goto err0;
  }
  if (((((((((((((avlt->min != 0) || (tree_insert(avlt, 'B') == 0)) || (avlt->min != tree_find(avlt, 'B'))) || (tree_insert(avlt, 'A') == 0)) || (avlt->min != tree_find(avlt, 'A'))) || (tree_insert(avlt, 'C') == 0)) || (avlt->min != tree_find(avlt, 'A'))) || (tree_delete(avlt, 'B') != 1)) || (avlt->min != tree_find(avlt, 'A'))) || (tree_delete(avlt, 'A') != 1)) || (avlt->min != tree_find(avlt, 'C'))) || (tree_delete(avlt, 'C') != 1)) || (avlt->min != 0))
  {
    fprintf(stdout, "invalid min\n");
    goto err;
  }
  avl_destroy(avlt);
  return 1;
  err:
  avl_destroy(avlt);

  err0:
  return 0;

}


/*** DEPENDENCIES:
avltree *tree_create()
{
  return avl_create(compare_func, destroy_func);
}


----------------------------
typedef struct 
{
  int (*compare)(const void *, const void *);
  void (*print)(void *);
  void (*destroy)(void *);
  avlnode root;
  avlnode nil;
  avlnode *min;
} avltree
----------------------------
void avl_destroy(avltree *avlt)
{
  destroy(avlt, avlt->root.left);
  free(avlt);
}


----------------------------
int tree_delete(avltree *avlt, int key)
{
  avlnode *node;
  unsigned int node_idx = 0;
  if ((node_idx = tree_find(avlt, key)) == 0)
  {
    fprintf(stdout, "tree_delete: %d not found\n", key);
    return 0;
  }
  avl_delete(avlt, node, 0);
  if (tree_find(avlt, key) == (&node[node_idx]))
  {
    fprintf(stdout, "tree_delete: delete %d failed\n", key);
    return 0;
  }
  return 1;
}


----------------------------
avlnode *tree_insert(avltree *avlt, int key)
{
  avlnode *node;
  unsigned int node_idx = 0;
  mydata *data;
  unsigned int data_idx = 0;
  if ((key < (-2147483648)) || (key > 2147483647))
  {
    fprintf(stdout, "tree_insert: invalid key %d\n", key);
    return 0;
  }
  if (((data_idx = makedata(key)) == 0) || ((node_idx = avl_insert(avlt, data)) == 0))
  {
    fprintf(stdout, "tree_insert: insert %d failed\n", key);
    free(data);
    return 0;
  }
  return node;
}


----------------------------
avlnode *tree_find(avltree *avlt, int key)
{
  mydata query;
  query.key = key;
  return avl_find(avlt, &query);
}


----------------------------
***/


int unit_test_atomic_deletion()
{
  avltree *avlt;
  unsigned int avlt_idx = 0;
  int i;
  int j;
  char *cases[] = {"P", "P", "PH", "H", "PH", "P", "PX", "P", "PX", "X", "PHX", "H", "PHX", "P", "PHX", "X", "PHXD", "X", "PHXDLTBF", "X", "PHXDLTB", "X", "PHXDLTF", "X", "PHXDL", "X", "PHXDLTBFJN", "X", "PHXDLTBFJ", "X", "PHXDLTBFN", "X", "PHXDLTBJN", "X", "PHXDLTBJ", "X", "PHXDLTBN", "X", "PHXDLTFJN", "X", "PHXDLTFJ", "X", "PHXDLTFN", "X", "PHXL", "X", "PHXDLTJN", "X", "PHXDLTJ", "X", "PHXDLTN", "X", "PHXb", "H", "PHXDTbZd", "H", "PHXDTbZ", "H", "PHXDTbd", "H", "PHXTb", "H", "PHXDTbRVZd", "H", "PHXDTbRVZ", "H", "PHXDTbRVd", "H", "PHXDTbRZd", "H", "PHXDTbRZ", "H", "PHXDTbRd", "H", "PHXDTbVZd", "H", "PHXDTbVZ", "H", "PHXDTbVd", "H", "PHXT", "H", "PHXDTbRV", "H", "PHXDTbR", "H", "PHXDTbV", "H", 0, 0};
  for (i = 0; (i < ((sizeof(cases)) / (sizeof(cases[0])))) && (cases[i] != 0); i += 2)
  {
    if ((avlt_idx = tree_create()) == 0)
    {
      fprintf(stdout, "%s-%s - create AVL tree failed\n", cases[i], cases[i + 1]);
      goto err0;
    }
    for (j = 0; j < strlen(cases[i]); j += 1)
    {
      if ((tree_insert(avlt, cases[i][j]) == 0) || (tree_check(avlt) != 1))
      {
        fprintf(stdout, "%s-%s - insert %c failed\n", cases[i], cases[i + 1], cases[i][j]);
        goto err;
      }
    }

    for (j = 0; j < strlen(cases[i + 1]); j += 1)
    {
      if ((tree_delete(avlt, cases[i + 1][j]) == 0) || (tree_check(avlt) != 1))
      {
        fprintf(stdout, "%s-%s - delete %c failed\n", cases[i], cases[i + 1], cases[i + 1][j]);
        goto err;
      }
    }

    avl_destroy(avlt);
  }

  return 1;
  err:
  avl_destroy(avlt);

  err0:
  return 0;

}


/*** DEPENDENCIES:
int tree_check(avltree *avlt)
{
  mydata min;
  mydata max;
  int rc;
  min.key = -2147483648;
  max.key = 2147483647;
  rc = 1;
  if (avl_check_order(avlt, &min, &max) != 1)
  {
    fprintf(stdout, "tree_check: invalid order\n");
    rc = 0;
  }
  if (avl_check_height(avlt) != 1)
  {
    fprintf(stdout, "tree_check: invalid height\n");
    rc = 0;
  }
  return rc;
}


----------------------------
avltree *tree_create()
{
  return avl_create(compare_func, destroy_func);
}


----------------------------
typedef struct 
{
  int (*compare)(const void *, const void *);
  void (*print)(void *);
  void (*destroy)(void *);
  avlnode root;
  avlnode nil;
  avlnode *min;
} avltree
----------------------------
void avl_destroy(avltree *avlt)
{
  destroy(avlt, avlt->root.left);
  free(avlt);
}


----------------------------
int tree_delete(avltree *avlt, int key)
{
  avlnode *node;
  unsigned int node_idx = 0;
  if ((node_idx = tree_find(avlt, key)) == 0)
  {
    fprintf(stdout, "tree_delete: %d not found\n", key);
    return 0;
  }
  avl_delete(avlt, node, 0);
  if (tree_find(avlt, key) == (&node[node_idx]))
  {
    fprintf(stdout, "tree_delete: delete %d failed\n", key);
    return 0;
  }
  return 1;
}


----------------------------
avlnode *tree_insert(avltree *avlt, int key)
{
  avlnode *node;
  unsigned int node_idx = 0;
  mydata *data;
  unsigned int data_idx = 0;
  if ((key < (-2147483648)) || (key > 2147483647))
  {
    fprintf(stdout, "tree_insert: invalid key %d\n", key);
    return 0;
  }
  if (((data_idx = makedata(key)) == 0) || ((node_idx = avl_insert(avlt, data)) == 0))
  {
    fprintf(stdout, "tree_insert: insert %d failed\n", key);
    free(data);
    return 0;
  }
  return node;
}


----------------------------
***/


int unit_test_create()
{
  avltree *avlt;
  unsigned int avlt_idx = 0;
  if ((avlt_idx = tree_create()) == 0)
  {
    fprintf(stdout, "create AVL tree failed\n");
    return 0;
  }
  if ((((((((((((avlt->compare != compare_func) || (avlt->destroy != destroy_func)) || (avlt->nil.left != (&avlt->nil))) || (avlt->nil.right != (&avlt->nil))) || (avlt->nil.parent != (&avlt->nil))) || (avlt->nil.bf != 0)) || (avlt->nil.data != 0)) || (avlt->root.left != (&avlt->nil))) || (avlt->root.right != (&avlt->nil))) || (avlt->root.parent != (&avlt->nil))) || (avlt->root.bf != 0)) || (avlt->root.data != 0))
  {
    fprintf(stdout, "init 1\n");
    avl_destroy(avlt);
    return 0;
  }
  avl_destroy(avlt);
  return 1;
}


/*** DEPENDENCIES:
int compare_func(const void *d1, const void *d2)
{
  mydata *p1;
  unsigned int p1_idx = 0;
  mydata *p2;
  unsigned int p2_idx = 0;
  assert(d1 != 0);
  assert(d2 != 0);
  p1_idx = (mydata *) d1;
  p2_idx = (mydata *) d2;
  if (p1->key == p2->key)
  {
    return 0;
  }
  else
    if (p1->key > p2->key)
  {
    return 1;
  }
  else
    return -1;
}


----------------------------
avltree *tree_create()
{
  return avl_create(compare_func, destroy_func);
}


----------------------------
typedef struct 
{
  int (*compare)(const void *, const void *);
  void (*print)(void *);
  void (*destroy)(void *);
  avlnode root;
  avlnode nil;
  avlnode *min;
} avltree
----------------------------
void destroy_func(void *d)
{
  mydata *p;
  unsigned int p_idx = 0;
  assert(d != 0);
  p_idx = (mydata *) d;
  free(p);
}


----------------------------
void avl_destroy(avltree *avlt)
{
  destroy(avlt, avlt->root.left);
  free(avlt);
}


----------------------------
***/


int unit_test_dup()
{
  avltree *avlt;
  unsigned int avlt_idx = 0;
  avlnode *n1;
  unsigned int n1_idx = 0;
  avlnode *n2;
  unsigned int n2_idx = 0;
  if ((avlt_idx = tree_create()) == 0)
  {
    fprintf(stdout, "create AVL tree failed\n");
    goto err0;
  }
  if (((n1_idx = tree_insert(avlt, 'N')) == 0) || ((n2_idx = tree_insert(avlt, 'N')) == 0))
  {
    fprintf(stdout, "insert failed\n");
    goto err;
  }
  if (((&n1[n1_idx]) == (&n2[n2_idx])) || (n1->right != (&n2[n2_idx])))
  {
    fprintf(stdout, "invalid dup\n");
    goto err;
  }
  avl_destroy(avlt);
  return 1;
  err:
  avl_destroy(avlt);

  err0:
  return 0;

}


/*** DEPENDENCIES:
typedef struct avlnode
{
  struct avlnode *left;
  struct avlnode *right;
  struct avlnode *parent;
  char bf;
  void *data;
} avlnode
----------------------------
avltree *tree_create()
{
  return avl_create(compare_func, destroy_func);
}


----------------------------
typedef struct 
{
  int (*compare)(const void *, const void *);
  void (*print)(void *);
  void (*destroy)(void *);
  avlnode root;
  avlnode nil;
  avlnode *min;
} avltree
----------------------------
void avl_destroy(avltree *avlt)
{
  destroy(avlt, avlt->root.left);
  free(avlt);
}


----------------------------
avlnode *tree_insert(avltree *avlt, int key)
{
  avlnode *node;
  unsigned int node_idx = 0;
  mydata *data;
  unsigned int data_idx = 0;
  if ((key < (-2147483648)) || (key > 2147483647))
  {
    fprintf(stdout, "tree_insert: invalid key %d\n", key);
    return 0;
  }
  if (((data_idx = makedata(key)) == 0) || ((node_idx = avl_insert(avlt, data)) == 0))
  {
    fprintf(stdout, "tree_insert: insert %d failed\n", key);
    free(data);
    return 0;
  }
  return node;
}


----------------------------
***/


int unit_test_successor()
{
  avltree *avlt;
  unsigned int avlt_idx = 0;
  avlnode *r;
  unsigned int r_idx = 0;
  avlnode *e;
  unsigned int e_idx = 0;
  avlnode *d;
  unsigned int d_idx = 0;
  avlnode *s;
  unsigned int s_idx = 0;
  avlnode *o;
  unsigned int o_idx = 0;
  avlnode *x;
  unsigned int x_idx = 0;
  avlnode *c;
  unsigned int c_idx = 0;
  avlnode *u;
  unsigned int u_idx = 0;
  avlnode *b;
  unsigned int b_idx = 0;
  avlnode *t;
  unsigned int t_idx = 0;
  if ((avlt_idx = tree_create()) == 0)
  {
    fprintf(stdout, "create AVL tree failed\n");
    goto err0;
  }
  if (((((((((((((r_idx = tree_insert(avlt, 'R')) == 0) || ((e_idx = tree_insert(avlt, 'E')) == 0)) || ((d_idx = tree_insert(avlt, 'D')) == 0)) || ((s_idx = tree_insert(avlt, 'S')) == 0)) || ((o_idx = tree_insert(avlt, 'O')) == 0)) || ((x_idx = tree_insert(avlt, 'X')) == 0)) || ((c_idx = tree_insert(avlt, 'C')) == 0)) || ((u_idx = tree_insert(avlt, 'U')) == 0)) || ((b_idx = tree_insert(avlt, 'B')) == 0)) || ((t_idx = tree_insert(avlt, 'T')) == 0)) || (tree_delete(avlt, 'O') != 1)) || (tree_check(avlt) != 1))
  {
    fprintf(stdout, "init failed\n");
    goto err;
  }
  if (((((((((avl_successor(avlt, b) != (&c[c_idx])) || (avl_successor(avlt, c) != (&d[d_idx]))) || (avl_successor(avlt, d) != (&e[e_idx]))) || (avl_successor(avlt, e) != (&r[r_idx]))) || (avl_successor(avlt, r) != (&s[s_idx]))) || (avl_successor(avlt, s) != (&t[t_idx]))) || (avl_successor(avlt, t) != (&u[u_idx]))) || (avl_successor(avlt, u) != (&x[x_idx]))) || (avl_successor(avlt, x) != 0))
  {
    fprintf(stdout, "successor failed\n");
    goto err;
  }
  avl_destroy(avlt);
  return 1;
  err:
  avl_destroy(avlt);

  err0:
  return 0;

}


/*** DEPENDENCIES:
int tree_check(avltree *avlt)
{
  mydata min;
  mydata max;
  int rc;
  min.key = -2147483648;
  max.key = 2147483647;
  rc = 1;
  if (avl_check_order(avlt, &min, &max) != 1)
  {
    fprintf(stdout, "tree_check: invalid order\n");
    rc = 0;
  }
  if (avl_check_height(avlt) != 1)
  {
    fprintf(stdout, "tree_check: invalid height\n");
    rc = 0;
  }
  return rc;
}


----------------------------
typedef struct avlnode
{
  struct avlnode *left;
  struct avlnode *right;
  struct avlnode *parent;
  char bf;
  void *data;
} avlnode
----------------------------
avltree *tree_create()
{
  return avl_create(compare_func, destroy_func);
}


----------------------------
typedef struct 
{
  int (*compare)(const void *, const void *);
  void (*print)(void *);
  void (*destroy)(void *);
  avlnode root;
  avlnode nil;
  avlnode *min;
} avltree
----------------------------
avlnode *avl_successor(avltree *avlt, avlnode *node)
{
  unsigned int node_idx = 0;
  avlnode *p;
  unsigned int p_idx = 0;
  p_idx = node->right;
  if ((&p[p_idx]) != (&avlt->nil))
  {
    for (; p->left != (&avlt->nil); p_idx = p_idx->left)
      ;

  }
  else
  {
    for (p_idx = node->parent; (&node[node_idx]) == p->right; node_idx = &p[p_idx], p_idx = p_idx->parent)
      ;

    if ((&p[p_idx]) == (&avlt->root))
    {
      p_idx = 0;
    }
  }
  return p;
}


----------------------------
void avl_destroy(avltree *avlt)
{
  destroy(avlt, avlt->root.left);
  free(avlt);
}


----------------------------
int tree_delete(avltree *avlt, int key)
{
  avlnode *node;
  unsigned int node_idx = 0;
  if ((node_idx = tree_find(avlt, key)) == 0)
  {
    fprintf(stdout, "tree_delete: %d not found\n", key);
    return 0;
  }
  avl_delete(avlt, node, 0);
  if (tree_find(avlt, key) == (&node[node_idx]))
  {
    fprintf(stdout, "tree_delete: delete %d failed\n", key);
    return 0;
  }
  return 1;
}


----------------------------
avlnode *tree_insert(avltree *avlt, int key)
{
  avlnode *node;
  unsigned int node_idx = 0;
  mydata *data;
  unsigned int data_idx = 0;
  if ((key < (-2147483648)) || (key > 2147483647))
  {
    fprintf(stdout, "tree_insert: invalid key %d\n", key);
    return 0;
  }
  if (((data_idx = makedata(key)) == 0) || ((node_idx = avl_insert(avlt, data)) == 0))
  {
    fprintf(stdout, "tree_insert: insert %d failed\n", key);
    free(data);
    return 0;
  }
  return node;
}


----------------------------
***/


int unit_test_chain_insertion()
{
  avltree *avlt;
  unsigned int avlt_idx = 0;
  int i;
  int j;
  char *cases[] = {"PHXDB", "PHXDF", "PHXLJ", "PHXLN", "PHXTR", "PHXTV", "PHXbZ", "PHXbd", "PHXDLB", "PHXDLF", "PHXDLJ", "PHXDLN", "PHXTbR", "PHXTbV", "PHXTbV", "PHXTbZ", "PHXTbd", 0};
  for (i = 0; (i < ((sizeof(cases)) / (sizeof(cases[0])))) && (cases[i] != 0); i += 1)
  {
    if ((avlt_idx = tree_create()) == 0)
    {
      fprintf(stdout, "%s - create AVL tree failed\n", cases[i]);
      goto err0;
    }
    for (j = 0; j < strlen(cases[i]); j += 1)
    {
      if ((tree_insert(avlt, cases[i][j]) == 0) || (tree_check(avlt) != 1))
      {
        fprintf(stdout, "%s - insert %c failed\n", cases[i], cases[i][j]);
        goto err;
      }
    }

    avl_destroy(avlt);
  }

  return 1;
  err:
  avl_destroy(avlt);

  err0:
  return 0;

}


/*** DEPENDENCIES:
int tree_check(avltree *avlt)
{
  mydata min;
  mydata max;
  int rc;
  min.key = -2147483648;
  max.key = 2147483647;
  rc = 1;
  if (avl_check_order(avlt, &min, &max) != 1)
  {
    fprintf(stdout, "tree_check: invalid order\n");
    rc = 0;
  }
  if (avl_check_height(avlt) != 1)
  {
    fprintf(stdout, "tree_check: invalid height\n");
    rc = 0;
  }
  return rc;
}


----------------------------
avltree *tree_create()
{
  return avl_create(compare_func, destroy_func);
}


----------------------------
typedef struct 
{
  int (*compare)(const void *, const void *);
  void (*print)(void *);
  void (*destroy)(void *);
  avlnode root;
  avlnode nil;
  avlnode *min;
} avltree
----------------------------
void avl_destroy(avltree *avlt)
{
  destroy(avlt, avlt->root.left);
  free(avlt);
}


----------------------------
avlnode *tree_insert(avltree *avlt, int key)
{
  avlnode *node;
  unsigned int node_idx = 0;
  mydata *data;
  unsigned int data_idx = 0;
  if ((key < (-2147483648)) || (key > 2147483647))
  {
    fprintf(stdout, "tree_insert: invalid key %d\n", key);
    return 0;
  }
  if (((data_idx = makedata(key)) == 0) || ((node_idx = avl_insert(avlt, data)) == 0))
  {
    fprintf(stdout, "tree_insert: insert %d failed\n", key);
    free(data);
    return 0;
  }
  return node;
}


----------------------------
***/


int unit_test_chain_deletion()
{
  avltree *avlt;
  unsigned int avlt_idx = 0;
  int i;
  int j;
  char *cases[] = {"PHXDLTbFJNZK", "T", "PHXDLTbFJNZdK", "T", "PHXDLTbFJNdK", "T", "PHXDLTbFRVZU", "L", "PHXDLTbBFRVZU", "L", "PHXDLTbBRVZU", "L", 0, 0};
  for (i = 0; (i < ((sizeof(cases)) / (sizeof(cases[0])))) && (cases[i] != 0); i += 2)
  {
    if ((avlt_idx = tree_create()) == 0)
    {
      fprintf(stdout, "%s-%s - create AVL tree failed\n", cases[i], cases[i + 1]);
      goto err0;
    }
    for (j = 0; j < strlen(cases[i]); j += 1)
    {
      if ((tree_insert(avlt, cases[i][j]) == 0) || (tree_check(avlt) != 1))
      {
        fprintf(stdout, "%s-%s - insert %c failed\n", cases[i], cases[i + 1], cases[i][j]);
        goto err;
      }
    }

    for (j = 0; j < strlen(cases[i + 1]); j += 1)
    {
      if ((tree_delete(avlt, cases[i + 1][j]) == 0) || (tree_check(avlt) != 1))
      {
        fprintf(stdout, "%s-%s - delete %c failed\n", cases[i], cases[i + 1], cases[i + 1][j]);
        goto err;
      }
    }

    avl_destroy(avlt);
  }

  return 1;
  err:
  avl_destroy(avlt);

  err0:
  return 0;

}


/*** DEPENDENCIES:
int tree_check(avltree *avlt)
{
  mydata min;
  mydata max;
  int rc;
  min.key = -2147483648;
  max.key = 2147483647;
  rc = 1;
  if (avl_check_order(avlt, &min, &max) != 1)
  {
    fprintf(stdout, "tree_check: invalid order\n");
    rc = 0;
  }
  if (avl_check_height(avlt) != 1)
  {
    fprintf(stdout, "tree_check: invalid height\n");
    rc = 0;
  }
  return rc;
}


----------------------------
avltree *tree_create()
{
  return avl_create(compare_func, destroy_func);
}


----------------------------
typedef struct 
{
  int (*compare)(const void *, const void *);
  void (*print)(void *);
  void (*destroy)(void *);
  avlnode root;
  avlnode nil;
  avlnode *min;
} avltree
----------------------------
void avl_destroy(avltree *avlt)
{
  destroy(avlt, avlt->root.left);
  free(avlt);
}


----------------------------
int tree_delete(avltree *avlt, int key)
{
  avlnode *node;
  unsigned int node_idx = 0;
  if ((node_idx = tree_find(avlt, key)) == 0)
  {
    fprintf(stdout, "tree_delete: %d not found\n", key);
    return 0;
  }
  avl_delete(avlt, node, 0);
  if (tree_find(avlt, key) == (&node[node_idx]))
  {
    fprintf(stdout, "tree_delete: delete %d failed\n", key);
    return 0;
  }
  return 1;
}


----------------------------
avlnode *tree_insert(avltree *avlt, int key)
{
  avlnode *node;
  unsigned int node_idx = 0;
  mydata *data;
  unsigned int data_idx = 0;
  if ((key < (-2147483648)) || (key > 2147483647))
  {
    fprintf(stdout, "tree_insert: invalid key %d\n", key);
    return 0;
  }
  if (((data_idx = makedata(key)) == 0) || ((node_idx = avl_insert(avlt, data)) == 0))
  {
    fprintf(stdout, "tree_insert: insert %d failed\n", key);
    free(data);
    return 0;
  }
  return node;
}


----------------------------
***/


int unit_test_atomic_insertion()
{
  avltree *avlt;
  unsigned int avlt_idx = 0;
  int i;
  int j;
  char *cases[] = {"P", "PH", "PX", "PHDPHXDLB", "PHXDLF", "PHL", "PHXDLJ", "PHXDLN", "PXb", "PHXTbZ", "PHXTbd", "PHXT", "PHXTbRV", "PHXTbR", "PHXTbV", 0};
  for (i = 0; (i < ((sizeof(cases)) / (sizeof(cases[0])))) && cases[i]; i += 1)
  {
    if ((avlt_idx = tree_create()) == 0)
    {
      fprintf(stdout, "%s - create AVL tree failed\n", cases[i]);
      goto err0;
    }
    for (j = 0; j < strlen(cases[i]); j += 1)
    {
      if ((tree_insert(avlt, cases[i][j]) == 0) || (tree_check(avlt) != 1))
      {
        fprintf(stdout, "%s - insert %c failed\n", cases[i], cases[i][j]);
        goto err;
      }
    }

    avl_destroy(avlt);
  }

  return 1;
  err:
  avl_destroy(avlt);

  err0:
  return 0;

}


/*** DEPENDENCIES:
int tree_check(avltree *avlt)
{
  mydata min;
  mydata max;
  int rc;
  min.key = -2147483648;
  max.key = 2147483647;
  rc = 1;
  if (avl_check_order(avlt, &min, &max) != 1)
  {
    fprintf(stdout, "tree_check: invalid order\n");
    rc = 0;
  }
  if (avl_check_height(avlt) != 1)
  {
    fprintf(stdout, "tree_check: invalid height\n");
    rc = 0;
  }
  return rc;
}


----------------------------
avltree *tree_create()
{
  return avl_create(compare_func, destroy_func);
}


----------------------------
typedef struct 
{
  int (*compare)(const void *, const void *);
  void (*print)(void *);
  void (*destroy)(void *);
  avlnode root;
  avlnode nil;
  avlnode *min;
} avltree
----------------------------
void avl_destroy(avltree *avlt)
{
  destroy(avlt, avlt->root.left);
  free(avlt);
}


----------------------------
avlnode *tree_insert(avltree *avlt, int key)
{
  avlnode *node;
  unsigned int node_idx = 0;
  mydata *data;
  unsigned int data_idx = 0;
  if ((key < (-2147483648)) || (key > 2147483647))
  {
    fprintf(stdout, "tree_insert: invalid key %d\n", key);
    return 0;
  }
  if (((data_idx = makedata(key)) == 0) || ((node_idx = avl_insert(avlt, data)) == 0))
  {
    fprintf(stdout, "tree_insert: insert %d failed\n", key);
    free(data);
    return 0;
  }
  return node;
}


----------------------------
***/


int unit_test_find()
{
  avltree *avlt;
  unsigned int avlt_idx = 0;
  avlnode *r;
  unsigned int r_idx = 0;
  avlnode *e;
  unsigned int e_idx = 0;
  avlnode *d;
  unsigned int d_idx = 0;
  avlnode *s;
  unsigned int s_idx = 0;
  avlnode *o;
  unsigned int o_idx = 0;
  avlnode *x;
  unsigned int x_idx = 0;
  avlnode *c;
  unsigned int c_idx = 0;
  avlnode *u;
  unsigned int u_idx = 0;
  avlnode *b;
  unsigned int b_idx = 0;
  avlnode *t;
  unsigned int t_idx = 0;
  if ((avlt_idx = tree_create()) == 0)
  {
    fprintf(stdout, "create AVL tree failed\n");
    goto err0;
  }
  if ((((((((((((r_idx = tree_insert(avlt, 'R')) == 0) || ((e_idx = tree_insert(avlt, 'E')) == 0)) || ((d_idx = tree_insert(avlt, 'D')) == 0)) || ((s_idx = tree_insert(avlt, 'S')) == 0)) || ((o_idx = tree_insert(avlt, 'O')) == 0)) || ((x_idx = tree_insert(avlt, 'X')) == 0)) || ((c_idx = tree_insert(avlt, 'C')) == 0)) || ((u_idx = tree_insert(avlt, 'U')) == 0)) || ((b_idx = tree_insert(avlt, 'B')) == 0)) || ((t_idx = tree_insert(avlt, 'T')) == 0)) || (tree_check(avlt) != 1))
  {
    fprintf(stdout, "init failed\n");
    goto err;
  }
  if ((((((((((avl_find(avlt, r->data) != (&r[r_idx])) || (avl_find(avlt, e->data) != (&e[e_idx]))) || (avl_find(avlt, d->data) != (&d[d_idx]))) || (avl_find(avlt, s->data) != (&s[s_idx]))) || (avl_find(avlt, o->data) != (&o[o_idx]))) || (avl_find(avlt, x->data) != (&x[x_idx]))) || (avl_find(avlt, c->data) != (&c[c_idx]))) || (avl_find(avlt, u->data) != (&u[u_idx]))) || (avl_find(avlt, b->data) != (&b[b_idx]))) || (avl_find(avlt, t->data) != (&t[t_idx])))
  {
    fprintf(stdout, "find failed\n");
    goto err;
  }
  avl_destroy(avlt);
  return 1;
  err:
  avl_destroy(avlt);

  err0:
  return 0;

}


/*** DEPENDENCIES:
int tree_check(avltree *avlt)
{
  mydata min;
  mydata max;
  int rc;
  min.key = -2147483648;
  max.key = 2147483647;
  rc = 1;
  if (avl_check_order(avlt, &min, &max) != 1)
  {
    fprintf(stdout, "tree_check: invalid order\n");
    rc = 0;
  }
  if (avl_check_height(avlt) != 1)
  {
    fprintf(stdout, "tree_check: invalid height\n");
    rc = 0;
  }
  return rc;
}


----------------------------
avlnode *avl_find(avltree *avlt, void *data)
{
  avlnode *p;
  unsigned int p_idx = 0;
  p_idx = avlt->root.left;
  while ((&p[p_idx]) != (&avlt->nil))
  {
    int cmp;
    cmp = avlt->compare(data, p->data);
    if (cmp == 0)
    {
      return p;
    }
    p_idx = (cmp < 0) ? (p_idx->left) : (p_idx->right);
  }

  return 0;
}


----------------------------
typedef struct avlnode
{
  struct avlnode *left;
  struct avlnode *right;
  struct avlnode *parent;
  char bf;
  void *data;
} avlnode
----------------------------
avltree *tree_create()
{
  return avl_create(compare_func, destroy_func);
}


----------------------------
typedef struct 
{
  int (*compare)(const void *, const void *);
  void (*print)(void *);
  void (*destroy)(void *);
  avlnode root;
  avlnode nil;
  avlnode *min;
} avltree
----------------------------
void avl_destroy(avltree *avlt)
{
  destroy(avlt, avlt->root.left);
  free(avlt);
}


----------------------------
avlnode *tree_insert(avltree *avlt, int key)
{
  avlnode *node;
  unsigned int node_idx = 0;
  mydata *data;
  unsigned int data_idx = 0;
  if ((key < (-2147483648)) || (key > 2147483647))
  {
    fprintf(stdout, "tree_insert: invalid key %d\n", key);
    return 0;
  }
  if (((data_idx = makedata(key)) == 0) || ((node_idx = avl_insert(avlt, data)) == 0))
  {
    fprintf(stdout, "tree_insert: insert %d failed\n", key);
    free(data);
    return 0;
  }
  return node;
}


----------------------------
***/


void all_tests()
{
  do
  {
    mu_tests += 1;
    printf("#%03d %s \n", mu_tests, "unit_test_create");
    if (unit_test_create())
    {
      printf("PASSED\n");
    }
    else
    {
      printf("FAILED\n");
      mu_fails++;
    }
  }
  while (0);
  do
  {
    mu_tests += 1;
    printf("#%03d %s \n", mu_tests, "unit_test_find");
    if (unit_test_find())
    {
      printf("PASSED\n");
    }
    else
    {
      printf("FAILED\n");
      mu_fails++;
    }
  }
  while (0);
  do
  {
    mu_tests += 1;
    printf("#%03d %s \n", mu_tests, "unit_test_successor");
    if (unit_test_successor())
    {
      printf("PASSED\n");
    }
    else
    {
      printf("FAILED\n");
      mu_fails++;
    }
  }
  while (0);
  do
  {
    mu_tests += 1;
    printf("#%03d %s \n", mu_tests, "unit_test_atomic_insertion");
    if (unit_test_atomic_insertion())
    {
      printf("PASSED\n");
    }
    else
    {
      printf("FAILED\n");
      mu_fails++;
    }
  }
  while (0);
  do
  {
    mu_tests += 1;
    printf("#%03d %s \n", mu_tests, "unit_test_atomic_deletion");
    if (unit_test_atomic_deletion())
    {
      printf("PASSED\n");
    }
    else
    {
      printf("FAILED\n");
      mu_fails++;
    }
  }
  while (0);
  do
  {
    mu_tests += 1;
    printf("#%03d %s \n", mu_tests, "unit_test_chain_insertion");
    if (unit_test_chain_insertion())
    {
      printf("PASSED\n");
    }
    else
    {
      printf("FAILED\n");
      mu_fails++;
    }
  }
  while (0);
  do
  {
    mu_tests += 1;
    printf("#%03d %s \n", mu_tests, "unit_test_chain_deletion");
    if (unit_test_chain_deletion())
    {
      printf("PASSED\n");
    }
    else
    {
      printf("FAILED\n");
      mu_fails++;
    }
  }
  while (0);
  do
  {
    mu_tests += 1;
    printf("#%03d %s \n", mu_tests, "unit_test_permutation_insertion");
    if (unit_test_permutation_insertion())
    {
      printf("PASSED\n");
    }
    else
    {
      printf("FAILED\n");
      mu_fails++;
    }
  }
  while (0);
  do
  {
    mu_tests += 1;
    printf("#%03d %s \n", mu_tests, "unit_test_permutation_deletion");
    if (unit_test_permutation_deletion())
    {
      printf("PASSED\n");
    }
    else
    {
      printf("FAILED\n");
      mu_fails++;
    }
  }
  while (0);
  do
  {
    mu_tests += 1;
    printf("#%03d %s \n", mu_tests, "unit_test_random_insertion_deletion");
    if (unit_test_random_insertion_deletion())
    {
      printf("PASSED\n");
    }
    else
    {
      printf("FAILED\n");
      mu_fails++;
    }
  }
  while (0);
  do
  {
    mu_tests += 1;
    printf("#%03d %s \n", mu_tests, "unit_test_dup");
    if (unit_test_dup())
    {
      printf("PASSED\n");
    }
    else
    {
      printf("FAILED\n");
      mu_fails++;
    }
  }
  while (0);
  do
  {
    mu_tests += 1;
    printf("#%03d %s \n", mu_tests, "unit_test_min");
    if (unit_test_min())
    {
      printf("PASSED\n");
    }
    else
    {
      printf("FAILED\n");
      mu_fails++;
    }
  }
  while (0);
}


/*** DEPENDENCIES:
int unit_test_permutation_insertion()
{
  char a[] = "ABCDEFGHIJ";
  permutation_error = 0;
  permute(a, 0, strlen(a) - 1, permutation_insert);
  return permutation_error == 0;
}


----------------------------
int unit_test_random_insertion_deletion()
{
  avltree *avlt;
  unsigned int avlt_idx = 0;
  int ninsert;
  int ndelete;
  int i;
  int key;
  int max;
  if ((avlt_idx = tree_create()) == 0)
  {
    fprintf(stdout, "create AVL tree failed\n");
    goto err0;
  }
  ninsert = 0;
  ndelete = 0;
  max = 9999;
  srand((unsigned int) time(0));
  for (i = 1; i <= 1999; i += 1)
  {
    key = rand() % max;
    if (tree_find(avlt, key) != 0)
    {
      continue;
    }
    ninsert += 1;
    if ((tree_insert(avlt, key) == 0) || (tree_check(avlt) != 1))
    {
      fprintf(stdout, "insert %d failed\n", key);
      goto err;
    }
  }

  for (i = 1; i < max; i += 1)
  {
    key = rand() % max;
    if (tree_find(avlt, key) == 0)
    {
      continue;
    }
    ndelete += 1;
    if ((tree_delete(avlt, key) != 1) || (tree_check(avlt) != 1))
    {
      fprintf(stdout, "delete %d failed\n", key);
      goto err;
    }
  }

  printf("\tstat: ninsert=%d, ndelete=%d\n", ninsert, ndelete);
  avl_destroy(avlt);
  return 1;
  err:
  avl_destroy(avlt);

  err0:
  return 0;

}


----------------------------
extern int mu_fails
----------------------------
extern int mu_tests
----------------------------
int unit_test_min()
{
  avltree *avlt;
  unsigned int avlt_idx = 0;
  if ((avlt_idx = tree_create()) == 0)
  {
    fprintf(stdout, "create AVL tree failed\n");
    goto err0;
  }
  if (((((((((((((avlt->min != 0) || (tree_insert(avlt, 'B') == 0)) || (avlt->min != tree_find(avlt, 'B'))) || (tree_insert(avlt, 'A') == 0)) || (avlt->min != tree_find(avlt, 'A'))) || (tree_insert(avlt, 'C') == 0)) || (avlt->min != tree_find(avlt, 'A'))) || (tree_delete(avlt, 'B') != 1)) || (avlt->min != tree_find(avlt, 'A'))) || (tree_delete(avlt, 'A') != 1)) || (avlt->min != tree_find(avlt, 'C'))) || (tree_delete(avlt, 'C') != 1)) || (avlt->min != 0))
  {
    fprintf(stdout, "invalid min\n");
    goto err;
  }
  avl_destroy(avlt);
  return 1;
  err:
  avl_destroy(avlt);

  err0:
  return 0;

}


----------------------------
int unit_test_permutation_deletion()
{
  char a[] = "ABCDEFGHIJ";
  permutation_error = 0;
  permute(a, 0, strlen(a) - 1, permutation_delete);
  return permutation_error == 0;
}


----------------------------
int unit_test_atomic_deletion()
{
  avltree *avlt;
  unsigned int avlt_idx = 0;
  int i;
  int j;
  char *cases[] = {"P", "P", "PH", "H", "PH", "P", "PX", "P", "PX", "X", "PHX", "H", "PHX", "P", "PHX", "X", "PHXD", "X", "PHXDLTBF", "X", "PHXDLTB", "X", "PHXDLTF", "X", "PHXDL", "X", "PHXDLTBFJN", "X", "PHXDLTBFJ", "X", "PHXDLTBFN", "X", "PHXDLTBJN", "X", "PHXDLTBJ", "X", "PHXDLTBN", "X", "PHXDLTFJN", "X", "PHXDLTFJ", "X", "PHXDLTFN", "X", "PHXL", "X", "PHXDLTJN", "X", "PHXDLTJ", "X", "PHXDLTN", "X", "PHXb", "H", "PHXDTbZd", "H", "PHXDTbZ", "H", "PHXDTbd", "H", "PHXTb", "H", "PHXDTbRVZd", "H", "PHXDTbRVZ", "H", "PHXDTbRVd", "H", "PHXDTbRZd", "H", "PHXDTbRZ", "H", "PHXDTbRd", "H", "PHXDTbVZd", "H", "PHXDTbVZ", "H", "PHXDTbVd", "H", "PHXT", "H", "PHXDTbRV", "H", "PHXDTbR", "H", "PHXDTbV", "H", 0, 0};
  for (i = 0; (i < ((sizeof(cases)) / (sizeof(cases[0])))) && (cases[i] != 0); i += 2)
  {
    if ((avlt_idx = tree_create()) == 0)
    {
      fprintf(stdout, "%s-%s - create AVL tree failed\n", cases[i], cases[i + 1]);
      goto err0;
    }
    for (j = 0; j < strlen(cases[i]); j += 1)
    {
      if ((tree_insert(avlt, cases[i][j]) == 0) || (tree_check(avlt) != 1))
      {
        fprintf(stdout, "%s-%s - insert %c failed\n", cases[i], cases[i + 1], cases[i][j]);
        goto err;
      }
    }

    for (j = 0; j < strlen(cases[i + 1]); j += 1)
    {
      if ((tree_delete(avlt, cases[i + 1][j]) == 0) || (tree_check(avlt) != 1))
      {
        fprintf(stdout, "%s-%s - delete %c failed\n", cases[i], cases[i + 1], cases[i + 1][j]);
        goto err;
      }
    }

    avl_destroy(avlt);
  }

  return 1;
  err:
  avl_destroy(avlt);

  err0:
  return 0;

}


----------------------------
int unit_test_create()
{
  avltree *avlt;
  unsigned int avlt_idx = 0;
  if ((avlt_idx = tree_create()) == 0)
  {
    fprintf(stdout, "create AVL tree failed\n");
    return 0;
  }
  if ((((((((((((avlt->compare != compare_func) || (avlt->destroy != destroy_func)) || (avlt->nil.left != (&avlt->nil))) || (avlt->nil.right != (&avlt->nil))) || (avlt->nil.parent != (&avlt->nil))) || (avlt->nil.bf != 0)) || (avlt->nil.data != 0)) || (avlt->root.left != (&avlt->nil))) || (avlt->root.right != (&avlt->nil))) || (avlt->root.parent != (&avlt->nil))) || (avlt->root.bf != 0)) || (avlt->root.data != 0))
  {
    fprintf(stdout, "init 1\n");
    avl_destroy(avlt);
    return 0;
  }
  avl_destroy(avlt);
  return 1;
}


----------------------------
int unit_test_dup()
{
  avltree *avlt;
  unsigned int avlt_idx = 0;
  avlnode *n1;
  unsigned int n1_idx = 0;
  avlnode *n2;
  unsigned int n2_idx = 0;
  if ((avlt_idx = tree_create()) == 0)
  {
    fprintf(stdout, "create AVL tree failed\n");
    goto err0;
  }
  if (((n1_idx = tree_insert(avlt, 'N')) == 0) || ((n2_idx = tree_insert(avlt, 'N')) == 0))
  {
    fprintf(stdout, "insert failed\n");
    goto err;
  }
  if (((&n1[n1_idx]) == (&n2[n2_idx])) || (n1->right != (&n2[n2_idx])))
  {
    fprintf(stdout, "invalid dup\n");
    goto err;
  }
  avl_destroy(avlt);
  return 1;
  err:
  avl_destroy(avlt);

  err0:
  return 0;

}


----------------------------
int unit_test_successor()
{
  avltree *avlt;
  unsigned int avlt_idx = 0;
  avlnode *r;
  unsigned int r_idx = 0;
  avlnode *e;
  unsigned int e_idx = 0;
  avlnode *d;
  unsigned int d_idx = 0;
  avlnode *s;
  unsigned int s_idx = 0;
  avlnode *o;
  unsigned int o_idx = 0;
  avlnode *x;
  unsigned int x_idx = 0;
  avlnode *c;
  unsigned int c_idx = 0;
  avlnode *u;
  unsigned int u_idx = 0;
  avlnode *b;
  unsigned int b_idx = 0;
  avlnode *t;
  unsigned int t_idx = 0;
  if ((avlt_idx = tree_create()) == 0)
  {
    fprintf(stdout, "create AVL tree failed\n");
    goto err0;
  }
  if (((((((((((((r_idx = tree_insert(avlt, 'R')) == 0) || ((e_idx = tree_insert(avlt, 'E')) == 0)) || ((d_idx = tree_insert(avlt, 'D')) == 0)) || ((s_idx = tree_insert(avlt, 'S')) == 0)) || ((o_idx = tree_insert(avlt, 'O')) == 0)) || ((x_idx = tree_insert(avlt, 'X')) == 0)) || ((c_idx = tree_insert(avlt, 'C')) == 0)) || ((u_idx = tree_insert(avlt, 'U')) == 0)) || ((b_idx = tree_insert(avlt, 'B')) == 0)) || ((t_idx = tree_insert(avlt, 'T')) == 0)) || (tree_delete(avlt, 'O') != 1)) || (tree_check(avlt) != 1))
  {
    fprintf(stdout, "init failed\n");
    goto err;
  }
  if (((((((((avl_successor(avlt, b) != (&c[c_idx])) || (avl_successor(avlt, c) != (&d[d_idx]))) || (avl_successor(avlt, d) != (&e[e_idx]))) || (avl_successor(avlt, e) != (&r[r_idx]))) || (avl_successor(avlt, r) != (&s[s_idx]))) || (avl_successor(avlt, s) != (&t[t_idx]))) || (avl_successor(avlt, t) != (&u[u_idx]))) || (avl_successor(avlt, u) != (&x[x_idx]))) || (avl_successor(avlt, x) != 0))
  {
    fprintf(stdout, "successor failed\n");
    goto err;
  }
  avl_destroy(avlt);
  return 1;
  err:
  avl_destroy(avlt);

  err0:
  return 0;

}


----------------------------
int unit_test_chain_insertion()
{
  avltree *avlt;
  unsigned int avlt_idx = 0;
  int i;
  int j;
  char *cases[] = {"PHXDB", "PHXDF", "PHXLJ", "PHXLN", "PHXTR", "PHXTV", "PHXbZ", "PHXbd", "PHXDLB", "PHXDLF", "PHXDLJ", "PHXDLN", "PHXTbR", "PHXTbV", "PHXTbV", "PHXTbZ", "PHXTbd", 0};
  for (i = 0; (i < ((sizeof(cases)) / (sizeof(cases[0])))) && (cases[i] != 0); i += 1)
  {
    if ((avlt_idx = tree_create()) == 0)
    {
      fprintf(stdout, "%s - create AVL tree failed\n", cases[i]);
      goto err0;
    }
    for (j = 0; j < strlen(cases[i]); j += 1)
    {
      if ((tree_insert(avlt, cases[i][j]) == 0) || (tree_check(avlt) != 1))
      {
        fprintf(stdout, "%s - insert %c failed\n", cases[i], cases[i][j]);
        goto err;
      }
    }

    avl_destroy(avlt);
  }

  return 1;
  err:
  avl_destroy(avlt);

  err0:
  return 0;

}


----------------------------
int unit_test_chain_deletion()
{
  avltree *avlt;
  unsigned int avlt_idx = 0;
  int i;
  int j;
  char *cases[] = {"PHXDLTbFJNZK", "T", "PHXDLTbFJNZdK", "T", "PHXDLTbFJNdK", "T", "PHXDLTbFRVZU", "L", "PHXDLTbBFRVZU", "L", "PHXDLTbBRVZU", "L", 0, 0};
  for (i = 0; (i < ((sizeof(cases)) / (sizeof(cases[0])))) && (cases[i] != 0); i += 2)
  {
    if ((avlt_idx = tree_create()) == 0)
    {
      fprintf(stdout, "%s-%s - create AVL tree failed\n", cases[i], cases[i + 1]);
      goto err0;
    }
    for (j = 0; j < strlen(cases[i]); j += 1)
    {
      if ((tree_insert(avlt, cases[i][j]) == 0) || (tree_check(avlt) != 1))
      {
        fprintf(stdout, "%s-%s - insert %c failed\n", cases[i], cases[i + 1], cases[i][j]);
        goto err;
      }
    }

    for (j = 0; j < strlen(cases[i + 1]); j += 1)
    {
      if ((tree_delete(avlt, cases[i + 1][j]) == 0) || (tree_check(avlt) != 1))
      {
        fprintf(stdout, "%s-%s - delete %c failed\n", cases[i], cases[i + 1], cases[i + 1][j]);
        goto err;
      }
    }

    avl_destroy(avlt);
  }

  return 1;
  err:
  avl_destroy(avlt);

  err0:
  return 0;

}


----------------------------
int unit_test_atomic_insertion()
{
  avltree *avlt;
  unsigned int avlt_idx = 0;
  int i;
  int j;
  char *cases[] = {"P", "PH", "PX", "PHDPHXDLB", "PHXDLF", "PHL", "PHXDLJ", "PHXDLN", "PXb", "PHXTbZ", "PHXTbd", "PHXT", "PHXTbRV", "PHXTbR", "PHXTbV", 0};
  for (i = 0; (i < ((sizeof(cases)) / (sizeof(cases[0])))) && cases[i]; i += 1)
  {
    if ((avlt_idx = tree_create()) == 0)
    {
      fprintf(stdout, "%s - create AVL tree failed\n", cases[i]);
      goto err0;
    }
    for (j = 0; j < strlen(cases[i]); j += 1)
    {
      if ((tree_insert(avlt, cases[i][j]) == 0) || (tree_check(avlt) != 1))
      {
        fprintf(stdout, "%s - insert %c failed\n", cases[i], cases[i][j]);
        goto err;
      }
    }

    avl_destroy(avlt);
  }

  return 1;
  err:
  avl_destroy(avlt);

  err0:
  return 0;

}


----------------------------
int unit_test_find()
{
  avltree *avlt;
  unsigned int avlt_idx = 0;
  avlnode *r;
  unsigned int r_idx = 0;
  avlnode *e;
  unsigned int e_idx = 0;
  avlnode *d;
  unsigned int d_idx = 0;
  avlnode *s;
  unsigned int s_idx = 0;
  avlnode *o;
  unsigned int o_idx = 0;
  avlnode *x;
  unsigned int x_idx = 0;
  avlnode *c;
  unsigned int c_idx = 0;
  avlnode *u;
  unsigned int u_idx = 0;
  avlnode *b;
  unsigned int b_idx = 0;
  avlnode *t;
  unsigned int t_idx = 0;
  if ((avlt_idx = tree_create()) == 0)
  {
    fprintf(stdout, "create AVL tree failed\n");
    goto err0;
  }
  if ((((((((((((r_idx = tree_insert(avlt, 'R')) == 0) || ((e_idx = tree_insert(avlt, 'E')) == 0)) || ((d_idx = tree_insert(avlt, 'D')) == 0)) || ((s_idx = tree_insert(avlt, 'S')) == 0)) || ((o_idx = tree_insert(avlt, 'O')) == 0)) || ((x_idx = tree_insert(avlt, 'X')) == 0)) || ((c_idx = tree_insert(avlt, 'C')) == 0)) || ((u_idx = tree_insert(avlt, 'U')) == 0)) || ((b_idx = tree_insert(avlt, 'B')) == 0)) || ((t_idx = tree_insert(avlt, 'T')) == 0)) || (tree_check(avlt) != 1))
  {
    fprintf(stdout, "init failed\n");
    goto err;
  }
  if ((((((((((avl_find(avlt, r->data) != (&r[r_idx])) || (avl_find(avlt, e->data) != (&e[e_idx]))) || (avl_find(avlt, d->data) != (&d[d_idx]))) || (avl_find(avlt, s->data) != (&s[s_idx]))) || (avl_find(avlt, o->data) != (&o[o_idx]))) || (avl_find(avlt, x->data) != (&x[x_idx]))) || (avl_find(avlt, c->data) != (&c[c_idx]))) || (avl_find(avlt, u->data) != (&u[u_idx]))) || (avl_find(avlt, b->data) != (&b[b_idx]))) || (avl_find(avlt, t->data) != (&t[t_idx])))
  {
    fprintf(stdout, "find failed\n");
    goto err;
  }
  avl_destroy(avlt);
  return 1;
  err:
  avl_destroy(avlt);

  err0:
  return 0;

}


----------------------------
***/


int main(int argc, char **argv)
{
  all_tests();
  if (mu_fails)
  {
    printf("*** %d/%d TESTS FAILED ***\n", mu_fails, mu_tests);
    return 1;
  }
  else
  {
    printf("ALL TESTS PASSED\n");
    return 0;
  }
}


/*** DEPENDENCIES:
extern int mu_fails
----------------------------
void all_tests()
{
  do
  {
    mu_tests += 1;
    printf("#%03d %s \n", mu_tests, "unit_test_create");
    if (unit_test_create())
    {
      printf("PASSED\n");
    }
    else
    {
      printf("FAILED\n");
      mu_fails++;
    }
  }
  while (0);
  do
  {
    mu_tests += 1;
    printf("#%03d %s \n", mu_tests, "unit_test_find");
    if (unit_test_find())
    {
      printf("PASSED\n");
    }
    else
    {
      printf("FAILED\n");
      mu_fails++;
    }
  }
  while (0);
  do
  {
    mu_tests += 1;
    printf("#%03d %s \n", mu_tests, "unit_test_successor");
    if (unit_test_successor())
    {
      printf("PASSED\n");
    }
    else
    {
      printf("FAILED\n");
      mu_fails++;
    }
  }
  while (0);
  do
  {
    mu_tests += 1;
    printf("#%03d %s \n", mu_tests, "unit_test_atomic_insertion");
    if (unit_test_atomic_insertion())
    {
      printf("PASSED\n");
    }
    else
    {
      printf("FAILED\n");
      mu_fails++;
    }
  }
  while (0);
  do
  {
    mu_tests += 1;
    printf("#%03d %s \n", mu_tests, "unit_test_atomic_deletion");
    if (unit_test_atomic_deletion())
    {
      printf("PASSED\n");
    }
    else
    {
      printf("FAILED\n");
      mu_fails++;
    }
  }
  while (0);
  do
  {
    mu_tests += 1;
    printf("#%03d %s \n", mu_tests, "unit_test_chain_insertion");
    if (unit_test_chain_insertion())
    {
      printf("PASSED\n");
    }
    else
    {
      printf("FAILED\n");
      mu_fails++;
    }
  }
  while (0);
  do
  {
    mu_tests += 1;
    printf("#%03d %s \n", mu_tests, "unit_test_chain_deletion");
    if (unit_test_chain_deletion())
    {
      printf("PASSED\n");
    }
    else
    {
      printf("FAILED\n");
      mu_fails++;
    }
  }
  while (0);
  do
  {
    mu_tests += 1;
    printf("#%03d %s \n", mu_tests, "unit_test_permutation_insertion");
    if (unit_test_permutation_insertion())
    {
      printf("PASSED\n");
    }
    else
    {
      printf("FAILED\n");
      mu_fails++;
    }
  }
  while (0);
  do
  {
    mu_tests += 1;
    printf("#%03d %s \n", mu_tests, "unit_test_permutation_deletion");
    if (unit_test_permutation_deletion())
    {
      printf("PASSED\n");
    }
    else
    {
      printf("FAILED\n");
      mu_fails++;
    }
  }
  while (0);
  do
  {
    mu_tests += 1;
    printf("#%03d %s \n", mu_tests, "unit_test_random_insertion_deletion");
    if (unit_test_random_insertion_deletion())
    {
      printf("PASSED\n");
    }
    else
    {
      printf("FAILED\n");
      mu_fails++;
    }
  }
  while (0);
  do
  {
    mu_tests += 1;
    printf("#%03d %s \n", mu_tests, "unit_test_dup");
    if (unit_test_dup())
    {
      printf("PASSED\n");
    }
    else
    {
      printf("FAILED\n");
      mu_fails++;
    }
  }
  while (0);
  do
  {
    mu_tests += 1;
    printf("#%03d %s \n", mu_tests, "unit_test_min");
    if (unit_test_min())
    {
      printf("PASSED\n");
    }
    else
    {
      printf("FAILED\n");
      mu_fails++;
    }
  }
  while (0);
}


----------------------------
extern int mu_tests
----------------------------
***/


