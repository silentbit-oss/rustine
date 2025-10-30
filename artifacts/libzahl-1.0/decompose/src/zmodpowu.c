void zmodpowu(z_t a, z_t b, unsigned long long int c, z_t d)
{
  if (!c)
  {
    if (zzero(b))
    {
      libzahl_error = EDOM, longjmp(libzahl_jmp_buf, 1);
    }
    else
      if (zzero(d))
    {
      libzahl_error = EDOM, longjmp(libzahl_jmp_buf, 1);
    }
    else
      zsetu(a, 1);
    return;
  }
  else
    if (zzero(d))
  {
    libzahl_error = EDOM, longjmp(libzahl_jmp_buf, 1);
  }
  else
    if (zzero(b))
  {
    a->sign = 0;
    return;
  }
  zmod(libzahl_tmp_pow_b, b, d);
  zset(libzahl_tmp_pow_d, d);
  zsetu(a, 1);
  for (; c; c >>= 1)
  {
    if (c & 1)
    {
      zmodmul(a, a, libzahl_tmp_pow_b, libzahl_tmp_pow_d);
    }
    zmodsqr(libzahl_tmp_pow_b, libzahl_tmp_pow_b, libzahl_tmp_pow_d);
  }

}


/*** DEPENDENCIES:
extern z_t libzahl_tmp_pow_b
----------------------------
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
extern z_t libzahl_tmp_pow_d
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
void zmod(z_t a, z_t b, z_t c)
{
  zdivmod(libzahl_tmp_mod, a, b, c);
}


----------------------------
extern int libzahl_error
----------------------------
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


----------------------------
***/


