# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c"
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c"
#pragma GCC diagnostic ignored "-Wsuggest-attribute=pure"


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
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h" 2
# 42 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
enum quoting_style
  {
# 55 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
    literal_quoting_style,
# 69 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
    shell_quoting_style,
# 84 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
    shell_always_quoting_style,
# 100 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
    shell_escape_quoting_style,
# 117 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
    shell_escape_always_quoting_style,
# 131 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
    c_quoting_style,
# 143 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
    c_maybe_quoting_style,
# 156 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
    escape_quoting_style,
# 182 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
    locale_quoting_style,
# 207 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
    clocale_quoting_style,
# 250 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
    custom_quoting_style
  };


enum quoting_flags
  {



    QA_ELIDE_NULL_BYTES = 0x01,
# 268 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
    QA_ELIDE_OUTER_QUOTES = 0x02,





    QA_SPLIT_TRIGRAPHS = 0x04
  };







extern char const *const quoting_style_args[];
extern enum quoting_style const quoting_style_vals[];

struct quoting_options;







struct quoting_options *clone_quoting_options (struct quoting_options *o)
 
  ;


enum quoting_style get_quoting_style (struct quoting_options const *o);



void set_quoting_style (struct quoting_options *o, enum quoting_style s);
# 312 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
int set_char_quoting (struct quoting_options *o, char c, int i);





int set_quoting_flags (struct quoting_options *o, int i);
# 329 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
void set_custom_quoting (struct quoting_options *o,
                         char const *left_quote,
                         char const *right_quote);
# 344 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
size_t quotearg_buffer (char * buffer, size_t buffersize,
                        char const *arg, size_t argsize,
                        struct quoting_options const *o);




char *quotearg_alloc (char const *arg, size_t argsize,
                      struct quoting_options const *o)
 
  ;







char *quotearg_alloc_mem (char const *arg, size_t argsize,
                          size_t *size, struct quoting_options const *o)
 
  ;
# 374 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
char *quotearg_n (int n, char const *arg);


char *quotearg (char const *arg);




char *quotearg_n_mem (int n, char const *arg, size_t argsize);


char *quotearg_mem (char const *arg, size_t argsize);




char *quotearg_n_style (int n, enum quoting_style s, char const *arg);




char *quotearg_n_style_mem (int n, enum quoting_style s,
                            char const *arg, size_t argsize);


char *quotearg_style (enum quoting_style s, char const *arg);


char *quotearg_style_mem (enum quoting_style s,
                          char const *arg, size_t argsize);



char *quotearg_char (char const *arg, char ch);


char *quotearg_char_mem (char const *arg, size_t argsize, char ch);


char *quotearg_colon (char const *arg);


char *quotearg_colon_mem (char const *arg, size_t argsize);


char *quotearg_n_style_colon (int n, enum quoting_style s, char const *arg);





char *quotearg_n_custom (int n, char const *left_quote,
                         char const *right_quote, char const *arg);



char *quotearg_n_custom_mem (int n, char const *left_quote,
                             char const *right_quote,
                             char const *arg, size_t argsize);


char *quotearg_custom (char const *left_quote, char const *right_quote,
                       char const *arg);



char *quotearg_custom_mem (char const *left_quote,
                           char const *right_quote,
                           char const *arg, size_t argsize);


void quotearg_free (void);
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quote.h" 1
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quote.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quote.h" 2
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quote.h"
extern struct quoting_options quote_quoting_options;





char const *quote_n_mem (int n, char const *arg, size_t argsize);




char const *quote_mem (char const *arg, size_t argsize);



char const *quote_n (int n, char const *arg);



char const *quote (char const *arg);
# 31 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/attribute.h" 1
# 33 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/minmax.h" 1
# 39 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/minmax.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/param.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/param.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/param.h" 2
# 40 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/minmax.h" 2
# 34 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2
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





inline void *xnrealloc (void *p, size_t n, size_t s)
  ;
inline void *
xnrealloc (void *p, size_t n, size_t s)
{
  return xreallocarray (p, n, s);
}




char *xcharalloc (size_t n)
 
  ;
# 213 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xalloc.h"

# 35 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c-strcaseeq.h" 1
# 19 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c-strcaseeq.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c-strcase.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c-strcase.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c-strcase.h" 2
# 47 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c-strcase.h"
extern int c_strcasecmp (const char *s1, const char *s2) ;




extern int c_strncasecmp (const char *s1, const char *s2, size_t n)
  ;
# 20 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c-strcaseeq.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c-ctype.h" 1
# 31 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c-ctype.h"

# 168 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c-ctype.h"
inline bool
c_isalnum (int c)
{
  switch (c)
    {
    case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
    case 'a' + (0): case 'b' + (0): case 'c' + (0): case 'd' + (0): case 'e' + (0): case 'f' + (0): case 'g' + (0): case 'h' + (0): case 'i' + (0): case 'j' + (0): case 'k' + (0): case 'l' + (0): case 'm' + (0): case 'n' + (0): case 'o' + (0): case 'p' + (0): case 'q' + (0): case 'r' + (0): case 's' + (0): case 't' + (0): case 'u' + (0): case 'v' + (0): case 'w' + (0): case 'x' + (0): case 'y' + (0): case 'z' + (0):
    case 'a' + ('A' - 'a'): case 'b' + ('A' - 'a'): case 'c' + ('A' - 'a'): case 'd' + ('A' - 'a'): case 'e' + ('A' - 'a'): case 'f' + ('A' - 'a'): case 'g' + ('A' - 'a'): case 'h' + ('A' - 'a'): case 'i' + ('A' - 'a'): case 'j' + ('A' - 'a'): case 'k' + ('A' - 'a'): case 'l' + ('A' - 'a'): case 'm' + ('A' - 'a'): case 'n' + ('A' - 'a'): case 'o' + ('A' - 'a'): case 'p' + ('A' - 'a'): case 'q' + ('A' - 'a'): case 'r' + ('A' - 'a'): case 's' + ('A' - 'a'): case 't' + ('A' - 'a'): case 'u' + ('A' - 'a'): case 'v' + ('A' - 'a'): case 'w' + ('A' - 'a'): case 'x' + ('A' - 'a'): case 'y' + ('A' - 'a'): case 'z' + ('A' - 'a'):
      return 1;
    default:
      return 0;
    }
}

inline bool
c_isalpha (int c)
{
  switch (c)
    {
    case 'a' + (0): case 'b' + (0): case 'c' + (0): case 'd' + (0): case 'e' + (0): case 'f' + (0): case 'g' + (0): case 'h' + (0): case 'i' + (0): case 'j' + (0): case 'k' + (0): case 'l' + (0): case 'm' + (0): case 'n' + (0): case 'o' + (0): case 'p' + (0): case 'q' + (0): case 'r' + (0): case 's' + (0): case 't' + (0): case 'u' + (0): case 'v' + (0): case 'w' + (0): case 'x' + (0): case 'y' + (0): case 'z' + (0):
    case 'a' + ('A' - 'a'): case 'b' + ('A' - 'a'): case 'c' + ('A' - 'a'): case 'd' + ('A' - 'a'): case 'e' + ('A' - 'a'): case 'f' + ('A' - 'a'): case 'g' + ('A' - 'a'): case 'h' + ('A' - 'a'): case 'i' + ('A' - 'a'): case 'j' + ('A' - 'a'): case 'k' + ('A' - 'a'): case 'l' + ('A' - 'a'): case 'm' + ('A' - 'a'): case 'n' + ('A' - 'a'): case 'o' + ('A' - 'a'): case 'p' + ('A' - 'a'): case 'q' + ('A' - 'a'): case 'r' + ('A' - 'a'): case 's' + ('A' - 'a'): case 't' + ('A' - 'a'): case 'u' + ('A' - 'a'): case 'v' + ('A' - 'a'): case 'w' + ('A' - 'a'): case 'x' + ('A' - 'a'): case 'y' + ('A' - 'a'): case 'z' + ('A' - 'a'):
      return 1;
    default:
      return 0;
    }
}



inline bool
c_isascii (int c)
{
  switch (c)
    {
    case ' ':
    case '\a': case '\b': case '\f': case '\n': case '\r': case '\t': case '\v': case '\x00': case '\x01': case '\x02': case '\x03': case '\x04': case '\x05': case '\x06': case '\x0e': case '\x0f': case '\x10': case '\x11': case '\x12': case '\x13': case '\x14': case '\x15': case '\x16': case '\x17': case '\x18': case '\x19': case '\x1a': case '\x1b': case '\x1c': case '\x1d': case '\x1e': case '\x1f': case '\x7f':
    case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
    case 'a' + (0): case 'b' + (0): case 'c' + (0): case 'd' + (0): case 'e' + (0): case 'f' + (0): case 'g' + (0): case 'h' + (0): case 'i' + (0): case 'j' + (0): case 'k' + (0): case 'l' + (0): case 'm' + (0): case 'n' + (0): case 'o' + (0): case 'p' + (0): case 'q' + (0): case 'r' + (0): case 's' + (0): case 't' + (0): case 'u' + (0): case 'v' + (0): case 'w' + (0): case 'x' + (0): case 'y' + (0): case 'z' + (0):
    case '!': case '"': case '#': case '$': case '%': case '&': case '\'': case '(': case ')': case '*': case '+': case ',': case '-': case '.': case '/': case ':': case ';': case '<': case '=': case '>': case '?': case '@': case '[': case '\\': case ']': case '^': case '_': case '`': case '{': case '|': case '}': case '~':
    case 'a' + ('A' - 'a'): case 'b' + ('A' - 'a'): case 'c' + ('A' - 'a'): case 'd' + ('A' - 'a'): case 'e' + ('A' - 'a'): case 'f' + ('A' - 'a'): case 'g' + ('A' - 'a'): case 'h' + ('A' - 'a'): case 'i' + ('A' - 'a'): case 'j' + ('A' - 'a'): case 'k' + ('A' - 'a'): case 'l' + ('A' - 'a'): case 'm' + ('A' - 'a'): case 'n' + ('A' - 'a'): case 'o' + ('A' - 'a'): case 'p' + ('A' - 'a'): case 'q' + ('A' - 'a'): case 'r' + ('A' - 'a'): case 's' + ('A' - 'a'): case 't' + ('A' - 'a'): case 'u' + ('A' - 'a'): case 'v' + ('A' - 'a'): case 'w' + ('A' - 'a'): case 'x' + ('A' - 'a'): case 'y' + ('A' - 'a'): case 'z' + ('A' - 'a'):
      return 1;
    default:
      return 0;
    }
}

inline bool
c_isblank (int c)
{
  return c == ' ' || c == '\t';
}

inline bool
c_iscntrl (int c)
{
  switch (c)
    {
    case '\a': case '\b': case '\f': case '\n': case '\r': case '\t': case '\v': case '\x00': case '\x01': case '\x02': case '\x03': case '\x04': case '\x05': case '\x06': case '\x0e': case '\x0f': case '\x10': case '\x11': case '\x12': case '\x13': case '\x14': case '\x15': case '\x16': case '\x17': case '\x18': case '\x19': case '\x1a': case '\x1b': case '\x1c': case '\x1d': case '\x1e': case '\x1f': case '\x7f':
      return 1;
    default:
      return 0;
    }
}

inline bool
c_isdigit (int c)
{
  switch (c)
    {
    case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
      return 1;
    default:
      return 0;
    }
}

