#include <assert.h>
#include <cache.h>
#include <deflate.h>
#include <gzip_container.h>
#include <hash.h>
#include <lz77.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <util.h>
#include <zlib_container.h>
#include <zopfli.h>
#include <zopfli_lib.c>

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
void ZopfliGzipCompress(const ZopfliOptions *options, const unsigned char *in, size_t insize, unsigned char **out, size_t *outsize);
void ZopfliZlibCompress(const ZopfliOptions *options, const unsigned char *in, size_t insize, unsigned char **out, size_t *outsize);
void ZopfliCompress(const ZopfliOptions *options, ZopfliFormat output_type, const unsigned char *in, size_t insize, unsigned char **out, size_t *outsize)
{
  if (output_type == ZOPFLI_FORMAT_GZIP)
  {
    ZopfliGzipCompress(options, in, insize, out, outsize);
  }
  else
    if (output_type == ZOPFLI_FORMAT_ZLIB)
  {
    ZopfliZlibCompress(options, in, insize, out, outsize);
  }
  else
    if (output_type == ZOPFLI_FORMAT_DEFLATE)
  {
    unsigned char bp = 0;
    ZopfliDeflate(options, 2, 1, in, insize, &bp, out, outsize);
  }
  else
  {
    assert(0);
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
void ZopfliGzipCompress(const ZopfliOptions *options, const unsigned char *in, size_t insize, unsigned char **out, size_t *outsize);
void ZopfliZlibCompress(const ZopfliOptions *options, const unsigned char *in, size_t insize, unsigned char **out, size_t *outsize);
void ZopfliCompress(const ZopfliOptions *options, ZopfliFormat output_type, const unsigned char *in, size_t insize, unsigned char **out, size_t *outsize)
{
  if (output_type == ZOPFLI_FORMAT_GZIP)
  {
    ZopfliGzipCompress(options, in, insize, out, outsize);
  }
  else
    if (output_type == ZOPFLI_FORMAT_ZLIB)
  {
    ZopfliZlibCompress(options, in, insize, out, outsize);
  }
  else
    if (output_type == ZOPFLI_FORMAT_DEFLATE)
  {
    unsigned char bp = 0;
    ZopfliDeflate(options, 2, 1, in, insize, &bp, out, outsize);
  }
  else
  {
    assert(0);
  }
}

