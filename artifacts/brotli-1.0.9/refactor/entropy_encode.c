#include <constants.h>
#include <entropy_encode.c>
#include <entropy_encode.h>
#include <platform.h>
#include <port.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <types.h>

typedef void *(*brotli_alloc_func)(void *opaque, size_t size);
typedef void (*brotli_free_func)(void *opaque, void *address);
inline static uint16_t BrotliUnalignedRead16(const void *p)
{
  return *((const uint16_t *) p);
}

inline static uint32_t BrotliUnalignedRead32(const void *p)
{
  return *((const uint32_t *) p);
}

inline static uint64_t BrotliUnalignedRead64(const void *p)
{
  return *((const uint64_t *) p);
}

inline static void BrotliUnalignedWrite64(void *p, uint64_t v)
{
  *((uint64_t *) p) = v;
}

inline static void BrotliRBit(void)
{
}

inline static double brotli_min_double(double a, double b)
{
  return (a < b) ? (a) : (b);
}

inline static double brotli_max_double(double a, double b)
{
  return (a > b) ? (a) : (b);
}

inline static float brotli_min_float(float a, float b)
{
  return (a < b) ? (a) : (b);
}

inline static float brotli_max_float(float a, float b)
{
  return (a > b) ? (a) : (b);
}

inline static int brotli_min_int(int a, int b)
{
  return (a < b) ? (a) : (b);
}

inline static int brotli_max_int(int a, int b)
{
  return (a > b) ? (a) : (b);
}

inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}

inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}

inline static uint32_t brotli_min_uint32_t(uint32_t a, uint32_t b)
{
  return (a < b) ? (a) : (b);
}

inline static uint32_t brotli_max_uint32_t(uint32_t a, uint32_t b)
{
  return (a > b) ? (a) : (b);
}

inline static uint8_t brotli_min_uint8_t(uint8_t a, uint8_t b)
{
  return (a < b) ? (a) : (b);
}

inline static uint8_t brotli_max_uint8_t(uint8_t a, uint8_t b)
{
  return (a > b) ? (a) : (b);
}

void *BrotliDefaultAllocFunc(void *opaque, size_t size);
void BrotliDefaultFreeFunc(void *opaque, void *address);
inline static void BrotliSuppressUnusedFunctions(void)
{
  (void) (&BrotliSuppressUnusedFunctions);
  (void) (&BrotliUnalignedRead16);
  (void) (&BrotliUnalignedRead32);
  (void) (&BrotliUnalignedRead64);
  (void) (&BrotliUnalignedWrite64);
  (void) (&BrotliUnalignedRead16);
  (void) (&BrotliUnalignedRead32);
  (void) (&BrotliUnalignedRead64);
  (void) (&BrotliUnalignedWrite64);
  (void) (&BrotliRBit);
  (void) (&brotli_min_double);
  (void) (&brotli_max_double);
  (void) (&brotli_min_float);
  (void) (&brotli_max_float);
  (void) (&brotli_min_int);
  (void) (&brotli_max_int);
  (void) (&brotli_min_size_t);
  (void) (&brotli_max_size_t);
  (void) (&brotli_min_uint32_t);
  (void) (&brotli_max_uint32_t);
  (void) (&brotli_min_uint8_t);
  (void) (&brotli_max_uint8_t);
  (void) (&BrotliDefaultAllocFunc);
  (void) (&BrotliDefaultFreeFunc);
}

typedef struct HuffmanTree
{
  uint32_t total_count_;
  int16_t index_left_;
  int16_t index_right_or_value_;
} HuffmanTree;
inline static void InitHuffmanTree(HuffmanTree *self, uint32_t count, int16_t left, int16_t right)
{
  self->total_count_ = count;
  self->index_left_ = left;
  self->index_right_or_value_ = right;
}

int BrotliSetDepth(int p, HuffmanTree *pool, uint8_t *depth, int max_depth);
void BrotliCreateHuffmanTree(const uint32_t *data, const size_t length, const int tree_limit, HuffmanTree *tree, uint8_t *depth);
void BrotliOptimizeHuffmanCountsForRle(size_t length, uint32_t *counts, uint8_t *good_for_rle);
void BrotliWriteHuffmanTree(const uint8_t *depth, size_t num, size_t *tree_size, uint8_t *tree, uint8_t *extra_bits_data);
void BrotliConvertBitDepthsToSymbols(const uint8_t *depth, size_t len, uint16_t *bits);
extern const size_t kBrotliShellGaps[6];
typedef int (*HuffmanTreeComparator)(const HuffmanTree *, const HuffmanTree *);
inline static void SortHuffmanTreeItems(HuffmanTree *items, const size_t n, HuffmanTreeComparator comparator)
{
  if (n < 13)
  {
    size_t i;
    for (i = 1; i < n; i += 1)
    {
      HuffmanTree tmp = items[i];
      size_t k = i;
      size_t j = i - 1;
      while (comparator(&tmp, &items[j]))
      {
        items[k] = items[j];
        k = j;
        if (!(j--))
        {
          break;
        }
      }

      items[k] = tmp;
    }

    return;
  }
  else
  {
    int g = (n < 57) ? (2) : (0);
    for (; g < 6; g += 1)
    {
      size_t gap = kBrotliShellGaps[g];
      size_t i;
      for (i = gap; i < n; i += 1)
      {
        size_t j = i;
        HuffmanTree tmp = items[i];
        for (; (j >= gap) && comparator(&tmp, &items[j - gap]); j -= gap)
        {
          items[j] = items[j - gap];
        }

        items[j] = tmp;
      }

    }

  }
}

