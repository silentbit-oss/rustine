static int alerts_enabled(struct window *w, int flags)
{
  if (flags & 0x1)
  {
    if (options_get_number(w->options, "monitor-bell"))
    {
      return 1;
    }
  }
  if (flags & 0x2)
  {
    if (options_get_number(w->options, "monitor-activity"))
    {
      return 1;
    }
  }
  if (flags & 0x8)
  {
    if (options_get_number(w->options, "monitor-silence") != 0)
    {
      return 1;
    }
  }
  return 0;
}


/*** DEPENDENCIES:
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
None
----------------------------
***/


static int alerts_action_applies(struct winlink *wl, const char *name)
{
  int action;
  action = options_get_number(wl->session->options, name);
  if (action == 1)
  {
    return 1;
  }
  if (action == 2)
  {
    return wl == wl->session->curw;
  }
  if (action == 3)
  {
    return wl != wl->session->curw;
  }
  return 0;
}


/*** DEPENDENCIES:
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
None
----------------------------
***/


static void alerts_set_message(struct winlink *wl, const char *type, const char *option)
{
  struct client *c;
  unsigned int c_idx = 0;
  int visual;
  visual = options_get_number(wl->session->options, option);
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if ((c->session != wl->session) || (c->flags & 0x2000))
    {
      continue;
    }
    if ((visual == 0) || (visual == 2))
    {
      tty_putcode(&c->tty, TTYC_BEL);
    }
    if (visual == 0)
    {
      continue;
    }
    if (c->session->curw == wl)
    {
      status_message_set(c, "%s in current window", type);
    }
    else
      status_message_set(c, "%s in window %d", type, wl->idx);
  }

}


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
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
void status_message_set(struct client *c, const char *fmt, ...)
{
  struct timeval tv;
  va_list ap;
  int delay;
  status_message_clear(c);
  if (c->status.old_status == 0)
  {
    c->status.old_status = xmalloc(sizeof(*c->status.old_status));
    memcpy(c->status.old_status, &c->status.status, sizeof(*c->status.old_status));
    screen_init(&c->status.status, c->tty.sx, 1, 0);
  }
  __builtin_va_start(ap);
  xvasprintf(&c->message_string, fmt, ap);
  ;
  server_client_add_message(c, "%s", c->message_string);
  delay = options_get_number(c->session->options, "display-time");
  if (delay > 0)
  {
    tv.tv_sec = delay / 1000;
    tv.tv_usec = (delay % 1000) * 1000L;
    if (event_initialized(&c->message_timer))
    {
      evtimer_del(&c->message_timer);
    }
    evtimer_set(&c->message_timer, status_message_callback, c);
    evtimer_add(&c->message_timer, &tv);
  }
  c->tty.flags |= 0x1 | 0x2;
  c->flags |= 0x10;
}


----------------------------
void tty_putcode(struct tty *tty, enum tty_code_code code)
{
  tty_puts(tty, tty_term_string(tty->term, code));
}


----------------------------
None
----------------------------
***/


static int alerts_check_silence(struct window *w)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct session *s;
  unsigned int s_idx = 0;
  if ((~w->flags) & 0x8)
  {
    return 0;
  }
  if (options_get_number(w->options, "monitor-silence") == 0)
  {
    return 0;
  }
  for (wl_idx = (&w->winlinks)->tqh_first; (&wl[wl_idx]) != 0; wl_idx = wl_idx->wentry.tqe_next)
  {
    wl->session->flags &= ~0x4;
  }

  for (wl_idx = (&w->winlinks)->tqh_first; (&wl[wl_idx]) != 0; wl_idx = wl_idx->wentry.tqe_next)
  {
    if (wl->flags & 0x4)
    {
      continue;
    }
    s_idx = wl->session;
    if (s->curw != (&wl[wl_idx]))
    {
      wl->flags |= 0x4;
      server_status_session(s);
    }
    if (!alerts_action_applies(wl, "silence-action"))
    {
      continue;
    }
    notify_winlink("alert-silence", wl);
    if (s->flags & 0x4)
    {
      continue;
    }
    s->flags |= 0x4;
    alerts_set_message(wl, "Silence", "visual-silence");
  }

  return 0x8;
}


