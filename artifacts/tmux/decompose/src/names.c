char *parse_window_name(const char *in)
{
  char *copy;
  char *name;
  unsigned int name_idx = 0;
  char *ptr;
  unsigned int ptr_idx = 0;
  name_idx = (copy = xstrdup(in));
  if (strncmp(name, "exec ", (sizeof("exec ")) - 1) == 0)
  {
    name_idx = (name_idx + (sizeof("exec "))) - 1;
  }
  while ((name[name_idx] == ' ') || (name[name_idx] == '-'))
  {
    name_idx += 1;
  }

  if ((ptr_idx = strchr(name, ' ')) != 0)
  {
    ptr[ptr_idx] = '\0';
  }
  if (name[name_idx] != '\0')
  {
    ptr_idx = ((&name[name_idx]) + strlen(name)) - 1;
    while ((((&ptr[ptr_idx]) > (&name[name_idx])) && (!isalnum((u_char) (*(&ptr[ptr_idx]))))) && (!ispunct((u_char) (*(&ptr[ptr_idx])))))
    {
      ptr[ptr_idx] = '\0';
      ptr_idx -= 1;
    }

  }
  if (name[name_idx] == '/')
  {
    name_idx = basename(name_idx);
  }
  name_idx = xstrdup(name_idx);
  free(copy);
  return name;
}


/*** DEPENDENCIES:
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
***/


static int name_time_expired(struct window *w, struct timeval *tv)
{
  struct timeval offset;
  do
  {
    (&offset)->tv_sec = tv->tv_sec - (&w->name_time)->tv_sec;
    (&offset)->tv_usec = tv->tv_usec - (&w->name_time)->tv_usec;
    if ((&offset)->tv_usec < 0)
    {
      (&offset)->tv_sec -= 1;
      (&offset)->tv_usec += 1000000;
    }
  }
  while (0);
  if ((offset.tv_sec != 0) || (offset.tv_usec > 500000))
  {
    return 0;
  }
  return 500000 - offset.tv_usec;
}


/*** DEPENDENCIES:
None
----------------------------
***/


