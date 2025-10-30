void layout_free_cell(struct layout_cell *lc)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  switch (lc->type)
  {
    case LAYOUT_LEFTRIGHT:

    case LAYOUT_TOPBOTTOM:
    {
      while (!((&lc->cells)->tqh_first == 0))
      {
        lcchild_idx = (&lc->cells)->tqh_first;
        do
        {
          if (lcchild->entry.tqe_next != 0)
          {
            lcchild->entry.tqe_next->entry.tqe_prev = lcchild->entry.tqe_prev;
          }
          else
            (&lc->cells)->tqh_last = lcchild->entry.tqe_prev;
          *lcchild->entry.tqe_prev = lcchild->entry.tqe_next;
          ;
          ;
        }
        while (0);
        layout_free_cell(lcchild);
      }

      break;
    }

    case LAYOUT_WINDOWPANE:
    {
      if (lc->wp != 0)
      {
        lc->wp->layout_cell = 0;
      }
      break;
    }

  }

  free(lc);
}


/*** DEPENDENCIES:
None
----------------------------
***/


static int layout_need_status(struct layout_cell *lc, int at_top)
{
  struct layout_cell *first_lc;
  unsigned int first_lc_idx = 0;
  if (lc->parent)
  {
    if (lc->parent->type == LAYOUT_LEFTRIGHT)
    {
      return layout_need_status(lc->parent, at_top);
    }
    if (at_top)
    {
      first_lc_idx = (&lc->parent->cells)->tqh_first;
    }
    else
      first_lc_idx = *((struct layout_cells *) (&lc->parent->cells)->tqh_last)->tqh_last;
    if (lc == (&first_lc[first_lc_idx]))
    {
      return layout_need_status(lc->parent, at_top);
    }
    return 0;
  }
  return 1;
}


/*** DEPENDENCIES:
None
----------------------------
***/


// hint:  ['lc_idx_ref is a mutable refrence to unsigned int', 'sx_ref is a mutable refrence to u_int', 'sy_ref is a mutable refrence to u_int', 'shift_ref is a mutable refrence to int']
void helper_layout_fix_panes_1(unsigned int * const lc_idx_ref, u_int * const sx_ref, u_int * const sy_ref, int * const shift_ref, u_int wsx, u_int wsy, struct window_pane * const wp, struct layout_cell * const lc, int status, int at_top)
{
  unsigned int lc_idx = *lc_idx_ref;
  u_int sx = *sx_ref;
  u_int sy = *sy_ref;
  int shift = *shift_ref;
  if ((lc_idx = wp->layout_cell) == 0)
  {
    continue;
  }
  if (status != 0)
  {
    shift = layout_need_status(lc, at_top);
  }
  else
    shift = 0;
  wp->xoff = lc->xoff;
  wp->yoff = lc->yoff;
  if (shift && at_top)
  {
    wp->yoff += 1;
  }
  if ((lc->xoff >= wsx) || ((lc->xoff + lc->sx) < wsx))
  {
    sx = lc->sx;
  }
  else
  {
    sx = wsx - lc->xoff;
    if (sx < 1)
    {
      sx = lc->sx;
    }
  }
  if ((lc->yoff >= wsy) || ((lc->yoff + lc->sy) < wsy))
  {
    sy = lc->sy;
  }
  else
  {
    sy = wsy - lc->yoff;
    if (sy < 2)
    {
      sy = lc->sy;
    }
  }
  if (shift)
  {
    sy -= 1;
  }
  window_pane_resize(wp, sx, sy);
  *lc_idx_ref = lc_idx;
  *sx_ref = sx;
  *sy_ref = sy;
  *shift_ref = shift;
}


/*** DEPENDENCIES:
void window_pane_resize(struct window_pane *wp, u_int sx, u_int sy)
{
  if ((sx == wp->sx) && (sy == wp->sy))
  {
    return;
  }
  wp->sx = sx;
  wp->sy = sy;
  screen_resize(&wp->base, sx, sy, wp->saved_grid == 0);
  if (wp->mode != 0)
  {
    wp->mode->resize(wp, sx, sy);
  }
  wp->flags |= 0x8;
}


----------------------------
static int layout_need_status(struct layout_cell *lc, int at_top)
{
  struct layout_cell *first_lc;
  unsigned int first_lc_idx = 0;
  if (lc->parent)
  {
    if (lc->parent->type == LAYOUT_LEFTRIGHT)
    {
      return layout_need_status(lc->parent, at_top);
    }
    if (at_top)
    {
      first_lc_idx = (&lc->parent->cells)->tqh_first;
    }
    else
      first_lc_idx = *((struct layout_cells *) (&lc->parent->cells)->tqh_last)->tqh_last;
    if (lc == (&first_lc[first_lc_idx]))
    {
      return layout_need_status(lc->parent, at_top);
    }
    return 0;
  }
  return 1;
}


----------------------------
None
----------------------------
***/


void layout_fix_panes(struct window *w, u_int wsx, u_int wsy)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  u_int sx;
  u_int sy;
  int shift;
  int status;
  int at_top;
  status = options_get_number(w->options, "pane-border-status");
  at_top = status == 1;
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    helper_layout_fix_panes_1(&lc_idx, &sx, &sy, &shift, wsx, wsy, wp, lc, status, at_top);
  }

}


/*** DEPENDENCIES:
void helper_layout_fix_panes_1(unsigned int * const lc_idx_ref, u_int * const sx_ref, u_int * const sy_ref, int * const shift_ref, u_int wsx, u_int wsy, struct window_pane * const wp, struct layout_cell * const lc, int status, int at_top)
{
  unsigned int lc_idx = *lc_idx_ref;
  u_int sx = *sx_ref;
  u_int sy = *sy_ref;
  int shift = *shift_ref;
  if ((lc_idx = wp->layout_cell) == 0)
  {
    continue;
  }
  if (status != 0)
  {
    shift = layout_need_status(lc, at_top);
  }
  else
    shift = 0;
  wp->xoff = lc->xoff;
  wp->yoff = lc->yoff;
  if (shift && at_top)
  {
    wp->yoff += 1;
  }
  if ((lc->xoff >= wsx) || ((lc->xoff + lc->sx) < wsx))
  {
    sx = lc->sx;
  }
  else
  {
    sx = wsx - lc->xoff;
    if (sx < 1)
    {
      sx = lc->sx;
    }
  }
  if ((lc->yoff >= wsy) || ((lc->yoff + lc->sy) < wsy))
  {
    sy = lc->sy;
  }
  else
  {
    sy = wsy - lc->yoff;
    if (sy < 2)
    {
      sy = lc->sy;
    }
  }
  if (shift)
  {
    sy -= 1;
  }
  window_pane_resize(wp, sx, sy);
  *lc_idx_ref = lc_idx;
  *sx_ref = sx;
  *sy_ref = sy;
  *shift_ref = shift;
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


void layout_free(struct window *w)
{
  layout_free_cell(w->layout_root);
}


/*** DEPENDENCIES:
void layout_free_cell(struct layout_cell *lc)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  switch (lc->type)
  {
    case LAYOUT_LEFTRIGHT:

    case LAYOUT_TOPBOTTOM:
    {
      while (!((&lc->cells)->tqh_first == 0))
      {
        lcchild_idx = (&lc->cells)->tqh_first;
        do
        {
          if (lcchild->entry.tqe_next != 0)
          {
            lcchild->entry.tqe_next->entry.tqe_prev = lcchild->entry.tqe_prev;
          }
          else
            (&lc->cells)->tqh_last = lcchild->entry.tqe_prev;
          *lcchild->entry.tqe_prev = lcchild->entry.tqe_next;
          ;
          ;
        }
        while (0);
        layout_free_cell(lcchild);
      }

      break;
    }

    case LAYOUT_WINDOWPANE:
    {
      if (lc->wp != 0)
      {
        lc->wp->layout_cell = 0;
      }
      break;
    }

  }

  free(lc);
}


----------------------------
None
----------------------------
***/


void layout_make_leaf(struct layout_cell *lc, struct window_pane *wp)
{
  lc->type = LAYOUT_WINDOWPANE;
  do
  {
    (&lc->cells)->tqh_first = 0;
    (&lc->cells)->tqh_last = &(&lc->cells)->tqh_first;
  }
  while (0);
  wp->layout_cell = lc;
  lc->wp = wp;
}


/*** DEPENDENCIES:
None
----------------------------
***/


static u_int layout_resize_check(struct window *w, struct layout_cell *lc, enum layout_type type)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  u_int available;
  u_int minimum;
  if (lc->type == LAYOUT_WINDOWPANE)
  {
    minimum = 2;
    if (type == LAYOUT_LEFTRIGHT)
    {
      available = lc->sx;
    }
    else
    {
      available = lc->sy;
      minimum += layout_need_status(lc, options_get_number(w->options, "pane-border-status") == 1);
    }
    if (available > minimum)
    {
      available -= minimum;
    }
    else
      available = 0;
  }
  else
    if (lc->type == type)
  {
    available = 0;
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      available += layout_resize_check(w, lcchild, type);
    }

  }
  else
  {
    minimum = 4294967295U;
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      available = layout_resize_check(w, lcchild, type);
      if (available < minimum)
      {
        minimum = available;
      }
    }

    available = minimum;
  }
  return available;
}


/*** DEPENDENCIES:
static int layout_need_status(struct layout_cell *lc, int at_top)
{
  struct layout_cell *first_lc;
  unsigned int first_lc_idx = 0;
  if (lc->parent)
  {
    if (lc->parent->type == LAYOUT_LEFTRIGHT)
    {
      return layout_need_status(lc->parent, at_top);
    }
    if (at_top)
    {
      first_lc_idx = (&lc->parent->cells)->tqh_first;
    }
    else
      first_lc_idx = *((struct layout_cells *) (&lc->parent->cells)->tqh_last)->tqh_last;
    if (lc == (&first_lc[first_lc_idx]))
    {
      return layout_need_status(lc->parent, at_top);
    }
    return 0;
  }
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
enum layout_type
{
  LAYOUT_LEFTRIGHT,
  LAYOUT_TOPBOTTOM,
  LAYOUT_WINDOWPANE
}
----------------------------
None
----------------------------
***/


