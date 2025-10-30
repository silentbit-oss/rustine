static enum cmd_retval cmd_break_pane_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct cmd_find_state *current = &item->shared->current;
  struct client *c = cmd_find_client(item, 0, 1);
  struct winlink *wl = item->source.wl;
  unsigned int wl_idx = 0;
  struct session *src_s = item->source.s;
  struct session *dst_s = item->target.s;
  struct window_pane *wp = item->source.wp;
  struct window *w = wl->window;
  unsigned int w_idx = 0;
  char *name;
  unsigned int name_idx = 0;
  char *cause;
  int idx = item->target.idx;
  const char *template;
  unsigned int template_idx = 0;
  char *cp;
  unsigned int cp_idx = 0;
  if ((idx != (-1)) && (winlink_find_by_index(&dst_s->windows, idx) != 0))
  {
    cmdq_error(item, "index %d already in use", idx);
    return CMD_RETURN_ERROR;
  }
  if (window_count_panes(w) == 1)
  {
    cmdq_error(item, "can't break with only one pane");
    return CMD_RETURN_ERROR;
  }
  server_unzoom_window(w);
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
  window_lost_pane(w, wp);
  layout_close_pane(wp);
  w_idx = (wp->window = window_create(dst_s->sx, dst_s->sy));
  do
  {
    if ((wp->entry.tqe_next = (&w->panes)->tqh_first) != 0)
    {
      (&w->panes)->tqh_first->entry.tqe_prev = &wp->entry.tqe_next;
    }
    else
      (&w->panes)->tqh_last = &wp->entry.tqe_next;
    (&w->panes)->tqh_first = wp;
    wp->entry.tqe_prev = &(&w->panes)->tqh_first;
  }
  while (0);
  w->active = wp;
  if (!args_has(args, 'n'))
  {
    name_idx = default_window_name(w);
    window_set_name(w, name);
    free(name);
  }
  else
  {
    window_set_name(w, args_get(args, 'n'));
    options_set_number(w->options, "automatic-rename", 0);
  }
  layout_init(w, wp);
  wp->flags |= 0x80;
  if (idx == (-1))
  {
    idx = (-1) - options_get_number(dst_s->options, "base-index");
  }
  wl_idx = session_attach(dst_s, w, idx, &cause);
  if (!args_has(self->args, 'd'))
  {
    session_select(dst_s, wl->idx);
    cmd_find_from_session(current, dst_s, 0);
  }
  server_redraw_session(src_s);
  if (src_s != dst_s)
  {
    server_redraw_session(dst_s);
  }
  server_status_session_group(src_s);
  if (src_s != dst_s)
  {
    server_status_session_group(dst_s);
  }
  if (args_has(args, 'P'))
  {
    if ((template_idx = args_get(args, 'F')) == 0)
    {
      template_idx = "#{session_name}:#{window_index}.#{pane_index}";
    }
    cp_idx = format_single(item, template, c, dst_s, wl, wp);
    cmdq_print(item, "%s", cp);
    free(cp);
  }
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
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


----------------------------
void server_unzoom_window(struct window *w)
{
  if (window_unzoom(w) == 0)
  {
    server_redraw_window(w);
  }
}


----------------------------
struct winlink *session_attach(struct session *s, struct window *w, int idx, char **cause)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  if ((wl_idx = winlink_add(&s->windows, idx)) == 0)
  {
    xasprintf(cause, "index in use: %d", idx);
    return 0;
  }
  wl->session = s;
  winlink_set_window(wl, w);
  notify_session_window("window-linked", s, w);
  session_group_synchronize_from(s);
  return wl;
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
struct windows
{
  struct window *rbh_root;
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


----------------------------
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


----------------------------
void window_set_name(struct window *w, const char *new_name)
{
  free(w->name);
  utf8_stravis(&w->name, new_name, ((0x01 | 0x02) | 0x08) | 0x10);
  notify_window("window-renamed", w);
}


----------------------------
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
int session_select(struct session *s, int idx)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  wl_idx = winlink_find_by_index(&s->windows, idx);
  return session_set_current(s, wl);
}


----------------------------
struct options_entry *options_set_number(struct options *oo, const char *name, long long value)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  if ((*name) == '@')
  {
    fatalx("user option %s must be a string", name);
  }
  o_idx = options_get_only(oo, name);
  if ((&o[o_idx]) == 0)
  {
    o_idx = options_default(oo, options_parent_table_entry(oo, name));
    if ((&o[o_idx]) == 0)
    {
      return 0;
    }
  }
  if (!((o->tableentry != 0) && ((((((o->tableentry->type == OPTIONS_TABLE_NUMBER) || (o->tableentry->type == OPTIONS_TABLE_KEY)) || (o->tableentry->type == OPTIONS_TABLE_COLOUR)) || (o->tableentry->type == OPTIONS_TABLE_ATTRIBUTES)) || (o->tableentry->type == OPTIONS_TABLE_FLAG)) || (o->tableentry->type == OPTIONS_TABLE_CHOICE))))
  {
    fatalx("option %s is not a number", name);
  }
  o->number = value;
  return o;
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
void server_status_session_group(struct session *s)
{
  unsigned int s_idx = 0;
  struct session_group *sg;
  unsigned int sg_idx = 0;
  if ((sg_idx = session_group_contains(s)) == 0)
  {
    server_status_session(s);
  }
  else
  {
    for (s_idx = (&sg->sessions)->tqh_first; (&s[s_idx]) != 0; s_idx = s_idx->gentry.tqe_next)
    {
      server_status_session(s);
    }

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
int args_has(struct args *args, u_char ch)
{
  return args_find(args, ch) != 0;
}


----------------------------
None
----------------------------
***/


