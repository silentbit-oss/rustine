static void input_ground(struct input_ctx *ictx)
{
  event_del(&ictx->timer);
  evbuffer_drain(ictx->since_ground, EVBUFFER_LENGTH(ictx->since_ground));
  if (ictx->input_space > 32)
  {
    ictx->input_space = 32;
    ictx->input_buf = xrealloc(ictx->input_buf, 32);
  }
}


/*** DEPENDENCIES:
void *xrealloc(void *ptr, size_t size)
{
  return xreallocarray(ptr, 1, size);
}


----------------------------
None
----------------------------
***/


static void input_clear(struct input_ctx *ictx)
{
  event_del(&ictx->timer);
  *ictx->interm_buf = '\0';
  ictx->interm_len = 0;
  *ictx->param_buf = '\0';
  ictx->param_len = 0;
  *ictx->input_buf = '\0';
  ictx->input_len = 0;
  ictx->flags &= ~0x1;
}


/*** DEPENDENCIES:
None
----------------------------
***/


static void input_start_timer(struct input_ctx *ictx)
{
  struct timeval tv = {.tv_usec = 100000};
  event_del(&ictx->timer);
  event_add(&ictx->timer, &tv);
}


/*** DEPENDENCIES:
None
----------------------------
***/


static void input_enter_dcs(struct input_ctx *ictx)
{
  log_debug("%s", __func__);
  input_clear(ictx);
  input_start_timer(ictx);
  ictx->last = -1;
}


/*** DEPENDENCIES:
static void input_clear(struct input_ctx *ictx)
{
  event_del(&ictx->timer);
  *ictx->interm_buf = '\0';
  ictx->interm_len = 0;
  *ictx->param_buf = '\0';
  ictx->param_len = 0;
  *ictx->input_buf = '\0';
  ictx->input_len = 0;
  ictx->flags &= ~0x1;
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
static void input_start_timer(struct input_ctx *ictx)
{
  struct timeval tv = {.tv_usec = 100000};
  event_del(&ictx->timer);
  event_add(&ictx->timer, &tv);
}


----------------------------
None
----------------------------
***/


static void input_enter_rename(struct input_ctx *ictx)
{
  log_debug("%s", __func__);
  input_clear(ictx);
  input_start_timer(ictx);
  ictx->last = -1;
}


/*** DEPENDENCIES:
static void input_clear(struct input_ctx *ictx)
{
  event_del(&ictx->timer);
  *ictx->interm_buf = '\0';
  ictx->interm_len = 0;
  *ictx->param_buf = '\0';
  ictx->param_len = 0;
  *ictx->input_buf = '\0';
  ictx->input_len = 0;
  ictx->flags &= ~0x1;
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
static void input_start_timer(struct input_ctx *ictx)
{
  struct timeval tv = {.tv_usec = 100000};
  event_del(&ictx->timer);
  event_add(&ictx->timer, &tv);
}


----------------------------
None
----------------------------
***/


static void input_enter_osc(struct input_ctx *ictx)
{
  log_debug("%s", __func__);
  input_clear(ictx);
  input_start_timer(ictx);
  ictx->last = -1;
}


/*** DEPENDENCIES:
static void input_clear(struct input_ctx *ictx)
{
  event_del(&ictx->timer);
  *ictx->interm_buf = '\0';
  ictx->interm_len = 0;
  *ictx->param_buf = '\0';
  ictx->param_len = 0;
  *ictx->input_buf = '\0';
  ictx->input_len = 0;
  ictx->flags &= ~0x1;
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
static void input_start_timer(struct input_ctx *ictx)
{
  struct timeval tv = {.tv_usec = 100000};
  event_del(&ictx->timer);
  event_add(&ictx->timer, &tv);
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
None
----------------------------
***/


static void input_osc_52(struct window_pane *wp, const char *p)
{
  char *end;
  unsigned int end_idx = 0;
  size_t len;
  u_char *out;
  unsigned int out_idx = 0;
  int outlen;
  int state;
  struct screen_write_ctx ctx;
  state = options_get_number(global_options, "set-clipboard");
  if (state != 2)
  {
    return;
  }
  if ((end_idx = strchr(p, ';')) == 0)
  {
    return;
  }
  end_idx += 1;
  if (end[end_idx] == '\0')
  {
    return;
  }
  len = (strlen(end) / 4) * 3;
  if (len == 0)
  {
    return;
  }
  out_idx = xmalloc(len);
  if ((outlen = b64_pton(end, out, len)) == (-1))
  {
    free(out);
    return;
  }
  screen_write_start(&ctx, wp, 0);
  screen_write_setselection(&ctx, out, outlen);
  screen_write_stop(&ctx);
  notify_pane("pane-set-clipboard", wp);
  paste_add(out, outlen);
}


/*** DEPENDENCIES:
void screen_write_setselection(struct screen_write_ctx *ctx, u_char *str, u_int len)
{
  struct tty_ctx ttyctx;
  screen_write_initctx(ctx, &ttyctx);
  ttyctx.ptr = str;
  ttyctx.num = len;
  tty_write(tty_cmd_setselection, &ttyctx);
}


----------------------------
None
----------------------------
void *xmalloc(size_t size)
{
  void *ptr;
  unsigned int ptr_idx = 0;
  if (size == 0)
  {
    fatalx("xmalloc: zero size");
  }
  ptr_idx = malloc(size);
  if ((&ptr[ptr_idx]) == 0)
  {
    fatalx("xmalloc: allocating %zu bytes: %s", size, strerror(errno));
  }
  return ptr;
}


----------------------------
void paste_add(char *data, size_t size)
{
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  struct paste_buffer *pb1;
  unsigned int pb1_idx = 0;
  u_int limit;
  if (size == 0)
  {
    free(data);
    return;
  }
  limit = options_get_number(global_options, "buffer-limit");
  for (pb_idx = paste_time_tree_RB_MINMAX(&paste_by_time, 1); ((&pb[pb_idx]) != 0) && ((pb1_idx = paste_time_tree_RB_PREV(pb), 1)); pb_idx = &pb1[pb1_idx])
  {
    if (paste_num_automatic < limit)
    {
      break;
    }
    if (pb->automatic)
    {
      paste_free(pb);
    }
  }

  pb_idx = xmalloc(sizeof(*pb_idx));
  pb->name = 0;
  do
  {
    free(pb->name);
    xasprintf(&pb->name, "buffer%04u", paste_next_index);
    paste_next_index += 1;
  }
  while (paste_get_name(pb->name) != 0);
  pb->data = data;
  pb->size = size;
  pb->automatic = 1;
  paste_num_automatic += 1;
  pb->created = time(0);
  pb->order = paste_next_order;
  paste_next_order += 1;
  paste_name_tree_RB_INSERT(&paste_by_name, pb);
  paste_time_tree_RB_INSERT(&paste_by_time, pb);
}


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
None
----------------------------
***/


static void input_osc_104(struct window_pane *wp, const char *p)
{
  char *copy;
  unsigned int copy_idx = 0;
  char *s;
  unsigned int s_idx = 0;
  long idx;
  if ((*p) == '\0')
  {
    window_pane_reset_palette(wp);
    return;
  }
  copy_idx = (s = &s[s_idx + s_idx]);
  while (s[s_idx] != '\0')
  {
    idx = strtol(s, &(&s[s_idx]), 10);
    if ((s[s_idx] != '\0') && (s[s_idx] != ';'))
    {
      goto bad;
    }
    if ((idx < 0) || (idx >= 0x100))
    {
      goto bad;
    }
    window_pane_unset_palette(wp, idx);
    if (s[s_idx] == ';')
    {
      s_idx += 1;
    }
  }

  free(copy);
  return;
  bad:
  log_debug("bad OSC 104: %s", p);

  free(copy);
}


/*** DEPENDENCIES:
void window_pane_reset_palette(struct window_pane *wp)
{
  if (wp->palette == 0)
  {
    return;
  }
  free(wp->palette);
  wp->palette = 0;
  wp->flags |= 0x1;
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
void window_pane_unset_palette(struct window_pane *wp, u_int n)
{
  if ((n > 0xff) || (wp->palette == 0))
  {
    return;
  }
  wp->palette[n] = 0;
  wp->flags |= 0x1;
}


----------------------------
None
----------------------------
***/


static void input_osc_4(struct window_pane *wp, const char *p)
{
  char *copy;
  unsigned int copy_idx = 0;
  char *s;
  unsigned int s_idx = 0;
  char *next = 0;
  long idx;
  u_int r;
  u_int g;
  u_int b;
  copy_idx = (s = &s[s_idx + s_idx]);
  while (((&s[s_idx]) != 0) && (s[s_idx] != '\0'))
  {
    idx = strtol(s, &next, 10);
    if ((*(next++)) != ';')
    {
      goto bad;
    }
    if ((idx < 0) || (idx >= 0x100))
    {
      goto bad;
    }
    s_idx = strsep(&next, ";");
    if (sscanf(s, "rgb:%2x/%2x/%2x", &r, &g, &b) != 3)
    {
      s_idx = next;
      continue;
    }
    window_pane_set_palette(wp, idx, colour_join_rgb(r, g, b));
    s_idx = next;
  }

  free(copy);
  return;
  bad:
  log_debug("bad OSC 4: %s", p);

  free(copy);
}


/*** DEPENDENCIES:
int colour_join_rgb(u_char r, u_char g, u_char b)
{
  return (((((int) (r & 0xff)) << 16) | (((int) (g & 0xff)) << 8)) | ((int) (b & 0xff))) | 0x02000000;
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
void window_pane_set_palette(struct window_pane *wp, u_int n, int colour)
{
  if (n > 0xff)
  {
    return;
  }
  if (wp->palette == 0)
  {
    wp->palette = xcalloc(0x100, sizeof(*wp->palette));
  }
  wp->palette[n] = colour;
  wp->flags |= 0x1;
}


----------------------------
None
----------------------------
***/


static void input_osc_11(struct window_pane *wp, const char *p)
{
  u_int r;
  u_int g;
  u_int b;
  if (sscanf(p, "rgb:%2x/%2x/%2x", &r, &g, &b) != 3)
  {
    goto bad;
  }
  wp->colgc.bg = colour_join_rgb(r, g, b);
  wp->flags |= 0x1;
  return;
  bad:
  log_debug("bad OSC 11: %s", p);

}


/*** DEPENDENCIES:
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
int colour_join_rgb(u_char r, u_char g, u_char b)
{
  return (((((int) (r & 0xff)) << 16) | (((int) (g & 0xff)) << 8)) | ((int) (b & 0xff))) | 0x02000000;
}


----------------------------
None
----------------------------
***/


static void input_osc_10(struct window_pane *wp, const char *p)
{
  u_int r;
  u_int g;
  u_int b;
  if (sscanf(p, "rgb:%2x/%2x/%2x", &r, &g, &b) != 3)
  {
    goto bad;
  }
  wp->colgc.fg = colour_join_rgb(r, g, b);
  wp->flags |= 0x1;
  return;
  bad:
  log_debug("bad OSC 10: %s", p);

}


/*** DEPENDENCIES:
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
int colour_join_rgb(u_char r, u_char g, u_char b)
{
  return (((((int) (r & 0xff)) << 16) | (((int) (g & 0xff)) << 8)) | ((int) (b & 0xff))) | 0x02000000;
}


----------------------------
None
----------------------------
***/


static void input_exit_osc(struct input_ctx *ictx)
{
  u_char *p = ictx->input_buf;
  unsigned int p_idx = 0;
  u_int option;
  if (ictx->flags & 0x1)
  {
    return;
  }
  if (((ictx->input_len < 1) || (p[p_idx] < '0')) || (p[p_idx] > '9'))
  {
    return;
  }
  log_debug("%s: \"%s\"", __func__, p);
  option = 0;
  while ((p[p_idx] >= '0') && (p[p_idx] <= '9'))
  {
    option = ((option * 10) + p[p_idx]) - '0';
    p_idx += 1;
  }

  if (p[p_idx] == ';')
  {
    p_idx += 1;
  }
  switch (option)
  {
    case 0:

    case 2:
    {
      if (utf8_isvalid(p))
      {
        screen_set_title(ictx->ctx.s, p);
        server_status_window(ictx->wp->window);
      }
      break;
    }

    case 4:
    {
      input_osc_4(ictx->wp, p);
      break;
    }

    case 10:
    {
      input_osc_10(ictx->wp, p);
      break;
    }

    case 11:
    {
      input_osc_11(ictx->wp, p);
      break;
    }

    case 12:
    {
      if (utf8_isvalid(p) && (p[p_idx] != '?'))
      {
        screen_set_cursor_colour(ictx->ctx.s, p);
      }
      break;
    }

    case 52:
    {
      input_osc_52(ictx->wp, p);
      break;
    }

    case 104:
    {
      input_osc_104(ictx->wp, p);
      break;
    }

    case 112:
    {
      if (p[p_idx] == '\0')
      {
        screen_set_cursor_colour(ictx->ctx.s, "");
      }
      break;
    }

    default:
    {
      log_debug("%s: unknown '%u'", __func__, option);
      break;
    }

  }

}


/*** DEPENDENCIES:
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
static void input_osc_52(struct window_pane *wp, const char *p)
{
  char *end;
  unsigned int end_idx = 0;
  size_t len;
  u_char *out;
  unsigned int out_idx = 0;
  int outlen;
  int state;
  struct screen_write_ctx ctx;
  state = options_get_number(global_options, "set-clipboard");
  if (state != 2)
  {
    return;
  }
  if ((end_idx = strchr(p, ';')) == 0)
  {
    return;
  }
  end_idx += 1;
  if (end[end_idx] == '\0')
  {
    return;
  }
  len = (strlen(end) / 4) * 3;
  if (len == 0)
  {
    return;
  }
  out_idx = xmalloc(len);
  if ((outlen = b64_pton(end, out, len)) == (-1))
  {
    free(out);
    return;
  }
  screen_write_start(&ctx, wp, 0);
  screen_write_setselection(&ctx, out, outlen);
  screen_write_stop(&ctx);
  notify_pane("pane-set-clipboard", wp);
  paste_add(out, outlen);
}


----------------------------
static void input_osc_104(struct window_pane *wp, const char *p)
{
  char *copy;
  unsigned int copy_idx = 0;
  char *s;
  unsigned int s_idx = 0;
  long idx;
  if ((*p) == '\0')
  {
    window_pane_reset_palette(wp);
    return;
  }
  copy_idx = (s = &s[s_idx + s_idx]);
  while (s[s_idx] != '\0')
  {
    idx = strtol(s, &(&s[s_idx]), 10);
    if ((s[s_idx] != '\0') && (s[s_idx] != ';'))
    {
      goto bad;
    }
    if ((idx < 0) || (idx >= 0x100))
    {
      goto bad;
    }
    window_pane_unset_palette(wp, idx);
    if (s[s_idx] == ';')
    {
      s_idx += 1;
    }
  }

  free(copy);
  return;
  bad:
  log_debug("bad OSC 104: %s", p);

  free(copy);
}


----------------------------
static void input_osc_4(struct window_pane *wp, const char *p)
{
  char *copy;
  unsigned int copy_idx = 0;
  char *s;
  unsigned int s_idx = 0;
  char *next = 0;
  long idx;
  u_int r;
  u_int g;
  u_int b;
  copy_idx = (s = &s[s_idx + s_idx]);
  while (((&s[s_idx]) != 0) && (s[s_idx] != '\0'))
  {
    idx = strtol(s, &next, 10);
    if ((*(next++)) != ';')
    {
      goto bad;
    }
    if ((idx < 0) || (idx >= 0x100))
    {
      goto bad;
    }
    s_idx = strsep(&next, ";");
    if (sscanf(s, "rgb:%2x/%2x/%2x", &r, &g, &b) != 3)
    {
      s_idx = next;
      continue;
    }
    window_pane_set_palette(wp, idx, colour_join_rgb(r, g, b));
    s_idx = next;
  }

  free(copy);
  return;
  bad:
  log_debug("bad OSC 4: %s", p);

  free(copy);
}


----------------------------
void screen_set_cursor_colour(struct screen *s, const char *colour)
{
  free(s->ccolour);
  s->ccolour = xstrdup(colour);
}


----------------------------
static void input_osc_11(struct window_pane *wp, const char *p)
{
  u_int r;
  u_int g;
  u_int b;
  if (sscanf(p, "rgb:%2x/%2x/%2x", &r, &g, &b) != 3)
  {
    goto bad;
  }
  wp->colgc.bg = colour_join_rgb(r, g, b);
  wp->flags |= 0x1;
  return;
  bad:
  log_debug("bad OSC 11: %s", p);

}


----------------------------
void screen_set_title(struct screen *s, const char *title)
{
  free(s->title);
  utf8_stravis(&s->title, title, ((0x01 | 0x02) | 0x08) | 0x10);
}


----------------------------
static void input_osc_10(struct window_pane *wp, const char *p)
{
  u_int r;
  u_int g;
  u_int b;
  if (sscanf(p, "rgb:%2x/%2x/%2x", &r, &g, &b) != 3)
  {
    goto bad;
  }
  wp->colgc.fg = colour_join_rgb(r, g, b);
  wp->flags |= 0x1;
  return;
  bad:
  log_debug("bad OSC 10: %s", p);

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
int utf8_isvalid(const char *s)
{
  unsigned int s_idx = 0;
  struct utf8_data ud;
  const char *end;
  unsigned int end_idx = 0;
  enum utf8_state more;
  end_idx = (&s[s_idx]) + strlen(s);
  while ((&s[s_idx]) < (&end[end_idx]))
  {
    if ((more = utf8_open(&ud, *(&s[s_idx]))) == UTF8_MORE)
    {
      while (((++(&s[s_idx])) < (&end[end_idx])) && (more == UTF8_MORE))
      {
        more = utf8_append(&ud, *(&s[s_idx]));
      }

      if (more == UTF8_DONE)
      {
        continue;
      }
      return 0;
    }
    if ((s[s_idx] < 0x20) || (s[s_idx] > 0x7e))
    {
      return 0;
    }
    s_idx += 1;
  }

  return 1;
}


----------------------------
None
----------------------------
***/


