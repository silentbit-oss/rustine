// element in merge of:  window_remove_ref,notify_add,window_pane_destroy,notify_callback,window_destroy_panes,window_destroy,notify_pane,window_pane_reset_mode
void window_remove_ref(struct window *w, const char *from)
{
  w->references -= 1;
  log_debug("%s: @%u %s, now %d", __func__, w->id, from, w->references);
  if (w->references == 0)
  {
    window_destroy(w);
  }
}


/*** DEPENDENCIES:
None
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


// element in merge of:  window_remove_ref,notify_add,window_pane_destroy,notify_callback,window_destroy_panes,window_destroy,notify_pane,window_pane_reset_mode
static void notify_add(const char *name, struct cmd_find_state *fs, struct client *c, struct session *s, struct window *w, struct window_pane *wp)
{
  struct notify_entry *ne;
  unsigned int ne_idx = 0;
  struct cmdq_item *new_item;
  unsigned int new_item_idx = 0;
  ne_idx = xcalloc(1, sizeof(*ne_idx));
  ne->name = xstrdup(name);
  ne->client = c;
  ne->session = s;
  ne->window = w;
  if (wp != 0)
  {
    ne->pane = wp->id;
  }
  else
    ne->pane = -1;
  if (c != 0)
  {
    c->references += 1;
  }
  if (s != 0)
  {
    session_add_ref(s, __func__);
  }
  if (w != 0)
  {
    window_add_ref(w, __func__);
  }
  cmd_find_copy_state(&ne->fs, fs);
  if (ne->fs.s != 0)
  {
    session_add_ref(ne->fs.s, __func__);
  }
  new_item_idx = cmdq_get_callback1("notify_callback", notify_callback, ne);
  cmdq_append(0, new_item);
}


/*** DEPENDENCIES:
None
----------------------------
void *xcalloc(size_t nmemb, size_t size)
{
  void *ptr;
  unsigned int ptr_idx = 0;
  if ((size == 0) || (nmemb == 0))
  {
    fatalx("xcalloc: zero size");
  }
  ptr_idx = calloc(nmemb, size);
  if ((&ptr[ptr_idx]) == 0)
  {
    fatalx("xcalloc: allocating %zu * %zu bytes: %s", nmemb, size, strerror(errno));
  }
  return ptr;
}


----------------------------
void cmdq_append(struct client *c, struct cmdq_item *item)
{
  unsigned int item_idx = 0;
  struct cmdq_list *queue = cmdq_get(c);
  struct cmdq_item *next;
  unsigned int next_idx = 0;
  do
  {
    next_idx = item->next_idx;
    item->next = 0;
    if (c != 0)
    {
      c->references += 1;
    }
    item->client = c;
    item->queue = queue;
    do
    {
      item->entry.tqe_next = 0;
      item->entry.tqe_prev = queue->tqh_last;
      *queue->tqh_last = &item[item_idx];
      queue->tqh_last = &item->entry.tqe_next;
    }
    while (0);
    item_idx = &next[next_idx];
  }
  while ((&item[item_idx]) != 0);
}


----------------------------
void session_add_ref(struct session *s, const char *from)
{
  s->references += 1;
  log_debug("%s: %s %s, now %d", __func__, s->name, from, s->references);
}


----------------------------
void cmd_find_copy_state(struct cmd_find_state *dst, struct cmd_find_state *src)
{
  dst->s = src->s;
  dst->wl = src->wl;
  dst->idx = src->idx;
  dst->w = src->w;
  dst->wp = src->wp;
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
struct cmdq_item *cmdq_get_callback1(const char *name, cmdq_cb cb, void *data)
{
  struct cmdq_item *item;
  unsigned int item_idx = 0;
  char *tmp;
  xasprintf(&tmp, "callback[%s]", name);
  item_idx = xcalloc(1, sizeof(*item_idx));
  item->name = tmp;
  item->type = CMDQ_CALLBACK;
  item->group = 0;
  item->flags = 0;
  item->cb = cb;
  item->data = data;
  return item;
}


----------------------------
void window_add_ref(struct window *w, const char *from)
{
  w->references += 1;
  log_debug("%s: @%u %s, now %d", __func__, w->id, from, w->references);
}


----------------------------
struct notify_entry
{
  const char *name;
  struct client *client;
  struct session *session;
  struct window *window;
  int pane;
  struct cmd_find_state fs;
}
----------------------------
None
----------------------------
***/


// element in merge of:  window_remove_ref,notify_add,window_pane_destroy,notify_callback,window_destroy_panes,window_destroy,notify_pane,window_pane_reset_mode
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


