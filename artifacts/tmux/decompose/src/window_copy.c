void window_copy_add_formats(struct window_pane *wp, struct format_tree *ft)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  if (wp->mode != (&window_copy_mode))
  {
    return;
  }
  format_add(ft, "selection_present", "%d", s->sel.flag);
  format_add(ft, "scroll_position", "%d", data->oy);
}


/*** DEPENDENCIES:
extern const struct window_mode window_copy_mode
----------------------------
None
----------------------------
void format_add(struct format_tree *ft, const char *key, const char *fmt, ...)
{
  struct format_entry *fe;
  unsigned int fe_idx = 0;
  struct format_entry *fe_now;
  unsigned int fe_now_idx = 0;
  va_list ap;
  fe_idx = xmalloc(sizeof(*fe_idx));
  fe->key = xstrdup(key);
  fe_now_idx = format_entry_tree_RB_INSERT(&ft->tree, fe);
  if ((&fe_now[fe_now_idx]) != 0)
  {
    free(fe->key);
    free(fe);
    free(fe_now->value);
    fe_idx = &fe_now[fe_now_idx];
  }
  fe->cb = 0;
  fe->t = 0;
  __builtin_va_start(ap);
  xvasprintf(&fe->value, fmt, ap);
  ;
}


----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
None
----------------------------
***/


static int window_copy_is_lowercase(const char *ptr)
{
  unsigned int ptr_idx = 0;
  while (ptr[ptr_idx] != '\0')
  {
    if (ptr[ptr_idx] != tolower((u_char) ptr[ptr_idx]))
    {
      return 0;
    }
    ptr_idx += 1;
  }

  return 1;
}


/*** DEPENDENCIES:
***/


static void window_copy_move_left(struct screen *s, u_int *fx, u_int *fy)
{
  if ((*fx) == 0)
  {
    if ((*fy) == 0)
    {
      return;
    }
    *fx = s->grid->sx - 1;
    *fy = (*fy) - 1;
  }
  else
    *fx = (*fx) - 1;
}


/*** DEPENDENCIES:
None
----------------------------
***/


static void window_copy_move_right(struct screen *s, u_int *fx, u_int *fy)
{
  if ((*fx) == (s->grid->sx - 1))
  {
    if ((*fy) == (s->grid->hsize + s->grid->sy))
    {
      return;
    }
    *fx = 0;
    *fy = (*fy) + 1;
  }
  else
    *fx = (*fx) + 1;
}


/*** DEPENDENCIES:
None
----------------------------
***/


static int window_copy_search_compare(struct grid *gd, u_int px, u_int py, struct grid *sgd, u_int spx, int cis)
{
  struct grid_cell gc;
  struct grid_cell sgc;
  const struct utf8_data *ud;
  unsigned int ud_idx = 0;
  const struct utf8_data *sud;
  unsigned int sud_idx = 0;
  grid_get_cell(gd, px, py, &gc);
  ud_idx = &gc.data;
  grid_get_cell(sgd, spx, 0, &sgc);
  sud_idx = &sgc.data;
  if ((ud->size != sud->size) || (ud->width != sud->width))
  {
    return 0;
  }
  if (cis && (ud->size == 1))
  {
    return tolower(ud->data[0]) == sud->data[0];
  }
  return memcmp(ud->data, sud->data, ud->size) == 0;
}


/*** DEPENDENCIES:
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
None
----------------------------
***/


static int window_copy_search_lr(struct grid *gd, struct grid *sgd, u_int *ppx, u_int py, u_int first, u_int last, int cis)
{
  u_int ax;
  u_int bx;
  u_int px;
  int matched;
  for (ax = first; ax < last; ax += 1)
  {
    if ((ax + sgd->sx) > gd->sx)
    {
      break;
    }
    for (bx = 0; bx < sgd->sx; bx += 1)
    {
      px = ax + bx;
      matched = window_copy_search_compare(gd, px, py, sgd, bx, cis);
      if (!matched)
      {
        break;
      }
    }

    if (bx == sgd->sx)
    {
      *ppx = ax;
      return 1;
    }
  }

  return 0;
}


/*** DEPENDENCIES:
static int window_copy_search_compare(struct grid *gd, u_int px, u_int py, struct grid *sgd, u_int spx, int cis)
{
  struct grid_cell gc;
  struct grid_cell sgc;
  const struct utf8_data *ud;
  unsigned int ud_idx = 0;
  const struct utf8_data *sud;
  unsigned int sud_idx = 0;
  grid_get_cell(gd, px, py, &gc);
  ud_idx = &gc.data;
  grid_get_cell(sgd, spx, 0, &sgc);
  sud_idx = &sgc.data;
  if ((ud->size != sud->size) || (ud->width != sud->width))
  {
    return 0;
  }
  if (cis && (ud->size == 1))
  {
    return tolower(ud->data[0]) == sud->data[0];
  }
  return memcmp(ud->data, sud->data, ud->size) == 0;
}


----------------------------
None
----------------------------
***/


static int window_copy_search_rl(struct grid *gd, struct grid *sgd, u_int *ppx, u_int py, u_int first, u_int last, int cis)
{
  u_int ax;
  u_int bx;
  u_int px;
  int matched;
  for (ax = last + 1; ax > first; ax -= 1)
  {
    if ((gd->sx - (ax - 1)) < sgd->sx)
    {
      continue;
    }
    for (bx = 0; bx < sgd->sx; bx += 1)
    {
      px = (ax - 1) + bx;
      matched = window_copy_search_compare(gd, px, py, sgd, bx, cis);
      if (!matched)
      {
        break;
      }
    }

    if (bx == sgd->sx)
    {
      *ppx = ax - 1;
      return 1;
    }
  }

  return 0;
}


/*** DEPENDENCIES:
static int window_copy_search_compare(struct grid *gd, u_int px, u_int py, struct grid *sgd, u_int spx, int cis)
{
  struct grid_cell gc;
  struct grid_cell sgc;
  const struct utf8_data *ud;
  unsigned int ud_idx = 0;
  const struct utf8_data *sud;
  unsigned int sud_idx = 0;
  grid_get_cell(gd, px, py, &gc);
  ud_idx = &gc.data;
  grid_get_cell(sgd, spx, 0, &sgc);
  sud_idx = &sgc.data;
  if ((ud->size != sud->size) || (ud->width != sud->width))
  {
    return 0;
  }
  if (cis && (ud->size == 1))
  {
    return tolower(ud->data[0]) == sud->data[0];
  }
  return memcmp(ud->data, sud->data, ud->size) == 0;
}


----------------------------
None
----------------------------
***/


// hint:  ['firstsx_ref is a mutable refrence to u_int', 'lastex_ref is a mutable refrence to u_int', 'restex_ref is a mutable refrence to u_int', 'restsx_ref is a mutable refrence to u_int', 'selx_ref is a mutable refrence to u_int']
void helper_window_copy_get_selection_1(u_int * const firstsx_ref, u_int * const lastex_ref, u_int * const restex_ref, u_int * const restsx_ref, u_int * const selx_ref, struct window_copy_mode_data * const data, int keys)
{
  u_int firstsx = *firstsx_ref;
  u_int lastex = *lastex_ref;
  u_int restex = *restex_ref;
  u_int restsx = *restsx_ref;
  u_int selx = *selx_ref;
  if (data->cursordrag == CURSORDRAG_ENDSEL)
  {
    selx = data->selx;
  }
  else
    selx = data->endselx;
  if (selx < data->cx)
  {
    if (keys == 0)
    {
      lastex = data->cx;
      restex = data->cx;
    }
    else
    {
      lastex = data->cx + 1;
      restex = data->cx + 1;
    }
    firstsx = selx;
    restsx = selx;
  }
  else
  {
    lastex = selx + 1;
    restex = selx + 1;
    firstsx = data->cx;
    restsx = data->cx;
  }
  *firstsx_ref = firstsx;
  *lastex_ref = lastex;
  *restex_ref = restex;
  *restsx_ref = restsx;
  *selx_ref = selx;
}


/*** DEPENDENCIES:
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
None
----------------------------
***/


void window_copy_init_for_output(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  data->backing = xmalloc(sizeof(*data->backing));
  screen_init(data->backing, (&wp->base)->grid->sx, (&wp->base)->grid->sy, 4294967295U);
}


/*** DEPENDENCIES:
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
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
None
----------------------------
***/


static void window_copy_write_line(struct window_pane *wp, struct screen_write_ctx *ctx, u_int py)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct options *oo = wp->window->options;
  struct grid_cell gc;
  char hdr[512];
  size_t size = 0;
  style_apply(&gc, oo, "mode-style");
  gc.flags |= 0x20;
  if (py == 0)
  {
    if (data->searchmark == 0)
    {
      size = xsnprintf(hdr, sizeof(hdr), "[%u/%u]", data->oy, data->backing->grid->hsize);
    }
    else
    {
      if (data->searchthis == (-1))
      {
        size = xsnprintf(hdr, sizeof(hdr), "(%u results) [%d/%u]", data->searchcount, data->oy, data->backing->grid->hsize);
      }
      else
      {
        size = xsnprintf(hdr, sizeof(hdr), "(%u/%u results) [%d/%u]", data->searchthis, data->searchcount, data->oy, data->backing->grid->hsize);
      }
    }
    if (size > s->grid->sx)
    {
      size = s->grid->sx;
    }
    screen_write_cursormove(ctx, s->grid->sx - size, 0);
    screen_write_puts(ctx, &gc, "%s", hdr);
  }
  else
    size = 0;
  if (size < s->grid->sx)
  {
    screen_write_cursormove(ctx, 0, py);
    screen_write_copy(ctx, data->backing, 0, (data->backing->grid->hsize - data->oy) + py, s->grid->sx - size, 1, data->searchmark, &gc);
  }
  if ((py == data->cy) && (data->cx == s->grid->sx))
  {
    memcpy(&gc, &grid_default_cell, sizeof(gc));
    screen_write_cursormove(ctx, s->grid->sx - 1, py);
    screen_write_putc(ctx, &gc, '$');
  }
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
extern const struct grid_cell grid_default_cell
----------------------------
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
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
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
void screen_write_puts(struct screen_write_ctx *ctx, const struct grid_cell *gcp, const char *fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  screen_write_vnputs(ctx, -1, gcp, fmt, ap);
  ;
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
None
----------------------------
***/


static void window_copy_redraw_lines(struct window_pane *wp, u_int py, u_int ny)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen_write_ctx ctx;
  u_int i;
  screen_write_start(&ctx, wp, 0);
  for (i = py; i < (py + ny); i += 1)
  {
    window_copy_write_line(wp, &ctx, i);
  }

  screen_write_cursormove(&ctx, data->cx, data->cy);
  screen_write_stop(&ctx);
}


/*** DEPENDENCIES:
static void window_copy_write_line(struct window_pane *wp, struct screen_write_ctx *ctx, u_int py)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct options *oo = wp->window->options;
  struct grid_cell gc;
  char hdr[512];
  size_t size = 0;
  style_apply(&gc, oo, "mode-style");
  gc.flags |= 0x20;
  if (py == 0)
  {
    if (data->searchmark == 0)
    {
      size = xsnprintf(hdr, sizeof(hdr), "[%u/%u]", data->oy, data->backing->grid->hsize);
    }
    else
    {
      if (data->searchthis == (-1))
      {
        size = xsnprintf(hdr, sizeof(hdr), "(%u results) [%d/%u]", data->searchcount, data->oy, data->backing->grid->hsize);
      }
      else
      {
        size = xsnprintf(hdr, sizeof(hdr), "(%u/%u results) [%d/%u]", data->searchthis, data->searchcount, data->oy, data->backing->grid->hsize);
      }
    }
    if (size > s->grid->sx)
    {
      size = s->grid->sx;
    }
    screen_write_cursormove(ctx, s->grid->sx - size, 0);
    screen_write_puts(ctx, &gc, "%s", hdr);
  }
  else
    size = 0;
  if (size < s->grid->sx)
  {
    screen_write_cursormove(ctx, 0, py);
    screen_write_copy(ctx, data->backing, 0, (data->backing->grid->hsize - data->oy) + py, s->grid->sx - size, 1, data->searchmark, &gc);
  }
  if ((py == data->cy) && (data->cx == s->grid->sx))
  {
    memcpy(&gc, &grid_default_cell, sizeof(gc));
    screen_write_cursormove(ctx, s->grid->sx - 1, py);
    screen_write_putc(ctx, &gc, '$');
  }
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
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
None
----------------------------
None
----------------------------
***/


void window_copy_vadd(struct window_pane *wp, const char *fmt, va_list ap)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *backing = data->backing;
  struct screen_write_ctx back_ctx;
  struct screen_write_ctx ctx;
  struct grid_cell gc;
  u_int old_hsize;
  u_int old_cy;
  if (backing == (&wp->base))
  {
    return;
  }
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  old_hsize = data->backing->grid->hsize;
  screen_write_start(&back_ctx, 0, backing);
  if (data->backing_written)
  {
    screen_write_carriagereturn(&back_ctx);
    screen_write_linefeed(&back_ctx, 0, 8);
  }
  else
    data->backing_written = 1;
  old_cy = backing->cy;
  screen_write_vnputs(&back_ctx, 0, &gc, fmt, ap);
  screen_write_stop(&back_ctx);
  data->oy += data->backing->grid->hsize - old_hsize;
  screen_write_start(&ctx, wp, &data->screen);
  if (data->backing->grid->hsize)
  {
    window_copy_redraw_lines(wp, 0, 1);
  }
  window_copy_redraw_lines(wp, old_cy, (backing->cy - old_cy) + 1);
  screen_write_stop(&ctx);
}


/*** DEPENDENCIES:
void screen_write_carriagereturn(struct screen_write_ctx *ctx)
{
  struct screen *s = ctx->s;
  s->cx = 0;
}


----------------------------
extern const struct grid_cell grid_default_cell
----------------------------
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


----------------------------
static void window_copy_redraw_lines(struct window_pane *wp, u_int py, u_int ny)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen_write_ctx ctx;
  u_int i;
  screen_write_start(&ctx, wp, 0);
  for (i = py; i < (py + ny); i += 1)
  {
    window_copy_write_line(wp, &ctx, i);
  }

  screen_write_cursormove(&ctx, data->cx, data->cy);
  screen_write_stop(&ctx);
}


----------------------------
None
----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
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
None
----------------------------
***/


static const char *window_copy_key_table(struct window_pane *wp)
{
  if (options_get_number(wp->window->options, "mode-keys") == 1)
  {
    return "copy-mode-vi";
  }
  return "copy-mode";
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


static void window_copy_clear_marks(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  free(data->searchmark);
  data->searchmark = 0;
}


/*** DEPENDENCIES:
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
None
----------------------------
***/


// hint:  ['found_ref is a mutable refrence to int', 'which_ref is a mutable refrence to int', 'px_ref is a mutable refrence to u_int', 'b_ref is a mutable refrence to u_int', 'nfound_ref is a mutable refrence to u_int']
void helper_window_copy_search_marks_1(int * const found_ref, int * const which_ref, u_int * const px_ref, u_int * const b_ref, u_int * const nfound_ref, struct screen * const ssp, struct window_copy_mode_data * const data, struct grid * const gd, int cis, u_int py, u_int width)
{
  int found = *found_ref;
  int which = *which_ref;
  u_int px = *px_ref;
  u_int b = *b_ref;
  u_int nfound = *nfound_ref;
  px = 0;
  for (;;)
  {
    found = window_copy_search_lr(gd, ssp->grid, &px, py, px, gd->sx, cis);
    if (!found)
    {
      break;
    }
    nfound += 1;
    if ((px == data->cx) && (py == ((gd->hsize + data->cy) - data->oy)))
    {
      which = nfound;
    }
    b = (py * gd->sx) + px;
    do
    {
      register bitstr_t *_name = data->searchmark;
      register int _start = b;
      register int _stop = (b + width) - 1;
      while (_start <= _stop)
      {
        _name[_start >> 3] |= 1 << (_start & 0x7);
        _start += 1;
      }

    }
    while (0);
    px += 1;
  }

  *found_ref = found;
  *which_ref = which;
  *px_ref = px;
  *b_ref = b;
  *nfound_ref = nfound;
}


/*** DEPENDENCIES:
typedef unsigned char bitstr_t
----------------------------
None
----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
static int window_copy_search_lr(struct grid *gd, struct grid *sgd, u_int *ppx, u_int py, u_int first, u_int last, int cis)
{
  u_int ax;
  u_int bx;
  u_int px;
  int matched;
  for (ax = first; ax < last; ax += 1)
  {
    if ((ax + sgd->sx) > gd->sx)
    {
      break;
    }
    for (bx = 0; bx < sgd->sx; bx += 1)
    {
      px = ax + bx;
      matched = window_copy_search_compare(gd, px, py, sgd, bx, cis);
      if (!matched)
      {
        break;
      }
    }

    if (bx == sgd->sx)
    {
      *ppx = ax;
      return 1;
    }
  }

  return 0;
}


----------------------------
None
----------------------------
None
----------------------------
***/


static int window_copy_search_marks(struct window_pane *wp, struct screen *ssp)
{
  unsigned int ssp_idx = 0;
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = data->backing;
  struct screen ss;
  struct screen_write_ctx ctx;
  struct grid *gd = s->grid;
  int found;
  int cis;
  int which = -1;
  u_int px;
  u_int py;
  u_int b;
  u_int nfound = 0;
  u_int width;
  if ((&ssp[ssp_idx]) == 0)
  {
    width = screen_write_strlen("%s", data->searchstr);
    screen_init(&ss, width, 1, 0);
    screen_write_start(&ctx, 0, &ss);
    screen_write_nputs(&ctx, -1, &grid_default_cell, "%s", data->searchstr);
    screen_write_stop(&ctx);
    ssp_idx = &ss;
  }
  else
    width = ssp->grid->sx;
  cis = window_copy_is_lowercase(data->searchstr);
  free(data->searchmark);
  data->searchmark = (bitstr_t *) calloc((size_t) ((((gd->hsize + gd->sy) * gd->sx) + 7) >> 3), sizeof(bitstr_t));
  for (py = 0; py < (gd->hsize + gd->sy); py += 1)
  {
    helper_window_copy_search_marks_1(&found, &which, &px, &b, &nfound, ssp, data, gd, cis, py, width);
  }

  if (which != (-1))
  {
    data->searchthis = (1 + nfound) - which;
  }
  else
    data->searchthis = -1;
  data->searchcount = nfound;
  if ((&ssp[ssp_idx]) == (&ss))
  {
    screen_free(&ss);
  }
  return nfound;
}


/*** DEPENDENCIES:
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
extern const struct grid_cell grid_default_cell
----------------------------
None
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
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
size_t screen_write_strlen(const char *fmt, ...)
{
  va_list ap;
  char *msg;
  struct utf8_data ud;
  u_char *ptr;
  unsigned int ptr_idx = 0;
  size_t left;
  size_t size = 0;
  enum utf8_state more;
  __builtin_va_start(ap);
  xvasprintf(&msg, fmt, ap);
  ;
  ptr_idx = msg;
  while (ptr[ptr_idx] != '\0')
  {
    if ((ptr[ptr_idx] > 0x7f) && (utf8_open(&ud, *(&ptr[ptr_idx])) == UTF8_MORE))
    {
      ptr_idx += 1;
      left = strlen(ptr);
      if (left < (((size_t) ud.size) - 1))
      {
        break;
      }
      while ((more = utf8_append(&ud, *(&ptr[ptr_idx]))) == UTF8_MORE)
      {
        ptr_idx += 1;
      }

      ptr_idx += 1;
      if (more == UTF8_DONE)
      {
        size += ud.width;
      }
    }
    else
    {
      if ((ptr[ptr_idx] > 0x1f) && (ptr[ptr_idx] < 0x7f))
      {
        size += 1;
      }
      ptr_idx += 1;
    }
  }

  free(msg);
  return size;
}


----------------------------
void helper_window_copy_search_marks_1(int * const found_ref, int * const which_ref, u_int * const px_ref, u_int * const b_ref, u_int * const nfound_ref, struct screen * const ssp, struct window_copy_mode_data * const data, struct grid * const gd, int cis, u_int py, u_int width)
{
  int found = *found_ref;
  int which = *which_ref;
  u_int px = *px_ref;
  u_int b = *b_ref;
  u_int nfound = *nfound_ref;
  px = 0;
  for (;;)
  {
    found = window_copy_search_lr(gd, ssp->grid, &px, py, px, gd->sx, cis);
    if (!found)
    {
      break;
    }
    nfound += 1;
    if ((px == data->cx) && (py == ((gd->hsize + data->cy) - data->oy)))
    {
      which = nfound;
    }
    b = (py * gd->sx) + px;
    do
    {
      register bitstr_t *_name = data->searchmark;
      register int _start = b;
      register int _stop = (b + width) - 1;
      while (_start <= _stop)
      {
        _name[_start >> 3] |= 1 << (_start & 0x7);
        _start += 1;
      }

    }
    while (0);
    px += 1;
  }

  *found_ref = found;
  *which_ref = which;
  *px_ref = px;
  *b_ref = b;
  *nfound_ref = nfound;
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
void screen_write_nputs(struct screen_write_ctx *ctx, ssize_t maxlen, const struct grid_cell *gcp, const char *fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  screen_write_vnputs(ctx, maxlen, gcp, fmt, ap);
  ;
}


----------------------------
static int window_copy_is_lowercase(const char *ptr)
{
  unsigned int ptr_idx = 0;
  while (ptr[ptr_idx] != '\0')
  {
    if (ptr[ptr_idx] != tolower((u_char) ptr[ptr_idx]))
    {
      return 0;
    }
    ptr_idx += 1;
  }

  return 1;
}


----------------------------
None
----------------------------
None
----------------------------
***/


static void window_copy_redraw_screen(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  window_copy_redraw_lines(wp, 0, (&data->screen)->grid->sy);
}


/*** DEPENDENCIES:
static void window_copy_redraw_lines(struct window_pane *wp, u_int py, u_int ny)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen_write_ctx ctx;
  u_int i;
  screen_write_start(&ctx, wp, 0);
  for (i = py; i < (py + ny); i += 1)
  {
    window_copy_write_line(wp, &ctx, i);
  }

  screen_write_cursormove(&ctx, data->cx, data->cy);
  screen_write_stop(&ctx);
}


----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
None
----------------------------
***/


static int window_copy_adjust_selection(struct window_pane *wp, u_int *selx, u_int *sely)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  u_int sx;
  u_int sy;
  u_int ty;
  int relpos;
  sx = *selx;
  sy = *sely;
  ty = data->backing->grid->hsize - data->oy;
  if (sy < ty)
  {
    relpos = WINDOW_COPY_REL_POS_ABOVE;
    if (!data->rectflag)
    {
      sx = 0;
    }
    sy = 0;
  }
  else
    if (sy > ((ty + s->grid->sy) - 1))
  {
    relpos = WINDOW_COPY_REL_POS_BELOW;
    if (!data->rectflag)
    {
      sx = s->grid->sx - 1;
    }
    sy = s->grid->sy - 1;
  }
  else
  {
    relpos = WINDOW_COPY_REL_POS_ON_SCREEN;
    sy -= ty;
  }
  *selx = sx;
  *sely = sy;
  return relpos;
}


/*** DEPENDENCIES:
None
----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
None
----------------------------
***/


static void window_copy_synchronize_cursor(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  u_int xx;
  u_int yy;
  xx = data->cx;
  yy = (data->backing->grid->hsize + data->cy) - data->oy;
  switch (data->cursordrag)
  {
    case CURSORDRAG_ENDSEL:
    {
      data->endselx = xx;
      data->endsely = yy;
      break;
    }

    case CURSORDRAG_SEL:
    {
      data->selx = xx;
      data->sely = yy;
      break;
    }

    case CURSORDRAG_NONE:
    {
      break;
    }

  }

}


/*** DEPENDENCIES:
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
None
----------------------------
***/


