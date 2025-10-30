#include <bitstring.h>
#include <compat.h>
#include <errno.h>
#include <event.h>
#include <fcntl.h>
#include <fnmatch.h>
#include <imsg.h>
#include <inttypes.h>
#include <ioctl.h>
#include <limits.h>
#include <queue.h>
#include <signal.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <tmux.h>
#include <tree.h>
#include <types.h>
#include <uio.h>
#include <unistd.h>
#include <vis.h>
#include <wchar.h>
#include <xmalloc.h>

void err(int, const char *, ...);
void errx(int, const char *, ...);
void warn(const char *, ...);
void warnx(const char *, ...);
typedef unsigned char bitstr_t;
char *vis(char *, int, int, int);
int strvis(char *, const char *, int);
int stravis(char **, const char *, int);
int strnvis(char *, const char *, size_t, int);
int strvisx(char *, const char *, size_t, int);
int strunvis(char *, const char *);
int unvis(char *, char, int *, int);
ssize_t strnunvis(char *, const char *, size_t);
struct ibuf
{
  struct 
  {
    struct ibuf *tqe_next;
    struct ibuf **tqe_prev;
  } entry;
  u_char *buf;
  size_t size;
  size_t max;
  size_t wpos;
  size_t rpos;
  int fd;
};
struct msgbuf
{
  struct 
  {
    struct ibuf *tqh_first;
    struct ibuf **tqh_last;
  } bufs;
  uint32_t queued;
  int fd;
};
struct ibuf_read
{
  u_char buf[65535];
  u_char *rptr;
  size_t wpos;
};
struct imsg_fd
{
  struct 
  {
    struct imsg_fd *tqe_next;
    struct imsg_fd **tqe_prev;
  } entry;
  int fd;
};
struct imsgbuf
{
  struct 
  {
    struct imsg_fd *tqh_first;
    struct imsg_fd **tqh_last;
  } fds;
  struct ibuf_read r;
  struct msgbuf w;
  int fd;
  pid_t pid;
};
struct imsg_hdr
{
  uint32_t type;
  uint16_t len;
  uint16_t flags;
  uint32_t peerid;
  uint32_t pid;
};
struct imsg
{
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
int imsg_compose(struct imsgbuf *, uint32_t, uint32_t, pid_t, int, const void *, uint16_t);
int imsg_composev(struct imsgbuf *, uint32_t, uint32_t, pid_t, int, const struct iovec *, int);
struct ibuf *imsg_create(struct imsgbuf *, uint32_t, uint32_t, pid_t, uint16_t);
int imsg_add(struct ibuf *, const void *, uint16_t);
void imsg_close(struct imsgbuf *, struct ibuf *);
void imsg_free(struct imsg *);
int imsg_flush(struct imsgbuf *);
void imsg_clear(struct imsgbuf *);
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
pid_t fdforkpty(int, int *, char *, struct termios *, struct winsize *);
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
extern int BSDopterr;
extern int BSDoptind;
extern int BSDoptopt;
extern int BSDoptreset;
extern char *BSDoptarg;
int BSDgetopt(int, char * const *, const char *);
void *xmalloc(size_t);
void *xcalloc(size_t, size_t);
void *xrealloc(void *, size_t);
void *xreallocarray(void *, size_t, size_t);
char *xstrdup(const char *);
char *xstrndup(const char *, size_t);
int xasprintf(char **, const char *, ...);
int xvasprintf(char **, const char *, va_list);
int xsnprintf(char *, size_t, const char *, ...);
int xvsnprintf(char *, size_t, const char *, va_list);
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
typedef unsigned long long key_code;
enum 
{
  KEYC_FOCUS_IN = 0x000010000000ULL,
  KEYC_FOCUS_OUT,
  KEYC_PASTE_START,
  KEYC_PASTE_END,
  KEYC_MOUSE,
  KEYC_DRAGGING,
  KEYC_MOUSEMOVE_PANE,
  KEYC_MOUSEMOVE_STATUS,
  KEYC_MOUSEMOVE_BORDER,
  KEYC_MOUSEDOWN1_PANE,
  KEYC_MOUSEDOWN1_STATUS,
  KEYC_MOUSEDOWN1_BORDER,
  KEYC_MOUSEDOWN2_PANE,
  KEYC_MOUSEDOWN2_STATUS,
  KEYC_MOUSEDOWN2_BORDER,
  KEYC_MOUSEDOWN3_PANE,
  KEYC_MOUSEDOWN3_STATUS,
  KEYC_MOUSEDOWN3_BORDER,
  KEYC_MOUSEUP1_PANE,
  KEYC_MOUSEUP1_STATUS,
  KEYC_MOUSEUP1_BORDER,
  KEYC_MOUSEUP2_PANE,
  KEYC_MOUSEUP2_STATUS,
  KEYC_MOUSEUP2_BORDER,
  KEYC_MOUSEUP3_PANE,
  KEYC_MOUSEUP3_STATUS,
  KEYC_MOUSEUP3_BORDER,
  KEYC_MOUSEDRAG1_PANE,
  KEYC_MOUSEDRAG1_STATUS,
  KEYC_MOUSEDRAG1_BORDER,
  KEYC_MOUSEDRAG2_PANE,
  KEYC_MOUSEDRAG2_STATUS,
  KEYC_MOUSEDRAG2_BORDER,
  KEYC_MOUSEDRAG3_PANE,
  KEYC_MOUSEDRAG3_STATUS,
  KEYC_MOUSEDRAG3_BORDER,
  KEYC_MOUSEDRAGEND1_PANE,
  KEYC_MOUSEDRAGEND1_STATUS,
  KEYC_MOUSEDRAGEND1_BORDER,
  KEYC_MOUSEDRAGEND2_PANE,
  KEYC_MOUSEDRAGEND2_STATUS,
  KEYC_MOUSEDRAGEND2_BORDER,
  KEYC_MOUSEDRAGEND3_PANE,
  KEYC_MOUSEDRAGEND3_STATUS,
  KEYC_MOUSEDRAGEND3_BORDER,
  KEYC_WHEELUP_PANE,
  KEYC_WHEELUP_STATUS,
  KEYC_WHEELUP_BORDER,
  KEYC_WHEELDOWN_PANE,
  KEYC_WHEELDOWN_STATUS,
  KEYC_WHEELDOWN_BORDER,
  KEYC_DOUBLECLICK1_PANE,
  KEYC_DOUBLECLICK1_STATUS,
  KEYC_DOUBLECLICK1_BORDER,
  KEYC_DOUBLECLICK2_PANE,
  KEYC_DOUBLECLICK2_STATUS,
  KEYC_DOUBLECLICK2_BORDER,
  KEYC_DOUBLECLICK3_PANE,
  KEYC_DOUBLECLICK3_STATUS,
  KEYC_DOUBLECLICK3_BORDER,
  KEYC_TRIPLECLICK1_PANE,
  KEYC_TRIPLECLICK1_STATUS,
  KEYC_TRIPLECLICK1_BORDER,
  KEYC_TRIPLECLICK2_PANE,
  KEYC_TRIPLECLICK2_STATUS,
  KEYC_TRIPLECLICK2_BORDER,
  KEYC_TRIPLECLICK3_PANE,
  KEYC_TRIPLECLICK3_STATUS,
  KEYC_TRIPLECLICK3_BORDER,
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
  KEYC_KP_PERIOD
};
enum tty_code_code
{
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
  TTYC_XT
};
enum msgtype
{
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
  MSG_EXEC
};
struct msg_command_data
{
  int argc;
};
struct msg_stdin_data
{
  ssize_t size;
  char data[1024];
};
struct msg_stdout_data
{
  ssize_t size;
  char data[1024];
};
struct msg_stderr_data
{
  ssize_t size;
  char data[1024];
};
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
};
enum utf8_state
{
  UTF8_MORE,
  UTF8_DONE,
  UTF8_ERROR
};
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
};
struct grid_cell_entry
{
  u_char flags;
  union 
  {
    u_int offset;
    struct 
    {
      u_char attr;
      u_char fg;
      u_char bg;
      u_char data;
    } data;
  };
};
struct grid_line
{
  u_int cellused;
  u_int cellsize;
  struct grid_cell_entry *celldata;
  u_int extdsize;
  struct grid_cell *extddata;
  int flags;
};
struct grid
{
  int flags;
  u_int sx;
  u_int sy;
  u_int hscrolled;
  u_int hsize;
  u_int hlimit;
  struct grid_line *linedata;
};
struct hook
{
  const char *name;
  struct cmd_list *cmdlist;
  struct 
  {
    struct hook *rbe_left;
    struct hook *rbe_right;
    struct hook *rbe_parent;
    int rbe_color;
  } entry;
};
struct job;
typedef void (*job_update_cb)(struct job *);
typedef void (*job_complete_cb)(struct job *);
typedef void (*job_free_cb)(void *);
struct job
{
  enum 
  {
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
  struct 
  {
    struct job *le_next;
    struct job **le_prev;
  } entry;
};
struct joblist
{
  struct job *lh_first;
};
struct screen_sel
{
  int flag;
  int hidden;
  int rectflag;
  enum 
  {
    LINE_SEL_NONE,
    LINE_SEL_LEFT_RIGHT,
    LINE_SEL_RIGHT_LEFT
  } lineflag;
  int modekeys;
  u_int sx;
  u_int sy;
  u_int ex;
  u_int ey;
  struct grid_cell cell;
};
struct screen_titles;
struct screen
{
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
struct screen_write_ctx
{
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
struct window_mode
{
  const char *name;
  struct screen *(*init)(struct window_pane *, struct cmd_find_state *, struct args *);
  void (*free)(struct window_pane *);
  void (*resize)(struct window_pane *, u_int, u_int);
  void (*key)(struct window_pane *, struct client *, struct session *, key_code, struct mouse_event *);
  const char *(*key_table)(struct window_pane *);
  void (*command)(struct window_pane *, struct client *, struct session *, struct args *, struct mouse_event *);
};
struct window_choose_data
{
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
struct window_pane
{
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
  struct 
  {
    struct window_pane *tqe_next;
    struct window_pane **tqe_prev;
  } entry;
  struct 
  {
    struct window_pane *rbe_left;
    struct window_pane *rbe_right;
    struct window_pane *rbe_parent;
    int rbe_color;
  } tree_entry;
};
struct window_panes
{
  struct window_pane *tqh_first;
  struct window_pane **tqh_last;
};
struct window_pane_tree
{
  struct window_pane *rbh_root;
};
struct window
{
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
  int alerts_queued;
  struct 
  {
    struct window *tqe_next;
    struct window **tqe_prev;
  } alerts_entry;
  struct options *options;
  struct grid_cell style;
  struct grid_cell active_style;
  u_int references;
  struct 
  {
    struct winlink *tqh_first;
    struct winlink **tqh_last;
  } winlinks;
  struct 
  {
    struct window *rbe_left;
    struct window *rbe_right;
    struct window *rbe_parent;
    int rbe_color;
  } entry;
};
struct windows
{
  struct window *rbh_root;
};
struct winlink
{
  int idx;
  struct session *session;
  struct window *window;
  size_t status_width;
  struct grid_cell status_cell;
  char *status_text;
  int flags;
  struct 
  {
    struct winlink *rbe_left;
    struct winlink *rbe_right;
    struct winlink *rbe_parent;
    int rbe_color;
  } entry;
  struct 
  {
    struct winlink *tqe_next;
    struct winlink **tqe_prev;
  } wentry;
  struct 
  {
    struct winlink *tqe_next;
    struct winlink **tqe_prev;
  } sentry;
};
struct winlinks
{
  struct winlink *rbh_root;
};
struct winlink_stack
{
  struct winlink *tqh_first;
  struct winlink **tqh_last;
};
enum layout_type
{
  LAYOUT_LEFTRIGHT,
  LAYOUT_TOPBOTTOM,
  LAYOUT_WINDOWPANE
};
struct layout_cells
{
  struct layout_cell *tqh_first;
  struct layout_cell **tqh_last;
};
struct layout_cell
{
  enum layout_type type;
  struct layout_cell *parent;
  u_int sx;
  u_int sy;
  u_int xoff;
  u_int yoff;
  struct window_pane *wp;
  struct layout_cells cells;
  struct 
  {
    struct layout_cell *tqe_next;
    struct layout_cell **tqe_prev;
  } entry;
};
struct environ_entry
{
  char *name;
  char *value;
  struct 
  {
    struct environ_entry *rbe_left;
    struct environ_entry *rbe_right;
    struct environ_entry *rbe_parent;
    int rbe_color;
  } entry;
};
struct session_group
{
  const char *name;
  struct 
  {
    struct session *tqh_first;
    struct session **tqh_last;
  } sessions;
  struct 
  {
    struct session_group *rbe_left;
    struct session_group *rbe_right;
    struct session_group *rbe_parent;
    int rbe_color;
  } entry;
};
struct session_groups
{
  struct session_group *rbh_root;
};
struct session
{
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
  struct 
  {
    struct session *tqe_next;
    struct session **tqe_prev;
  } gentry;
  struct 
  {
    struct session *rbe_left;
    struct session *rbe_right;
    struct session *rbe_parent;
    int rbe_color;
  } entry;
};
struct sessions
{
  struct session *rbh_root;
};
struct mouse_event
{
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
struct tty_key
{
  char ch;
  key_code key;
  struct tty_key *left;
  struct tty_key *right;
  struct tty_key *next;
};
struct tty_code;
struct tty_term
{
  char *name;
  u_int references;
  char acs[255 + 1][2];
  struct tty_code *codes;
  int flags;
  struct 
  {
    struct tty_term *le_next;
    struct tty_term **le_prev;
  } entry;
};
struct tty_terms
{
  struct tty_term *lh_first;
};
struct tty
{
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
  int flags;
  struct tty_term *term;
  char *term_name;
  int term_flags;
  enum 
  {
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
  void (*mouse_drag_update)(struct client *, struct mouse_event *);
  void (*mouse_drag_release)(struct client *, struct mouse_event *);
  struct event key_timer;
  struct tty_key *key_tree;
};
struct tty_ctx
{
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
struct message_entry
{
  char *msg;
  u_int msg_num;
  time_t msg_time;
  struct 
  {
    struct message_entry *tqe_next;
    struct message_entry **tqe_prev;
  } entry;
};
struct args_entry;
struct args_tree
{
  struct args_entry *rbh_root;
};
struct args
{
  struct args_tree tree;
  int argc;
  char **argv;
};
enum cmd_find_type
{
  CMD_FIND_PANE,
  CMD_FIND_WINDOW,
  CMD_FIND_SESSION
};
struct cmd_find_state
{
  int flags;
  struct cmd_find_state *current;
  struct session *s;
  struct winlink *wl;
  struct window *w;
  struct window_pane *wp;
  int idx;
};
struct cmd
{
  const struct cmd_entry *entry;
  struct args *args;
  char *file;
  u_int line;
  int flags;
  struct 
  {
    struct cmd *tqe_next;
    struct cmd **tqe_prev;
  } qentry;
};
struct cmd_list
{
  int references;
  struct 
  {
    struct cmd *tqh_first;
    struct cmd **tqh_last;
  } list;
};
enum cmd_retval
{
  CMD_RETURN_ERROR = -1,
  CMD_RETURN_NORMAL = 0,
  CMD_RETURN_WAIT,
  CMD_RETURN_STOP
};
enum cmdq_type
{
  CMDQ_COMMAND,
  CMDQ_CALLBACK
};
struct cmdq_shared
{
  int references;
  int flags;
  struct format_tree *formats;
  struct mouse_event mouse;
  struct cmd_find_state current;
};
typedef enum cmd_retval (*cmdq_cb)(struct cmdq_item *, void *);
struct cmdq_item
{
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
  struct 
  {
    struct cmdq_item *tqe_next;
    struct cmdq_item **tqe_prev;
  } entry;
};
struct cmdq_list
{
  struct cmdq_item *tqh_first;
  struct cmdq_item **tqh_last;
};
struct cmd_entry_flag
{
  char flag;
  enum cmd_find_type type;
  int flags;
};
struct cmd_entry
{
  const char *name;
  const char *alias;
  struct 
  {
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
struct status_line
{
  struct event timer;
  struct screen status;
  struct screen *old_status;
};
typedef int (*prompt_input_cb)(struct client *, void *, const char *, int);
typedef void (*prompt_free_cb)(void *);
struct client
{
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
  int flags;
  struct key_table *keytable;
  struct event identify_timer;
  void (*identify_callback)(struct client *, struct window_pane *);
  void *identify_callback_data;
  char *message_string;
  struct event message_timer;
  u_int message_next;
  struct 
  {
    struct message_entry *tqh_first;
    struct message_entry **tqh_last;
  } message_log;
  char *prompt_string;
  struct utf8_data *prompt_buffer;
  size_t prompt_index;
  prompt_input_cb prompt_inputcb;
  prompt_free_cb prompt_freecb;
  void *prompt_data;
  u_int prompt_hindex;
  enum 
  {
    PROMPT_ENTRY,
    PROMPT_COMMAND
  } prompt_mode;
  int prompt_flags;
  struct session *session;
  struct session *last_session;
  int wlmouse;
  int references;
  struct 
  {
    struct client *tqe_next;
    struct client **tqe_prev;
  } entry;
};
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
};
struct key_binding
{
  key_code key;
  struct cmd_list *cmdlist;
  int flags;
  struct 
  {
    struct key_binding *rbe_left;
    struct key_binding *rbe_right;
    struct key_binding *rbe_parent;
    int rbe_color;
  } entry;
};
struct key_bindings
{
  struct key_binding *rbh_root;
};
struct key_table
{
  const char *name;
  struct key_bindings key_bindings;
  u_int references;
  struct 
  {
    struct key_table *rbe_left;
    struct key_table *rbe_right;
    struct key_table *rbe_parent;
    int rbe_color;
  } entry;
};
struct key_tables
{
  struct key_table *rbh_root;
};
enum options_table_type
{
  OPTIONS_TABLE_STRING,
  OPTIONS_TABLE_NUMBER,
  OPTIONS_TABLE_KEY,
  OPTIONS_TABLE_COLOUR,
  OPTIONS_TABLE_ATTRIBUTES,
  OPTIONS_TABLE_FLAG,
  OPTIONS_TABLE_CHOICE,
  OPTIONS_TABLE_STYLE,
  OPTIONS_TABLE_ARRAY
};
enum options_table_scope
{
  OPTIONS_TABLE_NONE,
  OPTIONS_TABLE_SERVER,
  OPTIONS_TABLE_SESSION,
  OPTIONS_TABLE_WINDOW
};
struct options_table_entry
{
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
void proc_set_signals(struct tmuxproc *, void (*)(int));
void proc_clear_signals(struct tmuxproc *, int);
struct tmuxpeer *proc_add_peer(struct tmuxproc *, int, void (*)(struct imsg *, void *), void *);
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
struct format_tree;
int format_true(const char *);
struct format_tree *format_create(struct client *, struct cmdq_item *, int, int);
void format_free(struct format_tree *);
void format_add(struct format_tree *, const char *, const char *, ...);
char *format_expand_time(struct format_tree *, const char *, time_t);
char *format_expand(struct format_tree *, const char *);
char *format_single(struct cmdq_item *, const char *, struct client *, struct session *, struct winlink *, struct window_pane *);
void format_defaults(struct format_tree *, struct client *, struct session *, struct winlink *, struct window_pane *);
void format_defaults_window(struct format_tree *, struct window *);
void format_defaults_pane(struct format_tree *, struct window_pane *);
void format_defaults_paste_buffer(struct format_tree *, struct paste_buffer *);
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
void hooks_insert(struct hooks *, struct cmdq_item *, struct cmd_find_state *, const char *, ...);
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
struct options_entry *options_empty(struct options *, const struct options_table_entry *);
struct options_entry *options_default(struct options *, const struct options_table_entry *);
const char *options_name(struct options_entry *);
const struct options_table_entry *options_table_entry(struct options_entry *);
struct options_entry *options_get_only(struct options *, const char *);
struct options_entry *options_get(struct options *, const char *);
void options_remove(struct options_entry *);
void options_array_clear(struct options_entry *);
const char *options_array_get(struct options_entry *, u_int);
int options_array_set(struct options_entry *, u_int, const char *, int);
int options_array_size(struct options_entry *, u_int *);
void options_array_assign(struct options_entry *, const char *);
int options_isstring(struct options_entry *);
const char *options_tostring(struct options_entry *, int, int);
char *options_parse(const char *, int *);
struct options_entry *options_parse_get(struct options *, const char *, int *, int);
char *options_match(const char *, int *, int *);
struct options_entry *options_match_get(struct options *, const char *, int *, int, int *);
const char *options_get_string(struct options *, const char *);
long long options_get_number(struct options *, const char *);
const struct grid_cell *options_get_style(struct options *, const char *);
struct options_entry *options_set_string(struct options *, const char *, int, const char *, ...);
struct options_entry *options_set_number(struct options *, const char *, long long);
struct options_entry *options_set_style(struct options *, const char *, int, const char *);
enum options_table_scope options_scope_from_flags(struct args *, int, struct cmd_find_state *, struct options **, char **);
void options_style_update_new(struct options *, struct options_entry *);
void options_style_update_old(struct options *, struct options_entry *);
extern const struct options_table_entry options_table[];
extern struct joblist all_jobs;
struct job *job_run(const char *, struct session *, const char *, job_update_cb, job_complete_cb, job_free_cb, void *, int);
void job_free(struct job *);
void job_died(struct job *, int);
struct environ *environ_create(void);
void environ_free(struct environ *);
struct environ_entry *environ_first(struct environ *);
struct environ_entry *environ_next(struct environ_entry *);
void environ_copy(struct environ *, struct environ *);
struct environ_entry *environ_find(struct environ *, const char *);
void environ_set(struct environ *, const char *, const char *, ...);
void environ_clear(struct environ *, const char *);
void environ_put(struct environ *, const char *);
void environ_unset(struct environ *, const char *);
void environ_update(struct options *, struct environ *, struct environ *);
void environ_push(struct environ *);
void environ_log(struct environ *, const char *, ...);
struct environ *environ_for_session(struct session *, int);
void tty_create_log(void);
void tty_raw(struct tty *, const char *);
void tty_attributes(struct tty *, const struct grid_cell *, const struct window_pane *);
void tty_reset(struct tty *);
void tty_region_off(struct tty *);
void tty_margin_off(struct tty *);
void tty_cursor(struct tty *, u_int, u_int);
void tty_putcode(struct tty *, enum tty_code_code);
void tty_putcode1(struct tty *, enum tty_code_code, int);
void tty_putcode2(struct tty *, enum tty_code_code, int, int);
void tty_putcode3(struct tty *, enum tty_code_code, int, int, int);
void tty_putcode_ptr1(struct tty *, enum tty_code_code, const void *);
void tty_putcode_ptr2(struct tty *, enum tty_code_code, const void *, const void *);
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
void tty_draw_pane(struct tty *, const struct window_pane *, u_int, u_int, u_int);
void tty_draw_line(struct tty *, const struct window_pane *, struct screen *, u_int, u_int, u_int);
int tty_open(struct tty *, char **);
void tty_close(struct tty *);
void tty_free(struct tty *);
void tty_set_type(struct tty *, int);
void tty_write(void (*)(struct tty *, const struct tty_ctx *), struct tty_ctx *);
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
const char *tty_term_string2(struct tty_term *, enum tty_code_code, int, int);
const char *tty_term_string3(struct tty_term *, enum tty_code_code, int, int, int);
const char *tty_term_ptr1(struct tty_term *, enum tty_code_code, const void *);
const char *tty_term_ptr2(struct tty_term *, enum tty_code_code, const void *, const void *);
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
long long args_strtonum(struct args *, u_char, long long, long long, char **);
int cmd_find_target(struct cmd_find_state *, struct cmdq_item *, const char *, enum cmd_find_type, int);
struct client *cmd_find_best_client(struct session *);
struct client *cmd_find_client(struct cmdq_item *, const char *, int);
void cmd_find_clear_state(struct cmd_find_state *, int);
int cmd_find_empty_state(struct cmd_find_state *);
int cmd_find_valid_state(struct cmd_find_state *);
void cmd_find_copy_state(struct cmd_find_state *, struct cmd_find_state *);
void cmd_find_log_state(const char *, struct cmd_find_state *);
void cmd_find_from_session(struct cmd_find_state *, struct session *, int);
void cmd_find_from_winlink(struct cmd_find_state *, struct winlink *, int);
int cmd_find_from_session_window(struct cmd_find_state *, struct session *, struct window *, int);
int cmd_find_from_window(struct cmd_find_state *, struct window *, int);
void cmd_find_from_winlink_pane(struct cmd_find_state *, struct winlink *, struct window_pane *, int);
int cmd_find_from_pane(struct cmd_find_state *, struct window_pane *, int);
int cmd_find_from_client(struct cmd_find_state *, struct client *, int);
int cmd_find_from_mouse(struct cmd_find_state *, struct mouse_event *, int);
int cmd_find_from_nothing(struct cmd_find_state *, int);
int cmd_pack_argv(int, char **, char *, size_t);
int cmd_unpack_argv(char *, size_t, int, char ***);
char **cmd_copy_argv(int, char **);
void cmd_free_argv(int, char **);
char *cmd_stringify_argv(int, char **);
struct cmd *cmd_parse(int, char **, const char *, u_int, char **);
char *cmd_print(struct cmd *);
int cmd_mouse_at(struct window_pane *, struct mouse_event *, u_int *, u_int *, int);
struct winlink *cmd_mouse_window(struct mouse_event *, struct session **);
struct window_pane *cmd_mouse_pane(struct mouse_event *, struct session **, struct winlink **);
char *cmd_template_replace(const char *, const char *, int);
extern const struct cmd_entry *cmd_table[];
enum cmd_retval cmd_attach_session(struct cmdq_item *, const char *, int, int, const char *, int);
struct cmd_list *cmd_list_parse(int, char **, const char *, u_int, char **);
void cmd_list_free(struct cmd_list *);
char *cmd_list_print(struct cmd_list *);
struct cmdq_item *cmdq_get_command(struct cmd_list *, struct cmd_find_state *, struct mouse_event *, int);
struct cmdq_item *cmdq_get_callback1(const char *, cmdq_cb, void *);
void cmdq_insert_after(struct cmdq_item *, struct cmdq_item *);
void cmdq_append(struct client *, struct cmdq_item *);
void cmdq_format(struct cmdq_item *, const char *, const char *, ...);
u_int cmdq_next(struct client *);
void cmdq_guard(struct cmdq_item *, const char *, int);
void cmdq_print(struct cmdq_item *, const char *, ...);
void cmdq_error(struct cmdq_item *, const char *, ...);
int cmd_string_split(const char *, int *, char ***);
struct cmd_list *cmd_string_parse(const char *, const char *, u_int, char **);
void cmd_wait_for_flush(void);
int client_main(struct event_base *, int, char **, int);
void key_bindings_RB_INSERT_COLOR(struct key_bindings *, struct key_binding *);
void key_bindings_RB_REMOVE_COLOR(struct key_bindings *, struct key_binding *, struct key_binding *);
struct key_binding *key_bindings_RB_REMOVE(struct key_bindings *, struct key_binding *);
struct key_binding *key_bindings_RB_INSERT(struct key_bindings *, struct key_binding *);
struct key_binding *key_bindings_RB_FIND(struct key_bindings *, struct key_binding *);
struct key_binding *key_bindings_RB_NFIND(struct key_bindings *, struct key_binding *);
struct key_binding *key_bindings_RB_NEXT(struct key_binding *);
struct key_binding *key_bindings_RB_PREV(struct key_binding *);
struct key_binding *key_bindings_RB_MINMAX(struct key_bindings *, int);
void key_tables_RB_INSERT_COLOR(struct key_tables *, struct key_table *);
void key_tables_RB_REMOVE_COLOR(struct key_tables *, struct key_table *, struct key_table *);
struct key_table *key_tables_RB_REMOVE(struct key_tables *, struct key_table *);
struct key_table *key_tables_RB_INSERT(struct key_tables *, struct key_table *);
struct key_table *key_tables_RB_FIND(struct key_tables *, struct key_table *);
struct key_table *key_tables_RB_NFIND(struct key_tables *, struct key_table *);
struct key_table *key_tables_RB_NEXT(struct key_table *);
struct key_table *key_tables_RB_PREV(struct key_table *);
struct key_table *key_tables_RB_MINMAX(struct key_tables *, int);
extern struct key_tables key_tables;
int key_table_cmp(struct key_table *, struct key_table *);
int key_bindings_cmp(struct key_binding *, struct key_binding *);
struct key_table *key_bindings_get_table(const char *, int);
void key_bindings_unref_table(struct key_table *);
void key_bindings_add(const char *, key_code, int, struct cmd_list *);
void key_bindings_remove(const char *, key_code);
void key_bindings_remove_table(const char *);
void key_bindings_init(void);
void key_bindings_dispatch(struct key_binding *, struct cmdq_item *, struct client *, struct mouse_event *, struct cmd_find_state *);
key_code key_string_lookup_string(const char *);
const char *key_string_lookup_key(key_code);
void alerts_reset_all(void);
void alerts_queue(struct window *, int);
void alerts_check_session(struct session *);
extern struct tmuxproc *server_proc;
extern struct clients clients;
extern struct cmd_find_state marked_pane;
void server_set_marked(struct session *, struct winlink *, struct window_pane *);
void server_clear_marked(void);
int server_is_marked(struct session *, struct winlink *, struct window_pane *);
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
void server_client_add_message(struct client *, const char *, ...);
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
int server_link_window(struct session *, struct winlink *, struct session *, int, int, int, char **);
void server_unlink_window(struct session *, struct winlink *);
void server_destroy_pane(struct window_pane *, int);
void server_destroy_session(struct session *);
void server_check_unattached(void);
int server_set_stdin_callback(struct client *, void (*)(struct client *, int, void *), void *, char **);
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
void status_prompt_set(struct client *, const char *, const char *, prompt_input_cb, prompt_free_cb, void *, int);
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
void grid_set_cells(struct grid *, u_int, u_int, const struct grid_cell *, const char *, size_t);
void grid_clear(struct grid *, u_int, u_int, u_int, u_int, u_int);
void grid_clear_lines(struct grid *, u_int, u_int, u_int);
void grid_move_lines(struct grid *, u_int, u_int, u_int, u_int);
void grid_move_cells(struct grid *, u_int, u_int, u_int, u_int, u_int);
char *grid_string_cells(struct grid *, u_int, u_int, u_int, struct grid_cell **, int, int, int);
void grid_duplicate_lines(struct grid *, u_int, struct grid *, u_int, u_int);
void grid_reflow(struct grid *, u_int, u_int *);
void grid_view_get_cell(struct grid *, u_int, u_int, struct grid_cell *);
void grid_view_set_cell(struct grid *, u_int, u_int, const struct grid_cell *);
void grid_view_set_cells(struct grid *, u_int, u_int, const struct grid_cell *, const char *, size_t);
void grid_view_clear_history(struct grid *, u_int);
void grid_view_clear(struct grid *, u_int, u_int, u_int, u_int, u_int);
void grid_view_scroll_region_up(struct grid *, u_int, u_int, u_int);
void grid_view_scroll_region_down(struct grid *, u_int, u_int, u_int);
void grid_view_insert_lines(struct grid *, u_int, u_int, u_int);
void grid_view_insert_lines_region(struct grid *, u_int, u_int, u_int, u_int);
void grid_view_delete_lines(struct grid *, u_int, u_int, u_int);
void grid_view_delete_lines_region(struct grid *, u_int, u_int, u_int, u_int);
void grid_view_insert_cells(struct grid *, u_int, u_int, u_int, u_int);
void grid_view_delete_cells(struct grid *, u_int, u_int, u_int, u_int);
char *grid_view_string_cells(struct grid *, u_int, u_int, u_int);
void screen_write_start(struct screen_write_ctx *, struct window_pane *, struct screen *);
void screen_write_stop(struct screen_write_ctx *);
void screen_write_reset(struct screen_write_ctx *);
size_t screen_write_cstrlen(const char *, ...);
void screen_write_cnputs(struct screen_write_ctx *, ssize_t, const struct grid_cell *, const char *, ...);
size_t screen_write_strlen(const char *, ...);
void screen_write_puts(struct screen_write_ctx *, const struct grid_cell *, const char *, ...);
void screen_write_nputs(struct screen_write_ctx *, ssize_t, const struct grid_cell *, const char *, ...);
void screen_write_vnputs(struct screen_write_ctx *, ssize_t, const struct grid_cell *, const char *, va_list);
void screen_write_putc(struct screen_write_ctx *, const struct grid_cell *, u_char);
void screen_write_copy(struct screen_write_ctx *, struct screen *, u_int, u_int, u_int, u_int, bitstr_t *, const struct grid_cell *);
void screen_write_fast_copy(struct screen_write_ctx *, struct screen *, u_int, u_int, u_int, u_int);
void screen_write_hline(struct screen_write_ctx *, u_int, int, int);
void screen_write_vline(struct screen_write_ctx *, u_int, int, int);
void screen_write_box(struct screen_write_ctx *, u_int, u_int);
void screen_write_preview(struct screen_write_ctx *, struct screen *, u_int, u_int);
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
void screen_write_collect_add(struct screen_write_ctx *, const struct grid_cell *);
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
void screen_set_selection(struct screen *, u_int, u_int, u_int, u_int, u_int, struct grid_cell *);
void screen_clear_selection(struct screen *);
void screen_hide_selection(struct screen *);
int screen_check_selection(struct screen *, u_int, u_int);
void screen_select_cell(struct screen *, struct grid_cell *, const struct grid_cell *);
extern struct windows windows;
extern struct window_pane_tree all_window_panes;
int window_cmp(struct window *, struct window *);
void windows_RB_INSERT_COLOR(struct windows *, struct window *);
void windows_RB_REMOVE_COLOR(struct windows *, struct window *, struct window *);
struct window *windows_RB_REMOVE(struct windows *, struct window *);
struct window *windows_RB_INSERT(struct windows *, struct window *);
struct window *windows_RB_FIND(struct windows *, struct window *);
struct window *windows_RB_NFIND(struct windows *, struct window *);
struct window *windows_RB_NEXT(struct window *);
struct window *windows_RB_PREV(struct window *);
struct window *windows_RB_MINMAX(struct windows *, int);
int winlink_cmp(struct winlink *, struct winlink *);
void winlinks_RB_INSERT_COLOR(struct winlinks *, struct winlink *);
void winlinks_RB_REMOVE_COLOR(struct winlinks *, struct winlink *, struct winlink *);
struct winlink *winlinks_RB_REMOVE(struct winlinks *, struct winlink *);
struct winlink *winlinks_RB_INSERT(struct winlinks *, struct winlink *);
struct winlink *winlinks_RB_FIND(struct winlinks *, struct winlink *);
struct winlink *winlinks_RB_NFIND(struct winlinks *, struct winlink *);
struct winlink *winlinks_RB_NEXT(struct winlink *);
struct winlink *winlinks_RB_PREV(struct winlink *);
struct winlink *winlinks_RB_MINMAX(struct winlinks *, int);
int window_pane_cmp(struct window_pane *, struct window_pane *);
void window_pane_tree_RB_INSERT_COLOR(struct window_pane_tree *, struct window_pane *);
void window_pane_tree_RB_REMOVE_COLOR(struct window_pane_tree *, struct window_pane *, struct window_pane *);
struct window_pane *window_pane_tree_RB_REMOVE(struct window_pane_tree *, struct window_pane *);
struct window_pane *window_pane_tree_RB_INSERT(struct window_pane_tree *, struct window_pane *);
struct window_pane *window_pane_tree_RB_FIND(struct window_pane_tree *, struct window_pane *);
struct window_pane *window_pane_tree_RB_NFIND(struct window_pane_tree *, struct window_pane *);
struct window_pane *window_pane_tree_RB_NEXT(struct window_pane *);
struct window_pane *window_pane_tree_RB_PREV(struct window_pane *);
struct window_pane *window_pane_tree_RB_MINMAX(struct window_pane_tree *, int);
struct winlink *winlink_find_by_index(struct winlinks *, int);
struct winlink *winlink_find_by_window(struct winlinks *, struct window *);
struct winlink *winlink_find_by_window_id(struct winlinks *, u_int);
u_int winlink_count(struct winlinks *);
struct winlink *winlink_add(struct winlinks *, int);
void winlink_set_window(struct winlink *, struct window *);
void winlink_remove(struct winlinks *, struct winlink *);
struct winlink *winlink_next(struct winlink *);
struct winlink *winlink_previous(struct winlink *);
struct winlink *winlink_next_by_number(struct winlink *, struct session *, int);
struct winlink *winlink_previous_by_number(struct winlink *, struct session *, int);
void winlink_stack_push(struct winlink_stack *, struct winlink *);
void winlink_stack_remove(struct winlink_stack *, struct winlink *);
struct window *window_find_by_id_str(const char *);
struct window *window_find_by_id(u_int);
void window_update_activity(struct window *);
struct window *window_create(u_int, u_int);
struct window *window_create_spawn(const char *, int, char **, const char *, const char *, const char *, struct environ *, struct termios *, u_int, u_int, u_int, char **);
struct window_pane *window_get_active_at(struct window *, u_int, u_int);
struct window_pane *window_find_string(struct window *, const char *);
int window_has_pane(struct window *, struct window_pane *);
int window_set_active_pane(struct window *, struct window_pane *);
void window_redraw_active_switch(struct window *, struct window_pane *);
struct window_pane *window_add_pane(struct window *, struct window_pane *, int, int, u_int);
void window_resize(struct window *, u_int, u_int);
int window_zoom(struct window_pane *);
int window_unzoom(struct window *);
void window_lost_pane(struct window *, struct window_pane *);
void window_remove_pane(struct window *, struct window_pane *);
struct window_pane *window_pane_at_index(struct window *, u_int);
struct window_pane *window_pane_next_by_number(struct window *, struct window_pane *, u_int);
struct window_pane *window_pane_previous_by_number(struct window *, struct window_pane *, u_int);
int window_pane_index(struct window_pane *, u_int *);
u_int window_count_panes(struct window *);
void window_destroy_panes(struct window *);
struct window_pane *window_pane_find_by_id_str(const char *);
struct window_pane *window_pane_find_by_id(u_int);
int window_pane_destroy_ready(struct window_pane *);
int window_pane_spawn(struct window_pane *, int, char **, const char *, const char *, const char *, struct environ *, struct termios *, char **);
void window_pane_resize(struct window_pane *, u_int, u_int);
void window_pane_alternate_on(struct window_pane *, struct grid_cell *, int);
void window_pane_alternate_off(struct window_pane *, struct grid_cell *, int);
void window_pane_set_palette(struct window_pane *, u_int, int);
void window_pane_unset_palette(struct window_pane *, u_int);
void window_pane_reset_palette(struct window_pane *);
int window_pane_get_palette(const struct window_pane *, int);
int window_pane_set_mode(struct window_pane *, const struct window_mode *, struct cmd_find_state *, struct args *);
void window_pane_reset_mode(struct window_pane *);
void window_pane_key(struct window_pane *, struct client *, struct session *, key_code, struct mouse_event *);
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
void layout_destroy_cell(struct window *, struct layout_cell *, struct layout_cell **);
void layout_set_size(struct layout_cell *, u_int, u_int, u_int, u_int);
void layout_make_leaf(struct layout_cell *, struct window_pane *);
void layout_make_node(struct layout_cell *, enum layout_type);
void layout_fix_offsets(struct layout_cell *);
void layout_fix_panes(struct window *, u_int, u_int);
void layout_resize_adjust(struct window *, struct layout_cell *, enum layout_type, int);
void layout_init(struct window *, struct window_pane *);
void layout_free(struct window *);
void layout_resize(struct window *, u_int, u_int);
void layout_resize_pane(struct window_pane *, enum layout_type, int, int);
void layout_resize_pane_to(struct window_pane *, enum layout_type, u_int);
void layout_assign_pane(struct layout_cell *, struct window_pane *);
struct layout_cell *layout_split_pane(struct window_pane *, enum layout_type, int, int, int);
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
typedef void (*mode_tree_draw_cb)(void *, void *, struct screen_write_ctx *, u_int, u_int);
typedef int (*mode_tree_search_cb)(void *, void *, const char *);
typedef void (*mode_tree_each_cb)(void *, void *, struct client *, key_code);
u_int mode_tree_count_tagged(struct mode_tree_data *);
void *mode_tree_get_current(struct mode_tree_data *);
void mode_tree_expand_current(struct mode_tree_data *);
void mode_tree_set_current(struct mode_tree_data *, uint64_t);
void mode_tree_each_tagged(struct mode_tree_data *, mode_tree_each_cb, struct client *, key_code, int);
void mode_tree_up(struct mode_tree_data *, int);
void mode_tree_down(struct mode_tree_data *, int);
struct mode_tree_data *mode_tree_start(struct window_pane *, struct args *, mode_tree_build_cb, mode_tree_draw_cb, mode_tree_search_cb, void *, const char **, u_int, struct screen **);
void mode_tree_zoom(struct mode_tree_data *, struct args *);
void mode_tree_build(struct mode_tree_data *);
void mode_tree_free(struct mode_tree_data *);
void mode_tree_resize(struct mode_tree_data *, u_int, u_int);
struct mode_tree_item *mode_tree_add(struct mode_tree_data *, struct mode_tree_item *, void *, uint64_t, const char *, const char *, int);
void mode_tree_remove(struct mode_tree_data *, struct mode_tree_item *);
void mode_tree_draw(struct mode_tree_data *);
int mode_tree_key(struct mode_tree_data *, struct client *, key_code *, struct mouse_event *, u_int *, u_int *);
void mode_tree_run_command(struct client *, struct cmd_find_state *, const char *, const char *);
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
void window_copy_add_formats(struct window_pane *, struct format_tree *);
void check_window_name(struct window *);
char *default_window_name(struct window *);
char *parse_window_name(const char *);
void control_callback(struct client *, int, void *);
void control_write(struct client *, const char *, ...);
void control_write_buffer(struct client *, struct evbuffer *);
void control_notify_input(struct client *, struct window_pane *, struct evbuffer *);
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
void sessions_RB_INSERT_COLOR(struct sessions *, struct session *);
void sessions_RB_REMOVE_COLOR(struct sessions *, struct session *, struct session *);
struct session *sessions_RB_REMOVE(struct sessions *, struct session *);
struct session *sessions_RB_INSERT(struct sessions *, struct session *);
struct session *sessions_RB_FIND(struct sessions *, struct session *);
struct session *sessions_RB_NFIND(struct sessions *, struct session *);
struct session *sessions_RB_NEXT(struct session *);
struct session *sessions_RB_PREV(struct session *);
struct session *sessions_RB_MINMAX(struct sessions *, int);
int session_group_cmp(struct session_group *, struct session_group *);
void session_groups_RB_INSERT_COLOR(struct session_groups *, struct session_group *);
void session_groups_RB_REMOVE_COLOR(struct session_groups *, struct session_group *, struct session_group *);
struct session_group *session_groups_RB_REMOVE(struct session_groups *, struct session_group *);
struct session_group *session_groups_RB_INSERT(struct session_groups *, struct session_group *);
struct session_group *session_groups_RB_FIND(struct session_groups *, struct session_group *);
struct session_group *session_groups_RB_NFIND(struct session_groups *, struct session_group *);
struct session_group *session_groups_RB_NEXT(struct session_group *);
struct session_group *session_groups_RB_PREV(struct session_group *);
struct session_group *session_groups_RB_MINMAX(struct session_groups *, int);
int session_alive(struct session *);
struct session *session_find(const char *);
struct session *session_find_by_id_str(const char *);
struct session *session_find_by_id(u_int);
struct session *session_create(const char *, const char *, int, char **, const char *, const char *, struct environ *, struct termios *, int, u_int, u_int, char **);
void session_destroy(struct session *, const char *);
void session_add_ref(struct session *, const char *);
void session_remove_ref(struct session *, const char *);
int session_check_name(const char *);
void session_update_activity(struct session *, struct timeval *);
struct session *session_next_session(struct session *);
struct session *session_previous_session(struct session *);
struct winlink *session_new(struct session *, const char *, int, char **, const char *, const char *, int, char **);
struct winlink *session_attach(struct session *, struct window *, int, char **);
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
int style_parse(const struct grid_cell *, struct grid_cell *, const char *);
const char *style_tostring(struct grid_cell *);
void style_apply(struct grid_cell *, struct options *, const char *);
void style_apply_update(struct grid_cell *, struct options *, const char *);
int style_equal(const struct grid_cell *, const struct grid_cell *);
struct windows windows;
struct window_pane_tree all_window_panes;
static u_int next_window_pane_id;
static u_int next_window_id;
static u_int next_active_point;
static void window_destroy(struct window *);
static struct window_pane *window_pane_create(struct window *, u_int, u_int, u_int);
static void window_pane_destroy(struct window_pane *);
static void window_pane_read_callback(struct bufferevent *, void *);
static void window_pane_error_callback(struct bufferevent *, short, void *);
static int winlink_next_index(struct winlinks *, int);
static struct window_pane *window_pane_choose_best(struct window_pane **, u_int);
void windows_RB_INSERT_COLOR(struct windows *head, struct window *elm)
{
  unsigned int elm_idx = 0;
  struct window *parent;
  unsigned int parent_idx = 0;
  struct window *gparent;
  unsigned int gparent_idx = 0;
  struct window *tmp;
  unsigned int tmp_idx = 0;
  while ((parent_idx = elm->entry.rbe_parent) && (parent->entry.rbe_color == 1))
  {
    helper_windows_RB_INSERT_COLOR_1(&elm_idx, &parent_idx, &gparent_idx, &tmp_idx, head, elm, parent, gparent, tmp);
  }

  head->rbh_root->entry.rbe_color = 0;
}

void windows_RB_REMOVE_COLOR(struct windows *head, struct window *parent, struct window *elm)
{
  unsigned int elm_idx = 0;
  unsigned int parent_idx = 0;
  struct window *tmp;
  unsigned int tmp_idx = 0;
  while ((((&elm[elm_idx]) == 0) || (elm->entry.rbe_color == 0)) && ((&elm[elm_idx]) != head->rbh_root))
  {
    helper_windows_RB_REMOVE_COLOR_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }

  if (elm)
  {
    elm->entry.rbe_color = 0;
  }
}

struct window *windows_RB_REMOVE(struct windows *head, struct window *elm)
{
  unsigned int elm_idx = 0;
  struct window *child;
  unsigned int child_idx = 0;
  struct window *parent;
  unsigned int parent_idx = 0;
  struct window *old = elm;
  int color;
  if (elm->entry.rbe_left == 0)
  {
    child_idx = elm->entry.rbe_right;
  }
  else
    if (elm->entry.rbe_right == 0)
  {
    child_idx = elm->entry.rbe_left;
  }
  else
  {
    helper_windows_RB_REMOVE_1(&elm_idx, &child_idx, &parent_idx, &color, head, elm, child, parent, old);
  }
  parent_idx = elm->entry.rbe_parent;
  color = elm->entry.rbe_color;
  if (child)
  {
    child->entry.rbe_parent = &parent[parent_idx];
  }
  if (parent)
  {
    if (parent->entry.rbe_left == (&elm[elm_idx]))
    {
      parent->entry.rbe_left = &child[child_idx];
    }
    else
      parent->entry.rbe_right = &child[child_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &child[child_idx];
  color:
  if (color == 0)
  {
    windows_RB_REMOVE_COLOR(head, parent, child);
  }

  return old;
}

struct window *windows_RB_INSERT(struct windows *head, struct window *elm)
{
  struct window *tmp;
  unsigned int tmp_idx = 0;
  struct window *parent = 0;
  unsigned int parent_idx = 0;
  int comp = 0;
  tmp_idx = head->rbh_root;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    comp = window_cmp(elm, parent);
    if (comp < 0)
    {
      tmp_idx = tmp_idx->entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->entry.rbe_right;
    }
    else
      return tmp;
  }

  do
  {
    elm->entry.rbe_parent = &parent[parent_idx];
    elm->entry.rbe_left = (elm->entry.rbe_right = 0);
    elm->entry.rbe_color = 1;
  }
  while (0);
  if ((&parent[parent_idx]) != 0)
  {
    if (comp < 0)
    {
      parent->entry.rbe_left = elm;
    }
    else
      parent->entry.rbe_right = elm;
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = elm;
  windows_RB_INSERT_COLOR(head, elm);
  return 0;
}

struct window *windows_RB_FIND(struct windows *head, struct window *elm)
{
  struct window *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  int comp;
  while (tmp)
  {
    comp = window_cmp(elm, tmp);
    if (comp < 0)
    {
      tmp_idx = tmp_idx->entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->entry.rbe_right;
    }
    else
      return tmp;
  }

  return 0;
}

struct window *windows_RB_NFIND(struct windows *head, struct window *elm)
{
  struct window *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct window *res = 0;
  unsigned int res_idx = 0;
  int comp;
  while (tmp)
  {
    comp = window_cmp(elm, tmp);
    if (comp < 0)
    {
      res_idx = &tmp[tmp_idx];
      tmp_idx = tmp_idx->entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->entry.rbe_right;
    }
    else
      return tmp;
  }

  return res;
}

struct window *windows_RB_NEXT(struct window *elm)
{
  unsigned int elm_idx = 0;
  if (elm->entry.rbe_right)
  {
    elm_idx = elm_idx->entry.rbe_right;
    while (elm->entry.rbe_left)
    {
      elm_idx = elm_idx->entry.rbe_left;
    }

  }
  else
  {
    if (elm->entry.rbe_parent && ((&elm[elm_idx]) == elm->entry.rbe_parent->entry.rbe_left))
    {
      elm_idx = elm_idx->entry.rbe_parent;
    }
    else
    {
      while (elm->entry.rbe_parent && ((&elm[elm_idx]) == elm->entry.rbe_parent->entry.rbe_right))
      {
        elm_idx = elm_idx->entry.rbe_parent;
      }

      elm_idx = elm_idx->entry.rbe_parent;
    }
  }
  return elm;
}

struct window *windows_RB_PREV(struct window *elm)
{
  unsigned int elm_idx = 0;
  if (elm->entry.rbe_left)
  {
    elm_idx = elm_idx->entry.rbe_left;
    while (elm->entry.rbe_right)
    {
      elm_idx = elm_idx->entry.rbe_right;
    }

  }
  else
  {
    if (elm->entry.rbe_parent && ((&elm[elm_idx]) == elm->entry.rbe_parent->entry.rbe_right))
    {
      elm_idx = elm_idx->entry.rbe_parent;
    }
    else
    {
      while (elm->entry.rbe_parent && ((&elm[elm_idx]) == elm->entry.rbe_parent->entry.rbe_left))
      {
        elm_idx = elm_idx->entry.rbe_parent;
      }

      elm_idx = elm_idx->entry.rbe_parent;
    }
  }
  return elm;
}

struct window *windows_RB_MINMAX(struct windows *head, int val)
{
  struct window *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct window *parent = 0;
  unsigned int parent_idx = 0;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    if (val < 0)
    {
      tmp_idx = tmp_idx->entry.rbe_left;
    }
    else
      tmp_idx = tmp_idx->entry.rbe_right;
  }

  return parent;
}

void winlinks_RB_INSERT_COLOR(struct winlinks *head, struct winlink *elm)
{
  unsigned int elm_idx = 0;
  struct winlink *parent;
  unsigned int parent_idx = 0;
  struct winlink *gparent;
  unsigned int gparent_idx = 0;
  struct winlink *tmp;
  unsigned int tmp_idx = 0;
  while ((parent_idx = elm->entry.rbe_parent) && (parent->entry.rbe_color == 1))
  {
    helper_winlinks_RB_INSERT_COLOR_1(&elm_idx, &parent_idx, &gparent_idx, &tmp_idx, head, elm, parent, gparent, tmp);
  }

  head->rbh_root->entry.rbe_color = 0;
}

void winlinks_RB_REMOVE_COLOR(struct winlinks *head, struct winlink *parent, struct winlink *elm)
{
  unsigned int elm_idx = 0;
  unsigned int parent_idx = 0;
  struct winlink *tmp;
  unsigned int tmp_idx = 0;
  while ((((&elm[elm_idx]) == 0) || (elm->entry.rbe_color == 0)) && ((&elm[elm_idx]) != head->rbh_root))
  {
    helper_winlinks_RB_REMOVE_COLOR_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }

  if (elm)
  {
    elm->entry.rbe_color = 0;
  }
}

struct winlink *winlinks_RB_REMOVE(struct winlinks *head, struct winlink *elm)
{
  unsigned int elm_idx = 0;
  struct winlink *child;
  unsigned int child_idx = 0;
  struct winlink *parent;
  unsigned int parent_idx = 0;
  struct winlink *old = elm;
  int color;
  if (elm->entry.rbe_left == 0)
  {
    child_idx = elm->entry.rbe_right;
  }
  else
    if (elm->entry.rbe_right == 0)
  {
    child_idx = elm->entry.rbe_left;
  }
  else
  {
    helper_winlinks_RB_REMOVE_1(&elm_idx, &child_idx, &parent_idx, &color, head, elm, child, parent, old);
  }
  parent_idx = elm->entry.rbe_parent;
  color = elm->entry.rbe_color;
  if (child)
  {
    child->entry.rbe_parent = &parent[parent_idx];
  }
  if (parent)
  {
    if (parent->entry.rbe_left == (&elm[elm_idx]))
    {
      parent->entry.rbe_left = &child[child_idx];
    }
    else
      parent->entry.rbe_right = &child[child_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &child[child_idx];
  color:
  if (color == 0)
  {
    winlinks_RB_REMOVE_COLOR(head, parent, child);
  }

  return old;
}

struct winlink *winlinks_RB_INSERT(struct winlinks *head, struct winlink *elm)
{
  struct winlink *tmp;
  unsigned int tmp_idx = 0;
  struct winlink *parent = 0;
  unsigned int parent_idx = 0;
  int comp = 0;
  tmp_idx = head->rbh_root;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    comp = winlink_cmp(elm, parent);
    if (comp < 0)
    {
      tmp_idx = tmp_idx->entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->entry.rbe_right;
    }
    else
      return tmp;
  }

  do
  {
    elm->entry.rbe_parent = &parent[parent_idx];
    elm->entry.rbe_left = (elm->entry.rbe_right = 0);
    elm->entry.rbe_color = 1;
  }
  while (0);
  if ((&parent[parent_idx]) != 0)
  {
    if (comp < 0)
    {
      parent->entry.rbe_left = elm;
    }
    else
      parent->entry.rbe_right = elm;
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = elm;
  winlinks_RB_INSERT_COLOR(head, elm);
  return 0;
}

struct winlink *winlinks_RB_FIND(struct winlinks *head, struct winlink *elm)
{
  struct winlink *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  int comp;
  while (tmp)
  {
    comp = winlink_cmp(elm, tmp);
    if (comp < 0)
    {
      tmp_idx = tmp_idx->entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->entry.rbe_right;
    }
    else
      return tmp;
  }

  return 0;
}

struct winlink *winlinks_RB_NFIND(struct winlinks *head, struct winlink *elm)
{
  struct winlink *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct winlink *res = 0;
  unsigned int res_idx = 0;
  int comp;
  while (tmp)
  {
    comp = winlink_cmp(elm, tmp);
    if (comp < 0)
    {
      res_idx = &tmp[tmp_idx];
      tmp_idx = tmp_idx->entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->entry.rbe_right;
    }
    else
      return tmp;
  }

  return res;
}

struct winlink *winlinks_RB_NEXT(struct winlink *elm)
{
  unsigned int elm_idx = 0;
  if (elm->entry.rbe_right)
  {
    elm_idx = elm_idx->entry.rbe_right;
    while (elm->entry.rbe_left)
    {
      elm_idx = elm_idx->entry.rbe_left;
    }

  }
  else
  {
    if (elm->entry.rbe_parent && ((&elm[elm_idx]) == elm->entry.rbe_parent->entry.rbe_left))
    {
      elm_idx = elm_idx->entry.rbe_parent;
    }
    else
    {
      while (elm->entry.rbe_parent && ((&elm[elm_idx]) == elm->entry.rbe_parent->entry.rbe_right))
      {
        elm_idx = elm_idx->entry.rbe_parent;
      }

      elm_idx = elm_idx->entry.rbe_parent;
    }
  }
  return elm;
}

struct winlink *winlinks_RB_PREV(struct winlink *elm)
{
  unsigned int elm_idx = 0;
  if (elm->entry.rbe_left)
  {
    elm_idx = elm_idx->entry.rbe_left;
    while (elm->entry.rbe_right)
    {
      elm_idx = elm_idx->entry.rbe_right;
    }

  }
  else
  {
    if (elm->entry.rbe_parent && ((&elm[elm_idx]) == elm->entry.rbe_parent->entry.rbe_right))
    {
      elm_idx = elm_idx->entry.rbe_parent;
    }
    else
    {
      while (elm->entry.rbe_parent && ((&elm[elm_idx]) == elm->entry.rbe_parent->entry.rbe_left))
      {
        elm_idx = elm_idx->entry.rbe_parent;
      }

      elm_idx = elm_idx->entry.rbe_parent;
    }
  }
  return elm;
}

struct winlink *winlinks_RB_MINMAX(struct winlinks *head, int val)
{
  struct winlink *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct winlink *parent = 0;
  unsigned int parent_idx = 0;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    if (val < 0)
    {
      tmp_idx = tmp_idx->entry.rbe_left;
    }
    else
      tmp_idx = tmp_idx->entry.rbe_right;
  }

  return parent;
}

void window_pane_tree_RB_INSERT_COLOR(struct window_pane_tree *head, struct window_pane *elm)
{
  unsigned int elm_idx = 0;
  struct window_pane *parent;
  unsigned int parent_idx = 0;
  struct window_pane *gparent;
  unsigned int gparent_idx = 0;
  struct window_pane *tmp;
  unsigned int tmp_idx = 0;
  while ((parent_idx = elm->tree_entry.rbe_parent) && (parent->tree_entry.rbe_color == 1))
  {
    helper_window_pane_tree_RB_INSERT_COLOR_1(&elm_idx, &parent_idx, &gparent_idx, &tmp_idx, head, elm, parent, gparent, tmp);
  }

  head->rbh_root->tree_entry.rbe_color = 0;
}

void window_pane_tree_RB_REMOVE_COLOR(struct window_pane_tree *head, struct window_pane *parent, struct window_pane *elm)
{
  unsigned int elm_idx = 0;
  unsigned int parent_idx = 0;
  struct window_pane *tmp;
  unsigned int tmp_idx = 0;
  while ((((&elm[elm_idx]) == 0) || (elm->tree_entry.rbe_color == 0)) && ((&elm[elm_idx]) != head->rbh_root))
  {
    helper_window_pane_tree_RB_REMOVE_COLOR_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }

  if (elm)
  {
    elm->tree_entry.rbe_color = 0;
  }
}

struct window_pane *window_pane_tree_RB_REMOVE(struct window_pane_tree *head, struct window_pane *elm)
{
  unsigned int elm_idx = 0;
  struct window_pane *child;
  unsigned int child_idx = 0;
  struct window_pane *parent;
  unsigned int parent_idx = 0;
  struct window_pane *old = elm;
  int color;
  if (elm->tree_entry.rbe_left == 0)
  {
    child_idx = elm->tree_entry.rbe_right;
  }
  else
    if (elm->tree_entry.rbe_right == 0)
  {
    child_idx = elm->tree_entry.rbe_left;
  }
  else
  {
    helper_window_pane_tree_RB_REMOVE_1(&elm_idx, &child_idx, &parent_idx, &color, head, elm, child, parent, old);
  }
  parent_idx = elm->tree_entry.rbe_parent;
  color = elm->tree_entry.rbe_color;
  if (child)
  {
    child->tree_entry.rbe_parent = &parent[parent_idx];
  }
  if (parent)
  {
    if (parent->tree_entry.rbe_left == (&elm[elm_idx]))
    {
      parent->tree_entry.rbe_left = &child[child_idx];
    }
    else
      parent->tree_entry.rbe_right = &child[child_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &child[child_idx];
  color:
  if (color == 0)
  {
    window_pane_tree_RB_REMOVE_COLOR(head, parent, child);
  }

  return old;
}

struct window_pane *window_pane_tree_RB_INSERT(struct window_pane_tree *head, struct window_pane *elm)
{
  struct window_pane *tmp;
  unsigned int tmp_idx = 0;
  struct window_pane *parent = 0;
  unsigned int parent_idx = 0;
  int comp = 0;
  tmp_idx = head->rbh_root;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    comp = window_pane_cmp(elm, parent);
    if (comp < 0)
    {
      tmp_idx = tmp_idx->tree_entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->tree_entry.rbe_right;
    }
    else
      return tmp;
  }

  do
  {
    elm->tree_entry.rbe_parent = &parent[parent_idx];
    elm->tree_entry.rbe_left = (elm->tree_entry.rbe_right = 0);
    elm->tree_entry.rbe_color = 1;
  }
  while (0);
  if ((&parent[parent_idx]) != 0)
  {
    if (comp < 0)
    {
      parent->tree_entry.rbe_left = elm;
    }
    else
      parent->tree_entry.rbe_right = elm;
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = elm;
  window_pane_tree_RB_INSERT_COLOR(head, elm);
  return 0;
}

struct window_pane *window_pane_tree_RB_FIND(struct window_pane_tree *head, struct window_pane *elm)
{
  struct window_pane *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  int comp;
  while (tmp)
  {
    comp = window_pane_cmp(elm, tmp);
    if (comp < 0)
    {
      tmp_idx = tmp_idx->tree_entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->tree_entry.rbe_right;
    }
    else
      return tmp;
  }

  return 0;
}

struct window_pane *window_pane_tree_RB_NFIND(struct window_pane_tree *head, struct window_pane *elm)
{
  struct window_pane *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct window_pane *res = 0;
  unsigned int res_idx = 0;
  int comp;
  while (tmp)
  {
    comp = window_pane_cmp(elm, tmp);
    if (comp < 0)
    {
      res_idx = &tmp[tmp_idx];
      tmp_idx = tmp_idx->tree_entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->tree_entry.rbe_right;
    }
    else
      return tmp;
  }

  return res;
}

struct window_pane *window_pane_tree_RB_NEXT(struct window_pane *elm)
{
  unsigned int elm_idx = 0;
  if (elm->tree_entry.rbe_right)
  {
    elm_idx = elm_idx->tree_entry.rbe_right;
    while (elm->tree_entry.rbe_left)
    {
      elm_idx = elm_idx->tree_entry.rbe_left;
    }

  }
  else
  {
    if (elm->tree_entry.rbe_parent && ((&elm[elm_idx]) == elm->tree_entry.rbe_parent->tree_entry.rbe_left))
    {
      elm_idx = elm_idx->tree_entry.rbe_parent;
    }
    else
    {
      while (elm->tree_entry.rbe_parent && ((&elm[elm_idx]) == elm->tree_entry.rbe_parent->tree_entry.rbe_right))
      {
        elm_idx = elm_idx->tree_entry.rbe_parent;
      }

      elm_idx = elm_idx->tree_entry.rbe_parent;
    }
  }
  return elm;
}

struct window_pane *window_pane_tree_RB_PREV(struct window_pane *elm)
{
  unsigned int elm_idx = 0;
  if (elm->tree_entry.rbe_left)
  {
    elm_idx = elm_idx->tree_entry.rbe_left;
    while (elm->tree_entry.rbe_right)
    {
      elm_idx = elm_idx->tree_entry.rbe_right;
    }

  }
  else
  {
    if (elm->tree_entry.rbe_parent && ((&elm[elm_idx]) == elm->tree_entry.rbe_parent->tree_entry.rbe_right))
    {
      elm_idx = elm_idx->tree_entry.rbe_parent;
    }
    else
    {
      while (elm->tree_entry.rbe_parent && ((&elm[elm_idx]) == elm->tree_entry.rbe_parent->tree_entry.rbe_left))
      {
        elm_idx = elm_idx->tree_entry.rbe_parent;
      }

      elm_idx = elm_idx->tree_entry.rbe_parent;
    }
  }
  return elm;
}

struct window_pane *window_pane_tree_RB_MINMAX(struct window_pane_tree *head, int val)
{
  struct window_pane *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct window_pane *parent = 0;
  unsigned int parent_idx = 0;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    if (val < 0)
    {
      tmp_idx = tmp_idx->tree_entry.rbe_left;
    }
    else
      tmp_idx = tmp_idx->tree_entry.rbe_right;
  }

  return parent;
}

int window_cmp(struct window *w1, struct window *w2)
{
  return w1->id - w2->id;
}

int winlink_cmp(struct winlink *wl1, struct winlink *wl2)
{
  return wl1->idx - wl2->idx;
}

int window_pane_cmp(struct window_pane *wp1, struct window_pane *wp2)
{
  return wp1->id - wp2->id;
}

struct winlink *winlink_find_by_window(struct winlinks *wwl, struct window *w)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  for (wl_idx = winlinks_RB_MINMAX(wwl, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    if (wl->window == w)
    {
      return wl;
    }
  }

  return 0;
}

struct winlink *winlink_find_by_index(struct winlinks *wwl, int idx)
{
  struct winlink wl;
  if (idx < 0)
  {
    fatalx("bad index");
  }
  wl.idx = idx;
  return winlinks_RB_FIND(wwl, &wl);
}

struct winlink *winlink_find_by_window_id(struct winlinks *wwl, u_int id)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  for (wl_idx = winlinks_RB_MINMAX(wwl, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    if (wl->window->id == id)
    {
      return wl;
    }
  }

  return 0;
}

static int winlink_next_index(struct winlinks *wwl, int idx)
{
  int i;
  i = idx;
  do
  {
    if (winlink_find_by_index(wwl, i) == 0)
    {
      return i;
    }
    if (i == 2147483647)
    {
      i = 0;
    }
    else
      i++;
    i += 1;
  }
  while (i != idx);
  return -1;
}

u_int winlink_count(struct winlinks *wwl)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  u_int n;
  n = 0;
  for (wl_idx = winlinks_RB_MINMAX(wwl, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    n += 1;
  }

  return n;
}

struct winlink *winlink_add(struct winlinks *wwl, int idx)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  if (idx < 0)
  {
    if ((idx = winlink_next_index(wwl, (-idx) - 1)) == (-1))
    {
      return 0;
    }
  }
  else
    if (winlink_find_by_index(wwl, idx) != 0)
  {
    return 0;
  }
  wl_idx = xcalloc(1, sizeof(*wl_idx));
  wl->idx = idx;
  winlinks_RB_INSERT(wwl, wl);
  return wl;
}

void winlink_set_window(struct winlink *wl, struct window *w)
{
  if (wl->window != 0)
  {
    do
    {
      if (wl->wentry.tqe_next != 0)
      {
        wl->wentry.tqe_next->wentry.tqe_prev = wl->wentry.tqe_prev;
      }
      else
        (&wl->window->winlinks)->tqh_last = wl->wentry.tqe_prev;
      *wl->wentry.tqe_prev = wl->wentry.tqe_next;
      ;
      ;
    }
    while (0);
    window_remove_ref(wl->window, __func__);
  }
  do
  {
    wl->wentry.tqe_next = 0;
    wl->wentry.tqe_prev = (&w->winlinks)->tqh_last;
    *(&w->winlinks)->tqh_last = wl;
    (&w->winlinks)->tqh_last = &wl->wentry.tqe_next;
  }
  while (0);
  wl->window = w;
  window_add_ref(w, __func__);
}

void winlink_remove(struct winlinks *wwl, struct winlink *wl)
{
  struct window *w = wl->window;
  if (w != 0)
  {
    do
    {
      if (wl->wentry.tqe_next != 0)
      {
        wl->wentry.tqe_next->wentry.tqe_prev = wl->wentry.tqe_prev;
      }
      else
        (&w->winlinks)->tqh_last = wl->wentry.tqe_prev;
      *wl->wentry.tqe_prev = wl->wentry.tqe_next;
      ;
      ;
    }
    while (0);
    window_remove_ref(w, __func__);
  }
  winlinks_RB_REMOVE(wwl, wl);
  free(wl->status_text);
  free(wl);
}

struct winlink *winlink_next(struct winlink *wl)
{
  return winlinks_RB_NEXT(wl);
}

struct winlink *winlink_previous(struct winlink *wl)
{
  return winlinks_RB_PREV(wl);
}

struct winlink *winlink_next_by_number(struct winlink *wl, struct session *s, int n)
{
  unsigned int wl_idx = 0;
  for (; n > 0; n -= 1)
  {
    if ((wl_idx = winlinks_RB_NEXT(wl_idx)) == 0)
    {
      wl_idx = winlinks_RB_MINMAX(&s->windows, -1);
    }
  }

