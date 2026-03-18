#include <bzlib.h>
#include <bzlib_private.h>
#include <compress.c>
#include <ctype.h>
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
void BZ2_bsInitWrite(EState *s)
{
  s->bsLive = 0;
  s->bsBuff = 0;
}

static void bsFinishWrite(EState *s)
{
  while (s->bsLive > 0)
  {
    s->zbits[s->numZ] = (UChar) (s->bsBuff >> 24);
    s->numZ += 1;
    s->bsBuff <<= 8;
    s->bsLive -= 8;
  }

}

static void bsW(EState *s, Int32 n, UInt32 v)
{
  {
    while (s->bsLive >= 8)
    {
      s->zbits[s->numZ] = (UChar) (s->bsBuff >> 24);
      s->numZ += 1;
      s->bsBuff <<= 8;
      s->bsLive -= 8;
    }

  }
  ;
  s->bsBuff |= v << ((32 - s->bsLive) - n);
  s->bsLive += n;
}

static void bsPutUInt32(EState *s, UInt32 u)
{
  bsW(s, 8, (u >> 24) & 0xffL);
  bsW(s, 8, (u >> 16) & 0xffL);
  bsW(s, 8, (u >> 8) & 0xffL);
  bsW(s, 8, u & 0xffL);
}

static void bsPutUChar(EState *s, UChar c)
{
  bsW(s, 8, (UInt32) c);
}

static void makeMaps_e(EState *s)
{
  Int32 i;
  s->nInUse = 0;
  for (i = 0; i < 256; i += 1)
  {
    if (s->inUse[i])
    {
      s->unseqToSeq[i] = s->nInUse;
      s->nInUse += 1;
    }
  }

}

static void generateMTFValues(EState *s)
{
  UChar yy[256];
  Int32 i;
  Int32 j;
  Int32 zPend;
  Int32 wr;
  Int32 EOB;
  UInt32 *ptr = s->ptr;
  UChar *block = s->block;
  UInt16 *mtfv = s->mtfv;
  makeMaps_e(s);
  EOB = s->nInUse + 1;
  for (i = 0; i <= EOB; i += 1)
  {
    s->mtfFreq[i] = 0;
  }

  wr = 0;
  zPend = 0;
  for (i = 0; i < s->nInUse; i += 1)
  {
    yy[i] = (UChar) i;
  }

  for (i = 0; i < s->nblock; i += 1)
  {
    UChar ll_i;
    ;
    j = ptr[i] - 1;
    if (j < 0)
    {
      j += s->nblock;
    }
    ll_i = s->unseqToSeq[block[j]];
    ;
    if (yy[0] == ll_i)
    {
      zPend += 1;
    }
    else
    {
      if (zPend > 0)
      {
        zPend -= 1;
        while ((Bool) 1)
        {
          if (zPend & 1)
          {
            mtfv[wr] = 1;
            wr += 1;
            s->mtfFreq[1] += 1;
          }
          else
          {
            mtfv[wr] = 0;
            wr += 1;
            s->mtfFreq[0] += 1;
          }
          if (zPend < 2)
          {
            break;
          }
          zPend = (zPend - 2) / 2;
        }

        ;
        zPend = 0;
      }
      {
        register UChar rtmp;
        register UChar *ryy_j;
        unsigned int ryy_j_idx = 0;
        register UChar rll_i;
        rtmp = yy[1];
        yy[1] = yy[0];
        ryy_j_idx = &yy[1];
        rll_i = ll_i;
        while (rll_i != rtmp)
        {
          register UChar rtmp2;
          ryy_j_idx += 1;
          rtmp2 = rtmp;
          rtmp = ryy_j[ryy_j_idx];
          ryy_j[ryy_j_idx] = rtmp2;
        }

        ;
        yy[0] = rtmp;
        j = (&ryy_j[ryy_j_idx]) - (&yy[0]);
        mtfv[wr] = j + 1;
        wr += 1;
        s->mtfFreq[j + 1] += 1;
      }
    }
  }

  if (zPend > 0)
  {
    zPend -= 1;
    while ((Bool) 1)
    {
      if (zPend & 1)
      {
        mtfv[wr] = 1;
        wr += 1;
        s->mtfFreq[1] += 1;
      }
      else
      {
        mtfv[wr] = 0;
        wr += 1;
        s->mtfFreq[0] += 1;
      }
      if (zPend < 2)
      {
        break;
      }
      zPend = (zPend - 2) / 2;
    }

    ;
    zPend = 0;
  }
  mtfv[wr] = EOB;
  wr += 1;
  s->mtfFreq[EOB] += 1;
  s->nMTF = wr;
}

