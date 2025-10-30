int zsets(z_t a, const char *str)
{
  unsigned int str_idx = 0;
  unsigned long long int temp = 0;
  int neg = str[str_idx] == '-';
  const char *str_end;
  unsigned int str_end_idx = 0;
  str_idx += neg || ((*str_idx) == '+');
  if (!(*(&str[str_idx])))
  {
    errno = EINVAL;
    return -1;
  }
  for (str_end_idx = &str[str_idx]; str_end[str_end_idx]; str_end_idx += 1)
  {
    if (!isdigit(*(&str_end[str_end_idx])))
    {
      errno = EINVAL;
      return -1;
    }
  }

  a->sign = 0;
  zset(libzahl_tmp_str_num, libzahl_const_1e19);
  switch (((&str_end[str_end_idx]) - (&str[str_idx])) % 19)
  {
    while (str[str_idx])
    {
      zmul(a, a, libzahl_const_1e19);
      temp = 0;
      case 0:
        temp *= 10, temp += str[str_idx] & 15;
        str_idx += 1;

      case 18:
        temp *= 10, temp += str[str_idx] & 15;
        str_idx += 1;

      case 17:
        temp *= 10, temp += str[str_idx] & 15;
        str_idx += 1;

      case 16:
        temp *= 10, temp += str[str_idx] & 15;
        str_idx += 1;

      case 15:
        temp *= 10, temp += str[str_idx] & 15;
        str_idx += 1;

      case 14:
        temp *= 10, temp += str[str_idx] & 15;
        str_idx += 1;

      case 13:
        temp *= 10, temp += str[str_idx] & 15;
        str_idx += 1;

      case 12:
        temp *= 10, temp += str[str_idx] & 15;
        str_idx += 1;

      case 11:
        temp *= 10, temp += str[str_idx] & 15;
        str_idx += 1;

      case 10:
        temp *= 10, temp += str[str_idx] & 15;
        str_idx += 1;

      case 9:
        temp *= 10, temp += str[str_idx] & 15;
        str_idx += 1;

      case 8:
        temp *= 10, temp += str[str_idx] & 15;
        str_idx += 1;

      case 7:
        temp *= 10, temp += str[str_idx] & 15;
        str_idx += 1;

      case 6:
        temp *= 10, temp += str[str_idx] & 15;
        str_idx += 1;

      case 5:
        temp *= 10, temp += str[str_idx] & 15;
        str_idx += 1;

      case 4:
        temp *= 10, temp += str[str_idx] & 15;
        str_idx += 1;

      case 3:
        temp *= 10, temp += str[str_idx] & 15;
        str_idx += 1;

      case 2:
        temp *= 10, temp += str[str_idx] & 15;
        str_idx += 1;

      case 1:
        temp *= 10, temp += str[str_idx] & 15;
        str_idx += 1;

      if (!temp)
      {
        continue;
      }
      libzahl_tmp_str_num->chars[0] = (zahl_char_t) temp;
      temp >>= 32;
      libzahl_tmp_str_num->chars[1] = (zahl_char_t) temp;
      libzahl_tmp_str_num->used = 1 + (!(!temp));
      zadd(a, a, libzahl_tmp_str_num);
    }

  }

  if (neg)
  {
    a->sign = -zsignum(a);
  }
  return 0;
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
void zadd(z_t a, z_t b, z_t c)
{
  if (zzero(b))
  {
    do
    {
      if (a != c)
      {
        zset(a, c);
      }
    }
    while (0);
  }
  else
    if (zzero(c))
  {
    do
    {
      if (a != b)
      {
        zset(a, b);
      }
    }
    while (0);
  }
  else
    if (b == c)
  {
    zlsh(a, b, 1);
  }
  else
    if ((zsignum(b) | zsignum(c)) < 0)
  {
    if (zsignum(b) < 0)
    {
      if (zsignum(c) < 0)
      {
        zadd_unsigned(a, b, c);
        a->sign = -zsignum(a);
      }
      else
      {
        zsub_unsigned(a, c, b);
      }
    }
    else
    {
      zsub_unsigned(a, b, c);
    }
  }
  else
  {
    zadd_unsigned(a, b, c);
  }
}


----------------------------
extern z_t libzahl_const_1e19
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
inline static int zsignum(z_t a)
{
  return a->sign;
}


----------------------------
extern z_t libzahl_tmp_str_num
----------------------------
***/


