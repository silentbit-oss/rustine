# 0 "/app/subjects/libcsv/libcsv.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/app/subjects/libcsv/libcsv.c"
# 20 "/app/subjects/libcsv/libcsv.c"
# 1 "/app/pipeline/preprocess/fake_libc_include/assert.h" 1
# 1 "/app/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/app/pipeline/preprocess/fake_libc_include/assert.h" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1



typedef int START_DELIMETER;
typedef int socklen_t;
typedef int size_t;
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
# 3 "/app/pipeline/preprocess/fake_libc_include/assert.h" 2
# 21 "/app/subjects/libcsv/libcsv.c" 2


# 1 "/app/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 24 "/app/subjects/libcsv/libcsv.c" 2




# 1 "/app/subjects/libcsv/csv.h" 1
# 22 "/app/subjects/libcsv/csv.h"
# 1 "/app/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 23 "/app/subjects/libcsv/csv.h" 2
# 1 "/app/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 24 "/app/subjects/libcsv/csv.h" 2
# 60 "/app/subjects/libcsv/csv.h"
struct csv_parser {
  int pstate;
  int quoted;
  size_t spaces;
  unsigned char * entry_buf;
  size_t entry_pos;
  size_t entry_size;
  int status;
  unsigned char options;
  unsigned char quote_char;
  unsigned char delim_char;
  int (*is_space)(unsigned char);
  int (*is_term)(unsigned char);
  size_t blk_size;
  void *(*malloc_func)(size_t);
  void *(*realloc_func)(void *, size_t);
  void (*free_func)(void *);
};


int csv_init(struct csv_parser *p, unsigned char options);
int csv_fini(struct csv_parser *p, void (*cb1)(void *, size_t, void *), void (*cb2)(int, void *), void *data);
void csv_free(struct csv_parser *p);
int csv_error(const struct csv_parser *p);
const char * csv_strerror(int error);
size_t csv_parse(struct csv_parser *p, const void *s, size_t len, void (*cb1)(void *, size_t, void *), void (*cb2)(int, void *), void *data);
size_t csv_write(void *dest, size_t dest_size, const void *src, size_t src_size);
int csv_fwrite(FILE *fp, const void *src, size_t src_size);
size_t csv_write2(void *dest, size_t dest_size, const void *src, size_t src_size, unsigned char quote);
int csv_fwrite2(FILE *fp, const void *src, size_t src_size, unsigned char quote);
int csv_get_opts(const struct csv_parser *p);
int csv_set_opts(struct csv_parser *p, unsigned char options);
void csv_set_delim(struct csv_parser *p, unsigned char c);
void csv_set_quote(struct csv_parser *p, unsigned char c);
unsigned char csv_get_delim(const struct csv_parser *p);
unsigned char csv_get_quote(const struct csv_parser *p);
void csv_set_space_func(struct csv_parser *p, int (*f)(unsigned char));
void csv_set_term_func(struct csv_parser *p, int (*f)(unsigned char));
void csv_set_realloc_func(struct csv_parser *p, void *(*)(void *, size_t));
void csv_set_free_func(struct csv_parser *p, void (*)(void *));
void csv_set_blk_size(struct csv_parser *p, size_t);
size_t csv_get_buffer_size(const struct csv_parser *p);
# 29 "/app/subjects/libcsv/libcsv.c" 2
# 73 "/app/subjects/libcsv/libcsv.c"
static const char *csv_errors[] = {"success",
                             "error parsing data while strict checking enabled",
                             "memory exhausted while increasing buffer size",
                             "data size too large",
                             "invalid status code"};

int
csv_error(const struct csv_parser *p)
{
  assert(p && "received null csv_parser");


  return p->status;
}

const char *
csv_strerror(int status)
{

  if (status >= 4 || status < 0)
    return csv_errors[4];
  else
    return csv_errors[status];
}

int
csv_get_opts(const struct csv_parser *p)
{

  if (p == 0)
    return -1;

  return p->options;
}

int
csv_set_opts(struct csv_parser *p, unsigned char options)
{

  if (p == 0)
    return -1;

  p->options = options;
  return 0;
}

