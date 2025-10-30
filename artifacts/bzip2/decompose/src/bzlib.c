const char *BZ2_bzlibVersion(void)
{
  return "1.1.0";
}


/*** DEPENDENCIES:
***/


static int bz_config_ok(void)
{
  if ((sizeof(int)) != 4)
  {
    return 0;
  }
  if ((sizeof(short)) != 2)
  {
    return 0;
  }
  if ((sizeof(char)) != 1)
  {
    return 0;
  }
  return 1;
}


/*** DEPENDENCIES:
***/


static void default_bzfree(void *opaque, void *addr)
{
  if (addr != 0)
  {
    free(addr);
  }
}


/*** DEPENDENCIES:
***/


static void *default_bzalloc(void *opaque, Int32 items, Int32 size)
{
  void *v = malloc(items * size);
  return v;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
***/


int BZ2_bzDecompressInit(bz_stream *strm, int verbosity, int small)
{
  DState *s;
  unsigned int s_idx = 0;
  if (!bz_config_ok())
  {
    return -9;
  }
  if (strm == 0)
  {
    return -2;
  }
  if ((small != 0) && (small != 1))
  {
    return -2;
  }
  if ((verbosity < 0) || (verbosity > 4))
  {
    return -2;
  }
  if (strm->bzalloc == 0)
  {
    strm->bzalloc = default_bzalloc;
  }
  if (strm->bzfree == 0)
  {
    strm->bzfree = default_bzfree;
  }
  s_idx = strm->bzalloc(strm->opaque, sizeof(DState), 1);
  if ((&s[s_idx]) == 0)
  {
    return -3;
  }
  s->strm = strm;
  strm->state = &s[s_idx];
  s->state = 10;
  s->bsLive = 0;
  s->bsBuff = 0;
  s->calculatedCombinedCRC = 0;
  strm->total_in_lo32 = 0;
  strm->total_in_hi32 = 0;
  strm->total_out_lo32 = 0;
  strm->total_out_hi32 = 0;
  s->smallDecompress = (Bool) small;
  s->ll4 = 0;
  s->ll16 = 0;
  s->tt = 0;
  s->currBlockNo = 0;
  s->verbosity = verbosity;
  return 0;
}


/*** DEPENDENCIES:
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
} bz_stream
----------------------------
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
} DState
----------------------------
static int bz_config_ok(void)
{
  if ((sizeof(int)) != 4)
  {
    return 0;
  }
  if ((sizeof(short)) != 2)
  {
    return 0;
  }
  if ((sizeof(char)) != 1)
  {
    return 0;
  }
  return 1;
}


----------------------------
static void default_bzfree(void *opaque, void *addr)
{
  if (addr != 0)
  {
    free(addr);
  }
}


----------------------------
static void *default_bzalloc(void *opaque, Int32 items, Int32 size)
{
  void *v = malloc(items * size);
  return v;
}


----------------------------
***/


BZFILE *BZ2_bzReadOpen(int *bzerror, FILE *f, int verbosity, int small, void *unused, int nUnused)
{
  unsigned int unused_idx = 0;
  bzFile *bzf = 0;
  unsigned int bzf_idx = 0;
  int ret;
  {
    if (bzerror != 0)
    {
      *bzerror = 0;
    }
    if ((&bzf[bzf_idx]) != 0)
    {
      bzf->lastErr = 0;
    }
  }
  ;
  if (((((f == 0) || ((small != 0) && (small != 1))) || ((verbosity < 0) || (verbosity > 4))) || (((&unused[unused_idx]) == 0) && (nUnused != 0))) || (((&unused[unused_idx]) != 0) && ((nUnused < 0) || (nUnused > 5000))))
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -2;
      }
      if ((&bzf[bzf_idx]) != 0)
      {
        bzf->lastErr = -2;
      }
    }
    ;
    return 0;
  }
  ;
  if (ferror(f))
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -6;
      }
      if ((&bzf[bzf_idx]) != 0)
      {
        bzf->lastErr = -6;
      }
    }
    ;
    return 0;
  }
  ;
  bzf_idx = malloc(sizeof(bzFile));
  if ((&bzf[bzf_idx]) == 0)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -3;
      }
      if ((&bzf[bzf_idx]) != 0)
      {
        bzf->lastErr = -3;
      }
    }
    ;
    return 0;
  }
  ;
  {
    if (bzerror != 0)
    {
      *bzerror = 0;
    }
    if ((&bzf[bzf_idx]) != 0)
    {
      bzf->lastErr = 0;
    }
  }
  ;
  bzf->initialisedOk = (Bool) 0;
  bzf->handle = f;
  bzf->bufN = 0;
  bzf->writing = (Bool) 0;
  bzf->strm.bzalloc = 0;
  bzf->strm.bzfree = 0;
  bzf->strm.opaque = 0;
  while (nUnused > 0)
  {
    bzf->buf[bzf->bufN] = *((UChar *) unused);
    bzf->bufN += 1;
    unused_idx = (void *) (1 + ((UChar *) unused_idx));
    nUnused -= 1;
  }

  ret = BZ2_bzDecompressInit(&bzf->strm, verbosity, small);
  if (ret != 0)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = ret;
      }
      if ((&bzf[bzf_idx]) != 0)
      {
        bzf->lastErr = ret;
      }
    }
    ;
    free(bzf);
    return 0;
  }
  ;
  bzf->strm.avail_in = bzf->bufN;
  bzf->strm.next_in = bzf->buf;
  bzf->initialisedOk = (Bool) 1;
  return bzf;
}


/*** DEPENDENCIES:
typedef struct 
{
  FILE *handle;
  Char buf[5000];
  Int32 bufN;
  Bool writing;
  bz_stream strm;
  Int32 lastErr;
  Bool initialisedOk;
} bzFile
----------------------------
int BZ2_bzDecompressInit(bz_stream *strm, int verbosity, int small)
{
  DState *s;
  unsigned int s_idx = 0;
  if (!bz_config_ok())
  {
    return -9;
  }
  if (strm == 0)
  {
    return -2;
  }
  if ((small != 0) && (small != 1))
  {
    return -2;
  }
  if ((verbosity < 0) || (verbosity > 4))
  {
    return -2;
  }
  if (strm->bzalloc == 0)
  {
    strm->bzalloc = default_bzalloc;
  }
  if (strm->bzfree == 0)
  {
    strm->bzfree = default_bzfree;
  }
  s_idx = strm->bzalloc(strm->opaque, sizeof(DState), 1);
  if ((&s[s_idx]) == 0)
  {
    return -3;
  }
  s->strm = strm;
  strm->state = &s[s_idx];
  s->state = 10;
  s->bsLive = 0;
  s->bsBuff = 0;
  s->calculatedCombinedCRC = 0;
  strm->total_in_lo32 = 0;
  strm->total_in_hi32 = 0;
  strm->total_out_lo32 = 0;
  strm->total_out_hi32 = 0;
  s->smallDecompress = (Bool) small;
  s->ll4 = 0;
  s->ll16 = 0;
  s->tt = 0;
  s->currBlockNo = 0;
  s->verbosity = verbosity;
  return 0;
}


----------------------------
***/


static void prepare_new_block(EState *s)
{
  Int32 i;
  s->nblock = 0;
  s->numZ = 0;
  s->state_out_pos = 0;
  {
    s->blockCRC = 0xffffffffL;
  }
  ;
  for (i = 0; i < 256; i += 1)
    s->inUse[i] = (Bool) 0;

  s->blockNo += 1;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
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
} EState
----------------------------
***/


static void init_RL(EState *s)
{
  s->state_in_ch = 256;
  s->state_in_len = 0;
}


/*** DEPENDENCIES:
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
} EState
----------------------------
***/


int BZ2_bzCompressInit(bz_stream *strm, int blockSize100k, int verbosity, int workFactor)
{
  Int32 n;
  EState *s;
  unsigned int s_idx = 0;
  if (!bz_config_ok())
  {
    return -9;
  }
  if (((((strm == 0) || (blockSize100k < 1)) || (blockSize100k > 9)) || (workFactor < 0)) || (workFactor > 250))
  {
    return -2;
  }
  if (workFactor == 0)
  {
    workFactor = 30;
  }
  if (strm->bzalloc == 0)
  {
    strm->bzalloc = default_bzalloc;
  }
  if (strm->bzfree == 0)
  {
    strm->bzfree = default_bzfree;
  }
  s_idx = strm->bzalloc(strm->opaque, sizeof(EState), 1);
  if ((&s[s_idx]) == 0)
  {
    return -3;
  }
  s->strm = strm;
  s->arr1 = 0;
  s->arr2 = 0;
  s->ftab = 0;
  n = 100000 * blockSize100k;
  s->arr1 = strm->bzalloc(strm->opaque, n * (sizeof(UInt32)), 1);
  s->arr2 = strm->bzalloc(strm->opaque, (n + (((2 + 12) + 18) + 2)) * (sizeof(UInt32)), 1);
  s->ftab = strm->bzalloc(strm->opaque, 65537 * (sizeof(UInt32)), 1);
  if (((s->arr1 == 0) || (s->arr2 == 0)) || (s->ftab == 0))
  {
    if (s->arr1 != 0)
    {
      strm->bzfree(strm->opaque, s->arr1);
    }
    if (s->arr2 != 0)
    {
      strm->bzfree(strm->opaque, s->arr2);
    }
    if (s->ftab != 0)
    {
      strm->bzfree(strm->opaque, s->ftab);
    }
    if ((&s[s_idx]) != 0)
    {
      strm->bzfree(strm->opaque, s);
    }
    return -3;
  }
  s->blockNo = 0;
  s->state = 2;
  s->mode = 2;
  s->combinedCRC = 0;
  s->blockSize100k = blockSize100k;
  s->nblockMAX = (100000 * blockSize100k) - 19;
  s->verbosity = verbosity;
  s->workFactor = workFactor;
  s->block = (UChar *) s->arr2;
  s->mtfv = (UInt16 *) s->arr1;
  s->zbits = 0;
  s->ptr = (UInt32 *) s->arr1;
  strm->state = &s[s_idx];
  strm->total_in_lo32 = 0;
  strm->total_in_hi32 = 0;
  strm->total_out_lo32 = 0;
  strm->total_out_hi32 = 0;
  init_RL(s);
  prepare_new_block(s);
  return 0;
}


/*** DEPENDENCIES:
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
} bz_stream
----------------------------
static void prepare_new_block(EState *s)
{
  Int32 i;
  s->nblock = 0;
  s->numZ = 0;
  s->state_out_pos = 0;
  {
    s->blockCRC = 0xffffffffL;
  }
  ;
  for (i = 0; i < 256; i += 1)
    s->inUse[i] = (Bool) 0;

  s->blockNo += 1;
}


----------------------------
typedef int Int32
----------------------------
static void *default_bzalloc(void *opaque, Int32 items, Int32 size)
{
  void *v = malloc(items * size);
  return v;
}


----------------------------
static void init_RL(EState *s)
{
  s->state_in_ch = 256;
  s->state_in_len = 0;
}


----------------------------
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
} EState
----------------------------
static void default_bzfree(void *opaque, void *addr)
{
  if (addr != 0)
  {
    free(addr);
  }
}


----------------------------
static int bz_config_ok(void)
{
  if ((sizeof(int)) != 4)
  {
    return 0;
  }
  if ((sizeof(short)) != 2)
  {
    return 0;
  }
  if ((sizeof(char)) != 1)
  {
    return 0;
  }
  return 1;
}


----------------------------
***/


BZFILE *BZ2_bzWriteOpen(int *bzerror, FILE *f, int blockSize100k, int verbosity, int workFactor)
{
  Int32 ret;
  bzFile *bzf = 0;
  unsigned int bzf_idx = 0;
  {
    if (bzerror != 0)
    {
      *bzerror = 0;
    }
    if ((&bzf[bzf_idx]) != 0)
    {
      bzf->lastErr = 0;
    }
  }
  ;
  if ((((f == 0) || ((blockSize100k < 1) || (blockSize100k > 9))) || ((workFactor < 0) || (workFactor > 250))) || ((verbosity < 0) || (verbosity > 4)))
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -2;
      }
      if ((&bzf[bzf_idx]) != 0)
      {
        bzf->lastErr = -2;
      }
    }
    ;
    return 0;
  }
  ;
  if (ferror(f))
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -6;
      }
      if ((&bzf[bzf_idx]) != 0)
      {
        bzf->lastErr = -6;
      }
    }
    ;
    return 0;
  }
  ;
  bzf_idx = malloc(sizeof(bzFile));
  if ((&bzf[bzf_idx]) == 0)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -3;
      }
      if ((&bzf[bzf_idx]) != 0)
      {
        bzf->lastErr = -3;
      }
    }
    ;
    return 0;
  }
  ;
  {
    if (bzerror != 0)
    {
      *bzerror = 0;
    }
    if ((&bzf[bzf_idx]) != 0)
    {
      bzf->lastErr = 0;
    }
  }
  ;
  bzf->initialisedOk = (Bool) 0;
  bzf->bufN = 0;
  bzf->handle = f;
  bzf->writing = (Bool) 1;
  bzf->strm.bzalloc = 0;
  bzf->strm.bzfree = 0;
  bzf->strm.opaque = 0;
  if (workFactor == 0)
  {
    workFactor = 30;
  }
  ret = BZ2_bzCompressInit(&bzf->strm, blockSize100k, verbosity, workFactor);
  if (ret != 0)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = ret;
      }
      if ((&bzf[bzf_idx]) != 0)
      {
        bzf->lastErr = ret;
      }
    }
    ;
    free(bzf);
    return 0;
  }
  ;
  bzf->strm.avail_in = 0;
  bzf->initialisedOk = (Bool) 1;
  return bzf;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
typedef struct 
{
  FILE *handle;
  Char buf[5000];
  Int32 bufN;
  Bool writing;
  bz_stream strm;
  Int32 lastErr;
  Bool initialisedOk;
} bzFile
----------------------------
int BZ2_bzCompressInit(bz_stream *strm, int blockSize100k, int verbosity, int workFactor)
{
  Int32 n;
  EState *s;
  unsigned int s_idx = 0;
  if (!bz_config_ok())
  {
    return -9;
  }
  if (((((strm == 0) || (blockSize100k < 1)) || (blockSize100k > 9)) || (workFactor < 0)) || (workFactor > 250))
  {
    return -2;
  }
  if (workFactor == 0)
  {
    workFactor = 30;
  }
  if (strm->bzalloc == 0)
  {
    strm->bzalloc = default_bzalloc;
  }
  if (strm->bzfree == 0)
  {
    strm->bzfree = default_bzfree;
  }
  s_idx = strm->bzalloc(strm->opaque, sizeof(EState), 1);
  if ((&s[s_idx]) == 0)
  {
    return -3;
  }
  s->strm = strm;
  s->arr1 = 0;
  s->arr2 = 0;
  s->ftab = 0;
  n = 100000 * blockSize100k;
  s->arr1 = strm->bzalloc(strm->opaque, n * (sizeof(UInt32)), 1);
  s->arr2 = strm->bzalloc(strm->opaque, (n + (((2 + 12) + 18) + 2)) * (sizeof(UInt32)), 1);
  s->ftab = strm->bzalloc(strm->opaque, 65537 * (sizeof(UInt32)), 1);
  if (((s->arr1 == 0) || (s->arr2 == 0)) || (s->ftab == 0))
  {
    if (s->arr1 != 0)
    {
      strm->bzfree(strm->opaque, s->arr1);
    }
    if (s->arr2 != 0)
    {
      strm->bzfree(strm->opaque, s->arr2);
    }
    if (s->ftab != 0)
    {
      strm->bzfree(strm->opaque, s->ftab);
    }
    if ((&s[s_idx]) != 0)
    {
      strm->bzfree(strm->opaque, s);
    }
    return -3;
  }
  s->blockNo = 0;
  s->state = 2;
  s->mode = 2;
  s->combinedCRC = 0;
  s->blockSize100k = blockSize100k;
  s->nblockMAX = (100000 * blockSize100k) - 19;
  s->verbosity = verbosity;
  s->workFactor = workFactor;
  s->block = (UChar *) s->arr2;
  s->mtfv = (UInt16 *) s->arr1;
  s->zbits = 0;
  s->ptr = (UInt32 *) s->arr1;
  strm->state = &s[s_idx];
  strm->total_in_lo32 = 0;
  strm->total_in_hi32 = 0;
  strm->total_out_lo32 = 0;
  strm->total_out_hi32 = 0;
  init_RL(s);
  prepare_new_block(s);
  return 0;
}


----------------------------
***/


static BZFILE *bzopen_or_bzdopen(const char *path, int fd, const char *mode, int open_mode)
{
  unsigned int mode_idx = 0;
  int bzerr;
  char unused[5000];
  int blockSize100k = 9;
  int writing = 0;
  char mode2[10] = "";
  FILE *fp = 0;
  unsigned int fp_idx = 0;
  BZFILE *bzfp = 0;
  unsigned int bzfp_idx = 0;
  int verbosity = 0;
  int workFactor = 30;
  int smallMode = 0;
  int nUnused = 0;
  if ((&mode[mode_idx]) == 0)
  {
    return 0;
  }
  while (mode[mode_idx])
  {
    switch (mode[mode_idx])
    {
      case 'r':
      {
        writing = 0;
        break;
      }

      case 'w':
      {
        writing = 1;
        break;
      }

      case 's':
      {
        smallMode = 1;
        break;
      }

      default:
      {
        if (isdigit((int) mode[mode_idx]))
        {
          blockSize100k = mode[mode_idx] - 0x30;
        }
      }

    }

    mode_idx += 1;
  }

  strcat(mode2, (writing) ? ("wb") : ("rb"));
  if (open_mode == 0)
  {
    strcat(mode2, (writing) ? ("e") : ("e"));
  }
  if (open_mode == 0)
  {
    if ((path == 0) || (strcmp(path, "") == 0))
    {
      fp_idx = (writing) ? (stdout) : (stdin);
      ;
    }
    else
    {
      fp_idx = fopen(path, mode2);
    }
  }
  else
  {
    fp_idx = fdopen(fd, mode2);
  }
  if ((&fp[fp_idx]) == 0)
  {
    return 0;
  }
  if (writing)
  {
    if (blockSize100k < 1)
    {
      blockSize100k = 1;
    }
    if (blockSize100k > 9)
    {
      blockSize100k = 9;
    }
    bzfp_idx = BZ2_bzWriteOpen(&bzerr, fp, blockSize100k, verbosity, workFactor);
  }
  else
  {
    bzfp_idx = BZ2_bzReadOpen(&bzerr, fp, verbosity, smallMode, unused, nUnused);
  }
  if ((&bzfp[bzfp_idx]) == 0)
  {
    if (((&fp[fp_idx]) != stdin) && ((&fp[fp_idx]) != stdout))
    {
      fclose(fp);
    }
    return 0;
  }
  return bzfp;
}


