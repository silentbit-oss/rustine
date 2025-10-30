size_t zstr_length(z_t a, unsigned long long int radix)
{
  size_t size_total = 1;
  size_t size_temp;
  zset(libzahl_tmp_str_num, a);
  while (!zzero(libzahl_tmp_str_num))
  {
    zsetu(libzahl_tmp_str_mag, radix);
    zset(libzahl_tmp_str_div, libzahl_tmp_str_mag);
    size_temp = 1;
    while (zcmpmag(libzahl_tmp_str_mag, libzahl_tmp_str_num) <= 0)
    {
      zset(libzahl_tmp_str_div, libzahl_tmp_str_mag);
      zsqr(libzahl_tmp_str_mag, libzahl_tmp_str_mag);
      size_temp <<= 1;
    }

    size_temp >>= 1;
    size_total += size_temp;
    zdiv(libzahl_tmp_str_num, libzahl_tmp_str_num, libzahl_tmp_str_div);
  }

  return size_total + (zsignum(a) < 0);
}


/*** DEPENDENCIES:
extern z_t libzahl_tmp_str_mag
----------------------------
extern z_t libzahl_tmp_str_div
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
void zdiv(z_t a, z_t b, z_t c)
{
  zdivmod(a, libzahl_tmp_div, b, c);
}


----------------------------
extern z_t libzahl_tmp_str_num
----------------------------
inline static int zsignum(z_t a)
{
  return a->sign;
}


----------------------------
***/


