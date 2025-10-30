#include <avl_bf.c>
#include <avl_bf.h>
#include <stdio.h>
#include <stdlib.h>

enum avlbf
{
  LEFTHEAVY = -1,
  BALANCED = 0,
  RIGHTHEAVY = 1
};
enum avltraversal
{
  PREORDER,
  INORDER,
  POSTORDER
};
typedef struct avlnode
{
  struct avlnode *left;
  struct avlnode *right;
  struct avlnode *parent;
  char bf;
  void *data;
} avlnode;
typedef struct 
{
  int (*compare)(const void *, const void *);
  void (*print)(void *);
  void (*destroy)(void *);
  avlnode root;
  avlnode nil;
  avlnode *min;
} avltree;
avltree *avl_create(int (*compare_func)(const void *, const void *), void (*destroy_func)(void *));
void avl_destroy(avltree *avlt);
avlnode *avl_find(avltree *avlt, void *data);
avlnode *avl_successor(avltree *avlt, avlnode *node);
int avl_apply(avltree *avlt, avlnode *node, int (*func)(void *, void *), void *cookie, enum avltraversal order);
void avl_print(avltree *avlt, void (*print_func)(void *));
avlnode *avl_insert(avltree *avlt, void *data);
void *avl_delete(avltree *avlt, avlnode *node, int keep);
int avl_check_order(avltree *avlt, void *min, void *max);
int avl_check_height(avltree *avlt);
static avlnode *rotate_left(avltree *avlt, avlnode *x);
static avlnode *rotate_right(avltree *avlt, avlnode *x);
static avlnode *fix_insert_leftimbalance(avltree *avlt, avlnode *p);
static avlnode *fix_insert_rightimbalance(avltree *avlt, avlnode *p);
static avlnode *fix_delete_leftimbalance(avltree *avlt, avlnode *p);
static avlnode *fix_delete_rightimbalance(avltree *avlt, avlnode *p);
static int check_order(avltree *avlt, avlnode *n, void *min, void *max);
static int check_height(avltree *avlt, avlnode *n);
static void print(avltree *avlt, avlnode *n, void (*print_func)(void *), int depth, char *label);
static void destroy(avltree *avlt, avlnode *n);
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

void avl_destroy(avltree *avlt)
{
  destroy(avlt, avlt->root.left);
  free(avlt);
}

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

avlnode *avl_successor(avltree *avlt, avlnode *node)
{
  unsigned int node_idx = 0;
  avlnode *p;
  unsigned int p_idx = 0;
  p_idx = node->right;
  if ((&p[p_idx]) != (&avlt->nil))
  {
    for (; p->left != (&avlt->nil); p_idx = p_idx->left)
    {
      ;
    }

  }
  else
  {
    for (p_idx = node->parent; (&node[node_idx]) == p->right; node_idx = &p[p_idx], p_idx = p_idx->parent)
    {
      ;
    }

    if ((&p[p_idx]) == (&avlt->root))
    {
      p_idx = 0;
    }
  }
  return p;
}

int avl_apply(avltree *avlt, avlnode *node, int (*func)(void *, void *), void *cookie, enum avltraversal order)
{
  int err;
  if (node != (&avlt->nil))
  {
    if ((order == PREORDER) && ((err = func(node->data, cookie)) != 0))
    {
      return err;
    }
    if ((err = avl_apply(avlt, node->left, func, cookie, order)) != 0)
    {
      return err;
    }
    if ((order == INORDER) && ((err = func(node->data, cookie)) != 0))
    {
      return err;
    }
    if ((err = avl_apply(avlt, node->right, func, cookie, order)) != 0)
    {
      return err;
    }
    if ((order == POSTORDER) && ((err = func(node->data, cookie)) != 0))
    {
      return err;
    }
  }
  return 0;
}

void avl_print(avltree *avlt, void (*print_func)(void *))
{
  printf("\n--\n");
  print(avlt, avlt->root.left, print_func, 0, "T");
  printf("\nheight = %d\n", check_height(avlt, avlt->root.left));
}

