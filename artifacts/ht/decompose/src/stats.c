void exit_nomem(void)
{
  fprintf(stderr, "out of memory\n");
  exit(1);
}


/*** DEPENDENCIES:
***/


size_t get_probe_len(ht *table, const char *key)
{
  uint64_t hash = hash_key(key);
  size_t index = (size_t) (hash & ((uint64_t) (table->capacity - 1)));
  size_t probe_len = 0;
  while (table->entries[index].key != 0)
  {
    probe_len += 1;
    if (strcmp(key, table->entries[index].key) == 0)
    {
      return probe_len;
    }
    index += 1;
    if (index >= table->capacity)
    {
      index = 0;
    }
  }

  return probe_len;
}


/*** DEPENDENCIES:
struct ht
{
  ht_entry *entries;
  size_t capacity;
  size_t length;
}
----------------------------
static uint64_t hash_key(const char *key)
{
  uint64_t hash = 14695981039346656037UL;
  for (const char *p = key; p[p_idx]; p_idx += 1)
  {
    hash ^= (uint64_t) ((unsigned char) p[p_idx]);
    hash *= 1099511628211UL;
  }

  unsigned int p_idx = 0;
  return hash;
}


----------------------------
***/


int main(void)
{
  ht *counts = ht_create();
  if (counts == 0)
  {
    exit_nomem();
  }
  char word[101];
  while (scanf("%100s", word) != EOF)
  {
    void *value = ht_get(counts, word);
    if (value != 0)
    {
      int *pcount = (int *) value;
      *pcount += 1;
      continue;
    }
    int *pcount = malloc(sizeof(int));
    if (pcount == 0)
    {
      exit_nomem();
    }
    *pcount = 1;
    if (ht_set(counts, word, pcount) == 0)
    {
      exit_nomem();
    }
  }

  hti it = ht_iterator(counts);
  size_t total_probes = 0;
  while (ht_next(&it))
  {
    total_probes += get_probe_len(counts, it.key);
    free(it.value);
  }

  printf("len=%lu cap=%lu avgprobe=%.3f\n", ht_length(counts), counts->capacity, ((double) total_probes) / ht_length(counts));
  ht_destroy(counts);
  return 0;
}


/*** DEPENDENCIES:
typedef struct 
{
  const char *key;
  void *value;
  ht *_table;
  size_t _index;
} hti
----------------------------
void *ht_get(ht *table, const char *key)
{
  uint64_t hash = hash_key(key);
  size_t index = (size_t) (hash & ((uint64_t) (table->capacity - 1)));
  while (table->entries[index].key != 0)
  {
    if (strcmp(key, table->entries[index].key) == 0)
    {
      return table->entries[index].value;
    }
    index += 1;
    if (index >= table->capacity)
    {
      index = 0;
    }
  }

  return 0;
}


----------------------------
void ht_destroy(ht *table)
{
  for (size_t i = 0; i < table->capacity; i += 1)
  {
    free((void *) table->entries[i].key);
  }

  free(table->entries);
  free(table);
}


----------------------------
size_t get_probe_len(ht *table, const char *key)
{
  uint64_t hash = hash_key(key);
  size_t index = (size_t) (hash & ((uint64_t) (table->capacity - 1)));
  size_t probe_len = 0;
  while (table->entries[index].key != 0)
  {
    probe_len += 1;
    if (strcmp(key, table->entries[index].key) == 0)
    {
      return probe_len;
    }
    index += 1;
    if (index >= table->capacity)
    {
      index = 0;
    }
  }

  return probe_len;
}


----------------------------
ht *ht_create(void)
{
  ht *table = malloc(sizeof(ht));
  if (table == 0)
  {
    return 0;
  }
  table->length = 0;
  table->capacity = 16;
  table->entries = calloc(table->capacity, sizeof(ht_entry));
  if (table->entries == 0)
  {
    free(table);
    return 0;
  }
  return table;
}


----------------------------
bool ht_next(hti *it)
{
  ht *table = it->_table;
  while (it->_index < table->capacity)
  {
    size_t i = it->_index;
    it->_index += 1;
    if (table->entries[i].key != 0)
    {
      ht_entry entry = table->entries[i];
      it->key = entry.key;
      it->value = entry.value;
      return 1;
    }
  }

  return 0;
}


----------------------------
struct ht
{
  ht_entry *entries;
  size_t capacity;
  size_t length;
}
----------------------------
size_t ht_length(ht *table)
{
  return table->length;
}


----------------------------
hti ht_iterator(ht *table)
{
  hti it;
  it._table = table;
  it._index = 0;
  return it;
}


----------------------------
void exit_nomem(void)
{
  fprintf(stderr, "out of memory\n");
  exit(1);
}


----------------------------
const char *ht_set(ht *table, const char *key, void *value)
{
  assert(value != 0);
  if (value == 0)
  {
    return 0;
  }
  if (table->length >= (table->capacity / 2))
  {
    if (!ht_expand(table))
    {
      return 0;
    }
  }
  return ht_set_entry(table->entries, table->capacity, key, value, &table->length);
}


----------------------------
***/


