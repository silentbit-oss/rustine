static void screen_write_initctx(struct screen_write_ctx *ctx, struct tty_ctx *ttyctx)
{
  struct screen *s = ctx->s;
  memset(ttyctx, 0, sizeof(*ttyctx));
  ttyctx->wp = ctx->wp;
  ttyctx->ocx = s->cx;
  ttyctx->ocy = s->cy;
  ttyctx->orlower = s->rlower;
  ttyctx->orupper = s->rupper;
}


/*** DEPENDENCIES:
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
None
----------------------------
None
----------------------------
***/


void screen_write_setselection(struct screen_write_ctx *ctx, u_char *str, u_int len)
{
  struct tty_ctx ttyctx;
  screen_write_initctx(ctx, &ttyctx);
  ttyctx.ptr = str;
  ttyctx.num = len;
  tty_write(tty_cmd_setselection, &ttyctx);
}


/*** DEPENDENCIES:
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void screen_write_initctx(struct screen_write_ctx *ctx, struct tty_ctx *ttyctx)
{
  struct screen *s = ctx->s;
  memset(ttyctx, 0, sizeof(*ttyctx));
  ttyctx->wp = ctx->wp;
  ttyctx->ocx = s->cx;
  ttyctx->ocy = s->cy;
  ttyctx->orlower = s->rlower;
  ttyctx->orupper = s->rupper;
}


----------------------------
void tty_cmd_setselection(struct tty *tty, const struct tty_ctx *ctx)
{
  char *buf;
  unsigned int buf_idx = 0;
  size_t off;
  if (!tty_term_has(tty->term, TTYC_MS))
  {
    return;
  }
  off = (4 * ((ctx->num + 2) / 3)) + 1;
  buf_idx = xmalloc(off);
  b64_ntop(ctx->ptr, ctx->num, buf, off);
  tty_putcode_ptr2(tty, TTYC_MS, "", buf);
  free(buf);
}


----------------------------
void tty_write(void (*cmdfn)(struct tty *, const struct tty_ctx *), struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  struct client *c;
  unsigned int c_idx = 0;
  if (wp == 0)
  {
    return;
  }
  if ((wp->flags & (0x1 | 0x2)) || (!window_pane_visible(wp)))
  {
    return;
  }
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (!tty_client_ready(c, wp))
    {
      continue;
    }
    ctx->xoff = wp->xoff;
    ctx->yoff = wp->yoff;
    if (status_at_line(c) == 0)
    {
      ctx->yoff += status_line_size(c->session);
    }
    cmdfn(&c->tty, ctx);
  }

}


----------------------------
None
----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
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


/*** DEPENDENCIES:
extern const struct grid_cell grid_default_cell
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
void grid_view_get_cell(struct grid *gd, u_int px, u_int py, struct grid_cell *gc)
{
  grid_get_cell(gd, px, gd->hsize + py, gc);
}


----------------------------
void grid_view_set_cells(struct grid *gd, u_int px, u_int py, const struct grid_cell *gc, const char *s, size_t slen)
{
  grid_set_cells(gd, px, gd->hsize + py, gc, s, slen);
}


----------------------------
void grid_view_set_cell(struct grid *gd, u_int px, u_int py, const struct grid_cell *gc)
{
  grid_set_cell(gd, px, gd->hsize + py, gc);
}


----------------------------
None
----------------------------
struct screen_write_collect_item
{
  u_int x;
  int wrapped;
  u_int used;
  char data[256];
  struct grid_cell gc;
  struct 
  {
    struct screen_write_collect_item *tqe_next;
    struct screen_write_collect_item **tqe_prev;
  } entry;
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


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
***/


// hint:  ['ci_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int', 'y_ref is a mutable refrence to u_int', 'items_ref is a mutable refrence to u_int', 'ttyctx_ref is a mutable refrence to ', 'written_ref is a mutable refrence to size_t']
void helper_screen_write_collect_flush_1(unsigned int * const ci_idx_ref, unsigned int * const tmp_idx_ref, u_int * const y_ref, u_int * const items_ref, struct tty_ctx * const ttyctx_ref, size_t * const written_ref, struct screen_write_ctx * const ctx, struct screen_write_collect_item * const ci, struct screen_write_collect_item * const tmp)
{
  unsigned int ci_idx = *ci_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  u_int y = *y_ref;
  u_int items = *items_ref;
  struct tty_ctx ttyctx = *ttyctx_ref;
  size_t written = *written_ref;
  for (ci_idx = (&ctx->list[y].items)->tqh_first; ((&ci[ci_idx]) != 0) && ((tmp_idx = ci->entry.tqe_next, 1)); ci_idx = &tmp[tmp_idx])
  {
    screen_write_cursormove(ctx, ci->x, y);
    screen_write_initctx(ctx, &ttyctx);
    ttyctx.cell = &ci->gc;
    ttyctx.wrapped = ci->wrapped;
    ttyctx.ptr = ci->data;
    ttyctx.num = ci->used;
    tty_write(tty_cmd_cells, &ttyctx);
    items += 1;
    written += ci->used;
    do
    {
      if (ci->entry.tqe_next != 0)
      {
        ci->entry.tqe_next->entry.tqe_prev = ci->entry.tqe_prev;
      }
      else
        (&ctx->list[y].items)->tqh_last = ci->entry.tqe_prev;
      *ci->entry.tqe_prev = ci->entry.tqe_next;
      ;
      ;
    }
    while (0);
    free(ci);
  }

  *ci_idx_ref = ci_idx;
  *tmp_idx_ref = tmp_idx;
  *y_ref = y;
  *items_ref = items;
  *ttyctx_ref = ttyctx;
  *written_ref = written;
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
void tty_cmd_cells(struct tty *tty, const struct tty_ctx *ctx)
{
  tty_cursor_pane_unless_wrap(tty, ctx, ctx->ocx, ctx->ocy);
  tty_attributes(tty, ctx->cell, ctx->wp);
  tty_putn(tty, ctx->ptr, ctx->num, ctx->num);
}


----------------------------
struct screen_write_collect_item
{
  u_int x;
  int wrapped;
  u_int used;
  char data[256];
  struct grid_cell gc;
  struct 
  {
    struct screen_write_collect_item *tqe_next;
    struct screen_write_collect_item **tqe_prev;
  } entry;
}
----------------------------
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void screen_write_initctx(struct screen_write_ctx *ctx, struct tty_ctx *ttyctx)
{
  struct screen *s = ctx->s;
  memset(ttyctx, 0, sizeof(*ttyctx));
  ttyctx->wp = ctx->wp;
  ttyctx->ocx = s->cx;
  ttyctx->ocy = s->cy;
  ttyctx->orlower = s->rlower;
  ttyctx->orupper = s->rupper;
}


----------------------------
void tty_write(void (*cmdfn)(struct tty *, const struct tty_ctx *), struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  struct client *c;
  unsigned int c_idx = 0;
  if (wp == 0)
  {
    return;
  }
  if ((wp->flags & (0x1 | 0x2)) || (!window_pane_visible(wp)))
  {
    return;
  }
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (!tty_client_ready(c, wp))
    {
      continue;
    }
    ctx->xoff = wp->xoff;
    ctx->yoff = wp->yoff;
    if (status_at_line(c) == 0)
    {
      ctx->yoff += status_line_size(c->session);
    }
    cmdfn(&c->tty, ctx);
  }

}


----------------------------
None
----------------------------
None
----------------------------
***/


static void screen_write_collect_flush(struct screen_write_ctx *ctx, int scroll_only)
{
  struct screen *s = ctx->s;
  struct screen_write_collect_item *ci;
  unsigned int ci_idx = 0;
  struct screen_write_collect_item *tmp;
  unsigned int tmp_idx = 0;
  u_int y;
  u_int cx;
  u_int cy;
  u_int items = 0;
  struct tty_ctx ttyctx;
  size_t written = 0;
  if (ctx->scrolled != 0)
  {
    log_debug("%s: scrolled %u (region %u-%u)", __func__, ctx->scrolled, s->rupper, s->rlower);
    if (ctx->scrolled > ((s->rlower - s->rupper) + 1))
    {
      ctx->scrolled = (s->rlower - s->rupper) + 1;
    }
    screen_write_initctx(ctx, &ttyctx);
    ttyctx.num = ctx->scrolled;
    ttyctx.bg = ctx->bg;
    tty_write(tty_cmd_scrollup, &ttyctx);
  }
  ctx->scrolled = 0;
  ctx->bg = 8;
  if (scroll_only)
  {
    return;
  }
  cx = s->cx;
  cy = s->cy;
  for (y = 0; y < s->grid->sy; y += 1)
  {
    helper_screen_write_collect_flush_1(&ci_idx, &tmp_idx, &y, &items, &ttyctx, &written, ctx, ci, tmp);
  }

  s->cx = cx;
  s->cy = cy;
  log_debug("%s: flushed %u items (%zu bytes)", __func__, items, written);
  ctx->written += written;
}


/*** DEPENDENCIES:
struct screen_write_collect_item
{
  u_int x;
  int wrapped;
  u_int used;
  char data[256];
  struct grid_cell gc;
  struct 
  {
    struct screen_write_collect_item *tqe_next;
    struct screen_write_collect_item **tqe_prev;
  } entry;
}
----------------------------
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void screen_write_initctx(struct screen_write_ctx *ctx, struct tty_ctx *ttyctx)
{
  struct screen *s = ctx->s;
  memset(ttyctx, 0, sizeof(*ttyctx));
  ttyctx->wp = ctx->wp;
  ttyctx->ocx = s->cx;
  ttyctx->ocy = s->cy;
  ttyctx->orlower = s->rlower;
  ttyctx->orupper = s->rupper;
}


----------------------------
void tty_write(void (*cmdfn)(struct tty *, const struct tty_ctx *), struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  struct client *c;
  unsigned int c_idx = 0;
  if (wp == 0)
  {
    return;
  }
  if ((wp->flags & (0x1 | 0x2)) || (!window_pane_visible(wp)))
  {
    return;
  }
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (!tty_client_ready(c, wp))
    {
      continue;
    }
    ctx->xoff = wp->xoff;
    ctx->yoff = wp->yoff;
    if (status_at_line(c) == 0)
    {
      ctx->yoff += status_line_size(c->session);
    }
    cmdfn(&c->tty, ctx);
  }

}


----------------------------
void helper_screen_write_collect_flush_1(unsigned int * const ci_idx_ref, unsigned int * const tmp_idx_ref, u_int * const y_ref, u_int * const items_ref, struct tty_ctx * const ttyctx_ref, size_t * const written_ref, struct screen_write_ctx * const ctx, struct screen_write_collect_item * const ci, struct screen_write_collect_item * const tmp)
{
  unsigned int ci_idx = *ci_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  u_int y = *y_ref;
  u_int items = *items_ref;
  struct tty_ctx ttyctx = *ttyctx_ref;
  size_t written = *written_ref;
  for (ci_idx = (&ctx->list[y].items)->tqh_first; ((&ci[ci_idx]) != 0) && ((tmp_idx = ci->entry.tqe_next, 1)); ci_idx = &tmp[tmp_idx])
  {
    screen_write_cursormove(ctx, ci->x, y);
    screen_write_initctx(ctx, &ttyctx);
    ttyctx.cell = &ci->gc;
    ttyctx.wrapped = ci->wrapped;
    ttyctx.ptr = ci->data;
    ttyctx.num = ci->used;
    tty_write(tty_cmd_cells, &ttyctx);
    items += 1;
    written += ci->used;
    do
    {
      if (ci->entry.tqe_next != 0)
      {
        ci->entry.tqe_next->entry.tqe_prev = ci->entry.tqe_prev;
      }
      else
        (&ctx->list[y].items)->tqh_last = ci->entry.tqe_prev;
      *ci->entry.tqe_prev = ci->entry.tqe_next;
      ;
      ;
    }
    while (0);
    free(ci);
  }

  *ci_idx_ref = ci_idx;
  *tmp_idx_ref = tmp_idx;
  *y_ref = y;
  *items_ref = items;
  *ttyctx_ref = ttyctx;
  *written_ref = written;
}


----------------------------
void tty_cmd_scrollup(struct tty *tty, const struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  u_int i;
  if ((((!((ctx->xoff == 0) && (ctx->wp->screen->grid->sx >= tty->sx))) && (!(tty->term_type == TTY_VT420))) || tty_fake_bce(tty, wp, 8)) || (!tty_term_has(tty->term, TTYC_CSR)))
  {
    tty_redraw_region(tty, ctx);
    return;
  }
  tty_default_attributes(tty, wp, ctx->bg);
  tty_region_pane(tty, ctx, ctx->orupper, ctx->orlower);
  tty_margin_pane(tty, ctx);
  if ((ctx->num == 1) || (!tty_term_has(tty->term, TTYC_INDN)))
  {
    if (!(tty->term_type == TTY_VT420))
    {
      tty_cursor(tty, 0, tty->rlower);
    }
    else
      tty_cursor(tty, tty->rright, tty->rlower);
    for (i = 0; i < ctx->num; i += 1)
    {
      tty_putc(tty, '\n');
    }

  }
  else
  {
    tty_cursor(tty, 0, tty->cy);
    tty_putcode1(tty, TTYC_INDN, ctx->num);
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


void screen_write_stop(struct screen_write_ctx *ctx)
{
  screen_write_collect_end(ctx);
  screen_write_collect_flush(ctx, 0);
  log_debug("%s: %u cells (%u written, %u skipped)", __func__, ctx->cells, ctx->written, ctx->skipped);
  free(ctx->item);
  free(ctx->list);
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
None
----------------------------
static void screen_write_collect_flush(struct screen_write_ctx *ctx, int scroll_only)
{
  struct screen *s = ctx->s;
  struct screen_write_collect_item *ci;
  unsigned int ci_idx = 0;
  struct screen_write_collect_item *tmp;
  unsigned int tmp_idx = 0;
  u_int y;
  u_int cx;
  u_int cy;
  u_int items = 0;
  struct tty_ctx ttyctx;
  size_t written = 0;
  if (ctx->scrolled != 0)
  {
    log_debug("%s: scrolled %u (region %u-%u)", __func__, ctx->scrolled, s->rupper, s->rlower);
    if (ctx->scrolled > ((s->rlower - s->rupper) + 1))
    {
      ctx->scrolled = (s->rlower - s->rupper) + 1;
    }
    screen_write_initctx(ctx, &ttyctx);
    ttyctx.num = ctx->scrolled;
    ttyctx.bg = ctx->bg;
    tty_write(tty_cmd_scrollup, &ttyctx);
  }
  ctx->scrolled = 0;
  ctx->bg = 8;
  if (scroll_only)
  {
    return;
  }
  cx = s->cx;
  cy = s->cy;
  for (y = 0; y < s->grid->sy; y += 1)
  {
    helper_screen_write_collect_flush_1(&ci_idx, &tmp_idx, &y, &items, &ttyctx, &written, ctx, ci, tmp);
  }

  s->cx = cx;
  s->cy = cy;
  log_debug("%s: flushed %u items (%zu bytes)", __func__, items, written);
  ctx->written += written;
}


----------------------------
None
----------------------------
***/


void screen_write_mode_set(struct screen_write_ctx *ctx, int mode)
{
  struct screen *s = ctx->s;
  s->mode |= mode;
}


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
***/


void screen_write_mode_clear(struct screen_write_ctx *ctx, int mode)
{
  struct screen *s = ctx->s;
  s->mode &= ~mode;
}


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
***/


void screen_write_carriagereturn(struct screen_write_ctx *ctx)
{
  struct screen *s = ctx->s;
  s->cx = 0;
}


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
***/


static const struct grid_cell *screen_write_combine(struct screen_write_ctx *ctx, const struct utf8_data *ud, u_int *xx)
{
  struct screen *s = ctx->s;
  struct grid *gd = s->grid;
  static struct grid_cell gc;
  u_int n;
  if (s->cx == 0)
  {
    return 0;
  }
  if (ud->size == 0)
  {
    fatalx("UTF-8 data empty");
  }
  for (n = 1; n <= s->cx; n += 1)
  {
    grid_view_get_cell(gd, s->cx - n, s->cy, &gc);
    if ((~gc.flags) & 0x4)
    {
      break;
    }
  }

  if (n > s->cx)
  {
    return 0;
  }
  *xx = s->cx - n;
  if ((gc.data.size + ud->size) > (sizeof(gc.data.data)))
  {
    return 0;
  }
  log_debug("%s: %.*s onto %.*s at %u,%u", __func__, (int) ud->size, ud->data, (int) gc.data.size, gc.data.data, *xx, s->cy);
  memcpy(gc.data.data + gc.data.size, ud->data, ud->size);
  gc.data.size += ud->size;
  grid_view_set_cell(gd, *xx, s->cy, &gc);
  return &gc;
}


