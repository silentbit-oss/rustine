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
***/


