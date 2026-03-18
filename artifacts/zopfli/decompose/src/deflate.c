static int ZopfliGetDistExtraBits(int dist)
{
  if (dist < 5)
  {
    return 0;
  }
  return (31 ^ __builtin_clz(dist - 1)) - 1;
}


/*** DEPENDENCIES:
***/


static int ZopfliGetDistExtraBitsValue(int dist)
{
  if (dist < 5)
  {
    return 0;
  }
  else
  {
    int l = 31 ^ __builtin_clz(dist - 1);
    return (dist - (1 + (1 << l))) & ((1 << (l - 1)) - 1);
  }
}


/*** DEPENDENCIES:
***/


static int ZopfliGetDistSymbol(int dist)
{
  if (dist < 5)
  {
    return dist - 1;
  }
  else
  {
    int l = 31 ^ __builtin_clz(dist - 1);
    int r = ((dist - 1) >> (l - 1)) & 1;
    return (l * 2) + r;
  }
}


/*** DEPENDENCIES:
***/


static int ZopfliGetLengthExtraBits(int l)
{
  static const int table[259] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0};
  return table[l];
}


/*** DEPENDENCIES:
***/


static int ZopfliGetLengthExtraBitsValue(int l)
{
  static const int table[259] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 0};
  return table[l];
}


/*** DEPENDENCIES:
***/


static int ZopfliGetLengthSymbol(int l)
{
  static const int table[259] = {0, 0, 0, 257, 258, 259, 260, 261, 262, 263, 264, 265, 265, 266, 266, 267, 267, 268, 268, 269, 269, 269, 269, 270, 270, 270, 270, 271, 271, 271, 271, 272, 272, 272, 272, 273, 273, 273, 273, 273, 273, 273, 273, 274, 274, 274, 274, 274, 274, 274, 274, 275, 275, 275, 275, 275, 275, 275, 275, 276, 276, 276, 276, 276, 276, 276, 276, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 285};
  return table[l];
}


/*** DEPENDENCIES:
***/


static int ZopfliGetLengthSymbolExtraBits(int s)
{
  static const int table[29] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0};
  return table[s - 257];
}


/*** DEPENDENCIES:
***/


static int ZopfliGetDistSymbolExtraBits(int s)
{
  static const int table[30] = {0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13};
  return table[s];
}


/*** DEPENDENCIES:
***/


static void AddBit(int bit, unsigned char *bp, unsigned char **out, size_t *outsize)
{
  if ((*bp) == 0)
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = 0;
    *outsize += 1;
  }
  ;
  (*out)[(*outsize) - 1] |= bit << (*bp);
  *bp = ((*bp) + 1) & 7;
}


/*** DEPENDENCIES:
***/


static void AddBits(unsigned symbol, unsigned length, unsigned char *bp, unsigned char **out, size_t *outsize)
{
  unsigned i;
  for (i = 0; i < length; i += 1)
  {
    unsigned bit = (symbol >> i) & 1;
    if ((*bp) == 0)
    {
      if (!((*outsize) & ((*outsize) - 1)))
      {
        *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
      }
      (*out)[*outsize] = 0;
      *outsize += 1;
    }
    ;
    (*out)[(*outsize) - 1] |= bit << (*bp);
    *bp = ((*bp) + 1) & 7;
  }

}


/*** DEPENDENCIES:
***/


static void AddHuffmanBits(unsigned symbol, unsigned length, unsigned char *bp, unsigned char **out, size_t *outsize)
{
  unsigned i;
  for (i = 0; i < length; i += 1)
  {
    unsigned bit = (symbol >> ((length - i) - 1)) & 1;
    if ((*bp) == 0)
    {
      if (!((*outsize) & ((*outsize) - 1)))
      {
        *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
      }
      (*out)[*outsize] = 0;
      *outsize += 1;
    }
    ;
    (*out)[(*outsize) - 1] |= bit << (*bp);
    *bp = ((*bp) + 1) & 7;
  }

}


/*** DEPENDENCIES:
***/


static void PatchDistanceCodesForBuggyDecoders(unsigned *d_lengths)
{
  int num_dist_codes = 0;
  int i;
  for (i = 0; i < 30; i += 1)
  {
    if (d_lengths[i])
    {
      num_dist_codes += 1;
    }
    if (num_dist_codes >= 2)
    {
      return;
    }
  }

  if (num_dist_codes == 0)
  {
    d_lengths[0] = (d_lengths[1] = 1);
  }
  else
    if (num_dist_codes == 1)
  {
    d_lengths[(d_lengths[0]) ? (1) : (0)] = 1;
  }
}


/*** DEPENDENCIES:
***/


static void GetFixedTree(unsigned *ll_lengths, unsigned *d_lengths)
{
  size_t i;
  for (i = 0; i < 144; i += 1)
    ll_lengths[i] = 8;

  for (i = 144; i < 256; i += 1)
    ll_lengths[i] = 9;

  for (i = 256; i < 280; i += 1)
    ll_lengths[i] = 7;

  for (i = 280; i < 288; i += 1)
    ll_lengths[i] = 8;

  for (i = 0; i < 32; i += 1)
    d_lengths[i] = 5;

}


/*** DEPENDENCIES:
***/


static size_t AbsDiff(size_t x, size_t y)
{
  if (x > y)
  {
    return x - y;
  }
  else
    return y - x;
}


/*** DEPENDENCIES:
***/


// hint:  ['rle_size_ref is a mutable refrence to size_t', 'rle_bits_size_ref is a mutable refrence to size_t', 'count_ref is a mutable refrence to unsigned']
void helper_helper_helper_EncodeTree_1_1_1(size_t * const rle_size_ref, size_t * const rle_bits_size_ref, unsigned * const count_ref, unsigned * const rle, unsigned * const rle_bits, size_t clcounts[19], int size_only)
{
  size_t rle_size = *rle_size_ref;
  size_t rle_bits_size = *rle_bits_size_ref;
  unsigned count = *count_ref;
  unsigned count2 = (count > 6) ? (6) : (count);
  if (!size_only)
  {
    {
      if (!((*(&rle_size)) & ((*(&rle_size)) - 1)))
      {
        rle = (rle_size == 0) ? (malloc(sizeof(*(*(&rle))))) : (realloc(*(&rle), (rle_size * 2) * (sizeof(*(*(&rle))))));
      }
      rle[rle_size] = 16;
      rle_size += 1;
    }
    ;
    {
      if (!((*(&rle_bits_size)) & ((*(&rle_bits_size)) - 1)))
      {
        rle_bits = (rle_bits_size == 0) ? (malloc(sizeof(*(*(&rle_bits))))) : (realloc(*(&rle_bits), (rle_bits_size * 2) * (sizeof(*(*(&rle_bits))))));
      }
      rle_bits[rle_bits_size] = count2 - 3;
      rle_bits_size += 1;
    }
    ;
  }
  clcounts[16] += 1;
  count -= count2;
  *rle_size_ref = rle_size;
  *rle_bits_size_ref = rle_bits_size;
  *count_ref = count;
}


/*** DEPENDENCIES:
***/


// hint:  ['rle_size_ref is a mutable refrence to size_t', 'rle_bits_size_ref is a mutable refrence to size_t', 'count_ref is a mutable refrence to unsigned']
void helper_helper_helper_EncodeTree_1_2_1(size_t * const rle_size_ref, size_t * const rle_bits_size_ref, unsigned * const count_ref, unsigned * const rle, unsigned * const rle_bits, size_t clcounts[19], int size_only)
{
  size_t rle_size = *rle_size_ref;
  size_t rle_bits_size = *rle_bits_size_ref;
  unsigned count = *count_ref;
  while (count >= 11)
  {
    unsigned count2 = (count > 138) ? (138) : (count);
    if (!size_only)
    {
      {
        if (!((*(&rle_size)) & ((*(&rle_size)) - 1)))
        {
          rle = (rle_size == 0) ? (malloc(sizeof(*(*(&rle))))) : (realloc(*(&rle), (rle_size * 2) * (sizeof(*(*(&rle))))));
        }
        rle[rle_size] = 18;
        rle_size += 1;
      }
      ;
      {
        if (!((*(&rle_bits_size)) & ((*(&rle_bits_size)) - 1)))
        {
          rle_bits = (rle_bits_size == 0) ? (malloc(sizeof(*(*(&rle_bits))))) : (realloc(*(&rle_bits), (rle_bits_size * 2) * (sizeof(*(*(&rle_bits))))));
        }
        rle_bits[rle_bits_size] = count2 - 11;
        rle_bits_size += 1;
      }
      ;
    }
    clcounts[18] += 1;
    count -= count2;
  }

  *rle_size_ref = rle_size;
  *rle_bits_size_ref = rle_bits_size;
  *count_ref = count;
}


/*** DEPENDENCIES:
***/


// hint:  ['rle_size_ref is a mutable refrence to size_t', 'rle_bits_size_ref is a mutable refrence to size_t', 'count_ref is a mutable refrence to unsigned']
void helper_helper_helper_EncodeTree_1_2_2(size_t * const rle_size_ref, size_t * const rle_bits_size_ref, unsigned * const count_ref, unsigned * const rle, unsigned * const rle_bits, size_t clcounts[19], int size_only)
{
  size_t rle_size = *rle_size_ref;
  size_t rle_bits_size = *rle_bits_size_ref;
  unsigned count = *count_ref;
  while (count >= 3)
  {
    unsigned count2 = (count > 10) ? (10) : (count);
    if (!size_only)
    {
      {
        if (!((*(&rle_size)) & ((*(&rle_size)) - 1)))
        {
          rle = (rle_size == 0) ? (malloc(sizeof(*(*(&rle))))) : (realloc(*(&rle), (rle_size * 2) * (sizeof(*(*(&rle))))));
        }
        rle[rle_size] = 17;
        rle_size += 1;
      }
      ;
      {
        if (!((*(&rle_bits_size)) & ((*(&rle_bits_size)) - 1)))
        {
          rle_bits = (rle_bits_size == 0) ? (malloc(sizeof(*(*(&rle_bits))))) : (realloc(*(&rle_bits), (rle_bits_size * 2) * (sizeof(*(*(&rle_bits))))));
        }
        rle_bits[rle_bits_size] = count2 - 3;
        rle_bits_size += 1;
      }
      ;
    }
    clcounts[17] += 1;
    count -= count2;
  }

  *rle_size_ref = rle_size;
  *rle_bits_size_ref = rle_bits_size;
  *count_ref = count;
}


/*** DEPENDENCIES:
***/


// hint:  ['rle_size_ref is a mutable refrence to size_t', 'rle_bits_size_ref is a mutable refrence to size_t', 'count_ref is a mutable refrence to unsigned']
void helper_helper_EncodeTree_1_2(size_t * const rle_size_ref, size_t * const rle_bits_size_ref, unsigned * const count_ref, int use_17, int use_18, unsigned * const rle, unsigned * const rle_bits, size_t clcounts[19], int size_only)
{
  size_t rle_size = *rle_size_ref;
  size_t rle_bits_size = *rle_bits_size_ref;
  unsigned count = *count_ref;
  if (use_18)
  {
    helper_helper_helper_EncodeTree_1_2_1(&rle_size, &rle_bits_size, &count, rle, rle_bits, clcounts, size_only);
  }
  if (use_17)
  {
    helper_helper_helper_EncodeTree_1_2_2(&rle_size, &rle_bits_size, &count, rle, rle_bits, clcounts, size_only);
  }
  *rle_size_ref = rle_size;
  *rle_bits_size_ref = rle_bits_size;
  *count_ref = count;
}


/*** DEPENDENCIES:
void helper_helper_helper_EncodeTree_1_2_2(size_t * const rle_size_ref, size_t * const rle_bits_size_ref, unsigned * const count_ref, unsigned * const rle, unsigned * const rle_bits, size_t clcounts[19], int size_only)
{
  size_t rle_size = *rle_size_ref;
  size_t rle_bits_size = *rle_bits_size_ref;
  unsigned count = *count_ref;
  while (count >= 3)
  {
    unsigned count2 = (count > 10) ? (10) : (count);
    if (!size_only)
    {
      {
        if (!((*(&rle_size)) & ((*(&rle_size)) - 1)))
        {
          rle = (rle_size == 0) ? (malloc(sizeof(*(*(&rle))))) : (realloc(*(&rle), (rle_size * 2) * (sizeof(*(*(&rle))))));
        }
        rle[rle_size] = 17;
        rle_size += 1;
      }
      ;
      {
        if (!((*(&rle_bits_size)) & ((*(&rle_bits_size)) - 1)))
        {
          rle_bits = (rle_bits_size == 0) ? (malloc(sizeof(*(*(&rle_bits))))) : (realloc(*(&rle_bits), (rle_bits_size * 2) * (sizeof(*(*(&rle_bits))))));
        }
        rle_bits[rle_bits_size] = count2 - 3;
        rle_bits_size += 1;
      }
      ;
    }
    clcounts[17] += 1;
    count -= count2;
  }

  *rle_size_ref = rle_size;
  *rle_bits_size_ref = rle_bits_size;
  *count_ref = count;
}


----------------------------
void helper_helper_helper_EncodeTree_1_2_1(size_t * const rle_size_ref, size_t * const rle_bits_size_ref, unsigned * const count_ref, unsigned * const rle, unsigned * const rle_bits, size_t clcounts[19], int size_only)
{
  size_t rle_size = *rle_size_ref;
  size_t rle_bits_size = *rle_bits_size_ref;
  unsigned count = *count_ref;
  while (count >= 11)
  {
    unsigned count2 = (count > 138) ? (138) : (count);
    if (!size_only)
    {
      {
        if (!((*(&rle_size)) & ((*(&rle_size)) - 1)))
        {
          rle = (rle_size == 0) ? (malloc(sizeof(*(*(&rle))))) : (realloc(*(&rle), (rle_size * 2) * (sizeof(*(*(&rle))))));
        }
        rle[rle_size] = 18;
        rle_size += 1;
      }
      ;
      {
        if (!((*(&rle_bits_size)) & ((*(&rle_bits_size)) - 1)))
        {
          rle_bits = (rle_bits_size == 0) ? (malloc(sizeof(*(*(&rle_bits))))) : (realloc(*(&rle_bits), (rle_bits_size * 2) * (sizeof(*(*(&rle_bits))))));
        }
        rle_bits[rle_bits_size] = count2 - 11;
        rle_bits_size += 1;
      }
      ;
    }
    clcounts[18] += 1;
    count -= count2;
  }

  *rle_size_ref = rle_size;
  *rle_bits_size_ref = rle_bits_size;
  *count_ref = count;
}


----------------------------
***/