/*** DEPENDENCIES:
void grid_view_get_cell(struct grid *gd, u_int px, u_int py, struct grid_cell *gc)
{
  grid_get_cell(gd, px, gd->hsize + py, gc);
}


----------------------------
void grid_view_set_cell(struct grid *gd, u_int px, u_int py, const struct grid_cell *gc)
{
  grid_set_cell(gd, px, gd->hsize + py, gc);
}


----------------------------
None
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
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
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


// hint:  ['gc_idx_ref is a mutable refrence to unsigned int', 'ttyctx_ref is a mutable refrence to ', 'cx_ref is a mutable refrence to u_int', 'cy_ref is a mutable refrence to u_int']
void helper_screen_write_cell_1(unsigned int * const gc_idx_ref, struct tty_ctx * const ttyctx_ref, u_int * const cx_ref, u_int * const cy_ref, struct screen_write_ctx * const ctx, const struct grid_cell * const gc, struct screen * const s, u_int xx)
{
  unsigned int gc_idx = *gc_idx_ref;
  struct tty_ctx ttyctx = *ttyctx_ref;
  u_int cx = *cx_ref;
  u_int cy = *cy_ref;
  screen_write_collect_flush(ctx, 0);
  if ((gc_idx = screen_write_combine(ctx, &gc_idx->data, &xx)) != 0)
  {
    cx = s->cx;
    cy = s->cy;
    screen_write_cursormove(ctx, xx, s->cy);
    screen_write_initctx(ctx, &ttyctx);
    ttyctx.cell = &gc[gc_idx];
    tty_write(tty_cmd_cell, &ttyctx);
    s->cx = cx;
    s->cy = cy;
  }
  return;
  *gc_idx_ref = gc_idx;
  *ttyctx_ref = ttyctx;
  *cx_ref = cx;
  *cy_ref = cy;
}


/*** DEPENDENCIES:
static const struct grid_cell *screen_write_combine(struct screen_write_ctx *ctx, const struct utf8_data *ud, u_int *xx)
{
  struct screen *s = ctx->s;
  struct grid *gd = s->grid;
  static struct grid_cell gc;
  u_int n;
  if (s->cx == 0)
  {
    return 0;
  }
  if (ud->size == 0)
  {
    fatalx("UTF-8 data empty");
  }
  for (n = 1; n <= s->cx; n += 1)
  {
    grid_view_get_cell(gd, s->cx - n, s->cy, &gc);
    if ((~gc.flags) & 0x4)
    {
      break;
    }
  }

  if (n > s->cx)
  {
    return 0;
  }
  *xx = s->cx - n;
  if ((gc.data.size + ud->size) > (sizeof(gc.data.data)))
  {
    return 0;
  }
  log_debug("%s: %.*s onto %.*s at %u,%u", __func__, (int) ud->size, ud->data, (int) gc.data.size, gc.data.data, *xx, s->cy);
  memcpy(gc.data.data + gc.data.size, ud->data, ud->size);
  gc.data.size += ud->size;
  grid_view_set_cell(gd, *xx, s->cy, &gc);
  return &gc;
}


----------------------------
void tty_cmd_cell(struct tty *tty, const struct tty_ctx *ctx)
{
  if (((ctx->xoff + ctx->ocx) > (tty->sx - 1)) && (ctx->ocy == ctx->orlower))
  {
    if ((ctx->xoff == 0) && (ctx->wp->screen->grid->sx >= tty->sx))
    {
      tty_region_pane(tty, ctx, ctx->orupper, ctx->orlower);
    }
    else
      tty_margin_off(tty);
  }
  tty_cursor_pane_unless_wrap(tty, ctx, ctx->ocx, ctx->ocy);
  tty_cell(tty, ctx->cell, ctx->wp);
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
static void screen_write_collect_flush(struct screen_write_ctx *ctx, int scroll_only)
{
  struct screen *s = ctx->s;
  struct screen_write_collect_item *ci;
  unsigned int ci_idx = 0;
  struct screen_write_collect_item *tmp;
  unsigned int tmp_idx = 0;
  u_int y;
  u_int cx;
  u_int cy;
  u_int items = 0;
  struct tty_ctx ttyctx;
  size_t written = 0;
  if (ctx->scrolled != 0)
  {
    log_debug("%s: scrolled %u (region %u-%u)", __func__, ctx->scrolled, s->rupper, s->rlower);
    if (ctx->scrolled > ((s->rlower - s->rupper) + 1))
    {
      ctx->scrolled = (s->rlower - s->rupper) + 1;
    }
    screen_write_initctx(ctx, &ttyctx);
    ttyctx.num = ctx->scrolled;
    ttyctx.bg = ctx->bg;
    tty_write(tty_cmd_scrollup, &ttyctx);
  }
  ctx->scrolled = 0;
  ctx->bg = 8;
  if (scroll_only)
  {
    return;
  }
  cx = s->cx;
  cy = s->cy;
  for (y = 0; y < s->grid->sy; y += 1)
  {
    helper_screen_write_collect_flush_1(&ci_idx, &tmp_idx, &y, &items, &ttyctx, &written, ctx, ci, tmp);
  }

  s->cx = cx;
  s->cy = cy;
  log_debug("%s: flushed %u items (%zu bytes)", __func__, items, written);
  ctx->written += written;
}


----------------------------
None
----------------------------
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void screen_write_initctx(struct screen_write_ctx *ctx, struct tty_ctx *ttyctx)
{
  struct screen *s = ctx->s;
  memset(ttyctx, 0, sizeof(*ttyctx));
  ttyctx->wp = ctx->wp;
  ttyctx->ocx = s->cx;
  ttyctx->ocy = s->cy;
  ttyctx->orlower = s->rlower;
  ttyctx->orupper = s->rupper;
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
void tty_write(void (*cmdfn)(struct tty *, const struct tty_ctx *), struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  struct client *c;
  unsigned int c_idx = 0;
  if (wp == 0)
  {
    return;
  }
  if ((wp->flags & (0x1 | 0x2)) || (!window_pane_visible(wp)))
  {
    return;
  }
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (!tty_client_ready(c, wp))
    {
      continue;
    }
    ctx->xoff = wp->xoff;
    ctx->yoff = wp->yoff;
    if (status_at_line(c) == 0)
    {
      ctx->yoff += status_line_size(c->session);
    }
    cmdfn(&c->tty, ctx);
  }

}


----------------------------
None
----------------------------
None
----------------------------
***/


static int screen_write_overwrite(struct screen_write_ctx *ctx, struct grid_cell *gc, u_int width)
{
  struct screen *s = ctx->s;
  struct grid *gd = s->grid;
  struct grid_cell tmp_gc;
  u_int xx;
  int done = 0;
  if (gc->flags & 0x4)
  {
    xx = s->cx + 1;
    while ((--xx) > 0)
    {
      grid_view_get_cell(gd, xx, s->cy, &tmp_gc);
      if ((~tmp_gc.flags) & 0x4)
      {
        break;
      }
      log_debug("%s: padding at %u,%u", __func__, xx, s->cy);
      grid_view_set_cell(gd, xx, s->cy, &grid_default_cell);
    }

    log_debug("%s: character at %u,%u", __func__, xx, s->cy);
    grid_view_set_cell(gd, xx, s->cy, &grid_default_cell);
    done = 1;
  }
  if (((width != 1) || (gc->data.width != 1)) || (gc->flags & 0x4))
  {
    xx = (s->cx + width) - 1;
    while ((++xx) < s->grid->sx)
    {
      grid_view_get_cell(gd, xx, s->cy, &tmp_gc);
      if ((~tmp_gc.flags) & 0x4)
      {
        break;
      }
      log_debug("%s: overwrite at %u,%u", __func__, xx, s->cy);
      grid_view_set_cell(gd, xx, s->cy, &grid_default_cell);
      done = 1;
    }

  }
  return done;
}


/*** DEPENDENCIES:
extern const struct grid_cell grid_default_cell
----------------------------
void grid_view_get_cell(struct grid *gd, u_int px, u_int py, struct grid_cell *gc)
{
  grid_get_cell(gd, px, gd->hsize + py, gc);
}


----------------------------
void grid_view_set_cell(struct grid *gd, u_int px, u_int py, const struct grid_cell *gc)
{
  grid_set_cell(gd, px, gd->hsize + py, gc);
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


static void screen_write_collect_clear(struct screen_write_ctx *ctx, u_int y, u_int n)
{
  struct screen_write_collect_item *ci;
  unsigned int ci_idx = 0;
  struct screen_write_collect_item *tmp;
  unsigned int tmp_idx = 0;
  u_int i;
  size_t size;
  for (i = y; i < (y + n); i += 1)
  {
    if ((&ctx->list[i].items)->tqh_first == 0)
    {
      continue;
    }
    size = 0;
    for (ci_idx = (&ctx->list[i].items)->tqh_first; ((&ci[ci_idx]) != 0) && ((tmp_idx = ci->entry.tqe_next, 1)); ci_idx = &tmp[tmp_idx])
    {
      size += ci->used;
      do
      {
        if (ci->entry.tqe_next != 0)
        {
          ci->entry.tqe_next->entry.tqe_prev = ci->entry.tqe_prev;
        }
        else
          (&ctx->list[i].items)->tqh_last = ci->entry.tqe_prev;
        *ci->entry.tqe_prev = ci->entry.tqe_next;
        ;
        ;
      }
      while (0);
      free(ci);
    }

    ctx->skipped += size;
    log_debug("%s: dropped %zu bytes (line %u)", __func__, size, i);
  }

}


/*** DEPENDENCIES:
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
struct screen_write_collect_item
{
  u_int x;
  int wrapped;
  u_int used;
  char data[256];
  struct grid_cell gc;
  struct 
  {
    struct screen_write_collect_item *tqe_next;
    struct screen_write_collect_item **tqe_prev;
  } entry;
}
----------------------------
None
----------------------------
***/


static void screen_write_collect_scroll(struct screen_write_ctx *ctx)
{
  struct screen *s = ctx->s;
  struct screen_write_collect_line *cl;
  unsigned int cl_idx = 0;
  u_int y;
  log_debug("%s: at %u,%u (region %u-%u)", __func__, s->cx, s->cy, s->rupper, s->rlower);
  screen_write_collect_clear(ctx, s->rupper, 1);
  for (y = s->rupper; y < s->rlower; y += 1)
  {
    cl_idx = &ctx->list[y + 1];
    do
    {
      if (!((&cl->items)->tqh_first == 0))
      {
        *(&ctx->list[y].items)->tqh_last = (&cl->items)->tqh_first;
        (&cl->items)->tqh_first->entry.tqe_prev = (&ctx->list[y].items)->tqh_last;
        (&ctx->list[y].items)->tqh_last = (&cl->items)->tqh_last;
        do
        {
          (&cl->items)->tqh_first = 0;
          (&cl->items)->tqh_last = &(&cl->items)->tqh_first;
        }
        while (0);
      }
    }
    while (0);
    do
    {
      (&cl->items)->tqh_first = 0;
      (&cl->items)->tqh_last = &(&cl->items)->tqh_first;
    }
    while (0);
  }

}


/*** DEPENDENCIES:
static void screen_write_collect_clear(struct screen_write_ctx *ctx, u_int y, u_int n)
{
  struct screen_write_collect_item *ci;
  unsigned int ci_idx = 0;
  struct screen_write_collect_item *tmp;
  unsigned int tmp_idx = 0;
  u_int i;
  size_t size;
  for (i = y; i < (y + n); i += 1)
  {
    if ((&ctx->list[i].items)->tqh_first == 0)
    {
      continue;
    }
    size = 0;
    for (ci_idx = (&ctx->list[i].items)->tqh_first; ((&ci[ci_idx]) != 0) && ((tmp_idx = ci->entry.tqe_next, 1)); ci_idx = &tmp[tmp_idx])
    {
      size += ci->used;
      do
      {
        if (ci->entry.tqe_next != 0)
        {
          ci->entry.tqe_next->entry.tqe_prev = ci->entry.tqe_prev;
        }
        else
          (&ctx->list[i].items)->tqh_last = ci->entry.tqe_prev;
        *ci->entry.tqe_prev = ci->entry.tqe_next;
        ;
        ;
      }
      while (0);
      free(ci);
    }

    ctx->skipped += size;
    log_debug("%s: dropped %zu bytes (line %u)", __func__, size, i);
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
struct screen_write_collect_line
{
  struct 
  {
    struct screen_write_collect_item *tqh_first;
    struct screen_write_collect_item **tqh_last;
  } items;
}
----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
static void screen_write_collect_scroll(struct screen_write_ctx *ctx)
{
  struct screen *s = ctx->s;
  struct screen_write_collect_line *cl;
  unsigned int cl_idx = 0;
  u_int y;
  log_debug("%s: at %u,%u (region %u-%u)", __func__, s->cx, s->cy, s->rupper, s->rlower);
  screen_write_collect_clear(ctx, s->rupper, 1);
  for (y = s->rupper; y < s->rlower; y += 1)
  {
    cl_idx = &ctx->list[y + 1];
    do
    {
      if (!((&cl->items)->tqh_first == 0))
      {
        *(&ctx->list[y].items)->tqh_last = (&cl->items)->tqh_first;
        (&cl->items)->tqh_first->entry.tqe_prev = (&ctx->list[y].items)->tqh_last;
        (&ctx->list[y].items)->tqh_last = (&cl->items)->tqh_last;
        do
        {
          (&cl->items)->tqh_first = 0;
          (&cl->items)->tqh_last = &(&cl->items)->tqh_first;
        }
        while (0);
      }
    }
    while (0);
    do
    {
      (&cl->items)->tqh_first = 0;
      (&cl->items)->tqh_last = &(&cl->items)->tqh_first;
    }
    while (0);
  }

}


----------------------------
static void screen_write_collect_flush(struct screen_write_ctx *ctx, int scroll_only)
{
  struct screen *s = ctx->s;
  struct screen_write_collect_item *ci;
  unsigned int ci_idx = 0;
  struct screen_write_collect_item *tmp;
  unsigned int tmp_idx = 0;
  u_int y;
  u_int cx;
  u_int cy;
  u_int items = 0;
  struct tty_ctx ttyctx;
  size_t written = 0;
  if (ctx->scrolled != 0)
  {
    log_debug("%s: scrolled %u (region %u-%u)", __func__, ctx->scrolled, s->rupper, s->rlower);
    if (ctx->scrolled > ((s->rlower - s->rupper) + 1))
    {
      ctx->scrolled = (s->rlower - s->rupper) + 1;
    }
    screen_write_initctx(ctx, &ttyctx);
    ttyctx.num = ctx->scrolled;
    ttyctx.bg = ctx->bg;
    tty_write(tty_cmd_scrollup, &ttyctx);
  }
  ctx->scrolled = 0;
  ctx->bg = 8;
  if (scroll_only)
  {
    return;
  }
  cx = s->cx;
  cy = s->cy;
  for (y = 0; y < s->grid->sy; y += 1)
  {
    helper_screen_write_collect_flush_1(&ci_idx, &tmp_idx, &y, &items, &ttyctx, &written, ctx, ci, tmp);
  }

  s->cx = cx;
  s->cy = cy;
  log_debug("%s: flushed %u items (%zu bytes)", __func__, items, written);
  ctx->written += written;
}


----------------------------
None
----------------------------
void grid_view_scroll_region_up(struct grid *gd, u_int rupper, u_int rlower, u_int bg)
{
  if (gd->flags & 0x1)
  {
    grid_collect_history(gd);
    if ((rupper == 0) && (rlower == (gd->sy - 1)))
    {
      grid_scroll_history(gd, bg);
    }
    else
    {
      rupper = gd->hsize + rupper;
      rlower = gd->hsize + rlower;
      grid_scroll_history_region(gd, rupper, rlower, bg);
    }
  }
  else
  {
    rupper = gd->hsize + rupper;
    rlower = gd->hsize + rlower;
    grid_move_lines(gd, rupper, rupper + 1, rlower - rupper, bg);
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


// hint:  ['gce_idx_ref is a mutable refrence to unsigned int', 'skip_ref is a mutable refrence to int']
void helper_screen_write_cell_2(unsigned int * const gce_idx_ref, int * const skip_ref, const struct grid_cell * const gc, struct screen * const s, struct grid_line * const gl, struct grid_cell_entry * const gce)
{
  unsigned int gce_idx = *gce_idx_ref;
  int skip = *skip_ref;
  if (s->cx >= gl->cellsize)
  {
    skip = grid_cells_equal(gc, &grid_default_cell);
  }
  else
  {
    gce_idx = &gl->celldata[s->cx];
    if (gce->flags & 0x8)
    {
      skip = 0;
    }
    else
      if (gc->flags != gce->flags)
    {
      skip = 0;
    }
    else
      if (gc->attr != gce->data.attr)
    {
      skip = 0;
    }
    else
      if (gc->fg != gce->data.fg)
    {
      skip = 0;
    }
    else
      if (gc->bg != gce->data.bg)
    {
      skip = 0;
    }
    else
      if (gc->data.width != 1)
    {
      skip = 0;
    }
    else
      if (gc->data.size != 1)
    {
      skip = 0;
    }
    else
      if (gce->data.data != gc->data.data[0])
    {
      skip = 0;
    }
  }
  *gce_idx_ref = gce_idx;
  *skip_ref = skip;
}


/*** DEPENDENCIES:
struct grid_cell_entry
{
  u_char flags;
  union 
  {
    u_int offset;
    struct 
    {
      u_char attr;
      u_char fg;
      u_char bg;
      u_char data;
    } data;
  };
}
----------------------------
extern const struct grid_cell grid_default_cell
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
int grid_cells_equal(const struct grid_cell *gca, const struct grid_cell *gcb)
{
  if ((gca->fg != gcb->fg) || (gca->bg != gcb->bg))
  {
    return 0;
  }
  if ((gca->attr != gcb->attr) || (gca->flags != gcb->flags))
  {
    return 0;
  }
  if (gca->data.width != gcb->data.width)
  {
    return 0;
  }
  if (gca->data.size != gcb->data.size)
  {
    return 0;
  }
  return memcmp(gca->data.data, gcb->data.data, gca->data.size) == 0;
}


----------------------------
None
----------------------------
***/


void screen_write_cell(struct screen_write_ctx *ctx, const struct grid_cell *gc)
{
  unsigned int gc_idx = 0;
  struct screen *s = ctx->s;
  struct grid *gd = s->grid;
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  struct grid_cell_entry *gce;
  unsigned int gce_idx = 0;
  struct grid_cell tmp_gc;
  struct grid_cell now_gc;
  struct tty_ctx ttyctx;
  u_int sx = s->grid->sx;
  u_int sy = s->grid->sy;
  u_int width = gc->data.width;
  u_int xx;
  u_int last;
  u_int cx;
  u_int cy;
  int selected;
  int skip = 1;
  if (gc->flags & 0x4)
  {
    return;
  }
  ctx->cells += 1;
  if (width == 0)
  {
    helper_screen_write_cell_1(&gc_idx, &ttyctx, &cx, &cy, ctx, gc, s, xx);
  }
  screen_write_collect_flush(ctx, 1);
  if ((((~s->mode) & 0x10) && (width > 1)) && ((width > sx) || ((s->cx != sx) && (s->cx > (sx - width)))))
  {
    return;
  }
  if (s->mode & 0x2)
  {
    grid_view_insert_cells(s->grid, s->cx, s->cy, width, 8);
    skip = 0;
  }
  if ((s->mode & 0x10) && (s->cx > (sx - width)))
  {
    log_debug("%s: wrapped at %u,%u", __func__, s->cx, s->cy);
    screen_write_linefeed(ctx, 1, 8);
    s->cx = 0;
    screen_write_collect_flush(ctx, 1);
  }
  if ((s->cx > (sx - width)) || (s->cy > (sy - 1)))
  {
    return;
  }
  screen_write_initctx(ctx, &ttyctx);
  gl_idx = &s->grid->linedata[s->grid->hsize + s->cy];
  if (gl->flags & 0x2)
  {
    grid_view_get_cell(gd, s->cx, s->cy, &now_gc);
    if (screen_write_overwrite(ctx, &now_gc, width))
    {
      skip = 0;
    }
  }
  for (xx = s->cx + 1; xx < (s->cx + width); xx += 1)
  {
    log_debug("%s: new padding at %u,%u", __func__, xx, s->cy);
    grid_view_set_cell(gd, xx, s->cy, &screen_write_pad_cell);
    skip = 0;
  }

  if (skip)
  {
    helper_screen_write_cell_2(&gce_idx, &skip, gc, s, gl, gce);
  }
  selected = screen_check_selection(s, s->cx, s->cy);
  if (selected && ((~gc->flags) & 0x10))
  {
    memcpy(&tmp_gc, gc, sizeof(tmp_gc));
    tmp_gc.flags |= 0x10;
    grid_view_set_cell(gd, s->cx, s->cy, &tmp_gc);
  }
  else
    if ((!selected) && (gc->flags & 0x10))
  {
    memcpy(&tmp_gc, gc, sizeof(tmp_gc));
    tmp_gc.flags &= ~0x10;
    grid_view_set_cell(gd, s->cx, s->cy, &tmp_gc);
  }
  else
    if (!skip)
  {
    grid_view_set_cell(gd, s->cx, s->cy, gc);
  }
  if (selected)
  {
    skip = 0;
  }
  last = !(s->mode & 0x10);
  if (s->cx <= ((sx - last) - width))
  {
    s->cx += width;
  }
  else
    s->cx = sx - last;
  if (s->mode & 0x2)
  {
    screen_write_collect_flush(ctx, 0);
    ttyctx.num = width;
    tty_write(tty_cmd_insertcharacter, &ttyctx);
  }
  if (!skip)
  {
    if (selected)
    {
      screen_select_cell(s, &tmp_gc, gc);
      ttyctx.cell = &tmp_gc;
    }
    else
      ttyctx.cell = &gc[gc_idx];
    tty_write(tty_cmd_cell, &ttyctx);
    ctx->written += 1;
  }
  else
    ctx->skipped++;
}


