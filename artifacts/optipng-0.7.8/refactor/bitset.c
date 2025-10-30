#include <bitset.c>
#include <bitset.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stddef.h>

typedef unsigned int opng_bitset_t;
enum 
{
  OPNG_BITSET_ELT_MIN = 0,
  OPNG_BITSET_ELT_MAX = (int) (((sizeof(opng_bitset_t)) * 8) - 1)
};
unsigned int opng_bitset_count(opng_bitset_t set);
int opng_bitset_find_first(opng_bitset_t set);
int opng_bitset_find_next(opng_bitset_t set, int elt);
int opng_bitset_find_last(opng_bitset_t set);
int opng_bitset_find_prev(opng_bitset_t set, int elt);
int opng_strparse_rangeset_to_bitset(opng_bitset_t *out_set, const char *rangeset_str, opng_bitset_t mask_set);
size_t opng_strformat_bitset_as_rangeset(char *out_buf, size_t out_buf_size, opng_bitset_t bitset);
unsigned int opng_bitset_count(opng_bitset_t set)
{
  unsigned int result;
  result = 0;
  while (set != 0)
  {
    set &= set - 1;
    result += 1;
  }

  return result;
}

int opng_bitset_find_first(opng_bitset_t set)
{
  int i;
  for (i = 0; i <= OPNG_BITSET_ELT_MAX; i += 1)
  {
    if ((set & (1U << i)) != 0)
    {
      return i;
    }
  }

  return -1;
}

int opng_bitset_find_next(opng_bitset_t set, int elt)
{
  int i;
  for (i = ((elt > (-1)) ? (elt) : (-1)) + 1; i <= OPNG_BITSET_ELT_MAX; i += 1)
  {
    if ((set & (1U << i)) != 0)
    {
      return i;
    }
  }

  return -1;
}

int opng_bitset_find_last(opng_bitset_t set)
{
  int i;
  for (i = OPNG_BITSET_ELT_MAX; i >= 0; i -= 1)
  {
    if ((set & (1U << i)) != 0)
    {
      return i;
    }
  }

  return -1;
}

int opng_bitset_find_prev(opng_bitset_t set, int elt)
{
  int i;
  for (i = ((elt < (OPNG_BITSET_ELT_MAX + 1)) ? (elt) : (OPNG_BITSET_ELT_MAX + 1)) - 1; i >= 0; i -= 1)
  {
    if ((set & (1U << i)) != 0)
    {
      return i;
    }
  }

  return -1;
}

int opng_strparse_rangeset_to_bitset(opng_bitset_t *out_set, const char *rangeset_str, opng_bitset_t mask_set)
{
  opng_bitset_t result;
  const char *ptr;
  unsigned int ptr_idx = 0;
  int state;
  int num;
  int num1;
  int num2;
  int err_invalid;
  int err_range;
  result = 0U;
  ptr_idx = rangeset_str;
  state = 0;
  err_invalid = (err_range = 0);
  num1 = (num2 = -1);
  for (;;)
  {
    helper_opng_strparse_rangeset_to_bitset_1(&result, &ptr_idx, &state, &num, &num1, &num2, &err_invalid, &err_range, mask_set, ptr);
  }

  {
    while (isspace(*(&ptr[ptr_idx])))
    {
      ptr_idx += 1;
    }

  }
  ;
  if (ptr[ptr_idx] != '\0')
  {
    err_invalid = 1;
  }
  if (err_invalid)
  {
    *out_set = 0U;
    return -1;
  }
  else
    if (err_range)
  {
    *out_set = ~0U;
    return -1;
  }
  else
  {
    *out_set = result;
    return 0;
  }
}

size_t opng_strformat_bitset_as_rangeset(char *out_buf, size_t out_buf_size, opng_bitset_t bitset);