/*** DEPENDENCIES:
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
static int alerts_action_applies(struct winlink *wl, const char *name)
{
  int action;
  action = options_get_number(wl->session->options, name);
  if (action == 1)
  {
    return 1;
  }
  if (action == 2)
  {
    return wl == wl->session->curw;
  }
  if (action == 3)
  {
    return wl != wl->session->curw;
  }
  return 0;
}


----------------------------
void notify_winlink(const char *name, struct winlink *wl)
{
  struct cmd_find_state fs;
  cmd_find_from_winlink(&fs, wl, 0);
  notify_add(name, &fs, 0, wl->session, wl->window, 0);
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
static void alerts_set_message(struct winlink *wl, const char *type, const char *option)
{
  struct client *c;
  unsigned int c_idx = 0;
  int visual;
  visual = options_get_number(wl->session->options, option);
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if ((c->session != wl->session) || (c->flags & 0x2000))
    {
      continue;
    }
    if ((visual == 0) || (visual == 2))
    {
      tty_putcode(&c->tty, TTYC_BEL);
    }
    if (visual == 0)
    {
      continue;
    }
    if (c->session->curw == wl)
    {
      status_message_set(c, "%s in current window", type);
    }
    else
      status_message_set(c, "%s in window %d", type, wl->idx);
  }

}


----------------------------
None
----------------------------
***/


static int alerts_check_activity(struct window *w)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct session *s;
  unsigned int s_idx = 0;
  if ((~w->flags) & 0x2)
  {
    return 0;
  }
  if (!options_get_number(w->options, "monitor-activity"))
  {
    return 0;
  }
  for (wl_idx = (&w->winlinks)->tqh_first; (&wl[wl_idx]) != 0; wl_idx = wl_idx->wentry.tqe_next)
  {
    wl->session->flags &= ~0x4;
  }

  for (wl_idx = (&w->winlinks)->tqh_first; (&wl[wl_idx]) != 0; wl_idx = wl_idx->wentry.tqe_next)
  {
    if (wl->flags & 0x2)
    {
      continue;
    }
    s_idx = wl->session;
    if (s->curw != (&wl[wl_idx]))
    {
      wl->flags |= 0x2;
      server_status_session(s);
    }
    if (!alerts_action_applies(wl, "activity-action"))
    {
      continue;
    }
    notify_winlink("alert-activity", wl);
    if (s->flags & 0x4)
    {
      continue;
    }
    s->flags |= 0x4;
    alerts_set_message(wl, "Activity", "visual-activity");
  }

  return 0x2;
}


/*** DEPENDENCIES:
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
static int alerts_action_applies(struct winlink *wl, const char *name)
{
  int action;
  action = options_get_number(wl->session->options, name);
  if (action == 1)
  {
    return 1;
  }
  if (action == 2)
  {
    return wl == wl->session->curw;
  }
  if (action == 3)
  {
    return wl != wl->session->curw;
  }
  return 0;
}


----------------------------
void notify_winlink(const char *name, struct winlink *wl)
{
  struct cmd_find_state fs;
  cmd_find_from_winlink(&fs, wl, 0);
  notify_add(name, &fs, 0, wl->session, wl->window, 0);
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
static void alerts_set_message(struct winlink *wl, const char *type, const char *option)
{
  struct client *c;
  unsigned int c_idx = 0;
  int visual;
  visual = options_get_number(wl->session->options, option);
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if ((c->session != wl->session) || (c->flags & 0x2000))
    {
      continue;
    }
    if ((visual == 0) || (visual == 2))
    {
      tty_putcode(&c->tty, TTYC_BEL);
    }
    if (visual == 0)
    {
      continue;
    }
    if (c->session->curw == wl)
    {
      status_message_set(c, "%s in current window", type);
    }
    else
      status_message_set(c, "%s in window %d", type, wl->idx);
  }

}


----------------------------
None
----------------------------
***/


