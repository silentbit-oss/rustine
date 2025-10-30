void zsplit(z_t high, z_t low, z_t a, size_t delim)
{
  if (zzero(a))
  {
    high->sign = 0;
    low->sign = 0;
    return;
  }
  if (high == a)
  {
    ztrunc(low, a, delim);
    zrsh(high, a, delim);
  }
  else
  {
    zrsh(high, a, delim);
    ztrunc(low, a, delim);
  }
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
***/


