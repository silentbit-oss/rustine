#include <errno.h>
#include <internals.h>
#include <setjmp.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <zadd.c>
#include <zahl.h>

typedef uint32_t zahl_char_t;
typedef struct 
{
  int sign;
  size_t used;
  size_t alloced;
  zahl_char_t *chars;
} z_t[1];
enum zprimality
{
  NONPRIME = 0,
  PROBABLY_PRIME,
  PRIME
};
enum zranddev
{
  FAST_RANDOM = 0,
  SECURE_RANDOM
};
enum zranddist
{
  QUASIUNIFORM = 0,
  UNIFORM
};
enum zerror
{
  ZERROR_ERRNO_SET = 0
};
void zsetup(jmp_buf);
void zunsetup(void);
void zfree(z_t);
void zswap(z_t, z_t);
size_t zsave(z_t, void *);
size_t zload(z_t, const void *);
void zset(z_t, z_t);
void zseti(z_t, long long int);
void zsetu(z_t, unsigned long long int);
int zcmp(z_t, z_t);
int zcmpi(z_t, long long int);
int zcmpu(z_t, unsigned long long int);
int zcmpmag(z_t, z_t);
void zadd(z_t, z_t, z_t);
void zsub(z_t, z_t, z_t);
void zmul(z_t, z_t, z_t);
void zmodmul(z_t, z_t, z_t, z_t);
void zdiv(z_t, z_t, z_t);
void zdivmod(z_t, z_t, z_t, z_t);
void zmod(z_t, z_t, z_t);
void zsqr(z_t, z_t);
void zmodsqr(z_t, z_t, z_t);
void zneg(z_t, z_t);
void zabs(z_t, z_t);
void zpow(z_t, z_t, z_t);
void zmodpow(z_t, z_t, z_t, z_t);
void zpowu(z_t, z_t, unsigned long long int);
void zmodpowu(z_t, z_t, unsigned long long int, z_t);
void zadd_unsigned(z_t, z_t, z_t);
void zsub_unsigned(z_t, z_t, z_t);
void zand(z_t, z_t, z_t);
void zor(z_t, z_t, z_t);
void zxor(z_t, z_t, z_t);
void znot(z_t, z_t);
void zlsh(z_t, z_t, size_t);
void zrsh(z_t, z_t, size_t);
void ztrunc(z_t, z_t, size_t);
int zbtest(z_t, size_t);
void zsplit(z_t, z_t, z_t, size_t);
size_t zbits(z_t);
size_t zlsb(z_t);
void zbset(z_t, z_t, size_t, int);
void zgcd(z_t, z_t, z_t);
enum zprimality zptest(z_t, z_t, int);
void zrand(z_t, enum zranddev, enum zranddist, z_t);
char *zstr(z_t, char *);
int zsets(z_t, const char *);
size_t zstr_length(z_t, unsigned long long int);
enum zerror zerror(const char **);
void zperror(const char *);
inline static void zinit(z_t a)
{
  a->alloced = 0;
  a->chars = 0;
}

inline static int zeven(z_t a)
{
  return (!a->sign) || (!(a->chars[0] & 1));
}

inline static int zodd(z_t a)
{
  return a->sign && (a->chars[0] & 1);
}

inline static int zeven_nonzero(z_t a)
{
  return !(a->chars[0] & 1);
}

inline static int zodd_nonzero(z_t a)
{
  return a->chars[0] & 1;
}

inline static int zzero(z_t a)
{
  return !a->sign;
}

inline static int zsignum(z_t a)
{
  return a->sign;
}