static void sendMTFValues(EState *s)
{
  Int32 v;
  Int32 t;
  Int32 i;
  Int32 j;
  Int32 gs;
  Int32 ge;
  Int32 totc;
  Int32 bt;
  Int32 bc;
  Int32 iter;
  Int32 nSelectors;
  Int32 alphaSize;
  Int32 minLen;
  Int32 maxLen;
  Int32 selCtr;
  Int32 nGroups;
  Int32 nBytes;
  UInt16 cost[6];
  Int32 fave[6];
  UInt16 *mtfv = s->mtfv;
  if (s->verbosity >= 3)
  {
    fprintf(stderr, "      %d in block, %d after MTF & 1-2 coding, %d+2 syms in use\n", s->nblock, s->nMTF, s->nInUse);
  }
  alphaSize = s->nInUse + 2;
  for (t = 0; t < 6; t += 1)
  {
    for (v = 0; v < alphaSize; v += 1)
    {
      s->len[t][v] = 15;
    }

  }

  {
    if (!(s->nMTF > 0))
    {
      BZ2_bz__AssertH__fail(3001);
    }
  }
  ;
  if (s->nMTF < 200)
  {
    nGroups = 2;
  }
  else
    if (s->nMTF < 600)
  {
    nGroups = 3;
  }
  else
    if (s->nMTF < 1200)
  {
    nGroups = 4;
  }
  else
    if (s->nMTF < 2400)
  {
    nGroups = 5;
  }
  else
    nGroups = 6;
  {
    Int32 nPart;
    Int32 remF;
    Int32 tFreq;
    Int32 aFreq;
    nPart = nGroups;
    remF = s->nMTF;
    gs = 0;
    while (nPart > 0)
    {
      tFreq = remF / nPart;
      ge = gs - 1;
      aFreq = 0;
      while ((aFreq < tFreq) && (ge < (alphaSize - 1)))
      {
        ge += 1;
        aFreq += s->mtfFreq[ge];
      }

      if ((((ge > gs) && (nPart != nGroups)) && (nPart != 1)) && (((nGroups - nPart) % 2) == 1))
      {
        aFreq -= s->mtfFreq[ge];
        ge -= 1;
      }
      if (s->verbosity >= 3)
      {
        fprintf(stderr, "      initial group %d, [%d .. %d], has %d syms (%4.1f%%)\n", nPart, gs, ge, aFreq, (100.0 * ((float) aFreq)) / ((float) s->nMTF));
      }
      for (v = 0; v < alphaSize; v += 1)
      {
        if ((v >= gs) && (v <= ge))
        {
          s->len[nPart - 1][v] = 0;
        }
        else
          s->len[nPart - 1][v] = 15;
      }

      nPart -= 1;
      gs = ge + 1;
      remF -= aFreq;
    }

  }
  for (iter = 0; iter < 4; iter += 1)
  {
    for (t = 0; t < nGroups; t += 1)
    {
      fave[t] = 0;
    }

    for (t = 0; t < nGroups; t += 1)
    {
      for (v = 0; v < alphaSize; v += 1)
      {
        s->rfreq[t][v] = 0;
      }

    }

    if (nGroups == 6)
    {
      for (v = 0; v < alphaSize; v += 1)
      {
        s->len_pack[v][0] = (s->len[1][v] << 16) | s->len[0][v];
        s->len_pack[v][1] = (s->len[3][v] << 16) | s->len[2][v];
        s->len_pack[v][2] = (s->len[5][v] << 16) | s->len[4][v];
      }

    }
    nSelectors = 0;
    totc = 0;
    gs = 0;
    while ((Bool) 1)
    {
      if (gs >= s->nMTF)
      {
        break;
      }
      ge = (gs + 50) - 1;
      if (ge >= s->nMTF)
      {
        ge = s->nMTF - 1;
      }
      for (t = 0; t < nGroups; t += 1)
      {
        cost[t] = 0;
      }

      if ((nGroups == 6) && (50 == ((ge - gs) + 1)))
      {
        register UInt32 cost01;
        register UInt32 cost23;
        register UInt32 cost45;
        register UInt16 icv;
        cost01 = (cost23 = (cost45 = 0));
        icv = mtfv[gs + 0];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 1];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 2];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 3];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 4];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 5];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 6];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 7];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 8];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 9];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 10];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 11];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 12];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 13];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 14];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 15];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 16];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 17];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 18];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 19];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 20];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 21];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 22];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 23];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 24];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 25];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 26];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 27];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 28];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 29];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 30];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 31];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 32];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 33];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 34];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 35];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 36];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 37];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 38];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 39];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 40];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 41];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 42];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 43];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 44];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 45];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 46];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 47];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 48];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 49];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        cost[0] = cost01 & 0xffff;
        cost[1] = cost01 >> 16;
        cost[2] = cost23 & 0xffff;
        cost[3] = cost23 >> 16;
        cost[4] = cost45 & 0xffff;
        cost[5] = cost45 >> 16;
      }
      else
      {
        for (i = gs; i <= ge; i += 1)
        {
          UInt16 icv = mtfv[i];
          for (t = 0; t < nGroups; t += 1)
          {
            cost[t] += s->len[t][icv];
          }

        }

      }
      bc = 999999999;
      bt = -1;
      for (t = 0; t < nGroups; t += 1)
      {
        if (cost[t] < bc)
        {
          bc = cost[t];
          bt = t;
        }
      }

      ;
      totc += bc;
      fave[bt] += 1;
      s->selector[nSelectors] = bt;
      nSelectors += 1;
      if ((nGroups == 6) && (50 == ((ge - gs) + 1)))
      {
        s->rfreq[bt][mtfv[gs + 0]] += 1;
        s->rfreq[bt][mtfv[gs + 1]] += 1;
        s->rfreq[bt][mtfv[gs + 2]] += 1;
        s->rfreq[bt][mtfv[gs + 3]] += 1;
        s->rfreq[bt][mtfv[gs + 4]] += 1;
        s->rfreq[bt][mtfv[gs + 5]] += 1;
        s->rfreq[bt][mtfv[gs + 6]] += 1;
        s->rfreq[bt][mtfv[gs + 7]] += 1;
        s->rfreq[bt][mtfv[gs + 8]] += 1;
        s->rfreq[bt][mtfv[gs + 9]] += 1;
        s->rfreq[bt][mtfv[gs + 10]] += 1;
        s->rfreq[bt][mtfv[gs + 11]] += 1;
        s->rfreq[bt][mtfv[gs + 12]] += 1;
        s->rfreq[bt][mtfv[gs + 13]] += 1;
        s->rfreq[bt][mtfv[gs + 14]] += 1;
        s->rfreq[bt][mtfv[gs + 15]] += 1;
        s->rfreq[bt][mtfv[gs + 16]] += 1;
        s->rfreq[bt][mtfv[gs + 17]] += 1;
        s->rfreq[bt][mtfv[gs + 18]] += 1;
        s->rfreq[bt][mtfv[gs + 19]] += 1;
        s->rfreq[bt][mtfv[gs + 20]] += 1;
        s->rfreq[bt][mtfv[gs + 21]] += 1;
        s->rfreq[bt][mtfv[gs + 22]] += 1;
        s->rfreq[bt][mtfv[gs + 23]] += 1;
        s->rfreq[bt][mtfv[gs + 24]] += 1;
        s->rfreq[bt][mtfv[gs + 25]] += 1;
        s->rfreq[bt][mtfv[gs + 26]] += 1;
        s->rfreq[bt][mtfv[gs + 27]] += 1;
        s->rfreq[bt][mtfv[gs + 28]] += 1;
        s->rfreq[bt][mtfv[gs + 29]] += 1;
        s->rfreq[bt][mtfv[gs + 30]] += 1;
        s->rfreq[bt][mtfv[gs + 31]] += 1;
        s->rfreq[bt][mtfv[gs + 32]] += 1;
        s->rfreq[bt][mtfv[gs + 33]] += 1;
        s->rfreq[bt][mtfv[gs + 34]] += 1;
        s->rfreq[bt][mtfv[gs + 35]] += 1;
        s->rfreq[bt][mtfv[gs + 36]] += 1;
        s->rfreq[bt][mtfv[gs + 37]] += 1;
        s->rfreq[bt][mtfv[gs + 38]] += 1;
        s->rfreq[bt][mtfv[gs + 39]] += 1;
        s->rfreq[bt][mtfv[gs + 40]] += 1;
        s->rfreq[bt][mtfv[gs + 41]] += 1;
        s->rfreq[bt][mtfv[gs + 42]] += 1;
        s->rfreq[bt][mtfv[gs + 43]] += 1;
        s->rfreq[bt][mtfv[gs + 44]] += 1;
        s->rfreq[bt][mtfv[gs + 45]] += 1;
        s->rfreq[bt][mtfv[gs + 46]] += 1;
        s->rfreq[bt][mtfv[gs + 47]] += 1;
        s->rfreq[bt][mtfv[gs + 48]] += 1;
        s->rfreq[bt][mtfv[gs + 49]] += 1;
      }
      else
      {
        for (i = gs; i <= ge; i += 1)
        {
          s->rfreq[bt][mtfv[i]] += 1;
        }

      }
      gs = ge + 1;
    }

    if (s->verbosity >= 3)
    {
      fprintf(stderr, "      pass %d: size is %d, grp uses are ", iter + 1, totc / 8);
      for (t = 0; t < nGroups; t += 1)
      {
        fprintf(stderr, "%d ", fave[t]);
      }

      fprintf(stderr, "\n");
    }
    for (t = 0; t < nGroups; t += 1)
    {
      BZ2_hbMakeCodeLengths(&s->len[t][0], &s->rfreq[t][0], alphaSize, 17);
    }

  }

  {
    if (!(nGroups < 8))
    {
      BZ2_bz__AssertH__fail(3002);
    }
  }
  ;
  {
    if (!((nSelectors < 32768) && (nSelectors <= (2 + (900000 / 50)))))
    {
      BZ2_bz__AssertH__fail(3003);
    }
  }
  ;
  {
    UChar pos[6];
    UChar ll_i;
    UChar tmp2;
    UChar tmp;
    for (i = 0; i < nGroups; i += 1)
    {
      pos[i] = i;
    }

    for (i = 0; i < nSelectors; i += 1)
    {
      ll_i = s->selector[i];
      j = 0;
      tmp = pos[j];
      while (ll_i != tmp)
      {
        j += 1;
        tmp2 = tmp;
        tmp = pos[j];
        pos[j] = tmp2;
      }

      ;
      pos[0] = tmp;
      s->selectorMtf[i] = j;
    }

  }
  ;
  for (t = 0; t < nGroups; t += 1)
  {
    minLen = 32;
    maxLen = 0;
    for (i = 0; i < alphaSize; i += 1)
    {
      if (s->len[t][i] > maxLen)
      {
        maxLen = s->len[t][i];
      }
      if (s->len[t][i] < minLen)
      {
        minLen = s->len[t][i];
      }
    }

    {
      if (!(!(maxLen > 17)))
      {
        BZ2_bz__AssertH__fail(3004);
      }
    }
    ;
    {
      if (!(!(minLen < 1)))
      {
        BZ2_bz__AssertH__fail(3005);
      }
    }
    ;
    BZ2_hbAssignCodes(&s->code[t][0], &s->len[t][0], minLen, maxLen, alphaSize);
  }

  {
    Bool inUse16[16];
    for (i = 0; i < 16; i += 1)
    {
      inUse16[i] = (Bool) 0;
      for (j = 0; j < 16; j += 1)
      {
        if (s->inUse[(i * 16) + j])
        {
          inUse16[i] = (Bool) 1;
        }
      }

    }

    nBytes = s->numZ;
    for (i = 0; i < 16; i += 1)
    {
      if (inUse16[i])
      {
        bsW(s, 1, 1);
      }
      else
        bsW(s, 1, 0);
    }

    for (i = 0; i < 16; i += 1)
    {
      if (inUse16[i])
      {
        for (j = 0; j < 16; j += 1)
        {
          if (s->inUse[(i * 16) + j])
          {
            bsW(s, 1, 1);
          }
          else
            bsW(s, 1, 0);
        }

      }
    }

    if (s->verbosity >= 3)
    {
      fprintf(stderr, "      bytes: mapping %d, ", s->numZ - nBytes);
    }
  }
  nBytes = s->numZ;
  bsW(s, 3, nGroups);
  bsW(s, 15, nSelectors);
  for (i = 0; i < nSelectors; i += 1)
  {
    for (j = 0; j < s->selectorMtf[i]; j += 1)
    {
      bsW(s, 1, 1);
    }

    bsW(s, 1, 0);
  }

  if (s->verbosity >= 3)
  {
    fprintf(stderr, "selectors %d, ", s->numZ - nBytes);
  }
  nBytes = s->numZ;
  for (t = 0; t < nGroups; t += 1)
  {
    Int32 curr = s->len[t][0];
    bsW(s, 5, curr);
    for (i = 0; i < alphaSize; i += 1)
    {
      while (curr < s->len[t][i])
      {
        bsW(s, 2, 2);
        curr += 1;
      }

      ;
      while (curr > s->len[t][i])
      {
        bsW(s, 2, 3);
        curr -= 1;
      }

      ;
      bsW(s, 1, 0);
    }

  }

  if (s->verbosity >= 3)
  {
    fprintf(stderr, "code lengths %d, ", s->numZ - nBytes);
  }
  nBytes = s->numZ;
  selCtr = 0;
  gs = 0;
  while ((Bool) 1)
  {
    if (gs >= s->nMTF)
    {
      break;
    }
    ge = (gs + 50) - 1;
    if (ge >= s->nMTF)
    {
      ge = s->nMTF - 1;
    }
    {
      if (!(s->selector[selCtr] < nGroups))
      {
        BZ2_bz__AssertH__fail(3006);
      }
    }
    ;
    if ((nGroups == 6) && (50 == ((ge - gs) + 1)))
    {
      UInt16 mtfv_i;
      UChar *s_len_sel_selCtr = &s->len[s->selector[selCtr]][0];
      Int32 *s_code_sel_selCtr = &s->code[s->selector[selCtr]][0];
      mtfv_i = mtfv[gs + 0];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 1];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 2];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 3];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 4];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 5];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 6];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 7];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 8];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 9];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 10];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 11];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 12];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 13];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 14];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 15];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 16];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 17];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 18];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 19];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 20];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 21];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 22];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 23];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 24];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 25];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 26];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 27];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 28];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 29];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 30];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 31];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 32];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 33];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 34];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 35];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 36];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 37];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 38];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 39];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 40];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 41];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 42];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 43];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 44];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 45];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 46];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 47];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 48];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 49];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
    }
    else
    {
      for (i = gs; i <= ge; i += 1)
      {
        bsW(s, s->len[s->selector[selCtr]][mtfv[i]], s->code[s->selector[selCtr]][mtfv[i]]);
      }

    }
    gs = ge + 1;
    selCtr += 1;
  }

  {
    if (!(selCtr == nSelectors))
    {
      BZ2_bz__AssertH__fail(3007);
    }
  }
  ;
  if (s->verbosity >= 3)
  {
    fprintf(stderr, "codes %d\n", s->numZ - nBytes);
  }
}

