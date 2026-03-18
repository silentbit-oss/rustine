#include <assert.h>
#include <cache.h>
#include <hash.h>
#include <lz77.c>
#include <lz77.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <symbols.h>
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

static size_t CeilDiv(size_t a, size_t b)
{
  return ((a + b) - 1) / b;
}

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
    helper_ZopfliStoreLitLenDist_1(&length, &llstart, store, origsize);
  }
  else
  {
    helper_ZopfliStoreLitLenDist_2(&length, &dist, &llstart, &dstart, store, origsize);
  }
}

void ZopfliAppendLZ77Store(const ZopfliLZ77Store *store, ZopfliLZ77Store *target)
{
  size_t i;
  for (i = 0; i < store->size; i += 1)
  {
    ZopfliStoreLitLenDist(store->litlens[i], store->dists[i], store->pos[i], target);
  }

}

size_t ZopfliLZ77GetByteRange(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend)
{
  size_t l = lend - 1;
  if (lstart == lend)
  {
    return 0;
  }
  return (lz77->pos[l] + ((lz77->dists[l] == 0) ? (1) : (lz77->litlens[l]))) - lz77->pos[lstart];
}

static void ZopfliLZ77GetHistogramAt(const ZopfliLZ77Store *lz77, size_t lpos, size_t *ll_counts, size_t *d_counts)
{
  size_t llpos = 288 * (lpos / 288);
  size_t dpos = 32 * (lpos / 32);
  size_t i;
  for (i = 0; i < 288; i += 1)
  {
    ll_counts[i] = lz77->ll_counts[llpos + i];
  }

  for (i = lpos + 1; (i < (llpos + 288)) && (i < lz77->size); i += 1)
  {
    ll_counts[lz77->ll_symbol[i]] -= 1;
  }

  for (i = 0; i < 32; i += 1)
  {
    d_counts[i] = lz77->d_counts[dpos + i];
  }

  for (i = lpos + 1; (i < (dpos + 32)) && (i < lz77->size); i += 1)
  {
    if (lz77->dists[i] != 0)
    {
      d_counts[lz77->d_symbol[i]] -= 1;
    }
  }

}

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

void ZopfliCleanBlockState(ZopfliBlockState *s)
{
  if (s->lmc)
  {
    ZopfliCleanCache(s->lmc);
    free(s->lmc);
  }
}

static int GetLengthScore(int length, int distance)
{
  return (distance > 1024) ? (length - 1) : (length);
}

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

static const unsigned char *GetMatch(const unsigned char *scan, const unsigned char *match, const unsigned char *end, const unsigned char *safe_end)
{
  unsigned int match_idx = 0;
  unsigned int scan_idx = 0;
  if ((sizeof(size_t)) == 8)
  {
    while (((&scan[scan_idx]) < safe_end) && ((*((size_t *) scan)) == (*((size_t *) match))))
    {
      scan_idx += 8;
      match_idx += 8;
    }

  }
  else
    if ((sizeof(unsigned int)) == 4)
  {
    while (((&scan[scan_idx]) < safe_end) && ((*((unsigned int *) scan)) == (*((unsigned int *) match))))
    {
      scan_idx += 4;
      match_idx += 4;
    }

  }
  else
  {
    while ((((((((((&scan[scan_idx]) < safe_end) && (scan[scan_idx] == match[match_idx])) && ((*(++(&scan[scan_idx]))) == (*(++(&match[match_idx]))))) && ((*(++(&scan[scan_idx]))) == (*(++(&match[match_idx]))))) && ((*(++(&scan[scan_idx]))) == (*(++(&match[match_idx]))))) && ((*(++(&scan[scan_idx]))) == (*(++(&match[match_idx]))))) && ((*(++(&scan[scan_idx]))) == (*(++(&match[match_idx]))))) && ((*(++(&scan[scan_idx]))) == (*(++(&match[match_idx]))))) && ((*(++(&scan[scan_idx]))) == (*(++(&match[match_idx])))))
    {
      scan_idx += 1;
      match_idx += 1;
    }

  }
  while (((&scan[scan_idx]) != end) && (scan[scan_idx] == match[match_idx]))
  {
    scan_idx += 1;
    match_idx += 1;
  }

  return scan;
}