static int window_copy_update_selection(struct window_pane *wp, int may_redraw)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct options *oo = wp->window->options;
  struct grid_cell gc;
  u_int sx;
  u_int sy;
  u_int cy;
  u_int endsx;
  u_int endsy;
  int startrelpos;
  int endrelpos;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return 0;
  }
  window_copy_synchronize_cursor(wp);
  sx = data->selx;
  sy = data->sely;
  startrelpos = window_copy_adjust_selection(wp, &sx, &sy);
  endsx = data->endselx;
  endsy = data->endsely;
  endrelpos = window_copy_adjust_selection(wp, &endsx, &endsy);
  if ((startrelpos == endrelpos) && (startrelpos != WINDOW_COPY_REL_POS_ON_SCREEN))
  {
    screen_hide_selection(s);
    return 0;
  }
  style_apply(&gc, oo, "mode-style");
  gc.flags |= 0x20;
  screen_set_selection(s, sx, sy, endsx, endsy, data->rectflag, &gc);
  if (data->rectflag && may_redraw)
  {
    cy = data->cy;
    if (data->cursordrag == CURSORDRAG_ENDSEL)
    {
      if (sy < cy)
      {
        window_copy_redraw_lines(wp, sy, (cy - sy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (sy - cy) + 1);
    }
    else
    {
      if (endsy < cy)
      {
        window_copy_redraw_lines(wp, endsy, (cy - endsy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (endsy - cy) + 1);
    }
  }
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
static void window_copy_redraw_lines(struct window_pane *wp, u_int py, u_int ny)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen_write_ctx ctx;
  u_int i;
  screen_write_start(&ctx, wp, 0);
  for (i = py; i < (py + ny); i += 1)
  {
    window_copy_write_line(wp, &ctx, i);
  }

  screen_write_cursormove(&ctx, data->cx, data->cy);
  screen_write_stop(&ctx);
}


----------------------------
None
----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
static int window_copy_adjust_selection(struct window_pane *wp, u_int *selx, u_int *sely)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  u_int sx;
  u_int sy;
  u_int ty;
  int relpos;
  sx = *selx;
  sy = *sely;
  ty = data->backing->grid->hsize - data->oy;
  if (sy < ty)
  {
    relpos = WINDOW_COPY_REL_POS_ABOVE;
    if (!data->rectflag)
    {
      sx = 0;
    }
    sy = 0;
  }
  else
    if (sy > ((ty + s->grid->sy) - 1))
  {
    relpos = WINDOW_COPY_REL_POS_BELOW;
    if (!data->rectflag)
    {
      sx = s->grid->sx - 1;
    }
    sy = s->grid->sy - 1;
  }
  else
  {
    relpos = WINDOW_COPY_REL_POS_ON_SCREEN;
    sy -= ty;
  }
  *selx = sx;
  *sely = sy;
  return relpos;
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
void screen_set_selection(struct screen *s, u_int sx, u_int sy, u_int ex, u_int ey, u_int rectflag, struct grid_cell *gc)
{
  struct screen_sel *sel = &s->sel;
  memcpy(&sel->cell, gc, sizeof(sel->cell));
  sel->flag = 1;
  sel->hidden = 0;
  sel->rectflag = rectflag;
  sel->sx = sx;
  sel->sy = sy;
  sel->ex = ex;
  sel->ey = ey;
}


----------------------------
static void window_copy_synchronize_cursor(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  u_int xx;
  u_int yy;
  xx = data->cx;
  yy = (data->backing->grid->hsize + data->cy) - data->oy;
  switch (data->cursordrag)
  {
    case CURSORDRAG_ENDSEL:
    {
      data->endselx = xx;
      data->endsely = yy;
      break;
    }

    case CURSORDRAG_SEL:
    {
      data->selx = xx;
      data->sely = yy;
      break;
    }

    case CURSORDRAG_NONE:
    {
      break;
    }

  }

}


----------------------------
None
----------------------------
void screen_hide_selection(struct screen *s)
{
  struct screen_sel *sel = &s->sel;
  sel->hidden = 1;
}


----------------------------
None
----------------------------
None
----------------------------
***/


static void window_copy_scroll_to(struct window_pane *wp, u_int px, u_int py)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct grid *gd = data->backing->grid;
  u_int offset;
  u_int gap;
  data->cx = px;
  if ((py >= (gd->hsize - data->oy)) && (py < ((gd->hsize - data->oy) + gd->sy)))
  {
    data->cy = py - (gd->hsize - data->oy);
  }
  else
  {
    gap = gd->sy / 4;
    if (py < gd->sy)
    {
      offset = 0;
      data->cy = py;
    }
    else
      if (py > ((gd->hsize + gd->sy) - gap))
    {
      offset = gd->hsize;
      data->cy = py - gd->hsize;
    }
    else
    {
      offset = (py + gap) - gd->sy;
      data->cy = py - offset;
    }
    data->oy = gd->hsize - offset;
  }
  window_copy_update_selection(wp, 1);
  window_copy_redraw_screen(wp);
}


/*** DEPENDENCIES:
static void window_copy_redraw_screen(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  window_copy_redraw_lines(wp, 0, (&data->screen)->grid->sy);
}


----------------------------
None
----------------------------
static int window_copy_update_selection(struct window_pane *wp, int may_redraw)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct options *oo = wp->window->options;
  struct grid_cell gc;
  u_int sx;
  u_int sy;
  u_int cy;
  u_int endsx;
  u_int endsy;
  int startrelpos;
  int endrelpos;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return 0;
  }
  window_copy_synchronize_cursor(wp);
  sx = data->selx;
  sy = data->sely;
  startrelpos = window_copy_adjust_selection(wp, &sx, &sy);
  endsx = data->endselx;
  endsy = data->endsely;
  endrelpos = window_copy_adjust_selection(wp, &endsx, &endsy);
  if ((startrelpos == endrelpos) && (startrelpos != WINDOW_COPY_REL_POS_ON_SCREEN))
  {
    screen_hide_selection(s);
    return 0;
  }
  style_apply(&gc, oo, "mode-style");
  gc.flags |= 0x20;
  screen_set_selection(s, sx, sy, endsx, endsy, data->rectflag, &gc);
  if (data->rectflag && may_redraw)
  {
    cy = data->cy;
    if (data->cursordrag == CURSORDRAG_ENDSEL)
    {
      if (sy < cy)
      {
        window_copy_redraw_lines(wp, sy, (cy - sy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (sy - cy) + 1);
    }
    else
    {
      if (endsy < cy)
      {
        window_copy_redraw_lines(wp, endsy, (cy - endsy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (endsy - cy) + 1);
    }
  }
  return 1;
}


----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
None
----------------------------
***/


static int window_copy_search_jump(struct window_pane *wp, struct grid *gd, struct grid *sgd, u_int fx, u_int fy, u_int endline, int cis, int wrap, int direction)
{
  u_int i;
  u_int px;
  int found;
  found = 0;
  if (direction)
  {
    for (i = fy; i <= endline; i += 1)
    {
      found = window_copy_search_lr(gd, sgd, &px, i, fx, gd->sx, cis);
      if (found)
      {
        break;
      }
      fx = 0;
    }

  }
  else
  {
    for (i = fy + 1; endline < i; i -= 1)
    {
      found = window_copy_search_rl(gd, sgd, &px, i - 1, 0, fx, cis);
      if (found)
      {
        i -= 1;
        break;
      }
      fx = gd->sx;
    }

  }
  if (found)
  {
    window_copy_scroll_to(wp, px, i);
    return 1;
  }
  if (wrap)
  {
    return window_copy_search_jump(wp, gd, sgd, (direction) ? (0) : (gd->sx - 1), (direction) ? (0) : ((gd->hsize + gd->sy) - 1), fy, cis, 0, direction);
  }
  return 0;
}


/*** DEPENDENCIES:
static int window_copy_search_lr(struct grid *gd, struct grid *sgd, u_int *ppx, u_int py, u_int first, u_int last, int cis)
{
  u_int ax;
  u_int bx;
  u_int px;
  int matched;
  for (ax = first; ax < last; ax += 1)
  {
    if ((ax + sgd->sx) > gd->sx)
    {
      break;
    }
    for (bx = 0; bx < sgd->sx; bx += 1)
    {
      px = ax + bx;
      matched = window_copy_search_compare(gd, px, py, sgd, bx, cis);
      if (!matched)
      {
        break;
      }
    }

    if (bx == sgd->sx)
    {
      *ppx = ax;
      return 1;
    }
  }

  return 0;
}


----------------------------
None
----------------------------
static void window_copy_scroll_to(struct window_pane *wp, u_int px, u_int py)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct grid *gd = data->backing->grid;
  u_int offset;
  u_int gap;
  data->cx = px;
  if ((py >= (gd->hsize - data->oy)) && (py < ((gd->hsize - data->oy) + gd->sy)))
  {
    data->cy = py - (gd->hsize - data->oy);
  }
  else
  {
    gap = gd->sy / 4;
    if (py < gd->sy)
    {
      offset = 0;
      data->cy = py;
    }
    else
      if (py > ((gd->hsize + gd->sy) - gap))
    {
      offset = gd->hsize;
      data->cy = py - gd->hsize;
    }
    else
    {
      offset = (py + gap) - gd->sy;
      data->cy = py - offset;
    }
    data->oy = gd->hsize - offset;
  }
  window_copy_update_selection(wp, 1);
  window_copy_redraw_screen(wp);
}


----------------------------
static int window_copy_search_rl(struct grid *gd, struct grid *sgd, u_int *ppx, u_int py, u_int first, u_int last, int cis)
{
  u_int ax;
  u_int bx;
  u_int px;
  int matched;
  for (ax = last + 1; ax > first; ax -= 1)
  {
    if ((gd->sx - (ax - 1)) < sgd->sx)
    {
      continue;
    }
    for (bx = 0; bx < sgd->sx; bx += 1)
    {
      px = (ax - 1) + bx;
      matched = window_copy_search_compare(gd, px, py, sgd, bx, cis);
      if (!matched)
      {
        break;
      }
    }

    if (bx == sgd->sx)
    {
      *ppx = ax - 1;
      return 1;
    }
  }

  return 0;
}


----------------------------
None
----------------------------
***/


static u_int window_copy_find_length(struct window_pane *wp, u_int py)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = data->backing;
  struct grid_cell gc;
  u_int px;
  px = s->grid->linedata[py].cellsize;
  if (px > s->grid->sx)
  {
    px = s->grid->sx;
  }
  while (px > 0)
  {
    grid_get_cell(s->grid, px - 1, py, &gc);
    if ((gc.data.size != 1) || ((*gc.data.data) != ' '))
    {
      break;
    }
    px -= 1;
  }

  return px;
}


/*** DEPENDENCIES:
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
None
----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
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


static void window_copy_update_cursor(struct window_pane *wp, u_int cx, u_int cy)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct screen_write_ctx ctx;
  u_int old_cx;
  u_int old_cy;
  old_cx = data->cx;
  old_cy = data->cy;
  data->cx = cx;
  data->cy = cy;
  if (old_cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, old_cy, 1);
  }
  if (data->cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, data->cy, 1);
  }
  else
  {
    screen_write_start(&ctx, wp, 0);
    screen_write_cursormove(&ctx, data->cx, data->cy);
    screen_write_stop(&ctx);
  }
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
static void window_copy_redraw_lines(struct window_pane *wp, u_int py, u_int ny)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen_write_ctx ctx;
  u_int i;
  screen_write_start(&ctx, wp, 0);
  for (i = py; i < (py + ny); i += 1)
  {
    window_copy_write_line(wp, &ctx, i);
  }

  screen_write_cursormove(&ctx, data->cx, data->cy);
  screen_write_stop(&ctx);
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
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
None
----------------------------
None
----------------------------
***/


static void window_copy_clear_selection(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  u_int px;
  u_int py;
  screen_clear_selection(&data->screen);
  data->cursordrag = CURSORDRAG_NONE;
  py = (data->backing->grid->hsize + data->cy) - data->oy;
  px = window_copy_find_length(wp, py);
  if (data->cx > px)
  {
    window_copy_update_cursor(wp, px, data->cy);
  }
}


/*** DEPENDENCIES:
void screen_clear_selection(struct screen *s)
{
  struct screen_sel *sel = &s->sel;
  sel->flag = 0;
  sel->hidden = 0;
  sel->lineflag = LINE_SEL_NONE;
}


----------------------------
static u_int window_copy_find_length(struct window_pane *wp, u_int py)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = data->backing;
  struct grid_cell gc;
  u_int px;
  px = s->grid->linedata[py].cellsize;
  if (px > s->grid->sx)
  {
    px = s->grid->sx;
  }
  while (px > 0)
  {
    grid_get_cell(s->grid, px - 1, py, &gc);
    if ((gc.data.size != 1) || ((*gc.data.data) != ' '))
    {
      break;
    }
    px -= 1;
  }

  return px;
}


----------------------------
static void window_copy_update_cursor(struct window_pane *wp, u_int cx, u_int cy)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct screen_write_ctx ctx;
  u_int old_cx;
  u_int old_cy;
  old_cx = data->cx;
  old_cy = data->cy;
  data->cx = cx;
  data->cy = cy;
  if (old_cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, old_cy, 1);
  }
  if (data->cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, data->cy, 1);
  }
  else
  {
    screen_write_start(&ctx, wp, 0);
    screen_write_cursormove(&ctx, data->cx, data->cy);
    screen_write_stop(&ctx);
  }
}


----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
None
----------------------------
***/


static int window_copy_search(struct window_pane *wp, int direction)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = data->backing;
  struct screen ss;
  struct screen_write_ctx ctx;
  struct grid *gd = s->grid;
  u_int fx;
  u_int fy;
  u_int endline;
  int wrapflag;
  int cis;
  int found;
  free(wp->searchstr);
  wp->searchstr = xstrdup(data->searchstr);
  fx = data->cx;
  fy = (data->backing->grid->hsize - data->oy) + data->cy;
  screen_init(&ss, screen_write_strlen("%s", data->searchstr), 1, 0);
  screen_write_start(&ctx, 0, &ss);
  screen_write_nputs(&ctx, -1, &grid_default_cell, "%s", data->searchstr);
  screen_write_stop(&ctx);
  if (direction)
  {
    window_copy_move_right(s, &fx, &fy);
  }
  else
    window_copy_move_left(s, &fx, &fy);
  window_copy_clear_selection(wp);
  wrapflag = options_get_number(wp->window->options, "wrap-search");
  cis = window_copy_is_lowercase(data->searchstr);
  if (direction)
  {
    endline = (gd->hsize + gd->sy) - 1;
  }
  else
    endline = 0;
  found = window_copy_search_jump(wp, gd, ss.grid, fx, fy, endline, cis, wrapflag, direction);
  if (window_copy_search_marks(wp, &ss))
  {
    window_copy_redraw_screen(wp);
  }
  screen_free(&ss);
  return found;
}


/*** DEPENDENCIES:
static void window_copy_move_left(struct screen *s, u_int *fx, u_int *fy)
{
  if ((*fx) == 0)
  {
    if ((*fy) == 0)
    {
      return;
    }
    *fx = s->grid->sx - 1;
    *fy = (*fy) - 1;
  }
  else
    *fx = (*fx) - 1;
}


----------------------------
static int window_copy_search_marks(struct window_pane *wp, struct screen *ssp)
{
  unsigned int ssp_idx = 0;
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = data->backing;
  struct screen ss;
  struct screen_write_ctx ctx;
  struct grid *gd = s->grid;
  int found;
  int cis;
  int which = -1;
  u_int px;
  u_int py;
  u_int b;
  u_int nfound = 0;
  u_int width;
  if ((&ssp[ssp_idx]) == 0)
  {
    width = screen_write_strlen("%s", data->searchstr);
    screen_init(&ss, width, 1, 0);
    screen_write_start(&ctx, 0, &ss);
    screen_write_nputs(&ctx, -1, &grid_default_cell, "%s", data->searchstr);
    screen_write_stop(&ctx);
    ssp_idx = &ss;
  }
  else
    width = ssp->grid->sx;
  cis = window_copy_is_lowercase(data->searchstr);
  free(data->searchmark);
  data->searchmark = (bitstr_t *) calloc((size_t) ((((gd->hsize + gd->sy) * gd->sx) + 7) >> 3), sizeof(bitstr_t));
  for (py = 0; py < (gd->hsize + gd->sy); py += 1)
  {
    helper_window_copy_search_marks_1(&found, &which, &px, &b, &nfound, ssp, data, gd, cis, py, width);
  }

  if (which != (-1))
  {
    data->searchthis = (1 + nfound) - which;
  }
  else
    data->searchthis = -1;
  data->searchcount = nfound;
  if ((&ssp[ssp_idx]) == (&ss))
  {
    screen_free(&ss);
  }
  return nfound;
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
size_t screen_write_strlen(const char *fmt, ...)
{
  va_list ap;
  char *msg;
  struct utf8_data ud;
  u_char *ptr;
  unsigned int ptr_idx = 0;
  size_t left;
  size_t size = 0;
  enum utf8_state more;
  __builtin_va_start(ap);
  xvasprintf(&msg, fmt, ap);
  ;
  ptr_idx = msg;
  while (ptr[ptr_idx] != '\0')
  {
    if ((ptr[ptr_idx] > 0x7f) && (utf8_open(&ud, *(&ptr[ptr_idx])) == UTF8_MORE))
    {
      ptr_idx += 1;
      left = strlen(ptr);
      if (left < (((size_t) ud.size) - 1))
      {
        break;
      }
      while ((more = utf8_append(&ud, *(&ptr[ptr_idx]))) == UTF8_MORE)
      {
        ptr_idx += 1;
      }

      ptr_idx += 1;
      if (more == UTF8_DONE)
      {
        size += ud.width;
      }
    }
    else
    {
      if ((ptr[ptr_idx] > 0x1f) && (ptr[ptr_idx] < 0x7f))
      {
        size += 1;
      }
      ptr_idx += 1;
    }
  }

  free(msg);
  return size;
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
void screen_write_nputs(struct screen_write_ctx *ctx, ssize_t maxlen, const struct grid_cell *gcp, const char *fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  screen_write_vnputs(ctx, maxlen, gcp, fmt, ap);
  ;
}


----------------------------
static int window_copy_is_lowercase(const char *ptr)
{
  unsigned int ptr_idx = 0;
  while (ptr[ptr_idx] != '\0')
  {
    if (ptr[ptr_idx] != tolower((u_char) ptr[ptr_idx]))
    {
      return 0;
    }
    ptr_idx += 1;
  }

  return 1;
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
extern const struct grid_cell grid_default_cell
----------------------------
static int window_copy_search_jump(struct window_pane *wp, struct grid *gd, struct grid *sgd, u_int fx, u_int fy, u_int endline, int cis, int wrap, int direction)
{
  u_int i;
  u_int px;
  int found;
  found = 0;
  if (direction)
  {
    for (i = fy; i <= endline; i += 1)
    {
      found = window_copy_search_lr(gd, sgd, &px, i, fx, gd->sx, cis);
      if (found)
      {
        break;
      }
      fx = 0;
    }

  }
  else
  {
    for (i = fy + 1; endline < i; i -= 1)
    {
      found = window_copy_search_rl(gd, sgd, &px, i - 1, 0, fx, cis);
      if (found)
      {
        i -= 1;
        break;
      }
      fx = gd->sx;
    }

  }
  if (found)
  {
    window_copy_scroll_to(wp, px, i);
    return 1;
  }
  if (wrap)
  {
    return window_copy_search_jump(wp, gd, sgd, (direction) ? (0) : (gd->sx - 1), (direction) ? (0) : ((gd->hsize + gd->sy) - 1), fy, cis, 0, direction);
  }
  return 0;
}


----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
static void window_copy_redraw_screen(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  window_copy_redraw_lines(wp, 0, (&data->screen)->grid->sy);
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
static void window_copy_clear_selection(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  u_int px;
  u_int py;
  screen_clear_selection(&data->screen);
  data->cursordrag = CURSORDRAG_NONE;
  py = (data->backing->grid->hsize + data->cy) - data->oy;
  px = window_copy_find_length(wp, py);
  if (data->cx > px)
  {
    window_copy_update_cursor(wp, px, data->cy);
  }
}


----------------------------
static void window_copy_move_right(struct screen *s, u_int *fx, u_int *fy)
{
  if ((*fx) == (s->grid->sx - 1))
  {
    if ((*fy) == (s->grid->hsize + s->grid->sy))
    {
      return;
    }
    *fx = 0;
    *fy = (*fy) + 1;
  }
  else
    *fx = (*fx) + 1;
}


----------------------------
None
----------------------------
***/


static int window_copy_search_up(struct window_pane *wp)
{
  return window_copy_search(wp, 0);
}


/*** DEPENDENCIES:
static int window_copy_search(struct window_pane *wp, int direction)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = data->backing;
  struct screen ss;
  struct screen_write_ctx ctx;
  struct grid *gd = s->grid;
  u_int fx;
  u_int fy;
  u_int endline;
  int wrapflag;
  int cis;
  int found;
  free(wp->searchstr);
  wp->searchstr = xstrdup(data->searchstr);
  fx = data->cx;
  fy = (data->backing->grid->hsize - data->oy) + data->cy;
  screen_init(&ss, screen_write_strlen("%s", data->searchstr), 1, 0);
  screen_write_start(&ctx, 0, &ss);
  screen_write_nputs(&ctx, -1, &grid_default_cell, "%s", data->searchstr);
  screen_write_stop(&ctx);
  if (direction)
  {
    window_copy_move_right(s, &fx, &fy);
  }
  else
    window_copy_move_left(s, &fx, &fy);
  window_copy_clear_selection(wp);
  wrapflag = options_get_number(wp->window->options, "wrap-search");
  cis = window_copy_is_lowercase(data->searchstr);
  if (direction)
  {
    endline = (gd->hsize + gd->sy) - 1;
  }
  else
    endline = 0;
  found = window_copy_search_jump(wp, gd, ss.grid, fx, fy, endline, cis, wrapflag, direction);
  if (window_copy_search_marks(wp, &ss))
  {
    window_copy_redraw_screen(wp);
  }
  screen_free(&ss);
  return found;
}


----------------------------
None
----------------------------
***/


static int window_copy_search_down(struct window_pane *wp)
{
  return window_copy_search(wp, 1);
}


/*** DEPENDENCIES:
static int window_copy_search(struct window_pane *wp, int direction)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = data->backing;
  struct screen ss;
  struct screen_write_ctx ctx;
  struct grid *gd = s->grid;
  u_int fx;
  u_int fy;
  u_int endline;
  int wrapflag;
  int cis;
  int found;
  free(wp->searchstr);
  wp->searchstr = xstrdup(data->searchstr);
  fx = data->cx;
  fy = (data->backing->grid->hsize - data->oy) + data->cy;
  screen_init(&ss, screen_write_strlen("%s", data->searchstr), 1, 0);
  screen_write_start(&ctx, 0, &ss);
  screen_write_nputs(&ctx, -1, &grid_default_cell, "%s", data->searchstr);
  screen_write_stop(&ctx);
  if (direction)
  {
    window_copy_move_right(s, &fx, &fy);
  }
  else
    window_copy_move_left(s, &fx, &fy);
  window_copy_clear_selection(wp);
  wrapflag = options_get_number(wp->window->options, "wrap-search");
  cis = window_copy_is_lowercase(data->searchstr);
  if (direction)
  {
    endline = (gd->hsize + gd->sy) - 1;
  }
  else
    endline = 0;
  found = window_copy_search_jump(wp, gd, ss.grid, fx, fy, endline, cis, wrapflag, direction);
  if (window_copy_search_marks(wp, &ss))
  {
    window_copy_redraw_screen(wp);
  }
  screen_free(&ss);
  return found;
}


----------------------------
None
----------------------------
***/


static void window_copy_free(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  if (wp->fd != (-1))
  {
    bufferevent_enable(wp->event, EV_READ | EV_WRITE);
  }
  free(data->searchmark);
  free(data->searchstr);
  if (data->backing != (&wp->base))
  {
    screen_free(data->backing);
    free(data->backing);
  }
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
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
None
----------------------------
***/


static void window_copy_redraw_selection(struct window_pane *wp, u_int old_y)
{
  struct window_copy_mode_data *data = wp->modedata;
  u_int new_y;
  u_int start;
  u_int end;
  new_y = data->cy;
  if (old_y <= new_y)
  {
    start = old_y;
    end = new_y;
  }
  else
  {
    start = new_y;
    end = old_y;
  }
  window_copy_redraw_lines(wp, start, (end - start) + 1);
}


/*** DEPENDENCIES:
static void window_copy_redraw_lines(struct window_pane *wp, u_int py, u_int ny)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen_write_ctx ctx;
  u_int i;
  screen_write_start(&ctx, wp, 0);
  for (i = py; i < (py + ny); i += 1)
  {
    window_copy_write_line(wp, &ctx, i);
  }

  screen_write_cursormove(&ctx, data->cx, data->cy);
  screen_write_stop(&ctx);
}


----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
None
----------------------------
***/


static void window_copy_copy_buffer(struct window_pane *wp, const char *bufname, void *buf, size_t len)
{
  struct screen_write_ctx ctx;
  if (options_get_number(global_options, "set-clipboard") != 0)
  {
    screen_write_start(&ctx, wp, 0);
    screen_write_setselection(&ctx, buf, len);
    screen_write_stop(&ctx);
    notify_pane("pane-set-clipboard", wp);
  }
  if (paste_set(buf, len, bufname, 0) != 0)
  {
    free(buf);
  }
}


/*** DEPENDENCIES:
int paste_set(char *data, size_t size, const char *name, char **cause)
{
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  struct paste_buffer *old;
  unsigned int old_idx = 0;
  if (cause != 0)
  {
    *cause = 0;
  }
  if (size == 0)
  {
    free(data);
    return 0;
  }
  if (name == 0)
  {
    paste_add(data, size);
    return 0;
  }
  if ((*name) == '\0')
  {
    if (cause != 0)
    {
      *cause = xstrdup("empty buffer name");
    }
    return -1;
  }
  pb_idx = xmalloc(sizeof(*pb_idx));
  pb->name = xstrdup(name);
  pb->data = data;
  pb->size = size;
  pb->automatic = 0;
  pb->order = paste_next_order;
  paste_next_order += 1;
  pb->created = time(0);
  if ((old_idx = paste_get_name(name)) != 0)
  {
    paste_free(old);
  }
  paste_name_tree_RB_INSERT(&paste_by_name, pb);
  paste_time_tree_RB_INSERT(&paste_by_time, pb);
  return 0;
}


----------------------------
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


// hint:  ['ud_ref is a mutable refrence to ', 'i_ref is a mutable refrence to u_int', 's_idx_ref is a mutable refrence to unsigned int']
void helper_window_copy_copy_line_1(struct utf8_data * const ud_ref, u_int * const i_ref, unsigned int * const s_idx_ref, char ** const buf, size_t * const off, u_int sy, u_int sx, u_int ex, struct grid * const gd, struct grid_cell gc, const char * const s)
{
  struct utf8_data ud = *ud_ref;
  u_int i = *i_ref;
  unsigned int s_idx = *s_idx_ref;
  for (i = sx; i < ex; i += 1)
  {
    grid_get_cell(gd, i, sy, &gc);
    if (gc.flags & 0x4)
    {
      continue;
    }
    utf8_copy(&ud, &gc.data);
    if ((ud.size == 1) && (gc.attr & 0x80))
    {
      s_idx = tty_acs_get(0, ud.data[0]);
      if (((&s[s_idx]) != 0) && (strlen(s) <= (sizeof(ud.data))))
      {
        ud.size = strlen(s);
        memcpy(ud.data, s, ud.size);
      }
    }
    *buf = xrealloc(*buf, (*off) + ud.size);
    memcpy((*buf) + (*off), ud.data, ud.size);
    *off += ud.size;
  }

  *ud_ref = ud;
  *i_ref = i;
  *s_idx_ref = s_idx;
}


/*** DEPENDENCIES:
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
const char *tty_acs_get(struct tty *tty, u_char ch)
{
  struct tty_acs_entry *entry;
  unsigned int entry_idx = 0;
  if (tty_acs_needed(tty))
  {
    if (tty->term->acs[ch][0] == '\0')
    {
      return 0;
    }
    return &tty->term->acs[ch][0];
  }
  entry_idx = bsearch(&ch, tty_acs_table, (sizeof(tty_acs_table)) / (sizeof(tty_acs_table[0])), sizeof(tty_acs_table[0]), tty_acs_cmp);
  if ((&entry[entry_idx]) == 0)
  {
    return 0;
  }
  return entry->string;
}


----------------------------
void *xrealloc(void *ptr, size_t size)
{
  return xreallocarray(ptr, 1, size);
}


----------------------------
None
----------------------------
***/


static void window_copy_copy_line(struct window_pane *wp, char **buf, size_t *off, u_int sy, u_int sx, u_int ex)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct grid *gd = data->backing->grid;
  struct grid_cell gc;
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  struct utf8_data ud;
  u_int i;
  u_int xx;
  u_int wrapped = 0;
  const char *s;
  unsigned int s_idx = 0;
  if (sx > ex)
  {
    return;
  }
  gl_idx = &gd->linedata[sy];
  if ((gl->flags & 0x1) && (gl->cellsize <= gd->sx))
  {
    wrapped = 1;
  }
  if (wrapped)
  {
    xx = gl->cellsize;
  }
  else
    xx = window_copy_find_length(wp, sy);
  if (ex > xx)
  {
    ex = xx;
  }
  if (sx > xx)
  {
    sx = xx;
  }
  if (sx < ex)
  {
    helper_window_copy_copy_line_1(&ud, &i, &s_idx, buf, off, sy, sx, ex, gd, gc, s);
  }
  if ((!wrapped) || (ex != xx))
  {
    *buf = xrealloc(*buf, (*off) + 1);
    (*buf)[(*off)++] = '\n';
  }
}


/*** DEPENDENCIES:
static u_int window_copy_find_length(struct window_pane *wp, u_int py)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = data->backing;
  struct grid_cell gc;
  u_int px;
  px = s->grid->linedata[py].cellsize;
  if (px > s->grid->sx)
  {
    px = s->grid->sx;
  }
  while (px > 0)
  {
    grid_get_cell(s->grid, px - 1, py, &gc);
    if ((gc.data.size != 1) || ((*gc.data.data) != ' '))
    {
      break;
    }
    px -= 1;
  }

  return px;
}


----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
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
void helper_window_copy_copy_line_1(struct utf8_data * const ud_ref, u_int * const i_ref, unsigned int * const s_idx_ref, char ** const buf, size_t * const off, u_int sy, u_int sx, u_int ex, struct grid * const gd, struct grid_cell gc, const char * const s)
{
  struct utf8_data ud = *ud_ref;
  u_int i = *i_ref;
  unsigned int s_idx = *s_idx_ref;
  for (i = sx; i < ex; i += 1)
  {
    grid_get_cell(gd, i, sy, &gc);
    if (gc.flags & 0x4)
    {
      continue;
    }
    utf8_copy(&ud, &gc.data);
    if ((ud.size == 1) && (gc.attr & 0x80))
    {
      s_idx = tty_acs_get(0, ud.data[0]);
      if (((&s[s_idx]) != 0) && (strlen(s) <= (sizeof(ud.data))))
      {
        ud.size = strlen(s);
        memcpy(ud.data, s, ud.size);
      }
    }
    *buf = xrealloc(*buf, (*off) + ud.size);
    memcpy((*buf) + (*off), ud.data, ud.size);
    *off += ud.size;
  }

  *ud_ref = ud;
  *i_ref = i;
  *s_idx_ref = s_idx;
}


----------------------------
None
----------------------------
void *xrealloc(void *ptr, size_t size)
{
  return xreallocarray(ptr, 1, size);
}


----------------------------
None
----------------------------
***/


static void *window_copy_get_selection(struct window_pane *wp, size_t *len)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  char *buf;
  unsigned int buf_idx = 0;
  size_t off;
  u_int i;
  u_int xx;
  u_int yy;
  u_int sx;
  u_int sy;
  u_int ex;
  u_int ey;
  u_int ey_last;
  u_int firstsx;
  u_int lastex;
  u_int restex;
  u_int restsx;
  u_int selx;
  int keys;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return 0;
  }
  buf_idx = xmalloc(1);
  off = 0;
  buf[buf_idx] = '\0';
  xx = data->endselx;
  yy = data->endsely;
  if ((yy < data->sely) || ((yy == data->sely) && (xx < data->selx)))
  {
    sx = xx;
    sy = yy;
    ex = data->selx;
    ey = data->sely;
  }
  else
  {
    sx = data->selx;
    sy = data->sely;
    ex = xx;
    ey = yy;
  }
  ey_last = window_copy_find_length(wp, ey);
  if (ex > ey_last)
  {
    ex = ey_last;
  }
  xx = s->grid->sx;
  keys = options_get_number(wp->window->options, "mode-keys");
  if (data->rectflag)
  {
    helper_window_copy_get_selection_1(&firstsx, &lastex, &restex, &restsx, &selx, data, keys);
  }
  else
  {
    if (keys == 0)
    {
      lastex = ex;
    }
    else
      lastex = ex + 1;
    restex = xx;
    firstsx = sx;
    restsx = 0;
  }
  for (i = sy; i <= ey; i += 1)
  {
    window_copy_copy_line(wp, &(&buf[buf_idx]), &off, i, (i == sy) ? (firstsx) : (restsx), (i == ey) ? (lastex) : (restex));
  }

  if (off == 0)
  {
    free(buf);
    return 0;
  }
  if ((keys == 0) || (lastex <= ey_last))
  {
    off -= 1;
  }
  *len = off;
  return buf;
}


