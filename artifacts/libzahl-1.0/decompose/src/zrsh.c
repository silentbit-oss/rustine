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
***/


