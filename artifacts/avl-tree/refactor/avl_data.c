#include <assert.h>
#include <avl_data.c>
#include <avl_data.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
  int key;
} mydata;
mydata *makedata(int key);
int compare_func(const void *d1, const void *d2);
void destroy_func(void *d);
void print_func(void *d);
void print_char_func(void *d);
mydata *makedata(int key)
{
  mydata *p;
  unsigned int p_idx = 0;
  p_idx = (mydata *) malloc(sizeof(mydata));
  if ((&p[p_idx]) != 0)
  {
    p->key = key;
  }
  return p;
}

int compare_func(const void *d1, const void *d2)
{
  mydata *p1;
  unsigned int p1_idx = 0;
  mydata *p2;
  unsigned int p2_idx = 0;
  assert(d1 != 0);
  assert(d2 != 0);
  p1_idx = (mydata *) d1;
  p2_idx = (mydata *) d2;
  if (p1->key == p2->key)
  {
    return 0;
  }
  else
    if (p1->key > p2->key)
  {
    return 1;
  }
  else
    return -1;
}

void destroy_func(void *d)
{
  mydata *p;
  unsigned int p_idx = 0;
  assert(d != 0);
  p_idx = (mydata *) d;
  free(p);
}

void print_func(void *d)
{
  mydata *p;
  unsigned int p_idx = 0;
  assert(d != 0);
  p_idx = (mydata *) d;
  printf("%d", p->key);
}

void print_char_func(void *d)
{
  mydata *p;
  unsigned int p_idx = 0;
  assert(d != 0);
  p_idx = (mydata *) d;
  printf("%c", p->key & 127);
}


typedef struct 
{
  int key;
} mydata;
mydata *makedata(int key);
int compare_func(const void *d1, const void *d2);
void destroy_func(void *d);
void print_func(void *d);
void print_char_func(void *d);
mydata *makedata(int key)
{
  mydata *p;
  unsigned int p_idx = 0;
  p_idx = (mydata *) malloc(sizeof(mydata));
  if ((&p[p_idx]) != 0)
  {
    p->key = key;
  }
  return p;
}

int compare_func(const void *d1, const void *d2)
{
  mydata *p1;
  unsigned int p1_idx = 0;
  mydata *p2;
  unsigned int p2_idx = 0;
  assert(d1 != 0);
  assert(d2 != 0);
  p1_idx = (mydata *) d1;
  p2_idx = (mydata *) d2;
  if (p1->key == p2->key)
  {
    return 0;
  }
  else
    if (p1->key > p2->key)
  {
    return 1;
  }
  else
    return -1;
}

void destroy_func(void *d)
{
  mydata *p;
  unsigned int p_idx = 0;
  assert(d != 0);
  p_idx = (mydata *) d;
  free(p);
}

void print_func(void *d)
{
  mydata *p;
  unsigned int p_idx = 0;
  assert(d != 0);
  p_idx = (mydata *) d;
  printf("%d", p->key);
}

void print_char_func(void *d)
{
  mydata *p;
  unsigned int p_idx = 0;
  assert(d != 0);
  p_idx = (mydata *) d;
  printf("%c", p->key & 127);
}

