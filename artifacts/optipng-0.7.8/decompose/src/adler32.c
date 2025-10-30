static uLong adler32_combine_(uLong adler1, uLong adler2, off_t len2)
{
  unsigned long sum1;
  unsigned long sum2;
  unsigned rem;
  if (len2 < 0)
  {
    return 0xffffffffUL;
  }
  len2 %= 65521U;
  rem = (unsigned) len2;
  sum1 = adler1 & 0xffff;
  sum2 = rem * sum1;
  sum2 %= 65521U;
  sum1 += ((adler2 & 0xffff) + 65521U) - 1;
  sum2 += ((((adler1 >> 16) & 0xffff) + ((adler2 >> 16) & 0xffff)) + 65521U) - rem;
  if (sum1 >= 65521U)
  {
    sum1 -= 65521U;
  }
  if (sum1 >= 65521U)
  {
    sum1 -= 65521U;
  }
  if (sum2 >= (((unsigned long) 65521U) << 1))
  {
    sum2 -= ((unsigned long) 65521U) << 1;
  }
  if (sum2 >= 65521U)
  {
    sum2 -= 65521U;
  }
  return sum1 | (sum2 << 16);
}


/*** DEPENDENCIES:
typedef unsigned long uLong
----------------------------
***/


uLong adler32_combine(uLong adler1, uLong adler2, off_t len2)
{
  return adler32_combine_(adler1, adler2, len2);
}


/*** DEPENDENCIES:
typedef unsigned long uLong
----------------------------
static uLong adler32_combine_(uLong adler1, uLong adler2, off_t len2)
{
  unsigned long sum1;
  unsigned long sum2;
  unsigned rem;
  if (len2 < 0)
  {
    return 0xffffffffUL;
  }
  len2 %= 65521U;
  rem = (unsigned) len2;
  sum1 = adler1 & 0xffff;
  sum2 = rem * sum1;
  sum2 %= 65521U;
  sum1 += ((adler2 & 0xffff) + 65521U) - 1;
  sum2 += ((((adler1 >> 16) & 0xffff) + ((adler2 >> 16) & 0xffff)) + 65521U) - rem;
  if (sum1 >= 65521U)
  {
    sum1 -= 65521U;
  }
  if (sum1 >= 65521U)
  {
    sum1 -= 65521U;
  }
  if (sum2 >= (((unsigned long) 65521U) << 1))
  {
    sum2 -= ((unsigned long) 65521U) << 1;
  }
  if (sum2 >= 65521U)
  {
    sum2 -= 65521U;
  }
  return sum1 | (sum2 << 16);
}


----------------------------
***/


uLong adler32_combine64(uLong adler1, uLong adler2, off_t len2)
{
  return adler32_combine_(adler1, adler2, len2);
}


/*** DEPENDENCIES:
typedef unsigned long uLong
----------------------------
static uLong adler32_combine_(uLong adler1, uLong adler2, off_t len2)
{
  unsigned long sum1;
  unsigned long sum2;
  unsigned rem;
  if (len2 < 0)
  {
    return 0xffffffffUL;
  }
  len2 %= 65521U;
  rem = (unsigned) len2;
  sum1 = adler1 & 0xffff;
  sum2 = rem * sum1;
  sum2 %= 65521U;
  sum1 += ((adler2 & 0xffff) + 65521U) - 1;
  sum2 += ((((adler1 >> 16) & 0xffff) + ((adler2 >> 16) & 0xffff)) + 65521U) - rem;
  if (sum1 >= 65521U)
  {
    sum1 -= 65521U;
  }
  if (sum1 >= 65521U)
  {
    sum1 -= 65521U;
  }
  if (sum2 >= (((unsigned long) 65521U) << 1))
  {
    sum2 -= ((unsigned long) 65521U) << 1;
  }
  if (sum2 >= 65521U)
  {
    sum2 -= 65521U;
  }
  return sum1 | (sum2 << 16);
}


----------------------------
***/


