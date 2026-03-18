void zmodsqr(z_t a, z_t b, z_t c)
{
  if (a == c)
  {
    zset(libzahl_tmp_modsqr, c);
    zsqr(a, b);
    zmod(a, a, libzahl_tmp_modsqr);
  }
  else
  {
    zsqr(a, b);
    zmod(a, a, c);
  }
}


/*** DEPENDENCIES:
extern z_t libzahl_tmp_modsqr
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
typedef struct 
{
  int sign;
  size_t used;
  size_t alloced;
  zahl_char_t *chars;
} z_t[1]
----------------------------
void zsqr(z_t a, z_t b)
{
  size_t m2;
  z_t z0;
  z_t z1;
  z_t z2;
  z_t high;
  z_t low;
  int sign;
  if (zzero(b))
  {
    a->sign = 0;
    return;
  }
  m2 = zbits(b);
  if (m2 <= (32 / 2))
  {
    do
    {
      if (a->alloced < 1)
      {
        libzahl_realloc(a, 1);
      }
    }
    while (0);
    a->used = 1;
    a->chars[0] = b->chars[0] * b->chars[0];
    a->sign = 1;
    return;
  }
  sign = zsignum(b);
  b->sign = 1;
  m2 >>= 1;
  zinit(z0);
  zinit(z1);
  zinit(z2);
  zinit(high);
  zinit(low);
  zsplit(high, low, b, m2);
  zsqr(z0, low);
  zsqr(z2, high);
  zmul(z1, low, high);
  zlsh(z1, z1, m2 + 1);
  m2 <<= 1;
  zlsh(z2, z2, m2);
  zadd(a, z2, z1);
  zadd(a, a, z0);
  zfree(z0);
  zfree(z1);
  zfree(z2);
  zfree(high);
  zfree(low);
  b->sign = sign;
  a->sign = 1;
}


----------------------------
void zmod(z_t a, z_t b, z_t c)
{
  zdivmod(libzahl_tmp_mod, a, b, c);
}


----------------------------
***/