/*** DEPENDENCIES:
BZFILE *BZ2_bzReadOpen(int *bzerror, FILE *f, int verbosity, int small, void *unused, int nUnused)
{
  unsigned int unused_idx = 0;
  bzFile *bzf = 0;
  unsigned int bzf_idx = 0;
  int ret;
  {
    if (bzerror != 0)
    {
      *bzerror = 0;
    }
    if ((&bzf[bzf_idx]) != 0)
    {
      bzf->lastErr = 0;
    }
  }
  ;
  if (((((f == 0) || ((small != 0) && (small != 1))) || ((verbosity < 0) || (verbosity > 4))) || (((&unused[unused_idx]) == 0) && (nUnused != 0))) || (((&unused[unused_idx]) != 0) && ((nUnused < 0) || (nUnused > 5000))))
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -2;
      }
      if ((&bzf[bzf_idx]) != 0)
      {
        bzf->lastErr = -2;
      }
    }
    ;
    return 0;
  }
  ;
  if (ferror(f))
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -6;
      }
      if ((&bzf[bzf_idx]) != 0)
      {
        bzf->lastErr = -6;
      }
    }
    ;
    return 0;
  }
  ;
  bzf_idx = malloc(sizeof(bzFile));
  if ((&bzf[bzf_idx]) == 0)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -3;
      }
      if ((&bzf[bzf_idx]) != 0)
      {
        bzf->lastErr = -3;
      }
    }
    ;
    return 0;
  }
  ;
  {
    if (bzerror != 0)
    {
      *bzerror = 0;
    }
    if ((&bzf[bzf_idx]) != 0)
    {
      bzf->lastErr = 0;
    }
  }
  ;
  bzf->initialisedOk = (Bool) 0;
  bzf->handle = f;
  bzf->bufN = 0;
  bzf->writing = (Bool) 0;
  bzf->strm.bzalloc = 0;
  bzf->strm.bzfree = 0;
  bzf->strm.opaque = 0;
  while (nUnused > 0)
  {
    bzf->buf[bzf->bufN] = *((UChar *) unused);
    bzf->bufN += 1;
    unused_idx = (void *) (1 + ((UChar *) unused_idx));
    nUnused -= 1;
  }

  ret = BZ2_bzDecompressInit(&bzf->strm, verbosity, small);
  if (ret != 0)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = ret;
      }
      if ((&bzf[bzf_idx]) != 0)
      {
        bzf->lastErr = ret;
      }
    }
    ;
    free(bzf);
    return 0;
  }
  ;
  bzf->strm.avail_in = bzf->bufN;
  bzf->strm.next_in = bzf->buf;
  bzf->initialisedOk = (Bool) 1;
  return bzf;
}


----------------------------
typedef void BZFILE
----------------------------
BZFILE *BZ2_bzWriteOpen(int *bzerror, FILE *f, int blockSize100k, int verbosity, int workFactor)
{
  Int32 ret;
  bzFile *bzf = 0;
  unsigned int bzf_idx = 0;
  {
    if (bzerror != 0)
    {
      *bzerror = 0;
    }
    if ((&bzf[bzf_idx]) != 0)
    {
      bzf->lastErr = 0;
    }
  }
  ;
  if ((((f == 0) || ((blockSize100k < 1) || (blockSize100k > 9))) || ((workFactor < 0) || (workFactor > 250))) || ((verbosity < 0) || (verbosity > 4)))
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -2;
      }
      if ((&bzf[bzf_idx]) != 0)
      {
        bzf->lastErr = -2;
      }
    }
    ;
    return 0;
  }
  ;
  if (ferror(f))
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -6;
      }
      if ((&bzf[bzf_idx]) != 0)
      {
        bzf->lastErr = -6;
      }
    }
    ;
    return 0;
  }
  ;
  bzf_idx = malloc(sizeof(bzFile));
  if ((&bzf[bzf_idx]) == 0)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -3;
      }
      if ((&bzf[bzf_idx]) != 0)
      {
        bzf->lastErr = -3;
      }
    }
    ;
    return 0;
  }
  ;
  {
    if (bzerror != 0)
    {
      *bzerror = 0;
    }
    if ((&bzf[bzf_idx]) != 0)
    {
      bzf->lastErr = 0;
    }
  }
  ;
  bzf->initialisedOk = (Bool) 0;
  bzf->bufN = 0;
  bzf->handle = f;
  bzf->writing = (Bool) 1;
  bzf->strm.bzalloc = 0;
  bzf->strm.bzfree = 0;
  bzf->strm.opaque = 0;
  if (workFactor == 0)
  {
    workFactor = 30;
  }
  ret = BZ2_bzCompressInit(&bzf->strm, blockSize100k, verbosity, workFactor);
  if (ret != 0)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = ret;
      }
      if ((&bzf[bzf_idx]) != 0)
      {
        bzf->lastErr = ret;
      }
    }
    ;
    free(bzf);
    return 0;
  }
  ;
  bzf->strm.avail_in = 0;
  bzf->initialisedOk = (Bool) 1;
  return bzf;
}


----------------------------
***/


BZFILE *BZ2_bzopen(const char *path, const char *mode)
{
  return bzopen_or_bzdopen(path, -1, mode, 0);
}


/*** DEPENDENCIES:
static BZFILE *bzopen_or_bzdopen(const char *path, int fd, const char *mode, int open_mode)
{
  unsigned int mode_idx = 0;
  int bzerr;
  char unused[5000];
  int blockSize100k = 9;
  int writing = 0;
  char mode2[10] = "";
  FILE *fp = 0;
  unsigned int fp_idx = 0;
  BZFILE *bzfp = 0;
  unsigned int bzfp_idx = 0;
  int verbosity = 0;
  int workFactor = 30;
  int smallMode = 0;
  int nUnused = 0;
  if ((&mode[mode_idx]) == 0)
  {
    return 0;
  }
  while (mode[mode_idx])
  {
    switch (mode[mode_idx])
    {
      case 'r':
      {
        writing = 0;
        break;
      }

      case 'w':
      {
        writing = 1;
        break;
      }

      case 's':
      {
        smallMode = 1;
        break;
      }

      default:
      {
        if (isdigit((int) mode[mode_idx]))
        {
          blockSize100k = mode[mode_idx] - 0x30;
        }
      }

    }

    mode_idx += 1;
  }

  strcat(mode2, (writing) ? ("wb") : ("rb"));
  if (open_mode == 0)
  {
    strcat(mode2, (writing) ? ("e") : ("e"));
  }
  if (open_mode == 0)
  {
    if ((path == 0) || (strcmp(path, "") == 0))
    {
      fp_idx = (writing) ? (stdout) : (stdin);
      ;
    }
    else
    {
      fp_idx = fopen(path, mode2);
    }
  }
  else
  {
    fp_idx = fdopen(fd, mode2);
  }
  if ((&fp[fp_idx]) == 0)
  {
    return 0;
  }
  if (writing)
  {
    if (blockSize100k < 1)
    {
      blockSize100k = 1;
    }
    if (blockSize100k > 9)
    {
      blockSize100k = 9;
    }
    bzfp_idx = BZ2_bzWriteOpen(&bzerr, fp, blockSize100k, verbosity, workFactor);
  }
  else
  {
    bzfp_idx = BZ2_bzReadOpen(&bzerr, fp, verbosity, smallMode, unused, nUnused);
  }
  if ((&bzfp[bzfp_idx]) == 0)
  {
    if (((&fp[fp_idx]) != stdin) && ((&fp[fp_idx]) != stdout))
    {
      fclose(fp);
    }
    return 0;
  }
  return bzfp;
}


----------------------------
***/


BZFILE *BZ2_bzdopen(int fd, const char *mode)
{
  return bzopen_or_bzdopen(0, fd, mode, 1);
}


/*** DEPENDENCIES:
static BZFILE *bzopen_or_bzdopen(const char *path, int fd, const char *mode, int open_mode)
{
  unsigned int mode_idx = 0;
  int bzerr;
  char unused[5000];
  int blockSize100k = 9;
  int writing = 0;
  char mode2[10] = "";
  FILE *fp = 0;
  unsigned int fp_idx = 0;
  BZFILE *bzfp = 0;
  unsigned int bzfp_idx = 0;
  int verbosity = 0;
  int workFactor = 30;
  int smallMode = 0;
  int nUnused = 0;
  if ((&mode[mode_idx]) == 0)
  {
    return 0;
  }
  while (mode[mode_idx])
  {
    switch (mode[mode_idx])
    {
      case 'r':
      {
        writing = 0;
        break;
      }

      case 'w':
      {
        writing = 1;
        break;
      }

      case 's':
      {
        smallMode = 1;
        break;
      }

      default:
      {
        if (isdigit((int) mode[mode_idx]))
        {
          blockSize100k = mode[mode_idx] - 0x30;
        }
      }

    }

    mode_idx += 1;
  }

  strcat(mode2, (writing) ? ("wb") : ("rb"));
  if (open_mode == 0)
  {
    strcat(mode2, (writing) ? ("e") : ("e"));
  }
  if (open_mode == 0)
  {
    if ((path == 0) || (strcmp(path, "") == 0))
    {
      fp_idx = (writing) ? (stdout) : (stdin);
      ;
    }
    else
    {
      fp_idx = fopen(path, mode2);
    }
  }
  else
  {
    fp_idx = fdopen(fd, mode2);
  }
  if ((&fp[fp_idx]) == 0)
  {
    return 0;
  }
  if (writing)
  {
    if (blockSize100k < 1)
    {
      blockSize100k = 1;
    }
    if (blockSize100k > 9)
    {
      blockSize100k = 9;
    }
    bzfp_idx = BZ2_bzWriteOpen(&bzerr, fp, blockSize100k, verbosity, workFactor);
  }
  else
  {
    bzfp_idx = BZ2_bzReadOpen(&bzerr, fp, verbosity, smallMode, unused, nUnused);
  }
  if ((&bzfp[bzfp_idx]) == 0)
  {
    if (((&fp[fp_idx]) != stdin) && ((&fp[fp_idx]) != stdout))
    {
      fclose(fp);
    }
    return 0;
  }
  return bzfp;
}


----------------------------
***/


int BZ2_bzflush(BZFILE *b)
{
  return 0;
}


/*** DEPENDENCIES:
typedef void BZFILE
----------------------------
***/


void BZ2_bz__AssertH__fail(int errcode)
{
  fprintf(stderr, "\n\nbzip2/libbzip2: internal error number %d.\nThis is a bug in bzip2/libbzip2, %s.\nPlease report it at: https://gitlab.com/bzip2/bzip2/-/issues\nIf this happened when you were using some program which uses\nlibbzip2 as a component, you should also report this bug to\nthe author(s) of that program.\nPlease make an effort to report this bug;\ntimely and accurate bug reports eventually lead to higher\nquality software.  Thanks.\n\n", errcode, BZ2_bzlibVersion());
  if (errcode == 1007)
  {
    fprintf(stderr, "\n*** A special note about internal error number 1007 ***\n\nExperience suggests that a common cause of i.e. 1007\nis unreliable memory or other hardware.  The 1007 assertion\njust happens to cross-check the results of huge numbers of\nmemory reads/writes, and so acts (unintendedly) as a stress\ntest of your memory system.\n\nI suggest the following: try compressing the file again,\npossibly monitoring progress in detail with the -vv flag.\n\n* If the error cannot be reproduced, and/or happens at different\n  points in compression, you may have a flaky memory system.\n  Try a memory-test program.  I have used Memtest86\n  (www.memtest86.com).  At the time of writing it is free (GPLd).\n  Memtest86 tests memory much more thorougly than your BIOSs\n  power-on test, and may find failures that the BIOS doesn't.\n\n* If the error can be repeatably reproduced, this is a bug in\n  bzip2, and I would very much like to hear about it.  Please\n  let me know, and, ideally, save a copy of the file causing the\n  problem -- without which I will be unable to investigate it.\n\n");
  }
  exit(3);
}


/*** DEPENDENCIES:
const char *BZ2_bzlibVersion(void)
{
  return "1.1.0";
}


----------------------------
***/


Int32 BZ2_indexIntoF(Int32 indx, Int32 *cftab)
{
  Int32 nb;
  Int32 na;
  Int32 mid;
  nb = 0;
  na = 256;
  do
  {
    mid = (nb + na) >> 1;
    if (indx >= cftab[mid])
    {
      nb = mid;
    }
    else
      na = mid;
  }
  while ((na - nb) != 1);
  return nb;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
***/


static Bool isempty_RL(EState *s)
{
  if ((s->state_in_ch < 256) && (s->state_in_len > 0))
  {
    return (Bool) 0;
  }
  else
    return (Bool) 1;
}


/*** DEPENDENCIES:
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
} EState
----------------------------
***/


static Bool myfeof(FILE *f)
{
  Int32 c = fgetc(f);
  if (c == EOF)
  {
    return (Bool) 1;
  }
  ungetc(c, f);
  return (Bool) 0;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
***/


int BZ2_bzCompressEnd(bz_stream *strm)
{
  EState *s;
  unsigned int s_idx = 0;
  if (strm == 0)
  {
    return -2;
  }
  s_idx = strm->state;
  if ((&s[s_idx]) == 0)
  {
    return -2;
  }
  if (s->strm != strm)
  {
    return -2;
  }
  if (s->arr1 != 0)
  {
    strm->bzfree(strm->opaque, s->arr1);
  }
  if (s->arr2 != 0)
  {
    strm->bzfree(strm->opaque, s->arr2);
  }
  if (s->ftab != 0)
  {
    strm->bzfree(strm->opaque, s->ftab);
  }
  strm->bzfree(strm->opaque, strm->state);
  strm->state = 0;
  return 0;
}


/*** DEPENDENCIES:
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
} bz_stream
----------------------------
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
} EState
----------------------------
***/


int BZ2_bzDecompressEnd(bz_stream *strm)
{
  DState *s;
  unsigned int s_idx = 0;
  if (strm == 0)
  {
    return -2;
  }
  s_idx = strm->state;
  if ((&s[s_idx]) == 0)
  {
    return -2;
  }
  if (s->strm != strm)
  {
    return -2;
  }
  if (s->tt != 0)
  {
    strm->bzfree(strm->opaque, s->tt);
  }
  if (s->ll16 != 0)
  {
    strm->bzfree(strm->opaque, s->ll16);
  }
  if (s->ll4 != 0)
  {
    strm->bzfree(strm->opaque, s->ll4);
  }
  strm->bzfree(strm->opaque, strm->state);
  strm->state = 0;
  return 0;
}


/*** DEPENDENCIES:
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
} bz_stream
----------------------------
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
} DState
----------------------------
***/


void BZ2_bzReadGetUnused(int *bzerror, BZFILE *b, void **unused, int *nUnused)
{
  bzFile *bzf = (bzFile *) b;
  if (bzf == 0)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -2;
      }
      if (bzf != 0)
      {
        bzf->lastErr = -2;
      }
    }
    ;
    return;
  }
  ;
  if (bzf->lastErr != 4)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -1;
      }
      if (bzf != 0)
      {
        bzf->lastErr = -1;
      }
    }
    ;
    return;
  }
  ;
  if ((unused == 0) || (nUnused == 0))
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -2;
      }
      if (bzf != 0)
      {
        bzf->lastErr = -2;
      }
    }
    ;
    return;
  }
  ;
  {
    if (bzerror != 0)
    {
      *bzerror = 0;
    }
    if (bzf != 0)
    {
      bzf->lastErr = 0;
    }
  }
  ;
  *nUnused = bzf->strm.avail_in;
  *unused = bzf->strm.next_in;
}


/*** DEPENDENCIES:
typedef struct 
{
  FILE *handle;
  Char buf[5000];
  Int32 bufN;
  Bool writing;
  bz_stream strm;
  Int32 lastErr;
  Bool initialisedOk;
} bzFile
----------------------------
typedef void BZFILE
----------------------------
***/


static Bool copy_output_until_stop(EState *s)
{
  Bool progress_out = (Bool) 0;
  while ((Bool) 1)
  {
    if (s->strm->avail_out == 0)
    {
      break;
    }
    if (s->state_out_pos >= s->numZ)
    {
      break;
    }
    progress_out = (Bool) 1;
    *s->strm->next_out = s->zbits[s->state_out_pos];
    s->state_out_pos += 1;
    s->strm->avail_out -= 1;
    s->strm->next_out += 1;
    s->strm->total_out_lo32 += 1;
    if (s->strm->total_out_lo32 == 0)
    {
      s->strm->total_out_hi32 += 1;
    }
  }

  return progress_out;
}


/*** DEPENDENCIES:
typedef unsigned char Bool
----------------------------
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
} EState
----------------------------
***/


static void add_pair_to_block(EState *s)
{
  Int32 i;
  UChar ch = (UChar) s->state_in_ch;
  for (i = 0; i < s->state_in_len; i += 1)
  {
    {
      s->blockCRC = (s->blockCRC << 8) ^ BZ2_crc32Table[(s->blockCRC >> 24) ^ ((UChar) ch)];
    }
    ;
  }

  s->inUse[s->state_in_ch] = (Bool) 1;
  switch (s->state_in_len)
  {
    case 1:
    {
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      break;
    }

    case 2:
    {
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      break;
    }

    case 3:
    {
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      break;
    }

    default:
    {
      s->inUse[s->state_in_len - 4] = (Bool) 1;
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      s->block[s->nblock] = (UChar) (s->state_in_len - 4);
      s->nblock += 1;
      break;
    }

  }

}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
typedef char Char
----------------------------
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
} EState
----------------------------
typedef unsigned char UChar
----------------------------
extern UInt32 BZ2_crc32Table[256]
----------------------------
***/


// hint:  ['progress_in_ref is a mutable refrence to Bool']
void helper_copy_input_until_stop_2(Bool * const progress_in_ref, EState * const s)
{
  Bool progress_in = *progress_in_ref;
  while ((Bool) 1)
  {
    if (s->nblock >= s->nblockMAX)
    {
      break;
    }
    if (s->strm->avail_in == 0)
    {
      break;
    }
    if (s->avail_in_expect == 0)
    {
      break;
    }
    progress_in = (Bool) 1;
    {
      UInt32 zchh = (UInt32) ((UInt32) (*((UChar *) s->strm->next_in)));
      if ((zchh != s->state_in_ch) && (s->state_in_len == 1))
      {
        UChar ch = (UChar) s->state_in_ch;
        {
          s->blockCRC = (s->blockCRC << 8) ^ BZ2_crc32Table[(s->blockCRC >> 24) ^ ((UChar) ch)];
        }
        ;
        s->inUse[s->state_in_ch] = (Bool) 1;
        s->block[s->nblock] = (UChar) ch;
        s->nblock += 1;
        s->state_in_ch = zchh;
      }
      else
        if ((zchh != s->state_in_ch) || (s->state_in_len == 255))
      {
        if (s->state_in_ch < 256)
        {
          add_pair_to_block(s);
        }
        s->state_in_ch = zchh;
        s->state_in_len = 1;
      }
      else
      {
        s->state_in_len += 1;
      }
    }
    ;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
    s->avail_in_expect -= 1;
  }

  *progress_in_ref = progress_in;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
typedef unsigned int UInt32
----------------------------
typedef char Char
----------------------------
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
} EState
----------------------------
typedef unsigned char Bool
----------------------------
typedef unsigned char UChar
----------------------------
extern UInt32 BZ2_crc32Table[256]
----------------------------
static void add_pair_to_block(EState *s)
{
  Int32 i;
  UChar ch = (UChar) s->state_in_ch;
  for (i = 0; i < s->state_in_len; i += 1)
  {
    {
      s->blockCRC = (s->blockCRC << 8) ^ BZ2_crc32Table[(s->blockCRC >> 24) ^ ((UChar) ch)];
    }
    ;
  }

  s->inUse[s->state_in_ch] = (Bool) 1;
  switch (s->state_in_len)
  {
    case 1:
    {
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      break;
    }

    case 2:
    {
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      break;
    }

    case 3:
    {
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      break;
    }

    default:
    {
      s->inUse[s->state_in_len - 4] = (Bool) 1;
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      s->block[s->nblock] = (UChar) (s->state_in_len - 4);
      s->nblock += 1;
      break;
    }

  }

}


----------------------------
***/


