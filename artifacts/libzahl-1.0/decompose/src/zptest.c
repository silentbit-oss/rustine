// hint:  ['i_ref is a mutable refrence to size_t']
enum zprimality helper_zptest_1(size_t * const i_ref, z_t witness, z_t n, size_t r)
{
  size_t i = *i_ref;
  zrand(libzahl_tmp_ptest_a, FAST_RANDOM, UNIFORM, libzahl_tmp_ptest_n4);
  zadd_unsigned(libzahl_tmp_ptest_a, libzahl_tmp_ptest_a, libzahl_const_2);
  zmodpow(libzahl_tmp_ptest_x, libzahl_tmp_ptest_a, libzahl_tmp_ptest_d, n);
  if ((!zcmp(libzahl_tmp_ptest_x, libzahl_const_1)) || (!zcmp(libzahl_tmp_ptest_x, libzahl_tmp_ptest_n1)))
  {
    continue;
  }
  for (i = 1; i < r; i += 1)
  {
    zsqr(libzahl_tmp_ptest_x, libzahl_tmp_ptest_x);
    zmod(libzahl_tmp_ptest_x, libzahl_tmp_ptest_x, n);
    if (!zcmp(libzahl_tmp_ptest_x, libzahl_const_1))
    {
      if (witness)
      {
        zswap(witness, libzahl_tmp_ptest_a);
      }
      return NONPRIME;
    }
    if (!zcmp(libzahl_tmp_ptest_x, libzahl_tmp_ptest_n1))
    {
      break;
    }
  }

  if (i == r)
  {
    if (witness)
    {
      zswap(witness, libzahl_tmp_ptest_a);
    }
    return NONPRIME;
  }
  *i_ref = i;
}


