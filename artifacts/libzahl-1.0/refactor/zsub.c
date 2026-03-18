#include <errno.h>
#include <internals.h>
#include <setjmp.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <zahl.h>
#include <zsub.c>

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
    helper_zsub_unsigned_1(&a, &s_idx, &n, b, c, magcmp);
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
    {
      a->chars[i] = UINT32_MAX;
      i += 1;
    }

    a->chars[i] -= 1;
  }
  a->sign = magcmp;
}

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
    {
      a->chars[i] = UINT32_MAX;
      i += 1;
    }

    a->chars[i] -= 1;
  }
  a->sign = magcmp;
}

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

void helper_zsub_unsigned_1(z_t * const a_ref, unsigned int * const s_idx_ref, size_t * const n_ref, z_t b, z_t c, int magcmp)
{
  z_t a = *a_ref;
  unsigned int s_idx = *s_idx_ref;
  size_t n = *n_ref;
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
  *a_ref = a;
  *s_idx_ref = s_idx;
  *n_ref = n;
}

