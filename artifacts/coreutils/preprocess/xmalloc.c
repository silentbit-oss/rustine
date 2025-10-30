# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xmalloc.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xmalloc.c"
# 18 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xmalloc.c"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/./include/config.h" 1
# 4902 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/./include/config.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdbool.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdbool.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1



typedef int START_DELIMETER;
typedef unsigned chtype;
typedef chtype attr_t;
typedef int socklen_t;
typedef int size_t;
typedef struct __dirstream DIR;
typedef int __builtin_va_list;
typedef int __gnuc_va_list;
typedef int va_list;
typedef int __int8_t;
typedef int __uint8_t;
typedef int __int16_t;
typedef int __uint16_t;
typedef int __int_least16_t;
typedef int __uint_least16_t;
typedef int __int32_t;
typedef int __uint32_t;
typedef int __int64_t;
typedef int __uint64_t;
typedef int __int_least32_t;
typedef int __uint_least32_t;
typedef int __s8;
typedef int __u8;
typedef int __s16;
typedef int __u16;
typedef int __s32;
typedef int __u32;
typedef int __s64;
typedef int __u64;
typedef int _LOCK_T;
typedef int _LOCK_RECURSIVE_T;
typedef int _off_t;
typedef int __dev_t;
typedef int __uid_t;
typedef int __gid_t;
typedef int _off64_t;
typedef int _fpos_t;
typedef int _ssize_t;
typedef int wint_t;
typedef int _mbstate_t;
typedef int _flock_t;
typedef int _iconv_t;
typedef int __ULong;
typedef int __FILE;
typedef int ptrdiff_t;
typedef int wchar_t;
typedef int char16_t;
typedef int char32_t;
typedef int __off_t;
typedef int __pid_t;
typedef int __loff_t;
typedef int u_char;
typedef int u_short;
typedef int u_int;
typedef int u_long;
typedef int ushort;
typedef int uint;
typedef int clock_t;
typedef int time_t;
typedef int daddr_t;
typedef int caddr_t;
typedef int ino_t;
typedef int off_t;
typedef int dev_t;
typedef int uid_t;
typedef int gid_t;
typedef int pid_t;
typedef int key_t;
typedef int ssize_t;
typedef int mode_t;
typedef int nlink_t;
typedef int fd_mask;
typedef int _types_fd_set;
typedef int clockid_t;
typedef int timer_t;
typedef int useconds_t;
typedef int suseconds_t;
typedef int FILE;
typedef int fpos_t;
typedef int cookie_read_function_t;
typedef int cookie_write_function_t;
typedef int cookie_seek_function_t;
typedef int cookie_close_function_t;
typedef int cookie_io_functions_t;
typedef int div_t;
typedef int ldiv_t;
typedef int lldiv_t;
typedef int sigset_t;
typedef int __sigset_t;
typedef int _sig_func_ptr;
typedef int sig_atomic_t;
typedef int __tzrule_type;
typedef int __tzinfo_type;
typedef int mbstate_t;
typedef int sem_t;
typedef int pthread_t;
typedef int pthread_attr_t;
typedef int pthread_mutex_t;
typedef int pthread_mutexattr_t;
typedef int pthread_cond_t;
typedef int pthread_condattr_t;
typedef int pthread_key_t;
typedef int pthread_once_t;
typedef int pthread_rwlock_t;
typedef int pthread_rwlockattr_t;
typedef int pthread_spinlock_t;
typedef int pthread_barrier_t;
typedef int pthread_barrierattr_t;
typedef int jmp_buf;
typedef int rlim_t;
typedef int sa_family_t;
typedef int sigjmp_buf;
typedef int stack_t;
typedef int siginfo_t;
typedef int z_stream;


typedef int int8_t;
typedef int uint8_t;
typedef int int16_t;
typedef int uint16_t;
typedef int int32_t;
typedef int uint32_t;
typedef int int64_t;
typedef int uint64_t;


typedef int int_least8_t;
typedef int uint_least8_t;
typedef int int_least16_t;
typedef int uint_least16_t;
typedef int int_least32_t;
typedef int uint_least32_t;
typedef int int_least64_t;
typedef int uint_least64_t;