inline bool
c_isgraph (int c)
{
  switch (c)
    {
    case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
    case 'a' + (0): case 'b' + (0): case 'c' + (0): case 'd' + (0): case 'e' + (0): case 'f' + (0): case 'g' + (0): case 'h' + (0): case 'i' + (0): case 'j' + (0): case 'k' + (0): case 'l' + (0): case 'm' + (0): case 'n' + (0): case 'o' + (0): case 'p' + (0): case 'q' + (0): case 'r' + (0): case 's' + (0): case 't' + (0): case 'u' + (0): case 'v' + (0): case 'w' + (0): case 'x' + (0): case 'y' + (0): case 'z' + (0):
    case '!': case '"': case '#': case '$': case '%': case '&': case '\'': case '(': case ')': case '*': case '+': case ',': case '-': case '.': case '/': case ':': case ';': case '<': case '=': case '>': case '?': case '@': case '[': case '\\': case ']': case '^': case '_': case '`': case '{': case '|': case '}': case '~':
    case 'a' + ('A' - 'a'): case 'b' + ('A' - 'a'): case 'c' + ('A' - 'a'): case 'd' + ('A' - 'a'): case 'e' + ('A' - 'a'): case 'f' + ('A' - 'a'): case 'g' + ('A' - 'a'): case 'h' + ('A' - 'a'): case 'i' + ('A' - 'a'): case 'j' + ('A' - 'a'): case 'k' + ('A' - 'a'): case 'l' + ('A' - 'a'): case 'm' + ('A' - 'a'): case 'n' + ('A' - 'a'): case 'o' + ('A' - 'a'): case 'p' + ('A' - 'a'): case 'q' + ('A' - 'a'): case 'r' + ('A' - 'a'): case 's' + ('A' - 'a'): case 't' + ('A' - 'a'): case 'u' + ('A' - 'a'): case 'v' + ('A' - 'a'): case 'w' + ('A' - 'a'): case 'x' + ('A' - 'a'): case 'y' + ('A' - 'a'): case 'z' + ('A' - 'a'):
      return 1;
    default:
      return 0;
    }
}

inline bool
c_islower (int c)
{
  switch (c)
    {
    case 'a' + (0): case 'b' + (0): case 'c' + (0): case 'd' + (0): case 'e' + (0): case 'f' + (0): case 'g' + (0): case 'h' + (0): case 'i' + (0): case 'j' + (0): case 'k' + (0): case 'l' + (0): case 'm' + (0): case 'n' + (0): case 'o' + (0): case 'p' + (0): case 'q' + (0): case 'r' + (0): case 's' + (0): case 't' + (0): case 'u' + (0): case 'v' + (0): case 'w' + (0): case 'x' + (0): case 'y' + (0): case 'z' + (0):
      return 1;
    default:
      return 0;
    }
}

inline bool
c_isprint (int c)
{
  switch (c)
    {
    case ' ':
    case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
    case 'a' + (0): case 'b' + (0): case 'c' + (0): case 'd' + (0): case 'e' + (0): case 'f' + (0): case 'g' + (0): case 'h' + (0): case 'i' + (0): case 'j' + (0): case 'k' + (0): case 'l' + (0): case 'm' + (0): case 'n' + (0): case 'o' + (0): case 'p' + (0): case 'q' + (0): case 'r' + (0): case 's' + (0): case 't' + (0): case 'u' + (0): case 'v' + (0): case 'w' + (0): case 'x' + (0): case 'y' + (0): case 'z' + (0):
    case '!': case '"': case '#': case '$': case '%': case '&': case '\'': case '(': case ')': case '*': case '+': case ',': case '-': case '.': case '/': case ':': case ';': case '<': case '=': case '>': case '?': case '@': case '[': case '\\': case ']': case '^': case '_': case '`': case '{': case '|': case '}': case '~':
    case 'a' + ('A' - 'a'): case 'b' + ('A' - 'a'): case 'c' + ('A' - 'a'): case 'd' + ('A' - 'a'): case 'e' + ('A' - 'a'): case 'f' + ('A' - 'a'): case 'g' + ('A' - 'a'): case 'h' + ('A' - 'a'): case 'i' + ('A' - 'a'): case 'j' + ('A' - 'a'): case 'k' + ('A' - 'a'): case 'l' + ('A' - 'a'): case 'm' + ('A' - 'a'): case 'n' + ('A' - 'a'): case 'o' + ('A' - 'a'): case 'p' + ('A' - 'a'): case 'q' + ('A' - 'a'): case 'r' + ('A' - 'a'): case 's' + ('A' - 'a'): case 't' + ('A' - 'a'): case 'u' + ('A' - 'a'): case 'v' + ('A' - 'a'): case 'w' + ('A' - 'a'): case 'x' + ('A' - 'a'): case 'y' + ('A' - 'a'): case 'z' + ('A' - 'a'):
      return 1;
    default:
      return 0;
    }
}

inline bool
c_ispunct (int c)
{
  switch (c)
    {
    case '!': case '"': case '#': case '$': case '%': case '&': case '\'': case '(': case ')': case '*': case '+': case ',': case '-': case '.': case '/': case ':': case ';': case '<': case '=': case '>': case '?': case '@': case '[': case '\\': case ']': case '^': case '_': case '`': case '{': case '|': case '}': case '~':
      return 1;
    default:
      return 0;
    }
}

inline bool
c_isspace (int c)
{
  switch (c)
    {
    case ' ': case '\t': case '\n': case '\v': case '\f': case '\r':
      return 1;
    default:
      return 0;
    }
}

inline bool
c_isupper (int c)
{
  switch (c)
    {
    case 'a' + ('A' - 'a'): case 'b' + ('A' - 'a'): case 'c' + ('A' - 'a'): case 'd' + ('A' - 'a'): case 'e' + ('A' - 'a'): case 'f' + ('A' - 'a'): case 'g' + ('A' - 'a'): case 'h' + ('A' - 'a'): case 'i' + ('A' - 'a'): case 'j' + ('A' - 'a'): case 'k' + ('A' - 'a'): case 'l' + ('A' - 'a'): case 'm' + ('A' - 'a'): case 'n' + ('A' - 'a'): case 'o' + ('A' - 'a'): case 'p' + ('A' - 'a'): case 'q' + ('A' - 'a'): case 'r' + ('A' - 'a'): case 's' + ('A' - 'a'): case 't' + ('A' - 'a'): case 'u' + ('A' - 'a'): case 'v' + ('A' - 'a'): case 'w' + ('A' - 'a'): case 'x' + ('A' - 'a'): case 'y' + ('A' - 'a'): case 'z' + ('A' - 'a'):
      return 1;
    default:
      return 0;
    }
}

inline bool
c_isxdigit (int c)
{
  switch (c)
    {
    case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
    case 'a' + (0): case 'b' + (0): case 'c' + (0): case 'd' + (0): case 'e' + (0): case 'f' + (0): case 'a' + ('A' - 'a'): case 'b' + ('A' - 'a'): case 'c' + ('A' - 'a'): case 'd' + ('A' - 'a'): case 'e' + ('A' - 'a'): case 'f' + ('A' - 'a'):
      return 1;
    default:
      return 0;
    }
}

inline int
c_tolower (int c)
{
  switch (c)
    {
    case 'a' + ('A' - 'a'): case 'b' + ('A' - 'a'): case 'c' + ('A' - 'a'): case 'd' + ('A' - 'a'): case 'e' + ('A' - 'a'): case 'f' + ('A' - 'a'): case 'g' + ('A' - 'a'): case 'h' + ('A' - 'a'): case 'i' + ('A' - 'a'): case 'j' + ('A' - 'a'): case 'k' + ('A' - 'a'): case 'l' + ('A' - 'a'): case 'm' + ('A' - 'a'): case 'n' + ('A' - 'a'): case 'o' + ('A' - 'a'): case 'p' + ('A' - 'a'): case 'q' + ('A' - 'a'): case 'r' + ('A' - 'a'): case 's' + ('A' - 'a'): case 't' + ('A' - 'a'): case 'u' + ('A' - 'a'): case 'v' + ('A' - 'a'): case 'w' + ('A' - 'a'): case 'x' + ('A' - 'a'): case 'y' + ('A' - 'a'): case 'z' + ('A' - 'a'):
      return c - 'A' + 'a';
    default:
      return c;
    }
}

inline int
c_toupper (int c)
{
  switch (c)
    {
    case 'a' + (0): case 'b' + (0): case 'c' + (0): case 'd' + (0): case 'e' + (0): case 'f' + (0): case 'g' + (0): case 'h' + (0): case 'i' + (0): case 'j' + (0): case 'k' + (0): case 'l' + (0): case 'm' + (0): case 'n' + (0): case 'o' + (0): case 'p' + (0): case 'q' + (0): case 'r' + (0): case 's' + (0): case 't' + (0): case 'u' + (0): case 'v' + (0): case 'w' + (0): case 'x' + (0): case 'y' + (0): case 'z' + (0):
      return c - 'a' + 'A';
    default:
      return c;
    }
}






# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c-strcaseeq.h" 2
# 36 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/localcharset.h" 1
# 35 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/localcharset.h"
extern const char * locale_charset (void);
# 37 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/ctype.h" 1
# 39 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/errno.h" 1
# 40 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 1
# 41 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 42 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 43 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 44 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/uchar.h" 1
# 45 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/wchar.h" 1
# 46 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/gettext.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/gettext.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/libintl.h" 1
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/gettext.h" 2
# 141 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/gettext.h"
static const char *
pgettext_aux (const char *domain,
              const char *msg_ctxt_id, const char *msgid,
              int category)
{
  const char *translation = dcgettext (domain, msg_ctxt_id, category);
  if (translation == msg_ctxt_id)
    return msgid;
  else
    return translation;
}

static const char *
npgettext_aux (const char *domain,
               const char *msg_ctxt_id, const char *msgid,
               const char *msgid_plural, unsigned long int n,
               int category)
{
  const char *translation =
    dcngettext (domain, msg_ctxt_id, msgid_plural, n, category);
  if (translation == msg_ctxt_id || translation == msgid_plural)
    return (n == 1 ? msgid : msgid_plural);
  else
    return translation;
}





# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 172 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/gettext.h" 2
# 188 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/gettext.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 189 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/gettext.h" 2







static const char *
dcpgettext_expr (const char *domain,
                 const char *msgctxt, const char *msgid,
                 int category)
{
  size_t msgctxt_len = strlen (msgctxt) + 1;
  size_t msgid_len = strlen (msgid) + 1;
  const char *translation;



  char buf[1024];
  char *msg_ctxt_id =
    (msgctxt_len + msgid_len <= sizeof (buf)
     ? buf
     : (char *) malloc (msgctxt_len + msgid_len));
  if (msg_ctxt_id != 0)

    {
      int found_translation;
      memcpy (msg_ctxt_id, msgctxt, msgctxt_len - 1);
      msg_ctxt_id[msgctxt_len - 1] = '\004';
      memcpy (msg_ctxt_id + msgctxt_len, msgid, msgid_len);
      translation = dcgettext (domain, msg_ctxt_id, category);
      found_translation = (translation != msg_ctxt_id);

      if (msg_ctxt_id != buf)
        free (msg_ctxt_id);

      if (found_translation)
        return translation;
    }
  return msgid;
}






static const char *
dcnpgettext_expr (const char *domain,
                  const char *msgctxt, const char *msgid,
                  const char *msgid_plural, unsigned long int n,
                  int category)
{
  size_t msgctxt_len = strlen (msgctxt) + 1;
  size_t msgid_len = strlen (msgid) + 1;
  const char *translation;



  char buf[1024];
  char *msg_ctxt_id =
    (msgctxt_len + msgid_len <= sizeof (buf)
     ? buf
     : (char *) malloc (msgctxt_len + msgid_len));
  if (msg_ctxt_id != 0)

    {
      int found_translation;
      memcpy (msg_ctxt_id, msgctxt, msgctxt_len - 1);
      msg_ctxt_id[msgctxt_len - 1] = '\004';
      memcpy (msg_ctxt_id + msgctxt_len, msgid, msgid_len);
      translation = dcngettext (domain, msg_ctxt_id, msgid_plural, n, category);
      found_translation = !(translation == msg_ctxt_id || translation == msgid_plural);

      if (msg_ctxt_id != buf)
        free (msg_ctxt_id);

      if (found_translation)
        return translation;
    }
  return (n == 1 ? msgid : msgid_plural);
}
# 48 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2
# 57 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c"
struct quoting_options
{

  enum quoting_style style;


  int flags;



  unsigned int quote_these_too[(255 / (sizeof (int) * 8)) + 1];


  char const *left_quote;


  char const *right_quote;
};


