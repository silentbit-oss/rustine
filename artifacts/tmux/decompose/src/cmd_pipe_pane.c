// hint:  ['null_fd_ref is a mutable refrence to int']
void helper_cmd_pipe_pane_exec_2(int * const null_fd_ref, char * const cmd, int pipe_fd[2], int in, int out, sigset_t oldset)
{
  int null_fd = *null_fd_ref;
  proc_clear_signals(server_proc, 1);
  sigprocmask(SIG_SETMASK, &oldset, 0);
  close(pipe_fd[0]);
  null_fd = open("/dev/null", O_WRONLY, 0);
  if (out)
  {
    if (dup2(pipe_fd[1], STDIN_FILENO) == (-1))
    {
      _exit(1);
    }
  }
  else
  {
    if (dup2(null_fd, STDIN_FILENO) == (-1))
    {
      _exit(1);
    }
  }
  if (in)
  {
    if (dup2(pipe_fd[1], STDOUT_FILENO) == (-1))
    {
      _exit(1);
    }
    if (pipe_fd[1] != STDOUT_FILENO)
    {
      close(pipe_fd[1]);
    }
  }
  else
  {
    if (dup2(null_fd, STDOUT_FILENO) == (-1))
    {
      _exit(1);
    }
  }
  if (dup2(null_fd, STDERR_FILENO) == (-1))
  {
    _exit(1);
  }
  closefrom(STDERR_FILENO + 1);
  execl("/bin/sh", "sh", "-c", cmd, (char *) 0);
  _exit(1);
  *null_fd_ref = null_fd;
}


/*** DEPENDENCIES:
void proc_clear_signals(struct tmuxproc *tp, int defaults)
{
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  sa.sa_handler = SIG_DFL;
  sigaction(SIGINT, &sa, 0);
  sigaction(SIGPIPE, &sa, 0);
  sigaction(SIGTSTP, &sa, 0);
  signal_del(&tp->ev_sighup);
  signal_del(&tp->ev_sigchld);
  signal_del(&tp->ev_sigcont);
  signal_del(&tp->ev_sigterm);
  signal_del(&tp->ev_sigusr1);
  signal_del(&tp->ev_sigusr2);
  signal_del(&tp->ev_sigwinch);
  if (defaults)
  {
    sigaction(SIGHUP, &sa, 0);
    sigaction(SIGCHLD, &sa, 0);
    sigaction(SIGCONT, &sa, 0);
    sigaction(SIGTERM, &sa, 0);
    sigaction(SIGUSR1, &sa, 0);
    sigaction(SIGUSR2, &sa, 0);
    sigaction(SIGWINCH, &sa, 0);
  }
}


----------------------------
***/


static void cmd_pipe_pane_read_callback(struct bufferevent *bufev, void *data)
{
  struct window_pane *wp = data;
  struct evbuffer *evb = wp->pipe_event->input;
  size_t available;
  available = EVBUFFER_LENGTH(evb);
  log_debug("%%%u pipe read %zu", wp->id, available);
  bufferevent_write(wp->event, EVBUFFER_DATA(evb), available);
  evbuffer_drain(evb, available);
  if (window_pane_destroy_ready(wp))
  {
    server_destroy_pane(wp, 1);
  }
}


/*** DEPENDENCIES:
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
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


----------------------------
void server_destroy_pane(struct window_pane *wp, int notify)
{
  struct window *w = wp->window;
  struct screen_write_ctx ctx;
  struct grid_cell gc;
  time_t t;
  char tim[26];
  if (wp->fd != (-1))
  {
    bufferevent_free(wp->event);
    close(wp->fd);
    wp->fd = -1;
  }
  if (options_get_number(w->options, "remain-on-exit"))
  {
    helper_server_destroy_pane_1(wp, notify, ctx, gc, t, tim);
  }
  if (notify)
  {
    notify_pane("pane-exited", wp);
  }
  server_unzoom_window(w);
  layout_close_pane(wp);
  window_remove_pane(w, wp);
  if ((&w->panes)->tqh_first == 0)
  {
    server_kill_window(w);
  }
  else
    server_redraw_window(w);
}


----------------------------
None
----------------------------
***/


static void cmd_pipe_pane_write_callback(struct bufferevent *bufev, void *data)
{
  struct window_pane *wp = data;
  log_debug("%%%u pipe empty", wp->id);
  if (window_pane_destroy_ready(wp))
  {
    server_destroy_pane(wp, 1);
  }
}


