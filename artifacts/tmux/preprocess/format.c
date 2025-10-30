# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/format.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/format.c"
# 19 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/format.c"
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
# 20 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/format.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/wait.h" 1
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/format.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/errno.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/errno.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/errno.h" 2
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/format.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/fnmatch.h" 1
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/format.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/libgen.h" 1
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/format.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdarg.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/format.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 27 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/format.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/format.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/time.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/format.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/unistd.h" 1
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/format.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/tmux.h" 1
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/tmux.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/time.h" 1
# 25 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/tmux.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/sys/uio.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/tmux.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/event.h" 1
# 28 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/tmux.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/limits.h" 1
# 29 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/tmux.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdarg.h" 1
# 30 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/tmux.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 31 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/tmux.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/termios.h" 1
# 32 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/tmux.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/wchar.h" 1
# 33 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/tmux.h" 2





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
# 39 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/tmux.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/xmalloc.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/xmalloc.h"
void *xmalloc(size_t);
void *xcalloc(size_t, size_t);
void *xrealloc(void *, size_t);
void *xreallocarray(void *, size_t, size_t);
char *xstrdup(const char *);
char *xstrndup(const char *, size_t);
int xasprintf(char **, const char *, ...)
 
  ;
int xvasprintf(char **, const char *, va_list)
  ;
int xsnprintf(char *, size_t, const char *, ...)
 
 
  ;
int xvsnprintf(char *, size_t, const char *, va_list)
 
  ;
# 40 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/tmux.h" 2

extern char **environ;

struct args;
struct client;
struct cmd_find_state;
struct cmdq_item;
struct cmdq_list;
struct environ;
struct format_job_tree;
struct input_ctx;
struct mode_tree_data;
struct mouse_event;
struct options;
struct options_entry;
struct session;
struct tmuxpeer;
struct tmuxproc;
# 135 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/tmux.h"
typedef unsigned long long key_code;


enum {

 KEYC_FOCUS_IN = 0x000010000000ULL,
 KEYC_FOCUS_OUT,


 KEYC_PASTE_START,
 KEYC_PASTE_END,


 KEYC_MOUSE,
 KEYC_DRAGGING,
 KEYC_MOUSEMOVE_PANE, KEYC_MOUSEMOVE_STATUS, KEYC_MOUSEMOVE_BORDER,
 KEYC_MOUSEDOWN1_PANE, KEYC_MOUSEDOWN1_STATUS, KEYC_MOUSEDOWN1_BORDER,
 KEYC_MOUSEDOWN2_PANE, KEYC_MOUSEDOWN2_STATUS, KEYC_MOUSEDOWN2_BORDER,
 KEYC_MOUSEDOWN3_PANE, KEYC_MOUSEDOWN3_STATUS, KEYC_MOUSEDOWN3_BORDER,
 KEYC_MOUSEUP1_PANE, KEYC_MOUSEUP1_STATUS, KEYC_MOUSEUP1_BORDER,
 KEYC_MOUSEUP2_PANE, KEYC_MOUSEUP2_STATUS, KEYC_MOUSEUP2_BORDER,
 KEYC_MOUSEUP3_PANE, KEYC_MOUSEUP3_STATUS, KEYC_MOUSEUP3_BORDER,
 KEYC_MOUSEDRAG1_PANE, KEYC_MOUSEDRAG1_STATUS, KEYC_MOUSEDRAG1_BORDER,
 KEYC_MOUSEDRAG2_PANE, KEYC_MOUSEDRAG2_STATUS, KEYC_MOUSEDRAG2_BORDER,
 KEYC_MOUSEDRAG3_PANE, KEYC_MOUSEDRAG3_STATUS, KEYC_MOUSEDRAG3_BORDER,
 KEYC_MOUSEDRAGEND1_PANE, KEYC_MOUSEDRAGEND1_STATUS, KEYC_MOUSEDRAGEND1_BORDER,
 KEYC_MOUSEDRAGEND2_PANE, KEYC_MOUSEDRAGEND2_STATUS, KEYC_MOUSEDRAGEND2_BORDER,
 KEYC_MOUSEDRAGEND3_PANE, KEYC_MOUSEDRAGEND3_STATUS, KEYC_MOUSEDRAGEND3_BORDER,
 KEYC_WHEELUP_PANE, KEYC_WHEELUP_STATUS, KEYC_WHEELUP_BORDER,
 KEYC_WHEELDOWN_PANE, KEYC_WHEELDOWN_STATUS, KEYC_WHEELDOWN_BORDER,
 KEYC_DOUBLECLICK1_PANE, KEYC_DOUBLECLICK1_STATUS, KEYC_DOUBLECLICK1_BORDER,
 KEYC_DOUBLECLICK2_PANE, KEYC_DOUBLECLICK2_STATUS, KEYC_DOUBLECLICK2_BORDER,
 KEYC_DOUBLECLICK3_PANE, KEYC_DOUBLECLICK3_STATUS, KEYC_DOUBLECLICK3_BORDER,
 KEYC_TRIPLECLICK1_PANE, KEYC_TRIPLECLICK1_STATUS, KEYC_TRIPLECLICK1_BORDER,
 KEYC_TRIPLECLICK2_PANE, KEYC_TRIPLECLICK2_STATUS, KEYC_TRIPLECLICK2_BORDER,
 KEYC_TRIPLECLICK3_PANE, KEYC_TRIPLECLICK3_STATUS, KEYC_TRIPLECLICK3_BORDER,


 KEYC_BSPACE,


 KEYC_F1,
 KEYC_F2,
 KEYC_F3,
 KEYC_F4,
 KEYC_F5,
 KEYC_F6,
 KEYC_F7,
 KEYC_F8,
 KEYC_F9,
 KEYC_F10,
 KEYC_F11,
 KEYC_F12,
 KEYC_IC,
 KEYC_DC,
 KEYC_HOME,
 KEYC_END,
 KEYC_NPAGE,
 KEYC_PPAGE,
 KEYC_BTAB,


 KEYC_UP,
 KEYC_DOWN,
 KEYC_LEFT,
 KEYC_RIGHT,


 KEYC_KP_SLASH,
 KEYC_KP_STAR,
 KEYC_KP_MINUS,
 KEYC_KP_SEVEN,
 KEYC_KP_EIGHT,
 KEYC_KP_NINE,
 KEYC_KP_PLUS,
 KEYC_KP_FOUR,
 KEYC_KP_FIVE,
 KEYC_KP_SIX,
 KEYC_KP_ONE,
 KEYC_KP_TWO,
 KEYC_KP_THREE,
 KEYC_KP_ENTER,
 KEYC_KP_ZERO,
 KEYC_KP_PERIOD,
};


enum tty_code_code {
 TTYC_AX = 0,
 TTYC_ACSC,
 TTYC_BCE,
 TTYC_BEL,
 TTYC_BLINK,
 TTYC_BOLD,
 TTYC_CIVIS,
 TTYC_CLEAR,
 TTYC_CNORM,
 TTYC_COLORS,
 TTYC_CR,
 TTYC_CS,
 TTYC_CSR,
 TTYC_CUB,
 TTYC_CUB1,
 TTYC_CUD,
 TTYC_CUD1,
 TTYC_CUF,
 TTYC_CUF1,
 TTYC_CUP,
 TTYC_CUU,
 TTYC_CUU1,
 TTYC_CVVIS,
 TTYC_DCH,
 TTYC_DCH1,
 TTYC_DIM,
 TTYC_DL,
 TTYC_DL1,
 TTYC_E3,
 TTYC_ECH,
 TTYC_ED,
 TTYC_EL,
 TTYC_EL1,
 TTYC_ENACS,
 TTYC_FSL,
 TTYC_HOME,
 TTYC_HPA,
 TTYC_ICH,
 TTYC_ICH1,
 TTYC_IL,
 TTYC_IL1,
 TTYC_INDN,
 TTYC_INVIS,
 TTYC_KCBT,
 TTYC_KCUB1,
 TTYC_KCUD1,
 TTYC_KCUF1,
 TTYC_KCUU1,
 TTYC_KDC2,
 TTYC_KDC3,
 TTYC_KDC4,
 TTYC_KDC5,
 TTYC_KDC6,
 TTYC_KDC7,
 TTYC_KDCH1,
 TTYC_KDN2,
 TTYC_KDN3,
 TTYC_KDN4,
 TTYC_KDN5,
 TTYC_KDN6,
 TTYC_KDN7,
 TTYC_KEND,
 TTYC_KEND2,
 TTYC_KEND3,
 TTYC_KEND4,
 TTYC_KEND5,
 TTYC_KEND6,
 TTYC_KEND7,
 TTYC_KF1,
 TTYC_KF10,
 TTYC_KF11,
 TTYC_KF12,
 TTYC_KF13,
 TTYC_KF14,
 TTYC_KF15,
 TTYC_KF16,
 TTYC_KF17,
 TTYC_KF18,
 TTYC_KF19,
 TTYC_KF2,
 TTYC_KF20,
 TTYC_KF21,
 TTYC_KF22,
 TTYC_KF23,
 TTYC_KF24,
 TTYC_KF25,
 TTYC_KF26,
 TTYC_KF27,
 TTYC_KF28,
 TTYC_KF29,
 TTYC_KF3,
 TTYC_KF30,
 TTYC_KF31,
 TTYC_KF32,
 TTYC_KF33,
 TTYC_KF34,
 TTYC_KF35,
 TTYC_KF36,
 TTYC_KF37,
 TTYC_KF38,
 TTYC_KF39,
 TTYC_KF4,
 TTYC_KF40,
 TTYC_KF41,
 TTYC_KF42,
 TTYC_KF43,
 TTYC_KF44,
 TTYC_KF45,
 TTYC_KF46,
 TTYC_KF47,
 TTYC_KF48,
 TTYC_KF49,
 TTYC_KF5,
 TTYC_KF50,
 TTYC_KF51,
 TTYC_KF52,
 TTYC_KF53,
 TTYC_KF54,
 TTYC_KF55,
 TTYC_KF56,
 TTYC_KF57,
 TTYC_KF58,
 TTYC_KF59,
 TTYC_KF6,
 TTYC_KF60,
 TTYC_KF61,
 TTYC_KF62,
 TTYC_KF63,
 TTYC_KF7,
 TTYC_KF8,
 TTYC_KF9,
 TTYC_KHOM2,
 TTYC_KHOM3,
 TTYC_KHOM4,
 TTYC_KHOM5,
 TTYC_KHOM6,
 TTYC_KHOM7,
 TTYC_KHOME,
 TTYC_KIC2,
 TTYC_KIC3,
 TTYC_KIC4,
 TTYC_KIC5,
 TTYC_KIC6,
 TTYC_KIC7,
 TTYC_KICH1,
 TTYC_KIND,
 TTYC_KLFT2,
 TTYC_KLFT3,
 TTYC_KLFT4,
 TTYC_KLFT5,
 TTYC_KLFT6,
 TTYC_KLFT7,
 TTYC_KMOUS,
 TTYC_KNP,
 TTYC_KNXT2,
 TTYC_KNXT3,
 TTYC_KNXT4,
 TTYC_KNXT5,
 TTYC_KNXT6,
 TTYC_KNXT7,
 TTYC_KPP,
 TTYC_KPRV2,
 TTYC_KPRV3,
 TTYC_KPRV4,
 TTYC_KPRV5,
 TTYC_KPRV6,
 TTYC_KPRV7,
 TTYC_KRI,
 TTYC_KRIT2,
 TTYC_KRIT3,
 TTYC_KRIT4,
 TTYC_KRIT5,
 TTYC_KRIT6,
 TTYC_KRIT7,
 TTYC_KUP2,
 TTYC_KUP3,
 TTYC_KUP4,
 TTYC_KUP5,
 TTYC_KUP6,
 TTYC_KUP7,
 TTYC_MS,
 TTYC_OP,
 TTYC_REV,
 TTYC_RGB,
 TTYC_RI,
 TTYC_RMACS,
 TTYC_RMCUP,
 TTYC_RMKX,
 TTYC_SE,
 TTYC_SETAB,
 TTYC_SETAF,
 TTYC_SETRGBB,
 TTYC_SETRGBF,
 TTYC_SGR0,
 TTYC_SITM,
 TTYC_SMACS,
 TTYC_SMCUP,
 TTYC_SMKX,
 TTYC_SMSO,
 TTYC_SMUL,
 TTYC_SMXX,
 TTYC_SS,
 TTYC_TC,
 TTYC_TSL,
 TTYC_U8,
 TTYC_VPA,
 TTYC_XENL,
 TTYC_XT,
};


enum msgtype {
 MSG_VERSION = 12,

 MSG_IDENTIFY_FLAGS = 100,
 MSG_IDENTIFY_TERM,
 MSG_IDENTIFY_TTYNAME,
 MSG_IDENTIFY_OLDCWD,
 MSG_IDENTIFY_STDIN,
 MSG_IDENTIFY_ENVIRON,
 MSG_IDENTIFY_DONE,
 MSG_IDENTIFY_CLIENTPID,
 MSG_IDENTIFY_CWD,

 MSG_COMMAND = 200,
 MSG_DETACH,
 MSG_DETACHKILL,
 MSG_EXIT,
 MSG_EXITED,
 MSG_EXITING,
 MSG_LOCK,
 MSG_READY,
 MSG_RESIZE,
 MSG_SHELL,
 MSG_SHUTDOWN,
 MSG_STDERR,
 MSG_STDIN,
 MSG_STDOUT,
 MSG_SUSPEND,
 MSG_UNLOCK,
 MSG_WAKEUP,
 MSG_EXEC,
};






struct msg_command_data {
 int argc;
};

struct msg_stdin_data {
 ssize_t size;
 char data[1024];
};

struct msg_stdout_data {
 ssize_t size;
 char data[1024];
};

struct msg_stderr_data {
 ssize_t size;
 char data[1024];
};
# 518 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/tmux.h"
struct utf8_data {
 u_char data[9];

 u_char have;
 u_char size;

 u_char width;
} ;
enum utf8_state {
 UTF8_MORE,
 UTF8_DONE,
 UTF8_ERROR
};
# 561 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/tmux.h"
struct grid_cell {
 u_char flags;
 u_short attr;
 int fg;
 int bg;
 struct utf8_data data;
};
struct grid_cell_entry {
 u_char flags;
 union {
  u_int offset;
  struct {
   u_char attr;
   u_char fg;
   u_char bg;
   u_char data;
  } data;
 };
} ;


struct grid_line {
 u_int cellused;
 u_int cellsize;
 struct grid_cell_entry *celldata;

 u_int extdsize;
 struct grid_cell *extddata;

 int flags;
} ;


struct grid {
 int flags;


 u_int sx;
 u_int sy;

 u_int hscrolled;
 u_int hsize;
 u_int hlimit;

 struct grid_line *linedata;
};


struct hook {
 const char *name;

 struct cmd_list *cmdlist;

 struct { struct hook *rbe_left; struct hook *rbe_right; struct hook *rbe_parent; int rbe_color; } entry;
};


struct job;
typedef void (*job_update_cb) (struct job *);
typedef void (*job_complete_cb) (struct job *);
typedef void (*job_free_cb) (void *);
struct job {
 enum {
  JOB_RUNNING,
  JOB_DEAD,
  JOB_CLOSED
 } state;

 int flags;


 char *cmd;
 pid_t pid;
 int status;

 int fd;
 struct bufferevent *event;

 job_update_cb updatecb;
 job_complete_cb completecb;
 job_free_cb freecb;
 void *data;

 struct { struct job *le_next; struct job **le_prev; } entry;
};
struct joblist { struct job *lh_first; };


struct screen_sel {
 int flag;
 int hidden;

 int rectflag;
 enum {
  LINE_SEL_NONE,
  LINE_SEL_LEFT_RIGHT,
  LINE_SEL_RIGHT_LEFT,
 } lineflag;

 int modekeys;

 u_int sx;
 u_int sy;

 u_int ex;
 u_int ey;

 struct grid_cell cell;
};


struct screen_titles;
struct screen {
 char *title;
 struct screen_titles *titles;

 struct grid *grid;

 u_int cx;
 u_int cy;

 u_int cstyle;
 char *ccolour;

 u_int rupper;
 u_int rlower;

 int mode;

 bitstr_t *tabs;

 struct screen_sel sel;
};


struct screen_write_collect_item;
struct screen_write_collect_line;
struct screen_write_ctx {
 struct window_pane *wp;
 struct screen *s;

 struct screen_write_collect_item *item;
 struct screen_write_collect_line *list;
 u_int scrolled;
 u_int bg;

 u_int cells;
 u_int written;
 u_int skipped;
};
# 722 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/tmux.h"
struct window_mode {
 const char *name;

 struct screen *(*init)(struct window_pane *, struct cmd_find_state *,
        struct args *);
 void (*free)(struct window_pane *);
 void (*resize)(struct window_pane *, u_int, u_int);
 void (*key)(struct window_pane *, struct client *,
        struct session *, key_code, struct mouse_event *);

 const char *(*key_table)(struct window_pane *);
 void (*command)(struct window_pane *, struct client *,
        struct session *, struct args *,
        struct mouse_event *);
};



struct window_choose_data {
 struct client *start_client;
 struct session *start_session;

 u_int idx;
 int type;




 struct session *tree_session;

 struct winlink *wl;
 int pane_id;

 char *ft_template;
 struct format_tree *ft;

 char *command;
};


struct window_pane {
 u_int id;
 u_int active_point;

 struct window *window;

 struct layout_cell *layout_cell;
 struct layout_cell *saved_layout_cell;

 u_int sx;
 u_int sy;

 u_int osx;
 u_int osy;

 u_int xoff;
 u_int yoff;

 int flags;
# 793 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/tmux.h"
 int argc;
 char **argv;
 char *shell;
 const char *cwd;

 pid_t pid;
 char tty[32];
 int status;

 int fd;
 struct bufferevent *event;

 struct event resize_timer;

 struct input_ctx *ictx;

 struct grid_cell colgc;

 int *palette;

 int pipe_fd;
 struct bufferevent *pipe_event;
 size_t pipe_off;

 struct screen *screen;
 struct screen base;

 struct screen status_screen;
 size_t status_size;


 u_int saved_cx;
 u_int saved_cy;
 struct grid *saved_grid;
 struct grid_cell saved_cell;

 const struct window_mode *mode;
 void *modedata;
 struct event modetimer;
 time_t modelast;
 u_int modeprefix;
 char *searchstr;

 struct { struct window_pane *tqe_next; struct window_pane **tqe_prev; } entry;
 struct { struct window_pane *rbe_left; struct window_pane *rbe_right; struct window_pane *rbe_parent; int rbe_color; } tree_entry;
};
struct window_panes { struct window_pane *tqh_first; struct window_pane **tqh_last; };
struct window_pane_tree { struct window_pane *rbh_root; };


struct window {
 u_int id;