int
csv_init(struct csv_parser *p, unsigned char options)
{

  if (p == 0)
    return -1;

  p->entry_buf = 0;
  p->pstate = 0;
  p->quoted = 0;
  p->spaces = 0;
  p->entry_pos = 0;
  p->entry_size = 0;
  p->status = 0;
  p->options = options;
  p->quote_char = 0x22;
  p->delim_char = 0x2c;
  p->is_space = 0;
  p->is_term = 0;
  p->blk_size = 128;
  p->malloc_func = 0;
  p->realloc_func = realloc;
  p->free_func = free;

  return 0;
}

void
csv_free(struct csv_parser *p)
{

  if (p == 0)
    return;

  if (p->entry_buf && p->free_func)
    p->free_func(p->entry_buf);

  p->entry_buf = 0;
  p->entry_size = 0;

  return;
}

int
csv_fini(struct csv_parser *p, void (*cb1)(void *, size_t, void *), void (*cb2)(int c, void *), void *data)
{
  if (p == 0)
    return -1;


  int quoted = p->quoted;
  int pstate = p->pstate;
  size_t spaces = p->spaces;
  size_t entry_pos = p->entry_pos;

  if ((pstate == 2) && p->quoted && (p->options & 1) && (p->options & 4)) {

    p->status = 1;
    return -1;
  }

  switch (pstate) {
    case 3:
      p->entry_pos -= p->spaces + 1;
      entry_pos = p->entry_pos;

    case 1:
    case 2:




      do { if (!quoted) entry_pos -= spaces; if (p->options & 8) ((p)->entry_buf[entry_pos]) = '\0'; if (cb1 && (p->options & 16) && !quoted && entry_pos == 0) cb1(0, entry_pos, data); else if (cb1) cb1(p->entry_buf, entry_pos, data); pstate = 1; entry_pos = quoted = spaces = 0; } while (0);
      do { if (cb2) cb2(-1, data); pstate = 0; entry_pos = quoted = spaces = 0; } while (0);
      break;
    case 0:
      ;
  }


  p->spaces = p->quoted = p->entry_pos = p->status = 0;
  p->pstate = 0;

  return 0;
}

void
csv_set_delim(struct csv_parser *p, unsigned char c)
{

  if (p) p->delim_char = c;
}

void
csv_set_quote(struct csv_parser *p, unsigned char c)
{

  if (p) p->quote_char = c;
}

unsigned char
csv_get_delim(const struct csv_parser *p)
{
  assert(p && "received null csv_parser");


  return p->delim_char;
}

unsigned char
csv_get_quote(const struct csv_parser *p)
{
  assert(p && "received null csv_parser");


  return p->quote_char;
}

void
csv_set_space_func(struct csv_parser *p, int (*f)(unsigned char))
{

  if (p) p->is_space = f;
}

void
csv_set_term_func(struct csv_parser *p, int (*f)(unsigned char))
{

  if (p) p->is_term = f;
}

void
csv_set_realloc_func(struct csv_parser *p, void *(*f)(void *, size_t))
{

  if (p && f) p->realloc_func = f;
}

void
csv_set_free_func(struct csv_parser *p, void (*f)(void *))
{

  if (p && f) p->free_func = f;
}

void
csv_set_blk_size(struct csv_parser *p, size_t size)
{

  if (p) p->blk_size = size;
}

size_t
csv_get_buffer_size(const struct csv_parser *p)
{

  if (p)
    return p->entry_size;
  return 0;
}

static int
csv_increase_buffer(struct csv_parser *p)
{
  if (p == 0) return 0;
  if (p->realloc_func == 0) return 0;







  size_t to_add = p->blk_size;
  void *vp;

  if ( p->entry_size >= SIZE_MAX - to_add )
    to_add = SIZE_MAX - p->entry_size;

  if (!to_add) {
    p->status = 3;
    return -1;
  }

  while ((vp = p->realloc_func(p->entry_buf, p->entry_size + to_add)) == 0) {
    to_add /= 2;
    if (!to_add) {
      p->status = 2;
      return -1;
    }
  }


  p->entry_buf = vp;
  p->entry_size += to_add;
  return 0;
}

