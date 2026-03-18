#include <avl_bf.h>
#include <avl_data.h>
#include <avl_example.c>
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
typedef struct 
{
  int key;
} mydata;
mydata *makedata(int key);
int compare_func(const void *d1, const void *d2);
void destroy_func(void *d);
void print_func(void *d);
void print_char_func(void *d);
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