typedef struct BrotliDistanceCodeLimit
{
  uint32_t max_alphabet_size;
  uint32_t max_distance;
} BrotliDistanceCodeLimit;
inline static BrotliDistanceCodeLimit BrotliCalculateDistanceCodeLimit(uint32_t max_distance, uint32_t npostfix, uint32_t ndirect)
{
  BrotliDistanceCodeLimit result;
  (void) (&BrotliCalculateDistanceCodeLimit);
  if (max_distance <= ndirect)
  {
    result.max_alphabet_size = max_distance + 16;
    result.max_distance = max_distance;
    return result;
  }
  else
  {
    uint32_t forbidden_distance = max_distance + 1;
    uint32_t offset = (forbidden_distance - ndirect) - 1;
    uint32_t ndistbits = 0;
    uint32_t tmp;
    uint32_t half;
    uint32_t group;
    uint32_t postfix = (1u << npostfix) - 1;
    uint32_t extra;
    uint32_t start;
    offset = (offset >> npostfix) + 4;
    tmp = offset / 2;
    while (tmp != 0)
    {
      ndistbits += 1;
      tmp = tmp >> 1;
    }

    ndistbits -= 1;
    half = (offset >> ndistbits) & 1;
    group = ((ndistbits - 1) << 1) | half;
    if (group == 0)
    {
      result.max_alphabet_size = ndirect + 16;
      result.max_distance = ndirect;
      return result;
    }
    group -= 1;
    ndistbits = (group >> 1) + 1;
    extra = (1u << ndistbits) - 1;
    start = (1u << (ndistbits + 1)) - 4;
    start += (group & 1) << ndistbits;
    result.max_alphabet_size = ((((group << npostfix) | postfix) + ndirect) + 16) + 1;
    result.max_distance = ((((start + extra) << npostfix) + postfix) + ndirect) + 1;
    return result;
  }
}

typedef struct 
{
  uint16_t offset;
  uint8_t nbits;
} BrotliPrefixCodeRange;
extern const BrotliPrefixCodeRange _kBrotliPrefixCodeRanges[26];
const size_t kBrotliShellGaps[] = {132, 57, 23, 10, 4, 1};
int BrotliSetDepth(int p0, HuffmanTree *pool, uint8_t *depth, int max_depth)
{
  int stack[16];
  int level = 0;
  int p = p0;
  ;
  stack[0] = -1;
  while (1)
  {
    if (pool[p].index_left_ >= 0)
    {
      level += 1;
      if (level > max_depth)
      {
        return 0;
      }
      stack[level] = pool[p].index_right_or_value_;
      p = pool[p].index_left_;
      continue;
    }
    else
    {
      depth[pool[p].index_right_or_value_] = (uint8_t) level;
    }
    while ((level >= 0) && (stack[level] == (-1)))
    {
      level -= 1;
    }

    if (level < 0)
    {
      return 1;
    }
    p = stack[level];
    stack[level] = -1;
  }

}

inline static int SortHuffmanTree(const HuffmanTree *v0, const HuffmanTree *v1)
{
  if (v0->total_count_ != v1->total_count_)
  {
    return (!(!(v0->total_count_ < v1->total_count_))) ? (1) : (0);
  }
  return (!(!(v0->index_right_or_value_ > v1->index_right_or_value_))) ? (1) : (0);
}

void BrotliCreateHuffmanTree(const uint32_t *data, const size_t length, const int tree_limit, HuffmanTree *tree, uint8_t *depth)
{
  uint32_t count_limit;
  HuffmanTree sentinel;
  InitHuffmanTree(&sentinel, ~((uint32_t) 0), -1, -1);
  for (count_limit = 1;; count_limit *= 2)
  {
    helper_BrotliCreateHuffmanTree_1(data, length, tree_limit, tree, depth, count_limit, sentinel);
  }

}

static void Reverse(uint8_t *v, size_t start, size_t end)
{
  end -= 1;
  while (start < end)
  {
    uint8_t tmp = v[start];
    v[start] = v[end];
    v[end] = tmp;
    start += 1;
    end -= 1;
  }

}

static void BrotliWriteHuffmanTreeRepetitions(const uint8_t previous_value, const uint8_t value, size_t repetitions, size_t *tree_size, uint8_t *tree, uint8_t *extra_bits_data)
{
  ;
  if (previous_value != value)
  {
    tree[*tree_size] = value;
    extra_bits_data[*tree_size] = 0;
    *tree_size += 1;
    repetitions -= 1;
  }
  if (repetitions == 7)
  {
    tree[*tree_size] = value;
    extra_bits_data[*tree_size] = 0;
    *tree_size += 1;
    repetitions -= 1;
  }
  if (repetitions < 3)
  {
    size_t i;
    for (i = 0; i < repetitions; i += 1)
    {
      tree[*tree_size] = value;
      extra_bits_data[*tree_size] = 0;
      *tree_size += 1;
    }

  }
  else
  {
    size_t start = *tree_size;
    repetitions -= 3;
    while (1)
    {
      tree[*tree_size] = 16;
      extra_bits_data[*tree_size] = repetitions & 0x3;
      *tree_size += 1;
      repetitions >>= 2;
      if (repetitions == 0)
      {
        break;
      }
      repetitions -= 1;
    }

    Reverse(tree, start, *tree_size);
    Reverse(extra_bits_data, start, *tree_size);
  }
}

