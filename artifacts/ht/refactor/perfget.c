#include <ctype.h>
#include <ht.h>
#include <perfget.c>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void *found;
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

  int runs = 10;
  clock_t start = clock();
  for (int run = 0; run < runs; run += 1)
  {
    for (int i = 0; i < ht_length(counts); i += 1)
    {
      found = ht_get(counts, keys[i]);
    }

  }

  clock_t end = clock();
  double elapsed_ms = (((double) (end - start)) / CLOCKS_PER_SEC) * 1000;
  printf("%d runs getting %lu keys: %.03fms\n", runs, ht_length(counts), elapsed_ms);
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

void *found;
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

  int runs = 10;
  clock_t start = clock();
  for (int run = 0; run < runs; run += 1)
  {
    for (int i = 0; i < ht_length(counts); i += 1)
    {
      found = ht_get(counts, keys[i]);
    }

  }

  clock_t end = clock();
  double elapsed_ms = (((double) (end - start)) / CLOCKS_PER_SEC) * 1000;
  printf("%d runs getting %lu keys: %.03fms\n", runs, ht_length(counts), elapsed_ms);
  return 0;
}

