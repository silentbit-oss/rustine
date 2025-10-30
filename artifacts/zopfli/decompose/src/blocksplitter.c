void ZopfliBlockSplitSimple(const unsigned char *in, size_t instart, size_t inend, size_t blocksize, size_t **splitpoints, size_t *npoints)
{
  size_t i = instart;
  while (i < inend)
  {
    {
      if (!((*npoints) & ((*npoints) - 1)))
      {
        *splitpoints = ((*npoints) == 0) ? (malloc(sizeof(*(*splitpoints)))) : (realloc(*splitpoints, ((*npoints) * 2) * (sizeof(*(*splitpoints)))));
      }
      (*splitpoints)[*npoints] = i;
      *npoints += 1;
    }
    ;
    i += blocksize;
  }

  (void) in;
}


/*** DEPENDENCIES:
***/


static void AddSorted(size_t value, size_t **out, size_t *outsize)
{
  size_t i;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = value;
    *outsize += 1;
  }
  ;
  for (i = 0; (i + 1) < (*outsize); i += 1)
  {
    if ((*out)[i] > value)
    {
      size_t j;
      for (j = (*outsize) - 1; j > i; j -= 1)
      {
        (*out)[j] = (*out)[j - 1];
      }

      (*out)[i] = value;
      break;
    }
  }

}


/*** DEPENDENCIES:
***/


static int FindLargestSplittableBlock(size_t lz77size, const unsigned char *done, const size_t *splitpoints, size_t npoints, size_t *lstart, size_t *lend)
{
  size_t longest = 0;
  int found = 0;
  size_t i;
  for (i = 0; i <= npoints; i += 1)
  {
    size_t start = (i == 0) ? (0) : (splitpoints[i - 1]);
    size_t end = (i == npoints) ? (lz77size - 1) : (splitpoints[i]);
    if ((!done[start]) && ((end - start) > longest))
    {
      *lstart = start;
      *lend = end;
      found = 1;
      longest = end - start;
    }
  }

  return found;
}


/*** DEPENDENCIES:
***/


// hint:  ['start_ref is a mutable refrence to size_t', 'end_ref is a mutable refrence to size_t']
size_t helper_FindMinimum_1(size_t * const start_ref, size_t * const end_ref, void * const context, double * const smallest)
{
  size_t start = *start_ref;
  size_t end = *end_ref;
  size_t i;
  size_t p[9];
  double vp[9];
  size_t besti;
  double best;
  double lastbest = 1e30;
  size_t pos = start;
  for (;;)
  {
    if ((end - start) <= 9)
    {
      break;
    }
    for (i = 0; i < 9; i += 1)
    {
      p[i] = start + ((i + 1) * ((end - start) / (9 + 1)));
      vp[i] = f(p[i], context);
    }

    besti = 0;
    best = vp[0];
    for (i = 1; i < 9; i += 1)
    {
      if (vp[i] < best)
      {
        best = vp[i];
        besti = i;
      }
    }

    if (best > lastbest)
    {
      break;
    }
    start = (besti == 0) ? (start) : (p[besti - 1]);
    end = (besti == (9 - 1)) ? (end) : (p[besti + 1]);
    pos = p[besti];
    lastbest = best;
  }

  *smallest = lastbest;
  return pos;
  *start_ref = start;
  *end_ref = end;
}


/*** DEPENDENCIES:
pub f: _XImage_funcs
----------------------------
***/


