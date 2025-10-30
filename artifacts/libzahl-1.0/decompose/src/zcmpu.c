int zcmpu(z_t a, unsigned long long int b)
{
  if (!b)
  {
    return zsignum(a);
  }
  if (zsignum(a) <= 0)
  {
    return -1;
  }
  zsetu(libzahl_tmp_cmp, b);
  return zcmp(a, libzahl_tmp_cmp);
}


/*** DEPENDENCIES:
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
void zsetu(z_t a, unsigned long long int b)
{
  if (!b)
  {
    a->sign = 0;
    return;
  }
  do
  {
    if (a->alloced < ((((sizeof(b)) + (sizeof(*a->chars))) - 1) / (sizeof(*a->chars))))
    {
      libzahl_realloc(a, (((sizeof(b)) + (sizeof(*a->chars))) - 1) / (sizeof(*a->chars)));
    }
  }
  while (0);
  a->sign = 1;
  a->used = 0;
  while (b)
  {
    a->chars[a->used++] = (zahl_char_t) b;
    b >>= 32;
  }

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


