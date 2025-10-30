# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/pwd.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/pwd.c"
# 17 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/pwd.c"
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
# 18 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/pwd.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/getopt.h" 1
# 19 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/pwd.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 20 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/pwd.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/types.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/types.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/types.h" 2
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/pwd.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 1
# 19 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/attribute.h" 1
# 20 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/alloca.h" 1
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/stat.h" 1
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2





# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/param.h" 1
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2


# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/unistd.h" 1
# 33 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 1
# 35 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/pathmax.h" 1
# 47 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/pathmax.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/unistd.h" 1
# 48 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/pathmax.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 1
# 50 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/pathmax.h" 2







# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/param.h" 1
# 58 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/pathmax.h" 2
# 37 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2




# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/configmake.h" 1
# 42 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/time.h" 1
# 44 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/time.h" 1
# 45 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2







# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/sysmacros.h" 1
# 53 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2
# 70 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/stdckdint.h" 1
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/stdckdint.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/intprops-internal.h" 1
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/intprops-internal.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 1
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/intprops-internal.h" 2



#pragma GCC diagnostic ignored "-Wtype-limits"
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/stdckdint.h" 2
# 71 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 72 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 73 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/errno.h" 1
# 74 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2
# 82 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 83 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/version.h" 1
extern char const *Version;
# 84 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2


enum
{
  EXIT_TIMEDOUT = 124,
  EXIT_CANCELED = 125,
  EXIT_CANNOT_INVOKE = 126,
  EXIT_ENOENT = 127
};

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/exitfail.h" 1
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/exitfail.h"
extern int volatile exit_failure;
# 95 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2


static inline void
initialize_exit_failure (int status)
{
  if (status != 1)
    exit_failure = status;
}

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/fcntl.h" 1
# 105 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2



enum { O_PATHSEARCH = O_SEARCH };


# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/dirent.h" 1
# 112 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2




enum
{
  NOT_AN_INODE_NUMBER = 0
};
# 129 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/inttypes.h" 1
# 130 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2
# 142 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/stat-macros.h" 1
# 143 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/timespec.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/timespec.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/time.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/timespec.h" 2


# 39 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/timespec.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/arg-nonnull.h" 1
# 40 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/timespec.h" 2




enum { TIMESPEC_HZ = 1000000000 };
enum { LOG10_TIMESPEC_HZ = 9 };




enum { TIMESPEC_RESOLUTION = TIMESPEC_HZ };
enum { LOG10_TIMESPEC_RESOLUTION = LOG10_TIMESPEC_HZ };



inline struct timespec
make_timespec (time_t s, long int ns)
{
  return (struct timespec) { .tv_sec = s, .tv_nsec = ns };
}



inline int
timespec_cmp (struct timespec a, struct timespec b)
{
  return 2 * (((a.tv_sec) > (b.tv_sec)) - ((a.tv_sec) < (b.tv_sec))) + (((a.tv_nsec) > (b.tv_nsec)) - ((a.tv_nsec) < (b.tv_nsec)));
}



inline int
timespec_sign (struct timespec a)
{
  return (((a.tv_sec) > (0)) - ((a.tv_sec) < (0))) + (!a.tv_sec & !!a.tv_nsec);
}

struct timespec timespec_add (struct timespec, struct timespec)
  ;
struct timespec timespec_sub (struct timespec, struct timespec)
  ;
struct timespec dtotimespec (double)
  ;


inline double
timespectod (struct timespec a)
{
  return a.tv_sec + a.tv_nsec / 1e9;
}

long int gettime_res (void);
struct timespec current_timespec (void);
void gettime (struct timespec *) ;
int settime (struct timespec const *) ;






# 145 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2
# 158 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h"
static inline unsigned char to_uchar (char ch) { return ch; }

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/locale.h" 1
# 161 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2



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
# 165 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2
# 177 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h"
static inline unsigned long int
select_plural (uintmax_t n)
{


  enum { PLURAL_REDUCER = 1000000 };
  return (n <= 18446744073709551615UL ? n : n % PLURAL_REDUCER + PLURAL_REDUCER);
}
# 236 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/idx.h" 1
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/idx.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/idx.h" 2


# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/idx.h" 2
# 130 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/idx.h"
typedef ptrdiff_t idx_t;
# 237 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xalloc.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xalloc.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xalloc.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xalloc.h" 2






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

