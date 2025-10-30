#include <bitstring.h>
#include <compat.h>
#include <event.h>
#include <imsg.h>
#include <inttypes.h>
#include <ioctl.h>
#include <limits.h>
#include <queue.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <time.h>
#include <tmux.h>
#include <tree.h>
#include <types.h>
#include <uio.h>
#include <vis.h>
#include <wchar.h>
#include <window-buffer.c>
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
static struct screen *window_buffer_init(struct window_pane *, struct cmd_find_state *, struct args *);
static void window_buffer_free(struct window_pane *);
static void window_buffer_resize(struct window_pane *, u_int, u_int);
static void window_buffer_key(struct window_pane *, struct client *, struct session *, key_code, struct mouse_event *);
const struct window_mode window_buffer_mode = {.name = "buffer-mode", .init = window_buffer_init, .free = window_buffer_free, .resize = window_buffer_resize, .key = window_buffer_key};
enum window_buffer_sort_type
{
  WINDOW_BUFFER_BY_TIME,
  WINDOW_BUFFER_BY_NAME,
  WINDOW_BUFFER_BY_SIZE
};
static const char *window_buffer_sort_list[] = {"time", "name", "size"};
struct window_buffer_itemdata
{
  const char *name;
  u_int order;
  size_t size;
};
struct window_buffer_modedata
{
  struct mode_tree_data *data;
  char *command;
  char *format;
  struct window_buffer_itemdata **item_list;
  u_int item_size;
};
static struct window_buffer_itemdata *window_buffer_add_item(struct window_buffer_modedata *data)
{
  struct window_buffer_itemdata *item;
  unsigned int item_idx = 0;
  data->item_list = xreallocarray(data->item_list, data->item_size + 1, sizeof(*data->item_list));
  item_idx = (data->item_list[data->item_size++] = xcalloc(1, sizeof(*item_idx)));
  return item;
}

static void window_buffer_free_item(struct window_buffer_itemdata *item)
{
  free((void *) item->name);
  free(item);
}

static int window_buffer_cmp_name(const void *a0, const void *b0)
{
  const struct window_buffer_itemdata * const *a = a0;
  const struct window_buffer_itemdata * const *b = b0;
  return strcmp((*a)->name, (*b)->name);
}

static int window_buffer_cmp_time(const void *a0, const void *b0)
{
  const struct window_buffer_itemdata * const *a = a0;
  const struct window_buffer_itemdata * const *b = b0;
  if ((*a)->order > (*b)->order)
  {
    return -1;
  }
  if ((*a)->order < (*b)->order)
  {
    return 1;
  }
  return strcmp((*a)->name, (*b)->name);
}

static int window_buffer_cmp_size(const void *a0, const void *b0)
{
  const struct window_buffer_itemdata * const *a = a0;
  const struct window_buffer_itemdata * const *b = b0;
  if ((*a)->size > (*b)->size)
  {
    return -1;
  }
  if ((*a)->size < (*b)->size)
  {
    return 1;
  }
  return strcmp((*a)->name, (*b)->name);
}

static void window_buffer_build(void *modedata, u_int sort_type, uint64_t *tag, const char *filter)
{
  struct window_buffer_modedata *data = modedata;
  struct window_buffer_itemdata *item;
  unsigned int item_idx = 0;
  u_int i;
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  char *text;
  unsigned int text_idx = 0;
  char *cp;
  unsigned int cp_idx = 0;
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  for (i = 0; i < data->item_size; i += 1)
  {
    window_buffer_free_item(data->item_list[i]);
  }

  free(data->item_list);
  data->item_list = 0;
  data->item_size = 0;
  pb_idx = 0;
  while ((pb_idx = paste_walk(pb_idx)) != 0)
  {
    item_idx = window_buffer_add_item(data);
    item->name = xstrdup(paste_buffer_name(pb));
    paste_buffer_data(pb, &item->size);
    item->order = paste_buffer_order(pb);
  }

  switch (sort_type)
  {
    case WINDOW_BUFFER_BY_NAME:
    {
      qsort(data->item_list, data->item_size, sizeof(*data->item_list), window_buffer_cmp_name);
      break;
    }

    case WINDOW_BUFFER_BY_TIME:
    {
      qsort(data->item_list, data->item_size, sizeof(*data->item_list), window_buffer_cmp_time);
      break;
    }

    case WINDOW_BUFFER_BY_SIZE:
    {
      qsort(data->item_list, data->item_size, sizeof(*data->item_list), window_buffer_cmp_size);
      break;
    }

  }

  for (i = 0; i < data->item_size; i += 1)
  {
    helper_window_buffer_build_1(&item_idx, &pb_idx, &text_idx, &cp_idx, &ft_idx, filter, data, item, i, pb, text, cp, ft);
  }

}