// hint:  ['progress_in_ref is a mutable refrence to Bool']
void helper_copy_input_until_stop_1(Bool * const progress_in_ref, EState * const s)
{
  Bool progress_in = *progress_in_ref;
  while ((Bool) 1)
  {
    if (s->nblock >= s->nblockMAX)
    {
      break;
    }
    if (s->strm->avail_in == 0)
    {
      break;
    }
    progress_in = (Bool) 1;
    {
      UInt32 zchh = (UInt32) ((UInt32) (*((UChar *) s->strm->next_in)));
      if ((zchh != s->state_in_ch) && (s->state_in_len == 1))
      {
        UChar ch = (UChar) s->state_in_ch;
        {
          s->blockCRC = (s->blockCRC << 8) ^ BZ2_crc32Table[(s->blockCRC >> 24) ^ ((UChar) ch)];
        }
        ;
        s->inUse[s->state_in_ch] = (Bool) 1;
        s->block[s->nblock] = (UChar) ch;
        s->nblock += 1;
        s->state_in_ch = zchh;
      }
      else
        if ((zchh != s->state_in_ch) || (s->state_in_len == 255))
      {
        if (s->state_in_ch < 256)
        {
          add_pair_to_block(s);
        }
        s->state_in_ch = zchh;
        s->state_in_len = 1;
      }
      else
      {
        s->state_in_len += 1;
      }
    }
    ;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  *progress_in_ref = progress_in;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
typedef unsigned int UInt32
----------------------------
typedef char Char
----------------------------
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
} EState
----------------------------
typedef unsigned char Bool
----------------------------
typedef unsigned char UChar
----------------------------
extern UInt32 BZ2_crc32Table[256]
----------------------------
static void add_pair_to_block(EState *s)
{
  Int32 i;
  UChar ch = (UChar) s->state_in_ch;
  for (i = 0; i < s->state_in_len; i += 1)
  {
    {
      s->blockCRC = (s->blockCRC << 8) ^ BZ2_crc32Table[(s->blockCRC >> 24) ^ ((UChar) ch)];
    }
    ;
  }

  s->inUse[s->state_in_ch] = (Bool) 1;
  switch (s->state_in_len)
  {
    case 1:
    {
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      break;
    }

    case 2:
    {
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      break;
    }

    case 3:
    {
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      break;
    }

    default:
    {
      s->inUse[s->state_in_len - 4] = (Bool) 1;
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      s->block[s->nblock] = (UChar) (s->state_in_len - 4);
      s->nblock += 1;
      break;
    }

  }

}


----------------------------
***/


static Bool copy_input_until_stop(EState *s)
{
  Bool progress_in = (Bool) 0;
  if (s->mode == 2)
  {
    helper_copy_input_until_stop_1(&progress_in, s);
  }
  else
  {
    helper_copy_input_until_stop_2(&progress_in, s);
  }
  return progress_in;
}


/*** DEPENDENCIES:
typedef unsigned char Bool
----------------------------
void helper_copy_input_until_stop_2(Bool * const progress_in_ref, EState * const s)
{
  Bool progress_in = *progress_in_ref;
  while ((Bool) 1)
  {
    if (s->nblock >= s->nblockMAX)
    {
      break;
    }
    if (s->strm->avail_in == 0)
    {
      break;
    }
    if (s->avail_in_expect == 0)
    {
      break;
    }
    progress_in = (Bool) 1;
    {
      UInt32 zchh = (UInt32) ((UInt32) (*((UChar *) s->strm->next_in)));
      if ((zchh != s->state_in_ch) && (s->state_in_len == 1))
      {
        UChar ch = (UChar) s->state_in_ch;
        {
          s->blockCRC = (s->blockCRC << 8) ^ BZ2_crc32Table[(s->blockCRC >> 24) ^ ((UChar) ch)];
        }
        ;
        s->inUse[s->state_in_ch] = (Bool) 1;
        s->block[s->nblock] = (UChar) ch;
        s->nblock += 1;
        s->state_in_ch = zchh;
      }
      else
        if ((zchh != s->state_in_ch) || (s->state_in_len == 255))
      {
        if (s->state_in_ch < 256)
        {
          add_pair_to_block(s);
        }
        s->state_in_ch = zchh;
        s->state_in_len = 1;
      }
      else
      {
        s->state_in_len += 1;
      }
    }
    ;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
    s->avail_in_expect -= 1;
  }

  *progress_in_ref = progress_in;
}


----------------------------
void helper_copy_input_until_stop_1(Bool * const progress_in_ref, EState * const s)
{
  Bool progress_in = *progress_in_ref;
  while ((Bool) 1)
  {
    if (s->nblock >= s->nblockMAX)
    {
      break;
    }
    if (s->strm->avail_in == 0)
    {
      break;
    }
    progress_in = (Bool) 1;
    {
      UInt32 zchh = (UInt32) ((UInt32) (*((UChar *) s->strm->next_in)));
      if ((zchh != s->state_in_ch) && (s->state_in_len == 1))
      {
        UChar ch = (UChar) s->state_in_ch;
        {
          s->blockCRC = (s->blockCRC << 8) ^ BZ2_crc32Table[(s->blockCRC >> 24) ^ ((UChar) ch)];
        }
        ;
        s->inUse[s->state_in_ch] = (Bool) 1;
        s->block[s->nblock] = (UChar) ch;
        s->nblock += 1;
        s->state_in_ch = zchh;
      }
      else
        if ((zchh != s->state_in_ch) || (s->state_in_len == 255))
      {
        if (s->state_in_ch < 256)
        {
          add_pair_to_block(s);
        }
        s->state_in_ch = zchh;
        s->state_in_len = 1;
      }
      else
      {
        s->state_in_len += 1;
      }
    }
    ;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  *progress_in_ref = progress_in;
}


----------------------------
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
} EState
----------------------------
***/


static void flush_RL(EState *s)
{
  if (s->state_in_ch < 256)
  {
    add_pair_to_block(s);
  }
  init_RL(s);
}


/*** DEPENDENCIES:
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
} EState
----------------------------
static void init_RL(EState *s)
{
  s->state_in_ch = 256;
  s->state_in_len = 0;
}


----------------------------
static void add_pair_to_block(EState *s)
{
  Int32 i;
  UChar ch = (UChar) s->state_in_ch;
  for (i = 0; i < s->state_in_len; i += 1)
  {
    {
      s->blockCRC = (s->blockCRC << 8) ^ BZ2_crc32Table[(s->blockCRC >> 24) ^ ((UChar) ch)];
    }
    ;
  }

  s->inUse[s->state_in_ch] = (Bool) 1;
  switch (s->state_in_len)
  {
    case 1:
    {
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      break;
    }

    case 2:
    {
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      break;
    }

    case 3:
    {
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      break;
    }

    default:
    {
      s->inUse[s->state_in_len - 4] = (Bool) 1;
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      s->block[s->nblock] = (UChar) ch;
      s->nblock += 1;
      s->block[s->nblock] = (UChar) (s->state_in_len - 4);
      s->nblock += 1;
      break;
    }

  }

}


----------------------------
***/


static Bool handle_compress(bz_stream *strm)
{
  Bool progress_in = (Bool) 0;
  Bool progress_out = (Bool) 0;
  EState *s = strm->state;
  while ((Bool) 1)
  {
    if (s->state == 1)
    {
      progress_out |= copy_output_until_stop(s);
      if (s->state_out_pos < s->numZ)
      {
        break;
      }
      if (((s->mode == 4) && (s->avail_in_expect == 0)) && isempty_RL(s))
      {
        break;
      }
      prepare_new_block(s);
      s->state = 2;
      if (((s->mode == 3) && (s->avail_in_expect == 0)) && isempty_RL(s))
      {
        break;
      }
    }
    if (s->state == 2)
    {
      progress_in |= copy_input_until_stop(s);
      if ((s->mode != 2) && (s->avail_in_expect == 0))
      {
        flush_RL(s);
        BZ2_compressBlock(s, (Bool) (s->mode == 4));
        s->state = 1;
      }
      else
        if (s->nblock >= s->nblockMAX)
      {
        BZ2_compressBlock(s, (Bool) 0);
        s->state = 1;
      }
      else
        if (s->strm->avail_in == 0)
      {
        break;
      }
    }
  }

  return progress_in || progress_out;
}


/*** DEPENDENCIES:
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
} bz_stream
----------------------------
static void prepare_new_block(EState *s)
{
  Int32 i;
  s->nblock = 0;
  s->numZ = 0;
  s->state_out_pos = 0;
  {
    s->blockCRC = 0xffffffffL;
  }
  ;
  for (i = 0; i < 256; i += 1)
    s->inUse[i] = (Bool) 0;

  s->blockNo += 1;
}


----------------------------
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
} EState
----------------------------
static Bool copy_output_until_stop(EState *s)
{
  Bool progress_out = (Bool) 0;
  while ((Bool) 1)
  {
    if (s->strm->avail_out == 0)
    {
      break;
    }
    if (s->state_out_pos >= s->numZ)
    {
      break;
    }
    progress_out = (Bool) 1;
    *s->strm->next_out = s->zbits[s->state_out_pos];
    s->state_out_pos += 1;
    s->strm->avail_out -= 1;
    s->strm->next_out += 1;
    s->strm->total_out_lo32 += 1;
    if (s->strm->total_out_lo32 == 0)
    {
      s->strm->total_out_hi32 += 1;
    }
  }

  return progress_out;
}


----------------------------
typedef unsigned char Bool
----------------------------
static Bool copy_input_until_stop(EState *s)
{
  Bool progress_in = (Bool) 0;
  if (s->mode == 2)
  {
    helper_copy_input_until_stop_1(&progress_in, s);
  }
  else
  {
    helper_copy_input_until_stop_2(&progress_in, s);
  }
  return progress_in;
}


----------------------------
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


----------------------------
static Bool isempty_RL(EState *s)
{
  if ((s->state_in_ch < 256) && (s->state_in_len > 0))
  {
    return (Bool) 0;
  }
  else
    return (Bool) 1;
}


----------------------------
static void flush_RL(EState *s)
{
  if (s->state_in_ch < 256)
  {
    add_pair_to_block(s);
  }
  init_RL(s);
}


----------------------------
***/


int BZ2_bzCompress(bz_stream *strm, int action)
{
  Bool progress;
  EState *s;
  unsigned int s_idx = 0;
  if (strm == 0)
  {
    return -2;
  }
  s_idx = strm->state;
  if ((&s[s_idx]) == 0)
  {
    return -2;
  }
  if (s->strm != strm)
  {
    return -2;
  }
  preswitch:
  switch (s->mode)
  {
    case 1:
    {
      return -1;
    }

    case 2:
    {
      if (action == 0)
      {
        progress = handle_compress(strm);
        return (progress) ? (1) : (-2);
      }
      else
        if (action == 1)
      {
        s->avail_in_expect = strm->avail_in;
        s->mode = 3;
        goto preswitch;
      }
      else
        if (action == 2)
      {
        s->avail_in_expect = strm->avail_in;
        s->mode = 4;
        goto preswitch;
      }
      else
        return -2;
    }

    case 3:
    {
      if (action != 1)
      {
        return -1;
      }
      if (s->avail_in_expect != s->strm->avail_in)
      {
        return -1;
      }
      progress = handle_compress(strm);
      if (((s->avail_in_expect > 0) || (!isempty_RL(s))) || (s->state_out_pos < s->numZ))
      {
        return 2;
      }
      s->mode = 2;
      return 1;
    }

    case 4:
    {
      if (action != 2)
      {
        return -1;
      }
      if (s->avail_in_expect != s->strm->avail_in)
      {
        return -1;
      }
      progress = handle_compress(strm);
      if (!progress)
      {
        return -1;
      }
      if (((s->avail_in_expect > 0) || (!isempty_RL(s))) || (s->state_out_pos < s->numZ))
      {
        return 3;
      }
      s->mode = 1;
      return 4;
    }

  }


  return 0;
}


/*** DEPENDENCIES:
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
} bz_stream
----------------------------
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
} EState
----------------------------
typedef unsigned char Bool
----------------------------
static Bool isempty_RL(EState *s)
{
  if ((s->state_in_ch < 256) && (s->state_in_len > 0))
  {
    return (Bool) 0;
  }
  else
    return (Bool) 1;
}


----------------------------
static Bool handle_compress(bz_stream *strm)
{
  Bool progress_in = (Bool) 0;
  Bool progress_out = (Bool) 0;
  EState *s = strm->state;
  while ((Bool) 1)
  {
    if (s->state == 1)
    {
      progress_out |= copy_output_until_stop(s);
      if (s->state_out_pos < s->numZ)
      {
        break;
      }
      if (((s->mode == 4) && (s->avail_in_expect == 0)) && isempty_RL(s))
      {
        break;
      }
      prepare_new_block(s);
      s->state = 2;
      if (((s->mode == 3) && (s->avail_in_expect == 0)) && isempty_RL(s))
      {
        break;
      }
    }
    if (s->state == 2)
    {
      progress_in |= copy_input_until_stop(s);
      if ((s->mode != 2) && (s->avail_in_expect == 0))
      {
        flush_RL(s);
        BZ2_compressBlock(s, (Bool) (s->mode == 4));
        s->state = 1;
      }
      else
        if (s->nblock >= s->nblockMAX)
      {
        BZ2_compressBlock(s, (Bool) 0);
        s->state = 1;
      }
      else
        if (s->strm->avail_in == 0)
      {
        break;
      }
    }
  }

  return progress_in || progress_out;
}


----------------------------
***/


// hint:  ['n_ref is a mutable refrence to Int32', 'n2_ref is a mutable refrence to Int32', 'ret_ref is a mutable refrence to Int32']
void helper_BZ2_bzWriteClose64_1(Int32 * const n_ref, Int32 * const n2_ref, Int32 * const ret_ref, int * const bzerror, bzFile * const bzf)
{
  Int32 n = *n_ref;
  Int32 n2 = *n2_ref;
  Int32 ret = *ret_ref;
  while ((Bool) 1)
  {
    bzf->strm.avail_out = 5000;
    bzf->strm.next_out = bzf->buf;
    ret = BZ2_bzCompress(&bzf->strm, 2);
    if ((ret != 3) && (ret != 4))
    {
      {
        if (bzerror != 0)
        {
          *bzerror = ret;
        }
        if (bzf != 0)
        {
          bzf->lastErr = ret;
        }
      }
      ;
      return;
    }
    ;
    if (bzf->strm.avail_out < 5000)
    {
      n = 5000 - bzf->strm.avail_out;
      n2 = fwrite((void *) bzf->buf, sizeof(UChar), n, bzf->handle);
      if ((n != n2) || ferror(bzf->handle))
      {
        {
          if (bzerror != 0)
          {
            *bzerror = -6;
          }
          if (bzf != 0)
          {
            bzf->lastErr = -6;
          }
        }
        ;
        return;
      }
      ;
    }
    if (ret == 4)
    {
      break;
    }
  }

  *n_ref = n;
  *n2_ref = n2;
  *ret_ref = ret;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
typedef struct 
{
  FILE *handle;
  Char buf[5000];
  Int32 bufN;
  Bool writing;
  bz_stream strm;
  Int32 lastErr;
  Bool initialisedOk;
} bzFile
----------------------------
int BZ2_bzCompress(bz_stream *strm, int action)
{
  Bool progress;
  EState *s;
  unsigned int s_idx = 0;
  if (strm == 0)
  {
    return -2;
  }
  s_idx = strm->state;
  if ((&s[s_idx]) == 0)
  {
    return -2;
  }
  if (s->strm != strm)
  {
    return -2;
  }
  preswitch:
  switch (s->mode)
  {
    case 1:
    {
      return -1;
    }

    case 2:
    {
      if (action == 0)
      {
        progress = handle_compress(strm);
        return (progress) ? (1) : (-2);
      }
      else
        if (action == 1)
      {
        s->avail_in_expect = strm->avail_in;
        s->mode = 3;
        goto preswitch;
      }
      else
        if (action == 2)
      {
        s->avail_in_expect = strm->avail_in;
        s->mode = 4;
        goto preswitch;
      }
      else
        return -2;
    }

    case 3:
    {
      if (action != 1)
      {
        return -1;
      }
      if (s->avail_in_expect != s->strm->avail_in)
      {
        return -1;
      }
      progress = handle_compress(strm);
      if (((s->avail_in_expect > 0) || (!isempty_RL(s))) || (s->state_out_pos < s->numZ))
      {
        return 2;
      }
      s->mode = 2;
      return 1;
    }

    case 4:
    {
      if (action != 2)
      {
        return -1;
      }
      if (s->avail_in_expect != s->strm->avail_in)
      {
        return -1;
      }
      progress = handle_compress(strm);
      if (!progress)
      {
        return -1;
      }
      if (((s->avail_in_expect > 0) || (!isempty_RL(s))) || (s->state_out_pos < s->numZ))
      {
        return 3;
      }
      s->mode = 1;
      return 4;
    }

  }


  return 0;
}


----------------------------
***/


void BZ2_bzWriteClose64(int *bzerror, BZFILE *b, int abandon, unsigned int *nbytes_in_lo32, unsigned int *nbytes_in_hi32, unsigned int *nbytes_out_lo32, unsigned int *nbytes_out_hi32)
{
  Int32 n;
  Int32 n2;
  Int32 ret;
  bzFile *bzf = (bzFile *) b;
  if (bzf == 0)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = 0;
      }
      if (bzf != 0)
      {
        bzf->lastErr = 0;
      }
    }
    ;
    return;
  }
  ;
  if (!bzf->writing)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -1;
      }
      if (bzf != 0)
      {
        bzf->lastErr = -1;
      }
    }
    ;
    return;
  }
  ;
  if (ferror(bzf->handle))
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -6;
      }
      if (bzf != 0)
      {
        bzf->lastErr = -6;
      }
    }
    ;
    return;
  }
  ;
  if (nbytes_in_lo32 != 0)
  {
    *nbytes_in_lo32 = 0;
  }
  if (nbytes_in_hi32 != 0)
  {
    *nbytes_in_hi32 = 0;
  }
  if (nbytes_out_lo32 != 0)
  {
    *nbytes_out_lo32 = 0;
  }
  if (nbytes_out_hi32 != 0)
  {
    *nbytes_out_hi32 = 0;
  }
  if ((!abandon) && (bzf->lastErr == 0))
  {
    helper_BZ2_bzWriteClose64_1(&n, &n2, &ret, bzerror, bzf);
  }
  if ((!abandon) && (!ferror(bzf->handle)))
  {
    fflush(bzf->handle);
    if (ferror(bzf->handle))
    {
      {
        if (bzerror != 0)
        {
          *bzerror = -6;
        }
        if (bzf != 0)
        {
          bzf->lastErr = -6;
        }
      }
      ;
      return;
    }
    ;
  }
  if (nbytes_in_lo32 != 0)
  {
    *nbytes_in_lo32 = bzf->strm.total_in_lo32;
  }
  if (nbytes_in_hi32 != 0)
  {
    *nbytes_in_hi32 = bzf->strm.total_in_hi32;
  }
  if (nbytes_out_lo32 != 0)
  {
    *nbytes_out_lo32 = bzf->strm.total_out_lo32;
  }
  if (nbytes_out_hi32 != 0)
  {
    *nbytes_out_hi32 = bzf->strm.total_out_hi32;
  }
  {
    if (bzerror != 0)
    {
      *bzerror = 0;
    }
    if (bzf != 0)
    {
      bzf->lastErr = 0;
    }
  }
  ;
  BZ2_bzCompressEnd(&bzf->strm);
  free(bzf);
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
typedef struct 
{
  FILE *handle;
  Char buf[5000];
  Int32 bufN;
  Bool writing;
  bz_stream strm;
  Int32 lastErr;
  Bool initialisedOk;
} bzFile
----------------------------
int BZ2_bzCompressEnd(bz_stream *strm)
{
  EState *s;
  unsigned int s_idx = 0;
  if (strm == 0)
  {
    return -2;
  }
  s_idx = strm->state;
  if ((&s[s_idx]) == 0)
  {
    return -2;
  }
  if (s->strm != strm)
  {
    return -2;
  }
  if (s->arr1 != 0)
  {
    strm->bzfree(strm->opaque, s->arr1);
  }
  if (s->arr2 != 0)
  {
    strm->bzfree(strm->opaque, s->arr2);
  }
  if (s->ftab != 0)
  {
    strm->bzfree(strm->opaque, s->ftab);
  }
  strm->bzfree(strm->opaque, strm->state);
  strm->state = 0;
  return 0;
}


