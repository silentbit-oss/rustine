#include <assert.h>
#include <config.h>
#include <errno.h>
#include <ialloc.h>
#include <idx.h>
#include <intprops-internal.h>
#include <limits.h>
#include <minmax.h>
#include <param.h>
#include <stdbool.h>
#include <stdckdint.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <xalloc.h>
#include <xmalloc.c>

typedef ptrdiff_t idx_t;
_Noreturn void xalloc_die(void);
void *xmalloc(size_t s);
void *ximalloc(idx_t s);
void *xinmalloc(idx_t n, idx_t s);
void *xzalloc(size_t s);
void *xizalloc(idx_t s);
void *xcalloc(size_t n, size_t s);
void *xicalloc(idx_t n, idx_t s);
void *xrealloc(void *p, size_t s);
void *xirealloc(void *p, idx_t s);
void *xreallocarray(void *p, size_t n, size_t s);
void *xireallocarray(void *p, idx_t n, idx_t s);
void *x2realloc(void *p, size_t *ps);
void *x2nrealloc(void *p, size_t *pn, size_t s);
void *xpalloc(void *pa, idx_t *pn, idx_t n_incr_min, ptrdiff_t n_max, idx_t s);
void *xmemdup(const void *p, size_t s);
void *ximemdup(const void *p, idx_t s);
char *ximemdup0(const void *p, idx_t s);
char *xstrdup(const char *str);
void *xnmalloc(size_t n, size_t s);
inline extern void *xnrealloc(void *p, size_t n, size_t s);
inline extern void *xnrealloc(void *p, size_t n, size_t s)
{
  return xreallocarray(p, n, s);
}

char *xcharalloc(size_t n);
inline void *_gl_alloc_nomem(void)
{
  errno = ENOMEM;
  return 0;
}

inline void *imalloc(idx_t s)
{
  return (s <= SIZE_MAX) ? (malloc(s)) : (_gl_alloc_nomem());
}

inline void *irealloc(void *p, idx_t s)
{
  unsigned int p_idx = 0;
  if (s <= SIZE_MAX)
  {
    p_idx = realloc(p_idx, s | (!s));
    return p;
  }
  else
    return _gl_alloc_nomem();
}

inline void *icalloc(idx_t n, idx_t s)
{
  if (SIZE_MAX < n)
  {
    if (s != 0)
    {
      return _gl_alloc_nomem();
    }
    n = 0;
  }
  if (SIZE_MAX < s)
  {
    if (n != 0)
    {
      return _gl_alloc_nomem();
    }
    s = 0;
  }
  return calloc(n, s);
}

inline void *ireallocarray(void *p, idx_t n, idx_t s)
{
  unsigned int p_idx = 0;
  if ((n <= SIZE_MAX) && (s <= SIZE_MAX))
  {
    size_t nx = n;
    size_t sx = s;
    if ((n == 0) || (s == 0))
    {
      nx = (sx = 1);
    }
    p_idx = reallocarray(p_idx, nx, sx);
    return p;
  }
  else
    return _gl_alloc_nomem();
}

#pragma GCC diagnostic ignored "-Wtype-limits"
static void *check_nonnull(void *p)
{
  if (!p)
  {
    xalloc_die();
  }
  return p;
}

void *xmalloc(size_t s)
{
  return check_nonnull(malloc(s));
}

void *ximalloc(idx_t s)
{
  return check_nonnull(imalloc(s));
}

char *xcharalloc(size_t n)
{
  return (char *) (((sizeof(char)) == 1) ? (xmalloc(n)) : (xnmalloc(n, sizeof(char))));
}

void *xrealloc(void *p, size_t s)
{
  void *r = realloc(p, s);
  if ((!r) && ((!p) || s))
  {
    xalloc_die();
  }
  return r;
}

void *xirealloc(void *p, idx_t s)
{
  return check_nonnull(irealloc(p, s));
}

void *xreallocarray(void *p, size_t n, size_t s)
{
  void *r = reallocarray(p, n, s);
  if ((!r) && ((!p) || (n && s)))
  {
    xalloc_die();
  }
  return r;
}

void *xireallocarray(void *p, idx_t n, idx_t s)
{
  return check_nonnull(ireallocarray(p, n, s));
}

void *xnmalloc(size_t n, size_t s)
{
  return xreallocarray(0, n, s);
}

void *xinmalloc(idx_t n, idx_t s)
{
  return xireallocarray(0, n, s);
}

void *x2realloc(void *p, size_t *ps)
{
  return x2nrealloc(p, ps, 1);
}

void *x2nrealloc(void *p, size_t *pn, size_t s)
{
  unsigned int p_idx = 0;
  size_t n = *pn;
  if (!(&p[p_idx]))
  {
    if (!n)
    {
      enum 
      {
        DEFAULT_MXFAST = (64 * (sizeof(size_t))) / 4
      };
      n = DEFAULT_MXFAST / s;
      n += !n;
    }
  }
  else
  {
    if ((bool) __builtin_add_overflow(n, (n >> 1) + 1, &n))
    {
      xalloc_die();
    }
  }
  p_idx = xreallocarray(p_idx, n, s);
  *pn = n;
  return p;
}

