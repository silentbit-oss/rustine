#include <arraylist.c>
#include <arraylist.h>
#include <config.h>
#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

typedef void array_list_free_fn(void *data);
struct array_list
{
  void **array;
  size_t length;
  size_t size;
  array_list_free_fn *free_fn;
};
typedef struct array_list array_list;
extern struct array_list *array_list_new(array_list_free_fn *free_fn);
extern struct array_list *array_list_new2(array_list_free_fn *free_fn, int initial_size);
extern void array_list_free(struct array_list *al);
extern void *array_list_get_idx(struct array_list *al, size_t i);
extern int array_list_insert_idx(struct array_list *al, size_t i, void *data);
extern int array_list_put_idx(struct array_list *al, size_t i, void *data);
extern int array_list_add(struct array_list *al, void *data);
extern size_t array_list_length(struct array_list *al);
extern void array_list_sort(struct array_list *arr, int (*compar)(const void *, const void *));
extern void *array_list_bsearch(const void **key, struct array_list *arr, int (*compar)(const void *, const void *));
extern int array_list_del_idx(struct array_list *arr, size_t idx, size_t count);
extern int array_list_shrink(struct array_list *arr, size_t empty_slots);
struct array_list *array_list_new(array_list_free_fn *free_fn)
{
  return array_list_new2(free_fn, 32);
}

struct array_list *array_list_new2(array_list_free_fn *free_fn, int initial_size)
{
  struct array_list *arr;
  unsigned int arr_idx = 0;
  if ((initial_size < 0) || (((size_t) initial_size) >= (18446744073709551615UL / (sizeof(void *)))))
  {
    return 0;
  }
  arr_idx = (struct array_list *) malloc(sizeof(struct array_list));
  if (!(&arr[arr_idx]))
  {
    return 0;
  }
  arr->size = initial_size;
  arr->length = 0;
  arr->free_fn = free_fn;
  if (!(arr->array = (void **) malloc(arr->size * (sizeof(void *)))))
  {
    free(arr);
    return 0;
  }
  return arr;
}

extern void array_list_free(struct array_list *arr)
{
  size_t i;
  for (i = 0; i < arr->length; i += 1)
  {
    if (arr->array[i])
    {
      arr->free_fn(arr->array[i]);
    }
  }

  free(arr->array);
  free(arr);
}

void *array_list_get_idx(struct array_list *arr, size_t i)
{
  if (i >= arr->length)
  {
    return 0;
  }
  return arr->array[i];
}

static int array_list_expand_internal(struct array_list *arr, size_t max)
{
  void *t;
  unsigned int t_idx = 0;
  size_t new_size;
  if (max < arr->size)
  {
    return 0;
  }
  if (arr->size >= (18446744073709551615UL / 2))
  {
    new_size = max;
  }
  else
  {
    new_size = arr->size << 1;
    if (new_size < max)
    {
      new_size = max;
    }
  }
  if (new_size > ((~((size_t) 0)) / (sizeof(void *))))
  {
    return -1;
  }
  if (!(t_idx = realloc(arr->array, new_size * (sizeof(void *)))))
  {
    return -1;
  }
  arr->array = (void **) t;
  arr->size = new_size;
  return 0;
}

int array_list_shrink(struct array_list *arr, size_t empty_slots)
{
  void *t;
  unsigned int t_idx = 0;
  size_t new_size;
  if (empty_slots >= ((18446744073709551615UL / (sizeof(void *))) - arr->length))
  {
    return -1;
  }
  new_size = arr->length + empty_slots;
  if (new_size == arr->size)
  {
    return 0;
  }
  if (new_size > arr->size)
  {
    return array_list_expand_internal(arr, new_size);
  }
  if (new_size == 0)
  {
    new_size = 1;
  }
  if (!(t_idx = realloc(arr->array, new_size * (sizeof(void *)))))
  {
    return -1;
  }
  arr->array = (void **) t;
  arr->size = new_size;
  return 0;
}

int array_list_insert_idx(struct array_list *arr, size_t idx, void *data)
{
  size_t move_amount;
  if (idx >= arr->length)
  {
    return array_list_put_idx(arr, idx, data);
  }
  if (arr->length == 18446744073709551615UL)
  {
    return -1;
  }
  if (array_list_expand_internal(arr, arr->length + 1))
  {
    return -1;
  }
  move_amount = (arr->length - idx) * (sizeof(void *));
  memmove((arr->array + idx) + 1, arr->array + idx, move_amount);
  arr->array[idx] = data;
  arr->length += 1;
  return 0;
}

