void server_status_client(struct client *c)
{
  c->flags |= 0x10;
}


/*** DEPENDENCIES:
None
----------------------------
***/


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


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
}
----------------------------
void server_status_client(struct client *c)
{
  c->flags |= 0x10;
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
int session_has(struct session *s, struct window *w)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  for (wl_idx = (&w->winlinks)->tqh_first; (&wl[wl_idx]) != 0; wl_idx = wl_idx->wentry.tqe_next)
  {
    if (wl->session == s)
    {
      return 1;
    }
  }

  return 0;
}


----------------------------
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
struct sessions
{
  struct session *rbh_root;
}
----------------------------
None
----------------------------
***/


void server_redraw_client(struct client *c)
{
  c->flags |= 0x8;
}


/*** DEPENDENCIES:
None
----------------------------
***/


void server_redraw_window(struct window *w)
{
  struct client *c;
  unsigned int c_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if ((c->session != 0) && (c->session->curw->window == w))
    {
      server_redraw_client(c);
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
void server_redraw_client(struct client *c)
{
  c->flags |= 0x8;
}


----------------------------
None
----------------------------
***/


void server_check_unattached(void)
{
  struct session *s;
  unsigned int s_idx = 0;
  for (s_idx = sessions_RB_MINMAX(&sessions, -1); (&s[s_idx]) != 0; s_idx = sessions_RB_NEXT(s_idx))
  {
    if (!(s->flags & 0x1))
    {
      continue;
    }
    if (options_get_number(s->options, "destroy-unattached"))
    {
      session_destroy(s, __func__);
    }
  }

}


/*** DEPENDENCIES:
struct sessions
{
  struct session *rbh_root;
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
***/


void server_lock_client(struct client *c)
{
  const char *cmd;
  unsigned int cmd_idx = 0;
  if (c->flags & 0x2000)
  {
    return;
  }
  if (c->flags & 0x40)
  {
    return;
  }
  cmd_idx = options_get_string(c->session->options, "lock-command");
  if ((cmd[cmd_idx] == '\0') || ((strlen(cmd) + 1) > (16384 - (sizeof(struct imsg_hdr)))))
  {
    return;
  }
  tty_stop_tty(&c->tty);
  tty_raw(&c->tty, tty_term_string(c->tty.term, TTYC_SMCUP));
  tty_raw(&c->tty, tty_term_string(c->tty.term, TTYC_CLEAR));
  tty_raw(&c->tty, tty_term_string(c->tty.term, TTYC_E3));
  c->flags |= 0x40;
  proc_send(c->peer, MSG_LOCK, -1, cmd, strlen(cmd) + 1);
}


/*** DEPENDENCIES:
void tty_raw(struct tty *tty, const char *s)
{
  unsigned int s_idx = 0;
  ssize_t n;
  ssize_t slen;
  u_int i;
  slen = strlen(s);
  for (i = 0; i < 5; i += 1)
  {
    n = write(tty->fd, s, slen);
    if (n >= 0)
    {
      s_idx += n;
      slen -= n;
      if (slen == 0)
      {
        break;
      }
    }
    else
      if ((n == (-1)) && (errno != EAGAIN))
    {
      break;
    }
    usleep(100);
  }

}


----------------------------
void tty_stop_tty(struct tty *tty)
{
  struct winsize ws;
  if (!(tty->flags & 0x10))
  {
    return;
  }
  tty->flags &= ~0x10;
  event_del(&tty->timer);
  tty->flags &= ~0x80;
  event_del(&tty->event_in);
  event_del(&tty->event_out);
  if (ioctl(tty->fd, TIOCGWINSZ, &ws) == (-1))
  {
    return;
  }
  if (tcsetattr(tty->fd, TCSANOW, &tty->tio) == (-1))
  {
    return;
  }
  tty_raw(tty, tty_term_string2(tty->term, TTYC_CSR, 0, ws.ws_row - 1));
  if (tty_acs_needed(tty))
  {
    tty_raw(tty, tty_term_string(tty->term, TTYC_RMACS));
  }
  tty_raw(tty, tty_term_string(tty->term, TTYC_SGR0));
  tty_raw(tty, tty_term_string(tty->term, TTYC_RMKX));
  tty_raw(tty, tty_term_string(tty->term, TTYC_CLEAR));
  if (tty_term_has(tty->term, TTYC_SS) && (tty->cstyle != 0))
  {
    if (tty_term_has(tty->term, TTYC_SE))
    {
      tty_raw(tty, tty_term_string(tty->term, TTYC_SE));
    }
    else
      tty_raw(tty, tty_term_string1(tty->term, TTYC_SS, 0));
  }
  if (tty->mode & 0x400)
  {
    tty_raw(tty, "\033[?2004l");
  }
  tty_raw(tty, tty_term_string(tty->term, TTYC_CR));
  tty_raw(tty, tty_term_string(tty->term, TTYC_CNORM));
  if (tty_term_has(tty->term, TTYC_KMOUS))
  {
    tty_raw(tty, "\033[?1000l\033[?1002l\033[?1006l\033[?1005l");
  }
  if (tty_term_flag(tty->term, TTYC_XT))
  {
    if (tty->flags & 0x40)
    {
      tty->flags &= ~0x40;
      tty_raw(tty, "\033[?1004l");
    }
  }
  if (tty->term_type == TTY_VT420)
  {
    tty_raw(tty, "\033[?69l");
  }
  tty_raw(tty, tty_term_string(tty->term, TTYC_RMCUP));
  setblocking(tty->fd, 1);
}


----------------------------
None
----------------------------
const char *tty_term_string(struct tty_term *term, enum tty_code_code code)
{
  if (!tty_term_has(term, code))
  {
    return "";
  }
  if (term->codes[code].type != TTYCODE_STRING)
  {
    fatalx("not a string: %d", code);
  }
  return term->codes[code].value.string;
}


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


void server_lock_session(struct session *s)
{
  struct client *c;
  unsigned int c_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (c->session == s)
    {
      server_lock_client(c);
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
void server_lock_client(struct client *c)
{
  const char *cmd;
  unsigned int cmd_idx = 0;
  if (c->flags & 0x2000)
  {
    return;
  }
  if (c->flags & 0x40)
  {
    return;
  }
  cmd_idx = options_get_string(c->session->options, "lock-command");
  if ((cmd[cmd_idx] == '\0') || ((strlen(cmd) + 1) > (16384 - (sizeof(struct imsg_hdr)))))
  {
    return;
  }
  tty_stop_tty(&c->tty);
  tty_raw(&c->tty, tty_term_string(c->tty.term, TTYC_SMCUP));
  tty_raw(&c->tty, tty_term_string(c->tty.term, TTYC_CLEAR));
  tty_raw(&c->tty, tty_term_string(c->tty.term, TTYC_E3));
  c->flags |= 0x40;
  proc_send(c->peer, MSG_LOCK, -1, cmd, strlen(cmd) + 1);
}


----------------------------
None
----------------------------
***/


void server_unzoom_window(struct window *w)
{
  if (window_unzoom(w) == 0)
  {
    server_redraw_window(w);
  }
}


/*** DEPENDENCIES:
int window_unzoom(struct window *w)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  if (!(w->flags & 0x1000))
  {
    return -1;
  }
  w->flags &= ~0x1000;
  layout_free(w);
  w->layout_root = w->saved_layout_root;
  w->saved_layout_root = 0;
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    wp->layout_cell = wp->saved_layout_cell;
    wp->saved_layout_cell = 0;
  }

  layout_fix_panes(w, w->sx, w->sy);
  notify_window("window-layout-changed", w);
  return 0;
}


----------------------------
void server_redraw_window(struct window *w)
{
  struct client *c;
  unsigned int c_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if ((c->session != 0) && (c->session->curw->window == w))
    {
      server_redraw_client(c);
    }
  }

}


----------------------------
None
----------------------------
***/


void helper_server_destroy_pane_1(struct window_pane * const wp, int notify, struct screen_write_ctx ctx, struct grid_cell gc, time_t t, char tim[26])
{
  if ((~wp->flags) & 0x200)
  {
    return;
  }
  if (wp->flags & 0x400)
  {
    return;
  }
  wp->flags |= 0x400;
  if (notify)
  {
    notify_pane("pane-died", wp);
  }
  screen_write_start(&ctx, wp, &wp->base);
  screen_write_scrollregion(&ctx, 0, ctx.s->grid->sy - 1);
  screen_write_cursormove(&ctx, 0, ctx.s->grid->sy - 1);
  screen_write_linefeed(&ctx, 1, 8);
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  time(&t);
  ctime_r(&t, tim);
  if (WIFEXITED(wp->status))
  {
    screen_write_nputs(&ctx, -1, &gc, "Pane is dead (status %d, %s)", WEXITSTATUS(wp->status), tim);
  }
  else
    if (WIFSIGNALED(wp->status))
  {
    screen_write_nputs(&ctx, -1, &gc, "Pane is dead (signal %d, %s)", WTERMSIG(wp->status), tim);
  }
  screen_write_stop(&ctx);
  wp->flags |= 0x1;
  return;
}


/*** DEPENDENCIES:
None
----------------------------
extern const struct grid_cell grid_default_cell
----------------------------
void screen_write_cursormove(struct screen_write_ctx *ctx, u_int px, u_int py)
{
  struct screen *s = ctx->s;
  if (px > (s->grid->sx - 1))
  {
    px = s->grid->sx - 1;
  }
  if (py > (s->grid->sy - 1))
  {
    py = s->grid->sy - 1;
  }
  s->cx = px;
  s->cy = py;
}


----------------------------
pub time: Time
----------------------------
void screen_write_start(struct screen_write_ctx *ctx, struct window_pane *wp, struct screen *s)
{
  char tmp[16];
  u_int y;
  memset(ctx, 0, sizeof(*ctx));
  ctx->wp = wp;
  if ((wp != 0) && (s == 0))
  {
    ctx->s = wp->screen;
  }
  else
    ctx->s = s;
  ctx->list = xcalloc(ctx->s->grid->sy, sizeof(*ctx->list));
  for (y = 0; y < ctx->s->grid->sy; y += 1)
  {
    do
    {
      (&ctx->list[y].items)->tqh_first = 0;
      (&ctx->list[y].items)->tqh_last = &(&ctx->list[y].items)->tqh_first;
    }
    while (0);
  }

  ctx->item = xcalloc(1, sizeof(*ctx->item));
  ctx->scrolled = 0;
  ctx->bg = 8;
  if (wp != 0)
  {
    snprintf(tmp, sizeof(tmp), "pane %%%u", wp->id);
  }
  log_debug("%s: size %ux%u, %s", __func__, ctx->s->grid->sx, ctx->s->grid->sy, (wp == 0) ? ("no pane") : (tmp));
}


----------------------------
void screen_write_stop(struct screen_write_ctx *ctx)
{
  screen_write_collect_end(ctx);
  screen_write_collect_flush(ctx, 0);
  log_debug("%s: %u cells (%u written, %u skipped)", __func__, ctx->cells, ctx->written, ctx->skipped);
  free(ctx->item);
  free(ctx->list);
}


----------------------------
None
----------------------------
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
void screen_write_linefeed(struct screen_write_ctx *ctx, int wrapped, u_int bg)
{
  struct screen *s = ctx->s;
  struct grid *gd = s->grid;
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  gl_idx = &gd->linedata[gd->hsize + s->cy];
  if (wrapped)
  {
    gl->flags |= 0x1;
  }
  else
    gl->flags &= ~0x1;
  log_debug("%s: at %u,%u (region %u-%u)", __func__, s->cx, s->cy, s->rupper, s->rlower);
  if (bg != ctx->bg)
  {
    screen_write_collect_flush(ctx, 1);
    ctx->bg = bg;
  }
  if (s->cy == s->rlower)
  {
    grid_view_scroll_region_up(gd, s->rupper, s->rlower, bg);
    screen_write_collect_scroll(ctx);
    ctx->scrolled += 1;
  }
  else
    if (s->cy < (s->grid->sy - 1))
  {
    s->cy += 1;
  }
}


----------------------------
void screen_write_nputs(struct screen_write_ctx *ctx, ssize_t maxlen, const struct grid_cell *gcp, const char *fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  screen_write_vnputs(ctx, maxlen, gcp, fmt, ap);
  ;
}


----------------------------
None
----------------------------
void screen_write_scrollregion(struct screen_write_ctx *ctx, u_int rupper, u_int rlower)
{
  struct screen *s = ctx->s;
  if (rupper > (s->grid->sy - 1))
  {
    rupper = s->grid->sy - 1;
  }
  if (rlower > (s->grid->sy - 1))
  {
    rlower = s->grid->sy - 1;
  }
  if (rupper >= rlower)
  {
    return;
  }
  screen_write_collect_flush(ctx, 0);
  s->cx = 0;
  s->cy = 0;
  s->rupper = rupper;
  s->rlower = rlower;
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
}
----------------------------
void server_redraw_client(struct client *c)
{
  c->flags |= 0x8;
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
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
struct sessions
{
  struct session *rbh_root;
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
None
----------------------------
***/


static struct session *server_next_session(struct session *s)
{
  struct session *s_loop;
  unsigned int s_loop_idx = 0;
  struct session *s_out;
  unsigned int s_out_idx = 0;
  s_out_idx = 0;
  for (s_loop_idx = sessions_RB_MINMAX(&sessions, -1); (&s_loop[s_loop_idx]) != 0; s_loop_idx = sessions_RB_NEXT(s_loop_idx))
  {
    if ((&s_loop[s_loop_idx]) == s)
    {
      continue;
    }
    if (((&s_out[s_out_idx]) == 0) || (((&s_loop->activity_time)->tv_sec == (&s_out->activity_time)->tv_sec) ? ((&s_loop->activity_time)->tv_usec < (&s_out->activity_time)->tv_usec) : ((&s_loop->activity_time)->tv_sec < (&s_out->activity_time)->tv_sec)))
    {
      s_out_idx = &s_loop[s_loop_idx];
    }
  }

  return s_out;
}


/*** DEPENDENCIES:
struct sessions
{
  struct session *rbh_root;
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
None
----------------------------
***/


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


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
}
----------------------------
void notify_client(const char *name, struct client *c)
{
  struct cmd_find_state fs;
  cmd_find_from_client(&fs, c, 0);
  notify_add(name, &fs, c, 0, 0, 0);
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
void server_redraw_client(struct client *c)
{
  c->flags |= 0x8;
}


----------------------------
static struct session *server_next_session(struct session *s)
{
  struct session *s_loop;
  unsigned int s_loop_idx = 0;
  struct session *s_out;
  unsigned int s_out_idx = 0;
  s_out_idx = 0;
  for (s_loop_idx = sessions_RB_MINMAX(&sessions, -1); (&s_loop[s_loop_idx]) != 0; s_loop_idx = sessions_RB_NEXT(s_loop_idx))
  {
    if ((&s_loop[s_loop_idx]) == s)
    {
      continue;
    }
    if (((&s_out[s_out_idx]) == 0) || (((&s_loop->activity_time)->tv_sec == (&s_out->activity_time)->tv_sec) ? ((&s_loop->activity_time)->tv_usec < (&s_out->activity_time)->tv_usec) : ((&s_loop->activity_time)->tv_sec < (&s_out->activity_time)->tv_sec)))
    {
      s_out_idx = &s_loop[s_loop_idx];
    }
  }

  return s_out;
}


----------------------------
void alerts_check_session(struct session *s)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  for (wl_idx = winlinks_RB_MINMAX(&s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    alerts_check_all(wl->window);
  }

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
void status_timer_start(struct client *c)
{
  struct session *s = c->session;
  if (event_initialized(&c->status.timer))
  {
    evtimer_del(&c->status.timer);
  }
  else
    evtimer_set(&c->status.timer, status_timer_callback, c);
  if ((s != 0) && options_get_number(s->options, "status"))
  {
    status_timer_callback(-1, 0, c);
  }
}


----------------------------
void session_update_activity(struct session *s, struct timeval *from)
{
  struct timeval *last = &s->last_activity_time;
  struct timeval tv;
  memcpy(last, &s->activity_time, sizeof(*last));
  if (from == 0)
  {
    gettimeofday(&s->activity_time, 0);
  }
  else
    memcpy(&s->activity_time, from, sizeof(s->activity_time));
  log_debug("session %s activity %lld.%06d (last %lld.%06d)", s->name, (long long) s->activity_time.tv_sec, (int) s->activity_time.tv_usec, (long long) last->tv_sec, (int) last->tv_usec);
  if (evtimer_initialized(&s->lock_timer))
  {
    evtimer_del(&s->lock_timer);
  }
  else
    evtimer_set(&s->lock_timer, session_lock_timer, s);
  if ((~s->flags) & 0x1)
  {
    timerclear(&tv);
    tv.tv_sec = options_get_number(s->options, "lock-after-time");
    if (tv.tv_sec != 0)
    {
      evtimer_add(&s->lock_timer, &tv);
    }
  }
}


----------------------------
void server_client_set_key_table(struct client *c, const char *name)
{
  unsigned int name_idx = 0;
  if ((&name[name_idx]) == 0)
  {
    name_idx = server_client_get_key_table(c);
  }
  key_bindings_unref_table(c->keytable);
  c->keytable = key_bindings_get_table(name, 1);
  c->keytable->references += 1;
}


----------------------------
None
----------------------------
***/


static void server_destroy_session_group(struct session *s)
{
  unsigned int s_idx = 0;
  struct session_group *sg;
  unsigned int sg_idx = 0;
  struct session *s1;
  unsigned int s1_idx = 0;
  if ((sg_idx = session_group_contains(s)) == 0)
  {
    server_destroy_session(s);
  }
  else
  {
    for (s_idx = (&sg->sessions)->tqh_first; ((&s[s_idx]) != 0) && ((s1_idx = s->gentry.tqe_next, 1)); s_idx = &s1[s1_idx])
    {
      server_destroy_session(s);
      session_destroy(s, __func__);
    }

  }
}


/*** DEPENDENCIES:
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
struct sessions
{
  struct session *rbh_root;
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
None
----------------------------
***/


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


/*** DEPENDENCIES:
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
int session_has(struct session *s, struct window *w)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  for (wl_idx = (&w->winlinks)->tqh_first; (&wl[wl_idx]) != 0; wl_idx = wl_idx->wentry.tqe_next)
  {
    if (wl->session == s)
    {
      return 1;
    }
  }

  return 0;
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
void session_renumber_windows(struct session *s)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct winlink *wl1;
  unsigned int wl1_idx = 0;
  struct winlink *wl_new;
  unsigned int wl_new_idx = 0;
  struct winlinks old_wins;
  struct winlink_stack old_lastw;
  int new_idx;
  int new_curw_idx;
  memcpy(&old_wins, &s->windows, sizeof(old_wins));
  do
  {
    (&s->windows)->rbh_root = 0;
  }
  while (0);
  new_idx = options_get_number(s->options, "base-index");
  new_curw_idx = 0;
  for (wl_idx = winlinks_RB_MINMAX(&old_wins, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    wl_new_idx = winlink_add(&s->windows, new_idx);
    wl_new->session = s;
    winlink_set_window(wl_new, wl->window);
    wl_new->flags |= wl->flags & ((0x1 | 0x2) | 0x4);
    if ((&wl[wl_idx]) == s->curw)
    {
      new_curw_idx = wl_new->idx;
    }
    new_idx += 1;
  }

  memcpy(&old_lastw, &s->lastw, sizeof(old_lastw));
  do
  {
    (&s->lastw)->tqh_first = 0;
    (&s->lastw)->tqh_last = &(&s->lastw)->tqh_first;
  }
  while (0);
  for (wl_idx = (&old_lastw)->tqh_first; (&wl[wl_idx]) != 0; wl_idx = wl_idx->sentry.tqe_next)
  {
    wl_new_idx = winlink_find_by_window(&s->windows, wl->window);
    if ((&wl_new[wl_new_idx]) != 0)
    {
      do
      {
        wl_new->sentry.tqe_next = 0;
        wl_new->sentry.tqe_prev = (&s->lastw)->tqh_last;
        *(&s->lastw)->tqh_last = &wl_new[wl_new_idx];
        (&s->lastw)->tqh_last = &wl_new->sentry.tqe_next;
      }
      while (0);
    }
  }

  s->curw = winlink_find_by_index(&s->windows, new_curw_idx);
  for (wl_idx = winlinks_RB_MINMAX(&old_wins, -1); ((&wl[wl_idx]) != 0) && ((wl1_idx = winlinks_RB_NEXT(wl), 1)); wl_idx = &wl1[wl1_idx])
  {
    winlink_remove(&old_wins, wl);
  }

}


----------------------------
int session_detach(struct session *s, struct winlink *wl)
{
  if (((s->curw == wl) && (session_last(s) != 0)) && (session_previous(s, 0) != 0))
  {
    session_next(s, 0);
  }
  wl->flags &= ~((0x1 | 0x2) | 0x4);
  notify_session_window("window-unlinked", s, wl->window);
  winlink_stack_remove(&s->lastw, wl);
  winlink_remove(&s->windows, wl);
  session_group_synchronize_from(s);
  if ((&s->windows)->rbh_root == 0)
  {
    session_destroy(s, __func__);
    return 1;
  }
  return 0;
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
struct sessions
{
  struct session *rbh_root;
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
static void server_destroy_session_group(struct session *s)
{
  unsigned int s_idx = 0;
  struct session_group *sg;
  unsigned int sg_idx = 0;
  struct session *s1;
  unsigned int s1_idx = 0;
  if ((sg_idx = session_group_contains(s)) == 0)
  {
    server_destroy_session(s);
  }
  else
  {
    for (s_idx = (&sg->sessions)->tqh_first; ((&s[s_idx]) != 0) && ((s1_idx = s->gentry.tqe_next, 1)); s_idx = &s1[s1_idx])
    {
      server_destroy_session(s);
      session_destroy(s, __func__);
    }

  }
}


----------------------------
None
----------------------------
***/


void server_destroy_pane(struct window_pane *wp, int notify)
{
  struct window *w = wp->window;
  struct screen_write_ctx ctx;
  struct grid_cell gc;
  time_t t;
  char tim[26];
  if (wp->fd != (-1))
  {
    bufferevent_free(wp->event);
    close(wp->fd);
    wp->fd = -1;
  }
  if (options_get_number(w->options, "remain-on-exit"))
  {
    helper_server_destroy_pane_1(wp, notify, ctx, gc, t, tim);
  }
  if (notify)
  {
    notify_pane("pane-exited", wp);
  }
  server_unzoom_window(w);
  layout_close_pane(wp);
  window_remove_pane(w, wp);
  if ((&w->panes)->tqh_first == 0)
  {
    server_kill_window(w);
  }
  else
    server_redraw_window(w);
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
None
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
None
----------------------------
void server_redraw_window(struct window *w)
{
  struct client *c;
  unsigned int c_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if ((c->session != 0) && (c->session->curw->window == w))
    {
      server_redraw_client(c);
    }
  }

}


----------------------------
void helper_server_destroy_pane_1(struct window_pane * const wp, int notify, struct screen_write_ctx ctx, struct grid_cell gc, time_t t, char tim[26])
{
  if ((~wp->flags) & 0x200)
  {
    return;
  }
  if (wp->flags & 0x400)
  {
    return;
  }
  wp->flags |= 0x400;
  if (notify)
  {
    notify_pane("pane-died", wp);
  }
  screen_write_start(&ctx, wp, &wp->base);
  screen_write_scrollregion(&ctx, 0, ctx.s->grid->sy - 1);
  screen_write_cursormove(&ctx, 0, ctx.s->grid->sy - 1);
  screen_write_linefeed(&ctx, 1, 8);
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  time(&t);
  ctime_r(&t, tim);
  if (WIFEXITED(wp->status))
  {
    screen_write_nputs(&ctx, -1, &gc, "Pane is dead (status %d, %s)", WEXITSTATUS(wp->status), tim);
  }
  else
    if (WIFSIGNALED(wp->status))
  {
    screen_write_nputs(&ctx, -1, &gc, "Pane is dead (signal %d, %s)", WTERMSIG(wp->status), tim);
  }
  screen_write_stop(&ctx);
  wp->flags |= 0x1;
  return;
}


----------------------------
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
void window_remove_pane(struct window *w, struct window_pane *wp)
{
  window_lost_pane(w, wp);
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
None
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
None
----------------------------
***/


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


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
}
----------------------------
None
----------------------------
***/


void server_lock(void)
{
  struct client *c;
  unsigned int c_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (c->session != 0)
    {
      server_lock_client(c);
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
void server_lock_client(struct client *c)
{
  const char *cmd;
  unsigned int cmd_idx = 0;
  if (c->flags & 0x2000)
  {
    return;
  }
  if (c->flags & 0x40)
  {
    return;
  }
  cmd_idx = options_get_string(c->session->options, "lock-command");
  if ((cmd[cmd_idx] == '\0') || ((strlen(cmd) + 1) > (16384 - (sizeof(struct imsg_hdr)))))
  {
    return;
  }
  tty_stop_tty(&c->tty);
  tty_raw(&c->tty, tty_term_string(c->tty.term, TTYC_SMCUP));
  tty_raw(&c->tty, tty_term_string(c->tty.term, TTYC_CLEAR));
  tty_raw(&c->tty, tty_term_string(c->tty.term, TTYC_E3));
  c->flags |= 0x40;
  proc_send(c->peer, MSG_LOCK, -1, cmd, strlen(cmd) + 1);
}


----------------------------
None
----------------------------
***/


int server_set_stdin_callback(struct client *c, void (*cb)(struct client *, int, void *), void *cb_data, char **cause)
{
  if ((c == 0) || (c->session != 0))
  {
    *cause = xstrdup("no client with stdin");
    return -1;
  }
  if (c->flags & 0x1)
  {
    *cause = xstrdup("stdin is a tty");
    return -1;
  }
  if (c->stdin_callback != 0)
  {
    *cause = xstrdup("stdin in use");
    return -1;
  }
  c->stdin_callback_data = cb_data;
  c->stdin_callback = cb;
  c->references += 1;
  if (c->stdin_closed)
  {
    c->stdin_callback(c, 1, c->stdin_callback_data);
  }
  proc_send(c->peer, MSG_STDIN, -1, 0, 0);
  return 0;
}


/*** DEPENDENCIES:
None
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
None
----------------------------
***/


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


/*** DEPENDENCIES:
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
struct sessions
{
  struct session *rbh_root;
}
----------------------------
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
None
----------------------------
***/


void server_unlink_window(struct session *s, struct winlink *wl)
{
  if (session_detach(s, wl))
  {
    server_destroy_session_group(s);
  }
  else
    server_redraw_session_group(s);
}


/*** DEPENDENCIES:
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
static void server_destroy_session_group(struct session *s)
{
  unsigned int s_idx = 0;
  struct session_group *sg;
  unsigned int sg_idx = 0;
  struct session *s1;
  unsigned int s1_idx = 0;
  if ((sg_idx = session_group_contains(s)) == 0)
  {
    server_destroy_session(s);
  }
  else
  {
    for (s_idx = (&sg->sessions)->tqh_first; ((&s[s_idx]) != 0) && ((s1_idx = s->gentry.tqe_next, 1)); s_idx = &s1[s1_idx])
    {
      server_destroy_session(s);
      session_destroy(s, __func__);
    }

  }
}


----------------------------
int session_detach(struct session *s, struct winlink *wl)
{
  if (((s->curw == wl) && (session_last(s) != 0)) && (session_previous(s, 0) != 0))
  {
    session_next(s, 0);
  }
  wl->flags &= ~((0x1 | 0x2) | 0x4);
  notify_session_window("window-unlinked", s, wl->window);
  winlink_stack_remove(&s->lastw, wl);
  winlink_remove(&s->windows, wl);
  session_group_synchronize_from(s);
  if ((&s->windows)->rbh_root == 0)
  {
    session_destroy(s, __func__);
    return 1;
  }
  return 0;
}


----------------------------
None
----------------------------
***/


// hint:  ['selectflag_ref is a mutable refrence to int']
int helper_server_link_window_1(int * const selectflag_ref, struct winlink * const srcwl, struct session * const dst, int dstidx, int killflag, char ** const cause, struct winlink * const dstwl, unsigned int dstwl_idx)
{
  int selectflag = *selectflag_ref;
  if (dstwl->window == srcwl->window)
  {
    xasprintf(cause, "same index: %d", dstidx);
    return -1;
  }
  if (killflag)
  {
    notify_session_window("window-unlinked", dst, dstwl->window);
    dstwl->flags &= ~((0x1 | 0x2) | 0x4);
    winlink_stack_remove(&dst->lastw, dstwl);
    winlink_remove(&dst->windows, dstwl);
    if ((&dstwl[dstwl_idx]) == dst->curw)
    {
      selectflag = 1;
      dst->curw = 0;
    }
  }
  *selectflag_ref = selectflag;
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
void winlink_stack_remove(struct winlink_stack *stack, struct winlink *wl)
{
  struct winlink *wl2;
  unsigned int wl2_idx = 0;
  if (wl == 0)
  {
    return;
  }
  for (wl2_idx = stack->tqh_first; (&wl2[wl2_idx]) != 0; wl2_idx = wl2_idx->sentry.tqe_next)
  {
    if ((&wl2[wl2_idx]) == wl)
    {
      do
      {
        if (wl->sentry.tqe_next != 0)
        {
          wl->sentry.tqe_next->sentry.tqe_prev = wl->sentry.tqe_prev;
        }
        else
          stack->tqh_last = wl->sentry.tqe_prev;
        *wl->sentry.tqe_prev = wl->sentry.tqe_next;
        ;
        ;
      }
      while (0);
      return;
    }
  }

}


----------------------------
void winlink_remove(struct winlinks *wwl, struct winlink *wl)
{
  struct window *w = wl->window;
  if (w != 0)
  {
    do
    {
      if (wl->wentry.tqe_next != 0)
      {
        wl->wentry.tqe_next->wentry.tqe_prev = wl->wentry.tqe_prev;
      }
      else
        (&w->winlinks)->tqh_last = wl->wentry.tqe_prev;
      *wl->wentry.tqe_prev = wl->wentry.tqe_next;
      ;
      ;
    }
    while (0);
    window_remove_ref(w, __func__);
  }
  winlinks_RB_REMOVE(wwl, wl);
  free(wl->status_text);
  free(wl);
}


----------------------------
int xasprintf(char **ret, const char *fmt, ...)
{
  va_list ap;
  int i;
  __builtin_va_start(ap);
  i = xvasprintf(ret, fmt, ap);
  ;
  return i;
}


----------------------------
void notify_session_window(const char *name, struct session *s, struct window *w)
{
  struct cmd_find_state fs;
  cmd_find_from_session_window(&fs, s, w, 0);
  notify_add(name, &fs, 0, s, w, 0);
}


----------------------------
None
----------------------------
***/


int server_link_window(struct session *src, struct winlink *srcwl, struct session *dst, int dstidx, int killflag, int selectflag, char **cause)
{
  struct winlink *dstwl;
  unsigned int dstwl_idx = 0;
  struct session_group *srcsg;
  unsigned int srcsg_idx = 0;
  struct session_group *dstsg;
  unsigned int dstsg_idx = 0;
  srcsg_idx = session_group_contains(src);
  dstsg_idx = session_group_contains(dst);
  if ((((src != dst) && ((&srcsg[srcsg_idx]) != 0)) && ((&dstsg[dstsg_idx]) != 0)) && ((&srcsg[srcsg_idx]) == (&dstsg[dstsg_idx])))
  {
    xasprintf(cause, "sessions are grouped");
    return -1;
  }
  dstwl_idx = 0;
  if (dstidx != (-1))
  {
    dstwl_idx = winlink_find_by_index(&dst->windows, dstidx);
  }
  if ((&dstwl[dstwl_idx]) != 0)
  {
    helper_server_link_window_1(&selectflag, srcwl, dst, dstidx, killflag, cause, dstwl, dstwl_idx);
  }
  if (dstidx == (-1))
  {
    dstidx = (-1) - options_get_number(dst->options, "base-index");
  }
  dstwl_idx = session_attach(dst, srcwl->window, dstidx, cause);
  if ((&dstwl[dstwl_idx]) == 0)
  {
    return -1;
  }
  if (selectflag)
  {
    session_select(dst, dstwl->idx);
  }
  server_redraw_session_group(dst);
  return 0;
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
struct windows
{
  struct window *rbh_root;
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
int xasprintf(char **ret, const char *fmt, ...)
{
  va_list ap;
  int i;
  __builtin_va_start(ap);
  i = xvasprintf(ret, fmt, ap);
  ;
  return i;
}


----------------------------
int helper_server_link_window_1(int * const selectflag_ref, struct winlink * const srcwl, struct session * const dst, int dstidx, int killflag, char ** const cause, struct winlink * const dstwl, unsigned int dstwl_idx)
{
  int selectflag = *selectflag_ref;
  if (dstwl->window == srcwl->window)
  {
    xasprintf(cause, "same index: %d", dstidx);
    return -1;
  }
  if (killflag)
  {
    notify_session_window("window-unlinked", dst, dstwl->window);
    dstwl->flags &= ~((0x1 | 0x2) | 0x4);
    winlink_stack_remove(&dst->lastw, dstwl);
    winlink_remove(&dst->windows, dstwl);
    if ((&dstwl[dstwl_idx]) == dst->curw)
    {
      selectflag = 1;
      dst->curw = 0;
    }
  }
  *selectflag_ref = selectflag;
}


----------------------------
None
----------------------------
***/


void server_kill_pane(struct window_pane *wp)
{
  struct window *w = wp->window;
  if (window_count_panes(w) == 1)
  {
    server_kill_window(w);
    recalculate_sizes();
  }
  else
  {
    server_unzoom_window(w);
    layout_close_pane(wp);
    window_remove_pane(w, wp);
    server_redraw_window(w);
  }
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
void server_redraw_window(struct window *w)
{
  struct client *c;
  unsigned int c_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if ((c->session != 0) && (c->session->curw->window == w))
    {
      server_redraw_client(c);
    }
  }

}


----------------------------
void window_remove_pane(struct window *w, struct window_pane *wp)
{
  window_lost_pane(w, wp);
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
None
----------------------------
***/


