#include <assert.h>
#include <blocksplitter.h>
#include <cache.h>
#include <deflate.h>
#include <hash.h>
#include <lz77.h>
#include <math.h>
#include <squeeze.c>
#include <squeeze.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <symbols.h>
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
void ZopfliLZ77Optimal(ZopfliBlockState *s, const unsigned char *in, size_t instart, size_t inend, int numiterations, ZopfliLZ77Store *store);
void ZopfliLZ77OptimalFixed(ZopfliBlockState *s, const unsigned char *in, size_t instart, size_t inend, ZopfliLZ77Store *store);
void ZopfliBlockSplitLZ77(const ZopfliOptions *options, const ZopfliLZ77Store *lz77, size_t maxblocks, size_t **splitpoints, size_t *npoints);
void ZopfliBlockSplit(const ZopfliOptions *options, const unsigned char *in, size_t instart, size_t inend, size_t maxblocks, size_t **splitpoints, size_t *npoints);
void ZopfliBlockSplitSimple(const unsigned char *in, size_t instart, size_t inend, size_t blocksize, size_t **splitpoints, size_t *npoints);
void ZopfliDeflate(const ZopfliOptions *options, int btype, int final, const unsigned char *in, size_t insize, unsigned char *bp, unsigned char **out, size_t *outsize);
void ZopfliDeflatePart(const ZopfliOptions *options, int btype, int final, const unsigned char *in, size_t instart, size_t inend, unsigned char *bp, unsigned char **out, size_t *outsize);
double ZopfliCalculateBlockSize(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend, int btype);
double ZopfliCalculateBlockSizeAutoType(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend);
static int ZopfliGetDistExtraBits(int dist)
{
  if (dist < 5)
  {
    return 0;
  }
  return (31 ^ __builtin_clz(dist - 1)) - 1;
}

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

static int ZopfliGetLengthExtraBits(int l)
{
  static const int table[259] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0};
  return table[l];
}

static int ZopfliGetLengthExtraBitsValue(int l)
{
  static const int table[259] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 0};
  return table[l];
}

static int ZopfliGetLengthSymbol(int l)
{
  static const int table[259] = {0, 0, 0, 257, 258, 259, 260, 261, 262, 263, 264, 265, 265, 266, 266, 267, 267, 268, 268, 269, 269, 269, 269, 270, 270, 270, 270, 271, 271, 271, 271, 272, 272, 272, 272, 273, 273, 273, 273, 273, 273, 273, 273, 274, 274, 274, 274, 274, 274, 274, 274, 275, 275, 275, 275, 275, 275, 275, 275, 276, 276, 276, 276, 276, 276, 276, 276, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 285};
  return table[l];
}

static int ZopfliGetLengthSymbolExtraBits(int s)
{
  static const int table[29] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0};
  return table[s - 257];
}

static int ZopfliGetDistSymbolExtraBits(int s)
{
  static const int table[30] = {0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13};
  return table[s];
}

void ZopfliCalculateBitLengths(const size_t *count, size_t n, int maxbits, unsigned *bitlengths);
void ZopfliLengthsToSymbols(const unsigned *lengths, size_t n, unsigned maxbits, unsigned *symbols);
void ZopfliCalculateEntropy(const size_t *count, size_t n, double *bitlengths);
typedef struct SymbolStats
{
  size_t litlens[288];
  size_t dists[32];
  double ll_symbols[288];
  double d_symbols[32];
} SymbolStats;
static void InitStats(SymbolStats *stats)
{
  memset(stats->litlens, 0, 288 * (sizeof(stats->litlens[0])));
  memset(stats->dists, 0, 32 * (sizeof(stats->dists[0])));
  memset(stats->ll_symbols, 0, 288 * (sizeof(stats->ll_symbols[0])));
  memset(stats->d_symbols, 0, 32 * (sizeof(stats->d_symbols[0])));
}

static void CopyStats(SymbolStats *source, SymbolStats *dest)
{
  memcpy(dest->litlens, source->litlens, 288 * (sizeof(dest->litlens[0])));
  memcpy(dest->dists, source->dists, 32 * (sizeof(dest->dists[0])));
  memcpy(dest->ll_symbols, source->ll_symbols, 288 * (sizeof(dest->ll_symbols[0])));
  memcpy(dest->d_symbols, source->d_symbols, 32 * (sizeof(dest->d_symbols[0])));
}

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

