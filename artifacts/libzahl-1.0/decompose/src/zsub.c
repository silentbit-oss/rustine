void zsub_unsigned(z_t a, z_t b, z_t c)
{
  zahl_char_t carry[] = {0, 0};
  zahl_char_t *s;
  unsigned int s_idx = 0;
  size_t i;
  size_t n;
  int magcmp;
  if (zzero(b))
  {
    zabs(a, c);
    zneg(a, a);
    return;
  }
  else
    if (zzero(c))
  {
    zabs(a, b);
    return;
  }
  magcmp = zcmpmag(b, c);
  if (magcmp <= 0)
  {
    if (magcmp == 0)
    {
      a->sign = 0;
      return;
    }
    n = (b->used < c->used) ? (b->used) : (c->used);
    if (a == b)
    {
      zset(libzahl_tmp_sub, b);
      s_idx = libzahl_tmp_sub->chars;
    }
    else
    {
      s_idx = b->chars;
    }
    do
    {
      if (a != c)
      {
        zset(a, c);
      }
    }
    while (0);
  }
  else
  {
    n = (b->used < c->used) ? (b->used) : (c->used);
    if (a == c)
    {
      zset(libzahl_tmp_sub, c);
      s_idx = libzahl_tmp_sub->chars;
    }
    else
    {
      s_idx = c->chars;
    }
    do
    {
      if (a != b)
      {
        zset(a, b);
      }
    }
    while (0);
  }
  for (i = 0; i < n; i += 1)
  {
    carry[(~i) & 1] = (carry[i & 1]) ? (a->chars[i] <= s[i + s_idx]) : (a->chars[i] < s[i + s_idx]);
    a->chars[i] -= s[i + s_idx];
    a->chars[i] -= carry[i & 1];
  }

  if (carry[i & 1])
  {
    while (!a->chars[i])
      a->chars[i] = UINT32_MAX;

    i += 1;
    a->chars[i] -= 1;
  }
  a->sign = magcmp;
}


/*** DEPENDENCIES:
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


----------------------------
int zcmpmag(z_t a, z_t b)
{
  size_t i;
  size_t j;
  if (zzero(a))
  {
    return -(!zzero(b));
  }
  if (zzero(b))
  {
    return 1;
  }
  i = a->used - 1;
  j = b->used - 1;
  for (; i > j; i -= 1)
  {
    if (a->chars[i])
    {
      return +1;
    }
    a->used -= 1;
  }

  for (; j > i; j -= 1)
  {
    if (b->chars[j])
    {
      return -1;
    }
    b->used -= 1;
  }

  for (; i; i -= 1)
    if (a->chars[i] != b->chars[i])
  {
    return ((a->chars[i] > b->chars[i]) * 2) - 1;
  }

  return (a->chars[0] < b->chars[0]) ? (-1) : (a->chars[0] > b->chars[0]);
}


----------------------------
extern z_t libzahl_tmp_sub
----------------------------
typedef uint32_t zahl_char_t
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
void zneg(z_t a, z_t b)
{
  do
  {
    if (a != b)
    {
      zset(a, b);
    }
  }
  while (0);
  a->sign = -zsignum(a);
}


----------------------------
***/


void zsub(z_t a, z_t b, z_t c)
{
  if (b == c)
  {
    a->sign = 0;
  }
  else
    if (zzero(b))
  {
    zneg(a, c);
  }
  else
    if (zzero(c))
  {
    do
    {
      if (a != b)
      {
        zset(a, b);
      }
    }
    while (0);
  }
  else
    if ((zsignum(b) | zsignum(c)) < 0)
  {
    if (zsignum(b) < 0)
    {
      if (zsignum(c) < 0)
      {
        zsub_unsigned(a, c, b);
      }
      else
      {
        zadd_unsigned(a, b, c);
        a->sign = -zsignum(a);
      }
    }
    else
    {
      zadd_unsigned(a, b, c);
    }
  }
  else
  {
    zsub_unsigned(a, b, c);
  }
}


