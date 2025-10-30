#include <ctype.h>
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
void exit_nomem(void)
{
  fprintf(stderr, "out of memory\n");
  exit(1);
}

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
  while (ht_next(&it))
  {
    printf("%s %d\n", it.key, *((int *) it.value));
    free(it.value);
  }

  printf("%d\n", (int) ht_length(counts));
  ht_destroy(counts);
  return 0;
}

