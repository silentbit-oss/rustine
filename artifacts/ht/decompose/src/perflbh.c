item *linear_search(item *items, size_t size, const char *key)
{
  for (size_t i = 0; i < size; i += 1)
  {
    if (strcmp(items[i].key, key) == 0)
    {
      return &items[i];
    }
  }

  return 0;
}


/*** DEPENDENCIES:
typedef struct 
{
  char *key;
  int value;
} item
----------------------------
***/


item *binary_search(item *items, size_t size, const char *key)
{
  size_t low = 0;
  size_t high = size;
  while (low < high)
  {
    size_t mid = (low + high) / 2;
    int c = strcmp(items[mid].key, key);
    if (c == 0)
    {
      return &items[mid];
    }
    if (c < 0)
    {
      low = mid + 1;
    }
    else
    {
      high = mid;
    }
  }

  if ((low < size) && (strcmp(items[low].key, key) == 0))
  {
    return &items[low];
  }
  return 0;
}


/*** DEPENDENCIES:
typedef struct 
{
  char *key;
  int value;
} item
----------------------------
***/


int main(int argc, char **argv)
{
  int runs = 5000000;
  for (int num_items = 1; num_items < ((sizeof(items)) / (sizeof(item))); num_items += 1)
  {
    printf("NUM ITEMS: %d\n", num_items);
    clock_t start = clock();
    for (int item_index = 0; item_index < num_items; item_index += 1)
    {
      char *key = items[item_index].key;
      for (int run = 0; run < runs; run += 1)
      {
        found = linear_search(items, num_items, key);
      }

    }

    clock_t end = clock();
    double elapsed = (((double) (end - start)) / CLOCKS_PER_SEC) / num_items;
    printf("  linear, %d runs: %.09fs\n", runs, elapsed);
    start = clock();
    for (int item_index = 0; item_index < num_items; item_index += 1)
    {
      char *key = items[item_index].key;
      for (int run = 0; run < runs; run += 1)
      {
        found = binary_search(items, num_items, key);
      }

    }

    end = clock();
    elapsed = (((double) (end - start)) / CLOCKS_PER_SEC) / num_items;
    printf("  binary, %d runs: %.09fs\n", runs, elapsed);
    ht *table = ht_create();
    if (table == 0)
    {
      exit_nomem();
    }
    for (int item_index = 0; item_index < num_items; item_index += 1)
    {
      int *pn = malloc(sizeof(int));
      if (pn == 0)
      {
        exit_nomem();
      }
      *pn = items[item_index].value;
      const char *p = ht_set(table, items[item_index].key, pn);
      if (p == 0)
      {
        exit_nomem();
      }
    }

    start = clock();
    for (int item_index = 0; item_index < num_items; item_index += 1)
    {
      char *key = items[item_index].key;
      for (int run = 0; run < runs; run += 1)
      {
        value = (int *) ht_get(table, key);
      }

    }

    end = clock();
    elapsed = (((double) (end - start)) / CLOCKS_PER_SEC) / num_items;
    printf("  hash  , %d runs: %.09fs\n", runs, elapsed);
  }

}


/*** DEPENDENCIES:
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
void *found
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
item *binary_search(item *items, size_t size, const char *key)
{
  size_t low = 0;
  size_t high = size;
  while (low < high)
  {
    size_t mid = (low + high) / 2;
    int c = strcmp(items[mid].key, key);
    if (c == 0)
    {
      return &items[mid];
    }
    if (c < 0)
    {
      low = mid + 1;
    }
    else
    {
      high = mid;
    }
  }

  if ((low < size) && (strcmp(items[low].key, key) == 0))
  {
    return &items[low];
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
item *linear_search(item *items, size_t size, const char *key)
{
  for (size_t i = 0; i < size; i += 1)
  {
    if (strcmp(items[i].key, key) == 0)
    {
      return &items[i];
    }
  }

  return 0;
}


----------------------------
item items[] = {{"aoo", 0}, {"bar", 1}, {"cazz", 2}, {"duzz", 3}, {"eaddle", 4}, {"fche", 5}, {"garf", 6}, {"hache", 7}, {"iya", 8}, {"jay", 9}, {"kay", 10}, {"lell", 11}, {"memm", 12}, {"noo", 0}, {"oar", 1}, {"pazz", 2}, {"quzz", 3}, {"raddle", 4}, {"sche", 5}, {"tarf", 6}, {"uache", 7}, {"vya", 8}, {"way", 9}, {"xay", 10}, {"yell", 11}, {"zemm", 12}}
----------------------------
int *value
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