extern z_t libzahl_tmp_cmp;
extern z_t libzahl_tmp_str_num;
extern z_t libzahl_tmp_str_mag;
extern z_t libzahl_tmp_str_div;
extern z_t libzahl_tmp_str_rem;
extern z_t libzahl_tmp_gcd_u;
extern z_t libzahl_tmp_gcd_v;
extern z_t libzahl_tmp_sub;
extern z_t libzahl_tmp_modmul;
extern z_t libzahl_tmp_div;
extern z_t libzahl_tmp_mod;
extern z_t libzahl_tmp_pow_b;
extern z_t libzahl_tmp_pow_c;
extern z_t libzahl_tmp_pow_d;
extern z_t libzahl_tmp_modsqr;
extern z_t libzahl_tmp_divmod_a;
extern z_t libzahl_tmp_divmod_b;
extern z_t libzahl_tmp_divmod_d;
extern z_t libzahl_tmp_ptest_x;
extern z_t libzahl_tmp_ptest_a;
extern z_t libzahl_tmp_ptest_d;
extern z_t libzahl_tmp_ptest_n1;
extern z_t libzahl_tmp_ptest_n4;
extern z_t libzahl_const_1e19;
extern z_t libzahl_const_1e9;
extern z_t libzahl_const_1;
extern z_t libzahl_const_2;
extern z_t libzahl_const_4;
extern z_t libzahl_tmp_divmod_ds[32];
extern jmp_buf libzahl_jmp_buf;
extern int libzahl_set_up;
extern int libzahl_error;
extern zahl_char_t **libzahl_pool[(sizeof(size_t)) * 8];
extern size_t libzahl_pool_n[(sizeof(size_t)) * 8];
extern size_t libzahl_pool_alloc[(sizeof(size_t)) * 8];
void libzahl_realloc(z_t a, size_t need);
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