int avl_check_order(avltree *avlt, void *min, void *max)
{
  return check_order(avlt, avlt->root.left, min, max);
}

int avl_check_height(avltree *avlt)
{
  int height;
  height = check_height(avlt, avlt->root.left);
  return (height < 0) ? (0) : (1);
}

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
    helper_avl_insert_1(&current_idx, &parent_idx, avlt, current, parent);
  }

  return new_node;
}

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

avlnode *rotate_left(avltree *avlt, avlnode *x)
{
  avlnode *y;
  unsigned int y_idx = 0;
  y_idx = x->right;
  x->right = y->left;
  if (x->right != (&avlt->nil))
  {
    x->right->parent = x;
  }
  y->parent = x->parent;
  if (x == x->parent->left)
  {
    x->parent->left = &y[y_idx];
  }
  else
    x->parent->right = &y[y_idx];
  y->left = x;
  x->parent = &y[y_idx];
  return y;
}

avlnode *rotate_right(avltree *avlt, avlnode *x)
{
  avlnode *y;
  unsigned int y_idx = 0;
  y_idx = x->left;
  x->left = y->right;
  if (x->left != (&avlt->nil))
  {
    x->left->parent = x;
  }
  y->parent = x->parent;
  if (x == x->parent->left)
  {
    x->parent->left = &y[y_idx];
  }
  else
    x->parent->right = &y[y_idx];
  y->right = x;
  x->parent = &y[y_idx];
  return y;
}

avlnode *fix_insert_leftimbalance(avltree *avlt, avlnode *p)
{
  unsigned int p_idx = 0;
  if (p->left->bf == p->bf)
  {
    p_idx = rotate_right(avlt, p_idx);
    p->bf = (p->right->bf = 0);
  }
  else
  {
    int oldbf;
    oldbf = p->left->right->bf;
    rotate_left(avlt, p->left);
    p_idx = rotate_right(avlt, p_idx);
    p->bf = 0;
    if (oldbf == (-1))
    {
      p->left->bf = 0;
      p->right->bf = 1;
    }
    else
      if (oldbf == 1)
    {
      p->left->bf = -1;
      p->right->bf = 0;
    }
    else
      if (oldbf == 0)
    {
      p->left->bf = (p->right->bf = 0);
    }
  }
  return p;
}

avlnode *fix_insert_rightimbalance(avltree *avlt, avlnode *p)
{
  unsigned int p_idx = 0;
  if (p->right->bf == p->bf)
  {
    p_idx = rotate_left(avlt, p_idx);
    p->bf = (p->left->bf = 0);
  }
  else
  {
    int oldbf;
    oldbf = p->right->left->bf;
    rotate_right(avlt, p->right);
    p_idx = rotate_left(avlt, p_idx);
    p->bf = 0;
    if (oldbf == (-1))
    {
      p->left->bf = 0;
      p->right->bf = 1;
    }
    else
      if (oldbf == 1)
    {
      p->left->bf = -1;
      p->right->bf = 0;
    }
    else
      if (oldbf == 0)
    {
      p->left->bf = (p->right->bf = 0);
    }
  }
  return p;
}

avlnode *fix_delete_leftimbalance(avltree *avlt, avlnode *p)
{
  unsigned int p_idx = 0;
  if (p->left->bf == (-1))
  {
    p_idx = rotate_right(avlt, p_idx);
    p->bf = (p->right->bf = 0);
  }
  else
    if (p->left->bf == 0)
  {
    p_idx = rotate_right(avlt, p_idx);
    p->bf = 1;
    p->right->bf = -1;
  }
  else
    if (p->left->bf == 1)
  {
    int oldbf;
    oldbf = p->left->right->bf;
    rotate_left(avlt, p->left);
    p_idx = rotate_right(avlt, p_idx);
    p->bf = 0;
    if (oldbf == (-1))
    {
      p->left->bf = 0;
      p->right->bf = 1;
    }
    else
      if (oldbf == 1)
    {
      p->left->bf = -1;
      p->right->bf = 0;
    }
    else
      if (oldbf == 0)
    {
      p->left->bf = (p->right->bf = 0);
    }
  }
  return p;
}