static void input_exit_apc(struct input_ctx *ictx)
{
  if (ictx->flags & 0x1)
  {
    return;
  }
  log_debug("%s: \"%s\"", __func__, ictx->input_buf);
  if (!utf8_isvalid(ictx->input_buf))
  {
    return;
  }
  screen_set_title(ictx->ctx.s, ictx->input_buf);
  server_status_window(ictx->wp->window);
}


/*** DEPENDENCIES:
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
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
void screen_set_title(struct screen *s, const char *title)
{
  free(s->title);
  utf8_stravis(&s->title, title, ((0x01 | 0x02) | 0x08) | 0x10);
}


----------------------------
int utf8_isvalid(const char *s)
{
  unsigned int s_idx = 0;
  struct utf8_data ud;
  const char *end;
  unsigned int end_idx = 0;
  enum utf8_state more;
  end_idx = (&s[s_idx]) + strlen(s);
  while ((&s[s_idx]) < (&end[end_idx]))
  {
    if ((more = utf8_open(&ud, *(&s[s_idx]))) == UTF8_MORE)
    {
      while (((++(&s[s_idx])) < (&end[end_idx])) && (more == UTF8_MORE))
      {
        more = utf8_append(&ud, *(&s[s_idx]));
      }

      if (more == UTF8_DONE)
      {
        continue;
      }
      return 0;
    }
    if ((s[s_idx] < 0x20) || (s[s_idx] > 0x7e))
    {
      return 0;
    }
    s_idx += 1;
  }

  return 1;
}


----------------------------
None
----------------------------
***/


static void input_enter_apc(struct input_ctx *ictx)
{
  log_debug("%s", __func__);
  input_clear(ictx);
  input_start_timer(ictx);
  ictx->last = -1;
}


/*** DEPENDENCIES:
static void input_clear(struct input_ctx *ictx)
{
  event_del(&ictx->timer);
  *ictx->interm_buf = '\0';
  ictx->interm_len = 0;
  *ictx->param_buf = '\0';
  ictx->param_len = 0;
  *ictx->input_buf = '\0';
  ictx->input_len = 0;
  ictx->flags &= ~0x1;
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
static void input_start_timer(struct input_ctx *ictx)
{
  struct timeval tv = {.tv_usec = 100000};
  event_del(&ictx->timer);
  event_add(&ictx->timer, &tv);
}


----------------------------
None
----------------------------
***/


static void input_exit_rename(struct input_ctx *ictx)
{
  if (ictx->flags & 0x1)
  {
    return;
  }
  if (!options_get_number(ictx->wp->window->options, "allow-rename"))
  {
    return;
  }
  log_debug("%s: \"%s\"", __func__, ictx->input_buf);
  if (!utf8_isvalid(ictx->input_buf))
  {
    return;
  }
  window_set_name(ictx->wp->window, ictx->input_buf);
  options_set_number(ictx->wp->window->options, "automatic-rename", 0);
  server_status_window(ictx->wp->window);
}


/*** DEPENDENCIES:
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
void window_set_name(struct window *w, const char *new_name)
{
  free(w->name);
  utf8_stravis(&w->name, new_name, ((0x01 | 0x02) | 0x08) | 0x10);
  notify_window("window-renamed", w);
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
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
int utf8_isvalid(const char *s)
{
  unsigned int s_idx = 0;
  struct utf8_data ud;
  const char *end;
  unsigned int end_idx = 0;
  enum utf8_state more;
  end_idx = (&s[s_idx]) + strlen(s);
  while ((&s[s_idx]) < (&end[end_idx]))
  {
    if ((more = utf8_open(&ud, *(&s[s_idx]))) == UTF8_MORE)
    {
      while (((++(&s[s_idx])) < (&end[end_idx])) && (more == UTF8_MORE))
      {
        more = utf8_append(&ud, *(&s[s_idx]));
      }

      if (more == UTF8_DONE)
      {
        continue;
      }
      return 0;
    }
    if ((s[s_idx] < 0x20) || (s[s_idx] > 0x7e))
    {
      return 0;
    }
    s_idx += 1;
  }

  return 1;
}


----------------------------
None
----------------------------
***/


static int input_intermediate(struct input_ctx *ictx)
{
  if (ictx->interm_len == ((sizeof(ictx->interm_buf)) - 1))
  {
    ictx->flags |= 0x1;
  }
  else
  {
    ictx->interm_buf[ictx->interm_len++] = ictx->ch;
    ictx->interm_buf[ictx->interm_len] = '\0';
  }
  return 0;
}


/*** DEPENDENCIES:
None
----------------------------
***/


static int input_parameter(struct input_ctx *ictx)
{
  if (ictx->param_len == ((sizeof(ictx->param_buf)) - 1))
  {
    ictx->flags |= 0x1;
  }
  else
  {
    ictx->param_buf[ictx->param_len++] = ictx->ch;
    ictx->param_buf[ictx->param_len] = '\0';
  }
  return 0;
}


/*** DEPENDENCIES:
None
----------------------------
***/


struct evbuffer *input_pending(struct window_pane *wp)
{
  return wp->ictx->since_ground;
}


/*** DEPENDENCIES:
None
----------------------------
***/


static int input_get(struct input_ctx *ictx, u_int validx, int minval, int defval)
{
  struct input_param *ip;
  unsigned int ip_idx = 0;
  int retval;
  if (validx >= ictx->param_list_len)
  {
    return defval;
  }
  ip_idx = &ictx->param_list[validx];
  if (ip->type == INPUT_MISSING)
  {
    return defval;
  }
  if (ip->type == INPUT_STRING)
  {
    return -1;
  }
  retval = ip->num;
  if (retval < minval)
  {
    return minval;
  }
  return retval;
}


/*** DEPENDENCIES:
struct input_param
{
  enum 
  {
    INPUT_MISSING,
    INPUT_NUMBER,
    INPUT_STRING
  } type;
  union 
  {
    int num;
    char *str;
  };
}
----------------------------
None
----------------------------
***/


static void input_reset_cell(struct input_ctx *ictx)
{
  memcpy(&ictx->cell.cell, &grid_default_cell, sizeof(ictx->cell.cell));
  ictx->cell.set = 0;
  ictx->cell.g0set = (ictx->cell.g1set = 0);
  memcpy(&ictx->old_cell, &ictx->cell, sizeof(ictx->old_cell));
  ictx->old_cx = 0;
  ictx->old_cy = 0;
}


/*** DEPENDENCIES:
extern const struct grid_cell grid_default_cell
----------------------------
None
----------------------------
***/


static int input_input(struct input_ctx *ictx)
{
  size_t available;
  available = ictx->input_space;
  while ((ictx->input_len + 1) >= available)
  {
    available *= 2;
    if (available > 1048576)
    {
      ictx->flags |= 0x1;
      return 0;
    }
    ictx->input_buf = xrealloc(ictx->input_buf, available);
    ictx->input_space = available;
  }

  ictx->input_buf[ictx->input_len++] = ictx->ch;
  ictx->input_buf[ictx->input_len] = '\0';
  return 0;
}


/*** DEPENDENCIES:
void *xrealloc(void *ptr, size_t size)
{
  return xreallocarray(ptr, 1, size);
}


----------------------------
None
----------------------------
***/


static int input_table_compare(const void *key, const void *value)
{
  const struct input_ctx *ictx = key;
  const struct input_table_entry *entry = value;
  if (ictx->ch != entry->ch)
  {
    return ictx->ch - entry->ch;
  }
  return strcmp(ictx->interm_buf, entry->interm);
}


/*** DEPENDENCIES:
struct input_table_entry
{
  int ch;
  const char *interm;
  int type;
}
----------------------------
None
----------------------------
***/


static int input_print(struct input_ctx *ictx)
{
  int set;
  ictx->utf8started = 0;
  set = (ictx->cell.set == 0) ? (ictx->cell.g0set) : (ictx->cell.g1set);
  if (set == 1)
  {
    ictx->cell.cell.attr |= 0x80;
  }
  else
    ictx->cell.cell.attr &= ~0x80;
  utf8_set(&ictx->cell.cell.data, ictx->ch);
  screen_write_collect_add(&ictx->ctx, &ictx->cell.cell);
  ictx->last = ictx->ch;
  ictx->cell.cell.attr &= ~0x80;
  return 0;
}


/*** DEPENDENCIES:
void utf8_set(struct utf8_data *ud, u_char ch)
{
  static const struct utf8_data empty = {{0}, 1, 1, 1};
  memcpy(ud, &empty, sizeof(*ud));
  *ud->data = ch;
}


----------------------------
void screen_write_collect_add(struct screen_write_ctx *ctx, const struct grid_cell *gc)
{
  struct screen *s = ctx->s;
  struct screen_write_collect_item *ci;
  unsigned int ci_idx = 0;
  u_int sx = s->grid->sx;
  int collect;
  collect = 1;
  if (((gc->data.width != 1) || (gc->data.size != 1)) || ((*gc->data.data) >= 0x7f))
  {
    collect = 0;
  }
  else
    if (gc->attr & 0x80)
  {
    collect = 0;
  }
  else
    if ((~s->mode) & 0x10)
  {
    collect = 0;
  }
  else
    if (s->mode & 0x2)
  {
    collect = 0;
  }
  else
    if (s->sel.flag)
  {
    collect = 0;
  }
  if (!collect)
  {
    screen_write_collect_end(ctx);
    screen_write_collect_flush(ctx, 0);
    screen_write_cell(ctx, gc);
    return;
  }
  ctx->cells += 1;
  if ((s->cx > (sx - 1)) || (ctx->item->used > ((sx - 1) - s->cx)))
  {
    screen_write_collect_end(ctx);
  }
  ci_idx = ctx->item;
  if (s->cx > (sx - 1))
  {
    log_debug("%s: wrapped at %u,%u", __func__, s->cx, s->cy);
    ci->wrapped = 1;
    screen_write_linefeed(ctx, 1, 8);
    s->cx = 0;
  }
  if (ci->used == 0)
  {
    memcpy(&ci->gc, gc, sizeof(ci->gc));
  }
  ci->data[ci->used++] = gc->data.data[0];
  if (ci->used == ((sizeof(ci->data)) - 1))
  {
    screen_write_collect_end(ctx);
  }
}


----------------------------
None
----------------------------
***/


static int input_csi_dispatch_sgr_256_do(struct input_ctx *ictx, int fgbg, int c)
{
  struct grid_cell *gc = &ictx->cell.cell;
  if ((c == (-1)) || (c > 255))
  {
    if (fgbg == 38)
    {
      gc->fg = 8;
    }
    else
      if (fgbg == 48)
    {
      gc->bg = 8;
    }
  }
  else
  {
    if (fgbg == 38)
    {
      gc->fg = c | 0x01000000;
    }
    else
      if (fgbg == 48)
    {
      gc->bg = c | 0x01000000;
    }
  }
  return 1;
}


/*** DEPENDENCIES:
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
None
----------------------------
None
----------------------------
***/


static void input_csi_dispatch_sgr_256(struct input_ctx *ictx, int fgbg, u_int *i)
{
  int c;
  c = input_get(ictx, (*i) + 1, 0, -1);
  if (input_csi_dispatch_sgr_256_do(ictx, fgbg, c))
  {
    *i += 1;
  }
}


/*** DEPENDENCIES:
static int input_get(struct input_ctx *ictx, u_int validx, int minval, int defval)
{
  struct input_param *ip;
  unsigned int ip_idx = 0;
  int retval;
  if (validx >= ictx->param_list_len)
  {
    return defval;
  }
  ip_idx = &ictx->param_list[validx];
  if (ip->type == INPUT_MISSING)
  {
    return defval;
  }
  if (ip->type == INPUT_STRING)
  {
    return -1;
  }
  retval = ip->num;
  if (retval < minval)
  {
    return minval;
  }
  return retval;
}


----------------------------
static int input_csi_dispatch_sgr_256_do(struct input_ctx *ictx, int fgbg, int c)
{
  struct grid_cell *gc = &ictx->cell.cell;
  if ((c == (-1)) || (c > 255))
  {
    if (fgbg == 38)
    {
      gc->fg = 8;
    }
    else
      if (fgbg == 48)
    {
      gc->bg = 8;
    }
  }
  else
  {
    if (fgbg == 38)
    {
      gc->fg = c | 0x01000000;
    }
    else
      if (fgbg == 48)
    {
      gc->bg = c | 0x01000000;
    }
  }
  return 1;
}


----------------------------
None
----------------------------
***/


static int input_csi_dispatch_sgr_rgb_do(struct input_ctx *ictx, int fgbg, int r, int g, int b)
{
  struct grid_cell *gc = &ictx->cell.cell;
  if ((r == (-1)) || (r > 255))
  {
    return 0;
  }
  if ((g == (-1)) || (g > 255))
  {
    return 0;
  }
  if ((b == (-1)) || (b > 255))
  {
    return 0;
  }
  if (fgbg == 38)
  {
    gc->fg = colour_join_rgb(r, g, b);
  }
  else
    if (fgbg == 48)
  {
    gc->bg = colour_join_rgb(r, g, b);
  }
  return 1;
}


/*** DEPENDENCIES:
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
None
----------------------------
int colour_join_rgb(u_char r, u_char g, u_char b)
{
  return (((((int) (r & 0xff)) << 16) | (((int) (g & 0xff)) << 8)) | ((int) (b & 0xff))) | 0x02000000;
}


----------------------------
None
----------------------------
***/


static void input_csi_dispatch_sgr_rgb(struct input_ctx *ictx, int fgbg, u_int *i)
{
  int r;
  int g;
  int b;
  r = input_get(ictx, (*i) + 1, 0, -1);
  g = input_get(ictx, (*i) + 2, 0, -1);
  b = input_get(ictx, (*i) + 3, 0, -1);
  if (input_csi_dispatch_sgr_rgb_do(ictx, fgbg, r, g, b))
  {
    *i += 3;
  }
}


/*** DEPENDENCIES:
static int input_get(struct input_ctx *ictx, u_int validx, int minval, int defval)
{
  struct input_param *ip;
  unsigned int ip_idx = 0;
  int retval;
  if (validx >= ictx->param_list_len)
  {
    return defval;
  }
  ip_idx = &ictx->param_list[validx];
  if (ip->type == INPUT_MISSING)
  {
    return defval;
  }
  if (ip->type == INPUT_STRING)
  {
    return -1;
  }
  retval = ip->num;
  if (retval < minval)
  {
    return minval;
  }
  return retval;
}


----------------------------
static int input_csi_dispatch_sgr_rgb_do(struct input_ctx *ictx, int fgbg, int r, int g, int b)
{
  struct grid_cell *gc = &ictx->cell.cell;
  if ((r == (-1)) || (r > 255))
  {
    return 0;
  }
  if ((g == (-1)) || (g > 255))
  {
    return 0;
  }
  if ((b == (-1)) || (b > 255))
  {
    return 0;
  }
  if (fgbg == 38)
  {
    gc->fg = colour_join_rgb(r, g, b);
  }
  else
    if (fgbg == 48)
  {
    gc->bg = colour_join_rgb(r, g, b);
  }
  return 1;
}


----------------------------
None
----------------------------
***/


static int input_dcs_dispatch(struct input_ctx *ictx)
{
  const char prefix[] = "tmux;";
  const u_int prefix_len = (sizeof(prefix)) - 1;
  if (ictx->flags & 0x1)
  {
    return 0;
  }
  log_debug("%s: \"%s\"", __func__, ictx->input_buf);
  if ((ictx->input_len >= prefix_len) && (strncmp(ictx->input_buf, prefix, prefix_len) == 0))
  {
    screen_write_rawstring(&ictx->ctx, ictx->input_buf + prefix_len, ictx->input_len - prefix_len);
  }
  return 0;
}


/*** DEPENDENCIES:
void screen_write_rawstring(struct screen_write_ctx *ctx, u_char *str, u_int len)
{
  struct tty_ctx ttyctx;
  screen_write_initctx(ctx, &ttyctx);
  ttyctx.ptr = str;
  ttyctx.num = len;
  tty_write(tty_cmd_rawstring, &ttyctx);
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


// hint:  ['n_ref is a mutable refrence to int', 'cx_ref is a mutable refrence to u_int']
void helper_input_csi_dispatch_1(int * const n_ref, u_int * const cx_ref, struct input_ctx * const ictx, struct screen * const s)
{
  int n = *n_ref;
  u_int cx = *cx_ref;
  cx = s->cx;
  if (cx > (s->grid->sx - 1))
  {
    cx = s->grid->sx - 1;
  }
  n = input_get(ictx, 0, 1, 1);
  if (n == (-1))
  {
    break;
  }
  while ((cx > 0) && ((n--) > 0))
  {
    do
    {
      cx -= 1;
    }
    while ((cx > 0) && (!(s->tabs[cx >> 3] & (1 << (cx & 0x7)))));
  }

  s->cx = cx;
  break;
  *n_ref = n;
  *cx_ref = cx;
}


/*** DEPENDENCIES:
static int input_get(struct input_ctx *ictx, u_int validx, int minval, int defval)
{
  struct input_param *ip;
  unsigned int ip_idx = 0;
  int retval;
  if (validx >= ictx->param_list_len)
  {
    return defval;
  }
  ip_idx = &ictx->param_list[validx];
  if (ip->type == INPUT_MISSING)
  {
    return defval;
  }
  if (ip->type == INPUT_STRING)
  {
    return -1;
  }
  retval = ip->num;
  if (retval < minval)
  {
    return minval;
  }
  return retval;
}


----------------------------
None
----------------------------
None
----------------------------
***/


