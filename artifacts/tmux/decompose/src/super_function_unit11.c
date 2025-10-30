// element in merge of:  layout_set_size_check,helper_layout_set_size_check_1
static int layout_set_size_check(struct window *w, struct layout_cell *lc, enum layout_type type, int size)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  u_int new_size;
  u_int available;
  u_int previous;
  u_int count;
  u_int idx;
  if (lc->type == LAYOUT_WINDOWPANE)
  {
    return size >= 2;
  }
  available = size;
  count = 0;
  for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
  {
    count += 1;
  }

  if (lc->type == type)
  {
    helper_layout_set_size_check_1(&lcchild_idx, &new_size, &available, &previous, &idx, w, lc, type, size, lcchild, count);
  }
  else
  {
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      if (lcchild->type == LAYOUT_WINDOWPANE)
      {
        continue;
      }
      if (!layout_set_size_check(w, lcchild, type, size))
      {
        return 0;
      }
    }

  }
  return 1;
}


/*** DEPENDENCIES:
None
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


// element in merge of:  layout_set_size_check,helper_layout_set_size_check_1
// hint:  ['lcchild_idx_ref is a mutable refrence to unsigned int', 'new_size_ref is a mutable refrence to u_int', 'available_ref is a mutable refrence to u_int', 'previous_ref is a mutable refrence to u_int', 'idx_ref is a mutable refrence to u_int']
int helper_layout_set_size_check_1(unsigned int * const lcchild_idx_ref, u_int * const new_size_ref, u_int * const available_ref, u_int * const previous_ref, u_int * const idx_ref, struct window * const w, struct layout_cell * const lc, enum layout_type type, int size, struct layout_cell * const lcchild, u_int count)
{
  unsigned int lcchild_idx = *lcchild_idx_ref;
  u_int new_size = *new_size_ref;
  u_int available = *available_ref;
  u_int previous = *previous_ref;
  u_int idx = *idx_ref;
  if (type == LAYOUT_LEFTRIGHT)
  {
    previous = lc->sx;
  }
  else
    previous = lc->sy;
  idx = 0;
  for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
  {
    new_size = layout_new_pane_size(w, previous, lcchild, type, size, count - idx, available);
    if (new_size > available)
    {
      return 0;
    }
    available -= new_size + 1;
    if (!layout_set_size_check(w, lcchild, type, new_size))
    {
      return 0;
    }
    idx += 1;
  }

  *lcchild_idx_ref = lcchild_idx;
  *new_size_ref = new_size;
  *available_ref = available;
  *previous_ref = previous;
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


