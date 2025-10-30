static enum cmd_retval cmd_swap_window_exec(struct cmd *self, struct cmdq_item *item)
{
  struct session *src;
  unsigned int src_idx = 0;
  struct session *dst;
  unsigned int dst_idx = 0;
  struct session_group *sg_src;
  unsigned int sg_src_idx = 0;
  struct session_group *sg_dst;
  unsigned int sg_dst_idx = 0;
  struct winlink *wl_src;
  unsigned int wl_src_idx = 0;
  struct winlink *wl_dst;
  unsigned int wl_dst_idx = 0;
  struct window *w_src;
  unsigned int w_src_idx = 0;
  struct window *w_dst;
  unsigned int w_dst_idx = 0;
  wl_src_idx = item->source.wl;
  src_idx = item->source.s;
  sg_src_idx = session_group_contains(src);
  wl_dst_idx = item->target.wl;
  dst_idx = item->target.s;
  sg_dst_idx = session_group_contains(dst);
  if (((((&src[src_idx]) != (&dst[dst_idx])) && ((&sg_src[sg_src_idx]) != 0)) && ((&sg_dst[sg_dst_idx]) != 0)) && ((&sg_src[sg_src_idx]) == (&sg_dst[sg_dst_idx])))
  {
    cmdq_error(item, "can't move window, sessions are grouped");
    return CMD_RETURN_ERROR;
  }
  if (wl_dst->window == wl_src->window)
  {
    return CMD_RETURN_NORMAL;
  }
  w_dst_idx = wl_dst->window;
  do
  {
    if (wl_dst->wentry.tqe_next != 0)
    {
      wl_dst->wentry.tqe_next->wentry.tqe_prev = wl_dst->wentry.tqe_prev;
    }
    else
      (&w_dst->winlinks)->tqh_last = wl_dst->wentry.tqe_prev;
    *wl_dst->wentry.tqe_prev = wl_dst->wentry.tqe_next;
    ;
    ;
  }
  while (0);
  w_src_idx = wl_src->window;
  do
  {
    if (wl_src->wentry.tqe_next != 0)
    {
      wl_src->wentry.tqe_next->wentry.tqe_prev = wl_src->wentry.tqe_prev;
    }
    else
      (&w_src->winlinks)->tqh_last = wl_src->wentry.tqe_prev;
    *wl_src->wentry.tqe_prev = wl_src->wentry.tqe_next;
    ;
    ;
  }
  while (0);
  wl_dst->window = &w_src[w_src_idx];
  do
  {
    wl_dst->wentry.tqe_next = 0;
    wl_dst->wentry.tqe_prev = (&w_src->winlinks)->tqh_last;
    *(&w_src->winlinks)->tqh_last = &wl_dst[wl_dst_idx];
    (&w_src->winlinks)->tqh_last = &wl_dst->wentry.tqe_next;
  }
  while (0);
  wl_src->window = &w_dst[w_dst_idx];
  do
  {
    wl_src->wentry.tqe_next = 0;
    wl_src->wentry.tqe_prev = (&w_dst->winlinks)->tqh_last;
    *(&w_dst->winlinks)->tqh_last = &wl_src[wl_src_idx];
    (&w_dst->winlinks)->tqh_last = &wl_src->wentry.tqe_next;
  }
  while (0);
  if (!args_has(self->args, 'd'))
  {
    session_select(dst, wl_dst->idx);
    if ((&src[src_idx]) != (&dst[dst_idx]))
    {
      session_select(src, wl_src->idx);
    }
  }
  session_group_synchronize_from(src);
  server_redraw_session_group(src);
  if ((&src[src_idx]) != (&dst[dst_idx]))
  {
    session_group_synchronize_from(dst);
    server_redraw_session_group(dst);
  }
  recalculate_sizes();
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
int session_select(struct session *s, int idx)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  wl_idx = winlink_find_by_index(&s->windows, idx);
  return session_set_current(s, wl);
}


----------------------------
struct session_group *session_group_contains(struct session *target)
{
  struct session_group *sg;
  unsigned int sg_idx = 0;
  struct session *s;
  unsigned int s_idx = 0;
  for (sg_idx = session_groups_RB_MINMAX(&session_groups, -1); (&sg[sg_idx]) != 0; sg_idx = session_groups_RB_NEXT(sg_idx))
  {
    for (s_idx = (&sg->sessions)->tqh_first; (&s[s_idx]) != 0; s_idx = s_idx->gentry.tqe_next)
    {
      if ((&s[s_idx]) == target)
      {
        return sg;
      }
    }

  }

  return 0;
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
void server_redraw_session_group(struct session *s)
{
  unsigned int s_idx = 0;
  struct session_group *sg;
  unsigned int sg_idx = 0;
  if ((sg_idx = session_group_contains(s)) == 0)
  {
    server_redraw_session(s);
  }
  else
  {
    for (s_idx = (&sg->sessions)->tqh_first; (&s[s_idx]) != 0; s_idx = s_idx->gentry.tqe_next)
    {
      server_redraw_session(s);
    }

  }
}


----------------------------
void session_group_synchronize_from(struct session *target)
{
  struct session_group *sg;
  unsigned int sg_idx = 0;
  struct session *s;
  unsigned int s_idx = 0;
  if ((sg_idx = session_group_contains(target)) == 0)
  {
    return;
  }
  for (s_idx = (&sg->sessions)->tqh_first; (&s[s_idx]) != 0; s_idx = s_idx->gentry.tqe_next)
  {
    if ((&s[s_idx]) != target)
    {
      session_group_synchronize1(target, s);
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
struct session_group
{
  const char *name;
  struct 
  {
    struct session *tqh_first;
    struct session **tqh_last;
  } sessions;
  struct 
  {
    struct session_group *rbe_left;
    struct session_group *rbe_right;
    struct session_group *rbe_parent;
    int rbe_color;
  } entry;
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