# 238 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/verify.h" 1
# 239 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2
# 254 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unlocked-io.h" 1
# 39 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unlocked-io.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 40 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/unlocked-io.h" 2
# 255 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/same-inode.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/same-inode.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/stat.h" 1
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/same-inode.h" 2


# 82 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/same-inode.h"
inline bool
psame_inode (struct stat const *a, struct stat const *b)
{
  return (! (((a)->st_dev ^ (b)->st_dev) | ((a)->st_ino ^ (b)->st_ino)));
}







# 256 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/dirname.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/dirname.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/dirname.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/filename.h" 1
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/filename.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/filename.h" 2
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/dirname.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/basename-lgpl.h" 1
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/basename-lgpl.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/basename-lgpl.h" 2
# 71 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/basename-lgpl.h"
extern char *last_component (char const *filename) ;




extern size_t base_len (char const *filename) ;
# 31 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/dirname.h" 2
# 41 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/dirname.h"
char *base_name (char const *file)
 
  ;
char *dir_name (char const *file)
 
  ;


char *mdir_name (char const *file)
  ;
size_t dir_len (char const *file) ;

bool strip_trailing_slashes (char *file);
# 258 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/openat.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/openat.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/fcntl.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/openat.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/types.h" 1
# 31 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/openat.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/stat.h" 1
# 32 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/openat.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/unistd.h" 1
# 33 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/openat.h" 2


# 55 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/openat.h"
_Noreturn void openat_restore_fail (int);
_Noreturn void openat_save_fail (int);
# 68 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/openat.h"
inline int
chownat (int fd, char const *file, uid_t owner, gid_t group)
{
  return fchownat (fd, file, owner, group, 0);
}

inline int
lchownat (int fd, char const *file, uid_t owner, gid_t group)
{
  return fchownat (fd, file, owner, group, AT_SYMLINK_NOFOLLOW);
}
# 88 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/openat.h"
inline int
chmodat (int fd, char const *file, mode_t mode)
{
  return fchmodat (fd, file, mode, 0);
}

inline int
lchmodat (int fd, char const *file, mode_t mode)
{
  return fchmodat (fd, file, mode, AT_SYMLINK_NOFOLLOW);
}
# 135 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/openat.h"

# 259 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2

static inline bool
dot_or_dotdot (char const *file_name)
{
  if (file_name[0] == '.')
    {
      char sep = file_name[(file_name[1] == '.') + 1];
      return (! sep || ((sep) == '/'));
    }
  else
    return 0;
}


static inline struct dirent const *
readdir_ignoring_dot_and_dotdot (DIR *dirp)
{
  while (1)
    {
      struct dirent const *dp = readdir (dirp);
      if (dp == ((void *) 0) || ! dot_or_dotdot (dp->d_name))
        return dp;
    }
}





enum {
    DS_UNKNOWN = -2,
    DS_EMPTY = -1,
    DS_NONEMPTY = 0,
};
static inline int
directory_status (int fd_cwd, char const *dir)
{
  DIR *dirp;
  bool no_direntries;
  int saved_errno;
  int fd = openat (fd_cwd, dir,
                   (O_RDONLY | O_DIRECTORY
                    | O_NOCTTY | O_NOFOLLOW | O_NONBLOCK));

  if (fd < 0)
    return errno;

  dirp = fdopendir (fd);
  if (dirp == ((void *) 0))
    {
      saved_errno = errno;
      close (fd);
      return saved_errno;
    }

  errno = 0;
  no_direntries = !readdir_ignoring_dot_and_dotdot (dirp);
  saved_errno = errno;
  closedir (dirp);
  return no_direntries && saved_errno == 0 ? DS_EMPTY : saved_errno;
}






enum
{
  GETOPT_HELP_CHAR = (-128 - 2),
  GETOPT_VERSION_CHAR = (-128 - 3)
};
# 357 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closein.h" 1
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closein.h"
void close_stdin_set_file_name (const char *file);
void close_stdin (void);
# 358 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/closeout.h"
void close_stdout_set_file_name (const char *file);
void close_stdout_set_ignore_EPIPE (bool ignore);
void close_stdout (void);
# 359 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2


# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/version-etc.h" 1
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/version-etc.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdarg.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/version-etc.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/version-etc.h" 2






extern const char version_etc_copyright[];
# 53 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/version-etc.h"
extern void version_etc_arn (FILE *stream,
                             const char *command_name, const char *package,
                             const char *version,
                             const char * const * authors, size_t n_authors);


extern void version_etc_ar (FILE *stream,
                            const char *command_name, const char *package,
                            const char *version, const char * const * authors);