----------------------------
void helper_BZ2_bzWriteClose64_1(Int32 * const n_ref, Int32 * const n2_ref, Int32 * const ret_ref, int * const bzerror, bzFile * const bzf)
{
  Int32 n = *n_ref;
  Int32 n2 = *n2_ref;
  Int32 ret = *ret_ref;
  while ((Bool) 1)
  {
    bzf->strm.avail_out = 5000;
    bzf->strm.next_out = bzf->buf;
    ret = BZ2_bzCompress(&bzf->strm, 2);
    if ((ret != 3) && (ret != 4))
    {
      {
        if (bzerror != 0)
        {
          *bzerror = ret;
        }
        if (bzf != 0)
        {
          bzf->lastErr = ret;
        }
      }
      ;
      return;
    }
    ;
    if (bzf->strm.avail_out < 5000)
    {
      n = 5000 - bzf->strm.avail_out;
      n2 = fwrite((void *) bzf->buf, sizeof(UChar), n, bzf->handle);
      if ((n != n2) || ferror(bzf->handle))
      {
        {
          if (bzerror != 0)
          {
            *bzerror = -6;
          }
          if (bzf != 0)
          {
            bzf->lastErr = -6;
          }
        }
        ;
        return;
      }
      ;
    }
    if (ret == 4)
    {
      break;
    }
  }

  *n_ref = n;
  *n2_ref = n2;
  *ret_ref = ret;
}


----------------------------
typedef void BZFILE
----------------------------
***/


void BZ2_bzWriteClose(int *bzerror, BZFILE *b, int abandon, unsigned int *nbytes_in, unsigned int *nbytes_out)
{
  BZ2_bzWriteClose64(bzerror, b, abandon, nbytes_in, 0, nbytes_out, 0);
}


/*** DEPENDENCIES:
typedef void BZFILE
----------------------------
void BZ2_bzWriteClose64(int *bzerror, BZFILE *b, int abandon, unsigned int *nbytes_in_lo32, unsigned int *nbytes_in_hi32, unsigned int *nbytes_out_lo32, unsigned int *nbytes_out_hi32)
{
  Int32 n;
  Int32 n2;
  Int32 ret;
  bzFile *bzf = (bzFile *) b;
  if (bzf == 0)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = 0;
      }
      if (bzf != 0)
      {
        bzf->lastErr = 0;
      }
    }
    ;
    return;
  }
  ;
  if (!bzf->writing)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -1;
      }
      if (bzf != 0)
      {
        bzf->lastErr = -1;
      }
    }
    ;
    return;
  }
  ;
  if (ferror(bzf->handle))
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -6;
      }
      if (bzf != 0)
      {
        bzf->lastErr = -6;
      }
    }
    ;
    return;
  }
  ;
  if (nbytes_in_lo32 != 0)
  {
    *nbytes_in_lo32 = 0;
  }
  if (nbytes_in_hi32 != 0)
  {
    *nbytes_in_hi32 = 0;
  }
  if (nbytes_out_lo32 != 0)
  {
    *nbytes_out_lo32 = 0;
  }
  if (nbytes_out_hi32 != 0)
  {
    *nbytes_out_hi32 = 0;
  }
  if ((!abandon) && (bzf->lastErr == 0))
  {
    helper_BZ2_bzWriteClose64_1(&n, &n2, &ret, bzerror, bzf);
  }
  if ((!abandon) && (!ferror(bzf->handle)))
  {
    fflush(bzf->handle);
    if (ferror(bzf->handle))
    {
      {
        if (bzerror != 0)
        {
          *bzerror = -6;
        }
        if (bzf != 0)
        {
          bzf->lastErr = -6;
        }
      }
      ;
      return;
    }
    ;
  }
  if (nbytes_in_lo32 != 0)
  {
    *nbytes_in_lo32 = bzf->strm.total_in_lo32;
  }
  if (nbytes_in_hi32 != 0)
  {
    *nbytes_in_hi32 = bzf->strm.total_in_hi32;
  }
  if (nbytes_out_lo32 != 0)
  {
    *nbytes_out_lo32 = bzf->strm.total_out_lo32;
  }
  if (nbytes_out_hi32 != 0)
  {
    *nbytes_out_hi32 = bzf->strm.total_out_hi32;
  }
  {
    if (bzerror != 0)
    {
      *bzerror = 0;
    }
    if (bzf != 0)
    {
      bzf->lastErr = 0;
    }
  }
  ;
  BZ2_bzCompressEnd(&bzf->strm);
  free(bzf);
}


----------------------------
***/


// hint:  ['k1_ref is a mutable refrence to UChar']
Bool helper_helper_unRLE_obuf_to_output_FAST_2_1(UChar * const k1_ref, DState * const s)
{
  UChar k1 = *k1_ref;
  while ((Bool) 1)
  {
    if (s->strm->avail_out == 0)
    {
      return (Bool) 0;
    }
    if (s->state_out_len == 0)
    {
      break;
    }
    *((UChar *) s->strm->next_out) = s->state_out_ch;
    {
      s->calculatedBlockCRC = (s->calculatedBlockCRC << 8) ^ BZ2_crc32Table[(s->calculatedBlockCRC >> 24) ^ ((UChar) s->state_out_ch)];
    }
    ;
    s->state_out_len -= 1;
    s->strm->next_out += 1;
    s->strm->avail_out -= 1;
    s->strm->total_out_lo32 += 1;
    if (s->strm->total_out_lo32 == 0)
    {
      s->strm->total_out_hi32 += 1;
    }
  }

  if (s->nblock_used == (s->save_nblock + 1))
  {
    return (Bool) 0;
  }
  if (s->nblock_used > (s->save_nblock + 1))
  {
    return (Bool) 1;
  }
  s->state_out_len = 1;
  s->state_out_ch = s->k0;
  if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
  {
    return (Bool) 1;
  }
  s->tPos = s->tt[s->tPos];
  k1 = (UChar) (s->tPos & 0xff);
  s->tPos >>= 8;
  ;
  if (s->rNToGo == 0)
  {
    s->rNToGo = BZ2_rNums[s->rTPos];
    s->rTPos += 1;
    if (s->rTPos == 512)
    {
      s->rTPos = 0;
    }
  }
  s->rNToGo -= 1;
  ;
  k1 ^= (s->rNToGo == 1) ? (1) : (0);
  s->nblock_used += 1;
  if (s->nblock_used == (s->save_nblock + 1))
  {
    continue;
  }
  if (k1 != s->k0)
  {
    s->k0 = k1;
    continue;
  }
  ;
  s->state_out_len = 2;
  if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
  {
    return (Bool) 1;
  }
  s->tPos = s->tt[s->tPos];
  k1 = (UChar) (s->tPos & 0xff);
  s->tPos >>= 8;
  ;
  if (s->rNToGo == 0)
  {
    s->rNToGo = BZ2_rNums[s->rTPos];
    s->rTPos += 1;
    if (s->rTPos == 512)
    {
      s->rTPos = 0;
    }
  }
  s->rNToGo -= 1;
  ;
  k1 ^= (s->rNToGo == 1) ? (1) : (0);
  s->nblock_used += 1;
  if (s->nblock_used == (s->save_nblock + 1))
  {
    continue;
  }
  if (k1 != s->k0)
  {
    s->k0 = k1;
    continue;
  }
  ;
  s->state_out_len = 3;
  if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
  {
    return (Bool) 1;
  }
  s->tPos = s->tt[s->tPos];
  k1 = (UChar) (s->tPos & 0xff);
  s->tPos >>= 8;
  ;
  if (s->rNToGo == 0)
  {
    s->rNToGo = BZ2_rNums[s->rTPos];
    s->rTPos += 1;
    if (s->rTPos == 512)
    {
      s->rTPos = 0;
    }
  }
  s->rNToGo -= 1;
  ;
  k1 ^= (s->rNToGo == 1) ? (1) : (0);
  s->nblock_used += 1;
  if (s->nblock_used == (s->save_nblock + 1))
  {
    continue;
  }
  if (k1 != s->k0)
  {
    s->k0 = k1;
    continue;
  }
  ;
  if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
  {
    return (Bool) 1;
  }
  s->tPos = s->tt[s->tPos];
  k1 = (UChar) (s->tPos & 0xff);
  s->tPos >>= 8;
  ;
  if (s->rNToGo == 0)
  {
    s->rNToGo = BZ2_rNums[s->rTPos];
    s->rTPos += 1;
    if (s->rTPos == 512)
    {
      s->rTPos = 0;
    }
  }
  s->rNToGo -= 1;
  ;
  k1 ^= (s->rNToGo == 1) ? (1) : (0);
  s->nblock_used += 1;
  s->state_out_len = ((Int32) k1) + 4;
  if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
  {
    return (Bool) 1;
  }
  s->tPos = s->tt[s->tPos];
  s->k0 = (UChar) (s->tPos & 0xff);
  s->tPos >>= 8;
  ;
  if (s->rNToGo == 0)
  {
    s->rNToGo = BZ2_rNums[s->rTPos];
    s->rTPos += 1;
    if (s->rTPos == 512)
    {
      s->rTPos = 0;
    }
  }
  s->rNToGo -= 1;
  ;
  s->k0 ^= (s->rNToGo == 1) ? (1) : (0);
  s->nblock_used += 1;
  *k1_ref = k1;
}


/*** DEPENDENCIES:
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
} DState
----------------------------
typedef char Char
----------------------------
typedef unsigned char UChar
----------------------------
extern Int32 BZ2_rNums[512]
----------------------------
extern UInt32 BZ2_crc32Table[256]
----------------------------
***/


// hint:  ['k1_ref is a mutable refrence to UChar']
Bool helper_unRLE_obuf_to_output_FAST_2(UChar * const k1_ref, DState * const s)
{
  UChar k1 = *k1_ref;
  while ((Bool) 1)
  {
    helper_helper_unRLE_obuf_to_output_FAST_2_1(&k1, s);
  }

  *k1_ref = k1;
}


/*** DEPENDENCIES:
typedef unsigned char UChar
----------------------------
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
} DState
----------------------------
typedef char Char
----------------------------
Bool helper_helper_unRLE_obuf_to_output_FAST_2_1(UChar * const k1_ref, DState * const s)
{
  UChar k1 = *k1_ref;
  while ((Bool) 1)
  {
    if (s->strm->avail_out == 0)
    {
      return (Bool) 0;
    }
    if (s->state_out_len == 0)
    {
      break;
    }
    *((UChar *) s->strm->next_out) = s->state_out_ch;
    {
      s->calculatedBlockCRC = (s->calculatedBlockCRC << 8) ^ BZ2_crc32Table[(s->calculatedBlockCRC >> 24) ^ ((UChar) s->state_out_ch)];
    }
    ;
    s->state_out_len -= 1;
    s->strm->next_out += 1;
    s->strm->avail_out -= 1;
    s->strm->total_out_lo32 += 1;
    if (s->strm->total_out_lo32 == 0)
    {
      s->strm->total_out_hi32 += 1;
    }
  }

  if (s->nblock_used == (s->save_nblock + 1))
  {
    return (Bool) 0;
  }
  if (s->nblock_used > (s->save_nblock + 1))
  {
    return (Bool) 1;
  }
  s->state_out_len = 1;
  s->state_out_ch = s->k0;
  if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
  {
    return (Bool) 1;
  }
  s->tPos = s->tt[s->tPos];
  k1 = (UChar) (s->tPos & 0xff);
  s->tPos >>= 8;
  ;
  if (s->rNToGo == 0)
  {
    s->rNToGo = BZ2_rNums[s->rTPos];
    s->rTPos += 1;
    if (s->rTPos == 512)
    {
      s->rTPos = 0;
    }
  }
  s->rNToGo -= 1;
  ;
  k1 ^= (s->rNToGo == 1) ? (1) : (0);
  s->nblock_used += 1;
  if (s->nblock_used == (s->save_nblock + 1))
  {
    continue;
  }
  if (k1 != s->k0)
  {
    s->k0 = k1;
    continue;
  }
  ;
  s->state_out_len = 2;
  if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
  {
    return (Bool) 1;
  }
  s->tPos = s->tt[s->tPos];
  k1 = (UChar) (s->tPos & 0xff);
  s->tPos >>= 8;
  ;
  if (s->rNToGo == 0)
  {
    s->rNToGo = BZ2_rNums[s->rTPos];
    s->rTPos += 1;
    if (s->rTPos == 512)
    {
      s->rTPos = 0;
    }
  }
  s->rNToGo -= 1;
  ;
  k1 ^= (s->rNToGo == 1) ? (1) : (0);
  s->nblock_used += 1;
  if (s->nblock_used == (s->save_nblock + 1))
  {
    continue;
  }
  if (k1 != s->k0)
  {
    s->k0 = k1;
    continue;
  }
  ;
  s->state_out_len = 3;
  if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
  {
    return (Bool) 1;
  }
  s->tPos = s->tt[s->tPos];
  k1 = (UChar) (s->tPos & 0xff);
  s->tPos >>= 8;
  ;
  if (s->rNToGo == 0)
  {
    s->rNToGo = BZ2_rNums[s->rTPos];
    s->rTPos += 1;
    if (s->rTPos == 512)
    {
      s->rTPos = 0;
    }
  }
  s->rNToGo -= 1;
  ;
  k1 ^= (s->rNToGo == 1) ? (1) : (0);
  s->nblock_used += 1;
  if (s->nblock_used == (s->save_nblock + 1))
  {
    continue;
  }
  if (k1 != s->k0)
  {
    s->k0 = k1;
    continue;
  }
  ;
  if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
  {
    return (Bool) 1;
  }
  s->tPos = s->tt[s->tPos];
  k1 = (UChar) (s->tPos & 0xff);
  s->tPos >>= 8;
  ;
  if (s->rNToGo == 0)
  {
    s->rNToGo = BZ2_rNums[s->rTPos];
    s->rTPos += 1;
    if (s->rTPos == 512)
    {
      s->rTPos = 0;
    }
  }
  s->rNToGo -= 1;
  ;
  k1 ^= (s->rNToGo == 1) ? (1) : (0);
  s->nblock_used += 1;
  s->state_out_len = ((Int32) k1) + 4;
  if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
  {
    return (Bool) 1;
  }
  s->tPos = s->tt[s->tPos];
  s->k0 = (UChar) (s->tPos & 0xff);
  s->tPos >>= 8;
  ;
  if (s->rNToGo == 0)
  {
    s->rNToGo = BZ2_rNums[s->rTPos];
    s->rTPos += 1;
    if (s->rTPos == 512)
    {
      s->rTPos = 0;
    }
  }
  s->rNToGo -= 1;
  ;
  s->k0 ^= (s->rNToGo == 1) ? (1) : (0);
  s->nblock_used += 1;
  *k1_ref = k1;
}


----------------------------
***/


