// hint:  ['lastwp_idx_ref is a mutable refrence to unsigned int', 'markedwp_idx_ref is a mutable refrence to unsigned int']
enum cmd_retval helper_cmd_select_pane_exec_1(unsigned int * const lastwp_idx_ref, unsigned int * const markedwp_idx_ref, struct args * const args, struct winlink * const wl, struct session * const s, struct window_pane * const wp, struct window_pane * const lastwp, struct window_pane * const markedwp)
{
  unsigned int lastwp_idx = *lastwp_idx_ref;
  unsigned int markedwp_idx = *markedwp_idx_ref;
  if (args_has(args, 'm') && (!window_pane_visible(wp)))
  {
    return CMD_RETURN_NORMAL;
  }
  lastwp_idx = marked_pane.wp;
  if (args_has(args, 'M') || server_is_marked(s, wl, wp))
  {
    server_clear_marked();
  }
  else
    server_set_marked(s, wl, wp);
  markedwp_idx = marked_pane.wp;
  if ((&lastwp[lastwp_idx]) != 0)
  {
    server_redraw_window_borders(lastwp->window);
    server_status_window(lastwp->window);
  }
  if ((&markedwp[markedwp_idx]) != 0)
  {
    server_redraw_window_borders(markedwp->window);
    server_status_window(markedwp->window);
  }
  return CMD_RETURN_NORMAL;
  *lastwp_idx_ref = lastwp_idx;
  *markedwp_idx_ref = markedwp_idx;
}


/*** DEPENDENCIES:
extern struct cmd_find_state marked_pane
----------------------------
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
int server_is_marked(struct session *s, struct winlink *wl, struct window_pane *wp)
{
  if (((s == 0) || (wl == 0)) || (wp == 0))
  {
    return 0;
  }
  if ((marked_pane.s != s) || (marked_pane.wl != wl))
  {
    return 0;
  }
  if (marked_pane.wp != wp)
  {
    return 0;
  }
  return server_check_marked();
}


----------------------------
void server_set_marked(struct session *s, struct winlink *wl, struct window_pane *wp)
{
  cmd_find_clear_state(&marked_pane, 0);
  marked_pane.s = s;
  marked_pane.wl = wl;
  marked_pane.w = wl->window;
  marked_pane.wp = wp;
}


----------------------------
void server_clear_marked(void)
{
  cmd_find_clear_state(&marked_pane, 0);
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
void server_redraw_window_borders(struct window *w)
{
  struct client *c;
  unsigned int c_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if ((c->session != 0) && (c->session->curw->window == w))
    {
      c->flags |= 0x400;
    }
  }

}


----------------------------
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


----------------------------
None
----------------------------
int args_has(struct args *args, u_char ch)
{
  return args_find(args, ch) != 0;
}


----------------------------
None
----------------------------
***/