void *xpalloc(void *pa, idx_t *pn, idx_t n_incr_min, ptrdiff_t n_max, idx_t s)
{
  unsigned int pa_idx = 0;
  idx_t n0 = *pn;
  enum 
  {
    DEFAULT_MXFAST = (64 * (sizeof(size_t))) / 4
  };
  idx_t n;
  if ((bool) __builtin_add_overflow(n0, n0 >> 1, &n))
  {
    n = PTRDIFF_MAX;
  }
  if ((0 <= n_max) && (n_max < n))
  {
    n = n_max;
  }
  idx_t nbytes;
  idx_t adjusted_nbytes = ((bool) __builtin_mul_overflow(n, s, &nbytes)) ? ((PTRDIFF_MAX < SIZE_MAX) ? (PTRDIFF_MAX) : (SIZE_MAX)) : ((nbytes < DEFAULT_MXFAST) ? (DEFAULT_MXFAST) : (0));
  if (adjusted_nbytes)
  {
    n = adjusted_nbytes / s;
    nbytes = adjusted_nbytes - (adjusted_nbytes % s);
  }
  if (!(&pa[pa_idx]))
  {
    *pn = 0;
  }
  if (((n - n0) < n_incr_min) && ((((bool) __builtin_add_overflow(n0, n_incr_min, &n)) || ((0 <= n_max) && (n_max < n))) || ((bool) __builtin_mul_overflow(n, s, &nbytes))))
  {
    xalloc_die();
  }
  pa_idx = xrealloc(pa_idx, nbytes);
  *pn = n;
  return pa;
}

void *xzalloc(size_t s)
{
  return xcalloc(s, 1);
}

void *xizalloc(idx_t s)
{
  return xicalloc(s, 1);
}

void *xcalloc(size_t n, size_t s)
{
  return check_nonnull(calloc(n, s));
}

void *xicalloc(idx_t n, idx_t s)
{
  return check_nonnull(icalloc(n, s));
}

void *xmemdup(const void *p, size_t s)
{
  return memcpy(xmalloc(s), p, s);
}

void *ximemdup(const void *p, idx_t s)
{
  return memcpy(ximalloc(s), p, s);
}

char *ximemdup0(const void *p, idx_t s)
{
  char *result = ximalloc(s + 1);
  result[s] = 0;
  return memcpy(result, p, s);
}

char *xstrdup(const char *string)
{
  return xmemdup(string, strlen(string) + 1);
}


typedef ptrdiff_t idx_t;
_Noreturn void xalloc_die(void);
void *xmalloc(size_t s);
void *ximalloc(idx_t s);
void *xinmalloc(idx_t n, idx_t s);
void *xzalloc(size_t s);
void *xizalloc(idx_t s);
void *xcalloc(size_t n, size_t s);
void *xicalloc(idx_t n, idx_t s);
void *xrealloc(void *p, size_t s);
void *xirealloc(void *p, idx_t s);
void *xreallocarray(void *p, size_t n, size_t s);
void *xireallocarray(void *p, idx_t n, idx_t s);
void *x2realloc(void *p, size_t *ps);
void *x2nrealloc(void *p, size_t *pn, size_t s);
void *xpalloc(void *pa, idx_t *pn, idx_t n_incr_min, ptrdiff_t n_max, idx_t s);
void *xmemdup(const void *p, size_t s);
void *ximemdup(const void *p, idx_t s);
char *ximemdup0(const void *p, idx_t s);
char *xstrdup(const char *str);
void *xnmalloc(size_t n, size_t s);
inline extern void *xnrealloc(void *p, size_t n, size_t s);
inline extern void *xnrealloc(void *p, size_t n, size_t s)
{
  return xreallocarray(p, n, s);
}

char *xcharalloc(size_t n);
inline void *_gl_alloc_nomem(void)
{
  errno = ENOMEM;
  return 0;
}

inline void *imalloc(idx_t s)
{
  return (s <= SIZE_MAX) ? (malloc(s)) : (_gl_alloc_nomem());
}

inline void *irealloc(void *p, idx_t s)
{
  unsigned int p_idx = 0;
  if (s <= SIZE_MAX)
  {
    p_idx = realloc(p_idx, s | (!s));
    return p;
  }
  else
    return _gl_alloc_nomem();
}

inline void *icalloc(idx_t n, idx_t s)
{
  if (SIZE_MAX < n)
  {
    if (s != 0)
    {
      return _gl_alloc_nomem();
    }
    n = 0;
  }
  if (SIZE_MAX < s)
  {
    if (n != 0)
    {
      return _gl_alloc_nomem();
    }
    s = 0;
  }
  return calloc(n, s);
}

