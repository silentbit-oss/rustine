static enum cmd_retval cmd_respawn_window_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct session *s = item->target.s;
  struct winlink *wl = item->target.wl;
  struct window *w = wl->window;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  struct client *c = cmd_find_client(item, 0, 1);
  struct environ *env;
  unsigned int env_idx = 0;
  const char *path = 0;
  unsigned int path_idx = 0;
  const char *cp;
  unsigned int cp_idx = 0;
  char *cause;
  char *cwd = 0;
  unsigned int cwd_idx = 0;
  struct environ_entry *envent;
  unsigned int envent_idx = 0;
  if (!args_has(self->args, 'k'))
  {
    for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
    {
      if (wp->fd == (-1))
      {
        continue;
      }
      cmdq_error(item, "window still active: %s:%d", s->name, wl->idx);
      return CMD_RETURN_ERROR;
    }

  }
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
  layout_free(w);
  window_destroy_panes(w);
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
  window_pane_resize(wp, w->sx, w->sy);
  if ((item->client != 0) && (item->client->session == 0))
  {
    envent_idx = environ_find(item->client->environ, "PATH");
  }
  else
    envent_idx = environ_find(s->environ, "PATH");
  if ((&envent[envent_idx]) != 0)
  {
    path_idx = envent->value;
  }
  if ((cp_idx = args_get(args, 'c')) != 0)
  {
    cwd_idx = format_single(item, cp, c, s, 0, 0);
  }
  env_idx = environ_for_session(s, 0);
  if (window_pane_spawn(wp, args->argc, args->argv, path, 0, cwd, env, s->tio, &cause) != 0)
  {
    cmdq_error(item, "respawn window failed: %s", cause);
    free(cause);
    environ_free(env);
    free(cwd);
    server_destroy_pane(wp, 0);
    return CMD_RETURN_ERROR;
  }
  environ_free(env);
  free(cwd);
  layout_init(w, wp);
  window_pane_reset_mode(wp);
  screen_reinit(&wp->base);
  input_init(wp);
  window_set_active_pane(w, wp);
  recalculate_sizes();
  server_redraw_window(w);
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
None
----------------------------
void layout_free(struct window *w)
{
  layout_free_cell(w->layout_root);
}


----------------------------
void recalculate_sizes(void)
{
  struct session *s;
  unsigned int s_idx = 0;
  struct client *c;
  unsigned int c_idx = 0;
  struct window *w;
  unsigned int w_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int ssx;
  u_int ssy;
  u_int has;
  u_int limit;
  u_int lines;
  int flag;
  int is_zoomed;
  int forced;
  for (s_idx = sessions_RB_MINMAX(&sessions, -1); (&s[s_idx]) != 0; s_idx = sessions_RB_NEXT(s_idx))
  {
    helper_recalculate_sizes_1(&c_idx, &ssx, &ssy, &lines, s, s_idx, c);
  }

  for (w_idx = windows_RB_MINMAX(&windows, -1); (&w[w_idx]) != 0; w_idx = windows_RB_NEXT(w_idx))
  {
    helper_recalculate_sizes_2(&s_idx, &wp_idx, &ssx, &ssy, &has, &limit, &flag, &is_zoomed, &forced, s, w, w_idx, wp);
  }

}


----------------------------
const char *args_get(struct args *args, u_char ch)
{
  struct args_entry *entry;
  unsigned int entry_idx = 0;
  if ((entry_idx = args_find(args, ch)) == 0)
  {
    return 0;
  }
  return entry->value;
}


----------------------------
void server_redraw_window(struct window *w)
{
  struct client *c;
  unsigned int c_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if ((c->session != 0) && (c->session->curw->window == w))
    {
      server_redraw_client(c);
    }
  }

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
void environ_free(struct environ *env)
{
  struct environ_entry *envent;
  unsigned int envent_idx = 0;
  struct environ_entry *envent1;
  unsigned int envent1_idx = 0;
  for (envent_idx = environ_RB_MINMAX(env, -1); ((&envent[envent_idx]) != 0) && ((envent1_idx = environ_RB_NEXT(envent), 1)); envent_idx = &envent1[envent1_idx])
  {
    environ_RB_REMOVE(env, envent);
    free(envent->name);
    free(envent->value);
    free(envent);
  }

  free(env);
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


----------------------------
struct environ *environ_for_session(struct session *s, int no_TERM)
{
  struct environ *env;
  unsigned int env_idx = 0;
  const char *value;
  unsigned int value_idx = 0;
  int idx;
  env_idx = environ_create();
  environ_copy(global_environ, env);
  if (s != 0)
  {
    environ_copy(s->environ, env);
  }
  if (!no_TERM)
  {
    value_idx = options_get_string(global_options, "default-terminal");
    environ_set(env, "TERM", "%s", value);
  }
  if (s != 0)
  {
    idx = s->id;
  }
  else
    idx = -1;
  environ_set(env, "TMUX", "%s,%ld,%d", socket_path, (long) getpid(), idx);
  return env;
}


----------------------------
None
----------------------------
void screen_reinit(struct screen *s)
{
  s->cx = 0;
  s->cy = 0;
  s->rupper = 0;
  s->rlower = s->grid->sy - 1;
  s->mode = 0x1 | 0x10;
  screen_reset_tabs(s);
  grid_clear_lines(s->grid, s->grid->hsize, s->grid->sy, 8);
  screen_clear_selection(s);
  screen_free_titles(s);
}


----------------------------
char *format_single(struct cmdq_item *item, const char *fmt, struct client *c, struct session *s, struct winlink *wl, struct window_pane *wp)
{
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  char *expanded;
  unsigned int expanded_idx = 0;
  if (item != 0)
  {
    ft_idx = format_create(item->client, item, 0, 0);
  }
  else
    ft_idx = format_create(0, item, 0, 0);
  format_defaults(ft, c, s, wl, wp);
  expanded_idx = format_expand(ft, fmt);
  format_free(ft);
  return expanded;
}


----------------------------
int args_has(struct args *args, u_char ch)
{
  return args_find(args, ch) != 0;
}


----------------------------
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


----------------------------
void layout_init(struct window *w, struct window_pane *wp)
{
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  lc_idx = (w->layout_root = layout_create_cell(0));
  layout_set_size(lc, w->sx, w->sy, 0, 0);
  layout_make_leaf(lc, wp);
  layout_fix_panes(w, w->sx, w->sy);
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
void input_init(struct window_pane *wp)
{
  struct input_ctx *ictx;
  unsigned int ictx_idx = 0;
  ictx_idx = (wp->ictx_idx = xcalloc(1, sizeof(*ictx_idx)));
  ictx->input_space = 32;
  ictx->input_buf = xmalloc(32);
  ictx->since_ground = evbuffer_new();
  evtimer_set(&ictx->timer, input_timer_callback, ictx);
  input_reset(wp, 0);
}


----------------------------
struct environ_entry *environ_find(struct environ *env, const char *name)
{
  struct environ_entry envent;
  envent.name = (char *) name;
  return environ_RB_FIND(env, &envent);
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


----------------------------
None
----------------------------
***/