extern void version_etc_va (FILE *stream,
                            const char *command_name, const char *package,
                            const char *version, va_list authors);



extern void version_etc (FILE *stream,
                         const char *command_name, const char *package,
                         const char *version,
                                                              ...)
  ;


extern void unused__emit_bug_reporting_address (void);
# 362 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2


# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/propername.h" 1
# 114 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/propername.h"
extern const char * proper_name (const char *name) ;





extern const char * proper_name_utf8 (const char *name_ascii,
                                      const char *name_utf8);




extern const char *proper_name_lite (const char *name_ascii,
                                     const char *name_utf8);
# 365 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2






# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/progname.h" 1
# 32 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/progname.h"
extern const char *program_name;




extern void set_program_name (const char *argv0);
# 372 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2
# 380 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/minmax.h" 1
# 39 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/minmax.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/param.h" 1
# 40 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/minmax.h" 2
# 381 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/intprops.h" 1
# 382 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2
# 457 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h"

static size_t
gcd (size_t u, size_t v)
{
  do
    {
      size_t t = u % v;
      u = v;
      v = t;
    }
  while (v);

  return u;
}






static inline size_t
lcm (size_t u, size_t v)
{
  return u * (v / gcd (u, v));
}






static inline void *
ptr_align (void const *ptr, size_t alignment)
{
  char const *p0 = ptr;
  char const *p1 = p0 + alignment - 1;
  return (void *) (p1 - (size_t) p1 % alignment);
}





static inline bool
is_nul (void const *buf, size_t length)
{
  const unsigned char *p = buf;
# 513 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h"
  unsigned char word;


  if (! length)
      return 1;


  while (__builtin_expect ((length & (sizeof word - 1)), 0))
    {
      if (*p)
        return 0;
      p++;
      length--;
      if (! length)
        return 1;
   }


  for (;;)
    {
      memcpy (&word, p, sizeof word);
      if (word)
        return 0;
      p += sizeof word;
      length -= sizeof word;
      if (! length)
        return 1;
      if (__builtin_expect ((length & 15), 0) == 0)
        break;
   }


   return memcmp (buf, p, length) == 0;
}
# 556 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h"
static inline void
emit_stdin_note (void)
{
  fputs_unlocked (gettext ("\nWith no FILE, or when FILE is -, read standard input.\n"),stdout)

           ;
}
static inline void
emit_mandatory_arg_note (void)
{
  fputs_unlocked (gettext ("\nMandatory arguments to long options are mandatory for short options too.\n"),stdout)

           ;
}

static inline void
emit_size_note (void)
{
  fputs_unlocked (gettext ("\nThe SIZE argument is an integer and optional unit (example: 10K is 10*1024).\nUnits are K,M,G,T,P,E,Z,Y,R,Q (powers of 1024) or KB,MB,... (powers of 1000).\nBinary prefixes can be used, too: KiB=K, MiB=M, and so on.\n"),stdout)



           ;
}

static inline void
emit_blocksize_note (char const *program)
{
  printf (gettext ("\nDisplay values are in units of the first available SIZE from --block-size,\nand the %s_BLOCK_SIZE, BLOCK_SIZE and BLOCKSIZE environment variables.\nOtherwise, units default to 1024 bytes (or 512 if POSIXLY_CORRECT is set).\n")



  , program);
}

static inline void
emit_update_parameters_note (void)
{
  fputs_unlocked (gettext ("\nUPDATE controls which existing files in the destination are replaced.\n'all' is the default operation when an --update option is not specified,\nand results in all existing files in the destination being replaced.\n'none' is like the --no-clobber option, in that no files in the\ndestination are replaced, and skipped files do not induce a failure.\n'none-fail' also ensures no files are replaced in the destination,\nbut any skipped files are diagnosed and induce a failure.\n'older' is the default operation when --update is specified, and results\nin files being replaced if they're older than the corresponding source file.\n"),stdout)
# 605 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h"
           ;
}

static inline void
emit_backup_suffix_note (void)
{
  fputs_unlocked (gettext ("\nThe backup suffix is '~', unless set with --suffix or SIMPLE_BACKUP_SUFFIX.\nThe version control method may be selected via the --backup option or through\nthe VERSION_CONTROL environment variable.  Here are the values:\n\n"),stdout)





           ;
  fputs_unlocked (gettext ("  none, off       never make backups (even if --backup is given)\n  numbered, t     make numbered backups\n  existing, nil   numbered if numbered backups exist, simple otherwise\n  simple, never   always make simple backups\n"),stdout)




           ;
}