// hint:  ['rle_size_ref is a mutable refrence to size_t', 'rle_bits_size_ref is a mutable refrence to size_t', 'symbol_ref is a mutable refrence to unsigned char', 'count_ref is a mutable refrence to unsigned']
void helper_helper_EncodeTree_1_1(size_t * const rle_size_ref, size_t * const rle_bits_size_ref, unsigned char * const symbol_ref, unsigned * const count_ref, unsigned * const rle, unsigned * const rle_bits, size_t clcounts[19], int size_only)
{
  size_t rle_size = *rle_size_ref;
  size_t rle_bits_size = *rle_bits_size_ref;
  unsigned char symbol = *symbol_ref;
  unsigned count = *count_ref;
  count -= 1;
  clcounts[symbol] += 1;
  if (!size_only)
  {
    {
      if (!((*(&rle_size)) & ((*(&rle_size)) - 1)))
      {
        rle = (rle_size == 0) ? (malloc(sizeof(*(*(&rle))))) : (realloc(*(&rle), (rle_size * 2) * (sizeof(*(*(&rle))))));
      }
      rle[rle_size] = symbol;
      rle_size += 1;
    }
    ;
    {
      if (!((*(&rle_bits_size)) & ((*(&rle_bits_size)) - 1)))
      {
        rle_bits = (rle_bits_size == 0) ? (malloc(sizeof(*(*(&rle_bits))))) : (realloc(*(&rle_bits), (rle_bits_size * 2) * (sizeof(*(*(&rle_bits))))));
      }
      rle_bits[rle_bits_size] = 0;
      rle_bits_size += 1;
    }
    ;
  }
  while (count >= 3)
  {
    helper_helper_helper_EncodeTree_1_1_1(&rle_size, &rle_bits_size, &count, rle, rle_bits, clcounts, size_only);
  }

  *rle_size_ref = rle_size;
  *rle_bits_size_ref = rle_bits_size;
  *symbol_ref = symbol;
  *count_ref = count;
}


/*** DEPENDENCIES:
void helper_helper_helper_EncodeTree_1_1_1(size_t * const rle_size_ref, size_t * const rle_bits_size_ref, unsigned * const count_ref, unsigned * const rle, unsigned * const rle_bits, size_t clcounts[19], int size_only)
{
  size_t rle_size = *rle_size_ref;
  size_t rle_bits_size = *rle_bits_size_ref;
  unsigned count = *count_ref;
  unsigned count2 = (count > 6) ? (6) : (count);
  if (!size_only)
  {
    {
      if (!((*(&rle_size)) & ((*(&rle_size)) - 1)))
      {
        rle = (rle_size == 0) ? (malloc(sizeof(*(*(&rle))))) : (realloc(*(&rle), (rle_size * 2) * (sizeof(*(*(&rle))))));
      }
      rle[rle_size] = 16;
      rle_size += 1;
    }
    ;
    {
      if (!((*(&rle_bits_size)) & ((*(&rle_bits_size)) - 1)))
      {
        rle_bits = (rle_bits_size == 0) ? (malloc(sizeof(*(*(&rle_bits))))) : (realloc(*(&rle_bits), (rle_bits_size * 2) * (sizeof(*(*(&rle_bits))))));
      }
      rle_bits[rle_bits_size] = count2 - 3;
      rle_bits_size += 1;
    }
    ;
  }
  clcounts[16] += 1;
  count -= count2;
  *rle_size_ref = rle_size;
  *rle_bits_size_ref = rle_bits_size;
  *count_ref = count;
}


----------------------------
***/


// hint:  ['rle_size_ref is a mutable refrence to size_t', 'rle_bits_size_ref is a mutable refrence to size_t', 'i_ref is a mutable refrence to size_t', 'j_ref is a mutable refrence to size_t']
void helper_EncodeTree_1(size_t * const rle_size_ref, size_t * const rle_bits_size_ref, size_t * const i_ref, size_t * const j_ref, const unsigned * const ll_lengths, const unsigned * const d_lengths, int use_16, int use_17, int use_18, unsigned lld_total, unsigned * const rle, unsigned * const rle_bits, unsigned hlit2, size_t clcounts[19], int size_only)
{
  size_t rle_size = *rle_size_ref;
  size_t rle_bits_size = *rle_bits_size_ref;
  size_t i = *i_ref;
  size_t j = *j_ref;
  unsigned char symbol = (i < hlit2) ? (ll_lengths[i]) : (d_lengths[i - hlit2]);
  unsigned count = 1;
  if (use_16 || ((symbol == 0) && (use_17 || use_18)))
  {
    for (j = i + 1; (j < lld_total) && (symbol == ((j < hlit2) ? (ll_lengths[j]) : (d_lengths[j - hlit2]))); j += 1)
    {
      count += 1;
    }

  }
  i += count - 1;
  if ((symbol == 0) && (count >= 3))
  {
    helper_helper_EncodeTree_1_2(&rle_size, &rle_bits_size, &count, use_17, use_18, rle, rle_bits, clcounts, size_only);
  }
  if (use_16 && (count >= 4))
  {
    helper_helper_EncodeTree_1_1(&rle_size, &rle_bits_size, &symbol, &count, rle, rle_bits, clcounts, size_only);
  }
  clcounts[symbol] += count;
  while (count > 0)
  {
    if (!size_only)
    {
      {
        if (!((*(&rle_size)) & ((*(&rle_size)) - 1)))
        {
          rle = (rle_size == 0) ? (malloc(sizeof(*(*(&rle))))) : (realloc(*(&rle), (rle_size * 2) * (sizeof(*(*(&rle))))));
        }
        rle[rle_size] = symbol;
        rle_size += 1;
      }
      ;
      {
        if (!((*(&rle_bits_size)) & ((*(&rle_bits_size)) - 1)))
        {
          rle_bits = (rle_bits_size == 0) ? (malloc(sizeof(*(*(&rle_bits))))) : (realloc(*(&rle_bits), (rle_bits_size * 2) * (sizeof(*(*(&rle_bits))))));
        }
        rle_bits[rle_bits_size] = 0;
        rle_bits_size += 1;
      }
      ;
    }
    count -= 1;
  }

  *rle_size_ref = rle_size;
  *rle_bits_size_ref = rle_bits_size;
  *i_ref = i;
  *j_ref = j;
}


/*** DEPENDENCIES:
void helper_helper_EncodeTree_1_2(size_t * const rle_size_ref, size_t * const rle_bits_size_ref, unsigned * const count_ref, int use_17, int use_18, unsigned * const rle, unsigned * const rle_bits, size_t clcounts[19], int size_only)
{
  size_t rle_size = *rle_size_ref;
  size_t rle_bits_size = *rle_bits_size_ref;
  unsigned count = *count_ref;
  if (use_18)
  {
    helper_helper_helper_EncodeTree_1_2_1(&rle_size, &rle_bits_size, &count, rle, rle_bits, clcounts, size_only);
  }
  if (use_17)
  {
    helper_helper_helper_EncodeTree_1_2_2(&rle_size, &rle_bits_size, &count, rle, rle_bits, clcounts, size_only);
  }
  *rle_size_ref = rle_size;
  *rle_bits_size_ref = rle_bits_size;
  *count_ref = count;
}


----------------------------
void helper_helper_EncodeTree_1_1(size_t * const rle_size_ref, size_t * const rle_bits_size_ref, unsigned char * const symbol_ref, unsigned * const count_ref, unsigned * const rle, unsigned * const rle_bits, size_t clcounts[19], int size_only)
{
  size_t rle_size = *rle_size_ref;
  size_t rle_bits_size = *rle_bits_size_ref;
  unsigned char symbol = *symbol_ref;
  unsigned count = *count_ref;
  count -= 1;
  clcounts[symbol] += 1;
  if (!size_only)
  {
    {
      if (!((*(&rle_size)) & ((*(&rle_size)) - 1)))
      {
        rle = (rle_size == 0) ? (malloc(sizeof(*(*(&rle))))) : (realloc(*(&rle), (rle_size * 2) * (sizeof(*(*(&rle))))));
      }
      rle[rle_size] = symbol;
      rle_size += 1;
    }
    ;
    {
      if (!((*(&rle_bits_size)) & ((*(&rle_bits_size)) - 1)))
      {
        rle_bits = (rle_bits_size == 0) ? (malloc(sizeof(*(*(&rle_bits))))) : (realloc(*(&rle_bits), (rle_bits_size * 2) * (sizeof(*(*(&rle_bits))))));
      }
      rle_bits[rle_bits_size] = 0;
      rle_bits_size += 1;
    }
    ;
  }
  while (count >= 3)
  {
    helper_helper_helper_EncodeTree_1_1_1(&rle_size, &rle_bits_size, &count, rle, rle_bits, clcounts, size_only);
  }

  *rle_size_ref = rle_size;
  *rle_bits_size_ref = rle_bits_size;
  *symbol_ref = symbol;
  *count_ref = count;
}


----------------------------
***/


static size_t EncodeTree(const unsigned *ll_lengths, const unsigned *d_lengths, int use_16, int use_17, int use_18, unsigned char *bp, unsigned char **out, size_t *outsize)
{
  unsigned lld_total;
  unsigned *rle = 0;
  unsigned *rle_bits = 0;
  size_t rle_size = 0;
  size_t rle_bits_size = 0;
  unsigned hlit = 29;
  unsigned hdist = 29;
  unsigned hclen;
  unsigned hlit2;
  size_t i;
  size_t j;
  size_t clcounts[19];
  unsigned clcl[19];
  unsigned clsymbols[19];
  static const unsigned order[19] = {16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15};
  int size_only = !out;
  size_t result_size = 0;
  for (i = 0; i < 19; i += 1)
    clcounts[i] = 0;

  while ((hlit > 0) && (ll_lengths[(257 + hlit) - 1] == 0))
    hlit--;

  hlit -= 1;
  while ((hdist > 0) && (d_lengths[(1 + hdist) - 1] == 0))
    hdist--;

  hdist -= 1;
  hlit2 = hlit + 257;
  lld_total = (hlit2 + hdist) + 1;
  for (i = 0; i < lld_total; i += 1)
  {
    helper_EncodeTree_1(&rle_size, &rle_bits_size, &i, &j, ll_lengths, d_lengths, use_16, use_17, use_18, lld_total, rle, rle_bits, hlit2, clcounts, size_only);
  }

  ZopfliCalculateBitLengths(clcounts, 19, 7, clcl);
  if (!size_only)
  {
    ZopfliLengthsToSymbols(clcl, 19, 7, clsymbols);
  }
  hclen = 15;
  while ((hclen > 0) && (clcounts[order[(hclen + 4) - 1]] == 0))
    hclen--;

  hclen -= 1;
  if (!size_only)
  {
    AddBits(hlit, 5, bp, out, outsize);
    AddBits(hdist, 5, bp, out, outsize);
    AddBits(hclen, 4, bp, out, outsize);
    for (i = 0; i < (hclen + 4); i += 1)
    {
      AddBits(clcl[order[i]], 3, bp, out, outsize);
    }

    for (i = 0; i < rle_size; i += 1)
    {
      unsigned symbol = clsymbols[rle[i]];
      AddHuffmanBits(symbol, clcl[rle[i]], bp, out, outsize);
      if (rle[i] == 16)
      {
        AddBits(rle_bits[i], 2, bp, out, outsize);
      }
      else
        if (rle[i] == 17)
      {
        AddBits(rle_bits[i], 3, bp, out, outsize);
      }
      else
        if (rle[i] == 18)
      {
        AddBits(rle_bits[i], 7, bp, out, outsize);
      }
    }

  }
  result_size += 14;
  result_size += (hclen + 4) * 3;
  for (i = 0; i < 19; i += 1)
  {
    result_size += clcl[i] * clcounts[i];
  }

  result_size += clcounts[16] * 2;
  result_size += clcounts[17] * 3;
  result_size += clcounts[18] * 7;
  free(rle);
  free(rle_bits);
  return result_size;
}


/*** DEPENDENCIES:
void ZopfliCalculateBitLengths(const size_t *count, size_t n, int maxbits, unsigned *bitlengths)
{
  int error = ZopfliLengthLimitedCodeLengths(count, n, maxbits, bitlengths);
  (void) error;
  assert(!error);
}


----------------------------
void ZopfliLengthsToSymbols(const unsigned *lengths, size_t n, unsigned maxbits, unsigned *symbols)
{
  size_t *bl_count = (size_t *) malloc((sizeof(size_t)) * (maxbits + 1));
  size_t *next_code = (size_t *) malloc((sizeof(size_t)) * (maxbits + 1));
  unsigned bits;
  unsigned i;
  unsigned code;
  for (i = 0; i < n; i += 1)
  {
    symbols[i] = 0;
  }

  for (bits = 0; bits <= maxbits; bits += 1)
  {
    bl_count[bits] = 0;
  }

  for (i = 0; i < n; i += 1)
  {
    assert(lengths[i] <= maxbits);
    bl_count[lengths[i]] += 1;
  }

  code = 0;
  bl_count[0] = 0;
  for (bits = 1; bits <= maxbits; bits += 1)
  {
    code = (code + bl_count[bits - 1]) << 1;
    next_code[bits] = code;
  }

  for (i = 0; i < n; i += 1)
  {
    unsigned len = lengths[i];
    if (len != 0)
    {
      symbols[i] = next_code[len];
      next_code[len] += 1;
    }
  }

  free(bl_count);
  free(next_code);
}


----------------------------
static void AddHuffmanBits(unsigned symbol, unsigned length, unsigned char *bp, unsigned char **out, size_t *outsize)
{
  unsigned i;
  for (i = 0; i < length; i += 1)
  {
    unsigned bit = (symbol >> ((length - i) - 1)) & 1;
    if ((*bp) == 0)
    {
      if (!((*outsize) & ((*outsize) - 1)))
      {
        *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
      }
      (*out)[*outsize] = 0;
      *outsize += 1;
    }
    ;
    (*out)[(*outsize) - 1] |= bit << (*bp);
    *bp = ((*bp) + 1) & 7;
  }

}


----------------------------
void helper_EncodeTree_1(size_t * const rle_size_ref, size_t * const rle_bits_size_ref, size_t * const i_ref, size_t * const j_ref, const unsigned * const ll_lengths, const unsigned * const d_lengths, int use_16, int use_17, int use_18, unsigned lld_total, unsigned * const rle, unsigned * const rle_bits, unsigned hlit2, size_t clcounts[19], int size_only)
{
  size_t rle_size = *rle_size_ref;
  size_t rle_bits_size = *rle_bits_size_ref;
  size_t i = *i_ref;
  size_t j = *j_ref;
  unsigned char symbol = (i < hlit2) ? (ll_lengths[i]) : (d_lengths[i - hlit2]);
  unsigned count = 1;
  if (use_16 || ((symbol == 0) && (use_17 || use_18)))
  {
    for (j = i + 1; (j < lld_total) && (symbol == ((j < hlit2) ? (ll_lengths[j]) : (d_lengths[j - hlit2]))); j += 1)
    {
      count += 1;
    }

  }
  i += count - 1;
  if ((symbol == 0) && (count >= 3))
  {
    helper_helper_EncodeTree_1_2(&rle_size, &rle_bits_size, &count, use_17, use_18, rle, rle_bits, clcounts, size_only);
  }
  if (use_16 && (count >= 4))
  {
    helper_helper_EncodeTree_1_1(&rle_size, &rle_bits_size, &symbol, &count, rle, rle_bits, clcounts, size_only);
  }
  clcounts[symbol] += count;
  while (count > 0)
  {
    if (!size_only)
    {
      {
        if (!((*(&rle_size)) & ((*(&rle_size)) - 1)))
        {
          rle = (rle_size == 0) ? (malloc(sizeof(*(*(&rle))))) : (realloc(*(&rle), (rle_size * 2) * (sizeof(*(*(&rle))))));
        }
        rle[rle_size] = symbol;
        rle_size += 1;
      }
      ;
      {
        if (!((*(&rle_bits_size)) & ((*(&rle_bits_size)) - 1)))
        {
          rle_bits = (rle_bits_size == 0) ? (malloc(sizeof(*(*(&rle_bits))))) : (realloc(*(&rle_bits), (rle_bits_size * 2) * (sizeof(*(*(&rle_bits))))));
        }
        rle_bits[rle_bits_size] = 0;
        rle_bits_size += 1;
      }
      ;
    }
    count -= 1;
  }

  *rle_size_ref = rle_size;
  *rle_bits_size_ref = rle_bits_size;
  *i_ref = i;
  *j_ref = j;
}


----------------------------
static void AddBits(unsigned symbol, unsigned length, unsigned char *bp, unsigned char **out, size_t *outsize)
{
  unsigned i;
  for (i = 0; i < length; i += 1)
  {
    unsigned bit = (symbol >> i) & 1;
    if ((*bp) == 0)
    {
      if (!((*outsize) & ((*outsize) - 1)))
      {
        *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
      }
      (*out)[*outsize] = 0;
      *outsize += 1;
    }
    ;
    (*out)[(*outsize) - 1] |= bit << (*bp);
    *bp = ((*bp) + 1) & 7;
  }

}


----------------------------
***/


