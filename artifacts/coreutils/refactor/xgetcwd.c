#include <assert.h>
#include <config.h>
#include <errno.h>
#include <idx.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <xalloc.h>
#include <xgetcwd.c>
#include <xgetcwd.h>

extern char *xgetcwd(void);
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
inline void *xnrealloc(void *p, size_t n, size_t s);
inline void *xnrealloc(void *p, size_t n, size_t s)
{
  return xreallocarray(p, n, s);
}

char *xcharalloc(size_t n);
char *xgetcwd(void)
{
  char *cwd = getcwd(0, 0);
  if ((!cwd) && (errno == ENOMEM))
  {
    xalloc_die();
  }
  return cwd;
}


extern char *xgetcwd(void);
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
inline void *xnrealloc(void *p, size_t n, size_t s);
inline void *xnrealloc(void *p, size_t n, size_t s)
{
  return xreallocarray(p, n, s);
}

char *xcharalloc(size_t n);
char *xgetcwd(void)
{
  char *cwd = getcwd(0, 0);
  if ((!cwd) && (errno == ENOMEM))
  {
    xalloc_die();
  }
  return cwd;
}

