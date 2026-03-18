void zgcd(z_t a, z_t b, z_t c)
{
  size_t shifts = 0;
  size_t i = 0;
  size_t min;
  zahl_char_t uv;
  zahl_char_t bit;
  int neg;
  if (!zcmp(b, c))
  {
    do
    {
      if (a != b)
      {
        zset(a, b);
      }
    }
    while (0);
    return;
  }
  if (zzero(b))
  {
    do
    {
      if (a != c)
      {
        zset(a, c);
      }
    }
    while (0);
    return;
  }
  if (zzero(c))
  {
    do
    {
      if (a != b)
      {
        zset(a, b);
      }
    }
    while (0);
    return;
  }
  zabs(libzahl_tmp_gcd_u, b);
  zabs(libzahl_tmp_gcd_v, c);
  neg = (zsignum(b) < 0) && (zsignum(c) < 0);
  min = (libzahl_tmp_gcd_u->used < libzahl_tmp_gcd_v->used) ? (libzahl_tmp_gcd_u->used) : (libzahl_tmp_gcd_v->used);
  for (; i < min; i += 1)
  {
    uv = libzahl_tmp_gcd_u->chars[i] | libzahl_tmp_gcd_v->chars[i];
    for (bit = 1; bit; bit <<= 1, shifts += 1)
      if (uv & bit)
    {
      goto loop_done;
    }

  }

  for (; i < libzahl_tmp_gcd_u->used; i += 1)
    for (bit = 1; bit; bit <<= 1, shifts += 1)
    if (libzahl_tmp_gcd_u->chars[i] & bit)
  {
    goto loop_done;
  }


  for (; i < libzahl_tmp_gcd_v->used; i += 1)
    for (bit = 1; bit; bit <<= 1, shifts += 1)
    if (libzahl_tmp_gcd_v->chars[i] & bit)
  {
    goto loop_done;
  }


  loop_done:
  zrsh(libzahl_tmp_gcd_u, libzahl_tmp_gcd_u, shifts);

  zrsh(libzahl_tmp_gcd_v, libzahl_tmp_gcd_v, shifts);
  zrsh(libzahl_tmp_gcd_u, libzahl_tmp_gcd_u, zlsb(libzahl_tmp_gcd_u));
  do
  {
    zrsh(libzahl_tmp_gcd_v, libzahl_tmp_gcd_v, zlsb(libzahl_tmp_gcd_v));
    if (zcmpmag(libzahl_tmp_gcd_u, libzahl_tmp_gcd_v) > 0)
    {
      zswap(libzahl_tmp_gcd_u, libzahl_tmp_gcd_v);
    }
    zsub_unsigned(libzahl_tmp_gcd_v, libzahl_tmp_gcd_v, libzahl_tmp_gcd_u);
  }
  while (!zzero(libzahl_tmp_gcd_v));
  zlsh(a, libzahl_tmp_gcd_u, shifts);
  a->sign = (neg) ? (-1) : (1);
}


