#include <ht.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct ht ht;
ht *ht_create(void);
void ht_destroy(ht *table);
void *ht_get(ht *table, const char *key);
const char *ht_set(ht *table, const char *key, void *value);
size_t ht_length(ht *table);
typedef struct 
{
  const char *key;
  void *value;
  ht *_table;
  size_t _index;
} hti;
hti ht_iterator(ht *table);
bool ht_next(hti *it);
typedef struct 
{
  char *key;
  void *value;
} ht_entry;
struct ht
{
  ht_entry *entries;
  size_t capacity;
  size_t length;
};
typedef struct 
{
  char *key;
  int value;
} item;
void exit_nomem(void)
{
  fprintf(stderr, "out of memory\n");
  exit(1);
}

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