static void window_buffer_draw(void *modedata, void *itemdata, struct screen_write_ctx *ctx, u_int sx, u_int sy)
{
  struct window_buffer_itemdata *item = itemdata;
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  char line[1024];
  const char *pdata;
  unsigned int pdata_idx = 0;
  const char *end;
  unsigned int end_idx = 0;
  const char *cp;
  unsigned int cp_idx = 0;
  size_t psize;
  size_t at;
  u_int i;
  u_int cx = ctx->s->cx;
  u_int cy = ctx->s->cy;
  pb_idx = paste_get_name(item->name);
  if ((&pb[pb_idx]) == 0)
  {
    return;
  }
  pdata_idx = (end = &end[end_idx + end_idx]);
  for (i = 0; i < sy; i += 1)
  {
    helper_window_buffer_draw_1(&end_idx, &cp_idx, &at, ctx, sx, line, pdata, pdata_idx, end, cp, psize, i, cx, cy);
  }

}

static int window_buffer_search(void *modedata, void *itemdata, const char *ss)
{
  struct window_buffer_itemdata *item = itemdata;
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  const char *bufdata;
  unsigned int bufdata_idx = 0;
  size_t bufsize;
  if ((pb_idx = paste_get_name(item->name)) == 0)
  {
    return 0;
  }
  if (strstr(item->name, ss) != 0)
  {
    return 1;
  }
  bufdata_idx = paste_buffer_data(pb, &bufsize);
  return memmem(bufdata, bufsize, ss, strlen(ss)) != 0;
}

static struct screen *window_buffer_init(struct window_pane *wp, struct cmd_find_state *fs, struct args *args)
{
  struct window_buffer_modedata *data;
  struct screen *s;
  wp->modedata = (data = xcalloc(1, sizeof(*data)));
  if ((args == 0) || (!args_has(args, 'F')))
  {
    data->format = xstrdup("#{buffer_size} bytes (#{t:buffer_created})");
  }
  else
    data->format = xstrdup(args_get(args, 'F'));
  if ((args == 0) || (args->argc == 0))
  {
    data->command = xstrdup("paste-buffer -b '%%'");
  }
  else
    data->command = xstrdup(args->argv[0]);
  data->data = mode_tree_start(wp, args, window_buffer_build, window_buffer_draw, window_buffer_search, data, window_buffer_sort_list, (sizeof(window_buffer_sort_list)) / (sizeof(window_buffer_sort_list[0])), &s);
  mode_tree_zoom(data->data, args);
  mode_tree_build(data->data);
  mode_tree_draw(data->data);
  return s;
}

static void window_buffer_free(struct window_pane *wp)
{
  struct window_buffer_modedata *data = wp->modedata;
  u_int i;
  if (data == 0)
  {
    return;
  }
  mode_tree_free(data->data);
  for (i = 0; i < data->item_size; i += 1)
  {
    window_buffer_free_item(data->item_list[i]);
  }

  free(data->item_list);
  free(data->format);
  free(data->command);
  free(data);
}

static void window_buffer_resize(struct window_pane *wp, u_int sx, u_int sy)
{
  struct window_buffer_modedata *data = wp->modedata;
  mode_tree_resize(data->data, sx, sy);
}