/*** DEPENDENCIES:
void zlsh(z_t a, z_t b, size_t bits)
{
  size_t i;
  size_t chars;
  size_t cbits;
  zahl_char_t carry[] = {0, 0};
  if (zzero(b))
  {
    a->sign = 0;
    return;
  }
  if (!bits)
  {
    do
    {
      if (a != b)
      {
        zset(a, b);
      }
    }
    while (0);
    return;
  }
  chars = bits >> 5;
  bits = bits & (32 - 1);
  cbits = 32 - bits;
  do
  {
    if (a->alloced < (b->used + chars))
    {
      libzahl_realloc(a, b->used + chars);
    }
  }
  while (0);
  if (a == b)
  {
    memmove(a->chars + chars, b->chars, b->used * (sizeof(zahl_char_t)));
  }
  else
    memcpy(a->chars + chars, b->chars, b->used * (sizeof(zahl_char_t)));
  memset(a->chars, 0, chars * (sizeof(zahl_char_t)));
  a->used = b->used + chars;
  if (bits)
  {
    for (i = chars; i < a->used; i += 1)
    {
      carry[(~i) & 1] = a->chars[i] >> cbits;
      a->chars[i] <<= bits;
      a->chars[i] |= carry[i & 1];
    }

    if (carry[i & 1])
    {
      do
      {
        if (a->alloced < (a->used + 1))
        {
          libzahl_realloc(a, a->used + 1);
        }
      }
      while (0);
      a->chars[i] = carry[i & 1];
      a->used += 1;
    }
  }
  a->sign = zsignum(b);
}


----------------------------
void zabs(z_t a, z_t b)
{
  do
  {
    if (a != b)
    {
      zset(a, b);
    }
  }
  while (0);
  a->sign = !zzero(a);
}


----------------------------
int zcmpmag(z_t a, z_t b)
{
  size_t i;
  size_t j;
  if (zzero(a))
  {
    return -(!zzero(b));
  }
  if (zzero(b))
  {
    return 1;
  }
  i = a->used - 1;
  j = b->used - 1;
  for (; i > j; i -= 1)
  {
    if (a->chars[i])
    {
      return +1;
    }
    a->used -= 1;
  }

  for (; j > i; j -= 1)
  {
    if (b->chars[j])
    {
      return -1;
    }
    b->used -= 1;
  }

  for (; i; i -= 1)
    if (a->chars[i] != b->chars[i])
  {
    return ((a->chars[i] > b->chars[i]) * 2) - 1;
  }

  return (a->chars[0] < b->chars[0]) ? (-1) : (a->chars[0] > b->chars[0]);
}


----------------------------
typedef uint32_t zahl_char_t
----------------------------
extern z_t libzahl_tmp_gcd_u
----------------------------
void zswap(z_t a, z_t b)
{
  z_t t;
  *t = *a;
  *a = *b;
  *b = *t;
}


----------------------------
size_t zlsb(z_t a)
{
  size_t i = 0;
  zahl_char_t x;
  if (zzero(a))
  {
    return SIZE_MAX;
  }
  for (;; i += 1)
  {
    x = a->chars[i];
    if (x)
    {
      x = ~x;
      for (i *= 32; x & 1; x >>= 1, i += 1)
        ;

      return i;
    }
  }

}


----------------------------
void zsub_unsigned(z_t a, z_t b, z_t c)
{
  zahl_char_t carry[] = {0, 0};
  zahl_char_t *s;
  unsigned int s_idx = 0;
  size_t i;
  size_t n;
  int magcmp;
  if (zzero(b))
  {
    zabs(a, c);
    zneg(a, a);
    return;
  }
  else
    if (zzero(c))
  {
    zabs(a, b);
    return;
  }
  magcmp = zcmpmag(b, c);
  if (magcmp <= 0)
  {
    if (magcmp == 0)
    {
      a->sign = 0;
      return;
    }
    n = (b->used < c->used) ? (b->used) : (c->used);
    if (a == b)
    {
      zset(libzahl_tmp_sub, b);
      s_idx = libzahl_tmp_sub->chars;
    }
    else
    {
      s_idx = b->chars;
    }
    do
    {
      if (a != c)
      {
        zset(a, c);
      }
    }
    while (0);
  }
  else
  {
    n = (b->used < c->used) ? (b->used) : (c->used);
    if (a == c)
    {
      zset(libzahl_tmp_sub, c);
      s_idx = libzahl_tmp_sub->chars;
    }
    else
    {
      s_idx = c->chars;
    }
    do
    {
      if (a != b)
      {
        zset(a, b);
      }
    }
    while (0);
  }
  for (i = 0; i < n; i += 1)
  {
    carry[(~i) & 1] = (carry[i & 1]) ? (a->chars[i] <= s[i + s_idx]) : (a->chars[i] < s[i + s_idx]);
    a->chars[i] -= s[i + s_idx];
    a->chars[i] -= carry[i & 1];
  }

  if (carry[i & 1])
  {
    while (!a->chars[i])
      a->chars[i] = UINT32_MAX;

    i += 1;
    a->chars[i] -= 1;
  }
  a->sign = magcmp;
}


----------------------------
void zset(z_t a, z_t b)
{
  if (zzero(b))
  {
    a->sign = 0;
  }
  else
  {
    do
    {
      if (a->alloced < b->used)
      {
        libzahl_realloc(a, b->used);
      }
    }
    while (0);
    a->sign = b->sign;
    a->used = b->used;
    memcpy(a->chars, b->chars, b->used * (sizeof(zahl_char_t)));
  }
}


----------------------------
int zcmp(z_t a, z_t b)
{
  if (zsignum(a) != zsignum(b))
  {
    return (zsignum(a) < zsignum(b)) ? (-1) : (zsignum(a) > zsignum(b));
  }
  return zsignum(a) * zcmpmag(a, b);
}


----------------------------
inline static int zzero(z_t a)
{
  return !a->sign;
}


----------------------------
typedef struct 
{
  int sign;
  size_t used;
  size_t alloced;
  zahl_char_t *chars;
} z_t[1]
----------------------------
inline static int zsignum(z_t a)
{
  return a->sign;
}


----------------------------
extern z_t libzahl_tmp_gcd_v
----------------------------
void zrsh(z_t a, z_t b, size_t bits)
{
  size_t i;
  size_t chars;
  size_t cbits;
  if (!bits)
  {
    do
    {
      if (a != b)
      {
        zset(a, b);
      }
    }
    while (0);
    return;
  }
  chars = bits >> 5;
  if ((zzero(b) || (chars >= b->used)) || (zbits(b) <= bits))
  {
    a->sign = 0;
    return;
  }
  bits = bits & (32 - 1);
  cbits = 32 - bits;
  if (chars && (a == b))
  {
    a->used -= chars;
    memmove(a->chars, a->chars + chars, a->used * (sizeof(zahl_char_t)));
  }
  else
    if (a != b)
  {
    a->used = b->used - chars;
    do
    {
      if (a->alloced < a->used)
      {
        libzahl_realloc(a, a->used);
      }
    }
    while (0);
    memcpy(a->chars, b->chars + chars, a->used * (sizeof(zahl_char_t)));
  }
  if (bits)
  {
    a->chars[0] >>= bits;
    for (i = 1; i < a->used; i += 1)
    {
      a->chars[i - 1] |= a->chars[i] << cbits;
      a->chars[i] >>= bits;
    }

    while (!a->chars[a->used - 1])
      a->used--;

  }
  a->sign = zsignum(b);
}


----------------------------
***/