void zadd(z_t a, z_t b, z_t c)
{
  if (zzero(b))
  {
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
    if (b == c)
  {
    zlsh(a, b, 1);
  }
  else
    if ((zsignum(b) | zsignum(c)) < 0)
  {
    if (zsignum(b) < 0)
    {
      if (zsignum(c) < 0)
      {
        zadd_unsigned(a, b, c);
        a->sign = -zsignum(a);
      }
      else
      {
        zsub_unsigned(a, c, b);
      }
    }
    else
    {
      zsub_unsigned(a, b, c);
    }
  }
  else
  {
    zadd_unsigned(a, b, c);
  }
}


typedef uint32_t zahl_char_t;
typedef struct 
{
  int sign;
  size_t used;
  size_t alloced;
  zahl_char_t *chars;
} z_t[1];
enum zprimality
{
  NONPRIME = 0,
  PROBABLY_PRIME,
  PRIME
};
enum zranddev
{
  FAST_RANDOM = 0,
  SECURE_RANDOM
};
enum zranddist
{
  QUASIUNIFORM = 0,
  UNIFORM
};
enum zerror
{
  ZERROR_ERRNO_SET = 0
};
void zsetup(jmp_buf);
void zunsetup(void);
void zfree(z_t);
void zswap(z_t, z_t);
size_t zsave(z_t, void *);
size_t zload(z_t, const void *);
void zset(z_t, z_t);
void zseti(z_t, long long int);
void zsetu(z_t, unsigned long long int);
int zcmp(z_t, z_t);
int zcmpi(z_t, long long int);
int zcmpu(z_t, unsigned long long int);
int zcmpmag(z_t, z_t);
void zadd(z_t, z_t, z_t);
void zsub(z_t, z_t, z_t);
void zmul(z_t, z_t, z_t);
void zmodmul(z_t, z_t, z_t, z_t);
void zdiv(z_t, z_t, z_t);
void zdivmod(z_t, z_t, z_t, z_t);
void zmod(z_t, z_t, z_t);
void zsqr(z_t, z_t);
void zmodsqr(z_t, z_t, z_t);
void zneg(z_t, z_t);
void zabs(z_t, z_t);
void zpow(z_t, z_t, z_t);
void zmodpow(z_t, z_t, z_t, z_t);
void zpowu(z_t, z_t, unsigned long long int);
void zmodpowu(z_t, z_t, unsigned long long int, z_t);
void zadd_unsigned(z_t, z_t, z_t);
void zsub_unsigned(z_t, z_t, z_t);
void zand(z_t, z_t, z_t);
void zor(z_t, z_t, z_t);
void zxor(z_t, z_t, z_t);
void znot(z_t, z_t);
void zlsh(z_t, z_t, size_t);
void zrsh(z_t, z_t, size_t);
void ztrunc(z_t, z_t, size_t);
int zbtest(z_t, size_t);
void zsplit(z_t, z_t, z_t, size_t);
size_t zbits(z_t);
size_t zlsb(z_t);
void zbset(z_t, z_t, size_t, int);
void zgcd(z_t, z_t, z_t);
enum zprimality zptest(z_t, z_t, int);
void zrand(z_t, enum zranddev, enum zranddist, z_t);
char *zstr(z_t, char *);
int zsets(z_t, const char *);
size_t zstr_length(z_t, unsigned long long int);
enum zerror zerror(const char **);
void zperror(const char *);
inline static void zinit(z_t a)
{
  a->alloced = 0;
  a->chars = 0;
}

inline static int zeven(z_t a)
{
  return (!a->sign) || (!(a->chars[0] & 1));
}

inline static int zodd(z_t a)
{
  return a->sign && (a->chars[0] & 1);
}

inline static int zeven_nonzero(z_t a)
{
  return !(a->chars[0] & 1);
}

inline static int zodd_nonzero(z_t a)
{
  return a->chars[0] & 1;
}

inline static int zzero(z_t a)
{
  return !a->sign;
}

inline static int zsignum(z_t a)
{
  return a->sign;
}

extern z_t libzahl_tmp_cmp;
extern z_t libzahl_tmp_str_num;
extern z_t libzahl_tmp_str_mag;
extern z_t libzahl_tmp_str_div;
extern z_t libzahl_tmp_str_rem;
extern z_t libzahl_tmp_gcd_u;
extern z_t libzahl_tmp_gcd_v;
extern z_t libzahl_tmp_sub;
extern z_t libzahl_tmp_modmul;
extern z_t libzahl_tmp_div;
extern z_t libzahl_tmp_mod;
extern z_t libzahl_tmp_pow_b;
extern z_t libzahl_tmp_pow_c;
extern z_t libzahl_tmp_pow_d;
extern z_t libzahl_tmp_modsqr;
extern z_t libzahl_tmp_divmod_a;
extern z_t libzahl_tmp_divmod_b;
extern z_t libzahl_tmp_divmod_d;
extern z_t libzahl_tmp_ptest_x;
extern z_t libzahl_tmp_ptest_a;
extern z_t libzahl_tmp_ptest_d;
extern z_t libzahl_tmp_ptest_n1;
extern z_t libzahl_tmp_ptest_n4;
extern z_t libzahl_const_1e19;
extern z_t libzahl_const_1e9;
extern z_t libzahl_const_1;
extern z_t libzahl_const_2;
extern z_t libzahl_const_4;
extern z_t libzahl_tmp_divmod_ds[32];
extern jmp_buf libzahl_jmp_buf;
extern int libzahl_set_up;
extern int libzahl_error;
extern zahl_char_t **libzahl_pool[(sizeof(size_t)) * 8];
extern size_t libzahl_pool_n[(sizeof(size_t)) * 8];
extern size_t libzahl_pool_alloc[(sizeof(size_t)) * 8];
void libzahl_realloc(z_t a, size_t need);
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

void zadd(z_t a, z_t b, z_t c)
{
  if (zzero(b))
  {
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
    if (b == c)
  {
    zlsh(a, b, 1);
  }
  else
    if ((zsignum(b) | zsignum(c)) < 0)
  {
    if (zsignum(b) < 0)
    {
      if (zsignum(c) < 0)
      {
        zadd_unsigned(a, b, c);
        a->sign = -zsignum(a);
      }
      else
      {
        zsub_unsigned(a, c, b);
      }
    }
    else
    {
      zsub_unsigned(a, b, c);
    }
  }
  else
  {
    zadd_unsigned(a, b, c);
  }
}