  return wl;
}

struct winlink *winlink_previous_by_number(struct winlink *wl, struct session *s, int n)
{
  unsigned int wl_idx = 0;
  for (; n > 0; n -= 1)
  {
    if ((wl_idx = winlinks_RB_PREV(wl_idx)) == 0)
    {
      wl_idx = winlinks_RB_MINMAX(&s->windows, 1);
    }
  }

  return wl;
}

void winlink_stack_push(struct winlink_stack *stack, struct winlink *wl)
{
  if (wl == 0)
  {
    return;
  }
  winlink_stack_remove(stack, wl);
  do
  {
    if ((wl->sentry.tqe_next = stack->tqh_first) != 0)
    {
      stack->tqh_first->sentry.tqe_prev = &wl->sentry.tqe_next;
    }
    else
      stack->tqh_last = &wl->sentry.tqe_next;
    stack->tqh_first = wl;
    wl->sentry.tqe_prev = &stack->tqh_first;
  }
  while (0);
}

void winlink_stack_remove(struct winlink_stack *stack, struct winlink *wl)
{
  struct winlink *wl2;
  unsigned int wl2_idx = 0;
  if (wl == 0)
  {
    return;
  }
  for (wl2_idx = stack->tqh_first; (&wl2[wl2_idx]) != 0; wl2_idx = wl2_idx->sentry.tqe_next)
  {
    if ((&wl2[wl2_idx]) == wl)
    {
      do
      {
        if (wl->sentry.tqe_next != 0)
        {
          wl->sentry.tqe_next->sentry.tqe_prev = wl->sentry.tqe_prev;
        }
        else
          stack->tqh_last = wl->sentry.tqe_prev;
        *wl->sentry.tqe_prev = wl->sentry.tqe_next;
        ;
        ;
      }
      while (0);
      return;
    }
  }

}

struct window *window_find_by_id_str(const char *s)
{
  const char *errstr;
  u_int id;
  if ((*s) != '@')
  {
    return 0;
  }
  id = strtonum(s + 1, 0, 4294967295U, &errstr);
  if (errstr != 0)
  {
    return 0;
  }
  return window_find_by_id(id);
}

struct window *window_find_by_id(u_int id)
{
  struct window w;
  w.id = id;
  return windows_RB_FIND(&windows, &w);
}

void window_update_activity(struct window *w)
{
  gettimeofday(&w->activity_time, 0);
  alerts_queue(w, 0x2);
}

struct window *window_create(u_int sx, u_int sy)
{
  struct window *w;
  unsigned int w_idx = 0;
  w_idx = xcalloc(1, sizeof(*w_idx));
  w->name = 0;
  w->flags = 0x8000;
  do
  {
    (&w->panes)->tqh_first = 0;
    (&w->panes)->tqh_last = &(&w->panes)->tqh_first;
  }
  while (0);
  w->active = 0;
  w->lastlayout = -1;
  w->layout_root = 0;
  w->sx = sx;
  w->sy = sy;
  w->options = options_create(global_w_options);
  w->references = 0;
  do
  {
    (&w->winlinks)->tqh_first = 0;
    (&w->winlinks)->tqh_last = &(&w->winlinks)->tqh_first;
  }
  while (0);
  w->id = next_window_id;
  next_window_id += 1;
  windows_RB_INSERT(&windows, w);
  window_update_activity(w);
  return w;
}

struct window *window_create_spawn(const char *name, int argc, char **argv, const char *path, const char *shell, const char *cwd, struct environ *env, struct termios *tio, u_int sx, u_int sy, u_int hlimit, char **cause)
{
  struct window *w;
  unsigned int w_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  w_idx = window_create(sx, sy);
  wp_idx = window_add_pane(w, 0, 0, 0, hlimit);
  layout_init(w, wp);
  if (window_pane_spawn(wp, argc, argv, path, shell, cwd, env, tio, cause) != 0)
  {
    window_destroy(w);
    return 0;
  }
  w->active = (&w->panes)->tqh_first;
  if (name != 0)
  {
    w->name = xstrdup(name);
    options_set_number(w->options, "automatic-rename", 0);
  }
  else
    w->name = default_window_name(w);
  notify_window("window-pane-changed", w);
  return w;
}

static void window_destroy(struct window *w)
{
  log_debug("window @%u destroyed (%d references)", w->id, w->references);
  windows_RB_REMOVE(&windows, w);
  if (w->layout_root != 0)
  {
    layout_free_cell(w->layout_root);
  }
  if (w->saved_layout_root != 0)
  {
    layout_free_cell(w->saved_layout_root);
  }
  free(w->old_layout);
  if (event_initialized(&w->name_event))
  {
    evtimer_del(&w->name_event);
  }
  if (event_initialized(&w->alerts_timer))
  {
    evtimer_del(&w->alerts_timer);
  }
  options_free(w->options);
  window_destroy_panes(w);
  free(w->name);
  free(w);
}

int window_pane_destroy_ready(struct window_pane *wp)
{
  int n;
  if (wp->pipe_fd != (-1))
  {
    if (EVBUFFER_LENGTH(wp->pipe_event->output) != 0)
    {
      return 0;
    }
    if ((ioctl(wp->fd, FIONREAD, &n) != (-1)) && (n > 0))
    {
      return 0;
    }
  }
  if ((~wp->flags) & 0x100)
  {
    return 0;
  }
  return 1;
}

void window_add_ref(struct window *w, const char *from)
{
  w->references += 1;
  log_debug("%s: @%u %s, now %d", __func__, w->id, from, w->references);
}

void window_remove_ref(struct window *w, const char *from)
{
  w->references -= 1;
  log_debug("%s: @%u %s, now %d", __func__, w->id, from, w->references);
  if (w->references == 0)
  {
    window_destroy(w);
  }
}

void window_set_name(struct window *w, const char *new_name)
{
  free(w->name);
  utf8_stravis(&w->name, new_name, ((0x01 | 0x02) | 0x08) | 0x10);
  notify_window("window-renamed", w);
}

void window_resize(struct window *w, u_int sx, u_int sy)
{
  w->sx = sx;
  w->sy = sy;
}

int window_has_pane(struct window *w, struct window_pane *wp)
{
  struct window_pane *wp1;
  unsigned int wp1_idx = 0;
  for (wp1_idx = (&w->panes)->tqh_first; (&wp1[wp1_idx]) != 0; wp1_idx = wp1_idx->entry.tqe_next)
  {
    if ((&wp1[wp1_idx]) == wp)
    {
      return 1;
    }
  }

  return 0;
}

int window_set_active_pane(struct window *w, struct window_pane *wp)
{
  log_debug("%s: pane %%%u (was %%%u)", __func__, wp->id, w->active->id);
  if (wp == w->active)
  {
    return 0;
  }
  w->last = w->active;
  w->active = wp;
  while (!window_pane_visible(w->active))
  {
    w->active = *((struct window_panes *) w->active->entry.tqe_prev)->tqh_last;
    if (w->active == 0)
    {
      w->active = *((struct window_panes *) (&w->panes)->tqh_last)->tqh_last;
    }
    if (w->active == wp)
    {
      notify_window("window-pane-changed", w);
      return 1;
    }
  }

  w->active->active_point = next_active_point;
  next_active_point += 1;
  w->active->flags |= 0x80;
  notify_window("window-pane-changed", w);
  return 1;
}

void window_redraw_active_switch(struct window *w, struct window_pane *wp)
{
  const struct grid_cell *gc;
  unsigned int gc_idx = 0;
  if (wp == w->active)
  {
    return;
  }
  gc_idx = options_get_style(w->options, "window-active-style");
  if (style_equal(gc, options_get_style(w->options, "window-style")))
  {
    return;
  }
  if (((window_pane_get_palette(w->active, w->active->colgc.fg) != (-1)) || (window_pane_get_palette(w->active, w->active->colgc.bg) != (-1))) || style_equal(&grid_default_cell, &w->active->colgc))
  {
    w->active->flags |= 0x1;
  }
  if (((window_pane_get_palette(wp, wp->colgc.fg) != (-1)) || (window_pane_get_palette(wp, wp->colgc.bg) != (-1))) || style_equal(&grid_default_cell, &wp->colgc))
  {
    wp->flags |= 0x1;
  }
}

struct window_pane *window_get_active_at(struct window *w, u_int x, u_int y)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    if (!window_pane_visible(wp))
    {
      continue;
    }
    if ((x < wp->xoff) || (x > (wp->xoff + wp->sx)))
    {
      continue;
    }
    if ((y < wp->yoff) || (y > (wp->yoff + wp->sy)))
    {
      continue;
    }
    return wp;
  }