// hint:  ['ip_idx_ref is a mutable refrence to unsigned int']
int helper_input_split_1(unsigned int * const ip_idx_ref, struct input_ctx * const ictx, const char * const errstr, char * const out, unsigned int out_idx, struct input_param * const ip)
{
  unsigned int ip_idx = *ip_idx_ref;
  if (out[out_idx] == '\0')
  {
    ip->type = INPUT_MISSING;
  }
  else
  {
    if (strchr(out, ':') != 0)
    {
      ip->type = INPUT_STRING;
      ip->str = xstrdup(out);
    }
    else
    {
      ip->type = INPUT_NUMBER;
      ip->num = strtonum(out, 0, 2147483647, &errstr);
      if (errstr != 0)
      {
        return -1;
      }
    }
  }
  ip_idx = &ictx->param_list[++ictx->param_list_len];
  if (ictx->param_list_len == ((sizeof(ictx->param_list)) / (sizeof(ictx->param_list[0]))))
  {
    return -1;
  }
  *ip_idx_ref = ip_idx;
}


/*** DEPENDENCIES:
struct input_param
{
  enum 
  {
    INPUT_MISSING,
    INPUT_NUMBER,
    INPUT_STRING
  } type;
  union 
  {
    int num;
    char *str;
  };
}
----------------------------
long long strtonum(const char *numstr, long long minval, long long maxval, const char **errstrp)
{
  long long ll = 0;
  char *ep;
  int error = 0;
  struct errval
  {
    const char *errstr;
    int err;
  } ev[4] = {{0, 0}, {"invalid", EINVAL}, {"too small", ERANGE}, {"too large", ERANGE}};
  ev[0].err = errno;
  errno = 0;
  if (minval > maxval)
  {
    error = 1;
  }
  else
  {
    ll = strtoll(numstr, &ep, 10);
    if ((numstr == ep) || ((*ep) != '\0'))
    {
      error = 1;
    }
    else
      if (((ll == LLONG_MIN) && (errno == ERANGE)) || (ll < minval))
    {
      error = 2;
    }
    else
      if (((ll == LLONG_MAX) && (errno == ERANGE)) || (ll > maxval))
    {
      error = 3;
    }
  }
  if (errstrp != 0)
  {
    *errstrp = ev[error].errstr;
  }
  errno = ev[error].err;
  if (error)
  {
    ll = 0;
  }
  return ll;
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
None
----------------------------
***/


static int input_split(struct input_ctx *ictx)
{
  const char *errstr;
  char *ptr;
  unsigned int ptr_idx = 0;
  char *out;
  unsigned int out_idx = 0;
  struct input_param *ip;
  unsigned int ip_idx = 0;
  u_int i;
  for (i = 0; i < ictx->param_list_len; i += 1)
  {
    if (ictx->param_list[i].type == INPUT_STRING)
    {
      free(ictx->param_list[i].str);
    }
  }

  ictx->param_list_len = 0;
  if (ictx->param_len == 0)
  {
    return 0;
  }
  ip_idx = &ictx->param_list[0];
  ptr_idx = ictx->param_buf;
  while ((out_idx = strsep(&(&ptr[ptr_idx]), ";")) != 0)
  {
    helper_input_split_1(&ip_idx, ictx, errstr, out, out_idx, ip);
  }

  for (i = 0; i < ictx->param_list_len; i += 1)
  {
    ip_idx = &ictx->param_list[i];
    if (ip->type == INPUT_MISSING)
    {
      log_debug("parameter %u: missing", i);
    }
    else
      if (ip->type == INPUT_STRING)
    {
      log_debug("parameter %u: string %s", i, ip->str);
    }
    else
      if (ip->type == INPUT_NUMBER)
    {
      log_debug("parameter %u: number %d", i, ip->num);
    }
  }

  return 0;
}


/*** DEPENDENCIES:
struct input_param
{
  enum 
  {
    INPUT_MISSING,
    INPUT_NUMBER,
    INPUT_STRING
  } type;
  union 
  {
    int num;
    char *str;
  };
}
----------------------------
int helper_input_split_1(unsigned int * const ip_idx_ref, struct input_ctx * const ictx, const char * const errstr, char * const out, unsigned int out_idx, struct input_param * const ip)
{
  unsigned int ip_idx = *ip_idx_ref;
  if (out[out_idx] == '\0')
  {
    ip->type = INPUT_MISSING;
  }
  else
  {
    if (strchr(out, ':') != 0)
    {
      ip->type = INPUT_STRING;
      ip->str = xstrdup(out);
    }
    else
    {
      ip->type = INPUT_NUMBER;
      ip->num = strtonum(out, 0, 2147483647, &errstr);
      if (errstr != 0)
      {
        return -1;
      }
    }
  }
  ip_idx = &ictx->param_list[++ictx->param_list_len];
  if (ictx->param_list_len == ((sizeof(ictx->param_list)) / (sizeof(ictx->param_list[0]))))
  {
    return -1;
  }
  *ip_idx_ref = ip_idx;
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


static void input_set_state(struct window_pane *wp, const struct input_transition *itr)
{
  struct input_ctx *ictx = wp->ictx;
  if (ictx->state->exit != 0)
  {
    ictx->state->exit(ictx);
  }
  ictx->state = itr->state;
  if (ictx->state->enter != 0)
  {
    ictx->state->enter(ictx);
  }
}


/*** DEPENDENCIES:
None
----------------------------
***/


void helper_input_csi_dispatch_rm_private_1(struct input_ctx * const ictx, struct window_pane * const wp, u_int i)
{
  switch (input_get(ictx, i, 0, -1))
  {
    case -1:
    {
      break;
    }

    case 1:
    {
      screen_write_mode_clear(&ictx->ctx, 0x4);
      break;
    }

    case 3:
    {
      screen_write_cursormove(&ictx->ctx, 0, 0);
      screen_write_clearscreen(&ictx->ctx, ictx->cell.cell.bg);
      break;
    }

    case 7:
    {
      screen_write_mode_clear(&ictx->ctx, 0x10);
      break;
    }

    case 12:
    {
      screen_write_mode_clear(&ictx->ctx, 0x80);
      break;
    }

    case 25:
    {
      screen_write_mode_clear(&ictx->ctx, 0x1);
      break;
    }

    case 1000:

    case 1001:

    case 1002:

    case 1003:
    {
      screen_write_mode_clear(&ictx->ctx, (0x20 | 0x40) | 0x1000);
      break;
    }

    case 1004:
    {
      screen_write_mode_clear(&ictx->ctx, 0x800);
      break;
    }

    case 1005:
    {
      screen_write_mode_clear(&ictx->ctx, 0x100);
      break;
    }

    case 1006:
    {
      screen_write_mode_clear(&ictx->ctx, 0x200);
      break;
    }

    case 47:

    case 1047:
    {
      window_pane_alternate_off(wp, &ictx->cell.cell, 0);
      break;
    }

    case 1049:
    {
      window_pane_alternate_off(wp, &ictx->cell.cell, 1);
      break;
    }

    case 2004:
    {
      screen_write_mode_clear(&ictx->ctx, 0x400);
      break;
    }

    default:
    {
      log_debug("%s: unknown '%c'", __func__, ictx->ch);
      break;
    }

  }

}


/*** DEPENDENCIES:
static int input_get(struct input_ctx *ictx, u_int validx, int minval, int defval)
{
  struct input_param *ip;
  unsigned int ip_idx = 0;
  int retval;
  if (validx >= ictx->param_list_len)
  {
    return defval;
  }
  ip_idx = &ictx->param_list[validx];
  if (ip->type == INPUT_MISSING)
  {
    return defval;
  }
  if (ip->type == INPUT_STRING)
  {
    return -1;
  }
  retval = ip->num;
  if (retval < minval)
  {
    return minval;
  }
  return retval;
}


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
void screen_write_mode_clear(struct screen_write_ctx *ctx, int mode)
{
  struct screen *s = ctx->s;
  s->mode &= ~mode;
}


----------------------------
void window_pane_alternate_off(struct window_pane *wp, struct grid_cell *gc, int cursor)
{
  struct screen *s = &wp->base;
  u_int sx;
  u_int sy;
  if (wp->saved_grid == 0)
  {
    return;
  }
  if (!options_get_number(wp->window->options, "alternate-screen"))
  {
    return;
  }
  sx = s->grid->sx;
  sy = s->grid->sy;
  if (sy > wp->saved_grid->sy)
  {
    screen_resize(s, sx, wp->saved_grid->sy, 1);
  }
  grid_duplicate_lines(s->grid, s->grid->hsize, wp->saved_grid, 0, sy);
  if (cursor)
  {
    s->cx = wp->saved_cx;
  }
  if (s->cx > (s->grid->sx - 1))
  {
    s->cx = s->grid->sx - 1;
  }
  if (cursor)
  {
    s->cy = wp->saved_cy;
  }
  if (s->cy > (s->grid->sy - 1))
  {
    s->cy = s->grid->sy - 1;
  }
  memcpy(gc, &wp->saved_cell, sizeof(*gc));
  wp->base.grid->flags |= 0x1;
  if ((sy > wp->saved_grid->sy) || (sx != wp->saved_grid->sx))
  {
    screen_resize(s, sx, sy, 1);
  }
  grid_destroy(wp->saved_grid);
  wp->saved_grid = 0;
  wp->flags |= 0x1;
}


----------------------------
void screen_write_clearscreen(struct screen_write_ctx *ctx, u_int bg)
{
  struct screen *s = ctx->s;
  struct tty_ctx ttyctx;
  u_int sx = s->grid->sx;
  u_int sy = s->grid->sy;
  screen_write_initctx(ctx, &ttyctx);
  ttyctx.bg = bg;
  if (s->grid->flags & 0x1)
  {
    grid_view_clear_history(s->grid, bg);
  }
  else
    grid_view_clear(s->grid, 0, 0, sx, sy, bg);
  screen_write_collect_clear(ctx, 0, sy);
  tty_write(tty_cmd_clearscreen, &ttyctx);
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


static void input_csi_dispatch_rm_private(struct input_ctx *ictx)
{
  struct window_pane *wp = ictx->wp;
  u_int i;
  for (i = 0; i < ictx->param_list_len; i += 1)
  {
    helper_input_csi_dispatch_rm_private_1(ictx, wp, i);
  }

}


/*** DEPENDENCIES:
void helper_input_csi_dispatch_rm_private_1(struct input_ctx * const ictx, struct window_pane * const wp, u_int i)
{
  switch (input_get(ictx, i, 0, -1))
  {
    case -1:
    {
      break;
    }

    case 1:
    {
      screen_write_mode_clear(&ictx->ctx, 0x4);
      break;
    }

    case 3:
    {
      screen_write_cursormove(&ictx->ctx, 0, 0);
      screen_write_clearscreen(&ictx->ctx, ictx->cell.cell.bg);
      break;
    }

    case 7:
    {
      screen_write_mode_clear(&ictx->ctx, 0x10);
      break;
    }

    case 12:
    {
      screen_write_mode_clear(&ictx->ctx, 0x80);
      break;
    }

    case 25:
    {
      screen_write_mode_clear(&ictx->ctx, 0x1);
      break;
    }

    case 1000:

    case 1001:

    case 1002:

    case 1003:
    {
      screen_write_mode_clear(&ictx->ctx, (0x20 | 0x40) | 0x1000);
      break;
    }

    case 1004:
    {
      screen_write_mode_clear(&ictx->ctx, 0x800);
      break;
    }

    case 1005:
    {
      screen_write_mode_clear(&ictx->ctx, 0x100);
      break;
    }

    case 1006:
    {
      screen_write_mode_clear(&ictx->ctx, 0x200);
      break;
    }

    case 47:

    case 1047:
    {
      window_pane_alternate_off(wp, &ictx->cell.cell, 0);
      break;
    }

    case 1049:
    {
      window_pane_alternate_off(wp, &ictx->cell.cell, 1);
      break;
    }

    case 2004:
    {
      screen_write_mode_clear(&ictx->ctx, 0x400);
      break;
    }

    default:
    {
      log_debug("%s: unknown '%c'", __func__, ictx->ch);
      break;
    }

  }

}


----------------------------
None
----------------------------
***/


void helper_input_csi_dispatch_sm_private_1(struct input_ctx * const ictx, struct window_pane * const wp, u_int i)
{
  switch (input_get(ictx, i, 0, -1))
  {
    case -1:
    {
      break;
    }

    case 1:
    {
      screen_write_mode_set(&ictx->ctx, 0x4);
      break;
    }

    case 3:
    {
      screen_write_cursormove(&ictx->ctx, 0, 0);
      screen_write_clearscreen(&ictx->ctx, ictx->cell.cell.bg);
      break;
    }

    case 7:
    {
      screen_write_mode_set(&ictx->ctx, 0x10);
      break;
    }

    case 12:
    {
      screen_write_mode_set(&ictx->ctx, 0x80);
      break;
    }

    case 25:
    {
      screen_write_mode_set(&ictx->ctx, 0x1);
      break;
    }

    case 1000:
    {
      screen_write_mode_clear(&ictx->ctx, (0x20 | 0x40) | 0x1000);
      screen_write_mode_set(&ictx->ctx, 0x20);
      break;
    }

    case 1002:
    {
      screen_write_mode_clear(&ictx->ctx, (0x20 | 0x40) | 0x1000);
      screen_write_mode_set(&ictx->ctx, 0x40);
      break;
    }

    case 1003:
    {
      screen_write_mode_clear(&ictx->ctx, (0x20 | 0x40) | 0x1000);
      screen_write_mode_set(&ictx->ctx, 0x1000);
      break;
    }

    case 1004:
    {
      if (ictx->ctx.s->mode & 0x800)
      {
        break;
      }
      screen_write_mode_set(&ictx->ctx, 0x800);
      wp->flags |= 0x20;
      break;
    }

    case 1005:
    {
      screen_write_mode_set(&ictx->ctx, 0x100);
      break;
    }

    case 1006:
    {
      screen_write_mode_set(&ictx->ctx, 0x200);
      break;
    }

    case 47:

    case 1047:
    {
      window_pane_alternate_on(wp, &ictx->cell.cell, 0);
      break;
    }

    case 1049:
    {
      window_pane_alternate_on(wp, &ictx->cell.cell, 1);
      break;
    }

    case 2004:
    {
      screen_write_mode_set(&ictx->ctx, 0x400);
      break;
    }

    default:
    {
      log_debug("%s: unknown '%c'", __func__, ictx->ch);
      break;
    }

  }

}


/*** DEPENDENCIES:
static int input_get(struct input_ctx *ictx, u_int validx, int minval, int defval)
{
  struct input_param *ip;
  unsigned int ip_idx = 0;
  int retval;
  if (validx >= ictx->param_list_len)
  {
    return defval;
  }
  ip_idx = &ictx->param_list[validx];
  if (ip->type == INPUT_MISSING)
  {
    return defval;
  }
  if (ip->type == INPUT_STRING)
  {
    return -1;
  }
  retval = ip->num;
  if (retval < minval)
  {
    return minval;
  }
  return retval;
}


----------------------------
void window_pane_alternate_on(struct window_pane *wp, struct grid_cell *gc, int cursor)
{
  struct screen *s = &wp->base;
  u_int sx;
  u_int sy;
  if (wp->saved_grid != 0)
  {
    return;
  }
  if (!options_get_number(wp->window->options, "alternate-screen"))
  {
    return;
  }
  sx = s->grid->sx;
  sy = s->grid->sy;
  wp->saved_grid = grid_create(sx, sy, 0);
  grid_duplicate_lines(wp->saved_grid, 0, s->grid, s->grid->hsize, sy);
  if (cursor)
  {
    wp->saved_cx = s->cx;
    wp->saved_cy = s->cy;
  }
  memcpy(&wp->saved_cell, gc, sizeof(wp->saved_cell));
  grid_view_clear(s->grid, 0, 0, sx, sy, 8);
  wp->base.grid->flags &= ~0x1;
  wp->flags |= 0x1;
}


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
void screen_write_mode_clear(struct screen_write_ctx *ctx, int mode)
{
  struct screen *s = ctx->s;
  s->mode &= ~mode;
}


----------------------------
void screen_write_clearscreen(struct screen_write_ctx *ctx, u_int bg)
{
  struct screen *s = ctx->s;
  struct tty_ctx ttyctx;
  u_int sx = s->grid->sx;
  u_int sy = s->grid->sy;
  screen_write_initctx(ctx, &ttyctx);
  ttyctx.bg = bg;
  if (s->grid->flags & 0x1)
  {
    grid_view_clear_history(s->grid, bg);
  }
  else
    grid_view_clear(s->grid, 0, 0, sx, sy, bg);
  screen_write_collect_clear(ctx, 0, sy);
  tty_write(tty_cmd_clearscreen, &ttyctx);
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
void screen_write_mode_set(struct screen_write_ctx *ctx, int mode)
{
  struct screen *s = ctx->s;
  s->mode |= mode;
}


----------------------------
None
----------------------------
***/


static void input_csi_dispatch_sm_private(struct input_ctx *ictx)
{
  struct window_pane *wp = ictx->wp;
  u_int i;
  for (i = 0; i < ictx->param_list_len; i += 1)
  {
    helper_input_csi_dispatch_sm_private_1(ictx, wp, i);
  }

}