void layout_resize_adjust(struct window *w, struct layout_cell *lc, enum layout_type type, int change)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  if (type == LAYOUT_LEFTRIGHT)
  {
    lc->sx += change;
  }
  else
    lc->sy += change;
  if (type == LAYOUT_WINDOWPANE)
  {
    return;
  }
  if (lc->type != type)
  {
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      layout_resize_adjust(w, lcchild, type, change);
    }

    return;
  }
  while (change != 0)
  {
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      if (change == 0)
      {
        break;
      }
      if (change > 0)
      {
        layout_resize_adjust(w, lcchild, type, 1);
        change -= 1;
        continue;
      }
      if (layout_resize_check(w, lcchild, type) > 0)
      {
        layout_resize_adjust(w, lcchild, type, -1);
        change += 1;
      }
    }

  }

}


/*** DEPENDENCIES:
static u_int layout_resize_check(struct window *w, struct layout_cell *lc, enum layout_type type)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  u_int available;
  u_int minimum;
  if (lc->type == LAYOUT_WINDOWPANE)
  {
    minimum = 2;
    if (type == LAYOUT_LEFTRIGHT)
    {
      available = lc->sx;
    }
    else
    {
      available = lc->sy;
      minimum += layout_need_status(lc, options_get_number(w->options, "pane-border-status") == 1);
    }
    if (available > minimum)
    {
      available -= minimum;
    }
    else
      available = 0;
  }
  else
    if (lc->type == type)
  {
    available = 0;
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      available += layout_resize_check(w, lcchild, type);
    }

  }
  else
  {
    minimum = 4294967295U;
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      available = layout_resize_check(w, lcchild, type);
      if (available < minimum)
      {
        minimum = available;
      }
    }

    available = minimum;
  }
  return available;
}


----------------------------
enum layout_type
{
  LAYOUT_LEFTRIGHT,
  LAYOUT_TOPBOTTOM,
  LAYOUT_WINDOWPANE
}
----------------------------
None
----------------------------
***/


int layout_spread_cell(struct window *w, struct layout_cell *parent)
{
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  u_int number;
  u_int each;
  u_int size;
  int change;
  int changed;
  number = 0;
  for (lc_idx = (&parent->cells)->tqh_first; (&lc[lc_idx]) != 0; lc_idx = lc_idx->entry.tqe_next)
  {
    number += 1;
  }

  if (number <= 1)
  {
    return 0;
  }
  if (parent->type == LAYOUT_LEFTRIGHT)
  {
    size = parent->sx;
  }
  else
    if (parent->type == LAYOUT_TOPBOTTOM)
  {
    size = parent->sy;
  }
  else
    return 0;
  each = (size - (number - 1)) / number;
  changed = 0;
  for (lc_idx = (&parent->cells)->tqh_first; (&lc[lc_idx]) != 0; lc_idx = lc_idx->entry.tqe_next)
  {
    if (lc->entry.tqe_next == 0)
    {
      each = size - ((each + 1) * (number - 1));
    }
    change = 0;
    if (parent->type == LAYOUT_LEFTRIGHT)
    {
      change = each - ((int) lc->sx);
      layout_resize_adjust(w, lc, LAYOUT_LEFTRIGHT, change);
    }
    else
      if (parent->type == LAYOUT_TOPBOTTOM)
    {
      change = each - ((int) lc->sy);
      layout_resize_adjust(w, lc, LAYOUT_TOPBOTTOM, change);
    }
    if (change != 0)
    {
      changed = 1;
    }
  }

  return changed;
}


/*** DEPENDENCIES:
void layout_resize_adjust(struct window *w, struct layout_cell *lc, enum layout_type type, int change)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  if (type == LAYOUT_LEFTRIGHT)
  {
    lc->sx += change;
  }
  else
    lc->sy += change;
  if (type == LAYOUT_WINDOWPANE)
  {
    return;
  }
  if (lc->type != type)
  {
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      layout_resize_adjust(w, lcchild, type, change);
    }

    return;
  }
  while (change != 0)
  {
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      if (change == 0)
      {
        break;
      }
      if (change > 0)
      {
        layout_resize_adjust(w, lcchild, type, 1);
        change -= 1;
        continue;
      }
      if (layout_resize_check(w, lcchild, type) > 0)
      {
        layout_resize_adjust(w, lcchild, type, -1);
        change += 1;
      }
    }

  }

}


----------------------------
None
----------------------------
***/


void layout_make_node(struct layout_cell *lc, enum layout_type type)
{
  if (type == LAYOUT_WINDOWPANE)
  {
    fatalx("bad layout type");
  }
  lc->type = type;
  do
  {
    (&lc->cells)->tqh_first = 0;
    (&lc->cells)->tqh_last = &(&lc->cells)->tqh_first;
  }
  while (0);
  if (lc->wp != 0)
  {
    lc->wp->layout_cell = 0;
  }
  lc->wp = 0;
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
enum layout_type
{
  LAYOUT_LEFTRIGHT,
  LAYOUT_TOPBOTTOM,
  LAYOUT_WINDOWPANE
}
----------------------------
None
----------------------------
***/


void layout_print_cell(struct layout_cell *lc, const char *hdr, u_int n)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  const char *type;
  unsigned int type_idx = 0;
  switch (lc->type)
  {
    case LAYOUT_LEFTRIGHT:
    {
      type_idx = "LEFTRIGHT";
      break;
    }

    case LAYOUT_TOPBOTTOM:
    {
      type_idx = "TOPBOTTOM";
      break;
    }

    case LAYOUT_WINDOWPANE:
    {
      type_idx = "WINDOWPANE";
      break;
    }

    default:
    {
      type_idx = "UNKNOWN";
      break;
    }

  }

  log_debug("%s:%*s%p type %s [parent %p] wp=%p [%u,%u %ux%u]", hdr, n, " ", lc, type, lc->parent, lc->wp, lc->xoff, lc->yoff, lc->sx, lc->sy);
  switch (lc->type)
  {
    case LAYOUT_LEFTRIGHT:

    case LAYOUT_TOPBOTTOM:
    {
      for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
      {
        layout_print_cell(lcchild, hdr, n + 1);
      }

      break;
    }

    case LAYOUT_WINDOWPANE:
    {
      break;
    }

  }

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
None
----------------------------
***/


struct layout_cell *layout_create_cell(struct layout_cell *lcparent)
{
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  lc_idx = xmalloc(sizeof(*lc_idx));
  lc->type = LAYOUT_WINDOWPANE;
  lc->parent = lcparent;
  do
  {
    (&lc->cells)->tqh_first = 0;
    (&lc->cells)->tqh_last = &(&lc->cells)->tqh_first;
  }
  while (0);
  lc->sx = 4294967295U;
  lc->sy = 4294967295U;
  lc->xoff = 4294967295U;
  lc->yoff = 4294967295U;
  lc->wp = 0;
  return lc;
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
None
----------------------------
***/


void layout_fix_offsets(struct layout_cell *lc)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  u_int xoff;
  u_int yoff;
  if (lc->type == LAYOUT_LEFTRIGHT)
  {
    xoff = lc->xoff;
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      lcchild->xoff = xoff;
      lcchild->yoff = lc->yoff;
      if (lcchild->type != LAYOUT_WINDOWPANE)
      {
        layout_fix_offsets(lcchild);
      }
      xoff += lcchild->sx + 1;
    }

  }
  else
  {
    yoff = lc->yoff;
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      lcchild->xoff = lc->xoff;
      lcchild->yoff = yoff;
      if (lcchild->type != LAYOUT_WINDOWPANE)
      {
        layout_fix_offsets(lcchild);
      }
      yoff += lcchild->sy + 1;
    }

  }
}


/*** DEPENDENCIES:
None
----------------------------
***/


void layout_set_size(struct layout_cell *lc, u_int sx, u_int sy, u_int xoff, u_int yoff)
{
  lc->sx = sx;
  lc->sy = sy;
  lc->xoff = xoff;
  lc->yoff = yoff;
}


/*** DEPENDENCIES:
None
----------------------------
***/


void helper_layout_destroy_cell_1(struct layout_cell * const lc, struct layout_cell ** const lcroot, unsigned int lc_idx, struct layout_cell * const lcparent)
{
  do
  {
    if (lc->entry.tqe_next != 0)
    {
      lc->entry.tqe_next->entry.tqe_prev = lc->entry.tqe_prev;
    }
    else
      (&lcparent->cells)->tqh_last = lc->entry.tqe_prev;
    *lc->entry.tqe_prev = lc->entry.tqe_next;
    ;
    ;
  }
  while (0);
  lc->parent = lcparent->parent;
  if (lc->parent == 0)
  {
    lc->xoff = 0;
    lc->yoff = 0;
    *lcroot = &lc[lc_idx];
  }
  else
    do
  {
    if ((lc->entry.tqe_next = lcparent->entry.tqe_next) != 0)
    {
      lc->entry.tqe_next->entry.tqe_prev = &lc->entry.tqe_next;
    }
    else
      (&lc->parent->cells)->tqh_last = &lc->entry.tqe_next;
    lc->entry.tqe_prev = lcparent->entry.tqe_prev;
    *lc->entry.tqe_prev = &lc[lc_idx];
    ;
    ;
  }
  while (0);
  layout_free_cell(lcparent);
}


