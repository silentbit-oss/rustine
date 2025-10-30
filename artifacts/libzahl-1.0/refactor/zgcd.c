#include <errno.h>
#include <internals.h>
#include <setjmp.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <zahl.h>
#include <zgcd.c>

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
void zgcd(z_t a, z_t b, z_t c)
{
  size_t shifts = 0;
  size_t i = 0;
  size_t min;
  zahl_char_t uv;
  zahl_char_t bit;
  int neg;
  if (!zcmp(b, c))
  {
    do
    {
      if (a != b)
      {
        zset(a, b);
      }
    }
    while (0);
    return;
  }
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
    return;
  }
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
    return;
  }
  zabs(libzahl_tmp_gcd_u, b);
  zabs(libzahl_tmp_gcd_v, c);
  neg = (zsignum(b) < 0) && (zsignum(c) < 0);
  min = (libzahl_tmp_gcd_u->used < libzahl_tmp_gcd_v->used) ? (libzahl_tmp_gcd_u->used) : (libzahl_tmp_gcd_v->used);
  for (; i < min; i += 1)
  {
    uv = libzahl_tmp_gcd_u->chars[i] | libzahl_tmp_gcd_v->chars[i];
    for (bit = 1; bit; bit <<= 1, shifts += 1)
    {
      if (uv & bit)
      {
        goto loop_done;
      }
    }

  }

  for (; i < libzahl_tmp_gcd_u->used; i += 1)
  {
    for (bit = 1; bit; bit <<= 1, shifts += 1)
    {
      if (libzahl_tmp_gcd_u->chars[i] & bit)
      {
        goto loop_done;
      }
    }

  }

  for (; i < libzahl_tmp_gcd_v->used; i += 1)
  {
    for (bit = 1; bit; bit <<= 1, shifts += 1)
    {
      if (libzahl_tmp_gcd_v->chars[i] & bit)
      {
        goto loop_done;
      }
    }

  }

  loop_done:
  zrsh(libzahl_tmp_gcd_u, libzahl_tmp_gcd_u, shifts);

  zrsh(libzahl_tmp_gcd_v, libzahl_tmp_gcd_v, shifts);
  zrsh(libzahl_tmp_gcd_u, libzahl_tmp_gcd_u, zlsb(libzahl_tmp_gcd_u));
  do
  {
    zrsh(libzahl_tmp_gcd_v, libzahl_tmp_gcd_v, zlsb(libzahl_tmp_gcd_v));
    if (zcmpmag(libzahl_tmp_gcd_u, libzahl_tmp_gcd_v) > 0)
    {
      zswap(libzahl_tmp_gcd_u, libzahl_tmp_gcd_v);
    }
    zsub_unsigned(libzahl_tmp_gcd_v, libzahl_tmp_gcd_v, libzahl_tmp_gcd_u);
  }
  while (!zzero(libzahl_tmp_gcd_v));
  zlsh(a, libzahl_tmp_gcd_u, shifts);
  a->sign = (neg) ? (-1) : (1);
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
void zgcd(z_t a, z_t b, z_t c)
{
  size_t shifts = 0;
  size_t i = 0;
  size_t min;
  zahl_char_t uv;
  zahl_char_t bit;
  int neg;
  if (!zcmp(b, c))
  {
    do
    {
      if (a != b)
      {
        zset(a, b);
      }
    }
    while (0);
    return;
  }
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
    return;
  }
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
    return;
  }
  zabs(libzahl_tmp_gcd_u, b);
  zabs(libzahl_tmp_gcd_v, c);
  neg = (zsignum(b) < 0) && (zsignum(c) < 0);
  min = (libzahl_tmp_gcd_u->used < libzahl_tmp_gcd_v->used) ? (libzahl_tmp_gcd_u->used) : (libzahl_tmp_gcd_v->used);
  for (; i < min; i += 1)
  {
    uv = libzahl_tmp_gcd_u->chars[i] | libzahl_tmp_gcd_v->chars[i];
    for (bit = 1; bit; bit <<= 1, shifts += 1)
    {
      if (uv & bit)
      {
        goto loop_done;
      }
    }

  }

  for (; i < libzahl_tmp_gcd_u->used; i += 1)
  {
    for (bit = 1; bit; bit <<= 1, shifts += 1)
    {
      if (libzahl_tmp_gcd_u->chars[i] & bit)
      {
        goto loop_done;
      }
    }

  }

  for (; i < libzahl_tmp_gcd_v->used; i += 1)
  {
    for (bit = 1; bit; bit <<= 1, shifts += 1)
    {
      if (libzahl_tmp_gcd_v->chars[i] & bit)
      {
        goto loop_done;
      }
    }

  }

  loop_done:
  zrsh(libzahl_tmp_gcd_u, libzahl_tmp_gcd_u, shifts);

  zrsh(libzahl_tmp_gcd_v, libzahl_tmp_gcd_v, shifts);
  zrsh(libzahl_tmp_gcd_u, libzahl_tmp_gcd_u, zlsb(libzahl_tmp_gcd_u));
  do
  {
    zrsh(libzahl_tmp_gcd_v, libzahl_tmp_gcd_v, zlsb(libzahl_tmp_gcd_v));
    if (zcmpmag(libzahl_tmp_gcd_u, libzahl_tmp_gcd_v) > 0)
    {
      zswap(libzahl_tmp_gcd_u, libzahl_tmp_gcd_v);
    }
    zsub_unsigned(libzahl_tmp_gcd_v, libzahl_tmp_gcd_v, libzahl_tmp_gcd_u);
  }
  while (!zzero(libzahl_tmp_gcd_v));
  zlsh(a, libzahl_tmp_gcd_u, shifts);
  a->sign = (neg) ? (-1) : (1);
}

