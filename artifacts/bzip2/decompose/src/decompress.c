void helper_BZ2_decompress_11(DState * const s)
{
  s->save_i = 0;
  s->save_j = 0;
  s->save_t = 0;
  s->save_alphaSize = 0;
  s->save_nGroups = 0;
  s->save_nSelectors = 0;
  s->save_EOB = 0;
  s->save_groupNo = 0;
  s->save_groupPos = 0;
  s->save_nextSym = 0;
  s->save_nblockMAX = 0;
  s->save_nblock = 0;
  s->save_es = 0;
  s->save_N = 0;
  s->save_curr = 0;
  s->save_zt = 0;
  s->save_zn = 0;
  s->save_zvec = 0;
  s->save_zj = 0;
  s->save_gSel = 0;
  s->save_gMinlen = 0;
  s->save_gLimit = 0;
  s->save_gBase = 0;
  s->save_gPerm = 0;
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
***/


static void makeMaps_d(DState *s)
{
  Int32 i;
  s->nInUse = 0;
  for (i = 0; i < 256; i += 1)
    if (s->inUse[i])
  {
    s->seqToUnseq[s->nInUse] = i;
    s->nInUse += 1;
  }

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
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32']
void helper_BZ2_decompress_16(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 16;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if (uc != 0x59)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  *uc_ref = uc;
  *retVal_ref = retVal;
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
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32']
void helper_BZ2_decompress_22(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 45;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if (uc != 0x50)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  *uc_ref = uc;
  *retVal_ref = retVal;
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
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32']
void helper_BZ2_decompress_17(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 17;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if (uc != 0x26)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  *uc_ref = uc;
  *retVal_ref = retVal;
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
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32', 'i_ref is a mutable refrence to Int32']
void helper_helper_BZ2_decompress_28_2(UChar * const uc_ref, Int32 * const retVal_ref, Int32 * const i_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  Int32 i = *i_ref;
  case 28:
    s->state = 28;

  while ((Bool) 1)
  {
    if (s->bsLive >= 1)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 1)) & ((1 << 1) - 1);
      s->bsLive -= 1;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if (uc == 1)
  {
    s->inUse16[i] = (Bool) 1;
  }
  else
    s->inUse16[i] = (Bool) 0;
  *uc_ref = uc;
  *retVal_ref = retVal;
  *i_ref = i;
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
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32']
void helper_helper_BZ2_decompress_28_1(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  if (s->bsLive >= 8)
  {
    UInt32 v;
    v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
    s->bsLive -= 8;
    uc = v;
    break;
  }
  if (s->strm->avail_in == 0)
  {
    retVal = 0;
    goto save_state_and_return;
  }
  ;
  ;
  s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
  s->bsLive += 8;
  s->strm->next_in += 1;
  s->strm->avail_in -= 1;
  s->strm->total_in_lo32 += 1;
  if (s->strm->total_in_lo32 == 0)
  {
    s->strm->total_in_hi32 += 1;
  }
  *uc_ref = uc;
  *retVal_ref = retVal;
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
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32', 'i_ref is a mutable refrence to Int32', 'j_ref is a mutable refrence to Int32']
void helper_helper_BZ2_decompress_28_3(UChar * const uc_ref, Int32 * const retVal_ref, Int32 * const i_ref, Int32 * const j_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  Int32 i = *i_ref;
  Int32 j = *j_ref;
  for (j = 0; j < 16; j += 1)
  {
    case 29:
      s->state = 29;

    while ((Bool) 1)
    {
      if (s->bsLive >= 1)
      {
        UInt32 v;
        v = (s->bsBuff >> (s->bsLive - 1)) & ((1 << 1) - 1);
        s->bsLive -= 1;
        uc = v;
        break;
      }
      if (s->strm->avail_in == 0)
      {
        retVal = 0;
        goto save_state_and_return;
      }
      ;
      ;
      s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
      s->bsLive += 8;
      s->strm->next_in += 1;
      s->strm->avail_in -= 1;
      s->strm->total_in_lo32 += 1;
      if (s->strm->total_in_lo32 == 0)
      {
        s->strm->total_in_hi32 += 1;
      }
    }

    ;
    if (uc == 1)
    {
      s->inUse[(i * 16) + j] = (Bool) 1;
    }
  }

  *uc_ref = uc;
  *retVal_ref = retVal;
  *i_ref = i;
  *j_ref = j;
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
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32', 'i_ref is a mutable refrence to Int32', 'j_ref is a mutable refrence to Int32', 'alphaSize_ref is a mutable refrence to Int32']
void helper_BZ2_decompress_28(UChar * const uc_ref, Int32 * const retVal_ref, Int32 * const i_ref, Int32 * const j_ref, Int32 * const alphaSize_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  Int32 i = *i_ref;
  Int32 j = *j_ref;
  Int32 alphaSize = *alphaSize_ref;
  s->state = 27;
  while ((Bool) 1)
  {
    helper_helper_BZ2_decompress_28_1(&uc, &retVal, s);
  }

  ;
  s->origPtr = (s->origPtr << 8) | ((Int32) uc);
  if (s->origPtr < 0)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  if (s->origPtr > (10 + (100000 * s->blockSize100k)))
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  for (i = 0; i < 16; i += 1)
  {
    helper_helper_BZ2_decompress_28_2(&uc, &retVal, &i, s);
  }

  for (i = 0; i < 256; i += 1)
    s->inUse[i] = (Bool) 0;

  for (i = 0; i < 16; i += 1)
    if (s->inUse16[i])
  {
    helper_helper_BZ2_decompress_28_3(&uc, &retVal, &i, &j, s);
  }

  makeMaps_d(s);
  if (s->nInUse == 0)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  alphaSize = s->nInUse + 2;
  *uc_ref = uc;
  *retVal_ref = retVal;
  *i_ref = i;
  *j_ref = j;
  *alphaSize_ref = alphaSize;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
void helper_helper_BZ2_decompress_28_2(UChar * const uc_ref, Int32 * const retVal_ref, Int32 * const i_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  Int32 i = *i_ref;
  case 28:
    s->state = 28;

  while ((Bool) 1)
  {
    if (s->bsLive >= 1)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 1)) & ((1 << 1) - 1);
      s->bsLive -= 1;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if (uc == 1)
  {
    s->inUse16[i] = (Bool) 1;
  }
  else
    s->inUse16[i] = (Bool) 0;
  *uc_ref = uc;
  *retVal_ref = retVal;
  *i_ref = i;
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
void helper_helper_BZ2_decompress_28_1(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  if (s->bsLive >= 8)
  {
    UInt32 v;
    v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
    s->bsLive -= 8;
    uc = v;
    break;
  }
  if (s->strm->avail_in == 0)
  {
    retVal = 0;
    goto save_state_and_return;
  }
  ;
  ;
  s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
  s->bsLive += 8;
  s->strm->next_in += 1;
  s->strm->avail_in -= 1;
  s->strm->total_in_lo32 += 1;
  if (s->strm->total_in_lo32 == 0)
  {
    s->strm->total_in_hi32 += 1;
  }
  *uc_ref = uc;
  *retVal_ref = retVal;
}


----------------------------
typedef char Char
----------------------------
static void makeMaps_d(DState *s)
{
  Int32 i;
  s->nInUse = 0;
  for (i = 0; i < 256; i += 1)
    if (s->inUse[i])
  {
    s->seqToUnseq[s->nInUse] = i;
    s->nInUse += 1;
  }

}


----------------------------
void helper_helper_BZ2_decompress_28_3(UChar * const uc_ref, Int32 * const retVal_ref, Int32 * const i_ref, Int32 * const j_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  Int32 i = *i_ref;
  Int32 j = *j_ref;
  for (j = 0; j < 16; j += 1)
  {
    case 29:
      s->state = 29;

    while ((Bool) 1)
    {
      if (s->bsLive >= 1)
      {
        UInt32 v;
        v = (s->bsBuff >> (s->bsLive - 1)) & ((1 << 1) - 1);
        s->bsLive -= 1;
        uc = v;
        break;
      }
      if (s->strm->avail_in == 0)
      {
        retVal = 0;
        goto save_state_and_return;
      }
      ;
      ;
      s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
      s->bsLive += 8;
      s->strm->next_in += 1;
      s->strm->avail_in -= 1;
      s->strm->total_in_lo32 += 1;
      if (s->strm->total_in_lo32 == 0)
      {
        s->strm->total_in_hi32 += 1;
      }
    }

    ;
    if (uc == 1)
    {
      s->inUse[(i * 16) + j] = (Bool) 1;
    }
  }

  *uc_ref = uc;
  *retVal_ref = retVal;
  *i_ref = i;
  *j_ref = j;
}


----------------------------
typedef unsigned char UChar
----------------------------
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32']
void helper_BZ2_decompress_3(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 22;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  s->storedBlockCRC = (s->storedBlockCRC << 8) | ((UInt32) uc);
  *uc_ref = uc;
  *retVal_ref = retVal;
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
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32']
void helper_BZ2_decompress_23(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 46;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if (uc != 0x90)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  s->storedCombinedCRC = 0;
  *uc_ref = uc;
  *retVal_ref = retVal;
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
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32']
void helper_BZ2_decompress_9(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 48;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  s->storedCombinedCRC = (s->storedCombinedCRC << 8) | ((UInt32) uc);
  *uc_ref = uc;
  *retVal_ref = retVal;
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
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32']
void helper_BZ2_decompress_7(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 26;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  s->origPtr = (s->origPtr << 8) | ((Int32) uc);
  *uc_ref = uc;
  *retVal_ref = retVal;
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
***/


// hint:  ['retVal_ref is a mutable refrence to Int32', 'nSelectors_ref is a mutable refrence to Int32']
void helper_helper_BZ2_decompress_29_1(Int32 * const retVal_ref, Int32 * const nSelectors_ref, DState * const s)
{
  Int32 retVal = *retVal_ref;
  Int32 nSelectors = *nSelectors_ref;
  if (s->bsLive >= 15)
  {
    UInt32 v;
    v = (s->bsBuff >> (s->bsLive - 15)) & ((1 << 15) - 1);
    s->bsLive -= 15;
    nSelectors = v;
    break;
  }
  if (s->strm->avail_in == 0)
  {
    retVal = 0;
    goto save_state_and_return;
  }
  ;
  ;
  s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
  s->bsLive += 8;
  s->strm->next_in += 1;
  s->strm->avail_in -= 1;
  s->strm->total_in_lo32 += 1;
  if (s->strm->total_in_lo32 == 0)
  {
    s->strm->total_in_hi32 += 1;
  }
  *retVal_ref = retVal;
  *nSelectors_ref = nSelectors;
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
***/


// hint:  ['retVal_ref is a mutable refrence to Int32', 'zvec_ref is a mutable refrence to Int32']
void helper_helper_helper_BZ2_decompress_29_6_1(Int32 * const retVal_ref, Int32 * const zvec_ref, DState * const s, Int32 zn)
{
  Int32 retVal = *retVal_ref;
  Int32 zvec = *zvec_ref;
  if (s->bsLive >= zn)
  {
    UInt32 v;
    v = (s->bsBuff >> (s->bsLive - zn)) & ((1 << zn) - 1);
    s->bsLive -= zn;
    zvec = v;
    break;
  }
  if (s->strm->avail_in == 0)
  {
    retVal = 0;
    goto save_state_and_return;
  }
  ;
  ;
  s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
  s->bsLive += 8;
  s->strm->next_in += 1;
  s->strm->avail_in -= 1;
  s->strm->total_in_lo32 += 1;
  if (s->strm->total_in_lo32 == 0)
  {
    s->strm->total_in_hi32 += 1;
  }
  *retVal_ref = retVal;
  *zvec_ref = zvec;
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
***/


// hint:  ['retVal_ref is a mutable refrence to Int32', 'zj_ref is a mutable refrence to Int32']
void helper_helper_helper_helper_BZ2_decompress_29_6_2_1(Int32 * const retVal_ref, Int32 * const zj_ref, DState * const s)
{
  Int32 retVal = *retVal_ref;
  Int32 zj = *zj_ref;
  if (s->bsLive >= 1)
  {
    UInt32 v;
    v = (s->bsBuff >> (s->bsLive - 1)) & ((1 << 1) - 1);
    s->bsLive -= 1;
    zj = v;
    break;
  }
  if (s->strm->avail_in == 0)
  {
    retVal = 0;
    goto save_state_and_return;
  }
  ;
  ;
  s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
  s->bsLive += 8;
  s->strm->next_in += 1;
  s->strm->avail_in -= 1;
  s->strm->total_in_lo32 += 1;
  if (s->strm->total_in_lo32 == 0)
  {
    s->strm->total_in_hi32 += 1;
  }
  *retVal_ref = retVal;
  *zj_ref = zj;
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
***/


// hint:  ['retVal_ref is a mutable refrence to Int32', 'zn_ref is a mutable refrence to Int32', 'zvec_ref is a mutable refrence to Int32', 'zj_ref is a mutable refrence to Int32']
void helper_helper_helper_BZ2_decompress_29_6_2(Int32 * const retVal_ref, Int32 * const zn_ref, Int32 * const zvec_ref, Int32 * const zj_ref, DState * const s, Int32 * const gLimit, unsigned int gLimit_idx)
{
  Int32 retVal = *retVal_ref;
  Int32 zn = *zn_ref;
  Int32 zvec = *zvec_ref;
  Int32 zj = *zj_ref;
  if (zn > 20)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  if (zvec <= gLimit[zn + gLimit_idx])
  {
    break;
  }
  zn += 1;
  case 37:
    s->state = 37;

  while ((Bool) 1)
  {
    helper_helper_helper_helper_BZ2_decompress_29_6_2_1(&retVal, &zj, s);
  }

  ;
  zvec = (zvec << 1) | zj;
  *retVal_ref = retVal;
  *zn_ref = zn;
  *zvec_ref = zvec;
  *zj_ref = zj;
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
void helper_helper_helper_helper_BZ2_decompress_29_6_2_1(Int32 * const retVal_ref, Int32 * const zj_ref, DState * const s)
{
  Int32 retVal = *retVal_ref;
  Int32 zj = *zj_ref;
  if (s->bsLive >= 1)
  {
    UInt32 v;
    v = (s->bsBuff >> (s->bsLive - 1)) & ((1 << 1) - 1);
    s->bsLive -= 1;
    zj = v;
    break;
  }
  if (s->strm->avail_in == 0)
  {
    retVal = 0;
    goto save_state_and_return;
  }
  ;
  ;
  s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
  s->bsLive += 8;
  s->strm->next_in += 1;
  s->strm->avail_in -= 1;
  s->strm->total_in_lo32 += 1;
  if (s->strm->total_in_lo32 == 0)
  {
    s->strm->total_in_hi32 += 1;
  }
  *retVal_ref = retVal;
  *zj_ref = zj;
}


----------------------------
***/


// hint:  ['retVal_ref is a mutable refrence to Int32', 'groupNo_ref is a mutable refrence to Int32', 'groupPos_ref is a mutable refrence to Int32', 'nextSym_ref is a mutable refrence to Int32', 'zn_ref is a mutable refrence to Int32', 'zvec_ref is a mutable refrence to Int32', 'zj_ref is a mutable refrence to Int32', 'gSel_ref is a mutable refrence to Int32', 'gMinlen_ref is a mutable refrence to Int32', 'gLimit_idx_ref is a mutable refrence to unsigned int', 'gBase_idx_ref is a mutable refrence to unsigned int', 'gPerm_idx_ref is a mutable refrence to unsigned int']
void helper_helper_BZ2_decompress_29_6(Int32 * const retVal_ref, Int32 * const groupNo_ref, Int32 * const groupPos_ref, Int32 * const nextSym_ref, Int32 * const zn_ref, Int32 * const zvec_ref, Int32 * const zj_ref, Int32 * const gSel_ref, Int32 * const gMinlen_ref, unsigned int * const gLimit_idx_ref, unsigned int * const gBase_idx_ref, unsigned int * const gPerm_idx_ref, DState * const s, Int32 * const gLimit, Int32 * const gBase, Int32 * const gPerm, Int32 nSelectors)
{
  Int32 retVal = *retVal_ref;
  Int32 groupNo = *groupNo_ref;
  Int32 groupPos = *groupPos_ref;
  Int32 nextSym = *nextSym_ref;
  Int32 zn = *zn_ref;
  Int32 zvec = *zvec_ref;
  Int32 zj = *zj_ref;
  Int32 gSel = *gSel_ref;
  Int32 gMinlen = *gMinlen_ref;
  unsigned int gLimit_idx = *gLimit_idx_ref;
  unsigned int gBase_idx = *gBase_idx_ref;
  unsigned int gPerm_idx = *gPerm_idx_ref;
  if (groupPos == 0)
  {
    groupNo += 1;
    if (groupNo >= nSelectors)
    {
      retVal = -4;
      goto save_state_and_return;
    }
    ;
    ;
    groupPos = 50;
    gSel = s->selector[groupNo];
    gMinlen = s->minLens[gSel];
    gLimit_idx = &s->limit[gSel][0];
    gPerm_idx = &s->perm[gSel][0];
    gBase_idx = &s->base[gSel][0];
  }
  groupPos -= 1;
  zn = gMinlen;
  case 36:
    s->state = 36;

  while ((Bool) 1)
  {
    helper_helper_helper_BZ2_decompress_29_6_1(&retVal, &zvec, s, zn);
  }

  ;
  while (1)
  {
    helper_helper_helper_BZ2_decompress_29_6_2(&retVal, &zn, &zvec, &zj, s, gLimit, gLimit_idx);
  }

  ;
  if (((zvec - gBase[zn + gBase_idx]) < 0) || ((zvec - gBase[zn + gBase_idx]) >= 258))
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  nextSym = gPerm[(zvec - gBase[zn + gBase_idx]) + gPerm_idx];
  *retVal_ref = retVal;
  *groupNo_ref = groupNo;
  *groupPos_ref = groupPos;
  *nextSym_ref = nextSym;
  *zn_ref = zn;
  *zvec_ref = zvec;
  *zj_ref = zj;
  *gSel_ref = gSel;
  *gMinlen_ref = gMinlen;
  *gLimit_idx_ref = gLimit_idx;
  *gBase_idx_ref = gBase_idx;
  *gPerm_idx_ref = gPerm_idx;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
void helper_helper_helper_BZ2_decompress_29_6_1(Int32 * const retVal_ref, Int32 * const zvec_ref, DState * const s, Int32 zn)
{
  Int32 retVal = *retVal_ref;
  Int32 zvec = *zvec_ref;
  if (s->bsLive >= zn)
  {
    UInt32 v;
    v = (s->bsBuff >> (s->bsLive - zn)) & ((1 << zn) - 1);
    s->bsLive -= zn;
    zvec = v;
    break;
  }
  if (s->strm->avail_in == 0)
  {
    retVal = 0;
    goto save_state_and_return;
  }
  ;
  ;
  s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
  s->bsLive += 8;
  s->strm->next_in += 1;
  s->strm->avail_in -= 1;
  s->strm->total_in_lo32 += 1;
  if (s->strm->total_in_lo32 == 0)
  {
    s->strm->total_in_hi32 += 1;
  }
  *retVal_ref = retVal;
  *zvec_ref = zvec;
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
void helper_helper_helper_BZ2_decompress_29_6_2(Int32 * const retVal_ref, Int32 * const zn_ref, Int32 * const zvec_ref, Int32 * const zj_ref, DState * const s, Int32 * const gLimit, unsigned int gLimit_idx)
{
  Int32 retVal = *retVal_ref;
  Int32 zn = *zn_ref;
  Int32 zvec = *zvec_ref;
  Int32 zj = *zj_ref;
  if (zn > 20)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  if (zvec <= gLimit[zn + gLimit_idx])
  {
    break;
  }
  zn += 1;
  case 37:
    s->state = 37;

  while ((Bool) 1)
  {
    helper_helper_helper_helper_BZ2_decompress_29_6_2_1(&retVal, &zj, s);
  }

  ;
  zvec = (zvec << 1) | zj;
  *retVal_ref = retVal;
  *zn_ref = zn;
  *zvec_ref = zvec;
  *zj_ref = zj;
}


----------------------------
***/


// hint:  ['retVal_ref is a mutable refrence to Int32', 'groupNo_ref is a mutable refrence to Int32', 'groupPos_ref is a mutable refrence to Int32', 'nextSym_ref is a mutable refrence to Int32', 'zn_ref is a mutable refrence to Int32', 'zvec_ref is a mutable refrence to Int32', 'zj_ref is a mutable refrence to Int32', 'gSel_ref is a mutable refrence to Int32', 'gMinlen_ref is a mutable refrence to Int32', 'gLimit_idx_ref is a mutable refrence to unsigned int', 'gBase_idx_ref is a mutable refrence to unsigned int', 'gPerm_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_BZ2_decompress_29_8_2_2(Int32 * const retVal_ref, Int32 * const groupNo_ref, Int32 * const groupPos_ref, Int32 * const nextSym_ref, Int32 * const zn_ref, Int32 * const zvec_ref, Int32 * const zj_ref, Int32 * const gSel_ref, Int32 * const gMinlen_ref, unsigned int * const gLimit_idx_ref, unsigned int * const gBase_idx_ref, unsigned int * const gPerm_idx_ref, DState * const s, Int32 * const gLimit, Int32 * const gBase, Int32 * const gPerm, Int32 nSelectors)
{
  Int32 retVal = *retVal_ref;
  Int32 groupNo = *groupNo_ref;
  Int32 groupPos = *groupPos_ref;
  Int32 nextSym = *nextSym_ref;
  Int32 zn = *zn_ref;
  Int32 zvec = *zvec_ref;
  Int32 zj = *zj_ref;
  Int32 gSel = *gSel_ref;
  Int32 gMinlen = *gMinlen_ref;
  unsigned int gLimit_idx = *gLimit_idx_ref;
  unsigned int gBase_idx = *gBase_idx_ref;
  unsigned int gPerm_idx = *gPerm_idx_ref;
  if (groupPos == 0)
  {
    groupNo += 1;
    if (groupNo >= nSelectors)
    {
      retVal = -4;
      goto save_state_and_return;
    }
    ;
    ;
    groupPos = 50;
    gSel = s->selector[groupNo];
    gMinlen = s->minLens[gSel];
    gLimit_idx = &s->limit[gSel][0];
    gPerm_idx = &s->perm[gSel][0];
    gBase_idx = &s->base[gSel][0];
  }
  groupPos -= 1;
  zn = gMinlen;
  case 40:
    s->state = 40;

  while ((Bool) 1)
  {
    if (s->bsLive >= zn)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - zn)) & ((1 << zn) - 1);
      s->bsLive -= zn;
      zvec = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  while (1)
  {
    if (zn > 20)
    {
      retVal = -4;
      goto save_state_and_return;
    }
    ;
    ;
    if (zvec <= gLimit[zn + gLimit_idx])
    {
      break;
    }
    zn += 1;
    case 41:
      s->state = 41;

    while ((Bool) 1)
    {
      if (s->bsLive >= 1)
      {
        UInt32 v;
        v = (s->bsBuff >> (s->bsLive - 1)) & ((1 << 1) - 1);
        s->bsLive -= 1;
        zj = v;
        break;
      }
      if (s->strm->avail_in == 0)
      {
        retVal = 0;
        goto save_state_and_return;
      }
      ;
      ;
      s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
      s->bsLive += 8;
      s->strm->next_in += 1;
      s->strm->avail_in -= 1;
      s->strm->total_in_lo32 += 1;
      if (s->strm->total_in_lo32 == 0)
      {
        s->strm->total_in_hi32 += 1;
      }
    }

    ;
    zvec = (zvec << 1) | zj;
  }

  ;
  if (((zvec - gBase[zn + gBase_idx]) < 0) || ((zvec - gBase[zn + gBase_idx]) >= 258))
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  nextSym = gPerm[(zvec - gBase[zn + gBase_idx]) + gPerm_idx];
  *retVal_ref = retVal;
  *groupNo_ref = groupNo;
  *groupPos_ref = groupPos;
  *nextSym_ref = nextSym;
  *zn_ref = zn;
  *zvec_ref = zvec;
  *zj_ref = zj;
  *gSel_ref = gSel;
  *gMinlen_ref = gMinlen;
  *gLimit_idx_ref = gLimit_idx;
  *gBase_idx_ref = gBase_idx;
  *gPerm_idx_ref = gPerm_idx;
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
***/


// hint:  ['uc_ref is a mutable refrence to UChar']
void helper_helper_helper_helper_BZ2_decompress_29_8_2_1(UChar * const uc_ref, DState * const s, Int32 nextSym)
{
  UChar uc = *uc_ref;
  Int32 ii;
  Int32 jj;
  Int32 kk;
  Int32 pp;
  Int32 lno;
  Int32 off;
  UInt32 nn;
  nn = (UInt32) (nextSym - 1);
  if (nn < 16)
  {
    pp = s->mtfbase[0];
    uc = s->mtfa[pp + nn];
    while (nn > 3)
    {
      Int32 z = pp + nn;
      s->mtfa[z] = s->mtfa[z - 1];
      s->mtfa[z - 1] = s->mtfa[z - 2];
      s->mtfa[z - 2] = s->mtfa[z - 3];
      s->mtfa[z - 3] = s->mtfa[z - 4];
      nn -= 4;
    }

    while (nn > 0)
    {
      s->mtfa[pp + nn] = s->mtfa[(pp + nn) - 1];
      nn -= 1;
    }

    ;
    s->mtfa[pp] = uc;
  }
  else
  {
    lno = nn / 16;
    off = nn % 16;
    pp = s->mtfbase[lno] + off;
    uc = s->mtfa[pp];
    while (pp > s->mtfbase[lno])
    {
      s->mtfa[pp] = s->mtfa[pp - 1];
      pp -= 1;
    }

    ;
    s->mtfbase[lno] += 1;
    while (lno > 0)
    {
      s->mtfbase[lno] -= 1;
      s->mtfa[s->mtfbase[lno]] = s->mtfa[(s->mtfbase[lno - 1] + 16) - 1];
      lno -= 1;
    }

    s->mtfbase[0] -= 1;
    s->mtfa[s->mtfbase[0]] = uc;
    if (s->mtfbase[0] == 0)
    {
      kk = 4096 - 1;
      for (ii = (256 / 16) - 1; ii >= 0; ii -= 1)
      {
        for (jj = 16 - 1; jj >= 0; jj -= 1)
        {
          s->mtfa[kk] = s->mtfa[s->mtfbase[ii] + jj];
          kk -= 1;
        }

        s->mtfbase[ii] = kk + 1;
      }

    }
  }
  *uc_ref = uc;
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
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32', 'groupNo_ref is a mutable refrence to Int32', 'groupPos_ref is a mutable refrence to Int32', 'nextSym_ref is a mutable refrence to Int32', 'nblock_ref is a mutable refrence to Int32', 'zn_ref is a mutable refrence to Int32', 'zvec_ref is a mutable refrence to Int32', 'zj_ref is a mutable refrence to Int32', 'gSel_ref is a mutable refrence to Int32', 'gMinlen_ref is a mutable refrence to Int32', 'gLimit_idx_ref is a mutable refrence to unsigned int', 'gBase_idx_ref is a mutable refrence to unsigned int', 'gPerm_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_BZ2_decompress_29_8_2(UChar * const uc_ref, Int32 * const retVal_ref, Int32 * const groupNo_ref, Int32 * const groupPos_ref, Int32 * const nextSym_ref, Int32 * const nblock_ref, Int32 * const zn_ref, Int32 * const zvec_ref, Int32 * const zj_ref, Int32 * const gSel_ref, Int32 * const gMinlen_ref, unsigned int * const gLimit_idx_ref, unsigned int * const gBase_idx_ref, unsigned int * const gPerm_idx_ref, DState * const s, Int32 * const gLimit, Int32 * const gBase, Int32 * const gPerm, Int32 nSelectors, Int32 nblockMAX)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  Int32 groupNo = *groupNo_ref;
  Int32 groupPos = *groupPos_ref;
  Int32 nextSym = *nextSym_ref;
  Int32 nblock = *nblock_ref;
  Int32 zn = *zn_ref;
  Int32 zvec = *zvec_ref;
  Int32 zj = *zj_ref;
  Int32 gSel = *gSel_ref;
  Int32 gMinlen = *gMinlen_ref;
  unsigned int gLimit_idx = *gLimit_idx_ref;
  unsigned int gBase_idx = *gBase_idx_ref;
  unsigned int gPerm_idx = *gPerm_idx_ref;
  if (nblock >= nblockMAX)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  {
    helper_helper_helper_helper_BZ2_decompress_29_8_2_1(&uc, s, nextSym);
  }
  s->unzftab[s->seqToUnseq[uc]] += 1;
  if (s->smallDecompress)
  {
    s->ll16[nblock] = (UInt16) s->seqToUnseq[uc];
  }
  else
    s->tt[nblock] = (UInt32) s->seqToUnseq[uc];
  nblock += 1;
  {
    helper_helper_helper_helper_BZ2_decompress_29_8_2_2(&retVal, &groupNo, &groupPos, &nextSym, &zn, &zvec, &zj, &gSel, &gMinlen, &gLimit_idx, &gBase_idx, &gPerm_idx, s, gLimit, gBase, gPerm, nSelectors);
  }
  ;
  continue;
  *uc_ref = uc;
  *retVal_ref = retVal;
  *groupNo_ref = groupNo;
  *groupPos_ref = groupPos;
  *nextSym_ref = nextSym;
  *nblock_ref = nblock;
  *zn_ref = zn;
  *zvec_ref = zvec;
  *zj_ref = zj;
  *gSel_ref = gSel;
  *gMinlen_ref = gMinlen;
  *gLimit_idx_ref = gLimit_idx;
  *gBase_idx_ref = gBase_idx;
  *gPerm_idx_ref = gPerm_idx;
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
typedef char Char
----------------------------
void helper_helper_helper_helper_BZ2_decompress_29_8_2_2(Int32 * const retVal_ref, Int32 * const groupNo_ref, Int32 * const groupPos_ref, Int32 * const nextSym_ref, Int32 * const zn_ref, Int32 * const zvec_ref, Int32 * const zj_ref, Int32 * const gSel_ref, Int32 * const gMinlen_ref, unsigned int * const gLimit_idx_ref, unsigned int * const gBase_idx_ref, unsigned int * const gPerm_idx_ref, DState * const s, Int32 * const gLimit, Int32 * const gBase, Int32 * const gPerm, Int32 nSelectors)
{
  Int32 retVal = *retVal_ref;
  Int32 groupNo = *groupNo_ref;
  Int32 groupPos = *groupPos_ref;
  Int32 nextSym = *nextSym_ref;
  Int32 zn = *zn_ref;
  Int32 zvec = *zvec_ref;
  Int32 zj = *zj_ref;
  Int32 gSel = *gSel_ref;
  Int32 gMinlen = *gMinlen_ref;
  unsigned int gLimit_idx = *gLimit_idx_ref;
  unsigned int gBase_idx = *gBase_idx_ref;
  unsigned int gPerm_idx = *gPerm_idx_ref;
  if (groupPos == 0)
  {
    groupNo += 1;
    if (groupNo >= nSelectors)
    {
      retVal = -4;
      goto save_state_and_return;
    }
    ;
    ;
    groupPos = 50;
    gSel = s->selector[groupNo];
    gMinlen = s->minLens[gSel];
    gLimit_idx = &s->limit[gSel][0];
    gPerm_idx = &s->perm[gSel][0];
    gBase_idx = &s->base[gSel][0];
  }
  groupPos -= 1;
  zn = gMinlen;
  case 40:
    s->state = 40;

  while ((Bool) 1)
  {
    if (s->bsLive >= zn)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - zn)) & ((1 << zn) - 1);
      s->bsLive -= zn;
      zvec = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  while (1)
  {
    if (zn > 20)
    {
      retVal = -4;
      goto save_state_and_return;
    }
    ;
    ;
    if (zvec <= gLimit[zn + gLimit_idx])
    {
      break;
    }
    zn += 1;
    case 41:
      s->state = 41;

    while ((Bool) 1)
    {
      if (s->bsLive >= 1)
      {
        UInt32 v;
        v = (s->bsBuff >> (s->bsLive - 1)) & ((1 << 1) - 1);
        s->bsLive -= 1;
        zj = v;
        break;
      }
      if (s->strm->avail_in == 0)
      {
        retVal = 0;
        goto save_state_and_return;
      }
      ;
      ;
      s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
      s->bsLive += 8;
      s->strm->next_in += 1;
      s->strm->avail_in -= 1;
      s->strm->total_in_lo32 += 1;
      if (s->strm->total_in_lo32 == 0)
      {
        s->strm->total_in_hi32 += 1;
      }
    }

    ;
    zvec = (zvec << 1) | zj;
  }

  ;
  if (((zvec - gBase[zn + gBase_idx]) < 0) || ((zvec - gBase[zn + gBase_idx]) >= 258))
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  nextSym = gPerm[(zvec - gBase[zn + gBase_idx]) + gPerm_idx];
  *retVal_ref = retVal;
  *groupNo_ref = groupNo;
  *groupPos_ref = groupPos;
  *nextSym_ref = nextSym;
  *zn_ref = zn;
  *zvec_ref = zvec;
  *zj_ref = zj;
  *gSel_ref = gSel;
  *gMinlen_ref = gMinlen;
  *gLimit_idx_ref = gLimit_idx;
  *gBase_idx_ref = gBase_idx;
  *gPerm_idx_ref = gPerm_idx;
}


----------------------------
void helper_helper_helper_helper_BZ2_decompress_29_8_2_1(UChar * const uc_ref, DState * const s, Int32 nextSym)
{
  UChar uc = *uc_ref;
  Int32 ii;
  Int32 jj;
  Int32 kk;
  Int32 pp;
  Int32 lno;
  Int32 off;
  UInt32 nn;
  nn = (UInt32) (nextSym - 1);
  if (nn < 16)
  {
    pp = s->mtfbase[0];
    uc = s->mtfa[pp + nn];
    while (nn > 3)
    {
      Int32 z = pp + nn;
      s->mtfa[z] = s->mtfa[z - 1];
      s->mtfa[z - 1] = s->mtfa[z - 2];
      s->mtfa[z - 2] = s->mtfa[z - 3];
      s->mtfa[z - 3] = s->mtfa[z - 4];
      nn -= 4;
    }

    while (nn > 0)
    {
      s->mtfa[pp + nn] = s->mtfa[(pp + nn) - 1];
      nn -= 1;
    }

    ;
    s->mtfa[pp] = uc;
  }
  else
  {
    lno = nn / 16;
    off = nn % 16;
    pp = s->mtfbase[lno] + off;
    uc = s->mtfa[pp];
    while (pp > s->mtfbase[lno])
    {
      s->mtfa[pp] = s->mtfa[pp - 1];
      pp -= 1;
    }

    ;
    s->mtfbase[lno] += 1;
    while (lno > 0)
    {
      s->mtfbase[lno] -= 1;
      s->mtfa[s->mtfbase[lno]] = s->mtfa[(s->mtfbase[lno - 1] + 16) - 1];
      lno -= 1;
    }

    s->mtfbase[0] -= 1;
    s->mtfa[s->mtfbase[0]] = uc;
    if (s->mtfbase[0] == 0)
    {
      kk = 4096 - 1;
      for (ii = (256 / 16) - 1; ii >= 0; ii -= 1)
      {
        for (jj = 16 - 1; jj >= 0; jj -= 1)
        {
          s->mtfa[kk] = s->mtfa[s->mtfbase[ii] + jj];
          kk -= 1;
        }

        s->mtfbase[ii] = kk + 1;
      }

    }
  }
  *uc_ref = uc;
}


----------------------------
typedef unsigned char UChar
----------------------------
***/


// hint:  ['retVal_ref is a mutable refrence to Int32', 'groupNo_ref is a mutable refrence to Int32', 'groupPos_ref is a mutable refrence to Int32', 'nextSym_ref is a mutable refrence to Int32', 'es_ref is a mutable refrence to Int32', 'N_ref is a mutable refrence to Int32', 'zn_ref is a mutable refrence to Int32', 'zvec_ref is a mutable refrence to Int32', 'zj_ref is a mutable refrence to Int32', 'gSel_ref is a mutable refrence to Int32', 'gMinlen_ref is a mutable refrence to Int32', 'gLimit_idx_ref is a mutable refrence to unsigned int', 'gBase_idx_ref is a mutable refrence to unsigned int', 'gPerm_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_BZ2_decompress_29_8_1_1(Int32 * const retVal_ref, Int32 * const groupNo_ref, Int32 * const groupPos_ref, Int32 * const nextSym_ref, Int32 * const es_ref, Int32 * const N_ref, Int32 * const zn_ref, Int32 * const zvec_ref, Int32 * const zj_ref, Int32 * const gSel_ref, Int32 * const gMinlen_ref, unsigned int * const gLimit_idx_ref, unsigned int * const gBase_idx_ref, unsigned int * const gPerm_idx_ref, DState * const s, Int32 * const gLimit, Int32 * const gBase, Int32 * const gPerm, Int32 nSelectors)
{
  Int32 retVal = *retVal_ref;
  Int32 groupNo = *groupNo_ref;
  Int32 groupPos = *groupPos_ref;
  Int32 nextSym = *nextSym_ref;
  Int32 es = *es_ref;
  Int32 N = *N_ref;
  Int32 zn = *zn_ref;
  Int32 zvec = *zvec_ref;
  Int32 zj = *zj_ref;
  Int32 gSel = *gSel_ref;
  Int32 gMinlen = *gMinlen_ref;
  unsigned int gLimit_idx = *gLimit_idx_ref;
  unsigned int gBase_idx = *gBase_idx_ref;
  unsigned int gPerm_idx = *gPerm_idx_ref;
  if (N >= ((2 * 1024) * 1024))
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  if (nextSym == 0)
  {
    es = es + ((0 + 1) * N);
  }
  else
    if (nextSym == 1)
  {
    es = es + ((1 + 1) * N);
  }
  N = N * 2;
  {
    if (groupPos == 0)
    {
      groupNo += 1;
      if (groupNo >= nSelectors)
      {
        retVal = -4;
        goto save_state_and_return;
      }
      ;
      ;
      groupPos = 50;
      gSel = s->selector[groupNo];
      gMinlen = s->minLens[gSel];
      gLimit_idx = &s->limit[gSel][0];
      gPerm_idx = &s->perm[gSel][0];
      gBase_idx = &s->base[gSel][0];
    }
    groupPos -= 1;
    zn = gMinlen;
    case 38:
      s->state = 38;

    while ((Bool) 1)
    {
      if (s->bsLive >= zn)
      {
        UInt32 v;
        v = (s->bsBuff >> (s->bsLive - zn)) & ((1 << zn) - 1);
        s->bsLive -= zn;
        zvec = v;
        break;
      }
      if (s->strm->avail_in == 0)
      {
        retVal = 0;
        goto save_state_and_return;
      }
      ;
      ;
      s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
      s->bsLive += 8;
      s->strm->next_in += 1;
      s->strm->avail_in -= 1;
      s->strm->total_in_lo32 += 1;
      if (s->strm->total_in_lo32 == 0)
      {
        s->strm->total_in_hi32 += 1;
      }
    }

    ;
    while (1)
    {
      if (zn > 20)
      {
        retVal = -4;
        goto save_state_and_return;
      }
      ;
      ;
      if (zvec <= gLimit[zn + gLimit_idx])
      {
        break;
      }
      zn += 1;
      case 39:
        s->state = 39;

      while ((Bool) 1)
      {
        if (s->bsLive >= 1)
        {
          UInt32 v;
          v = (s->bsBuff >> (s->bsLive - 1)) & ((1 << 1) - 1);
          s->bsLive -= 1;
          zj = v;
          break;
        }
        if (s->strm->avail_in == 0)
        {
          retVal = 0;
          goto save_state_and_return;
        }
        ;
        ;
        s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
        s->bsLive += 8;
        s->strm->next_in += 1;
        s->strm->avail_in -= 1;
        s->strm->total_in_lo32 += 1;
        if (s->strm->total_in_lo32 == 0)
        {
          s->strm->total_in_hi32 += 1;
        }
      }

      ;
      zvec = (zvec << 1) | zj;
    }

    ;
    if (((zvec - gBase[zn + gBase_idx]) < 0) || ((zvec - gBase[zn + gBase_idx]) >= 258))
    {
      retVal = -4;
      goto save_state_and_return;
    }
    ;
    ;
    nextSym = gPerm[(zvec - gBase[zn + gBase_idx]) + gPerm_idx];
  }
  ;
  *retVal_ref = retVal;
  *groupNo_ref = groupNo;
  *groupPos_ref = groupPos;
  *nextSym_ref = nextSym;
  *es_ref = es;
  *N_ref = N;
  *zn_ref = zn;
  *zvec_ref = zvec;
  *zj_ref = zj;
  *gSel_ref = gSel;
  *gMinlen_ref = gMinlen;
  *gLimit_idx_ref = gLimit_idx;
  *gBase_idx_ref = gBase_idx;
  *gPerm_idx_ref = gPerm_idx;
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
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32', 'groupNo_ref is a mutable refrence to Int32', 'groupPos_ref is a mutable refrence to Int32', 'nextSym_ref is a mutable refrence to Int32', 'nblock_ref is a mutable refrence to Int32', 'es_ref is a mutable refrence to Int32', 'N_ref is a mutable refrence to Int32', 'zn_ref is a mutable refrence to Int32', 'zvec_ref is a mutable refrence to Int32', 'zj_ref is a mutable refrence to Int32', 'gSel_ref is a mutable refrence to Int32', 'gMinlen_ref is a mutable refrence to Int32', 'gLimit_idx_ref is a mutable refrence to unsigned int', 'gBase_idx_ref is a mutable refrence to unsigned int', 'gPerm_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_BZ2_decompress_29_8_1(UChar * const uc_ref, Int32 * const retVal_ref, Int32 * const groupNo_ref, Int32 * const groupPos_ref, Int32 * const nextSym_ref, Int32 * const nblock_ref, Int32 * const es_ref, Int32 * const N_ref, Int32 * const zn_ref, Int32 * const zvec_ref, Int32 * const zj_ref, Int32 * const gSel_ref, Int32 * const gMinlen_ref, unsigned int * const gLimit_idx_ref, unsigned int * const gBase_idx_ref, unsigned int * const gPerm_idx_ref, DState * const s, Int32 * const gLimit, Int32 * const gBase, Int32 * const gPerm, Int32 nSelectors, Int32 nblockMAX)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  Int32 groupNo = *groupNo_ref;
  Int32 groupPos = *groupPos_ref;
  Int32 nextSym = *nextSym_ref;
  Int32 nblock = *nblock_ref;
  Int32 es = *es_ref;
  Int32 N = *N_ref;
  Int32 zn = *zn_ref;
  Int32 zvec = *zvec_ref;
  Int32 zj = *zj_ref;
  Int32 gSel = *gSel_ref;
  Int32 gMinlen = *gMinlen_ref;
  unsigned int gLimit_idx = *gLimit_idx_ref;
  unsigned int gBase_idx = *gBase_idx_ref;
  unsigned int gPerm_idx = *gPerm_idx_ref;
  es = -1;
  N = 1;
  do
  {
    helper_helper_helper_helper_BZ2_decompress_29_8_1_1(&retVal, &groupNo, &groupPos, &nextSym, &es, &N, &zn, &zvec, &zj, &gSel, &gMinlen, &gLimit_idx, &gBase_idx, &gPerm_idx, s, gLimit, gBase, gPerm, nSelectors);
  }
  while ((nextSym == 0) || (nextSym == 1));
  es += 1;
  uc = s->seqToUnseq[s->mtfa[s->mtfbase[0]]];
  s->unzftab[uc] += es;
  if (s->smallDecompress)
  {
    while (es > 0)
    {
      if (nblock >= nblockMAX)
      {
        retVal = -4;
        goto save_state_and_return;
      }
      ;
      ;
      s->ll16[nblock] = (UInt16) uc;
      nblock += 1;
      es -= 1;
    }

  }
  else
    while (es > 0)
  {
    if (nblock >= nblockMAX)
    {
      retVal = -4;
      goto save_state_and_return;
    }
    ;
    ;
    s->tt[nblock] = (UInt32) uc;
    nblock += 1;
    es -= 1;
  }

  ;
  continue;
  *uc_ref = uc;
  *retVal_ref = retVal;
  *groupNo_ref = groupNo;
  *groupPos_ref = groupPos;
  *nextSym_ref = nextSym;
  *nblock_ref = nblock;
  *es_ref = es;
  *N_ref = N;
  *zn_ref = zn;
  *zvec_ref = zvec;
  *zj_ref = zj;
  *gSel_ref = gSel;
  *gMinlen_ref = gMinlen;
  *gLimit_idx_ref = gLimit_idx;
  *gBase_idx_ref = gBase_idx;
  *gPerm_idx_ref = gPerm_idx;
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
void helper_helper_helper_helper_BZ2_decompress_29_8_1_1(Int32 * const retVal_ref, Int32 * const groupNo_ref, Int32 * const groupPos_ref, Int32 * const nextSym_ref, Int32 * const es_ref, Int32 * const N_ref, Int32 * const zn_ref, Int32 * const zvec_ref, Int32 * const zj_ref, Int32 * const gSel_ref, Int32 * const gMinlen_ref, unsigned int * const gLimit_idx_ref, unsigned int * const gBase_idx_ref, unsigned int * const gPerm_idx_ref, DState * const s, Int32 * const gLimit, Int32 * const gBase, Int32 * const gPerm, Int32 nSelectors)
{
  Int32 retVal = *retVal_ref;
  Int32 groupNo = *groupNo_ref;
  Int32 groupPos = *groupPos_ref;
  Int32 nextSym = *nextSym_ref;
  Int32 es = *es_ref;
  Int32 N = *N_ref;
  Int32 zn = *zn_ref;
  Int32 zvec = *zvec_ref;
  Int32 zj = *zj_ref;
  Int32 gSel = *gSel_ref;
  Int32 gMinlen = *gMinlen_ref;
  unsigned int gLimit_idx = *gLimit_idx_ref;
  unsigned int gBase_idx = *gBase_idx_ref;
  unsigned int gPerm_idx = *gPerm_idx_ref;
  if (N >= ((2 * 1024) * 1024))
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  if (nextSym == 0)
  {
    es = es + ((0 + 1) * N);
  }
  else
    if (nextSym == 1)
  {
    es = es + ((1 + 1) * N);
  }
  N = N * 2;
  {
    if (groupPos == 0)
    {
      groupNo += 1;
      if (groupNo >= nSelectors)
      {
        retVal = -4;
        goto save_state_and_return;
      }
      ;
      ;
      groupPos = 50;
      gSel = s->selector[groupNo];
      gMinlen = s->minLens[gSel];
      gLimit_idx = &s->limit[gSel][0];
      gPerm_idx = &s->perm[gSel][0];
      gBase_idx = &s->base[gSel][0];
    }
    groupPos -= 1;
    zn = gMinlen;
    case 38:
      s->state = 38;

    while ((Bool) 1)
    {
      if (s->bsLive >= zn)
      {
        UInt32 v;
        v = (s->bsBuff >> (s->bsLive - zn)) & ((1 << zn) - 1);
        s->bsLive -= zn;
        zvec = v;
        break;
      }
      if (s->strm->avail_in == 0)
      {
        retVal = 0;
        goto save_state_and_return;
      }
      ;
      ;
      s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
      s->bsLive += 8;
      s->strm->next_in += 1;
      s->strm->avail_in -= 1;
      s->strm->total_in_lo32 += 1;
      if (s->strm->total_in_lo32 == 0)
      {
        s->strm->total_in_hi32 += 1;
      }
    }

    ;
    while (1)
    {
      if (zn > 20)
      {
        retVal = -4;
        goto save_state_and_return;
      }
      ;
      ;
      if (zvec <= gLimit[zn + gLimit_idx])
      {
        break;
      }
      zn += 1;
      case 39:
        s->state = 39;

      while ((Bool) 1)
      {
        if (s->bsLive >= 1)
        {
          UInt32 v;
          v = (s->bsBuff >> (s->bsLive - 1)) & ((1 << 1) - 1);
          s->bsLive -= 1;
          zj = v;
          break;
        }
        if (s->strm->avail_in == 0)
        {
          retVal = 0;
          goto save_state_and_return;
        }
        ;
        ;
        s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
        s->bsLive += 8;
        s->strm->next_in += 1;
        s->strm->avail_in -= 1;
        s->strm->total_in_lo32 += 1;
        if (s->strm->total_in_lo32 == 0)
        {
          s->strm->total_in_hi32 += 1;
        }
      }

      ;
      zvec = (zvec << 1) | zj;
    }

    ;
    if (((zvec - gBase[zn + gBase_idx]) < 0) || ((zvec - gBase[zn + gBase_idx]) >= 258))
    {
      retVal = -4;
      goto save_state_and_return;
    }
    ;
    ;
    nextSym = gPerm[(zvec - gBase[zn + gBase_idx]) + gPerm_idx];
  }
  ;
  *retVal_ref = retVal;
  *groupNo_ref = groupNo;
  *groupPos_ref = groupPos;
  *nextSym_ref = nextSym;
  *es_ref = es;
  *N_ref = N;
  *zn_ref = zn;
  *zvec_ref = zvec;
  *zj_ref = zj;
  *gSel_ref = gSel;
  *gMinlen_ref = gMinlen;
  *gLimit_idx_ref = gLimit_idx;
  *gBase_idx_ref = gBase_idx;
  *gPerm_idx_ref = gPerm_idx;
}


----------------------------
typedef char Char
----------------------------
typedef unsigned char UChar
----------------------------
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32', 'groupNo_ref is a mutable refrence to Int32', 'groupPos_ref is a mutable refrence to Int32', 'nextSym_ref is a mutable refrence to Int32', 'nblock_ref is a mutable refrence to Int32', 'es_ref is a mutable refrence to Int32', 'N_ref is a mutable refrence to Int32', 'zn_ref is a mutable refrence to Int32', 'zvec_ref is a mutable refrence to Int32', 'zj_ref is a mutable refrence to Int32', 'gSel_ref is a mutable refrence to Int32', 'gMinlen_ref is a mutable refrence to Int32', 'gLimit_idx_ref is a mutable refrence to unsigned int', 'gBase_idx_ref is a mutable refrence to unsigned int', 'gPerm_idx_ref is a mutable refrence to unsigned int']
void helper_helper_BZ2_decompress_29_8(UChar * const uc_ref, Int32 * const retVal_ref, Int32 * const groupNo_ref, Int32 * const groupPos_ref, Int32 * const nextSym_ref, Int32 * const nblock_ref, Int32 * const es_ref, Int32 * const N_ref, Int32 * const zn_ref, Int32 * const zvec_ref, Int32 * const zj_ref, Int32 * const gSel_ref, Int32 * const gMinlen_ref, unsigned int * const gLimit_idx_ref, unsigned int * const gBase_idx_ref, unsigned int * const gPerm_idx_ref, DState * const s, Int32 * const gLimit, Int32 * const gBase, Int32 * const gPerm, Int32 nSelectors, Int32 EOB, Int32 nblockMAX)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  Int32 groupNo = *groupNo_ref;
  Int32 groupPos = *groupPos_ref;
  Int32 nextSym = *nextSym_ref;
  Int32 nblock = *nblock_ref;
  Int32 es = *es_ref;
  Int32 N = *N_ref;
  Int32 zn = *zn_ref;
  Int32 zvec = *zvec_ref;
  Int32 zj = *zj_ref;
  Int32 gSel = *gSel_ref;
  Int32 gMinlen = *gMinlen_ref;
  unsigned int gLimit_idx = *gLimit_idx_ref;
  unsigned int gBase_idx = *gBase_idx_ref;
  unsigned int gPerm_idx = *gPerm_idx_ref;
  if (nextSym == EOB)
  {
    break;
  }
  if ((nextSym == 0) || (nextSym == 1))
  {
    helper_helper_helper_BZ2_decompress_29_8_1(&uc, &retVal, &groupNo, &groupPos, &nextSym, &nblock, &es, &N, &zn, &zvec, &zj, &gSel, &gMinlen, &gLimit_idx, &gBase_idx, &gPerm_idx, s, gLimit, gBase, gPerm, nSelectors, nblockMAX);
  }
  else
  {
    helper_helper_helper_BZ2_decompress_29_8_2(&uc, &retVal, &groupNo, &groupPos, &nextSym, &nblock, &zn, &zvec, &zj, &gSel, &gMinlen, &gLimit_idx, &gBase_idx, &gPerm_idx, s, gLimit, gBase, gPerm, nSelectors, nblockMAX);
  }
  *uc_ref = uc;
  *retVal_ref = retVal;
  *groupNo_ref = groupNo;
  *groupPos_ref = groupPos;
  *nextSym_ref = nextSym;
  *nblock_ref = nblock;
  *es_ref = es;
  *N_ref = N;
  *zn_ref = zn;
  *zvec_ref = zvec;
  *zj_ref = zj;
  *gSel_ref = gSel;
  *gMinlen_ref = gMinlen;
  *gLimit_idx_ref = gLimit_idx;
  *gBase_idx_ref = gBase_idx;
  *gPerm_idx_ref = gPerm_idx;
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
void helper_helper_helper_BZ2_decompress_29_8_2(UChar * const uc_ref, Int32 * const retVal_ref, Int32 * const groupNo_ref, Int32 * const groupPos_ref, Int32 * const nextSym_ref, Int32 * const nblock_ref, Int32 * const zn_ref, Int32 * const zvec_ref, Int32 * const zj_ref, Int32 * const gSel_ref, Int32 * const gMinlen_ref, unsigned int * const gLimit_idx_ref, unsigned int * const gBase_idx_ref, unsigned int * const gPerm_idx_ref, DState * const s, Int32 * const gLimit, Int32 * const gBase, Int32 * const gPerm, Int32 nSelectors, Int32 nblockMAX)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  Int32 groupNo = *groupNo_ref;
  Int32 groupPos = *groupPos_ref;
  Int32 nextSym = *nextSym_ref;
  Int32 nblock = *nblock_ref;
  Int32 zn = *zn_ref;
  Int32 zvec = *zvec_ref;
  Int32 zj = *zj_ref;
  Int32 gSel = *gSel_ref;
  Int32 gMinlen = *gMinlen_ref;
  unsigned int gLimit_idx = *gLimit_idx_ref;
  unsigned int gBase_idx = *gBase_idx_ref;
  unsigned int gPerm_idx = *gPerm_idx_ref;
  if (nblock >= nblockMAX)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  {
    helper_helper_helper_helper_BZ2_decompress_29_8_2_1(&uc, s, nextSym);
  }
  s->unzftab[s->seqToUnseq[uc]] += 1;
  if (s->smallDecompress)
  {
    s->ll16[nblock] = (UInt16) s->seqToUnseq[uc];
  }
  else
    s->tt[nblock] = (UInt32) s->seqToUnseq[uc];
  nblock += 1;
  {
    helper_helper_helper_helper_BZ2_decompress_29_8_2_2(&retVal, &groupNo, &groupPos, &nextSym, &zn, &zvec, &zj, &gSel, &gMinlen, &gLimit_idx, &gBase_idx, &gPerm_idx, s, gLimit, gBase, gPerm, nSelectors);
  }
  ;
  continue;
  *uc_ref = uc;
  *retVal_ref = retVal;
  *groupNo_ref = groupNo;
  *groupPos_ref = groupPos;
  *nextSym_ref = nextSym;
  *nblock_ref = nblock;
  *zn_ref = zn;
  *zvec_ref = zvec;
  *zj_ref = zj;
  *gSel_ref = gSel;
  *gMinlen_ref = gMinlen;
  *gLimit_idx_ref = gLimit_idx;
  *gBase_idx_ref = gBase_idx;
  *gPerm_idx_ref = gPerm_idx;
}


----------------------------
typedef char Char
----------------------------
void helper_helper_helper_BZ2_decompress_29_8_1(UChar * const uc_ref, Int32 * const retVal_ref, Int32 * const groupNo_ref, Int32 * const groupPos_ref, Int32 * const nextSym_ref, Int32 * const nblock_ref, Int32 * const es_ref, Int32 * const N_ref, Int32 * const zn_ref, Int32 * const zvec_ref, Int32 * const zj_ref, Int32 * const gSel_ref, Int32 * const gMinlen_ref, unsigned int * const gLimit_idx_ref, unsigned int * const gBase_idx_ref, unsigned int * const gPerm_idx_ref, DState * const s, Int32 * const gLimit, Int32 * const gBase, Int32 * const gPerm, Int32 nSelectors, Int32 nblockMAX)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  Int32 groupNo = *groupNo_ref;
  Int32 groupPos = *groupPos_ref;
  Int32 nextSym = *nextSym_ref;
  Int32 nblock = *nblock_ref;
  Int32 es = *es_ref;
  Int32 N = *N_ref;
  Int32 zn = *zn_ref;
  Int32 zvec = *zvec_ref;
  Int32 zj = *zj_ref;
  Int32 gSel = *gSel_ref;
  Int32 gMinlen = *gMinlen_ref;
  unsigned int gLimit_idx = *gLimit_idx_ref;
  unsigned int gBase_idx = *gBase_idx_ref;
  unsigned int gPerm_idx = *gPerm_idx_ref;
  es = -1;
  N = 1;
  do
  {
    helper_helper_helper_helper_BZ2_decompress_29_8_1_1(&retVal, &groupNo, &groupPos, &nextSym, &es, &N, &zn, &zvec, &zj, &gSel, &gMinlen, &gLimit_idx, &gBase_idx, &gPerm_idx, s, gLimit, gBase, gPerm, nSelectors);
  }
  while ((nextSym == 0) || (nextSym == 1));
  es += 1;
  uc = s->seqToUnseq[s->mtfa[s->mtfbase[0]]];
  s->unzftab[uc] += es;
  if (s->smallDecompress)
  {
    while (es > 0)
    {
      if (nblock >= nblockMAX)
      {
        retVal = -4;
        goto save_state_and_return;
      }
      ;
      ;
      s->ll16[nblock] = (UInt16) uc;
      nblock += 1;
      es -= 1;
    }

  }
  else
    while (es > 0)
  {
    if (nblock >= nblockMAX)
    {
      retVal = -4;
      goto save_state_and_return;
    }
    ;
    ;
    s->tt[nblock] = (UInt32) uc;
    nblock += 1;
    es -= 1;
  }

  ;
  continue;
  *uc_ref = uc;
  *retVal_ref = retVal;
  *groupNo_ref = groupNo;
  *groupPos_ref = groupPos;
  *nextSym_ref = nextSym;
  *nblock_ref = nblock;
  *es_ref = es;
  *N_ref = N;
  *zn_ref = zn;
  *zvec_ref = zvec;
  *zj_ref = zj;
  *gSel_ref = gSel;
  *gMinlen_ref = gMinlen;
  *gLimit_idx_ref = gLimit_idx;
  *gBase_idx_ref = gBase_idx;
  *gPerm_idx_ref = gPerm_idx;
}


----------------------------
typedef unsigned char UChar
----------------------------
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'i_ref is a mutable refrence to Int32']
Int32 helper_helper_BZ2_decompress_29_3(UChar * const uc_ref, Int32 * const i_ref, DState * const s, Int32 nblock)
{
  UChar uc = *uc_ref;
  Int32 i = *i_ref;
  for (i = 0; i < nblock; i += 1)
  {
    uc = (UChar) (s->tt[i] & 0xff);
    s->tt[s->cftab[uc]] |= i << 8;
    s->cftab[uc] += 1;
  }

  s->tPos = s->tt[s->origPtr] >> 8;
  s->nblock_used = 0;
  if (s->blockRandomised)
  {
    s->rNToGo = 0;
    s->rTPos = 0;
    if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
    {
      return (Bool) 1;
    }
    s->tPos = s->tt[s->tPos];
    s->k0 = (UChar) (s->tPos & 0xff);
    s->tPos >>= 8;
    ;
    s->nblock_used += 1;
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
  }
  else
  {
    if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
    {
      return (Bool) 1;
    }
    s->tPos = s->tt[s->tPos];
    s->k0 = (UChar) (s->tPos & 0xff);
    s->tPos >>= 8;
    ;
    s->nblock_used += 1;
  }
  *uc_ref = uc;
  *i_ref = i;
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
typedef char Char
----------------------------
typedef unsigned char UChar
----------------------------
extern Int32 BZ2_rNums[512]
----------------------------
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32']
void helper_helper_BZ2_decompress_29_2(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  if (s->bsLive >= 8)
  {
    UInt32 v;
    v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
    s->bsLive -= 8;
    uc = v;
    break;
  }
  if (s->strm->avail_in == 0)
  {
    retVal = 0;
    goto save_state_and_return;
  }
  ;
  ;
  s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
  s->bsLive += 8;
  s->strm->next_in += 1;
  s->strm->avail_in -= 1;
  s->strm->total_in_lo32 += 1;
  if (s->strm->total_in_lo32 == 0)
  {
    s->strm->total_in_hi32 += 1;
  }
  *uc_ref = uc;
  *retVal_ref = retVal;
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
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32', 'j_ref is a mutable refrence to Int32']
void helper_helper_helper_BZ2_decompress_29_4_1(UChar * const uc_ref, Int32 * const retVal_ref, Int32 * const j_ref, DState * const s, Int32 nGroups)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  Int32 j = *j_ref;
  case 32:
    s->state = 32;

  while ((Bool) 1)
  {
    if (s->bsLive >= 1)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 1)) & ((1 << 1) - 1);
      s->bsLive -= 1;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if (uc == 0)
  {
    break;
  }
  j += 1;
  if (j >= nGroups)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  *uc_ref = uc;
  *retVal_ref = retVal;
  *j_ref = j;
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
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32', 'i_ref is a mutable refrence to Int32', 'j_ref is a mutable refrence to Int32']
void helper_helper_BZ2_decompress_29_4(UChar * const uc_ref, Int32 * const retVal_ref, Int32 * const i_ref, Int32 * const j_ref, DState * const s, Int32 nGroups)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  Int32 i = *i_ref;
  Int32 j = *j_ref;
  j = 0;
  while ((Bool) 1)
  {
    helper_helper_helper_BZ2_decompress_29_4_1(&uc, &retVal, &j, s, nGroups);
  }

  if (i < (2 + (900000 / 50)))
  {
    s->selectorMtf[i] = j;
  }
  *uc_ref = uc;
  *retVal_ref = retVal;
  *i_ref = i;
  *j_ref = j;
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
typedef char Char
----------------------------
typedef unsigned char UChar
----------------------------
void helper_helper_helper_BZ2_decompress_29_4_1(UChar * const uc_ref, Int32 * const retVal_ref, Int32 * const j_ref, DState * const s, Int32 nGroups)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  Int32 j = *j_ref;
  case 32:
    s->state = 32;

  while ((Bool) 1)
  {
    if (s->bsLive >= 1)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 1)) & ((1 << 1) - 1);
      s->bsLive -= 1;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if (uc == 0)
  {
    break;
  }
  j += 1;
  if (j >= nGroups)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  *uc_ref = uc;
  *retVal_ref = retVal;
  *j_ref = j;
}


----------------------------
***/


Int32 helper_helper_helper_BZ2_decompress_29_5_1(DState * const s)
{
  s->rNToGo = 0;
  s->rTPos = 0;
  if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
  {
    return (Bool) 1;
  }
  s->k0 = BZ2_indexIntoF(s->tPos, s->cftab);
  s->tPos = ((UInt32) s->ll16[s->tPos]) | (((((UInt32) s->ll4[s->tPos >> 1]) >> ((s->tPos << 2) & 0x4)) & 0xF) << 16);
  ;
  s->nblock_used += 1;
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
}


/*** DEPENDENCIES:
extern Int32 BZ2_rNums[512]
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


// hint:  ['uc_ref is a mutable refrence to UChar', 'i_ref is a mutable refrence to Int32', 'j_ref is a mutable refrence to Int32']
Int32 helper_helper_BZ2_decompress_29_5(UChar * const uc_ref, Int32 * const i_ref, Int32 * const j_ref, DState * const s, Int32 nblock)
{
  UChar uc = *uc_ref;
  Int32 i = *i_ref;
  Int32 j = *j_ref;
  for (i = 0; i <= 256; i += 1)
    s->cftabCopy[i] = s->cftab[i];

  for (i = 0; i < nblock; i += 1)
  {
    uc = (UChar) s->ll16[i];
    {
      s->ll16[i] = (UInt16) (s->cftabCopy[uc] & 0x0000ffff);
      {
        if ((i & 0x1) == 0)
        {
          s->ll4[i >> 1] = (s->ll4[i >> 1] & 0xf0) | (s->cftabCopy[uc] >> 16);
        }
        else
          s->ll4[i >> 1] = (s->ll4[i >> 1] & 0x0f) | ((s->cftabCopy[uc] >> 16) << 4);
      }
      ;
    }
    ;
    s->cftabCopy[uc] += 1;
  }

  i = s->origPtr;
  j = ((UInt32) s->ll16[i]) | (((((UInt32) s->ll4[i >> 1]) >> ((i << 2) & 0x4)) & 0xF) << 16);
  do
  {
    Int32 tmp = ((UInt32) s->ll16[j]) | (((((UInt32) s->ll4[j >> 1]) >> ((j << 2) & 0x4)) & 0xF) << 16);
    {
      s->ll16[j] = (UInt16) (i & 0x0000ffff);
      {
        if ((j & 0x1) == 0)
        {
          s->ll4[j >> 1] = (s->ll4[j >> 1] & 0xf0) | (i >> 16);
        }
        else
          s->ll4[j >> 1] = (s->ll4[j >> 1] & 0x0f) | ((i >> 16) << 4);
      }
      ;
    }
    ;
    i = j;
    j = tmp;
  }
  while (i != s->origPtr);
  s->tPos = s->origPtr;
  s->nblock_used = 0;
  if (s->blockRandomised)
  {
    helper_helper_helper_BZ2_decompress_29_5_1(s);
  }
  else
  {
    if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
    {
      return (Bool) 1;
    }
    s->k0 = BZ2_indexIntoF(s->tPos, s->cftab);
    s->tPos = ((UInt32) s->ll16[s->tPos]) | (((((UInt32) s->ll4[s->tPos >> 1]) >> ((s->tPos << 2) & 0x4)) & 0xF) << 16);
    ;
    s->nblock_used += 1;
  }
  *uc_ref = uc;
  *i_ref = i;
  *j_ref = j;
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
Int32 helper_helper_helper_BZ2_decompress_29_5_1(DState * const s)
{
  s->rNToGo = 0;
  s->rTPos = 0;
  if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
  {
    return (Bool) 1;
  }
  s->k0 = BZ2_indexIntoF(s->tPos, s->cftab);
  s->tPos = ((UInt32) s->ll16[s->tPos]) | (((((UInt32) s->ll4[s->tPos >> 1]) >> ((s->tPos << 2) & 0x4)) & 0xF) << 16);
  ;
  s->nblock_used += 1;
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
}


----------------------------
typedef char Char
----------------------------
typedef unsigned char UChar
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


// hint:  ['retVal_ref is a mutable refrence to Int32', 'curr_ref is a mutable refrence to Int32']
void helper_helper_helper_BZ2_decompress_29_7_1(Int32 * const retVal_ref, Int32 * const curr_ref, DState * const s)
{
  Int32 retVal = *retVal_ref;
  Int32 curr = *curr_ref;
  if (s->bsLive >= 5)
  {
    UInt32 v;
    v = (s->bsBuff >> (s->bsLive - 5)) & ((1 << 5) - 1);
    s->bsLive -= 5;
    curr = v;
    break;
  }
  if (s->strm->avail_in == 0)
  {
    retVal = 0;
    goto save_state_and_return;
  }
  ;
  ;
  s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
  s->bsLive += 8;
  s->strm->next_in += 1;
  s->strm->avail_in -= 1;
  s->strm->total_in_lo32 += 1;
  if (s->strm->total_in_lo32 == 0)
  {
    s->strm->total_in_hi32 += 1;
  }
  *retVal_ref = retVal;
  *curr_ref = curr;
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
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32', 'curr_ref is a mutable refrence to Int32']
void helper_helper_helper_helper_BZ2_decompress_29_7_2_1(UChar * const uc_ref, Int32 * const retVal_ref, Int32 * const curr_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  Int32 curr = *curr_ref;
  if ((curr < 1) || (curr > 20))
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  case 34:
    s->state = 34;

  while ((Bool) 1)
  {
    if (s->bsLive >= 1)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 1)) & ((1 << 1) - 1);
      s->bsLive -= 1;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if (uc == 0)
  {
    break;
  }
  case 35:
    s->state = 35;

  while ((Bool) 1)
  {
    if (s->bsLive >= 1)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 1)) & ((1 << 1) - 1);
      s->bsLive -= 1;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if (uc == 0)
  {
    curr += 1;
  }
  else
    curr--;
  curr -= 1;
  *uc_ref = uc;
  *retVal_ref = retVal;
  *curr_ref = curr;
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
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32', 'i_ref is a mutable refrence to Int32', 't_ref is a mutable refrence to Int32', 'curr_ref is a mutable refrence to Int32']
void helper_helper_helper_BZ2_decompress_29_7_2(UChar * const uc_ref, Int32 * const retVal_ref, Int32 * const i_ref, Int32 * const t_ref, Int32 * const curr_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  Int32 i = *i_ref;
  Int32 t = *t_ref;
  Int32 curr = *curr_ref;
  while ((Bool) 1)
  {
    helper_helper_helper_helper_BZ2_decompress_29_7_2_1(&uc, &retVal, &curr, s);
  }

  s->len[t][i] = curr;
  *uc_ref = uc;
  *retVal_ref = retVal;
  *i_ref = i;
  *t_ref = t;
  *curr_ref = curr;
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
typedef char Char
----------------------------
void helper_helper_helper_helper_BZ2_decompress_29_7_2_1(UChar * const uc_ref, Int32 * const retVal_ref, Int32 * const curr_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  Int32 curr = *curr_ref;
  if ((curr < 1) || (curr > 20))
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  case 34:
    s->state = 34;

  while ((Bool) 1)
  {
    if (s->bsLive >= 1)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 1)) & ((1 << 1) - 1);
      s->bsLive -= 1;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if (uc == 0)
  {
    break;
  }
  case 35:
    s->state = 35;

  while ((Bool) 1)
  {
    if (s->bsLive >= 1)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 1)) & ((1 << 1) - 1);
      s->bsLive -= 1;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if (uc == 0)
  {
    curr += 1;
  }
  else
    curr--;
  curr -= 1;
  *uc_ref = uc;
  *retVal_ref = retVal;
  *curr_ref = curr;
}


----------------------------
typedef unsigned char UChar
----------------------------
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32', 'i_ref is a mutable refrence to Int32', 't_ref is a mutable refrence to Int32', 'curr_ref is a mutable refrence to Int32']
void helper_helper_BZ2_decompress_29_7(UChar * const uc_ref, Int32 * const retVal_ref, Int32 * const i_ref, Int32 * const t_ref, Int32 * const curr_ref, DState * const s, Int32 alphaSize)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  Int32 i = *i_ref;
  Int32 t = *t_ref;
  Int32 curr = *curr_ref;
  case 33:
    s->state = 33;

  while ((Bool) 1)
  {
    helper_helper_helper_BZ2_decompress_29_7_1(&retVal, &curr, s);
  }

  ;
  for (i = 0; i < alphaSize; i += 1)
  {
    helper_helper_helper_BZ2_decompress_29_7_2(&uc, &retVal, &i, &t, &curr, s);
  }

  *uc_ref = uc;
  *retVal_ref = retVal;
  *i_ref = i;
  *t_ref = t;
  *curr_ref = curr;
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
typedef char Char
----------------------------
void helper_helper_helper_BZ2_decompress_29_7_1(Int32 * const retVal_ref, Int32 * const curr_ref, DState * const s)
{
  Int32 retVal = *retVal_ref;
  Int32 curr = *curr_ref;
  if (s->bsLive >= 5)
  {
    UInt32 v;
    v = (s->bsBuff >> (s->bsLive - 5)) & ((1 << 5) - 1);
    s->bsLive -= 5;
    curr = v;
    break;
  }
  if (s->strm->avail_in == 0)
  {
    retVal = 0;
    goto save_state_and_return;
  }
  ;
  ;
  s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
  s->bsLive += 8;
  s->strm->next_in += 1;
  s->strm->avail_in -= 1;
  s->strm->total_in_lo32 += 1;
  if (s->strm->total_in_lo32 == 0)
  {
    s->strm->total_in_hi32 += 1;
  }
  *retVal_ref = retVal;
  *curr_ref = curr;
}


----------------------------
void helper_helper_helper_BZ2_decompress_29_7_2(UChar * const uc_ref, Int32 * const retVal_ref, Int32 * const i_ref, Int32 * const t_ref, Int32 * const curr_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  Int32 i = *i_ref;
  Int32 t = *t_ref;
  Int32 curr = *curr_ref;
  while ((Bool) 1)
  {
    helper_helper_helper_helper_BZ2_decompress_29_7_2_1(&uc, &retVal, &curr, s);
  }

  s->len[t][i] = curr;
  *uc_ref = uc;
  *retVal_ref = retVal;
  *i_ref = i;
  *t_ref = t;
  *curr_ref = curr;
}


----------------------------
typedef unsigned char UChar
----------------------------
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32', 'minLen_ref is a mutable refrence to Int32', 'maxLen_ref is a mutable refrence to Int32', 'i_ref is a mutable refrence to Int32', 'j_ref is a mutable refrence to Int32', 't_ref is a mutable refrence to Int32', 'nSelectors_ref is a mutable refrence to Int32', 'EOB_ref is a mutable refrence to Int32', 'groupNo_ref is a mutable refrence to Int32', 'groupPos_ref is a mutable refrence to Int32', 'nextSym_ref is a mutable refrence to Int32', 'nblockMAX_ref is a mutable refrence to Int32', 'nblock_ref is a mutable refrence to Int32', 'es_ref is a mutable refrence to Int32', 'N_ref is a mutable refrence to Int32', 'curr_ref is a mutable refrence to Int32', 'zn_ref is a mutable refrence to Int32', 'zvec_ref is a mutable refrence to Int32', 'zj_ref is a mutable refrence to Int32', 'gSel_ref is a mutable refrence to Int32', 'gMinlen_ref is a mutable refrence to Int32', 'gLimit_idx_ref is a mutable refrence to unsigned int', 'gBase_idx_ref is a mutable refrence to unsigned int', 'gPerm_idx_ref is a mutable refrence to unsigned int']
Int32 helper_BZ2_decompress_29(UChar * const uc_ref, Int32 * const retVal_ref, Int32 * const minLen_ref, Int32 * const maxLen_ref, Int32 * const i_ref, Int32 * const j_ref, Int32 * const t_ref, Int32 * const nSelectors_ref, Int32 * const EOB_ref, Int32 * const groupNo_ref, Int32 * const groupPos_ref, Int32 * const nextSym_ref, Int32 * const nblockMAX_ref, Int32 * const nblock_ref, Int32 * const es_ref, Int32 * const N_ref, Int32 * const curr_ref, Int32 * const zn_ref, Int32 * const zvec_ref, Int32 * const zj_ref, Int32 * const gSel_ref, Int32 * const gMinlen_ref, unsigned int * const gLimit_idx_ref, unsigned int * const gBase_idx_ref, unsigned int * const gPerm_idx_ref, DState * const s, Int32 alphaSize, Int32 nGroups, Int32 * const gLimit, Int32 * const gBase, Int32 * const gPerm)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  Int32 minLen = *minLen_ref;
  Int32 maxLen = *maxLen_ref;
  Int32 i = *i_ref;
  Int32 j = *j_ref;
  Int32 t = *t_ref;
  Int32 nSelectors = *nSelectors_ref;
  Int32 EOB = *EOB_ref;
  Int32 groupNo = *groupNo_ref;
  Int32 groupPos = *groupPos_ref;
  Int32 nextSym = *nextSym_ref;
  Int32 nblockMAX = *nblockMAX_ref;
  Int32 nblock = *nblock_ref;
  Int32 es = *es_ref;
  Int32 N = *N_ref;
  Int32 curr = *curr_ref;
  Int32 zn = *zn_ref;
  Int32 zvec = *zvec_ref;
  Int32 zj = *zj_ref;
  Int32 gSel = *gSel_ref;
  Int32 gMinlen = *gMinlen_ref;
  unsigned int gLimit_idx = *gLimit_idx_ref;
  unsigned int gBase_idx = *gBase_idx_ref;
  unsigned int gPerm_idx = *gPerm_idx_ref;
  s->state = 31;
  while ((Bool) 1)
  {
    helper_helper_BZ2_decompress_29_1(&retVal, &nSelectors, s);
  }

  ;
  if (nSelectors < 1)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  for (i = 0; i < nSelectors; i += 1)
  {
    helper_helper_BZ2_decompress_29_4(&uc, &retVal, &i, &j, s, nGroups);
  }

  if (nSelectors > (2 + (900000 / 50)))
  {
    nSelectors = 2 + (900000 / 50);
  }
  {
    UChar pos[6];
    UChar tmp;
    UChar v;
    for (v = 0; v < nGroups; v += 1)
      pos[v] = v;

    for (i = 0; i < nSelectors; i += 1)
    {
      v = s->selectorMtf[i];
      tmp = pos[v];
      while (v > 0)
      {
        pos[v] = pos[v - 1];
        v -= 1;
      }

      pos[0] = tmp;
      s->selector[i] = tmp;
    }

  }
  for (t = 0; t < nGroups; t += 1)
  {
    helper_helper_BZ2_decompress_29_7(&uc, &retVal, &i, &t, &curr, s, alphaSize);
  }

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

    BZ2_hbCreateDecodeTables(&s->limit[t][0], &s->base[t][0], &s->perm[t][0], &s->len[t][0], minLen, maxLen, alphaSize);
    s->minLens[t] = minLen;
  }

  EOB = s->nInUse + 1;
  nblockMAX = 100000 * s->blockSize100k;
  groupNo = -1;
  groupPos = 0;
  for (i = 0; i <= 255; i += 1)
    s->unzftab[i] = 0;

  {
    Int32 ii;
    Int32 jj;
    Int32 kk;
    kk = 4096 - 1;
    for (ii = (256 / 16) - 1; ii >= 0; ii -= 1)
    {
      for (jj = 16 - 1; jj >= 0; jj -= 1)
      {
        s->mtfa[kk] = (UChar) ((ii * 16) + jj);
        kk -= 1;
      }

      s->mtfbase[ii] = kk + 1;
    }

  }
  nblock = 0;
  {
    helper_helper_BZ2_decompress_29_6(&retVal, &groupNo, &groupPos, &nextSym, &zn, &zvec, &zj, &gSel, &gMinlen, &gLimit_idx, &gBase_idx, &gPerm_idx, s, gLimit, gBase, gPerm, nSelectors);
  }
  ;
  while ((Bool) 1)
  {
    helper_helper_BZ2_decompress_29_8(&uc, &retVal, &groupNo, &groupPos, &nextSym, &nblock, &es, &N, &zn, &zvec, &zj, &gSel, &gMinlen, &gLimit_idx, &gBase_idx, &gPerm_idx, s, gLimit, gBase, gPerm, nSelectors, EOB, nblockMAX);
  }

  if ((s->origPtr < 0) || (s->origPtr >= nblock))
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  for (i = 0; i <= 255; i += 1)
  {
    if ((s->unzftab[i] < 0) || (s->unzftab[i] > nblock))
    {
      retVal = -4;
      goto save_state_and_return;
    }
    ;
    ;
  }

  s->cftab[0] = 0;
  for (i = 1; i <= 256; i += 1)
    s->cftab[i] = s->unzftab[i - 1];

  for (i = 1; i <= 256; i += 1)
    s->cftab[i] += s->cftab[i - 1];

  for (i = 0; i <= 256; i += 1)
  {
    if ((s->cftab[i] < 0) || (s->cftab[i] > nblock))
    {
      {
        retVal = -4;
        goto save_state_and_return;
      }
      ;
      ;
    }
  }

  for (i = 1; i <= 256; i += 1)
  {
    if (s->cftab[i - 1] > s->cftab[i])
    {
      {
        retVal = -4;
        goto save_state_and_return;
      }
      ;
      ;
    }
  }

  s->state_out_len = 0;
  s->state_out_ch = 0;
  {
    s->calculatedBlockCRC = 0xffffffffL;
  }
  ;
  s->state = 2;
  if (s->verbosity >= 2)
  {
    fprintf(stderr, "rt+rld");
  }
  if (s->smallDecompress)
  {
    helper_helper_BZ2_decompress_29_5(&uc, &i, &j, s, nblock);
  }
  else
  {
    helper_helper_BZ2_decompress_29_3(&uc, &i, s, nblock);
  }
  {
    retVal = 0;
    goto save_state_and_return;
  }
  ;
  ;
  endhdr_2:
  case 42:
    s->state = 42;


  while ((Bool) 1)
  {
    helper_helper_BZ2_decompress_29_2(&uc, &retVal, s);
  }

  ;
  if (uc != 0x72)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  *uc_ref = uc;
  *retVal_ref = retVal;
  *minLen_ref = minLen;
  *maxLen_ref = maxLen;
  *i_ref = i;
  *j_ref = j;
  *t_ref = t;
  *nSelectors_ref = nSelectors;
  *EOB_ref = EOB;
  *groupNo_ref = groupNo;
  *groupPos_ref = groupPos;
  *nextSym_ref = nextSym;
  *nblockMAX_ref = nblockMAX;
  *nblock_ref = nblock;
  *es_ref = es;
  *N_ref = N;
  *curr_ref = curr;
  *zn_ref = zn;
  *zvec_ref = zvec;
  *zj_ref = zj;
  *gSel_ref = gSel;
  *gMinlen_ref = gMinlen;
  *gLimit_idx_ref = gLimit_idx;
  *gBase_idx_ref = gBase_idx;
  *gPerm_idx_ref = gPerm_idx;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
void helper_helper_BZ2_decompress_29_1(Int32 * const retVal_ref, Int32 * const nSelectors_ref, DState * const s)
{
  Int32 retVal = *retVal_ref;
  Int32 nSelectors = *nSelectors_ref;
  if (s->bsLive >= 15)
  {
    UInt32 v;
    v = (s->bsBuff >> (s->bsLive - 15)) & ((1 << 15) - 1);
    s->bsLive -= 15;
    nSelectors = v;
    break;
  }
  if (s->strm->avail_in == 0)
  {
    retVal = 0;
    goto save_state_and_return;
  }
  ;
  ;
  s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
  s->bsLive += 8;
  s->strm->next_in += 1;
  s->strm->avail_in -= 1;
  s->strm->total_in_lo32 += 1;
  if (s->strm->total_in_lo32 == 0)
  {
    s->strm->total_in_hi32 += 1;
  }
  *retVal_ref = retVal;
  *nSelectors_ref = nSelectors;
}


----------------------------
void helper_helper_BZ2_decompress_29_6(Int32 * const retVal_ref, Int32 * const groupNo_ref, Int32 * const groupPos_ref, Int32 * const nextSym_ref, Int32 * const zn_ref, Int32 * const zvec_ref, Int32 * const zj_ref, Int32 * const gSel_ref, Int32 * const gMinlen_ref, unsigned int * const gLimit_idx_ref, unsigned int * const gBase_idx_ref, unsigned int * const gPerm_idx_ref, DState * const s, Int32 * const gLimit, Int32 * const gBase, Int32 * const gPerm, Int32 nSelectors)
{
  Int32 retVal = *retVal_ref;
  Int32 groupNo = *groupNo_ref;
  Int32 groupPos = *groupPos_ref;
  Int32 nextSym = *nextSym_ref;
  Int32 zn = *zn_ref;
  Int32 zvec = *zvec_ref;
  Int32 zj = *zj_ref;
  Int32 gSel = *gSel_ref;
  Int32 gMinlen = *gMinlen_ref;
  unsigned int gLimit_idx = *gLimit_idx_ref;
  unsigned int gBase_idx = *gBase_idx_ref;
  unsigned int gPerm_idx = *gPerm_idx_ref;
  if (groupPos == 0)
  {
    groupNo += 1;
    if (groupNo >= nSelectors)
    {
      retVal = -4;
      goto save_state_and_return;
    }
    ;
    ;
    groupPos = 50;
    gSel = s->selector[groupNo];
    gMinlen = s->minLens[gSel];
    gLimit_idx = &s->limit[gSel][0];
    gPerm_idx = &s->perm[gSel][0];
    gBase_idx = &s->base[gSel][0];
  }
  groupPos -= 1;
  zn = gMinlen;
  case 36:
    s->state = 36;

  while ((Bool) 1)
  {
    helper_helper_helper_BZ2_decompress_29_6_1(&retVal, &zvec, s, zn);
  }

  ;
  while (1)
  {
    helper_helper_helper_BZ2_decompress_29_6_2(&retVal, &zn, &zvec, &zj, s, gLimit, gLimit_idx);
  }

  ;
  if (((zvec - gBase[zn + gBase_idx]) < 0) || ((zvec - gBase[zn + gBase_idx]) >= 258))
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  nextSym = gPerm[(zvec - gBase[zn + gBase_idx]) + gPerm_idx];
  *retVal_ref = retVal;
  *groupNo_ref = groupNo;
  *groupPos_ref = groupPos;
  *nextSym_ref = nextSym;
  *zn_ref = zn;
  *zvec_ref = zvec;
  *zj_ref = zj;
  *gSel_ref = gSel;
  *gMinlen_ref = gMinlen;
  *gLimit_idx_ref = gLimit_idx;
  *gBase_idx_ref = gBase_idx;
  *gPerm_idx_ref = gPerm_idx;
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
void helper_helper_BZ2_decompress_29_8(UChar * const uc_ref, Int32 * const retVal_ref, Int32 * const groupNo_ref, Int32 * const groupPos_ref, Int32 * const nextSym_ref, Int32 * const nblock_ref, Int32 * const es_ref, Int32 * const N_ref, Int32 * const zn_ref, Int32 * const zvec_ref, Int32 * const zj_ref, Int32 * const gSel_ref, Int32 * const gMinlen_ref, unsigned int * const gLimit_idx_ref, unsigned int * const gBase_idx_ref, unsigned int * const gPerm_idx_ref, DState * const s, Int32 * const gLimit, Int32 * const gBase, Int32 * const gPerm, Int32 nSelectors, Int32 EOB, Int32 nblockMAX)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  Int32 groupNo = *groupNo_ref;
  Int32 groupPos = *groupPos_ref;
  Int32 nextSym = *nextSym_ref;
  Int32 nblock = *nblock_ref;
  Int32 es = *es_ref;
  Int32 N = *N_ref;
  Int32 zn = *zn_ref;
  Int32 zvec = *zvec_ref;
  Int32 zj = *zj_ref;
  Int32 gSel = *gSel_ref;
  Int32 gMinlen = *gMinlen_ref;
  unsigned int gLimit_idx = *gLimit_idx_ref;
  unsigned int gBase_idx = *gBase_idx_ref;
  unsigned int gPerm_idx = *gPerm_idx_ref;
  if (nextSym == EOB)
  {
    break;
  }
  if ((nextSym == 0) || (nextSym == 1))
  {
    helper_helper_helper_BZ2_decompress_29_8_1(&uc, &retVal, &groupNo, &groupPos, &nextSym, &nblock, &es, &N, &zn, &zvec, &zj, &gSel, &gMinlen, &gLimit_idx, &gBase_idx, &gPerm_idx, s, gLimit, gBase, gPerm, nSelectors, nblockMAX);
  }
  else
  {
    helper_helper_helper_BZ2_decompress_29_8_2(&uc, &retVal, &groupNo, &groupPos, &nextSym, &nblock, &zn, &zvec, &zj, &gSel, &gMinlen, &gLimit_idx, &gBase_idx, &gPerm_idx, s, gLimit, gBase, gPerm, nSelectors, nblockMAX);
  }
  *uc_ref = uc;
  *retVal_ref = retVal;
  *groupNo_ref = groupNo;
  *groupPos_ref = groupPos;
  *nextSym_ref = nextSym;
  *nblock_ref = nblock;
  *es_ref = es;
  *N_ref = N;
  *zn_ref = zn;
  *zvec_ref = zvec;
  *zj_ref = zj;
  *gSel_ref = gSel;
  *gMinlen_ref = gMinlen;
  *gLimit_idx_ref = gLimit_idx;
  *gBase_idx_ref = gBase_idx;
  *gPerm_idx_ref = gPerm_idx;
}


----------------------------
typedef char Char
----------------------------
Int32 helper_helper_BZ2_decompress_29_3(UChar * const uc_ref, Int32 * const i_ref, DState * const s, Int32 nblock)
{
  UChar uc = *uc_ref;
  Int32 i = *i_ref;
  for (i = 0; i < nblock; i += 1)
  {
    uc = (UChar) (s->tt[i] & 0xff);
    s->tt[s->cftab[uc]] |= i << 8;
    s->cftab[uc] += 1;
  }

  s->tPos = s->tt[s->origPtr] >> 8;
  s->nblock_used = 0;
  if (s->blockRandomised)
  {
    s->rNToGo = 0;
    s->rTPos = 0;
    if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
    {
      return (Bool) 1;
    }
    s->tPos = s->tt[s->tPos];
    s->k0 = (UChar) (s->tPos & 0xff);
    s->tPos >>= 8;
    ;
    s->nblock_used += 1;
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
  }
  else
  {
    if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
    {
      return (Bool) 1;
    }
    s->tPos = s->tt[s->tPos];
    s->k0 = (UChar) (s->tPos & 0xff);
    s->tPos >>= 8;
    ;
    s->nblock_used += 1;
  }
  *uc_ref = uc;
  *i_ref = i;
}


----------------------------
void helper_helper_BZ2_decompress_29_2(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  if (s->bsLive >= 8)
  {
    UInt32 v;
    v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
    s->bsLive -= 8;
    uc = v;
    break;
  }
  if (s->strm->avail_in == 0)
  {
    retVal = 0;
    goto save_state_and_return;
  }
  ;
  ;
  s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
  s->bsLive += 8;
  s->strm->next_in += 1;
  s->strm->avail_in -= 1;
  s->strm->total_in_lo32 += 1;
  if (s->strm->total_in_lo32 == 0)
  {
    s->strm->total_in_hi32 += 1;
  }
  *uc_ref = uc;
  *retVal_ref = retVal;
}


----------------------------
void helper_helper_BZ2_decompress_29_4(UChar * const uc_ref, Int32 * const retVal_ref, Int32 * const i_ref, Int32 * const j_ref, DState * const s, Int32 nGroups)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  Int32 i = *i_ref;
  Int32 j = *j_ref;
  j = 0;
  while ((Bool) 1)
  {
    helper_helper_helper_BZ2_decompress_29_4_1(&uc, &retVal, &j, s, nGroups);
  }

  if (i < (2 + (900000 / 50)))
  {
    s->selectorMtf[i] = j;
  }
  *uc_ref = uc;
  *retVal_ref = retVal;
  *i_ref = i;
  *j_ref = j;
}


----------------------------
typedef unsigned char UChar
----------------------------
Int32 helper_helper_BZ2_decompress_29_5(UChar * const uc_ref, Int32 * const i_ref, Int32 * const j_ref, DState * const s, Int32 nblock)
{
  UChar uc = *uc_ref;
  Int32 i = *i_ref;
  Int32 j = *j_ref;
  for (i = 0; i <= 256; i += 1)
    s->cftabCopy[i] = s->cftab[i];

  for (i = 0; i < nblock; i += 1)
  {
    uc = (UChar) s->ll16[i];
    {
      s->ll16[i] = (UInt16) (s->cftabCopy[uc] & 0x0000ffff);
      {
        if ((i & 0x1) == 0)
        {
          s->ll4[i >> 1] = (s->ll4[i >> 1] & 0xf0) | (s->cftabCopy[uc] >> 16);
        }
        else
          s->ll4[i >> 1] = (s->ll4[i >> 1] & 0x0f) | ((s->cftabCopy[uc] >> 16) << 4);
      }
      ;
    }
    ;
    s->cftabCopy[uc] += 1;
  }

  i = s->origPtr;
  j = ((UInt32) s->ll16[i]) | (((((UInt32) s->ll4[i >> 1]) >> ((i << 2) & 0x4)) & 0xF) << 16);
  do
  {
    Int32 tmp = ((UInt32) s->ll16[j]) | (((((UInt32) s->ll4[j >> 1]) >> ((j << 2) & 0x4)) & 0xF) << 16);
    {
      s->ll16[j] = (UInt16) (i & 0x0000ffff);
      {
        if ((j & 0x1) == 0)
        {
          s->ll4[j >> 1] = (s->ll4[j >> 1] & 0xf0) | (i >> 16);
        }
        else
          s->ll4[j >> 1] = (s->ll4[j >> 1] & 0x0f) | ((i >> 16) << 4);
      }
      ;
    }
    ;
    i = j;
    j = tmp;
  }
  while (i != s->origPtr);
  s->tPos = s->origPtr;
  s->nblock_used = 0;
  if (s->blockRandomised)
  {
    helper_helper_helper_BZ2_decompress_29_5_1(s);
  }
  else
  {
    if (s->tPos >= (((UInt32) 100000) * ((UInt32) s->blockSize100k)))
    {
      return (Bool) 1;
    }
    s->k0 = BZ2_indexIntoF(s->tPos, s->cftab);
    s->tPos = ((UInt32) s->ll16[s->tPos]) | (((((UInt32) s->ll4[s->tPos >> 1]) >> ((s->tPos << 2) & 0x4)) & 0xF) << 16);
    ;
    s->nblock_used += 1;
  }
  *uc_ref = uc;
  *i_ref = i;
  *j_ref = j;
}


----------------------------
void BZ2_hbCreateDecodeTables(Int32 *limit, Int32 *base, Int32 *perm, UChar *length, Int32 minLen, Int32 maxLen, Int32 alphaSize)
{
  Int32 pp;
  Int32 i;
  Int32 j;
  Int32 vec;
  pp = 0;
  for (i = minLen; i <= maxLen; i += 1)
    for (j = 0; j < alphaSize; j += 1)
    if (length[j] == i)
  {
    perm[pp] = j;
    pp += 1;
  }


  ;
  for (i = 0; i < 23; i += 1)
    base[i] = 0;

  for (i = 0; i < alphaSize; i += 1)
    base[length[i] + 1]++;

  for (i = 1; i < 23; i += 1)
    base[i] += base[i - 1];

  for (i = 0; i < 23; i += 1)
    limit[i] = 0;

  vec = 0;
  for (i = minLen; i <= maxLen; i += 1)
  {
    vec += base[i + 1] - base[i];
    limit[i] = vec - 1;
    vec <<= 1;
  }

  for (i = minLen + 1; i <= maxLen; i += 1)
    base[i] = ((limit[i - 1] + 1) << 1) - base[i];

}


----------------------------
void helper_helper_BZ2_decompress_29_7(UChar * const uc_ref, Int32 * const retVal_ref, Int32 * const i_ref, Int32 * const t_ref, Int32 * const curr_ref, DState * const s, Int32 alphaSize)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  Int32 i = *i_ref;
  Int32 t = *t_ref;
  Int32 curr = *curr_ref;
  case 33:
    s->state = 33;

  while ((Bool) 1)
  {
    helper_helper_helper_BZ2_decompress_29_7_1(&retVal, &curr, s);
  }

  ;
  for (i = 0; i < alphaSize; i += 1)
  {
    helper_helper_helper_BZ2_decompress_29_7_2(&uc, &retVal, &i, &t, &curr, s);
  }

  *uc_ref = uc;
  *retVal_ref = retVal;
  *i_ref = i;
  *t_ref = t;
  *curr_ref = curr;
}


----------------------------
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32']
void helper_BZ2_decompress_4(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 23;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  s->storedBlockCRC = (s->storedBlockCRC << 8) | ((UInt32) uc);
  *uc_ref = uc;
  *retVal_ref = retVal;
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
***/


// hint:  ['retVal_ref is a mutable refrence to Int32']
void helper_helper_BZ2_decompress_27_1(Int32 * const retVal_ref, DState * const s)
{
  Int32 retVal = *retVal_ref;
  if (s->bsLive >= 8)
  {
    UInt32 v;
    v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
    s->bsLive -= 8;
    s->blockSize100k = v;
    break;
  }
  if (s->strm->avail_in == 0)
  {
    retVal = 0;
    goto save_state_and_return;
  }
  ;
  ;
  s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
  s->bsLive += 8;
  s->strm->next_in += 1;
  s->strm->avail_in -= 1;
  s->strm->total_in_lo32 += 1;
  if (s->strm->total_in_lo32 == 0)
  {
    s->strm->total_in_hi32 += 1;
  }
  *retVal_ref = retVal;
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
***/


// hint:  ['retVal_ref is a mutable refrence to Int32']
void helper_BZ2_decompress_27(Int32 * const retVal_ref, DState * const s, bz_stream * const strm)
{
  Int32 retVal = *retVal_ref;
  s->state = 13;
  while ((Bool) 1)
  {
    helper_helper_BZ2_decompress_27_1(&retVal, s);
  }

  if ((s->blockSize100k < (0x30 + 1)) || (s->blockSize100k > (0x30 + 9)))
  {
    retVal = -5;
    goto save_state_and_return;
  }
  ;
  ;
  s->blockSize100k -= 0x30;
  if (s->smallDecompress)
  {
    s->ll16 = strm->bzalloc(strm->opaque, (s->blockSize100k * 100000) * (sizeof(UInt16)), 1);
    s->ll4 = strm->bzalloc(strm->opaque, ((1 + (s->blockSize100k * 100000)) >> 1) * (sizeof(UChar)), 1);
    if ((s->ll16 == 0) || (s->ll4 == 0))
    {
      retVal = -3;
      goto save_state_and_return;
    }
    ;
    ;
  }
  else
  {
    s->tt = strm->bzalloc(strm->opaque, (s->blockSize100k * 100000) * (sizeof(Int32)), 1);
    if (s->tt == 0)
    {
      retVal = -3;
      goto save_state_and_return;
    }
    ;
    ;
  }
  *retVal_ref = retVal;
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
void helper_helper_BZ2_decompress_27_1(Int32 * const retVal_ref, DState * const s)
{
  Int32 retVal = *retVal_ref;
  if (s->bsLive >= 8)
  {
    UInt32 v;
    v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
    s->bsLive -= 8;
    s->blockSize100k = v;
    break;
  }
  if (s->strm->avail_in == 0)
  {
    retVal = 0;
    goto save_state_and_return;
  }
  ;
  ;
  s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
  s->bsLive += 8;
  s->strm->next_in += 1;
  s->strm->avail_in -= 1;
  s->strm->total_in_lo32 += 1;
  if (s->strm->total_in_lo32 == 0)
  {
    s->strm->total_in_hi32 += 1;
  }
  *retVal_ref = retVal;
}


----------------------------
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
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32']
void helper_BZ2_decompress_10(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 49;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  s->storedCombinedCRC = (s->storedCombinedCRC << 8) | ((UInt32) uc);
  *uc_ref = uc;
  *retVal_ref = retVal;
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
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32']
void helper_BZ2_decompress_12(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 12;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  if (uc != 0x68)
  {
    retVal = -5;
    goto save_state_and_return;
  }
  ;
  ;
  *uc_ref = uc;
  *retVal_ref = retVal;
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
***/


// hint:  ['retVal_ref is a mutable refrence to Int32', 'nGroups_ref is a mutable refrence to Int32']
void helper_BZ2_decompress_19(Int32 * const retVal_ref, Int32 * const nGroups_ref, DState * const s)
{
  Int32 retVal = *retVal_ref;
  Int32 nGroups = *nGroups_ref;
  s->state = 30;
  while ((Bool) 1)
  {
    if (s->bsLive >= 3)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 3)) & ((1 << 3) - 1);
      s->bsLive -= 3;
      nGroups = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if ((nGroups < 2) || (nGroups > 6))
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  *retVal_ref = retVal;
  *nGroups_ref = nGroups;
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
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32']
void helper_BZ2_decompress_1(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 20;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  s->storedBlockCRC = (s->storedBlockCRC << 8) | ((UInt32) uc);
  *uc_ref = uc;
  *retVal_ref = retVal;
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
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32']
void helper_BZ2_decompress_26(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 19;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if (uc != 0x59)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  s->currBlockNo += 1;
  if (s->verbosity >= 2)
  {
    fprintf(stderr, "\n    [%d: huff+mtf ", s->currBlockNo);
  }
  s->storedBlockCRC = 0;
  *uc_ref = uc;
  *retVal_ref = retVal;
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
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32']
void helper_BZ2_decompress_14(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 11;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if (uc != 0x5a)
  {
    retVal = -5;
    goto save_state_and_return;
  }
  ;
  ;
  *uc_ref = uc;
  *retVal_ref = retVal;
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
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32']
void helper_BZ2_decompress_21(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 44;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if (uc != 0x38)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  *uc_ref = uc;
  *retVal_ref = retVal;
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
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32']
void helper_BZ2_decompress_18(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 18;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if (uc != 0x53)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  *uc_ref = uc;
  *retVal_ref = retVal;
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
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32']
void helper_BZ2_decompress_6(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 25;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  s->origPtr = (s->origPtr << 8) | ((Int32) uc);
  *uc_ref = uc;
  *retVal_ref = retVal;
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
***/


// hint:  ['retVal_ref is a mutable refrence to Int32']
void helper_BZ2_decompress_5(Int32 * const retVal_ref, DState * const s)
{
  Int32 retVal = *retVal_ref;
  s->state = 24;
  while ((Bool) 1)
  {
    if (s->bsLive >= 1)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 1)) & ((1 << 1) - 1);
      s->bsLive -= 1;
      s->blockRandomised = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  s->origPtr = 0;
  *retVal_ref = retVal;
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
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32']
void helper_BZ2_decompress_25(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 50;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  s->storedCombinedCRC = (s->storedCombinedCRC << 8) | ((UInt32) uc);
  s->state = 1;
  {
    retVal = 4;
    goto save_state_and_return;
  }
  ;
  ;
  *uc_ref = uc;
  *retVal_ref = retVal;
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
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32']
void helper_BZ2_decompress_15(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 15;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if (uc != 0x41)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  *uc_ref = uc;
  *retVal_ref = retVal;
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
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32']
void helper_BZ2_decompress_8(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 47;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  s->storedCombinedCRC = (s->storedCombinedCRC << 8) | ((UInt32) uc);
  *uc_ref = uc;
  *retVal_ref = retVal;
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
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32']
void helper_BZ2_decompress_24(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 14;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if (uc == 0x17)
  {
    goto endhdr_2;
  }
  if (uc != 0x31)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  *uc_ref = uc;
  *retVal_ref = retVal;
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
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32']
void helper_BZ2_decompress_20(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 43;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if (uc != 0x45)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  *uc_ref = uc;
  *retVal_ref = retVal;
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
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32']
void helper_BZ2_decompress_2(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 21;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  s->storedBlockCRC = (s->storedBlockCRC << 8) | ((UInt32) uc);
  *uc_ref = uc;
  *retVal_ref = retVal;
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
***/


// hint:  ['uc_ref is a mutable refrence to UChar', 'retVal_ref is a mutable refrence to Int32']
void helper_BZ2_decompress_13(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 10;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if (uc != 0x42)
  {
    retVal = -5;
    goto save_state_and_return;
  }
  ;
  ;
  *uc_ref = uc;
  *retVal_ref = retVal;
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
***/


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


/*** DEPENDENCIES:
void helper_BZ2_decompress_16(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 16;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if (uc != 0x59)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  *uc_ref = uc;
  *retVal_ref = retVal;
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
void helper_BZ2_decompress_22(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 45;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if (uc != 0x50)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  *uc_ref = uc;
  *retVal_ref = retVal;
}


----------------------------
void helper_BZ2_decompress_17(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 17;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if (uc != 0x26)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  *uc_ref = uc;
  *retVal_ref = retVal;
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
void helper_BZ2_decompress_28(UChar * const uc_ref, Int32 * const retVal_ref, Int32 * const i_ref, Int32 * const j_ref, Int32 * const alphaSize_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  Int32 i = *i_ref;
  Int32 j = *j_ref;
  Int32 alphaSize = *alphaSize_ref;
  s->state = 27;
  while ((Bool) 1)
  {
    helper_helper_BZ2_decompress_28_1(&uc, &retVal, s);
  }

  ;
  s->origPtr = (s->origPtr << 8) | ((Int32) uc);
  if (s->origPtr < 0)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  if (s->origPtr > (10 + (100000 * s->blockSize100k)))
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  for (i = 0; i < 16; i += 1)
  {
    helper_helper_BZ2_decompress_28_2(&uc, &retVal, &i, s);
  }

  for (i = 0; i < 256; i += 1)
    s->inUse[i] = (Bool) 0;

  for (i = 0; i < 16; i += 1)
    if (s->inUse16[i])
  {
    helper_helper_BZ2_decompress_28_3(&uc, &retVal, &i, &j, s);
  }

  makeMaps_d(s);
  if (s->nInUse == 0)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  alphaSize = s->nInUse + 2;
  *uc_ref = uc;
  *retVal_ref = retVal;
  *i_ref = i;
  *j_ref = j;
  *alphaSize_ref = alphaSize;
}


----------------------------
void helper_BZ2_decompress_3(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 22;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  s->storedBlockCRC = (s->storedBlockCRC << 8) | ((UInt32) uc);
  *uc_ref = uc;
  *retVal_ref = retVal;
}


----------------------------
void helper_BZ2_decompress_23(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 46;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if (uc != 0x90)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  s->storedCombinedCRC = 0;
  *uc_ref = uc;
  *retVal_ref = retVal;
}


----------------------------
void helper_BZ2_decompress_9(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 48;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  s->storedCombinedCRC = (s->storedCombinedCRC << 8) | ((UInt32) uc);
  *uc_ref = uc;
  *retVal_ref = retVal;
}


----------------------------
typedef unsigned char UChar
----------------------------
void helper_BZ2_decompress_7(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 26;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  s->origPtr = (s->origPtr << 8) | ((Int32) uc);
  *uc_ref = uc;
  *retVal_ref = retVal;
}


----------------------------
Int32 helper_BZ2_decompress_29(UChar * const uc_ref, Int32 * const retVal_ref, Int32 * const minLen_ref, Int32 * const maxLen_ref, Int32 * const i_ref, Int32 * const j_ref, Int32 * const t_ref, Int32 * const nSelectors_ref, Int32 * const EOB_ref, Int32 * const groupNo_ref, Int32 * const groupPos_ref, Int32 * const nextSym_ref, Int32 * const nblockMAX_ref, Int32 * const nblock_ref, Int32 * const es_ref, Int32 * const N_ref, Int32 * const curr_ref, Int32 * const zn_ref, Int32 * const zvec_ref, Int32 * const zj_ref, Int32 * const gSel_ref, Int32 * const gMinlen_ref, unsigned int * const gLimit_idx_ref, unsigned int * const gBase_idx_ref, unsigned int * const gPerm_idx_ref, DState * const s, Int32 alphaSize, Int32 nGroups, Int32 * const gLimit, Int32 * const gBase, Int32 * const gPerm)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  Int32 minLen = *minLen_ref;
  Int32 maxLen = *maxLen_ref;
  Int32 i = *i_ref;
  Int32 j = *j_ref;
  Int32 t = *t_ref;
  Int32 nSelectors = *nSelectors_ref;
  Int32 EOB = *EOB_ref;
  Int32 groupNo = *groupNo_ref;
  Int32 groupPos = *groupPos_ref;
  Int32 nextSym = *nextSym_ref;
  Int32 nblockMAX = *nblockMAX_ref;
  Int32 nblock = *nblock_ref;
  Int32 es = *es_ref;
  Int32 N = *N_ref;
  Int32 curr = *curr_ref;
  Int32 zn = *zn_ref;
  Int32 zvec = *zvec_ref;
  Int32 zj = *zj_ref;
  Int32 gSel = *gSel_ref;
  Int32 gMinlen = *gMinlen_ref;
  unsigned int gLimit_idx = *gLimit_idx_ref;
  unsigned int gBase_idx = *gBase_idx_ref;
  unsigned int gPerm_idx = *gPerm_idx_ref;
  s->state = 31;
  while ((Bool) 1)
  {
    helper_helper_BZ2_decompress_29_1(&retVal, &nSelectors, s);
  }

  ;
  if (nSelectors < 1)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  for (i = 0; i < nSelectors; i += 1)
  {
    helper_helper_BZ2_decompress_29_4(&uc, &retVal, &i, &j, s, nGroups);
  }

  if (nSelectors > (2 + (900000 / 50)))
  {
    nSelectors = 2 + (900000 / 50);
  }
  {
    UChar pos[6];
    UChar tmp;
    UChar v;
    for (v = 0; v < nGroups; v += 1)
      pos[v] = v;

    for (i = 0; i < nSelectors; i += 1)
    {
      v = s->selectorMtf[i];
      tmp = pos[v];
      while (v > 0)
      {
        pos[v] = pos[v - 1];
        v -= 1;
      }

      pos[0] = tmp;
      s->selector[i] = tmp;
    }

  }
  for (t = 0; t < nGroups; t += 1)
  {
    helper_helper_BZ2_decompress_29_7(&uc, &retVal, &i, &t, &curr, s, alphaSize);
  }

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

    BZ2_hbCreateDecodeTables(&s->limit[t][0], &s->base[t][0], &s->perm[t][0], &s->len[t][0], minLen, maxLen, alphaSize);
    s->minLens[t] = minLen;
  }

  EOB = s->nInUse + 1;
  nblockMAX = 100000 * s->blockSize100k;
  groupNo = -1;
  groupPos = 0;
  for (i = 0; i <= 255; i += 1)
    s->unzftab[i] = 0;

  {
    Int32 ii;
    Int32 jj;
    Int32 kk;
    kk = 4096 - 1;
    for (ii = (256 / 16) - 1; ii >= 0; ii -= 1)
    {
      for (jj = 16 - 1; jj >= 0; jj -= 1)
      {
        s->mtfa[kk] = (UChar) ((ii * 16) + jj);
        kk -= 1;
      }

      s->mtfbase[ii] = kk + 1;
    }

  }
  nblock = 0;
  {
    helper_helper_BZ2_decompress_29_6(&retVal, &groupNo, &groupPos, &nextSym, &zn, &zvec, &zj, &gSel, &gMinlen, &gLimit_idx, &gBase_idx, &gPerm_idx, s, gLimit, gBase, gPerm, nSelectors);
  }
  ;
  while ((Bool) 1)
  {
    helper_helper_BZ2_decompress_29_8(&uc, &retVal, &groupNo, &groupPos, &nextSym, &nblock, &es, &N, &zn, &zvec, &zj, &gSel, &gMinlen, &gLimit_idx, &gBase_idx, &gPerm_idx, s, gLimit, gBase, gPerm, nSelectors, EOB, nblockMAX);
  }

  if ((s->origPtr < 0) || (s->origPtr >= nblock))
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  for (i = 0; i <= 255; i += 1)
  {
    if ((s->unzftab[i] < 0) || (s->unzftab[i] > nblock))
    {
      retVal = -4;
      goto save_state_and_return;
    }
    ;
    ;
  }

  s->cftab[0] = 0;
  for (i = 1; i <= 256; i += 1)
    s->cftab[i] = s->unzftab[i - 1];

  for (i = 1; i <= 256; i += 1)
    s->cftab[i] += s->cftab[i - 1];

  for (i = 0; i <= 256; i += 1)
  {
    if ((s->cftab[i] < 0) || (s->cftab[i] > nblock))
    {
      {
        retVal = -4;
        goto save_state_and_return;
      }
      ;
      ;
    }
  }

  for (i = 1; i <= 256; i += 1)
  {
    if (s->cftab[i - 1] > s->cftab[i])
    {
      {
        retVal = -4;
        goto save_state_and_return;
      }
      ;
      ;
    }
  }

  s->state_out_len = 0;
  s->state_out_ch = 0;
  {
    s->calculatedBlockCRC = 0xffffffffL;
  }
  ;
  s->state = 2;
  if (s->verbosity >= 2)
  {
    fprintf(stderr, "rt+rld");
  }
  if (s->smallDecompress)
  {
    helper_helper_BZ2_decompress_29_5(&uc, &i, &j, s, nblock);
  }
  else
  {
    helper_helper_BZ2_decompress_29_3(&uc, &i, s, nblock);
  }
  {
    retVal = 0;
    goto save_state_and_return;
  }
  ;
  ;
  endhdr_2:
  case 42:
    s->state = 42;


  while ((Bool) 1)
  {
    helper_helper_BZ2_decompress_29_2(&uc, &retVal, s);
  }

  ;
  if (uc != 0x72)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  *uc_ref = uc;
  *retVal_ref = retVal;
  *minLen_ref = minLen;
  *maxLen_ref = maxLen;
  *i_ref = i;
  *j_ref = j;
  *t_ref = t;
  *nSelectors_ref = nSelectors;
  *EOB_ref = EOB;
  *groupNo_ref = groupNo;
  *groupPos_ref = groupPos;
  *nextSym_ref = nextSym;
  *nblockMAX_ref = nblockMAX;
  *nblock_ref = nblock;
  *es_ref = es;
  *N_ref = N;
  *curr_ref = curr;
  *zn_ref = zn;
  *zvec_ref = zvec;
  *zj_ref = zj;
  *gSel_ref = gSel;
  *gMinlen_ref = gMinlen;
  *gLimit_idx_ref = gLimit_idx;
  *gBase_idx_ref = gBase_idx;
  *gPerm_idx_ref = gPerm_idx;
}


----------------------------
void helper_BZ2_decompress_4(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 23;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  s->storedBlockCRC = (s->storedBlockCRC << 8) | ((UInt32) uc);
  *uc_ref = uc;
  *retVal_ref = retVal;
}


----------------------------
void helper_BZ2_decompress_27(Int32 * const retVal_ref, DState * const s, bz_stream * const strm)
{
  Int32 retVal = *retVal_ref;
  s->state = 13;
  while ((Bool) 1)
  {
    helper_helper_BZ2_decompress_27_1(&retVal, s);
  }

  if ((s->blockSize100k < (0x30 + 1)) || (s->blockSize100k > (0x30 + 9)))
  {
    retVal = -5;
    goto save_state_and_return;
  }
  ;
  ;
  s->blockSize100k -= 0x30;
  if (s->smallDecompress)
  {
    s->ll16 = strm->bzalloc(strm->opaque, (s->blockSize100k * 100000) * (sizeof(UInt16)), 1);
    s->ll4 = strm->bzalloc(strm->opaque, ((1 + (s->blockSize100k * 100000)) >> 1) * (sizeof(UChar)), 1);
    if ((s->ll16 == 0) || (s->ll4 == 0))
    {
      retVal = -3;
      goto save_state_and_return;
    }
    ;
    ;
  }
  else
  {
    s->tt = strm->bzalloc(strm->opaque, (s->blockSize100k * 100000) * (sizeof(Int32)), 1);
    if (s->tt == 0)
    {
      retVal = -3;
      goto save_state_and_return;
    }
    ;
    ;
  }
  *retVal_ref = retVal;
}


----------------------------
void helper_BZ2_decompress_10(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 49;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  s->storedCombinedCRC = (s->storedCombinedCRC << 8) | ((UInt32) uc);
  *uc_ref = uc;
  *retVal_ref = retVal;
}


----------------------------
void helper_BZ2_decompress_12(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 12;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  if (uc != 0x68)
  {
    retVal = -5;
    goto save_state_and_return;
  }
  ;
  ;
  *uc_ref = uc;
  *retVal_ref = retVal;
}


----------------------------
void helper_BZ2_decompress_19(Int32 * const retVal_ref, Int32 * const nGroups_ref, DState * const s)
{
  Int32 retVal = *retVal_ref;
  Int32 nGroups = *nGroups_ref;
  s->state = 30;
  while ((Bool) 1)
  {
    if (s->bsLive >= 3)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 3)) & ((1 << 3) - 1);
      s->bsLive -= 3;
      nGroups = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if ((nGroups < 2) || (nGroups > 6))
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  *retVal_ref = retVal;
  *nGroups_ref = nGroups;
}


----------------------------
typedef char Char
----------------------------
void helper_BZ2_decompress_1(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 20;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  s->storedBlockCRC = (s->storedBlockCRC << 8) | ((UInt32) uc);
  *uc_ref = uc;
  *retVal_ref = retVal;
}


----------------------------
void helper_BZ2_decompress_26(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 19;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if (uc != 0x59)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  s->currBlockNo += 1;
  if (s->verbosity >= 2)
  {
    fprintf(stderr, "\n    [%d: huff+mtf ", s->currBlockNo);
  }
  s->storedBlockCRC = 0;
  *uc_ref = uc;
  *retVal_ref = retVal;
}


----------------------------
void helper_BZ2_decompress_14(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 11;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if (uc != 0x5a)
  {
    retVal = -5;
    goto save_state_and_return;
  }
  ;
  ;
  *uc_ref = uc;
  *retVal_ref = retVal;
}


----------------------------
void helper_BZ2_decompress_21(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 44;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if (uc != 0x38)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  *uc_ref = uc;
  *retVal_ref = retVal;
}


----------------------------
typedef int Int32
----------------------------
void helper_BZ2_decompress_18(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 18;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if (uc != 0x53)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  *uc_ref = uc;
  *retVal_ref = retVal;
}


----------------------------
void helper_BZ2_decompress_6(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 25;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  s->origPtr = (s->origPtr << 8) | ((Int32) uc);
  *uc_ref = uc;
  *retVal_ref = retVal;
}


----------------------------
void helper_BZ2_decompress_5(Int32 * const retVal_ref, DState * const s)
{
  Int32 retVal = *retVal_ref;
  s->state = 24;
  while ((Bool) 1)
  {
    if (s->bsLive >= 1)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 1)) & ((1 << 1) - 1);
      s->bsLive -= 1;
      s->blockRandomised = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  s->origPtr = 0;
  *retVal_ref = retVal;
}


----------------------------
void helper_BZ2_decompress_25(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 50;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  s->storedCombinedCRC = (s->storedCombinedCRC << 8) | ((UInt32) uc);
  s->state = 1;
  {
    retVal = 4;
    goto save_state_and_return;
  }
  ;
  ;
  *uc_ref = uc;
  *retVal_ref = retVal;
}


----------------------------
void helper_BZ2_decompress_15(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 15;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if (uc != 0x41)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  *uc_ref = uc;
  *retVal_ref = retVal;
}


----------------------------
void helper_BZ2_decompress_8(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 47;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  s->storedCombinedCRC = (s->storedCombinedCRC << 8) | ((UInt32) uc);
  *uc_ref = uc;
  *retVal_ref = retVal;
}


----------------------------
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
void helper_BZ2_decompress_24(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 14;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if (uc == 0x17)
  {
    goto endhdr_2;
  }
  if (uc != 0x31)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  *uc_ref = uc;
  *retVal_ref = retVal;
}


----------------------------
void helper_BZ2_decompress_11(DState * const s)
{
  s->save_i = 0;
  s->save_j = 0;
  s->save_t = 0;
  s->save_alphaSize = 0;
  s->save_nGroups = 0;
  s->save_nSelectors = 0;
  s->save_EOB = 0;
  s->save_groupNo = 0;
  s->save_groupPos = 0;
  s->save_nextSym = 0;
  s->save_nblockMAX = 0;
  s->save_nblock = 0;
  s->save_es = 0;
  s->save_N = 0;
  s->save_curr = 0;
  s->save_zt = 0;
  s->save_zn = 0;
  s->save_zvec = 0;
  s->save_zj = 0;
  s->save_gSel = 0;
  s->save_gMinlen = 0;
  s->save_gLimit = 0;
  s->save_gBase = 0;
  s->save_gPerm = 0;
}


----------------------------
void helper_BZ2_decompress_20(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 43;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if (uc != 0x45)
  {
    retVal = -4;
    goto save_state_and_return;
  }
  ;
  ;
  *uc_ref = uc;
  *retVal_ref = retVal;
}


----------------------------
void helper_BZ2_decompress_2(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 21;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  s->storedBlockCRC = (s->storedBlockCRC << 8) | ((UInt32) uc);
  *uc_ref = uc;
  *retVal_ref = retVal;
}


----------------------------
void helper_BZ2_decompress_13(UChar * const uc_ref, Int32 * const retVal_ref, DState * const s)
{
  UChar uc = *uc_ref;
  Int32 retVal = *retVal_ref;
  s->state = 10;
  while ((Bool) 1)
  {
    if (s->bsLive >= 8)
    {
      UInt32 v;
      v = (s->bsBuff >> (s->bsLive - 8)) & ((1 << 8) - 1);
      s->bsLive -= 8;
      uc = v;
      break;
    }
    if (s->strm->avail_in == 0)
    {
      retVal = 0;
      goto save_state_and_return;
    }
    ;
    ;
    s->bsBuff = (s->bsBuff << 8) | ((UInt32) (*((UChar *) s->strm->next_in)));
    s->bsLive += 8;
    s->strm->next_in += 1;
    s->strm->avail_in -= 1;
    s->strm->total_in_lo32 += 1;
    if (s->strm->total_in_lo32 == 0)
    {
      s->strm->total_in_hi32 += 1;
    }
  }

  ;
  if (uc != 0x42)
  {
    retVal = -5;
    goto save_state_and_return;
  }
  ;
  ;
  *uc_ref = uc;
  *retVal_ref = retVal;
}


----------------------------
***/


