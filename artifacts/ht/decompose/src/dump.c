int main(void)
{
  item items[] = {{"foo", 10}, {"bar", 42}, {"bazz", 36}, {"buzz", 7}, {"bob", 11}, {"jane", 100}, {"x", 200}};
  size_t num_items = (sizeof(items)) / (sizeof(item));
  ht *table = ht_create();
  if (table == 0)
  {
    exit_nomem();
  }
  for (int i = 0; i < num_items; i += 1)
  {
    if (ht_set(table, items[i].key, &items[i].value) == 0)
    {
      exit_nomem();
    }
  }

  for (int i = 0; i < table->capacity; i += 1)
  {
    if (table->entries[i].key != 0)
    {
      printf("index %d: key %s, value %d\n", i, table->entries[i].key, *((int *) table->entries[i].value));
    }
    else
    {
      printf("index %d: empty\n", i);
    }
  }

  return 0;
}


/*** DEPENDENCIES:
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
typedef struct 
{
  char *key;
  int value;
} item
----------------------------
struct ht
{
  ht_entry *entries;
  size_t capacity;
  size_t length;
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