typedef struct RanState
{
  unsigned int m_w;
  unsigned int m_z;
} RanState;
static void InitRanState(RanState *state)
{
  state->m_w = 1;
  state->m_z = 2;
}

static unsigned int Ran(RanState *state)
{
  state->m_z = (36969 * (state->m_z & 65535)) + (state->m_z >> 16);
  state->m_w = (18000 * (state->m_w & 65535)) + (state->m_w >> 16);
  return (state->m_z << 16) + state->m_w;
}

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

static void RandomizeStatFreqs(RanState *state, SymbolStats *stats)
{
  RandomizeFreqs(state, stats->litlens, 288);
  RandomizeFreqs(state, stats->dists, 32);
  stats->litlens[256] = 1;
}

static void ClearStatFreqs(SymbolStats *stats)
{
  size_t i;
  for (i = 0; i < 288; i += 1)
  {
    stats->litlens[i] = 0;
  }

  for (i = 0; i < 32; i += 1)
  {
    stats->dists[i] = 0;
  }

}

typedef double CostModelFun(unsigned litlen, unsigned dist, void *context);
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

static size_t zopfli_min(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}

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
  {
    costs[i] = 1e30;
  }

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
    helper_FollowPath_1(&j, &pos, &total_length_test, s, in, inend, path, store, h, i);
  }

}

static void CalculateStatistics(SymbolStats *stats)
{
  ZopfliCalculateEntropy(stats->litlens, 288, stats->ll_symbols);
  ZopfliCalculateEntropy(stats->dists, 32, stats->d_symbols);
}

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
void ZopfliLZ77Optimal(ZopfliBlockState *s, const unsigned char *in, size_t instart, size_t inend, int numiterations, ZopfliLZ77Store *store);
void ZopfliLZ77OptimalFixed(ZopfliBlockState *s, const unsigned char *in, size_t instart, size_t inend, ZopfliLZ77Store *store);
void ZopfliBlockSplitLZ77(const ZopfliOptions *options, const ZopfliLZ77Store *lz77, size_t maxblocks, size_t **splitpoints, size_t *npoints);
void ZopfliBlockSplit(const ZopfliOptions *options, const unsigned char *in, size_t instart, size_t inend, size_t maxblocks, size_t **splitpoints, size_t *npoints);
void ZopfliBlockSplitSimple(const unsigned char *in, size_t instart, size_t inend, size_t blocksize, size_t **splitpoints, size_t *npoints);
void ZopfliDeflate(const ZopfliOptions *options, int btype, int final, const unsigned char *in, size_t insize, unsigned char *bp, unsigned char **out, size_t *outsize);
void ZopfliDeflatePart(const ZopfliOptions *options, int btype, int final, const unsigned char *in, size_t instart, size_t inend, unsigned char *bp, unsigned char **out, size_t *outsize);
double ZopfliCalculateBlockSize(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend, int btype);
double ZopfliCalculateBlockSizeAutoType(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend);
static int ZopfliGetDistExtraBits(int dist)
{
  if (dist < 5)
  {
    return 0;
  }
  return (31 ^ __builtin_clz(dist - 1)) - 1;
}

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

static int ZopfliGetLengthExtraBits(int l)
{
  static const int table[259] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0};
  return table[l];
}

static int ZopfliGetLengthExtraBitsValue(int l)
{
  static const int table[259] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 0};
  return table[l];
}

static int ZopfliGetLengthSymbol(int l)
{
  static const int table[259] = {0, 0, 0, 257, 258, 259, 260, 261, 262, 263, 264, 265, 265, 266, 266, 267, 267, 268, 268, 269, 269, 269, 269, 270, 270, 270, 270, 271, 271, 271, 271, 272, 272, 272, 272, 273, 273, 273, 273, 273, 273, 273, 273, 274, 274, 274, 274, 274, 274, 274, 274, 275, 275, 275, 275, 275, 275, 275, 275, 276, 276, 276, 276, 276, 276, 276, 276, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 277, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 278, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 279, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 280, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 281, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 282, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 283, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 284, 285};
  return table[l];
}

