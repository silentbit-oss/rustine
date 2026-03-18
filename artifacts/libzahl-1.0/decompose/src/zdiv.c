void zdiv(z_t a, z_t b, z_t c)
{
  zdivmod(a, libzahl_tmp_div, b, c);
}


/*** DEPENDENCIES:
extern z_t libzahl_tmp_div
----------------------------
typedef struct 
{
  int sign;
  size_t used;
  size_t alloced;
  zahl_char_t *chars;
} z_t[1]
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