avlnode *fix_delete_rightimbalance(avltree *avlt, avlnode *p)
{
  unsigned int p_idx = 0;
  if (p->right->bf == 1)
  {
    p_idx = rotate_left(avlt, p_idx);
    p->bf = (p->left->bf = 0);
  }
  else
    if (p->right->bf == 0)
  {
    p_idx = rotate_left(avlt, p_idx);
    p->bf = -1;
    p->left->bf = 1;
  }
  else
    if (p->right->bf == (-1))
  {
    int oldbf;
    oldbf = p->right->left->bf;
    rotate_right(avlt, p->right);
    p_idx = rotate_left(avlt, p_idx);
    p->bf = 0;
    if (oldbf == (-1))
    {
      p->left->bf = 0;
      p->right->bf = 1;
    }
    else
      if (oldbf == 1)
    {
      p->left->bf = -1;
      p->right->bf = 0;
    }
    else
      if (oldbf == 0)
    {
      p->left->bf = (p->right->bf = 0);
    }
  }
  return p;
}

int check_order(avltree *avlt, avlnode *n, void *min, void *max)
{
  if (n == (&avlt->nil))
  {
    return 1;
  }
  if ((avlt->compare(n->data, min) < 0) || (avlt->compare(n->data, max) > 0))
  {
    return 0;
  }
  return check_order(avlt, n->left, min, n->data) && check_order(avlt, n->right, n->data, max);
}

int check_height(avltree *avlt, avlnode *n)
{
  int lh;
  int rh;
  int cmp;
  if (n == (&avlt->nil))
  {
    return 0;
  }
  lh = check_height(avlt, n->left);
  if (lh < 0)
  {
    return lh;
  }
  rh = check_height(avlt, n->right);
  if (rh < 0)
  {
    return rh;
  }
  cmp = rh - lh;
  if (((cmp < (-1)) || (cmp > 1)) || (cmp != n->bf))
  {
    return -1;
  }
  return 1 + ((lh > rh) ? (lh) : (rh));
}

void print(avltree *avlt, avlnode *n, void (*print_func)(void *), int depth, char *label)
{
  if (n != (&avlt->nil))
  {
    print(avlt, n->right, print_func, depth + 1, "R");
    printf("%*s", 8 * depth, "");
    if (label)
    {
      printf("%s: ", label);
    }
    print_func(n->data);
    printf(" (%s%d)\n", (n->bf >= 0) ? ("+") : (""), n->bf);
    print(avlt, n->left, print_func, depth + 1, "L");
  }
}

void destroy(avltree *avlt, avlnode *n)
{
  if (n != (&avlt->nil))
  {
    destroy(avlt, n->left);
    destroy(avlt, n->right);
    avlt->destroy(n->data);
    free(n);
  }
}


enum avlbf
{
  LEFTHEAVY = -1,
  BALANCED = 0,
  RIGHTHEAVY = 1
};
enum avltraversal
{
  PREORDER,
  INORDER,
  POSTORDER
};
typedef struct avlnode
{
  struct avlnode *left;
  struct avlnode *right;
  struct avlnode *parent;
  char bf;
  void *data;
} avlnode;
typedef struct 
{
  int (*compare)(const void *, const void *);
  void (*print)(void *);
  void (*destroy)(void *);
  avlnode root;
  avlnode nil;
  avlnode *min;
} avltree;
avltree *avl_create(int (*compare_func)(const void *, const void *), void (*destroy_func)(void *));
void avl_destroy(avltree *avlt);
avlnode *avl_find(avltree *avlt, void *data);
avlnode *avl_successor(avltree *avlt, avlnode *node);
int avl_apply(avltree *avlt, avlnode *node, int (*func)(void *, void *), void *cookie, enum avltraversal order);
void avl_print(avltree *avlt, void (*print_func)(void *));
avlnode *avl_insert(avltree *avlt, void *data);
void *avl_delete(avltree *avlt, avlnode *node, int keep);
int avl_check_order(avltree *avlt, void *min, void *max);
int avl_check_height(avltree *avlt);
static avlnode *rotate_left(avltree *avlt, avlnode *x);
static avlnode *rotate_right(avltree *avlt, avlnode *x);
static avlnode *fix_insert_leftimbalance(avltree *avlt, avlnode *p);
static avlnode *fix_insert_rightimbalance(avltree *avlt, avlnode *p);
static avlnode *fix_delete_leftimbalance(avltree *avlt, avlnode *p);
static avlnode *fix_delete_rightimbalance(avltree *avlt, avlnode *p);
static int check_order(avltree *avlt, avlnode *n, void *min, void *max);
static int check_height(avltree *avlt, avlnode *n);
static void print(avltree *avlt, avlnode *n, void (*print_func)(void *), int depth, char *label);
static void destroy(avltree *avlt, avlnode *n);
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

