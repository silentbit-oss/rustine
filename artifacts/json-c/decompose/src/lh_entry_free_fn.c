typedef void lh_entry_free_fn(struct lh_entry *e)
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
***/


