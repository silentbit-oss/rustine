static void screen_free_titles(struct screen *s)
{
  struct screen_title_entry *title_entry;
  unsigned int title_entry_idx = 0;
  if (s->titles == 0)
  {
    return;
  }
  while ((title_entry_idx = s->titles->tqh_first) != 0)
  {
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

  free(s->titles);
  s->titles = 0;
}


/*** DEPENDENCIES:
None
----------------------------
***/


void screen_free(struct screen *s)
{
  free(s->tabs);
  free(s->title);
  free(s->ccolour);
  grid_destroy(s->grid);
  screen_free_titles(s);
}


/*** DEPENDENCIES:
static void screen_free_titles(struct screen *s)
{
  struct screen_title_entry *title_entry;
  unsigned int title_entry_idx = 0;
  if (s->titles == 0)
  {
    return;
  }
  while ((title_entry_idx = s->titles->tqh_first) != 0)
  {
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

  free(s->titles);
  s->titles = 0;
}


----------------------------
void grid_destroy(struct grid *gd)
{
  grid_free_lines(gd, 0, gd->hsize + gd->sy);
  free(gd->linedata);
  free(gd);
}


----------------------------
None
----------------------------
***/


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


void screen_set_cursor_colour(struct screen *s, const char *colour)
{
  free(s->ccolour);
  s->ccolour = xstrdup(colour);
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
None
----------------------------
***/


void screen_set_title(struct screen *s, const char *title)
{
  free(s->title);
  utf8_stravis(&s->title, title, ((0x01 | 0x02) | 0x08) | 0x10);
}


/*** DEPENDENCIES:
int utf8_stravis(char **dst, const char *src, int flag)
{
  char *buf;
  unsigned int buf_idx = 0;
  int len;
  buf_idx = xreallocarray(0, 4, strlen(src) + 1);
  len = utf8_strvis(buf, src, strlen(src), flag);
  *dst = xrealloc(buf, len + 1);
  return len;
}


----------------------------
None
----------------------------
***/


static void screen_reflow(struct screen *s, u_int new_x)
{
  grid_reflow(s->grid, new_x, &s->cy);
}


/*** DEPENDENCIES:
void grid_reflow(struct grid *gd, u_int sx, u_int *cursor)
{
  struct grid *target;
  unsigned int target_idx = 0;
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  struct grid_cell gc;
  u_int yy;
  u_int cy;
  u_int width;
  u_int i;
  u_int at;
  u_int first;
  struct timeval start;
  struct timeval tv;
  gettimeofday(&start, 0);
  log_debug("%s: %u lines, new width %u", __func__, gd->hsize + gd->sy, sx);
  cy = gd->hsize + (*cursor);
  target_idx = grid_create(gd->sx, 0, 0);
  for (yy = 0; yy < (gd->hsize + gd->sy); yy += 1)
  {
    helper_grid_reflow_1(&gl_idx, &width, &i, &at, &first, gd, sx, target, gl, gc, yy, cy);
  }

  if (target->sy < gd->sy)
  {
    grid_reflow_add(target, gd->sy - target->sy);
  }
  gd->hsize = target->sy - gd->sy;
  free(gd->linedata);
  gd->linedata = target->linedata;
  free(target);
  if (gd->hscrolled > gd->hsize)
  {
    gd->hscrolled = gd->hsize;
  }
  if (cy < gd->hsize)
  {
    *cursor = 0;
  }
  else
    *cursor = cy - gd->hsize;
  gettimeofday(&tv, 0);
  do
  {
    (&tv)->tv_sec = (&tv)->tv_sec - (&start)->tv_sec;
    (&tv)->tv_usec = (&tv)->tv_usec - (&start)->tv_usec;
    if ((&tv)->tv_usec < 0)
    {
      (&tv)->tv_sec -= 1;
      (&tv)->tv_usec += 1000000;
    }
  }
  while (0);
  log_debug("%s: now %u lines (in %llu.%06u seconds)", __func__, gd->hsize + gd->sy, (unsigned long long) tv.tv_sec, (u_int) tv.tv_usec);
}


----------------------------
None
----------------------------
***/


// hint:  ['needed_ref is a mutable refrence to u_int', 'available_ref is a mutable refrence to u_int', 'i_ref is a mutable refrence to u_int']
void helper_screen_resize_y_1(u_int * const needed_ref, u_int * const available_ref, u_int * const i_ref, struct screen * const s, u_int sy, struct grid * const gd, u_int oldy)
{
  u_int needed = *needed_ref;
  u_int available = *available_ref;
  u_int i = *i_ref;
  needed = sy - oldy;
  available = gd->hscrolled;
  if ((gd->flags & 0x1) && (available > 0))
  {
    if (available > needed)
    {
      available = needed;
    }
    gd->hscrolled -= available;
    gd->hsize -= available;
    s->cy += available;
  }
  else
    available = 0;
  needed -= available;
  for (i = (gd->hsize + sy) - needed; i < (gd->hsize + sy); i += 1)
  {
    memset(&gd->linedata[i], 0, sizeof(gd->linedata[i]));
  }

  *needed_ref = needed;
  *available_ref = available;
  *i_ref = i;
}


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
***/


// hint:  ['needed_ref is a mutable refrence to u_int', 'available_ref is a mutable refrence to u_int']
void helper_screen_resize_y_2(u_int * const needed_ref, u_int * const available_ref, struct screen * const s, u_int sy, struct grid * const gd, u_int oldy)
{
  u_int needed = *needed_ref;
  u_int available = *available_ref;
  needed = oldy - sy;
  available = (oldy - 1) - s->cy;
  if (available > 0)
  {
    if (available > needed)
    {
      available = needed;
    }
    grid_view_delete_lines(gd, oldy - available, available, 8);
  }
  needed -= available;
  available = s->cy;
  if (gd->flags & 0x1)
  {
    gd->hscrolled += needed;
    gd->hsize += needed;
  }
  else
    if ((needed > 0) && (available > 0))
  {
    if (available > needed)
    {
      available = needed;
    }
    grid_view_delete_lines(gd, 0, available, 8);
  }
  s->cy -= needed;
  *needed_ref = needed;
  *available_ref = available;
}


/*** DEPENDENCIES:
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


static void screen_resize_y(struct screen *s, u_int sy)
{
  struct grid *gd = s->grid;
  u_int needed;
  u_int available;
  u_int oldy;
  u_int i;
  if (sy == 0)
  {
    fatalx("zero size");
  }
  oldy = s->grid->sy;
  if (sy < oldy)
  {
    helper_screen_resize_y_2(&needed, &available, s, sy, gd, oldy);
  }
  gd->linedata = xreallocarray(gd->linedata, gd->hsize + sy, sizeof(*gd->linedata));
  if (sy > oldy)
  {
    helper_screen_resize_y_1(&needed, &available, &i, s, sy, gd, oldy);
  }
  gd->sy = sy;
  s->rupper = 0;
  s->rlower = s->grid->sy - 1;
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
void helper_screen_resize_y_1(u_int * const needed_ref, u_int * const available_ref, u_int * const i_ref, struct screen * const s, u_int sy, struct grid * const gd, u_int oldy)
{
  u_int needed = *needed_ref;
  u_int available = *available_ref;
  u_int i = *i_ref;
  needed = sy - oldy;
  available = gd->hscrolled;
  if ((gd->flags & 0x1) && (available > 0))
  {
    if (available > needed)
    {
      available = needed;
    }
    gd->hscrolled -= available;
    gd->hsize -= available;
    s->cy += available;
  }
  else
    available = 0;
  needed -= available;
  for (i = (gd->hsize + sy) - needed; i < (gd->hsize + sy); i += 1)
  {
    memset(&gd->linedata[i], 0, sizeof(gd->linedata[i]));
  }

  *needed_ref = needed;
  *available_ref = available;
  *i_ref = i;
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
void helper_screen_resize_y_2(u_int * const needed_ref, u_int * const available_ref, struct screen * const s, u_int sy, struct grid * const gd, u_int oldy)
{
  u_int needed = *needed_ref;
  u_int available = *available_ref;
  needed = oldy - sy;
  available = (oldy - 1) - s->cy;
  if (available > 0)
  {
    if (available > needed)
    {
      available = needed;
    }
    grid_view_delete_lines(gd, oldy - available, available, 8);
  }
  needed -= available;
  available = s->cy;
  if (gd->flags & 0x1)
  {
    gd->hscrolled += needed;
    gd->hsize += needed;
  }
  else
    if ((needed > 0) && (available > 0))
  {
    if (available > needed)
    {
      available = needed;
    }
    grid_view_delete_lines(gd, 0, available, 8);
  }
  s->cy -= needed;
  *needed_ref = needed;
  *available_ref = available;
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
void fatal(const char *msg, ...)
{
  char *fmt;
  va_list ap;
  __builtin_va_start(ap);
  if (asprintf(&fmt, "fatal: %s: %s", msg, strerror(errno)) == (-1))
  {
    exit(1);
  }
  log_vwrite(fmt, ap);
  ;
  exit(1);
}


----------------------------
None
----------------------------
***/


static void screen_resize_x(struct screen *s, u_int sx)
{
  struct grid *gd = s->grid;
  if (sx == 0)
  {
    fatalx("zero size");
  }
  if (s->cx >= sx)
  {
    s->cx = sx - 1;
  }
  gd->sx = sx;
}


/*** DEPENDENCIES:
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
None
----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
static void screen_reflow(struct screen *s, u_int new_x)
{
  grid_reflow(s->grid, new_x, &s->cy);
}


----------------------------
static void screen_resize_y(struct screen *s, u_int sy)
{
  struct grid *gd = s->grid;
  u_int needed;
  u_int available;
  u_int oldy;
  u_int i;
  if (sy == 0)
  {
    fatalx("zero size");
  }
  oldy = s->grid->sy;
  if (sy < oldy)
  {
    helper_screen_resize_y_2(&needed, &available, s, sy, gd, oldy);
  }
  gd->linedata = xreallocarray(gd->linedata, gd->hsize + sy, sizeof(*gd->linedata));
  if (sy > oldy)
  {
    helper_screen_resize_y_1(&needed, &available, &i, s, sy, gd, oldy);
  }
  gd->sy = sy;
  s->rupper = 0;
  s->rlower = s->grid->sy - 1;
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
static void screen_resize_x(struct screen *s, u_int sx)
{
  struct grid *gd = s->grid;
  if (sx == 0)
  {
    fatalx("zero size");
  }
  if (s->cx >= sx)
  {
    s->cx = sx - 1;
  }
  gd->sx = sx;
}


----------------------------
None
----------------------------
***/


void screen_set_cursor_style(struct screen *s, u_int style)
{
  if (style <= 6)
  {
    s->cstyle = style;
  }
}


/*** DEPENDENCIES:
None
----------------------------
***/


void screen_clear_selection(struct screen *s)
{
  struct screen_sel *sel = &s->sel;
  sel->flag = 0;
  sel->hidden = 0;
  sel->lineflag = LINE_SEL_NONE;
}


/*** DEPENDENCIES:
struct screen_sel
{
  int flag;
  int hidden;
  int rectflag;
  enum 
  {
    LINE_SEL_NONE,
    LINE_SEL_LEFT_RIGHT,
    LINE_SEL_RIGHT_LEFT
  } lineflag;
  int modekeys;
  u_int sx;
  u_int sy;
  u_int ex;
  u_int ey;
  struct grid_cell cell;
}
----------------------------
None
----------------------------
***/


void screen_hide_selection(struct screen *s)
{
  struct screen_sel *sel = &s->sel;
  sel->hidden = 1;
}


/*** DEPENDENCIES:
struct screen_sel
{
  int flag;
  int hidden;
  int rectflag;
  enum 
  {
    LINE_SEL_NONE,
    LINE_SEL_LEFT_RIGHT,
    LINE_SEL_RIGHT_LEFT
  } lineflag;
  int modekeys;
  u_int sx;
  u_int sy;
  u_int ex;
  u_int ey;
  struct grid_cell cell;
}
----------------------------
None
----------------------------
***/


int helper_screen_check_selection_1(u_int px, u_int py, struct screen_sel * const sel)
{
  if (sel->sy < sel->ey)
  {
    if ((py < sel->sy) || (py > sel->ey))
    {
      return 0;
    }
  }
  else
    if (sel->sy > sel->ey)
  {
    if ((py > sel->sy) || (py < sel->ey))
    {
      return 0;
    }
  }
  else
  {
    if (py != sel->sy)
    {
      return 0;
    }
  }
  if (sel->ex < sel->sx)
  {
    if (px < sel->ex)
    {
      return 0;
    }
    if (px > sel->sx)
    {
      return 0;
    }
  }
  else
  {
    if (px < sel->sx)
    {
      return 0;
    }
    if (px > sel->ex)
    {
      return 0;
    }
  }
}


/*** DEPENDENCIES:
struct screen_sel
{
  int flag;
  int hidden;
  int rectflag;
  enum 
  {
    LINE_SEL_NONE,
    LINE_SEL_LEFT_RIGHT,
    LINE_SEL_RIGHT_LEFT
  } lineflag;
  int modekeys;
  u_int sx;
  u_int sy;
  u_int ex;
  u_int ey;
  struct grid_cell cell;
}
----------------------------
None
----------------------------
***/


// hint:  ['xx_ref is a mutable refrence to u_int']
int helper_screen_check_selection_2(u_int * const xx_ref, u_int px, u_int py, struct screen_sel * const sel)
{
  u_int xx = *xx_ref;
  if (sel->sy < sel->ey)
  {
    if ((py < sel->sy) || (py > sel->ey))
    {
      return 0;
    }
    if ((py == sel->sy) && (px < sel->sx))
    {
      return 0;
    }
    if ((py == sel->ey) && (px > sel->ex))
    {
      return 0;
    }
  }
  else
    if (sel->sy > sel->ey)
  {
    if ((py > sel->sy) || (py < sel->ey))
    {
      return 0;
    }
    if ((py == sel->ey) && (px < sel->ex))
    {
      return 0;
    }
    if (sel->modekeys == 0)
    {
      xx = sel->sx - 1;
    }
    else
      xx = sel->sx;
    if ((py == sel->sy) && ((sel->sx == 0) || (px > xx)))
    {
      return 0;
    }
  }
  else
  {
    if (py != sel->sy)
    {
      return 0;
    }
    if (sel->ex < sel->sx)
    {
      if (sel->modekeys == 0)
      {
        xx = sel->sx - 1;
      }
      else
        xx = sel->sx;
      if ((px > xx) || (px < sel->ex))
      {
        return 0;
      }
    }
    else
    {
      if ((px < sel->sx) || (px > sel->ex))
      {
        return 0;
      }
    }
  }
  *xx_ref = xx;
}


/*** DEPENDENCIES:
struct screen_sel
{
  int flag;
  int hidden;
  int rectflag;
  enum 
  {
    LINE_SEL_NONE,
    LINE_SEL_LEFT_RIGHT,
    LINE_SEL_RIGHT_LEFT
  } lineflag;
  int modekeys;
  u_int sx;
  u_int sy;
  u_int ex;
  u_int ey;
  struct grid_cell cell;
}
----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
void screen_clear_selection(struct screen *s)
{
  struct screen_sel *sel = &s->sel;
  sel->flag = 0;
  sel->hidden = 0;
  sel->lineflag = LINE_SEL_NONE;
}


----------------------------
static void screen_free_titles(struct screen *s)
{
  struct screen_title_entry *title_entry;
  unsigned int title_entry_idx = 0;
  if (s->titles == 0)
  {
    return;
  }
  while ((title_entry_idx = s->titles->tqh_first) != 0)
  {
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

  free(s->titles);
  s->titles = 0;
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
void grid_clear_lines(struct grid *gd, u_int py, u_int ny, u_int bg)
{
  u_int yy;
  if (ny == 0)
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
  for (yy = py; yy < (py + ny); yy += 1)
  {
    grid_free_line(gd, yy);
    grid_empty_line(gd, yy, bg);
  }

}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
struct grid *grid_create(u_int sx, u_int sy, u_int hlimit)
{
  struct grid *gd;
  unsigned int gd_idx = 0;
  gd_idx = xmalloc(sizeof(*gd_idx));
  gd->sx = sx;
  gd->sy = sy;
  gd->flags = 0x1;
  gd->hscrolled = 0;
  gd->hsize = 0;
  gd->hlimit = hlimit;
  if (gd->sy != 0)
  {
    gd->linedata = xcalloc(gd->sy, sizeof(*gd->linedata));
  }
  else
    gd->linedata = 0;
  return gd;
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


/*** DEPENDENCIES:
int helper_screen_check_selection_2(u_int * const xx_ref, u_int px, u_int py, struct screen_sel * const sel)
{
  u_int xx = *xx_ref;
  if (sel->sy < sel->ey)
  {
    if ((py < sel->sy) || (py > sel->ey))
    {
      return 0;
    }
    if ((py == sel->sy) && (px < sel->sx))
    {
      return 0;
    }
    if ((py == sel->ey) && (px > sel->ex))
    {
      return 0;
    }
  }
  else
    if (sel->sy > sel->ey)
  {
    if ((py > sel->sy) || (py < sel->ey))
    {
      return 0;
    }
    if ((py == sel->ey) && (px < sel->ex))
    {
      return 0;
    }
    if (sel->modekeys == 0)
    {
      xx = sel->sx - 1;
    }
    else
      xx = sel->sx;
    if ((py == sel->sy) && ((sel->sx == 0) || (px > xx)))
    {
      return 0;
    }
  }
  else
  {
    if (py != sel->sy)
    {
      return 0;
    }
    if (sel->ex < sel->sx)
    {
      if (sel->modekeys == 0)
      {
        xx = sel->sx - 1;
      }
      else
        xx = sel->sx;
      if ((px > xx) || (px < sel->ex))
      {
        return 0;
      }
    }
    else
    {
      if ((px < sel->sx) || (px > sel->ex))
      {
        return 0;
      }
    }
  }
  *xx_ref = xx;
}


----------------------------
int helper_screen_check_selection_1(u_int px, u_int py, struct screen_sel * const sel)
{
  if (sel->sy < sel->ey)
  {
    if ((py < sel->sy) || (py > sel->ey))
    {
      return 0;
    }
  }
  else
    if (sel->sy > sel->ey)
  {
    if ((py > sel->sy) || (py < sel->ey))
    {
      return 0;
    }
  }
  else
  {
    if (py != sel->sy)
    {
      return 0;
    }
  }
  if (sel->ex < sel->sx)
  {
    if (px < sel->ex)
    {
      return 0;
    }
    if (px > sel->sx)
    {
      return 0;
    }
  }
  else
  {
    if (px < sel->sx)
    {
      return 0;
    }
    if (px > sel->ex)
    {
      return 0;
    }
  }
}


----------------------------
struct screen_sel
{
  int flag;
  int hidden;
  int rectflag;
  enum 
  {
    LINE_SEL_NONE,
    LINE_SEL_LEFT_RIGHT,
    LINE_SEL_RIGHT_LEFT
  } lineflag;
  int modekeys;
  u_int sx;
  u_int sy;
  u_int ex;
  u_int ey;
  struct grid_cell cell;
}
----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
void screen_set_title(struct screen *s, const char *title)
{
  free(s->title);
  utf8_stravis(&s->title, title, ((0x01 | 0x02) | 0x08) | 0x10);
}


----------------------------
None
----------------------------
***/


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
struct screen_sel
{
  int flag;
  int hidden;
  int rectflag;
  enum 
  {
    LINE_SEL_NONE,
    LINE_SEL_LEFT_RIGHT,
    LINE_SEL_RIGHT_LEFT
  } lineflag;
  int modekeys;
  u_int sx;
  u_int sy;
  u_int ex;
  u_int ey;
  struct grid_cell cell;
}
----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
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