typedef int int_fast8_t;
typedef int uint_fast8_t;
typedef int int_fast16_t;
typedef int uint_fast16_t;
typedef int int_fast32_t;
typedef int uint_fast32_t;
typedef int int_fast64_t;
typedef int uint_fast64_t;


typedef int intptr_t;
typedef int uintptr_t;


typedef int intmax_t;
typedef int uintmax_t;


typedef _Bool bool;


typedef void* MirEGLNativeWindowType;
typedef void* MirEGLNativeDisplayType;
typedef struct MirConnection MirConnection;
typedef struct MirSurface MirSurface;
typedef struct MirSurfaceSpec MirSurfaceSpec;
typedef struct MirScreencast MirScreencast;
typedef struct MirPromptSession MirPromptSession;
typedef struct MirBufferStream MirBufferStream;
typedef struct MirPersistentId MirPersistentId;
typedef struct MirBlob MirBlob;
typedef struct MirDisplayConfig MirDisplayConfig;


typedef struct xcb_connection_t xcb_connection_t;
typedef uint32_t xcb_window_t;
typedef uint32_t xcb_visualid_t;


typedef _Atomic(_Bool) atomic_bool;
typedef _Atomic(char) atomic_char;
typedef _Atomic(signed char) atomic_schar;
typedef _Atomic(unsigned char) atomic_uchar;
typedef _Atomic(short) atomic_short;
typedef _Atomic(unsigned short) atomic_ushort;
typedef _Atomic(int) atomic_int;
typedef _Atomic(unsigned int) atomic_uint;
typedef _Atomic(long) atomic_long;
typedef _Atomic(unsigned long) atomic_ulong;
typedef _Atomic(long long) atomic_llong;
typedef _Atomic(unsigned long long) atomic_ullong;
typedef _Atomic(uint_least16_t) atomic_char16_t;
typedef _Atomic(uint_least32_t) atomic_char32_t;
typedef _Atomic(wchar_t) atomic_wchar_t;
typedef _Atomic(int_least8_t) atomic_int_least8_t;
typedef _Atomic(uint_least8_t) atomic_uint_least8_t;
typedef _Atomic(int_least16_t) atomic_int_least16_t;
typedef _Atomic(uint_least16_t) atomic_uint_least16_t;
typedef _Atomic(int_least32_t) atomic_int_least32_t;
typedef _Atomic(uint_least32_t) atomic_uint_least32_t;
typedef _Atomic(int_least64_t) atomic_int_least64_t;
typedef _Atomic(uint_least64_t) atomic_uint_least64_t;
typedef _Atomic(int_fast8_t) atomic_int_fast8_t;
typedef _Atomic(uint_fast8_t) atomic_uint_fast8_t;
typedef _Atomic(int_fast16_t) atomic_int_fast16_t;
typedef _Atomic(uint_fast16_t) atomic_uint_fast16_t;
typedef _Atomic(int_fast32_t) atomic_int_fast32_t;
typedef _Atomic(uint_fast32_t) atomic_uint_fast32_t;
typedef _Atomic(int_fast64_t) atomic_int_fast64_t;
typedef _Atomic(uint_fast64_t) atomic_uint_fast64_t;
typedef _Atomic(intptr_t) atomic_intptr_t;
typedef _Atomic(uintptr_t) atomic_uintptr_t;
typedef _Atomic(size_t) atomic_size_t;
typedef _Atomic(ptrdiff_t) atomic_ptrdiff_t;
typedef _Atomic(intmax_t) atomic_intmax_t;
typedef _Atomic(uintmax_t) atomic_uintmax_t;
typedef struct atomic_flag { atomic_bool _Value; } atomic_flag;
typedef enum memory_order {
  memory_order_relaxed,
  memory_order_consume,
  memory_order_acquire,
  memory_order_release,
  memory_order_acq_rel,
  memory_order_seq_cst
} memory_order;

typedef struct __locale_struct *__locale_t;
typedef __locale_t locale_t;
typedef int END_DELIMETER;
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdbool.h" 2
# 4903 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/./include/config.h" 2
# 4936 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/./include/config.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 1
# 4937 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/./include/config.h" 2
# 19 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xmalloc.c" 2



# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xalloc.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xalloc.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xalloc.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xalloc.h" 2


# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/idx.h" 1
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/idx.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/idx.h" 2


# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/idx.h" 2
# 130 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/idx.h"
typedef ptrdiff_t idx_t;
# 33 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xalloc.h" 2



# 53 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xalloc.h"
_Noreturn void xalloc_die (void);





void *xmalloc (size_t s)
 
  ;
void *ximalloc (idx_t s)
 
  ;
void *xinmalloc (idx_t n, idx_t s)
 
  ;
void *xzalloc (size_t s)
 
  ;
void *xizalloc (idx_t s)
 
  ;
void *xcalloc (size_t n, size_t s)
 
  ;
void *xicalloc (idx_t n, idx_t s)
 
  ;
void *xrealloc (void *p, size_t s)
  ;
void *xirealloc (void *p, idx_t s)
  ;
void *xreallocarray (void *p, size_t n, size_t s)
  ;
void *xireallocarray (void *p, idx_t n, idx_t s)
  ;
void *x2realloc (void *p, size_t *ps)
  ;
void *x2nrealloc (void *p, size_t *pn, size_t s)
  ;
void *xpalloc (void *pa, idx_t *pn, idx_t n_incr_min, ptrdiff_t n_max, idx_t s)
  ;
void *xmemdup (void const *p, size_t s)
 
  ;
void *ximemdup (void const *p, idx_t s)
 
  ;
char *ximemdup0 (void const *p, idx_t s)
 
  ;
char *xstrdup (char const *str)
 
  ;
# 136 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xalloc.h"
void *xnmalloc (size_t n, size_t s)
 
  ;





extern inline void *xnrealloc (void *p, size_t n, size_t s)
  ;
extern inline void *
xnrealloc (void *p, size_t n, size_t s)
{
  return xreallocarray (p, n, s);
}




char *xcharalloc (size_t n)
 
  ;
# 213 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xalloc.h"

# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xmalloc.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/ialloc.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/ialloc.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/errno.h" 1
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/ialloc.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 31 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/ialloc.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 32 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/ialloc.h" 2





# 45 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/ialloc.h"
inline void *
_gl_alloc_nomem (void)
{
  errno = ENOMEM;
  return 0;
}




inline

void *
imalloc (idx_t s)
{
  return s <= SIZE_MAX ? malloc (s) : _gl_alloc_nomem ();
}




inline

void *
irealloc (void *p, idx_t s)
{
  if (s <= SIZE_MAX)
    {


      p = realloc (p, s | !s);




      return p;
    }
  else
    return _gl_alloc_nomem ();
}




inline

void *
icalloc (idx_t n, idx_t s)
{
  if (SIZE_MAX < n)
    {
      if (s != 0)
        return _gl_alloc_nomem ();
      n = 0;
    }
  if (SIZE_MAX < s)
    {
      if (n != 0)
        return _gl_alloc_nomem ();
      s = 0;
    }
  return calloc (n, s);
}




inline void *
ireallocarray (void *p, idx_t n, idx_t s)
{
  if (n <= SIZE_MAX && s <= SIZE_MAX)
    {


      size_t nx = n;
      size_t sx = s;
      if (n == 0 || s == 0)
        nx = sx = 1;
      p = reallocarray (p, nx, sx);




      return p;
    }
  else
    return _gl_alloc_nomem ();
}






# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xmalloc.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/minmax.h" 1
# 39 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/minmax.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/param.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/param.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/param.h" 2
# 40 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/minmax.h" 2
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xmalloc.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/stdckdint.h" 1
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/stdckdint.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/intprops-internal.h" 1
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/intprops-internal.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 1
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/intprops-internal.h" 2



 
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/intprops-internal.h"
#pragma GCC diagnostic ignored "-Wtype-limits"
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/stdckdint.h" 2
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xmalloc.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xmalloc.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xmalloc.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 31 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xmalloc.c" 2

static void *
check_nonnull (void *p)
{
  if (!p)
    xalloc_die ();
  return p;
}