static inline void
emit_symlink_recurse_options (char const *default_opt)
{
      printf (gettext ("\nThe following options modify how a hierarchy is traversed when the -R\noption is also specified.  If more than one is specified, only the final\none takes effect. '%s' is the default.\n\n  -H                     if a command line argument is a symbolic link\n                         to a directory, traverse it\n  -L                     traverse every symbolic link to a directory\n                         encountered\n  -P                     do not traverse any symbolic links\n\n")
# 641 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h"
  , default_opt);
}

static inline void
emit_exec_status (char const *program)
{
      printf (gettext ("\nExit status:\n  125  if the %s command itself fails\n  126  if COMMAND is found but cannot be invoked\n  127  if COMMAND cannot be found\n  -    the exit status of COMMAND otherwise\n")





  , program);
}

static inline void
emit_ancillary_info (char const *program)
{
  struct infomap { char const *program; char const *node; } const infomap[] = {
    { "[", "test invocation" },
    { "coreutils", "Multi-call invocation" },
    { "sha224sum", "sha2 utilities" },
    { "sha256sum", "sha2 utilities" },
    { "sha384sum", "sha2 utilities" },
    { "sha512sum", "sha2 utilities" },
    { ((void *) 0), ((void *) 0) }
  };

  char const *node = program;
  struct infomap const *map_prog = infomap;

  while (map_prog->program && ! (strcmp (program, map_prog->program) == 0))
    map_prog++;

  if (map_prog->node)
    node = map_prog->node;

  printf (gettext ("\n%s online help: <%s>\n"), "GNU coreutils", "https://www.gnu.org/software/coreutils/");



  char const *lc_messages = setlocale (LC_MESSAGES, ((void *) 0));
  if (lc_messages && strncmp (lc_messages, "" "en_" "", sizeof ("en_") - 1))
    {




      fputs_unlocked (gettext ("Report any translation bugs to " "<https://translationproject.org/team/>\n"),stdout)
                                                                   ;
    }



  char const *url_program = (strcmp (program, "[") == 0) ? "test" : program;
  printf (gettext ("Full documentation <%s%s>\n"),
          "https://www.gnu.org/software/coreutils/", url_program);
  printf (gettext ("or available locally via: info '(coreutils) %s%s'\n"),
          node, node == program ? " invocation" : "");
}
# 714 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/inttostr.h" 1
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/inttostr.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/inttostr.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/types.h" 1
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/inttostr.h" 2
# 35 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/inttostr.h"
 char *imaxtostr (intmax_t, char *);
 char *inttostr (int, char *);
 char *offtostr (off_t, char *);
 char *uinttostr (unsigned int, char *);
 char *umaxtostr (uintmax_t, char *);
# 715 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2

static inline char *
timetostr (time_t t, char *buf)
{
  return ((! ((time_t) 0 < (time_t) -1))
          ? imaxtostr (t, buf)
          : umaxtostr (t, buf));
}

static inline char *
bad_cast (char const *s)
{
  return (char *) s;
}


static inline bool
usable_st_size (struct stat const *sb)
{
  return (S_ISREG (sb->st_mode) || S_ISLNK (sb->st_mode)
          || S_TYPEISSHM (sb) || S_TYPEISTMO (sb));
}

_Noreturn void usage (int status);

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/error.h" 1
# 741 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2
# 766 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h"
static inline void
write_error (void)
{
  int saved_errno = errno;
  fflush_unlocked (stdout);
  fpurge (stdout);
  clearerr_unlocked (stdout);
  error (1, saved_errno, gettext ("write error"));
}






static inline char *
stzncpy (char * dest, char const * src, size_t len)
{
  size_t i;
  for (i = 0; i < len && *src; i++)
    *dest++ = *src++;
  *dest = 0;
  return dest;
}
# 799 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h"
static inline bool
is_ENOTSUP (int err)
{
  return err == EOPNOTSUPP || (ENOTSUP != EOPNOTSUPP && err == ENOTSUP);
}




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
# 809 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/system.h" 2
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/pwd.c" 2
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
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/pwd.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/root-dev-ino.h" 1
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/root-dev-ino.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/dev-ino.h" 1
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/dev-ino.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/types.h" 1
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/dev-ino.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/stat.h" 1
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/dev-ino.h" 2






