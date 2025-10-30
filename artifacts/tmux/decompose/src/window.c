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


/*** DEPENDENCIES:
None
----------------------------
***/


void window_add_ref(struct window *w, const char *from)
{
  w->references += 1;
  log_debug("%s: @%u %s, now %d", __func__, w->id, from, w->references);
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


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'child_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'color_ref is a mutable refrence to int']
void helper_window_pane_tree_RB_REMOVE_1(unsigned int * const elm_idx_ref, unsigned int * const child_idx_ref, unsigned int * const parent_idx_ref, int * const color_ref, struct window_pane_tree * const head, struct window_pane * const elm, struct window_pane * const child, struct window_pane * const parent, struct window_pane * const old)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int child_idx = *child_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  int color = *color_ref;
  struct window_pane *left;
  unsigned int left_idx = 0;
  elm_idx = elm_idx->tree_entry.rbe_right;
  while (left_idx = elm->tree_entry.rbe_left)
  {
    elm_idx = &left[left_idx];
  }

  child_idx = elm->tree_entry.rbe_right;
  parent_idx = elm->tree_entry.rbe_parent;
  color = elm->tree_entry.rbe_color;
  if (child)
  {
    child->tree_entry.rbe_parent = &parent[parent_idx];
  }
  if (parent)
  {
    if (parent->tree_entry.rbe_left == (&elm[elm_idx]))
    {
      parent->tree_entry.rbe_left = &child[child_idx];
    }
    else
      parent->tree_entry.rbe_right = &child[child_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &child[child_idx];
  if (elm->tree_entry.rbe_parent == old)
  {
    parent_idx = &elm[elm_idx];
  }
  elm->tree_entry = old->tree_entry;
  if (old->tree_entry.rbe_parent)
  {
    if (old->tree_entry.rbe_parent->tree_entry.rbe_left == old)
    {
      old->tree_entry.rbe_parent->tree_entry.rbe_left = &elm[elm_idx];
    }
    else
      old->tree_entry.rbe_parent->tree_entry.rbe_right = &elm[elm_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &elm[elm_idx];
  old->tree_entry.rbe_left->tree_entry.rbe_parent = &elm[elm_idx];
  if (old->tree_entry.rbe_right)
  {
    old->tree_entry.rbe_right->tree_entry.rbe_parent = &elm[elm_idx];
  }
  if (parent)
  {
    left_idx = &parent[parent_idx];
    do
    {
      do
      {
      }
      while (0);
    }
    while (left_idx = left_idx->tree_entry.rbe_parent);
  }
  goto color;
  *elm_idx_ref = elm_idx;
  *child_idx_ref = child_idx;
  *parent_idx_ref = parent_idx;
  *color_ref = color;
}


/*** DEPENDENCIES:
struct window_pane_tree
{
  struct window_pane *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_1_2_1(unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->tree_entry.rbe_right;
  if (parent->tree_entry.rbe_right = tmp->tree_entry.rbe_left)
  {
    tmp->tree_entry.rbe_left->tree_entry.rbe_parent = &parent[parent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->tree_entry.rbe_parent = parent->tree_entry.rbe_parent)
  {
    if ((&parent[parent_idx]) == parent->tree_entry.rbe_parent->tree_entry.rbe_left)
    {
      parent->tree_entry.rbe_parent->tree_entry.rbe_left = &tmp[tmp_idx];
    }
    else
      parent->tree_entry.rbe_parent->tree_entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->tree_entry.rbe_left = &parent[parent_idx];
  parent->tree_entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->tree_entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct window_pane_tree
{
  struct window_pane *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_1_2_2(unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct window_pane *oleft;
  unsigned int oleft_idx = 0;
  if (oleft_idx = tmp->tree_entry.rbe_left)
  {
    oleft->tree_entry.rbe_color = 0;
  }
  tmp->tree_entry.rbe_color = 1;
  do
  {
    oleft_idx = tmp->tree_entry.rbe_left;
    if (tmp->tree_entry.rbe_left = oleft->tree_entry.rbe_right)
    {
      oleft->tree_entry.rbe_right->tree_entry.rbe_parent = &tmp[tmp_idx];
    }
    do
    {
    }
    while (0);
    if (oleft->tree_entry.rbe_parent = tmp->tree_entry.rbe_parent)
    {
      if ((&tmp[tmp_idx]) == tmp->tree_entry.rbe_parent->tree_entry.rbe_left)
      {
        tmp->tree_entry.rbe_parent->tree_entry.rbe_left = &oleft[oleft_idx];
      }
      else
        tmp->tree_entry.rbe_parent->tree_entry.rbe_right = &oleft[oleft_idx];
    }
    else
      head->rbh_root = &oleft[oleft_idx];
    oleft->tree_entry.rbe_right = &tmp[tmp_idx];
    tmp->tree_entry.rbe_parent = &oleft[oleft_idx];
    do
    {
    }
    while (0);
    if (oleft->tree_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->tree_entry.rbe_right;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct window_pane_tree
{
  struct window_pane *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->tree_entry.rbe_right == 0) || (tmp->tree_entry.rbe_right->tree_entry.rbe_color == 0))
  {
    helper_helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_1_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->tree_entry.rbe_color = parent->tree_entry.rbe_color;
  parent->tree_entry.rbe_color = 0;
  if (tmp->tree_entry.rbe_right)
  {
    tmp->tree_entry.rbe_right->tree_entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct window_pane_tree
{
  struct window_pane *rbh_root;
}
----------------------------
void helper_helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_1_2_1(unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->tree_entry.rbe_right;
  if (parent->tree_entry.rbe_right = tmp->tree_entry.rbe_left)
  {
    tmp->tree_entry.rbe_left->tree_entry.rbe_parent = &parent[parent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->tree_entry.rbe_parent = parent->tree_entry.rbe_parent)
  {
    if ((&parent[parent_idx]) == parent->tree_entry.rbe_parent->tree_entry.rbe_left)
    {
      parent->tree_entry.rbe_parent->tree_entry.rbe_left = &tmp[tmp_idx];
    }
    else
      parent->tree_entry.rbe_parent->tree_entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->tree_entry.rbe_left = &parent[parent_idx];
  parent->tree_entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->tree_entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_1_2_2(unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct window_pane *oleft;
  unsigned int oleft_idx = 0;
  if (oleft_idx = tmp->tree_entry.rbe_left)
  {
    oleft->tree_entry.rbe_color = 0;
  }
  tmp->tree_entry.rbe_color = 1;
  do
  {
    oleft_idx = tmp->tree_entry.rbe_left;
    if (tmp->tree_entry.rbe_left = oleft->tree_entry.rbe_right)
    {
      oleft->tree_entry.rbe_right->tree_entry.rbe_parent = &tmp[tmp_idx];
    }
    do
    {
    }
    while (0);
    if (oleft->tree_entry.rbe_parent = tmp->tree_entry.rbe_parent)
    {
      if ((&tmp[tmp_idx]) == tmp->tree_entry.rbe_parent->tree_entry.rbe_left)
      {
        tmp->tree_entry.rbe_parent->tree_entry.rbe_left = &oleft[oleft_idx];
      }
      else
        tmp->tree_entry.rbe_parent->tree_entry.rbe_right = &oleft[oleft_idx];
    }
    else
      head->rbh_root = &oleft[oleft_idx];
    oleft->tree_entry.rbe_right = &tmp[tmp_idx];
    tmp->tree_entry.rbe_parent = &oleft[oleft_idx];
    do
    {
    }
    while (0);
    if (oleft->tree_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->tree_entry.rbe_right;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp->tree_entry.rbe_color = 0;
    parent->tree_entry.rbe_color = 1;
  }
  while (0);
  do
  {
    tmp_idx = parent->tree_entry.rbe_right;
    if (parent->tree_entry.rbe_right = tmp->tree_entry.rbe_left)
    {
      tmp->tree_entry.rbe_left->tree_entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->tree_entry.rbe_parent = parent->tree_entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->tree_entry.rbe_parent->tree_entry.rbe_left)
      {
        parent->tree_entry.rbe_parent->tree_entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->tree_entry.rbe_parent->tree_entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->tree_entry.rbe_left = &parent[parent_idx];
    parent->tree_entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->tree_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->tree_entry.rbe_right;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct window_pane_tree
{
  struct window_pane *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const elm, struct window_pane * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->tree_entry.rbe_right;
  if (tmp->tree_entry.rbe_color == 1)
  {
    helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_1_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->tree_entry.rbe_left == 0) || (tmp->tree_entry.rbe_left->tree_entry.rbe_color == 0)) && ((tmp->tree_entry.rbe_right == 0) || (tmp->tree_entry.rbe_right->tree_entry.rbe_color == 0)))
  {
    tmp->tree_entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->tree_entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_1_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct window_pane_tree
{
  struct window_pane *rbh_root;
}
----------------------------
void helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->tree_entry.rbe_right == 0) || (tmp->tree_entry.rbe_right->tree_entry.rbe_color == 0))
  {
    helper_helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_1_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->tree_entry.rbe_color = parent->tree_entry.rbe_color;
  parent->tree_entry.rbe_color = 0;
  if (tmp->tree_entry.rbe_right)
  {
    tmp->tree_entry.rbe_right->tree_entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp->tree_entry.rbe_color = 0;
    parent->tree_entry.rbe_color = 1;
  }
  while (0);
  do
  {
    tmp_idx = parent->tree_entry.rbe_right;
    if (parent->tree_entry.rbe_right = tmp->tree_entry.rbe_left)
    {
      tmp->tree_entry.rbe_left->tree_entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->tree_entry.rbe_parent = parent->tree_entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->tree_entry.rbe_parent->tree_entry.rbe_left)
      {
        parent->tree_entry.rbe_parent->tree_entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->tree_entry.rbe_parent->tree_entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->tree_entry.rbe_left = &parent[parent_idx];
    parent->tree_entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->tree_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->tree_entry.rbe_right;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_2_2_2(unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct window_pane *oright;
  unsigned int oright_idx = 0;
  if (oright_idx = tmp->tree_entry.rbe_right)
  {
    oright->tree_entry.rbe_color = 0;
  }
  tmp->tree_entry.rbe_color = 1;
  do
  {
    oright_idx = tmp->tree_entry.rbe_right;
    if (tmp->tree_entry.rbe_right = oright->tree_entry.rbe_left)
    {
      oright->tree_entry.rbe_left->tree_entry.rbe_parent = &tmp[tmp_idx];
    }
    do
    {
    }
    while (0);
    if (oright->tree_entry.rbe_parent = tmp->tree_entry.rbe_parent)
    {
      if ((&tmp[tmp_idx]) == tmp->tree_entry.rbe_parent->tree_entry.rbe_left)
      {
        tmp->tree_entry.rbe_parent->tree_entry.rbe_left = &oright[oright_idx];
      }
      else
        tmp->tree_entry.rbe_parent->tree_entry.rbe_right = &oright[oright_idx];
    }
    else
      head->rbh_root = &oright[oright_idx];
    oright->tree_entry.rbe_left = &tmp[tmp_idx];
    tmp->tree_entry.rbe_parent = &oright[oright_idx];
    do
    {
    }
    while (0);
    if (oright->tree_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->tree_entry.rbe_left;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct window_pane_tree
{
  struct window_pane *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_2_2_1(unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->tree_entry.rbe_left;
  if (parent->tree_entry.rbe_left = tmp->tree_entry.rbe_right)
  {
    tmp->tree_entry.rbe_right->tree_entry.rbe_parent = &parent[parent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->tree_entry.rbe_parent = parent->tree_entry.rbe_parent)
  {
    if ((&parent[parent_idx]) == parent->tree_entry.rbe_parent->tree_entry.rbe_left)
    {
      parent->tree_entry.rbe_parent->tree_entry.rbe_left = &tmp[tmp_idx];
    }
    else
      parent->tree_entry.rbe_parent->tree_entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->tree_entry.rbe_right = &parent[parent_idx];
  parent->tree_entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->tree_entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct window_pane_tree
{
  struct window_pane *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->tree_entry.rbe_left == 0) || (tmp->tree_entry.rbe_left->tree_entry.rbe_color == 0))
  {
    helper_helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_2_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->tree_entry.rbe_color = parent->tree_entry.rbe_color;
  parent->tree_entry.rbe_color = 0;
  if (tmp->tree_entry.rbe_left)
  {
    tmp->tree_entry.rbe_left->tree_entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_2_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct window_pane_tree
{
  struct window_pane *rbh_root;
}
----------------------------
void helper_helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_2_2_2(unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct window_pane *oright;
  unsigned int oright_idx = 0;
  if (oright_idx = tmp->tree_entry.rbe_right)
  {
    oright->tree_entry.rbe_color = 0;
  }
  tmp->tree_entry.rbe_color = 1;
  do
  {
    oright_idx = tmp->tree_entry.rbe_right;
    if (tmp->tree_entry.rbe_right = oright->tree_entry.rbe_left)
    {
      oright->tree_entry.rbe_left->tree_entry.rbe_parent = &tmp[tmp_idx];
    }
    do
    {
    }
    while (0);
    if (oright->tree_entry.rbe_parent = tmp->tree_entry.rbe_parent)
    {
      if ((&tmp[tmp_idx]) == tmp->tree_entry.rbe_parent->tree_entry.rbe_left)
      {
        tmp->tree_entry.rbe_parent->tree_entry.rbe_left = &oright[oright_idx];
      }
      else
        tmp->tree_entry.rbe_parent->tree_entry.rbe_right = &oright[oright_idx];
    }
    else
      head->rbh_root = &oright[oright_idx];
    oright->tree_entry.rbe_left = &tmp[tmp_idx];
    tmp->tree_entry.rbe_parent = &oright[oright_idx];
    do
    {
    }
    while (0);
    if (oright->tree_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->tree_entry.rbe_left;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_2_2_1(unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->tree_entry.rbe_left;
  if (parent->tree_entry.rbe_left = tmp->tree_entry.rbe_right)
  {
    tmp->tree_entry.rbe_right->tree_entry.rbe_parent = &parent[parent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->tree_entry.rbe_parent = parent->tree_entry.rbe_parent)
  {
    if ((&parent[parent_idx]) == parent->tree_entry.rbe_parent->tree_entry.rbe_left)
    {
      parent->tree_entry.rbe_parent->tree_entry.rbe_left = &tmp[tmp_idx];
    }
    else
      parent->tree_entry.rbe_parent->tree_entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->tree_entry.rbe_right = &parent[parent_idx];
  parent->tree_entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->tree_entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp->tree_entry.rbe_color = 0;
    parent->tree_entry.rbe_color = 1;
  }
  while (0);
  do
  {
    tmp_idx = parent->tree_entry.rbe_left;
    if (parent->tree_entry.rbe_left = tmp->tree_entry.rbe_right)
    {
      tmp->tree_entry.rbe_right->tree_entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->tree_entry.rbe_parent = parent->tree_entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->tree_entry.rbe_parent->tree_entry.rbe_left)
      {
        parent->tree_entry.rbe_parent->tree_entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->tree_entry.rbe_parent->tree_entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->tree_entry.rbe_right = &parent[parent_idx];
    parent->tree_entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->tree_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->tree_entry.rbe_left;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct window_pane_tree
{
  struct window_pane *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const elm, struct window_pane * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->tree_entry.rbe_left;
  if (tmp->tree_entry.rbe_color == 1)
  {
    helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->tree_entry.rbe_left == 0) || (tmp->tree_entry.rbe_left->tree_entry.rbe_color == 0)) && ((tmp->tree_entry.rbe_right == 0) || (tmp->tree_entry.rbe_right->tree_entry.rbe_color == 0)))
  {
    tmp->tree_entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->tree_entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_2_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct window_pane_tree
{
  struct window_pane *rbh_root;
}
----------------------------
void helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->tree_entry.rbe_left == 0) || (tmp->tree_entry.rbe_left->tree_entry.rbe_color == 0))
  {
    helper_helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_2_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->tree_entry.rbe_color = parent->tree_entry.rbe_color;
  parent->tree_entry.rbe_color = 0;
  if (tmp->tree_entry.rbe_left)
  {
    tmp->tree_entry.rbe_left->tree_entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_2_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp->tree_entry.rbe_color = 0;
    parent->tree_entry.rbe_color = 1;
  }
  while (0);
  do
  {
    tmp_idx = parent->tree_entry.rbe_left;
    if (parent->tree_entry.rbe_left = tmp->tree_entry.rbe_right)
    {
      tmp->tree_entry.rbe_right->tree_entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->tree_entry.rbe_parent = parent->tree_entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->tree_entry.rbe_parent->tree_entry.rbe_left)
      {
        parent->tree_entry.rbe_parent->tree_entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->tree_entry.rbe_parent->tree_entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->tree_entry.rbe_right = &parent[parent_idx];
    parent->tree_entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->tree_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->tree_entry.rbe_left;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_window_pane_tree_RB_REMOVE_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const elm, struct window_pane * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if (parent->tree_entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  else
  {
    helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct window_pane_tree
{
  struct window_pane *rbh_root;
}
----------------------------
void helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const elm, struct window_pane * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->tree_entry.rbe_right;
  if (tmp->tree_entry.rbe_color == 1)
  {
    helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_1_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->tree_entry.rbe_left == 0) || (tmp->tree_entry.rbe_left->tree_entry.rbe_color == 0)) && ((tmp->tree_entry.rbe_right == 0) || (tmp->tree_entry.rbe_right->tree_entry.rbe_color == 0)))
  {
    tmp->tree_entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->tree_entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_1_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const elm, struct window_pane * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->tree_entry.rbe_left;
  if (tmp->tree_entry.rbe_color == 1)
  {
    helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->tree_entry.rbe_left == 0) || (tmp->tree_entry.rbe_left->tree_entry.rbe_color == 0)) && ((tmp->tree_entry.rbe_right == 0) || (tmp->tree_entry.rbe_right->tree_entry.rbe_color == 0)))
  {
    tmp->tree_entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->tree_entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_2_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


void window_pane_tree_RB_REMOVE_COLOR(struct window_pane_tree *head, struct window_pane *parent, struct window_pane *elm)
{
  unsigned int elm_idx = 0;
  unsigned int parent_idx = 0;
  struct window_pane *tmp;
  unsigned int tmp_idx = 0;
  while ((((&elm[elm_idx]) == 0) || (elm->tree_entry.rbe_color == 0)) && ((&elm[elm_idx]) != head->rbh_root))
  {
    helper_window_pane_tree_RB_REMOVE_COLOR_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }

  if (elm)
  {
    elm->tree_entry.rbe_color = 0;
  }
}


/*** DEPENDENCIES:
struct window_pane_tree
{
  struct window_pane *rbh_root;
}
----------------------------
void helper_window_pane_tree_RB_REMOVE_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const parent, struct window_pane * const elm, struct window_pane * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if (parent->tree_entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  else
  {
    helper_helper_window_pane_tree_RB_REMOVE_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


struct window_pane *window_pane_tree_RB_REMOVE(struct window_pane_tree *head, struct window_pane *elm)
{
  unsigned int elm_idx = 0;
  struct window_pane *child;
  unsigned int child_idx = 0;
  struct window_pane *parent;
  unsigned int parent_idx = 0;
  struct window_pane *old = elm;
  int color;
  if (elm->tree_entry.rbe_left == 0)
  {
    child_idx = elm->tree_entry.rbe_right;
  }
  else
    if (elm->tree_entry.rbe_right == 0)
  {
    child_idx = elm->tree_entry.rbe_left;
  }
  else
  {
    helper_window_pane_tree_RB_REMOVE_1(&elm_idx, &child_idx, &parent_idx, &color, head, elm, child, parent, old);
  }
  parent_idx = elm->tree_entry.rbe_parent;
  color = elm->tree_entry.rbe_color;
  if (child)
  {
    child->tree_entry.rbe_parent = &parent[parent_idx];
  }
  if (parent)
  {
    if (parent->tree_entry.rbe_left == (&elm[elm_idx]))
    {
      parent->tree_entry.rbe_left = &child[child_idx];
    }
    else
      parent->tree_entry.rbe_right = &child[child_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &child[child_idx];
  color:
  if (color == 0)
  {
    window_pane_tree_RB_REMOVE_COLOR(head, parent, child);
  }

  return old;
}


/*** DEPENDENCIES:
struct window_pane_tree
{
  struct window_pane *rbh_root;
}
----------------------------
void helper_window_pane_tree_RB_REMOVE_1(unsigned int * const elm_idx_ref, unsigned int * const child_idx_ref, unsigned int * const parent_idx_ref, int * const color_ref, struct window_pane_tree * const head, struct window_pane * const elm, struct window_pane * const child, struct window_pane * const parent, struct window_pane * const old)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int child_idx = *child_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  int color = *color_ref;
  struct window_pane *left;
  unsigned int left_idx = 0;
  elm_idx = elm_idx->tree_entry.rbe_right;
  while (left_idx = elm->tree_entry.rbe_left)
  {
    elm_idx = &left[left_idx];
  }

  child_idx = elm->tree_entry.rbe_right;
  parent_idx = elm->tree_entry.rbe_parent;
  color = elm->tree_entry.rbe_color;
  if (child)
  {
    child->tree_entry.rbe_parent = &parent[parent_idx];
  }
  if (parent)
  {
    if (parent->tree_entry.rbe_left == (&elm[elm_idx]))
    {
      parent->tree_entry.rbe_left = &child[child_idx];
    }
    else
      parent->tree_entry.rbe_right = &child[child_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &child[child_idx];
  if (elm->tree_entry.rbe_parent == old)
  {
    parent_idx = &elm[elm_idx];
  }
  elm->tree_entry = old->tree_entry;
  if (old->tree_entry.rbe_parent)
  {
    if (old->tree_entry.rbe_parent->tree_entry.rbe_left == old)
    {
      old->tree_entry.rbe_parent->tree_entry.rbe_left = &elm[elm_idx];
    }
    else
      old->tree_entry.rbe_parent->tree_entry.rbe_right = &elm[elm_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &elm[elm_idx];
  old->tree_entry.rbe_left->tree_entry.rbe_parent = &elm[elm_idx];
  if (old->tree_entry.rbe_right)
  {
    old->tree_entry.rbe_right->tree_entry.rbe_parent = &elm[elm_idx];
  }
  if (parent)
  {
    left_idx = &parent[parent_idx];
    do
    {
      do
      {
      }
      while (0);
    }
    while (left_idx = left_idx->tree_entry.rbe_parent);
  }
  goto color;
  *elm_idx_ref = elm_idx;
  *child_idx_ref = child_idx;
  *parent_idx_ref = parent_idx;
  *color_ref = color;
}


----------------------------
void window_pane_tree_RB_REMOVE_COLOR(struct window_pane_tree *head, struct window_pane *parent, struct window_pane *elm)
{
  unsigned int elm_idx = 0;
  unsigned int parent_idx = 0;
  struct window_pane *tmp;
  unsigned int tmp_idx = 0;
  while ((((&elm[elm_idx]) == 0) || (elm->tree_entry.rbe_color == 0)) && ((&elm[elm_idx]) != head->rbh_root))
  {
    helper_window_pane_tree_RB_REMOVE_COLOR_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }

  if (elm)
  {
    elm->tree_entry.rbe_color = 0;
  }
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
None
----------------------------
***/


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


/*** DEPENDENCIES:
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
None
----------------------------
***/


struct winlink *winlink_find_by_window_id(struct winlinks *wwl, u_int id)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  for (wl_idx = winlinks_RB_MINMAX(wwl, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    if (wl->window->id == id)
    {
      return wl;
    }
  }

  return 0;
}


/*** DEPENDENCIES:
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
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
None
----------------------------
***/


int window_has_pane(struct window *w, struct window_pane *wp)
{
  struct window_pane *wp1;
  unsigned int wp1_idx = 0;
  for (wp1_idx = (&w->panes)->tqh_first; (&wp1[wp1_idx]) != 0; wp1_idx = wp1_idx->entry.tqe_next)
  {
    if ((&wp1[wp1_idx]) == wp)
    {
      return 1;
    }
  }

  return 0;
}


/*** DEPENDENCIES:
None
----------------------------
***/


u_int window_pane_search(struct window_pane *wp, const char *searchstr)
{
  struct screen *s = &wp->base;
  char *newsearchstr;
  char *line;
  unsigned int line_idx = 0;
  u_int i;
  xasprintf(&newsearchstr, "*%s*", searchstr);
  for (i = 0; i < s->grid->sy; i += 1)
  {
    line_idx = grid_view_string_cells(s->grid, 0, i, s->grid->sx);
    if (fnmatch(newsearchstr, line, 0) == 0)
    {
      free(line);
      break;
    }
    free(line);
  }

  free(newsearchstr);
  if (i == s->grid->sy)
  {
    return 0;
  }
  return i + 1;
}


/*** DEPENDENCIES:
None
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
char *grid_view_string_cells(struct grid *gd, u_int px, u_int py, u_int nx)
{
  px = px;
  py = gd->hsize + py;
  return grid_string_cells(gd, px, py, nx, 0, 0, 0, 0);
}


----------------------------
None
----------------------------
***/


u_int winlink_count(struct winlinks *wwl)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  u_int n;
  n = 0;
  for (wl_idx = winlinks_RB_MINMAX(wwl, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    n += 1;
  }

  return n;
}


/*** DEPENDENCIES:
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
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
None
----------------------------
***/


const char *window_printable_flags(struct winlink *wl)
{
  struct session *s = wl->session;
  static char flags[32];
  int pos;
  pos = 0;
  if (wl->flags & 0x2)
  {
    flags[pos] = '#';
    pos += 1;
  }
  if (wl->flags & 0x1)
  {
    flags[pos] = '!';
    pos += 1;
  }
  if (wl->flags & 0x4)
  {
    flags[pos] = '~';
    pos += 1;
  }
  if (wl == s->curw)
  {
    flags[pos] = '*';
    pos += 1;
  }
  if (wl == (&s->lastw)->tqh_first)
  {
    flags[pos] = '-';
    pos += 1;
  }
  if (server_check_marked() && (wl == marked_pane.wl))
  {
    flags[pos] = 'M';
    pos += 1;
  }
  if (wl->window->flags & 0x1000)
  {
    flags[pos] = 'Z';
    pos += 1;
  }
  flags[pos] = '\0';
  return flags;
}


/*** DEPENDENCIES:
extern struct cmd_find_state marked_pane
----------------------------
int server_check_marked(void)
{
  return cmd_find_valid_state(&marked_pane);
}


----------------------------
None
----------------------------
***/


struct winlink *winlink_find_by_window(struct winlinks *wwl, struct window *w)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  for (wl_idx = winlinks_RB_MINMAX(wwl, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    if (wl->window == w)
    {
      return wl;
    }
  }

  return 0;
}


/*** DEPENDENCIES:
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
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_windows_RB_REMOVE_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp->entry.rbe_color = 0;
    parent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    tmp_idx = parent->entry.rbe_left;
    if (parent->entry.rbe_left = tmp->entry.rbe_right)
    {
      tmp->entry.rbe_right->entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
      {
        parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->entry.rbe_right = &parent[parent_idx];
    parent->entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->entry.rbe_left;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_windows_RB_REMOVE_COLOR_1_2_2_2(unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct window *oright;
  unsigned int oright_idx = 0;
  if (oright_idx = tmp->entry.rbe_right)
  {
    oright->entry.rbe_color = 0;
  }
  tmp->entry.rbe_color = 1;
  do
  {
    oright_idx = tmp->entry.rbe_right;
    if (tmp->entry.rbe_right = oright->entry.rbe_left)
    {
      oright->entry.rbe_left->entry.rbe_parent = &tmp[tmp_idx];
    }
    do
    {
    }
    while (0);
    if (oright->entry.rbe_parent = tmp->entry.rbe_parent)
    {
      if ((&tmp[tmp_idx]) == tmp->entry.rbe_parent->entry.rbe_left)
      {
        tmp->entry.rbe_parent->entry.rbe_left = &oright[oright_idx];
      }
      else
        tmp->entry.rbe_parent->entry.rbe_right = &oright[oright_idx];
    }
    else
      head->rbh_root = &oright[oright_idx];
    oright->entry.rbe_left = &tmp[tmp_idx];
    tmp->entry.rbe_parent = &oright[oright_idx];
    do
    {
    }
    while (0);
    if (oright->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->entry.rbe_left;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_windows_RB_REMOVE_COLOR_1_2_2_1(unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_left;
  if (parent->entry.rbe_left = tmp->entry.rbe_right)
  {
    tmp->entry.rbe_right->entry.rbe_parent = &parent[parent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
  {
    if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
    {
      parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
    }
    else
      parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->entry.rbe_right = &parent[parent_idx];
  parent->entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_windows_RB_REMOVE_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_windows_RB_REMOVE_COLOR_1_2_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_left)
  {
    tmp->entry.rbe_left->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_windows_RB_REMOVE_COLOR_1_2_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
void helper_helper_helper_helper_windows_RB_REMOVE_COLOR_1_2_2_2(unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct window *oright;
  unsigned int oright_idx = 0;
  if (oright_idx = tmp->entry.rbe_right)
  {
    oright->entry.rbe_color = 0;
  }
  tmp->entry.rbe_color = 1;
  do
  {
    oright_idx = tmp->entry.rbe_right;
    if (tmp->entry.rbe_right = oright->entry.rbe_left)
    {
      oright->entry.rbe_left->entry.rbe_parent = &tmp[tmp_idx];
    }
    do
    {
    }
    while (0);
    if (oright->entry.rbe_parent = tmp->entry.rbe_parent)
    {
      if ((&tmp[tmp_idx]) == tmp->entry.rbe_parent->entry.rbe_left)
      {
        tmp->entry.rbe_parent->entry.rbe_left = &oright[oright_idx];
      }
      else
        tmp->entry.rbe_parent->entry.rbe_right = &oright[oright_idx];
    }
    else
      head->rbh_root = &oright[oright_idx];
    oright->entry.rbe_left = &tmp[tmp_idx];
    tmp->entry.rbe_parent = &oright[oright_idx];
    do
    {
    }
    while (0);
    if (oright->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->entry.rbe_left;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_helper_helper_windows_RB_REMOVE_COLOR_1_2_2_1(unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_left;
  if (parent->entry.rbe_left = tmp->entry.rbe_right)
  {
    tmp->entry.rbe_right->entry.rbe_parent = &parent[parent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
  {
    if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
    {
      parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
    }
    else
      parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->entry.rbe_right = &parent[parent_idx];
  parent->entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_windows_RB_REMOVE_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const elm, struct window * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_left;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_windows_RB_REMOVE_COLOR_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_windows_RB_REMOVE_COLOR_1_2_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
void helper_helper_helper_windows_RB_REMOVE_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp->entry.rbe_color = 0;
    parent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    tmp_idx = parent->entry.rbe_left;
    if (parent->entry.rbe_left = tmp->entry.rbe_right)
    {
      tmp->entry.rbe_right->entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
      {
        parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->entry.rbe_right = &parent[parent_idx];
    parent->entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->entry.rbe_left;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_helper_windows_RB_REMOVE_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_windows_RB_REMOVE_COLOR_1_2_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_left)
  {
    tmp->entry.rbe_left->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_windows_RB_REMOVE_COLOR_1_2_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_windows_RB_REMOVE_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp->entry.rbe_color = 0;
    parent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    tmp_idx = parent->entry.rbe_right;
    if (parent->entry.rbe_right = tmp->entry.rbe_left)
    {
      tmp->entry.rbe_left->entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
      {
        parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->entry.rbe_left = &parent[parent_idx];
    parent->entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->entry.rbe_right;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_windows_RB_REMOVE_COLOR_1_1_2_1(unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_right;
  if (parent->entry.rbe_right = tmp->entry.rbe_left)
  {
    tmp->entry.rbe_left->entry.rbe_parent = &parent[parent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
  {
    if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
    {
      parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
    }
    else
      parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->entry.rbe_left = &parent[parent_idx];
  parent->entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_windows_RB_REMOVE_COLOR_1_1_2_2(unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct window *oleft;
  unsigned int oleft_idx = 0;
  if (oleft_idx = tmp->entry.rbe_left)
  {
    oleft->entry.rbe_color = 0;
  }
  tmp->entry.rbe_color = 1;
  do
  {
    oleft_idx = tmp->entry.rbe_left;
    if (tmp->entry.rbe_left = oleft->entry.rbe_right)
    {
      oleft->entry.rbe_right->entry.rbe_parent = &tmp[tmp_idx];
    }
    do
    {
    }
    while (0);
    if (oleft->entry.rbe_parent = tmp->entry.rbe_parent)
    {
      if ((&tmp[tmp_idx]) == tmp->entry.rbe_parent->entry.rbe_left)
      {
        tmp->entry.rbe_parent->entry.rbe_left = &oleft[oleft_idx];
      }
      else
        tmp->entry.rbe_parent->entry.rbe_right = &oleft[oleft_idx];
    }
    else
      head->rbh_root = &oleft[oleft_idx];
    oleft->entry.rbe_right = &tmp[tmp_idx];
    tmp->entry.rbe_parent = &oleft[oleft_idx];
    do
    {
    }
    while (0);
    if (oleft->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->entry.rbe_right;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_windows_RB_REMOVE_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_windows_RB_REMOVE_COLOR_1_1_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_right)
  {
    tmp->entry.rbe_right->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_windows_RB_REMOVE_COLOR_1_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
void helper_helper_helper_helper_windows_RB_REMOVE_COLOR_1_1_2_1(unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_right;
  if (parent->entry.rbe_right = tmp->entry.rbe_left)
  {
    tmp->entry.rbe_left->entry.rbe_parent = &parent[parent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
  {
    if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
    {
      parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
    }
    else
      parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->entry.rbe_left = &parent[parent_idx];
  parent->entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_helper_helper_windows_RB_REMOVE_COLOR_1_1_2_2(unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct window *oleft;
  unsigned int oleft_idx = 0;
  if (oleft_idx = tmp->entry.rbe_left)
  {
    oleft->entry.rbe_color = 0;
  }
  tmp->entry.rbe_color = 1;
  do
  {
    oleft_idx = tmp->entry.rbe_left;
    if (tmp->entry.rbe_left = oleft->entry.rbe_right)
    {
      oleft->entry.rbe_right->entry.rbe_parent = &tmp[tmp_idx];
    }
    do
    {
    }
    while (0);
    if (oleft->entry.rbe_parent = tmp->entry.rbe_parent)
    {
      if ((&tmp[tmp_idx]) == tmp->entry.rbe_parent->entry.rbe_left)
      {
        tmp->entry.rbe_parent->entry.rbe_left = &oleft[oleft_idx];
      }
      else
        tmp->entry.rbe_parent->entry.rbe_right = &oleft[oleft_idx];
    }
    else
      head->rbh_root = &oleft[oleft_idx];
    oleft->entry.rbe_right = &tmp[tmp_idx];
    tmp->entry.rbe_parent = &oleft[oleft_idx];
    do
    {
    }
    while (0);
    if (oleft->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->entry.rbe_right;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_windows_RB_REMOVE_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const elm, struct window * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_right;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_windows_RB_REMOVE_COLOR_1_1_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_windows_RB_REMOVE_COLOR_1_1_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
void helper_helper_helper_windows_RB_REMOVE_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp->entry.rbe_color = 0;
    parent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    tmp_idx = parent->entry.rbe_right;
    if (parent->entry.rbe_right = tmp->entry.rbe_left)
    {
      tmp->entry.rbe_left->entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
      {
        parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->entry.rbe_left = &parent[parent_idx];
    parent->entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->entry.rbe_right;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_helper_windows_RB_REMOVE_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_windows_RB_REMOVE_COLOR_1_1_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_right)
  {
    tmp->entry.rbe_right->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_windows_RB_REMOVE_COLOR_1_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_windows_RB_REMOVE_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const elm, struct window * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if (parent->entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_windows_RB_REMOVE_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  else
  {
    helper_helper_windows_RB_REMOVE_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
void helper_helper_windows_RB_REMOVE_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const elm, struct window * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_left;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_windows_RB_REMOVE_COLOR_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_windows_RB_REMOVE_COLOR_1_2_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_windows_RB_REMOVE_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const elm, struct window * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_right;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_windows_RB_REMOVE_COLOR_1_1_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_windows_RB_REMOVE_COLOR_1_1_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


void windows_RB_REMOVE_COLOR(struct windows *head, struct window *parent, struct window *elm)
{
  unsigned int elm_idx = 0;
  unsigned int parent_idx = 0;
  struct window *tmp;
  unsigned int tmp_idx = 0;
  while ((((&elm[elm_idx]) == 0) || (elm->entry.rbe_color == 0)) && ((&elm[elm_idx]) != head->rbh_root))
  {
    helper_windows_RB_REMOVE_COLOR_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }

  if (elm)
  {
    elm->entry.rbe_color = 0;
  }
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
void helper_windows_RB_REMOVE_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const parent, struct window * const elm, struct window * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if (parent->entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_windows_RB_REMOVE_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  else
  {
    helper_helper_windows_RB_REMOVE_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'child_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'color_ref is a mutable refrence to int']
void helper_windows_RB_REMOVE_1(unsigned int * const elm_idx_ref, unsigned int * const child_idx_ref, unsigned int * const parent_idx_ref, int * const color_ref, struct windows * const head, struct window * const elm, struct window * const child, struct window * const parent, struct window * const old)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int child_idx = *child_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  int color = *color_ref;
  struct window *left;
  unsigned int left_idx = 0;
  elm_idx = elm_idx->entry.rbe_right;
  while (left_idx = elm->entry.rbe_left)
  {
    elm_idx = &left[left_idx];
  }

  child_idx = elm->entry.rbe_right;
  parent_idx = elm->entry.rbe_parent;
  color = elm->entry.rbe_color;
  if (child)
  {
    child->entry.rbe_parent = &parent[parent_idx];
  }
  if (parent)
  {
    if (parent->entry.rbe_left == (&elm[elm_idx]))
    {
      parent->entry.rbe_left = &child[child_idx];
    }
    else
      parent->entry.rbe_right = &child[child_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &child[child_idx];
  if (elm->entry.rbe_parent == old)
  {
    parent_idx = &elm[elm_idx];
  }
  elm->entry = old->entry;
  if (old->entry.rbe_parent)
  {
    if (old->entry.rbe_parent->entry.rbe_left == old)
    {
      old->entry.rbe_parent->entry.rbe_left = &elm[elm_idx];
    }
    else
      old->entry.rbe_parent->entry.rbe_right = &elm[elm_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &elm[elm_idx];
  old->entry.rbe_left->entry.rbe_parent = &elm[elm_idx];
  if (old->entry.rbe_right)
  {
    old->entry.rbe_right->entry.rbe_parent = &elm[elm_idx];
  }
  if (parent)
  {
    left_idx = &parent[parent_idx];
    do
    {
      do
      {
      }
      while (0);
    }
    while (left_idx = left_idx->entry.rbe_parent);
  }
  goto color;
  *elm_idx_ref = elm_idx;
  *child_idx_ref = child_idx;
  *parent_idx_ref = parent_idx;
  *color_ref = color;
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
None
----------------------------
***/


struct window *windows_RB_REMOVE(struct windows *head, struct window *elm)
{
  unsigned int elm_idx = 0;
  struct window *child;
  unsigned int child_idx = 0;
  struct window *parent;
  unsigned int parent_idx = 0;
  struct window *old = elm;
  int color;
  if (elm->entry.rbe_left == 0)
  {
    child_idx = elm->entry.rbe_right;
  }
  else
    if (elm->entry.rbe_right == 0)
  {
    child_idx = elm->entry.rbe_left;
  }
  else
  {
    helper_windows_RB_REMOVE_1(&elm_idx, &child_idx, &parent_idx, &color, head, elm, child, parent, old);
  }
  parent_idx = elm->entry.rbe_parent;
  color = elm->entry.rbe_color;
  if (child)
  {
    child->entry.rbe_parent = &parent[parent_idx];
  }
  if (parent)
  {
    if (parent->entry.rbe_left == (&elm[elm_idx]))
    {
      parent->entry.rbe_left = &child[child_idx];
    }
    else
      parent->entry.rbe_right = &child[child_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &child[child_idx];
  color:
  if (color == 0)
  {
    windows_RB_REMOVE_COLOR(head, parent, child);
  }

  return old;
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
void windows_RB_REMOVE_COLOR(struct windows *head, struct window *parent, struct window *elm)
{
  unsigned int elm_idx = 0;
  unsigned int parent_idx = 0;
  struct window *tmp;
  unsigned int tmp_idx = 0;
  while ((((&elm[elm_idx]) == 0) || (elm->entry.rbe_color == 0)) && ((&elm[elm_idx]) != head->rbh_root))
  {
    helper_windows_RB_REMOVE_COLOR_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }

  if (elm)
  {
    elm->entry.rbe_color = 0;
  }
}


----------------------------
void helper_windows_RB_REMOVE_1(unsigned int * const elm_idx_ref, unsigned int * const child_idx_ref, unsigned int * const parent_idx_ref, int * const color_ref, struct windows * const head, struct window * const elm, struct window * const child, struct window * const parent, struct window * const old)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int child_idx = *child_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  int color = *color_ref;
  struct window *left;
  unsigned int left_idx = 0;
  elm_idx = elm_idx->entry.rbe_right;
  while (left_idx = elm->entry.rbe_left)
  {
    elm_idx = &left[left_idx];
  }

  child_idx = elm->entry.rbe_right;
  parent_idx = elm->entry.rbe_parent;
  color = elm->entry.rbe_color;
  if (child)
  {
    child->entry.rbe_parent = &parent[parent_idx];
  }
  if (parent)
  {
    if (parent->entry.rbe_left == (&elm[elm_idx]))
    {
      parent->entry.rbe_left = &child[child_idx];
    }
    else
      parent->entry.rbe_right = &child[child_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &child[child_idx];
  if (elm->entry.rbe_parent == old)
  {
    parent_idx = &elm[elm_idx];
  }
  elm->entry = old->entry;
  if (old->entry.rbe_parent)
  {
    if (old->entry.rbe_parent->entry.rbe_left == old)
    {
      old->entry.rbe_parent->entry.rbe_left = &elm[elm_idx];
    }
    else
      old->entry.rbe_parent->entry.rbe_right = &elm[elm_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &elm[elm_idx];
  old->entry.rbe_left->entry.rbe_parent = &elm[elm_idx];
  if (old->entry.rbe_right)
  {
    old->entry.rbe_right->entry.rbe_parent = &elm[elm_idx];
  }
  if (parent)
  {
    left_idx = &parent[parent_idx];
    do
    {
      do
      {
      }
      while (0);
    }
    while (left_idx = left_idx->entry.rbe_parent);
  }
  goto color;
  *elm_idx_ref = elm_idx;
  *child_idx_ref = child_idx;
  *parent_idx_ref = parent_idx;
  *color_ref = color;
}


----------------------------
None
----------------------------
***/


int window_pane_get_palette(const struct window_pane *wp, int c)
{
  int new;
  if ((wp == 0) || (wp->palette == 0))
  {
    return -1;
  }
  new = -1;
  if (c < 8)
  {
    new = wp->palette[c];
  }
  else
    if ((c >= 90) && (c <= 97))
  {
    new = wp->palette[(8 + c) - 90];
  }
  else
    if (c & 0x01000000)
  {
    new = wp->palette[c & (~0x01000000)];
  }
  if (new == 0)
  {
    return -1;
  }
  return new;
}


/*** DEPENDENCIES:
None
----------------------------
***/


void window_pane_reset_palette(struct window_pane *wp)
{
  if (wp->palette == 0)
  {
    return;
  }
  free(wp->palette);
  wp->palette = 0;
  wp->flags |= 0x1;
}


/*** DEPENDENCIES:
None
----------------------------
***/


void window_pane_unset_palette(struct window_pane *wp, u_int n)
{
  if ((n > 0xff) || (wp->palette == 0))
  {
    return;
  }
  wp->palette[n] = 0;
  wp->flags |= 0x1;
}


/*** DEPENDENCIES:
None
----------------------------
***/


void window_pane_set_palette(struct window_pane *wp, u_int n, int colour)
{
  if (n > 0xff)
  {
    return;
  }
  if (wp->palette == 0)
  {
    wp->palette = xcalloc(0x100, sizeof(*wp->palette));
  }
  wp->palette[n] = colour;
  wp->flags |= 0x1;
}


/*** DEPENDENCIES:
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


void window_set_name(struct window *w, const char *new_name)
{
  free(w->name);
  utf8_stravis(&w->name, new_name, ((0x01 | 0x02) | 0x08) | 0x10);
  notify_window("window-renamed", w);
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
None
----------------------------
***/


int window_cmp(struct window *w1, struct window *w2)
{
  return w1->id - w2->id;
}


/*** DEPENDENCIES:
None
----------------------------
***/


struct window *windows_RB_NEXT(struct window *elm)
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


/*** DEPENDENCIES:
None
----------------------------
***/


struct window *windows_RB_PREV(struct window *elm)
{
  unsigned int elm_idx = 0;
  if (elm->entry.rbe_left)
  {
    elm_idx = elm_idx->entry.rbe_left;
    while (elm->entry.rbe_right)
    {
      elm_idx = elm_idx->entry.rbe_right;
    }

  }
  else
  {
    if (elm->entry.rbe_parent && ((&elm[elm_idx]) == elm->entry.rbe_parent->entry.rbe_right))
    {
      elm_idx = elm_idx->entry.rbe_parent;
    }
    else
    {
      while (elm->entry.rbe_parent && ((&elm[elm_idx]) == elm->entry.rbe_parent->entry.rbe_left))
      {
        elm_idx = elm_idx->entry.rbe_parent;
      }

      elm_idx = elm_idx->entry.rbe_parent;
    }
  }
  return elm;
}


/*** DEPENDENCIES:
None
----------------------------
***/


int winlink_cmp(struct winlink *wl1, struct winlink *wl2)
{
  return wl1->idx - wl2->idx;
}


/*** DEPENDENCIES:
None
----------------------------
***/


struct winlink *winlinks_RB_PREV(struct winlink *elm)
{
  unsigned int elm_idx = 0;
  if (elm->entry.rbe_left)
  {
    elm_idx = elm_idx->entry.rbe_left;
    while (elm->entry.rbe_right)
    {
      elm_idx = elm_idx->entry.rbe_right;
    }

  }
  else
  {
    if (elm->entry.rbe_parent && ((&elm[elm_idx]) == elm->entry.rbe_parent->entry.rbe_right))
    {
      elm_idx = elm_idx->entry.rbe_parent;
    }
    else
    {
      while (elm->entry.rbe_parent && ((&elm[elm_idx]) == elm->entry.rbe_parent->entry.rbe_left))
      {
        elm_idx = elm_idx->entry.rbe_parent;
      }

      elm_idx = elm_idx->entry.rbe_parent;
    }
  }
  return elm;
}


/*** DEPENDENCIES:
None
----------------------------
***/


void window_resize(struct window *w, u_int sx, u_int sy)
{
  w->sx = sx;
  w->sy = sy;
}


/*** DEPENDENCIES:
None
----------------------------
***/


struct winlink *winlink_next(struct winlink *wl)
{
  return winlinks_RB_NEXT(wl);
}


/*** DEPENDENCIES:
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
***/


struct winlink *winlink_previous(struct winlink *wl)
{
  return winlinks_RB_PREV(wl);
}


/*** DEPENDENCIES:
struct winlink *winlinks_RB_PREV(struct winlink *elm)
{
  unsigned int elm_idx = 0;
  if (elm->entry.rbe_left)
  {
    elm_idx = elm_idx->entry.rbe_left;
    while (elm->entry.rbe_right)
    {
      elm_idx = elm_idx->entry.rbe_right;
    }

  }
  else
  {
    if (elm->entry.rbe_parent && ((&elm[elm_idx]) == elm->entry.rbe_parent->entry.rbe_right))
    {
      elm_idx = elm_idx->entry.rbe_parent;
    }
    else
    {
      while (elm->entry.rbe_parent && ((&elm[elm_idx]) == elm->entry.rbe_parent->entry.rbe_left))
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
***/


struct window *windows_RB_MINMAX(struct windows *head, int val)
{
  struct window *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct window *parent = 0;
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


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
None
----------------------------
***/


int window_pane_cmp(struct window_pane *wp1, struct window_pane *wp2)
{
  return wp1->id - wp2->id;
}


/*** DEPENDENCIES:
None
----------------------------
***/


struct window_pane *window_pane_tree_RB_NEXT(struct window_pane *elm)
{
  unsigned int elm_idx = 0;
  if (elm->tree_entry.rbe_right)
  {
    elm_idx = elm_idx->tree_entry.rbe_right;
    while (elm->tree_entry.rbe_left)
    {
      elm_idx = elm_idx->tree_entry.rbe_left;
    }

  }
  else
  {
    if (elm->tree_entry.rbe_parent && ((&elm[elm_idx]) == elm->tree_entry.rbe_parent->tree_entry.rbe_left))
    {
      elm_idx = elm_idx->tree_entry.rbe_parent;
    }
    else
    {
      while (elm->tree_entry.rbe_parent && ((&elm[elm_idx]) == elm->tree_entry.rbe_parent->tree_entry.rbe_right))
      {
        elm_idx = elm_idx->tree_entry.rbe_parent;
      }

      elm_idx = elm_idx->tree_entry.rbe_parent;
    }
  }
  return elm;
}


/*** DEPENDENCIES:
None
----------------------------
***/


struct window_pane *window_pane_tree_RB_PREV(struct window_pane *elm)
{
  unsigned int elm_idx = 0;
  if (elm->tree_entry.rbe_left)
  {
    elm_idx = elm_idx->tree_entry.rbe_left;
    while (elm->tree_entry.rbe_right)
    {
      elm_idx = elm_idx->tree_entry.rbe_right;
    }

  }
  else
  {
    if (elm->tree_entry.rbe_parent && ((&elm[elm_idx]) == elm->tree_entry.rbe_parent->tree_entry.rbe_right))
    {
      elm_idx = elm_idx->tree_entry.rbe_parent;
    }
    else
    {
      while (elm->tree_entry.rbe_parent && ((&elm[elm_idx]) == elm->tree_entry.rbe_parent->tree_entry.rbe_left))
      {
        elm_idx = elm_idx->tree_entry.rbe_parent;
      }

      elm_idx = elm_idx->tree_entry.rbe_parent;
    }
  }
  return elm;
}


/*** DEPENDENCIES:
None
----------------------------
***/


void winlink_stack_remove(struct winlink_stack *stack, struct winlink *wl)
{
  struct winlink *wl2;
  unsigned int wl2_idx = 0;
  if (wl == 0)
  {
    return;
  }
  for (wl2_idx = stack->tqh_first; (&wl2[wl2_idx]) != 0; wl2_idx = wl2_idx->sentry.tqe_next)
  {
    if ((&wl2[wl2_idx]) == wl)
    {
      do
      {
        if (wl->sentry.tqe_next != 0)
        {
          wl->sentry.tqe_next->sentry.tqe_prev = wl->sentry.tqe_prev;
        }
        else
          stack->tqh_last = wl->sentry.tqe_prev;
        *wl->sentry.tqe_prev = wl->sentry.tqe_next;
        ;
        ;
      }
      while (0);
      return;
    }
  }

}


/*** DEPENDENCIES:
None
----------------------------
***/


void window_update_activity(struct window *w)
{
  gettimeofday(&w->activity_time, 0);
  alerts_queue(w, 0x2);
}


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
***/


struct window_pane *window_pane_next_by_number(struct window *w, struct window_pane *wp, u_int n)
{
  unsigned int wp_idx = 0;
  for (; n > 0; n -= 1)
  {
    if ((wp_idx = wp_idx->entry.tqe_next) == 0)
    {
      wp_idx = (&w->panes)->tqh_first;
    }
  }

  return wp;
}


/*** DEPENDENCIES:
None
----------------------------
***/


struct window_pane *window_pane_previous_by_number(struct window *w, struct window_pane *wp, u_int n)
{
  unsigned int wp_idx = 0;
  for (; n > 0; n -= 1)
  {
    if ((wp_idx = *((struct window_panes *) wp_idx->entry.tqe_prev)->tqh_last) == 0)
    {
      wp_idx = *((struct window_panes *) (&w->panes)->tqh_last)->tqh_last;
    }
  }

  return wp;
}


/*** DEPENDENCIES:
None
----------------------------
***/


int window_pane_destroy_ready(struct window_pane *wp)
{
  int n;
  if (wp->pipe_fd != (-1))
  {
    if (EVBUFFER_LENGTH(wp->pipe_event->output) != 0)
    {
      return 0;
    }
    if ((ioctl(wp->fd, FIONREAD, &n) != (-1)) && (n > 0))
    {
      return 0;
    }
  }
  if ((~wp->flags) & 0x100)
  {
    return 0;
  }
  return 1;
}


/*** DEPENDENCIES:
None
----------------------------
***/


void winlink_clear_flags(struct winlink *wl)
{
  struct winlink *loop;
  unsigned int loop_idx = 0;
  wl->window->flags &= ~((0x1 | 0x2) | 0x8);
  for (loop_idx = (&wl->window->winlinks)->tqh_first; (&loop[loop_idx]) != 0; loop_idx = loop_idx->wentry.tqe_next)
  {
    if ((loop->flags & ((0x1 | 0x2) | 0x4)) != 0)
    {
      loop->flags &= ~((0x1 | 0x2) | 0x4);
      server_status_session(loop->session);
    }
  }

}


/*** DEPENDENCIES:
void server_status_session(struct session *s)
{
  struct client *c;
  unsigned int c_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (c->session == s)
    {
      server_status_client(c);
    }
  }

}


----------------------------
None
----------------------------
***/


static struct window_pane *window_pane_choose_best(struct window_pane **list, u_int size)
{
  struct window_pane *next;
  unsigned int next_idx = 0;
  struct window_pane *best;
  unsigned int best_idx = 0;
  u_int i;
  if (size == 0)
  {
    return 0;
  }
  best_idx = list[0];
  for (i = 1; i < size; i += 1)
  {
    next_idx = list[i];
    if (next->active_point > best->active_point)
    {
      best_idx = &next[next_idx];
    }
  }

  return best;
}


/*** DEPENDENCIES:
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'child_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'color_ref is a mutable refrence to int']
void helper_winlinks_RB_REMOVE_1(unsigned int * const elm_idx_ref, unsigned int * const child_idx_ref, unsigned int * const parent_idx_ref, int * const color_ref, struct winlinks * const head, struct winlink * const elm, struct winlink * const child, struct winlink * const parent, struct winlink * const old)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int child_idx = *child_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  int color = *color_ref;
  struct winlink *left;
  unsigned int left_idx = 0;
  elm_idx = elm_idx->entry.rbe_right;
  while (left_idx = elm->entry.rbe_left)
  {
    elm_idx = &left[left_idx];
  }

  child_idx = elm->entry.rbe_right;
  parent_idx = elm->entry.rbe_parent;
  color = elm->entry.rbe_color;
  if (child)
  {
    child->entry.rbe_parent = &parent[parent_idx];
  }
  if (parent)
  {
    if (parent->entry.rbe_left == (&elm[elm_idx]))
    {
      parent->entry.rbe_left = &child[child_idx];
    }
    else
      parent->entry.rbe_right = &child[child_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &child[child_idx];
  if (elm->entry.rbe_parent == old)
  {
    parent_idx = &elm[elm_idx];
  }
  elm->entry = old->entry;
  if (old->entry.rbe_parent)
  {
    if (old->entry.rbe_parent->entry.rbe_left == old)
    {
      old->entry.rbe_parent->entry.rbe_left = &elm[elm_idx];
    }
    else
      old->entry.rbe_parent->entry.rbe_right = &elm[elm_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &elm[elm_idx];
  old->entry.rbe_left->entry.rbe_parent = &elm[elm_idx];
  if (old->entry.rbe_right)
  {
    old->entry.rbe_right->entry.rbe_parent = &elm[elm_idx];
  }
  if (parent)
  {
    left_idx = &parent[parent_idx];
    do
    {
      do
      {
      }
      while (0);
    }
    while (left_idx = left_idx->entry.rbe_parent);
  }
  goto color;
  *elm_idx_ref = elm_idx;
  *child_idx_ref = child_idx;
  *parent_idx_ref = parent_idx;
  *color_ref = color;
}


/*** DEPENDENCIES:
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_windows_RB_INSERT_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const gparent, struct window * const tmp, unsigned int gparent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->entry.rbe_left;
  if (gparent->entry.rbe_left = tmp->entry.rbe_right)
  {
    tmp->entry.rbe_right->entry.rbe_parent = &gparent[gparent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent = gparent->entry.rbe_parent)
  {
    if ((&gparent[gparent_idx]) == gparent->entry.rbe_parent->entry.rbe_left)
    {
      gparent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
    }
    else
      gparent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->entry.rbe_right = &gparent[gparent_idx];
  gparent->entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_windows_RB_INSERT_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const elm, struct window * const parent, struct window * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp_idx = parent->entry.rbe_right;
    if (parent->entry.rbe_right = tmp->entry.rbe_left)
    {
      tmp->entry.rbe_left->entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
      {
        parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->entry.rbe_left = &parent[parent_idx];
    parent->entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = &parent[parent_idx];
  parent_idx = &elm[elm_idx];
  elm_idx = &tmp[tmp_idx];
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_windows_RB_INSERT_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const gparent, struct window * const tmp, unsigned int gparent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->entry.rbe_right;
  if (gparent->entry.rbe_right = tmp->entry.rbe_left)
  {
    tmp->entry.rbe_left->entry.rbe_parent = &gparent[gparent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent = gparent->entry.rbe_parent)
  {
    if ((&gparent[gparent_idx]) == gparent->entry.rbe_parent->entry.rbe_left)
    {
      gparent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
    }
    else
      gparent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->entry.rbe_left = &gparent[gparent_idx];
  gparent->entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_windows_RB_INSERT_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const elm, struct window * const parent, struct window * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp_idx = parent->entry.rbe_left;
    if (parent->entry.rbe_left = tmp->entry.rbe_right)
    {
      tmp->entry.rbe_right->entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
      {
        parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->entry.rbe_right = &parent[parent_idx];
    parent->entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = &parent[parent_idx];
  parent_idx = &elm[elm_idx];
  elm_idx = &tmp[tmp_idx];
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_winlinks_RB_INSERT_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const gparent, struct winlink * const tmp, unsigned int gparent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->entry.rbe_left;
  if (gparent->entry.rbe_left = tmp->entry.rbe_right)
  {
    tmp->entry.rbe_right->entry.rbe_parent = &gparent[gparent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent = gparent->entry.rbe_parent)
  {
    if ((&gparent[gparent_idx]) == gparent->entry.rbe_parent->entry.rbe_left)
    {
      gparent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
    }
    else
      gparent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->entry.rbe_right = &gparent[gparent_idx];
  gparent->entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_winlinks_RB_INSERT_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const elm, struct winlink * const parent, struct winlink * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp_idx = parent->entry.rbe_right;
    if (parent->entry.rbe_right = tmp->entry.rbe_left)
    {
      tmp->entry.rbe_left->entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
      {
        parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->entry.rbe_left = &parent[parent_idx];
    parent->entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = &parent[parent_idx];
  parent_idx = &elm[elm_idx];
  elm_idx = &tmp[tmp_idx];
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_winlinks_RB_INSERT_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const gparent, struct winlink * const tmp, unsigned int gparent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->entry.rbe_right;
  if (gparent->entry.rbe_right = tmp->entry.rbe_left)
  {
    tmp->entry.rbe_left->entry.rbe_parent = &gparent[gparent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent = gparent->entry.rbe_parent)
  {
    if ((&gparent[gparent_idx]) == gparent->entry.rbe_parent->entry.rbe_left)
    {
      gparent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
    }
    else
      gparent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->entry.rbe_left = &gparent[gparent_idx];
  gparent->entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_winlinks_RB_INSERT_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const elm, struct winlink * const parent, struct winlink * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp_idx = parent->entry.rbe_left;
    if (parent->entry.rbe_left = tmp->entry.rbe_right)
    {
      tmp->entry.rbe_right->entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
      {
        parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->entry.rbe_right = &parent[parent_idx];
    parent->entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = &parent[parent_idx];
  parent_idx = &elm[elm_idx];
  elm_idx = &tmp[tmp_idx];
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp->entry.rbe_color = 0;
    parent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    tmp_idx = parent->entry.rbe_right;
    if (parent->entry.rbe_right = tmp->entry.rbe_left)
    {
      tmp->entry.rbe_left->entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
      {
        parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->entry.rbe_left = &parent[parent_idx];
    parent->entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->entry.rbe_right;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp->entry.rbe_color = 0;
    parent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    tmp_idx = parent->entry.rbe_left;
    if (parent->entry.rbe_left = tmp->entry.rbe_right)
    {
      tmp->entry.rbe_right->entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
      {
        parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->entry.rbe_right = &parent[parent_idx];
    parent->entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->entry.rbe_left;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_1_2_1(unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_right;
  if (parent->entry.rbe_right = tmp->entry.rbe_left)
  {
    tmp->entry.rbe_left->entry.rbe_parent = &parent[parent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
  {
    if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
    {
      parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
    }
    else
      parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->entry.rbe_left = &parent[parent_idx];
  parent->entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_1_2_2(unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct winlink *oleft;
  unsigned int oleft_idx = 0;
  if (oleft_idx = tmp->entry.rbe_left)
  {
    oleft->entry.rbe_color = 0;
  }
  tmp->entry.rbe_color = 1;
  do
  {
    oleft_idx = tmp->entry.rbe_left;
    if (tmp->entry.rbe_left = oleft->entry.rbe_right)
    {
      oleft->entry.rbe_right->entry.rbe_parent = &tmp[tmp_idx];
    }
    do
    {
    }
    while (0);
    if (oleft->entry.rbe_parent = tmp->entry.rbe_parent)
    {
      if ((&tmp[tmp_idx]) == tmp->entry.rbe_parent->entry.rbe_left)
      {
        tmp->entry.rbe_parent->entry.rbe_left = &oleft[oleft_idx];
      }
      else
        tmp->entry.rbe_parent->entry.rbe_right = &oleft[oleft_idx];
    }
    else
      head->rbh_root = &oleft[oleft_idx];
    oleft->entry.rbe_right = &tmp[tmp_idx];
    tmp->entry.rbe_parent = &oleft[oleft_idx];
    do
    {
    }
    while (0);
    if (oleft->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->entry.rbe_right;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_2_2_1(unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_left;
  if (parent->entry.rbe_left = tmp->entry.rbe_right)
  {
    tmp->entry.rbe_right->entry.rbe_parent = &parent[parent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
  {
    if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
    {
      parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
    }
    else
      parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->entry.rbe_right = &parent[parent_idx];
  parent->entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_2_2_2(unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct winlink *oright;
  unsigned int oright_idx = 0;
  if (oright_idx = tmp->entry.rbe_right)
  {
    oright->entry.rbe_color = 0;
  }
  tmp->entry.rbe_color = 1;
  do
  {
    oright_idx = tmp->entry.rbe_right;
    if (tmp->entry.rbe_right = oright->entry.rbe_left)
    {
      oright->entry.rbe_left->entry.rbe_parent = &tmp[tmp_idx];
    }
    do
    {
    }
    while (0);
    if (oright->entry.rbe_parent = tmp->entry.rbe_parent)
    {
      if ((&tmp[tmp_idx]) == tmp->entry.rbe_parent->entry.rbe_left)
      {
        tmp->entry.rbe_parent->entry.rbe_left = &oright[oright_idx];
      }
      else
        tmp->entry.rbe_parent->entry.rbe_right = &oright[oright_idx];
    }
    else
      head->rbh_root = &oright[oright_idx];
    oright->entry.rbe_left = &tmp[tmp_idx];
    tmp->entry.rbe_parent = &oright[oright_idx];
    do
    {
    }
    while (0);
    if (oright->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->entry.rbe_left;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
None
----------------------------
***/


struct window_pane *window_pane_tree_RB_MINMAX(struct window_pane_tree *head, int val)
{
  struct window_pane *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct window_pane *parent = 0;
  unsigned int parent_idx = 0;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    if (val < 0)
    {
      tmp_idx = tmp_idx->tree_entry.rbe_left;
    }
    else
      tmp_idx = tmp_idx->tree_entry.rbe_right;
  }

  return parent;
}


/*** DEPENDENCIES:
struct window_pane_tree
{
  struct window_pane *rbh_root;
}
----------------------------
None
----------------------------
***/


struct window_pane *window_pane_at_index(struct window *w, u_int idx)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int n;
  n = options_get_number(w->options, "pane-base-index");
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    if (n == idx)
    {
      return wp;
    }
    n += 1;
  }

  return 0;
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


// hint:  ['list_idx_ref is a mutable refrence to unsigned int', 'end_ref is a mutable refrence to u_int', 'size_ref is a mutable refrence to u_int', 'found_ref is a mutable refrence to int']
void helper_window_pane_find_down_1(unsigned int * const list_idx_ref, u_int * const end_ref, u_int * const size_ref, int * const found_ref, struct window_pane * const wp, struct window_pane * const next, unsigned int next_idx, struct window_pane ** const list, u_int edge, u_int left, u_int right)
{
  unsigned int list_idx = *list_idx_ref;
  u_int end = *end_ref;
  u_int size = *size_ref;
  int found = *found_ref;
  if (((&next[next_idx]) == wp) || (!window_pane_visible(next)))
  {
    continue;
  }
  if (next->yoff != edge)
  {
    continue;
  }
  end = (next->xoff + next->sx) - 1;
  found = 0;
  if ((next->xoff < left) && (end > right))
  {
    found = 1;
  }
  else
    if ((next->xoff >= left) && (next->xoff <= right))
  {
    found = 1;
  }
  else
    if ((end >= left) && (end <= right))
  {
    found = 1;
  }
  if (!found)
  {
    continue;
  }
  list_idx = xreallocarray(list_idx, size + 1, sizeof(*list_idx));
  list[size + list_idx] = &next[next_idx];
  size += 1;
  *list_idx_ref = list_idx;
  *end_ref = end;
  *size_ref = size;
  *found_ref = found;
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


struct window_pane *window_pane_find_down(struct window_pane *wp)
{
  struct window_pane *next;
  unsigned int next_idx = 0;
  struct window_pane *best;
  unsigned int best_idx = 0;
  struct window_pane **list;
  unsigned int list_idx = 0;
  u_int edge;
  u_int left;
  u_int right;
  u_int end;
  u_int size;
  int status;
  int found;
  if ((wp == 0) || (!window_pane_visible(wp)))
  {
    return 0;
  }
  status = options_get_number(wp->window->options, "pane-border-status");
  list_idx = 0;
  size = 0;
  edge = (wp->yoff + wp->sy) + 1;
  if (edge >= (wp->window->sy - ((status == 2) ? (1) : (0))))
  {
    edge = (status == 1) ? (1) : (0);
  }
  left = wp->xoff;
  right = wp->xoff + wp->sx;
  for (next_idx = (&wp->window->panes)->tqh_first; (&next[next_idx]) != 0; next_idx = next_idx->entry.tqe_next)
  {
    helper_window_pane_find_down_1(&list_idx, &end, &size, &found, wp, next, next_idx, list, edge, left, right);
  }

  best_idx = window_pane_choose_best(list, size);
  free(list);
  return best;
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
static struct window_pane *window_pane_choose_best(struct window_pane **list, u_int size)
{
  struct window_pane *next;
  unsigned int next_idx = 0;
  struct window_pane *best;
  unsigned int best_idx = 0;
  u_int i;
  if (size == 0)
  {
    return 0;
  }
  best_idx = list[0];
  for (i = 1; i < size; i += 1)
  {
    next_idx = list[i];
    if (next->active_point > best->active_point)
    {
      best_idx = &next[next_idx];
    }
  }

  return best;
}


----------------------------
void helper_window_pane_find_down_1(unsigned int * const list_idx_ref, u_int * const end_ref, u_int * const size_ref, int * const found_ref, struct window_pane * const wp, struct window_pane * const next, unsigned int next_idx, struct window_pane ** const list, u_int edge, u_int left, u_int right)
{
  unsigned int list_idx = *list_idx_ref;
  u_int end = *end_ref;
  u_int size = *size_ref;
  int found = *found_ref;
  if (((&next[next_idx]) == wp) || (!window_pane_visible(next)))
  {
    continue;
  }
  if (next->yoff != edge)
  {
    continue;
  }
  end = (next->xoff + next->sx) - 1;
  found = 0;
  if ((next->xoff < left) && (end > right))
  {
    found = 1;
  }
  else
    if ((next->xoff >= left) && (next->xoff <= right))
  {
    found = 1;
  }
  else
    if ((end >= left) && (end <= right))
  {
    found = 1;
  }
  if (!found)
  {
    continue;
  }
  list_idx = xreallocarray(list_idx, size + 1, sizeof(*list_idx));
  list[size + list_idx] = &next[next_idx];
  size += 1;
  *list_idx_ref = list_idx;
  *end_ref = end;
  *size_ref = size;
  *found_ref = found;
}


----------------------------
None
----------------------------
***/


struct window_pane *window_pane_tree_RB_FIND(struct window_pane_tree *head, struct window_pane *elm)
{
  struct window_pane *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  int comp;
  while (tmp)
  {
    comp = window_pane_cmp(elm, tmp);
    if (comp < 0)
    {
      tmp_idx = tmp_idx->tree_entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->tree_entry.rbe_right;
    }
    else
      return tmp;
  }

  return 0;
}


/*** DEPENDENCIES:
struct window_pane_tree
{
  struct window_pane *rbh_root;
}
----------------------------
int window_pane_cmp(struct window_pane *wp1, struct window_pane *wp2)
{
  return wp1->id - wp2->id;
}


----------------------------
None
----------------------------
***/


struct window_pane *window_pane_find_by_id(u_int id)
{
  struct window_pane wp;
  wp.id = id;
  return window_pane_tree_RB_FIND(&all_window_panes, &wp);
}


/*** DEPENDENCIES:
struct window_pane *window_pane_tree_RB_FIND(struct window_pane_tree *head, struct window_pane *elm)
{
  struct window_pane *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  int comp;
  while (tmp)
  {
    comp = window_pane_cmp(elm, tmp);
    if (comp < 0)
    {
      tmp_idx = tmp_idx->tree_entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->tree_entry.rbe_right;
    }
    else
      return tmp;
  }

  return 0;
}


----------------------------
extern struct window_pane_tree all_window_panes
----------------------------
None
----------------------------
***/


struct window_pane *window_pane_find_by_id_str(const char *s)
{
  const char *errstr;
  u_int id;
  if ((*s) != '%')
  {
    return 0;
  }
  id = strtonum(s + 1, 0, 4294967295U, &errstr);
  if (errstr != 0)
  {
    return 0;
  }
  return window_pane_find_by_id(id);
}


/*** DEPENDENCIES:
struct window_pane *window_pane_find_by_id(u_int id)
{
  struct window_pane wp;
  wp.id = id;
  return window_pane_tree_RB_FIND(&all_window_panes, &wp);
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
None
----------------------------
***/


// hint:  ['list_idx_ref is a mutable refrence to unsigned int', 'end_ref is a mutable refrence to u_int', 'size_ref is a mutable refrence to u_int', 'found_ref is a mutable refrence to int']
void helper_window_pane_find_up_1(unsigned int * const list_idx_ref, u_int * const end_ref, u_int * const size_ref, int * const found_ref, struct window_pane * const wp, struct window_pane * const next, unsigned int next_idx, struct window_pane ** const list, u_int edge, u_int left, u_int right)
{
  unsigned int list_idx = *list_idx_ref;
  u_int end = *end_ref;
  u_int size = *size_ref;
  int found = *found_ref;
  if (((&next[next_idx]) == wp) || (!window_pane_visible(next)))
  {
    continue;
  }
  if (((next->yoff + next->sy) + 1) != edge)
  {
    continue;
  }
  end = (next->xoff + next->sx) - 1;
  found = 0;
  if ((next->xoff < left) && (end > right))
  {
    found = 1;
  }
  else
    if ((next->xoff >= left) && (next->xoff <= right))
  {
    found = 1;
  }
  else
    if ((end >= left) && (end <= right))
  {
    found = 1;
  }
  if (!found)
  {
    continue;
  }
  list_idx = xreallocarray(list_idx, size + 1, sizeof(*list_idx));
  list[size + list_idx] = &next[next_idx];
  size += 1;
  *list_idx_ref = list_idx;
  *end_ref = end;
  *size_ref = size;
  *found_ref = found;
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


struct window_pane *window_pane_find_up(struct window_pane *wp)
{
  struct window_pane *next;
  unsigned int next_idx = 0;
  struct window_pane *best;
  unsigned int best_idx = 0;
  struct window_pane **list;
  unsigned int list_idx = 0;
  u_int edge;
  u_int left;
  u_int right;
  u_int end;
  u_int size;
  int status;
  int found;
  if ((wp == 0) || (!window_pane_visible(wp)))
  {
    return 0;
  }
  status = options_get_number(wp->window->options, "pane-border-status");
  list_idx = 0;
  size = 0;
  edge = wp->yoff;
  if (edge == ((status == 1) ? (1) : (0)))
  {
    edge = (wp->window->sy + 1) - ((status == 2) ? (1) : (0));
  }
  left = wp->xoff;
  right = wp->xoff + wp->sx;
  for (next_idx = (&wp->window->panes)->tqh_first; (&next[next_idx]) != 0; next_idx = next_idx->entry.tqe_next)
  {
    helper_window_pane_find_up_1(&list_idx, &end, &size, &found, wp, next, next_idx, list, edge, left, right);
  }

  best_idx = window_pane_choose_best(list, size);
  free(list);
  return best;
}


/*** DEPENDENCIES:
void helper_window_pane_find_up_1(unsigned int * const list_idx_ref, u_int * const end_ref, u_int * const size_ref, int * const found_ref, struct window_pane * const wp, struct window_pane * const next, unsigned int next_idx, struct window_pane ** const list, u_int edge, u_int left, u_int right)
{
  unsigned int list_idx = *list_idx_ref;
  u_int end = *end_ref;
  u_int size = *size_ref;
  int found = *found_ref;
  if (((&next[next_idx]) == wp) || (!window_pane_visible(next)))
  {
    continue;
  }
  if (((next->yoff + next->sy) + 1) != edge)
  {
    continue;
  }
  end = (next->xoff + next->sx) - 1;
  found = 0;
  if ((next->xoff < left) && (end > right))
  {
    found = 1;
  }
  else
    if ((next->xoff >= left) && (next->xoff <= right))
  {
    found = 1;
  }
  else
    if ((end >= left) && (end <= right))
  {
    found = 1;
  }
  if (!found)
  {
    continue;
  }
  list_idx = xreallocarray(list_idx, size + 1, sizeof(*list_idx));
  list[size + list_idx] = &next[next_idx];
  size += 1;
  *list_idx_ref = list_idx;
  *end_ref = end;
  *size_ref = size;
  *found_ref = found;
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
static struct window_pane *window_pane_choose_best(struct window_pane **list, u_int size)
{
  struct window_pane *next;
  unsigned int next_idx = 0;
  struct window_pane *best;
  unsigned int best_idx = 0;
  u_int i;
  if (size == 0)
  {
    return 0;
  }
  best_idx = list[0];
  for (i = 1; i < size; i += 1)
  {
    next_idx = list[i];
    if (next->active_point > best->active_point)
    {
      best_idx = &next[next_idx];
    }
  }

  return best;
}


----------------------------
None
----------------------------
***/


// hint:  ['list_idx_ref is a mutable refrence to unsigned int', 'end_ref is a mutable refrence to u_int', 'size_ref is a mutable refrence to u_int', 'found_ref is a mutable refrence to int']
void helper_window_pane_find_right_1(unsigned int * const list_idx_ref, u_int * const end_ref, u_int * const size_ref, int * const found_ref, struct window_pane * const wp, struct window_pane * const next, unsigned int next_idx, struct window_pane ** const list, u_int edge, u_int top, u_int bottom)
{
  unsigned int list_idx = *list_idx_ref;
  u_int end = *end_ref;
  u_int size = *size_ref;
  int found = *found_ref;
  if (((&next[next_idx]) == wp) || (!window_pane_visible(next)))
  {
    continue;
  }
  if (next->xoff != edge)
  {
    continue;
  }
  end = (next->yoff + next->sy) - 1;
  found = 0;
  if ((next->yoff < top) && (end > bottom))
  {
    found = 1;
  }
  else
    if ((next->yoff >= top) && (next->yoff <= bottom))
  {
    found = 1;
  }
  else
    if ((end >= top) && (end <= bottom))
  {
    found = 1;
  }
  if (!found)
  {
    continue;
  }
  list_idx = xreallocarray(list_idx, size + 1, sizeof(*list_idx));
  list[size + list_idx] = &next[next_idx];
  size += 1;
  *list_idx_ref = list_idx;
  *end_ref = end;
  *size_ref = size;
  *found_ref = found;
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


struct window_pane *window_pane_find_right(struct window_pane *wp)
{
  struct window_pane *next;
  unsigned int next_idx = 0;
  struct window_pane *best;
  unsigned int best_idx = 0;
  struct window_pane **list;
  unsigned int list_idx = 0;
  u_int edge;
  u_int top;
  u_int bottom;
  u_int end;
  u_int size;
  int found;
  if ((wp == 0) || (!window_pane_visible(wp)))
  {
    return 0;
  }
  list_idx = 0;
  size = 0;
  edge = (wp->xoff + wp->sx) + 1;
  if (edge >= wp->window->sx)
  {
    edge = 0;
  }
  top = wp->yoff;
  bottom = wp->yoff + wp->sy;
  for (next_idx = (&wp->window->panes)->tqh_first; (&next[next_idx]) != 0; next_idx = next_idx->entry.tqe_next)
  {
    helper_window_pane_find_right_1(&list_idx, &end, &size, &found, wp, next, next_idx, list, edge, top, bottom);
  }

  best_idx = window_pane_choose_best(list, size);
  free(list);
  return best;
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
void helper_window_pane_find_right_1(unsigned int * const list_idx_ref, u_int * const end_ref, u_int * const size_ref, int * const found_ref, struct window_pane * const wp, struct window_pane * const next, unsigned int next_idx, struct window_pane ** const list, u_int edge, u_int top, u_int bottom)
{
  unsigned int list_idx = *list_idx_ref;
  u_int end = *end_ref;
  u_int size = *size_ref;
  int found = *found_ref;
  if (((&next[next_idx]) == wp) || (!window_pane_visible(next)))
  {
    continue;
  }
  if (next->xoff != edge)
  {
    continue;
  }
  end = (next->yoff + next->sy) - 1;
  found = 0;
  if ((next->yoff < top) && (end > bottom))
  {
    found = 1;
  }
  else
    if ((next->yoff >= top) && (next->yoff <= bottom))
  {
    found = 1;
  }
  else
    if ((end >= top) && (end <= bottom))
  {
    found = 1;
  }
  if (!found)
  {
    continue;
  }
  list_idx = xreallocarray(list_idx, size + 1, sizeof(*list_idx));
  list[size + list_idx] = &next[next_idx];
  size += 1;
  *list_idx_ref = list_idx;
  *end_ref = end;
  *size_ref = size;
  *found_ref = found;
}


----------------------------
static struct window_pane *window_pane_choose_best(struct window_pane **list, u_int size)
{
  struct window_pane *next;
  unsigned int next_idx = 0;
  struct window_pane *best;
  unsigned int best_idx = 0;
  u_int i;
  if (size == 0)
  {
    return 0;
  }
  best_idx = list[0];
  for (i = 1; i < size; i += 1)
  {
    next_idx = list[i];
    if (next->active_point > best->active_point)
    {
      best_idx = &next[next_idx];
    }
  }

  return best;
}


----------------------------
None
----------------------------
***/


// hint:  ['list_idx_ref is a mutable refrence to unsigned int', 'end_ref is a mutable refrence to u_int', 'size_ref is a mutable refrence to u_int', 'found_ref is a mutable refrence to int']
void helper_window_pane_find_left_1(unsigned int * const list_idx_ref, u_int * const end_ref, u_int * const size_ref, int * const found_ref, struct window_pane * const wp, struct window_pane * const next, unsigned int next_idx, struct window_pane ** const list, u_int edge, u_int top, u_int bottom)
{
  unsigned int list_idx = *list_idx_ref;
  u_int end = *end_ref;
  u_int size = *size_ref;
  int found = *found_ref;
  if (((&next[next_idx]) == wp) || (!window_pane_visible(next)))
  {
    continue;
  }
  if (((next->xoff + next->sx) + 1) != edge)
  {
    continue;
  }
  end = (next->yoff + next->sy) - 1;
  found = 0;
  if ((next->yoff < top) && (end > bottom))
  {
    found = 1;
  }
  else
    if ((next->yoff >= top) && (next->yoff <= bottom))
  {
    found = 1;
  }
  else
    if ((end >= top) && (end <= bottom))
  {
    found = 1;
  }
  if (!found)
  {
    continue;
  }
  list_idx = xreallocarray(list_idx, size + 1, sizeof(*list_idx));
  list[size + list_idx] = &next[next_idx];
  size += 1;
  *list_idx_ref = list_idx;
  *end_ref = end;
  *size_ref = size;
  *found_ref = found;
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


struct window_pane *window_pane_find_left(struct window_pane *wp)
{
  struct window_pane *next;
  unsigned int next_idx = 0;
  struct window_pane *best;
  unsigned int best_idx = 0;
  struct window_pane **list;
  unsigned int list_idx = 0;
  u_int edge;
  u_int top;
  u_int bottom;
  u_int end;
  u_int size;
  int found;
  if ((wp == 0) || (!window_pane_visible(wp)))
  {
    return 0;
  }
  list_idx = 0;
  size = 0;
  edge = wp->xoff;
  if (edge == 0)
  {
    edge = wp->window->sx + 1;
  }
  top = wp->yoff;
  bottom = wp->yoff + wp->sy;
  for (next_idx = (&wp->window->panes)->tqh_first; (&next[next_idx]) != 0; next_idx = next_idx->entry.tqe_next)
  {
    helper_window_pane_find_left_1(&list_idx, &end, &size, &found, wp, next, next_idx, list, edge, top, bottom);
  }

  best_idx = window_pane_choose_best(list, size);
  free(list);
  return best;
}


/*** DEPENDENCIES:
void helper_window_pane_find_left_1(unsigned int * const list_idx_ref, u_int * const end_ref, u_int * const size_ref, int * const found_ref, struct window_pane * const wp, struct window_pane * const next, unsigned int next_idx, struct window_pane ** const list, u_int edge, u_int top, u_int bottom)
{
  unsigned int list_idx = *list_idx_ref;
  u_int end = *end_ref;
  u_int size = *size_ref;
  int found = *found_ref;
  if (((&next[next_idx]) == wp) || (!window_pane_visible(next)))
  {
    continue;
  }
  if (((next->xoff + next->sx) + 1) != edge)
  {
    continue;
  }
  end = (next->yoff + next->sy) - 1;
  found = 0;
  if ((next->yoff < top) && (end > bottom))
  {
    found = 1;
  }
  else
    if ((next->yoff >= top) && (next->yoff <= bottom))
  {
    found = 1;
  }
  else
    if ((end >= top) && (end <= bottom))
  {
    found = 1;
  }
  if (!found)
  {
    continue;
  }
  list_idx = xreallocarray(list_idx, size + 1, sizeof(*list_idx));
  list[size + list_idx] = &next[next_idx];
  size += 1;
  *list_idx_ref = list_idx;
  *end_ref = end;
  *size_ref = size;
  *found_ref = found;
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
static struct window_pane *window_pane_choose_best(struct window_pane **list, u_int size)
{
  struct window_pane *next;
  unsigned int next_idx = 0;
  struct window_pane *best;
  unsigned int best_idx = 0;
  u_int i;
  if (size == 0)
  {
    return 0;
  }
  best_idx = list[0];
  for (i = 1; i < size; i += 1)
  {
    next_idx = list[i];
    if (next->active_point > best->active_point)
    {
      best_idx = &next[next_idx];
    }
  }

  return best;
}


----------------------------
None
----------------------------
***/


struct window_pane *window_get_active_at(struct window *w, u_int x, u_int y)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    if (!window_pane_visible(wp))
    {
      continue;
    }
    if ((x < wp->xoff) || (x > (wp->xoff + wp->sx)))
    {
      continue;
    }
    if ((y < wp->yoff) || (y > (wp->yoff + wp->sy)))
    {
      continue;
    }
    return wp;
  }

  return 0;
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
None
----------------------------
***/


struct window_pane *window_find_string(struct window *w, const char *s)
{
  u_int x;
  u_int y;
  x = w->sx / 2;
  y = w->sy / 2;
  if (strcasecmp(s, "top") == 0)
  {
    y = 0;
  }
  else
    if (strcasecmp(s, "bottom") == 0)
  {
    y = w->sy - 1;
  }
  else
    if (strcasecmp(s, "left") == 0)
  {
    x = 0;
  }
  else
    if (strcasecmp(s, "right") == 0)
  {
    x = w->sx - 1;
  }
  else
    if (strcasecmp(s, "top-left") == 0)
  {
    x = 0;
    y = 0;
  }
  else
    if (strcasecmp(s, "top-right") == 0)
  {
    x = w->sx - 1;
    y = 0;
  }
  else
    if (strcasecmp(s, "bottom-left") == 0)
  {
    x = 0;
    y = w->sy - 1;
  }
  else
    if (strcasecmp(s, "bottom-right") == 0)
  {
    x = w->sx - 1;
    y = w->sy - 1;
  }
  else
    return 0;
  return window_get_active_at(w, x, y);
}


/*** DEPENDENCIES:
struct window_pane *window_get_active_at(struct window *w, u_int x, u_int y)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    if (!window_pane_visible(wp))
    {
      continue;
    }
    if ((x < wp->xoff) || (x > (wp->xoff + wp->sx)))
    {
      continue;
    }
    if ((y < wp->yoff) || (y > (wp->yoff + wp->sy)))
    {
      continue;
    }
    return wp;
  }

  return 0;
}


----------------------------
None
----------------------------
***/


struct window *windows_RB_FIND(struct windows *head, struct window *elm)
{
  struct window *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  int comp;
  while (tmp)
  {
    comp = window_cmp(elm, tmp);
    if (comp < 0)
    {
      tmp_idx = tmp_idx->entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->entry.rbe_right;
    }
    else
      return tmp;
  }

  return 0;
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
int window_cmp(struct window *w1, struct window *w2)
{
  return w1->id - w2->id;
}


----------------------------
None
----------------------------
***/


struct window *window_find_by_id(u_int id)
{
  struct window w;
  w.id = id;
  return windows_RB_FIND(&windows, &w);
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
struct window *windows_RB_FIND(struct windows *head, struct window *elm)
{
  struct window *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  int comp;
  while (tmp)
  {
    comp = window_cmp(elm, tmp);
    if (comp < 0)
    {
      tmp_idx = tmp_idx->entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->entry.rbe_right;
    }
    else
      return tmp;
  }

  return 0;
}


----------------------------
None
----------------------------
***/


struct winlink *winlinks_RB_FIND(struct winlinks *head, struct winlink *elm)
{
  struct winlink *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  int comp;
  while (tmp)
  {
    comp = winlink_cmp(elm, tmp);
    if (comp < 0)
    {
      tmp_idx = tmp_idx->entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->entry.rbe_right;
    }
    else
      return tmp;
  }

  return 0;
}


/*** DEPENDENCIES:
int winlink_cmp(struct winlink *wl1, struct winlink *wl2)
{
  return wl1->idx - wl2->idx;
}


----------------------------
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
None
----------------------------
***/


struct winlink *winlink_find_by_index(struct winlinks *wwl, int idx)
{
  struct winlink wl;
  if (idx < 0)
  {
    fatalx("bad index");
  }
  wl.idx = idx;
  return winlinks_RB_FIND(wwl, &wl);
}


/*** DEPENDENCIES:
struct winlink *winlinks_RB_FIND(struct winlinks *head, struct winlink *elm)
{
  struct winlink *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  int comp;
  while (tmp)
  {
    comp = winlink_cmp(elm, tmp);
    if (comp < 0)
    {
      tmp_idx = tmp_idx->entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->entry.rbe_right;
    }
    else
      return tmp;
  }

  return 0;
}


----------------------------
struct winlinks
{
  struct winlink *rbh_root;
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
***/


struct winlink *winlink_next_by_number(struct winlink *wl, struct session *s, int n)
{
  unsigned int wl_idx = 0;
  for (; n > 0; n -= 1)
  {
    if ((wl_idx = winlinks_RB_NEXT(wl_idx)) == 0)
    {
      wl_idx = winlinks_RB_MINMAX(&s->windows, -1);
    }
  }

  return wl;
}


/*** DEPENDENCIES:
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


struct winlink *winlink_previous_by_number(struct winlink *wl, struct session *s, int n)
{
  unsigned int wl_idx = 0;
  for (; n > 0; n -= 1)
  {
    if ((wl_idx = winlinks_RB_PREV(wl_idx)) == 0)
    {
      wl_idx = winlinks_RB_MINMAX(&s->windows, 1);
    }
  }

  return wl;
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
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
struct winlink *winlinks_RB_PREV(struct winlink *elm)
{
  unsigned int elm_idx = 0;
  if (elm->entry.rbe_left)
  {
    elm_idx = elm_idx->entry.rbe_left;
    while (elm->entry.rbe_right)
    {
      elm_idx = elm_idx->entry.rbe_right;
    }

  }
  else
  {
    if (elm->entry.rbe_parent && ((&elm[elm_idx]) == elm->entry.rbe_parent->entry.rbe_right))
    {
      elm_idx = elm_idx->entry.rbe_parent;
    }
    else
    {
      while (elm->entry.rbe_parent && ((&elm[elm_idx]) == elm->entry.rbe_parent->entry.rbe_left))
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
***/


struct window *window_find_by_id_str(const char *s)
{
  const char *errstr;
  u_int id;
  if ((*s) != '@')
  {
    return 0;
  }
  id = strtonum(s + 1, 0, 4294967295U, &errstr);
  if (errstr != 0)
  {
    return 0;
  }
  return window_find_by_id(id);
}


/*** DEPENDENCIES:
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
struct window *window_find_by_id(u_int id)
{
  struct window w;
  w.id = id;
  return windows_RB_FIND(&windows, &w);
}


----------------------------
None
----------------------------
***/


int window_unzoom(struct window *w)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  if (!(w->flags & 0x1000))
  {
    return -1;
  }
  w->flags &= ~0x1000;
  layout_free(w);
  w->layout_root = w->saved_layout_root;
  w->saved_layout_root = 0;
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    wp->layout_cell = wp->saved_layout_cell;
    wp->saved_layout_cell = 0;
  }

  layout_fix_panes(w, w->sx, w->sy);
  notify_window("window-layout-changed", w);
  return 0;
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
void layout_free(struct window *w)
{
  layout_free_cell(w->layout_root);
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


int window_set_active_pane(struct window *w, struct window_pane *wp)
{
  log_debug("%s: pane %%%u (was %%%u)", __func__, wp->id, w->active->id);
  if (wp == w->active)
  {
    return 0;
  }
  w->last = w->active;
  w->active = wp;
  while (!window_pane_visible(w->active))
  {
    w->active = *((struct window_panes *) w->active->entry.tqe_prev)->tqh_last;
    if (w->active == 0)
    {
      w->active = *((struct window_panes *) (&w->panes)->tqh_last)->tqh_last;
    }
    if (w->active == wp)
    {
      notify_window("window-pane-changed", w);
      return 1;
    }
  }

  w->active->active_point = next_active_point;
  next_active_point += 1;
  w->active->flags |= 0x80;
  notify_window("window-pane-changed", w);
  return 1;
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
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
static u_int next_active_point
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


int window_zoom(struct window_pane *wp)
{
  struct window *w = wp->window;
  struct window_pane *wp1;
  unsigned int wp1_idx = 0;
  if (w->flags & 0x1000)
  {
    return -1;
  }
  if (!window_pane_visible(wp))
  {
    return -1;
  }
  if (window_count_panes(w) == 1)
  {
    return -1;
  }
  if (w->active != wp)
  {
    window_set_active_pane(w, wp);
  }
  for (wp1_idx = (&w->panes)->tqh_first; (&wp1[wp1_idx]) != 0; wp1_idx = wp1_idx->entry.tqe_next)
  {
    wp1->saved_layout_cell = wp1->layout_cell;
    wp1->layout_cell = 0;
  }

  w->saved_layout_root = w->layout_root;
  layout_init(w, wp);
  w->flags |= 0x1000;
  notify_window("window-layout-changed", w);
  return 0;
}


/*** DEPENDENCIES:
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
void layout_init(struct window *w, struct window_pane *wp)
{
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  lc_idx = (w->layout_root = layout_create_cell(0));
  layout_set_size(lc, w->sx, w->sy, 0, 0);
  layout_make_leaf(lc, wp);
  layout_fix_panes(w, w->sx, w->sy);
}


----------------------------
void notify_window(const char *name, struct window *w)
{
  struct cmd_find_state fs;
  cmd_find_from_window(&fs, w, 0);
  notify_add(name, &fs, 0, 0, w, 0);
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
int window_set_active_pane(struct window *w, struct window_pane *wp)
{
  log_debug("%s: pane %%%u (was %%%u)", __func__, wp->id, w->active->id);
  if (wp == w->active)
  {
    return 0;
  }
  w->last = w->active;
  w->active = wp;
  while (!window_pane_visible(w->active))
  {
    w->active = *((struct window_panes *) w->active->entry.tqe_prev)->tqh_last;
    if (w->active == 0)
    {
      w->active = *((struct window_panes *) (&w->panes)->tqh_last)->tqh_last;
    }
    if (w->active == wp)
    {
      notify_window("window-pane-changed", w);
      return 1;
    }
  }

  w->active->active_point = next_active_point;
  next_active_point += 1;
  w->active->flags |= 0x80;
  notify_window("window-pane-changed", w);
  return 1;
}


----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_1_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_right)
  {
    tmp->entry.rbe_right->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
void helper_helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_1_2_1(unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_right;
  if (parent->entry.rbe_right = tmp->entry.rbe_left)
  {
    tmp->entry.rbe_left->entry.rbe_parent = &parent[parent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
  {
    if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
    {
      parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
    }
    else
      parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->entry.rbe_left = &parent[parent_idx];
  parent->entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}


----------------------------
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
void helper_helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_1_2_2(unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct winlink *oleft;
  unsigned int oleft_idx = 0;
  if (oleft_idx = tmp->entry.rbe_left)
  {
    oleft->entry.rbe_color = 0;
  }
  tmp->entry.rbe_color = 1;
  do
  {
    oleft_idx = tmp->entry.rbe_left;
    if (tmp->entry.rbe_left = oleft->entry.rbe_right)
    {
      oleft->entry.rbe_right->entry.rbe_parent = &tmp[tmp_idx];
    }
    do
    {
    }
    while (0);
    if (oleft->entry.rbe_parent = tmp->entry.rbe_parent)
    {
      if ((&tmp[tmp_idx]) == tmp->entry.rbe_parent->entry.rbe_left)
      {
        tmp->entry.rbe_parent->entry.rbe_left = &oleft[oleft_idx];
      }
      else
        tmp->entry.rbe_parent->entry.rbe_right = &oleft[oleft_idx];
    }
    else
      head->rbh_root = &oleft[oleft_idx];
    oleft->entry.rbe_right = &tmp[tmp_idx];
    tmp->entry.rbe_parent = &oleft[oleft_idx];
    do
    {
    }
    while (0);
    if (oleft->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->entry.rbe_right;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_winlinks_RB_REMOVE_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const elm, struct winlink * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_right;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_1_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_1_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
void helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp->entry.rbe_color = 0;
    parent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    tmp_idx = parent->entry.rbe_right;
    if (parent->entry.rbe_right = tmp->entry.rbe_left)
    {
      tmp->entry.rbe_left->entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
      {
        parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->entry.rbe_left = &parent[parent_idx];
    parent->entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->entry.rbe_right;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
void helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_1_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_right)
  {
    tmp->entry.rbe_right->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_2_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_left)
  {
    tmp->entry.rbe_left->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_2_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
void helper_helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_2_2_1(unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_left;
  if (parent->entry.rbe_left = tmp->entry.rbe_right)
  {
    tmp->entry.rbe_right->entry.rbe_parent = &parent[parent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
  {
    if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
    {
      parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
    }
    else
      parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->entry.rbe_right = &parent[parent_idx];
  parent->entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_2_2_2(unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct winlink *oright;
  unsigned int oright_idx = 0;
  if (oright_idx = tmp->entry.rbe_right)
  {
    oright->entry.rbe_color = 0;
  }
  tmp->entry.rbe_color = 1;
  do
  {
    oright_idx = tmp->entry.rbe_right;
    if (tmp->entry.rbe_right = oright->entry.rbe_left)
    {
      oright->entry.rbe_left->entry.rbe_parent = &tmp[tmp_idx];
    }
    do
    {
    }
    while (0);
    if (oright->entry.rbe_parent = tmp->entry.rbe_parent)
    {
      if ((&tmp[tmp_idx]) == tmp->entry.rbe_parent->entry.rbe_left)
      {
        tmp->entry.rbe_parent->entry.rbe_left = &oright[oright_idx];
      }
      else
        tmp->entry.rbe_parent->entry.rbe_right = &oright[oright_idx];
    }
    else
      head->rbh_root = &oright[oright_idx];
    oright->entry.rbe_left = &tmp[tmp_idx];
    tmp->entry.rbe_parent = &oright[oright_idx];
    do
    {
    }
    while (0);
    if (oright->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->entry.rbe_left;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_winlinks_RB_REMOVE_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const elm, struct winlink * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_left;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_2_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
void helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp->entry.rbe_color = 0;
    parent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    tmp_idx = parent->entry.rbe_left;
    if (parent->entry.rbe_left = tmp->entry.rbe_right)
    {
      tmp->entry.rbe_right->entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
      {
        parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->entry.rbe_right = &parent[parent_idx];
    parent->entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->entry.rbe_left;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
void helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_2_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_left)
  {
    tmp->entry.rbe_left->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_2_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_winlinks_RB_REMOVE_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const elm, struct winlink * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if (parent->entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_winlinks_RB_REMOVE_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  else
  {
    helper_helper_winlinks_RB_REMOVE_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
void helper_helper_winlinks_RB_REMOVE_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const elm, struct winlink * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_right;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_1_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_1_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_winlinks_RB_REMOVE_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const elm, struct winlink * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_left;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_winlinks_RB_REMOVE_COLOR_1_2_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
None
----------------------------
***/


void winlinks_RB_REMOVE_COLOR(struct winlinks *head, struct winlink *parent, struct winlink *elm)
{
  unsigned int elm_idx = 0;
  unsigned int parent_idx = 0;
  struct winlink *tmp;
  unsigned int tmp_idx = 0;
  while ((((&elm[elm_idx]) == 0) || (elm->entry.rbe_color == 0)) && ((&elm[elm_idx]) != head->rbh_root))
  {
    helper_winlinks_RB_REMOVE_COLOR_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }

  if (elm)
  {
    elm->entry.rbe_color = 0;
  }
}


/*** DEPENDENCIES:
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
void helper_winlinks_RB_REMOVE_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const parent, struct winlink * const elm, struct winlink * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if (parent->entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_winlinks_RB_REMOVE_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  else
  {
    helper_helper_winlinks_RB_REMOVE_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


struct winlink *winlinks_RB_REMOVE(struct winlinks *head, struct winlink *elm)
{
  unsigned int elm_idx = 0;
  struct winlink *child;
  unsigned int child_idx = 0;
  struct winlink *parent;
  unsigned int parent_idx = 0;
  struct winlink *old = elm;
  int color;
  if (elm->entry.rbe_left == 0)
  {
    child_idx = elm->entry.rbe_right;
  }
  else
    if (elm->entry.rbe_right == 0)
  {
    child_idx = elm->entry.rbe_left;
  }
  else
  {
    helper_winlinks_RB_REMOVE_1(&elm_idx, &child_idx, &parent_idx, &color, head, elm, child, parent, old);
  }
  parent_idx = elm->entry.rbe_parent;
  color = elm->entry.rbe_color;
  if (child)
  {
    child->entry.rbe_parent = &parent[parent_idx];
  }
  if (parent)
  {
    if (parent->entry.rbe_left == (&elm[elm_idx]))
    {
      parent->entry.rbe_left = &child[child_idx];
    }
    else
      parent->entry.rbe_right = &child[child_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &child[child_idx];
  color:
  if (color == 0)
  {
    winlinks_RB_REMOVE_COLOR(head, parent, child);
  }

  return old;
}


/*** DEPENDENCIES:
void winlinks_RB_REMOVE_COLOR(struct winlinks *head, struct winlink *parent, struct winlink *elm)
{
  unsigned int elm_idx = 0;
  unsigned int parent_idx = 0;
  struct winlink *tmp;
  unsigned int tmp_idx = 0;
  while ((((&elm[elm_idx]) == 0) || (elm->entry.rbe_color == 0)) && ((&elm[elm_idx]) != head->rbh_root))
  {
    helper_winlinks_RB_REMOVE_COLOR_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }

  if (elm)
  {
    elm->entry.rbe_color = 0;
  }
}


----------------------------
void helper_winlinks_RB_REMOVE_1(unsigned int * const elm_idx_ref, unsigned int * const child_idx_ref, unsigned int * const parent_idx_ref, int * const color_ref, struct winlinks * const head, struct winlink * const elm, struct winlink * const child, struct winlink * const parent, struct winlink * const old)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int child_idx = *child_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  int color = *color_ref;
  struct winlink *left;
  unsigned int left_idx = 0;
  elm_idx = elm_idx->entry.rbe_right;
  while (left_idx = elm->entry.rbe_left)
  {
    elm_idx = &left[left_idx];
  }

  child_idx = elm->entry.rbe_right;
  parent_idx = elm->entry.rbe_parent;
  color = elm->entry.rbe_color;
  if (child)
  {
    child->entry.rbe_parent = &parent[parent_idx];
  }
  if (parent)
  {
    if (parent->entry.rbe_left == (&elm[elm_idx]))
    {
      parent->entry.rbe_left = &child[child_idx];
    }
    else
      parent->entry.rbe_right = &child[child_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &child[child_idx];
  if (elm->entry.rbe_parent == old)
  {
    parent_idx = &elm[elm_idx];
  }
  elm->entry = old->entry;
  if (old->entry.rbe_parent)
  {
    if (old->entry.rbe_parent->entry.rbe_left == old)
    {
      old->entry.rbe_parent->entry.rbe_left = &elm[elm_idx];
    }
    else
      old->entry.rbe_parent->entry.rbe_right = &elm[elm_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &elm[elm_idx];
  old->entry.rbe_left->entry.rbe_parent = &elm[elm_idx];
  if (old->entry.rbe_right)
  {
    old->entry.rbe_right->entry.rbe_parent = &elm[elm_idx];
  }
  if (parent)
  {
    left_idx = &parent[parent_idx];
    do
    {
      do
      {
      }
      while (0);
    }
    while (left_idx = left_idx->entry.rbe_parent);
  }
  goto color;
  *elm_idx_ref = elm_idx;
  *child_idx_ref = child_idx;
  *parent_idx_ref = parent_idx;
  *color_ref = color;
}


----------------------------
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
None
----------------------------
***/


void winlink_remove(struct winlinks *wwl, struct winlink *wl)
{
  struct window *w = wl->window;
  if (w != 0)
  {
    do
    {
      if (wl->wentry.tqe_next != 0)
      {
        wl->wentry.tqe_next->wentry.tqe_prev = wl->wentry.tqe_prev;
      }
      else
        (&w->winlinks)->tqh_last = wl->wentry.tqe_prev;
      *wl->wentry.tqe_prev = wl->wentry.tqe_next;
      ;
      ;
    }
    while (0);
    window_remove_ref(w, __func__);
  }
  winlinks_RB_REMOVE(wwl, wl);
  free(wl->status_text);
  free(wl);
}


/*** DEPENDENCIES:
struct winlink *winlinks_RB_REMOVE(struct winlinks *head, struct winlink *elm)
{
  unsigned int elm_idx = 0;
  struct winlink *child;
  unsigned int child_idx = 0;
  struct winlink *parent;
  unsigned int parent_idx = 0;
  struct winlink *old = elm;
  int color;
  if (elm->entry.rbe_left == 0)
  {
    child_idx = elm->entry.rbe_right;
  }
  else
    if (elm->entry.rbe_right == 0)
  {
    child_idx = elm->entry.rbe_left;
  }
  else
  {
    helper_winlinks_RB_REMOVE_1(&elm_idx, &child_idx, &parent_idx, &color, head, elm, child, parent, old);
  }
  parent_idx = elm->entry.rbe_parent;
  color = elm->entry.rbe_color;
  if (child)
  {
    child->entry.rbe_parent = &parent[parent_idx];
  }
  if (parent)
  {
    if (parent->entry.rbe_left == (&elm[elm_idx]))
    {
      parent->entry.rbe_left = &child[child_idx];
    }
    else
      parent->entry.rbe_right = &child[child_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &child[child_idx];
  color:
  if (color == 0)
  {
    winlinks_RB_REMOVE_COLOR(head, parent, child);
  }

  return old;
}


----------------------------
None
----------------------------
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
None
----------------------------
***/


void window_lost_pane(struct window *w, struct window_pane *wp)
{
  log_debug("%s: @%u pane %%%u", __func__, w->id, wp->id);
  if (wp == marked_pane.wp)
  {
    server_clear_marked();
  }
  if (wp == w->active)
  {
    w->active = w->last;
    w->last = 0;
    if (w->active == 0)
    {
      w->active = *((struct window_panes *) wp->entry.tqe_prev)->tqh_last;
      if (w->active == 0)
      {
        w->active = wp->entry.tqe_next;
      }
    }
    if (w->active != 0)
    {
      w->active->flags |= 0x80;
      notify_window("window-pane-changed", w);
    }
  }
  else
    if (wp == w->last)
  {
    w->last = 0;
  }
}


/*** DEPENDENCIES:
extern struct cmd_find_state marked_pane
----------------------------
void server_clear_marked(void)
{
  cmd_find_clear_state(&marked_pane, 0);
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


void window_remove_pane(struct window *w, struct window_pane *wp)
{
  window_lost_pane(w, wp);
  do
  {
    if (wp->entry.tqe_next != 0)
    {
      wp->entry.tqe_next->entry.tqe_prev = wp->entry.tqe_prev;
    }
    else
      (&w->panes)->tqh_last = wp->entry.tqe_prev;
    *wp->entry.tqe_prev = wp->entry.tqe_next;
    ;
    ;
  }
  while (0);
  window_pane_destroy(wp);
}


/*** DEPENDENCIES:
None
----------------------------
void window_lost_pane(struct window *w, struct window_pane *wp)
{
  log_debug("%s: @%u pane %%%u", __func__, w->id, wp->id);
  if (wp == marked_pane.wp)
  {
    server_clear_marked();
  }
  if (wp == w->active)
  {
    w->active = w->last;
    w->last = 0;
    if (w->active == 0)
    {
      w->active = *((struct window_panes *) wp->entry.tqe_prev)->tqh_last;
      if (w->active == 0)
      {
        w->active = wp->entry.tqe_next;
      }
    }
    if (w->active != 0)
    {
      w->active->flags |= 0x80;
      notify_window("window-pane-changed", w);
    }
  }
  else
    if (wp == w->last)
  {
    w->last = 0;
  }
}


----------------------------
None
----------------------------
***/


static int winlink_next_index(struct winlinks *wwl, int idx)
{
  int i;
  i = idx;
  do
  {
    if (winlink_find_by_index(wwl, i) == 0)
    {
      return i;
    }
    if (i == 2147483647)
    {
      i = 0;
    }
    else
      i++;
    i += 1;
  }
  while (i != idx);
  return -1;
}


/*** DEPENDENCIES:
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
struct winlink *winlink_find_by_index(struct winlinks *wwl, int idx)
{
  struct winlink wl;
  if (idx < 0)
  {
    fatalx("bad index");
  }
  wl.idx = idx;
  return winlinks_RB_FIND(wwl, &wl);
}


----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_winlinks_RB_INSERT_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const elm, struct winlink * const parent, struct winlink * const gparent, struct winlink * const tmp, unsigned int gparent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->entry.rbe_right;
  if ((&tmp[tmp_idx]) && (tmp->entry.rbe_color == 1))
  {
    tmp->entry.rbe_color = 0;
    do
    {
      parent->entry.rbe_color = 0;
      gparent->entry.rbe_color = 1;
    }
    while (0);
    elm_idx = &gparent[gparent_idx];
    continue;
  }
  if (parent->entry.rbe_right == (&elm[elm_idx]))
  {
    helper_helper_helper_winlinks_RB_INSERT_COLOR_1_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_winlinks_RB_INSERT_COLOR_1_1_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
void helper_helper_helper_winlinks_RB_INSERT_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const gparent, struct winlink * const tmp, unsigned int gparent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->entry.rbe_left;
  if (gparent->entry.rbe_left = tmp->entry.rbe_right)
  {
    tmp->entry.rbe_right->entry.rbe_parent = &gparent[gparent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent = gparent->entry.rbe_parent)
  {
    if ((&gparent[gparent_idx]) == gparent->entry.rbe_parent->entry.rbe_left)
    {
      gparent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
    }
    else
      gparent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->entry.rbe_right = &gparent[gparent_idx];
  gparent->entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}


----------------------------
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
void helper_helper_helper_winlinks_RB_INSERT_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const elm, struct winlink * const parent, struct winlink * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp_idx = parent->entry.rbe_right;
    if (parent->entry.rbe_right = tmp->entry.rbe_left)
    {
      tmp->entry.rbe_left->entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
      {
        parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->entry.rbe_left = &parent[parent_idx];
    parent->entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = &parent[parent_idx];
  parent_idx = &elm[elm_idx];
  elm_idx = &tmp[tmp_idx];
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_winlinks_RB_INSERT_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const elm, struct winlink * const parent, struct winlink * const gparent, struct winlink * const tmp, unsigned int gparent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->entry.rbe_left;
  if ((&tmp[tmp_idx]) && (tmp->entry.rbe_color == 1))
  {
    tmp->entry.rbe_color = 0;
    do
    {
      parent->entry.rbe_color = 0;
      gparent->entry.rbe_color = 1;
    }
    while (0);
    elm_idx = &gparent[gparent_idx];
    continue;
  }
  if (parent->entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_helper_winlinks_RB_INSERT_COLOR_1_2_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_winlinks_RB_INSERT_COLOR_1_2_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
void helper_helper_helper_winlinks_RB_INSERT_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const elm, struct winlink * const parent, struct winlink * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp_idx = parent->entry.rbe_left;
    if (parent->entry.rbe_left = tmp->entry.rbe_right)
    {
      tmp->entry.rbe_right->entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
      {
        parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->entry.rbe_right = &parent[parent_idx];
    parent->entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = &parent[parent_idx];
  parent_idx = &elm[elm_idx];
  elm_idx = &tmp[tmp_idx];
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_helper_winlinks_RB_INSERT_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const gparent, struct winlink * const tmp, unsigned int gparent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->entry.rbe_right;
  if (gparent->entry.rbe_right = tmp->entry.rbe_left)
  {
    tmp->entry.rbe_left->entry.rbe_parent = &gparent[gparent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent = gparent->entry.rbe_parent)
  {
    if ((&gparent[gparent_idx]) == gparent->entry.rbe_parent->entry.rbe_left)
    {
      gparent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
    }
    else
      gparent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->entry.rbe_left = &gparent[gparent_idx];
  gparent->entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}


----------------------------
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'gparent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_winlinks_RB_INSERT_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const gparent_idx_ref, unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const elm, struct winlink * const parent, struct winlink * const gparent, struct winlink * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int gparent_idx = *gparent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  gparent_idx = parent->entry.rbe_parent;
  if ((&parent[parent_idx]) == gparent->entry.rbe_left)
  {
    helper_helper_winlinks_RB_INSERT_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  else
  {
    helper_helper_winlinks_RB_INSERT_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *gparent_idx_ref = gparent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
void helper_helper_winlinks_RB_INSERT_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const elm, struct winlink * const parent, struct winlink * const gparent, struct winlink * const tmp, unsigned int gparent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->entry.rbe_right;
  if ((&tmp[tmp_idx]) && (tmp->entry.rbe_color == 1))
  {
    tmp->entry.rbe_color = 0;
    do
    {
      parent->entry.rbe_color = 0;
      gparent->entry.rbe_color = 1;
    }
    while (0);
    elm_idx = &gparent[gparent_idx];
    continue;
  }
  if (parent->entry.rbe_right == (&elm[elm_idx]))
  {
    helper_helper_helper_winlinks_RB_INSERT_COLOR_1_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_winlinks_RB_INSERT_COLOR_1_1_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_winlinks_RB_INSERT_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const elm, struct winlink * const parent, struct winlink * const gparent, struct winlink * const tmp, unsigned int gparent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->entry.rbe_left;
  if ((&tmp[tmp_idx]) && (tmp->entry.rbe_color == 1))
  {
    tmp->entry.rbe_color = 0;
    do
    {
      parent->entry.rbe_color = 0;
      gparent->entry.rbe_color = 1;
    }
    while (0);
    elm_idx = &gparent[gparent_idx];
    continue;
  }
  if (parent->entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_helper_winlinks_RB_INSERT_COLOR_1_2_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_winlinks_RB_INSERT_COLOR_1_2_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
None
----------------------------
***/


void winlinks_RB_INSERT_COLOR(struct winlinks *head, struct winlink *elm)
{
  unsigned int elm_idx = 0;
  struct winlink *parent;
  unsigned int parent_idx = 0;
  struct winlink *gparent;
  unsigned int gparent_idx = 0;
  struct winlink *tmp;
  unsigned int tmp_idx = 0;
  while ((parent_idx = elm->entry.rbe_parent) && (parent->entry.rbe_color == 1))
  {
    helper_winlinks_RB_INSERT_COLOR_1(&elm_idx, &parent_idx, &gparent_idx, &tmp_idx, head, elm, parent, gparent, tmp);
  }

  head->rbh_root->entry.rbe_color = 0;
}


/*** DEPENDENCIES:
void helper_winlinks_RB_INSERT_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const gparent_idx_ref, unsigned int * const tmp_idx_ref, struct winlinks * const head, struct winlink * const elm, struct winlink * const parent, struct winlink * const gparent, struct winlink * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int gparent_idx = *gparent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  gparent_idx = parent->entry.rbe_parent;
  if ((&parent[parent_idx]) == gparent->entry.rbe_left)
  {
    helper_helper_winlinks_RB_INSERT_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  else
  {
    helper_helper_winlinks_RB_INSERT_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *gparent_idx_ref = gparent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
None
----------------------------
***/


struct winlink *winlinks_RB_INSERT(struct winlinks *head, struct winlink *elm)
{
  struct winlink *tmp;
  unsigned int tmp_idx = 0;
  struct winlink *parent = 0;
  unsigned int parent_idx = 0;
  int comp = 0;
  tmp_idx = head->rbh_root;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    comp = winlink_cmp(elm, parent);
    if (comp < 0)
    {
      tmp_idx = tmp_idx->entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->entry.rbe_right;
    }
    else
      return tmp;
  }

  do
  {
    elm->entry.rbe_parent = &parent[parent_idx];
    elm->entry.rbe_left = (elm->entry.rbe_right = 0);
    elm->entry.rbe_color = 1;
  }
  while (0);
  if ((&parent[parent_idx]) != 0)
  {
    if (comp < 0)
    {
      parent->entry.rbe_left = elm;
    }
    else
      parent->entry.rbe_right = elm;
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = elm;
  winlinks_RB_INSERT_COLOR(head, elm);
  return 0;
}


/*** DEPENDENCIES:
int winlink_cmp(struct winlink *wl1, struct winlink *wl2)
{
  return wl1->idx - wl2->idx;
}


----------------------------
void winlinks_RB_INSERT_COLOR(struct winlinks *head, struct winlink *elm)
{
  unsigned int elm_idx = 0;
  struct winlink *parent;
  unsigned int parent_idx = 0;
  struct winlink *gparent;
  unsigned int gparent_idx = 0;
  struct winlink *tmp;
  unsigned int tmp_idx = 0;
  while ((parent_idx = elm->entry.rbe_parent) && (parent->entry.rbe_color == 1))
  {
    helper_winlinks_RB_INSERT_COLOR_1(&elm_idx, &parent_idx, &gparent_idx, &tmp_idx, head, elm, parent, gparent, tmp);
  }

  head->rbh_root->entry.rbe_color = 0;
}


----------------------------
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
None
----------------------------
***/


struct winlink *winlink_add(struct winlinks *wwl, int idx)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  if (idx < 0)
  {
    if ((idx = winlink_next_index(wwl, (-idx) - 1)) == (-1))
    {
      return 0;
    }
  }
  else
    if (winlink_find_by_index(wwl, idx) != 0)
  {
    return 0;
  }
  wl_idx = xcalloc(1, sizeof(*wl_idx));
  wl->idx = idx;
  winlinks_RB_INSERT(wwl, wl);
  return wl;
}


/*** DEPENDENCIES:
static int winlink_next_index(struct winlinks *wwl, int idx)
{
  int i;
  i = idx;
  do
  {
    if (winlink_find_by_index(wwl, i) == 0)
    {
      return i;
    }
    if (i == 2147483647)
    {
      i = 0;
    }
    else
      i++;
    i += 1;
  }
  while (i != idx);
  return -1;
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
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
struct winlink *winlink_find_by_index(struct winlinks *wwl, int idx)
{
  struct winlink wl;
  if (idx < 0)
  {
    fatalx("bad index");
  }
  wl.idx = idx;
  return winlinks_RB_FIND(wwl, &wl);
}


----------------------------
struct winlink *winlinks_RB_INSERT(struct winlinks *head, struct winlink *elm)
{
  struct winlink *tmp;
  unsigned int tmp_idx = 0;
  struct winlink *parent = 0;
  unsigned int parent_idx = 0;
  int comp = 0;
  tmp_idx = head->rbh_root;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    comp = winlink_cmp(elm, parent);
    if (comp < 0)
    {
      tmp_idx = tmp_idx->entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->entry.rbe_right;
    }
    else
      return tmp;
  }

  do
  {
    elm->entry.rbe_parent = &parent[parent_idx];
    elm->entry.rbe_left = (elm->entry.rbe_right = 0);
    elm->entry.rbe_color = 1;
  }
  while (0);
  if ((&parent[parent_idx]) != 0)
  {
    if (comp < 0)
    {
      parent->entry.rbe_left = elm;
    }
    else
      parent->entry.rbe_right = elm;
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = elm;
  winlinks_RB_INSERT_COLOR(head, elm);
  return 0;
}


----------------------------
None
----------------------------
***/


void winlink_set_window(struct winlink *wl, struct window *w)
{
  if (wl->window != 0)
  {
    do
    {
      if (wl->wentry.tqe_next != 0)
      {
        wl->wentry.tqe_next->wentry.tqe_prev = wl->wentry.tqe_prev;
      }
      else
        (&wl->window->winlinks)->tqh_last = wl->wentry.tqe_prev;
      *wl->wentry.tqe_prev = wl->wentry.tqe_next;
      ;
      ;
    }
    while (0);
    window_remove_ref(wl->window, __func__);
  }
  do
  {
    wl->wentry.tqe_next = 0;
    wl->wentry.tqe_prev = (&w->winlinks)->tqh_last;
    *(&w->winlinks)->tqh_last = wl;
    (&w->winlinks)->tqh_last = &wl->wentry.tqe_next;
  }
  while (0);
  wl->window = w;
  window_add_ref(w, __func__);
}


/*** DEPENDENCIES:
None
----------------------------
void window_add_ref(struct window *w, const char *from)
{
  w->references += 1;
  log_debug("%s: @%u %s, now %d", __func__, w->id, from, w->references);
}


----------------------------
None
----------------------------
***/


void winlink_stack_push(struct winlink_stack *stack, struct winlink *wl)
{
  if (wl == 0)
  {
    return;
  }
  winlink_stack_remove(stack, wl);
  do
  {
    if ((wl->sentry.tqe_next = stack->tqh_first) != 0)
    {
      stack->tqh_first->sentry.tqe_prev = &wl->sentry.tqe_next;
    }
    else
      stack->tqh_last = &wl->sentry.tqe_next;
    stack->tqh_first = wl;
    wl->sentry.tqe_prev = &stack->tqh_first;
  }
  while (0);
}


/*** DEPENDENCIES:
void winlink_stack_remove(struct winlink_stack *stack, struct winlink *wl)
{
  struct winlink *wl2;
  unsigned int wl2_idx = 0;
  if (wl == 0)
  {
    return;
  }
  for (wl2_idx = stack->tqh_first; (&wl2[wl2_idx]) != 0; wl2_idx = wl2_idx->sentry.tqe_next)
  {
    if ((&wl2[wl2_idx]) == wl)
    {
      do
      {
        if (wl->sentry.tqe_next != 0)
        {
          wl->sentry.tqe_next->sentry.tqe_prev = wl->sentry.tqe_prev;
        }
        else
          stack->tqh_last = wl->sentry.tqe_prev;
        *wl->sentry.tqe_prev = wl->sentry.tqe_next;
        ;
        ;
      }
      while (0);
      return;
    }
  }

}


----------------------------
None
----------------------------
***/


static void window_pane_mode_timer(int fd, short events, void *arg)
{
  struct window_pane *wp = arg;
  struct timeval tv = {.tv_sec = 10};
  int n = 0;
  evtimer_del(&wp->modetimer);
  evtimer_add(&wp->modetimer, &tv);
  log_debug("%%%u in mode: last=%ld", wp->id, (long) wp->modelast);
  if (wp->modelast < (time(0) - 180))
  {
    if ((ioctl(wp->fd, FIONREAD, &n) == (-1)) || (n > 0))
    {
      window_pane_reset_mode(wp);
    }
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
pub time: Time
----------------------------
None
----------------------------
***/


int window_pane_set_mode(struct window_pane *wp, const struct window_mode *mode, struct cmd_find_state *fs, struct args *args)
{
  struct screen *s;
  unsigned int s_idx = 0;
  struct timeval tv = {.tv_sec = 10};
  if (wp->mode != 0)
  {
    return 1;
  }
  wp->mode = mode;
  wp->modelast = time(0);
  evtimer_set(&wp->modetimer, window_pane_mode_timer, wp);
  evtimer_add(&wp->modetimer, &tv);
  if ((s_idx = wp->mode->init(wp, fs, args)) != 0)
  {
    wp->screen = &s[s_idx];
  }
  wp->flags |= 0x1 | 0x80;
  server_status_window(wp->window);
  notify_pane("pane-mode-changed", wp);
  return 0;
}


/*** DEPENDENCIES:
None
----------------------------
static void window_pane_mode_timer(int fd, short events, void *arg)
{
  struct window_pane *wp = arg;
  struct timeval tv = {.tv_sec = 10};
  int n = 0;
  evtimer_del(&wp->modetimer);
  evtimer_add(&wp->modetimer, &tv);
  log_debug("%%%u in mode: last=%ld", wp->id, (long) wp->modelast);
  if (wp->modelast < (time(0) - 180))
  {
    if ((ioctl(wp->fd, FIONREAD, &n) == (-1)) || (n > 0))
    {
      window_pane_reset_mode(wp);
    }
  }
}


----------------------------
void server_status_window(struct window *w)
{
  struct session *s;
  unsigned int s_idx = 0;
  for (s_idx = sessions_RB_MINMAX(&sessions, -1); (&s[s_idx]) != 0; s_idx = sessions_RB_NEXT(s_idx))
  {
    if (session_has(s, w))
    {
      server_status_session(s);
    }
  }

}


----------------------------
None
----------------------------
pub time: Time
----------------------------
None
----------------------------
None
----------------------------
***/


void window_pane_key(struct window_pane *wp, struct client *c, struct session *s, key_code key, struct mouse_event *m)
{
  struct window_pane *wp2;
  unsigned int wp2_idx = 0;
  if ((((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) >= KEYC_MOUSE) && ((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) < KEYC_BSPACE)) && (m == 0))
  {
    return;
  }
  if (wp->mode != 0)
  {
    wp->modelast = time(0);
    if (wp->mode->key != 0)
    {
      wp->mode->key(wp, c, s, key & (~0x1000000000000ULL), m);
    }
    return;
  }
  if ((wp->fd == (-1)) || (wp->flags & 0x40))
  {
    return;
  }
  input_key(wp, key, m);
  if (((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) >= KEYC_MOUSE) && ((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) < KEYC_BSPACE))
  {
    return;
  }
  if (options_get_number(wp->window->options, "synchronize-panes"))
  {
    for (wp2_idx = (&wp->window->panes)->tqh_first; (&wp2[wp2_idx]) != 0; wp2_idx = wp2_idx->entry.tqe_next)
    {
      if (((&wp2[wp2_idx]) == wp) || (wp2->mode != 0))
      {
        continue;
      }
      if ((wp2->fd == (-1)) || (wp2->flags & 0x40))
      {
        continue;
      }
      if (window_pane_visible(wp2))
      {
        input_key(wp2, key, 0);
      }
    }

  }
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
typedef unsigned long long key_code
----------------------------
pub time: Time
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
void input_key(struct window_pane *wp, key_code key, struct mouse_event *m)
{
  const struct input_key_ent *ike;
  unsigned int ike_idx = 0;
  u_int i;
  size_t dlen;
  char *out;
  unsigned int out_idx = 0;
  key_code justkey;
  struct utf8_data ud;
  log_debug("writing key 0x%llx (%s) to %%%u", key, key_string_lookup_key(key), wp->id);
  if (((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) >= KEYC_MOUSE) && ((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) < KEYC_BSPACE))
  {
    if (((m != 0) && (m->wp != (-1))) && (((u_int) m->wp) == wp->id))
    {
      input_key_mouse(wp, m);
    }
    return;
  }
  justkey = key & (~(0x1000000000000ULL | 0x200000000000ULL));
  if (justkey <= 0x7f)
  {
    if (key & 0x200000000000ULL)
    {
      bufferevent_write(wp->event, "\033", 1);
    }
    ud.data[0] = justkey;
    bufferevent_write(wp->event, &ud.data[0], 1);
    return;
  }
  if ((justkey > 0x7f) && (justkey < 0x000010000000ULL))
  {
    if (utf8_split(justkey, &ud) != UTF8_DONE)
    {
      return;
    }
    if (key & 0x200000000000ULL)
    {
      bufferevent_write(wp->event, "\033", 1);
    }
    bufferevent_write(wp->event, ud.data, ud.size);
    return;
  }
  if (options_get_number(wp->window->options, "xterm-keys"))
  {
    if ((out_idx = xterm_keys_lookup(key)) != 0)
    {
      bufferevent_write(wp->event, out, strlen(out));
      free(out);
      return;
    }
  }
  key &= ~0x1000000000000ULL;
  for (i = 0; i < ((sizeof(input_keys)) / (sizeof(input_keys[0]))); i += 1)
  {
    ike_idx = &input_keys[i];
    if ((ike->flags & 0x1) && (!(wp->screen->mode & 0x8)))
    {
      continue;
    }
    if ((ike->flags & 0x2) && (!(wp->screen->mode & 0x4)))
    {
      continue;
    }
    if ((key & 0x200000000000ULL) && ((ike->key | 0x200000000000ULL) == key))
    {
      break;
    }
    if (ike->key == key)
    {
      break;
    }
  }

  if (i == ((sizeof(input_keys)) / (sizeof(input_keys[0]))))
  {
    log_debug("key 0x%llx missing", key);
    return;
  }
  dlen = strlen(ike->data);
  log_debug("found key 0x%llx: \"%s\"", key, ike->data);
  if (key & 0x200000000000ULL)
  {
    bufferevent_write(wp->event, "\033", 1);
  }
  bufferevent_write(wp->event, ike->data, dlen);
}


----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_windows_RB_INSERT_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const elm, struct window * const parent, struct window * const gparent, struct window * const tmp, unsigned int gparent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->entry.rbe_right;
  if ((&tmp[tmp_idx]) && (tmp->entry.rbe_color == 1))
  {
    tmp->entry.rbe_color = 0;
    do
    {
      parent->entry.rbe_color = 0;
      gparent->entry.rbe_color = 1;
    }
    while (0);
    elm_idx = &gparent[gparent_idx];
    continue;
  }
  if (parent->entry.rbe_right == (&elm[elm_idx]))
  {
    helper_helper_helper_windows_RB_INSERT_COLOR_1_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_windows_RB_INSERT_COLOR_1_1_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
void helper_helper_helper_windows_RB_INSERT_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const gparent, struct window * const tmp, unsigned int gparent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->entry.rbe_left;
  if (gparent->entry.rbe_left = tmp->entry.rbe_right)
  {
    tmp->entry.rbe_right->entry.rbe_parent = &gparent[gparent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent = gparent->entry.rbe_parent)
  {
    if ((&gparent[gparent_idx]) == gparent->entry.rbe_parent->entry.rbe_left)
    {
      gparent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
    }
    else
      gparent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->entry.rbe_right = &gparent[gparent_idx];
  gparent->entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_helper_windows_RB_INSERT_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const elm, struct window * const parent, struct window * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp_idx = parent->entry.rbe_right;
    if (parent->entry.rbe_right = tmp->entry.rbe_left)
    {
      tmp->entry.rbe_left->entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
      {
        parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->entry.rbe_left = &parent[parent_idx];
    parent->entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = &parent[parent_idx];
  parent_idx = &elm[elm_idx];
  elm_idx = &tmp[tmp_idx];
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_windows_RB_INSERT_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const elm, struct window * const parent, struct window * const gparent, struct window * const tmp, unsigned int gparent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->entry.rbe_left;
  if ((&tmp[tmp_idx]) && (tmp->entry.rbe_color == 1))
  {
    tmp->entry.rbe_color = 0;
    do
    {
      parent->entry.rbe_color = 0;
      gparent->entry.rbe_color = 1;
    }
    while (0);
    elm_idx = &gparent[gparent_idx];
    continue;
  }
  if (parent->entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_helper_windows_RB_INSERT_COLOR_1_2_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_windows_RB_INSERT_COLOR_1_2_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
void helper_helper_helper_windows_RB_INSERT_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const gparent, struct window * const tmp, unsigned int gparent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->entry.rbe_right;
  if (gparent->entry.rbe_right = tmp->entry.rbe_left)
  {
    tmp->entry.rbe_left->entry.rbe_parent = &gparent[gparent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent = gparent->entry.rbe_parent)
  {
    if ((&gparent[gparent_idx]) == gparent->entry.rbe_parent->entry.rbe_left)
    {
      gparent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
    }
    else
      gparent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->entry.rbe_left = &gparent[gparent_idx];
  gparent->entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_helper_windows_RB_INSERT_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const elm, struct window * const parent, struct window * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp_idx = parent->entry.rbe_left;
    if (parent->entry.rbe_left = tmp->entry.rbe_right)
    {
      tmp->entry.rbe_right->entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent = parent->entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->entry.rbe_parent->entry.rbe_left)
      {
        parent->entry.rbe_parent->entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->entry.rbe_parent->entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->entry.rbe_right = &parent[parent_idx];
    parent->entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = &parent[parent_idx];
  parent_idx = &elm[elm_idx];
  elm_idx = &tmp[tmp_idx];
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'gparent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_windows_RB_INSERT_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const gparent_idx_ref, unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const elm, struct window * const parent, struct window * const gparent, struct window * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int gparent_idx = *gparent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  gparent_idx = parent->entry.rbe_parent;
  if ((&parent[parent_idx]) == gparent->entry.rbe_left)
  {
    helper_helper_windows_RB_INSERT_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  else
  {
    helper_helper_windows_RB_INSERT_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *gparent_idx_ref = gparent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
void helper_helper_windows_RB_INSERT_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const elm, struct window * const parent, struct window * const gparent, struct window * const tmp, unsigned int gparent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->entry.rbe_right;
  if ((&tmp[tmp_idx]) && (tmp->entry.rbe_color == 1))
  {
    tmp->entry.rbe_color = 0;
    do
    {
      parent->entry.rbe_color = 0;
      gparent->entry.rbe_color = 1;
    }
    while (0);
    elm_idx = &gparent[gparent_idx];
    continue;
  }
  if (parent->entry.rbe_right == (&elm[elm_idx]))
  {
    helper_helper_helper_windows_RB_INSERT_COLOR_1_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_windows_RB_INSERT_COLOR_1_1_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_windows_RB_INSERT_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const elm, struct window * const parent, struct window * const gparent, struct window * const tmp, unsigned int gparent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->entry.rbe_left;
  if ((&tmp[tmp_idx]) && (tmp->entry.rbe_color == 1))
  {
    tmp->entry.rbe_color = 0;
    do
    {
      parent->entry.rbe_color = 0;
      gparent->entry.rbe_color = 1;
    }
    while (0);
    elm_idx = &gparent[gparent_idx];
    continue;
  }
  if (parent->entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_helper_windows_RB_INSERT_COLOR_1_2_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_windows_RB_INSERT_COLOR_1_2_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


void windows_RB_INSERT_COLOR(struct windows *head, struct window *elm)
{
  unsigned int elm_idx = 0;
  struct window *parent;
  unsigned int parent_idx = 0;
  struct window *gparent;
  unsigned int gparent_idx = 0;
  struct window *tmp;
  unsigned int tmp_idx = 0;
  while ((parent_idx = elm->entry.rbe_parent) && (parent->entry.rbe_color == 1))
  {
    helper_windows_RB_INSERT_COLOR_1(&elm_idx, &parent_idx, &gparent_idx, &tmp_idx, head, elm, parent, gparent, tmp);
  }

  head->rbh_root->entry.rbe_color = 0;
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
void helper_windows_RB_INSERT_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const gparent_idx_ref, unsigned int * const tmp_idx_ref, struct windows * const head, struct window * const elm, struct window * const parent, struct window * const gparent, struct window * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int gparent_idx = *gparent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  gparent_idx = parent->entry.rbe_parent;
  if ((&parent[parent_idx]) == gparent->entry.rbe_left)
  {
    helper_helper_windows_RB_INSERT_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  else
  {
    helper_helper_windows_RB_INSERT_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *gparent_idx_ref = gparent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


struct window *windows_RB_NFIND(struct windows *head, struct window *elm)
{
  struct window *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct window *res = 0;
  unsigned int res_idx = 0;
  int comp;
  while (tmp)
  {
    comp = window_cmp(elm, tmp);
    if (comp < 0)
    {
      res_idx = &tmp[tmp_idx];
      tmp_idx = tmp_idx->entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->entry.rbe_right;
    }
    else
      return tmp;
  }

  return res;
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
int window_cmp(struct window *w1, struct window *w2)
{
  return w1->id - w2->id;
}


----------------------------
None
----------------------------
***/


struct winlink *winlinks_RB_NFIND(struct winlinks *head, struct winlink *elm)
{
  struct winlink *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct winlink *res = 0;
  unsigned int res_idx = 0;
  int comp;
  while (tmp)
  {
    comp = winlink_cmp(elm, tmp);
    if (comp < 0)
    {
      res_idx = &tmp[tmp_idx];
      tmp_idx = tmp_idx->entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->entry.rbe_right;
    }
    else
      return tmp;
  }

  return res;
}


/*** DEPENDENCIES:
int winlink_cmp(struct winlink *wl1, struct winlink *wl2)
{
  return wl1->idx - wl2->idx;
}


----------------------------
struct winlinks
{
  struct winlink *rbh_root;
}
----------------------------
None
----------------------------
***/


void helper_window_add_pane_1(struct window * const w, struct window_pane * const other, int full_size, unsigned int other_idx, struct window_pane * const wp, unsigned int wp_idx)
{
  log_debug("%s: @%u before %%%u", __func__, w->id, wp->id);
  if (full_size)
  {
    do
    {
      if ((wp->entry.tqe_next = (&w->panes)->tqh_first) != 0)
      {
        (&w->panes)->tqh_first->entry.tqe_prev = &wp->entry.tqe_next;
      }
      else
        (&w->panes)->tqh_last = &wp->entry.tqe_next;
      (&w->panes)->tqh_first = &wp[wp_idx];
      wp->entry.tqe_prev = &(&w->panes)->tqh_first;
    }
    while (0);
  }
  else
    do
  {
    wp->entry.tqe_prev = other->entry.tqe_prev;
    wp->entry.tqe_next = &other[other_idx];
    *other->entry.tqe_prev = &wp[wp_idx];
    other->entry.tqe_prev = &wp->entry.tqe_next;
  }
  while (0);
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


void helper_window_add_pane_2(struct window * const w, struct window_pane * const other, int full_size, struct window_pane * const wp, unsigned int wp_idx)
{
  log_debug("%s: @%u after %%%u", __func__, w->id, wp->id);
  if (full_size)
  {
    do
    {
      wp->entry.tqe_next = 0;
      wp->entry.tqe_prev = (&w->panes)->tqh_last;
      *(&w->panes)->tqh_last = &wp[wp_idx];
      (&w->panes)->tqh_last = &wp->entry.tqe_next;
    }
    while (0);
  }
  else
    do
  {
    if ((wp->entry.tqe_next = other->entry.tqe_next) != 0)
    {
      wp->entry.tqe_next->entry.tqe_prev = &wp->entry.tqe_next;
    }
    else
      (&w->panes)->tqh_last = &wp->entry.tqe_next;
    other->entry.tqe_next = &wp[wp_idx];
    wp->entry.tqe_prev = &other->entry.tqe_next;
  }
  while (0);
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


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_window_pane_tree_RB_INSERT_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const gparent, struct window_pane * const tmp, unsigned int gparent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->tree_entry.rbe_left;
  if (gparent->tree_entry.rbe_left = tmp->tree_entry.rbe_right)
  {
    tmp->tree_entry.rbe_right->tree_entry.rbe_parent = &gparent[gparent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->tree_entry.rbe_parent = gparent->tree_entry.rbe_parent)
  {
    if ((&gparent[gparent_idx]) == gparent->tree_entry.rbe_parent->tree_entry.rbe_left)
    {
      gparent->tree_entry.rbe_parent->tree_entry.rbe_left = &tmp[tmp_idx];
    }
    else
      gparent->tree_entry.rbe_parent->tree_entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->tree_entry.rbe_right = &gparent[gparent_idx];
  gparent->tree_entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->tree_entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct window_pane_tree
{
  struct window_pane *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_window_pane_tree_RB_INSERT_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const elm, struct window_pane * const parent, struct window_pane * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp_idx = parent->tree_entry.rbe_right;
    if (parent->tree_entry.rbe_right = tmp->tree_entry.rbe_left)
    {
      tmp->tree_entry.rbe_left->tree_entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->tree_entry.rbe_parent = parent->tree_entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->tree_entry.rbe_parent->tree_entry.rbe_left)
      {
        parent->tree_entry.rbe_parent->tree_entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->tree_entry.rbe_parent->tree_entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->tree_entry.rbe_left = &parent[parent_idx];
    parent->tree_entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->tree_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = &parent[parent_idx];
  parent_idx = &elm[elm_idx];
  elm_idx = &tmp[tmp_idx];
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct window_pane_tree
{
  struct window_pane *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_window_pane_tree_RB_INSERT_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const gparent, struct window_pane * const tmp, unsigned int gparent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->tree_entry.rbe_right;
  if (gparent->tree_entry.rbe_right = tmp->tree_entry.rbe_left)
  {
    tmp->tree_entry.rbe_left->tree_entry.rbe_parent = &gparent[gparent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->tree_entry.rbe_parent = gparent->tree_entry.rbe_parent)
  {
    if ((&gparent[gparent_idx]) == gparent->tree_entry.rbe_parent->tree_entry.rbe_left)
    {
      gparent->tree_entry.rbe_parent->tree_entry.rbe_left = &tmp[tmp_idx];
    }
    else
      gparent->tree_entry.rbe_parent->tree_entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->tree_entry.rbe_left = &gparent[gparent_idx];
  gparent->tree_entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->tree_entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct window_pane_tree
{
  struct window_pane *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_window_pane_tree_RB_INSERT_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const elm, struct window_pane * const parent, struct window_pane * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp_idx = parent->tree_entry.rbe_left;
    if (parent->tree_entry.rbe_left = tmp->tree_entry.rbe_right)
    {
      tmp->tree_entry.rbe_right->tree_entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->tree_entry.rbe_parent = parent->tree_entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->tree_entry.rbe_parent->tree_entry.rbe_left)
      {
        parent->tree_entry.rbe_parent->tree_entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->tree_entry.rbe_parent->tree_entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->tree_entry.rbe_right = &parent[parent_idx];
    parent->tree_entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->tree_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = &parent[parent_idx];
  parent_idx = &elm[elm_idx];
  elm_idx = &tmp[tmp_idx];
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct window_pane_tree
{
  struct window_pane *rbh_root;
}
----------------------------
None
----------------------------
***/


void window_pane_alternate_off(struct window_pane *wp, struct grid_cell *gc, int cursor)
{
  struct screen *s = &wp->base;
  u_int sx;
  u_int sy;
  if (wp->saved_grid == 0)
  {
    return;
  }
  if (!options_get_number(wp->window->options, "alternate-screen"))
  {
    return;
  }
  sx = s->grid->sx;
  sy = s->grid->sy;
  if (sy > wp->saved_grid->sy)
  {
    screen_resize(s, sx, wp->saved_grid->sy, 1);
  }
  grid_duplicate_lines(s->grid, s->grid->hsize, wp->saved_grid, 0, sy);
  if (cursor)
  {
    s->cx = wp->saved_cx;
  }
  if (s->cx > (s->grid->sx - 1))
  {
    s->cx = s->grid->sx - 1;
  }
  if (cursor)
  {
    s->cy = wp->saved_cy;
  }
  if (s->cy > (s->grid->sy - 1))
  {
    s->cy = s->grid->sy - 1;
  }
  memcpy(gc, &wp->saved_cell, sizeof(*gc));
  wp->base.grid->flags |= 0x1;
  if ((sy > wp->saved_grid->sy) || (sx != wp->saved_grid->sx))
  {
    screen_resize(s, sx, sy, 1);
  }
  grid_destroy(wp->saved_grid);
  wp->saved_grid = 0;
  wp->flags |= 0x1;
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
void grid_duplicate_lines(struct grid *dst, u_int dy, struct grid *src, u_int sy, u_int ny)
{
  struct grid_line *dstl;
  unsigned int dstl_idx = 0;
  struct grid_line *srcl;
  unsigned int srcl_idx = 0;
  u_int yy;
  if ((dy + ny) > (dst->hsize + dst->sy))
  {
    ny = (dst->hsize + dst->sy) - dy;
  }
  if ((sy + ny) > (src->hsize + src->sy))
  {
    ny = (src->hsize + src->sy) - sy;
  }
  grid_free_lines(dst, dy, ny);
  for (yy = 0; yy < ny; yy += 1)
  {
    srcl_idx = &src->linedata[sy];
    dstl_idx = &dst->linedata[dy];
    memcpy(dstl, srcl, sizeof(*(&dstl[dstl_idx])));
    if (srcl->cellsize != 0)
    {
      dstl->celldata = xreallocarray(0, srcl->cellsize, sizeof(*dstl->celldata));
      memcpy(dstl->celldata, srcl->celldata, srcl->cellsize * (sizeof(*dstl->celldata)));
    }
    else
      dstl->celldata = 0;
    if (srcl->extdsize != 0)
    {
      dstl->extdsize = srcl->extdsize;
      dstl->extddata = xreallocarray(0, dstl->extdsize, sizeof(*dstl->extddata));
      memcpy(dstl->extddata, srcl->extddata, dstl->extdsize * (sizeof(*dstl->extddata)));
    }
    sy += 1;
    dy += 1;
  }

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
None
----------------------------
***/


void window_pane_alternate_on(struct window_pane *wp, struct grid_cell *gc, int cursor)
{
  struct screen *s = &wp->base;
  u_int sx;
  u_int sy;
  if (wp->saved_grid != 0)
  {
    return;
  }
  if (!options_get_number(wp->window->options, "alternate-screen"))
  {
    return;
  }
  sx = s->grid->sx;
  sy = s->grid->sy;
  wp->saved_grid = grid_create(sx, sy, 0);
  grid_duplicate_lines(wp->saved_grid, 0, s->grid, s->grid->hsize, sy);
  if (cursor)
  {
    wp->saved_cx = s->cx;
    wp->saved_cy = s->cy;
  }
  memcpy(&wp->saved_cell, gc, sizeof(wp->saved_cell));
  grid_view_clear(s->grid, 0, 0, sx, sy, 8);
  wp->base.grid->flags &= ~0x1;
  wp->flags |= 0x1;
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
void grid_duplicate_lines(struct grid *dst, u_int dy, struct grid *src, u_int sy, u_int ny)
{
  struct grid_line *dstl;
  unsigned int dstl_idx = 0;
  struct grid_line *srcl;
  unsigned int srcl_idx = 0;
  u_int yy;
  if ((dy + ny) > (dst->hsize + dst->sy))
  {
    ny = (dst->hsize + dst->sy) - dy;
  }
  if ((sy + ny) > (src->hsize + src->sy))
  {
    ny = (src->hsize + src->sy) - sy;
  }
  grid_free_lines(dst, dy, ny);
  for (yy = 0; yy < ny; yy += 1)
  {
    srcl_idx = &src->linedata[sy];
    dstl_idx = &dst->linedata[dy];
    memcpy(dstl, srcl, sizeof(*(&dstl[dstl_idx])));
    if (srcl->cellsize != 0)
    {
      dstl->celldata = xreallocarray(0, srcl->cellsize, sizeof(*dstl->celldata));
      memcpy(dstl->celldata, srcl->celldata, srcl->cellsize * (sizeof(*dstl->celldata)));
    }
    else
      dstl->celldata = 0;
    if (srcl->extdsize != 0)
    {
      dstl->extdsize = srcl->extdsize;
      dstl->extddata = xreallocarray(0, dstl->extdsize, sizeof(*dstl->extddata));
      memcpy(dstl->extddata, srcl->extddata, dstl->extdsize * (sizeof(*dstl->extddata)));
    }
    sy += 1;
    dy += 1;
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


struct window *windows_RB_INSERT(struct windows *head, struct window *elm)
{
  struct window *tmp;
  unsigned int tmp_idx = 0;
  struct window *parent = 0;
  unsigned int parent_idx = 0;
  int comp = 0;
  tmp_idx = head->rbh_root;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    comp = window_cmp(elm, parent);
    if (comp < 0)
    {
      tmp_idx = tmp_idx->entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->entry.rbe_right;
    }
    else
      return tmp;
  }

  do
  {
    elm->entry.rbe_parent = &parent[parent_idx];
    elm->entry.rbe_left = (elm->entry.rbe_right = 0);
    elm->entry.rbe_color = 1;
  }
  while (0);
  if ((&parent[parent_idx]) != 0)
  {
    if (comp < 0)
    {
      parent->entry.rbe_left = elm;
    }
    else
      parent->entry.rbe_right = elm;
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = elm;
  windows_RB_INSERT_COLOR(head, elm);
  return 0;
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
int window_cmp(struct window *w1, struct window *w2)
{
  return w1->id - w2->id;
}


----------------------------
void windows_RB_INSERT_COLOR(struct windows *head, struct window *elm)
{
  unsigned int elm_idx = 0;
  struct window *parent;
  unsigned int parent_idx = 0;
  struct window *gparent;
  unsigned int gparent_idx = 0;
  struct window *tmp;
  unsigned int tmp_idx = 0;
  while ((parent_idx = elm->entry.rbe_parent) && (parent->entry.rbe_color == 1))
  {
    helper_windows_RB_INSERT_COLOR_1(&elm_idx, &parent_idx, &gparent_idx, &tmp_idx, head, elm, parent, gparent, tmp);
  }

  head->rbh_root->entry.rbe_color = 0;
}


----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_window_pane_tree_RB_INSERT_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const elm, struct window_pane * const parent, struct window_pane * const gparent, struct window_pane * const tmp, unsigned int gparent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->tree_entry.rbe_left;
  if ((&tmp[tmp_idx]) && (tmp->tree_entry.rbe_color == 1))
  {
    tmp->tree_entry.rbe_color = 0;
    do
    {
      parent->tree_entry.rbe_color = 0;
      gparent->tree_entry.rbe_color = 1;
    }
    while (0);
    elm_idx = &gparent[gparent_idx];
    continue;
  }
  if (parent->tree_entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_helper_window_pane_tree_RB_INSERT_COLOR_1_2_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->tree_entry.rbe_color = 0;
    gparent->tree_entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_window_pane_tree_RB_INSERT_COLOR_1_2_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct window_pane_tree
{
  struct window_pane *rbh_root;
}
----------------------------
void helper_helper_helper_window_pane_tree_RB_INSERT_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const gparent, struct window_pane * const tmp, unsigned int gparent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->tree_entry.rbe_right;
  if (gparent->tree_entry.rbe_right = tmp->tree_entry.rbe_left)
  {
    tmp->tree_entry.rbe_left->tree_entry.rbe_parent = &gparent[gparent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->tree_entry.rbe_parent = gparent->tree_entry.rbe_parent)
  {
    if ((&gparent[gparent_idx]) == gparent->tree_entry.rbe_parent->tree_entry.rbe_left)
    {
      gparent->tree_entry.rbe_parent->tree_entry.rbe_left = &tmp[tmp_idx];
    }
    else
      gparent->tree_entry.rbe_parent->tree_entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->tree_entry.rbe_left = &gparent[gparent_idx];
  gparent->tree_entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->tree_entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_helper_window_pane_tree_RB_INSERT_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const elm, struct window_pane * const parent, struct window_pane * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp_idx = parent->tree_entry.rbe_left;
    if (parent->tree_entry.rbe_left = tmp->tree_entry.rbe_right)
    {
      tmp->tree_entry.rbe_right->tree_entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->tree_entry.rbe_parent = parent->tree_entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->tree_entry.rbe_parent->tree_entry.rbe_left)
      {
        parent->tree_entry.rbe_parent->tree_entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->tree_entry.rbe_parent->tree_entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->tree_entry.rbe_right = &parent[parent_idx];
    parent->tree_entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->tree_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = &parent[parent_idx];
  parent_idx = &elm[elm_idx];
  elm_idx = &tmp[tmp_idx];
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_window_pane_tree_RB_INSERT_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const elm, struct window_pane * const parent, struct window_pane * const gparent, struct window_pane * const tmp, unsigned int gparent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->tree_entry.rbe_right;
  if ((&tmp[tmp_idx]) && (tmp->tree_entry.rbe_color == 1))
  {
    tmp->tree_entry.rbe_color = 0;
    do
    {
      parent->tree_entry.rbe_color = 0;
      gparent->tree_entry.rbe_color = 1;
    }
    while (0);
    elm_idx = &gparent[gparent_idx];
    continue;
  }
  if (parent->tree_entry.rbe_right == (&elm[elm_idx]))
  {
    helper_helper_helper_window_pane_tree_RB_INSERT_COLOR_1_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->tree_entry.rbe_color = 0;
    gparent->tree_entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_window_pane_tree_RB_INSERT_COLOR_1_1_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct window_pane_tree
{
  struct window_pane *rbh_root;
}
----------------------------
void helper_helper_helper_window_pane_tree_RB_INSERT_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const gparent, struct window_pane * const tmp, unsigned int gparent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->tree_entry.rbe_left;
  if (gparent->tree_entry.rbe_left = tmp->tree_entry.rbe_right)
  {
    tmp->tree_entry.rbe_right->tree_entry.rbe_parent = &gparent[gparent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->tree_entry.rbe_parent = gparent->tree_entry.rbe_parent)
  {
    if ((&gparent[gparent_idx]) == gparent->tree_entry.rbe_parent->tree_entry.rbe_left)
    {
      gparent->tree_entry.rbe_parent->tree_entry.rbe_left = &tmp[tmp_idx];
    }
    else
      gparent->tree_entry.rbe_parent->tree_entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->tree_entry.rbe_right = &gparent[gparent_idx];
  gparent->tree_entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->tree_entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_helper_window_pane_tree_RB_INSERT_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const elm, struct window_pane * const parent, struct window_pane * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp_idx = parent->tree_entry.rbe_right;
    if (parent->tree_entry.rbe_right = tmp->tree_entry.rbe_left)
    {
      tmp->tree_entry.rbe_left->tree_entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->tree_entry.rbe_parent = parent->tree_entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->tree_entry.rbe_parent->tree_entry.rbe_left)
      {
        parent->tree_entry.rbe_parent->tree_entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->tree_entry.rbe_parent->tree_entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->tree_entry.rbe_left = &parent[parent_idx];
    parent->tree_entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->tree_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = &parent[parent_idx];
  parent_idx = &elm[elm_idx];
  elm_idx = &tmp[tmp_idx];
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'gparent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_window_pane_tree_RB_INSERT_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const gparent_idx_ref, unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const elm, struct window_pane * const parent, struct window_pane * const gparent, struct window_pane * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int gparent_idx = *gparent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  gparent_idx = parent->tree_entry.rbe_parent;
  if ((&parent[parent_idx]) == gparent->tree_entry.rbe_left)
  {
    helper_helper_window_pane_tree_RB_INSERT_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  else
  {
    helper_helper_window_pane_tree_RB_INSERT_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *gparent_idx_ref = gparent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct window_pane_tree
{
  struct window_pane *rbh_root;
}
----------------------------
void helper_helper_window_pane_tree_RB_INSERT_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const elm, struct window_pane * const parent, struct window_pane * const gparent, struct window_pane * const tmp, unsigned int gparent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->tree_entry.rbe_left;
  if ((&tmp[tmp_idx]) && (tmp->tree_entry.rbe_color == 1))
  {
    tmp->tree_entry.rbe_color = 0;
    do
    {
      parent->tree_entry.rbe_color = 0;
      gparent->tree_entry.rbe_color = 1;
    }
    while (0);
    elm_idx = &gparent[gparent_idx];
    continue;
  }
  if (parent->tree_entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_helper_window_pane_tree_RB_INSERT_COLOR_1_2_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->tree_entry.rbe_color = 0;
    gparent->tree_entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_window_pane_tree_RB_INSERT_COLOR_1_2_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_window_pane_tree_RB_INSERT_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const elm, struct window_pane * const parent, struct window_pane * const gparent, struct window_pane * const tmp, unsigned int gparent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->tree_entry.rbe_right;
  if ((&tmp[tmp_idx]) && (tmp->tree_entry.rbe_color == 1))
  {
    tmp->tree_entry.rbe_color = 0;
    do
    {
      parent->tree_entry.rbe_color = 0;
      gparent->tree_entry.rbe_color = 1;
    }
    while (0);
    elm_idx = &gparent[gparent_idx];
    continue;
  }
  if (parent->tree_entry.rbe_right == (&elm[elm_idx]))
  {
    helper_helper_helper_window_pane_tree_RB_INSERT_COLOR_1_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->tree_entry.rbe_color = 0;
    gparent->tree_entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_window_pane_tree_RB_INSERT_COLOR_1_1_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


void window_pane_tree_RB_INSERT_COLOR(struct window_pane_tree *head, struct window_pane *elm)
{
  unsigned int elm_idx = 0;
  struct window_pane *parent;
  unsigned int parent_idx = 0;
  struct window_pane *gparent;
  unsigned int gparent_idx = 0;
  struct window_pane *tmp;
  unsigned int tmp_idx = 0;
  while ((parent_idx = elm->tree_entry.rbe_parent) && (parent->tree_entry.rbe_color == 1))
  {
    helper_window_pane_tree_RB_INSERT_COLOR_1(&elm_idx, &parent_idx, &gparent_idx, &tmp_idx, head, elm, parent, gparent, tmp);
  }

  head->rbh_root->tree_entry.rbe_color = 0;
}


/*** DEPENDENCIES:
struct window_pane_tree
{
  struct window_pane *rbh_root;
}
----------------------------
void helper_window_pane_tree_RB_INSERT_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const gparent_idx_ref, unsigned int * const tmp_idx_ref, struct window_pane_tree * const head, struct window_pane * const elm, struct window_pane * const parent, struct window_pane * const gparent, struct window_pane * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int gparent_idx = *gparent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  gparent_idx = parent->tree_entry.rbe_parent;
  if ((&parent[parent_idx]) == gparent->tree_entry.rbe_left)
  {
    helper_helper_window_pane_tree_RB_INSERT_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  else
  {
    helper_helper_window_pane_tree_RB_INSERT_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *gparent_idx_ref = gparent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


struct window_pane *window_pane_tree_RB_NFIND(struct window_pane_tree *head, struct window_pane *elm)
{
  struct window_pane *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct window_pane *res = 0;
  unsigned int res_idx = 0;
  int comp;
  while (tmp)
  {
    comp = window_pane_cmp(elm, tmp);
    if (comp < 0)
    {
      res_idx = &tmp[tmp_idx];
      tmp_idx = tmp_idx->tree_entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->tree_entry.rbe_right;
    }
    else
      return tmp;
  }

  return res;
}


/*** DEPENDENCIES:
struct window_pane_tree
{
  struct window_pane *rbh_root;
}
----------------------------
int window_pane_cmp(struct window_pane *wp1, struct window_pane *wp2)
{
  return wp1->id - wp2->id;
}


----------------------------
None
----------------------------
***/


static void window_pane_read_callback(struct bufferevent *bufev, void *data)
{
  struct window_pane *wp = data;
  struct evbuffer *evb = wp->event->input;
  size_t size = EVBUFFER_LENGTH(evb);
  char *new_data;
  unsigned int new_data_idx = 0;
  size_t new_size;
  new_size = size - wp->pipe_off;
  if ((wp->pipe_fd != (-1)) && (new_size > 0))
  {
    new_data_idx = EVBUFFER_DATA(evb) + wp->pipe_off;
    bufferevent_write(wp->pipe_event, new_data, new_size);
  }
  log_debug("%%%u has %zu bytes", wp->id, size);
  input_parse(wp);
  wp->pipe_off = EVBUFFER_LENGTH(evb);
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
void input_parse(struct window_pane *wp)
{
  struct input_ctx *ictx = wp->ictx;
  const struct input_transition *itr;
  unsigned int itr_idx = 0;
  struct evbuffer *evb = wp->event->input;
  u_char *buf;
  unsigned int buf_idx = 0;
  size_t len;
  size_t off;
  if (EVBUFFER_LENGTH(evb) == 0)
  {
    return;
  }
  window_update_activity(wp->window);
  wp->flags |= 0x80;
  if (wp->mode == 0)
  {
    screen_write_start(&ictx->ctx, wp, &wp->base);
  }
  else
    screen_write_start(&ictx->ctx, 0, &wp->base);
  ictx->wp = wp;
  buf_idx = EVBUFFER_DATA(evb);
  len = EVBUFFER_LENGTH(evb);
  off = 0;
  notify_input(wp, evb);
  log_debug("%s: %%%u %s, %zu bytes: %.*s", __func__, wp->id, ictx->state->name, len, (int) len, buf);
  while (off < len)
  {
    helper_input_parse_1(&itr_idx, &off, wp, ictx, itr, buf, buf_idx);
  }

  screen_write_stop(&ictx->ctx);
  evbuffer_drain(evb, len);
}


----------------------------
None
----------------------------
***/


struct window_pane *window_pane_tree_RB_INSERT(struct window_pane_tree *head, struct window_pane *elm)
{
  struct window_pane *tmp;
  unsigned int tmp_idx = 0;
  struct window_pane *parent = 0;
  unsigned int parent_idx = 0;
  int comp = 0;
  tmp_idx = head->rbh_root;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    comp = window_pane_cmp(elm, parent);
    if (comp < 0)
    {
      tmp_idx = tmp_idx->tree_entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->tree_entry.rbe_right;
    }
    else
      return tmp;
  }

  do
  {
    elm->tree_entry.rbe_parent = &parent[parent_idx];
    elm->tree_entry.rbe_left = (elm->tree_entry.rbe_right = 0);
    elm->tree_entry.rbe_color = 1;
  }
  while (0);
  if ((&parent[parent_idx]) != 0)
  {
    if (comp < 0)
    {
      parent->tree_entry.rbe_left = elm;
    }
    else
      parent->tree_entry.rbe_right = elm;
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = elm;
  window_pane_tree_RB_INSERT_COLOR(head, elm);
  return 0;
}


/*** DEPENDENCIES:
struct window_pane_tree
{
  struct window_pane *rbh_root;
}
----------------------------
int window_pane_cmp(struct window_pane *wp1, struct window_pane *wp2)
{
  return wp1->id - wp2->id;
}


----------------------------
void window_pane_tree_RB_INSERT_COLOR(struct window_pane_tree *head, struct window_pane *elm)
{
  unsigned int elm_idx = 0;
  struct window_pane *parent;
  unsigned int parent_idx = 0;
  struct window_pane *gparent;
  unsigned int gparent_idx = 0;
  struct window_pane *tmp;
  unsigned int tmp_idx = 0;
  while ((parent_idx = elm->tree_entry.rbe_parent) && (parent->tree_entry.rbe_color == 1))
  {
    helper_window_pane_tree_RB_INSERT_COLOR_1(&elm_idx, &parent_idx, &gparent_idx, &tmp_idx, head, elm, parent, gparent, tmp);
  }

  head->rbh_root->tree_entry.rbe_color = 0;
}


----------------------------
None
----------------------------
***/


static void window_pane_error_callback(struct bufferevent *bufev, short what, void *data)
{
  struct window_pane *wp = data;
  log_debug("%%%u error", wp->id);
  wp->flags |= 0x100;
  if (window_pane_destroy_ready(wp))
  {
    server_destroy_pane(wp, 1);
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
int window_pane_destroy_ready(struct window_pane *wp)
{
  int n;
  if (wp->pipe_fd != (-1))
  {
    if (EVBUFFER_LENGTH(wp->pipe_event->output) != 0)
    {
      return 0;
    }
    if ((ioctl(wp->fd, FIONREAD, &n) != (-1)) && (n > 0))
    {
      return 0;
    }
  }
  if ((~wp->flags) & 0x100)
  {
    return 0;
  }
  return 1;
}


----------------------------
void server_destroy_pane(struct window_pane *wp, int notify)
{
  struct window *w = wp->window;
  struct screen_write_ctx ctx;
  struct grid_cell gc;
  time_t t;
  char tim[26];
  if (wp->fd != (-1))
  {
    bufferevent_free(wp->event);
    close(wp->fd);
    wp->fd = -1;
  }
  if (options_get_number(w->options, "remain-on-exit"))
  {
    helper_server_destroy_pane_1(wp, notify, ctx, gc, t, tim);
  }
  if (notify)
  {
    notify_pane("pane-exited", wp);
  }
  server_unzoom_window(w);
  layout_close_pane(wp);
  window_remove_pane(w, wp);
  if ((&w->panes)->tqh_first == 0)
  {
    server_kill_window(w);
  }
  else
    server_redraw_window(w);
}


----------------------------
None
----------------------------
***/


static struct window_pane *window_pane_create(struct window *w, u_int sx, u_int sy, u_int hlimit)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  char host[255 + 1];
  wp_idx = xcalloc(1, sizeof(*wp_idx));
  wp->window = w;
  wp->id = next_window_pane_id;
  next_window_pane_id += 1;
  window_pane_tree_RB_INSERT(&all_window_panes, wp);
  wp->argc = 0;
  wp->argv = 0;
  wp->shell = 0;
  wp->cwd = 0;
  wp->fd = -1;
  wp->event = 0;
  wp->mode = 0;
  wp->modeprefix = 1;
  wp->layout_cell = 0;
  wp->xoff = 0;
  wp->yoff = 0;
  wp->sx = (wp->osx = sx);
  wp->sy = (wp->osx = sy);
  wp->pipe_fd = -1;
  wp->pipe_off = 0;
  wp->pipe_event = 0;
  wp->saved_grid = 0;
  memcpy(&wp->colgc, &grid_default_cell, sizeof(wp->colgc));
  screen_init(&wp->base, sx, sy, hlimit);
  wp->screen = &wp->base;
  screen_init(&wp->status_screen, 1, 1, 0);
  if (gethostname(host, sizeof(host)) == 0)
  {
    screen_set_title(&wp->base, host);
  }
  input_init(wp);
  return wp;
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
static u_int next_window_pane_id
----------------------------
void screen_set_title(struct screen *s, const char *title)
{
  free(s->title);
  utf8_stravis(&s->title, title, ((0x01 | 0x02) | 0x08) | 0x10);
}


----------------------------
void input_init(struct window_pane *wp)
{
  struct input_ctx *ictx;
  unsigned int ictx_idx = 0;
  ictx_idx = (wp->ictx_idx = xcalloc(1, sizeof(*ictx_idx)));
  ictx->input_space = 32;
  ictx->input_buf = xmalloc(32);
  ictx->since_ground = evbuffer_new();
  evtimer_set(&ictx->timer, input_timer_callback, ictx);
  input_reset(wp, 0);
}


----------------------------
struct window_pane *window_pane_tree_RB_INSERT(struct window_pane_tree *head, struct window_pane *elm)
{
  struct window_pane *tmp;
  unsigned int tmp_idx = 0;
  struct window_pane *parent = 0;
  unsigned int parent_idx = 0;
  int comp = 0;
  tmp_idx = head->rbh_root;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    comp = window_pane_cmp(elm, parent);
    if (comp < 0)
    {
      tmp_idx = tmp_idx->tree_entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->tree_entry.rbe_right;
    }
    else
      return tmp;
  }

  do
  {
    elm->tree_entry.rbe_parent = &parent[parent_idx];
    elm->tree_entry.rbe_left = (elm->tree_entry.rbe_right = 0);
    elm->tree_entry.rbe_color = 1;
  }
  while (0);
  if ((&parent[parent_idx]) != 0)
  {
    if (comp < 0)
    {
      parent->tree_entry.rbe_left = elm;
    }
    else
      parent->tree_entry.rbe_right = elm;
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = elm;
  window_pane_tree_RB_INSERT_COLOR(head, elm);
  return 0;
}


----------------------------
extern struct window_pane_tree all_window_panes
----------------------------
None
----------------------------
***/


struct window_pane *window_add_pane(struct window *w, struct window_pane *other, int before, int full_size, u_int hlimit)
{
  unsigned int other_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  if ((&other[other_idx]) == 0)
  {
    other_idx = w->active;
  }
  wp_idx = window_pane_create(w, w->sx, w->sy, hlimit);
  if ((&w->panes)->tqh_first == 0)
  {
    log_debug("%s: @%u at start", __func__, w->id);
    do
    {
      if ((wp->entry.tqe_next = (&w->panes)->tqh_first) != 0)
      {
        (&w->panes)->tqh_first->entry.tqe_prev = &wp->entry.tqe_next;
      }
      else
        (&w->panes)->tqh_last = &wp->entry.tqe_next;
      (&w->panes)->tqh_first = &wp[wp_idx];
      wp->entry.tqe_prev = &(&w->panes)->tqh_first;
    }
    while (0);
  }
  else
    if (before)
  {
    helper_window_add_pane_1(w, other, full_size, other_idx, wp, wp_idx);
  }
  else
  {
    helper_window_add_pane_2(w, other, full_size, wp, wp_idx);
  }
  return wp;
}


/*** DEPENDENCIES:
void helper_window_add_pane_2(struct window * const w, struct window_pane * const other, int full_size, struct window_pane * const wp, unsigned int wp_idx)
{
  log_debug("%s: @%u after %%%u", __func__, w->id, wp->id);
  if (full_size)
  {
    do
    {
      wp->entry.tqe_next = 0;
      wp->entry.tqe_prev = (&w->panes)->tqh_last;
      *(&w->panes)->tqh_last = &wp[wp_idx];
      (&w->panes)->tqh_last = &wp->entry.tqe_next;
    }
    while (0);
  }
  else
    do
  {
    if ((wp->entry.tqe_next = other->entry.tqe_next) != 0)
    {
      wp->entry.tqe_next->entry.tqe_prev = &wp->entry.tqe_next;
    }
    else
      (&w->panes)->tqh_last = &wp->entry.tqe_next;
    other->entry.tqe_next = &wp[wp_idx];
    wp->entry.tqe_prev = &other->entry.tqe_next;
  }
  while (0);
}


----------------------------
void helper_window_add_pane_1(struct window * const w, struct window_pane * const other, int full_size, unsigned int other_idx, struct window_pane * const wp, unsigned int wp_idx)
{
  log_debug("%s: @%u before %%%u", __func__, w->id, wp->id);
  if (full_size)
  {
    do
    {
      if ((wp->entry.tqe_next = (&w->panes)->tqh_first) != 0)
      {
        (&w->panes)->tqh_first->entry.tqe_prev = &wp->entry.tqe_next;
      }
      else
        (&w->panes)->tqh_last = &wp->entry.tqe_next;
      (&w->panes)->tqh_first = &wp[wp_idx];
      wp->entry.tqe_prev = &(&w->panes)->tqh_first;
    }
    while (0);
  }
  else
    do
  {
    wp->entry.tqe_prev = other->entry.tqe_prev;
    wp->entry.tqe_next = &other[other_idx];
    *other->entry.tqe_prev = &wp[wp_idx];
    other->entry.tqe_prev = &wp->entry.tqe_next;
  }
  while (0);
}


----------------------------
static struct window_pane *window_pane_create(struct window *w, u_int sx, u_int sy, u_int hlimit)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  char host[255 + 1];
  wp_idx = xcalloc(1, sizeof(*wp_idx));
  wp->window = w;
  wp->id = next_window_pane_id;
  next_window_pane_id += 1;
  window_pane_tree_RB_INSERT(&all_window_panes, wp);
  wp->argc = 0;
  wp->argv = 0;
  wp->shell = 0;
  wp->cwd = 0;
  wp->fd = -1;
  wp->event = 0;
  wp->mode = 0;
  wp->modeprefix = 1;
  wp->layout_cell = 0;
  wp->xoff = 0;
  wp->yoff = 0;
  wp->sx = (wp->osx = sx);
  wp->sy = (wp->osx = sy);
  wp->pipe_fd = -1;
  wp->pipe_off = 0;
  wp->pipe_event = 0;
  wp->saved_grid = 0;
  memcpy(&wp->colgc, &grid_default_cell, sizeof(wp->colgc));
  screen_init(&wp->base, sx, sy, hlimit);
  wp->screen = &wp->base;
  screen_init(&wp->status_screen, 1, 1, 0);
  if (gethostname(host, sizeof(host)) == 0)
  {
    screen_set_title(&wp->base, host);
  }
  input_init(wp);
  return wp;
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


int winlink_shuffle_up(struct session *s, struct winlink *wl)
{
  unsigned int wl_idx = 0;
  int idx;
  int last;
  idx = wl->idx + 1;
  for (last = idx; last < 2147483647; last += 1)
  {
    if (winlink_find_by_index(&s->windows, last) == 0)
    {
      break;
    }
  }

  if (last == 2147483647)
  {
    return -1;
  }
  for (; last > idx; last -= 1)
  {
    wl_idx = winlink_find_by_index(&s->windows, last - 1);
    server_link_window(s, wl, s, last, 0, 0, 0);
    server_unlink_window(s, wl);
  }

  return idx;
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
void server_unlink_window(struct session *s, struct winlink *wl)
{
  if (session_detach(s, wl))
  {
    server_destroy_session_group(s);
  }
  else
    server_redraw_session_group(s);
}


----------------------------
struct winlink *winlink_find_by_index(struct winlinks *wwl, int idx)
{
  struct winlink wl;
  if (idx < 0)
  {
    fatalx("bad index");
  }
  wl.idx = idx;
  return winlinks_RB_FIND(wwl, &wl);
}


----------------------------
int server_link_window(struct session *src, struct winlink *srcwl, struct session *dst, int dstidx, int killflag, int selectflag, char **cause)
{
  struct winlink *dstwl;
  unsigned int dstwl_idx = 0;
  struct session_group *srcsg;
  unsigned int srcsg_idx = 0;
  struct session_group *dstsg;
  unsigned int dstsg_idx = 0;
  srcsg_idx = session_group_contains(src);
  dstsg_idx = session_group_contains(dst);
  if ((((src != dst) && ((&srcsg[srcsg_idx]) != 0)) && ((&dstsg[dstsg_idx]) != 0)) && ((&srcsg[srcsg_idx]) == (&dstsg[dstsg_idx])))
  {
    xasprintf(cause, "sessions are grouped");
    return -1;
  }
  dstwl_idx = 0;
  if (dstidx != (-1))
  {
    dstwl_idx = winlink_find_by_index(&dst->windows, dstidx);
  }
  if ((&dstwl[dstwl_idx]) != 0)
  {
    helper_server_link_window_1(&selectflag, srcwl, dst, dstidx, killflag, cause, dstwl, dstwl_idx);
  }
  if (dstidx == (-1))
  {
    dstidx = (-1) - options_get_number(dst->options, "base-index");
  }
  dstwl_idx = session_attach(dst, srcwl->window, dstidx, cause);
  if ((&dstwl[dstwl_idx]) == 0)
  {
    return -1;
  }
  if (selectflag)
  {
    session_select(dst, dstwl->idx);
  }
  server_redraw_session_group(dst);
  return 0;
}


----------------------------
None
----------------------------
***/


struct window *window_create(u_int sx, u_int sy)
{
  struct window *w;
  unsigned int w_idx = 0;
  w_idx = xcalloc(1, sizeof(*w_idx));
  w->name = 0;
  w->flags = 0x8000;
  do
  {
    (&w->panes)->tqh_first = 0;
    (&w->panes)->tqh_last = &(&w->panes)->tqh_first;
  }
  while (0);
  w->active = 0;
  w->lastlayout = -1;
  w->layout_root = 0;
  w->sx = sx;
  w->sy = sy;
  w->options = options_create(global_w_options);
  w->references = 0;
  do
  {
    (&w->winlinks)->tqh_first = 0;
    (&w->winlinks)->tqh_last = &(&w->winlinks)->tqh_first;
  }
  while (0);
  w->id = next_window_id;
  next_window_id += 1;
  windows_RB_INSERT(&windows, w);
  window_update_activity(w);
  return w;
}


/*** DEPENDENCIES:
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
struct windows
{
  struct window *rbh_root;
}
----------------------------
static u_int next_window_id
----------------------------
struct window *windows_RB_INSERT(struct windows *head, struct window *elm)
{
  struct window *tmp;
  unsigned int tmp_idx = 0;
  struct window *parent = 0;
  unsigned int parent_idx = 0;
  int comp = 0;
  tmp_idx = head->rbh_root;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    comp = window_cmp(elm, parent);
    if (comp < 0)
    {
      tmp_idx = tmp_idx->entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->entry.rbe_right;
    }
    else
      return tmp;
  }

  do
  {
    elm->entry.rbe_parent = &parent[parent_idx];
    elm->entry.rbe_left = (elm->entry.rbe_right = 0);
    elm->entry.rbe_color = 1;
  }
  while (0);
  if ((&parent[parent_idx]) != 0)
  {
    if (comp < 0)
    {
      parent->entry.rbe_left = elm;
    }
    else
      parent->entry.rbe_right = elm;
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = elm;
  windows_RB_INSERT_COLOR(head, elm);
  return 0;
}


----------------------------
struct options *options_create(struct options *parent)
{
  struct options *oo;
  unsigned int oo_idx = 0;
  oo_idx = xcalloc(1, sizeof(*oo_idx));
  do
  {
    (&oo->tree)->rbh_root = 0;
  }
  while (0);
  oo->parent = parent;
  return oo;
}


----------------------------
void window_update_activity(struct window *w)
{
  gettimeofday(&w->activity_time, 0);
  alerts_queue(w, 0x2);
}


----------------------------
None
----------------------------
***/


void window_redraw_active_switch(struct window *w, struct window_pane *wp)
{
  const struct grid_cell *gc;
  unsigned int gc_idx = 0;
  if (wp == w->active)
  {
    return;
  }
  gc_idx = options_get_style(w->options, "window-active-style");
  if (style_equal(gc, options_get_style(w->options, "window-style")))
  {
    return;
  }
  if (((window_pane_get_palette(w->active, w->active->colgc.fg) != (-1)) || (window_pane_get_palette(w->active, w->active->colgc.bg) != (-1))) || style_equal(&grid_default_cell, &w->active->colgc))
  {
    w->active->flags |= 0x1;
  }
  if (((window_pane_get_palette(wp, wp->colgc.fg) != (-1)) || (window_pane_get_palette(wp, wp->colgc.bg) != (-1))) || style_equal(&grid_default_cell, &wp->colgc))
  {
    wp->flags |= 0x1;
  }
}


/*** DEPENDENCIES:
extern const struct grid_cell grid_default_cell
----------------------------
const struct grid_cell *options_get_style(struct options *oo, const char *name)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_get(oo, name);
  if ((&o[o_idx]) == 0)
  {
    fatalx("missing option %s", name);
  }
  if (!((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_STYLE)))
  {
    fatalx("option %s is not a style", name);
  }
  return &o->style;
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
int window_pane_get_palette(const struct window_pane *wp, int c)
{
  int new;
  if ((wp == 0) || (wp->palette == 0))
  {
    return -1;
  }
  new = -1;
  if (c < 8)
  {
    new = wp->palette[c];
  }
  else
    if ((c >= 90) && (c <= 97))
  {
    new = wp->palette[(8 + c) - 90];
  }
  else
    if (c & 0x01000000)
  {
    new = wp->palette[c & (~0x01000000)];
  }
  if (new == 0)
  {
    return -1;
  }
  return new;
}


----------------------------
None
----------------------------
int style_equal(const struct grid_cell *gc1, const struct grid_cell *gc2)
{
  return (((gc1->fg == gc2->fg) && (gc1->bg == gc2->bg)) && ((gc1->flags & (~0x4)) == (gc2->flags & (~0x4)))) && ((gc1->attr & (~0x80)) == (gc2->attr & (~0x80)));
}


----------------------------
None
----------------------------
***/


// hint:  ['cwd_idx_ref is a mutable refrence to unsigned int', 'argvp_idx_ref is a mutable refrence to unsigned int', 'ptr_idx_ref is a mutable refrence to unsigned int', 'first_idx_ref is a mutable refrence to unsigned int', 'home_idx_ref is a mutable refrence to unsigned int', 'tio2_ref is a mutable refrence to ']
void helper_window_pane_spawn_1(unsigned int * const cwd_idx_ref, unsigned int * const argvp_idx_ref, unsigned int * const ptr_idx_ref, unsigned int * const first_idx_ref, unsigned int * const home_idx_ref, struct termios * const tio2_ref, struct window_pane * const wp, const char * const path, const char * const cwd, struct environ * const env, struct termios * const tio, char * const argv0, char ** const argvp, const char * const ptr, const char * const first, const char * const home, sigset_t oldset)
{
  unsigned int cwd_idx = *cwd_idx_ref;
  unsigned int argvp_idx = *argvp_idx_ref;
  unsigned int ptr_idx = *ptr_idx_ref;
  unsigned int first_idx = *first_idx_ref;
  unsigned int home_idx = *home_idx_ref;
  struct termios tio2 = *tio2_ref;
  proc_clear_signals(server_proc, 1);
  sigprocmask(SIG_SETMASK, &oldset, 0);
  cwd_idx = 0;
  if (chdir(wp->cwd) == 0)
  {
    cwd_idx = wp->cwd_idx;
  }
  else
    if (((home_idx = find_home()) != 0) && (chdir(home) == 0))
  {
    cwd_idx = &home[home_idx];
  }
  else
    chdir("/");
  if (tcgetattr(STDIN_FILENO, &tio2) != 0)
  {
    fatal("tcgetattr failed");
  }
  if (tio != 0)
  {
    memcpy(tio2.c_cc, tio->c_cc, sizeof(tio2.c_cc));
  }
  tio2.c_cc[VERASE] = '\177';
  if (tcsetattr(STDIN_FILENO, TCSANOW, &tio2) != 0)
  {
    fatal("tcgetattr failed");
  }
  log_close();
  closefrom(STDERR_FILENO + 1);
  if (path != 0)
  {
    environ_set(env, "PATH", "%s", path);
  }
  if ((&cwd[cwd_idx]) != 0)
  {
    environ_set(env, "PWD", "%s", cwd);
  }
  environ_set(env, "TMUX_PANE", "%%%u", wp->id);
  environ_push(env);
  setenv("SHELL", wp->shell, 1);
  ptr_idx = strrchr(wp->shell, '/');
  if (wp->argc > 0)
  {
    if (wp->argc != 1)
    {
      argvp_idx = cmd_copy_argv(wp->argc, wp->argv);
      execvp(argvp[0 + argvp_idx], argvp);
      fatal("execvp failed");
    }
    first_idx = wp->argv[0];
    if (((&ptr[ptr_idx]) != 0) && ((*((&ptr[ptr_idx]) + 1)) != '\0'))
    {
      xasprintf(&argv0, "%s", (&ptr[ptr_idx]) + 1);
    }
    else
      xasprintf(&argv0, "%s", wp->shell);
    execl(wp->shell, argv0, "-c", first, (char *) 0);
    fatal("execl failed");
  }
  if (((&ptr[ptr_idx]) != 0) && ((*((&ptr[ptr_idx]) + 1)) != '\0'))
  {
    xasprintf(&argv0, "-%s", (&ptr[ptr_idx]) + 1);
  }
  else
    xasprintf(&argv0, "-%s", wp->shell);
  execl(wp->shell, argv0, (char *) 0);
  fatal("execl failed");
  *cwd_idx_ref = cwd_idx;
  *argvp_idx_ref = argvp_idx;
  *ptr_idx_ref = ptr_idx;
  *first_idx_ref = first_idx;
  *home_idx_ref = home_idx;
  *tio2_ref = tio2;
}


/*** DEPENDENCIES:
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
void environ_push(struct environ *env)
{
  struct environ_entry *envent;
  unsigned int envent_idx = 0;
  environ = xcalloc(1, sizeof(*environ));
  for (envent_idx = environ_RB_MINMAX(env, -1); (&envent[envent_idx]) != 0; envent_idx = environ_RB_NEXT(envent_idx))
  {
    if ((envent->value != 0) && ((*envent->name) != '\0'))
    {
      setenv(envent->name, envent->value, 1);
    }
  }

}


----------------------------
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
void environ_set(struct environ *env, const char *name, const char *fmt, ...)
{
  struct environ_entry *envent;
  unsigned int envent_idx = 0;
  va_list ap;
  __builtin_va_start(ap);
  if ((envent_idx = environ_find(env, name)) != 0)
  {
    free(envent->value);
    xvasprintf(&envent->value, fmt, ap);
  }
  else
  {
    envent_idx = xmalloc(sizeof(*envent_idx));
    envent->name = xstrdup(name);
    xvasprintf(&envent->value, fmt, ap);
    environ_RB_INSERT(env, envent);
  }
  ;
}


----------------------------
void proc_clear_signals(struct tmuxproc *tp, int defaults)
{
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  sa.sa_handler = SIG_DFL;
  sigaction(SIGINT, &sa, 0);
  sigaction(SIGPIPE, &sa, 0);
  sigaction(SIGTSTP, &sa, 0);
  signal_del(&tp->ev_sighup);
  signal_del(&tp->ev_sigchld);
  signal_del(&tp->ev_sigcont);
  signal_del(&tp->ev_sigterm);
  signal_del(&tp->ev_sigusr1);
  signal_del(&tp->ev_sigusr2);
  signal_del(&tp->ev_sigwinch);
  if (defaults)
  {
    sigaction(SIGHUP, &sa, 0);
    sigaction(SIGCHLD, &sa, 0);
    sigaction(SIGCONT, &sa, 0);
    sigaction(SIGTERM, &sa, 0);
    sigaction(SIGUSR1, &sa, 0);
    sigaction(SIGUSR2, &sa, 0);
    sigaction(SIGWINCH, &sa, 0);
  }
}


----------------------------
void log_close(void)
{
  if (log_file != 0)
  {
    fclose(log_file);
  }
  log_file = 0;
  event_set_log_callback(0);
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
char **cmd_copy_argv(int argc, char **argv)
{
  char **new_argv;
  unsigned int new_argv_idx = 0;
  int i;
  if (argc == 0)
  {
    return 0;
  }
  new_argv_idx = xcalloc(argc + 1, sizeof(*new_argv_idx));
  for (i = 0; i < argc; i += 1)
  {
    if (argv[i] != 0)
    {
      new_argv[i + new_argv_idx] = xstrdup(argv[i]);
    }
  }

  return new_argv;
}


----------------------------
None
----------------------------
None
----------------------------
***/


int window_pane_spawn(struct window_pane *wp, int argc, char **argv, const char *path, const char *shell, const char *cwd, struct environ *env, struct termios *tio, char **cause)
{
  unsigned int cwd_idx = 0;
  struct winsize ws;
  char *argv0;
  char *cmd;
  unsigned int cmd_idx = 0;
  char **argvp;
  unsigned int argvp_idx = 0;
  const char *ptr;
  unsigned int ptr_idx = 0;
  const char *first;
  unsigned int first_idx = 0;
  const char *home;
  unsigned int home_idx = 0;
  struct termios tio2;
  int i;
  sigset_t set;
  sigset_t oldset;
  if (wp->fd != (-1))
  {
    bufferevent_free(wp->event);
    close(wp->fd);
  }
  if (argc > 0)
  {
    cmd_free_argv(wp->argc, wp->argv);
    wp->argc = argc;
    wp->argv = cmd_copy_argv(argc, argv);
  }
  if (shell != 0)
  {
    free(wp->shell);
    wp->shell = xstrdup(shell);
  }
  if ((&cwd[cwd_idx]) != 0)
  {
    free((void *) wp->cwd);
    wp->cwd = xstrdup(cwd);
  }
  wp->flags &= ~(0x200 | 0x400);
  cmd_idx = cmd_stringify_argv(wp->argc, wp->argv);
  log_debug("spawn: %s -- %s", wp->shell, cmd);
  for (i = 0; i < wp->argc; i += 1)
  {
    log_debug("spawn: argv[%d] = %s", i, wp->argv[i]);
  }

  environ_log(env, "spawn: ");
  memset(&ws, 0, sizeof(ws));
  ws.ws_col = (&wp->base)->grid->sx;
  ws.ws_row = (&wp->base)->grid->sy;
  sigfillset(&set);
  sigprocmask(SIG_BLOCK, &set, &oldset);
  switch (wp->pid = fdforkpty(ptm_fd, &wp->fd, wp->tty, 0, &ws))
  {
    case -1:
    {
      wp->fd = -1;
      xasprintf(cause, "%s: %s", cmd, strerror(errno));
      free(cmd);
      sigprocmask(SIG_SETMASK, &oldset, 0);
      return -1;
    }

    case 0:
    {
      helper_window_pane_spawn_1(&cwd_idx, &argvp_idx, &ptr_idx, &first_idx, &home_idx, &tio2, wp, path, cwd, env, tio, argv0, argvp, ptr, first, home, oldset);
    }

  }

  sigprocmask(SIG_SETMASK, &oldset, 0);
  setblocking(wp->fd, 0);
  wp->event = bufferevent_new(wp->fd, window_pane_read_callback, 0, window_pane_error_callback, wp);
  bufferevent_setwatermark(wp->event, EV_READ, 0, 4096);
  bufferevent_enable(wp->event, EV_READ | EV_WRITE);
  free(cmd);
  return 0;
}


/*** DEPENDENCIES:
None
----------------------------
void cmd_free_argv(int argc, char **argv)
{
  int i;
  if (argc == 0)
  {
    return;
  }
  for (i = 0; i < argc; i += 1)
  {
    free(argv[i]);
  }

  free(argv);
}


----------------------------
pid_t fdforkpty(int ptmfd, int *master, char *name, struct termios *tio, struct winsize *ws)
{
  return forkpty(master, name, tio, ws);
}


----------------------------
void helper_window_pane_spawn_1(unsigned int * const cwd_idx_ref, unsigned int * const argvp_idx_ref, unsigned int * const ptr_idx_ref, unsigned int * const first_idx_ref, unsigned int * const home_idx_ref, struct termios * const tio2_ref, struct window_pane * const wp, const char * const path, const char * const cwd, struct environ * const env, struct termios * const tio, char * const argv0, char ** const argvp, const char * const ptr, const char * const first, const char * const home, sigset_t oldset)
{
  unsigned int cwd_idx = *cwd_idx_ref;
  unsigned int argvp_idx = *argvp_idx_ref;
  unsigned int ptr_idx = *ptr_idx_ref;
  unsigned int first_idx = *first_idx_ref;
  unsigned int home_idx = *home_idx_ref;
  struct termios tio2 = *tio2_ref;
  proc_clear_signals(server_proc, 1);
  sigprocmask(SIG_SETMASK, &oldset, 0);
  cwd_idx = 0;
  if (chdir(wp->cwd) == 0)
  {
    cwd_idx = wp->cwd_idx;
  }
  else
    if (((home_idx = find_home()) != 0) && (chdir(home) == 0))
  {
    cwd_idx = &home[home_idx];
  }
  else
    chdir("/");
  if (tcgetattr(STDIN_FILENO, &tio2) != 0)
  {
    fatal("tcgetattr failed");
  }
  if (tio != 0)
  {
    memcpy(tio2.c_cc, tio->c_cc, sizeof(tio2.c_cc));
  }
  tio2.c_cc[VERASE] = '\177';
  if (tcsetattr(STDIN_FILENO, TCSANOW, &tio2) != 0)
  {
    fatal("tcgetattr failed");
  }
  log_close();
  closefrom(STDERR_FILENO + 1);
  if (path != 0)
  {
    environ_set(env, "PATH", "%s", path);
  }
  if ((&cwd[cwd_idx]) != 0)
  {
    environ_set(env, "PWD", "%s", cwd);
  }
  environ_set(env, "TMUX_PANE", "%%%u", wp->id);
  environ_push(env);
  setenv("SHELL", wp->shell, 1);
  ptr_idx = strrchr(wp->shell, '/');
  if (wp->argc > 0)
  {
    if (wp->argc != 1)
    {
      argvp_idx = cmd_copy_argv(wp->argc, wp->argv);
      execvp(argvp[0 + argvp_idx], argvp);
      fatal("execvp failed");
    }
    first_idx = wp->argv[0];
    if (((&ptr[ptr_idx]) != 0) && ((*((&ptr[ptr_idx]) + 1)) != '\0'))
    {
      xasprintf(&argv0, "%s", (&ptr[ptr_idx]) + 1);
    }
    else
      xasprintf(&argv0, "%s", wp->shell);
    execl(wp->shell, argv0, "-c", first, (char *) 0);
    fatal("execl failed");
  }
  if (((&ptr[ptr_idx]) != 0) && ((*((&ptr[ptr_idx]) + 1)) != '\0'))
  {
    xasprintf(&argv0, "-%s", (&ptr[ptr_idx]) + 1);
  }
  else
    xasprintf(&argv0, "-%s", wp->shell);
  execl(wp->shell, argv0, (char *) 0);
  fatal("execl failed");
  *cwd_idx_ref = cwd_idx;
  *argvp_idx_ref = argvp_idx;
  *ptr_idx_ref = ptr_idx;
  *first_idx_ref = first_idx;
  *home_idx_ref = home_idx;
  *tio2_ref = tio2;
}


----------------------------
char *cmd_stringify_argv(int argc, char **argv)
{
  char *buf;
  unsigned int buf_idx = 0;
  int i;
  size_t len;
  if (argc == 0)
  {
    return xstrdup("");
  }
  len = 0;
  buf_idx = 0;
  for (i = 0; i < argc; i += 1)
  {
    len += strlen(argv[i]) + 1;
    buf_idx = xrealloc(buf_idx, len);
    if (i == 0)
    {
      buf[buf_idx] = '\0';
    }
    else
      strlcat(buf, " ", len);
    strlcat(buf, argv[i], len);
  }

  return buf;
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
static void window_pane_read_callback(struct bufferevent *bufev, void *data)
{
  struct window_pane *wp = data;
  struct evbuffer *evb = wp->event->input;
  size_t size = EVBUFFER_LENGTH(evb);
  char *new_data;
  unsigned int new_data_idx = 0;
  size_t new_size;
  new_size = size - wp->pipe_off;
  if ((wp->pipe_fd != (-1)) && (new_size > 0))
  {
    new_data_idx = EVBUFFER_DATA(evb) + wp->pipe_off;
    bufferevent_write(wp->pipe_event, new_data, new_size);
  }
  log_debug("%%%u has %zu bytes", wp->id, size);
  input_parse(wp);
  wp->pipe_off = EVBUFFER_LENGTH(evb);
}


----------------------------
static void window_pane_error_callback(struct bufferevent *bufev, short what, void *data)
{
  struct window_pane *wp = data;
  log_debug("%%%u error", wp->id);
  wp->flags |= 0x100;
  if (window_pane_destroy_ready(wp))
  {
    server_destroy_pane(wp, 1);
  }
}


----------------------------
char **cmd_copy_argv(int argc, char **argv)
{
  char **new_argv;
  unsigned int new_argv_idx = 0;
  int i;
  if (argc == 0)
  {
    return 0;
  }
  new_argv_idx = xcalloc(argc + 1, sizeof(*new_argv_idx));
  for (i = 0; i < argc; i += 1)
  {
    if (argv[i] != 0)
    {
      new_argv[i + new_argv_idx] = xstrdup(argv[i]);
    }
  }

  return new_argv;
}


----------------------------
void environ_log(struct environ *env, const char *fmt, ...)
{
  struct environ_entry *envent;
  unsigned int envent_idx = 0;
  va_list ap;
  char *prefix;
  __builtin_va_start(ap);
  vasprintf(&prefix, fmt, ap);
  ;
  for (envent_idx = environ_RB_MINMAX(env, -1); (&envent[envent_idx]) != 0; envent_idx = environ_RB_NEXT(envent_idx))
  {
    if ((envent->value != 0) && ((*envent->name) != '\0'))
    {
      log_debug("%s%s=%s", prefix, envent->name, envent->value);
    }
  }

  free(prefix);
}


----------------------------
void setblocking(int fd, int state)
{
  int mode;
  if ((mode = fcntl(fd, F_GETFL)) != (-1))
  {
    if (!state)
    {
      mode |= O_NONBLOCK;
    }
    else
      mode &= ~O_NONBLOCK;
    fcntl(fd, F_SETFL, mode);
  }
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
extern int ptm_fd
----------------------------
None
----------------------------
***/


struct window *window_create_spawn(const char *name, int argc, char **argv, const char *path, const char *shell, const char *cwd, struct environ *env, struct termios *tio, u_int sx, u_int sy, u_int hlimit, char **cause)
{
  struct window *w;
  unsigned int w_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  w_idx = window_create(sx, sy);
  wp_idx = window_add_pane(w, 0, 0, 0, hlimit);
  layout_init(w, wp);
  if (window_pane_spawn(wp, argc, argv, path, shell, cwd, env, tio, cause) != 0)
  {
    window_destroy(w);
    return 0;
  }
  w->active = (&w->panes)->tqh_first;
  if (name != 0)
  {
    w->name = xstrdup(name);
    options_set_number(w->options, "automatic-rename", 0);
  }
  else
    w->name = default_window_name(w);
  notify_window("window-pane-changed", w);
  return w;
}


/*** DEPENDENCIES:
char *default_window_name(struct window *w)
{
  char *cmd;
  unsigned int cmd_idx = 0;
  char *s;
  unsigned int s_idx = 0;
  cmd_idx = cmd_stringify_argv(w->active->argc, w->active->argv);
  if (((&cmd[cmd_idx]) != 0) && (cmd[cmd_idx] != '\0'))
  {
    s_idx = parse_window_name(cmd);
  }
  else
    s_idx = parse_window_name(w->active->shell);
  free(cmd);
  return s;
}


----------------------------
None
----------------------------
struct options_entry *options_set_number(struct options *oo, const char *name, long long value)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  if ((*name) == '@')
  {
    fatalx("user option %s must be a string", name);
  }
  o_idx = options_get_only(oo, name);
  if ((&o[o_idx]) == 0)
  {
    o_idx = options_default(oo, options_parent_table_entry(oo, name));
    if ((&o[o_idx]) == 0)
    {
      return 0;
    }
  }
  if (!((o->tableentry != 0) && ((((((o->tableentry->type == OPTIONS_TABLE_NUMBER) || (o->tableentry->type == OPTIONS_TABLE_KEY)) || (o->tableentry->type == OPTIONS_TABLE_COLOUR)) || (o->tableentry->type == OPTIONS_TABLE_ATTRIBUTES)) || (o->tableentry->type == OPTIONS_TABLE_FLAG)) || (o->tableentry->type == OPTIONS_TABLE_CHOICE))))
  {
    fatalx("option %s is not a number", name);
  }
  o->number = value;
  return o;
}


----------------------------
struct window_pane *window_add_pane(struct window *w, struct window_pane *other, int before, int full_size, u_int hlimit)
{
  unsigned int other_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  if ((&other[other_idx]) == 0)
  {
    other_idx = w->active;
  }
  wp_idx = window_pane_create(w, w->sx, w->sy, hlimit);
  if ((&w->panes)->tqh_first == 0)
  {
    log_debug("%s: @%u at start", __func__, w->id);
    do
    {
      if ((wp->entry.tqe_next = (&w->panes)->tqh_first) != 0)
      {
        (&w->panes)->tqh_first->entry.tqe_prev = &wp->entry.tqe_next;
      }
      else
        (&w->panes)->tqh_last = &wp->entry.tqe_next;
      (&w->panes)->tqh_first = &wp[wp_idx];
      wp->entry.tqe_prev = &(&w->panes)->tqh_first;
    }
    while (0);
  }
  else
    if (before)
  {
    helper_window_add_pane_1(w, other, full_size, other_idx, wp, wp_idx);
  }
  else
  {
    helper_window_add_pane_2(w, other, full_size, wp, wp_idx);
  }
  return wp;
}


----------------------------
struct window *window_create(u_int sx, u_int sy)
{
  struct window *w;
  unsigned int w_idx = 0;
  w_idx = xcalloc(1, sizeof(*w_idx));
  w->name = 0;
  w->flags = 0x8000;
  do
  {
    (&w->panes)->tqh_first = 0;
    (&w->panes)->tqh_last = &(&w->panes)->tqh_first;
  }
  while (0);
  w->active = 0;
  w->lastlayout = -1;
  w->layout_root = 0;
  w->sx = sx;
  w->sy = sy;
  w->options = options_create(global_w_options);
  w->references = 0;
  do
  {
    (&w->winlinks)->tqh_first = 0;
    (&w->winlinks)->tqh_last = &(&w->winlinks)->tqh_first;
  }
  while (0);
  w->id = next_window_id;
  next_window_id += 1;
  windows_RB_INSERT(&windows, w);
  window_update_activity(w);
  return w;
}


----------------------------
int window_pane_spawn(struct window_pane *wp, int argc, char **argv, const char *path, const char *shell, const char *cwd, struct environ *env, struct termios *tio, char **cause)
{
  unsigned int cwd_idx = 0;
  struct winsize ws;
  char *argv0;
  char *cmd;
  unsigned int cmd_idx = 0;
  char **argvp;
  unsigned int argvp_idx = 0;
  const char *ptr;
  unsigned int ptr_idx = 0;
  const char *first;
  unsigned int first_idx = 0;
  const char *home;
  unsigned int home_idx = 0;
  struct termios tio2;
  int i;
  sigset_t set;
  sigset_t oldset;
  if (wp->fd != (-1))
  {
    bufferevent_free(wp->event);
    close(wp->fd);
  }
  if (argc > 0)
  {
    cmd_free_argv(wp->argc, wp->argv);
    wp->argc = argc;
    wp->argv = cmd_copy_argv(argc, argv);
  }
  if (shell != 0)
  {
    free(wp->shell);
    wp->shell = xstrdup(shell);
  }
  if ((&cwd[cwd_idx]) != 0)
  {
    free((void *) wp->cwd);
    wp->cwd = xstrdup(cwd);
  }
  wp->flags &= ~(0x200 | 0x400);
  cmd_idx = cmd_stringify_argv(wp->argc, wp->argv);
  log_debug("spawn: %s -- %s", wp->shell, cmd);
  for (i = 0; i < wp->argc; i += 1)
  {
    log_debug("spawn: argv[%d] = %s", i, wp->argv[i]);
  }

  environ_log(env, "spawn: ");
  memset(&ws, 0, sizeof(ws));
  ws.ws_col = (&wp->base)->grid->sx;
  ws.ws_row = (&wp->base)->grid->sy;
  sigfillset(&set);
  sigprocmask(SIG_BLOCK, &set, &oldset);
  switch (wp->pid = fdforkpty(ptm_fd, &wp->fd, wp->tty, 0, &ws))
  {
    case -1:
    {
      wp->fd = -1;
      xasprintf(cause, "%s: %s", cmd, strerror(errno));
      free(cmd);
      sigprocmask(SIG_SETMASK, &oldset, 0);
      return -1;
    }

    case 0:
    {
      helper_window_pane_spawn_1(&cwd_idx, &argvp_idx, &ptr_idx, &first_idx, &home_idx, &tio2, wp, path, cwd, env, tio, argv0, argvp, ptr, first, home, oldset);
    }

  }

  sigprocmask(SIG_SETMASK, &oldset, 0);
  setblocking(wp->fd, 0);
  wp->event = bufferevent_new(wp->fd, window_pane_read_callback, 0, window_pane_error_callback, wp);
  bufferevent_setwatermark(wp->event, EV_READ, 0, 4096);
  bufferevent_enable(wp->event, EV_READ | EV_WRITE);
  free(cmd);
  return 0;
}


----------------------------
void layout_init(struct window *w, struct window_pane *wp)
{
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  lc_idx = (w->layout_root = layout_create_cell(0));
  layout_set_size(lc, w->sx, w->sy, 0, 0);
  layout_make_leaf(lc, wp);
  layout_fix_panes(w, w->sx, w->sy);
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
void notify_window(const char *name, struct window *w)
{
  struct cmd_find_state fs;
  cmd_find_from_window(&fs, w, 0);
  notify_add(name, &fs, 0, 0, w, 0);
}


----------------------------
None
----------------------------
None
----------------------------
***/