// hint:  ['adler_ref is a mutable refrence to uLong', 'len_ref is a mutable refrence to z_size_t', 'buf_idx_ref is a mutable refrence to unsigned int', 'sum2_ref is a mutable refrence to unsigned long']
void helper_helper_adler32_z_2_1(uLong * const adler_ref, z_size_t * const len_ref, unsigned int * const buf_idx_ref, unsigned long * const sum2_ref, const Bytef * const buf)
{
  uLong adler = *adler_ref;
  z_size_t len = *len_ref;
  unsigned int buf_idx = *buf_idx_ref;
  unsigned long sum2 = *sum2_ref;
  len -= 16;
  {
    adler += buf[0 + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[(0 + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  {
    adler += buf[(0 + 2) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[((0 + 2) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  ;
  {
    adler += buf[(0 + 4) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[((0 + 4) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  {
    adler += buf[((0 + 4) + 2) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[(((0 + 4) + 2) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  ;
  ;
  {
    adler += buf[8 + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[(8 + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  {
    adler += buf[(8 + 2) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[((8 + 2) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  ;
  {
    adler += buf[(8 + 4) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[((8 + 4) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  {
    adler += buf[((8 + 4) + 2) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[(((8 + 4) + 2) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  ;
  ;
  ;
  buf_idx += 16;
  *adler_ref = adler;
  *len_ref = len;
  *buf_idx_ref = buf_idx;
  *sum2_ref = sum2;
}


/*** DEPENDENCIES:
typedef unsigned long uLong
----------------------------
typedef Byte Bytef
----------------------------
typedef size_t z_size_t
----------------------------
typedef unsigned char Byte
----------------------------
***/


// hint:  ['adler_ref is a mutable refrence to uLong', 'len_ref is a mutable refrence to z_size_t', 'buf_idx_ref is a mutable refrence to unsigned int', 'sum2_ref is a mutable refrence to unsigned long']
void helper_adler32_z_2(uLong * const adler_ref, z_size_t * const len_ref, unsigned int * const buf_idx_ref, unsigned long * const sum2_ref, const Bytef * const buf)
{
  uLong adler = *adler_ref;
  z_size_t len = *len_ref;
  unsigned int buf_idx = *buf_idx_ref;
  unsigned long sum2 = *sum2_ref;
  while (len >= 16)
  {
    helper_helper_adler32_z_2_1(&adler, &len, &buf_idx, &sum2, buf);
  }

  while (len--)
  {
    adler += buf[buf_idx];
    buf_idx += 1;
    sum2 += adler;
  }

  adler %= 65521U;
  sum2 %= 65521U;
  *adler_ref = adler;
  *len_ref = len;
  *buf_idx_ref = buf_idx;
  *sum2_ref = sum2;
}


/*** DEPENDENCIES:
typedef unsigned long uLong
----------------------------
typedef Byte Bytef
----------------------------
void helper_helper_adler32_z_2_1(uLong * const adler_ref, z_size_t * const len_ref, unsigned int * const buf_idx_ref, unsigned long * const sum2_ref, const Bytef * const buf)
{
  uLong adler = *adler_ref;
  z_size_t len = *len_ref;
  unsigned int buf_idx = *buf_idx_ref;
  unsigned long sum2 = *sum2_ref;
  len -= 16;
  {
    adler += buf[0 + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[(0 + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  {
    adler += buf[(0 + 2) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[((0 + 2) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  ;
  {
    adler += buf[(0 + 4) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[((0 + 4) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  {
    adler += buf[((0 + 4) + 2) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[(((0 + 4) + 2) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  ;
  ;
  {
    adler += buf[8 + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[(8 + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  {
    adler += buf[(8 + 2) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[((8 + 2) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  ;
  {
    adler += buf[(8 + 4) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[((8 + 4) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  {
    adler += buf[((8 + 4) + 2) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[(((8 + 4) + 2) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  ;
  ;
  ;
  buf_idx += 16;
  *adler_ref = adler;
  *len_ref = len;
  *buf_idx_ref = buf_idx;
  *sum2_ref = sum2;
}


----------------------------
typedef size_t z_size_t
----------------------------
typedef unsigned char Byte
----------------------------
***/


// hint:  ['adler_ref is a mutable refrence to uLong', 'buf_idx_ref is a mutable refrence to unsigned int', 'sum2_ref is a mutable refrence to unsigned long']
void helper_helper_adler32_z_1_1(uLong * const adler_ref, unsigned int * const buf_idx_ref, unsigned long * const sum2_ref, const Bytef * const buf)
{
  uLong adler = *adler_ref;
  unsigned int buf_idx = *buf_idx_ref;
  unsigned long sum2 = *sum2_ref;
  {
    adler += buf[0 + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[(0 + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  {
    adler += buf[(0 + 2) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[((0 + 2) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  ;
  {
    adler += buf[(0 + 4) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[((0 + 4) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  {
    adler += buf[((0 + 4) + 2) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[(((0 + 4) + 2) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  ;
  ;
  {
    adler += buf[8 + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[(8 + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  {
    adler += buf[(8 + 2) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[((8 + 2) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  ;
  {
    adler += buf[(8 + 4) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[((8 + 4) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  {
    adler += buf[((8 + 4) + 2) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[(((8 + 4) + 2) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  ;
  ;
  ;
  buf_idx += 16;
  *adler_ref = adler;
  *buf_idx_ref = buf_idx;
  *sum2_ref = sum2;
}


/*** DEPENDENCIES:
typedef unsigned long uLong
----------------------------
typedef Byte Bytef
----------------------------
typedef unsigned char Byte
----------------------------
***/


// hint:  ['adler_ref is a mutable refrence to uLong', 'len_ref is a mutable refrence to z_size_t', 'buf_idx_ref is a mutable refrence to unsigned int', 'sum2_ref is a mutable refrence to unsigned long', 'n_ref is a mutable refrence to unsigned']
void helper_adler32_z_1(uLong * const adler_ref, z_size_t * const len_ref, unsigned int * const buf_idx_ref, unsigned long * const sum2_ref, unsigned * const n_ref, const Bytef * const buf)
{
  uLong adler = *adler_ref;
  z_size_t len = *len_ref;
  unsigned int buf_idx = *buf_idx_ref;
  unsigned long sum2 = *sum2_ref;
  unsigned n = *n_ref;
  len -= 5552;
  n = 5552 / 16;
  do
  {
    helper_helper_adler32_z_1_1(&adler, &buf_idx, &sum2, buf);
  }
  while (--n);
  adler %= 65521U;
  sum2 %= 65521U;
  *adler_ref = adler;
  *len_ref = len;
  *buf_idx_ref = buf_idx;
  *sum2_ref = sum2;
  *n_ref = n;
}


/*** DEPENDENCIES:
typedef unsigned long uLong
----------------------------
typedef Byte Bytef
----------------------------
void helper_helper_adler32_z_1_1(uLong * const adler_ref, unsigned int * const buf_idx_ref, unsigned long * const sum2_ref, const Bytef * const buf)
{
  uLong adler = *adler_ref;
  unsigned int buf_idx = *buf_idx_ref;
  unsigned long sum2 = *sum2_ref;
  {
    adler += buf[0 + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[(0 + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  {
    adler += buf[(0 + 2) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[((0 + 2) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  ;
  {
    adler += buf[(0 + 4) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[((0 + 4) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  {
    adler += buf[((0 + 4) + 2) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[(((0 + 4) + 2) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  ;
  ;
  {
    adler += buf[8 + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[(8 + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  {
    adler += buf[(8 + 2) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[((8 + 2) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  ;
  {
    adler += buf[(8 + 4) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[((8 + 4) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  {
    adler += buf[((8 + 4) + 2) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[(((8 + 4) + 2) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  ;
  ;
  ;
  buf_idx += 16;
  *adler_ref = adler;
  *buf_idx_ref = buf_idx;
  *sum2_ref = sum2;
}


----------------------------
typedef size_t z_size_t
----------------------------
typedef unsigned char Byte
----------------------------
***/


uLong adler32_z(uLong adler, const Bytef *buf, z_size_t len)
{
  unsigned int buf_idx = 0;
  unsigned long sum2;
  unsigned n;
  sum2 = (adler >> 16) & 0xffff;
  adler &= 0xffff;
  if (len == 1)
  {
    adler += buf[0 + buf_idx];
    if (adler >= 65521U)
    {
      adler -= 65521U;
    }
    sum2 += adler;
    if (sum2 >= 65521U)
    {
      sum2 -= 65521U;
    }
    return adler | (sum2 << 16);
  }
  if ((&buf[buf_idx]) == 0)
  {
    return 1L;
  }
  if (len < 16)
  {
    while (len--)
    {
      adler += buf[buf_idx];
      buf_idx += 1;
      sum2 += adler;
    }

    if (adler >= 65521U)
    {
      adler -= 65521U;
    }
    sum2 %= 65521U;
    return adler | (sum2 << 16);
  }
  while (len >= 5552)
  {
    helper_adler32_z_1(&adler, &len, &buf_idx, &sum2, &n, buf);
  }

  if (len)
  {
    helper_adler32_z_2(&adler, &len, &buf_idx, &sum2, buf);
  }
  return adler | (sum2 << 16);
}


/*** DEPENDENCIES:
typedef unsigned long uLong
----------------------------
typedef Byte Bytef
----------------------------
void helper_adler32_z_2(uLong * const adler_ref, z_size_t * const len_ref, unsigned int * const buf_idx_ref, unsigned long * const sum2_ref, const Bytef * const buf)
{
  uLong adler = *adler_ref;
  z_size_t len = *len_ref;
  unsigned int buf_idx = *buf_idx_ref;
  unsigned long sum2 = *sum2_ref;
  while (len >= 16)
  {
    helper_helper_adler32_z_2_1(&adler, &len, &buf_idx, &sum2, buf);
  }

  while (len--)
  {
    adler += buf[buf_idx];
    buf_idx += 1;
    sum2 += adler;
  }

  adler %= 65521U;
  sum2 %= 65521U;
  *adler_ref = adler;
  *len_ref = len;
  *buf_idx_ref = buf_idx;
  *sum2_ref = sum2;
}


----------------------------
typedef size_t z_size_t
----------------------------
void helper_adler32_z_1(uLong * const adler_ref, z_size_t * const len_ref, unsigned int * const buf_idx_ref, unsigned long * const sum2_ref, unsigned * const n_ref, const Bytef * const buf)
{
  uLong adler = *adler_ref;
  z_size_t len = *len_ref;
  unsigned int buf_idx = *buf_idx_ref;
  unsigned long sum2 = *sum2_ref;
  unsigned n = *n_ref;
  len -= 5552;
  n = 5552 / 16;
  do
  {
    helper_helper_adler32_z_1_1(&adler, &buf_idx, &sum2, buf);
  }
  while (--n);
  adler %= 65521U;
  sum2 %= 65521U;
  *adler_ref = adler;
  *len_ref = len;
  *buf_idx_ref = buf_idx;
  *sum2_ref = sum2;
  *n_ref = n;
}


----------------------------
typedef unsigned char Byte
----------------------------
***/


uLong adler32(uLong adler, const Bytef *buf, uInt len)
{
  return adler32_z(adler, buf, len);
}


/*** DEPENDENCIES:
typedef unsigned long uLong
----------------------------
typedef Byte Bytef
----------------------------
uLong adler32_z(uLong adler, const Bytef *buf, z_size_t len)
{
  unsigned int buf_idx = 0;
  unsigned long sum2;
  unsigned n;
  sum2 = (adler >> 16) & 0xffff;
  adler &= 0xffff;
  if (len == 1)
  {
    adler += buf[0 + buf_idx];
    if (adler >= 65521U)
    {
      adler -= 65521U;
    }
    sum2 += adler;
    if (sum2 >= 65521U)
    {
      sum2 -= 65521U;
    }
    return adler | (sum2 << 16);
  }
  if ((&buf[buf_idx]) == 0)
  {
    return 1L;
  }
  if (len < 16)
  {
    while (len--)
    {
      adler += buf[buf_idx];
      buf_idx += 1;
      sum2 += adler;
    }

    if (adler >= 65521U)
    {
      adler -= 65521U;
    }
    sum2 %= 65521U;
    return adler | (sum2 << 16);
  }
  while (len >= 5552)
  {
    helper_adler32_z_1(&adler, &len, &buf_idx, &sum2, &n, buf);
  }

  if (len)
  {
    helper_adler32_z_2(&adler, &len, &buf_idx, &sum2, buf);
  }
  return adler | (sum2 << 16);
}


----------------------------
typedef unsigned int uInt
----------------------------
typedef unsigned char Byte
----------------------------
***/


