void zswap(z_t a, z_t b)
{
  z_t t;
  *t = *a;
  *a = *b;
  *b = *t;
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
***/