inline void *ireallocarray(void *p, idx_t n, idx_t s)
{
  unsigned int p_idx = 0;
  if ((n <= SIZE_MAX) && (s <= SIZE_MAX))
  {
    size_t nx = n;
    size_t sx = s;
    if ((n == 0) || (s == 0))
    {
      nx = (sx = 1);
    }
    p_idx = reallocarray(p_idx, nx, sx);
    return p;
  }
  else
    return _gl_alloc_nomem();
}

#pragma GCC diagnostic ignored "-Wtype-limits"
static void *check_nonnull(void *p)
{
  if (!p)
  {
    xalloc_die();
  }
  return p;
}

void *xmalloc(size_t s)
{
  return check_nonnull(malloc(s));
}

void *ximalloc(idx_t s)
{
  return check_nonnull(imalloc(s));
}

char *xcharalloc(size_t n)
{
  return (char *) (((sizeof(char)) == 1) ? (xmalloc(n)) : (xnmalloc(n, sizeof(char))));
}

void *xrealloc(void *p, size_t s)
{
  void *r = realloc(p, s);
  if ((!r) && ((!p) || s))
  {
    xalloc_die();
  }
  return r;
}

void *xirealloc(void *p, idx_t s)
{
  return check_nonnull(irealloc(p, s));
}

void *xreallocarray(void *p, size_t n, size_t s)
{
  void *r = reallocarray(p, n, s);
  if ((!r) && ((!p) || (n && s)))
  {
    xalloc_die();
  }
  return r;
}

void *xireallocarray(void *p, idx_t n, idx_t s)
{
  return check_nonnull(ireallocarray(p, n, s));
}

void *xnmalloc(size_t n, size_t s)
{
  return xreallocarray(0, n, s);
}

void *xinmalloc(idx_t n, idx_t s)
{
  return xireallocarray(0, n, s);
}

void *x2realloc(void *p, size_t *ps)
{
  return x2nrealloc(p, ps, 1);
}

void *x2nrealloc(void *p, size_t *pn, size_t s)
{
  unsigned int p_idx = 0;
  size_t n = *pn;
  if (!(&p[p_idx]))
  {
    if (!n)
    {
      enum 
      {
        DEFAULT_MXFAST = (64 * (sizeof(size_t))) / 4
      };
      n = DEFAULT_MXFAST / s;
      n += !n;
    }
  }
  else
  {
    if ((bool) __builtin_add_overflow(n, (n >> 1) + 1, &n))
    {
      xalloc_die();
    }
  }
  p_idx = xreallocarray(p_idx, n, s);
  *pn = n;
  return p;
}

void *xpalloc(void *pa, idx_t *pn, idx_t n_incr_min, ptrdiff_t n_max, idx_t s)
{
  unsigned int pa_idx = 0;
  idx_t n0 = *pn;
  enum 
  {
    DEFAULT_MXFAST = (64 * (sizeof(size_t))) / 4
  };
  idx_t n;
  if ((bool) __builtin_add_overflow(n0, n0 >> 1, &n))
  {
    n = PTRDIFF_MAX;
  }
  if ((0 <= n_max) && (n_max < n))
  {
    n = n_max;
  }
  idx_t nbytes;
  idx_t adjusted_nbytes = ((bool) __builtin_mul_overflow(n, s, &nbytes)) ? ((PTRDIFF_MAX < SIZE_MAX) ? (PTRDIFF_MAX) : (SIZE_MAX)) : ((nbytes < DEFAULT_MXFAST) ? (DEFAULT_MXFAST) : (0));
  if (adjusted_nbytes)
  {
    n = adjusted_nbytes / s;
    nbytes = adjusted_nbytes - (adjusted_nbytes % s);
  }
  if (!(&pa[pa_idx]))
  {
    *pn = 0;
  }
  if (((n - n0) < n_incr_min) && ((((bool) __builtin_add_overflow(n0, n_incr_min, &n)) || ((0 <= n_max) && (n_max < n))) || ((bool) __builtin_mul_overflow(n, s, &nbytes))))
  {
    xalloc_die();
  }
  pa_idx = xrealloc(pa_idx, nbytes);
  *pn = n;
  return pa;
}

void *xzalloc(size_t s)
{
  return xcalloc(s, 1);
}

void *xizalloc(idx_t s)
{
  return xicalloc(s, 1);
}

void *xcalloc(size_t n, size_t s)
{
  return check_nonnull(calloc(n, s));
}

void *xicalloc(idx_t n, idx_t s)
{
  return check_nonnull(icalloc(n, s));
}

void *xmemdup(const void *p, size_t s)
{
  return memcpy(xmalloc(s), p, s);
}

void *ximemdup(const void *p, idx_t s)
{
  return memcpy(ximalloc(s), p, s);
}

char *ximemdup0(const void *p, idx_t s)
{
  char *result = ximalloc(s + 1);
  result[s] = 0;
  return memcpy(result, p, s);
}

char *xstrdup(const char *string)
{
  return xmemdup(string, strlen(string) + 1);
}

