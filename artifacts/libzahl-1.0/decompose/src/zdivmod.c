void zdivmod(z_t a, z_t b, z_t c, z_t d)
{
  size_t c_bits;
  size_t d_bits;
  size_t bit;
  int sign;
  int cmpmag;
  sign = zsignum(c) * zsignum(d);
  if (!sign)
  {
    if (zzero(c))
    {
      if (zzero(d))
      {
        libzahl_error = EDOM, longjmp(libzahl_jmp_buf, 1);
      }
      else
      {
        a->sign = 0;
        b->sign = 0;
      }
    }
    else
    {
      libzahl_error = EDOM, longjmp(libzahl_jmp_buf, 1);
    }
    return;
  }
  else
    if ((cmpmag = zcmpmag(c, d)) <= 0)
  {
    if (cmpmag == 0)
    {
      zseti(a, sign);
      b->sign = 0;
      return;
    }
    else
    {
      do
      {
        if (b != c)
        {
          zset(b, c);
        }
      }
      while (0);
    }
    b->sign = 1;
    a->sign = 0;
    return;
  }
  c_bits = zbits(c);
  d_bits = zbits(d);
  bit = c_bits - d_bits;
  zlsh(libzahl_tmp_divmod_d, d, bit);
  libzahl_tmp_divmod_d->sign = 1;
  if (zcmpmag(libzahl_tmp_divmod_d, c) > 0)
  {
    zrsh(libzahl_tmp_divmod_d, libzahl_tmp_divmod_d, 1);
    bit -= 1;
  }
  libzahl_tmp_divmod_a->sign = 0;
  zabs(libzahl_tmp_divmod_b, c);
  if (bit < 32)
  {
    for (;;)
    {
      if (zcmpmag(libzahl_tmp_divmod_d, libzahl_tmp_divmod_b) <= 0)
      {
        zsub(libzahl_tmp_divmod_b, libzahl_tmp_divmod_b, libzahl_tmp_divmod_d);
        zbset(libzahl_tmp_divmod_a, libzahl_tmp_divmod_a, bit, 1);
      }
      if ((!(bit--)) || zzero(libzahl_tmp_divmod_b))
      {
        goto done;
      }
      zrsh(libzahl_tmp_divmod_d, libzahl_tmp_divmod_d, 1);
    }

  }
  else
  {
    size_t i;
    for (i = 0; i < 32; i += 1)
      zrsh(libzahl_tmp_divmod_ds[i], libzahl_tmp_divmod_d, i);

    for (;;)
    {
      for (i = 0; i < 32; i += 1)
      {
        if (zcmpmag(libzahl_tmp_divmod_ds[i], libzahl_tmp_divmod_b) <= 0)
        {
          zsub(libzahl_tmp_divmod_b, libzahl_tmp_divmod_b, libzahl_tmp_divmod_ds[i]);
          zbset(libzahl_tmp_divmod_a, libzahl_tmp_divmod_a, bit, 1);
        }
        if ((!(bit--)) || zzero(libzahl_tmp_divmod_b))
        {
          goto done;
        }
      }

      for (i = ((bit < (32 - 1)) ? (bit) : (32 - 1)) + 1; i--;)
        zrsh(libzahl_tmp_divmod_ds[i], libzahl_tmp_divmod_ds[i], 32);

    }

  }
  done:
  zswap(a, libzahl_tmp_divmod_a);

  zswap(b, libzahl_tmp_divmod_b);
  a->sign = sign;
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
extern z_t libzahl_tmp_divmod_d
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
extern jmp_buf libzahl_jmp_buf
----------------------------
inline static int zsignum(z_t a)
{
  return a->sign;
}


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
extern z_t libzahl_tmp_divmod_ds[32]
----------------------------
extern int libzahl_error
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
extern z_t libzahl_tmp_divmod_a
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
extern z_t libzahl_tmp_divmod_b
----------------------------
void zseti(z_t a, long long int b)
{
  if (b >= 0)
  {
    zsetu(a, (unsigned long long int) b);
  }
  else
  {
    zsetu(a, (unsigned long long int) (-b));
    a->sign = -1;
  }
}


----------------------------
void zswap(z_t a, z_t b)
{
  z_t t;
  *t = *a;
  *a = *b;
  *b = *t;
}


----------------------------
inline static int zzero(z_t a)
{
  return !a->sign;
}


----------------------------
void zbset(z_t a, z_t b, size_t bit, int action)
{
  zahl_char_t mask = 1;
  size_t chars;
  chars = bit >> 5;
  bit = bit & (32 - 1);
  mask <<= bit;
  do
  {
    if (a != b)
    {
      zset(a, b);
    }
  }
  while (0);
  if (action)
  {
    if (zzero(a))
    {
      a->used = 0;
      a->sign = 1;
    }
    if (a->used <= chars)
    {
      do
      {
        if (a->alloced < (chars + 1))
        {
          libzahl_realloc(a, chars + 1);
        }
      }
      while (0);
      memset(a->chars + a->used, 0, ((chars + 1) - a->used) * (sizeof(zahl_char_t)));
      a->used = chars + 1;
    }
  }
  if (action > 0)
  {
    a->chars[chars] |= mask;
    return;
  }
  else
    if (action < 0)
  {
    a->chars[chars] ^= mask;
  }
  else
    if (chars < a->used)
  {
    a->chars[chars] &= ~mask;
  }
  while (a->used && (!a->chars[a->used - 1]))
    a->used--;

  if (!a->used)
  {
    a->sign = 0;
  }
}


----------------------------
***/