static void name_time_callback(int fd, short events, void *arg)
{
  struct window *w = arg;
  log_debug("@%u name timer expired", w->id);
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
None
----------------------------
***/


static char *format_window_name(struct window *w)
{
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  const char *fmt;
  unsigned int fmt_idx = 0;
  char *name;
  unsigned int name_idx = 0;
  ft_idx = format_create(0, 0, 0x40000000U | w->id, 0);
  format_defaults_window(ft, w);
  format_defaults_pane(ft, w->active);
  fmt_idx = options_get_string(w->options, "automatic-rename-format");
  name_idx = format_expand(ft, fmt);
  format_free(ft);
  return name;
}


/*** DEPENDENCIES:
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
void format_defaults_window(struct format_tree *ft, struct window *w)
{
  ft->w = w;
  format_add_tv(ft, "window_activity", &w->activity_time);
  format_add(ft, "window_id", "@%u", w->id);
  format_add(ft, "window_name", "%s", w->name);
  format_add(ft, "window_width", "%u", w->sx);
  format_add(ft, "window_height", "%u", w->sy);
  format_add_cb(ft, "window_layout", format_cb_window_layout);
  format_add_cb(ft, "window_visible_layout", format_cb_window_visible_layout);
  format_add(ft, "window_panes", "%u", window_count_panes(w));
  format_add(ft, "window_zoomed_flag", "%d", !(!(w->flags & 0x1000)));
}


----------------------------
void format_defaults_pane(struct format_tree *ft, struct window_pane *wp)
{
  struct grid *gd = wp->base.grid;
  int status = wp->status;
  u_int idx;
  if (ft->w == 0)
  {
    ft->w = wp->window;
  }
  ft->wp = wp;
  format_add(ft, "history_size", "%u", gd->hsize);
  format_add(ft, "history_limit", "%u", gd->hlimit);
  format_add_cb(ft, "history_bytes", format_cb_history_bytes);
  if (window_pane_index(wp, &idx) != 0)
  {
    fatalx("index not found");
  }
  format_add(ft, "pane_index", "%u", idx);
  format_add(ft, "pane_width", "%u", wp->sx);
  format_add(ft, "pane_height", "%u", wp->sy);
  format_add(ft, "pane_title", "%s", wp->base.title);
  format_add(ft, "pane_id", "%%%u", wp->id);
  format_add(ft, "pane_active", "%d", wp == wp->window->active);
  format_add(ft, "pane_input_off", "%d", !(!(wp->flags & 0x40)));
  format_add(ft, "pane_pipe", "%d", wp->pipe_fd != (-1));
  if ((wp->flags & 0x200) && WIFEXITED(status))
  {
    format_add(ft, "pane_dead_status", "%d", WEXITSTATUS(status));
  }
  format_add(ft, "pane_dead", "%d", wp->fd == (-1));
  if (window_pane_visible(wp))
  {
    format_add(ft, "pane_left", "%u", wp->xoff);
    format_add(ft, "pane_top", "%u", wp->yoff);
    format_add(ft, "pane_right", "%u", (wp->xoff + wp->sx) - 1);
    format_add(ft, "pane_bottom", "%u", (wp->yoff + wp->sy) - 1);
    format_add(ft, "pane_at_left", "%d", wp->xoff == 0);
    format_add(ft, "pane_at_top", "%d", wp->yoff == 0);
    format_add(ft, "pane_at_right", "%d", (wp->xoff + wp->sx) == wp->window->sx);
    format_add(ft, "pane_at_bottom", "%d", (wp->yoff + wp->sy) == wp->window->sy);
  }
  format_add(ft, "pane_in_mode", "%d", wp->screen != (&wp->base));
  if (wp->mode != 0)
  {
    format_add(ft, "pane_mode", "%s", wp->mode->name);
  }
  format_add(ft, "pane_synchronized", "%d", !(!options_get_number(wp->window->options, "synchronize-panes")));
  if (wp->searchstr != 0)
  {
    format_add(ft, "pane_search_string", "%s", wp->searchstr);
  }
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
  format_add(ft, "alternate_on", "%d", (wp->saved_grid) ? (1) : (0));
  format_add(ft, "alternate_saved_x", "%u", wp->saved_cx);
  format_add(ft, "alternate_saved_y", "%u", wp->saved_cy);
  format_add(ft, "cursor_flag", "%d", !(!(wp->base.mode & 0x1)));
  format_add(ft, "insert_flag", "%d", !(!(wp->base.mode & 0x2)));
  format_add(ft, "keypad_cursor_flag", "%d", !(!(wp->base.mode & 0x4)));
  format_add(ft, "keypad_flag", "%d", !(!(wp->base.mode & 0x8)));
  format_add(ft, "wrap_flag", "%d", !(!(wp->base.mode & 0x10)));
  format_add(ft, "mouse_any_flag", "%d", !(!(wp->base.mode & ((0x20 | 0x40) | 0x1000))));
  format_add(ft, "mouse_standard_flag", "%d", !(!(wp->base.mode & 0x20)));
  format_add(ft, "mouse_button_flag", "%d", !(!(wp->base.mode & 0x40)));
  format_add(ft, "mouse_all_flag", "%d", !(!(wp->base.mode & 0x1000)));
  format_add_cb(ft, "pane_tabs", format_cb_pane_tabs);
}


----------------------------
None
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
None
----------------------------
***/


void check_window_name(struct window *w)
{
  struct timeval tv;
  struct timeval next;
  char *name;
  unsigned int name_idx = 0;
  int left;
  if (w->active == 0)
  {
    return;
  }
  if (!options_get_number(w->options, "automatic-rename"))
  {
    return;
  }
  if ((~w->active->flags) & 0x80)
  {
    log_debug("@%u active pane not changed", w->id);
    return;
  }
  log_debug("@%u active pane changed", w->id);
  gettimeofday(&tv, 0);
  left = name_time_expired(w, &tv);
  if (left != 0)
  {
    if (!event_initialized(&w->name_event))
    {
      evtimer_set(&w->name_event, name_time_callback, w);
    }
    if (!evtimer_pending(&w->name_event, 0))
    {
      log_debug("@%u name timer queued (%d left)", w->id, left);
      timerclear(&next);
      next.tv_usec = left;
      event_add(&w->name_event, &next);
    }
    else
    {
      log_debug("@%u name timer already queued (%d left)", w->id, left);
    }
    return;
  }
  memcpy(&w->name_time, &tv, sizeof(w->name_time));
  if (event_initialized(&w->name_event))
  {
    evtimer_del(&w->name_event);
  }
  w->active->flags &= ~0x80;
  name_idx = format_window_name(w);
  if (strcmp(name, w->name) != 0)
  {
    log_debug("@%u new name %s (was %s)", w->id, name, w->name);
    window_set_name(w, name);
    server_status_window(w);
  }
  else
    log_debug("@%u name not changed (still %s)", w->id, w->name);
  free(name);
}


/*** DEPENDENCIES:
void server_status_window(struct window *w)
{
  struct session *s;
  unsigned int s_idx = 0;
  for (s_idx = sessions_RB_MINMAX(&sessions, -1); (&s[s_idx]) != 0; s_idx = sessions_RB_NEXT(s_idx))
  {
    if (session_has(s, w))
    {
      server_status_session(s);
    }
  }

}


----------------------------
static void name_time_callback(int fd, short events, void *arg)
{
  struct window *w = arg;
  log_debug("@%u name timer expired", w->id);
}


----------------------------
void window_set_name(struct window *w, const char *new_name)
{
  free(w->name);
  utf8_stravis(&w->name, new_name, ((0x01 | 0x02) | 0x08) | 0x10);
  notify_window("window-renamed", w);
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
static int name_time_expired(struct window *w, struct timeval *tv)
{
  struct timeval offset;
  do
  {
    (&offset)->tv_sec = tv->tv_sec - (&w->name_time)->tv_sec;
    (&offset)->tv_usec = tv->tv_usec - (&w->name_time)->tv_usec;
    if ((&offset)->tv_usec < 0)
    {
      (&offset)->tv_sec -= 1;
      (&offset)->tv_usec += 1000000;
    }
  }
  while (0);
  if ((offset.tv_sec != 0) || (offset.tv_usec > 500000))
  {
    return 0;
  }
  return 500000 - offset.tv_usec;
}


----------------------------
static char *format_window_name(struct window *w)
{
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  const char *fmt;
  unsigned int fmt_idx = 0;
  char *name;
  unsigned int name_idx = 0;
  ft_idx = format_create(0, 0, 0x40000000U | w->id, 0);
  format_defaults_window(ft, w);
  format_defaults_pane(ft, w->active);
  fmt_idx = options_get_string(w->options, "automatic-rename-format");
  name_idx = format_expand(ft, fmt);
  format_free(ft);
  return name;
}


----------------------------
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
None
----------------------------
***/


char *default_window_name(struct window *w)
{
  char *cmd;
  unsigned int cmd_idx = 0;
  char *s;
  unsigned int s_idx = 0;
  cmd_idx = cmd_stringify_argv(w->active->argc, w->active->argv);
  if (((&cmd[cmd_idx]) != 0) && (cmd[cmd_idx] != '\0'))
  {
    s_idx = parse_window_name(cmd);
  }
  else
    s_idx = parse_window_name(w->active->shell);
  free(cmd);
  return s;
}


/*** DEPENDENCIES:
char *parse_window_name(const char *in)
{
  char *copy;
  char *name;
  unsigned int name_idx = 0;
  char *ptr;
  unsigned int ptr_idx = 0;
  name_idx = (copy = xstrdup(in));
  if (strncmp(name, "exec ", (sizeof("exec ")) - 1) == 0)
  {
    name_idx = (name_idx + (sizeof("exec "))) - 1;
  }
  while ((name[name_idx] == ' ') || (name[name_idx] == '-'))
  {
    name_idx += 1;
  }

  if ((ptr_idx = strchr(name, ' ')) != 0)
  {
    ptr[ptr_idx] = '\0';
  }
  if (name[name_idx] != '\0')
  {
    ptr_idx = ((&name[name_idx]) + strlen(name)) - 1;
    while ((((&ptr[ptr_idx]) > (&name[name_idx])) && (!isalnum((u_char) (*(&ptr[ptr_idx]))))) && (!ispunct((u_char) (*(&ptr[ptr_idx])))))
    {
      ptr[ptr_idx] = '\0';
      ptr_idx -= 1;
    }

  }
  if (name[name_idx] == '/')
  {
    name_idx = basename(name_idx);
  }
  name_idx = xstrdup(name_idx);
  free(copy);
  return name;
}


----------------------------
char *cmd_stringify_argv(int argc, char **argv)
{
  char *buf;
  unsigned int buf_idx = 0;
  int i;
  size_t len;
  if (argc == 0)
  {
    return xstrdup("");
  }
  len = 0;
  buf_idx = 0;
  for (i = 0; i < argc; i += 1)
  {
    len += strlen(argv[i]) + 1;
    buf_idx = xrealloc(buf_idx, len);
    if (i == 0)
    {
      buf[buf_idx] = '\0';
    }
    else
      strlcat(buf, " ", len);
    strlcat(buf, argv[i], len);
  }

  return buf;
}


----------------------------
None
----------------------------
***/


