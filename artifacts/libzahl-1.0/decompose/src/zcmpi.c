int zcmpi(z_t a, long long int b)
{
  if (!b)
  {
    return zsignum(a);
  }
  if (zzero(a))
  {
    return (b > 0) ? (-1) : (b < 0);
  }
  zseti(libzahl_tmp_cmp, b);
  return zcmp(a, libzahl_tmp_cmp);
}


/*** DEPENDENCIES:
void zseti(z_t a, long long int b)
{
  if (b >= 0)
  {
    zsetu(a, (unsigned long long int) b);
  }
  else
  {
    zsetu(a, (unsigned long long int) (-b));
    a->sign = -1;
  }
}


----------------------------
extern z_t libzahl_tmp_cmp
----------------------------
int zcmp(z_t a, z_t b)
{
  if (zsignum(a) != zsignum(b))
  {
    return (zsignum(a) < zsignum(b)) ? (-1) : (zsignum(a) > zsignum(b));
  }
  return zsignum(a) * zcmpmag(a, b);
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


