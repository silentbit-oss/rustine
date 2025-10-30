static void window_clock_free(struct window_pane *wp)
{
  struct window_clock_mode_data *data = wp->modedata;
  evtimer_del(&data->timer);
  screen_free(&data->screen);
  free(data);
}


/*** DEPENDENCIES:
void screen_free(struct screen *s)
{
  free(s->tabs);
  free(s->title);
  free(s->ccolour);
  grid_destroy(s->grid);
  screen_free_titles(s);
}


----------------------------
struct window_clock_mode_data
{
  struct screen screen;
  time_t tim;
  struct event timer;
}
----------------------------
None
----------------------------
***/


// hint:  ['i_ref is a mutable refrence to u_int', 'j_ref is a mutable refrence to u_int', 'x_ref is a mutable refrence to u_int', 'idx_ref is a mutable refrence to u_int']
void helper_window_clock_draw_screen_1(u_int * const i_ref, u_int * const j_ref, u_int * const x_ref, u_int * const idx_ref, struct screen_write_ctx ctx, struct grid_cell gc, char * const ptr, unsigned int ptr_idx, u_int y)
{
  u_int i = *i_ref;
  u_int j = *j_ref;
  u_int x = *x_ref;
  u_int idx = *idx_ref;
  if ((ptr[ptr_idx] >= '0') && (ptr[ptr_idx] <= '9'))
  {
    idx = ptr[ptr_idx] - '0';
  }
  else
    if (ptr[ptr_idx] == ':')
  {
    idx = 10;
  }
  else
    if (ptr[ptr_idx] == 'A')
  {
    idx = 11;
  }
  else
    if (ptr[ptr_idx] == 'P')
  {
    idx = 12;
  }
  else
    if (ptr[ptr_idx] == 'M')
  {
    idx = 13;
  }
  else
  {
    x += 6;
    continue;
  }
  for (j = 0; j < 5; j += 1)
  {
    for (i = 0; i < 5; i += 1)
    {
      screen_write_cursormove(&ctx, x + i, y + j);
      if (window_clock_table[idx][j][i])
      {
        screen_write_putc(&ctx, &gc, ' ');
      }
    }

  }

  x += 6;
  *i_ref = i;
  *j_ref = j;
  *x_ref = x;
  *idx_ref = idx;
}


/*** DEPENDENCIES:
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
extern const char window_clock_table[14][5][5]
----------------------------
None
----------------------------
void screen_write_putc(struct screen_write_ctx *ctx, const struct grid_cell *gcp, u_char ch)
{
  struct grid_cell gc;
  memcpy(&gc, gcp, sizeof(gc));
  utf8_set(&gc.data, ch);
  screen_write_cell(ctx, &gc);
}


----------------------------
None
----------------------------
***/


static void window_clock_draw_screen(struct window_pane *wp)
{
  struct window_clock_mode_data *data = wp->modedata;
  struct screen_write_ctx ctx;
  int colour;
  int style;
  struct screen *s = &data->screen;
  struct grid_cell gc;
  char tim[64];
  char *ptr;
  unsigned int ptr_idx = 0;
  time_t t;
  struct tm *tm;
  unsigned int tm_idx = 0;
  u_int i;
  u_int j;
  u_int x;
  u_int y;
  u_int idx;
  colour = options_get_number(wp->window->options, "clock-mode-colour");
  style = options_get_number(wp->window->options, "clock-mode-style");
  screen_write_start(&ctx, 0, s);
  t = time(0);
  tm_idx = localtime(&t);
  if (style == 0)
  {
    strftime(tim, sizeof(tim), "%l:%M ", localtime(&t));
    if (tm->tm_hour >= 12)
    {
      strlcat(tim, "PM", sizeof(tim));
    }
    else
      strlcat(tim, "AM", sizeof(tim));
  }
  else
    strftime(tim, sizeof(tim), "%H:%M", tm);
  screen_write_clearscreen(&ctx, 8);
  if ((s->grid->sx < (6 * strlen(tim))) || (s->grid->sy < 6))
  {
    if ((s->grid->sx >= strlen(tim)) && (s->grid->sy != 0))
    {
      x = (s->grid->sx / 2) - (strlen(tim) / 2);
      y = s->grid->sy / 2;
      screen_write_cursormove(&ctx, x, y);
      memcpy(&gc, &grid_default_cell, sizeof(gc));
      gc.flags |= 0x20;
      gc.fg = colour;
      screen_write_puts(&ctx, &gc, "%s", tim);
    }
    screen_write_stop(&ctx);
    return;
  }
  x = (s->grid->sx / 2) - (3 * strlen(tim));
  y = (s->grid->sy / 2) - 3;
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  gc.flags |= 0x20;
  gc.bg = colour;
  for (ptr_idx = tim; ptr[ptr_idx] != '\0'; ptr_idx += 1)
  {
    helper_window_clock_draw_screen_1(&i, &j, &x, &idx, ctx, gc, ptr, ptr_idx, y);
  }

  screen_write_stop(&ctx);
}