size_t
csv_parse(struct csv_parser *p, const void *s, size_t len, void (*cb1)(void *, size_t, void *), void (*cb2)(int c, void *), void *data)
{
  assert(p && "received null csv_parser");

  if (s == 0) return 0;

  unsigned const char *us = s;
  unsigned char c;
  size_t pos = 0;


  unsigned char delim = p->delim_char;
  unsigned char quote = p->quote_char;
  int (*is_space)(unsigned char) = p->is_space;
  int (*is_term)(unsigned char) = p->is_term;
  int quoted = p->quoted;
  int pstate = p->pstate;
  size_t spaces = p->spaces;
  size_t entry_pos = p->entry_pos;


  if (!p->entry_buf && pos < len) {

    if (csv_increase_buffer(p) != 0) {
      p->quoted = quoted, p->pstate = pstate, p->spaces = spaces, p->entry_pos = entry_pos;
      return pos;
    }
  }

  while (pos < len) {

    if (entry_pos == ((p->options & 8) ? p->entry_size - 1 : p->entry_size) ) {
      if (csv_increase_buffer(p) != 0) {
        p->quoted = quoted, p->pstate = pstate, p->spaces = spaces, p->entry_pos = entry_pos;
        return pos;
      }
    }

    c = us[pos++];

    switch (pstate) {
      case 0:
      case 1:
        if ((is_space ? is_space(c) : c == 0x20 || c == 0x09) && c!=delim) {
          continue;
        } else if (is_term ? is_term(c) : c == 0x0d || c == 0x0a) {
          if (pstate == 1) {
            do { if (!quoted) entry_pos -= spaces; if (p->options & 8) ((p)->entry_buf[entry_pos]) = '\0'; if (cb1 && (p->options & 16) && !quoted && entry_pos == 0) cb1(0, entry_pos, data); else if (cb1) cb1(p->entry_buf, entry_pos, data); pstate = 1; entry_pos = quoted = spaces = 0; } while (0);
            do { if (cb2) cb2(c, data); pstate = 0; entry_pos = quoted = spaces = 0; } while (0);
          } else {

            if (p->options & 2) {
              do { if (cb2) cb2(c, data); pstate = 0; entry_pos = quoted = spaces = 0; } while (0);
            }
          }
          continue;
        } else if (c == delim) {
          do { if (!quoted) entry_pos -= spaces; if (p->options & 8) ((p)->entry_buf[entry_pos]) = '\0'; if (cb1 && (p->options & 16) && !quoted && entry_pos == 0) cb1(0, entry_pos, data); else if (cb1) cb1(p->entry_buf, entry_pos, data); pstate = 1; entry_pos = quoted = spaces = 0; } while (0);
          break;
        } else if (c == quote) {
          pstate = 2;
          quoted = 1;
        } else {
          pstate = 2;
          quoted = 0;
          ((p)->entry_buf[entry_pos++] = (c));
        }
        break;
      case 2:
        if (c == quote) {
          if (quoted) {
            ((p)->entry_buf[entry_pos++] = (c));
            pstate = 3;
          } else {

            if (p->options & 1) {
              p->status = 1;
              p->quoted = quoted, p->pstate = pstate, p->spaces = spaces, p->entry_pos = entry_pos;
              return pos-1;
            }
            ((p)->entry_buf[entry_pos++] = (c));
            spaces = 0;
          }
        } else if (c == delim) {
          if (quoted) {
            ((p)->entry_buf[entry_pos++] = (c));
          } else {
            do { if (!quoted) entry_pos -= spaces; if (p->options & 8) ((p)->entry_buf[entry_pos]) = '\0'; if (cb1 && (p->options & 16) && !quoted && entry_pos == 0) cb1(0, entry_pos, data); else if (cb1) cb1(p->entry_buf, entry_pos, data); pstate = 1; entry_pos = quoted = spaces = 0; } while (0);
          }
        } else if (is_term ? is_term(c) : c == 0x0d || c == 0x0a) {
          if (!quoted) {
            do { if (!quoted) entry_pos -= spaces; if (p->options & 8) ((p)->entry_buf[entry_pos]) = '\0'; if (cb1 && (p->options & 16) && !quoted && entry_pos == 0) cb1(0, entry_pos, data); else if (cb1) cb1(p->entry_buf, entry_pos, data); pstate = 1; entry_pos = quoted = spaces = 0; } while (0);
            do { if (cb2) cb2(c, data); pstate = 0; entry_pos = quoted = spaces = 0; } while (0);
          } else {
            ((p)->entry_buf[entry_pos++] = (c));
          }
        } else if (!quoted && (is_space? is_space(c) : c == 0x20 || c == 0x09)) {
            ((p)->entry_buf[entry_pos++] = (c));
            spaces++;
        } else {
          ((p)->entry_buf[entry_pos++] = (c));
          spaces = 0;
        }
        break;
      case 3:

        if (c == delim) {
          entry_pos -= spaces + 1;
          do { if (!quoted) entry_pos -= spaces; if (p->options & 8) ((p)->entry_buf[entry_pos]) = '\0'; if (cb1 && (p->options & 16) && !quoted && entry_pos == 0) cb1(0, entry_pos, data); else if (cb1) cb1(p->entry_buf, entry_pos, data); pstate = 1; entry_pos = quoted = spaces = 0; } while (0);
        } else if (is_term ? is_term(c) : c == 0x0d || c == 0x0a) {
          entry_pos -= spaces + 1;
          do { if (!quoted) entry_pos -= spaces; if (p->options & 8) ((p)->entry_buf[entry_pos]) = '\0'; if (cb1 && (p->options & 16) && !quoted && entry_pos == 0) cb1(0, entry_pos, data); else if (cb1) cb1(p->entry_buf, entry_pos, data); pstate = 1; entry_pos = quoted = spaces = 0; } while (0);
          do { if (cb2) cb2(c, data); pstate = 0; entry_pos = quoted = spaces = 0; } while (0);
        } else if (is_space ? is_space(c) : c == 0x20 || c == 0x09) {
          ((p)->entry_buf[entry_pos++] = (c));
          spaces++;
        } else if (c == quote) {
          if (spaces) {

            if (p->options & 1) {
              p->status = 1;
              p->quoted = quoted, p->pstate = pstate, p->spaces = spaces, p->entry_pos = entry_pos;
              return pos-1;
            }
            spaces = 0;
            ((p)->entry_buf[entry_pos++] = (c));
          } else {

            pstate = 2;
          }
        } else {

          if (p->options & 1) {
            p->status = 1;
            p->quoted = quoted, p->pstate = pstate, p->spaces = spaces, p->entry_pos = entry_pos;
            return pos-1;
          }
          pstate = 2;
          spaces = 0;
          ((p)->entry_buf[entry_pos++] = (c));
        }
        break;
     default:
       break;
    }
  }
  p->quoted = quoted, p->pstate = pstate, p->spaces = spaces, p->entry_pos = entry_pos;
  return pos;
}