/*** DEPENDENCIES:
void layout_free_cell(struct layout_cell *lc)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  switch (lc->type)
  {
    case LAYOUT_LEFTRIGHT:

    case LAYOUT_TOPBOTTOM:
    {
      while (!((&lc->cells)->tqh_first == 0))
      {
        lcchild_idx = (&lc->cells)->tqh_first;
        do
        {
          if (lcchild->entry.tqe_next != 0)
          {
            lcchild->entry.tqe_next->entry.tqe_prev = lcchild->entry.tqe_prev;
          }
          else
            (&lc->cells)->tqh_last = lcchild->entry.tqe_prev;
          *lcchild->entry.tqe_prev = lcchild->entry.tqe_next;
          ;
          ;
        }
        while (0);
        layout_free_cell(lcchild);
      }

      break;
    }

    case LAYOUT_WINDOWPANE:
    {
      if (lc->wp != 0)
      {
        lc->wp->layout_cell = 0;
      }
      break;
    }

  }

  free(lc);
}


----------------------------
None
----------------------------
***/


// hint:  ['lcparent_idx_ref is a mutable refrence to unsigned int', 'lcnew_idx_ref is a mutable refrence to unsigned int']
void helper_layout_split_pane_1(unsigned int * const lcparent_idx_ref, unsigned int * const lcnew_idx_ref, int insert_before, struct layout_cell * const lc, unsigned int lc_idx, struct layout_cell * const lcparent, struct layout_cell * const lcnew)
{
  unsigned int lcparent_idx = *lcparent_idx_ref;
  unsigned int lcnew_idx = *lcnew_idx_ref;
  lcparent_idx = lc->parent;
  lcnew_idx = layout_create_cell(lcparent);
  if (insert_before)
  {
    do
    {
      lcnew->entry.tqe_prev = lc->entry.tqe_prev;
      lcnew->entry.tqe_next = &lc[lc_idx];
      *lc->entry.tqe_prev = &lcnew[lcnew_idx];
      lc->entry.tqe_prev = &lcnew->entry.tqe_next;
    }
    while (0);
  }
  else
    do
  {
    if ((lcnew->entry.tqe_next = lc->entry.tqe_next) != 0)
    {
      lcnew->entry.tqe_next->entry.tqe_prev = &lcnew->entry.tqe_next;
    }
    else
      (&lcparent->cells)->tqh_last = &lcnew->entry.tqe_next;
    lc->entry.tqe_next = &lcnew[lcnew_idx];
    lcnew->entry.tqe_prev = &lc->entry.tqe_next;
  }
  while (0);
  *lcparent_idx_ref = lcparent_idx;
  *lcnew_idx_ref = lcnew_idx;
}


/*** DEPENDENCIES:
struct layout_cell *layout_create_cell(struct layout_cell *lcparent)
{
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  lc_idx = xmalloc(sizeof(*lc_idx));
  lc->type = LAYOUT_WINDOWPANE;
  lc->parent = lcparent;
  do
  {
    (&lc->cells)->tqh_first = 0;
    (&lc->cells)->tqh_last = &(&lc->cells)->tqh_first;
  }
  while (0);
  lc->sx = 4294967295U;
  lc->sy = 4294967295U;
  lc->xoff = 4294967295U;
  lc->yoff = 4294967295U;
  lc->wp = 0;
  return lc;
}


----------------------------
None
----------------------------
***/


void layout_resize(struct window *w, u_int sx, u_int sy)
{
  struct layout_cell *lc = w->layout_root;
  int xlimit;
  int ylimit;
  int xchange;
  int ychange;
  xchange = sx - w->sx;
  xlimit = layout_resize_check(w, lc, LAYOUT_LEFTRIGHT);
  if ((xchange < 0) && (xchange < (-xlimit)))
  {
    xchange = -xlimit;
  }
  if (xlimit == 0)
  {
    if (sx <= lc->sx)
    {
      xchange = 0;
    }
    else
      xchange = sx - lc->sx;
  }
  if (xchange != 0)
  {
    layout_resize_adjust(w, lc, LAYOUT_LEFTRIGHT, xchange);
  }
  ychange = sy - w->sy;
  ylimit = layout_resize_check(w, lc, LAYOUT_TOPBOTTOM);
  if ((ychange < 0) && (ychange < (-ylimit)))
  {
    ychange = -ylimit;
  }
  if (ylimit == 0)
  {
    if (sy <= lc->sy)
    {
      ychange = 0;
    }
    else
      ychange = sy - lc->sy;
  }
  if (ychange != 0)
  {
    layout_resize_adjust(w, lc, LAYOUT_TOPBOTTOM, ychange);
  }
  layout_fix_offsets(lc);
  layout_fix_panes(w, sx, sy);
}


/*** DEPENDENCIES:
void layout_fix_offsets(struct layout_cell *lc)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  u_int xoff;
  u_int yoff;
  if (lc->type == LAYOUT_LEFTRIGHT)
  {
    xoff = lc->xoff;
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      lcchild->xoff = xoff;
      lcchild->yoff = lc->yoff;
      if (lcchild->type != LAYOUT_WINDOWPANE)
      {
        layout_fix_offsets(lcchild);
      }
      xoff += lcchild->sx + 1;
    }

  }
  else
  {
    yoff = lc->yoff;
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      lcchild->xoff = lc->xoff;
      lcchild->yoff = yoff;
      if (lcchild->type != LAYOUT_WINDOWPANE)
      {
        layout_fix_offsets(lcchild);
      }
      yoff += lcchild->sy + 1;
    }

  }
}


----------------------------
static u_int layout_resize_check(struct window *w, struct layout_cell *lc, enum layout_type type)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  u_int available;
  u_int minimum;
  if (lc->type == LAYOUT_WINDOWPANE)
  {
    minimum = 2;
    if (type == LAYOUT_LEFTRIGHT)
    {
      available = lc->sx;
    }
    else
    {
      available = lc->sy;
      minimum += layout_need_status(lc, options_get_number(w->options, "pane-border-status") == 1);
    }
    if (available > minimum)
    {
      available -= minimum;
    }
    else
      available = 0;
  }
  else
    if (lc->type == type)
  {
    available = 0;
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      available += layout_resize_check(w, lcchild, type);
    }

  }
  else
  {
    minimum = 4294967295U;
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      available = layout_resize_check(w, lcchild, type);
      if (available < minimum)
      {
        minimum = available;
      }
    }

    available = minimum;
  }
  return available;
}


----------------------------
void layout_fix_panes(struct window *w, u_int wsx, u_int wsy)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  u_int sx;
  u_int sy;
  int shift;
  int status;
  int at_top;
  status = options_get_number(w->options, "pane-border-status");
  at_top = status == 1;
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    helper_layout_fix_panes_1(&lc_idx, &sx, &sy, &shift, wsx, wsy, wp, lc, status, at_top);
  }

}


----------------------------
void layout_resize_adjust(struct window *w, struct layout_cell *lc, enum layout_type type, int change)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  if (type == LAYOUT_LEFTRIGHT)
  {
    lc->sx += change;
  }
  else
    lc->sy += change;
  if (type == LAYOUT_WINDOWPANE)
  {
    return;
  }
  if (lc->type != type)
  {
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      layout_resize_adjust(w, lcchild, type, change);
    }

    return;
  }
  while (change != 0)
  {
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      if (change == 0)
      {
        break;
      }
      if (change > 0)
      {
        layout_resize_adjust(w, lcchild, type, 1);
        change -= 1;
        continue;
      }
      if (layout_resize_check(w, lcchild, type) > 0)
      {
        layout_resize_adjust(w, lcchild, type, -1);
        change += 1;
      }
    }

  }

}


----------------------------
None
----------------------------
***/


void layout_init(struct window *w, struct window_pane *wp)
{
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  lc_idx = (w->layout_root = layout_create_cell(0));
  layout_set_size(lc, w->sx, w->sy, 0, 0);
  layout_make_leaf(lc, wp);
  layout_fix_panes(w, w->sx, w->sy);
}


/*** DEPENDENCIES:
void layout_make_leaf(struct layout_cell *lc, struct window_pane *wp)
{
  lc->type = LAYOUT_WINDOWPANE;
  do
  {
    (&lc->cells)->tqh_first = 0;
    (&lc->cells)->tqh_last = &(&lc->cells)->tqh_first;
  }
  while (0);
  wp->layout_cell = lc;
  lc->wp = wp;
}


----------------------------
void layout_fix_panes(struct window *w, u_int wsx, u_int wsy)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  u_int sx;
  u_int sy;
  int shift;
  int status;
  int at_top;
  status = options_get_number(w->options, "pane-border-status");
  at_top = status == 1;
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    helper_layout_fix_panes_1(&lc_idx, &sx, &sy, &shift, wsx, wsy, wp, lc, status, at_top);
  }

}


----------------------------
struct layout_cell *layout_create_cell(struct layout_cell *lcparent)
{
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  lc_idx = xmalloc(sizeof(*lc_idx));
  lc->type = LAYOUT_WINDOWPANE;
  lc->parent = lcparent;
  do
  {
    (&lc->cells)->tqh_first = 0;
    (&lc->cells)->tqh_last = &(&lc->cells)->tqh_first;
  }
  while (0);
  lc->sx = 4294967295U;
  lc->sy = 4294967295U;
  lc->xoff = 4294967295U;
  lc->yoff = 4294967295U;
  lc->wp = 0;
  return lc;
}


----------------------------
void layout_set_size(struct layout_cell *lc, u_int sx, u_int sy, u_int xoff, u_int yoff)
{
  lc->sx = sx;
  lc->sy = sy;
  lc->xoff = xoff;
  lc->yoff = yoff;
}


----------------------------
None
----------------------------
***/


