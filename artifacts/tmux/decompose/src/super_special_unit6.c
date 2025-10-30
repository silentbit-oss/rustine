// element in merge of:  mode_tree_list,mode_tree_item
struct mode_tree_list
{
  struct mode_tree_item *tqh_first;
  struct mode_tree_item **tqh_last;
}
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  mode_tree_list,mode_tree_item
struct mode_tree_item
{
  struct mode_tree_item *parent;
  void *itemdata;
  u_int line;
  uint64_t tag;
  const char *name;
  const char *text;
  int expanded;
  int tagged;
  struct mode_tree_list children;
  struct 
  {
    struct mode_tree_item *tqe_next;
    struct mode_tree_item **tqe_prev;
  } entry;
}
/*** DEPENDENCIES:
None
----------------------------
***/


