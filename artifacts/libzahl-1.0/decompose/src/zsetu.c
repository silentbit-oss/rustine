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


/*** DEPENDENCIES:
typedef struct 
{
  int sign;
  size_t used;
  size_t alloced;
  zahl_char_t *chars;
} z_t[1]
----------------------------
void libzahl_realloc(z_t a, size_t need)
{
  size_t i;
  size_t x;
  zahl_char_t *new;
  unsigned int new_idx = 0;
  if ((need & ((~need) + 1)) != need)
  {
    need |= need >> 1;
    need |= need >> 2;
    need |= need >> 4;
    for (i = sizeof(need), x = 8; i; i >>= 1, x <<= 1)
      need |= need >> x;

    need += 1;
  }
  for (i = 0, x = need; x; x >>= 1)
    i += 1;

  if (libzahl_pool_n[i])
  {
    libzahl_pool_n[i] -= 1;
    new_idx = libzahl_pool[i][libzahl_pool_n[i]];
    memcpy(new, a->chars, a->alloced * (sizeof(zahl_char_t)));
    zfree(a);
    a->chars = &new[new_idx];
  }
  else
  {
    a->chars = realloc(a->chars, need * (sizeof(zahl_char_t)));
    if (!a->chars)
    {
      if (!errno)
      {
        errno = ENOMEM;
      }
      libzahl_error = errno, longjmp(libzahl_jmp_buf, 1);
    }
  }
  a->alloced = need;
}


----------------------------
***/


