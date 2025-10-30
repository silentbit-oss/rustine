static int screen_redraw_cell_border1(struct window_pane *wp, u_int px, u_int py)
{
  if ((((px >= wp->xoff) && (px < (wp->xoff + wp->sx))) && (py >= wp->yoff)) && (py < (wp->yoff + wp->sy)))
  {
    return 0;
  }
  if (((wp->yoff == 0) || (py >= (wp->yoff - 1))) && (py <= (wp->yoff + wp->sy)))
  {
    if ((wp->xoff != 0) && (px == (wp->xoff - 1)))
    {
      return 1;
    }
    if (px == (wp->xoff + wp->sx))
    {
      return 2;
    }
  }
  if (((wp->xoff == 0) || (px >= (wp->xoff - 1))) && (px <= (wp->xoff + wp->sx)))
  {
    if ((wp->yoff != 0) && (py == (wp->yoff - 1)))
    {
      return 3;
    }
    if (py == (wp->yoff + wp->sy))
    {
      return 4;
    }
  }
  return -1;
}


/*** DEPENDENCIES:
None
----------------------------
***/


void screen_redraw_pane(struct client *c, struct window_pane *wp)
{
  u_int i;
  u_int yoff;
  if (!window_pane_visible(wp))
  {
    return;
  }
  yoff = wp->yoff;
  if (status_at_line(c) == 0)
  {
    yoff += status_line_size(c->session);
  }
  log_debug("%s: redraw pane %%%u (at %u,%u)", c->name, wp->id, wp->xoff, yoff);
  for (i = 0; i < wp->sy; i += 1)
  {
    tty_draw_pane(&c->tty, wp, i, wp->xoff, yoff);
  }

  tty_reset(&c->tty);
}


/*** DEPENDENCIES:
void tty_reset(struct tty *tty)
{
  struct grid_cell *gc = &tty->cell;
  if (!grid_cells_equal(gc, &grid_default_cell))
  {
    if ((gc->attr & 0x80) && tty_acs_needed(tty))
    {
      tty_putcode(tty, TTYC_RMACS);
    }
    tty_putcode(tty, TTYC_SGR0);
    memcpy(gc, &grid_default_cell, sizeof(*gc));
  }
  memcpy(&tty->last_cell, &grid_default_cell, sizeof(tty->last_cell));
  tty->last_wp = -1;
}


----------------------------
void tty_draw_pane(struct tty *tty, const struct window_pane *wp, u_int py, u_int ox, u_int oy)
{
  tty_draw_line(tty, wp, wp->screen, py, ox, oy);
}


----------------------------
int window_pane_visible(struct window_pane *wp)
{
  struct window *w = wp->window;
  if (wp->layout_cell == 0)
  {
    return 0;
  }
  if ((wp->xoff >= w->sx) || (wp->yoff >= w->sy))
  {
    return 0;
  }
  if (((wp->xoff + wp->sx) > w->sx) || ((wp->yoff + wp->sy) > w->sy))
  {
    return 0;
  }
  return 1;
}


----------------------------
u_int status_line_size(struct session *s)
{
  if (s->statusat == (-1))
  {
    return 0;
  }
  return 1;
}


----------------------------
int status_at_line(struct client *c)
{
  struct session *s = c->session;
  if (c->flags & 0x800000)
  {
    return -1;
  }
  if (s->statusat != 1)
  {
    return s->statusat;
  }
  return c->tty.sy - status_line_size(s);
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


static void screen_redraw_draw_number(struct client *c, struct window_pane *wp, u_int lines, u_int top)
{
  struct tty *tty = &c->tty;
  struct session *s = c->session;
  struct options *oo = s->options;
  struct window *w = wp->window;
  struct grid_cell gc;
  u_int idx;
  u_int px;
  u_int py;
  u_int i;
  u_int j;
  u_int xoff;
  u_int yoff;
  int colour;
  int active_colour;
  char buf[16];
  char *ptr;
  unsigned int ptr_idx = 0;
  size_t len;
  if (window_pane_index(wp, &idx) != 0)
  {
    fatalx("index not found");
  }
  len = xsnprintf(buf, sizeof(buf), "%u", idx);
  if (wp->sx < len)
  {
    return;
  }
  colour = options_get_number(oo, "display-panes-colour");
  active_colour = options_get_number(oo, "display-panes-active-colour");
  px = wp->sx / 2;
  py = wp->sy / 2;
  xoff = wp->xoff;
  yoff = wp->yoff;
  if (top)
  {
    yoff += lines;
  }
  if ((wp->sx < (len * 6)) || (wp->sy < 5))
  {
    tty_cursor(tty, (xoff + px) - (len / 2), yoff + py);
    goto draw_text;
  }
  px -= len * 3;
  py -= 2;
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  if (w->active == wp)
  {
    gc.bg = active_colour;
  }
  else
    gc.bg = colour;
  gc.flags |= 0x20;
  tty_attributes(tty, &gc, wp);
  for (ptr_idx = buf; ptr[ptr_idx] != '\0'; ptr_idx += 1)
  {
    if ((ptr[ptr_idx] < '0') || (ptr[ptr_idx] > '9'))
    {
      continue;
    }
    idx = ptr[ptr_idx] - '0';
    for (j = 0; j < 5; j += 1)
    {
      for (i = px; i < (px + 5); i += 1)
      {
        tty_cursor(tty, xoff + i, (yoff + py) + j);
        if (window_clock_table[idx][j][i - px])
        {
          tty_putc(tty, ' ');
        }
      }

    }

    px += 6;
  }

  len = xsnprintf(buf, sizeof(buf), "%ux%u", wp->sx, wp->sy);
  if ((wp->sx < len) || (wp->sy < 6))
  {
    return;
  }
  tty_cursor(tty, (xoff + wp->sx) - len, yoff);
  draw_text:
  memcpy(&gc, &grid_default_cell, sizeof(gc));

  if (w->active == wp)
  {
    gc.fg = active_colour;
  }
  else
    gc.fg = colour;
  gc.flags |= 0x20;
  tty_attributes(tty, &gc, wp);
  tty_puts(tty, buf);
  tty_cursor(tty, 0, 0);
}


/*** DEPENDENCIES:
extern const struct grid_cell grid_default_cell
----------------------------
void tty_attributes(struct tty *tty, const struct grid_cell *gc, const struct window_pane *wp)
{
  struct grid_cell *tc = &tty->cell;
  struct grid_cell gc2;
  int changed;
  if ((((((wp != 0) && (((int) wp->id) == tty->last_wp)) && (~(wp->window->flags & 0x8000))) && (gc->attr == tty->last_cell.attr)) && (gc->fg == tty->last_cell.fg)) && (gc->bg == tty->last_cell.bg))
  {
    return;
  }
  tty->last_wp = (wp != 0) ? ((int) wp->id) : (-1);
  memcpy(&tty->last_cell, gc, sizeof(tty->last_cell));
  memcpy(&gc2, gc, sizeof(gc2));
  if (wp != 0)
  {
    tty_default_colours(&gc2, wp);
  }
  if (!tty_term_has(tty->term, TTYC_SETAB))
  {
    if (gc2.attr & 0x10)
    {
      if ((gc2.fg != 7) && (gc2.fg != 8))
      {
        gc2.attr &= ~0x10;
      }
    }
    else
    {
      if ((gc2.bg != 0) && (gc2.bg != 8))
      {
        gc2.attr |= 0x10;
      }
    }
  }
  tty_check_fg(tty, wp, &gc2);
  tty_check_bg(tty, wp, &gc2);
  if (tc->attr & (~gc2.attr))
  {
    tty_reset(tty);
  }
  tty_colours(tty, &gc2);
  changed = gc2.attr & (~tc->attr);
  tc->attr = gc2.attr;
  if (changed & 0x1)
  {
    tty_putcode(tty, TTYC_BOLD);
  }
  if (changed & 0x2)
  {
    tty_putcode(tty, TTYC_DIM);
  }
  if (changed & 0x40)
  {
    tty_set_italics(tty);
  }
  if (changed & 0x4)
  {
    tty_putcode(tty, TTYC_SMUL);
  }
  if (changed & 0x8)
  {
    tty_putcode(tty, TTYC_BLINK);
  }
  if (changed & 0x10)
  {
    if (tty_term_has(tty->term, TTYC_REV))
    {
      tty_putcode(tty, TTYC_REV);
    }
    else
      if (tty_term_has(tty->term, TTYC_SMSO))
    {
      tty_putcode(tty, TTYC_SMSO);
    }
  }
  if (changed & 0x20)
  {
    tty_putcode(tty, TTYC_INVIS);
  }
  if (changed & 0x100)
  {
    tty_putcode(tty, TTYC_SMXX);
  }
  if ((changed & 0x80) && tty_acs_needed(tty))
  {
    tty_putcode(tty, TTYC_SMACS);
  }
}


----------------------------
void tty_cursor(struct tty *tty, u_int cx, u_int cy)
{
  struct tty_term *term = tty->term;
  u_int thisx;
  u_int thisy;
  int change;
  if (cx > (tty->sx - 1))
  {
    cx = tty->sx - 1;
  }
  thisx = tty->cx;
  thisy = tty->cy;
  if ((cx == thisx) && (cy == thisy))
  {
    return;
  }
  if (thisx > (tty->sx - 1))
  {
    goto absolute;
  }
  if (((cx == 0) && (cy == 0)) && tty_term_has(term, TTYC_HOME))
  {
    tty_putcode(tty, TTYC_HOME);
    goto out;
  }
  if ((((cx == 0) && (cy == (thisy + 1))) && (thisy != tty->rlower)) && ((!(tty->term_type == TTY_VT420)) || (tty->rleft == 0)))
  {
    tty_putc(tty, '\r');
    tty_putc(tty, '\n');
    goto out;
  }
  if (cy == thisy)
  {
    helper_tty_cursor_2(&change, tty, cx, term, thisx);
  }
  else
    if (cx == thisx)
  {
    helper_tty_cursor_1(&change, tty, cy, term, thisy);
  }
  absolute:
  tty_putcode2(tty, TTYC_CUP, cy, cx);

  out:
  tty->cx = cx;

  tty->cy = cy;
}


----------------------------
int xsnprintf(char *str, size_t len, const char *fmt, ...)
{
  va_list ap;
  int i;
  __builtin_va_start(ap);
  i = xvsnprintf(str, len, fmt, ap);
  ;
  return i;
}


----------------------------
void tty_putc(struct tty *tty, u_char ch)
{
  const char *acs;
  unsigned int acs_idx = 0;
  if (tty->cell.attr & 0x80)
  {
    acs_idx = tty_acs_get(tty, ch);
    if ((&acs[acs_idx]) != 0)
    {
      tty_add(tty, acs, strlen(acs));
    }
    else
      tty_add(tty, &ch, 1);
  }
  else
    tty_add(tty, &ch, 1);
  if ((ch >= 0x20) && (ch != 0x7f))
  {
    if (tty->cx >= tty->sx)
    {
      tty->cx = 1;
      if (tty->cy != tty->rlower)
      {
        tty->cy += 1;
      }
      if (tty->term->flags & 0x2)
      {
        tty_putcode2(tty, TTYC_CUP, tty->cy, tty->cx);
      }
    }
    else
      tty->cx++;
  }
}


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
void tty_puts(struct tty *tty, const char *s)
{
  if ((*s) != '\0')
  {
    tty_add(tty, s, strlen(s));
  }
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
extern const char window_clock_table[14][5][5]
----------------------------
None
----------------------------
int window_pane_index(struct window_pane *wp, u_int *i)
{
  struct window_pane *wq;
  unsigned int wq_idx = 0;
  struct window *w = wp->window;
  *i = options_get_number(w->options, "pane-base-index");
  for (wq_idx = (&w->panes)->tqh_first; (&wq[wq_idx]) != 0; wq_idx = wq_idx->entry.tqe_next)
  {
    if (wp == (&wq[wq_idx]))
    {
      return 0;
    }
    *i += 1;
  }

  return -1;
}


----------------------------
None
----------------------------
***/