static void window_buffer_do_delete(void *modedata, void *itemdata, struct client *c, key_code key)
{
  struct window_buffer_modedata *data = modedata;
  struct window_buffer_itemdata *item = itemdata;
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  if (item == mode_tree_get_current(data->data))
  {
    mode_tree_down(data->data, 0);
  }
  if ((pb_idx = paste_get_name(item->name)) != 0)
  {
    paste_free(pb);
  }
}

static void window_buffer_do_paste(void *modedata, void *itemdata, struct client *c, key_code key)
{
  struct window_buffer_modedata *data = modedata;
  struct window_buffer_itemdata *item = itemdata;
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  if ((pb_idx = paste_get_name(item->name)) != 0)
  {
    mode_tree_run_command(c, 0, data->command, item->name);
  }
}

static void window_buffer_key(struct window_pane *wp, struct client *c, struct session *s, key_code key, struct mouse_event *m)
{
  struct window_buffer_modedata *data = wp->modedata;
  struct mode_tree_data *mtd = data->data;
  struct window_buffer_itemdata *item;
  unsigned int item_idx = 0;
  int finished;
  finished = mode_tree_key(mtd, c, &key, m, 0, 0);
  switch (key)
  {
    case 'd':
    {
      item_idx = mode_tree_get_current(mtd);
      window_buffer_do_delete(data, item, c, key);
      mode_tree_build(mtd);
      break;
    }

    case 'D':
    {
      mode_tree_each_tagged(mtd, window_buffer_do_delete, c, key, 0);
      mode_tree_build(mtd);
      break;
    }

    case 'P':
    {
      mode_tree_each_tagged(mtd, window_buffer_do_paste, c, key, 0);
      finished = 1;
      break;
    }

    case 'p':

    case '\r':
    {
      item_idx = mode_tree_get_current(mtd);
      window_buffer_do_paste(data, item, c, key);
      finished = 1;
      break;
    }

  }

  if (finished || (paste_get_top(0) == 0))
  {
    window_pane_reset_mode(wp);
  }
  else
  {
    mode_tree_draw(mtd);
    wp->flags |= 0x1;
  }
}


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
static struct screen *window_buffer_init(struct window_pane *, struct cmd_find_state *, struct args *);
static void window_buffer_free(struct window_pane *);
static void window_buffer_resize(struct window_pane *, u_int, u_int);
static void window_buffer_key(struct window_pane *, struct client *, struct session *, key_code, struct mouse_event *);
const struct window_mode window_buffer_mode = {.name = "buffer-mode", .init = window_buffer_init, .free = window_buffer_free, .resize = window_buffer_resize, .key = window_buffer_key};
enum window_buffer_sort_type
{
  WINDOW_BUFFER_BY_TIME,
  WINDOW_BUFFER_BY_NAME,
  WINDOW_BUFFER_BY_SIZE
};
static const char *window_buffer_sort_list[] = {"time", "name", "size"};
struct window_buffer_itemdata
{
  const char *name;
  u_int order;
  size_t size;
};
struct window_buffer_modedata
{
  struct mode_tree_data *data;
  char *command;
  char *format;
  struct window_buffer_itemdata **item_list;
  u_int item_size;
};
static struct window_buffer_itemdata *window_buffer_add_item(struct window_buffer_modedata *data)
{
  struct window_buffer_itemdata *item;
  unsigned int item_idx = 0;
  data->item_list = xreallocarray(data->item_list, data->item_size + 1, sizeof(*data->item_list));
  item_idx = (data->item_list[data->item_size++] = xcalloc(1, sizeof(*item_idx)));
  return item;
}

static void window_buffer_free_item(struct window_buffer_itemdata *item)
{
  free((void *) item->name);
  free(item);
}

static int window_buffer_cmp_name(const void *a0, const void *b0)
{
  const struct window_buffer_itemdata * const *a = a0;
  const struct window_buffer_itemdata * const *b = b0;
  return strcmp((*a)->name, (*b)->name);
}

