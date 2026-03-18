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


/*** DEPENDENCIES:
extern size_t libzahl_pool_alloc[(sizeof(size_t)) * 8]
----------------------------
extern size_t libzahl_pool_n[(sizeof(size_t)) * 8]
----------------------------
typedef uint32_t zahl_char_t
----------------------------
typedef struct 
{
  int sign;
  size_t used;
  size_t alloced;
  zahl_char_t *chars;
} z_t[1]
----------------------------
extern zahl_char_t **libzahl_pool[(sizeof(size_t)) * 8]
----------------------------
***/