int array_list_put_idx(struct array_list *arr, size_t idx, void *data)
{
  if (idx > (18446744073709551615UL - 1))
  {
    return -1;
  }
  if (array_list_expand_internal(arr, idx + 1))
  {
    return -1;
  }
  if ((idx < arr->length) && arr->array[idx])
  {
    arr->free_fn(arr->array[idx]);
  }
  arr->array[idx] = data;
  if (idx > arr->length)
  {
    memset(arr->array + arr->length, 0, (idx - arr->length) * (sizeof(void *)));
  }
  if (arr->length <= idx)
  {
    arr->length = idx + 1;
  }
  return 0;
}

int array_list_add(struct array_list *arr, void *data)
{
  size_t idx = arr->length;
  if (idx > (18446744073709551615UL - 1))
  {
    return -1;
  }
  if (array_list_expand_internal(arr, idx + 1))
  {
    return -1;
  }
  arr->array[idx] = data;
  arr->length += 1;
  return 0;
}

void array_list_sort(struct array_list *arr, int (*compar)(const void *, const void *))
{
  qsort(arr->array, arr->length, sizeof(arr->array[0]), compar);
}

void *array_list_bsearch(const void **key, struct array_list *arr, int (*compar)(const void *, const void *))
{
  return bsearch(key, arr->array, arr->length, sizeof(arr->array[0]), compar);
}

size_t array_list_length(struct array_list *arr)
{
  return arr->length;
}

int array_list_del_idx(struct array_list *arr, size_t idx, size_t count)
{
  size_t i;
  size_t stop;
  if (idx > (18446744073709551615UL - count))
  {
    return -1;
  }
  stop = idx + count;
  if ((idx >= arr->length) || (stop > arr->length))
  {
    return -1;
  }
  for (i = idx; i < stop; i += 1)
  {
    if (arr->array[i])
    {
      arr->free_fn(arr->array[i]);
    }
  }

  memmove(arr->array + idx, arr->array + stop, (arr->length - stop) * (sizeof(void *)));
  arr->length -= count;
  return 0;
}


typedef void array_list_free_fn(void *data);
struct array_list
{
  void **array;
  size_t length;
  size_t size;
  array_list_free_fn *free_fn;
};
typedef struct array_list array_list;
extern struct array_list *array_list_new(array_list_free_fn *free_fn);
extern struct array_list *array_list_new2(array_list_free_fn *free_fn, int initial_size);
extern void array_list_free(struct array_list *al);
extern void *array_list_get_idx(struct array_list *al, size_t i);
extern int array_list_insert_idx(struct array_list *al, size_t i, void *data);
extern int array_list_put_idx(struct array_list *al, size_t i, void *data);
extern int array_list_add(struct array_list *al, void *data);
extern size_t array_list_length(struct array_list *al);
extern void array_list_sort(struct array_list *arr, int (*compar)(const void *, const void *));
extern void *array_list_bsearch(const void **key, struct array_list *arr, int (*compar)(const void *, const void *));
extern int array_list_del_idx(struct array_list *arr, size_t idx, size_t count);
extern int array_list_shrink(struct array_list *arr, size_t empty_slots);
struct array_list *array_list_new(array_list_free_fn *free_fn)
{
  return array_list_new2(free_fn, 32);
}

struct array_list *array_list_new2(array_list_free_fn *free_fn, int initial_size)
{
  struct array_list *arr;
  unsigned int arr_idx = 0;
  if ((initial_size < 0) || (((size_t) initial_size) >= (18446744073709551615UL / (sizeof(void *)))))
  {
    return 0;
  }
  arr_idx = (struct array_list *) malloc(sizeof(struct array_list));
  if (!(&arr[arr_idx]))
  {
    return 0;
  }
  arr->size = initial_size;
  arr->length = 0;
  arr->free_fn = free_fn;
  if (!(arr->array = (void **) malloc(arr->size * (sizeof(void *)))))
  {
    free(arr);
    return 0;
  }
  return arr;
}

extern void array_list_free(struct array_list *arr)
{
  size_t i;
  for (i = 0; i < arr->length; i += 1)
  {
    if (arr->array[i])
    {
      arr->free_fn(arr->array[i]);
    }
  }

  free(arr->array);
  free(arr);
}

