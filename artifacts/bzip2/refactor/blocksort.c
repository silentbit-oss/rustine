#include <blocksort.c>
#include <bzlib.h>
#include <bzlib_private.h>
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
static void fallbackSimpleSort(UInt32 *fmap, UInt32 *eclass, Int32 lo, Int32 hi)
{
  Int32 i;
  Int32 j;
  Int32 tmp;
  UInt32 ec_tmp;
  if (lo == hi)
  {
    return;
  }
  if ((hi - lo) > 3)
  {
    for (i = hi - 4; i >= lo; i -= 1)
    {
      tmp = fmap[i];
      ec_tmp = eclass[tmp];
      for (j = i + 4; (j <= hi) && (ec_tmp > eclass[fmap[j]]); j += 4)
      {
        fmap[j - 4] = fmap[j];
      }

      fmap[j - 4] = tmp;
    }

  }
  for (i = hi - 1; i >= lo; i -= 1)
  {
    tmp = fmap[i];
    ec_tmp = eclass[tmp];
    for (j = i + 1; (j <= hi) && (ec_tmp > eclass[fmap[j]]); j += 1)
    {
      fmap[j - 1] = fmap[j];
    }

    fmap[j - 1] = tmp;
  }

}

static void fallbackQSort3(UInt32 *fmap, UInt32 *eclass, Int32 loSt, Int32 hiSt)
{
  Int32 unLo;
  Int32 unHi;
  Int32 ltLo;
  Int32 gtHi;
  Int32 n;
  Int32 m;
  Int32 sp;
  Int32 lo;
  Int32 hi;
  UInt32 med;
  UInt32 r;
  UInt32 r3;
  Int32 stackLo[100];
  Int32 stackHi[100];
  r = 0;
  sp = 0;
  {
    stackLo[sp] = loSt;
    stackHi[sp] = hiSt;
    sp += 1;
  }
  ;
  while (sp > 0)
  {
    {
      if (!(sp < (100 - 1)))
      {
        BZ2_bz__AssertH__fail(1004);
      }
    }
    ;
    {
      sp -= 1;
      lo = stackLo[sp];
      hi = stackHi[sp];
    }
    ;
    if ((hi - lo) < 10)
    {
      fallbackSimpleSort(fmap, eclass, lo, hi);
      continue;
    }
    r = ((r * 7621) + 1) % 32768;
    r3 = r % 3;
    if (r3 == 0)
    {
      med = eclass[fmap[lo]];
    }
    else
      if (r3 == 1)
    {
      med = eclass[fmap[(lo + hi) >> 1]];
    }
    else
      med = eclass[fmap[hi]];
    unLo = (ltLo = lo);
    unHi = (gtHi = hi);
    while (1)
    {
      while (1)
      {
        if (unLo > unHi)
        {
          break;
        }
        n = ((Int32) eclass[fmap[unLo]]) - ((Int32) med);
        if (n == 0)
        {
          {
            Int32 zztmp = fmap[unLo];
            fmap[unLo] = fmap[ltLo];
            fmap[ltLo] = zztmp;
          }
          ;
          ltLo += 1;
          unLo += 1;
          continue;
        }
        ;
        if (n > 0)
        {
          break;
        }
        unLo += 1;
      }

      while (1)
      {
        if (unLo > unHi)
        {
          break;
        }
        n = ((Int32) eclass[fmap[unHi]]) - ((Int32) med);
        if (n == 0)
        {
          {
            Int32 zztmp = fmap[unHi];
            fmap[unHi] = fmap[gtHi];
            fmap[gtHi] = zztmp;
          }
          ;
          gtHi -= 1;
          unHi -= 1;
          continue;
        }
        ;
        if (n < 0)
        {
          break;
        }
        unHi -= 1;
      }

      if (unLo > unHi)
      {
        break;
      }
      {
        Int32 zztmp = fmap[unLo];
        fmap[unLo] = fmap[unHi];
        fmap[unHi] = zztmp;
      }
      ;
      unLo += 1;
      unHi -= 1;
    }

    ;
    if (gtHi < ltLo)
    {
      continue;
    }
    n = ((ltLo - lo) < (unLo - ltLo)) ? (ltLo - lo) : (unLo - ltLo);
    {
      Int32 yyp1 = lo;
      Int32 yyp2 = unLo - n;
      Int32 yyn = n;
      while (yyn > 0)
      {
        {
          Int32 zztmp = fmap[yyp1];
          fmap[yyp1] = fmap[yyp2];
          fmap[yyp2] = zztmp;
        }
        ;
        yyp1 += 1;
        yyp2 += 1;
        yyn -= 1;
      }

    }
    ;
    m = ((hi - gtHi) < (gtHi - unHi)) ? (hi - gtHi) : (gtHi - unHi);
    {
      Int32 yyp1 = unLo;
      Int32 yyp2 = (hi - m) + 1;
      Int32 yyn = m;
      while (yyn > 0)
      {
        {
          Int32 zztmp = fmap[yyp1];
          fmap[yyp1] = fmap[yyp2];
          fmap[yyp2] = zztmp;
        }
        ;
        yyp1 += 1;
        yyp2 += 1;
        yyn -= 1;
      }

    }
    ;
    n = ((lo + unLo) - ltLo) - 1;
    m = (hi - (gtHi - unHi)) + 1;
    if ((n - lo) > (hi - m))
    {
      {
        stackLo[sp] = lo;
        stackHi[sp] = n;
        sp += 1;
      }
      ;
      {
        stackLo[sp] = m;
        stackHi[sp] = hi;
        sp += 1;
      }
      ;
    }
    else
    {
      {
        stackLo[sp] = m;
        stackHi[sp] = hi;
        sp += 1;
      }
      ;
      {
        stackLo[sp] = lo;
        stackHi[sp] = n;
        sp += 1;
      }
      ;
    }
  }

}

static void fallbackSort(UInt32 *fmap, UInt32 *eclass, UInt32 *bhtab, Int32 nblock, Int32 verb)
{
  Int32 ftab[257];
  Int32 ftabCopy[256];
  Int32 H;
  Int32 i;
  Int32 j;
  Int32 k;
  Int32 l;
  Int32 r;
  Int32 cc;
  Int32 cc1;
  Int32 nNotDone;
  Int32 nBhtab;
  UChar *eclass8 = (UChar *) eclass;
  if (verb >= 4)
  {
    fprintf(stderr, "        bucket sorting ...\n");
  }
  for (i = 0; i < 257; i += 1)
  {
    ftab[i] = 0;
  }

  for (i = 0; i < nblock; i += 1)
  {
    ftab[eclass8[i]] += 1;
  }

  for (i = 0; i < 256; i += 1)
  {
    ftabCopy[i] = ftab[i];
  }

  for (i = 1; i < 257; i += 1)
  {
    ftab[i] += ftab[i - 1];
  }

  for (i = 0; i < nblock; i += 1)
  {
    j = eclass8[i];
    k = ftab[j] - 1;
    ftab[j] = k;
    fmap[k] = i;
  }

  nBhtab = 2 + (nblock / 32);
  for (i = 0; i < nBhtab; i += 1)
  {
    bhtab[i] = 0;
  }

  for (i = 0; i < 256; i += 1)
  {
    bhtab[ftab[i] >> 5] |= ((UInt32) 1) << (ftab[i] & 31);
  }

  for (i = 0; i < 32; i += 1)
  {
    bhtab[(nblock + (2 * i)) >> 5] |= ((UInt32) 1) << ((nblock + (2 * i)) & 31);
    bhtab[((nblock + (2 * i)) + 1) >> 5] &= ~(((UInt32) 1) << (((nblock + (2 * i)) + 1) & 31));
  }

  H = 1;
  while (1)
  {
    if (verb >= 4)
    {
      fprintf(stderr, "        depth %6d has ", H);
    }
    j = 0;
    for (i = 0; i < nblock; i += 1)
    {
      if (bhtab[i >> 5] & (((UInt32) 1) << (i & 31)))
      {
        j = i;
      }
      k = fmap[i] - H;
      if (k < 0)
      {
        k += nblock;
      }
      eclass[k] = j;
    }

    nNotDone = 0;
    r = -1;
    while (1)
    {
      k = r + 1;
      while ((bhtab[k >> 5] & (((UInt32) 1) << (k & 31))) && (k & 0x01f))
      {
        k += 1;
      }

      if (bhtab[k >> 5] & (((UInt32) 1) << (k & 31)))
      {
        while (bhtab[k >> 5] == 0xffffffff)
        {
          k += 32;
        }

        while (bhtab[k >> 5] & (((UInt32) 1) << (k & 31)))
        {
          k += 1;
        }

      }
      l = k - 1;
      if (l >= nblock)
      {
        break;
      }
      while ((!(bhtab[k >> 5] & (((UInt32) 1) << (k & 31)))) && (k & 0x01f))
      {
        k += 1;
      }

      if (!(bhtab[k >> 5] & (((UInt32) 1) << (k & 31))))
      {
        while (bhtab[k >> 5] == 0x00000000)
        {
          k += 32;
        }

        while (!(bhtab[k >> 5] & (((UInt32) 1) << (k & 31))))
        {
          k += 1;
        }

      }
      r = k - 1;
      if (r >= nblock)
      {
        break;
      }
      if (r > l)
      {
        nNotDone += (r - l) + 1;
        fallbackQSort3(fmap, eclass, l, r);
        cc = -1;
        for (i = l; i <= r; i += 1)
        {
          cc1 = eclass[fmap[i]];
          if (cc != cc1)
          {
            bhtab[i >> 5] |= ((UInt32) 1) << (i & 31);
            cc = cc1;
          }
          ;
        }

      }
    }

    if (verb >= 4)
    {
      fprintf(stderr, "%6d unresolved strings\n", nNotDone);
    }
    H *= 2;
    if ((H > nblock) || (nNotDone == 0))
    {
      break;
    }
  }

  if (verb >= 4)
  {
    fprintf(stderr, "        reconstructing block ...\n");
  }
  j = 0;
  for (i = 0; i < nblock; i += 1)
  {
    while (ftabCopy[j] == 0)
    {
      j += 1;
    }

    ftabCopy[j] -= 1;
    eclass8[fmap[i]] = (UChar) j;
  }

  {
    if (!(j < 256))
    {
      BZ2_bz__AssertH__fail(1005);
    }
  }
  ;
}