// hint:  ['c_calculatedBlockCRC_ref is a mutable refrence to UInt32', 'c_state_out_len_ref is a mutable refrence to Int32', 'cs_next_out_idx_ref is a mutable refrence to unsigned int', 'cs_avail_out_ref is a mutable refrence to unsigned int']
void helper_helper_helper_unRLE_obuf_to_output_FAST_1_1_1(UInt32 * const c_calculatedBlockCRC_ref, Int32 * const c_state_out_len_ref, unsigned int * const cs_next_out_idx_ref, unsigned int * const cs_avail_out_ref, char * const cs_next_out, UChar c_state_out_ch)
{
  UInt32 c_calculatedBlockCRC = *c_calculatedBlockCRC_ref;
  Int32 c_state_out_len = *c_state_out_len_ref;
  unsigned int cs_next_out_idx = *cs_next_out_idx_ref;
  unsigned int cs_avail_out = *cs_avail_out_ref;
  while ((Bool) 1)
  {
    if (cs_avail_out == 0)
    {
      goto return_notr;
    }
    if (c_state_out_len == 1)
    {
      break;
    }
    *((UChar *) cs_next_out) = c_state_out_ch;
    {
      c_calculatedBlockCRC = (c_calculatedBlockCRC << 8) ^ BZ2_crc32Table[(c_calculatedBlockCRC >> 24) ^ ((UChar) c_state_out_ch)];
    }
    ;
    c_state_out_len -= 1;
    cs_next_out_idx += 1;
    cs_avail_out -= 1;
  }

  s_state_out_len_eq_one:
  {
    if (cs_avail_out == 0)
    {
      c_state_out_len = 1;
      goto return_notr;
    }
    ;
    *((UChar *) cs_next_out) = c_state_out_ch;
    {
      c_calculatedBlockCRC = (c_calculatedBlockCRC << 8) ^ BZ2_crc32Table[(c_calculatedBlockCRC >> 24) ^ ((UChar) c_state_out_ch)];
    }
    ;
    cs_next_out_idx += 1;
    cs_avail_out -= 1;
  }

  *c_calculatedBlockCRC_ref = c_calculatedBlockCRC;
  *c_state_out_len_ref = c_state_out_len;
  *cs_next_out_idx_ref = cs_next_out_idx;
  *cs_avail_out_ref = cs_avail_out;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
typedef unsigned int UInt32
----------------------------
typedef char Char
----------------------------
typedef unsigned char UChar
----------------------------
extern UInt32 BZ2_crc32Table[256]
----------------------------
***/


// hint:  ['k1_ref is a mutable refrence to UChar', 'c_calculatedBlockCRC_ref is a mutable refrence to UInt32', 'c_state_out_ch_ref is a mutable refrence to UChar', 'c_state_out_len_ref is a mutable refrence to Int32', 'c_nblock_used_ref is a mutable refrence to Int32', 'c_k0_ref is a mutable refrence to Int32', 'c_tPos_ref is a mutable refrence to UInt32', 'cs_next_out_idx_ref is a mutable refrence to unsigned int', 'cs_avail_out_ref is a mutable refrence to unsigned int']
Bool helper_helper_unRLE_obuf_to_output_FAST_1_1(UChar * const k1_ref, UInt32 * const c_calculatedBlockCRC_ref, UChar * const c_state_out_ch_ref, Int32 * const c_state_out_len_ref, Int32 * const c_nblock_used_ref, Int32 * const c_k0_ref, UInt32 * const c_tPos_ref, unsigned int * const cs_next_out_idx_ref, unsigned int * const cs_avail_out_ref, UInt32 * const c_tt, char * const cs_next_out, Int32 ro_blockSize100k, Int32 s_save_nblockPP)
{
  UChar k1 = *k1_ref;
  UInt32 c_calculatedBlockCRC = *c_calculatedBlockCRC_ref;
  UChar c_state_out_ch = *c_state_out_ch_ref;
  Int32 c_state_out_len = *c_state_out_len_ref;
  Int32 c_nblock_used = *c_nblock_used_ref;
  Int32 c_k0 = *c_k0_ref;
  UInt32 c_tPos = *c_tPos_ref;
  unsigned int cs_next_out_idx = *cs_next_out_idx_ref;
  unsigned int cs_avail_out = *cs_avail_out_ref;
  if (c_state_out_len > 0)
  {
    helper_helper_helper_unRLE_obuf_to_output_FAST_1_1_1(&c_calculatedBlockCRC, &c_state_out_len, &cs_next_out_idx, &cs_avail_out, cs_next_out, c_state_out_ch);
  }
  if (c_nblock_used > s_save_nblockPP)
  {
    return (Bool) 1;
  }
  if (c_nblock_used == s_save_nblockPP)
  {
    c_state_out_len = 0;
    goto return_notr;
  }
  ;
  c_state_out_ch = c_k0;
  if (c_tPos >= (((UInt32) 100000) * ((UInt32) ro_blockSize100k)))
  {
    return (Bool) 1;
  }
  c_tPos = c_tt[c_tPos];
  k1 = (UChar) (c_tPos & 0xff);
  c_tPos >>= 8;
  ;
  c_nblock_used += 1;
  if (k1 != c_k0)
  {
    c_k0 = k1;
    goto s_state_out_len_eq_one;
  }
  ;
  if (c_nblock_used == s_save_nblockPP)
  {
    goto s_state_out_len_eq_one;
  }
  c_state_out_len = 2;
  if (c_tPos >= (((UInt32) 100000) * ((UInt32) ro_blockSize100k)))
  {
    return (Bool) 1;
  }
  c_tPos = c_tt[c_tPos];
  k1 = (UChar) (c_tPos & 0xff);
  c_tPos >>= 8;
  ;
  c_nblock_used += 1;
  if (c_nblock_used == s_save_nblockPP)
  {
    continue;
  }
  if (k1 != c_k0)
  {
    c_k0 = k1;
    continue;
  }
  ;
  c_state_out_len = 3;
  if (c_tPos >= (((UInt32) 100000) * ((UInt32) ro_blockSize100k)))
  {
    return (Bool) 1;
  }
  c_tPos = c_tt[c_tPos];
  k1 = (UChar) (c_tPos & 0xff);
  c_tPos >>= 8;
  ;
  c_nblock_used += 1;
  if (c_nblock_used == s_save_nblockPP)
  {
    continue;
  }
  if (k1 != c_k0)
  {
    c_k0 = k1;
    continue;
  }
  ;
  if (c_tPos >= (((UInt32) 100000) * ((UInt32) ro_blockSize100k)))
  {
    return (Bool) 1;
  }
  c_tPos = c_tt[c_tPos];
  k1 = (UChar) (c_tPos & 0xff);
  c_tPos >>= 8;
  ;
  c_nblock_used += 1;
  c_state_out_len = ((Int32) k1) + 4;
  if (c_tPos >= (((UInt32) 100000) * ((UInt32) ro_blockSize100k)))
  {
    return (Bool) 1;
  }
  c_tPos = c_tt[c_tPos];
  c_k0 = (UChar) (c_tPos & 0xff);
  c_tPos >>= 8;
  ;
  c_nblock_used += 1;
  *k1_ref = k1;
  *c_calculatedBlockCRC_ref = c_calculatedBlockCRC;
  *c_state_out_ch_ref = c_state_out_ch;
  *c_state_out_len_ref = c_state_out_len;
  *c_nblock_used_ref = c_nblock_used;
  *c_k0_ref = c_k0;
  *c_tPos_ref = c_tPos;
  *cs_next_out_idx_ref = cs_next_out_idx;
  *cs_avail_out_ref = cs_avail_out;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
typedef unsigned int UInt32
----------------------------
typedef char Char
----------------------------
void helper_helper_helper_unRLE_obuf_to_output_FAST_1_1_1(UInt32 * const c_calculatedBlockCRC_ref, Int32 * const c_state_out_len_ref, unsigned int * const cs_next_out_idx_ref, unsigned int * const cs_avail_out_ref, char * const cs_next_out, UChar c_state_out_ch)
{
  UInt32 c_calculatedBlockCRC = *c_calculatedBlockCRC_ref;
  Int32 c_state_out_len = *c_state_out_len_ref;
  unsigned int cs_next_out_idx = *cs_next_out_idx_ref;
  unsigned int cs_avail_out = *cs_avail_out_ref;
  while ((Bool) 1)
  {
    if (cs_avail_out == 0)
    {
      goto return_notr;
    }
    if (c_state_out_len == 1)
    {
      break;
    }
    *((UChar *) cs_next_out) = c_state_out_ch;
    {
      c_calculatedBlockCRC = (c_calculatedBlockCRC << 8) ^ BZ2_crc32Table[(c_calculatedBlockCRC >> 24) ^ ((UChar) c_state_out_ch)];
    }
    ;
    c_state_out_len -= 1;
    cs_next_out_idx += 1;
    cs_avail_out -= 1;
  }

  s_state_out_len_eq_one:
  {
    if (cs_avail_out == 0)
    {
      c_state_out_len = 1;
      goto return_notr;
    }
    ;
    *((UChar *) cs_next_out) = c_state_out_ch;
    {
      c_calculatedBlockCRC = (c_calculatedBlockCRC << 8) ^ BZ2_crc32Table[(c_calculatedBlockCRC >> 24) ^ ((UChar) c_state_out_ch)];
    }
    ;
    cs_next_out_idx += 1;
    cs_avail_out -= 1;
  }

  *c_calculatedBlockCRC_ref = c_calculatedBlockCRC;
  *c_state_out_len_ref = c_state_out_len;
  *cs_next_out_idx_ref = cs_next_out_idx;
  *cs_avail_out_ref = cs_avail_out;
}


----------------------------
typedef unsigned char UChar
----------------------------
***/


// hint:  ['k1_ref is a mutable refrence to UChar']
Bool helper_unRLE_obuf_to_output_FAST_1(UChar * const k1_ref, DState * const s)
{
  UChar k1 = *k1_ref;
  UInt32 c_calculatedBlockCRC = s->calculatedBlockCRC;
  UChar c_state_out_ch = s->state_out_ch;
  Int32 c_state_out_len = s->state_out_len;
  Int32 c_nblock_used = s->nblock_used;
  Int32 c_k0 = s->k0;
  UInt32 *c_tt = s->tt;
  UInt32 c_tPos = s->tPos;
  char *cs_next_out = s->strm->next_out;
  unsigned int cs_next_out_idx = 0;
  unsigned int cs_avail_out = s->strm->avail_out;
  Int32 ro_blockSize100k = s->blockSize100k;
  UInt32 avail_out_INIT = cs_avail_out;
  Int32 s_save_nblockPP = s->save_nblock + 1;
  unsigned int total_out_lo32_old;
  while ((Bool) 1)
  {
    helper_helper_unRLE_obuf_to_output_FAST_1_1(&k1, &c_calculatedBlockCRC, &c_state_out_ch, &c_state_out_len, &c_nblock_used, &c_k0, &c_tPos, &cs_next_out_idx, &cs_avail_out, c_tt, cs_next_out, ro_blockSize100k, s_save_nblockPP);
  }

  return_notr:
  total_out_lo32_old = s->strm->total_out_lo32;

  s->strm->total_out_lo32 += avail_out_INIT - cs_avail_out;
  if (s->strm->total_out_lo32 < total_out_lo32_old)
  {
    s->strm->total_out_hi32 += 1;
  }
  s->calculatedBlockCRC = c_calculatedBlockCRC;
  s->state_out_ch = c_state_out_ch;
  s->state_out_len = c_state_out_len;
  s->nblock_used = c_nblock_used;
  s->k0 = c_k0;
  s->tt = c_tt;
  s->tPos = c_tPos;
  s->strm->next_out = &cs_next_out[cs_next_out_idx];
  s->strm->avail_out = cs_avail_out;
  *k1_ref = k1;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
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
} DState
----------------------------
typedef unsigned int UInt32
----------------------------
typedef char Char
----------------------------
typedef unsigned char UChar
----------------------------
Bool helper_helper_unRLE_obuf_to_output_FAST_1_1(UChar * const k1_ref, UInt32 * const c_calculatedBlockCRC_ref, UChar * const c_state_out_ch_ref, Int32 * const c_state_out_len_ref, Int32 * const c_nblock_used_ref, Int32 * const c_k0_ref, UInt32 * const c_tPos_ref, unsigned int * const cs_next_out_idx_ref, unsigned int * const cs_avail_out_ref, UInt32 * const c_tt, char * const cs_next_out, Int32 ro_blockSize100k, Int32 s_save_nblockPP)
{
  UChar k1 = *k1_ref;
  UInt32 c_calculatedBlockCRC = *c_calculatedBlockCRC_ref;
  UChar c_state_out_ch = *c_state_out_ch_ref;
  Int32 c_state_out_len = *c_state_out_len_ref;
  Int32 c_nblock_used = *c_nblock_used_ref;
  Int32 c_k0 = *c_k0_ref;
  UInt32 c_tPos = *c_tPos_ref;
  unsigned int cs_next_out_idx = *cs_next_out_idx_ref;
  unsigned int cs_avail_out = *cs_avail_out_ref;
  if (c_state_out_len > 0)
  {
    helper_helper_helper_unRLE_obuf_to_output_FAST_1_1_1(&c_calculatedBlockCRC, &c_state_out_len, &cs_next_out_idx, &cs_avail_out, cs_next_out, c_state_out_ch);
  }
  if (c_nblock_used > s_save_nblockPP)
  {
    return (Bool) 1;
  }
  if (c_nblock_used == s_save_nblockPP)
  {
    c_state_out_len = 0;
    goto return_notr;
  }
  ;
  c_state_out_ch = c_k0;
  if (c_tPos >= (((UInt32) 100000) * ((UInt32) ro_blockSize100k)))
  {
    return (Bool) 1;
  }
  c_tPos = c_tt[c_tPos];
  k1 = (UChar) (c_tPos & 0xff);
  c_tPos >>= 8;
  ;
  c_nblock_used += 1;
  if (k1 != c_k0)
  {
    c_k0 = k1;
    goto s_state_out_len_eq_one;
  }
  ;
  if (c_nblock_used == s_save_nblockPP)
  {
    goto s_state_out_len_eq_one;
  }
  c_state_out_len = 2;
  if (c_tPos >= (((UInt32) 100000) * ((UInt32) ro_blockSize100k)))
  {
    return (Bool) 1;
  }
  c_tPos = c_tt[c_tPos];
  k1 = (UChar) (c_tPos & 0xff);
  c_tPos >>= 8;
  ;
  c_nblock_used += 1;
  if (c_nblock_used == s_save_nblockPP)
  {
    continue;
  }
  if (k1 != c_k0)
  {
    c_k0 = k1;
    continue;
  }
  ;
  c_state_out_len = 3;
  if (c_tPos >= (((UInt32) 100000) * ((UInt32) ro_blockSize100k)))
  {
    return (Bool) 1;
  }
  c_tPos = c_tt[c_tPos];
  k1 = (UChar) (c_tPos & 0xff);
  c_tPos >>= 8;
  ;
  c_nblock_used += 1;
  if (c_nblock_used == s_save_nblockPP)
  {
    continue;
  }
  if (k1 != c_k0)
  {
    c_k0 = k1;
    continue;
  }
  ;
  if (c_tPos >= (((UInt32) 100000) * ((UInt32) ro_blockSize100k)))
  {
    return (Bool) 1;
  }
  c_tPos = c_tt[c_tPos];
  k1 = (UChar) (c_tPos & 0xff);
  c_tPos >>= 8;
  ;
  c_nblock_used += 1;
  c_state_out_len = ((Int32) k1) + 4;
  if (c_tPos >= (((UInt32) 100000) * ((UInt32) ro_blockSize100k)))
  {
    return (Bool) 1;
  }
  c_tPos = c_tt[c_tPos];
  c_k0 = (UChar) (c_tPos & 0xff);
  c_tPos >>= 8;
  ;
  c_nblock_used += 1;
  *k1_ref = k1;
  *c_calculatedBlockCRC_ref = c_calculatedBlockCRC;
  *c_state_out_ch_ref = c_state_out_ch;
  *c_state_out_len_ref = c_state_out_len;
  *c_nblock_used_ref = c_nblock_used;
  *c_k0_ref = c_k0;
  *c_tPos_ref = c_tPos;
  *cs_next_out_idx_ref = cs_next_out_idx;
  *cs_avail_out_ref = cs_avail_out;
}


----------------------------
***/


static Bool unRLE_obuf_to_output_FAST(DState *s)
{
  UChar k1;
  if (s->blockRandomised)
  {
    helper_unRLE_obuf_to_output_FAST_2(&k1, s);
  }
  else
  {
    helper_unRLE_obuf_to_output_FAST_1(&k1, s);
  }
  return (Bool) 0;
}


/*** DEPENDENCIES:
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
} DState
----------------------------
Bool helper_unRLE_obuf_to_output_FAST_2(UChar * const k1_ref, DState * const s)
{
  UChar k1 = *k1_ref;
  while ((Bool) 1)
  {
    helper_helper_unRLE_obuf_to_output_FAST_2_1(&k1, s);
  }

  *k1_ref = k1;
}


----------------------------
Bool helper_unRLE_obuf_to_output_FAST_1(UChar * const k1_ref, DState * const s)
{
  UChar k1 = *k1_ref;
  UInt32 c_calculatedBlockCRC = s->calculatedBlockCRC;
  UChar c_state_out_ch = s->state_out_ch;
  Int32 c_state_out_len = s->state_out_len;
  Int32 c_nblock_used = s->nblock_used;
  Int32 c_k0 = s->k0;
  UInt32 *c_tt = s->tt;
  UInt32 c_tPos = s->tPos;
  char *cs_next_out = s->strm->next_out;
  unsigned int cs_next_out_idx = 0;
  unsigned int cs_avail_out = s->strm->avail_out;
  Int32 ro_blockSize100k = s->blockSize100k;
  UInt32 avail_out_INIT = cs_avail_out;
  Int32 s_save_nblockPP = s->save_nblock + 1;
  unsigned int total_out_lo32_old;
  while ((Bool) 1)
  {
    helper_helper_unRLE_obuf_to_output_FAST_1_1(&k1, &c_calculatedBlockCRC, &c_state_out_ch, &c_state_out_len, &c_nblock_used, &c_k0, &c_tPos, &cs_next_out_idx, &cs_avail_out, c_tt, cs_next_out, ro_blockSize100k, s_save_nblockPP);
  }

  return_notr:
  total_out_lo32_old = s->strm->total_out_lo32;

  s->strm->total_out_lo32 += avail_out_INIT - cs_avail_out;
  if (s->strm->total_out_lo32 < total_out_lo32_old)
  {
    s->strm->total_out_hi32 += 1;
  }
  s->calculatedBlockCRC = c_calculatedBlockCRC;
  s->state_out_ch = c_state_out_ch;
  s->state_out_len = c_state_out_len;
  s->nblock_used = c_nblock_used;
  s->k0 = c_k0;
  s->tt = c_tt;
  s->tPos = c_tPos;
  s->strm->next_out = &cs_next_out[cs_next_out_idx];
  s->strm->avail_out = cs_avail_out;
  *k1_ref = k1;
}


----------------------------
typedef char Char
----------------------------
typedef unsigned char UChar
----------------------------
***/


// hint:  ['k1_ref is a mutable refrence to UChar']
Bool helper_helper_unRLE_obuf_to_output_SMALL_2_1(UChar * const k1_ref, DState * const s)
{
  UChar k1 = *k1_ref;
  while ((Bool) 1)
  {
    if (s->strm->avail_out == 0)
    {
      return (Bool) 0;
    }
    if (s->state_out_len == 0)
    {
      break;
    }
    *((UChar *) s->strm->next_out) = s->state_out_ch;
    {
      s->calculatedBlockCRC = (s->calculatedBlockCRC << 8) ^ BZ2_crc32Table[(s->calculatedBlockCRC >> 24) ^ ((UChar) s->state_out_ch)];
    }
    ;
    s->state_out_len -= 1;
    s->strm->next_out += 1;
    s->strm->avail_out -= 1;
    s->strm->total_out_lo32 += 1;
    if (s->strm->total_out_lo32 == 0)
    {
      s->strm->total_out_hi32 += 1;
    }
  }

  if (s->nblock_used == (s->save_nblock + 1))
  {
    return (Bool) 0;
  }
  if (s->nblock_used > (s->save_nblock + 1))
  {
    return (Bool) 1;
  }
  s->state_out_len = 1;
  s->state_out_ch = s->k0;
  if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
  {
    return (Bool) 1;
  }
  k1 = BZ2_indexIntoF(s->tPos, s->cftab);
  s->tPos = ((UInt32) s->ll16[s->tPos]) | (((((UInt32) s->ll4[s->tPos >> 1]) >> ((s->tPos << 2) & 0x4)) & 0xF) << 16);
  ;
  if (s->rNToGo == 0)
  {
    s->rNToGo = BZ2_rNums[s->rTPos];
    s->rTPos += 1;
    if (s->rTPos == 512)
    {
      s->rTPos = 0;
    }
  }
  s->rNToGo -= 1;
  ;
  k1 ^= (s->rNToGo == 1) ? (1) : (0);
  s->nblock_used += 1;
  if (s->nblock_used == (s->save_nblock + 1))
  {
    continue;
  }
  if (k1 != s->k0)
  {
    s->k0 = k1;
    continue;
  }
  ;
  s->state_out_len = 2;
  if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
  {
    return (Bool) 1;
  }
  k1 = BZ2_indexIntoF(s->tPos, s->cftab);
  s->tPos = ((UInt32) s->ll16[s->tPos]) | (((((UInt32) s->ll4[s->tPos >> 1]) >> ((s->tPos << 2) & 0x4)) & 0xF) << 16);
  ;
  if (s->rNToGo == 0)
  {
    s->rNToGo = BZ2_rNums[s->rTPos];
    s->rTPos += 1;
    if (s->rTPos == 512)
    {
      s->rTPos = 0;
    }
  }
  s->rNToGo -= 1;
  ;
  k1 ^= (s->rNToGo == 1) ? (1) : (0);
  s->nblock_used += 1;
  if (s->nblock_used == (s->save_nblock + 1))
  {
    continue;
  }
  if (k1 != s->k0)
  {
    s->k0 = k1;
    continue;
  }
  ;
  s->state_out_len = 3;
  if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
  {
    return (Bool) 1;
  }
  k1 = BZ2_indexIntoF(s->tPos, s->cftab);
  s->tPos = ((UInt32) s->ll16[s->tPos]) | (((((UInt32) s->ll4[s->tPos >> 1]) >> ((s->tPos << 2) & 0x4)) & 0xF) << 16);
  ;
  if (s->rNToGo == 0)
  {
    s->rNToGo = BZ2_rNums[s->rTPos];
    s->rTPos += 1;
    if (s->rTPos == 512)
    {
      s->rTPos = 0;
    }
  }
  s->rNToGo -= 1;
  ;
  k1 ^= (s->rNToGo == 1) ? (1) : (0);
  s->nblock_used += 1;
  if (s->nblock_used == (s->save_nblock + 1))
  {
    continue;
  }
  if (k1 != s->k0)
  {
    s->k0 = k1;
    continue;
  }
  ;
  if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
  {
    return (Bool) 1;
  }
  k1 = BZ2_indexIntoF(s->tPos, s->cftab);
  s->tPos = ((UInt32) s->ll16[s->tPos]) | (((((UInt32) s->ll4[s->tPos >> 1]) >> ((s->tPos << 2) & 0x4)) & 0xF) << 16);
  ;
  if (s->rNToGo == 0)
  {
    s->rNToGo = BZ2_rNums[s->rTPos];
    s->rTPos += 1;
    if (s->rTPos == 512)
    {
      s->rTPos = 0;
    }
  }
  s->rNToGo -= 1;
  ;
  k1 ^= (s->rNToGo == 1) ? (1) : (0);
  s->nblock_used += 1;
  s->state_out_len = ((Int32) k1) + 4;
  if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
  {
    return (Bool) 1;
  }
  s->k0 = BZ2_indexIntoF(s->tPos, s->cftab);
  s->tPos = ((UInt32) s->ll16[s->tPos]) | (((((UInt32) s->ll4[s->tPos >> 1]) >> ((s->tPos << 2) & 0x4)) & 0xF) << 16);
  ;
  if (s->rNToGo == 0)
  {
    s->rNToGo = BZ2_rNums[s->rTPos];
    s->rTPos += 1;
    if (s->rTPos == 512)
    {
      s->rTPos = 0;
    }
  }
  s->rNToGo -= 1;
  ;
  s->k0 ^= (s->rNToGo == 1) ? (1) : (0);
  s->nblock_used += 1;
  *k1_ref = k1;
}


/*** DEPENDENCIES:
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
} DState
----------------------------
typedef char Char
----------------------------
typedef unsigned char UChar
----------------------------
extern Int32 BZ2_rNums[512]
----------------------------
extern UInt32 BZ2_crc32Table[256]
----------------------------
Int32 BZ2_indexIntoF(Int32 indx, Int32 *cftab)
{
  Int32 nb;
  Int32 na;
  Int32 mid;
  nb = 0;
  na = 256;
  do
  {
    mid = (nb + na) >> 1;
    if (indx >= cftab[mid])
    {
      nb = mid;
    }
    else
      na = mid;
  }
  while ((na - nb) != 1);
  return nb;
}


----------------------------
***/


// hint:  ['k1_ref is a mutable refrence to UChar']
Bool helper_unRLE_obuf_to_output_SMALL_2(UChar * const k1_ref, DState * const s)
{
  UChar k1 = *k1_ref;
  while ((Bool) 1)
  {
    helper_helper_unRLE_obuf_to_output_SMALL_2_1(&k1, s);
  }

  *k1_ref = k1;
}


/*** DEPENDENCIES:
typedef unsigned char UChar
----------------------------
Bool helper_helper_unRLE_obuf_to_output_SMALL_2_1(UChar * const k1_ref, DState * const s)
{
  UChar k1 = *k1_ref;
  while ((Bool) 1)
  {
    if (s->strm->avail_out == 0)
    {
      return (Bool) 0;
    }
    if (s->state_out_len == 0)
    {
      break;
    }
    *((UChar *) s->strm->next_out) = s->state_out_ch;
    {
      s->calculatedBlockCRC = (s->calculatedBlockCRC << 8) ^ BZ2_crc32Table[(s->calculatedBlockCRC >> 24) ^ ((UChar) s->state_out_ch)];
    }
    ;
    s->state_out_len -= 1;
    s->strm->next_out += 1;
    s->strm->avail_out -= 1;
    s->strm->total_out_lo32 += 1;
    if (s->strm->total_out_lo32 == 0)
    {
      s->strm->total_out_hi32 += 1;
    }
  }

  if (s->nblock_used == (s->save_nblock + 1))
  {
    return (Bool) 0;
  }
  if (s->nblock_used > (s->save_nblock + 1))
  {
    return (Bool) 1;
  }
  s->state_out_len = 1;
  s->state_out_ch = s->k0;
  if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
  {
    return (Bool) 1;
  }
  k1 = BZ2_indexIntoF(s->tPos, s->cftab);
  s->tPos = ((UInt32) s->ll16[s->tPos]) | (((((UInt32) s->ll4[s->tPos >> 1]) >> ((s->tPos << 2) & 0x4)) & 0xF) << 16);
  ;
  if (s->rNToGo == 0)
  {
    s->rNToGo = BZ2_rNums[s->rTPos];
    s->rTPos += 1;
    if (s->rTPos == 512)
    {
      s->rTPos = 0;
    }
  }
  s->rNToGo -= 1;
  ;
  k1 ^= (s->rNToGo == 1) ? (1) : (0);
  s->nblock_used += 1;
  if (s->nblock_used == (s->save_nblock + 1))
  {
    continue;
  }
  if (k1 != s->k0)
  {
    s->k0 = k1;
    continue;
  }
  ;
  s->state_out_len = 2;
  if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
  {
    return (Bool) 1;
  }
  k1 = BZ2_indexIntoF(s->tPos, s->cftab);
  s->tPos = ((UInt32) s->ll16[s->tPos]) | (((((UInt32) s->ll4[s->tPos >> 1]) >> ((s->tPos << 2) & 0x4)) & 0xF) << 16);
  ;
  if (s->rNToGo == 0)
  {
    s->rNToGo = BZ2_rNums[s->rTPos];
    s->rTPos += 1;
    if (s->rTPos == 512)
    {
      s->rTPos = 0;
    }
  }
  s->rNToGo -= 1;
  ;
  k1 ^= (s->rNToGo == 1) ? (1) : (0);
  s->nblock_used += 1;
  if (s->nblock_used == (s->save_nblock + 1))
  {
    continue;
  }
  if (k1 != s->k0)
  {
    s->k0 = k1;
    continue;
  }
  ;
  s->state_out_len = 3;
  if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
  {
    return (Bool) 1;
  }
  k1 = BZ2_indexIntoF(s->tPos, s->cftab);
  s->tPos = ((UInt32) s->ll16[s->tPos]) | (((((UInt32) s->ll4[s->tPos >> 1]) >> ((s->tPos << 2) & 0x4)) & 0xF) << 16);
  ;
  if (s->rNToGo == 0)
  {
    s->rNToGo = BZ2_rNums[s->rTPos];
    s->rTPos += 1;
    if (s->rTPos == 512)
    {
      s->rTPos = 0;
    }
  }
  s->rNToGo -= 1;
  ;
  k1 ^= (s->rNToGo == 1) ? (1) : (0);
  s->nblock_used += 1;
  if (s->nblock_used == (s->save_nblock + 1))
  {
    continue;
  }
  if (k1 != s->k0)
  {
    s->k0 = k1;
    continue;
  }
  ;
  if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
  {
    return (Bool) 1;
  }
  k1 = BZ2_indexIntoF(s->tPos, s->cftab);
  s->tPos = ((UInt32) s->ll16[s->tPos]) | (((((UInt32) s->ll4[s->tPos >> 1]) >> ((s->tPos << 2) & 0x4)) & 0xF) << 16);
  ;
  if (s->rNToGo == 0)
  {
    s->rNToGo = BZ2_rNums[s->rTPos];
    s->rTPos += 1;
    if (s->rTPos == 512)
    {
      s->rTPos = 0;
    }
  }
  s->rNToGo -= 1;
  ;
  k1 ^= (s->rNToGo == 1) ? (1) : (0);
  s->nblock_used += 1;
  s->state_out_len = ((Int32) k1) + 4;
  if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
  {
    return (Bool) 1;
  }
  s->k0 = BZ2_indexIntoF(s->tPos, s->cftab);
  s->tPos = ((UInt32) s->ll16[s->tPos]) | (((((UInt32) s->ll4[s->tPos >> 1]) >> ((s->tPos << 2) & 0x4)) & 0xF) << 16);
  ;
  if (s->rNToGo == 0)
  {
    s->rNToGo = BZ2_rNums[s->rTPos];
    s->rTPos += 1;
    if (s->rTPos == 512)
    {
      s->rTPos = 0;
    }
  }
  s->rNToGo -= 1;
  ;
  s->k0 ^= (s->rNToGo == 1) ? (1) : (0);
  s->nblock_used += 1;
  *k1_ref = k1;
}


----------------------------
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
} DState
----------------------------
typedef char Char
----------------------------
***/


// hint:  ['k1_ref is a mutable refrence to UChar']
Bool helper_helper_unRLE_obuf_to_output_SMALL_1_1(UChar * const k1_ref, DState * const s)
{
  UChar k1 = *k1_ref;
  while ((Bool) 1)
  {
    if (s->strm->avail_out == 0)
    {
      return (Bool) 0;
    }
    if (s->state_out_len == 0)
    {
      break;
    }
    *((UChar *) s->strm->next_out) = s->state_out_ch;
    {
      s->calculatedBlockCRC = (s->calculatedBlockCRC << 8) ^ BZ2_crc32Table[(s->calculatedBlockCRC >> 24) ^ ((UChar) s->state_out_ch)];
    }
    ;
    s->state_out_len -= 1;
    s->strm->next_out += 1;
    s->strm->avail_out -= 1;
    s->strm->total_out_lo32 += 1;
    if (s->strm->total_out_lo32 == 0)
    {
      s->strm->total_out_hi32 += 1;
    }
  }

  if (s->nblock_used == (s->save_nblock + 1))
  {
    return (Bool) 0;
  }
  if (s->nblock_used > (s->save_nblock + 1))
  {
    return (Bool) 1;
  }
  s->state_out_len = 1;
  s->state_out_ch = s->k0;
  if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
  {
    return (Bool) 1;
  }
  k1 = BZ2_indexIntoF(s->tPos, s->cftab);
  s->tPos = ((UInt32) s->ll16[s->tPos]) | (((((UInt32) s->ll4[s->tPos >> 1]) >> ((s->tPos << 2) & 0x4)) & 0xF) << 16);
  ;
  s->nblock_used += 1;
  if (s->nblock_used == (s->save_nblock + 1))
  {
    continue;
  }
  if (k1 != s->k0)
  {
    s->k0 = k1;
    continue;
  }
  ;
  s->state_out_len = 2;
  if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
  {
    return (Bool) 1;
  }
  k1 = BZ2_indexIntoF(s->tPos, s->cftab);
  s->tPos = ((UInt32) s->ll16[s->tPos]) | (((((UInt32) s->ll4[s->tPos >> 1]) >> ((s->tPos << 2) & 0x4)) & 0xF) << 16);
  ;
  s->nblock_used += 1;
  if (s->nblock_used == (s->save_nblock + 1))
  {
    continue;
  }
  if (k1 != s->k0)
  {
    s->k0 = k1;
    continue;
  }
  ;
  s->state_out_len = 3;
  if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
  {
    return (Bool) 1;
  }
  k1 = BZ2_indexIntoF(s->tPos, s->cftab);
  s->tPos = ((UInt32) s->ll16[s->tPos]) | (((((UInt32) s->ll4[s->tPos >> 1]) >> ((s->tPos << 2) & 0x4)) & 0xF) << 16);
  ;
  s->nblock_used += 1;
  if (s->nblock_used == (s->save_nblock + 1))
  {
    continue;
  }
  if (k1 != s->k0)
  {
    s->k0 = k1;
    continue;
  }
  ;
  if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
  {
    return (Bool) 1;
  }
  k1 = BZ2_indexIntoF(s->tPos, s->cftab);
  s->tPos = ((UInt32) s->ll16[s->tPos]) | (((((UInt32) s->ll4[s->tPos >> 1]) >> ((s->tPos << 2) & 0x4)) & 0xF) << 16);
  ;
  s->nblock_used += 1;
  s->state_out_len = ((Int32) k1) + 4;
  if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
  {
    return (Bool) 1;
  }
  s->k0 = BZ2_indexIntoF(s->tPos, s->cftab);
  s->tPos = ((UInt32) s->ll16[s->tPos]) | (((((UInt32) s->ll4[s->tPos >> 1]) >> ((s->tPos << 2) & 0x4)) & 0xF) << 16);
  ;
  s->nblock_used += 1;
  *k1_ref = k1;
}


/*** DEPENDENCIES:
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
} DState
----------------------------
typedef char Char
----------------------------
typedef unsigned char UChar
----------------------------
extern UInt32 BZ2_crc32Table[256]
----------------------------
Int32 BZ2_indexIntoF(Int32 indx, Int32 *cftab)
{
  Int32 nb;
  Int32 na;
  Int32 mid;
  nb = 0;
  na = 256;
  do
  {
    mid = (nb + na) >> 1;
    if (indx >= cftab[mid])
    {
      nb = mid;
    }
    else
      na = mid;
  }
  while ((na - nb) != 1);
  return nb;
}


----------------------------
***/


// hint:  ['k1_ref is a mutable refrence to UChar']
Bool helper_unRLE_obuf_to_output_SMALL_1(UChar * const k1_ref, DState * const s)
{
  UChar k1 = *k1_ref;
  while ((Bool) 1)
  {
    helper_helper_unRLE_obuf_to_output_SMALL_1_1(&k1, s);
  }

  *k1_ref = k1;
}


/*** DEPENDENCIES:
typedef unsigned char UChar
----------------------------
Bool helper_helper_unRLE_obuf_to_output_SMALL_1_1(UChar * const k1_ref, DState * const s)
{
  UChar k1 = *k1_ref;
  while ((Bool) 1)
  {
    if (s->strm->avail_out == 0)
    {
      return (Bool) 0;
    }
    if (s->state_out_len == 0)
    {
      break;
    }
    *((UChar *) s->strm->next_out) = s->state_out_ch;
    {
      s->calculatedBlockCRC = (s->calculatedBlockCRC << 8) ^ BZ2_crc32Table[(s->calculatedBlockCRC >> 24) ^ ((UChar) s->state_out_ch)];
    }
    ;
    s->state_out_len -= 1;
    s->strm->next_out += 1;
    s->strm->avail_out -= 1;
    s->strm->total_out_lo32 += 1;
    if (s->strm->total_out_lo32 == 0)
    {
      s->strm->total_out_hi32 += 1;
    }
  }

  if (s->nblock_used == (s->save_nblock + 1))
  {
    return (Bool) 0;
  }
  if (s->nblock_used > (s->save_nblock + 1))
  {
    return (Bool) 1;
  }
  s->state_out_len = 1;
  s->state_out_ch = s->k0;
  if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
  {
    return (Bool) 1;
  }
  k1 = BZ2_indexIntoF(s->tPos, s->cftab);
  s->tPos = ((UInt32) s->ll16[s->tPos]) | (((((UInt32) s->ll4[s->tPos >> 1]) >> ((s->tPos << 2) & 0x4)) & 0xF) << 16);
  ;
  s->nblock_used += 1;
  if (s->nblock_used == (s->save_nblock + 1))
  {
    continue;
  }
  if (k1 != s->k0)
  {
    s->k0 = k1;
    continue;
  }
  ;
  s->state_out_len = 2;
  if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
  {
    return (Bool) 1;
  }
  k1 = BZ2_indexIntoF(s->tPos, s->cftab);
  s->tPos = ((UInt32) s->ll16[s->tPos]) | (((((UInt32) s->ll4[s->tPos >> 1]) >> ((s->tPos << 2) & 0x4)) & 0xF) << 16);
  ;
  s->nblock_used += 1;
  if (s->nblock_used == (s->save_nblock + 1))
  {
    continue;
  }
  if (k1 != s->k0)
  {
    s->k0 = k1;
    continue;
  }
  ;
  s->state_out_len = 3;
  if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
  {
    return (Bool) 1;
  }
  k1 = BZ2_indexIntoF(s->tPos, s->cftab);
  s->tPos = ((UInt32) s->ll16[s->tPos]) | (((((UInt32) s->ll4[s->tPos >> 1]) >> ((s->tPos << 2) & 0x4)) & 0xF) << 16);
  ;
  s->nblock_used += 1;
  if (s->nblock_used == (s->save_nblock + 1))
  {
    continue;
  }
  if (k1 != s->k0)
  {
    s->k0 = k1;
    continue;
  }
  ;
  if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
  {
    return (Bool) 1;
  }
  k1 = BZ2_indexIntoF(s->tPos, s->cftab);
  s->tPos = ((UInt32) s->ll16[s->tPos]) | (((((UInt32) s->ll4[s->tPos >> 1]) >> ((s->tPos << 2) & 0x4)) & 0xF) << 16);
  ;
  s->nblock_used += 1;
  s->state_out_len = ((Int32) k1) + 4;
  if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
  {
    return (Bool) 1;
  }
  s->k0 = BZ2_indexIntoF(s->tPos, s->cftab);
  s->tPos = ((UInt32) s->ll16[s->tPos]) | (((((UInt32) s->ll4[s->tPos >> 1]) >> ((s->tPos << 2) & 0x4)) & 0xF) << 16);
  ;
  s->nblock_used += 1;
  *k1_ref = k1;
}


----------------------------
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
} DState
----------------------------
typedef char Char
----------------------------
***/


static Bool unRLE_obuf_to_output_SMALL(DState *s)
{
  UChar k1;
  if (s->blockRandomised)
  {
    helper_unRLE_obuf_to_output_SMALL_2(&k1, s);
  }
  else
  {
    helper_unRLE_obuf_to_output_SMALL_1(&k1, s);
  }
}


/*** DEPENDENCIES:
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
} DState
----------------------------
typedef char Char
----------------------------
Bool helper_unRLE_obuf_to_output_SMALL_2(UChar * const k1_ref, DState * const s)
{
  UChar k1 = *k1_ref;
  while ((Bool) 1)
  {
    helper_helper_unRLE_obuf_to_output_SMALL_2_1(&k1, s);
  }

  *k1_ref = k1;
}


----------------------------
typedef unsigned char UChar
----------------------------
Bool helper_unRLE_obuf_to_output_SMALL_1(UChar * const k1_ref, DState * const s)
{
  UChar k1 = *k1_ref;
  while ((Bool) 1)
  {
    helper_helper_unRLE_obuf_to_output_SMALL_1_1(&k1, s);
  }

  *k1_ref = k1;
}


----------------------------
***/


// hint:  ['corrupt_ref is a mutable refrence to Bool']
int helper_BZ2_bzDecompress_1(Bool * const corrupt_ref, DState * const s)
{
  Bool corrupt = *corrupt_ref;
  if (s->state == 1)
  {
    return -1;
  }
  if (s->state == 2)
  {
    if (s->smallDecompress)
    {
      corrupt = unRLE_obuf_to_output_SMALL(s);
    }
    else
      corrupt = unRLE_obuf_to_output_FAST(s);
    if (corrupt)
    {
      return -4;
    }
    if ((s->nblock_used == (s->save_nblock + 1)) && (s->state_out_len == 0))
    {
      {
        s->calculatedBlockCRC = ~s->calculatedBlockCRC;
      }
      ;
      if (s->verbosity >= 3)
      {
        fprintf(stderr, " {0x%08x, 0x%08x}", s->storedBlockCRC, s->calculatedBlockCRC);
      }
      if (s->verbosity >= 2)
      {
        fprintf(stderr, "]");
      }
      if (s->calculatedBlockCRC != s->storedBlockCRC)
      {
        return -4;
      }
      s->calculatedCombinedCRC = (s->calculatedCombinedCRC << 1) | (s->calculatedCombinedCRC >> 31);
      s->calculatedCombinedCRC ^= s->calculatedBlockCRC;
      s->state = 14;
    }
    else
    {
      return 0;
    }
  }
  if (s->state >= 10)
  {
    Int32 r = BZ2_decompress(s);
    if (r == 4)
    {
      if (s->verbosity >= 3)
      {
        fprintf(stderr, "\n    combined CRCs: stored = 0x%08x, computed = 0x%08x", s->storedCombinedCRC, s->calculatedCombinedCRC);
      }
      if (s->calculatedCombinedCRC != s->storedCombinedCRC)
      {
        return -4;
      }
      return r;
    }
    if (s->state != 2)
    {
      return r;
    }
  }
  *corrupt_ref = corrupt;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
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
} DState
----------------------------
static Bool unRLE_obuf_to_output_FAST(DState *s)
{
  UChar k1;
  if (s->blockRandomised)
  {
    helper_unRLE_obuf_to_output_FAST_2(&k1, s);
  }
  else
  {
    helper_unRLE_obuf_to_output_FAST_1(&k1, s);
  }
  return (Bool) 0;
}


----------------------------
Int32 BZ2_decompress(DState *s)
{
  UChar uc;
  Int32 retVal;
  Int32 minLen;
  Int32 maxLen;
  bz_stream *strm = s->strm;
  Int32 i;
  Int32 j;
  Int32 t;
  Int32 alphaSize;
  Int32 nGroups;
  Int32 nSelectors;
  Int32 EOB;
  Int32 groupNo;
  Int32 groupPos;
  Int32 nextSym;
  Int32 nblockMAX;
  Int32 nblock;
  Int32 es;
  Int32 N;
  Int32 curr;
  Int32 zt;
  Int32 zn;
  Int32 zvec;
  Int32 zj;
  Int32 gSel;
  Int32 gMinlen;
  Int32 *gLimit;
  unsigned int gLimit_idx = 0;
  Int32 *gBase;
  unsigned int gBase_idx = 0;
  Int32 *gPerm;
  unsigned int gPerm_idx = 0;
  if (s->state == 10)
  {
    helper_BZ2_decompress_11(s);
  }
  i = s->save_i;
  j = s->save_j;
  t = s->save_t;
  alphaSize = s->save_alphaSize;
  nGroups = s->save_nGroups;
  nSelectors = s->save_nSelectors;
  EOB = s->save_EOB;
  groupNo = s->save_groupNo;
  groupPos = s->save_groupPos;
  nextSym = s->save_nextSym;
  nblockMAX = s->save_nblockMAX;
  nblock = s->save_nblock;
  es = s->save_es;
  N = s->save_N;
  curr = s->save_curr;
  zt = s->save_zt;
  zn = s->save_zn;
  zvec = s->save_zvec;
  zj = s->save_zj;
  gSel = s->save_gSel;
  gMinlen = s->save_gMinlen;
  gLimit_idx = s->save_gLimit;
  gBase_idx = s->save_gBase;
  gPerm_idx = s->save_gPerm;
  retVal = 0;
  switch (s->state)
  {
    case 10:
    {
      helper_BZ2_decompress_13(&uc, &retVal, s);
    }

    case 11:
    {
      helper_BZ2_decompress_14(&uc, &retVal, s);
    }

    case 12:
    {
      helper_BZ2_decompress_12(&uc, &retVal, s);
    }

    case 13:
    {
      helper_BZ2_decompress_27(&retVal, s, strm);
    }

    case 14:
    {
      helper_BZ2_decompress_24(&uc, &retVal, s);
    }

    case 15:
    {
      helper_BZ2_decompress_15(&uc, &retVal, s);
    }

    case 16:
    {
      helper_BZ2_decompress_16(&uc, &retVal, s);
    }

    case 17:
    {
      helper_BZ2_decompress_17(&uc, &retVal, s);
    }

    case 18:
    {
      helper_BZ2_decompress_18(&uc, &retVal, s);
    }

    case 19:
    {
      helper_BZ2_decompress_26(&uc, &retVal, s);
    }

    case 20:
    {
      helper_BZ2_decompress_1(&uc, &retVal, s);
    }

    case 21:
    {
      helper_BZ2_decompress_2(&uc, &retVal, s);
    }

    case 22:
    {
      helper_BZ2_decompress_3(&uc, &retVal, s);
    }

    case 23:
    {
      helper_BZ2_decompress_4(&uc, &retVal, s);
    }

    case 24:
    {
      helper_BZ2_decompress_5(&retVal, s);
    }

    case 25:
    {
      helper_BZ2_decompress_6(&uc, &retVal, s);
    }

    case 26:
    {
      helper_BZ2_decompress_7(&uc, &retVal, s);
    }

    case 27:
    {
      helper_BZ2_decompress_28(&uc, &retVal, &i, &j, &alphaSize, s);
    }

    case 30:
    {
      helper_BZ2_decompress_19(&retVal, &nGroups, s);
    }

    case 31:
    {
      helper_BZ2_decompress_29(&uc, &retVal, &minLen, &maxLen, &i, &j, &t, &nSelectors, &EOB, &groupNo, &groupPos, &nextSym, &nblockMAX, &nblock, &es, &N, &curr, &zn, &zvec, &zj, &gSel, &gMinlen, &gLimit_idx, &gBase_idx, &gPerm_idx, s, alphaSize, nGroups, gLimit, gBase, gPerm);
    }

    case 43:
    {
      helper_BZ2_decompress_20(&uc, &retVal, s);
    }

    case 44:
    {
      helper_BZ2_decompress_21(&uc, &retVal, s);
    }

    case 45:
    {
      helper_BZ2_decompress_22(&uc, &retVal, s);
    }

    case 46:
    {
      helper_BZ2_decompress_23(&uc, &retVal, s);
    }

    case 47:
    {
      helper_BZ2_decompress_8(&uc, &retVal, s);
    }

    case 48:
    {
      helper_BZ2_decompress_9(&uc, &retVal, s);
    }

    case 49:
    {
      helper_BZ2_decompress_10(&uc, &retVal, s);
    }

    case 50:
    {
      helper_BZ2_decompress_25(&uc, &retVal, s);
    }

    default:
    {
      {
        if (!((Bool) 0))
        {
          BZ2_bz__AssertH__fail(4001);
        }
      }
      ;
    }

  }

  {
    if (!((Bool) 0))
    {
      BZ2_bz__AssertH__fail(4002);
    }
  }
  ;
  save_state_and_return:
  s->save_i = i;

  s->save_j = j;
  s->save_t = t;
  s->save_alphaSize = alphaSize;
  s->save_nGroups = nGroups;
  s->save_nSelectors = nSelectors;
  s->save_EOB = EOB;
  s->save_groupNo = groupNo;
  s->save_groupPos = groupPos;
  s->save_nextSym = nextSym;
  s->save_nblockMAX = nblockMAX;
  s->save_nblock = nblock;
  s->save_es = es;
  s->save_N = N;
  s->save_curr = curr;
  s->save_zt = zt;
  s->save_zn = zn;
  s->save_zvec = zvec;
  s->save_zj = zj;
  s->save_gSel = gSel;
  s->save_gMinlen = gMinlen;
  s->save_gLimit = &gLimit[gLimit_idx];
  s->save_gBase = &gBase[gBase_idx];
  s->save_gPerm = &gPerm[gPerm_idx];
  return retVal;
}


----------------------------
static Bool unRLE_obuf_to_output_SMALL(DState *s)
{
  UChar k1;
  if (s->blockRandomised)
  {
    helper_unRLE_obuf_to_output_SMALL_2(&k1, s);
  }
  else
  {
    helper_unRLE_obuf_to_output_SMALL_1(&k1, s);
  }
}


----------------------------
typedef unsigned char Bool
----------------------------
***/


int BZ2_bzDecompress(bz_stream *strm)
{
  Bool corrupt;
  DState *s;
  unsigned int s_idx = 0;
  if (strm == 0)
  {
    return -2;
  }
  s_idx = strm->state;
  if ((&s[s_idx]) == 0)
  {
    return -2;
  }
  if (s->strm != strm)
  {
    return -2;
  }
  while ((Bool) 1)
  {
    helper_BZ2_bzDecompress_1(&corrupt, s);
  }

  {
    if (!0)
    {
      BZ2_bz__AssertH__fail(6001);
    }
  }
  ;
  return 0;
}


/*** DEPENDENCIES:
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
} bz_stream
----------------------------
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
} DState
----------------------------
int helper_BZ2_bzDecompress_1(Bool * const corrupt_ref, DState * const s)
{
  Bool corrupt = *corrupt_ref;
  if (s->state == 1)
  {
    return -1;
  }
  if (s->state == 2)
  {
    if (s->smallDecompress)
    {
      corrupt = unRLE_obuf_to_output_SMALL(s);
    }
    else
      corrupt = unRLE_obuf_to_output_FAST(s);
    if (corrupt)
    {
      return -4;
    }
    if ((s->nblock_used == (s->save_nblock + 1)) && (s->state_out_len == 0))
    {
      {
        s->calculatedBlockCRC = ~s->calculatedBlockCRC;
      }
      ;
      if (s->verbosity >= 3)
      {
        fprintf(stderr, " {0x%08x, 0x%08x}", s->storedBlockCRC, s->calculatedBlockCRC);
      }
      if (s->verbosity >= 2)
      {
        fprintf(stderr, "]");
      }
      if (s->calculatedBlockCRC != s->storedBlockCRC)
      {
        return -4;
      }
      s->calculatedCombinedCRC = (s->calculatedCombinedCRC << 1) | (s->calculatedCombinedCRC >> 31);
      s->calculatedCombinedCRC ^= s->calculatedBlockCRC;
      s->state = 14;
    }
    else
    {
      return 0;
    }
  }
  if (s->state >= 10)
  {
    Int32 r = BZ2_decompress(s);
    if (r == 4)
    {
      if (s->verbosity >= 3)
      {
        fprintf(stderr, "\n    combined CRCs: stored = 0x%08x, computed = 0x%08x", s->storedCombinedCRC, s->calculatedCombinedCRC);
      }
      if (s->calculatedCombinedCRC != s->storedCombinedCRC)
      {
        return -4;
      }
      return r;
    }
    if (s->state != 2)
    {
      return r;
    }
  }
  *corrupt_ref = corrupt;
}


----------------------------
void BZ2_bz__AssertH__fail(int errcode)
{
  fprintf(stderr, "\n\nbzip2/libbzip2: internal error number %d.\nThis is a bug in bzip2/libbzip2, %s.\nPlease report it at: https://gitlab.com/bzip2/bzip2/-/issues\nIf this happened when you were using some program which uses\nlibbzip2 as a component, you should also report this bug to\nthe author(s) of that program.\nPlease make an effort to report this bug;\ntimely and accurate bug reports eventually lead to higher\nquality software.  Thanks.\n\n", errcode, BZ2_bzlibVersion());
  if (errcode == 1007)
  {
    fprintf(stderr, "\n*** A special note about internal error number 1007 ***\n\nExperience suggests that a common cause of i.e. 1007\nis unreliable memory or other hardware.  The 1007 assertion\njust happens to cross-check the results of huge numbers of\nmemory reads/writes, and so acts (unintendedly) as a stress\ntest of your memory system.\n\nI suggest the following: try compressing the file again,\npossibly monitoring progress in detail with the -vv flag.\n\n* If the error cannot be reproduced, and/or happens at different\n  points in compression, you may have a flaky memory system.\n  Try a memory-test program.  I have used Memtest86\n  (www.memtest86.com).  At the time of writing it is free (GPLd).\n  Memtest86 tests memory much more thorougly than your BIOSs\n  power-on test, and may find failures that the BIOS doesn't.\n\n* If the error can be repeatably reproduced, this is a bug in\n  bzip2, and I would very much like to hear about it.  Please\n  let me know, and, ideally, save a copy of the file causing the\n  problem -- without which I will be unable to investigate it.\n\n");
  }
  exit(3);
}


----------------------------
typedef unsigned char Bool
----------------------------
***/


// hint:  ['n_ref is a mutable refrence to Int32', 'ret_ref is a mutable refrence to Int32']
int helper_BZ2_bzRead_1(Int32 * const n_ref, Int32 * const ret_ref, int * const bzerror, int len, bzFile * const bzf)
{
  Int32 n = *n_ref;
  Int32 ret = *ret_ref;
  if (ferror(bzf->handle))
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -6;
      }
      if (bzf != 0)
      {
        bzf->lastErr = -6;
      }
    }
    ;
    return 0;
  }
  ;
  if ((bzf->strm.avail_in == 0) && (!myfeof(bzf->handle)))
  {
    n = fread(bzf->buf, sizeof(UChar), 5000, bzf->handle);
    if (ferror(bzf->handle))
    {
      {
        if (bzerror != 0)
        {
          *bzerror = -6;
        }
        if (bzf != 0)
        {
          bzf->lastErr = -6;
        }
      }
      ;
      return 0;
    }
    ;
    bzf->bufN = n;
    bzf->strm.avail_in = bzf->bufN;
    bzf->strm.next_in = bzf->buf;
  }
  ret = BZ2_bzDecompress(&bzf->strm);
  if ((ret != 0) && (ret != 4))
  {
    {
      if (bzerror != 0)
      {
        *bzerror = ret;
      }
      if (bzf != 0)
      {
        bzf->lastErr = ret;
      }
    }
    ;
    return 0;
  }
  ;
  if ((((ret == 0) && myfeof(bzf->handle)) && (bzf->strm.avail_in == 0)) && (bzf->strm.avail_out > 0))
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -7;
      }
      if (bzf != 0)
      {
        bzf->lastErr = -7;
      }
    }
    ;
    return 0;
  }
  ;
  if (ret == 4)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = 4;
      }
      if (bzf != 0)
      {
        bzf->lastErr = 4;
      }
    }
    ;
    return len - bzf->strm.avail_out;
  }
  ;
  if (bzf->strm.avail_out == 0)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = 0;
      }
      if (bzf != 0)
      {
        bzf->lastErr = 0;
      }
    }
    ;
    return len;
  }
  ;
  *n_ref = n;
  *ret_ref = ret;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
