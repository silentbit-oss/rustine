void zmul(z_t a, z_t b, z_t c)
{
  size_t m;
  size_t m2;
  z_t z0;
  z_t z1;
  z_t z2;
  z_t b_high;
  z_t b_low;
  z_t c_high;
  z_t c_low;
  int b_sign;
  int c_sign;
  b_sign = zsignum(b);
  c_sign = zsignum(c);
  if ((!b_sign) || (!c_sign))
  {
    a->sign = 0;
    return;
  }
  m = zbits(b);
  m2 = (b == c) ? (m) : (zbits(c));
  if ((m + m2) <= 32)
  {
    do
    {
      if (a->alloced < 1)
      {
        libzahl_realloc(a, 1);
      }
    }
    while (0);
    a->used = 1;
    a->chars[0] = b->chars[0] * c->chars[0];
    a->sign = b_sign * c_sign;
    return;
  }
  b->sign = 1;
  c->sign = 1;
  m = (m > m2) ? (m) : (m2);
  m2 = m >> 1;
  zinit(z0);
  zinit(z1);
  zinit(z2);
  zinit(b_high);
  zinit(b_low);
  zinit(c_high);
  zinit(c_low);
  zsplit(b_high, b_low, b, m2);
  zsplit(c_high, c_low, c, m2);
  zmul(z0, b_low, c_low);
  zmul(z2, b_high, c_high);
  zadd(b_low, b_low, b_high);
  zadd(c_low, c_low, c_high);
  zmul(z1, b_low, c_low);
  zsub(z1, z1, z0);
  zsub(z1, z1, z2);
  zlsh(z1, z1, m2);
  m2 <<= 1;
  zlsh(z2, z2, m2);
  zadd(a, z2, z1);
  zadd(a, a, z0);
  zfree(z0);
  zfree(z1);
  zfree(z2);
  zfree(b_high);
  zfree(b_low);
  zfree(c_high);
  zfree(c_low);
  b->sign = b_sign;
  c->sign = c_sign;
  a->sign = b_sign * c_sign;
}