struct dev_ino
{
  ino_t st_ino;
  dev_t st_dev;
};
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/root-dev-ino.h" 2


struct dev_ino *
get_root_dev_ino (struct dev_ino *root_d_i) ;
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/pwd.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xgetcwd.h" 1
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xgetcwd.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/xgetcwd.h" 2






extern char *xgetcwd (void)
  ;
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/pwd.c" 2






struct file_name
{
  char *buf;
  size_t n_alloc;
  char *start;
};

static struct option const longopts[] =
{
  {"logical", no_argument, ((void *) 0), 'L'},
  {"physical", no_argument, ((void *) 0), 'P'},
  {"help", no_argument, ((void *) 0), GETOPT_HELP_CHAR},
  {"version", no_argument, ((void *) 0), GETOPT_VERSION_CHAR},
  {((void *) 0), 0, ((void *) 0), 0}
};

void
usage (int status)
{
  if (status != 0)
    do { fprintf (stderr, gettext ("Try '%s --help' for more information.\n"), program_name); } while (0);
  else
    {
      printf (gettext ("Usage: %s [OPTION]...\n"), program_name);
      fputs_unlocked (gettext ("Print the full filename of the current working directory.\n\n"),stdout)


           ;
      fputs_unlocked (gettext ("  -L, --logical   use PWD from environment, even if it contains symlinks\n"),stdout)

           ;
      fputs_unlocked (gettext ("  -P, --physical  resolve all symlinks\n"),stdout)

           ;
      fputs_unlocked (gettext ("      --help        display this help and exit\n"),stdout);
      fputs_unlocked (gettext ("      --version     output version information and exit\n"),stdout);
      fputs_unlocked (gettext ("\nIf no option is specified, -P is assumed.\n"),stdout)

           ;
      printf (gettext ("\n" "Your shell may have its own version of %s, which usually supersedes\n" "the version described here.  Please refer to your shell's documentation\n" "for details about the options it supports.\n"), "pwd");
      emit_ancillary_info ("pwd");
    }
  exit (status);
}

static void
file_name_free (struct file_name *p)
{
  free (p->buf);
  free (p);
}

static struct file_name *
file_name_init (void)
{
  struct file_name *p = xmalloc (sizeof *p);



  p->n_alloc = ((2 * 8192) < (32 * 1024) ? (2 * 8192) : (32 * 1024));

  p->buf = xmalloc (p->n_alloc);
  p->start = p->buf + (p->n_alloc - 1);
  p->start[0] = '\0';
  return p;
}


static void
file_name_prepend (struct file_name *p, char const *s, size_t s_len)
{
  size_t n_free = p->start - p->buf;
  if (n_free < 1 + s_len)
    {
      size_t half = p->n_alloc + 1 + s_len;




      char *q = xnmalloc (2, half);
      size_t n_used = p->n_alloc - n_free;
      p->start = q + 2 * half - n_used;
      memcpy (p->start, p->buf + n_free, n_used);
      free (p->buf);
      p->buf = q;
      p->n_alloc = 2 * half;
    }

  p->start -= 1 + s_len;
  p->start[0] = '/';
  memcpy (p->start + 1, s, s_len);
}