typedef struct 
{
  FILE *handle;
  Char buf[5000];
  Int32 bufN;
  Bool writing;
  bz_stream strm;
  Int32 lastErr;
  Bool initialisedOk;
} bzFile
----------------------------
static Bool myfeof(FILE *f)
{
  Int32 c = fgetc(f);
  if (c == EOF)
  {
    return (Bool) 1;
  }
  ungetc(c, f);
  return (Bool) 0;
}


----------------------------
int BZ2_bzDecompress(bz_stream *strm)
{
  Bool corrupt;
  DState *s;
  unsigned int s_idx = 0;
  if (strm == 0)
  {
    return -2;
  }
  s_idx = strm->state;
  if ((&s[s_idx]) == 0)
  {
    return -2;
  }
  if (s->strm != strm)
  {
    return -2;
  }
  while ((Bool) 1)
  {
    helper_BZ2_bzDecompress_1(&corrupt, s);
  }

  {
    if (!0)
    {
      BZ2_bz__AssertH__fail(6001);
    }
  }
  ;
  return 0;
}


----------------------------
***/


int BZ2_bzRead(int *bzerror, BZFILE *b, void *buf, int len)
{
  Int32 n;
  Int32 ret;
  bzFile *bzf = (bzFile *) b;
  {
    if (bzerror != 0)
    {
      *bzerror = 0;
    }
    if (bzf != 0)
    {
      bzf->lastErr = 0;
    }
  }
  ;
  if (((bzf == 0) || (buf == 0)) || (len < 0))
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -2;
      }
      if (bzf != 0)
      {
        bzf->lastErr = -2;
      }
    }
    ;
    return 0;
  }
  ;
  if (bzf->writing)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -1;
      }
      if (bzf != 0)
      {
        bzf->lastErr = -1;
      }
    }
    ;
    return 0;
  }
  ;
  if (len == 0)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = 0;
      }
      if (bzf != 0)
      {
        bzf->lastErr = 0;
      }
    }
    ;
    return 0;
  }
  ;
  bzf->strm.avail_out = len;
  bzf->strm.next_out = buf;
  while ((Bool) 1)
  {
    helper_BZ2_bzRead_1(&n, &ret, bzerror, len, bzf);
  }

  return 0;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