 char *name;
 struct event name_event;
 struct timeval name_time;

 struct event alerts_timer;

 struct timeval activity_time;

 struct window_pane *active;
 struct window_pane *last;
 struct window_panes panes;

 int lastlayout;
 struct layout_cell *layout_root;
 struct layout_cell *saved_layout_root;
 char *old_layout;

 u_int sx;
 u_int sy;

 int flags;
# 877 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/tmux.h"
 int alerts_queued;
 struct { struct window *tqe_next; struct window **tqe_prev; } alerts_entry;

 struct options *options;

 struct grid_cell style;
 struct grid_cell active_style;

 u_int references;
 struct { struct winlink *tqh_first; struct winlink **tqh_last; } winlinks;

 struct { struct window *rbe_left; struct window *rbe_right; struct window *rbe_parent; int rbe_color; } entry;
};
struct windows { struct window *rbh_root; };


struct winlink {
 int idx;
 struct session *session;
 struct window *window;

 size_t status_width;
 struct grid_cell status_cell;
 char *status_text;

 int flags;





 struct { struct winlink *rbe_left; struct winlink *rbe_right; struct winlink *rbe_parent; int rbe_color; } entry;
 struct { struct winlink *tqe_next; struct winlink **tqe_prev; } wentry;
 struct { struct winlink *tqe_next; struct winlink **tqe_prev; } sentry;
};
struct winlinks { struct winlink *rbh_root; };
struct winlink_stack { struct winlink *tqh_first; struct winlink **tqh_last; };


enum layout_type {
 LAYOUT_LEFTRIGHT,
 LAYOUT_TOPBOTTOM,
 LAYOUT_WINDOWPANE
};


struct layout_cells { struct layout_cell *tqh_first; struct layout_cell **tqh_last; };


struct layout_cell {
 enum layout_type type;

 struct layout_cell *parent;

 u_int sx;
 u_int sy;

 u_int xoff;
 u_int yoff;

 struct window_pane *wp;
 struct layout_cells cells;

 struct { struct layout_cell *tqe_next; struct layout_cell **tqe_prev; } entry;
};


struct environ_entry {
 char *name;
 char *value;

 struct { struct environ_entry *rbe_left; struct environ_entry *rbe_right; struct environ_entry *rbe_parent; int rbe_color; } entry;
};


struct session_group {
 const char *name;
 struct { struct session *tqh_first; struct session **tqh_last; } sessions;

 struct { struct session_group *rbe_left; struct session_group *rbe_right; struct session_group *rbe_parent; int rbe_color; } entry;
};
struct session_groups { struct session_group *rbh_root; };

struct session {
 u_int id;

 char *name;
 const char *cwd;

 struct timeval creation_time;
 struct timeval last_attached_time;
 struct timeval activity_time;
 struct timeval last_activity_time;

 struct event lock_timer;

 u_int sx;
 u_int sy;

 struct winlink *curw;
 struct winlink_stack lastw;
 struct winlinks windows;

 int statusat;

 struct hooks *hooks;
 struct options *options;




 int flags;

 u_int attached;

 struct termios *tio;

 struct environ *environ;

 int references;

 struct { struct session *tqe_next; struct session **tqe_prev; } gentry;
 struct { struct session *rbe_left; struct session *rbe_right; struct session *rbe_parent; int rbe_color; } entry;
};
struct sessions { struct session *rbh_root; };
# 1022 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/tmux.h"
struct mouse_event {
 int valid;

 key_code key;
 int statusat;

 u_int x;
 u_int y;
 u_int b;

 u_int lx;
 u_int ly;
 u_int lb;

 int s;
 int w;
 int wp;

 u_int sgr_type;
 u_int sgr_b;
};


struct tty_key {
 char ch;
 key_code key;

 struct tty_key *left;
 struct tty_key *right;

 struct tty_key *next;
};

struct tty_code;
struct tty_term {
 char *name;
 u_int references;

 char acs[255 + 1][2];

 struct tty_code *codes;



 int flags;

 struct { struct tty_term *le_next; struct tty_term **le_prev; } entry;
};
struct tty_terms { struct tty_term *lh_first; };

struct tty {
 struct client *client;

 u_int sx;
 u_int sy;

 u_int cx;
 u_int cy;
 u_int cstyle;
 char *ccolour;

 int mode;

 u_int rlower;
 u_int rupper;

 u_int rleft;
 u_int rright;

 int fd;
 struct event event_in;
 struct evbuffer *in;
 struct event event_out;
 struct evbuffer *out;
 struct event timer;
 size_t discarded;

 struct termios tio;

 struct grid_cell cell;

 int last_wp;
 struct grid_cell last_cell;
# 1114 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/tmux.h"
 int flags;

 struct tty_term *term;
 char *term_name;
 int term_flags;
 enum {
  TTY_VT100,
  TTY_VT101,
  TTY_VT102,
  TTY_VT220,
  TTY_VT320,
  TTY_VT420,
  TTY_UNKNOWN
 } term_type;

 struct mouse_event mouse;
 int mouse_drag_flag;
 void (*mouse_drag_update)(struct client *,
       struct mouse_event *);
 void (*mouse_drag_release)(struct client *,
       struct mouse_event *);

 struct event key_timer;
 struct tty_key *key_tree;
};




struct tty_ctx {
 struct window_pane *wp;

 const struct grid_cell *cell;
 int wrapped;

 u_int num;
 void *ptr;






 u_int ocx;
 u_int ocy;

 u_int orupper;
 u_int orlower;

 u_int xoff;
 u_int yoff;


 u_int bg;
};


struct message_entry {
 char *msg;
 u_int msg_num;
 time_t msg_time;
 struct { struct message_entry *tqe_next; struct message_entry **tqe_prev; } entry;
};


struct args_entry;
struct args_tree { struct args_entry *rbh_root; };
struct args {
 struct args_tree tree;
 int argc;
 char **argv;
};


enum cmd_find_type {
 CMD_FIND_PANE,
 CMD_FIND_WINDOW,
 CMD_FIND_SESSION,
};
struct cmd_find_state {
 int flags;
 struct cmd_find_state *current;

 struct session *s;
 struct winlink *wl;
 struct window *w;
 struct window_pane *wp;
 int idx;
};
# 1214 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/tmux.h"
struct cmd {
 const struct cmd_entry *entry;
 struct args *args;

 char *file;
 u_int line;


 int flags;

 struct { struct cmd *tqe_next; struct cmd **tqe_prev; } qentry;
};

struct cmd_list {
 int references;
 struct { struct cmd *tqh_first; struct cmd **tqh_last; } list;
};


enum cmd_retval {
 CMD_RETURN_ERROR = -1,
 CMD_RETURN_NORMAL = 0,
 CMD_RETURN_WAIT,
 CMD_RETURN_STOP
};


enum cmdq_type {
 CMDQ_COMMAND,
 CMDQ_CALLBACK,
};


struct cmdq_shared {
 int references;

 int flags;


 struct format_tree *formats;

 struct mouse_event mouse;
 struct cmd_find_state current;
};


typedef enum cmd_retval (*cmdq_cb) (struct cmdq_item *, void *);
struct cmdq_item {
 const char *name;
 struct cmdq_list *queue;
 struct cmdq_item *next;

 struct client *client;

 enum cmdq_type type;
 u_int group;

 u_int number;
 time_t time;

 int flags;




 struct cmdq_shared *shared;
 struct cmd_find_state source;
 struct cmd_find_state target;

 struct cmd_list *cmdlist;
 struct cmd *cmd;

 cmdq_cb cb;
 void *data;

 struct { struct cmdq_item *tqe_next; struct cmdq_item **tqe_prev; } entry;
};
struct cmdq_list { struct cmdq_item *tqh_first; struct cmdq_item **tqh_last; };


struct cmd_entry_flag {
 char flag;
 enum cmd_find_type type;
 int flags;
};


struct cmd_entry {
 const char *name;
 const char *alias;

 struct {
  const char *template;
  int lower;
  int upper;
 } args;
 const char *usage;

 struct cmd_entry_flag source;
 struct cmd_entry_flag target;




 int flags;

 enum cmd_retval (*exec)(struct cmd *, struct cmdq_item *);
};


struct status_line {
 struct event timer;
 struct screen status;
 struct screen *old_status;
};


typedef int (*prompt_input_cb)(struct client *, void *, const char *, int);
typedef void (*prompt_free_cb)(void *);
struct client {
 const char *name;
 struct tmuxpeer *peer;
 struct cmdq_list queue;

 pid_t pid;
 int fd;
 struct event event;
 int retval;

 struct timeval creation_time;
 struct timeval activity_time;

 struct environ *environ;
 struct format_job_tree *jobs;

 char *title;
 const char *cwd;

 char *term;
 char *ttyname;
 struct tty tty;

 size_t written;
 size_t discarded;
 size_t redraw;

 void (*stdin_callback)(struct client *, int, void *);
 void *stdin_callback_data;
 struct evbuffer *stdin_data;
 int stdin_closed;
 struct evbuffer *stdout_data;
 struct evbuffer *stderr_data;

 struct event repeat_timer;

 struct event click_timer;
 u_int click_button;

 struct status_line status;
# 1398 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/tmux.h"
 int flags;
 struct key_table *keytable;

 struct event identify_timer;
 void (*identify_callback)(struct client *,
        struct window_pane *);
 void *identify_callback_data;

 char *message_string;
 struct event message_timer;
 u_int message_next;
 struct { struct message_entry *tqh_first; struct message_entry **tqh_last; } message_log;

 char *prompt_string;
 struct utf8_data *prompt_buffer;
 size_t prompt_index;
 prompt_input_cb prompt_inputcb;
 prompt_free_cb prompt_freecb;
 void *prompt_data;
 u_int prompt_hindex;
 enum { PROMPT_ENTRY, PROMPT_COMMAND } prompt_mode;





 int prompt_flags;

 struct session *session;
 struct session *last_session;

 int wlmouse;

 int references;

 struct { struct client *tqe_next; struct client **tqe_prev; } entry;
};
struct clients { struct client *tqh_first; struct client **tqh_last; };


struct key_binding {
 key_code key;
 struct cmd_list *cmdlist;

 int flags;


 struct { struct key_binding *rbe_left; struct key_binding *rbe_right; struct key_binding *rbe_parent; int rbe_color; } entry;
};
struct key_bindings { struct key_binding *rbh_root; };

struct key_table {
 const char *name;
 struct key_bindings key_bindings;

 u_int references;

 struct { struct key_table *rbe_left; struct key_table *rbe_right; struct key_table *rbe_parent; int rbe_color; } entry;
};
struct key_tables { struct key_table *rbh_root; };


enum options_table_type {
 OPTIONS_TABLE_STRING,
 OPTIONS_TABLE_NUMBER,
 OPTIONS_TABLE_KEY,
 OPTIONS_TABLE_COLOUR,
 OPTIONS_TABLE_ATTRIBUTES,
 OPTIONS_TABLE_FLAG,
 OPTIONS_TABLE_CHOICE,
 OPTIONS_TABLE_STYLE,
 OPTIONS_TABLE_ARRAY,
};
enum options_table_scope {
 OPTIONS_TABLE_NONE,
 OPTIONS_TABLE_SERVER,
 OPTIONS_TABLE_SESSION,
 OPTIONS_TABLE_WINDOW,
};

struct options_table_entry {
 const char *name;
 enum options_table_type type;
 enum options_table_scope scope;

 u_int minimum;
 u_int maximum;
 const char **choices;

 const char *default_str;
 long long default_num;

 const char *separator;
 const char *style;
};
# 1506 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/tmux.h"
extern struct hooks *global_hooks;
extern struct options *global_options;
extern struct options *global_s_options;
extern struct options *global_w_options;
extern struct environ *global_environ;
extern struct timeval start_time;
extern const char *socket_path;
extern const char *shell_command;
extern int ptm_fd;
extern const char *shell_command;
int areshell(const char *);
void setblocking(int, int);
const char *find_home(void);


struct imsg;
int proc_send(struct tmuxpeer *, enum msgtype, int, const void *, size_t);
struct tmuxproc *proc_start(const char *);
void proc_loop(struct tmuxproc *, int (*)(void));
void proc_exit(struct tmuxproc *);
void proc_set_signals(struct tmuxproc *, void(*)(int));
void proc_clear_signals(struct tmuxproc *, int);
struct tmuxpeer *proc_add_peer(struct tmuxproc *, int,
     void (*)(struct imsg *, void *), void *);
void proc_remove_peer(struct tmuxpeer *);
void proc_kill_peer(struct tmuxpeer *);
void proc_toggle_log(struct tmuxproc *);


extern int cfg_finished;
void start_cfg(void);
int load_cfg(const char *, struct client *, struct cmdq_item *, int);
void set_cfg_file(const char *);
void cfg_add_cause(const char *, ...);
void cfg_print_causes(struct cmdq_item *);
void cfg_show_causes(struct session *);


struct paste_buffer;
const char *paste_buffer_name(struct paste_buffer *);
u_int paste_buffer_order(struct paste_buffer *);
time_t paste_buffer_created(struct paste_buffer *);
const char *paste_buffer_data(struct paste_buffer *, size_t *);
struct paste_buffer *paste_walk(struct paste_buffer *);
struct paste_buffer *paste_get_top(const char **);
struct paste_buffer *paste_get_name(const char *);
void paste_free(struct paste_buffer *);
void paste_add(char *, size_t);
int paste_rename(const char *, const char *, char **);
int paste_set(char *, size_t, const char *, char **);
char *paste_make_sample(struct paste_buffer *);
# 1565 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/tmux.h"
struct format_tree;
int format_true(const char *);
struct format_tree *format_create(struct client *, struct cmdq_item *, int,
       int);
void format_free(struct format_tree *);
void format_add(struct format_tree *, const char *,
       const char *, ...);
char *format_expand_time(struct format_tree *, const char *, time_t);
char *format_expand(struct format_tree *, const char *);
char *format_single(struct cmdq_item *, const char *,
       struct client *, struct session *, struct winlink *,
       struct window_pane *);
void format_defaults(struct format_tree *, struct client *,
       struct session *, struct winlink *, struct window_pane *);
void format_defaults_window(struct format_tree *, struct window *);
void format_defaults_pane(struct format_tree *,
       struct window_pane *);
void format_defaults_paste_buffer(struct format_tree *,
       struct paste_buffer *);
void format_lost_client(struct client *);


struct hook;
struct hooks *hooks_get(struct session *);
struct hooks *hooks_create(struct hooks *);
void hooks_free(struct hooks *);
struct hook *hooks_first(struct hooks *);
struct hook *hooks_next(struct hook *);
void hooks_add(struct hooks *, const char *, struct cmd_list *);
void hooks_copy(struct hooks *, struct hooks *);
void hooks_remove(struct hooks *, const char *);
struct hook *hooks_find(struct hooks *, const char *);
void hooks_insert(struct hooks *, struct cmdq_item *,
      struct cmd_find_state *, const char *, ...);


void notify_input(struct window_pane *, struct evbuffer *);
void notify_client(const char *, struct client *);
void notify_session(const char *, struct session *);
void notify_winlink(const char *, struct winlink *);
void notify_session_window(const char *, struct session *, struct window *);
void notify_window(const char *, struct window *);
void notify_pane(const char *, struct window_pane *);


struct options *options_create(struct options *);
void options_free(struct options *);
struct options_entry *options_first(struct options *);
struct options_entry *options_next(struct options_entry *);
struct options_entry *options_empty(struct options *,
       const struct options_table_entry *);
struct options_entry *options_default(struct options *,
       const struct options_table_entry *);
const char *options_name(struct options_entry *);
const struct options_table_entry *options_table_entry(struct options_entry *);
struct options_entry *options_get_only(struct options *, const char *);
struct options_entry *options_get(struct options *, const char *);
void options_remove(struct options_entry *);
void options_array_clear(struct options_entry *);
const char *options_array_get(struct options_entry *, u_int);
int options_array_set(struct options_entry *, u_int, const char *,
       int);
int options_array_size(struct options_entry *, u_int *);
void options_array_assign(struct options_entry *, const char *);
int options_isstring(struct options_entry *);
const char *options_tostring(struct options_entry *, int, int);
char *options_parse(const char *, int *);
struct options_entry *options_parse_get(struct options *, const char *, int *,
       int);
char *options_match(const char *, int *, int *);
struct options_entry *options_match_get(struct options *, const char *, int *,
       int, int *);
const char *options_get_string(struct options *, const char *);
long long options_get_number(struct options *, const char *);
const struct grid_cell *options_get_style(struct options *, const char *);
struct options_entry * options_set_string(struct options *,
       const char *, int, const char *, ...);
struct options_entry *options_set_number(struct options *, const char *,
       long long);
struct options_entry *options_set_style(struct options *, const char *, int,
       const char *);
enum options_table_scope options_scope_from_flags(struct args *, int,
       struct cmd_find_state *, struct options **, char **);
void options_style_update_new(struct options *,
       struct options_entry *);
void options_style_update_old(struct options *,
       struct options_entry *);


extern const struct options_table_entry options_table[];


extern struct joblist all_jobs;
struct job *job_run(const char *, struct session *, const char *,
       job_update_cb, job_complete_cb, job_free_cb, void *, int);
void job_free(struct job *);
void job_died(struct job *, int);


struct environ *environ_create(void);
void environ_free(struct environ *);
struct environ_entry *environ_first(struct environ *);
struct environ_entry *environ_next(struct environ_entry *);
void environ_copy(struct environ *, struct environ *);
struct environ_entry *environ_find(struct environ *, const char *);
void environ_set(struct environ *, const char *, const char *,
     ...);
void environ_clear(struct environ *, const char *);
void environ_put(struct environ *, const char *);
void environ_unset(struct environ *, const char *);
void environ_update(struct options *, struct environ *, struct environ *);
void environ_push(struct environ *);
void environ_log(struct environ *, const char *, ...);
struct environ *environ_for_session(struct session *, int);


void tty_create_log(void);
void tty_raw(struct tty *, const char *);
void tty_attributes(struct tty *, const struct grid_cell *,
     const struct window_pane *);
void tty_reset(struct tty *);
void tty_region_off(struct tty *);
void tty_margin_off(struct tty *);
void tty_cursor(struct tty *, u_int, u_int);
void tty_putcode(struct tty *, enum tty_code_code);
void tty_putcode1(struct tty *, enum tty_code_code, int);
void tty_putcode2(struct tty *, enum tty_code_code, int, int);
void tty_putcode3(struct tty *, enum tty_code_code, int, int, int);
void tty_putcode_ptr1(struct tty *, enum tty_code_code, const void *);
void tty_putcode_ptr2(struct tty *, enum tty_code_code, const void *,
     const void *);
