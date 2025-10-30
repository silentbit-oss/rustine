// element in merge of:  layout_resize_child_cells,helper_layout_resize_child_cells_1
static void layout_resize_child_cells(struct window *w, struct layout_cell *lc)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  u_int previous;
  u_int available;
  u_int count;
  u_int idx;
  if (lc->type == LAYOUT_WINDOWPANE)
  {
    return;
  }
  count = 0;
  previous = 0;
  for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
  {
    count += 1;
    if (lc->type == LAYOUT_LEFTRIGHT)
    {
      previous += lcchild->sx;
    }
    else
      if (lc->type == LAYOUT_TOPBOTTOM)
    {
      previous += lcchild->sy;
    }
  }

  previous += count - 1;
  available = 0;
  if (lc->type == LAYOUT_LEFTRIGHT)
  {
    available = lc->sx;
  }
  else
    if (lc->type == LAYOUT_TOPBOTTOM)
  {
    available = lc->sy;
  }
  idx = 0;
  for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
  {
    helper_layout_resize_child_cells_1(&available, &idx, w, lc, lcchild, previous, count);
  }

}


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
***/


// element in merge of:  layout_resize_child_cells,helper_layout_resize_child_cells_1
// hint:  ['available_ref is a mutable refrence to u_int', 'idx_ref is a mutable refrence to u_int']
void helper_layout_resize_child_cells_1(u_int * const available_ref, u_int * const idx_ref, struct window * const w, struct layout_cell * const lc, struct layout_cell * const lcchild, u_int previous, u_int count)
{
  u_int available = *available_ref;
  u_int idx = *idx_ref;
  if (lc->type == LAYOUT_TOPBOTTOM)
  {
    lcchild->sx = lc->sx;
    lcchild->xoff = lc->xoff;
  }
  else
  {
    lcchild->sx = layout_new_pane_size(w, previous, lcchild, lc->type, lc->sx, count - idx, available);
    available -= lcchild->sx + 1;
  }
  if (lc->type == LAYOUT_LEFTRIGHT)
  {
    lcchild->sy = lc->sy;
  }
  else
  {
    lcchild->sy = layout_new_pane_size(w, previous, lcchild, lc->type, lc->sy, count - idx, available);
    available -= lcchild->sy + 1;
  }
  layout_resize_child_cells(w, lcchild);
  idx += 1;
  *available_ref = available;
  *idx_ref = idx;
}


/*** DEPENDENCIES:
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


----------------------------
None
----------------------------
None
----------------------------
***/


