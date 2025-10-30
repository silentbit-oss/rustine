void zpowu(z_t a, z_t b, unsigned long long int c)
{
  if (!c)
  {
    if (zzero(b))
    {
      libzahl_error = EDOM, longjmp(libzahl_jmp_buf, 1);
    }
    zsetu(a, 1);
    return;
  }
  else
    if (zzero(b))
  {
    a->sign = 0;
    return;
  }
  zset(libzahl_tmp_pow_b, b);
  zsetu(a, 1);
  for (; c; c >>= 1)
  {
    if (c & 1)
    {
      zmul(a, a, libzahl_tmp_pow_b);
    }
    zsqr(libzahl_tmp_pow_b, libzahl_tmp_pow_b);
  }

}


/*** DEPENDENCIES:
extern z_t libzahl_tmp_pow_b
----------------------------
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
extern jmp_buf libzahl_jmp_buf
----------------------------
typedef struct 
{
  int sign;
  size_t used;
  size_t alloced;
  zahl_char_t *chars;
} z_t[1]
----------------------------
inline static int zzero(z_t a)
{
  return !a->sign;
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
extern int libzahl_error
----------------------------
***/


