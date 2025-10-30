# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.c"
# 19 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.c"
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
# 20 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.h"
void close_stdout_set_file_name (const char *file);
void close_stdout_set_ignore_EPIPE (bool ignore);
void close_stdout (void);
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/errno.h" 1
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/unistd.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.c" 2

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
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.c" 2


# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/close-stream.h" 1
# 18 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/close-stream.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 19 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/close-stream.h" 2






int close_stream (FILE *stream);
# 31 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/error.h" 1
# 32 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/exitfail.h" 1
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/exitfail.h"
extern int volatile exit_failure;
# 33 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.c" 2
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
# 34 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.c" 2
# 42 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.c"
enum { SANITIZE_ADDRESS = 0 };


static const char *file_name;



void
close_stdout_set_file_name (const char *file)
{
  file_name = file;
}

static bool ignore_EPIPE ;
# 86 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.c"
void
close_stdout_set_ignore_EPIPE (bool ignore)
{
  ignore_EPIPE = ignore;
}
# 115 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.c"
void
close_stdout (void)
{
  if (close_stream (stdout) != 0
      && !(ignore_EPIPE && errno == EPIPE))
    {
      char const *write_error = gettext ("write error");
      if (file_name)
        error (0, errno, "%s: %s", quotearg_colon (file_name),
               write_error);
      else
        error (0, errno, "%s", write_error);

      _exit (exit_failure);
    }



  if (!SANITIZE_ADDRESS && close_stream (stderr) != 0)
    _exit (exit_failure);
}
# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.c"
# 19 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.c"
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
# 20 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.h"
void close_stdout_set_file_name (const char *file);
void close_stdout_set_ignore_EPIPE (bool ignore);
void close_stdout (void);
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/errno.h" 1
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/unistd.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.c" 2

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
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.c" 2


# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/close-stream.h" 1
# 18 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/close-stream.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 19 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/close-stream.h" 2






int close_stream (FILE *stream);
# 31 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/error.h" 1
# 32 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/exitfail.h" 1
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/exitfail.h"
extern int volatile exit_failure;
# 33 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.c" 2
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
# 34 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.c" 2
# 42 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.c"
enum { SANITIZE_ADDRESS = 0 };


static const char *file_name;



void
close_stdout_set_file_name (const char *file)
{
  file_name = file;
}

static bool ignore_EPIPE ;
# 86 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.c"
void
close_stdout_set_ignore_EPIPE (bool ignore)
{
  ignore_EPIPE = ignore;
}
# 115 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.c"
void
close_stdout (void)
{
  if (close_stream (stdout) != 0
      && !(ignore_EPIPE && errno == EPIPE))
    {
      char const *write_error = gettext ("write error");
      if (file_name)
        error (0, errno, "%s: %s", quotearg_colon (file_name),
               write_error);
      else
        error (0, errno, "%s", write_error);

      _exit (exit_failure);
    }



  if (!SANITIZE_ADDRESS && close_stream (stderr) != 0)
    _exit (exit_failure);
}