static void AddDynamicTree(const unsigned *ll_lengths, const unsigned *d_lengths, unsigned char *bp, unsigned char **out, size_t *outsize)
{
  int i;
  int best = 0;
  size_t bestsize = 0;
  for (i = 0; i < 8; i += 1)
  {
    size_t size = EncodeTree(ll_lengths, d_lengths, i & 1, i & 2, i & 4, 0, 0, 0);
    if ((bestsize == 0) || (size < bestsize))
    {
      bestsize = size;
      best = i;
    }
  }

  EncodeTree(ll_lengths, d_lengths, best & 1, best & 2, best & 4, bp, out, outsize);
}


/*** DEPENDENCIES:
static size_t EncodeTree(const unsigned *ll_lengths, const unsigned *d_lengths, int use_16, int use_17, int use_18, unsigned char *bp, unsigned char **out, size_t *outsize)
{
  unsigned lld_total;
  unsigned *rle = 0;
  unsigned *rle_bits = 0;
  size_t rle_size = 0;
  size_t rle_bits_size = 0;
  unsigned hlit = 29;
  unsigned hdist = 29;
  unsigned hclen;
  unsigned hlit2;
  size_t i;
  size_t j;
  size_t clcounts[19];
  unsigned clcl[19];
  unsigned clsymbols[19];
  static const unsigned order[19] = {16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15};
  int size_only = !out;
  size_t result_size = 0;
  for (i = 0; i < 19; i += 1)
    clcounts[i] = 0;

  while ((hlit > 0) && (ll_lengths[(257 + hlit) - 1] == 0))
    hlit--;

  hlit -= 1;
  while ((hdist > 0) && (d_lengths[(1 + hdist) - 1] == 0))
    hdist--;

  hdist -= 1;
  hlit2 = hlit + 257;
  lld_total = (hlit2 + hdist) + 1;
  for (i = 0; i < lld_total; i += 1)
  {
    helper_EncodeTree_1(&rle_size, &rle_bits_size, &i, &j, ll_lengths, d_lengths, use_16, use_17, use_18, lld_total, rle, rle_bits, hlit2, clcounts, size_only);
  }

  ZopfliCalculateBitLengths(clcounts, 19, 7, clcl);
  if (!size_only)
  {
    ZopfliLengthsToSymbols(clcl, 19, 7, clsymbols);
  }
  hclen = 15;
  while ((hclen > 0) && (clcounts[order[(hclen + 4) - 1]] == 0))
    hclen--;

  hclen -= 1;
  if (!size_only)
  {
    AddBits(hlit, 5, bp, out, outsize);
    AddBits(hdist, 5, bp, out, outsize);
    AddBits(hclen, 4, bp, out, outsize);
    for (i = 0; i < (hclen + 4); i += 1)
    {
      AddBits(clcl[order[i]], 3, bp, out, outsize);
    }

    for (i = 0; i < rle_size; i += 1)
    {
      unsigned symbol = clsymbols[rle[i]];
      AddHuffmanBits(symbol, clcl[rle[i]], bp, out, outsize);
      if (rle[i] == 16)
      {
        AddBits(rle_bits[i], 2, bp, out, outsize);
      }
      else
        if (rle[i] == 17)
      {
        AddBits(rle_bits[i], 3, bp, out, outsize);
      }
      else
        if (rle[i] == 18)
      {
        AddBits(rle_bits[i], 7, bp, out, outsize);
      }
    }

  }
  result_size += 14;
  result_size += (hclen + 4) * 3;
  for (i = 0; i < 19; i += 1)
  {
    result_size += clcl[i] * clcounts[i];
  }

  result_size += clcounts[16] * 2;
  result_size += clcounts[17] * 3;
  result_size += clcounts[18] * 7;
  free(rle);
  free(rle_bits);
  return result_size;
}


----------------------------
***/


static size_t CalculateTreeSize(const unsigned *ll_lengths, const unsigned *d_lengths)
{
  size_t result = 0;
  int i;
  for (i = 0; i < 8; i += 1)
  {
    size_t size = EncodeTree(ll_lengths, d_lengths, i & 1, i & 2, i & 4, 0, 0, 0);
    if ((result == 0) || (size < result))
    {
      result = size;
    }
  }

  return result;
}


/*** DEPENDENCIES:
static size_t EncodeTree(const unsigned *ll_lengths, const unsigned *d_lengths, int use_16, int use_17, int use_18, unsigned char *bp, unsigned char **out, size_t *outsize)
{
  unsigned lld_total;
  unsigned *rle = 0;
  unsigned *rle_bits = 0;
  size_t rle_size = 0;
  size_t rle_bits_size = 0;
  unsigned hlit = 29;
  unsigned hdist = 29;
  unsigned hclen;
  unsigned hlit2;
  size_t i;
  size_t j;
  size_t clcounts[19];
  unsigned clcl[19];
  unsigned clsymbols[19];
  static const unsigned order[19] = {16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15};
  int size_only = !out;
  size_t result_size = 0;
  for (i = 0; i < 19; i += 1)
    clcounts[i] = 0;

  while ((hlit > 0) && (ll_lengths[(257 + hlit) - 1] == 0))
    hlit--;

  hlit -= 1;
  while ((hdist > 0) && (d_lengths[(1 + hdist) - 1] == 0))
    hdist--;

  hdist -= 1;
  hlit2 = hlit + 257;
  lld_total = (hlit2 + hdist) + 1;
  for (i = 0; i < lld_total; i += 1)
  {
    helper_EncodeTree_1(&rle_size, &rle_bits_size, &i, &j, ll_lengths, d_lengths, use_16, use_17, use_18, lld_total, rle, rle_bits, hlit2, clcounts, size_only);
  }

  ZopfliCalculateBitLengths(clcounts, 19, 7, clcl);
  if (!size_only)
  {
    ZopfliLengthsToSymbols(clcl, 19, 7, clsymbols);
  }
  hclen = 15;
  while ((hclen > 0) && (clcounts[order[(hclen + 4) - 1]] == 0))
    hclen--;

  hclen -= 1;
  if (!size_only)
  {
    AddBits(hlit, 5, bp, out, outsize);
    AddBits(hdist, 5, bp, out, outsize);
    AddBits(hclen, 4, bp, out, outsize);
    for (i = 0; i < (hclen + 4); i += 1)
    {
      AddBits(clcl[order[i]], 3, bp, out, outsize);
    }

    for (i = 0; i < rle_size; i += 1)
    {
      unsigned symbol = clsymbols[rle[i]];
      AddHuffmanBits(symbol, clcl[rle[i]], bp, out, outsize);
      if (rle[i] == 16)
      {
        AddBits(rle_bits[i], 2, bp, out, outsize);
      }
      else
        if (rle[i] == 17)
      {
        AddBits(rle_bits[i], 3, bp, out, outsize);
      }
      else
        if (rle[i] == 18)
      {
        AddBits(rle_bits[i], 7, bp, out, outsize);
      }
    }

  }
  result_size += 14;
  result_size += (hclen + 4) * 3;
  for (i = 0; i < 19; i += 1)
  {
    result_size += clcl[i] * clcounts[i];
  }

  result_size += clcounts[16] * 2;
  result_size += clcounts[17] * 3;
  result_size += clcounts[18] * 7;
  free(rle);
  free(rle_bits);
  return result_size;
}


----------------------------
***/


// hint:  ['i_ref is a mutable refrence to int', 'k_ref is a mutable refrence to int', 'stride_ref is a mutable refrence to int', 'sum_ref is a mutable refrence to size_t', 'limit_ref is a mutable refrence to size_t']
void helper_OptimizeHuffmanForRle_1(int * const i_ref, int * const k_ref, int * const stride_ref, size_t * const sum_ref, size_t * const limit_ref, int length, size_t * const counts, int * const good_for_rle, unsigned int good_for_rle_idx)
{
  int i = *i_ref;
  int k = *k_ref;
  int stride = *stride_ref;
  size_t sum = *sum_ref;
  size_t limit = *limit_ref;
  if (((i == length) || good_for_rle[i + good_for_rle_idx]) || (AbsDiff(counts[i], limit) >= 4))
  {
    if ((stride >= 4) || ((stride >= 3) && (sum == 0)))
    {
      int count = (sum + (stride / 2)) / stride;
      if (count < 1)
      {
        count = 1;
      }
      if (sum == 0)
      {
        count = 0;
      }
      for (k = 0; k < stride; k += 1)
      {
        counts[(i - k) - 1] = count;
      }

    }
    stride = 0;
    sum = 0;
    if (i < (length - 3))
    {
      limit = ((((counts[i] + counts[i + 1]) + counts[i + 2]) + counts[i + 3]) + 2) / 4;
    }
    else
      if (i < length)
    {
      limit = counts[i];
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
  }
  *i_ref = i;
  *k_ref = k;
  *stride_ref = stride;
  *sum_ref = sum;
  *limit_ref = limit;
}


/*** DEPENDENCIES:
static size_t AbsDiff(size_t x, size_t y)
{
  if (x > y)
  {
    return x - y;
  }
  else
    return y - x;
}


----------------------------
***/


void OptimizeHuffmanForRle(int length, size_t *counts)
{
  int i;
  int k;
  int stride;
  size_t symbol;
  size_t sum;
  size_t limit;
  int *good_for_rle;
  unsigned int good_for_rle_idx = 0;
  for (; length >= 0; length -= 1)
  {
    if (length == 0)
    {
      return;
    }
    if (counts[length - 1] != 0)
    {
      break;
    }
  }

  good_for_rle_idx = (int *) malloc(((unsigned) length) * (sizeof(int)));
  for (i = 0; i < length; i += 1)
    good_for_rle[i + good_for_rle_idx] = 0;

  symbol = counts[0];
  stride = 0;
  for (i = 0; i < (length + 1); i += 1)
  {
    if ((i == length) || (counts[i] != symbol))
    {
      if (((symbol == 0) && (stride >= 5)) || ((symbol != 0) && (stride >= 7)))
      {
        for (k = 0; k < stride; k += 1)
        {
          good_for_rle[((i - k) - 1) + good_for_rle_idx] = 1;
        }

      }
      stride = 1;
      if (i != length)
      {
        symbol = counts[i];
      }
    }
    else
    {
      stride += 1;
    }
  }

  stride = 0;
  limit = counts[0];
  sum = 0;
  for (i = 0; i < (length + 1); i += 1)
  {
    helper_OptimizeHuffmanForRle_1(&i, &k, &stride, &sum, &limit, length, counts, good_for_rle, good_for_rle_idx);
  }

  free(good_for_rle);
}


/*** DEPENDENCIES:
void helper_OptimizeHuffmanForRle_1(int * const i_ref, int * const k_ref, int * const stride_ref, size_t * const sum_ref, size_t * const limit_ref, int length, size_t * const counts, int * const good_for_rle, unsigned int good_for_rle_idx)
{
  int i = *i_ref;
  int k = *k_ref;
  int stride = *stride_ref;
  size_t sum = *sum_ref;
  size_t limit = *limit_ref;
  if (((i == length) || good_for_rle[i + good_for_rle_idx]) || (AbsDiff(counts[i], limit) >= 4))
  {
    if ((stride >= 4) || ((stride >= 3) && (sum == 0)))
    {
      int count = (sum + (stride / 2)) / stride;
      if (count < 1)
      {
        count = 1;
      }
      if (sum == 0)
      {
        count = 0;
      }
      for (k = 0; k < stride; k += 1)
      {
        counts[(i - k) - 1] = count;
      }

    }
    stride = 0;
    sum = 0;
    if (i < (length - 3))
    {
      limit = ((((counts[i] + counts[i + 1]) + counts[i + 2]) + counts[i + 3]) + 2) / 4;
    }
    else
      if (i < length)
    {
      limit = counts[i];
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
  }
  *i_ref = i;
  *k_ref = k;
  *stride_ref = stride;
  *sum_ref = sum;
  *limit_ref = limit;
}


----------------------------
***/


// hint:  ['pos_ref is a mutable refrence to size_t']
void helper_AddNonCompressedBlock_1(size_t * const pos_ref, int final, const unsigned char * const in, size_t inend, unsigned char * const bp, unsigned char ** const out, size_t * const outsize)
{
  size_t pos = *pos_ref;
  size_t i;
  unsigned short blocksize = 65535;
  unsigned short nlen;
  int currentfinal;
  if ((pos + blocksize) > inend)
  {
    blocksize = inend - pos;
  }
  currentfinal = (pos + blocksize) >= inend;
  nlen = ~blocksize;
  AddBit(final && currentfinal, bp, out, outsize);
  AddBit(0, bp, out, outsize);
  AddBit(0, bp, out, outsize);
  *bp = 0;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = blocksize % 256;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = (blocksize / 256) % 256;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = nlen % 256;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = (nlen / 256) % 256;
    *outsize += 1;
  }
  ;
  for (i = 0; i < blocksize; i += 1)
  {
    {
      if (!((*outsize) & ((*outsize) - 1)))
      {
        *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
      }
      (*out)[*outsize] = in[pos + i];
      *outsize += 1;
    }
    ;
  }

  if (currentfinal)
  {
    break;
  }
  pos += blocksize;
  *pos_ref = pos;
}