typedef unsigned int opng_bitset_t;
enum 
{
  OPNG_BITSET_ELT_MIN = 0,
  OPNG_BITSET_ELT_MAX = (int) (((sizeof(opng_bitset_t)) * 8) - 1)
};
unsigned int opng_bitset_count(opng_bitset_t set);
int opng_bitset_find_first(opng_bitset_t set);
int opng_bitset_find_next(opng_bitset_t set, int elt);
int opng_bitset_find_last(opng_bitset_t set);
int opng_bitset_find_prev(opng_bitset_t set, int elt);
int opng_strparse_rangeset_to_bitset(opng_bitset_t *out_set, const char *rangeset_str, opng_bitset_t mask_set);
size_t opng_strformat_bitset_as_rangeset(char *out_buf, size_t out_buf_size, opng_bitset_t bitset);
unsigned int opng_bitset_count(opng_bitset_t set)
{
  unsigned int result;
  result = 0;
  while (set != 0)
  {
    set &= set - 1;
    result += 1;
  }

  return result;
}

int opng_bitset_find_first(opng_bitset_t set)
{
  int i;
  for (i = 0; i <= OPNG_BITSET_ELT_MAX; i += 1)
  {
    if ((set & (1U << i)) != 0)
    {
      return i;
    }
  }

  return -1;
}

int opng_bitset_find_next(opng_bitset_t set, int elt)
{
  int i;
  for (i = ((elt > (-1)) ? (elt) : (-1)) + 1; i <= OPNG_BITSET_ELT_MAX; i += 1)
  {
    if ((set & (1U << i)) != 0)
    {
      return i;
    }
  }

  return -1;
}

int opng_bitset_find_last(opng_bitset_t set)
{
  int i;
  for (i = OPNG_BITSET_ELT_MAX; i >= 0; i -= 1)
  {
    if ((set & (1U << i)) != 0)
    {
      return i;
    }
  }

  return -1;
}

int opng_bitset_find_prev(opng_bitset_t set, int elt)
{
  int i;
  for (i = ((elt < (OPNG_BITSET_ELT_MAX + 1)) ? (elt) : (OPNG_BITSET_ELT_MAX + 1)) - 1; i >= 0; i -= 1)
  {
    if ((set & (1U << i)) != 0)
    {
      return i;
    }
  }

  return -1;
}

int opng_strparse_rangeset_to_bitset(opng_bitset_t *out_set, const char *rangeset_str, opng_bitset_t mask_set)
{
  opng_bitset_t result;
  const char *ptr;
  unsigned int ptr_idx = 0;
  int state;
  int num;
  int num1;
  int num2;
  int err_invalid;
  int err_range;
  result = 0U;
  ptr_idx = rangeset_str;
  state = 0;
  err_invalid = (err_range = 0);
  num1 = (num2 = -1);
  for (;;)
  {
    {
      while (isspace(*(&ptr[ptr_idx])))
      {
        ptr_idx += 1;
      }

    }
    ;
    switch (state)
    {
      case 0:

      case 2:
        if ((ptr[ptr_idx] >= '0') && (ptr[ptr_idx] <= '9'))
      {
        num = 0;
        do
        {
          num = (10 * num) + (ptr[ptr_idx] - '0');
          if (num > OPNG_BITSET_ELT_MAX)
          {
            num = OPNG_BITSET_ELT_MAX;
            err_range = 1;
          }
          ptr_idx += 1;
        }
        while ((ptr[ptr_idx] >= '0') && (ptr[ptr_idx] <= '9'));
        if (!((mask_set & (1U << num)) != 0))
        {
          err_range = 1;
        }
        if (state == 0)
        {
          num1 = num;
        }
        num2 = num;
        state += 1;
        continue;
      }
        break;

      case 1:
        if (ptr[ptr_idx] == '-')
      {
        ptr_idx += 1;
        num2 = OPNG_BITSET_ELT_MAX;
        state += 1;
        continue;
      }
        break;

    }

    if (state > 0)
    {
      if (num1 <= num2)
      {
        result |= (num1 <= num2) ? ((((1U << (num2 - num1)) << 1) - 1) << num1) : (0U);
        result &= mask_set;
      }
      else
      {
        err_range = 1;
      }
      state = 0;
    }
    if ((ptr[ptr_idx] == ',') || (ptr[ptr_idx] == ';'))
    {
      ptr_idx += 1;
      continue;
    }
    else
      if (ptr[ptr_idx] == '-')
    {
      err_invalid = 1;
      break;
    }
    else
    {
      break;
    }
  }

  {
    while (isspace(*(&ptr[ptr_idx])))
    {
      ptr_idx += 1;
    }

  }
  ;
  if (ptr[ptr_idx] != '\0')
  {
    err_invalid = 1;
  }
  if (err_invalid)
  {
    *out_set = 0U;
    return -1;
  }
  else
    if (err_range)
  {
    *out_set = ~0U;
    return -1;
  }
  else
  {
    *out_set = result;
    return 0;
  }
}

