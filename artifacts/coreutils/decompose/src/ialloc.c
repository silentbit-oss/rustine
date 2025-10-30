inline extern void *_gl_alloc_nomem(void)
{
  errno = ENOMEM;
  return 0;
}


/*** DEPENDENCIES:
***/


inline extern void *imalloc(idx_t s)
{
  return (s <= SIZE_MAX) ? (malloc(s)) : (_gl_alloc_nomem());
}


/*** DEPENDENCIES:
inline extern void *_gl_alloc_nomem(void)
{
  errno = ENOMEM;
  return 0;
}


----------------------------
typedef ptrdiff_t idx_t
----------------------------
***/


inline extern void *irealloc(void *p, idx_t s)
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


/*** DEPENDENCIES:
inline extern void *_gl_alloc_nomem(void)
{
  errno = ENOMEM;
  return 0;
}


----------------------------
typedef ptrdiff_t idx_t
----------------------------
***/


inline extern void *icalloc(idx_t n, idx_t s)
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


/*** DEPENDENCIES:
inline extern void *_gl_alloc_nomem(void)
{
  errno = ENOMEM;
  return 0;
}


----------------------------
typedef ptrdiff_t idx_t
----------------------------
***/


inline extern void *ireallocarray(void *p, idx_t n, idx_t s)
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


/*** DEPENDENCIES:
inline extern void *_gl_alloc_nomem(void)
{
  errno = ENOMEM;
  return 0;
}


----------------------------
typedef ptrdiff_t idx_t
----------------------------
***/