/*** DEPENDENCIES:
static void AddBit(int bit, unsigned char *bp, unsigned char **out, size_t *outsize)
{
  if ((*bp) == 0)
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = 0;
    *outsize += 1;
  }
  ;
  (*out)[(*outsize) - 1] |= bit << (*bp);
  *bp = ((*bp) + 1) & 7;
}


----------------------------
***/


static size_t CalculateBlockSymbolSizeSmall(const unsigned *ll_lengths, const unsigned *d_lengths, const ZopfliLZ77Store *lz77, size_t lstart, size_t lend)
{
  size_t result = 0;
  size_t i;
  for (i = lstart; i < lend; i += 1)
  {
    assert(i < lz77->size);
    assert(lz77->litlens[i] < 259);
    if (lz77->dists[i] == 0)
    {
      result += ll_lengths[lz77->litlens[i]];
    }
    else
    {
      int ll_symbol = ZopfliGetLengthSymbol(lz77->litlens[i]);
      int d_symbol = ZopfliGetDistSymbol(lz77->dists[i]);
      result += ll_lengths[ll_symbol];
      result += d_lengths[d_symbol];
      result += ZopfliGetLengthSymbolExtraBits(ll_symbol);
      result += ZopfliGetDistSymbolExtraBits(d_symbol);
    }
  }

  result += ll_lengths[256];
  return result;
}


/*** DEPENDENCIES:
typedef struct ZopfliLZ77Store
{
  unsigned short *litlens;
  unsigned short *dists;
  size_t size;
  const unsigned char *data;
  size_t *pos;
  unsigned short *ll_symbol;
  unsigned short *d_symbol;
  size_t *ll_counts;
  size_t *d_counts;
} ZopfliLZ77Store
----------------------------
static int ZopfliGetDistSymbolExtraBits(int s)
{
  static const int table[30] = {0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13};
  return table[s];
}


----------------------------
static int ZopfliGetDistSymbol(int dist)
{
  if (dist < 5)
  {
    return dist - 1;
  }
  else
  {
    int l = 31 ^ __builtin_clz(dist - 1);
    int r = ((dist - 1) >> (l - 1)) & 1;
    return (l * 2) + r;
  }
}


----------------------------
static int ZopfliGetLengthSymbolExtraBits(int s)
{
  static const int table[29] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0};
  return table[s - 257];
}


----------------------------
static int ZopfliGetLengthSymbol(int l)
{
  static const int table[259] = {0, 0, 0, 257, 258, 259, 260, 261, 262, 263, 264, 265, 265, 266, 266, 267, 267, 268, 268, 269, 269, 269, 269, 270, 270, 270, 270, 271, 271, 271, 271, 272, 272, 272, 272, 273, 273, 273, 273, 273, 273, 273, 273, 274, 274, 274, 274, 274, 274, 274, 274, 275, 275, 275, 275, 275, 275, 275, 275, 276, 276, 276, 276, 276, 276, 276, 276, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 285};
  return table[l];
}


----------------------------
***/


static size_t CalculateBlockSymbolSizeGivenCounts(const size_t *ll_counts, const size_t *d_counts, const unsigned *ll_lengths, const unsigned *d_lengths, const ZopfliLZ77Store *lz77, size_t lstart, size_t lend)
{
  size_t result = 0;
  size_t i;
  if ((lstart + (288 * 3)) > lend)
  {
    return CalculateBlockSymbolSizeSmall(ll_lengths, d_lengths, lz77, lstart, lend);
  }
  else
  {
    for (i = 0; i < 256; i += 1)
    {
      result += ll_lengths[i] * ll_counts[i];
    }

    for (i = 257; i < 286; i += 1)
    {
      result += ll_lengths[i] * ll_counts[i];
      result += ZopfliGetLengthSymbolExtraBits(i) * ll_counts[i];
    }

    for (i = 0; i < 30; i += 1)
    {
      result += d_lengths[i] * d_counts[i];
      result += ZopfliGetDistSymbolExtraBits(i) * d_counts[i];
    }

    result += ll_lengths[256];
    return result;
  }
}


/*** DEPENDENCIES:
typedef struct ZopfliLZ77Store
{
  unsigned short *litlens;
  unsigned short *dists;
  size_t size;
  const unsigned char *data;
  size_t *pos;
  unsigned short *ll_symbol;
  unsigned short *d_symbol;
  size_t *ll_counts;
  size_t *d_counts;
} ZopfliLZ77Store
----------------------------
static size_t CalculateBlockSymbolSizeSmall(const unsigned *ll_lengths, const unsigned *d_lengths, const ZopfliLZ77Store *lz77, size_t lstart, size_t lend)
{
  size_t result = 0;
  size_t i;
  for (i = lstart; i < lend; i += 1)
  {
    assert(i < lz77->size);
    assert(lz77->litlens[i] < 259);
    if (lz77->dists[i] == 0)
    {
      result += ll_lengths[lz77->litlens[i]];
    }
    else
    {
      int ll_symbol = ZopfliGetLengthSymbol(lz77->litlens[i]);
      int d_symbol = ZopfliGetDistSymbol(lz77->dists[i]);
      result += ll_lengths[ll_symbol];
      result += d_lengths[d_symbol];
      result += ZopfliGetLengthSymbolExtraBits(ll_symbol);
      result += ZopfliGetDistSymbolExtraBits(d_symbol);
    }
  }

  result += ll_lengths[256];
  return result;
}


----------------------------
static int ZopfliGetLengthSymbolExtraBits(int s)
{
  static const int table[29] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0};
  return table[s - 257];
}


----------------------------
static int ZopfliGetDistSymbolExtraBits(int s)
{
  static const int table[30] = {0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13};
  return table[s];
}


----------------------------
***/


static double TryOptimizeHuffmanForRle(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend, const size_t *ll_counts, const size_t *d_counts, unsigned *ll_lengths, unsigned *d_lengths)
{
  size_t ll_counts2[288];
  size_t d_counts2[32];
  unsigned ll_lengths2[288];
  unsigned d_lengths2[32];
  double treesize;
  double datasize;
  double treesize2;
  double datasize2;
  treesize = CalculateTreeSize(ll_lengths, d_lengths);
  datasize = CalculateBlockSymbolSizeGivenCounts(ll_counts, d_counts, ll_lengths, d_lengths, lz77, lstart, lend);
  memcpy(ll_counts2, ll_counts, sizeof(ll_counts2));
  memcpy(d_counts2, d_counts, sizeof(d_counts2));
  OptimizeHuffmanForRle(288, ll_counts2);
  OptimizeHuffmanForRle(32, d_counts2);
  ZopfliCalculateBitLengths(ll_counts2, 288, 15, ll_lengths2);
  ZopfliCalculateBitLengths(d_counts2, 32, 15, d_lengths2);
  PatchDistanceCodesForBuggyDecoders(d_lengths2);
  treesize2 = CalculateTreeSize(ll_lengths2, d_lengths2);
  datasize2 = CalculateBlockSymbolSizeGivenCounts(ll_counts, d_counts, ll_lengths2, d_lengths2, lz77, lstart, lend);
  if ((treesize2 + datasize2) < (treesize + datasize))
  {
    memcpy(ll_lengths, ll_lengths2, sizeof(ll_lengths2));
    memcpy(d_lengths, d_lengths2, sizeof(d_lengths2));
    return treesize2 + datasize2;
  }
  return treesize + datasize;
}


/*** DEPENDENCIES:
typedef struct ZopfliLZ77Store
{
  unsigned short *litlens;
  unsigned short *dists;
  size_t size;
  const unsigned char *data;
  size_t *pos;
  unsigned short *ll_symbol;
  unsigned short *d_symbol;
  size_t *ll_counts;
  size_t *d_counts;
} ZopfliLZ77Store
----------------------------
void ZopfliCalculateBitLengths(const size_t *count, size_t n, int maxbits, unsigned *bitlengths)
{
  int error = ZopfliLengthLimitedCodeLengths(count, n, maxbits, bitlengths);
  (void) error;
  assert(!error);
}


----------------------------
static size_t CalculateBlockSymbolSizeGivenCounts(const size_t *ll_counts, const size_t *d_counts, const unsigned *ll_lengths, const unsigned *d_lengths, const ZopfliLZ77Store *lz77, size_t lstart, size_t lend)
{
  size_t result = 0;
  size_t i;
  if ((lstart + (288 * 3)) > lend)
  {
    return CalculateBlockSymbolSizeSmall(ll_lengths, d_lengths, lz77, lstart, lend);
  }
  else
  {
    for (i = 0; i < 256; i += 1)
    {
      result += ll_lengths[i] * ll_counts[i];
    }

    for (i = 257; i < 286; i += 1)
    {
      result += ll_lengths[i] * ll_counts[i];
      result += ZopfliGetLengthSymbolExtraBits(i) * ll_counts[i];
    }

    for (i = 0; i < 30; i += 1)
    {
      result += d_lengths[i] * d_counts[i];
      result += ZopfliGetDistSymbolExtraBits(i) * d_counts[i];
    }

    result += ll_lengths[256];
    return result;
  }
}


----------------------------
static size_t CalculateTreeSize(const unsigned *ll_lengths, const unsigned *d_lengths)
{
  size_t result = 0;
  int i;
  for (i = 0; i < 8; i += 1)
  {
    size_t size = EncodeTree(ll_lengths, d_lengths, i & 1, i & 2, i & 4, 0, 0, 0);
    if ((result == 0) || (size < result))
    {
      result = size;
    }
  }

  return result;
}


----------------------------
void OptimizeHuffmanForRle(int length, size_t *counts)
{
  int i;
  int k;
  int stride;
  size_t symbol;
  size_t sum;
  size_t limit;
  int *good_for_rle;
  unsigned int good_for_rle_idx = 0;
  for (; length >= 0; length -= 1)
  {
    if (length == 0)
    {
      return;
    }
    if (counts[length - 1] != 0)
    {
      break;
    }
  }

  good_for_rle_idx = (int *) malloc(((unsigned) length) * (sizeof(int)));
  for (i = 0; i < length; i += 1)
    good_for_rle[i + good_for_rle_idx] = 0;

  symbol = counts[0];
  stride = 0;
  for (i = 0; i < (length + 1); i += 1)
  {
    if ((i == length) || (counts[i] != symbol))
    {
      if (((symbol == 0) && (stride >= 5)) || ((symbol != 0) && (stride >= 7)))
      {
        for (k = 0; k < stride; k += 1)
        {
          good_for_rle[((i - k) - 1) + good_for_rle_idx] = 1;
        }

      }
      stride = 1;
      if (i != length)
      {
        symbol = counts[i];
      }
    }
    else
    {
      stride += 1;
    }
  }

  stride = 0;
  limit = counts[0];
  sum = 0;
  for (i = 0; i < (length + 1); i += 1)
  {
    helper_OptimizeHuffmanForRle_1(&i, &k, &stride, &sum, &limit, length, counts, good_for_rle, good_for_rle_idx);
  }

  free(good_for_rle);
}


----------------------------
static void PatchDistanceCodesForBuggyDecoders(unsigned *d_lengths)
{
  int num_dist_codes = 0;
  int i;
  for (i = 0; i < 30; i += 1)
  {
    if (d_lengths[i])
    {
      num_dist_codes += 1;
    }
    if (num_dist_codes >= 2)
    {
      return;
    }
  }

  if (num_dist_codes == 0)
  {
    d_lengths[0] = (d_lengths[1] = 1);
  }
  else
    if (num_dist_codes == 1)
  {
    d_lengths[(d_lengths[0]) ? (1) : (0)] = 1;
  }
}


----------------------------
***/


static double GetDynamicLengths(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend, unsigned *ll_lengths, unsigned *d_lengths)
{
  size_t ll_counts[288];
  size_t d_counts[32];
  ZopfliLZ77GetHistogram(lz77, lstart, lend, ll_counts, d_counts);
  ll_counts[256] = 1;
  ZopfliCalculateBitLengths(ll_counts, 288, 15, ll_lengths);
  ZopfliCalculateBitLengths(d_counts, 32, 15, d_lengths);
  PatchDistanceCodesForBuggyDecoders(d_lengths);
  return TryOptimizeHuffmanForRle(lz77, lstart, lend, ll_counts, d_counts, ll_lengths, d_lengths);
}


/*** DEPENDENCIES:
typedef struct ZopfliLZ77Store
{
  unsigned short *litlens;
  unsigned short *dists;
  size_t size;
  const unsigned char *data;
  size_t *pos;
  unsigned short *ll_symbol;
  unsigned short *d_symbol;
  size_t *ll_counts;
  size_t *d_counts;
} ZopfliLZ77Store
----------------------------
void ZopfliLZ77GetHistogram(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend, size_t *ll_counts, size_t *d_counts)
{
  size_t i;
  if ((lstart + (288 * 3)) > lend)
  {
    memset(ll_counts, 0, (sizeof(*ll_counts)) * 288);
    memset(d_counts, 0, (sizeof(*d_counts)) * 32);
    for (i = lstart; i < lend; i += 1)
    {
      ll_counts[lz77->ll_symbol[i]] += 1;
      if (lz77->dists[i] != 0)
      {
        d_counts[lz77->d_symbol[i]] += 1;
      }
    }

  }
  else
  {
    ZopfliLZ77GetHistogramAt(lz77, lend - 1, ll_counts, d_counts);
    if (lstart > 0)
    {
      size_t ll_counts2[288];
      size_t d_counts2[32];
      ZopfliLZ77GetHistogramAt(lz77, lstart - 1, ll_counts2, d_counts2);
      for (i = 0; i < 288; i += 1)
      {
        ll_counts[i] -= ll_counts2[i];
      }

      for (i = 0; i < 32; i += 1)
      {
        d_counts[i] -= d_counts2[i];
      }

    }
  }
}


----------------------------
void ZopfliCalculateBitLengths(const size_t *count, size_t n, int maxbits, unsigned *bitlengths)
{
  int error = ZopfliLengthLimitedCodeLengths(count, n, maxbits, bitlengths);
  (void) error;
  assert(!error);
}


----------------------------
static double TryOptimizeHuffmanForRle(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend, const size_t *ll_counts, const size_t *d_counts, unsigned *ll_lengths, unsigned *d_lengths)
{
  size_t ll_counts2[288];
  size_t d_counts2[32];
  unsigned ll_lengths2[288];
  unsigned d_lengths2[32];
  double treesize;
  double datasize;
  double treesize2;
  double datasize2;
  treesize = CalculateTreeSize(ll_lengths, d_lengths);
  datasize = CalculateBlockSymbolSizeGivenCounts(ll_counts, d_counts, ll_lengths, d_lengths, lz77, lstart, lend);
  memcpy(ll_counts2, ll_counts, sizeof(ll_counts2));
  memcpy(d_counts2, d_counts, sizeof(d_counts2));
  OptimizeHuffmanForRle(288, ll_counts2);
  OptimizeHuffmanForRle(32, d_counts2);
  ZopfliCalculateBitLengths(ll_counts2, 288, 15, ll_lengths2);
  ZopfliCalculateBitLengths(d_counts2, 32, 15, d_lengths2);
  PatchDistanceCodesForBuggyDecoders(d_lengths2);
  treesize2 = CalculateTreeSize(ll_lengths2, d_lengths2);
  datasize2 = CalculateBlockSymbolSizeGivenCounts(ll_counts, d_counts, ll_lengths2, d_lengths2, lz77, lstart, lend);
  if ((treesize2 + datasize2) < (treesize + datasize))
  {
    memcpy(ll_lengths, ll_lengths2, sizeof(ll_lengths2));
    memcpy(d_lengths, d_lengths2, sizeof(d_lengths2));
    return treesize2 + datasize2;
  }
  return treesize + datasize;
}


----------------------------
static void PatchDistanceCodesForBuggyDecoders(unsigned *d_lengths)
{
  int num_dist_codes = 0;
  int i;
  for (i = 0; i < 30; i += 1)
  {
    if (d_lengths[i])
    {
      num_dist_codes += 1;
    }
    if (num_dist_codes >= 2)
    {
      return;
    }
  }

  if (num_dist_codes == 0)
  {
    d_lengths[0] = (d_lengths[1] = 1);
  }
  else
    if (num_dist_codes == 1)
  {
    d_lengths[(d_lengths[0]) ? (1) : (0)] = 1;
  }
}


----------------------------
***/