  return 0;
}

struct window_pane *window_find_string(struct window *w, const char *s)
{
  u_int x;
  u_int y;
  x = w->sx / 2;
  y = w->sy / 2;
  if (strcasecmp(s, "top") == 0)
  {
    y = 0;
  }
  else
    if (strcasecmp(s, "bottom") == 0)
  {
    y = w->sy - 1;
  }
  else
    if (strcasecmp(s, "left") == 0)
  {
    x = 0;
  }
  else
    if (strcasecmp(s, "right") == 0)
  {
    x = w->sx - 1;
  }
  else
    if (strcasecmp(s, "top-left") == 0)
  {
    x = 0;
    y = 0;
  }
  else
    if (strcasecmp(s, "top-right") == 0)
  {
    x = w->sx - 1;
    y = 0;
  }
  else
    if (strcasecmp(s, "bottom-left") == 0)
  {
    x = 0;
    y = w->sy - 1;
  }
  else
    if (strcasecmp(s, "bottom-right") == 0)
  {
    x = w->sx - 1;
    y = w->sy - 1;
  }
  else
    return 0;
  return window_get_active_at(w, x, y);
}

int window_zoom(struct window_pane *wp)
{
  struct window *w = wp->window;
  struct window_pane *wp1;
  unsigned int wp1_idx = 0;
  if (w->flags & 0x1000)
  {
    return -1;
  }
  if (!window_pane_visible(wp))
  {
    return -1;
  }
  if (window_count_panes(w) == 1)
  {
    return -1;
  }
  if (w->active != wp)
  {
    window_set_active_pane(w, wp);
  }
  for (wp1_idx = (&w->panes)->tqh_first; (&wp1[wp1_idx]) != 0; wp1_idx = wp1_idx->entry.tqe_next)
  {
    wp1->saved_layout_cell = wp1->layout_cell;
    wp1->layout_cell = 0;
  }

  w->saved_layout_root = w->layout_root;
  layout_init(w, wp);
  w->flags |= 0x1000;
  notify_window("window-layout-changed", w);
  return 0;
}

int window_unzoom(struct window *w)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  if (!(w->flags & 0x1000))
  {
    return -1;
  }
  w->flags &= ~0x1000;
  layout_free(w);
  w->layout_root = w->saved_layout_root;
  w->saved_layout_root = 0;
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    wp->layout_cell = wp->saved_layout_cell;
    wp->saved_layout_cell = 0;
  }