/*** DEPENDENCIES:
void zmul(z_t a, z_t b, z_t c)
{
  size_t m;
  size_t m2;
  z_t z0;
  z_t z1;
  z_t z2;
  z_t b_high;
  z_t b_low;
  z_t c_high;
  z_t c_low;
  int b_sign;
  int c_sign;
  b_sign = zsignum(b);
  c_sign = zsignum(c);
  if ((!b_sign) || (!c_sign))
  {
    a->sign = 0;
    return;
  }
  m = zbits(b);
  m2 = (b == c) ? (m) : (zbits(c));
  if ((m + m2) <= 32)
  {
    do
    {
      if (a->alloced < 1)
      {
        libzahl_realloc(a, 1);
      }
    }
    while (0);
    a->used = 1;
    a->chars[0] = b->chars[0] * c->chars[0];
    a->sign = b_sign * c_sign;
    return;
  }
  b->sign = 1;
  c->sign = 1;
  m = (m > m2) ? (m) : (m2);
  m2 = m >> 1;
  zinit(z0);
  zinit(z1);
  zinit(z2);
  zinit(b_high);
  zinit(b_low);
  zinit(c_high);
  zinit(c_low);
  zsplit(b_high, b_low, b, m2);
  zsplit(c_high, c_low, c, m2);
  zmul(z0, b_low, c_low);
  zmul(z2, b_high, c_high);
  zadd(b_low, b_low, b_high);
  zadd(c_low, c_low, c_high);
  zmul(z1, b_low, c_low);
  zsub(z1, z1, z0);
  zsub(z1, z1, z2);
  zlsh(z1, z1, m2);
  m2 <<= 1;
  zlsh(z2, z2, m2);
  zadd(a, z2, z1);
  zadd(a, a, z0);
  zfree(z0);
  zfree(z1);
  zfree(z2);
  zfree(b_high);
  zfree(b_low);
  zfree(c_high);
  zfree(c_low);
  b->sign = b_sign;
  c->sign = c_sign;
  a->sign = b_sign * c_sign;
}


----------------------------
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
void zadd(z_t a, z_t b, z_t c)
{
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
  }
  else
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
  }
  else
    if (b == c)
  {
    zlsh(a, b, 1);
  }
  else
    if ((zsignum(b) | zsignum(c)) < 0)
  {
    if (zsignum(b) < 0)
    {
      if (zsignum(c) < 0)
      {
        zadd_unsigned(a, b, c);
        a->sign = -zsignum(a);
      }
      else
      {
        zsub_unsigned(a, c, b);
      }
    }
    else
    {
      zsub_unsigned(a, b, c);
    }
  }
  else
  {
    zadd_unsigned(a, b, c);
  }
}


----------------------------
void zsplit(z_t high, z_t low, z_t a, size_t delim)
{
  if (zzero(a))
  {
    high->sign = 0;
    low->sign = 0;
    return;
  }
  if (high == a)
  {
    ztrunc(low, a, delim);
    zrsh(high, a, delim);
  }
  else
  {
    zrsh(high, a, delim);
    ztrunc(low, a, delim);
  }
}


----------------------------
void zfree(z_t a)
{
  size_t i = 0;
  size_t x;
  size_t j;
  zahl_char_t **new;
  unsigned int new_idx = 0;
  if (!a->chars)
  {
    return;
  }
  for (x = a->alloced; x; x >>= 1)
    i += 1;

  j = libzahl_pool_n[i]++;
  if (j == libzahl_pool_alloc[i])
  {
    x = (j) ? ((j * 3) >> 1) : (128);
    new_idx = realloc(libzahl_pool[i], x * (sizeof(zahl_char_t *)));
    if (!(&new[new_idx]))
    {
      free(a->chars);
      free(libzahl_pool[i]);
      libzahl_pool_n[i] = 0;
      libzahl_pool[i] = 0;
      libzahl_pool_alloc[i] = 0;
      return;
    }
    libzahl_pool[i] = &new[new_idx];
    libzahl_pool_alloc[i] = x;
  }
  libzahl_pool[i][j] = a->chars;
}


----------------------------
void libzahl_realloc(z_t a, size_t need)
{
  size_t i;
  size_t x;
  zahl_char_t *new;
  unsigned int new_idx = 0;
  if ((need & ((~need) + 1)) != need)
  {
    need |= need >> 1;
    need |= need >> 2;
    need |= need >> 4;
    for (i = sizeof(need), x = 8; i; i >>= 1, x <<= 1)
      need |= need >> x;

    need += 1;
  }
  for (i = 0, x = need; x; x >>= 1)
    i += 1;

  if (libzahl_pool_n[i])
  {
    libzahl_pool_n[i] -= 1;
    new_idx = libzahl_pool[i][libzahl_pool_n[i]];
    memcpy(new, a->chars, a->alloced * (sizeof(zahl_char_t)));
    zfree(a);
    a->chars = &new[new_idx];
  }
  else
  {
    a->chars = realloc(a->chars, need * (sizeof(zahl_char_t)));
    if (!a->chars)
    {
      if (!errno)
      {
        errno = ENOMEM;
      }
      libzahl_error = errno, longjmp(libzahl_jmp_buf, 1);
    }
  }
  a->alloced = need;
}


----------------------------
void zsub(z_t a, z_t b, z_t c)
{
  if (b == c)
  {
    a->sign = 0;
  }
  else
    if (zzero(b))
  {
    zneg(a, c);
  }
  else
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
  }
  else
    if ((zsignum(b) | zsignum(c)) < 0)
  {
    if (zsignum(b) < 0)
    {
      if (zsignum(c) < 0)
      {
        zsub_unsigned(a, c, b);
      }
      else
      {
        zadd_unsigned(a, b, c);
        a->sign = -zsignum(a);
      }
    }
    else
    {
      zadd_unsigned(a, b, c);
    }
  }
  else
  {
    zsub_unsigned(a, b, c);
  }
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
size_t zbits(z_t a)
{
  size_t i;
  zahl_char_t x;
  if (zzero(a))
  {
    return 1;
  }
  for (i = a->used - 1;; i -= 1)
  {
    x = a->chars[i];
    if (x)
    {
      a->used = i + 1;
      for (i *= 32; x; x >>= 1, i += 1)
        ;

      return i;
    }
  }

}


----------------------------
inline static int zsignum(z_t a)
{
  return a->sign;
}


----------------------------
inline static void zinit(z_t a)
{
  a->alloced = 0;
  a->chars = 0;
}


----------------------------
***/