void BZ2_compressBlock(EState *s, Bool is_last_block)
{
  if (s->nblock > 0)
  {
    {
      s->blockCRC = ~s->blockCRC;
    }
    ;
    s->combinedCRC = (s->combinedCRC << 1) | (s->combinedCRC >> 31);
    s->combinedCRC ^= s->blockCRC;
    if (s->blockNo > 1)
    {
      s->numZ = 0;
    }
    if (s->verbosity >= 2)
    {
      fprintf(stderr, "    block %d: crc = 0x%08x, combined CRC = 0x%08x, size = %d\n", s->blockNo, s->blockCRC, s->combinedCRC, s->nblock);
    }
    BZ2_blockSort(s);
  }
  s->zbits = (UChar *) (&((UChar *) s->arr2)[s->nblock]);
  if (s->blockNo == 1)
  {
    BZ2_bsInitWrite(s);
    bsPutUChar(s, 0x42);
    bsPutUChar(s, 0x5a);
    bsPutUChar(s, 0x68);
    bsPutUChar(s, (UChar) (0x30 + s->blockSize100k));
  }
  if (s->nblock > 0)
  {
    bsPutUChar(s, 0x31);
    bsPutUChar(s, 0x41);
    bsPutUChar(s, 0x59);
    bsPutUChar(s, 0x26);
    bsPutUChar(s, 0x53);
    bsPutUChar(s, 0x59);
    bsPutUInt32(s, s->blockCRC);
    bsW(s, 1, 0);
    bsW(s, 24, s->origPtr);
    generateMTFValues(s);
    sendMTFValues(s);
  }
  if (is_last_block)
  {
    bsPutUChar(s, 0x17);
    bsPutUChar(s, 0x72);
    bsPutUChar(s, 0x45);
    bsPutUChar(s, 0x38);
    bsPutUChar(s, 0x50);
    bsPutUChar(s, 0x90);
    bsPutUInt32(s, s->combinedCRC);
    if (s->verbosity >= 2)
    {
      fprintf(stderr, "    final combined CRC = 0x%08x\n   ", s->combinedCRC);
    }
    bsFinishWrite(s);
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
void BZ2_bsInitWrite(EState *s)
{
  s->bsLive = 0;
  s->bsBuff = 0;
}

static void bsFinishWrite(EState *s)
{
  while (s->bsLive > 0)
  {
    s->zbits[s->numZ] = (UChar) (s->bsBuff >> 24);
    s->numZ += 1;
    s->bsBuff <<= 8;
    s->bsLive -= 8;
  }

}

static void bsW(EState *s, Int32 n, UInt32 v)
{
  {
    while (s->bsLive >= 8)
    {
      s->zbits[s->numZ] = (UChar) (s->bsBuff >> 24);
      s->numZ += 1;
      s->bsBuff <<= 8;
      s->bsLive -= 8;
    }

  }
  ;
  s->bsBuff |= v << ((32 - s->bsLive) - n);
  s->bsLive += n;
}

static void bsPutUInt32(EState *s, UInt32 u)
{
  bsW(s, 8, (u >> 24) & 0xffL);
  bsW(s, 8, (u >> 16) & 0xffL);
  bsW(s, 8, (u >> 8) & 0xffL);
  bsW(s, 8, u & 0xffL);
}

static void bsPutUChar(EState *s, UChar c)
{
  bsW(s, 8, (UInt32) c);
}

static void makeMaps_e(EState *s)
{
  Int32 i;
  s->nInUse = 0;
  for (i = 0; i < 256; i += 1)
  {
    if (s->inUse[i])
    {
      s->unseqToSeq[i] = s->nInUse;
      s->nInUse += 1;
    }
  }

}

static void generateMTFValues(EState *s)
{
  UChar yy[256];
  Int32 i;
  Int32 j;
  Int32 zPend;
  Int32 wr;
  Int32 EOB;
  UInt32 *ptr = s->ptr;
  UChar *block = s->block;
  UInt16 *mtfv = s->mtfv;
  makeMaps_e(s);
  EOB = s->nInUse + 1;
  for (i = 0; i <= EOB; i += 1)
  {
    s->mtfFreq[i] = 0;
  }

  wr = 0;
  zPend = 0;
  for (i = 0; i < s->nInUse; i += 1)
  {
    yy[i] = (UChar) i;
  }

  for (i = 0; i < s->nblock; i += 1)
  {
    UChar ll_i;
    ;
    j = ptr[i] - 1;
    if (j < 0)
    {
      j += s->nblock;
    }
    ll_i = s->unseqToSeq[block[j]];
    ;
    if (yy[0] == ll_i)
    {
      zPend += 1;
    }
    else
    {
      if (zPend > 0)
      {
        zPend -= 1;
        while ((Bool) 1)
        {
          if (zPend & 1)
          {
            mtfv[wr] = 1;
            wr += 1;
            s->mtfFreq[1] += 1;
          }
          else
          {
            mtfv[wr] = 0;
            wr += 1;
            s->mtfFreq[0] += 1;
          }
          if (zPend < 2)
          {
            break;
          }
          zPend = (zPend - 2) / 2;
        }

        ;
        zPend = 0;
      }
      {
        register UChar rtmp;
        register UChar *ryy_j;
        unsigned int ryy_j_idx = 0;
        register UChar rll_i;
        rtmp = yy[1];
        yy[1] = yy[0];
        ryy_j_idx = &yy[1];
        rll_i = ll_i;
        while (rll_i != rtmp)
        {
          register UChar rtmp2;
          ryy_j_idx += 1;
          rtmp2 = rtmp;
          rtmp = ryy_j[ryy_j_idx];
          ryy_j[ryy_j_idx] = rtmp2;
        }

        ;
        yy[0] = rtmp;
        j = (&ryy_j[ryy_j_idx]) - (&yy[0]);
        mtfv[wr] = j + 1;
        wr += 1;
        s->mtfFreq[j + 1] += 1;
      }
    }
  }

  if (zPend > 0)
  {
    zPend -= 1;
    while ((Bool) 1)
    {
      if (zPend & 1)
      {
        mtfv[wr] = 1;
        wr += 1;
        s->mtfFreq[1] += 1;
      }
      else
      {
        mtfv[wr] = 0;
        wr += 1;
        s->mtfFreq[0] += 1;
      }
      if (zPend < 2)
      {
        break;
      }
      zPend = (zPend - 2) / 2;
    }

    ;
    zPend = 0;
  }
  mtfv[wr] = EOB;
  wr += 1;
  s->mtfFreq[EOB] += 1;
  s->nMTF = wr;
}

static void sendMTFValues(EState *s)
{
  Int32 v;
  Int32 t;
  Int32 i;
  Int32 j;
  Int32 gs;
  Int32 ge;
  Int32 totc;
  Int32 bt;
  Int32 bc;
  Int32 iter;
  Int32 nSelectors;
  Int32 alphaSize;
  Int32 minLen;
  Int32 maxLen;
  Int32 selCtr;
  Int32 nGroups;
  Int32 nBytes;
  UInt16 cost[6];
  Int32 fave[6];
  UInt16 *mtfv = s->mtfv;
  if (s->verbosity >= 3)
  {
    fprintf(stderr, "      %d in block, %d after MTF & 1-2 coding, %d+2 syms in use\n", s->nblock, s->nMTF, s->nInUse);
  }
  alphaSize = s->nInUse + 2;
  for (t = 0; t < 6; t += 1)
  {
    for (v = 0; v < alphaSize; v += 1)
    {
      s->len[t][v] = 15;
    }

  }

  {
    if (!(s->nMTF > 0))
    {
      BZ2_bz__AssertH__fail(3001);
    }
  }
  ;
  if (s->nMTF < 200)
  {
    nGroups = 2;
  }
  else
    if (s->nMTF < 600)
  {
    nGroups = 3;
  }
  else
    if (s->nMTF < 1200)
  {
    nGroups = 4;
  }
  else
    if (s->nMTF < 2400)
  {
    nGroups = 5;
  }
  else
    nGroups = 6;
  {
    Int32 nPart;
    Int32 remF;
    Int32 tFreq;
    Int32 aFreq;
    nPart = nGroups;
    remF = s->nMTF;
    gs = 0;
    while (nPart > 0)
    {
      tFreq = remF / nPart;
      ge = gs - 1;
      aFreq = 0;
      while ((aFreq < tFreq) && (ge < (alphaSize - 1)))
      {
        ge += 1;
        aFreq += s->mtfFreq[ge];
      }

      if ((((ge > gs) && (nPart != nGroups)) && (nPart != 1)) && (((nGroups - nPart) % 2) == 1))
      {
        aFreq -= s->mtfFreq[ge];
        ge -= 1;
      }
      if (s->verbosity >= 3)
      {
        fprintf(stderr, "      initial group %d, [%d .. %d], has %d syms (%4.1f%%)\n", nPart, gs, ge, aFreq, (100.0 * ((float) aFreq)) / ((float) s->nMTF));
      }
      for (v = 0; v < alphaSize; v += 1)
      {
        if ((v >= gs) && (v <= ge))
        {
          s->len[nPart - 1][v] = 0;
        }
        else
          s->len[nPart - 1][v] = 15;
      }

      nPart -= 1;
      gs = ge + 1;
      remF -= aFreq;
    }

  }
  for (iter = 0; iter < 4; iter += 1)
  {
    for (t = 0; t < nGroups; t += 1)
    {
      fave[t] = 0;
    }

    for (t = 0; t < nGroups; t += 1)
    {
      for (v = 0; v < alphaSize; v += 1)
      {
        s->rfreq[t][v] = 0;
      }

    }

    if (nGroups == 6)
    {
      for (v = 0; v < alphaSize; v += 1)
      {
        s->len_pack[v][0] = (s->len[1][v] << 16) | s->len[0][v];
        s->len_pack[v][1] = (s->len[3][v] << 16) | s->len[2][v];
        s->len_pack[v][2] = (s->len[5][v] << 16) | s->len[4][v];
      }

    }
    nSelectors = 0;
    totc = 0;
    gs = 0;
    while ((Bool) 1)
    {
      if (gs >= s->nMTF)
      {
        break;
      }
      ge = (gs + 50) - 1;
      if (ge >= s->nMTF)
      {
        ge = s->nMTF - 1;
      }
      for (t = 0; t < nGroups; t += 1)
      {
        cost[t] = 0;
      }

      if ((nGroups == 6) && (50 == ((ge - gs) + 1)))
      {
        register UInt32 cost01;
        register UInt32 cost23;
        register UInt32 cost45;
        register UInt16 icv;
        cost01 = (cost23 = (cost45 = 0));
        icv = mtfv[gs + 0];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 1];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 2];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 3];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 4];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 5];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 6];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 7];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 8];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 9];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 10];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 11];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 12];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 13];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 14];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 15];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 16];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 17];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 18];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 19];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 20];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 21];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 22];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 23];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 24];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 25];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 26];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 27];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 28];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 29];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 30];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 31];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 32];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 33];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 34];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 35];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 36];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 37];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 38];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 39];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 40];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 41];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 42];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 43];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 44];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 45];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 46];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 47];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 48];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        icv = mtfv[gs + 49];
        cost01 += s->len_pack[icv][0];
        cost23 += s->len_pack[icv][1];
        cost45 += s->len_pack[icv][2];
        ;
        cost[0] = cost01 & 0xffff;
        cost[1] = cost01 >> 16;
        cost[2] = cost23 & 0xffff;
        cost[3] = cost23 >> 16;
        cost[4] = cost45 & 0xffff;
        cost[5] = cost45 >> 16;
      }
      else
      {
        for (i = gs; i <= ge; i += 1)
        {
          UInt16 icv = mtfv[i];
          for (t = 0; t < nGroups; t += 1)
          {
            cost[t] += s->len[t][icv];
          }

        }

      }
      bc = 999999999;
      bt = -1;
      for (t = 0; t < nGroups; t += 1)
      {
        if (cost[t] < bc)
        {
          bc = cost[t];
          bt = t;
        }
      }

      ;
      totc += bc;
      fave[bt] += 1;
      s->selector[nSelectors] = bt;
      nSelectors += 1;
      if ((nGroups == 6) && (50 == ((ge - gs) + 1)))
      {
        s->rfreq[bt][mtfv[gs + 0]] += 1;
        s->rfreq[bt][mtfv[gs + 1]] += 1;
        s->rfreq[bt][mtfv[gs + 2]] += 1;
        s->rfreq[bt][mtfv[gs + 3]] += 1;
        s->rfreq[bt][mtfv[gs + 4]] += 1;
        s->rfreq[bt][mtfv[gs + 5]] += 1;
        s->rfreq[bt][mtfv[gs + 6]] += 1;
        s->rfreq[bt][mtfv[gs + 7]] += 1;
        s->rfreq[bt][mtfv[gs + 8]] += 1;
        s->rfreq[bt][mtfv[gs + 9]] += 1;
        s->rfreq[bt][mtfv[gs + 10]] += 1;
        s->rfreq[bt][mtfv[gs + 11]] += 1;
        s->rfreq[bt][mtfv[gs + 12]] += 1;
        s->rfreq[bt][mtfv[gs + 13]] += 1;
        s->rfreq[bt][mtfv[gs + 14]] += 1;
        s->rfreq[bt][mtfv[gs + 15]] += 1;
        s->rfreq[bt][mtfv[gs + 16]] += 1;
        s->rfreq[bt][mtfv[gs + 17]] += 1;
        s->rfreq[bt][mtfv[gs + 18]] += 1;
        s->rfreq[bt][mtfv[gs + 19]] += 1;
        s->rfreq[bt][mtfv[gs + 20]] += 1;
        s->rfreq[bt][mtfv[gs + 21]] += 1;
        s->rfreq[bt][mtfv[gs + 22]] += 1;
        s->rfreq[bt][mtfv[gs + 23]] += 1;
        s->rfreq[bt][mtfv[gs + 24]] += 1;
        s->rfreq[bt][mtfv[gs + 25]] += 1;
        s->rfreq[bt][mtfv[gs + 26]] += 1;
        s->rfreq[bt][mtfv[gs + 27]] += 1;
        s->rfreq[bt][mtfv[gs + 28]] += 1;
        s->rfreq[bt][mtfv[gs + 29]] += 1;
        s->rfreq[bt][mtfv[gs + 30]] += 1;
        s->rfreq[bt][mtfv[gs + 31]] += 1;
        s->rfreq[bt][mtfv[gs + 32]] += 1;
        s->rfreq[bt][mtfv[gs + 33]] += 1;
        s->rfreq[bt][mtfv[gs + 34]] += 1;
        s->rfreq[bt][mtfv[gs + 35]] += 1;
        s->rfreq[bt][mtfv[gs + 36]] += 1;
        s->rfreq[bt][mtfv[gs + 37]] += 1;
        s->rfreq[bt][mtfv[gs + 38]] += 1;
        s->rfreq[bt][mtfv[gs + 39]] += 1;
        s->rfreq[bt][mtfv[gs + 40]] += 1;
        s->rfreq[bt][mtfv[gs + 41]] += 1;
        s->rfreq[bt][mtfv[gs + 42]] += 1;
        s->rfreq[bt][mtfv[gs + 43]] += 1;
        s->rfreq[bt][mtfv[gs + 44]] += 1;
        s->rfreq[bt][mtfv[gs + 45]] += 1;
        s->rfreq[bt][mtfv[gs + 46]] += 1;
        s->rfreq[bt][mtfv[gs + 47]] += 1;
        s->rfreq[bt][mtfv[gs + 48]] += 1;
        s->rfreq[bt][mtfv[gs + 49]] += 1;
      }
      else
      {
        for (i = gs; i <= ge; i += 1)
        {
          s->rfreq[bt][mtfv[i]] += 1;
        }

      }
      gs = ge + 1;
    }

    if (s->verbosity >= 3)
    {
      fprintf(stderr, "      pass %d: size is %d, grp uses are ", iter + 1, totc / 8);
      for (t = 0; t < nGroups; t += 1)
      {
        fprintf(stderr, "%d ", fave[t]);
      }

      fprintf(stderr, "\n");
    }
    for (t = 0; t < nGroups; t += 1)
    {
      BZ2_hbMakeCodeLengths(&s->len[t][0], &s->rfreq[t][0], alphaSize, 17);
    }

  }

  {
    if (!(nGroups < 8))
    {
      BZ2_bz__AssertH__fail(3002);
    }
  }
  ;
  {
    if (!((nSelectors < 32768) && (nSelectors <= (2 + (900000 / 50)))))
    {
      BZ2_bz__AssertH__fail(3003);
    }
  }
  ;
  {
    UChar pos[6];
    UChar ll_i;
    UChar tmp2;
    UChar tmp;
    for (i = 0; i < nGroups; i += 1)
    {
      pos[i] = i;
    }

    for (i = 0; i < nSelectors; i += 1)
    {
      ll_i = s->selector[i];
      j = 0;
      tmp = pos[j];
      while (ll_i != tmp)
      {
        j += 1;
        tmp2 = tmp;
        tmp = pos[j];
        pos[j] = tmp2;
      }

      ;
      pos[0] = tmp;
      s->selectorMtf[i] = j;
    }

  }
  ;
  for (t = 0; t < nGroups; t += 1)
  {
    minLen = 32;
    maxLen = 0;
    for (i = 0; i < alphaSize; i += 1)
    {
      if (s->len[t][i] > maxLen)
      {
        maxLen = s->len[t][i];
      }
      if (s->len[t][i] < minLen)
      {
        minLen = s->len[t][i];
      }
    }

    {
      if (!(!(maxLen > 17)))
      {
        BZ2_bz__AssertH__fail(3004);
      }
    }
    ;
    {
      if (!(!(minLen < 1)))
      {
        BZ2_bz__AssertH__fail(3005);
      }
    }
    ;
    BZ2_hbAssignCodes(&s->code[t][0], &s->len[t][0], minLen, maxLen, alphaSize);
  }

  {
    Bool inUse16[16];
    for (i = 0; i < 16; i += 1)
    {
      inUse16[i] = (Bool) 0;
      for (j = 0; j < 16; j += 1)
      {
        if (s->inUse[(i * 16) + j])
        {
          inUse16[i] = (Bool) 1;
        }
      }

    }

    nBytes = s->numZ;
    for (i = 0; i < 16; i += 1)
    {
      if (inUse16[i])
      {
        bsW(s, 1, 1);
      }
      else
        bsW(s, 1, 0);
    }

    for (i = 0; i < 16; i += 1)
    {
      if (inUse16[i])
      {
        for (j = 0; j < 16; j += 1)
        {
          if (s->inUse[(i * 16) + j])
          {
            bsW(s, 1, 1);
          }
          else
            bsW(s, 1, 0);
        }

      }
    }

    if (s->verbosity >= 3)
    {
      fprintf(stderr, "      bytes: mapping %d, ", s->numZ - nBytes);
    }
  }
  nBytes = s->numZ;
  bsW(s, 3, nGroups);
  bsW(s, 15, nSelectors);
  for (i = 0; i < nSelectors; i += 1)
  {
    for (j = 0; j < s->selectorMtf[i]; j += 1)
    {
      bsW(s, 1, 1);
    }

    bsW(s, 1, 0);
  }

  if (s->verbosity >= 3)
  {
    fprintf(stderr, "selectors %d, ", s->numZ - nBytes);
  }
  nBytes = s->numZ;
  for (t = 0; t < nGroups; t += 1)
  {
    Int32 curr = s->len[t][0];
    bsW(s, 5, curr);
    for (i = 0; i < alphaSize; i += 1)
    {
      while (curr < s->len[t][i])
      {
        bsW(s, 2, 2);
        curr += 1;
      }

      ;
      while (curr > s->len[t][i])
      {
        bsW(s, 2, 3);
        curr -= 1;
      }

      ;
      bsW(s, 1, 0);
    }

  }

  if (s->verbosity >= 3)
  {
    fprintf(stderr, "code lengths %d, ", s->numZ - nBytes);
  }
  nBytes = s->numZ;
  selCtr = 0;
  gs = 0;
  while ((Bool) 1)
  {
    if (gs >= s->nMTF)
    {
      break;
    }
    ge = (gs + 50) - 1;
    if (ge >= s->nMTF)
    {
      ge = s->nMTF - 1;
    }
    {
      if (!(s->selector[selCtr] < nGroups))
      {
        BZ2_bz__AssertH__fail(3006);
      }
    }
    ;
    if ((nGroups == 6) && (50 == ((ge - gs) + 1)))
    {
      UInt16 mtfv_i;
      UChar *s_len_sel_selCtr = &s->len[s->selector[selCtr]][0];
      Int32 *s_code_sel_selCtr = &s->code[s->selector[selCtr]][0];
      mtfv_i = mtfv[gs + 0];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 1];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 2];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 3];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 4];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 5];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 6];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 7];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 8];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 9];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 10];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 11];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 12];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 13];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 14];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 15];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 16];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 17];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 18];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 19];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 20];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 21];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 22];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 23];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 24];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 25];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 26];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 27];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 28];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 29];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 30];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 31];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 32];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 33];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 34];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 35];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 36];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 37];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 38];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 39];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 40];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 41];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 42];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 43];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 44];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 45];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 46];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 47];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 48];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
      mtfv_i = mtfv[gs + 49];
      bsW(s, s_len_sel_selCtr[mtfv_i], s_code_sel_selCtr[mtfv_i]);
    }
    else
    {
      for (i = gs; i <= ge; i += 1)
      {
        bsW(s, s->len[s->selector[selCtr]][mtfv[i]], s->code[s->selector[selCtr]][mtfv[i]]);
      }

    }
    gs = ge + 1;
    selCtr += 1;
  }

  {
    if (!(selCtr == nSelectors))
    {
      BZ2_bz__AssertH__fail(3007);
    }
  }
  ;
  if (s->verbosity >= 3)
  {
    fprintf(stderr, "codes %d\n", s->numZ - nBytes);
  }
}

