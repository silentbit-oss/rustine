# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat/vis.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat/vis.c"
# 31 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat/vis.c"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/types.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/types.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1



typedef int START_DELIMETER;
typedef unsigned chtype;
typedef chtype attr_t;
typedef int socklen_t;
typedef int size_t;
typedef struct __dirstream DIR;
typedef unsigned char cc_t;
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
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/types.h" 2
# 32 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat/vis.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/errno.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/errno.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/errno.h" 2
# 33 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat/vis.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/ctype.h" 1
# 34 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat/vis.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 1
# 35 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat/vis.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 36 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat/vis.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 37 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat/vis.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat.h" 1
# 20 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/types.h" 1
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/ioctl.h" 1
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/uio.h" 1
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 1
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/termios.h" 1
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/wchar.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat.h" 2
# 58 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat.h"
void err(int, const char *, ...);
void errx(int, const char *, ...);
void warn(const char *, ...);
void warnx(const char *, ...);
# 79 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/inttypes.h" 1
# 80 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat.h" 2





# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat/queue.h" 1
# 86 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat.h" 2





# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat/tree.h" 1
# 92 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat.h" 2





# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat/bitstring.h" 1
# 48 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat/bitstring.h"
typedef unsigned char bitstr_t;
# 98 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat.h" 2
# 119 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat/vis.h" 1
# 76 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat/vis.h"
char *vis(char *, int, int, int);
int strvis(char *, const char *, int);
int stravis(char **, const char *, int);
int strnvis(char *, const char *, size_t, int);
int strvisx(char *, const char *, size_t, int);
int strunvis(char *, const char *);
int unvis(char *, char, int *, int);
ssize_t strnunvis(char *, const char *, size_t);
# 120 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat.h" 2





# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat/imsg.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat/imsg.h"
struct ibuf {
 struct { struct ibuf *tqe_next; struct ibuf **tqe_prev; } entry;
 u_char *buf;
 size_t size;
 size_t max;
 size_t wpos;
 size_t rpos;
 int fd;
};

struct msgbuf {
 struct { struct ibuf *tqh_first; struct ibuf **tqh_last; } bufs;
 uint32_t queued;
 int fd;
};

struct ibuf_read {
 u_char buf[65535];
 u_char *rptr;
 size_t wpos;
};

struct imsg_fd {
 struct { struct imsg_fd *tqe_next; struct imsg_fd **tqe_prev; } entry;
 int fd;
};

struct imsgbuf {
 struct { struct imsg_fd *tqh_first; struct imsg_fd **tqh_last; } fds;
 struct ibuf_read r;
 struct msgbuf w;
 int fd;
 pid_t pid;
};



struct imsg_hdr {
 uint32_t type;
 uint16_t len;
 uint16_t flags;
 uint32_t peerid;
 uint32_t pid;
};

struct imsg {
 struct imsg_hdr hdr;
 int fd;
 void *data;
};



struct ibuf *ibuf_open(size_t);
struct ibuf *ibuf_dynamic(size_t, size_t);
int ibuf_add(struct ibuf *, const void *, size_t);
void *ibuf_reserve(struct ibuf *, size_t);
void *ibuf_seek(struct ibuf *, size_t, size_t);
size_t ibuf_size(struct ibuf *);
size_t ibuf_left(struct ibuf *);
void ibuf_close(struct msgbuf *, struct ibuf *);
int ibuf_write(struct msgbuf *);
void ibuf_free(struct ibuf *);
void msgbuf_init(struct msgbuf *);
void msgbuf_clear(struct msgbuf *);
int msgbuf_write(struct msgbuf *);
void msgbuf_drain(struct msgbuf *, size_t);


void imsg_init(struct imsgbuf *, int);
ssize_t imsg_read(struct imsgbuf *);
ssize_t imsg_get(struct imsgbuf *, struct imsg *);
int imsg_compose(struct imsgbuf *, uint32_t, uint32_t, pid_t, int,
     const void *, uint16_t);