/*** DEPENDENCIES:
void helper_window_copy_get_selection_1(u_int * const firstsx_ref, u_int * const lastex_ref, u_int * const restex_ref, u_int * const restsx_ref, u_int * const selx_ref, struct window_copy_mode_data * const data, int keys)
{
  u_int firstsx = *firstsx_ref;
  u_int lastex = *lastex_ref;
  u_int restex = *restex_ref;
  u_int restsx = *restsx_ref;
  u_int selx = *selx_ref;
  if (data->cursordrag == CURSORDRAG_ENDSEL)
  {
    selx = data->selx;
  }
  else
    selx = data->endselx;
  if (selx < data->cx)
  {
    if (keys == 0)
    {
      lastex = data->cx;
      restex = data->cx;
    }
    else
    {
      lastex = data->cx + 1;
      restex = data->cx + 1;
    }
    firstsx = selx;
    restsx = selx;
  }
  else
  {
    lastex = selx + 1;
    restex = selx + 1;
    firstsx = data->cx;
    restsx = data->cx;
  }
  *firstsx_ref = firstsx;
  *lastex_ref = lastex;
  *restex_ref = restex;
  *restsx_ref = restsx;
  *selx_ref = selx;
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
static void window_copy_copy_line(struct window_pane *wp, char **buf, size_t *off, u_int sy, u_int sx, u_int ex)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct grid *gd = data->backing->grid;
  struct grid_cell gc;
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  struct utf8_data ud;
  u_int i;
  u_int xx;
  u_int wrapped = 0;
  const char *s;
  unsigned int s_idx = 0;
  if (sx > ex)
  {
    return;
  }
  gl_idx = &gd->linedata[sy];
  if ((gl->flags & 0x1) && (gl->cellsize <= gd->sx))
  {
    wrapped = 1;
  }
  if (wrapped)
  {
    xx = gl->cellsize;
  }
  else
    xx = window_copy_find_length(wp, sy);
  if (ex > xx)
  {
    ex = xx;
  }
  if (sx > xx)
  {
    sx = xx;
  }
  if (sx < ex)
  {
    helper_window_copy_copy_line_1(&ud, &i, &s_idx, buf, off, sy, sx, ex, gd, gc, s);
  }
  if ((!wrapped) || (ex != xx))
  {
    *buf = xrealloc(*buf, (*off) + 1);
    (*buf)[(*off)++] = '\n';
  }
}


----------------------------
static u_int window_copy_find_length(struct window_pane *wp, u_int py)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = data->backing;
  struct grid_cell gc;
  u_int px;
  px = s->grid->linedata[py].cellsize;
  if (px > s->grid->sx)
  {
    px = s->grid->sx;
  }
  while (px > 0)
  {
    grid_get_cell(s->grid, px - 1, py, &gc);
    if ((gc.data.size != 1) || ((*gc.data.data) != ' '))
    {
      break;
    }
    px -= 1;
  }

  return px;
}


----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
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


static void window_copy_copy_selection(struct window_pane *wp, const char *bufname)
{
  void *buf;
  unsigned int buf_idx = 0;
  size_t len;
  buf_idx = window_copy_get_selection(wp, &len);
  if ((&buf[buf_idx]) == 0)
  {
    return;
  }
  window_copy_copy_buffer(wp, bufname, buf, len);
}


/*** DEPENDENCIES:
static void window_copy_copy_buffer(struct window_pane *wp, const char *bufname, void *buf, size_t len)
{
  struct screen_write_ctx ctx;
  if (options_get_number(global_options, "set-clipboard") != 0)
  {
    screen_write_start(&ctx, wp, 0);
    screen_write_setselection(&ctx, buf, len);
    screen_write_stop(&ctx);
    notify_pane("pane-set-clipboard", wp);
  }
  if (paste_set(buf, len, bufname, 0) != 0)
  {
    free(buf);
  }
}


----------------------------
static void *window_copy_get_selection(struct window_pane *wp, size_t *len)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  char *buf;
  unsigned int buf_idx = 0;
  size_t off;
  u_int i;
  u_int xx;
  u_int yy;
  u_int sx;
  u_int sy;
  u_int ex;
  u_int ey;
  u_int ey_last;
  u_int firstsx;
  u_int lastex;
  u_int restex;
  u_int restsx;
  u_int selx;
  int keys;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return 0;
  }
  buf_idx = xmalloc(1);
  off = 0;
  buf[buf_idx] = '\0';
  xx = data->endselx;
  yy = data->endsely;
  if ((yy < data->sely) || ((yy == data->sely) && (xx < data->selx)))
  {
    sx = xx;
    sy = yy;
    ex = data->selx;
    ey = data->sely;
  }
  else
  {
    sx = data->selx;
    sy = data->sely;
    ex = xx;
    ey = yy;
  }
  ey_last = window_copy_find_length(wp, ey);
  if (ex > ey_last)
  {
    ex = ey_last;
  }
  xx = s->grid->sx;
  keys = options_get_number(wp->window->options, "mode-keys");
  if (data->rectflag)
  {
    helper_window_copy_get_selection_1(&firstsx, &lastex, &restex, &restsx, &selx, data, keys);
  }
  else
  {
    if (keys == 0)
    {
      lastex = ex;
    }
    else
      lastex = ex + 1;
    restex = xx;
    firstsx = sx;
    restsx = 0;
  }
  for (i = sy; i <= ey; i += 1)
  {
    window_copy_copy_line(wp, &(&buf[buf_idx]), &off, i, (i == sy) ? (firstsx) : (restsx), (i == ey) ? (lastex) : (restex));
  }

  if (off == 0)
  {
    free(buf);
    return 0;
  }
  if ((keys == 0) || (lastex <= ey_last))
  {
    off -= 1;
  }
  *len = off;
  return buf;
}


----------------------------
None
----------------------------
***/


static void window_copy_previous_paragraph(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  u_int oy;
  oy = (data->backing->grid->hsize + data->cy) - data->oy;
  while ((oy > 0) && (window_copy_find_length(wp, oy) == 0))
  {
    oy -= 1;
  }

  while ((oy > 0) && (window_copy_find_length(wp, oy) > 0))
  {
    oy -= 1;
  }

  window_copy_scroll_to(wp, 0, oy);
}


/*** DEPENDENCIES:
static u_int window_copy_find_length(struct window_pane *wp, u_int py)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = data->backing;
  struct grid_cell gc;
  u_int px;
  px = s->grid->linedata[py].cellsize;
  if (px > s->grid->sx)
  {
    px = s->grid->sx;
  }
  while (px > 0)
  {
    grid_get_cell(s->grid, px - 1, py, &gc);
    if ((gc.data.size != 1) || ((*gc.data.data) != ' '))
    {
      break;
    }
    px -= 1;
  }

  return px;
}


----------------------------
static void window_copy_scroll_to(struct window_pane *wp, u_int px, u_int py)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct grid *gd = data->backing->grid;
  u_int offset;
  u_int gap;
  data->cx = px;
  if ((py >= (gd->hsize - data->oy)) && (py < ((gd->hsize - data->oy) + gd->sy)))
  {
    data->cy = py - (gd->hsize - data->oy);
  }
  else
  {
    gap = gd->sy / 4;
    if (py < gd->sy)
    {
      offset = 0;
      data->cy = py;
    }
    else
      if (py > ((gd->hsize + gd->sy) - gap))
    {
      offset = gd->hsize;
      data->cy = py - gd->hsize;
    }
    else
    {
      offset = (py + gap) - gd->sy;
      data->cy = py - offset;
    }
    data->oy = gd->hsize - offset;
  }
  window_copy_update_selection(wp, 1);
  window_copy_redraw_screen(wp);
}


----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
None
----------------------------
***/


static void window_copy_write_lines(struct window_pane *wp, struct screen_write_ctx *ctx, u_int py, u_int ny)
{
  u_int yy;
  for (yy = py; yy < (py + ny); yy += 1)
  {
    window_copy_write_line(wp, ctx, py);
  }

}


/*** DEPENDENCIES:
static void window_copy_write_line(struct window_pane *wp, struct screen_write_ctx *ctx, u_int py)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct options *oo = wp->window->options;
  struct grid_cell gc;
  char hdr[512];
  size_t size = 0;
  style_apply(&gc, oo, "mode-style");
  gc.flags |= 0x20;
  if (py == 0)
  {
    if (data->searchmark == 0)
    {
      size = xsnprintf(hdr, sizeof(hdr), "[%u/%u]", data->oy, data->backing->grid->hsize);
    }
    else
    {
      if (data->searchthis == (-1))
      {
        size = xsnprintf(hdr, sizeof(hdr), "(%u results) [%d/%u]", data->searchcount, data->oy, data->backing->grid->hsize);
      }
      else
      {
        size = xsnprintf(hdr, sizeof(hdr), "(%u/%u results) [%d/%u]", data->searchthis, data->searchcount, data->oy, data->backing->grid->hsize);
      }
    }
    if (size > s->grid->sx)
    {
      size = s->grid->sx;
    }
    screen_write_cursormove(ctx, s->grid->sx - size, 0);
    screen_write_puts(ctx, &gc, "%s", hdr);
  }
  else
    size = 0;
  if (size < s->grid->sx)
  {
    screen_write_cursormove(ctx, 0, py);
    screen_write_copy(ctx, data->backing, 0, (data->backing->grid->hsize - data->oy) + py, s->grid->sx - size, 1, data->searchmark, &gc);
  }
  if ((py == data->cy) && (data->cx == s->grid->sx))
  {
    memcpy(&gc, &grid_default_cell, sizeof(gc));
    screen_write_cursormove(ctx, s->grid->sx - 1, py);
    screen_write_putc(ctx, &gc, '$');
  }
}


----------------------------
None
----------------------------
None
----------------------------
***/


static void window_copy_start_selection(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  data->selx = data->cx;
  data->sely = (data->backing->grid->hsize + data->cy) - data->oy;
  data->endselx = data->selx;
  data->endsely = data->sely;
  data->cursordrag = CURSORDRAG_ENDSEL;
  s->sel.flag = 1;
  window_copy_update_selection(wp, 1);
}


/*** DEPENDENCIES:
None
----------------------------
static int window_copy_update_selection(struct window_pane *wp, int may_redraw)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct options *oo = wp->window->options;
  struct grid_cell gc;
  u_int sx;
  u_int sy;
  u_int cy;
  u_int endsx;
  u_int endsy;
  int startrelpos;
  int endrelpos;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return 0;
  }
  window_copy_synchronize_cursor(wp);
  sx = data->selx;
  sy = data->sely;
  startrelpos = window_copy_adjust_selection(wp, &sx, &sy);
  endsx = data->endselx;
  endsy = data->endsely;
  endrelpos = window_copy_adjust_selection(wp, &endsx, &endsy);
  if ((startrelpos == endrelpos) && (startrelpos != WINDOW_COPY_REL_POS_ON_SCREEN))
  {
    screen_hide_selection(s);
    return 0;
  }
  style_apply(&gc, oo, "mode-style");
  gc.flags |= 0x20;
  screen_set_selection(s, sx, sy, endsx, endsy, data->rectflag, &gc);
  if (data->rectflag && may_redraw)
  {
    cy = data->cy;
    if (data->cursordrag == CURSORDRAG_ENDSEL)
    {
      if (sy < cy)
      {
        window_copy_redraw_lines(wp, sy, (cy - sy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (sy - cy) + 1);
    }
    else
    {
      if (endsy < cy)
      {
        window_copy_redraw_lines(wp, endsy, (cy - endsy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (endsy - cy) + 1);
    }
  }
  return 1;
}


----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
None
----------------------------
***/


static void window_copy_next_paragraph(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  u_int maxy;
  u_int ox;
  u_int oy;
  oy = (data->backing->grid->hsize + data->cy) - data->oy;
  maxy = (data->backing->grid->hsize + s->grid->sy) - 1;
  while ((oy < maxy) && (window_copy_find_length(wp, oy) == 0))
  {
    oy += 1;
  }

  while ((oy < maxy) && (window_copy_find_length(wp, oy) > 0))
  {
    oy += 1;
  }

  ox = window_copy_find_length(wp, oy);
  window_copy_scroll_to(wp, ox, oy);
}


/*** DEPENDENCIES:
static u_int window_copy_find_length(struct window_pane *wp, u_int py)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = data->backing;
  struct grid_cell gc;
  u_int px;
  px = s->grid->linedata[py].cellsize;
  if (px > s->grid->sx)
  {
    px = s->grid->sx;
  }
  while (px > 0)
  {
    grid_get_cell(s->grid, px - 1, py, &gc);
    if ((gc.data.size != 1) || ((*gc.data.data) != ' '))
    {
      break;
    }
    px -= 1;
  }

  return px;
}


----------------------------
static void window_copy_scroll_to(struct window_pane *wp, u_int px, u_int py)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct grid *gd = data->backing->grid;
  u_int offset;
  u_int gap;
  data->cx = px;
  if ((py >= (gd->hsize - data->oy)) && (py < ((gd->hsize - data->oy) + gd->sy)))
  {
    data->cy = py - (gd->hsize - data->oy);
  }
  else
  {
    gap = gd->sy / 4;
    if (py < gd->sy)
    {
      offset = 0;
      data->cy = py;
    }
    else
      if (py > ((gd->hsize + gd->sy) - gap))
    {
      offset = gd->hsize;
      data->cy = py - gd->hsize;
    }
    else
    {
      offset = (py + gap) - gd->sy;
      data->cy = py - offset;
    }
    data->oy = gd->hsize - offset;
  }
  window_copy_update_selection(wp, 1);
  window_copy_redraw_screen(wp);
}


----------------------------
None
----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
None
----------------------------
***/


static void window_copy_goto_line(struct window_pane *wp, const char *linestr)
{
  struct window_copy_mode_data *data = wp->modedata;
  const char *errstr;
  u_int lineno;
  lineno = strtonum(linestr, 0, data->backing->grid->hsize, &errstr);
  if (errstr != 0)
  {
    return;
  }
  data->oy = lineno;
  window_copy_update_selection(wp, 1);
  window_copy_redraw_screen(wp);
}


/*** DEPENDENCIES:
static void window_copy_redraw_screen(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  window_copy_redraw_lines(wp, 0, (&data->screen)->grid->sy);
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
static int window_copy_update_selection(struct window_pane *wp, int may_redraw)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct options *oo = wp->window->options;
  struct grid_cell gc;
  u_int sx;
  u_int sy;
  u_int cy;
  u_int endsx;
  u_int endsy;
  int startrelpos;
  int endrelpos;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return 0;
  }
  window_copy_synchronize_cursor(wp);
  sx = data->selx;
  sy = data->sely;
  startrelpos = window_copy_adjust_selection(wp, &sx, &sy);
  endsx = data->endselx;
  endsy = data->endsely;
  endrelpos = window_copy_adjust_selection(wp, &endsx, &endsy);
  if ((startrelpos == endrelpos) && (startrelpos != WINDOW_COPY_REL_POS_ON_SCREEN))
  {
    screen_hide_selection(s);
    return 0;
  }
  style_apply(&gc, oo, "mode-style");
  gc.flags |= 0x20;
  screen_set_selection(s, sx, sy, endsx, endsy, data->rectflag, &gc);
  if (data->rectflag && may_redraw)
  {
    cy = data->cy;
    if (data->cursordrag == CURSORDRAG_ENDSEL)
    {
      if (sy < cy)
      {
        window_copy_redraw_lines(wp, sy, (cy - sy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (sy - cy) + 1);
    }
    else
    {
      if (endsy < cy)
      {
        window_copy_redraw_lines(wp, endsy, (cy - endsy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (endsy - cy) + 1);
    }
  }
  return 1;
}


----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
None
----------------------------
***/


static void window_copy_other_end(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  u_int selx;
  u_int sely;
  u_int cy;
  u_int yy;
  u_int hsize;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return;
  }
  if (s->sel.lineflag == LINE_SEL_LEFT_RIGHT)
  {
    s->sel.lineflag = LINE_SEL_RIGHT_LEFT;
  }
  else
    if (s->sel.lineflag == LINE_SEL_RIGHT_LEFT)
  {
    s->sel.lineflag = LINE_SEL_LEFT_RIGHT;
  }
  switch (data->cursordrag)
  {
    case CURSORDRAG_NONE:

    case CURSORDRAG_SEL:
    {
      data->cursordrag = CURSORDRAG_ENDSEL;
      break;
    }

    case CURSORDRAG_ENDSEL:
    {
      data->cursordrag = CURSORDRAG_SEL;
      break;
    }

  }

  selx = data->endselx;
  sely = data->endsely;
  if (data->cursordrag == CURSORDRAG_SEL)
  {
    selx = data->selx;
    sely = data->sely;
  }
  cy = data->cy;
  yy = (data->backing->grid->hsize + data->cy) - data->oy;
  data->cx = selx;
  hsize = data->backing->grid->hsize;
  if (sely < (hsize - data->oy))
  {
    data->oy = hsize - sely;
    data->cy = 0;
  }
  else
    if (sely > ((hsize - data->oy) + s->grid->sy))
  {
    data->oy = ((hsize - sely) + s->grid->sy) - 1;
    data->cy = s->grid->sy - 1;
  }
  else
    data->cy = (cy + sely) - yy;
  window_copy_update_selection(wp, 1);
  window_copy_redraw_screen(wp);
}


/*** DEPENDENCIES:
static void window_copy_redraw_screen(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  window_copy_redraw_lines(wp, 0, (&data->screen)->grid->sy);
}


----------------------------
None
----------------------------
static int window_copy_update_selection(struct window_pane *wp, int may_redraw)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct options *oo = wp->window->options;
  struct grid_cell gc;
  u_int sx;
  u_int sy;
  u_int cy;
  u_int endsx;
  u_int endsy;
  int startrelpos;
  int endrelpos;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return 0;
  }
  window_copy_synchronize_cursor(wp);
  sx = data->selx;
  sy = data->sely;
  startrelpos = window_copy_adjust_selection(wp, &sx, &sy);
  endsx = data->endselx;
  endsy = data->endsely;
  endrelpos = window_copy_adjust_selection(wp, &endsx, &endsy);
  if ((startrelpos == endrelpos) && (startrelpos != WINDOW_COPY_REL_POS_ON_SCREEN))
  {
    screen_hide_selection(s);
    return 0;
  }
  style_apply(&gc, oo, "mode-style");
  gc.flags |= 0x20;
  screen_set_selection(s, sx, sy, endsx, endsy, data->rectflag, &gc);
  if (data->rectflag && may_redraw)
  {
    cy = data->cy;
    if (data->cursordrag == CURSORDRAG_ENDSEL)
    {
      if (sy < cy)
      {
        window_copy_redraw_lines(wp, sy, (cy - sy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (sy - cy) + 1);
    }
    else
    {
      if (endsy < cy)
      {
        window_copy_redraw_lines(wp, endsy, (cy - endsy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (endsy - cy) + 1);
    }
  }
  return 1;
}


----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
None
----------------------------
***/


static int window_copy_in_set(struct window_pane *wp, u_int px, u_int py, const char *set)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct grid_cell gc;
  const struct utf8_data *ud;
  unsigned int ud_idx = 0;
  grid_get_cell(data->backing->grid, px, py, &gc);
  ud_idx = &gc.data;
  if ((ud->size != 1) || (gc.flags & 0x4))
  {
    return 0;
  }
  if (((*ud->data) == 0x00) || ((*ud->data) == 0x7f))
  {
    return 0;
  }
  return strchr(set, *ud->data) != 0;
}


/*** DEPENDENCIES:
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
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
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
None
----------------------------
***/


static void window_copy_rectangle_toggle(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  u_int px;
  u_int py;
  data->rectflag = !data->rectflag;
  py = (data->backing->grid->hsize + data->cy) - data->oy;
  px = window_copy_find_length(wp, py);
  if (data->cx > px)
  {
    window_copy_update_cursor(wp, px, data->cy);
  }
  window_copy_update_selection(wp, 1);
  window_copy_redraw_screen(wp);
}


/*** DEPENDENCIES:
static int window_copy_update_selection(struct window_pane *wp, int may_redraw)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct options *oo = wp->window->options;
  struct grid_cell gc;
  u_int sx;
  u_int sy;
  u_int cy;
  u_int endsx;
  u_int endsy;
  int startrelpos;
  int endrelpos;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return 0;
  }
  window_copy_synchronize_cursor(wp);
  sx = data->selx;
  sy = data->sely;
  startrelpos = window_copy_adjust_selection(wp, &sx, &sy);
  endsx = data->endselx;
  endsy = data->endsely;
  endrelpos = window_copy_adjust_selection(wp, &endsx, &endsy);
  if ((startrelpos == endrelpos) && (startrelpos != WINDOW_COPY_REL_POS_ON_SCREEN))
  {
    screen_hide_selection(s);
    return 0;
  }
  style_apply(&gc, oo, "mode-style");
  gc.flags |= 0x20;
  screen_set_selection(s, sx, sy, endsx, endsy, data->rectflag, &gc);
  if (data->rectflag && may_redraw)
  {
    cy = data->cy;
    if (data->cursordrag == CURSORDRAG_ENDSEL)
    {
      if (sy < cy)
      {
        window_copy_redraw_lines(wp, sy, (cy - sy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (sy - cy) + 1);
    }
    else
    {
      if (endsy < cy)
      {
        window_copy_redraw_lines(wp, endsy, (cy - endsy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (endsy - cy) + 1);
    }
  }
  return 1;
}


----------------------------
static u_int window_copy_find_length(struct window_pane *wp, u_int py)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = data->backing;
  struct grid_cell gc;
  u_int px;
  px = s->grid->linedata[py].cellsize;
  if (px > s->grid->sx)
  {
    px = s->grid->sx;
  }
  while (px > 0)
  {
    grid_get_cell(s->grid, px - 1, py, &gc);
    if ((gc.data.size != 1) || ((*gc.data.data) != ' '))
    {
      break;
    }
    px -= 1;
  }

  return px;
}


----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
static void window_copy_redraw_screen(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  window_copy_redraw_lines(wp, 0, (&data->screen)->grid->sy);
}


----------------------------
static void window_copy_update_cursor(struct window_pane *wp, u_int cx, u_int cy)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct screen_write_ctx ctx;
  u_int old_cx;
  u_int old_cy;
  old_cx = data->cx;
  old_cy = data->cy;
  data->cx = cx;
  data->cy = cy;
  if (old_cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, old_cy, 1);
  }
  if (data->cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, data->cy, 1);
  }
  else
  {
    screen_write_start(&ctx, wp, 0);
    screen_write_cursormove(&ctx, data->cx, data->cy);
    screen_write_stop(&ctx);
  }
}


----------------------------
None
----------------------------
***/


static void window_copy_move_mouse(struct mouse_event *m)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int x;
  u_int y;
  wp_idx = cmd_mouse_pane(m, 0, 0);
  if (((&wp[wp_idx]) == 0) || (wp->mode != (&window_copy_mode)))
  {
    return;
  }
  if (cmd_mouse_at(wp, m, &x, &y, 0) != 0)
  {
    return;
  }
  window_copy_update_cursor(wp, x, y);
}


/*** DEPENDENCIES:
extern const struct window_mode window_copy_mode
----------------------------
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
struct window_pane *cmd_mouse_pane(struct mouse_event *m, struct session **sp, struct winlink **wlp)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  if ((wl_idx = cmd_mouse_window(m, sp)) == 0)
  {
    return 0;
  }
  if ((wp_idx = window_pane_find_by_id(m->wp_idx)) == 0)
  {
    return 0;
  }
  if (!window_has_pane(wl->window, wp))
  {
    return 0;
  }
  if (wlp != 0)
  {
    *wlp = &wl[wl_idx];
  }
  return wp;
}


----------------------------
int cmd_mouse_at(struct window_pane *wp, struct mouse_event *m, u_int *xp, u_int *yp, int last)
{
  u_int x;
  u_int y;
  if (last)
  {
    x = m->lx;
    y = m->ly;
  }
  else
  {
    x = m->x;
    y = m->y;
  }
  if ((m->statusat == 0) && (y > 0))
  {
    y -= 1;
  }
  else
    if ((m->statusat > 0) && (y >= ((u_int) m->statusat)))
  {
    y = m->statusat - 1;
  }
  if ((x < wp->xoff) || (x >= (wp->xoff + wp->sx)))
  {
    return -1;
  }
  if ((y < wp->yoff) || (y >= (wp->yoff + wp->sy)))
  {
    return -1;
  }
  if (xp != 0)
  {
    *xp = x - wp->xoff;
  }
  if (yp != 0)
  {
    *yp = y - wp->yoff;
  }
  return 0;
}


----------------------------
static void window_copy_update_cursor(struct window_pane *wp, u_int cx, u_int cy)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct screen_write_ctx ctx;
  u_int old_cx;
  u_int old_cy;
  old_cx = data->cx;
  old_cy = data->cy;
  data->cx = cx;
  data->cy = cy;
  if (old_cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, old_cy, 1);
  }
  if (data->cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, data->cy, 1);
  }
  else
  {
    screen_write_start(&ctx, wp, 0);
    screen_write_cursormove(&ctx, data->cx, data->cy);
    screen_write_stop(&ctx);
  }
}


----------------------------
None
----------------------------
***/


// hint:  ['argument_idx_ref is a mutable refrence to unsigned int', 'redraw_ref is a mutable refrence to int', 'prefix_ref is a mutable refrence to char']
void helper_helper_window_copy_command_1_1(unsigned int * const argument_idx_ref, int * const redraw_ref, char * const prefix_ref, struct window_pane * const wp, struct window_copy_mode_data * const data, const char * const argument)
{
  unsigned int argument_idx = *argument_idx_ref;
  int redraw = *redraw_ref;
  char prefix = *prefix_ref;
  prefix = argument[argument_idx];
  argument_idx += 1;
  if ((data->searchx == (-1)) || (data->searchy == (-1)))
  {
    data->searchx = data->cx;
    data->searchy = data->cy;
    data->searcho = data->oy;
  }
  else
    if ((data->searchstr != 0) && (strcmp(argument, data->searchstr) != 0))
  {
    data->cx = data->searchx;
    data->cy = data->searchy;
    data->oy = data->searcho;
    redraw = 1;
  }
  if (argument[argument_idx] == '\0')
  {
    window_copy_clear_marks(wp);
    redraw = 1;
  }
  else
    if ((prefix == '=') || (prefix == '-'))
  {
    data->searchtype = WINDOW_COPY_SEARCHUP;
    free(data->searchstr);
    data->searchstr = xstrdup(argument);
    if (!window_copy_search_up(wp))
    {
      window_copy_clear_marks(wp);
      redraw = 1;
    }
  }
  else
    if (prefix == '+')
  {
    data->searchtype = WINDOW_COPY_SEARCHDOWN;
    free(data->searchstr);
    data->searchstr = xstrdup(argument);
    if (!window_copy_search_down(wp))
    {
      window_copy_clear_marks(wp);
      redraw = 1;
    }
  }
  *argument_idx_ref = argument_idx;
  *redraw_ref = redraw;
  *prefix_ref = prefix;
}


/*** DEPENDENCIES:
static int window_copy_search_down(struct window_pane *wp)
{
  return window_copy_search(wp, 1);
}


----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
static int window_copy_search_up(struct window_pane *wp)
{
  return window_copy_search(wp, 0);
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
static void window_copy_clear_marks(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  free(data->searchmark);
  data->searchmark = 0;
}


----------------------------
None
----------------------------
***/


// hint:  ['argument_idx_ref is a mutable refrence to unsigned int', 'redraw_ref is a mutable refrence to int', 'prefix_ref is a mutable refrence to char']
void helper_helper_window_copy_command_1_2(unsigned int * const argument_idx_ref, int * const redraw_ref, char * const prefix_ref, struct window_pane * const wp, struct window_copy_mode_data * const data, const char * const argument)
{
  unsigned int argument_idx = *argument_idx_ref;
  int redraw = *redraw_ref;
  char prefix = *prefix_ref;
  prefix = argument[argument_idx];
  argument_idx += 1;
  if ((data->searchx == (-1)) || (data->searchy == (-1)))
  {
    data->searchx = data->cx;
    data->searchy = data->cy;
    data->searcho = data->oy;
  }
  else
    if ((data->searchstr != 0) && (strcmp(argument, data->searchstr) != 0))
  {
    data->cx = data->searchx;
    data->cy = data->searchy;
    data->oy = data->searcho;
    redraw = 1;
  }
  if (argument[argument_idx] == '\0')
  {
    window_copy_clear_marks(wp);
    redraw = 1;
  }
  else
    if ((prefix == '=') || (prefix == '+'))
  {
    data->searchtype = WINDOW_COPY_SEARCHDOWN;
    free(data->searchstr);
    data->searchstr = xstrdup(argument);
    if (!window_copy_search_down(wp))
    {
      window_copy_clear_marks(wp);
      redraw = 1;
    }
  }
  else
    if (prefix == '-')
  {
    data->searchtype = WINDOW_COPY_SEARCHUP;
    free(data->searchstr);
    data->searchstr = xstrdup(argument);
    if (!window_copy_search_up(wp))
    {
      window_copy_clear_marks(wp);
      redraw = 1;
    }
  }
  *argument_idx_ref = argument_idx;
  *redraw_ref = redraw;
  *prefix_ref = prefix;
}


/*** DEPENDENCIES:
static int window_copy_search_down(struct window_pane *wp)
{
  return window_copy_search(wp, 1);
}


----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
static int window_copy_search_up(struct window_pane *wp)
{
  return window_copy_search(wp, 0);
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
static void window_copy_clear_marks(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  free(data->searchmark);
  data->searchmark = 0;
}


----------------------------
None
----------------------------
***/


static void window_copy_cursor_jump_to(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *back_s = data->backing;
  struct grid_cell gc;
  u_int px;
  u_int py;
  u_int xx;
  px = data->cx + 2;
  py = (back_s->grid->hsize + data->cy) - data->oy;
  xx = window_copy_find_length(wp, py);
  while (px < xx)
  {
    grid_get_cell(back_s->grid, px, py, &gc);
    if (((!(gc.flags & 0x4)) && (gc.data.size == 1)) && ((*gc.data.data) == data->jumpchar))
    {
      window_copy_update_cursor(wp, px - 1, data->cy);
      if (window_copy_update_selection(wp, 1))
      {
        window_copy_redraw_lines(wp, data->cy, 1);
      }
      return;
    }
    px += 1;
  }

}


/*** DEPENDENCIES:
static int window_copy_update_selection(struct window_pane *wp, int may_redraw)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct options *oo = wp->window->options;
  struct grid_cell gc;
  u_int sx;
  u_int sy;
  u_int cy;
  u_int endsx;
  u_int endsy;
  int startrelpos;
  int endrelpos;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return 0;
  }
  window_copy_synchronize_cursor(wp);
  sx = data->selx;
  sy = data->sely;
  startrelpos = window_copy_adjust_selection(wp, &sx, &sy);
  endsx = data->endselx;
  endsy = data->endsely;
  endrelpos = window_copy_adjust_selection(wp, &endsx, &endsy);
  if ((startrelpos == endrelpos) && (startrelpos != WINDOW_COPY_REL_POS_ON_SCREEN))
  {
    screen_hide_selection(s);
    return 0;
  }
  style_apply(&gc, oo, "mode-style");
  gc.flags |= 0x20;
  screen_set_selection(s, sx, sy, endsx, endsy, data->rectflag, &gc);
  if (data->rectflag && may_redraw)
  {
    cy = data->cy;
    if (data->cursordrag == CURSORDRAG_ENDSEL)
    {
      if (sy < cy)
      {
        window_copy_redraw_lines(wp, sy, (cy - sy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (sy - cy) + 1);
    }
    else
    {
      if (endsy < cy)
      {
        window_copy_redraw_lines(wp, endsy, (cy - endsy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (endsy - cy) + 1);
    }
  }
  return 1;
}


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
static u_int window_copy_find_length(struct window_pane *wp, u_int py)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = data->backing;
  struct grid_cell gc;
  u_int px;
  px = s->grid->linedata[py].cellsize;
  if (px > s->grid->sx)
  {
    px = s->grid->sx;
  }
  while (px > 0)
  {
    grid_get_cell(s->grid, px - 1, py, &gc);
    if ((gc.data.size != 1) || ((*gc.data.data) != ' '))
    {
      break;
    }
    px -= 1;
  }

  return px;
}


----------------------------
static void window_copy_redraw_lines(struct window_pane *wp, u_int py, u_int ny)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen_write_ctx ctx;
  u_int i;
  screen_write_start(&ctx, wp, 0);
  for (i = py; i < (py + ny); i += 1)
  {
    window_copy_write_line(wp, &ctx, i);
  }

  screen_write_cursormove(&ctx, data->cx, data->cy);
  screen_write_stop(&ctx);
}


----------------------------
None
----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
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
static void window_copy_update_cursor(struct window_pane *wp, u_int cx, u_int cy)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct screen_write_ctx ctx;
  u_int old_cx;
  u_int old_cy;
  old_cx = data->cx;
  old_cy = data->cy;
  data->cx = cx;
  data->cy = cy;
  if (old_cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, old_cy, 1);
  }
  if (data->cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, data->cy, 1);
  }
  else
  {
    screen_write_start(&ctx, wp, 0);
    screen_write_cursormove(&ctx, data->cx, data->cy);
    screen_write_stop(&ctx);
  }
}


----------------------------
None
----------------------------
***/