static void BrotliWriteHuffmanTreeRepetitionsZeros(size_t repetitions, size_t *tree_size, uint8_t *tree, uint8_t *extra_bits_data)
{
  if (repetitions == 11)
  {
    tree[*tree_size] = 0;
    extra_bits_data[*tree_size] = 0;
    *tree_size += 1;
    repetitions -= 1;
  }
  if (repetitions < 3)
  {
    size_t i;
    for (i = 0; i < repetitions; i += 1)
    {
      tree[*tree_size] = 0;
      extra_bits_data[*tree_size] = 0;
      *tree_size += 1;
    }

  }
  else
  {
    size_t start = *tree_size;
    repetitions -= 3;
    while (1)
    {
      tree[*tree_size] = 17;
      extra_bits_data[*tree_size] = repetitions & 0x7;
      *tree_size += 1;
      repetitions >>= 3;
      if (repetitions == 0)
      {
        break;
      }
      repetitions -= 1;
    }

    Reverse(tree, start, *tree_size);
    Reverse(extra_bits_data, start, *tree_size);
  }
}

void BrotliOptimizeHuffmanCountsForRle(size_t length, uint32_t *counts, uint8_t *good_for_rle)
{
  size_t nonzero_count = 0;
  size_t stride;
  size_t limit;
  size_t sum;
  const size_t streak_limit = 1240;
  size_t i;
  for (i = 0; i < length; i += 1)
  {
    if (counts[i])
    {
      nonzero_count += 1;
    }
  }

  if (nonzero_count < 16)
  {
    return;
  }
  while ((length != 0) && (counts[length - 1] == 0))
  {
    length -= 1;
  }

  if (length == 0)
  {
    return;
  }
  {
    helper_BrotliOptimizeHuffmanCountsForRle_2(&i, length, counts);
  }
  memset(good_for_rle, 0, length);
  {
    helper_BrotliOptimizeHuffmanCountsForRle_1(&i, length, counts, good_for_rle);
  }
  stride = 0;
  limit = ((256 * ((counts[0] + counts[1]) + counts[2])) / 3) + 420;
  sum = 0;
  for (i = 0; i <= length; i += 1)
  {
    helper_BrotliOptimizeHuffmanCountsForRle_3(&stride, &limit, &sum, &i, length, counts, good_for_rle, streak_limit);
  }

}

static void DecideOverRleUse(const uint8_t *depth, const size_t length, int *use_rle_for_non_zero, int *use_rle_for_zero)
{
  size_t total_reps_zero = 0;
  size_t total_reps_non_zero = 0;
  size_t count_reps_zero = 1;
  size_t count_reps_non_zero = 1;
  size_t i;
  for (i = 0; i < length;)
  {
    const uint8_t value = depth[i];
    size_t reps = 1;
    size_t k;
    for (k = i + 1; (k < length) && (depth[k] == value); k += 1)
    {
      reps += 1;
    }

    if ((reps >= 3) && (value == 0))
    {
      total_reps_zero += reps;
      count_reps_zero += 1;
    }
    if ((reps >= 4) && (value != 0))
    {
      total_reps_non_zero += reps;
      count_reps_non_zero += 1;
    }
    i += reps;
  }

  *use_rle_for_non_zero = (!(!(total_reps_non_zero > (count_reps_non_zero * 2)))) ? (1) : (0);
  *use_rle_for_zero = (!(!(total_reps_zero > (count_reps_zero * 2)))) ? (1) : (0);
}

void BrotliWriteHuffmanTree(const uint8_t *depth, size_t length, size_t *tree_size, uint8_t *tree, uint8_t *extra_bits_data)
{
  uint8_t previous_value = 8;
  size_t i;
  int use_rle_for_non_zero = 0;
  int use_rle_for_zero = 0;
  size_t new_length = length;
  for (i = 0; i < length; i += 1)
  {
    if (depth[(length - i) - 1] == 0)
    {
      new_length -= 1;
    }
    else
    {
      break;
    }
  }

  if (length > 50)
  {
    DecideOverRleUse(depth, new_length, &use_rle_for_non_zero, &use_rle_for_zero);
  }
  for (i = 0; i < new_length;)
  {
    const uint8_t value = depth[i];
    size_t reps = 1;
    if (((value != 0) && use_rle_for_non_zero) || ((value == 0) && use_rle_for_zero))
    {
      size_t k;
      for (k = i + 1; (k < new_length) && (depth[k] == value); k += 1)
      {
        reps += 1;
      }

    }
    if (value == 0)
    {
      BrotliWriteHuffmanTreeRepetitionsZeros(reps, tree_size, tree, extra_bits_data);
    }
    else
    {
      BrotliWriteHuffmanTreeRepetitions(previous_value, value, reps, tree_size, tree, extra_bits_data);
      previous_value = value;
    }
    i += reps;
  }

}

static uint16_t BrotliReverseBits(size_t num_bits, uint16_t bits)
{
  static const size_t kLut[16] = {0x00, 0x08, 0x04, 0x0C, 0x02, 0x0A, 0x06, 0x0E, 0x01, 0x09, 0x05, 0x0D, 0x03, 0x0B, 0x07, 0x0F};
  size_t retval = kLut[bits & 0x0F];
  size_t i;
  for (i = 4; i < num_bits; i += 4)
  {
    retval <<= 4;
    bits = (uint16_t) (bits >> 4);
    retval |= kLut[bits & 0x0F];
  }

  retval >>= (0 - num_bits) & 0x03;
  return (uint16_t) retval;
}

