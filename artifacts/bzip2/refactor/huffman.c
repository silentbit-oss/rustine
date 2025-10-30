#include <bzlib.h>
#include <bzlib_private.h>
#include <ctype.h>
#include <huffman.c>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
  char *next_in;
  unsigned int avail_in;
  unsigned int total_in_lo32;
  unsigned int total_in_hi32;
  char *next_out;
  unsigned int avail_out;
  unsigned int total_out_lo32;
  unsigned int total_out_hi32;
  void *state;
  void *(*bzalloc)(void *, int, int);
  void (*bzfree)(void *, void *);
  void *opaque;
} bz_stream;
extern int BZ2_bzCompressInit(bz_stream *strm, int blockSize100k, int verbosity, int workFactor);
extern int BZ2_bzCompress(bz_stream *strm, int action);
extern int BZ2_bzCompressEnd(bz_stream *strm);
extern int BZ2_bzDecompressInit(bz_stream *strm, int verbosity, int small);
extern int BZ2_bzDecompress(bz_stream *strm);
extern int BZ2_bzDecompressEnd(bz_stream *strm);
typedef void BZFILE;
extern BZFILE *BZ2_bzReadOpen(int *bzerror, FILE *f, int verbosity, int small, void *unused, int nUnused);
extern void BZ2_bzReadClose(int *bzerror, BZFILE *b);
extern void BZ2_bzReadGetUnused(int *bzerror, BZFILE *b, void **unused, int *nUnused);
extern int BZ2_bzRead(int *bzerror, BZFILE *b, void *buf, int len);
extern BZFILE *BZ2_bzWriteOpen(int *bzerror, FILE *f, int blockSize100k, int verbosity, int workFactor);
extern void BZ2_bzWrite(int *bzerror, BZFILE *b, void *buf, int len);
extern void BZ2_bzWriteClose(int *bzerror, BZFILE *b, int abandon, unsigned int *nbytes_in, unsigned int *nbytes_out);
extern void BZ2_bzWriteClose64(int *bzerror, BZFILE *b, int abandon, unsigned int *nbytes_in_lo32, unsigned int *nbytes_in_hi32, unsigned int *nbytes_out_lo32, unsigned int *nbytes_out_hi32);
extern int BZ2_bzBuffToBuffCompress(char *dest, unsigned int *destLen, char *source, unsigned int sourceLen, int blockSize100k, int verbosity, int workFactor);
extern int BZ2_bzBuffToBuffDecompress(char *dest, unsigned int *destLen, char *source, unsigned int sourceLen, int small, int verbosity);
extern const char *BZ2_bzlibVersion(void);
extern BZFILE *BZ2_bzopen(const char *path, const char *mode);
extern BZFILE *BZ2_bzdopen(int fd, const char *mode);
extern int BZ2_bzread(BZFILE *b, void *buf, int len);
extern int BZ2_bzwrite(BZFILE *b, void *buf, int len);
extern int BZ2_bzflush(BZFILE *b);
extern void BZ2_bzclose(BZFILE *b);
extern const char *BZ2_bzerror(BZFILE *b, int *errnum);
typedef char Char;
typedef unsigned char Bool;
typedef unsigned char UChar;
typedef int Int32;
typedef unsigned int UInt32;
typedef short Int16;
typedef unsigned short UInt16;
extern void BZ2_bz__AssertH__fail(int errcode);
extern Int32 BZ2_rNums[512];
extern UInt32 BZ2_crc32Table[256];
typedef struct 
{
  bz_stream *strm;
  Int32 mode;
  Int32 state;
  UInt32 avail_in_expect;
  UInt32 *arr1;
  UInt32 *arr2;
  UInt32 *ftab;
  Int32 origPtr;
  UInt32 *ptr;
  UChar *block;
  UInt16 *mtfv;
  UChar *zbits;
  Int32 workFactor;
  UInt32 state_in_ch;
  Int32 state_in_len;
  Int32 rNToGo;
  Int32 rTPos;
  Int32 nblock;
  Int32 nblockMAX;
  Int32 numZ;
  Int32 state_out_pos;
  Int32 nInUse;
  Bool inUse[256];
  UChar unseqToSeq[256];
  UInt32 bsBuff;
  Int32 bsLive;
  UInt32 blockCRC;
  UInt32 combinedCRC;
  Int32 verbosity;
  Int32 blockNo;
  Int32 blockSize100k;
  Int32 nMTF;
  Int32 mtfFreq[258];
  UChar selector[2 + (900000 / 50)];
  UChar selectorMtf[2 + (900000 / 50)];
  UChar len[6][258];
  Int32 code[6][258];
  Int32 rfreq[6][258];
  UInt32 len_pack[258][4];
} EState;
extern void BZ2_blockSort(EState *);
extern void BZ2_compressBlock(EState *, Bool);
extern void BZ2_bsInitWrite(EState *);
extern void BZ2_hbAssignCodes(Int32 *, UChar *, Int32, Int32, Int32);
extern void BZ2_hbMakeCodeLengths(UChar *, Int32 *, Int32, Int32);
typedef struct 
{
  bz_stream *strm;
  Int32 state;
  UChar state_out_ch;
  Int32 state_out_len;
  Bool blockRandomised;
  Int32 rNToGo;
  Int32 rTPos;
  UInt32 bsBuff;
  Int32 bsLive;
  Int32 blockSize100k;
  Bool smallDecompress;
  Int32 currBlockNo;
  Int32 verbosity;
  Int32 origPtr;
  UInt32 tPos;
  Int32 k0;
  Int32 unzftab[256];
  Int32 nblock_used;
  Int32 cftab[257];
  Int32 cftabCopy[257];
  UInt32 *tt;
  UInt16 *ll16;
  UChar *ll4;
  UInt32 storedBlockCRC;
  UInt32 storedCombinedCRC;
  UInt32 calculatedBlockCRC;
  UInt32 calculatedCombinedCRC;
  Int32 nInUse;
  Bool inUse[256];
  Bool inUse16[16];
  UChar seqToUnseq[256];
  UChar mtfa[4096];
  Int32 mtfbase[256 / 16];
  UChar selector[2 + (900000 / 50)];
  UChar selectorMtf[2 + (900000 / 50)];
  UChar len[6][258];
  Int32 limit[6][258];
  Int32 base[6][258];
  Int32 perm[6][258];
  Int32 minLens[6];
  Int32 save_i;
  Int32 save_j;
  Int32 save_t;
  Int32 save_alphaSize;
  Int32 save_nGroups;
  Int32 save_nSelectors;
  Int32 save_EOB;
  Int32 save_groupNo;
  Int32 save_groupPos;
  Int32 save_nextSym;
  Int32 save_nblockMAX;
  Int32 save_nblock;
  Int32 save_es;
  Int32 save_N;
  Int32 save_curr;
  Int32 save_zt;
  Int32 save_zn;
  Int32 save_zvec;
  Int32 save_zj;
  Int32 save_gSel;
  Int32 save_gMinlen;
  Int32 *save_gLimit;
  Int32 *save_gBase;
  Int32 *save_gPerm;
} DState;
extern Int32 BZ2_indexIntoF(Int32, Int32 *);
extern Int32 BZ2_decompress(DState *);
extern void BZ2_hbCreateDecodeTables(Int32 *, Int32 *, Int32 *, UChar *, Int32, Int32, Int32);
void BZ2_hbMakeCodeLengths(UChar *len, Int32 *freq, Int32 alphaSize, Int32 maxLen)
{
  Int32 nNodes;
  Int32 nHeap;
  Int32 n1;
  Int32 n2;
  Int32 i;
  Int32 j;
  Int32 k;
  Bool tooLong;
  Int32 heap[258 + 2];
  Int32 weight[258 * 2];
  Int32 parent[258 * 2];
  for (i = 0; i < alphaSize; i += 1)
  {
    weight[i + 1] = ((freq[i] == 0) ? (1) : (freq[i])) << 8;
  }

  while ((Bool) 1)
  {
    nNodes = alphaSize;
    nHeap = 0;
    heap[0] = 0;
    weight[0] = 0;
    parent[0] = -2;
    for (i = 1; i <= alphaSize; i += 1)
    {
      parent[i] = -1;
      nHeap += 1;
      heap[nHeap] = i;
      {
        Int32 zz;
        Int32 tmp;
        zz = nHeap;
        tmp = heap[zz];
        while (weight[tmp] < weight[heap[zz >> 1]])
        {
          heap[zz] = heap[zz >> 1];
          zz >>= 1;
        }

        heap[zz] = tmp;
      }
      ;
    }

    {
      if (!(nHeap < (258 + 2)))
      {
        BZ2_bz__AssertH__fail(2001);
      }
    }
    ;
    while (nHeap > 1)
    {
      n1 = heap[1];
      heap[1] = heap[nHeap];
      nHeap -= 1;
      {
        Int32 zz;
        Int32 yy;
        Int32 tmp;
        zz = 1;
        tmp = heap[zz];
        while ((Bool) 1)
        {
          yy = zz << 1;
          if (yy > nHeap)
          {
            break;
          }
          if ((yy < nHeap) && (weight[heap[yy + 1]] < weight[heap[yy]]))
          {
            yy += 1;
          }
          if (weight[tmp] < weight[heap[yy]])
          {
            break;
          }
          heap[zz] = heap[yy];
          zz = yy;
        }

        heap[zz] = tmp;
      }
      ;
      n2 = heap[1];
      heap[1] = heap[nHeap];
      nHeap -= 1;
      {
        Int32 zz;
        Int32 yy;
        Int32 tmp;
        zz = 1;
        tmp = heap[zz];
        while ((Bool) 1)
        {
          yy = zz << 1;
          if (yy > nHeap)
          {
            break;
          }
          if ((yy < nHeap) && (weight[heap[yy + 1]] < weight[heap[yy]]))
          {
            yy += 1;
          }
          if (weight[tmp] < weight[heap[yy]])
          {
            break;
          }
          heap[zz] = heap[yy];
          zz = yy;
        }

        heap[zz] = tmp;
      }
      ;
      nNodes += 1;
      parent[n1] = (parent[n2] = nNodes);
      weight[nNodes] = ((weight[n1] & 0xffffff00) + (weight[n2] & 0xffffff00)) | (1 + (((weight[n1] & 0x000000ff) > (weight[n2] & 0x000000ff)) ? (weight[n1] & 0x000000ff) : (weight[n2] & 0x000000ff)));
      parent[nNodes] = -1;
      nHeap += 1;
      heap[nHeap] = nNodes;
      {
        Int32 zz;
        Int32 tmp;
        zz = nHeap;
        tmp = heap[zz];
        while (weight[tmp] < weight[heap[zz >> 1]])
        {
          heap[zz] = heap[zz >> 1];
          zz >>= 1;
        }

        heap[zz] = tmp;
      }
      ;
    }

    {
      if (!(nNodes < (258 * 2)))
      {
        BZ2_bz__AssertH__fail(2002);
      }
    }
    ;
    tooLong = (Bool) 0;
    for (i = 1; i <= alphaSize; i += 1)
    {
      j = 0;
      k = i;
      while (parent[k] >= 0)
      {
        k = parent[k];
        j += 1;
      }

      len[i - 1] = j;
      if (j > maxLen)
      {
        tooLong = (Bool) 1;
      }
    }

    if (!tooLong)
    {
      break;
    }
    for (i = 1; i <= alphaSize; i += 1)
    {
      j = weight[i] >> 8;
      j = 1 + (j / 2);
      weight[i] = j << 8;
    }

  }

}

