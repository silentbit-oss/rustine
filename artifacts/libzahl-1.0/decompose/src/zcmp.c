int zcmp(z_t a, z_t b)
{
  if (zsignum(a) != zsignum(b))
  {
    return (zsignum(a) < zsignum(b)) ? (-1) : (zsignum(a) > zsignum(b));
  }
  return zsignum(a) * zcmpmag(a, b);
}


/*** DEPENDENCIES:
typedef struct 
{
  int sign;
  size_t used;
  size_t alloced;
  zahl_char_t *chars;
} z_t[1]
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
inline static int zsignum(z_t a)
{
  return a->sign;
}


----------------------------
***/


