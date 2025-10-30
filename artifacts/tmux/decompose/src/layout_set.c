static void layout_set_even(struct window *w, enum layout_type type)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  struct layout_cell *lcnew;
  unsigned int lcnew_idx = 0;
  u_int n;
  layout_print_cell(w->layout_root, __func__, 1);
  n = window_count_panes(w);
  if (n <= 1)
  {
    return;
  }
  layout_free(w);
  lc_idx = (w->layout_root = layout_create_cell(0));
  layout_set_size(lc, w->sx, w->sy, 0, 0);
  layout_make_node(lc, type);
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    lcnew_idx = layout_create_cell(lc);
    layout_make_leaf(lcnew, wp);
    lcnew->sx = w->sx;
    lcnew->sy = w->sy;
    do
    {
      lcnew->entry.tqe_next = 0;
      lcnew->entry.tqe_prev = (&lc->cells)->tqh_last;
      *(&lc->cells)->tqh_last = &lcnew[lcnew_idx];
      (&lc->cells)->tqh_last = &lcnew->entry.tqe_next;
    }
    while (0);
  }

  layout_spread_cell(w, lc);
  layout_fix_offsets(lc);
  layout_fix_panes(w, w->sx, w->sy);
  layout_print_cell(w->layout_root, __func__, 1);
  notify_window("window-layout-changed", w);
  server_redraw_window(w);
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
void layout_free(struct window *w)
{
  layout_free_cell(w->layout_root);
}


----------------------------
enum layout_type
{
  LAYOUT_LEFTRIGHT,
  LAYOUT_TOPBOTTOM,
  LAYOUT_WINDOWPANE
}
----------------------------
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


static void layout_set_even_v(struct window *w)
{
  layout_set_even(w, LAYOUT_TOPBOTTOM);
}


/*** DEPENDENCIES:
static void layout_set_even(struct window *w, enum layout_type type)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  struct layout_cell *lcnew;
  unsigned int lcnew_idx = 0;
  u_int n;
  layout_print_cell(w->layout_root, __func__, 1);
  n = window_count_panes(w);
  if (n <= 1)
  {
    return;
  }
  layout_free(w);
  lc_idx = (w->layout_root = layout_create_cell(0));
  layout_set_size(lc, w->sx, w->sy, 0, 0);
  layout_make_node(lc, type);
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    lcnew_idx = layout_create_cell(lc);
    layout_make_leaf(lcnew, wp);
    lcnew->sx = w->sx;
    lcnew->sy = w->sy;
    do
    {
      lcnew->entry.tqe_next = 0;
      lcnew->entry.tqe_prev = (&lc->cells)->tqh_last;
      *(&lc->cells)->tqh_last = &lcnew[lcnew_idx];
      (&lc->cells)->tqh_last = &lcnew->entry.tqe_next;
    }
    while (0);
  }

  layout_spread_cell(w, lc);
  layout_fix_offsets(lc);
  layout_fix_panes(w, w->sx, w->sy);
  layout_print_cell(w->layout_root, __func__, 1);
  notify_window("window-layout-changed", w);
  server_redraw_window(w);
}


----------------------------
None
----------------------------
***/