/*** DEPENDENCIES:
struct window_clock_mode_data
{
  struct screen screen;
  time_t tim;
  struct event timer;
}
----------------------------
void helper_window_clock_draw_screen_1(u_int * const i_ref, u_int * const j_ref, u_int * const x_ref, u_int * const idx_ref, struct screen_write_ctx ctx, struct grid_cell gc, char * const ptr, unsigned int ptr_idx, u_int y)
{
  u_int i = *i_ref;
  u_int j = *j_ref;
  u_int x = *x_ref;
  u_int idx = *idx_ref;
  if ((ptr[ptr_idx] >= '0') && (ptr[ptr_idx] <= '9'))
  {
    idx = ptr[ptr_idx] - '0';
  }
  else
    if (ptr[ptr_idx] == ':')
  {
    idx = 10;
  }
  else
    if (ptr[ptr_idx] == 'A')
  {
    idx = 11;
  }
  else
    if (ptr[ptr_idx] == 'P')
  {
    idx = 12;
  }
  else
    if (ptr[ptr_idx] == 'M')
  {
    idx = 13;
  }
  else
  {
    x += 6;
    continue;
  }
  for (j = 0; j < 5; j += 1)
  {
    for (i = 0; i < 5; i += 1)
    {
      screen_write_cursormove(&ctx, x + i, y + j);
      if (window_clock_table[idx][j][i])
      {
        screen_write_putc(&ctx, &gc, ' ');
      }
    }

  }

  x += 6;
  *i_ref = i;
  *j_ref = j;
  *x_ref = x;
  *idx_ref = idx;
}


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
void screen_write_puts(struct screen_write_ctx *ctx, const struct grid_cell *gcp, const char *fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  screen_write_vnputs(ctx, -1, gcp, fmt, ap);
  ;
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
None
----------------------------
***/


static void window_clock_timer_callback(int fd, short events, void *arg)
{
  struct window_pane *wp = arg;
  struct window_clock_mode_data *data = wp->modedata;
  struct tm now;
  struct tm then;
  time_t t;
  struct timeval tv = {.tv_sec = 1};
  evtimer_del(&data->timer);
  evtimer_add(&data->timer, &tv);
  t = time(0);
  gmtime_r(&t, &now);
  gmtime_r(&data->tim, &then);
  if (now.tm_min == then.tm_min)
  {
    return;
  }
  data->tim = t;
  window_clock_draw_screen(wp);
  server_redraw_window(wp->window);
}