static int TryGetFromLongestMatchCache(ZopfliBlockState *s, size_t pos, size_t *limit, unsigned short *sublen, unsigned short *distance, unsigned short *length)
{
  size_t lmcpos = pos - s->blockstart;
  unsigned char cache_available = s->lmc && ((s->lmc->length[lmcpos] == 0) || (s->lmc->dist[lmcpos] != 0));
  unsigned char limit_ok_for_cache = cache_available && ((((*limit) == 258) || (s->lmc->length[lmcpos] <= (*limit))) || (sublen && (ZopfliMaxCachedSublen(s->lmc, lmcpos, s->lmc->length[lmcpos]) >= (*limit))));
  if ((s->lmc && limit_ok_for_cache) && cache_available)
  {
    if ((!sublen) || (s->lmc->length[lmcpos] <= ZopfliMaxCachedSublen(s->lmc, lmcpos, s->lmc->length[lmcpos])))
    {
      *length = s->lmc->length[lmcpos];
      if ((*length) > (*limit))
      {
        *length = *limit;
      }
      if (sublen)
      {
        ZopfliCacheToSublen(s->lmc, lmcpos, *length, sublen);
        *distance = sublen[*length];
        if (((*limit) == 258) && ((*length) >= 3))
        {
          assert(sublen[*length] == s->lmc->dist[lmcpos]);
        }
      }
      else
      {
        *distance = s->lmc->dist[lmcpos];
      }
      return 1;
    }
    *limit = s->lmc->length[lmcpos];
  }
  return 0;
}

static void StoreInLongestMatchCache(ZopfliBlockState *s, size_t pos, size_t limit, const unsigned short *sublen, unsigned short distance, unsigned short length)
{
  size_t lmcpos = pos - s->blockstart;
  unsigned char cache_available = s->lmc && ((s->lmc->length[lmcpos] == 0) || (s->lmc->dist[lmcpos] != 0));
  if (((s->lmc && (limit == 258)) && sublen) && (!cache_available))
  {
    assert((s->lmc->length[lmcpos] == 1) && (s->lmc->dist[lmcpos] == 0));
    s->lmc->dist[lmcpos] = (length < 3) ? (0) : (distance);
    s->lmc->length[lmcpos] = (length < 3) ? (0) : (length);
    assert(!((s->lmc->length[lmcpos] == 1) && (s->lmc->dist[lmcpos] == 0)));
    ZopfliSublenToCache(sublen, lmcpos, length, s->lmc);
  }
}

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

static size_t CeilDiv(size_t a, size_t b)
{
  return ((a + b) - 1) / b;
}

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
    store->size = origsize;
    {
      if (!((*(&store->size)) & ((*(&store->size)) - 1)))
      {
        store->ll_symbol = (store->size == 0) ? (malloc(sizeof(*(*(&store->ll_symbol))))) : (realloc(*(&store->ll_symbol), (store->size * 2) * (sizeof(*(*(&store->ll_symbol))))));
      }
      store->ll_symbol[store->size] = ZopfliGetLengthSymbol(length);
      store->size += 1;
    }
    ;
    store->size = origsize;
    {
      if (!((*(&store->size)) & ((*(&store->size)) - 1)))
      {
        store->d_symbol = (store->size == 0) ? (malloc(sizeof(*(*(&store->d_symbol))))) : (realloc(*(&store->d_symbol), (store->size * 2) * (sizeof(*(*(&store->d_symbol))))));
      }
      store->d_symbol[store->size] = ZopfliGetDistSymbol(dist);
      store->size += 1;
    }
    ;
    store->ll_counts[llstart + ZopfliGetLengthSymbol(length)] += 1;
    store->d_counts[dstart + ZopfliGetDistSymbol(dist)] += 1;
  }
}

void ZopfliAppendLZ77Store(const ZopfliLZ77Store *store, ZopfliLZ77Store *target)
{
  size_t i;
  for (i = 0; i < store->size; i += 1)
  {
    ZopfliStoreLitLenDist(store->litlens[i], store->dists[i], store->pos[i], target);
  }

}

size_t ZopfliLZ77GetByteRange(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend)
{
  size_t l = lend - 1;
  if (lstart == lend)
  {
    return 0;
  }
  return (lz77->pos[l] + ((lz77->dists[l] == 0) ? (1) : (lz77->litlens[l]))) - lz77->pos[lstart];
}

