size_t zsave(z_t a, void *buffer)
{
  if (buffer)
  {
    char *buf = buffer;
    unsigned int buf_idx = 0;
    *((int *) buf) = a->sign, buf_idx += sizeof(int);
    *((size_t *) buf) = a->used, buf_idx += sizeof(size_t);
    if (!zzero(a))
    {
      memcpy(buf, a->chars, a->used * (sizeof(zahl_char_t)));
    }
  }
  return ((sizeof(int)) + (sizeof(size_t))) + ((zzero(a)) ? (0) : (a->used * (sizeof(zahl_char_t))));
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


