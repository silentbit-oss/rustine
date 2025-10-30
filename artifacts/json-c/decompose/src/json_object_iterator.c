struct json_object_iterator
{
  const void *opaque_;
}
/*** DEPENDENCIES:
***/


struct json_object_iterator json_object_iter_init_default(void)
{
  struct json_object_iterator iter;
  iter.opaque_ = 0;
  return iter;
}


/*** DEPENDENCIES:
struct json_object_iter
{
  char *key;
  struct json_object *val;
  struct lh_entry *entry;
}
----------------------------
struct json_object_iterator
{
  const void *opaque_;
}
----------------------------
None
----------------------------
***/


const char *json_object_iter_peek_name(const struct json_object_iterator *iter)
{
  do
  {
  }
  while (0);
  do
  {
  }
  while (0);
  return (const char *) ((const struct lh_entry *) iter->opaque_)->k;
}


/*** DEPENDENCIES:
struct json_object_iter
{
  char *key;
  struct json_object *val;
  struct lh_entry *entry;
}
----------------------------
struct json_object_iterator
{
  const void *opaque_;
}
----------------------------
None
----------------------------
***/


json_bool json_object_iter_equal(const struct json_object_iterator *iter1, const struct json_object_iterator *iter2)
{
  do
  {
  }
  while (0);
  do
  {
  }
  while (0);
  return iter1->opaque_ == iter2->opaque_;
}


/*** DEPENDENCIES:
struct json_object_iter
{
  char *key;
  struct json_object *val;
  struct lh_entry *entry;
}
----------------------------
struct json_object_iterator
{
  const void *opaque_;
}
----------------------------
None
----------------------------
***/


struct json_object_iterator json_object_iter_end(const struct json_object *obj)
{
  struct json_object_iterator iter;
  do
  {
  }
  while (0);
  do
  {
  }
  while (0);
  iter.opaque_ = kObjectEndIterValue;
  return iter;
}


/*** DEPENDENCIES:
struct json_object_iter
{
  char *key;
  struct json_object *val;
  struct lh_entry *entry;
}
----------------------------
struct json_object_iterator
{
  const void *opaque_;
}
----------------------------
static const void *kObjectEndIterValue = 0
----------------------------
None
----------------------------
***/


void json_object_iter_next(struct json_object_iterator *iter)
{
  do
  {
  }
  while (0);
  do
  {
  }
  while (0);
  iter->opaque_ = lh_entry_next((const struct lh_entry *) iter->opaque_);
}


/*** DEPENDENCIES:
struct json_object_iter
{
  char *key;
  struct json_object *val;
  struct lh_entry *entry;
}
----------------------------
inline static struct lh_entry *lh_entry_next(const struct lh_entry *e)
{
  return e->next;
}


----------------------------
struct json_object_iterator
{
  const void *opaque_;
}
----------------------------
None
----------------------------
***/


struct json_object *json_object_iter_peek_value(const struct json_object_iterator *iter)
{
  do
  {
  }
  while (0);
  do
  {
  }
  while (0);
  return (struct json_object *) lh_entry_v((const struct lh_entry *) iter->opaque_);
}


/*** DEPENDENCIES:
struct json_object_iter
{
  char *key;
  struct json_object *val;
  struct lh_entry *entry;
}
----------------------------
inline static void *lh_entry_v(const struct lh_entry *e)
{
  return (void *) ((uintptr_t) ((const void *) e->v));
}


----------------------------
struct json_object_iterator
{
  const void *opaque_;
}
----------------------------
None
----------------------------
***/


struct json_object_iterator json_object_iter_begin(struct json_object *obj)
{
  struct json_object_iterator iter;
  struct lh_table *pTable;
  unsigned int pTable_idx = 0;
  pTable_idx = json_object_get_object(obj);
  do
  {
  }
  while (0);
  iter.opaque_ = lh_table_head(pTable);
  return iter;
}


/*** DEPENDENCIES:
inline static struct lh_entry *lh_table_head(const lh_table *t)
{
  return t->head;
}


----------------------------
struct json_object_iter
{
  char *key;
  struct json_object *val;
  struct lh_entry *entry;
}
----------------------------
struct json_object_iterator
{
  const void *opaque_;
}
----------------------------
struct lh_table *json_object_get_object(const struct json_object *jso)
{
  if (!jso)
  {
    return 0;
  }
  switch (jso->o_type)
  {
    case json_type_object:
    {
      return JC_OBJECT_C(jso)->c_object;
    }

    default:
    {
      return 0;
    }

  }

}


----------------------------
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
----------------------------
None
----------------------------
***/