static void window_copy_cursor_jump_back(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *back_s = data->backing;
  struct grid_cell gc;
  u_int px;
  u_int py;
  px = data->cx;
  py = (back_s->grid->hsize + data->cy) - data->oy;
  if (px > 0)
  {
    px -= 1;
  }
  for (;;)
  {
    grid_get_cell(back_s->grid, px, py, &gc);
    if (((!(gc.flags & 0x4)) && (gc.data.size == 1)) && ((*gc.data.data) == data->jumpchar))
    {
      window_copy_update_cursor(wp, px, data->cy);
      if (window_copy_update_selection(wp, 1))
      {
        window_copy_redraw_lines(wp, data->cy, 1);
      }
      return;
    }
    if (px == 0)
    {
      break;
    }
    px -= 1;
  }

}


/*** DEPENDENCIES:
static int window_copy_update_selection(struct window_pane *wp, int may_redraw)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct options *oo = wp->window->options;
  struct grid_cell gc;
  u_int sx;
  u_int sy;
  u_int cy;
  u_int endsx;
  u_int endsy;
  int startrelpos;
  int endrelpos;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return 0;
  }
  window_copy_synchronize_cursor(wp);
  sx = data->selx;
  sy = data->sely;
  startrelpos = window_copy_adjust_selection(wp, &sx, &sy);
  endsx = data->endselx;
  endsy = data->endsely;
  endrelpos = window_copy_adjust_selection(wp, &endsx, &endsy);
  if ((startrelpos == endrelpos) && (startrelpos != WINDOW_COPY_REL_POS_ON_SCREEN))
  {
    screen_hide_selection(s);
    return 0;
  }
  style_apply(&gc, oo, "mode-style");
  gc.flags |= 0x20;
  screen_set_selection(s, sx, sy, endsx, endsy, data->rectflag, &gc);
  if (data->rectflag && may_redraw)
  {
    cy = data->cy;
    if (data->cursordrag == CURSORDRAG_ENDSEL)
    {
      if (sy < cy)
      {
        window_copy_redraw_lines(wp, sy, (cy - sy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (sy - cy) + 1);
    }
    else
    {
      if (endsy < cy)
      {
        window_copy_redraw_lines(wp, endsy, (cy - endsy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (endsy - cy) + 1);
    }
  }
  return 1;
}


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
static void window_copy_redraw_lines(struct window_pane *wp, u_int py, u_int ny)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen_write_ctx ctx;
  u_int i;
  screen_write_start(&ctx, wp, 0);
  for (i = py; i < (py + ny); i += 1)
  {
    window_copy_write_line(wp, &ctx, i);
  }

  screen_write_cursormove(&ctx, data->cx, data->cy);
  screen_write_stop(&ctx);
}


----------------------------
None
----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
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
static void window_copy_update_cursor(struct window_pane *wp, u_int cx, u_int cy)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct screen_write_ctx ctx;
  u_int old_cx;
  u_int old_cy;
  old_cx = data->cx;
  old_cy = data->cy;
  data->cx = cx;
  data->cy = cy;
  if (old_cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, old_cy, 1);
  }
  if (data->cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, data->cy, 1);
  }
  else
  {
    screen_write_start(&ctx, wp, 0);
    screen_write_cursormove(&ctx, data->cx, data->cy);
    screen_write_stop(&ctx);
  }
}


----------------------------
None
----------------------------
***/


static void window_copy_cursor_jump(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *back_s = data->backing;
  struct grid_cell gc;
  u_int px;
  u_int py;
  u_int xx;
  px = data->cx + 1;
  py = (back_s->grid->hsize + data->cy) - data->oy;
  xx = window_copy_find_length(wp, py);
  while (px < xx)
  {
    grid_get_cell(back_s->grid, px, py, &gc);
    if (((!(gc.flags & 0x4)) && (gc.data.size == 1)) && ((*gc.data.data) == data->jumpchar))
    {
      window_copy_update_cursor(wp, px, data->cy);
      if (window_copy_update_selection(wp, 1))
      {
        window_copy_redraw_lines(wp, data->cy, 1);
      }
      return;
    }
    px += 1;
  }

}


/*** DEPENDENCIES:
static int window_copy_update_selection(struct window_pane *wp, int may_redraw)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct options *oo = wp->window->options;
  struct grid_cell gc;
  u_int sx;
  u_int sy;
  u_int cy;
  u_int endsx;
  u_int endsy;
  int startrelpos;
  int endrelpos;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return 0;
  }
  window_copy_synchronize_cursor(wp);
  sx = data->selx;
  sy = data->sely;
  startrelpos = window_copy_adjust_selection(wp, &sx, &sy);
  endsx = data->endselx;
  endsy = data->endsely;
  endrelpos = window_copy_adjust_selection(wp, &endsx, &endsy);
  if ((startrelpos == endrelpos) && (startrelpos != WINDOW_COPY_REL_POS_ON_SCREEN))
  {
    screen_hide_selection(s);
    return 0;
  }
  style_apply(&gc, oo, "mode-style");
  gc.flags |= 0x20;
  screen_set_selection(s, sx, sy, endsx, endsy, data->rectflag, &gc);
  if (data->rectflag && may_redraw)
  {
    cy = data->cy;
    if (data->cursordrag == CURSORDRAG_ENDSEL)
    {
      if (sy < cy)
      {
        window_copy_redraw_lines(wp, sy, (cy - sy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (sy - cy) + 1);
    }
    else
    {
      if (endsy < cy)
      {
        window_copy_redraw_lines(wp, endsy, (cy - endsy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (endsy - cy) + 1);
    }
  }
  return 1;
}


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
static u_int window_copy_find_length(struct window_pane *wp, u_int py)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = data->backing;
  struct grid_cell gc;
  u_int px;
  px = s->grid->linedata[py].cellsize;
  if (px > s->grid->sx)
  {
    px = s->grid->sx;
  }
  while (px > 0)
  {
    grid_get_cell(s->grid, px - 1, py, &gc);
    if ((gc.data.size != 1) || ((*gc.data.data) != ' '))
    {
      break;
    }
    px -= 1;
  }

  return px;
}


----------------------------
static void window_copy_redraw_lines(struct window_pane *wp, u_int py, u_int ny)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen_write_ctx ctx;
  u_int i;
  screen_write_start(&ctx, wp, 0);
  for (i = py; i < (py + ny); i += 1)
  {
    window_copy_write_line(wp, &ctx, i);
  }

  screen_write_cursormove(&ctx, data->cx, data->cy);
  screen_write_stop(&ctx);
}


----------------------------
None
----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
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
static void window_copy_update_cursor(struct window_pane *wp, u_int cx, u_int cy)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct screen_write_ctx ctx;
  u_int old_cx;
  u_int old_cy;
  old_cx = data->cx;
  old_cy = data->cy;
  data->cx = cx;
  data->cy = cy;
  if (old_cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, old_cy, 1);
  }
  if (data->cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, data->cy, 1);
  }
  else
  {
    screen_write_start(&ctx, wp, 0);
    screen_write_cursormove(&ctx, data->cx, data->cy);
    screen_write_stop(&ctx);
  }
}


----------------------------
None
----------------------------
***/


static void window_copy_cursor_jump_to_back(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *back_s = data->backing;
  struct grid_cell gc;
  u_int px;
  u_int py;
  px = data->cx;
  py = (back_s->grid->hsize + data->cy) - data->oy;
  if (px > 0)
  {
    px -= 1;
  }
  if (px > 0)
  {
    px -= 1;
  }
  for (;;)
  {
    grid_get_cell(back_s->grid, px, py, &gc);
    if (((!(gc.flags & 0x4)) && (gc.data.size == 1)) && ((*gc.data.data) == data->jumpchar))
    {
      window_copy_update_cursor(wp, px + 1, data->cy);
      if (window_copy_update_selection(wp, 1))
      {
        window_copy_redraw_lines(wp, data->cy, 1);
      }
      return;
    }
    if (px == 0)
    {
      break;
    }
    px -= 1;
  }

}


/*** DEPENDENCIES:
static int window_copy_update_selection(struct window_pane *wp, int may_redraw)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct options *oo = wp->window->options;
  struct grid_cell gc;
  u_int sx;
  u_int sy;
  u_int cy;
  u_int endsx;
  u_int endsy;
  int startrelpos;
  int endrelpos;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return 0;
  }
  window_copy_synchronize_cursor(wp);
  sx = data->selx;
  sy = data->sely;
  startrelpos = window_copy_adjust_selection(wp, &sx, &sy);
  endsx = data->endselx;
  endsy = data->endsely;
  endrelpos = window_copy_adjust_selection(wp, &endsx, &endsy);
  if ((startrelpos == endrelpos) && (startrelpos != WINDOW_COPY_REL_POS_ON_SCREEN))
  {
    screen_hide_selection(s);
    return 0;
  }
  style_apply(&gc, oo, "mode-style");
  gc.flags |= 0x20;
  screen_set_selection(s, sx, sy, endsx, endsy, data->rectflag, &gc);
  if (data->rectflag && may_redraw)
  {
    cy = data->cy;
    if (data->cursordrag == CURSORDRAG_ENDSEL)
    {
      if (sy < cy)
      {
        window_copy_redraw_lines(wp, sy, (cy - sy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (sy - cy) + 1);
    }
    else
    {
      if (endsy < cy)
      {
        window_copy_redraw_lines(wp, endsy, (cy - endsy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (endsy - cy) + 1);
    }
  }
  return 1;
}


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
static void window_copy_redraw_lines(struct window_pane *wp, u_int py, u_int ny)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen_write_ctx ctx;
  u_int i;
  screen_write_start(&ctx, wp, 0);
  for (i = py; i < (py + ny); i += 1)
  {
    window_copy_write_line(wp, &ctx, i);
  }

  screen_write_cursormove(&ctx, data->cx, data->cy);
  screen_write_stop(&ctx);
}


----------------------------
None
----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
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
static void window_copy_update_cursor(struct window_pane *wp, u_int cx, u_int cy)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct screen_write_ctx ctx;
  u_int old_cx;
  u_int old_cy;
  old_cx = data->cx;
  old_cy = data->cy;
  data->cx = cx;
  data->cy = cy;
  if (old_cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, old_cy, 1);
  }
  if (data->cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, data->cy, 1);
  }
  else
  {
    screen_write_start(&ctx, wp, 0);
    screen_write_cursormove(&ctx, data->cx, data->cy);
    screen_write_stop(&ctx);
  }
}


----------------------------
None
----------------------------
***/


// hint:  ['np_ref is a mutable refrence to u_int']
void helper_helper_window_copy_command_2_1(u_int * const np_ref, struct window_pane * const wp, struct window_copy_mode_data * const data)
{
  u_int np = *np_ref;
  switch (data->jumptype)
  {
    case WINDOW_COPY_JUMPFORWARD:
    {
      for (; np != 0; np -= 1)
      {
        window_copy_cursor_jump(wp);
      }

      break;
    }

    case WINDOW_COPY_JUMPBACKWARD:
    {
      for (; np != 0; np -= 1)
      {
        window_copy_cursor_jump_back(wp);
      }

      break;
    }

    case WINDOW_COPY_JUMPTOFORWARD:
    {
      for (; np != 0; np -= 1)
      {
        window_copy_cursor_jump_to(wp);
      }

      break;
    }

    case WINDOW_COPY_JUMPTOBACKWARD:
    {
      for (; np != 0; np -= 1)
      {
        window_copy_cursor_jump_to_back(wp);
      }

      break;
    }

  }

  *np_ref = np;
}


/*** DEPENDENCIES:
static void window_copy_cursor_jump_to(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *back_s = data->backing;
  struct grid_cell gc;
  u_int px;
  u_int py;
  u_int xx;
  px = data->cx + 2;
  py = (back_s->grid->hsize + data->cy) - data->oy;
  xx = window_copy_find_length(wp, py);
  while (px < xx)
  {
    grid_get_cell(back_s->grid, px, py, &gc);
    if (((!(gc.flags & 0x4)) && (gc.data.size == 1)) && ((*gc.data.data) == data->jumpchar))
    {
      window_copy_update_cursor(wp, px - 1, data->cy);
      if (window_copy_update_selection(wp, 1))
      {
        window_copy_redraw_lines(wp, data->cy, 1);
      }
      return;
    }
    px += 1;
  }

}


----------------------------
static void window_copy_cursor_jump_back(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *back_s = data->backing;
  struct grid_cell gc;
  u_int px;
  u_int py;
  px = data->cx;
  py = (back_s->grid->hsize + data->cy) - data->oy;
  if (px > 0)
  {
    px -= 1;
  }
  for (;;)
  {
    grid_get_cell(back_s->grid, px, py, &gc);
    if (((!(gc.flags & 0x4)) && (gc.data.size == 1)) && ((*gc.data.data) == data->jumpchar))
    {
      window_copy_update_cursor(wp, px, data->cy);
      if (window_copy_update_selection(wp, 1))
      {
        window_copy_redraw_lines(wp, data->cy, 1);
      }
      return;
    }
    if (px == 0)
    {
      break;
    }
    px -= 1;
  }

}


----------------------------
static void window_copy_cursor_jump(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *back_s = data->backing;
  struct grid_cell gc;
  u_int px;
  u_int py;
  u_int xx;
  px = data->cx + 1;
  py = (back_s->grid->hsize + data->cy) - data->oy;
  xx = window_copy_find_length(wp, py);
  while (px < xx)
  {
    grid_get_cell(back_s->grid, px, py, &gc);
    if (((!(gc.flags & 0x4)) && (gc.data.size == 1)) && ((*gc.data.data) == data->jumpchar))
    {
      window_copy_update_cursor(wp, px, data->cy);
      if (window_copy_update_selection(wp, 1))
      {
        window_copy_redraw_lines(wp, data->cy, 1);
      }
      return;
    }
    px += 1;
  }

}


----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
static void window_copy_cursor_jump_to_back(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *back_s = data->backing;
  struct grid_cell gc;
  u_int px;
  u_int py;
  px = data->cx;
  py = (back_s->grid->hsize + data->cy) - data->oy;
  if (px > 0)
  {
    px -= 1;
  }
  if (px > 0)
  {
    px -= 1;
  }
  for (;;)
  {
    grid_get_cell(back_s->grid, px, py, &gc);
    if (((!(gc.flags & 0x4)) && (gc.data.size == 1)) && ((*gc.data.data) == data->jumpchar))
    {
      window_copy_update_cursor(wp, px + 1, data->cy);
      if (window_copy_update_selection(wp, 1))
      {
        window_copy_redraw_lines(wp, data->cy, 1);
      }
      return;
    }
    if (px == 0)
    {
      break;
    }
    px -= 1;
  }

}


----------------------------
None
----------------------------
***/


// hint:  ['np_ref is a mutable refrence to u_int']
void helper_helper_window_copy_command_2_2(u_int * const np_ref, struct window_pane * const wp, struct window_copy_mode_data * const data)
{
  u_int np = *np_ref;
  switch (data->jumptype)
  {
    case WINDOW_COPY_JUMPFORWARD:
    {
      for (; np != 0; np -= 1)
      {
        window_copy_cursor_jump_back(wp);
      }

      break;
    }

    case WINDOW_COPY_JUMPBACKWARD:
    {
      for (; np != 0; np -= 1)
      {
        window_copy_cursor_jump(wp);
      }

      break;
    }

    case WINDOW_COPY_JUMPTOFORWARD:
    {
      for (; np != 0; np -= 1)
      {
        window_copy_cursor_jump_to_back(wp);
      }

      break;
    }

    case WINDOW_COPY_JUMPTOBACKWARD:
    {
      for (; np != 0; np -= 1)
      {
        window_copy_cursor_jump_to(wp);
      }

      break;
    }

  }

  *np_ref = np;
}


/*** DEPENDENCIES:
static void window_copy_cursor_jump_to(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *back_s = data->backing;
  struct grid_cell gc;
  u_int px;
  u_int py;
  u_int xx;
  px = data->cx + 2;
  py = (back_s->grid->hsize + data->cy) - data->oy;
  xx = window_copy_find_length(wp, py);
  while (px < xx)
  {
    grid_get_cell(back_s->grid, px, py, &gc);
    if (((!(gc.flags & 0x4)) && (gc.data.size == 1)) && ((*gc.data.data) == data->jumpchar))
    {
      window_copy_update_cursor(wp, px - 1, data->cy);
      if (window_copy_update_selection(wp, 1))
      {
        window_copy_redraw_lines(wp, data->cy, 1);
      }
      return;
    }
    px += 1;
  }

}


----------------------------
static void window_copy_cursor_jump_back(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *back_s = data->backing;
  struct grid_cell gc;
  u_int px;
  u_int py;
  px = data->cx;
  py = (back_s->grid->hsize + data->cy) - data->oy;
  if (px > 0)
  {
    px -= 1;
  }
  for (;;)
  {
    grid_get_cell(back_s->grid, px, py, &gc);
    if (((!(gc.flags & 0x4)) && (gc.data.size == 1)) && ((*gc.data.data) == data->jumpchar))
    {
      window_copy_update_cursor(wp, px, data->cy);
      if (window_copy_update_selection(wp, 1))
      {
        window_copy_redraw_lines(wp, data->cy, 1);
      }
      return;
    }
    if (px == 0)
    {
      break;
    }
    px -= 1;
  }

}


----------------------------
static void window_copy_cursor_jump(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *back_s = data->backing;
  struct grid_cell gc;
  u_int px;
  u_int py;
  u_int xx;
  px = data->cx + 1;
  py = (back_s->grid->hsize + data->cy) - data->oy;
  xx = window_copy_find_length(wp, py);
  while (px < xx)
  {
    grid_get_cell(back_s->grid, px, py, &gc);
    if (((!(gc.flags & 0x4)) && (gc.data.size == 1)) && ((*gc.data.data) == data->jumpchar))
    {
      window_copy_update_cursor(wp, px, data->cy);
      if (window_copy_update_selection(wp, 1))
      {
        window_copy_redraw_lines(wp, data->cy, 1);
      }
      return;
    }
    px += 1;
  }

}


----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
static void window_copy_cursor_jump_to_back(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *back_s = data->backing;
  struct grid_cell gc;
  u_int px;
  u_int py;
  px = data->cx;
  py = (back_s->grid->hsize + data->cy) - data->oy;
  if (px > 0)
  {
    px -= 1;
  }
  if (px > 0)
  {
    px -= 1;
  }
  for (;;)
  {
    grid_get_cell(back_s->grid, px, py, &gc);
    if (((!(gc.flags & 0x4)) && (gc.data.size == 1)) && ((*gc.data.data) == data->jumpchar))
    {
      window_copy_update_cursor(wp, px + 1, data->cy);
      if (window_copy_update_selection(wp, 1))
      {
        window_copy_redraw_lines(wp, data->cy, 1);
      }
      return;
    }
    if (px == 0)
    {
      break;
    }
    px -= 1;
  }

}


----------------------------
None
----------------------------
***/


static void window_copy_copy_pipe(struct window_pane *wp, struct session *s, const char *bufname, const char *arg)
{
  void *buf;
  unsigned int buf_idx = 0;
  size_t len;
  struct job *job;
  unsigned int job_idx = 0;
  char *expanded;
  unsigned int expanded_idx = 0;
  buf_idx = window_copy_get_selection(wp, &len);
  if ((&buf[buf_idx]) == 0)
  {
    return;
  }
  expanded_idx = format_single(0, arg, 0, s, 0, wp);
  job_idx = job_run(expanded, s, 0, 0, 0, 0, 0, 0x1);
  bufferevent_write(job->event, buf, len);
  free(expanded);
  window_copy_copy_buffer(wp, bufname, buf, len);
}


/*** DEPENDENCIES:
struct job *job_run(const char *cmd, struct session *s, const char *cwd, job_update_cb updatecb, job_complete_cb completecb, job_free_cb freecb, void *data, int flags)
{
  struct job *job;
  unsigned int job_idx = 0;
  struct environ *env;
  unsigned int env_idx = 0;
  pid_t pid;
  int nullfd;
  int out[2];
  const char *home;
  unsigned int home_idx = 0;
  sigset_t set;
  sigset_t oldset;
  if (socketpair(AF_UNIX, SOCK_STREAM, PF_UNSPEC, out) != 0)
  {
    return 0;
  }
  env_idx = environ_for_session(s, !cfg_finished);
  sigfillset(&set);
  sigprocmask(SIG_BLOCK, &set, &oldset);
  switch (pid = fork())
  {
    case -1:
    {
      sigprocmask(SIG_SETMASK, &oldset, 0);
      environ_free(env);
      close(out[0]);
      close(out[1]);
      return 0;
    }

    case 0:
    {
      helper_job_run_1(&nullfd, &home_idx, cmd, cwd, env, out, home, oldset);
    }

  }

  sigprocmask(SIG_SETMASK, &oldset, 0);
  environ_free(env);
  close(out[1]);
  job_idx = xmalloc(sizeof(*job_idx));
  job->state = JOB_RUNNING;
  job->flags = flags;
  job->cmd = xstrdup(cmd);
  job->pid = pid;
  job->status = 0;
  do
  {
    if ((job->entry.le_next = (&all_jobs)->lh_first) != 0)
    {
      (&all_jobs)->lh_first->entry.le_prev = &job->entry.le_next;
    }
    (&all_jobs)->lh_first = &job[job_idx];
    job->entry.le_prev = &(&all_jobs)->lh_first;
  }
  while (0);
  job->updatecb = updatecb;
  job->completecb = completecb;
  job->freecb = freecb;
  job->data = data;
  job->fd = out[0];
  setblocking(job->fd, 0);
  job->event = bufferevent_new(job->fd, job_read_callback, job_write_callback, job_error_callback, job);
  bufferevent_enable(job->event, EV_READ | EV_WRITE);
  log_debug("run job %p: %s, pid %ld", job, job->cmd, (long) job->pid);
  return job;
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
static void *window_copy_get_selection(struct window_pane *wp, size_t *len)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  char *buf;
  unsigned int buf_idx = 0;
  size_t off;
  u_int i;
  u_int xx;
  u_int yy;
  u_int sx;
  u_int sy;
  u_int ex;
  u_int ey;
  u_int ey_last;
  u_int firstsx;
  u_int lastex;
  u_int restex;
  u_int restsx;
  u_int selx;
  int keys;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return 0;
  }
  buf_idx = xmalloc(1);
  off = 0;
  buf[buf_idx] = '\0';
  xx = data->endselx;
  yy = data->endsely;
  if ((yy < data->sely) || ((yy == data->sely) && (xx < data->selx)))
  {
    sx = xx;
    sy = yy;
    ex = data->selx;
    ey = data->sely;
  }
  else
  {
    sx = data->selx;
    sy = data->sely;
    ex = xx;
    ey = yy;
  }
  ey_last = window_copy_find_length(wp, ey);
  if (ex > ey_last)
  {
    ex = ey_last;
  }
  xx = s->grid->sx;
  keys = options_get_number(wp->window->options, "mode-keys");
  if (data->rectflag)
  {
    helper_window_copy_get_selection_1(&firstsx, &lastex, &restex, &restsx, &selx, data, keys);
  }
  else
  {
    if (keys == 0)
    {
      lastex = ex;
    }
    else
      lastex = ex + 1;
    restex = xx;
    firstsx = sx;
    restsx = 0;
  }
  for (i = sy; i <= ey; i += 1)
  {
    window_copy_copy_line(wp, &(&buf[buf_idx]), &off, i, (i == sy) ? (firstsx) : (restsx), (i == ey) ? (lastex) : (restex));
  }

  if (off == 0)
  {
    free(buf);
    return 0;
  }
  if ((keys == 0) || (lastex <= ey_last))
  {
    off -= 1;
  }
  *len = off;
  return buf;
}


----------------------------
struct job
{
  enum 
  {
    JOB_RUNNING,
    JOB_DEAD,
    JOB_CLOSED
  } state;
  int flags;
  char *cmd;
  pid_t pid;
  int status;
  int fd;
  struct bufferevent *event;
  job_update_cb updatecb;
  job_complete_cb completecb;
  job_free_cb freecb;
  void *data;
  struct 
  {
    struct job *le_next;
    struct job **le_prev;
  } entry;
}
----------------------------
static void window_copy_copy_buffer(struct window_pane *wp, const char *bufname, void *buf, size_t len)
{
  struct screen_write_ctx ctx;
  if (options_get_number(global_options, "set-clipboard") != 0)
  {
    screen_write_start(&ctx, wp, 0);
    screen_write_setselection(&ctx, buf, len);
    screen_write_stop(&ctx);
    notify_pane("pane-set-clipboard", wp);
  }
  if (paste_set(buf, len, bufname, 0) != 0)
  {
    free(buf);
  }
}


----------------------------
None
----------------------------
***/


static void window_copy_scroll_up(struct window_pane *wp, u_int ny)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct screen_write_ctx ctx;
  if (data->oy < ny)
  {
    ny = data->oy;
  }
  if (ny == 0)
  {
    return;
  }
  data->oy -= ny;
  window_copy_update_selection(wp, 0);
  screen_write_start(&ctx, wp, 0);
  screen_write_cursormove(&ctx, 0, 0);
  screen_write_deleteline(&ctx, ny, 8);
  window_copy_write_lines(wp, &ctx, s->grid->sy - ny, ny);
  window_copy_write_line(wp, &ctx, 0);
  if (s->grid->sy > 1)
  {
    window_copy_write_line(wp, &ctx, 1);
  }
  if (s->grid->sy > 3)
  {
    window_copy_write_line(wp, &ctx, s->grid->sy - 2);
  }
  if (s->sel.flag && (s->grid->sy > ny))
  {
    window_copy_write_line(wp, &ctx, (s->grid->sy - ny) - 1);
  }
  screen_write_cursormove(&ctx, data->cx, data->cy);
  screen_write_stop(&ctx);
}


/*** DEPENDENCIES:
static void window_copy_write_lines(struct window_pane *wp, struct screen_write_ctx *ctx, u_int py, u_int ny)
{
  u_int yy;
  for (yy = py; yy < (py + ny); yy += 1)
  {
    window_copy_write_line(wp, ctx, py);
  }

}


----------------------------
static void window_copy_write_line(struct window_pane *wp, struct screen_write_ctx *ctx, u_int py)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct options *oo = wp->window->options;
  struct grid_cell gc;
  char hdr[512];
  size_t size = 0;
  style_apply(&gc, oo, "mode-style");
  gc.flags |= 0x20;
  if (py == 0)
  {
    if (data->searchmark == 0)
    {
      size = xsnprintf(hdr, sizeof(hdr), "[%u/%u]", data->oy, data->backing->grid->hsize);
    }
    else
    {
      if (data->searchthis == (-1))
      {
        size = xsnprintf(hdr, sizeof(hdr), "(%u results) [%d/%u]", data->searchcount, data->oy, data->backing->grid->hsize);
      }
      else
      {
        size = xsnprintf(hdr, sizeof(hdr), "(%u/%u results) [%d/%u]", data->searchthis, data->searchcount, data->oy, data->backing->grid->hsize);
      }
    }
    if (size > s->grid->sx)
    {
      size = s->grid->sx;
    }
    screen_write_cursormove(ctx, s->grid->sx - size, 0);
    screen_write_puts(ctx, &gc, "%s", hdr);
  }
  else
    size = 0;
  if (size < s->grid->sx)
  {
    screen_write_cursormove(ctx, 0, py);
    screen_write_copy(ctx, data->backing, 0, (data->backing->grid->hsize - data->oy) + py, s->grid->sx - size, 1, data->searchmark, &gc);
  }
  if ((py == data->cy) && (data->cx == s->grid->sx))
  {
    memcpy(&gc, &grid_default_cell, sizeof(gc));
    screen_write_cursormove(ctx, s->grid->sx - 1, py);
    screen_write_putc(ctx, &gc, '$');
  }
}


----------------------------
static int window_copy_update_selection(struct window_pane *wp, int may_redraw)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct options *oo = wp->window->options;
  struct grid_cell gc;
  u_int sx;
  u_int sy;
  u_int cy;
  u_int endsx;
  u_int endsy;
  int startrelpos;
  int endrelpos;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return 0;
  }
  window_copy_synchronize_cursor(wp);
  sx = data->selx;
  sy = data->sely;
  startrelpos = window_copy_adjust_selection(wp, &sx, &sy);
  endsx = data->endselx;
  endsy = data->endsely;
  endrelpos = window_copy_adjust_selection(wp, &endsx, &endsy);
  if ((startrelpos == endrelpos) && (startrelpos != WINDOW_COPY_REL_POS_ON_SCREEN))
  {
    screen_hide_selection(s);
    return 0;
  }
  style_apply(&gc, oo, "mode-style");
  gc.flags |= 0x20;
  screen_set_selection(s, sx, sy, endsx, endsy, data->rectflag, &gc);
  if (data->rectflag && may_redraw)
  {
    cy = data->cy;
    if (data->cursordrag == CURSORDRAG_ENDSEL)
    {
      if (sy < cy)
      {
        window_copy_redraw_lines(wp, sy, (cy - sy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (sy - cy) + 1);
    }
    else
    {
      if (endsy < cy)
      {
        window_copy_redraw_lines(wp, endsy, (cy - endsy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (endsy - cy) + 1);
    }
  }
  return 1;
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
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
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
None
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
None
----------------------------
***/