static void ZopfliLZ77GetHistogramAt(const ZopfliLZ77Store *lz77, size_t lpos, size_t *ll_counts, size_t *d_counts)
{
  size_t llpos = 288 * (lpos / 288);
  size_t dpos = 32 * (lpos / 32);
  size_t i;
  for (i = 0; i < 288; i += 1)
  {
    ll_counts[i] = lz77->ll_counts[llpos + i];
  }

  for (i = lpos + 1; (i < (llpos + 288)) && (i < lz77->size); i += 1)
  {
    ll_counts[lz77->ll_symbol[i]] -= 1;
  }

  for (i = 0; i < 32; i += 1)
  {
    d_counts[i] = lz77->d_counts[dpos + i];
  }

  for (i = lpos + 1; (i < (dpos + 32)) && (i < lz77->size); i += 1)
  {
    if (lz77->dists[i] != 0)
    {
      d_counts[lz77->d_symbol[i]] -= 1;
    }
  }

}

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

void ZopfliCleanBlockState(ZopfliBlockState *s)
{
  if (s->lmc)
  {
    ZopfliCleanCache(s->lmc);
    free(s->lmc);
  }
}

static int GetLengthScore(int length, int distance)
{
  return (distance > 1024) ? (length - 1) : (length);
}

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

static const unsigned char *GetMatch(const unsigned char *scan, const unsigned char *match, const unsigned char *end, const unsigned char *safe_end)
{
  unsigned int match_idx = 0;
  unsigned int scan_idx = 0;
  if ((sizeof(size_t)) == 8)
  {
    while (((&scan[scan_idx]) < safe_end) && ((*((size_t *) scan)) == (*((size_t *) match))))
    {
      scan_idx += 8;
      match_idx += 8;
    }

  }
  else
    if ((sizeof(unsigned int)) == 4)
  {
    while (((&scan[scan_idx]) < safe_end) && ((*((unsigned int *) scan)) == (*((unsigned int *) match))))
    {
      scan_idx += 4;
      match_idx += 4;
    }

  }
  else
  {
    while ((((((((((&scan[scan_idx]) < safe_end) && (scan[scan_idx] == match[match_idx])) && ((*(++(&scan[scan_idx]))) == (*(++(&match[match_idx]))))) && ((*(++(&scan[scan_idx]))) == (*(++(&match[match_idx]))))) && ((*(++(&scan[scan_idx]))) == (*(++(&match[match_idx]))))) && ((*(++(&scan[scan_idx]))) == (*(++(&match[match_idx]))))) && ((*(++(&scan[scan_idx]))) == (*(++(&match[match_idx]))))) && ((*(++(&scan[scan_idx]))) == (*(++(&match[match_idx]))))) && ((*(++(&scan[scan_idx]))) == (*(++(&match[match_idx])))))
    {
      scan_idx += 1;
      match_idx += 1;
    }

  }
  while (((&scan[scan_idx]) != end) && (scan[scan_idx] == match[match_idx]))
  {
    scan_idx += 1;
    match_idx += 1;
  }

  return scan;
}

static int TryGetFromLongestMatchCache(ZopfliBlockState *s, size_t pos, size_t *limit, unsigned short *sublen, unsigned short *distance, unsigned short *length)
{
  size_t lmcpos = pos - s->blockstart;
  unsigned char cache_available = s->lmc && ((s->lmc->length[lmcpos] == 0) || (s->lmc->dist[lmcpos] != 0));
  unsigned char limit_ok_for_cache = cache_available && ((((*limit) == 258) || (s->lmc->length[lmcpos] <= (*limit))) || (sublen && (ZopfliMaxCachedSublen(s->lmc, lmcpos, s->lmc->length[lmcpos]) >= (*limit))));
  if ((s->lmc && limit_ok_for_cache) && cache_available)
  {
    if ((!sublen) || (s->lmc->length[lmcpos] <= ZopfliMaxCachedSublen(s->lmc, lmcpos, s->lmc->length[lmcpos])))
    {
      *length = s->lmc->length[lmcpos];
      if ((*length) > (*limit))
      {
        *length = *limit;
      }
      if (sublen)
      {
        ZopfliCacheToSublen(s->lmc, lmcpos, *length, sublen);
        *distance = sublen[*length];
        if (((*limit) == 258) && ((*length) >= 3))
        {
          assert(sublen[*length] == s->lmc->dist[lmcpos]);
        }
      }
      else
      {
        *distance = s->lmc->dist[lmcpos];
      }
      return 1;
    }
    *limit = s->lmc->length[lmcpos];
  }
  return 0;
}