void avl_destroy(avltree *avlt)
{
  destroy(avlt, avlt->root.left);
  free(avlt);
}

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

avlnode *avl_successor(avltree *avlt, avlnode *node)
{
  unsigned int node_idx = 0;
  avlnode *p;
  unsigned int p_idx = 0;
  p_idx = node->right;
  if ((&p[p_idx]) != (&avlt->nil))
  {
    for (; p->left != (&avlt->nil); p_idx = p_idx->left)
    {
      ;
    }

  }
  else
  {
    for (p_idx = node->parent; (&node[node_idx]) == p->right; node_idx = &p[p_idx], p_idx = p_idx->parent)
    {
      ;
    }

    if ((&p[p_idx]) == (&avlt->root))
    {
      p_idx = 0;
    }
  }
  return p;
}

int avl_apply(avltree *avlt, avlnode *node, int (*func)(void *, void *), void *cookie, enum avltraversal order)
{
  int err;
  if (node != (&avlt->nil))
  {
    if ((order == PREORDER) && ((err = func(node->data, cookie)) != 0))
    {
      return err;
    }
    if ((err = avl_apply(avlt, node->left, func, cookie, order)) != 0)
    {
      return err;
    }
    if ((order == INORDER) && ((err = func(node->data, cookie)) != 0))
    {
      return err;
    }
    if ((err = avl_apply(avlt, node->right, func, cookie, order)) != 0)
    {
      return err;
    }
    if ((order == POSTORDER) && ((err = func(node->data, cookie)) != 0))
    {
      return err;
    }
  }
  return 0;
}

void avl_print(avltree *avlt, void (*print_func)(void *))
{
  printf("\n--\n");
  print(avlt, avlt->root.left, print_func, 0, "T");
  printf("\nheight = %d\n", check_height(avlt, avlt->root.left));
}

int avl_check_order(avltree *avlt, void *min, void *max)
{
  return check_order(avlt, avlt->root.left, min, max);
}

int avl_check_height(avltree *avlt)
{
  int height;
  height = check_height(avlt, avlt->root.left);
  return (height < 0) ? (0) : (1);
}

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
    if ((&current[current_idx]) == parent->left)
    {
      if (parent->bf == (-1))
      {
        parent->bf = 0;
      }
      else
        if (parent->bf == 0)
      {
        parent->bf = 1;
        break;
      }
      else
        if (parent->bf == 1)
      {
        parent_idx = fix_delete_rightimbalance(avlt, parent_idx);
        if (parent->bf == (-1))
        {
          break;
        }
      }
    }
    else
    {
      if (parent->bf == 1)
      {
        parent->bf = 0;
      }
      else
        if (parent->bf == 0)
      {
        parent->bf = -1;
        break;
      }
      else
        if (parent->bf == (-1))
      {
        parent_idx = fix_delete_leftimbalance(avlt, parent_idx);
        if (parent->bf == 1)
        {
          break;
        }
      }
    }
    current_idx = &parent[parent_idx];
    parent_idx = current->parent_idx;
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