  layout_fix_panes(w, w->sx, w->sy);
  notify_window("window-layout-changed", w);
  return 0;
}

struct window_pane *window_add_pane(struct window *w, struct window_pane *other, int before, int full_size, u_int hlimit)
{
  unsigned int other_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  if ((&other[other_idx]) == 0)
  {
    other_idx = w->active;
  }
  wp_idx = window_pane_create(w, w->sx, w->sy, hlimit);
  if ((&w->panes)->tqh_first == 0)
  {
    log_debug("%s: @%u at start", __func__, w->id);
    do
    {
      if ((wp->entry.tqe_next = (&w->panes)->tqh_first) != 0)
      {
        (&w->panes)->tqh_first->entry.tqe_prev = &wp->entry.tqe_next;
      }
      else
        (&w->panes)->tqh_last = &wp->entry.tqe_next;
      (&w->panes)->tqh_first = &wp[wp_idx];
      wp->entry.tqe_prev = &(&w->panes)->tqh_first;
    }
    while (0);
  }
  else
    if (before)
  {
    helper_window_add_pane_1(w, other, full_size, other_idx, wp, wp_idx);
  }
  else
  {
    helper_window_add_pane_2(w, other, full_size, wp, wp_idx);
  }
  return wp;
}

void window_lost_pane(struct window *w, struct window_pane *wp)
{
  log_debug("%s: @%u pane %%%u", __func__, w->id, wp->id);
  if (wp == marked_pane.wp)
  {
    server_clear_marked();
  }
  if (wp == w->active)
  {
    w->active = w->last;
    w->last = 0;
    if (w->active == 0)
    {
      w->active = *((struct window_panes *) wp->entry.tqe_prev)->tqh_last;
      if (w->active == 0)
      {
        w->active = wp->entry.tqe_next;
      }
    }
    if (w->active != 0)
    {
      w->active->flags |= 0x80;
      notify_window("window-pane-changed", w);
    }
  }
  else
    if (wp == w->last)
  {
    w->last = 0;
  }
}

void window_remove_pane(struct window *w, struct window_pane *wp)
{
  window_lost_pane(w, wp);
  do
  {
    if (wp->entry.tqe_next != 0)
    {
      wp->entry.tqe_next->entry.tqe_prev = wp->entry.tqe_prev;
    }
    else
      (&w->panes)->tqh_last = wp->entry.tqe_prev;
    *wp->entry.tqe_prev = wp->entry.tqe_next;
    ;
    ;
  }
  while (0);
  window_pane_destroy(wp);
}

struct window_pane *window_pane_at_index(struct window *w, u_int idx)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int n;
  n = options_get_number(w->options, "pane-base-index");
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    if (n == idx)
    {
      return wp;
    }
    n += 1;
  }