size_t opng_strformat_bitset_as_rangeset(char *out_buf, size_t out_buf_size, opng_bitset_t bitset);
void helper_opng_strparse_rangeset_to_bitset_1(opng_bitset_t * const result_ref, unsigned int * const ptr_idx_ref, int * const state_ref, int * const num_ref, int * const num1_ref, int * const num2_ref, int * const err_invalid_ref, int * const err_range_ref, opng_bitset_t mask_set, const char * const ptr)
{
  opng_bitset_t result = *result_ref;
  unsigned int ptr_idx = *ptr_idx_ref;
  int state = *state_ref;
  int num = *num_ref;
  int num1 = *num1_ref;
  int num2 = *num2_ref;
  int err_invalid = *err_invalid_ref;
  int err_range = *err_range_ref;
  {
    while (isspace(*(&ptr[ptr_idx])))
    {
      ptr_idx += 1;
    }

  }
  ;
  switch (state)
  {
    case 0:

    case 2:
    {
      helper_helper_opng_strparse_rangeset_to_bitset_1_1(&ptr_idx, &state, &num, &num1, &num2, &err_range, mask_set, ptr);
    }

    case 1:
    {
      if (ptr[ptr_idx] == '-')
      {
        ptr_idx += 1;
        num2 = OPNG_BITSET_ELT_MAX;
        state += 1;
        continue;
      }
      break;
    }

  }

  if (state > 0)
  {
    if (num1 <= num2)
    {
      result |= (num1 <= num2) ? ((((1U << (num2 - num1)) << 1) - 1) << num1) : (0U);
      result &= mask_set;
    }
    else
    {
      err_range = 1;
    }
    state = 0;
  }
  if ((ptr[ptr_idx] == ',') || (ptr[ptr_idx] == ';'))
  {
    ptr_idx += 1;
    continue;
  }
  else
    if (ptr[ptr_idx] == '-')
  {
    err_invalid = 1;
    break;
  }
  else
  {
    break;
  }
  *result_ref = result;
  *ptr_idx_ref = ptr_idx;
  *state_ref = state;
  *num_ref = num;
  *num1_ref = num1;
  *num2_ref = num2;
  *err_invalid_ref = err_invalid;
  *err_range_ref = err_range;
}

void helper_helper_opng_strparse_rangeset_to_bitset_1_1(unsigned int * const ptr_idx_ref, int * const state_ref, int * const num_ref, int * const num1_ref, int * const num2_ref, int * const err_range_ref, opng_bitset_t mask_set, const char * const ptr)
{
  unsigned int ptr_idx = *ptr_idx_ref;
  int state = *state_ref;
  int num = *num_ref;
  int num1 = *num1_ref;
  int num2 = *num2_ref;
  int err_range = *err_range_ref;
  if ((ptr[ptr_idx] >= '0') && (ptr[ptr_idx] <= '9'))
  {
    num = 0;
    do
    {
      num = (10 * num) + (ptr[ptr_idx] - '0');
      if (num > OPNG_BITSET_ELT_MAX)
      {
        num = OPNG_BITSET_ELT_MAX;
        err_range = 1;
      }
      ptr_idx += 1;
    }
    while ((ptr[ptr_idx] >= '0') && (ptr[ptr_idx] <= '9'));
    if (!((mask_set & (1U << num)) != 0))
    {
      err_range = 1;
    }
    if (state == 0)
    {
      num1 = num;
    }
    num2 = num;
    state += 1;
    continue;
  }
  break;
  *ptr_idx_ref = ptr_idx;
  *state_ref = state;
  *num_ref = num;
  *num1_ref = num1;
  *num2_ref = num2;
  *err_range_ref = err_range;
}

