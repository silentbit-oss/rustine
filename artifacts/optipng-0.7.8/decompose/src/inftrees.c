// hint:  ['curr_ref is a mutable refrence to unsigned', 'drop_ref is a mutable refrence to unsigned', 'left_ref is a mutable refrence to int', 'used_ref is a mutable refrence to unsigned', 'low_ref is a mutable refrence to unsigned', 'next_idx_ref is a mutable refrence to unsigned int']
int helper_helper_inflate_table_1_1(unsigned * const curr_ref, unsigned * const drop_ref, int * const left_ref, unsigned * const used_ref, unsigned * const low_ref, unsigned int * const next_idx_ref, codetype type, code ** const table, unsigned max, unsigned root, unsigned mask, code * const next, unsigned short count[15 + 1], unsigned len, unsigned min, unsigned huff)
{
  unsigned curr = *curr_ref;
  unsigned drop = *drop_ref;
  int left = *left_ref;
  unsigned used = *used_ref;
  unsigned low = *low_ref;
  unsigned int next_idx = *next_idx_ref;
  if (drop == 0)
  {
    drop = root;
  }
  next_idx += min;
  curr = len - drop;
  left = (int) (1 << curr);
  while ((curr + drop) < max)
  {
    left -= count[curr + drop];
    if (left <= 0)
    {
      break;
    }
    curr += 1;
    left <<= 1;
  }

  used += 1U << curr;
  if (((type == LENS) && (used > 852)) || ((type == DISTS) && (used > 592)))
  {
    return 1;
  }
  low = huff & mask;
  (*table)[low].op = (unsigned char) curr;
  (*table)[low].bits = (unsigned char) root;
  (*table)[low].val = (unsigned short) ((&next[next_idx]) - (*table));
  *curr_ref = curr;
  *drop_ref = drop;
  *left_ref = left;
  *used_ref = used;
  *low_ref = low;
  *next_idx_ref = next_idx;
}


/*** DEPENDENCIES:
typedef enum 
{
  CODES,
  LENS,
  DISTS
} codetype
----------------------------
typedef struct 
{
  unsigned char op;
  unsigned char bits;
  unsigned short val;
} code
----------------------------
***/


// hint:  ['len_ref is a mutable refrence to unsigned', 'sym_ref is a mutable refrence to unsigned', 'min_ref is a mutable refrence to unsigned', 'curr_ref is a mutable refrence to unsigned', 'drop_ref is a mutable refrence to unsigned', 'left_ref is a mutable refrence to int', 'used_ref is a mutable refrence to unsigned', 'huff_ref is a mutable refrence to unsigned', 'incr_ref is a mutable refrence to unsigned', 'fill_ref is a mutable refrence to unsigned', 'low_ref is a mutable refrence to unsigned', 'here_ref is a mutable refrence to code', 'next_idx_ref is a mutable refrence to unsigned int']
int helper_inflate_table_1(unsigned * const len_ref, unsigned * const sym_ref, unsigned * const min_ref, unsigned * const curr_ref, unsigned * const drop_ref, int * const left_ref, unsigned * const used_ref, unsigned * const huff_ref, unsigned * const incr_ref, unsigned * const fill_ref, unsigned * const low_ref, code * const here_ref, unsigned int * const next_idx_ref, codetype type, unsigned short * const lens, code ** const table, unsigned short * const work, unsigned max, unsigned root, unsigned mask, code * const next, const unsigned short * const base, unsigned int base_idx, const unsigned short * const extra, unsigned int extra_idx, unsigned match, unsigned short count[15 + 1])
{
  unsigned len = *len_ref;
  unsigned sym = *sym_ref;
  unsigned min = *min_ref;
  unsigned curr = *curr_ref;
  unsigned drop = *drop_ref;
  int left = *left_ref;
  unsigned used = *used_ref;
  unsigned huff = *huff_ref;
  unsigned incr = *incr_ref;
  unsigned fill = *fill_ref;
  unsigned low = *low_ref;
  code here = *here_ref;
  unsigned int next_idx = *next_idx_ref;
  here.bits = (unsigned char) (len - drop);
  if ((work[sym] + 1U) < match)
  {
    here.op = (unsigned char) 0;
    here.val = work[sym];
  }
  else
    if (work[sym] >= match)
  {
    here.op = (unsigned char) extra[(work[sym] - match) + extra_idx];
    here.val = base[(work[sym] - match) + base_idx];
  }
  else
  {
    here.op = (unsigned char) (32 + 64);
    here.val = 0;
  }
  incr = 1U << (len - drop);
  fill = 1U << curr;
  min = fill;
  do
  {
    fill -= incr;
    next[((huff >> drop) + fill) + next_idx] = here;
  }
  while (fill != 0);
  incr = 1U << (len - 1);
  while (huff & incr)
  {
    incr >>= 1;
  }

  if (incr != 0)
  {
    huff &= incr - 1;
    huff += incr;
  }
  else
    huff = 0;
  sym += 1;
  if ((--count[len]) == 0)
  {
    if (len == max)
    {
      break;
    }
    len = lens[work[sym]];
  }
  if ((len > root) && ((huff & mask) != low))
  {
    helper_helper_inflate_table_1_1(&curr, &drop, &left, &used, &low, &next_idx, type, table, max, root, mask, next, count, len, min, huff);
  }
  *len_ref = len;
  *sym_ref = sym;
  *min_ref = min;
  *curr_ref = curr;
  *drop_ref = drop;
  *left_ref = left;
  *used_ref = used;
  *huff_ref = huff;
  *incr_ref = incr;
  *fill_ref = fill;
  *low_ref = low;
  *here_ref = here;
  *next_idx_ref = next_idx;
}