void tty_puts(struct tty *, const char *);
void tty_putc(struct tty *, u_char);
void tty_putn(struct tty *, const void *, size_t, u_int);
int tty_init(struct tty *, struct client *, int, char *);
void tty_resize(struct tty *);
void tty_set_size(struct tty *, u_int, u_int);
void tty_start_tty(struct tty *);
void tty_stop_tty(struct tty *);
void tty_set_title(struct tty *, const char *);
void tty_update_mode(struct tty *, int, struct screen *);
void tty_draw_pane(struct tty *, const struct window_pane *, u_int, u_int,
     u_int);
void tty_draw_line(struct tty *, const struct window_pane *, struct screen *,
     u_int, u_int, u_int);
int tty_open(struct tty *, char **);
void tty_close(struct tty *);
void tty_free(struct tty *);
void tty_set_type(struct tty *, int);
void tty_write(void (*)(struct tty *, const struct tty_ctx *),
     struct tty_ctx *);
void tty_cmd_alignmenttest(struct tty *, const struct tty_ctx *);
void tty_cmd_cell(struct tty *, const struct tty_ctx *);
void tty_cmd_cells(struct tty *, const struct tty_ctx *);
void tty_cmd_clearendofline(struct tty *, const struct tty_ctx *);
void tty_cmd_clearendofscreen(struct tty *, const struct tty_ctx *);
void tty_cmd_clearline(struct tty *, const struct tty_ctx *);
void tty_cmd_clearscreen(struct tty *, const struct tty_ctx *);
void tty_cmd_clearstartofline(struct tty *, const struct tty_ctx *);
void tty_cmd_clearstartofscreen(struct tty *, const struct tty_ctx *);
void tty_cmd_deletecharacter(struct tty *, const struct tty_ctx *);
void tty_cmd_clearcharacter(struct tty *, const struct tty_ctx *);
void tty_cmd_deleteline(struct tty *, const struct tty_ctx *);
void tty_cmd_erasecharacter(struct tty *, const struct tty_ctx *);
void tty_cmd_insertcharacter(struct tty *, const struct tty_ctx *);
void tty_cmd_insertline(struct tty *, const struct tty_ctx *);
void tty_cmd_linefeed(struct tty *, const struct tty_ctx *);
void tty_cmd_scrollup(struct tty *, const struct tty_ctx *);
void tty_cmd_reverseindex(struct tty *, const struct tty_ctx *);
void tty_cmd_setselection(struct tty *, const struct tty_ctx *);
void tty_cmd_rawstring(struct tty *, const struct tty_ctx *);


extern struct tty_terms tty_terms;
u_int tty_term_ncodes(void);
struct tty_term *tty_term_find(char *, int, char **);
void tty_term_free(struct tty_term *);
int tty_term_has(struct tty_term *, enum tty_code_code);
const char *tty_term_string(struct tty_term *, enum tty_code_code);
const char *tty_term_string1(struct tty_term *, enum tty_code_code, int);
const char *tty_term_string2(struct tty_term *, enum tty_code_code, int,
       int);
const char *tty_term_string3(struct tty_term *, enum tty_code_code, int,
       int, int);
const char *tty_term_ptr1(struct tty_term *, enum tty_code_code,
       const void *);
const char *tty_term_ptr2(struct tty_term *, enum tty_code_code,
       const void *, const void *);
int tty_term_number(struct tty_term *, enum tty_code_code);
int tty_term_flag(struct tty_term *, enum tty_code_code);
const char *tty_term_describe(struct tty_term *, enum tty_code_code);


int tty_acs_needed(struct tty *);
const char *tty_acs_get(struct tty *, u_char);


void tty_keys_build(struct tty *);
void tty_keys_free(struct tty *);
key_code tty_keys_next(struct tty *);


void args_set(struct args *, u_char, const char *);
struct args *args_parse(const char *, int, char **);
void args_free(struct args *);
char *args_print(struct args *);
int args_has(struct args *, u_char);
const char *args_get(struct args *, u_char);
long long args_strtonum(struct args *, u_char, long long, long long,
       char **);


int cmd_find_target(struct cmd_find_state *, struct cmdq_item *,
       const char *, enum cmd_find_type, int);
struct client *cmd_find_best_client(struct session *);
struct client *cmd_find_client(struct cmdq_item *, const char *, int);
void cmd_find_clear_state(struct cmd_find_state *, int);
int cmd_find_empty_state(struct cmd_find_state *);
int cmd_find_valid_state(struct cmd_find_state *);
void cmd_find_copy_state(struct cmd_find_state *,
       struct cmd_find_state *);
void cmd_find_log_state(const char *, struct cmd_find_state *);
void cmd_find_from_session(struct cmd_find_state *,
       struct session *, int);
void cmd_find_from_winlink(struct cmd_find_state *,
       struct winlink *, int);
int cmd_find_from_session_window(struct cmd_find_state *,
       struct session *, struct window *, int);
int cmd_find_from_window(struct cmd_find_state *, struct window *,
       int);
void cmd_find_from_winlink_pane(struct cmd_find_state *,
       struct winlink *, struct window_pane *, int);
int cmd_find_from_pane(struct cmd_find_state *,
       struct window_pane *, int);
int cmd_find_from_client(struct cmd_find_state *, struct client *,
       int);
int cmd_find_from_mouse(struct cmd_find_state *,
       struct mouse_event *, int);
int cmd_find_from_nothing(struct cmd_find_state *, int);


int cmd_pack_argv(int, char **, char *, size_t);
int cmd_unpack_argv(char *, size_t, int, char ***);
char **cmd_copy_argv(int, char **);
void cmd_free_argv(int, char **);
char *cmd_stringify_argv(int, char **);
struct cmd *cmd_parse(int, char **, const char *, u_int, char **);
char *cmd_print(struct cmd *);
int cmd_mouse_at(struct window_pane *, struct mouse_event *,
       u_int *, u_int *, int);
struct winlink *cmd_mouse_window(struct mouse_event *, struct session **);
struct window_pane *cmd_mouse_pane(struct mouse_event *, struct session **,
       struct winlink **);
char *cmd_template_replace(const char *, const char *, int);
extern const struct cmd_entry *cmd_table[];


enum cmd_retval cmd_attach_session(struct cmdq_item *, const char *, int, int,
       const char *, int);


struct cmd_list *cmd_list_parse(int, char **, const char *, u_int, char **);
void cmd_list_free(struct cmd_list *);
char *cmd_list_print(struct cmd_list *);


struct cmdq_item *cmdq_get_command(struct cmd_list *, struct cmd_find_state *,
       struct mouse_event *, int);

struct cmdq_item *cmdq_get_callback1(const char *, cmdq_cb, void *);
void cmdq_insert_after(struct cmdq_item *, struct cmdq_item *);
void cmdq_append(struct client *, struct cmdq_item *);
void cmdq_format(struct cmdq_item *, const char *,
       const char *, ...);
u_int cmdq_next(struct client *);
void cmdq_guard(struct cmdq_item *, const char *, int);
void cmdq_print(struct cmdq_item *, const char *, ...);
void cmdq_error(struct cmdq_item *, const char *, ...);


int cmd_string_split(const char *, int *, char ***);
struct cmd_list *cmd_string_parse(const char *, const char *, u_int, char **);


void cmd_wait_for_flush(void);


int client_main(struct event_base *, int, char **, int);


 void key_bindings_RB_INSERT_COLOR(struct key_bindings *, struct key_binding *); void key_bindings_RB_REMOVE_COLOR(struct key_bindings *, struct key_binding *, struct key_binding *); struct key_binding *key_bindings_RB_REMOVE(struct key_bindings *, struct key_binding *); struct key_binding *key_bindings_RB_INSERT(struct key_bindings *, struct key_binding *); struct key_binding *key_bindings_RB_FIND(struct key_bindings *, struct key_binding *); struct key_binding *key_bindings_RB_NFIND(struct key_bindings *, struct key_binding *); struct key_binding *key_bindings_RB_NEXT(struct key_binding *); struct key_binding *key_bindings_RB_PREV(struct key_binding *); struct key_binding *key_bindings_RB_MINMAX(struct key_bindings *, int);;
 void key_tables_RB_INSERT_COLOR(struct key_tables *, struct key_table *); void key_tables_RB_REMOVE_COLOR(struct key_tables *, struct key_table *, struct key_table *); struct key_table *key_tables_RB_REMOVE(struct key_tables *, struct key_table *); struct key_table *key_tables_RB_INSERT(struct key_tables *, struct key_table *); struct key_table *key_tables_RB_FIND(struct key_tables *, struct key_table *); struct key_table *key_tables_RB_NFIND(struct key_tables *, struct key_table *); struct key_table *key_tables_RB_NEXT(struct key_table *); struct key_table *key_tables_RB_PREV(struct key_table *); struct key_table *key_tables_RB_MINMAX(struct key_tables *, int);;
extern struct key_tables key_tables;
int key_table_cmp(struct key_table *, struct key_table *);
int key_bindings_cmp(struct key_binding *, struct key_binding *);
struct key_table *key_bindings_get_table(const char *, int);
void key_bindings_unref_table(struct key_table *);
void key_bindings_add(const char *, key_code, int, struct cmd_list *);
void key_bindings_remove(const char *, key_code);
void key_bindings_remove_table(const char *);
void key_bindings_init(void);
void key_bindings_dispatch(struct key_binding *, struct cmdq_item *,
      struct client *, struct mouse_event *, struct cmd_find_state *);


key_code key_string_lookup_string(const char *);
const char *key_string_lookup_key(key_code);


void alerts_reset_all(void);
void alerts_queue(struct window *, int);
void alerts_check_session(struct session *);


extern struct tmuxproc *server_proc;
extern struct clients clients;
extern struct cmd_find_state marked_pane;
void server_set_marked(struct session *, struct winlink *,
      struct window_pane *);
void server_clear_marked(void);
int server_is_marked(struct session *, struct winlink *,
      struct window_pane *);
int server_check_marked(void);
int server_start(struct tmuxproc *, struct event_base *, int, char *);
void server_update_socket(void);
void server_add_accept(int);


u_int server_client_how_many(void);
void server_client_set_identify(struct client *, u_int);
void server_client_clear_identify(struct client *, struct window_pane *);
void server_client_set_key_table(struct client *, const char *);
const char *server_client_get_key_table(struct client *);
int server_client_check_nested(struct client *);
void server_client_handle_key(struct client *, key_code);
struct client *server_client_create(int);
int server_client_open(struct client *, char **);
void server_client_unref(struct client *);
void server_client_lost(struct client *);
void server_client_suspend(struct client *);
void server_client_detach(struct client *, enum msgtype);
void server_client_exec(struct client *, const char *);
void server_client_loop(void);
void server_client_push_stdout(struct client *);
void server_client_push_stderr(struct client *);
void server_client_add_message(struct client *, const char *,
      ...);
char *server_client_get_path(struct client *, const char *);
const char *server_client_get_cwd(struct client *);


void server_redraw_client(struct client *);
void server_status_client(struct client *);
void server_redraw_session(struct session *);
void server_redraw_session_group(struct session *);
void server_status_session(struct session *);
void server_status_session_group(struct session *);
void server_redraw_window(struct window *);
void server_redraw_window_borders(struct window *);
void server_status_window(struct window *);
void server_lock(void);
void server_lock_session(struct session *);
void server_lock_client(struct client *);
void server_kill_pane(struct window_pane *);
void server_kill_window(struct window *);
int server_link_window(struct session *,
      struct winlink *, struct session *, int, int, int, char **);
void server_unlink_window(struct session *, struct winlink *);
void server_destroy_pane(struct window_pane *, int);
void server_destroy_session(struct session *);
void server_check_unattached(void);
int server_set_stdin_callback(struct client *, void (*)(struct client *,
      int, void *), void *, char **);
void server_unzoom_window(struct window *);


void status_timer_start(struct client *);
void status_timer_start_all(void);
void status_update_saved(struct session *s);
int status_at_line(struct client *);
u_int status_line_size(struct session *);
struct window *status_get_window_at(struct client *, u_int);
int status_redraw(struct client *);
void status_message_set(struct client *, const char *, ...);
void status_message_clear(struct client *);
int status_message_redraw(struct client *);
void status_prompt_set(struct client *, const char *, const char *,
      prompt_input_cb, prompt_free_cb, void *, int);
void status_prompt_clear(struct client *);
int status_prompt_redraw(struct client *);
int status_prompt_key(struct client *, key_code);
void status_prompt_update(struct client *, const char *, const char *);
void status_prompt_load_history(void);
void status_prompt_save_history(void);


void recalculate_sizes(void);


void input_init(struct window_pane *);
void input_free(struct window_pane *);
void input_reset(struct window_pane *, int);
struct evbuffer *input_pending(struct window_pane *);
void input_parse(struct window_pane *);


void input_key(struct window_pane *, key_code, struct mouse_event *);


char *xterm_keys_lookup(key_code);
int xterm_keys_find(const char *, size_t, size_t *, key_code *);


int colour_find_rgb(u_char, u_char, u_char);
int colour_join_rgb(u_char, u_char, u_char);
void colour_split_rgb(int, u_char *, u_char *, u_char *);
const char *colour_tostring(int);
int colour_fromstring(const char *s);
u_char colour_256to16(u_char);


const char *attributes_tostring(int);
int attributes_fromstring(const char *);


extern const struct grid_cell grid_default_cell;
int grid_cells_equal(const struct grid_cell *, const struct grid_cell *);
struct grid *grid_create(u_int, u_int, u_int);
void grid_destroy(struct grid *);
int grid_compare(struct grid *, struct grid *);
void grid_collect_history(struct grid *);
void grid_scroll_history(struct grid *, u_int);
void grid_scroll_history_region(struct grid *, u_int, u_int, u_int);
void grid_clear_history(struct grid *);
const struct grid_line *grid_peek_line(struct grid *, u_int);
void grid_get_cell(struct grid *, u_int, u_int, struct grid_cell *);
void grid_set_cell(struct grid *, u_int, u_int, const struct grid_cell *);
void grid_set_cells(struct grid *, u_int, u_int, const struct grid_cell *,
      const char *, size_t);
void grid_clear(struct grid *, u_int, u_int, u_int, u_int, u_int);
void grid_clear_lines(struct grid *, u_int, u_int, u_int);
void grid_move_lines(struct grid *, u_int, u_int, u_int, u_int);
void grid_move_cells(struct grid *, u_int, u_int, u_int, u_int, u_int);
char *grid_string_cells(struct grid *, u_int, u_int, u_int,
      struct grid_cell **, int, int, int);
void grid_duplicate_lines(struct grid *, u_int, struct grid *, u_int,
      u_int);
void grid_reflow(struct grid *, u_int, u_int *);


void grid_view_get_cell(struct grid *, u_int, u_int, struct grid_cell *);
void grid_view_set_cell(struct grid *, u_int, u_int,
      const struct grid_cell *);
void grid_view_set_cells(struct grid *, u_int, u_int,
      const struct grid_cell *, const char *, size_t);
void grid_view_clear_history(struct grid *, u_int);
void grid_view_clear(struct grid *, u_int, u_int, u_int, u_int, u_int);
void grid_view_scroll_region_up(struct grid *, u_int, u_int, u_int);
void grid_view_scroll_region_down(struct grid *, u_int, u_int, u_int);
void grid_view_insert_lines(struct grid *, u_int, u_int, u_int);
void grid_view_insert_lines_region(struct grid *, u_int, u_int, u_int,
 u_int);
void grid_view_delete_lines(struct grid *, u_int, u_int, u_int);
void grid_view_delete_lines_region(struct grid *, u_int, u_int, u_int,
 u_int);
void grid_view_insert_cells(struct grid *, u_int, u_int, u_int, u_int);
void grid_view_delete_cells(struct grid *, u_int, u_int, u_int, u_int);
char *grid_view_string_cells(struct grid *, u_int, u_int, u_int);


void screen_write_start(struct screen_write_ctx *, struct window_pane *,
      struct screen *);
void screen_write_stop(struct screen_write_ctx *);
void screen_write_reset(struct screen_write_ctx *);
size_t screen_write_cstrlen(const char *, ...);
void screen_write_cnputs(struct screen_write_ctx *,
      ssize_t, const struct grid_cell *, const char *, ...);
size_t screen_write_strlen(const char *, ...);
void screen_write_puts(struct screen_write_ctx *,
      const struct grid_cell *, const char *, ...);
void screen_write_nputs(struct screen_write_ctx *,
      ssize_t, const struct grid_cell *, const char *, ...);
void screen_write_vnputs(struct screen_write_ctx *, ssize_t,
      const struct grid_cell *, const char *, va_list);
void screen_write_putc(struct screen_write_ctx *, const struct grid_cell *,
      u_char);
void screen_write_copy(struct screen_write_ctx *, struct screen *, u_int,
      u_int, u_int, u_int, bitstr_t *, const struct grid_cell *);
void screen_write_fast_copy(struct screen_write_ctx *, struct screen *,
      u_int, u_int, u_int, u_int);
void screen_write_hline(struct screen_write_ctx *, u_int, int, int);
void screen_write_vline(struct screen_write_ctx *, u_int, int, int);
void screen_write_box(struct screen_write_ctx *, u_int, u_int);
void screen_write_preview(struct screen_write_ctx *, struct screen *, u_int,
      u_int);
void screen_write_backspace(struct screen_write_ctx *);
void screen_write_mode_set(struct screen_write_ctx *, int);
void screen_write_mode_clear(struct screen_write_ctx *, int);
void screen_write_cursorup(struct screen_write_ctx *, u_int);
void screen_write_cursordown(struct screen_write_ctx *, u_int);
void screen_write_cursorright(struct screen_write_ctx *, u_int);
void screen_write_cursorleft(struct screen_write_ctx *, u_int);
void screen_write_alignmenttest(struct screen_write_ctx *);
void screen_write_insertcharacter(struct screen_write_ctx *, u_int, u_int);
void screen_write_deletecharacter(struct screen_write_ctx *, u_int, u_int);
void screen_write_clearcharacter(struct screen_write_ctx *, u_int, u_int);
void screen_write_insertline(struct screen_write_ctx *, u_int, u_int);
void screen_write_deleteline(struct screen_write_ctx *, u_int, u_int);
void screen_write_clearline(struct screen_write_ctx *, u_int);
void screen_write_clearendofline(struct screen_write_ctx *, u_int);
void screen_write_clearstartofline(struct screen_write_ctx *, u_int);
void screen_write_cursormove(struct screen_write_ctx *, u_int, u_int);
void screen_write_reverseindex(struct screen_write_ctx *, u_int);
void screen_write_scrollregion(struct screen_write_ctx *, u_int, u_int);
void screen_write_linefeed(struct screen_write_ctx *, int, u_int);
void screen_write_scrollup(struct screen_write_ctx *, u_int, u_int);
void screen_write_carriagereturn(struct screen_write_ctx *);
void screen_write_clearendofscreen(struct screen_write_ctx *, u_int);
void screen_write_clearstartofscreen(struct screen_write_ctx *, u_int);
void screen_write_clearscreen(struct screen_write_ctx *, u_int);
void screen_write_clearhistory(struct screen_write_ctx *);
void screen_write_collect_end(struct screen_write_ctx *);
void screen_write_collect_add(struct screen_write_ctx *,
      const struct grid_cell *);