char const *const quoting_style_args[] =
{
  "literal",
  "shell",
  "shell-always",
  "shell-escape",
  "shell-escape-always",
  "c",
  "c-maybe",
  "escape",
  "locale",
  "clocale",
  0
};


enum quoting_style const quoting_style_vals[] =
{
  literal_quoting_style,
  shell_quoting_style,
  shell_always_quoting_style,
  shell_escape_quoting_style,
  shell_escape_always_quoting_style,
  c_quoting_style,
  c_maybe_quoting_style,
  escape_quoting_style,
  locale_quoting_style,
  clocale_quoting_style
};


static struct quoting_options default_quoting_options;




struct quoting_options *
clone_quoting_options (struct quoting_options *o)
{
  int e = errno;
  struct quoting_options *p = xmemdup (o ? o : &default_quoting_options,
                                       sizeof *o);
  errno = e;
  return p;
}


enum quoting_style
get_quoting_style (struct quoting_options const *o)
{
  return (o ? o : &default_quoting_options)->style;
}



void
set_quoting_style (struct quoting_options *o, enum quoting_style s)
{
  (o ? o : &default_quoting_options)->style = s;
}






int
set_char_quoting (struct quoting_options *o, char c, int i)
{
  unsigned char uc = c;
  unsigned int *p =
    (o ? o : &default_quoting_options)->quote_these_too + uc / (sizeof (int) * 8);
  int shift = uc % (sizeof (int) * 8);
  int r = (*p >> shift) & 1;
  *p ^= ((i & 1) ^ r) << shift;
  return r;
}





int
set_quoting_flags (struct quoting_options *o, int i)
{
  int r;
  if (!o)
    o = &default_quoting_options;
  r = o->flags;
  o->flags = i;
  return r;
}

void
set_custom_quoting (struct quoting_options *o,
                    char const *left_quote, char const *right_quote)
{
  if (!o)
    o = &default_quoting_options;
  o->style = custom_quoting_style;
  if (!left_quote || !right_quote)
    abort ();
  o->left_quote = left_quote;
  o->right_quote = right_quote;
}


static struct quoting_options
quoting_options_from_style (enum quoting_style style)
{
  struct quoting_options o = { literal_quoting_style, 0, { 0 }, 0, 0 };
  if (style == custom_quoting_style)
    abort ();
  o.style = style;
  return o;
}





static char const *
gettext_quote (char const *msgid, enum quoting_style s)
{
  char const *translation = gettext (msgid);
  char const *locale_code;

  if (translation != msgid)
    return translation;
# 225 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c"
  locale_code = locale_charset ();
  if ((c_strcasecmp (locale_code, "UTF-8") == 0))
    return msgid[0] == '`' ? "\xe2\x80\x98": "\xe2\x80\x99";
  if ((c_strcasecmp (locale_code, "GB18030") == 0))
    return msgid[0] == '`' ? "\xa1\ae": "\xa1\xaf";

  return (s == clocale_quoting_style ? "\"" : "'");
}
# 247 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c"
static size_t
quotearg_buffer_restyled (char *buffer, size_t buffersize,
                          char const *arg, size_t argsize,
                          enum quoting_style quoting_style, int flags,
                          unsigned int const *quote_these_too,
                          char const *left_quote,
                          char const *right_quote)
{
  size_t i;
  size_t len = 0;
  size_t orig_buffersize = 0;
  char const *quote_string = 0;
  size_t quote_string_len = 0;
  bool backslash_escapes = 0;
  bool unibyte_locale = MB_CUR_MAX == 1;
  bool elide_outer_quotes = (flags & QA_ELIDE_OUTER_QUOTES) != 0;
  bool encountered_single_quote = 0;
  bool all_c_and_shell_quote_compat = 1;
# 305 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c"
 process_input: ;
  bool pending_shell_escape_end = 0;

  switch (quoting_style)
    {
    case c_maybe_quoting_style:
      quoting_style = c_quoting_style;
      elide_outer_quotes = 1;
      ;
    case c_quoting_style:
      if (!elide_outer_quotes)
        do { if (len < buffersize) buffer[len] = ('"'); len++; } while (0);
      backslash_escapes = 1;
      quote_string = "\"";
      quote_string_len = 1;
      break;

    case escape_quoting_style:
      backslash_escapes = 1;
      elide_outer_quotes = 0;
      break;

    case locale_quoting_style:
    case clocale_quoting_style:
    case custom_quoting_style:
      {
        if (quoting_style != custom_quoting_style)
          {
# 354 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c"
            left_quote = gettext_quote ("`", quoting_style);
            right_quote = gettext_quote ("'", quoting_style);
          }
        if (!elide_outer_quotes)
          for (quote_string = left_quote; *quote_string; quote_string++)
            do { if (len < buffersize) buffer[len] = (*quote_string); len++; } while (0);
        backslash_escapes = 1;
        quote_string = right_quote;
        quote_string_len = strlen (quote_string);
      }
      break;

    case shell_escape_quoting_style:
      backslash_escapes = 1;
      ;
    case shell_quoting_style:
      elide_outer_quotes = 1;
      ;
    case shell_escape_always_quoting_style:
      if (!elide_outer_quotes)
        backslash_escapes = 1;
      ;
    case shell_always_quoting_style:
      quoting_style = shell_always_quoting_style;
      if (!elide_outer_quotes)
        do { if (len < buffersize) buffer[len] = ('\''); len++; } while (0);
      quote_string = "'";
      quote_string_len = 1;
      break;

    case literal_quoting_style:
      elide_outer_quotes = 0;
      break;

    default:
      abort ();
    }

  for (i = 0; ! (argsize == ((size_t) -1) ? arg[i] == '\0' : i == argsize); i++)
    {
      unsigned char c;
      unsigned char esc;
      bool is_right_quote = 0;
      bool escaping = 0;
      bool c_and_shell_quote_compat = 0;

      if (backslash_escapes
          && quoting_style != shell_always_quoting_style
          && quote_string_len
          && (i + quote_string_len
              <= (argsize == ((size_t) -1) && 1 < quote_string_len



                  ? (argsize = strlen (arg)) : argsize))
          && memcmp (arg + i, quote_string, quote_string_len) == 0)
        {
          if (elide_outer_quotes)
            goto force_outer_quoting_style;
          is_right_quote = 1;
        }

      c = arg[i];
      switch (c)
        {
        case '\0':
          if (backslash_escapes)
            {
              do { if (elide_outer_quotes) goto force_outer_quoting_style; escaping = 1; if (quoting_style == shell_always_quoting_style && ! pending_shell_escape_end) { do { if (len < buffersize) buffer[len] = ('\''); len++; } while (0); do { if (len < buffersize) buffer[len] = ('$'); len++; } while (0); do { if (len < buffersize) buffer[len] = ('\''); len++; } while (0); pending_shell_escape_end = 1; } do { if (len < buffersize) buffer[len] = ('\\'); len++; } while (0); } while (0);






              if (quoting_style != shell_always_quoting_style
                  && i + 1 < argsize && '0' <= arg[i + 1] && arg[i + 1] <= '9')
                {
                  do { if (len < buffersize) buffer[len] = ('0'); len++; } while (0);
                  do { if (len < buffersize) buffer[len] = ('0'); len++; } while (0);
                }
              c = '0';




            }
          else if (flags & QA_ELIDE_NULL_BYTES)
            continue;
          break;

        case '?':
          switch (quoting_style)
            {
            case shell_always_quoting_style:
              if (elide_outer_quotes)
                goto force_outer_quoting_style;
              break;

            case c_quoting_style:
              if ((flags & QA_SPLIT_TRIGRAPHS)
                  && i + 2 < argsize && arg[i + 1] == '?')
                switch (arg[i + 2])
                  {
                  case '!': case '\'':
                  case '(': case ')': case '-': case '/':
                  case '<': case '=': case '>':


                    if (elide_outer_quotes)
                      goto force_outer_quoting_style;
                    c = arg[i + 2];
                    i += 2;
                    do { if (len < buffersize) buffer[len] = ('?'); len++; } while (0);
                    do { if (len < buffersize) buffer[len] = ('"'); len++; } while (0);
                    do { if (len < buffersize) buffer[len] = ('"'); len++; } while (0);
                    do { if (len < buffersize) buffer[len] = ('?'); len++; } while (0);
                    break;

                  default:
                    break;
                  }
              break;

            default:
              break;
            }
          break;

        case '\a': esc = 'a'; goto c_escape;
        case '\b': esc = 'b'; goto c_escape;
        case '\f': esc = 'f'; goto c_escape;
        case '\n': esc = 'n'; goto c_and_shell_escape;
        case '\r': esc = 'r'; goto c_and_shell_escape;
        case '\t': esc = 't'; goto c_and_shell_escape;
        case '\v': esc = 'v'; goto c_escape;
        case '\\': esc = c;

          if (quoting_style == shell_always_quoting_style)
            {
              if (elide_outer_quotes)
                goto force_outer_quoting_style;
              goto store_c;
            }



          if (backslash_escapes && elide_outer_quotes && quote_string_len)
            goto store_c;

        c_and_shell_escape:
          if (quoting_style == shell_always_quoting_style
              && elide_outer_quotes)
            goto force_outer_quoting_style;

        c_escape:
          if (backslash_escapes)
            {
              c = esc;
              goto store_escape;
            }
          break;

        case '{': case '}':
          if (! (argsize == ((size_t) -1) ? arg[1] == '\0' : argsize == 1))
            break;
          ;
        case '#': case '~':
          if (i != 0)
            break;
          ;
        case ' ':
          c_and_shell_quote_compat = 1;
          ;
        case '!':
        case '"': case '$': case '&':
        case '(': case ')': case '*': case ';':
        case '<':
        case '=':
        case '>': case '[':
        case '^':
        case '`': case '|':

          if (quoting_style == shell_always_quoting_style
              && elide_outer_quotes)
            goto force_outer_quoting_style;
          break;

        case '\'':
          encountered_single_quote = 1;
          c_and_shell_quote_compat = 1;
          if (quoting_style == shell_always_quoting_style)
            {
              if (elide_outer_quotes)
                goto force_outer_quoting_style;

              if (buffersize && ! orig_buffersize)
                {



                  orig_buffersize = buffersize;
                  buffersize = 0;
                }

              do { if (len < buffersize) buffer[len] = ('\''); len++; } while (0);
              do { if (len < buffersize) buffer[len] = ('\\'); len++; } while (0);
              do { if (len < buffersize) buffer[len] = ('\''); len++; } while (0);
              pending_shell_escape_end = 0;
            }
          break;

        case '%': case '+': case ',': case '-': case '.': case '/':
        case '0': case '1': case '2': case '3': case '4': case '5':
        case '6': case '7': case '8': case '9': case ':':
        case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
        case 'G': case 'H': case 'I': case 'J': case 'K': case 'L':
        case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R':
        case 'S': case 'T': case 'U': case 'V': case 'W': case 'X':
        case 'Y': case 'Z': case ']': case '_': case 'a': case 'b':
        case 'c': case 'd': case 'e': case 'f': case 'g': case 'h':
        case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
        case 'o': case 'p': case 'q': case 'r': case 's': case 't':
        case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
# 588 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c"
          c_and_shell_quote_compat = 1;
          break;

        default:





          {

            size_t m;

            bool printable;

            if (unibyte_locale)
              {
                m = 1;
                printable = isprint (c) != 0;
              }
            else
              {
                mbstate_t mbstate;
                mbszero (&mbstate);

                m = 0;
                printable = 1;
                if (argsize == ((size_t) -1))
                  argsize = strlen (arg);

                for (;;)
                  {
                    char32_t w;
                    size_t bytes = mbrtoc32 (&w, &arg[i + m],
                                             argsize - (i + m), &mbstate);
                    if (bytes == 0)
                      break;
                    else if (bytes == (size_t) -1)
                      {
                        printable = 0;
                        break;
                      }
                    else if (bytes == (size_t) -2)
                      {
                        printable = 0;
                        while (i + m < argsize && arg[i + m])
                          m++;
                        break;
                      }
                    else
                      {
# 647 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c"
                        if ('[' == 0x5b && elide_outer_quotes
                            && quoting_style == shell_always_quoting_style)
                          {
                            size_t j;
                            for (j = 1; j < bytes; j++)
                              switch (arg[i + m + j])
                                {
                                case '[': case '\\': case '^':
                                case '`': case '|':
                                  goto force_outer_quoting_style;

                                default:
                                  break;
                                }
                          }

                        if (! c32isprint (w))
                          printable = 0;
                        m += bytes;
                      }



                      break;
                  }
              }

            c_and_shell_quote_compat = printable;

            if (1 < m || (backslash_escapes && ! printable))
              {


                size_t ilim = i + m;

                for (;;)
                  {
                    if (backslash_escapes && ! printable)
                      {
                        do { if (elide_outer_quotes) goto force_outer_quoting_style; escaping = 1; if (quoting_style == shell_always_quoting_style && ! pending_shell_escape_end) { do { if (len < buffersize) buffer[len] = ('\''); len++; } while (0); do { if (len < buffersize) buffer[len] = ('$'); len++; } while (0); do { if (len < buffersize) buffer[len] = ('\''); len++; } while (0); pending_shell_escape_end = 1; } do { if (len < buffersize) buffer[len] = ('\\'); len++; } while (0); } while (0);
                        do { if (len < buffersize) buffer[len] = ('0' + (c >> 6)); len++; } while (0);
                        do { if (len < buffersize) buffer[len] = ('0' + ((c >> 3) & 7)); len++; } while (0);
                        c = '0' + (c & 7);
                      }
                    else if (is_right_quote)
                      {
                        do { if (len < buffersize) buffer[len] = ('\\'); len++; } while (0);
                        is_right_quote = 0;
                      }
                    if (ilim <= i + 1)
                      break;
                    do { if (pending_shell_escape_end && ! escaping) { do { if (len < buffersize) buffer[len] = ('\''); len++; } while (0); do { if (len < buffersize) buffer[len] = ('\''); len++; } while (0); pending_shell_escape_end = 0; } } while (0);
                    do { if (len < buffersize) buffer[len] = (c); len++; } while (0);
                    c = arg[++i];
                  }

                goto store_c;
              }
          }
        }

      if (! (((backslash_escapes && quoting_style != shell_always_quoting_style)
              || elide_outer_quotes)
             && quote_these_too
             && quote_these_too[c / (sizeof (int) * 8)] >> (c % (sizeof (int) * 8)) & 1)
          && !is_right_quote)
        goto store_c;

    store_escape:
      do { if (elide_outer_quotes) goto force_outer_quoting_style; escaping = 1; if (quoting_style == shell_always_quoting_style && ! pending_shell_escape_end) { do { if (len < buffersize) buffer[len] = ('\''); len++; } while (0); do { if (len < buffersize) buffer[len] = ('$'); len++; } while (0); do { if (len < buffersize) buffer[len] = ('\''); len++; } while (0); pending_shell_escape_end = 1; } do { if (len < buffersize) buffer[len] = ('\\'); len++; } while (0); } while (0);

    store_c:
      do { if (pending_shell_escape_end && ! escaping) { do { if (len < buffersize) buffer[len] = ('\''); len++; } while (0); do { if (len < buffersize) buffer[len] = ('\''); len++; } while (0); pending_shell_escape_end = 0; } } while (0);
      do { if (len < buffersize) buffer[len] = (c); len++; } while (0);

      if (! c_and_shell_quote_compat)
        all_c_and_shell_quote_compat = 0;
    }

  if (len == 0 && quoting_style == shell_always_quoting_style
      && elide_outer_quotes)
    goto force_outer_quoting_style;





  if (quoting_style == shell_always_quoting_style && ! elide_outer_quotes
      && encountered_single_quote)
    {
      if (all_c_and_shell_quote_compat)
        return quotearg_buffer_restyled (buffer, orig_buffersize, arg, argsize,
                                         c_quoting_style,
                                         flags, quote_these_too,
                                         left_quote, right_quote);
      else if (! buffersize && orig_buffersize)
        {

          buffersize = orig_buffersize;
          len = 0;
          goto process_input;
        }
    }

  if (quote_string && !elide_outer_quotes)
    for (; *quote_string; quote_string++)
      do { if (len < buffersize) buffer[len] = (*quote_string); len++; } while (0);

  if (len < buffersize)
    buffer[len] = '\0';
  return len;

 force_outer_quoting_style:


  if (quoting_style == shell_always_quoting_style && backslash_escapes)
    quoting_style = shell_escape_always_quoting_style;
  return quotearg_buffer_restyled (buffer, buffersize, arg, argsize,
                                   quoting_style,
                                   flags & ~QA_ELIDE_OUTER_QUOTES, 0,
                                   left_quote, right_quote);
}
# 779 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c"
size_t
quotearg_buffer (char *buffer, size_t buffersize,
                 char const *arg, size_t argsize,
                 struct quoting_options const *o)
{
  struct quoting_options const *p = o ? o : &default_quoting_options;
  int e = errno;
  size_t r = quotearg_buffer_restyled (buffer, buffersize, arg, argsize,
                                       p->style, p->flags, p->quote_these_too,
                                       p->left_quote, p->right_quote);
  errno = e;
  return r;
}

