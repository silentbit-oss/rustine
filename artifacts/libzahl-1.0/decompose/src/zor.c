void zor(z_t a, z_t b, z_t c)
{
  size_t n;
  size_t m;
  if (zzero(b))
  {
    if (zzero(c))
    {
      a->sign = 0;
    }
    else
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
    return;
  }
  m = (b->used > c->used) ? (b->used) : (c->used);
  n = (b->used + c->used) - m;
  do
  {
    if (a->alloced < m)
    {
      libzahl_realloc(a, m);
    }
  }
  while (0);
  if (a == b)
  {
    if (b->used < c->used)
    {
      memcpy(a->chars + n, c->chars + n, (m - n) * (sizeof(zahl_char_t)));
    }
    while (n--)
      a->chars[n] |= c->chars[n];

  }
  else
    if (a == c)
  {
    if (c->used < b->used)
    {
      memcpy(a->chars + n, b->chars + n, (m - n) * (sizeof(zahl_char_t)));
    }
    while (n--)
      a->chars[n] |= b->chars[n];

  }
  else
    if (m == b->used)
  {
    memcpy(a->chars, b->chars, m * (sizeof(zahl_char_t)));
    while (n--)
      a->chars[n] |= c->chars[n];

  }
  else
  {
    memcpy(a->chars, c->chars, m * (sizeof(zahl_char_t)));
    while (n--)
      a->chars[n] |= b->chars[n];

  }
  a->used = m;
  a->sign = (((zsignum(b) > 0) && (zsignum(c) > 0)) * 2) - 1;
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