int helper_BZ2_bzRead_1(Int32 * const n_ref, Int32 * const ret_ref, int * const bzerror, int len, bzFile * const bzf)
{
  Int32 n = *n_ref;
  Int32 ret = *ret_ref;
  if (ferror(bzf->handle))
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -6;
      }
      if (bzf != 0)
      {
        bzf->lastErr = -6;
      }
    }
    ;
    return 0;
  }
  ;
  if ((bzf->strm.avail_in == 0) && (!myfeof(bzf->handle)))
  {
    n = fread(bzf->buf, sizeof(UChar), 5000, bzf->handle);
    if (ferror(bzf->handle))
    {
      {
        if (bzerror != 0)
        {
          *bzerror = -6;
        }
        if (bzf != 0)
        {
          bzf->lastErr = -6;
        }
      }
      ;
      return 0;
    }
    ;
    bzf->bufN = n;
    bzf->strm.avail_in = bzf->bufN;
    bzf->strm.next_in = bzf->buf;
  }
  ret = BZ2_bzDecompress(&bzf->strm);
  if ((ret != 0) && (ret != 4))
  {
    {
      if (bzerror != 0)
      {
        *bzerror = ret;
      }
      if (bzf != 0)
      {
        bzf->lastErr = ret;
      }
    }
    ;
    return 0;
  }
  ;
  if ((((ret == 0) && myfeof(bzf->handle)) && (bzf->strm.avail_in == 0)) && (bzf->strm.avail_out > 0))
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -7;
      }
      if (bzf != 0)
      {
        bzf->lastErr = -7;
      }
    }
    ;
    return 0;
  }
  ;
  if (ret == 4)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = 4;
      }
      if (bzf != 0)
      {
        bzf->lastErr = 4;
      }
    }
    ;
    return len - bzf->strm.avail_out;
  }
  ;
  if (bzf->strm.avail_out == 0)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = 0;
      }
      if (bzf != 0)
      {
        bzf->lastErr = 0;
      }
    }
    ;
    return len;
  }
  ;
  *n_ref = n;
  *ret_ref = ret;
}


----------------------------
typedef void BZFILE
----------------------------
typedef struct 
{
  FILE *handle;
  Char buf[5000];
  Int32 bufN;
  Bool writing;
  bz_stream strm;
  Int32 lastErr;
  Bool initialisedOk;
} bzFile
----------------------------
***/


int BZ2_bzread(BZFILE *b, void *buf, int len)
{
  int bzerr;
  int nread;
  if (((bzFile *) b)->lastErr == 4)
  {
    return 0;
  }
  nread = BZ2_bzRead(&bzerr, b, buf, len);
  if ((bzerr == 0) || (bzerr == 4))
  {
    return nread;
  }
  else
  {
    return -1;
  }
}


/*** DEPENDENCIES:
int BZ2_bzRead(int *bzerror, BZFILE *b, void *buf, int len)
{
  Int32 n;
  Int32 ret;
  bzFile *bzf = (bzFile *) b;
  {
    if (bzerror != 0)
    {
      *bzerror = 0;
    }
    if (bzf != 0)
    {
      bzf->lastErr = 0;
    }
  }
  ;
  if (((bzf == 0) || (buf == 0)) || (len < 0))
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -2;
      }
      if (bzf != 0)
      {
        bzf->lastErr = -2;
      }
    }
    ;
    return 0;
  }
  ;
  if (bzf->writing)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -1;
      }
      if (bzf != 0)
      {
        bzf->lastErr = -1;
      }
    }
    ;
    return 0;
  }
  ;
  if (len == 0)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = 0;
      }
      if (bzf != 0)
      {
        bzf->lastErr = 0;
      }
    }
    ;
    return 0;
  }
  ;
  bzf->strm.avail_out = len;
  bzf->strm.next_out = buf;
  while ((Bool) 1)
  {
    helper_BZ2_bzRead_1(&n, &ret, bzerror, len, bzf);
  }

  return 0;
}


----------------------------
typedef void BZFILE
----------------------------
***/


// hint:  ['n_ref is a mutable refrence to Int32', 'n2_ref is a mutable refrence to Int32', 'ret_ref is a mutable refrence to Int32']
void helper_BZ2_bzWrite_1(Int32 * const n_ref, Int32 * const n2_ref, Int32 * const ret_ref, int * const bzerror, bzFile * const bzf)
{
  Int32 n = *n_ref;
  Int32 n2 = *n2_ref;
  Int32 ret = *ret_ref;
  bzf->strm.avail_out = 5000;
  bzf->strm.next_out = bzf->buf;
  ret = BZ2_bzCompress(&bzf->strm, 0);
  if (ret != 1)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = ret;
      }
      if (bzf != 0)
      {
        bzf->lastErr = ret;
      }
    }
    ;
    return;
  }
  ;
  if (bzf->strm.avail_out < 5000)
  {
    n = 5000 - bzf->strm.avail_out;
    n2 = fwrite((void *) bzf->buf, sizeof(UChar), n, bzf->handle);
    if ((n != n2) || ferror(bzf->handle))
    {
      {
        if (bzerror != 0)
        {
          *bzerror = -6;
        }
        if (bzf != 0)
        {
          bzf->lastErr = -6;
        }
      }
      ;
      return;
    }
    ;
  }
  if (bzf->strm.avail_in == 0)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = 0;
      }
      if (bzf != 0)
      {
        bzf->lastErr = 0;
      }
    }
    ;
    return;
  }
  ;
  *n_ref = n;
  *n2_ref = n2;
  *ret_ref = ret;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
typedef struct 
{
  FILE *handle;
  Char buf[5000];
  Int32 bufN;
  Bool writing;
  bz_stream strm;
  Int32 lastErr;
  Bool initialisedOk;
} bzFile
----------------------------
int BZ2_bzCompress(bz_stream *strm, int action)
{
  Bool progress;
  EState *s;
  unsigned int s_idx = 0;
  if (strm == 0)
  {
    return -2;
  }
  s_idx = strm->state;
  if ((&s[s_idx]) == 0)
  {
    return -2;
  }
  if (s->strm != strm)
  {
    return -2;
  }
  preswitch:
  switch (s->mode)
  {
    case 1:
    {
      return -1;
    }

    case 2:
    {
      if (action == 0)
      {
        progress = handle_compress(strm);
        return (progress) ? (1) : (-2);
      }
      else
        if (action == 1)
      {
        s->avail_in_expect = strm->avail_in;
        s->mode = 3;
        goto preswitch;
      }
      else
        if (action == 2)
      {
        s->avail_in_expect = strm->avail_in;
        s->mode = 4;
        goto preswitch;
      }
      else
        return -2;
    }

    case 3:
    {
      if (action != 1)
      {
        return -1;
      }
      if (s->avail_in_expect != s->strm->avail_in)
      {
        return -1;
      }
      progress = handle_compress(strm);
      if (((s->avail_in_expect > 0) || (!isempty_RL(s))) || (s->state_out_pos < s->numZ))
      {
        return 2;
      }
      s->mode = 2;
      return 1;
    }

    case 4:
    {
      if (action != 2)
      {
        return -1;
      }
      if (s->avail_in_expect != s->strm->avail_in)
      {
        return -1;
      }
      progress = handle_compress(strm);
      if (!progress)
      {
        return -1;
      }
      if (((s->avail_in_expect > 0) || (!isempty_RL(s))) || (s->state_out_pos < s->numZ))
      {
        return 3;
      }
      s->mode = 1;
      return 4;
    }

  }


  return 0;
}