static void PrintBlockSplitPoints(const ZopfliLZ77Store *lz77, const size_t *lz77splitpoints, size_t nlz77points)
{
  size_t *splitpoints = 0;
  size_t npoints = 0;
  size_t i;
  size_t pos = 0;
  if (nlz77points > 0)
  {
    for (i = 0; i < lz77->size; i += 1)
    {
      size_t length = (lz77->dists[i] == 0) ? (1) : (lz77->litlens[i]);
      if (lz77splitpoints[npoints] == i)
      {
        {
          if (!((*(&npoints)) & ((*(&npoints)) - 1)))
          {
            splitpoints = (npoints == 0) ? (malloc(sizeof(*(*(&splitpoints))))) : (realloc(*(&splitpoints), (npoints * 2) * (sizeof(*(*(&splitpoints))))));
          }
          splitpoints[npoints] = pos;
          npoints += 1;
        }
        ;
        if (npoints == nlz77points)
        {
          break;
        }
      }
      pos += length;
    }

  }
  assert(npoints == nlz77points);
  fprintf(stderr, "block split points: ");
  for (i = 0; i < npoints; i += 1)
  {
    fprintf(stderr, "%d ", (int) splitpoints[i]);
  }

  fprintf(stderr, "(hex:");
  for (i = 0; i < npoints; i += 1)
  {
    fprintf(stderr, " %x", (int) splitpoints[i]);
  }

  fprintf(stderr, ")\n");
  free(splitpoints);
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
***/


static size_t FindMinimum(FindMinimumFun f, void *context, size_t start, size_t end, double *smallest)
{
  if ((end - start) < 1024)
  {
    double best = 1e30;
    size_t result = start;
    size_t i;
    for (i = start; i < end; i += 1)
    {
      double v = f(i, context);
      if (v < best)
      {
        best = v;
        result = i;
      }
    }

    *smallest = best;
    return result;
  }
  else
  {
    helper_FindMinimum_1(&start, &end, context, smallest);
  }
}


/*** DEPENDENCIES:
size_t helper_FindMinimum_1(size_t * const start_ref, size_t * const end_ref, void * const context, double * const smallest)
{
  size_t start = *start_ref;
  size_t end = *end_ref;
  size_t i;
  size_t p[9];
  double vp[9];
  size_t besti;
  double best;
  double lastbest = 1e30;
  size_t pos = start;
  for (;;)
  {
    if ((end - start) <= 9)
    {
      break;
    }
    for (i = 0; i < 9; i += 1)
    {
      p[i] = start + ((i + 1) * ((end - start) / (9 + 1)));
      vp[i] = f(p[i], context);
    }

    besti = 0;
    best = vp[0];
    for (i = 1; i < 9; i += 1)
    {
      if (vp[i] < best)
      {
        best = vp[i];
        besti = i;
      }
    }

    if (best > lastbest)
    {
      break;
    }
    start = (besti == 0) ? (start) : (p[besti - 1]);
    end = (besti == (9 - 1)) ? (end) : (p[besti + 1]);
    pos = p[besti];
    lastbest = best;
  }

  *smallest = lastbest;
  return pos;
  *start_ref = start;
  *end_ref = end;
}


----------------------------
typedef double FindMinimumFun(size_t i, void *context)
----------------------------
pub f: _XImage_funcs
----------------------------
***/


static double EstimateCost(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend)
{
  return ZopfliCalculateBlockSizeAutoType(lz77, lstart, lend);
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
***/


static double SplitCost(size_t i, void *context)
{
  SplitCostContext *c = (SplitCostContext *) context;
  return EstimateCost(c->lz77, c->start, i) + EstimateCost(c->lz77, i, c->end);
}


/*** DEPENDENCIES:
typedef struct SplitCostContext
{
  const ZopfliLZ77Store *lz77;
  size_t start;
  size_t end;
} SplitCostContext
----------------------------
static double EstimateCost(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend)
{
  return ZopfliCalculateBlockSizeAutoType(lz77, lstart, lend);
}


----------------------------
***/


// hint:  ['lstart_ref is a mutable refrence to size_t', 'llpos_ref is a mutable refrence to size_t', 'numblocks_ref is a mutable refrence to size_t', 'done_idx_ref is a mutable refrence to unsigned int', 'origcost_ref is a mutable refrence to double']
void helper_ZopfliBlockSplitLZ77_1(size_t * const lstart_ref, size_t * const llpos_ref, size_t * const numblocks_ref, unsigned int * const done_idx_ref, double * const origcost_ref, const ZopfliLZ77Store * const lz77, size_t maxblocks, size_t ** const splitpoints, size_t * const npoints, size_t lend, unsigned char * const done, double splitcost)
{
  size_t lstart = *lstart_ref;
  size_t llpos = *llpos_ref;
  size_t numblocks = *numblocks_ref;
  unsigned int done_idx = *done_idx_ref;
  double origcost = *origcost_ref;
  SplitCostContext c;
  if ((maxblocks > 0) && (numblocks >= maxblocks))
  {
    break;
  }
  c.lz77 = lz77;
  c.start = lstart;
  c.end = lend;
  assert(lstart < lend);
  llpos = FindMinimum(SplitCost, &c, lstart + 1, lend, &splitcost);
  assert(llpos > lstart);
  assert(llpos < lend);
  origcost = EstimateCost(lz77, lstart, lend);
  if (((splitcost > origcost) || (llpos == (lstart + 1))) || (llpos == lend))
  {
    done[lstart + done_idx] = 1;
  }
  else
  {
    AddSorted(llpos, splitpoints, npoints);
    numblocks += 1;
  }
  if (!FindLargestSplittableBlock(lz77->size, done, *splitpoints, *npoints, &lstart, &lend))
  {
    break;
  }
  if ((lend - lstart) < 10)
  {
    break;
  }
  *lstart_ref = lstart;
  *llpos_ref = llpos;
  *numblocks_ref = numblocks;
  *done_idx_ref = done_idx;
  *origcost_ref = origcost;
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
static size_t FindMinimum(FindMinimumFun f, void *context, size_t start, size_t end, double *smallest)
{
  if ((end - start) < 1024)
  {
    double best = 1e30;
    size_t result = start;
    size_t i;
    for (i = start; i < end; i += 1)
    {
      double v = f(i, context);
      if (v < best)
      {
        best = v;
        result = i;
      }
    }

    *smallest = best;
    return result;
  }
  else
  {
    helper_FindMinimum_1(&start, &end, context, smallest);
  }
}


----------------------------
typedef struct SplitCostContext
{
  const ZopfliLZ77Store *lz77;
  size_t start;
  size_t end;
} SplitCostContext
----------------------------
static double EstimateCost(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend)
{
  return ZopfliCalculateBlockSizeAutoType(lz77, lstart, lend);
}


----------------------------
static int FindLargestSplittableBlock(size_t lz77size, const unsigned char *done, const size_t *splitpoints, size_t npoints, size_t *lstart, size_t *lend)
{
  size_t longest = 0;
  int found = 0;
  size_t i;
  for (i = 0; i <= npoints; i += 1)
  {
    size_t start = (i == 0) ? (0) : (splitpoints[i - 1]);
    size_t end = (i == npoints) ? (lz77size - 1) : (splitpoints[i]);
    if ((!done[start]) && ((end - start) > longest))
    {
      *lstart = start;
      *lend = end;
      found = 1;
      longest = end - start;
    }
  }

  return found;
}


----------------------------
static void AddSorted(size_t value, size_t **out, size_t *outsize)
{
  size_t i;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = value;
    *outsize += 1;
  }
  ;
  for (i = 0; (i + 1) < (*outsize); i += 1)
  {
    if ((*out)[i] > value)
    {
      size_t j;
      for (j = (*outsize) - 1; j > i; j -= 1)
      {
        (*out)[j] = (*out)[j - 1];
      }

      (*out)[i] = value;
      break;
    }
  }

}


----------------------------
static double SplitCost(size_t i, void *context)
{
  SplitCostContext *c = (SplitCostContext *) context;
  return EstimateCost(c->lz77, c->start, i) + EstimateCost(c->lz77, i, c->end);
}


----------------------------
***/


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
static void PrintBlockSplitPoints(const ZopfliLZ77Store *lz77, const size_t *lz77splitpoints, size_t nlz77points)
{
  size_t *splitpoints = 0;
  size_t npoints = 0;
  size_t i;
  size_t pos = 0;
  if (nlz77points > 0)
  {
    for (i = 0; i < lz77->size; i += 1)
    {
      size_t length = (lz77->dists[i] == 0) ? (1) : (lz77->litlens[i]);
      if (lz77splitpoints[npoints] == i)
      {
        {
          if (!((*(&npoints)) & ((*(&npoints)) - 1)))
          {
            splitpoints = (npoints == 0) ? (malloc(sizeof(*(*(&splitpoints))))) : (realloc(*(&splitpoints), (npoints * 2) * (sizeof(*(*(&splitpoints))))));
          }
          splitpoints[npoints] = pos;
          npoints += 1;
        }
        ;
        if (npoints == nlz77points)
        {
          break;
        }
      }
      pos += length;
    }

  }
  assert(npoints == nlz77points);
  fprintf(stderr, "block split points: ");
  for (i = 0; i < npoints; i += 1)
  {
    fprintf(stderr, "%d ", (int) splitpoints[i]);
  }

  fprintf(stderr, "(hex:");
  for (i = 0; i < npoints; i += 1)
  {
    fprintf(stderr, " %x", (int) splitpoints[i]);
  }

  fprintf(stderr, ")\n");
  free(splitpoints);
}


----------------------------
void helper_ZopfliBlockSplitLZ77_1(size_t * const lstart_ref, size_t * const llpos_ref, size_t * const numblocks_ref, unsigned int * const done_idx_ref, double * const origcost_ref, const ZopfliLZ77Store * const lz77, size_t maxblocks, size_t ** const splitpoints, size_t * const npoints, size_t lend, unsigned char * const done, double splitcost)
{
  size_t lstart = *lstart_ref;
  size_t llpos = *llpos_ref;
  size_t numblocks = *numblocks_ref;
  unsigned int done_idx = *done_idx_ref;
  double origcost = *origcost_ref;
  SplitCostContext c;
  if ((maxblocks > 0) && (numblocks >= maxblocks))
  {
    break;
  }
  c.lz77 = lz77;
  c.start = lstart;
  c.end = lend;
  assert(lstart < lend);
  llpos = FindMinimum(SplitCost, &c, lstart + 1, lend, &splitcost);
  assert(llpos > lstart);
  assert(llpos < lend);
  origcost = EstimateCost(lz77, lstart, lend);
  if (((splitcost > origcost) || (llpos == (lstart + 1))) || (llpos == lend))
  {
    done[lstart + done_idx] = 1;
  }
  else
  {
    AddSorted(llpos, splitpoints, npoints);
    numblocks += 1;
  }
  if (!FindLargestSplittableBlock(lz77->size, done, *splitpoints, *npoints, &lstart, &lend))
  {
    break;
  }
  if ((lend - lstart) < 10)
  {
    break;
  }
  *lstart_ref = lstart;
  *llpos_ref = llpos;
  *numblocks_ref = numblocks;
  *done_idx_ref = done_idx;
  *origcost_ref = origcost;
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
***/