static void StoreInLongestMatchCache(ZopfliBlockState *s, size_t pos, size_t limit, const unsigned short *sublen, unsigned short distance, unsigned short length)
{
  size_t lmcpos = pos - s->blockstart;
  unsigned char cache_available = s->lmc && ((s->lmc->length[lmcpos] == 0) || (s->lmc->dist[lmcpos] != 0));
  if (((s->lmc && (limit == 258)) && sublen) && (!cache_available))
  {
    assert((s->lmc->length[lmcpos] == 1) && (s->lmc->dist[lmcpos] == 0));
    s->lmc->dist[lmcpos] = (length < 3) ? (0) : (distance);
    s->lmc->length[lmcpos] = (length < 3) ? (0) : (length);
    assert(!((s->lmc->length[lmcpos] == 1) && (s->lmc->dist[lmcpos] == 0)));
    ZopfliSublenToCache(sublen, lmcpos, length, s->lmc);
  }
}

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
    unsigned short currentlength = 0;
    assert(p < 32768);
    assert(p == hprev[pp + hprev_idx]);
    assert(hhashval[p + hhashval_idx] == hval);
    if (dist > 0)
    {
      assert(pos < size);
      assert(dist <= pos);
      scan_idx = &array[pos];
      match_idx = &array[pos - dist];
      if (((pos + bestlength) >= size) || ((*((&scan[scan_idx]) + bestlength)) == (*((&match[match_idx]) + bestlength))))
      {
        unsigned short same0 = h->same[pos & (32768 - 1)];
        if ((same0 > 2) && (scan[scan_idx] == match[match_idx]))
        {
          unsigned short same1 = h->same[(pos - dist) & (32768 - 1)];
          unsigned short same = (same0 < same1) ? (same0) : (same1);
          if (same > limit)
          {
            same = limit;
          }
          scan_idx += same;
          match_idx += same;
        }
        scan_idx = GetMatch(scan_idx, match, arrayend, arrayend_safe);
        currentlength = (&scan[scan_idx]) - (&array[pos]);
      }
      if (currentlength > bestlength)
      {
        if (sublen)
        {
          unsigned short j;
          for (j = bestlength + 1; j <= currentlength; j += 1)
          {
            sublen[j] = dist;
          }

        }
        bestdist = dist;
        bestlength = currentlength;
        if (currentlength >= limit)
        {
          break;
        }
      }
    }
    if ((((&hhead[hhead_idx]) != h->head2) && (bestlength >= h->same[hpos])) && (h->val2 == h->hashval2[p]))
    {
      hhead_idx = h->head2;
      hprev_idx = h->prev2;
      hhashval_idx = h->hashval2;
      hval = h->val2;
    }
    pp = p;
    p = hprev[p + hprev_idx];
    if (p == pp)
    {
      break;
    }
    dist += (p < pp) ? (pp - p) : ((32768 - p) + pp);
    chain_counter -= 1;
    if (chain_counter <= 0)
    {
      break;
    }
  }

  StoreInLongestMatchCache(s, pos, limit, sublen, bestdist, bestlength);
  assert(bestlength <= limit);
  *distance = bestdist;
  *length = bestlength;
  assert((pos + (*length)) <= size);
}

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
    ZopfliUpdateHash(in, i, inend, h);
    ZopfliFindLongestMatch(s, h, in, i, inend, 258, dummysublen, &dist, &leng);
    lengthscore = GetLengthScore(leng, dist);
    prevlengthscore = GetLengthScore(prev_length, prev_match);
    if (match_available)
    {
      match_available = 0;
      if (lengthscore > (prevlengthscore + 1))
      {
        ZopfliStoreLitLenDist(in[i - 1], 0, i - 1, store);
        if ((lengthscore >= 3) && (leng < 258))
        {
          match_available = 1;
          prev_length = leng;
          prev_match = dist;
          continue;
        }
      }
      else
      {
        leng = prev_length;
        dist = prev_match;
        lengthscore = prevlengthscore;
        ZopfliVerifyLenDist(in, inend, i - 1, dist, leng);
        ZopfliStoreLitLenDist(leng, dist, i - 1, store);
        for (j = 2; j < leng; j += 1)
        {
          assert(i < inend);
          i += 1;
          ZopfliUpdateHash(in, i, inend, h);
        }

        continue;
      }
    }
    else
      if ((lengthscore >= 3) && (leng < 258))
    {
      match_available = 1;
      prev_length = leng;
      prev_match = dist;
      continue;
    }
    if (lengthscore >= 3)
    {
      ZopfliVerifyLenDist(in, inend, i, dist, leng);
      ZopfliStoreLitLenDist(leng, dist, i, store);
    }
    else
    {
      leng = 1;
      ZopfliStoreLitLenDist(in[i], 0, i, store);
    }
    for (j = 1; j < leng; j += 1)
    {
      assert(i < inend);
      i += 1;
      ZopfliUpdateHash(in, i, inend, h);
    }

  }

}

