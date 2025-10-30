// element in merge of:  args,args_tree,args_entry
struct args
{
  struct args_tree tree;
  int argc;
  char **argv;
}
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  args,args_tree,args_entry
struct args_tree
{
  struct args_entry *rbh_root;
}
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  args,args_tree,args_entry
struct args_entry
{
  u_char flag;
  char *value;
  struct 
  {
    struct args_entry *rbe_left;
    struct args_entry *rbe_right;
    struct args_entry *rbe_parent;
    int rbe_color;
  } entry;
}
/*** DEPENDENCIES:
None
----------------------------
***/