/*** DEPENDENCIES:
None
----------------------------
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


----------------------------
void cmd_free_argv(int argc, char **argv)
{
  int i;
  if (argc == 0)
  {
    return;
  }
  for (i = 0; i < argc; i += 1)
  {
    free(argv[i]);
  }

  free(argv);
}


----------------------------
void grid_destroy(struct grid *gd)
{
  grid_free_lines(gd, 0, gd->hsize + gd->sy);
  free(gd->linedata);
  free(gd);
}


----------------------------
void screen_free(struct screen *s)
{
  free(s->tabs);
  free(s->title);
  free(s->ccolour);
  grid_destroy(s->grid);
  screen_free_titles(s);
}


----------------------------
void input_free(struct window_pane *wp)
{
  struct input_ctx *ictx = wp->ictx;
  u_int i;
  for (i = 0; i < ictx->param_list_len; i += 1)
  {
    if (ictx->param_list[i].type == INPUT_STRING)
    {
      free(ictx->param_list[i].str);
    }
  }

  event_del(&ictx->timer);
  free(ictx->input_buf);
  evbuffer_free(ictx->since_ground);
  free(ictx);
  wp->ictx = 0;
}


----------------------------
extern struct window_pane_tree all_window_panes
----------------------------
None
----------------------------
***/


// element in merge of:  window_remove_ref,notify_add,window_pane_destroy,notify_callback,window_destroy_panes,window_destroy,notify_pane,window_pane_reset_mode
static enum cmd_retval notify_callback(struct cmdq_item *item, void *data)
{
  struct notify_entry *ne = data;
  log_debug("%s: %s", __func__, ne->name);
  if (strcmp(ne->name, "pane-mode-changed") == 0)
  {
    control_notify_pane_mode_changed(ne->pane);
  }
  if (strcmp(ne->name, "window-layout-changed") == 0)
  {
    control_notify_window_layout_changed(ne->window);
  }
  if (strcmp(ne->name, "window-pane-changed") == 0)
  {
    control_notify_window_pane_changed(ne->window);
  }
  if (strcmp(ne->name, "window-unlinked") == 0)
  {
    control_notify_window_unlinked(ne->session, ne->window);
  }
  if (strcmp(ne->name, "window-linked") == 0)
  {
    control_notify_window_linked(ne->session, ne->window);
  }
  if (strcmp(ne->name, "window-renamed") == 0)
  {
    control_notify_window_renamed(ne->window);
  }
  if (strcmp(ne->name, "client-session-changed") == 0)
  {
    control_notify_client_session_changed(ne->client);
  }
  if (strcmp(ne->name, "session-renamed") == 0)
  {
    control_notify_session_renamed(ne->session);
  }
  if (strcmp(ne->name, "session-created") == 0)
  {
    control_notify_session_created(ne->session);
  }
  if (strcmp(ne->name, "session-closed") == 0)
  {
    control_notify_session_closed(ne->session);
  }
  if (strcmp(ne->name, "session-window-changed") == 0)
  {
    control_notify_session_window_changed(ne->session);
  }
  notify_hook(item, ne);
  if (ne->client != 0)
  {
    server_client_unref(ne->client);
  }
  if (ne->session != 0)
  {
    session_remove_ref(ne->session, __func__);
  }
  if (ne->window != 0)
  {
    window_remove_ref(ne->window, __func__);
  }
  if (ne->fs.s != 0)
  {
    session_remove_ref(ne->fs.s, __func__);
  }
  free((void *) ne->name);
  free(ne);
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
void control_notify_session_created(struct session *s)
{
  struct client *c;
  unsigned int c_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (!(((&c[c_idx]) != 0) && (c->flags & 0x2000)))
    {
      continue;
    }
    control_write(c, "%%sessions-changed");
  }

}


----------------------------
void control_notify_window_renamed(struct window *w)
{
  struct client *c;
  unsigned int c_idx = 0;
  struct session *cs;
  unsigned int cs_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if ((!(((&c[c_idx]) != 0) && (c->flags & 0x2000))) || (c->session == 0))
    {
      continue;
    }
    cs_idx = c->session;
    if (winlink_find_by_window_id(&cs->windows, w->id) != 0)
    {
      control_write(c, "%%window-renamed @%u %s", w->id, w->name);
    }
    else
    {
      control_write(c, "%%unlinked-window-renamed @%u %s", w->id, w->name);
    }
  }

}


----------------------------
void control_notify_window_linked(struct session *s, struct window *w)
{
  struct client *c;
  unsigned int c_idx = 0;
  struct session *cs;
  unsigned int cs_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if ((!(((&c[c_idx]) != 0) && (c->flags & 0x2000))) || (c->session == 0))
    {
      continue;
    }
    cs_idx = c->session;
    if (winlink_find_by_window_id(&cs->windows, w->id) != 0)
    {
      control_write(c, "%%window-add @%u", w->id);
    }
    else
      control_write(c, "%%unlinked-window-add @%u", w->id);
  }

}