static void screen_redraw_draw_panes(struct client *c, u_int lines, u_int top)
{
  struct window *w = c->session->curw->window;
  struct tty *tty = &c->tty;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int i;
  u_int y;
  if (top)
  {
    y = lines;
  }
  else
    y = 0;
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    if (!window_pane_visible(wp))
    {
      continue;
    }
    for (i = 0; i < wp->sy; i += 1)
    {
      tty_draw_pane(tty, wp, i, wp->xoff, y + wp->yoff);
    }

    if (c->flags & 0x100)
    {
      screen_redraw_draw_number(c, wp, lines, top);
    }
  }

}


/*** DEPENDENCIES:
int window_pane_visible(struct window_pane *wp)
{
  struct window *w = wp->window;
  if (wp->layout_cell == 0)
  {
    return 0;
  }
  if ((wp->xoff >= w->sx) || (wp->yoff >= w->sy))
  {
    return 0;
  }
  if (((wp->xoff + wp->sx) > w->sx) || ((wp->yoff + wp->sy) > w->sy))
  {
    return 0;
  }
  return 1;
}


----------------------------
void tty_draw_pane(struct tty *tty, const struct window_pane *wp, u_int py, u_int ox, u_int oy)
{
  tty_draw_line(tty, wp, wp->screen, py, ox, oy);
}


----------------------------
static void screen_redraw_draw_number(struct client *c, struct window_pane *wp, u_int lines, u_int top)
{
  struct tty *tty = &c->tty;
  struct session *s = c->session;
  struct options *oo = s->options;
  struct window *w = wp->window;
  struct grid_cell gc;
  u_int idx;
  u_int px;
  u_int py;
  u_int i;
  u_int j;
  u_int xoff;
  u_int yoff;
  int colour;
  int active_colour;
  char buf[16];
  char *ptr;
  unsigned int ptr_idx = 0;
  size_t len;
  if (window_pane_index(wp, &idx) != 0)
  {
    fatalx("index not found");
  }
  len = xsnprintf(buf, sizeof(buf), "%u", idx);
  if (wp->sx < len)
  {
    return;
  }
  colour = options_get_number(oo, "display-panes-colour");
  active_colour = options_get_number(oo, "display-panes-active-colour");
  px = wp->sx / 2;
  py = wp->sy / 2;
  xoff = wp->xoff;
  yoff = wp->yoff;
  if (top)
  {
    yoff += lines;
  }
  if ((wp->sx < (len * 6)) || (wp->sy < 5))
  {
    tty_cursor(tty, (xoff + px) - (len / 2), yoff + py);
    goto draw_text;
  }
  px -= len * 3;
  py -= 2;
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  if (w->active == wp)
  {
    gc.bg = active_colour;
  }
  else
    gc.bg = colour;
  gc.flags |= 0x20;
  tty_attributes(tty, &gc, wp);
  for (ptr_idx = buf; ptr[ptr_idx] != '\0'; ptr_idx += 1)
  {
    if ((ptr[ptr_idx] < '0') || (ptr[ptr_idx] > '9'))
    {
      continue;
    }
    idx = ptr[ptr_idx] - '0';
    for (j = 0; j < 5; j += 1)
    {
      for (i = px; i < (px + 5); i += 1)
      {
        tty_cursor(tty, xoff + i, (yoff + py) + j);
        if (window_clock_table[idx][j][i - px])
        {
          tty_putc(tty, ' ');
        }
      }

    }

    px += 6;
  }

  len = xsnprintf(buf, sizeof(buf), "%ux%u", wp->sx, wp->sy);
  if ((wp->sx < len) || (wp->sy < 6))
  {
    return;
  }
  tty_cursor(tty, (xoff + wp->sx) - len, yoff);
  draw_text:
  memcpy(&gc, &grid_default_cell, sizeof(gc));

  if (w->active == wp)
  {
    gc.fg = active_colour;
  }
  else
    gc.fg = colour;
  gc.flags |= 0x20;
  tty_attributes(tty, &gc, wp);
  tty_puts(tty, buf);
  tty_cursor(tty, 0, 0);
}


----------------------------
None
----------------------------
***/


static void screen_redraw_draw_pane_status(struct client *c, int pane_status)
{
  struct window *w = c->session->curw->window;
  struct options *oo = c->session->options;
  struct tty *tty = &c->tty;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  int spos;
  u_int yoff;
  spos = options_get_number(oo, "status-position");
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    if (!window_pane_visible(wp))
    {
      continue;
    }
    if (pane_status == 1)
    {
      yoff = wp->yoff - 1;
    }
    else
      yoff = wp->yoff + wp->sy;
    if (spos == 0)
    {
      yoff += 1;
    }
    tty_draw_line(tty, 0, &wp->status_screen, 0, wp->xoff + 2, yoff);
  }

  tty_cursor(tty, 0, 0);
}


/*** DEPENDENCIES:
void tty_cursor(struct tty *tty, u_int cx, u_int cy)
{
  struct tty_term *term = tty->term;
  u_int thisx;
  u_int thisy;
  int change;
  if (cx > (tty->sx - 1))
  {
    cx = tty->sx - 1;
  }
  thisx = tty->cx;
  thisy = tty->cy;
  if ((cx == thisx) && (cy == thisy))
  {
    return;
  }
  if (thisx > (tty->sx - 1))
  {
    goto absolute;
  }
  if (((cx == 0) && (cy == 0)) && tty_term_has(term, TTYC_HOME))
  {
    tty_putcode(tty, TTYC_HOME);
    goto out;
  }
  if ((((cx == 0) && (cy == (thisy + 1))) && (thisy != tty->rlower)) && ((!(tty->term_type == TTY_VT420)) || (tty->rleft == 0)))
  {
    tty_putc(tty, '\r');
    tty_putc(tty, '\n');
    goto out;
  }
  if (cy == thisy)
  {
    helper_tty_cursor_2(&change, tty, cx, term, thisx);
  }
  else
    if (cx == thisx)
  {
    helper_tty_cursor_1(&change, tty, cy, term, thisy);
  }
  absolute:
  tty_putcode2(tty, TTYC_CUP, cy, cx);

  out:
  tty->cx = cx;

  tty->cy = cy;
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
int window_pane_visible(struct window_pane *wp)
{
  struct window *w = wp->window;
  if (wp->layout_cell == 0)
  {
    return 0;
  }
  if ((wp->xoff >= w->sx) || (wp->yoff >= w->sy))
  {
    return 0;
  }
  if (((wp->xoff + wp->sx) > w->sx) || ((wp->yoff + wp->sy) > w->sy))
  {
    return 0;
  }
  return 1;
}


----------------------------
None
----------------------------
void tty_draw_line(struct tty *tty, const struct window_pane *wp, struct screen *s, u_int py, u_int ox, u_int oy)
{
  struct grid *gd = s->grid;
  struct grid_cell gc;
  struct grid_cell last;
  const struct grid_cell *gcp;
  unsigned int gcp_idx = 0;
  u_int i;
  u_int j;
  u_int ux;
  u_int sx;
  u_int nx;
  u_int width;
  int flags;
  int cleared = 0;
  char buf[512];
  size_t len;
  size_t old_len;
  flags = tty->flags & 0x1;
  tty->flags |= 0x1;
  tty_update_mode(tty, tty->mode, s);
  tty_region_off(tty);
  tty_margin_off(tty);
  sx = s->grid->sx;
  if (sx > gd->linedata[gd->hsize + py].cellsize)
  {
    sx = gd->linedata[gd->hsize + py].cellsize;
  }
  if (sx > tty->sx)
  {
    sx = tty->sx;
  }
  ux = 0;
  if ((((((wp == 0) || (py == 0)) || ((~gd->linedata[(gd->hsize + py) - 1].flags) & 0x1)) || (ox != 0)) || (tty->cx < tty->sx)) || (s->grid->sx < tty->sx))
  {
    if (((((s->grid->sx < tty->sx) && (ox == 0)) && (sx != s->grid->sx)) && tty_term_has(tty->term, TTYC_EL1)) && (!tty_fake_bce(tty, wp, 8)))
    {
      tty_default_attributes(tty, wp, 8);
      tty_cursor(tty, s->grid->sx - 1, oy + py);
      tty_putcode(tty, TTYC_EL1);
      cleared = 1;
    }
    if (sx != 0)
    {
      tty_cursor(tty, ox, oy + py);
    }
  }
  else
    log_debug("%s: wrapped line %u", __func__, oy + py);
  memcpy(&last, &grid_default_cell, sizeof(last));
  len = 0;
  width = 0;
  for (i = 0; i < sx; i += 1)
  {
    helper_tty_draw_line_1(&gcp_idx, &j, &ux, &width, &len, tty, wp, s, py, gd, gc, last, gcp, i, buf);
  }

  if (len != 0)
  {
    if (grid_cells_equal(&last, &grid_default_cell))
    {
      old_len = len;
      while ((len > 0) && (buf[len - 1] == ' '))
      {
        len -= 1;
        width -= 1;
      }

      log_debug("%s: trimmed %zu spaces", __func__, old_len - len);
    }
    if (len != 0)
    {
      tty_attributes(tty, &last, wp);
      tty_putn(tty, buf, len, width);
      ux += width;
    }
  }
  if ((!cleared) && (ux < s->grid->sx))
  {
    nx = s->grid->sx - ux;
    tty_default_attributes(tty, wp, 8);
    tty_clear_line(tty, wp, oy + py, ox + ux, nx, 8);
  }
  tty->flags = (tty->flags & (~0x1)) | flags;
  tty_update_mode(tty, tty->mode, s);
}


----------------------------
None
----------------------------
***/


