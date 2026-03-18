int main(int argc, char *argv[])
{
  avltree *avlt;
  unsigned int avlt_idx = 0;
  if ((avlt_idx = avl_create(compare_func, destroy_func)) == 0)
  {
    fprintf(stderr, "create AVL tree failed\n");
    return 1;
  }
  char a[] = {'R', 'E', 'D', 'S', 'O', 'X', 'C', 'U', 'B', 'T'};
  int i;
  mydata *data;
  unsigned int data_idx = 0;
  for (i = 0; i < ((sizeof(a)) / (sizeof(a[0]))); i += 1)
  {
    if (((data_idx = makedata(a[i])) == 0) || (avl_insert(avlt, data) == 0))
    {
      fprintf(stderr, "insert %c: out of memory\n", a[i]);
      free(data);
      break;
    }
    printf("insert %c", a[i]);
    avl_print(avlt, print_char_func);
    printf("\n");
  }

  avlnode *node;
  unsigned int node_idx = 0;
  mydata query;
  query.key = 'O';
  printf("delete %c", query.key);
  if ((node_idx = avl_find(avlt, &query)) != 0)
  {
    avl_delete(avlt, node, 0);
  }
  avl_print(avlt, print_char_func);
  while (node_idx = avlt->min)
  {
    printf("\ndelete ");
    print_char_func(node->data);
    avl_delete(avlt, node, 0);
    avl_print(avlt, print_char_func);
  }

  avl_destroy(avlt);
  return 0;
}


/*** DEPENDENCIES:
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
typedef struct 
{
  int key;
} mydata
----------------------------
void avl_destroy(avltree *avlt)
{
  destroy(avlt, avlt->root.left);
  free(avlt);
}


----------------------------
void print_char_func(void *d)
{
  mydata *p;
  unsigned int p_idx = 0;
  assert(d != 0);
  p_idx = (mydata *) d;
  printf("%c", p->key & 127);
}


----------------------------
void avl_print(avltree *avlt, void (*print_func)(void *))
{
  printf("\n--\n");
  print(avlt, avlt->root.left, print_func, 0, "T");
  printf("\nheight = %d\n", check_height(avlt, avlt->root.left));
}


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