char *
quotearg_alloc (char const *arg, size_t argsize,
                struct quoting_options const *o)
{
  return quotearg_alloc_mem (arg, argsize, 0, o);
}







char *
quotearg_alloc_mem (char const *arg, size_t argsize, size_t *size,
                    struct quoting_options const *o)
{
  struct quoting_options const *p = o ? o : &default_quoting_options;
  int e = errno;

  int flags = p->flags | (size ? 0 : QA_ELIDE_NULL_BYTES);
  size_t bufsize = quotearg_buffer_restyled (0, 0, arg, argsize, p->style,
                                             flags, p->quote_these_too,
                                             p->left_quote,
                                             p->right_quote) + 1;
  char *buf = xcharalloc (bufsize);
  quotearg_buffer_restyled (buf, bufsize, arg, argsize, p->style, flags,
                            p->quote_these_too,
                            p->left_quote, p->right_quote);
  errno = e;
  if (size)
    *size = bufsize - 1;
  return buf;
}


struct slotvec
{
  size_t size;
  char *val;
};



static char slot0[256];
static int nslots = 1;
static struct slotvec slotvec0 = {sizeof slot0, slot0};
static struct slotvec *slotvec = &slotvec0;

void
quotearg_free (void)
{
  struct slotvec *sv = slotvec;
  int i;
  for (i = 1; i < nslots; i++)
    free (sv[i].val);
  if (sv[0].val != slot0)
    {
      free (sv[0].val);
      slotvec0.size = sizeof slot0;
      slotvec0.val = slot0;
    }
  if (sv != &slotvec0)
    {
      free (sv);
      slotvec = &slotvec0;
    }
  nslots = 1;
}
# 872 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c"
static char *
quotearg_n_options (int n, char const *arg, size_t argsize,
                    struct quoting_options const *options)
{
  int e = errno;

  struct slotvec *sv = slotvec;

  int nslots_max = ((2147483647) < (PTRDIFF_MAX) ? (2147483647) : (PTRDIFF_MAX));
  if (! (0 <= n && n < nslots_max))
    abort ();

  if (nslots <= n)
    {
      bool preallocated = (sv == &slotvec0);
      idx_t new_nslots = nslots;

      slotvec = sv = xpalloc (preallocated ? 0 : sv, &new_nslots,
                              n - nslots + 1, nslots_max, sizeof *sv);
      if (preallocated)
        *sv = slotvec0;
      memset (sv + nslots, 0, (new_nslots - nslots) * sizeof *sv);
      nslots = new_nslots;
    }

  {
    size_t size = sv[n].size;
    char *val = sv[n].val;

    int flags = options->flags | QA_ELIDE_NULL_BYTES;
    size_t qsize = quotearg_buffer_restyled (val, size, arg, argsize,
                                             options->style, flags,
                                             options->quote_these_too,
                                             options->left_quote,
                                             options->right_quote);

    if (size <= qsize)
      {
        sv[n].size = size = qsize + 1;
        if (val != slot0)
          free (val);
        sv[n].val = val = xcharalloc (size);
        quotearg_buffer_restyled (val, size, arg, argsize, options->style,
                                  flags, options->quote_these_too,
                                  options->left_quote,
                                  options->right_quote);
      }

    errno = e;
    return val;
  }
}

char *
quotearg_n (int n, char const *arg)
{
  return quotearg_n_options (n, arg, ((size_t) -1), &default_quoting_options);
}

char *
quotearg_n_mem (int n, char const *arg, size_t argsize)
{
  return quotearg_n_options (n, arg, argsize, &default_quoting_options);
}

char *
quotearg (char const *arg)
{
  return quotearg_n (0, arg);
}

char *
quotearg_mem (char const *arg, size_t argsize)
{
  return quotearg_n_mem (0, arg, argsize);
}

char *
quotearg_n_style (int n, enum quoting_style s, char const *arg)
{
  struct quoting_options const o = quoting_options_from_style (s);
  return quotearg_n_options (n, arg, ((size_t) -1), &o);
}

char *
quotearg_n_style_mem (int n, enum quoting_style s,
                      char const *arg, size_t argsize)
{
  struct quoting_options const o = quoting_options_from_style (s);
  return quotearg_n_options (n, arg, argsize, &o);
}

char *
quotearg_style (enum quoting_style s, char const *arg)
{
  return quotearg_n_style (0, s, arg);
}

char *
quotearg_style_mem (enum quoting_style s, char const *arg, size_t argsize)
{
  return quotearg_n_style_mem (0, s, arg, argsize);
}

char *
quotearg_char_mem (char const *arg, size_t argsize, char ch)
{
  struct quoting_options options;
  options = default_quoting_options;
  set_char_quoting (&options, ch, 1);
  return quotearg_n_options (0, arg, argsize, &options);
}

char *
quotearg_char (char const *arg, char ch)
{
  return quotearg_char_mem (arg, ((size_t) -1), ch);
}

char *
quotearg_colon (char const *arg)
{
  return quotearg_char (arg, ':');
}

char *
quotearg_colon_mem (char const *arg, size_t argsize)
{
  return quotearg_char_mem (arg, argsize, ':');
}

char *
quotearg_n_style_colon (int n, enum quoting_style s, char const *arg)
{
  struct quoting_options options;
  options = quoting_options_from_style (s);
  set_char_quoting (&options, ':', 1);
  return quotearg_n_options (n, arg, ((size_t) -1), &options);
}

char *
quotearg_n_custom (int n, char const *left_quote,
                   char const *right_quote, char const *arg)
{
  return quotearg_n_custom_mem (n, left_quote, right_quote, arg,
                                ((size_t) -1));
}

char *
quotearg_n_custom_mem (int n, char const *left_quote,
                       char const *right_quote,
                       char const *arg, size_t argsize)
{
  struct quoting_options o = default_quoting_options;
  set_custom_quoting (&o, left_quote, right_quote);
  return quotearg_n_options (n, arg, argsize, &o);
}

char *
quotearg_custom (char const *left_quote, char const *right_quote,
                 char const *arg)
{
  return quotearg_n_custom (0, left_quote, right_quote, arg);
}

char *
quotearg_custom_mem (char const *left_quote, char const *right_quote,
                     char const *arg, size_t argsize)
{
  return quotearg_n_custom_mem (0, left_quote, right_quote, arg,
                                argsize);
}



struct quoting_options quote_quoting_options =
  {
    locale_quoting_style,
    0,
    { 0 },
    0, 0
  };

char const *
quote_n_mem (int n, char const *arg, size_t argsize)
{
  return quotearg_n_options (n, arg, argsize, &quote_quoting_options);
}

char const *
quote_mem (char const *arg, size_t argsize)
{
  return quote_n_mem (0, arg, argsize);
}

char const *
quote_n (int n, char const *arg)
{
  return quote_n_mem (n, arg, ((size_t) -1));
}