void BZ2_hbAssignCodes(Int32 *code, UChar *length, Int32 minLen, Int32 maxLen, Int32 alphaSize)
{
  Int32 n;
  Int32 vec;
  Int32 i;
  vec = 0;
  for (n = minLen; n <= maxLen; n += 1)
  {
    for (i = 0; i < alphaSize; i += 1)
    {
      if (length[i] == n)
      {
        code[i] = vec;
        vec += 1;
      }
    }

    ;
    vec <<= 1;
  }

}

void BZ2_hbCreateDecodeTables(Int32 *limit, Int32 *base, Int32 *perm, UChar *length, Int32 minLen, Int32 maxLen, Int32 alphaSize)
{
  Int32 pp;
  Int32 i;
  Int32 j;
  Int32 vec;
  pp = 0;
  for (i = minLen; i <= maxLen; i += 1)
  {
    for (j = 0; j < alphaSize; j += 1)
    {
      if (length[j] == i)
      {
        perm[pp] = j;
        pp += 1;
      }
    }

  }

  ;
  for (i = 0; i < 23; i += 1)
  {
    base[i] = 0;
  }

  for (i = 0; i < alphaSize; i += 1)
  {
    base[length[i] + 1] += 1;
  }

  for (i = 1; i < 23; i += 1)
  {
    base[i] += base[i - 1];
  }

  for (i = 0; i < 23; i += 1)
  {
    limit[i] = 0;
  }

  vec = 0;
  for (i = minLen; i <= maxLen; i += 1)
  {
    vec += base[i + 1] - base[i];
    limit[i] = vec - 1;
    vec <<= 1;
  }

  for (i = minLen + 1; i <= maxLen; i += 1)
  {
    base[i] = ((limit[i - 1] + 1) << 1) - base[i];
  }

}