void *
xmalloc (size_t s)
{
  return check_nonnull (malloc (s));
}

void *
ximalloc (idx_t s)
{
  return check_nonnull (imalloc (s));
}

char *
xcharalloc (size_t n)
{
  return ((char *) (sizeof (char) == 1 ? xmalloc (n) : xnmalloc (n, sizeof (char))));
}




void *
xrealloc (void *p, size_t s)
{
  void *r = realloc (p, s);
  if (!r && (!p || s))
    xalloc_die ();
  return r;
}

void *
xirealloc (void *p, idx_t s)
{
  return check_nonnull (irealloc (p, s));
}




void *
xreallocarray (void *p, size_t n, size_t s)
{
  void *r = reallocarray (p, n, s);
  if (!r && (!p || (n && s)))
    xalloc_die ();
  return r;
}

void *
xireallocarray (void *p, idx_t n, idx_t s)
{
  return check_nonnull (ireallocarray (p, n, s));
}




void *
xnmalloc (size_t n, size_t s)
{
  return xreallocarray (0, n, s);
}

void *
xinmalloc (idx_t n, idx_t s)
{
  return xireallocarray (0, n, s);
}







void *
x2realloc (void *p, size_t *ps)
{
  return x2nrealloc (p, ps, 1);
}
# 177 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xmalloc.c"
void *
x2nrealloc (void *p, size_t *pn, size_t s)
{
  size_t n = *pn;

  if (! p)
    {
      if (! n)
        {




          enum { DEFAULT_MXFAST = 64 * sizeof (size_t) / 4 };

          n = DEFAULT_MXFAST / s;
          n += !n;
        }
    }
  else
    {

      if (((bool) __builtin_add_overflow (n, (n >> 1) + 1, &n)))
        xalloc_die ();
    }

  p = xreallocarray (p, n, s);
  *pn = n;
  return p;
}
# 224 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xmalloc.c"
void *
xpalloc (void *pa, idx_t *pn, idx_t n_incr_min, ptrdiff_t n_max, idx_t s)
{
  idx_t n0 = *pn;




  enum { DEFAULT_MXFAST = 64 * sizeof (size_t) / 4 };






  idx_t n;
  if (((bool) __builtin_add_overflow (n0, n0 >> 1, &n)))
    n = PTRDIFF_MAX;
  if (0 <= n_max && n_max < n)
    n = n_max;






  idx_t nbytes;



  idx_t adjusted_nbytes
    = (((bool) __builtin_mul_overflow (n, s, &nbytes))
       ? ((PTRDIFF_MAX) < (SIZE_MAX) ? (PTRDIFF_MAX) : (SIZE_MAX))
       : nbytes < DEFAULT_MXFAST ? DEFAULT_MXFAST : 0);
  if (adjusted_nbytes)
    {
      n = adjusted_nbytes / s;
      nbytes = adjusted_nbytes - adjusted_nbytes % s;
    }

  if (! pa)
    *pn = 0;
  if (n - n0 < n_incr_min
      && (((bool) __builtin_add_overflow (n0, n_incr_min, &n))
          || (0 <= n_max && n_max < n)
          || ((bool) __builtin_mul_overflow (n, s, &nbytes))))
    xalloc_die ();
  pa = xrealloc (pa, nbytes);
  *pn = n;
  return pa;
}





void *
xzalloc (size_t s)
{
  return xcalloc (s, 1);
}

void *
xizalloc (idx_t s)
{
  return xicalloc (s, 1);
}




void *
xcalloc (size_t n, size_t s)
{
  return check_nonnull (calloc (n, s));
}

void *
xicalloc (idx_t n, idx_t s)
{
  return check_nonnull (icalloc (n, s));
}





void *
xmemdup (void const *p, size_t s)
{
  return memcpy (xmalloc (s), p, s);
}

void *
ximemdup (void const *p, idx_t s)
{
  return memcpy (ximalloc (s), p, s);
}




char *
ximemdup0 (void const *p, idx_t s)
{
  char *result = ximalloc (s + 1);
  result[s] = 0;
  return memcpy (result, p, s);
}