/*** DEPENDENCIES:
void helper_input_csi_dispatch_sm_private_1(struct input_ctx * const ictx, struct window_pane * const wp, u_int i)
{
  switch (input_get(ictx, i, 0, -1))
  {
    case -1:
    {
      break;
    }

    case 1:
    {
      screen_write_mode_set(&ictx->ctx, 0x4);
      break;
    }

    case 3:
    {
      screen_write_cursormove(&ictx->ctx, 0, 0);
      screen_write_clearscreen(&ictx->ctx, ictx->cell.cell.bg);
      break;
    }

    case 7:
    {
      screen_write_mode_set(&ictx->ctx, 0x10);
      break;
    }

    case 12:
    {
      screen_write_mode_set(&ictx->ctx, 0x80);
      break;
    }

    case 25:
    {
      screen_write_mode_set(&ictx->ctx, 0x1);
      break;
    }

    case 1000:
    {
      screen_write_mode_clear(&ictx->ctx, (0x20 | 0x40) | 0x1000);
      screen_write_mode_set(&ictx->ctx, 0x20);
      break;
    }

    case 1002:
    {
      screen_write_mode_clear(&ictx->ctx, (0x20 | 0x40) | 0x1000);
      screen_write_mode_set(&ictx->ctx, 0x40);
      break;
    }

    case 1003:
    {
      screen_write_mode_clear(&ictx->ctx, (0x20 | 0x40) | 0x1000);
      screen_write_mode_set(&ictx->ctx, 0x1000);
      break;
    }

    case 1004:
    {
      if (ictx->ctx.s->mode & 0x800)
      {
        break;
      }
      screen_write_mode_set(&ictx->ctx, 0x800);
      wp->flags |= 0x20;
      break;
    }

    case 1005:
    {
      screen_write_mode_set(&ictx->ctx, 0x100);
      break;
    }

    case 1006:
    {
      screen_write_mode_set(&ictx->ctx, 0x200);
      break;
    }

    case 47:

    case 1047:
    {
      window_pane_alternate_on(wp, &ictx->cell.cell, 0);
      break;
    }

    case 1049:
    {
      window_pane_alternate_on(wp, &ictx->cell.cell, 1);
      break;
    }

    case 2004:
    {
      screen_write_mode_set(&ictx->ctx, 0x400);
      break;
    }

    default:
    {
      log_debug("%s: unknown '%c'", __func__, ictx->ch);
      break;
    }

  }

}


----------------------------
None
----------------------------
***/


// hint:  ['itr_idx_ref is a mutable refrence to unsigned int', 'off_ref is a mutable refrence to size_t']
void helper_input_parse_1(unsigned int * const itr_idx_ref, size_t * const off_ref, struct window_pane * const wp, struct input_ctx * const ictx, const struct input_transition * const itr, u_char * const buf, unsigned int buf_idx)
{
  unsigned int itr_idx = *itr_idx_ref;
  size_t off = *off_ref;
  ictx->ch = buf[off + buf_idx];
  off += 1;
  itr_idx = ictx->state->transitions;
  while ((itr->first != (-1)) && (itr->last != (-1)))
  {
    if ((ictx->ch >= itr->first) && (ictx->ch <= itr->last))
    {
      break;
    }
    itr_idx += 1;
  }

  if ((itr->first == (-1)) || (itr->last == (-1)))
  {
    fatalx("no transition from state");
  }
  if (itr->handler != input_print)
  {
    screen_write_collect_end(&ictx->ctx);
  }
  if ((itr->handler != 0) && (itr->handler(ictx) != 0))
  {
    continue;
  }
  if (itr->state != 0)
  {
    input_set_state(wp, itr);
  }
  if (ictx->state != (&input_state_ground))
  {
    evbuffer_add(ictx->since_ground, &ictx->ch, 1);
  }
  *itr_idx_ref = itr_idx;
  *off_ref = off;
}


/*** DEPENDENCIES:
void screen_write_collect_end(struct screen_write_ctx *ctx)
{
  struct screen *s = ctx->s;
  struct screen_write_collect_item *ci = ctx->item;
  struct grid_cell gc;
  u_int xx;
  if (ci->used == 0)
  {
    return;
  }
  ci->data[ci->used] = '\0';
  ci->x = s->cx;
  do
  {
    ci->entry.tqe_next = 0;
    ci->entry.tqe_prev = (&ctx->list[s->cy].items)->tqh_last;
    *(&ctx->list[s->cy].items)->tqh_last = ci;
    (&ctx->list[s->cy].items)->tqh_last = &ci->entry.tqe_next;
  }
  while (0);
  ctx->item = xcalloc(1, sizeof(*ctx->item));
  log_debug("%s: %u %s (at %u,%u)", __func__, ci->used, ci->data, s->cx, s->cy);
  if (s->cx != 0)
  {
    for (xx = s->cx; xx > 0; xx -= 1)
    {
      grid_view_get_cell(s->grid, xx, s->cy, &gc);
      if ((~gc.flags) & 0x4)
      {
        break;
      }
      grid_view_set_cell(s->grid, xx, s->cy, &grid_default_cell);
    }

    if (gc.data.width > 1)
    {
      grid_view_set_cell(s->grid, xx, s->cy, &grid_default_cell);
    }
  }
  memcpy(&gc, &ci->gc, sizeof(gc));
  grid_view_set_cells(s->grid, s->cx, s->cy, &gc, ci->data, ci->used);
  s->cx += ci->used;
  for (xx = s->cx; xx < s->grid->sx; xx += 1)
  {
    grid_view_get_cell(s->grid, xx, s->cy, &gc);
    if ((~gc.flags) & 0x4)
    {
      break;
    }
    grid_view_set_cell(s->grid, xx, s->cy, &grid_default_cell);
  }

}


----------------------------
static const struct input_state input_state_ground = {"ground", input_ground, 0, input_state_ground_table}
----------------------------
void fatalx(const char *msg, ...)
{
  char *fmt;
  va_list ap;
  __builtin_va_start(ap);
  if (asprintf(&fmt, "fatal: %s", msg) == (-1))
  {
    exit(1);
  }
  log_vwrite(fmt, ap);
  ;
  exit(1);
}


----------------------------
static int input_print(struct input_ctx *ictx)
{
  int set;
  ictx->utf8started = 0;
  set = (ictx->cell.set == 0) ? (ictx->cell.g0set) : (ictx->cell.g1set);
  if (set == 1)
  {
    ictx->cell.cell.attr |= 0x80;
  }
  else
    ictx->cell.cell.attr &= ~0x80;
  utf8_set(&ictx->cell.cell.data, ictx->ch);
  screen_write_collect_add(&ictx->ctx, &ictx->cell.cell);
  ictx->last = ictx->ch;
  ictx->cell.cell.attr &= ~0x80;
  return 0;
}


----------------------------
static void input_set_state(struct window_pane *wp, const struct input_transition *itr)
{
  struct input_ctx *ictx = wp->ictx;
  if (ictx->state->exit != 0)
  {
    ictx->state->exit(ictx);
  }
  ictx->state = itr->state;
  if (ictx->state->enter != 0)
  {
    ictx->state->enter(ictx);
  }
}


----------------------------
None
----------------------------
***/


void input_parse(struct window_pane *wp)
{
  struct input_ctx *ictx = wp->ictx;
  const struct input_transition *itr;
  unsigned int itr_idx = 0;
  struct evbuffer *evb = wp->event->input;
  u_char *buf;
  unsigned int buf_idx = 0;
  size_t len;
  size_t off;
  if (EVBUFFER_LENGTH(evb) == 0)
  {
    return;
  }
  window_update_activity(wp->window);
  wp->flags |= 0x80;
  if (wp->mode == 0)
  {
    screen_write_start(&ictx->ctx, wp, &wp->base);
  }
  else
    screen_write_start(&ictx->ctx, 0, &wp->base);
  ictx->wp = wp;
  buf_idx = EVBUFFER_DATA(evb);
  len = EVBUFFER_LENGTH(evb);
  off = 0;
  notify_input(wp, evb);
  log_debug("%s: %%%u %s, %zu bytes: %.*s", __func__, wp->id, ictx->state->name, len, (int) len, buf);
  while (off < len)
  {
    helper_input_parse_1(&itr_idx, &off, wp, ictx, itr, buf, buf_idx);
  }

  screen_write_stop(&ictx->ctx);
  evbuffer_drain(evb, len);
}


/*** DEPENDENCIES:
void notify_input(struct window_pane *wp, struct evbuffer *input)
{
  struct client *c;
  unsigned int c_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (c->flags & 0x2000)
    {
      control_notify_input(c, wp, input);
    }
  }

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
void helper_input_parse_1(unsigned int * const itr_idx_ref, size_t * const off_ref, struct window_pane * const wp, struct input_ctx * const ictx, const struct input_transition * const itr, u_char * const buf, unsigned int buf_idx)
{
  unsigned int itr_idx = *itr_idx_ref;
  size_t off = *off_ref;
  ictx->ch = buf[off + buf_idx];
  off += 1;
  itr_idx = ictx->state->transitions;
  while ((itr->first != (-1)) && (itr->last != (-1)))
  {
    if ((ictx->ch >= itr->first) && (ictx->ch <= itr->last))
    {
      break;
    }
    itr_idx += 1;
  }

  if ((itr->first == (-1)) || (itr->last == (-1)))
  {
    fatalx("no transition from state");
  }
  if (itr->handler != input_print)
  {
    screen_write_collect_end(&ictx->ctx);
  }
  if ((itr->handler != 0) && (itr->handler(ictx) != 0))
  {
    continue;
  }
  if (itr->state != 0)
  {
    input_set_state(wp, itr);
  }
  if (ictx->state != (&input_state_ground))
  {
    evbuffer_add(ictx->since_ground, &ictx->ch, 1);
  }
  *itr_idx_ref = itr_idx;
  *off_ref = off;
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
void window_update_activity(struct window *w)
{
  gettimeofday(&w->activity_time, 0);
  alerts_queue(w, 0x2);
}


----------------------------
None
----------------------------
***/


static void input_csi_dispatch_rm(struct input_ctx *ictx)
{
  u_int i;
  for (i = 0; i < ictx->param_list_len; i += 1)
  {
    switch (input_get(ictx, i, 0, -1))
    {
      case -1:
      {
        break;
      }

      case 4:
      {
        screen_write_mode_clear(&ictx->ctx, 0x2);
        break;
      }

      case 34:
      {
        screen_write_mode_set(&ictx->ctx, 0x80);
        break;
      }

      default:
      {
        log_debug("%s: unknown '%c'", __func__, ictx->ch);
        break;
      }

    }

  }

}


/*** DEPENDENCIES:
static int input_get(struct input_ctx *ictx, u_int validx, int minval, int defval)
{
  struct input_param *ip;
  unsigned int ip_idx = 0;
  int retval;
  if (validx >= ictx->param_list_len)
  {
    return defval;
  }
  ip_idx = &ictx->param_list[validx];
  if (ip->type == INPUT_MISSING)
  {
    return defval;
  }
  if (ip->type == INPUT_STRING)
  {
    return -1;
  }
  retval = ip->num;
  if (retval < minval)
  {
    return minval;
  }
  return retval;
}


----------------------------
void screen_write_mode_clear(struct screen_write_ctx *ctx, int mode)
{
  struct screen *s = ctx->s;
  s->mode &= ~mode;
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
void screen_write_mode_set(struct screen_write_ctx *ctx, int mode)
{
  struct screen *s = ctx->s;
  s->mode |= mode;
}


----------------------------
None
----------------------------
***/


static void input_csi_dispatch_sm(struct input_ctx *ictx)
{
  u_int i;
  for (i = 0; i < ictx->param_list_len; i += 1)
  {
    switch (input_get(ictx, i, 0, -1))
    {
      case -1:
      {
        break;
      }

      case 4:
      {
        screen_write_mode_set(&ictx->ctx, 0x2);
        break;
      }

      case 34:
      {
        screen_write_mode_clear(&ictx->ctx, 0x80);
        break;
      }

      default:
      {
        log_debug("%s: unknown '%c'", __func__, ictx->ch);
        break;
      }

    }

  }

}


/*** DEPENDENCIES:
static int input_get(struct input_ctx *ictx, u_int validx, int minval, int defval)
{
  struct input_param *ip;
  unsigned int ip_idx = 0;
  int retval;
  if (validx >= ictx->param_list_len)
  {
    return defval;
  }
  ip_idx = &ictx->param_list[validx];
  if (ip->type == INPUT_MISSING)
  {
    return defval;
  }
  if (ip->type == INPUT_STRING)
  {
    return -1;
  }
  retval = ip->num;
  if (retval < minval)
  {
    return minval;
  }
  return retval;
}


----------------------------
void screen_write_mode_clear(struct screen_write_ctx *ctx, int mode)
{
  struct screen *s = ctx->s;
  s->mode &= ~mode;
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
void screen_write_mode_set(struct screen_write_ctx *ctx, int mode)
{
  struct screen *s = ctx->s;
  s->mode |= mode;
}


----------------------------
None
----------------------------
***/


// hint:  ['m_ref is a mutable refrence to int']
void helper_input_csi_dispatch_winops_1(int * const m_ref, struct input_ctx * const ictx, struct window_pane * const wp, int n)
{
  int m = *m_ref;
  switch (n)
  {
    case 1:

    case 2:

    case 5:

    case 6:

    case 7:

    case 11:

    case 13:

    case 14:

    case 19:

    case 20:

    case 21:

    case 24:
    {
      break;
    }

    case 3:

    case 4:

    case 8:
    {
      m += 1;
      if (input_get(ictx, m, 0, -1) == (-1))
      {
        return;
      }
    }

    case 9:

    case 10:
    {
      m += 1;
      if (input_get(ictx, m, 0, -1) == (-1))
      {
        return;
      }
      break;
    }

    case 22:
    {
      m += 1;
      switch (input_get(ictx, m, 0, -1))
      {
        case -1:
        {
          return;
        }

        case 0:

        case 2:
        {
          screen_push_title(ictx->ctx.s);
          break;
        }

      }

      break;
    }

    case 23:
    {
      m += 1;
      switch (input_get(ictx, m, 0, -1))
      {
        case -1:
        {
          return;
        }

        case 0:

        case 2:
        {
          screen_pop_title(ictx->ctx.s);
          server_status_window(ictx->wp->window);
          break;
        }

      }

      break;
    }

    case 18:
    {
      input_reply(ictx, "\033[8;%u;%ut", wp->sy, wp->sx);
      break;
    }

    default:
    {
      log_debug("%s: unknown '%c'", __func__, ictx->ch);
      break;
    }

  }

  m += 1;
  *m_ref = m;
}


/*** DEPENDENCIES:
static int input_get(struct input_ctx *ictx, u_int validx, int minval, int defval)
{
  struct input_param *ip;
  unsigned int ip_idx = 0;
  int retval;
  if (validx >= ictx->param_list_len)
  {
    return defval;
  }
  ip_idx = &ictx->param_list[validx];
  if (ip->type == INPUT_MISSING)
  {
    return defval;
  }
  if (ip->type == INPUT_STRING)
  {
    return -1;
  }
  retval = ip->num;
  if (retval < minval)
  {
    return minval;
  }
  return retval;
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
void input_reply(struct input_ctx *ictx, const char *fmt, ...)
{
  va_list ap;
  char *reply;
  __builtin_va_start(ap);
  xvasprintf(&reply, fmt, ap);
  ;
  bufferevent_write(ictx->wp->event, reply, strlen(reply));
  free(reply);
}


----------------------------
void screen_pop_title(struct screen *s)
{
  struct screen_title_entry *title_entry;
  unsigned int title_entry_idx = 0;
  if (s->titles == 0)
  {
    return;
  }
  title_entry_idx = s->titles->tqh_first;
  if ((&title_entry[title_entry_idx]) != 0)
  {
    screen_set_title(s, title_entry->text);
    do
    {
      if (title_entry->entry.tqe_next != 0)
      {
        title_entry->entry.tqe_next->entry.tqe_prev = title_entry->entry.tqe_prev;
      }
      else
        s->titles->tqh_last = title_entry->entry.tqe_prev;
      *title_entry->entry.tqe_prev = title_entry->entry.tqe_next;
      ;
      ;
    }
    while (0);
    free(title_entry->text);
    free(title_entry);
  }
}


----------------------------
void screen_push_title(struct screen *s)
{
  struct screen_title_entry *title_entry;
  unsigned int title_entry_idx = 0;
  if (s->titles == 0)
  {
    s->titles = xmalloc(sizeof(*s->titles));
    do
    {
      s->titles->tqh_first = 0;
      s->titles->tqh_last = &s->titles->tqh_first;
    }
    while (0);
  }
  title_entry_idx = xmalloc(sizeof(*title_entry_idx));
  title_entry->text = xstrdup(s->title);
  do
  {
    if ((title_entry->entry.tqe_next = s->titles->tqh_first) != 0)
    {
      s->titles->tqh_first->entry.tqe_prev = &title_entry->entry.tqe_next;
    }
    else
      s->titles->tqh_last = &title_entry->entry.tqe_next;
    s->titles->tqh_first = &title_entry[title_entry_idx];
    title_entry->entry.tqe_prev = &s->titles->tqh_first;
  }
  while (0);
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


static void input_csi_dispatch_winops(struct input_ctx *ictx)
{
  struct window_pane *wp = ictx->wp;
  int n;
  int m;
  m = 0;
  while ((n = input_get(ictx, m, 0, -1)) != (-1))
  {
    helper_input_csi_dispatch_winops_1(&m, ictx, wp, n);
  }

}


/*** DEPENDENCIES:
static int input_get(struct input_ctx *ictx, u_int validx, int minval, int defval)
{
  struct input_param *ip;
  unsigned int ip_idx = 0;
  int retval;
  if (validx >= ictx->param_list_len)
  {
    return defval;
  }
  ip_idx = &ictx->param_list[validx];
  if (ip->type == INPUT_MISSING)
  {
    return defval;
  }
  if (ip->type == INPUT_STRING)
  {
    return -1;
  }
  retval = ip->num;
  if (retval < minval)
  {
    return minval;
  }
  return retval;
}


----------------------------
void helper_input_csi_dispatch_winops_1(int * const m_ref, struct input_ctx * const ictx, struct window_pane * const wp, int n)
{
  int m = *m_ref;
  switch (n)
  {
    case 1:

    case 2:

    case 5:

    case 6:

    case 7:

    case 11:

    case 13:

    case 14:

    case 19:

    case 20:

    case 21:

    case 24:
    {
      break;
    }

    case 3:

    case 4:

    case 8:
    {
      m += 1;
      if (input_get(ictx, m, 0, -1) == (-1))
      {
        return;
      }
    }

    case 9:

    case 10:
    {
      m += 1;
      if (input_get(ictx, m, 0, -1) == (-1))
      {
        return;
      }
      break;
    }

    case 22:
    {
      m += 1;
      switch (input_get(ictx, m, 0, -1))
      {
        case -1:
        {
          return;
        }

        case 0:

        case 2:
        {
          screen_push_title(ictx->ctx.s);
          break;
        }

      }

      break;
    }

    case 23:
    {
      m += 1;
      switch (input_get(ictx, m, 0, -1))
      {
        case -1:
        {
          return;
        }

        case 0:

        case 2:
        {
          screen_pop_title(ictx->ctx.s);
          server_status_window(ictx->wp->window);
          break;
        }

      }

      break;
    }

    case 18:
    {
      input_reply(ictx, "\033[8;%u;%ut", wp->sy, wp->sx);
      break;
    }

    default:
    {
      log_debug("%s: unknown '%c'", __func__, ictx->ch);
      break;
    }

  }

  m += 1;
  *m_ref = m;
}


----------------------------
None
----------------------------
***/