static int alerts_check_bell(struct window *w)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct session *s;
  unsigned int s_idx = 0;
  if ((~w->flags) & 0x1)
  {
    return 0;
  }
  if (!options_get_number(w->options, "monitor-bell"))
  {
    return 0;
  }
  for (wl_idx = (&w->winlinks)->tqh_first; (&wl[wl_idx]) != 0; wl_idx = wl_idx->wentry.tqe_next)
  {
    wl->session->flags &= ~0x4;
  }

  for (wl_idx = (&w->winlinks)->tqh_first; (&wl[wl_idx]) != 0; wl_idx = wl_idx->wentry.tqe_next)
  {
    s_idx = wl->session;
    if (s->curw != (&wl[wl_idx]))
    {
      wl->flags |= 0x1;
      server_status_session(s);
    }
    if (!alerts_action_applies(wl, "bell-action"))
    {
      continue;
    }
    notify_winlink("alert-bell", wl);
    if (s->flags & 0x4)
    {
      continue;
    }
    s->flags |= 0x4;
    alerts_set_message(wl, "Bell", "visual-bell");
  }

  return 0x1;
}


/*** DEPENDENCIES:
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
static int alerts_action_applies(struct winlink *wl, const char *name)
{
  int action;
  action = options_get_number(wl->session->options, name);
  if (action == 1)
  {
    return 1;
  }
  if (action == 2)
  {
    return wl == wl->session->curw;
  }
  if (action == 3)
  {
    return wl != wl->session->curw;
  }
  return 0;
}


----------------------------
void notify_winlink(const char *name, struct winlink *wl)
{
  struct cmd_find_state fs;
  cmd_find_from_winlink(&fs, wl, 0);
  notify_add(name, &fs, 0, wl->session, wl->window, 0);
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
static void alerts_set_message(struct winlink *wl, const char *type, const char *option)
{
  struct client *c;
  unsigned int c_idx = 0;
  int visual;
  visual = options_get_number(wl->session->options, option);
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if ((c->session != wl->session) || (c->flags & 0x2000))
    {
      continue;
    }
    if ((visual == 0) || (visual == 2))
    {
      tty_putcode(&c->tty, TTYC_BEL);
    }
    if (visual == 0)
    {
      continue;
    }
    if (c->session->curw == wl)
    {
      status_message_set(c, "%s in current window", type);
    }
    else
      status_message_set(c, "%s in window %d", type, wl->idx);
  }

}


----------------------------
None
----------------------------
***/


static int alerts_check_all(struct window *w)
{
  int alerts;
  alerts = alerts_check_bell(w);
  alerts |= alerts_check_activity(w);
  alerts |= alerts_check_silence(w);
  return alerts;
}


/*** DEPENDENCIES:
static int alerts_check_silence(struct window *w)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct session *s;
  unsigned int s_idx = 0;
  if ((~w->flags) & 0x8)
  {
    return 0;
  }
  if (options_get_number(w->options, "monitor-silence") == 0)
  {
    return 0;
  }
  for (wl_idx = (&w->winlinks)->tqh_first; (&wl[wl_idx]) != 0; wl_idx = wl_idx->wentry.tqe_next)
  {
    wl->session->flags &= ~0x4;
  }

  for (wl_idx = (&w->winlinks)->tqh_first; (&wl[wl_idx]) != 0; wl_idx = wl_idx->wentry.tqe_next)
  {
    if (wl->flags & 0x4)
    {
      continue;
    }
    s_idx = wl->session;
    if (s->curw != (&wl[wl_idx]))
    {
      wl->flags |= 0x4;
      server_status_session(s);
    }
    if (!alerts_action_applies(wl, "silence-action"))
    {
      continue;
    }
    notify_winlink("alert-silence", wl);
    if (s->flags & 0x4)
    {
      continue;
    }
    s->flags |= 0x4;
    alerts_set_message(wl, "Silence", "visual-silence");
  }

  return 0x8;
}


----------------------------
static int alerts_check_activity(struct window *w)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct session *s;
  unsigned int s_idx = 0;
  if ((~w->flags) & 0x2)
  {
    return 0;
  }
  if (!options_get_number(w->options, "monitor-activity"))
  {
    return 0;
  }
  for (wl_idx = (&w->winlinks)->tqh_first; (&wl[wl_idx]) != 0; wl_idx = wl_idx->wentry.tqe_next)
  {
    wl->session->flags &= ~0x4;
  }

  for (wl_idx = (&w->winlinks)->tqh_first; (&wl[wl_idx]) != 0; wl_idx = wl_idx->wentry.tqe_next)
  {
    if (wl->flags & 0x2)
    {
      continue;
    }
    s_idx = wl->session;
    if (s->curw != (&wl[wl_idx]))
    {
      wl->flags |= 0x2;
      server_status_session(s);
    }
    if (!alerts_action_applies(wl, "activity-action"))
    {
      continue;
    }
    notify_winlink("alert-activity", wl);
    if (s->flags & 0x4)
    {
      continue;
    }
    s->flags |= 0x4;
    alerts_set_message(wl, "Activity", "visual-activity");
  }

  return 0x2;
}


----------------------------
static int alerts_check_bell(struct window *w)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct session *s;
  unsigned int s_idx = 0;
  if ((~w->flags) & 0x1)
  {
    return 0;
  }
  if (!options_get_number(w->options, "monitor-bell"))
  {
    return 0;
  }
  for (wl_idx = (&w->winlinks)->tqh_first; (&wl[wl_idx]) != 0; wl_idx = wl_idx->wentry.tqe_next)
  {
    wl->session->flags &= ~0x4;
  }

  for (wl_idx = (&w->winlinks)->tqh_first; (&wl[wl_idx]) != 0; wl_idx = wl_idx->wentry.tqe_next)
  {
    s_idx = wl->session;
    if (s->curw != (&wl[wl_idx]))
    {
      wl->flags |= 0x1;
      server_status_session(s);
    }
    if (!alerts_action_applies(wl, "bell-action"))
    {
      continue;
    }
    notify_winlink("alert-bell", wl);
    if (s->flags & 0x4)
    {
      continue;
    }
    s->flags |= 0x4;
    alerts_set_message(wl, "Bell", "visual-bell");
  }

  return 0x1;
}


----------------------------
None
----------------------------
***/