static int window_buffer_cmp_time(const void *a0, const void *b0)
{
  const struct window_buffer_itemdata * const *a = a0;
  const struct window_buffer_itemdata * const *b = b0;
  if ((*a)->order > (*b)->order)
  {
    return -1;
  }
  if ((*a)->order < (*b)->order)
  {
    return 1;
  }
  return strcmp((*a)->name, (*b)->name);
}

static int window_buffer_cmp_size(const void *a0, const void *b0)
{
  const struct window_buffer_itemdata * const *a = a0;
  const struct window_buffer_itemdata * const *b = b0;
  if ((*a)->size > (*b)->size)
  {
    return -1;
  }
  if ((*a)->size < (*b)->size)
  {
    return 1;
  }
  return strcmp((*a)->name, (*b)->name);
}

static void window_buffer_build(void *modedata, u_int sort_type, uint64_t *tag, const char *filter)
{
  struct window_buffer_modedata *data = modedata;
  struct window_buffer_itemdata *item;
  unsigned int item_idx = 0;
  u_int i;
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  char *text;
  unsigned int text_idx = 0;
  char *cp;
  unsigned int cp_idx = 0;
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  for (i = 0; i < data->item_size; i += 1)
  {
    window_buffer_free_item(data->item_list[i]);
  }

  free(data->item_list);
  data->item_list = 0;
  data->item_size = 0;
  pb_idx = 0;
  while ((pb_idx = paste_walk(pb_idx)) != 0)
  {
    item_idx = window_buffer_add_item(data);
    item->name = xstrdup(paste_buffer_name(pb));
    paste_buffer_data(pb, &item->size);
    item->order = paste_buffer_order(pb);
  }

  switch (sort_type)
  {
    case WINDOW_BUFFER_BY_NAME:
      qsort(data->item_list, data->item_size, sizeof(*data->item_list), window_buffer_cmp_name);
      break;

    case WINDOW_BUFFER_BY_TIME:
      qsort(data->item_list, data->item_size, sizeof(*data->item_list), window_buffer_cmp_time);
      break;

    case WINDOW_BUFFER_BY_SIZE:
      qsort(data->item_list, data->item_size, sizeof(*data->item_list), window_buffer_cmp_size);
      break;

  }

  for (i = 0; i < data->item_size; i += 1)
  {
    item_idx = data->item_list[i];
    pb_idx = paste_get_name(item->name);
    if ((&pb[pb_idx]) == 0)
    {
      continue;
    }
    ft_idx = format_create(0, 0, 0, 0);
    format_defaults_paste_buffer(ft, pb);
    if (filter != 0)
    {
      cp_idx = format_expand(ft, filter);
      if (!format_true(cp))
      {
        free(cp);
        format_free(ft);
        continue;
      }
      free(cp);
    }
    text_idx = format_expand(ft, data->format);
    mode_tree_add(data->data, 0, item, item->order, item->name, text, -1);
    free(text);
    format_free(ft);
  }

}

static void window_buffer_draw(void *modedata, void *itemdata, struct screen_write_ctx *ctx, u_int sx, u_int sy)
{
  struct window_buffer_itemdata *item = itemdata;
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  char line[1024];
  const char *pdata;
  unsigned int pdata_idx = 0;
  const char *end;
  unsigned int end_idx = 0;
  const char *cp;
  unsigned int cp_idx = 0;
  size_t psize;
  size_t at;
  u_int i;
  u_int cx = ctx->s->cx;
  u_int cy = ctx->s->cy;
  pb_idx = paste_get_name(item->name);
  if ((&pb[pb_idx]) == 0)
  {
    return;
  }
  pdata_idx = (end = &end[end_idx + end_idx]);
  for (i = 0; i < sy; i += 1)
  {
    at = 0;
    while (((&end[end_idx]) != ((&pdata[pdata_idx]) + psize)) && (end[end_idx] != '\n'))
    {
      if (((sizeof(line)) - at) > 5)
      {
        cp_idx = vis(line + at, *(&end[end_idx]), 0x08 | 0x01, 0);
        at = (&cp[cp_idx]) - line;
      }
      end_idx += 1;
    }

    if (at > sx)
    {
      at = sx;
    }
    line[at] = '\0';
    if ((*line) != '\0')
    {
      screen_write_cursormove(ctx, cx, cy + i);
      screen_write_puts(ctx, &grid_default_cell, "%s", line);
    }
    if ((&end[end_idx]) == ((&pdata[pdata_idx]) + psize))
    {
      break;
    }
    end_idx += 1;
  }

}