avlnode *rotate_left(avltree *avlt, avlnode *x)
{
  avlnode *y;
  unsigned int y_idx = 0;
  y_idx = x->right;
  x->right = y->left;
  if (x->right != (&avlt->nil))
  {
    x->right->parent = x;
  }
  y->parent = x->parent;
  if (x == x->parent->left)
  {
    x->parent->left = &y[y_idx];
  }
  else
    x->parent->right = &y[y_idx];
  y->left = x;
  x->parent = &y[y_idx];
  return y;
}

avlnode *rotate_right(avltree *avlt, avlnode *x)
{
  avlnode *y;
  unsigned int y_idx = 0;
  y_idx = x->left;
  x->left = y->right;
  if (x->left != (&avlt->nil))
  {
    x->left->parent = x;
  }
  y->parent = x->parent;
  if (x == x->parent->left)
  {
    x->parent->left = &y[y_idx];
  }
  else
    x->parent->right = &y[y_idx];
  y->right = x;
  x->parent = &y[y_idx];
  return y;
}

avlnode *fix_insert_leftimbalance(avltree *avlt, avlnode *p)
{
  unsigned int p_idx = 0;
  if (p->left->bf == p->bf)
  {
    p_idx = rotate_right(avlt, p_idx);
    p->bf = (p->right->bf = 0);
  }
  else
  {
    int oldbf;
    oldbf = p->left->right->bf;
    rotate_left(avlt, p->left);
    p_idx = rotate_right(avlt, p_idx);
    p->bf = 0;
    if (oldbf == (-1))
    {
      p->left->bf = 0;
      p->right->bf = 1;
    }
    else
      if (oldbf == 1)
    {
      p->left->bf = -1;
      p->right->bf = 0;
    }
    else
      if (oldbf == 0)
    {
      p->left->bf = (p->right->bf = 0);
    }
  }
  return p;
}

avlnode *fix_insert_rightimbalance(avltree *avlt, avlnode *p)
{
  unsigned int p_idx = 0;
  if (p->right->bf == p->bf)
  {
    p_idx = rotate_left(avlt, p_idx);
    p->bf = (p->left->bf = 0);
  }
  else
  {
    int oldbf;
    oldbf = p->right->left->bf;
    rotate_right(avlt, p->right);
    p_idx = rotate_left(avlt, p_idx);
    p->bf = 0;
    if (oldbf == (-1))
    {
      p->left->bf = 0;
      p->right->bf = 1;
    }
    else
      if (oldbf == 1)
    {
      p->left->bf = -1;
      p->right->bf = 0;
    }
    else
      if (oldbf == 0)
    {
      p->left->bf = (p->right->bf = 0);
    }
  }
  return p;
}

avlnode *fix_delete_leftimbalance(avltree *avlt, avlnode *p)
{
  unsigned int p_idx = 0;
  if (p->left->bf == (-1))
  {
    p_idx = rotate_right(avlt, p_idx);
    p->bf = (p->right->bf = 0);
  }
  else
    if (p->left->bf == 0)
  {
    p_idx = rotate_right(avlt, p_idx);
    p->bf = 1;
    p->right->bf = -1;
  }
  else
    if (p->left->bf == 1)
  {
    int oldbf;
    oldbf = p->left->right->bf;
    rotate_left(avlt, p->left);
    p_idx = rotate_right(avlt, p_idx);
    p->bf = 0;
    if (oldbf == (-1))
    {
      p->left->bf = 0;
      p->right->bf = 1;
    }
    else
      if (oldbf == 1)
    {
      p->left->bf = -1;
      p->right->bf = 0;
    }
    else
      if (oldbf == 0)
    {
      p->left->bf = (p->right->bf = 0);
    }
  }
  return p;
}