----------------------------
None
----------------------------
void control_notify_session_renamed(struct session *s)
{
  struct client *c;
  unsigned int c_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (!(((&c[c_idx]) != 0) && (c->flags & 0x2000)))
    {
      continue;
    }
    control_write(c, "%%session-renamed $%u %s", s->id, s->name);
  }

}


----------------------------
void control_notify_window_pane_changed(struct window *w)
{
  struct client *c;
  unsigned int c_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (!(((&c[c_idx]) != 0) && (c->flags & 0x2000)))
    {
      continue;
    }
    control_write(c, "%%window-pane-changed @%u %%%u", w->id, w->active->id);
  }

}


----------------------------
struct notify_entry
{
  const char *name;
  struct client *client;
  struct session *session;
  struct window *window;
  int pane;
  struct cmd_find_state fs;
}
----------------------------
void server_client_unref(struct client *c)
{
  log_debug("unref client %p (%d references)", c, c->references);
  c->references -= 1;
  if (c->references == 0)
  {
    event_once(-1, EV_TIMEOUT, server_client_free, c, 0);
  }
}


----------------------------
static void notify_hook(struct cmdq_item *item, struct notify_entry *ne)
{
  struct cmd_find_state fs;
  struct hook *hook;
  unsigned int hook_idx = 0;
  struct cmdq_item *new_item;
  unsigned int new_item_idx = 0;
  struct session *s = ne->session;
  struct window *w = ne->window;
  cmd_find_clear_state(&fs, 0);
  if (cmd_find_empty_state(&ne->fs) || (!cmd_find_valid_state(&ne->fs)))
  {
    cmd_find_from_nothing(&fs, 0);
  }
  else
    cmd_find_copy_state(&fs, &ne->fs);
  hook_idx = hooks_find(hooks_get(fs.s), ne->name);
  if ((&hook[hook_idx]) == 0)
  {
    return;
  }
  log_debug("notify hook %s", ne->name);
  new_item_idx = cmdq_get_command(hook->cmdlist, &fs, 0, 0x4);
  cmdq_format(new_item, "hook", "%s", ne->name);
  if (s != 0)
  {
    cmdq_format(new_item, "hook_session", "$%u", s->id);
    cmdq_format(new_item, "hook_session_name", "%s", s->name);
  }
  if (w != 0)
  {
    cmdq_format(new_item, "hook_window", "@%u", w->id);
    cmdq_format(new_item, "hook_window_name", "%s", w->name);
  }
  if (ne->pane != (-1))
  {
    cmdq_format(new_item, "hook_pane", "%%%d", ne->pane);
  }
  cmdq_insert_after(item, new_item);
}


----------------------------
void control_notify_window_unlinked(struct session *s, struct window *w)
{
  struct client *c;
  unsigned int c_idx = 0;
  struct session *cs;
  unsigned int cs_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if ((!(((&c[c_idx]) != 0) && (c->flags & 0x2000))) || (c->session == 0))
    {
      continue;
    }
    cs_idx = c->session;
    if (winlink_find_by_window_id(&cs->windows, w->id) != 0)
    {
      control_write(c, "%%window-close @%u", w->id);
    }
    else
      control_write(c, "%%unlinked-window-close @%u", w->id);
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
void session_remove_ref(struct session *s, const char *from)
{
  s->references -= 1;
  log_debug("%s: %s %s, now %d", __func__, s->name, from, s->references);
  if (s->references == 0)
  {
    event_once(-1, EV_TIMEOUT, session_free, s, 0);
  }
}


----------------------------
void control_notify_window_layout_changed(struct window *w)
{
  struct client *c;
  unsigned int c_idx = 0;
  struct session *s;
  unsigned int s_idx = 0;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  const char *template;
  unsigned int template_idx = 0;
  char *cp;
  unsigned int cp_idx = 0;
  template_idx = "%layout-change #{window_id} #{window_layout} #{window_visible_layout} #{window_flags}";
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if ((!(((&c[c_idx]) != 0) && (c->flags & 0x2000))) || (c->session == 0))
    {
      continue;
    }
    s_idx = c->session;
    if (winlink_find_by_window_id(&s->windows, w->id) == 0)
    {
      continue;
    }
    if (w->layout_root == 0)
    {
      continue;
    }
    wl_idx = winlink_find_by_window(&s->windows, w);
    if ((&wl[wl_idx]) != 0)
    {
      cp_idx = format_single(0, template, c, 0, wl, 0);
      control_write(c, "%s", cp);
      free(cp);
    }
  }

}