static size_t CalculateBlockSymbolSize(const unsigned *ll_lengths, const unsigned *d_lengths, const ZopfliLZ77Store *lz77, size_t lstart, size_t lend)
{
  if ((lstart + (288 * 3)) > lend)
  {
    return CalculateBlockSymbolSizeSmall(ll_lengths, d_lengths, lz77, lstart, lend);
  }
  else
  {
    size_t ll_counts[288];
    size_t d_counts[32];
    ZopfliLZ77GetHistogram(lz77, lstart, lend, ll_counts, d_counts);
    return CalculateBlockSymbolSizeGivenCounts(ll_counts, d_counts, ll_lengths, d_lengths, lz77, lstart, lend);
  }
}


/*** DEPENDENCIES:
typedef struct ZopfliLZ77Store
{
  unsigned short *litlens;
  unsigned short *dists;
  size_t size;
  const unsigned char *data;
  size_t *pos;
  unsigned short *ll_symbol;
  unsigned short *d_symbol;
  size_t *ll_counts;
  size_t *d_counts;
} ZopfliLZ77Store
----------------------------
static size_t CalculateBlockSymbolSizeSmall(const unsigned *ll_lengths, const unsigned *d_lengths, const ZopfliLZ77Store *lz77, size_t lstart, size_t lend)
{
  size_t result = 0;
  size_t i;
  for (i = lstart; i < lend; i += 1)
  {
    assert(i < lz77->size);
    assert(lz77->litlens[i] < 259);
    if (lz77->dists[i] == 0)
    {
      result += ll_lengths[lz77->litlens[i]];
    }
    else
    {
      int ll_symbol = ZopfliGetLengthSymbol(lz77->litlens[i]);
      int d_symbol = ZopfliGetDistSymbol(lz77->dists[i]);
      result += ll_lengths[ll_symbol];
      result += d_lengths[d_symbol];
      result += ZopfliGetLengthSymbolExtraBits(ll_symbol);
      result += ZopfliGetDistSymbolExtraBits(d_symbol);
    }
  }

  result += ll_lengths[256];
  return result;
}


----------------------------
void ZopfliLZ77GetHistogram(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend, size_t *ll_counts, size_t *d_counts)
{
  size_t i;
  if ((lstart + (288 * 3)) > lend)
  {
    memset(ll_counts, 0, (sizeof(*ll_counts)) * 288);
    memset(d_counts, 0, (sizeof(*d_counts)) * 32);
    for (i = lstart; i < lend; i += 1)
    {
      ll_counts[lz77->ll_symbol[i]] += 1;
      if (lz77->dists[i] != 0)
      {
        d_counts[lz77->d_symbol[i]] += 1;
      }
    }

  }
  else
  {
    ZopfliLZ77GetHistogramAt(lz77, lend - 1, ll_counts, d_counts);
    if (lstart > 0)
    {
      size_t ll_counts2[288];
      size_t d_counts2[32];
      ZopfliLZ77GetHistogramAt(lz77, lstart - 1, ll_counts2, d_counts2);
      for (i = 0; i < 288; i += 1)
      {
        ll_counts[i] -= ll_counts2[i];
      }

      for (i = 0; i < 32; i += 1)
      {
        d_counts[i] -= d_counts2[i];
      }

    }
  }
}


----------------------------
static size_t CalculateBlockSymbolSizeGivenCounts(const size_t *ll_counts, const size_t *d_counts, const unsigned *ll_lengths, const unsigned *d_lengths, const ZopfliLZ77Store *lz77, size_t lstart, size_t lend)
{
  size_t result = 0;
  size_t i;
  if ((lstart + (288 * 3)) > lend)
  {
    return CalculateBlockSymbolSizeSmall(ll_lengths, d_lengths, lz77, lstart, lend);
  }
  else
  {
    for (i = 0; i < 256; i += 1)
    {
      result += ll_lengths[i] * ll_counts[i];
    }

    for (i = 257; i < 286; i += 1)
    {
      result += ll_lengths[i] * ll_counts[i];
      result += ZopfliGetLengthSymbolExtraBits(i) * ll_counts[i];
    }

    for (i = 0; i < 30; i += 1)
    {
      result += d_lengths[i] * d_counts[i];
      result += ZopfliGetDistSymbolExtraBits(i) * d_counts[i];
    }

    result += ll_lengths[256];
    return result;
  }
}


----------------------------
***/


double ZopfliCalculateBlockSize(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend, int btype)
{
  unsigned ll_lengths[288];
  unsigned d_lengths[32];
  double result = 3;
  if (btype == 0)
  {
    size_t length = ZopfliLZ77GetByteRange(lz77, lstart, lend);
    size_t rem = length % 65535;
    size_t blocks = (length / 65535) + ((rem) ? (1) : (0));
    return ((blocks * 5) * 8) + (length * 8);
  }
  if (btype == 1)
  {
    GetFixedTree(ll_lengths, d_lengths);
    result += CalculateBlockSymbolSize(ll_lengths, d_lengths, lz77, lstart, lend);
  }
  else
  {
    result += GetDynamicLengths(lz77, lstart, lend, ll_lengths, d_lengths);
  }
  return result;
}


/*** DEPENDENCIES:
typedef struct ZopfliLZ77Store
{
  unsigned short *litlens;
  unsigned short *dists;
  size_t size;
  const unsigned char *data;
  size_t *pos;
  unsigned short *ll_symbol;
  unsigned short *d_symbol;
  size_t *ll_counts;
  size_t *d_counts;
} ZopfliLZ77Store
----------------------------
static double GetDynamicLengths(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend, unsigned *ll_lengths, unsigned *d_lengths)
{
  size_t ll_counts[288];
  size_t d_counts[32];
  ZopfliLZ77GetHistogram(lz77, lstart, lend, ll_counts, d_counts);
  ll_counts[256] = 1;
  ZopfliCalculateBitLengths(ll_counts, 288, 15, ll_lengths);
  ZopfliCalculateBitLengths(d_counts, 32, 15, d_lengths);
  PatchDistanceCodesForBuggyDecoders(d_lengths);
  return TryOptimizeHuffmanForRle(lz77, lstart, lend, ll_counts, d_counts, ll_lengths, d_lengths);
}


----------------------------
static size_t CalculateBlockSymbolSize(const unsigned *ll_lengths, const unsigned *d_lengths, const ZopfliLZ77Store *lz77, size_t lstart, size_t lend)
{
  if ((lstart + (288 * 3)) > lend)
  {
    return CalculateBlockSymbolSizeSmall(ll_lengths, d_lengths, lz77, lstart, lend);
  }
  else
  {
    size_t ll_counts[288];
    size_t d_counts[32];
    ZopfliLZ77GetHistogram(lz77, lstart, lend, ll_counts, d_counts);
    return CalculateBlockSymbolSizeGivenCounts(ll_counts, d_counts, ll_lengths, d_lengths, lz77, lstart, lend);
  }
}


----------------------------
size_t ZopfliLZ77GetByteRange(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend)
{
  size_t l = lend - 1;
  if (lstart == lend)
  {
    return 0;
  }
  return (lz77->pos[l] + ((lz77->dists[l] == 0) ? (1) : (lz77->litlens[l]))) - lz77->pos[lstart];
}


----------------------------
static void GetFixedTree(unsigned *ll_lengths, unsigned *d_lengths)
{
  size_t i;
  for (i = 0; i < 144; i += 1)
    ll_lengths[i] = 8;

  for (i = 144; i < 256; i += 1)
    ll_lengths[i] = 9;

  for (i = 256; i < 280; i += 1)
    ll_lengths[i] = 7;

  for (i = 280; i < 288; i += 1)
    ll_lengths[i] = 8;

  for (i = 0; i < 32; i += 1)
    d_lengths[i] = 5;

}


----------------------------
***/


double ZopfliCalculateBlockSizeAutoType(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend)
{
  double uncompressedcost = ZopfliCalculateBlockSize(lz77, lstart, lend, 0);
  double fixedcost = (lz77->size > 1000) ? (uncompressedcost) : (ZopfliCalculateBlockSize(lz77, lstart, lend, 1));
  double dyncost = ZopfliCalculateBlockSize(lz77, lstart, lend, 2);
  return ((uncompressedcost < fixedcost) && (uncompressedcost < dyncost)) ? (uncompressedcost) : ((fixedcost < dyncost) ? (fixedcost) : (dyncost));
}


/*** DEPENDENCIES:
typedef struct ZopfliLZ77Store
{
  unsigned short *litlens;
  unsigned short *dists;
  size_t size;
  const unsigned char *data;
  size_t *pos;
  unsigned short *ll_symbol;
  unsigned short *d_symbol;
  size_t *ll_counts;
  size_t *d_counts;
} ZopfliLZ77Store
----------------------------
double ZopfliCalculateBlockSize(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend, int btype)
{
  unsigned ll_lengths[288];
  unsigned d_lengths[32];
  double result = 3;
  if (btype == 0)
  {
    size_t length = ZopfliLZ77GetByteRange(lz77, lstart, lend);
    size_t rem = length % 65535;
    size_t blocks = (length / 65535) + ((rem) ? (1) : (0));
    return ((blocks * 5) * 8) + (length * 8);
  }
  if (btype == 1)
  {
    GetFixedTree(ll_lengths, d_lengths);
    result += CalculateBlockSymbolSize(ll_lengths, d_lengths, lz77, lstart, lend);
  }
  else
  {
    result += GetDynamicLengths(lz77, lstart, lend, ll_lengths, d_lengths);
  }
  return result;
}


----------------------------
***/


static void AddLZ77Data(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend, size_t expected_data_size, const unsigned *ll_symbols, const unsigned *ll_lengths, const unsigned *d_symbols, const unsigned *d_lengths, unsigned char *bp, unsigned char **out, size_t *outsize)
{
  size_t testlength = 0;
  size_t i;
  for (i = lstart; i < lend; i += 1)
  {
    unsigned dist = lz77->dists[i];
    unsigned litlen = lz77->litlens[i];
    if (dist == 0)
    {
      assert(litlen < 256);
      assert(ll_lengths[litlen] > 0);
      AddHuffmanBits(ll_symbols[litlen], ll_lengths[litlen], bp, out, outsize);
      testlength += 1;
    }
    else
    {
      unsigned lls = ZopfliGetLengthSymbol(litlen);
      unsigned ds = ZopfliGetDistSymbol(dist);
      assert((litlen >= 3) && (litlen <= 288));
      assert(ll_lengths[lls] > 0);
      assert(d_lengths[ds] > 0);
      AddHuffmanBits(ll_symbols[lls], ll_lengths[lls], bp, out, outsize);
      AddBits(ZopfliGetLengthExtraBitsValue(litlen), ZopfliGetLengthExtraBits(litlen), bp, out, outsize);
      AddHuffmanBits(d_symbols[ds], d_lengths[ds], bp, out, outsize);
      AddBits(ZopfliGetDistExtraBitsValue(dist), ZopfliGetDistExtraBits(dist), bp, out, outsize);
      testlength += litlen;
    }
  }

  assert((expected_data_size == 0) || (testlength == expected_data_size));
}


/*** DEPENDENCIES:
typedef struct ZopfliLZ77Store
{
  unsigned short *litlens;
  unsigned short *dists;
  size_t size;
  const unsigned char *data;
  size_t *pos;
  unsigned short *ll_symbol;
  unsigned short *d_symbol;
  size_t *ll_counts;
  size_t *d_counts;
} ZopfliLZ77Store
----------------------------
static int ZopfliGetDistExtraBits(int dist)
{
  if (dist < 5)
  {
    return 0;
  }
  return (31 ^ __builtin_clz(dist - 1)) - 1;
}


----------------------------
static int ZopfliGetDistSymbol(int dist)
{
  if (dist < 5)
  {
    return dist - 1;
  }
  else
  {
    int l = 31 ^ __builtin_clz(dist - 1);
    int r = ((dist - 1) >> (l - 1)) & 1;
    return (l * 2) + r;
  }
}


----------------------------
static void AddHuffmanBits(unsigned symbol, unsigned length, unsigned char *bp, unsigned char **out, size_t *outsize)
{
  unsigned i;
  for (i = 0; i < length; i += 1)
  {
    unsigned bit = (symbol >> ((length - i) - 1)) & 1;
    if ((*bp) == 0)
    {
      if (!((*outsize) & ((*outsize) - 1)))
      {
        *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
      }
      (*out)[*outsize] = 0;
      *outsize += 1;
    }
    ;
    (*out)[(*outsize) - 1] |= bit << (*bp);
    *bp = ((*bp) + 1) & 7;
  }

}


----------------------------
static int ZopfliGetDistExtraBitsValue(int dist)
{
  if (dist < 5)
  {
    return 0;
  }
  else
  {
    int l = 31 ^ __builtin_clz(dist - 1);
    return (dist - (1 + (1 << l))) & ((1 << (l - 1)) - 1);
  }
}


----------------------------
static int ZopfliGetLengthExtraBits(int l)
{
  static const int table[259] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0};
  return table[l];
}


----------------------------
static int ZopfliGetLengthSymbol(int l)
{
  static const int table[259] = {0, 0, 0, 257, 258, 259, 260, 261, 262, 263, 264, 265, 265, 266, 266, 267, 267, 268, 268, 269, 269, 269, 269, 270, 270, 270, 270, 271, 271, 271, 271, 272, 272, 272, 272, 273, 273, 273, 273, 273, 273, 273, 273, 274, 274, 274, 274, 274, 274, 274, 274, 275, 275, 275, 275, 275, 275, 275, 275, 276, 276, 276, 276, 276, 276, 276, 276, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 285};
  return table[l];
}


----------------------------
static void AddBits(unsigned symbol, unsigned length, unsigned char *bp, unsigned char **out, size_t *outsize)
{
  unsigned i;
  for (i = 0; i < length; i += 1)
  {
    unsigned bit = (symbol >> i) & 1;
    if ((*bp) == 0)
    {
      if (!((*outsize) & ((*outsize) - 1)))
      {
        *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
      }
      (*out)[*outsize] = 0;
      *outsize += 1;
    }
    ;
    (*out)[(*outsize) - 1] |= bit << (*bp);
    *bp = ((*bp) + 1) & 7;
  }

}


----------------------------
static int ZopfliGetLengthExtraBitsValue(int l)
{
  static const int table[259] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 0};
  return table[l];
}


----------------------------
***/


