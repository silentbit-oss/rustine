#include <cache.h>
#include <deflate.h>
#include <gzip_container.c>
#include <gzip_container.h>
#include <hash.h>
#include <lz77.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <util.h>
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
void ZopfliGzipCompress(const ZopfliOptions *options, const unsigned char *in, size_t insize, unsigned char **out, size_t *outsize);
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
static const unsigned long crc32_table[256] = {0u, 1996959894u, 3993919788u, 2567524794u, 124634137u, 1886057615u, 3915621685u, 2657392035u, 249268274u, 2044508324u, 3772115230u, 2547177864u, 162941995u, 2125561021u, 3887607047u, 2428444049u, 498536548u, 1789927666u, 4089016648u, 2227061214u, 450548861u, 1843258603u, 4107580753u, 2211677639u, 325883990u, 1684777152u, 4251122042u, 2321926636u, 335633487u, 1661365465u, 4195302755u, 2366115317u, 997073096u, 1281953886u, 3579855332u, 2724688242u, 1006888145u, 1258607687u, 3524101629u, 2768942443u, 901097722u, 1119000684u, 3686517206u, 2898065728u, 853044451u, 1172266101u, 3705015759u, 2882616665u, 651767980u, 1373503546u, 3369554304u, 3218104598u, 565507253u, 1454621731u, 3485111705u, 3099436303u, 671266974u, 1594198024u, 3322730930u, 2970347812u, 795835527u, 1483230225u, 3244367275u, 3060149565u, 1994146192u, 31158534u, 2563907772u, 4023717930u, 1907459465u, 112637215u, 2680153253u, 3904427059u, 2013776290u, 251722036u, 2517215374u, 3775830040u, 2137656763u, 141376813u, 2439277719u, 3865271297u, 1802195444u, 476864866u, 2238001368u, 4066508878u, 1812370925u, 453092731u, 2181625025u, 4111451223u, 1706088902u, 314042704u, 2344532202u, 4240017532u, 1658658271u, 366619977u, 2362670323u, 4224994405u, 1303535960u, 984961486u, 2747007092u, 3569037538u, 1256170817u, 1037604311u, 2765210733u, 3554079995u, 1131014506u, 879679996u, 2909243462u, 3663771856u, 1141124467u, 855842277u, 2852801631u, 3708648649u, 1342533948u, 654459306u, 3188396048u, 3373015174u, 1466479909u, 544179635u, 3110523913u, 3462522015u, 1591671054u, 702138776u, 2966460450u, 3352799412u, 1504918807u, 783551873u, 3082640443u, 3233442989u, 3988292384u, 2596254646u, 62317068u, 1957810842u, 3939845945u, 2647816111u, 81470997u, 1943803523u, 3814918930u, 2489596804u, 225274430u, 2053790376u, 3826175755u, 2466906013u, 167816743u, 2097651377u, 4027552580u, 2265490386u, 503444072u, 1762050814u, 4150417245u, 2154129355u, 426522225u, 1852507879u, 4275313526u, 2312317920u, 282753626u, 1742555852u, 4189708143u, 2394877945u, 397917763u, 1622183637u, 3604390888u, 2714866558u, 953729732u, 1340076626u, 3518719985u, 2797360999u, 1068828381u, 1219638859u, 3624741850u, 2936675148u, 906185462u, 1090812512u, 3747672003u, 2825379669u, 829329135u, 1181335161u, 3412177804u, 3160834842u, 628085408u, 1382605366u, 3423369109u, 3138078467u, 570562233u, 1426400815u, 3317316542u, 2998733608u, 733239954u, 1555261956u, 3268935591u, 3050360625u, 752459403u, 1541320221u, 2607071920u, 3965973030u, 1969922972u, 40735498u, 2617837225u, 3943577151u, 1913087877u, 83908371u, 2512341634u, 3803740692u, 2075208622u, 213261112u, 2463272603u, 3855990285u, 2094854071u, 198958881u, 2262029012u, 4057260610u, 1759359992u, 534414190u, 2176718541u, 4139329115u, 1873836001u, 414664567u, 2282248934u, 4279200368u, 1711684554u, 285281116u, 2405801727u, 4167216745u, 1634467795u, 376229701u, 2685067896u, 3608007406u, 1308918612u, 956543938u, 2808555105u, 3495958263u, 1231636301u, 1047427035u, 2932959818u, 3654703836u, 1088359270u, 936918000u, 2847714899u, 3736837829u, 1202900863u, 817233897u, 3183342108u, 3401237130u, 1404277552u, 615818150u, 3134207493u, 3453421203u, 1423857449u, 601450431u, 3009837614u, 3294710456u, 1567103746u, 711928724u, 3020668471u, 3272380065u, 1510334235u, 755167117u};
static unsigned long CRC(const unsigned char *data, size_t size)
{
  unsigned int data_idx = 0;
  unsigned long result = 0xffffffffu;
  for (; size > 0; size -= 1)
  {
    result = crc32_table[(result ^ data[data_idx]) & 0xff] ^ (result >> 8);
    data_idx += 1;
  }

  return result ^ 0xffffffffu;
}