/*** DEPENDENCIES:
void tty_cmd_cell(struct tty *tty, const struct tty_ctx *ctx)
{
  if (((ctx->xoff + ctx->ocx) > (tty->sx - 1)) && (ctx->ocy == ctx->orlower))
  {
    if ((ctx->xoff == 0) && (ctx->wp->screen->grid->sx >= tty->sx))
    {
      tty_region_pane(tty, ctx, ctx->orupper, ctx->orlower);
    }
    else
      tty_margin_off(tty);
  }
  tty_cursor_pane_unless_wrap(tty, ctx, ctx->ocx, ctx->ocy);
  tty_cell(tty, ctx->cell, ctx->wp);
}


----------------------------
struct grid_cell_entry
{
  u_char flags;
  union 
  {
    u_int offset;
    struct 
    {
      u_char attr;
      u_char fg;
      u_char bg;
      u_char data;
    } data;
  };
}
----------------------------
void helper_screen_write_cell_1(unsigned int * const gc_idx_ref, struct tty_ctx * const ttyctx_ref, u_int * const cx_ref, u_int * const cy_ref, struct screen_write_ctx * const ctx, const struct grid_cell * const gc, struct screen * const s, u_int xx)
{
  unsigned int gc_idx = *gc_idx_ref;
  struct tty_ctx ttyctx = *ttyctx_ref;
  u_int cx = *cx_ref;
  u_int cy = *cy_ref;
  screen_write_collect_flush(ctx, 0);
  if ((gc_idx = screen_write_combine(ctx, &gc_idx->data, &xx)) != 0)
  {
    cx = s->cx;
    cy = s->cy;
    screen_write_cursormove(ctx, xx, s->cy);
    screen_write_initctx(ctx, &ttyctx);
    ttyctx.cell = &gc[gc_idx];
    tty_write(tty_cmd_cell, &ttyctx);
    s->cx = cx;
    s->cy = cy;
  }
  return;
  *gc_idx_ref = gc_idx;
  *ttyctx_ref = ttyctx;
  *cx_ref = cx;
  *cy_ref = cy;
}


----------------------------
int screen_check_selection(struct screen *s, u_int px, u_int py)
{
  struct screen_sel *sel = &s->sel;
  u_int xx;
  if ((!sel->flag) || sel->hidden)
  {
    return 0;
  }
  if (sel->rectflag)
  {
    helper_screen_check_selection_1(px, py, sel);
  }
  else
  {
    helper_screen_check_selection_2(&xx, px, py, sel);
  }
  return 1;
}


----------------------------
void grid_view_insert_cells(struct grid *gd, u_int px, u_int py, u_int nx, u_int bg)
{
  u_int sx;
  px = px;
  py = gd->hsize + py;
  sx = gd->sx;
  if (px >= (sx - 1))
  {
    grid_clear(gd, px, py, 1, 1, bg);
  }
  else
    grid_move_cells(gd, px + nx, px, py, (sx - px) - nx, bg);
}


----------------------------
static int screen_write_overwrite(struct screen_write_ctx *ctx, struct grid_cell *gc, u_int width)
{
  struct screen *s = ctx->s;
  struct grid *gd = s->grid;
  struct grid_cell tmp_gc;
  u_int xx;
  int done = 0;
  if (gc->flags & 0x4)
  {
    xx = s->cx + 1;
    while ((--xx) > 0)
    {
      grid_view_get_cell(gd, xx, s->cy, &tmp_gc);
      if ((~tmp_gc.flags) & 0x4)
      {
        break;
      }
      log_debug("%s: padding at %u,%u", __func__, xx, s->cy);
      grid_view_set_cell(gd, xx, s->cy, &grid_default_cell);
    }

    log_debug("%s: character at %u,%u", __func__, xx, s->cy);
    grid_view_set_cell(gd, xx, s->cy, &grid_default_cell);
    done = 1;
  }
  if (((width != 1) || (gc->data.width != 1)) || (gc->flags & 0x4))
  {
    xx = (s->cx + width) - 1;
    while ((++xx) < s->grid->sx)
    {
      grid_view_get_cell(gd, xx, s->cy, &tmp_gc);
      if ((~tmp_gc.flags) & 0x4)
      {
        break;
      }
      log_debug("%s: overwrite at %u,%u", __func__, xx, s->cy);
      grid_view_set_cell(gd, xx, s->cy, &grid_default_cell);
      done = 1;
    }

  }
  return done;
}


----------------------------
void grid_view_set_cell(struct grid *gd, u_int px, u_int py, const struct grid_cell *gc)
{
  grid_set_cell(gd, px, gd->hsize + py, gc);
}


----------------------------
static void screen_write_collect_flush(struct screen_write_ctx *ctx, int scroll_only)
{
  struct screen *s = ctx->s;
  struct screen_write_collect_item *ci;
  unsigned int ci_idx = 0;
  struct screen_write_collect_item *tmp;
  unsigned int tmp_idx = 0;
  u_int y;
  u_int cx;
  u_int cy;
  u_int items = 0;
  struct tty_ctx ttyctx;
  size_t written = 0;
  if (ctx->scrolled != 0)
  {
    log_debug("%s: scrolled %u (region %u-%u)", __func__, ctx->scrolled, s->rupper, s->rlower);
    if (ctx->scrolled > ((s->rlower - s->rupper) + 1))
    {
      ctx->scrolled = (s->rlower - s->rupper) + 1;
    }
    screen_write_initctx(ctx, &ttyctx);
    ttyctx.num = ctx->scrolled;
    ttyctx.bg = ctx->bg;
    tty_write(tty_cmd_scrollup, &ttyctx);
  }
  ctx->scrolled = 0;
  ctx->bg = 8;
  if (scroll_only)
  {
    return;
  }
  cx = s->cx;
  cy = s->cy;
  for (y = 0; y < s->grid->sy; y += 1)
  {
    helper_screen_write_collect_flush_1(&ci_idx, &tmp_idx, &y, &items, &ttyctx, &written, ctx, ci, tmp);
  }

  s->cx = cx;
  s->cy = cy;
  log_debug("%s: flushed %u items (%zu bytes)", __func__, items, written);
  ctx->written += written;
}


----------------------------
None
----------------------------
static void screen_write_initctx(struct screen_write_ctx *ctx, struct tty_ctx *ttyctx)
{
  struct screen *s = ctx->s;
  memset(ttyctx, 0, sizeof(*ttyctx));
  ttyctx->wp = ctx->wp;
  ttyctx->ocx = s->cx;
  ttyctx->ocy = s->cy;
  ttyctx->orlower = s->rlower;
  ttyctx->orupper = s->rupper;
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
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
void tty_cmd_insertcharacter(struct tty *tty, const struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  if (((!((ctx->xoff == 0) && (ctx->wp->screen->grid->sx >= tty->sx))) || tty_fake_bce(tty, wp, ctx->bg)) || ((!tty_term_has(tty->term, TTYC_ICH)) && (!tty_term_has(tty->term, TTYC_ICH1))))
  {
    tty_draw_pane(tty, wp, ctx->ocy, ctx->xoff, ctx->yoff);
    return;
  }
  tty_default_attributes(tty, wp, ctx->bg);
  tty_cursor_pane(tty, ctx, ctx->ocx, ctx->ocy);
  tty_emulate_repeat(tty, TTYC_ICH, TTYC_ICH1, ctx->num);
}


----------------------------
void grid_view_get_cell(struct grid *gd, u_int px, u_int py, struct grid_cell *gc)
{
  grid_get_cell(gd, px, gd->hsize + py, gc);
}


----------------------------
void screen_select_cell(struct screen *s, struct grid_cell *dst, const struct grid_cell *src)
{
  if ((!s->sel.flag) || s->sel.hidden)
  {
    return;
  }
  memcpy(dst, &s->sel.cell, sizeof(*dst));
  utf8_copy(&dst->data, &src->data);
  dst->attr = dst->attr & (~0x80);
  dst->attr |= src->attr & 0x80;
  dst->flags = src->flags;
}


----------------------------
static const struct grid_cell screen_write_pad_cell = {0x4, 0, 8, 8, {{0}, 0, 0, 0}}
----------------------------
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
void tty_write(void (*cmdfn)(struct tty *, const struct tty_ctx *), struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  struct client *c;
  unsigned int c_idx = 0;
  if (wp == 0)
  {
    return;
  }
  if ((wp->flags & (0x1 | 0x2)) || (!window_pane_visible(wp)))
  {
    return;
  }
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (!tty_client_ready(c, wp))
    {
      continue;
    }
    ctx->xoff = wp->xoff;
    ctx->yoff = wp->yoff;
    if (status_at_line(c) == 0)
    {
      ctx->yoff += status_line_size(c->session);
    }
    cmdfn(&c->tty, ctx);
  }

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
void helper_screen_write_cell_2(unsigned int * const gce_idx_ref, int * const skip_ref, const struct grid_cell * const gc, struct screen * const s, struct grid_line * const gl, struct grid_cell_entry * const gce)
{
  unsigned int gce_idx = *gce_idx_ref;
  int skip = *skip_ref;
  if (s->cx >= gl->cellsize)
  {
    skip = grid_cells_equal(gc, &grid_default_cell);
  }
  else
  {
    gce_idx = &gl->celldata[s->cx];
    if (gce->flags & 0x8)
    {
      skip = 0;
    }
    else
      if (gc->flags != gce->flags)
    {
      skip = 0;
    }
    else
      if (gc->attr != gce->data.attr)
    {
      skip = 0;
    }
    else
      if (gc->fg != gce->data.fg)
    {
      skip = 0;
    }
    else
      if (gc->bg != gce->data.bg)
    {
      skip = 0;
    }
    else
      if (gc->data.width != 1)
    {
      skip = 0;
    }
    else
      if (gc->data.size != 1)
    {
      skip = 0;
    }
    else
      if (gce->data.data != gc->data.data[0])
    {
      skip = 0;
    }
  }
  *gce_idx_ref = gce_idx;
  *skip_ref = skip;
}


----------------------------
None
----------------------------
***/


void screen_write_putc(struct screen_write_ctx *ctx, const struct grid_cell *gcp, u_char ch)
{
  struct grid_cell gc;
  memcpy(&gc, gcp, sizeof(gc));
  utf8_set(&gc.data, ch);
  screen_write_cell(ctx, &gc);
}


/*** DEPENDENCIES:
void utf8_set(struct utf8_data *ud, u_char ch)
{
  static const struct utf8_data empty = {{0}, 1, 1, 1};
  memcpy(ud, &empty, sizeof(*ud));
  *ud->data = ch;
}


----------------------------
None
----------------------------
void screen_write_cell(struct screen_write_ctx *ctx, const struct grid_cell *gc)
{
  unsigned int gc_idx = 0;
  struct screen *s = ctx->s;
  struct grid *gd = s->grid;
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  struct grid_cell_entry *gce;
  unsigned int gce_idx = 0;
  struct grid_cell tmp_gc;
  struct grid_cell now_gc;
  struct tty_ctx ttyctx;
  u_int sx = s->grid->sx;
  u_int sy = s->grid->sy;
  u_int width = gc->data.width;
  u_int xx;
  u_int last;
  u_int cx;
  u_int cy;
  int selected;
  int skip = 1;
  if (gc->flags & 0x4)
  {
    return;
  }
  ctx->cells += 1;
  if (width == 0)
  {
    helper_screen_write_cell_1(&gc_idx, &ttyctx, &cx, &cy, ctx, gc, s, xx);
  }
  screen_write_collect_flush(ctx, 1);
  if ((((~s->mode) & 0x10) && (width > 1)) && ((width > sx) || ((s->cx != sx) && (s->cx > (sx - width)))))
  {
    return;
  }
  if (s->mode & 0x2)
  {
    grid_view_insert_cells(s->grid, s->cx, s->cy, width, 8);
    skip = 0;
  }
  if ((s->mode & 0x10) && (s->cx > (sx - width)))
  {
    log_debug("%s: wrapped at %u,%u", __func__, s->cx, s->cy);
    screen_write_linefeed(ctx, 1, 8);
    s->cx = 0;
    screen_write_collect_flush(ctx, 1);
  }
  if ((s->cx > (sx - width)) || (s->cy > (sy - 1)))
  {
    return;
  }
  screen_write_initctx(ctx, &ttyctx);
  gl_idx = &s->grid->linedata[s->grid->hsize + s->cy];
  if (gl->flags & 0x2)
  {
    grid_view_get_cell(gd, s->cx, s->cy, &now_gc);
    if (screen_write_overwrite(ctx, &now_gc, width))
    {
      skip = 0;
    }
  }
  for (xx = s->cx + 1; xx < (s->cx + width); xx += 1)
  {
    log_debug("%s: new padding at %u,%u", __func__, xx, s->cy);
    grid_view_set_cell(gd, xx, s->cy, &screen_write_pad_cell);
    skip = 0;
  }

  if (skip)
  {
    helper_screen_write_cell_2(&gce_idx, &skip, gc, s, gl, gce);
  }
  selected = screen_check_selection(s, s->cx, s->cy);
  if (selected && ((~gc->flags) & 0x10))
  {
    memcpy(&tmp_gc, gc, sizeof(tmp_gc));
    tmp_gc.flags |= 0x10;
    grid_view_set_cell(gd, s->cx, s->cy, &tmp_gc);
  }
  else
    if ((!selected) && (gc->flags & 0x10))
  {
    memcpy(&tmp_gc, gc, sizeof(tmp_gc));
    tmp_gc.flags &= ~0x10;
    grid_view_set_cell(gd, s->cx, s->cy, &tmp_gc);
  }
  else
    if (!skip)
  {
    grid_view_set_cell(gd, s->cx, s->cy, gc);
  }
  if (selected)
  {
    skip = 0;
  }
  last = !(s->mode & 0x10);
  if (s->cx <= ((sx - last) - width))
  {
    s->cx += width;
  }
  else
    s->cx = sx - last;
  if (s->mode & 0x2)
  {
    screen_write_collect_flush(ctx, 0);
    ttyctx.num = width;
    tty_write(tty_cmd_insertcharacter, &ttyctx);
  }
  if (!skip)
  {
    if (selected)
    {
      screen_select_cell(s, &tmp_gc, gc);
      ttyctx.cell = &tmp_gc;
    }
    else
      ttyctx.cell = &gc[gc_idx];
    tty_write(tty_cmd_cell, &ttyctx);
    ctx->written += 1;
  }
  else
    ctx->skipped++;
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
None
----------------------------
***/


// hint:  ['ptr_idx_ref is a mutable refrence to unsigned int', 'left_ref is a mutable refrence to size_t', 'size_ref is a mutable refrence to size_t', 'more_ref is a mutable refrence to ']
void helper_helper_screen_write_vnputs_1_1(unsigned int * const ptr_idx_ref, size_t * const left_ref, size_t * const size_ref, enum utf8_state * const more_ref, struct screen_write_ctx * const ctx, ssize_t maxlen, struct utf8_data * const ud, u_char * const ptr, struct grid_cell gc)
{
  unsigned int ptr_idx = *ptr_idx_ref;
  size_t left = *left_ref;
  size_t size = *size_ref;
  enum utf8_state more = *more_ref;
  ptr_idx += 1;
  left = strlen(ptr);
  if (left < (((size_t) ud->size) - 1))
  {
    break;
  }
  while ((more = utf8_append(ud, *(&ptr[ptr_idx]))) == UTF8_MORE)
  {
    ptr_idx += 1;
  }

  ptr_idx += 1;
  if (more != UTF8_DONE)
  {
    continue;
  }
  if ((maxlen > 0) && ((size + ud->width) > ((size_t) maxlen)))
  {
    while (size < ((size_t) maxlen))
    {
      screen_write_putc(ctx, &gc, ' ');
      size += 1;
    }

    break;
  }
  size += ud->width;
  screen_write_cell(ctx, &gc);
  *ptr_idx_ref = ptr_idx;
  *left_ref = left;
  *size_ref = size;
  *more_ref = more;
}