void screen_write_cell(struct screen_write_ctx *, const struct grid_cell *);
void screen_write_setselection(struct screen_write_ctx *, u_char *, u_int);
void screen_write_rawstring(struct screen_write_ctx *, u_char *, u_int);


void screen_redraw_update(struct client *);
void screen_redraw_screen(struct client *, int, int, int);
void screen_redraw_pane(struct client *, struct window_pane *);


void screen_init(struct screen *, u_int, u_int, u_int);
void screen_reinit(struct screen *);
void screen_free(struct screen *);
void screen_reset_tabs(struct screen *);
void screen_set_cursor_style(struct screen *, u_int);
void screen_set_cursor_colour(struct screen *, const char *);
void screen_set_title(struct screen *, const char *);
void screen_push_title(struct screen *);
void screen_pop_title(struct screen *);
void screen_resize(struct screen *, u_int, u_int, int);
void screen_set_selection(struct screen *,
      u_int, u_int, u_int, u_int, u_int, struct grid_cell *);
void screen_clear_selection(struct screen *);
void screen_hide_selection(struct screen *);
int screen_check_selection(struct screen *, u_int, u_int);
void screen_select_cell(struct screen *, struct grid_cell *,
      const struct grid_cell *);


extern struct windows windows;
extern struct window_pane_tree all_window_panes;
int window_cmp(struct window *, struct window *);
 void windows_RB_INSERT_COLOR(struct windows *, struct window *); void windows_RB_REMOVE_COLOR(struct windows *, struct window *, struct window *); struct window *windows_RB_REMOVE(struct windows *, struct window *); struct window *windows_RB_INSERT(struct windows *, struct window *); struct window *windows_RB_FIND(struct windows *, struct window *); struct window *windows_RB_NFIND(struct windows *, struct window *); struct window *windows_RB_NEXT(struct window *); struct window *windows_RB_PREV(struct window *); struct window *windows_RB_MINMAX(struct windows *, int);;
int winlink_cmp(struct winlink *, struct winlink *);
 void winlinks_RB_INSERT_COLOR(struct winlinks *, struct winlink *); void winlinks_RB_REMOVE_COLOR(struct winlinks *, struct winlink *, struct winlink *); struct winlink *winlinks_RB_REMOVE(struct winlinks *, struct winlink *); struct winlink *winlinks_RB_INSERT(struct winlinks *, struct winlink *); struct winlink *winlinks_RB_FIND(struct winlinks *, struct winlink *); struct winlink *winlinks_RB_NFIND(struct winlinks *, struct winlink *); struct winlink *winlinks_RB_NEXT(struct winlink *); struct winlink *winlinks_RB_PREV(struct winlink *); struct winlink *winlinks_RB_MINMAX(struct winlinks *, int);;
int window_pane_cmp(struct window_pane *, struct window_pane *);
 void window_pane_tree_RB_INSERT_COLOR(struct window_pane_tree *, struct window_pane *); void window_pane_tree_RB_REMOVE_COLOR(struct window_pane_tree *, struct window_pane *, struct window_pane *); struct window_pane *window_pane_tree_RB_REMOVE(struct window_pane_tree *, struct window_pane *); struct window_pane *window_pane_tree_RB_INSERT(struct window_pane_tree *, struct window_pane *); struct window_pane *window_pane_tree_RB_FIND(struct window_pane_tree *, struct window_pane *); struct window_pane *window_pane_tree_RB_NFIND(struct window_pane_tree *, struct window_pane *); struct window_pane *window_pane_tree_RB_NEXT(struct window_pane *); struct window_pane *window_pane_tree_RB_PREV(struct window_pane *); struct window_pane *window_pane_tree_RB_MINMAX(struct window_pane_tree *, int);;
struct winlink *winlink_find_by_index(struct winlinks *, int);
struct winlink *winlink_find_by_window(struct winlinks *, struct window *);
struct winlink *winlink_find_by_window_id(struct winlinks *, u_int);
u_int winlink_count(struct winlinks *);
struct winlink *winlink_add(struct winlinks *, int);
void winlink_set_window(struct winlink *, struct window *);
void winlink_remove(struct winlinks *, struct winlink *);
struct winlink *winlink_next(struct winlink *);
struct winlink *winlink_previous(struct winlink *);
struct winlink *winlink_next_by_number(struct winlink *, struct session *,
       int);
struct winlink *winlink_previous_by_number(struct winlink *, struct session *,
       int);
void winlink_stack_push(struct winlink_stack *, struct winlink *);
void winlink_stack_remove(struct winlink_stack *, struct winlink *);
struct window *window_find_by_id_str(const char *);
struct window *window_find_by_id(u_int);
void window_update_activity(struct window *);
struct window *window_create(u_int, u_int);
struct window *window_create_spawn(const char *, int, char **, const char *,
       const char *, const char *, struct environ *,
       struct termios *, u_int, u_int, u_int, char **);
struct window_pane *window_get_active_at(struct window *, u_int, u_int);
struct window_pane *window_find_string(struct window *, const char *);
int window_has_pane(struct window *, struct window_pane *);
int window_set_active_pane(struct window *, struct window_pane *);
void window_redraw_active_switch(struct window *,
       struct window_pane *);
struct window_pane *window_add_pane(struct window *, struct window_pane *, int,
       int, u_int);
void window_resize(struct window *, u_int, u_int);
int window_zoom(struct window_pane *);
int window_unzoom(struct window *);
void window_lost_pane(struct window *, struct window_pane *);
void window_remove_pane(struct window *, struct window_pane *);
struct window_pane *window_pane_at_index(struct window *, u_int);
struct window_pane *window_pane_next_by_number(struct window *,
   struct window_pane *, u_int);
struct window_pane *window_pane_previous_by_number(struct window *,
   struct window_pane *, u_int);
int window_pane_index(struct window_pane *, u_int *);
u_int window_count_panes(struct window *);
void window_destroy_panes(struct window *);
struct window_pane *window_pane_find_by_id_str(const char *);
struct window_pane *window_pane_find_by_id(u_int);
int window_pane_destroy_ready(struct window_pane *);
int window_pane_spawn(struct window_pane *, int, char **,
       const char *, const char *, const char *, struct environ *,
       struct termios *, char **);
void window_pane_resize(struct window_pane *, u_int, u_int);
void window_pane_alternate_on(struct window_pane *,
       struct grid_cell *, int);
void window_pane_alternate_off(struct window_pane *,
       struct grid_cell *, int);
void window_pane_set_palette(struct window_pane *, u_int, int);
void window_pane_unset_palette(struct window_pane *, u_int);
void window_pane_reset_palette(struct window_pane *);
int window_pane_get_palette(const struct window_pane *, int);
int window_pane_set_mode(struct window_pane *,
       const struct window_mode *, struct cmd_find_state *,
       struct args *);
void window_pane_reset_mode(struct window_pane *);
void window_pane_key(struct window_pane *, struct client *,
       struct session *, key_code, struct mouse_event *);
int window_pane_visible(struct window_pane *);
u_int window_pane_search(struct window_pane *, const char *);
const char *window_printable_flags(struct winlink *);
struct window_pane *window_pane_find_up(struct window_pane *);
struct window_pane *window_pane_find_down(struct window_pane *);
struct window_pane *window_pane_find_left(struct window_pane *);
struct window_pane *window_pane_find_right(struct window_pane *);
void window_set_name(struct window *, const char *);
void window_add_ref(struct window *, const char *);
void window_remove_ref(struct window *, const char *);
void winlink_clear_flags(struct winlink *);
int winlink_shuffle_up(struct session *, struct winlink *);


u_int layout_count_cells(struct layout_cell *);
struct layout_cell *layout_create_cell(struct layout_cell *);
void layout_free_cell(struct layout_cell *);
void layout_print_cell(struct layout_cell *, const char *, u_int);
void layout_destroy_cell(struct window *, struct layout_cell *,
       struct layout_cell **);
void layout_set_size(struct layout_cell *, u_int, u_int, u_int,
       u_int);
void layout_make_leaf(struct layout_cell *, struct window_pane *);
void layout_make_node(struct layout_cell *, enum layout_type);
void layout_fix_offsets(struct layout_cell *);
void layout_fix_panes(struct window *, u_int, u_int);
void layout_resize_adjust(struct window *, struct layout_cell *,
       enum layout_type, int);
void layout_init(struct window *, struct window_pane *);
void layout_free(struct window *);
void layout_resize(struct window *, u_int, u_int);
void layout_resize_pane(struct window_pane *, enum layout_type,
       int, int);
void layout_resize_pane_to(struct window_pane *, enum layout_type,
       u_int);
void layout_assign_pane(struct layout_cell *, struct window_pane *);
struct layout_cell *layout_split_pane(struct window_pane *, enum layout_type,
       int, int, int);
void layout_close_pane(struct window_pane *);
int layout_spread_cell(struct window *, struct layout_cell *);
void layout_spread_out(struct window_pane *);


char *layout_dump(struct layout_cell *);
int layout_parse(struct window *, const char *);


int layout_set_lookup(const char *);
u_int layout_set_select(struct window *, u_int);
u_int layout_set_next(struct window *);
u_int layout_set_previous(struct window *);


typedef void (*mode_tree_build_cb)(void *, u_int, uint64_t *, const char *);
typedef void (*mode_tree_draw_cb)(void *, void *, struct screen_write_ctx *,
    u_int, u_int);
typedef int (*mode_tree_search_cb)(void *, void *, const char *);
typedef void (*mode_tree_each_cb)(void *, void *, struct client *, key_code);
u_int mode_tree_count_tagged(struct mode_tree_data *);
void *mode_tree_get_current(struct mode_tree_data *);
void mode_tree_expand_current(struct mode_tree_data *);
void mode_tree_set_current(struct mode_tree_data *, uint64_t);
void mode_tree_each_tagged(struct mode_tree_data *, mode_tree_each_cb,
      struct client *, key_code, int);
void mode_tree_up(struct mode_tree_data *, int);
void mode_tree_down(struct mode_tree_data *, int);
struct mode_tree_data *mode_tree_start(struct window_pane *, struct args *,
      mode_tree_build_cb, mode_tree_draw_cb, mode_tree_search_cb,
      void *, const char **, u_int, struct screen **);
void mode_tree_zoom(struct mode_tree_data *, struct args *);
void mode_tree_build(struct mode_tree_data *);
void mode_tree_free(struct mode_tree_data *);
void mode_tree_resize(struct mode_tree_data *, u_int, u_int);
struct mode_tree_item *mode_tree_add(struct mode_tree_data *,
      struct mode_tree_item *, void *, uint64_t, const char *,
      const char *, int);
void mode_tree_remove(struct mode_tree_data *, struct mode_tree_item *);
void mode_tree_draw(struct mode_tree_data *);
int mode_tree_key(struct mode_tree_data *, struct client *, key_code *,
      struct mouse_event *, u_int *, u_int *);
void mode_tree_run_command(struct client *, struct cmd_find_state *,
      const char *, const char *);


extern const struct window_mode window_buffer_mode;


extern const struct window_mode window_tree_mode;


extern const struct window_mode window_clock_mode;
extern const char window_clock_table[14][5][5];


extern const struct window_mode window_client_mode;


extern const struct window_mode window_copy_mode;
void window_copy_init_from_pane(struct window_pane *, int);
void window_copy_init_for_output(struct window_pane *);
void window_copy_add(struct window_pane *, const char *, ...);
void window_copy_vadd(struct window_pane *, const char *, va_list);
void window_copy_pageup(struct window_pane *, int);
void window_copy_start_drag(struct client *, struct mouse_event *);
void window_copy_add_formats(struct window_pane *,
       struct format_tree *);


void check_window_name(struct window *);
char *default_window_name(struct window *);
char *parse_window_name(const char *);


void control_callback(struct client *, int, void *);
void control_write(struct client *, const char *, ...);
void control_write_buffer(struct client *, struct evbuffer *);


void control_notify_input(struct client *, struct window_pane *,
     struct evbuffer *);
void control_notify_pane_mode_changed(int);
void control_notify_window_layout_changed(struct window *);
void control_notify_window_pane_changed(struct window *);
void control_notify_window_unlinked(struct session *, struct window *);
void control_notify_window_linked(struct session *, struct window *);
void control_notify_window_renamed(struct window *);
void control_notify_client_session_changed(struct client *);
void control_notify_session_renamed(struct session *);
void control_notify_session_created(struct session *);
void control_notify_session_closed(struct session *);
void control_notify_session_window_changed(struct session *);


extern struct sessions sessions;
extern struct session_groups session_groups;
int session_cmp(struct session *, struct session *);
 void sessions_RB_INSERT_COLOR(struct sessions *, struct session *); void sessions_RB_REMOVE_COLOR(struct sessions *, struct session *, struct session *); struct session *sessions_RB_REMOVE(struct sessions *, struct session *); struct session *sessions_RB_INSERT(struct sessions *, struct session *); struct session *sessions_RB_FIND(struct sessions *, struct session *); struct session *sessions_RB_NFIND(struct sessions *, struct session *); struct session *sessions_RB_NEXT(struct session *); struct session *sessions_RB_PREV(struct session *); struct session *sessions_RB_MINMAX(struct sessions *, int);;
int session_group_cmp(struct session_group *, struct session_group *);
 void session_groups_RB_INSERT_COLOR(struct session_groups *, struct session_group *); void session_groups_RB_REMOVE_COLOR(struct session_groups *, struct session_group *, struct session_group *); struct session_group *session_groups_RB_REMOVE(struct session_groups *, struct session_group *); struct session_group *session_groups_RB_INSERT(struct session_groups *, struct session_group *); struct session_group *session_groups_RB_FIND(struct session_groups *, struct session_group *); struct session_group *session_groups_RB_NFIND(struct session_groups *, struct session_group *); struct session_group *session_groups_RB_NEXT(struct session_group *); struct session_group *session_groups_RB_PREV(struct session_group *); struct session_group *session_groups_RB_MINMAX(struct session_groups *, int);;
int session_alive(struct session *);
struct session *session_find(const char *);
struct session *session_find_by_id_str(const char *);
struct session *session_find_by_id(u_int);
struct session *session_create(const char *, const char *, int, char **,
       const char *, const char *, struct environ *,
       struct termios *, int, u_int, u_int, char **);
void session_destroy(struct session *, const char *);
void session_add_ref(struct session *, const char *);
void session_remove_ref(struct session *, const char *);
int session_check_name(const char *);
void session_update_activity(struct session *, struct timeval *);
struct session *session_next_session(struct session *);
struct session *session_previous_session(struct session *);
struct winlink *session_new(struct session *, const char *, int, char **,
       const char *, const char *, int, char **);
struct winlink *session_attach(struct session *, struct window *, int,
       char **);
int session_detach(struct session *, struct winlink *);
int session_has(struct session *, struct window *);
int session_is_linked(struct session *, struct window *);
int session_next(struct session *, int);
int session_previous(struct session *, int);
int session_select(struct session *, int);
int session_last(struct session *);
int session_set_current(struct session *, struct winlink *);
struct session_group *session_group_contains(struct session *);
struct session_group *session_group_find(const char *);
struct session_group *session_group_new(const char *);
void session_group_add(struct session_group *, struct session *);
void session_group_synchronize_to(struct session *);
void session_group_synchronize_from(struct session *);
u_int session_group_count(struct session_group *);
void session_renumber_windows(struct session *);


void utf8_set(struct utf8_data *, u_char);
void utf8_copy(struct utf8_data *, const struct utf8_data *);
enum utf8_state utf8_open(struct utf8_data *, u_char);
enum utf8_state utf8_append(struct utf8_data *, u_char);
enum utf8_state utf8_combine(const struct utf8_data *, wchar_t *);
enum utf8_state utf8_split(wchar_t, struct utf8_data *);
int utf8_isvalid(const char *);
int utf8_strvis(char *, const char *, size_t, int);
int utf8_stravis(char **, const char *, int);
char *utf8_sanitize(const char *);
size_t utf8_strlen(const struct utf8_data *);
u_int utf8_strwidth(const struct utf8_data *, ssize_t);
struct utf8_data *utf8_fromcstr(const char *);
char *utf8_tocstr(struct utf8_data *);
u_int utf8_cstrwidth(const char *);
char *utf8_rtrimcstr(const char *, u_int);
char *utf8_trimcstr(const char *, u_int);
char *utf8_padcstr(const char *, u_int);


char *osdep_get_name(int, char *);
char *osdep_get_cwd(int);
struct event_base *osdep_event_init(void);


void log_add_level(void);
int log_get_level(void);
void log_open(const char *);
void log_toggle(const char *);
void log_close(void);
void log_debug(const char *, ...);
 void fatal(const char *, ...);
 void fatalx(const char *, ...);


int style_parse(const struct grid_cell *,
       struct grid_cell *, const char *);
const char *style_tostring(struct grid_cell *);
void style_apply(struct grid_cell *, struct options *,
       const char *);
void style_apply_update(struct grid_cell *, struct options *,
       const char *);
int style_equal(const struct grid_cell *,
       const struct grid_cell *);
# 32 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/format.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/variadic.h" 1



struct cmdq_item;
struct client;
struct environ;
struct format_tree;
struct hooks;
struct cmd_find_state;
struct options;
struct screen_write_ctx;
struct grid_cell;
struct window_pane;

void args_print_add(char **buf, size_t *len, const char *fmt, ...);
void cfg_add_cause(const char *fmt, ...);
void cmdq_format(struct cmdq_item *item, const char *key, const char *fmt, ...);
void cmdq_print(struct cmdq_item *item, const char *fmt, ...);
void cmdq_error(struct cmdq_item *item, const char *fmt, ...);
void control_write(struct client *c, const char *fmt, ...);
void environ_set(struct environ *env, const char *name, const char *fmt, ...);
void environ_log(struct environ *env, const char *fmt, ...);
void format_add(struct format_tree *ft, const char *key, const char *fmt, ...);
void hooks_insert(struct hooks *hooks, struct cmdq_item *item, struct cmd_find_state *fs, const char *fmt, ...);
void input_reply(struct input_ctx *, const char *, ...);
void log_debug(const char *msg, ...);
 void fatal(const char *msg, ...);
 void fatalx(const char *msg, ...);