static char *
nth_parent (size_t n)
{
  char *buf = xnmalloc (3, n);
  char *p = buf;

  for (size_t i = 0; i < n; i++)
    {
      memcpy (p, "../", 3);
      p += 3;
    }
  p[-1] = '\0';
  return buf;
}
# 152 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/pwd.c"
static void
find_dir_entry (struct stat *dot_sb, struct file_name *file_name,
                size_t parent_height)
{
  DIR *dirp;
  int fd;
  struct stat parent_sb;
  bool use_lstat;
  bool found;

  dirp = opendir ("..");
  if (dirp == ((void *) 0))
    error (1, errno, gettext ("cannot open directory %s"),
           quote (nth_parent (parent_height)));

  fd = dirfd (dirp);
  if ((0 <= fd ? fchdir (fd) : chdir ("..")) < 0)
    error (1, errno, gettext ("failed to chdir to %s"),
           quote (nth_parent (parent_height)));

  if ((0 <= fd ? fstat (fd, &parent_sb) : stat (".", &parent_sb)) < 0)
    error (1, errno, gettext ("failed to stat %s"),
           quote (nth_parent (parent_height)));



  use_lstat = (parent_sb.st_dev != dot_sb->st_dev);

  found = 0;
  while (1)
    {
      struct dirent const *dp;
      struct stat ent_sb;
      ino_t ino;

      errno = 0;
      if ((dp = readdir_ignoring_dot_and_dotdot (dirp)) == ((void *) 0))
        {
          if (errno)
            {

              int e = errno;
              closedir (dirp);
              errno = e;


              dirp = ((void *) 0);
            }
          break;
        }

      ino = (dp)->d_ino;

      if (ino == NOT_AN_INODE_NUMBER || use_lstat)
        {
          if (lstat (dp->d_name, &ent_sb) < 0)
            {

              continue;
            }
          ino = ent_sb.st_ino;
        }

      if (ino != dot_sb->st_ino)
        continue;



      if ( ! use_lstat || ent_sb.st_dev == dot_sb->st_dev)
        {
          file_name_prepend (file_name, dp->d_name, strlen ((dp)->d_name));
          found = 1;
          break;
        }
    }

  if (dirp == ((void *) 0) || closedir (dirp) != 0)
    {


      error (1, errno, gettext ("reading directory %s"),
             quote (nth_parent (parent_height)));
    }

  if ( ! found)
    error (1, 0,
           gettext ("couldn't find directory entry in %s with matching i-node"),
           quote (nth_parent (parent_height)));

  *dot_sb = parent_sb;
}
# 267 "/home/enumclass/Documents/C2RustTranslation/bkp/coreutils/pwd.c"
static void
robust_getcwd (struct file_name *file_name)
{
  size_t height = 1;
  struct dev_ino dev_ino_buf;
  struct dev_ino *root_dev_ino = get_root_dev_ino (&dev_ino_buf);
  struct stat dot_sb;

  if (root_dev_ino == ((void *) 0))
    error (1, errno, gettext ("failed to get attributes of %s"),
           quotearg_style (shell_escape_always_quoting_style, "/"));

  if (stat (".", &dot_sb) < 0)
    error (1, errno, gettext ("failed to stat %s"), quotearg_style (shell_escape_always_quoting_style, "."));

  while (1)
    {

      if ((! (((&dot_sb)->st_dev ^ (root_dev_ino)->st_dev) | ((&dot_sb)->st_ino ^ (root_dev_ino)->st_ino))))
        break;

      find_dir_entry (&dot_sb, file_name, height++);
    }


  if (file_name->start[0] == '\0')
    file_name_prepend (file_name, "", 0);
}




static char *
logical_getcwd (void)
{
  struct stat st1;
  struct stat st2;
  char *wd = getenv ("PWD");
  char *p;


  if (!wd || wd[0] != '/')
    return ((void *) 0);
  p = wd;
  while ((p = strstr (p, "/.")))
    {
      if (!p[2] || p[2] == '/'
          || (p[2] == '.' && (!p[3] || p[3] == '/')))
        return ((void *) 0);
      p++;
    }


  if (stat (wd, &st1) == 0 && stat (".", &st2) == 0 && psame_inode (&st1, &st2))
    return wd;
  return ((void *) 0);
}


int
main (int argc, char **argv)
{
  char *wd;



  bool logical = (getenv ("POSIXLY_CORRECT") != ((void *) 0));

  ;
  set_program_name (argv[0]);
  setlocale (LC_ALL, "");
  bindtextdomain ("coreutils", "/usr/local/share/locale");
  textdomain ("coreutils");

  atexit (close_stdout);

  while (1)
    {
      int c = getopt_long (argc, argv, "LP", longopts, ((void *) 0));
      if (c == -1)
        break;
      switch (c)
        {
        case 'L':
          logical = 1;
          break;
        case 'P':
          logical = 0;
          break;

        case GETOPT_HELP_CHAR: usage (0); break;;

        case GETOPT_VERSION_CHAR: version_etc (stdout, "pwd", "GNU coreutils", Version, proper_name_lite ("Jim Meyering", "Jim Meyering"), (char *) ((void *) 0)); exit (0); break;;

        default:
          usage (1);
        }
    }

  if (optind < argc)
    error (0, 0, gettext ("ignoring non-option arguments"));

  if (logical)
    {
      wd = logical_getcwd ();
      if (wd)
        {
          puts (wd);
          return 0;
        }
    }

  wd = xgetcwd ();
  if (wd != ((void *) 0))
    {
      puts (wd);
      free (wd);
    }
  else
    {
      struct file_name *file_name = file_name_init ();
      robust_getcwd (file_name);
      puts (file_name->start);
      file_name_free (file_name);
    }

  return 0;
}
