static void zrand_get_random_bits(z_t r, size_t bits, int fd)
{
  size_t read_total = 0;
  size_t n;
  size_t chars = (bits + (32 - 1)) >> 5;
  ssize_t read_just;
  zahl_char_t mask = 1;
  char *buf;
  unsigned int buf_idx = 0;
  do
  {
    if (r->alloced < chars)
    {
      libzahl_realloc(r, chars);
    }
  }
  while (0);
  buf_idx = (char *) r->chars;
  for (n = chars * (sizeof(zahl_char_t)); n;)
  {
    read_just = read(fd, (&buf[buf_idx]) + read_total, n);
    if (read_just < 0)
    {
      libzahl_error = errno, longjmp(libzahl_jmp_buf, 1);
    }
    read_total += (size_t) read_just;
    n -= (size_t) read_just;
  }

  bits = bits & (32 - 1);
  mask <<= bits;
  mask -= 1;
  r->chars[chars - 1] &= mask;
  for (n = chars; n--;)
  {
    if (r->chars[n])
    {
      r->used = n + 1;
      r->sign = 1;
      return;
    }
  }

  r->sign = 0;
}


/*** DEPENDENCIES:
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
typedef uint32_t zahl_char_t
----------------------------
extern jmp_buf libzahl_jmp_buf
----------------------------
typedef struct 
{
  int sign;
  size_t used;
  size_t alloced;
  zahl_char_t *chars;
} z_t[1]
----------------------------
extern int libzahl_error
----------------------------
***/


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


/*** DEPENDENCIES:
extern z_t libzahl_const_1
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
enum zranddev
{
  FAST_RANDOM = 0,
  SECURE_RANDOM
}
----------------------------
enum zranddist
{
  QUASIUNIFORM = 0,
  UNIFORM
}
----------------------------
extern jmp_buf libzahl_jmp_buf
----------------------------
typedef struct 
{
  int sign;
  size_t used;
  size_t alloced;
  zahl_char_t *chars;
} z_t[1]
----------------------------
inline static int zzero(z_t a)
{
  return !a->sign;
}


----------------------------
inline static int zsignum(z_t a)
{
  return a->sign;
}


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
extern int libzahl_error
----------------------------
static void zrand_get_random_bits(z_t r, size_t bits, int fd)
{
  size_t read_total = 0;
  size_t n;
  size_t chars = (bits + (32 - 1)) >> 5;
  ssize_t read_just;
  zahl_char_t mask = 1;
  char *buf;
  unsigned int buf_idx = 0;
  do
  {
    if (r->alloced < chars)
    {
      libzahl_realloc(r, chars);
    }
  }
  while (0);
  buf_idx = (char *) r->chars;
  for (n = chars * (sizeof(zahl_char_t)); n;)
  {
    read_just = read(fd, (&buf[buf_idx]) + read_total, n);
    if (read_just < 0)
    {
      libzahl_error = errno, longjmp(libzahl_jmp_buf, 1);
    }
    read_total += (size_t) read_just;
    n -= (size_t) read_just;
  }

  bits = bits & (32 - 1);
  mask <<= bits;
  mask -= 1;
  r->chars[chars - 1] &= mask;
  for (n = chars; n--;)
  {
    if (r->chars[n])
    {
      r->used = n + 1;
      r->sign = 1;
      return;
    }
  }

  r->sign = 0;
}


----------------------------
***/