typedef struct 
{
  char *next_in;
  unsigned int avail_in;
  unsigned int total_in_lo32;
  unsigned int total_in_hi32;
  char *next_out;
  unsigned int avail_out;
  unsigned int total_out_lo32;
  unsigned int total_out_hi32;
  void *state;
  void *(*bzalloc)(void *, int, int);
  void (*bzfree)(void *, void *);
  void *opaque;
} bz_stream;
extern int BZ2_bzCompressInit(bz_stream *strm, int blockSize100k, int verbosity, int workFactor);
extern int BZ2_bzCompress(bz_stream *strm, int action);
extern int BZ2_bzCompressEnd(bz_stream *strm);
extern int BZ2_bzDecompressInit(bz_stream *strm, int verbosity, int small);
extern int BZ2_bzDecompress(bz_stream *strm);
extern int BZ2_bzDecompressEnd(bz_stream *strm);
typedef void BZFILE;
extern BZFILE *BZ2_bzReadOpen(int *bzerror, FILE *f, int verbosity, int small, void *unused, int nUnused);
extern void BZ2_bzReadClose(int *bzerror, BZFILE *b);
extern void BZ2_bzReadGetUnused(int *bzerror, BZFILE *b, void **unused, int *nUnused);
extern int BZ2_bzRead(int *bzerror, BZFILE *b, void *buf, int len);
extern BZFILE *BZ2_bzWriteOpen(int *bzerror, FILE *f, int blockSize100k, int verbosity, int workFactor);
extern void BZ2_bzWrite(int *bzerror, BZFILE *b, void *buf, int len);
extern void BZ2_bzWriteClose(int *bzerror, BZFILE *b, int abandon, unsigned int *nbytes_in, unsigned int *nbytes_out);
extern void BZ2_bzWriteClose64(int *bzerror, BZFILE *b, int abandon, unsigned int *nbytes_in_lo32, unsigned int *nbytes_in_hi32, unsigned int *nbytes_out_lo32, unsigned int *nbytes_out_hi32);
extern int BZ2_bzBuffToBuffCompress(char *dest, unsigned int *destLen, char *source, unsigned int sourceLen, int blockSize100k, int verbosity, int workFactor);
extern int BZ2_bzBuffToBuffDecompress(char *dest, unsigned int *destLen, char *source, unsigned int sourceLen, int small, int verbosity);
extern const char *BZ2_bzlibVersion(void);
extern BZFILE *BZ2_bzopen(const char *path, const char *mode);
extern BZFILE *BZ2_bzdopen(int fd, const char *mode);
extern int BZ2_bzread(BZFILE *b, void *buf, int len);
extern int BZ2_bzwrite(BZFILE *b, void *buf, int len);
extern int BZ2_bzflush(BZFILE *b);
extern void BZ2_bzclose(BZFILE *b);
extern const char *BZ2_bzerror(BZFILE *b, int *errnum);
typedef char Char;
typedef unsigned char Bool;
typedef unsigned char UChar;
typedef int Int32;
typedef unsigned int UInt32;
typedef short Int16;
typedef unsigned short UInt16;
extern void BZ2_bz__AssertH__fail(int errcode);
extern Int32 BZ2_rNums[512];
extern UInt32 BZ2_crc32Table[256];
typedef struct 
{
  bz_stream *strm;
  Int32 mode;
  Int32 state;
  UInt32 avail_in_expect;
  UInt32 *arr1;
  UInt32 *arr2;
  UInt32 *ftab;
  Int32 origPtr;
  UInt32 *ptr;
  UChar *block;
  UInt16 *mtfv;
  UChar *zbits;
  Int32 workFactor;
  UInt32 state_in_ch;
  Int32 state_in_len;
  Int32 rNToGo;
  Int32 rTPos;
  Int32 nblock;
  Int32 nblockMAX;
  Int32 numZ;
  Int32 state_out_pos;
  Int32 nInUse;
  Bool inUse[256];
  UChar unseqToSeq[256];
  UInt32 bsBuff;
  Int32 bsLive;
  UInt32 blockCRC;
  UInt32 combinedCRC;
  Int32 verbosity;
  Int32 blockNo;
  Int32 blockSize100k;
  Int32 nMTF;
  Int32 mtfFreq[258];
  UChar selector[2 + (900000 / 50)];
  UChar selectorMtf[2 + (900000 / 50)];
  UChar len[6][258];
  Int32 code[6][258];
  Int32 rfreq[6][258];
  UInt32 len_pack[258][4];
} EState;
extern void BZ2_blockSort(EState *);
extern void BZ2_compressBlock(EState *, Bool);
extern void BZ2_bsInitWrite(EState *);
extern void BZ2_hbAssignCodes(Int32 *, UChar *, Int32, Int32, Int32);
extern void BZ2_hbMakeCodeLengths(UChar *, Int32 *, Int32, Int32);
typedef struct 
{
  bz_stream *strm;
  Int32 state;
  UChar state_out_ch;
  Int32 state_out_len;
  Bool blockRandomised;
  Int32 rNToGo;
  Int32 rTPos;
  UInt32 bsBuff;
  Int32 bsLive;
  Int32 blockSize100k;
  Bool smallDecompress;
  Int32 currBlockNo;
  Int32 verbosity;
  Int32 origPtr;
  UInt32 tPos;
  Int32 k0;
  Int32 unzftab[256];
  Int32 nblock_used;
  Int32 cftab[257];
  Int32 cftabCopy[257];
  UInt32 *tt;
  UInt16 *ll16;
  UChar *ll4;
  UInt32 storedBlockCRC;
  UInt32 storedCombinedCRC;
  UInt32 calculatedBlockCRC;
  UInt32 calculatedCombinedCRC;
  Int32 nInUse;
  Bool inUse[256];
  Bool inUse16[16];
  UChar seqToUnseq[256];
  UChar mtfa[4096];
  Int32 mtfbase[256 / 16];
  UChar selector[2 + (900000 / 50)];
  UChar selectorMtf[2 + (900000 / 50)];
  UChar len[6][258];
  Int32 limit[6][258];
  Int32 base[6][258];
  Int32 perm[6][258];
  Int32 minLens[6];
  Int32 save_i;
  Int32 save_j;
  Int32 save_t;
  Int32 save_alphaSize;
  Int32 save_nGroups;
  Int32 save_nSelectors;
  Int32 save_EOB;
  Int32 save_groupNo;
  Int32 save_groupPos;
  Int32 save_nextSym;
  Int32 save_nblockMAX;
  Int32 save_nblock;
  Int32 save_es;
  Int32 save_N;
  Int32 save_curr;
  Int32 save_zt;
  Int32 save_zn;
  Int32 save_zvec;
  Int32 save_zj;
  Int32 save_gSel;
  Int32 save_gMinlen;
  Int32 *save_gLimit;
  Int32 *save_gBase;
  Int32 *save_gPerm;
} DState;
extern Int32 BZ2_indexIntoF(Int32, Int32 *);
extern Int32 BZ2_decompress(DState *);
extern void BZ2_hbCreateDecodeTables(Int32 *, Int32 *, Int32 *, UChar *, Int32, Int32, Int32);
void BZ2_hbMakeCodeLengths(UChar *len, Int32 *freq, Int32 alphaSize, Int32 maxLen)
{
  Int32 nNodes;
  Int32 nHeap;
  Int32 n1;
  Int32 n2;
  Int32 i;
  Int32 j;
  Int32 k;
  Bool tooLong;
  Int32 heap[258 + 2];
  Int32 weight[258 * 2];
  Int32 parent[258 * 2];
  for (i = 0; i < alphaSize; i += 1)
  {
    weight[i + 1] = ((freq[i] == 0) ? (1) : (freq[i])) << 8;
  }

  while ((Bool) 1)
  {
    nNodes = alphaSize;
    nHeap = 0;
    heap[0] = 0;
    weight[0] = 0;
    parent[0] = -2;
    for (i = 1; i <= alphaSize; i += 1)
    {
      parent[i] = -1;
      nHeap += 1;
      heap[nHeap] = i;
      {
        Int32 zz;
        Int32 tmp;
        zz = nHeap;
        tmp = heap[zz];
        while (weight[tmp] < weight[heap[zz >> 1]])
        {
          heap[zz] = heap[zz >> 1];
          zz >>= 1;
        }

        heap[zz] = tmp;
      }
      ;
    }

    {
      if (!(nHeap < (258 + 2)))
      {
        BZ2_bz__AssertH__fail(2001);
      }
    }
    ;
    while (nHeap > 1)
    {
      n1 = heap[1];
      heap[1] = heap[nHeap];
      nHeap -= 1;
      {
        Int32 zz;
        Int32 yy;
        Int32 tmp;
        zz = 1;
        tmp = heap[zz];
        while ((Bool) 1)
        {
          yy = zz << 1;
          if (yy > nHeap)
          {
            break;
          }
          if ((yy < nHeap) && (weight[heap[yy + 1]] < weight[heap[yy]]))
          {
            yy += 1;
          }
          if (weight[tmp] < weight[heap[yy]])
          {
            break;
          }
          heap[zz] = heap[yy];
          zz = yy;
        }

        heap[zz] = tmp;
      }
      ;
      n2 = heap[1];
      heap[1] = heap[nHeap];
      nHeap -= 1;
      {
        Int32 zz;
        Int32 yy;
        Int32 tmp;
        zz = 1;
        tmp = heap[zz];
        while ((Bool) 1)
        {
          yy = zz << 1;
          if (yy > nHeap)
          {
            break;
          }
          if ((yy < nHeap) && (weight[heap[yy + 1]] < weight[heap[yy]]))
          {
            yy += 1;
          }
          if (weight[tmp] < weight[heap[yy]])
          {
            break;
          }
          heap[zz] = heap[yy];
          zz = yy;
        }

        heap[zz] = tmp;
      }
      ;
      nNodes += 1;
      parent[n1] = (parent[n2] = nNodes);
      weight[nNodes] = ((weight[n1] & 0xffffff00) + (weight[n2] & 0xffffff00)) | (1 + (((weight[n1] & 0x000000ff) > (weight[n2] & 0x000000ff)) ? (weight[n1] & 0x000000ff) : (weight[n2] & 0x000000ff)));
      parent[nNodes] = -1;
      nHeap += 1;
      heap[nHeap] = nNodes;
      {
        Int32 zz;
        Int32 tmp;
        zz = nHeap;
        tmp = heap[zz];
        while (weight[tmp] < weight[heap[zz >> 1]])
        {
          heap[zz] = heap[zz >> 1];
          zz >>= 1;
        }

        heap[zz] = tmp;
      }
      ;
    }

    {
      if (!(nNodes < (258 * 2)))
      {
        BZ2_bz__AssertH__fail(2002);
      }
    }
    ;
    tooLong = (Bool) 0;
    for (i = 1; i <= alphaSize; i += 1)
    {
      j = 0;
      k = i;
      while (parent[k] >= 0)
      {
        k = parent[k];
        j += 1;
      }

      len[i - 1] = j;
      if (j > maxLen)
      {
        tooLong = (Bool) 1;
      }
    }

    if (!tooLong)
    {
      break;
    }
    for (i = 1; i <= alphaSize; i += 1)
    {
      j = weight[i] >> 8;
      j = 1 + (j / 2);
      weight[i] = j << 8;
    }

  }

}

