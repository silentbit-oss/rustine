void helper_helper_helper_BZ2_hbMakeCodeLengths_1_1_1(Int32 heap[258 + 2], Int32 weight[258 * 2], Int32 nHeap)
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


/*** DEPENDENCIES:
typedef int Int32
----------------------------
***/


void helper_helper_helper_BZ2_hbMakeCodeLengths_1_1_2(Int32 heap[258 + 2], Int32 weight[258 * 2], Int32 nHeap)
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


/*** DEPENDENCIES:
typedef int Int32
----------------------------
***/


// hint:  ['nNodes_ref is a mutable refrence to Int32', 'nHeap_ref is a mutable refrence to Int32', 'n1_ref is a mutable refrence to Int32', 'n2_ref is a mutable refrence to Int32']
void helper_helper_BZ2_hbMakeCodeLengths_1_1(Int32 * const nNodes_ref, Int32 * const nHeap_ref, Int32 * const n1_ref, Int32 * const n2_ref, Int32 heap[258 + 2], Int32 weight[258 * 2], Int32 parent[258 * 2])
{
  Int32 nNodes = *nNodes_ref;
  Int32 nHeap = *nHeap_ref;
  Int32 n1 = *n1_ref;
  Int32 n2 = *n2_ref;
  n1 = heap[1];
  heap[1] = heap[nHeap];
  nHeap -= 1;
  {
    helper_helper_helper_BZ2_hbMakeCodeLengths_1_1_1(heap, weight, nHeap);
  }
  ;
  n2 = heap[1];
  heap[1] = heap[nHeap];
  nHeap -= 1;
  {
    helper_helper_helper_BZ2_hbMakeCodeLengths_1_1_2(heap, weight, nHeap);
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
  *nNodes_ref = nNodes;
  *nHeap_ref = nHeap;
  *n1_ref = n1;
  *n2_ref = n2;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
void helper_helper_helper_BZ2_hbMakeCodeLengths_1_1_2(Int32 heap[258 + 2], Int32 weight[258 * 2], Int32 nHeap)
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


----------------------------
void helper_helper_helper_BZ2_hbMakeCodeLengths_1_1_1(Int32 heap[258 + 2], Int32 weight[258 * 2], Int32 nHeap)
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


----------------------------
***/


// hint:  ['nNodes_ref is a mutable refrence to Int32', 'nHeap_ref is a mutable refrence to Int32', 'n1_ref is a mutable refrence to Int32', 'n2_ref is a mutable refrence to Int32', 'i_ref is a mutable refrence to Int32', 'j_ref is a mutable refrence to Int32', 'k_ref is a mutable refrence to Int32', 'tooLong_ref is a mutable refrence to Bool']
void helper_BZ2_hbMakeCodeLengths_1(Int32 * const nNodes_ref, Int32 * const nHeap_ref, Int32 * const n1_ref, Int32 * const n2_ref, Int32 * const i_ref, Int32 * const j_ref, Int32 * const k_ref, Bool * const tooLong_ref, UChar * const len, Int32 alphaSize, Int32 maxLen, Int32 heap[258 + 2], Int32 weight[258 * 2], Int32 parent[258 * 2])
{
  Int32 nNodes = *nNodes_ref;
  Int32 nHeap = *nHeap_ref;
  Int32 n1 = *n1_ref;
  Int32 n2 = *n2_ref;
  Int32 i = *i_ref;
  Int32 j = *j_ref;
  Int32 k = *k_ref;
  Bool tooLong = *tooLong_ref;
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
    helper_helper_BZ2_hbMakeCodeLengths_1_1(&nNodes, &nHeap, &n1, &n2, heap, weight, parent);
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

  *nNodes_ref = nNodes;
  *nHeap_ref = nHeap;
  *n1_ref = n1;
  *n2_ref = n2;
  *i_ref = i;
  *j_ref = j;
  *k_ref = k;
  *tooLong_ref = tooLong;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
typedef char Char
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
typedef unsigned char UChar
----------------------------
void helper_helper_BZ2_hbMakeCodeLengths_1_1(Int32 * const nNodes_ref, Int32 * const nHeap_ref, Int32 * const n1_ref, Int32 * const n2_ref, Int32 heap[258 + 2], Int32 weight[258 * 2], Int32 parent[258 * 2])
{
  Int32 nNodes = *nNodes_ref;
  Int32 nHeap = *nHeap_ref;
  Int32 n1 = *n1_ref;
  Int32 n2 = *n2_ref;
  n1 = heap[1];
  heap[1] = heap[nHeap];
  nHeap -= 1;
  {
    helper_helper_helper_BZ2_hbMakeCodeLengths_1_1_1(heap, weight, nHeap);
  }
  ;
  n2 = heap[1];
  heap[1] = heap[nHeap];
  nHeap -= 1;
  {
    helper_helper_helper_BZ2_hbMakeCodeLengths_1_1_2(heap, weight, nHeap);
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
  *nNodes_ref = nNodes;
  *nHeap_ref = nHeap;
  *n1_ref = n1;
  *n2_ref = n2;
}


----------------------------
***/


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
    weight[i + 1] = ((freq[i] == 0) ? (1) : (freq[i])) << 8;

  while ((Bool) 1)
  {
    helper_BZ2_hbMakeCodeLengths_1(&nNodes, &nHeap, &n1, &n2, &i, &j, &k, &tooLong, len, alphaSize, maxLen, heap, weight, parent);
  }

}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
void helper_BZ2_hbMakeCodeLengths_1(Int32 * const nNodes_ref, Int32 * const nHeap_ref, Int32 * const n1_ref, Int32 * const n2_ref, Int32 * const i_ref, Int32 * const j_ref, Int32 * const k_ref, Bool * const tooLong_ref, UChar * const len, Int32 alphaSize, Int32 maxLen, Int32 heap[258 + 2], Int32 weight[258 * 2], Int32 parent[258 * 2])
{
  Int32 nNodes = *nNodes_ref;
  Int32 nHeap = *nHeap_ref;
  Int32 n1 = *n1_ref;
  Int32 n2 = *n2_ref;
  Int32 i = *i_ref;
  Int32 j = *j_ref;
  Int32 k = *k_ref;
  Bool tooLong = *tooLong_ref;
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
    helper_helper_BZ2_hbMakeCodeLengths_1_1(&nNodes, &nHeap, &n1, &n2, heap, weight, parent);
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

  *nNodes_ref = nNodes;
  *nHeap_ref = nHeap;
  *n1_ref = n1;
  *n2_ref = n2;
  *i_ref = i;
  *j_ref = j;
  *k_ref = k;
  *tooLong_ref = tooLong;
}


----------------------------
typedef char Char
----------------------------
typedef unsigned char Bool
----------------------------
typedef unsigned char UChar
----------------------------
***/


void BZ2_hbAssignCodes(Int32 *code, UChar *length, Int32 minLen, Int32 maxLen, Int32 alphaSize)
{
  Int32 n;
  Int32 vec;
  Int32 i;
  vec = 0;
  for (n = minLen; n <= maxLen; n += 1)
  {
    for (i = 0; i < alphaSize; i += 1)
      if (length[i] == n)
    {
      code[i] = vec;
      vec += 1;
    }

    ;
    vec <<= 1;
  }

}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
typedef unsigned char UChar
----------------------------
typedef char Char
----------------------------
***/


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


/*** DEPENDENCIES:
typedef int Int32
----------------------------
typedef unsigned char UChar
----------------------------
typedef char Char
----------------------------
***/