/*** DEPENDENCIES:
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
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


----------------------------
void server_destroy_pane(struct window_pane *wp, int notify)
{
  struct window *w = wp->window;
  struct screen_write_ctx ctx;
  struct grid_cell gc;
  time_t t;
  char tim[26];
  if (wp->fd != (-1))
  {
    bufferevent_free(wp->event);
    close(wp->fd);
    wp->fd = -1;
  }
  if (options_get_number(w->options, "remain-on-exit"))
  {
    helper_server_destroy_pane_1(wp, notify, ctx, gc, t, tim);
  }
  if (notify)
  {
    notify_pane("pane-exited", wp);
  }
  server_unzoom_window(w);
  layout_close_pane(wp);
  window_remove_pane(w, wp);
  if ((&w->panes)->tqh_first == 0)
  {
    server_kill_window(w);
  }
  else
    server_redraw_window(w);
}


----------------------------
None
----------------------------
***/


static void cmd_pipe_pane_error_callback(struct bufferevent *bufev, short what, void *data)
{
  struct window_pane *wp = data;
  log_debug("%%%u pipe error", wp->id);
  bufferevent_free(wp->pipe_event);
  close(wp->pipe_fd);
  wp->pipe_fd = -1;
  if (window_pane_destroy_ready(wp))
  {
    server_destroy_pane(wp, 1);
  }
}


/*** DEPENDENCIES:
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
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


----------------------------
void server_destroy_pane(struct window_pane *wp, int notify)
{
  struct window *w = wp->window;
  struct screen_write_ctx ctx;
  struct grid_cell gc;
  time_t t;
  char tim[26];
  if (wp->fd != (-1))
  {
    bufferevent_free(wp->event);
    close(wp->fd);
    wp->fd = -1;
  }
  if (options_get_number(w->options, "remain-on-exit"))
  {
    helper_server_destroy_pane_1(wp, notify, ctx, gc, t, tim);
  }
  if (notify)
  {
    notify_pane("pane-exited", wp);
  }
  server_unzoom_window(w);
  layout_close_pane(wp);
  window_remove_pane(w, wp);
  if ((&w->panes)->tqh_first == 0)
  {
    server_kill_window(w);
  }
  else
    server_redraw_window(w);
}


----------------------------
None
----------------------------
***/


