struct lh_table
{
  int size;
  int count;
  struct lh_entry *head;
  struct lh_entry *tail;
  struct lh_entry *table;
  lh_entry_free_fn *free_fn;
  lh_hash_fn *hash_fn;
  lh_equal_fn *equal_fn;
}
/*** DEPENDENCIES:
typedef void lh_entry_free_fn(struct lh_entry *e)
----------------------------
typedef unsigned long lh_hash_fn(const void *k)
----------------------------
struct lh_entry
{
  const void *k;
  int k_is_constant;
  const void *v;
  struct lh_entry *next;
  struct lh_entry *prev;
}
----------------------------
typedef int lh_equal_fn(const void *k1, const void *k2)
----------------------------
***/