char const *
quote (char const *arg)
{
  return quote_n (0, arg);
}
# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c"
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c"
#pragma GCC diagnostic ignored "-Wsuggest-attribute=pure"


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
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h" 2
# 42 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
enum quoting_style
  {
# 55 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
    literal_quoting_style,
# 69 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
    shell_quoting_style,
# 84 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
    shell_always_quoting_style,
# 100 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
    shell_escape_quoting_style,
# 117 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
    shell_escape_always_quoting_style,
# 131 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
    c_quoting_style,
# 143 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
    c_maybe_quoting_style,
# 156 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
    escape_quoting_style,
# 182 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
    locale_quoting_style,
# 207 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
    clocale_quoting_style,
# 250 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
    custom_quoting_style
  };


enum quoting_flags
  {



    QA_ELIDE_NULL_BYTES = 0x01,
# 268 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
    QA_ELIDE_OUTER_QUOTES = 0x02,





    QA_SPLIT_TRIGRAPHS = 0x04
  };







extern char const *const quoting_style_args[];
extern enum quoting_style const quoting_style_vals[];

struct quoting_options;







struct quoting_options *clone_quoting_options (struct quoting_options *o)
 
  ;


enum quoting_style get_quoting_style (struct quoting_options const *o);



void set_quoting_style (struct quoting_options *o, enum quoting_style s);
# 312 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
int set_char_quoting (struct quoting_options *o, char c, int i);





int set_quoting_flags (struct quoting_options *o, int i);
# 329 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
void set_custom_quoting (struct quoting_options *o,
                         char const *left_quote,
                         char const *right_quote);
# 344 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
size_t quotearg_buffer (char * buffer, size_t buffersize,
                        char const *arg, size_t argsize,
                        struct quoting_options const *o);




char *quotearg_alloc (char const *arg, size_t argsize,
                      struct quoting_options const *o)
 
  ;







char *quotearg_alloc_mem (char const *arg, size_t argsize,
                          size_t *size, struct quoting_options const *o)
 
  ;
# 374 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.h"
char *quotearg_n (int n, char const *arg);


char *quotearg (char const *arg);




char *quotearg_n_mem (int n, char const *arg, size_t argsize);


char *quotearg_mem (char const *arg, size_t argsize);




char *quotearg_n_style (int n, enum quoting_style s, char const *arg);




char *quotearg_n_style_mem (int n, enum quoting_style s,
                            char const *arg, size_t argsize);


char *quotearg_style (enum quoting_style s, char const *arg);


char *quotearg_style_mem (enum quoting_style s,
                          char const *arg, size_t argsize);



char *quotearg_char (char const *arg, char ch);


char *quotearg_char_mem (char const *arg, size_t argsize, char ch);


char *quotearg_colon (char const *arg);


char *quotearg_colon_mem (char const *arg, size_t argsize);


char *quotearg_n_style_colon (int n, enum quoting_style s, char const *arg);





char *quotearg_n_custom (int n, char const *left_quote,
                         char const *right_quote, char const *arg);



char *quotearg_n_custom_mem (int n, char const *left_quote,
                             char const *right_quote,
                             char const *arg, size_t argsize);


char *quotearg_custom (char const *left_quote, char const *right_quote,
                       char const *arg);



char *quotearg_custom_mem (char const *left_quote,
                           char const *right_quote,
                           char const *arg, size_t argsize);


void quotearg_free (void);
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quote.h" 1
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quote.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quote.h" 2
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quote.h"
extern struct quoting_options quote_quoting_options;





char const *quote_n_mem (int n, char const *arg, size_t argsize);




char const *quote_mem (char const *arg, size_t argsize);



char const *quote_n (int n, char const *arg);



char const *quote (char const *arg);
# 31 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/attribute.h" 1
# 33 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/minmax.h" 1
# 39 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/minmax.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/param.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/param.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/param.h" 2
# 40 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/minmax.h" 2
# 34 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2
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





inline void *xnrealloc (void *p, size_t n, size_t s)
  ;
inline void *
xnrealloc (void *p, size_t n, size_t s)
{
  return xreallocarray (p, n, s);
}




char *xcharalloc (size_t n)
 
  ;
# 213 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xalloc.h"

# 35 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c-strcaseeq.h" 1
# 19 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c-strcaseeq.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c-strcase.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c-strcase.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c-strcase.h" 2
# 47 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c-strcase.h"
extern int c_strcasecmp (const char *s1, const char *s2) ;




extern int c_strncasecmp (const char *s1, const char *s2, size_t n)
  ;
# 20 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c-strcaseeq.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c-ctype.h" 1
# 31 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c-ctype.h"

# 168 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c-ctype.h"
inline bool
c_isalnum (int c)
{
  switch (c)
    {
    case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
    case 'a' + (0): case 'b' + (0): case 'c' + (0): case 'd' + (0): case 'e' + (0): case 'f' + (0): case 'g' + (0): case 'h' + (0): case 'i' + (0): case 'j' + (0): case 'k' + (0): case 'l' + (0): case 'm' + (0): case 'n' + (0): case 'o' + (0): case 'p' + (0): case 'q' + (0): case 'r' + (0): case 's' + (0): case 't' + (0): case 'u' + (0): case 'v' + (0): case 'w' + (0): case 'x' + (0): case 'y' + (0): case 'z' + (0):
    case 'a' + ('A' - 'a'): case 'b' + ('A' - 'a'): case 'c' + ('A' - 'a'): case 'd' + ('A' - 'a'): case 'e' + ('A' - 'a'): case 'f' + ('A' - 'a'): case 'g' + ('A' - 'a'): case 'h' + ('A' - 'a'): case 'i' + ('A' - 'a'): case 'j' + ('A' - 'a'): case 'k' + ('A' - 'a'): case 'l' + ('A' - 'a'): case 'm' + ('A' - 'a'): case 'n' + ('A' - 'a'): case 'o' + ('A' - 'a'): case 'p' + ('A' - 'a'): case 'q' + ('A' - 'a'): case 'r' + ('A' - 'a'): case 's' + ('A' - 'a'): case 't' + ('A' - 'a'): case 'u' + ('A' - 'a'): case 'v' + ('A' - 'a'): case 'w' + ('A' - 'a'): case 'x' + ('A' - 'a'): case 'y' + ('A' - 'a'): case 'z' + ('A' - 'a'):
      return 1;
    default:
      return 0;
    }
}

inline bool
c_isalpha (int c)
{
  switch (c)
    {
    case 'a' + (0): case 'b' + (0): case 'c' + (0): case 'd' + (0): case 'e' + (0): case 'f' + (0): case 'g' + (0): case 'h' + (0): case 'i' + (0): case 'j' + (0): case 'k' + (0): case 'l' + (0): case 'm' + (0): case 'n' + (0): case 'o' + (0): case 'p' + (0): case 'q' + (0): case 'r' + (0): case 's' + (0): case 't' + (0): case 'u' + (0): case 'v' + (0): case 'w' + (0): case 'x' + (0): case 'y' + (0): case 'z' + (0):
    case 'a' + ('A' - 'a'): case 'b' + ('A' - 'a'): case 'c' + ('A' - 'a'): case 'd' + ('A' - 'a'): case 'e' + ('A' - 'a'): case 'f' + ('A' - 'a'): case 'g' + ('A' - 'a'): case 'h' + ('A' - 'a'): case 'i' + ('A' - 'a'): case 'j' + ('A' - 'a'): case 'k' + ('A' - 'a'): case 'l' + ('A' - 'a'): case 'm' + ('A' - 'a'): case 'n' + ('A' - 'a'): case 'o' + ('A' - 'a'): case 'p' + ('A' - 'a'): case 'q' + ('A' - 'a'): case 'r' + ('A' - 'a'): case 's' + ('A' - 'a'): case 't' + ('A' - 'a'): case 'u' + ('A' - 'a'): case 'v' + ('A' - 'a'): case 'w' + ('A' - 'a'): case 'x' + ('A' - 'a'): case 'y' + ('A' - 'a'): case 'z' + ('A' - 'a'):
      return 1;
    default:
      return 0;
    }
}



inline bool
c_isascii (int c)
{
  switch (c)
    {
    case ' ':
    case '\a': case '\b': case '\f': case '\n': case '\r': case '\t': case '\v': case '\x00': case '\x01': case '\x02': case '\x03': case '\x04': case '\x05': case '\x06': case '\x0e': case '\x0f': case '\x10': case '\x11': case '\x12': case '\x13': case '\x14': case '\x15': case '\x16': case '\x17': case '\x18': case '\x19': case '\x1a': case '\x1b': case '\x1c': case '\x1d': case '\x1e': case '\x1f': case '\x7f':
    case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
    case 'a' + (0): case 'b' + (0): case 'c' + (0): case 'd' + (0): case 'e' + (0): case 'f' + (0): case 'g' + (0): case 'h' + (0): case 'i' + (0): case 'j' + (0): case 'k' + (0): case 'l' + (0): case 'm' + (0): case 'n' + (0): case 'o' + (0): case 'p' + (0): case 'q' + (0): case 'r' + (0): case 's' + (0): case 't' + (0): case 'u' + (0): case 'v' + (0): case 'w' + (0): case 'x' + (0): case 'y' + (0): case 'z' + (0):
    case '!': case '"': case '#': case '$': case '%': case '&': case '\'': case '(': case ')': case '*': case '+': case ',': case '-': case '.': case '/': case ':': case ';': case '<': case '=': case '>': case '?': case '@': case '[': case '\\': case ']': case '^': case '_': case '`': case '{': case '|': case '}': case '~':
    case 'a' + ('A' - 'a'): case 'b' + ('A' - 'a'): case 'c' + ('A' - 'a'): case 'd' + ('A' - 'a'): case 'e' + ('A' - 'a'): case 'f' + ('A' - 'a'): case 'g' + ('A' - 'a'): case 'h' + ('A' - 'a'): case 'i' + ('A' - 'a'): case 'j' + ('A' - 'a'): case 'k' + ('A' - 'a'): case 'l' + ('A' - 'a'): case 'm' + ('A' - 'a'): case 'n' + ('A' - 'a'): case 'o' + ('A' - 'a'): case 'p' + ('A' - 'a'): case 'q' + ('A' - 'a'): case 'r' + ('A' - 'a'): case 's' + ('A' - 'a'): case 't' + ('A' - 'a'): case 'u' + ('A' - 'a'): case 'v' + ('A' - 'a'): case 'w' + ('A' - 'a'): case 'x' + ('A' - 'a'): case 'y' + ('A' - 'a'): case 'z' + ('A' - 'a'):
      return 1;
    default:
      return 0;
    }
}

inline bool
c_isblank (int c)
{
  return c == ' ' || c == '\t';
}

inline bool
c_iscntrl (int c)
{
  switch (c)
    {
    case '\a': case '\b': case '\f': case '\n': case '\r': case '\t': case '\v': case '\x00': case '\x01': case '\x02': case '\x03': case '\x04': case '\x05': case '\x06': case '\x0e': case '\x0f': case '\x10': case '\x11': case '\x12': case '\x13': case '\x14': case '\x15': case '\x16': case '\x17': case '\x18': case '\x19': case '\x1a': case '\x1b': case '\x1c': case '\x1d': case '\x1e': case '\x1f': case '\x7f':
      return 1;
    default:
      return 0;
    }
}

inline bool
c_isdigit (int c)
{
  switch (c)
    {
    case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
      return 1;
    default:
      return 0;
    }
}