void *array_list_get_idx(struct array_list *arr, size_t i)
{
  if (i >= arr->length)
  {
    return 0;
  }
  return arr->array[i];
}

static int array_list_expand_internal(struct array_list *arr, size_t max)
{
  void *t;
  unsigned int t_idx = 0;
  size_t new_size;
  if (max < arr->size)
  {
    return 0;
  }
  if (arr->size >= (18446744073709551615UL / 2))
  {
    new_size = max;
  }
  else
  {
    new_size = arr->size << 1;
    if (new_size < max)
    {
      new_size = max;
    }
  }
  if (new_size > ((~((size_t) 0)) / (sizeof(void *))))
  {
    return -1;
  }
  if (!(t_idx = realloc(arr->array, new_size * (sizeof(void *)))))
  {
    return -1;
  }
  arr->array = (void **) t;
  arr->size = new_size;
  return 0;
}

int array_list_shrink(struct array_list *arr, size_t empty_slots)
{
  void *t;
  unsigned int t_idx = 0;
  size_t new_size;
  if (empty_slots >= ((18446744073709551615UL / (sizeof(void *))) - arr->length))
  {
    return -1;
  }
  new_size = arr->length + empty_slots;
  if (new_size == arr->size)
  {
    return 0;
  }
  if (new_size > arr->size)
  {
    return array_list_expand_internal(arr, new_size);
  }
  if (new_size == 0)
  {
    new_size = 1;
  }
  if (!(t_idx = realloc(arr->array, new_size * (sizeof(void *)))))
  {
    return -1;
  }
  arr->array = (void **) t;
  arr->size = new_size;
  return 0;
}

int array_list_insert_idx(struct array_list *arr, size_t idx, void *data)
{
  size_t move_amount;
  if (idx >= arr->length)
  {
    return array_list_put_idx(arr, idx, data);
  }
  if (arr->length == 18446744073709551615UL)
  {
    return -1;
  }
  if (array_list_expand_internal(arr, arr->length + 1))
  {
    return -1;
  }
  move_amount = (arr->length - idx) * (sizeof(void *));
  memmove((arr->array + idx) + 1, arr->array + idx, move_amount);
  arr->array[idx] = data;
  arr->length += 1;
  return 0;
}

int array_list_put_idx(struct array_list *arr, size_t idx, void *data)
{
  if (idx > (18446744073709551615UL - 1))
  {
    return -1;
  }
  if (array_list_expand_internal(arr, idx + 1))
  {
    return -1;
  }
  if ((idx < arr->length) && arr->array[idx])
  {
    arr->free_fn(arr->array[idx]);
  }
  arr->array[idx] = data;
  if (idx > arr->length)
  {
    memset(arr->array + arr->length, 0, (idx - arr->length) * (sizeof(void *)));
  }
  if (arr->length <= idx)
  {
    arr->length = idx + 1;
  }
  return 0;
}

int array_list_add(struct array_list *arr, void *data)
{
  size_t idx = arr->length;
  if (idx > (18446744073709551615UL - 1))
  {
    return -1;
  }
  if (array_list_expand_internal(arr, idx + 1))
  {
    return -1;
  }
  arr->array[idx] = data;
  arr->length += 1;
  return 0;
}

void array_list_sort(struct array_list *arr, int (*compar)(const void *, const void *))
{
  qsort(arr->array, arr->length, sizeof(arr->array[0]), compar);
}

void *array_list_bsearch(const void **key, struct array_list *arr, int (*compar)(const void *, const void *))
{
  return bsearch(key, arr->array, arr->length, sizeof(arr->array[0]), compar);
}

size_t array_list_length(struct array_list *arr)
{
  return arr->length;
}

int array_list_del_idx(struct array_list *arr, size_t idx, size_t count)
{
  size_t i;
  size_t stop;
  if (idx > (18446744073709551615UL - count))
  {
    return -1;
  }
  stop = idx + count;
  if ((idx >= arr->length) || (stop > arr->length))
  {
    return -1;
  }
  for (i = idx; i < stop; i += 1)
  {
    if (arr->array[i])
    {
      arr->free_fn(arr->array[i]);
    }
  }

  memmove(arr->array + idx, arr->array + stop, (arr->length - stop) * (sizeof(void *)));
  arr->length -= count;
  return 0;
}

