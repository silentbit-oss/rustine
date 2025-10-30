// element in merge of:  lh_table_resize,lh_table_insert_w_hash
int lh_table_resize(struct lh_table *t, int new_size)
{
  struct lh_table *new_t;
  unsigned int new_t_idx = 0;
  struct lh_entry *ent;
  unsigned int ent_idx = 0;
  new_t_idx = lh_table_new(new_size, 0, t->hash_fn, t->equal_fn);
  if ((&new_t[new_t_idx]) == 0)
  {
    return -1;
  }
  for (ent_idx = t->head; (&ent[ent_idx]) != 0; ent_idx = ent_idx->next)
  {
    unsigned long h = lh_get_hash(new_t, ent->k);
    unsigned int opts = 0;
    if (ent->k_is_constant)
    {
      opts = 1 << 2;
    }
    if (lh_table_insert_w_hash(new_t, ent->k, ent->v, h, opts) != 0)
    {
      lh_table_free(new_t);
      return -1;
    }
  }

  free(t->table);
  t->table = new_t->table;
  t->size = new_size;
  t->head = new_t->head;
  t->tail = new_t->tail;
  free(new_t);
  return 0;
}


/*** DEPENDENCIES:
struct lh_table *lh_table_new(int size, lh_entry_free_fn *free_fn, lh_hash_fn *hash_fn, lh_equal_fn *equal_fn)
{
  int i;
  struct lh_table *t;
  unsigned int t_idx = 0;
  assert(size > 0);
  t_idx = (struct lh_table *) calloc(1, sizeof(struct lh_table));
  if (!(&t[t_idx]))
  {
    return 0;
  }
  t->count = 0;
  t->size = size;
  t->table = (struct lh_entry *) calloc(size, sizeof(struct lh_entry));
  if (!t->table)
  {
    free(t);
    return 0;
  }
  t->free_fn = free_fn;
  t->hash_fn = hash_fn;
  t->equal_fn = equal_fn;
  for (i = 0; i < size; i += 1)
  {
    t->table[i].k = (void *) (-1);
  }

  return t;
}


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
void lh_table_free(struct lh_table *t)
{
  struct lh_entry *c;
  unsigned int c_idx = 0;
  if (t->free_fn)
  {
    for (c_idx = t->head; (&c[c_idx]) != 0; c_idx = c_idx->next)
    {
      t->free_fn(c);
    }

  }
  free(t->table);
  free(t);
}


----------------------------
inline static unsigned long lh_get_hash(const struct lh_table *t, const void *k)
{
  return t->hash_fn(k);
}


----------------------------
None
----------------------------
***/


// element in merge of:  lh_table_resize,lh_table_insert_w_hash
int lh_table_insert_w_hash(struct lh_table *t, const void *k, const void *v, const unsigned long h, const unsigned opts)
{
  unsigned long n;
  if (t->count >= (t->size * 0.66))
  {
    int new_size = (t->size > (2147483647 / 2)) ? (2147483647) : (t->size * 2);
    if ((t->size == 2147483647) || (lh_table_resize(t, new_size) != 0))
    {
      return -1;
    }
  }
  n = h % t->size;
  while (1)
  {
    if ((t->table[n].k == ((void *) (-1))) || (t->table[n].k == ((void *) (-2))))
    {
      break;
    }
    if (((int) (++n)) == t->size)
    {
      n = 0;
    }
  }

  t->table[n].k = k;
  t->table[n].k_is_constant = opts & (1 << 2);
  t->table[n].v = v;
  t->count += 1;
  if (t->head == 0)
  {
    t->head = (t->tail = &t->table[n]);
    t->table[n].next = (t->table[n].prev = 0);
  }
  else
  {
    t->tail->next = &t->table[n];
    t->table[n].prev = t->tail;
    t->table[n].next = 0;
    t->tail = &t->table[n];
  }
  return 0;
}


/*** DEPENDENCIES:
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