static void window_copy_scroll_down(struct window_pane *wp, u_int ny)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct screen_write_ctx ctx;
  if (ny > data->backing->grid->hsize)
  {
    return;
  }
  if (data->oy > (data->backing->grid->hsize - ny))
  {
    ny = data->backing->grid->hsize - data->oy;
  }
  if (ny == 0)
  {
    return;
  }
  data->oy += ny;
  window_copy_update_selection(wp, 0);
  screen_write_start(&ctx, wp, 0);
  screen_write_cursormove(&ctx, 0, 0);
  screen_write_insertline(&ctx, ny, 8);
  window_copy_write_lines(wp, &ctx, 0, ny);
  if (s->sel.flag && (s->grid->sy > ny))
  {
    window_copy_write_line(wp, &ctx, ny);
  }
  else
    if (ny == 1)
  {
    window_copy_write_line(wp, &ctx, 1);
  }
  screen_write_cursormove(&ctx, data->cx, data->cy);
  screen_write_stop(&ctx);
}


/*** DEPENDENCIES:
static void window_copy_write_lines(struct window_pane *wp, struct screen_write_ctx *ctx, u_int py, u_int ny)
{
  u_int yy;
  for (yy = py; yy < (py + ny); yy += 1)
  {
    window_copy_write_line(wp, ctx, py);
  }

}


----------------------------
static void window_copy_write_line(struct window_pane *wp, struct screen_write_ctx *ctx, u_int py)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct options *oo = wp->window->options;
  struct grid_cell gc;
  char hdr[512];
  size_t size = 0;
  style_apply(&gc, oo, "mode-style");
  gc.flags |= 0x20;
  if (py == 0)
  {
    if (data->searchmark == 0)
    {
      size = xsnprintf(hdr, sizeof(hdr), "[%u/%u]", data->oy, data->backing->grid->hsize);
    }
    else
    {
      if (data->searchthis == (-1))
      {
        size = xsnprintf(hdr, sizeof(hdr), "(%u results) [%d/%u]", data->searchcount, data->oy, data->backing->grid->hsize);
      }
      else
      {
        size = xsnprintf(hdr, sizeof(hdr), "(%u/%u results) [%d/%u]", data->searchthis, data->searchcount, data->oy, data->backing->grid->hsize);
      }
    }
    if (size > s->grid->sx)
    {
      size = s->grid->sx;
    }
    screen_write_cursormove(ctx, s->grid->sx - size, 0);
    screen_write_puts(ctx, &gc, "%s", hdr);
  }
  else
    size = 0;
  if (size < s->grid->sx)
  {
    screen_write_cursormove(ctx, 0, py);
    screen_write_copy(ctx, data->backing, 0, (data->backing->grid->hsize - data->oy) + py, s->grid->sx - size, 1, data->searchmark, &gc);
  }
  if ((py == data->cy) && (data->cx == s->grid->sx))
  {
    memcpy(&gc, &grid_default_cell, sizeof(gc));
    screen_write_cursormove(ctx, s->grid->sx - 1, py);
    screen_write_putc(ctx, &gc, '$');
  }
}


----------------------------
static int window_copy_update_selection(struct window_pane *wp, int may_redraw)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct options *oo = wp->window->options;
  struct grid_cell gc;
  u_int sx;
  u_int sy;
  u_int cy;
  u_int endsx;
  u_int endsy;
  int startrelpos;
  int endrelpos;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return 0;
  }
  window_copy_synchronize_cursor(wp);
  sx = data->selx;
  sy = data->sely;
  startrelpos = window_copy_adjust_selection(wp, &sx, &sy);
  endsx = data->endselx;
  endsy = data->endsely;
  endrelpos = window_copy_adjust_selection(wp, &endsx, &endsy);
  if ((startrelpos == endrelpos) && (startrelpos != WINDOW_COPY_REL_POS_ON_SCREEN))
  {
    screen_hide_selection(s);
    return 0;
  }
  style_apply(&gc, oo, "mode-style");
  gc.flags |= 0x20;
  screen_set_selection(s, sx, sy, endsx, endsy, data->rectflag, &gc);
  if (data->rectflag && may_redraw)
  {
    cy = data->cy;
    if (data->cursordrag == CURSORDRAG_ENDSEL)
    {
      if (sy < cy)
      {
        window_copy_redraw_lines(wp, sy, (cy - sy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (sy - cy) + 1);
    }
    else
    {
      if (endsy < cy)
      {
        window_copy_redraw_lines(wp, endsy, (cy - endsy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (endsy - cy) + 1);
    }
  }
  return 1;
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
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
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
None
----------------------------
None
----------------------------
***/


void window_copy_pageup(struct window_pane *wp, int half_page)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  u_int n;
  u_int ox;
  u_int oy;
  u_int px;
  u_int py;
  oy = (data->backing->grid->hsize + data->cy) - data->oy;
  ox = window_copy_find_length(wp, oy);
  if ((s->sel.lineflag == LINE_SEL_LEFT_RIGHT) && (oy == data->sely))
  {
    window_copy_other_end(wp);
  }
  if (data->cx != ox)
  {
    data->lastcx = data->cx;
    data->lastsx = ox;
  }
  data->cx = data->lastcx;
  n = 1;
  if (s->grid->sy > 2)
  {
    if (half_page)
    {
      n = s->grid->sy / 2;
    }
    else
      n = s->grid->sy - 2;
  }
  if ((data->oy + n) > data->backing->grid->hsize)
  {
    data->oy = data->backing->grid->hsize;
  }
  else
    data->oy += n;
  if ((!data->screen.sel.flag) || (!data->rectflag))
  {
    py = (data->backing->grid->hsize + data->cy) - data->oy;
    px = window_copy_find_length(wp, py);
    if (((data->cx >= data->lastsx) && (data->cx != px)) || (data->cx > px))
    {
      window_copy_cursor_end_of_line(wp);
    }
  }
  window_copy_update_selection(wp, 1);
  window_copy_redraw_screen(wp);
}


/*** DEPENDENCIES:
static int window_copy_update_selection(struct window_pane *wp, int may_redraw)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct options *oo = wp->window->options;
  struct grid_cell gc;
  u_int sx;
  u_int sy;
  u_int cy;
  u_int endsx;
  u_int endsy;
  int startrelpos;
  int endrelpos;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return 0;
  }
  window_copy_synchronize_cursor(wp);
  sx = data->selx;
  sy = data->sely;
  startrelpos = window_copy_adjust_selection(wp, &sx, &sy);
  endsx = data->endselx;
  endsy = data->endsely;
  endrelpos = window_copy_adjust_selection(wp, &endsx, &endsy);
  if ((startrelpos == endrelpos) && (startrelpos != WINDOW_COPY_REL_POS_ON_SCREEN))
  {
    screen_hide_selection(s);
    return 0;
  }
  style_apply(&gc, oo, "mode-style");
  gc.flags |= 0x20;
  screen_set_selection(s, sx, sy, endsx, endsy, data->rectflag, &gc);
  if (data->rectflag && may_redraw)
  {
    cy = data->cy;
    if (data->cursordrag == CURSORDRAG_ENDSEL)
    {
      if (sy < cy)
      {
        window_copy_redraw_lines(wp, sy, (cy - sy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (sy - cy) + 1);
    }
    else
    {
      if (endsy < cy)
      {
        window_copy_redraw_lines(wp, endsy, (cy - endsy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (endsy - cy) + 1);
    }
  }
  return 1;
}


----------------------------
static void window_copy_other_end(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  u_int selx;
  u_int sely;
  u_int cy;
  u_int yy;
  u_int hsize;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return;
  }
  if (s->sel.lineflag == LINE_SEL_LEFT_RIGHT)
  {
    s->sel.lineflag = LINE_SEL_RIGHT_LEFT;
  }
  else
    if (s->sel.lineflag == LINE_SEL_RIGHT_LEFT)
  {
    s->sel.lineflag = LINE_SEL_LEFT_RIGHT;
  }
  switch (data->cursordrag)
  {
    case CURSORDRAG_NONE:

    case CURSORDRAG_SEL:
    {
      data->cursordrag = CURSORDRAG_ENDSEL;
      break;
    }

    case CURSORDRAG_ENDSEL:
    {
      data->cursordrag = CURSORDRAG_SEL;
      break;
    }

  }

  selx = data->endselx;
  sely = data->endsely;
  if (data->cursordrag == CURSORDRAG_SEL)
  {
    selx = data->selx;
    sely = data->sely;
  }
  cy = data->cy;
  yy = (data->backing->grid->hsize + data->cy) - data->oy;
  data->cx = selx;
  hsize = data->backing->grid->hsize;
  if (sely < (hsize - data->oy))
  {
    data->oy = hsize - sely;
    data->cy = 0;
  }
  else
    if (sely > ((hsize - data->oy) + s->grid->sy))
  {
    data->oy = ((hsize - sely) + s->grid->sy) - 1;
    data->cy = s->grid->sy - 1;
  }
  else
    data->cy = (cy + sely) - yy;
  window_copy_update_selection(wp, 1);
  window_copy_redraw_screen(wp);
}


----------------------------
static u_int window_copy_find_length(struct window_pane *wp, u_int py)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = data->backing;
  struct grid_cell gc;
  u_int px;
  px = s->grid->linedata[py].cellsize;
  if (px > s->grid->sx)
  {
    px = s->grid->sx;
  }
  while (px > 0)
  {
    grid_get_cell(s->grid, px - 1, py, &gc);
    if ((gc.data.size != 1) || ((*gc.data.data) != ' '))
    {
      break;
    }
    px -= 1;
  }

  return px;
}


----------------------------
None
----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
static void window_copy_redraw_screen(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  window_copy_redraw_lines(wp, 0, (&data->screen)->grid->sy);
}


----------------------------
None
----------------------------
None
----------------------------
***/


static int window_copy_pagedown(struct window_pane *wp, int half_page, int scroll_exit)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  u_int n;
  u_int ox;
  u_int oy;
  u_int px;
  u_int py;
  oy = (data->backing->grid->hsize + data->cy) - data->oy;
  ox = window_copy_find_length(wp, oy);
  if ((s->sel.lineflag == LINE_SEL_RIGHT_LEFT) && (oy == data->sely))
  {
    window_copy_other_end(wp);
  }
  if (data->cx != ox)
  {
    data->lastcx = data->cx;
    data->lastsx = ox;
  }
  data->cx = data->lastcx;
  n = 1;
  if (s->grid->sy > 2)
  {
    if (half_page)
    {
      n = s->grid->sy / 2;
    }
    else
      n = s->grid->sy - 2;
  }
  if (data->oy < n)
  {
    data->oy = 0;
  }
  else
    data->oy -= n;
  if ((!data->screen.sel.flag) || (!data->rectflag))
  {
    py = (data->backing->grid->hsize + data->cy) - data->oy;
    px = window_copy_find_length(wp, py);
    if (((data->cx >= data->lastsx) && (data->cx != px)) || (data->cx > px))
    {
      window_copy_cursor_end_of_line(wp);
    }
  }
  if (scroll_exit && (data->oy == 0))
  {
    return 1;
  }
  window_copy_update_selection(wp, 1);
  window_copy_redraw_screen(wp);
  return 0;
}


/*** DEPENDENCIES:
static int window_copy_update_selection(struct window_pane *wp, int may_redraw)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct options *oo = wp->window->options;
  struct grid_cell gc;
  u_int sx;
  u_int sy;
  u_int cy;
  u_int endsx;
  u_int endsy;
  int startrelpos;
  int endrelpos;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return 0;
  }
  window_copy_synchronize_cursor(wp);
  sx = data->selx;
  sy = data->sely;
  startrelpos = window_copy_adjust_selection(wp, &sx, &sy);
  endsx = data->endselx;
  endsy = data->endsely;
  endrelpos = window_copy_adjust_selection(wp, &endsx, &endsy);
  if ((startrelpos == endrelpos) && (startrelpos != WINDOW_COPY_REL_POS_ON_SCREEN))
  {
    screen_hide_selection(s);
    return 0;
  }
  style_apply(&gc, oo, "mode-style");
  gc.flags |= 0x20;
  screen_set_selection(s, sx, sy, endsx, endsy, data->rectflag, &gc);
  if (data->rectflag && may_redraw)
  {
    cy = data->cy;
    if (data->cursordrag == CURSORDRAG_ENDSEL)
    {
      if (sy < cy)
      {
        window_copy_redraw_lines(wp, sy, (cy - sy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (sy - cy) + 1);
    }
    else
    {
      if (endsy < cy)
      {
        window_copy_redraw_lines(wp, endsy, (cy - endsy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (endsy - cy) + 1);
    }
  }
  return 1;
}


----------------------------
static void window_copy_other_end(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  u_int selx;
  u_int sely;
  u_int cy;
  u_int yy;
  u_int hsize;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return;
  }
  if (s->sel.lineflag == LINE_SEL_LEFT_RIGHT)
  {
    s->sel.lineflag = LINE_SEL_RIGHT_LEFT;
  }
  else
    if (s->sel.lineflag == LINE_SEL_RIGHT_LEFT)
  {
    s->sel.lineflag = LINE_SEL_LEFT_RIGHT;
  }
  switch (data->cursordrag)
  {
    case CURSORDRAG_NONE:

    case CURSORDRAG_SEL:
    {
      data->cursordrag = CURSORDRAG_ENDSEL;
      break;
    }

    case CURSORDRAG_ENDSEL:
    {
      data->cursordrag = CURSORDRAG_SEL;
      break;
    }

  }

  selx = data->endselx;
  sely = data->endsely;
  if (data->cursordrag == CURSORDRAG_SEL)
  {
    selx = data->selx;
    sely = data->sely;
  }
  cy = data->cy;
  yy = (data->backing->grid->hsize + data->cy) - data->oy;
  data->cx = selx;
  hsize = data->backing->grid->hsize;
  if (sely < (hsize - data->oy))
  {
    data->oy = hsize - sely;
    data->cy = 0;
  }
  else
    if (sely > ((hsize - data->oy) + s->grid->sy))
  {
    data->oy = ((hsize - sely) + s->grid->sy) - 1;
    data->cy = s->grid->sy - 1;
  }
  else
    data->cy = (cy + sely) - yy;
  window_copy_update_selection(wp, 1);
  window_copy_redraw_screen(wp);
}


----------------------------
static u_int window_copy_find_length(struct window_pane *wp, u_int py)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = data->backing;
  struct grid_cell gc;
  u_int px;
  px = s->grid->linedata[py].cellsize;
  if (px > s->grid->sx)
  {
    px = s->grid->sx;
  }
  while (px > 0)
  {
    grid_get_cell(s->grid, px - 1, py, &gc);
    if ((gc.data.size != 1) || ((*gc.data.data) != ' '))
    {
      break;
    }
    px -= 1;
  }

  return px;
}


----------------------------
None
----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
static void window_copy_redraw_screen(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  window_copy_redraw_lines(wp, 0, (&data->screen)->grid->sy);
}


----------------------------
None
----------------------------
None
----------------------------
***/


static void window_copy_cursor_previous_word(struct window_pane *wp, const char *separators)
{
  struct window_copy_mode_data *data = wp->modedata;
  u_int px;
  u_int py;
  px = data->cx;
  py = (data->backing->grid->hsize + data->cy) - data->oy;
  for (;;)
  {
    if (px > 0)
    {
      px -= 1;
      if (!window_copy_in_set(wp, px, py, separators))
      {
        break;
      }
    }
    else
    {
      if ((data->cy == 0) && ((data->backing->grid->hsize == 0) || (data->oy >= (data->backing->grid->hsize - 1))))
      {
        goto out;
      }
      window_copy_cursor_up(wp, 0);
      py = (data->backing->grid->hsize + data->cy) - data->oy;
      px = window_copy_find_length(wp, py);
    }
  }

  while ((px > 0) && (!window_copy_in_set(wp, px - 1, py, separators)))
  {
    px -= 1;
  }

  out:
  window_copy_update_cursor(wp, px, data->cy);

  if (window_copy_update_selection(wp, 1))
  {
    window_copy_redraw_lines(wp, data->cy, 1);
  }
}


/*** DEPENDENCIES:
static int window_copy_update_selection(struct window_pane *wp, int may_redraw)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct options *oo = wp->window->options;
  struct grid_cell gc;
  u_int sx;
  u_int sy;
  u_int cy;
  u_int endsx;
  u_int endsy;
  int startrelpos;
  int endrelpos;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return 0;
  }
  window_copy_synchronize_cursor(wp);
  sx = data->selx;
  sy = data->sely;
  startrelpos = window_copy_adjust_selection(wp, &sx, &sy);
  endsx = data->endselx;
  endsy = data->endsely;
  endrelpos = window_copy_adjust_selection(wp, &endsx, &endsy);
  if ((startrelpos == endrelpos) && (startrelpos != WINDOW_COPY_REL_POS_ON_SCREEN))
  {
    screen_hide_selection(s);
    return 0;
  }
  style_apply(&gc, oo, "mode-style");
  gc.flags |= 0x20;
  screen_set_selection(s, sx, sy, endsx, endsy, data->rectflag, &gc);
  if (data->rectflag && may_redraw)
  {
    cy = data->cy;
    if (data->cursordrag == CURSORDRAG_ENDSEL)
    {
      if (sy < cy)
      {
        window_copy_redraw_lines(wp, sy, (cy - sy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (sy - cy) + 1);
    }
    else
    {
      if (endsy < cy)
      {
        window_copy_redraw_lines(wp, endsy, (cy - endsy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (endsy - cy) + 1);
    }
  }
  return 1;
}


----------------------------
static u_int window_copy_find_length(struct window_pane *wp, u_int py)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = data->backing;
  struct grid_cell gc;
  u_int px;
  px = s->grid->linedata[py].cellsize;
  if (px > s->grid->sx)
  {
    px = s->grid->sx;
  }
  while (px > 0)
  {
    grid_get_cell(s->grid, px - 1, py, &gc);
    if ((gc.data.size != 1) || ((*gc.data.data) != ' '))
    {
      break;
    }
    px -= 1;
  }

  return px;
}


----------------------------
static int window_copy_in_set(struct window_pane *wp, u_int px, u_int py, const char *set)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct grid_cell gc;
  const struct utf8_data *ud;
  unsigned int ud_idx = 0;
  grid_get_cell(data->backing->grid, px, py, &gc);
  ud_idx = &gc.data;
  if ((ud->size != 1) || (gc.flags & 0x4))
  {
    return 0;
  }
  if (((*ud->data) == 0x00) || ((*ud->data) == 0x7f))
  {
    return 0;
  }
  return strchr(set, *ud->data) != 0;
}


----------------------------
static void window_copy_redraw_lines(struct window_pane *wp, u_int py, u_int ny)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen_write_ctx ctx;
  u_int i;
  screen_write_start(&ctx, wp, 0);
  for (i = py; i < (py + ny); i += 1)
  {
    window_copy_write_line(wp, &ctx, i);
  }

  screen_write_cursormove(&ctx, data->cx, data->cy);
  screen_write_stop(&ctx);
}


----------------------------
None
----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
static void window_copy_update_cursor(struct window_pane *wp, u_int cx, u_int cy)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct screen_write_ctx ctx;
  u_int old_cx;
  u_int old_cy;
  old_cx = data->cx;
  old_cy = data->cy;
  data->cx = cx;
  data->cy = cy;
  if (old_cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, old_cy, 1);
  }
  if (data->cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, data->cy, 1);
  }
  else
  {
    screen_write_start(&ctx, wp, 0);
    screen_write_cursormove(&ctx, data->cx, data->cy);
    screen_write_stop(&ctx);
  }
}


----------------------------
None
----------------------------
***/


static void window_copy_cursor_back_to_indentation(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  u_int px;
  u_int py;
  u_int xx;
  struct grid_cell gc;
  px = 0;
  py = (data->backing->grid->hsize + data->cy) - data->oy;
  xx = window_copy_find_length(wp, py);
  while (px < xx)
  {
    grid_get_cell(data->backing->grid, px, py, &gc);
    if ((gc.data.size != 1) || ((*gc.data.data) != ' '))
    {
      break;
    }
    px += 1;
  }

  window_copy_update_cursor(wp, px, data->cy);
  if (window_copy_update_selection(wp, 1))
  {
    window_copy_redraw_lines(wp, data->cy, 1);
  }
}


/*** DEPENDENCIES:
static int window_copy_update_selection(struct window_pane *wp, int may_redraw)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct options *oo = wp->window->options;
  struct grid_cell gc;
  u_int sx;
  u_int sy;
  u_int cy;
  u_int endsx;
  u_int endsy;
  int startrelpos;
  int endrelpos;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return 0;
  }
  window_copy_synchronize_cursor(wp);
  sx = data->selx;
  sy = data->sely;
  startrelpos = window_copy_adjust_selection(wp, &sx, &sy);
  endsx = data->endselx;
  endsy = data->endsely;
  endrelpos = window_copy_adjust_selection(wp, &endsx, &endsy);
  if ((startrelpos == endrelpos) && (startrelpos != WINDOW_COPY_REL_POS_ON_SCREEN))
  {
    screen_hide_selection(s);
    return 0;
  }
  style_apply(&gc, oo, "mode-style");
  gc.flags |= 0x20;
  screen_set_selection(s, sx, sy, endsx, endsy, data->rectflag, &gc);
  if (data->rectflag && may_redraw)
  {
    cy = data->cy;
    if (data->cursordrag == CURSORDRAG_ENDSEL)
    {
      if (sy < cy)
      {
        window_copy_redraw_lines(wp, sy, (cy - sy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (sy - cy) + 1);
    }
    else
    {
      if (endsy < cy)
      {
        window_copy_redraw_lines(wp, endsy, (cy - endsy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (endsy - cy) + 1);
    }
  }
  return 1;
}


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
static u_int window_copy_find_length(struct window_pane *wp, u_int py)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = data->backing;
  struct grid_cell gc;
  u_int px;
  px = s->grid->linedata[py].cellsize;
  if (px > s->grid->sx)
  {
    px = s->grid->sx;
  }
  while (px > 0)
  {
    grid_get_cell(s->grid, px - 1, py, &gc);
    if ((gc.data.size != 1) || ((*gc.data.data) != ' '))
    {
      break;
    }
    px -= 1;
  }

  return px;
}


----------------------------
static void window_copy_redraw_lines(struct window_pane *wp, u_int py, u_int ny)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen_write_ctx ctx;
  u_int i;
  screen_write_start(&ctx, wp, 0);
  for (i = py; i < (py + ny); i += 1)
  {
    window_copy_write_line(wp, &ctx, i);
  }

  screen_write_cursormove(&ctx, data->cx, data->cy);
  screen_write_stop(&ctx);
}


----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
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
static void window_copy_update_cursor(struct window_pane *wp, u_int cx, u_int cy)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct screen_write_ctx ctx;
  u_int old_cx;
  u_int old_cy;
  old_cx = data->cx;
  old_cy = data->cy;
  data->cx = cx;
  data->cy = cy;
  if (old_cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, old_cy, 1);
  }
  if (data->cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, data->cy, 1);
  }
  else
  {
    screen_write_start(&ctx, wp, 0);
    screen_write_cursormove(&ctx, data->cx, data->cy);
    screen_write_stop(&ctx);
  }
}


----------------------------
None
----------------------------
***/


static void window_copy_cursor_next_word(struct window_pane *wp, const char *separators)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *back_s = data->backing;
  u_int px;
  u_int py;
  u_int xx;
  u_int yy;
  int expected = 0;
  px = data->cx;
  py = (back_s->grid->hsize + data->cy) - data->oy;
  xx = window_copy_find_length(wp, py);
  yy = (back_s->grid->hsize + back_s->grid->sy) - 1;
  do
  {
    while ((px > xx) || (window_copy_in_set(wp, px, py, separators) == expected))
    {
      if (px > xx)
      {
        if (py == yy)
        {
          return;
        }
        window_copy_cursor_down(wp, 0);
        px = 0;
        py = (back_s->grid->hsize + data->cy) - data->oy;
        xx = window_copy_find_length(wp, py);
      }
      else
        px++;
      px += 1;
    }

    expected = !expected;
  }
  while (expected == 1);
  window_copy_update_cursor(wp, px, data->cy);
  if (window_copy_update_selection(wp, 1))
  {
    window_copy_redraw_lines(wp, data->cy, 1);
  }
}


/*** DEPENDENCIES:
static int window_copy_update_selection(struct window_pane *wp, int may_redraw)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct options *oo = wp->window->options;
  struct grid_cell gc;
  u_int sx;
  u_int sy;
  u_int cy;
  u_int endsx;
  u_int endsy;
  int startrelpos;
  int endrelpos;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return 0;
  }
  window_copy_synchronize_cursor(wp);
  sx = data->selx;
  sy = data->sely;
  startrelpos = window_copy_adjust_selection(wp, &sx, &sy);
  endsx = data->endselx;
  endsy = data->endsely;
  endrelpos = window_copy_adjust_selection(wp, &endsx, &endsy);
  if ((startrelpos == endrelpos) && (startrelpos != WINDOW_COPY_REL_POS_ON_SCREEN))
  {
    screen_hide_selection(s);
    return 0;
  }
  style_apply(&gc, oo, "mode-style");
  gc.flags |= 0x20;
  screen_set_selection(s, sx, sy, endsx, endsy, data->rectflag, &gc);
  if (data->rectflag && may_redraw)
  {
    cy = data->cy;
    if (data->cursordrag == CURSORDRAG_ENDSEL)
    {
      if (sy < cy)
      {
        window_copy_redraw_lines(wp, sy, (cy - sy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (sy - cy) + 1);
    }
    else
    {
      if (endsy < cy)
      {
        window_copy_redraw_lines(wp, endsy, (cy - endsy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (endsy - cy) + 1);
    }
  }
  return 1;
}


----------------------------
static u_int window_copy_find_length(struct window_pane *wp, u_int py)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = data->backing;
  struct grid_cell gc;
  u_int px;
  px = s->grid->linedata[py].cellsize;
  if (px > s->grid->sx)
  {
    px = s->grid->sx;
  }
  while (px > 0)
  {
    grid_get_cell(s->grid, px - 1, py, &gc);
    if ((gc.data.size != 1) || ((*gc.data.data) != ' '))
    {
      break;
    }
    px -= 1;
  }

  return px;
}


----------------------------
static int window_copy_in_set(struct window_pane *wp, u_int px, u_int py, const char *set)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct grid_cell gc;
  const struct utf8_data *ud;
  unsigned int ud_idx = 0;
  grid_get_cell(data->backing->grid, px, py, &gc);
  ud_idx = &gc.data;
  if ((ud->size != 1) || (gc.flags & 0x4))
  {
    return 0;
  }
  if (((*ud->data) == 0x00) || ((*ud->data) == 0x7f))
  {
    return 0;
  }
  return strchr(set, *ud->data) != 0;
}


----------------------------
static void window_copy_redraw_lines(struct window_pane *wp, u_int py, u_int ny)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen_write_ctx ctx;
  u_int i;
  screen_write_start(&ctx, wp, 0);
  for (i = py; i < (py + ny); i += 1)
  {
    window_copy_write_line(wp, &ctx, i);
  }

  screen_write_cursormove(&ctx, data->cx, data->cy);
  screen_write_stop(&ctx);
}


----------------------------
None
----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
None
----------------------------
static void window_copy_update_cursor(struct window_pane *wp, u_int cx, u_int cy)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct screen_write_ctx ctx;
  u_int old_cx;
  u_int old_cy;
  old_cx = data->cx;
  old_cy = data->cy;
  data->cx = cx;
  data->cy = cy;
  if (old_cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, old_cy, 1);
  }
  if (data->cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, data->cy, 1);
  }
  else
  {
    screen_write_start(&ctx, wp, 0);
    screen_write_cursormove(&ctx, data->cx, data->cy);
    screen_write_stop(&ctx);
  }
}


----------------------------
None
----------------------------
***/


void window_copy_init_from_pane(struct window_pane *wp, int scroll_exit)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct screen_write_ctx ctx;
  u_int i;
  if (wp->mode != (&window_copy_mode))
  {
    fatalx("not in copy mode");
  }
  data->backing = &wp->base;
  data->cx = data->backing->cx;
  data->cy = data->backing->cy;
  data->scroll_exit = scroll_exit;
  s->cx = data->cx;
  s->cy = data->cy;
  screen_write_start(&ctx, 0, s);
  for (i = 0; i < s->grid->sy; i += 1)
  {
    window_copy_write_line(wp, &ctx, i);
  }

  screen_write_cursormove(&ctx, data->cx, data->cy);
  screen_write_stop(&ctx);
}


/*** DEPENDENCIES:
extern const struct window_mode window_copy_mode
----------------------------
static void window_copy_write_line(struct window_pane *wp, struct screen_write_ctx *ctx, u_int py)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct options *oo = wp->window->options;
  struct grid_cell gc;
  char hdr[512];
  size_t size = 0;
  style_apply(&gc, oo, "mode-style");
  gc.flags |= 0x20;
  if (py == 0)
  {
    if (data->searchmark == 0)
    {
      size = xsnprintf(hdr, sizeof(hdr), "[%u/%u]", data->oy, data->backing->grid->hsize);
    }
    else
    {
      if (data->searchthis == (-1))
      {
        size = xsnprintf(hdr, sizeof(hdr), "(%u results) [%d/%u]", data->searchcount, data->oy, data->backing->grid->hsize);
      }
      else
      {
        size = xsnprintf(hdr, sizeof(hdr), "(%u/%u results) [%d/%u]", data->searchthis, data->searchcount, data->oy, data->backing->grid->hsize);
      }
    }
    if (size > s->grid->sx)
    {
      size = s->grid->sx;
    }
    screen_write_cursormove(ctx, s->grid->sx - size, 0);
    screen_write_puts(ctx, &gc, "%s", hdr);
  }
  else
    size = 0;
  if (size < s->grid->sx)
  {
    screen_write_cursormove(ctx, 0, py);
    screen_write_copy(ctx, data->backing, 0, (data->backing->grid->hsize - data->oy) + py, s->grid->sx - size, 1, data->searchmark, &gc);
  }
  if ((py == data->cy) && (data->cx == s->grid->sx))
  {
    memcpy(&gc, &grid_default_cell, sizeof(gc));
    screen_write_cursormove(ctx, s->grid->sx - 1, py);
    screen_write_putc(ctx, &gc, '$');
  }
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
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
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
None
----------------------------
None
----------------------------
***/