static void input_csi_dispatch_sgr_colon(struct input_ctx *ictx, u_int i)
{
  char *s = ictx->param_list[i].str;
  char *copy;
  char *ptr;
  unsigned int ptr_idx = 0;
  char *out;
  unsigned int out_idx = 0;
  int p[8];
  u_int n;
  const char *errstr;
  for (n = 0; n < ((sizeof(p)) / (sizeof(p[0]))); n += 1)
  {
    p[n] = -1;
  }

  n = 0;
  ptr_idx = (copy = xstrdup(s));
  while ((out_idx = strsep(&(&ptr[ptr_idx]), ":")) != 0)
  {
    if (out[out_idx] != '\0')
    {
      p[n] = strtonum(out, 0, 2147483647, &errstr);
      n += 1;
      if ((errstr != 0) || (n == ((sizeof(p)) / (sizeof(p[0])))))
      {
        free(copy);
        return;
      }
    }
    log_debug("%s: %u = %d", __func__, n - 1, p[n - 1]);
  }

  free(copy);
  if ((n == 0) || ((p[0] != 38) && (p[0] != 48)))
  {
    return;
  }
  if (p[1] == (-1))
  {
    i = 2;
  }
  else
    i = 1;
  switch (p[i])
  {
    case 2:
    {
      if (n < (i + 4))
      {
        break;
      }
      input_csi_dispatch_sgr_rgb_do(ictx, p[0], p[i + 1], p[i + 2], p[i + 3]);
      break;
    }

    case 5:
    {
      if (n < (i + 2))
      {
        break;
      }
      input_csi_dispatch_sgr_256_do(ictx, p[0], p[i + 1]);
      break;
    }

  }

}


/*** DEPENDENCIES:
static int input_csi_dispatch_sgr_256_do(struct input_ctx *ictx, int fgbg, int c)
{
  struct grid_cell *gc = &ictx->cell.cell;
  if ((c == (-1)) || (c > 255))
  {
    if (fgbg == 38)
    {
      gc->fg = 8;
    }
    else
      if (fgbg == 48)
    {
      gc->bg = 8;
    }
  }
  else
  {
    if (fgbg == 38)
    {
      gc->fg = c | 0x01000000;
    }
    else
      if (fgbg == 48)
    {
      gc->bg = c | 0x01000000;
    }
  }
  return 1;
}


----------------------------
static int input_csi_dispatch_sgr_rgb_do(struct input_ctx *ictx, int fgbg, int r, int g, int b)
{
  struct grid_cell *gc = &ictx->cell.cell;
  if ((r == (-1)) || (r > 255))
  {
    return 0;
  }
  if ((g == (-1)) || (g > 255))
  {
    return 0;
  }
  if ((b == (-1)) || (b > 255))
  {
    return 0;
  }
  if (fgbg == 38)
  {
    gc->fg = colour_join_rgb(r, g, b);
  }
  else
    if (fgbg == 48)
  {
    gc->bg = colour_join_rgb(r, g, b);
  }
  return 1;
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
long long strtonum(const char *numstr, long long minval, long long maxval, const char **errstrp)
{
  long long ll = 0;
  char *ep;
  int error = 0;
  struct errval
  {
    const char *errstr;
    int err;
  } ev[4] = {{0, 0}, {"invalid", EINVAL}, {"too small", ERANGE}, {"too large", ERANGE}};
  ev[0].err = errno;
  errno = 0;
  if (minval > maxval)
  {
    error = 1;
  }
  else
  {
    ll = strtoll(numstr, &ep, 10);
    if ((numstr == ep) || ((*ep) != '\0'))
    {
      error = 1;
    }
    else
      if (((ll == LLONG_MIN) && (errno == ERANGE)) || (ll < minval))
    {
      error = 2;
    }
    else
      if (((ll == LLONG_MAX) && (errno == ERANGE)) || (ll > maxval))
    {
      error = 3;
    }
  }
  if (errstrp != 0)
  {
    *errstrp = ev[error].errstr;
  }
  errno = ev[error].err;
  if (error)
  {
    ll = 0;
  }
  return ll;
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


// hint:  ['i_ref is a mutable refrence to u_int', 'n_ref is a mutable refrence to int']
void helper_input_csi_dispatch_sgr_1(u_int * const i_ref, int * const n_ref, struct input_ctx * const ictx, struct grid_cell * const gc)
{
  u_int i = *i_ref;
  int n = *n_ref;
  if (ictx->param_list[i].type == INPUT_STRING)
  {
    input_csi_dispatch_sgr_colon(ictx, i);
    continue;
  }
  n = input_get(ictx, i, 0, 0);
  if (n == (-1))
  {
    continue;
  }
  if ((n == 38) || (n == 48))
  {
    i += 1;
    switch (input_get(ictx, i, 0, -1))
    {
      case 2:
      {
        input_csi_dispatch_sgr_rgb(ictx, n, &i);
        break;
      }

      case 5:
      {
        input_csi_dispatch_sgr_256(ictx, n, &i);
        break;
      }

    }

    continue;
  }
  switch (n)
  {
    case 0:
    {
      memcpy(gc, &grid_default_cell, sizeof(*gc));
      break;
    }

    case 1:
    {
      gc->attr |= 0x1;
      break;
    }

    case 2:
    {
      gc->attr |= 0x2;
      break;
    }

    case 3:
    {
      gc->attr |= 0x40;
      break;
    }

    case 4:
    {
      gc->attr |= 0x4;
      break;
    }

    case 5:
    {
      gc->attr |= 0x8;
      break;
    }

    case 7:
    {
      gc->attr |= 0x10;
      break;
    }

    case 8:
    {
      gc->attr |= 0x20;
      break;
    }

    case 9:
    {
      gc->attr |= 0x100;
      break;
    }

    case 22:
    {
      gc->attr &= ~(0x1 | 0x2);
      break;
    }

    case 23:
    {
      gc->attr &= ~0x40;
      break;
    }

    case 24:
    {
      gc->attr &= ~0x4;
      break;
    }

    case 25:
    {
      gc->attr &= ~0x8;
      break;
    }

    case 27:
    {
      gc->attr &= ~0x10;
      break;
    }

    case 28:
    {
      gc->attr &= ~0x20;
      break;
    }

    case 29:
    {
      gc->attr &= ~0x100;
      break;
    }

    case 30:

    case 31:

    case 32:

    case 33:

    case 34:

    case 35:

    case 36:

    case 37:
    {
      gc->fg = n - 30;
      break;
    }

    case 39:
    {
      gc->fg = 8;
      break;
    }

    case 40:

    case 41:

    case 42:

    case 43:

    case 44:

    case 45:

    case 46:

    case 47:
    {
      gc->bg = n - 40;
      break;
    }

    case 49:
    {
      gc->bg = 8;
      break;
    }

    case 90:

    case 91:

    case 92:

    case 93:

    case 94:

    case 95:

    case 96:

    case 97:
    {
      gc->fg = n;
      break;
    }

    case 100:

    case 101:

    case 102:

    case 103:

    case 104:

    case 105:

    case 106:

    case 107:
    {
      gc->bg = n - 10;
      break;
    }

  }

  *i_ref = i;
  *n_ref = n;
}


/*** DEPENDENCIES:
static int input_get(struct input_ctx *ictx, u_int validx, int minval, int defval)
{
  struct input_param *ip;
  unsigned int ip_idx = 0;
  int retval;
  if (validx >= ictx->param_list_len)
  {
    return defval;
  }
  ip_idx = &ictx->param_list[validx];
  if (ip->type == INPUT_MISSING)
  {
    return defval;
  }
  if (ip->type == INPUT_STRING)
  {
    return -1;
  }
  retval = ip->num;
  if (retval < minval)
  {
    return minval;
  }
  return retval;
}


----------------------------
extern const struct grid_cell grid_default_cell
----------------------------
static void input_csi_dispatch_sgr_256(struct input_ctx *ictx, int fgbg, u_int *i)
{
  int c;
  c = input_get(ictx, (*i) + 1, 0, -1);
  if (input_csi_dispatch_sgr_256_do(ictx, fgbg, c))
  {
    *i += 1;
  }
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
static void input_csi_dispatch_sgr_colon(struct input_ctx *ictx, u_int i)
{
  char *s = ictx->param_list[i].str;
  char *copy;
  char *ptr;
  unsigned int ptr_idx = 0;
  char *out;
  unsigned int out_idx = 0;
  int p[8];
  u_int n;
  const char *errstr;
  for (n = 0; n < ((sizeof(p)) / (sizeof(p[0]))); n += 1)
  {
    p[n] = -1;
  }

  n = 0;
  ptr_idx = (copy = xstrdup(s));
  while ((out_idx = strsep(&(&ptr[ptr_idx]), ":")) != 0)
  {
    if (out[out_idx] != '\0')
    {
      p[n] = strtonum(out, 0, 2147483647, &errstr);
      n += 1;
      if ((errstr != 0) || (n == ((sizeof(p)) / (sizeof(p[0])))))
      {
        free(copy);
        return;
      }
    }
    log_debug("%s: %u = %d", __func__, n - 1, p[n - 1]);
  }

  free(copy);
  if ((n == 0) || ((p[0] != 38) && (p[0] != 48)))
  {
    return;
  }
  if (p[1] == (-1))
  {
    i = 2;
  }
  else
    i = 1;
  switch (p[i])
  {
    case 2:
    {
      if (n < (i + 4))
      {
        break;
      }
      input_csi_dispatch_sgr_rgb_do(ictx, p[0], p[i + 1], p[i + 2], p[i + 3]);
      break;
    }

    case 5:
    {
      if (n < (i + 2))
      {
        break;
      }
      input_csi_dispatch_sgr_256_do(ictx, p[0], p[i + 1]);
      break;
    }

  }

}


----------------------------
None
----------------------------
static void input_csi_dispatch_sgr_rgb(struct input_ctx *ictx, int fgbg, u_int *i)
{
  int r;
  int g;
  int b;
  r = input_get(ictx, (*i) + 1, 0, -1);
  g = input_get(ictx, (*i) + 2, 0, -1);
  b = input_get(ictx, (*i) + 3, 0, -1);
  if (input_csi_dispatch_sgr_rgb_do(ictx, fgbg, r, g, b))
  {
    *i += 3;
  }
}


----------------------------
None
----------------------------
***/


static void input_csi_dispatch_sgr(struct input_ctx *ictx)
{
  struct grid_cell *gc = &ictx->cell.cell;
  u_int i;
  int n;
  if (ictx->param_list_len == 0)
  {
    memcpy(gc, &grid_default_cell, sizeof(*gc));
    return;
  }
  for (i = 0; i < ictx->param_list_len; i += 1)
  {
    helper_input_csi_dispatch_sgr_1(&i, &n, ictx, gc);
  }

}


/*** DEPENDENCIES:
void helper_input_csi_dispatch_sgr_1(u_int * const i_ref, int * const n_ref, struct input_ctx * const ictx, struct grid_cell * const gc)
{
  u_int i = *i_ref;
  int n = *n_ref;
  if (ictx->param_list[i].type == INPUT_STRING)
  {
    input_csi_dispatch_sgr_colon(ictx, i);
    continue;
  }
  n = input_get(ictx, i, 0, 0);
  if (n == (-1))
  {
    continue;
  }
  if ((n == 38) || (n == 48))
  {
    i += 1;
    switch (input_get(ictx, i, 0, -1))
    {
      case 2:
      {
        input_csi_dispatch_sgr_rgb(ictx, n, &i);
        break;
      }

      case 5:
      {
        input_csi_dispatch_sgr_256(ictx, n, &i);
        break;
      }

    }

    continue;
  }
  switch (n)
  {
    case 0:
    {
      memcpy(gc, &grid_default_cell, sizeof(*gc));
      break;
    }

    case 1:
    {
      gc->attr |= 0x1;
      break;
    }

    case 2:
    {
      gc->attr |= 0x2;
      break;
    }

    case 3:
    {
      gc->attr |= 0x40;
      break;
    }

    case 4:
    {
      gc->attr |= 0x4;
      break;
    }

    case 5:
    {
      gc->attr |= 0x8;
      break;
    }

    case 7:
    {
      gc->attr |= 0x10;
      break;
    }

    case 8:
    {
      gc->attr |= 0x20;
      break;
    }

    case 9:
    {
      gc->attr |= 0x100;
      break;
    }

    case 22:
    {
      gc->attr &= ~(0x1 | 0x2);
      break;
    }

    case 23:
    {
      gc->attr &= ~0x40;
      break;
    }

    case 24:
    {
      gc->attr &= ~0x4;
      break;
    }

    case 25:
    {
      gc->attr &= ~0x8;
      break;
    }

    case 27:
    {
      gc->attr &= ~0x10;
      break;
    }

    case 28:
    {
      gc->attr &= ~0x20;
      break;
    }

    case 29:
    {
      gc->attr &= ~0x100;
      break;
    }

    case 30:

    case 31:

    case 32:

    case 33:

    case 34:

    case 35:

    case 36:

    case 37:
    {
      gc->fg = n - 30;
      break;
    }

    case 39:
    {
      gc->fg = 8;
      break;
    }

    case 40:

    case 41:

    case 42:

    case 43:

    case 44:

    case 45:

    case 46:

    case 47:
    {
      gc->bg = n - 40;
      break;
    }

    case 49:
    {
      gc->bg = 8;
      break;
    }

    case 90:

    case 91:

    case 92:

    case 93:

    case 94:

    case 95:

    case 96:

    case 97:
    {
      gc->fg = n;
      break;
    }

    case 100:

    case 101:

    case 102:

    case 103:

    case 104:

    case 105:

    case 106:

    case 107:
    {
      gc->bg = n - 10;
      break;
    }

  }

  *i_ref = i;
  *n_ref = n;
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
None
----------------------------
extern const struct grid_cell grid_default_cell
----------------------------
None
----------------------------
***/


void input_reset(struct window_pane *wp, int clear)
{
  struct input_ctx *ictx = wp->ictx;
  input_reset_cell(ictx);
  if (clear)
  {
    if (wp->mode == 0)
    {
      screen_write_start(&ictx->ctx, wp, &wp->base);
    }
    else
      screen_write_start(&ictx->ctx, 0, &wp->base);
    screen_write_reset(&ictx->ctx);
    screen_write_stop(&ictx->ctx);
  }
  input_clear(ictx);
  ictx->last = -1;
  ictx->state = &input_state_ground;
  ictx->flags = 0;
}


/*** DEPENDENCIES:
static const struct input_state input_state_ground = {"ground", input_ground, 0, input_state_ground_table}
----------------------------
static void input_reset_cell(struct input_ctx *ictx)
{
  memcpy(&ictx->cell.cell, &grid_default_cell, sizeof(ictx->cell.cell));
  ictx->cell.set = 0;
  ictx->cell.g0set = (ictx->cell.g1set = 0);
  memcpy(&ictx->old_cell, &ictx->cell, sizeof(ictx->old_cell));
  ictx->old_cx = 0;
  ictx->old_cy = 0;
}


----------------------------
static void input_clear(struct input_ctx *ictx)
{
  event_del(&ictx->timer);
  *ictx->interm_buf = '\0';
  ictx->interm_len = 0;
  *ictx->param_buf = '\0';
  ictx->param_len = 0;
  *ictx->input_buf = '\0';
  ictx->input_len = 0;
  ictx->flags &= ~0x1;
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
void screen_write_reset(struct screen_write_ctx *ctx)
{
  struct screen *s = ctx->s;
  screen_reset_tabs(s);
  screen_write_scrollregion(ctx, 0, s->grid->sy - 1);
  s->mode &= ~(((0x2 | 0x4) | 0x8) | 0x800);
  s->mode &= ~((((0x20 | 0x40) | 0x1000) | 0x100) | 0x200);
  screen_write_clearscreen(ctx, 8);
  screen_write_cursormove(ctx, 0, 0);
}


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
None
----------------------------
***/


static void input_timer_callback(int fd, short events, void *arg)
{
  struct input_ctx *ictx = arg;
  struct window_pane *wp = ictx->wp;
  log_debug("%s: %%%u %s expired", __func__, wp->id, ictx->state->name);
  input_reset(wp, 0);
}