/*** DEPENDENCIES:
void zadd_unsigned(z_t a, z_t b, z_t c)
{
  size_t i;
  size_t size;
  size_t n;
  uint32_t carry[] = {0, 0};
  zahl_char_t *addend;
  unsigned int addend_idx = 0;
  if (zzero(b))
  {
    zabs(a, c);
    return;
  }
  else
    if (zzero(c))
  {
    zabs(a, b);
    return;
  }
  size = (b->used > c->used) ? (b->used) : (c->used);
  n = (b->used + c->used) - size;
  do
  {
    if (a->alloced < (size + 1))
    {
      libzahl_realloc(a, size + 1);
    }
  }
  while (0);
  a->chars[size] = 0;
  if (a == b)
  {
    if (a->used < c->used)
    {
      n = c->used;
      memset(a->chars + a->used, 0, (n - a->used) * (sizeof(zahl_char_t)));
    }
    addend_idx = c->chars;
  }
  else
    if (a == c)
  {
    if (a->used < b->used)
    {
      n = b->used;
      memset(a->chars + a->used, 0, (n - a->used) * (sizeof(zahl_char_t)));
    }
    addend_idx = b->chars;
  }
  else
    if (b->used > c->used)
  {
    memcpy(a->chars, b->chars, b->used * (sizeof(zahl_char_t)));
    a->used = b->used;
    addend_idx = c->chars;
  }
  else
  {
    memcpy(a->chars, c->chars, c->used * (sizeof(zahl_char_t)));
    a->used = c->used;
    addend_idx = b->chars;
  }
  for (i = 0; i < n; i += 1)
  {
    if (carry[i & 1])
    {
      carry[(~i) & 1] = (UINT32_MAX - a->chars[i]) <= addend[i + addend_idx];
    }
    else
      carry[(~i) & 1] = (UINT32_MAX - a->chars[i]) < addend[i + addend_idx];
    a->chars[i] += addend[i + addend_idx] + carry[i & 1];
  }

  while (carry[i & 1])
  {
    carry[(~i) & 1] = a->chars[i] == UINT32_MAX;
    a->chars[i] += 1;
    i += 1;
  }

  if (a->used < i)
  {
    a->used = i;
  }
  a->sign = 1;
}


----------------------------
void zsub_unsigned(z_t a, z_t b, z_t c)
{
  zahl_char_t carry[] = {0, 0};
  zahl_char_t *s;
  unsigned int s_idx = 0;
  size_t i;
  size_t n;
  int magcmp;
  if (zzero(b))
  {
    zabs(a, c);
    zneg(a, a);
    return;
  }
  else
    if (zzero(c))
  {
    zabs(a, b);
    return;
  }
  magcmp = zcmpmag(b, c);
  if (magcmp <= 0)
  {
    if (magcmp == 0)
    {
      a->sign = 0;
      return;
    }
    n = (b->used < c->used) ? (b->used) : (c->used);
    if (a == b)
    {
      zset(libzahl_tmp_sub, b);
      s_idx = libzahl_tmp_sub->chars;
    }
    else
    {
      s_idx = b->chars;
    }
    do
    {
      if (a != c)
      {
        zset(a, c);
      }
    }
    while (0);
  }
  else
  {
    n = (b->used < c->used) ? (b->used) : (c->used);
    if (a == c)
    {
      zset(libzahl_tmp_sub, c);
      s_idx = libzahl_tmp_sub->chars;
    }
    else
    {
      s_idx = c->chars;
    }
    do
    {
      if (a != b)
      {
        zset(a, b);
      }
    }
    while (0);
  }
  for (i = 0; i < n; i += 1)
  {
    carry[(~i) & 1] = (carry[i & 1]) ? (a->chars[i] <= s[i + s_idx]) : (a->chars[i] < s[i + s_idx]);
    a->chars[i] -= s[i + s_idx];
    a->chars[i] -= carry[i & 1];
  }

  if (carry[i & 1])
  {
    while (!a->chars[i])
      a->chars[i] = UINT32_MAX;

    i += 1;
    a->chars[i] -= 1;
  }
  a->sign = magcmp;
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
void zneg(z_t a, z_t b)
{
  do
  {
    if (a != b)
    {
      zset(a, b);
    }
  }
  while (0);
  a->sign = -zsignum(a);
}


----------------------------
inline static int zsignum(z_t a)
{
  return a->sign;
}


----------------------------
***/