static void screen_redraw_draw_status(struct client *c, u_int lines, u_int top)
{
  struct tty *tty = &c->tty;
  u_int i;
  u_int y;
  if (top)
  {
    y = 0;
  }
  else
    y = tty->sy - lines;
  for (i = 0; i < lines; i += 1)
  {
    tty_draw_line(tty, 0, &c->status.status, i, 0, y);
  }

}


/*** DEPENDENCIES:
void tty_draw_line(struct tty *tty, const struct window_pane *wp, struct screen *s, u_int py, u_int ox, u_int oy)
{
  struct grid *gd = s->grid;
  struct grid_cell gc;
  struct grid_cell last;
  const struct grid_cell *gcp;
  unsigned int gcp_idx = 0;
  u_int i;
  u_int j;
  u_int ux;
  u_int sx;
  u_int nx;
  u_int width;
  int flags;
  int cleared = 0;
  char buf[512];
  size_t len;
  size_t old_len;
  flags = tty->flags & 0x1;
  tty->flags |= 0x1;
  tty_update_mode(tty, tty->mode, s);
  tty_region_off(tty);
  tty_margin_off(tty);
  sx = s->grid->sx;
  if (sx > gd->linedata[gd->hsize + py].cellsize)
  {
    sx = gd->linedata[gd->hsize + py].cellsize;
  }
  if (sx > tty->sx)
  {
    sx = tty->sx;
  }
  ux = 0;
  if ((((((wp == 0) || (py == 0)) || ((~gd->linedata[(gd->hsize + py) - 1].flags) & 0x1)) || (ox != 0)) || (tty->cx < tty->sx)) || (s->grid->sx < tty->sx))
  {
    if (((((s->grid->sx < tty->sx) && (ox == 0)) && (sx != s->grid->sx)) && tty_term_has(tty->term, TTYC_EL1)) && (!tty_fake_bce(tty, wp, 8)))
    {
      tty_default_attributes(tty, wp, 8);
      tty_cursor(tty, s->grid->sx - 1, oy + py);
      tty_putcode(tty, TTYC_EL1);
      cleared = 1;
    }
    if (sx != 0)
    {
      tty_cursor(tty, ox, oy + py);
    }
  }
  else
    log_debug("%s: wrapped line %u", __func__, oy + py);
  memcpy(&last, &grid_default_cell, sizeof(last));
  len = 0;
  width = 0;
  for (i = 0; i < sx; i += 1)
  {
    helper_tty_draw_line_1(&gcp_idx, &j, &ux, &width, &len, tty, wp, s, py, gd, gc, last, gcp, i, buf);
  }

  if (len != 0)
  {
    if (grid_cells_equal(&last, &grid_default_cell))
    {
      old_len = len;
      while ((len > 0) && (buf[len - 1] == ' '))
      {
        len -= 1;
        width -= 1;
      }

      log_debug("%s: trimmed %zu spaces", __func__, old_len - len);
    }
    if (len != 0)
    {
      tty_attributes(tty, &last, wp);
      tty_putn(tty, buf, len, width);
      ux += width;
    }
  }
  if ((!cleared) && (ux < s->grid->sx))
  {
    nx = s->grid->sx - ux;
    tty_default_attributes(tty, wp, 8);
    tty_clear_line(tty, wp, oy + py, ox + ux, nx, 8);
  }
  tty->flags = (tty->flags & (~0x1)) | flags;
  tty_update_mode(tty, tty->mode, s);
}


----------------------------
None
----------------------------
***/


static int screen_redraw_cell_border(struct client *c, u_int px, u_int py)
{
  struct window *w = c->session->curw->window;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  int retval;
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    if (!window_pane_visible(wp))
    {
      continue;
    }
    if ((retval = screen_redraw_cell_border1(wp, px, py)) != (-1))
    {
      return !(!retval);
    }
  }

  return 0;
}


/*** DEPENDENCIES:
static int screen_redraw_cell_border1(struct window_pane *wp, u_int px, u_int py)
{
  if ((((px >= wp->xoff) && (px < (wp->xoff + wp->sx))) && (py >= wp->yoff)) && (py < (wp->yoff + wp->sy)))
  {
    return 0;
  }
  if (((wp->yoff == 0) || (py >= (wp->yoff - 1))) && (py <= (wp->yoff + wp->sy)))
  {
    if ((wp->xoff != 0) && (px == (wp->xoff - 1)))
    {
      return 1;
    }
    if (px == (wp->xoff + wp->sx))
    {
      return 2;
    }
  }
  if (((wp->xoff == 0) || (px >= (wp->xoff - 1))) && (px <= (wp->xoff + wp->sx)))
  {
    if ((wp->yoff != 0) && (py == (wp->yoff - 1)))
    {
      return 3;
    }
    if (py == (wp->yoff + wp->sy))
    {
      return 4;
    }
  }
  return -1;
}


----------------------------
int window_pane_visible(struct window_pane *wp)
{
  struct window *w = wp->window;
  if (wp->layout_cell == 0)
  {
    return 0;
  }
  if ((wp->xoff >= w->sx) || (wp->yoff >= w->sy))
  {
    return 0;
  }
  if (((wp->xoff + wp->sx) > w->sx) || ((wp->yoff + wp->sy) > w->sy))
  {
    return 0;
  }
  return 1;
}


----------------------------
None
----------------------------
***/


// hint:  ['borders_ref is a mutable refrence to int']
int helper_screen_redraw_check_cell_1(int * const borders_ref, struct client * const c, u_int px, u_int py, int pane_status, struct window_pane ** const wpp, struct window * const w, struct window_pane * const wp, unsigned int wp_idx)
{
  int borders = *borders_ref;
  if (!window_pane_visible(wp))
  {
    continue;
  }
  *wpp = &wp[wp_idx];
  if (((((wp->xoff != 0) && (px < (wp->xoff - 1))) || (px > (wp->xoff + wp->sx))) || ((wp->yoff != 0) && (py < (wp->yoff - 1)))) || (py > (wp->yoff + wp->sy)))
  {
    continue;
  }
  if (!screen_redraw_cell_border(c, px, py))
  {
    return 0;
  }
  borders = 0;
  if ((px == 0) || screen_redraw_cell_border(c, px - 1, py))
  {
    borders |= 8;
  }
  if ((px <= w->sx) && screen_redraw_cell_border(c, px + 1, py))
  {
    borders |= 4;
  }
  if (pane_status == 1)
  {
    if ((py != 0) && screen_redraw_cell_border(c, px, py - 1))
    {
      borders |= 2;
    }
  }
  else
  {
    if ((py == 0) || screen_redraw_cell_border(c, px, py - 1))
    {
      borders |= 2;
    }
  }
  if ((py <= w->sy) && screen_redraw_cell_border(c, px, py + 1))
  {
    borders |= 1;
  }
  switch (borders)
  {
    case 15:
    {
      return 11;
    }

    case 14:
    {
      return 8;
    }

    case 13:
    {
      return 7;
    }

    case 12:
    {
      return 2;
    }

    case 11:
    {
      return 10;
    }

    case 10:
    {
      return 6;
    }

    case 9:
    {
      return 4;
    }

    case 7:
    {
      return 9;
    }

    case 6:
    {
      return 5;
    }

    case 5:
    {
      return 3;
    }

    case 3:
    {
      return 1;
    }

  }

  *borders_ref = borders;
}


/*** DEPENDENCIES:
int window_pane_visible(struct window_pane *wp)
{
  struct window *w = wp->window;
  if (wp->layout_cell == 0)
  {
    return 0;
  }
  if ((wp->xoff >= w->sx) || (wp->yoff >= w->sy))
  {
    return 0;
  }
  if (((wp->xoff + wp->sx) > w->sx) || ((wp->yoff + wp->sy) > w->sy))
  {
    return 0;
  }
  return 1;
}


----------------------------
static int screen_redraw_cell_border(struct client *c, u_int px, u_int py)
{
  struct window *w = c->session->curw->window;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  int retval;
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    if (!window_pane_visible(wp))
    {
      continue;
    }
    if ((retval = screen_redraw_cell_border1(wp, px, py)) != (-1))
    {
      return !(!retval);
    }
  }

  return 0;
}


----------------------------
None
----------------------------
***/


static int screen_redraw_check_cell(struct client *c, u_int px, u_int py, int pane_status, struct window_pane **wpp)
{
  struct window *w = c->session->curw->window;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  int borders;
  u_int right;
  u_int line;
  *wpp = 0;
  if ((px > w->sx) || (py > w->sy))
  {
    return 12;
  }
  if (pane_status != 0)
  {
    for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
    {
      if (!window_pane_visible(wp))
      {
        continue;
      }
      if (pane_status == 1)
      {
        line = wp->yoff - 1;
      }
      else
        line = wp->yoff + wp->sy;
      right = ((wp->xoff + 2) + wp->status_size) - 1;
      if (((py == line) && (px >= (wp->xoff + 2))) && (px <= right))
      {
        return 0;
      }
    }

  }
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    helper_screen_redraw_check_cell_1(&borders, c, px, py, pane_status, wpp, w, wp, wp_idx);
  }

  return 12;
}


