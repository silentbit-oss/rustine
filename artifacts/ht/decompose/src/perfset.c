int main(int argc, char **argv)
{
  if (argc < 2)
  {
    fprintf(stderr, "usage: perftest file\n");
    return 1;
  }
  FILE *f = fopen(argv[1], "rb");
  if (f == 0)
  {
    fprintf(stderr, "can't open file: %s\n", argv[1]);
    return 1;
  }
  fseek(f, 0, 2);
  long size = ftell(f);
  fseek(f, 0, 0);
  char *contents = (char *) malloc(size + 1);
  if (contents == 0)
  {
    exit_nomem();
  }
  size_t nread = fread(contents, 1, size, f);
  if (((long) nread) != size)
  {
    fprintf(stderr, "read %ld bytes instead of %ld", (long) nread, size);
    return 1;
  }
  fclose(f);
  contents[size] = 0;
  ht *counts = ht_create();
  if (counts == 0)
  {
    exit_nomem();
  }
  for (char *p = contents; p[p_idx]; p_idx += 1)
  {
    while (p[p_idx] && (p[p_idx] <= ' '))
    {
      p_idx += 1;
    }

    char *word = p;
    while (p[p_idx] && (p[p_idx] > ' '))
    {
      p_idx += 1;
    }

    if (p[p_idx] != 0)
    {
      p[p_idx] = 0;
    }
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

  unsigned int p_idx = 0;
  const char **keys = malloc(ht_length(counts) * (sizeof(char *)));
  if (keys == 0)
  {
    exit_nomem();
  }
  hti it = ht_iterator(counts);
  int i = 0;
  while (ht_next(&it))
  {
    keys[i] = it.key;
    i += 1;
  }

  ht *table = ht_create();
  if (table == 0)
  {
    exit_nomem();
  }
  int value = 1;
  clock_t start = clock();
  for (int i = 0; i < ht_length(counts); i += 1)
  {
    if (ht_set(table, keys[i], &value) == 0)
    {
      exit_nomem();
    }
  }

  clock_t end = clock();
  double elapsed_ms = (((double) (end - start)) / CLOCKS_PER_SEC) * 1000;
  printf("setting %lu keys: %.09fms\n", ht_length(counts), elapsed_ms);
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


