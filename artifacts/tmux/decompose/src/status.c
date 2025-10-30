u_int status_line_size(struct session *s)
{
  if (s->statusat == (-1))
  {
    return 0;
  }
  return 1;
}


/*** DEPENDENCIES:
None
----------------------------
***/


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


/*** DEPENDENCIES:
u_int status_line_size(struct session *s)
{
  if (s->statusat == (-1))
  {
    return 0;
  }
  return 1;
}


----------------------------
None
----------------------------
***/


static char *status_prompt_complete_prefix(const char **list, u_int size)
{
  char *out;
  unsigned int out_idx = 0;
  u_int i;
  size_t j;
  out_idx = xstrdup(list[0]);
  for (i = 1; i < size; i += 1)
  {
    j = strlen(list[i]);
    if (j > strlen(out))
    {
      j = strlen(out);
    }
    for (; j > 0; j -= 1)
    {
      if (out[(j - 1) + out_idx] != list[i][j - 1])
      {
        out[(j - 1) + out_idx] = '\0';
      }
    }

  }

  return out;
}


/*** DEPENDENCIES:
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
***/


static int status_prompt_in_list(const char *ws, const struct utf8_data *ud)
{
  if ((ud->size != 1) || (ud->width != 1))
  {
    return 0;
  }
  return strchr(ws, *ud->data) != 0;
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
***/


static int status_prompt_space(const struct utf8_data *ud)
{
  if ((ud->size != 1) || (ud->width != 1))
  {
    return 0;
  }
  return (*ud->data) == ' ';
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
***/


void status_update_saved(struct session *s)
{
  if (!options_get_number(s->options, "status"))
  {
    s->statusat = -1;
  }
  else
    if (options_get_number(s->options, "status-position") == 0)
  {
    s->statusat = 0;
  }
  else
    s->statusat = 1;
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


void status_message_clear(struct client *c)
{
  if (c->message_string == 0)
  {
    return;
  }
  free(c->message_string);
  c->message_string = 0;
  if (c->prompt_string == 0)
  {
    c->tty.flags &= ~(0x1 | 0x2);
  }
  c->flags |= 0x8;
  screen_reinit(&c->status.status);
}


/*** DEPENDENCIES:
void screen_reinit(struct screen *s)
{
  s->cx = 0;
  s->cy = 0;
  s->rupper = 0;
  s->rlower = s->grid->sy - 1;
  s->mode = 0x1 | 0x10;
  screen_reset_tabs(s);
  grid_clear_lines(s->grid, s->grid->hsize, s->grid->sy, 8);
  screen_clear_selection(s);
  screen_free_titles(s);
}


----------------------------
None
----------------------------
***/


void status_prompt_clear(struct client *c)
{
  if (c->prompt_string == 0)
  {
    return;
  }
  if ((c->prompt_freecb != 0) && (c->prompt_data != 0))
  {
    c->prompt_freecb(c->prompt_data);
  }
  free(c->prompt_string);
  c->prompt_string = 0;
  free(c->prompt_buffer);
  c->prompt_buffer = 0;
  c->tty.flags &= ~(0x1 | 0x2);
  c->flags |= 0x8;
  screen_reinit(&c->status.status);
}


/*** DEPENDENCIES:
void screen_reinit(struct screen *s)
{
  s->cx = 0;
  s->cy = 0;
  s->rupper = 0;
  s->rlower = s->grid->sy - 1;
  s->mode = 0x1 | 0x10;
  screen_reset_tabs(s);
  grid_clear_lines(s->grid, s->grid->hsize, s->grid->sy, 8);
  screen_clear_selection(s);
  screen_free_titles(s);
}


----------------------------
None
----------------------------
***/


void status_message_callback(int fd, short event, void *data)
{
  struct client *c = data;
  status_message_clear(c);
}


/*** DEPENDENCIES:
void status_message_clear(struct client *c)
{
  if (c->message_string == 0)
  {
    return;
  }
  free(c->message_string);
  c->message_string = 0;
  if (c->prompt_string == 0)
  {
    c->tty.flags &= ~(0x1 | 0x2);
  }
  c->flags |= 0x8;
  screen_reinit(&c->status.status);
}


----------------------------
None
----------------------------
***/


static const char *status_prompt_up_history(u_int *idx)
{
  if ((status_prompt_hsize == 0) || ((*idx) == status_prompt_hsize))
  {
    return 0;
  }
  *idx += 1;
  return status_prompt_hlist[status_prompt_hsize - (*idx)];
}


/*** DEPENDENCIES:
static char **status_prompt_hlist
----------------------------
static u_int status_prompt_hsize
----------------------------
***/


static const char *status_prompt_down_history(u_int *idx)
{
  if ((status_prompt_hsize == 0) || ((*idx) == 0))
  {
    return "";
  }
  *idx -= 1;
  if ((*idx) == 0)
  {
    return "";
  }
  return status_prompt_hlist[status_prompt_hsize - (*idx)];
}


/*** DEPENDENCIES:
static char **status_prompt_hlist
----------------------------
static u_int status_prompt_hsize
----------------------------
***/


static int status_prompt_translate_key(struct client *c, key_code key, key_code *new_key)
{
  if (c->prompt_mode == PROMPT_ENTRY)
  {
    switch (key)
    {
      case '\003':

      case '\010':

      case '\011':

      case '\025':

      case '\027':

      case '\n':

      case '\r':

      case KEYC_BSPACE:

      case KEYC_DC:

      case KEYC_DOWN:

      case KEYC_END:

      case KEYC_HOME:

      case KEYC_LEFT:

      case KEYC_RIGHT:

      case KEYC_UP:
      {
        *new_key = key;
        return 1;
      }

      case '\033':
      {
        c->prompt_mode = PROMPT_COMMAND;
        c->flags |= 0x10;
        return 0;
      }

    }

    *new_key = key;
    return 2;
  }
  switch (key)
  {
    case 'A':

    case 'I':

    case 'C':

    case 's':

    case 'a':
    {
      c->prompt_mode = PROMPT_ENTRY;
      c->flags |= 0x10;
      break;
    }

    case 'S':
    {
      c->prompt_mode = PROMPT_ENTRY;
      c->flags |= 0x10;
      *new_key = '\025';
      return 1;
    }

    case 'i':

    case '\033':
    {
      c->prompt_mode = PROMPT_ENTRY;
      c->flags |= 0x10;
      return 0;
    }

  }

  switch (key)
  {
    case 'A':

    case '$':
    {
      *new_key = KEYC_END;
      return 1;
    }

    case 'I':

    case '0':

    case '^':
    {
      *new_key = KEYC_HOME;
      return 1;
    }

    case 'C':

    case 'D':
    {
      *new_key = '\013';
      return 1;
    }

    case KEYC_BSPACE:

    case 'X':
    {
      *new_key = KEYC_BSPACE;
      return 1;
    }

    case 'b':

    case 'B':
    {
      *new_key = 'b' | 0x200000000000ULL;
      return 1;
    }

    case 'd':
    {
      *new_key = '\025';
      return 1;
    }

    case 'e':

    case 'E':

    case 'w':

    case 'W':
    {
      *new_key = 'f' | 0x200000000000ULL;
      return 1;
    }

    case 'p':
    {
      *new_key = '\031';
      return 1;
    }

    case 's':

    case KEYC_DC:

    case 'x':
    {
      *new_key = KEYC_DC;
      return 1;
    }

    case KEYC_DOWN:

    case 'j':
    {
      *new_key = KEYC_DOWN;
      return 1;
    }

    case KEYC_LEFT:

    case 'h':
    {
      *new_key = KEYC_LEFT;
      return 1;
    }

    case 'a':

    case KEYC_RIGHT:

    case 'l':
    {
      *new_key = KEYC_RIGHT;
      return 1;
    }

    case KEYC_UP:

    case 'k':
    {
      *new_key = KEYC_UP;
      return 1;
    }

    case '\010':

    case '\003':

    case '\n':

    case '\r':
    {
      return 1;
    }

  }

  return 0;
}


/*** DEPENDENCIES:
typedef unsigned long long key_code
----------------------------
None
----------------------------
***/


// hint:  ['width_ref is a mutable refrence to u_int']
void helper_status_prompt_redraw_1(u_int * const width_ref, struct client * const c, struct screen_write_ctx ctx, u_int i, u_int offset, u_int pwidth, struct grid_cell gc, struct grid_cell cursorgc)
{
  u_int width = *width_ref;
  if (width < offset)
  {
    width += c->prompt_buffer[i].width;
    continue;
  }
  if (width >= (offset + pwidth))
  {
    break;
  }
  width += c->prompt_buffer[i].width;
  if (width > (offset + pwidth))
  {
    break;
  }
  if (i != c->prompt_index)
  {
    utf8_copy(&gc.data, &c->prompt_buffer[i]);
    screen_write_cell(&ctx, &gc);
  }
  else
  {
    utf8_copy(&cursorgc.data, &c->prompt_buffer[i]);
    screen_write_cell(&ctx, &cursorgc);
  }
  *width_ref = width;
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
void screen_write_stop(struct screen_write_ctx *ctx)
{
  screen_write_collect_end(ctx);
  screen_write_collect_flush(ctx, 0);
  log_debug("%s: %u cells (%u written, %u skipped)", __func__, ctx->cells, ctx->written, ctx->skipped);
  free(ctx->item);
  free(ctx->list);
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
void screen_write_putc(struct screen_write_ctx *ctx, const struct grid_cell *gcp, u_char ch)
{
  struct grid_cell gc;
  memcpy(&gc, gcp, sizeof(gc));
  utf8_set(&gc.data, ch);
  screen_write_cell(ctx, &gc);
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
u_int utf8_strwidth(const struct utf8_data *s, ssize_t n)
{
  ssize_t i;
  u_int width;
  width = 0;
  for (i = 0; s[i].size != 0; i += 1)
  {
    if ((n != (-1)) && (n == i))
    {
      break;
    }
    width += s[i].width;
  }

  return width;
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
void helper_status_prompt_redraw_1(u_int * const width_ref, struct client * const c, struct screen_write_ctx ctx, u_int i, u_int offset, u_int pwidth, struct grid_cell gc, struct grid_cell cursorgc)
{
  u_int width = *width_ref;
  if (width < offset)
  {
    width += c->prompt_buffer[i].width;
    continue;
  }
  if (width >= (offset + pwidth))
  {
    break;
  }
  width += c->prompt_buffer[i].width;
  if (width > (offset + pwidth))
  {
    break;
  }
  if (i != c->prompt_index)
  {
    utf8_copy(&gc.data, &c->prompt_buffer[i]);
    screen_write_cell(&ctx, &gc);
  }
  else
  {
    utf8_copy(&cursorgc.data, &c->prompt_buffer[i]);
    screen_write_cell(&ctx, &cursorgc);
  }
  *width_ref = width;
}


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


/*** DEPENDENCIES:
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
None
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
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
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
u_int status_line_size(struct session *s)
{
  if (s->statusat == (-1))
  {
    return 0;
  }
  return 1;
}


----------------------------
void screen_write_putc(struct screen_write_ctx *ctx, const struct grid_cell *gcp, u_char ch)
{
  struct grid_cell gc;
  memcpy(&gc, gcp, sizeof(gc));
  utf8_set(&gc.data, ch);
  screen_write_cell(ctx, &gc);
}


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


static char *status_replace(struct client *c, struct winlink *wl, const char *fmt, time_t t)
{
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  char *expanded;
  unsigned int expanded_idx = 0;
  u_int tag;
  if (fmt == 0)
  {
    return xstrdup("");
  }
  if (wl != 0)
  {
    tag = 0x40000000U | wl->window->id;
  }
  else
    tag = 0;
  if (c->flags & 0x80000)
  {
    ft_idx = format_create(c, 0, tag, 0x1 | 0x2);
  }
  else
    ft_idx = format_create(c, 0, tag, 0x1);
  format_defaults(ft, c, 0, wl, 0);
  expanded_idx = format_expand_time(ft, fmt, t);
  format_free(ft);
  return expanded;
}


/*** DEPENDENCIES:
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
char *format_expand_time(struct format_tree *ft, const char *fmt, time_t t)
{
  struct tm *tm;
  unsigned int tm_idx = 0;
  char s[2048];
  if ((fmt == 0) || ((*fmt) == '\0'))
  {
    return xstrdup("");
  }
  tm_idx = localtime(&t);
  if (strftime(s, sizeof(s), fmt, tm) == 0)
  {
    return xstrdup("");
  }
  return format_expand(ft, s);
}


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
None
----------------------------
***/


static char *status_redraw_get_left(struct client *c, time_t t, struct grid_cell *gc, size_t *size)
{
  struct session *s = c->session;
  const char *template;
  unsigned int template_idx = 0;
  char *left;
  unsigned int left_idx = 0;
  size_t leftlen;
  style_apply_update(gc, s->options, "status-left-style");
  template_idx = options_get_string(s->options, "status-left");
  left_idx = status_replace(c, 0, template, t);
  *size = options_get_number(s->options, "status-left-length");
  leftlen = screen_write_cstrlen("%s", left);
  if (leftlen < (*size))
  {
    *size = leftlen;
  }
  return left;
}


/*** DEPENDENCIES:
static char *status_replace(struct client *c, struct winlink *wl, const char *fmt, time_t t)
{
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  char *expanded;
  unsigned int expanded_idx = 0;
  u_int tag;
  if (fmt == 0)
  {
    return xstrdup("");
  }
  if (wl != 0)
  {
    tag = 0x40000000U | wl->window->id;
  }
  else
    tag = 0;
  if (c->flags & 0x80000)
  {
    ft_idx = format_create(c, 0, tag, 0x1 | 0x2);
  }
  else
    ft_idx = format_create(c, 0, tag, 0x1);
  format_defaults(ft, c, 0, wl, 0);
  expanded_idx = format_expand_time(ft, fmt, t);
  format_free(ft);
  return expanded;
}


----------------------------
void style_apply_update(struct grid_cell *gc, struct options *oo, const char *name)
{
  const struct grid_cell *gcp;
  unsigned int gcp_idx = 0;
  gcp_idx = options_get_style(oo, name);
  if (gcp->fg != 8)
  {
    gc->fg = gcp->fg;
  }
  if (gcp->bg != 8)
  {
    gc->bg = gcp->bg;
  }
  if (gcp->attr != 0)
  {
    gc->attr |= gcp->attr;
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


static char *status_redraw_get_right(struct client *c, time_t t, struct grid_cell *gc, size_t *size)
{
  struct session *s = c->session;
  const char *template;
  unsigned int template_idx = 0;
  char *right;
  unsigned int right_idx = 0;
  size_t rightlen;
  style_apply_update(gc, s->options, "status-right-style");
  template_idx = options_get_string(s->options, "status-right");
  right_idx = status_replace(c, 0, template, t);
  *size = options_get_number(s->options, "status-right-length");
  rightlen = screen_write_cstrlen("%s", right);
  if (rightlen < (*size))
  {
    *size = rightlen;
  }
  return right;
}


/*** DEPENDENCIES:
static char *status_replace(struct client *c, struct winlink *wl, const char *fmt, time_t t)
{
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  char *expanded;
  unsigned int expanded_idx = 0;
  u_int tag;
  if (fmt == 0)
  {
    return xstrdup("");
  }
  if (wl != 0)
  {
    tag = 0x40000000U | wl->window->id;
  }
  else
    tag = 0;
  if (c->flags & 0x80000)
  {
    ft_idx = format_create(c, 0, tag, 0x1 | 0x2);
  }
  else
    ft_idx = format_create(c, 0, tag, 0x1);
  format_defaults(ft, c, 0, wl, 0);
  expanded_idx = format_expand_time(ft, fmt, t);
  format_free(ft);
  return expanded;
}


----------------------------
void style_apply_update(struct grid_cell *gc, struct options *oo, const char *name)
{
  const struct grid_cell *gcp;
  unsigned int gcp_idx = 0;
  gcp_idx = options_get_style(oo, name);
  if (gcp->fg != 8)
  {
    gc->fg = gcp->fg;
  }
  if (gcp->bg != 8)
  {
    gc->bg = gcp->bg;
  }
  if (gcp->attr != 0)
  {
    gc->attr |= gcp->attr;
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


static char *status_print(struct client *c, struct winlink *wl, time_t t, struct grid_cell *gc)
{
  struct options *oo = wl->window->options;
  struct session *s = c->session;
  const char *fmt;
  unsigned int fmt_idx = 0;
  char *text;
  unsigned int text_idx = 0;
  style_apply_update(gc, oo, "window-status-style");
  fmt_idx = options_get_string(oo, "window-status-format");
  if (wl == s->curw)
  {
    style_apply_update(gc, oo, "window-status-current-style");
    fmt_idx = options_get_string(oo, "window-status-current-format");
  }
  if (wl == (&s->lastw)->tqh_first)
  {
    style_apply_update(gc, oo, "window-status-last-style");
  }
  if (wl->flags & 0x1)
  {
    style_apply_update(gc, oo, "window-status-bell-style");
  }
  else
    if (wl->flags & (0x2 | 0x4))
  {
    style_apply_update(gc, oo, "window-status-activity-style");
  }
  text_idx = status_replace(c, wl, fmt, t);
  return text;
}


/*** DEPENDENCIES:
static char *status_replace(struct client *c, struct winlink *wl, const char *fmt, time_t t)
{
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  char *expanded;
  unsigned int expanded_idx = 0;
  u_int tag;
  if (fmt == 0)
  {
    return xstrdup("");
  }
  if (wl != 0)
  {
    tag = 0x40000000U | wl->window->id;
  }
  else
    tag = 0;
  if (c->flags & 0x80000)
  {
    ft_idx = format_create(c, 0, tag, 0x1 | 0x2);
  }
  else
    ft_idx = format_create(c, 0, tag, 0x1);
  format_defaults(ft, c, 0, wl, 0);
  expanded_idx = format_expand_time(ft, fmt, t);
  format_free(ft);
  return expanded;
}


----------------------------
None
----------------------------
void style_apply_update(struct grid_cell *gc, struct options *oo, const char *name)
{
  const struct grid_cell *gcp;
  unsigned int gcp_idx = 0;
  gcp_idx = options_get_style(oo, name);
  if (gcp->fg != 8)
  {
    gc->fg = gcp->fg;
  }
  if (gcp->bg != 8)
  {
    gc->bg = gcp->bg;
  }
  if (gcp->attr != 0)
  {
    gc->attr |= gcp->attr;
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
None
----------------------------
***/


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


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
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
static char *status_redraw_get_left(struct client *c, time_t t, struct grid_cell *gc, size_t *size)
{
  struct session *s = c->session;
  const char *template;
  unsigned int template_idx = 0;
  char *left;
  unsigned int left_idx = 0;
  size_t leftlen;
  style_apply_update(gc, s->options, "status-left-style");
  template_idx = options_get_string(s->options, "status-left");
  left_idx = status_replace(c, 0, template, t);
  *size = options_get_number(s->options, "status-left-length");
  leftlen = screen_write_cstrlen("%s", left);
  if (leftlen < (*size))
  {
    *size = leftlen;
  }
  return left;
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
static char *status_redraw_get_right(struct client *c, time_t t, struct grid_cell *gc, size_t *size)
{
  struct session *s = c->session;
  const char *template;
  unsigned int template_idx = 0;
  char *right;
  unsigned int right_idx = 0;
  size_t rightlen;
  style_apply_update(gc, s->options, "status-right-style");
  template_idx = options_get_string(s->options, "status-right");
  right_idx = status_replace(c, 0, template, t);
  *size = options_get_number(s->options, "status-right-length");
  rightlen = screen_write_cstrlen("%s", right);
  if (rightlen < (*size))
  {
    *size = rightlen;
  }
  return right;
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
void screen_write_putc(struct screen_write_ctx *ctx, const struct grid_cell *gcp, u_char ch)
{
  struct grid_cell gc;
  memcpy(&gc, gcp, sizeof(gc));
  utf8_set(&gc.data, ch);
  screen_write_cell(ctx, &gc);
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
static char *status_print(struct client *c, struct winlink *wl, time_t t, struct grid_cell *gc)
{
  struct options *oo = wl->window->options;
  struct session *s = c->session;
  const char *fmt;
  unsigned int fmt_idx = 0;
  char *text;
  unsigned int text_idx = 0;
  style_apply_update(gc, oo, "window-status-style");
  fmt_idx = options_get_string(oo, "window-status-format");
  if (wl == s->curw)
  {
    style_apply_update(gc, oo, "window-status-current-style");
    fmt_idx = options_get_string(oo, "window-status-current-format");
  }
  if (wl == (&s->lastw)->tqh_first)
  {
    style_apply_update(gc, oo, "window-status-last-style");
  }
  if (wl->flags & 0x1)
  {
    style_apply_update(gc, oo, "window-status-bell-style");
  }
  else
    if (wl->flags & (0x2 | 0x4))
  {
    style_apply_update(gc, oo, "window-status-activity-style");
  }
  text_idx = status_replace(c, wl, fmt, t);
  return text;
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
None
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


static void status_timer_callback(int fd, short events, void *arg)
{
  struct client *c = arg;
  struct session *s = c->session;
  struct timeval tv;
  evtimer_del(&c->status.timer);
  if (s == 0)
  {
    return;
  }
  if ((c->message_string == 0) && (c->prompt_string == 0))
  {
    c->flags |= 0x10;
  }
  timerclear(&tv);
  tv.tv_sec = options_get_number(s->options, "status-interval");
  if (tv.tv_sec != 0)
  {
    evtimer_add(&c->status.timer, &tv);
  }
  log_debug("client %p, status interval %d", c, (int) tv.tv_sec);
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


/*** DEPENDENCIES:
static void status_timer_callback(int fd, short events, void *arg)
{
  struct client *c = arg;
  struct session *s = c->session;
  struct timeval tv;
  evtimer_del(&c->status.timer);
  if (s == 0)
  {
    return;
  }
  if ((c->message_string == 0) && (c->prompt_string == 0))
  {
    c->flags |= 0x10;
  }
  timerclear(&tv);
  tv.tv_sec = options_get_number(s->options, "status-interval");
  if (tv.tv_sec != 0)
  {
    evtimer_add(&c->status.timer, &tv);
  }
  log_debug("client %p, status interval %d", c, (int) tv.tv_sec);
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
***/


static char *status_prompt_find_history_file(void)
{
  const char *home;
  unsigned int home_idx = 0;
  const char *history_file;
  unsigned int history_file_idx = 0;
  char *path;
  history_file_idx = options_get_string(global_options, "history-file");
  if (history_file[history_file_idx] == '\0')
  {
    return 0;
  }
  if (history_file[history_file_idx] == '/')
  {
    return xstrdup(history_file);
  }
  if ((history_file[0 + history_file_idx] != '~') || (history_file[1 + history_file_idx] != '/'))
  {
    return 0;
  }
  if ((home_idx = find_home()) == 0)
  {
    return 0;
  }
  xasprintf(&path, "%s%s", home, (&history_file[history_file_idx]) + 1);
  return path;
}


/*** DEPENDENCIES:
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
const char *find_home(void)
{
  struct passwd *pw;
  unsigned int pw_idx = 0;
  static const char *home;
  unsigned int home_idx = 0;
  if ((&home[home_idx]) != 0)
  {
    return home;
  }
  home_idx = getenv("HOME");
  if (((&home[home_idx]) == 0) || (home[home_idx] == '\0'))
  {
    pw_idx = getpwuid(getuid());
    if ((&pw[pw_idx]) != 0)
    {
      home_idx = pw->pw_dir;
    }
    else
      home_idx = 0;
  }
  return home;
}


----------------------------
***/


void status_prompt_save_history(void)
{
  FILE *f;
  unsigned int f_idx = 0;
  u_int i;
  char *history_file;
  unsigned int history_file_idx = 0;
  if ((history_file_idx = status_prompt_find_history_file()) == 0)
  {
    return;
  }
  log_debug("saving history to %s", history_file);
  f_idx = fopen(history_file, "w");
  if ((&f[f_idx]) == 0)
  {
    log_debug("%s: %s", history_file, strerror(errno));
    free(history_file);
    return;
  }
  free(history_file);
  for (i = 0; i < status_prompt_hsize; i += 1)
  {
    fputs(status_prompt_hlist[i], f);
    fputc('\n', f);
  }

  fclose(f);
}


/*** DEPENDENCIES:
static u_int status_prompt_hsize
----------------------------
static char **status_prompt_hlist
----------------------------
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
static char *status_prompt_find_history_file(void)
{
  const char *home;
  unsigned int home_idx = 0;
  const char *history_file;
  unsigned int history_file_idx = 0;
  char *path;
  history_file_idx = options_get_string(global_options, "history-file");
  if (history_file[history_file_idx] == '\0')
  {
    return 0;
  }
  if (history_file[history_file_idx] == '/')
  {
    return xstrdup(history_file);
  }
  if ((history_file[0 + history_file_idx] != '~') || (history_file[1 + history_file_idx] != '/'))
  {
    return 0;
  }
  if ((home_idx = find_home()) == 0)
  {
    return 0;
  }
  xasprintf(&path, "%s%s", home, (&history_file[history_file_idx]) + 1);
  return path;
}


----------------------------
***/


static void status_prompt_add_history(const char *line)
{
  size_t size;
  if ((status_prompt_hsize > 0) && (strcmp(status_prompt_hlist[status_prompt_hsize - 1], line) == 0))
  {
    return;
  }
  if (status_prompt_hsize == 100)
  {
    free(status_prompt_hlist[0]);
    size = (100 - 1) * (sizeof(*status_prompt_hlist));
    memmove(&status_prompt_hlist[0], &status_prompt_hlist[1], size);
    status_prompt_hlist[status_prompt_hsize - 1] = xstrdup(line);
    return;
  }
  status_prompt_hlist = xreallocarray(status_prompt_hlist, status_prompt_hsize + 1, sizeof(*status_prompt_hlist));
  status_prompt_hlist[status_prompt_hsize] = xstrdup(line);
  status_prompt_hsize += 1;
}


/*** DEPENDENCIES:
void *xreallocarray(void *ptr, size_t nmemb, size_t size)
{
  void *new_ptr;
  unsigned int new_ptr_idx = 0;
  if ((nmemb == 0) || (size == 0))
  {
    fatalx("xreallocarray: zero size");
  }
  new_ptr_idx = reallocarray(ptr, nmemb, size);
  if ((&new_ptr[new_ptr_idx]) == 0)
  {
    fatalx("xreallocarray: allocating %zu * %zu bytes: %s", nmemb, size, strerror(errno));
  }
  return new_ptr;
}


----------------------------
static char **status_prompt_hlist
----------------------------
static u_int status_prompt_hsize
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
***/


// hint:  ['line_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int', 'length_ref is a mutable refrence to size_t']
void helper_status_prompt_load_history_1(unsigned int * const line_idx_ref, unsigned int * const tmp_idx_ref, size_t * const length_ref, FILE * const f, char * const line, char * const tmp)
{
  unsigned int line_idx = *line_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  size_t length = *length_ref;
  if ((line_idx = fgetln(f, &length)) == 0)
  {
    break;
  }
  if (length > 0)
  {
    if (line[(length - 1) + line_idx] == '\n')
    {
      line[(length - 1) + line_idx] = '\0';
      status_prompt_add_history(line);
    }
    else
    {
      tmp_idx = xmalloc(length + 1);
      memcpy(tmp, line, length);
      tmp[length + tmp_idx] = '\0';
      status_prompt_add_history(tmp);
      free(tmp);
    }
  }
  *line_idx_ref = line_idx;
  *tmp_idx_ref = tmp_idx;
  *length_ref = length;
}


/*** DEPENDENCIES:
char *fgetln(FILE *fp, size_t *len)
{
  static char *buf = 0;
  unsigned int buf_idx = 0;
  static size_t bufsz = 0;
  size_t r = 0;
  char *p;
  unsigned int p_idx = 0;
  int c;
  int e;
  if ((!fp) || (!len))
  {
    errno = EINVAL;
    return 0;
  }
  if (!(&buf[buf_idx]))
  {
    if (!(buf_idx = calloc(1, 1024)))
    {
      return 0;
    }
    bufsz = 1024;
  }
  while ((c = getc(fp)) != EOF)
  {
    buf[r + buf_idx] = c;
    r += 1;
    if (r == bufsz)
    {
      if (!(p_idx = reallocarray(buf, 2, bufsz)))
      {
        e = errno;
        free(buf);
        errno = e;
        buf_idx = 0, bufsz = 0;
        return 0;
      }
      buf_idx = &p[p_idx], bufsz = 2 * bufsz;
    }
    if (c == '\n')
    {
      break;
    }
  }

  return (*len = r) ? (buf) : (0);
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
static void status_prompt_add_history(const char *line)
{
  size_t size;
  if ((status_prompt_hsize > 0) && (strcmp(status_prompt_hlist[status_prompt_hsize - 1], line) == 0))
  {
    return;
  }
  if (status_prompt_hsize == 100)
  {
    free(status_prompt_hlist[0]);
    size = (100 - 1) * (sizeof(*status_prompt_hlist));
    memmove(&status_prompt_hlist[0], &status_prompt_hlist[1], size);
    status_prompt_hlist[status_prompt_hsize - 1] = xstrdup(line);
    return;
  }
  status_prompt_hlist = xreallocarray(status_prompt_hlist, status_prompt_hsize + 1, sizeof(*status_prompt_hlist));
  status_prompt_hlist[status_prompt_hsize] = xstrdup(line);
  status_prompt_hsize += 1;
}


----------------------------
***/


void status_prompt_load_history(void)
{
  FILE *f;
  unsigned int f_idx = 0;
  char *history_file;
  unsigned int history_file_idx = 0;
  char *line;
  unsigned int line_idx = 0;
  char *tmp;
  unsigned int tmp_idx = 0;
  size_t length;
  if ((history_file_idx = status_prompt_find_history_file()) == 0)
  {
    return;
  }
  log_debug("loading history from %s", history_file);
  f_idx = fopen(history_file, "r");
  if ((&f[f_idx]) == 0)
  {
    log_debug("%s: %s", history_file, strerror(errno));
    free(history_file);
    return;
  }
  free(history_file);
  for (;;)
  {
    helper_status_prompt_load_history_1(&line_idx, &tmp_idx, &length, f, line, tmp);
  }

  fclose(f);
}


/*** DEPENDENCIES:
void helper_status_prompt_load_history_1(unsigned int * const line_idx_ref, unsigned int * const tmp_idx_ref, size_t * const length_ref, FILE * const f, char * const line, char * const tmp)
{
  unsigned int line_idx = *line_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  size_t length = *length_ref;
  if ((line_idx = fgetln(f, &length)) == 0)
  {
    break;
  }
  if (length > 0)
  {
    if (line[(length - 1) + line_idx] == '\n')
    {
      line[(length - 1) + line_idx] = '\0';
      status_prompt_add_history(line);
    }
    else
    {
      tmp_idx = xmalloc(length + 1);
      memcpy(tmp, line, length);
      tmp[length + tmp_idx] = '\0';
      status_prompt_add_history(tmp);
      free(tmp);
    }
  }
  *line_idx_ref = line_idx;
  *tmp_idx_ref = tmp_idx;
  *length_ref = length;
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
static char *status_prompt_find_history_file(void)
{
  const char *home;
  unsigned int home_idx = 0;
  const char *history_file;
  unsigned int history_file_idx = 0;
  char *path;
  history_file_idx = options_get_string(global_options, "history-file");
  if (history_file[history_file_idx] == '\0')
  {
    return 0;
  }
  if (history_file[history_file_idx] == '/')
  {
    return xstrdup(history_file);
  }
  if ((history_file[0 + history_file_idx] != '~') || (history_file[1 + history_file_idx] != '/'))
  {
    return 0;
  }
  if ((home_idx = find_home()) == 0)
  {
    return 0;
  }
  xasprintf(&path, "%s%s", home, (&history_file[history_file_idx]) + 1);
  return path;
}


----------------------------
***/


struct window *status_get_window_at(struct client *c, u_int x)
{
  struct session *s = c->session;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct options *oo;
  unsigned int oo_idx = 0;
  const char *sep;
  unsigned int sep_idx = 0;
  size_t seplen;
  x += c->wlmouse;
  for (wl_idx = winlinks_RB_MINMAX(&s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    oo_idx = wl->window->options;
    sep_idx = options_get_string(oo, "window-status-separator");
    seplen = screen_write_cstrlen("%s", sep);
    if (x < wl->status_width)
    {
      return wl->window;
    }
    x -= wl->status_width + seplen;
  }

  return 0;
}


/*** DEPENDENCIES:
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


// hint:  ['ws_idx_ref is a mutable refrence to unsigned int', 'idx_ref is a mutable refrence to size_t']
void helper_status_prompt_key_1(unsigned int * const ws_idx_ref, size_t * const idx_ref, struct client * const c, struct options * const oo, const char * const ws)
{
  unsigned int ws_idx = *ws_idx_ref;
  size_t idx = *idx_ref;
  ws_idx = options_get_string(oo, "word-separators");
  while (c->prompt_index != 0)
  {
    idx = --c->prompt_index;
    if (!status_prompt_in_list(ws, &c->prompt_buffer[idx]))
    {
      break;
    }
  }

  while (c->prompt_index != 0)
  {
    idx = --c->prompt_index;
    if (status_prompt_in_list(ws, &c->prompt_buffer[idx]))
    {
      c->prompt_index += 1;
      break;
    }
  }

  goto changed;
  *ws_idx_ref = ws_idx;
  *idx_ref = idx;
}


/*** DEPENDENCIES:
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
static int status_prompt_in_list(const char *ws, const struct utf8_data *ud)
{
  if ((ud->size != 1) || (ud->width != 1))
  {
    return 0;
  }
  return strchr(ws, *ud->data) != 0;
}


----------------------------
None
----------------------------
***/


// hint:  ['pb_idx_ref is a mutable refrence to unsigned int', 'bufdata_idx_ref is a mutable refrence to unsigned int', 'ch_ref is a mutable refrence to u_char', 'size_ref is a mutable refrence to size_t', 'n_ref is a mutable refrence to size_t', 'idx_ref is a mutable refrence to size_t', 'ud_idx_ref is a mutable refrence to unsigned int']
void helper_status_prompt_key_4(unsigned int * const pb_idx_ref, unsigned int * const bufdata_idx_ref, u_char * const ch_ref, size_t * const size_ref, size_t * const n_ref, size_t * const idx_ref, unsigned int * const ud_idx_ref, struct client * const c, struct paste_buffer * const pb, const char * const bufdata, size_t bufsize, struct utf8_data * const ud)
{
  unsigned int pb_idx = *pb_idx_ref;
  unsigned int bufdata_idx = *bufdata_idx_ref;
  u_char ch = *ch_ref;
  size_t size = *size_ref;
  size_t n = *n_ref;
  size_t idx = *idx_ref;
  unsigned int ud_idx = *ud_idx_ref;
  if ((pb_idx = paste_get_top(0)) == 0)
  {
    break;
  }
  bufdata_idx = paste_buffer_data(pb, &bufsize);
  for (n = 0; n < bufsize; n += 1)
  {
    ch = (u_char) bufdata[n + bufdata_idx];
    if ((ch < 32) || (ch >= 127))
    {
      break;
    }
  }

  c->prompt_buffer = xreallocarray(c->prompt_buffer, (size + n) + 1, sizeof(*c->prompt_buffer));
  if (c->prompt_index == size)
  {
    for (idx = 0; idx < n; idx += 1)
    {
      ud_idx = &c->prompt_buffer[c->prompt_index + idx];
      utf8_set(ud, bufdata[idx + bufdata_idx]);
    }

    c->prompt_index += n;
    c->prompt_buffer[c->prompt_index].size = 0;
  }
  else
  {
    memmove((c->prompt_buffer + c->prompt_index) + n, c->prompt_buffer + c->prompt_index, ((size + 1) - c->prompt_index) * (sizeof(*c->prompt_buffer)));
    for (idx = 0; idx < n; idx += 1)
    {
      ud_idx = &c->prompt_buffer[c->prompt_index + idx];
      utf8_set(ud, bufdata[idx + bufdata_idx]);
    }

    c->prompt_index += n;
  }
  goto changed;
  *pb_idx_ref = pb_idx;
  *bufdata_idx_ref = bufdata_idx;
  *ch_ref = ch;
  *size_ref = size;
  *n_ref = n;
  *idx_ref = idx;
  *ud_idx_ref = ud_idx;
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
void utf8_set(struct utf8_data *ud, u_char ch)
{
  static const struct utf8_data empty = {{0}, 1, 1, 1};
  memcpy(ud, &empty, sizeof(*ud));
  *ud->data = ch;
}


----------------------------
void *xreallocarray(void *ptr, size_t nmemb, size_t size)
{
  void *new_ptr;
  unsigned int new_ptr_idx = 0;
  if ((nmemb == 0) || (size == 0))
  {
    fatalx("xreallocarray: zero size");
  }
  new_ptr_idx = reallocarray(ptr, nmemb, size);
  if ((&new_ptr[new_ptr_idx]) == 0)
  {
    fatalx("xreallocarray: allocating %zu * %zu bytes: %s", nmemb, size, strerror(errno));
  }
  return new_ptr;
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
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
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
***/


// hint:  ['ws_idx_ref is a mutable refrence to unsigned int', 'idx_ref is a mutable refrence to size_t']
void helper_status_prompt_key_3(unsigned int * const ws_idx_ref, size_t * const idx_ref, struct client * const c, struct options * const oo, const char * const ws, size_t size)
{
  unsigned int ws_idx = *ws_idx_ref;
  size_t idx = *idx_ref;
  ws_idx = options_get_string(oo, "word-separators");
  idx = c->prompt_index;
  while (idx != 0)
  {
    idx -= 1;
    if (!status_prompt_in_list(ws, &c->prompt_buffer[idx]))
    {
      break;
    }
  }

  while (idx != 0)
  {
    idx -= 1;
    if (status_prompt_in_list(ws, &c->prompt_buffer[idx]))
    {
      idx += 1;
      break;
    }
  }

  memmove(c->prompt_buffer + idx, c->prompt_buffer + c->prompt_index, ((size + 1) - c->prompt_index) * (sizeof(*c->prompt_buffer)));
  memset((c->prompt_buffer + size) - (c->prompt_index - idx), '\0', (c->prompt_index - idx) * (sizeof(*c->prompt_buffer)));
  c->prompt_index = idx;
  goto changed;
  *ws_idx_ref = ws_idx;
  *idx_ref = idx;
}


/*** DEPENDENCIES:
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
static int status_prompt_in_list(const char *ws, const struct utf8_data *ud)
{
  if ((ud->size != 1) || (ud->width != 1))
  {
    return 0;
  }
  return strchr(ws, *ud->data) != 0;
}


----------------------------
None
----------------------------
***/


// hint:  ['ws_idx_ref is a mutable refrence to unsigned int', 'idx_ref is a mutable refrence to size_t']
void helper_status_prompt_key_2(unsigned int * const ws_idx_ref, size_t * const idx_ref, struct client * const c, struct options * const oo, const char * const ws, size_t size)
{
  unsigned int ws_idx = *ws_idx_ref;
  size_t idx = *idx_ref;
  ws_idx = options_get_string(oo, "word-separators");
  while (c->prompt_index != size)
  {
    idx = ++c->prompt_index;
    if (!status_prompt_in_list(ws, &c->prompt_buffer[idx]))
    {
      break;
    }
  }

  while (c->prompt_index != size)
  {
    idx = ++c->prompt_index;
    if (status_prompt_in_list(ws, &c->prompt_buffer[idx]))
    {
      break;
    }
  }

  if ((options_get_number(oo, "status-keys") == 1) && (c->prompt_index != 0))
  {
    c->prompt_index -= 1;
  }
  goto changed;
  *ws_idx_ref = ws_idx;
  *idx_ref = idx;
}


/*** DEPENDENCIES:
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
static int status_prompt_in_list(const char *ws, const struct utf8_data *ud)
{
  if ((ud->size != 1) || (ud->width != 1))
  {
    return 0;
  }
  return strchr(ws, *ud->data) != 0;
}


----------------------------
None
----------------------------
***/


static const char **status_prompt_complete_list(u_int *size, const char *s)
{
  const char **list = 0;
  unsigned int list_idx = 0;
  const char **layout;
  unsigned int layout_idx = 0;
  const struct cmd_entry **cmdent;
  unsigned int cmdent_idx = 0;
  const struct options_table_entry *oe;
  unsigned int oe_idx = 0;
  const char *layouts[] = {"even-horizontal", "even-vertical", "main-horizontal", "main-vertical", "tiled", 0};
  *size = 0;
  for (cmdent_idx = cmd_table; cmdent[cmdent_idx] != 0; cmdent_idx += 1)
  {
    if (strncmp(cmdent[cmdent_idx]->name, s, strlen(s)) == 0)
    {
      list_idx = xreallocarray(list_idx, (*size) + 1, sizeof(*list_idx));
      list[((*size)++) + list_idx] = cmdent[cmdent_idx]->name;
    }
  }

  for (oe_idx = options_table; oe->name != 0; oe_idx += 1)
  {
    if (strncmp(oe->name, s, strlen(s)) == 0)
    {
      list_idx = xreallocarray(list_idx, (*size) + 1, sizeof(*list_idx));
      list[((*size)++) + list_idx] = oe->name;
    }
  }

  for (layout_idx = layouts; layout[layout_idx] != 0; layout_idx += 1)
  {
    if (strncmp(*(&layout[layout_idx]), s, strlen(s)) == 0)
    {
      list_idx = xreallocarray(list_idx, (*size) + 1, sizeof(*list_idx));
      list[((*size)++) + list_idx] = layout[layout_idx];
    }
  }

  return list;
}


/*** DEPENDENCIES:
extern const struct options_table_entry options_table[]
----------------------------
void *xreallocarray(void *ptr, size_t nmemb, size_t size)
{
  void *new_ptr;
  unsigned int new_ptr_idx = 0;
  if ((nmemb == 0) || (size == 0))
  {
    fatalx("xreallocarray: zero size");
  }
  new_ptr_idx = reallocarray(ptr, nmemb, size);
  if ((&new_ptr[new_ptr_idx]) == 0)
  {
    fatalx("xreallocarray: allocating %zu * %zu bytes: %s", nmemb, size, strerror(errno));
  }
  return new_ptr;
}


----------------------------
None
----------------------------
extern const struct cmd_entry *cmd_table[]
----------------------------
None
----------------------------
***/


// hint:  ['list_idx_ref is a mutable refrence to unsigned int', 'size_ref is a mutable refrence to u_int', 'wl_idx_ref is a mutable refrence to unsigned int']
void helper_status_prompt_complete_1(unsigned int * const list_idx_ref, u_int * const size_ref, unsigned int * const wl_idx_ref, struct session * const session, const char * const s, const char ** const list, struct winlink * const wl, char * const tmp)
{
  unsigned int list_idx = *list_idx_ref;
  u_int size = *size_ref;
  unsigned int wl_idx = *wl_idx_ref;
  for (wl_idx = winlinks_RB_MINMAX(&session->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    xasprintf(&tmp, ":%s", wl->window->name);
    if (strncmp(tmp, s, strlen(s)) == 0)
    {
      list_idx = xreallocarray(list_idx, size + 1, sizeof(*list_idx));
      list[size + list_idx] = tmp;
      size += 1;
      continue;
    }
    free(tmp);
    xasprintf(&tmp, ":%d", wl->idx);
    if (strncmp(tmp, s, strlen(s)) == 0)
    {
      list_idx = xreallocarray(list_idx, size + 1, sizeof(*list_idx));
      list[size + list_idx] = tmp;
      size += 1;
      continue;
    }
    free(tmp);
  }

  *list_idx_ref = list_idx;
  *size_ref = size;
  *wl_idx_ref = wl_idx;
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
void *xreallocarray(void *ptr, size_t nmemb, size_t size)
{
  void *new_ptr;
  unsigned int new_ptr_idx = 0;
  if ((nmemb == 0) || (size == 0))
  {
    fatalx("xreallocarray: zero size");
  }
  new_ptr_idx = reallocarray(ptr, nmemb, size);
  if ((&new_ptr[new_ptr_idx]) == 0)
  {
    fatalx("xreallocarray: allocating %zu * %zu bytes: %s", nmemb, size, strerror(errno));
  }
  return new_ptr;
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
None
----------------------------
***/


// hint:  ['list_idx_ref is a mutable refrence to unsigned int', 'size_ref is a mutable refrence to u_int', 's_loop_idx_ref is a mutable refrence to unsigned int', 'wl_idx_ref is a mutable refrence to unsigned int', 'w_idx_ref is a mutable refrence to unsigned int']
void helper_status_prompt_complete_2(unsigned int * const list_idx_ref, u_int * const size_ref, unsigned int * const s_loop_idx_ref, unsigned int * const wl_idx_ref, unsigned int * const w_idx_ref, const char * const s, const char ** const list, struct session * const s_loop, struct winlink * const wl, struct window * const w, char * const tmp)
{
  unsigned int list_idx = *list_idx_ref;
  u_int size = *size_ref;
  unsigned int s_loop_idx = *s_loop_idx_ref;
  unsigned int wl_idx = *wl_idx_ref;
  unsigned int w_idx = *w_idx_ref;
  for (s_loop_idx = sessions_RB_MINMAX(&sessions, -1); (&s_loop[s_loop_idx]) != 0; s_loop_idx = sessions_RB_NEXT(s_loop_idx))
  {
    for (wl_idx = winlinks_RB_MINMAX(&s_loop->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
    {
      w_idx = wl->window;
      xasprintf(&tmp, "%s:%s", s_loop->name, w->name);
      if (strncmp(tmp, s, strlen(s)) == 0)
      {
        list_idx = xreallocarray(list_idx, size + 1, sizeof(*list_idx));
        list[size + list_idx] = tmp;
        size += 1;
        continue;
      }
      free(tmp);
      xasprintf(&tmp, "%s:%d", s_loop->name, wl->idx);
      if (strncmp(tmp, s, strlen(s)) == 0)
      {
        list_idx = xreallocarray(list_idx, size + 1, sizeof(*list_idx));
        list[size + list_idx] = tmp;
        size += 1;
        continue;
      }
      free(tmp);
    }

  }

  *list_idx_ref = list_idx;
  *size_ref = size;
  *s_loop_idx_ref = s_loop_idx;
  *wl_idx_ref = wl_idx;
  *w_idx_ref = w_idx;
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
void *xreallocarray(void *ptr, size_t nmemb, size_t size)
{
  void *new_ptr;
  unsigned int new_ptr_idx = 0;
  if ((nmemb == 0) || (size == 0))
  {
    fatalx("xreallocarray: zero size");
  }
  new_ptr_idx = reallocarray(ptr, nmemb, size);
  if ((&new_ptr[new_ptr_idx]) == 0)
  {
    fatalx("xreallocarray: allocating %zu * %zu bytes: %s", nmemb, size, strerror(errno));
  }
  return new_ptr;
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
None
----------------------------
***/


static char *status_prompt_complete(struct session *session, const char *s)
{
  unsigned int s_idx = 0;
  const char **list = 0;
  unsigned int list_idx = 0;
  const char *colon;
  unsigned int colon_idx = 0;
  u_int size = 0;
  u_int i;
  struct session *s_loop;
  unsigned int s_loop_idx = 0;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct window *w;
  unsigned int w_idx = 0;
  char *copy;
  unsigned int copy_idx = 0;
  char *out;
  unsigned int out_idx = 0;
  char *tmp;
  if (s[s_idx] == '\0')
  {
    return 0;
  }
  out_idx = 0;
  if ((strncmp(s, "-t", 2) != 0) && (strncmp(s, "-s", 2) != 0))
  {
    list_idx = status_prompt_complete_list(&size, s);
    if (size == 0)
    {
      out_idx = 0;
    }
    else
      if (size == 1)
    {
      xasprintf(&(&out[out_idx]), "%s ", list[0 + list_idx]);
    }
    else
      out_idx = status_prompt_complete_prefix(list, size);
    free(list);
    return out;
  }
  copy_idx = xstrdup(s);
  colon_idx = ":";
  if (copy[(strlen(copy) - 1) + copy_idx] == ':')
  {
    copy[(strlen(copy) - 1) + copy_idx] = '\0';
  }
  else
    colon_idx = "";
  s_idx = (&copy[copy_idx]) + 2;
  for (s_loop_idx = sessions_RB_MINMAX(&sessions, -1); (&s_loop[s_loop_idx]) != 0; s_loop_idx = sessions_RB_NEXT(s_loop_idx))
  {
    if (strncmp(s_loop->name, s, strlen(s)) == 0)
    {
      list_idx = xreallocarray(list_idx, size + 2, sizeof(*list_idx));
      list[size + list_idx] = s_loop->name;
      size += 1;
    }
  }

  if (size == 1)
  {
    out_idx = xstrdup(list[0 + list_idx]);
    if (session_find(list[0 + list_idx]) != 0)
    {
      colon_idx = ":";
    }
  }
  else
    if (size != 0)
  {
    out_idx = status_prompt_complete_prefix(list, size);
  }
  if ((&out[out_idx]) != 0)
  {
    xasprintf(&tmp, "-%c%s%s", copy[1 + copy_idx], out, colon);
    free(out);
    out_idx = tmp;
    goto found;
  }
  colon_idx = "";
  if (s[s_idx] == ':')
  {
    helper_status_prompt_complete_1(&list_idx, &size, &wl_idx, session, s, list, wl, tmp);
  }
  else
  {
    helper_status_prompt_complete_2(&list_idx, &size, &s_loop_idx, &wl_idx, &w_idx, s, list, s_loop, wl, w, tmp);
  }
  if (size == 1)
  {
    out_idx = xstrdup(list[0 + list_idx]);
    colon_idx = " ";
  }
  else
    if (size != 0)
  {
    out_idx = status_prompt_complete_prefix(list, size);
  }
  if ((&out[out_idx]) != 0)
  {
    xasprintf(&tmp, "-%c%s%s", copy[1 + copy_idx], out, colon);
    out_idx = tmp;
  }
  for (i = 0; i < size; i += 1)
  {
    free((void *) list[i + list_idx]);
  }

  found:
  free(copy);

  free(list);
  return out;
}


/*** DEPENDENCIES:
static const char **status_prompt_complete_list(u_int *size, const char *s)
{
  const char **list = 0;
  unsigned int list_idx = 0;
  const char **layout;
  unsigned int layout_idx = 0;
  const struct cmd_entry **cmdent;
  unsigned int cmdent_idx = 0;
  const struct options_table_entry *oe;
  unsigned int oe_idx = 0;
  const char *layouts[] = {"even-horizontal", "even-vertical", "main-horizontal", "main-vertical", "tiled", 0};
  *size = 0;
  for (cmdent_idx = cmd_table; cmdent[cmdent_idx] != 0; cmdent_idx += 1)
  {
    if (strncmp(cmdent[cmdent_idx]->name, s, strlen(s)) == 0)
    {
      list_idx = xreallocarray(list_idx, (*size) + 1, sizeof(*list_idx));
      list[((*size)++) + list_idx] = cmdent[cmdent_idx]->name;
    }
  }

  for (oe_idx = options_table; oe->name != 0; oe_idx += 1)
  {
    if (strncmp(oe->name, s, strlen(s)) == 0)
    {
      list_idx = xreallocarray(list_idx, (*size) + 1, sizeof(*list_idx));
      list[((*size)++) + list_idx] = oe->name;
    }
  }

  for (layout_idx = layouts; layout[layout_idx] != 0; layout_idx += 1)
  {
    if (strncmp(*(&layout[layout_idx]), s, strlen(s)) == 0)
    {
      list_idx = xreallocarray(list_idx, (*size) + 1, sizeof(*list_idx));
      list[((*size)++) + list_idx] = layout[layout_idx];
    }
  }

  return list;
}


----------------------------
struct session *session_find(const char *name)
{
  struct session s;
  s.name = (char *) name;
  return sessions_RB_FIND(&sessions, &s);
}


----------------------------
void helper_status_prompt_complete_1(unsigned int * const list_idx_ref, u_int * const size_ref, unsigned int * const wl_idx_ref, struct session * const session, const char * const s, const char ** const list, struct winlink * const wl, char * const tmp)
{
  unsigned int list_idx = *list_idx_ref;
  u_int size = *size_ref;
  unsigned int wl_idx = *wl_idx_ref;
  for (wl_idx = winlinks_RB_MINMAX(&session->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    xasprintf(&tmp, ":%s", wl->window->name);
    if (strncmp(tmp, s, strlen(s)) == 0)
    {
      list_idx = xreallocarray(list_idx, size + 1, sizeof(*list_idx));
      list[size + list_idx] = tmp;
      size += 1;
      continue;
    }
    free(tmp);
    xasprintf(&tmp, ":%d", wl->idx);
    if (strncmp(tmp, s, strlen(s)) == 0)
    {
      list_idx = xreallocarray(list_idx, size + 1, sizeof(*list_idx));
      list[size + list_idx] = tmp;
      size += 1;
      continue;
    }
    free(tmp);
  }

  *list_idx_ref = list_idx;
  *size_ref = size;
  *wl_idx_ref = wl_idx;
}


----------------------------
void *xreallocarray(void *ptr, size_t nmemb, size_t size)
{
  void *new_ptr;
  unsigned int new_ptr_idx = 0;
  if ((nmemb == 0) || (size == 0))
  {
    fatalx("xreallocarray: zero size");
  }
  new_ptr_idx = reallocarray(ptr, nmemb, size);
  if ((&new_ptr[new_ptr_idx]) == 0)
  {
    fatalx("xreallocarray: allocating %zu * %zu bytes: %s", nmemb, size, strerror(errno));
  }
  return new_ptr;
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
void helper_status_prompt_complete_2(unsigned int * const list_idx_ref, u_int * const size_ref, unsigned int * const s_loop_idx_ref, unsigned int * const wl_idx_ref, unsigned int * const w_idx_ref, const char * const s, const char ** const list, struct session * const s_loop, struct winlink * const wl, struct window * const w, char * const tmp)
{
  unsigned int list_idx = *list_idx_ref;
  u_int size = *size_ref;
  unsigned int s_loop_idx = *s_loop_idx_ref;
  unsigned int wl_idx = *wl_idx_ref;
  unsigned int w_idx = *w_idx_ref;
  for (s_loop_idx = sessions_RB_MINMAX(&sessions, -1); (&s_loop[s_loop_idx]) != 0; s_loop_idx = sessions_RB_NEXT(s_loop_idx))
  {
    for (wl_idx = winlinks_RB_MINMAX(&s_loop->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
    {
      w_idx = wl->window;
      xasprintf(&tmp, "%s:%s", s_loop->name, w->name);
      if (strncmp(tmp, s, strlen(s)) == 0)
      {
        list_idx = xreallocarray(list_idx, size + 1, sizeof(*list_idx));
        list[size + list_idx] = tmp;
        size += 1;
        continue;
      }
      free(tmp);
      xasprintf(&tmp, "%s:%d", s_loop->name, wl->idx);
      if (strncmp(tmp, s, strlen(s)) == 0)
      {
        list_idx = xreallocarray(list_idx, size + 1, sizeof(*list_idx));
        list[size + list_idx] = tmp;
        size += 1;
        continue;
      }
      free(tmp);
    }

  }

  *list_idx_ref = list_idx;
  *size_ref = size;
  *s_loop_idx_ref = s_loop_idx;
  *wl_idx_ref = wl_idx;
  *w_idx_ref = w_idx;
}


----------------------------
struct sessions
{
  struct session *rbh_root;
}
----------------------------
static char *status_prompt_complete_prefix(const char **list, u_int size)
{
  char *out;
  unsigned int out_idx = 0;
  u_int i;
  size_t j;
  out_idx = xstrdup(list[0]);
  for (i = 1; i < size; i += 1)
  {
    j = strlen(list[i]);
    if (j > strlen(out))
    {
      j = strlen(out);
    }
    for (; j > 0; j -= 1)
    {
      if (out[(j - 1) + out_idx] != list[i][j - 1])
      {
        out[(j - 1) + out_idx] = '\0';
      }
    }

  }

  return out;
}


----------------------------
None
----------------------------
***/


// hint:  ['s_idx_ref is a mutable refrence to unsigned int', 'size_ref is a mutable refrence to size_t', 'n_ref is a mutable refrence to size_t', 'off_ref is a mutable refrence to size_t', 'idx_ref is a mutable refrence to size_t', 'used_ref is a mutable refrence to size_t', 'first_idx_ref is a mutable refrence to unsigned int', 'last_idx_ref is a mutable refrence to unsigned int', 'ud_idx_ref is a mutable refrence to unsigned int']
void helper_status_prompt_key_5(unsigned int * const s_idx_ref, size_t * const size_ref, size_t * const n_ref, size_t * const off_ref, size_t * const idx_ref, size_t * const used_ref, unsigned int * const first_idx_ref, unsigned int * const last_idx_ref, unsigned int * const ud_idx_ref, struct client * const c, char * const s, char word[64], struct utf8_data * const first, struct utf8_data * const last, struct utf8_data * const ud)
{
  unsigned int s_idx = *s_idx_ref;
  size_t size = *size_ref;
  size_t n = *n_ref;
  size_t off = *off_ref;
  size_t idx = *idx_ref;
  size_t used = *used_ref;
  unsigned int first_idx = *first_idx_ref;
  unsigned int last_idx = *last_idx_ref;
  unsigned int ud_idx = *ud_idx_ref;
  if (c->prompt_buffer[0].size == 0)
  {
    break;
  }
  idx = c->prompt_index;
  if (idx != 0)
  {
    idx -= 1;
  }
  first_idx = &c->prompt_buffer[idx];
  while (((&first[first_idx]) > c->prompt_buffer) && (!status_prompt_space(first)))
  {
    first_idx -= 1;
  }

  while ((first->size != 0) && status_prompt_space(first))
  {
    first_idx += 1;
  }

  last_idx = &c->prompt_buffer[idx];
  while ((last->size != 0) && (!status_prompt_space(last)))
  {
    last_idx += 1;
  }

  while (((&last[last_idx]) > c->prompt_buffer) && status_prompt_space(last))
  {
    last_idx -= 1;
  }

  if (last->size != 0)
  {
    last_idx += 1;
  }
  if ((&last[last_idx]) <= (&first[first_idx]))
  {
    break;
  }
  used = 0;
  for (ud_idx = &first[first_idx]; (&ud[ud_idx]) < (&last[last_idx]); ud_idx += 1)
  {
    if ((used + ud->size) >= (sizeof(word)))
    {
      break;
    }
    memcpy(word + used, ud->data, ud->size);
    used += ud->size;
  }

  if ((&ud[ud_idx]) != (&last[last_idx]))
  {
    break;
  }
  word[used] = '\0';
  if ((s_idx = status_prompt_complete(c->session, word)) == 0)
  {
    break;
  }
  n = (size - ((&last[last_idx]) - c->prompt_buffer)) + 1;
  memmove(first, last, n * (sizeof(*c->prompt_buffer)));
  size -= (&last[last_idx]) - (&first[first_idx]);
  size += strlen(s);
  off = (&first[first_idx]) - c->prompt_buffer;
  c->prompt_buffer = xreallocarray(c->prompt_buffer, size + 1, sizeof(*c->prompt_buffer));
  first_idx = c->prompt_buffer + off;
  memmove((&first[first_idx]) + strlen(s), first, n * (sizeof(*c->prompt_buffer)));
  for (idx = 0; idx < strlen(s); idx += 1)
  {
    utf8_set(&first[idx + first_idx], s[idx + s_idx]);
  }

  c->prompt_index = ((&first[first_idx]) - c->prompt_buffer) + strlen(s);
  free(s);
  goto changed;
  *s_idx_ref = s_idx;
  *size_ref = size;
  *n_ref = n;
  *off_ref = off;
  *idx_ref = idx;
  *used_ref = used;
  *first_idx_ref = first_idx;
  *last_idx_ref = last_idx;
  *ud_idx_ref = ud_idx;
}


/*** DEPENDENCIES:
void utf8_set(struct utf8_data *ud, u_char ch)
{
  static const struct utf8_data empty = {{0}, 1, 1, 1};
  memcpy(ud, &empty, sizeof(*ud));
  *ud->data = ch;
}


----------------------------
static char *status_prompt_complete(struct session *session, const char *s)
{
  unsigned int s_idx = 0;
  const char **list = 0;
  unsigned int list_idx = 0;
  const char *colon;
  unsigned int colon_idx = 0;
  u_int size = 0;
  u_int i;
  struct session *s_loop;
  unsigned int s_loop_idx = 0;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct window *w;
  unsigned int w_idx = 0;
  char *copy;
  unsigned int copy_idx = 0;
  char *out;
  unsigned int out_idx = 0;
  char *tmp;
  if (s[s_idx] == '\0')
  {
    return 0;
  }
  out_idx = 0;
  if ((strncmp(s, "-t", 2) != 0) && (strncmp(s, "-s", 2) != 0))
  {
    list_idx = status_prompt_complete_list(&size, s);
    if (size == 0)
    {
      out_idx = 0;
    }
    else
      if (size == 1)
    {
      xasprintf(&(&out[out_idx]), "%s ", list[0 + list_idx]);
    }
    else
      out_idx = status_prompt_complete_prefix(list, size);
    free(list);
    return out;
  }
  copy_idx = xstrdup(s);
  colon_idx = ":";
  if (copy[(strlen(copy) - 1) + copy_idx] == ':')
  {
    copy[(strlen(copy) - 1) + copy_idx] = '\0';
  }
  else
    colon_idx = "";
  s_idx = (&copy[copy_idx]) + 2;
  for (s_loop_idx = sessions_RB_MINMAX(&sessions, -1); (&s_loop[s_loop_idx]) != 0; s_loop_idx = sessions_RB_NEXT(s_loop_idx))
  {
    if (strncmp(s_loop->name, s, strlen(s)) == 0)
    {
      list_idx = xreallocarray(list_idx, size + 2, sizeof(*list_idx));
      list[size + list_idx] = s_loop->name;
      size += 1;
    }
  }

  if (size == 1)
  {
    out_idx = xstrdup(list[0 + list_idx]);
    if (session_find(list[0 + list_idx]) != 0)
    {
      colon_idx = ":";
    }
  }
  else
    if (size != 0)
  {
    out_idx = status_prompt_complete_prefix(list, size);
  }
  if ((&out[out_idx]) != 0)
  {
    xasprintf(&tmp, "-%c%s%s", copy[1 + copy_idx], out, colon);
    free(out);
    out_idx = tmp;
    goto found;
  }
  colon_idx = "";
  if (s[s_idx] == ':')
  {
    helper_status_prompt_complete_1(&list_idx, &size, &wl_idx, session, s, list, wl, tmp);
  }
  else
  {
    helper_status_prompt_complete_2(&list_idx, &size, &s_loop_idx, &wl_idx, &w_idx, s, list, s_loop, wl, w, tmp);
  }
  if (size == 1)
  {
    out_idx = xstrdup(list[0 + list_idx]);
    colon_idx = " ";
  }
  else
    if (size != 0)
  {
    out_idx = status_prompt_complete_prefix(list, size);
  }
  if ((&out[out_idx]) != 0)
  {
    xasprintf(&tmp, "-%c%s%s", copy[1 + copy_idx], out, colon);
    out_idx = tmp;
  }
  for (i = 0; i < size; i += 1)
  {
    free((void *) list[i + list_idx]);
  }

  found:
  free(copy);

  free(list);
  return out;
}


----------------------------
void *xreallocarray(void *ptr, size_t nmemb, size_t size)
{
  void *new_ptr;
  unsigned int new_ptr_idx = 0;
  if ((nmemb == 0) || (size == 0))
  {
    fatalx("xreallocarray: zero size");
  }
  new_ptr_idx = reallocarray(ptr, nmemb, size);
  if ((&new_ptr[new_ptr_idx]) == 0)
  {
    fatalx("xreallocarray: allocating %zu * %zu bytes: %s", nmemb, size, strerror(errno));
  }
  return new_ptr;
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
static int status_prompt_space(const struct utf8_data *ud)
{
  if ((ud->size != 1) || (ud->width != 1))
  {
    return 0;
  }
  return (*ud->data) == ' ';
}


----------------------------
None
----------------------------
***/


int status_prompt_key(struct client *c, key_code key)
{
  struct options *oo = c->session->options;
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  char *s;
  unsigned int s_idx = 0;
  char *cp;
  char word[64];
  char prefix = '=';
  const char *histstr;
  unsigned int histstr_idx = 0;
  const char *bufdata;
  unsigned int bufdata_idx = 0;
  const char *ws = 0;
  unsigned int ws_idx = 0;
  u_char ch;
  size_t size;
  size_t n;
  size_t off;
  size_t idx;
  size_t bufsize;
  size_t used;
  struct utf8_data tmp;
  struct utf8_data *first;
  unsigned int first_idx = 0;
  struct utf8_data *last;
  unsigned int last_idx = 0;
  struct utf8_data *ud;
  unsigned int ud_idx = 0;
  int keys;
  size = utf8_strlen(c->prompt_buffer);
  if (c->prompt_flags & 0x2)
  {
    if ((key >= '0') && (key <= '9'))
    {
      goto append_key;
    }
    s_idx = utf8_tocstr(c->prompt_buffer);
    c->prompt_inputcb(c, c->prompt_data, s, 1);
    status_prompt_clear(c);
    free(s);
    return 1;
  }
  keys = options_get_number(c->session->options, "status-keys");
  if (keys == 1)
  {
    switch (status_prompt_translate_key(c, key, &key))
    {
      case 1:
      {
        goto process_key;
      }

      case 2:
      {
        goto append_key;
      }

      default:
      {
        return 0;
      }

    }

  }
  process_key:
  switch (key)
  {
    case KEYC_LEFT:

    case '\002':
    {
      if (c->prompt_index > 0)
      {
        c->prompt_index -= 1;
        break;
      }
      break;
    }

    case KEYC_RIGHT:

    case '\006':
    {
      if (c->prompt_index < size)
      {
        c->prompt_index += 1;
        break;
      }
      break;
    }

    case KEYC_HOME:

    case '\001':
    {
      if (c->prompt_index != 0)
      {
        c->prompt_index = 0;
        break;
      }
      break;
    }

    case KEYC_END:

    case '\005':
    {
      if (c->prompt_index != size)
      {
        c->prompt_index = size;
        break;
      }
      break;
    }

    case '\011':
    {
      helper_status_prompt_key_5(&s_idx, &size, &n, &off, &idx, &used, &first_idx, &last_idx, &ud_idx, c, s, word, first, last, ud);
    }

    case KEYC_BSPACE:

    case '\010':
    {
      if (c->prompt_index != 0)
      {
        if (c->prompt_index == size)
        {
          c->prompt_buffer[--c->prompt_index].size = 0;
        }
        else
        {
          memmove((c->prompt_buffer + c->prompt_index) - 1, c->prompt_buffer + c->prompt_index, ((size + 1) - c->prompt_index) * (sizeof(*c->prompt_buffer)));
          c->prompt_index -= 1;
        }
        goto changed;
      }
      break;
    }

    case KEYC_DC:

    case '\004':
    {
      if (c->prompt_index != size)
      {
        memmove(c->prompt_buffer + c->prompt_index, (c->prompt_buffer + c->prompt_index) + 1, ((size + 1) - c->prompt_index) * (sizeof(*c->prompt_buffer)));
        goto changed;
      }
      break;
    }

    case '\025':
    {
      c->prompt_buffer[0].size = 0;
      c->prompt_index = 0;
      goto changed;
    }

    case '\013':
    {
      if (c->prompt_index < size)
      {
        c->prompt_buffer[c->prompt_index].size = 0;
        goto changed;
      }
      break;
    }

    case '\027':
    {
      helper_status_prompt_key_3(&ws_idx, &idx, c, oo, ws, size);
    }

    case 'f' | 0x200000000000ULL:
    {
      helper_status_prompt_key_2(&ws_idx, &idx, c, oo, ws, size);
    }

    case 'b' | 0x200000000000ULL:
    {
      helper_status_prompt_key_1(&ws_idx, &idx, c, oo, ws);
    }

    case KEYC_UP:

    case '\020':
    {
      histstr_idx = status_prompt_up_history(&c->prompt_hindex);
      if ((&histstr[histstr_idx]) == 0)
      {
        break;
      }
      free(c->prompt_buffer);
      c->prompt_buffer = utf8_fromcstr(histstr);
      c->prompt_index = utf8_strlen(c->prompt_buffer);
      goto changed;
    }

    case KEYC_DOWN:

    case '\016':
    {
      histstr_idx = status_prompt_down_history(&c->prompt_hindex);
      if ((&histstr[histstr_idx]) == 0)
      {
        break;
      }
      free(c->prompt_buffer);
      c->prompt_buffer = utf8_fromcstr(histstr);
      c->prompt_index = utf8_strlen(c->prompt_buffer);
      goto changed;
    }

    case '\031':
    {
      helper_status_prompt_key_4(&pb_idx, &bufdata_idx, &ch, &size, &n, &idx, &ud_idx, c, pb, bufdata, bufsize, ud);
    }

    case '\024':
    {
      idx = c->prompt_index;
      if (idx < size)
      {
        idx += 1;
      }
      if (idx >= 2)
      {
        utf8_copy(&tmp, &c->prompt_buffer[idx - 2]);
        utf8_copy(&c->prompt_buffer[idx - 2], &c->prompt_buffer[idx - 1]);
        utf8_copy(&c->prompt_buffer[idx - 1], &tmp);
        c->prompt_index = idx;
        goto changed;
      }
      break;
    }

    case '\r':

    case '\n':
    {
      s_idx = utf8_tocstr(c->prompt_buffer);
      if (s[s_idx] != '\0')
      {
        status_prompt_add_history(s);
      }
      if (c->prompt_inputcb(c, c->prompt_data, s, 1) == 0)
      {
        status_prompt_clear(c);
      }
      free(s);
      break;
    }

    case '\033':

    case '\003':

    case '\007':
    {
      if (c->prompt_inputcb(c, c->prompt_data, 0, 1) == 0)
      {
        status_prompt_clear(c);
      }
      break;
    }

    case '\022':
    {
      if (c->prompt_flags & 0x4)
      {
        prefix = '-';
        goto changed;
      }
      break;
    }

    case '\023':
    {
      if (c->prompt_flags & 0x4)
      {
        prefix = '+';
        goto changed;
      }
      break;
    }

    default:
    {
      goto append_key;
    }

  }


  c->flags |= 0x10;
  return 0;
  append_key:
  if ((key <= 0x1f) || (key >= 0x000010000000ULL))
  {
    return 0;
  }

  if (utf8_split(key, &tmp) != UTF8_DONE)
  {
    return 0;
  }
  c->prompt_buffer = xreallocarray(c->prompt_buffer, size + 2, sizeof(*c->prompt_buffer));
  if (c->prompt_index == size)
  {
    utf8_copy(&c->prompt_buffer[c->prompt_index], &tmp);
    c->prompt_index += 1;
    c->prompt_buffer[c->prompt_index].size = 0;
  }
  else
  {
    memmove((c->prompt_buffer + c->prompt_index) + 1, c->prompt_buffer + c->prompt_index, ((size + 1) - c->prompt_index) * (sizeof(*c->prompt_buffer)));
    utf8_copy(&c->prompt_buffer[c->prompt_index], &tmp);
    c->prompt_index += 1;
  }
  if (c->prompt_flags & 0x1)
  {
    s_idx = utf8_tocstr(c->prompt_buffer);
    if (strlen(s) != 1)
    {
      status_prompt_clear(c);
    }
    else
      if (c->prompt_inputcb(c, c->prompt_data, s, 1) == 0)
    {
      status_prompt_clear(c);
    }
    free(s);
  }
  changed:
  c->flags |= 0x10;

  if (c->prompt_flags & 0x4)
  {
    s_idx = utf8_tocstr(c->prompt_buffer);
    xasprintf(&cp, "%c%s", prefix, s);
    c->prompt_inputcb(c, c->prompt_data, cp, 0);
    free(cp);
    free(s);
  }
  return 0;
}


/*** DEPENDENCIES:
typedef unsigned long long key_code
----------------------------
void *xreallocarray(void *ptr, size_t nmemb, size_t size)
{
  void *new_ptr;
  unsigned int new_ptr_idx = 0;
  if ((nmemb == 0) || (size == 0))
  {
    fatalx("xreallocarray: zero size");
  }
  new_ptr_idx = reallocarray(ptr, nmemb, size);
  if ((&new_ptr[new_ptr_idx]) == 0)
  {
    fatalx("xreallocarray: allocating %zu * %zu bytes: %s", nmemb, size, strerror(errno));
  }
  return new_ptr;
}


----------------------------
void helper_status_prompt_key_1(unsigned int * const ws_idx_ref, size_t * const idx_ref, struct client * const c, struct options * const oo, const char * const ws)
{
  unsigned int ws_idx = *ws_idx_ref;
  size_t idx = *idx_ref;
  ws_idx = options_get_string(oo, "word-separators");
  while (c->prompt_index != 0)
  {
    idx = --c->prompt_index;
    if (!status_prompt_in_list(ws, &c->prompt_buffer[idx]))
    {
      break;
    }
  }

  while (c->prompt_index != 0)
  {
    idx = --c->prompt_index;
    if (status_prompt_in_list(ws, &c->prompt_buffer[idx]))
    {
      c->prompt_index += 1;
      break;
    }
  }

  goto changed;
  *ws_idx_ref = ws_idx;
  *idx_ref = idx;
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
void helper_status_prompt_key_4(unsigned int * const pb_idx_ref, unsigned int * const bufdata_idx_ref, u_char * const ch_ref, size_t * const size_ref, size_t * const n_ref, size_t * const idx_ref, unsigned int * const ud_idx_ref, struct client * const c, struct paste_buffer * const pb, const char * const bufdata, size_t bufsize, struct utf8_data * const ud)
{
  unsigned int pb_idx = *pb_idx_ref;
  unsigned int bufdata_idx = *bufdata_idx_ref;
  u_char ch = *ch_ref;
  size_t size = *size_ref;
  size_t n = *n_ref;
  size_t idx = *idx_ref;
  unsigned int ud_idx = *ud_idx_ref;
  if ((pb_idx = paste_get_top(0)) == 0)
  {
    break;
  }
  bufdata_idx = paste_buffer_data(pb, &bufsize);
  for (n = 0; n < bufsize; n += 1)
  {
    ch = (u_char) bufdata[n + bufdata_idx];
    if ((ch < 32) || (ch >= 127))
    {
      break;
    }
  }

  c->prompt_buffer = xreallocarray(c->prompt_buffer, (size + n) + 1, sizeof(*c->prompt_buffer));
  if (c->prompt_index == size)
  {
    for (idx = 0; idx < n; idx += 1)
    {
      ud_idx = &c->prompt_buffer[c->prompt_index + idx];
      utf8_set(ud, bufdata[idx + bufdata_idx]);
    }

    c->prompt_index += n;
    c->prompt_buffer[c->prompt_index].size = 0;
  }
  else
  {
    memmove((c->prompt_buffer + c->prompt_index) + n, c->prompt_buffer + c->prompt_index, ((size + 1) - c->prompt_index) * (sizeof(*c->prompt_buffer)));
    for (idx = 0; idx < n; idx += 1)
    {
      ud_idx = &c->prompt_buffer[c->prompt_index + idx];
      utf8_set(ud, bufdata[idx + bufdata_idx]);
    }

    c->prompt_index += n;
  }
  goto changed;
  *pb_idx_ref = pb_idx;
  *bufdata_idx_ref = bufdata_idx;
  *ch_ref = ch;
  *size_ref = size;
  *n_ref = n;
  *idx_ref = idx;
  *ud_idx_ref = ud_idx;
}


----------------------------
void helper_status_prompt_key_3(unsigned int * const ws_idx_ref, size_t * const idx_ref, struct client * const c, struct options * const oo, const char * const ws, size_t size)
{
  unsigned int ws_idx = *ws_idx_ref;
  size_t idx = *idx_ref;
  ws_idx = options_get_string(oo, "word-separators");
  idx = c->prompt_index;
  while (idx != 0)
  {
    idx -= 1;
    if (!status_prompt_in_list(ws, &c->prompt_buffer[idx]))
    {
      break;
    }
  }

  while (idx != 0)
  {
    idx -= 1;
    if (status_prompt_in_list(ws, &c->prompt_buffer[idx]))
    {
      idx += 1;
      break;
    }
  }

  memmove(c->prompt_buffer + idx, c->prompt_buffer + c->prompt_index, ((size + 1) - c->prompt_index) * (sizeof(*c->prompt_buffer)));
  memset((c->prompt_buffer + size) - (c->prompt_index - idx), '\0', (c->prompt_index - idx) * (sizeof(*c->prompt_buffer)));
  c->prompt_index = idx;
  goto changed;
  *ws_idx_ref = ws_idx;
  *idx_ref = idx;
}


----------------------------
static const char *status_prompt_up_history(u_int *idx)
{
  if ((status_prompt_hsize == 0) || ((*idx) == status_prompt_hsize))
  {
    return 0;
  }
  *idx += 1;
  return status_prompt_hlist[status_prompt_hsize - (*idx)];
}


----------------------------
char *utf8_tocstr(struct utf8_data *src)
{
  unsigned int src_idx = 0;
  char *dst;
  unsigned int dst_idx = 0;
  size_t n;
  dst_idx = 0;
  n = 0;
  for (; src->size != 0; src_idx += 1)
  {
    dst_idx = xreallocarray(dst_idx, n + src->size, 1);
    memcpy((&dst[dst_idx]) + n, src->data, src->size);
    n += src->size;
  }

  dst_idx = xreallocarray(dst_idx, n + 1, 1);
  dst[n + dst_idx] = '\0';
  return dst;
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
static const char *status_prompt_down_history(u_int *idx)
{
  if ((status_prompt_hsize == 0) || ((*idx) == 0))
  {
    return "";
  }
  *idx -= 1;
  if ((*idx) == 0)
  {
    return "";
  }
  return status_prompt_hlist[status_prompt_hsize - (*idx)];
}


----------------------------
None
----------------------------
void status_prompt_clear(struct client *c)
{
  if (c->prompt_string == 0)
  {
    return;
  }
  if ((c->prompt_freecb != 0) && (c->prompt_data != 0))
  {
    c->prompt_freecb(c->prompt_data);
  }
  free(c->prompt_string);
  c->prompt_string = 0;
  free(c->prompt_buffer);
  c->prompt_buffer = 0;
  c->tty.flags &= ~(0x1 | 0x2);
  c->flags |= 0x8;
  screen_reinit(&c->status.status);
}


----------------------------
void helper_status_prompt_key_2(unsigned int * const ws_idx_ref, size_t * const idx_ref, struct client * const c, struct options * const oo, const char * const ws, size_t size)
{
  unsigned int ws_idx = *ws_idx_ref;
  size_t idx = *idx_ref;
  ws_idx = options_get_string(oo, "word-separators");
  while (c->prompt_index != size)
  {
    idx = ++c->prompt_index;
    if (!status_prompt_in_list(ws, &c->prompt_buffer[idx]))
    {
      break;
    }
  }

  while (c->prompt_index != size)
  {
    idx = ++c->prompt_index;
    if (status_prompt_in_list(ws, &c->prompt_buffer[idx]))
    {
      break;
    }
  }

  if ((options_get_number(oo, "status-keys") == 1) && (c->prompt_index != 0))
  {
    c->prompt_index -= 1;
  }
  goto changed;
  *ws_idx_ref = ws_idx;
  *idx_ref = idx;
}


----------------------------
size_t utf8_strlen(const struct utf8_data *s)
{
  size_t i;
  for (i = 0; s[i].size != 0; i += 1)
  {
    ;
  }

  return i;
}


----------------------------
struct utf8_data *utf8_fromcstr(const char *src)
{
  unsigned int src_idx = 0;
  struct utf8_data *dst;
  unsigned int dst_idx = 0;
  size_t n;
  enum utf8_state more;
  dst_idx = 0;
  n = 0;
  while (src[src_idx] != '\0')
  {
    dst_idx = xreallocarray(dst_idx, n + 1, sizeof(*dst_idx));
    if ((more = utf8_open(&dst[n + dst_idx], *(&src[src_idx]))) == UTF8_MORE)
    {
      while (((*(++(&src[src_idx]))) != '\0') && (more == UTF8_MORE))
      {
        more = utf8_append(&dst[n + dst_idx], *(&src[src_idx]));
      }

      if (more == UTF8_DONE)
      {
        n += 1;
        continue;
      }
      src_idx -= dst[n + dst_idx].have;
    }
    utf8_set(&dst[n + dst_idx], *(&src[src_idx]));
    n += 1;
    src_idx += 1;
  }

  dst_idx = xreallocarray(dst_idx, n + 1, sizeof(*dst_idx));
  dst[n + dst_idx].size = 0;
  return dst;
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
void helper_status_prompt_key_5(unsigned int * const s_idx_ref, size_t * const size_ref, size_t * const n_ref, size_t * const off_ref, size_t * const idx_ref, size_t * const used_ref, unsigned int * const first_idx_ref, unsigned int * const last_idx_ref, unsigned int * const ud_idx_ref, struct client * const c, char * const s, char word[64], struct utf8_data * const first, struct utf8_data * const last, struct utf8_data * const ud)
{
  unsigned int s_idx = *s_idx_ref;
  size_t size = *size_ref;
  size_t n = *n_ref;
  size_t off = *off_ref;
  size_t idx = *idx_ref;
  size_t used = *used_ref;
  unsigned int first_idx = *first_idx_ref;
  unsigned int last_idx = *last_idx_ref;
  unsigned int ud_idx = *ud_idx_ref;
  if (c->prompt_buffer[0].size == 0)
  {
    break;
  }
  idx = c->prompt_index;
  if (idx != 0)
  {
    idx -= 1;
  }
  first_idx = &c->prompt_buffer[idx];
  while (((&first[first_idx]) > c->prompt_buffer) && (!status_prompt_space(first)))
  {
    first_idx -= 1;
  }

  while ((first->size != 0) && status_prompt_space(first))
  {
    first_idx += 1;
  }

  last_idx = &c->prompt_buffer[idx];
  while ((last->size != 0) && (!status_prompt_space(last)))
  {
    last_idx += 1;
  }

  while (((&last[last_idx]) > c->prompt_buffer) && status_prompt_space(last))
  {
    last_idx -= 1;
  }

  if (last->size != 0)
  {
    last_idx += 1;
  }
  if ((&last[last_idx]) <= (&first[first_idx]))
  {
    break;
  }
  used = 0;
  for (ud_idx = &first[first_idx]; (&ud[ud_idx]) < (&last[last_idx]); ud_idx += 1)
  {
    if ((used + ud->size) >= (sizeof(word)))
    {
      break;
    }
    memcpy(word + used, ud->data, ud->size);
    used += ud->size;
  }

  if ((&ud[ud_idx]) != (&last[last_idx]))
  {
    break;
  }
  word[used] = '\0';
  if ((s_idx = status_prompt_complete(c->session, word)) == 0)
  {
    break;
  }
  n = (size - ((&last[last_idx]) - c->prompt_buffer)) + 1;
  memmove(first, last, n * (sizeof(*c->prompt_buffer)));
  size -= (&last[last_idx]) - (&first[first_idx]);
  size += strlen(s);
  off = (&first[first_idx]) - c->prompt_buffer;
  c->prompt_buffer = xreallocarray(c->prompt_buffer, size + 1, sizeof(*c->prompt_buffer));
  first_idx = c->prompt_buffer + off;
  memmove((&first[first_idx]) + strlen(s), first, n * (sizeof(*c->prompt_buffer)));
  for (idx = 0; idx < strlen(s); idx += 1)
  {
    utf8_set(&first[idx + first_idx], s[idx + s_idx]);
  }

  c->prompt_index = ((&first[first_idx]) - c->prompt_buffer) + strlen(s);
  free(s);
  goto changed;
  *s_idx_ref = s_idx;
  *size_ref = size;
  *n_ref = n;
  *off_ref = off;
  *idx_ref = idx;
  *used_ref = used;
  *first_idx_ref = first_idx;
  *last_idx_ref = last_idx;
  *ud_idx_ref = ud_idx;
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
static void status_prompt_add_history(const char *line)
{
  size_t size;
  if ((status_prompt_hsize > 0) && (strcmp(status_prompt_hlist[status_prompt_hsize - 1], line) == 0))
  {
    return;
  }
  if (status_prompt_hsize == 100)
  {
    free(status_prompt_hlist[0]);
    size = (100 - 1) * (sizeof(*status_prompt_hlist));
    memmove(&status_prompt_hlist[0], &status_prompt_hlist[1], size);
    status_prompt_hlist[status_prompt_hsize - 1] = xstrdup(line);
    return;
  }
  status_prompt_hlist = xreallocarray(status_prompt_hlist, status_prompt_hsize + 1, sizeof(*status_prompt_hlist));
  status_prompt_hlist[status_prompt_hsize] = xstrdup(line);
  status_prompt_hsize += 1;
}


----------------------------
static int status_prompt_translate_key(struct client *c, key_code key, key_code *new_key)
{
  if (c->prompt_mode == PROMPT_ENTRY)
  {
    switch (key)
    {
      case '\003':

      case '\010':

      case '\011':

      case '\025':

      case '\027':

      case '\n':

      case '\r':

      case KEYC_BSPACE:

      case KEYC_DC:

      case KEYC_DOWN:

      case KEYC_END:

      case KEYC_HOME:

      case KEYC_LEFT:

      case KEYC_RIGHT:

      case KEYC_UP:
      {
        *new_key = key;
        return 1;
      }

      case '\033':
      {
        c->prompt_mode = PROMPT_COMMAND;
        c->flags |= 0x10;
        return 0;
      }

    }

    *new_key = key;
    return 2;
  }
  switch (key)
  {
    case 'A':

    case 'I':

    case 'C':

    case 's':

    case 'a':
    {
      c->prompt_mode = PROMPT_ENTRY;
      c->flags |= 0x10;
      break;
    }

    case 'S':
    {
      c->prompt_mode = PROMPT_ENTRY;
      c->flags |= 0x10;
      *new_key = '\025';
      return 1;
    }

    case 'i':

    case '\033':
    {
      c->prompt_mode = PROMPT_ENTRY;
      c->flags |= 0x10;
      return 0;
    }

  }

  switch (key)
  {
    case 'A':

    case '$':
    {
      *new_key = KEYC_END;
      return 1;
    }

    case 'I':

    case '0':

    case '^':
    {
      *new_key = KEYC_HOME;
      return 1;
    }

    case 'C':

    case 'D':
    {
      *new_key = '\013';
      return 1;
    }

    case KEYC_BSPACE:

    case 'X':
    {
      *new_key = KEYC_BSPACE;
      return 1;
    }

    case 'b':

    case 'B':
    {
      *new_key = 'b' | 0x200000000000ULL;
      return 1;
    }

    case 'd':
    {
      *new_key = '\025';
      return 1;
    }

    case 'e':

    case 'E':

    case 'w':

    case 'W':
    {
      *new_key = 'f' | 0x200000000000ULL;
      return 1;
    }

    case 'p':
    {
      *new_key = '\031';
      return 1;
    }

    case 's':

    case KEYC_DC:

    case 'x':
    {
      *new_key = KEYC_DC;
      return 1;
    }

    case KEYC_DOWN:

    case 'j':
    {
      *new_key = KEYC_DOWN;
      return 1;
    }

    case KEYC_LEFT:

    case 'h':
    {
      *new_key = KEYC_LEFT;
      return 1;
    }

    case 'a':

    case KEYC_RIGHT:

    case 'l':
    {
      *new_key = KEYC_RIGHT;
      return 1;
    }

    case KEYC_UP:

    case 'k':
    {
      *new_key = KEYC_UP;
      return 1;
    }

    case '\010':

    case '\003':

    case '\n':

    case '\r':
    {
      return 1;
    }

  }

  return 0;
}


----------------------------
enum utf8_state utf8_split(wchar_t wc, struct utf8_data *ud)
{
  char s[MB_LEN_MAX];
  int slen;
  slen = wctomb(s, wc);
  if ((slen <= 0) || (slen > ((int) (sizeof(ud->data)))))
  {
    return UTF8_ERROR;
  }
  memcpy(ud->data, s, slen);
  ud->size = slen;
  ud->width = utf8_width(wc);
  return UTF8_DONE;
}


----------------------------
None
----------------------------
***/


void status_timer_start_all(void)
{
  struct client *c;
  unsigned int c_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    status_timer_start(c);
  }

}


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
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
None
----------------------------
***/


void status_prompt_update(struct client *c, const char *msg, const char *input)
{
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  time_t t;
  char *tmp;
  unsigned int tmp_idx = 0;
  ft_idx = format_create(c, 0, 0, 0);
  format_defaults(ft, c, 0, 0, 0);
  t = time(0);
  tmp_idx = format_expand_time(ft, input, t);
  free(c->prompt_string);
  c->prompt_string = format_expand_time(ft, msg, t);
  free(c->prompt_buffer);
  c->prompt_buffer = utf8_fromcstr(tmp);
  c->prompt_index = utf8_strlen(c->prompt_buffer);
  c->prompt_hindex = 0;
  c->flags |= 0x10;
  free(tmp);
  format_free(ft);
}


/*** DEPENDENCIES:
size_t utf8_strlen(const struct utf8_data *s)
{
  size_t i;
  for (i = 0; s[i].size != 0; i += 1)
  {
    ;
  }

  return i;
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
struct utf8_data *utf8_fromcstr(const char *src)
{
  unsigned int src_idx = 0;
  struct utf8_data *dst;
  unsigned int dst_idx = 0;
  size_t n;
  enum utf8_state more;
  dst_idx = 0;
  n = 0;
  while (src[src_idx] != '\0')
  {
    dst_idx = xreallocarray(dst_idx, n + 1, sizeof(*dst_idx));
    if ((more = utf8_open(&dst[n + dst_idx], *(&src[src_idx]))) == UTF8_MORE)
    {
      while (((*(++(&src[src_idx]))) != '\0') && (more == UTF8_MORE))
      {
        more = utf8_append(&dst[n + dst_idx], *(&src[src_idx]));
      }

      if (more == UTF8_DONE)
      {
        n += 1;
        continue;
      }
      src_idx -= dst[n + dst_idx].have;
    }
    utf8_set(&dst[n + dst_idx], *(&src[src_idx]));
    n += 1;
    src_idx += 1;
  }

  dst_idx = xreallocarray(dst_idx, n + 1, sizeof(*dst_idx));
  dst[n + dst_idx].size = 0;
  return dst;
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
pub time: Time
----------------------------
char *format_expand_time(struct format_tree *ft, const char *fmt, time_t t)
{
  struct tm *tm;
  unsigned int tm_idx = 0;
  char s[2048];
  if ((fmt == 0) || ((*fmt) == '\0'))
  {
    return xstrdup("");
  }
  tm_idx = localtime(&t);
  if (strftime(s, sizeof(s), fmt, tm) == 0)
  {
    return xstrdup("");
  }
  return format_expand(ft, s);
}


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
None
----------------------------
***/


void status_prompt_set(struct client *c, const char *msg, const char *input, prompt_input_cb inputcb, prompt_free_cb freecb, void *data, int flags)
{
  unsigned int input_idx = 0;
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  time_t t;
  char *tmp;
  unsigned int tmp_idx = 0;
  char *cp;
  ft_idx = format_create(c, 0, 0, 0);
  format_defaults(ft, c, 0, 0, 0);
  t = time(0);
  if ((&input[input_idx]) == 0)
  {
    input_idx = "";
  }
  if (flags & 0x8)
  {
    tmp_idx = xstrdup(input);
  }
  else
    tmp_idx = format_expand_time(ft, input, t);
  status_message_clear(c);
  status_prompt_clear(c);
  if (c->status.old_status == 0)
  {
    c->status.old_status = xmalloc(sizeof(*c->status.old_status));
    memcpy(c->status.old_status, &c->status.status, sizeof(*c->status.old_status));
    screen_init(&c->status.status, c->tty.sx, 1, 0);
  }
  c->prompt_string = format_expand_time(ft, msg, t);
  c->prompt_buffer = utf8_fromcstr(tmp);
  c->prompt_index = utf8_strlen(c->prompt_buffer);
  c->prompt_inputcb = inputcb;
  c->prompt_freecb = freecb;
  c->prompt_data = data;
  c->prompt_hindex = 0;
  c->prompt_flags = flags;
  c->prompt_mode = PROMPT_ENTRY;
  if ((~flags) & 0x4)
  {
    c->tty.flags |= 0x1 | 0x2;
  }
  c->flags |= 0x10;
  if ((flags & 0x4) && (tmp[tmp_idx] != '\0'))
  {
    xasprintf(&cp, "=%s", tmp);
    c->prompt_inputcb(c, c->prompt_data, cp, 0);
    free(cp);
  }
  free(tmp);
  format_free(ft);
}


/*** DEPENDENCIES:
size_t utf8_strlen(const struct utf8_data *s)
{
  size_t i;
  for (i = 0; s[i].size != 0; i += 1)
  {
    ;
  }

  return i;
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
struct utf8_data *utf8_fromcstr(const char *src)
{
  unsigned int src_idx = 0;
  struct utf8_data *dst;
  unsigned int dst_idx = 0;
  size_t n;
  enum utf8_state more;
  dst_idx = 0;
  n = 0;
  while (src[src_idx] != '\0')
  {
    dst_idx = xreallocarray(dst_idx, n + 1, sizeof(*dst_idx));
    if ((more = utf8_open(&dst[n + dst_idx], *(&src[src_idx]))) == UTF8_MORE)
    {
      while (((*(++(&src[src_idx]))) != '\0') && (more == UTF8_MORE))
      {
        more = utf8_append(&dst[n + dst_idx], *(&src[src_idx]));
      }

      if (more == UTF8_DONE)
      {
        n += 1;
        continue;
      }
      src_idx -= dst[n + dst_idx].have;
    }
    utf8_set(&dst[n + dst_idx], *(&src[src_idx]));
    n += 1;
    src_idx += 1;
  }

  dst_idx = xreallocarray(dst_idx, n + 1, sizeof(*dst_idx));
  dst[n + dst_idx].size = 0;
  return dst;
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
void status_prompt_clear(struct client *c)
{
  if (c->prompt_string == 0)
  {
    return;
  }
  if ((c->prompt_freecb != 0) && (c->prompt_data != 0))
  {
    c->prompt_freecb(c->prompt_data);
  }
  free(c->prompt_string);
  c->prompt_string = 0;
  free(c->prompt_buffer);
  c->prompt_buffer = 0;
  c->tty.flags &= ~(0x1 | 0x2);
  c->flags |= 0x8;
  screen_reinit(&c->status.status);
}


----------------------------
pub time: Time
----------------------------
typedef int (*prompt_input_cb)(struct client *, void *, const char *, int)
----------------------------
void status_message_clear(struct client *c)
{
  if (c->message_string == 0)
  {
    return;
  }
  free(c->message_string);
  c->message_string = 0;
  if (c->prompt_string == 0)
  {
    c->tty.flags &= ~(0x1 | 0x2);
  }
  c->flags |= 0x8;
  screen_reinit(&c->status.status);
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
typedef void (*prompt_free_cb)(void *)
----------------------------
char *format_expand_time(struct format_tree *ft, const char *fmt, time_t t)
{
  struct tm *tm;
  unsigned int tm_idx = 0;
  char s[2048];
  if ((fmt == 0) || ((*fmt) == '\0'))
  {
    return xstrdup("");
  }
  tm_idx = localtime(&t);
  if (strftime(s, sizeof(s), fmt, tm) == 0)
  {
    return xstrdup("");
  }
  return format_expand(ft, s);
}


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
None
----------------------------
***/