/*** DEPENDENCIES:
int window_pane_visible(struct window_pane *wp)
{
  struct window *w = wp->window;
  if (wp->layout_cell == 0)
  {
    return 0;
  }
  if ((wp->xoff >= w->sx) || (wp->yoff >= w->sy))
  {
    return 0;
  }
  if (((wp->xoff + wp->sx) > w->sx) || ((wp->yoff + wp->sy) > w->sy))
  {
    return 0;
  }
  return 1;
}


----------------------------
int helper_screen_redraw_check_cell_1(int * const borders_ref, struct client * const c, u_int px, u_int py, int pane_status, struct window_pane ** const wpp, struct window * const w, struct window_pane * const wp, unsigned int wp_idx)
{
  int borders = *borders_ref;
  if (!window_pane_visible(wp))
  {
    continue;
  }
  *wpp = &wp[wp_idx];
  if (((((wp->xoff != 0) && (px < (wp->xoff - 1))) || (px > (wp->xoff + wp->sx))) || ((wp->yoff != 0) && (py < (wp->yoff - 1)))) || (py > (wp->yoff + wp->sy)))
  {
    continue;
  }
  if (!screen_redraw_cell_border(c, px, py))
  {
    return 0;
  }
  borders = 0;
  if ((px == 0) || screen_redraw_cell_border(c, px - 1, py))
  {
    borders |= 8;
  }
  if ((px <= w->sx) && screen_redraw_cell_border(c, px + 1, py))
  {
    borders |= 4;
  }
  if (pane_status == 1)
  {
    if ((py != 0) && screen_redraw_cell_border(c, px, py - 1))
    {
      borders |= 2;
    }
  }
  else
  {
    if ((py == 0) || screen_redraw_cell_border(c, px, py - 1))
    {
      borders |= 2;
    }
  }
  if ((py <= w->sy) && screen_redraw_cell_border(c, px, py + 1))
  {
    borders |= 1;
  }
  switch (borders)
  {
    case 15:
    {
      return 11;
    }

    case 14:
    {
      return 8;
    }

    case 13:
    {
      return 7;
    }

    case 12:
    {
      return 2;
    }

    case 11:
    {
      return 10;
    }

    case 10:
    {
      return 6;
    }

    case 9:
    {
      return 4;
    }

    case 7:
    {
      return 9;
    }

    case 6:
    {
      return 5;
    }

    case 5:
    {
      return 3;
    }

    case 3:
    {
      return 1;
    }

  }

  *borders_ref = borders;
}


----------------------------
None
----------------------------
***/


static int screen_redraw_check_is(u_int px, u_int py, int type, int pane_status, struct window *w, struct window_pane *wantwp, struct window_pane *wp)
{
  int border;
  border = screen_redraw_cell_border1(wantwp, px, py);
  if ((border == 0) || (border == (-1)))
  {
    return 0;
  }
  if ((pane_status == 1) && (border == 4))
  {
    return 0;
  }
  if ((pane_status == 2) && (border == 3))
  {
    return 0;
  }
  if (window_count_panes(w) != 2)
  {
    return 1;
  }
  if ((wp == 0) || ((type == 12) || (type == 0)))
  {
    return 1;
  }
  if (pane_status != 0)
  {
    return 1;
  }
  if ((wp->xoff == 0) && (wp->sx == w->sx))
  {
    if (wp->yoff == 0)
    {
      if (wp == wantwp)
      {
        return px <= (wp->sx / 2);
      }
      return px > (wp->sx / 2);
    }
    return 0;
  }
  if ((wp->yoff == 0) && (wp->sy == w->sy))
  {
    if (wp->xoff == 0)
    {
      if (wp == wantwp)
      {
        return py <= (wp->sy / 2);
      }
      return py > (wp->sy / 2);
    }
    return 0;
  }
  return 1;
}


/*** DEPENDENCIES:
static int screen_redraw_cell_border1(struct window_pane *wp, u_int px, u_int py)
{
  if ((((px >= wp->xoff) && (px < (wp->xoff + wp->sx))) && (py >= wp->yoff)) && (py < (wp->yoff + wp->sy)))
  {
    return 0;
  }
  if (((wp->yoff == 0) || (py >= (wp->yoff - 1))) && (py <= (wp->yoff + wp->sy)))
  {
    if ((wp->xoff != 0) && (px == (wp->xoff - 1)))
    {
      return 1;
    }
    if (px == (wp->xoff + wp->sx))
    {
      return 2;
    }
  }
  if (((wp->xoff == 0) || (px >= (wp->xoff - 1))) && (px <= (wp->xoff + wp->sx)))
  {
    if ((wp->yoff != 0) && (py == (wp->yoff - 1)))
    {
      return 3;
    }
    if (py == (wp->yoff + wp->sy))
    {
      return 4;
    }
  }
  return -1;
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
None
----------------------------
***/


// hint:  ['i_ref is a mutable refrence to u_int', 'type_ref is a mutable refrence to u_int', 'active_ref is a mutable refrence to int']
void helper_screen_redraw_draw_borders_2(u_int * const i_ref, u_int * const type_ref, int * const active_ref, struct client * const c, int pane_status, u_int lines, u_int top, struct session * const s, struct window * const w, struct tty * const tty, struct window_pane * const wp, struct grid_cell m_active_gc, struct grid_cell active_gc, struct grid_cell m_other_gc, struct grid_cell other_gc, u_int j, u_int msgx, u_int msgy, int small)
{
  u_int i = *i_ref;
  u_int type = *type_ref;
  int active = *active_ref;
  for (i = 0; i < tty->sx; i += 1)
  {
    type = screen_redraw_check_cell(c, i, j, pane_status, &wp);
    if (type == 0)
    {
      continue;
    }
    if ((((type == 12) && small) && (i > msgx)) && (j == msgy))
    {
      continue;
    }
    active = screen_redraw_check_is(i, j, type, pane_status, w, w->active, wp);
    if (server_is_marked(s, s->curw, marked_pane.wp) && screen_redraw_check_is(i, j, type, pane_status, w, marked_pane.wp, wp))
    {
      if (active)
      {
        tty_attributes(tty, &m_active_gc, 0);
      }
      else
        tty_attributes(tty, &m_other_gc, 0);
    }
    else
      if (active)
    {
      tty_attributes(tty, &active_gc, 0);
    }
    else
      tty_attributes(tty, &other_gc, 0);
    if (top)
    {
      tty_cursor(tty, i, lines + j);
    }
    else
      tty_cursor(tty, i, j);
    tty_putc(tty, " xqlkmjwvtun~"[type]);
  }

  *i_ref = i;
  *type_ref = type;
  *active_ref = active;
}


/*** DEPENDENCIES:
extern struct cmd_find_state marked_pane
----------------------------
void tty_attributes(struct tty *tty, const struct grid_cell *gc, const struct window_pane *wp)
{
  struct grid_cell *tc = &tty->cell;
  struct grid_cell gc2;
  int changed;
  if ((((((wp != 0) && (((int) wp->id) == tty->last_wp)) && (~(wp->window->flags & 0x8000))) && (gc->attr == tty->last_cell.attr)) && (gc->fg == tty->last_cell.fg)) && (gc->bg == tty->last_cell.bg))
  {
    return;
  }
  tty->last_wp = (wp != 0) ? ((int) wp->id) : (-1);
  memcpy(&tty->last_cell, gc, sizeof(tty->last_cell));
  memcpy(&gc2, gc, sizeof(gc2));
  if (wp != 0)
  {
    tty_default_colours(&gc2, wp);
  }
  if (!tty_term_has(tty->term, TTYC_SETAB))
  {
    if (gc2.attr & 0x10)
    {
      if ((gc2.fg != 7) && (gc2.fg != 8))
      {
        gc2.attr &= ~0x10;
      }
    }
    else
    {
      if ((gc2.bg != 0) && (gc2.bg != 8))
      {
        gc2.attr |= 0x10;
      }
    }
  }
  tty_check_fg(tty, wp, &gc2);
  tty_check_bg(tty, wp, &gc2);
  if (tc->attr & (~gc2.attr))
  {
    tty_reset(tty);
  }
  tty_colours(tty, &gc2);
  changed = gc2.attr & (~tc->attr);
  tc->attr = gc2.attr;
  if (changed & 0x1)
  {
    tty_putcode(tty, TTYC_BOLD);
  }
  if (changed & 0x2)
  {
    tty_putcode(tty, TTYC_DIM);
  }
  if (changed & 0x40)
  {
    tty_set_italics(tty);
  }
  if (changed & 0x4)
  {
    tty_putcode(tty, TTYC_SMUL);
  }
  if (changed & 0x8)
  {
    tty_putcode(tty, TTYC_BLINK);
  }
  if (changed & 0x10)
  {
    if (tty_term_has(tty->term, TTYC_REV))
    {
      tty_putcode(tty, TTYC_REV);
    }
    else
      if (tty_term_has(tty->term, TTYC_SMSO))
    {
      tty_putcode(tty, TTYC_SMSO);
    }
  }
  if (changed & 0x20)
  {
    tty_putcode(tty, TTYC_INVIS);
  }
  if (changed & 0x100)
  {
    tty_putcode(tty, TTYC_SMXX);
  }
  if ((changed & 0x80) && tty_acs_needed(tty))
  {
    tty_putcode(tty, TTYC_SMACS);
  }
}


----------------------------
int server_is_marked(struct session *s, struct winlink *wl, struct window_pane *wp)
{
  if (((s == 0) || (wl == 0)) || (wp == 0))
  {
    return 0;
  }
  if ((marked_pane.s != s) || (marked_pane.wl != wl))
  {
    return 0;
  }
  if (marked_pane.wp != wp)
  {
    return 0;
  }
  return server_check_marked();
}


----------------------------
void tty_cursor(struct tty *tty, u_int cx, u_int cy)
{
  struct tty_term *term = tty->term;
  u_int thisx;
  u_int thisy;
  int change;
  if (cx > (tty->sx - 1))
  {
    cx = tty->sx - 1;
  }
  thisx = tty->cx;
  thisy = tty->cy;
  if ((cx == thisx) && (cy == thisy))
  {
    return;
  }
  if (thisx > (tty->sx - 1))
  {
    goto absolute;
  }
  if (((cx == 0) && (cy == 0)) && tty_term_has(term, TTYC_HOME))
  {
    tty_putcode(tty, TTYC_HOME);
    goto out;
  }
  if ((((cx == 0) && (cy == (thisy + 1))) && (thisy != tty->rlower)) && ((!(tty->term_type == TTY_VT420)) || (tty->rleft == 0)))
  {
    tty_putc(tty, '\r');
    tty_putc(tty, '\n');
    goto out;
  }
  if (cy == thisy)
  {
    helper_tty_cursor_2(&change, tty, cx, term, thisx);
  }
  else
    if (cx == thisx)
  {
    helper_tty_cursor_1(&change, tty, cy, term, thisy);
  }
  absolute:
  tty_putcode2(tty, TTYC_CUP, cy, cx);

  out:
  tty->cx = cx;

  tty->cy = cy;
}


----------------------------
void tty_putc(struct tty *tty, u_char ch)
{
  const char *acs;
  unsigned int acs_idx = 0;
  if (tty->cell.attr & 0x80)
  {
    acs_idx = tty_acs_get(tty, ch);
    if ((&acs[acs_idx]) != 0)
    {
      tty_add(tty, acs, strlen(acs));
    }
    else
      tty_add(tty, &ch, 1);
  }
  else
    tty_add(tty, &ch, 1);
  if ((ch >= 0x20) && (ch != 0x7f))
  {
    if (tty->cx >= tty->sx)
    {
      tty->cx = 1;
      if (tty->cy != tty->rlower)
      {
        tty->cy += 1;
      }
      if (tty->term->flags & 0x2)
      {
        tty_putcode2(tty, TTYC_CUP, tty->cy, tty->cx);
      }
    }
    else
      tty->cx++;
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
static int screen_redraw_check_cell(struct client *c, u_int px, u_int py, int pane_status, struct window_pane **wpp)
{
  struct window *w = c->session->curw->window;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  int borders;
  u_int right;
  u_int line;
  *wpp = 0;
  if ((px > w->sx) || (py > w->sy))
  {
    return 12;
  }
  if (pane_status != 0)
  {
    for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
    {
      if (!window_pane_visible(wp))
      {
        continue;
      }
      if (pane_status == 1)
      {
        line = wp->yoff - 1;
      }
      else
        line = wp->yoff + wp->sy;
      right = ((wp->xoff + 2) + wp->status_size) - 1;
      if (((py == line) && (px >= (wp->xoff + 2))) && (px <= right))
      {
        return 0;
      }
    }

  }
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    helper_screen_redraw_check_cell_1(&borders, c, px, py, pane_status, wpp, w, wp, wp_idx);
  }

  return 12;
}


----------------------------
None
----------------------------
static int screen_redraw_check_is(u_int px, u_int py, int type, int pane_status, struct window *w, struct window_pane *wantwp, struct window_pane *wp)
{
  int border;
  border = screen_redraw_cell_border1(wantwp, px, py);
  if ((border == 0) || (border == (-1)))
  {
    return 0;
  }
  if ((pane_status == 1) && (border == 4))
  {
    return 0;
  }
  if ((pane_status == 2) && (border == 3))
  {
    return 0;
  }
  if (window_count_panes(w) != 2)
  {
    return 1;
  }
  if ((wp == 0) || ((type == 12) || (type == 0)))
  {
    return 1;
  }
  if (pane_status != 0)
  {
    return 1;
  }
  if ((wp->xoff == 0) && (wp->sx == w->sx))
  {
    if (wp->yoff == 0)
    {
      if (wp == wantwp)
      {
        return px <= (wp->sx / 2);
      }
      return px > (wp->sx / 2);
    }
    return 0;
  }
  if ((wp->yoff == 0) && (wp->sy == w->sy))
  {
    if (wp->xoff == 0)
    {
      if (wp == wantwp)
      {
        return py <= (wp->sy / 2);
      }
      return py > (wp->sy / 2);
    }
    return 0;
  }
  return 1;
}


----------------------------
None
----------------------------
***/