struct options_entry *options_set_string(struct options *oo, const char *name, int append, const char *fmt, ...);
size_t screen_write_cstrlen(const char *fmt, ...);
size_t screen_write_strlen(const char *fmt, ...);
void screen_write_puts(struct screen_write_ctx *ctx, const struct grid_cell *gcp, const char *fmt, ...);
void screen_write_nputs(struct screen_write_ctx *ctx, ssize_t maxlen, const struct grid_cell *gcp, const char *fmt, ...);
void screen_write_cnputs(struct screen_write_ctx *ctx, ssize_t maxlen, const struct grid_cell *gcp, const char *fmt, ...);
void server_client_add_message(struct client *c, const char *fmt, ...);
void status_message_set(struct client *c, const char *fmt, ...);
void window_copy_add(struct window_pane *wp, const char *fmt, ...);
int xasprintf(char **ret, const char *fmt, ...);
int xsnprintf(char *str, size_t len, const char *fmt, ...);
void setproctitle( const char *fmt, ...);
# 33 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/format.c" 2






struct format_entry;
typedef void (*format_cb)(struct format_tree *, struct format_entry *);

static char *format_job_get(struct format_tree *, const char *);
static void format_job_timer(int, short, void *);

static char *format_find(struct format_tree *, const char *, int);
static void format_add_cb(struct format_tree *, const char *, format_cb);
static void format_add_tv(struct format_tree *, const char *,
       struct timeval *);
static int format_replace(struct format_tree *, const char *, size_t,
       char **, size_t *, size_t *);

static void format_defaults_session(struct format_tree *,
       struct session *);
static void format_defaults_client(struct format_tree *, struct client *);
static void format_defaults_winlink(struct format_tree *,
       struct winlink *);


struct format_job {
 struct client *client;
 u_int tag;
 const char *cmd;
 const char *expanded;

 time_t last;
 char *out;
 int updated;

 struct job *job;
 int status;

 struct { struct format_job *rbe_left; struct format_job *rbe_right; struct format_job *rbe_parent; int rbe_color; } entry;
};


static struct event format_job_event;
static int format_job_cmp(struct format_job *, struct format_job *);
static struct format_job_tree { struct format_job *rbh_root; } format_jobs = { 0 };
 static void format_job_tree_RB_INSERT_COLOR(struct format_job_tree *head, struct format_job *elm) { struct format_job *parent, *gparent, *tmp; while ((parent = (elm)->entry.rbe_parent) && (parent)->entry.rbe_color == 1) { gparent = (parent)->entry.rbe_parent; if (parent == (gparent)->entry.rbe_left) { tmp = (gparent)->entry.rbe_right; if (tmp && (tmp)->entry.rbe_color == 1) { (tmp)->entry.rbe_color = 0; do { (parent)->entry.rbe_color = 0; (gparent)->entry.rbe_color = 1; } while (0); elm = gparent; continue; } if ((parent)->entry.rbe_right == elm) { do { (tmp) = (parent)->entry.rbe_right; if (((parent)->entry.rbe_right = (tmp)->entry.rbe_left)) { ((tmp)->entry.rbe_left)->entry.rbe_parent = (parent); } do {} while (0); if (((tmp)->entry.rbe_parent = (parent)->entry.rbe_parent)) { if ((parent) == ((parent)->entry.rbe_parent)->entry.rbe_left) ((parent)->entry.rbe_parent)->entry.rbe_left = (tmp); else ((parent)->entry.rbe_parent)->entry.rbe_right = (tmp); } else (head)->rbh_root = (tmp); (tmp)->entry.rbe_left = (parent); (parent)->entry.rbe_parent = (tmp); do {} while (0); if (((tmp)->entry.rbe_parent)) do {} while (0); } while (0); tmp = parent; parent = elm; elm = tmp; } do { (parent)->entry.rbe_color = 0; (gparent)->entry.rbe_color = 1; } while (0); do { (tmp) = (gparent)->entry.rbe_left; if (((gparent)->entry.rbe_left = (tmp)->entry.rbe_right)) { ((tmp)->entry.rbe_right)->entry.rbe_parent = (gparent); } do {} while (0); if (((tmp)->entry.rbe_parent = (gparent)->entry.rbe_parent)) { if ((gparent) == ((gparent)->entry.rbe_parent)->entry.rbe_left) ((gparent)->entry.rbe_parent)->entry.rbe_left = (tmp); else ((gparent)->entry.rbe_parent)->entry.rbe_right = (tmp); } else (head)->rbh_root = (tmp); (tmp)->entry.rbe_right = (gparent); (gparent)->entry.rbe_parent = (tmp); do {} while (0); if (((tmp)->entry.rbe_parent)) do {} while (0); } while (0); } else { tmp = (gparent)->entry.rbe_left; if (tmp && (tmp)->entry.rbe_color == 1) { (tmp)->entry.rbe_color = 0; do { (parent)->entry.rbe_color = 0; (gparent)->entry.rbe_color = 1; } while (0); elm = gparent; continue; } if ((parent)->entry.rbe_left == elm) { do { (tmp) = (parent)->entry.rbe_left; if (((parent)->entry.rbe_left = (tmp)->entry.rbe_right)) { ((tmp)->entry.rbe_right)->entry.rbe_parent = (parent); } do {} while (0); if (((tmp)->entry.rbe_parent = (parent)->entry.rbe_parent)) { if ((parent) == ((parent)->entry.rbe_parent)->entry.rbe_left) ((parent)->entry.rbe_parent)->entry.rbe_left = (tmp); else ((parent)->entry.rbe_parent)->entry.rbe_right = (tmp); } else (head)->rbh_root = (tmp); (tmp)->entry.rbe_right = (parent); (parent)->entry.rbe_parent = (tmp); do {} while (0); if (((tmp)->entry.rbe_parent)) do {} while (0); } while (0); tmp = parent; parent = elm; elm = tmp; } do { (parent)->entry.rbe_color = 0; (gparent)->entry.rbe_color = 1; } while (0); do { (tmp) = (gparent)->entry.rbe_right; if (((gparent)->entry.rbe_right = (tmp)->entry.rbe_left)) { ((tmp)->entry.rbe_left)->entry.rbe_parent = (gparent); } do {} while (0); if (((tmp)->entry.rbe_parent = (gparent)->entry.rbe_parent)) { if ((gparent) == ((gparent)->entry.rbe_parent)->entry.rbe_left) ((gparent)->entry.rbe_parent)->entry.rbe_left = (tmp); else ((gparent)->entry.rbe_parent)->entry.rbe_right = (tmp); } else (head)->rbh_root = (tmp); (tmp)->entry.rbe_left = (gparent); (gparent)->entry.rbe_parent = (tmp); do {} while (0); if (((tmp)->entry.rbe_parent)) do {} while (0); } while (0); } } (head->rbh_root)->entry.rbe_color = 0; } static void format_job_tree_RB_REMOVE_COLOR(struct format_job_tree *head, struct format_job *parent, struct format_job *elm) { struct format_job *tmp; while ((elm == 0 || (elm)->entry.rbe_color == 0) && elm != (head)->rbh_root) { if ((parent)->entry.rbe_left == elm) { tmp = (parent)->entry.rbe_right; if ((tmp)->entry.rbe_color == 1) { do { (tmp)->entry.rbe_color = 0; (parent)->entry.rbe_color = 1; } while (0); do { (tmp) = (parent)->entry.rbe_right; if (((parent)->entry.rbe_right = (tmp)->entry.rbe_left)) { ((tmp)->entry.rbe_left)->entry.rbe_parent = (parent); } do {} while (0); if (((tmp)->entry.rbe_parent = (parent)->entry.rbe_parent)) { if ((parent) == ((parent)->entry.rbe_parent)->entry.rbe_left) ((parent)->entry.rbe_parent)->entry.rbe_left = (tmp); else ((parent)->entry.rbe_parent)->entry.rbe_right = (tmp); } else (head)->rbh_root = (tmp); (tmp)->entry.rbe_left = (parent); (parent)->entry.rbe_parent = (tmp); do {} while (0); if (((tmp)->entry.rbe_parent)) do {} while (0); } while (0); tmp = (parent)->entry.rbe_right; } if (((tmp)->entry.rbe_left == 0 || ((tmp)->entry.rbe_left)->entry.rbe_color == 0) && ((tmp)->entry.rbe_right == 0 || ((tmp)->entry.rbe_right)->entry.rbe_color == 0)) { (tmp)->entry.rbe_color = 1; elm = parent; parent = (elm)->entry.rbe_parent; } else { if ((tmp)->entry.rbe_right == 0 || ((tmp)->entry.rbe_right)->entry.rbe_color == 0) { struct format_job *oleft; if ((oleft = (tmp)->entry.rbe_left)) (oleft)->entry.rbe_color = 0; (tmp)->entry.rbe_color = 1; do { (oleft) = (tmp)->entry.rbe_left; if (((tmp)->entry.rbe_left = (oleft)->entry.rbe_right)) { ((oleft)->entry.rbe_right)->entry.rbe_parent = (tmp); } do {} while (0); if (((oleft)->entry.rbe_parent = (tmp)->entry.rbe_parent)) { if ((tmp) == ((tmp)->entry.rbe_parent)->entry.rbe_left) ((tmp)->entry.rbe_parent)->entry.rbe_left = (oleft); else ((tmp)->entry.rbe_parent)->entry.rbe_right = (oleft); } else (head)->rbh_root = (oleft); (oleft)->entry.rbe_right = (tmp); (tmp)->entry.rbe_parent = (oleft); do {} while (0); if (((oleft)->entry.rbe_parent)) do {} while (0); } while (0); tmp = (parent)->entry.rbe_right; } (tmp)->entry.rbe_color = (parent)->entry.rbe_color; (parent)->entry.rbe_color = 0; if ((tmp)->entry.rbe_right) ((tmp)->entry.rbe_right)->entry.rbe_color = 0; do { (tmp) = (parent)->entry.rbe_right; if (((parent)->entry.rbe_right = (tmp)->entry.rbe_left)) { ((tmp)->entry.rbe_left)->entry.rbe_parent = (parent); } do {} while (0); if (((tmp)->entry.rbe_parent = (parent)->entry.rbe_parent)) { if ((parent) == ((parent)->entry.rbe_parent)->entry.rbe_left) ((parent)->entry.rbe_parent)->entry.rbe_left = (tmp); else ((parent)->entry.rbe_parent)->entry.rbe_right = (tmp); } else (head)->rbh_root = (tmp); (tmp)->entry.rbe_left = (parent); (parent)->entry.rbe_parent = (tmp); do {} while (0); if (((tmp)->entry.rbe_parent)) do {} while (0); } while (0); elm = (head)->rbh_root; break; } } else { tmp = (parent)->entry.rbe_left; if ((tmp)->entry.rbe_color == 1) { do { (tmp)->entry.rbe_color = 0; (parent)->entry.rbe_color = 1; } while (0); do { (tmp) = (parent)->entry.rbe_left; if (((parent)->entry.rbe_left = (tmp)->entry.rbe_right)) { ((tmp)->entry.rbe_right)->entry.rbe_parent = (parent); } do {} while (0); if (((tmp)->entry.rbe_parent = (parent)->entry.rbe_parent)) { if ((parent) == ((parent)->entry.rbe_parent)->entry.rbe_left) ((parent)->entry.rbe_parent)->entry.rbe_left = (tmp); else ((parent)->entry.rbe_parent)->entry.rbe_right = (tmp); } else (head)->rbh_root = (tmp); (tmp)->entry.rbe_right = (parent); (parent)->entry.rbe_parent = (tmp); do {} while (0); if (((tmp)->entry.rbe_parent)) do {} while (0); } while (0); tmp = (parent)->entry.rbe_left; } if (((tmp)->entry.rbe_left == 0 || ((tmp)->entry.rbe_left)->entry.rbe_color == 0) && ((tmp)->entry.rbe_right == 0 || ((tmp)->entry.rbe_right)->entry.rbe_color == 0)) { (tmp)->entry.rbe_color = 1; elm = parent; parent = (elm)->entry.rbe_parent; } else { if ((tmp)->entry.rbe_left == 0 || ((tmp)->entry.rbe_left)->entry.rbe_color == 0) { struct format_job *oright; if ((oright = (tmp)->entry.rbe_right)) (oright)->entry.rbe_color = 0; (tmp)->entry.rbe_color = 1; do { (oright) = (tmp)->entry.rbe_right; if (((tmp)->entry.rbe_right = (oright)->entry.rbe_left)) { ((oright)->entry.rbe_left)->entry.rbe_parent = (tmp); } do {} while (0); if (((oright)->entry.rbe_parent = (tmp)->entry.rbe_parent)) { if ((tmp) == ((tmp)->entry.rbe_parent)->entry.rbe_left) ((tmp)->entry.rbe_parent)->entry.rbe_left = (oright); else ((tmp)->entry.rbe_parent)->entry.rbe_right = (oright); } else (head)->rbh_root = (oright); (oright)->entry.rbe_left = (tmp); (tmp)->entry.rbe_parent = (oright); do {} while (0); if (((oright)->entry.rbe_parent)) do {} while (0); } while (0); tmp = (parent)->entry.rbe_left; } (tmp)->entry.rbe_color = (parent)->entry.rbe_color; (parent)->entry.rbe_color = 0; if ((tmp)->entry.rbe_left) ((tmp)->entry.rbe_left)->entry.rbe_color = 0; do { (tmp) = (parent)->entry.rbe_left; if (((parent)->entry.rbe_left = (tmp)->entry.rbe_right)) { ((tmp)->entry.rbe_right)->entry.rbe_parent = (parent); } do {} while (0); if (((tmp)->entry.rbe_parent = (parent)->entry.rbe_parent)) { if ((parent) == ((parent)->entry.rbe_parent)->entry.rbe_left) ((parent)->entry.rbe_parent)->entry.rbe_left = (tmp); else ((parent)->entry.rbe_parent)->entry.rbe_right = (tmp); } else (head)->rbh_root = (tmp); (tmp)->entry.rbe_right = (parent); (parent)->entry.rbe_parent = (tmp); do {} while (0); if (((tmp)->entry.rbe_parent)) do {} while (0); } while (0); elm = (head)->rbh_root; break; } } } if (elm) (elm)->entry.rbe_color = 0; } static struct format_job * format_job_tree_RB_REMOVE(struct format_job_tree *head, struct format_job *elm) { struct format_job *child, *parent, *old = elm; int color; if ((elm)->entry.rbe_left == 0) child = (elm)->entry.rbe_right; else if ((elm)->entry.rbe_right == 0) child = (elm)->entry.rbe_left; else { struct format_job *left; elm = (elm)->entry.rbe_right; while ((left = (elm)->entry.rbe_left)) elm = left; child = (elm)->entry.rbe_right; parent = (elm)->entry.rbe_parent; color = (elm)->entry.rbe_color; if (child) (child)->entry.rbe_parent = parent; if (parent) { if ((parent)->entry.rbe_left == elm) (parent)->entry.rbe_left = child; else (parent)->entry.rbe_right = child; do {} while (0); } else (head)->rbh_root = child; if ((elm)->entry.rbe_parent == old) parent = elm; (elm)->entry = (old)->entry; if ((old)->entry.rbe_parent) { if (((old)->entry.rbe_parent)->entry.rbe_left == old) ((old)->entry.rbe_parent)->entry.rbe_left = elm; else ((old)->entry.rbe_parent)->entry.rbe_right = elm; do {} while (0); } else (head)->rbh_root = elm; ((old)->entry.rbe_left)->entry.rbe_parent = elm; if ((old)->entry.rbe_right) ((old)->entry.rbe_right)->entry.rbe_parent = elm; if (parent) { left = parent; do { do {} while (0); } while ((left = (left)->entry.rbe_parent)); } goto color; } parent = (elm)->entry.rbe_parent; color = (elm)->entry.rbe_color; if (child) (child)->entry.rbe_parent = parent; if (parent) { if ((parent)->entry.rbe_left == elm) (parent)->entry.rbe_left = child; else (parent)->entry.rbe_right = child; do {} while (0); } else (head)->rbh_root = child; color: if (color == 0) format_job_tree_RB_REMOVE_COLOR(head, parent, child); return (old); } static struct format_job * format_job_tree_RB_INSERT(struct format_job_tree *head, struct format_job *elm) { struct format_job *tmp; struct format_job *parent = 0; int comp = 0; tmp = (head)->rbh_root; while (tmp) { parent = tmp; comp = (format_job_cmp)(elm, parent); if (comp < 0) tmp = (tmp)->entry.rbe_left; else if (comp > 0) tmp = (tmp)->entry.rbe_right; else return (tmp); } do { (elm)->entry.rbe_parent = parent; (elm)->entry.rbe_left = (elm)->entry.rbe_right = 0; (elm)->entry.rbe_color = 1; } while (0); if (parent != 0) { if (comp < 0) (parent)->entry.rbe_left = elm; else (parent)->entry.rbe_right = elm; do {} while (0); } else (head)->rbh_root = elm; format_job_tree_RB_INSERT_COLOR(head, elm); return (0); } static struct format_job * format_job_tree_RB_FIND(struct format_job_tree *head, struct format_job *elm) { struct format_job *tmp = (head)->rbh_root; int comp; while (tmp) { comp = format_job_cmp(elm, tmp); if (comp < 0) tmp = (tmp)->entry.rbe_left; else if (comp > 0) tmp = (tmp)->entry.rbe_right; else return (tmp); } return (0); } static struct format_job * format_job_tree_RB_NFIND(struct format_job_tree *head, struct format_job *elm) { struct format_job *tmp = (head)->rbh_root; struct format_job *res = 0; int comp; while (tmp) { comp = format_job_cmp(elm, tmp); if (comp < 0) { res = tmp; tmp = (tmp)->entry.rbe_left; } else if (comp > 0) tmp = (tmp)->entry.rbe_right; else return (tmp); } return (res); } static struct format_job * format_job_tree_RB_NEXT(struct format_job *elm) { if ((elm)->entry.rbe_right) { elm = (elm)->entry.rbe_right; while ((elm)->entry.rbe_left) elm = (elm)->entry.rbe_left; } else { if ((elm)->entry.rbe_parent && (elm == ((elm)->entry.rbe_parent)->entry.rbe_left)) elm = (elm)->entry.rbe_parent; else { while ((elm)->entry.rbe_parent && (elm == ((elm)->entry.rbe_parent)->entry.rbe_right)) elm = (elm)->entry.rbe_parent; elm = (elm)->entry.rbe_parent; } } return (elm); } static struct format_job * format_job_tree_RB_PREV(struct format_job *elm) { if ((elm)->entry.rbe_left) { elm = (elm)->entry.rbe_left; while ((elm)->entry.rbe_right) elm = (elm)->entry.rbe_right; } else { if ((elm)->entry.rbe_parent && (elm == ((elm)->entry.rbe_parent)->entry.rbe_right)) elm = (elm)->entry.rbe_parent; else { while ((elm)->entry.rbe_parent && (elm == ((elm)->entry.rbe_parent)->entry.rbe_left)) elm = (elm)->entry.rbe_parent; elm = (elm)->entry.rbe_parent; } } return (elm); } static struct format_job * format_job_tree_RB_MINMAX(struct format_job_tree *head, int val) { struct format_job *tmp = (head)->rbh_root; struct format_job *parent = 0; while (tmp) { parent = tmp; if (val < 0) tmp = (tmp)->entry.rbe_left; else tmp = (tmp)->entry.rbe_right; } return (parent); };