void BrotliConvertBitDepthsToSymbols(const uint8_t *depth, size_t len, uint16_t *bits)
{
  uint16_t bl_count[16] = {0};
  uint16_t next_code[16];
  size_t i;
  int code = 0;
  for (i = 0; i < len; i += 1)
  {
    bl_count[depth[i]] += 1;
  }

  bl_count[0] = 0;
  next_code[0] = 0;
  for (i = 1; i < 16; i += 1)
  {
    code = (code + bl_count[i - 1]) << 1;
    next_code[i] = (uint16_t) code;
  }

  for (i = 0; i < len; i += 1)
  {
    if (depth[i])
    {
      bits[i] = BrotliReverseBits(depth[i], next_code[depth[i]]++);
    }
  }

}


typedef void *(*brotli_alloc_func)(void *opaque, size_t size);
typedef void (*brotli_free_func)(void *opaque, void *address);
inline static uint16_t BrotliUnalignedRead16(const void *p)
{
  return *((const uint16_t *) p);
}

inline static uint32_t BrotliUnalignedRead32(const void *p)
{
  return *((const uint32_t *) p);
}

inline static uint64_t BrotliUnalignedRead64(const void *p)
{
  return *((const uint64_t *) p);
}

inline static void BrotliUnalignedWrite64(void *p, uint64_t v)
{
  *((uint64_t *) p) = v;
}

inline static void BrotliRBit(void)
{
}

inline static double brotli_min_double(double a, double b)
{
  return (a < b) ? (a) : (b);
}

inline static double brotli_max_double(double a, double b)
{
  return (a > b) ? (a) : (b);
}

inline static float brotli_min_float(float a, float b)
{
  return (a < b) ? (a) : (b);
}

inline static float brotli_max_float(float a, float b)
{
  return (a > b) ? (a) : (b);
}

inline static int brotli_min_int(int a, int b)
{
  return (a < b) ? (a) : (b);
}

inline static int brotli_max_int(int a, int b)
{
  return (a > b) ? (a) : (b);
}

inline static size_t brotli_min_size_t(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}

inline static size_t brotli_max_size_t(size_t a, size_t b)
{
  return (a > b) ? (a) : (b);
}

inline static uint32_t brotli_min_uint32_t(uint32_t a, uint32_t b)
{
  return (a < b) ? (a) : (b);
}

inline static uint32_t brotli_max_uint32_t(uint32_t a, uint32_t b)
{
  return (a > b) ? (a) : (b);
}

inline static uint8_t brotli_min_uint8_t(uint8_t a, uint8_t b)
{
  return (a < b) ? (a) : (b);
}

inline static uint8_t brotli_max_uint8_t(uint8_t a, uint8_t b)
{
  return (a > b) ? (a) : (b);
}

void *BrotliDefaultAllocFunc(void *opaque, size_t size);
void BrotliDefaultFreeFunc(void *opaque, void *address);
inline static void BrotliSuppressUnusedFunctions(void)
{
  (void) (&BrotliSuppressUnusedFunctions);
  (void) (&BrotliUnalignedRead16);
  (void) (&BrotliUnalignedRead32);
  (void) (&BrotliUnalignedRead64);
  (void) (&BrotliUnalignedWrite64);
  (void) (&BrotliUnalignedRead16);
  (void) (&BrotliUnalignedRead32);
  (void) (&BrotliUnalignedRead64);
  (void) (&BrotliUnalignedWrite64);
  (void) (&BrotliRBit);
  (void) (&brotli_min_double);
  (void) (&brotli_max_double);
  (void) (&brotli_min_float);
  (void) (&brotli_max_float);
  (void) (&brotli_min_int);
  (void) (&brotli_max_int);
  (void) (&brotli_min_size_t);
  (void) (&brotli_max_size_t);
  (void) (&brotli_min_uint32_t);
  (void) (&brotli_max_uint32_t);
  (void) (&brotli_min_uint8_t);
  (void) (&brotli_max_uint8_t);
  (void) (&BrotliDefaultAllocFunc);
  (void) (&BrotliDefaultFreeFunc);
}

typedef struct HuffmanTree
{
  uint32_t total_count_;
  int16_t index_left_;
  int16_t index_right_or_value_;
} HuffmanTree;
inline static void InitHuffmanTree(HuffmanTree *self, uint32_t count, int16_t left, int16_t right)
{
  self->total_count_ = count;
  self->index_left_ = left;
  self->index_right_or_value_ = right;
}

int BrotliSetDepth(int p, HuffmanTree *pool, uint8_t *depth, int max_depth);
void BrotliCreateHuffmanTree(const uint32_t *data, const size_t length, const int tree_limit, HuffmanTree *tree, uint8_t *depth);
void BrotliOptimizeHuffmanCountsForRle(size_t length, uint32_t *counts, uint8_t *good_for_rle);
void BrotliWriteHuffmanTree(const uint8_t *depth, size_t num, size_t *tree_size, uint8_t *tree, uint8_t *extra_bits_data);
void BrotliConvertBitDepthsToSymbols(const uint8_t *depth, size_t len, uint16_t *bits);
extern const size_t kBrotliShellGaps[6];
typedef int (*HuffmanTreeComparator)(const HuffmanTree *, const HuffmanTree *);
inline static void SortHuffmanTreeItems(HuffmanTree *items, const size_t n, HuffmanTreeComparator comparator)
{
  if (n < 13)
  {
    size_t i;
    for (i = 1; i < n; i += 1)
    {
      HuffmanTree tmp = items[i];
      size_t k = i;
      size_t j = i - 1;
      while (comparator(&tmp, &items[j]))
      {
        items[k] = items[j];
        k = j;
        if (!(j--))
        {
          break;
        }
      }

      items[k] = tmp;
    }

    return;
  }
  else
  {
    int g = (n < 57) ? (2) : (0);
    for (; g < 6; g += 1)
    {
      size_t gap = kBrotliShellGaps[g];
      size_t i;
      for (i = gap; i < n; i += 1)
      {
        size_t j = i;
        HuffmanTree tmp = items[i];
        for (; (j >= gap) && comparator(&tmp, &items[j - gap]); j -= gap)
        {
          items[j] = items[j - gap];
        }

        items[j] = tmp;
      }

    }

  }
}