  return 0;
}

struct window_pane *window_pane_next_by_number(struct window *w, struct window_pane *wp, u_int n)
{
  unsigned int wp_idx = 0;
  for (; n > 0; n -= 1)
  {
    if ((wp_idx = wp_idx->entry.tqe_next) == 0)
    {
      wp_idx = (&w->panes)->tqh_first;
    }
  }

  return wp;
}

struct window_pane *window_pane_previous_by_number(struct window *w, struct window_pane *wp, u_int n)
{
  unsigned int wp_idx = 0;
  for (; n > 0; n -= 1)
  {
    if ((wp_idx = *((struct window_panes *) wp_idx->entry.tqe_prev)->tqh_last) == 0)
    {
      wp_idx = *((struct window_panes *) (&w->panes)->tqh_last)->tqh_last;
    }
  }

  return wp;
}

int window_pane_index(struct window_pane *wp, u_int *i)
{
  struct window_pane *wq;
  unsigned int wq_idx = 0;
  struct window *w = wp->window;
  *i = options_get_number(w->options, "pane-base-index");
  for (wq_idx = (&w->panes)->tqh_first; (&wq[wq_idx]) != 0; wq_idx = wq_idx->entry.tqe_next)
  {
    if (wp == (&wq[wq_idx]))
    {
      return 0;
    }
    *i += 1;
  }

  return -1;
}

u_int window_count_panes(struct window *w)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int n;
  n = 0;
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    n += 1;
  }

  return n;
}

void window_destroy_panes(struct window *w)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  while (!((&w->panes)->tqh_first == 0))
  {
    wp_idx = (&w->panes)->tqh_first;
    do
    {
      if (wp->entry.tqe_next != 0)
      {
        wp->entry.tqe_next->entry.tqe_prev = wp->entry.tqe_prev;
      }
      else
        (&w->panes)->tqh_last = wp->entry.tqe_prev;
      *wp->entry.tqe_prev = wp->entry.tqe_next;
      ;
      ;
    }
    while (0);
    window_pane_destroy(wp);
  }

}

const char *window_printable_flags(struct winlink *wl)
{
  struct session *s = wl->session;
  static char flags[32];
  int pos;
  pos = 0;
  if (wl->flags & 0x2)
  {
    flags[pos] = '#';
    pos += 1;
  }
  if (wl->flags & 0x1)
  {
    flags[pos] = '!';
    pos += 1;
  }
  if (wl->flags & 0x4)
  {
    flags[pos] = '~';
    pos += 1;
  }
  if (wl == s->curw)
  {
    flags[pos] = '*';
    pos += 1;
  }
  if (wl == (&s->lastw)->tqh_first)
  {
    flags[pos] = '-';
    pos += 1;
  }
  if (server_check_marked() && (wl == marked_pane.wl))
  {
    flags[pos] = 'M';
    pos += 1;
  }
  if (wl->window->flags & 0x1000)
  {
    flags[pos] = 'Z';
    pos += 1;
  }
  flags[pos] = '\0';
  return flags;
}

struct window_pane *window_pane_find_by_id_str(const char *s)
{
  const char *errstr;
  u_int id;
  if ((*s) != '%')
  {
    return 0;
  }
  id = strtonum(s + 1, 0, 4294967295U, &errstr);
  if (errstr != 0)
  {
    return 0;
  }
  return window_pane_find_by_id(id);
}

struct window_pane *window_pane_find_by_id(u_int id)
{
  struct window_pane wp;
  wp.id = id;
  return window_pane_tree_RB_FIND(&all_window_panes, &wp);
}

static struct window_pane *window_pane_create(struct window *w, u_int sx, u_int sy, u_int hlimit)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  char host[255 + 1];
  wp_idx = xcalloc(1, sizeof(*wp_idx));
  wp->window = w;
  wp->id = next_window_pane_id;
  next_window_pane_id += 1;
  window_pane_tree_RB_INSERT(&all_window_panes, wp);
  wp->argc = 0;
  wp->argv = 0;
  wp->shell = 0;
  wp->cwd = 0;
  wp->fd = -1;
  wp->event = 0;
  wp->mode = 0;
  wp->modeprefix = 1;
  wp->layout_cell = 0;
  wp->xoff = 0;
  wp->yoff = 0;
  wp->sx = (wp->osx = sx);
  wp->sy = (wp->osx = sy);
  wp->pipe_fd = -1;
  wp->pipe_off = 0;
  wp->pipe_event = 0;
  wp->saved_grid = 0;
  memcpy(&wp->colgc, &grid_default_cell, sizeof(wp->colgc));
  screen_init(&wp->base, sx, sy, hlimit);
  wp->screen = &wp->base;
  screen_init(&wp->status_screen, 1, 1, 0);
  if (gethostname(host, sizeof(host)) == 0)
  {
    screen_set_title(&wp->base, host);
  }
  input_init(wp);
  return wp;
}

static void window_pane_destroy(struct window_pane *wp)
{
  window_pane_reset_mode(wp);
  free(wp->searchstr);
  if (wp->fd != (-1))
  {
    bufferevent_free(wp->event);
    close(wp->fd);
  }
  input_free(wp);
  screen_free(&wp->base);
  if (wp->saved_grid != 0)
  {
    grid_destroy(wp->saved_grid);
  }
  if (wp->pipe_fd != (-1))
  {
    bufferevent_free(wp->pipe_event);
    close(wp->pipe_fd);
  }
  if (event_initialized(&wp->resize_timer))
  {
    event_del(&wp->resize_timer);
  }
  window_pane_tree_RB_REMOVE(&all_window_panes, wp);
  free((void *) wp->cwd);
  free(wp->shell);
  cmd_free_argv(wp->argc, wp->argv);
  free(wp->palette);
  free(wp);
}

int window_pane_spawn(struct window_pane *wp, int argc, char **argv, const char *path, const char *shell, const char *cwd, struct environ *env, struct termios *tio, char **cause)
{
  unsigned int cwd_idx = 0;
  struct winsize ws;
  char *argv0;
  char *cmd;
  unsigned int cmd_idx = 0;
  char **argvp;
  unsigned int argvp_idx = 0;
  const char *ptr;
  unsigned int ptr_idx = 0;
  const char *first;
  unsigned int first_idx = 0;
  const char *home;
  unsigned int home_idx = 0;
  struct termios tio2;
  int i;
  sigset_t set;
  sigset_t oldset;
  if (wp->fd != (-1))
  {
    bufferevent_free(wp->event);
    close(wp->fd);
  }
  if (argc > 0)
  {
    cmd_free_argv(wp->argc, wp->argv);
    wp->argc = argc;
    wp->argv = cmd_copy_argv(argc, argv);
  }
  if (shell != 0)
  {
    free(wp->shell);
    wp->shell = xstrdup(shell);
  }
  if ((&cwd[cwd_idx]) != 0)
  {
    free((void *) wp->cwd);
    wp->cwd = xstrdup(cwd);
  }
  wp->flags &= ~(0x200 | 0x400);
  cmd_idx = cmd_stringify_argv(wp->argc, wp->argv);
  log_debug("spawn: %s -- %s", wp->shell, cmd);
  for (i = 0; i < wp->argc; i += 1)
  {
    log_debug("spawn: argv[%d] = %s", i, wp->argv[i]);
  }

  environ_log(env, "spawn: ");
  memset(&ws, 0, sizeof(ws));
  ws.ws_col = (&wp->base)->grid->sx;
  ws.ws_row = (&wp->base)->grid->sy;
  sigfillset(&set);
  sigprocmask(SIG_BLOCK, &set, &oldset);
  switch (wp->pid = fdforkpty(ptm_fd, &wp->fd, wp->tty, 0, &ws))
  {
    case -1:
    {
      wp->fd = -1;
      xasprintf(cause, "%s: %s", cmd, strerror(errno));
      free(cmd);
      sigprocmask(SIG_SETMASK, &oldset, 0);
      return -1;
    }

    case 0:
    {
      helper_window_pane_spawn_1(&cwd_idx, &argvp_idx, &ptr_idx, &first_idx, &home_idx, &tio2, wp, path, cwd, env, tio, argv0, argvp, ptr, first, home, oldset);
    }

  }

  sigprocmask(SIG_SETMASK, &oldset, 0);
  setblocking(wp->fd, 0);
  wp->event = bufferevent_new(wp->fd, window_pane_read_callback, 0, window_pane_error_callback, wp);
  bufferevent_setwatermark(wp->event, EV_READ, 0, 4096);
  bufferevent_enable(wp->event, EV_READ | EV_WRITE);
  free(cmd);
  return 0;
}

static void window_pane_read_callback(struct bufferevent *bufev, void *data)
{
  struct window_pane *wp = data;
  struct evbuffer *evb = wp->event->input;
  size_t size = EVBUFFER_LENGTH(evb);
  char *new_data;
  unsigned int new_data_idx = 0;
  size_t new_size;
  new_size = size - wp->pipe_off;
  if ((wp->pipe_fd != (-1)) && (new_size > 0))
  {
    new_data_idx = EVBUFFER_DATA(evb) + wp->pipe_off;
    bufferevent_write(wp->pipe_event, new_data, new_size);
  }
  log_debug("%%%u has %zu bytes", wp->id, size);
  input_parse(wp);
  wp->pipe_off = EVBUFFER_LENGTH(evb);
}

static void window_pane_error_callback(struct bufferevent *bufev, short what, void *data)
{
  struct window_pane *wp = data;
  log_debug("%%%u error", wp->id);
  wp->flags |= 0x100;
  if (window_pane_destroy_ready(wp))
  {
    server_destroy_pane(wp, 1);
  }
}

void window_pane_resize(struct window_pane *wp, u_int sx, u_int sy)
{
  if ((sx == wp->sx) && (sy == wp->sy))
  {
    return;
  }
  wp->sx = sx;
  wp->sy = sy;
  screen_resize(&wp->base, sx, sy, wp->saved_grid == 0);
  if (wp->mode != 0)
  {
    wp->mode->resize(wp, sx, sy);
  }
  wp->flags |= 0x8;
}

void window_pane_alternate_on(struct window_pane *wp, struct grid_cell *gc, int cursor)
{
  struct screen *s = &wp->base;
  u_int sx;
  u_int sy;
  if (wp->saved_grid != 0)
  {
    return;
  }
  if (!options_get_number(wp->window->options, "alternate-screen"))
  {
    return;
  }
  sx = s->grid->sx;
  sy = s->grid->sy;
  wp->saved_grid = grid_create(sx, sy, 0);
  grid_duplicate_lines(wp->saved_grid, 0, s->grid, s->grid->hsize, sy);
  if (cursor)
  {
    wp->saved_cx = s->cx;
    wp->saved_cy = s->cy;
  }
  memcpy(&wp->saved_cell, gc, sizeof(wp->saved_cell));
  grid_view_clear(s->grid, 0, 0, sx, sy, 8);
  wp->base.grid->flags &= ~0x1;
  wp->flags |= 0x1;
}

void window_pane_alternate_off(struct window_pane *wp, struct grid_cell *gc, int cursor)
{
  struct screen *s = &wp->base;
  u_int sx;
  u_int sy;
  if (wp->saved_grid == 0)
  {
    return;
  }
  if (!options_get_number(wp->window->options, "alternate-screen"))
  {
    return;
  }
  sx = s->grid->sx;
  sy = s->grid->sy;
  if (sy > wp->saved_grid->sy)
  {
    screen_resize(s, sx, wp->saved_grid->sy, 1);
  }
  grid_duplicate_lines(s->grid, s->grid->hsize, wp->saved_grid, 0, sy);
  if (cursor)
  {
    s->cx = wp->saved_cx;
  }
  if (s->cx > (s->grid->sx - 1))
  {
    s->cx = s->grid->sx - 1;
  }
  if (cursor)
  {
    s->cy = wp->saved_cy;
  }
  if (s->cy > (s->grid->sy - 1))
  {
    s->cy = s->grid->sy - 1;
  }
  memcpy(gc, &wp->saved_cell, sizeof(*gc));
  wp->base.grid->flags |= 0x1;
  if ((sy > wp->saved_grid->sy) || (sx != wp->saved_grid->sx))
  {
    screen_resize(s, sx, sy, 1);
  }
  grid_destroy(wp->saved_grid);
  wp->saved_grid = 0;
  wp->flags |= 0x1;
}

void window_pane_set_palette(struct window_pane *wp, u_int n, int colour)
{
  if (n > 0xff)
  {
    return;
  }
  if (wp->palette == 0)
  {
    wp->palette = xcalloc(0x100, sizeof(*wp->palette));
  }
  wp->palette[n] = colour;
  wp->flags |= 0x1;
}

void window_pane_unset_palette(struct window_pane *wp, u_int n)
{
  if ((n > 0xff) || (wp->palette == 0))
  {
    return;
  }
  wp->palette[n] = 0;
  wp->flags |= 0x1;
}

void window_pane_reset_palette(struct window_pane *wp)
{
  if (wp->palette == 0)
  {
    return;
  }
  free(wp->palette);
  wp->palette = 0;
  wp->flags |= 0x1;
}

int window_pane_get_palette(const struct window_pane *wp, int c)
{
  int new;
  if ((wp == 0) || (wp->palette == 0))
  {
    return -1;
  }
  new = -1;
  if (c < 8)
  {
    new = wp->palette[c];
  }
  else
    if ((c >= 90) && (c <= 97))
  {
    new = wp->palette[(8 + c) - 90];
  }
  else
    if (c & 0x01000000)
  {
    new = wp->palette[c & (~0x01000000)];
  }
  if (new == 0)
  {
    return -1;
  }
  return new;
}

static void window_pane_mode_timer(int fd, short events, void *arg)
{
  struct window_pane *wp = arg;
  struct timeval tv = {.tv_sec = 10};
  int n = 0;
  evtimer_del(&wp->modetimer);
  evtimer_add(&wp->modetimer, &tv);
  log_debug("%%%u in mode: last=%ld", wp->id, (long) wp->modelast);
  if (wp->modelast < (time(0) - 180))
  {
    if ((ioctl(wp->fd, FIONREAD, &n) == (-1)) || (n > 0))
    {
      window_pane_reset_mode(wp);
    }
  }
}

int window_pane_set_mode(struct window_pane *wp, const struct window_mode *mode, struct cmd_find_state *fs, struct args *args)
{
  struct screen *s;
  unsigned int s_idx = 0;
  struct timeval tv = {.tv_sec = 10};
  if (wp->mode != 0)
  {
    return 1;
  }
  wp->mode = mode;
  wp->modelast = time(0);
  evtimer_set(&wp->modetimer, window_pane_mode_timer, wp);
  evtimer_add(&wp->modetimer, &tv);
  if ((s_idx = wp->mode->init(wp, fs, args)) != 0)
  {
    wp->screen = &s[s_idx];
  }
  wp->flags |= 0x1 | 0x80;
  server_status_window(wp->window);
  notify_pane("pane-mode-changed", wp);
  return 0;
}

void window_pane_reset_mode(struct window_pane *wp)
{
  if (wp->mode == 0)
  {
    return;
  }
  evtimer_del(&wp->modetimer);
  wp->mode->free(wp);
  wp->mode = 0;
  wp->modeprefix = 1;
  wp->screen = &wp->base;
  wp->flags |= 0x1 | 0x80;
  server_status_window(wp->window);
  notify_pane("pane-mode-changed", wp);
}

void window_pane_key(struct window_pane *wp, struct client *c, struct session *s, key_code key, struct mouse_event *m)
{
  struct window_pane *wp2;
  unsigned int wp2_idx = 0;
  if ((((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) >= KEYC_MOUSE) && ((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) < KEYC_BSPACE)) && (m == 0))
  {
    return;
  }
  if (wp->mode != 0)
  {
    wp->modelast = time(0);
    if (wp->mode->key != 0)
    {
      wp->mode->key(wp, c, s, key & (~0x1000000000000ULL), m);
    }
    return;
  }
  if ((wp->fd == (-1)) || (wp->flags & 0x40))
  {
    return;
  }
  input_key(wp, key, m);
  if (((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) >= KEYC_MOUSE) && ((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) < KEYC_BSPACE))
  {
    return;
  }
  if (options_get_number(wp->window->options, "synchronize-panes"))
  {
    for (wp2_idx = (&wp->window->panes)->tqh_first; (&wp2[wp2_idx]) != 0; wp2_idx = wp2_idx->entry.tqe_next)
    {
      if (((&wp2[wp2_idx]) == wp) || (wp2->mode != 0))
      {
        continue;
      }
      if ((wp2->fd == (-1)) || (wp2->flags & 0x40))
      {
        continue;
      }
      if (window_pane_visible(wp2))
      {
        input_key(wp2, key, 0);
      }
    }

  }
}

int window_pane_visible(struct window_pane *wp)
{
  struct window *w = wp->window;
  if (wp->layout_cell == 0)
  {
    return 0;
  }
  if ((wp->xoff >= w->sx) || (wp->yoff >= w->sy))
  {
    return 0;
  }
  if (((wp->xoff + wp->sx) > w->sx) || ((wp->yoff + wp->sy) > w->sy))
  {
    return 0;
  }
  return 1;
}

u_int window_pane_search(struct window_pane *wp, const char *searchstr)
{
  struct screen *s = &wp->base;
  char *newsearchstr;
  char *line;
  unsigned int line_idx = 0;
  u_int i;
  xasprintf(&newsearchstr, "*%s*", searchstr);
  for (i = 0; i < s->grid->sy; i += 1)
  {
    line_idx = grid_view_string_cells(s->grid, 0, i, s->grid->sx);
    if (fnmatch(newsearchstr, line, 0) == 0)
    {
      free(line);
      break;
    }
    free(line);
  }

  free(newsearchstr);
  if (i == s->grid->sy)
  {
    return 0;
  }
  return i + 1;
}

static struct window_pane *window_pane_choose_best(struct window_pane **list, u_int size)
{
  struct window_pane *next;
  unsigned int next_idx = 0;
  struct window_pane *best;
  unsigned int best_idx = 0;
  u_int i;
  if (size == 0)
  {
    return 0;
  }
  best_idx = list[0];
  for (i = 1; i < size; i += 1)
  {
    next_idx = list[i];
    if (next->active_point > best->active_point)
    {
      best_idx = &next[next_idx];
    }
  }

