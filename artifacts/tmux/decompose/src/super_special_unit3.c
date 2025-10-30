// element in merge of:  environ,environ_entry
struct environ
{
  struct environ_entry *rbh_root;
}
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  environ,environ_entry
struct environ_entry
{
  char *name;
  char *value;
  struct 
  {
    struct environ_entry *rbe_left;
    struct environ_entry *rbe_right;
    struct environ_entry *rbe_parent;
    int rbe_color;
  } entry;
}
/*** DEPENDENCIES:
None
----------------------------
***/