typedef struct BrotliDistanceCodeLimit
{
  uint32_t max_alphabet_size;
  uint32_t max_distance;
} BrotliDistanceCodeLimit;
inline static BrotliDistanceCodeLimit BrotliCalculateDistanceCodeLimit(uint32_t max_distance, uint32_t npostfix, uint32_t ndirect)
{
  BrotliDistanceCodeLimit result;
  (void) (&BrotliCalculateDistanceCodeLimit);
  if (max_distance <= ndirect)
  {
    result.max_alphabet_size = max_distance + 16;
    result.max_distance = max_distance;
    return result;
  }
  else
  {
    uint32_t forbidden_distance = max_distance + 1;
    uint32_t offset = (forbidden_distance - ndirect) - 1;
    uint32_t ndistbits = 0;
    uint32_t tmp;
    uint32_t half;
    uint32_t group;
    uint32_t postfix = (1u << npostfix) - 1;
    uint32_t extra;
    uint32_t start;
    offset = (offset >> npostfix) + 4;
    tmp = offset / 2;
    while (tmp != 0)
    {
      ndistbits += 1;
      tmp = tmp >> 1;
    }

    ndistbits -= 1;
    half = (offset >> ndistbits) & 1;
    group = ((ndistbits - 1) << 1) | half;
    if (group == 0)
    {
      result.max_alphabet_size = ndirect + 16;
      result.max_distance = ndirect;
      return result;
    }
    group -= 1;
    ndistbits = (group >> 1) + 1;
    extra = (1u << ndistbits) - 1;
    start = (1u << (ndistbits + 1)) - 4;
    start += (group & 1) << ndistbits;
    result.max_alphabet_size = ((((group << npostfix) | postfix) + ndirect) + 16) + 1;
    result.max_distance = ((((start + extra) << npostfix) + postfix) + ndirect) + 1;
    return result;
  }
}

typedef struct 
{
  uint16_t offset;
  uint8_t nbits;
} BrotliPrefixCodeRange;
extern const BrotliPrefixCodeRange _kBrotliPrefixCodeRanges[26];
const size_t kBrotliShellGaps[] = {132, 57, 23, 10, 4, 1};
int BrotliSetDepth(int p0, HuffmanTree *pool, uint8_t *depth, int max_depth)
{
  int stack[16];
  int level = 0;
  int p = p0;
  ;
  stack[0] = -1;
  while (1)
  {
    if (pool[p].index_left_ >= 0)
    {
      level += 1;
      if (level > max_depth)
      {
        return 0;
      }
      stack[level] = pool[p].index_right_or_value_;
      p = pool[p].index_left_;
      continue;
    }
    else
    {
      depth[pool[p].index_right_or_value_] = (uint8_t) level;
    }
    while ((level >= 0) && (stack[level] == (-1)))
    {
      level -= 1;
    }

    if (level < 0)
    {
      return 1;
    }
    p = stack[level];
    stack[level] = -1;
  }

}

inline static int SortHuffmanTree(const HuffmanTree *v0, const HuffmanTree *v1)
{
  if (v0->total_count_ != v1->total_count_)
  {
    return (!(!(v0->total_count_ < v1->total_count_))) ? (1) : (0);
  }
  return (!(!(v0->index_right_or_value_ > v1->index_right_or_value_))) ? (1) : (0);
}

void BrotliCreateHuffmanTree(const uint32_t *data, const size_t length, const int tree_limit, HuffmanTree *tree, uint8_t *depth)
{
  uint32_t count_limit;
  HuffmanTree sentinel;
  InitHuffmanTree(&sentinel, ~((uint32_t) 0), -1, -1);
  for (count_limit = 1;; count_limit *= 2)
  {
    size_t n = 0;
    size_t i;
    size_t j;
    size_t k;
    for (i = length; i != 0;)
    {
      i -= 1;
      if (data[i])
      {
        const uint32_t count = brotli_max_uint32_t(data[i], count_limit);
        InitHuffmanTree(&tree[n], count, -1, (int16_t) i);
        n += 1;
      }
    }

    if (n == 1)
    {
      depth[tree[0].index_right_or_value_] = 1;
      break;
    }
    SortHuffmanTreeItems(tree, n, SortHuffmanTree);
    tree[n] = sentinel;
    tree[n + 1] = sentinel;
    i = 0;
    j = n + 1;
    for (k = n - 1; k != 0; k -= 1)
    {
      size_t left;
      size_t right;
      if (tree[i].total_count_ <= tree[j].total_count_)
      {
        left = i;
        i += 1;
      }
      else
      {
        left = j;
        j += 1;
      }
      if (tree[i].total_count_ <= tree[j].total_count_)
      {
        right = i;
        i += 1;
      }
      else
      {
        right = j;
        j += 1;
      }
      {
        size_t j_end = (2 * n) - k;
        tree[j_end].total_count_ = tree[left].total_count_ + tree[right].total_count_;
        tree[j_end].index_left_ = (int16_t) left;
        tree[j_end].index_right_or_value_ = (int16_t) right;
        tree[j_end + 1] = sentinel;
      }
    }

    if (BrotliSetDepth((int) ((2 * n) - 1), &tree[0], depth, tree_limit))
    {
      break;
    }
  }

}

