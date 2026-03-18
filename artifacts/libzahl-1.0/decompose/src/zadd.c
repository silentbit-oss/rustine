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


/*** DEPENDENCIES:
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
***/


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
***/


