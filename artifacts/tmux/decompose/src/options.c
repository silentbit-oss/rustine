// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_options_tree_RB_REMOVE_COLOR_1_2_2_1(unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const parent, struct options_entry * const tmp, unsigned int parent_idx)
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
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_options_tree_RB_REMOVE_COLOR_1_2_2_2(unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const parent, struct options_entry * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct options_entry *oright;
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
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_options_tree_RB_REMOVE_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const parent, struct options_entry * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_options_tree_RB_REMOVE_COLOR_1_2_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_left)
  {
    tmp->entry.rbe_left->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_options_tree_RB_REMOVE_COLOR_1_2_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
void helper_helper_helper_helper_options_tree_RB_REMOVE_COLOR_1_2_2_1(unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const parent, struct options_entry * const tmp, unsigned int parent_idx)
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
void helper_helper_helper_helper_options_tree_RB_REMOVE_COLOR_1_2_2_2(unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const parent, struct options_entry * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct options_entry *oright;
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


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_options_tree_RB_REMOVE_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const parent, struct options_entry * const tmp, unsigned int parent_idx)
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
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_options_tree_RB_REMOVE_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const parent, struct options_entry * const elm, struct options_entry * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_left;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_options_tree_RB_REMOVE_COLOR_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_options_tree_RB_REMOVE_COLOR_1_2_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
void helper_helper_helper_options_tree_RB_REMOVE_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const parent, struct options_entry * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_options_tree_RB_REMOVE_COLOR_1_2_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_left)
  {
    tmp->entry.rbe_left->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_options_tree_RB_REMOVE_COLOR_1_2_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_helper_options_tree_RB_REMOVE_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const parent, struct options_entry * const tmp, unsigned int parent_idx)
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
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_options_tree_RB_REMOVE_COLOR_1_1_2_1(unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const parent, struct options_entry * const tmp, unsigned int parent_idx)
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
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_options_tree_RB_REMOVE_COLOR_1_1_2_2(unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const parent, struct options_entry * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct options_entry *oleft;
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
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_options_tree_RB_REMOVE_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const parent, struct options_entry * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_options_tree_RB_REMOVE_COLOR_1_1_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_right)
  {
    tmp->entry.rbe_right->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_options_tree_RB_REMOVE_COLOR_1_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
void helper_helper_helper_helper_options_tree_RB_REMOVE_COLOR_1_1_2_1(unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const parent, struct options_entry * const tmp, unsigned int parent_idx)
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
void helper_helper_helper_helper_options_tree_RB_REMOVE_COLOR_1_1_2_2(unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const parent, struct options_entry * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct options_entry *oleft;
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


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_options_tree_RB_REMOVE_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const parent, struct options_entry * const tmp, unsigned int parent_idx)
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
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_options_tree_RB_REMOVE_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const parent, struct options_entry * const elm, struct options_entry * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_right;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_options_tree_RB_REMOVE_COLOR_1_1_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_options_tree_RB_REMOVE_COLOR_1_1_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
void helper_helper_helper_options_tree_RB_REMOVE_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const parent, struct options_entry * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_options_tree_RB_REMOVE_COLOR_1_1_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_right)
  {
    tmp->entry.rbe_right->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_options_tree_RB_REMOVE_COLOR_1_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_helper_options_tree_RB_REMOVE_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const parent, struct options_entry * const tmp, unsigned int parent_idx)
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
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_options_tree_RB_REMOVE_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const parent, struct options_entry * const elm, struct options_entry * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if (parent->entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_options_tree_RB_REMOVE_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  else
  {
    helper_helper_options_tree_RB_REMOVE_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
void helper_helper_options_tree_RB_REMOVE_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const parent, struct options_entry * const elm, struct options_entry * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_left;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_options_tree_RB_REMOVE_COLOR_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_options_tree_RB_REMOVE_COLOR_1_2_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_options_tree_RB_REMOVE_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const parent, struct options_entry * const elm, struct options_entry * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_right;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_options_tree_RB_REMOVE_COLOR_1_1_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_options_tree_RB_REMOVE_COLOR_1_1_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


static void options_tree_RB_REMOVE_COLOR(struct options_tree *head, struct options_entry *parent, struct options_entry *elm)
{
  unsigned int elm_idx = 0;
  unsigned int parent_idx = 0;
  struct options_entry *tmp;
  unsigned int tmp_idx = 0;
  while ((((&elm[elm_idx]) == 0) || (elm->entry.rbe_color == 0)) && ((&elm[elm_idx]) != head->rbh_root))
  {
    helper_options_tree_RB_REMOVE_COLOR_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }

  if (elm)
  {
    elm->entry.rbe_color = 0;
  }
}


/*** DEPENDENCIES:
void helper_options_tree_RB_REMOVE_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const parent, struct options_entry * const elm, struct options_entry * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if (parent->entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_options_tree_RB_REMOVE_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  else
  {
    helper_helper_options_tree_RB_REMOVE_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
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
void helper_options_tree_RB_REMOVE_1(unsigned int * const elm_idx_ref, unsigned int * const child_idx_ref, unsigned int * const parent_idx_ref, int * const color_ref, struct options_tree * const head, struct options_entry * const elm, struct options_entry * const child, struct options_entry * const parent, struct options_entry * const old)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int child_idx = *child_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  int color = *color_ref;
  struct options_entry *left;
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
None
----------------------------
***/


static struct options_entry *options_tree_RB_REMOVE(struct options_tree *head, struct options_entry *elm)
{
  unsigned int elm_idx = 0;
  struct options_entry *child;
  unsigned int child_idx = 0;
  struct options_entry *parent;
  unsigned int parent_idx = 0;
  struct options_entry *old = elm;
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
    helper_options_tree_RB_REMOVE_1(&elm_idx, &child_idx, &parent_idx, &color, head, elm, child, parent, old);
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
    options_tree_RB_REMOVE_COLOR(head, parent, child);
  }

  return old;
}


/*** DEPENDENCIES:
static void options_tree_RB_REMOVE_COLOR(struct options_tree *head, struct options_entry *parent, struct options_entry *elm)
{
  unsigned int elm_idx = 0;
  unsigned int parent_idx = 0;
  struct options_entry *tmp;
  unsigned int tmp_idx = 0;
  while ((((&elm[elm_idx]) == 0) || (elm->entry.rbe_color == 0)) && ((&elm[elm_idx]) != head->rbh_root))
  {
    helper_options_tree_RB_REMOVE_COLOR_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }

  if (elm)
  {
    elm->entry.rbe_color = 0;
  }
}


----------------------------
void helper_options_tree_RB_REMOVE_1(unsigned int * const elm_idx_ref, unsigned int * const child_idx_ref, unsigned int * const parent_idx_ref, int * const color_ref, struct options_tree * const head, struct options_entry * const elm, struct options_entry * const child, struct options_entry * const parent, struct options_entry * const old)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int child_idx = *child_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  int color = *color_ref;
  struct options_entry *left;
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


void options_remove(struct options_entry *o)
{
  struct options *oo = o->owner;
  u_int i;
  if ((o->tableentry == 0) || (o->tableentry->type == OPTIONS_TABLE_STRING))
  {
    free((void *) o->string);
  }
  else
    if ((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_ARRAY))
  {
    for (i = 0; i < o->arraysize; i += 1)
    {
      free((void *) o->array[i]);
    }

    free(o->array);
  }
  options_tree_RB_REMOVE(&oo->tree, o);
  free(o);
}


/*** DEPENDENCIES:
static struct options_entry *options_tree_RB_REMOVE(struct options_tree *head, struct options_entry *elm)
{
  unsigned int elm_idx = 0;
  struct options_entry *child;
  unsigned int child_idx = 0;
  struct options_entry *parent;
  unsigned int parent_idx = 0;
  struct options_entry *old = elm;
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
    helper_options_tree_RB_REMOVE_1(&elm_idx, &child_idx, &parent_idx, &color, head, elm, child, parent, old);
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
    options_tree_RB_REMOVE_COLOR(head, parent, child);
  }

  return old;
}


----------------------------
None
----------------------------
***/


static struct options_entry *options_tree_RB_MINMAX(struct options_tree *head, int val)
{
  struct options_entry *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct options_entry *parent = 0;
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
None
----------------------------
***/


static struct options_entry *options_tree_RB_NEXT(struct options_entry *elm)
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


void options_free(struct options *oo)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  struct options_entry *tmp;
  unsigned int tmp_idx = 0;
  for (o_idx = options_tree_RB_MINMAX(&oo->tree, -1); ((&o[o_idx]) != 0) && ((tmp_idx = options_tree_RB_NEXT(o), 1)); o_idx = &tmp[tmp_idx])
  {
    options_remove(o);
  }

  free(oo);
}


/*** DEPENDENCIES:
void options_remove(struct options_entry *o)
{
  struct options *oo = o->owner;
  u_int i;
  if ((o->tableentry == 0) || (o->tableentry->type == OPTIONS_TABLE_STRING))
  {
    free((void *) o->string);
  }
  else
    if ((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_ARRAY))
  {
    for (i = 0; i < o->arraysize; i += 1)
    {
      free((void *) o->array[i]);
    }

    free(o->array);
  }
  options_tree_RB_REMOVE(&oo->tree, o);
  free(o);
}


----------------------------
static struct options_entry *options_tree_RB_MINMAX(struct options_tree *head, int val)
{
  struct options_entry *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct options_entry *parent = 0;
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
static struct options_entry *options_tree_RB_NEXT(struct options_entry *elm)
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


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
const char *helper_options_tostring_1(unsigned int * const tmp_idx_ref, struct options_entry * const o, int numeric, static char s[1024], const char * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = 0;
  switch (o->tableentry->type)
  {
    case OPTIONS_TABLE_NUMBER:
    {
      xsnprintf(s, sizeof(s), "%lld", o->number);
      break;
    }

    case OPTIONS_TABLE_KEY:
    {
      tmp_idx = key_string_lookup_key(o->number);
      break;
    }

    case OPTIONS_TABLE_COLOUR:
    {
      tmp_idx = colour_tostring(o->number);
      break;
    }

    case OPTIONS_TABLE_ATTRIBUTES:
    {
      tmp_idx = attributes_tostring(o->number);
      break;
    }

    case OPTIONS_TABLE_FLAG:
    {
      if (numeric)
      {
        xsnprintf(s, sizeof(s), "%lld", o->number);
      }
      else
        tmp_idx = (o->number) ? ("on") : ("off");
      break;
    }

    case OPTIONS_TABLE_CHOICE:
    {
      tmp_idx = o->tableentry->choices[o->number];
      break;
    }

    case OPTIONS_TABLE_STRING:

    case OPTIONS_TABLE_STYLE:

    case OPTIONS_TABLE_ARRAY:
    {
      break;
    }

  }

  if ((&tmp[tmp_idx]) != 0)
  {
    xsnprintf(s, sizeof(s), "%s", tmp);
  }
  return s;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
const char *key_string_lookup_key(key_code key)
{
  static char out[32];
  char tmp[8];
  u_int i;
  struct utf8_data ud;
  size_t off;
  *out = '\0';
  if (key == 0xffff00000000ULL)
  {
    return "None";
  }
  if (key == 0xfffe00000000ULL)
  {
    return "Unknown";
  }
  if (key == KEYC_FOCUS_IN)
  {
    return "FocusIn";
  }
  if (key == KEYC_FOCUS_OUT)
  {
    return "FocusOut";
  }
  if (key == KEYC_PASTE_START)
  {
    return "PasteStart";
  }
  if (key == KEYC_PASTE_END)
  {
    return "PasteEnd";
  }
  if (key == KEYC_MOUSE)
  {
    return "Mouse";
  }
  if (key == KEYC_DRAGGING)
  {
    return "Dragging";
  }
  if (key == KEYC_MOUSEMOVE_PANE)
  {
    return "MouseMovePane";
  }
  if (key == KEYC_MOUSEMOVE_STATUS)
  {
    return "MouseMoveStatus";
  }
  if (key == KEYC_MOUSEMOVE_BORDER)
  {
    return "MouseMoveBorder";
  }
  if ((key >= 0x000020000000ULL) && (key < (0x000020000000ULL + 1000)))
  {
    snprintf(out, sizeof(out), "User%u", (u_int) (key - 0x000020000000ULL));
    return out;
  }
  if ((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) == 0)
  {
    key = (' ' | 0x400000000000ULL) | (key & (((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL));
  }
  if (key & 0x400000000000ULL)
  {
    strlcat(out, "C-", sizeof(out));
  }
  if (key & 0x200000000000ULL)
  {
    strlcat(out, "M-", sizeof(out));
  }
  if (key & 0x800000000000ULL)
  {
    strlcat(out, "S-", sizeof(out));
  }
  key &= ~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL);
  for (i = 0; i < ((sizeof(key_string_table)) / (sizeof(key_string_table[0]))); i += 1)
  {
    if (key == key_string_table[i].key)
    {
      break;
    }
  }

  if (i != ((sizeof(key_string_table)) / (sizeof(key_string_table[0]))))
  {
    strlcat(out, key_string_table[i].string, sizeof(out));
    return out;
  }
  if ((key > 127) && (key < 0x000010000000ULL))
  {
    if (utf8_split(key, &ud) == UTF8_DONE)
    {
      off = strlen(out);
      memcpy(out + off, ud.data, ud.size);
      out[off + ud.size] = '\0';
      return out;
    }
  }
  if ((key == 127) || (key > 255))
  {
    snprintf(out, sizeof(out), "Invalid#%llx", key);
    return out;
  }
  if (key <= 32)
  {
    if ((key == 0) || (key > 26))
    {
      xsnprintf(tmp, sizeof(tmp), "C-%c", (int) (64 + key));
    }
    else
      xsnprintf(tmp, sizeof(tmp), "C-%c", (int) (96 + key));
  }
  else
    if ((key >= 32) && (key <= 126))
  {
    tmp[0] = key;
    tmp[1] = '\0';
  }
  else
    if (key >= 128)
  {
    xsnprintf(tmp, sizeof(tmp), "\\%llo", key);
  }
  strlcat(out, tmp, sizeof(out));
  return out;
}


----------------------------
const char *colour_tostring(int c)
{
  static char s[32];
  u_char r;
  u_char g;
  u_char b;
  if (c & 0x02000000)
  {
    colour_split_rgb(c, &r, &g, &b);
    xsnprintf(s, sizeof(s), "#%02x%02x%02x", r, g, b);
    return s;
  }
  if (c & 0x01000000)
  {
    xsnprintf(s, sizeof(s), "colour%u", c & 0xff);
    return s;
  }
  switch (c)
  {
    case 0:
    {
      return "black";
    }

    case 1:
    {
      return "red";
    }

    case 2:
    {
      return "green";
    }

    case 3:
    {
      return "yellow";
    }

    case 4:
    {
      return "blue";
    }

    case 5:
    {
      return "magenta";
    }

    case 6:
    {
      return "cyan";
    }

    case 7:
    {
      return "white";
    }

    case 8:
    {
      return "default";
    }

    case 90:
    {
      return "brightblack";
    }

    case 91:
    {
      return "brightred";
    }

    case 92:
    {
      return "brightgreen";
    }

    case 93:
    {
      return "brightyellow";
    }

    case 94:
    {
      return "brightblue";
    }

    case 95:
    {
      return "brightmagenta";
    }

    case 96:
    {
      return "brightcyan";
    }

    case 97:
    {
      return "brightwhite";
    }

  }

  return 0;
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
const char *attributes_tostring(int attr)
{
  static char buf[128];
  size_t len;
  if (attr == 0)
  {
    return "none";
  }
  len = xsnprintf(buf, sizeof(buf), "%s%s%s%s%s%s%s%s", (attr & 0x1) ? ("bright,") : (""), (attr & 0x2) ? ("dim,") : (""), (attr & 0x4) ? ("underscore,") : (""), (attr & 0x8) ? ("blink,") : (""), (attr & 0x10) ? ("reverse,") : (""), (attr & 0x20) ? ("hidden,") : (""), (attr & 0x40) ? ("italics,") : (""), (attr & 0x100) ? ("strikethrough,") : (""));
  if (len > 0)
  {
    buf[len - 1] = '\0';
  }
  return buf;
}


----------------------------
None
----------------------------
***/


const char *options_tostring(struct options_entry *o, int idx, int numeric)
{
  static char s[1024];
  const char *tmp;
  unsigned int tmp_idx = 0;
  if ((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_ARRAY))
  {
    if (idx == (-1))
    {
      return 0;
    }
    if ((((u_int) idx) >= o->arraysize) || (o->array[idx] == 0))
    {
      return "";
    }
    return o->array[idx];
  }
  if ((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_STYLE))
  {
    return style_tostring(&o->style);
  }
  if ((o->tableentry != 0) && ((((((o->tableentry->type == OPTIONS_TABLE_NUMBER) || (o->tableentry->type == OPTIONS_TABLE_KEY)) || (o->tableentry->type == OPTIONS_TABLE_COLOUR)) || (o->tableentry->type == OPTIONS_TABLE_ATTRIBUTES)) || (o->tableentry->type == OPTIONS_TABLE_FLAG)) || (o->tableentry->type == OPTIONS_TABLE_CHOICE)))
  {
    helper_options_tostring_1(&tmp_idx, o, numeric, s, tmp);
  }
  if ((o->tableentry == 0) || (o->tableentry->type == OPTIONS_TABLE_STRING))
  {
    return o->string;
  }
  return 0;
}


/*** DEPENDENCIES:
const char *style_tostring(struct grid_cell *gc)
{
  int off = 0;
  int comma = 0;
  static char s[256];
  *s = '\0';
  if (gc->fg != 8)
  {
    off += xsnprintf(s, sizeof(s), "fg=%s", colour_tostring(gc->fg));
    comma = 1;
  }
  if (gc->bg != 8)
  {
    off += xsnprintf(s + off, (sizeof(s)) - off, "%sbg=%s", (comma) ? (",") : (""), colour_tostring(gc->bg));
    comma = 1;
  }
  if ((gc->attr != 0) && (gc->attr != 0x80))
  {
    xsnprintf(s + off, (sizeof(s)) - off, "%s%s", (comma) ? (",") : (""), attributes_tostring(gc->attr));
  }
  if ((*s) == '\0')
  {
    return "default";
  }
  return s;
}


----------------------------
const char *helper_options_tostring_1(unsigned int * const tmp_idx_ref, struct options_entry * const o, int numeric, static char s[1024], const char * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = 0;
  switch (o->tableentry->type)
  {
    case OPTIONS_TABLE_NUMBER:
    {
      xsnprintf(s, sizeof(s), "%lld", o->number);
      break;
    }

    case OPTIONS_TABLE_KEY:
    {
      tmp_idx = key_string_lookup_key(o->number);
      break;
    }

    case OPTIONS_TABLE_COLOUR:
    {
      tmp_idx = colour_tostring(o->number);
      break;
    }

    case OPTIONS_TABLE_ATTRIBUTES:
    {
      tmp_idx = attributes_tostring(o->number);
      break;
    }

    case OPTIONS_TABLE_FLAG:
    {
      if (numeric)
      {
        xsnprintf(s, sizeof(s), "%lld", o->number);
      }
      else
        tmp_idx = (o->number) ? ("on") : ("off");
      break;
    }

    case OPTIONS_TABLE_CHOICE:
    {
      tmp_idx = o->tableentry->choices[o->number];
      break;
    }

    case OPTIONS_TABLE_STRING:

    case OPTIONS_TABLE_STYLE:

    case OPTIONS_TABLE_ARRAY:
    {
      break;
    }

  }

  if ((&tmp[tmp_idx]) != 0)
  {
    xsnprintf(s, sizeof(s), "%s", tmp);
  }
  return s;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


static int options_cmp(struct options_entry *lhs, struct options_entry *rhs)
{
  return strcmp(lhs->name, rhs->name);
}


/*** DEPENDENCIES:
None
----------------------------
***/


static struct options_entry *options_tree_RB_FIND(struct options_tree *head, struct options_entry *elm)
{
  struct options_entry *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  int comp;
  while (tmp)
  {
    comp = options_cmp(elm, tmp);
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
static int options_cmp(struct options_entry *lhs, struct options_entry *rhs)
{
  return strcmp(lhs->name, rhs->name);
}


----------------------------
None
----------------------------
***/


struct options_entry *options_get_only(struct options *oo, const char *name)
{
  struct options_entry o;
  o.name = name;
  return options_tree_RB_FIND(&oo->tree, &o);
}


/*** DEPENDENCIES:
static struct options_entry *options_tree_RB_FIND(struct options_tree *head, struct options_entry *elm)
{
  struct options_entry *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  int comp;
  while (tmp)
  {
    comp = options_cmp(elm, tmp);
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


struct options_entry *options_get(struct options *oo, const char *name)
{
  unsigned int oo_idx = 0;
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_get_only(oo, name);
  while ((&o[o_idx]) == 0)
  {
    oo_idx = oo_idx->parent;
    if ((&oo[oo_idx]) == 0)
    {
      break;
    }
    o_idx = options_get_only(oo, name);
  }

  return o;
}


/*** DEPENDENCIES:
struct options_entry *options_get_only(struct options *oo, const char *name)
{
  struct options_entry o;
  o.name = name;
  return options_tree_RB_FIND(&oo->tree, &o);
}


----------------------------
None
----------------------------
***/


char *options_parse(const char *name, int *idx)
{
  char *copy;
  unsigned int copy_idx = 0;
  char *cp;
  unsigned int cp_idx = 0;
  char *end;
  unsigned int end_idx = 0;
  if ((*name) == '\0')
  {
    return 0;
  }
  copy_idx = xstrdup(name);
  if ((cp_idx = strchr(copy, '[')) == 0)
  {
    *idx = -1;
    return copy;
  }
  end_idx = strchr((&cp[cp_idx]) + 1, ']');
  if ((((&end[end_idx]) == 0) || (end[1 + end_idx] != '\0')) || (!isdigit((u_char) end[(-1) + end_idx])))
  {
    free(copy);
    return 0;
  }
  if ((sscanf(cp, "[%d]", idx) != 1) || ((*idx) < 0))
  {
    free(copy);
    return 0;
  }
  cp[cp_idx] = '\0';
  return copy;
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


struct options_entry *options_parse_get(struct options *oo, const char *s, int *idx, int only)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  char *name;
  unsigned int name_idx = 0;
  name_idx = options_parse(s, idx);
  if ((&name[name_idx]) == 0)
  {
    return 0;
  }
  if (only)
  {
    o_idx = options_get_only(oo, name);
  }
  else
    o_idx = options_get(oo, name);
  free(name);
  return o;
}


/*** DEPENDENCIES:
struct options_entry *options_get_only(struct options *oo, const char *name)
{
  struct options_entry o;
  o.name = name;
  return options_tree_RB_FIND(&oo->tree, &o);
}


----------------------------
struct options_entry *options_get(struct options *oo, const char *name)
{
  unsigned int oo_idx = 0;
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_get_only(oo, name);
  while ((&o[o_idx]) == 0)
  {
    oo_idx = oo_idx->parent;
    if ((&oo[oo_idx]) == 0)
    {
      break;
    }
    o_idx = options_get_only(oo, name);
  }

  return o;
}


----------------------------
char *options_parse(const char *name, int *idx)
{
  char *copy;
  unsigned int copy_idx = 0;
  char *cp;
  unsigned int cp_idx = 0;
  char *end;
  unsigned int end_idx = 0;
  if ((*name) == '\0')
  {
    return 0;
  }
  copy_idx = xstrdup(name);
  if ((cp_idx = strchr(copy, '[')) == 0)
  {
    *idx = -1;
    return copy;
  }
  end_idx = strchr((&cp[cp_idx]) + 1, ']');
  if ((((&end[end_idx]) == 0) || (end[1 + end_idx] != '\0')) || (!isdigit((u_char) end[(-1) + end_idx])))
  {
    free(copy);
    return 0;
  }
  if ((sscanf(cp, "[%d]", idx) != 1) || ((*idx) < 0))
  {
    free(copy);
    return 0;
  }
  cp[cp_idx] = '\0';
  return copy;
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
struct options_entry *options_get(struct options *oo, const char *name)
{
  unsigned int oo_idx = 0;
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_get_only(oo, name);
  while ((&o[o_idx]) == 0)
  {
    oo_idx = oo_idx->parent;
    if ((&oo[oo_idx]) == 0)
    {
      break;
    }
    o_idx = options_get_only(oo, name);
  }

  return o;
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


/*** DEPENDENCIES:
struct options_entry *options_get(struct options *oo, const char *name)
{
  unsigned int oo_idx = 0;
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_get_only(oo, name);
  while ((&o[o_idx]) == 0)
  {
    oo_idx = oo_idx->parent;
    if ((&oo[oo_idx]) == 0)
    {
      break;
    }
    o_idx = options_get_only(oo, name);
  }

  return o;
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


/*** DEPENDENCIES:
struct options_entry *options_get(struct options *oo, const char *name)
{
  unsigned int oo_idx = 0;
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_get_only(oo, name);
  while ((&o[o_idx]) == 0)
  {
    oo_idx = oo_idx->parent;
    if ((&oo[oo_idx]) == 0)
    {
      break;
    }
    o_idx = options_get_only(oo, name);
  }

  return o;
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


const struct options_table_entry *options_parent_table_entry(struct options *oo, const char *s)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  if (oo->parent == 0)
  {
    fatalx("no parent options for %s", s);
  }
  o_idx = options_get_only(oo->parent, s);
  if ((&o[o_idx]) == 0)
  {
    fatalx("%s not in parent options", s);
  }
  return o->tableentry;
}


/*** DEPENDENCIES:
struct options_entry *options_get_only(struct options *oo, const char *name)
{
  struct options_entry o;
  o.name = name;
  return options_tree_RB_FIND(&oo->tree, &o);
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


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_options_tree_RB_INSERT_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const gparent, struct options_entry * const tmp, unsigned int gparent_idx)
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
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_options_tree_RB_INSERT_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const elm, struct options_entry * const parent, struct options_entry * const tmp)
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
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_options_tree_RB_INSERT_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const elm, struct options_entry * const parent, struct options_entry * const gparent, struct options_entry * const tmp, unsigned int gparent_idx)
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
    helper_helper_helper_options_tree_RB_INSERT_COLOR_1_2_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_options_tree_RB_INSERT_COLOR_1_2_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
void helper_helper_helper_options_tree_RB_INSERT_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const gparent, struct options_entry * const tmp, unsigned int gparent_idx)
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
void helper_helper_helper_options_tree_RB_INSERT_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const elm, struct options_entry * const parent, struct options_entry * const tmp)
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


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_options_tree_RB_INSERT_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const gparent, struct options_entry * const tmp, unsigned int gparent_idx)
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
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_options_tree_RB_INSERT_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const elm, struct options_entry * const parent, struct options_entry * const tmp)
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
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_options_tree_RB_INSERT_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const elm, struct options_entry * const parent, struct options_entry * const gparent, struct options_entry * const tmp, unsigned int gparent_idx)
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
    helper_helper_helper_options_tree_RB_INSERT_COLOR_1_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_options_tree_RB_INSERT_COLOR_1_1_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
void helper_helper_helper_options_tree_RB_INSERT_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const gparent, struct options_entry * const tmp, unsigned int gparent_idx)
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
void helper_helper_helper_options_tree_RB_INSERT_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const elm, struct options_entry * const parent, struct options_entry * const tmp)
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


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'gparent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_options_tree_RB_INSERT_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const gparent_idx_ref, unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const elm, struct options_entry * const parent, struct options_entry * const gparent, struct options_entry * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int gparent_idx = *gparent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  gparent_idx = parent->entry.rbe_parent;
  if ((&parent[parent_idx]) == gparent->entry.rbe_left)
  {
    helper_helper_options_tree_RB_INSERT_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  else
  {
    helper_helper_options_tree_RB_INSERT_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *gparent_idx_ref = gparent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
void helper_helper_options_tree_RB_INSERT_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const elm, struct options_entry * const parent, struct options_entry * const gparent, struct options_entry * const tmp, unsigned int gparent_idx)
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
    helper_helper_helper_options_tree_RB_INSERT_COLOR_1_2_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_options_tree_RB_INSERT_COLOR_1_2_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_options_tree_RB_INSERT_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const elm, struct options_entry * const parent, struct options_entry * const gparent, struct options_entry * const tmp, unsigned int gparent_idx)
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
    helper_helper_helper_options_tree_RB_INSERT_COLOR_1_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_options_tree_RB_INSERT_COLOR_1_1_1(&tmp_idx, head, gparent, tmp, gparent_idx);
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


static void options_tree_RB_INSERT_COLOR(struct options_tree *head, struct options_entry *elm)
{
  unsigned int elm_idx = 0;
  struct options_entry *parent;
  unsigned int parent_idx = 0;
  struct options_entry *gparent;
  unsigned int gparent_idx = 0;
  struct options_entry *tmp;
  unsigned int tmp_idx = 0;
  while ((parent_idx = elm->entry.rbe_parent) && (parent->entry.rbe_color == 1))
  {
    helper_options_tree_RB_INSERT_COLOR_1(&elm_idx, &parent_idx, &gparent_idx, &tmp_idx, head, elm, parent, gparent, tmp);
  }

  head->rbh_root->entry.rbe_color = 0;
}


/*** DEPENDENCIES:
void helper_options_tree_RB_INSERT_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const gparent_idx_ref, unsigned int * const tmp_idx_ref, struct options_tree * const head, struct options_entry * const elm, struct options_entry * const parent, struct options_entry * const gparent, struct options_entry * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int gparent_idx = *gparent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  gparent_idx = parent->entry.rbe_parent;
  if ((&parent[parent_idx]) == gparent->entry.rbe_left)
  {
    helper_helper_options_tree_RB_INSERT_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  else
  {
    helper_helper_options_tree_RB_INSERT_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
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


static struct options_entry *options_tree_RB_INSERT(struct options_tree *head, struct options_entry *elm)
{
  struct options_entry *tmp;
  unsigned int tmp_idx = 0;
  struct options_entry *parent = 0;
  unsigned int parent_idx = 0;
  int comp = 0;
  tmp_idx = head->rbh_root;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    comp = options_cmp(elm, parent);
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
  options_tree_RB_INSERT_COLOR(head, elm);
  return 0;
}


/*** DEPENDENCIES:
static int options_cmp(struct options_entry *lhs, struct options_entry *rhs)
{
  return strcmp(lhs->name, rhs->name);
}


----------------------------
static void options_tree_RB_INSERT_COLOR(struct options_tree *head, struct options_entry *elm)
{
  unsigned int elm_idx = 0;
  struct options_entry *parent;
  unsigned int parent_idx = 0;
  struct options_entry *gparent;
  unsigned int gparent_idx = 0;
  struct options_entry *tmp;
  unsigned int tmp_idx = 0;
  while ((parent_idx = elm->entry.rbe_parent) && (parent->entry.rbe_color == 1))
  {
    helper_options_tree_RB_INSERT_COLOR_1(&elm_idx, &parent_idx, &gparent_idx, &tmp_idx, head, elm, parent, gparent, tmp);
  }

  head->rbh_root->entry.rbe_color = 0;
}


----------------------------
None
----------------------------
***/


struct options_entry *options_add(struct options *oo, const char *name)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_get_only(oo, name);
  if ((&o[o_idx]) != 0)
  {
    options_remove(o);
  }
  o_idx = xcalloc(1, sizeof(*o_idx));
  o->owner = oo;
  o->name = xstrdup(name);
  options_tree_RB_INSERT(&oo->tree, o);
  return o;
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
static struct options_entry *options_tree_RB_INSERT(struct options_tree *head, struct options_entry *elm)
{
  struct options_entry *tmp;
  unsigned int tmp_idx = 0;
  struct options_entry *parent = 0;
  unsigned int parent_idx = 0;
  int comp = 0;
  tmp_idx = head->rbh_root;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    comp = options_cmp(elm, parent);
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
  options_tree_RB_INSERT_COLOR(head, elm);
  return 0;
}


----------------------------
void options_remove(struct options_entry *o)
{
  struct options *oo = o->owner;
  u_int i;
  if ((o->tableentry == 0) || (o->tableentry->type == OPTIONS_TABLE_STRING))
  {
    free((void *) o->string);
  }
  else
    if ((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_ARRAY))
  {
    for (i = 0; i < o->arraysize; i += 1)
    {
      free((void *) o->array[i]);
    }

    free(o->array);
  }
  options_tree_RB_REMOVE(&oo->tree, o);
  free(o);
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
struct options_entry *options_get_only(struct options *oo, const char *name)
{
  struct options_entry o;
  o.name = name;
  return options_tree_RB_FIND(&oo->tree, &o);
}


----------------------------
None
----------------------------
***/


struct options_entry *options_empty(struct options *oo, const struct options_table_entry *oe)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_add(oo, oe->name);
  o->tableentry = oe;
  return o;
}


/*** DEPENDENCIES:
struct options_entry *options_add(struct options *oo, const char *name)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_get_only(oo, name);
  if ((&o[o_idx]) != 0)
  {
    options_remove(o);
  }
  o_idx = xcalloc(1, sizeof(*o_idx));
  o->owner = oo;
  o->name = xstrdup(name);
  options_tree_RB_INSERT(&oo->tree, o);
  return o;
}


----------------------------
None
----------------------------
***/


int options_array_set(struct options_entry *o, u_int idx, const char *value, int append)
{
  char *new;
  unsigned int new_idx = 0;
  u_int i;
  if (!((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_ARRAY)))
  {
    return -1;
  }
  if (idx >= 1000)
  {
    return -1;
  }
  if (idx >= o->arraysize)
  {
    o->array = xreallocarray(o->array, idx + 1, sizeof(*o->array));
    for (i = o->arraysize; i < (idx + 1); i += 1)
    {
      o->array[i] = 0;
    }

    o->arraysize = idx + 1;
  }
  new_idx = 0;
  if (value != 0)
  {
    if ((o->array[idx] != 0) && append)
    {
      xasprintf(&(&new[new_idx]), "%s%s", o->array[idx], value);
    }
    else
      new_idx = xstrdup(value);
  }
  free((void *) o->array[idx]);
  o->array[idx] = &new[new_idx];
  return 0;
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
None
----------------------------
***/


void options_array_assign(struct options_entry *o, const char *s)
{
  const char *separator;
  unsigned int separator_idx = 0;
  char *copy;
  unsigned int copy_idx = 0;
  char *next;
  unsigned int next_idx = 0;
  char *string;
  u_int i;
  separator_idx = o->tableentry->separator_idx;
  if ((&separator[separator_idx]) == 0)
  {
    separator_idx = " ,";
  }
  copy_idx = (string = xstrdup(s));
  while ((next_idx = strsep(&string, separator)) != 0)
  {
    if (next[next_idx] == '\0')
    {
      continue;
    }
    for (i = 0; i < 1000; i += 1)
    {
      if ((i >= o->arraysize) || (o->array[i] == 0))
      {
        break;
      }
    }

    if (i == 1000)
    {
      break;
    }
    options_array_set(o, i, next, 0);
  }

  free(copy);
}


/*** DEPENDENCIES:
int options_array_set(struct options_entry *o, u_int idx, const char *value, int append)
{
  char *new;
  unsigned int new_idx = 0;
  u_int i;
  if (!((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_ARRAY)))
  {
    return -1;
  }
  if (idx >= 1000)
  {
    return -1;
  }
  if (idx >= o->arraysize)
  {
    o->array = xreallocarray(o->array, idx + 1, sizeof(*o->array));
    for (i = o->arraysize; i < (idx + 1); i += 1)
    {
      o->array[i] = 0;
    }

    o->arraysize = idx + 1;
  }
  new_idx = 0;
  if (value != 0)
  {
    if ((o->array[idx] != 0) && append)
    {
      xasprintf(&(&new[new_idx]), "%s%s", o->array[idx], value);
    }
    else
      new_idx = xstrdup(value);
  }
  free((void *) o->array[idx]);
  o->array[idx] = &new[new_idx];
  return 0;
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


struct options_entry *options_default(struct options *oo, const struct options_table_entry *oe)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_empty(oo, oe);
  if (oe->type == OPTIONS_TABLE_ARRAY)
  {
    options_array_assign(o, oe->default_str);
  }
  else
    if (oe->type == OPTIONS_TABLE_STRING)
  {
    o->string = xstrdup(oe->default_str);
  }
  else
    if (oe->type == OPTIONS_TABLE_STYLE)
  {
    memcpy(&o->style, &grid_default_cell, sizeof(o->style));
    style_parse(&grid_default_cell, &o->style, oe->default_str);
  }
  else
    o->number = oe->default_num;
  return o;
}


/*** DEPENDENCIES:
int style_parse(const struct grid_cell *defgc, struct grid_cell *gc, const char *in)
{
  unsigned int in_idx = 0;
  struct grid_cell savedgc;
  const char delimiters[] = " ,";
  char tmp[32];
  int val;
  int fg;
  int bg;
  int attr;
  int flags;
  size_t end;
  if (in[in_idx] == '\0')
  {
    return 0;
  }
  if (strchr(delimiters, in[(strlen(in) - 1) + in_idx]) != 0)
  {
    return -1;
  }
  memcpy(&savedgc, gc, sizeof(savedgc));
  fg = gc->fg;
  bg = gc->bg;
  attr = gc->attr;
  flags = gc->flags;
  do
  {
    helper_style_parse_1(&in_idx, &val, &fg, &bg, &attr, &flags, &end, defgc, in, delimiters, tmp);
  }
  while (in[in_idx] != '\0');
  gc->fg = fg;
  gc->bg = bg;
  gc->attr = attr;
  gc->flags = flags;
  return 0;
  error:
  memcpy(gc, &savedgc, sizeof(*gc));

  return -1;
}


----------------------------
extern const struct grid_cell grid_default_cell
----------------------------
struct options_entry *options_empty(struct options *oo, const struct options_table_entry *oe)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_add(oo, oe->name);
  o->tableentry = oe;
  return o;
}


----------------------------
void options_array_assign(struct options_entry *o, const char *s)
{
  const char *separator;
  unsigned int separator_idx = 0;
  char *copy;
  unsigned int copy_idx = 0;
  char *next;
  unsigned int next_idx = 0;
  char *string;
  u_int i;
  separator_idx = o->tableentry->separator_idx;
  if ((&separator[separator_idx]) == 0)
  {
    separator_idx = " ,";
  }
  copy_idx = (string = xstrdup(s));
  while ((next_idx = strsep(&string, separator)) != 0)
  {
    if (next[next_idx] == '\0')
    {
      continue;
    }
    for (i = 0; i < 1000; i += 1)
    {
      if ((i >= o->arraysize) || (o->array[i] == 0))
      {
        break;
      }
    }

    if (i == 1000)
    {
      break;
    }
    options_array_set(o, i, next, 0);
  }

  free(copy);
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


/*** DEPENDENCIES:
const struct options_table_entry *options_parent_table_entry(struct options *oo, const char *s)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  if (oo->parent == 0)
  {
    fatalx("no parent options for %s", s);
  }
  o_idx = options_get_only(oo->parent, s);
  if ((&o[o_idx]) == 0)
  {
    fatalx("%s not in parent options", s);
  }
  return o->tableentry;
}


----------------------------
struct options_entry *options_get_only(struct options *oo, const char *name)
{
  struct options_entry o;
  o.name = name;
  return options_tree_RB_FIND(&oo->tree, &o);
}


----------------------------
struct options_entry *options_default(struct options *oo, const struct options_table_entry *oe)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_empty(oo, oe);
  if (oe->type == OPTIONS_TABLE_ARRAY)
  {
    options_array_assign(o, oe->default_str);
  }
  else
    if (oe->type == OPTIONS_TABLE_STRING)
  {
    o->string = xstrdup(oe->default_str);
  }
  else
    if (oe->type == OPTIONS_TABLE_STYLE)
  {
    memcpy(&o->style, &grid_default_cell, sizeof(o->style));
    style_parse(&grid_default_cell, &o->style, oe->default_str);
  }
  else
    o->number = oe->default_num;
  return o;
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


const char *options_name(struct options_entry *o)
{
  return o->name;
}


/*** DEPENDENCIES:
None
----------------------------
***/


void options_array_clear(struct options_entry *o)
{
  if ((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_ARRAY))
  {
    o->arraysize = 0;
  }
}


/*** DEPENDENCIES:
None
----------------------------
***/


const char *options_array_get(struct options_entry *o, u_int idx)
{
  if (!((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_ARRAY)))
  {
    return 0;
  }
  if (idx >= o->arraysize)
  {
    return 0;
  }
  return o->array[idx];
}


/*** DEPENDENCIES:
None
----------------------------
***/


int options_array_size(struct options_entry *o, u_int *size)
{
  if (!((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_ARRAY)))
  {
    return -1;
  }
  if (size != 0)
  {
    *size = o->arraysize;
  }
  return 0;
}


/*** DEPENDENCIES:
None
----------------------------
***/


int options_isstring(struct options_entry *o)
{
  if (o->tableentry == 0)
  {
    return 1;
  }
  return ((o->tableentry == 0) || (o->tableentry->type == OPTIONS_TABLE_STRING)) || ((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_ARRAY));
}


/*** DEPENDENCIES:
None
----------------------------
***/


static struct options_entry *options_tree_RB_PREV(struct options_entry *elm)
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


struct options_entry *options_first(struct options *oo)
{
  return options_tree_RB_MINMAX(&oo->tree, -1);
}


/*** DEPENDENCIES:
static struct options_entry *options_tree_RB_MINMAX(struct options_tree *head, int val)
{
  struct options_entry *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct options_entry *parent = 0;
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


struct options_entry *options_next(struct options_entry *o)
{
  return options_tree_RB_NEXT(o);
}


/*** DEPENDENCIES:
static struct options_entry *options_tree_RB_NEXT(struct options_entry *elm)
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


const struct options_table_entry *options_table_entry(struct options_entry *o)
{
  return o->tableentry;
}


/*** DEPENDENCIES:
None
----------------------------
***/


static struct options_entry *options_tree_RB_NFIND(struct options_tree *head, struct options_entry *elm)
{
  struct options_entry *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct options_entry *res = 0;
  unsigned int res_idx = 0;
  int comp;
  while (tmp)
  {
    comp = options_cmp(elm, tmp);
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
static int options_cmp(struct options_entry *lhs, struct options_entry *rhs)
{
  return strcmp(lhs->name, rhs->name);
}


----------------------------
None
----------------------------
***/


struct options_entry *options_set_style(struct options *oo, const char *name, int append, const char *value)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  struct grid_cell gc;
  if ((*name) == '@')
  {
    fatalx("user option %s must be a string", name);
  }
  o_idx = options_get_only(oo, name);
  if ((((&o[o_idx]) != 0) && append) && ((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_STYLE)))
  {
    memcpy(&gc, &o->style, sizeof(gc));
  }
  else
    memcpy(&gc, &grid_default_cell, sizeof(gc));
  if (style_parse(&grid_default_cell, &gc, value) == (-1))
  {
    return 0;
  }
  if ((&o[o_idx]) == 0)
  {
    o_idx = options_default(oo, options_parent_table_entry(oo, name));
    if ((&o[o_idx]) == 0)
    {
      return 0;
    }
  }
  if (!((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_STYLE)))
  {
    fatalx("option %s is not a style", name);
  }
  memcpy(&o->style, &gc, sizeof(o->style));
  return o;
}


/*** DEPENDENCIES:
int style_parse(const struct grid_cell *defgc, struct grid_cell *gc, const char *in)
{
  unsigned int in_idx = 0;
  struct grid_cell savedgc;
  const char delimiters[] = " ,";
  char tmp[32];
  int val;
  int fg;
  int bg;
  int attr;
  int flags;
  size_t end;
  if (in[in_idx] == '\0')
  {
    return 0;
  }
  if (strchr(delimiters, in[(strlen(in) - 1) + in_idx]) != 0)
  {
    return -1;
  }
  memcpy(&savedgc, gc, sizeof(savedgc));
  fg = gc->fg;
  bg = gc->bg;
  attr = gc->attr;
  flags = gc->flags;
  do
  {
    helper_style_parse_1(&in_idx, &val, &fg, &bg, &attr, &flags, &end, defgc, in, delimiters, tmp);
  }
  while (in[in_idx] != '\0');
  gc->fg = fg;
  gc->bg = bg;
  gc->attr = attr;
  gc->flags = flags;
  return 0;
  error:
  memcpy(gc, &savedgc, sizeof(*gc));

  return -1;
}


----------------------------
extern const struct grid_cell grid_default_cell
----------------------------
const struct options_table_entry *options_parent_table_entry(struct options *oo, const char *s)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  if (oo->parent == 0)
  {
    fatalx("no parent options for %s", s);
  }
  o_idx = options_get_only(oo->parent, s);
  if ((&o[o_idx]) == 0)
  {
    fatalx("%s not in parent options", s);
  }
  return o->tableentry;
}


----------------------------
struct options_entry *options_default(struct options *oo, const struct options_table_entry *oe)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_empty(oo, oe);
  if (oe->type == OPTIONS_TABLE_ARRAY)
  {
    options_array_assign(o, oe->default_str);
  }
  else
    if (oe->type == OPTIONS_TABLE_STRING)
  {
    o->string = xstrdup(oe->default_str);
  }
  else
    if (oe->type == OPTIONS_TABLE_STYLE)
  {
    memcpy(&o->style, &grid_default_cell, sizeof(o->style));
    style_parse(&grid_default_cell, &o->style, oe->default_str);
  }
  else
    o->number = oe->default_num;
  return o;
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
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
struct options_entry *options_get_only(struct options *oo, const char *name)
{
  struct options_entry o;
  o.name = name;
  return options_tree_RB_FIND(&oo->tree, &o);
}


----------------------------
None
----------------------------
***/


void options_style_update_new(struct options *oo, struct options_entry *o)
{
  const char *newname = o->tableentry->style;
  struct options_entry *new;
  unsigned int new_idx = 0;
  if (newname == 0)
  {
    return;
  }
  new_idx = options_get_only(oo, newname);
  if ((&new[new_idx]) == 0)
  {
    new_idx = options_set_style(oo, newname, 0, "default");
  }
  if (strstr(o->name, "-bg") != 0)
  {
    new->style.bg = o->number;
  }
  else
    if (strstr(o->name, "-fg") != 0)
  {
    new->style.fg = o->number;
  }
  else
    if (strstr(o->name, "-attr") != 0)
  {
    new->style.attr = o->number;
  }
}


/*** DEPENDENCIES:
struct options_entry *options_get_only(struct options *oo, const char *name)
{
  struct options_entry o;
  o.name = name;
  return options_tree_RB_FIND(&oo->tree, &o);
}


----------------------------
struct options_entry *options_set_style(struct options *oo, const char *name, int append, const char *value)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  struct grid_cell gc;
  if ((*name) == '@')
  {
    fatalx("user option %s must be a string", name);
  }
  o_idx = options_get_only(oo, name);
  if ((((&o[o_idx]) != 0) && append) && ((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_STYLE)))
  {
    memcpy(&gc, &o->style, sizeof(gc));
  }
  else
    memcpy(&gc, &grid_default_cell, sizeof(gc));
  if (style_parse(&grid_default_cell, &gc, value) == (-1))
  {
    return 0;
  }
  if ((&o[o_idx]) == 0)
  {
    o_idx = options_default(oo, options_parent_table_entry(oo, name));
    if ((&o[o_idx]) == 0)
    {
      return 0;
    }
  }
  if (!((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_STYLE)))
  {
    fatalx("option %s is not a style", name);
  }
  memcpy(&o->style, &gc, sizeof(o->style));
  return o;
}


----------------------------
None
----------------------------
***/


char *options_match(const char *s, int *idx, int *ambiguous)
{
  const struct options_table_entry *oe;
  unsigned int oe_idx = 0;
  const struct options_table_entry *found;
  unsigned int found_idx = 0;
  char *name;
  unsigned int name_idx = 0;
  size_t namelen;
  name_idx = options_parse(s, idx);
  if ((&name[name_idx]) == 0)
  {
    return 0;
  }
  namelen = strlen(name);
  if (name[name_idx] == '@')
  {
    *ambiguous = 0;
    return name;
  }
  found_idx = 0;
  for (oe_idx = options_table; oe->name != 0; oe_idx += 1)
  {
    if (strcmp(oe->name, name) == 0)
    {
      found_idx = &oe[oe_idx];
      break;
    }
    if (strncmp(oe->name, name, namelen) == 0)
    {
      if ((&found[found_idx]) != 0)
      {
        *ambiguous = 1;
        free(name);
        return 0;
      }
      found_idx = &oe[oe_idx];
    }
  }

  free(name);
  if ((&found[found_idx]) == 0)
  {
    *ambiguous = 0;
    return 0;
  }
  return xstrdup(found->name);
}


/*** DEPENDENCIES:
extern const struct options_table_entry options_table[]
----------------------------
char *options_parse(const char *name, int *idx)
{
  char *copy;
  unsigned int copy_idx = 0;
  char *cp;
  unsigned int cp_idx = 0;
  char *end;
  unsigned int end_idx = 0;
  if ((*name) == '\0')
  {
    return 0;
  }
  copy_idx = xstrdup(name);
  if ((cp_idx = strchr(copy, '[')) == 0)
  {
    *idx = -1;
    return copy;
  }
  end_idx = strchr((&cp[cp_idx]) + 1, ']');
  if ((((&end[end_idx]) == 0) || (end[1 + end_idx] != '\0')) || (!isdigit((u_char) end[(-1) + end_idx])))
  {
    free(copy);
    return 0;
  }
  if ((sscanf(cp, "[%d]", idx) != 1) || ((*idx) < 0))
  {
    free(copy);
    return 0;
  }
  cp[cp_idx] = '\0';
  return copy;
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


struct options_entry *options_match_get(struct options *oo, const char *s, int *idx, int only, int *ambiguous)
{
  char *name;
  unsigned int name_idx = 0;
  struct options_entry *o;
  unsigned int o_idx = 0;
  name_idx = options_match(s, idx, ambiguous);
  if ((&name[name_idx]) == 0)
  {
    return 0;
  }
  *ambiguous = 0;
  if (only)
  {
    o_idx = options_get_only(oo, name);
  }
  else
    o_idx = options_get(oo, name);
  free(name);
  return o;
}


/*** DEPENDENCIES:
struct options_entry *options_get_only(struct options *oo, const char *name)
{
  struct options_entry o;
  o.name = name;
  return options_tree_RB_FIND(&oo->tree, &o);
}


----------------------------
struct options_entry *options_get(struct options *oo, const char *name)
{
  unsigned int oo_idx = 0;
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_get_only(oo, name);
  while ((&o[o_idx]) == 0)
  {
    oo_idx = oo_idx->parent;
    if ((&oo[oo_idx]) == 0)
    {
      break;
    }
    o_idx = options_get_only(oo, name);
  }

  return o;
}


----------------------------
char *options_match(const char *s, int *idx, int *ambiguous)
{
  const struct options_table_entry *oe;
  unsigned int oe_idx = 0;
  const struct options_table_entry *found;
  unsigned int found_idx = 0;
  char *name;
  unsigned int name_idx = 0;
  size_t namelen;
  name_idx = options_parse(s, idx);
  if ((&name[name_idx]) == 0)
  {
    return 0;
  }
  namelen = strlen(name);
  if (name[name_idx] == '@')
  {
    *ambiguous = 0;
    return name;
  }
  found_idx = 0;
  for (oe_idx = options_table; oe->name != 0; oe_idx += 1)
  {
    if (strcmp(oe->name, name) == 0)
    {
      found_idx = &oe[oe_idx];
      break;
    }
    if (strncmp(oe->name, name, namelen) == 0)
    {
      if ((&found[found_idx]) != 0)
      {
        *ambiguous = 1;
        free(name);
        return 0;
      }
      found_idx = &oe[oe_idx];
    }
  }

  free(name);
  if ((&found[found_idx]) == 0)
  {
    *ambiguous = 0;
    return 0;
  }
  return xstrdup(found->name);
}


----------------------------
None
----------------------------
***/


void options_style_update_old(struct options *oo, struct options_entry *o)
{
  char newname[128];
  int size;
  size = strrchr(o->name, '-') - o->name;
  xsnprintf(newname, sizeof(newname), "%.*s-bg", size, o->name);
  if (options_get(oo, newname) != 0)
  {
    options_set_number(oo, newname, o->style.bg);
  }
  xsnprintf(newname, sizeof(newname), "%.*s-fg", size, o->name);
  if (options_get(oo, newname) != 0)
  {
    options_set_number(oo, newname, o->style.fg);
  }
  xsnprintf(newname, sizeof(newname), "%.*s-attr", size, o->name);
  if (options_get(oo, newname) != 0)
  {
    options_set_number(oo, newname, o->style.attr);
  }
}


/*** DEPENDENCIES:
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
struct options_entry *options_get(struct options *oo, const char *name)
{
  unsigned int oo_idx = 0;
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_get_only(oo, name);
  while ((&o[o_idx]) == 0)
  {
    oo_idx = oo_idx->parent;
    if ((&oo[oo_idx]) == 0)
    {
      break;
    }
    o_idx = options_get_only(oo, name);
  }

  return o;
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
***/


enum options_table_scope options_scope_from_flags(struct args *args, int window, struct cmd_find_state *fs, struct options **oo, char **cause)
{
  struct session *s = fs->s;
  struct winlink *wl = fs->wl;
  const char *target = args_get(args, 't');
  if (args_has(args, 's'))
  {
    *oo = global_options;
    return OPTIONS_TABLE_SERVER;
  }
  if (window || args_has(args, 'w'))
  {
    if (args_has(args, 'g'))
    {
      *oo = global_w_options;
      return OPTIONS_TABLE_WINDOW;
    }
    if (wl == 0)
    {
      if (target != 0)
      {
        xasprintf(cause, "no such window: %s", target);
      }
      else
        xasprintf(cause, "no current window");
      return OPTIONS_TABLE_NONE;
    }
    *oo = wl->window->options;
    return OPTIONS_TABLE_WINDOW;
  }
  else
  {
    if (args_has(args, 'g'))
    {
      *oo = global_s_options;
      return OPTIONS_TABLE_SESSION;
    }
    if (s == 0)
    {
      if (target != 0)
      {
        xasprintf(cause, "no such session: %s", target);
      }
      else
        xasprintf(cause, "no current session");
      return OPTIONS_TABLE_NONE;
    }
    *oo = s->options;
    return OPTIONS_TABLE_SESSION;
  }
}


/*** DEPENDENCIES:
None
----------------------------
const char *args_get(struct args *args, u_char ch)
{
  struct args_entry *entry;
  unsigned int entry_idx = 0;
  if ((entry_idx = args_find(args, ch)) == 0)
  {
    return 0;
  }
  return entry->value;
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
enum options_table_scope
{
  OPTIONS_TABLE_NONE,
  OPTIONS_TABLE_SERVER,
  OPTIONS_TABLE_SESSION,
  OPTIONS_TABLE_WINDOW
}
----------------------------
None
----------------------------
int args_has(struct args *args, u_char ch)
{
  return args_find(args, ch) != 0;
}


----------------------------
None
----------------------------
***/


