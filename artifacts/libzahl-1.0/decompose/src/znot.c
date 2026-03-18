void znot(z_t a, z_t b)
{
  size_t bits;
  size_t n;
  if (zzero(b))
  {
    a->sign = 0;
    return;
  }
  bits = zbits(b);
  do
  {
    if (a != b)
    {
      zset(a, b);
    }
  }
  while (0);
  a->sign = -zsignum(a);
  for (n = a->used; n--;)
    a->chars[n] = ~a->chars[n];

  bits = bits & (32 - 1);
  if (bits)
  {
    a->chars[a->used - 1] &= (((zahl_char_t) 1) << bits) - 1;
  }
  while (a->used && (!a->chars[a->used - 1]))
    a->used--;

  if (!a->used)
  {
    a->sign = 0;
  }
}


/*** DEPENDENCIES:
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