static Bool mainGtU(UInt32 i1, UInt32 i2, UChar *block, UInt16 *quadrant, UInt32 nblock, Int32 *budget)
{
  Int32 k;
  UChar c1;
  UChar c2;
  UInt16 s1;
  UInt16 s2;
  ;
  c1 = block[i1];
  c2 = block[i2];
  if (c1 != c2)
  {
    return c1 > c2;
  }
  i1 += 1;
  i2 += 1;
  c1 = block[i1];
  c2 = block[i2];
  if (c1 != c2)
  {
    return c1 > c2;
  }
  i1 += 1;
  i2 += 1;
  c1 = block[i1];
  c2 = block[i2];
  if (c1 != c2)
  {
    return c1 > c2;
  }
  i1 += 1;
  i2 += 1;
  c1 = block[i1];
  c2 = block[i2];
  if (c1 != c2)
  {
    return c1 > c2;
  }
  i1 += 1;
  i2 += 1;
  c1 = block[i1];
  c2 = block[i2];
  if (c1 != c2)
  {
    return c1 > c2;
  }
  i1 += 1;
  i2 += 1;
  c1 = block[i1];
  c2 = block[i2];
  if (c1 != c2)
  {
    return c1 > c2;
  }
  i1 += 1;
  i2 += 1;
  c1 = block[i1];
  c2 = block[i2];
  if (c1 != c2)
  {
    return c1 > c2;
  }
  i1 += 1;
  i2 += 1;
  c1 = block[i1];
  c2 = block[i2];
  if (c1 != c2)
  {
    return c1 > c2;
  }
  i1 += 1;
  i2 += 1;
  c1 = block[i1];
  c2 = block[i2];
  if (c1 != c2)
  {
    return c1 > c2;
  }
  i1 += 1;
  i2 += 1;
  c1 = block[i1];
  c2 = block[i2];
  if (c1 != c2)
  {
    return c1 > c2;
  }
  i1 += 1;
  i2 += 1;
  c1 = block[i1];
  c2 = block[i2];
  if (c1 != c2)
  {
    return c1 > c2;
  }
  i1 += 1;
  i2 += 1;
  c1 = block[i1];
  c2 = block[i2];
  if (c1 != c2)
  {
    return c1 > c2;
  }
  i1 += 1;
  i2 += 1;
  k = nblock + 8;
  do
  {
    c1 = block[i1];
    c2 = block[i2];
    if (c1 != c2)
    {
      return c1 > c2;
    }
    s1 = quadrant[i1];
    s2 = quadrant[i2];
    if (s1 != s2)
    {
      return s1 > s2;
    }
    i1 += 1;
    i2 += 1;
    c1 = block[i1];
    c2 = block[i2];
    if (c1 != c2)
    {
      return c1 > c2;
    }
    s1 = quadrant[i1];
    s2 = quadrant[i2];
    if (s1 != s2)
    {
      return s1 > s2;
    }
    i1 += 1;
    i2 += 1;
    c1 = block[i1];
    c2 = block[i2];
    if (c1 != c2)
    {
      return c1 > c2;
    }
    s1 = quadrant[i1];
    s2 = quadrant[i2];
    if (s1 != s2)
    {
      return s1 > s2;
    }
    i1 += 1;
    i2 += 1;
    c1 = block[i1];
    c2 = block[i2];
    if (c1 != c2)
    {
      return c1 > c2;
    }
    s1 = quadrant[i1];
    s2 = quadrant[i2];
    if (s1 != s2)
    {
      return s1 > s2;
    }
    i1 += 1;
    i2 += 1;
    c1 = block[i1];
    c2 = block[i2];
    if (c1 != c2)
    {
      return c1 > c2;
    }
    s1 = quadrant[i1];
    s2 = quadrant[i2];
    if (s1 != s2)
    {
      return s1 > s2;
    }
    i1 += 1;
    i2 += 1;
    c1 = block[i1];
    c2 = block[i2];
    if (c1 != c2)
    {
      return c1 > c2;
    }
    s1 = quadrant[i1];
    s2 = quadrant[i2];
    if (s1 != s2)
    {
      return s1 > s2;
    }
    i1 += 1;
    i2 += 1;
    c1 = block[i1];
    c2 = block[i2];
    if (c1 != c2)
    {
      return c1 > c2;
    }
    s1 = quadrant[i1];
    s2 = quadrant[i2];
    if (s1 != s2)
    {
      return s1 > s2;
    }
    i1 += 1;
    i2 += 1;
    c1 = block[i1];
    c2 = block[i2];
    if (c1 != c2)
    {
      return c1 > c2;
    }
    s1 = quadrant[i1];
    s2 = quadrant[i2];
    if (s1 != s2)
    {
      return s1 > s2;
    }
    i1 += 1;
    i2 += 1;
    if (i1 >= nblock)
    {
      i1 -= nblock;
    }
    if (i2 >= nblock)
    {
      i2 -= nblock;
    }
    k -= 8;
    *budget -= 1;
  }
  while (k >= 0);
  return (Bool) 0;
}

static Int32 incs[14] = {1, 4, 13, 40, 121, 364, 1093, 3280, 9841, 29524, 88573, 265720, 797161, 2391484};
static void mainSimpleSort(UInt32 *ptr, UChar *block, UInt16 *quadrant, Int32 nblock, Int32 lo, Int32 hi, Int32 d, Int32 *budget)
{
  Int32 i;
  Int32 j;
  Int32 h;
  Int32 bigN;
  Int32 hp;
  UInt32 v;
  bigN = (hi - lo) + 1;
  if (bigN < 2)
  {
    return;
  }
  hp = 0;
  while (incs[hp] < bigN)
  {
    hp += 1;
  }

  hp -= 1;
  for (; hp >= 0; hp -= 1)
  {
    h = incs[hp];
    i = lo + h;
    while ((Bool) 1)
    {
      if (i > hi)
      {
        break;
      }
      v = ptr[i];
      j = i;
      while (mainGtU(ptr[j - h] + d, v + d, block, quadrant, nblock, budget))
      {
        ptr[j] = ptr[j - h];
        j = j - h;
        if (j <= ((lo + h) - 1))
        {
          break;
        }
      }

      ptr[j] = v;
      i += 1;
      if (i > hi)
      {
        break;
      }
      v = ptr[i];
      j = i;
      while (mainGtU(ptr[j - h] + d, v + d, block, quadrant, nblock, budget))
      {
        ptr[j] = ptr[j - h];
        j = j - h;
        if (j <= ((lo + h) - 1))
        {
          break;
        }
      }

      ptr[j] = v;
      i += 1;
      if (i > hi)
      {
        break;
      }
      v = ptr[i];
      j = i;
      while (mainGtU(ptr[j - h] + d, v + d, block, quadrant, nblock, budget))
      {
        ptr[j] = ptr[j - h];
        j = j - h;
        if (j <= ((lo + h) - 1))
        {
          break;
        }
      }

      ptr[j] = v;
      i += 1;
      if ((*budget) < 0)
      {
        return;
      }
    }

  }

}

