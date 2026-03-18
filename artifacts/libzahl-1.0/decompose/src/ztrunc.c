void ztrunc(z_t a, z_t b, size_t bits)
{
  zahl_char_t mask = 1;
  size_t chars;
  size_t i;
  if (zzero(b))
  {
    a->sign = 0;
    return;
  }
  chars = (bits + (32 - 1)) >> 5;
  a->sign = b->sign;
  a->used = (chars < b->used) ? (chars) : (b->used);
  if (a->used < chars)
  {
    bits = 0;
  }
  if (a != b)
  {
    do
    {
      if (a->alloced < a->used)
      {
        libzahl_realloc(a, a->used);
      }
    }
    while (0);
    memcpy(a->chars, b->chars, a->used * (sizeof(zahl_char_t)));
  }
  bits = bits & (32 - 1);
  if (bits)
  {
    mask <<= bits;
    mask -= 1;
    a->chars[a->used - 1] &= mask;
  }
  for (i = a->used; i--;)
    if (a->chars[i])
  {
    return;
  }

  a->sign = 0;
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
***/