// hint:  ['msgx_ref is a mutable refrence to u_int', 'msgy_ref is a mutable refrence to u_int', 'small_ref is a mutable refrence to int', 'flags_ref is a mutable refrence to int', 'tmp_idx_ref is a mutable refrence to unsigned int', 'msglen_ref is a mutable refrence to size_t']
void helper_screen_redraw_draw_borders_1(u_int * const msgx_ref, u_int * const msgy_ref, int * const small_ref, int * const flags_ref, unsigned int * const tmp_idx_ref, size_t * const msglen_ref, struct client * const c, u_int lines, u_int top, struct window * const w, struct tty * const tty, char msg[256], const char * const tmp)
{
  u_int msgx = *msgx_ref;
  u_int msgy = *msgy_ref;
  int small = *small_ref;
  int flags = *flags_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  size_t msglen = *msglen_ref;
  flags = w->flags & (0x2000 | 0x4000);
  if (flags == (0x2000 | 0x4000))
  {
    tmp_idx = "force-width, force-height";
  }
  else
    if (flags == 0x2000)
  {
    tmp_idx = "force-width";
  }
  else
    if (flags == 0x4000)
  {
    tmp_idx = "force-height";
  }
  else
    if (c->flags & 0x800000)
  {
    tmp_idx = "status line";
  }
  else
    tmp_idx = "a smaller client";
  xsnprintf(msg, sizeof(msg), "(size %ux%u from %s)", w->sx, w->sy, tmp);
  msglen = strlen(msg);
  if (((((tty->sy - 1) - lines) + top) > w->sy) && (tty->sx >= msglen))
  {
    msgx = tty->sx - msglen;
    msgy = ((tty->sy - 1) - lines) + top;
  }
  else
    if ((tty->sx - w->sx) > msglen)
  {
    msgx = tty->sx - msglen;
    msgy = ((tty->sy - 1) - lines) + top;
  }
  else
    small = 0;
  *msgx_ref = msgx;
  *msgy_ref = msgy;
  *small_ref = small;
  *flags_ref = flags;
  *tmp_idx_ref = tmp_idx;
  *msglen_ref = msglen;
}


/*** DEPENDENCIES:
int xsnprintf(char *str, size_t len, const char *fmt, ...)
{
  va_list ap;
  int i;
  __builtin_va_start(ap);
  i = xvsnprintf(str, len, fmt, ap);
  ;
  return i;
}


----------------------------
None
----------------------------
***/


static void screen_redraw_draw_borders(struct client *c, int pane_status, u_int lines, u_int top)
{
  struct session *s = c->session;
  struct window *w = s->curw->window;
  struct options *oo = w->options;
  struct tty *tty = &c->tty;
  struct window_pane *wp;
  struct grid_cell m_active_gc;
  struct grid_cell active_gc;
  struct grid_cell m_other_gc;
  struct grid_cell other_gc;
  struct grid_cell msg_gc;
  u_int i;
  u_int j;
  u_int type;
  u_int msgx = 0;
  u_int msgy = 0;
  int active;
  int small;
  int flags;
  char msg[256];
  const char *tmp;
  unsigned int tmp_idx = 0;
  size_t msglen = 0;
  small = (((tty->sy - lines) + top) > w->sy) || (tty->sx > w->sx);
  if (small)
  {
    helper_screen_redraw_draw_borders_1(&msgx, &msgy, &small, &flags, &tmp_idx, &msglen, c, lines, top, w, tty, msg, tmp);
  }
  style_apply(&other_gc, oo, "pane-border-style");
  style_apply(&active_gc, oo, "pane-active-border-style");
  active_gc.attr = (other_gc.attr = 0x80);
  memcpy(&m_other_gc, &other_gc, sizeof(m_other_gc));
  m_other_gc.attr ^= 0x10;
  memcpy(&m_active_gc, &active_gc, sizeof(m_active_gc));
  m_active_gc.attr ^= 0x10;
  for (j = 0; j < (tty->sy - lines); j += 1)
  {
    helper_screen_redraw_draw_borders_2(&i, &type, &active, c, pane_status, lines, top, s, w, tty, wp, m_active_gc, active_gc, m_other_gc, other_gc, j, msgx, msgy, small);
  }

  if (small)
  {
    memcpy(&msg_gc, &grid_default_cell, sizeof(msg_gc));
    tty_attributes(tty, &msg_gc, 0);
    tty_cursor(tty, msgx, msgy);
    tty_puts(tty, msg);
  }
}