// hint:  ['wp_idx_ref is a mutable refrence to unsigned int', 'lcrow_idx_ref is a mutable refrence to unsigned int', 'lcchild_idx_ref is a mutable refrence to unsigned int', 'used_ref is a mutable refrence to u_int', 'i_ref is a mutable refrence to u_int']
void helper_layout_set_main_h_1(unsigned int * const wp_idx_ref, unsigned int * const lcrow_idx_ref, unsigned int * const lcchild_idx_ref, u_int * const used_ref, u_int * const i_ref, struct window * const w, struct window_pane * const wp, struct layout_cell * const lc, struct layout_cell * const lcrow, struct layout_cell * const lcchild, u_int width, u_int height, u_int columns)
{
  unsigned int wp_idx = *wp_idx_ref;
  unsigned int lcrow_idx = *lcrow_idx_ref;
  unsigned int lcchild_idx = *lcchild_idx_ref;
  u_int used = *used_ref;
  u_int i = *i_ref;
  if ((&wp[wp_idx]) == 0)
  {
    break;
  }
  lcrow_idx = layout_create_cell(lc);
  layout_set_size(lcrow, w->sx, height, 0, 0);
  do
  {
    lcrow->entry.tqe_next = 0;
    lcrow->entry.tqe_prev = (&lc->cells)->tqh_last;
    *(&lc->cells)->tqh_last = &lcrow[lcrow_idx];
    (&lc->cells)->tqh_last = &lcrow->entry.tqe_next;
  }
  while (0);
  if (columns == 1)
  {
    layout_make_leaf(lcrow, wp);
    wp_idx = wp_idx->entry.tqe_next;
    continue;
  }
  layout_make_node(lcrow, LAYOUT_LEFTRIGHT);
  for (i = 0; i < columns; i += 1)
  {
    lcchild_idx = layout_create_cell(lcrow);
    layout_set_size(lcchild, width, height, 0, 0);
    layout_make_leaf(lcchild, wp);
    do
    {
      lcchild->entry.tqe_next = 0;
      lcchild->entry.tqe_prev = (&lcrow->cells)->tqh_last;
      *(&lcrow->cells)->tqh_last = &lcchild[lcchild_idx];
      (&lcrow->cells)->tqh_last = &lcchild->entry.tqe_next;
    }
    while (0);
    if ((wp_idx = wp_idx->entry.tqe_next) == 0)
    {
      break;
    }
  }

  if (i == columns)
  {
    i -= 1;
  }
  used = ((i + 1) * (width + 1)) - 1;
  if (w->sx <= used)
  {
    continue;
  }
  lcchild_idx = *((struct layout_cells *) (&lcrow->cells)->tqh_last)->tqh_last;
  layout_resize_adjust(w, lcchild, LAYOUT_LEFTRIGHT, w->sx - used);
  *wp_idx_ref = wp_idx;
  *lcrow_idx_ref = lcrow_idx;
  *lcchild_idx_ref = lcchild_idx;
  *used_ref = used;
  *i_ref = i;
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
None
----------------------------
***/


static void layout_set_main_h(struct window *w)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  struct layout_cell *lcmain;
  unsigned int lcmain_idx = 0;
  struct layout_cell *lcrow;
  unsigned int lcrow_idx = 0;
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  u_int n;
  u_int mainheight;
  u_int otherheight;
  u_int width;
  u_int height;
  u_int used;
  u_int i;
  u_int j;
  u_int columns;
  u_int rows;
  u_int totalrows;
  layout_print_cell(w->layout_root, __func__, 1);
  n = window_count_panes(w);
  if (n <= 1)
  {
    return;
  }
  n -= 1;
  columns = (w->sx + 1) / (2 + 1);
  if (columns == 0)
  {
    columns = 1;
  }
  rows = 1 + ((n - 1) / columns);
  columns = 1 + ((n - 1) / rows);
  width = (w->sx - (n - 1)) / columns;
  mainheight = options_get_number(w->options, "main-pane-height") + 1;
  otherheight = options_get_number(w->options, "other-pane-height") + 1;
  if ((otherheight > 1) && ((w->sy - otherheight) > mainheight))
  {
    mainheight = w->sy - otherheight;
  }
  if (mainheight < (2 + 1))
  {
    mainheight = 2 + 1;
  }
  totalrows = (rows * (2 + 1)) - 1;
  if ((mainheight + totalrows) > w->sy)
  {
    if (((totalrows + 2) + 1) > w->sy)
    {
      mainheight = 2 + 2;
    }
    else
      mainheight = w->sy - totalrows;
    height = 2;
  }
  else
    height = ((w->sy - mainheight) - (rows - 1)) / rows;
  layout_free(w);
  lc_idx = (w->layout_root = layout_create_cell(0));
  layout_set_size(lc, w->sx, (mainheight + (rows * (height + 1))) - 1, 0, 0);
  layout_make_node(lc, LAYOUT_TOPBOTTOM);
  lcmain_idx = layout_create_cell(lc);
  layout_set_size(lcmain, w->sx, mainheight - 1, 0, 0);
  layout_make_leaf(lcmain, (&w->panes)->tqh_first);
  do
  {
    lcmain->entry.tqe_next = 0;
    lcmain->entry.tqe_prev = (&lc->cells)->tqh_last;
    *(&lc->cells)->tqh_last = &lcmain[lcmain_idx];
    (&lc->cells)->tqh_last = &lcmain->entry.tqe_next;
  }
  while (0);
  wp_idx = (&w->panes)->tqh_first->entry.tqe_next;
  for (j = 0; j < rows; j += 1)
  {
    helper_layout_set_main_h_1(&wp_idx, &lcrow_idx, &lcchild_idx, &used, &i, w, wp, lc, lcrow, lcchild, width, height, columns);
  }

  used = ((mainheight + (rows * height)) + rows) - 1;
  if (w->sy > used)
  {
    lcrow_idx = *((struct layout_cells *) (&lc->cells)->tqh_last)->tqh_last;
    layout_resize_adjust(w, lcrow, LAYOUT_TOPBOTTOM, w->sy - used);
  }
  layout_fix_offsets(lc);
  layout_fix_panes(w, w->sx, w->sy);
  layout_print_cell(w->layout_root, __func__, 1);
  notify_window("window-layout-changed", w);
  server_redraw_window(w);
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
void layout_free(struct window *w)
{
  layout_free_cell(w->layout_root);
}


----------------------------
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
void helper_layout_set_main_h_1(unsigned int * const wp_idx_ref, unsigned int * const lcrow_idx_ref, unsigned int * const lcchild_idx_ref, u_int * const used_ref, u_int * const i_ref, struct window * const w, struct window_pane * const wp, struct layout_cell * const lc, struct layout_cell * const lcrow, struct layout_cell * const lcchild, u_int width, u_int height, u_int columns)
{
  unsigned int wp_idx = *wp_idx_ref;
  unsigned int lcrow_idx = *lcrow_idx_ref;
  unsigned int lcchild_idx = *lcchild_idx_ref;
  u_int used = *used_ref;
  u_int i = *i_ref;
  if ((&wp[wp_idx]) == 0)
  {
    break;
  }
  lcrow_idx = layout_create_cell(lc);
  layout_set_size(lcrow, w->sx, height, 0, 0);
  do
  {
    lcrow->entry.tqe_next = 0;
    lcrow->entry.tqe_prev = (&lc->cells)->tqh_last;
    *(&lc->cells)->tqh_last = &lcrow[lcrow_idx];
    (&lc->cells)->tqh_last = &lcrow->entry.tqe_next;
  }
  while (0);
  if (columns == 1)
  {
    layout_make_leaf(lcrow, wp);
    wp_idx = wp_idx->entry.tqe_next;
    continue;
  }
  layout_make_node(lcrow, LAYOUT_LEFTRIGHT);
  for (i = 0; i < columns; i += 1)
  {
    lcchild_idx = layout_create_cell(lcrow);
    layout_set_size(lcchild, width, height, 0, 0);
    layout_make_leaf(lcchild, wp);
    do
    {
      lcchild->entry.tqe_next = 0;
      lcchild->entry.tqe_prev = (&lcrow->cells)->tqh_last;
      *(&lcrow->cells)->tqh_last = &lcchild[lcchild_idx];
      (&lcrow->cells)->tqh_last = &lcchild->entry.tqe_next;
    }
    while (0);
    if ((wp_idx = wp_idx->entry.tqe_next) == 0)
    {
      break;
    }
  }

  if (i == columns)
  {
    i -= 1;
  }
  used = ((i + 1) * (width + 1)) - 1;
  if (w->sx <= used)
  {
    continue;
  }
  lcchild_idx = *((struct layout_cells *) (&lcrow->cells)->tqh_last)->tqh_last;
  layout_resize_adjust(w, lcchild, LAYOUT_LEFTRIGHT, w->sx - used);
  *wp_idx_ref = wp_idx;
  *lcrow_idx_ref = lcrow_idx;
  *lcchild_idx_ref = lcchild_idx;
  *used_ref = used;
  *i_ref = i;
}


----------------------------
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


static void layout_set_even_h(struct window *w)
{
  layout_set_even(w, LAYOUT_LEFTRIGHT);
}


/*** DEPENDENCIES:
static void layout_set_even(struct window *w, enum layout_type type)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  struct layout_cell *lcnew;
  unsigned int lcnew_idx = 0;
  u_int n;
  layout_print_cell(w->layout_root, __func__, 1);
  n = window_count_panes(w);
  if (n <= 1)
  {
    return;
  }
  layout_free(w);
  lc_idx = (w->layout_root = layout_create_cell(0));
  layout_set_size(lc, w->sx, w->sy, 0, 0);
  layout_make_node(lc, type);
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    lcnew_idx = layout_create_cell(lc);
    layout_make_leaf(lcnew, wp);
    lcnew->sx = w->sx;
    lcnew->sy = w->sy;
    do
    {
      lcnew->entry.tqe_next = 0;
      lcnew->entry.tqe_prev = (&lc->cells)->tqh_last;
      *(&lc->cells)->tqh_last = &lcnew[lcnew_idx];
      (&lc->cells)->tqh_last = &lcnew->entry.tqe_next;
    }
    while (0);
  }

  layout_spread_cell(w, lc);
  layout_fix_offsets(lc);
  layout_fix_panes(w, w->sx, w->sy);
  layout_print_cell(w->layout_root, __func__, 1);
  notify_window("window-layout-changed", w);
  server_redraw_window(w);
}


----------------------------
None
----------------------------
***/


// hint:  ['wp_idx_ref is a mutable refrence to unsigned int', 'lcrow_idx_ref is a mutable refrence to unsigned int', 'lcchild_idx_ref is a mutable refrence to unsigned int', 'used_ref is a mutable refrence to u_int', 'i_ref is a mutable refrence to u_int']
void helper_layout_set_tiled_1(unsigned int * const wp_idx_ref, unsigned int * const lcrow_idx_ref, unsigned int * const lcchild_idx_ref, u_int * const used_ref, u_int * const i_ref, struct window * const w, struct window_pane * const wp, struct layout_cell * const lc, struct layout_cell * const lcrow, struct layout_cell * const lcchild, u_int n, u_int width, u_int height, u_int j, u_int columns)
{
  unsigned int wp_idx = *wp_idx_ref;
  unsigned int lcrow_idx = *lcrow_idx_ref;
  unsigned int lcchild_idx = *lcchild_idx_ref;
  u_int used = *used_ref;
  u_int i = *i_ref;
  if ((&wp[wp_idx]) == 0)
  {
    break;
  }
  lcrow_idx = layout_create_cell(lc);
  layout_set_size(lcrow, w->sx, height, 0, 0);
  do
  {
    lcrow->entry.tqe_next = 0;
    lcrow->entry.tqe_prev = (&lc->cells)->tqh_last;
    *(&lc->cells)->tqh_last = &lcrow[lcrow_idx];
    (&lc->cells)->tqh_last = &lcrow->entry.tqe_next;
  }
  while (0);
  if (((n - (j * columns)) == 1) || (columns == 1))
  {
    layout_make_leaf(lcrow, wp);
    wp_idx = wp_idx->entry.tqe_next;
    continue;
  }
  layout_make_node(lcrow, LAYOUT_LEFTRIGHT);
  for (i = 0; i < columns; i += 1)
  {
    lcchild_idx = layout_create_cell(lcrow);
    layout_set_size(lcchild, width, height, 0, 0);
    layout_make_leaf(lcchild, wp);
    do
    {
      lcchild->entry.tqe_next = 0;
      lcchild->entry.tqe_prev = (&lcrow->cells)->tqh_last;
      *(&lcrow->cells)->tqh_last = &lcchild[lcchild_idx];
      (&lcrow->cells)->tqh_last = &lcchild->entry.tqe_next;
    }
    while (0);
    if ((wp_idx = wp_idx->entry.tqe_next) == 0)
    {
      break;
    }
  }

  if (i == columns)
  {
    i -= 1;
  }
  used = ((i + 1) * (width + 1)) - 1;
  if (w->sx <= used)
  {
    continue;
  }
  lcchild_idx = *((struct layout_cells *) (&lcrow->cells)->tqh_last)->tqh_last;
  layout_resize_adjust(w, lcchild, LAYOUT_LEFTRIGHT, w->sx - used);
  *wp_idx_ref = wp_idx;
  *lcrow_idx_ref = lcrow_idx;
  *lcchild_idx_ref = lcchild_idx;
  *used_ref = used;
  *i_ref = i;
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
None
----------------------------
***/


void layout_set_tiled(struct window *w)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  struct layout_cell *lcrow;
  unsigned int lcrow_idx = 0;
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  u_int n;
  u_int width;
  u_int height;
  u_int used;
  u_int i;
  u_int j;
  u_int columns;
  u_int rows;
  layout_print_cell(w->layout_root, __func__, 1);
  n = window_count_panes(w);
  if (n <= 1)
  {
    return;
  }
  rows = (columns = 1);
  while ((rows * columns) < n)
  {
    rows += 1;
    if ((rows * columns) < n)
    {
      columns += 1;
    }
  }

  width = (w->sx - (columns - 1)) / columns;
  if (width < 2)
  {
    width = 2;
  }
  height = (w->sy - (rows - 1)) / rows;
  if (height < 2)
  {
    height = 2;
  }
  layout_free(w);
  lc_idx = (w->layout_root = layout_create_cell(0));
  layout_set_size(lc, ((width + 1) * columns) - 1, ((height + 1) * rows) - 1, 0, 0);
  layout_make_node(lc, LAYOUT_TOPBOTTOM);
  wp_idx = (&w->panes)->tqh_first;
  for (j = 0; j < rows; j += 1)
  {
    helper_layout_set_tiled_1(&wp_idx, &lcrow_idx, &lcchild_idx, &used, &i, w, wp, lc, lcrow, lcchild, n, width, height, j, columns);
  }

  used = ((rows * height) + rows) - 1;
  if (w->sy > used)
  {
    lcrow_idx = *((struct layout_cells *) (&lc->cells)->tqh_last)->tqh_last;
    layout_resize_adjust(w, lcrow, LAYOUT_TOPBOTTOM, w->sy - used);
  }
  layout_fix_offsets(lc);
  layout_fix_panes(w, w->sx, w->sy);
  layout_print_cell(w->layout_root, __func__, 1);
  notify_window("window-layout-changed", w);
  server_redraw_window(w);
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
void helper_layout_set_tiled_1(unsigned int * const wp_idx_ref, unsigned int * const lcrow_idx_ref, unsigned int * const lcchild_idx_ref, u_int * const used_ref, u_int * const i_ref, struct window * const w, struct window_pane * const wp, struct layout_cell * const lc, struct layout_cell * const lcrow, struct layout_cell * const lcchild, u_int n, u_int width, u_int height, u_int j, u_int columns)
{
  unsigned int wp_idx = *wp_idx_ref;
  unsigned int lcrow_idx = *lcrow_idx_ref;
  unsigned int lcchild_idx = *lcchild_idx_ref;
  u_int used = *used_ref;
  u_int i = *i_ref;
  if ((&wp[wp_idx]) == 0)
  {
    break;
  }
  lcrow_idx = layout_create_cell(lc);
  layout_set_size(lcrow, w->sx, height, 0, 0);
  do
  {
    lcrow->entry.tqe_next = 0;
    lcrow->entry.tqe_prev = (&lc->cells)->tqh_last;
    *(&lc->cells)->tqh_last = &lcrow[lcrow_idx];
    (&lc->cells)->tqh_last = &lcrow->entry.tqe_next;
  }
  while (0);
  if (((n - (j * columns)) == 1) || (columns == 1))
  {
    layout_make_leaf(lcrow, wp);
    wp_idx = wp_idx->entry.tqe_next;
    continue;
  }
  layout_make_node(lcrow, LAYOUT_LEFTRIGHT);
  for (i = 0; i < columns; i += 1)
  {
    lcchild_idx = layout_create_cell(lcrow);
    layout_set_size(lcchild, width, height, 0, 0);
    layout_make_leaf(lcchild, wp);
    do
    {
      lcchild->entry.tqe_next = 0;
      lcchild->entry.tqe_prev = (&lcrow->cells)->tqh_last;
      *(&lcrow->cells)->tqh_last = &lcchild[lcchild_idx];
      (&lcrow->cells)->tqh_last = &lcchild->entry.tqe_next;
    }
    while (0);
    if ((wp_idx = wp_idx->entry.tqe_next) == 0)
    {
      break;
    }
  }

  if (i == columns)
  {
    i -= 1;
  }
  used = ((i + 1) * (width + 1)) - 1;
  if (w->sx <= used)
  {
    continue;
  }
  lcchild_idx = *((struct layout_cells *) (&lcrow->cells)->tqh_last)->tqh_last;
  layout_resize_adjust(w, lcchild, LAYOUT_LEFTRIGHT, w->sx - used);
  *wp_idx_ref = wp_idx;
  *lcrow_idx_ref = lcrow_idx;
  *lcchild_idx_ref = lcchild_idx;
  *used_ref = used;
  *i_ref = i;
}


----------------------------
void layout_free(struct window *w)
{
  layout_free_cell(w->layout_root);
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


// hint:  ['wp_idx_ref is a mutable refrence to unsigned int', 'lccolumn_idx_ref is a mutable refrence to unsigned int', 'lcchild_idx_ref is a mutable refrence to unsigned int', 'used_ref is a mutable refrence to u_int', 'i_ref is a mutable refrence to u_int']
void helper_layout_set_main_v_1(unsigned int * const wp_idx_ref, unsigned int * const lccolumn_idx_ref, unsigned int * const lcchild_idx_ref, u_int * const used_ref, u_int * const i_ref, struct window * const w, struct window_pane * const wp, struct layout_cell * const lc, struct layout_cell * const lccolumn, struct layout_cell * const lcchild, u_int width, u_int height, u_int rows)
{
  unsigned int wp_idx = *wp_idx_ref;
  unsigned int lccolumn_idx = *lccolumn_idx_ref;
  unsigned int lcchild_idx = *lcchild_idx_ref;
  u_int used = *used_ref;
  u_int i = *i_ref;
  if ((&wp[wp_idx]) == 0)
  {
    break;
  }
  lccolumn_idx = layout_create_cell(lc);
  layout_set_size(lccolumn, width, w->sy, 0, 0);
  do
  {
    lccolumn->entry.tqe_next = 0;
    lccolumn->entry.tqe_prev = (&lc->cells)->tqh_last;
    *(&lc->cells)->tqh_last = &lccolumn[lccolumn_idx];
    (&lc->cells)->tqh_last = &lccolumn->entry.tqe_next;
  }
  while (0);
  if (rows == 1)
  {
    layout_make_leaf(lccolumn, wp);
    wp_idx = wp_idx->entry.tqe_next;
    continue;
  }
  layout_make_node(lccolumn, LAYOUT_TOPBOTTOM);
  for (i = 0; i < rows; i += 1)
  {
    lcchild_idx = layout_create_cell(lccolumn);
    layout_set_size(lcchild, width, height, 0, 0);
    layout_make_leaf(lcchild, wp);
    do
    {
      lcchild->entry.tqe_next = 0;
      lcchild->entry.tqe_prev = (&lccolumn->cells)->tqh_last;
      *(&lccolumn->cells)->tqh_last = &lcchild[lcchild_idx];
      (&lccolumn->cells)->tqh_last = &lcchild->entry.tqe_next;
    }
    while (0);
    if ((wp_idx = wp_idx->entry.tqe_next) == 0)
    {
      break;
    }
  }

  if (i == rows)
  {
    i -= 1;
  }
  used = ((i + 1) * (height + 1)) - 1;
  if (w->sy <= used)
  {
    continue;
  }
  lcchild_idx = *((struct layout_cells *) (&lccolumn->cells)->tqh_last)->tqh_last;
  layout_resize_adjust(w, lcchild, LAYOUT_TOPBOTTOM, w->sy - used);
  *wp_idx_ref = wp_idx;
  *lccolumn_idx_ref = lccolumn_idx;
  *lcchild_idx_ref = lcchild_idx;
  *used_ref = used;
  *i_ref = i;
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
None
----------------------------
***/


static void layout_set_main_v(struct window *w)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  struct layout_cell *lcmain;
  unsigned int lcmain_idx = 0;
  struct layout_cell *lccolumn;
  unsigned int lccolumn_idx = 0;
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  u_int n;
  u_int mainwidth;
  u_int otherwidth;
  u_int width;
  u_int height;
  u_int used;
  u_int i;
  u_int j;
  u_int columns;
  u_int rows;
  u_int totalcolumns;
  layout_print_cell(w->layout_root, __func__, 1);
  n = window_count_panes(w);
  if (n <= 1)
  {
    return;
  }
  n -= 1;
  rows = (w->sy + 1) / (2 + 1);
  if (rows == 0)
  {
    rows = 1;
  }
  columns = 1 + ((n - 1) / rows);
  rows = 1 + ((n - 1) / columns);
  height = (w->sy - (n - 1)) / rows;
  mainwidth = options_get_number(w->options, "main-pane-width") + 1;
  otherwidth = options_get_number(w->options, "other-pane-width") + 1;
  if ((otherwidth > 1) && ((w->sx - otherwidth) > mainwidth))
  {
    mainwidth = w->sx - otherwidth;
  }
  if (mainwidth < (2 + 1))
  {
    mainwidth = 2 + 1;
  }
  totalcolumns = (columns * (2 + 1)) - 1;
  if ((mainwidth + totalcolumns) > w->sx)
  {
    if (((totalcolumns + 2) + 1) > w->sx)
    {
      mainwidth = 2 + 2;
    }
    else
      mainwidth = w->sx - totalcolumns;
    width = 2;
  }
  else
    width = ((w->sx - mainwidth) - (columns - 1)) / columns;
  layout_free(w);
  lc_idx = (w->layout_root = layout_create_cell(0));
  layout_set_size(lc, (mainwidth + (columns * (width + 1))) - 1, w->sy, 0, 0);
  layout_make_node(lc, LAYOUT_LEFTRIGHT);
  lcmain_idx = layout_create_cell(lc);
  layout_set_size(lcmain, mainwidth - 1, w->sy, 0, 0);
  layout_make_leaf(lcmain, (&w->panes)->tqh_first);
  do
  {
    lcmain->entry.tqe_next = 0;
    lcmain->entry.tqe_prev = (&lc->cells)->tqh_last;
    *(&lc->cells)->tqh_last = &lcmain[lcmain_idx];
    (&lc->cells)->tqh_last = &lcmain->entry.tqe_next;
  }
  while (0);
  wp_idx = (&w->panes)->tqh_first->entry.tqe_next;
  for (j = 0; j < columns; j += 1)
  {
    helper_layout_set_main_v_1(&wp_idx, &lccolumn_idx, &lcchild_idx, &used, &i, w, wp, lc, lccolumn, lcchild, width, height, rows);
  }

  used = ((mainwidth + (columns * width)) + columns) - 1;
  if (w->sx > used)
  {
    lccolumn_idx = *((struct layout_cells *) (&lc->cells)->tqh_last)->tqh_last;
    layout_resize_adjust(w, lccolumn, LAYOUT_LEFTRIGHT, w->sx - used);
  }
  layout_fix_offsets(lc);
  layout_fix_panes(w, w->sx, w->sy);
  layout_print_cell(w->layout_root, __func__, 1);
  notify_window("window-layout-changed", w);
  server_redraw_window(w);
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
void layout_free(struct window *w)
{
  layout_free_cell(w->layout_root);
}


----------------------------
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
void layout_set_size(struct layout_cell *lc, u_int sx, u_int sy, u_int xoff, u_int yoff)
{
  lc->sx = sx;
  lc->sy = sy;
  lc->xoff = xoff;
  lc->yoff = yoff;
}


----------------------------
void helper_layout_set_main_v_1(unsigned int * const wp_idx_ref, unsigned int * const lccolumn_idx_ref, unsigned int * const lcchild_idx_ref, u_int * const used_ref, u_int * const i_ref, struct window * const w, struct window_pane * const wp, struct layout_cell * const lc, struct layout_cell * const lccolumn, struct layout_cell * const lcchild, u_int width, u_int height, u_int rows)
{
  unsigned int wp_idx = *wp_idx_ref;
  unsigned int lccolumn_idx = *lccolumn_idx_ref;
  unsigned int lcchild_idx = *lcchild_idx_ref;
  u_int used = *used_ref;
  u_int i = *i_ref;
  if ((&wp[wp_idx]) == 0)
  {
    break;
  }
  lccolumn_idx = layout_create_cell(lc);
  layout_set_size(lccolumn, width, w->sy, 0, 0);
  do
  {
    lccolumn->entry.tqe_next = 0;
    lccolumn->entry.tqe_prev = (&lc->cells)->tqh_last;
    *(&lc->cells)->tqh_last = &lccolumn[lccolumn_idx];
    (&lc->cells)->tqh_last = &lccolumn->entry.tqe_next;
  }
  while (0);
  if (rows == 1)
  {
    layout_make_leaf(lccolumn, wp);
    wp_idx = wp_idx->entry.tqe_next;
    continue;
  }
  layout_make_node(lccolumn, LAYOUT_TOPBOTTOM);
  for (i = 0; i < rows; i += 1)
  {
    lcchild_idx = layout_create_cell(lccolumn);
    layout_set_size(lcchild, width, height, 0, 0);
    layout_make_leaf(lcchild, wp);
    do
    {
      lcchild->entry.tqe_next = 0;
      lcchild->entry.tqe_prev = (&lccolumn->cells)->tqh_last;
      *(&lccolumn->cells)->tqh_last = &lcchild[lcchild_idx];
      (&lccolumn->cells)->tqh_last = &lcchild->entry.tqe_next;
    }
    while (0);
    if ((wp_idx = wp_idx->entry.tqe_next) == 0)
    {
      break;
    }
  }

  if (i == rows)
  {
    i -= 1;
  }
  used = ((i + 1) * (height + 1)) - 1;
  if (w->sy <= used)
  {
    continue;
  }
  lcchild_idx = *((struct layout_cells *) (&lccolumn->cells)->tqh_last)->tqh_last;
  layout_resize_adjust(w, lcchild, LAYOUT_TOPBOTTOM, w->sy - used);
  *wp_idx_ref = wp_idx;
  *lccolumn_idx_ref = lccolumn_idx;
  *lcchild_idx_ref = lcchild_idx;
  *used_ref = used;
  *i_ref = i;
}


----------------------------
None
----------------------------
***/


int layout_set_lookup(const char *name)
{
  u_int i;
  int matched = -1;
  for (i = 0; i < ((sizeof(layout_sets)) / (sizeof(layout_sets[0]))); i += 1)
  {
    if (strncmp(layout_sets[i].name, name, strlen(name)) == 0)
    {
      if (matched != (-1))
      {
        return -1;
      }
      matched = i;
    }
  }

  return matched;
}


/*** DEPENDENCIES:
static const struct 
{
  const char *name;
  void (*arrange)(struct window *);
} layout_sets[] = {{"even-horizontal", layout_set_even_h}, {"even-vertical", layout_set_even_v}, {"main-horizontal", layout_set_main_h}, {"main-vertical", layout_set_main_v}, {"tiled", layout_set_tiled}}
----------------------------
***/


u_int layout_set_select(struct window *w, u_int layout)
{
  if (layout > (((sizeof(layout_sets)) / (sizeof(layout_sets[0]))) - 1))
  {
    layout = ((sizeof(layout_sets)) / (sizeof(layout_sets[0]))) - 1;
  }
  if (layout_sets[layout].arrange != 0)
  {
    layout_sets[layout].arrange(w);
  }
  w->lastlayout = layout;
  return layout;
}


/*** DEPENDENCIES:
static const struct 
{
  const char *name;
  void (*arrange)(struct window *);
} layout_sets[] = {{"even-horizontal", layout_set_even_h}, {"even-vertical", layout_set_even_v}, {"main-horizontal", layout_set_main_h}, {"main-vertical", layout_set_main_v}, {"tiled", layout_set_tiled}}
----------------------------
None
----------------------------
***/


u_int layout_set_next(struct window *w)
{
  u_int layout;
  if (w->lastlayout == (-1))
  {
    layout = 0;
  }
  else
  {
    layout = w->lastlayout + 1;
    if (layout > (((sizeof(layout_sets)) / (sizeof(layout_sets[0]))) - 1))
    {
      layout = 0;
    }
  }
  if (layout_sets[layout].arrange != 0)
  {
    layout_sets[layout].arrange(w);
  }
  w->lastlayout = layout;
  return layout;
}


/*** DEPENDENCIES:
static const struct 
{
  const char *name;
  void (*arrange)(struct window *);
} layout_sets[] = {{"even-horizontal", layout_set_even_h}, {"even-vertical", layout_set_even_v}, {"main-horizontal", layout_set_main_h}, {"main-vertical", layout_set_main_v}, {"tiled", layout_set_tiled}}
----------------------------
None
----------------------------
***/


u_int layout_set_previous(struct window *w)
{
  u_int layout;
  if (w->lastlayout == (-1))
  {
    layout = ((sizeof(layout_sets)) / (sizeof(layout_sets[0]))) - 1;
  }
  else
  {
    layout = w->lastlayout;
    if (layout == 0)
    {
      layout = ((sizeof(layout_sets)) / (sizeof(layout_sets[0]))) - 1;
    }
    else
      layout--;
    layout -= 1;
  }
  if (layout_sets[layout].arrange != 0)
  {
    layout_sets[layout].arrange(w);
  }
  w->lastlayout = layout;
  return layout;
}


/*** DEPENDENCIES:
static const struct 
{
  const char *name;
  void (*arrange)(struct window *);
} layout_sets[] = {{"even-horizontal", layout_set_even_h}, {"even-vertical", layout_set_even_v}, {"main-horizontal", layout_set_main_h}, {"main-vertical", layout_set_main_v}, {"tiled", layout_set_tiled}}
----------------------------
None
----------------------------
***/


