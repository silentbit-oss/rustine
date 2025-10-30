static enum cmd_retval cmd_kill_window_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct winlink *wl = item->target.wl;
  struct winlink *wl2;
  unsigned int wl2_idx = 0;
  struct winlink *wl3;
  unsigned int wl3_idx = 0;
  struct window *w = wl->window;
  struct session *s = item->target.s;
  if (self->entry == (&cmd_unlink_window_entry))
  {
    if ((!args_has(self->args, 'k')) && (!session_is_linked(s, w)))
    {
      cmdq_error(item, "window only linked to one session");
      return CMD_RETURN_ERROR;
    }
    server_unlink_window(s, wl);
  }
  else
  {
    if (args_has(args, 'a'))
    {
      for (wl2_idx = winlinks_RB_MINMAX(&s->windows, -1); ((&wl2[wl2_idx]) != 0) && ((wl3_idx = winlinks_RB_NEXT(wl2), 1)); wl2_idx = &wl3[wl3_idx])
      {
        if (wl != (&wl2[wl2_idx]))
        {
          server_kill_window(wl2->window);
        }
      }

    }
    else
      server_kill_window(wl->window);
  }
  recalculate_sizes();
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
int session_is_linked(struct session *s, struct window *w)
{
  struct session_group *sg;
  unsigned int sg_idx = 0;
  if ((sg_idx = session_group_contains(s)) != 0)
  {
    return w->references != session_group_count(sg);
  }
  return w->references != 1;
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
struct windows
{
  struct window *rbh_root;
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
enum cmd_retval
{
  CMD_RETURN_ERROR = -1,
  CMD_RETURN_NORMAL = 0,
  CMD_RETURN_WAIT,
  CMD_RETURN_STOP
}
----------------------------
void server_unlink_window(struct session *s, struct winlink *wl)
{
  if (session_detach(s, wl))
  {
    server_destroy_session_group(s);
  }
  else
    server_redraw_session_group(s);
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
extern const struct cmd_entry cmd_unlink_window_entry
----------------------------
void server_kill_window(struct window *w)
{
  struct session *s;
  unsigned int s_idx = 0;
  struct session *next_s;
  unsigned int next_s_idx = 0;
  struct session *target_s;
  unsigned int target_s_idx = 0;
  struct session_group *sg;
  unsigned int sg_idx = 0;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  next_s_idx = sessions_RB_MINMAX(&sessions, -1);
  while ((&next_s[next_s_idx]) != 0)
  {
    s_idx = &next_s[next_s_idx];
    next_s_idx = sessions_RB_NEXT(s);
    if (!session_has(s, w))
    {
      continue;
    }
    server_unzoom_window(w);
    while ((wl_idx = winlink_find_by_window(&s->windows, w)) != 0)
    {
      if (session_detach(s, wl))
      {
        server_destroy_session_group(s);
        break;
      }
      else
        server_redraw_session_group(s);
    }

    if (options_get_number(s->options, "renumber-windows"))
    {
      if ((sg_idx = session_group_contains(s)) != 0)
      {
        for (target_s_idx = (&sg->sessions)->tqh_first; (&target_s[target_s_idx]) != 0; target_s_idx = target_s_idx->gentry.tqe_next)
        {
          session_renumber_windows(target_s);
        }

      }
      else
        session_renumber_windows(s);
    }
  }

  recalculate_sizes();
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