/*** DEPENDENCIES:
None
----------------------------
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
}
----------------------------
void screen_write_cell(struct screen_write_ctx *ctx, const struct grid_cell *gc)
{
  unsigned int gc_idx = 0;
  struct screen *s = ctx->s;
  struct grid *gd = s->grid;
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  struct grid_cell_entry *gce;
  unsigned int gce_idx = 0;
  struct grid_cell tmp_gc;
  struct grid_cell now_gc;
  struct tty_ctx ttyctx;
  u_int sx = s->grid->sx;
  u_int sy = s->grid->sy;
  u_int width = gc->data.width;
  u_int xx;
  u_int last;
  u_int cx;
  u_int cy;
  int selected;
  int skip = 1;
  if (gc->flags & 0x4)
  {
    return;
  }
  ctx->cells += 1;
  if (width == 0)
  {
    helper_screen_write_cell_1(&gc_idx, &ttyctx, &cx, &cy, ctx, gc, s, xx);
  }
  screen_write_collect_flush(ctx, 1);
  if ((((~s->mode) & 0x10) && (width > 1)) && ((width > sx) || ((s->cx != sx) && (s->cx > (sx - width)))))
  {
    return;
  }
  if (s->mode & 0x2)
  {
    grid_view_insert_cells(s->grid, s->cx, s->cy, width, 8);
    skip = 0;
  }
  if ((s->mode & 0x10) && (s->cx > (sx - width)))
  {
    log_debug("%s: wrapped at %u,%u", __func__, s->cx, s->cy);
    screen_write_linefeed(ctx, 1, 8);
    s->cx = 0;
    screen_write_collect_flush(ctx, 1);
  }
  if ((s->cx > (sx - width)) || (s->cy > (sy - 1)))
  {
    return;
  }
  screen_write_initctx(ctx, &ttyctx);
  gl_idx = &s->grid->linedata[s->grid->hsize + s->cy];
  if (gl->flags & 0x2)
  {
    grid_view_get_cell(gd, s->cx, s->cy, &now_gc);
    if (screen_write_overwrite(ctx, &now_gc, width))
    {
      skip = 0;
    }
  }
  for (xx = s->cx + 1; xx < (s->cx + width); xx += 1)
  {
    log_debug("%s: new padding at %u,%u", __func__, xx, s->cy);
    grid_view_set_cell(gd, xx, s->cy, &screen_write_pad_cell);
    skip = 0;
  }

  if (skip)
  {
    helper_screen_write_cell_2(&gce_idx, &skip, gc, s, gl, gce);
  }
  selected = screen_check_selection(s, s->cx, s->cy);
  if (selected && ((~gc->flags) & 0x10))
  {
    memcpy(&tmp_gc, gc, sizeof(tmp_gc));
    tmp_gc.flags |= 0x10;
    grid_view_set_cell(gd, s->cx, s->cy, &tmp_gc);
  }
  else
    if ((!selected) && (gc->flags & 0x10))
  {
    memcpy(&tmp_gc, gc, sizeof(tmp_gc));
    tmp_gc.flags &= ~0x10;
    grid_view_set_cell(gd, s->cx, s->cy, &tmp_gc);
  }
  else
    if (!skip)
  {
    grid_view_set_cell(gd, s->cx, s->cy, gc);
  }
  if (selected)
  {
    skip = 0;
  }
  last = !(s->mode & 0x10);
  if (s->cx <= ((sx - last) - width))
  {
    s->cx += width;
  }
  else
    s->cx = sx - last;
  if (s->mode & 0x2)
  {
    screen_write_collect_flush(ctx, 0);
    ttyctx.num = width;
    tty_write(tty_cmd_insertcharacter, &ttyctx);
  }
  if (!skip)
  {
    if (selected)
    {
      screen_select_cell(s, &tmp_gc, gc);
      ttyctx.cell = &tmp_gc;
    }
    else
      ttyctx.cell = &gc[gc_idx];
    tty_write(tty_cmd_cell, &ttyctx);
    ctx->written += 1;
  }
  else
    ctx->skipped++;
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
enum utf8_state
{
  UTF8_MORE,
  UTF8_DONE,
  UTF8_ERROR
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


// hint:  ['gc_ref is a mutable refrence to ', 'ptr_idx_ref is a mutable refrence to unsigned int', 'left_ref is a mutable refrence to size_t', 'size_ref is a mutable refrence to size_t', 'more_ref is a mutable refrence to ']
void helper_screen_write_vnputs_1(struct grid_cell * const gc_ref, unsigned int * const ptr_idx_ref, size_t * const left_ref, size_t * const size_ref, enum utf8_state * const more_ref, struct screen_write_ctx * const ctx, ssize_t maxlen, struct utf8_data * const ud, u_char * const ptr)
{
  struct grid_cell gc = *gc_ref;
  unsigned int ptr_idx = *ptr_idx_ref;
  size_t left = *left_ref;
  size_t size = *size_ref;
  enum utf8_state more = *more_ref;
  if ((ptr[ptr_idx] > 0x7f) && (utf8_open(ud, *(&ptr[ptr_idx])) == UTF8_MORE))
  {
    helper_helper_screen_write_vnputs_1_1(&ptr_idx, &left, &size, &more, ctx, maxlen, ud, ptr, gc);
  }
  else
  {
    if ((maxlen > 0) && ((size + 1) > ((size_t) maxlen)))
    {
      break;
    }
    if (ptr[ptr_idx] == '\001')
    {
      gc.attr ^= 0x80;
    }
    else
      if ((ptr[ptr_idx] > 0x1f) && (ptr[ptr_idx] < 0x7f))
    {
      size += 1;
      screen_write_putc(ctx, &gc, *(&ptr[ptr_idx]));
    }
    ptr_idx += 1;
  }
  *gc_ref = gc;
  *ptr_idx_ref = ptr_idx;
  *left_ref = left;
  *size_ref = size;
  *more_ref = more;
}


/*** DEPENDENCIES:
None
----------------------------
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
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
enum utf8_state
{
  UTF8_MORE,
  UTF8_DONE,
  UTF8_ERROR
}
----------------------------
void helper_helper_screen_write_vnputs_1_1(unsigned int * const ptr_idx_ref, size_t * const left_ref, size_t * const size_ref, enum utf8_state * const more_ref, struct screen_write_ctx * const ctx, ssize_t maxlen, struct utf8_data * const ud, u_char * const ptr, struct grid_cell gc)
{
  unsigned int ptr_idx = *ptr_idx_ref;
  size_t left = *left_ref;
  size_t size = *size_ref;
  enum utf8_state more = *more_ref;
  ptr_idx += 1;
  left = strlen(ptr);
  if (left < (((size_t) ud->size) - 1))
  {
    break;
  }
  while ((more = utf8_append(ud, *(&ptr[ptr_idx]))) == UTF8_MORE)
  {
    ptr_idx += 1;
  }

  ptr_idx += 1;
  if (more != UTF8_DONE)
  {
    continue;
  }
  if ((maxlen > 0) && ((size + ud->width) > ((size_t) maxlen)))
  {
    while (size < ((size_t) maxlen))
    {
      screen_write_putc(ctx, &gc, ' ');
      size += 1;
    }

    break;
  }
  size += ud->width;
  screen_write_cell(ctx, &gc);
  *ptr_idx_ref = ptr_idx;
  *left_ref = left;
  *size_ref = size;
  *more_ref = more;
}


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


void screen_write_vnputs(struct screen_write_ctx *ctx, ssize_t maxlen, const struct grid_cell *gcp, const char *fmt, va_list ap)
{
  struct grid_cell gc;
  struct utf8_data *ud = &gc.data;
  char *msg;
  u_char *ptr;
  unsigned int ptr_idx = 0;
  size_t left;
  size_t size = 0;
  enum utf8_state more;
  memcpy(&gc, gcp, sizeof(gc));
  xvasprintf(&msg, fmt, ap);
  ptr_idx = msg;
  while (ptr[ptr_idx] != '\0')
  {
    helper_screen_write_vnputs_1(&gc, &ptr_idx, &left, &size, &more, ctx, maxlen, ud, ptr);
  }

  free(msg);
}


/*** DEPENDENCIES:
int xvasprintf(char **ret, const char *fmt, va_list ap)
{
  int i;
  i = vasprintf(ret, fmt, ap);
  if ((i < 0) || ((*ret) == 0))
  {
    fatalx("xasprintf: %s", strerror(errno));
  }
  return i;
}


----------------------------
void helper_screen_write_vnputs_1(struct grid_cell * const gc_ref, unsigned int * const ptr_idx_ref, size_t * const left_ref, size_t * const size_ref, enum utf8_state * const more_ref, struct screen_write_ctx * const ctx, ssize_t maxlen, struct utf8_data * const ud, u_char * const ptr)
{
  struct grid_cell gc = *gc_ref;
  unsigned int ptr_idx = *ptr_idx_ref;
  size_t left = *left_ref;
  size_t size = *size_ref;
  enum utf8_state more = *more_ref;
  if ((ptr[ptr_idx] > 0x7f) && (utf8_open(ud, *(&ptr[ptr_idx])) == UTF8_MORE))
  {
    helper_helper_screen_write_vnputs_1_1(&ptr_idx, &left, &size, &more, ctx, maxlen, ud, ptr, gc);
  }
  else
  {
    if ((maxlen > 0) && ((size + 1) > ((size_t) maxlen)))
    {
      break;
    }
    if (ptr[ptr_idx] == '\001')
    {
      gc.attr ^= 0x80;
    }
    else
      if ((ptr[ptr_idx] > 0x1f) && (ptr[ptr_idx] < 0x7f))
    {
      size += 1;
      screen_write_putc(ctx, &gc, *(&ptr[ptr_idx]));
    }
    ptr_idx += 1;
  }
  *gc_ref = gc;
  *ptr_idx_ref = ptr_idx;
  *left_ref = left;
  *size_ref = size;
  *more_ref = more;
}


----------------------------
None
----------------------------
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
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
enum utf8_state
{
  UTF8_MORE,
  UTF8_DONE,
  UTF8_ERROR
}
----------------------------
None
----------------------------
None
----------------------------
***/


void screen_write_fast_copy(struct screen_write_ctx *ctx, struct screen *src, u_int px, u_int py, u_int nx, u_int ny)
{
  struct screen *s = ctx->s;
  struct grid *gd = src->grid;
  struct grid_cell gc;
  u_int xx;
  u_int yy;
  u_int cx;
  u_int cy;
  if ((nx == 0) || (ny == 0))
  {
    return;
  }
  cy = s->cy;
  for (yy = py; yy < (py + ny); yy += 1)
  {
    if (yy >= (gd->hsize + gd->sy))
    {
      break;
    }
    cx = s->cx;
    for (xx = px; xx < (px + nx); xx += 1)
    {
      if (xx >= gd->linedata[yy].cellsize)
      {
        break;
      }
      grid_get_cell(gd, xx, yy, &gc);
      if ((xx + gc.data.width) > (px + nx))
      {
        break;
      }
      if (!grid_cells_equal(&gc, &grid_default_cell))
      {
        grid_view_set_cell(ctx->s->grid, cx, cy, &gc);
      }
      cx += 1;
    }

    cy += 1;
  }

}


/*** DEPENDENCIES:
extern const struct grid_cell grid_default_cell
----------------------------
void grid_get_cell(struct grid *gd, u_int px, u_int py, struct grid_cell *gc)
{
  if ((grid_check_y(gd, __func__, py) != 0) || (px >= gd->linedata[py].cellsize))
  {
    memcpy(gc, &grid_default_cell, sizeof(*gc));
    return;
  }
  return grid_get_cell1(&gd->linedata[py], px, gc);
}


----------------------------
void grid_view_set_cell(struct grid *gd, u_int px, u_int py, const struct grid_cell *gc)
{
  grid_set_cell(gd, px, gd->hsize + py, gc);
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
int grid_cells_equal(const struct grid_cell *gca, const struct grid_cell *gcb)
{
  if ((gca->fg != gcb->fg) || (gca->bg != gcb->bg))
  {
    return 0;
  }
  if ((gca->attr != gcb->attr) || (gca->flags != gcb->flags))
  {
    return 0;
  }
  if (gca->data.width != gcb->data.width)
  {
    return 0;
  }
  if (gca->data.size != gcb->data.size)
  {
    return 0;
  }
  return memcmp(gca->data.data, gcb->data.data, gca->data.size) == 0;
}


----------------------------
None
----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
static void screen_write_collect_flush(struct screen_write_ctx *ctx, int scroll_only)
{
  struct screen *s = ctx->s;
  struct screen_write_collect_item *ci;
  unsigned int ci_idx = 0;
  struct screen_write_collect_item *tmp;
  unsigned int tmp_idx = 0;
  u_int y;
  u_int cx;
  u_int cy;
  u_int items = 0;
  struct tty_ctx ttyctx;
  size_t written = 0;
  if (ctx->scrolled != 0)
  {
    log_debug("%s: scrolled %u (region %u-%u)", __func__, ctx->scrolled, s->rupper, s->rlower);
    if (ctx->scrolled > ((s->rlower - s->rupper) + 1))
    {
      ctx->scrolled = (s->rlower - s->rupper) + 1;
    }
    screen_write_initctx(ctx, &ttyctx);
    ttyctx.num = ctx->scrolled;
    ttyctx.bg = ctx->bg;
    tty_write(tty_cmd_scrollup, &ttyctx);
  }
  ctx->scrolled = 0;
  ctx->bg = 8;
  if (scroll_only)
  {
    return;
  }
  cx = s->cx;
  cy = s->cy;
  for (y = 0; y < s->grid->sy; y += 1)
  {
    helper_screen_write_collect_flush_1(&ci_idx, &tmp_idx, &y, &items, &ttyctx, &written, ctx, ci, tmp);
  }

  s->cx = cx;
  s->cy = cy;
  log_debug("%s: flushed %u items (%zu bytes)", __func__, items, written);
  ctx->written += written;
}


----------------------------
None
----------------------------
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void screen_write_initctx(struct screen_write_ctx *ctx, struct tty_ctx *ttyctx)
{
  struct screen *s = ctx->s;
  memset(ttyctx, 0, sizeof(*ttyctx));
  ttyctx->wp = ctx->wp;
  ttyctx->ocx = s->cx;
  ttyctx->ocy = s->cy;
  ttyctx->orlower = s->rlower;
  ttyctx->orupper = s->rupper;
}


----------------------------
void tty_write(void (*cmdfn)(struct tty *, const struct tty_ctx *), struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  struct client *c;
  unsigned int c_idx = 0;
  if (wp == 0)
  {
    return;
  }
  if ((wp->flags & (0x1 | 0x2)) || (!window_pane_visible(wp)))
  {
    return;
  }
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (!tty_client_ready(c, wp))
    {
      continue;
    }
    ctx->xoff = wp->xoff;
    ctx->yoff = wp->yoff;
    if (status_at_line(c) == 0)
    {
      ctx->yoff += status_line_size(c->session);
    }
    cmdfn(&c->tty, ctx);
  }

}


----------------------------
void tty_cmd_clearline(struct tty *tty, const struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  u_int nx;
  u_int py = ctx->yoff + ctx->ocy;
  tty_default_attributes(tty, wp, ctx->bg);
  nx = wp->screen->grid->sx;
  tty_clear_line(tty, wp, py, ctx->xoff, nx, ctx->bg);
}


----------------------------
static void screen_write_collect_clear(struct screen_write_ctx *ctx, u_int y, u_int n)
{
  struct screen_write_collect_item *ci;
  unsigned int ci_idx = 0;
  struct screen_write_collect_item *tmp;
  unsigned int tmp_idx = 0;
  u_int i;
  size_t size;
  for (i = y; i < (y + n); i += 1)
  {
    if ((&ctx->list[i].items)->tqh_first == 0)
    {
      continue;
    }
    size = 0;
    for (ci_idx = (&ctx->list[i].items)->tqh_first; ((&ci[ci_idx]) != 0) && ((tmp_idx = ci->entry.tqe_next, 1)); ci_idx = &tmp[tmp_idx])
    {
      size += ci->used;
      do
      {
        if (ci->entry.tqe_next != 0)
        {
          ci->entry.tqe_next->entry.tqe_prev = ci->entry.tqe_prev;
        }
        else
          (&ctx->list[i].items)->tqh_last = ci->entry.tqe_prev;
        *ci->entry.tqe_prev = ci->entry.tqe_next;
        ;
        ;
      }
      while (0);
      free(ci);
    }

    ctx->skipped += size;
    log_debug("%s: dropped %zu bytes (line %u)", __func__, size, i);
  }

}


----------------------------
None
----------------------------
void grid_view_clear(struct grid *gd, u_int px, u_int py, u_int nx, u_int ny, u_int bg)
{
  px = px;
  py = gd->hsize + py;
  grid_clear(gd, px, py, nx, ny, bg);
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
None
----------------------------
static void screen_write_collect_flush(struct screen_write_ctx *ctx, int scroll_only)
{
  struct screen *s = ctx->s;
  struct screen_write_collect_item *ci;
  unsigned int ci_idx = 0;
  struct screen_write_collect_item *tmp;
  unsigned int tmp_idx = 0;
  u_int y;
  u_int cx;
  u_int cy;
  u_int items = 0;
  struct tty_ctx ttyctx;
  size_t written = 0;
  if (ctx->scrolled != 0)
  {
    log_debug("%s: scrolled %u (region %u-%u)", __func__, ctx->scrolled, s->rupper, s->rlower);
    if (ctx->scrolled > ((s->rlower - s->rupper) + 1))
    {
      ctx->scrolled = (s->rlower - s->rupper) + 1;
    }
    screen_write_initctx(ctx, &ttyctx);
    ttyctx.num = ctx->scrolled;
    ttyctx.bg = ctx->bg;
    tty_write(tty_cmd_scrollup, &ttyctx);
  }
  ctx->scrolled = 0;
  ctx->bg = 8;
  if (scroll_only)
  {
    return;
  }
  cx = s->cx;
  cy = s->cy;
  for (y = 0; y < s->grid->sy; y += 1)
  {
    helper_screen_write_collect_flush_1(&ci_idx, &tmp_idx, &y, &items, &ttyctx, &written, ctx, ci, tmp);
  }

  s->cx = cx;
  s->cy = cy;
  log_debug("%s: flushed %u items (%zu bytes)", __func__, items, written);
  ctx->written += written;
}


----------------------------
None
----------------------------
***/


void screen_write_copy(struct screen_write_ctx *ctx, struct screen *src, u_int px, u_int py, u_int nx, u_int ny, bitstr_t *mbs, const struct grid_cell *mgc)
{
  struct screen *s = ctx->s;
  struct grid *gd = src->grid;
  struct grid_cell gc;
  u_int xx;
  u_int yy;
  u_int cx;
  u_int cy;
  u_int b;
  if ((nx == 0) || (ny == 0))
  {
    return;
  }
  cx = s->cx;
  cy = s->cy;
  for (yy = py; yy < (py + ny); yy += 1)
  {
    for (xx = px; xx < (px + nx); xx += 1)
    {
      grid_get_cell(gd, xx, yy, &gc);
      if (mbs != 0)
      {
        b = (yy * src->grid->sx) + xx;
        if (mbs[b >> 3] & (1 << (b & 0x7)))
        {
          gc.attr = mgc->attr;
          gc.fg = mgc->fg;
          gc.bg = mgc->bg;
        }
      }
      if ((xx + gc.data.width) <= (px + nx))
      {
        screen_write_cell(ctx, &gc);
      }
    }

    cy += 1;
    screen_write_cursormove(ctx, cx, cy);
  }

}