avlnode *fix_delete_rightimbalance(avltree *avlt, avlnode *p)
{
  unsigned int p_idx = 0;
  if (p->right->bf == 1)
  {
    p_idx = rotate_left(avlt, p_idx);
    p->bf = (p->left->bf = 0);
  }
  else
    if (p->right->bf == 0)
  {
    p_idx = rotate_left(avlt, p_idx);
    p->bf = -1;
    p->left->bf = 1;
  }
  else
    if (p->right->bf == (-1))
  {
    int oldbf;
    oldbf = p->right->left->bf;
    rotate_right(avlt, p->right);
    p_idx = rotate_left(avlt, p_idx);
    p->bf = 0;
    if (oldbf == (-1))
    {
      p->left->bf = 0;
      p->right->bf = 1;
    }
    else
      if (oldbf == 1)
    {
      p->left->bf = -1;
      p->right->bf = 0;
    }
    else
      if (oldbf == 0)
    {
      p->left->bf = (p->right->bf = 0);
    }
  }
  return p;
}

int check_order(avltree *avlt, avlnode *n, void *min, void *max)
{
  if (n == (&avlt->nil))
  {
    return 1;
  }
  if ((avlt->compare(n->data, min) < 0) || (avlt->compare(n->data, max) > 0))
  {
    return 0;
  }
  return check_order(avlt, n->left, min, n->data) && check_order(avlt, n->right, n->data, max);
}

int check_height(avltree *avlt, avlnode *n)
{
  int lh;
  int rh;
  int cmp;
  if (n == (&avlt->nil))
  {
    return 0;
  }
  lh = check_height(avlt, n->left);
  if (lh < 0)
  {
    return lh;
  }
  rh = check_height(avlt, n->right);
  if (rh < 0)
  {
    return rh;
  }
  cmp = rh - lh;
  if (((cmp < (-1)) || (cmp > 1)) || (cmp != n->bf))
  {
    return -1;
  }
  return 1 + ((lh > rh) ? (lh) : (rh));
}

void print(avltree *avlt, avlnode *n, void (*print_func)(void *), int depth, char *label)
{
  if (n != (&avlt->nil))
  {
    print(avlt, n->right, print_func, depth + 1, "R");
    printf("%*s", 8 * depth, "");
    if (label)
    {
      printf("%s: ", label);
    }
    print_func(n->data);
    printf(" (%s%d)\n", (n->bf >= 0) ? ("+") : (""), n->bf);
    print(avlt, n->left, print_func, depth + 1, "L");
  }
}

void destroy(avltree *avlt, avlnode *n)
{
  if (n != (&avlt->nil))
  {
    destroy(avlt, n->left);
    destroy(avlt, n->right);
    avlt->destroy(n->data);
    free(n);
  }
}

void helper_avl_insert_1(unsigned int * const current_idx_ref, unsigned int * const parent_idx_ref, avltree * const avlt, avlnode * const current, avlnode * const parent)
{
  unsigned int current_idx = *current_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
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
  *current_idx_ref = current_idx;
  *parent_idx_ref = parent_idx;
}

void helper_avl_delete_1(unsigned int * const current_idx_ref, unsigned int * const parent_idx_ref, avltree * const avlt, avlnode * const current, avlnode * const parent)
{
  unsigned int current_idx = *current_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  if ((&current[current_idx]) == parent->left)
  {
    if (parent->bf == (-1))
    {
      parent->bf = 0;
    }
    else
      if (parent->bf == 0)
    {
      parent->bf = 1;
      break;
    }
    else
      if (parent->bf == 1)
    {
      parent_idx = fix_delete_rightimbalance(avlt, parent_idx);
      if (parent->bf == (-1))
      {
        break;
      }
    }
  }
  else
  {
    if (parent->bf == 1)
    {
      parent->bf = 0;
    }
    else
      if (parent->bf == 0)
    {
      parent->bf = -1;
      break;
    }
    else
      if (parent->bf == (-1))
    {
      parent_idx = fix_delete_leftimbalance(avlt, parent_idx);
      if (parent->bf == 1)
      {
        break;
      }
    }
  }
  current_idx = &parent[parent_idx];
  parent_idx = current->parent_idx;
  *current_idx_ref = current_idx;
  *parent_idx_ref = parent_idx;
}