char *
xstrdup (char const *string)
{
  return xmemdup (string, strlen (string) + 1);
}
# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xmalloc.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xmalloc.c"
# 18 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xmalloc.c"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/./include/config.h" 1
# 4902 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/./include/config.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdbool.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdbool.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1



typedef int START_DELIMETER;
typedef unsigned chtype;
typedef chtype attr_t;
typedef int socklen_t;
typedef int size_t;
typedef struct __dirstream DIR;
typedef int __builtin_va_list;
typedef int __gnuc_va_list;
typedef int va_list;
typedef int __int8_t;
typedef int __uint8_t;
typedef int __int16_t;
typedef int __uint16_t;
typedef int __int_least16_t;
typedef int __uint_least16_t;
typedef int __int32_t;
typedef int __uint32_t;
typedef int __int64_t;
typedef int __uint64_t;
typedef int __int_least32_t;
typedef int __uint_least32_t;
typedef int __s8;
typedef int __u8;
typedef int __s16;
typedef int __u16;
typedef int __s32;
typedef int __u32;
typedef int __s64;
typedef int __u64;
typedef int _LOCK_T;
typedef int _LOCK_RECURSIVE_T;
typedef int _off_t;
typedef int __dev_t;
typedef int __uid_t;
typedef int __gid_t;
typedef int _off64_t;
typedef int _fpos_t;
typedef int _ssize_t;
typedef int wint_t;
typedef int _mbstate_t;
typedef int _flock_t;
typedef int _iconv_t;
typedef int __ULong;
typedef int __FILE;
typedef int ptrdiff_t;
typedef int wchar_t;
typedef int char16_t;
typedef int char32_t;
typedef int __off_t;
typedef int __pid_t;
typedef int __loff_t;
typedef int u_char;
typedef int u_short;
typedef int u_int;
typedef int u_long;
typedef int ushort;
typedef int uint;
typedef int clock_t;
typedef int time_t;
typedef int daddr_t;
typedef int caddr_t;
typedef int ino_t;
typedef int off_t;
typedef int dev_t;
typedef int uid_t;
typedef int gid_t;
typedef int pid_t;
typedef int key_t;
typedef int ssize_t;
typedef int mode_t;
typedef int nlink_t;
typedef int fd_mask;
typedef int _types_fd_set;
typedef int clockid_t;
typedef int timer_t;
typedef int useconds_t;
typedef int suseconds_t;
typedef int FILE;
typedef int fpos_t;
typedef int cookie_read_function_t;
typedef int cookie_write_function_t;
typedef int cookie_seek_function_t;
typedef int cookie_close_function_t;
typedef int cookie_io_functions_t;
typedef int div_t;
typedef int ldiv_t;
typedef int lldiv_t;
typedef int sigset_t;
typedef int __sigset_t;
typedef int _sig_func_ptr;
typedef int sig_atomic_t;
typedef int __tzrule_type;
typedef int __tzinfo_type;
typedef int mbstate_t;
typedef int sem_t;
typedef int pthread_t;
typedef int pthread_attr_t;
typedef int pthread_mutex_t;
typedef int pthread_mutexattr_t;
typedef int pthread_cond_t;
typedef int pthread_condattr_t;
typedef int pthread_key_t;
typedef int pthread_once_t;
typedef int pthread_rwlock_t;
typedef int pthread_rwlockattr_t;
typedef int pthread_spinlock_t;
typedef int pthread_barrier_t;
typedef int pthread_barrierattr_t;
typedef int jmp_buf;
typedef int rlim_t;
typedef int sa_family_t;
typedef int sigjmp_buf;
typedef int stack_t;
typedef int siginfo_t;
typedef int z_stream;


typedef int int8_t;
typedef int uint8_t;
typedef int int16_t;
typedef int uint16_t;
typedef int int32_t;
typedef int uint32_t;
typedef int int64_t;
typedef int uint64_t;


typedef int int_least8_t;
typedef int uint_least8_t;
typedef int int_least16_t;
typedef int uint_least16_t;
typedef int int_least32_t;
typedef int uint_least32_t;
typedef int int_least64_t;
typedef int uint_least64_t;