/*** DEPENDENCIES:
typedef enum 
{
  CODES,
  LENS,
  DISTS
} codetype
----------------------------
typedef struct 
{
  unsigned char op;
  unsigned char bits;
  unsigned short val;
} code
----------------------------
int helper_helper_inflate_table_1_1(unsigned * const curr_ref, unsigned * const drop_ref, int * const left_ref, unsigned * const used_ref, unsigned * const low_ref, unsigned int * const next_idx_ref, codetype type, code ** const table, unsigned max, unsigned root, unsigned mask, code * const next, unsigned short count[15 + 1], unsigned len, unsigned min, unsigned huff)
{
  unsigned curr = *curr_ref;
  unsigned drop = *drop_ref;
  int left = *left_ref;
  unsigned used = *used_ref;
  unsigned low = *low_ref;
  unsigned int next_idx = *next_idx_ref;
  if (drop == 0)
  {
    drop = root;
  }
  next_idx += min;
  curr = len - drop;
  left = (int) (1 << curr);
  while ((curr + drop) < max)
  {
    left -= count[curr + drop];
    if (left <= 0)
    {
      break;
    }
    curr += 1;
    left <<= 1;
  }

  used += 1U << curr;
  if (((type == LENS) && (used > 852)) || ((type == DISTS) && (used > 592)))
  {
    return 1;
  }
  low = huff & mask;
  (*table)[low].op = (unsigned char) curr;
  (*table)[low].bits = (unsigned char) root;
  (*table)[low].val = (unsigned short) ((&next[next_idx]) - (*table));
  *curr_ref = curr;
  *drop_ref = drop;
  *left_ref = left;
  *used_ref = used;
  *low_ref = low;
  *next_idx_ref = next_idx;
}


----------------------------
***/


int inflate_table(codetype type, unsigned short *lens, unsigned codes, code **table, unsigned *bits, unsigned short *work)
{
  unsigned len;
  unsigned sym;
  unsigned min;
  unsigned max;
  unsigned root;
  unsigned curr;
  unsigned drop;
  int left;
  unsigned used;
  unsigned huff;
  unsigned incr;
  unsigned fill;
  unsigned low;
  unsigned mask;
  code here;
  code *next;
  unsigned int next_idx = 0;
  const unsigned short *base;
  unsigned int base_idx = 0;
  const unsigned short *extra;
  unsigned int extra_idx = 0;
  unsigned match;
  unsigned short count[15 + 1];
  unsigned short offs[15 + 1];
  static const unsigned short lbase[31] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 15, 17, 19, 23, 27, 31, 35, 43, 51, 59, 67, 83, 99, 115, 131, 163, 195, 227, 258, 0, 0};
  static const unsigned short lext[31] = {16, 16, 16, 16, 16, 16, 16, 16, 17, 17, 17, 17, 18, 18, 18, 18, 19, 19, 19, 19, 20, 20, 20, 20, 21, 21, 21, 21, 16, 198, 203};
  static const unsigned short dbase[32] = {1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193, 257, 385, 513, 769, 1025, 1537, 2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577, 0, 0};
  static const unsigned short dext[32] = {16, 16, 16, 16, 17, 17, 18, 18, 19, 19, 20, 20, 21, 21, 22, 22, 23, 23, 24, 24, 25, 25, 26, 26, 27, 27, 28, 28, 29, 29, 64, 64};
  for (len = 0; len <= 15; len += 1)
  {
    count[len] = 0;
  }

  for (sym = 0; sym < codes; sym += 1)
  {
    count[lens[sym]] += 1;
  }

  root = *bits;
  for (max = 15; max >= 1; max -= 1)
  {
    if (count[max] != 0)
    {
      break;
    }
  }

  if (root > max)
  {
    root = max;
  }
  if (max == 0)
  {
    here.op = (unsigned char) 64;
    here.bits = (unsigned char) 1;
    here.val = (unsigned short) 0;
    *((*table)++) = here;
    *((*table)++) = here;
    *bits = 1;
    return 0;
  }
  for (min = 1; min < max; min += 1)
  {
    if (count[min] != 0)
    {
      break;
    }
  }

  if (root < min)
  {
    root = min;
  }
  left = 1;
  for (len = 1; len <= 15; len += 1)
  {
    left <<= 1;
    left -= count[len];
    if (left < 0)
    {
      return -1;
    }
  }

  if ((left > 0) && ((type == CODES) || (max != 1)))
  {
    return -1;
  }
  offs[1] = 0;
  for (len = 1; len < 15; len += 1)
  {
    offs[len + 1] = offs[len] + count[len];
  }

  for (sym = 0; sym < codes; sym += 1)
  {
    if (lens[sym] != 0)
    {
      work[offs[lens[sym]]++] = (unsigned short) sym;
    }
  }

  switch (type)
  {
    case CODES:
    {
      base_idx = (extra = &extra[extra_idx + extra_idx]);
      match = 20;
      break;
    }

    case LENS:
    {
      base_idx = lbase;
      extra_idx = lext;
      match = 257;
      break;
    }

    default:
    {
      base_idx = dbase;
      extra_idx = dext;
      match = 0;
    }

  }

  huff = 0;
  sym = 0;
  len = min;
  next_idx = *table;
  curr = root;
  drop = 0;
  low = (unsigned) (-1);
  used = 1U << root;
  mask = used - 1;
  if (((type == LENS) && (used > 852)) || ((type == DISTS) && (used > 592)))
  {
    return 1;
  }
  for (;;)
  {
    helper_inflate_table_1(&len, &sym, &min, &curr, &drop, &left, &used, &huff, &incr, &fill, &low, &here, &next_idx, type, lens, table, work, max, root, mask, next, base, base_idx, extra, extra_idx, match, count);
  }

  if (huff != 0)
  {
    here.op = (unsigned char) 64;
    here.bits = (unsigned char) (len - drop);
    here.val = (unsigned short) 0;
    next[huff + next_idx] = here;
  }
  *table += used;
  *bits = root;
  return 0;
}