void helper_ZopfliStoreLitLenDist_1(unsigned short * const length_ref, size_t * const llstart_ref, ZopfliLZ77Store * const store, size_t origsize)
{
  unsigned short length = *length_ref;
  size_t llstart = *llstart_ref;
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
  *length_ref = length;
  *llstart_ref = llstart;
}

void helper_ZopfliStoreLitLenDist_2(unsigned short * const length_ref, unsigned short * const dist_ref, size_t * const llstart_ref, size_t * const dstart_ref, ZopfliLZ77Store * const store, size_t origsize)
{
  unsigned short length = *length_ref;
  unsigned short dist = *dist_ref;
  size_t llstart = *llstart_ref;
  size_t dstart = *dstart_ref;
  store->size = origsize;
  {
    if (!((*(&store->size)) & ((*(&store->size)) - 1)))
    {
      store->ll_symbol = (store->size == 0) ? (malloc(sizeof(*(*(&store->ll_symbol))))) : (realloc(*(&store->ll_symbol), (store->size * 2) * (sizeof(*(*(&store->ll_symbol))))));
    }
    store->ll_symbol[store->size] = ZopfliGetLengthSymbol(length);
    store->size += 1;
  }
  ;
  store->size = origsize;
  {
    if (!((*(&store->size)) & ((*(&store->size)) - 1)))
    {
      store->d_symbol = (store->size == 0) ? (malloc(sizeof(*(*(&store->d_symbol))))) : (realloc(*(&store->d_symbol), (store->size * 2) * (sizeof(*(*(&store->d_symbol))))));
    }
    store->d_symbol[store->size] = ZopfliGetDistSymbol(dist);
    store->size += 1;
  }
  ;
  store->ll_counts[llstart + ZopfliGetLengthSymbol(length)] += 1;
  store->d_counts[dstart + ZopfliGetDistSymbol(dist)] += 1;
  *length_ref = length;
  *dist_ref = dist;
  *llstart_ref = llstart;
  *dstart_ref = dstart;
}

