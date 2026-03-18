#include <assert.h>
#include <blocksplitter.c>
#include <blocksplitter.h>
#include <cache.h>
#include <deflate.h>
#include <hash.h>
#include <lz77.h>
#include <squeeze.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tree.h>
#include <util.h>
#include <zopfli.h>

typedef struct ZopfliLongestMatchCache
{
  unsigned short *length;
  unsigned short *dist;
  unsigned char *sublen;
} ZopfliLongestMatchCache;
void ZopfliInitCache(size_t blocksize, ZopfliLongestMatchCache *lmc);
void ZopfliCleanCache(ZopfliLongestMatchCache *lmc);
void ZopfliSublenToCache(const unsigned short *sublen, size_t pos, size_t length, ZopfliLongestMatchCache *lmc);
void ZopfliCacheToSublen(const ZopfliLongestMatchCache *lmc, size_t pos, size_t length, unsigned short *sublen);
unsigned ZopfliMaxCachedSublen(const ZopfliLongestMatchCache *lmc, size_t pos, size_t length);
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
} ZopfliHash;
void ZopfliAllocHash(size_t window_size, ZopfliHash *h);
void ZopfliResetHash(size_t window_size, ZopfliHash *h);
void ZopfliCleanHash(ZopfliHash *h);
void ZopfliUpdateHash(const unsigned char *array, size_t pos, size_t end, ZopfliHash *h);
void ZopfliWarmupHash(const unsigned char *array, size_t pos, size_t end, ZopfliHash *h);
typedef struct ZopfliOptions
{
  int verbose;
  int verbose_more;
  int numiterations;
  int blocksplitting;
  int blocksplittinglast;
  int blocksplittingmax;
} ZopfliOptions;
void ZopfliInitOptions(ZopfliOptions *options);
typedef enum 
{
  ZOPFLI_FORMAT_GZIP,
  ZOPFLI_FORMAT_ZLIB,
  ZOPFLI_FORMAT_DEFLATE
} ZopfliFormat;
void ZopfliCompress(const ZopfliOptions *options, ZopfliFormat output_type, const unsigned char *in, size_t insize, unsigned char **out, size_t *outsize);
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
} ZopfliLZ77Store;
void ZopfliInitLZ77Store(const unsigned char *data, ZopfliLZ77Store *store);
void ZopfliCleanLZ77Store(ZopfliLZ77Store *store);
void ZopfliCopyLZ77Store(const ZopfliLZ77Store *source, ZopfliLZ77Store *dest);
void ZopfliStoreLitLenDist(unsigned short length, unsigned short dist, size_t pos, ZopfliLZ77Store *store);
void ZopfliAppendLZ77Store(const ZopfliLZ77Store *store, ZopfliLZ77Store *target);
size_t ZopfliLZ77GetByteRange(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend);
void ZopfliLZ77GetHistogram(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend, size_t *ll_counts, size_t *d_counts);
typedef struct ZopfliBlockState
{
  const ZopfliOptions *options;
  ZopfliLongestMatchCache *lmc;
  size_t blockstart;
  size_t blockend;
} ZopfliBlockState;
void ZopfliInitBlockState(const ZopfliOptions *options, size_t blockstart, size_t blockend, int add_lmc, ZopfliBlockState *s);
void ZopfliCleanBlockState(ZopfliBlockState *s);
void ZopfliFindLongestMatch(ZopfliBlockState *s, const ZopfliHash *h, const unsigned char *array, size_t pos, size_t size, size_t limit, unsigned short *sublen, unsigned short *distance, unsigned short *length);
void ZopfliVerifyLenDist(const unsigned char *data, size_t datasize, size_t pos, unsigned short dist, unsigned short length);
void ZopfliLZ77Greedy(ZopfliBlockState *s, const unsigned char *in, size_t instart, size_t inend, ZopfliLZ77Store *store, ZopfliHash *h);
void ZopfliBlockSplitLZ77(const ZopfliOptions *options, const ZopfliLZ77Store *lz77, size_t maxblocks, size_t **splitpoints, size_t *npoints);
void ZopfliBlockSplit(const ZopfliOptions *options, const unsigned char *in, size_t instart, size_t inend, size_t maxblocks, size_t **splitpoints, size_t *npoints);
void ZopfliBlockSplitSimple(const unsigned char *in, size_t instart, size_t inend, size_t blocksize, size_t **splitpoints, size_t *npoints);
void ZopfliDeflate(const ZopfliOptions *options, int btype, int final, const unsigned char *in, size_t insize, unsigned char *bp, unsigned char **out, size_t *outsize);
void ZopfliDeflatePart(const ZopfliOptions *options, int btype, int final, const unsigned char *in, size_t instart, size_t inend, unsigned char *bp, unsigned char **out, size_t *outsize);
double ZopfliCalculateBlockSize(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend, int btype);
double ZopfliCalculateBlockSizeAutoType(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend);
void ZopfliLZ77Optimal(ZopfliBlockState *s, const unsigned char *in, size_t instart, size_t inend, int numiterations, ZopfliLZ77Store *store);
void ZopfliLZ77OptimalFixed(ZopfliBlockState *s, const unsigned char *in, size_t instart, size_t inend, ZopfliLZ77Store *store);
void ZopfliCalculateBitLengths(const size_t *count, size_t n, int maxbits, unsigned *bitlengths);
void ZopfliLengthsToSymbols(const unsigned *lengths, size_t n, unsigned maxbits, unsigned *symbols);
void ZopfliCalculateEntropy(const size_t *count, size_t n, double *bitlengths);
typedef double FindMinimumFun(size_t i, void *context);
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