----------------------------
***/


void BZ2_bzWrite(int *bzerror, BZFILE *b, void *buf, int len)
{
  Int32 n;
  Int32 n2;
  Int32 ret;
  bzFile *bzf = (bzFile *) b;
  {
    if (bzerror != 0)
    {
      *bzerror = 0;
    }
    if (bzf != 0)
    {
      bzf->lastErr = 0;
    }
  }
  ;
  if (((bzf == 0) || (buf == 0)) || (len < 0))
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -2;
      }
      if (bzf != 0)
      {
        bzf->lastErr = -2;
      }
    }
    ;
    return;
  }
  ;
  if (!bzf->writing)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -1;
      }
      if (bzf != 0)
      {
        bzf->lastErr = -1;
      }
    }
    ;
    return;
  }
  ;
  if (ferror(bzf->handle))
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -6;
      }
      if (bzf != 0)
      {
        bzf->lastErr = -6;
      }
    }
    ;
    return;
  }
  ;
  if (len == 0)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = 0;
      }
      if (bzf != 0)
      {
        bzf->lastErr = 0;
      }
    }
    ;
    return;
  }
  ;
  bzf->strm.avail_in = len;
  bzf->strm.next_in = buf;
  while ((Bool) 1)
  {
    helper_BZ2_bzWrite_1(&n, &n2, &ret, bzerror, bzf);
  }

}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
void helper_BZ2_bzWrite_1(Int32 * const n_ref, Int32 * const n2_ref, Int32 * const ret_ref, int * const bzerror, bzFile * const bzf)
{
  Int32 n = *n_ref;
  Int32 n2 = *n2_ref;
  Int32 ret = *ret_ref;
  bzf->strm.avail_out = 5000;
  bzf->strm.next_out = bzf->buf;
  ret = BZ2_bzCompress(&bzf->strm, 0);
  if (ret != 1)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = ret;
      }
      if (bzf != 0)
      {
        bzf->lastErr = ret;
      }
    }
    ;
    return;
  }
  ;
  if (bzf->strm.avail_out < 5000)
  {
    n = 5000 - bzf->strm.avail_out;
    n2 = fwrite((void *) bzf->buf, sizeof(UChar), n, bzf->handle);
    if ((n != n2) || ferror(bzf->handle))
    {
      {
        if (bzerror != 0)
        {
          *bzerror = -6;
        }
        if (bzf != 0)
        {
          bzf->lastErr = -6;
        }
      }
      ;
      return;
    }
    ;
  }
  if (bzf->strm.avail_in == 0)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = 0;
      }
      if (bzf != 0)
      {
        bzf->lastErr = 0;
      }
    }
    ;
    return;
  }
  ;
  *n_ref = n;
  *n2_ref = n2;
  *ret_ref = ret;
}


----------------------------
typedef void BZFILE
----------------------------
typedef struct 
{
  FILE *handle;
  Char buf[5000];
  Int32 bufN;
  Bool writing;
  bz_stream strm;
  Int32 lastErr;
  Bool initialisedOk;
} bzFile
----------------------------
***/


int BZ2_bzwrite(BZFILE *b, void *buf, int len)
{
  int bzerr;
  BZ2_bzWrite(&bzerr, b, buf, len);
  if (bzerr == 0)
  {
    return len;
  }
  else
  {
    return -1;
  }
}


/*** DEPENDENCIES:
void BZ2_bzWrite(int *bzerror, BZFILE *b, void *buf, int len)
{
  Int32 n;
  Int32 n2;
  Int32 ret;
  bzFile *bzf = (bzFile *) b;
  {
    if (bzerror != 0)
    {
      *bzerror = 0;
    }
    if (bzf != 0)
    {
      bzf->lastErr = 0;
    }
  }
  ;
  if (((bzf == 0) || (buf == 0)) || (len < 0))
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -2;
      }
      if (bzf != 0)
      {
        bzf->lastErr = -2;
      }
    }
    ;
    return;
  }
  ;
  if (!bzf->writing)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -1;
      }
      if (bzf != 0)
      {
        bzf->lastErr = -1;
      }
    }
    ;
    return;
  }
  ;
  if (ferror(bzf->handle))
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -6;
      }
      if (bzf != 0)
      {
        bzf->lastErr = -6;
      }
    }
    ;
    return;
  }
  ;
  if (len == 0)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = 0;
      }
      if (bzf != 0)
      {
        bzf->lastErr = 0;
      }
    }
    ;
    return;
  }
  ;
  bzf->strm.avail_in = len;
  bzf->strm.next_in = buf;
  while ((Bool) 1)
  {
    helper_BZ2_bzWrite_1(&n, &n2, &ret, bzerror, bzf);
  }

}


----------------------------
typedef void BZFILE
----------------------------
***/


const char *BZ2_bzerror(BZFILE *b, int *errnum)
{
  int err = ((bzFile *) b)->lastErr;
  if (err > 0)
  {
    err = 0;
  }
  *errnum = err;
  return bzerrorstrings[err * (-1)];
}


/*** DEPENDENCIES:
typedef void BZFILE
----------------------------
static const char *bzerrorstrings[] = {"OK", "SEQUENCE_ERROR", "PARAM_ERROR", "MEM_ERROR", "DATA_ERROR", "DATA_ERROR_MAGIC", "IO_ERROR", "UNEXPECTED_EOF", "OUTBUFF_FULL", "CONFIG_ERROR", "???", "???", "???", "???", "???", "???"}
----------------------------
***/


void BZ2_bzReadClose(int *bzerror, BZFILE *b)
{
  bzFile *bzf = (bzFile *) b;
  {
    if (bzerror != 0)
    {
      *bzerror = 0;
    }
    if (bzf != 0)
    {
      bzf->lastErr = 0;
    }
  }
  ;
  if (bzf == 0)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = 0;
      }
      if (bzf != 0)
      {
        bzf->lastErr = 0;
      }
    }
    ;
    return;
  }
  ;
  if (bzf->writing)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -1;
      }
      if (bzf != 0)
      {
        bzf->lastErr = -1;
      }
    }
    ;
    return;
  }
  ;
  if (bzf->initialisedOk)
  {
    (void) BZ2_bzDecompressEnd(&bzf->strm);
  }
  free(bzf);
}


/*** DEPENDENCIES:
typedef struct 
{
  FILE *handle;
  Char buf[5000];
  Int32 bufN;
  Bool writing;
  bz_stream strm;
  Int32 lastErr;
  Bool initialisedOk;
} bzFile
----------------------------
int BZ2_bzDecompressEnd(bz_stream *strm)
{
  DState *s;
  unsigned int s_idx = 0;
  if (strm == 0)
  {
    return -2;
  }
  s_idx = strm->state;
  if ((&s[s_idx]) == 0)
  {
    return -2;
  }
  if (s->strm != strm)
  {
    return -2;
  }
  if (s->tt != 0)
  {
    strm->bzfree(strm->opaque, s->tt);
  }
  if (s->ll16 != 0)
  {
    strm->bzfree(strm->opaque, s->ll16);
  }
  if (s->ll4 != 0)
  {
    strm->bzfree(strm->opaque, s->ll4);
  }
  strm->bzfree(strm->opaque, strm->state);
  strm->state = 0;
  return 0;
}


----------------------------
typedef void BZFILE
----------------------------
***/


void BZ2_bzclose(BZFILE *b)
{
  int bzerr;
  FILE *fp;
  unsigned int fp_idx = 0;
  if (b == 0)
  {
    return;
  }
  fp_idx = ((bzFile *) b)->handle;
  if (((bzFile *) b)->writing)
  {
    BZ2_bzWriteClose(&bzerr, b, 0, 0, 0);
    if (bzerr != 0)
    {
      BZ2_bzWriteClose(0, b, 1, 0, 0);
    }
  }
  else
  {
    BZ2_bzReadClose(&bzerr, b);
  }
  if (((&fp[fp_idx]) != stdin) && ((&fp[fp_idx]) != stdout))
  {
    fclose(fp);
  }
}


/*** DEPENDENCIES:
void BZ2_bzReadClose(int *bzerror, BZFILE *b)
{
  bzFile *bzf = (bzFile *) b;
  {
    if (bzerror != 0)
    {
      *bzerror = 0;
    }
    if (bzf != 0)
    {
      bzf->lastErr = 0;
    }
  }
  ;
  if (bzf == 0)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = 0;
      }
      if (bzf != 0)
      {
        bzf->lastErr = 0;
      }
    }
    ;
    return;
  }
  ;
  if (bzf->writing)
  {
    {
      if (bzerror != 0)
      {
        *bzerror = -1;
      }
      if (bzf != 0)
      {
        bzf->lastErr = -1;
      }
    }
    ;
    return;
  }
  ;
  if (bzf->initialisedOk)
  {
    (void) BZ2_bzDecompressEnd(&bzf->strm);
  }
  free(bzf);
}


----------------------------
typedef void BZFILE
----------------------------
void BZ2_bzWriteClose(int *bzerror, BZFILE *b, int abandon, unsigned int *nbytes_in, unsigned int *nbytes_out)
{
  BZ2_bzWriteClose64(bzerror, b, abandon, nbytes_in, 0, nbytes_out, 0);
}


----------------------------
***/


int BZ2_bzBuffToBuffCompress(char *dest, unsigned int *destLen, char *source, unsigned int sourceLen, int blockSize100k, int verbosity, int workFactor)
{
  bz_stream strm;
  int ret;
  if (((((((((dest == 0) || (destLen == 0)) || (source == 0)) || (blockSize100k < 1)) || (blockSize100k > 9)) || (verbosity < 0)) || (verbosity > 4)) || (workFactor < 0)) || (workFactor > 250))
  {
    return -2;
  }
  if (workFactor == 0)
  {
    workFactor = 30;
  }
  strm.bzalloc = 0;
  strm.bzfree = 0;
  strm.opaque = 0;
  ret = BZ2_bzCompressInit(&strm, blockSize100k, verbosity, workFactor);
  if (ret != 0)
  {
    return ret;
  }
  strm.next_in = source;
  strm.next_out = dest;
  strm.avail_in = sourceLen;
  strm.avail_out = *destLen;
  ret = BZ2_bzCompress(&strm, 2);
  if (ret == 3)
  {
    goto output_overflow;
  }
  if (ret != 4)
  {
    goto errhandler;
  }
  *destLen -= strm.avail_out;
  BZ2_bzCompressEnd(&strm);
  return 0;
  output_overflow:
  BZ2_bzCompressEnd(&strm);

  return -8;
  errhandler:
  BZ2_bzCompressEnd(&strm);

  return ret;
}


/*** DEPENDENCIES:
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
} bz_stream
----------------------------
int BZ2_bzCompressEnd(bz_stream *strm)
{
  EState *s;
  unsigned int s_idx = 0;
  if (strm == 0)
  {
    return -2;
  }
  s_idx = strm->state;
  if ((&s[s_idx]) == 0)
  {
    return -2;
  }
  if (s->strm != strm)
  {
    return -2;
  }
  if (s->arr1 != 0)
  {
    strm->bzfree(strm->opaque, s->arr1);
  }
  if (s->arr2 != 0)
  {
    strm->bzfree(strm->opaque, s->arr2);
  }
  if (s->ftab != 0)
  {
    strm->bzfree(strm->opaque, s->ftab);
  }
  strm->bzfree(strm->opaque, strm->state);
  strm->state = 0;
  return 0;
}


----------------------------
int BZ2_bzCompressInit(bz_stream *strm, int blockSize100k, int verbosity, int workFactor)
{
  Int32 n;
  EState *s;
  unsigned int s_idx = 0;
  if (!bz_config_ok())
  {
    return -9;
  }
  if (((((strm == 0) || (blockSize100k < 1)) || (blockSize100k > 9)) || (workFactor < 0)) || (workFactor > 250))
  {
    return -2;
  }
  if (workFactor == 0)
  {
    workFactor = 30;
  }
  if (strm->bzalloc == 0)
  {
    strm->bzalloc = default_bzalloc;
  }
  if (strm->bzfree == 0)
  {
    strm->bzfree = default_bzfree;
  }
  s_idx = strm->bzalloc(strm->opaque, sizeof(EState), 1);
  if ((&s[s_idx]) == 0)
  {
    return -3;
  }
  s->strm = strm;
  s->arr1 = 0;
  s->arr2 = 0;
  s->ftab = 0;
  n = 100000 * blockSize100k;
  s->arr1 = strm->bzalloc(strm->opaque, n * (sizeof(UInt32)), 1);
  s->arr2 = strm->bzalloc(strm->opaque, (n + (((2 + 12) + 18) + 2)) * (sizeof(UInt32)), 1);
  s->ftab = strm->bzalloc(strm->opaque, 65537 * (sizeof(UInt32)), 1);
  if (((s->arr1 == 0) || (s->arr2 == 0)) || (s->ftab == 0))
  {
    if (s->arr1 != 0)
    {
      strm->bzfree(strm->opaque, s->arr1);
    }
    if (s->arr2 != 0)
    {
      strm->bzfree(strm->opaque, s->arr2);
    }
    if (s->ftab != 0)
    {
      strm->bzfree(strm->opaque, s->ftab);
    }
    if ((&s[s_idx]) != 0)
    {
      strm->bzfree(strm->opaque, s);
    }
    return -3;
  }
  s->blockNo = 0;
  s->state = 2;
  s->mode = 2;
  s->combinedCRC = 0;
  s->blockSize100k = blockSize100k;
  s->nblockMAX = (100000 * blockSize100k) - 19;
  s->verbosity = verbosity;
  s->workFactor = workFactor;
  s->block = (UChar *) s->arr2;
  s->mtfv = (UInt16 *) s->arr1;
  s->zbits = 0;
  s->ptr = (UInt32 *) s->arr1;
  strm->state = &s[s_idx];
  strm->total_in_lo32 = 0;
  strm->total_in_hi32 = 0;
  strm->total_out_lo32 = 0;
  strm->total_out_hi32 = 0;
  init_RL(s);
  prepare_new_block(s);
  return 0;
}


----------------------------
int BZ2_bzCompress(bz_stream *strm, int action)
{
  Bool progress;
  EState *s;
  unsigned int s_idx = 0;
  if (strm == 0)
  {
    return -2;
  }
  s_idx = strm->state;
  if ((&s[s_idx]) == 0)
  {
    return -2;
  }
  if (s->strm != strm)
  {
    return -2;
  }
  preswitch:
  switch (s->mode)
  {
    case 1:
    {
      return -1;
    }

    case 2:
    {
      if (action == 0)
      {
        progress = handle_compress(strm);
        return (progress) ? (1) : (-2);
      }
      else
        if (action == 1)
      {
        s->avail_in_expect = strm->avail_in;
        s->mode = 3;
        goto preswitch;
      }
      else
        if (action == 2)
      {
        s->avail_in_expect = strm->avail_in;
        s->mode = 4;
        goto preswitch;
      }
      else
        return -2;
    }

    case 3:
    {
      if (action != 1)
      {
        return -1;
      }
      if (s->avail_in_expect != s->strm->avail_in)
      {
        return -1;
      }
      progress = handle_compress(strm);
      if (((s->avail_in_expect > 0) || (!isempty_RL(s))) || (s->state_out_pos < s->numZ))
      {
        return 2;
      }
      s->mode = 2;
      return 1;
    }

    case 4:
    {
      if (action != 2)
      {
        return -1;
      }
      if (s->avail_in_expect != s->strm->avail_in)
      {
        return -1;
      }
      progress = handle_compress(strm);
      if (!progress)
      {
        return -1;
      }
      if (((s->avail_in_expect > 0) || (!isempty_RL(s))) || (s->state_out_pos < s->numZ))
      {
        return 3;
      }
      s->mode = 1;
      return 4;
    }

  }


  return 0;
}


----------------------------
***/


int BZ2_bzBuffToBuffDecompress(char *dest, unsigned int *destLen, char *source, unsigned int sourceLen, int small, int verbosity)
{
  bz_stream strm;
  int ret;
  if ((((((dest == 0) || (destLen == 0)) || (source == 0)) || ((small != 0) && (small != 1))) || (verbosity < 0)) || (verbosity > 4))
  {
    return -2;
  }
  strm.bzalloc = 0;
  strm.bzfree = 0;
  strm.opaque = 0;
  ret = BZ2_bzDecompressInit(&strm, verbosity, small);
  if (ret != 0)
  {
    return ret;
  }
  strm.next_in = source;
  strm.next_out = dest;
  strm.avail_in = sourceLen;
  strm.avail_out = *destLen;
  ret = BZ2_bzDecompress(&strm);
  if (ret == 0)
  {
    goto output_overflow_or_eof;
  }
  if (ret != 4)
  {
    goto errhandler;
  }
  *destLen -= strm.avail_out;
  BZ2_bzDecompressEnd(&strm);
  return 0;
  output_overflow_or_eof:
  if (strm.avail_out > 0)
  {
    BZ2_bzDecompressEnd(&strm);
    return -7;
  }
  else
  {
    BZ2_bzDecompressEnd(&strm);
    return -8;
  }

  ;
  errhandler:
  BZ2_bzDecompressEnd(&strm);

  return ret;
}


/*** DEPENDENCIES:
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
} bz_stream
----------------------------
int BZ2_bzDecompressInit(bz_stream *strm, int verbosity, int small)
{
  DState *s;
  unsigned int s_idx = 0;
  if (!bz_config_ok())
  {
    return -9;
  }
  if (strm == 0)
  {
    return -2;
  }
  if ((small != 0) && (small != 1))
  {
    return -2;
  }
  if ((verbosity < 0) || (verbosity > 4))
  {
    return -2;
  }
  if (strm->bzalloc == 0)
  {
    strm->bzalloc = default_bzalloc;
  }
  if (strm->bzfree == 0)
  {
    strm->bzfree = default_bzfree;
  }
  s_idx = strm->bzalloc(strm->opaque, sizeof(DState), 1);
  if ((&s[s_idx]) == 0)
  {
    return -3;
  }
  s->strm = strm;
  strm->state = &s[s_idx];
  s->state = 10;
  s->bsLive = 0;
  s->bsBuff = 0;
  s->calculatedCombinedCRC = 0;
  strm->total_in_lo32 = 0;
  strm->total_in_hi32 = 0;
  strm->total_out_lo32 = 0;
  strm->total_out_hi32 = 0;
  s->smallDecompress = (Bool) small;
  s->ll4 = 0;
  s->ll16 = 0;
  s->tt = 0;
  s->currBlockNo = 0;
  s->verbosity = verbosity;
  return 0;
}


----------------------------
int BZ2_bzDecompressEnd(bz_stream *strm)
{
  DState *s;
  unsigned int s_idx = 0;
  if (strm == 0)
  {
    return -2;
  }
  s_idx = strm->state;
  if ((&s[s_idx]) == 0)
  {
    return -2;
  }
  if (s->strm != strm)
  {
    return -2;
  }
  if (s->tt != 0)
  {
    strm->bzfree(strm->opaque, s->tt);
  }
  if (s->ll16 != 0)
  {
    strm->bzfree(strm->opaque, s->ll16);
  }
  if (s->ll4 != 0)
  {
    strm->bzfree(strm->opaque, s->ll4);
  }
  strm->bzfree(strm->opaque, strm->state);
  strm->state = 0;
  return 0;
}


----------------------------
int BZ2_bzDecompress(bz_stream *strm)
{
  Bool corrupt;
  DState *s;
  unsigned int s_idx = 0;
  if (strm == 0)
  {
    return -2;
  }
  s_idx = strm->state;
  if ((&s[s_idx]) == 0)
  {
    return -2;
  }
  if (s->strm != strm)
  {
    return -2;
  }
  while ((Bool) 1)
  {
    helper_BZ2_bzDecompress_1(&corrupt, s);
  }

  {
    if (!0)
    {
      BZ2_bz__AssertH__fail(6001);
    }
  }
  ;
  return 0;
}


----------------------------
***/