/*** DEPENDENCIES:
int helper_inflate_table_1(unsigned * const len_ref, unsigned * const sym_ref, unsigned * const min_ref, unsigned * const curr_ref, unsigned * const drop_ref, int * const left_ref, unsigned * const used_ref, unsigned * const huff_ref, unsigned * const incr_ref, unsigned * const fill_ref, unsigned * const low_ref, code * const here_ref, unsigned int * const next_idx_ref, codetype type, unsigned short * const lens, code ** const table, unsigned short * const work, unsigned max, unsigned root, unsigned mask, code * const next, const unsigned short * const base, unsigned int base_idx, const unsigned short * const extra, unsigned int extra_idx, unsigned match, unsigned short count[15 + 1])
{
  unsigned len = *len_ref;
  unsigned sym = *sym_ref;
  unsigned min = *min_ref;
  unsigned curr = *curr_ref;
  unsigned drop = *drop_ref;
  int left = *left_ref;
  unsigned used = *used_ref;
  unsigned huff = *huff_ref;
  unsigned incr = *incr_ref;
  unsigned fill = *fill_ref;
  unsigned low = *low_ref;
  code here = *here_ref;
  unsigned int next_idx = *next_idx_ref;
  here.bits = (unsigned char) (len - drop);
  if ((work[sym] + 1U) < match)
  {
    here.op = (unsigned char) 0;
    here.val = work[sym];
  }
  else
    if (work[sym] >= match)
  {
    here.op = (unsigned char) extra[(work[sym] - match) + extra_idx];
    here.val = base[(work[sym] - match) + base_idx];
  }
  else
  {
    here.op = (unsigned char) (32 + 64);
    here.val = 0;
  }
  incr = 1U << (len - drop);
  fill = 1U << curr;
  min = fill;
  do
  {
    fill -= incr;
    next[((huff >> drop) + fill) + next_idx] = here;
  }
  while (fill != 0);
  incr = 1U << (len - 1);
  while (huff & incr)
  {
    incr >>= 1;
  }

  if (incr != 0)
  {
    huff &= incr - 1;
    huff += incr;
  }
  else
    huff = 0;
  sym += 1;
  if ((--count[len]) == 0)
  {
    if (len == max)
    {
      break;
    }
    len = lens[work[sym]];
  }
  if ((len > root) && ((huff & mask) != low))
  {
    helper_helper_inflate_table_1_1(&curr, &drop, &left, &used, &low, &next_idx, type, table, max, root, mask, next, count, len, min, huff);
  }
  *len_ref = len;
  *sym_ref = sym;
  *min_ref = min;
  *curr_ref = curr;
  *drop_ref = drop;
  *left_ref = left;
  *used_ref = used;
  *huff_ref = huff;
  *incr_ref = incr;
  *fill_ref = fill;
  *low_ref = low;
  *here_ref = here;
  *next_idx_ref = next_idx;
}


----------------------------
typedef enum 
{
  CODES,
  LENS,
  DISTS
} codetype
----------------------------
typedef struct 
{
  unsigned char op;
  unsigned char bits;
  unsigned short val;
} code
----------------------------
***/


