static enum cmd_retval cmd_split_window_exec(struct cmd *self, struct cmdq_item *item)
{
  struct cmd_find_state *current = &item->shared->current;
  struct args *args = self->args;
  struct client *c = cmd_find_client(item, 0, 1);
  struct session *s = item->target.s;
  struct winlink *wl = item->target.wl;
  struct window *w = wl->window;
  struct window_pane *wp = item->target.wp;
  struct window_pane *new_wp = 0;
  unsigned int new_wp_idx = 0;
  struct environ *env;
  unsigned int env_idx = 0;
  const char *cmd;
  unsigned int cmd_idx = 0;
  const char *path;
  unsigned int path_idx = 0;
  const char *shell;
  unsigned int shell_idx = 0;
  const char *template;
  unsigned int template_idx = 0;
  const char *tmp;
  unsigned int tmp_idx = 0;
  char **argv;
  unsigned int argv_idx = 0;
  char *cause;
  unsigned int cause_idx = 0;
  char *new_cause;
  char *cp;
  unsigned int cp_idx = 0;
  char *cwd;
  unsigned int cwd_idx = 0;
  u_int hlimit;
  int argc;
  int size;
  int percentage;
  int before;
  enum layout_type type;
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  struct environ_entry *envent;
  unsigned int envent_idx = 0;
  struct cmd_find_state fs;
  server_unzoom_window(w);
  if (args->argc == 0)
  {
    cmd_idx = options_get_string(s->options, "default-command");
    if (((&cmd[cmd_idx]) != 0) && (cmd[cmd_idx] != '\0'))
    {
      argc = 1;
      argv_idx = (char **) (&(&cmd[cmd_idx]));
    }
    else
    {
      argc = 0;
      argv_idx = 0;
    }
  }
  else
  {
    argc = args->argc;
    argv_idx = args->argv_idx;
  }
  if ((tmp_idx = args_get(args, 'c')) != 0)
  {
    cwd_idx = format_single(item, tmp, c, s, 0, 0);
  }
  else
    if ((item->client != 0) && (item->client->session == 0))
  {
    cwd_idx = xstrdup(item->client->cwd_idx);
  }
  else
    cwd_idx = xstrdup(s->cwd_idx);
  type = LAYOUT_TOPBOTTOM;
  if (args_has(args, 'h'))
  {
    type = LAYOUT_LEFTRIGHT;
  }
  before = args_has(args, 'b');
  size = -1;
  if (args_has(args, 'l'))
  {
    size = args_strtonum(args, 'l', 0, 2147483647, &(&cause[cause_idx]));
    if ((&cause[cause_idx]) != 0)
    {
      xasprintf(&new_cause, "size %s", cause);
      free(cause);
      cause_idx = new_cause;
      goto error;
    }
  }
  else
    if (args_has(args, 'p'))
  {
    percentage = args_strtonum(args, 'p', 0, 2147483647, &(&cause[cause_idx]));
    if ((&cause[cause_idx]) != 0)
    {
      xasprintf(&new_cause, "percentage %s", cause);
      free(cause);
      cause_idx = new_cause;
      goto error;
    }
    if (type == LAYOUT_TOPBOTTOM)
    {
      size = (wp->sy * percentage) / 100;
    }
    else
      size = (wp->sx * percentage) / 100;
  }
  hlimit = options_get_number(s->options, "history-limit");
  shell_idx = options_get_string(s->options, "default-shell");
  if ((shell[shell_idx] == '\0') || areshell(shell))
  {
    shell_idx = "/bin/sh";
  }
  lc_idx = layout_split_pane(wp, type, size, before, args_has(args, 'f'));
  if ((&lc[lc_idx]) == 0)
  {
    cause_idx = xstrdup("pane too small");
    goto error;
  }
  new_wp_idx = window_add_pane(w, wp, before, args_has(args, 'f'), hlimit);
  layout_make_leaf(lc, new_wp);
  path_idx = 0;
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
  env_idx = environ_for_session(s, 0);
  if (window_pane_spawn(new_wp, argc, argv, path, shell, cwd, env, s->tio, &(&cause[cause_idx])) != 0)
  {
    environ_free(env);
    goto error;
  }
  environ_free(env);
  layout_fix_panes(w, w->sx, w->sy);
  server_redraw_window(w);
  if (!args_has(args, 'd'))
  {
    window_set_active_pane(w, new_wp);
    session_select(s, wl->idx);
    cmd_find_from_session(current, s, 0);
    server_redraw_session(s);
  }
  else
    server_status_session(s);
  if (args_has(args, 'P'))
  {
    if ((template_idx = args_get(args, 'F')) == 0)
    {
      template_idx = "#{session_name}:#{window_index}.#{pane_index}";
    }
    cp_idx = format_single(item, template, c, s, wl, new_wp);
    cmdq_print(item, "%s", cp);
    free(cp);
  }
  notify_window("window-layout-changed", w);
  cmd_find_from_winlink_pane(&fs, wl, new_wp, 0);
  hooks_insert(s->hooks, item, &fs, "after-split-window");
  free(cwd);
  return CMD_RETURN_NORMAL;
  error:
  if ((&new_wp[new_wp_idx]) != 0)
  {
    layout_close_pane(new_wp);
    window_remove_pane(w, new_wp);
  }