typedef int int_fast8_t;
typedef int uint_fast8_t;
typedef int int_fast16_t;
typedef int uint_fast16_t;
typedef int int_fast32_t;
typedef int uint_fast32_t;
typedef int int_fast64_t;
typedef int uint_fast64_t;


typedef int intptr_t;
typedef int uintptr_t;


typedef int intmax_t;
typedef int uintmax_t;


typedef _Bool bool;


typedef void* MirEGLNativeWindowType;
typedef void* MirEGLNativeDisplayType;
typedef struct MirConnection MirConnection;
typedef struct MirSurface MirSurface;
typedef struct MirSurfaceSpec MirSurfaceSpec;
typedef struct MirScreencast MirScreencast;
typedef struct MirPromptSession MirPromptSession;
typedef struct MirBufferStream MirBufferStream;
typedef struct MirPersistentId MirPersistentId;
typedef struct MirBlob MirBlob;
typedef struct MirDisplayConfig MirDisplayConfig;


typedef struct xcb_connection_t xcb_connection_t;
typedef uint32_t xcb_window_t;
typedef uint32_t xcb_visualid_t;


typedef _Atomic(_Bool) atomic_bool;
typedef _Atomic(char) atomic_char;
typedef _Atomic(signed char) atomic_schar;
typedef _Atomic(unsigned char) atomic_uchar;
typedef _Atomic(short) atomic_short;
typedef _Atomic(unsigned short) atomic_ushort;
typedef _Atomic(int) atomic_int;
typedef _Atomic(unsigned int) atomic_uint;
typedef _Atomic(long) atomic_long;
typedef _Atomic(unsigned long) atomic_ulong;
typedef _Atomic(long long) atomic_llong;
typedef _Atomic(unsigned long long) atomic_ullong;
typedef _Atomic(uint_least16_t) atomic_char16_t;
typedef _Atomic(uint_least32_t) atomic_char32_t;
typedef _Atomic(wchar_t) atomic_wchar_t;
typedef _Atomic(int_least8_t) atomic_int_least8_t;
typedef _Atomic(uint_least8_t) atomic_uint_least8_t;
typedef _Atomic(int_least16_t) atomic_int_least16_t;
typedef _Atomic(uint_least16_t) atomic_uint_least16_t;
typedef _Atomic(int_least32_t) atomic_int_least32_t;
typedef _Atomic(uint_least32_t) atomic_uint_least32_t;
typedef _Atomic(int_least64_t) atomic_int_least64_t;
typedef _Atomic(uint_least64_t) atomic_uint_least64_t;
typedef _Atomic(int_fast8_t) atomic_int_fast8_t;
typedef _Atomic(uint_fast8_t) atomic_uint_fast8_t;
typedef _Atomic(int_fast16_t) atomic_int_fast16_t;
typedef _Atomic(uint_fast16_t) atomic_uint_fast16_t;
typedef _Atomic(int_fast32_t) atomic_int_fast32_t;
typedef _Atomic(uint_fast32_t) atomic_uint_fast32_t;
typedef _Atomic(int_fast64_t) atomic_int_fast64_t;
typedef _Atomic(uint_fast64_t) atomic_uint_fast64_t;
typedef _Atomic(intptr_t) atomic_intptr_t;
typedef _Atomic(uintptr_t) atomic_uintptr_t;
typedef _Atomic(size_t) atomic_size_t;
typedef _Atomic(ptrdiff_t) atomic_ptrdiff_t;
typedef _Atomic(intmax_t) atomic_intmax_t;
typedef _Atomic(uintmax_t) atomic_uintmax_t;
typedef struct atomic_flag { atomic_bool _Value; } atomic_flag;
typedef enum memory_order {
  memory_order_relaxed,
  memory_order_consume,
  memory_order_acquire,
  memory_order_release,
  memory_order_acq_rel,
  memory_order_seq_cst
} memory_order;

typedef struct __locale_struct *__locale_t;
typedef __locale_t locale_t;
typedef int END_DELIMETER;
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdbool.h" 2
# 4903 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/./include/config.h" 2
# 4936 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/./include/config.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/assert.h" 1
# 4937 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/./include/config.h" 2
# 19 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xmalloc.c" 2



# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xalloc.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xalloc.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xalloc.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xalloc.h" 2


# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/idx.h" 1
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/idx.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/idx.h" 2


# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/idx.h" 2
# 130 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/idx.h"
typedef ptrdiff_t idx_t;
# 33 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xalloc.h" 2



# 53 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xalloc.h"
_Noreturn void xalloc_die (void);





void *xmalloc (size_t s)
 
  ;
void *ximalloc (idx_t s)
 
  ;
void *xinmalloc (idx_t n, idx_t s)
 
  ;
void *xzalloc (size_t s)
 
  ;
void *xizalloc (idx_t s)
 
  ;
void *xcalloc (size_t n, size_t s)
 
  ;
void *xicalloc (idx_t n, idx_t s)
 
  ;
void *xrealloc (void *p, size_t s)
  ;
void *xirealloc (void *p, idx_t s)
  ;
void *xreallocarray (void *p, size_t n, size_t s)
  ;
void *xireallocarray (void *p, idx_t n, idx_t s)
  ;
void *x2realloc (void *p, size_t *ps)
  ;
void *x2nrealloc (void *p, size_t *pn, size_t s)
  ;
void *xpalloc (void *pa, idx_t *pn, idx_t n_incr_min, ptrdiff_t n_max, idx_t s)
  ;
void *xmemdup (void const *p, size_t s)
 
  ;
void *ximemdup (void const *p, idx_t s)
 
  ;
char *ximemdup0 (void const *p, idx_t s)
 
  ;
char *xstrdup (char const *str)
 
  ;
# 136 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xalloc.h"
void *xnmalloc (size_t n, size_t s)
 
  ;





extern inline void *xnrealloc (void *p, size_t n, size_t s)
  ;
extern inline void *
xnrealloc (void *p, size_t n, size_t s)
{
  return xreallocarray (p, n, s);
}




char *xcharalloc (size_t n)
 
  ;
# 213 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xalloc.h"

# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xmalloc.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/ialloc.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/ialloc.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/errno.h" 1
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/ialloc.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 31 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/ialloc.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 32 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/ialloc.h" 2





# 45 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/ialloc.h"
inline void *
_gl_alloc_nomem (void)
{
  errno = ENOMEM;
  return 0;
}




inline

void *
imalloc (idx_t s)
{
  return s <= SIZE_MAX ? malloc (s) : _gl_alloc_nomem ();
}




inline

void *
irealloc (void *p, idx_t s)
{
  if (s <= SIZE_MAX)
    {


      p = realloc (p, s | !s);




      return p;
    }
  else
    return _gl_alloc_nomem ();
}




inline

void *
icalloc (idx_t n, idx_t s)
{
  if (SIZE_MAX < n)
    {
      if (s != 0)
        return _gl_alloc_nomem ();
      n = 0;
    }
  if (SIZE_MAX < s)
    {
      if (n != 0)
        return _gl_alloc_nomem ();
      s = 0;
    }
  return calloc (n, s);
}




inline void *
ireallocarray (void *p, idx_t n, idx_t s)
{
  if (n <= SIZE_MAX && s <= SIZE_MAX)
    {


      size_t nx = n;
      size_t sx = s;
      if (n == 0 || s == 0)
        nx = sx = 1;
      p = reallocarray (p, nx, sx);




      return p;
    }
  else
    return _gl_alloc_nomem ();
}






# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xmalloc.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/minmax.h" 1
# 39 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/minmax.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/param.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/param.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/param.h" 2
# 40 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/minmax.h" 2
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xmalloc.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/stdckdint.h" 1
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/stdckdint.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/intprops-internal.h" 1
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/intprops-internal.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 1
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/intprops-internal.h" 2



 
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/intprops-internal.h"
#pragma GCC diagnostic ignored "-Wtype-limits"
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/stdckdint.h" 2
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xmalloc.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xmalloc.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xmalloc.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 31 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xmalloc.c" 2

static void *
check_nonnull (void *p)
{
  if (!p)
    xalloc_die ();
  return p;
}



void *
xmalloc (size_t s)
{
  return check_nonnull (malloc (s));
}

