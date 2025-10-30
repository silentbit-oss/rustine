static enum cmd_retval cmd_kill_session_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct session *s;
  unsigned int s_idx = 0;
  struct session *sloop;
  unsigned int sloop_idx = 0;
  struct session *stmp;
  unsigned int stmp_idx = 0;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  s_idx = item->target.s_idx;
  if (args_has(args, 'C'))
  {
    for (wl_idx = winlinks_RB_MINMAX(&s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
    {
      wl->window->flags &= ~((0x1 | 0x2) | 0x8);
      wl->flags &= ~((0x1 | 0x2) | 0x4);
    }

    server_redraw_session(s);
  }
  else
    if (args_has(args, 'a'))
  {
    for (sloop_idx = sessions_RB_MINMAX(&sessions, -1); ((&sloop[sloop_idx]) != 0) && ((stmp_idx = sessions_RB_NEXT(sloop), 1)); sloop_idx = &stmp[stmp_idx])
    {
      if ((&sloop[sloop_idx]) != (&s[s_idx]))
      {
        server_destroy_session(sloop);
        session_destroy(sloop, __func__);
      }
    }

  }
  else
  {
    server_destroy_session(s);
    session_destroy(s, __func__);
  }
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
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
void server_destroy_session(struct session *s)
{
  struct client *c;
  unsigned int c_idx = 0;
  struct session *s_new;
  unsigned int s_new_idx = 0;
  if (!options_get_number(s->options, "detach-on-destroy"))
  {
    s_new_idx = server_next_session(s);
  }
  else
    s_new_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (c->session != s)
    {
      continue;
    }
    if ((&s_new[s_new_idx]) == 0)
    {
      c->session = 0;
      c->flags |= 0x4;
    }
    else
    {
      c->last_session = 0;
      c->session = &s_new[s_new_idx];
      server_client_set_key_table(c, 0);
      status_timer_start(c);
      notify_client("client-session-changed", c);
      session_update_activity(s_new, 0);
      gettimeofday(&s_new->last_attached_time, 0);
      server_redraw_client(c);
      alerts_check_session(s_new);
    }
  }

  recalculate_sizes();
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
enum cmd_retval
{
  CMD_RETURN_ERROR = -1,
  CMD_RETURN_NORMAL = 0,
  CMD_RETURN_WAIT,
  CMD_RETURN_STOP
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
struct sessions
{
  struct session *rbh_root;
}
----------------------------
void session_destroy(struct session *s, const char *from)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  log_debug("session %s destroyed (%s)", s->name, from);
  s->curw = 0;
  sessions_RB_REMOVE(&sessions, s);
  notify_session("session-closed", s);
  free(s->tio);
  if (event_initialized(&s->lock_timer))
  {
    event_del(&s->lock_timer);
  }
  session_group_remove(s);
  while (!((&s->lastw)->tqh_first == 0))
  {
    winlink_stack_remove(&s->lastw, (&s->lastw)->tqh_first);
  }

  while (!((&s->windows)->rbh_root == 0))
  {
    wl_idx = (&s->windows)->rbh_root;
    notify_session_window("window-unlinked", s, wl->window);
    winlink_remove(&s->windows, wl);
  }

  free((void *) s->cwd);
  session_remove_ref(s, __func__);
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
int args_has(struct args *args, u_char ch)
{
  return args_find(args, ch) != 0;
}


----------------------------
None
----------------------------
***/