/*** DEPENDENCIES:
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
void input_reset(struct window_pane *wp, int clear)
{
  struct input_ctx *ictx = wp->ictx;
  input_reset_cell(ictx);
  if (clear)
  {
    if (wp->mode == 0)
    {
      screen_write_start(&ictx->ctx, wp, &wp->base);
    }
    else
      screen_write_start(&ictx->ctx, 0, &wp->base);
    screen_write_reset(&ictx->ctx);
    screen_write_stop(&ictx->ctx);
  }
  input_clear(ictx);
  ictx->last = -1;
  ictx->state = &input_state_ground;
  ictx->flags = 0;
}


----------------------------
None
----------------------------
***/


void helper_input_csi_dispatch_4(struct input_ctx * const ictx, struct screen * const s)
{
  switch (input_get(ictx, 0, 0, 0))
  {
    case -1:
    {
      break;
    }

    case 0:
    {
      if (s->cx < s->grid->sx)
      {
        s->tabs[s->cx >> 3] &= ~(1 << (s->cx & 0x7));
      }
      break;
    }

    case 3:
    {
      do
      {
        register bitstr_t *_name = s->tabs;
        register int _start = 0;
        register int _stop = s->grid->sx - 1;
        while (_start <= _stop)
        {
          _name[_start >> 3] &= ~(1 << (_start & 0x7));
          _start += 1;
        }

      }
      while (0);
      break;
    }

    default:
    {
      log_debug("%s: unknown '%c'", __func__, ictx->ch);
      break;
    }

  }

  break;
}


/*** DEPENDENCIES:
static int input_get(struct input_ctx *ictx, u_int validx, int minval, int defval)
{
  struct input_param *ip;
  unsigned int ip_idx = 0;
  int retval;
  if (validx >= ictx->param_list_len)
  {
    return defval;
  }
  ip_idx = &ictx->param_list[validx];
  if (ip->type == INPUT_MISSING)
  {
    return defval;
  }
  if (ip->type == INPUT_STRING)
  {
    return -1;
  }
  retval = ip->num;
  if (retval < minval)
  {
    return minval;
  }
  return retval;
}


----------------------------
typedef unsigned char bitstr_t
----------------------------
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


void input_init(struct window_pane *wp)
{
  struct input_ctx *ictx;
  unsigned int ictx_idx = 0;
  ictx_idx = (wp->ictx_idx = xcalloc(1, sizeof(*ictx_idx)));
  ictx->input_space = 32;
  ictx->input_buf = xmalloc(32);
  ictx->since_ground = evbuffer_new();
  evtimer_set(&ictx->timer, input_timer_callback, ictx);
  input_reset(wp, 0);
}


/*** DEPENDENCIES:
void input_reset(struct window_pane *wp, int clear)
{
  struct input_ctx *ictx = wp->ictx;
  input_reset_cell(ictx);
  if (clear)
  {
    if (wp->mode == 0)
    {
      screen_write_start(&ictx->ctx, wp, &wp->base);
    }
    else
      screen_write_start(&ictx->ctx, 0, &wp->base);
    screen_write_reset(&ictx->ctx);
    screen_write_stop(&ictx->ctx);
  }
  input_clear(ictx);
  ictx->last = -1;
  ictx->state = &input_state_ground;
  ictx->flags = 0;
}


----------------------------
static void input_timer_callback(int fd, short events, void *arg)
{
  struct input_ctx *ictx = arg;
  struct window_pane *wp = ictx->wp;
  log_debug("%s: %%%u %s expired", __func__, wp->id, ictx->state->name);
  input_reset(wp, 0);
}


----------------------------
void *xmalloc(size_t size)
{
  void *ptr;
  unsigned int ptr_idx = 0;
  if (size == 0)
  {
    fatalx("xmalloc: zero size");
  }
  ptr_idx = malloc(size);
  if ((&ptr[ptr_idx]) == 0)
  {
    fatalx("xmalloc: allocating %zu bytes: %s", size, strerror(errno));
  }
  return ptr;
}


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
None
----------------------------
***/


static int input_top_bit_set(struct input_ctx *ictx)
{
  struct utf8_data *ud = &ictx->utf8data;
  ictx->last = -1;
  if (!ictx->utf8started)
  {
    if (utf8_open(ud, ictx->ch) != UTF8_MORE)
    {
      return 0;
    }
    ictx->utf8started = 1;
    return 0;
  }
  switch (utf8_append(ud, ictx->ch))
  {
    case UTF8_MORE:
    {
      return 0;
    }

    case UTF8_ERROR:
    {
      ictx->utf8started = 0;
      return 0;
    }

    case UTF8_DONE:
    {
      break;
    }

  }

  ictx->utf8started = 0;
  log_debug("%s %hhu '%*s' (width %hhu)", __func__, ud->size, (int) ud->size, ud->data, ud->width);
  utf8_copy(&ictx->cell.cell.data, ud);
  screen_write_collect_add(&ictx->ctx, &ictx->cell.cell);
  return 0;
}


/*** DEPENDENCIES:
void utf8_copy(struct utf8_data *to, const struct utf8_data *from)
{
  u_int i;
  memcpy(to, from, sizeof(*to));
  for (i = to->size; i < (sizeof(to->data)); i += 1)
  {
    to->data[i] = '\0';
  }

}


----------------------------
void screen_write_collect_add(struct screen_write_ctx *ctx, const struct grid_cell *gc)
{
  struct screen *s = ctx->s;
  struct screen_write_collect_item *ci;
  unsigned int ci_idx = 0;
  u_int sx = s->grid->sx;
  int collect;
  collect = 1;
  if (((gc->data.width != 1) || (gc->data.size != 1)) || ((*gc->data.data) >= 0x7f))
  {
    collect = 0;
  }
  else
    if (gc->attr & 0x80)
  {
    collect = 0;
  }
  else
    if ((~s->mode) & 0x10)
  {
    collect = 0;
  }
  else
    if (s->mode & 0x2)
  {
    collect = 0;
  }
  else
    if (s->sel.flag)
  {
    collect = 0;
  }
  if (!collect)
  {
    screen_write_collect_end(ctx);
    screen_write_collect_flush(ctx, 0);
    screen_write_cell(ctx, gc);
    return;
  }
  ctx->cells += 1;
  if ((s->cx > (sx - 1)) || (ctx->item->used > ((sx - 1) - s->cx)))
  {
    screen_write_collect_end(ctx);
  }
  ci_idx = ctx->item;
  if (s->cx > (sx - 1))
  {
    log_debug("%s: wrapped at %u,%u", __func__, s->cx, s->cy);
    ci->wrapped = 1;
    screen_write_linefeed(ctx, 1, 8);
    s->cx = 0;
  }
  if (ci->used == 0)
  {
    memcpy(&ci->gc, gc, sizeof(ci->gc));
  }
  ci->data[ci->used++] = gc->data.data[0];
  if (ci->used == ((sizeof(ci->data)) - 1))
  {
    screen_write_collect_end(ctx);
  }
}


----------------------------
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
}
----------------------------
enum utf8_state utf8_open(struct utf8_data *ud, u_char ch)
{
  memset(ud, 0, sizeof(*ud));
  if ((ch >= 0xc2) && (ch <= 0xdf))
  {
    ud->size = 2;
  }
  else
    if ((ch >= 0xe0) && (ch <= 0xef))
  {
    ud->size = 3;
  }
  else
    if ((ch >= 0xf0) && (ch <= 0xf4))
  {
    ud->size = 4;
  }
  else
    return UTF8_ERROR;
  utf8_append(ud, ch);
  return UTF8_MORE;
}


----------------------------
enum utf8_state utf8_append(struct utf8_data *ud, u_char ch)
{
  wchar_t wc;
  int width;
  if (ud->have >= ud->size)
  {
    fatalx("UTF-8 character overflow");
  }
  if (ud->size > (sizeof(ud->data)))
  {
    fatalx("UTF-8 character size too large");
  }
  if ((ud->have != 0) && ((ch & 0xc0) != 0x80))
  {
    ud->width = 0xff;
  }
  ud->data[ud->have++] = ch;
  if (ud->have != ud->size)
  {
    return UTF8_MORE;
  }
  if (ud->width == 0xff)
  {
    return UTF8_ERROR;
  }
  if (utf8_combine(ud, &wc) != UTF8_DONE)
  {
    return UTF8_ERROR;
  }
  if ((width = utf8_width(wc)) < 0)
  {
    return UTF8_ERROR;
  }
  ud->width = width;
  return UTF8_DONE;
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


void helper_input_csi_dispatch_2(struct input_ctx * const ictx, struct screen_write_ctx * const sctx, u_int bg)
{
  switch (input_get(ictx, 0, 0, 0))
  {
    case -1:
    {
      break;
    }

    case 0:
    {
      screen_write_clearendofline(sctx, bg);
      break;
    }

    case 1:
    {
      screen_write_clearstartofline(sctx, bg);
      break;
    }

    case 2:
    {
      screen_write_clearline(sctx, bg);
      break;
    }

    default:
    {
      log_debug("%s: unknown '%c'", __func__, ictx->ch);
      break;
    }

  }

  break;
}


/*** DEPENDENCIES:
static int input_get(struct input_ctx *ictx, u_int validx, int minval, int defval)
{
  struct input_param *ip;
  unsigned int ip_idx = 0;
  int retval;
  if (validx >= ictx->param_list_len)
  {
    return defval;
  }
  ip_idx = &ictx->param_list[validx];
  if (ip->type == INPUT_MISSING)
  {
    return defval;
  }
  if (ip->type == INPUT_STRING)
  {
    return -1;
  }
  retval = ip->num;
  if (retval < minval)
  {
    return minval;
  }
  return retval;
}


----------------------------
void screen_write_clearline(struct screen_write_ctx *ctx, u_int bg)
{
  struct screen *s = ctx->s;
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  struct tty_ctx ttyctx;
  u_int sx = s->grid->sx;
  gl_idx = &s->grid->linedata[s->grid->hsize + s->cy];
  if ((gl->cellsize == 0) && (bg == 8))
  {
    return;
  }
  screen_write_initctx(ctx, &ttyctx);
  ttyctx.bg = bg;
  grid_view_clear(s->grid, 0, s->cy, sx, 1, bg);
  screen_write_collect_clear(ctx, s->cy, 1);
  screen_write_collect_flush(ctx, 0);
  tty_write(tty_cmd_clearline, &ttyctx);
}


----------------------------
void screen_write_clearstartofline(struct screen_write_ctx *ctx, u_int bg)
{
  struct screen *s = ctx->s;
  struct tty_ctx ttyctx;
  u_int sx = s->grid->sx;
  screen_write_initctx(ctx, &ttyctx);
  ttyctx.bg = bg;
  if (s->cx > (sx - 1))
  {
    grid_view_clear(s->grid, 0, s->cy, sx, 1, bg);
  }
  else
    grid_view_clear(s->grid, 0, s->cy, s->cx + 1, 1, bg);
  if (s->cx > (sx - 1))
  {
    screen_write_collect_clear(ctx, s->cy, 1);
  }
  screen_write_collect_flush(ctx, 0);
  tty_write(tty_cmd_clearstartofline, &ttyctx);
}


----------------------------
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
void screen_write_clearendofline(struct screen_write_ctx *ctx, u_int bg)
{
  struct screen *s = ctx->s;
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  struct tty_ctx ttyctx;
  u_int sx = s->grid->sx;
  gl_idx = &s->grid->linedata[s->grid->hsize + s->cy];
  if ((s->cx > (sx - 1)) || ((s->cx >= gl->cellsize) && (bg == 8)))
  {
    return;
  }
  screen_write_initctx(ctx, &ttyctx);
  ttyctx.bg = bg;
  grid_view_clear(s->grid, s->cx, s->cy, sx - s->cx, 1, bg);
  if (s->cx == 0)
  {
    screen_write_collect_clear(ctx, s->cy, 1);
  }
  screen_write_collect_flush(ctx, 0);
  tty_write(tty_cmd_clearendofline, &ttyctx);
}


----------------------------
None
----------------------------
***/


void helper_input_csi_dispatch_3(struct input_ctx * const ictx, struct screen_write_ctx * const sctx, u_int bg)
{
  switch (input_get(ictx, 0, 0, 0))
  {
    case -1:
    {
      break;
    }

    case 0:
    {
      screen_write_clearendofscreen(sctx, bg);
      break;
    }

    case 1:
    {
      screen_write_clearstartofscreen(sctx, bg);
      break;
    }

    case 2:
    {
      screen_write_clearscreen(sctx, bg);
      break;
    }

    case 3:
    {
      if (input_get(ictx, 1, 0, 0) == 0)
      {
        screen_write_clearhistory(sctx);
      }
      break;
    }

    default:
    {
      log_debug("%s: unknown '%c'", __func__, ictx->ch);
      break;
    }

  }

  break;
}


