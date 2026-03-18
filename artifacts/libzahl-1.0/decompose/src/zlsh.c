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