static void Reverse(uint8_t *v, size_t start, size_t end)
{
  end -= 1;
  while (start < end)
  {
    uint8_t tmp = v[start];
    v[start] = v[end];
    v[end] = tmp;
    start += 1;
    end -= 1;
  }

}

static void BrotliWriteHuffmanTreeRepetitions(const uint8_t previous_value, const uint8_t value, size_t repetitions, size_t *tree_size, uint8_t *tree, uint8_t *extra_bits_data)
{
  ;
  if (previous_value != value)
  {
    tree[*tree_size] = value;
    extra_bits_data[*tree_size] = 0;
    *tree_size += 1;
    repetitions -= 1;
  }
  if (repetitions == 7)
  {
    tree[*tree_size] = value;
    extra_bits_data[*tree_size] = 0;
    *tree_size += 1;
    repetitions -= 1;
  }
  if (repetitions < 3)
  {
    size_t i;
    for (i = 0; i < repetitions; i += 1)
    {
      tree[*tree_size] = value;
      extra_bits_data[*tree_size] = 0;
      *tree_size += 1;
    }

  }
  else
  {
    size_t start = *tree_size;
    repetitions -= 3;
    while (1)
    {
      tree[*tree_size] = 16;
      extra_bits_data[*tree_size] = repetitions & 0x3;
      *tree_size += 1;
      repetitions >>= 2;
      if (repetitions == 0)
      {
        break;
      }
      repetitions -= 1;
    }

    Reverse(tree, start, *tree_size);
    Reverse(extra_bits_data, start, *tree_size);
  }
}

static void BrotliWriteHuffmanTreeRepetitionsZeros(size_t repetitions, size_t *tree_size, uint8_t *tree, uint8_t *extra_bits_data)
{
  if (repetitions == 11)
  {
    tree[*tree_size] = 0;
    extra_bits_data[*tree_size] = 0;
    *tree_size += 1;
    repetitions -= 1;
  }
  if (repetitions < 3)
  {
    size_t i;
    for (i = 0; i < repetitions; i += 1)
    {
      tree[*tree_size] = 0;
      extra_bits_data[*tree_size] = 0;
      *tree_size += 1;
    }

  }
  else
  {
    size_t start = *tree_size;
    repetitions -= 3;
    while (1)
    {
      tree[*tree_size] = 17;
      extra_bits_data[*tree_size] = repetitions & 0x7;
      *tree_size += 1;
      repetitions >>= 3;
      if (repetitions == 0)
      {
        break;
      }
      repetitions -= 1;
    }

    Reverse(tree, start, *tree_size);
    Reverse(extra_bits_data, start, *tree_size);
  }
}

void BrotliOptimizeHuffmanCountsForRle(size_t length, uint32_t *counts, uint8_t *good_for_rle)
{
  size_t nonzero_count = 0;
  size_t stride;
  size_t limit;
  size_t sum;
  const size_t streak_limit = 1240;
  size_t i;
  for (i = 0; i < length; i += 1)
  {
    if (counts[i])
    {
      nonzero_count += 1;
    }
  }

  if (nonzero_count < 16)
  {
    return;
  }
  while ((length != 0) && (counts[length - 1] == 0))
  {
    length -= 1;
  }

  if (length == 0)
  {
    return;
  }
  {
    size_t nonzeros = 0;
    uint32_t smallest_nonzero = 1 << 30;
    for (i = 0; i < length; i += 1)
    {
      if (counts[i] != 0)
      {
        nonzeros += 1;
        if (smallest_nonzero > counts[i])
        {
          smallest_nonzero = counts[i];
        }
      }
    }

    if (nonzeros < 5)
    {
      return;
    }
    if (smallest_nonzero < 4)
    {
      size_t zeros = length - nonzeros;
      if (zeros < 6)
      {
        for (i = 1; i < (length - 1); i += 1)
        {
          if (((counts[i - 1] != 0) && (counts[i] == 0)) && (counts[i + 1] != 0))
          {
            counts[i] = 1;
          }
        }

      }
    }
    if (nonzeros < 28)
    {
      return;
    }
  }
  memset(good_for_rle, 0, length);
  {
    uint32_t symbol = counts[0];
    size_t step = 0;
    for (i = 0; i <= length; i += 1)
    {
      if ((i == length) || (counts[i] != symbol))
      {
        if (((symbol == 0) && (step >= 5)) || ((symbol != 0) && (step >= 7)))
        {
          size_t k;
          for (k = 0; k < step; k += 1)
          {
            good_for_rle[(i - k) - 1] = 1;
          }

        }
        step = 1;
        if (i != length)
        {
          symbol = counts[i];
        }
      }
      else
      {
        step += 1;
      }
    }

  }
  stride = 0;
  limit = ((256 * ((counts[0] + counts[1]) + counts[2])) / 3) + 420;
  sum = 0;
  for (i = 0; i <= length; i += 1)
  {
    if ((((i == length) || good_for_rle[i]) || ((i != 0) && good_for_rle[i - 1])) || ((((256 * counts[i]) - limit) + streak_limit) >= (2 * streak_limit)))
    {
      if ((stride >= 4) || ((stride >= 3) && (sum == 0)))
      {
        size_t k;
        size_t count = (sum + (stride / 2)) / stride;
        if (count == 0)
        {
          count = 1;
        }
        if (sum == 0)
        {
          count = 0;
        }
        for (k = 0; k < stride; k += 1)
        {
          counts[(i - k) - 1] = (uint32_t) count;
        }

      }
      stride = 0;
      sum = 0;
      if (i < (length - 2))
      {
        limit = ((256 * ((counts[i] + counts[i + 1]) + counts[i + 2])) / 3) + 420;
      }
      else
        if (i < length)
      {
        limit = 256 * counts[i];
      }
      else
      {
        limit = 0;
      }
    }
    stride += 1;
    if (i != length)
    {
      sum += counts[i];
      if (stride >= 4)
      {
        limit = ((256 * sum) + (stride / 2)) / stride;
      }
      if (stride == 4)
      {
        limit += 120;
      }
    }
  }

}

