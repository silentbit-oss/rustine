#include <avl_bf.h>
#include <avl_data.h>
#include <avl_test.c>
#include <limits.h>
#include <minunit.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
typedef struct 
{
  int key;
} mydata;
mydata *makedata(int key);
int compare_func(const void *d1, const void *d2);
void destroy_func(void *d);
void print_func(void *d);
void print_char_func(void *d);
extern int mu_tests;
extern int mu_fails;
int mu_tests = 0;
int mu_fails = 0;
int permutation_error = 0;
static avltree *tree_create();
static avlnode *tree_find(avltree *avlt, int key);
static void tree_print(avltree *avlt);
static int tree_check(avltree *avlt);
static avlnode *tree_insert(avltree *avlt, int key);
static int tree_delete(avltree *avlt, int key);
static void swap(char *x, char *y);
static void permute(char *a, int start, int end, void func(char *));
static void permutation_insert(char *a);
static void permutation_delete(char *a);
static int unit_test_create();
static int unit_test_find();
static int unit_test_successor();
static int unit_test_atomic_insertion();
static int unit_test_atomic_deletion();
static int unit_test_chain_insertion();
static int unit_test_chain_deletion();
static int unit_test_permutation_insertion();
static int unit_test_permutation_deletion();
static int unit_test_random_insertion_deletion();
static int unit_test_dup();
static int unit_test_min();
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
      mu_fails += 1;
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
      mu_fails += 1;
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
      mu_fails += 1;
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
      mu_fails += 1;
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
      mu_fails += 1;
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
      mu_fails += 1;
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
      mu_fails += 1;
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
      mu_fails += 1;
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
      mu_fails += 1;
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
      mu_fails += 1;
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
      mu_fails += 1;
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
      mu_fails += 1;
    }
  }
  while (0);
}

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

avltree *tree_create()
{
  return avl_create(compare_func, destroy_func);
}

avlnode *tree_find(avltree *avlt, int key)
{
  mydata query;
  query.key = key;
  return avl_find(avlt, &query);
}

void tree_print(avltree *avlt)
{
  avl_print(avlt, print_func);
}

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

void swap(char *x, char *y)
{
  char temp;
  temp = *x;
  *x = *y;
  *y = temp;
}

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

int unit_test_permutation_insertion()
{
  char a[] = "ABCDEFGHIJ";
  permutation_error = 0;
  permute(a, 0, strlen(a) - 1, permutation_insert);
  return permutation_error == 0;
}

int unit_test_permutation_deletion()
{
  char a[] = "ABCDEFGHIJ";
  permutation_error = 0;
  permute(a, 0, strlen(a) - 1, permutation_delete);
  return permutation_error == 0;
}

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
typedef struct 
{
  int key;
} mydata;
mydata *makedata(int key);
int compare_func(const void *d1, const void *d2);
void destroy_func(void *d);
void print_func(void *d);
void print_char_func(void *d);
extern int mu_tests;
extern int mu_fails;
int mu_tests = 0;
int mu_fails = 0;
int permutation_error = 0;
static avltree *tree_create();
static avlnode *tree_find(avltree *avlt, int key);
static void tree_print(avltree *avlt);
static int tree_check(avltree *avlt);
static avlnode *tree_insert(avltree *avlt, int key);
static int tree_delete(avltree *avlt, int key);
static void swap(char *x, char *y);
static void permute(char *a, int start, int end, void func(char *));
static void permutation_insert(char *a);
static void permutation_delete(char *a);
static int unit_test_create();
static int unit_test_find();
static int unit_test_successor();
static int unit_test_atomic_insertion();
static int unit_test_atomic_deletion();
static int unit_test_chain_insertion();
static int unit_test_chain_deletion();
static int unit_test_permutation_insertion();
static int unit_test_permutation_deletion();
static int unit_test_random_insertion_deletion();
static int unit_test_dup();
static int unit_test_min();
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
      mu_fails += 1;
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
      mu_fails += 1;
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
      mu_fails += 1;
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
      mu_fails += 1;
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
      mu_fails += 1;
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
      mu_fails += 1;
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
      mu_fails += 1;
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
      mu_fails += 1;
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
      mu_fails += 1;
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
      mu_fails += 1;
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
      mu_fails += 1;
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
      mu_fails += 1;
    }
  }
  while (0);
}

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

avltree *tree_create()
{
  return avl_create(compare_func, destroy_func);
}

avlnode *tree_find(avltree *avlt, int key)
{
  mydata query;
  query.key = key;
  return avl_find(avlt, &query);
}

void tree_print(avltree *avlt)
{
  avl_print(avlt, print_func);
}

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

void swap(char *x, char *y)
{
  char temp;
  temp = *x;
  *x = *y;
  *y = temp;
}

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

int unit_test_permutation_insertion()
{
  char a[] = "ABCDEFGHIJ";
  permutation_error = 0;
  permute(a, 0, strlen(a) - 1, permutation_insert);
  return permutation_error == 0;
}

int unit_test_permutation_deletion()
{
  char a[] = "ABCDEFGHIJ";
  permutation_error = 0;
  permute(a, 0, strlen(a) - 1, permutation_delete);
  return permutation_error == 0;
}

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

