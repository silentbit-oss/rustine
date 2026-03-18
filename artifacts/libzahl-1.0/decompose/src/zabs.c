inline static void zinit(z_t a)
{
  a->alloced = 0;
  a->chars = 0;
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


inline static int zeven(z_t a)
{
  return (!a->sign) || (!(a->chars[0] & 1));
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


inline static int zodd(z_t a)
{
  return a->sign && (a->chars[0] & 1);
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


inline static int zeven_nonzero(z_t a)
{
  return !(a->chars[0] & 1);
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


inline static int zodd_nonzero(z_t a)
{
  return a->chars[0] & 1;
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


inline static int zzero(z_t a)
{
  return !a->sign;
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


inline static int zsignum(z_t a)
{
  return a->sign;
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
***/