int imsg_composev(struct imsgbuf *, uint32_t, uint32_t, pid_t, int,
     const struct iovec *, int);
struct ibuf *imsg_create(struct imsgbuf *, uint32_t, uint32_t, pid_t, uint16_t);
int imsg_add(struct ibuf *, const void *, uint16_t);
void imsg_close(struct imsgbuf *, struct ibuf *);
void imsg_free(struct imsg *);
int imsg_flush(struct imsgbuf *);
void imsg_clear(struct imsgbuf *);
# 126 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat.h" 2
# 216 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat.h"
void explicit_bzero(void *, size_t);




int getdtablecount(void);




void closefrom(int);




char *strcasestr(const char *, const char *);




char *strsep(char **, const char *);




long long strtonum(const char *, long long, long long, const char **);




size_t strlcpy(char *, const char *, size_t);




size_t strlcat(char *, const char *, size_t);




size_t strnlen(const char *, size_t);




char *strndup(const char *, size_t);




void *memmem(const void *, size_t, const void *, size_t);




int daemon(int, int);




const char *getprogname(void);




void setproctitle(const char *, ...);






int b64_ntop(const char *, size_t, char *, size_t);
int b64_pton(const char *, u_char *, size_t);




int getptmfd(void);
pid_t fdforkpty(int, int *, char *, struct termios *,
       struct winsize *);




pid_t forkpty(int *, char *, struct termios *, struct winsize *);




int asprintf(char **, const char *, ...);
int vasprintf(char **, const char *, va_list);




char *fgetln(FILE *, size_t *);



char *fparseln(FILE *, size_t *, size_t *, const char *, int);




int setenv(const char *, const char *, int);
int unsetenv(const char *);




void cfmakeraw(struct termios *);




void freezero(void *, size_t);




void *reallocarray(void *, size_t, size_t);




void *recallocarray(void *, size_t, size_t, size_t);
# 354 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat.h"
extern int BSDopterr;
extern int BSDoptind;
extern int BSDoptopt;
extern int BSDoptreset;
extern char *BSDoptarg;
int BSDgetopt(int, char *const *, const char *);
# 39 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat/vis.c" 2
# 56 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat/vis.c"
char *
vis(char *dst, int c, int flag, int nextc)
{
 if ((((c) == '\\' || (flag & 0x400) == 0) && (((u_int)(c) <= 255 && isascii((u_char)(c)) && (((c) != '*' && (c) != '?' && (c) != '[' && (c) != '#') || (flag & 0x100) == 0) && isgraph((u_char)(c))) || ((flag & 0x04) == 0 && (c) == ' ') || ((flag & 0x08) == 0 && (c) == '\t') || ((flag & 0x10) == 0 && (c) == '\n') || ((flag & 0x20) && ((c) == '\b' || (c) == '\007' || (c) == '\r' || isgraph((u_char)(c))))))) {
  if ((c == '"' && (flag & 0x200) != 0) ||
      (c == '\\' && (flag & 0x40) == 0))
   *dst++ = '\\';
  *dst++ = c;
  *dst = '\0';
  return (dst);
 }

 if (flag & 0x02) {
  switch(c) {
  case '\n':
   *dst++ = '\\';
   *dst++ = 'n';
   goto done;
  case '\r':
   *dst++ = '\\';
   *dst++ = 'r';
   goto done;
  case '\b':
   *dst++ = '\\';
   *dst++ = 'b';
   goto done;
  case '\a':
   *dst++ = '\\';
   *dst++ = 'a';
   goto done;
  case '\v':
   *dst++ = '\\';
   *dst++ = 'v';
   goto done;
  case '\t':
   *dst++ = '\\';
   *dst++ = 't';
   goto done;
  case '\f':
   *dst++ = '\\';
   *dst++ = 'f';
   goto done;
  case ' ':
   *dst++ = '\\';
   *dst++ = 's';
   goto done;
  case '\0':
   *dst++ = '\\';
   *dst++ = '0';
   if ((((u_char)(nextc)) >= '0' && ((u_char)(nextc)) <= '7')) {
    *dst++ = '0';
    *dst++ = '0';
   }
   goto done;
  }
 }
 if (((c & 0177) == ' ') || (flag & 0x01) ||
     ((flag & 0x100) && (c == '*' || c == '?' || c == '[' || c == '#'))) {
  *dst++ = '\\';
  *dst++ = ((u_char)c >> 6 & 07) + '0';
  *dst++ = ((u_char)c >> 3 & 07) + '0';
  *dst++ = ((u_char)c & 07) + '0';
  goto done;
 }
 if ((flag & 0x40) == 0)
  *dst++ = '\\';
 if (c & 0200) {
  c &= 0177;
  *dst++ = 'M';
 }
 if (iscntrl((u_char)c)) {
  *dst++ = '^';
  if (c == 0177)
   *dst++ = '?';
  else
   *dst++ = c + '@';
 } else {
  *dst++ = '-';
  *dst++ = c;
 }
done:
 *dst = '\0';
 return (dst);
}
# 154 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/compat/vis.c"
int
strvis(char *dst, const char *src, int flag)
{
 char c;
 char *start;

 for (start = dst; (c = *src);)
  dst = vis(dst, c, flag, *++src);
 *dst = '\0';
 return (dst - start);
}