static void AddNonCompressedBlock(const ZopfliOptions *options, int final, const unsigned char *in, size_t instart, size_t inend, unsigned char *bp, unsigned char **out, size_t *outsize)
{
  size_t pos = instart;
  (void) options;
  for (;;)
  {
    helper_AddNonCompressedBlock_1(&pos, final, in, inend, bp, out, outsize);
  }

}


/*** DEPENDENCIES:
void helper_AddNonCompressedBlock_1(size_t * const pos_ref, int final, const unsigned char * const in, size_t inend, unsigned char * const bp, unsigned char ** const out, size_t * const outsize)
{
  size_t pos = *pos_ref;
  size_t i;
  unsigned short blocksize = 65535;
  unsigned short nlen;
  int currentfinal;
  if ((pos + blocksize) > inend)
  {
    blocksize = inend - pos;
  }
  currentfinal = (pos + blocksize) >= inend;
  nlen = ~blocksize;
  AddBit(final && currentfinal, bp, out, outsize);
  AddBit(0, bp, out, outsize);
  AddBit(0, bp, out, outsize);
  *bp = 0;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = blocksize % 256;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = (blocksize / 256) % 256;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = nlen % 256;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = (nlen / 256) % 256;
    *outsize += 1;
  }
  ;
  for (i = 0; i < blocksize; i += 1)
  {
    {
      if (!((*outsize) & ((*outsize) - 1)))
      {
        *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
      }
      (*out)[*outsize] = in[pos + i];
      *outsize += 1;
    }
    ;
  }

  if (currentfinal)
  {
    break;
  }
  pos += blocksize;
  *pos_ref = pos;
}


----------------------------
typedef struct ZopfliOptions
{
  int verbose;
  int verbose_more;
  int numiterations;
  int blocksplitting;
  int blocksplittinglast;
  int blocksplittingmax;
} ZopfliOptions
----------------------------
***/


static void AddLZ77Block(const ZopfliOptions *options, int btype, int final, const ZopfliLZ77Store *lz77, size_t lstart, size_t lend, size_t expected_data_size, unsigned char *bp, unsigned char **out, size_t *outsize)
{
  unsigned ll_lengths[288];
  unsigned d_lengths[32];
  unsigned ll_symbols[288];
  unsigned d_symbols[32];
  size_t detect_block_size = *outsize;
  size_t compressed_size;
  size_t uncompressed_size = 0;
  size_t i;
  if (btype == 0)
  {
    size_t length = ZopfliLZ77GetByteRange(lz77, lstart, lend);
    size_t pos = (lstart == lend) ? (0) : (lz77->pos[lstart]);
    size_t end = pos + length;
    AddNonCompressedBlock(options, final, lz77->data, pos, end, bp, out, outsize);
    return;
  }
  AddBit(final, bp, out, outsize);
  AddBit(btype & 1, bp, out, outsize);
  AddBit((btype & 2) >> 1, bp, out, outsize);
  if (btype == 1)
  {
    GetFixedTree(ll_lengths, d_lengths);
  }
  else
  {
    unsigned detect_tree_size;
    assert(btype == 2);
    GetDynamicLengths(lz77, lstart, lend, ll_lengths, d_lengths);
    detect_tree_size = *outsize;
    AddDynamicTree(ll_lengths, d_lengths, bp, out, outsize);
    if (options->verbose)
    {
      fprintf(stderr, "treesize: %d\n", (int) ((*outsize) - detect_tree_size));
    }
  }
  ZopfliLengthsToSymbols(ll_lengths, 288, 15, ll_symbols);
  ZopfliLengthsToSymbols(d_lengths, 32, 15, d_symbols);
  detect_block_size = *outsize;
  AddLZ77Data(lz77, lstart, lend, expected_data_size, ll_symbols, ll_lengths, d_symbols, d_lengths, bp, out, outsize);
  AddHuffmanBits(ll_symbols[256], ll_lengths[256], bp, out, outsize);
  for (i = lstart; i < lend; i += 1)
  {
    uncompressed_size += (lz77->dists[i] == 0) ? (1) : (lz77->litlens[i]);
  }

  compressed_size = (*outsize) - detect_block_size;
  if (options->verbose)
  {
    fprintf(stderr, "compressed block size: %d (%dk) (unc: %d)\n", (int) compressed_size, (int) (compressed_size / 1024), (int) uncompressed_size);
  }
}


/*** DEPENDENCIES:
typedef struct ZopfliLZ77Store
{
  unsigned short *litlens;
  unsigned short *dists;
  size_t size;
  const unsigned char *data;
  size_t *pos;
  unsigned short *ll_symbol;
  unsigned short *d_symbol;
  size_t *ll_counts;
  size_t *d_counts;
} ZopfliLZ77Store
----------------------------
static double GetDynamicLengths(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend, unsigned *ll_lengths, unsigned *d_lengths)
{
  size_t ll_counts[288];
  size_t d_counts[32];
  ZopfliLZ77GetHistogram(lz77, lstart, lend, ll_counts, d_counts);
  ll_counts[256] = 1;
  ZopfliCalculateBitLengths(ll_counts, 288, 15, ll_lengths);
  ZopfliCalculateBitLengths(d_counts, 32, 15, d_lengths);
  PatchDistanceCodesForBuggyDecoders(d_lengths);
  return TryOptimizeHuffmanForRle(lz77, lstart, lend, ll_counts, d_counts, ll_lengths, d_lengths);
}


----------------------------
static void AddDynamicTree(const unsigned *ll_lengths, const unsigned *d_lengths, unsigned char *bp, unsigned char **out, size_t *outsize)
{
  int i;
  int best = 0;
  size_t bestsize = 0;
  for (i = 0; i < 8; i += 1)
  {
    size_t size = EncodeTree(ll_lengths, d_lengths, i & 1, i & 2, i & 4, 0, 0, 0);
    if ((bestsize == 0) || (size < bestsize))
    {
      bestsize = size;
      best = i;
    }
  }

  EncodeTree(ll_lengths, d_lengths, best & 1, best & 2, best & 4, bp, out, outsize);
}


----------------------------
static void AddBit(int bit, unsigned char *bp, unsigned char **out, size_t *outsize)
{
  if ((*bp) == 0)
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = 0;
    *outsize += 1;
  }
  ;
  (*out)[(*outsize) - 1] |= bit << (*bp);
  *bp = ((*bp) + 1) & 7;
}


----------------------------
size_t ZopfliLZ77GetByteRange(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend)
{
  size_t l = lend - 1;
  if (lstart == lend)
  {
    return 0;
  }
  return (lz77->pos[l] + ((lz77->dists[l] == 0) ? (1) : (lz77->litlens[l]))) - lz77->pos[lstart];
}


----------------------------
void ZopfliLengthsToSymbols(const unsigned *lengths, size_t n, unsigned maxbits, unsigned *symbols)
{
  size_t *bl_count = (size_t *) malloc((sizeof(size_t)) * (maxbits + 1));
  size_t *next_code = (size_t *) malloc((sizeof(size_t)) * (maxbits + 1));
  unsigned bits;
  unsigned i;
  unsigned code;
  for (i = 0; i < n; i += 1)
  {
    symbols[i] = 0;
  }

  for (bits = 0; bits <= maxbits; bits += 1)
  {
    bl_count[bits] = 0;
  }

  for (i = 0; i < n; i += 1)
  {
    assert(lengths[i] <= maxbits);
    bl_count[lengths[i]] += 1;
  }

  code = 0;
  bl_count[0] = 0;
  for (bits = 1; bits <= maxbits; bits += 1)
  {
    code = (code + bl_count[bits - 1]) << 1;
    next_code[bits] = code;
  }

  for (i = 0; i < n; i += 1)
  {
    unsigned len = lengths[i];
    if (len != 0)
    {
      symbols[i] = next_code[len];
      next_code[len] += 1;
    }
  }

  free(bl_count);
  free(next_code);
}


----------------------------
static void AddHuffmanBits(unsigned symbol, unsigned length, unsigned char *bp, unsigned char **out, size_t *outsize)
{
  unsigned i;
  for (i = 0; i < length; i += 1)
  {
    unsigned bit = (symbol >> ((length - i) - 1)) & 1;
    if ((*bp) == 0)
    {
      if (!((*outsize) & ((*outsize) - 1)))
      {
        *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
      }
      (*out)[*outsize] = 0;
      *outsize += 1;
    }
    ;
    (*out)[(*outsize) - 1] |= bit << (*bp);
    *bp = ((*bp) + 1) & 7;
  }

}


----------------------------
typedef struct ZopfliOptions
{
  int verbose;
  int verbose_more;
  int numiterations;
  int blocksplitting;
  int blocksplittinglast;
  int blocksplittingmax;
} ZopfliOptions
----------------------------
static void AddLZ77Data(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend, size_t expected_data_size, const unsigned *ll_symbols, const unsigned *ll_lengths, const unsigned *d_symbols, const unsigned *d_lengths, unsigned char *bp, unsigned char **out, size_t *outsize)
{
  size_t testlength = 0;
  size_t i;
  for (i = lstart; i < lend; i += 1)
  {
    unsigned dist = lz77->dists[i];
    unsigned litlen = lz77->litlens[i];
    if (dist == 0)
    {
      assert(litlen < 256);
      assert(ll_lengths[litlen] > 0);
      AddHuffmanBits(ll_symbols[litlen], ll_lengths[litlen], bp, out, outsize);
      testlength += 1;
    }
    else
    {
      unsigned lls = ZopfliGetLengthSymbol(litlen);
      unsigned ds = ZopfliGetDistSymbol(dist);
      assert((litlen >= 3) && (litlen <= 288));
      assert(ll_lengths[lls] > 0);
      assert(d_lengths[ds] > 0);
      AddHuffmanBits(ll_symbols[lls], ll_lengths[lls], bp, out, outsize);
      AddBits(ZopfliGetLengthExtraBitsValue(litlen), ZopfliGetLengthExtraBits(litlen), bp, out, outsize);
      AddHuffmanBits(d_symbols[ds], d_lengths[ds], bp, out, outsize);
      AddBits(ZopfliGetDistExtraBitsValue(dist), ZopfliGetDistExtraBits(dist), bp, out, outsize);
      testlength += litlen;
    }
  }

  assert((expected_data_size == 0) || (testlength == expected_data_size));
}


----------------------------
static void AddNonCompressedBlock(const ZopfliOptions *options, int final, const unsigned char *in, size_t instart, size_t inend, unsigned char *bp, unsigned char **out, size_t *outsize)
{
  size_t pos = instart;
  (void) options;
  for (;;)
  {
    helper_AddNonCompressedBlock_1(&pos, final, in, inend, bp, out, outsize);
  }

}


----------------------------
static void GetFixedTree(unsigned *ll_lengths, unsigned *d_lengths)
{
  size_t i;
  for (i = 0; i < 144; i += 1)
    ll_lengths[i] = 8;

  for (i = 144; i < 256; i += 1)
    ll_lengths[i] = 9;

  for (i = 256; i < 280; i += 1)
    ll_lengths[i] = 7;

  for (i = 280; i < 288; i += 1)
    ll_lengths[i] = 8;

  for (i = 0; i < 32; i += 1)
    d_lengths[i] = 5;

}


----------------------------
***/


static void AddLZ77BlockAutoType(const ZopfliOptions *options, int final, const ZopfliLZ77Store *lz77, size_t lstart, size_t lend, size_t expected_data_size, unsigned char *bp, unsigned char **out, size_t *outsize)
{
  double uncompressedcost = ZopfliCalculateBlockSize(lz77, lstart, lend, 0);
  double fixedcost = ZopfliCalculateBlockSize(lz77, lstart, lend, 1);
  double dyncost = ZopfliCalculateBlockSize(lz77, lstart, lend, 2);
  int expensivefixed = (lz77->size < 1000) || (fixedcost <= (dyncost * 1.1));
  ZopfliLZ77Store fixedstore;
  if (lstart == lend)
  {
    AddBits(final, 1, bp, out, outsize);
    AddBits(1, 2, bp, out, outsize);
    AddBits(0, 7, bp, out, outsize);
    return;
  }
  ZopfliInitLZ77Store(lz77->data, &fixedstore);
  if (expensivefixed)
  {
    size_t instart = lz77->pos[lstart];
    size_t inend = instart + ZopfliLZ77GetByteRange(lz77, lstart, lend);
    ZopfliBlockState s;
    ZopfliInitBlockState(options, instart, inend, 1, &s);
    ZopfliLZ77OptimalFixed(&s, lz77->data, instart, inend, &fixedstore);
    fixedcost = ZopfliCalculateBlockSize(&fixedstore, 0, fixedstore.size, 1);
    ZopfliCleanBlockState(&s);
  }
  if ((uncompressedcost < fixedcost) && (uncompressedcost < dyncost))
  {
    AddLZ77Block(options, 0, final, lz77, lstart, lend, expected_data_size, bp, out, outsize);
  }
  else
    if (fixedcost < dyncost)
  {
    if (expensivefixed)
    {
      AddLZ77Block(options, 1, final, &fixedstore, 0, fixedstore.size, expected_data_size, bp, out, outsize);
    }
    else
    {
      AddLZ77Block(options, 1, final, lz77, lstart, lend, expected_data_size, bp, out, outsize);
    }
  }
  else
  {
    AddLZ77Block(options, 2, final, lz77, lstart, lend, expected_data_size, bp, out, outsize);
  }
  ZopfliCleanLZ77Store(&fixedstore);
}