----------------------------
void control_notify_session_closed(struct session *s)
{
  struct client *c;
  unsigned int c_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (!(((&c[c_idx]) != 0) && (c->flags & 0x2000)))
    {
      continue;
    }
    control_write(c, "%%sessions-changed");
  }

}


----------------------------
void control_notify_pane_mode_changed(int pane)
{
  struct client *c;
  unsigned int c_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (!(((&c[c_idx]) != 0) && (c->flags & 0x2000)))
    {
      continue;
    }
    control_write(c, "%%pane-mode-changed %%%u", pane);
  }

}


----------------------------
void control_notify_client_session_changed(struct client *cc)
{
  struct client *c;
  unsigned int c_idx = 0;
  struct session *s;
  unsigned int s_idx = 0;
  if (cc->session == 0)
  {
    return;
  }
  s_idx = cc->session;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if ((!(((&c[c_idx]) != 0) && (c->flags & 0x2000))) || (c->session == 0))
    {
      continue;
    }
    if (cc == (&c[c_idx]))
    {
      control_write(c, "%%session-changed $%u %s", s->id, s->name);
    }
    else
    {
      control_write(c, "%%client-session-changed %s $%u %s", cc->name, s->id, s->name);
    }
  }

}


----------------------------
void control_notify_session_window_changed(struct session *s)
{
  struct client *c;
  unsigned int c_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (!(((&c[c_idx]) != 0) && (c->flags & 0x2000)))
    {
      continue;
    }
    control_write(c, "%%session-window-changed $%u @%u", s->id, s->curw->window->id);
  }

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


// element in merge of:  window_remove_ref,notify_add,window_pane_destroy,notify_callback,window_destroy_panes,window_destroy,notify_pane,window_pane_reset_mode
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


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
***/


// element in merge of:  window_remove_ref,notify_add,window_pane_destroy,notify_callback,window_destroy_panes,window_destroy,notify_pane,window_pane_reset_mode
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


/*** DEPENDENCIES:
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


----------------------------
None
----------------------------
struct windows
{
  struct window *rbh_root;
}
----------------------------
void options_free(struct options *oo)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  struct options_entry *tmp;
  unsigned int tmp_idx = 0;
  for (o_idx = options_tree_RB_MINMAX(&oo->tree, -1); ((&o[o_idx]) != 0) && ((tmp_idx = options_tree_RB_NEXT(o), 1)); o_idx = &tmp[tmp_idx])
  {
    options_remove(o);
  }

  free(oo);
}


----------------------------
void layout_free_cell(struct layout_cell *lc)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  switch (lc->type)
  {
    case LAYOUT_LEFTRIGHT:

    case LAYOUT_TOPBOTTOM:
    {
      while (!((&lc->cells)->tqh_first == 0))
      {
        lcchild_idx = (&lc->cells)->tqh_first;
        do
        {
          if (lcchild->entry.tqe_next != 0)
          {
            lcchild->entry.tqe_next->entry.tqe_prev = lcchild->entry.tqe_prev;
          }
          else
            (&lc->cells)->tqh_last = lcchild->entry.tqe_prev;
          *lcchild->entry.tqe_prev = lcchild->entry.tqe_next;
          ;
          ;
        }
        while (0);
        layout_free_cell(lcchild);
      }

      break;
    }

    case LAYOUT_WINDOWPANE:
    {
      if (lc->wp != 0)
      {
        lc->wp->layout_cell = 0;
      }
      break;
    }

  }

  free(lc);
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


// element in merge of:  window_remove_ref,notify_add,window_pane_destroy,notify_callback,window_destroy_panes,window_destroy,notify_pane,window_pane_reset_mode
void notify_pane(const char *name, struct window_pane *wp)
{
  struct cmd_find_state fs;
  cmd_find_from_pane(&fs, wp, 0);
  notify_add(name, &fs, 0, 0, 0, wp);
}


/*** DEPENDENCIES:
int cmd_find_from_pane(struct cmd_find_state *fs, struct window_pane *wp, int flags)
{
  if (cmd_find_from_window(fs, wp->window, flags) != 0)
  {
    return -1;
  }
  fs->wp = wp;
  cmd_find_log_state(__func__, fs);
  return 0;
}


----------------------------
None
----------------------------
None
----------------------------
***/


// element in merge of:  window_remove_ref,notify_add,window_pane_destroy,notify_callback,window_destroy_panes,window_destroy,notify_pane,window_pane_reset_mode
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


/*** DEPENDENCIES:
None
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
None
----------------------------
***/