int
strnvis(char *dst, const char *src, size_t siz, int flag)
{
 char *start, *end;
 char tbuf[5];
 int c, i;

 i = 0;
 for (start = dst, end = start + siz - 1; (c = *src) && dst < end; ) {
  if ((((c) == '\\' || (flag & 0x400) == 0) && (((u_int)(c) <= 255 && isascii((u_char)(c)) && (((c) != '*' && (c) != '?' && (c) != '[' && (c) != '#') || (flag & 0x100) == 0) && isgraph((u_char)(c))) || ((flag & 0x04) == 0 && (c) == ' ') || ((flag & 0x08) == 0 && (c) == '\t') || ((flag & 0x10) == 0 && (c) == '\n') || ((flag & 0x20) && ((c) == '\b' || (c) == '\007' || (c) == '\r' || isgraph((u_char)(c))))))) {
   if ((c == '"' && (flag & 0x200) != 0) ||
       (c == '\\' && (flag & 0x40) == 0)) {

    if (dst + 1 >= end) {
     i = 2;
     break;
    }
    *dst++ = '\\';
   }
   i = 1;
   *dst++ = c;
   src++;
  } else {
   i = vis(tbuf, c, flag, *++src) - tbuf;
   if (dst + i <= end) {
    memcpy(dst, tbuf, i);
    dst += i;
   } else {
    src--;
    break;
   }
  }
 }
 if (siz > 0)
  *dst = '\0';
 if (dst + i > end) {

  while ((c = *src))
   dst += vis(tbuf, c, flag, *++src) - tbuf;
 }
 return (dst - start);
}

int
stravis(char **outp, const char *src, int flag)
{
 char *buf;
 int len, serrno;

 buf = calloc(4, strlen(src) + 1);
 if (buf == 0)
  return -1;
 len = strvis(buf, src, flag);
 serrno = errno;
 *outp = realloc(buf, len + 1);
 if (*outp == 0) {
  *outp = buf;
  errno = serrno;
 }
 return (len);
}

int
strvisx(char *dst, const char *src, size_t len, int flag)
{
 char c;
 char *start;

 for (start = dst; len > 1; len--) {
  c = *src;
  dst = vis(dst, c, flag, *++src);
 }
 if (len)
  dst = vis(dst, *src, flag, '\0');
 *dst = '\0';
 return (dst - start);
}