/*** DEPENDENCIES:
extern z_t libzahl_tmp_ptest_x
----------------------------
extern z_t libzahl_tmp_ptest_d
----------------------------
extern z_t libzahl_const_1
----------------------------
void zmodpow(z_t a, z_t b, z_t c, z_t d)
{
  size_t i;
  size_t j;
  size_t n;
  size_t bits;
  zahl_char_t x;
  if (zsignum(c) <= 0)
  {
    if (zzero(c))
    {
      if (zzero(b))
      {
        libzahl_error = EDOM, longjmp(libzahl_jmp_buf, 1);
      }
      else
        if (zzero(d))
      {
        libzahl_error = EDOM, longjmp(libzahl_jmp_buf, 1);
      }
      zsetu(a, 1);
    }
    else
      if (zzero(b) || zzero(d))
    {
      libzahl_error = EDOM, longjmp(libzahl_jmp_buf, 1);
    }
    else
    {
      a->sign = 0;
    }
    return;
  }
  else
    if (zzero(d))
  {
    libzahl_error = EDOM, longjmp(libzahl_jmp_buf, 1);
  }
  else
    if (zzero(b))
  {
    a->sign = 0;
    return;
  }
  bits = zbits(c);
  n = bits >> 5;
  zmod(libzahl_tmp_pow_b, b, d);
  zset(libzahl_tmp_pow_c, c);
  zset(libzahl_tmp_pow_d, d);
  zsetu(a, 1);
  for (i = 0; i < n; i += 1)
  {
    x = libzahl_tmp_pow_c->chars[i];
    for (j = 32; j--; x >>= 1)
    {
      if (x & 1)
      {
        zmodmul(a, a, libzahl_tmp_pow_b, libzahl_tmp_pow_d);
      }
      zmodsqr(libzahl_tmp_pow_b, libzahl_tmp_pow_b, libzahl_tmp_pow_d);
    }

  }

  x = libzahl_tmp_pow_c->chars[i];
  for (; x; x >>= 1)
  {
    if (x & 1)
    {
      zmodmul(a, a, libzahl_tmp_pow_b, libzahl_tmp_pow_d);
    }
    zmodsqr(libzahl_tmp_pow_b, libzahl_tmp_pow_b, libzahl_tmp_pow_d);
  }

}


----------------------------
void zadd_unsigned(z_t a, z_t b, z_t c)
{
  size_t i;
  size_t size;
  size_t n;
  uint32_t carry[] = {0, 0};
  zahl_char_t *addend;
  unsigned int addend_idx = 0;
  if (zzero(b))
  {
    zabs(a, c);
    return;
  }
  else
    if (zzero(c))
  {
    zabs(a, b);
    return;
  }
  size = (b->used > c->used) ? (b->used) : (c->used);
  n = (b->used + c->used) - size;
  do
  {
    if (a->alloced < (size + 1))
    {
      libzahl_realloc(a, size + 1);
    }
  }
  while (0);
  a->chars[size] = 0;
  if (a == b)
  {
    if (a->used < c->used)
    {
      n = c->used;
      memset(a->chars + a->used, 0, (n - a->used) * (sizeof(zahl_char_t)));
    }
    addend_idx = c->chars;
  }
  else
    if (a == c)
  {
    if (a->used < b->used)
    {
      n = b->used;
      memset(a->chars + a->used, 0, (n - a->used) * (sizeof(zahl_char_t)));
    }
    addend_idx = b->chars;
  }
  else
    if (b->used > c->used)
  {
    memcpy(a->chars, b->chars, b->used * (sizeof(zahl_char_t)));
    a->used = b->used;
    addend_idx = c->chars;
  }
  else
  {
    memcpy(a->chars, c->chars, c->used * (sizeof(zahl_char_t)));
    a->used = c->used;
    addend_idx = b->chars;
  }
  for (i = 0; i < n; i += 1)
  {
    if (carry[i & 1])
    {
      carry[(~i) & 1] = (UINT32_MAX - a->chars[i]) <= addend[i + addend_idx];
    }
    else
      carry[(~i) & 1] = (UINT32_MAX - a->chars[i]) < addend[i + addend_idx];
    a->chars[i] += addend[i + addend_idx] + carry[i & 1];
  }

  while (carry[i & 1])
  {
    carry[(~i) & 1] = a->chars[i] == UINT32_MAX;
    a->chars[i] += 1;
    i += 1;
  }

  if (a->used < i)
  {
    a->used = i;
  }
  a->sign = 1;
}


----------------------------
extern z_t libzahl_const_2
----------------------------
extern z_t libzahl_tmp_ptest_n1
----------------------------
void zswap(z_t a, z_t b)
{
  z_t t;
  *t = *a;
  *a = *b;
  *b = *t;
}


----------------------------
extern z_t libzahl_tmp_ptest_a
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
typedef struct 
{
  int sign;
  size_t used;
  size_t alloced;
  zahl_char_t *chars;
} z_t[1]
----------------------------
void zsqr(z_t a, z_t b)
{
  size_t m2;
  z_t z0;
  z_t z1;
  z_t z2;
  z_t high;
  z_t low;
  int sign;
  if (zzero(b))
  {
    a->sign = 0;
    return;
  }
  m2 = zbits(b);
  if (m2 <= (32 / 2))
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
    a->chars[0] = b->chars[0] * b->chars[0];
    a->sign = 1;
    return;
  }
  sign = zsignum(b);
  b->sign = 1;
  m2 >>= 1;
  zinit(z0);
  zinit(z1);
  zinit(z2);
  zinit(high);
  zinit(low);
  zsplit(high, low, b, m2);
  zsqr(z0, low);
  zsqr(z2, high);
  zmul(z1, low, high);
  zlsh(z1, z1, m2 + 1);
  m2 <<= 1;
  zlsh(z2, z2, m2);
  zadd(a, z2, z1);
  zadd(a, a, z0);
  zfree(z0);
  zfree(z1);
  zfree(z2);
  zfree(high);
  zfree(low);
  b->sign = sign;
  a->sign = 1;
}


----------------------------
extern z_t libzahl_tmp_ptest_n4
----------------------------
void zrand(z_t r, enum zranddev dev, enum zranddist dist, z_t n)
{
  const char *pathname = 0;
  unsigned int pathname_idx = 0;
  size_t bits;
  int fd;
  switch (dev)
  {
    case FAST_RANDOM:
    {
      pathname_idx = "/dev/urandom";
      break;
    }

    case SECURE_RANDOM:
    {
      pathname_idx = "/dev/random";
      break;
    }

    default:
    {
      abort();
    }

  }

  if (zzero(n))
  {
    r->sign = 0;
    return;
  }
  fd = open(pathname, O_RDONLY);
  if (fd < 0)
  {
    libzahl_error = errno, longjmp(libzahl_jmp_buf, 1);
  }
  switch (dist)
  {
    case QUASIUNIFORM:
    {
      if (zsignum(n) < 0)
      {
        libzahl_error = EDOM, longjmp(libzahl_jmp_buf, 1);
      }
      bits = zbits(n);
      zrand_get_random_bits(r, bits, fd);
      zadd(r, r, libzahl_const_1);
      zmul(r, r, n);
      zrsh(r, r, bits);
      break;
    }

    case UNIFORM:
    {
      if (zsignum(n) < 0)
      {
        libzahl_error = EDOM, longjmp(libzahl_jmp_buf, 1);
      }
      bits = zbits(n);
      do
        zrand_get_random_bits(r, bits, fd);
      while (zcmpmag(r, n) > 0);
      break;
    }

    default:
    {
      abort();
    }

  }

  close(fd);
}


----------------------------
void zmod(z_t a, z_t b, z_t c)
{
  zdivmod(libzahl_tmp_mod, a, b, c);
}


----------------------------
***/