void layout_destroy_cell(struct window *w, struct layout_cell *lc, struct layout_cell **lcroot)
{
  unsigned int lc_idx = 0;
  struct layout_cell *lcother;
  unsigned int lcother_idx = 0;
  struct layout_cell *lcparent;
  unsigned int lcparent_idx = 0;
  lcparent_idx = lc->parent;
  if ((&lcparent[lcparent_idx]) == 0)
  {
    layout_free_cell(lc);
    *lcroot = 0;
    return;
  }
  if ((&lc[lc_idx]) == (&lcparent->cells)->tqh_first)
  {
    lcother_idx = lc->entry.tqe_next;
  }
  else
    lcother_idx = *((struct layout_cells *) lc->entry.tqe_prev)->tqh_last;
  if (lcparent->type == LAYOUT_LEFTRIGHT)
  {
    layout_resize_adjust(w, lcother, lcparent->type, lc->sx + 1);
  }
  else
    layout_resize_adjust(w, lcother, lcparent->type, lc->sy + 1);
  do
  {
    if (lc->entry.tqe_next != 0)
    {
      lc->entry.tqe_next->entry.tqe_prev = lc->entry.tqe_prev;
    }
    else
      (&lcparent->cells)->tqh_last = lc->entry.tqe_prev;
    *lc->entry.tqe_prev = lc->entry.tqe_next;
    ;
    ;
  }
  while (0);
  layout_free_cell(lc);
  lc_idx = (&lcparent->cells)->tqh_first;
  if (lc->entry.tqe_next == 0)
  {
    helper_layout_destroy_cell_1(lc, lcroot, lc_idx, lcparent);
  }
}


/*** DEPENDENCIES:
void layout_free_cell(struct layout_cell *lc)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  switch (lc->type)
  {
    case LAYOUT_LEFTRIGHT:

    case LAYOUT_TOPBOTTOM:
    {
      while (!((&lc->cells)->tqh_first == 0))
      {
        lcchild_idx = (&lc->cells)->tqh_first;
        do
        {
          if (lcchild->entry.tqe_next != 0)
          {
            lcchild->entry.tqe_next->entry.tqe_prev = lcchild->entry.tqe_prev;
          }
          else
            (&lc->cells)->tqh_last = lcchild->entry.tqe_prev;
          *lcchild->entry.tqe_prev = lcchild->entry.tqe_next;
          ;
          ;
        }
        while (0);
        layout_free_cell(lcchild);
      }

      break;
    }

    case LAYOUT_WINDOWPANE:
    {
      if (lc->wp != 0)
      {
        lc->wp->layout_cell = 0;
      }
      break;
    }

  }

  free(lc);
}


----------------------------
void layout_resize_adjust(struct window *w, struct layout_cell *lc, enum layout_type type, int change)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  if (type == LAYOUT_LEFTRIGHT)
  {
    lc->sx += change;
  }
  else
    lc->sy += change;
  if (type == LAYOUT_WINDOWPANE)
  {
    return;
  }
  if (lc->type != type)
  {
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      layout_resize_adjust(w, lcchild, type, change);
    }

    return;
  }
  while (change != 0)
  {
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      if (change == 0)
      {
        break;
      }
      if (change > 0)
      {
        layout_resize_adjust(w, lcchild, type, 1);
        change -= 1;
        continue;
      }
      if (layout_resize_check(w, lcchild, type) > 0)
      {
        layout_resize_adjust(w, lcchild, type, -1);
        change += 1;
      }
    }

  }

}


----------------------------
void helper_layout_destroy_cell_1(struct layout_cell * const lc, struct layout_cell ** const lcroot, unsigned int lc_idx, struct layout_cell * const lcparent)
{
  do
  {
    if (lc->entry.tqe_next != 0)
    {
      lc->entry.tqe_next->entry.tqe_prev = lc->entry.tqe_prev;
    }
    else
      (&lcparent->cells)->tqh_last = lc->entry.tqe_prev;
    *lc->entry.tqe_prev = lc->entry.tqe_next;
    ;
    ;
  }
  while (0);
  lc->parent = lcparent->parent;
  if (lc->parent == 0)
  {
    lc->xoff = 0;
    lc->yoff = 0;
    *lcroot = &lc[lc_idx];
  }
  else
    do
  {
    if ((lc->entry.tqe_next = lcparent->entry.tqe_next) != 0)
    {
      lc->entry.tqe_next->entry.tqe_prev = &lc->entry.tqe_next;
    }
    else
      (&lc->parent->cells)->tqh_last = &lc->entry.tqe_next;
    lc->entry.tqe_prev = lcparent->entry.tqe_prev;
    *lc->entry.tqe_prev = &lc[lc_idx];
    ;
    ;
  }
  while (0);
  layout_free_cell(lcparent);
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
void layout_fix_offsets(struct layout_cell *lc)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  u_int xoff;
  u_int yoff;
  if (lc->type == LAYOUT_LEFTRIGHT)
  {
    xoff = lc->xoff;
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      lcchild->xoff = xoff;
      lcchild->yoff = lc->yoff;
      if (lcchild->type != LAYOUT_WINDOWPANE)
      {
        layout_fix_offsets(lcchild);
      }
      xoff += lcchild->sx + 1;
    }

  }
  else
  {
    yoff = lc->yoff;
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      lcchild->xoff = lc->xoff;
      lcchild->yoff = yoff;
      if (lcchild->type != LAYOUT_WINDOWPANE)
      {
        layout_fix_offsets(lcchild);
      }
      yoff += lcchild->sy + 1;
    }

  }
}


----------------------------
void layout_fix_panes(struct window *w, u_int wsx, u_int wsy)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  u_int sx;
  u_int sy;
  int shift;
  int status;
  int at_top;
  status = options_get_number(w->options, "pane-border-status");
  at_top = status == 1;
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    helper_layout_fix_panes_1(&lc_idx, &sx, &sy, &shift, wsx, wsy, wp, lc, status, at_top);
  }

}


----------------------------
void layout_destroy_cell(struct window *w, struct layout_cell *lc, struct layout_cell **lcroot)
{
  unsigned int lc_idx = 0;
  struct layout_cell *lcother;
  unsigned int lcother_idx = 0;
  struct layout_cell *lcparent;
  unsigned int lcparent_idx = 0;
  lcparent_idx = lc->parent;
  if ((&lcparent[lcparent_idx]) == 0)
  {
    layout_free_cell(lc);
    *lcroot = 0;
    return;
  }
  if ((&lc[lc_idx]) == (&lcparent->cells)->tqh_first)
  {
    lcother_idx = lc->entry.tqe_next;
  }
  else
    lcother_idx = *((struct layout_cells *) lc->entry.tqe_prev)->tqh_last;
  if (lcparent->type == LAYOUT_LEFTRIGHT)
  {
    layout_resize_adjust(w, lcother, lcparent->type, lc->sx + 1);
  }
  else
    layout_resize_adjust(w, lcother, lcparent->type, lc->sy + 1);
  do
  {
    if (lc->entry.tqe_next != 0)
    {
      lc->entry.tqe_next->entry.tqe_prev = lc->entry.tqe_prev;
    }
    else
      (&lcparent->cells)->tqh_last = lc->entry.tqe_prev;
    *lc->entry.tqe_prev = lc->entry.tqe_next;
    ;
    ;
  }
  while (0);
  layout_free_cell(lc);
  lc_idx = (&lcparent->cells)->tqh_first;
  if (lc->entry.tqe_next == 0)
  {
    helper_layout_destroy_cell_1(lc, lcroot, lc_idx, lcparent);
  }
}


----------------------------
void notify_window(const char *name, struct window *w)
{
  struct cmd_find_state fs;
  cmd_find_from_window(&fs, w, 0);
  notify_add(name, &fs, 0, 0, w, 0);
}


----------------------------
None
----------------------------
***/


u_int layout_count_cells(struct layout_cell *lc)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  u_int count;
  switch (lc->type)
  {
    case LAYOUT_WINDOWPANE:
    {
      return 1;
    }

    case LAYOUT_LEFTRIGHT:

    case LAYOUT_TOPBOTTOM:
    {
      count = 0;
      for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
      {
        count += layout_count_cells(lcchild);
      }

      return count;
    }

    default:
    {
      fatalx("bad layout type");
    }

  }

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
***/


static u_int layout_new_pane_size(struct window *w, u_int previous, struct layout_cell *lc, enum layout_type type, u_int size, u_int count_left, u_int size_left)
{
  u_int new_size;
  u_int min;
  u_int max;
  u_int available;
  if (count_left == 1)
  {
    return size_left;
  }
  available = layout_resize_check(w, lc, type);
  min = (2 + 1) * (count_left - 1);
  if (type == LAYOUT_LEFTRIGHT)
  {
    if ((lc->sx - available) > min)
    {
      min = lc->sx - available;
    }
    new_size = (lc->sx * size) / previous;
  }
  else
  {
    if ((lc->sy - available) > min)
    {
      min = lc->sy - available;
    }
    new_size = (lc->sy * size) / previous;
  }
  max = size_left - min;
  if (new_size > max)
  {
    new_size = max;
  }
  if (new_size < 2)
  {
    new_size = 2;
  }
  return new_size;
}


/*** DEPENDENCIES:
static u_int layout_resize_check(struct window *w, struct layout_cell *lc, enum layout_type type)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  u_int available;
  u_int minimum;
  if (lc->type == LAYOUT_WINDOWPANE)
  {
    minimum = 2;
    if (type == LAYOUT_LEFTRIGHT)
    {
      available = lc->sx;
    }
    else
    {
      available = lc->sy;
      minimum += layout_need_status(lc, options_get_number(w->options, "pane-border-status") == 1);
    }
    if (available > minimum)
    {
      available -= minimum;
    }
    else
      available = 0;
  }
  else
    if (lc->type == type)
  {
    available = 0;
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      available += layout_resize_check(w, lcchild, type);
    }

  }
  else
  {
    minimum = 4294967295U;
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      available = layout_resize_check(w, lcchild, type);
      if (available < minimum)
      {
        minimum = available;
      }
    }

    available = minimum;
  }
  return available;
}


----------------------------
enum layout_type
{
  LAYOUT_LEFTRIGHT,
  LAYOUT_TOPBOTTOM,
  LAYOUT_WINDOWPANE
}
----------------------------
None
----------------------------
***/