/*** DEPENDENCIES:
typedef struct ZopfliLZ77Store
{
  unsigned short *litlens;
  unsigned short *dists;
  size_t size;
  const unsigned char *data;
  size_t *pos;
  unsigned short *ll_symbol;
  unsigned short *d_symbol;
  size_t *ll_counts;
  size_t *d_counts;
} ZopfliLZ77Store
----------------------------
void ZopfliLZ77OptimalFixed(ZopfliBlockState *s, const unsigned char *in, size_t instart, size_t inend, ZopfliLZ77Store *store)
{
  size_t blocksize = inend - instart;
  unsigned short *length_array = (unsigned short *) malloc((sizeof(unsigned short)) * (blocksize + 1));
  unsigned short *path = 0;
  size_t pathsize = 0;
  ZopfliHash hash;
  ZopfliHash *h = &hash;
  float *costs = (float *) malloc((sizeof(float)) * (blocksize + 1));
  if (!costs)
  {
    exit(-1);
  }
  if (!length_array)
  {
    exit(-1);
  }
  ZopfliAllocHash(32768, h);
  s->blockstart = instart;
  s->blockend = inend;
  LZ77OptimalRun(s, in, instart, inend, &path, &pathsize, length_array, GetCostFixed, 0, store, h, costs);
  free(length_array);
  free(path);
  free(costs);
  ZopfliCleanHash(h);
}


----------------------------
void ZopfliInitBlockState(const ZopfliOptions *options, size_t blockstart, size_t blockend, int add_lmc, ZopfliBlockState *s)
{
  s->options = options;
  s->blockstart = blockstart;
  s->blockend = blockend;
  if (add_lmc)
  {
    s->lmc = (ZopfliLongestMatchCache *) malloc(sizeof(ZopfliLongestMatchCache));
    ZopfliInitCache(blockend - blockstart, s->lmc);
  }
  else
  {
    s->lmc = 0;
  }
}


----------------------------
double ZopfliCalculateBlockSize(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend, int btype)
{
  unsigned ll_lengths[288];
  unsigned d_lengths[32];
  double result = 3;
  if (btype == 0)
  {
    size_t length = ZopfliLZ77GetByteRange(lz77, lstart, lend);
    size_t rem = length % 65535;
    size_t blocks = (length / 65535) + ((rem) ? (1) : (0));
    return ((blocks * 5) * 8) + (length * 8);
  }
  if (btype == 1)
  {
    GetFixedTree(ll_lengths, d_lengths);
    result += CalculateBlockSymbolSize(ll_lengths, d_lengths, lz77, lstart, lend);
  }
  else
  {
    result += GetDynamicLengths(lz77, lstart, lend, ll_lengths, d_lengths);
  }
  return result;
}


----------------------------
void ZopfliCleanLZ77Store(ZopfliLZ77Store *store)
{
  free(store->litlens);
  free(store->dists);
  free(store->pos);
  free(store->ll_symbol);
  free(store->d_symbol);
  free(store->ll_counts);
  free(store->d_counts);
}


----------------------------
typedef struct ZopfliBlockState
{
  const ZopfliOptions *options;
  ZopfliLongestMatchCache *lmc;
  size_t blockstart;
  size_t blockend;
} ZopfliBlockState
----------------------------
void ZopfliInitLZ77Store(const unsigned char *data, ZopfliLZ77Store *store)
{
  store->size = 0;
  store->litlens = 0;
  store->dists = 0;
  store->pos = 0;
  store->data = data;
  store->ll_symbol = 0;
  store->d_symbol = 0;
  store->ll_counts = 0;
  store->d_counts = 0;
}


----------------------------
void ZopfliCleanBlockState(ZopfliBlockState *s)
{
  if (s->lmc)
  {
    ZopfliCleanCache(s->lmc);
    free(s->lmc);
  }
}


----------------------------
size_t ZopfliLZ77GetByteRange(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend)
{
  size_t l = lend - 1;
  if (lstart == lend)
  {
    return 0;
  }
  return (lz77->pos[l] + ((lz77->dists[l] == 0) ? (1) : (lz77->litlens[l]))) - lz77->pos[lstart];
}


----------------------------
static void AddLZ77Block(const ZopfliOptions *options, int btype, int final, const ZopfliLZ77Store *lz77, size_t lstart, size_t lend, size_t expected_data_size, unsigned char *bp, unsigned char **out, size_t *outsize)
{
  unsigned ll_lengths[288];
  unsigned d_lengths[32];
  unsigned ll_symbols[288];
  unsigned d_symbols[32];
  size_t detect_block_size = *outsize;
  size_t compressed_size;
  size_t uncompressed_size = 0;
  size_t i;
  if (btype == 0)
  {
    size_t length = ZopfliLZ77GetByteRange(lz77, lstart, lend);
    size_t pos = (lstart == lend) ? (0) : (lz77->pos[lstart]);
    size_t end = pos + length;
    AddNonCompressedBlock(options, final, lz77->data, pos, end, bp, out, outsize);
    return;
  }
  AddBit(final, bp, out, outsize);
  AddBit(btype & 1, bp, out, outsize);
  AddBit((btype & 2) >> 1, bp, out, outsize);
  if (btype == 1)
  {
    GetFixedTree(ll_lengths, d_lengths);
  }
  else
  {
    unsigned detect_tree_size;
    assert(btype == 2);
    GetDynamicLengths(lz77, lstart, lend, ll_lengths, d_lengths);
    detect_tree_size = *outsize;
    AddDynamicTree(ll_lengths, d_lengths, bp, out, outsize);
    if (options->verbose)
    {
      fprintf(stderr, "treesize: %d\n", (int) ((*outsize) - detect_tree_size));
    }
  }
  ZopfliLengthsToSymbols(ll_lengths, 288, 15, ll_symbols);
  ZopfliLengthsToSymbols(d_lengths, 32, 15, d_symbols);
  detect_block_size = *outsize;
  AddLZ77Data(lz77, lstart, lend, expected_data_size, ll_symbols, ll_lengths, d_symbols, d_lengths, bp, out, outsize);
  AddHuffmanBits(ll_symbols[256], ll_lengths[256], bp, out, outsize);
  for (i = lstart; i < lend; i += 1)
  {
    uncompressed_size += (lz77->dists[i] == 0) ? (1) : (lz77->litlens[i]);
  }

  compressed_size = (*outsize) - detect_block_size;
  if (options->verbose)
  {
    fprintf(stderr, "compressed block size: %d (%dk) (unc: %d)\n", (int) compressed_size, (int) (compressed_size / 1024), (int) uncompressed_size);
  }
}


----------------------------
typedef struct ZopfliOptions
{
  int verbose;
  int verbose_more;
  int numiterations;
  int blocksplitting;
  int blocksplittinglast;
  int blocksplittingmax;
} ZopfliOptions
----------------------------
static void AddBits(unsigned symbol, unsigned length, unsigned char *bp, unsigned char **out, size_t *outsize)
{
  unsigned i;
  for (i = 0; i < length; i += 1)
  {
    unsigned bit = (symbol >> i) & 1;
    if ((*bp) == 0)
    {
      if (!((*outsize) & ((*outsize) - 1)))
      {
        *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
      }
      (*out)[*outsize] = 0;
      *outsize += 1;
    }
    ;
    (*out)[(*outsize) - 1] |= bit << (*bp);
    *bp = ((*bp) + 1) & 7;
  }

}


----------------------------
***/


void ZopfliDeflatePart(const ZopfliOptions *options, int btype, int final, const unsigned char *in, size_t instart, size_t inend, unsigned char *bp, unsigned char **out, size_t *outsize)
{
  size_t i;
  size_t *splitpoints_uncompressed = 0;
  size_t npoints = 0;
  size_t *splitpoints = 0;
  unsigned int splitpoints_idx = 0;
  double totalcost = 0;
  ZopfliLZ77Store lz77;
  if (btype == 0)
  {
    AddNonCompressedBlock(options, final, in, instart, inend, bp, out, outsize);
    return;
  }
  else
    if (btype == 1)
  {
    ZopfliLZ77Store store;
    ZopfliBlockState s;
    ZopfliInitLZ77Store(in, &store);
    ZopfliInitBlockState(options, instart, inend, 1, &s);
    ZopfliLZ77OptimalFixed(&s, in, instart, inend, &store);
    AddLZ77Block(options, btype, final, &store, 0, store.size, 0, bp, out, outsize);
    ZopfliCleanBlockState(&s);
    ZopfliCleanLZ77Store(&store);
    return;
  }
  if (options->blocksplitting)
  {
    ZopfliBlockSplit(options, in, instart, inend, options->blocksplittingmax, &splitpoints_uncompressed, &npoints);
    splitpoints_idx = (size_t *) malloc((sizeof(*splitpoints_idx)) * npoints);
  }
  ZopfliInitLZ77Store(in, &lz77);
  for (i = 0; i <= npoints; i += 1)
  {
    size_t start = (i == 0) ? (instart) : (splitpoints_uncompressed[i - 1]);
    size_t end = (i == npoints) ? (inend) : (splitpoints_uncompressed[i]);
    ZopfliBlockState s;
    ZopfliLZ77Store store;
    ZopfliInitLZ77Store(in, &store);
    ZopfliInitBlockState(options, start, end, 1, &s);
    ZopfliLZ77Optimal(&s, in, start, end, options->numiterations, &store);
    totalcost += ZopfliCalculateBlockSizeAutoType(&store, 0, store.size);
    ZopfliAppendLZ77Store(&store, &lz77);
    if (i < npoints)
    {
      splitpoints[i + splitpoints_idx] = lz77.size;
    }
    ZopfliCleanBlockState(&s);
    ZopfliCleanLZ77Store(&store);
  }

  if (options->blocksplitting && (npoints > 1))
  {
    size_t *splitpoints2 = 0;
    size_t npoints2 = 0;
    double totalcost2 = 0;
    ZopfliBlockSplitLZ77(options, &lz77, options->blocksplittingmax, &splitpoints2, &npoints2);
    for (i = 0; i <= npoints2; i += 1)
    {
      size_t start = (i == 0) ? (0) : (splitpoints2[i - 1]);
      size_t end = (i == npoints2) ? (lz77.size) : (splitpoints2[i]);
      totalcost2 += ZopfliCalculateBlockSizeAutoType(&lz77, start, end);
    }

    if (totalcost2 < totalcost)
    {
      free(splitpoints);
      splitpoints_idx = splitpoints2;
      npoints = npoints2;
    }
    else
    {
      free(splitpoints2);
    }
  }
  for (i = 0; i <= npoints; i += 1)
  {
    size_t start = (i == 0) ? (0) : (splitpoints[(i - 1) + splitpoints_idx]);
    size_t end = (i == npoints) ? (lz77.size) : (splitpoints[i + splitpoints_idx]);
    AddLZ77BlockAutoType(options, (i == npoints) && final, &lz77, start, end, 0, bp, out, outsize);
  }

  ZopfliCleanLZ77Store(&lz77);
  free(splitpoints);
  free(splitpoints_uncompressed);
}