static UChar mmed3(UChar a, UChar b, UChar c)
{
  UChar t;
  if (a > b)
  {
    t = a;
    a = b;
    b = t;
  }
  ;
  if (b > c)
  {
    b = c;
    if (a > b)
    {
      b = a;
    }
  }
  return b;
}

static void mainQSort3(UInt32 *ptr, UChar *block, UInt16 *quadrant, Int32 nblock, Int32 loSt, Int32 hiSt, Int32 dSt, Int32 *budget)
{
  Int32 unLo;
  Int32 unHi;
  Int32 ltLo;
  Int32 gtHi;
  Int32 n;
  Int32 m;
  Int32 med;
  Int32 sp;
  Int32 lo;
  Int32 hi;
  Int32 d;
  Int32 stackLo[100];
  Int32 stackHi[100];
  Int32 stackD[100];
  Int32 nextLo[3];
  Int32 nextHi[3];
  Int32 nextD[3];
  sp = 0;
  {
    stackLo[sp] = loSt;
    stackHi[sp] = hiSt;
    stackD[sp] = dSt;
    sp += 1;
  }
  ;
  while (sp > 0)
  {
    {
      if (!(sp < (100 - 2)))
      {
        BZ2_bz__AssertH__fail(1001);
      }
    }
    ;
    {
      sp -= 1;
      lo = stackLo[sp];
      hi = stackHi[sp];
      d = stackD[sp];
    }
    ;
    if (((hi - lo) < 20) || (d > (2 + 12)))
    {
      mainSimpleSort(ptr, block, quadrant, nblock, lo, hi, d, budget);
      if ((*budget) < 0)
      {
        return;
      }
      continue;
    }
    med = (Int32) mmed3(block[ptr[lo] + d], block[ptr[hi] + d], block[ptr[(lo + hi) >> 1] + d]);
    unLo = (ltLo = lo);
    unHi = (gtHi = hi);
    while ((Bool) 1)
    {
      while ((Bool) 1)
      {
        if (unLo > unHi)
        {
          break;
        }
        n = ((Int32) block[ptr[unLo] + d]) - med;
        if (n == 0)
        {
          {
            Int32 zztmp = ptr[unLo];
            ptr[unLo] = ptr[ltLo];
            ptr[ltLo] = zztmp;
          }
          ;
          ltLo += 1;
          unLo += 1;
          continue;
        }
        ;
        if (n > 0)
        {
          break;
        }
        unLo += 1;
      }

      while ((Bool) 1)
      {
        if (unLo > unHi)
        {
          break;
        }
        n = ((Int32) block[ptr[unHi] + d]) - med;
        if (n == 0)
        {
          {
            Int32 zztmp = ptr[unHi];
            ptr[unHi] = ptr[gtHi];
            ptr[gtHi] = zztmp;
          }
          ;
          gtHi -= 1;
          unHi -= 1;
          continue;
        }
        ;
        if (n < 0)
        {
          break;
        }
        unHi -= 1;
      }

      if (unLo > unHi)
      {
        break;
      }
      {
        Int32 zztmp = ptr[unLo];
        ptr[unLo] = ptr[unHi];
        ptr[unHi] = zztmp;
      }
      ;
      unLo += 1;
      unHi -= 1;
    }

    ;
    if (gtHi < ltLo)
    {
      {
        stackLo[sp] = lo;
        stackHi[sp] = hi;
        stackD[sp] = d + 1;
        sp += 1;
      }
      ;
      continue;
    }
    n = ((ltLo - lo) < (unLo - ltLo)) ? (ltLo - lo) : (unLo - ltLo);
    {
      Int32 yyp1 = lo;
      Int32 yyp2 = unLo - n;
      Int32 yyn = n;
      while (yyn > 0)
      {
        {
          Int32 zztmp = ptr[yyp1];
          ptr[yyp1] = ptr[yyp2];
          ptr[yyp2] = zztmp;
        }
        ;
        yyp1 += 1;
        yyp2 += 1;
        yyn -= 1;
      }

    }
    ;
    m = ((hi - gtHi) < (gtHi - unHi)) ? (hi - gtHi) : (gtHi - unHi);
    {
      Int32 yyp1 = unLo;
      Int32 yyp2 = (hi - m) + 1;
      Int32 yyn = m;
      while (yyn > 0)
      {
        {
          Int32 zztmp = ptr[yyp1];
          ptr[yyp1] = ptr[yyp2];
          ptr[yyp2] = zztmp;
        }
        ;
        yyp1 += 1;
        yyp2 += 1;
        yyn -= 1;
      }

    }
    ;
    n = ((lo + unLo) - ltLo) - 1;
    m = (hi - (gtHi - unHi)) + 1;
    nextLo[0] = lo;
    nextHi[0] = n;
    nextD[0] = d;
    nextLo[1] = m;
    nextHi[1] = hi;
    nextD[1] = d;
    nextLo[2] = n + 1;
    nextHi[2] = m - 1;
    nextD[2] = d + 1;
    if ((nextHi[0] - nextLo[0]) < (nextHi[1] - nextLo[1]))
    {
      Int32 tz;
      tz = nextLo[0];
      nextLo[0] = nextLo[1];
      nextLo[1] = tz;
      tz = nextHi[0];
      nextHi[0] = nextHi[1];
      nextHi[1] = tz;
      tz = nextD[0];
      nextD[0] = nextD[1];
      nextD[1] = tz;
    }
    ;
    if ((nextHi[1] - nextLo[1]) < (nextHi[2] - nextLo[2]))
    {
      Int32 tz;
      tz = nextLo[1];
      nextLo[1] = nextLo[2];
      nextLo[2] = tz;
      tz = nextHi[1];
      nextHi[1] = nextHi[2];
      nextHi[2] = tz;
      tz = nextD[1];
      nextD[1] = nextD[2];
      nextD[2] = tz;
    }
    ;
    if ((nextHi[0] - nextLo[0]) < (nextHi[1] - nextLo[1]))
    {
      Int32 tz;
      tz = nextLo[0];
      nextLo[0] = nextLo[1];
      nextLo[1] = tz;
      tz = nextHi[0];
      nextHi[0] = nextHi[1];
      nextHi[1] = tz;
      tz = nextD[0];
      nextD[0] = nextD[1];
      nextD[1] = tz;
    }
    ;
    ;
    ;
    {
      stackLo[sp] = nextLo[0];
      stackHi[sp] = nextHi[0];
      stackD[sp] = nextD[0];
      sp += 1;
    }
    ;
    {
      stackLo[sp] = nextLo[1];
      stackHi[sp] = nextHi[1];
      stackD[sp] = nextD[1];
      sp += 1;
    }
    ;
    {
      stackLo[sp] = nextLo[2];
      stackHi[sp] = nextHi[2];
      stackD[sp] = nextD[2];
      sp += 1;
    }
    ;
  }

}