static int layout_resize_pane_grow(struct window *w, struct layout_cell *lc, enum layout_type type, int needed, int opposite)
{
  struct layout_cell *lcadd;
  unsigned int lcadd_idx = 0;
  struct layout_cell *lcremove;
  unsigned int lcremove_idx = 0;
  u_int size = 0;
  lcadd_idx = lc;
  lcremove_idx = lc->entry.tqe_next;
  while ((&lcremove[lcremove_idx]) != 0)
  {
    size = layout_resize_check(w, lcremove, type);
    if (size > 0)
    {
      break;
    }
    lcremove_idx = lcremove_idx->entry.tqe_next;
  }

  if (opposite && ((&lcremove[lcremove_idx]) == 0))
  {
    lcremove_idx = *((struct layout_cells *) lc->entry.tqe_prev)->tqh_last;
    while ((&lcremove[lcremove_idx]) != 0)
    {
      size = layout_resize_check(w, lcremove, type);
      if (size > 0)
      {
        break;
      }
      lcremove_idx = *((struct layout_cells *) lcremove_idx->entry.tqe_prev)->tqh_last;
    }

  }
  if ((&lcremove[lcremove_idx]) == 0)
  {
    return 0;
  }
  if (size > ((u_int) needed))
  {
    size = needed;
  }
  layout_resize_adjust(w, lcadd, type, size);
  layout_resize_adjust(w, lcremove, type, -size);
  return size;
}


/*** DEPENDENCIES:
static u_int layout_resize_check(struct window *w, struct layout_cell *lc, enum layout_type type)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  u_int available;
  u_int minimum;
  if (lc->type == LAYOUT_WINDOWPANE)
  {
    minimum = 2;
    if (type == LAYOUT_LEFTRIGHT)
    {
      available = lc->sx;
    }
    else
    {
      available = lc->sy;
      minimum += layout_need_status(lc, options_get_number(w->options, "pane-border-status") == 1);
    }
    if (available > minimum)
    {
      available -= minimum;
    }
    else
      available = 0;
  }
  else
    if (lc->type == type)
  {
    available = 0;
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      available += layout_resize_check(w, lcchild, type);
    }

  }
  else
  {
    minimum = 4294967295U;
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      available = layout_resize_check(w, lcchild, type);
      if (available < minimum)
      {
        minimum = available;
      }
    }

    available = minimum;
  }
  return available;
}


----------------------------
void layout_resize_adjust(struct window *w, struct layout_cell *lc, enum layout_type type, int change)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  if (type == LAYOUT_LEFTRIGHT)
  {
    lc->sx += change;
  }
  else
    lc->sy += change;
  if (type == LAYOUT_WINDOWPANE)
  {
    return;
  }
  if (lc->type != type)
  {
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      layout_resize_adjust(w, lcchild, type, change);
    }

    return;
  }
  while (change != 0)
  {
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      if (change == 0)
      {
        break;
      }
      if (change > 0)
      {
        layout_resize_adjust(w, lcchild, type, 1);
        change -= 1;
        continue;
      }
      if (layout_resize_check(w, lcchild, type) > 0)
      {
        layout_resize_adjust(w, lcchild, type, -1);
        change += 1;
      }
    }

  }

}


----------------------------
enum layout_type
{
  LAYOUT_LEFTRIGHT,
  LAYOUT_TOPBOTTOM,
  LAYOUT_WINDOWPANE
}
----------------------------
None
----------------------------
***/


static int layout_resize_pane_shrink(struct window *w, struct layout_cell *lc, enum layout_type type, int needed)
{
  struct layout_cell *lcadd;
  unsigned int lcadd_idx = 0;
  struct layout_cell *lcremove;
  unsigned int lcremove_idx = 0;
  u_int size;
  lcremove_idx = lc;
  do
  {
    size = layout_resize_check(w, lcremove, type);
    if (size != 0)
    {
      break;
    }
    lcremove_idx = *((struct layout_cells *) lcremove_idx->entry.tqe_prev)->tqh_last;
  }
  while ((&lcremove[lcremove_idx]) != 0);
  if ((&lcremove[lcremove_idx]) == 0)
  {
    return 0;
  }
  lcadd_idx = lc->entry.tqe_next;
  if ((&lcadd[lcadd_idx]) == 0)
  {
    return 0;
  }
  if (size > ((u_int) (-needed)))
  {
    size = -needed;
  }
  layout_resize_adjust(w, lcadd, type, size);
  layout_resize_adjust(w, lcremove, type, -size);
  return size;
}


/*** DEPENDENCIES:
static u_int layout_resize_check(struct window *w, struct layout_cell *lc, enum layout_type type)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  u_int available;
  u_int minimum;
  if (lc->type == LAYOUT_WINDOWPANE)
  {
    minimum = 2;
    if (type == LAYOUT_LEFTRIGHT)
    {
      available = lc->sx;
    }
    else
    {
      available = lc->sy;
      minimum += layout_need_status(lc, options_get_number(w->options, "pane-border-status") == 1);
    }
    if (available > minimum)
    {
      available -= minimum;
    }
    else
      available = 0;
  }
  else
    if (lc->type == type)
  {
    available = 0;
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      available += layout_resize_check(w, lcchild, type);
    }

  }
  else
  {
    minimum = 4294967295U;
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      available = layout_resize_check(w, lcchild, type);
      if (available < minimum)
      {
        minimum = available;
      }
    }

    available = minimum;
  }
  return available;
}


----------------------------
void layout_resize_adjust(struct window *w, struct layout_cell *lc, enum layout_type type, int change)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  if (type == LAYOUT_LEFTRIGHT)
  {
    lc->sx += change;
  }
  else
    lc->sy += change;
  if (type == LAYOUT_WINDOWPANE)
  {
    return;
  }
  if (lc->type != type)
  {
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      layout_resize_adjust(w, lcchild, type, change);
    }

    return;
  }
  while (change != 0)
  {
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      if (change == 0)
      {
        break;
      }
      if (change > 0)
      {
        layout_resize_adjust(w, lcchild, type, 1);
        change -= 1;
        continue;
      }
      if (layout_resize_check(w, lcchild, type) > 0)
      {
        layout_resize_adjust(w, lcchild, type, -1);
        change += 1;
      }
    }

  }

}


----------------------------
enum layout_type
{
  LAYOUT_LEFTRIGHT,
  LAYOUT_TOPBOTTOM,
  LAYOUT_WINDOWPANE
}
----------------------------
None
----------------------------
***/


void layout_resize_pane(struct window_pane *wp, enum layout_type type, int change, int opposite)
{
  struct window *w = wp->window;
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  struct layout_cell *lcparent;
  unsigned int lcparent_idx = 0;
  int needed;
  int size;
  lc_idx = wp->layout_cell;
  lcparent_idx = lc->parent;
  while (((&lcparent[lcparent_idx]) != 0) && (lcparent->type != type))
  {
    lc_idx = &lcparent[lcparent_idx];
    lcparent_idx = lc->parent;
  }

  if ((&lcparent[lcparent_idx]) == 0)
  {
    return;
  }
  if ((&lc[lc_idx]) == (*((struct layout_cells *) (&lcparent->cells)->tqh_last)->tqh_last))
  {
    lc_idx = *((struct layout_cells *) lc_idx->entry.tqe_prev)->tqh_last;
  }
  needed = change;
  while (needed != 0)
  {
    if (change > 0)
    {
      size = layout_resize_pane_grow(w, lc, type, needed, opposite);
      needed -= size;
    }
    else
    {
      size = layout_resize_pane_shrink(w, lc, type, needed);
      needed += size;
    }
    if (size == 0)
    {
      break;
    }
  }

  layout_fix_offsets(wp->window->layout_root);
  layout_fix_panes(wp->window, wp->window->sx, wp->window->sy);
  notify_window("window-layout-changed", wp->window);
}


/*** DEPENDENCIES:
void layout_fix_panes(struct window *w, u_int wsx, u_int wsy)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  u_int sx;
  u_int sy;
  int shift;
  int status;
  int at_top;
  status = options_get_number(w->options, "pane-border-status");
  at_top = status == 1;
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    helper_layout_fix_panes_1(&lc_idx, &sx, &sy, &shift, wsx, wsy, wp, lc, status, at_top);
  }

}


----------------------------
void notify_window(const char *name, struct window *w)
{
  struct cmd_find_state fs;
  cmd_find_from_window(&fs, w, 0);
  notify_add(name, &fs, 0, 0, w, 0);
}


----------------------------
enum layout_type
{
  LAYOUT_LEFTRIGHT,
  LAYOUT_TOPBOTTOM,
  LAYOUT_WINDOWPANE
}
----------------------------
void layout_fix_offsets(struct layout_cell *lc)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  u_int xoff;
  u_int yoff;
  if (lc->type == LAYOUT_LEFTRIGHT)
  {
    xoff = lc->xoff;
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      lcchild->xoff = xoff;
      lcchild->yoff = lc->yoff;
      if (lcchild->type != LAYOUT_WINDOWPANE)
      {
        layout_fix_offsets(lcchild);
      }
      xoff += lcchild->sx + 1;
    }

  }
  else
  {
    yoff = lc->yoff;
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      lcchild->xoff = lc->xoff;
      lcchild->yoff = yoff;
      if (lcchild->type != LAYOUT_WINDOWPANE)
      {
        layout_fix_offsets(lcchild);
      }
      yoff += lcchild->sy + 1;
    }

  }
}


----------------------------
static int layout_resize_pane_grow(struct window *w, struct layout_cell *lc, enum layout_type type, int needed, int opposite)
{
  struct layout_cell *lcadd;
  unsigned int lcadd_idx = 0;
  struct layout_cell *lcremove;
  unsigned int lcremove_idx = 0;
  u_int size = 0;
  lcadd_idx = lc;
  lcremove_idx = lc->entry.tqe_next;
  while ((&lcremove[lcremove_idx]) != 0)
  {
    size = layout_resize_check(w, lcremove, type);
    if (size > 0)
    {
      break;
    }
    lcremove_idx = lcremove_idx->entry.tqe_next;
  }

  if (opposite && ((&lcremove[lcremove_idx]) == 0))
  {
    lcremove_idx = *((struct layout_cells *) lc->entry.tqe_prev)->tqh_last;
    while ((&lcremove[lcremove_idx]) != 0)
    {
      size = layout_resize_check(w, lcremove, type);
      if (size > 0)
      {
        break;
      }
      lcremove_idx = *((struct layout_cells *) lcremove_idx->entry.tqe_prev)->tqh_last;
    }

  }
  if ((&lcremove[lcremove_idx]) == 0)
  {
    return 0;
  }
  if (size > ((u_int) needed))
  {
    size = needed;
  }
  layout_resize_adjust(w, lcadd, type, size);
  layout_resize_adjust(w, lcremove, type, -size);
  return size;
}


----------------------------
static int layout_resize_pane_shrink(struct window *w, struct layout_cell *lc, enum layout_type type, int needed)
{
  struct layout_cell *lcadd;
  unsigned int lcadd_idx = 0;
  struct layout_cell *lcremove;
  unsigned int lcremove_idx = 0;
  u_int size;
  lcremove_idx = lc;
  do
  {
    size = layout_resize_check(w, lcremove, type);
    if (size != 0)
    {
      break;
    }
    lcremove_idx = *((struct layout_cells *) lcremove_idx->entry.tqe_prev)->tqh_last;
  }
  while ((&lcremove[lcremove_idx]) != 0);
  if ((&lcremove[lcremove_idx]) == 0)
  {
    return 0;
  }
  lcadd_idx = lc->entry.tqe_next;
  if ((&lcadd[lcadd_idx]) == 0)
  {
    return 0;
  }
  if (size > ((u_int) (-needed)))
  {
    size = -needed;
  }
  layout_resize_adjust(w, lcadd, type, size);
  layout_resize_adjust(w, lcremove, type, -size);
  return size;
}


----------------------------
None
----------------------------
***/