static void DecideOverRleUse(const uint8_t *depth, const size_t length, int *use_rle_for_non_zero, int *use_rle_for_zero)
{
  size_t total_reps_zero = 0;
  size_t total_reps_non_zero = 0;
  size_t count_reps_zero = 1;
  size_t count_reps_non_zero = 1;
  size_t i;
  for (i = 0; i < length;)
  {
    const uint8_t value = depth[i];
    size_t reps = 1;
    size_t k;
    for (k = i + 1; (k < length) && (depth[k] == value); k += 1)
    {
      reps += 1;
    }

    if ((reps >= 3) && (value == 0))
    {
      total_reps_zero += reps;
      count_reps_zero += 1;
    }
    if ((reps >= 4) && (value != 0))
    {
      total_reps_non_zero += reps;
      count_reps_non_zero += 1;
    }
    i += reps;
  }

  *use_rle_for_non_zero = (!(!(total_reps_non_zero > (count_reps_non_zero * 2)))) ? (1) : (0);
  *use_rle_for_zero = (!(!(total_reps_zero > (count_reps_zero * 2)))) ? (1) : (0);
}

void BrotliWriteHuffmanTree(const uint8_t *depth, size_t length, size_t *tree_size, uint8_t *tree, uint8_t *extra_bits_data)
{
  uint8_t previous_value = 8;
  size_t i;
  int use_rle_for_non_zero = 0;
  int use_rle_for_zero = 0;
  size_t new_length = length;
  for (i = 0; i < length; i += 1)
  {
    if (depth[(length - i) - 1] == 0)
    {
      new_length -= 1;
    }
    else
    {
      break;
    }
  }

  if (length > 50)
  {
    DecideOverRleUse(depth, new_length, &use_rle_for_non_zero, &use_rle_for_zero);
  }
  for (i = 0; i < new_length;)
  {
    const uint8_t value = depth[i];
    size_t reps = 1;
    if (((value != 0) && use_rle_for_non_zero) || ((value == 0) && use_rle_for_zero))
    {
      size_t k;
      for (k = i + 1; (k < new_length) && (depth[k] == value); k += 1)
      {
        reps += 1;
      }

    }
    if (value == 0)
    {
      BrotliWriteHuffmanTreeRepetitionsZeros(reps, tree_size, tree, extra_bits_data);
    }
    else
    {
      BrotliWriteHuffmanTreeRepetitions(previous_value, value, reps, tree_size, tree, extra_bits_data);
      previous_value = value;
    }
    i += reps;
  }

}

static uint16_t BrotliReverseBits(size_t num_bits, uint16_t bits)
{
  static const size_t kLut[16] = {0x00, 0x08, 0x04, 0x0C, 0x02, 0x0A, 0x06, 0x0E, 0x01, 0x09, 0x05, 0x0D, 0x03, 0x0B, 0x07, 0x0F};
  size_t retval = kLut[bits & 0x0F];
  size_t i;
  for (i = 4; i < num_bits; i += 4)
  {
    retval <<= 4;
    bits = (uint16_t) (bits >> 4);
    retval |= kLut[bits & 0x0F];
  }

  retval >>= (0 - num_bits) & 0x03;
  return (uint16_t) retval;
}

void BrotliConvertBitDepthsToSymbols(const uint8_t *depth, size_t len, uint16_t *bits)
{
  uint16_t bl_count[16] = {0};
  uint16_t next_code[16];
  size_t i;
  int code = 0;
  for (i = 0; i < len; i += 1)
  {
    bl_count[depth[i]] += 1;
  }

  bl_count[0] = 0;
  next_code[0] = 0;
  for (i = 1; i < 16; i += 1)
  {
    code = (code + bl_count[i - 1]) << 1;
    next_code[i] = (uint16_t) code;
  }

  for (i = 0; i < len; i += 1)
  {
    if (depth[i])
    {
      bits[i] = BrotliReverseBits(depth[i], next_code[depth[i]]++);
    }
  }

}

void helper_BrotliCreateHuffmanTree_1(const uint32_t * const data, const size_t length, const int tree_limit, HuffmanTree * const tree, uint8_t * const depth, uint32_t count_limit, HuffmanTree sentinel)
{
  size_t n = 0;
  size_t i;
  size_t j;
  size_t k;
  for (i = length; i != 0;)
  {
    i -= 1;
    if (data[i])
    {
      const uint32_t count = brotli_max_uint32_t(data[i], count_limit);
      InitHuffmanTree(&tree[n], count, -1, (int16_t) i);
      n += 1;
    }
  }

  if (n == 1)
  {
    depth[tree[0].index_right_or_value_] = 1;
    break;
  }
  SortHuffmanTreeItems(tree, n, SortHuffmanTree);
  tree[n] = sentinel;
  tree[n + 1] = sentinel;
  i = 0;
  j = n + 1;
  for (k = n - 1; k != 0; k -= 1)
  {
    helper_helper_BrotliCreateHuffmanTree_1_1(&i, &j, tree, sentinel, n, k);
  }

  if (BrotliSetDepth((int) ((2 * n) - 1), &tree[0], depth, tree_limit))
  {
    break;
  }
}