static int window_buffer_search(void *modedata, void *itemdata, const char *ss)
{
  struct window_buffer_itemdata *item = itemdata;
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  const char *bufdata;
  unsigned int bufdata_idx = 0;
  size_t bufsize;
  if ((pb_idx = paste_get_name(item->name)) == 0)
  {
    return 0;
  }
  if (strstr(item->name, ss) != 0)
  {
    return 1;
  }
  bufdata_idx = paste_buffer_data(pb, &bufsize);
  return memmem(bufdata, bufsize, ss, strlen(ss)) != 0;
}

static struct screen *window_buffer_init(struct window_pane *wp, struct cmd_find_state *fs, struct args *args)
{
  struct window_buffer_modedata *data;
  struct screen *s;
  wp->modedata = (data = xcalloc(1, sizeof(*data)));
  if ((args == 0) || (!args_has(args, 'F')))
  {
    data->format = xstrdup("#{buffer_size} bytes (#{t:buffer_created})");
  }
  else
    data->format = xstrdup(args_get(args, 'F'));
  if ((args == 0) || (args->argc == 0))
  {
    data->command = xstrdup("paste-buffer -b '%%'");
  }
  else
    data->command = xstrdup(args->argv[0]);
  data->data = mode_tree_start(wp, args, window_buffer_build, window_buffer_draw, window_buffer_search, data, window_buffer_sort_list, (sizeof(window_buffer_sort_list)) / (sizeof(window_buffer_sort_list[0])), &s);
  mode_tree_zoom(data->data, args);
  mode_tree_build(data->data);
  mode_tree_draw(data->data);
  return s;
}

static void window_buffer_free(struct window_pane *wp)
{
  struct window_buffer_modedata *data = wp->modedata;
  u_int i;
  if (data == 0)
  {
    return;
  }
  mode_tree_free(data->data);
  for (i = 0; i < data->item_size; i += 1)
  {
    window_buffer_free_item(data->item_list[i]);
  }

  free(data->item_list);
  free(data->format);
  free(data->command);
  free(data);
}

static void window_buffer_resize(struct window_pane *wp, u_int sx, u_int sy)
{
  struct window_buffer_modedata *data = wp->modedata;
  mode_tree_resize(data->data, sx, sy);
}

static void window_buffer_do_delete(void *modedata, void *itemdata, struct client *c, key_code key)
{
  struct window_buffer_modedata *data = modedata;
  struct window_buffer_itemdata *item = itemdata;
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  if (item == mode_tree_get_current(data->data))
  {
    mode_tree_down(data->data, 0);
  }
  if ((pb_idx = paste_get_name(item->name)) != 0)
  {
    paste_free(pb);
  }
}

static void window_buffer_do_paste(void *modedata, void *itemdata, struct client *c, key_code key)
{
  struct window_buffer_modedata *data = modedata;
  struct window_buffer_itemdata *item = itemdata;
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  if ((pb_idx = paste_get_name(item->name)) != 0)
  {
    mode_tree_run_command(c, 0, data->command, item->name);
  }
}

