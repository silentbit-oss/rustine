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
        fmap[j - 4] = fmap[j];

      fmap[j - 4] = tmp;
    }

  }
  for (i = hi - 1; i >= lo; i -= 1)
  {
    tmp = fmap[i];
    ec_tmp = eclass[tmp];
    for (j = i + 1; (j <= hi) && (ec_tmp > eclass[fmap[j]]); j += 1)
      fmap[j - 1] = fmap[j];

    fmap[j - 1] = tmp;
  }

}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
typedef unsigned int UInt32
----------------------------
***/


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


/*** DEPENDENCIES:
typedef unsigned char UChar
----------------------------
typedef char Char
----------------------------
***/


// hint:  ['unLo_ref is a mutable refrence to Int32', 'ltLo_ref is a mutable refrence to Int32', 'n_ref is a mutable refrence to Int32']
void helper_helper_helper_fallbackQSort3_1_1_1(Int32 * const unLo_ref, Int32 * const ltLo_ref, Int32 * const n_ref, UInt32 * const fmap, UInt32 * const eclass, UInt32 med, Int32 unHi)
{
  Int32 unLo = *unLo_ref;
  Int32 ltLo = *ltLo_ref;
  Int32 n = *n_ref;
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
  *unLo_ref = unLo;
  *ltLo_ref = ltLo;
  *n_ref = n;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
typedef unsigned int UInt32
----------------------------
***/


// hint:  ['unHi_ref is a mutable refrence to Int32', 'gtHi_ref is a mutable refrence to Int32', 'n_ref is a mutable refrence to Int32']
void helper_helper_helper_fallbackQSort3_1_1_2(Int32 * const unHi_ref, Int32 * const gtHi_ref, Int32 * const n_ref, UInt32 * const fmap, UInt32 * const eclass, UInt32 med, Int32 unLo)
{
  Int32 unHi = *unHi_ref;
  Int32 gtHi = *gtHi_ref;
  Int32 n = *n_ref;
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
  *unHi_ref = unHi;
  *gtHi_ref = gtHi;
  *n_ref = n;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
typedef unsigned int UInt32
----------------------------
***/


// hint:  ['unHi_ref is a mutable refrence to Int32', 'gtHi_ref is a mutable refrence to Int32', 'n_ref is a mutable refrence to Int32']
void helper_helper_helper_mainQSort3_1_1_2(Int32 * const unHi_ref, Int32 * const gtHi_ref, Int32 * const n_ref, UInt32 * const ptr, UChar * const block, Int32 med, Int32 d, Int32 unLo)
{
  Int32 unHi = *unHi_ref;
  Int32 gtHi = *gtHi_ref;
  Int32 n = *n_ref;
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
  *unHi_ref = unHi;
  *gtHi_ref = gtHi;
  *n_ref = n;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
typedef unsigned char UChar
----------------------------
typedef char Char
----------------------------
typedef unsigned int UInt32
----------------------------
***/


// hint:  ['unLo_ref is a mutable refrence to Int32', 'ltLo_ref is a mutable refrence to Int32', 'n_ref is a mutable refrence to Int32']
void helper_helper_helper_mainQSort3_1_1_1(Int32 * const unLo_ref, Int32 * const ltLo_ref, Int32 * const n_ref, UInt32 * const ptr, UChar * const block, Int32 med, Int32 d, Int32 unHi)
{
  Int32 unLo = *unLo_ref;
  Int32 ltLo = *ltLo_ref;
  Int32 n = *n_ref;
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
  *unLo_ref = unLo;
  *ltLo_ref = ltLo;
  *n_ref = n;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
typedef unsigned char UChar
----------------------------
typedef char Char
----------------------------
typedef unsigned int UInt32
----------------------------
***/


// hint:  ['unLo_ref is a mutable refrence to Int32', 'unHi_ref is a mutable refrence to Int32', 'ltLo_ref is a mutable refrence to Int32', 'gtHi_ref is a mutable refrence to Int32', 'n_ref is a mutable refrence to Int32']
void helper_helper_mainQSort3_1_1(Int32 * const unLo_ref, Int32 * const unHi_ref, Int32 * const ltLo_ref, Int32 * const gtHi_ref, Int32 * const n_ref, UInt32 * const ptr, UChar * const block, Int32 med, Int32 d)
{
  Int32 unLo = *unLo_ref;
  Int32 unHi = *unHi_ref;
  Int32 ltLo = *ltLo_ref;
  Int32 gtHi = *gtHi_ref;
  Int32 n = *n_ref;
  while ((Bool) 1)
  {
    helper_helper_helper_mainQSort3_1_1_1(&unLo, &ltLo, &n, ptr, block, med, d, unHi);
  }

  while ((Bool) 1)
  {
    helper_helper_helper_mainQSort3_1_1_2(&unHi, &gtHi, &n, ptr, block, med, d, unLo);
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
  *unLo_ref = unLo;
  *unHi_ref = unHi;
  *ltLo_ref = ltLo;
  *gtHi_ref = gtHi;
  *n_ref = n;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
typedef unsigned int UInt32
----------------------------
void helper_helper_helper_mainQSort3_1_1_2(Int32 * const unHi_ref, Int32 * const gtHi_ref, Int32 * const n_ref, UInt32 * const ptr, UChar * const block, Int32 med, Int32 d, Int32 unLo)
{
  Int32 unHi = *unHi_ref;
  Int32 gtHi = *gtHi_ref;
  Int32 n = *n_ref;
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
  *unHi_ref = unHi;
  *gtHi_ref = gtHi;
  *n_ref = n;
}


----------------------------
typedef char Char
----------------------------
void helper_helper_helper_mainQSort3_1_1_1(Int32 * const unLo_ref, Int32 * const ltLo_ref, Int32 * const n_ref, UInt32 * const ptr, UChar * const block, Int32 med, Int32 d, Int32 unHi)
{
  Int32 unLo = *unLo_ref;
  Int32 ltLo = *ltLo_ref;
  Int32 n = *n_ref;
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
  *unLo_ref = unLo;
  *ltLo_ref = ltLo;
  *n_ref = n;
}


----------------------------
typedef unsigned char UChar
----------------------------
***/


// hint:  ['i1_ref is a mutable refrence to UInt32', 'i2_ref is a mutable refrence to UInt32', 'k_ref is a mutable refrence to Int32', 'c1_ref is a mutable refrence to UChar', 'c2_ref is a mutable refrence to UChar', 's1_ref is a mutable refrence to UInt16', 's2_ref is a mutable refrence to UInt16']
Bool helper_mainGtU_1(UInt32 * const i1_ref, UInt32 * const i2_ref, Int32 * const k_ref, UChar * const c1_ref, UChar * const c2_ref, UInt16 * const s1_ref, UInt16 * const s2_ref, UChar * const block, UInt16 * const quadrant, UInt32 nblock, Int32 * const budget)
{
  UInt32 i1 = *i1_ref;
  UInt32 i2 = *i2_ref;
  Int32 k = *k_ref;
  UChar c1 = *c1_ref;
  UChar c2 = *c2_ref;
  UInt16 s1 = *s1_ref;
  UInt16 s2 = *s2_ref;
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
  *i1_ref = i1;
  *i2_ref = i2;
  *k_ref = k;
  *c1_ref = c1;
  *c2_ref = c2;
  *s1_ref = s1;
  *s2_ref = s2;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
typedef unsigned int UInt32
----------------------------
typedef char Char
----------------------------
typedef unsigned short UInt16
----------------------------
typedef short Int16
----------------------------
typedef unsigned char UChar
----------------------------
***/


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
    helper_mainGtU_1(&i1, &i2, &k, &c1, &c2, &s1, &s2, block, quadrant, nblock, budget);
  }
  while (k >= 0);
  return (Bool) 0;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
Bool helper_mainGtU_1(UInt32 * const i1_ref, UInt32 * const i2_ref, Int32 * const k_ref, UChar * const c1_ref, UChar * const c2_ref, UInt16 * const s1_ref, UInt16 * const s2_ref, UChar * const block, UInt16 * const quadrant, UInt32 nblock, Int32 * const budget)
{
  UInt32 i1 = *i1_ref;
  UInt32 i2 = *i2_ref;
  Int32 k = *k_ref;
  UChar c1 = *c1_ref;
  UChar c2 = *c2_ref;
  UInt16 s1 = *s1_ref;
  UInt16 s2 = *s2_ref;
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
  *i1_ref = i1;
  *i2_ref = i2;
  *k_ref = k;
  *c1_ref = c1;
  *c2_ref = c2;
  *s1_ref = s1;
  *s2_ref = s2;
}


----------------------------
typedef unsigned int UInt32
----------------------------
typedef char Char
----------------------------
typedef unsigned short UInt16
----------------------------
typedef short Int16
----------------------------
typedef unsigned char UChar
----------------------------
***/


// hint:  ['j_ref is a mutable refrence to Int32', 'v_ref is a mutable refrence to UInt32']
void helper_helper_mainSimpleSort_1_1(Int32 * const j_ref, UInt32 * const v_ref, UInt32 * const ptr, UChar * const block, UInt16 * const quadrant, Int32 nblock, Int32 lo, Int32 hi, Int32 d, Int32 * const budget, Int32 i, Int32 h)
{
  Int32 j = *j_ref;
  UInt32 v = *v_ref;
  if (i > hi)
    break;
  v = ptr[i];
  j = i;
  while (mainGtU(ptr[j - h] + d, v + d, block, quadrant, nblock, budget))
  {
    ptr[j] = ptr[j - h];
    j = j - h;
    if (j <= ((lo + h) - 1))
      break;
  }

  ptr[j] = v;
  i++;
  if (i > hi)
    break;
  v = ptr[i];
  j = i;
  while (mainGtU(ptr[j - h] + d, v + d, block, quadrant, nblock, budget))
  {
    ptr[j] = ptr[j - h];
    j = j - h;
    if (j <= ((lo + h) - 1))
      break;
  }

  ptr[j] = v;
  i++;
  if (i > hi)
    break;
  v = ptr[i];
  j = i;
  while (mainGtU(ptr[j - h] + d, v + d, block, quadrant, nblock, budget))
  {
    ptr[j] = ptr[j - h];
    j = j - h;
    if (j <= ((lo + h) - 1))
      break;
  }

  ptr[j] = v;
  i++;
  if ((*budget) < 0)
    return;
  *j_ref = j;
  *v_ref = v;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
typedef unsigned int UInt32
----------------------------
typedef char Char
----------------------------
typedef unsigned short UInt16
----------------------------
typedef short Int16
----------------------------
typedef unsigned char UChar
----------------------------
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
    helper_mainGtU_1(&i1, &i2, &k, &c1, &c2, &s1, &s2, block, quadrant, nblock, budget);
  }
  while (k >= 0);
  return (Bool) 0;
}


----------------------------
***/


// hint:  ['i_ref is a mutable refrence to Int32', 'j_ref is a mutable refrence to Int32', 'h_ref is a mutable refrence to Int32', 'v_ref is a mutable refrence to UInt32']
void helper_mainSimpleSort_1(Int32 * const i_ref, Int32 * const j_ref, Int32 * const h_ref, UInt32 * const v_ref, UInt32 * const ptr, UChar * const block, UInt16 * const quadrant, Int32 nblock, Int32 lo, Int32 hi, Int32 d, Int32 * const budget, Int32 hp)
{
  Int32 i = *i_ref;
  Int32 j = *j_ref;
  Int32 h = *h_ref;
  UInt32 v = *v_ref;
  h = incs[hp];
  i = lo + h;
  while ((Bool) 1)
  {
    helper_helper_mainSimpleSort_1_1(&j, &v, ptr, block, quadrant, nblock, lo, hi, d, budget, i, h);
  }

  *i_ref = i;
  *j_ref = j;
  *h_ref = h;
  *v_ref = v;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
typedef unsigned int UInt32
----------------------------
typedef char Char
----------------------------
void helper_helper_mainSimpleSort_1_1(Int32 * const j_ref, UInt32 * const v_ref, UInt32 * const ptr, UChar * const block, UInt16 * const quadrant, Int32 nblock, Int32 lo, Int32 hi, Int32 d, Int32 * const budget, Int32 i, Int32 h)
{
  Int32 j = *j_ref;
  UInt32 v = *v_ref;
  if (i > hi)
    break;
  v = ptr[i];
  j = i;
  while (mainGtU(ptr[j - h] + d, v + d, block, quadrant, nblock, budget))
  {
    ptr[j] = ptr[j - h];
    j = j - h;
    if (j <= ((lo + h) - 1))
      break;
  }

  ptr[j] = v;
  i++;
  if (i > hi)
    break;
  v = ptr[i];
  j = i;
  while (mainGtU(ptr[j - h] + d, v + d, block, quadrant, nblock, budget))
  {
    ptr[j] = ptr[j - h];
    j = j - h;
    if (j <= ((lo + h) - 1))
      break;
  }

  ptr[j] = v;
  i++;
  if (i > hi)
    break;
  v = ptr[i];
  j = i;
  while (mainGtU(ptr[j - h] + d, v + d, block, quadrant, nblock, budget))
  {
    ptr[j] = ptr[j - h];
    j = j - h;
    if (j <= ((lo + h) - 1))
      break;
  }

  ptr[j] = v;
  i++;
  if ((*budget) < 0)
    return;
  *j_ref = j;
  *v_ref = v;
}


----------------------------
typedef unsigned short UInt16
----------------------------
typedef short Int16
----------------------------
static Int32 incs[14] = {1, 4, 13, 40, 121, 364, 1093, 3280, 9841, 29524, 88573, 265720, 797161, 2391484}
----------------------------
typedef unsigned char UChar
----------------------------
***/


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
    hp++;

  hp += 1;
  hp -= 1;
  for (; hp >= 0; hp--)
  {
    helper_mainSimpleSort_1(&i, &j, &h, &v, ptr, block, quadrant, nblock, lo, hi, d, budget, hp);
  }

}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
typedef unsigned int UInt32
----------------------------
void helper_mainSimpleSort_1(Int32 * const i_ref, Int32 * const j_ref, Int32 * const h_ref, UInt32 * const v_ref, UInt32 * const ptr, UChar * const block, UInt16 * const quadrant, Int32 nblock, Int32 lo, Int32 hi, Int32 d, Int32 * const budget, Int32 hp)
{
  Int32 i = *i_ref;
  Int32 j = *j_ref;
  Int32 h = *h_ref;
  UInt32 v = *v_ref;
  h = incs[hp];
  i = lo + h;
  while ((Bool) 1)
  {
    helper_helper_mainSimpleSort_1_1(&j, &v, ptr, block, quadrant, nblock, lo, hi, d, budget, i, h);
  }

  *i_ref = i;
  *j_ref = j;
  *h_ref = h;
  *v_ref = v;
}


----------------------------
typedef char Char
----------------------------
typedef unsigned short UInt16
----------------------------
typedef short Int16
----------------------------
static Int32 incs[14] = {1, 4, 13, 40, 121, 364, 1093, 3280, 9841, 29524, 88573, 265720, 797161, 2391484}
----------------------------
typedef unsigned char UChar
----------------------------
***/


// hint:  ['unLo_ref is a mutable refrence to Int32', 'unHi_ref is a mutable refrence to Int32', 'ltLo_ref is a mutable refrence to Int32', 'gtHi_ref is a mutable refrence to Int32', 'n_ref is a mutable refrence to Int32', 'm_ref is a mutable refrence to Int32', 'med_ref is a mutable refrence to Int32', 'sp_ref is a mutable refrence to Int32', 'lo_ref is a mutable refrence to Int32', 'hi_ref is a mutable refrence to Int32', 'd_ref is a mutable refrence to Int32']
void helper_mainQSort3_1(Int32 * const unLo_ref, Int32 * const unHi_ref, Int32 * const ltLo_ref, Int32 * const gtHi_ref, Int32 * const n_ref, Int32 * const m_ref, Int32 * const med_ref, Int32 * const sp_ref, Int32 * const lo_ref, Int32 * const hi_ref, Int32 * const d_ref, UInt32 * const ptr, UChar * const block, UInt16 * const quadrant, Int32 nblock, Int32 * const budget, Int32 stackLo[100], Int32 stackHi[100], Int32 stackD[100], Int32 nextLo[3], Int32 nextHi[3], Int32 nextD[3])
{
  Int32 unLo = *unLo_ref;
  Int32 unHi = *unHi_ref;
  Int32 ltLo = *ltLo_ref;
  Int32 gtHi = *gtHi_ref;
  Int32 n = *n_ref;
  Int32 m = *m_ref;
  Int32 med = *med_ref;
  Int32 sp = *sp_ref;
  Int32 lo = *lo_ref;
  Int32 hi = *hi_ref;
  Int32 d = *d_ref;
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
    helper_helper_mainQSort3_1_1(&unLo, &unHi, &ltLo, &gtHi, &n, ptr, block, med, d);
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
  *unLo_ref = unLo;
  *unHi_ref = unHi;
  *ltLo_ref = ltLo;
  *gtHi_ref = gtHi;
  *n_ref = n;
  *m_ref = m;
  *med_ref = med;
  *sp_ref = sp;
  *lo_ref = lo;
  *hi_ref = hi;
  *d_ref = d;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
void helper_helper_mainQSort3_1_1(Int32 * const unLo_ref, Int32 * const unHi_ref, Int32 * const ltLo_ref, Int32 * const gtHi_ref, Int32 * const n_ref, UInt32 * const ptr, UChar * const block, Int32 med, Int32 d)
{
  Int32 unLo = *unLo_ref;
  Int32 unHi = *unHi_ref;
  Int32 ltLo = *ltLo_ref;
  Int32 gtHi = *gtHi_ref;
  Int32 n = *n_ref;
  while ((Bool) 1)
  {
    helper_helper_helper_mainQSort3_1_1_1(&unLo, &ltLo, &n, ptr, block, med, d, unHi);
  }

  while ((Bool) 1)
  {
    helper_helper_helper_mainQSort3_1_1_2(&unHi, &gtHi, &n, ptr, block, med, d, unLo);
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
  *unLo_ref = unLo;
  *unHi_ref = unHi;
  *ltLo_ref = ltLo;
  *gtHi_ref = gtHi;
  *n_ref = n;
}


----------------------------
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


----------------------------
typedef unsigned int UInt32
----------------------------
typedef char Char
----------------------------
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
    hp++;

  hp += 1;
  hp -= 1;
  for (; hp >= 0; hp--)
  {
    helper_mainSimpleSort_1(&i, &j, &h, &v, ptr, block, quadrant, nblock, lo, hi, d, budget, hp);
  }

}


----------------------------
typedef unsigned short UInt16
----------------------------
typedef short Int16
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
typedef unsigned char UChar
----------------------------
***/


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
    helper_mainQSort3_1(&unLo, &unHi, &ltLo, &gtHi, &n, &m, &med, &sp, &lo, &hi, &d, ptr, block, quadrant, nblock, budget, stackLo, stackHi, stackD, nextLo, nextHi, nextD);
  }

}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
void helper_mainQSort3_1(Int32 * const unLo_ref, Int32 * const unHi_ref, Int32 * const ltLo_ref, Int32 * const gtHi_ref, Int32 * const n_ref, Int32 * const m_ref, Int32 * const med_ref, Int32 * const sp_ref, Int32 * const lo_ref, Int32 * const hi_ref, Int32 * const d_ref, UInt32 * const ptr, UChar * const block, UInt16 * const quadrant, Int32 nblock, Int32 * const budget, Int32 stackLo[100], Int32 stackHi[100], Int32 stackD[100], Int32 nextLo[3], Int32 nextHi[3], Int32 nextD[3])
{
  Int32 unLo = *unLo_ref;
  Int32 unHi = *unHi_ref;
  Int32 ltLo = *ltLo_ref;
  Int32 gtHi = *gtHi_ref;
  Int32 n = *n_ref;
  Int32 m = *m_ref;
  Int32 med = *med_ref;
  Int32 sp = *sp_ref;
  Int32 lo = *lo_ref;
  Int32 hi = *hi_ref;
  Int32 d = *d_ref;
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
    helper_helper_mainQSort3_1_1(&unLo, &unHi, &ltLo, &gtHi, &n, ptr, block, med, d);
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
  *unLo_ref = unLo;
  *unHi_ref = unHi;
  *ltLo_ref = ltLo;
  *gtHi_ref = gtHi;
  *n_ref = n;
  *m_ref = m;
  *med_ref = med;
  *sp_ref = sp;
  *lo_ref = lo;
  *hi_ref = hi;
  *d_ref = d;
}


----------------------------
typedef unsigned int UInt32
----------------------------
typedef char Char
----------------------------
typedef unsigned short UInt16
----------------------------
typedef short Int16
----------------------------
typedef unsigned char UChar
----------------------------
***/


// hint:  ['j_ref is a mutable refrence to Int32', 'k_ref is a mutable refrence to Int32', 'c1_ref is a mutable refrence to UChar']
void helper_helper_mainSort_2_1(Int32 * const j_ref, Int32 * const k_ref, UChar * const c1_ref, UInt32 * const ptr, UChar * const block, UInt32 * const ftab, Bool bigDone[256], Int32 copyStart[256], Int32 copyEnd[256], Int32 nblock, Int32 ss)
{
  Int32 j = *j_ref;
  Int32 k = *k_ref;
  UChar c1 = *c1_ref;
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

  *j_ref = j;
  *k_ref = k;
  *c1_ref = c1;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
typedef unsigned int UInt32
----------------------------
typedef char Char
----------------------------
typedef unsigned char Bool
----------------------------
typedef unsigned char UChar
----------------------------
***/


// hint:  ['nblock_ref is a mutable refrence to Int32', 'j_ref is a mutable refrence to Int32', 'k_ref is a mutable refrence to Int32', 'ss_ref is a mutable refrence to Int32', 'sb_ref is a mutable refrence to Int32', 'c1_ref is a mutable refrence to UChar', 'numQSorted_ref is a mutable refrence to Int32']
void helper_mainSort_2(Int32 * const nblock_ref, Int32 * const j_ref, Int32 * const k_ref, Int32 * const ss_ref, Int32 * const sb_ref, UChar * const c1_ref, Int32 * const numQSorted_ref, UInt32 * const ptr, UChar * const block, UInt16 * const quadrant, UInt32 * const ftab, Int32 verb, Int32 * const budget, Int32 i, Int32 runningOrder[256], Bool bigDone[256], Int32 copyStart[256], Int32 copyEnd[256])
{
  Int32 nblock = *nblock_ref;
  Int32 j = *j_ref;
  Int32 k = *k_ref;
  Int32 ss = *ss_ref;
  Int32 sb = *sb_ref;
  UChar c1 = *c1_ref;
  Int32 numQSorted = *numQSorted_ref;
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
    helper_helper_mainSort_2_1(&j, &k, &c1, ptr, block, ftab, bigDone, copyStart, copyEnd, nblock, ss);
  }
  {
    if (!(((copyStart[ss] - 1) == copyEnd[ss]) || ((copyStart[ss] == 0) && (copyEnd[ss] == (nblock - 1)))))
    {
      BZ2_bz__AssertH__fail(1007);
    }
  }
  for (j = 0; j <= 255; j += 1)
    ftab[(j << 8) + ss] |= 1 << 21;

  bigDone[ss] = (Bool) 1;
  if (i < 255)
  {
    Int32 bbStart = ftab[ss << 8] & (~(1 << 21));
    Int32 bbSize = (ftab[(ss + 1) << 8] & (~(1 << 21))) - bbStart;
    Int32 shifts = 0;
    while ((bbSize >> shifts) > 65534)
      shifts++;

    shifts += 1;
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
  *nblock_ref = nblock;
  *j_ref = j;
  *k_ref = k;
  *ss_ref = ss;
  *sb_ref = sb;
  *c1_ref = c1;
  *numQSorted_ref = numQSorted;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
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
    helper_mainQSort3_1(&unLo, &unHi, &ltLo, &gtHi, &n, &m, &med, &sp, &lo, &hi, &d, ptr, block, quadrant, nblock, budget, stackLo, stackHi, stackD, nextLo, nextHi, nextD);
  }

}


----------------------------
typedef unsigned int UInt32
----------------------------
typedef char Char
----------------------------
typedef unsigned short UInt16
----------------------------
typedef short Int16
----------------------------
typedef unsigned char Bool
----------------------------
void helper_helper_mainSort_2_1(Int32 * const j_ref, Int32 * const k_ref, UChar * const c1_ref, UInt32 * const ptr, UChar * const block, UInt32 * const ftab, Bool bigDone[256], Int32 copyStart[256], Int32 copyEnd[256], Int32 nblock, Int32 ss)
{
  Int32 j = *j_ref;
  Int32 k = *k_ref;
  UChar c1 = *c1_ref;
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

  *j_ref = j;
  *k_ref = k;
  *c1_ref = c1;
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
typedef unsigned char UChar
----------------------------
***/


// hint:  ['j_ref is a mutable refrence to Int32', 's_ref is a mutable refrence to UInt16']
void helper_mainSort_1(Int32 * const j_ref, UInt16 * const s_ref, UInt32 * const ptr, UChar * const block, UInt32 * const ftab, Int32 i)
{
  Int32 j = *j_ref;
  UInt16 s = *s_ref;
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
  *j_ref = j;
  *s_ref = s;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
typedef unsigned int UInt32
----------------------------
typedef char Char
----------------------------
typedef unsigned short UInt16
----------------------------
typedef short Int16
----------------------------
typedef unsigned char UChar
----------------------------
***/


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
    ftab[i] = 0;

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
    ftab[i] += ftab[i - 1];

  s = block[0] << 8;
  i = nblock - 1;
  for (; i >= 3; i -= 4)
  {
    helper_mainSort_1(&j, &s, ptr, block, ftab, i);
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
      h = (3 * h) + 1;
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
    helper_mainSort_2(&nblock, &j, &k, &ss, &sb, &c1, &numQSorted, ptr, block, quadrant, ftab, verb, budget, i, runningOrder, bigDone, copyStart, copyEnd);
  }

  if (verb >= 4)
  {
    fprintf(stderr, "        %d pointers, %d sorted, %d scanned\n", nblock, numQSorted, nblock - numQSorted);
  }
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
void helper_mainSort_2(Int32 * const nblock_ref, Int32 * const j_ref, Int32 * const k_ref, Int32 * const ss_ref, Int32 * const sb_ref, UChar * const c1_ref, Int32 * const numQSorted_ref, UInt32 * const ptr, UChar * const block, UInt16 * const quadrant, UInt32 * const ftab, Int32 verb, Int32 * const budget, Int32 i, Int32 runningOrder[256], Bool bigDone[256], Int32 copyStart[256], Int32 copyEnd[256])
{
  Int32 nblock = *nblock_ref;
  Int32 j = *j_ref;
  Int32 k = *k_ref;
  Int32 ss = *ss_ref;
  Int32 sb = *sb_ref;
  UChar c1 = *c1_ref;
  Int32 numQSorted = *numQSorted_ref;
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
    helper_helper_mainSort_2_1(&j, &k, &c1, ptr, block, ftab, bigDone, copyStart, copyEnd, nblock, ss);
  }
  {
    if (!(((copyStart[ss] - 1) == copyEnd[ss]) || ((copyStart[ss] == 0) && (copyEnd[ss] == (nblock - 1)))))
    {
      BZ2_bz__AssertH__fail(1007);
    }
  }
  for (j = 0; j <= 255; j += 1)
    ftab[(j << 8) + ss] |= 1 << 21;

  bigDone[ss] = (Bool) 1;
  if (i < 255)
  {
    Int32 bbStart = ftab[ss << 8] & (~(1 << 21));
    Int32 bbSize = (ftab[(ss + 1) << 8] & (~(1 << 21))) - bbStart;
    Int32 shifts = 0;
    while ((bbSize >> shifts) > 65534)
      shifts++;

    shifts += 1;
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
  *nblock_ref = nblock;
  *j_ref = j;
  *k_ref = k;
  *ss_ref = ss;
  *sb_ref = sb;
  *c1_ref = c1;
  *numQSorted_ref = numQSorted;
}


----------------------------
typedef unsigned int UInt32
----------------------------
void helper_mainSort_1(Int32 * const j_ref, UInt16 * const s_ref, UInt32 * const ptr, UChar * const block, UInt32 * const ftab, Int32 i)
{
  Int32 j = *j_ref;
  UInt16 s = *s_ref;
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
  *j_ref = j;
  *s_ref = s;
}


----------------------------
typedef char Char
----------------------------
typedef unsigned short UInt16
----------------------------
typedef short Int16
----------------------------
typedef unsigned char Bool
----------------------------
typedef unsigned char UChar
----------------------------
***/


// hint:  ['unLo_ref is a mutable refrence to Int32', 'unHi_ref is a mutable refrence to Int32', 'ltLo_ref is a mutable refrence to Int32', 'gtHi_ref is a mutable refrence to Int32', 'n_ref is a mutable refrence to Int32']
void helper_helper_fallbackQSort3_1_1(Int32 * const unLo_ref, Int32 * const unHi_ref, Int32 * const ltLo_ref, Int32 * const gtHi_ref, Int32 * const n_ref, UInt32 * const fmap, UInt32 * const eclass, UInt32 med)
{
  Int32 unLo = *unLo_ref;
  Int32 unHi = *unHi_ref;
  Int32 ltLo = *ltLo_ref;
  Int32 gtHi = *gtHi_ref;
  Int32 n = *n_ref;
  while (1)
  {
    helper_helper_helper_fallbackQSort3_1_1_1(&unLo, &ltLo, &n, fmap, eclass, med, unHi);
  }

  while (1)
  {
    helper_helper_helper_fallbackQSort3_1_1_2(&unHi, &gtHi, &n, fmap, eclass, med, unLo);
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
  *unLo_ref = unLo;
  *unHi_ref = unHi;
  *ltLo_ref = ltLo;
  *gtHi_ref = gtHi;
  *n_ref = n;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
void helper_helper_helper_fallbackQSort3_1_1_1(Int32 * const unLo_ref, Int32 * const ltLo_ref, Int32 * const n_ref, UInt32 * const fmap, UInt32 * const eclass, UInt32 med, Int32 unHi)
{
  Int32 unLo = *unLo_ref;
  Int32 ltLo = *ltLo_ref;
  Int32 n = *n_ref;
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
  *unLo_ref = unLo;
  *ltLo_ref = ltLo;
  *n_ref = n;
}


----------------------------
typedef unsigned int UInt32
----------------------------
void helper_helper_helper_fallbackQSort3_1_1_2(Int32 * const unHi_ref, Int32 * const gtHi_ref, Int32 * const n_ref, UInt32 * const fmap, UInt32 * const eclass, UInt32 med, Int32 unLo)
{
  Int32 unHi = *unHi_ref;
  Int32 gtHi = *gtHi_ref;
  Int32 n = *n_ref;
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
  *unHi_ref = unHi;
  *gtHi_ref = gtHi;
  *n_ref = n;
}


----------------------------
***/


// hint:  ['unLo_ref is a mutable refrence to Int32', 'unHi_ref is a mutable refrence to Int32', 'ltLo_ref is a mutable refrence to Int32', 'gtHi_ref is a mutable refrence to Int32', 'n_ref is a mutable refrence to Int32', 'm_ref is a mutable refrence to Int32', 'sp_ref is a mutable refrence to Int32', 'lo_ref is a mutable refrence to Int32', 'hi_ref is a mutable refrence to Int32', 'med_ref is a mutable refrence to UInt32', 'r_ref is a mutable refrence to UInt32', 'r3_ref is a mutable refrence to UInt32']
void helper_fallbackQSort3_1(Int32 * const unLo_ref, Int32 * const unHi_ref, Int32 * const ltLo_ref, Int32 * const gtHi_ref, Int32 * const n_ref, Int32 * const m_ref, Int32 * const sp_ref, Int32 * const lo_ref, Int32 * const hi_ref, UInt32 * const med_ref, UInt32 * const r_ref, UInt32 * const r3_ref, UInt32 * const fmap, UInt32 * const eclass, Int32 stackLo[100], Int32 stackHi[100])
{
  Int32 unLo = *unLo_ref;
  Int32 unHi = *unHi_ref;
  Int32 ltLo = *ltLo_ref;
  Int32 gtHi = *gtHi_ref;
  Int32 n = *n_ref;
  Int32 m = *m_ref;
  Int32 sp = *sp_ref;
  Int32 lo = *lo_ref;
  Int32 hi = *hi_ref;
  UInt32 med = *med_ref;
  UInt32 r = *r_ref;
  UInt32 r3 = *r3_ref;
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
    helper_helper_fallbackQSort3_1_1(&unLo, &unHi, &ltLo, &gtHi, &n, fmap, eclass, med);
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
  *unLo_ref = unLo;
  *unHi_ref = unHi;
  *ltLo_ref = ltLo;
  *gtHi_ref = gtHi;
  *n_ref = n;
  *m_ref = m;
  *sp_ref = sp;
  *lo_ref = lo;
  *hi_ref = hi;
  *med_ref = med;
  *r_ref = r;
  *r3_ref = r3;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
void helper_helper_fallbackQSort3_1_1(Int32 * const unLo_ref, Int32 * const unHi_ref, Int32 * const ltLo_ref, Int32 * const gtHi_ref, Int32 * const n_ref, UInt32 * const fmap, UInt32 * const eclass, UInt32 med)
{
  Int32 unLo = *unLo_ref;
  Int32 unHi = *unHi_ref;
  Int32 ltLo = *ltLo_ref;
  Int32 gtHi = *gtHi_ref;
  Int32 n = *n_ref;
  while (1)
  {
    helper_helper_helper_fallbackQSort3_1_1_1(&unLo, &ltLo, &n, fmap, eclass, med, unHi);
  }

  while (1)
  {
    helper_helper_helper_fallbackQSort3_1_1_2(&unHi, &gtHi, &n, fmap, eclass, med, unLo);
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
  *unLo_ref = unLo;
  *unHi_ref = unHi;
  *ltLo_ref = ltLo;
  *gtHi_ref = gtHi;
  *n_ref = n;
}


----------------------------
typedef unsigned int UInt32
----------------------------
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
        fmap[j - 4] = fmap[j];

      fmap[j - 4] = tmp;
    }

  }
  for (i = hi - 1; i >= lo; i -= 1)
  {
    tmp = fmap[i];
    ec_tmp = eclass[tmp];
    for (j = i + 1; (j <= hi) && (ec_tmp > eclass[fmap[j]]); j += 1)
      fmap[j - 1] = fmap[j];

    fmap[j - 1] = tmp;
  }

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
***/


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
    helper_fallbackQSort3_1(&unLo, &unHi, &ltLo, &gtHi, &n, &m, &sp, &lo, &hi, &med, &r, &r3, fmap, eclass, stackLo, stackHi);
  }

}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
void helper_fallbackQSort3_1(Int32 * const unLo_ref, Int32 * const unHi_ref, Int32 * const ltLo_ref, Int32 * const gtHi_ref, Int32 * const n_ref, Int32 * const m_ref, Int32 * const sp_ref, Int32 * const lo_ref, Int32 * const hi_ref, UInt32 * const med_ref, UInt32 * const r_ref, UInt32 * const r3_ref, UInt32 * const fmap, UInt32 * const eclass, Int32 stackLo[100], Int32 stackHi[100])
{
  Int32 unLo = *unLo_ref;
  Int32 unHi = *unHi_ref;
  Int32 ltLo = *ltLo_ref;
  Int32 gtHi = *gtHi_ref;
  Int32 n = *n_ref;
  Int32 m = *m_ref;
  Int32 sp = *sp_ref;
  Int32 lo = *lo_ref;
  Int32 hi = *hi_ref;
  UInt32 med = *med_ref;
  UInt32 r = *r_ref;
  UInt32 r3 = *r3_ref;
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
    helper_helper_fallbackQSort3_1_1(&unLo, &unHi, &ltLo, &gtHi, &n, fmap, eclass, med);
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
  *unLo_ref = unLo;
  *unHi_ref = unHi;
  *ltLo_ref = ltLo;
  *gtHi_ref = gtHi;
  *n_ref = n;
  *m_ref = m;
  *sp_ref = sp;
  *lo_ref = lo;
  *hi_ref = hi;
  *med_ref = med;
  *r_ref = r;
  *r3_ref = r3;
}


----------------------------
typedef unsigned int UInt32
----------------------------
***/


// hint:  ['i_ref is a mutable refrence to Int32', 'k_ref is a mutable refrence to Int32', 'l_ref is a mutable refrence to Int32', 'r_ref is a mutable refrence to Int32', 'cc_ref is a mutable refrence to Int32', 'cc1_ref is a mutable refrence to Int32', 'nNotDone_ref is a mutable refrence to Int32']
void helper_helper_fallbackSort_1_1(Int32 * const i_ref, Int32 * const k_ref, Int32 * const l_ref, Int32 * const r_ref, Int32 * const cc_ref, Int32 * const cc1_ref, Int32 * const nNotDone_ref, UInt32 * const fmap, UInt32 * const eclass, UInt32 * const bhtab, Int32 nblock)
{
  Int32 i = *i_ref;
  Int32 k = *k_ref;
  Int32 l = *l_ref;
  Int32 r = *r_ref;
  Int32 cc = *cc_ref;
  Int32 cc1 = *cc1_ref;
  Int32 nNotDone = *nNotDone_ref;
  k = r + 1;
  while ((bhtab[k >> 5] & (((UInt32) 1) << (k & 31))) && (k & 0x01f))
    k++;

  k += 1;
  if (bhtab[k >> 5] & (((UInt32) 1) << (k & 31)))
  {
    while (bhtab[k >> 5] == 0xffffffff)
      k += 32;

    while (bhtab[k >> 5] & (((UInt32) 1) << (k & 31)))
      k++;

    k += 1;
  }
  l = k - 1;
  if (l >= nblock)
  {
    break;
  }
  while ((!(bhtab[k >> 5] & (((UInt32) 1) << (k & 31)))) && (k & 0x01f))
    k++;

  k += 1;
  if (!(bhtab[k >> 5] & (((UInt32) 1) << (k & 31))))
  {
    while (bhtab[k >> 5] == 0x00000000)
      k += 32;

    while (!(bhtab[k >> 5] & (((UInt32) 1) << (k & 31))))
      k++;

    k += 1;
  }
  r = k - 1;
  if (r >= nblock)
    break;
  if (r > l)
  {
    nNotDone += (r - l) + 1;
    fallbackQSort3(fmap, eclass, l, r);
    cc = -1;
    for (i = l; i <= r; i++)
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
  *i_ref = i;
  *k_ref = k;
  *l_ref = l;
  *r_ref = r;
  *cc_ref = cc;
  *cc1_ref = cc1;
  *nNotDone_ref = nNotDone;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
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
    helper_fallbackQSort3_1(&unLo, &unHi, &ltLo, &gtHi, &n, &m, &sp, &lo, &hi, &med, &r, &r3, fmap, eclass, stackLo, stackHi);
  }

}


----------------------------
typedef unsigned int UInt32
----------------------------
***/


// hint:  ['H_ref is a mutable refrence to Int32', 'i_ref is a mutable refrence to Int32', 'j_ref is a mutable refrence to Int32', 'k_ref is a mutable refrence to Int32', 'l_ref is a mutable refrence to Int32', 'r_ref is a mutable refrence to Int32', 'cc_ref is a mutable refrence to Int32', 'cc1_ref is a mutable refrence to Int32', 'nNotDone_ref is a mutable refrence to Int32']
void helper_fallbackSort_1(Int32 * const H_ref, Int32 * const i_ref, Int32 * const j_ref, Int32 * const k_ref, Int32 * const l_ref, Int32 * const r_ref, Int32 * const cc_ref, Int32 * const cc1_ref, Int32 * const nNotDone_ref, UInt32 * const fmap, UInt32 * const eclass, UInt32 * const bhtab, Int32 nblock, Int32 verb)
{
  Int32 H = *H_ref;
  Int32 i = *i_ref;
  Int32 j = *j_ref;
  Int32 k = *k_ref;
  Int32 l = *l_ref;
  Int32 r = *r_ref;
  Int32 cc = *cc_ref;
  Int32 cc1 = *cc1_ref;
  Int32 nNotDone = *nNotDone_ref;
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
    helper_helper_fallbackSort_1_1(&i, &k, &l, &r, &cc, &cc1, &nNotDone, fmap, eclass, bhtab, nblock);
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
  *H_ref = H;
  *i_ref = i;
  *j_ref = j;
  *k_ref = k;
  *l_ref = l;
  *r_ref = r;
  *cc_ref = cc;
  *cc1_ref = cc1;
  *nNotDone_ref = nNotDone;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
void helper_helper_fallbackSort_1_1(Int32 * const i_ref, Int32 * const k_ref, Int32 * const l_ref, Int32 * const r_ref, Int32 * const cc_ref, Int32 * const cc1_ref, Int32 * const nNotDone_ref, UInt32 * const fmap, UInt32 * const eclass, UInt32 * const bhtab, Int32 nblock)
{
  Int32 i = *i_ref;
  Int32 k = *k_ref;
  Int32 l = *l_ref;
  Int32 r = *r_ref;
  Int32 cc = *cc_ref;
  Int32 cc1 = *cc1_ref;
  Int32 nNotDone = *nNotDone_ref;
  k = r + 1;
  while ((bhtab[k >> 5] & (((UInt32) 1) << (k & 31))) && (k & 0x01f))
    k++;

  k += 1;
  if (bhtab[k >> 5] & (((UInt32) 1) << (k & 31)))
  {
    while (bhtab[k >> 5] == 0xffffffff)
      k += 32;

    while (bhtab[k >> 5] & (((UInt32) 1) << (k & 31)))
      k++;

    k += 1;
  }
  l = k - 1;
  if (l >= nblock)
  {
    break;
  }
  while ((!(bhtab[k >> 5] & (((UInt32) 1) << (k & 31)))) && (k & 0x01f))
    k++;

  k += 1;
  if (!(bhtab[k >> 5] & (((UInt32) 1) << (k & 31))))
  {
    while (bhtab[k >> 5] == 0x00000000)
      k += 32;

    while (!(bhtab[k >> 5] & (((UInt32) 1) << (k & 31))))
      k++;

    k += 1;
  }
  r = k - 1;
  if (r >= nblock)
    break;
  if (r > l)
  {
    nNotDone += (r - l) + 1;
    fallbackQSort3(fmap, eclass, l, r);
    cc = -1;
    for (i = l; i <= r; i++)
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
  *i_ref = i;
  *k_ref = k;
  *l_ref = l;
  *r_ref = r;
  *cc_ref = cc;
  *cc1_ref = cc1;
  *nNotDone_ref = nNotDone;
}


----------------------------
typedef unsigned int UInt32
----------------------------
***/


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
    ftab[i] = 0;

  for (i = 0; i < nblock; i += 1)
    ftab[eclass8[i]]++;

  for (i = 0; i < 256; i += 1)
    ftabCopy[i] = ftab[i];

  for (i = 1; i < 257; i += 1)
    ftab[i] += ftab[i - 1];

  for (i = 0; i < nblock; i += 1)
  {
    j = eclass8[i];
    k = ftab[j] - 1;
    ftab[j] = k;
    fmap[k] = i;
  }

  nBhtab = 2 + (nblock / 32);
  for (i = 0; i < nBhtab; i += 1)
    bhtab[i] = 0;

  for (i = 0; i < 256; i += 1)
    bhtab[ftab[i] >> 5] |= ((UInt32) 1) << (ftab[i] & 31);

  for (i = 0; i < 32; i += 1)
  {
    bhtab[(nblock + (2 * i)) >> 5] |= ((UInt32) 1) << ((nblock + (2 * i)) & 31);
    bhtab[((nblock + (2 * i)) + 1) >> 5] &= ~(((UInt32) 1) << (((nblock + (2 * i)) + 1) & 31));
  }

  H = 1;
  while (1)
  {
    helper_fallbackSort_1(&H, &i, &j, &k, &l, &r, &cc, &cc1, &nNotDone, fmap, eclass, bhtab, nblock, verb);
  }

  if (verb >= 4)
  {
    fprintf(stderr, "        reconstructing block ...\n");
  }
  j = 0;
  for (i = 0; i < nblock; i += 1)
  {
    while (ftabCopy[j] == 0)
      j++;

    j += 1;
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


/*** DEPENDENCIES:
typedef int Int32
----------------------------
void helper_fallbackSort_1(Int32 * const H_ref, Int32 * const i_ref, Int32 * const j_ref, Int32 * const k_ref, Int32 * const l_ref, Int32 * const r_ref, Int32 * const cc_ref, Int32 * const cc1_ref, Int32 * const nNotDone_ref, UInt32 * const fmap, UInt32 * const eclass, UInt32 * const bhtab, Int32 nblock, Int32 verb)
{
  Int32 H = *H_ref;
  Int32 i = *i_ref;
  Int32 j = *j_ref;
  Int32 k = *k_ref;
  Int32 l = *l_ref;
  Int32 r = *r_ref;
  Int32 cc = *cc_ref;
  Int32 cc1 = *cc1_ref;
  Int32 nNotDone = *nNotDone_ref;
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
    helper_helper_fallbackSort_1_1(&i, &k, &l, &r, &cc, &cc1, &nNotDone, fmap, eclass, bhtab, nblock);
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
  *H_ref = H;
  *i_ref = i;
  *j_ref = j;
  *k_ref = k;
  *l_ref = l;
  *r_ref = r;
  *cc_ref = cc;
  *cc1_ref = cc1;
  *nNotDone_ref = nNotDone;
}


----------------------------
typedef unsigned int UInt32
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
typedef unsigned char UChar
----------------------------
***/


// hint:  ['wfact_ref is a mutable refrence to Int32', 'quadrant_idx_ref is a mutable refrence to unsigned int', 'budget_ref is a mutable refrence to Int32', 'budgetInit_ref is a mutable refrence to Int32', 'i_ref is a mutable refrence to Int32']
void helper_BZ2_blockSort_1(Int32 * const wfact_ref, unsigned int * const quadrant_idx_ref, Int32 * const budget_ref, Int32 * const budgetInit_ref, Int32 * const i_ref, EState * const s, UInt32 * const ptr, UChar * const block, UInt32 * const ftab, Int32 nblock, Int32 verb, UInt16 * const quadrant)
{
  Int32 wfact = *wfact_ref;
  unsigned int quadrant_idx = *quadrant_idx_ref;
  Int32 budget = *budget_ref;
  Int32 budgetInit = *budgetInit_ref;
  Int32 i = *i_ref;
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
  *wfact_ref = wfact;
  *quadrant_idx_ref = quadrant_idx;
  *budget_ref = budget;
  *budgetInit_ref = budgetInit;
  *i_ref = i;
}


/*** DEPENDENCIES:
typedef int Int32
----------------------------
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
    ftab[i] = 0;

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
    ftab[i] += ftab[i - 1];

  s = block[0] << 8;
  i = nblock - 1;
  for (; i >= 3; i -= 4)
  {
    helper_mainSort_1(&j, &s, ptr, block, ftab, i);
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
      h = (3 * h) + 1;
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
    helper_mainSort_2(&nblock, &j, &k, &ss, &sb, &c1, &numQSorted, ptr, block, quadrant, ftab, verb, budget, i, runningOrder, bigDone, copyStart, copyEnd);
  }

  if (verb >= 4)
  {
    fprintf(stderr, "        %d pointers, %d sorted, %d scanned\n", nblock, numQSorted, nblock - numQSorted);
  }
}


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
typedef unsigned short UInt16
----------------------------
typedef short Int16
----------------------------
typedef unsigned char UChar
----------------------------
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
    ftab[i] = 0;

  for (i = 0; i < nblock; i += 1)
    ftab[eclass8[i]]++;

  for (i = 0; i < 256; i += 1)
    ftabCopy[i] = ftab[i];

  for (i = 1; i < 257; i += 1)
    ftab[i] += ftab[i - 1];

  for (i = 0; i < nblock; i += 1)
  {
    j = eclass8[i];
    k = ftab[j] - 1;
    ftab[j] = k;
    fmap[k] = i;
  }

  nBhtab = 2 + (nblock / 32);
  for (i = 0; i < nBhtab; i += 1)
    bhtab[i] = 0;

  for (i = 0; i < 256; i += 1)
    bhtab[ftab[i] >> 5] |= ((UInt32) 1) << (ftab[i] & 31);

  for (i = 0; i < 32; i += 1)
  {
    bhtab[(nblock + (2 * i)) >> 5] |= ((UInt32) 1) << ((nblock + (2 * i)) & 31);
    bhtab[((nblock + (2 * i)) + 1) >> 5] &= ~(((UInt32) 1) << (((nblock + (2 * i)) + 1) & 31));
  }

  H = 1;
  while (1)
  {
    helper_fallbackSort_1(&H, &i, &j, &k, &l, &r, &cc, &cc1, &nNotDone, fmap, eclass, bhtab, nblock, verb);
  }

  if (verb >= 4)
  {
    fprintf(stderr, "        reconstructing block ...\n");
  }
  j = 0;
  for (i = 0; i < nblock; i += 1)
  {
    while (ftabCopy[j] == 0)
      j++;

    j += 1;
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


----------------------------
***/


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
    helper_BZ2_blockSort_1(&wfact, &quadrant_idx, &budget, &budgetInit, &i, s, ptr, block, ftab, nblock, verb, quadrant);
  }
  s->origPtr = -1;
  for (i = 0; i < s->nblock; i += 1)
    if (ptr[i] == 0)
  {
    s->origPtr = i;
    break;
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


/*** DEPENDENCIES:
typedef int Int32
----------------------------
void helper_BZ2_blockSort_1(Int32 * const wfact_ref, unsigned int * const quadrant_idx_ref, Int32 * const budget_ref, Int32 * const budgetInit_ref, Int32 * const i_ref, EState * const s, UInt32 * const ptr, UChar * const block, UInt32 * const ftab, Int32 nblock, Int32 verb, UInt16 * const quadrant)
{
  Int32 wfact = *wfact_ref;
  unsigned int quadrant_idx = *quadrant_idx_ref;
  Int32 budget = *budget_ref;
  Int32 budgetInit = *budgetInit_ref;
  Int32 i = *i_ref;
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
  *wfact_ref = wfact;
  *quadrant_idx_ref = quadrant_idx;
  *budget_ref = budget;
  *budgetInit_ref = budgetInit;
  *i_ref = i;
}


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
typedef unsigned short UInt16
----------------------------
typedef short Int16
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
typedef unsigned char UChar
----------------------------
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
    ftab[i] = 0;

  for (i = 0; i < nblock; i += 1)
    ftab[eclass8[i]]++;

  for (i = 0; i < 256; i += 1)
    ftabCopy[i] = ftab[i];

  for (i = 1; i < 257; i += 1)
    ftab[i] += ftab[i - 1];

  for (i = 0; i < nblock; i += 1)
  {
    j = eclass8[i];
    k = ftab[j] - 1;
    ftab[j] = k;
    fmap[k] = i;
  }

  nBhtab = 2 + (nblock / 32);
  for (i = 0; i < nBhtab; i += 1)
    bhtab[i] = 0;

  for (i = 0; i < 256; i += 1)
    bhtab[ftab[i] >> 5] |= ((UInt32) 1) << (ftab[i] & 31);

  for (i = 0; i < 32; i += 1)
  {
    bhtab[(nblock + (2 * i)) >> 5] |= ((UInt32) 1) << ((nblock + (2 * i)) & 31);
    bhtab[((nblock + (2 * i)) + 1) >> 5] &= ~(((UInt32) 1) << (((nblock + (2 * i)) + 1) & 31));
  }

  H = 1;
  while (1)
  {
    helper_fallbackSort_1(&H, &i, &j, &k, &l, &r, &cc, &cc1, &nNotDone, fmap, eclass, bhtab, nblock, verb);
  }

  if (verb >= 4)
  {
    fprintf(stderr, "        reconstructing block ...\n");
  }
  j = 0;
  for (i = 0; i < nblock; i += 1)
  {
    while (ftabCopy[j] == 0)
      j++;

    j += 1;
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


----------------------------
***/


