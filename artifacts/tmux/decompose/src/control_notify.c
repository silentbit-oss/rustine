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


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
}
----------------------------
void control_write(struct client *c, const char *fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  evbuffer_add_vprintf(c->stdout_data, fmt, ap);
  ;
  evbuffer_add(c->stdout_data, "\n", 1);
  server_client_push_stdout(c);
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
}
----------------------------
struct windows
{
  struct window *rbh_root;
}
----------------------------
void control_write(struct client *c, const char *fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  evbuffer_add_vprintf(c->stdout_data, fmt, ap);
  ;
  evbuffer_add(c->stdout_data, "\n", 1);
  server_client_push_stdout(c);
}


----------------------------
struct winlink *winlink_find_by_window_id(struct winlinks *wwl, u_int id)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  for (wl_idx = winlinks_RB_MINMAX(wwl, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    if (wl->window->id == id)
    {
      return wl;
    }
  }

  return 0;
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
}
----------------------------
struct windows
{
  struct window *rbh_root;
}
----------------------------
void control_write(struct client *c, const char *fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  evbuffer_add_vprintf(c->stdout_data, fmt, ap);
  ;
  evbuffer_add(c->stdout_data, "\n", 1);
  server_client_push_stdout(c);
}


----------------------------
struct winlink *winlink_find_by_window_id(struct winlinks *wwl, u_int id)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  for (wl_idx = winlinks_RB_MINMAX(wwl, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    if (wl->window->id == id)
    {
      return wl;
    }
  }

  return 0;
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
}
----------------------------
void control_write(struct client *c, const char *fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  evbuffer_add_vprintf(c->stdout_data, fmt, ap);
  ;
  evbuffer_add(c->stdout_data, "\n", 1);
  server_client_push_stdout(c);
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
}
----------------------------
void control_write(struct client *c, const char *fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  evbuffer_add_vprintf(c->stdout_data, fmt, ap);
  ;
  evbuffer_add(c->stdout_data, "\n", 1);
  server_client_push_stdout(c);
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
}
----------------------------
struct windows
{
  struct window *rbh_root;
}
----------------------------
void control_write(struct client *c, const char *fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  evbuffer_add_vprintf(c->stdout_data, fmt, ap);
  ;
  evbuffer_add(c->stdout_data, "\n", 1);
  server_client_push_stdout(c);
}


----------------------------
struct winlink *winlink_find_by_window_id(struct winlinks *wwl, u_int id)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  for (wl_idx = winlinks_RB_MINMAX(wwl, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    if (wl->window->id == id)
    {
      return wl;
    }
  }

  return 0;
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
}
----------------------------
struct winlink *winlink_find_by_window_id(struct winlinks *wwl, u_int id)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  for (wl_idx = winlinks_RB_MINMAX(wwl, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    if (wl->window->id == id)
    {
      return wl;
    }
  }

  return 0;
}


----------------------------
struct windows
{
  struct window *rbh_root;
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
void control_write(struct client *c, const char *fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  evbuffer_add_vprintf(c->stdout_data, fmt, ap);
  ;
  evbuffer_add(c->stdout_data, "\n", 1);
  server_client_push_stdout(c);
}


----------------------------
struct winlink *winlink_find_by_window(struct winlinks *wwl, struct window *w)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  for (wl_idx = winlinks_RB_MINMAX(wwl, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    if (wl->window == w)
    {
      return wl;
    }
  }

  return 0;
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
}
----------------------------
void control_write(struct client *c, const char *fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  evbuffer_add_vprintf(c->stdout_data, fmt, ap);
  ;
  evbuffer_add(c->stdout_data, "\n", 1);
  server_client_push_stdout(c);
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
}
----------------------------
void control_write(struct client *c, const char *fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  evbuffer_add_vprintf(c->stdout_data, fmt, ap);
  ;
  evbuffer_add(c->stdout_data, "\n", 1);
  server_client_push_stdout(c);
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
}
----------------------------
void control_write(struct client *c, const char *fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  evbuffer_add_vprintf(c->stdout_data, fmt, ap);
  ;
  evbuffer_add(c->stdout_data, "\n", 1);
  server_client_push_stdout(c);
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
}
----------------------------
void control_write(struct client *c, const char *fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  evbuffer_add_vprintf(c->stdout_data, fmt, ap);
  ;
  evbuffer_add(c->stdout_data, "\n", 1);
  server_client_push_stdout(c);
}


----------------------------
None
----------------------------
***/


void control_notify_input(struct client *c, struct window_pane *wp, struct evbuffer *input)
{
  u_char *buf;
  unsigned int buf_idx = 0;
  size_t len;
  struct evbuffer *message;
  unsigned int message_idx = 0;
  u_int i;
  if (c->session == 0)
  {
    return;
  }
  buf_idx = EVBUFFER_DATA(input);
  len = EVBUFFER_LENGTH(input);
  if (winlink_find_by_window(&c->session->windows, wp->window) != 0)
  {
    message_idx = evbuffer_new();
    evbuffer_add_printf(message, "%%output %%%u ", wp->id);
    for (i = 0; i < len; i += 1)
    {
      if ((buf[i + buf_idx] < ' ') || (buf[i + buf_idx] == '\\'))
      {
        evbuffer_add_printf(message, "\\%03o", buf[i + buf_idx]);
      }
      else
        evbuffer_add_printf(message, "%c", buf[i + buf_idx]);
    }

    control_write_buffer(c, message);
    evbuffer_free(message);
  }
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
void control_write_buffer(struct client *c, struct evbuffer *buffer)
{
  evbuffer_add_buffer(c->stdout_data, buffer);
  evbuffer_add(c->stdout_data, "\n", 1);
  server_client_push_stdout(c);
}


----------------------------
struct winlink *winlink_find_by_window(struct winlinks *wwl, struct window *w)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  for (wl_idx = winlinks_RB_MINMAX(wwl, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    if (wl->window == w)
    {
      return wl;
    }
  }

  return 0;
}


----------------------------
None
----------------------------
***/


