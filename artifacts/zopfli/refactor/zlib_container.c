#include <cache.h>
#include <deflate.h>
#include <hash.h>
#include <lz77.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util.h>
#include <zlib_container.c>
#include <zlib_container.h>
#include <zopfli.h>

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
void ZopfliZlibCompress(const ZopfliOptions *options, const unsigned char *in, size_t insize, unsigned char **out, size_t *outsize);
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
void ZopfliDeflate(const ZopfliOptions *options, int btype, int final, const unsigned char *in, size_t insize, unsigned char *bp, unsigned char **out, size_t *outsize);
void ZopfliDeflatePart(const ZopfliOptions *options, int btype, int final, const unsigned char *in, size_t instart, size_t inend, unsigned char *bp, unsigned char **out, size_t *outsize);
double ZopfliCalculateBlockSize(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend, int btype);
double ZopfliCalculateBlockSizeAutoType(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend);
static unsigned adler32(const unsigned char *data, size_t size)
{
  unsigned int data_idx = 0;
  static const unsigned sums_overflow = 5550;
  unsigned s1 = 1;
  unsigned s2 = 1 >> 16;
  while (size > 0)
  {
    size_t amount = (size > sums_overflow) ? (sums_overflow) : (size);
    size -= amount;
    while (amount > 0)
    {
      s1 += data[data_idx];
      data_idx += 1;
      s2 += s1;
      amount -= 1;
    }

    s1 %= 65521;
    s2 %= 65521;
  }

  return (s2 << 16) | s1;
}

void ZopfliZlibCompress(const ZopfliOptions *options, const unsigned char *in, size_t insize, unsigned char **out, size_t *outsize)
{
  unsigned char bitpointer = 0;
  unsigned checksum = adler32(in, (unsigned) insize);
  unsigned cmf = 120;
  unsigned flevel = 3;
  unsigned fdict = 0;
  unsigned cmfflg = ((256 * cmf) + (fdict * 32)) + (flevel * 64);
  unsigned fcheck = 31 - (cmfflg % 31);
  cmfflg += fcheck;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = cmfflg / 256;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = cmfflg % 256;
    *outsize += 1;
  }
  ;
  ZopfliDeflate(options, 2, 1, in, insize, &bitpointer, out, outsize);
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = (checksum >> 24) % 256;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = (checksum >> 16) % 256;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = (checksum >> 8) % 256;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = checksum % 256;
    *outsize += 1;
  }
  ;
  if (options->verbose)
  {
    fprintf(stderr, "Original Size: %d, Zlib: %d, Compression: %f%% Removed\n", (int) insize, (int) (*outsize), (100.0 * ((double) (insize - (*outsize)))) / ((double) insize));
  }
}


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
void ZopfliZlibCompress(const ZopfliOptions *options, const unsigned char *in, size_t insize, unsigned char **out, size_t *outsize);
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
void ZopfliDeflate(const ZopfliOptions *options, int btype, int final, const unsigned char *in, size_t insize, unsigned char *bp, unsigned char **out, size_t *outsize);
void ZopfliDeflatePart(const ZopfliOptions *options, int btype, int final, const unsigned char *in, size_t instart, size_t inend, unsigned char *bp, unsigned char **out, size_t *outsize);
double ZopfliCalculateBlockSize(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend, int btype);
double ZopfliCalculateBlockSizeAutoType(const ZopfliLZ77Store *lz77, size_t lstart, size_t lend);
static unsigned adler32(const unsigned char *data, size_t size)
{
  unsigned int data_idx = 0;
  static const unsigned sums_overflow = 5550;
  unsigned s1 = 1;
  unsigned s2 = 1 >> 16;
  while (size > 0)
  {
    size_t amount = (size > sums_overflow) ? (sums_overflow) : (size);
    size -= amount;
    while (amount > 0)
    {
      s1 += data[data_idx];
      data_idx += 1;
      s2 += s1;
      amount -= 1;
    }

    s1 %= 65521;
    s2 %= 65521;
  }

  return (s2 << 16) | s1;
}

void ZopfliZlibCompress(const ZopfliOptions *options, const unsigned char *in, size_t insize, unsigned char **out, size_t *outsize)
{
  unsigned char bitpointer = 0;
  unsigned checksum = adler32(in, (unsigned) insize);
  unsigned cmf = 120;
  unsigned flevel = 3;
  unsigned fdict = 0;
  unsigned cmfflg = ((256 * cmf) + (fdict * 32)) + (flevel * 64);
  unsigned fcheck = 31 - (cmfflg % 31);
  cmfflg += fcheck;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = cmfflg / 256;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = cmfflg % 256;
    *outsize += 1;
  }
  ;
  ZopfliDeflate(options, 2, 1, in, insize, &bitpointer, out, outsize);
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = (checksum >> 24) % 256;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = (checksum >> 16) % 256;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = (checksum >> 8) % 256;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = checksum % 256;
    *outsize += 1;
  }
  ;
  if (options->verbose)
  {
    fprintf(stderr, "Original Size: %d, Zlib: %d, Compression: %f%% Removed\n", (int) insize, (int) (*outsize), (100.0 * ((double) (insize - (*outsize)))) / ((double) insize));
  }
}