/*** DEPENDENCIES:
void helper_screen_redraw_draw_borders_2(u_int * const i_ref, u_int * const type_ref, int * const active_ref, struct client * const c, int pane_status, u_int lines, u_int top, struct session * const s, struct window * const w, struct tty * const tty, struct window_pane * const wp, struct grid_cell m_active_gc, struct grid_cell active_gc, struct grid_cell m_other_gc, struct grid_cell other_gc, u_int j, u_int msgx, u_int msgy, int small)
{
  u_int i = *i_ref;
  u_int type = *type_ref;
  int active = *active_ref;
  for (i = 0; i < tty->sx; i += 1)
  {
    type = screen_redraw_check_cell(c, i, j, pane_status, &wp);
    if (type == 0)
    {
      continue;
    }
    if ((((type == 12) && small) && (i > msgx)) && (j == msgy))
    {
      continue;
    }
    active = screen_redraw_check_is(i, j, type, pane_status, w, w->active, wp);
    if (server_is_marked(s, s->curw, marked_pane.wp) && screen_redraw_check_is(i, j, type, pane_status, w, marked_pane.wp, wp))
    {
      if (active)
      {
        tty_attributes(tty, &m_active_gc, 0);
      }
      else
        tty_attributes(tty, &m_other_gc, 0);
    }
    else
      if (active)
    {
      tty_attributes(tty, &active_gc, 0);
    }
    else
      tty_attributes(tty, &other_gc, 0);
    if (top)
    {
      tty_cursor(tty, i, lines + j);
    }
    else
      tty_cursor(tty, i, j);
    tty_putc(tty, " xqlkmjwvtun~"[type]);
  }

  *i_ref = i;
  *type_ref = type;
  *active_ref = active;
}


----------------------------
extern const struct grid_cell grid_default_cell
----------------------------
void tty_attributes(struct tty *tty, const struct grid_cell *gc, const struct window_pane *wp)
{
  struct grid_cell *tc = &tty->cell;
  struct grid_cell gc2;
  int changed;
  if ((((((wp != 0) && (((int) wp->id) == tty->last_wp)) && (~(wp->window->flags & 0x8000))) && (gc->attr == tty->last_cell.attr)) && (gc->fg == tty->last_cell.fg)) && (gc->bg == tty->last_cell.bg))
  {
    return;
  }
  tty->last_wp = (wp != 0) ? ((int) wp->id) : (-1);
  memcpy(&tty->last_cell, gc, sizeof(tty->last_cell));
  memcpy(&gc2, gc, sizeof(gc2));
  if (wp != 0)
  {
    tty_default_colours(&gc2, wp);
  }
  if (!tty_term_has(tty->term, TTYC_SETAB))
  {
    if (gc2.attr & 0x10)
    {
      if ((gc2.fg != 7) && (gc2.fg != 8))
      {
        gc2.attr &= ~0x10;
      }
    }
    else
    {
      if ((gc2.bg != 0) && (gc2.bg != 8))
      {
        gc2.attr |= 0x10;
      }
    }
  }
  tty_check_fg(tty, wp, &gc2);
  tty_check_bg(tty, wp, &gc2);
  if (tc->attr & (~gc2.attr))
  {
    tty_reset(tty);
  }
  tty_colours(tty, &gc2);
  changed = gc2.attr & (~tc->attr);
  tc->attr = gc2.attr;
  if (changed & 0x1)
  {
    tty_putcode(tty, TTYC_BOLD);
  }
  if (changed & 0x2)
  {
    tty_putcode(tty, TTYC_DIM);
  }
  if (changed & 0x40)
  {
    tty_set_italics(tty);
  }
  if (changed & 0x4)
  {
    tty_putcode(tty, TTYC_SMUL);
  }
  if (changed & 0x8)
  {
    tty_putcode(tty, TTYC_BLINK);
  }
  if (changed & 0x10)
  {
    if (tty_term_has(tty->term, TTYC_REV))
    {
      tty_putcode(tty, TTYC_REV);
    }
    else
      if (tty_term_has(tty->term, TTYC_SMSO))
    {
      tty_putcode(tty, TTYC_SMSO);
    }
  }
  if (changed & 0x20)
  {
    tty_putcode(tty, TTYC_INVIS);
  }
  if (changed & 0x100)
  {
    tty_putcode(tty, TTYC_SMXX);
  }
  if ((changed & 0x80) && tty_acs_needed(tty))
  {
    tty_putcode(tty, TTYC_SMACS);
  }
}


----------------------------
void tty_cursor(struct tty *tty, u_int cx, u_int cy)
{
  struct tty_term *term = tty->term;
  u_int thisx;
  u_int thisy;
  int change;
  if (cx > (tty->sx - 1))
  {
    cx = tty->sx - 1;
  }
  thisx = tty->cx;
  thisy = tty->cy;
  if ((cx == thisx) && (cy == thisy))
  {
    return;
  }
  if (thisx > (tty->sx - 1))
  {
    goto absolute;
  }
  if (((cx == 0) && (cy == 0)) && tty_term_has(term, TTYC_HOME))
  {
    tty_putcode(tty, TTYC_HOME);
    goto out;
  }
  if ((((cx == 0) && (cy == (thisy + 1))) && (thisy != tty->rlower)) && ((!(tty->term_type == TTY_VT420)) || (tty->rleft == 0)))
  {
    tty_putc(tty, '\r');
    tty_putc(tty, '\n');
    goto out;
  }
  if (cy == thisy)
  {
    helper_tty_cursor_2(&change, tty, cx, term, thisx);
  }
  else
    if (cx == thisx)
  {
    helper_tty_cursor_1(&change, tty, cy, term, thisy);
  }
  absolute:
  tty_putcode2(tty, TTYC_CUP, cy, cx);

  out:
  tty->cx = cx;

  tty->cy = cy;
}


----------------------------
void tty_puts(struct tty *tty, const char *s)
{
  if ((*s) != '\0')
  {
    tty_add(tty, s, strlen(s));
  }
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
void helper_screen_redraw_draw_borders_1(u_int * const msgx_ref, u_int * const msgy_ref, int * const small_ref, int * const flags_ref, unsigned int * const tmp_idx_ref, size_t * const msglen_ref, struct client * const c, u_int lines, u_int top, struct window * const w, struct tty * const tty, char msg[256], const char * const tmp)
{
  u_int msgx = *msgx_ref;
  u_int msgy = *msgy_ref;
  int small = *small_ref;
  int flags = *flags_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  size_t msglen = *msglen_ref;
  flags = w->flags & (0x2000 | 0x4000);
  if (flags == (0x2000 | 0x4000))
  {
    tmp_idx = "force-width, force-height";
  }
  else
    if (flags == 0x2000)
  {
    tmp_idx = "force-width";
  }
  else
    if (flags == 0x4000)
  {
    tmp_idx = "force-height";
  }
  else
    if (c->flags & 0x800000)
  {
    tmp_idx = "status line";
  }
  else
    tmp_idx = "a smaller client";
  xsnprintf(msg, sizeof(msg), "(size %ux%u from %s)", w->sx, w->sy, tmp);
  msglen = strlen(msg);
  if (((((tty->sy - 1) - lines) + top) > w->sy) && (tty->sx >= msglen))
  {
    msgx = tty->sx - msglen;
    msgy = ((tty->sy - 1) - lines) + top;
  }
  else
    if ((tty->sx - w->sx) > msglen)
  {
    msgx = tty->sx - msglen;
    msgy = ((tty->sy - 1) - lines) + top;
  }
  else
    small = 0;
  *msgx_ref = msgx;
  *msgy_ref = msgy;
  *small_ref = small;
  *flags_ref = flags;
  *tmp_idx_ref = tmp_idx;
  *msglen_ref = msglen;
}


----------------------------
None
----------------------------
void style_apply(struct grid_cell *gc, struct options *oo, const char *name)
{
  const struct grid_cell *gcp;
  unsigned int gcp_idx = 0;
  memcpy(gc, &grid_default_cell, sizeof(*gc));
  gcp_idx = options_get_style(oo, name);
  gc->fg = gcp->fg;
  gc->bg = gcp->bg;
  gc->attr |= gcp->attr;
}


----------------------------
None
----------------------------
***/


void screen_redraw_screen(struct client *c, int draw_panes, int draw_status, int draw_borders)
{
  struct options *oo = c->session->options;
  struct tty *tty = &c->tty;
  struct window *w = c->session->curw->window;
  struct options *wo = w->options;
  u_int top;
  u_int lines;
  int position;
  int pane_status;
  if (c->flags & 0x40)
  {
    return;
  }
  if (c->flags & 0x800000)
  {
    lines = 0;
  }
  else
    lines = status_line_size(c->session);
  if ((c->message_string != 0) || (c->prompt_string != 0))
  {
    lines = (lines == 0) ? (1) : (lines);
  }
  position = options_get_number(oo, "status-position");
  if ((lines != 0) && (position == 0))
  {
    top = 1;
  }
  else
    top = 0;
  if (lines == 0)
  {
    draw_status = 0;
  }
  if (draw_borders)
  {
    pane_status = options_get_number(wo, "pane-border-status");
    screen_redraw_draw_borders(c, pane_status, lines, top);
    if (pane_status != 0)
    {
      screen_redraw_draw_pane_status(c, pane_status);
    }
  }
  if (draw_panes)
  {
    screen_redraw_draw_panes(c, lines, top);
  }
  if (draw_status)
  {
    screen_redraw_draw_status(c, lines, top);
  }
  tty_reset(tty);
}


/*** DEPENDENCIES:
void tty_reset(struct tty *tty)
{
  struct grid_cell *gc = &tty->cell;
  if (!grid_cells_equal(gc, &grid_default_cell))
  {
    if ((gc->attr & 0x80) && tty_acs_needed(tty))
    {
      tty_putcode(tty, TTYC_RMACS);
    }
    tty_putcode(tty, TTYC_SGR0);
    memcpy(gc, &grid_default_cell, sizeof(*gc));
  }
  memcpy(&tty->last_cell, &grid_default_cell, sizeof(tty->last_cell));
  tty->last_wp = -1;
}


----------------------------
static void screen_redraw_draw_panes(struct client *c, u_int lines, u_int top)
{
  struct window *w = c->session->curw->window;
  struct tty *tty = &c->tty;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int i;
  u_int y;
  if (top)
  {
    y = lines;
  }
  else
    y = 0;
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    if (!window_pane_visible(wp))
    {
      continue;
    }
    for (i = 0; i < wp->sy; i += 1)
    {
      tty_draw_pane(tty, wp, i, wp->xoff, y + wp->yoff);
    }

    if (c->flags & 0x100)
    {
      screen_redraw_draw_number(c, wp, lines, top);
    }
  }

}


----------------------------
static void screen_redraw_draw_pane_status(struct client *c, int pane_status)
{
  struct window *w = c->session->curw->window;
  struct options *oo = c->session->options;
  struct tty *tty = &c->tty;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  int spos;
  u_int yoff;
  spos = options_get_number(oo, "status-position");
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    if (!window_pane_visible(wp))
    {
      continue;
    }
    if (pane_status == 1)
    {
      yoff = wp->yoff - 1;
    }
    else
      yoff = wp->yoff + wp->sy;
    if (spos == 0)
    {
      yoff += 1;
    }
    tty_draw_line(tty, 0, &wp->status_screen, 0, wp->xoff + 2, yoff);
  }

  tty_cursor(tty, 0, 0);
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
u_int status_line_size(struct session *s)
{
  if (s->statusat == (-1))
  {
    return 0;
  }
  return 1;
}


----------------------------
static void screen_redraw_draw_status(struct client *c, u_int lines, u_int top)
{
  struct tty *tty = &c->tty;
  u_int i;
  u_int y;
  if (top)
  {
    y = 0;
  }
  else
    y = tty->sy - lines;
  for (i = 0; i < lines; i += 1)
  {
    tty_draw_line(tty, 0, &c->status.status, i, 0, y);
  }

}


----------------------------
None
----------------------------
static void screen_redraw_draw_borders(struct client *c, int pane_status, u_int lines, u_int top)
{
  struct session *s = c->session;
  struct window *w = s->curw->window;
  struct options *oo = w->options;
  struct tty *tty = &c->tty;
  struct window_pane *wp;
  struct grid_cell m_active_gc;
  struct grid_cell active_gc;
  struct grid_cell m_other_gc;
  struct grid_cell other_gc;
  struct grid_cell msg_gc;
  u_int i;
  u_int j;
  u_int type;
  u_int msgx = 0;
  u_int msgy = 0;
  int active;
  int small;
  int flags;
  char msg[256];
  const char *tmp;
  unsigned int tmp_idx = 0;
  size_t msglen = 0;
  small = (((tty->sy - lines) + top) > w->sy) || (tty->sx > w->sx);
  if (small)
  {
    helper_screen_redraw_draw_borders_1(&msgx, &msgy, &small, &flags, &tmp_idx, &msglen, c, lines, top, w, tty, msg, tmp);
  }
  style_apply(&other_gc, oo, "pane-border-style");
  style_apply(&active_gc, oo, "pane-active-border-style");
  active_gc.attr = (other_gc.attr = 0x80);
  memcpy(&m_other_gc, &other_gc, sizeof(m_other_gc));
  m_other_gc.attr ^= 0x10;
  memcpy(&m_active_gc, &active_gc, sizeof(m_active_gc));
  m_active_gc.attr ^= 0x10;
  for (j = 0; j < (tty->sy - lines); j += 1)
  {
    helper_screen_redraw_draw_borders_2(&i, &type, &active, c, pane_status, lines, top, s, w, tty, wp, m_active_gc, active_gc, m_other_gc, other_gc, j, msgx, msgy, small);
  }

  if (small)
  {
    memcpy(&msg_gc, &grid_default_cell, sizeof(msg_gc));
    tty_attributes(tty, &msg_gc, 0);
    tty_cursor(tty, msgx, msgy);
    tty_puts(tty, msg);
  }
}


----------------------------
None
----------------------------
***/