void layout_resize_pane_to(struct window_pane *wp, enum layout_type type, u_int new_size)
{
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  struct layout_cell *lcparent;
  unsigned int lcparent_idx = 0;
  int change;
  int size;
  lc_idx = wp->layout_cell;
  lcparent_idx = lc->parent;
  while (((&lcparent[lcparent_idx]) != 0) && (lcparent->type != type))
  {
    lc_idx = &lcparent[lcparent_idx];
    lcparent_idx = lc->parent;
  }

  if ((&lcparent[lcparent_idx]) == 0)
  {
    return;
  }
  if (type == LAYOUT_LEFTRIGHT)
  {
    size = lc->sx;
  }
  else
    size = lc->sy;
  if ((&lc[lc_idx]) == (*((struct layout_cells *) (&lcparent->cells)->tqh_last)->tqh_last))
  {
    change = size - new_size;
  }
  else
    change = new_size - size;
  layout_resize_pane(wp, type, change, 1);
}


/*** DEPENDENCIES:
void layout_resize_pane(struct window_pane *wp, enum layout_type type, int change, int opposite)
{
  struct window *w = wp->window;
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  struct layout_cell *lcparent;
  unsigned int lcparent_idx = 0;
  int needed;
  int size;
  lc_idx = wp->layout_cell;
  lcparent_idx = lc->parent;
  while (((&lcparent[lcparent_idx]) != 0) && (lcparent->type != type))
  {
    lc_idx = &lcparent[lcparent_idx];
    lcparent_idx = lc->parent;
  }

  if ((&lcparent[lcparent_idx]) == 0)
  {
    return;
  }
  if ((&lc[lc_idx]) == (*((struct layout_cells *) (&lcparent->cells)->tqh_last)->tqh_last))
  {
    lc_idx = *((struct layout_cells *) lc_idx->entry.tqe_prev)->tqh_last;
  }
  needed = change;
  while (needed != 0)
  {
    if (change > 0)
    {
      size = layout_resize_pane_grow(w, lc, type, needed, opposite);
      needed -= size;
    }
    else
    {
      size = layout_resize_pane_shrink(w, lc, type, needed);
      needed += size;
    }
    if (size == 0)
    {
      break;
    }
  }

  layout_fix_offsets(wp->window->layout_root);
  layout_fix_panes(wp->window, wp->window->sx, wp->window->sy);
  notify_window("window-layout-changed", wp->window);
}


----------------------------
enum layout_type
{
  LAYOUT_LEFTRIGHT,
  LAYOUT_TOPBOTTOM,
  LAYOUT_WINDOWPANE
}
----------------------------
None
----------------------------
***/


void layout_assign_pane(struct layout_cell *lc, struct window_pane *wp)
{
  layout_make_leaf(lc, wp);
  layout_fix_panes(wp->window, wp->window->sx, wp->window->sy);
}


/*** DEPENDENCIES:
void layout_make_leaf(struct layout_cell *lc, struct window_pane *wp)
{
  lc->type = LAYOUT_WINDOWPANE;
  do
  {
    (&lc->cells)->tqh_first = 0;
    (&lc->cells)->tqh_last = &(&lc->cells)->tqh_first;
  }
  while (0);
  wp->layout_cell = lc;
  lc->wp = wp;
}


----------------------------
void layout_fix_panes(struct window *w, u_int wsx, u_int wsy)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  u_int sx;
  u_int sy;
  int shift;
  int status;
  int at_top;
  status = options_get_number(w->options, "pane-border-status");
  at_top = status == 1;
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    helper_layout_fix_panes_1(&lc_idx, &sx, &sy, &shift, wsx, wsy, wp, lc, status, at_top);
  }

}


----------------------------
None
----------------------------
***/


void layout_spread_out(struct window_pane *wp)
{
  struct layout_cell *parent;
  unsigned int parent_idx = 0;
  struct window *w = wp->window;
  parent_idx = wp->layout_cell->parent_idx;
  if ((&parent[parent_idx]) == 0)
  {
    return;
  }
  do
  {
    if (layout_spread_cell(w, parent))
    {
      layout_fix_offsets(parent);
      layout_fix_panes(w, w->sx, w->sy);
      break;
    }
  }
  while ((parent_idx = parent_idx->parent_idx) != 0);
}


/*** DEPENDENCIES:
void layout_fix_offsets(struct layout_cell *lc)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  u_int xoff;
  u_int yoff;
  if (lc->type == LAYOUT_LEFTRIGHT)
  {
    xoff = lc->xoff;
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      lcchild->xoff = xoff;
      lcchild->yoff = lc->yoff;
      if (lcchild->type != LAYOUT_WINDOWPANE)
      {
        layout_fix_offsets(lcchild);
      }
      xoff += lcchild->sx + 1;
    }

  }
  else
  {
    yoff = lc->yoff;
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      lcchild->xoff = lc->xoff;
      lcchild->yoff = yoff;
      if (lcchild->type != LAYOUT_WINDOWPANE)
      {
        layout_fix_offsets(lcchild);
      }
      yoff += lcchild->sy + 1;
    }

  }
}


----------------------------
void layout_fix_panes(struct window *w, u_int wsx, u_int wsy)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  u_int sx;
  u_int sy;
  int shift;
  int status;
  int at_top;
  status = options_get_number(w->options, "pane-border-status");
  at_top = status == 1;
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    helper_layout_fix_panes_1(&lc_idx, &sx, &sy, &shift, wsx, wsy, wp, lc, status, at_top);
  }

}


----------------------------
int layout_spread_cell(struct window *w, struct layout_cell *parent)
{
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  u_int number;
  u_int each;
  u_int size;
  int change;
  int changed;
  number = 0;
  for (lc_idx = (&parent->cells)->tqh_first; (&lc[lc_idx]) != 0; lc_idx = lc_idx->entry.tqe_next)
  {
    number += 1;
  }

  if (number <= 1)
  {
    return 0;
  }
  if (parent->type == LAYOUT_LEFTRIGHT)
  {
    size = parent->sx;
  }
  else
    if (parent->type == LAYOUT_TOPBOTTOM)
  {
    size = parent->sy;
  }
  else
    return 0;
  each = (size - (number - 1)) / number;
  changed = 0;
  for (lc_idx = (&parent->cells)->tqh_first; (&lc[lc_idx]) != 0; lc_idx = lc_idx->entry.tqe_next)
  {
    if (lc->entry.tqe_next == 0)
    {
      each = size - ((each + 1) * (number - 1));
    }
    change = 0;
    if (parent->type == LAYOUT_LEFTRIGHT)
    {
      change = each - ((int) lc->sx);
      layout_resize_adjust(w, lc, LAYOUT_LEFTRIGHT, change);
    }
    else
      if (parent->type == LAYOUT_TOPBOTTOM)
    {
      change = each - ((int) lc->sy);
      layout_resize_adjust(w, lc, LAYOUT_TOPBOTTOM, change);
    }
    if (change != 0)
    {
      changed = 1;
    }
  }

  return changed;
}


----------------------------
None
----------------------------
***/


