void zmodmul(z_t a, z_t b, z_t c, z_t d)
{
  if (a == d)
  {
    zset(libzahl_tmp_modmul, d);
    zmul(a, b, c);
    zmod(a, a, libzahl_tmp_modmul);
  }
  else
  {
    zmul(a, b, c);
    zmod(a, a, d);
  }
}


/*** DEPENDENCIES:
void zmul(z_t a, z_t b, z_t c)
{
  size_t m;
  size_t m2;
  z_t z0;
  z_t z1;
  z_t z2;
  z_t b_high;
  z_t b_low;
  z_t c_high;
  z_t c_low;
  int b_sign;
  int c_sign;
  b_sign = zsignum(b);
  c_sign = zsignum(c);
  if ((!b_sign) || (!c_sign))
  {
    a->sign = 0;
    return;
  }
  m = zbits(b);
  m2 = (b == c) ? (m) : (zbits(c));
  if ((m + m2) <= 32)
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
    a->chars[0] = b->chars[0] * c->chars[0];
    a->sign = b_sign * c_sign;
    return;
  }
  b->sign = 1;
  c->sign = 1;
  m = (m > m2) ? (m) : (m2);
  m2 = m >> 1;
  zinit(z0);
  zinit(z1);
  zinit(z2);
  zinit(b_high);
  zinit(b_low);
  zinit(c_high);
  zinit(c_low);
  zsplit(b_high, b_low, b, m2);
  zsplit(c_high, c_low, c, m2);
  zmul(z0, b_low, c_low);
  zmul(z2, b_high, c_high);
  zadd(b_low, b_low, b_high);
  zadd(c_low, c_low, c_high);
  zmul(z1, b_low, c_low);
  zsub(z1, z1, z0);
  zsub(z1, z1, z2);
  zlsh(z1, z1, m2);
  m2 <<= 1;
  zlsh(z2, z2, m2);
  zadd(a, z2, z1);
  zadd(a, a, z0);
  zfree(z0);
  zfree(z1);
  zfree(z2);
  zfree(b_high);
  zfree(b_low);
  zfree(c_high);
  zfree(c_low);
  b->sign = b_sign;
  c->sign = c_sign;
  a->sign = b_sign * c_sign;
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
typedef struct 
{
  int sign;
  size_t used;
  size_t alloced;
  zahl_char_t *chars;
} z_t[1]
----------------------------
extern z_t libzahl_tmp_modmul
----------------------------
void zmod(z_t a, z_t b, z_t c)
{
  zdivmod(libzahl_tmp_mod, a, b, c);
}


----------------------------
***/