static int screen_redraw_make_pane_status(struct client *c, struct window *w, struct window_pane *wp)
{
  struct grid_cell gc;
  const char *fmt;
  unsigned int fmt_idx = 0;
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  char *out;
  unsigned int out_idx = 0;
  size_t outlen;
  struct screen_write_ctx ctx;
  struct screen old;
  if (wp == w->active)
  {
    style_apply(&gc, w->options, "pane-active-border-style");
  }
  else
    style_apply(&gc, w->options, "pane-border-style");
  fmt_idx = options_get_string(w->options, "pane-border-format");
  ft_idx = format_create(c, 0, 0x80000000U | wp->id, 0);
  format_defaults(ft, c, 0, 0, wp);
  memcpy(&old, &wp->status_screen, sizeof(old));
  screen_init(&wp->status_screen, wp->sx, 1, 0);
  wp->status_screen.mode = 0;
  out_idx = format_expand(ft, fmt);
  outlen = screen_write_cstrlen("%s", out);
  if (outlen > (wp->sx - 4))
  {
    outlen = wp->sx - 4;
  }
  screen_resize(&wp->status_screen, outlen, 1, 0);
  screen_write_start(&ctx, 0, &wp->status_screen);
  screen_write_cursormove(&ctx, 0, 0);
  screen_write_clearline(&ctx, 8);
  screen_write_cnputs(&ctx, outlen, &gc, "%s", out);
  screen_write_stop(&ctx);
  free(out);
  format_free(ft);
  wp->status_size = outlen;
  if (grid_compare(wp->status_screen.grid, old.grid) == 0)
  {
    screen_free(&old);
    return 0;
  }
  screen_free(&old);
  return 1;
}


/*** DEPENDENCIES:
void style_apply(struct grid_cell *gc, struct options *oo, const char *name)
{
  const struct grid_cell *gcp;
  unsigned int gcp_idx = 0;
  memcpy(gc, &grid_default_cell, sizeof(*gc));
  gcp_idx = options_get_style(oo, name);
  gc->fg = gcp->fg;
  gc->bg = gcp->bg;
  gc->attr |= gcp->attr;
}


----------------------------
void screen_write_cnputs(struct screen_write_ctx *ctx, ssize_t maxlen, const struct grid_cell *gcp, const char *fmt, ...)
{
  struct grid_cell gc;
  struct utf8_data *ud = &gc.data;
  va_list ap;
  char *msg;
  u_char *ptr;
  unsigned int ptr_idx = 0;
  u_char *last;
  unsigned int last_idx = 0;
  size_t left;
  size_t size = 0;
  enum utf8_state more;
  memcpy(&gc, gcp, sizeof(gc));
  __builtin_va_start(ap);
  xvasprintf(&msg, fmt, ap);
  ;
  ptr_idx = msg;
  while (ptr[ptr_idx] != '\0')
  {
    helper_screen_write_cnputs_1(&ptr_idx, &last_idx, &left, &size, &more, ctx, maxlen, gcp, gc, ud, ptr, last);
  }

  free(msg);
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
None
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
void screen_free(struct screen *s)
{
  free(s->tabs);
  free(s->title);
  free(s->ccolour);
  grid_destroy(s->grid);
  screen_free_titles(s);
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
int grid_compare(struct grid *ga, struct grid *gb)
{
  struct grid_line *gla;
  unsigned int gla_idx = 0;
  struct grid_line *glb;
  unsigned int glb_idx = 0;
  struct grid_cell gca;
  struct grid_cell gcb;
  u_int xx;
  u_int yy;
  if ((ga->sx != gb->sx) || (ga->sy != gb->sy))
  {
    return 1;
  }
  for (yy = 0; yy < ga->sy; yy += 1)
  {
    gla_idx = &ga->linedata[yy];
    glb_idx = &gb->linedata[yy];
    if (gla->cellsize != glb->cellsize)
    {
      return 1;
    }
    for (xx = 0; xx < gla->cellsize; xx += 1)
    {
      grid_get_cell(ga, xx, yy, &gca);
      grid_get_cell(gb, xx, yy, &gcb);
      if (!grid_cells_equal(&gca, &gcb))
      {
        return 1;
      }
    }

  }

  return 0;
}


----------------------------
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
size_t screen_write_cstrlen(const char *fmt, ...)
{
  va_list ap;
  char *msg;
  char *msg2;
  unsigned int msg2_idx = 0;
  char *ptr;
  unsigned int ptr_idx = 0;
  char *ptr2;
  unsigned int ptr2_idx = 0;
  size_t size;
  __builtin_va_start(ap);
  xvasprintf(&msg, fmt, ap);
  ;
  msg2_idx = xmalloc(strlen(msg) + 1);
  ptr_idx = msg;
  ptr2_idx = &msg2[msg2_idx];
  while (ptr[ptr_idx] != '\0')
  {
    if ((ptr[0 + ptr_idx] == '#') && (ptr[1 + ptr_idx] == '['))
    {
      while ((ptr[ptr_idx] != ']') && (ptr[ptr_idx] != '\0'))
      {
        ptr_idx += 1;
      }

      if (ptr[ptr_idx] == ']')
      {
        ptr_idx += 1;
      }
      continue;
    }
    ptr2[ptr2_idx] = ptr[ptr_idx];
    ptr_idx += 1;
    ptr2_idx += 1;
  }

  ptr2[ptr2_idx] = '\0';
  size = screen_write_strlen("%s", msg2);
  free(msg);
  free(msg2);
  return size;
}


----------------------------
None
----------------------------
***/


void screen_redraw_update(struct client *c)
{
  struct window *w = c->session->curw->window;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  struct options *wo = w->options;
  int redraw;
  if (c->message_string != 0)
  {
    redraw = status_message_redraw(c);
  }
  else
    if (c->prompt_string != 0)
  {
    redraw = status_prompt_redraw(c);
  }
  else
    redraw = status_redraw(c);
  if (!redraw)
  {
    c->flags &= ~0x10;
  }
  if (options_get_number(wo, "pane-border-status") != 0)
  {
    redraw = 0;
    for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
    {
      if (screen_redraw_make_pane_status(c, w, wp))
      {
        redraw = 1;
      }
    }

    if (redraw)
    {
      c->flags |= 0x400;
    }
  }
}