enum cmd_retval helper_cmd_pipe_pane_exec_1(struct window_pane * const wp, char * const cmd, int pipe_fd[2], int in, int out, sigset_t oldset)
{
  sigprocmask(SIG_SETMASK, &oldset, 0);
  close(pipe_fd[1]);
  wp->pipe_fd = pipe_fd[0];
  wp->pipe_off = EVBUFFER_LENGTH(wp->event->input);
  setblocking(wp->pipe_fd, 0);
  wp->pipe_event = bufferevent_new(wp->pipe_fd, cmd_pipe_pane_read_callback, cmd_pipe_pane_write_callback, cmd_pipe_pane_error_callback, wp);
  if (out)
  {
    bufferevent_enable(wp->pipe_event, EV_WRITE);
  }
  if (in)
  {
    bufferevent_enable(wp->pipe_event, EV_READ);
  }
  free(cmd);
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
static void cmd_pipe_pane_read_callback(struct bufferevent *bufev, void *data)
{
  struct window_pane *wp = data;
  struct evbuffer *evb = wp->pipe_event->input;
  size_t available;
  available = EVBUFFER_LENGTH(evb);
  log_debug("%%%u pipe read %zu", wp->id, available);
  bufferevent_write(wp->event, EVBUFFER_DATA(evb), available);
  evbuffer_drain(evb, available);
  if (window_pane_destroy_ready(wp))
  {
    server_destroy_pane(wp, 1);
  }
}


----------------------------
static void cmd_pipe_pane_error_callback(struct bufferevent *bufev, short what, void *data)
{
  struct window_pane *wp = data;
  log_debug("%%%u pipe error", wp->id);
  bufferevent_free(wp->pipe_event);
  close(wp->pipe_fd);
  wp->pipe_fd = -1;
  if (window_pane_destroy_ready(wp))
  {
    server_destroy_pane(wp, 1);
  }
}


----------------------------
static void cmd_pipe_pane_write_callback(struct bufferevent *bufev, void *data)
{
  struct window_pane *wp = data;
  log_debug("%%%u pipe empty", wp->id);
  if (window_pane_destroy_ready(wp))
  {
    server_destroy_pane(wp, 1);
  }
}


----------------------------
enum cmd_retval
{
  CMD_RETURN_ERROR = -1,
  CMD_RETURN_NORMAL = 0,
  CMD_RETURN_WAIT,
  CMD_RETURN_STOP
}
----------------------------
void setblocking(int fd, int state)
{
  int mode;
  if ((mode = fcntl(fd, F_GETFL)) != (-1))
  {
    if (!state)
    {
      mode |= O_NONBLOCK;
    }
    else
      mode &= ~O_NONBLOCK;
    fcntl(fd, F_SETFL, mode);
  }
}


----------------------------
None
----------------------------
***/


static enum cmd_retval cmd_pipe_pane_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct client *c = cmd_find_client(item, 0, 1);
  struct window_pane *wp = item->target.wp;
  struct session *s = item->target.s;
  struct winlink *wl = item->target.wl;
  char *cmd;
  unsigned int cmd_idx = 0;
  int old_fd;
  int pipe_fd[2];
  int null_fd;
  int in;
  int out;
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  sigset_t set;
  sigset_t oldset;
  old_fd = wp->pipe_fd;
  if (wp->pipe_fd != (-1))
  {
    bufferevent_free(wp->pipe_event);
    close(wp->pipe_fd);
    wp->pipe_fd = -1;
    if (window_pane_destroy_ready(wp))
    {
      server_destroy_pane(wp, 1);
      return CMD_RETURN_NORMAL;
    }
  }
  if ((args->argc == 0) || ((*args->argv[0]) == '\0'))
  {
    return CMD_RETURN_NORMAL;
  }
  if (args_has(self->args, 'o') && (old_fd != (-1)))
  {
    return CMD_RETURN_NORMAL;
  }
  if (args_has(self->args, 'I'))
  {
    in = 1;
    out = args_has(self->args, 'O');
  }
  else
  {
    in = 0;
    out = 1;
  }
  if (socketpair(AF_UNIX, SOCK_STREAM, PF_UNSPEC, pipe_fd) != 0)
  {
    cmdq_error(item, "socketpair error: %s", strerror(errno));
    return CMD_RETURN_ERROR;
  }
  ft_idx = format_create(item->client, item, 0, 0);
  format_defaults(ft, c, s, wl, wp);
  cmd_idx = format_expand_time(ft, args->argv[0], time(0));
  format_free(ft);
  sigfillset(&set);
  sigprocmask(SIG_BLOCK, &set, &oldset);
  switch (fork())
  {
    case -1:
    {
      sigprocmask(SIG_SETMASK, &oldset, 0);
      cmdq_error(item, "fork error: %s", strerror(errno));
      free(cmd);
      return CMD_RETURN_ERROR;
    }

    case 0:
    {
      helper_cmd_pipe_pane_exec_2(&null_fd, cmd, pipe_fd, in, out, oldset);
    }

    default:
    {
      helper_cmd_pipe_pane_exec_1(wp, cmd, pipe_fd, in, out, oldset);
    }

  }

}