inline bool
c_isgraph (int c)
{
  switch (c)
    {
    case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
    case 'a' + (0): case 'b' + (0): case 'c' + (0): case 'd' + (0): case 'e' + (0): case 'f' + (0): case 'g' + (0): case 'h' + (0): case 'i' + (0): case 'j' + (0): case 'k' + (0): case 'l' + (0): case 'm' + (0): case 'n' + (0): case 'o' + (0): case 'p' + (0): case 'q' + (0): case 'r' + (0): case 's' + (0): case 't' + (0): case 'u' + (0): case 'v' + (0): case 'w' + (0): case 'x' + (0): case 'y' + (0): case 'z' + (0):
    case '!': case '"': case '#': case '$': case '%': case '&': case '\'': case '(': case ')': case '*': case '+': case ',': case '-': case '.': case '/': case ':': case ';': case '<': case '=': case '>': case '?': case '@': case '[': case '\\': case ']': case '^': case '_': case '`': case '{': case '|': case '}': case '~':
    case 'a' + ('A' - 'a'): case 'b' + ('A' - 'a'): case 'c' + ('A' - 'a'): case 'd' + ('A' - 'a'): case 'e' + ('A' - 'a'): case 'f' + ('A' - 'a'): case 'g' + ('A' - 'a'): case 'h' + ('A' - 'a'): case 'i' + ('A' - 'a'): case 'j' + ('A' - 'a'): case 'k' + ('A' - 'a'): case 'l' + ('A' - 'a'): case 'm' + ('A' - 'a'): case 'n' + ('A' - 'a'): case 'o' + ('A' - 'a'): case 'p' + ('A' - 'a'): case 'q' + ('A' - 'a'): case 'r' + ('A' - 'a'): case 's' + ('A' - 'a'): case 't' + ('A' - 'a'): case 'u' + ('A' - 'a'): case 'v' + ('A' - 'a'): case 'w' + ('A' - 'a'): case 'x' + ('A' - 'a'): case 'y' + ('A' - 'a'): case 'z' + ('A' - 'a'):
      return 1;
    default:
      return 0;
    }
}

inline bool
c_islower (int c)
{
  switch (c)
    {
    case 'a' + (0): case 'b' + (0): case 'c' + (0): case 'd' + (0): case 'e' + (0): case 'f' + (0): case 'g' + (0): case 'h' + (0): case 'i' + (0): case 'j' + (0): case 'k' + (0): case 'l' + (0): case 'm' + (0): case 'n' + (0): case 'o' + (0): case 'p' + (0): case 'q' + (0): case 'r' + (0): case 's' + (0): case 't' + (0): case 'u' + (0): case 'v' + (0): case 'w' + (0): case 'x' + (0): case 'y' + (0): case 'z' + (0):
      return 1;
    default:
      return 0;
    }
}

inline bool
c_isprint (int c)
{
  switch (c)
    {
    case ' ':
    case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
    case 'a' + (0): case 'b' + (0): case 'c' + (0): case 'd' + (0): case 'e' + (0): case 'f' + (0): case 'g' + (0): case 'h' + (0): case 'i' + (0): case 'j' + (0): case 'k' + (0): case 'l' + (0): case 'm' + (0): case 'n' + (0): case 'o' + (0): case 'p' + (0): case 'q' + (0): case 'r' + (0): case 's' + (0): case 't' + (0): case 'u' + (0): case 'v' + (0): case 'w' + (0): case 'x' + (0): case 'y' + (0): case 'z' + (0):
    case '!': case '"': case '#': case '$': case '%': case '&': case '\'': case '(': case ')': case '*': case '+': case ',': case '-': case '.': case '/': case ':': case ';': case '<': case '=': case '>': case '?': case '@': case '[': case '\\': case ']': case '^': case '_': case '`': case '{': case '|': case '}': case '~':
    case 'a' + ('A' - 'a'): case 'b' + ('A' - 'a'): case 'c' + ('A' - 'a'): case 'd' + ('A' - 'a'): case 'e' + ('A' - 'a'): case 'f' + ('A' - 'a'): case 'g' + ('A' - 'a'): case 'h' + ('A' - 'a'): case 'i' + ('A' - 'a'): case 'j' + ('A' - 'a'): case 'k' + ('A' - 'a'): case 'l' + ('A' - 'a'): case 'm' + ('A' - 'a'): case 'n' + ('A' - 'a'): case 'o' + ('A' - 'a'): case 'p' + ('A' - 'a'): case 'q' + ('A' - 'a'): case 'r' + ('A' - 'a'): case 's' + ('A' - 'a'): case 't' + ('A' - 'a'): case 'u' + ('A' - 'a'): case 'v' + ('A' - 'a'): case 'w' + ('A' - 'a'): case 'x' + ('A' - 'a'): case 'y' + ('A' - 'a'): case 'z' + ('A' - 'a'):
      return 1;
    default:
      return 0;
    }
}

inline bool
c_ispunct (int c)
{
  switch (c)
    {
    case '!': case '"': case '#': case '$': case '%': case '&': case '\'': case '(': case ')': case '*': case '+': case ',': case '-': case '.': case '/': case ':': case ';': case '<': case '=': case '>': case '?': case '@': case '[': case '\\': case ']': case '^': case '_': case '`': case '{': case '|': case '}': case '~':
      return 1;
    default:
      return 0;
    }
}

inline bool
c_isspace (int c)
{
  switch (c)
    {
    case ' ': case '\t': case '\n': case '\v': case '\f': case '\r':
      return 1;
    default:
      return 0;
    }
}

inline bool
c_isupper (int c)
{
  switch (c)
    {
    case 'a' + ('A' - 'a'): case 'b' + ('A' - 'a'): case 'c' + ('A' - 'a'): case 'd' + ('A' - 'a'): case 'e' + ('A' - 'a'): case 'f' + ('A' - 'a'): case 'g' + ('A' - 'a'): case 'h' + ('A' - 'a'): case 'i' + ('A' - 'a'): case 'j' + ('A' - 'a'): case 'k' + ('A' - 'a'): case 'l' + ('A' - 'a'): case 'm' + ('A' - 'a'): case 'n' + ('A' - 'a'): case 'o' + ('A' - 'a'): case 'p' + ('A' - 'a'): case 'q' + ('A' - 'a'): case 'r' + ('A' - 'a'): case 's' + ('A' - 'a'): case 't' + ('A' - 'a'): case 'u' + ('A' - 'a'): case 'v' + ('A' - 'a'): case 'w' + ('A' - 'a'): case 'x' + ('A' - 'a'): case 'y' + ('A' - 'a'): case 'z' + ('A' - 'a'):
      return 1;
    default:
      return 0;
    }
}

inline bool
c_isxdigit (int c)
{
  switch (c)
    {
    case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
    case 'a' + (0): case 'b' + (0): case 'c' + (0): case 'd' + (0): case 'e' + (0): case 'f' + (0): case 'a' + ('A' - 'a'): case 'b' + ('A' - 'a'): case 'c' + ('A' - 'a'): case 'd' + ('A' - 'a'): case 'e' + ('A' - 'a'): case 'f' + ('A' - 'a'):
      return 1;
    default:
      return 0;
    }
}

inline int
c_tolower (int c)
{
  switch (c)
    {
    case 'a' + ('A' - 'a'): case 'b' + ('A' - 'a'): case 'c' + ('A' - 'a'): case 'd' + ('A' - 'a'): case 'e' + ('A' - 'a'): case 'f' + ('A' - 'a'): case 'g' + ('A' - 'a'): case 'h' + ('A' - 'a'): case 'i' + ('A' - 'a'): case 'j' + ('A' - 'a'): case 'k' + ('A' - 'a'): case 'l' + ('A' - 'a'): case 'm' + ('A' - 'a'): case 'n' + ('A' - 'a'): case 'o' + ('A' - 'a'): case 'p' + ('A' - 'a'): case 'q' + ('A' - 'a'): case 'r' + ('A' - 'a'): case 's' + ('A' - 'a'): case 't' + ('A' - 'a'): case 'u' + ('A' - 'a'): case 'v' + ('A' - 'a'): case 'w' + ('A' - 'a'): case 'x' + ('A' - 'a'): case 'y' + ('A' - 'a'): case 'z' + ('A' - 'a'):
      return c - 'A' + 'a';
    default:
      return c;
    }
}

inline int
c_toupper (int c)
{
  switch (c)
    {
    case 'a' + (0): case 'b' + (0): case 'c' + (0): case 'd' + (0): case 'e' + (0): case 'f' + (0): case 'g' + (0): case 'h' + (0): case 'i' + (0): case 'j' + (0): case 'k' + (0): case 'l' + (0): case 'm' + (0): case 'n' + (0): case 'o' + (0): case 'p' + (0): case 'q' + (0): case 'r' + (0): case 's' + (0): case 't' + (0): case 'u' + (0): case 'v' + (0): case 'w' + (0): case 'x' + (0): case 'y' + (0): case 'z' + (0):
      return c - 'a' + 'A';
    default:
      return c;
    }
}






# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/c-strcaseeq.h" 2
# 36 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/localcharset.h" 1
# 35 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/localcharset.h"
extern const char * locale_charset (void);
# 37 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/ctype.h" 1
# 39 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/errno.h" 1
# 40 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 1
# 41 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 42 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 43 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 44 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/uchar.h" 1
# 45 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/wchar.h" 1
# 46 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/gettext.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/gettext.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/libintl.h" 1
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/gettext.h" 2
# 141 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/gettext.h"
static const char *
pgettext_aux (const char *domain,
              const char *msg_ctxt_id, const char *msgid,
              int category)
{
  const char *translation = dcgettext (domain, msg_ctxt_id, category);
  if (translation == msg_ctxt_id)
    return msgid;
  else
    return translation;
}

static const char *
npgettext_aux (const char *domain,
               const char *msg_ctxt_id, const char *msgid,
               const char *msgid_plural, unsigned long int n,
               int category)
{
  const char *translation =
    dcngettext (domain, msg_ctxt_id, msgid_plural, n, category);
  if (translation == msg_ctxt_id || translation == msgid_plural)
    return (n == 1 ? msgid : msgid_plural);
  else
    return translation;
}





# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 172 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/gettext.h" 2
# 188 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/gettext.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 189 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/gettext.h" 2







static const char *
dcpgettext_expr (const char *domain,
                 const char *msgctxt, const char *msgid,
                 int category)
{
  size_t msgctxt_len = strlen (msgctxt) + 1;
  size_t msgid_len = strlen (msgid) + 1;
  const char *translation;



  char buf[1024];
  char *msg_ctxt_id =
    (msgctxt_len + msgid_len <= sizeof (buf)
     ? buf
     : (char *) malloc (msgctxt_len + msgid_len));
  if (msg_ctxt_id != 0)

    {
      int found_translation;
      memcpy (msg_ctxt_id, msgctxt, msgctxt_len - 1);
      msg_ctxt_id[msgctxt_len - 1] = '\004';
      memcpy (msg_ctxt_id + msgctxt_len, msgid, msgid_len);
      translation = dcgettext (domain, msg_ctxt_id, category);
      found_translation = (translation != msg_ctxt_id);

      if (msg_ctxt_id != buf)
        free (msg_ctxt_id);

      if (found_translation)
        return translation;
    }
  return msgid;
}






static const char *
dcnpgettext_expr (const char *domain,
                  const char *msgctxt, const char *msgid,
                  const char *msgid_plural, unsigned long int n,
                  int category)
{
  size_t msgctxt_len = strlen (msgctxt) + 1;
  size_t msgid_len = strlen (msgid) + 1;
  const char *translation;



  char buf[1024];
  char *msg_ctxt_id =
    (msgctxt_len + msgid_len <= sizeof (buf)
     ? buf
     : (char *) malloc (msgctxt_len + msgid_len));
  if (msg_ctxt_id != 0)

    {
      int found_translation;
      memcpy (msg_ctxt_id, msgctxt, msgctxt_len - 1);
      msg_ctxt_id[msgctxt_len - 1] = '\004';
      memcpy (msg_ctxt_id + msgctxt_len, msgid, msgid_len);
      translation = dcngettext (domain, msg_ctxt_id, msgid_plural, n, category);
      found_translation = !(translation == msg_ctxt_id || translation == msgid_plural);

      if (msg_ctxt_id != buf)
        free (msg_ctxt_id);

      if (found_translation)
        return translation;
    }
  return (n == 1 ? msgid : msgid_plural);
}
# 48 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c" 2
# 57 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c"
struct quoting_options
{

  enum quoting_style style;


  int flags;



  unsigned int quote_these_too[(255 / (sizeof (int) * 8)) + 1];


  char const *left_quote;


  char const *right_quote;
};


char const *const quoting_style_args[] =
{
  "literal",
  "shell",
  "shell-always",
  "shell-escape",
  "shell-escape-always",
  "c",
  "c-maybe",
  "escape",
  "locale",
  "clocale",
  0
};