size_t
csv_write (void *dest, size_t dest_size, const void *src, size_t src_size)
{
  return csv_write2(dest, dest_size, src, src_size, 0x22);
}

int
csv_fwrite (FILE *fp, const void *src, size_t src_size)
{
  return csv_fwrite2(fp, src, src_size, 0x22);
}

size_t
csv_write2 (void *dest, size_t dest_size, const void *src, size_t src_size, unsigned char quote)
{
  unsigned char *cdest = dest;
  const unsigned char *csrc = src;
  size_t chars = 0;

  if (src == 0)
    return 0;

  if (dest == 0)
    dest_size = 0;

  if (dest_size > 0)
    *cdest++ = quote;
  chars++;

  while (src_size) {
    if (*csrc == quote) {
      if (dest_size > chars)
        *cdest++ = quote;
      if (chars < SIZE_MAX) chars++;
    }
    if (dest_size > chars)
      *cdest++ = *csrc;
    if (chars < SIZE_MAX) chars++;
    src_size--;
    csrc++;
  }

  if (dest_size > chars)
    *cdest = quote;
  if (chars < SIZE_MAX) chars++;

  return chars;
}

int
csv_fwrite2 (FILE *fp, const void *src, size_t src_size, unsigned char quote)
{
  const unsigned char *csrc = src;

  if (fp == 0 || src == 0)
    return 0;

  if (fputc(quote, fp) == EOF)
    return EOF;

  while (src_size) {
    if (*csrc == quote) {
      if (fputc(quote, fp) == EOF)
        return EOF;
    }
    if (fputc(*csrc, fp) == EOF)
      return EOF;
    src_size--;
    csrc++;
  }

  if (fputc(quote, fp) == EOF) {
    return EOF;
  }

  return 0;
}
