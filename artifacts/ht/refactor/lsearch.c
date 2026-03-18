#include <lsearch.c>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

typedef struct 
{
  char *key;
  int value;
} item;
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

int main(void)
{
  item items[] = {{"foo", 10}, {"bar", 42}, {"bazz", 36}, {"buzz", 7}, {"bob", 11}, {"jane", 100}, {"x", 200}};
  size_t num_items = (sizeof(items)) / (sizeof(item));
  item *found = linear_search(items, num_items, "bob");
  if (found == 0)
  {
    return 1;
  }
  printf("linear_search: value of 'bob' is %d\n", found->value);
  return 0;
}


typedef struct 
{
  char *key;
  int value;
} item;
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

int main(void)
{
  item items[] = {{"foo", 10}, {"bar", 42}, {"bazz", 36}, {"buzz", 7}, {"bob", 11}, {"jane", 100}, {"x", 200}};
  size_t num_items = (sizeof(items)) / (sizeof(item));
  item *found = linear_search(items, num_items, "bob");
  if (found == 0)
  {
    return 1;
  }
  printf("linear_search: value of 'bob' is %d\n", found->value);
  return 0;
}