void *
ximalloc (idx_t s)
{
  return check_nonnull (imalloc (s));
}

char *
xcharalloc (size_t n)
{
  return ((char *) (sizeof (char) == 1 ? xmalloc (n) : xnmalloc (n, sizeof (char))));
}




void *
xrealloc (void *p, size_t s)
{
  void *r = realloc (p, s);
  if (!r && (!p || s))
    xalloc_die ();
  return r;
}

void *
xirealloc (void *p, idx_t s)
{
  return check_nonnull (irealloc (p, s));
}




void *
xreallocarray (void *p, size_t n, size_t s)
{
  void *r = reallocarray (p, n, s);
  if (!r && (!p || (n && s)))
    xalloc_die ();
  return r;
}

void *
xireallocarray (void *p, idx_t n, idx_t s)
{
  return check_nonnull (ireallocarray (p, n, s));
}




void *
xnmalloc (size_t n, size_t s)
{
  return xreallocarray (0, n, s);
}

void *
xinmalloc (idx_t n, idx_t s)
{
  return xireallocarray (0, n, s);
}







void *
x2realloc (void *p, size_t *ps)
{
  return x2nrealloc (p, ps, 1);
}
# 177 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xmalloc.c"
void *
x2nrealloc (void *p, size_t *pn, size_t s)
{
  size_t n = *pn;

  if (! p)
    {
      if (! n)
        {




          enum { DEFAULT_MXFAST = 64 * sizeof (size_t) / 4 };

          n = DEFAULT_MXFAST / s;
          n += !n;
        }
    }
  else
    {

      if (((bool) __builtin_add_overflow (n, (n >> 1) + 1, &n)))
        xalloc_die ();
    }

  p = xreallocarray (p, n, s);
  *pn = n;
  return p;
}
# 224 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xmalloc.c"
void *
xpalloc (void *pa, idx_t *pn, idx_t n_incr_min, ptrdiff_t n_max, idx_t s)
{
  idx_t n0 = *pn;




  enum { DEFAULT_MXFAST = 64 * sizeof (size_t) / 4 };






  idx_t n;
  if (((bool) __builtin_add_overflow (n0, n0 >> 1, &n)))
    n = PTRDIFF_MAX;
  if (0 <= n_max && n_max < n)
    n = n_max;






  idx_t nbytes;



  idx_t adjusted_nbytes
    = (((bool) __builtin_mul_overflow (n, s, &nbytes))
       ? ((PTRDIFF_MAX) < (SIZE_MAX) ? (PTRDIFF_MAX) : (SIZE_MAX))
       : nbytes < DEFAULT_MXFAST ? DEFAULT_MXFAST : 0);
  if (adjusted_nbytes)
    {
      n = adjusted_nbytes / s;
      nbytes = adjusted_nbytes - adjusted_nbytes % s;
    }

  if (! pa)
    *pn = 0;
  if (n - n0 < n_incr_min
      && (((bool) __builtin_add_overflow (n0, n_incr_min, &n))
          || (0 <= n_max && n_max < n)
          || ((bool) __builtin_mul_overflow (n, s, &nbytes))))
    xalloc_die ();
  pa = xrealloc (pa, nbytes);
  *pn = n;
  return pa;
}





void *
xzalloc (size_t s)
{
  return xcalloc (s, 1);
}

void *
xizalloc (idx_t s)
{
  return xicalloc (s, 1);
}




void *
xcalloc (size_t n, size_t s)
{
  return check_nonnull (calloc (n, s));
}

void *
xicalloc (idx_t n, idx_t s)
{
  return check_nonnull (icalloc (n, s));
}





void *
xmemdup (void const *p, size_t s)
{
  return memcpy (xmalloc (s), p, s);
}

void *
ximemdup (void const *p, idx_t s)
{
  return memcpy (ximalloc (s), p, s);
}




char *
ximemdup0 (void const *p, idx_t s)
{
  char *result = ximalloc (s + 1);
  result[s] = 0;
  return memcpy (result, p, s);
}



char *
xstrdup (char const *string)
{
  return xmemdup (string, strlen (string) + 1);
}