  cmdq_error(item, "create pane failed: %s", cause);
  free(cause);
  free(cwd);
  return CMD_RETURN_ERROR;
}


/*** DEPENDENCIES:
void server_unzoom_window(struct window *w)
{
  if (window_unzoom(w) == 0)
  {
    server_redraw_window(w);
  }
}


----------------------------
void notify_window(const char *name, struct window *w)
{
  struct cmd_find_state fs;
  cmd_find_from_window(&fs, w, 0);
  notify_add(name, &fs, 0, 0, w, 0);
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


----------------------------
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


----------------------------
enum layout_type
{
  LAYOUT_LEFTRIGHT,
  LAYOUT_TOPBOTTOM,
  LAYOUT_WINDOWPANE
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
void hooks_insert(struct hooks *hooks, struct cmdq_item *item, struct cmd_find_state *fs, const char *fmt, ...)
{
  struct hook *hook;
  unsigned int hook_idx = 0;
  va_list ap;
  char *name;
  struct cmdq_item *new_item;
  unsigned int new_item_idx = 0;
  if (item->flags & 0x4)
  {
    return;
  }
  __builtin_va_start(ap);
  xvasprintf(&name, fmt, ap);
  ;
  hook_idx = hooks_find(hooks, name);
  if ((&hook[hook_idx]) == 0)
  {
    free(name);
    return;
  }
  log_debug("running hook %s (parent %p)", name, item);
  new_item_idx = cmdq_get_command(hook->cmdlist, fs, 0, 0x4);
  cmdq_format(new_item, "hook", "%s", name);
  if (item != 0)
  {
    cmdq_insert_after(item, new_item);
  }
  else
    cmdq_append(0, new_item);
  free(name);
}


----------------------------
void cmd_find_from_session(struct cmd_find_state *fs, struct session *s, int flags)
{
  cmd_find_clear_state(fs, flags);
  fs->s = s;
  fs->wl = fs->s->curw;
  fs->w = fs->wl->window;
  fs->wp = fs->w->active;
  cmd_find_log_state(__func__, fs);
}


----------------------------
struct layout_cell *layout_split_pane(struct window_pane *wp, enum layout_type type, int size, int insert_before, int full_size)
{
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  struct layout_cell *lcparent;
  unsigned int lcparent_idx = 0;
  struct layout_cell *lcnew;
  unsigned int lcnew_idx = 0;
  struct layout_cell *lc1;
  unsigned int lc1_idx = 0;
  struct layout_cell *lc2;
  unsigned int lc2_idx = 0;
  u_int sx;
  u_int sy;
  u_int xoff;
  u_int yoff;
  u_int size1;
  u_int size2;
  u_int new_size;
  u_int saved_size;
  u_int resize_first = 0;
  if (full_size)
  {
    lc_idx = wp->window->layout_root;
  }
  else
    lc_idx = wp->layout_cell;
  sx = lc->sx;
  sy = lc->sy;
  xoff = lc->xoff;
  yoff = lc->yoff;
  switch (type)
  {
    case LAYOUT_LEFTRIGHT:
    {
      if (sx < ((2 * 2) + 1))
      {
        return 0;
      }
      break;
    }

    case LAYOUT_TOPBOTTOM:
    {
      if (sy < ((2 * 2) + 1))
      {
        return 0;
      }
      break;
    }

    default:
    {
      fatalx("bad layout type");
    }

  }

  if (type == LAYOUT_LEFTRIGHT)
  {
    saved_size = sx;
  }
  else
    saved_size = sy;
  if (size < 0)
  {
    size2 = ((saved_size + 1) / 2) - 1;
  }
  else
    if (insert_before)
  {
    size2 = (saved_size - size) - 1;
  }
  else
    size2 = size;
  if (size2 < 2)
  {
    size2 = 2;
  }
  else
    if (size2 > (saved_size - 2))
  {
    size2 = saved_size - 2;
  }
  size1 = (saved_size - 1) - size2;
  if (insert_before)
  {
    new_size = size2;
  }
  else
    new_size = size1;
  if (full_size && (!layout_set_size_check(wp->window, lc, type, new_size)))
  {
    return 0;
  }
  if ((lc->parent != 0) && (lc->parent->type == type))
  {
    helper_layout_split_pane_1(&lcparent_idx, &lcnew_idx, insert_before, lc, lc_idx, lcparent, lcnew);
  }
  else
    if ((full_size && (lc->parent == 0)) && (lc->type == type))
  {
    helper_layout_split_pane_2(&size, &lcnew_idx, &sx, &sy, &resize_first, wp, insert_before, lc, lcnew, new_size, saved_size);
  }
  else
  {
    helper_layout_split_pane_3(&lcparent_idx, &lcnew_idx, wp, type, insert_before, lc, lc_idx, lcparent, lcnew, sx, sy, xoff, yoff);
  }
  if (insert_before)
  {
    lc1_idx = &lcnew[lcnew_idx];
    lc2_idx = &lc[lc_idx];
  }
  else
  {
    lc1_idx = &lc[lc_idx];
    lc2_idx = &lcnew[lcnew_idx];
  }
  if ((!resize_first) && (type == LAYOUT_LEFTRIGHT))
  {
    layout_set_size(lc1, size1, sy, xoff, yoff);
    layout_set_size(lc2, size2, sy, (xoff + lc1->sx) + 1, yoff);
  }
  else
    if ((!resize_first) && (type == LAYOUT_TOPBOTTOM))
  {
    layout_set_size(lc1, sx, size1, xoff, yoff);
    layout_set_size(lc2, sx, size2, xoff, (yoff + lc1->sy) + 1);
  }
  if (full_size)
  {
    if (!resize_first)
    {
      layout_resize_child_cells(wp->window, lc);
    }
    layout_fix_offsets(wp->window->layout_root);
  }
  else
    layout_make_leaf(lc, wp);
  return lcnew;
}


----------------------------
void server_status_session(struct session *s)
{
  struct client *c;
  unsigned int c_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (c->session == s)
    {
      server_status_client(c);
    }
  }

}


----------------------------
void layout_make_leaf(struct layout_cell *lc, struct window_pane *wp)
{
  lc->type = LAYOUT_WINDOWPANE;
  do
  {
    (&lc->cells)->tqh_first = 0;
    (&lc->cells)->tqh_last = &(&lc->cells)->tqh_first;
  }
  while (0);
  wp->layout_cell = lc;
  lc->wp = wp;
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
char *xstrdup(const char *str)
{
  char *cp;
  unsigned int cp_idx = 0;
  if ((cp_idx = strdup(str)) == 0)
  {
    fatalx("xstrdup: %s", strerror(errno));
  }
  return cp;
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
void layout_fix_panes(struct window *w, u_int wsx, u_int wsy)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  u_int sx;
  u_int sy;
  int shift;
  int status;
  int at_top;
  status = options_get_number(w->options, "pane-border-status");
  at_top = status == 1;
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    helper_layout_fix_panes_1(&lc_idx, &sx, &sy, &shift, wsx, wsy, wp, lc, status, at_top);
  }

}


----------------------------
void layout_close_pane(struct window_pane *wp)
{
  struct window *w = wp->window;
  layout_destroy_cell(w, wp->layout_cell, &w->layout_root);
  if (w->layout_root != 0)
  {
    layout_fix_offsets(w->layout_root);
    layout_fix_panes(w, w->sx, w->sy);
  }
  notify_window("window-layout-changed", w);
}


----------------------------
int areshell(const char *shell)
{
  const char *progname;
  unsigned int progname_idx = 0;
  const char *ptr;
  unsigned int ptr_idx = 0;
  if ((ptr_idx = strrchr(shell, '/')) != 0)
  {
    ptr_idx += 1;
  }
  else
    ptr_idx = shell;
  progname_idx = getprogname();
  if (progname[progname_idx] == '-')
  {
    progname_idx += 1;
  }
  if (strcmp(ptr, progname) == 0)
  {
    return 1;
  }
  return 0;
}


----------------------------
void cmdq_print(struct cmdq_item *item, const char *fmt, ...)
{
  struct client *c = item->client;
  struct window *w;
  unsigned int w_idx = 0;
  va_list ap;
  char *tmp;
  char *msg;
  unsigned int msg_idx = 0;
  __builtin_va_start(ap);
  if (c == 0)
  {
    ;
  }
  else
    if ((c->session == 0) || (c->flags & 0x2000))
  {
    if ((~c->flags) & 0x10000)
    {
      xvasprintf(&tmp, fmt, ap);
      msg_idx = utf8_sanitize(tmp);
      free(tmp);
      evbuffer_add(c->stdout_data, msg, strlen(msg));
      free(msg);
    }
    else
      evbuffer_add_vprintf(c->stdout_data, fmt, ap);
    evbuffer_add(c->stdout_data, "\n", 1);
    server_client_push_stdout(c);
  }
  else
  {
    w_idx = c->session->curw->window;
    if (w->active->mode != (&window_copy_mode))
    {
      window_pane_reset_mode(w->active);
      window_pane_set_mode(w->active, &window_copy_mode, 0, 0);
      window_copy_init_for_output(w->active);
    }
    window_copy_vadd(w->active, fmt, ap);
  }
  ;
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
void cmd_find_from_winlink_pane(struct cmd_find_state *fs, struct winlink *wl, struct window_pane *wp, int flags)
{
  cmd_find_clear_state(fs, flags);
  fs->s = wl->session;
  fs->wl = wl;
  fs->idx = fs->wl->idx;
  fs->w = fs->wl->window;
  fs->wp = wp;
  cmd_find_log_state(__func__, fs);
}


----------------------------
int xasprintf(char **ret, const char *fmt, ...)
{
  va_list ap;
  int i;
  __builtin_va_start(ap);
  i = xvasprintf(ret, fmt, ap);
  ;
  return i;
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
long long args_strtonum(struct args *args, u_char ch, long long minval, long long maxval, char **cause)
{
  const char *errstr;
  long long ll;
  struct args_entry *entry;
  unsigned int entry_idx = 0;
  if ((entry_idx = args_find(args, ch)) == 0)
  {
    *cause = xstrdup("missing");
    return 0;
  }
  ll = strtonum(entry->value, minval, maxval, &errstr);
  if (errstr != 0)
  {
    *cause = xstrdup(errstr);
    return 0;
  }
  *cause = 0;
  return ll;
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
int session_select(struct session *s, int idx)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  wl_idx = winlink_find_by_index(&s->windows, idx);
  return session_set_current(s, wl);
}


----------------------------
None
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
enum cmd_retval
{
  CMD_RETURN_ERROR = -1,
  CMD_RETURN_NORMAL = 0,
  CMD_RETURN_WAIT,
  CMD_RETURN_STOP
}
----------------------------
long long options_get_number(struct options *oo, const char *name)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_get(oo, name);
  if ((&o[o_idx]) == 0)
  {
    fatalx("missing option %s", name);
  }
  if (!((o->tableentry != 0) && ((((((o->tableentry->type == OPTIONS_TABLE_NUMBER) || (o->tableentry->type == OPTIONS_TABLE_KEY)) || (o->tableentry->type == OPTIONS_TABLE_COLOUR)) || (o->tableentry->type == OPTIONS_TABLE_ATTRIBUTES)) || (o->tableentry->type == OPTIONS_TABLE_FLAG)) || (o->tableentry->type == OPTIONS_TABLE_CHOICE))))
  {
    fatalx("option %s is not a number", name);
  }
  return o->number;
}


----------------------------
void server_redraw_session(struct session *s)
{
  struct client *c;
  unsigned int c_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (c->session == s)
    {
      server_redraw_client(c);
    }
  }

}


----------------------------
struct environ_entry *environ_find(struct environ *env, const char *name)
{
  struct environ_entry envent;
  envent.name = (char *) name;
  return environ_RB_FIND(env, &envent);
}


----------------------------
const char *options_get_string(struct options *oo, const char *name)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_get(oo, name);
  if ((&o[o_idx]) == 0)
  {
    fatalx("missing option %s", name);
  }
  if (!((o->tableentry == 0) || (o->tableentry->type == OPTIONS_TABLE_STRING)))
  {
    fatalx("option %s is not a string", name);
  }
  return o->string;
}


----------------------------
int args_has(struct args *args, u_char ch)
{
  return args_find(args, ch) != 0;
}


----------------------------
None
----------------------------
***/