/*** DEPENDENCIES:
static int input_get(struct input_ctx *ictx, u_int validx, int minval, int defval)
{
  struct input_param *ip;
  unsigned int ip_idx = 0;
  int retval;
  if (validx >= ictx->param_list_len)
  {
    return defval;
  }
  ip_idx = &ictx->param_list[validx];
  if (ip->type == INPUT_MISSING)
  {
    return defval;
  }
  if (ip->type == INPUT_STRING)
  {
    return -1;
  }
  retval = ip->num;
  if (retval < minval)
  {
    return minval;
  }
  return retval;
}


----------------------------
void screen_write_clearstartofscreen(struct screen_write_ctx *ctx, u_int bg)
{
  struct screen *s = ctx->s;
  struct tty_ctx ttyctx;
  u_int sx = s->grid->sx;
  screen_write_initctx(ctx, &ttyctx);
  ttyctx.bg = bg;
  if (s->cy > 0)
  {
    grid_view_clear(s->grid, 0, 0, sx, s->cy, bg);
  }
  if (s->cx > (sx - 1))
  {
    grid_view_clear(s->grid, 0, s->cy, sx, 1, bg);
  }
  else
    grid_view_clear(s->grid, 0, s->cy, s->cx + 1, 1, bg);
  screen_write_collect_clear(ctx, 0, s->cy);
  screen_write_collect_flush(ctx, 0);
  tty_write(tty_cmd_clearstartofscreen, &ttyctx);
}


----------------------------
void screen_write_clearendofscreen(struct screen_write_ctx *ctx, u_int bg)
{
  struct screen *s = ctx->s;
  struct grid *gd = s->grid;
  struct tty_ctx ttyctx;
  u_int sx = s->grid->sx;
  u_int sy = s->grid->sy;
  screen_write_initctx(ctx, &ttyctx);
  ttyctx.bg = bg;
  if (((s->cx == 0) && (s->cy == 0)) && (gd->flags & 0x1))
  {
    grid_view_clear_history(gd, bg);
  }
  else
  {
    if (s->cx <= (sx - 1))
    {
      grid_view_clear(gd, s->cx, s->cy, sx - s->cx, 1, bg);
    }
    grid_view_clear(gd, 0, s->cy + 1, sx, sy - (s->cy + 1), bg);
  }
  screen_write_collect_clear(ctx, s->cy + 1, sy - (s->cy + 1));
  screen_write_collect_flush(ctx, 0);
  tty_write(tty_cmd_clearendofscreen, &ttyctx);
}


----------------------------
void screen_write_clearhistory(struct screen_write_ctx *ctx)
{
  struct screen *s = ctx->s;
  struct grid *gd = s->grid;
  grid_move_lines(gd, 0, gd->hsize, gd->sy, 8);
  gd->hscrolled = (gd->hsize = 0);
}


----------------------------
None
----------------------------
void screen_write_clearscreen(struct screen_write_ctx *ctx, u_int bg)
{
  struct screen *s = ctx->s;
  struct tty_ctx ttyctx;
  u_int sx = s->grid->sx;
  u_int sy = s->grid->sy;
  screen_write_initctx(ctx, &ttyctx);
  ttyctx.bg = bg;
  if (s->grid->flags & 0x1)
  {
    grid_view_clear_history(s->grid, bg);
  }
  else
    grid_view_clear(s->grid, 0, 0, sx, sy, bg);
  screen_write_collect_clear(ctx, 0, sy);
  tty_write(tty_cmd_clearscreen, &ttyctx);
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


static int input_c0_dispatch(struct input_ctx *ictx)
{
  struct screen_write_ctx *sctx = &ictx->ctx;
  struct window_pane *wp = ictx->wp;
  struct screen *s = sctx->s;
  ictx->utf8started = 0;
  log_debug("%s: '%c'", __func__, ictx->ch);
  switch (ictx->ch)
  {
    case '\000':
    {
      break;
    }

    case '\007':
    {
      alerts_queue(wp->window, 0x1);
      break;
    }

    case '\010':
    {
      screen_write_backspace(sctx);
      break;
    }

    case '\011':
    {
      if (s->cx >= (s->grid->sx - 1))
      {
        break;
      }
      do
      {
        s->cx += 1;
        if (s->tabs[s->cx >> 3] & (1 << (s->cx & 0x7)))
        {
          break;
        }
      }
      while (s->cx < (s->grid->sx - 1));
      break;
    }

    case '\012':

    case '\013':

    case '\014':
    {
      screen_write_linefeed(sctx, 0, ictx->cell.cell.bg);
      break;
    }

    case '\015':
    {
      screen_write_carriagereturn(sctx);
      break;
    }

    case '\016':
    {
      ictx->cell.set = 1;
      break;
    }

    case '\017':
    {
      ictx->cell.set = 0;
      break;
    }

    default:
    {
      log_debug("%s: unknown '%c'", __func__, ictx->ch);
      break;
    }

  }

  ictx->last = -1;
  return 0;
}


/*** DEPENDENCIES:
void screen_write_carriagereturn(struct screen_write_ctx *ctx)
{
  struct screen *s = ctx->s;
  s->cx = 0;
}


----------------------------
void screen_write_backspace(struct screen_write_ctx *ctx)
{
  struct screen *s = ctx->s;
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  if (s->cx == 0)
  {
    if (s->cy == 0)
    {
      return;
    }
    gl_idx = &s->grid->linedata[(s->grid->hsize + s->cy) - 1];
    if (gl->flags & 0x1)
    {
      s->cy -= 1;
      s->cx = s->grid->sx - 1;
    }
  }
  else
    s->cx--;
}


----------------------------
None
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


static int input_esc_dispatch(struct input_ctx *ictx)
{
  struct screen_write_ctx *sctx = &ictx->ctx;
  struct screen *s = sctx->s;
  struct input_table_entry *entry;
  unsigned int entry_idx = 0;
  if (ictx->flags & 0x1)
  {
    return 0;
  }
  log_debug("%s: '%c', %s", __func__, ictx->ch, ictx->interm_buf);
  entry_idx = bsearch(ictx, input_esc_table, (sizeof(input_esc_table)) / (sizeof(input_esc_table[0])), sizeof(input_esc_table[0]), input_table_compare);
  if ((&entry[entry_idx]) == 0)
  {
    log_debug("%s: unknown '%c'", __func__, ictx->ch);
    return 0;
  }
  switch (entry->type)
  {
    case INPUT_ESC_RIS:
    {
      window_pane_reset_palette(ictx->wp);
      input_reset_cell(ictx);
      screen_write_reset(sctx);
      break;
    }

    case INPUT_ESC_IND:
    {
      screen_write_linefeed(sctx, 0, ictx->cell.cell.bg);
      break;
    }

    case INPUT_ESC_NEL:
    {
      screen_write_carriagereturn(sctx);
      screen_write_linefeed(sctx, 0, ictx->cell.cell.bg);
      break;
    }

    case INPUT_ESC_HTS:
    {
      if (s->cx < s->grid->sx)
      {
        s->tabs[s->cx >> 3] |= 1 << (s->cx & 0x7);
      }
      break;
    }

    case INPUT_ESC_RI:
    {
      screen_write_reverseindex(sctx, ictx->cell.cell.bg);
      break;
    }

    case INPUT_ESC_DECKPAM:
    {
      screen_write_mode_set(sctx, 0x8);
      break;
    }

    case INPUT_ESC_DECKPNM:
    {
      screen_write_mode_clear(sctx, 0x8);
      break;
    }

    case INPUT_ESC_DECSC:
    {
      memcpy(&ictx->old_cell, &ictx->cell, sizeof(ictx->old_cell));
      ictx->old_cx = s->cx;
      ictx->old_cy = s->cy;
      break;
    }

    case INPUT_ESC_DECRC:
    {
      memcpy(&ictx->cell, &ictx->old_cell, sizeof(ictx->cell));
      screen_write_cursormove(sctx, ictx->old_cx, ictx->old_cy);
      break;
    }

    case INPUT_ESC_DECALN:
    {
      screen_write_alignmenttest(sctx);
      break;
    }

    case INPUT_ESC_SCSG0_ON:
    {
      ictx->cell.g0set = 1;
      break;
    }

    case INPUT_ESC_SCSG0_OFF:
    {
      ictx->cell.g0set = 0;
      break;
    }

    case INPUT_ESC_SCSG1_ON:
    {
      ictx->cell.g1set = 1;
      break;
    }

    case INPUT_ESC_SCSG1_OFF:
    {
      ictx->cell.g1set = 0;
      break;
    }

    case INPUT_ESC_ST:
    {
      break;
    }

  }

  ictx->last = -1;
  return 0;
}


/*** DEPENDENCIES:
static void input_reset_cell(struct input_ctx *ictx)
{
  memcpy(&ictx->cell.cell, &grid_default_cell, sizeof(ictx->cell.cell));
  ictx->cell.set = 0;
  ictx->cell.g0set = (ictx->cell.g1set = 0);
  memcpy(&ictx->old_cell, &ictx->cell, sizeof(ictx->old_cell));
  ictx->old_cx = 0;
  ictx->old_cy = 0;
}


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
void screen_write_mode_clear(struct screen_write_ctx *ctx, int mode)
{
  struct screen *s = ctx->s;
  s->mode &= ~mode;
}


----------------------------
static const struct input_table_entry input_esc_table[] = {{'0', "(", INPUT_ESC_SCSG0_ON}, {'0', ")", INPUT_ESC_SCSG1_ON}, {'7', "", INPUT_ESC_DECSC}, {'8', "", INPUT_ESC_DECRC}, {'8', "#", INPUT_ESC_DECALN}, {'=', "", INPUT_ESC_DECKPAM}, {'>', "", INPUT_ESC_DECKPNM}, {'B', "(", INPUT_ESC_SCSG0_OFF}, {'B', ")", INPUT_ESC_SCSG1_OFF}, {'D', "", INPUT_ESC_IND}, {'E', "", INPUT_ESC_NEL}, {'H', "", INPUT_ESC_HTS}, {'M', "", INPUT_ESC_RI}, {'\\', "", INPUT_ESC_ST}, {'c', "", INPUT_ESC_RIS}}
----------------------------
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
void screen_write_mode_set(struct screen_write_ctx *ctx, int mode)
{
  struct screen *s = ctx->s;
  s->mode |= mode;
}


----------------------------
void screen_write_carriagereturn(struct screen_write_ctx *ctx)
{
  struct screen *s = ctx->s;
  s->cx = 0;
}


----------------------------
void window_pane_reset_palette(struct window_pane *wp)
{
  if (wp->palette == 0)
  {
    return;
  }
  free(wp->palette);
  wp->palette = 0;
  wp->flags |= 0x1;
}


----------------------------
struct input_table_entry
{
  int ch;
  const char *interm;
  int type;
}
----------------------------
static int input_table_compare(const void *key, const void *value)
{
  const struct input_ctx *ictx = key;
  const struct input_table_entry *entry = value;
  if (ictx->ch != entry->ch)
  {
    return ictx->ch - entry->ch;
  }
  return strcmp(ictx->interm_buf, entry->interm);
}


----------------------------
void screen_write_reverseindex(struct screen_write_ctx *ctx, u_int bg)
{
  struct screen *s = ctx->s;
  struct tty_ctx ttyctx;
  screen_write_initctx(ctx, &ttyctx);
  ttyctx.bg = bg;
  if (s->cy == s->rupper)
  {
    grid_view_scroll_region_down(s->grid, s->rupper, s->rlower, bg);
  }
  else
    if (s->cy > 0)
  {
    s->cy -= 1;
  }
  screen_write_collect_flush(ctx, 0);
  tty_write(tty_cmd_reverseindex, &ttyctx);
}


----------------------------
void screen_write_alignmenttest(struct screen_write_ctx *ctx)
{
  struct screen *s = ctx->s;
  struct tty_ctx ttyctx;
  struct grid_cell gc;
  u_int xx;
  u_int yy;
  screen_write_initctx(ctx, &ttyctx);
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  utf8_set(&gc.data, 'E');
  for (yy = 0; yy < s->grid->sy; yy += 1)
  {
    for (xx = 0; xx < s->grid->sx; xx += 1)
    {
      grid_view_set_cell(s->grid, xx, yy, &gc);
    }

  }

  s->cx = 0;
  s->cy = 0;
  s->rupper = 0;
  s->rlower = s->grid->sy - 1;
  screen_write_collect_clear(ctx, 0, s->grid->sy - 1);
  tty_write(tty_cmd_alignmenttest, &ttyctx);
}


----------------------------
void screen_write_reset(struct screen_write_ctx *ctx)
{
  struct screen *s = ctx->s;
  screen_reset_tabs(s);
  screen_write_scrollregion(ctx, 0, s->grid->sy - 1);
  s->mode &= ~(((0x2 | 0x4) | 0x8) | 0x800);
  s->mode &= ~((((0x20 | 0x40) | 0x1000) | 0x100) | 0x200);
  screen_write_clearscreen(ctx, 8);
  screen_write_cursormove(ctx, 0, 0);
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
None
----------------------------
***/


static int input_csi_dispatch(struct input_ctx *ictx)
{
  struct screen_write_ctx *sctx = &ictx->ctx;
  struct screen *s = sctx->s;
  struct input_table_entry *entry;
  unsigned int entry_idx = 0;
  int i;
  int n;
  int m;
  u_int cx;
  u_int bg = ictx->cell.cell.bg;
  if (ictx->flags & 0x1)
  {
    return 0;
  }
  log_debug("%s: '%c' \"%s\" \"%s\"", __func__, ictx->ch, ictx->interm_buf, ictx->param_buf);
  if (input_split(ictx) != 0)
  {
    return 0;
  }
  entry_idx = bsearch(ictx, input_csi_table, (sizeof(input_csi_table)) / (sizeof(input_csi_table[0])), sizeof(input_csi_table[0]), input_table_compare);
  if ((&entry[entry_idx]) == 0)
  {
    log_debug("%s: unknown '%c'", __func__, ictx->ch);
    return 0;
  }
  switch (entry->type)
  {
    case INPUT_CSI_CBT:
    {
      helper_input_csi_dispatch_1(&n, &cx, ictx, s);
    }

    case INPUT_CSI_CUB:
    {
      n = input_get(ictx, 0, 1, 1);
      if (n != (-1))
      {
        screen_write_cursorleft(sctx, n);
      }
      break;
    }

    case INPUT_CSI_CUD:
    {
      n = input_get(ictx, 0, 1, 1);
      if (n != (-1))
      {
        screen_write_cursordown(sctx, n);
      }
      break;
    }

    case INPUT_CSI_CUF:
    {
      n = input_get(ictx, 0, 1, 1);
      if (n != (-1))
      {
        screen_write_cursorright(sctx, n);
      }
      break;
    }

    case INPUT_CSI_CUP:
    {
      n = input_get(ictx, 0, 1, 1);
      m = input_get(ictx, 1, 1, 1);
      if ((n != (-1)) && (m != (-1)))
      {
        screen_write_cursormove(sctx, m - 1, n - 1);
      }
      break;
    }

    case INPUT_CSI_WINOPS:
    {
      input_csi_dispatch_winops(ictx);
      break;
    }

    case INPUT_CSI_CUU:
    {
      n = input_get(ictx, 0, 1, 1);
      if (n != (-1))
      {
        screen_write_cursorup(sctx, n);
      }
      break;
    }

    case INPUT_CSI_CNL:
    {
      n = input_get(ictx, 0, 1, 1);
      if (n != (-1))
      {
        screen_write_carriagereturn(sctx);
        screen_write_cursordown(sctx, n);
      }
      break;
    }

    case INPUT_CSI_CPL:
    {
      n = input_get(ictx, 0, 1, 1);
      if (n != (-1))
      {
        screen_write_carriagereturn(sctx);
        screen_write_cursorup(sctx, n);
      }
      break;
    }

    case INPUT_CSI_DA:
    {
      switch (input_get(ictx, 0, 0, 0))
      {
        case -1:
        {
          break;
        }

        case 0:
        {
          input_reply(ictx, "\033[?1;2c");
          break;
        }

        default:
        {
          log_debug("%s: unknown '%c'", __func__, ictx->ch);
          break;
        }

      }

      break;
    }

    case INPUT_CSI_DA_TWO:
    {
      switch (input_get(ictx, 0, 0, 0))
      {
        case -1:
        {
          break;
        }

        case 0:
        {
          input_reply(ictx, "\033[>84;0;0c");
          break;
        }

        default:
        {
          log_debug("%s: unknown '%c'", __func__, ictx->ch);
          break;
        }

      }

      break;
    }

    case INPUT_CSI_ECH:
    {
      n = input_get(ictx, 0, 1, 1);
      if (n != (-1))
      {
        screen_write_clearcharacter(sctx, n, bg);
      }
      break;
    }

    case INPUT_CSI_DCH:
    {
      n = input_get(ictx, 0, 1, 1);
      if (n != (-1))
      {
        screen_write_deletecharacter(sctx, n, bg);
      }
      break;
    }

    case INPUT_CSI_DECSTBM:
    {
      n = input_get(ictx, 0, 1, 1);
      m = input_get(ictx, 1, 1, s->grid->sy);
      if ((n != (-1)) && (m != (-1)))
      {
        screen_write_scrollregion(sctx, n - 1, m - 1);
      }
      break;
    }

    case INPUT_CSI_DL:
    {
      n = input_get(ictx, 0, 1, 1);
      if (n != (-1))
      {
        screen_write_deleteline(sctx, n, bg);
      }
      break;
    }

    case INPUT_CSI_DSR:
    {
      switch (input_get(ictx, 0, 0, 0))
      {
        case -1:
        {
          break;
        }

        case 5:
        {
          input_reply(ictx, "\033[0n");
          break;
        }

        case 6:
        {
          input_reply(ictx, "\033[%u;%uR", s->cy + 1, s->cx + 1);
          break;
        }

        default:
        {
          log_debug("%s: unknown '%c'", __func__, ictx->ch);
          break;
        }

      }

      break;
    }

    case INPUT_CSI_ED:
    {
      helper_input_csi_dispatch_3(ictx, sctx, bg);
    }

    case INPUT_CSI_EL:
    {
      helper_input_csi_dispatch_2(ictx, sctx, bg);
    }

    case INPUT_CSI_HPA:
    {
      n = input_get(ictx, 0, 1, 1);
      if (n != (-1))
      {
        screen_write_cursormove(sctx, n - 1, s->cy);
      }
      break;
    }

    case INPUT_CSI_ICH:
    {
      n = input_get(ictx, 0, 1, 1);
      if (n != (-1))
      {
        screen_write_insertcharacter(sctx, n, bg);
      }
      break;
    }

    case INPUT_CSI_IL:
    {
      n = input_get(ictx, 0, 1, 1);
      if (n != (-1))
      {
        screen_write_insertline(sctx, n, bg);
      }
      break;
    }

    case INPUT_CSI_REP:
    {
      n = input_get(ictx, 0, 1, 1);
      if (n == (-1))
      {
        break;
      }
      if (ictx->last == (-1))
      {
        break;
      }
      ictx->ch = ictx->last;
      for (i = 0; i < n; i += 1)
      {
        input_print(ictx);
      }

      break;
    }

    case INPUT_CSI_RCP:
    {
      memcpy(&ictx->cell, &ictx->old_cell, sizeof(ictx->cell));
      screen_write_cursormove(sctx, ictx->old_cx, ictx->old_cy);
      break;
    }

    case INPUT_CSI_RM:
    {
      input_csi_dispatch_rm(ictx);
      break;
    }

    case INPUT_CSI_RM_PRIVATE:
    {
      input_csi_dispatch_rm_private(ictx);
      break;
    }

    case INPUT_CSI_SCP:
    {
      memcpy(&ictx->old_cell, &ictx->cell, sizeof(ictx->old_cell));
      ictx->old_cx = s->cx;
      ictx->old_cy = s->cy;
      break;
    }

    case INPUT_CSI_SGR:
    {
      input_csi_dispatch_sgr(ictx);
      break;
    }

    case INPUT_CSI_SM:
    {
      input_csi_dispatch_sm(ictx);
      break;
    }

    case INPUT_CSI_SM_PRIVATE:
    {
      input_csi_dispatch_sm_private(ictx);
      break;
    }

    case INPUT_CSI_SU:
    {
      n = input_get(ictx, 0, 1, 1);
      if (n != (-1))
      {
        screen_write_scrollup(sctx, n, bg);
      }
      break;
    }

    case INPUT_CSI_TBC:
    {
      helper_input_csi_dispatch_4(ictx, s);
    }

    case INPUT_CSI_VPA:
    {
      n = input_get(ictx, 0, 1, 1);
      if (n != (-1))
      {
        screen_write_cursormove(sctx, s->cx, n - 1);
      }
      break;
    }

    case INPUT_CSI_DECSCUSR:
    {
      n = input_get(ictx, 0, 0, 0);
      if (n != (-1))
      {
        screen_set_cursor_style(s, n);
      }
      break;
    }

  }

  ictx->last = -1;
  return 0;
}