void helper_BrotliOptimizeHuffmanCountsForRle_1(size_t * const i_ref, size_t length, uint32_t * const counts, uint8_t * const good_for_rle)
{
  size_t i = *i_ref;
  uint32_t symbol = counts[0];
  size_t step = 0;
  for (i = 0; i <= length; i += 1)
  {
    if ((i == length) || (counts[i] != symbol))
    {
      if (((symbol == 0) && (step >= 5)) || ((symbol != 0) && (step >= 7)))
      {
        size_t k;
        for (k = 0; k < step; k += 1)
        {
          good_for_rle[(i - k) - 1] = 1;
        }

      }
      step = 1;
      if (i != length)
      {
        symbol = counts[i];
      }
    }
    else
    {
      step += 1;
    }
  }

  *i_ref = i;
}

void helper_BrotliOptimizeHuffmanCountsForRle_2(size_t * const i_ref, size_t length, uint32_t * const counts)
{
  size_t i = *i_ref;
  size_t nonzeros = 0;
  uint32_t smallest_nonzero = 1 << 30;
  for (i = 0; i < length; i += 1)
  {
    if (counts[i] != 0)
    {
      nonzeros += 1;
      if (smallest_nonzero > counts[i])
      {
        smallest_nonzero = counts[i];
      }
    }
  }

  if (nonzeros < 5)
  {
    return;
  }
  if (smallest_nonzero < 4)
  {
    size_t zeros = length - nonzeros;
    if (zeros < 6)
    {
      for (i = 1; i < (length - 1); i += 1)
      {
        if (((counts[i - 1] != 0) && (counts[i] == 0)) && (counts[i + 1] != 0))
        {
          counts[i] = 1;
        }
      }

    }
  }
  if (nonzeros < 28)
  {
    return;
  }
  *i_ref = i;
}

void helper_BrotliOptimizeHuffmanCountsForRle_3(size_t * const stride_ref, size_t * const limit_ref, size_t * const sum_ref, size_t * const i_ref, size_t length, uint32_t * const counts, uint8_t * const good_for_rle, const size_t streak_limit)
{
  size_t stride = *stride_ref;
  size_t limit = *limit_ref;
  size_t sum = *sum_ref;
  size_t i = *i_ref;
  if ((((i == length) || good_for_rle[i]) || ((i != 0) && good_for_rle[i - 1])) || ((((256 * counts[i]) - limit) + streak_limit) >= (2 * streak_limit)))
  {
    helper_helper_BrotliOptimizeHuffmanCountsForRle_3_1(&stride, &limit, &sum, &i, length, counts);
  }
  stride += 1;
  if (i != length)
  {
    sum += counts[i];
    if (stride >= 4)
    {
      limit = ((256 * sum) + (stride / 2)) / stride;
    }
    if (stride == 4)
    {
      limit += 120;
    }
  }
  *stride_ref = stride;
  *limit_ref = limit;
  *sum_ref = sum;
  *i_ref = i;
}

void helper_helper_BrotliCreateHuffmanTree_1_1(size_t * const i_ref, size_t * const j_ref, HuffmanTree * const tree, HuffmanTree sentinel, size_t n, size_t k)
{
  size_t i = *i_ref;
  size_t j = *j_ref;
  size_t left;
  size_t right;
  if (tree[i].total_count_ <= tree[j].total_count_)
  {
    left = i;
    i += 1;
  }
  else
  {
    left = j;
    j += 1;
  }
  if (tree[i].total_count_ <= tree[j].total_count_)
  {
    right = i;
    i += 1;
  }
  else
  {
    right = j;
    j += 1;
  }
  {
    size_t j_end = (2 * n) - k;
    tree[j_end].total_count_ = tree[left].total_count_ + tree[right].total_count_;
    tree[j_end].index_left_ = (int16_t) left;
    tree[j_end].index_right_or_value_ = (int16_t) right;
    tree[j_end + 1] = sentinel;
  }
  *i_ref = i;
  *j_ref = j;
}

void helper_helper_BrotliOptimizeHuffmanCountsForRle_3_1(size_t * const stride_ref, size_t * const limit_ref, size_t * const sum_ref, size_t * const i_ref, size_t length, uint32_t * const counts)
{
  size_t stride = *stride_ref;
  size_t limit = *limit_ref;
  size_t sum = *sum_ref;
  size_t i = *i_ref;
  if ((stride >= 4) || ((stride >= 3) && (sum == 0)))
  {
    size_t k;
    size_t count = (sum + (stride / 2)) / stride;
    if (count == 0)
    {
      count = 1;
    }
    if (sum == 0)
    {
      count = 0;
    }
    for (k = 0; k < stride; k += 1)
    {
      counts[(i - k) - 1] = (uint32_t) count;
    }

  }
  stride = 0;
  sum = 0;
  if (i < (length - 2))
  {
    limit = ((256 * ((counts[i] + counts[i + 1]) + counts[i + 2])) / 3) + 420;
  }
  else
    if (i < length)
  {
    limit = 256 * counts[i];
  }
  else
  {
    limit = 0;
  }
  *stride_ref = stride;
  *limit_ref = limit;
  *sum_ref = sum;
  *i_ref = i;
}