void BZ2_hbAssignCodes(Int32 *code, UChar *length, Int32 minLen, Int32 maxLen, Int32 alphaSize)
{
  Int32 n;
  Int32 vec;
  Int32 i;
  vec = 0;
  for (n = minLen; n <= maxLen; n += 1)
  {
    for (i = 0; i < alphaSize; i += 1)
    {
      if (length[i] == n)
      {
        code[i] = vec;
        vec += 1;
      }
    }

    ;
    vec <<= 1;
  }

}

void BZ2_hbCreateDecodeTables(Int32 *limit, Int32 *base, Int32 *perm, UChar *length, Int32 minLen, Int32 maxLen, Int32 alphaSize)
{
  Int32 pp;
  Int32 i;
  Int32 j;
  Int32 vec;
  pp = 0;
  for (i = minLen; i <= maxLen; i += 1)
  {
    for (j = 0; j < alphaSize; j += 1)
    {
      if (length[j] == i)
      {
        perm[pp] = j;
        pp += 1;
      }
    }

  }

  ;
  for (i = 0; i < 23; i += 1)
  {
    base[i] = 0;
  }

  for (i = 0; i < alphaSize; i += 1)
  {
    base[length[i] + 1] += 1;
  }

  for (i = 1; i < 23; i += 1)
  {
    base[i] += base[i - 1];
  }

  for (i = 0; i < 23; i += 1)
  {
    limit[i] = 0;
  }

  vec = 0;
  for (i = minLen; i <= maxLen; i += 1)
  {
    vec += base[i + 1] - base[i];
    limit[i] = vec - 1;
    vec <<= 1;
  }

  for (i = minLen + 1; i <= maxLen; i += 1)
  {
    base[i] = ((limit[i - 1] + 1) << 1) - base[i];
  }

}