static int
format_job_cmp(struct format_job *fj1, struct format_job *fj2)
{
 if (fj1->tag < fj2->tag)
  return (-1);
 if (fj1->tag > fj2->tag)
  return (1);
 return (strcmp(fj1->cmd, fj2->cmd));
}
# 99 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/format.c"
struct format_entry {
 char *key;
 char *value;
 time_t t;
 format_cb cb;
 struct { struct format_entry *rbe_left; struct format_entry *rbe_right; struct format_entry *rbe_parent; int rbe_color; } entry;
};


struct format_tree {
 struct window *w;
 struct winlink *wl;
 struct session *s;
 struct window_pane *wp;

 struct client *client;
 u_int tag;
 int flags;

 struct format_entry_tree { struct format_entry *rbh_root; } tree;
};
static int format_entry_cmp(struct format_entry *, struct format_entry *);
 void format_entry_tree_RB_INSERT_COLOR(struct format_entry_tree *head, struct format_entry *elm) { struct format_entry *parent, *gparent, *tmp; while ((parent = (elm)->entry.rbe_parent) && (parent)->entry.rbe_color == 1) { gparent = (parent)->entry.rbe_parent; if (parent == (gparent)->entry.rbe_left) { tmp = (gparent)->entry.rbe_right; if (tmp && (tmp)->entry.rbe_color == 1) { (tmp)->entry.rbe_color = 0; do { (parent)->entry.rbe_color = 0; (gparent)->entry.rbe_color = 1; } while (0); elm = gparent; continue; } if ((parent)->entry.rbe_right == elm) { do { (tmp) = (parent)->entry.rbe_right; if (((parent)->entry.rbe_right = (tmp)->entry.rbe_left)) { ((tmp)->entry.rbe_left)->entry.rbe_parent = (parent); } do {} while (0); if (((tmp)->entry.rbe_parent = (parent)->entry.rbe_parent)) { if ((parent) == ((parent)->entry.rbe_parent)->entry.rbe_left) ((parent)->entry.rbe_parent)->entry.rbe_left = (tmp); else ((parent)->entry.rbe_parent)->entry.rbe_right = (tmp); } else (head)->rbh_root = (tmp); (tmp)->entry.rbe_left = (parent); (parent)->entry.rbe_parent = (tmp); do {} while (0); if (((tmp)->entry.rbe_parent)) do {} while (0); } while (0); tmp = parent; parent = elm; elm = tmp; } do { (parent)->entry.rbe_color = 0; (gparent)->entry.rbe_color = 1; } while (0); do { (tmp) = (gparent)->entry.rbe_left; if (((gparent)->entry.rbe_left = (tmp)->entry.rbe_right)) { ((tmp)->entry.rbe_right)->entry.rbe_parent = (gparent); } do {} while (0); if (((tmp)->entry.rbe_parent = (gparent)->entry.rbe_parent)) { if ((gparent) == ((gparent)->entry.rbe_parent)->entry.rbe_left) ((gparent)->entry.rbe_parent)->entry.rbe_left = (tmp); else ((gparent)->entry.rbe_parent)->entry.rbe_right = (tmp); } else (head)->rbh_root = (tmp); (tmp)->entry.rbe_right = (gparent); (gparent)->entry.rbe_parent = (tmp); do {} while (0); if (((tmp)->entry.rbe_parent)) do {} while (0); } while (0); } else { tmp = (gparent)->entry.rbe_left; if (tmp && (tmp)->entry.rbe_color == 1) { (tmp)->entry.rbe_color = 0; do { (parent)->entry.rbe_color = 0; (gparent)->entry.rbe_color = 1; } while (0); elm = gparent; continue; } if ((parent)->entry.rbe_left == elm) { do { (tmp) = (parent)->entry.rbe_left; if (((parent)->entry.rbe_left = (tmp)->entry.rbe_right)) { ((tmp)->entry.rbe_right)->entry.rbe_parent = (parent); } do {} while (0); if (((tmp)->entry.rbe_parent = (parent)->entry.rbe_parent)) { if ((parent) == ((parent)->entry.rbe_parent)->entry.rbe_left) ((parent)->entry.rbe_parent)->entry.rbe_left = (tmp); else ((parent)->entry.rbe_parent)->entry.rbe_right = (tmp); } else (head)->rbh_root = (tmp); (tmp)->entry.rbe_right = (parent); (parent)->entry.rbe_parent = (tmp); do {} while (0); if (((tmp)->entry.rbe_parent)) do {} while (0); } while (0); tmp = parent; parent = elm; elm = tmp; } do { (parent)->entry.rbe_color = 0; (gparent)->entry.rbe_color = 1; } while (0); do { (tmp) = (gparent)->entry.rbe_right; if (((gparent)->entry.rbe_right = (tmp)->entry.rbe_left)) { ((tmp)->entry.rbe_left)->entry.rbe_parent = (gparent); } do {} while (0); if (((tmp)->entry.rbe_parent = (gparent)->entry.rbe_parent)) { if ((gparent) == ((gparent)->entry.rbe_parent)->entry.rbe_left) ((gparent)->entry.rbe_parent)->entry.rbe_left = (tmp); else ((gparent)->entry.rbe_parent)->entry.rbe_right = (tmp); } else (head)->rbh_root = (tmp); (tmp)->entry.rbe_left = (gparent); (gparent)->entry.rbe_parent = (tmp); do {} while (0); if (((tmp)->entry.rbe_parent)) do {} while (0); } while (0); } } (head->rbh_root)->entry.rbe_color = 0; } void format_entry_tree_RB_REMOVE_COLOR(struct format_entry_tree *head, struct format_entry *parent, struct format_entry *elm) { struct format_entry *tmp; while ((elm == 0 || (elm)->entry.rbe_color == 0) && elm != (head)->rbh_root) { if ((parent)->entry.rbe_left == elm) { tmp = (parent)->entry.rbe_right; if ((tmp)->entry.rbe_color == 1) { do { (tmp)->entry.rbe_color = 0; (parent)->entry.rbe_color = 1; } while (0); do { (tmp) = (parent)->entry.rbe_right; if (((parent)->entry.rbe_right = (tmp)->entry.rbe_left)) { ((tmp)->entry.rbe_left)->entry.rbe_parent = (parent); } do {} while (0); if (((tmp)->entry.rbe_parent = (parent)->entry.rbe_parent)) { if ((parent) == ((parent)->entry.rbe_parent)->entry.rbe_left) ((parent)->entry.rbe_parent)->entry.rbe_left = (tmp); else ((parent)->entry.rbe_parent)->entry.rbe_right = (tmp); } else (head)->rbh_root = (tmp); (tmp)->entry.rbe_left = (parent); (parent)->entry.rbe_parent = (tmp); do {} while (0); if (((tmp)->entry.rbe_parent)) do {} while (0); } while (0); tmp = (parent)->entry.rbe_right; } if (((tmp)->entry.rbe_left == 0 || ((tmp)->entry.rbe_left)->entry.rbe_color == 0) && ((tmp)->entry.rbe_right == 0 || ((tmp)->entry.rbe_right)->entry.rbe_color == 0)) { (tmp)->entry.rbe_color = 1; elm = parent; parent = (elm)->entry.rbe_parent; } else { if ((tmp)->entry.rbe_right == 0 || ((tmp)->entry.rbe_right)->entry.rbe_color == 0) { struct format_entry *oleft; if ((oleft = (tmp)->entry.rbe_left)) (oleft)->entry.rbe_color = 0; (tmp)->entry.rbe_color = 1; do { (oleft) = (tmp)->entry.rbe_left; if (((tmp)->entry.rbe_left = (oleft)->entry.rbe_right)) { ((oleft)->entry.rbe_right)->entry.rbe_parent = (tmp); } do {} while (0); if (((oleft)->entry.rbe_parent = (tmp)->entry.rbe_parent)) { if ((tmp) == ((tmp)->entry.rbe_parent)->entry.rbe_left) ((tmp)->entry.rbe_parent)->entry.rbe_left = (oleft); else ((tmp)->entry.rbe_parent)->entry.rbe_right = (oleft); } else (head)->rbh_root = (oleft); (oleft)->entry.rbe_right = (tmp); (tmp)->entry.rbe_parent = (oleft); do {} while (0); if (((oleft)->entry.rbe_parent)) do {} while (0); } while (0); tmp = (parent)->entry.rbe_right; } (tmp)->entry.rbe_color = (parent)->entry.rbe_color; (parent)->entry.rbe_color = 0; if ((tmp)->entry.rbe_right) ((tmp)->entry.rbe_right)->entry.rbe_color = 0; do { (tmp) = (parent)->entry.rbe_right; if (((parent)->entry.rbe_right = (tmp)->entry.rbe_left)) { ((tmp)->entry.rbe_left)->entry.rbe_parent = (parent); } do {} while (0); if (((tmp)->entry.rbe_parent = (parent)->entry.rbe_parent)) { if ((parent) == ((parent)->entry.rbe_parent)->entry.rbe_left) ((parent)->entry.rbe_parent)->entry.rbe_left = (tmp); else ((parent)->entry.rbe_parent)->entry.rbe_right = (tmp); } else (head)->rbh_root = (tmp); (tmp)->entry.rbe_left = (parent); (parent)->entry.rbe_parent = (tmp); do {} while (0); if (((tmp)->entry.rbe_parent)) do {} while (0); } while (0); elm = (head)->rbh_root; break; } } else { tmp = (parent)->entry.rbe_left; if ((tmp)->entry.rbe_color == 1) { do { (tmp)->entry.rbe_color = 0; (parent)->entry.rbe_color = 1; } while (0); do { (tmp) = (parent)->entry.rbe_left; if (((parent)->entry.rbe_left = (tmp)->entry.rbe_right)) { ((tmp)->entry.rbe_right)->entry.rbe_parent = (parent); } do {} while (0); if (((tmp)->entry.rbe_parent = (parent)->entry.rbe_parent)) { if ((parent) == ((parent)->entry.rbe_parent)->entry.rbe_left) ((parent)->entry.rbe_parent)->entry.rbe_left = (tmp); else ((parent)->entry.rbe_parent)->entry.rbe_right = (tmp); } else (head)->rbh_root = (tmp); (tmp)->entry.rbe_right = (parent); (parent)->entry.rbe_parent = (tmp); do {} while (0); if (((tmp)->entry.rbe_parent)) do {} while (0); } while (0); tmp = (parent)->entry.rbe_left; } if (((tmp)->entry.rbe_left == 0 || ((tmp)->entry.rbe_left)->entry.rbe_color == 0) && ((tmp)->entry.rbe_right == 0 || ((tmp)->entry.rbe_right)->entry.rbe_color == 0)) { (tmp)->entry.rbe_color = 1; elm = parent; parent = (elm)->entry.rbe_parent; } else { if ((tmp)->entry.rbe_left == 0 || ((tmp)->entry.rbe_left)->entry.rbe_color == 0) { struct format_entry *oright; if ((oright = (tmp)->entry.rbe_right)) (oright)->entry.rbe_color = 0; (tmp)->entry.rbe_color = 1; do { (oright) = (tmp)->entry.rbe_right; if (((tmp)->entry.rbe_right = (oright)->entry.rbe_left)) { ((oright)->entry.rbe_left)->entry.rbe_parent = (tmp); } do {} while (0); if (((oright)->entry.rbe_parent = (tmp)->entry.rbe_parent)) { if ((tmp) == ((tmp)->entry.rbe_parent)->entry.rbe_left) ((tmp)->entry.rbe_parent)->entry.rbe_left = (oright); else ((tmp)->entry.rbe_parent)->entry.rbe_right = (oright); } else (head)->rbh_root = (oright); (oright)->entry.rbe_left = (tmp); (tmp)->entry.rbe_parent = (oright); do {} while (0); if (((oright)->entry.rbe_parent)) do {} while (0); } while (0); tmp = (parent)->entry.rbe_left; } (tmp)->entry.rbe_color = (parent)->entry.rbe_color; (parent)->entry.rbe_color = 0; if ((tmp)->entry.rbe_left) ((tmp)->entry.rbe_left)->entry.rbe_color = 0; do { (tmp) = (parent)->entry.rbe_left; if (((parent)->entry.rbe_left = (tmp)->entry.rbe_right)) { ((tmp)->entry.rbe_right)->entry.rbe_parent = (parent); } do {} while (0); if (((tmp)->entry.rbe_parent = (parent)->entry.rbe_parent)) { if ((parent) == ((parent)->entry.rbe_parent)->entry.rbe_left) ((parent)->entry.rbe_parent)->entry.rbe_left = (tmp); else ((parent)->entry.rbe_parent)->entry.rbe_right = (tmp); } else (head)->rbh_root = (tmp); (tmp)->entry.rbe_right = (parent); (parent)->entry.rbe_parent = (tmp); do {} while (0); if (((tmp)->entry.rbe_parent)) do {} while (0); } while (0); elm = (head)->rbh_root; break; } } } if (elm) (elm)->entry.rbe_color = 0; } struct format_entry * format_entry_tree_RB_REMOVE(struct format_entry_tree *head, struct format_entry *elm) { struct format_entry *child, *parent, *old = elm; int color; if ((elm)->entry.rbe_left == 0) child = (elm)->entry.rbe_right; else if ((elm)->entry.rbe_right == 0) child = (elm)->entry.rbe_left; else { struct format_entry *left; elm = (elm)->entry.rbe_right; while ((left = (elm)->entry.rbe_left)) elm = left; child = (elm)->entry.rbe_right; parent = (elm)->entry.rbe_parent; color = (elm)->entry.rbe_color; if (child) (child)->entry.rbe_parent = parent; if (parent) { if ((parent)->entry.rbe_left == elm) (parent)->entry.rbe_left = child; else (parent)->entry.rbe_right = child; do {} while (0); } else (head)->rbh_root = child; if ((elm)->entry.rbe_parent == old) parent = elm; (elm)->entry = (old)->entry; if ((old)->entry.rbe_parent) { if (((old)->entry.rbe_parent)->entry.rbe_left == old) ((old)->entry.rbe_parent)->entry.rbe_left = elm; else ((old)->entry.rbe_parent)->entry.rbe_right = elm; do {} while (0); } else (head)->rbh_root = elm; ((old)->entry.rbe_left)->entry.rbe_parent = elm; if ((old)->entry.rbe_right) ((old)->entry.rbe_right)->entry.rbe_parent = elm; if (parent) { left = parent; do { do {} while (0); } while ((left = (left)->entry.rbe_parent)); } goto color; } parent = (elm)->entry.rbe_parent; color = (elm)->entry.rbe_color; if (child) (child)->entry.rbe_parent = parent; if (parent) { if ((parent)->entry.rbe_left == elm) (parent)->entry.rbe_left = child; else (parent)->entry.rbe_right = child; do {} while (0); } else (head)->rbh_root = child; color: if (color == 0) format_entry_tree_RB_REMOVE_COLOR(head, parent, child); return (old); } struct format_entry * format_entry_tree_RB_INSERT(struct format_entry_tree *head, struct format_entry *elm) { struct format_entry *tmp; struct format_entry *parent = 0; int comp = 0; tmp = (head)->rbh_root; while (tmp) { parent = tmp; comp = (format_entry_cmp)(elm, parent); if (comp < 0) tmp = (tmp)->entry.rbe_left; else if (comp > 0) tmp = (tmp)->entry.rbe_right; else return (tmp); } do { (elm)->entry.rbe_parent = parent; (elm)->entry.rbe_left = (elm)->entry.rbe_right = 0; (elm)->entry.rbe_color = 1; } while (0); if (parent != 0) { if (comp < 0) (parent)->entry.rbe_left = elm; else (parent)->entry.rbe_right = elm; do {} while (0); } else (head)->rbh_root = elm; format_entry_tree_RB_INSERT_COLOR(head, elm); return (0); } struct format_entry * format_entry_tree_RB_FIND(struct format_entry_tree *head, struct format_entry *elm) { struct format_entry *tmp = (head)->rbh_root; int comp; while (tmp) { comp = format_entry_cmp(elm, tmp); if (comp < 0) tmp = (tmp)->entry.rbe_left; else if (comp > 0) tmp = (tmp)->entry.rbe_right; else return (tmp); } return (0); } struct format_entry * format_entry_tree_RB_NFIND(struct format_entry_tree *head, struct format_entry *elm) { struct format_entry *tmp = (head)->rbh_root; struct format_entry *res = 0; int comp; while (tmp) { comp = format_entry_cmp(elm, tmp); if (comp < 0) { res = tmp; tmp = (tmp)->entry.rbe_left; } else if (comp > 0) tmp = (tmp)->entry.rbe_right; else return (tmp); } return (res); } struct format_entry * format_entry_tree_RB_NEXT(struct format_entry *elm) { if ((elm)->entry.rbe_right) { elm = (elm)->entry.rbe_right; while ((elm)->entry.rbe_left) elm = (elm)->entry.rbe_left; } else { if ((elm)->entry.rbe_parent && (elm == ((elm)->entry.rbe_parent)->entry.rbe_left)) elm = (elm)->entry.rbe_parent; else { while ((elm)->entry.rbe_parent && (elm == ((elm)->entry.rbe_parent)->entry.rbe_right)) elm = (elm)->entry.rbe_parent; elm = (elm)->entry.rbe_parent; } } return (elm); } struct format_entry * format_entry_tree_RB_PREV(struct format_entry *elm) { if ((elm)->entry.rbe_left) { elm = (elm)->entry.rbe_left; while ((elm)->entry.rbe_right) elm = (elm)->entry.rbe_right; } else { if ((elm)->entry.rbe_parent && (elm == ((elm)->entry.rbe_parent)->entry.rbe_right)) elm = (elm)->entry.rbe_parent; else { while ((elm)->entry.rbe_parent && (elm == ((elm)->entry.rbe_parent)->entry.rbe_left)) elm = (elm)->entry.rbe_parent; elm = (elm)->entry.rbe_parent; } } return (elm); } struct format_entry * format_entry_tree_RB_MINMAX(struct format_entry_tree *head, int val) { struct format_entry *tmp = (head)->rbh_root; struct format_entry *parent = 0; while (tmp) { parent = tmp; if (val < 0) tmp = (tmp)->entry.rbe_left; else tmp = (tmp)->entry.rbe_right; } return (parent); };


static int
format_entry_cmp(struct format_entry *fe1, struct format_entry *fe2)
{
 return (strcmp(fe1->key, fe2->key));
}


