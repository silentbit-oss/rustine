char *zstr(z_t a, char *b)
{
  unsigned int b_idx = 0;
  char buf[9 + 1];
  size_t n;
  size_t len;
  char overridden = 0;
  int neg;
  if (zzero(a))
  {
    if (!(&b[b_idx]))
    {
      b_idx = malloc(2);
      if (!(&b[b_idx]))
      {
        libzahl_error = errno, longjmp(libzahl_jmp_buf, 1);
      }
    }
    b[0 + b_idx] = '0';
    b[1 + b_idx] = 0;
    return b;
  }
  n = zstr_length(a, 10);
  if (!(&b[b_idx]))
  {
    b_idx = malloc(n + 1);
    if (!(&b[b_idx]))
    {
      libzahl_error = errno, longjmp(libzahl_jmp_buf, 1);
    }
  }
  neg = zsignum(a) < 0;
  zabs(libzahl_tmp_str_num, a);
  b[0 + b_idx] = '-';
  b_idx += neg;
  n -= neg;
  n = (n > 9) ? (n - 9) : (0);
  for (;;)
  {
    zdivmod(libzahl_tmp_str_num, libzahl_tmp_str_rem, libzahl_tmp_str_num, libzahl_const_1e9);
    if (!zzero(libzahl_tmp_str_num))
    {
      sprintf((&b[b_idx]) + n, "%09lu", (zzero(libzahl_tmp_str_rem)) ? (0UL) : ((unsigned long) libzahl_tmp_str_rem->chars[0]));
      b[(n + 9) + b_idx] = overridden;
      overridden = b[n + b_idx];
      n = (n > 9) ? (n - 9) : (0);
    }
    else
    {
      len = (size_t) sprintf(buf, "%lu", (unsigned long) libzahl_tmp_str_rem->chars[0]);
      if (overridden)
      {
        buf[len] = b[(n + len) + b_idx];
      }
      memcpy((&b[b_idx]) + n, buf, len + 1);
      break;
    }
  }

  return (&b[b_idx]) - neg;
}


/*** DEPENDENCIES:
void zabs(z_t a, z_t b)
{
  do
  {
    if (a != b)
    {
      zset(a, b);
    }
  }
  while (0);
  a->sign = !zzero(a);
}


----------------------------
extern z_t libzahl_tmp_str_rem
----------------------------
extern z_t libzahl_const_1e9
----------------------------
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
inline static int zsignum(z_t a)
{
  return a->sign;
}


----------------------------
extern z_t libzahl_tmp_str_num
----------------------------
extern int libzahl_error
----------------------------
void zdivmod(z_t a, z_t b, z_t c, z_t d)
{
  size_t c_bits;
  size_t d_bits;
  size_t bit;
  int sign;
  int cmpmag;
  sign = zsignum(c) * zsignum(d);
  if (!sign)
  {
    if (zzero(c))
    {
      if (zzero(d))
      {
        libzahl_error = EDOM, longjmp(libzahl_jmp_buf, 1);
      }
      else
      {
        a->sign = 0;
        b->sign = 0;
      }
    }
    else
    {
      libzahl_error = EDOM, longjmp(libzahl_jmp_buf, 1);
    }
    return;
  }
  else
    if ((cmpmag = zcmpmag(c, d)) <= 0)
  {
    if (cmpmag == 0)
    {
      zseti(a, sign);
      b->sign = 0;
      return;
    }
    else
    {
      do
      {
        if (b != c)
        {
          zset(b, c);
        }
      }
      while (0);
    }
    b->sign = 1;
    a->sign = 0;
    return;
  }
  c_bits = zbits(c);
  d_bits = zbits(d);
  bit = c_bits - d_bits;
  zlsh(libzahl_tmp_divmod_d, d, bit);
  libzahl_tmp_divmod_d->sign = 1;
  if (zcmpmag(libzahl_tmp_divmod_d, c) > 0)
  {
    zrsh(libzahl_tmp_divmod_d, libzahl_tmp_divmod_d, 1);
    bit -= 1;
  }
  libzahl_tmp_divmod_a->sign = 0;
  zabs(libzahl_tmp_divmod_b, c);
  if (bit < 32)
  {
    for (;;)
    {
      if (zcmpmag(libzahl_tmp_divmod_d, libzahl_tmp_divmod_b) <= 0)
      {
        zsub(libzahl_tmp_divmod_b, libzahl_tmp_divmod_b, libzahl_tmp_divmod_d);
        zbset(libzahl_tmp_divmod_a, libzahl_tmp_divmod_a, bit, 1);
      }
      if ((!(bit--)) || zzero(libzahl_tmp_divmod_b))
      {
        goto done;
      }
      zrsh(libzahl_tmp_divmod_d, libzahl_tmp_divmod_d, 1);
    }

  }
  else
  {
    size_t i;
    for (i = 0; i < 32; i += 1)
      zrsh(libzahl_tmp_divmod_ds[i], libzahl_tmp_divmod_d, i);

    for (;;)
    {
      for (i = 0; i < 32; i += 1)
      {
        if (zcmpmag(libzahl_tmp_divmod_ds[i], libzahl_tmp_divmod_b) <= 0)
        {
          zsub(libzahl_tmp_divmod_b, libzahl_tmp_divmod_b, libzahl_tmp_divmod_ds[i]);
          zbset(libzahl_tmp_divmod_a, libzahl_tmp_divmod_a, bit, 1);
        }
        if ((!(bit--)) || zzero(libzahl_tmp_divmod_b))
        {
          goto done;
        }
      }

      for (i = ((bit < (32 - 1)) ? (bit) : (32 - 1)) + 1; i--;)
        zrsh(libzahl_tmp_divmod_ds[i], libzahl_tmp_divmod_ds[i], 32);

    }

  }
  done:
  zswap(a, libzahl_tmp_divmod_a);

  zswap(b, libzahl_tmp_divmod_b);
  a->sign = sign;
}


----------------------------
***/