/*** DEPENDENCIES:
typedef unsigned char bitstr_t
----------------------------
void grid_get_cell(struct grid *gd, u_int px, u_int py, struct grid_cell *gc)
{
  if ((grid_check_y(gd, __func__, py) != 0) || (px >= gd->linedata[py].cellsize))
  {
    memcpy(gc, &grid_default_cell, sizeof(*gc));
    return;
  }
  return grid_get_cell1(&gd->linedata[py], px, gc);
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
None
----------------------------
void screen_write_cell(struct screen_write_ctx *ctx, const struct grid_cell *gc)
{
  unsigned int gc_idx = 0;
  struct screen *s = ctx->s;
  struct grid *gd = s->grid;
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  struct grid_cell_entry *gce;
  unsigned int gce_idx = 0;
  struct grid_cell tmp_gc;
  struct grid_cell now_gc;
  struct tty_ctx ttyctx;
  u_int sx = s->grid->sx;
  u_int sy = s->grid->sy;
  u_int width = gc->data.width;
  u_int xx;
  u_int last;
  u_int cx;
  u_int cy;
  int selected;
  int skip = 1;
  if (gc->flags & 0x4)
  {
    return;
  }
  ctx->cells += 1;
  if (width == 0)
  {
    helper_screen_write_cell_1(&gc_idx, &ttyctx, &cx, &cy, ctx, gc, s, xx);
  }
  screen_write_collect_flush(ctx, 1);
  if ((((~s->mode) & 0x10) && (width > 1)) && ((width > sx) || ((s->cx != sx) && (s->cx > (sx - width)))))
  {
    return;
  }
  if (s->mode & 0x2)
  {
    grid_view_insert_cells(s->grid, s->cx, s->cy, width, 8);
    skip = 0;
  }
  if ((s->mode & 0x10) && (s->cx > (sx - width)))
  {
    log_debug("%s: wrapped at %u,%u", __func__, s->cx, s->cy);
    screen_write_linefeed(ctx, 1, 8);
    s->cx = 0;
    screen_write_collect_flush(ctx, 1);
  }
  if ((s->cx > (sx - width)) || (s->cy > (sy - 1)))
  {
    return;
  }
  screen_write_initctx(ctx, &ttyctx);
  gl_idx = &s->grid->linedata[s->grid->hsize + s->cy];
  if (gl->flags & 0x2)
  {
    grid_view_get_cell(gd, s->cx, s->cy, &now_gc);
    if (screen_write_overwrite(ctx, &now_gc, width))
    {
      skip = 0;
    }
  }
  for (xx = s->cx + 1; xx < (s->cx + width); xx += 1)
  {
    log_debug("%s: new padding at %u,%u", __func__, xx, s->cy);
    grid_view_set_cell(gd, xx, s->cy, &screen_write_pad_cell);
    skip = 0;
  }

  if (skip)
  {
    helper_screen_write_cell_2(&gce_idx, &skip, gc, s, gl, gce);
  }
  selected = screen_check_selection(s, s->cx, s->cy);
  if (selected && ((~gc->flags) & 0x10))
  {
    memcpy(&tmp_gc, gc, sizeof(tmp_gc));
    tmp_gc.flags |= 0x10;
    grid_view_set_cell(gd, s->cx, s->cy, &tmp_gc);
  }
  else
    if ((!selected) && (gc->flags & 0x10))
  {
    memcpy(&tmp_gc, gc, sizeof(tmp_gc));
    tmp_gc.flags &= ~0x10;
    grid_view_set_cell(gd, s->cx, s->cy, &tmp_gc);
  }
  else
    if (!skip)
  {
    grid_view_set_cell(gd, s->cx, s->cy, gc);
  }
  if (selected)
  {
    skip = 0;
  }
  last = !(s->mode & 0x10);
  if (s->cx <= ((sx - last) - width))
  {
    s->cx += width;
  }
  else
    s->cx = sx - last;
  if (s->mode & 0x2)
  {
    screen_write_collect_flush(ctx, 0);
    ttyctx.num = width;
    tty_write(tty_cmd_insertcharacter, &ttyctx);
  }
  if (!skip)
  {
    if (selected)
    {
      screen_select_cell(s, &tmp_gc, gc);
      ttyctx.cell = &tmp_gc;
    }
    else
      ttyctx.cell = &gc[gc_idx];
    tty_write(tty_cmd_cell, &ttyctx);
    ctx->written += 1;
  }
  else
    ctx->skipped++;
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
None
----------------------------
***/


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
static void screen_write_collect_flush(struct screen_write_ctx *ctx, int scroll_only)
{
  struct screen *s = ctx->s;
  struct screen_write_collect_item *ci;
  unsigned int ci_idx = 0;
  struct screen_write_collect_item *tmp;
  unsigned int tmp_idx = 0;
  u_int y;
  u_int cx;
  u_int cy;
  u_int items = 0;
  struct tty_ctx ttyctx;
  size_t written = 0;
  if (ctx->scrolled != 0)
  {
    log_debug("%s: scrolled %u (region %u-%u)", __func__, ctx->scrolled, s->rupper, s->rlower);
    if (ctx->scrolled > ((s->rlower - s->rupper) + 1))
    {
      ctx->scrolled = (s->rlower - s->rupper) + 1;
    }
    screen_write_initctx(ctx, &ttyctx);
    ttyctx.num = ctx->scrolled;
    ttyctx.bg = ctx->bg;
    tty_write(tty_cmd_scrollup, &ttyctx);
  }
  ctx->scrolled = 0;
  ctx->bg = 8;
  if (scroll_only)
  {
    return;
  }
  cx = s->cx;
  cy = s->cy;
  for (y = 0; y < s->grid->sy; y += 1)
  {
    helper_screen_write_collect_flush_1(&ci_idx, &tmp_idx, &y, &items, &ttyctx, &written, ctx, ci, tmp);
  }

  s->cx = cx;
  s->cy = cy;
  log_debug("%s: flushed %u items (%zu bytes)", __func__, items, written);
  ctx->written += written;
}