static const char *format_upper[] = {
 0,
 0,
 0,
 "pane_id",
 0,
 "window_flags",
 0,
 "host",
 "window_index",
 0,
 0,
 0,
 0,
 0,
 0,
 "pane_index",
 0,
 0,
 "session_name",
 "pane_title",
 0,
 0,
 "window_name",
 0,
 0,
 0
};


static const char *format_lower[] = {
 0,
 0,
 0,
 0,
 0,
 0,
 0,
 "host_short",
 0,
 0,
 0,
 0,
 0,
 0,
 0,
 0,
 0,
 0,
 0,
 0,
 0,
 0,
 0,
 0,
 0,
 0
};


static void
format_job_update(struct job *job)
{
 struct format_job *fj = job->data;
 struct evbuffer *evb = job->event->input;
 char *line = 0, *next;
 time_t t;

 while ((next = evbuffer_readline(evb)) != 0) {
  free(line);
  line = next;
 }
 if (line == 0)
  return;
 fj->updated = 1;

 free(fj->out);
 fj->out = line;

 log_debug("%s: %p %s: %s", __func__, fj, fj->cmd, fj->out);

 t = time(0);
 if (fj->status && fj->last != t) {
  if (fj->client != 0)
   server_status_client(fj->client);
  fj->last = t;
 }
}


static void
format_job_complete(struct job *job)
{
 struct format_job *fj = job->data;
 char *line, *buf;
 size_t len;

 fj->job = 0;

 buf = 0;
 if ((line = evbuffer_readline(job->event->input)) == 0) {
  len = EVBUFFER_LENGTH(job->event->input);
  buf = xmalloc(len + 1);
  if (len != 0)
   memcpy(buf, EVBUFFER_DATA(job->event->input), len);
  buf[len] = '\0';
 } else
  buf = line;

 log_debug("%s: %p %s: %s", __func__, fj, fj->cmd, buf);

 if (*buf != '\0' || !fj->updated) {
  free(fj->out);
  fj->out = buf;
 } else
  free(buf);

 if (fj->status) {
  if (fj->client != 0)
   server_status_client(fj->client);
  fj->status = 0;
 }
}


static char *
format_job_get(struct format_tree *ft, const char *cmd)
{
 struct format_job_tree *jobs;
 struct format_job fj0, *fj;
 time_t t;
 char *expanded;
 int force;

 if (ft->client == 0)
  jobs = &format_jobs;
 else if (ft->client->jobs != 0)
  jobs = ft->client->jobs;
 else {
  jobs = ft->client->jobs = xmalloc(sizeof *ft->client->jobs);
  do { (jobs)->rbh_root = 0; } while (0);
 }

 fj0.tag = ft->tag;
 fj0.cmd = cmd;
 if ((fj = format_job_tree_RB_FIND(jobs, &fj0)) == 0) {
  fj = xcalloc(1, sizeof *fj);
  fj->client = ft->client;
  fj->tag = ft->tag;
  fj->cmd = xstrdup(cmd);
  fj->expanded = 0;

  xasprintf(&fj->out, "<'%s' not ready>", fj->cmd);

  format_job_tree_RB_INSERT(jobs, fj);
 }

 expanded = format_expand(ft, cmd);
 if (fj->expanded == 0 || strcmp(expanded, fj->expanded) != 0) {
  free((void *)fj->expanded);
  fj->expanded = xstrdup(expanded);
  force = 1;
 } else
  force = (ft->flags & 0x2);

 t = time(0);
 if (fj->job == 0 && (force || fj->last != t)) {
  fj->job = job_run(expanded, 0, 0, format_job_update,
      format_job_complete, 0, fj, 0x1);
  if (fj->job == 0) {
   free(fj->out);
   xasprintf(&fj->out, "<'%s' didn't start>", fj->cmd);
  }
  fj->last = t;
  fj->updated = 0;
 }

 if (ft->flags & 0x1)
  fj->status = 1;

 free(expanded);
 return (format_expand(ft, fj->out));
}


static void
format_job_tidy(struct format_job_tree *jobs, int force)
{
 struct format_job *fj, *fj1;
 time_t now;

 now = time(0);
 for ((fj) = format_job_tree_RB_MINMAX(jobs, -1); ((fj) != 0) && ((fj1) = format_job_tree_RB_NEXT(fj), 1); (fj) = (fj1)) {
  if (!force && (fj->last > now || now - fj->last < 3600))
   continue;
  format_job_tree_RB_REMOVE(jobs, fj);

  log_debug("%s: %s", __func__, fj->cmd);

  if (fj->job != 0)
   job_free(fj->job);

  free((void *)fj->expanded);
  free((void *)fj->cmd);
  free(fj->out);

  free(fj);
 }
}


void
format_lost_client(struct client *c)
{
 if (c->jobs != 0)
  format_job_tidy(c->jobs, 1);
 free(c->jobs);
}


static void
format_job_timer( int fd, short events, void *arg)
{
 struct client *c;
 struct timeval tv = { .tv_sec = 60 };

 format_job_tidy(&format_jobs, 0);
 for((c) = ((&clients)->tqh_first); (c) != 0; (c) = ((c)->entry.tqe_next)) {
  if (c->jobs != 0)
   format_job_tidy(c->jobs, 0);
 }

 evtimer_del(&format_job_event);
 evtimer_add(&format_job_event, &tv);
}


static void
format_cb_host( struct format_tree *ft, struct format_entry *fe)
{
 char host[255 + 1];

 if (gethostname(host, sizeof host) != 0)
  fe->value = xstrdup("");
 else
  fe->value = xstrdup(host);
}


static void
format_cb_host_short( struct format_tree *ft, struct format_entry *fe)
{
 char host[255 + 1], *cp;

 if (gethostname(host, sizeof host) != 0)
  fe->value = xstrdup("");
 else {
  if ((cp = strchr(host, '.')) != 0)
   *cp = '\0';
  fe->value = xstrdup(host);
 }
}


static void
format_cb_pid( struct format_tree *ft, struct format_entry *fe)
{
 xasprintf(&fe->value, "%ld", (long)getpid());
}


static void
format_cb_session_alerts(struct format_tree *ft, struct format_entry *fe)
{
 struct session *s = ft->s;
 struct winlink *wl;
 char alerts[1024], tmp[16];

 if (s == 0)
  return;

 *alerts = '\0';
 for ((wl) = winlinks_RB_MINMAX(&s->windows, -1); (wl) != 0; (wl) = winlinks_RB_NEXT(wl)) {
  if ((wl->flags & (0x1|0x2|0x4)) == 0)
   continue;
  xsnprintf(tmp, sizeof tmp, "%u", wl->idx);

  if (*alerts != '\0')
   strlcat(alerts, ",", sizeof alerts);
  strlcat(alerts, tmp, sizeof alerts);
  if (wl->flags & 0x2)
   strlcat(alerts, "#", sizeof alerts);
  if (wl->flags & 0x1)
   strlcat(alerts, "!", sizeof alerts);
  if (wl->flags & 0x4)
   strlcat(alerts, "~", sizeof alerts);
 }
 fe->value = xstrdup(alerts);
}


static void
format_cb_session_stack(struct format_tree *ft, struct format_entry *fe)
{
 struct session *s = ft->s;
 struct winlink *wl;
 char result[1024], tmp[16];

 if (s == 0)
  return;

 xsnprintf(result, sizeof result, "%u", s->curw->idx);
 for((wl) = ((&s->lastw)->tqh_first); (wl) != 0; (wl) = ((wl)->sentry.tqe_next)) {
  xsnprintf(tmp, sizeof tmp, "%u", wl->idx);

  if (*result != '\0')
   strlcat(result, ",", sizeof result);
  strlcat(result, tmp, sizeof result);
 }
 fe->value = xstrdup(result);
}


static void
format_cb_window_stack_index(struct format_tree *ft, struct format_entry *fe)
{
 struct session *s = ft->wl->session;
 struct winlink *wl;
 u_int idx;

 idx = 0;
 for((wl) = ((&s->lastw)->tqh_first); (wl) != 0; (wl) = ((wl)->sentry.tqe_next)) {
  idx++;
  if (wl == ft->wl)
   break;
 }
 if (wl != 0)
  xasprintf(&fe->value, "%u", idx);
 else
  fe->value = xstrdup("0");
}


static void
format_cb_window_layout(struct format_tree *ft, struct format_entry *fe)
{
 struct window *w = ft->w;

 if (w == 0)
  return;

 if (w->saved_layout_root != 0)
  fe->value = layout_dump(w->saved_layout_root);
 else
  fe->value = layout_dump(w->layout_root);
}


static void
format_cb_window_visible_layout(struct format_tree *ft, struct format_entry *fe)
{
 struct window *w = ft->w;

 if (w == 0)
  return;

 fe->value = layout_dump(w->layout_root);
}


static void
format_cb_start_command(struct format_tree *ft, struct format_entry *fe)
{
 struct window_pane *wp = ft->wp;

 if (wp == 0)
  return;

 fe->value = cmd_stringify_argv(wp->argc, wp->argv);
}


static void
format_cb_current_command(struct format_tree *ft, struct format_entry *fe)
{
 struct window_pane *wp = ft->wp;
 char *cmd;

 if (wp == 0)
  return;

 cmd = osdep_get_name(wp->fd, wp->tty);
 if (cmd == 0 || *cmd == '\0') {
  free(cmd);
  cmd = cmd_stringify_argv(wp->argc, wp->argv);
  if (cmd == 0 || *cmd == '\0') {
   free(cmd);
   cmd = xstrdup(wp->shell);
  }
 }
 fe->value = parse_window_name(cmd);
 free(cmd);
}


static void
format_cb_current_path(struct format_tree *ft, struct format_entry *fe)
{
 struct window_pane *wp = ft->wp;
 char *cwd;

 if (wp == 0)
  return;

 cwd = osdep_get_cwd(wp->fd);
 if (cwd != 0)
  fe->value = xstrdup(cwd);
}


static void
format_cb_history_bytes(struct format_tree *ft, struct format_entry *fe)
{
 struct window_pane *wp = ft->wp;
 struct grid *gd;
 struct grid_line *gl;
 unsigned long long size;
 u_int i;

 if (wp == 0)
  return;
 gd = wp->base.grid;

 size = 0;
 for (i = 0; i < gd->hsize; i++) {
  gl = &gd->linedata[i];
  size += gl->cellsize * sizeof *gl->celldata;
  size += gl->extdsize * sizeof *gl->extddata;
 }
 size += gd->hsize * sizeof *gd->linedata;

 xasprintf(&fe->value, "%llu", size);
}


static void
format_cb_pane_tabs(struct format_tree *ft, struct format_entry *fe)
{
 struct window_pane *wp = ft->wp;
 struct evbuffer *buffer;
 u_int i;
 int size;

 if (wp == 0)
  return;

 buffer = evbuffer_new();
 for (i = 0; i < wp->base.grid->sx; i++) {
  if (!((wp->base.tabs)[((i) >> 3)] & (1 << ((i)&0x7))))
   continue;

  if (EVBUFFER_LENGTH(buffer) > 0)
   evbuffer_add(buffer, ",", 1);
  evbuffer_add_printf(buffer, "%u", i);
 }
 if ((size = EVBUFFER_LENGTH(buffer)) != 0)
  xasprintf(&fe->value, "%.*s", size, EVBUFFER_DATA(buffer));
 evbuffer_free(buffer);
}


static void
format_cb_session_group_list(struct format_tree *ft, struct format_entry *fe)
{
 struct session *s = ft->s;
 struct session_group *sg;
 struct session *loop;
 struct evbuffer *buffer;
 int size;

 if (s == 0)
  return;
 sg = session_group_contains(s);
 if (sg == 0)
  return;

 buffer = evbuffer_new();
 for((loop) = ((&sg->sessions)->tqh_first); (loop) != 0; (loop) = ((loop)->gentry.tqe_next)) {
  if (EVBUFFER_LENGTH(buffer) > 0)
   evbuffer_add(buffer, ",", 1);
  evbuffer_add_printf(buffer, "%s", loop->name);
 }
 if ((size = EVBUFFER_LENGTH(buffer)) != 0)
  xasprintf(&fe->value, "%.*s", size, EVBUFFER_DATA(buffer));
 evbuffer_free(buffer);
}


static void
format_merge(struct format_tree *ft, struct format_tree *from)
{
 struct format_entry *fe;

 for ((fe) = format_entry_tree_RB_MINMAX(&from->tree, -1); (fe) != 0; (fe) = format_entry_tree_RB_NEXT(fe)) {
  if (fe->value != 0)
   format_add(ft, fe->key, "%s", fe->value);
 }
}


struct format_tree *
format_create(struct client *c, struct cmdq_item *item, int tag, int flags)
{
 struct format_tree *ft;

 if (!event_initialized(&format_job_event)) {
  evtimer_set(&format_job_event, format_job_timer, 0);
  format_job_timer(-1, 0, 0);
 }

 ft = xcalloc(1, sizeof *ft);
 do { (&ft->tree)->rbh_root = 0; } while (0);

 if (c != 0) {
  ft->client = c;
  ft->client->references++;
 }

 ft->tag = tag;
 ft->flags = flags;

 format_add(ft, "version", "%s", VERSION);
 format_add_cb(ft, "host", format_cb_host);
 format_add_cb(ft, "host_short", format_cb_host_short);
 format_add_cb(ft, "pid", format_cb_pid);
 format_add(ft, "socket_path", "%s", socket_path);
 format_add_tv(ft, "start_time", &start_time);

 if (item != 0) {
  if (item->cmd != 0)
   format_add(ft, "command", "%s", item->cmd->entry->name);
  if (item->shared != 0 && item->shared->formats != 0)
   format_merge(ft, item->shared->formats);
 }

 return (ft);
}


void
format_free(struct format_tree *ft)
{
 struct format_entry *fe, *fe1;

 for ((fe) = format_entry_tree_RB_MINMAX(&ft->tree, -1); ((fe) != 0) && ((fe1) = format_entry_tree_RB_NEXT(fe), 1); (fe) = (fe1)) {
  format_entry_tree_RB_REMOVE(&ft->tree, fe);
  free(fe->value);
  free(fe->key);
  free(fe);
 }

 if (ft->client != 0)
  server_client_unref(ft->client);
 free(ft);
}
# 725 "/home/enumclass/Documents/C2RustTranslation/bkp/tmux/format.c"
static void
format_add_tv(struct format_tree *ft, const char *key, struct timeval *tv)
{
 struct format_entry *fe;
 struct format_entry *fe_now;

 fe = xmalloc(sizeof *fe);
 fe->key = xstrdup(key);

 fe_now = format_entry_tree_RB_INSERT(&ft->tree, fe);
 if (fe_now != 0) {
  free(fe->key);
  free(fe);
  free(fe_now->value);
  fe = fe_now;
 }

 fe->cb = 0;
 fe->t = tv->tv_sec;

 fe->value = 0;
}


static void
format_add_cb(struct format_tree *ft, const char *key, format_cb cb)
{
 struct format_entry *fe;
 struct format_entry *fe_now;

 fe = xmalloc(sizeof *fe);
 fe->key = xstrdup(key);

 fe_now = format_entry_tree_RB_INSERT(&ft->tree, fe);
 if (fe_now != 0) {
  free(fe->key);
  free(fe);
  free(fe_now->value);
  fe = fe_now;
 }

 fe->cb = cb;
 fe->t = 0;

 fe->value = 0;
}


static char *
format_find(struct format_tree *ft, const char *key, int modifiers)
{
 struct format_entry *fe, fe_find;
 struct environ_entry *envent;
 static char s[64];
 struct options_entry *o;
 const char *found;
 int idx;
 char *copy, *saved;

 if (~modifiers & 0x1) {
  o = options_parse_get(global_options, key, &idx, 0);
  if (o == 0 && ft->w != 0)
   o = options_parse_get(ft->w->options, key, &idx, 0);
  if (o == 0)
   o = options_parse_get(global_w_options, key, &idx, 0);
  if (o == 0 && ft->s != 0)
   o = options_parse_get(ft->s->options, key, &idx, 0);
  if (o == 0)
   o = options_parse_get(global_s_options, key, &idx, 0);
  if (o != 0) {
   found = options_tostring(o, idx, 1);
   goto found;
  }
 }
 found = 0;

 fe_find.key = (char *) key;
 fe = format_entry_tree_RB_FIND(&ft->tree, &fe_find);
 if (fe != 0) {
  if (modifiers & 0x1) {
   if (fe->t == 0)
    return (0);
   ctime_r(&fe->t, s);
   s[strcspn(s, "\n")] = '\0';
   found = s;
   goto found;
  }
  if (fe->t != 0) {
   xsnprintf(s, sizeof s, "%lld", (long long)fe->t);
   found = s;
   goto found;
  }
  if (fe->value == 0 && fe->cb != 0) {
   fe->cb(ft, fe);
   if (fe->value == 0)
    fe->value = xstrdup("");
  }
  found = fe->value;
  goto found;
 }

 if (~modifiers & 0x1) {
  envent = 0;
  if (ft->s != 0)
   envent = environ_find(ft->s->environ, key);
  if (envent == 0)
   envent = environ_find(global_environ, key);
  if (envent != 0) {
   found = envent->value;
   goto found;
  }
 }

 return (0);

found:
 if (found == 0)
  return (0);
 copy = xstrdup(found);
 if (modifiers & 0x2) {
  saved = copy;
  copy = xstrdup(basename(saved));
  free(saved);
 }
 if (modifiers & 0x4) {
  saved = copy;
  copy = xstrdup(dirname(saved));
  free(saved);
 }
 return (copy);
}


static char *
format_skip(char *s)
{
 int brackets = 0;

 for (; *s != '\0'; s++) {
  if (*s == '{')
   brackets++;
  if (*s == '}')
   brackets--;
  if (*s == ',' && brackets == 0)
   break;
 }
 if (*s == '\0')
  return (0);
 return (s);
}


static int
format_choose(char *s, char **left, char **right)
{
 char *cp;

 cp = format_skip(s);
 if (cp == 0)
  return (-1);
 *cp = '\0';

 *left = s;
 *right = cp + 1;
 return (0);
}


int
format_true(const char *s)
{
 if (s != 0 && *s != '\0' && (s[0] != '0' || s[1] != '\0'))
  return (1);
 return (0);
}