/*** DEPENDENCIES:
int status_prompt_redraw(struct client *c)
{
  struct screen_write_ctx ctx;
  struct session *s = c->session;
  struct screen old_status;
  u_int i;
  u_int offset;
  u_int left;
  u_int start;
  u_int pcursor;
  u_int pwidth;
  u_int width;
  u_int lines;
  struct grid_cell gc;
  struct grid_cell cursorgc;
  if ((c->tty.sx == 0) || (c->tty.sy == 0))
  {
    return 0;
  }
  memcpy(&old_status, &c->status.status, sizeof(old_status));
  lines = status_line_size(c->session);
  if (lines <= 1)
  {
    lines = 1;
    screen_init(&c->status.status, c->tty.sx, 1, 0);
  }
  else
    screen_init(&c->status.status, c->tty.sx, lines, 0);
  if (c->prompt_mode == PROMPT_COMMAND)
  {
    style_apply(&gc, s->options, "message-command-style");
  }
  else
    style_apply(&gc, s->options, "message-style");
  memcpy(&cursorgc, &gc, sizeof(cursorgc));
  cursorgc.attr ^= 0x10;
  start = screen_write_strlen("%s", c->prompt_string);
  if (start > c->tty.sx)
  {
    start = c->tty.sx;
  }
  screen_write_start(&ctx, 0, &c->status.status);
  screen_write_cursormove(&ctx, 0, 0);
  for (offset = 0; offset < (lines * c->tty.sx); offset += 1)
  {
    screen_write_putc(&ctx, &gc, ' ');
  }

  screen_write_cursormove(&ctx, 0, 0);
  screen_write_nputs(&ctx, start, &gc, "%s", c->prompt_string);
  screen_write_cursormove(&ctx, start, 0);
  left = c->tty.sx - start;
  if (left == 0)
  {
    goto finished;
  }
  pcursor = utf8_strwidth(c->prompt_buffer, c->prompt_index);
  pwidth = utf8_strwidth(c->prompt_buffer, -1);
  if (pcursor >= left)
  {
    offset = (pcursor - left) + 1;
    pwidth = left;
  }
  else
    offset = 0;
  if (pwidth > left)
  {
    pwidth = left;
  }
  width = 0;
  for (i = 0; c->prompt_buffer[i].size != 0; i += 1)
  {
    helper_status_prompt_redraw_1(&width, c, ctx, i, offset, pwidth, gc, cursorgc);
  }

  if ((c->status.status.cx < (&c->status.status)->grid->sx) && (c->prompt_index >= i))
  {
    screen_write_putc(&ctx, &cursorgc, ' ');
  }
  finished:
  screen_write_stop(&ctx);

  if (grid_compare(c->status.status.grid, old_status.grid) == 0)
  {
    screen_free(&old_status);
    return 0;
  }
  screen_free(&old_status);
  return 1;
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
int status_message_redraw(struct client *c)
{
  struct screen_write_ctx ctx;
  struct session *s = c->session;
  struct screen old_status;
  size_t len;
  struct grid_cell gc;
  u_int lines;
  u_int offset;
  if ((c->tty.sx == 0) || (c->tty.sy == 0))
  {
    return 0;
  }
  memcpy(&old_status, &c->status.status, sizeof(old_status));
  lines = status_line_size(c->session);
  if (lines <= 1)
  {
    lines = 1;
    screen_init(&c->status.status, c->tty.sx, 1, 0);
  }
  else
    screen_init(&c->status.status, c->tty.sx, lines, 0);
  len = screen_write_strlen("%s", c->message_string);
  if (len > c->tty.sx)
  {
    len = c->tty.sx;
  }
  style_apply(&gc, s->options, "message-style");
  screen_write_start(&ctx, 0, &c->status.status);
  screen_write_cursormove(&ctx, 0, 0);
  for (offset = 0; offset < (lines * c->tty.sx); offset += 1)
  {
    screen_write_putc(&ctx, &gc, ' ');
  }

  screen_write_cursormove(&ctx, 0, lines - 1);
  screen_write_nputs(&ctx, len, &gc, "%s", c->message_string);
  screen_write_stop(&ctx);
  if (grid_compare(c->status.status.grid, old_status.grid) == 0)
  {
    screen_free(&old_status);
    return 0;
  }
  screen_free(&old_status);
  return 1;
}


----------------------------
int status_redraw(struct client *c)
{
  struct screen_write_ctx ctx;
  struct session *s = c->session;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct screen old_status;
  struct screen window_list;
  struct grid_cell stdgc;
  struct grid_cell lgc;
  struct grid_cell rgc;
  struct grid_cell gc;
  struct options *oo;
  unsigned int oo_idx = 0;
  time_t t;
  char *left;
  unsigned int left_idx = 0;
  char *right;
  unsigned int right_idx = 0;
  const char *sep;
  unsigned int sep_idx = 0;
  u_int offset;
  u_int needed;
  u_int lines;
  u_int wlstart;
  u_int wlwidth;
  u_int wlavailable;
  u_int wloffset;
  u_int wlsize;
  size_t llen;
  size_t rlen;
  size_t seplen;
  int larrow;
  int rarrow;
  if (c->status.old_status != 0)
  {
    screen_free(c->status.old_status);
    free(c->status.old_status);
    c->status.old_status = 0;
  }
  lines = status_line_size(s);
  if ((c->tty.sy == 0) || (lines == 0))
  {
    return 1;
  }
  left_idx = (right = &right[right_idx + right_idx]);
  larrow = (rarrow = 0);
  t = time(0);
  style_apply(&stdgc, s->options, "status-style");
  memcpy(&old_status, &c->status.status, sizeof(old_status));
  screen_init(&c->status.status, c->tty.sx, lines, 0);
  screen_write_start(&ctx, 0, &c->status.status);
  for (offset = 0; offset < (lines * c->tty.sx); offset += 1)
  {
    screen_write_putc(&ctx, &stdgc, ' ');
  }

  screen_write_stop(&ctx);
  if (c->tty.sy < lines)
  {
    goto out;
  }
  memcpy(&lgc, &stdgc, sizeof(lgc));
  left_idx = status_redraw_get_left(c, t, &lgc, &llen);
  memcpy(&rgc, &stdgc, sizeof(rgc));
  right_idx = status_redraw_get_right(c, t, &rgc, &rlen);
  needed = 0;
  if (llen != 0)
  {
    needed += llen;
  }
  if (rlen != 0)
  {
    needed += rlen;
  }
  if ((c->tty.sx == 0) || (c->tty.sx <= needed))
  {
    goto out;
  }
  wlavailable = c->tty.sx - needed;
  wlstart = (wloffset = (wlwidth = 0));
  for (wl_idx = winlinks_RB_MINMAX(&s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    free(wl->status_text);
    memcpy(&wl->status_cell, &stdgc, sizeof(wl->status_cell));
    wl->status_text = status_print(c, wl, t, &wl->status_cell);
    wl->status_width = screen_write_cstrlen("%s", wl->status_text);
    if ((&wl[wl_idx]) == s->curw)
    {
      wloffset = wlwidth;
    }
    oo_idx = wl->window->options;
    sep_idx = options_get_string(oo, "window-status-separator");
    seplen = screen_write_cstrlen("%s", sep);
    wlwidth += wl->status_width + seplen;
  }

  screen_init(&window_list, wlwidth, 1, 0);
  screen_write_start(&ctx, 0, &window_list);
  for (wl_idx = winlinks_RB_MINMAX(&s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    screen_write_cnputs(&ctx, -1, &wl->status_cell, "%s", wl->status_text);
    oo_idx = wl->window->options;
    sep_idx = options_get_string(oo, "window-status-separator");
    screen_write_cnputs(&ctx, -1, &stdgc, "%s", sep);
  }

  screen_write_stop(&ctx);
  if (wlwidth <= wlavailable)
  {
    goto draw;
  }
  wlsize = s->curw->status_width;
  if ((wloffset + wlsize) < wlavailable)
  {
    if (wlavailable > 0)
    {
      rarrow = 1;
      wlavailable -= 1;
    }
    wlwidth = wlavailable;
  }
  else
  {
    if (wlavailable > 0)
    {
      larrow = 1;
      wlavailable -= 1;
    }
    wlstart = (wloffset + wlsize) - wlavailable;
    if ((wlavailable > 0) && (wlwidth > ((wlstart + wlavailable) + 1)))
    {
      rarrow = 1;
      wlstart += 1;
      wlavailable -= 1;
    }
    wlwidth = wlavailable;
  }
  if ((wlwidth == 0) || (wlavailable == 0))
  {
    screen_free(&window_list);
    goto out;
  }
  offset = 0;
  for (wl_idx = winlinks_RB_MINMAX(&s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    if (((wl->flags & ((0x1 | 0x2) | 0x4)) && (larrow == 1)) && (offset < wlstart))
    {
      larrow = -1;
    }
    offset += wl->status_width;
    if (((wl->flags & ((0x1 | 0x2) | 0x4)) && (rarrow == 1)) && (offset > (wlstart + wlwidth)))
    {
      rarrow = -1;
    }
  }

  draw:
  screen_write_start(&ctx, 0, &c->status.status);

  screen_write_cursormove(&ctx, 0, 0);
  if (llen != 0)
  {
    screen_write_cnputs(&ctx, llen, &lgc, "%s", left);
  }
  if (larrow != 0)
  {
    memcpy(&gc, &stdgc, sizeof(gc));
    if (larrow == (-1))
    {
      gc.attr ^= 0x10;
    }
    screen_write_putc(&ctx, &gc, '<');
  }
  if (rarrow != 0)
  {
    screen_write_cursormove(&ctx, (c->tty.sx - rlen) - 1, 0);
    memcpy(&gc, &stdgc, sizeof(gc));
    if (rarrow == (-1))
    {
      gc.attr ^= 0x10;
    }
    screen_write_putc(&ctx, &gc, '>');
  }
  else
    screen_write_cursormove(&ctx, c->tty.sx - rlen, 0);
  if (rlen != 0)
  {
    screen_write_cnputs(&ctx, rlen, &rgc, "%s", right);
  }
  if (llen != 0)
  {
    wloffset = llen;
  }
  else
    wloffset = 0;
  if (wlwidth < wlavailable)
  {
    switch (options_get_number(s->options, "status-justify"))
    {
      case 1:
      {
        wloffset += (wlavailable - wlwidth) / 2;
        break;
      }

      case 2:
      {
        wloffset += wlavailable - wlwidth;
        break;
      }

    }

  }
  if (larrow != 0)
  {
    wloffset += 1;
  }
  c->wlmouse = (-wloffset) + wlstart;
  screen_write_cursormove(&ctx, wloffset, 0);
  screen_write_fast_copy(&ctx, &window_list, wlstart, 0, wlwidth, 1);
  screen_free(&window_list);
  screen_write_stop(&ctx);
  out:
  free(left);

  free(right);
  if (grid_compare(c->status.status.grid, old_status.grid) == 0)
  {
    screen_free(&old_status);
    return 0;
  }
  screen_free(&old_status);
  return 1;
}


----------------------------
None
----------------------------
static int screen_redraw_make_pane_status(struct client *c, struct window *w, struct window_pane *wp)
{
  struct grid_cell gc;
  const char *fmt;
  unsigned int fmt_idx = 0;
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  char *out;
  unsigned int out_idx = 0;
  size_t outlen;
  struct screen_write_ctx ctx;
  struct screen old;
  if (wp == w->active)
  {
    style_apply(&gc, w->options, "pane-active-border-style");
  }
  else
    style_apply(&gc, w->options, "pane-border-style");
  fmt_idx = options_get_string(w->options, "pane-border-format");
  ft_idx = format_create(c, 0, 0x80000000U | wp->id, 0);
  format_defaults(ft, c, 0, 0, wp);
  memcpy(&old, &wp->status_screen, sizeof(old));
  screen_init(&wp->status_screen, wp->sx, 1, 0);
  wp->status_screen.mode = 0;
  out_idx = format_expand(ft, fmt);
  outlen = screen_write_cstrlen("%s", out);
  if (outlen > (wp->sx - 4))
  {
    outlen = wp->sx - 4;
  }
  screen_resize(&wp->status_screen, outlen, 1, 0);
  screen_write_start(&ctx, 0, &wp->status_screen);
  screen_write_cursormove(&ctx, 0, 0);
  screen_write_clearline(&ctx, 8);
  screen_write_cnputs(&ctx, outlen, &gc, "%s", out);
  screen_write_stop(&ctx);
  free(out);
  format_free(ft);
  wp->status_size = outlen;
  if (grid_compare(wp->status_screen.grid, old.grid) == 0)
  {
    screen_free(&old);
    return 0;
  }
  screen_free(&old);
  return 1;
}


----------------------------
None
----------------------------
***/