/*** DEPENDENCIES:
static void window_clock_draw_screen(struct window_pane *wp)
{
  struct window_clock_mode_data *data = wp->modedata;
  struct screen_write_ctx ctx;
  int colour;
  int style;
  struct screen *s = &data->screen;
  struct grid_cell gc;
  char tim[64];
  char *ptr;
  unsigned int ptr_idx = 0;
  time_t t;
  struct tm *tm;
  unsigned int tm_idx = 0;
  u_int i;
  u_int j;
  u_int x;
  u_int y;
  u_int idx;
  colour = options_get_number(wp->window->options, "clock-mode-colour");
  style = options_get_number(wp->window->options, "clock-mode-style");
  screen_write_start(&ctx, 0, s);
  t = time(0);
  tm_idx = localtime(&t);
  if (style == 0)
  {
    strftime(tim, sizeof(tim), "%l:%M ", localtime(&t));
    if (tm->tm_hour >= 12)
    {
      strlcat(tim, "PM", sizeof(tim));
    }
    else
      strlcat(tim, "AM", sizeof(tim));
  }
  else
    strftime(tim, sizeof(tim), "%H:%M", tm);
  screen_write_clearscreen(&ctx, 8);
  if ((s->grid->sx < (6 * strlen(tim))) || (s->grid->sy < 6))
  {
    if ((s->grid->sx >= strlen(tim)) && (s->grid->sy != 0))
    {
      x = (s->grid->sx / 2) - (strlen(tim) / 2);
      y = s->grid->sy / 2;
      screen_write_cursormove(&ctx, x, y);
      memcpy(&gc, &grid_default_cell, sizeof(gc));
      gc.flags |= 0x20;
      gc.fg = colour;
      screen_write_puts(&ctx, &gc, "%s", tim);
    }
    screen_write_stop(&ctx);
    return;
  }
  x = (s->grid->sx / 2) - (3 * strlen(tim));
  y = (s->grid->sy / 2) - 3;
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  gc.flags |= 0x20;
  gc.bg = colour;
  for (ptr_idx = tim; ptr[ptr_idx] != '\0'; ptr_idx += 1)
  {
    helper_window_clock_draw_screen_1(&i, &j, &x, &idx, ctx, gc, ptr, ptr_idx, y);
  }

  screen_write_stop(&ctx);
}


----------------------------
struct window_clock_mode_data
{
  struct screen screen;
  time_t tim;
  struct event timer;
}
----------------------------
pub time: Time
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


static void window_clock_resize(struct window_pane *wp, u_int sx, u_int sy)
{
  struct window_clock_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  screen_resize(s, sx, sy, 0);
  window_clock_draw_screen(wp);
}


/*** DEPENDENCIES:
void screen_resize(struct screen *s, u_int sx, u_int sy, int reflow)
{
  if (sx < 1)
  {
    sx = 1;
  }
  if (sy < 1)
  {
    sy = 1;
  }
  if (sx != s->grid->sx)
  {
    screen_resize_x(s, sx);
    screen_reset_tabs(s);
  }
  else
    reflow = 0;
  if (sy != s->grid->sy)
  {
    screen_resize_y(s, sy);
  }
  if (reflow)
  {
    screen_reflow(s, sx);
  }
}


----------------------------
static void window_clock_draw_screen(struct window_pane *wp)
{
  struct window_clock_mode_data *data = wp->modedata;
  struct screen_write_ctx ctx;
  int colour;
  int style;
  struct screen *s = &data->screen;
  struct grid_cell gc;
  char tim[64];
  char *ptr;
  unsigned int ptr_idx = 0;
  time_t t;
  struct tm *tm;
  unsigned int tm_idx = 0;
  u_int i;
  u_int j;
  u_int x;
  u_int y;
  u_int idx;
  colour = options_get_number(wp->window->options, "clock-mode-colour");
  style = options_get_number(wp->window->options, "clock-mode-style");
  screen_write_start(&ctx, 0, s);
  t = time(0);
  tm_idx = localtime(&t);
  if (style == 0)
  {
    strftime(tim, sizeof(tim), "%l:%M ", localtime(&t));
    if (tm->tm_hour >= 12)
    {
      strlcat(tim, "PM", sizeof(tim));
    }
    else
      strlcat(tim, "AM", sizeof(tim));
  }
  else
    strftime(tim, sizeof(tim), "%H:%M", tm);
  screen_write_clearscreen(&ctx, 8);
  if ((s->grid->sx < (6 * strlen(tim))) || (s->grid->sy < 6))
  {
    if ((s->grid->sx >= strlen(tim)) && (s->grid->sy != 0))
    {
      x = (s->grid->sx / 2) - (strlen(tim) / 2);
      y = s->grid->sy / 2;
      screen_write_cursormove(&ctx, x, y);
      memcpy(&gc, &grid_default_cell, sizeof(gc));
      gc.flags |= 0x20;
      gc.fg = colour;
      screen_write_puts(&ctx, &gc, "%s", tim);
    }
    screen_write_stop(&ctx);
    return;
  }
  x = (s->grid->sx / 2) - (3 * strlen(tim));
  y = (s->grid->sy / 2) - 3;
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  gc.flags |= 0x20;
  gc.bg = colour;
  for (ptr_idx = tim; ptr[ptr_idx] != '\0'; ptr_idx += 1)
  {
    helper_window_clock_draw_screen_1(&i, &j, &x, &idx, ctx, gc, ptr, ptr_idx, y);
  }

  screen_write_stop(&ctx);
}


----------------------------
None
----------------------------
struct window_clock_mode_data
{
  struct screen screen;
  time_t tim;
  struct event timer;
}
----------------------------
None
----------------------------
***/


static void window_clock_key(struct window_pane *wp, struct client *c, struct session *sess, key_code key, struct mouse_event *m)
{
  window_pane_reset_mode(wp);
}