static double EstimateCost(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend)
{
  return ZopfliCalculateBlockSizeAutoType(lz77, lstart, lend);
}

typedef struct SplitCostContext
{
  const ZopfliLZ77Store *lz77;
  size_t start;
  size_t end;
} SplitCostContext;
static double SplitCost(size_t i, void *context)
{
  SplitCostContext *c = (SplitCostContext *) context;
  return EstimateCost(c->lz77, c->start, i) + EstimateCost(c->lz77, i, c->end);
}

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
  {
    done[i + done_idx] = 0;
  }

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
    helper_ZopfliBlockSplit_1(&pos, &i, splitpoints, npoints, lz77splitpoints, nlz77points, store);
  }
  assert((*npoints) == nlz77points);
  free(lz77splitpoints);
  ZopfliCleanBlockState(&s);
  ZopfliCleanLZ77Store(&store);
  ZopfliCleanHash(h);
}

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


typedef struct ZopfliLongestMatchCache
{
  unsigned short *length;
  unsigned short *dist;
  unsigned char *sublen;
} ZopfliLongestMatchCache;
void ZopfliInitCache(size_t blocksize, ZopfliLongestMatchCache *lmc);
void ZopfliCleanCache(ZopfliLongestMatchCache *lmc);
void ZopfliSublenToCache(const unsigned short *sublen, size_t pos, size_t length, ZopfliLongestMatchCache *lmc);
void ZopfliCacheToSublen(const ZopfliLongestMatchCache *lmc, size_t pos, size_t length, unsigned short *sublen);
unsigned ZopfliMaxCachedSublen(const ZopfliLongestMatchCache *lmc, size_t pos, size_t length);
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
} ZopfliHash;
void ZopfliAllocHash(size_t window_size, ZopfliHash *h);
void ZopfliResetHash(size_t window_size, ZopfliHash *h);
void ZopfliCleanHash(ZopfliHash *h);
void ZopfliUpdateHash(const unsigned char *array, size_t pos, size_t end, ZopfliHash *h);
void ZopfliWarmupHash(const unsigned char *array, size_t pos, size_t end, ZopfliHash *h);
typedef struct ZopfliOptions
{
  int verbose;
  int verbose_more;
  int numiterations;
  int blocksplitting;
  int blocksplittinglast;
  int blocksplittingmax;
} ZopfliOptions;
void ZopfliInitOptions(ZopfliOptions *options);
typedef enum 
{
  ZOPFLI_FORMAT_GZIP,
  ZOPFLI_FORMAT_ZLIB,
  ZOPFLI_FORMAT_DEFLATE
} ZopfliFormat;
void ZopfliCompress(const ZopfliOptions *options, ZopfliFormat output_type, const unsigned char *in, size_t insize, unsigned char **out, size_t *outsize);
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
} ZopfliLZ77Store;
void ZopfliInitLZ77Store(const unsigned char *data, ZopfliLZ77Store *store);
void ZopfliCleanLZ77Store(ZopfliLZ77Store *store);
void ZopfliCopyLZ77Store(const ZopfliLZ77Store *source, ZopfliLZ77Store *dest);
void ZopfliStoreLitLenDist(unsigned short length, unsigned short dist, size_t pos, ZopfliLZ77Store *store);
void ZopfliAppendLZ77Store(const ZopfliLZ77Store *store, ZopfliLZ77Store *target);
size_t ZopfliLZ77GetByteRange(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend);
void ZopfliLZ77GetHistogram(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend, size_t *ll_counts, size_t *d_counts);
typedef struct ZopfliBlockState
{
  const ZopfliOptions *options;
  ZopfliLongestMatchCache *lmc;
  size_t blockstart;
  size_t blockend;
} ZopfliBlockState;
void ZopfliInitBlockState(const ZopfliOptions *options, size_t blockstart, size_t blockend, int add_lmc, ZopfliBlockState *s);
void ZopfliCleanBlockState(ZopfliBlockState *s);
void ZopfliFindLongestMatch(ZopfliBlockState *s, const ZopfliHash *h, const unsigned char *array, size_t pos, size_t size, size_t limit, unsigned short *sublen, unsigned short *distance, unsigned short *length);
void ZopfliVerifyLenDist(const unsigned char *data, size_t datasize, size_t pos, unsigned short dist, unsigned short length);
void ZopfliLZ77Greedy(ZopfliBlockState *s, const unsigned char *in, size_t instart, size_t inend, ZopfliLZ77Store *store, ZopfliHash *h);
void ZopfliBlockSplitLZ77(const ZopfliOptions *options, const ZopfliLZ77Store *lz77, size_t maxblocks, size_t **splitpoints, size_t *npoints);
void ZopfliBlockSplit(const ZopfliOptions *options, const unsigned char *in, size_t instart, size_t inend, size_t maxblocks, size_t **splitpoints, size_t *npoints);
void ZopfliBlockSplitSimple(const unsigned char *in, size_t instart, size_t inend, size_t blocksize, size_t **splitpoints, size_t *npoints);
void ZopfliDeflate(const ZopfliOptions *options, int btype, int final, const unsigned char *in, size_t insize, unsigned char *bp, unsigned char **out, size_t *outsize);
void ZopfliDeflatePart(const ZopfliOptions *options, int btype, int final, const unsigned char *in, size_t instart, size_t inend, unsigned char *bp, unsigned char **out, size_t *outsize);
double ZopfliCalculateBlockSize(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend, int btype);
double ZopfliCalculateBlockSizeAutoType(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend);
void ZopfliLZ77Optimal(ZopfliBlockState *s, const unsigned char *in, size_t instart, size_t inend, int numiterations, ZopfliLZ77Store *store);
void ZopfliLZ77OptimalFixed(ZopfliBlockState *s, const unsigned char *in, size_t instart, size_t inend, ZopfliLZ77Store *store);
void ZopfliCalculateBitLengths(const size_t *count, size_t n, int maxbits, unsigned *bitlengths);
void ZopfliLengthsToSymbols(const unsigned *lengths, size_t n, unsigned maxbits, unsigned *symbols);
void ZopfliCalculateEntropy(const size_t *count, size_t n, double *bitlengths);
typedef double FindMinimumFun(size_t i, void *context);
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
  }
}