void ZopfliGzipCompress(const ZopfliOptions *options, const unsigned char *in, size_t insize, unsigned char **out, size_t *outsize)
{
  unsigned long crcvalue = CRC(in, insize);
  unsigned char bp = 0;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = 31;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = 139;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = 8;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = 0;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = 0;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = 0;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = 0;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = 0;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = 2;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = 3;
    *outsize += 1;
  }
  ;
  ZopfliDeflate(options, 2, 1, in, insize, &bp, out, outsize);
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = crcvalue % 256;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = (crcvalue >> 8) % 256;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = (crcvalue >> 16) % 256;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = (crcvalue >> 24) % 256;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = insize % 256;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = (insize >> 8) % 256;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = (insize >> 16) % 256;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = (insize >> 24) % 256;
    *outsize += 1;
  }
  ;
  if (options->verbose)
  {
    fprintf(stderr, "Original Size: %d, Gzip: %d, Compression: %f%% Removed\n", (int) insize, (int) (*outsize), (100.0 * ((double) (insize - (*outsize)))) / ((double) insize));
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
void ZopfliGzipCompress(const ZopfliOptions *options, const unsigned char *in, size_t insize, unsigned char **out, size_t *outsize);
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
static const unsigned long crc32_table[256] = {0u, 1996959894u, 3993919788u, 2567524794u, 124634137u, 1886057615u, 3915621685u, 2657392035u, 249268274u, 2044508324u, 3772115230u, 2547177864u, 162941995u, 2125561021u, 3887607047u, 2428444049u, 498536548u, 1789927666u, 4089016648u, 2227061214u, 450548861u, 1843258603u, 4107580753u, 2211677639u, 325883990u, 1684777152u, 4251122042u, 2321926636u, 335633487u, 1661365465u, 4195302755u, 2366115317u, 997073096u, 1281953886u, 3579855332u, 2724688242u, 1006888145u, 1258607687u, 3524101629u, 2768942443u, 901097722u, 1119000684u, 3686517206u, 2898065728u, 853044451u, 1172266101u, 3705015759u, 2882616665u, 651767980u, 1373503546u, 3369554304u, 3218104598u, 565507253u, 1454621731u, 3485111705u, 3099436303u, 671266974u, 1594198024u, 3322730930u, 2970347812u, 795835527u, 1483230225u, 3244367275u, 3060149565u, 1994146192u, 31158534u, 2563907772u, 4023717930u, 1907459465u, 112637215u, 2680153253u, 3904427059u, 2013776290u, 251722036u, 2517215374u, 3775830040u, 2137656763u, 141376813u, 2439277719u, 3865271297u, 1802195444u, 476864866u, 2238001368u, 4066508878u, 1812370925u, 453092731u, 2181625025u, 4111451223u, 1706088902u, 314042704u, 2344532202u, 4240017532u, 1658658271u, 366619977u, 2362670323u, 4224994405u, 1303535960u, 984961486u, 2747007092u, 3569037538u, 1256170817u, 1037604311u, 2765210733u, 3554079995u, 1131014506u, 879679996u, 2909243462u, 3663771856u, 1141124467u, 855842277u, 2852801631u, 3708648649u, 1342533948u, 654459306u, 3188396048u, 3373015174u, 1466479909u, 544179635u, 3110523913u, 3462522015u, 1591671054u, 702138776u, 2966460450u, 3352799412u, 1504918807u, 783551873u, 3082640443u, 3233442989u, 3988292384u, 2596254646u, 62317068u, 1957810842u, 3939845945u, 2647816111u, 81470997u, 1943803523u, 3814918930u, 2489596804u, 225274430u, 2053790376u, 3826175755u, 2466906013u, 167816743u, 2097651377u, 4027552580u, 2265490386u, 503444072u, 1762050814u, 4150417245u, 2154129355u, 426522225u, 1852507879u, 4275313526u, 2312317920u, 282753626u, 1742555852u, 4189708143u, 2394877945u, 397917763u, 1622183637u, 3604390888u, 2714866558u, 953729732u, 1340076626u, 3518719985u, 2797360999u, 1068828381u, 1219638859u, 3624741850u, 2936675148u, 906185462u, 1090812512u, 3747672003u, 2825379669u, 829329135u, 1181335161u, 3412177804u, 3160834842u, 628085408u, 1382605366u, 3423369109u, 3138078467u, 570562233u, 1426400815u, 3317316542u, 2998733608u, 733239954u, 1555261956u, 3268935591u, 3050360625u, 752459403u, 1541320221u, 2607071920u, 3965973030u, 1969922972u, 40735498u, 2617837225u, 3943577151u, 1913087877u, 83908371u, 2512341634u, 3803740692u, 2075208622u, 213261112u, 2463272603u, 3855990285u, 2094854071u, 198958881u, 2262029012u, 4057260610u, 1759359992u, 534414190u, 2176718541u, 4139329115u, 1873836001u, 414664567u, 2282248934u, 4279200368u, 1711684554u, 285281116u, 2405801727u, 4167216745u, 1634467795u, 376229701u, 2685067896u, 3608007406u, 1308918612u, 956543938u, 2808555105u, 3495958263u, 1231636301u, 1047427035u, 2932959818u, 3654703836u, 1088359270u, 936918000u, 2847714899u, 3736837829u, 1202900863u, 817233897u, 3183342108u, 3401237130u, 1404277552u, 615818150u, 3134207493u, 3453421203u, 1423857449u, 601450431u, 3009837614u, 3294710456u, 1567103746u, 711928724u, 3020668471u, 3272380065u, 1510334235u, 755167117u};
static unsigned long CRC(const unsigned char *data, size_t size)
{
  unsigned int data_idx = 0;
  unsigned long result = 0xffffffffu;
  for (; size > 0; size -= 1)
  {
    result = crc32_table[(result ^ data[data_idx]) & 0xff] ^ (result >> 8);
    data_idx += 1;
  }

  return result ^ 0xffffffffu;
}

void ZopfliGzipCompress(const ZopfliOptions *options, const unsigned char *in, size_t insize, unsigned char **out, size_t *outsize)
{
  unsigned long crcvalue = CRC(in, insize);
  unsigned char bp = 0;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = 31;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = 139;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = 8;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = 0;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = 0;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = 0;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = 0;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = 0;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = 2;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = 3;
    *outsize += 1;
  }
  ;
  ZopfliDeflate(options, 2, 1, in, insize, &bp, out, outsize);
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = crcvalue % 256;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = (crcvalue >> 8) % 256;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = (crcvalue >> 16) % 256;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = (crcvalue >> 24) % 256;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = insize % 256;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = (insize >> 8) % 256;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = (insize >> 16) % 256;
    *outsize += 1;
  }
  ;
  {
    if (!((*outsize) & ((*outsize) - 1)))
    {
      *out = ((*outsize) == 0) ? (malloc(sizeof(*(*out)))) : (realloc(*out, ((*outsize) * 2) * (sizeof(*(*out)))));
    }
    (*out)[*outsize] = (insize >> 24) % 256;
    *outsize += 1;
  }
  ;
  if (options->verbose)
  {
    fprintf(stderr, "Original Size: %d, Gzip: %d, Compression: %f%% Removed\n", (int) insize, (int) (*outsize), (100.0 * ((double) (insize - (*outsize)))) / ((double) insize));
  }
}