void helper_ZopfliFindLongestMatch_1(unsigned short * const p_ref, unsigned short * const pp_ref, unsigned short * const bestdist_ref, unsigned short * const bestlength_ref, unsigned int * const scan_idx_ref, unsigned int * const match_idx_ref, int * const chain_counter_ref, unsigned * const dist_ref, unsigned int * const hhead_idx_ref, unsigned int * const hprev_idx_ref, unsigned int * const hhashval_idx_ref, int * const hval_ref, const ZopfliHash * const h, const unsigned char * const array, size_t pos, size_t size, size_t limit, unsigned short * const sublen, unsigned short hpos, const unsigned char * const scan, const unsigned char * const match, const unsigned char * const arrayend, const unsigned char * const arrayend_safe, int * const hhead, unsigned short * const hprev, int * const hhashval)
{
  unsigned short p = *p_ref;
  unsigned short pp = *pp_ref;
  unsigned short bestdist = *bestdist_ref;
  unsigned short bestlength = *bestlength_ref;
  unsigned int scan_idx = *scan_idx_ref;
  unsigned int match_idx = *match_idx_ref;
  int chain_counter = *chain_counter_ref;
  unsigned dist = *dist_ref;
  unsigned int hhead_idx = *hhead_idx_ref;
  unsigned int hprev_idx = *hprev_idx_ref;
  unsigned int hhashval_idx = *hhashval_idx_ref;
  int hval = *hval_ref;
  unsigned short currentlength = 0;
  assert(p < 32768);
  assert(p == hprev[pp + hprev_idx]);
  assert(hhashval[p + hhashval_idx] == hval);
  if (dist > 0)
  {
    helper_helper_ZopfliFindLongestMatch_1_1(&bestdist, &bestlength, &scan_idx, &match_idx, &currentlength, h, array, pos, size, limit, sublen, scan, match, arrayend, arrayend_safe, dist);
  }
  if ((((&hhead[hhead_idx]) != h->head2) && (bestlength >= h->same[hpos])) && (h->val2 == h->hashval2[p]))
  {
    hhead_idx = h->head2;
    hprev_idx = h->prev2;
    hhashval_idx = h->hashval2;
    hval = h->val2;
  }
  pp = p;
  p = hprev[p + hprev_idx];
  if (p == pp)
  {
    break;
  }
  dist += (p < pp) ? (pp - p) : ((32768 - p) + pp);
  chain_counter -= 1;
  if (chain_counter <= 0)
  {
    break;
  }
  *p_ref = p;
  *pp_ref = pp;
  *bestdist_ref = bestdist;
  *bestlength_ref = bestlength;
  *scan_idx_ref = scan_idx;
  *match_idx_ref = match_idx;
  *chain_counter_ref = chain_counter;
  *dist_ref = dist;
  *hhead_idx_ref = hhead_idx;
  *hprev_idx_ref = hprev_idx;
  *hhashval_idx_ref = hhashval_idx;
  *hval_ref = hval;
}

void helper_ZopfliLZ77Greedy_1(size_t * const i_ref, size_t * const j_ref, unsigned short * const leng_ref, unsigned short * const dist_ref, int * const lengthscore_ref, unsigned * const prev_length_ref, unsigned * const prev_match_ref, int * const prevlengthscore_ref, int * const match_available_ref, ZopfliBlockState * const s, const unsigned char * const in, size_t inend, ZopfliLZ77Store * const store, ZopfliHash * const h, unsigned short dummysublen[259])
{
  size_t i = *i_ref;
  size_t j = *j_ref;
  unsigned short leng = *leng_ref;
  unsigned short dist = *dist_ref;
  int lengthscore = *lengthscore_ref;
  unsigned prev_length = *prev_length_ref;
  unsigned prev_match = *prev_match_ref;
  int prevlengthscore = *prevlengthscore_ref;
  int match_available = *match_available_ref;
  ZopfliUpdateHash(in, i, inend, h);
  ZopfliFindLongestMatch(s, h, in, i, inend, 258, dummysublen, &dist, &leng);
  lengthscore = GetLengthScore(leng, dist);
  prevlengthscore = GetLengthScore(prev_length, prev_match);
  if (match_available)
  {
    helper_helper_ZopfliLZ77Greedy_1_1(&i, &j, &leng, &dist, &lengthscore, &prev_length, &prev_match, &match_available, in, inend, store, h, prevlengthscore);
  }
  else
    if ((lengthscore >= 3) && (leng < 258))
  {
    match_available = 1;
    prev_length = leng;
    prev_match = dist;
    continue;
  }
  if (lengthscore >= 3)
  {
    ZopfliVerifyLenDist(in, inend, i, dist, leng);
    ZopfliStoreLitLenDist(leng, dist, i, store);
  }
  else
  {
    leng = 1;
    ZopfliStoreLitLenDist(in[i], 0, i, store);
  }
  for (j = 1; j < leng; j += 1)
  {
    assert(i < inend);
    i += 1;
    ZopfliUpdateHash(in, i, inend, h);
  }

  *i_ref = i;
  *j_ref = j;
  *leng_ref = leng;
  *dist_ref = dist;
  *lengthscore_ref = lengthscore;
  *prev_length_ref = prev_length;
  *prev_match_ref = prev_match;
  *prevlengthscore_ref = prevlengthscore;
  *match_available_ref = match_available;
}

