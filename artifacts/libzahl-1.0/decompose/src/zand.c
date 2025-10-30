void zand(z_t a, z_t b, z_t c)
{
  size_t n;
  if (zzero(b) || zzero(c))
  {
    a->sign = 0;
    return;
  }
  n = (b->used < c->used) ? (b->used) : (c->used);
  while (n--)
    if (b->chars[n] & c->chars[n])
  {
    goto found_highest;
  }

  a->sign = 0;
  return;
  n += 1;
  found_highest:
  a->used = n;

  if (a == b)
  {
    while (n--)
      a->chars[n] &= c->chars[n];

  }
  else
    if (a == c)
  {
    while (n--)
      a->chars[n] &= b->chars[n];

  }
  else
  {
    do
    {
      if (a->alloced < a->used)
      {
        libzahl_realloc(a, a->used);
      }
    }
    while (0);
    memcpy(a->chars, c->chars, a->used * (sizeof(zahl_char_t)));
    while (n--)
      a->chars[n] &= b->chars[n];

  }
  a->sign = (((zsignum(b) > 0) || (zsignum(c) > 0)) * 2) - 1;
}


/*** DEPENDENCIES:
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
***/


