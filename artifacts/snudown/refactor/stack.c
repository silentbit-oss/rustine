#include <stack.h>
#include <stdlib.h>
#include <string.h>

struct stack
{
  void **item;
  size_t size;
  size_t asize;
};
void stack_free(struct stack *);
int stack_grow(struct stack *, size_t);
int stack_init(struct stack *, size_t);
int stack_push(struct stack *, void *);
void *stack_pop(struct stack *);
void *stack_top(struct stack *);
int stack_grow(struct stack *st, size_t new_size)
{
  void **new_st;
  unsigned int new_st_idx = 0;
  if (st->asize >= new_size)
  {
    return 0;
  }
  new_st_idx = realloc(st->item, new_size * (sizeof(void *)));
  if ((&new_st[new_st_idx]) == 0)
  {
    return -1;
  }
  memset((&new_st[new_st_idx]) + st->asize, 0x0, (new_size - st->asize) * (sizeof(void *)));
  st->item = &new_st[new_st_idx];
  st->asize = new_size;
  if (st->size > new_size)
  {
    st->size = new_size;
  }
  return 0;
}

void stack_free(struct stack *st)
{
  if (!st)
  {
    return;
  }
  free(st->item);
  st->item = 0;
  st->size = 0;
  st->asize = 0;
}

int stack_init(struct stack *st, size_t initial_size)
{
  st->item = 0;
  st->size = 0;
  st->asize = 0;
  if (!initial_size)
  {
    initial_size = 8;
  }
  return stack_grow(st, initial_size);
}

void *stack_pop(struct stack *st)
{
  if (!st->size)
  {
    return 0;
  }
  return st->item[--st->size];
}

int stack_push(struct stack *st, void *item)
{
  if (stack_grow(st, st->size * 2) < 0)
  {
    return -1;
  }
  st->item[st->size++] = item;
  return 0;
}

void *stack_top(struct stack *st)
{
  if (!st->size)
  {
    return 0;
  }
  return st->item[st->size - 1];
}