  return best;
}

struct window_pane *window_pane_find_up(struct window_pane *wp)
{
  struct window_pane *next;
  unsigned int next_idx = 0;
  struct window_pane *best;
  unsigned int best_idx = 0;
  struct window_pane **list;
  unsigned int list_idx = 0;
  u_int edge;
  u_int left;
  u_int right;
  u_int end;
  u_int size;
  int status;
  int found;
  if ((wp == 0) || (!window_pane_visible(wp)))
  {
    return 0;
  }
  status = options_get_number(wp->window->options, "pane-border-status");
  list_idx = 0;
  size = 0;
  edge = wp->yoff;
  if (edge == ((status == 1) ? (1) : (0)))
  {
    edge = (wp->window->sy + 1) - ((status == 2) ? (1) : (0));
  }
  left = wp->xoff;
  right = wp->xoff + wp->sx;
  for (next_idx = (&wp->window->panes)->tqh_first; (&next[next_idx]) != 0; next_idx = next_idx->entry.tqe_next)
  {
    helper_window_pane_find_up_1(&list_idx, &end, &size, &found, wp, next, next_idx, list, edge, left, right);
  }

  best_idx = window_pane_choose_best(list, size);
  free(list);
  return best;
}

struct window_pane *window_pane_find_down(struct window_pane *wp)
{
  struct window_pane *next;
  unsigned int next_idx = 0;
  struct window_pane *best;
  unsigned int best_idx = 0;
  struct window_pane **list;
  unsigned int list_idx = 0;
  u_int edge;
  u_int left;
  u_int right;
  u_int end;
  u_int size;
  int status;
  int found;
  if ((wp == 0) || (!window_pane_visible(wp)))
  {
    return 0;
  }
  status = options_get_number(wp->window->options, "pane-border-status");
  list_idx = 0;
  size = 0;
  edge = (wp->yoff + wp->sy) + 1;
  if (edge >= (wp->window->sy - ((status == 2) ? (1) : (0))))
  {
    edge = (status == 1) ? (1) : (0);
  }
  left = wp->xoff;
  right = wp->xoff + wp->sx;
  for (next_idx = (&wp->window->panes)->tqh_first; (&next[next_idx]) != 0; next_idx = next_idx->entry.tqe_next)
  {
    helper_window_pane_find_down_1(&list_idx, &end, &size, &found, wp, next, next_idx, list, edge, left, right);
  }

  best_idx = window_pane_choose_best(list, size);
  free(list);
  return best;
}

struct window_pane *window_pane_find_left(struct window_pane *wp)
{
  struct window_pane *next;
  unsigned int next_idx = 0;
  struct window_pane *best;
  unsigned int best_idx = 0;
  struct window_pane **list;
  unsigned int list_idx = 0;
  u_int edge;
  u_int top;
  u_int bottom;
  u_int end;
  u_int size;
  int found;
  if ((wp == 0) || (!window_pane_visible(wp)))
  {
    return 0;
  }
  list_idx = 0;
  size = 0;
  edge = wp->xoff;
  if (edge == 0)
  {
    edge = wp->window->sx + 1;
  }
  top = wp->yoff;
  bottom = wp->yoff + wp->sy;
  for (next_idx = (&wp->window->panes)->tqh_first; (&next[next_idx]) != 0; next_idx = next_idx->entry.tqe_next)
  {
    helper_window_pane_find_left_1(&list_idx, &end, &size, &found, wp, next, next_idx, list, edge, top, bottom);
  }

  best_idx = window_pane_choose_best(list, size);
  free(list);
  return best;
}

struct window_pane *window_pane_find_right(struct window_pane *wp)
{
  struct window_pane *next;
  unsigned int next_idx = 0;
  struct window_pane *best;
  unsigned int best_idx = 0;
  struct window_pane **list;
  unsigned int list_idx = 0;
  u_int edge;
  u_int top;
  u_int bottom;
  u_int end;
  u_int size;
  int found;
  if ((wp == 0) || (!window_pane_visible(wp)))
  {
    return 0;
  }
  list_idx = 0;
  size = 0;
  edge = (wp->xoff + wp->sx) + 1;
  if (edge >= wp->window->sx)
  {
    edge = 0;
  }
  top = wp->yoff;
  bottom = wp->yoff + wp->sy;
  for (next_idx = (&wp->window->panes)->tqh_first; (&next[next_idx]) != 0; next_idx = next_idx->entry.tqe_next)
  {
    helper_window_pane_find_right_1(&list_idx, &end, &size, &found, wp, next, next_idx, list, edge, top, bottom);
  }