void helper_helper_ZopfliFindLongestMatch_1_1(unsigned short * const bestdist_ref, unsigned short * const bestlength_ref, unsigned int * const scan_idx_ref, unsigned int * const match_idx_ref, unsigned short * const currentlength_ref, const ZopfliHash * const h, const unsigned char * const array, size_t pos, size_t size, size_t limit, unsigned short * const sublen, const unsigned char * const scan, const unsigned char * const match, const unsigned char * const arrayend, const unsigned char * const arrayend_safe, unsigned dist)
{
  unsigned short bestdist = *bestdist_ref;
  unsigned short bestlength = *bestlength_ref;
  unsigned int scan_idx = *scan_idx_ref;
  unsigned int match_idx = *match_idx_ref;
  unsigned short currentlength = *currentlength_ref;
  assert(pos < size);
  assert(dist <= pos);
  scan_idx = &array[pos];
  match_idx = &array[pos - dist];
  if (((pos + bestlength) >= size) || ((*((&scan[scan_idx]) + bestlength)) == (*((&match[match_idx]) + bestlength))))
  {
    unsigned short same0 = h->same[pos & (32768 - 1)];
    if ((same0 > 2) && (scan[scan_idx] == match[match_idx]))
    {
      unsigned short same1 = h->same[(pos - dist) & (32768 - 1)];
      unsigned short same = (same0 < same1) ? (same0) : (same1);
      if (same > limit)
      {
        same = limit;
      }
      scan_idx += same;
      match_idx += same;
    }
    scan_idx = GetMatch(scan_idx, match, arrayend, arrayend_safe);
    currentlength = (&scan[scan_idx]) - (&array[pos]);
  }
  if (currentlength > bestlength)
  {
    if (sublen)
    {
      unsigned short j;
      for (j = bestlength + 1; j <= currentlength; j += 1)
      {
        sublen[j] = dist;
      }

    }
    bestdist = dist;
    bestlength = currentlength;
    if (currentlength >= limit)
    {
      break;
    }
  }
  *bestdist_ref = bestdist;
  *bestlength_ref = bestlength;
  *scan_idx_ref = scan_idx;
  *match_idx_ref = match_idx;
  *currentlength_ref = currentlength;
}

void helper_helper_ZopfliLZ77Greedy_1_1(size_t * const i_ref, size_t * const j_ref, unsigned short * const leng_ref, unsigned short * const dist_ref, int * const lengthscore_ref, unsigned * const prev_length_ref, unsigned * const prev_match_ref, int * const match_available_ref, const unsigned char * const in, size_t inend, ZopfliLZ77Store * const store, ZopfliHash * const h, int prevlengthscore)
{
  size_t i = *i_ref;
  size_t j = *j_ref;
  unsigned short leng = *leng_ref;
  unsigned short dist = *dist_ref;
  int lengthscore = *lengthscore_ref;
  unsigned prev_length = *prev_length_ref;
  unsigned prev_match = *prev_match_ref;
  int match_available = *match_available_ref;
  match_available = 0;
  if (lengthscore > (prevlengthscore + 1))
  {
    ZopfliStoreLitLenDist(in[i - 1], 0, i - 1, store);
    if ((lengthscore >= 3) && (leng < 258))
    {
      match_available = 1;
      prev_length = leng;
      prev_match = dist;
      continue;
    }
  }
  else
  {
    leng = prev_length;
    dist = prev_match;
    lengthscore = prevlengthscore;
    ZopfliVerifyLenDist(in, inend, i - 1, dist, leng);
    ZopfliStoreLitLenDist(leng, dist, i - 1, store);
    for (j = 2; j < leng; j += 1)
    {
      assert(i < inend);
      i += 1;
      ZopfliUpdateHash(in, i, inend, h);
    }

    continue;
  }
  *i_ref = i;
  *j_ref = j;
  *leng_ref = leng;
  *dist_ref = dist;
  *lengthscore_ref = lengthscore;
  *prev_length_ref = prev_length;
  *prev_match_ref = prev_match;
  *match_available_ref = match_available;
}

