// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
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
}
/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
***/


// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
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
}
/*** DEPENDENCIES:
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
}
----------------------------
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
None
----------------------------
None
----------------------------
***/


// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
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
}
/*** DEPENDENCIES:
enum cmd_retval
{
  CMD_RETURN_ERROR = -1,
  CMD_RETURN_NORMAL = 0,
  CMD_RETURN_WAIT,
  CMD_RETURN_STOP
}
----------------------------
None
----------------------------
***/


// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
struct winlink_stack
{
  struct winlink *tqh_first;
  struct winlink **tqh_last;
}
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
struct cmd_list
{
  int references;
  struct 
  {
    struct cmd *tqh_first;
    struct cmd **tqh_last;
  } list;
}
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
struct key_bindings
{
  struct key_binding *rbh_root;
}
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
struct format_job
{
  struct client *client;
  u_int tag;
  const char *cmd;
  const char *expanded;
  time_t last;
  char *out;
  int updated;
  struct job *job;
  int status;
  struct 
  {
    struct format_job *rbe_left;
    struct format_job *rbe_right;
    struct format_job *rbe_parent;
    int rbe_color;
  } entry;
}
/*** DEPENDENCIES:
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
}
----------------------------
None
----------------------------
***/


// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
struct cmdq_shared
{
  int references;
  int flags;
  struct format_tree *formats;
  struct mouse_event mouse;
  struct cmd_find_state current;
}
/*** DEPENDENCIES:
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
}
----------------------------
None
----------------------------
***/


// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
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
}
/*** DEPENDENCIES:
None
----------------------------
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
None
----------------------------
None
----------------------------
***/


// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
struct window_panes
{
  struct window_pane *tqh_first;
  struct window_pane **tqh_last;
}
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
struct window_mode
{
  const char *name;
  struct screen *(*init)(struct window_pane *, struct cmd_find_state *, struct args *);
  void (*free)(struct window_pane *);
  void (*resize)(struct window_pane *, u_int, u_int);
  void (*key)(struct window_pane *, struct client *, struct session *, key_code, struct mouse_event *);
  const char *(*key_table)(struct window_pane *);
  void (*command)(struct window_pane *, struct client *, struct session *, struct args *, struct mouse_event *);
}
/*** DEPENDENCIES:
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
}
----------------------------
None
----------------------------
None
----------------------------
typedef unsigned long long key_code
----------------------------
None
----------------------------
***/


// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
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
}
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
struct input_transition
{
  int first;
  int last;
  int (*handler)(struct input_ctx *);
  const struct input_state *state;
}
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
struct tty_key
{
  char ch;
  key_code key;
  struct tty_key *left;
  struct tty_key *right;
  struct tty_key *next;
}
/*** DEPENDENCIES:
typedef unsigned long long key_code
----------------------------
None
----------------------------
***/


// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
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
}
/*** DEPENDENCIES:
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
None
----------------------------
None
----------------------------
None
----------------------------
***/


// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
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
}
/*** DEPENDENCIES:
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
None
----------------------------
None
----------------------------
***/


// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
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
}
/*** DEPENDENCIES:
None
----------------------------
struct screen_write_collect_line
{
  struct 
  {
    struct screen_write_collect_item *tqh_first;
    struct screen_write_collect_item **tqh_last;
  } items;
}
----------------------------
struct screen_write_collect_item
{
  u_int x;
  int wrapped;
  u_int used;
  char data[256];
  struct grid_cell gc;
  struct 
  {
    struct screen_write_collect_item *tqe_next;
    struct screen_write_collect_item **tqe_prev;
  } entry;
}
----------------------------
None
----------------------------
***/


// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
struct layout_cells
{
  struct layout_cell *tqh_first;
  struct layout_cell **tqh_last;
}
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
struct format_tree
{
  struct window *w;
  struct winlink *wl;
  struct session *s;
  struct window_pane *wp;
  struct client *client;
  u_int tag;
  int flags;
  struct format_entry_tree
  {
    struct format_entry *rbh_root;
  } tree;
}
/*** DEPENDENCIES:
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
None
----------------------------
***/


// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
struct cmd_find_state
{
  int flags;
  struct cmd_find_state *current;
  struct session *s;
  struct winlink *wl;
  struct window *w;
  struct window_pane *wp;
  int idx;
}
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
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
}
/*** DEPENDENCIES:
enum layout_type
{
  LAYOUT_LEFTRIGHT,
  LAYOUT_TOPBOTTOM,
  LAYOUT_WINDOWPANE
}
----------------------------
None
----------------------------
***/


// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
struct cmd_entry_flag
{
  char flag;
  enum cmd_find_type type;
  int flags;
}
/*** DEPENDENCIES:
enum cmd_find_type
{
  CMD_FIND_PANE,
  CMD_FIND_WINDOW,
  CMD_FIND_SESSION
}
----------------------------
None
----------------------------
***/


// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
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
}
/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
None
----------------------------
***/


// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
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
}
/*** DEPENDENCIES:
struct tmuxpeer
{
  struct tmuxproc *parent;
  struct imsgbuf ibuf;
  struct event event;
  int flags;
  void (*dispatchcb)(struct imsg *, void *);
  void *arg;
}
----------------------------
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
}
----------------------------
typedef int (*prompt_input_cb)(struct client *, void *, const char *, int)
----------------------------
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
}
----------------------------
struct status_line
{
  struct event timer;
  struct screen status;
  struct screen *old_status;
}
----------------------------
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
}
----------------------------
typedef void (*prompt_free_cb)(void *)
----------------------------
None
----------------------------
None
----------------------------
***/


// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
struct cmdq_list
{
  struct cmdq_item *tqh_first;
  struct cmdq_item **tqh_last;
}
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
struct input_state
{
  const char *name;
  void (*enter)(struct input_ctx *);
  void (*exit)(struct input_ctx *);
  const struct input_transition *transitions;
}
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
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
}
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
struct hooks
{
  struct hooks_tree
  {
    struct hook *rbh_root;
  } tree;
  struct hooks *parent;
}
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
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
}
/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
struct tty_code
{
  enum tty_code_type type;
  union 
  {
    char *string;
    int number;
    int flag;
  } value;
}
/*** DEPENDENCIES:
enum tty_code_type
{
  TTYCODE_NONE = 0,
  TTYCODE_STRING,
  TTYCODE_NUMBER,
  TTYCODE_FLAG
}
----------------------------
None
----------------------------
***/


// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
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
}
/*** DEPENDENCIES:
enum cmdq_type
{
  CMDQ_COMMAND,
  CMDQ_CALLBACK
}
----------------------------
typedef enum cmd_retval (*cmdq_cb)(struct cmdq_item *, void *)
----------------------------
None
----------------------------
***/


// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
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
}
/*** DEPENDENCIES:
typedef unsigned long long key_code
----------------------------
None
----------------------------
***/


// element in merge of:  cmd,tty,cmd_entry,winlink_stack,cmd_list,key_bindings,format_job,cmdq_shared,window_pane,window_panes,window_mode,hook,input_transition,tty_key,window,winlink,screen_write_ctx,layout_cells,format_tree,cmd_find_state,layout_cell,cmd_entry_flag,session,client,cmdq_list,input_state,key_table,hooks,tty_term,tty_code,cmdq_item,key_binding,input_ctx
struct input_ctx
{
  struct window_pane *wp;
  struct screen_write_ctx ctx;
  struct input_cell cell;
  struct input_cell old_cell;
  u_int old_cx;
  u_int old_cy;
  u_char interm_buf[4];
  size_t interm_len;
  u_char param_buf[64];
  size_t param_len;
  u_char *input_buf;
  size_t input_len;
  size_t input_space;
  struct input_param param_list[24];
  u_int param_list_len;
  struct utf8_data utf8data;
  int utf8started;
  int ch;
  int last;
  int flags;
  const struct input_state *state;
  struct event timer;
  struct evbuffer *since_ground;
}
/*** DEPENDENCIES:
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
}
----------------------------
struct input_param
{
  enum 
  {
    INPUT_MISSING,
    INPUT_NUMBER,
    INPUT_STRING
  } type;
  union 
  {
    int num;
    char *str;
  };
}
----------------------------
struct input_cell
{
  struct grid_cell cell;
  int set;
  int g0set;
  int g1set;
}
----------------------------
None
----------------------------
None
----------------------------
***/