/*** DEPENDENCIES:
static int input_get(struct input_ctx *ictx, u_int validx, int minval, int defval)
{
  struct input_param *ip;
  unsigned int ip_idx = 0;
  int retval;
  if (validx >= ictx->param_list_len)
  {
    return defval;
  }
  ip_idx = &ictx->param_list[validx];
  if (ip->type == INPUT_MISSING)
  {
    return defval;
  }
  if (ip->type == INPUT_STRING)
  {
    return -1;
  }
  retval = ip->num;
  if (retval < minval)
  {
    return minval;
  }
  return retval;
}


----------------------------
void helper_input_csi_dispatch_3(struct input_ctx * const ictx, struct screen_write_ctx * const sctx, u_int bg)
{
  switch (input_get(ictx, 0, 0, 0))
  {
    case -1:
    {
      break;
    }

    case 0:
    {
      screen_write_clearendofscreen(sctx, bg);
      break;
    }

    case 1:
    {
      screen_write_clearstartofscreen(sctx, bg);
      break;
    }

    case 2:
    {
      screen_write_clearscreen(sctx, bg);
      break;
    }

    case 3:
    {
      if (input_get(ictx, 1, 0, 0) == 0)
      {
        screen_write_clearhistory(sctx);
      }
      break;
    }

    default:
    {
      log_debug("%s: unknown '%c'", __func__, ictx->ch);
      break;
    }

  }

  break;
}


----------------------------
void screen_write_cursorleft(struct screen_write_ctx *ctx, u_int nx)
{
  struct screen *s = ctx->s;
  if (nx == 0)
  {
    nx = 1;
  }
  if (nx > s->cx)
  {
    nx = s->cx;
  }
  if (nx == 0)
  {
    return;
  }
  s->cx -= nx;
}


----------------------------
void screen_write_deletecharacter(struct screen_write_ctx *ctx, u_int nx, u_int bg)
{
  struct screen *s = ctx->s;
  struct tty_ctx ttyctx;
  if (nx == 0)
  {
    nx = 1;
  }
  if (nx > (s->grid->sx - s->cx))
  {
    nx = s->grid->sx - s->cx;
  }
  if (nx == 0)
  {
    return;
  }
  if (s->cx > (s->grid->sx - 1))
  {
    return;
  }
  screen_write_initctx(ctx, &ttyctx);
  ttyctx.bg = bg;
  grid_view_delete_cells(s->grid, s->cx, s->cy, nx, bg);
  screen_write_collect_flush(ctx, 0);
  ttyctx.num = nx;
  tty_write(tty_cmd_deletecharacter, &ttyctx);
}


----------------------------
void screen_write_cursordown(struct screen_write_ctx *ctx, u_int ny)
{
  struct screen *s = ctx->s;
  if (ny == 0)
  {
    ny = 1;
  }
  if (s->cy > s->rlower)
  {
    if (ny > ((s->grid->sy - 1) - s->cy))
    {
      ny = (s->grid->sy - 1) - s->cy;
    }
  }
  else
  {
    if (ny > (s->rlower - s->cy))
    {
      ny = s->rlower - s->cy;
    }
  }
  if (s->cx == s->grid->sx)
  {
    s->cx -= 1;
  }
  if (ny == 0)
  {
    return;
  }
  s->cy += ny;
}


----------------------------
void helper_input_csi_dispatch_1(int * const n_ref, u_int * const cx_ref, struct input_ctx * const ictx, struct screen * const s)
{
  int n = *n_ref;
  u_int cx = *cx_ref;
  cx = s->cx;
  if (cx > (s->grid->sx - 1))
  {
    cx = s->grid->sx - 1;
  }
  n = input_get(ictx, 0, 1, 1);
  if (n == (-1))
  {
    break;
  }
  while ((cx > 0) && ((n--) > 0))
  {
    do
    {
      cx -= 1;
    }
    while ((cx > 0) && (!(s->tabs[cx >> 3] & (1 << (cx & 0x7)))));
  }

  s->cx = cx;
  break;
  *n_ref = n;
  *cx_ref = cx;
}


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
void screen_write_insertline(struct screen_write_ctx *ctx, u_int ny, u_int bg)
{
  struct screen *s = ctx->s;
  struct grid *gd = s->grid;
  struct tty_ctx ttyctx;
  if (ny == 0)
  {
    ny = 1;
  }
  if ((s->cy < s->rupper) || (s->cy > s->rlower))
  {
    if (ny > (s->grid->sy - s->cy))
    {
      ny = s->grid->sy - s->cy;
    }
    if (ny == 0)
    {
      return;
    }
    screen_write_initctx(ctx, &ttyctx);
    ttyctx.bg = bg;
    grid_view_insert_lines(gd, s->cy, ny, bg);
    screen_write_collect_flush(ctx, 0);
    ttyctx.num = ny;
    tty_write(tty_cmd_insertline, &ttyctx);
    return;
  }
  if (ny > ((s->rlower + 1) - s->cy))
  {
    ny = (s->rlower + 1) - s->cy;
  }
  if (ny == 0)
  {
    return;
  }
  screen_write_initctx(ctx, &ttyctx);
  ttyctx.bg = bg;
  if ((s->cy < s->rupper) || (s->cy > s->rlower))
  {
    grid_view_insert_lines(gd, s->cy, ny, bg);
  }
  else
    grid_view_insert_lines_region(gd, s->rlower, s->cy, ny, bg);
  screen_write_collect_flush(ctx, 0);
  ttyctx.num = ny;
  tty_write(tty_cmd_insertline, &ttyctx);
}


----------------------------
static void input_csi_dispatch_sm_private(struct input_ctx *ictx)
{
  struct window_pane *wp = ictx->wp;
  u_int i;
  for (i = 0; i < ictx->param_list_len; i += 1)
  {
    helper_input_csi_dispatch_sm_private_1(ictx, wp, i);
  }

}


----------------------------
void screen_write_scrollup(struct screen_write_ctx *ctx, u_int lines, u_int bg)
{
  struct screen *s = ctx->s;
  struct grid *gd = s->grid;
  u_int i;
  if (lines == 0)
  {
    lines = 1;
  }
  else
    if (lines > ((s->rlower - s->rupper) + 1))
  {
    lines = (s->rlower - s->rupper) + 1;
  }
  if (bg != ctx->bg)
  {
    screen_write_collect_flush(ctx, 1);
    ctx->bg = bg;
  }
  for (i = 0; i < lines; i += 1)
  {
    grid_view_scroll_region_up(gd, s->rupper, s->rlower, bg);
    screen_write_collect_scroll(ctx);
  }

  ctx->scrolled += lines;
}


----------------------------
static void input_csi_dispatch_winops(struct input_ctx *ictx)
{
  struct window_pane *wp = ictx->wp;
  int n;
  int m;
  m = 0;
  while ((n = input_get(ictx, m, 0, -1)) != (-1))
  {
    helper_input_csi_dispatch_winops_1(&m, ictx, wp, n);
  }

}


----------------------------
void screen_set_cursor_style(struct screen *s, u_int style)
{
  if (style <= 6)
  {
    s->cstyle = style;
  }
}


----------------------------
None
----------------------------
void screen_write_clearcharacter(struct screen_write_ctx *ctx, u_int nx, u_int bg)
{
  struct screen *s = ctx->s;
  struct tty_ctx ttyctx;
  if (nx == 0)
  {
    nx = 1;
  }
  if (nx > (s->grid->sx - s->cx))
  {
    nx = s->grid->sx - s->cx;
  }
  if (nx == 0)
  {
    return;
  }
  if (s->cx > (s->grid->sx - 1))
  {
    return;
  }
  screen_write_initctx(ctx, &ttyctx);
  ttyctx.bg = bg;
  grid_view_clear(s->grid, s->cx, s->cy, nx, 1, bg);
  screen_write_collect_flush(ctx, 0);
  ttyctx.num = nx;
  tty_write(tty_cmd_clearcharacter, &ttyctx);
}


----------------------------
void screen_write_cursorright(struct screen_write_ctx *ctx, u_int nx)
{
  struct screen *s = ctx->s;
  if (nx == 0)
  {
    nx = 1;
  }
  if (nx > ((s->grid->sx - 1) - s->cx))
  {
    nx = (s->grid->sx - 1) - s->cx;
  }
  if (nx == 0)
  {
    return;
  }
  s->cx += nx;
}


----------------------------
static int input_table_compare(const void *key, const void *value)
{
  const struct input_ctx *ictx = key;
  const struct input_table_entry *entry = value;
  if (ictx->ch != entry->ch)
  {
    return ictx->ch - entry->ch;
  }
  return strcmp(ictx->interm_buf, entry->interm);
}


----------------------------
static void input_csi_dispatch_sm(struct input_ctx *ictx)
{
  u_int i;
  for (i = 0; i < ictx->param_list_len; i += 1)
  {
    switch (input_get(ictx, i, 0, -1))
    {
      case -1:
      {
        break;
      }

      case 4:
      {
        screen_write_mode_set(&ictx->ctx, 0x2);
        break;
      }

      case 34:
      {
        screen_write_mode_clear(&ictx->ctx, 0x80);
        break;
      }

      default:
      {
        log_debug("%s: unknown '%c'", __func__, ictx->ch);
        break;
      }

    }

  }

}


----------------------------
static void input_csi_dispatch_rm(struct input_ctx *ictx)
{
  u_int i;
  for (i = 0; i < ictx->param_list_len; i += 1)
  {
    switch (input_get(ictx, i, 0, -1))
    {
      case -1:
      {
        break;
      }

      case 4:
      {
        screen_write_mode_clear(&ictx->ctx, 0x2);
        break;
      }

      case 34:
      {
        screen_write_mode_set(&ictx->ctx, 0x80);
        break;
      }

      default:
      {
        log_debug("%s: unknown '%c'", __func__, ictx->ch);
        break;
      }

    }

  }

}


----------------------------
void screen_write_cursorup(struct screen_write_ctx *ctx, u_int ny)
{
  struct screen *s = ctx->s;
  if (ny == 0)
  {
    ny = 1;
  }
  if (s->cy < s->rupper)
  {
    if (ny > s->cy)
    {
      ny = s->cy;
    }
  }
  else
  {
    if (ny > (s->cy - s->rupper))
    {
      ny = s->cy - s->rupper;
    }
  }
  if (s->cx == s->grid->sx)
  {
    s->cx -= 1;
  }
  if (ny == 0)
  {
    return;
  }
  s->cy -= ny;
}


----------------------------
static const struct input_table_entry input_csi_table[] = {{'@', "", INPUT_CSI_ICH}, {'A', "", INPUT_CSI_CUU}, {'B', "", INPUT_CSI_CUD}, {'C', "", INPUT_CSI_CUF}, {'D', "", INPUT_CSI_CUB}, {'E', "", INPUT_CSI_CNL}, {'F', "", INPUT_CSI_CPL}, {'G', "", INPUT_CSI_HPA}, {'H', "", INPUT_CSI_CUP}, {'J', "", INPUT_CSI_ED}, {'K', "", INPUT_CSI_EL}, {'L', "", INPUT_CSI_IL}, {'M', "", INPUT_CSI_DL}, {'P', "", INPUT_CSI_DCH}, {'S', "", INPUT_CSI_SU}, {'X', "", INPUT_CSI_ECH}, {'Z', "", INPUT_CSI_CBT}, {'b', "", INPUT_CSI_REP}, {'c', "", INPUT_CSI_DA}, {'c', ">", INPUT_CSI_DA_TWO}, {'d', "", INPUT_CSI_VPA}, {'f', "", INPUT_CSI_CUP}, {'g', "", INPUT_CSI_TBC}, {'h', "", INPUT_CSI_SM}, {'h', "?", INPUT_CSI_SM_PRIVATE}, {'l', "", INPUT_CSI_RM}, {'l', "?", INPUT_CSI_RM_PRIVATE}, {'m', "", INPUT_CSI_SGR}, {'n', "", INPUT_CSI_DSR}, {'q', " ", INPUT_CSI_DECSCUSR}, {'r', "", INPUT_CSI_DECSTBM}, {'s', "", INPUT_CSI_SCP}, {'t', "", INPUT_CSI_WINOPS}, {'u', "", INPUT_CSI_RCP}}
----------------------------
static int input_print(struct input_ctx *ictx)
{
  int set;
  ictx->utf8started = 0;
  set = (ictx->cell.set == 0) ? (ictx->cell.g0set) : (ictx->cell.g1set);
  if (set == 1)
  {
    ictx->cell.cell.attr |= 0x80;
  }
  else
    ictx->cell.cell.attr &= ~0x80;
  utf8_set(&ictx->cell.cell.data, ictx->ch);
  screen_write_collect_add(&ictx->ctx, &ictx->cell.cell);
  ictx->last = ictx->ch;
  ictx->cell.cell.attr &= ~0x80;
  return 0;
}


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
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
void screen_write_deleteline(struct screen_write_ctx *ctx, u_int ny, u_int bg)
{
  struct screen *s = ctx->s;
  struct grid *gd = s->grid;
  struct tty_ctx ttyctx;
  if (ny == 0)
  {
    ny = 1;
  }
  if ((s->cy < s->rupper) || (s->cy > s->rlower))
  {
    if (ny > (s->grid->sy - s->cy))
    {
      ny = s->grid->sy - s->cy;
    }
    if (ny == 0)
    {
      return;
    }
    screen_write_initctx(ctx, &ttyctx);
    ttyctx.bg = bg;
    grid_view_delete_lines(gd, s->cy, ny, bg);
    screen_write_collect_flush(ctx, 0);
    ttyctx.num = ny;
    tty_write(tty_cmd_deleteline, &ttyctx);
    return;
  }
  if (ny > ((s->rlower + 1) - s->cy))
  {
    ny = (s->rlower + 1) - s->cy;
  }
  if (ny == 0)
  {
    return;
  }
  screen_write_initctx(ctx, &ttyctx);
  ttyctx.bg = bg;
  if ((s->cy < s->rupper) || (s->cy > s->rlower))
  {
    grid_view_delete_lines(gd, s->cy, ny, bg);
  }
  else
    grid_view_delete_lines_region(gd, s->rlower, s->cy, ny, bg);
  screen_write_collect_flush(ctx, 0);
  ttyctx.num = ny;
  tty_write(tty_cmd_deleteline, &ttyctx);
}


----------------------------
void screen_write_insertcharacter(struct screen_write_ctx *ctx, u_int nx, u_int bg)
{
  struct screen *s = ctx->s;
  struct tty_ctx ttyctx;
  if (nx == 0)
  {
    nx = 1;
  }
  if (nx > (s->grid->sx - s->cx))
  {
    nx = s->grid->sx - s->cx;
  }
  if (nx == 0)
  {
    return;
  }
  if (s->cx > (s->grid->sx - 1))
  {
    return;
  }
  screen_write_initctx(ctx, &ttyctx);
  ttyctx.bg = bg;
  grid_view_insert_cells(s->grid, s->cx, s->cy, nx, bg);
  screen_write_collect_flush(ctx, 0);
  ttyctx.num = nx;
  tty_write(tty_cmd_insertcharacter, &ttyctx);
}


----------------------------
void screen_write_carriagereturn(struct screen_write_ctx *ctx)
{
  struct screen *s = ctx->s;
  s->cx = 0;
}


----------------------------
struct input_table_entry
{
  int ch;
  const char *interm;
  int type;
}
----------------------------
void helper_input_csi_dispatch_4(struct input_ctx * const ictx, struct screen * const s)
{
  switch (input_get(ictx, 0, 0, 0))
  {
    case -1:
    {
      break;
    }

    case 0:
    {
      if (s->cx < s->grid->sx)
      {
        s->tabs[s->cx >> 3] &= ~(1 << (s->cx & 0x7));
      }
      break;
    }

    case 3:
    {
      do
      {
        register bitstr_t *_name = s->tabs;
        register int _start = 0;
        register int _stop = s->grid->sx - 1;
        while (_start <= _stop)
        {
          _name[_start >> 3] &= ~(1 << (_start & 0x7));
          _start += 1;
        }

      }
      while (0);
      break;
    }

    default:
    {
      log_debug("%s: unknown '%c'", __func__, ictx->ch);
      break;
    }

  }

  break;
}


----------------------------
void input_reply(struct input_ctx *ictx, const char *fmt, ...)
{
  va_list ap;
  char *reply;
  __builtin_va_start(ap);
  xvasprintf(&reply, fmt, ap);
  ;
  bufferevent_write(ictx->wp->event, reply, strlen(reply));
  free(reply);
}


----------------------------
void helper_input_csi_dispatch_2(struct input_ctx * const ictx, struct screen_write_ctx * const sctx, u_int bg)
{
  switch (input_get(ictx, 0, 0, 0))
  {
    case -1:
    {
      break;
    }

    case 0:
    {
      screen_write_clearendofline(sctx, bg);
      break;
    }

    case 1:
    {
      screen_write_clearstartofline(sctx, bg);
      break;
    }

    case 2:
    {
      screen_write_clearline(sctx, bg);
      break;
    }

    default:
    {
      log_debug("%s: unknown '%c'", __func__, ictx->ch);
      break;
    }

  }

  break;
}


----------------------------
static void input_csi_dispatch_sgr(struct input_ctx *ictx)
{
  struct grid_cell *gc = &ictx->cell.cell;
  u_int i;
  int n;
  if (ictx->param_list_len == 0)
  {
    memcpy(gc, &grid_default_cell, sizeof(*gc));
    return;
  }
  for (i = 0; i < ictx->param_list_len; i += 1)
  {
    helper_input_csi_dispatch_sgr_1(&i, &n, ictx, gc);
  }

}


----------------------------
static int input_split(struct input_ctx *ictx)
{
  const char *errstr;
  char *ptr;
  unsigned int ptr_idx = 0;
  char *out;
  unsigned int out_idx = 0;
  struct input_param *ip;
  unsigned int ip_idx = 0;
  u_int i;
  for (i = 0; i < ictx->param_list_len; i += 1)
  {
    if (ictx->param_list[i].type == INPUT_STRING)
    {
      free(ictx->param_list[i].str);
    }
  }

  ictx->param_list_len = 0;
  if (ictx->param_len == 0)
  {
    return 0;
  }
  ip_idx = &ictx->param_list[0];
  ptr_idx = ictx->param_buf;
  while ((out_idx = strsep(&(&ptr[ptr_idx]), ";")) != 0)
  {
    helper_input_split_1(&ip_idx, ictx, errstr, out, out_idx, ip);
  }

  for (i = 0; i < ictx->param_list_len; i += 1)
  {
    ip_idx = &ictx->param_list[i];
    if (ip->type == INPUT_MISSING)
    {
      log_debug("parameter %u: missing", i);
    }
    else
      if (ip->type == INPUT_STRING)
    {
      log_debug("parameter %u: string %s", i, ip->str);
    }
    else
      if (ip->type == INPUT_NUMBER)
    {
      log_debug("parameter %u: number %d", i, ip->num);
    }
  }

  return 0;
}


----------------------------
static void input_csi_dispatch_rm_private(struct input_ctx *ictx)
{
  struct window_pane *wp = ictx->wp;
  u_int i;
  for (i = 0; i < ictx->param_list_len; i += 1)
  {
    helper_input_csi_dispatch_rm_private_1(ictx, wp, i);
  }

}


----------------------------
None
----------------------------
***/