enum quoting_style const quoting_style_vals[] =
{
  literal_quoting_style,
  shell_quoting_style,
  shell_always_quoting_style,
  shell_escape_quoting_style,
  shell_escape_always_quoting_style,
  c_quoting_style,
  c_maybe_quoting_style,
  escape_quoting_style,
  locale_quoting_style,
  clocale_quoting_style
};


static struct quoting_options default_quoting_options;




struct quoting_options *
clone_quoting_options (struct quoting_options *o)
{
  int e = errno;
  struct quoting_options *p = xmemdup (o ? o : &default_quoting_options,
                                       sizeof *o);
  errno = e;
  return p;
}


enum quoting_style
get_quoting_style (struct quoting_options const *o)
{
  return (o ? o : &default_quoting_options)->style;
}



void
set_quoting_style (struct quoting_options *o, enum quoting_style s)
{
  (o ? o : &default_quoting_options)->style = s;
}






int
set_char_quoting (struct quoting_options *o, char c, int i)
{
  unsigned char uc = c;
  unsigned int *p =
    (o ? o : &default_quoting_options)->quote_these_too + uc / (sizeof (int) * 8);
  int shift = uc % (sizeof (int) * 8);
  int r = (*p >> shift) & 1;
  *p ^= ((i & 1) ^ r) << shift;
  return r;
}





int
set_quoting_flags (struct quoting_options *o, int i)
{
  int r;
  if (!o)
    o = &default_quoting_options;
  r = o->flags;
  o->flags = i;
  return r;
}

void
set_custom_quoting (struct quoting_options *o,
                    char const *left_quote, char const *right_quote)
{
  if (!o)
    o = &default_quoting_options;
  o->style = custom_quoting_style;
  if (!left_quote || !right_quote)
    abort ();
  o->left_quote = left_quote;
  o->right_quote = right_quote;
}


static struct quoting_options
quoting_options_from_style (enum quoting_style style)
{
  struct quoting_options o = { literal_quoting_style, 0, { 0 }, 0, 0 };
  if (style == custom_quoting_style)
    abort ();
  o.style = style;
  return o;
}





static char const *
gettext_quote (char const *msgid, enum quoting_style s)
{
  char const *translation = gettext (msgid);
  char const *locale_code;

  if (translation != msgid)
    return translation;
# 225 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c"
  locale_code = locale_charset ();
  if ((c_strcasecmp (locale_code, "UTF-8") == 0))
    return msgid[0] == '`' ? "\xe2\x80\x98": "\xe2\x80\x99";
  if ((c_strcasecmp (locale_code, "GB18030") == 0))
    return msgid[0] == '`' ? "\xa1\ae": "\xa1\xaf";

  return (s == clocale_quoting_style ? "\"" : "'");
}
# 247 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c"
static size_t
quotearg_buffer_restyled (char *buffer, size_t buffersize,
                          char const *arg, size_t argsize,
                          enum quoting_style quoting_style, int flags,
                          unsigned int const *quote_these_too,
                          char const *left_quote,
                          char const *right_quote)
{
  size_t i;
  size_t len = 0;
  size_t orig_buffersize = 0;
  char const *quote_string = 0;
  size_t quote_string_len = 0;
  bool backslash_escapes = 0;
  bool unibyte_locale = MB_CUR_MAX == 1;
  bool elide_outer_quotes = (flags & QA_ELIDE_OUTER_QUOTES) != 0;
  bool encountered_single_quote = 0;
  bool all_c_and_shell_quote_compat = 1;
# 305 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c"
 process_input: ;
  bool pending_shell_escape_end = 0;

  switch (quoting_style)
    {
    case c_maybe_quoting_style:
      quoting_style = c_quoting_style;
      elide_outer_quotes = 1;
      ;
    case c_quoting_style:
      if (!elide_outer_quotes)
        do { if (len < buffersize) buffer[len] = ('"'); len++; } while (0);
      backslash_escapes = 1;
      quote_string = "\"";
      quote_string_len = 1;
      break;

    case escape_quoting_style:
      backslash_escapes = 1;
      elide_outer_quotes = 0;
      break;

    case locale_quoting_style:
    case clocale_quoting_style:
    case custom_quoting_style:
      {
        if (quoting_style != custom_quoting_style)
          {
# 354 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c"
            left_quote = gettext_quote ("`", quoting_style);
            right_quote = gettext_quote ("'", quoting_style);
          }
        if (!elide_outer_quotes)
          for (quote_string = left_quote; *quote_string; quote_string++)
            do { if (len < buffersize) buffer[len] = (*quote_string); len++; } while (0);
        backslash_escapes = 1;
        quote_string = right_quote;
        quote_string_len = strlen (quote_string);
      }
      break;

    case shell_escape_quoting_style:
      backslash_escapes = 1;
      ;
    case shell_quoting_style:
      elide_outer_quotes = 1;
      ;
    case shell_escape_always_quoting_style:
      if (!elide_outer_quotes)
        backslash_escapes = 1;
      ;
    case shell_always_quoting_style:
      quoting_style = shell_always_quoting_style;
      if (!elide_outer_quotes)
        do { if (len < buffersize) buffer[len] = ('\''); len++; } while (0);
      quote_string = "'";
      quote_string_len = 1;
      break;

    case literal_quoting_style:
      elide_outer_quotes = 0;
      break;

    default:
      abort ();
    }

  for (i = 0; ! (argsize == ((size_t) -1) ? arg[i] == '\0' : i == argsize); i++)
    {
      unsigned char c;
      unsigned char esc;
      bool is_right_quote = 0;
      bool escaping = 0;
      bool c_and_shell_quote_compat = 0;

      if (backslash_escapes
          && quoting_style != shell_always_quoting_style
          && quote_string_len
          && (i + quote_string_len
              <= (argsize == ((size_t) -1) && 1 < quote_string_len



                  ? (argsize = strlen (arg)) : argsize))
          && memcmp (arg + i, quote_string, quote_string_len) == 0)
        {
          if (elide_outer_quotes)
            goto force_outer_quoting_style;
          is_right_quote = 1;
        }

      c = arg[i];
      switch (c)
        {
        case '\0':
          if (backslash_escapes)
            {
              do { if (elide_outer_quotes) goto force_outer_quoting_style; escaping = 1; if (quoting_style == shell_always_quoting_style && ! pending_shell_escape_end) { do { if (len < buffersize) buffer[len] = ('\''); len++; } while (0); do { if (len < buffersize) buffer[len] = ('$'); len++; } while (0); do { if (len < buffersize) buffer[len] = ('\''); len++; } while (0); pending_shell_escape_end = 1; } do { if (len < buffersize) buffer[len] = ('\\'); len++; } while (0); } while (0);






              if (quoting_style != shell_always_quoting_style
                  && i + 1 < argsize && '0' <= arg[i + 1] && arg[i + 1] <= '9')
                {
                  do { if (len < buffersize) buffer[len] = ('0'); len++; } while (0);
                  do { if (len < buffersize) buffer[len] = ('0'); len++; } while (0);
                }
              c = '0';




            }
          else if (flags & QA_ELIDE_NULL_BYTES)
            continue;
          break;

        case '?':
          switch (quoting_style)
            {
            case shell_always_quoting_style:
              if (elide_outer_quotes)
                goto force_outer_quoting_style;
              break;

            case c_quoting_style:
              if ((flags & QA_SPLIT_TRIGRAPHS)
                  && i + 2 < argsize && arg[i + 1] == '?')
                switch (arg[i + 2])
                  {
                  case '!': case '\'':
                  case '(': case ')': case '-': case '/':
                  case '<': case '=': case '>':


                    if (elide_outer_quotes)
                      goto force_outer_quoting_style;
                    c = arg[i + 2];
                    i += 2;
                    do { if (len < buffersize) buffer[len] = ('?'); len++; } while (0);
                    do { if (len < buffersize) buffer[len] = ('"'); len++; } while (0);
                    do { if (len < buffersize) buffer[len] = ('"'); len++; } while (0);
                    do { if (len < buffersize) buffer[len] = ('?'); len++; } while (0);
                    break;

                  default:
                    break;
                  }
              break;

            default:
              break;
            }
          break;

        case '\a': esc = 'a'; goto c_escape;
        case '\b': esc = 'b'; goto c_escape;
        case '\f': esc = 'f'; goto c_escape;
        case '\n': esc = 'n'; goto c_and_shell_escape;
        case '\r': esc = 'r'; goto c_and_shell_escape;
        case '\t': esc = 't'; goto c_and_shell_escape;
        case '\v': esc = 'v'; goto c_escape;
        case '\\': esc = c;

          if (quoting_style == shell_always_quoting_style)
            {
              if (elide_outer_quotes)
                goto force_outer_quoting_style;
              goto store_c;
            }



          if (backslash_escapes && elide_outer_quotes && quote_string_len)
            goto store_c;

        c_and_shell_escape:
          if (quoting_style == shell_always_quoting_style
              && elide_outer_quotes)
            goto force_outer_quoting_style;

        c_escape:
          if (backslash_escapes)
            {
              c = esc;
              goto store_escape;
            }
          break;

        case '{': case '}':
          if (! (argsize == ((size_t) -1) ? arg[1] == '\0' : argsize == 1))
            break;
          ;
        case '#': case '~':
          if (i != 0)
            break;
          ;
        case ' ':
          c_and_shell_quote_compat = 1;
          ;
        case '!':
        case '"': case '$': case '&':
        case '(': case ')': case '*': case ';':
        case '<':
        case '=':
        case '>': case '[':
        case '^':
        case '`': case '|':

          if (quoting_style == shell_always_quoting_style
              && elide_outer_quotes)
            goto force_outer_quoting_style;
          break;

        case '\'':
          encountered_single_quote = 1;
          c_and_shell_quote_compat = 1;
          if (quoting_style == shell_always_quoting_style)
            {
              if (elide_outer_quotes)
                goto force_outer_quoting_style;

              if (buffersize && ! orig_buffersize)
                {



                  orig_buffersize = buffersize;
                  buffersize = 0;
                }

              do { if (len < buffersize) buffer[len] = ('\''); len++; } while (0);
              do { if (len < buffersize) buffer[len] = ('\\'); len++; } while (0);
              do { if (len < buffersize) buffer[len] = ('\''); len++; } while (0);
              pending_shell_escape_end = 0;
            }
          break;

        case '%': case '+': case ',': case '-': case '.': case '/':
        case '0': case '1': case '2': case '3': case '4': case '5':
        case '6': case '7': case '8': case '9': case ':':
        case 'A': case 'B': case 'C': case 'D': case 'E': case 'F':
        case 'G': case 'H': case 'I': case 'J': case 'K': case 'L':
        case 'M': case 'N': case 'O': case 'P': case 'Q': case 'R':
        case 'S': case 'T': case 'U': case 'V': case 'W': case 'X':
        case 'Y': case 'Z': case ']': case '_': case 'a': case 'b':
        case 'c': case 'd': case 'e': case 'f': case 'g': case 'h':
        case 'i': case 'j': case 'k': case 'l': case 'm': case 'n':
        case 'o': case 'p': case 'q': case 'r': case 's': case 't':
        case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
# 588 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c"
          c_and_shell_quote_compat = 1;
          break;

        default:





          {

            size_t m;

            bool printable;

            if (unibyte_locale)
              {
                m = 1;
                printable = isprint (c) != 0;
              }
            else
              {
                mbstate_t mbstate;
                mbszero (&mbstate);

                m = 0;
                printable = 1;
                if (argsize == ((size_t) -1))
                  argsize = strlen (arg);

                for (;;)
                  {
                    char32_t w;
                    size_t bytes = mbrtoc32 (&w, &arg[i + m],
                                             argsize - (i + m), &mbstate);
                    if (bytes == 0)
                      break;
                    else if (bytes == (size_t) -1)
                      {
                        printable = 0;
                        break;
                      }
                    else if (bytes == (size_t) -2)
                      {
                        printable = 0;
                        while (i + m < argsize && arg[i + m])
                          m++;
                        break;
                      }
                    else
                      {
# 647 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c"
                        if ('[' == 0x5b && elide_outer_quotes
                            && quoting_style == shell_always_quoting_style)
                          {
                            size_t j;
                            for (j = 1; j < bytes; j++)
                              switch (arg[i + m + j])
                                {
                                case '[': case '\\': case '^':
                                case '`': case '|':
                                  goto force_outer_quoting_style;

                                default:
                                  break;
                                }
                          }

                        if (! c32isprint (w))
                          printable = 0;
                        m += bytes;
                      }



                      break;
                  }
              }

            c_and_shell_quote_compat = printable;

            if (1 < m || (backslash_escapes && ! printable))
              {


                size_t ilim = i + m;

                for (;;)
                  {
                    if (backslash_escapes && ! printable)
                      {
                        do { if (elide_outer_quotes) goto force_outer_quoting_style; escaping = 1; if (quoting_style == shell_always_quoting_style && ! pending_shell_escape_end) { do { if (len < buffersize) buffer[len] = ('\''); len++; } while (0); do { if (len < buffersize) buffer[len] = ('$'); len++; } while (0); do { if (len < buffersize) buffer[len] = ('\''); len++; } while (0); pending_shell_escape_end = 1; } do { if (len < buffersize) buffer[len] = ('\\'); len++; } while (0); } while (0);
                        do { if (len < buffersize) buffer[len] = ('0' + (c >> 6)); len++; } while (0);
                        do { if (len < buffersize) buffer[len] = ('0' + ((c >> 3) & 7)); len++; } while (0);
                        c = '0' + (c & 7);
                      }
                    else if (is_right_quote)
                      {
                        do { if (len < buffersize) buffer[len] = ('\\'); len++; } while (0);
                        is_right_quote = 0;
                      }
                    if (ilim <= i + 1)
                      break;
                    do { if (pending_shell_escape_end && ! escaping) { do { if (len < buffersize) buffer[len] = ('\''); len++; } while (0); do { if (len < buffersize) buffer[len] = ('\''); len++; } while (0); pending_shell_escape_end = 0; } } while (0);
                    do { if (len < buffersize) buffer[len] = (c); len++; } while (0);
                    c = arg[++i];
                  }

                goto store_c;
              }
          }
        }

      if (! (((backslash_escapes && quoting_style != shell_always_quoting_style)
              || elide_outer_quotes)
             && quote_these_too
             && quote_these_too[c / (sizeof (int) * 8)] >> (c % (sizeof (int) * 8)) & 1)
          && !is_right_quote)
        goto store_c;

    store_escape:
      do { if (elide_outer_quotes) goto force_outer_quoting_style; escaping = 1; if (quoting_style == shell_always_quoting_style && ! pending_shell_escape_end) { do { if (len < buffersize) buffer[len] = ('\''); len++; } while (0); do { if (len < buffersize) buffer[len] = ('$'); len++; } while (0); do { if (len < buffersize) buffer[len] = ('\''); len++; } while (0); pending_shell_escape_end = 1; } do { if (len < buffersize) buffer[len] = ('\\'); len++; } while (0); } while (0);

    store_c:
      do { if (pending_shell_escape_end && ! escaping) { do { if (len < buffersize) buffer[len] = ('\''); len++; } while (0); do { if (len < buffersize) buffer[len] = ('\''); len++; } while (0); pending_shell_escape_end = 0; } } while (0);
      do { if (len < buffersize) buffer[len] = (c); len++; } while (0);

      if (! c_and_shell_quote_compat)
        all_c_and_shell_quote_compat = 0;
    }

  if (len == 0 && quoting_style == shell_always_quoting_style
      && elide_outer_quotes)
    goto force_outer_quoting_style;





  if (quoting_style == shell_always_quoting_style && ! elide_outer_quotes
      && encountered_single_quote)
    {
      if (all_c_and_shell_quote_compat)
        return quotearg_buffer_restyled (buffer, orig_buffersize, arg, argsize,
                                         c_quoting_style,
                                         flags, quote_these_too,
                                         left_quote, right_quote);
      else if (! buffersize && orig_buffersize)
        {

          buffersize = orig_buffersize;
          len = 0;
          goto process_input;
        }
    }

  if (quote_string && !elide_outer_quotes)
    for (; *quote_string; quote_string++)
      do { if (len < buffersize) buffer[len] = (*quote_string); len++; } while (0);

  if (len < buffersize)
    buffer[len] = '\0';
  return len;

 force_outer_quoting_style:


  if (quoting_style == shell_always_quoting_style && backslash_escapes)
    quoting_style = shell_escape_always_quoting_style;
  return quotearg_buffer_restyled (buffer, buffersize, arg, argsize,
                                   quoting_style,
                                   flags & ~QA_ELIDE_OUTER_QUOTES, 0,
                                   left_quote, right_quote);
}
# 779 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c"
size_t
quotearg_buffer (char *buffer, size_t buffersize,
                 char const *arg, size_t argsize,
                 struct quoting_options const *o)
{
  struct quoting_options const *p = o ? o : &default_quoting_options;
  int e = errno;
  size_t r = quotearg_buffer_restyled (buffer, buffersize, arg, argsize,
                                       p->style, p->flags, p->quote_these_too,
                                       p->left_quote, p->right_quote);
  errno = e;
  return r;
}

