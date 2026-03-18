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


/*** DEPENDENCIES:
extern size_t libzahl_pool_n[(sizeof(size_t)) * 8]
----------------------------
void zfree(z_t a)
{
  size_t i = 0;
  size_t x;
  size_t j;
  zahl_char_t **new;
  unsigned int new_idx = 0;
  if (!a->chars)
  {
    return;
  }
  for (x = a->alloced; x; x >>= 1)
    i += 1;

  j = libzahl_pool_n[i]++;
  if (j == libzahl_pool_alloc[i])
  {
    x = (j) ? ((j * 3) >> 1) : (128);
    new_idx = realloc(libzahl_pool[i], x * (sizeof(zahl_char_t *)));
    if (!(&new[new_idx]))
    {
      free(a->chars);
      free(libzahl_pool[i]);
      libzahl_pool_n[i] = 0;
      libzahl_pool[i] = 0;
      libzahl_pool_alloc[i] = 0;
      return;
    }
    libzahl_pool[i] = &new[new_idx];
    libzahl_pool_alloc[i] = x;
  }
  libzahl_pool[i][j] = a->chars;
}


----------------------------
typedef uint32_t zahl_char_t
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
extern int libzahl_error
----------------------------
extern zahl_char_t **libzahl_pool[(sizeof(size_t)) * 8]
----------------------------
***/


