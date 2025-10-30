struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
/*** DEPENDENCIES:
typedef void (*format_cb)(struct format_tree *, struct format_entry *)
----------------------------
***/