char *
quotearg_alloc (char const *arg, size_t argsize,
                struct quoting_options const *o)
{
  return quotearg_alloc_mem (arg, argsize, 0, o);
}







char *
quotearg_alloc_mem (char const *arg, size_t argsize, size_t *size,
                    struct quoting_options const *o)
{
  struct quoting_options const *p = o ? o : &default_quoting_options;
  int e = errno;

  int flags = p->flags | (size ? 0 : QA_ELIDE_NULL_BYTES);
  size_t bufsize = quotearg_buffer_restyled (0, 0, arg, argsize, p->style,
                                             flags, p->quote_these_too,
                                             p->left_quote,
                                             p->right_quote) + 1;
  char *buf = xcharalloc (bufsize);
  quotearg_buffer_restyled (buf, bufsize, arg, argsize, p->style, flags,
                            p->quote_these_too,
                            p->left_quote, p->right_quote);
  errno = e;
  if (size)
    *size = bufsize - 1;
  return buf;
}


struct slotvec
{
  size_t size;
  char *val;
};



static char slot0[256];
static int nslots = 1;
static struct slotvec slotvec0 = {sizeof slot0, slot0};
static struct slotvec *slotvec = &slotvec0;

void
quotearg_free (void)
{
  struct slotvec *sv = slotvec;
  int i;
  for (i = 1; i < nslots; i++)
    free (sv[i].val);
  if (sv[0].val != slot0)
    {
      free (sv[0].val);
      slotvec0.size = sizeof slot0;
      slotvec0.val = slot0;
    }
  if (sv != &slotvec0)
    {
      free (sv);
      slotvec = &slotvec0;
    }
  nslots = 1;
}
# 872 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/quotearg.c"
static char *
quotearg_n_options (int n, char const *arg, size_t argsize,
                    struct quoting_options const *options)
{
  int e = errno;

  struct slotvec *sv = slotvec;

  int nslots_max = ((2147483647) < (PTRDIFF_MAX) ? (2147483647) : (PTRDIFF_MAX));
  if (! (0 <= n && n < nslots_max))
    abort ();

  if (nslots <= n)
    {
      bool preallocated = (sv == &slotvec0);
      idx_t new_nslots = nslots;

      slotvec = sv = xpalloc (preallocated ? 0 : sv, &new_nslots,
                              n - nslots + 1, nslots_max, sizeof *sv);
      if (preallocated)
        *sv = slotvec0;
      memset (sv + nslots, 0, (new_nslots - nslots) * sizeof *sv);
      nslots = new_nslots;
    }

  {
    size_t size = sv[n].size;
    char *val = sv[n].val;

    int flags = options->flags | QA_ELIDE_NULL_BYTES;
    size_t qsize = quotearg_buffer_restyled (val, size, arg, argsize,
                                             options->style, flags,
                                             options->quote_these_too,
                                             options->left_quote,
                                             options->right_quote);

    if (size <= qsize)
      {
        sv[n].size = size = qsize + 1;
        if (val != slot0)
          free (val);
        sv[n].val = val = xcharalloc (size);
        quotearg_buffer_restyled (val, size, arg, argsize, options->style,
                                  flags, options->quote_these_too,
                                  options->left_quote,
                                  options->right_quote);
      }

    errno = e;
    return val;
  }
}

char *
quotearg_n (int n, char const *arg)
{
  return quotearg_n_options (n, arg, ((size_t) -1), &default_quoting_options);
}

char *
quotearg_n_mem (int n, char const *arg, size_t argsize)
{
  return quotearg_n_options (n, arg, argsize, &default_quoting_options);
}

char *
quotearg (char const *arg)
{
  return quotearg_n (0, arg);
}

char *
quotearg_mem (char const *arg, size_t argsize)
{
  return quotearg_n_mem (0, arg, argsize);
}

char *
quotearg_n_style (int n, enum quoting_style s, char const *arg)
{
  struct quoting_options const o = quoting_options_from_style (s);
  return quotearg_n_options (n, arg, ((size_t) -1), &o);
}

char *
quotearg_n_style_mem (int n, enum quoting_style s,
                      char const *arg, size_t argsize)
{
  struct quoting_options const o = quoting_options_from_style (s);
  return quotearg_n_options (n, arg, argsize, &o);
}

char *
quotearg_style (enum quoting_style s, char const *arg)
{
  return quotearg_n_style (0, s, arg);
}

char *
quotearg_style_mem (enum quoting_style s, char const *arg, size_t argsize)
{
  return quotearg_n_style_mem (0, s, arg, argsize);
}

char *
quotearg_char_mem (char const *arg, size_t argsize, char ch)
{
  struct quoting_options options;
  options = default_quoting_options;
  set_char_quoting (&options, ch, 1);
  return quotearg_n_options (0, arg, argsize, &options);
}

char *
quotearg_char (char const *arg, char ch)
{
  return quotearg_char_mem (arg, ((size_t) -1), ch);
}

char *
quotearg_colon (char const *arg)
{
  return quotearg_char (arg, ':');
}

char *
quotearg_colon_mem (char const *arg, size_t argsize)
{
  return quotearg_char_mem (arg, argsize, ':');
}

char *
quotearg_n_style_colon (int n, enum quoting_style s, char const *arg)
{
  struct quoting_options options;
  options = quoting_options_from_style (s);
  set_char_quoting (&options, ':', 1);
  return quotearg_n_options (n, arg, ((size_t) -1), &options);
}

char *
quotearg_n_custom (int n, char const *left_quote,
                   char const *right_quote, char const *arg)
{
  return quotearg_n_custom_mem (n, left_quote, right_quote, arg,
                                ((size_t) -1));
}

char *
quotearg_n_custom_mem (int n, char const *left_quote,
                       char const *right_quote,
                       char const *arg, size_t argsize)
{
  struct quoting_options o = default_quoting_options;
  set_custom_quoting (&o, left_quote, right_quote);
  return quotearg_n_options (n, arg, argsize, &o);
}

char *
quotearg_custom (char const *left_quote, char const *right_quote,
                 char const *arg)
{
  return quotearg_n_custom (0, left_quote, right_quote, arg);
}

char *
quotearg_custom_mem (char const *left_quote, char const *right_quote,
                     char const *arg, size_t argsize)
{
  return quotearg_n_custom_mem (0, left_quote, right_quote, arg,
                                argsize);
}



struct quoting_options quote_quoting_options =
  {
    locale_quoting_style,
    0,
    { 0 },
    0, 0
  };

char const *
quote_n_mem (int n, char const *arg, size_t argsize)
{
  return quotearg_n_options (n, arg, argsize, &quote_quoting_options);
}

char const *
quote_mem (char const *arg, size_t argsize)
{
  return quote_n_mem (0, arg, argsize);
}

char const *
quote_n (int n, char const *arg)
{
  return quote_n_mem (n, arg, ((size_t) -1));
}

char const *
quote (char const *arg)
{
  return quote_n (0, arg);
}
