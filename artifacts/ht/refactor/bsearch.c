#include <bsearch.c>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
  char *key;
  int value;
} item;
int cmp(const void *a, const void *b)
{
  item *item_a = (item *) a;
  item *item_b = (item *) b;
  return strcmp(item_a->key, item_b->key);
}

item *binary_search(item *items, size_t size, const char *key)
{
  if ((size + size) < size)
  {
    return 0;
  }
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

  return 0;
}

int main(void)
{
  item items[] = {{"bar", 42}, {"bazz", 36}, {"bob", 11}, {"buzz", 7}, {"foo", 10}, {"jane", 100}, {"x", 200}};
  size_t num_items = (sizeof(items)) / (sizeof(item));
  item key = {"bob", 0};
  item *found = bsearch(&key, items, num_items, sizeof(item), cmp);
  unsigned int found_idx = 0;
  if ((&found[found_idx]) == 0)
  {
    return 1;
  }
  printf("bsearch: value of 'bob' is %d\n", found->value);
  found_idx = binary_search(items, num_items, "bob");
  if ((&found[found_idx]) == 0)
  {
    return 1;
  }
  printf("binary_search: value of 'bob' is %d\n", found->value);
  return 0;
}


typedef struct 
{
  char *key;
  int value;
} item;
int cmp(const void *a, const void *b)
{
  item *item_a = (item *) a;
  item *item_b = (item *) b;
  return strcmp(item_a->key, item_b->key);
}

item *binary_search(item *items, size_t size, const char *key)
{
  if ((size + size) < size)
  {
    return 0;
  }
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

  return 0;
}

int main(void)
{
  item items[] = {{"bar", 42}, {"bazz", 36}, {"bob", 11}, {"buzz", 7}, {"foo", 10}, {"jane", 100}, {"x", 200}};
  size_t num_items = (sizeof(items)) / (sizeof(item));
  item key = {"bob", 0};
  item *found = bsearch(&key, items, num_items, sizeof(item), cmp);
  unsigned int found_idx = 0;
  if ((&found[found_idx]) == 0)
  {
    return 1;
  }
  printf("bsearch: value of 'bob' is %d\n", found->value);
  found_idx = binary_search(items, num_items, "bob");
  if ((&found[found_idx]) == 0)
  {
    return 1;
  }
  printf("binary_search: value of 'bob' is %d\n", found->value);
  return 0;
}