static void mainSort(UInt32 *ptr, UChar *block, UInt16 *quadrant, UInt32 *ftab, Int32 nblock, Int32 verb, Int32 *budget)
{
  Int32 i;
  Int32 j;
  Int32 k;
  Int32 ss;
  Int32 sb;
  Int32 runningOrder[256];
  Bool bigDone[256];
  Int32 copyStart[256];
  Int32 copyEnd[256];
  UChar c1;
  Int32 numQSorted;
  UInt16 s;
  if (verb >= 4)
  {
    fprintf(stderr, "        main sort initialise ...\n");
  }
  for (i = 65536; i >= 0; i -= 1)
  {
    ftab[i] = 0;
  }

  j = block[0] << 8;
  i = nblock - 1;
  for (; i >= 3; i -= 4)
  {
    quadrant[i] = 0;
    j = (j >> 8) | (((UInt16) block[i]) << 8);
    ftab[j] += 1;
    quadrant[i - 1] = 0;
    j = (j >> 8) | (((UInt16) block[i - 1]) << 8);
    ftab[j] += 1;
    quadrant[i - 2] = 0;
    j = (j >> 8) | (((UInt16) block[i - 2]) << 8);
    ftab[j] += 1;
    quadrant[i - 3] = 0;
    j = (j >> 8) | (((UInt16) block[i - 3]) << 8);
    ftab[j] += 1;
  }

  for (; i >= 0; i -= 1)
  {
    quadrant[i] = 0;
    j = (j >> 8) | (((UInt16) block[i]) << 8);
    ftab[j] += 1;
  }

  for (i = 0; i < (((2 + 12) + 18) + 2); i += 1)
  {
    block[nblock + i] = block[i];
    quadrant[nblock + i] = 0;
  }

  if (verb >= 4)
  {
    fprintf(stderr, "        bucket sorting ...\n");
  }
  for (i = 1; i <= 65536; i += 1)
  {
    ftab[i] += ftab[i - 1];
  }

  s = block[0] << 8;
  i = nblock - 1;
  for (; i >= 3; i -= 4)
  {
    s = (s >> 8) | (block[i] << 8);
    j = ftab[s] - 1;
    ftab[s] = j;
    ptr[j] = i;
    s = (s >> 8) | (block[i - 1] << 8);
    j = ftab[s] - 1;
    ftab[s] = j;
    ptr[j] = i - 1;
    s = (s >> 8) | (block[i - 2] << 8);
    j = ftab[s] - 1;
    ftab[s] = j;
    ptr[j] = i - 2;
    s = (s >> 8) | (block[i - 3] << 8);
    j = ftab[s] - 1;
    ftab[s] = j;
    ptr[j] = i - 3;
  }

  for (; i >= 0; i -= 1)
  {
    s = (s >> 8) | (block[i] << 8);
    j = ftab[s] - 1;
    ftab[s] = j;
    ptr[j] = i;
  }

  for (i = 0; i <= 255; i += 1)
  {
    bigDone[i] = (Bool) 0;
    runningOrder[i] = i;
  }

  {
    Int32 vv;
    Int32 h = 1;
    do
    {
      h = (3 * h) + 1;
    }
    while (h <= 256);
    do
    {
      h = h / 3;
      for (i = h; i <= 255; i += 1)
      {
        vv = runningOrder[i];
        j = i;
        while ((ftab[(runningOrder[j - h] + 1) << 8] - ftab[runningOrder[j - h] << 8]) > (ftab[(vv + 1) << 8] - ftab[vv << 8]))
        {
          runningOrder[j] = runningOrder[j - h];
          j = j - h;
          if (j <= (h - 1))
          {
            goto zero;
          }
        }

        zero:
        runningOrder[j] = vv;

      }

    }
    while (h != 1);
  }
  numQSorted = 0;
  for (i = 0; i <= 255; i += 1)
  {
    ss = runningOrder[i];
    for (j = 0; j <= 255; j += 1)
    {
      if (j != ss)
      {
        sb = (ss << 8) + j;
        if (!(ftab[sb] & (1 << 21)))
        {
          Int32 lo = ftab[sb] & (~(1 << 21));
          Int32 hi = (ftab[sb + 1] & (~(1 << 21))) - 1;
          if (hi > lo)
          {
            if (verb >= 4)
            {
              fprintf(stderr, "        qsort [0x%x, 0x%x]   done %d   this %d\n", ss, j, numQSorted, (hi - lo) + 1);
            }
            mainQSort3(ptr, block, quadrant, nblock, lo, hi, 2, budget);
            numQSorted += (hi - lo) + 1;
            if ((*budget) < 0)
            {
              return;
            }
          }
        }
        ftab[sb] |= 1 << 21;
      }
    }

    {
      if (!(!bigDone[ss]))
      {
        BZ2_bz__AssertH__fail(1006);
      }
    }
    ;
    {
      for (j = 0; j <= 255; j += 1)
      {
        copyStart[j] = ftab[(j << 8) + ss] & (~(1 << 21));
        copyEnd[j] = (ftab[((j << 8) + ss) + 1] & (~(1 << 21))) - 1;
      }

      for (j = ftab[ss << 8] & (~(1 << 21)); j < copyStart[ss]; j += 1)
      {
        k = ptr[j] - 1;
        if (k < 0)
        {
          k += nblock;
        }
        c1 = block[k];
        if (!bigDone[c1])
        {
          ptr[copyStart[c1]++] = k;
        }
      }

      for (j = (ftab[(ss + 1) << 8] & (~(1 << 21))) - 1; j > copyEnd[ss]; j -= 1)
      {
        k = ptr[j] - 1;
        if (k < 0)
        {
          k += nblock;
        }
        c1 = block[k];
        if (!bigDone[c1])
        {
          ptr[copyEnd[c1]--] = k;
        }
      }

    }
    {
      if (!(((copyStart[ss] - 1) == copyEnd[ss]) || ((copyStart[ss] == 0) && (copyEnd[ss] == (nblock - 1)))))
      {
        BZ2_bz__AssertH__fail(1007);
      }
    }
    for (j = 0; j <= 255; j += 1)
    {
      ftab[(j << 8) + ss] |= 1 << 21;
    }

    bigDone[ss] = (Bool) 1;
    if (i < 255)
    {
      Int32 bbStart = ftab[ss << 8] & (~(1 << 21));
      Int32 bbSize = (ftab[(ss + 1) << 8] & (~(1 << 21))) - bbStart;
      Int32 shifts = 0;
      while ((bbSize >> shifts) > 65534)
      {
        shifts += 1;
      }

      for (j = bbSize - 1; j >= 0; j -= 1)
      {
        Int32 a2update = ptr[bbStart + j];
        UInt16 qVal = (UInt16) (j >> shifts);
        quadrant[a2update] = qVal;
        if (a2update < (((2 + 12) + 18) + 2))
        {
          quadrant[a2update + nblock] = qVal;
        }
      }

      {
        if (!(((bbSize - 1) >> shifts) <= 65535))
        {
          BZ2_bz__AssertH__fail(1002);
        }
      }
      ;
    }
  }

  if (verb >= 4)
  {
    fprintf(stderr, "        %d pointers, %d sorted, %d scanned\n", nblock, numQSorted, nblock - numQSorted);
  }
}