static void window_copy_drag_update(struct client *c, struct mouse_event *m)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  struct window_copy_mode_data *data;
  unsigned int data_idx = 0;
  u_int x;
  u_int y;
  u_int old_cy;
  wp_idx = cmd_mouse_pane(m, 0, 0);
  if (((&wp[wp_idx]) == 0) || (wp->mode != (&window_copy_mode)))
  {
    return;
  }
  data_idx = wp->modedata;
  if (cmd_mouse_at(wp, m, &x, &y, 0) != 0)
  {
    return;
  }
  old_cy = data->cy;
  window_copy_update_cursor(wp, x, y);
  if (window_copy_update_selection(wp, 1))
  {
    window_copy_redraw_selection(wp, old_cy);
  }
}


/*** DEPENDENCIES:
extern const struct window_mode window_copy_mode
----------------------------
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
static int window_copy_update_selection(struct window_pane *wp, int may_redraw)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct options *oo = wp->window->options;
  struct grid_cell gc;
  u_int sx;
  u_int sy;
  u_int cy;
  u_int endsx;
  u_int endsy;
  int startrelpos;
  int endrelpos;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return 0;
  }
  window_copy_synchronize_cursor(wp);
  sx = data->selx;
  sy = data->sely;
  startrelpos = window_copy_adjust_selection(wp, &sx, &sy);
  endsx = data->endselx;
  endsy = data->endsely;
  endrelpos = window_copy_adjust_selection(wp, &endsx, &endsy);
  if ((startrelpos == endrelpos) && (startrelpos != WINDOW_COPY_REL_POS_ON_SCREEN))
  {
    screen_hide_selection(s);
    return 0;
  }
  style_apply(&gc, oo, "mode-style");
  gc.flags |= 0x20;
  screen_set_selection(s, sx, sy, endsx, endsy, data->rectflag, &gc);
  if (data->rectflag && may_redraw)
  {
    cy = data->cy;
    if (data->cursordrag == CURSORDRAG_ENDSEL)
    {
      if (sy < cy)
      {
        window_copy_redraw_lines(wp, sy, (cy - sy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (sy - cy) + 1);
    }
    else
    {
      if (endsy < cy)
      {
        window_copy_redraw_lines(wp, endsy, (cy - endsy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (endsy - cy) + 1);
    }
  }
  return 1;
}


----------------------------
struct window_pane *cmd_mouse_pane(struct mouse_event *m, struct session **sp, struct winlink **wlp)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  if ((wl_idx = cmd_mouse_window(m, sp)) == 0)
  {
    return 0;
  }
  if ((wp_idx = window_pane_find_by_id(m->wp_idx)) == 0)
  {
    return 0;
  }
  if (!window_has_pane(wl->window, wp))
  {
    return 0;
  }
  if (wlp != 0)
  {
    *wlp = &wl[wl_idx];
  }
  return wp;
}


----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
int cmd_mouse_at(struct window_pane *wp, struct mouse_event *m, u_int *xp, u_int *yp, int last)
{
  u_int x;
  u_int y;
  if (last)
  {
    x = m->lx;
    y = m->ly;
  }
  else
  {
    x = m->x;
    y = m->y;
  }
  if ((m->statusat == 0) && (y > 0))
  {
    y -= 1;
  }
  else
    if ((m->statusat > 0) && (y >= ((u_int) m->statusat)))
  {
    y = m->statusat - 1;
  }
  if ((x < wp->xoff) || (x >= (wp->xoff + wp->sx)))
  {
    return -1;
  }
  if ((y < wp->yoff) || (y >= (wp->yoff + wp->sy)))
  {
    return -1;
  }
  if (xp != 0)
  {
    *xp = x - wp->xoff;
  }
  if (yp != 0)
  {
    *yp = y - wp->yoff;
  }
  return 0;
}


----------------------------
static void window_copy_redraw_selection(struct window_pane *wp, u_int old_y)
{
  struct window_copy_mode_data *data = wp->modedata;
  u_int new_y;
  u_int start;
  u_int end;
  new_y = data->cy;
  if (old_y <= new_y)
  {
    start = old_y;
    end = new_y;
  }
  else
  {
    start = new_y;
    end = old_y;
  }
  window_copy_redraw_lines(wp, start, (end - start) + 1);
}


----------------------------
static void window_copy_update_cursor(struct window_pane *wp, u_int cx, u_int cy)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct screen_write_ctx ctx;
  u_int old_cx;
  u_int old_cy;
  old_cx = data->cx;
  old_cy = data->cy;
  data->cx = cx;
  data->cy = cy;
  if (old_cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, old_cy, 1);
  }
  if (data->cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, data->cy, 1);
  }
  else
  {
    screen_write_start(&ctx, wp, 0);
    screen_write_cursormove(&ctx, data->cx, data->cy);
    screen_write_stop(&ctx);
  }
}


----------------------------
None
----------------------------
***/


void window_copy_start_drag(struct client *c, struct mouse_event *m)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int x;
  u_int y;
  if (c == 0)
  {
    return;
  }
  wp_idx = cmd_mouse_pane(m, 0, 0);
  if (((&wp[wp_idx]) == 0) || (wp->mode != (&window_copy_mode)))
  {
    return;
  }
  if (cmd_mouse_at(wp, m, &x, &y, 1) != 0)
  {
    return;
  }
  c->tty.mouse_drag_update = window_copy_drag_update;
  c->tty.mouse_drag_release = 0;
  window_copy_update_cursor(wp, x, y);
  window_copy_start_selection(wp);
  window_copy_redraw_screen(wp);
}


/*** DEPENDENCIES:
extern const struct window_mode window_copy_mode
----------------------------
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
static void window_copy_drag_update(struct client *c, struct mouse_event *m)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  struct window_copy_mode_data *data;
  unsigned int data_idx = 0;
  u_int x;
  u_int y;
  u_int old_cy;
  wp_idx = cmd_mouse_pane(m, 0, 0);
  if (((&wp[wp_idx]) == 0) || (wp->mode != (&window_copy_mode)))
  {
    return;
  }
  data_idx = wp->modedata;
  if (cmd_mouse_at(wp, m, &x, &y, 0) != 0)
  {
    return;
  }
  old_cy = data->cy;
  window_copy_update_cursor(wp, x, y);
  if (window_copy_update_selection(wp, 1))
  {
    window_copy_redraw_selection(wp, old_cy);
  }
}


----------------------------
struct window_pane *cmd_mouse_pane(struct mouse_event *m, struct session **sp, struct winlink **wlp)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  if ((wl_idx = cmd_mouse_window(m, sp)) == 0)
  {
    return 0;
  }
  if ((wp_idx = window_pane_find_by_id(m->wp_idx)) == 0)
  {
    return 0;
  }
  if (!window_has_pane(wl->window, wp))
  {
    return 0;
  }
  if (wlp != 0)
  {
    *wlp = &wl[wl_idx];
  }
  return wp;
}


----------------------------
static void window_copy_start_selection(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  data->selx = data->cx;
  data->sely = (data->backing->grid->hsize + data->cy) - data->oy;
  data->endselx = data->selx;
  data->endsely = data->sely;
  data->cursordrag = CURSORDRAG_ENDSEL;
  s->sel.flag = 1;
  window_copy_update_selection(wp, 1);
}


----------------------------
static void window_copy_redraw_screen(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  window_copy_redraw_lines(wp, 0, (&data->screen)->grid->sy);
}


----------------------------
int cmd_mouse_at(struct window_pane *wp, struct mouse_event *m, u_int *xp, u_int *yp, int last)
{
  u_int x;
  u_int y;
  if (last)
  {
    x = m->lx;
    y = m->ly;
  }
  else
  {
    x = m->x;
    y = m->y;
  }
  if ((m->statusat == 0) && (y > 0))
  {
    y -= 1;
  }
  else
    if ((m->statusat > 0) && (y >= ((u_int) m->statusat)))
  {
    y = m->statusat - 1;
  }
  if ((x < wp->xoff) || (x >= (wp->xoff + wp->sx)))
  {
    return -1;
  }
  if ((y < wp->yoff) || (y >= (wp->yoff + wp->sy)))
  {
    return -1;
  }
  if (xp != 0)
  {
    *xp = x - wp->xoff;
  }
  if (yp != 0)
  {
    *yp = y - wp->yoff;
  }
  return 0;
}


----------------------------
static void window_copy_update_cursor(struct window_pane *wp, u_int cx, u_int cy)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct screen_write_ctx ctx;
  u_int old_cx;
  u_int old_cy;
  old_cx = data->cx;
  old_cy = data->cy;
  data->cx = cx;
  data->cy = cy;
  if (old_cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, old_cy, 1);
  }
  if (data->cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, data->cy, 1);
  }
  else
  {
    screen_write_start(&ctx, wp, 0);
    screen_write_cursormove(&ctx, data->cx, data->cy);
    screen_write_stop(&ctx);
  }
}


----------------------------
None
----------------------------
***/


static struct screen *window_copy_init(struct window_pane *wp, struct cmd_find_state *fs, struct args *args)
{
  struct window_copy_mode_data *data;
  struct screen *s;
  unsigned int s_idx = 0;
  wp->modedata = (data = xmalloc(sizeof(*data)));
  data->oy = 0;
  data->cx = 0;
  data->cy = 0;
  data->cursordrag = CURSORDRAG_NONE;
  data->lastcx = 0;
  data->lastsx = 0;
  data->backing_written = 0;
  data->rectflag = 0;
  data->scroll_exit = 0;
  if (wp->searchstr != 0)
  {
    data->searchtype = WINDOW_COPY_SEARCHUP;
    data->searchstr = xstrdup(wp->searchstr);
  }
  else
  {
    data->searchtype = WINDOW_COPY_OFF;
    data->searchstr = 0;
  }
  data->searchmark = 0;
  data->searchx = (data->searchy = (data->searcho = -1));
  if (wp->fd != (-1))
  {
    bufferevent_disable(wp->event, EV_READ | EV_WRITE);
  }
  data->jumptype = WINDOW_COPY_OFF;
  data->jumpchar = '\0';
  s_idx = &data->screen;
  screen_init(s, (&wp->base)->grid->sx, (&wp->base)->grid->sy, 0);
  s->sel.modekeys = options_get_number(wp->window->options, "mode-keys");
  data->backing = 0;
  return s;
}


/*** DEPENDENCIES:
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
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
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
None
----------------------------
***/


static void window_copy_cursor_left(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  u_int py;
  u_int cx;
  struct grid_cell gc;
  py = (data->backing->grid->hsize + data->cy) - data->oy;
  cx = data->cx;
  while (cx > 0)
  {
    grid_get_cell(data->backing->grid, cx, py, &gc);
    if ((~gc.flags) & 0x4)
    {
      break;
    }
    cx -= 1;
  }

  if ((cx == 0) && (py > 0))
  {
    window_copy_cursor_up(wp, 0);
    window_copy_cursor_end_of_line(wp);
  }
  else
    if (cx > 0)
  {
    window_copy_update_cursor(wp, cx - 1, data->cy);
    if (window_copy_update_selection(wp, 1))
    {
      window_copy_redraw_lines(wp, data->cy, 1);
    }
  }
}


/*** DEPENDENCIES:
static int window_copy_update_selection(struct window_pane *wp, int may_redraw)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct options *oo = wp->window->options;
  struct grid_cell gc;
  u_int sx;
  u_int sy;
  u_int cy;
  u_int endsx;
  u_int endsy;
  int startrelpos;
  int endrelpos;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return 0;
  }
  window_copy_synchronize_cursor(wp);
  sx = data->selx;
  sy = data->sely;
  startrelpos = window_copy_adjust_selection(wp, &sx, &sy);
  endsx = data->endselx;
  endsy = data->endsely;
  endrelpos = window_copy_adjust_selection(wp, &endsx, &endsy);
  if ((startrelpos == endrelpos) && (startrelpos != WINDOW_COPY_REL_POS_ON_SCREEN))
  {
    screen_hide_selection(s);
    return 0;
  }
  style_apply(&gc, oo, "mode-style");
  gc.flags |= 0x20;
  screen_set_selection(s, sx, sy, endsx, endsy, data->rectflag, &gc);
  if (data->rectflag && may_redraw)
  {
    cy = data->cy;
    if (data->cursordrag == CURSORDRAG_ENDSEL)
    {
      if (sy < cy)
      {
        window_copy_redraw_lines(wp, sy, (cy - sy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (sy - cy) + 1);
    }
    else
    {
      if (endsy < cy)
      {
        window_copy_redraw_lines(wp, endsy, (cy - endsy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (endsy - cy) + 1);
    }
  }
  return 1;
}


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
static void window_copy_redraw_lines(struct window_pane *wp, u_int py, u_int ny)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen_write_ctx ctx;
  u_int i;
  screen_write_start(&ctx, wp, 0);
  for (i = py; i < (py + ny); i += 1)
  {
    window_copy_write_line(wp, &ctx, i);
  }

  screen_write_cursormove(&ctx, data->cx, data->cy);
  screen_write_stop(&ctx);
}


----------------------------
None
----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
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
static void window_copy_update_cursor(struct window_pane *wp, u_int cx, u_int cy)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct screen_write_ctx ctx;
  u_int old_cx;
  u_int old_cy;
  old_cx = data->cx;
  old_cy = data->cy;
  data->cx = cx;
  data->cy = cy;
  if (old_cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, old_cy, 1);
  }
  if (data->cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, data->cy, 1);
  }
  else
  {
    screen_write_start(&ctx, wp, 0);
    screen_write_cursormove(&ctx, data->cx, data->cy);
    screen_write_stop(&ctx);
  }
}


----------------------------
None
----------------------------
***/


static void window_copy_resize(struct window_pane *wp, u_int sx, u_int sy)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct screen_write_ctx ctx;
  screen_resize(s, sx, sy, 1);
  if (data->backing != (&wp->base))
  {
    screen_resize(data->backing, sx, sy, 1);
  }
  if (data->cy > (sy - 1))
  {
    data->cy = sy - 1;
  }
  if (data->cx > sx)
  {
    data->cx = sx;
  }
  if (data->oy > data->backing->grid->hsize)
  {
    data->oy = data->backing->grid->hsize;
  }
  window_copy_clear_selection(wp);
  screen_write_start(&ctx, 0, s);
  window_copy_write_lines(wp, &ctx, 0, s->grid->sy - 1);
  screen_write_stop(&ctx);
  if (data->searchmark != 0)
  {
    window_copy_search_marks(wp, 0);
  }
  data->searchx = data->cx;
  data->searchy = data->cy;
  data->searcho = data->oy;
  window_copy_redraw_screen(wp);
}


/*** DEPENDENCIES:
static void window_copy_write_lines(struct window_pane *wp, struct screen_write_ctx *ctx, u_int py, u_int ny)
{
  u_int yy;
  for (yy = py; yy < (py + ny); yy += 1)
  {
    window_copy_write_line(wp, ctx, py);
  }

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
static int window_copy_search_marks(struct window_pane *wp, struct screen *ssp)
{
  unsigned int ssp_idx = 0;
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = data->backing;
  struct screen ss;
  struct screen_write_ctx ctx;
  struct grid *gd = s->grid;
  int found;
  int cis;
  int which = -1;
  u_int px;
  u_int py;
  u_int b;
  u_int nfound = 0;
  u_int width;
  if ((&ssp[ssp_idx]) == 0)
  {
    width = screen_write_strlen("%s", data->searchstr);
    screen_init(&ss, width, 1, 0);
    screen_write_start(&ctx, 0, &ss);
    screen_write_nputs(&ctx, -1, &grid_default_cell, "%s", data->searchstr);
    screen_write_stop(&ctx);
    ssp_idx = &ss;
  }
  else
    width = ssp->grid->sx;
  cis = window_copy_is_lowercase(data->searchstr);
  free(data->searchmark);
  data->searchmark = (bitstr_t *) calloc((size_t) ((((gd->hsize + gd->sy) * gd->sx) + 7) >> 3), sizeof(bitstr_t));
  for (py = 0; py < (gd->hsize + gd->sy); py += 1)
  {
    helper_window_copy_search_marks_1(&found, &which, &px, &b, &nfound, ssp, data, gd, cis, py, width);
  }

  if (which != (-1))
  {
    data->searchthis = (1 + nfound) - which;
  }
  else
    data->searchthis = -1;
  data->searchcount = nfound;
  if ((&ssp[ssp_idx]) == (&ss))
  {
    screen_free(&ss);
  }
  return nfound;
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
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
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
static void window_copy_redraw_screen(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  window_copy_redraw_lines(wp, 0, (&data->screen)->grid->sy);
}


----------------------------
static void window_copy_clear_selection(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  u_int px;
  u_int py;
  screen_clear_selection(&data->screen);
  data->cursordrag = CURSORDRAG_NONE;
  py = (data->backing->grid->hsize + data->cy) - data->oy;
  px = window_copy_find_length(wp, py);
  if (data->cx > px)
  {
    window_copy_update_cursor(wp, px, data->cy);
  }
}


----------------------------
None
----------------------------
None
----------------------------
***/


static void window_copy_cursor_right(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  u_int px;
  u_int py;
  u_int yy;
  u_int cx;
  u_int cy;
  struct grid_cell gc;
  py = (data->backing->grid->hsize + data->cy) - data->oy;
  yy = (data->backing->grid->hsize + data->backing->grid->sy) - 1;
  if (data->screen.sel.flag && data->rectflag)
  {
    px = (&data->screen)->grid->sx;
  }
  else
    px = window_copy_find_length(wp, py);
  if ((data->cx >= px) && (py < yy))
  {
    window_copy_cursor_start_of_line(wp);
    window_copy_cursor_down(wp, 0);
  }
  else
    if (data->cx < px)
  {
    cx = data->cx + 1;
    cy = (data->backing->grid->hsize + data->cy) - data->oy;
    while (cx < px)
    {
      grid_get_cell(data->backing->grid, cx, cy, &gc);
      if ((~gc.flags) & 0x4)
      {
        break;
      }
      cx += 1;
    }

    window_copy_update_cursor(wp, cx, data->cy);
    if (window_copy_update_selection(wp, 1))
    {
      window_copy_redraw_lines(wp, data->cy, 1);
    }
  }
}


/*** DEPENDENCIES:
static int window_copy_update_selection(struct window_pane *wp, int may_redraw)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct options *oo = wp->window->options;
  struct grid_cell gc;
  u_int sx;
  u_int sy;
  u_int cy;
  u_int endsx;
  u_int endsy;
  int startrelpos;
  int endrelpos;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return 0;
  }
  window_copy_synchronize_cursor(wp);
  sx = data->selx;
  sy = data->sely;
  startrelpos = window_copy_adjust_selection(wp, &sx, &sy);
  endsx = data->endselx;
  endsy = data->endsely;
  endrelpos = window_copy_adjust_selection(wp, &endsx, &endsy);
  if ((startrelpos == endrelpos) && (startrelpos != WINDOW_COPY_REL_POS_ON_SCREEN))
  {
    screen_hide_selection(s);
    return 0;
  }
  style_apply(&gc, oo, "mode-style");
  gc.flags |= 0x20;
  screen_set_selection(s, sx, sy, endsx, endsy, data->rectflag, &gc);
  if (data->rectflag && may_redraw)
  {
    cy = data->cy;
    if (data->cursordrag == CURSORDRAG_ENDSEL)
    {
      if (sy < cy)
      {
        window_copy_redraw_lines(wp, sy, (cy - sy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (sy - cy) + 1);
    }
    else
    {
      if (endsy < cy)
      {
        window_copy_redraw_lines(wp, endsy, (cy - endsy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (endsy - cy) + 1);
    }
  }
  return 1;
}


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
static u_int window_copy_find_length(struct window_pane *wp, u_int py)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = data->backing;
  struct grid_cell gc;
  u_int px;
  px = s->grid->linedata[py].cellsize;
  if (px > s->grid->sx)
  {
    px = s->grid->sx;
  }
  while (px > 0)
  {
    grid_get_cell(s->grid, px - 1, py, &gc);
    if ((gc.data.size != 1) || ((*gc.data.data) != ' '))
    {
      break;
    }
    px -= 1;
  }

  return px;
}


----------------------------
static void window_copy_redraw_lines(struct window_pane *wp, u_int py, u_int ny)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen_write_ctx ctx;
  u_int i;
  screen_write_start(&ctx, wp, 0);
  for (i = py; i < (py + ny); i += 1)
  {
    window_copy_write_line(wp, &ctx, i);
  }

  screen_write_cursormove(&ctx, data->cx, data->cy);
  screen_write_stop(&ctx);
}


----------------------------
None
----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
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
static void window_copy_update_cursor(struct window_pane *wp, u_int cx, u_int cy)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct screen_write_ctx ctx;
  u_int old_cx;
  u_int old_cy;
  old_cx = data->cx;
  old_cy = data->cy;
  data->cx = cx;
  data->cy = cy;
  if (old_cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, old_cy, 1);
  }
  if (data->cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, data->cy, 1);
  }
  else
  {
    screen_write_start(&ctx, wp, 0);
    screen_write_cursormove(&ctx, data->cx, data->cy);
    screen_write_stop(&ctx);
  }
}


----------------------------
None
----------------------------
***/


static void window_copy_cursor_next_word_end(struct window_pane *wp, const char *separators)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct options *oo = wp->window->options;
  struct screen *back_s = data->backing;
  u_int px;
  u_int py;
  u_int xx;
  u_int yy;
  int keys;
  int expected = 1;
  px = data->cx;
  py = (back_s->grid->hsize + data->cy) - data->oy;
  xx = window_copy_find_length(wp, py);
  yy = (back_s->grid->hsize + back_s->grid->sy) - 1;
  keys = options_get_number(oo, "mode-keys");
  if ((keys == 1) && (!window_copy_in_set(wp, px, py, separators)))
  {
    px += 1;
  }
  do
  {
    while ((px > xx) || (window_copy_in_set(wp, px, py, separators) == expected))
    {
      if (px > xx)
      {
        if (py == yy)
        {
          return;
        }
        window_copy_cursor_down(wp, 0);
        px = 0;
        py = (back_s->grid->hsize + data->cy) - data->oy;
        xx = window_copy_find_length(wp, py);
      }
      else
        px++;
      px += 1;
    }

    expected = !expected;
  }
  while (expected == 0);
  if ((keys == 1) && (px != 0))
  {
    px -= 1;
  }
  window_copy_update_cursor(wp, px, data->cy);
  if (window_copy_update_selection(wp, 1))
  {
    window_copy_redraw_lines(wp, data->cy, 1);
  }
}


/*** DEPENDENCIES:
static int window_copy_update_selection(struct window_pane *wp, int may_redraw)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct options *oo = wp->window->options;
  struct grid_cell gc;
  u_int sx;
  u_int sy;
  u_int cy;
  u_int endsx;
  u_int endsy;
  int startrelpos;
  int endrelpos;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return 0;
  }
  window_copy_synchronize_cursor(wp);
  sx = data->selx;
  sy = data->sely;
  startrelpos = window_copy_adjust_selection(wp, &sx, &sy);
  endsx = data->endselx;
  endsy = data->endsely;
  endrelpos = window_copy_adjust_selection(wp, &endsx, &endsy);
  if ((startrelpos == endrelpos) && (startrelpos != WINDOW_COPY_REL_POS_ON_SCREEN))
  {
    screen_hide_selection(s);
    return 0;
  }
  style_apply(&gc, oo, "mode-style");
  gc.flags |= 0x20;
  screen_set_selection(s, sx, sy, endsx, endsy, data->rectflag, &gc);
  if (data->rectflag && may_redraw)
  {
    cy = data->cy;
    if (data->cursordrag == CURSORDRAG_ENDSEL)
    {
      if (sy < cy)
      {
        window_copy_redraw_lines(wp, sy, (cy - sy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (sy - cy) + 1);
    }
    else
    {
      if (endsy < cy)
      {
        window_copy_redraw_lines(wp, endsy, (cy - endsy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (endsy - cy) + 1);
    }
  }
  return 1;
}


----------------------------
static u_int window_copy_find_length(struct window_pane *wp, u_int py)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = data->backing;
  struct grid_cell gc;
  u_int px;
  px = s->grid->linedata[py].cellsize;
  if (px > s->grid->sx)
  {
    px = s->grid->sx;
  }
  while (px > 0)
  {
    grid_get_cell(s->grid, px - 1, py, &gc);
    if ((gc.data.size != 1) || ((*gc.data.data) != ' '))
    {
      break;
    }
    px -= 1;
  }

  return px;
}


----------------------------
static int window_copy_in_set(struct window_pane *wp, u_int px, u_int py, const char *set)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct grid_cell gc;
  const struct utf8_data *ud;
  unsigned int ud_idx = 0;
  grid_get_cell(data->backing->grid, px, py, &gc);
  ud_idx = &gc.data;
  if ((ud->size != 1) || (gc.flags & 0x4))
  {
    return 0;
  }
  if (((*ud->data) == 0x00) || ((*ud->data) == 0x7f))
  {
    return 0;
  }
  return strchr(set, *ud->data) != 0;
}


----------------------------
static void window_copy_redraw_lines(struct window_pane *wp, u_int py, u_int ny)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen_write_ctx ctx;
  u_int i;
  screen_write_start(&ctx, wp, 0);
  for (i = py; i < (py + ny); i += 1)
  {
    window_copy_write_line(wp, &ctx, i);
  }

  screen_write_cursormove(&ctx, data->cx, data->cy);
  screen_write_stop(&ctx);
}


----------------------------
None
----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
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
static void window_copy_update_cursor(struct window_pane *wp, u_int cx, u_int cy)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct screen_write_ctx ctx;
  u_int old_cx;
  u_int old_cy;
  old_cx = data->cx;
  old_cy = data->cy;
  data->cx = cx;
  data->cy = cy;
  if (old_cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, old_cy, 1);
  }
  if (data->cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, data->cy, 1);
  }
  else
  {
    screen_write_start(&ctx, wp, 0);
    screen_write_cursormove(&ctx, data->cx, data->cy);
    screen_write_stop(&ctx);
  }
}


----------------------------
None
----------------------------
None
----------------------------
***/


// hint:  ['argument_idx_ref is a mutable refrence to unsigned int', 'np_ref is a mutable refrence to u_int', 'cancel_ref is a mutable refrence to int', 'redraw_ref is a mutable refrence to int', 'prefix_ref is a mutable refrence to char']
void helper_window_copy_command_1(unsigned int * const argument_idx_ref, u_int * const np_ref, int * const cancel_ref, int * const redraw_ref, char * const prefix_ref, struct window_pane * const wp, struct session * const s, struct args * const args, struct window_copy_mode_data * const data, const char * const command, const char * const argument)
{
  unsigned int argument_idx = *argument_idx_ref;
  u_int np = *np_ref;
  int cancel = *cancel_ref;
  int redraw = *redraw_ref;
  char prefix = *prefix_ref;
  argument_idx = args->argv[1];
  if (strcmp(command, "copy-pipe") == 0)
  {
    if (s != 0)
    {
      window_copy_copy_pipe(wp, s, 0, argument);
    }
  }
  if (strcmp(command, "copy-pipe-and-cancel") == 0)
  {
    if (s != 0)
    {
      window_copy_copy_pipe(wp, s, 0, argument);
      cancel = 1;
    }
  }
  if (strcmp(command, "goto-line") == 0)
  {
    window_copy_goto_line(wp, argument);
  }
  if (strcmp(command, "jump-backward") == 0)
  {
    data->jumptype = WINDOW_COPY_JUMPBACKWARD;
    data->jumpchar = argument[argument_idx];
    for (; np != 0; np -= 1)
    {
      window_copy_cursor_jump_back(wp);
    }

  }
  if (strcmp(command, "jump-forward") == 0)
  {
    data->jumptype = WINDOW_COPY_JUMPFORWARD;
    data->jumpchar = argument[argument_idx];
    for (; np != 0; np -= 1)
    {
      window_copy_cursor_jump(wp);
    }

  }
  if (strcmp(command, "jump-to-backward") == 0)
  {
    data->jumptype = WINDOW_COPY_JUMPTOBACKWARD;
    data->jumpchar = argument[argument_idx];
    for (; np != 0; np -= 1)
    {
      window_copy_cursor_jump_to_back(wp);
    }

  }
  if (strcmp(command, "jump-to-forward") == 0)
  {
    data->jumptype = WINDOW_COPY_JUMPTOFORWARD;
    data->jumpchar = argument[argument_idx];
    for (; np != 0; np -= 1)
    {
      window_copy_cursor_jump_to(wp);
    }

  }
  if (strcmp(command, "search-backward") == 0)
  {
    data->searchtype = WINDOW_COPY_SEARCHUP;
    free(data->searchstr);
    data->searchstr = xstrdup(argument);
    for (; np != 0; np -= 1)
    {
      window_copy_search_up(wp);
    }

  }
  if (strcmp(command, "search-forward") == 0)
  {
    data->searchtype = WINDOW_COPY_SEARCHDOWN;
    free(data->searchstr);
    data->searchstr = xstrdup(argument);
    for (; np != 0; np -= 1)
    {
      window_copy_search_down(wp);
    }

  }
  if (strcmp(command, "search-backward-incremental") == 0)
  {
    helper_helper_window_copy_command_1_1(&argument_idx, &redraw, &prefix, wp, data, argument);
  }
  if (strcmp(command, "search-forward-incremental") == 0)
  {
    helper_helper_window_copy_command_1_2(&argument_idx, &redraw, &prefix, wp, data, argument);
  }
  *argument_idx_ref = argument_idx;
  *np_ref = np;
  *cancel_ref = cancel;
  *redraw_ref = redraw;
  *prefix_ref = prefix;
}