void BZ2_compressBlock(EState *s, Bool is_last_block)
{
  if (s->nblock > 0)
  {
    {
      s->blockCRC = ~s->blockCRC;
    }
    ;
    s->combinedCRC = (s->combinedCRC << 1) | (s->combinedCRC >> 31);
    s->combinedCRC ^= s->blockCRC;
    if (s->blockNo > 1)
    {
      s->numZ = 0;
    }
    if (s->verbosity >= 2)
    {
      fprintf(stderr, "    block %d: crc = 0x%08x, combined CRC = 0x%08x, size = %d\n", s->blockNo, s->blockCRC, s->combinedCRC, s->nblock);
    }
    BZ2_blockSort(s);
  }
  s->zbits = (UChar *) (&((UChar *) s->arr2)[s->nblock]);
  if (s->blockNo == 1)
  {
    BZ2_bsInitWrite(s);
    bsPutUChar(s, 0x42);
    bsPutUChar(s, 0x5a);
    bsPutUChar(s, 0x68);
    bsPutUChar(s, (UChar) (0x30 + s->blockSize100k));
  }
  if (s->nblock > 0)
  {
    bsPutUChar(s, 0x31);
    bsPutUChar(s, 0x41);
    bsPutUChar(s, 0x59);
    bsPutUChar(s, 0x26);
    bsPutUChar(s, 0x53);
    bsPutUChar(s, 0x59);
    bsPutUInt32(s, s->blockCRC);
    bsW(s, 1, 0);
    bsW(s, 24, s->origPtr);
    generateMTFValues(s);
    sendMTFValues(s);
  }
  if (is_last_block)
  {
    bsPutUChar(s, 0x17);
    bsPutUChar(s, 0x72);
    bsPutUChar(s, 0x45);
    bsPutUChar(s, 0x38);
    bsPutUChar(s, 0x50);
    bsPutUChar(s, 0x90);
    bsPutUInt32(s, s->combinedCRC);
    if (s->verbosity >= 2)
    {
      fprintf(stderr, "    final combined CRC = 0x%08x\n   ", s->combinedCRC);
    }
    bsFinishWrite(s);
  }
}