  best_idx = window_pane_choose_best(list, size);
  free(list);
  return best;
}

void winlink_clear_flags(struct winlink *wl)
{
  struct winlink *loop;
  unsigned int loop_idx = 0;
  wl->window->flags &= ~((0x1 | 0x2) | 0x8);
  for (loop_idx = (&wl->window->winlinks)->tqh_first; (&loop[loop_idx]) != 0; loop_idx = loop_idx->wentry.tqe_next)
  {
    if ((loop->flags & ((0x1 | 0x2) | 0x4)) != 0)
    {
      loop->flags &= ~((0x1 | 0x2) | 0x4);
      server_status_session(loop->session);
    }
  }

}

int winlink_shuffle_up(struct session *s, struct winlink *wl)
{
  unsigned int wl_idx = 0;
  int idx;
  int last;
  idx = wl->idx + 1;
  for (last = idx; last < 2147483647; last += 1)
  {
    if (winlink_find_by_index(&s->windows, last) == 0)
    {
      break;
    }
  }

  if (last == 2147483647)
  {
    return -1;
  }
  for (; last > idx; last -= 1)
  {
    wl_idx = winlink_find_by_index(&s->windows, last - 1);
    server_link_window(s, wl, s, last, 0, 0, 0);
    server_unlink_window(s, wl);
  }

  return idx;
}

void helper_windows_RB_INSERT_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const gparent_idx_ref, unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const elm, struct window * const parent, struct window * const gparent, struct window * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int gparent_idx = *gparent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  gparent_idx = parent->entry.rbe_parent;
  if ((&parent[parent_idx]) == gparent->entry.rbe_left)
  {
    helper_helper_windows_RB_INSERT_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  else
  {
    helper_helper_windows_RB_INSERT_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *gparent_idx_ref = gparent_idx;
  *tmp_idx_ref = tmp_idx;
}

void helper_windows_RB_REMOVE_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const elm, struct window * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if (parent->entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_windows_RB_REMOVE_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  else
  {
    helper_helper_windows_RB_REMOVE_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}

void helper_windows_RB_REMOVE_1(unsigned int * const elm_idx_ref, unsigned int * const child_idx_ref, unsigned int * const parent_idx_ref, int * const color_ref, struct windows * const head, struct window * const elm, struct window * const child, struct window * const parent, struct window * const old)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int child_idx = *child_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  int color = *color_ref;
  struct window *left;
  unsigned int left_idx = 0;
  elm_idx = elm_idx->entry.rbe_right;
  while (left_idx = elm->entry.rbe_left)
  {
    elm_idx = &left[left_idx];
  }

  child_idx = elm->entry.rbe_right;
  parent_idx = elm->entry.rbe_parent;
  color = elm->entry.rbe_color;
  if (child)
  {
    child->entry.rbe_parent = &parent[parent_idx];
  }
  if (parent)
  {
    if (parent->entry.rbe_left == (&elm[elm_idx]))
    {
      parent->entry.rbe_left = &child[child_idx];
    }
    else
      parent->entry.rbe_right = &child[child_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &child[child_idx];
  if (elm->entry.rbe_parent == old)
  {
    parent_idx = &elm[elm_idx];
  }
  elm->entry = old->entry;
  if (old->entry.rbe_parent)
  {
    if (old->entry.rbe_parent->entry.rbe_left == old)
    {
      old->entry.rbe_parent->entry.rbe_left = &elm[elm_idx];
    }
    else
      old->entry.rbe_parent->entry.rbe_right = &elm[elm_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &elm[elm_idx];
  old->entry.rbe_left->entry.rbe_parent = &elm[elm_idx];
  if (old->entry.rbe_right)
  {
    old->entry.rbe_right->entry.rbe_parent = &elm[elm_idx];
  }
  if (parent)
  {
    left_idx = &parent[parent_idx];
    do
    {
      do
      {
      }
      while (0);
    }
    while (left_idx = left_idx->entry.rbe_parent);
  }
  goto color;
  *elm_idx_ref = elm_idx;
  *child_idx_ref = child_idx;
  *parent_idx_ref = parent_idx;
  *color_ref = color;
}

void helper_winlinks_RB_INSERT_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const gparent_idx_ref, unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const elm, struct winlink * const parent, struct winlink * const gparent, struct winlink * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int gparent_idx = *gparent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  gparent_idx = parent->entry.rbe_parent;
  if ((&parent[parent_idx]) == gparent->entry.rbe_left)
  {
    helper_helper_winlinks_RB_INSERT_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  else
  {
    helper_helper_winlinks_RB_INSERT_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *gparent_idx_ref = gparent_idx;
  *tmp_idx_ref = tmp_idx;
}

void helper_winlinks_RB_REMOVE_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const elm, struct winlink * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if (parent->entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_winlinks_RB_REMOVE_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  else
  {
    helper_helper_winlinks_RB_REMOVE_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}

void helper_winlinks_RB_REMOVE_1(unsigned int * const elm_idx_ref, unsigned int * const child_idx_ref, unsigned int * const parent_idx_ref, int * const color_ref, struct winlinks * const head, struct winlink * const elm, struct winlink * const child, struct winlink * const parent, struct winlink * const old)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int child_idx = *child_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  int color = *color_ref;
  struct winlink *left;
  unsigned int left_idx = 0;
  elm_idx = elm_idx->entry.rbe_right;
  while (left_idx = elm->entry.rbe_left)
  {
    elm_idx = &left[left_idx];
  }

  child_idx = elm->entry.rbe_right;
  parent_idx = elm->entry.rbe_parent;
  color = elm->entry.rbe_color;
  if (child)
  {
    child->entry.rbe_parent = &parent[parent_idx];
  }
  if (parent)
  {
    if (parent->entry.rbe_left == (&elm[elm_idx]))
    {
      parent->entry.rbe_left = &child[child_idx];
    }
    else
      parent->entry.rbe_right = &child[child_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &child[child_idx];
  if (elm->entry.rbe_parent == old)
  {
    parent_idx = &elm[elm_idx];
  }
  elm->entry = old->entry;
  if (old->entry.rbe_parent)
  {
    if (old->entry.rbe_parent->entry.rbe_left == old)
    {
      old->entry.rbe_parent->entry.rbe_left = &elm[elm_idx];
    }
    else
      old->entry.rbe_parent->entry.rbe_right = &elm[elm_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &elm[elm_idx];
  old->entry.rbe_left->entry.rbe_parent = &elm[elm_idx];
  if (old->entry.rbe_right)
  {
    old->entry.rbe_right->entry.rbe_parent = &elm[elm_idx];
  }
  if (parent)
  {
    left_idx = &parent[parent_idx];
    do
    {
      do
      {
      }
      while (0);
    }
    while (left_idx = left_idx->entry.rbe_parent);
  }
  goto color;
  *elm_idx_ref = elm_idx;
  *child_idx_ref = child_idx;
  *parent_idx_ref = parent_idx;
  *color_ref = color;
}

void helper_window_pane_tree_RB_INSERT_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const gparent_idx_ref, unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const elm, struct window_pane * const parent, struct window_pane * const gparent, struct window_pane * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int gparent_idx = *gparent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  gparent_idx = parent->tree_entry.rbe_parent;
  if ((&parent[parent_idx]) == gparent->tree_entry.rbe_left)
  {
    helper_helper_window_pane_tree_RB_INSERT_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  else
  {
    helper_helper_window_pane_tree_RB_INSERT_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *gparent_idx_ref = gparent_idx;
  *tmp_idx_ref = tmp_idx;
}

void helper_window_pane_tree_RB_REMOVE_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const elm, struct window_pane * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if (parent->tree_entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  else
  {
    helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}

void helper_window_pane_tree_RB_REMOVE_1(unsigned int * const elm_idx_ref, unsigned int * const child_idx_ref, unsigned int * const parent_idx_ref, int * const color_ref, struct window_pane_tree * const head, struct window_pane * const elm, struct window_pane * const child, struct window_pane * const parent, struct window_pane * const old)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int child_idx = *child_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  int color = *color_ref;
  struct window_pane *left;
  unsigned int left_idx = 0;
  elm_idx = elm_idx->tree_entry.rbe_right;
  while (left_idx = elm->tree_entry.rbe_left)
  {
    elm_idx = &left[left_idx];
  }

  child_idx = elm->tree_entry.rbe_right;
  parent_idx = elm->tree_entry.rbe_parent;
  color = elm->tree_entry.rbe_color;
  if (child)
  {
    child->tree_entry.rbe_parent = &parent[parent_idx];
  }
  if (parent)
  {
    if (parent->tree_entry.rbe_left == (&elm[elm_idx]))
    {
      parent->tree_entry.rbe_left = &child[child_idx];
    }
    else
      parent->tree_entry.rbe_right = &child[child_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &child[child_idx];
  if (elm->tree_entry.rbe_parent == old)
  {
    parent_idx = &elm[elm_idx];
  }
  elm->tree_entry = old->tree_entry;
  if (old->tree_entry.rbe_parent)
  {
    if (old->tree_entry.rbe_parent->tree_entry.rbe_left == old)
    {
      old->tree_entry.rbe_parent->tree_entry.rbe_left = &elm[elm_idx];
    }
    else
      old->tree_entry.rbe_parent->tree_entry.rbe_right = &elm[elm_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &elm[elm_idx];
  old->tree_entry.rbe_left->tree_entry.rbe_parent = &elm[elm_idx];
  if (old->tree_entry.rbe_right)
  {
    old->tree_entry.rbe_right->tree_entry.rbe_parent = &elm[elm_idx];
  }
  if (parent)
  {
    left_idx = &parent[parent_idx];
    do
    {
      do
      {
      }
      while (0);
    }
    while (left_idx = left_idx->tree_entry.rbe_parent);
  }
  goto color;
  *elm_idx_ref = elm_idx;
  *child_idx_ref = child_idx;
  *parent_idx_ref = parent_idx;
  *color_ref = color;
}

void helper_window_add_pane_1(struct window * const w, struct window_pane * const other, int full_size, unsigned int other_idx, struct window_pane * const wp, unsigned int wp_idx)
{
  log_debug("%s: @%u before %%%u", __func__, w->id, wp->id);
  if (full_size)
  {
    do
    {
      if ((wp->entry.tqe_next = (&w->panes)->tqh_first) != 0)
      {
        (&w->panes)->tqh_first->entry.tqe_prev = &wp->entry.tqe_next;
      }
      else
        (&w->panes)->tqh_last = &wp->entry.tqe_next;
      (&w->panes)->tqh_first = &wp[wp_idx];
      wp->entry.tqe_prev = &(&w->panes)->tqh_first;
    }
    while (0);
  }
  else
    do
  {
    wp->entry.tqe_prev = other->entry.tqe_prev;
    wp->entry.tqe_next = &other[other_idx];
    *other->entry.tqe_prev = &wp[wp_idx];
    other->entry.tqe_prev = &wp->entry.tqe_next;
  }
  while (0);
}

void helper_window_add_pane_2(struct window * const w, struct window_pane * const other, int full_size, struct window_pane * const wp, unsigned int wp_idx)
{
  log_debug("%s: @%u after %%%u", __func__, w->id, wp->id);
  if (full_size)
  {
    do
    {
      wp->entry.tqe_next = 0;
      wp->entry.tqe_prev = (&w->panes)->tqh_last;
      *(&w->panes)->tqh_last = &wp[wp_idx];
      (&w->panes)->tqh_last = &wp->entry.tqe_next;
    }
    while (0);
  }
  else
    do
  {
    if ((wp->entry.tqe_next = other->entry.tqe_next) != 0)
    {
      wp->entry.tqe_next->entry.tqe_prev = &wp->entry.tqe_next;
    }
    else
      (&w->panes)->tqh_last = &wp->entry.tqe_next;
    other->entry.tqe_next = &wp[wp_idx];
    wp->entry.tqe_prev = &other->entry.tqe_next;
  }
  while (0);
}

void helper_window_pane_spawn_1(unsigned int * const cwd_idx_ref, unsigned int * const argvp_idx_ref, unsigned int * const ptr_idx_ref, unsigned int * const first_idx_ref, unsigned int * const home_idx_ref, struct termios * const tio2_ref, struct window_pane * const wp, const char * const path, const char * const cwd, struct environ * const env, struct termios * const tio, char * const argv0, char ** const argvp, const char * const ptr, const char * const first, const char * const home, sigset_t oldset)
{
  unsigned int cwd_idx = *cwd_idx_ref;
  unsigned int argvp_idx = *argvp_idx_ref;
  unsigned int ptr_idx = *ptr_idx_ref;
  unsigned int first_idx = *first_idx_ref;
  unsigned int home_idx = *home_idx_ref;
  struct termios tio2 = *tio2_ref;
  proc_clear_signals(server_proc, 1);
  sigprocmask(SIG_SETMASK, &oldset, 0);
  cwd_idx = 0;
  if (chdir(wp->cwd) == 0)
  {
    cwd_idx = wp->cwd_idx;
  }
  else
    if (((home_idx = find_home()) != 0) && (chdir(home) == 0))
  {
    cwd_idx = &home[home_idx];
  }
  else
    chdir("/");
  if (tcgetattr(STDIN_FILENO, &tio2) != 0)
  {
    fatal("tcgetattr failed");
  }
  if (tio != 0)
  {
    memcpy(tio2.c_cc, tio->c_cc, sizeof(tio2.c_cc));
  }
  tio2.c_cc[VERASE] = '\177';
  if (tcsetattr(STDIN_FILENO, TCSANOW, &tio2) != 0)
  {
    fatal("tcgetattr failed");
  }
  log_close();
  closefrom(STDERR_FILENO + 1);
  if (path != 0)
  {
    environ_set(env, "PATH", "%s", path);
  }
  if ((&cwd[cwd_idx]) != 0)
  {
    environ_set(env, "PWD", "%s", cwd);
  }
  environ_set(env, "TMUX_PANE", "%%%u", wp->id);
  environ_push(env);
  setenv("SHELL", wp->shell, 1);
  ptr_idx = strrchr(wp->shell, '/');
  if (wp->argc > 0)
  {
    if (wp->argc != 1)
    {
      argvp_idx = cmd_copy_argv(wp->argc, wp->argv);
      execvp(argvp[0 + argvp_idx], argvp);
      fatal("execvp failed");
    }
    first_idx = wp->argv[0];
    if (((&ptr[ptr_idx]) != 0) && ((*((&ptr[ptr_idx]) + 1)) != '\0'))
    {
      xasprintf(&argv0, "%s", (&ptr[ptr_idx]) + 1);
    }
    else
      xasprintf(&argv0, "%s", wp->shell);
    execl(wp->shell, argv0, "-c", first, (char *) 0);
    fatal("execl failed");
  }
  if (((&ptr[ptr_idx]) != 0) && ((*((&ptr[ptr_idx]) + 1)) != '\0'))
  {
    xasprintf(&argv0, "-%s", (&ptr[ptr_idx]) + 1);
  }
  else
    xasprintf(&argv0, "-%s", wp->shell);
  execl(wp->shell, argv0, (char *) 0);
  fatal("execl failed");
  *cwd_idx_ref = cwd_idx;
  *argvp_idx_ref = argvp_idx;
  *ptr_idx_ref = ptr_idx;
  *first_idx_ref = first_idx;
  *home_idx_ref = home_idx;
  *tio2_ref = tio2;
}

void helper_window_pane_find_up_1(unsigned int * const list_idx_ref, u_int * const end_ref, u_int * const size_ref, int * const found_ref, struct window_pane * const wp, struct window_pane * const next, unsigned int next_idx, struct window_pane ** const list, u_int edge, u_int left, u_int right)
{
  unsigned int list_idx = *list_idx_ref;
  u_int end = *end_ref;
  u_int size = *size_ref;
  int found = *found_ref;
  if (((&next[next_idx]) == wp) || (!window_pane_visible(next)))
  {
    continue;
  }
  if (((next->yoff + next->sy) + 1) != edge)
  {
    continue;
  }
  end = (next->xoff + next->sx) - 1;
  found = 0;
  if ((next->xoff < left) && (end > right))
  {
    found = 1;
  }
  else
    if ((next->xoff >= left) && (next->xoff <= right))
  {
    found = 1;
  }
  else
    if ((end >= left) && (end <= right))
  {
    found = 1;
  }
  if (!found)
  {
    continue;
  }
  list_idx = xreallocarray(list_idx, size + 1, sizeof(*list_idx));
  list[size + list_idx] = &next[next_idx];
  size += 1;
  *list_idx_ref = list_idx;
  *end_ref = end;
  *size_ref = size;
  *found_ref = found;
}

void helper_window_pane_find_down_1(unsigned int * const list_idx_ref, u_int * const end_ref, u_int * const size_ref, int * const found_ref, struct window_pane * const wp, struct window_pane * const next, unsigned int next_idx, struct window_pane ** const list, u_int edge, u_int left, u_int right)
{
  unsigned int list_idx = *list_idx_ref;
  u_int end = *end_ref;
  u_int size = *size_ref;
  int found = *found_ref;
  if (((&next[next_idx]) == wp) || (!window_pane_visible(next)))
  {
    continue;
  }
  if (next->yoff != edge)
  {
    continue;
  }
  end = (next->xoff + next->sx) - 1;
  found = 0;
  if ((next->xoff < left) && (end > right))
  {
    found = 1;
  }
  else
    if ((next->xoff >= left) && (next->xoff <= right))
  {
    found = 1;
  }
  else
    if ((end >= left) && (end <= right))
  {
    found = 1;
  }
  if (!found)
  {
    continue;
  }
  list_idx = xreallocarray(list_idx, size + 1, sizeof(*list_idx));
  list[size + list_idx] = &next[next_idx];
  size += 1;
  *list_idx_ref = list_idx;
  *end_ref = end;
  *size_ref = size;
  *found_ref = found;
}

void helper_window_pane_find_left_1(unsigned int * const list_idx_ref, u_int * const end_ref, u_int * const size_ref, int * const found_ref, struct window_pane * const wp, struct window_pane * const next, unsigned int next_idx, struct window_pane ** const list, u_int edge, u_int top, u_int bottom)
{
  unsigned int list_idx = *list_idx_ref;
  u_int end = *end_ref;
  u_int size = *size_ref;
  int found = *found_ref;
  if (((&next[next_idx]) == wp) || (!window_pane_visible(next)))
  {
    continue;
  }
  if (((next->xoff + next->sx) + 1) != edge)
  {
    continue;
  }
  end = (next->yoff + next->sy) - 1;
  found = 0;
  if ((next->yoff < top) && (end > bottom))
  {
    found = 1;
  }
  else
    if ((next->yoff >= top) && (next->yoff <= bottom))
  {
    found = 1;
  }
  else
    if ((end >= top) && (end <= bottom))
  {
    found = 1;
  }
  if (!found)
  {
    continue;
  }
  list_idx = xreallocarray(list_idx, size + 1, sizeof(*list_idx));
  list[size + list_idx] = &next[next_idx];
  size += 1;
  *list_idx_ref = list_idx;
  *end_ref = end;
  *size_ref = size;
  *found_ref = found;
}

void helper_window_pane_find_right_1(unsigned int * const list_idx_ref, u_int * const end_ref, u_int * const size_ref, int * const found_ref, struct window_pane * const wp, struct window_pane * const next, unsigned int next_idx, struct window_pane ** const list, u_int edge, u_int top, u_int bottom)
{
  unsigned int list_idx = *list_idx_ref;
  u_int end = *end_ref;
  u_int size = *size_ref;
  int found = *found_ref;
  if (((&next[next_idx]) == wp) || (!window_pane_visible(next)))
  {
    continue;
  }
  if (next->xoff != edge)
  {
    continue;
  }
  end = (next->yoff + next->sy) - 1;
  found = 0;
  if ((next->yoff < top) && (end > bottom))
  {
    found = 1;
  }
  else
    if ((next->yoff >= top) && (next->yoff <= bottom))
  {
    found = 1;
  }
  else
    if ((end >= top) && (end <= bottom))
  {
    found = 1;
  }
  if (!found)
  {
    continue;
  }
  list_idx = xreallocarray(list_idx, size + 1, sizeof(*list_idx));
  list[size + list_idx] = &next[next_idx];
  size += 1;
  *list_idx_ref = list_idx;
  *end_ref = end;
  *size_ref = size;
  *found_ref = found;
}

void helper_helper_windows_RB_INSERT_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const elm, struct window * const parent, struct window * const gparent, struct window * const tmp, unsigned int gparent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->entry.rbe_right;
  if ((&tmp[tmp_idx]) && (tmp->entry.rbe_color == 1))
  {
    tmp->entry.rbe_color = 0;
    do
    {
      parent->entry.rbe_color = 0;
      gparent->entry.rbe_color = 1;
    }
    while (0);
    elm_idx = &gparent[gparent_idx];
    continue;
  }
  if (parent->entry.rbe_right == (&elm[elm_idx]))
  {
    helper_helper_helper_windows_RB_INSERT_COLOR_1_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_windows_RB_INSERT_COLOR_1_1_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_windows_RB_INSERT_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const elm, struct window * const parent, struct window * const gparent, struct window * const tmp, unsigned int gparent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->entry.rbe_left;
  if ((&tmp[tmp_idx]) && (tmp->entry.rbe_color == 1))
  {
    tmp->entry.rbe_color = 0;
    do
    {
      parent->entry.rbe_color = 0;
      gparent->entry.rbe_color = 1;
    }
    while (0);
    elm_idx = &gparent[gparent_idx];
    continue;
  }
  if (parent->entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_helper_windows_RB_INSERT_COLOR_1_2_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_windows_RB_INSERT_COLOR_1_2_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_windows_RB_REMOVE_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const elm, struct window * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_right;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_windows_RB_REMOVE_COLOR_1_1_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_windows_RB_REMOVE_COLOR_1_1_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_windows_RB_REMOVE_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const elm, struct window * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_left;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_windows_RB_REMOVE_COLOR_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_windows_RB_REMOVE_COLOR_1_2_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_winlinks_RB_INSERT_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const elm, struct winlink * const parent, struct winlink * const gparent, struct winlink * const tmp, unsigned int gparent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->entry.rbe_right;
  if ((&tmp[tmp_idx]) && (tmp->entry.rbe_color == 1))
  {
    tmp->entry.rbe_color = 0;
    do
    {
      parent->entry.rbe_color = 0;
      gparent->entry.rbe_color = 1;
    }
    while (0);
    elm_idx = &gparent[gparent_idx];
    continue;
  }
  if (parent->entry.rbe_right == (&elm[elm_idx]))
  {
    helper_helper_helper_winlinks_RB_INSERT_COLOR_1_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_winlinks_RB_INSERT_COLOR_1_1_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_winlinks_RB_INSERT_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const elm, struct winlink * const parent, struct winlink * const gparent, struct winlink * const tmp, unsigned int gparent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->entry.rbe_left;
  if ((&tmp[tmp_idx]) && (tmp->entry.rbe_color == 1))
  {
    tmp->entry.rbe_color = 0;
    do
    {
      parent->entry.rbe_color = 0;
      gparent->entry.rbe_color = 1;
    }
    while (0);
    elm_idx = &gparent[gparent_idx];
    continue;
  }
  if (parent->entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_helper_winlinks_RB_INSERT_COLOR_1_2_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_winlinks_RB_INSERT_COLOR_1_2_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_winlinks_RB_REMOVE_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const elm, struct winlink * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_right;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_1_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_1_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_winlinks_RB_REMOVE_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const elm, struct winlink * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_left;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_2_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_window_pane_tree_RB_INSERT_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const elm, struct window_pane * const parent, struct window_pane * const gparent, struct window_pane * const tmp, unsigned int gparent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->tree_entry.rbe_right;
  if ((&tmp[tmp_idx]) && (tmp->tree_entry.rbe_color == 1))
  {
    tmp->tree_entry.rbe_color = 0;
    do
    {
      parent->tree_entry.rbe_color = 0;
      gparent->tree_entry.rbe_color = 1;
    }
    while (0);
    elm_idx = &gparent[gparent_idx];
    continue;
  }
  if (parent->tree_entry.rbe_right == (&elm[elm_idx]))
  {
    helper_helper_helper_window_pane_tree_RB_INSERT_COLOR_1_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->tree_entry.rbe_color = 0;
    gparent->tree_entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_window_pane_tree_RB_INSERT_COLOR_1_1_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_window_pane_tree_RB_INSERT_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const elm, struct window_pane * const parent, struct window_pane * const gparent, struct window_pane * const tmp, unsigned int gparent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->tree_entry.rbe_left;
  if ((&tmp[tmp_idx]) && (tmp->tree_entry.rbe_color == 1))
  {
    tmp->tree_entry.rbe_color = 0;
    do
    {
      parent->tree_entry.rbe_color = 0;
      gparent->tree_entry.rbe_color = 1;
    }
    while (0);
    elm_idx = &gparent[gparent_idx];
    continue;
  }
  if (parent->tree_entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_helper_window_pane_tree_RB_INSERT_COLOR_1_2_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->tree_entry.rbe_color = 0;
    gparent->tree_entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_window_pane_tree_RB_INSERT_COLOR_1_2_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const elm, struct window_pane * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->tree_entry.rbe_right;
  if (tmp->tree_entry.rbe_color == 1)
  {
    helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_1_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->tree_entry.rbe_left == 0) || (tmp->tree_entry.rbe_left->tree_entry.rbe_color == 0)) && ((tmp->tree_entry.rbe_right == 0) || (tmp->tree_entry.rbe_right->tree_entry.rbe_color == 0)))
  {
    tmp->tree_entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->tree_entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_1_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const elm, struct window_pane * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->tree_entry.rbe_left;
  if (tmp->tree_entry.rbe_color == 1)
  {
    helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->tree_entry.rbe_left == 0) || (tmp->tree_entry.rbe_left->tree_entry.rbe_color == 0)) && ((tmp->tree_entry.rbe_right == 0) || (tmp->tree_entry.rbe_right->tree_entry.rbe_color == 0)))
  {
    tmp->tree_entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->tree_entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_2_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_windows_RB_INSERT_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const gparent, struct window * const tmp, unsigned int gparent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->entry.rbe_left;
  if (gparent->entry.rbe_left = tmp->entry.rbe_right)
  {
    tmp->entry.rbe_right->entry.rbe_parent = &gparent[gparent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent = gparent->entry.rbe_parent)
  {
    if ((&gparent[gparent_idx]) == gparent->entry.rbe_parent->entry.rbe_left)
    {
      gparent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
    }
    else
      gparent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->entry.rbe_right = &gparent[gparent_idx];
  gparent->entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_windows_RB_INSERT_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const elm, struct window * const parent, struct window * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp_idx = parent->entry.rbe_right;
    if (parent->entry.rbe_right = tmp->entry.rbe_left)
    {
      tmp->entry.rbe_left->entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
      {
        parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->entry.rbe_left = &parent[parent_idx];
    parent->entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = &parent[parent_idx];
  parent_idx = &elm[elm_idx];
  elm_idx = &tmp[tmp_idx];
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_windows_RB_INSERT_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const gparent, struct window * const tmp, unsigned int gparent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->entry.rbe_right;
  if (gparent->entry.rbe_right = tmp->entry.rbe_left)
  {
    tmp->entry.rbe_left->entry.rbe_parent = &gparent[gparent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent = gparent->entry.rbe_parent)
  {
    if ((&gparent[gparent_idx]) == gparent->entry.rbe_parent->entry.rbe_left)
    {
      gparent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
    }
    else
      gparent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->entry.rbe_left = &gparent[gparent_idx];
  gparent->entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_windows_RB_INSERT_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const elm, struct window * const parent, struct window * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp_idx = parent->entry.rbe_left;
    if (parent->entry.rbe_left = tmp->entry.rbe_right)
    {
      tmp->entry.rbe_right->entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
      {
        parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->entry.rbe_right = &parent[parent_idx];
    parent->entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = &parent[parent_idx];
  parent_idx = &elm[elm_idx];
  elm_idx = &tmp[tmp_idx];
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_windows_RB_REMOVE_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp->entry.rbe_color = 0;
    parent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    tmp_idx = parent->entry.rbe_right;
    if (parent->entry.rbe_right = tmp->entry.rbe_left)
    {
      tmp->entry.rbe_left->entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
      {
        parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->entry.rbe_left = &parent[parent_idx];
    parent->entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->entry.rbe_right;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_windows_RB_REMOVE_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_windows_RB_REMOVE_COLOR_1_1_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_right)
  {
    tmp->entry.rbe_right->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_windows_RB_REMOVE_COLOR_1_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_windows_RB_REMOVE_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp->entry.rbe_color = 0;
    parent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    tmp_idx = parent->entry.rbe_left;
    if (parent->entry.rbe_left = tmp->entry.rbe_right)
    {
      tmp->entry.rbe_right->entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
      {
        parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->entry.rbe_right = &parent[parent_idx];
    parent->entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->entry.rbe_left;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_windows_RB_REMOVE_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_windows_RB_REMOVE_COLOR_1_2_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_left)
  {
    tmp->entry.rbe_left->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_windows_RB_REMOVE_COLOR_1_2_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_winlinks_RB_INSERT_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const gparent, struct winlink * const tmp, unsigned int gparent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->entry.rbe_left;
  if (gparent->entry.rbe_left = tmp->entry.rbe_right)
  {
    tmp->entry.rbe_right->entry.rbe_parent = &gparent[gparent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent = gparent->entry.rbe_parent)
  {
    if ((&gparent[gparent_idx]) == gparent->entry.rbe_parent->entry.rbe_left)
    {
      gparent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
    }
    else
      gparent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->entry.rbe_right = &gparent[gparent_idx];
  gparent->entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_winlinks_RB_INSERT_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const elm, struct winlink * const parent, struct winlink * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp_idx = parent->entry.rbe_right;
    if (parent->entry.rbe_right = tmp->entry.rbe_left)
    {
      tmp->entry.rbe_left->entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
      {
        parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->entry.rbe_left = &parent[parent_idx];
    parent->entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = &parent[parent_idx];
  parent_idx = &elm[elm_idx];
  elm_idx = &tmp[tmp_idx];
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_winlinks_RB_INSERT_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const gparent, struct winlink * const tmp, unsigned int gparent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->entry.rbe_right;
  if (gparent->entry.rbe_right = tmp->entry.rbe_left)
  {
    tmp->entry.rbe_left->entry.rbe_parent = &gparent[gparent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent = gparent->entry.rbe_parent)
  {
    if ((&gparent[gparent_idx]) == gparent->entry.rbe_parent->entry.rbe_left)
    {
      gparent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
    }
    else
      gparent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->entry.rbe_left = &gparent[gparent_idx];
  gparent->entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_winlinks_RB_INSERT_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const elm, struct winlink * const parent, struct winlink * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp_idx = parent->entry.rbe_left;
    if (parent->entry.rbe_left = tmp->entry.rbe_right)
    {
      tmp->entry.rbe_right->entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
      {
        parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->entry.rbe_right = &parent[parent_idx];
    parent->entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = &parent[parent_idx];
  parent_idx = &elm[elm_idx];
  elm_idx = &tmp[tmp_idx];
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp->entry.rbe_color = 0;
    parent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    tmp_idx = parent->entry.rbe_right;
    if (parent->entry.rbe_right = tmp->entry.rbe_left)
    {
      tmp->entry.rbe_left->entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
      {
        parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->entry.rbe_left = &parent[parent_idx];
    parent->entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->entry.rbe_right;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_1_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_right)
  {
    tmp->entry.rbe_right->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp->entry.rbe_color = 0;
    parent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    tmp_idx = parent->entry.rbe_left;
    if (parent->entry.rbe_left = tmp->entry.rbe_right)
    {
      tmp->entry.rbe_right->entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
      {
        parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->entry.rbe_right = &parent[parent_idx];
    parent->entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->entry.rbe_left;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_2_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_left)
  {
    tmp->entry.rbe_left->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_2_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_window_pane_tree_RB_INSERT_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const gparent, struct window_pane * const tmp, unsigned int gparent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->tree_entry.rbe_left;
  if (gparent->tree_entry.rbe_left = tmp->tree_entry.rbe_right)
  {
    tmp->tree_entry.rbe_right->tree_entry.rbe_parent = &gparent[gparent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->tree_entry.rbe_parent = gparent->tree_entry.rbe_parent)
  {
    if ((&gparent[gparent_idx]) == gparent->tree_entry.rbe_parent->tree_entry.rbe_left)
    {
      gparent->tree_entry.rbe_parent->tree_entry.rbe_left = &tmp[tmp_idx];
    }
    else
      gparent->tree_entry.rbe_parent->tree_entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->tree_entry.rbe_right = &gparent[gparent_idx];
  gparent->tree_entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->tree_entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_window_pane_tree_RB_INSERT_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const elm, struct window_pane * const parent, struct window_pane * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp_idx = parent->tree_entry.rbe_right;
    if (parent->tree_entry.rbe_right = tmp->tree_entry.rbe_left)
    {
      tmp->tree_entry.rbe_left->tree_entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->tree_entry.rbe_parent = parent->tree_entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->tree_entry.rbe_parent->tree_entry.rbe_left)
      {
        parent->tree_entry.rbe_parent->tree_entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->tree_entry.rbe_parent->tree_entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->tree_entry.rbe_left = &parent[parent_idx];
    parent->tree_entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->tree_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = &parent[parent_idx];
  parent_idx = &elm[elm_idx];
  elm_idx = &tmp[tmp_idx];
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_window_pane_tree_RB_INSERT_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const gparent, struct window_pane * const tmp, unsigned int gparent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->tree_entry.rbe_right;
  if (gparent->tree_entry.rbe_right = tmp->tree_entry.rbe_left)
  {
    tmp->tree_entry.rbe_left->tree_entry.rbe_parent = &gparent[gparent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->tree_entry.rbe_parent = gparent->tree_entry.rbe_parent)
  {
    if ((&gparent[gparent_idx]) == gparent->tree_entry.rbe_parent->tree_entry.rbe_left)
    {
      gparent->tree_entry.rbe_parent->tree_entry.rbe_left = &tmp[tmp_idx];
    }
    else
      gparent->tree_entry.rbe_parent->tree_entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->tree_entry.rbe_left = &gparent[gparent_idx];
  gparent->tree_entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->tree_entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_window_pane_tree_RB_INSERT_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const elm, struct window_pane * const parent, struct window_pane * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp_idx = parent->tree_entry.rbe_left;
    if (parent->tree_entry.rbe_left = tmp->tree_entry.rbe_right)
    {
      tmp->tree_entry.rbe_right->tree_entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->tree_entry.rbe_parent = parent->tree_entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->tree_entry.rbe_parent->tree_entry.rbe_left)
      {
        parent->tree_entry.rbe_parent->tree_entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->tree_entry.rbe_parent->tree_entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->tree_entry.rbe_right = &parent[parent_idx];
    parent->tree_entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->tree_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = &parent[parent_idx];
  parent_idx = &elm[elm_idx];
  elm_idx = &tmp[tmp_idx];
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp->tree_entry.rbe_color = 0;
    parent->tree_entry.rbe_color = 1;
  }
  while (0);
  do
  {
    tmp_idx = parent->tree_entry.rbe_right;
    if (parent->tree_entry.rbe_right = tmp->tree_entry.rbe_left)
    {
      tmp->tree_entry.rbe_left->tree_entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->tree_entry.rbe_parent = parent->tree_entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->tree_entry.rbe_parent->tree_entry.rbe_left)
      {
        parent->tree_entry.rbe_parent->tree_entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->tree_entry.rbe_parent->tree_entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->tree_entry.rbe_left = &parent[parent_idx];
    parent->tree_entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->tree_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->tree_entry.rbe_right;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->tree_entry.rbe_right == 0) || (tmp->tree_entry.rbe_right->tree_entry.rbe_color == 0))
  {
    helper_helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_1_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->tree_entry.rbe_color = parent->tree_entry.rbe_color;
  parent->tree_entry.rbe_color = 0;
  if (tmp->tree_entry.rbe_right)
  {
    tmp->tree_entry.rbe_right->tree_entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp->tree_entry.rbe_color = 0;
    parent->tree_entry.rbe_color = 1;
  }
  while (0);
  do
  {
    tmp_idx = parent->tree_entry.rbe_left;
    if (parent->tree_entry.rbe_left = tmp->tree_entry.rbe_right)
    {
      tmp->tree_entry.rbe_right->tree_entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->tree_entry.rbe_parent = parent->tree_entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->tree_entry.rbe_parent->tree_entry.rbe_left)
      {
        parent->tree_entry.rbe_parent->tree_entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->tree_entry.rbe_parent->tree_entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->tree_entry.rbe_right = &parent[parent_idx];
    parent->tree_entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->tree_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->tree_entry.rbe_left;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->tree_entry.rbe_left == 0) || (tmp->tree_entry.rbe_left->tree_entry.rbe_color == 0))
  {
    helper_helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_2_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->tree_entry.rbe_color = parent->tree_entry.rbe_color;
  parent->tree_entry.rbe_color = 0;
  if (tmp->tree_entry.rbe_left)
  {
    tmp->tree_entry.rbe_left->tree_entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_2_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_helper_windows_RB_REMOVE_COLOR_1_1_2_1(unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_right;
  if (parent->entry.rbe_right = tmp->entry.rbe_left)
  {
    tmp->entry.rbe_left->entry.rbe_parent = &parent[parent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
  {
    if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
    {
      parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
    }
    else
      parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->entry.rbe_left = &parent[parent_idx];
  parent->entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_helper_windows_RB_REMOVE_COLOR_1_1_2_2(unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct window *oleft;
  unsigned int oleft_idx = 0;
  if (oleft_idx = tmp->entry.rbe_left)
  {
    oleft->entry.rbe_color = 0;
  }
  tmp->entry.rbe_color = 1;
  do
  {
    oleft_idx = tmp->entry.rbe_left;
    if (tmp->entry.rbe_left = oleft->entry.rbe_right)
    {
      oleft->entry.rbe_right->entry.rbe_parent = &tmp[tmp_idx];
    }
    do
    {
    }
    while (0);
    if (oleft->entry.rbe_parent = tmp->entry.rbe_parent)
    {
      if ((&tmp[tmp_idx]) == tmp->entry.rbe_parent->entry.rbe_left)
      {
        tmp->entry.rbe_parent->entry.rbe_left = &oleft[oleft_idx];
      }
      else
        tmp->entry.rbe_parent->entry.rbe_right = &oleft[oleft_idx];
    }
    else
      head->rbh_root = &oleft[oleft_idx];
    oleft->entry.rbe_right = &tmp[tmp_idx];
    tmp->entry.rbe_parent = &oleft[oleft_idx];
    do
    {
    }
    while (0);
    if (oleft->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->entry.rbe_right;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_helper_windows_RB_REMOVE_COLOR_1_2_2_1(unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_left;
  if (parent->entry.rbe_left = tmp->entry.rbe_right)
  {
    tmp->entry.rbe_right->entry.rbe_parent = &parent[parent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
  {
    if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
    {
      parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
    }
    else
      parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->entry.rbe_right = &parent[parent_idx];
  parent->entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_helper_windows_RB_REMOVE_COLOR_1_2_2_2(unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct window *oright;
  unsigned int oright_idx = 0;
  if (oright_idx = tmp->entry.rbe_right)
  {
    oright->entry.rbe_color = 0;
  }
  tmp->entry.rbe_color = 1;
  do
  {
    oright_idx = tmp->entry.rbe_right;
    if (tmp->entry.rbe_right = oright->entry.rbe_left)
    {
      oright->entry.rbe_left->entry.rbe_parent = &tmp[tmp_idx];
    }
    do
    {
    }
    while (0);
    if (oright->entry.rbe_parent = tmp->entry.rbe_parent)
    {
      if ((&tmp[tmp_idx]) == tmp->entry.rbe_parent->entry.rbe_left)
      {
        tmp->entry.rbe_parent->entry.rbe_left = &oright[oright_idx];
      }
      else
        tmp->entry.rbe_parent->entry.rbe_right = &oright[oright_idx];
    }
    else
      head->rbh_root = &oright[oright_idx];
    oright->entry.rbe_left = &tmp[tmp_idx];
    tmp->entry.rbe_parent = &oright[oright_idx];
    do
    {
    }
    while (0);
    if (oright->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->entry.rbe_left;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_1_2_1(unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_right;
  if (parent->entry.rbe_right = tmp->entry.rbe_left)
  {
    tmp->entry.rbe_left->entry.rbe_parent = &parent[parent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
  {
    if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
    {
      parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
    }
    else
      parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->entry.rbe_left = &parent[parent_idx];
  parent->entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_1_2_2(unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct winlink *oleft;
  unsigned int oleft_idx = 0;
  if (oleft_idx = tmp->entry.rbe_left)
  {
    oleft->entry.rbe_color = 0;
  }
  tmp->entry.rbe_color = 1;
  do
  {
    oleft_idx = tmp->entry.rbe_left;
    if (tmp->entry.rbe_left = oleft->entry.rbe_right)
    {
      oleft->entry.rbe_right->entry.rbe_parent = &tmp[tmp_idx];
    }
    do
    {
    }
    while (0);
    if (oleft->entry.rbe_parent = tmp->entry.rbe_parent)
    {
      if ((&tmp[tmp_idx]) == tmp->entry.rbe_parent->entry.rbe_left)
      {
        tmp->entry.rbe_parent->entry.rbe_left = &oleft[oleft_idx];
      }
      else
        tmp->entry.rbe_parent->entry.rbe_right = &oleft[oleft_idx];
    }
    else
      head->rbh_root = &oleft[oleft_idx];
    oleft->entry.rbe_right = &tmp[tmp_idx];
    tmp->entry.rbe_parent = &oleft[oleft_idx];
    do
    {
    }
    while (0);
    if (oleft->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->entry.rbe_right;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_2_2_1(unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_left;
  if (parent->entry.rbe_left = tmp->entry.rbe_right)
  {
    tmp->entry.rbe_right->entry.rbe_parent = &parent[parent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
  {
    if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
    {
      parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
    }
    else
      parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->entry.rbe_right = &parent[parent_idx];
  parent->entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_2_2_2(unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct winlink *oright;
  unsigned int oright_idx = 0;
  if (oright_idx = tmp->entry.rbe_right)
  {
    oright->entry.rbe_color = 0;
  }
  tmp->entry.rbe_color = 1;
  do
  {
    oright_idx = tmp->entry.rbe_right;
    if (tmp->entry.rbe_right = oright->entry.rbe_left)
    {
      oright->entry.rbe_left->entry.rbe_parent = &tmp[tmp_idx];
    }
    do
    {
    }
    while (0);
    if (oright->entry.rbe_parent = tmp->entry.rbe_parent)
    {
      if ((&tmp[tmp_idx]) == tmp->entry.rbe_parent->entry.rbe_left)
      {
        tmp->entry.rbe_parent->entry.rbe_left = &oright[oright_idx];
      }
      else
        tmp->entry.rbe_parent->entry.rbe_right = &oright[oright_idx];
    }
    else
      head->rbh_root = &oright[oright_idx];
    oright->entry.rbe_left = &tmp[tmp_idx];
    tmp->entry.rbe_parent = &oright[oright_idx];
    do
    {
    }
    while (0);
    if (oright->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->entry.rbe_left;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_1_2_1(unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->tree_entry.rbe_right;
  if (parent->tree_entry.rbe_right = tmp->tree_entry.rbe_left)
  {
    tmp->tree_entry.rbe_left->tree_entry.rbe_parent = &parent[parent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->tree_entry.rbe_parent = parent->tree_entry.rbe_parent)
  {
    if ((&parent[parent_idx]) == parent->tree_entry.rbe_parent->tree_entry.rbe_left)
    {
      parent->tree_entry.rbe_parent->tree_entry.rbe_left = &tmp[tmp_idx];
    }
    else
      parent->tree_entry.rbe_parent->tree_entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->tree_entry.rbe_left = &parent[parent_idx];
  parent->tree_entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->tree_entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_1_2_2(unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct window_pane *oleft;
  unsigned int oleft_idx = 0;
  if (oleft_idx = tmp->tree_entry.rbe_left)
  {
    oleft->tree_entry.rbe_color = 0;
  }
  tmp->tree_entry.rbe_color = 1;
  do
  {
    oleft_idx = tmp->tree_entry.rbe_left;
    if (tmp->tree_entry.rbe_left = oleft->tree_entry.rbe_right)
    {
      oleft->tree_entry.rbe_right->tree_entry.rbe_parent = &tmp[tmp_idx];
    }
    do
    {
    }
    while (0);
    if (oleft->tree_entry.rbe_parent = tmp->tree_entry.rbe_parent)
    {
      if ((&tmp[tmp_idx]) == tmp->tree_entry.rbe_parent->tree_entry.rbe_left)
      {
        tmp->tree_entry.rbe_parent->tree_entry.rbe_left = &oleft[oleft_idx];
      }
      else
        tmp->tree_entry.rbe_parent->tree_entry.rbe_right = &oleft[oleft_idx];
    }
    else
      head->rbh_root = &oleft[oleft_idx];
    oleft->tree_entry.rbe_right = &tmp[tmp_idx];
    tmp->tree_entry.rbe_parent = &oleft[oleft_idx];
    do
    {
    }
    while (0);
    if (oleft->tree_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->tree_entry.rbe_right;
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_2_2_1(unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->tree_entry.rbe_left;
  if (parent->tree_entry.rbe_left = tmp->tree_entry.rbe_right)
  {
    tmp->tree_entry.rbe_right->tree_entry.rbe_parent = &parent[parent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->tree_entry.rbe_parent = parent->tree_entry.rbe_parent)
  {
    if ((&parent[parent_idx]) == parent->tree_entry.rbe_parent->tree_entry.rbe_left)
    {
      parent->tree_entry.rbe_parent->tree_entry.rbe_left = &tmp[tmp_idx];
    }
    else
      parent->tree_entry.rbe_parent->tree_entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->tree_entry.rbe_right = &parent[parent_idx];
  parent->tree_entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->tree_entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}

void helper_helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_2_2_2(unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct window_pane *oright;
  unsigned int oright_idx = 0;
  if (oright_idx = tmp->tree_entry.rbe_right)
  {
    oright->tree_entry.rbe_color = 0;
  }
  tmp->tree_entry.rbe_color = 1;
  do
  {
    oright_idx = tmp->tree_entry.rbe_right;
    if (tmp->tree_entry.rbe_right = oright->tree_entry.rbe_left)
    {
      oright->tree_entry.rbe_left->tree_entry.rbe_parent = &tmp[tmp_idx];
    }
    do
    {
    }
    while (0);
    if (oright->tree_entry.rbe_parent = tmp->tree_entry.rbe_parent)
    {
      if ((&tmp[tmp_idx]) == tmp->tree_entry.rbe_parent->tree_entry.rbe_left)
      {
        tmp->tree_entry.rbe_parent->tree_entry.rbe_left = &oright[oright_idx];
      }
      else
        tmp->tree_entry.rbe_parent->tree_entry.rbe_right = &oright[oright_idx];
    }
    else
      head->rbh_root = &oright[oright_idx];
    oright->tree_entry.rbe_left = &tmp[tmp_idx];
    tmp->tree_entry.rbe_parent = &oright[oright_idx];
    do
    {
    }
    while (0);
    if (oright->tree_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->tree_entry.rbe_left;
  *tmp_idx_ref = tmp_idx;
}