/*** DEPENDENCIES:
static void window_copy_cursor_jump_to(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *back_s = data->backing;
  struct grid_cell gc;
  u_int px;
  u_int py;
  u_int xx;
  px = data->cx + 2;
  py = (back_s->grid->hsize + data->cy) - data->oy;
  xx = window_copy_find_length(wp, py);
  while (px < xx)
  {
    grid_get_cell(back_s->grid, px, py, &gc);
    if (((!(gc.flags & 0x4)) && (gc.data.size == 1)) && ((*gc.data.data) == data->jumpchar))
    {
      window_copy_update_cursor(wp, px - 1, data->cy);
      if (window_copy_update_selection(wp, 1))
      {
        window_copy_redraw_lines(wp, data->cy, 1);
      }
      return;
    }
    px += 1;
  }

}


----------------------------
static void window_copy_cursor_jump_back(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *back_s = data->backing;
  struct grid_cell gc;
  u_int px;
  u_int py;
  px = data->cx;
  py = (back_s->grid->hsize + data->cy) - data->oy;
  if (px > 0)
  {
    px -= 1;
  }
  for (;;)
  {
    grid_get_cell(back_s->grid, px, py, &gc);
    if (((!(gc.flags & 0x4)) && (gc.data.size == 1)) && ((*gc.data.data) == data->jumpchar))
    {
      window_copy_update_cursor(wp, px, data->cy);
      if (window_copy_update_selection(wp, 1))
      {
        window_copy_redraw_lines(wp, data->cy, 1);
      }
      return;
    }
    if (px == 0)
    {
      break;
    }
    px -= 1;
  }

}


----------------------------
static int window_copy_search_down(struct window_pane *wp)
{
  return window_copy_search(wp, 1);
}


----------------------------
void helper_helper_window_copy_command_1_2(unsigned int * const argument_idx_ref, int * const redraw_ref, char * const prefix_ref, struct window_pane * const wp, struct window_copy_mode_data * const data, const char * const argument)
{
  unsigned int argument_idx = *argument_idx_ref;
  int redraw = *redraw_ref;
  char prefix = *prefix_ref;
  prefix = argument[argument_idx];
  argument_idx += 1;
  if ((data->searchx == (-1)) || (data->searchy == (-1)))
  {
    data->searchx = data->cx;
    data->searchy = data->cy;
    data->searcho = data->oy;
  }
  else
    if ((data->searchstr != 0) && (strcmp(argument, data->searchstr) != 0))
  {
    data->cx = data->searchx;
    data->cy = data->searchy;
    data->oy = data->searcho;
    redraw = 1;
  }
  if (argument[argument_idx] == '\0')
  {
    window_copy_clear_marks(wp);
    redraw = 1;
  }
  else
    if ((prefix == '=') || (prefix == '+'))
  {
    data->searchtype = WINDOW_COPY_SEARCHDOWN;
    free(data->searchstr);
    data->searchstr = xstrdup(argument);
    if (!window_copy_search_down(wp))
    {
      window_copy_clear_marks(wp);
      redraw = 1;
    }
  }
  else
    if (prefix == '-')
  {
    data->searchtype = WINDOW_COPY_SEARCHUP;
    free(data->searchstr);
    data->searchstr = xstrdup(argument);
    if (!window_copy_search_up(wp))
    {
      window_copy_clear_marks(wp);
      redraw = 1;
    }
  }
  *argument_idx_ref = argument_idx;
  *redraw_ref = redraw;
  *prefix_ref = prefix;
}


----------------------------
static void window_copy_cursor_jump(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *back_s = data->backing;
  struct grid_cell gc;
  u_int px;
  u_int py;
  u_int xx;
  px = data->cx + 1;
  py = (back_s->grid->hsize + data->cy) - data->oy;
  xx = window_copy_find_length(wp, py);
  while (px < xx)
  {
    grid_get_cell(back_s->grid, px, py, &gc);
    if (((!(gc.flags & 0x4)) && (gc.data.size == 1)) && ((*gc.data.data) == data->jumpchar))
    {
      window_copy_update_cursor(wp, px, data->cy);
      if (window_copy_update_selection(wp, 1))
      {
        window_copy_redraw_lines(wp, data->cy, 1);
      }
      return;
    }
    px += 1;
  }

}


----------------------------
static void window_copy_goto_line(struct window_pane *wp, const char *linestr)
{
  struct window_copy_mode_data *data = wp->modedata;
  const char *errstr;
  u_int lineno;
  lineno = strtonum(linestr, 0, data->backing->grid->hsize, &errstr);
  if (errstr != 0)
  {
    return;
  }
  data->oy = lineno;
  window_copy_update_selection(wp, 1);
  window_copy_redraw_screen(wp);
}


----------------------------
void helper_helper_window_copy_command_1_1(unsigned int * const argument_idx_ref, int * const redraw_ref, char * const prefix_ref, struct window_pane * const wp, struct window_copy_mode_data * const data, const char * const argument)
{
  unsigned int argument_idx = *argument_idx_ref;
  int redraw = *redraw_ref;
  char prefix = *prefix_ref;
  prefix = argument[argument_idx];
  argument_idx += 1;
  if ((data->searchx == (-1)) || (data->searchy == (-1)))
  {
    data->searchx = data->cx;
    data->searchy = data->cy;
    data->searcho = data->oy;
  }
  else
    if ((data->searchstr != 0) && (strcmp(argument, data->searchstr) != 0))
  {
    data->cx = data->searchx;
    data->cy = data->searchy;
    data->oy = data->searcho;
    redraw = 1;
  }
  if (argument[argument_idx] == '\0')
  {
    window_copy_clear_marks(wp);
    redraw = 1;
  }
  else
    if ((prefix == '=') || (prefix == '-'))
  {
    data->searchtype = WINDOW_COPY_SEARCHUP;
    free(data->searchstr);
    data->searchstr = xstrdup(argument);
    if (!window_copy_search_up(wp))
    {
      window_copy_clear_marks(wp);
      redraw = 1;
    }
  }
  else
    if (prefix == '+')
  {
    data->searchtype = WINDOW_COPY_SEARCHDOWN;
    free(data->searchstr);
    data->searchstr = xstrdup(argument);
    if (!window_copy_search_down(wp))
    {
      window_copy_clear_marks(wp);
      redraw = 1;
    }
  }
  *argument_idx_ref = argument_idx;
  *redraw_ref = redraw;
  *prefix_ref = prefix;
}


----------------------------
None
----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
static int window_copy_search_up(struct window_pane *wp)
{
  return window_copy_search(wp, 0);
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
static void window_copy_cursor_jump_to_back(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *back_s = data->backing;
  struct grid_cell gc;
  u_int px;
  u_int py;
  px = data->cx;
  py = (back_s->grid->hsize + data->cy) - data->oy;
  if (px > 0)
  {
    px -= 1;
  }
  if (px > 0)
  {
    px -= 1;
  }
  for (;;)
  {
    grid_get_cell(back_s->grid, px, py, &gc);
    if (((!(gc.flags & 0x4)) && (gc.data.size == 1)) && ((*gc.data.data) == data->jumpchar))
    {
      window_copy_update_cursor(wp, px + 1, data->cy);
      if (window_copy_update_selection(wp, 1))
      {
        window_copy_redraw_lines(wp, data->cy, 1);
      }
      return;
    }
    if (px == 0)
    {
      break;
    }
    px -= 1;
  }

}


----------------------------
static void window_copy_copy_pipe(struct window_pane *wp, struct session *s, const char *bufname, const char *arg)
{
  void *buf;
  unsigned int buf_idx = 0;
  size_t len;
  struct job *job;
  unsigned int job_idx = 0;
  char *expanded;
  unsigned int expanded_idx = 0;
  buf_idx = window_copy_get_selection(wp, &len);
  if ((&buf[buf_idx]) == 0)
  {
    return;
  }
  expanded_idx = format_single(0, arg, 0, s, 0, wp);
  job_idx = job_run(expanded, s, 0, 0, 0, 0, 0, 0x1);
  bufferevent_write(job->event, buf, len);
  free(expanded);
  window_copy_copy_buffer(wp, bufname, buf, len);
}


----------------------------
None
----------------------------
***/


static void window_copy_append_selection(struct window_pane *wp, const char *bufname)
{
  char *buf;
  unsigned int buf_idx = 0;
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  const char *bufdata;
  unsigned int bufdata_idx = 0;
  size_t len;
  size_t bufsize;
  struct screen_write_ctx ctx;
  buf_idx = window_copy_get_selection(wp, &len);
  if ((&buf[buf_idx]) == 0)
  {
    return;
  }
  if (options_get_number(global_options, "set-clipboard") != 0)
  {
    screen_write_start(&ctx, wp, 0);
    screen_write_setselection(&ctx, buf, len);
    screen_write_stop(&ctx);
    notify_pane("pane-set-clipboard", wp);
  }
  if ((bufname == 0) || ((*bufname) == '\0'))
  {
    pb_idx = paste_get_top(&bufname);
  }
  else
    pb_idx = paste_get_name(bufname);
  if ((&pb[pb_idx]) != 0)
  {
    bufdata_idx = paste_buffer_data(pb, &bufsize);
    buf_idx = xrealloc(buf_idx, len + bufsize);
    memmove((&buf[buf_idx]) + bufsize, buf, len);
    memcpy(buf, bufdata, bufsize);
    len += bufsize;
  }
  if (paste_set(buf, len, bufname, 0) != 0)
  {
    free(buf);
  }
}


/*** DEPENDENCIES:
struct paste_buffer *paste_get_top(const char **name)
{
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  pb_idx = paste_time_tree_RB_MINMAX(&paste_by_time, -1);
  if ((&pb[pb_idx]) == 0)
  {
    return 0;
  }
  if (name != 0)
  {
    *name = pb->name;
  }
  return pb;
}


----------------------------
int paste_set(char *data, size_t size, const char *name, char **cause)
{
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  struct paste_buffer *old;
  unsigned int old_idx = 0;
  if (cause != 0)
  {
    *cause = 0;
  }
  if (size == 0)
  {
    free(data);
    return 0;
  }
  if (name == 0)
  {
    paste_add(data, size);
    return 0;
  }
  if ((*name) == '\0')
  {
    if (cause != 0)
    {
      *cause = xstrdup("empty buffer name");
    }
    return -1;
  }
  pb_idx = xmalloc(sizeof(*pb_idx));
  pb->name = xstrdup(name);
  pb->data = data;
  pb->size = size;
  pb->automatic = 0;
  pb->order = paste_next_order;
  paste_next_order += 1;
  pb->created = time(0);
  if ((old_idx = paste_get_name(name)) != 0)
  {
    paste_free(old);
  }
  paste_name_tree_RB_INSERT(&paste_by_name, pb);
  paste_time_tree_RB_INSERT(&paste_by_time, pb);
  return 0;
}


----------------------------
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
struct paste_buffer *paste_get_name(const char *name)
{
  struct paste_buffer pbfind;
  if ((name == 0) || ((*name) == '\0'))
  {
    return 0;
  }
  pbfind.name = (char *) name;
  return paste_name_tree_RB_FIND(&paste_by_name, &pbfind);
}


----------------------------
static void *window_copy_get_selection(struct window_pane *wp, size_t *len)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  char *buf;
  unsigned int buf_idx = 0;
  size_t off;
  u_int i;
  u_int xx;
  u_int yy;
  u_int sx;
  u_int sy;
  u_int ex;
  u_int ey;
  u_int ey_last;
  u_int firstsx;
  u_int lastex;
  u_int restex;
  u_int restsx;
  u_int selx;
  int keys;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return 0;
  }
  buf_idx = xmalloc(1);
  off = 0;
  buf[buf_idx] = '\0';
  xx = data->endselx;
  yy = data->endsely;
  if ((yy < data->sely) || ((yy == data->sely) && (xx < data->selx)))
  {
    sx = xx;
    sy = yy;
    ex = data->selx;
    ey = data->sely;
  }
  else
  {
    sx = data->selx;
    sy = data->sely;
    ex = xx;
    ey = yy;
  }
  ey_last = window_copy_find_length(wp, ey);
  if (ex > ey_last)
  {
    ex = ey_last;
  }
  xx = s->grid->sx;
  keys = options_get_number(wp->window->options, "mode-keys");
  if (data->rectflag)
  {
    helper_window_copy_get_selection_1(&firstsx, &lastex, &restex, &restsx, &selx, data, keys);
  }
  else
  {
    if (keys == 0)
    {
      lastex = ex;
    }
    else
      lastex = ex + 1;
    restex = xx;
    firstsx = sx;
    restsx = 0;
  }
  for (i = sy; i <= ey; i += 1)
  {
    window_copy_copy_line(wp, &(&buf[buf_idx]), &off, i, (i == sy) ? (firstsx) : (restsx), (i == ey) ? (lastex) : (restex));
  }

  if (off == 0)
  {
    free(buf);
    return 0;
  }
  if ((keys == 0) || (lastex <= ey_last))
  {
    off -= 1;
  }
  *len = off;
  return buf;
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
struct paste_buffer
{
  char *data;
  size_t size;
  char *name;
  time_t created;
  int automatic;
  u_int order;
  struct 
  {
    struct paste_buffer *rbe_left;
    struct paste_buffer *rbe_right;
    struct paste_buffer *rbe_parent;
    int rbe_color;
  } name_entry;
  struct 
  {
    struct paste_buffer *rbe_left;
    struct paste_buffer *rbe_right;
    struct paste_buffer *rbe_parent;
    int rbe_color;
  } time_entry;
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
const char *paste_buffer_data(struct paste_buffer *pb, size_t *size)
{
  if (size != 0)
  {
    *size = pb->size;
  }
  return pb->data;
}


----------------------------
None
----------------------------
void *xrealloc(void *ptr, size_t size)
{
  return xreallocarray(ptr, 1, size);
}


----------------------------
None
----------------------------
***/


// hint:  ['ws_idx_ref is a mutable refrence to unsigned int', 'np_ref is a mutable refrence to u_int', 'cancel_ref is a mutable refrence to int', 'redraw_ref is a mutable refrence to int', 'scroll_exit_ref is a mutable refrence to int']
void helper_window_copy_command_2(unsigned int * const ws_idx_ref, u_int * const np_ref, int * const cancel_ref, int * const redraw_ref, int * const scroll_exit_ref, struct window_pane * const wp, struct client * const c, struct session * const s, struct mouse_event * const m, struct window_copy_mode_data * const data, struct screen * const sn, const char * const command, const char * const ws)
{
  unsigned int ws_idx = *ws_idx_ref;
  u_int np = *np_ref;
  int cancel = *cancel_ref;
  int redraw = *redraw_ref;
  int scroll_exit = *scroll_exit_ref;
  if (strcmp(command, "append-selection") == 0)
  {
    if (s != 0)
    {
      window_copy_append_selection(wp, 0);
    }
    window_copy_clear_selection(wp);
    redraw = 1;
  }
  if (strcmp(command, "append-selection-and-cancel") == 0)
  {
    if (s != 0)
    {
      window_copy_append_selection(wp, 0);
    }
    window_copy_clear_selection(wp);
    redraw = 1;
    cancel = 1;
  }
  if (strcmp(command, "back-to-indentation") == 0)
  {
    window_copy_cursor_back_to_indentation(wp);
  }
  if (strcmp(command, "begin-selection") == 0)
  {
    if (m != 0)
    {
      window_copy_start_drag(c, m);
    }
    else
    {
      sn->sel.lineflag = LINE_SEL_NONE;
      window_copy_start_selection(wp);
      redraw = 1;
    }
  }
  if (strcmp(command, "stop-selection") == 0)
  {
    data->cursordrag = CURSORDRAG_NONE;
  }
  if (strcmp(command, "bottom-line") == 0)
  {
    data->cx = 0;
    data->cy = sn->grid->sy - 1;
    window_copy_update_selection(wp, 1);
    redraw = 1;
  }
  if (strcmp(command, "cancel") == 0)
  {
    cancel = 1;
  }
  if (strcmp(command, "clear-selection") == 0)
  {
    window_copy_clear_selection(wp);
    redraw = 1;
  }
  if (strcmp(command, "copy-end-of-line") == 0)
  {
    window_copy_start_selection(wp);
    for (; np > 1; np -= 1)
    {
      window_copy_cursor_down(wp, 0);
    }

    window_copy_cursor_end_of_line(wp);
    redraw = 1;
    if (s != 0)
    {
      window_copy_copy_selection(wp, 0);
      cancel = 1;
    }
  }
  if (strcmp(command, "copy-line") == 0)
  {
    window_copy_cursor_start_of_line(wp);
    window_copy_start_selection(wp);
    for (; np > 1; np -= 1)
    {
      window_copy_cursor_down(wp, 0);
    }

    window_copy_cursor_end_of_line(wp);
    redraw = 1;
    if (s != 0)
    {
      window_copy_copy_selection(wp, 0);
      cancel = 1;
    }
  }
  if (strcmp(command, "copy-selection") == 0)
  {
    if (s != 0)
    {
      window_copy_copy_selection(wp, 0);
    }
    window_copy_clear_selection(wp);
    redraw = 1;
  }
  if (strcmp(command, "copy-selection-and-cancel") == 0)
  {
    if (s != 0)
    {
      window_copy_copy_selection(wp, 0);
    }
    window_copy_clear_selection(wp);
    redraw = 1;
    cancel = 1;
  }
  if (strcmp(command, "cursor-down") == 0)
  {
    for (; np != 0; np -= 1)
    {
      window_copy_cursor_down(wp, 0);
    }

  }
  if (strcmp(command, "cursor-left") == 0)
  {
    for (; np != 0; np -= 1)
    {
      window_copy_cursor_left(wp);
    }

  }
  if (strcmp(command, "cursor-right") == 0)
  {
    for (; np != 0; np -= 1)
    {
      window_copy_cursor_right(wp);
    }

  }
  if (strcmp(command, "cursor-up") == 0)
  {
    for (; np != 0; np -= 1)
    {
      window_copy_cursor_up(wp, 0);
    }

  }
  if (strcmp(command, "end-of-line") == 0)
  {
    window_copy_cursor_end_of_line(wp);
  }
  if ((strcmp(command, "halfpage-down") == 0) || (strcmp(command, "halfpage-down-and-cancel") == 0))
  {
    if (strcmp(command, "halfpage-down-and-cancel") == 0)
    {
      scroll_exit = 1;
    }
    else
      scroll_exit = data->scroll_exit;
    for (; np != 0; np -= 1)
    {
      if (window_copy_pagedown(wp, 1, scroll_exit))
      {
        cancel = 1;
        break;
      }
    }

  }
  if (strcmp(command, "halfpage-up") == 0)
  {
    for (; np != 0; np -= 1)
    {
      window_copy_pageup(wp, 1);
    }

  }
  if (strcmp(command, "history-bottom") == 0)
  {
    data->cx = 0;
    data->cy = sn->grid->sy - 1;
    data->oy = 0;
    window_copy_update_selection(wp, 1);
    redraw = 1;
  }
  if (strcmp(command, "history-top") == 0)
  {
    data->cx = 0;
    data->cy = 0;
    data->oy = data->backing->grid->hsize;
    window_copy_update_selection(wp, 1);
    redraw = 1;
  }
  if (strcmp(command, "jump-again") == 0)
  {
    helper_helper_window_copy_command_2_1(&np, wp, data);
  }
  if (strcmp(command, "jump-reverse") == 0)
  {
    helper_helper_window_copy_command_2_2(&np, wp, data);
  }
  if (strcmp(command, "middle-line") == 0)
  {
    data->cx = 0;
    data->cy = (sn->grid->sy - 1) / 2;
    window_copy_update_selection(wp, 1);
    redraw = 1;
  }
  if (strcmp(command, "next-paragraph") == 0)
  {
    for (; np != 0; np -= 1)
    {
      window_copy_next_paragraph(wp);
    }

  }
  if (strcmp(command, "next-space") == 0)
  {
    for (; np != 0; np -= 1)
    {
      window_copy_cursor_next_word(wp, " ");
    }

  }
  if (strcmp(command, "next-space-end") == 0)
  {
    for (; np != 0; np -= 1)
    {
      window_copy_cursor_next_word_end(wp, " ");
    }

  }
  if (strcmp(command, "next-word") == 0)
  {
    ws_idx = options_get_string(s->options, "word-separators");
    for (; np != 0; np -= 1)
    {
      window_copy_cursor_next_word(wp, ws);
    }

  }
  if (strcmp(command, "next-word-end") == 0)
  {
    ws_idx = options_get_string(s->options, "word-separators");
    for (; np != 0; np -= 1)
    {
      window_copy_cursor_next_word_end(wp, ws);
    }

  }
  if (strcmp(command, "other-end") == 0)
  {
    if ((np % 2) != 0)
    {
      window_copy_other_end(wp);
    }
  }
  if ((strcmp(command, "page-down") == 0) || (strcmp(command, "page-down-and-cancel") == 0))
  {
    if (strcmp(command, "page-down-and-cancel") == 0)
    {
      scroll_exit = 1;
    }
    else
      scroll_exit = data->scroll_exit;
    for (; np != 0; np -= 1)
    {
      if (window_copy_pagedown(wp, 0, scroll_exit))
      {
        cancel = 1;
        break;
      }
    }

  }
  if (strcmp(command, "page-up") == 0)
  {
    for (; np != 0; np -= 1)
    {
      window_copy_pageup(wp, 0);
    }

  }
  if (strcmp(command, "previous-paragraph") == 0)
  {
    for (; np != 0; np -= 1)
    {
      window_copy_previous_paragraph(wp);
    }

  }
  if (strcmp(command, "previous-space") == 0)
  {
    for (; np != 0; np -= 1)
    {
      window_copy_cursor_previous_word(wp, " ");
    }

  }
  if (strcmp(command, "previous-word") == 0)
  {
    ws_idx = options_get_string(s->options, "word-separators");
    for (; np != 0; np -= 1)
    {
      window_copy_cursor_previous_word(wp, ws);
    }

  }
  if (strcmp(command, "rectangle-toggle") == 0)
  {
    sn->sel.lineflag = LINE_SEL_NONE;
    window_copy_rectangle_toggle(wp);
  }
  if ((strcmp(command, "scroll-down") == 0) || (strcmp(command, "scroll-down-and-cancel") == 0))
  {
    if (strcmp(command, "scroll-down-and-cancel") == 0)
    {
      scroll_exit = 1;
    }
    else
      scroll_exit = data->scroll_exit;
    for (; np != 0; np -= 1)
    {
      window_copy_cursor_down(wp, 1);
    }

    if (scroll_exit && (data->oy == 0))
    {
      cancel = 1;
    }
  }
  if (strcmp(command, "scroll-up") == 0)
  {
    for (; np != 0; np -= 1)
    {
      window_copy_cursor_up(wp, 1);
    }

  }
  if (strcmp(command, "search-again") == 0)
  {
    if (data->searchtype == WINDOW_COPY_SEARCHUP)
    {
      for (; np != 0; np -= 1)
      {
        window_copy_search_up(wp);
      }

    }
    else
      if (data->searchtype == WINDOW_COPY_SEARCHDOWN)
    {
      for (; np != 0; np -= 1)
      {
        window_copy_search_down(wp);
      }

    }
  }
  if (strcmp(command, "search-reverse") == 0)
  {
    if (data->searchtype == WINDOW_COPY_SEARCHUP)
    {
      for (; np != 0; np -= 1)
      {
        window_copy_search_down(wp);
      }

    }
    else
      if (data->searchtype == WINDOW_COPY_SEARCHDOWN)
    {
      for (; np != 0; np -= 1)
      {
        window_copy_search_up(wp);
      }

    }
  }
  if (strcmp(command, "select-line") == 0)
  {
    sn->sel.lineflag = LINE_SEL_LEFT_RIGHT;
    data->rectflag = 0;
    window_copy_cursor_start_of_line(wp);
    window_copy_start_selection(wp);
    for (; np > 1; np -= 1)
    {
      window_copy_cursor_down(wp, 0);
    }

    window_copy_cursor_end_of_line(wp);
    redraw = 1;
  }
  if (strcmp(command, "select-word") == 0)
  {
    sn->sel.lineflag = LINE_SEL_LEFT_RIGHT;
    data->rectflag = 0;
    ws_idx = options_get_string(s->options, "word-separators");
    window_copy_cursor_previous_word(wp, ws);
    window_copy_start_selection(wp);
    window_copy_cursor_next_word_end(wp, ws);
    redraw = 1;
  }
  if (strcmp(command, "start-of-line") == 0)
  {
    window_copy_cursor_start_of_line(wp);
  }
  if (strcmp(command, "top-line") == 0)
  {
    data->cx = 0;
    data->cy = 0;
    window_copy_update_selection(wp, 1);
    redraw = 1;
  }
  *ws_idx_ref = ws_idx;
  *np_ref = np;
  *cancel_ref = cancel;
  *redraw_ref = redraw;
  *scroll_exit_ref = scroll_exit;
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
static int window_copy_search_down(struct window_pane *wp)
{
  return window_copy_search(wp, 1);
}


----------------------------
static int window_copy_pagedown(struct window_pane *wp, int half_page, int scroll_exit)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  u_int n;
  u_int ox;
  u_int oy;
  u_int px;
  u_int py;
  oy = (data->backing->grid->hsize + data->cy) - data->oy;
  ox = window_copy_find_length(wp, oy);
  if ((s->sel.lineflag == LINE_SEL_RIGHT_LEFT) && (oy == data->sely))
  {
    window_copy_other_end(wp);
  }
  if (data->cx != ox)
  {
    data->lastcx = data->cx;
    data->lastsx = ox;
  }
  data->cx = data->lastcx;
  n = 1;
  if (s->grid->sy > 2)
  {
    if (half_page)
    {
      n = s->grid->sy / 2;
    }
    else
      n = s->grid->sy - 2;
  }
  if (data->oy < n)
  {
    data->oy = 0;
  }
  else
    data->oy -= n;
  if ((!data->screen.sel.flag) || (!data->rectflag))
  {
    py = (data->backing->grid->hsize + data->cy) - data->oy;
    px = window_copy_find_length(wp, py);
    if (((data->cx >= data->lastsx) && (data->cx != px)) || (data->cx > px))
    {
      window_copy_cursor_end_of_line(wp);
    }
  }
  if (scroll_exit && (data->oy == 0))
  {
    return 1;
  }
  window_copy_update_selection(wp, 1);
  window_copy_redraw_screen(wp);
  return 0;
}


----------------------------
static void window_copy_other_end(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  u_int selx;
  u_int sely;
  u_int cy;
  u_int yy;
  u_int hsize;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return;
  }
  if (s->sel.lineflag == LINE_SEL_LEFT_RIGHT)
  {
    s->sel.lineflag = LINE_SEL_RIGHT_LEFT;
  }
  else
    if (s->sel.lineflag == LINE_SEL_RIGHT_LEFT)
  {
    s->sel.lineflag = LINE_SEL_LEFT_RIGHT;
  }
  switch (data->cursordrag)
  {
    case CURSORDRAG_NONE:

    case CURSORDRAG_SEL:
    {
      data->cursordrag = CURSORDRAG_ENDSEL;
      break;
    }

    case CURSORDRAG_ENDSEL:
    {
      data->cursordrag = CURSORDRAG_SEL;
      break;
    }

  }

  selx = data->endselx;
  sely = data->endsely;
  if (data->cursordrag == CURSORDRAG_SEL)
  {
    selx = data->selx;
    sely = data->sely;
  }
  cy = data->cy;
  yy = (data->backing->grid->hsize + data->cy) - data->oy;
  data->cx = selx;
  hsize = data->backing->grid->hsize;
  if (sely < (hsize - data->oy))
  {
    data->oy = hsize - sely;
    data->cy = 0;
  }
  else
    if (sely > ((hsize - data->oy) + s->grid->sy))
  {
    data->oy = ((hsize - sely) + s->grid->sy) - 1;
    data->cy = s->grid->sy - 1;
  }
  else
    data->cy = (cy + sely) - yy;
  window_copy_update_selection(wp, 1);
  window_copy_redraw_screen(wp);
}


----------------------------
static void window_copy_append_selection(struct window_pane *wp, const char *bufname)
{
  char *buf;
  unsigned int buf_idx = 0;
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  const char *bufdata;
  unsigned int bufdata_idx = 0;
  size_t len;
  size_t bufsize;
  struct screen_write_ctx ctx;
  buf_idx = window_copy_get_selection(wp, &len);
  if ((&buf[buf_idx]) == 0)
  {
    return;
  }
  if (options_get_number(global_options, "set-clipboard") != 0)
  {
    screen_write_start(&ctx, wp, 0);
    screen_write_setselection(&ctx, buf, len);
    screen_write_stop(&ctx);
    notify_pane("pane-set-clipboard", wp);
  }
  if ((bufname == 0) || ((*bufname) == '\0'))
  {
    pb_idx = paste_get_top(&bufname);
  }
  else
    pb_idx = paste_get_name(bufname);
  if ((&pb[pb_idx]) != 0)
  {
    bufdata_idx = paste_buffer_data(pb, &bufsize);
    buf_idx = xrealloc(buf_idx, len + bufsize);
    memmove((&buf[buf_idx]) + bufsize, buf, len);
    memcpy(buf, bufdata, bufsize);
    len += bufsize;
  }
  if (paste_set(buf, len, bufname, 0) != 0)
  {
    free(buf);
  }
}


----------------------------
static void window_copy_cursor_left(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  u_int py;
  u_int cx;
  struct grid_cell gc;
  py = (data->backing->grid->hsize + data->cy) - data->oy;
  cx = data->cx;
  while (cx > 0)
  {
    grid_get_cell(data->backing->grid, cx, py, &gc);
    if ((~gc.flags) & 0x4)
    {
      break;
    }
    cx -= 1;
  }

  if ((cx == 0) && (py > 0))
  {
    window_copy_cursor_up(wp, 0);
    window_copy_cursor_end_of_line(wp);
  }
  else
    if (cx > 0)
  {
    window_copy_update_cursor(wp, cx - 1, data->cy);
    if (window_copy_update_selection(wp, 1))
    {
      window_copy_redraw_lines(wp, data->cy, 1);
    }
  }
}