void BZ2_blockSort(EState *s)
{
  UInt32 *ptr = s->ptr;
  UChar *block = s->block;
  UInt32 *ftab = s->ftab;
  Int32 nblock = s->nblock;
  Int32 verb = s->verbosity;
  Int32 wfact = s->workFactor;
  UInt16 *quadrant;
  unsigned int quadrant_idx = 0;
  Int32 budget;
  Int32 budgetInit;
  Int32 i;
  if (nblock < 10000)
  {
    fallbackSort(s->arr1, s->arr2, ftab, nblock, verb);
  }
  else
  {
    i = nblock + (((2 + 12) + 18) + 2);
    if (i & 1)
    {
      i += 1;
    }
    quadrant_idx = (UInt16 *) (&block[i]);
    if (wfact < 1)
    {
      wfact = 1;
    }
    if (wfact > 100)
    {
      wfact = 100;
    }
    budgetInit = nblock * ((wfact - 1) / 3);
    budget = budgetInit;
    mainSort(ptr, block, quadrant, ftab, nblock, verb, &budget);
    if (verb >= 3)
    {
      fprintf(stderr, "      %d work, %d block, ratio %5.2f\n", budgetInit - budget, nblock, ((float) (budgetInit - budget)) / ((float) ((nblock == 0) ? (1) : (nblock))));
    }
    if (budget < 0)
    {
      if (verb >= 2)
      {
        fprintf(stderr, "    too repetitive; using fallback sorting algorithm\n");
      }
      fallbackSort(s->arr1, s->arr2, ftab, nblock, verb);
    }
  }
  s->origPtr = -1;
  for (i = 0; i < s->nblock; i += 1)
  {
    if (ptr[i] == 0)
    {
      s->origPtr = i;
      break;
    }
  }

  ;
  {
    if (!(s->origPtr != (-1)))
    {
      BZ2_bz__AssertH__fail(1003);
    }
  }
  ;
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
static void fallbackSimpleSort(UInt32 *fmap, UInt32 *eclass, Int32 lo, Int32 hi)
{
  Int32 i;
  Int32 j;
  Int32 tmp;
  UInt32 ec_tmp;
  if (lo == hi)
  {
    return;
  }
  if ((hi - lo) > 3)
  {
    for (i = hi - 4; i >= lo; i -= 1)
    {
      tmp = fmap[i];
      ec_tmp = eclass[tmp];
      for (j = i + 4; (j <= hi) && (ec_tmp > eclass[fmap[j]]); j += 4)
      {
        fmap[j - 4] = fmap[j];
      }

      fmap[j - 4] = tmp;
    }

  }
  for (i = hi - 1; i >= lo; i -= 1)
  {
    tmp = fmap[i];
    ec_tmp = eclass[tmp];
    for (j = i + 1; (j <= hi) && (ec_tmp > eclass[fmap[j]]); j += 1)
    {
      fmap[j - 1] = fmap[j];
    }

    fmap[j - 1] = tmp;
  }

}

static void fallbackQSort3(UInt32 *fmap, UInt32 *eclass, Int32 loSt, Int32 hiSt)
{
  Int32 unLo;
  Int32 unHi;
  Int32 ltLo;
  Int32 gtHi;
  Int32 n;
  Int32 m;
  Int32 sp;
  Int32 lo;
  Int32 hi;
  UInt32 med;
  UInt32 r;
  UInt32 r3;
  Int32 stackLo[100];
  Int32 stackHi[100];
  r = 0;
  sp = 0;
  {
    stackLo[sp] = loSt;
    stackHi[sp] = hiSt;
    sp += 1;
  }
  ;
  while (sp > 0)
  {
    {
      if (!(sp < (100 - 1)))
      {
        BZ2_bz__AssertH__fail(1004);
      }
    }
    ;
    {
      sp -= 1;
      lo = stackLo[sp];
      hi = stackHi[sp];
    }
    ;
    if ((hi - lo) < 10)
    {
      fallbackSimpleSort(fmap, eclass, lo, hi);
      continue;
    }
    r = ((r * 7621) + 1) % 32768;
    r3 = r % 3;
    if (r3 == 0)
    {
      med = eclass[fmap[lo]];
    }
    else
      if (r3 == 1)
    {
      med = eclass[fmap[(lo + hi) >> 1]];
    }
    else
      med = eclass[fmap[hi]];
    unLo = (ltLo = lo);
    unHi = (gtHi = hi);
    while (1)
    {
      while (1)
      {
        if (unLo > unHi)
        {
          break;
        }
        n = ((Int32) eclass[fmap[unLo]]) - ((Int32) med);
        if (n == 0)
        {
          {
            Int32 zztmp = fmap[unLo];
            fmap[unLo] = fmap[ltLo];
            fmap[ltLo] = zztmp;
          }
          ;
          ltLo += 1;
          unLo += 1;
          continue;
        }
        ;
        if (n > 0)
        {
          break;
        }
        unLo += 1;
      }

      while (1)
      {
        if (unLo > unHi)
        {
          break;
        }
        n = ((Int32) eclass[fmap[unHi]]) - ((Int32) med);
        if (n == 0)
        {
          {
            Int32 zztmp = fmap[unHi];
            fmap[unHi] = fmap[gtHi];
            fmap[gtHi] = zztmp;
          }
          ;
          gtHi -= 1;
          unHi -= 1;
          continue;
        }
        ;
        if (n < 0)
        {
          break;
        }
        unHi -= 1;
      }

      if (unLo > unHi)
      {
        break;
      }
      {
        Int32 zztmp = fmap[unLo];
        fmap[unLo] = fmap[unHi];
        fmap[unHi] = zztmp;
      }
      ;
      unLo += 1;
      unHi -= 1;
    }

    ;
    if (gtHi < ltLo)
    {
      continue;
    }
    n = ((ltLo - lo) < (unLo - ltLo)) ? (ltLo - lo) : (unLo - ltLo);
    {
      Int32 yyp1 = lo;
      Int32 yyp2 = unLo - n;
      Int32 yyn = n;
      while (yyn > 0)
      {
        {
          Int32 zztmp = fmap[yyp1];
          fmap[yyp1] = fmap[yyp2];
          fmap[yyp2] = zztmp;
        }
        ;
        yyp1 += 1;
        yyp2 += 1;
        yyn -= 1;
      }

    }
    ;
    m = ((hi - gtHi) < (gtHi - unHi)) ? (hi - gtHi) : (gtHi - unHi);
    {
      Int32 yyp1 = unLo;
      Int32 yyp2 = (hi - m) + 1;
      Int32 yyn = m;
      while (yyn > 0)
      {
        {
          Int32 zztmp = fmap[yyp1];
          fmap[yyp1] = fmap[yyp2];
          fmap[yyp2] = zztmp;
        }
        ;
        yyp1 += 1;
        yyp2 += 1;
        yyn -= 1;
      }

    }
    ;
    n = ((lo + unLo) - ltLo) - 1;
    m = (hi - (gtHi - unHi)) + 1;
    if ((n - lo) > (hi - m))
    {
      {
        stackLo[sp] = lo;
        stackHi[sp] = n;
        sp += 1;
      }
      ;
      {
        stackLo[sp] = m;
        stackHi[sp] = hi;
        sp += 1;
      }
      ;
    }
    else
    {
      {
        stackLo[sp] = m;
        stackHi[sp] = hi;
        sp += 1;
      }
      ;
      {
        stackLo[sp] = lo;
        stackHi[sp] = n;
        sp += 1;
      }
      ;
    }
  }

}

static void fallbackSort(UInt32 *fmap, UInt32 *eclass, UInt32 *bhtab, Int32 nblock, Int32 verb)
{
  Int32 ftab[257];
  Int32 ftabCopy[256];
  Int32 H;
  Int32 i;
  Int32 j;
  Int32 k;
  Int32 l;
  Int32 r;
  Int32 cc;
  Int32 cc1;
  Int32 nNotDone;
  Int32 nBhtab;
  UChar *eclass8 = (UChar *) eclass;
  if (verb >= 4)
  {
    fprintf(stderr, "        bucket sorting ...\n");
  }
  for (i = 0; i < 257; i += 1)
  {
    ftab[i] = 0;
  }

  for (i = 0; i < nblock; i += 1)
  {
    ftab[eclass8[i]] += 1;
  }

  for (i = 0; i < 256; i += 1)
  {
    ftabCopy[i] = ftab[i];
  }

  for (i = 1; i < 257; i += 1)
  {
    ftab[i] += ftab[i - 1];
  }

  for (i = 0; i < nblock; i += 1)
  {
    j = eclass8[i];
    k = ftab[j] - 1;
    ftab[j] = k;
    fmap[k] = i;
  }

  nBhtab = 2 + (nblock / 32);
  for (i = 0; i < nBhtab; i += 1)
  {
    bhtab[i] = 0;
  }

  for (i = 0; i < 256; i += 1)
  {
    bhtab[ftab[i] >> 5] |= ((UInt32) 1) << (ftab[i] & 31);
  }

  for (i = 0; i < 32; i += 1)
  {
    bhtab[(nblock + (2 * i)) >> 5] |= ((UInt32) 1) << ((nblock + (2 * i)) & 31);
    bhtab[((nblock + (2 * i)) + 1) >> 5] &= ~(((UInt32) 1) << (((nblock + (2 * i)) + 1) & 31));
  }

  H = 1;
  while (1)
  {
    if (verb >= 4)
    {
      fprintf(stderr, "        depth %6d has ", H);
    }
    j = 0;
    for (i = 0; i < nblock; i += 1)
    {
      if (bhtab[i >> 5] & (((UInt32) 1) << (i & 31)))
      {
        j = i;
      }
      k = fmap[i] - H;
      if (k < 0)
      {
        k += nblock;
      }
      eclass[k] = j;
    }

    nNotDone = 0;
    r = -1;
    while (1)
    {
      k = r + 1;
      while ((bhtab[k >> 5] & (((UInt32) 1) << (k & 31))) && (k & 0x01f))
      {
        k += 1;
      }

      if (bhtab[k >> 5] & (((UInt32) 1) << (k & 31)))
      {
        while (bhtab[k >> 5] == 0xffffffff)
        {
          k += 32;
        }

        while (bhtab[k >> 5] & (((UInt32) 1) << (k & 31)))
        {
          k += 1;
        }

      }
      l = k - 1;
      if (l >= nblock)
      {
        break;
      }
      while ((!(bhtab[k >> 5] & (((UInt32) 1) << (k & 31)))) && (k & 0x01f))
      {
        k += 1;
      }

      if (!(bhtab[k >> 5] & (((UInt32) 1) << (k & 31))))
      {
        while (bhtab[k >> 5] == 0x00000000)
        {
          k += 32;
        }

        while (!(bhtab[k >> 5] & (((UInt32) 1) << (k & 31))))
        {
          k += 1;
        }

      }
      r = k - 1;
      if (r >= nblock)
      {
        break;
      }
      if (r > l)
      {
        nNotDone += (r - l) + 1;
        fallbackQSort3(fmap, eclass, l, r);
        cc = -1;
        for (i = l; i <= r; i += 1)
        {
          cc1 = eclass[fmap[i]];
          if (cc != cc1)
          {
            bhtab[i >> 5] |= ((UInt32) 1) << (i & 31);
            cc = cc1;
          }
          ;
        }

      }
    }

    if (verb >= 4)
    {
      fprintf(stderr, "%6d unresolved strings\n", nNotDone);
    }
    H *= 2;
    if ((H > nblock) || (nNotDone == 0))
    {
      break;
    }
  }

  if (verb >= 4)
  {
    fprintf(stderr, "        reconstructing block ...\n");
  }
  j = 0;
  for (i = 0; i < nblock; i += 1)
  {
    while (ftabCopy[j] == 0)
    {
      j += 1;
    }

    ftabCopy[j] -= 1;
    eclass8[fmap[i]] = (UChar) j;
  }

  {
    if (!(j < 256))
    {
      BZ2_bz__AssertH__fail(1005);
    }
  }
  ;
}

static Bool mainGtU(UInt32 i1, UInt32 i2, UChar *block, UInt16 *quadrant, UInt32 nblock, Int32 *budget)
{
  Int32 k;
  UChar c1;
  UChar c2;
  UInt16 s1;
  UInt16 s2;
  ;
  c1 = block[i1];
  c2 = block[i2];
  if (c1 != c2)
  {
    return c1 > c2;
  }
  i1 += 1;
  i2 += 1;
  c1 = block[i1];
  c2 = block[i2];
  if (c1 != c2)
  {
    return c1 > c2;
  }
  i1 += 1;
  i2 += 1;
  c1 = block[i1];
  c2 = block[i2];
  if (c1 != c2)
  {
    return c1 > c2;
  }
  i1 += 1;
  i2 += 1;
  c1 = block[i1];
  c2 = block[i2];
  if (c1 != c2)
  {
    return c1 > c2;
  }
  i1 += 1;
  i2 += 1;
  c1 = block[i1];
  c2 = block[i2];
  if (c1 != c2)
  {
    return c1 > c2;
  }
  i1 += 1;
  i2 += 1;
  c1 = block[i1];
  c2 = block[i2];
  if (c1 != c2)
  {
    return c1 > c2;
  }
  i1 += 1;
  i2 += 1;
  c1 = block[i1];
  c2 = block[i2];
  if (c1 != c2)
  {
    return c1 > c2;
  }
  i1 += 1;
  i2 += 1;
  c1 = block[i1];
  c2 = block[i2];
  if (c1 != c2)
  {
    return c1 > c2;
  }
  i1 += 1;
  i2 += 1;
  c1 = block[i1];
  c2 = block[i2];
  if (c1 != c2)
  {
    return c1 > c2;
  }
  i1 += 1;
  i2 += 1;
  c1 = block[i1];
  c2 = block[i2];
  if (c1 != c2)
  {
    return c1 > c2;
  }
  i1 += 1;
  i2 += 1;
  c1 = block[i1];
  c2 = block[i2];
  if (c1 != c2)
  {
    return c1 > c2;
  }
  i1 += 1;
  i2 += 1;
  c1 = block[i1];
  c2 = block[i2];
  if (c1 != c2)
  {
    return c1 > c2;
  }
  i1 += 1;
  i2 += 1;
  k = nblock + 8;
  do
  {
    c1 = block[i1];
    c2 = block[i2];
    if (c1 != c2)
    {
      return c1 > c2;
    }
    s1 = quadrant[i1];
    s2 = quadrant[i2];
    if (s1 != s2)
    {
      return s1 > s2;
    }
    i1 += 1;
    i2 += 1;
    c1 = block[i1];
    c2 = block[i2];
    if (c1 != c2)
    {
      return c1 > c2;
    }
    s1 = quadrant[i1];
    s2 = quadrant[i2];
    if (s1 != s2)
    {
      return s1 > s2;
    }
    i1 += 1;
    i2 += 1;
    c1 = block[i1];
    c2 = block[i2];
    if (c1 != c2)
    {
      return c1 > c2;
    }
    s1 = quadrant[i1];
    s2 = quadrant[i2];
    if (s1 != s2)
    {
      return s1 > s2;
    }
    i1 += 1;
    i2 += 1;
    c1 = block[i1];
    c2 = block[i2];
    if (c1 != c2)
    {
      return c1 > c2;
    }
    s1 = quadrant[i1];
    s2 = quadrant[i2];
    if (s1 != s2)
    {
      return s1 > s2;
    }
    i1 += 1;
    i2 += 1;
    c1 = block[i1];
    c2 = block[i2];
    if (c1 != c2)
    {
      return c1 > c2;
    }
    s1 = quadrant[i1];
    s2 = quadrant[i2];
    if (s1 != s2)
    {
      return s1 > s2;
    }
    i1 += 1;
    i2 += 1;
    c1 = block[i1];
    c2 = block[i2];
    if (c1 != c2)
    {
      return c1 > c2;
    }
    s1 = quadrant[i1];
    s2 = quadrant[i2];
    if (s1 != s2)
    {
      return s1 > s2;
    }
    i1 += 1;
    i2 += 1;
    c1 = block[i1];
    c2 = block[i2];
    if (c1 != c2)
    {
      return c1 > c2;
    }
    s1 = quadrant[i1];
    s2 = quadrant[i2];
    if (s1 != s2)
    {
      return s1 > s2;
    }
    i1 += 1;
    i2 += 1;
    c1 = block[i1];
    c2 = block[i2];
    if (c1 != c2)
    {
      return c1 > c2;
    }
    s1 = quadrant[i1];
    s2 = quadrant[i2];
    if (s1 != s2)
    {
      return s1 > s2;
    }
    i1 += 1;
    i2 += 1;
    if (i1 >= nblock)
    {
      i1 -= nblock;
    }
    if (i2 >= nblock)
    {
      i2 -= nblock;
    }
    k -= 8;
    *budget -= 1;
  }
  while (k >= 0);
  return (Bool) 0;
}

static Int32 incs[14] = {1, 4, 13, 40, 121, 364, 1093, 3280, 9841, 29524, 88573, 265720, 797161, 2391484};
static void mainSimpleSort(UInt32 *ptr, UChar *block, UInt16 *quadrant, Int32 nblock, Int32 lo, Int32 hi, Int32 d, Int32 *budget)
{
  Int32 i;
  Int32 j;
  Int32 h;
  Int32 bigN;
  Int32 hp;
  UInt32 v;
  bigN = (hi - lo) + 1;
  if (bigN < 2)
  {
    return;
  }
  hp = 0;
  while (incs[hp] < bigN)
  {
    hp += 1;
  }

  hp -= 1;
  for (; hp >= 0; hp -= 1)
  {
    h = incs[hp];
    i = lo + h;
    while ((Bool) 1)
    {
      if (i > hi)
      {
        break;
      }
      v = ptr[i];
      j = i;
      while (mainGtU(ptr[j - h] + d, v + d, block, quadrant, nblock, budget))
      {
        ptr[j] = ptr[j - h];
        j = j - h;
        if (j <= ((lo + h) - 1))
        {
          break;
        }
      }

      ptr[j] = v;
      i += 1;
      if (i > hi)
      {
        break;
      }
      v = ptr[i];
      j = i;
      while (mainGtU(ptr[j - h] + d, v + d, block, quadrant, nblock, budget))
      {
        ptr[j] = ptr[j - h];
        j = j - h;
        if (j <= ((lo + h) - 1))
        {
          break;
        }
      }

      ptr[j] = v;
      i += 1;
      if (i > hi)
      {
        break;
      }
      v = ptr[i];
      j = i;
      while (mainGtU(ptr[j - h] + d, v + d, block, quadrant, nblock, budget))
      {
        ptr[j] = ptr[j - h];
        j = j - h;
        if (j <= ((lo + h) - 1))
        {
          break;
        }
      }

      ptr[j] = v;
      i += 1;
      if ((*budget) < 0)
      {
        return;
      }
    }

  }

}

static UChar mmed3(UChar a, UChar b, UChar c)
{
  UChar t;
  if (a > b)
  {
    t = a;
    a = b;
    b = t;
  }
  ;
  if (b > c)
  {
    b = c;
    if (a > b)
    {
      b = a;
    }
  }
  return b;
}

static void mainQSort3(UInt32 *ptr, UChar *block, UInt16 *quadrant, Int32 nblock, Int32 loSt, Int32 hiSt, Int32 dSt, Int32 *budget)
{
  Int32 unLo;
  Int32 unHi;
  Int32 ltLo;
  Int32 gtHi;
  Int32 n;
  Int32 m;
  Int32 med;
  Int32 sp;
  Int32 lo;
  Int32 hi;
  Int32 d;
  Int32 stackLo[100];
  Int32 stackHi[100];
  Int32 stackD[100];
  Int32 nextLo[3];
  Int32 nextHi[3];
  Int32 nextD[3];
  sp = 0;
  {
    stackLo[sp] = loSt;
    stackHi[sp] = hiSt;
    stackD[sp] = dSt;
    sp += 1;
  }
  ;
  while (sp > 0)
  {
    {
      if (!(sp < (100 - 2)))
      {
        BZ2_bz__AssertH__fail(1001);
      }
    }
    ;
    {
      sp -= 1;
      lo = stackLo[sp];
      hi = stackHi[sp];
      d = stackD[sp];
    }
    ;
    if (((hi - lo) < 20) || (d > (2 + 12)))
    {
      mainSimpleSort(ptr, block, quadrant, nblock, lo, hi, d, budget);
      if ((*budget) < 0)
      {
        return;
      }
      continue;
    }
    med = (Int32) mmed3(block[ptr[lo] + d], block[ptr[hi] + d], block[ptr[(lo + hi) >> 1] + d]);
    unLo = (ltLo = lo);
    unHi = (gtHi = hi);
    while ((Bool) 1)
    {
      while ((Bool) 1)
      {
        if (unLo > unHi)
        {
          break;
        }
        n = ((Int32) block[ptr[unLo] + d]) - med;
        if (n == 0)
        {
          {
            Int32 zztmp = ptr[unLo];
            ptr[unLo] = ptr[ltLo];
            ptr[ltLo] = zztmp;
          }
          ;
          ltLo += 1;
          unLo += 1;
          continue;
        }
        ;
        if (n > 0)
        {
          break;
        }
        unLo += 1;
      }

      while ((Bool) 1)
      {
        if (unLo > unHi)
        {
          break;
        }
        n = ((Int32) block[ptr[unHi] + d]) - med;
        if (n == 0)
        {
          {
            Int32 zztmp = ptr[unHi];
            ptr[unHi] = ptr[gtHi];
            ptr[gtHi] = zztmp;
          }
          ;
          gtHi -= 1;
          unHi -= 1;
          continue;
        }
        ;
        if (n < 0)
        {
          break;
        }
        unHi -= 1;
      }

      if (unLo > unHi)
      {
        break;
      }
      {
        Int32 zztmp = ptr[unLo];
        ptr[unLo] = ptr[unHi];
        ptr[unHi] = zztmp;
      }
      ;
      unLo += 1;
      unHi -= 1;
    }

    ;
    if (gtHi < ltLo)
    {
      {
        stackLo[sp] = lo;
        stackHi[sp] = hi;
        stackD[sp] = d + 1;
        sp += 1;
      }
      ;
      continue;
    }
    n = ((ltLo - lo) < (unLo - ltLo)) ? (ltLo - lo) : (unLo - ltLo);
    {
      Int32 yyp1 = lo;
      Int32 yyp2 = unLo - n;
      Int32 yyn = n;
      while (yyn > 0)
      {
        {
          Int32 zztmp = ptr[yyp1];
          ptr[yyp1] = ptr[yyp2];
          ptr[yyp2] = zztmp;
        }
        ;
        yyp1 += 1;
        yyp2 += 1;
        yyn -= 1;
      }

    }
    ;
    m = ((hi - gtHi) < (gtHi - unHi)) ? (hi - gtHi) : (gtHi - unHi);
    {
      Int32 yyp1 = unLo;
      Int32 yyp2 = (hi - m) + 1;
      Int32 yyn = m;
      while (yyn > 0)
      {
        {
          Int32 zztmp = ptr[yyp1];
          ptr[yyp1] = ptr[yyp2];
          ptr[yyp2] = zztmp;
        }
        ;
        yyp1 += 1;
        yyp2 += 1;
        yyn -= 1;
      }

    }
    ;
    n = ((lo + unLo) - ltLo) - 1;
    m = (hi - (gtHi - unHi)) + 1;
    nextLo[0] = lo;
    nextHi[0] = n;
    nextD[0] = d;
    nextLo[1] = m;
    nextHi[1] = hi;
    nextD[1] = d;
    nextLo[2] = n + 1;
    nextHi[2] = m - 1;
    nextD[2] = d + 1;
    if ((nextHi[0] - nextLo[0]) < (nextHi[1] - nextLo[1]))
    {
      Int32 tz;
      tz = nextLo[0];
      nextLo[0] = nextLo[1];
      nextLo[1] = tz;
      tz = nextHi[0];
      nextHi[0] = nextHi[1];
      nextHi[1] = tz;
      tz = nextD[0];
      nextD[0] = nextD[1];
      nextD[1] = tz;
    }
    ;
    if ((nextHi[1] - nextLo[1]) < (nextHi[2] - nextLo[2]))
    {
      Int32 tz;
      tz = nextLo[1];
      nextLo[1] = nextLo[2];
      nextLo[2] = tz;
      tz = nextHi[1];
      nextHi[1] = nextHi[2];
      nextHi[2] = tz;
      tz = nextD[1];
      nextD[1] = nextD[2];
      nextD[2] = tz;
    }
    ;
    if ((nextHi[0] - nextLo[0]) < (nextHi[1] - nextLo[1]))
    {
      Int32 tz;
      tz = nextLo[0];
      nextLo[0] = nextLo[1];
      nextLo[1] = tz;
      tz = nextHi[0];
      nextHi[0] = nextHi[1];
      nextHi[1] = tz;
      tz = nextD[0];
      nextD[0] = nextD[1];
      nextD[1] = tz;
    }
    ;
    ;
    ;
    {
      stackLo[sp] = nextLo[0];
      stackHi[sp] = nextHi[0];
      stackD[sp] = nextD[0];
      sp += 1;
    }
    ;
    {
      stackLo[sp] = nextLo[1];
      stackHi[sp] = nextHi[1];
      stackD[sp] = nextD[1];
      sp += 1;
    }
    ;
    {
      stackLo[sp] = nextLo[2];
      stackHi[sp] = nextHi[2];
      stackD[sp] = nextD[2];
      sp += 1;
    }
    ;
  }

}

static void mainSort(UInt32 *ptr, UChar *block, UInt16 *quadrant, UInt32 *ftab, Int32 nblock, Int32 verb, Int32 *budget)
{
  Int32 i;
  Int32 j;
  Int32 k;
  Int32 ss;
  Int32 sb;
  Int32 runningOrder[256];
  Bool bigDone[256];
  Int32 copyStart[256];
  Int32 copyEnd[256];
  UChar c1;
  Int32 numQSorted;
  UInt16 s;
  if (verb >= 4)
  {
    fprintf(stderr, "        main sort initialise ...\n");
  }
  for (i = 65536; i >= 0; i -= 1)
  {
    ftab[i] = 0;
  }

  j = block[0] << 8;
  i = nblock - 1;
  for (; i >= 3; i -= 4)
  {
    quadrant[i] = 0;
    j = (j >> 8) | (((UInt16) block[i]) << 8);
    ftab[j] += 1;
    quadrant[i - 1] = 0;
    j = (j >> 8) | (((UInt16) block[i - 1]) << 8);
    ftab[j] += 1;
    quadrant[i - 2] = 0;
    j = (j >> 8) | (((UInt16) block[i - 2]) << 8);
    ftab[j] += 1;
    quadrant[i - 3] = 0;
    j = (j >> 8) | (((UInt16) block[i - 3]) << 8);
    ftab[j] += 1;
  }

  for (; i >= 0; i -= 1)
  {
    quadrant[i] = 0;
    j = (j >> 8) | (((UInt16) block[i]) << 8);
    ftab[j] += 1;
  }

  for (i = 0; i < (((2 + 12) + 18) + 2); i += 1)
  {
    block[nblock + i] = block[i];
    quadrant[nblock + i] = 0;
  }

  if (verb >= 4)
  {
    fprintf(stderr, "        bucket sorting ...\n");
  }
  for (i = 1; i <= 65536; i += 1)
  {
    ftab[i] += ftab[i - 1];
  }

  s = block[0] << 8;
  i = nblock - 1;
  for (; i >= 3; i -= 4)
  {
    s = (s >> 8) | (block[i] << 8);
    j = ftab[s] - 1;
    ftab[s] = j;
    ptr[j] = i;
    s = (s >> 8) | (block[i - 1] << 8);
    j = ftab[s] - 1;
    ftab[s] = j;
    ptr[j] = i - 1;
    s = (s >> 8) | (block[i - 2] << 8);
    j = ftab[s] - 1;
    ftab[s] = j;
    ptr[j] = i - 2;
    s = (s >> 8) | (block[i - 3] << 8);
    j = ftab[s] - 1;
    ftab[s] = j;
    ptr[j] = i - 3;
  }

  for (; i >= 0; i -= 1)
  {
    s = (s >> 8) | (block[i] << 8);
    j = ftab[s] - 1;
    ftab[s] = j;
    ptr[j] = i;
  }

  for (i = 0; i <= 255; i += 1)
  {
    bigDone[i] = (Bool) 0;
    runningOrder[i] = i;
  }

  {
    Int32 vv;
    Int32 h = 1;
    do
    {
      h = (3 * h) + 1;
    }
    while (h <= 256);
    do
    {
      h = h / 3;
      for (i = h; i <= 255; i += 1)
      {
        vv = runningOrder[i];
        j = i;
        while ((ftab[(runningOrder[j - h] + 1) << 8] - ftab[runningOrder[j - h] << 8]) > (ftab[(vv + 1) << 8] - ftab[vv << 8]))
        {
          runningOrder[j] = runningOrder[j - h];
          j = j - h;
          if (j <= (h - 1))
          {
            goto zero;
          }
        }

        zero:
        runningOrder[j] = vv;

      }

    }
    while (h != 1);
  }
  numQSorted = 0;
  for (i = 0; i <= 255; i += 1)
  {
    ss = runningOrder[i];
    for (j = 0; j <= 255; j += 1)
    {
      if (j != ss)
      {
        sb = (ss << 8) + j;
        if (!(ftab[sb] & (1 << 21)))
        {
          Int32 lo = ftab[sb] & (~(1 << 21));
          Int32 hi = (ftab[sb + 1] & (~(1 << 21))) - 1;
          if (hi > lo)
          {
            if (verb >= 4)
            {
              fprintf(stderr, "        qsort [0x%x, 0x%x]   done %d   this %d\n", ss, j, numQSorted, (hi - lo) + 1);
            }
            mainQSort3(ptr, block, quadrant, nblock, lo, hi, 2, budget);
            numQSorted += (hi - lo) + 1;
            if ((*budget) < 0)
            {
              return;
            }
          }
        }
        ftab[sb] |= 1 << 21;
      }
    }

    {
      if (!(!bigDone[ss]))
      {
        BZ2_bz__AssertH__fail(1006);
      }
    }
    ;
    {
      for (j = 0; j <= 255; j += 1)
      {
        copyStart[j] = ftab[(j << 8) + ss] & (~(1 << 21));
        copyEnd[j] = (ftab[((j << 8) + ss) + 1] & (~(1 << 21))) - 1;
      }

      for (j = ftab[ss << 8] & (~(1 << 21)); j < copyStart[ss]; j += 1)
      {
        k = ptr[j] - 1;
        if (k < 0)
        {
          k += nblock;
        }
        c1 = block[k];
        if (!bigDone[c1])
        {
          ptr[copyStart[c1]++] = k;
        }
      }

      for (j = (ftab[(ss + 1) << 8] & (~(1 << 21))) - 1; j > copyEnd[ss]; j -= 1)
      {
        k = ptr[j] - 1;
        if (k < 0)
        {
          k += nblock;
        }
        c1 = block[k];
        if (!bigDone[c1])
        {
          ptr[copyEnd[c1]--] = k;
        }
      }

    }
    {
      if (!(((copyStart[ss] - 1) == copyEnd[ss]) || ((copyStart[ss] == 0) && (copyEnd[ss] == (nblock - 1)))))
      {
        BZ2_bz__AssertH__fail(1007);
      }
    }
    for (j = 0; j <= 255; j += 1)
    {
      ftab[(j << 8) + ss] |= 1 << 21;
    }

    bigDone[ss] = (Bool) 1;
    if (i < 255)
    {
      Int32 bbStart = ftab[ss << 8] & (~(1 << 21));
      Int32 bbSize = (ftab[(ss + 1) << 8] & (~(1 << 21))) - bbStart;
      Int32 shifts = 0;
      while ((bbSize >> shifts) > 65534)
      {
        shifts += 1;
      }

      for (j = bbSize - 1; j >= 0; j -= 1)
      {
        Int32 a2update = ptr[bbStart + j];
        UInt16 qVal = (UInt16) (j >> shifts);
        quadrant[a2update] = qVal;
        if (a2update < (((2 + 12) + 18) + 2))
        {
          quadrant[a2update + nblock] = qVal;
        }
      }

      {
        if (!(((bbSize - 1) >> shifts) <= 65535))
        {
          BZ2_bz__AssertH__fail(1002);
        }
      }
      ;
    }
  }

  if (verb >= 4)
  {
    fprintf(stderr, "        %d pointers, %d sorted, %d scanned\n", nblock, numQSorted, nblock - numQSorted);
  }
}

void BZ2_blockSort(EState *s)
{
  UInt32 *ptr = s->ptr;
  UChar *block = s->block;
  UInt32 *ftab = s->ftab;
  Int32 nblock = s->nblock;
  Int32 verb = s->verbosity;
  Int32 wfact = s->workFactor;
  UInt16 *quadrant;
  unsigned int quadrant_idx = 0;
  Int32 budget;
  Int32 budgetInit;
  Int32 i;
  if (nblock < 10000)
  {
    fallbackSort(s->arr1, s->arr2, ftab, nblock, verb);
  }
  else
  {
    i = nblock + (((2 + 12) + 18) + 2);
    if (i & 1)
    {
      i += 1;
    }
    quadrant_idx = (UInt16 *) (&block[i]);
    if (wfact < 1)
    {
      wfact = 1;
    }
    if (wfact > 100)
    {
      wfact = 100;
    }
    budgetInit = nblock * ((wfact - 1) / 3);
    budget = budgetInit;
    mainSort(ptr, block, quadrant, ftab, nblock, verb, &budget);
    if (verb >= 3)
    {
      fprintf(stderr, "      %d work, %d block, ratio %5.2f\n", budgetInit - budget, nblock, ((float) (budgetInit - budget)) / ((float) ((nblock == 0) ? (1) : (nblock))));
    }
    if (budget < 0)
    {
      if (verb >= 2)
      {
        fprintf(stderr, "    too repetitive; using fallback sorting algorithm\n");
      }
      fallbackSort(s->arr1, s->arr2, ftab, nblock, verb);
    }
  }
  s->origPtr = -1;
  for (i = 0; i < s->nblock; i += 1)
  {
    if (ptr[i] == 0)
    {
      s->origPtr = i;
      break;
    }
  }

  ;
  {
    if (!(s->origPtr != (-1)))
    {
      BZ2_bz__AssertH__fail(1003);
    }
  }
  ;
}

