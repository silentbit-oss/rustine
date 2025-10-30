static void cmd_list_windows_session(struct cmd *self, struct session *s, struct cmdq_item *item, int type)
{
  struct args *args = self->args;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  u_int n;
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  const char *template;
  unsigned int template_idx = 0;
  char *line;
  unsigned int line_idx = 0;
  template_idx = args_get(args, 'F');
  if ((&template[template_idx]) == 0)
  {
    switch (type)
    {
      case 0:
      {
        template_idx = "#{window_index}: #{window_name}#{window_flags} (#{window_panes} panes) [#{window_width}x#{window_height}] [layout #{window_layout}] #{window_id}#{?window_active, (active),}";
        ;
        break;
      }

      case 1:
      {
        template_idx = "#{session_name}:#{window_index}: #{window_name}#{window_flags} (#{window_panes} panes) [#{window_width}x#{window_height}] ";
        break;
      }

    }

  }
  n = 0;
  for (wl_idx = winlinks_RB_MINMAX(&s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    ft_idx = format_create(item->client, item, 0, 0);
    format_add(ft, "line", "%u", n);
    format_defaults(ft, 0, s, wl, 0);
    line_idx = format_expand(ft, template);
    cmdq_print(item, "%s", line);
    free(line);
    format_free(ft);
    n += 1;
  }

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
struct windows
{
  struct window *rbh_root;
}
----------------------------
void format_add(struct format_tree *ft, const char *key, const char *fmt, ...)
{
  struct format_entry *fe;
  unsigned int fe_idx = 0;
  struct format_entry *fe_now;
  unsigned int fe_now_idx = 0;
  va_list ap;
  fe_idx = xmalloc(sizeof(*fe_idx));
  fe->key = xstrdup(key);
  fe_now_idx = format_entry_tree_RB_INSERT(&ft->tree, fe);
  if ((&fe_now[fe_now_idx]) != 0)
  {
    free(fe->key);
    free(fe);
    free(fe_now->value);
    fe_idx = &fe_now[fe_now_idx];
  }
  fe->cb = 0;
  fe->t = 0;
  __builtin_va_start(ap);
  xvasprintf(&fe->value, fmt, ap);
  ;
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
None
----------------------------
None
----------------------------
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
None
----------------------------
***/


static void cmd_list_windows_server(struct cmd *self, struct cmdq_item *item)
{
  struct session *s;
  unsigned int s_idx = 0;
  for (s_idx = sessions_RB_MINMAX(&sessions, -1); (&s[s_idx]) != 0; s_idx = sessions_RB_NEXT(s_idx))
  {
    cmd_list_windows_session(self, s, item, 1);
  }

}


/*** DEPENDENCIES:
struct sessions
{
  struct session *rbh_root;
}
----------------------------
struct session *sessions_RB_MINMAX(struct sessions *head, int val)
{
  struct session *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct session *parent = 0;
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


----------------------------
struct session *sessions_RB_NEXT(struct session *elm)
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


----------------------------
static void cmd_list_windows_session(struct cmd *self, struct session *s, struct cmdq_item *item, int type)
{
  struct args *args = self->args;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  u_int n;
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  const char *template;
  unsigned int template_idx = 0;
  char *line;
  unsigned int line_idx = 0;
  template_idx = args_get(args, 'F');
  if ((&template[template_idx]) == 0)
  {
    switch (type)
    {
      case 0:
      {
        template_idx = "#{window_index}: #{window_name}#{window_flags} (#{window_panes} panes) [#{window_width}x#{window_height}] [layout #{window_layout}] #{window_id}#{?window_active, (active),}";
        ;
        break;
      }

      case 1:
      {
        template_idx = "#{session_name}:#{window_index}: #{window_name}#{window_flags} (#{window_panes} panes) [#{window_width}x#{window_height}] ";
        break;
      }

    }

  }
  n = 0;
  for (wl_idx = winlinks_RB_MINMAX(&s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    ft_idx = format_create(item->client, item, 0, 0);
    format_add(ft, "line", "%u", n);
    format_defaults(ft, 0, s, wl, 0);
    line_idx = format_expand(ft, template);
    cmdq_print(item, "%s", line);
    free(line);
    format_free(ft);
    n += 1;
  }

}


----------------------------
None
----------------------------
***/


static enum cmd_retval cmd_list_windows_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  if (args_has(args, 'a'))
  {
    cmd_list_windows_server(self, item);
  }
  else
    cmd_list_windows_session(self, item->target.s, item, 0);
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
static void cmd_list_windows_session(struct cmd *self, struct session *s, struct cmdq_item *item, int type)
{
  struct args *args = self->args;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  u_int n;
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  const char *template;
  unsigned int template_idx = 0;
  char *line;
  unsigned int line_idx = 0;
  template_idx = args_get(args, 'F');
  if ((&template[template_idx]) == 0)
  {
    switch (type)
    {
      case 0:
      {
        template_idx = "#{window_index}: #{window_name}#{window_flags} (#{window_panes} panes) [#{window_width}x#{window_height}] [layout #{window_layout}] #{window_id}#{?window_active, (active),}";
        ;
        break;
      }

      case 1:
      {
        template_idx = "#{session_name}:#{window_index}: #{window_name}#{window_flags} (#{window_panes} panes) [#{window_width}x#{window_height}] ";
        break;
      }

    }

  }
  n = 0;
  for (wl_idx = winlinks_RB_MINMAX(&s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    ft_idx = format_create(item->client, item, 0, 0);
    format_add(ft, "line", "%u", n);
    format_defaults(ft, 0, s, wl, 0);
    line_idx = format_expand(ft, template);
    cmdq_print(item, "%s", line);
    free(line);
    format_free(ft);
    n += 1;
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
static void cmd_list_windows_server(struct cmd *self, struct cmdq_item *item)
{
  struct session *s;
  unsigned int s_idx = 0;
  for (s_idx = sessions_RB_MINMAX(&sessions, -1); (&s[s_idx]) != 0; s_idx = sessions_RB_NEXT(s_idx))
  {
    cmd_list_windows_session(self, s, item, 1);
  }

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