static int ZopfliGetLengthSymbolExtraBits(int s)
{
  static const int table[29] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 0};
  return table[s - 257];
}

static int ZopfliGetDistSymbolExtraBits(int s)
{
  static const int table[30] = {0, 0, 0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13};
  return table[s];
}

void ZopfliCalculateBitLengths(const size_t *count, size_t n, int maxbits, unsigned *bitlengths);
void ZopfliLengthsToSymbols(const unsigned *lengths, size_t n, unsigned maxbits, unsigned *symbols);
void ZopfliCalculateEntropy(const size_t *count, size_t n, double *bitlengths);
typedef struct SymbolStats
{
  size_t litlens[288];
  size_t dists[32];
  double ll_symbols[288];
  double d_symbols[32];
} SymbolStats;
static void InitStats(SymbolStats *stats)
{
  memset(stats->litlens, 0, 288 * (sizeof(stats->litlens[0])));
  memset(stats->dists, 0, 32 * (sizeof(stats->dists[0])));
  memset(stats->ll_symbols, 0, 288 * (sizeof(stats->ll_symbols[0])));
  memset(stats->d_symbols, 0, 32 * (sizeof(stats->d_symbols[0])));
}

static void CopyStats(SymbolStats *source, SymbolStats *dest)
{
  memcpy(dest->litlens, source->litlens, 288 * (sizeof(dest->litlens[0])));
  memcpy(dest->dists, source->dists, 32 * (sizeof(dest->dists[0])));
  memcpy(dest->ll_symbols, source->ll_symbols, 288 * (sizeof(dest->ll_symbols[0])));
  memcpy(dest->d_symbols, source->d_symbols, 32 * (sizeof(dest->d_symbols[0])));
}

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

typedef struct RanState
{
  unsigned int m_w;
  unsigned int m_z;
} RanState;
static void InitRanState(RanState *state)
{
  state->m_w = 1;
  state->m_z = 2;
}

static unsigned int Ran(RanState *state)
{
  state->m_z = (36969 * (state->m_z & 65535)) + (state->m_z >> 16);
  state->m_w = (18000 * (state->m_w & 65535)) + (state->m_w >> 16);
  return (state->m_z << 16) + state->m_w;
}

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

static void RandomizeStatFreqs(RanState *state, SymbolStats *stats)
{
  RandomizeFreqs(state, stats->litlens, 288);
  RandomizeFreqs(state, stats->dists, 32);
  stats->litlens[256] = 1;
}

static void ClearStatFreqs(SymbolStats *stats)
{
  size_t i;
  for (i = 0; i < 288; i += 1)
  {
    stats->litlens[i] = 0;
  }

  for (i = 0; i < 32; i += 1)
  {
    stats->dists[i] = 0;
  }

}

typedef double CostModelFun(unsigned litlen, unsigned dist, void *context);
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

static size_t zopfli_min(size_t a, size_t b)
{
  return (a < b) ? (a) : (b);
}

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
  {
    costs[i] = 1e30;
  }

  costs[0] = 0;
  length_array[0] = 0;
  for (i = instart; i < inend; i += 1)
  {
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

  }

  assert(costs[blocksize] >= 0);
  result = costs[blocksize];
  return result;
}

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

static void CalculateStatistics(SymbolStats *stats)
{
  ZopfliCalculateEntropy(stats->litlens, 288, stats->ll_symbols);
  ZopfliCalculateEntropy(stats->dists, 32, stats->d_symbols);
}

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
  }

  free(length_array);
  free(path);
  free(costs);
  ZopfliCleanLZ77Store(&currentstore);
  ZopfliCleanHash(h);
}

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

void helper_FollowPath_1(size_t * const j_ref, size_t * const pos_ref, size_t * const total_length_test_ref, ZopfliBlockState * const s, const unsigned char * const in, size_t inend, unsigned short * const path, ZopfliLZ77Store * const store, ZopfliHash * const h, size_t i)
{
  size_t j = *j_ref;
  size_t pos = *pos_ref;
  size_t total_length_test = *total_length_test_ref;
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
  *j_ref = j;
  *pos_ref = pos;
  *total_length_test_ref = total_length_test;
}

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

