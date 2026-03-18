#include <errno.h>
#include <fcntl.h>
#include <internals.h>
#include <setjmp.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <zahl.h>
#include <zrand.c>

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
static void zrand_get_random_bits(z_t r, size_t bits, int fd)
{
  size_t read_total = 0;
  size_t n;
  size_t chars = (bits + (32 - 1)) >> 5;
  ssize_t read_just;
  zahl_char_t mask = 1;
  char *buf;
  unsigned int buf_idx = 0;
  do
  {
    if (r->alloced < chars)
    {
      libzahl_realloc(r, chars);
    }
  }
  while (0);
  buf_idx = (char *) r->chars;
  for (n = chars * (sizeof(zahl_char_t)); n;)
  {
    read_just = read(fd, (&buf[buf_idx]) + read_total, n);
    if (read_just < 0)
    {
      libzahl_error = errno, longjmp(libzahl_jmp_buf, 1);
    }
    read_total += (size_t) read_just;
    n -= (size_t) read_just;
  }

  bits = bits & (32 - 1);
  mask <<= bits;
  mask -= 1;
  r->chars[chars - 1] &= mask;
  for (n = chars; n--;)
  {
    if (r->chars[n])
    {
      r->used = n + 1;
      r->sign = 1;
      return;
    }
  }

  r->sign = 0;
}

void zrand(z_t r, enum zranddev dev, enum zranddist dist, z_t n)
{
  const char *pathname = 0;
  unsigned int pathname_idx = 0;
  size_t bits;
  int fd;
  switch (dev)
  {
    case FAST_RANDOM:
    {
      pathname_idx = "/dev/urandom";
      break;
    }

    case SECURE_RANDOM:
    {
      pathname_idx = "/dev/random";
      break;
    }

    default:
    {
      abort();
    }

  }

  if (zzero(n))
  {
    r->sign = 0;
    return;
  }
  fd = open(pathname, O_RDONLY);
  if (fd < 0)
  {
    libzahl_error = errno, longjmp(libzahl_jmp_buf, 1);
  }
  switch (dist)
  {
    case QUASIUNIFORM:
    {
      if (zsignum(n) < 0)
      {
        libzahl_error = EDOM, longjmp(libzahl_jmp_buf, 1);
      }
      bits = zbits(n);
      zrand_get_random_bits(r, bits, fd);
      zadd(r, r, libzahl_const_1);
      zmul(r, r, n);
      zrsh(r, r, bits);
      break;
    }

    case UNIFORM:
    {
      if (zsignum(n) < 0)
      {
        libzahl_error = EDOM, longjmp(libzahl_jmp_buf, 1);
      }
      bits = zbits(n);
      do
      {
        zrand_get_random_bits(r, bits, fd);
      }
      while (zcmpmag(r, n) > 0);
      break;
    }

    default:
    {
      abort();
    }

  }

  close(fd);
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
static void zrand_get_random_bits(z_t r, size_t bits, int fd)
{
  size_t read_total = 0;
  size_t n;
  size_t chars = (bits + (32 - 1)) >> 5;
  ssize_t read_just;
  zahl_char_t mask = 1;
  char *buf;
  unsigned int buf_idx = 0;
  do
  {
    if (r->alloced < chars)
    {
      libzahl_realloc(r, chars);
    }
  }
  while (0);
  buf_idx = (char *) r->chars;
  for (n = chars * (sizeof(zahl_char_t)); n;)
  {
    read_just = read(fd, (&buf[buf_idx]) + read_total, n);
    if (read_just < 0)
    {
      libzahl_error = errno, longjmp(libzahl_jmp_buf, 1);
    }
    read_total += (size_t) read_just;
    n -= (size_t) read_just;
  }

  bits = bits & (32 - 1);
  mask <<= bits;
  mask -= 1;
  r->chars[chars - 1] &= mask;
  for (n = chars; n--;)
  {
    if (r->chars[n])
    {
      r->used = n + 1;
      r->sign = 1;
      return;
    }
  }

  r->sign = 0;
}

void zrand(z_t r, enum zranddev dev, enum zranddist dist, z_t n)
{
  const char *pathname = 0;
  unsigned int pathname_idx = 0;
  size_t bits;
  int fd;
  switch (dev)
  {
    case FAST_RANDOM:
      pathname_idx = "/dev/urandom";
      break;

    case SECURE_RANDOM:
      pathname_idx = "/dev/random";
      break;

    default:
      abort();

  }

  if (zzero(n))
  {
    r->sign = 0;
    return;
  }
  fd = open(pathname, O_RDONLY);
  if (fd < 0)
  {
    libzahl_error = errno, longjmp(libzahl_jmp_buf, 1);
  }
  switch (dist)
  {
    case QUASIUNIFORM:
      if (zsignum(n) < 0)
    {
      libzahl_error = EDOM, longjmp(libzahl_jmp_buf, 1);
    }
      bits = zbits(n);
      zrand_get_random_bits(r, bits, fd);
      zadd(r, r, libzahl_const_1);
      zmul(r, r, n);
      zrsh(r, r, bits);
      break;

    case UNIFORM:
      if (zsignum(n) < 0)
    {
      libzahl_error = EDOM, longjmp(libzahl_jmp_buf, 1);
    }
      bits = zbits(n);
      do
    {
      zrand_get_random_bits(r, bits, fd);
    }
    while (zcmpmag(r, n) > 0);
      break;

    default:
      abort();

  }

  close(fd);
}

