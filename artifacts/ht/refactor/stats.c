#include <ctype.h>
#include <ht.h>
#include <stats.c>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

