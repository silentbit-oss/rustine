struct json_object_iter
{
  char *key;
  struct json_object *val;
  struct lh_entry *entry;
}
/*** DEPENDENCIES:
struct lh_entry
{
  const void *k;
  int k_is_constant;
  const void *v;
  struct lh_entry *next;
  struct lh_entry *prev;
}
----------------------------
None
----------------------------
***/