/*** DEPENDENCIES:
void helper_cmd_pipe_pane_exec_2(int * const null_fd_ref, char * const cmd, int pipe_fd[2], int in, int out, sigset_t oldset)
{
  int null_fd = *null_fd_ref;
  proc_clear_signals(server_proc, 1);
  sigprocmask(SIG_SETMASK, &oldset, 0);
  close(pipe_fd[0]);
  null_fd = open("/dev/null", O_WRONLY, 0);
  if (out)
  {
    if (dup2(pipe_fd[1], STDIN_FILENO) == (-1))
    {
      _exit(1);
    }
  }
  else
  {
    if (dup2(null_fd, STDIN_FILENO) == (-1))
    {
      _exit(1);
    }
  }
  if (in)
  {
    if (dup2(pipe_fd[1], STDOUT_FILENO) == (-1))
    {
      _exit(1);
    }
    if (pipe_fd[1] != STDOUT_FILENO)
    {
      close(pipe_fd[1]);
    }
  }
  else
  {
    if (dup2(null_fd, STDOUT_FILENO) == (-1))
    {
      _exit(1);
    }
  }
  if (dup2(null_fd, STDERR_FILENO) == (-1))
  {
    _exit(1);
  }
  closefrom(STDERR_FILENO + 1);
  execl("/bin/sh", "sh", "-c", cmd, (char *) 0);
  _exit(1);
  *null_fd_ref = null_fd;
}


----------------------------
void format_free(struct format_tree *ft)
{
  struct format_entry *fe;
  unsigned int fe_idx = 0;
  struct format_entry *fe1;
  unsigned int fe1_idx = 0;
  for (fe_idx = format_entry_tree_RB_MINMAX(&ft->tree, -1); ((&fe[fe_idx]) != 0) && ((fe1_idx = format_entry_tree_RB_NEXT(fe), 1)); fe_idx = &fe1[fe1_idx])
  {
    format_entry_tree_RB_REMOVE(&ft->tree, fe);
    free(fe->value);
    free(fe->key);
    free(fe);
  }

  if (ft->client != 0)
  {
    server_client_unref(ft->client);
  }
  free(ft);
}


----------------------------
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


----------------------------
int args_has(struct args *args, u_char ch)
{
  return args_find(args, ch) != 0;
}


----------------------------
struct format_tree *format_create(struct client *c, struct cmdq_item *item, int tag, int flags)
{
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  if (!event_initialized(&format_job_event))
  {
    evtimer_set(&format_job_event, format_job_timer, 0);
    format_job_timer(-1, 0, 0);
  }
  ft_idx = xcalloc(1, sizeof(*ft_idx));
  do
  {
    (&ft->tree)->rbh_root = 0;
  }
  while (0);
  if (c != 0)
  {
    ft->client = c;
    ft->client->references += 1;
  }
  ft->tag = tag;
  ft->flags = flags;
  format_add(ft, "version", "%s", VERSION);
  format_add_cb(ft, "host", format_cb_host);
  format_add_cb(ft, "host_short", format_cb_host_short);
  format_add_cb(ft, "pid", format_cb_pid);
  format_add(ft, "socket_path", "%s", socket_path);
  format_add_tv(ft, "start_time", &start_time);
  if (item != 0)
  {
    if (item->cmd != 0)
    {
      format_add(ft, "command", "%s", item->cmd->entry->name);
    }
    if ((item->shared != 0) && (item->shared->formats != 0))
    {
      format_merge(ft, item->shared->formats);
    }
  }
  return ft;
}


----------------------------
pub time: Time
----------------------------
enum cmd_retval
{
  CMD_RETURN_ERROR = -1,
  CMD_RETURN_NORMAL = 0,
  CMD_RETURN_WAIT,
  CMD_RETURN_STOP
}
----------------------------
void server_destroy_pane(struct window_pane *wp, int notify)
{
  struct window *w = wp->window;
  struct screen_write_ctx ctx;
  struct grid_cell gc;
  time_t t;
  char tim[26];
  if (wp->fd != (-1))
  {
    bufferevent_free(wp->event);
    close(wp->fd);
    wp->fd = -1;
  }
  if (options_get_number(w->options, "remain-on-exit"))
  {
    helper_server_destroy_pane_1(wp, notify, ctx, gc, t, tim);
  }
  if (notify)
  {
    notify_pane("pane-exited", wp);
  }
  server_unzoom_window(w);
  layout_close_pane(wp);
  window_remove_pane(w, wp);
  if ((&w->panes)->tqh_first == 0)
  {
    server_kill_window(w);
  }
  else
    server_redraw_window(w);
}


----------------------------
void cmdq_error(struct cmdq_item *item, const char *fmt, ...)
{
  struct client *c = item->client;
  struct cmd *cmd = item->cmd;
  va_list ap;
  char *msg;
  unsigned int msg_idx = 0;
  size_t msglen;
  char *tmp;
  unsigned int tmp_idx = 0;
  __builtin_va_start(ap);
  msglen = xvasprintf(&(&msg[msg_idx]), fmt, ap);
  ;
  log_debug("%s: %s", __func__, msg);
  if (c == 0)
  {
    cfg_add_cause("%s:%u: %s", cmd->file, cmd->line, msg);
  }
  else
    if ((c->session == 0) || (c->flags & 0x2000))
  {
    if ((~c->flags) & 0x10000)
    {
      tmp_idx = &msg[msg_idx];
      msg_idx = utf8_sanitize(tmp);
      free(tmp);
      msglen = strlen(msg);
    }
    evbuffer_add(c->stderr_data, msg, msglen);
    evbuffer_add(c->stderr_data, "\n", 1);
    server_client_push_stderr(c);
    c->retval = 1;
  }
  else
  {
    msg[msg_idx] = toupper((u_char) msg[msg_idx]);
    status_message_set(c, "%s", msg);
  }
  free(msg);
}


----------------------------
struct client *cmd_find_client(struct cmdq_item *item, const char *target, int quiet)
{
  struct client *c;
  unsigned int c_idx = 0;
  char *copy;
  unsigned int copy_idx = 0;
  size_t size;
  if (target == 0)
  {
    return cmd_find_current_client(item, quiet);
  }
  copy_idx = xstrdup(target);
  size = strlen(copy);
  if ((size != 0) && (copy[(size - 1) + copy_idx] == ':'))
  {
    copy[(size - 1) + copy_idx] = '\0';
  }
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (c->session == 0)
    {
      continue;
    }
    if (strcmp(copy, c->name) == 0)
    {
      break;
    }
    if ((*c->ttyname) == '\0')
    {
      continue;
    }
    if (strcmp(copy, c->ttyname) == 0)
    {
      break;
    }
    if (strncmp(c->ttyname, "/dev/", (sizeof("/dev/")) - 1) != 0)
    {
      continue;
    }
    if (strcmp(copy, (c->ttyname + (sizeof("/dev/"))) - 1) == 0)
    {
      break;
    }
  }

  if (((&c[c_idx]) == 0) && (!quiet))
  {
    cmdq_error(item, "can't find client %s", copy);
  }
  free(copy);
  log_debug("%s: target %s, return %p", __func__, target, c);
  return c;
}


----------------------------
None
----------------------------
char *format_expand_time(struct format_tree *ft, const char *fmt, time_t t)
{
  struct tm *tm;
  unsigned int tm_idx = 0;
  char s[2048];
  if ((fmt == 0) || ((*fmt) == '\0'))
  {
    return xstrdup("");
  }
  tm_idx = localtime(&t);
  if (strftime(s, sizeof(s), fmt, tm) == 0)
  {
    return xstrdup("");
  }
  return format_expand(ft, s);
}


----------------------------
void format_defaults(struct format_tree *ft, struct client *c, struct session *s, struct winlink *wl, struct window_pane *wp)
{
  unsigned int wp_idx = 0;
  unsigned int wl_idx = 0;
  unsigned int s_idx = 0;
  if (((c != 0) && ((&s[s_idx]) != 0)) && (c->session != (&s[s_idx])))
  {
    log_debug("%s: session does not match", __func__);
  }
  format_add(ft, "session_format", "%d", (&s[s_idx]) != 0);
  format_add(ft, "window_format", "%d", (&wl[wl_idx]) != 0);
  format_add(ft, "pane_format", "%d", (&wp[wp_idx]) != 0);
  if (((&s[s_idx]) == 0) && (c != 0))
  {
    s_idx = c->session;
  }
  if (((&wl[wl_idx]) == 0) && ((&s[s_idx]) != 0))
  {
    wl_idx = s->curw;
  }
  if (((&wp[wp_idx]) == 0) && ((&wl[wl_idx]) != 0))
  {
    wp_idx = wl->window->active;
  }
  if (c != 0)
  {
    format_defaults_client(ft, c);
  }
  if ((&s[s_idx]) != 0)
  {
    format_defaults_session(ft, s);
  }
  if ((&wl[wl_idx]) != 0)
  {
    format_defaults_winlink(ft, wl);
  }
  if ((&wp[wp_idx]) != 0)
  {
    format_defaults_pane(ft, wp);
  }
}


----------------------------
enum cmd_retval helper_cmd_pipe_pane_exec_1(struct window_pane * const wp, char * const cmd, int pipe_fd[2], int in, int out, sigset_t oldset)
{
  sigprocmask(SIG_SETMASK, &oldset, 0);
  close(pipe_fd[1]);
  wp->pipe_fd = pipe_fd[0];
  wp->pipe_off = EVBUFFER_LENGTH(wp->event->input);
  setblocking(wp->pipe_fd, 0);
  wp->pipe_event = bufferevent_new(wp->pipe_fd, cmd_pipe_pane_read_callback, cmd_pipe_pane_write_callback, cmd_pipe_pane_error_callback, wp);
  if (out)
  {
    bufferevent_enable(wp->pipe_event, EV_WRITE);
  }
  if (in)
  {
    bufferevent_enable(wp->pipe_event, EV_READ);
  }
  free(cmd);
  return CMD_RETURN_NORMAL;
}


----------------------------
None
----------------------------
***/


