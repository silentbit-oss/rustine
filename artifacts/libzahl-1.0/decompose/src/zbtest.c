int zbtest(z_t a, size_t bit)
{
  size_t chars;
  if (zzero(a))
  {
    return 0;
  }
  chars = bit >> 5;
  if (chars >= a->used)
  {
    return 0;
  }
  bit = bit & (32 - 1);
  return (a->chars[chars] >> bit) & 1;
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
***/


