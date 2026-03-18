size_t zlsb(z_t a)
{
  size_t i = 0;
  zahl_char_t x;
  if (zzero(a))
  {
    return SIZE_MAX;
  }
  for (;; i += 1)
  {
    x = a->chars[i];
    if (x)
    {
      x = ~x;
      for (i *= 32; x & 1; x >>= 1, i += 1)
        ;

      return i;
    }
  }

}


/*** DEPENDENCIES:
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
typedef uint32_t zahl_char_t
----------------------------
***/