/*** DEPENDENCIES:
struct mouse_event
{
  int valid;
  key_code key;
  int statusat;
  u_int x;
  u_int y;
  u_int b;
  u_int lx;
  u_int ly;
  u_int lb;
  int s;
  int w;
  int wp;
  u_int sgr_type;
  u_int sgr_b;
}
----------------------------
None
----------------------------
typedef unsigned long long key_code
----------------------------
None
----------------------------
***/


static struct screen *window_clock_init(struct window_pane *wp, struct cmd_find_state *fs, struct args *args)
{
  struct window_clock_mode_data *data;
  struct screen *s;
  unsigned int s_idx = 0;
  struct timeval tv = {.tv_sec = 1};
  wp->modedata = (data = xmalloc(sizeof(*data)));
  data->tim = time(0);
  evtimer_set(&data->timer, window_clock_timer_callback, wp);
  evtimer_add(&data->timer, &tv);
  s_idx = &data->screen;
  screen_init(s, (&wp->base)->grid->sx, (&wp->base)->grid->sy, 0);
  s->mode &= ~0x1;
  window_clock_draw_screen(wp);
  return s;
}


/*** DEPENDENCIES:
static void window_clock_draw_screen(struct window_pane *wp)
{
  struct window_clock_mode_data *data = wp->modedata;
  struct screen_write_ctx ctx;
  int colour;
  int style;
  struct screen *s = &data->screen;
  struct grid_cell gc;
  char tim[64];
  char *ptr;
  unsigned int ptr_idx = 0;
  time_t t;
  struct tm *tm;
  unsigned int tm_idx = 0;
  u_int i;
  u_int j;
  u_int x;
  u_int y;
  u_int idx;
  colour = options_get_number(wp->window->options, "clock-mode-colour");
  style = options_get_number(wp->window->options, "clock-mode-style");
  screen_write_start(&ctx, 0, s);
  t = time(0);
  tm_idx = localtime(&t);
  if (style == 0)
  {
    strftime(tim, sizeof(tim), "%l:%M ", localtime(&t));
    if (tm->tm_hour >= 12)
    {
      strlcat(tim, "PM", sizeof(tim));
    }
    else
      strlcat(tim, "AM", sizeof(tim));
  }
  else
    strftime(tim, sizeof(tim), "%H:%M", tm);
  screen_write_clearscreen(&ctx, 8);
  if ((s->grid->sx < (6 * strlen(tim))) || (s->grid->sy < 6))
  {
    if ((s->grid->sx >= strlen(tim)) && (s->grid->sy != 0))
    {
      x = (s->grid->sx / 2) - (strlen(tim) / 2);
      y = s->grid->sy / 2;
      screen_write_cursormove(&ctx, x, y);
      memcpy(&gc, &grid_default_cell, sizeof(gc));
      gc.flags |= 0x20;
      gc.fg = colour;
      screen_write_puts(&ctx, &gc, "%s", tim);
    }
    screen_write_stop(&ctx);
    return;
  }
  x = (s->grid->sx / 2) - (3 * strlen(tim));
  y = (s->grid->sy / 2) - 3;
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  gc.flags |= 0x20;
  gc.bg = colour;
  for (ptr_idx = tim; ptr[ptr_idx] != '\0'; ptr_idx += 1)
  {
    helper_window_clock_draw_screen_1(&i, &j, &x, &idx, ctx, gc, ptr, ptr_idx, y);
  }

  screen_write_stop(&ctx);
}


----------------------------
None
----------------------------
void screen_init(struct screen *s, u_int sx, u_int sy, u_int hlimit)
{
  s->grid = grid_create(sx, sy, hlimit);
  s->title = xstrdup("");
  s->titles = 0;
  s->cstyle = 0;
  s->ccolour = xstrdup("");
  s->tabs = 0;
  screen_reinit(s);
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
struct window_clock_mode_data
{
  struct screen screen;
  time_t tim;
  struct event timer;
}
----------------------------
pub time: Time
----------------------------
None
----------------------------
static void window_clock_timer_callback(int fd, short events, void *arg)
{
  struct window_pane *wp = arg;
  struct window_clock_mode_data *data = wp->modedata;
  struct tm now;
  struct tm then;
  time_t t;
  struct timeval tv = {.tv_sec = 1};
  evtimer_del(&data->timer);
  evtimer_add(&data->timer, &tv);
  t = time(0);
  gmtime_r(&t, &now);
  gmtime_r(&data->tim, &then);
  if (now.tm_min == then.tm_min)
  {
    return;
  }
  data->tim = t;
  window_clock_draw_screen(wp);
  server_redraw_window(wp->window);
}


----------------------------
None
----------------------------
***/


