static size_t zopfli_min(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


/*** DEPENDENCIES:
***/


static void TraceBackwards(size_t size, const unsigned short *length_array, unsigned short **path, size_t *pathsize)
{
  size_t index = size;
  if (size == 0)
  {
    return;
  }
  for (;;)
  {
    {
      if (!((*pathsize) & ((*pathsize) - 1)))
      {
        *path = ((*pathsize) == 0) ? (malloc(sizeof(*(*path)))) : (realloc(*path, ((*pathsize) * 2) * (sizeof(*(*path)))));
      }
      (*path)[*pathsize] = length_array[index];
      *pathsize += 1;
    }
    ;
    assert(length_array[index] <= index);
    assert(length_array[index] <= 258);
    assert(length_array[index] != 0);
    index -= length_array[index];
    if (index == 0)
    {
      break;
    }
  }

  for (index = 0; index < ((*pathsize) / 2); index += 1)
  {
    unsigned short temp = (*path)[index];
    (*path)[index] = (*path)[((*pathsize) - index) - 1];
    (*path)[((*pathsize) - index) - 1] = temp;
  }

}


/*** DEPENDENCIES:
***/


static void InitStats(SymbolStats *stats)
{
  memset(stats->litlens, 0, 288 * (sizeof(stats->litlens[0])));
  memset(stats->dists, 0, 32 * (sizeof(stats->dists[0])));
  memset(stats->ll_symbols, 0, 288 * (sizeof(stats->ll_symbols[0])));
  memset(stats->d_symbols, 0, 32 * (sizeof(stats->d_symbols[0])));
}


/*** DEPENDENCIES:
typedef struct SymbolStats
{
  size_t litlens[288];
  size_t dists[32];
  double ll_symbols[288];
  double d_symbols[32];
} SymbolStats
----------------------------
***/


static void CopyStats(SymbolStats *source, SymbolStats *dest)
{
  memcpy(dest->litlens, source->litlens, 288 * (sizeof(dest->litlens[0])));
  memcpy(dest->dists, source->dists, 32 * (sizeof(dest->dists[0])));
  memcpy(dest->ll_symbols, source->ll_symbols, 288 * (sizeof(dest->ll_symbols[0])));
  memcpy(dest->d_symbols, source->d_symbols, 32 * (sizeof(dest->d_symbols[0])));
}


/*** DEPENDENCIES:
typedef struct SymbolStats
{
  size_t litlens[288];
  size_t dists[32];
  double ll_symbols[288];
  double d_symbols[32];
} SymbolStats
----------------------------
***/


static void AddWeighedStatFreqs(const SymbolStats *stats1, double w1, const SymbolStats *stats2, double w2, SymbolStats *result)
{
  size_t i;
  for (i = 0; i < 288; i += 1)
  {
    result->litlens[i] = (size_t) ((stats1->litlens[i] * w1) + (stats2->litlens[i] * w2));
  }

  for (i = 0; i < 32; i += 1)
  {
    result->dists[i] = (size_t) ((stats1->dists[i] * w1) + (stats2->dists[i] * w2));
  }

  result->litlens[256] = 1;
}


/*** DEPENDENCIES:
typedef struct SymbolStats
{
  size_t litlens[288];
  size_t dists[32];
  double ll_symbols[288];
  double d_symbols[32];
} SymbolStats
----------------------------
***/


static void InitRanState(RanState *state)
{
  state->m_w = 1;
  state->m_z = 2;
}


/*** DEPENDENCIES:
typedef struct RanState
{
  unsigned int m_w;
  unsigned int m_z;
} RanState
----------------------------
***/


static unsigned int Ran(RanState *state)
{
  state->m_z = (36969 * (state->m_z & 65535)) + (state->m_z >> 16);
  state->m_w = (18000 * (state->m_w & 65535)) + (state->m_w >> 16);
  return (state->m_z << 16) + state->m_w;
}


/*** DEPENDENCIES:
typedef struct RanState
{
  unsigned int m_w;
  unsigned int m_z;
} RanState
----------------------------
***/


static void ClearStatFreqs(SymbolStats *stats)
{
  size_t i;
  for (i = 0; i < 288; i += 1)
    stats->litlens[i] = 0;

  for (i = 0; i < 32; i += 1)
    stats->dists[i] = 0;

}


/*** DEPENDENCIES:
typedef struct SymbolStats
{
  size_t litlens[288];
  size_t dists[32];
  double ll_symbols[288];
  double d_symbols[32];
} SymbolStats
----------------------------
***/


static double GetCostModelMinCost(CostModelFun *costmodel, void *costcontext)
{
  double mincost;
  int bestlength = 0;
  int bestdist = 0;
  int i;
  static const int dsymbols[30] = {1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193, 257, 385, 513, 769, 1025, 1537, 2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577};
  mincost = 1e30;
  for (i = 3; i < 259; i += 1)
  {
    double c = costmodel(i, 1, costcontext);
    if (c < mincost)
    {
      bestlength = i;
      mincost = c;
    }
  }

  mincost = 1e30;
  for (i = 0; i < 30; i += 1)
  {
    double c = costmodel(3, dsymbols[i], costcontext);
    if (c < mincost)
    {
      bestdist = dsymbols[i];
      mincost = c;
    }
  }

  return costmodel(bestlength, bestdist, costcontext);
}


/*** DEPENDENCIES:
typedef double CostModelFun(unsigned litlen, unsigned dist, void *context)
----------------------------
***/


static void FollowPath(ZopfliBlockState *s, const unsigned char *in, size_t instart, size_t inend, unsigned short *path, size_t pathsize, ZopfliLZ77Store *store, ZopfliHash *h)
{
  size_t i;
  size_t j;
  size_t pos = 0;
  size_t windowstart = (instart > 32768) ? (instart - 32768) : (0);
  size_t total_length_test = 0;
  if (instart == inend)
  {
    return;
  }
  ZopfliResetHash(32768, h);
  ZopfliWarmupHash(in, windowstart, inend, h);
  for (i = windowstart; i < instart; i += 1)
  {
    ZopfliUpdateHash(in, i, inend, h);
  }

  pos = instart;
  for (i = 0; i < pathsize; i += 1)
  {
    unsigned short length = path[i];
    unsigned short dummy_length;
    unsigned short dist;
    assert(pos < inend);
    ZopfliUpdateHash(in, pos, inend, h);
    if (length >= 3)
    {
      ZopfliFindLongestMatch(s, h, in, pos, inend, length, 0, &dist, &dummy_length);
      assert(!(((dummy_length != length) && (length > 2)) && (dummy_length > 2)));
      ZopfliVerifyLenDist(in, inend, pos, dist, length);
      ZopfliStoreLitLenDist(length, dist, pos, store);
      total_length_test += length;
    }
    else
    {
      length = 1;
      ZopfliStoreLitLenDist(in[pos], 0, pos, store);
      total_length_test += 1;
    }
    assert((pos + length) <= inend);
    for (j = 1; j < length; j += 1)
    {
      ZopfliUpdateHash(in, pos + j, inend, h);
    }

    pos += length;
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
typedef struct ZopfliHash
{
  int *head;
  unsigned short *prev;
  int *hashval;
  int val;
  int *head2;
  unsigned short *prev2;
  int *hashval2;
  int val2;
  unsigned short *same;
} ZopfliHash
----------------------------
void ZopfliStoreLitLenDist(unsigned short length, unsigned short dist, size_t pos, ZopfliLZ77Store *store)
{
  size_t i;
  size_t origsize = store->size;
  size_t llstart = 288 * (origsize / 288);
  size_t dstart = 32 * (origsize / 32);
  if ((origsize % 288) == 0)
  {
    size_t llsize = origsize;
    for (i = 0; i < 288; i += 1)
    {
      {
        if (!((*(&llsize)) & ((*(&llsize)) - 1)))
        {
          store->ll_counts = (llsize == 0) ? (malloc(sizeof(*(*(&store->ll_counts))))) : (realloc(*(&store->ll_counts), (llsize * 2) * (sizeof(*(*(&store->ll_counts))))));
        }
        store->ll_counts[llsize] = (origsize == 0) ? (0) : (store->ll_counts[(origsize - 288) + i]);
        llsize += 1;
      }
      ;
    }

  }
  if ((origsize % 32) == 0)
  {
    size_t dsize = origsize;
    for (i = 0; i < 32; i += 1)
    {
      {
        if (!((*(&dsize)) & ((*(&dsize)) - 1)))
        {
          store->d_counts = (dsize == 0) ? (malloc(sizeof(*(*(&store->d_counts))))) : (realloc(*(&store->d_counts), (dsize * 2) * (sizeof(*(*(&store->d_counts))))));
        }
        store->d_counts[dsize] = (origsize == 0) ? (0) : (store->d_counts[(origsize - 32) + i]);
        dsize += 1;
      }
      ;
    }

  }
  {
    if (!((*(&store->size)) & ((*(&store->size)) - 1)))
    {
      store->litlens = (store->size == 0) ? (malloc(sizeof(*(*(&store->litlens))))) : (realloc(*(&store->litlens), (store->size * 2) * (sizeof(*(*(&store->litlens))))));
    }
    store->litlens[store->size] = length;
    store->size += 1;
  }
  ;
  store->size = origsize;
  {
    if (!((*(&store->size)) & ((*(&store->size)) - 1)))
    {
      store->dists = (store->size == 0) ? (malloc(sizeof(*(*(&store->dists))))) : (realloc(*(&store->dists), (store->size * 2) * (sizeof(*(*(&store->dists))))));
    }
    store->dists[store->size] = dist;
    store->size += 1;
  }
  ;
  store->size = origsize;
  {
    if (!((*(&store->size)) & ((*(&store->size)) - 1)))
    {
      store->pos = (store->size == 0) ? (malloc(sizeof(*(*(&store->pos))))) : (realloc(*(&store->pos), (store->size * 2) * (sizeof(*(*(&store->pos))))));
    }
    store->pos[store->size] = pos;
    store->size += 1;
  }
  ;
  assert(length < 259);
  if (dist == 0)
  {
    store->size = origsize;
    {
      if (!((*(&store->size)) & ((*(&store->size)) - 1)))
      {
        store->ll_symbol = (store->size == 0) ? (malloc(sizeof(*(*(&store->ll_symbol))))) : (realloc(*(&store->ll_symbol), (store->size * 2) * (sizeof(*(*(&store->ll_symbol))))));
      }
      store->ll_symbol[store->size] = length;
      store->size += 1;
    }
    ;
    store->size = origsize;
    {
      if (!((*(&store->size)) & ((*(&store->size)) - 1)))
      {
        store->d_symbol = (store->size == 0) ? (malloc(sizeof(*(*(&store->d_symbol))))) : (realloc(*(&store->d_symbol), (store->size * 2) * (sizeof(*(*(&store->d_symbol))))));
      }
      store->d_symbol[store->size] = 0;
      store->size += 1;
    }
    ;
    store->ll_counts[llstart + length] += 1;
  }
  else
  {
    helper_ZopfliStoreLitLenDist_1(&length, &dist, &llstart, &dstart, store, origsize);
  }
}


----------------------------
void ZopfliWarmupHash(const unsigned char *array, size_t pos, size_t end, ZopfliHash *h)
{
  UpdateHashValue(h, array[pos + 0]);
  if ((pos + 1) < end)
  {
    UpdateHashValue(h, array[pos + 1]);
  }
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
void ZopfliResetHash(size_t window_size, ZopfliHash *h)
{
  size_t i;
  h->val = 0;
  for (i = 0; i < 65536; i += 1)
  {
    h->head[i] = -1;
  }

  for (i = 0; i < window_size; i += 1)
  {
    h->prev[i] = i;
    h->hashval[i] = -1;
  }

  for (i = 0; i < window_size; i += 1)
  {
    h->same[i] = 0;
  }

  h->val2 = 0;
  for (i = 0; i < 65536; i += 1)
  {
    h->head2[i] = -1;
  }

  for (i = 0; i < window_size; i += 1)
  {
    h->prev2[i] = i;
    h->hashval2[i] = -1;
  }

}


----------------------------
void ZopfliVerifyLenDist(const unsigned char *data, size_t datasize, size_t pos, unsigned short dist, unsigned short length)
{
  size_t i;
  assert((pos + length) <= datasize);
  for (i = 0; i < length; i += 1)
  {
    if (data[(pos - dist) + i] != data[pos + i])
    {
      assert(data[(pos - dist) + i] == data[pos + i]);
      break;
    }
  }

}


----------------------------
void ZopfliFindLongestMatch(ZopfliBlockState *s, const ZopfliHash *h, const unsigned char *array, size_t pos, size_t size, size_t limit, unsigned short *sublen, unsigned short *distance, unsigned short *length)
{
  unsigned short hpos = pos & (32768 - 1);
  unsigned short p;
  unsigned short pp;
  unsigned short bestdist = 0;
  unsigned short bestlength = 1;
  const unsigned char *scan;
  unsigned int scan_idx = 0;
  const unsigned char *match;
  unsigned int match_idx = 0;
  const unsigned char *arrayend;
  unsigned int arrayend_idx = 0;
  const unsigned char *arrayend_safe;
  unsigned int arrayend_safe_idx = 0;
  int chain_counter = 8192;
  unsigned dist = 0;
  int *hhead = h->head;
  unsigned int hhead_idx = 0;
  unsigned short *hprev = h->prev;
  unsigned int hprev_idx = 0;
  int *hhashval = h->hashval;
  unsigned int hhashval_idx = 0;
  int hval = h->val;
  if (TryGetFromLongestMatchCache(s, pos, &limit, sublen, distance, length))
  {
    assert((pos + (*length)) <= size);
    return;
  }
  assert(limit <= 258);
  assert(limit >= 3);
  assert(pos < size);
  if ((size - pos) < 3)
  {
    *length = 0;
    *distance = 0;
    return;
  }
  if ((pos + limit) > size)
  {
    limit = size - pos;
  }
  arrayend_idx = (&array[pos]) + limit;
  arrayend_safe_idx = (&arrayend[arrayend_idx]) - 8;
  assert(hval < 65536);
  pp = hhead[hval + hhead_idx];
  p = hprev[pp + hprev_idx];
  assert(pp == hpos);
  dist = (p < pp) ? (pp - p) : ((32768 - p) + pp);
  while (dist < 32768)
  {
    helper_ZopfliFindLongestMatch_1(&p, &pp, &bestdist, &bestlength, &scan_idx, &match_idx, &chain_counter, &dist, &hhead_idx, &hprev_idx, &hhashval_idx, &hval, h, array, pos, size, limit, sublen, hpos, scan, match, arrayend, arrayend_safe, hhead, hprev, hhashval);
  }

  StoreInLongestMatchCache(s, pos, limit, sublen, bestdist, bestlength);
  assert(bestlength <= limit);
  *distance = bestdist;
  *length = bestlength;
  assert((pos + (*length)) <= size);
}


----------------------------
void ZopfliUpdateHash(const unsigned char *array, size_t pos, size_t end, ZopfliHash *h)
{
  unsigned short hpos = pos & (32768 - 1);
  size_t amount = 0;
  UpdateHashValue(h, ((pos + 3) <= end) ? (array[(pos + 3) - 1]) : (0));
  h->hashval[hpos] = h->val;
  if ((h->head[h->val] != (-1)) && (h->hashval[h->head[h->val]] == h->val))
  {
    h->prev[hpos] = h->head[h->val];
  }
  else
    h->prev[hpos] = hpos;
  h->head[h->val] = hpos;
  if (h->same[(pos - 1) & (32768 - 1)] > 1)
  {
    amount = h->same[(pos - 1) & (32768 - 1)] - 1;
  }
  while (((((pos + amount) + 1) < end) && (array[pos] == array[(pos + amount) + 1])) && (amount < ((unsigned short) (-1))))
  {
    amount += 1;
  }

  h->same[hpos] = amount;
  h->val2 = ((h->same[hpos] - 3) & 255) ^ h->val;
  h->hashval2[hpos] = h->val2;
  if ((h->head2[h->val2] != (-1)) && (h->hashval2[h->head2[h->val2]] == h->val2))
  {
    h->prev2[hpos] = h->head2[h->val2];
  }
  else
    h->prev2[hpos] = hpos;
  h->head2[h->val2] = hpos;
}


----------------------------
***/


// hint:  ['i_ref is a mutable refrence to size_t', 'k_ref is a mutable refrence to size_t', 'kend_ref is a mutable refrence to size_t', 'mincostaddcostj_ref is a mutable refrence to double']
void helper_GetBestLengths_1(size_t * const i_ref, size_t * const k_ref, size_t * const kend_ref, double * const mincostaddcostj_ref, ZopfliBlockState * const s, const unsigned char * const in, size_t instart, size_t inend, void * const costcontext, unsigned short * const length_array, ZopfliHash * const h, float * const costs, unsigned short leng, unsigned short dist, unsigned short sublen[259], double mincost)
{
  size_t i = *i_ref;
  size_t k = *k_ref;
  size_t kend = *kend_ref;
  double mincostaddcostj = *mincostaddcostj_ref;
  size_t j = i - instart;
  ZopfliUpdateHash(in, i, inend, h);
  if ((((h->same[i & (32768 - 1)] > (258 * 2)) && (i > ((instart + 258) + 1))) && (((i + (258 * 2)) + 1) < inend)) && (h->same[(i - 258) & (32768 - 1)] > 258))
  {
    double symbolcost = costmodel(258, 1, costcontext);
    for (k = 0; k < 258; k += 1)
    {
      costs[j + 258] = costs[j] + symbolcost;
      length_array[j + 258] = 258;
      i += 1;
      j += 1;
      ZopfliUpdateHash(in, i, inend, h);
    }

  }
  ZopfliFindLongestMatch(s, h, in, i, inend, 258, sublen, &dist, &leng);
  if ((i + 1) <= inend)
  {
    double newCost = costmodel(in[i], 0, costcontext) + costs[j];
    assert(newCost >= 0);
    if (newCost < costs[j + 1])
    {
      costs[j + 1] = newCost;
      length_array[j + 1] = 1;
    }
  }
  kend = zopfli_min(leng, inend - i);
  mincostaddcostj = mincost + costs[j];
  for (k = 3; k <= kend; k += 1)
  {
    double newCost;
    if (costs[j + k] <= mincostaddcostj)
    {
      continue;
    }
    newCost = costmodel(k, sublen[k], costcontext) + costs[j];
    assert(newCost >= 0);
    if (newCost < costs[j + k])
    {
      assert(k <= 258);
      costs[j + k] = newCost;
      length_array[j + k] = k;
    }
  }

  *i_ref = i;
  *k_ref = k;
  *kend_ref = kend;
  *mincostaddcostj_ref = mincostaddcostj;
}


/*** DEPENDENCIES:
typedef struct ZopfliHash
{
  int *head;
  unsigned short *prev;
  int *hashval;
  int val;
  int *head2;
  unsigned short *prev2;
  int *hashval2;
  int val2;
  unsigned short *same;
} ZopfliHash
----------------------------
typedef struct ZopfliBlockState
{
  const ZopfliOptions *options;
  ZopfliLongestMatchCache *lmc;
  size_t blockstart;
  size_t blockend;
} ZopfliBlockState
----------------------------
void ZopfliFindLongestMatch(ZopfliBlockState *s, const ZopfliHash *h, const unsigned char *array, size_t pos, size_t size, size_t limit, unsigned short *sublen, unsigned short *distance, unsigned short *length)
{
  unsigned short hpos = pos & (32768 - 1);
  unsigned short p;
  unsigned short pp;
  unsigned short bestdist = 0;
  unsigned short bestlength = 1;
  const unsigned char *scan;
  unsigned int scan_idx = 0;
  const unsigned char *match;
  unsigned int match_idx = 0;
  const unsigned char *arrayend;
  unsigned int arrayend_idx = 0;
  const unsigned char *arrayend_safe;
  unsigned int arrayend_safe_idx = 0;
  int chain_counter = 8192;
  unsigned dist = 0;
  int *hhead = h->head;
  unsigned int hhead_idx = 0;
  unsigned short *hprev = h->prev;
  unsigned int hprev_idx = 0;
  int *hhashval = h->hashval;
  unsigned int hhashval_idx = 0;
  int hval = h->val;
  if (TryGetFromLongestMatchCache(s, pos, &limit, sublen, distance, length))
  {
    assert((pos + (*length)) <= size);
    return;
  }
  assert(limit <= 258);
  assert(limit >= 3);
  assert(pos < size);
  if ((size - pos) < 3)
  {
    *length = 0;
    *distance = 0;
    return;
  }
  if ((pos + limit) > size)
  {
    limit = size - pos;
  }
  arrayend_idx = (&array[pos]) + limit;
  arrayend_safe_idx = (&arrayend[arrayend_idx]) - 8;
  assert(hval < 65536);
  pp = hhead[hval + hhead_idx];
  p = hprev[pp + hprev_idx];
  assert(pp == hpos);
  dist = (p < pp) ? (pp - p) : ((32768 - p) + pp);
  while (dist < 32768)
  {
    helper_ZopfliFindLongestMatch_1(&p, &pp, &bestdist, &bestlength, &scan_idx, &match_idx, &chain_counter, &dist, &hhead_idx, &hprev_idx, &hhashval_idx, &hval, h, array, pos, size, limit, sublen, hpos, scan, match, arrayend, arrayend_safe, hhead, hprev, hhashval);
  }

  StoreInLongestMatchCache(s, pos, limit, sublen, bestdist, bestlength);
  assert(bestlength <= limit);
  *distance = bestdist;
  *length = bestlength;
  assert((pos + (*length)) <= size);
}


----------------------------
void ZopfliUpdateHash(const unsigned char *array, size_t pos, size_t end, ZopfliHash *h)
{
  unsigned short hpos = pos & (32768 - 1);
  size_t amount = 0;
  UpdateHashValue(h, ((pos + 3) <= end) ? (array[(pos + 3) - 1]) : (0));
  h->hashval[hpos] = h->val;
  if ((h->head[h->val] != (-1)) && (h->hashval[h->head[h->val]] == h->val))
  {
    h->prev[hpos] = h->head[h->val];
  }
  else
    h->prev[hpos] = hpos;
  h->head[h->val] = hpos;
  if (h->same[(pos - 1) & (32768 - 1)] > 1)
  {
    amount = h->same[(pos - 1) & (32768 - 1)] - 1;
  }
  while (((((pos + amount) + 1) < end) && (array[pos] == array[(pos + amount) + 1])) && (amount < ((unsigned short) (-1))))
  {
    amount += 1;
  }

  h->same[hpos] = amount;
  h->val2 = ((h->same[hpos] - 3) & 255) ^ h->val;
  h->hashval2[hpos] = h->val2;
  if ((h->head2[h->val2] != (-1)) && (h->hashval2[h->head2[h->val2]] == h->val2))
  {
    h->prev2[hpos] = h->head2[h->val2];
  }
  else
    h->prev2[hpos] = hpos;
  h->head2[h->val2] = hpos;
}


----------------------------
static size_t zopfli_min(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}


----------------------------
***/


static double GetBestLengths(ZopfliBlockState *s, const unsigned char *in, size_t instart, size_t inend, CostModelFun *costmodel, void *costcontext, unsigned short *length_array, ZopfliHash *h, float *costs)
{
  size_t blocksize = inend - instart;
  size_t i = 0;
  size_t k;
  size_t kend;
  unsigned short leng;
  unsigned short dist;
  unsigned short sublen[259];
  size_t windowstart = (instart > 32768) ? (instart - 32768) : (0);
  double result;
  double mincost = GetCostModelMinCost(costmodel, costcontext);
  double mincostaddcostj;
  if (instart == inend)
  {
    return 0;
  }
  ZopfliResetHash(32768, h);
  ZopfliWarmupHash(in, windowstart, inend, h);
  for (i = windowstart; i < instart; i += 1)
  {
    ZopfliUpdateHash(in, i, inend, h);
  }

  for (i = 1; i < (blocksize + 1); i += 1)
    costs[i] = 1e30;

  costs[0] = 0;
  length_array[0] = 0;
  for (i = instart; i < inend; i += 1)
  {
    helper_GetBestLengths_1(&i, &k, &kend, &mincostaddcostj, s, in, instart, inend, costcontext, length_array, h, costs, leng, dist, sublen, mincost);
  }

  assert(costs[blocksize] >= 0);
  result = costs[blocksize];
  return result;
}


/*** DEPENDENCIES:
typedef struct ZopfliHash
{
  int *head;
  unsigned short *prev;
  int *hashval;
  int val;
  int *head2;
  unsigned short *prev2;
  int *hashval2;
  int val2;
  unsigned short *same;
} ZopfliHash
----------------------------
void ZopfliWarmupHash(const unsigned char *array, size_t pos, size_t end, ZopfliHash *h)
{
  UpdateHashValue(h, array[pos + 0]);
  if ((pos + 1) < end)
  {
    UpdateHashValue(h, array[pos + 1]);
  }
}


----------------------------
static double GetCostModelMinCost(CostModelFun *costmodel, void *costcontext)
{
  double mincost;
  int bestlength = 0;
  int bestdist = 0;
  int i;
  static const int dsymbols[30] = {1, 2, 3, 4, 5, 7, 9, 13, 17, 25, 33, 49, 65, 97, 129, 193, 257, 385, 513, 769, 1025, 1537, 2049, 3073, 4097, 6145, 8193, 12289, 16385, 24577};
  mincost = 1e30;
  for (i = 3; i < 259; i += 1)
  {
    double c = costmodel(i, 1, costcontext);
    if (c < mincost)
    {
      bestlength = i;
      mincost = c;
    }
  }

  mincost = 1e30;
  for (i = 0; i < 30; i += 1)
  {
    double c = costmodel(3, dsymbols[i], costcontext);
    if (c < mincost)
    {
      bestdist = dsymbols[i];
      mincost = c;
    }
  }

  return costmodel(bestlength, bestdist, costcontext);
}


----------------------------
typedef double CostModelFun(unsigned litlen, unsigned dist, void *context)
----------------------------
typedef struct ZopfliBlockState
{
  const ZopfliOptions *options;
  ZopfliLongestMatchCache *lmc;
  size_t blockstart;
  size_t blockend;
} ZopfliBlockState
----------------------------
void ZopfliResetHash(size_t window_size, ZopfliHash *h)
{
  size_t i;
  h->val = 0;
  for (i = 0; i < 65536; i += 1)
  {
    h->head[i] = -1;
  }

  for (i = 0; i < window_size; i += 1)
  {
    h->prev[i] = i;
    h->hashval[i] = -1;
  }

  for (i = 0; i < window_size; i += 1)
  {
    h->same[i] = 0;
  }

  h->val2 = 0;
  for (i = 0; i < 65536; i += 1)
  {
    h->head2[i] = -1;
  }

  for (i = 0; i < window_size; i += 1)
  {
    h->prev2[i] = i;
    h->hashval2[i] = -1;
  }

}


----------------------------
void helper_GetBestLengths_1(size_t * const i_ref, size_t * const k_ref, size_t * const kend_ref, double * const mincostaddcostj_ref, ZopfliBlockState * const s, const unsigned char * const in, size_t instart, size_t inend, void * const costcontext, unsigned short * const length_array, ZopfliHash * const h, float * const costs, unsigned short leng, unsigned short dist, unsigned short sublen[259], double mincost)
{
  size_t i = *i_ref;
  size_t k = *k_ref;
  size_t kend = *kend_ref;
  double mincostaddcostj = *mincostaddcostj_ref;
  size_t j = i - instart;
  ZopfliUpdateHash(in, i, inend, h);
  if ((((h->same[i & (32768 - 1)] > (258 * 2)) && (i > ((instart + 258) + 1))) && (((i + (258 * 2)) + 1) < inend)) && (h->same[(i - 258) & (32768 - 1)] > 258))
  {
    double symbolcost = costmodel(258, 1, costcontext);
    for (k = 0; k < 258; k += 1)
    {
      costs[j + 258] = costs[j] + symbolcost;
      length_array[j + 258] = 258;
      i += 1;
      j += 1;
      ZopfliUpdateHash(in, i, inend, h);
    }

  }
  ZopfliFindLongestMatch(s, h, in, i, inend, 258, sublen, &dist, &leng);
  if ((i + 1) <= inend)
  {
    double newCost = costmodel(in[i], 0, costcontext) + costs[j];
    assert(newCost >= 0);
    if (newCost < costs[j + 1])
    {
      costs[j + 1] = newCost;
      length_array[j + 1] = 1;
    }
  }
  kend = zopfli_min(leng, inend - i);
  mincostaddcostj = mincost + costs[j];
  for (k = 3; k <= kend; k += 1)
  {
    double newCost;
    if (costs[j + k] <= mincostaddcostj)
    {
      continue;
    }
    newCost = costmodel(k, sublen[k], costcontext) + costs[j];
    assert(newCost >= 0);
    if (newCost < costs[j + k])
    {
      assert(k <= 258);
      costs[j + k] = newCost;
      length_array[j + k] = k;
    }
  }

  *i_ref = i;
  *k_ref = k;
  *kend_ref = kend;
  *mincostaddcostj_ref = mincostaddcostj;
}


----------------------------
void ZopfliUpdateHash(const unsigned char *array, size_t pos, size_t end, ZopfliHash *h)
{
  unsigned short hpos = pos & (32768 - 1);
  size_t amount = 0;
  UpdateHashValue(h, ((pos + 3) <= end) ? (array[(pos + 3) - 1]) : (0));
  h->hashval[hpos] = h->val;
  if ((h->head[h->val] != (-1)) && (h->hashval[h->head[h->val]] == h->val))
  {
    h->prev[hpos] = h->head[h->val];
  }
  else
    h->prev[hpos] = hpos;
  h->head[h->val] = hpos;
  if (h->same[(pos - 1) & (32768 - 1)] > 1)
  {
    amount = h->same[(pos - 1) & (32768 - 1)] - 1;
  }
  while (((((pos + amount) + 1) < end) && (array[pos] == array[(pos + amount) + 1])) && (amount < ((unsigned short) (-1))))
  {
    amount += 1;
  }

  h->same[hpos] = amount;
  h->val2 = ((h->same[hpos] - 3) & 255) ^ h->val;
  h->hashval2[hpos] = h->val2;
  if ((h->head2[h->val2] != (-1)) && (h->hashval2[h->head2[h->val2]] == h->val2))
  {
    h->prev2[hpos] = h->head2[h->val2];
  }
  else
    h->prev2[hpos] = hpos;
  h->head2[h->val2] = hpos;
}


----------------------------
***/


static double LZ77OptimalRun(ZopfliBlockState *s, const unsigned char *in, size_t instart, size_t inend, unsigned short **path, size_t *pathsize, unsigned short *length_array, CostModelFun *costmodel, void *costcontext, ZopfliLZ77Store *store, ZopfliHash *h, float *costs)
{
  double cost = GetBestLengths(s, in, instart, inend, costmodel, costcontext, length_array, h, costs);
  free(*path);
  *path = 0;
  *pathsize = 0;
  TraceBackwards(inend - instart, length_array, path, pathsize);
  FollowPath(s, in, instart, inend, *path, *pathsize, store, h);
  assert(cost < 1e30);
  return cost;
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
typedef struct ZopfliHash
{
  int *head;
  unsigned short *prev;
  int *hashval;
  int val;
  int *head2;
  unsigned short *prev2;
  int *hashval2;
  int val2;
  unsigned short *same;
} ZopfliHash
----------------------------
static void FollowPath(ZopfliBlockState *s, const unsigned char *in, size_t instart, size_t inend, unsigned short *path, size_t pathsize, ZopfliLZ77Store *store, ZopfliHash *h)
{
  size_t i;
  size_t j;
  size_t pos = 0;
  size_t windowstart = (instart > 32768) ? (instart - 32768) : (0);
  size_t total_length_test = 0;
  if (instart == inend)
  {
    return;
  }
  ZopfliResetHash(32768, h);
  ZopfliWarmupHash(in, windowstart, inend, h);
  for (i = windowstart; i < instart; i += 1)
  {
    ZopfliUpdateHash(in, i, inend, h);
  }

  pos = instart;
  for (i = 0; i < pathsize; i += 1)
  {
    unsigned short length = path[i];
    unsigned short dummy_length;
    unsigned short dist;
    assert(pos < inend);
    ZopfliUpdateHash(in, pos, inend, h);
    if (length >= 3)
    {
      ZopfliFindLongestMatch(s, h, in, pos, inend, length, 0, &dist, &dummy_length);
      assert(!(((dummy_length != length) && (length > 2)) && (dummy_length > 2)));
      ZopfliVerifyLenDist(in, inend, pos, dist, length);
      ZopfliStoreLitLenDist(length, dist, pos, store);
      total_length_test += length;
    }
    else
    {
      length = 1;
      ZopfliStoreLitLenDist(in[pos], 0, pos, store);
      total_length_test += 1;
    }
    assert((pos + length) <= inend);
    for (j = 1; j < length; j += 1)
    {
      ZopfliUpdateHash(in, pos + j, inend, h);
    }

    pos += length;
  }

}


----------------------------
typedef double CostModelFun(unsigned litlen, unsigned dist, void *context)
----------------------------
static void TraceBackwards(size_t size, const unsigned short *length_array, unsigned short **path, size_t *pathsize)
{
  size_t index = size;
  if (size == 0)
  {
    return;
  }
  for (;;)
  {
    {
      if (!((*pathsize) & ((*pathsize) - 1)))
      {
        *path = ((*pathsize) == 0) ? (malloc(sizeof(*(*path)))) : (realloc(*path, ((*pathsize) * 2) * (sizeof(*(*path)))));
      }
      (*path)[*pathsize] = length_array[index];
      *pathsize += 1;
    }
    ;
    assert(length_array[index] <= index);
    assert(length_array[index] <= 258);
    assert(length_array[index] != 0);
    index -= length_array[index];
    if (index == 0)
    {
      break;
    }
  }

  for (index = 0; index < ((*pathsize) / 2); index += 1)
  {
    unsigned short temp = (*path)[index];
    (*path)[index] = (*path)[((*pathsize) - index) - 1];
    (*path)[((*pathsize) - index) - 1] = temp;
  }

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
static double GetBestLengths(ZopfliBlockState *s, const unsigned char *in, size_t instart, size_t inend, CostModelFun *costmodel, void *costcontext, unsigned short *length_array, ZopfliHash *h, float *costs)
{
  size_t blocksize = inend - instart;
  size_t i = 0;
  size_t k;
  size_t kend;
  unsigned short leng;
  unsigned short dist;
  unsigned short sublen[259];
  size_t windowstart = (instart > 32768) ? (instart - 32768) : (0);
  double result;
  double mincost = GetCostModelMinCost(costmodel, costcontext);
  double mincostaddcostj;
  if (instart == inend)
  {
    return 0;
  }
  ZopfliResetHash(32768, h);
  ZopfliWarmupHash(in, windowstart, inend, h);
  for (i = windowstart; i < instart; i += 1)
  {
    ZopfliUpdateHash(in, i, inend, h);
  }

  for (i = 1; i < (blocksize + 1); i += 1)
    costs[i] = 1e30;

  costs[0] = 0;
  length_array[0] = 0;
  for (i = instart; i < inend; i += 1)
  {
    helper_GetBestLengths_1(&i, &k, &kend, &mincostaddcostj, s, in, instart, inend, costcontext, length_array, h, costs, leng, dist, sublen, mincost);
  }

  assert(costs[blocksize] >= 0);
  result = costs[blocksize];
  return result;
}


----------------------------
***/


static double GetCostFixed(unsigned litlen, unsigned dist, void *unused)
{
  (void) unused;
  if (dist == 0)
  {
    if (litlen <= 143)
    {
      return 8;
    }
    else
      return 9;
  }
  else
  {
    int dbits = ZopfliGetDistExtraBits(dist);
    int lbits = ZopfliGetLengthExtraBits(litlen);
    int lsym = ZopfliGetLengthSymbol(litlen);
    int cost = 0;
    if (lsym <= 279)
    {
      cost += 7;
    }
    else
      cost += 8;
    cost += 5;
    return (cost + dbits) + lbits;
  }
}


/*** DEPENDENCIES:
static int ZopfliGetDistExtraBits(int dist)
{
  if (dist < 5)
  {
    return 0;
  }
  return (31 ^ __builtin_clz(dist - 1)) - 1;
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
***/


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
typedef struct ZopfliHash
{
  int *head;
  unsigned short *prev;
  int *hashval;
  int val;
  int *head2;
  unsigned short *prev2;
  int *hashval2;
  int val2;
  unsigned short *same;
} ZopfliHash
----------------------------
typedef struct ZopfliBlockState
{
  const ZopfliOptions *options;
  ZopfliLongestMatchCache *lmc;
  size_t blockstart;
  size_t blockend;
} ZopfliBlockState
----------------------------
void ZopfliAllocHash(size_t window_size, ZopfliHash *h)
{
  h->head = (int *) malloc((sizeof(*h->head)) * 65536);
  h->prev = (unsigned short *) malloc((sizeof(*h->prev)) * window_size);
  h->hashval = (int *) malloc((sizeof(*h->hashval)) * window_size);
  h->same = (unsigned short *) malloc((sizeof(*h->same)) * window_size);
  h->head2 = (int *) malloc((sizeof(*h->head2)) * 65536);
  h->prev2 = (unsigned short *) malloc((sizeof(*h->prev2)) * window_size);
  h->hashval2 = (int *) malloc((sizeof(*h->hashval2)) * window_size);
}


----------------------------
static double LZ77OptimalRun(ZopfliBlockState *s, const unsigned char *in, size_t instart, size_t inend, unsigned short **path, size_t *pathsize, unsigned short *length_array, CostModelFun *costmodel, void *costcontext, ZopfliLZ77Store *store, ZopfliHash *h, float *costs)
{
  double cost = GetBestLengths(s, in, instart, inend, costmodel, costcontext, length_array, h, costs);
  free(*path);
  *path = 0;
  *pathsize = 0;
  TraceBackwards(inend - instart, length_array, path, pathsize);
  FollowPath(s, in, instart, inend, *path, *pathsize, store, h);
  assert(cost < 1e30);
  return cost;
}


----------------------------
void ZopfliCleanHash(ZopfliHash *h)
{
  free(h->head);
  free(h->prev);
  free(h->hashval);
  free(h->head2);
  free(h->prev2);
  free(h->hashval2);
  free(h->same);
}


----------------------------
static double GetCostFixed(unsigned litlen, unsigned dist, void *unused)
{
  (void) unused;
  if (dist == 0)
  {
    if (litlen <= 143)
    {
      return 8;
    }
    else
      return 9;
  }
  else
  {
    int dbits = ZopfliGetDistExtraBits(dist);
    int lbits = ZopfliGetLengthExtraBits(litlen);
    int lsym = ZopfliGetLengthSymbol(litlen);
    int cost = 0;
    if (lsym <= 279)
    {
      cost += 7;
    }
    else
      cost += 8;
    cost += 5;
    return (cost + dbits) + lbits;
  }
}


----------------------------
***/


static void CalculateStatistics(SymbolStats *stats)
{
  ZopfliCalculateEntropy(stats->litlens, 288, stats->ll_symbols);
  ZopfliCalculateEntropy(stats->dists, 32, stats->d_symbols);
}


/*** DEPENDENCIES:
void ZopfliCalculateEntropy(const size_t *count, size_t n, double *bitlengths)
{
  static const double kInvLog2 = 1.4426950408889;
  unsigned sum = 0;
  unsigned i;
  double log2sum;
  for (i = 0; i < n; i += 1)
  {
    sum += count[i];
  }

  log2sum = ((sum == 0) ? (log(n)) : (log(sum))) * kInvLog2;
  for (i = 0; i < n; i += 1)
  {
    if (count[i] == 0)
    {
      bitlengths[i] = log2sum;
    }
    else
      bitlengths[i] = log2sum - (log(count[i]) * kInvLog2);
    if ((bitlengths[i] < 0) && (bitlengths[i] > (-1e-5)))
    {
      bitlengths[i] = 0;
    }
    assert(bitlengths[i] >= 0);
  }

}


----------------------------
typedef struct SymbolStats
{
  size_t litlens[288];
  size_t dists[32];
  double ll_symbols[288];
  double d_symbols[32];
} SymbolStats
----------------------------
***/


static void GetStatistics(const ZopfliLZ77Store *store, SymbolStats *stats)
{
  size_t i;
  for (i = 0; i < store->size; i += 1)
  {
    if (store->dists[i] == 0)
    {
      stats->litlens[store->litlens[i]] += 1;
    }
    else
    {
      stats->litlens[ZopfliGetLengthSymbol(store->litlens[i])] += 1;
      stats->dists[ZopfliGetDistSymbol(store->dists[i])] += 1;
    }
  }

  stats->litlens[256] = 1;
  CalculateStatistics(stats);
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
static int ZopfliGetLengthSymbol(int l)
{
  static const int table[259] = {0, 0, 0, 257, 258, 259, 260, 261, 262, 263, 264, 265, 265, 266, 266, 267, 267, 268, 268, 269, 269, 269, 269, 270, 270, 270, 270, 271, 271, 271, 271, 272, 272, 272, 272, 273, 273, 273, 273, 273, 273, 273, 273, 274, 274, 274, 274, 274, 274, 274, 274, 275, 275, 275, 275, 275, 275, 275, 275, 276, 276, 276, 276, 276, 276, 276, 276, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 285};
  return table[l];
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
static void CalculateStatistics(SymbolStats *stats)
{
  ZopfliCalculateEntropy(stats->litlens, 288, stats->ll_symbols);
  ZopfliCalculateEntropy(stats->dists, 32, stats->d_symbols);
}


----------------------------
typedef struct SymbolStats
{
  size_t litlens[288];
  size_t dists[32];
  double ll_symbols[288];
  double d_symbols[32];
} SymbolStats
----------------------------
***/


static void RandomizeFreqs(RanState *state, size_t *freqs, int n)
{
  int i;
  for (i = 0; i < n; i += 1)
  {
    if (((Ran(state) >> 4) % 3) == 0)
    {
      freqs[i] = freqs[Ran(state) % n];
    }
  }

}


/*** DEPENDENCIES:
static unsigned int Ran(RanState *state)
{
  state->m_z = (36969 * (state->m_z & 65535)) + (state->m_z >> 16);
  state->m_w = (18000 * (state->m_w & 65535)) + (state->m_w >> 16);
  return (state->m_z << 16) + state->m_w;
}


----------------------------
typedef struct RanState
{
  unsigned int m_w;
  unsigned int m_z;
} RanState
----------------------------
***/


static void RandomizeStatFreqs(RanState *state, SymbolStats *stats)
{
  RandomizeFreqs(state, stats->litlens, 288);
  RandomizeFreqs(state, stats->dists, 32);
  stats->litlens[256] = 1;
}


/*** DEPENDENCIES:
typedef struct SymbolStats
{
  size_t litlens[288];
  size_t dists[32];
  double ll_symbols[288];
  double d_symbols[32];
} SymbolStats
----------------------------
typedef struct RanState
{
  unsigned int m_w;
  unsigned int m_z;
} RanState
----------------------------
static void RandomizeFreqs(RanState *state, size_t *freqs, int n)
{
  int i;
  for (i = 0; i < n; i += 1)
  {
    if (((Ran(state) >> 4) % 3) == 0)
    {
      freqs[i] = freqs[Ran(state) % n];
    }
  }

}


----------------------------
***/


static double GetCostStat(unsigned litlen, unsigned dist, void *context)
{
  SymbolStats *stats = (SymbolStats *) context;
  if (dist == 0)
  {
    return stats->ll_symbols[litlen];
  }
  else
  {
    int lsym = ZopfliGetLengthSymbol(litlen);
    int lbits = ZopfliGetLengthExtraBits(litlen);
    int dsym = ZopfliGetDistSymbol(dist);
    int dbits = ZopfliGetDistExtraBits(dist);
    return ((lbits + dbits) + stats->ll_symbols[lsym]) + stats->d_symbols[dsym];
  }
}


/*** DEPENDENCIES:
static int ZopfliGetDistExtraBits(int dist)
{
  if (dist < 5)
  {
    return 0;
  }
  return (31 ^ __builtin_clz(dist - 1)) - 1;
}


----------------------------
static int ZopfliGetLengthSymbol(int l)
{
  static const int table[259] = {0, 0, 0, 257, 258, 259, 260, 261, 262, 263, 264, 265, 265, 266, 266, 267, 267, 268, 268, 269, 269, 269, 269, 270, 270, 270, 270, 271, 271, 271, 271, 272, 272, 272, 272, 273, 273, 273, 273, 273, 273, 273, 273, 274, 274, 274, 274, 274, 274, 274, 274, 275, 275, 275, 275, 275, 275, 275, 275, 276, 276, 276, 276, 276, 276, 276, 276, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 285};
  return table[l];
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
static int ZopfliGetLengthExtraBits(int l)
{
  static const int table[259] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0};
  return table[l];
}


----------------------------
typedef struct SymbolStats
{
  size_t litlens[288];
  size_t dists[32];
  double ll_symbols[288];
  double d_symbols[32];
} SymbolStats
----------------------------
***/


// hint:  ['cost_ref is a mutable refrence to double', 'bestcost_ref is a mutable refrence to double', 'lastcost_ref is a mutable refrence to double', 'lastrandomstep_ref is a mutable refrence to int']
void helper_ZopfliLZ77Optimal_1(double * const cost_ref, double * const bestcost_ref, double * const lastcost_ref, int * const lastrandomstep_ref, ZopfliBlockState * const s, const unsigned char * const in, size_t instart, size_t inend, ZopfliLZ77Store * const store, unsigned short * const length_array, unsigned short * const path, size_t pathsize, ZopfliLZ77Store currentstore, ZopfliHash * const h, SymbolStats stats, SymbolStats beststats, SymbolStats laststats, int i, float * const costs, RanState ran_state)
{
  double cost = *cost_ref;
  double bestcost = *bestcost_ref;
  double lastcost = *lastcost_ref;
  int lastrandomstep = *lastrandomstep_ref;
  ZopfliCleanLZ77Store(&currentstore);
  ZopfliInitLZ77Store(in, &currentstore);
  LZ77OptimalRun(s, in, instart, inend, &path, &pathsize, length_array, GetCostStat, (void *) (&stats), &currentstore, h, costs);
  cost = ZopfliCalculateBlockSize(&currentstore, 0, currentstore.size, 2);
  if (s->options->verbose_more || (s->options->verbose && (cost < bestcost)))
  {
    fprintf(stderr, "Iteration %d: %d bit\n", i, (int) cost);
  }
  if (cost < bestcost)
  {
    ZopfliCopyLZ77Store(&currentstore, store);
    CopyStats(&stats, &beststats);
    bestcost = cost;
  }
  CopyStats(&stats, &laststats);
  ClearStatFreqs(&stats);
  GetStatistics(&currentstore, &stats);
  if (lastrandomstep != (-1))
  {
    AddWeighedStatFreqs(&stats, 1.0, &laststats, 0.5, &stats);
    CalculateStatistics(&stats);
  }
  if ((i > 5) && (cost == lastcost))
  {
    CopyStats(&beststats, &stats);
    RandomizeStatFreqs(&ran_state, &stats);
    CalculateStatistics(&stats);
    lastrandomstep = i;
  }
  lastcost = cost;
  *cost_ref = cost;
  *bestcost_ref = bestcost;
  *lastcost_ref = lastcost;
  *lastrandomstep_ref = lastrandomstep;
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
static void GetStatistics(const ZopfliLZ77Store *store, SymbolStats *stats)
{
  size_t i;
  for (i = 0; i < store->size; i += 1)
  {
    if (store->dists[i] == 0)
    {
      stats->litlens[store->litlens[i]] += 1;
    }
    else
    {
      stats->litlens[ZopfliGetLengthSymbol(store->litlens[i])] += 1;
      stats->dists[ZopfliGetDistSymbol(store->dists[i])] += 1;
    }
  }

  stats->litlens[256] = 1;
  CalculateStatistics(stats);
}


----------------------------
typedef struct ZopfliHash
{
  int *head;
  unsigned short *prev;
  int *hashval;
  int val;
  int *head2;
  unsigned short *prev2;
  int *hashval2;
  int val2;
  unsigned short *same;
} ZopfliHash
----------------------------
static void RandomizeStatFreqs(RanState *state, SymbolStats *stats)
{
  RandomizeFreqs(state, stats->litlens, 288);
  RandomizeFreqs(state, stats->dists, 32);
  stats->litlens[256] = 1;
}


----------------------------
static double GetCostStat(unsigned litlen, unsigned dist, void *context)
{
  SymbolStats *stats = (SymbolStats *) context;
  if (dist == 0)
  {
    return stats->ll_symbols[litlen];
  }
  else
  {
    int lsym = ZopfliGetLengthSymbol(litlen);
    int lbits = ZopfliGetLengthExtraBits(litlen);
    int dsym = ZopfliGetDistSymbol(dist);
    int dbits = ZopfliGetDistExtraBits(dist);
    return ((lbits + dbits) + stats->ll_symbols[lsym]) + stats->d_symbols[dsym];
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
void ZopfliCopyLZ77Store(const ZopfliLZ77Store *source, ZopfliLZ77Store *dest)
{
  size_t i;
  size_t llsize = 288 * CeilDiv(source->size, 288);
  size_t dsize = 32 * CeilDiv(source->size, 32);
  ZopfliCleanLZ77Store(dest);
  ZopfliInitLZ77Store(source->data, dest);
  dest->litlens = (unsigned short *) malloc((sizeof(*dest->litlens)) * source->size);
  dest->dists = (unsigned short *) malloc((sizeof(*dest->dists)) * source->size);
  dest->pos = (size_t *) malloc((sizeof(*dest->pos)) * source->size);
  dest->ll_symbol = (unsigned short *) malloc((sizeof(*dest->ll_symbol)) * source->size);
  dest->d_symbol = (unsigned short *) malloc((sizeof(*dest->d_symbol)) * source->size);
  dest->ll_counts = (size_t *) malloc((sizeof(*dest->ll_counts)) * llsize);
  dest->d_counts = (size_t *) malloc((sizeof(*dest->d_counts)) * dsize);
  if ((!dest->litlens) || (!dest->dists))
  {
    exit(-1);
  }
  if (!dest->pos)
  {
    exit(-1);
  }
  if ((!dest->ll_symbol) || (!dest->d_symbol))
  {
    exit(-1);
  }
  if ((!dest->ll_counts) || (!dest->d_counts))
  {
    exit(-1);
  }
  dest->size = source->size;
  for (i = 0; i < source->size; i += 1)
  {
    dest->litlens[i] = source->litlens[i];
    dest->dists[i] = source->dists[i];
    dest->pos[i] = source->pos[i];
    dest->ll_symbol[i] = source->ll_symbol[i];
    dest->d_symbol[i] = source->d_symbol[i];
  }

  for (i = 0; i < llsize; i += 1)
  {
    dest->ll_counts[i] = source->ll_counts[i];
  }

  for (i = 0; i < dsize; i += 1)
  {
    dest->d_counts[i] = source->d_counts[i];
  }

}


----------------------------
typedef struct RanState
{
  unsigned int m_w;
  unsigned int m_z;
} RanState
----------------------------
static void CalculateStatistics(SymbolStats *stats)
{
  ZopfliCalculateEntropy(stats->litlens, 288, stats->ll_symbols);
  ZopfliCalculateEntropy(stats->dists, 32, stats->d_symbols);
}


----------------------------
static void AddWeighedStatFreqs(const SymbolStats *stats1, double w1, const SymbolStats *stats2, double w2, SymbolStats *result)
{
  size_t i;
  for (i = 0; i < 288; i += 1)
  {
    result->litlens[i] = (size_t) ((stats1->litlens[i] * w1) + (stats2->litlens[i] * w2));
  }

  for (i = 0; i < 32; i += 1)
  {
    result->dists[i] = (size_t) ((stats1->dists[i] * w1) + (stats2->dists[i] * w2));
  }

  result->litlens[256] = 1;
}


----------------------------
static void ClearStatFreqs(SymbolStats *stats)
{
  size_t i;
  for (i = 0; i < 288; i += 1)
    stats->litlens[i] = 0;

  for (i = 0; i < 32; i += 1)
    stats->dists[i] = 0;

}


----------------------------
static double LZ77OptimalRun(ZopfliBlockState *s, const unsigned char *in, size_t instart, size_t inend, unsigned short **path, size_t *pathsize, unsigned short *length_array, CostModelFun *costmodel, void *costcontext, ZopfliLZ77Store *store, ZopfliHash *h, float *costs)
{
  double cost = GetBestLengths(s, in, instart, inend, costmodel, costcontext, length_array, h, costs);
  free(*path);
  *path = 0;
  *pathsize = 0;
  TraceBackwards(inend - instart, length_array, path, pathsize);
  FollowPath(s, in, instart, inend, *path, *pathsize, store, h);
  assert(cost < 1e30);
  return cost;
}


----------------------------
typedef struct SymbolStats
{
  size_t litlens[288];
  size_t dists[32];
  double ll_symbols[288];
  double d_symbols[32];
} SymbolStats
----------------------------
static void CopyStats(SymbolStats *source, SymbolStats *dest)
{
  memcpy(dest->litlens, source->litlens, 288 * (sizeof(dest->litlens[0])));
  memcpy(dest->dists, source->dists, 32 * (sizeof(dest->dists[0])));
  memcpy(dest->ll_symbols, source->ll_symbols, 288 * (sizeof(dest->ll_symbols[0])));
  memcpy(dest->d_symbols, source->d_symbols, 32 * (sizeof(dest->d_symbols[0])));
}


----------------------------
***/


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
static void GetStatistics(const ZopfliLZ77Store *store, SymbolStats *stats)
{
  size_t i;
  for (i = 0; i < store->size; i += 1)
  {
    if (store->dists[i] == 0)
    {
      stats->litlens[store->litlens[i]] += 1;
    }
    else
    {
      stats->litlens[ZopfliGetLengthSymbol(store->litlens[i])] += 1;
      stats->dists[ZopfliGetDistSymbol(store->dists[i])] += 1;
    }
  }

  stats->litlens[256] = 1;
  CalculateStatistics(stats);
}


----------------------------
typedef struct ZopfliHash
{
  int *head;
  unsigned short *prev;
  int *hashval;
  int val;
  int *head2;
  unsigned short *prev2;
  int *hashval2;
  int val2;
  unsigned short *same;
} ZopfliHash
----------------------------
void ZopfliLZ77Greedy(ZopfliBlockState *s, const unsigned char *in, size_t instart, size_t inend, ZopfliLZ77Store *store, ZopfliHash *h)
{
  size_t i = 0;
  size_t j;
  unsigned short leng;
  unsigned short dist;
  int lengthscore;
  size_t windowstart = (instart > 32768) ? (instart - 32768) : (0);
  unsigned short dummysublen[259];
  unsigned prev_length = 0;
  unsigned prev_match = 0;
  int prevlengthscore;
  int match_available = 0;
  if (instart == inend)
  {
    return;
  }
  ZopfliResetHash(32768, h);
  ZopfliWarmupHash(in, windowstart, inend, h);
  for (i = windowstart; i < instart; i += 1)
  {
    ZopfliUpdateHash(in, i, inend, h);
  }

  for (i = instart; i < inend; i += 1)
  {
    helper_ZopfliLZ77Greedy_1(&i, &j, &leng, &dist, &lengthscore, &prev_length, &prev_match, &prevlengthscore, &match_available, s, in, inend, store, h, dummysublen);
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
static void InitRanState(RanState *state)
{
  state->m_w = 1;
  state->m_z = 2;
}


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
typedef struct RanState
{
  unsigned int m_w;
  unsigned int m_z;
} RanState
----------------------------
void ZopfliAllocHash(size_t window_size, ZopfliHash *h)
{
  h->head = (int *) malloc((sizeof(*h->head)) * 65536);
  h->prev = (unsigned short *) malloc((sizeof(*h->prev)) * window_size);
  h->hashval = (int *) malloc((sizeof(*h->hashval)) * window_size);
  h->same = (unsigned short *) malloc((sizeof(*h->same)) * window_size);
  h->head2 = (int *) malloc((sizeof(*h->head2)) * 65536);
  h->prev2 = (unsigned short *) malloc((sizeof(*h->prev2)) * window_size);
  h->hashval2 = (int *) malloc((sizeof(*h->hashval2)) * window_size);
}


----------------------------
typedef struct SymbolStats
{
  size_t litlens[288];
  size_t dists[32];
  double ll_symbols[288];
  double d_symbols[32];
} SymbolStats
----------------------------
void ZopfliCleanHash(ZopfliHash *h)
{
  free(h->head);
  free(h->prev);
  free(h->hashval);
  free(h->head2);
  free(h->prev2);
  free(h->hashval2);
  free(h->same);
}


----------------------------
static void InitStats(SymbolStats *stats)
{
  memset(stats->litlens, 0, 288 * (sizeof(stats->litlens[0])));
  memset(stats->dists, 0, 32 * (sizeof(stats->dists[0])));
  memset(stats->ll_symbols, 0, 288 * (sizeof(stats->ll_symbols[0])));
  memset(stats->d_symbols, 0, 32 * (sizeof(stats->d_symbols[0])));
}


----------------------------
void helper_ZopfliLZ77Optimal_1(double * const cost_ref, double * const bestcost_ref, double * const lastcost_ref, int * const lastrandomstep_ref, ZopfliBlockState * const s, const unsigned char * const in, size_t instart, size_t inend, ZopfliLZ77Store * const store, unsigned short * const length_array, unsigned short * const path, size_t pathsize, ZopfliLZ77Store currentstore, ZopfliHash * const h, SymbolStats stats, SymbolStats beststats, SymbolStats laststats, int i, float * const costs, RanState ran_state)
{
  double cost = *cost_ref;
  double bestcost = *bestcost_ref;
  double lastcost = *lastcost_ref;
  int lastrandomstep = *lastrandomstep_ref;
  ZopfliCleanLZ77Store(&currentstore);
  ZopfliInitLZ77Store(in, &currentstore);
  LZ77OptimalRun(s, in, instart, inend, &path, &pathsize, length_array, GetCostStat, (void *) (&stats), &currentstore, h, costs);
  cost = ZopfliCalculateBlockSize(&currentstore, 0, currentstore.size, 2);
  if (s->options->verbose_more || (s->options->verbose && (cost < bestcost)))
  {
    fprintf(stderr, "Iteration %d: %d bit\n", i, (int) cost);
  }
  if (cost < bestcost)
  {
    ZopfliCopyLZ77Store(&currentstore, store);
    CopyStats(&stats, &beststats);
    bestcost = cost;
  }
  CopyStats(&stats, &laststats);
  ClearStatFreqs(&stats);
  GetStatistics(&currentstore, &stats);
  if (lastrandomstep != (-1))
  {
    AddWeighedStatFreqs(&stats, 1.0, &laststats, 0.5, &stats);
    CalculateStatistics(&stats);
  }
  if ((i > 5) && (cost == lastcost))
  {
    CopyStats(&beststats, &stats);
    RandomizeStatFreqs(&ran_state, &stats);
    CalculateStatistics(&stats);
    lastrandomstep = i;
  }
  lastcost = cost;
  *cost_ref = cost;
  *bestcost_ref = bestcost;
  *lastcost_ref = lastcost;
  *lastrandomstep_ref = lastrandomstep;
}


----------------------------
***/