// hint:  ['size_ref is a mutable refrence to int', 'lcnew_idx_ref is a mutable refrence to unsigned int', 'sx_ref is a mutable refrence to u_int', 'sy_ref is a mutable refrence to u_int', 'resize_first_ref is a mutable refrence to u_int']
void helper_layout_split_pane_2(int * const size_ref, unsigned int * const lcnew_idx_ref, u_int * const sx_ref, u_int * const sy_ref, u_int * const resize_first_ref, struct window_pane * const wp, int insert_before, struct layout_cell * const lc, struct layout_cell * const lcnew, u_int new_size, u_int saved_size)
{
  int size = *size_ref;
  unsigned int lcnew_idx = *lcnew_idx_ref;
  u_int sx = *sx_ref;
  u_int sy = *sy_ref;
  u_int resize_first = *resize_first_ref;
  if (lc->type == LAYOUT_LEFTRIGHT)
  {
    lc->sx = new_size;
    layout_resize_child_cells(wp->window, lc);
    lc->sx = saved_size;
  }
  else
    if (lc->type == LAYOUT_TOPBOTTOM)
  {
    lc->sy = new_size;
    layout_resize_child_cells(wp->window, lc);
    lc->sy = saved_size;
  }
  resize_first = 1;
  lcnew_idx = layout_create_cell(lc);
  size = (saved_size - 1) - new_size;
  if (lc->type == LAYOUT_LEFTRIGHT)
  {
    layout_set_size(lcnew, size, sy, 0, 0);
  }
  else
    if (lc->type == LAYOUT_TOPBOTTOM)
  {
    layout_set_size(lcnew, sx, size, 0, 0);
  }
  if (insert_before)
  {
    do
    {
      if ((lcnew->entry.tqe_next = (&lc->cells)->tqh_first) != 0)
      {
        (&lc->cells)->tqh_first->entry.tqe_prev = &lcnew->entry.tqe_next;
      }
      else
        (&lc->cells)->tqh_last = &lcnew->entry.tqe_next;
      (&lc->cells)->tqh_first = &lcnew[lcnew_idx];
      lcnew->entry.tqe_prev = &(&lc->cells)->tqh_first;
    }
    while (0);
  }
  else
    do
  {
    lcnew->entry.tqe_next = 0;
    lcnew->entry.tqe_prev = (&lc->cells)->tqh_last;
    *(&lc->cells)->tqh_last = &lcnew[lcnew_idx];
    (&lc->cells)->tqh_last = &lcnew->entry.tqe_next;
  }
  while (0);
  *size_ref = size;
  *lcnew_idx_ref = lcnew_idx;
  *sx_ref = sx;
  *sy_ref = sy;
  *resize_first_ref = resize_first;
}


/*** DEPENDENCIES:
struct layout_cell *layout_create_cell(struct layout_cell *lcparent)
{
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  lc_idx = xmalloc(sizeof(*lc_idx));
  lc->type = LAYOUT_WINDOWPANE;
  lc->parent = lcparent;
  do
  {
    (&lc->cells)->tqh_first = 0;
    (&lc->cells)->tqh_last = &(&lc->cells)->tqh_first;
  }
  while (0);
  lc->sx = 4294967295U;
  lc->sy = 4294967295U;
  lc->xoff = 4294967295U;
  lc->yoff = 4294967295U;
  lc->wp = 0;
  return lc;
}


----------------------------
void layout_set_size(struct layout_cell *lc, u_int sx, u_int sy, u_int xoff, u_int yoff)
{
  lc->sx = sx;
  lc->sy = sy;
  lc->xoff = xoff;
  lc->yoff = yoff;
}


----------------------------
None
----------------------------
None
----------------------------
***/


// hint:  ['lcparent_idx_ref is a mutable refrence to unsigned int', 'lcnew_idx_ref is a mutable refrence to unsigned int']
void helper_layout_split_pane_3(unsigned int * const lcparent_idx_ref, unsigned int * const lcnew_idx_ref, struct window_pane * const wp, enum layout_type type, int insert_before, struct layout_cell * const lc, unsigned int lc_idx, struct layout_cell * const lcparent, struct layout_cell * const lcnew, u_int sx, u_int sy, u_int xoff, u_int yoff)
{
  unsigned int lcparent_idx = *lcparent_idx_ref;
  unsigned int lcnew_idx = *lcnew_idx_ref;
  lcparent_idx = layout_create_cell(lc->parent);
  layout_make_node(lcparent, type);
  layout_set_size(lcparent, sx, sy, xoff, yoff);
  if (lc->parent == 0)
  {
    wp->window->layout_root = &lcparent[lcparent_idx];
  }
  else
    do
  {
    if ((lcparent->entry.tqe_next = lc->entry.tqe_next) != 0)
    {
      lcparent->entry.tqe_next->entry.tqe_prev = &lcparent->entry.tqe_next;
    }
    else
      (&lc->parent->cells)->tqh_last = &lcparent->entry.tqe_next;
    lcparent->entry.tqe_prev = lc->entry.tqe_prev;
    *lcparent->entry.tqe_prev = &lcparent[lcparent_idx];
    ;
    ;
  }
  while (0);
  lc->parent = &lcparent[lcparent_idx];
  do
  {
    if ((lc->entry.tqe_next = (&lcparent->cells)->tqh_first) != 0)
    {
      (&lcparent->cells)->tqh_first->entry.tqe_prev = &lc->entry.tqe_next;
    }
    else
      (&lcparent->cells)->tqh_last = &lc->entry.tqe_next;
    (&lcparent->cells)->tqh_first = &lc[lc_idx];
    lc->entry.tqe_prev = &(&lcparent->cells)->tqh_first;
  }
  while (0);
  lcnew_idx = layout_create_cell(lcparent);
  if (insert_before)
  {
    do
    {
      if ((lcnew->entry.tqe_next = (&lcparent->cells)->tqh_first) != 0)
      {
        (&lcparent->cells)->tqh_first->entry.tqe_prev = &lcnew->entry.tqe_next;
      }
      else
        (&lcparent->cells)->tqh_last = &lcnew->entry.tqe_next;
      (&lcparent->cells)->tqh_first = &lcnew[lcnew_idx];
      lcnew->entry.tqe_prev = &(&lcparent->cells)->tqh_first;
    }
    while (0);
  }
  else
    do
  {
    lcnew->entry.tqe_next = 0;
    lcnew->entry.tqe_prev = (&lcparent->cells)->tqh_last;
    *(&lcparent->cells)->tqh_last = &lcnew[lcnew_idx];
    (&lcparent->cells)->tqh_last = &lcnew->entry.tqe_next;
  }
  while (0);
  *lcparent_idx_ref = lcparent_idx;
  *lcnew_idx_ref = lcnew_idx;
}


/*** DEPENDENCIES:
void layout_make_node(struct layout_cell *lc, enum layout_type type)
{
  if (type == LAYOUT_WINDOWPANE)
  {
    fatalx("bad layout type");
  }
  lc->type = type;
  do
  {
    (&lc->cells)->tqh_first = 0;
    (&lc->cells)->tqh_last = &(&lc->cells)->tqh_first;
  }
  while (0);
  if (lc->wp != 0)
  {
    lc->wp->layout_cell = 0;
  }
  lc->wp = 0;
}


----------------------------
struct layout_cell *layout_create_cell(struct layout_cell *lcparent)
{
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  lc_idx = xmalloc(sizeof(*lc_idx));
  lc->type = LAYOUT_WINDOWPANE;
  lc->parent = lcparent;
  do
  {
    (&lc->cells)->tqh_first = 0;
    (&lc->cells)->tqh_last = &(&lc->cells)->tqh_first;
  }
  while (0);
  lc->sx = 4294967295U;
  lc->sy = 4294967295U;
  lc->xoff = 4294967295U;
  lc->yoff = 4294967295U;
  lc->wp = 0;
  return lc;
}


----------------------------
void layout_set_size(struct layout_cell *lc, u_int sx, u_int sy, u_int xoff, u_int yoff)
{
  lc->sx = sx;
  lc->sy = sy;
  lc->xoff = xoff;
  lc->yoff = yoff;
}


----------------------------
enum layout_type
{
  LAYOUT_LEFTRIGHT,
  LAYOUT_TOPBOTTOM,
  LAYOUT_WINDOWPANE
}
----------------------------
None
----------------------------
***/


struct layout_cell *layout_split_pane(struct window_pane *wp, enum layout_type type, int size, int insert_before, int full_size)
{
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  struct layout_cell *lcparent;
  unsigned int lcparent_idx = 0;
  struct layout_cell *lcnew;
  unsigned int lcnew_idx = 0;
  struct layout_cell *lc1;
  unsigned int lc1_idx = 0;
  struct layout_cell *lc2;
  unsigned int lc2_idx = 0;
  u_int sx;
  u_int sy;
  u_int xoff;
  u_int yoff;
  u_int size1;
  u_int size2;
  u_int new_size;
  u_int saved_size;
  u_int resize_first = 0;
  if (full_size)
  {
    lc_idx = wp->window->layout_root;
  }
  else
    lc_idx = wp->layout_cell;
  sx = lc->sx;
  sy = lc->sy;
  xoff = lc->xoff;
  yoff = lc->yoff;
  switch (type)
  {
    case LAYOUT_LEFTRIGHT:
    {
      if (sx < ((2 * 2) + 1))
      {
        return 0;
      }
      break;
    }

    case LAYOUT_TOPBOTTOM:
    {
      if (sy < ((2 * 2) + 1))
      {
        return 0;
      }
      break;
    }

    default:
    {
      fatalx("bad layout type");
    }

  }