static void alerts_callback(int fd, short events, void *arg)
{
  struct window *w;
  unsigned int w_idx = 0;
  struct window *w1;
  unsigned int w1_idx = 0;
  int alerts;
  for (w_idx = (&alerts_list)->tqh_first; ((&w[w_idx]) != 0) && ((w1_idx = w->alerts_entry.tqe_next, 1)); w_idx = &w1[w1_idx])
  {
    alerts = alerts_check_all(w);
    log_debug("@%u alerts check, alerts %#x", w->id, alerts);
    w->alerts_queued = 0;
    do
    {
      if (w->alerts_entry.tqe_next != 0)
      {
        w->alerts_entry.tqe_next->alerts_entry.tqe_prev = w->alerts_entry.tqe_prev;
      }
      else
        (&alerts_list)->tqh_last = w->alerts_entry.tqe_prev;
      *w->alerts_entry.tqe_prev = w->alerts_entry.tqe_next;
      ;
      ;
    }
    while (0);
    w->flags &= ~((0x1 | 0x2) | 0x8);
    window_remove_ref(w, __func__);
  }

  alerts_fired = 0;
}


/*** DEPENDENCIES:
static struct 
{
  struct window *tqh_first;
  struct window **tqh_last;
} alerts_list = {0, &alerts_list.tqh_first}
----------------------------
None
----------------------------
static int alerts_check_all(struct window *w)
{
  int alerts;
  alerts = alerts_check_bell(w);
  alerts |= alerts_check_activity(w);
  alerts |= alerts_check_silence(w);
  return alerts;
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
static int alerts_fired
----------------------------
None
----------------------------
***/


void alerts_check_session(struct session *s)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  for (wl_idx = winlinks_RB_MINMAX(&s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    alerts_check_all(wl->window);
  }

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
static int alerts_check_all(struct window *w)
{
  int alerts;
  alerts = alerts_check_bell(w);
  alerts |= alerts_check_activity(w);
  alerts |= alerts_check_silence(w);
  return alerts;
}


----------------------------
None
----------------------------
***/


void alerts_reset_all(void)
{
  struct window *w;
  unsigned int w_idx = 0;
  for (w_idx = windows_RB_MINMAX(&windows, -1); (&w[w_idx]) != 0; w_idx = windows_RB_NEXT(w_idx))
  {
    alerts_reset(w);
  }

}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
None
----------------------------
struct window *windows_RB_MINMAX(struct windows *head, int val)
{
  struct window *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct window *parent = 0;
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
struct window *windows_RB_NEXT(struct window *elm)
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
None
----------------------------
***/