/*** DEPENDENCIES:
typedef struct ZopfliLZ77Store
{
  unsigned short *litlens;
  unsigned short *dists;
  size_t size;
  const unsigned char *data;
  size_t *pos;
  unsigned short *ll_symbol;
  unsigned short *d_symbol;
  size_t *ll_counts;
  size_t *d_counts;
} ZopfliLZ77Store
----------------------------
double ZopfliCalculateBlockSizeAutoType(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend)
{
  double uncompressedcost = ZopfliCalculateBlockSize(lz77, lstart, lend, 0);
  double fixedcost = (lz77->size > 1000) ? (uncompressedcost) : (ZopfliCalculateBlockSize(lz77, lstart, lend, 1));
  double dyncost = ZopfliCalculateBlockSize(lz77, lstart, lend, 2);
  return ((uncompressedcost < fixedcost) && (uncompressedcost < dyncost)) ? (uncompressedcost) : ((fixedcost < dyncost) ? (fixedcost) : (dyncost));
}


----------------------------
void ZopfliLZ77OptimalFixed(ZopfliBlockState *s, const unsigned char *in, size_t instart, size_t inend, ZopfliLZ77Store *store)
{
  size_t blocksize = inend - instart;
  unsigned short *length_array = (unsigned short *) malloc((sizeof(unsigned short)) * (blocksize + 1));
  unsigned short *path = 0;
  size_t pathsize = 0;
  ZopfliHash hash;
  ZopfliHash *h = &hash;
  float *costs = (float *) malloc((sizeof(float)) * (blocksize + 1));
  if (!costs)
  {
    exit(-1);
  }
  if (!length_array)
  {
    exit(-1);
  }
  ZopfliAllocHash(32768, h);
  s->blockstart = instart;
  s->blockend = inend;
  LZ77OptimalRun(s, in, instart, inend, &path, &pathsize, length_array, GetCostFixed, 0, store, h, costs);
  free(length_array);
  free(path);
  free(costs);
  ZopfliCleanHash(h);
}


----------------------------
void ZopfliInitBlockState(const ZopfliOptions *options, size_t blockstart, size_t blockend, int add_lmc, ZopfliBlockState *s)
{
  s->options = options;
  s->blockstart = blockstart;
  s->blockend = blockend;
  if (add_lmc)
  {
    s->lmc = (ZopfliLongestMatchCache *) malloc(sizeof(ZopfliLongestMatchCache));
    ZopfliInitCache(blockend - blockstart, s->lmc);
  }
  else
  {
    s->lmc = 0;
  }
}


----------------------------
void ZopfliLZ77Optimal(ZopfliBlockState *s, const unsigned char *in, size_t instart, size_t inend, int numiterations, ZopfliLZ77Store *store)
{
  size_t blocksize = inend - instart;
  unsigned short *length_array = (unsigned short *) malloc((sizeof(unsigned short)) * (blocksize + 1));
  unsigned short *path = 0;
  size_t pathsize = 0;
  ZopfliLZ77Store currentstore;
  ZopfliHash hash;
  ZopfliHash *h = &hash;
  SymbolStats stats;
  SymbolStats beststats;
  SymbolStats laststats;
  int i;
  float *costs = (float *) malloc((sizeof(float)) * (blocksize + 1));
  double cost;
  double bestcost = 1e30;
  double lastcost = 0;
  RanState ran_state;
  int lastrandomstep = -1;
  if (!costs)
  {
    exit(-1);
  }
  if (!length_array)
  {
    exit(-1);
  }
  InitRanState(&ran_state);
  InitStats(&stats);
  ZopfliInitLZ77Store(in, &currentstore);
  ZopfliAllocHash(32768, h);
  ZopfliLZ77Greedy(s, in, instart, inend, &currentstore, h);
  GetStatistics(&currentstore, &stats);
  for (i = 0; i < numiterations; i += 1)
  {
    helper_ZopfliLZ77Optimal_1(&cost, &bestcost, &lastcost, &lastrandomstep, s, in, instart, inend, store, length_array, path, pathsize, currentstore, h, stats, beststats, laststats, i, costs, ran_state);
  }

  free(length_array);
  free(path);
  free(costs);
  ZopfliCleanLZ77Store(&currentstore);
  ZopfliCleanHash(h);
}


----------------------------
void ZopfliAppendLZ77Store(const ZopfliLZ77Store *store, ZopfliLZ77Store *target)
{
  size_t i;
  for (i = 0; i < store->size; i += 1)
  {
    ZopfliStoreLitLenDist(store->litlens[i], store->dists[i], store->pos[i], target);
  }

}


----------------------------
void ZopfliCleanLZ77Store(ZopfliLZ77Store *store)
{
  free(store->litlens);
  free(store->dists);
  free(store->pos);
  free(store->ll_symbol);
  free(store->d_symbol);
  free(store->ll_counts);
  free(store->d_counts);
}


----------------------------
typedef struct ZopfliBlockState
{
  const ZopfliOptions *options;
  ZopfliLongestMatchCache *lmc;
  size_t blockstart;
  size_t blockend;
} ZopfliBlockState
----------------------------
void ZopfliInitLZ77Store(const unsigned char *data, ZopfliLZ77Store *store)
{
  store->size = 0;
  store->litlens = 0;
  store->dists = 0;
  store->pos = 0;
  store->data = data;
  store->ll_symbol = 0;
  store->d_symbol = 0;
  store->ll_counts = 0;
  store->d_counts = 0;
}


----------------------------
void ZopfliCleanBlockState(ZopfliBlockState *s)
{
  if (s->lmc)
  {
    ZopfliCleanCache(s->lmc);
    free(s->lmc);
  }
}


----------------------------
static void AddLZ77BlockAutoType(const ZopfliOptions *options, int final, const ZopfliLZ77Store *lz77, size_t lstart, size_t lend, size_t expected_data_size, unsigned char *bp, unsigned char **out, size_t *outsize)
{
  double uncompressedcost = ZopfliCalculateBlockSize(lz77, lstart, lend, 0);
  double fixedcost = ZopfliCalculateBlockSize(lz77, lstart, lend, 1);
  double dyncost = ZopfliCalculateBlockSize(lz77, lstart, lend, 2);
  int expensivefixed = (lz77->size < 1000) || (fixedcost <= (dyncost * 1.1));
  ZopfliLZ77Store fixedstore;
  if (lstart == lend)
  {
    AddBits(final, 1, bp, out, outsize);
    AddBits(1, 2, bp, out, outsize);
    AddBits(0, 7, bp, out, outsize);
    return;
  }
  ZopfliInitLZ77Store(lz77->data, &fixedstore);
  if (expensivefixed)
  {
    size_t instart = lz77->pos[lstart];
    size_t inend = instart + ZopfliLZ77GetByteRange(lz77, lstart, lend);
    ZopfliBlockState s;
    ZopfliInitBlockState(options, instart, inend, 1, &s);
    ZopfliLZ77OptimalFixed(&s, lz77->data, instart, inend, &fixedstore);
    fixedcost = ZopfliCalculateBlockSize(&fixedstore, 0, fixedstore.size, 1);
    ZopfliCleanBlockState(&s);
  }
  if ((uncompressedcost < fixedcost) && (uncompressedcost < dyncost))
  {
    AddLZ77Block(options, 0, final, lz77, lstart, lend, expected_data_size, bp, out, outsize);
  }
  else
    if (fixedcost < dyncost)
  {
    if (expensivefixed)
    {
      AddLZ77Block(options, 1, final, &fixedstore, 0, fixedstore.size, expected_data_size, bp, out, outsize);
    }
    else
    {
      AddLZ77Block(options, 1, final, lz77, lstart, lend, expected_data_size, bp, out, outsize);
    }
  }
  else
  {
    AddLZ77Block(options, 2, final, lz77, lstart, lend, expected_data_size, bp, out, outsize);
  }
  ZopfliCleanLZ77Store(&fixedstore);
}


----------------------------
static void AddLZ77Block(const ZopfliOptions *options, int btype, int final, const ZopfliLZ77Store *lz77, size_t lstart, size_t lend, size_t expected_data_size, unsigned char *bp, unsigned char **out, size_t *outsize)
{
  unsigned ll_lengths[288];
  unsigned d_lengths[32];
  unsigned ll_symbols[288];
  unsigned d_symbols[32];
  size_t detect_block_size = *outsize;
  size_t compressed_size;
  size_t uncompressed_size = 0;
  size_t i;
  if (btype == 0)
  {
    size_t length = ZopfliLZ77GetByteRange(lz77, lstart, lend);
    size_t pos = (lstart == lend) ? (0) : (lz77->pos[lstart]);
    size_t end = pos + length;
    AddNonCompressedBlock(options, final, lz77->data, pos, end, bp, out, outsize);
    return;
  }
  AddBit(final, bp, out, outsize);
  AddBit(btype & 1, bp, out, outsize);
  AddBit((btype & 2) >> 1, bp, out, outsize);
  if (btype == 1)
  {
    GetFixedTree(ll_lengths, d_lengths);
  }
  else
  {
    unsigned detect_tree_size;
    assert(btype == 2);
    GetDynamicLengths(lz77, lstart, lend, ll_lengths, d_lengths);
    detect_tree_size = *outsize;
    AddDynamicTree(ll_lengths, d_lengths, bp, out, outsize);
    if (options->verbose)
    {
      fprintf(stderr, "treesize: %d\n", (int) ((*outsize) - detect_tree_size));
    }
  }
  ZopfliLengthsToSymbols(ll_lengths, 288, 15, ll_symbols);
  ZopfliLengthsToSymbols(d_lengths, 32, 15, d_symbols);
  detect_block_size = *outsize;
  AddLZ77Data(lz77, lstart, lend, expected_data_size, ll_symbols, ll_lengths, d_symbols, d_lengths, bp, out, outsize);
  AddHuffmanBits(ll_symbols[256], ll_lengths[256], bp, out, outsize);
  for (i = lstart; i < lend; i += 1)
  {
    uncompressed_size += (lz77->dists[i] == 0) ? (1) : (lz77->litlens[i]);
  }

  compressed_size = (*outsize) - detect_block_size;
  if (options->verbose)
  {
    fprintf(stderr, "compressed block size: %d (%dk) (unc: %d)\n", (int) compressed_size, (int) (compressed_size / 1024), (int) uncompressed_size);
  }
}


----------------------------
void ZopfliBlockSplit(const ZopfliOptions *options, const unsigned char *in, size_t instart, size_t inend, size_t maxblocks, size_t **splitpoints, size_t *npoints)
{
  size_t pos = 0;
  size_t i;
  ZopfliBlockState s;
  size_t *lz77splitpoints = 0;
  size_t nlz77points = 0;
  ZopfliLZ77Store store;
  ZopfliHash hash;
  ZopfliHash *h = &hash;
  ZopfliInitLZ77Store(in, &store);
  ZopfliInitBlockState(options, instart, inend, 0, &s);
  ZopfliAllocHash(32768, h);
  *npoints = 0;
  *splitpoints = 0;
  ZopfliLZ77Greedy(&s, in, instart, inend, &store, h);
  ZopfliBlockSplitLZ77(options, &store, maxblocks, &lz77splitpoints, &nlz77points);
  pos = instart;
  if (nlz77points > 0)
  {
    for (i = 0; i < store.size; i += 1)
    {
      size_t length = (store.dists[i] == 0) ? (1) : (store.litlens[i]);
      if (lz77splitpoints[*npoints] == i)
      {
        {
          if (!((*npoints) & ((*npoints) - 1)))
          {
            *splitpoints = ((*npoints) == 0) ? (malloc(sizeof(*(*splitpoints)))) : (realloc(*splitpoints, ((*npoints) * 2) * (sizeof(*(*splitpoints)))));
          }
          (*splitpoints)[*npoints] = pos;
          *npoints += 1;
        }
        ;
        if ((*npoints) == nlz77points)
        {
          break;
        }
      }
      pos += length;
    }

  }
  assert((*npoints) == nlz77points);
  free(lz77splitpoints);
  ZopfliCleanBlockState(&s);
  ZopfliCleanLZ77Store(&store);
  ZopfliCleanHash(h);
}


----------------------------
typedef struct ZopfliOptions
{
  int verbose;
  int verbose_more;
  int numiterations;
  int blocksplitting;
  int blocksplittinglast;
  int blocksplittingmax;
} ZopfliOptions
----------------------------
void ZopfliBlockSplitLZ77(const ZopfliOptions *options, const ZopfliLZ77Store *lz77, size_t maxblocks, size_t **splitpoints, size_t *npoints)
{
  size_t lstart;
  size_t lend;
  size_t i;
  size_t llpos = 0;
  size_t numblocks = 1;
  unsigned char *done;
  unsigned int done_idx = 0;
  double splitcost;
  double origcost;
  if (lz77->size < 10)
  {
    return;
  }
  done_idx = (unsigned char *) malloc(lz77->size);
  if (!(&done[done_idx]))
  {
    exit(-1);
  }
  for (i = 0; i < lz77->size; i += 1)
    done[i + done_idx] = 0;

  lstart = 0;
  lend = lz77->size;
  for (;;)
  {
    helper_ZopfliBlockSplitLZ77_1(&lstart, &llpos, &numblocks, &done_idx, &origcost, lz77, maxblocks, splitpoints, npoints, lend, done, splitcost);
  }

  if (options->verbose)
  {
    PrintBlockSplitPoints(lz77, *splitpoints, *npoints);
  }
  free(done);
}


----------------------------
static void AddNonCompressedBlock(const ZopfliOptions *options, int final, const unsigned char *in, size_t instart, size_t inend, unsigned char *bp, unsigned char **out, size_t *outsize)
{
  size_t pos = instart;
  (void) options;
  for (;;)
  {
    helper_AddNonCompressedBlock_1(&pos, final, in, inend, bp, out, outsize);
  }

}


----------------------------
***/


void ZopfliDeflate(const ZopfliOptions *options, int btype, int final, const unsigned char *in, size_t insize, unsigned char *bp, unsigned char **out, size_t *outsize)
{
  size_t offset = *outsize;
  size_t i = 0;
  do
  {
    int masterfinal = (i + 1000000) >= insize;
    int final2 = final && masterfinal;
    size_t size = (masterfinal) ? (insize - i) : (1000000);
    ZopfliDeflatePart(options, btype, final2, in, i, i + size, bp, out, outsize);
    i += size;
  }
  while (i < insize);
  if (options->verbose)
  {
    fprintf(stderr, "Original Size: %lu, Deflate: %lu, Compression: %f%% Removed\n", (unsigned long) insize, (unsigned long) ((*outsize) - offset), (100.0 * ((double) (insize - ((*outsize) - offset)))) / ((double) insize));
  }
}


/*** DEPENDENCIES:
void ZopfliDeflatePart(const ZopfliOptions *options, int btype, int final, const unsigned char *in, size_t instart, size_t inend, unsigned char *bp, unsigned char **out, size_t *outsize)
{
  size_t i;
  size_t *splitpoints_uncompressed = 0;
  size_t npoints = 0;
  size_t *splitpoints = 0;
  unsigned int splitpoints_idx = 0;
  double totalcost = 0;
  ZopfliLZ77Store lz77;
  if (btype == 0)
  {
    AddNonCompressedBlock(options, final, in, instart, inend, bp, out, outsize);
    return;
  }
  else
    if (btype == 1)
  {
    ZopfliLZ77Store store;
    ZopfliBlockState s;
    ZopfliInitLZ77Store(in, &store);
    ZopfliInitBlockState(options, instart, inend, 1, &s);
    ZopfliLZ77OptimalFixed(&s, in, instart, inend, &store);
    AddLZ77Block(options, btype, final, &store, 0, store.size, 0, bp, out, outsize);
    ZopfliCleanBlockState(&s);
    ZopfliCleanLZ77Store(&store);
    return;
  }
  if (options->blocksplitting)
  {
    ZopfliBlockSplit(options, in, instart, inend, options->blocksplittingmax, &splitpoints_uncompressed, &npoints);
    splitpoints_idx = (size_t *) malloc((sizeof(*splitpoints_idx)) * npoints);
  }
  ZopfliInitLZ77Store(in, &lz77);
  for (i = 0; i <= npoints; i += 1)
  {
    size_t start = (i == 0) ? (instart) : (splitpoints_uncompressed[i - 1]);
    size_t end = (i == npoints) ? (inend) : (splitpoints_uncompressed[i]);
    ZopfliBlockState s;
    ZopfliLZ77Store store;
    ZopfliInitLZ77Store(in, &store);
    ZopfliInitBlockState(options, start, end, 1, &s);
    ZopfliLZ77Optimal(&s, in, start, end, options->numiterations, &store);
    totalcost += ZopfliCalculateBlockSizeAutoType(&store, 0, store.size);
    ZopfliAppendLZ77Store(&store, &lz77);
    if (i < npoints)
    {
      splitpoints[i + splitpoints_idx] = lz77.size;
    }
    ZopfliCleanBlockState(&s);
    ZopfliCleanLZ77Store(&store);
  }

  if (options->blocksplitting && (npoints > 1))
  {
    size_t *splitpoints2 = 0;
    size_t npoints2 = 0;
    double totalcost2 = 0;
    ZopfliBlockSplitLZ77(options, &lz77, options->blocksplittingmax, &splitpoints2, &npoints2);
    for (i = 0; i <= npoints2; i += 1)
    {
      size_t start = (i == 0) ? (0) : (splitpoints2[i - 1]);
      size_t end = (i == npoints2) ? (lz77.size) : (splitpoints2[i]);
      totalcost2 += ZopfliCalculateBlockSizeAutoType(&lz77, start, end);
    }

    if (totalcost2 < totalcost)
    {
      free(splitpoints);
      splitpoints_idx = splitpoints2;
      npoints = npoints2;
    }
    else
    {
      free(splitpoints2);
    }
  }
  for (i = 0; i <= npoints; i += 1)
  {
    size_t start = (i == 0) ? (0) : (splitpoints[(i - 1) + splitpoints_idx]);
    size_t end = (i == npoints) ? (lz77.size) : (splitpoints[i + splitpoints_idx]);
    AddLZ77BlockAutoType(options, (i == npoints) && final, &lz77, start, end, 0, bp, out, outsize);
  }

  ZopfliCleanLZ77Store(&lz77);
  free(splitpoints);
  free(splitpoints_uncompressed);
}


----------------------------
typedef struct ZopfliOptions
{
  int verbose;
  int verbose_more;
  int numiterations;
  int blocksplitting;
  int blocksplittinglast;
  int blocksplittingmax;
} ZopfliOptions
----------------------------
***/