  if (type == LAYOUT_LEFTRIGHT)
  {
    saved_size = sx;
  }
  else
    saved_size = sy;
  if (size < 0)
  {
    size2 = ((saved_size + 1) / 2) - 1;
  }
  else
    if (insert_before)
  {
    size2 = (saved_size - size) - 1;
  }
  else
    size2 = size;
  if (size2 < 2)
  {
    size2 = 2;
  }
  else
    if (size2 > (saved_size - 2))
  {
    size2 = saved_size - 2;
  }
  size1 = (saved_size - 1) - size2;
  if (insert_before)
  {
    new_size = size2;
  }
  else
    new_size = size1;
  if (full_size && (!layout_set_size_check(wp->window, lc, type, new_size)))
  {
    return 0;
  }
  if ((lc->parent != 0) && (lc->parent->type == type))
  {
    helper_layout_split_pane_1(&lcparent_idx, &lcnew_idx, insert_before, lc, lc_idx, lcparent, lcnew);
  }
  else
    if ((full_size && (lc->parent == 0)) && (lc->type == type))
  {
    helper_layout_split_pane_2(&size, &lcnew_idx, &sx, &sy, &resize_first, wp, insert_before, lc, lcnew, new_size, saved_size);
  }
  else
  {
    helper_layout_split_pane_3(&lcparent_idx, &lcnew_idx, wp, type, insert_before, lc, lc_idx, lcparent, lcnew, sx, sy, xoff, yoff);
  }
  if (insert_before)
  {
    lc1_idx = &lcnew[lcnew_idx];
    lc2_idx = &lc[lc_idx];
  }
  else
  {
    lc1_idx = &lc[lc_idx];
    lc2_idx = &lcnew[lcnew_idx];
  }
  if ((!resize_first) && (type == LAYOUT_LEFTRIGHT))
  {
    layout_set_size(lc1, size1, sy, xoff, yoff);
    layout_set_size(lc2, size2, sy, (xoff + lc1->sx) + 1, yoff);
  }
  else
    if ((!resize_first) && (type == LAYOUT_TOPBOTTOM))
  {
    layout_set_size(lc1, sx, size1, xoff, yoff);
    layout_set_size(lc2, sx, size2, xoff, (yoff + lc1->sy) + 1);
  }
  if (full_size)
  {
    if (!resize_first)
    {
      layout_resize_child_cells(wp->window, lc);
    }
    layout_fix_offsets(wp->window->layout_root);
  }
  else
    layout_make_leaf(lc, wp);
  return lcnew;
}


/*** DEPENDENCIES:
void layout_make_leaf(struct layout_cell *lc, struct window_pane *wp)
{
  lc->type = LAYOUT_WINDOWPANE;
  do
  {
    (&lc->cells)->tqh_first = 0;
    (&lc->cells)->tqh_last = &(&lc->cells)->tqh_first;
  }
  while (0);
  wp->layout_cell = lc;
  lc->wp = wp;
}


----------------------------
void helper_layout_split_pane_2(int * const size_ref, unsigned int * const lcnew_idx_ref, u_int * const sx_ref, u_int * const sy_ref, u_int * const resize_first_ref, struct window_pane * const wp, int insert_before, struct layout_cell * const lc, struct layout_cell * const lcnew, u_int new_size, u_int saved_size)
{
  int size = *size_ref;
  unsigned int lcnew_idx = *lcnew_idx_ref;
  u_int sx = *sx_ref;
  u_int sy = *sy_ref;
  u_int resize_first = *resize_first_ref;
  if (lc->type == LAYOUT_LEFTRIGHT)
  {
    lc->sx = new_size;
    layout_resize_child_cells(wp->window, lc);
    lc->sx = saved_size;
  }
  else
    if (lc->type == LAYOUT_TOPBOTTOM)
  {
    lc->sy = new_size;
    layout_resize_child_cells(wp->window, lc);
    lc->sy = saved_size;
  }
  resize_first = 1;
  lcnew_idx = layout_create_cell(lc);
  size = (saved_size - 1) - new_size;
  if (lc->type == LAYOUT_LEFTRIGHT)
  {
    layout_set_size(lcnew, size, sy, 0, 0);
  }
  else
    if (lc->type == LAYOUT_TOPBOTTOM)
  {
    layout_set_size(lcnew, sx, size, 0, 0);
  }
  if (insert_before)
  {
    do
    {
      if ((lcnew->entry.tqe_next = (&lc->cells)->tqh_first) != 0)
      {
        (&lc->cells)->tqh_first->entry.tqe_prev = &lcnew->entry.tqe_next;
      }
      else
        (&lc->cells)->tqh_last = &lcnew->entry.tqe_next;
      (&lc->cells)->tqh_first = &lcnew[lcnew_idx];
      lcnew->entry.tqe_prev = &(&lc->cells)->tqh_first;
    }
    while (0);
  }
  else
    do
  {
    lcnew->entry.tqe_next = 0;
    lcnew->entry.tqe_prev = (&lc->cells)->tqh_last;
    *(&lc->cells)->tqh_last = &lcnew[lcnew_idx];
    (&lc->cells)->tqh_last = &lcnew->entry.tqe_next;
  }
  while (0);
  *size_ref = size;
  *lcnew_idx_ref = lcnew_idx;
  *sx_ref = sx;
  *sy_ref = sy;
  *resize_first_ref = resize_first;
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
None
----------------------------
void layout_set_size(struct layout_cell *lc, u_int sx, u_int sy, u_int xoff, u_int yoff)
{
  lc->sx = sx;
  lc->sy = sy;
  lc->xoff = xoff;
  lc->yoff = yoff;
}


----------------------------
enum layout_type
{
  LAYOUT_LEFTRIGHT,
  LAYOUT_TOPBOTTOM,
  LAYOUT_WINDOWPANE
}
----------------------------
void layout_fix_offsets(struct layout_cell *lc)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  u_int xoff;
  u_int yoff;
  if (lc->type == LAYOUT_LEFTRIGHT)
  {
    xoff = lc->xoff;
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      lcchild->xoff = xoff;
      lcchild->yoff = lc->yoff;
      if (lcchild->type != LAYOUT_WINDOWPANE)
      {
        layout_fix_offsets(lcchild);
      }
      xoff += lcchild->sx + 1;
    }

  }
  else
  {
    yoff = lc->yoff;
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      lcchild->xoff = lc->xoff;
      lcchild->yoff = yoff;
      if (lcchild->type != LAYOUT_WINDOWPANE)
      {
        layout_fix_offsets(lcchild);
      }
      yoff += lcchild->sy + 1;
    }

  }
}


----------------------------
void helper_layout_split_pane_3(unsigned int * const lcparent_idx_ref, unsigned int * const lcnew_idx_ref, struct window_pane * const wp, enum layout_type type, int insert_before, struct layout_cell * const lc, unsigned int lc_idx, struct layout_cell * const lcparent, struct layout_cell * const lcnew, u_int sx, u_int sy, u_int xoff, u_int yoff)
{
  unsigned int lcparent_idx = *lcparent_idx_ref;
  unsigned int lcnew_idx = *lcnew_idx_ref;
  lcparent_idx = layout_create_cell(lc->parent);
  layout_make_node(lcparent, type);
  layout_set_size(lcparent, sx, sy, xoff, yoff);
  if (lc->parent == 0)
  {
    wp->window->layout_root = &lcparent[lcparent_idx];
  }
  else
    do
  {
    if ((lcparent->entry.tqe_next = lc->entry.tqe_next) != 0)
    {
      lcparent->entry.tqe_next->entry.tqe_prev = &lcparent->entry.tqe_next;
    }
    else
      (&lc->parent->cells)->tqh_last = &lcparent->entry.tqe_next;
    lcparent->entry.tqe_prev = lc->entry.tqe_prev;
    *lcparent->entry.tqe_prev = &lcparent[lcparent_idx];
    ;
    ;
  }
  while (0);
  lc->parent = &lcparent[lcparent_idx];
  do
  {
    if ((lc->entry.tqe_next = (&lcparent->cells)->tqh_first) != 0)
    {
      (&lcparent->cells)->tqh_first->entry.tqe_prev = &lc->entry.tqe_next;
    }
    else
      (&lcparent->cells)->tqh_last = &lc->entry.tqe_next;
    (&lcparent->cells)->tqh_first = &lc[lc_idx];
    lc->entry.tqe_prev = &(&lcparent->cells)->tqh_first;
  }
  while (0);
  lcnew_idx = layout_create_cell(lcparent);
  if (insert_before)
  {
    do
    {
      if ((lcnew->entry.tqe_next = (&lcparent->cells)->tqh_first) != 0)
      {
        (&lcparent->cells)->tqh_first->entry.tqe_prev = &lcnew->entry.tqe_next;
      }
      else
        (&lcparent->cells)->tqh_last = &lcnew->entry.tqe_next;
      (&lcparent->cells)->tqh_first = &lcnew[lcnew_idx];
      lcnew->entry.tqe_prev = &(&lcparent->cells)->tqh_first;
    }
    while (0);
  }
  else
    do
  {
    lcnew->entry.tqe_next = 0;
    lcnew->entry.tqe_prev = (&lcparent->cells)->tqh_last;
    *(&lcparent->cells)->tqh_last = &lcnew[lcnew_idx];
    (&lcparent->cells)->tqh_last = &lcnew->entry.tqe_next;
  }
  while (0);
  *lcparent_idx_ref = lcparent_idx;
  *lcnew_idx_ref = lcnew_idx;
}


----------------------------
void helper_layout_split_pane_1(unsigned int * const lcparent_idx_ref, unsigned int * const lcnew_idx_ref, int insert_before, struct layout_cell * const lc, unsigned int lc_idx, struct layout_cell * const lcparent, struct layout_cell * const lcnew)
{
  unsigned int lcparent_idx = *lcparent_idx_ref;
  unsigned int lcnew_idx = *lcnew_idx_ref;
  lcparent_idx = lc->parent;
  lcnew_idx = layout_create_cell(lcparent);
  if (insert_before)
  {
    do
    {
      lcnew->entry.tqe_prev = lc->entry.tqe_prev;
      lcnew->entry.tqe_next = &lc[lc_idx];
      *lc->entry.tqe_prev = &lcnew[lcnew_idx];
      lc->entry.tqe_prev = &lcnew->entry.tqe_next;
    }
    while (0);
  }
  else
    do
  {
    if ((lcnew->entry.tqe_next = lc->entry.tqe_next) != 0)
    {
      lcnew->entry.tqe_next->entry.tqe_prev = &lcnew->entry.tqe_next;
    }
    else
      (&lcparent->cells)->tqh_last = &lcnew->entry.tqe_next;
    lc->entry.tqe_next = &lcnew[lcnew_idx];
    lcnew->entry.tqe_prev = &lc->entry.tqe_next;
  }
  while (0);
  *lcparent_idx_ref = lcparent_idx;
  *lcnew_idx_ref = lcnew_idx;
}


----------------------------
None
----------------------------
None
----------------------------
***/