enum zprimality zptest(z_t witness, z_t n, int t)
{
  size_t i;
  size_t r;
  if (zcmpu(n, 3) <= 0)
  {
    if (zcmpu(n, 1) <= 0)
    {
      if (witness)
      {
        do
        {
          if (witness != n)
          {
            zset(witness, n);
          }
        }
        while (0);
      }
      return NONPRIME;
    }
    else
    {
      return PRIME;
    }
  }
  if (zeven(n))
  {
    if (witness)
    {
      do
      {
        if (witness != n)
        {
          zset(witness, n);
        }
      }
      while (0);
    }
    return NONPRIME;
  }
  zsub_unsigned(libzahl_tmp_ptest_n1, n, libzahl_const_1);
  zsub_unsigned(libzahl_tmp_ptest_n4, n, libzahl_const_4);
  r = zlsb(libzahl_tmp_ptest_n1);
  zrsh(libzahl_tmp_ptest_d, libzahl_tmp_ptest_n1, r);
  while (t--)
  {
    helper_zptest_1(&i, witness, n, r);
  }

  return PROBABLY_PRIME;
}


/*** DEPENDENCIES:
extern z_t libzahl_const_1
----------------------------
extern z_t libzahl_tmp_ptest_d
----------------------------
extern z_t libzahl_tmp_ptest_n1
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
extern z_t libzahl_const_4
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
enum zprimality helper_zptest_1(size_t * const i_ref, z_t witness, z_t n, size_t r)
{
  size_t i = *i_ref;
  zrand(libzahl_tmp_ptest_a, FAST_RANDOM, UNIFORM, libzahl_tmp_ptest_n4);
  zadd_unsigned(libzahl_tmp_ptest_a, libzahl_tmp_ptest_a, libzahl_const_2);
  zmodpow(libzahl_tmp_ptest_x, libzahl_tmp_ptest_a, libzahl_tmp_ptest_d, n);
  if ((!zcmp(libzahl_tmp_ptest_x, libzahl_const_1)) || (!zcmp(libzahl_tmp_ptest_x, libzahl_tmp_ptest_n1)))
  {
    continue;
  }
  for (i = 1; i < r; i += 1)
  {
    zsqr(libzahl_tmp_ptest_x, libzahl_tmp_ptest_x);
    zmod(libzahl_tmp_ptest_x, libzahl_tmp_ptest_x, n);
    if (!zcmp(libzahl_tmp_ptest_x, libzahl_const_1))
    {
      if (witness)
      {
        zswap(witness, libzahl_tmp_ptest_a);
      }
      return NONPRIME;
    }
    if (!zcmp(libzahl_tmp_ptest_x, libzahl_tmp_ptest_n1))
    {
      break;
    }
  }

  if (i == r)
  {
    if (witness)
    {
      zswap(witness, libzahl_tmp_ptest_a);
    }
    return NONPRIME;
  }
  *i_ref = i;
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
extern z_t libzahl_tmp_ptest_n4
----------------------------
inline static int zeven(z_t a)
{
  return (!a->sign) || (!(a->chars[0] & 1));
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
int zcmpu(z_t a, unsigned long long int b)
{
  if (!b)
  {
    return zsignum(a);
  }
  if (zsignum(a) <= 0)
  {
    return -1;
  }
  zsetu(libzahl_tmp_cmp, b);
  return zcmp(a, libzahl_tmp_cmp);
}


----------------------------
***/


