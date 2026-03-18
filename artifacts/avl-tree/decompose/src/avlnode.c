typedef struct avlnode
{
  struct avlnode *left;
  struct avlnode *right;
  struct avlnode *parent;
  char bf;
  void *data;
} avlnode
/*** DEPENDENCIES:
***/