// hint:  ['lastwp_idx_ref is a mutable refrence to unsigned int']
enum cmd_retval helper_cmd_select_pane_exec_2(unsigned int * const lastwp_idx_ref, struct cmd * const self, struct cmdq_item * const item, struct cmd_find_state * const current, struct winlink * const wl, struct window * const w, struct window_pane * const lastwp)
{
  unsigned int lastwp_idx = *lastwp_idx_ref;
  lastwp_idx = w->last;
  if ((&lastwp[lastwp_idx]) == 0)
  {
    cmdq_error(item, "no last pane");
    return CMD_RETURN_ERROR;
  }
  if (args_has(self->args, 'e'))
  {
    lastwp->flags &= ~0x40;
  }
  else
    if (args_has(self->args, 'd'))
  {
    lastwp->flags |= 0x40;
  }
  else
  {
    server_unzoom_window(w);
    window_redraw_active_switch(w, lastwp);
    if (window_set_active_pane(w, lastwp))
    {
      cmd_find_from_winlink(current, wl, 0);
      server_status_window(w);
      server_redraw_window_borders(w);
    }
  }
  return CMD_RETURN_NORMAL;
  *lastwp_idx_ref = lastwp_idx;
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
int args_has(struct args *args, u_char ch)
{
  return args_find(args, ch) != 0;
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


----------------------------
void cmd_find_from_winlink(struct cmd_find_state *fs, struct winlink *wl, int flags)
{
  cmd_find_clear_state(fs, flags);
  fs->s = wl->session;
  fs->wl = wl;
  fs->w = wl->window;
  fs->wp = wl->window->active;
  cmd_find_log_state(__func__, fs);
}


----------------------------
void server_redraw_window_borders(struct window *w)
{
  struct client *c;
  unsigned int c_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if ((c->session != 0) && (c->session->curw->window == w))
    {
      c->flags |= 0x400;
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


static enum cmd_retval cmd_select_pane_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct cmd_find_state *current = &item->shared->current;
  struct client *c = cmd_find_client(item, 0, 1);
  struct winlink *wl = item->target.wl;
  struct window *w = wl->window;
  struct session *s = item->target.s;
  struct window_pane *wp = item->target.wp;
  unsigned int wp_idx = 0;
  struct window_pane *lastwp;
  unsigned int lastwp_idx = 0;
  struct window_pane *markedwp;
  unsigned int markedwp_idx = 0;
  char *pane_title;
  unsigned int pane_title_idx = 0;
  const char *style;
  unsigned int style_idx = 0;
  if ((self->entry == (&cmd_last_pane_entry)) || args_has(args, 'l'))
  {
    helper_cmd_select_pane_exec_2(&lastwp_idx, self, item, current, wl, w, lastwp);
  }
  if (args_has(args, 'm') || args_has(args, 'M'))
  {
    helper_cmd_select_pane_exec_1(&lastwp_idx, &markedwp_idx, args, wl, s, wp, lastwp, markedwp);
  }
  if (args_has(self->args, 'P') || args_has(self->args, 'g'))
  {
    if (args_has(args, 'P'))
    {
      style_idx = args_get(args, 'P');
      if (style_parse(&grid_default_cell, &wp->colgc, style) == (-1))
      {
        cmdq_error(item, "bad style: %s", style);
        return CMD_RETURN_ERROR;
      }
      wp->flags |= 0x1;
    }
    if (args_has(self->args, 'g'))
    {
      cmdq_print(item, "%s", style_tostring(&wp->colgc));
    }
    return CMD_RETURN_NORMAL;
  }
  if (args_has(self->args, 'L'))
  {
    server_unzoom_window(wp->window);
    wp_idx = window_pane_find_left(wp_idx);
  }
  else
    if (args_has(self->args, 'R'))
  {
    server_unzoom_window(wp->window);
    wp_idx = window_pane_find_right(wp_idx);
  }
  else
    if (args_has(self->args, 'U'))
  {
    server_unzoom_window(wp->window);
    wp_idx = window_pane_find_up(wp_idx);
  }
  else
    if (args_has(self->args, 'D'))
  {
    server_unzoom_window(wp->window);
    wp_idx = window_pane_find_down(wp_idx);
  }
  if ((&wp[wp_idx]) == 0)
  {
    return CMD_RETURN_NORMAL;
  }
  if (args_has(self->args, 'e'))
  {
    wp->flags &= ~0x40;
    return CMD_RETURN_NORMAL;
  }
  if (args_has(self->args, 'd'))
  {
    wp->flags |= 0x40;
    return CMD_RETURN_NORMAL;
  }
  if (args_has(self->args, 'T'))
  {
    pane_title_idx = format_single(item, args_get(self->args, 'T'), c, s, wl, wp);
    screen_set_title(&wp->base, pane_title);
    server_status_window(wp->window);
    free(pane_title);
  }
  if ((&wp[wp_idx]) == w->active)
  {
    return CMD_RETURN_NORMAL;
  }
  server_unzoom_window(wp->window);
  if (!window_pane_visible(wp))
  {
    cmdq_error(item, "pane not visible");
    return CMD_RETURN_ERROR;
  }
  window_redraw_active_switch(w, wp);
  if (window_set_active_pane(w, wp))
  {
    cmd_find_from_winlink_pane(current, wl, wp, 0);
    hooks_insert(s->hooks, item, current, "after-select-pane");
    server_status_window(w);
    server_redraw_window_borders(w);
  }
  return CMD_RETURN_NORMAL;
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


----------------------------
enum cmd_retval helper_cmd_select_pane_exec_1(unsigned int * const lastwp_idx_ref, unsigned int * const markedwp_idx_ref, struct args * const args, struct winlink * const wl, struct session * const s, struct window_pane * const wp, struct window_pane * const lastwp, struct window_pane * const markedwp)
{
  unsigned int lastwp_idx = *lastwp_idx_ref;
  unsigned int markedwp_idx = *markedwp_idx_ref;
  if (args_has(args, 'm') && (!window_pane_visible(wp)))
  {
    return CMD_RETURN_NORMAL;
  }
  lastwp_idx = marked_pane.wp;
  if (args_has(args, 'M') || server_is_marked(s, wl, wp))
  {
    server_clear_marked();
  }
  else
    server_set_marked(s, wl, wp);
  markedwp_idx = marked_pane.wp;
  if ((&lastwp[lastwp_idx]) != 0)
  {
    server_redraw_window_borders(lastwp->window);
    server_status_window(lastwp->window);
  }
  if ((&markedwp[markedwp_idx]) != 0)
  {
    server_redraw_window_borders(markedwp->window);
    server_status_window(markedwp->window);
  }
  return CMD_RETURN_NORMAL;
  *lastwp_idx_ref = lastwp_idx;
  *markedwp_idx_ref = markedwp_idx;
}


----------------------------
enum cmd_retval helper_cmd_select_pane_exec_2(unsigned int * const lastwp_idx_ref, struct cmd * const self, struct cmdq_item * const item, struct cmd_find_state * const current, struct winlink * const wl, struct window * const w, struct window_pane * const lastwp)
{
  unsigned int lastwp_idx = *lastwp_idx_ref;
  lastwp_idx = w->last;
  if ((&lastwp[lastwp_idx]) == 0)
  {
    cmdq_error(item, "no last pane");
    return CMD_RETURN_ERROR;
  }
  if (args_has(self->args, 'e'))
  {
    lastwp->flags &= ~0x40;
  }
  else
    if (args_has(self->args, 'd'))
  {
    lastwp->flags |= 0x40;
  }
  else
  {
    server_unzoom_window(w);
    window_redraw_active_switch(w, lastwp);
    if (window_set_active_pane(w, lastwp))
    {
      cmd_find_from_winlink(current, wl, 0);
      server_status_window(w);
      server_redraw_window_borders(w);
    }
  }
  return CMD_RETURN_NORMAL;
  *lastwp_idx_ref = lastwp_idx;
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


----------------------------
int style_parse(const struct grid_cell *defgc, struct grid_cell *gc, const char *in)
{
  unsigned int in_idx = 0;
  struct grid_cell savedgc;
  const char delimiters[] = " ,";
  char tmp[32];
  int val;
  int fg;
  int bg;
  int attr;
  int flags;
  size_t end;
  if (in[in_idx] == '\0')
  {
    return 0;
  }
  if (strchr(delimiters, in[(strlen(in) - 1) + in_idx]) != 0)
  {
    return -1;
  }
  memcpy(&savedgc, gc, sizeof(savedgc));
  fg = gc->fg;
  bg = gc->bg;
  attr = gc->attr;
  flags = gc->flags;
  do
  {
    helper_style_parse_1(&in_idx, &val, &fg, &bg, &attr, &flags, &end, defgc, in, delimiters, tmp);
  }
  while (in[in_idx] != '\0');
  gc->fg = fg;
  gc->bg = bg;
  gc->attr = attr;
  gc->flags = flags;
  return 0;
  error:
  memcpy(gc, &savedgc, sizeof(*gc));

  return -1;
}


----------------------------
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
extern const struct grid_cell grid_default_cell
----------------------------
extern const struct cmd_entry cmd_last_pane_entry
----------------------------
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
const char *style_tostring(struct grid_cell *gc)
{
  int off = 0;
  int comma = 0;
  static char s[256];
  *s = '\0';
  if (gc->fg != 8)
  {
    off += xsnprintf(s, sizeof(s), "fg=%s", colour_tostring(gc->fg));
    comma = 1;
  }
  if (gc->bg != 8)
  {
    off += xsnprintf(s + off, (sizeof(s)) - off, "%sbg=%s", (comma) ? (",") : (""), colour_tostring(gc->bg));
    comma = 1;
  }
  if ((gc->attr != 0) && (gc->attr != 0x80))
  {
    xsnprintf(s + off, (sizeof(s)) - off, "%s%s", (comma) ? (",") : (""), attributes_tostring(gc->attr));
  }
  if ((*s) == '\0')
  {
    return "default";
  }
  return s;
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


----------------------------
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


----------------------------
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


----------------------------
void screen_set_title(struct screen *s, const char *title)
{
  free(s->title);
  utf8_stravis(&s->title, title, ((0x01 | 0x02) | 0x08) | 0x10);
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
void server_redraw_window_borders(struct window *w)
{
  struct client *c;
  unsigned int c_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if ((c->session != 0) && (c->session->curw->window == w))
    {
      c->flags |= 0x400;
    }
  }

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