static int
format_replace(struct format_tree *ft, const char *key, size_t keylen,
    char **buf, size_t *len, size_t *off)
{
 struct window_pane *wp = ft->wp;
 char *copy, *copy0, *endptr, *ptr, *found, *new;
 char *value, *from = 0, *to = 0, *left, *right;
 size_t valuelen, newlen, fromlen, tolen, used;
 long limit = 0;
 int modifiers = 0, compare = 0, search = 0;


 copy0 = copy = xmalloc(keylen + 1);
 memcpy(copy, key, keylen);
 copy[keylen] = '\0';


 switch (copy[0]) {
 case 'm':
  if (copy[1] != ':')
   break;
  compare = -2;
  copy += 2;
  break;
 case 'C':
  if (copy[1] != ':')
   break;
  search = 1;
  copy += 2;
  break;
 case '|':
  if (copy[1] != '|' || copy[2] != ':')
   break;
  compare = -3;
  copy += 3;
  break;
 case '&':
  if (copy[1] != '&' || copy[2] != ':')
   break;
  compare = -4;
  copy += 3;
  break;
 case '!':
  if (copy[1] == '=' && copy[2] == ':') {
   compare = -1;
   copy += 3;
   break;
  }
  break;
 case '=':
  if (copy[1] == '=' && copy[2] == ':') {
   compare = 1;
   copy += 3;
   break;
  }
  errno = 0;
  limit = strtol(copy + 1, &endptr, 10);
  if (errno == ERANGE && (limit == -9223372036854775808L || limit == 9223372036854775807L))
   break;
  if (*endptr != ':')
   break;
  copy = endptr + 1;
  break;
 case 'b':
  if (copy[1] != ':')
   break;
  modifiers |= 0x2;
  copy += 2;
  break;
 case 'd':
  if (copy[1] != ':')
   break;
  modifiers |= 0x4;
  copy += 2;
  break;
 case 't':
  if (copy[1] != ':')
   break;
  modifiers |= 0x1;
  copy += 2;
  break;
 case 's':
  if (copy[1] != '/')
   break;
  from = copy + 2;
  for (copy = from; *copy != '\0' && *copy != '/'; copy++)
                ;
  if (copy[0] != '/' || copy == from) {
   copy = copy0;
   break;
  }
  copy[0] = '\0';
  to = copy + 1;
  for (copy = to; *copy != '\0' && *copy != '/'; copy++)
                ;
  if (copy[0] != '/' || copy[1] != ':') {
   copy = copy0;
   break;
  }
  copy[0] = '\0';

  modifiers |= 0x8;
  copy += 2;
  break;
 }


 if (search) {

  if (wp == 0)
   value = xstrdup("0");
  else
   xasprintf(&value, "%u", window_pane_search(wp, copy));
 } else if (compare != 0) {

  if (format_choose(copy, &left, &right) != 0)
   goto fail;
  left = format_expand(ft, left);
  right = format_expand(ft, right);
  if (compare == -3 &&
      (format_true(left) || format_true(right)))
   value = xstrdup("1");
  else if (compare == -4 &&
      (format_true(left) && format_true(right)))
   value = xstrdup("1");
  else if (compare == 1 && strcmp(left, right) == 0)
   value = xstrdup("1");
  else if (compare == -1 && strcmp(left, right) != 0)
   value = xstrdup("1");
  else if (compare == -2 && fnmatch(left, right, 0) == 0)
   value = xstrdup("1");
  else
   value = xstrdup("0");
  free(right);
  free(left);
 } else if (*copy == '?') {

  ptr = format_skip(copy);
  if (ptr == 0)
   goto fail;
  *ptr = '\0';

  found = format_find(ft, copy + 1, modifiers);
  if (found == 0)
   found = format_expand(ft, copy + 1);
  if (format_choose(ptr + 1, &left, &right) != 0)
   goto fail;

  if (format_true(found))
   value = format_expand(ft, left);
  else
   value = format_expand(ft, right);
  free(found);
 } else {

  value = format_find(ft, copy, modifiers);
  if (value == 0)
   value = xstrdup("");
 }


 if (modifiers & 0x8) {
  fromlen = strlen(from);
  tolen = strlen(to);

  newlen = strlen(value) + 1;
  copy = new = xmalloc(newlen);
  for (ptr = value; *ptr != '\0'; ) {
   if (strncmp(ptr, from, fromlen) != 0) {
    *new++ = *ptr++;
    continue;
   }
   used = new - copy;

   newlen += tolen;
   copy = xrealloc(copy, newlen);

   new = copy + used;
   memcpy(new, to, tolen);

   new += tolen;
   ptr += fromlen;
  }
  *new = '\0';
  free(value);
  value = copy;
 }


 if (limit > 0) {
  new = utf8_trimcstr(value, limit);
  free(value);
  value = new;
 } else if (limit < 0) {
  new = utf8_rtrimcstr(value, -limit);
  free(value);
  value = new;
 }


 valuelen = strlen(value);
 while (*len - *off < valuelen + 1) {
  *buf = xreallocarray(*buf, 2, *len);
  *len *= 2;
 }
 memcpy(*buf + *off, value, valuelen);
 *off += valuelen;

 free(value);
 free(copy0);
 return (0);

fail:
 free(copy0);
 return (-1);
}


char *
format_expand_time(struct format_tree *ft, const char *fmt, time_t t)
{
 struct tm *tm;
 char s[2048];

 if (fmt == 0 || *fmt == '\0')
  return (xstrdup(""));

 tm = localtime(&t);

 if (strftime(s, sizeof s, fmt, tm) == 0)
  return (xstrdup(""));

 return (format_expand(ft, s));
}


char *
format_expand(struct format_tree *ft, const char *fmt)
{
 char *buf, *out, *name;
 const char *ptr, *s, *saved = fmt;
 size_t off, len, n, outlen;
 int ch, brackets;

 if (fmt == 0)
  return (xstrdup(""));

 len = 64;
 buf = xmalloc(len);
 off = 0;

 while (*fmt != '\0') {
  if (*fmt != '#') {
   while (len - off < 2) {
    buf = xreallocarray(buf, 2, len);
    len *= 2;
   }
   buf[off++] = *fmt++;
   continue;
  }
  fmt++;

  ch = (u_char) *fmt++;
  switch (ch) {
  case '(':
   brackets = 1;
   for (ptr = fmt; *ptr != '\0'; ptr++) {
    if (*ptr == '(')
     brackets++;
    if (*ptr == ')' && --brackets == 0)
     break;
   }
   if (*ptr != ')' || brackets != 0)
    break;
   n = ptr - fmt;

   if (ft->flags & 0x4)
    out = xstrdup("");
   else {
    name = xstrndup(fmt, n);
    out = format_job_get(ft, name);
    free(name);
   }
   outlen = strlen(out);

   while (len - off < outlen + 1) {
    buf = xreallocarray(buf, 2, len);
    len *= 2;
   }
   memcpy(buf + off, out, outlen);
   off += outlen;

   free(out);

   fmt += n + 1;
   continue;
  case '{':
   brackets = 1;
   for (ptr = fmt; *ptr != '\0'; ptr++) {
    if (*ptr == '{')
     brackets++;
    if (*ptr == '}' && --brackets == 0)
     break;
   }
   if (*ptr != '}' || brackets != 0)
    break;
   n = ptr - fmt;

   if (format_replace(ft, fmt, n, &buf, &len, &off) != 0)
    break;
   fmt += n + 1;
   continue;
  case '#':
   while (len - off < 2) {
    buf = xreallocarray(buf, 2, len);
    len *= 2;
   }
   buf[off++] = '#';
   continue;
  default:
   s = 0;
   if (ch >= 'A' && ch <= 'Z')
    s = format_upper[ch - 'A'];
   else if (ch >= 'a' && ch <= 'z')
    s = format_lower[ch - 'a'];
   if (s == 0) {
    while (len - off < 3) {
     buf = xreallocarray(buf, 2, len);
     len *= 2;
    }
    buf[off++] = '#';
    buf[off++] = ch;
    continue;
   }
   n = strlen(s);
   if (format_replace(ft, s, n, &buf, &len, &off) != 0)
    break;
   continue;
  }

  break;
 }
 buf[off] = '\0';

 log_debug("format '%s' -> '%s'", saved, buf);
 return (buf);
}


char *
format_single(struct cmdq_item *item, const char *fmt, struct client *c,
    struct session *s, struct winlink *wl, struct window_pane *wp)
{
 struct format_tree *ft;
 char *expanded;

 if (item != 0)
  ft = format_create(item->client, item, 0, 0);
 else
  ft = format_create(0, item, 0, 0);
 format_defaults(ft, c, s, wl, wp);

 expanded = format_expand(ft, fmt);
 format_free(ft);
 return (expanded);
}


void
format_defaults(struct format_tree *ft, struct client *c, struct session *s,
    struct winlink *wl, struct window_pane *wp)
{
 if (c != 0 && s != 0 && c->session != s)
  log_debug("%s: session does not match", __func__);

 format_add(ft, "session_format", "%d", s != 0);
 format_add(ft, "window_format", "%d", wl != 0);
 format_add(ft, "pane_format", "%d", wp != 0);

 if (s == 0 && c != 0)
  s = c->session;
 if (wl == 0 && s != 0)
  wl = s->curw;
 if (wp == 0 && wl != 0)
  wp = wl->window->active;

 if (c != 0)
  format_defaults_client(ft, c);
 if (s != 0)
  format_defaults_session(ft, s);
 if (wl != 0)
  format_defaults_winlink(ft, wl);
 if (wp != 0)
  format_defaults_pane(ft, wp);
}


static void
format_defaults_session(struct format_tree *ft, struct session *s)
{
 struct session_group *sg;

 ft->s = s;

 format_add(ft, "session_name", "%s", s->name);
 format_add(ft, "session_windows", "%u", winlink_count(&s->windows));
 format_add(ft, "session_width", "%u", s->sx);
 format_add(ft, "session_height", "%u", s->sy);
 format_add(ft, "session_id", "$%u", s->id);

 sg = session_group_contains(s);
 format_add(ft, "session_grouped", "%d", sg != 0);
 if (sg != 0) {
  format_add(ft, "session_group", "%s", sg->name);
  format_add(ft, "session_group_size", "%u",
      session_group_count (sg));
  format_add_cb(ft, "session_group_list",
      format_cb_session_group_list);
 }

 format_add_tv(ft, "session_created", &s->creation_time);
 format_add_tv(ft, "session_last_attached", &s->last_attached_time);
 format_add_tv(ft, "session_activity", &s->activity_time);

 format_add(ft, "session_attached", "%u", s->attached);
 format_add(ft, "session_many_attached", "%d", s->attached > 1);

 format_add_cb(ft, "session_alerts", format_cb_session_alerts);
 format_add_cb(ft, "session_stack", format_cb_session_stack);
}


static void
format_defaults_client(struct format_tree *ft, struct client *c)
{
 struct session *s;
 const char *name;
 struct tty *tty = &c->tty;
 const char *types[] = { "VT100", "VT101", "VT102", "VT220", "VT320", "VT420", "Unknown" };

 if (ft->s == 0)
  ft->s = c->session;

 format_add(ft, "client_name", "%s", c->name);
 format_add(ft, "client_pid", "%ld", (long) c->pid);
 format_add(ft, "client_height", "%u", tty->sy);
 format_add(ft, "client_width", "%u", tty->sx);
 format_add(ft, "client_tty", "%s", c->ttyname);
 format_add(ft, "client_control_mode", "%d",
  !!(c->flags & 0x2000));

 if (tty->term_name != 0)
  format_add(ft, "client_termname", "%s", tty->term_name);
 if (tty->term_name != 0)
  format_add(ft, "client_termtype", "%s", types[tty->term_type]);

 format_add_tv(ft, "client_created", &c->creation_time);
 format_add_tv(ft, "client_activity", &c->activity_time);

 format_add(ft, "client_written", "%zu", c->written);
 format_add(ft, "client_discarded", "%zu", c->discarded);

 name = server_client_get_key_table(c);
 if (strcmp(c->keytable->name, name) == 0)
  format_add(ft, "client_prefix", "%d", 0);
 else
  format_add(ft, "client_prefix", "%d", 1);
 format_add(ft, "client_key_table", "%s", c->keytable->name);

 if (tty->flags & 0x8)
  format_add(ft, "client_utf8", "%d", 1);
 else
  format_add(ft, "client_utf8", "%d", 0);

 if (c->flags & 0x800)
  format_add(ft, "client_readonly", "%d", 1);
 else
  format_add(ft, "client_readonly", "%d", 0);

 s = c->session;
 if (s != 0)
  format_add(ft, "client_session", "%s", s->name);
 s = c->last_session;
 if (s != 0 && session_alive(s))
  format_add(ft, "client_last_session", "%s", s->name);
}


void
format_defaults_window(struct format_tree *ft, struct window *w)
{
 ft->w = w;

 format_add_tv(ft, "window_activity", &w->activity_time);
 format_add(ft, "window_id", "@%u", w->id);
 format_add(ft, "window_name", "%s", w->name);
 format_add(ft, "window_width", "%u", w->sx);
 format_add(ft, "window_height", "%u", w->sy);
 format_add_cb(ft, "window_layout", format_cb_window_layout);
 format_add_cb(ft, "window_visible_layout",
     format_cb_window_visible_layout);
 format_add(ft, "window_panes", "%u", window_count_panes(w));
 format_add(ft, "window_zoomed_flag", "%d",
     !!(w->flags & 0x1000));
}


static void
format_defaults_winlink(struct format_tree *ft, struct winlink *wl)
{
 struct session *s = wl->session;
 struct window *w = wl->window;

 if (ft->w == 0)
  ft->w = wl->window;
 ft->wl = wl;

 format_defaults_window(ft, w);

 format_add(ft, "window_index", "%d", wl->idx);
 format_add_cb(ft, "window_stack_index", format_cb_window_stack_index);
 format_add(ft, "window_flags", "%s", window_printable_flags(wl));
 format_add(ft, "window_active", "%d", wl == s->curw);

 format_add(ft, "window_bell_flag", "%d",
     !!(wl->flags & 0x1));
 format_add(ft, "window_activity_flag", "%d",
     !!(wl->flags & 0x2));
 format_add(ft, "window_silence_flag", "%d",
     !!(wl->flags & 0x4));
 format_add(ft, "window_last_flag", "%d",
     !!(wl == ((&s->lastw)->tqh_first)));
 format_add(ft, "window_linked", "%d", session_is_linked(s, wl->window));
}


void
format_defaults_pane(struct format_tree *ft, struct window_pane *wp)
{
 struct grid *gd = wp->base.grid;
 int status = wp->status;
 u_int idx;

 if (ft->w == 0)
  ft->w = wp->window;
 ft->wp = wp;

 format_add(ft, "history_size", "%u", gd->hsize);
 format_add(ft, "history_limit", "%u", gd->hlimit);
 format_add_cb(ft, "history_bytes", format_cb_history_bytes);

 if (window_pane_index(wp, &idx) != 0)
  fatalx("index not found");
 format_add(ft, "pane_index", "%u", idx);

 format_add(ft, "pane_width", "%u", wp->sx);
 format_add(ft, "pane_height", "%u", wp->sy);
 format_add(ft, "pane_title", "%s", wp->base.title);
 format_add(ft, "pane_id", "%%%u", wp->id);
 format_add(ft, "pane_active", "%d", wp == wp->window->active);
 format_add(ft, "pane_input_off", "%d", !!(wp->flags & 0x40));
 format_add(ft, "pane_pipe", "%d", wp->pipe_fd != -1);

 if ((wp->flags & 0x200) && WIFEXITED(status))
  format_add(ft, "pane_dead_status", "%d", WEXITSTATUS(status));
 format_add(ft, "pane_dead", "%d", wp->fd == -1);

 if (window_pane_visible(wp)) {
  format_add(ft, "pane_left", "%u", wp->xoff);
  format_add(ft, "pane_top", "%u", wp->yoff);
  format_add(ft, "pane_right", "%u", wp->xoff + wp->sx - 1);
  format_add(ft, "pane_bottom", "%u", wp->yoff + wp->sy - 1);
  format_add(ft, "pane_at_left", "%d", wp->xoff == 0);
  format_add(ft, "pane_at_top", "%d", wp->yoff == 0);
  format_add(ft, "pane_at_right", "%d",
      wp->xoff + wp->sx == wp->window->sx);
  format_add(ft, "pane_at_bottom", "%d",
      wp->yoff + wp->sy == wp->window->sy);
 }

 format_add(ft, "pane_in_mode", "%d", wp->screen != &wp->base);
 if (wp->mode != 0)
  format_add(ft, "pane_mode", "%s", wp->mode->name);

 format_add(ft, "pane_synchronized", "%d",
     !!options_get_number(wp->window->options, "synchronize-panes"));
 if (wp->searchstr != 0)
  format_add(ft, "pane_search_string", "%s", wp->searchstr);

 format_add(ft, "pane_tty", "%s", wp->tty);
 format_add(ft, "pane_pid", "%ld", (long) wp->pid);
 format_add_cb(ft, "pane_start_command", format_cb_start_command);
 format_add_cb(ft, "pane_current_command", format_cb_current_command);
 format_add_cb(ft, "pane_current_path", format_cb_current_path);

 format_add(ft, "cursor_x", "%u", wp->base.cx);
 format_add(ft, "cursor_y", "%u", wp->base.cy);
 format_add(ft, "scroll_region_upper", "%u", wp->base.rupper);
 format_add(ft, "scroll_region_lower", "%u", wp->base.rlower);

 window_copy_add_formats(wp, ft);

 format_add(ft, "alternate_on", "%d", wp->saved_grid ? 1 : 0);
 format_add(ft, "alternate_saved_x", "%u", wp->saved_cx);
 format_add(ft, "alternate_saved_y", "%u", wp->saved_cy);

 format_add(ft, "cursor_flag", "%d",
     !!(wp->base.mode & 0x1));
 format_add(ft, "insert_flag", "%d",
     !!(wp->base.mode & 0x2));
 format_add(ft, "keypad_cursor_flag", "%d",
     !!(wp->base.mode & 0x4));
 format_add(ft, "keypad_flag", "%d",
     !!(wp->base.mode & 0x8));
 format_add(ft, "wrap_flag", "%d",
     !!(wp->base.mode & 0x10));

 format_add(ft, "mouse_any_flag", "%d",
     !!(wp->base.mode & (0x20|0x40|0x1000)));
 format_add(ft, "mouse_standard_flag", "%d",
     !!(wp->base.mode & 0x20));
 format_add(ft, "mouse_button_flag", "%d",
     !!(wp->base.mode & 0x40));
 format_add(ft, "mouse_all_flag", "%d",
     !!(wp->base.mode & 0x1000));

 format_add_cb(ft, "pane_tabs", format_cb_pane_tabs);
}


void
format_defaults_paste_buffer(struct format_tree *ft, struct paste_buffer *pb)
{
 struct timeval tv;
 size_t size;
 char *s;

 timerclear(&tv);
 tv.tv_sec = paste_buffer_created(pb);
 paste_buffer_data(pb, &size);

 format_add(ft, "buffer_size", "%zu", size);
 format_add(ft, "buffer_name", "%s", paste_buffer_name(pb));
 format_add_tv(ft, "buffer_created", &tv);

 s = paste_make_sample(pb);
 format_add(ft, "buffer_sample", "%s", s);
 free(s);
}