static void window_buffer_key(struct window_pane *wp, struct client *c, struct session *s, key_code key, struct mouse_event *m)
{
  struct window_buffer_modedata *data = wp->modedata;
  struct mode_tree_data *mtd = data->data;
  struct window_buffer_itemdata *item;
  unsigned int item_idx = 0;
  int finished;
  finished = mode_tree_key(mtd, c, &key, m, 0, 0);
  switch (key)
  {
    case 'd':
      item_idx = mode_tree_get_current(mtd);
      window_buffer_do_delete(data, item, c, key);
      mode_tree_build(mtd);
      break;

    case 'D':
      mode_tree_each_tagged(mtd, window_buffer_do_delete, c, key, 0);
      mode_tree_build(mtd);
      break;

    case 'P':
      mode_tree_each_tagged(mtd, window_buffer_do_paste, c, key, 0);
      finished = 1;
      break;

    case 'p':

    case '\r':
      item_idx = mode_tree_get_current(mtd);
      window_buffer_do_paste(data, item, c, key);
      finished = 1;
      break;

  }

  if (finished || (paste_get_top(0) == 0))
  {
    window_pane_reset_mode(wp);
  }
  else
  {
    mode_tree_draw(mtd);
    wp->flags |= 0x1;
  }
}

void helper_window_buffer_build_1(unsigned int * const item_idx_ref, unsigned int * const pb_idx_ref, unsigned int * const text_idx_ref, unsigned int * const cp_idx_ref, unsigned int * const ft_idx_ref, const char * const filter, struct window_buffer_modedata * const data, struct window_buffer_itemdata * const item, u_int i, struct paste_buffer * const pb, char * const text, char * const cp, struct format_tree * const ft)
{
  unsigned int item_idx = *item_idx_ref;
  unsigned int pb_idx = *pb_idx_ref;
  unsigned int text_idx = *text_idx_ref;
  unsigned int cp_idx = *cp_idx_ref;
  unsigned int ft_idx = *ft_idx_ref;
  item_idx = data->item_list[i];
  pb_idx = paste_get_name(item->name);
  if ((&pb[pb_idx]) == 0)
  {
    continue;
  }
  ft_idx = format_create(0, 0, 0, 0);
  format_defaults_paste_buffer(ft, pb);
  if (filter != 0)
  {
    cp_idx = format_expand(ft, filter);
    if (!format_true(cp))
    {
      free(cp);
      format_free(ft);
      continue;
    }
    free(cp);
  }
  text_idx = format_expand(ft, data->format);
  mode_tree_add(data->data, 0, item, item->order, item->name, text, -1);
  free(text);
  format_free(ft);
  *item_idx_ref = item_idx;
  *pb_idx_ref = pb_idx;
  *text_idx_ref = text_idx;
  *cp_idx_ref = cp_idx;
  *ft_idx_ref = ft_idx;
}

void helper_window_buffer_draw_1(unsigned int * const end_idx_ref, unsigned int * const cp_idx_ref, size_t * const at_ref, struct screen_write_ctx * const ctx, u_int sx, char line[1024], const char * const pdata, unsigned int pdata_idx, const char * const end, const char * const cp, size_t psize, u_int i, u_int cx, u_int cy)
{
  unsigned int end_idx = *end_idx_ref;
  unsigned int cp_idx = *cp_idx_ref;
  size_t at = *at_ref;
  at = 0;
  while (((&end[end_idx]) != ((&pdata[pdata_idx]) + psize)) && (end[end_idx] != '\n'))
  {
    if (((sizeof(line)) - at) > 5)
    {
      cp_idx = vis(line + at, *(&end[end_idx]), 0x08 | 0x01, 0);
      at = (&cp[cp_idx]) - line;
    }
    end_idx += 1;
  }

  if (at > sx)
  {
    at = sx;
  }
  line[at] = '\0';
  if ((*line) != '\0')
  {
    screen_write_cursormove(ctx, cx, cy + i);
    screen_write_puts(ctx, &grid_default_cell, "%s", line);
  }
  if ((&end[end_idx]) == ((&pdata[pdata_idx]) + psize))
  {
    break;
  }
  end_idx += 1;
  *end_idx_ref = end_idx;
  *cp_idx_ref = cp_idx;
  *at_ref = at;
}