----------------------------
void window_copy_start_drag(struct client *c, struct mouse_event *m)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int x;
  u_int y;
  if (c == 0)
  {
    return;
  }
  wp_idx = cmd_mouse_pane(m, 0, 0);
  if (((&wp[wp_idx]) == 0) || (wp->mode != (&window_copy_mode)))
  {
    return;
  }
  if (cmd_mouse_at(wp, m, &x, &y, 1) != 0)
  {
    return;
  }
  c->tty.mouse_drag_update = window_copy_drag_update;
  c->tty.mouse_drag_release = 0;
  window_copy_update_cursor(wp, x, y);
  window_copy_start_selection(wp);
  window_copy_redraw_screen(wp);
}


----------------------------
static void window_copy_cursor_right(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  u_int px;
  u_int py;
  u_int yy;
  u_int cx;
  u_int cy;
  struct grid_cell gc;
  py = (data->backing->grid->hsize + data->cy) - data->oy;
  yy = (data->backing->grid->hsize + data->backing->grid->sy) - 1;
  if (data->screen.sel.flag && data->rectflag)
  {
    px = (&data->screen)->grid->sx;
  }
  else
    px = window_copy_find_length(wp, py);
  if ((data->cx >= px) && (py < yy))
  {
    window_copy_cursor_start_of_line(wp);
    window_copy_cursor_down(wp, 0);
  }
  else
    if (data->cx < px)
  {
    cx = data->cx + 1;
    cy = (data->backing->grid->hsize + data->cy) - data->oy;
    while (cx < px)
    {
      grid_get_cell(data->backing->grid, cx, cy, &gc);
      if ((~gc.flags) & 0x4)
      {
        break;
      }
      cx += 1;
    }

    window_copy_update_cursor(wp, cx, data->cy);
    if (window_copy_update_selection(wp, 1))
    {
      window_copy_redraw_lines(wp, data->cy, 1);
    }
  }
}


----------------------------
static void window_copy_rectangle_toggle(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  u_int px;
  u_int py;
  data->rectflag = !data->rectflag;
  py = (data->backing->grid->hsize + data->cy) - data->oy;
  px = window_copy_find_length(wp, py);
  if (data->cx > px)
  {
    window_copy_update_cursor(wp, px, data->cy);
  }
  window_copy_update_selection(wp, 1);
  window_copy_redraw_screen(wp);
}


----------------------------
static void window_copy_start_selection(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  data->selx = data->cx;
  data->sely = (data->backing->grid->hsize + data->cy) - data->oy;
  data->endselx = data->selx;
  data->endsely = data->sely;
  data->cursordrag = CURSORDRAG_ENDSEL;
  s->sel.flag = 1;
  window_copy_update_selection(wp, 1);
}


----------------------------
static void window_copy_previous_paragraph(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  u_int oy;
  oy = (data->backing->grid->hsize + data->cy) - data->oy;
  while ((oy > 0) && (window_copy_find_length(wp, oy) == 0))
  {
    oy -= 1;
  }

  while ((oy > 0) && (window_copy_find_length(wp, oy) > 0))
  {
    oy -= 1;
  }

  window_copy_scroll_to(wp, 0, oy);
}


----------------------------
None
----------------------------
static int window_copy_update_selection(struct window_pane *wp, int may_redraw)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct options *oo = wp->window->options;
  struct grid_cell gc;
  u_int sx;
  u_int sy;
  u_int cy;
  u_int endsx;
  u_int endsy;
  int startrelpos;
  int endrelpos;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return 0;
  }
  window_copy_synchronize_cursor(wp);
  sx = data->selx;
  sy = data->sely;
  startrelpos = window_copy_adjust_selection(wp, &sx, &sy);
  endsx = data->endselx;
  endsy = data->endsely;
  endrelpos = window_copy_adjust_selection(wp, &endsx, &endsy);
  if ((startrelpos == endrelpos) && (startrelpos != WINDOW_COPY_REL_POS_ON_SCREEN))
  {
    screen_hide_selection(s);
    return 0;
  }
  style_apply(&gc, oo, "mode-style");
  gc.flags |= 0x20;
  screen_set_selection(s, sx, sy, endsx, endsy, data->rectflag, &gc);
  if (data->rectflag && may_redraw)
  {
    cy = data->cy;
    if (data->cursordrag == CURSORDRAG_ENDSEL)
    {
      if (sy < cy)
      {
        window_copy_redraw_lines(wp, sy, (cy - sy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (sy - cy) + 1);
    }
    else
    {
      if (endsy < cy)
      {
        window_copy_redraw_lines(wp, endsy, (cy - endsy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (endsy - cy) + 1);
    }
  }
  return 1;
}


----------------------------
static void window_copy_copy_selection(struct window_pane *wp, const char *bufname)
{
  void *buf;
  unsigned int buf_idx = 0;
  size_t len;
  buf_idx = window_copy_get_selection(wp, &len);
  if ((&buf[buf_idx]) == 0)
  {
    return;
  }
  window_copy_copy_buffer(wp, bufname, buf, len);
}


----------------------------
static void window_copy_cursor_back_to_indentation(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  u_int px;
  u_int py;
  u_int xx;
  struct grid_cell gc;
  px = 0;
  py = (data->backing->grid->hsize + data->cy) - data->oy;
  xx = window_copy_find_length(wp, py);
  while (px < xx)
  {
    grid_get_cell(data->backing->grid, px, py, &gc);
    if ((gc.data.size != 1) || ((*gc.data.data) != ' '))
    {
      break;
    }
    px += 1;
  }

  window_copy_update_cursor(wp, px, data->cy);
  if (window_copy_update_selection(wp, 1))
  {
    window_copy_redraw_lines(wp, data->cy, 1);
  }
}


----------------------------
static void window_copy_next_paragraph(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  u_int maxy;
  u_int ox;
  u_int oy;
  oy = (data->backing->grid->hsize + data->cy) - data->oy;
  maxy = (data->backing->grid->hsize + s->grid->sy) - 1;
  while ((oy < maxy) && (window_copy_find_length(wp, oy) == 0))
  {
    oy += 1;
  }

  while ((oy < maxy) && (window_copy_find_length(wp, oy) > 0))
  {
    oy += 1;
  }

  ox = window_copy_find_length(wp, oy);
  window_copy_scroll_to(wp, ox, oy);
}


----------------------------
static void window_copy_cursor_next_word_end(struct window_pane *wp, const char *separators)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct options *oo = wp->window->options;
  struct screen *back_s = data->backing;
  u_int px;
  u_int py;
  u_int xx;
  u_int yy;
  int keys;
  int expected = 1;
  px = data->cx;
  py = (back_s->grid->hsize + data->cy) - data->oy;
  xx = window_copy_find_length(wp, py);
  yy = (back_s->grid->hsize + back_s->grid->sy) - 1;
  keys = options_get_number(oo, "mode-keys");
  if ((keys == 1) && (!window_copy_in_set(wp, px, py, separators)))
  {
    px += 1;
  }
  do
  {
    while ((px > xx) || (window_copy_in_set(wp, px, py, separators) == expected))
    {
      if (px > xx)
      {
        if (py == yy)
        {
          return;
        }
        window_copy_cursor_down(wp, 0);
        px = 0;
        py = (back_s->grid->hsize + data->cy) - data->oy;
        xx = window_copy_find_length(wp, py);
      }
      else
        px++;
      px += 1;
    }

    expected = !expected;
  }
  while (expected == 0);
  if ((keys == 1) && (px != 0))
  {
    px -= 1;
  }
  window_copy_update_cursor(wp, px, data->cy);
  if (window_copy_update_selection(wp, 1))
  {
    window_copy_redraw_lines(wp, data->cy, 1);
  }
}


----------------------------
None
----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
void helper_helper_window_copy_command_2_1(u_int * const np_ref, struct window_pane * const wp, struct window_copy_mode_data * const data)
{
  u_int np = *np_ref;
  switch (data->jumptype)
  {
    case WINDOW_COPY_JUMPFORWARD:
    {
      for (; np != 0; np -= 1)
      {
        window_copy_cursor_jump(wp);
      }

      break;
    }

    case WINDOW_COPY_JUMPBACKWARD:
    {
      for (; np != 0; np -= 1)
      {
        window_copy_cursor_jump_back(wp);
      }

      break;
    }

    case WINDOW_COPY_JUMPTOFORWARD:
    {
      for (; np != 0; np -= 1)
      {
        window_copy_cursor_jump_to(wp);
      }

      break;
    }

    case WINDOW_COPY_JUMPTOBACKWARD:
    {
      for (; np != 0; np -= 1)
      {
        window_copy_cursor_jump_to_back(wp);
      }

      break;
    }

  }

  *np_ref = np;
}


----------------------------
static void window_copy_cursor_next_word(struct window_pane *wp, const char *separators)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *back_s = data->backing;
  u_int px;
  u_int py;
  u_int xx;
  u_int yy;
  int expected = 0;
  px = data->cx;
  py = (back_s->grid->hsize + data->cy) - data->oy;
  xx = window_copy_find_length(wp, py);
  yy = (back_s->grid->hsize + back_s->grid->sy) - 1;
  do
  {
    while ((px > xx) || (window_copy_in_set(wp, px, py, separators) == expected))
    {
      if (px > xx)
      {
        if (py == yy)
        {
          return;
        }
        window_copy_cursor_down(wp, 0);
        px = 0;
        py = (back_s->grid->hsize + data->cy) - data->oy;
        xx = window_copy_find_length(wp, py);
      }
      else
        px++;
      px += 1;
    }

    expected = !expected;
  }
  while (expected == 1);
  window_copy_update_cursor(wp, px, data->cy);
  if (window_copy_update_selection(wp, 1))
  {
    window_copy_redraw_lines(wp, data->cy, 1);
  }
}


----------------------------
static int window_copy_search_up(struct window_pane *wp)
{
  return window_copy_search(wp, 0);
}


----------------------------
void helper_helper_window_copy_command_2_2(u_int * const np_ref, struct window_pane * const wp, struct window_copy_mode_data * const data)
{
  u_int np = *np_ref;
  switch (data->jumptype)
  {
    case WINDOW_COPY_JUMPFORWARD:
    {
      for (; np != 0; np -= 1)
      {
        window_copy_cursor_jump_back(wp);
      }

      break;
    }

    case WINDOW_COPY_JUMPBACKWARD:
    {
      for (; np != 0; np -= 1)
      {
        window_copy_cursor_jump(wp);
      }

      break;
    }

    case WINDOW_COPY_JUMPTOFORWARD:
    {
      for (; np != 0; np -= 1)
      {
        window_copy_cursor_jump_to_back(wp);
      }

      break;
    }

    case WINDOW_COPY_JUMPTOBACKWARD:
    {
      for (; np != 0; np -= 1)
      {
        window_copy_cursor_jump_to(wp);
      }

      break;
    }

  }

  *np_ref = np;
}


----------------------------
static void window_copy_cursor_previous_word(struct window_pane *wp, const char *separators)
{
  struct window_copy_mode_data *data = wp->modedata;
  u_int px;
  u_int py;
  px = data->cx;
  py = (data->backing->grid->hsize + data->cy) - data->oy;
  for (;;)
  {
    if (px > 0)
    {
      px -= 1;
      if (!window_copy_in_set(wp, px, py, separators))
      {
        break;
      }
    }
    else
    {
      if ((data->cy == 0) && ((data->backing->grid->hsize == 0) || (data->oy >= (data->backing->grid->hsize - 1))))
      {
        goto out;
      }
      window_copy_cursor_up(wp, 0);
      py = (data->backing->grid->hsize + data->cy) - data->oy;
      px = window_copy_find_length(wp, py);
    }
  }

  while ((px > 0) && (!window_copy_in_set(wp, px - 1, py, separators)))
  {
    px -= 1;
  }

  out:
  window_copy_update_cursor(wp, px, data->cy);

  if (window_copy_update_selection(wp, 1))
  {
    window_copy_redraw_lines(wp, data->cy, 1);
  }
}


----------------------------
static void window_copy_clear_selection(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  u_int px;
  u_int py;
  screen_clear_selection(&data->screen);
  data->cursordrag = CURSORDRAG_NONE;
  py = (data->backing->grid->hsize + data->cy) - data->oy;
  px = window_copy_find_length(wp, py);
  if (data->cx > px)
  {
    window_copy_update_cursor(wp, px, data->cy);
  }
}


----------------------------
void window_copy_pageup(struct window_pane *wp, int half_page)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  u_int n;
  u_int ox;
  u_int oy;
  u_int px;
  u_int py;
  oy = (data->backing->grid->hsize + data->cy) - data->oy;
  ox = window_copy_find_length(wp, oy);
  if ((s->sel.lineflag == LINE_SEL_LEFT_RIGHT) && (oy == data->sely))
  {
    window_copy_other_end(wp);
  }
  if (data->cx != ox)
  {
    data->lastcx = data->cx;
    data->lastsx = ox;
  }
  data->cx = data->lastcx;
  n = 1;
  if (s->grid->sy > 2)
  {
    if (half_page)
    {
      n = s->grid->sy / 2;
    }
    else
      n = s->grid->sy - 2;
  }
  if ((data->oy + n) > data->backing->grid->hsize)
  {
    data->oy = data->backing->grid->hsize;
  }
  else
    data->oy += n;
  if ((!data->screen.sel.flag) || (!data->rectflag))
  {
    py = (data->backing->grid->hsize + data->cy) - data->oy;
    px = window_copy_find_length(wp, py);
    if (((data->cx >= data->lastsx) && (data->cx != px)) || (data->cx > px))
    {
      window_copy_cursor_end_of_line(wp);
    }
  }
  window_copy_update_selection(wp, 1);
  window_copy_redraw_screen(wp);
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


static void window_copy_command(struct window_pane *wp, struct client *c, struct session *s, struct args *args, struct mouse_event *m)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *sn = &data->screen;
  const char *command;
  unsigned int command_idx = 0;
  const char *argument;
  unsigned int argument_idx = 0;
  const char *ws;
  unsigned int ws_idx = 0;
  u_int np = wp->modeprefix;
  int cancel = 0;
  int redraw = 0;
  int scroll_exit;
  char prefix;
  if (args->argc == 0)
  {
    return;
  }
  command_idx = args->argv[0];
  if ((m != 0) && m->valid)
  {
    window_copy_move_mouse(m);
  }
  if (args->argc == 1)
  {
    helper_window_copy_command_2(&ws_idx, &np, &cancel, &redraw, &scroll_exit, wp, c, s, m, data, sn, command, ws);
  }
  else
    if ((args->argc == 2) && ((*args->argv[1]) != '\0'))
  {
    helper_window_copy_command_1(&argument_idx, &np, &cancel, &redraw, &prefix, wp, s, args, data, command, argument);
  }
  if ((strncmp(command, "search-", 7) != 0) && (data->searchmark != 0))
  {
    window_copy_clear_marks(wp);
    redraw = 1;
    data->searchx = (data->searchy = -1);
  }
  if (cancel)
  {
    window_pane_reset_mode(wp);
  }
  else
    if (redraw)
  {
    window_copy_redraw_screen(wp);
  }
  wp->modeprefix = 1;
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
void helper_window_copy_command_1(unsigned int * const argument_idx_ref, u_int * const np_ref, int * const cancel_ref, int * const redraw_ref, char * const prefix_ref, struct window_pane * const wp, struct session * const s, struct args * const args, struct window_copy_mode_data * const data, const char * const command, const char * const argument)
{
  unsigned int argument_idx = *argument_idx_ref;
  u_int np = *np_ref;
  int cancel = *cancel_ref;
  int redraw = *redraw_ref;
  char prefix = *prefix_ref;
  argument_idx = args->argv[1];
  if (strcmp(command, "copy-pipe") == 0)
  {
    if (s != 0)
    {
      window_copy_copy_pipe(wp, s, 0, argument);
    }
  }
  if (strcmp(command, "copy-pipe-and-cancel") == 0)
  {
    if (s != 0)
    {
      window_copy_copy_pipe(wp, s, 0, argument);
      cancel = 1;
    }
  }
  if (strcmp(command, "goto-line") == 0)
  {
    window_copy_goto_line(wp, argument);
  }
  if (strcmp(command, "jump-backward") == 0)
  {
    data->jumptype = WINDOW_COPY_JUMPBACKWARD;
    data->jumpchar = argument[argument_idx];
    for (; np != 0; np -= 1)
    {
      window_copy_cursor_jump_back(wp);
    }

  }
  if (strcmp(command, "jump-forward") == 0)
  {
    data->jumptype = WINDOW_COPY_JUMPFORWARD;
    data->jumpchar = argument[argument_idx];
    for (; np != 0; np -= 1)
    {
      window_copy_cursor_jump(wp);
    }

  }
  if (strcmp(command, "jump-to-backward") == 0)
  {
    data->jumptype = WINDOW_COPY_JUMPTOBACKWARD;
    data->jumpchar = argument[argument_idx];
    for (; np != 0; np -= 1)
    {
      window_copy_cursor_jump_to_back(wp);
    }

  }
  if (strcmp(command, "jump-to-forward") == 0)
  {
    data->jumptype = WINDOW_COPY_JUMPTOFORWARD;
    data->jumpchar = argument[argument_idx];
    for (; np != 0; np -= 1)
    {
      window_copy_cursor_jump_to(wp);
    }

  }
  if (strcmp(command, "search-backward") == 0)
  {
    data->searchtype = WINDOW_COPY_SEARCHUP;
    free(data->searchstr);
    data->searchstr = xstrdup(argument);
    for (; np != 0; np -= 1)
    {
      window_copy_search_up(wp);
    }

  }
  if (strcmp(command, "search-forward") == 0)
  {
    data->searchtype = WINDOW_COPY_SEARCHDOWN;
    free(data->searchstr);
    data->searchstr = xstrdup(argument);
    for (; np != 0; np -= 1)
    {
      window_copy_search_down(wp);
    }

  }
  if (strcmp(command, "search-backward-incremental") == 0)
  {
    helper_helper_window_copy_command_1_1(&argument_idx, &redraw, &prefix, wp, data, argument);
  }
  if (strcmp(command, "search-forward-incremental") == 0)
  {
    helper_helper_window_copy_command_1_2(&argument_idx, &redraw, &prefix, wp, data, argument);
  }
  *argument_idx_ref = argument_idx;
  *np_ref = np;
  *cancel_ref = cancel;
  *redraw_ref = redraw;
  *prefix_ref = prefix;
}


----------------------------
None
----------------------------
None
----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
static void window_copy_redraw_screen(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  window_copy_redraw_lines(wp, 0, (&data->screen)->grid->sy);
}


----------------------------
static void window_copy_move_mouse(struct mouse_event *m)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int x;
  u_int y;
  wp_idx = cmd_mouse_pane(m, 0, 0);
  if (((&wp[wp_idx]) == 0) || (wp->mode != (&window_copy_mode)))
  {
    return;
  }
  if (cmd_mouse_at(wp, m, &x, &y, 0) != 0)
  {
    return;
  }
  window_copy_update_cursor(wp, x, y);
}


----------------------------
void helper_window_copy_command_2(unsigned int * const ws_idx_ref, u_int * const np_ref, int * const cancel_ref, int * const redraw_ref, int * const scroll_exit_ref, struct window_pane * const wp, struct client * const c, struct session * const s, struct mouse_event * const m, struct window_copy_mode_data * const data, struct screen * const sn, const char * const command, const char * const ws)
{
  unsigned int ws_idx = *ws_idx_ref;
  u_int np = *np_ref;
  int cancel = *cancel_ref;
  int redraw = *redraw_ref;
  int scroll_exit = *scroll_exit_ref;
  if (strcmp(command, "append-selection") == 0)
  {
    if (s != 0)
    {
      window_copy_append_selection(wp, 0);
    }
    window_copy_clear_selection(wp);
    redraw = 1;
  }
  if (strcmp(command, "append-selection-and-cancel") == 0)
  {
    if (s != 0)
    {
      window_copy_append_selection(wp, 0);
    }
    window_copy_clear_selection(wp);
    redraw = 1;
    cancel = 1;
  }
  if (strcmp(command, "back-to-indentation") == 0)
  {
    window_copy_cursor_back_to_indentation(wp);
  }
  if (strcmp(command, "begin-selection") == 0)
  {
    if (m != 0)
    {
      window_copy_start_drag(c, m);
    }
    else
    {
      sn->sel.lineflag = LINE_SEL_NONE;
      window_copy_start_selection(wp);
      redraw = 1;
    }
  }
  if (strcmp(command, "stop-selection") == 0)
  {
    data->cursordrag = CURSORDRAG_NONE;
  }
  if (strcmp(command, "bottom-line") == 0)
  {
    data->cx = 0;
    data->cy = sn->grid->sy - 1;
    window_copy_update_selection(wp, 1);
    redraw = 1;
  }
  if (strcmp(command, "cancel") == 0)
  {
    cancel = 1;
  }
  if (strcmp(command, "clear-selection") == 0)
  {
    window_copy_clear_selection(wp);
    redraw = 1;
  }
  if (strcmp(command, "copy-end-of-line") == 0)
  {
    window_copy_start_selection(wp);
    for (; np > 1; np -= 1)
    {
      window_copy_cursor_down(wp, 0);
    }

    window_copy_cursor_end_of_line(wp);
    redraw = 1;
    if (s != 0)
    {
      window_copy_copy_selection(wp, 0);
      cancel = 1;
    }
  }
  if (strcmp(command, "copy-line") == 0)
  {
    window_copy_cursor_start_of_line(wp);
    window_copy_start_selection(wp);
    for (; np > 1; np -= 1)
    {
      window_copy_cursor_down(wp, 0);
    }

    window_copy_cursor_end_of_line(wp);
    redraw = 1;
    if (s != 0)
    {
      window_copy_copy_selection(wp, 0);
      cancel = 1;
    }
  }
  if (strcmp(command, "copy-selection") == 0)
  {
    if (s != 0)
    {
      window_copy_copy_selection(wp, 0);
    }
    window_copy_clear_selection(wp);
    redraw = 1;
  }
  if (strcmp(command, "copy-selection-and-cancel") == 0)
  {
    if (s != 0)
    {
      window_copy_copy_selection(wp, 0);
    }
    window_copy_clear_selection(wp);
    redraw = 1;
    cancel = 1;
  }
  if (strcmp(command, "cursor-down") == 0)
  {
    for (; np != 0; np -= 1)
    {
      window_copy_cursor_down(wp, 0);
    }

  }
  if (strcmp(command, "cursor-left") == 0)
  {
    for (; np != 0; np -= 1)
    {
      window_copy_cursor_left(wp);
    }

  }
  if (strcmp(command, "cursor-right") == 0)
  {
    for (; np != 0; np -= 1)
    {
      window_copy_cursor_right(wp);
    }

  }
  if (strcmp(command, "cursor-up") == 0)
  {
    for (; np != 0; np -= 1)
    {
      window_copy_cursor_up(wp, 0);
    }

  }
  if (strcmp(command, "end-of-line") == 0)
  {
    window_copy_cursor_end_of_line(wp);
  }
  if ((strcmp(command, "halfpage-down") == 0) || (strcmp(command, "halfpage-down-and-cancel") == 0))
  {
    if (strcmp(command, "halfpage-down-and-cancel") == 0)
    {
      scroll_exit = 1;
    }
    else
      scroll_exit = data->scroll_exit;
    for (; np != 0; np -= 1)
    {
      if (window_copy_pagedown(wp, 1, scroll_exit))
      {
        cancel = 1;
        break;
      }
    }

  }
  if (strcmp(command, "halfpage-up") == 0)
  {
    for (; np != 0; np -= 1)
    {
      window_copy_pageup(wp, 1);
    }

  }
  if (strcmp(command, "history-bottom") == 0)
  {
    data->cx = 0;
    data->cy = sn->grid->sy - 1;
    data->oy = 0;
    window_copy_update_selection(wp, 1);
    redraw = 1;
  }
  if (strcmp(command, "history-top") == 0)
  {
    data->cx = 0;
    data->cy = 0;
    data->oy = data->backing->grid->hsize;
    window_copy_update_selection(wp, 1);
    redraw = 1;
  }
  if (strcmp(command, "jump-again") == 0)
  {
    helper_helper_window_copy_command_2_1(&np, wp, data);
  }
  if (strcmp(command, "jump-reverse") == 0)
  {
    helper_helper_window_copy_command_2_2(&np, wp, data);
  }
  if (strcmp(command, "middle-line") == 0)
  {
    data->cx = 0;
    data->cy = (sn->grid->sy - 1) / 2;
    window_copy_update_selection(wp, 1);
    redraw = 1;
  }
  if (strcmp(command, "next-paragraph") == 0)
  {
    for (; np != 0; np -= 1)
    {
      window_copy_next_paragraph(wp);
    }

  }
  if (strcmp(command, "next-space") == 0)
  {
    for (; np != 0; np -= 1)
    {
      window_copy_cursor_next_word(wp, " ");
    }

  }
  if (strcmp(command, "next-space-end") == 0)
  {
    for (; np != 0; np -= 1)
    {
      window_copy_cursor_next_word_end(wp, " ");
    }

  }
  if (strcmp(command, "next-word") == 0)
  {
    ws_idx = options_get_string(s->options, "word-separators");
    for (; np != 0; np -= 1)
    {
      window_copy_cursor_next_word(wp, ws);
    }

  }
  if (strcmp(command, "next-word-end") == 0)
  {
    ws_idx = options_get_string(s->options, "word-separators");
    for (; np != 0; np -= 1)
    {
      window_copy_cursor_next_word_end(wp, ws);
    }

  }
  if (strcmp(command, "other-end") == 0)
  {
    if ((np % 2) != 0)
    {
      window_copy_other_end(wp);
    }
  }
  if ((strcmp(command, "page-down") == 0) || (strcmp(command, "page-down-and-cancel") == 0))
  {
    if (strcmp(command, "page-down-and-cancel") == 0)
    {
      scroll_exit = 1;
    }
    else
      scroll_exit = data->scroll_exit;
    for (; np != 0; np -= 1)
    {
      if (window_copy_pagedown(wp, 0, scroll_exit))
      {
        cancel = 1;
        break;
      }
    }

  }
  if (strcmp(command, "page-up") == 0)
  {
    for (; np != 0; np -= 1)
    {
      window_copy_pageup(wp, 0);
    }

  }
  if (strcmp(command, "previous-paragraph") == 0)
  {
    for (; np != 0; np -= 1)
    {
      window_copy_previous_paragraph(wp);
    }

  }
  if (strcmp(command, "previous-space") == 0)
  {
    for (; np != 0; np -= 1)
    {
      window_copy_cursor_previous_word(wp, " ");
    }

  }
  if (strcmp(command, "previous-word") == 0)
  {
    ws_idx = options_get_string(s->options, "word-separators");
    for (; np != 0; np -= 1)
    {
      window_copy_cursor_previous_word(wp, ws);
    }

  }
  if (strcmp(command, "rectangle-toggle") == 0)
  {
    sn->sel.lineflag = LINE_SEL_NONE;
    window_copy_rectangle_toggle(wp);
  }
  if ((strcmp(command, "scroll-down") == 0) || (strcmp(command, "scroll-down-and-cancel") == 0))
  {
    if (strcmp(command, "scroll-down-and-cancel") == 0)
    {
      scroll_exit = 1;
    }
    else
      scroll_exit = data->scroll_exit;
    for (; np != 0; np -= 1)
    {
      window_copy_cursor_down(wp, 1);
    }

    if (scroll_exit && (data->oy == 0))
    {
      cancel = 1;
    }
  }
  if (strcmp(command, "scroll-up") == 0)
  {
    for (; np != 0; np -= 1)
    {
      window_copy_cursor_up(wp, 1);
    }

  }
  if (strcmp(command, "search-again") == 0)
  {
    if (data->searchtype == WINDOW_COPY_SEARCHUP)
    {
      for (; np != 0; np -= 1)
      {
        window_copy_search_up(wp);
      }

    }
    else
      if (data->searchtype == WINDOW_COPY_SEARCHDOWN)
    {
      for (; np != 0; np -= 1)
      {
        window_copy_search_down(wp);
      }

    }
  }
  if (strcmp(command, "search-reverse") == 0)
  {
    if (data->searchtype == WINDOW_COPY_SEARCHUP)
    {
      for (; np != 0; np -= 1)
      {
        window_copy_search_down(wp);
      }

    }
    else
      if (data->searchtype == WINDOW_COPY_SEARCHDOWN)
    {
      for (; np != 0; np -= 1)
      {
        window_copy_search_up(wp);
      }

    }
  }
  if (strcmp(command, "select-line") == 0)
  {
    sn->sel.lineflag = LINE_SEL_LEFT_RIGHT;
    data->rectflag = 0;
    window_copy_cursor_start_of_line(wp);
    window_copy_start_selection(wp);
    for (; np > 1; np -= 1)
    {
      window_copy_cursor_down(wp, 0);
    }

    window_copy_cursor_end_of_line(wp);
    redraw = 1;
  }
  if (strcmp(command, "select-word") == 0)
  {
    sn->sel.lineflag = LINE_SEL_LEFT_RIGHT;
    data->rectflag = 0;
    ws_idx = options_get_string(s->options, "word-separators");
    window_copy_cursor_previous_word(wp, ws);
    window_copy_start_selection(wp);
    window_copy_cursor_next_word_end(wp, ws);
    redraw = 1;
  }
  if (strcmp(command, "start-of-line") == 0)
  {
    window_copy_cursor_start_of_line(wp);
  }
  if (strcmp(command, "top-line") == 0)
  {
    data->cx = 0;
    data->cy = 0;
    window_copy_update_selection(wp, 1);
    redraw = 1;
  }
  *ws_idx_ref = ws_idx;
  *np_ref = np;
  *cancel_ref = cancel;
  *redraw_ref = redraw;
  *scroll_exit_ref = scroll_exit;
}


----------------------------
None
----------------------------
static void window_copy_clear_marks(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  free(data->searchmark);
  data->searchmark = 0;
}


----------------------------
None
----------------------------
***/