----------------------------
None
----------------------------
struct screen_write_collect_item
{
  u_int x;
  int wrapped;
  u_int used;
  char data[256];
  struct grid_cell gc;
  struct 
  {
    struct screen_write_collect_item *tqe_next;
    struct screen_write_collect_item **tqe_prev;
  } entry;
}
----------------------------
void screen_write_cell(struct screen_write_ctx *ctx, const struct grid_cell *gc)
{
  unsigned int gc_idx = 0;
  struct screen *s = ctx->s;
  struct grid *gd = s->grid;
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  struct grid_cell_entry *gce;
  unsigned int gce_idx = 0;
  struct grid_cell tmp_gc;
  struct grid_cell now_gc;
  struct tty_ctx ttyctx;
  u_int sx = s->grid->sx;
  u_int sy = s->grid->sy;
  u_int width = gc->data.width;
  u_int xx;
  u_int last;
  u_int cx;
  u_int cy;
  int selected;
  int skip = 1;
  if (gc->flags & 0x4)
  {
    return;
  }
  ctx->cells += 1;
  if (width == 0)
  {
    helper_screen_write_cell_1(&gc_idx, &ttyctx, &cx, &cy, ctx, gc, s, xx);
  }
  screen_write_collect_flush(ctx, 1);
  if ((((~s->mode) & 0x10) && (width > 1)) && ((width > sx) || ((s->cx != sx) && (s->cx > (sx - width)))))
  {
    return;
  }
  if (s->mode & 0x2)
  {
    grid_view_insert_cells(s->grid, s->cx, s->cy, width, 8);
    skip = 0;
  }
  if ((s->mode & 0x10) && (s->cx > (sx - width)))
  {
    log_debug("%s: wrapped at %u,%u", __func__, s->cx, s->cy);
    screen_write_linefeed(ctx, 1, 8);
    s->cx = 0;
    screen_write_collect_flush(ctx, 1);
  }
  if ((s->cx > (sx - width)) || (s->cy > (sy - 1)))
  {
    return;
  }
  screen_write_initctx(ctx, &ttyctx);
  gl_idx = &s->grid->linedata[s->grid->hsize + s->cy];
  if (gl->flags & 0x2)
  {
    grid_view_get_cell(gd, s->cx, s->cy, &now_gc);
    if (screen_write_overwrite(ctx, &now_gc, width))
    {
      skip = 0;
    }
  }
  for (xx = s->cx + 1; xx < (s->cx + width); xx += 1)
  {
    log_debug("%s: new padding at %u,%u", __func__, xx, s->cy);
    grid_view_set_cell(gd, xx, s->cy, &screen_write_pad_cell);
    skip = 0;
  }

  if (skip)
  {
    helper_screen_write_cell_2(&gce_idx, &skip, gc, s, gl, gce);
  }
  selected = screen_check_selection(s, s->cx, s->cy);
  if (selected && ((~gc->flags) & 0x10))
  {
    memcpy(&tmp_gc, gc, sizeof(tmp_gc));
    tmp_gc.flags |= 0x10;
    grid_view_set_cell(gd, s->cx, s->cy, &tmp_gc);
  }
  else
    if ((!selected) && (gc->flags & 0x10))
  {
    memcpy(&tmp_gc, gc, sizeof(tmp_gc));
    tmp_gc.flags &= ~0x10;
    grid_view_set_cell(gd, s->cx, s->cy, &tmp_gc);
  }
  else
    if (!skip)
  {
    grid_view_set_cell(gd, s->cx, s->cy, gc);
  }
  if (selected)
  {
    skip = 0;
  }
  last = !(s->mode & 0x10);
  if (s->cx <= ((sx - last) - width))
  {
    s->cx += width;
  }
  else
    s->cx = sx - last;
  if (s->mode & 0x2)
  {
    screen_write_collect_flush(ctx, 0);
    ttyctx.num = width;
    tty_write(tty_cmd_insertcharacter, &ttyctx);
  }
  if (!skip)
  {
    if (selected)
    {
      screen_select_cell(s, &tmp_gc, gc);
      ttyctx.cell = &tmp_gc;
    }
    else
      ttyctx.cell = &gc[gc_idx];
    tty_write(tty_cmd_cell, &ttyctx);
    ctx->written += 1;
  }
  else
    ctx->skipped++;
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


void screen_write_rawstring(struct screen_write_ctx *ctx, u_char *str, u_int len)
{
  struct tty_ctx ttyctx;
  screen_write_initctx(ctx, &ttyctx);
  ttyctx.ptr = str;
  ttyctx.num = len;
  tty_write(tty_cmd_rawstring, &ttyctx);
}


/*** DEPENDENCIES:
void tty_cmd_rawstring(struct tty *tty, const struct tty_ctx *ctx)
{
  tty_add(tty, ctx->ptr, ctx->num);
  tty_invalidate(tty);
}


----------------------------
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void screen_write_initctx(struct screen_write_ctx *ctx, struct tty_ctx *ttyctx)
{
  struct screen *s = ctx->s;
  memset(ttyctx, 0, sizeof(*ttyctx));
  ttyctx->wp = ctx->wp;
  ttyctx->ocx = s->cx;
  ttyctx->ocy = s->cy;
  ttyctx->orlower = s->rlower;
  ttyctx->orupper = s->rupper;
}


----------------------------
void tty_write(void (*cmdfn)(struct tty *, const struct tty_ctx *), struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  struct client *c;
  unsigned int c_idx = 0;
  if (wp == 0)
  {
    return;
  }
  if ((wp->flags & (0x1 | 0x2)) || (!window_pane_visible(wp)))
  {
    return;
  }
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (!tty_client_ready(c, wp))
    {
      continue;
    }
    ctx->xoff = wp->xoff;
    ctx->yoff = wp->yoff;
    if (status_at_line(c) == 0)
    {
      ctx->yoff += status_line_size(c->session);
    }
    cmdfn(&c->tty, ctx);
  }

}


----------------------------
None
----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
void grid_view_clear_history(struct grid *gd, u_int bg)
{
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  u_int yy;
  u_int last;
  last = 0;
  for (yy = 0; yy < gd->sy; yy += 1)
  {
    gl_idx = &gd->linedata[gd->hsize + yy];
    if (gl->cellused != 0)
    {
      last = yy + 1;
    }
  }

  if (last == 0)
  {
    grid_view_clear(gd, 0, 0, gd->sx, gd->sy, bg);
    return;
  }
  for (yy = 0; yy < last; yy += 1)
  {
    grid_collect_history(gd);
    grid_scroll_history(gd, bg);
  }

  if (last < gd->sy)
  {
    grid_view_clear(gd, 0, 0, gd->sx, gd->sy - last, bg);
  }
  gd->hscrolled = 0;
}


----------------------------
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void screen_write_initctx(struct screen_write_ctx *ctx, struct tty_ctx *ttyctx)
{
  struct screen *s = ctx->s;
  memset(ttyctx, 0, sizeof(*ttyctx));
  ttyctx->wp = ctx->wp;
  ttyctx->ocx = s->cx;
  ttyctx->ocy = s->cy;
  ttyctx->orlower = s->rlower;
  ttyctx->orupper = s->rupper;
}


----------------------------
void tty_write(void (*cmdfn)(struct tty *, const struct tty_ctx *), struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  struct client *c;
  unsigned int c_idx = 0;
  if (wp == 0)
  {
    return;
  }
  if ((wp->flags & (0x1 | 0x2)) || (!window_pane_visible(wp)))
  {
    return;
  }
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (!tty_client_ready(c, wp))
    {
      continue;
    }
    ctx->xoff = wp->xoff;
    ctx->yoff = wp->yoff;
    if (status_at_line(c) == 0)
    {
      ctx->yoff += status_line_size(c->session);
    }
    cmdfn(&c->tty, ctx);
  }

}


----------------------------
void tty_cmd_clearscreen(struct tty *tty, const struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  u_int px;
  u_int py;
  u_int nx;
  u_int ny;
  tty_default_attributes(tty, wp, ctx->bg);
  tty_region_pane(tty, ctx, 0, wp->screen->grid->sy - 1);
  tty_margin_off(tty);
  px = ctx->xoff;
  nx = wp->screen->grid->sx;
  py = ctx->yoff;
  ny = wp->screen->grid->sy;
  tty_clear_area(tty, wp, py, ny, px, nx, ctx->bg);
}


----------------------------
static void screen_write_collect_clear(struct screen_write_ctx *ctx, u_int y, u_int n)
{
  struct screen_write_collect_item *ci;
  unsigned int ci_idx = 0;
  struct screen_write_collect_item *tmp;
  unsigned int tmp_idx = 0;
  u_int i;
  size_t size;
  for (i = y; i < (y + n); i += 1)
  {
    if ((&ctx->list[i].items)->tqh_first == 0)
    {
      continue;
    }
    size = 0;
    for (ci_idx = (&ctx->list[i].items)->tqh_first; ((&ci[ci_idx]) != 0) && ((tmp_idx = ci->entry.tqe_next, 1)); ci_idx = &tmp[tmp_idx])
    {
      size += ci->used;
      do
      {
        if (ci->entry.tqe_next != 0)
        {
          ci->entry.tqe_next->entry.tqe_prev = ci->entry.tqe_prev;
        }
        else
          (&ctx->list[i].items)->tqh_last = ci->entry.tqe_prev;
        *ci->entry.tqe_prev = ci->entry.tqe_next;
        ;
        ;
      }
      while (0);
      free(ci);
    }

    ctx->skipped += size;
    log_debug("%s: dropped %zu bytes (line %u)", __func__, size, i);
  }

}


----------------------------
None
----------------------------
void grid_view_clear(struct grid *gd, u_int px, u_int py, u_int nx, u_int ny, u_int bg)
{
  px = px;
  py = gd->hsize + py;
  grid_clear(gd, px, py, nx, ny, bg);
}


----------------------------
None
----------------------------
***/


void screen_write_box(struct screen_write_ctx *ctx, u_int nx, u_int ny)
{
  struct screen *s = ctx->s;
  struct grid_cell gc;
  u_int cx;
  u_int cy;
  u_int i;
  cx = s->cx;
  cy = s->cy;
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  gc.attr |= 0x80;
  screen_write_putc(ctx, &gc, 'l');
  for (i = 1; i < (nx - 1); i += 1)
  {
    screen_write_putc(ctx, &gc, 'q');
  }

  screen_write_putc(ctx, &gc, 'k');
  screen_write_cursormove(ctx, cx, (cy + ny) - 1);
  screen_write_putc(ctx, &gc, 'm');
  for (i = 1; i < (nx - 1); i += 1)
  {
    screen_write_putc(ctx, &gc, 'q');
  }

  screen_write_putc(ctx, &gc, 'j');
  for (i = 1; i < (ny - 1); i += 1)
  {
    screen_write_cursormove(ctx, cx, cy + i);
    screen_write_putc(ctx, &gc, 'x');
  }

  for (i = 1; i < (ny - 1); i += 1)
  {
    screen_write_cursormove(ctx, (cx + nx) - 1, cy + i);
    screen_write_putc(ctx, &gc, 'x');
  }

  screen_write_cursormove(ctx, cx, cy);
}


/*** DEPENDENCIES:
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


/*** DEPENDENCIES:
static void screen_write_collect_flush(struct screen_write_ctx *ctx, int scroll_only)
{
  struct screen *s = ctx->s;
  struct screen_write_collect_item *ci;
  unsigned int ci_idx = 0;
  struct screen_write_collect_item *tmp;
  unsigned int tmp_idx = 0;
  u_int y;
  u_int cx;
  u_int cy;
  u_int items = 0;
  struct tty_ctx ttyctx;
  size_t written = 0;
  if (ctx->scrolled != 0)
  {
    log_debug("%s: scrolled %u (region %u-%u)", __func__, ctx->scrolled, s->rupper, s->rlower);
    if (ctx->scrolled > ((s->rlower - s->rupper) + 1))
    {
      ctx->scrolled = (s->rlower - s->rupper) + 1;
    }
    screen_write_initctx(ctx, &ttyctx);
    ttyctx.num = ctx->scrolled;
    ttyctx.bg = ctx->bg;
    tty_write(tty_cmd_scrollup, &ttyctx);
  }
  ctx->scrolled = 0;
  ctx->bg = 8;
  if (scroll_only)
  {
    return;
  }
  cx = s->cx;
  cy = s->cy;
  for (y = 0; y < s->grid->sy; y += 1)
  {
    helper_screen_write_collect_flush_1(&ci_idx, &tmp_idx, &y, &items, &ttyctx, &written, ctx, ci, tmp);
  }

  s->cx = cx;
  s->cy = cy;
  log_debug("%s: flushed %u items (%zu bytes)", __func__, items, written);
  ctx->written += written;
}


----------------------------
None
----------------------------
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void screen_write_initctx(struct screen_write_ctx *ctx, struct tty_ctx *ttyctx)
{
  struct screen *s = ctx->s;
  memset(ttyctx, 0, sizeof(*ttyctx));
  ttyctx->wp = ctx->wp;
  ttyctx->ocx = s->cx;
  ttyctx->ocy = s->cy;
  ttyctx->orlower = s->rlower;
  ttyctx->orupper = s->rupper;
}


----------------------------
void tty_cmd_clearendofline(struct tty *tty, const struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  u_int nx;
  u_int py = ctx->yoff + ctx->ocy;
  tty_default_attributes(tty, wp, ctx->bg);
  nx = wp->screen->grid->sx - ctx->ocx;
  tty_clear_line(tty, wp, py, ctx->xoff + ctx->ocx, nx, ctx->bg);
}


----------------------------
void tty_write(void (*cmdfn)(struct tty *, const struct tty_ctx *), struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  struct client *c;
  unsigned int c_idx = 0;
  if (wp == 0)
  {
    return;
  }
  if ((wp->flags & (0x1 | 0x2)) || (!window_pane_visible(wp)))
  {
    return;
  }
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (!tty_client_ready(c, wp))
    {
      continue;
    }
    ctx->xoff = wp->xoff;
    ctx->yoff = wp->yoff;
    if (status_at_line(c) == 0)
    {
      ctx->yoff += status_line_size(c->session);
    }
    cmdfn(&c->tty, ctx);
  }

}


----------------------------
static void screen_write_collect_clear(struct screen_write_ctx *ctx, u_int y, u_int n)
{
  struct screen_write_collect_item *ci;
  unsigned int ci_idx = 0;
  struct screen_write_collect_item *tmp;
  unsigned int tmp_idx = 0;
  u_int i;
  size_t size;
  for (i = y; i < (y + n); i += 1)
  {
    if ((&ctx->list[i].items)->tqh_first == 0)
    {
      continue;
    }
    size = 0;
    for (ci_idx = (&ctx->list[i].items)->tqh_first; ((&ci[ci_idx]) != 0) && ((tmp_idx = ci->entry.tqe_next, 1)); ci_idx = &tmp[tmp_idx])
    {
      size += ci->used;
      do
      {
        if (ci->entry.tqe_next != 0)
        {
          ci->entry.tqe_next->entry.tqe_prev = ci->entry.tqe_prev;
        }
        else
          (&ctx->list[i].items)->tqh_last = ci->entry.tqe_prev;
        *ci->entry.tqe_prev = ci->entry.tqe_next;
        ;
        ;
      }
      while (0);
      free(ci);
    }

    ctx->skipped += size;
    log_debug("%s: dropped %zu bytes (line %u)", __func__, size, i);
  }

}


----------------------------
None
----------------------------
void grid_view_clear(struct grid *gd, u_int px, u_int py, u_int nx, u_int ny, u_int bg)
{
  px = px;
  py = gd->hsize + py;
  grid_clear(gd, px, py, nx, ny, bg);
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
None
----------------------------
***/


void screen_write_clearhistory(struct screen_write_ctx *ctx)
{
  struct screen *s = ctx->s;
  struct grid *gd = s->grid;
  grid_move_lines(gd, 0, gd->hsize, gd->sy, 8);
  gd->hscrolled = (gd->hsize = 0);
}


/*** DEPENDENCIES:
void grid_move_lines(struct grid *gd, u_int dy, u_int py, u_int ny, u_int bg)
{
  u_int yy;
  if ((ny == 0) || (py == dy))
  {
    return;
  }
  if (grid_check_y(gd, __func__, py) != 0)
  {
    return;
  }
  if (grid_check_y(gd, __func__, (py + ny) - 1) != 0)
  {
    return;
  }
  if (grid_check_y(gd, __func__, dy) != 0)
  {
    return;
  }
  if (grid_check_y(gd, __func__, (dy + ny) - 1) != 0)
  {
    return;
  }
  for (yy = dy; yy < (dy + ny); yy += 1)
  {
    if ((yy >= py) && (yy < (py + ny)))
    {
      continue;
    }
    grid_free_line(gd, yy);
  }

  memmove(&gd->linedata[dy], &gd->linedata[py], ny * (sizeof(*gd->linedata)));
  for (yy = py; yy < (py + ny); yy += 1)
  {
    if ((yy < dy) || (yy >= (dy + ny)))
    {
      grid_empty_line(gd, yy, bg);
    }
  }

}


----------------------------
None
----------------------------
None
----------------------------
None
----------------------------
***/


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
void screen_reset_tabs(struct screen *s)
{
  u_int i;
  free(s->tabs);
  if ((s->tabs = (bitstr_t *) calloc((size_t) ((s->grid->sx + 7) >> 3), sizeof(bitstr_t))) == 0)
  {
    fatal("bit_alloc failed");
  }
  for (i = 8; i < s->grid->sx; i += 8)
  {
    s->tabs[i >> 3] |= 1 << (i & 0x7);
  }

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


/*** DEPENDENCIES:
static void screen_write_collect_scroll(struct screen_write_ctx *ctx)
{
  struct screen *s = ctx->s;
  struct screen_write_collect_line *cl;
  unsigned int cl_idx = 0;
  u_int y;
  log_debug("%s: at %u,%u (region %u-%u)", __func__, s->cx, s->cy, s->rupper, s->rlower);
  screen_write_collect_clear(ctx, s->rupper, 1);
  for (y = s->rupper; y < s->rlower; y += 1)
  {
    cl_idx = &ctx->list[y + 1];
    do
    {
      if (!((&cl->items)->tqh_first == 0))
      {
        *(&ctx->list[y].items)->tqh_last = (&cl->items)->tqh_first;
        (&cl->items)->tqh_first->entry.tqe_prev = (&ctx->list[y].items)->tqh_last;
        (&ctx->list[y].items)->tqh_last = (&cl->items)->tqh_last;
        do
        {
          (&cl->items)->tqh_first = 0;
          (&cl->items)->tqh_last = &(&cl->items)->tqh_first;
        }
        while (0);
      }
    }
    while (0);
    do
    {
      (&cl->items)->tqh_first = 0;
      (&cl->items)->tqh_last = &(&cl->items)->tqh_first;
    }
    while (0);
  }

}


----------------------------
static void screen_write_collect_flush(struct screen_write_ctx *ctx, int scroll_only)
{
  struct screen *s = ctx->s;
  struct screen_write_collect_item *ci;
  unsigned int ci_idx = 0;
  struct screen_write_collect_item *tmp;
  unsigned int tmp_idx = 0;
  u_int y;
  u_int cx;
  u_int cy;
  u_int items = 0;
  struct tty_ctx ttyctx;
  size_t written = 0;
  if (ctx->scrolled != 0)
  {
    log_debug("%s: scrolled %u (region %u-%u)", __func__, ctx->scrolled, s->rupper, s->rlower);
    if (ctx->scrolled > ((s->rlower - s->rupper) + 1))
    {
      ctx->scrolled = (s->rlower - s->rupper) + 1;
    }
    screen_write_initctx(ctx, &ttyctx);
    ttyctx.num = ctx->scrolled;
    ttyctx.bg = ctx->bg;
    tty_write(tty_cmd_scrollup, &ttyctx);
  }
  ctx->scrolled = 0;
  ctx->bg = 8;
  if (scroll_only)
  {
    return;
  }
  cx = s->cx;
  cy = s->cy;
  for (y = 0; y < s->grid->sy; y += 1)
  {
    helper_screen_write_collect_flush_1(&ci_idx, &tmp_idx, &y, &items, &ttyctx, &written, ctx, ci, tmp);
  }

  s->cx = cx;
  s->cy = cy;
  log_debug("%s: flushed %u items (%zu bytes)", __func__, items, written);
  ctx->written += written;
}


----------------------------
None
----------------------------
void grid_view_scroll_region_up(struct grid *gd, u_int rupper, u_int rlower, u_int bg)
{
  if (gd->flags & 0x1)
  {
    grid_collect_history(gd);
    if ((rupper == 0) && (rlower == (gd->sy - 1)))
    {
      grid_scroll_history(gd, bg);
    }
    else
    {
      rupper = gd->hsize + rupper;
      rlower = gd->hsize + rlower;
      grid_scroll_history_region(gd, rupper, rlower, bg);
    }
  }
  else
  {
    rupper = gd->hsize + rupper;
    rlower = gd->hsize + rlower;
    grid_move_lines(gd, rupper, rupper + 1, rlower - rupper, bg);
  }
}


----------------------------
None
----------------------------
None
----------------------------
***/


void screen_write_hline(struct screen_write_ctx *ctx, u_int nx, int left, int right)
{
  struct screen *s = ctx->s;
  struct grid_cell gc;
  u_int cx;
  u_int cy;
  u_int i;
  cx = s->cx;
  cy = s->cy;
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  gc.attr |= 0x80;
  screen_write_putc(ctx, &gc, (left) ? ('t') : ('q'));
  for (i = 1; i < (nx - 1); i += 1)
  {
    screen_write_putc(ctx, &gc, 'q');
  }

  screen_write_putc(ctx, &gc, (right) ? ('u') : ('q'));
  screen_write_cursormove(ctx, cx, cy);
}


/*** DEPENDENCIES:
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


void screen_write_vline(struct screen_write_ctx *ctx, u_int ny, int top, int bottom)
{
  struct screen *s = ctx->s;
  struct grid_cell gc;
  u_int cx;
  u_int cy;
  u_int i;
  cx = s->cx;
  cy = s->cy;
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  gc.attr |= 0x80;
  screen_write_putc(ctx, &gc, (top) ? ('w') : ('x'));
  for (i = 1; i < (ny - 1); i += 1)
  {
    screen_write_cursormove(ctx, cx, cy + i);
    screen_write_putc(ctx, &gc, 'x');
  }

  screen_write_cursormove(ctx, cx, (cy + ny) - 1);
  screen_write_putc(ctx, &gc, (bottom) ? ('v') : ('x'));
  screen_write_cursormove(ctx, cx, cy);
}


/*** DEPENDENCIES:
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


/*** DEPENDENCIES:
static void screen_write_collect_flush(struct screen_write_ctx *ctx, int scroll_only)
{
  struct screen *s = ctx->s;
  struct screen_write_collect_item *ci;
  unsigned int ci_idx = 0;
  struct screen_write_collect_item *tmp;
  unsigned int tmp_idx = 0;
  u_int y;
  u_int cx;
  u_int cy;
  u_int items = 0;
  struct tty_ctx ttyctx;
  size_t written = 0;
  if (ctx->scrolled != 0)
  {
    log_debug("%s: scrolled %u (region %u-%u)", __func__, ctx->scrolled, s->rupper, s->rlower);
    if (ctx->scrolled > ((s->rlower - s->rupper) + 1))
    {
      ctx->scrolled = (s->rlower - s->rupper) + 1;
    }
    screen_write_initctx(ctx, &ttyctx);
    ttyctx.num = ctx->scrolled;
    ttyctx.bg = ctx->bg;
    tty_write(tty_cmd_scrollup, &ttyctx);
  }
  ctx->scrolled = 0;
  ctx->bg = 8;
  if (scroll_only)
  {
    return;
  }
  cx = s->cx;
  cy = s->cy;
  for (y = 0; y < s->grid->sy; y += 1)
  {
    helper_screen_write_collect_flush_1(&ci_idx, &tmp_idx, &y, &items, &ttyctx, &written, ctx, ci, tmp);
  }

  s->cx = cx;
  s->cy = cy;
  log_debug("%s: flushed %u items (%zu bytes)", __func__, items, written);
  ctx->written += written;
}


----------------------------
void tty_cmd_clearstartofline(struct tty *tty, const struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  u_int py = ctx->yoff + ctx->ocy;
  tty_default_attributes(tty, wp, ctx->bg);
  tty_clear_line(tty, wp, py, ctx->xoff, ctx->ocx + 1, ctx->bg);
}


----------------------------
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void screen_write_initctx(struct screen_write_ctx *ctx, struct tty_ctx *ttyctx)
{
  struct screen *s = ctx->s;
  memset(ttyctx, 0, sizeof(*ttyctx));
  ttyctx->wp = ctx->wp;
  ttyctx->ocx = s->cx;
  ttyctx->ocy = s->cy;
  ttyctx->orlower = s->rlower;
  ttyctx->orupper = s->rupper;
}


----------------------------
void tty_write(void (*cmdfn)(struct tty *, const struct tty_ctx *), struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  struct client *c;
  unsigned int c_idx = 0;
  if (wp == 0)
  {
    return;
  }
  if ((wp->flags & (0x1 | 0x2)) || (!window_pane_visible(wp)))
  {
    return;
  }
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (!tty_client_ready(c, wp))
    {
      continue;
    }
    ctx->xoff = wp->xoff;
    ctx->yoff = wp->yoff;
    if (status_at_line(c) == 0)
    {
      ctx->yoff += status_line_size(c->session);
    }
    cmdfn(&c->tty, ctx);
  }

}


----------------------------
static void screen_write_collect_clear(struct screen_write_ctx *ctx, u_int y, u_int n)
{
  struct screen_write_collect_item *ci;
  unsigned int ci_idx = 0;
  struct screen_write_collect_item *tmp;
  unsigned int tmp_idx = 0;
  u_int i;
  size_t size;
  for (i = y; i < (y + n); i += 1)
  {
    if ((&ctx->list[i].items)->tqh_first == 0)
    {
      continue;
    }
    size = 0;
    for (ci_idx = (&ctx->list[i].items)->tqh_first; ((&ci[ci_idx]) != 0) && ((tmp_idx = ci->entry.tqe_next, 1)); ci_idx = &tmp[tmp_idx])
    {
      size += ci->used;
      do
      {
        if (ci->entry.tqe_next != 0)
        {
          ci->entry.tqe_next->entry.tqe_prev = ci->entry.tqe_prev;
        }
        else
          (&ctx->list[i].items)->tqh_last = ci->entry.tqe_prev;
        *ci->entry.tqe_prev = ci->entry.tqe_next;
        ;
        ;
      }
      while (0);
      free(ci);
    }

    ctx->skipped += size;
    log_debug("%s: dropped %zu bytes (line %u)", __func__, size, i);
  }

}


----------------------------
None
----------------------------
void grid_view_clear(struct grid *gd, u_int px, u_int py, u_int nx, u_int ny, u_int bg)
{
  px = px;
  py = gd->hsize + py;
  grid_clear(gd, px, py, nx, ny, bg);
}


----------------------------
None
----------------------------
***/


void screen_write_preview(struct screen_write_ctx *ctx, struct screen *src, u_int nx, u_int ny)
{
  struct screen *s = ctx->s;
  struct grid_cell gc;
  u_int cx;
  u_int cy;
  u_int px;
  u_int py;
  cx = s->cx;
  cy = s->cy;
  if (src->mode & 0x1)
  {
    px = src->cx;
    if (px < (nx / 3))
    {
      px = 0;
    }
    else
      px = px - (nx / 3);
    if ((px + nx) > src->grid->sx)
    {
      if (nx > src->grid->sx)
      {
        px = 0;
      }
      else
        px = src->grid->sx - nx;
    }
    py = src->cy;
    if (py < (ny / 3))
    {
      py = 0;
    }
    else
      py = py - (ny / 3);
    if ((py + ny) > src->grid->sy)
    {
      if (ny > src->grid->sy)
      {
        py = 0;
      }
      else
        py = src->grid->sy - ny;
    }
  }
  else
  {
    px = 0;
    py = 0;
  }
  screen_write_fast_copy(ctx, src, px, src->grid->hsize + py, nx, ny);
  if (src->mode & 0x1)
  {
    grid_view_get_cell(src->grid, src->cx, src->cy, &gc);
    gc.attr |= 0x10;
    screen_write_cursormove(ctx, cx + (src->cx - px), cy + (src->cy - py));
    screen_write_cell(ctx, &gc);
  }
}


/*** DEPENDENCIES:
void grid_view_get_cell(struct grid *gd, u_int px, u_int py, struct grid_cell *gc)
{
  grid_get_cell(gd, px, gd->hsize + py, gc);
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
None
----------------------------
void screen_write_fast_copy(struct screen_write_ctx *ctx, struct screen *src, u_int px, u_int py, u_int nx, u_int ny)
{
  struct screen *s = ctx->s;
  struct grid *gd = src->grid;
  struct grid_cell gc;
  u_int xx;
  u_int yy;
  u_int cx;
  u_int cy;
  if ((nx == 0) || (ny == 0))
  {
    return;
  }
  cy = s->cy;
  for (yy = py; yy < (py + ny); yy += 1)
  {
    if (yy >= (gd->hsize + gd->sy))
    {
      break;
    }
    cx = s->cx;
    for (xx = px; xx < (px + nx); xx += 1)
    {
      if (xx >= gd->linedata[yy].cellsize)
      {
        break;
      }
      grid_get_cell(gd, xx, yy, &gc);
      if ((xx + gc.data.width) > (px + nx))
      {
        break;
      }
      if (!grid_cells_equal(&gc, &grid_default_cell))
      {
        grid_view_set_cell(ctx->s->grid, cx, cy, &gc);
      }
      cx += 1;
    }

    cy += 1;
  }

}


----------------------------
void screen_write_cell(struct screen_write_ctx *ctx, const struct grid_cell *gc)
{
  unsigned int gc_idx = 0;
  struct screen *s = ctx->s;
  struct grid *gd = s->grid;
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  struct grid_cell_entry *gce;
  unsigned int gce_idx = 0;
  struct grid_cell tmp_gc;
  struct grid_cell now_gc;
  struct tty_ctx ttyctx;
  u_int sx = s->grid->sx;
  u_int sy = s->grid->sy;
  u_int width = gc->data.width;
  u_int xx;
  u_int last;
  u_int cx;
  u_int cy;
  int selected;
  int skip = 1;
  if (gc->flags & 0x4)
  {
    return;
  }
  ctx->cells += 1;
  if (width == 0)
  {
    helper_screen_write_cell_1(&gc_idx, &ttyctx, &cx, &cy, ctx, gc, s, xx);
  }
  screen_write_collect_flush(ctx, 1);
  if ((((~s->mode) & 0x10) && (width > 1)) && ((width > sx) || ((s->cx != sx) && (s->cx > (sx - width)))))
  {
    return;
  }
  if (s->mode & 0x2)
  {
    grid_view_insert_cells(s->grid, s->cx, s->cy, width, 8);
    skip = 0;
  }
  if ((s->mode & 0x10) && (s->cx > (sx - width)))
  {
    log_debug("%s: wrapped at %u,%u", __func__, s->cx, s->cy);
    screen_write_linefeed(ctx, 1, 8);
    s->cx = 0;
    screen_write_collect_flush(ctx, 1);
  }
  if ((s->cx > (sx - width)) || (s->cy > (sy - 1)))
  {
    return;
  }
  screen_write_initctx(ctx, &ttyctx);
  gl_idx = &s->grid->linedata[s->grid->hsize + s->cy];
  if (gl->flags & 0x2)
  {
    grid_view_get_cell(gd, s->cx, s->cy, &now_gc);
    if (screen_write_overwrite(ctx, &now_gc, width))
    {
      skip = 0;
    }
  }
  for (xx = s->cx + 1; xx < (s->cx + width); xx += 1)
  {
    log_debug("%s: new padding at %u,%u", __func__, xx, s->cy);
    grid_view_set_cell(gd, xx, s->cy, &screen_write_pad_cell);
    skip = 0;
  }

  if (skip)
  {
    helper_screen_write_cell_2(&gce_idx, &skip, gc, s, gl, gce);
  }
  selected = screen_check_selection(s, s->cx, s->cy);
  if (selected && ((~gc->flags) & 0x10))
  {
    memcpy(&tmp_gc, gc, sizeof(tmp_gc));
    tmp_gc.flags |= 0x10;
    grid_view_set_cell(gd, s->cx, s->cy, &tmp_gc);
  }
  else
    if ((!selected) && (gc->flags & 0x10))
  {
    memcpy(&tmp_gc, gc, sizeof(tmp_gc));
    tmp_gc.flags &= ~0x10;
    grid_view_set_cell(gd, s->cx, s->cy, &tmp_gc);
  }
  else
    if (!skip)
  {
    grid_view_set_cell(gd, s->cx, s->cy, gc);
  }
  if (selected)
  {
    skip = 0;
  }
  last = !(s->mode & 0x10);
  if (s->cx <= ((sx - last) - width))
  {
    s->cx += width;
  }
  else
    s->cx = sx - last;
  if (s->mode & 0x2)
  {
    screen_write_collect_flush(ctx, 0);
    ttyctx.num = width;
    tty_write(tty_cmd_insertcharacter, &ttyctx);
  }
  if (!skip)
  {
    if (selected)
    {
      screen_select_cell(s, &tmp_gc, gc);
      ttyctx.cell = &tmp_gc;
    }
    else
      ttyctx.cell = &gc[gc_idx];
    tty_write(tty_cmd_cell, &ttyctx);
    ctx->written += 1;
  }
  else
    ctx->skipped++;
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
None
----------------------------
***/


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


/*** DEPENDENCIES:
void tty_cmd_clearstartofscreen(struct tty *tty, const struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  u_int px;
  u_int py;
  u_int nx;
  u_int ny;
  tty_default_attributes(tty, wp, ctx->bg);
  tty_region_pane(tty, ctx, 0, wp->screen->grid->sy - 1);
  tty_margin_off(tty);
  px = ctx->xoff;
  nx = wp->screen->grid->sx;
  py = ctx->yoff;
  ny = ctx->ocy - 1;
  tty_clear_area(tty, wp, py, ny, px, nx, ctx->bg);
  px = ctx->xoff;
  nx = ctx->ocx + 1;
  py = ctx->yoff + ctx->ocy;
  tty_clear_line(tty, wp, py, px, nx, ctx->bg);
}


----------------------------
static void screen_write_collect_flush(struct screen_write_ctx *ctx, int scroll_only)
{
  struct screen *s = ctx->s;
  struct screen_write_collect_item *ci;
  unsigned int ci_idx = 0;
  struct screen_write_collect_item *tmp;
  unsigned int tmp_idx = 0;
  u_int y;
  u_int cx;
  u_int cy;
  u_int items = 0;
  struct tty_ctx ttyctx;
  size_t written = 0;
  if (ctx->scrolled != 0)
  {
    log_debug("%s: scrolled %u (region %u-%u)", __func__, ctx->scrolled, s->rupper, s->rlower);
    if (ctx->scrolled > ((s->rlower - s->rupper) + 1))
    {
      ctx->scrolled = (s->rlower - s->rupper) + 1;
    }
    screen_write_initctx(ctx, &ttyctx);
    ttyctx.num = ctx->scrolled;
    ttyctx.bg = ctx->bg;
    tty_write(tty_cmd_scrollup, &ttyctx);
  }
  ctx->scrolled = 0;
  ctx->bg = 8;
  if (scroll_only)
  {
    return;
  }
  cx = s->cx;
  cy = s->cy;
  for (y = 0; y < s->grid->sy; y += 1)
  {
    helper_screen_write_collect_flush_1(&ci_idx, &tmp_idx, &y, &items, &ttyctx, &written, ctx, ci, tmp);
  }

  s->cx = cx;
  s->cy = cy;
  log_debug("%s: flushed %u items (%zu bytes)", __func__, items, written);
  ctx->written += written;
}


----------------------------
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void screen_write_initctx(struct screen_write_ctx *ctx, struct tty_ctx *ttyctx)
{
  struct screen *s = ctx->s;
  memset(ttyctx, 0, sizeof(*ttyctx));
  ttyctx->wp = ctx->wp;
  ttyctx->ocx = s->cx;
  ttyctx->ocy = s->cy;
  ttyctx->orlower = s->rlower;
  ttyctx->orupper = s->rupper;
}


----------------------------
void tty_write(void (*cmdfn)(struct tty *, const struct tty_ctx *), struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  struct client *c;
  unsigned int c_idx = 0;
  if (wp == 0)
  {
    return;
  }
  if ((wp->flags & (0x1 | 0x2)) || (!window_pane_visible(wp)))
  {
    return;
  }
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (!tty_client_ready(c, wp))
    {
      continue;
    }
    ctx->xoff = wp->xoff;
    ctx->yoff = wp->yoff;
    if (status_at_line(c) == 0)
    {
      ctx->yoff += status_line_size(c->session);
    }
    cmdfn(&c->tty, ctx);
  }

}


----------------------------
static void screen_write_collect_clear(struct screen_write_ctx *ctx, u_int y, u_int n)
{
  struct screen_write_collect_item *ci;
  unsigned int ci_idx = 0;
  struct screen_write_collect_item *tmp;
  unsigned int tmp_idx = 0;
  u_int i;
  size_t size;
  for (i = y; i < (y + n); i += 1)
  {
    if ((&ctx->list[i].items)->tqh_first == 0)
    {
      continue;
    }
    size = 0;
    for (ci_idx = (&ctx->list[i].items)->tqh_first; ((&ci[ci_idx]) != 0) && ((tmp_idx = ci->entry.tqe_next, 1)); ci_idx = &tmp[tmp_idx])
    {
      size += ci->used;
      do
      {
        if (ci->entry.tqe_next != 0)
        {
          ci->entry.tqe_next->entry.tqe_prev = ci->entry.tqe_prev;
        }
        else
          (&ctx->list[i].items)->tqh_last = ci->entry.tqe_prev;
        *ci->entry.tqe_prev = ci->entry.tqe_next;
        ;
        ;
      }
      while (0);
      free(ci);
    }

    ctx->skipped += size;
    log_debug("%s: dropped %zu bytes (line %u)", __func__, size, i);
  }

}


----------------------------
None
----------------------------
void grid_view_clear(struct grid *gd, u_int px, u_int py, u_int nx, u_int ny, u_int bg)
{
  px = px;
  py = gd->hsize + py;
  grid_clear(gd, px, py, nx, ny, bg);
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
void grid_view_clear_history(struct grid *gd, u_int bg)
{
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  u_int yy;
  u_int last;
  last = 0;
  for (yy = 0; yy < gd->sy; yy += 1)
  {
    gl_idx = &gd->linedata[gd->hsize + yy];
    if (gl->cellused != 0)
    {
      last = yy + 1;
    }
  }

  if (last == 0)
  {
    grid_view_clear(gd, 0, 0, gd->sx, gd->sy, bg);
    return;
  }
  for (yy = 0; yy < last; yy += 1)
  {
    grid_collect_history(gd);
    grid_scroll_history(gd, bg);
  }

  if (last < gd->sy)
  {
    grid_view_clear(gd, 0, 0, gd->sx, gd->sy - last, bg);
  }
  gd->hscrolled = 0;
}


----------------------------
static void screen_write_collect_flush(struct screen_write_ctx *ctx, int scroll_only)
{
  struct screen *s = ctx->s;
  struct screen_write_collect_item *ci;
  unsigned int ci_idx = 0;
  struct screen_write_collect_item *tmp;
  unsigned int tmp_idx = 0;
  u_int y;
  u_int cx;
  u_int cy;
  u_int items = 0;
  struct tty_ctx ttyctx;
  size_t written = 0;
  if (ctx->scrolled != 0)
  {
    log_debug("%s: scrolled %u (region %u-%u)", __func__, ctx->scrolled, s->rupper, s->rlower);
    if (ctx->scrolled > ((s->rlower - s->rupper) + 1))
    {
      ctx->scrolled = (s->rlower - s->rupper) + 1;
    }
    screen_write_initctx(ctx, &ttyctx);
    ttyctx.num = ctx->scrolled;
    ttyctx.bg = ctx->bg;
    tty_write(tty_cmd_scrollup, &ttyctx);
  }
  ctx->scrolled = 0;
  ctx->bg = 8;
  if (scroll_only)
  {
    return;
  }
  cx = s->cx;
  cy = s->cy;
  for (y = 0; y < s->grid->sy; y += 1)
  {
    helper_screen_write_collect_flush_1(&ci_idx, &tmp_idx, &y, &items, &ttyctx, &written, ctx, ci, tmp);
  }

  s->cx = cx;
  s->cy = cy;
  log_debug("%s: flushed %u items (%zu bytes)", __func__, items, written);
  ctx->written += written;
}


----------------------------
None
----------------------------
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void screen_write_initctx(struct screen_write_ctx *ctx, struct tty_ctx *ttyctx)
{
  struct screen *s = ctx->s;
  memset(ttyctx, 0, sizeof(*ttyctx));
  ttyctx->wp = ctx->wp;
  ttyctx->ocx = s->cx;
  ttyctx->ocy = s->cy;
  ttyctx->orlower = s->rlower;
  ttyctx->orupper = s->rupper;
}


----------------------------
void tty_cmd_clearendofscreen(struct tty *tty, const struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  u_int px;
  u_int py;
  u_int nx;
  u_int ny;
  tty_default_attributes(tty, wp, ctx->bg);
  tty_region_pane(tty, ctx, 0, wp->screen->grid->sy - 1);
  tty_margin_off(tty);
  px = ctx->xoff;
  nx = wp->screen->grid->sx;
  py = (ctx->yoff + ctx->ocy) + 1;
  ny = (wp->screen->grid->sy - ctx->ocy) - 1;
  tty_clear_area(tty, wp, py, ny, px, nx, ctx->bg);
  px = ctx->xoff + ctx->ocx;
  nx = wp->screen->grid->sx - ctx->ocx;
  py = ctx->yoff + ctx->ocy;
  tty_clear_line(tty, wp, py, px, nx, ctx->bg);
}


----------------------------
void tty_write(void (*cmdfn)(struct tty *, const struct tty_ctx *), struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  struct client *c;
  unsigned int c_idx = 0;
  if (wp == 0)
  {
    return;
  }
  if ((wp->flags & (0x1 | 0x2)) || (!window_pane_visible(wp)))
  {
    return;
  }
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (!tty_client_ready(c, wp))
    {
      continue;
    }
    ctx->xoff = wp->xoff;
    ctx->yoff = wp->yoff;
    if (status_at_line(c) == 0)
    {
      ctx->yoff += status_line_size(c->session);
    }
    cmdfn(&c->tty, ctx);
  }

}


----------------------------
static void screen_write_collect_clear(struct screen_write_ctx *ctx, u_int y, u_int n)
{
  struct screen_write_collect_item *ci;
  unsigned int ci_idx = 0;
  struct screen_write_collect_item *tmp;
  unsigned int tmp_idx = 0;
  u_int i;
  size_t size;
  for (i = y; i < (y + n); i += 1)
  {
    if ((&ctx->list[i].items)->tqh_first == 0)
    {
      continue;
    }
    size = 0;
    for (ci_idx = (&ctx->list[i].items)->tqh_first; ((&ci[ci_idx]) != 0) && ((tmp_idx = ci->entry.tqe_next, 1)); ci_idx = &tmp[tmp_idx])
    {
      size += ci->used;
      do
      {
        if (ci->entry.tqe_next != 0)
        {
          ci->entry.tqe_next->entry.tqe_prev = ci->entry.tqe_prev;
        }
        else
          (&ctx->list[i].items)->tqh_last = ci->entry.tqe_prev;
        *ci->entry.tqe_prev = ci->entry.tqe_next;
        ;
        ;
      }
      while (0);
      free(ci);
    }

    ctx->skipped += size;
    log_debug("%s: dropped %zu bytes (line %u)", __func__, size, i);
  }

}


----------------------------
None
----------------------------
void grid_view_clear(struct grid *gd, u_int px, u_int py, u_int nx, u_int ny, u_int bg)
{
  px = px;
  py = gd->hsize + py;
  grid_clear(gd, px, py, nx, ny, bg);
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
void tty_cmd_insertcharacter(struct tty *tty, const struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  if (((!((ctx->xoff == 0) && (ctx->wp->screen->grid->sx >= tty->sx))) || tty_fake_bce(tty, wp, ctx->bg)) || ((!tty_term_has(tty->term, TTYC_ICH)) && (!tty_term_has(tty->term, TTYC_ICH1))))
  {
    tty_draw_pane(tty, wp, ctx->ocy, ctx->xoff, ctx->yoff);
    return;
  }
  tty_default_attributes(tty, wp, ctx->bg);
  tty_cursor_pane(tty, ctx, ctx->ocx, ctx->ocy);
  tty_emulate_repeat(tty, TTYC_ICH, TTYC_ICH1, ctx->num);
}


----------------------------
void grid_view_insert_cells(struct grid *gd, u_int px, u_int py, u_int nx, u_int bg)
{
  u_int sx;
  px = px;
  py = gd->hsize + py;
  sx = gd->sx;
  if (px >= (sx - 1))
  {
    grid_clear(gd, px, py, 1, 1, bg);
  }
  else
    grid_move_cells(gd, px + nx, px, py, (sx - px) - nx, bg);
}


----------------------------
static void screen_write_collect_flush(struct screen_write_ctx *ctx, int scroll_only)
{
  struct screen *s = ctx->s;
  struct screen_write_collect_item *ci;
  unsigned int ci_idx = 0;
  struct screen_write_collect_item *tmp;
  unsigned int tmp_idx = 0;
  u_int y;
  u_int cx;
  u_int cy;
  u_int items = 0;
  struct tty_ctx ttyctx;
  size_t written = 0;
  if (ctx->scrolled != 0)
  {
    log_debug("%s: scrolled %u (region %u-%u)", __func__, ctx->scrolled, s->rupper, s->rlower);
    if (ctx->scrolled > ((s->rlower - s->rupper) + 1))
    {
      ctx->scrolled = (s->rlower - s->rupper) + 1;
    }
    screen_write_initctx(ctx, &ttyctx);
    ttyctx.num = ctx->scrolled;
    ttyctx.bg = ctx->bg;
    tty_write(tty_cmd_scrollup, &ttyctx);
  }
  ctx->scrolled = 0;
  ctx->bg = 8;
  if (scroll_only)
  {
    return;
  }
  cx = s->cx;
  cy = s->cy;
  for (y = 0; y < s->grid->sy; y += 1)
  {
    helper_screen_write_collect_flush_1(&ci_idx, &tmp_idx, &y, &items, &ttyctx, &written, ctx, ci, tmp);
  }

  s->cx = cx;
  s->cy = cy;
  log_debug("%s: flushed %u items (%zu bytes)", __func__, items, written);
  ctx->written += written;
}


----------------------------
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void screen_write_initctx(struct screen_write_ctx *ctx, struct tty_ctx *ttyctx)
{
  struct screen *s = ctx->s;
  memset(ttyctx, 0, sizeof(*ttyctx));
  ttyctx->wp = ctx->wp;
  ttyctx->ocx = s->cx;
  ttyctx->ocy = s->cy;
  ttyctx->orlower = s->rlower;
  ttyctx->orupper = s->rupper;
}


----------------------------
void tty_write(void (*cmdfn)(struct tty *, const struct tty_ctx *), struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  struct client *c;
  unsigned int c_idx = 0;
  if (wp == 0)
  {
    return;
  }
  if ((wp->flags & (0x1 | 0x2)) || (!window_pane_visible(wp)))
  {
    return;
  }
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (!tty_client_ready(c, wp))
    {
      continue;
    }
    ctx->xoff = wp->xoff;
    ctx->yoff = wp->yoff;
    if (status_at_line(c) == 0)
    {
      ctx->yoff += status_line_size(c->session);
    }
    cmdfn(&c->tty, ctx);
  }

}


----------------------------
None
----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
static void screen_write_collect_flush(struct screen_write_ctx *ctx, int scroll_only)
{
  struct screen *s = ctx->s;
  struct screen_write_collect_item *ci;
  unsigned int ci_idx = 0;
  struct screen_write_collect_item *tmp;
  unsigned int tmp_idx = 0;
  u_int y;
  u_int cx;
  u_int cy;
  u_int items = 0;
  struct tty_ctx ttyctx;
  size_t written = 0;
  if (ctx->scrolled != 0)
  {
    log_debug("%s: scrolled %u (region %u-%u)", __func__, ctx->scrolled, s->rupper, s->rlower);
    if (ctx->scrolled > ((s->rlower - s->rupper) + 1))
    {
      ctx->scrolled = (s->rlower - s->rupper) + 1;
    }
    screen_write_initctx(ctx, &ttyctx);
    ttyctx.num = ctx->scrolled;
    ttyctx.bg = ctx->bg;
    tty_write(tty_cmd_scrollup, &ttyctx);
  }
  ctx->scrolled = 0;
  ctx->bg = 8;
  if (scroll_only)
  {
    return;
  }
  cx = s->cx;
  cy = s->cy;
  for (y = 0; y < s->grid->sy; y += 1)
  {
    helper_screen_write_collect_flush_1(&ci_idx, &tmp_idx, &y, &items, &ttyctx, &written, ctx, ci, tmp);
  }

  s->cx = cx;
  s->cy = cy;
  log_debug("%s: flushed %u items (%zu bytes)", __func__, items, written);
  ctx->written += written;
}


----------------------------
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void screen_write_initctx(struct screen_write_ctx *ctx, struct tty_ctx *ttyctx)
{
  struct screen *s = ctx->s;
  memset(ttyctx, 0, sizeof(*ttyctx));
  ttyctx->wp = ctx->wp;
  ttyctx->ocx = s->cx;
  ttyctx->ocy = s->cy;
  ttyctx->orlower = s->rlower;
  ttyctx->orupper = s->rupper;
}


----------------------------
void tty_write(void (*cmdfn)(struct tty *, const struct tty_ctx *), struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  struct client *c;
  unsigned int c_idx = 0;
  if (wp == 0)
  {
    return;
  }
  if ((wp->flags & (0x1 | 0x2)) || (!window_pane_visible(wp)))
  {
    return;
  }
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (!tty_client_ready(c, wp))
    {
      continue;
    }
    ctx->xoff = wp->xoff;
    ctx->yoff = wp->yoff;
    if (status_at_line(c) == 0)
    {
      ctx->yoff += status_line_size(c->session);
    }
    cmdfn(&c->tty, ctx);
  }

}


----------------------------
void grid_view_delete_cells(struct grid *gd, u_int px, u_int py, u_int nx, u_int bg)
{
  u_int sx;
  px = px;
  py = gd->hsize + py;
  sx = gd->sx;
  grid_move_cells(gd, px, px + nx, py, (sx - px) - nx, bg);
  grid_clear(gd, sx - nx, py, (px + nx) - (sx - nx), 1, bg);
}


----------------------------
None
----------------------------
void tty_cmd_deletecharacter(struct tty *tty, const struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  if (((!((ctx->xoff == 0) && (ctx->wp->screen->grid->sx >= tty->sx))) || tty_fake_bce(tty, wp, ctx->bg)) || ((!tty_term_has(tty->term, TTYC_DCH)) && (!tty_term_has(tty->term, TTYC_DCH1))))
  {
    tty_draw_pane(tty, wp, ctx->ocy, ctx->xoff, ctx->yoff);
    return;
  }
  tty_default_attributes(tty, wp, ctx->bg);
  tty_cursor_pane(tty, ctx, ctx->ocx, ctx->ocy);
  tty_emulate_repeat(tty, TTYC_DCH, TTYC_DCH1, ctx->num);
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
static void screen_write_collect_flush(struct screen_write_ctx *ctx, int scroll_only)
{
  struct screen *s = ctx->s;
  struct screen_write_collect_item *ci;
  unsigned int ci_idx = 0;
  struct screen_write_collect_item *tmp;
  unsigned int tmp_idx = 0;
  u_int y;
  u_int cx;
  u_int cy;
  u_int items = 0;
  struct tty_ctx ttyctx;
  size_t written = 0;
  if (ctx->scrolled != 0)
  {
    log_debug("%s: scrolled %u (region %u-%u)", __func__, ctx->scrolled, s->rupper, s->rlower);
    if (ctx->scrolled > ((s->rlower - s->rupper) + 1))
    {
      ctx->scrolled = (s->rlower - s->rupper) + 1;
    }
    screen_write_initctx(ctx, &ttyctx);
    ttyctx.num = ctx->scrolled;
    ttyctx.bg = ctx->bg;
    tty_write(tty_cmd_scrollup, &ttyctx);
  }
  ctx->scrolled = 0;
  ctx->bg = 8;
  if (scroll_only)
  {
    return;
  }
  cx = s->cx;
  cy = s->cy;
  for (y = 0; y < s->grid->sy; y += 1)
  {
    helper_screen_write_collect_flush_1(&ci_idx, &tmp_idx, &y, &items, &ttyctx, &written, ctx, ci, tmp);
  }

  s->cx = cx;
  s->cy = cy;
  log_debug("%s: flushed %u items (%zu bytes)", __func__, items, written);
  ctx->written += written;
}


----------------------------
void tty_cmd_clearcharacter(struct tty *tty, const struct tty_ctx *ctx)
{
  tty_default_attributes(tty, ctx->wp, ctx->bg);
  tty_cursor_pane(tty, ctx, ctx->ocx, ctx->ocy);
  if (tty_term_has(tty->term, TTYC_ECH) && (!tty_fake_bce(tty, ctx->wp, 8)))
  {
    tty_putcode1(tty, TTYC_ECH, ctx->num);
  }
  else
    tty_repeat_space(tty, ctx->num);
}


----------------------------
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void screen_write_initctx(struct screen_write_ctx *ctx, struct tty_ctx *ttyctx)
{
  struct screen *s = ctx->s;
  memset(ttyctx, 0, sizeof(*ttyctx));
  ttyctx->wp = ctx->wp;
  ttyctx->ocx = s->cx;
  ttyctx->ocy = s->cy;
  ttyctx->orlower = s->rlower;
  ttyctx->orupper = s->rupper;
}


----------------------------
void tty_write(void (*cmdfn)(struct tty *, const struct tty_ctx *), struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  struct client *c;
  unsigned int c_idx = 0;
  if (wp == 0)
  {
    return;
  }
  if ((wp->flags & (0x1 | 0x2)) || (!window_pane_visible(wp)))
  {
    return;
  }
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (!tty_client_ready(c, wp))
    {
      continue;
    }
    ctx->xoff = wp->xoff;
    ctx->yoff = wp->yoff;
    if (status_at_line(c) == 0)
    {
      ctx->yoff += status_line_size(c->session);
    }
    cmdfn(&c->tty, ctx);
  }

}


----------------------------
None
----------------------------
void grid_view_clear(struct grid *gd, u_int px, u_int py, u_int nx, u_int ny, u_int bg)
{
  px = px;
  py = gd->hsize + py;
  grid_clear(gd, px, py, nx, ny, bg);
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
void grid_view_scroll_region_down(struct grid *gd, u_int rupper, u_int rlower, u_int bg)
{
  rupper = gd->hsize + rupper;
  rlower = gd->hsize + rlower;
  grid_move_lines(gd, rupper + 1, rupper, rlower - rupper, bg);
}


----------------------------
static void screen_write_collect_flush(struct screen_write_ctx *ctx, int scroll_only)
{
  struct screen *s = ctx->s;
  struct screen_write_collect_item *ci;
  unsigned int ci_idx = 0;
  struct screen_write_collect_item *tmp;
  unsigned int tmp_idx = 0;
  u_int y;
  u_int cx;
  u_int cy;
  u_int items = 0;
  struct tty_ctx ttyctx;
  size_t written = 0;
  if (ctx->scrolled != 0)
  {
    log_debug("%s: scrolled %u (region %u-%u)", __func__, ctx->scrolled, s->rupper, s->rlower);
    if (ctx->scrolled > ((s->rlower - s->rupper) + 1))
    {
      ctx->scrolled = (s->rlower - s->rupper) + 1;
    }
    screen_write_initctx(ctx, &ttyctx);
    ttyctx.num = ctx->scrolled;
    ttyctx.bg = ctx->bg;
    tty_write(tty_cmd_scrollup, &ttyctx);
  }
  ctx->scrolled = 0;
  ctx->bg = 8;
  if (scroll_only)
  {
    return;
  }
  cx = s->cx;
  cy = s->cy;
  for (y = 0; y < s->grid->sy; y += 1)
  {
    helper_screen_write_collect_flush_1(&ci_idx, &tmp_idx, &y, &items, &ttyctx, &written, ctx, ci, tmp);
  }

  s->cx = cx;
  s->cy = cy;
  log_debug("%s: flushed %u items (%zu bytes)", __func__, items, written);
  ctx->written += written;
}


----------------------------
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void screen_write_initctx(struct screen_write_ctx *ctx, struct tty_ctx *ttyctx)
{
  struct screen *s = ctx->s;
  memset(ttyctx, 0, sizeof(*ttyctx));
  ttyctx->wp = ctx->wp;
  ttyctx->ocx = s->cx;
  ttyctx->ocy = s->cy;
  ttyctx->orlower = s->rlower;
  ttyctx->orupper = s->rupper;
}


----------------------------
void tty_cmd_reverseindex(struct tty *tty, const struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  if (ctx->ocy != ctx->orupper)
  {
    return;
  }
  if ((((!((ctx->xoff == 0) && (ctx->wp->screen->grid->sx >= tty->sx))) || tty_fake_bce(tty, wp, 8)) || (!tty_term_has(tty->term, TTYC_CSR))) || (!tty_term_has(tty->term, TTYC_RI)))
  {
    tty_redraw_region(tty, ctx);
    return;
  }
  tty_default_attributes(tty, wp, ctx->bg);
  tty_region_pane(tty, ctx, ctx->orupper, ctx->orlower);
  tty_margin_off(tty);
  tty_cursor_pane(tty, ctx, ctx->ocx, ctx->orupper);
  tty_putcode(tty, TTYC_RI);
}


----------------------------
void tty_write(void (*cmdfn)(struct tty *, const struct tty_ctx *), struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  struct client *c;
  unsigned int c_idx = 0;
  if (wp == 0)
  {
    return;
  }
  if ((wp->flags & (0x1 | 0x2)) || (!window_pane_visible(wp)))
  {
    return;
  }
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (!tty_client_ready(c, wp))
    {
      continue;
    }
    ctx->xoff = wp->xoff;
    ctx->yoff = wp->yoff;
    if (status_at_line(c) == 0)
    {
      ctx->yoff += status_line_size(c->session);
    }
    cmdfn(&c->tty, ctx);
  }

}


----------------------------
None
----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
void tty_cmd_deleteline(struct tty *tty, const struct tty_ctx *ctx)
{
  if ((((!((ctx->xoff == 0) && (ctx->wp->screen->grid->sx >= tty->sx))) || tty_fake_bce(tty, ctx->wp, ctx->bg)) || (!tty_term_has(tty->term, TTYC_CSR))) || (!tty_term_has(tty->term, TTYC_DL1)))
  {
    tty_redraw_region(tty, ctx);
    return;
  }
  tty_default_attributes(tty, ctx->wp, ctx->bg);
  tty_region_pane(tty, ctx, ctx->orupper, ctx->orlower);
  tty_margin_off(tty);
  tty_cursor_pane(tty, ctx, ctx->ocx, ctx->ocy);
  tty_emulate_repeat(tty, TTYC_DL, TTYC_DL1, ctx->num);
  tty->cx = (tty->cy = 4294967295U);
}


----------------------------
void grid_view_delete_lines_region(struct grid *gd, u_int rlower, u_int py, u_int ny, u_int bg)
{
  u_int ny2;
  rlower = gd->hsize + rlower;
  py = gd->hsize + py;
  ny2 = ((rlower + 1) - py) - ny;
  grid_move_lines(gd, py, py + ny, ny2, bg);
  grid_clear(gd, 0, py + ny2, gd->sx, ny - ny2, bg);
}


----------------------------
static void screen_write_collect_flush(struct screen_write_ctx *ctx, int scroll_only)
{
  struct screen *s = ctx->s;
  struct screen_write_collect_item *ci;
  unsigned int ci_idx = 0;
  struct screen_write_collect_item *tmp;
  unsigned int tmp_idx = 0;
  u_int y;
  u_int cx;
  u_int cy;
  u_int items = 0;
  struct tty_ctx ttyctx;
  size_t written = 0;
  if (ctx->scrolled != 0)
  {
    log_debug("%s: scrolled %u (region %u-%u)", __func__, ctx->scrolled, s->rupper, s->rlower);
    if (ctx->scrolled > ((s->rlower - s->rupper) + 1))
    {
      ctx->scrolled = (s->rlower - s->rupper) + 1;
    }
    screen_write_initctx(ctx, &ttyctx);
    ttyctx.num = ctx->scrolled;
    ttyctx.bg = ctx->bg;
    tty_write(tty_cmd_scrollup, &ttyctx);
  }
  ctx->scrolled = 0;
  ctx->bg = 8;
  if (scroll_only)
  {
    return;
  }
  cx = s->cx;
  cy = s->cy;
  for (y = 0; y < s->grid->sy; y += 1)
  {
    helper_screen_write_collect_flush_1(&ci_idx, &tmp_idx, &y, &items, &ttyctx, &written, ctx, ci, tmp);
  }

  s->cx = cx;
  s->cy = cy;
  log_debug("%s: flushed %u items (%zu bytes)", __func__, items, written);
  ctx->written += written;
}


----------------------------
None
----------------------------
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void screen_write_initctx(struct screen_write_ctx *ctx, struct tty_ctx *ttyctx)
{
  struct screen *s = ctx->s;
  memset(ttyctx, 0, sizeof(*ttyctx));
  ttyctx->wp = ctx->wp;
  ttyctx->ocx = s->cx;
  ttyctx->ocy = s->cy;
  ttyctx->orlower = s->rlower;
  ttyctx->orupper = s->rupper;
}


----------------------------
void tty_write(void (*cmdfn)(struct tty *, const struct tty_ctx *), struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  struct client *c;
  unsigned int c_idx = 0;
  if (wp == 0)
  {
    return;
  }
  if ((wp->flags & (0x1 | 0x2)) || (!window_pane_visible(wp)))
  {
    return;
  }
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (!tty_client_ready(c, wp))
    {
      continue;
    }
    ctx->xoff = wp->xoff;
    ctx->yoff = wp->yoff;
    if (status_at_line(c) == 0)
    {
      ctx->yoff += status_line_size(c->session);
    }
    cmdfn(&c->tty, ctx);
  }

}


----------------------------
void grid_view_delete_lines(struct grid *gd, u_int py, u_int ny, u_int bg)
{
  u_int sy;
  py = gd->hsize + py;
  sy = gd->hsize + gd->sy;
  grid_move_lines(gd, py, py + ny, (sy - py) - ny, bg);
  grid_clear(gd, 0, sy - ny, gd->sx, (py + ny) - (sy - ny), bg);
}


----------------------------
None
----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
void grid_view_insert_lines_region(struct grid *gd, u_int rlower, u_int py, u_int ny, u_int bg)
{
  u_int ny2;
  rlower = gd->hsize + rlower;
  py = gd->hsize + py;
  ny2 = ((rlower + 1) - py) - ny;
  grid_move_lines(gd, (rlower + 1) - ny2, py, ny2, bg);
  grid_clear(gd, 0, py + ny2, gd->sx, ny - ny2, bg);
}


----------------------------
static void screen_write_collect_flush(struct screen_write_ctx *ctx, int scroll_only)
{
  struct screen *s = ctx->s;
  struct screen_write_collect_item *ci;
  unsigned int ci_idx = 0;
  struct screen_write_collect_item *tmp;
  unsigned int tmp_idx = 0;
  u_int y;
  u_int cx;
  u_int cy;
  u_int items = 0;
  struct tty_ctx ttyctx;
  size_t written = 0;
  if (ctx->scrolled != 0)
  {
    log_debug("%s: scrolled %u (region %u-%u)", __func__, ctx->scrolled, s->rupper, s->rlower);
    if (ctx->scrolled > ((s->rlower - s->rupper) + 1))
    {
      ctx->scrolled = (s->rlower - s->rupper) + 1;
    }
    screen_write_initctx(ctx, &ttyctx);
    ttyctx.num = ctx->scrolled;
    ttyctx.bg = ctx->bg;
    tty_write(tty_cmd_scrollup, &ttyctx);
  }
  ctx->scrolled = 0;
  ctx->bg = 8;
  if (scroll_only)
  {
    return;
  }
  cx = s->cx;
  cy = s->cy;
  for (y = 0; y < s->grid->sy; y += 1)
  {
    helper_screen_write_collect_flush_1(&ci_idx, &tmp_idx, &y, &items, &ttyctx, &written, ctx, ci, tmp);
  }

  s->cx = cx;
  s->cy = cy;
  log_debug("%s: flushed %u items (%zu bytes)", __func__, items, written);
  ctx->written += written;
}


----------------------------
None
----------------------------
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void screen_write_initctx(struct screen_write_ctx *ctx, struct tty_ctx *ttyctx)
{
  struct screen *s = ctx->s;
  memset(ttyctx, 0, sizeof(*ttyctx));
  ttyctx->wp = ctx->wp;
  ttyctx->ocx = s->cx;
  ttyctx->ocy = s->cy;
  ttyctx->orlower = s->rlower;
  ttyctx->orupper = s->rupper;
}


----------------------------
void tty_cmd_insertline(struct tty *tty, const struct tty_ctx *ctx)
{
  if ((((!((ctx->xoff == 0) && (ctx->wp->screen->grid->sx >= tty->sx))) || tty_fake_bce(tty, ctx->wp, ctx->bg)) || (!tty_term_has(tty->term, TTYC_CSR))) || (!tty_term_has(tty->term, TTYC_IL1)))
  {
    tty_redraw_region(tty, ctx);
    return;
  }
  tty_default_attributes(tty, ctx->wp, ctx->bg);
  tty_region_pane(tty, ctx, ctx->orupper, ctx->orlower);
  tty_margin_off(tty);
  tty_cursor_pane(tty, ctx, ctx->ocx, ctx->ocy);
  tty_emulate_repeat(tty, TTYC_IL, TTYC_IL1, ctx->num);
  tty->cx = (tty->cy = 4294967295U);
}


----------------------------
void tty_write(void (*cmdfn)(struct tty *, const struct tty_ctx *), struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  struct client *c;
  unsigned int c_idx = 0;
  if (wp == 0)
  {
    return;
  }
  if ((wp->flags & (0x1 | 0x2)) || (!window_pane_visible(wp)))
  {
    return;
  }
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (!tty_client_ready(c, wp))
    {
      continue;
    }
    ctx->xoff = wp->xoff;
    ctx->yoff = wp->yoff;
    if (status_at_line(c) == 0)
    {
      ctx->yoff += status_line_size(c->session);
    }
    cmdfn(&c->tty, ctx);
  }

}


----------------------------
None
----------------------------
void grid_view_insert_lines(struct grid *gd, u_int py, u_int ny, u_int bg)
{
  u_int sy;
  py = gd->hsize + py;
  sy = gd->hsize + gd->sy;
  grid_move_lines(gd, py + ny, py, (sy - py) - ny, bg);
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
void utf8_set(struct utf8_data *ud, u_char ch)
{
  static const struct utf8_data empty = {{0}, 1, 1, 1};
  memcpy(ud, &empty, sizeof(*ud));
  *ud->data = ch;
}


----------------------------
extern const struct grid_cell grid_default_cell
----------------------------
void grid_view_set_cell(struct grid *gd, u_int px, u_int py, const struct grid_cell *gc)
{
  grid_set_cell(gd, px, gd->hsize + py, gc);
}


----------------------------
None
----------------------------
struct tty_ctx
{
  struct window_pane *wp;
  const struct grid_cell *cell;
  int wrapped;
  u_int num;
  void *ptr;
  u_int ocx;
  u_int ocy;
  u_int orupper;
  u_int orlower;
  u_int xoff;
  u_int yoff;
  u_int bg;
}
----------------------------
static void screen_write_initctx(struct screen_write_ctx *ctx, struct tty_ctx *ttyctx)
{
  struct screen *s = ctx->s;
  memset(ttyctx, 0, sizeof(*ttyctx));
  ttyctx->wp = ctx->wp;
  ttyctx->ocx = s->cx;
  ttyctx->ocy = s->cy;
  ttyctx->orlower = s->rlower;
  ttyctx->orupper = s->rupper;
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
void tty_write(void (*cmdfn)(struct tty *, const struct tty_ctx *), struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  struct client *c;
  unsigned int c_idx = 0;
  if (wp == 0)
  {
    return;
  }
  if ((wp->flags & (0x1 | 0x2)) || (!window_pane_visible(wp)))
  {
    return;
  }
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (!tty_client_ready(c, wp))
    {
      continue;
    }
    ctx->xoff = wp->xoff;
    ctx->yoff = wp->yoff;
    if (status_at_line(c) == 0)
    {
      ctx->yoff += status_line_size(c->session);
    }
    cmdfn(&c->tty, ctx);
  }

}


----------------------------
static void screen_write_collect_clear(struct screen_write_ctx *ctx, u_int y, u_int n)
{
  struct screen_write_collect_item *ci;
  unsigned int ci_idx = 0;
  struct screen_write_collect_item *tmp;
  unsigned int tmp_idx = 0;
  u_int i;
  size_t size;
  for (i = y; i < (y + n); i += 1)
  {
    if ((&ctx->list[i].items)->tqh_first == 0)
    {
      continue;
    }
    size = 0;
    for (ci_idx = (&ctx->list[i].items)->tqh_first; ((&ci[ci_idx]) != 0) && ((tmp_idx = ci->entry.tqe_next, 1)); ci_idx = &tmp[tmp_idx])
    {
      size += ci->used;
      do
      {
        if (ci->entry.tqe_next != 0)
        {
          ci->entry.tqe_next->entry.tqe_prev = ci->entry.tqe_prev;
        }
        else
          (&ctx->list[i].items)->tqh_last = ci->entry.tqe_prev;
        *ci->entry.tqe_prev = ci->entry.tqe_next;
        ;
        ;
      }
      while (0);
      free(ci);
    }

    ctx->skipped += size;
    log_debug("%s: dropped %zu bytes (line %u)", __func__, size, i);
  }

}


----------------------------
None
----------------------------
void tty_cmd_alignmenttest(struct tty *tty, const struct tty_ctx *ctx)
{
  struct window_pane *wp = ctx->wp;
  struct screen *s = wp->screen;
  u_int i;
  u_int j;
  tty_attributes(tty, &grid_default_cell, wp);
  tty_region_pane(tty, ctx, 0, s->grid->sy - 1);
  tty_margin_off(tty);
  for (j = 0; j < s->grid->sy; j += 1)
  {
    tty_cursor_pane(tty, ctx, 0, j);
    for (i = 0; i < s->grid->sx; i += 1)
    {
      tty_putc(tty, 'E');
    }

  }

}


----------------------------
None
----------------------------
***/