static double EstimateCost(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend)
{
  return ZopfliCalculateBlockSizeAutoType(lz77, lstart, lend);
}

typedef struct SplitCostContext
{
  const ZopfliLZ77Store *lz77;
  size_t start;
  size_t end;
} SplitCostContext;
static double SplitCost(size_t i, void *context)
{
  SplitCostContext *c = (SplitCostContext *) context;
  return EstimateCost(c->lz77, c->start, i) + EstimateCost(c->lz77, i, c->end);
}

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
  {
    done[i + done_idx] = 0;
  }

  lstart = 0;
  lend = lz77->size;
  for (;;)
  {
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
  }

  if (options->verbose)
  {
    PrintBlockSplitPoints(lz77, *splitpoints, *npoints);
  }
  free(done);
}

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
    helper_helper_FindMinimum_1_1(&start, &end, &i, &besti, &best, &lastbest, &pos, context, p, vp);
  }

  *smallest = lastbest;
  return pos;
  *start_ref = start;
  *end_ref = end;
}

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

void helper_ZopfliBlockSplit_1(size_t * const pos_ref, size_t * const i_ref, size_t ** const splitpoints, size_t * const npoints, size_t * const lz77splitpoints, size_t nlz77points, ZopfliLZ77Store store)
{
  size_t pos = *pos_ref;
  size_t i = *i_ref;
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

  *pos_ref = pos;
  *i_ref = i;
}

void helper_helper_FindMinimum_1_1(size_t * const start_ref, size_t * const end_ref, size_t * const i_ref, size_t * const besti_ref, double * const best_ref, double * const lastbest_ref, size_t * const pos_ref, void * const context, size_t p[9], double vp[9])
{
  size_t start = *start_ref;
  size_t end = *end_ref;
  size_t i = *i_ref;
  size_t besti = *besti_ref;
  double best = *best_ref;
  double lastbest = *lastbest_ref;
  size_t pos = *pos_ref;
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
  *start_ref = start;
  *end_ref = end;
  *i_ref = i;
  *besti_ref = besti;
  *best_ref = best;
  *lastbest_ref = lastbest;
  *pos_ref = pos;
}

