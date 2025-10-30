// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_format_entry_tree_RB_INSERT_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const elm, struct format_entry * const parent, struct format_entry * const tmp)
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
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_format_entry_tree_RB_INSERT_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const gparent, struct format_entry * const tmp, unsigned int gparent_idx)
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
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_format_entry_tree_RB_INSERT_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const elm, struct format_entry * const parent, struct format_entry * const gparent, struct format_entry * const tmp, unsigned int gparent_idx)
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
    helper_helper_helper_format_entry_tree_RB_INSERT_COLOR_1_2_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_format_entry_tree_RB_INSERT_COLOR_1_2_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
void helper_helper_helper_format_entry_tree_RB_INSERT_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const elm, struct format_entry * const parent, struct format_entry * const tmp)
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
void helper_helper_helper_format_entry_tree_RB_INSERT_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const gparent, struct format_entry * const tmp, unsigned int gparent_idx)
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
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_format_entry_tree_RB_INSERT_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const gparent, struct format_entry * const tmp, unsigned int gparent_idx)
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
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_format_entry_tree_RB_INSERT_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const elm, struct format_entry * const parent, struct format_entry * const tmp)
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
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_format_entry_tree_RB_INSERT_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const elm, struct format_entry * const parent, struct format_entry * const gparent, struct format_entry * const tmp, unsigned int gparent_idx)
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
    helper_helper_helper_format_entry_tree_RB_INSERT_COLOR_1_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_format_entry_tree_RB_INSERT_COLOR_1_1_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
void helper_helper_helper_format_entry_tree_RB_INSERT_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const gparent, struct format_entry * const tmp, unsigned int gparent_idx)
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
void helper_helper_helper_format_entry_tree_RB_INSERT_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const elm, struct format_entry * const parent, struct format_entry * const tmp)
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
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'gparent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_format_entry_tree_RB_INSERT_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const gparent_idx_ref, unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const elm, struct format_entry * const parent, struct format_entry * const gparent, struct format_entry * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int gparent_idx = *gparent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  gparent_idx = parent->entry.rbe_parent;
  if ((&parent[parent_idx]) == gparent->entry.rbe_left)
  {
    helper_helper_format_entry_tree_RB_INSERT_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  else
  {
    helper_helper_format_entry_tree_RB_INSERT_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *gparent_idx_ref = gparent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
void helper_helper_format_entry_tree_RB_INSERT_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const elm, struct format_entry * const parent, struct format_entry * const gparent, struct format_entry * const tmp, unsigned int gparent_idx)
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
    helper_helper_helper_format_entry_tree_RB_INSERT_COLOR_1_2_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_format_entry_tree_RB_INSERT_COLOR_1_2_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
void helper_helper_format_entry_tree_RB_INSERT_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const elm, struct format_entry * const parent, struct format_entry * const gparent, struct format_entry * const tmp, unsigned int gparent_idx)
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
    helper_helper_helper_format_entry_tree_RB_INSERT_COLOR_1_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_format_entry_tree_RB_INSERT_COLOR_1_1_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
***/


void format_entry_tree_RB_INSERT_COLOR(struct format_entry_tree *head, struct format_entry *elm)
{
  unsigned int elm_idx = 0;
  struct format_entry *parent;
  unsigned int parent_idx = 0;
  struct format_entry *gparent;
  unsigned int gparent_idx = 0;
  struct format_entry *tmp;
  unsigned int tmp_idx = 0;
  while ((parent_idx = elm->entry.rbe_parent) && (parent->entry.rbe_color == 1))
  {
    helper_format_entry_tree_RB_INSERT_COLOR_1(&elm_idx, &parent_idx, &gparent_idx, &tmp_idx, head, elm, parent, gparent, tmp);
  }

  head->rbh_root->entry.rbe_color = 0;
}


/*** DEPENDENCIES:
void helper_format_entry_tree_RB_INSERT_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const gparent_idx_ref, unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const elm, struct format_entry * const parent, struct format_entry * const gparent, struct format_entry * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int gparent_idx = *gparent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  gparent_idx = parent->entry.rbe_parent;
  if ((&parent[parent_idx]) == gparent->entry.rbe_left)
  {
    helper_helper_format_entry_tree_RB_INSERT_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  else
  {
    helper_helper_format_entry_tree_RB_INSERT_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *gparent_idx_ref = gparent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


static int format_entry_cmp(struct format_entry *fe1, struct format_entry *fe2)
{
  return strcmp(fe1->key, fe2->key);
}


/*** DEPENDENCIES:
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


struct format_entry *format_entry_tree_RB_INSERT(struct format_entry_tree *head, struct format_entry *elm)
{
  struct format_entry *tmp;
  unsigned int tmp_idx = 0;
  struct format_entry *parent = 0;
  unsigned int parent_idx = 0;
  int comp = 0;
  tmp_idx = head->rbh_root;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    comp = format_entry_cmp(elm, parent);
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
  format_entry_tree_RB_INSERT_COLOR(head, elm);
  return 0;
}


/*** DEPENDENCIES:
void format_entry_tree_RB_INSERT_COLOR(struct format_entry_tree *head, struct format_entry *elm)
{
  unsigned int elm_idx = 0;
  struct format_entry *parent;
  unsigned int parent_idx = 0;
  struct format_entry *gparent;
  unsigned int gparent_idx = 0;
  struct format_entry *tmp;
  unsigned int tmp_idx = 0;
  while ((parent_idx = elm->entry.rbe_parent) && (parent->entry.rbe_color == 1))
  {
    helper_format_entry_tree_RB_INSERT_COLOR_1(&elm_idx, &parent_idx, &gparent_idx, &tmp_idx, head, elm, parent, gparent, tmp);
  }

  head->rbh_root->entry.rbe_color = 0;
}


----------------------------
static int format_entry_cmp(struct format_entry *fe1, struct format_entry *fe2)
{
  return strcmp(fe1->key, fe2->key);
}


----------------------------
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


static void format_add_tv(struct format_tree *ft, const char *key, struct timeval *tv)
{
  struct format_entry *fe;
  unsigned int fe_idx = 0;
  struct format_entry *fe_now;
  unsigned int fe_now_idx = 0;
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
  fe->t = tv->tv_sec;
  fe->value = 0;
}


/*** DEPENDENCIES:
struct format_entry *format_entry_tree_RB_INSERT(struct format_entry_tree *head, struct format_entry *elm)
{
  struct format_entry *tmp;
  unsigned int tmp_idx = 0;
  struct format_entry *parent = 0;
  unsigned int parent_idx = 0;
  int comp = 0;
  tmp_idx = head->rbh_root;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    comp = format_entry_cmp(elm, parent);
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
  format_entry_tree_RB_INSERT_COLOR(head, elm);
  return 0;
}


----------------------------
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
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


static void format_cb_host(struct format_tree *ft, struct format_entry *fe)
{
  char host[255 + 1];
  if (gethostname(host, sizeof(host)) != 0)
  {
    fe->value = xstrdup("");
  }
  else
    fe->value = xstrdup(host);
}


/*** DEPENDENCIES:
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
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


static void format_add_cb(struct format_tree *ft, const char *key, format_cb cb)
{
  struct format_entry *fe;
  unsigned int fe_idx = 0;
  struct format_entry *fe_now;
  unsigned int fe_now_idx = 0;
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
  fe->cb = cb;
  fe->t = 0;
  fe->value = 0;
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
struct format_entry *format_entry_tree_RB_INSERT(struct format_entry_tree *head, struct format_entry *elm)
{
  struct format_entry *tmp;
  unsigned int tmp_idx = 0;
  struct format_entry *parent = 0;
  unsigned int parent_idx = 0;
  int comp = 0;
  tmp_idx = head->rbh_root;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    comp = format_entry_cmp(elm, parent);
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
  format_entry_tree_RB_INSERT_COLOR(head, elm);
  return 0;
}


----------------------------
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
typedef void (*format_cb)(struct format_tree *, struct format_entry *)
----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_format_job_tree_RB_REMOVE_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const parent, struct format_job * const tmp, unsigned int parent_idx)
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
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_format_job_tree_RB_REMOVE_COLOR_1_2_2_2(unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const parent, struct format_job * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct format_job *oright;
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
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_format_job_tree_RB_REMOVE_COLOR_1_2_2_1(unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const parent, struct format_job * const tmp, unsigned int parent_idx)
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
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_format_job_tree_RB_REMOVE_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const parent, struct format_job * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_format_job_tree_RB_REMOVE_COLOR_1_2_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_left)
  {
    tmp->entry.rbe_left->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_format_job_tree_RB_REMOVE_COLOR_1_2_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
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
void helper_helper_helper_helper_format_job_tree_RB_REMOVE_COLOR_1_2_2_2(unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const parent, struct format_job * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct format_job *oright;
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
void helper_helper_helper_helper_format_job_tree_RB_REMOVE_COLOR_1_2_2_1(unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const parent, struct format_job * const tmp, unsigned int parent_idx)
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
void helper_helper_format_job_tree_RB_REMOVE_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const parent, struct format_job * const elm, struct format_job * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_left;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_format_job_tree_RB_REMOVE_COLOR_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_format_job_tree_RB_REMOVE_COLOR_1_2_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
void helper_helper_helper_format_job_tree_RB_REMOVE_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const parent, struct format_job * const tmp, unsigned int parent_idx)
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
void helper_helper_helper_format_job_tree_RB_REMOVE_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const parent, struct format_job * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_format_job_tree_RB_REMOVE_COLOR_1_2_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_left)
  {
    tmp->entry.rbe_left->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_format_job_tree_RB_REMOVE_COLOR_1_2_2_1(&tmp_idx, head, parent, tmp, parent_idx);
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
void helper_helper_helper_helper_format_job_tree_RB_REMOVE_COLOR_1_1_2_1(unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const parent, struct format_job * const tmp, unsigned int parent_idx)
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
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_format_job_tree_RB_REMOVE_COLOR_1_1_2_2(unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const parent, struct format_job * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct format_job *oleft;
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
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_format_job_tree_RB_REMOVE_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const parent, struct format_job * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_format_job_tree_RB_REMOVE_COLOR_1_1_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_right)
  {
    tmp->entry.rbe_right->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_format_job_tree_RB_REMOVE_COLOR_1_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
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
void helper_helper_helper_helper_format_job_tree_RB_REMOVE_COLOR_1_1_2_1(unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const parent, struct format_job * const tmp, unsigned int parent_idx)
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
void helper_helper_helper_helper_format_job_tree_RB_REMOVE_COLOR_1_1_2_2(unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const parent, struct format_job * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct format_job *oleft;
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
void helper_helper_helper_format_job_tree_RB_REMOVE_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const parent, struct format_job * const tmp, unsigned int parent_idx)
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
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_format_job_tree_RB_REMOVE_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const parent, struct format_job * const elm, struct format_job * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_right;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_format_job_tree_RB_REMOVE_COLOR_1_1_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_format_job_tree_RB_REMOVE_COLOR_1_1_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
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
void helper_helper_helper_format_job_tree_RB_REMOVE_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const parent, struct format_job * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_format_job_tree_RB_REMOVE_COLOR_1_1_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_right)
  {
    tmp->entry.rbe_right->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_format_job_tree_RB_REMOVE_COLOR_1_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_helper_format_job_tree_RB_REMOVE_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const parent, struct format_job * const tmp, unsigned int parent_idx)
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
void helper_format_job_tree_RB_REMOVE_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const parent, struct format_job * const elm, struct format_job * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if (parent->entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_format_job_tree_RB_REMOVE_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  else
  {
    helper_helper_format_job_tree_RB_REMOVE_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
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
void helper_helper_format_job_tree_RB_REMOVE_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const parent, struct format_job * const elm, struct format_job * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_left;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_format_job_tree_RB_REMOVE_COLOR_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_format_job_tree_RB_REMOVE_COLOR_1_2_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_format_job_tree_RB_REMOVE_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const parent, struct format_job * const elm, struct format_job * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_right;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_format_job_tree_RB_REMOVE_COLOR_1_1_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_format_job_tree_RB_REMOVE_COLOR_1_1_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


static void format_job_tree_RB_REMOVE_COLOR(struct format_job_tree *head, struct format_job *parent, struct format_job *elm)
{
  unsigned int elm_idx = 0;
  unsigned int parent_idx = 0;
  struct format_job *tmp;
  unsigned int tmp_idx = 0;
  while ((((&elm[elm_idx]) == 0) || (elm->entry.rbe_color == 0)) && ((&elm[elm_idx]) != head->rbh_root))
  {
    helper_format_job_tree_RB_REMOVE_COLOR_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }

  if (elm)
  {
    elm->entry.rbe_color = 0;
  }
}


/*** DEPENDENCIES:
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
void helper_format_job_tree_RB_REMOVE_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const parent, struct format_job * const elm, struct format_job * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if (parent->entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_format_job_tree_RB_REMOVE_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  else
  {
    helper_helper_format_job_tree_RB_REMOVE_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
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
void helper_format_job_tree_RB_REMOVE_1(unsigned int * const elm_idx_ref, unsigned int * const child_idx_ref, unsigned int * const parent_idx_ref, int * const color_ref, struct format_job_tree * const head, struct format_job * const elm, struct format_job * const child, struct format_job * const parent, struct format_job * const old)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int child_idx = *child_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  int color = *color_ref;
  struct format_job *left;
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
None
----------------------------
***/


static struct format_job *format_job_tree_RB_REMOVE(struct format_job_tree *head, struct format_job *elm)
{
  unsigned int elm_idx = 0;
  struct format_job *child;
  unsigned int child_idx = 0;
  struct format_job *parent;
  unsigned int parent_idx = 0;
  struct format_job *old = elm;
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
    helper_format_job_tree_RB_REMOVE_1(&elm_idx, &child_idx, &parent_idx, &color, head, elm, child, parent, old);
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
    format_job_tree_RB_REMOVE_COLOR(head, parent, child);
  }

  return old;
}


/*** DEPENDENCIES:
static void format_job_tree_RB_REMOVE_COLOR(struct format_job_tree *head, struct format_job *parent, struct format_job *elm)
{
  unsigned int elm_idx = 0;
  unsigned int parent_idx = 0;
  struct format_job *tmp;
  unsigned int tmp_idx = 0;
  while ((((&elm[elm_idx]) == 0) || (elm->entry.rbe_color == 0)) && ((&elm[elm_idx]) != head->rbh_root))
  {
    helper_format_job_tree_RB_REMOVE_COLOR_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }

  if (elm)
  {
    elm->entry.rbe_color = 0;
  }
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
void helper_format_job_tree_RB_REMOVE_1(unsigned int * const elm_idx_ref, unsigned int * const child_idx_ref, unsigned int * const parent_idx_ref, int * const color_ref, struct format_job_tree * const head, struct format_job * const elm, struct format_job * const child, struct format_job * const parent, struct format_job * const old)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int child_idx = *child_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  int color = *color_ref;
  struct format_job *left;
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


static struct format_job *format_job_tree_RB_MINMAX(struct format_job_tree *head, int val)
{
  struct format_job *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct format_job *parent = 0;
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
None
----------------------------
***/


static struct format_job *format_job_tree_RB_NEXT(struct format_job *elm)
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
None
----------------------------
***/


static void format_job_tidy(struct format_job_tree *jobs, int force)
{
  struct format_job *fj;
  unsigned int fj_idx = 0;
  struct format_job *fj1;
  unsigned int fj1_idx = 0;
  time_t now;
  now = time(0);
  for (fj_idx = format_job_tree_RB_MINMAX(jobs, -1); ((&fj[fj_idx]) != 0) && ((fj1_idx = format_job_tree_RB_NEXT(fj), 1)); fj_idx = &fj1[fj1_idx])
  {
    if ((!force) && ((fj->last > now) || ((now - fj->last) < 3600)))
    {
      continue;
    }
    format_job_tree_RB_REMOVE(jobs, fj);
    log_debug("%s: %s", __func__, fj->cmd);
    if (fj->job != 0)
    {
      job_free(fj->job);
    }
    free((void *) fj->expanded);
    free((void *) fj->cmd);
    free(fj->out);
    free(fj);
  }

}


/*** DEPENDENCIES:
static struct format_job *format_job_tree_RB_REMOVE(struct format_job_tree *head, struct format_job *elm)
{
  unsigned int elm_idx = 0;
  struct format_job *child;
  unsigned int child_idx = 0;
  struct format_job *parent;
  unsigned int parent_idx = 0;
  struct format_job *old = elm;
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
    helper_format_job_tree_RB_REMOVE_1(&elm_idx, &child_idx, &parent_idx, &color, head, elm, child, parent, old);
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
    format_job_tree_RB_REMOVE_COLOR(head, parent, child);
  }

  return old;
}


----------------------------
pub time: Time
----------------------------
static struct format_job *format_job_tree_RB_MINMAX(struct format_job_tree *head, int val)
{
  struct format_job *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct format_job *parent = 0;
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
static struct format_job *format_job_tree_RB_NEXT(struct format_job *elm)
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
void job_free(struct job *job)
{
  log_debug("free job %p: %s", job, job->cmd);
  do
  {
    if (job->entry.le_next != 0)
    {
      job->entry.le_next->entry.le_prev = job->entry.le_prev;
    }
    *job->entry.le_prev = job->entry.le_next;
    ;
    ;
  }
  while (0);
  free(job->cmd);
  if ((job->freecb != 0) && (job->data != 0))
  {
    job->freecb(job->data);
  }
  if (job->pid != (-1))
  {
    kill(job->pid, SIGTERM);
  }
  if (job->event != 0)
  {
    bufferevent_free(job->event);
  }
  if (job->fd != (-1))
  {
    close(job->fd);
  }
  free(job);
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


static void format_job_timer(int fd, short events, void *arg)
{
  struct client *c;
  unsigned int c_idx = 0;
  struct timeval tv = {.tv_sec = 60};
  format_job_tidy(&format_jobs, 0);
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (c->jobs != 0)
    {
      format_job_tidy(c->jobs, 0);
    }
  }

  evtimer_del(&format_job_event);
  evtimer_add(&format_job_event, &tv);
}


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
}
----------------------------
static struct format_job_tree
{
  struct format_job *rbh_root;
} format_jobs = {0}
----------------------------
static struct event format_job_event
----------------------------
static void format_job_tidy(struct format_job_tree *jobs, int force)
{
  struct format_job *fj;
  unsigned int fj_idx = 0;
  struct format_job *fj1;
  unsigned int fj1_idx = 0;
  time_t now;
  now = time(0);
  for (fj_idx = format_job_tree_RB_MINMAX(jobs, -1); ((&fj[fj_idx]) != 0) && ((fj1_idx = format_job_tree_RB_NEXT(fj), 1)); fj_idx = &fj1[fj1_idx])
  {
    if ((!force) && ((fj->last > now) || ((now - fj->last) < 3600)))
    {
      continue;
    }
    format_job_tree_RB_REMOVE(jobs, fj);
    log_debug("%s: %s", __func__, fj->cmd);
    if (fj->job != 0)
    {
      job_free(fj->job);
    }
    free((void *) fj->expanded);
    free((void *) fj->cmd);
    free(fj->out);
    free(fj);
  }

}


----------------------------
None
----------------------------
***/


static void format_cb_pid(struct format_tree *ft, struct format_entry *fe)
{
  xasprintf(&fe->value, "%ld", (long) getpid());
}


/*** DEPENDENCIES:
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
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


struct format_entry *format_entry_tree_RB_NEXT(struct format_entry *elm)
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
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


struct format_entry *format_entry_tree_RB_MINMAX(struct format_entry_tree *head, int val)
{
  struct format_entry *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct format_entry *parent = 0;
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
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


static void format_merge(struct format_tree *ft, struct format_tree *from)
{
  struct format_entry *fe;
  unsigned int fe_idx = 0;
  for (fe_idx = format_entry_tree_RB_MINMAX(&from->tree, -1); (&fe[fe_idx]) != 0; fe_idx = format_entry_tree_RB_NEXT(fe_idx))
  {
    if (fe->value != 0)
    {
      format_add(ft, fe->key, "%s", fe->value);
    }
  }

}


/*** DEPENDENCIES:
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
struct format_entry *format_entry_tree_RB_NEXT(struct format_entry *elm)
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
struct format_entry *format_entry_tree_RB_MINMAX(struct format_entry_tree *head, int val)
{
  struct format_entry *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct format_entry *parent = 0;
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
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
None
----------------------------
***/


static void format_cb_host_short(struct format_tree *ft, struct format_entry *fe)
{
  char host[255 + 1];
  char *cp;
  unsigned int cp_idx = 0;
  if (gethostname(host, sizeof(host)) != 0)
  {
    fe->value = xstrdup("");
  }
  else
  {
    if ((cp_idx = strchr(host, '.')) != 0)
    {
      cp[cp_idx] = '\0';
    }
    fe->value = xstrdup(host);
  }
}


/*** DEPENDENCIES:
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
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


/*** DEPENDENCIES:
extern struct timeval start_time
----------------------------
extern const char *socket_path
----------------------------
static void format_add_tv(struct format_tree *ft, const char *key, struct timeval *tv)
{
  struct format_entry *fe;
  unsigned int fe_idx = 0;
  struct format_entry *fe_now;
  unsigned int fe_now_idx = 0;
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
  fe->t = tv->tv_sec;
  fe->value = 0;
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
static struct event format_job_event
----------------------------
static void format_cb_host(struct format_tree *ft, struct format_entry *fe)
{
  char host[255 + 1];
  if (gethostname(host, sizeof(host)) != 0)
  {
    fe->value = xstrdup("");
  }
  else
    fe->value = xstrdup(host);
}


----------------------------
static void format_add_cb(struct format_tree *ft, const char *key, format_cb cb)
{
  struct format_entry *fe;
  unsigned int fe_idx = 0;
  struct format_entry *fe_now;
  unsigned int fe_now_idx = 0;
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
  fe->cb = cb;
  fe->t = 0;
  fe->value = 0;
}


----------------------------
static void format_job_timer(int fd, short events, void *arg)
{
  struct client *c;
  unsigned int c_idx = 0;
  struct timeval tv = {.tv_sec = 60};
  format_job_tidy(&format_jobs, 0);
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (c->jobs != 0)
    {
      format_job_tidy(c->jobs, 0);
    }
  }

  evtimer_del(&format_job_event);
  evtimer_add(&format_job_event, &tv);
}


----------------------------
static void format_cb_pid(struct format_tree *ft, struct format_entry *fe)
{
  xasprintf(&fe->value, "%ld", (long) getpid());
}


----------------------------
static void format_merge(struct format_tree *ft, struct format_tree *from)
{
  struct format_entry *fe;
  unsigned int fe_idx = 0;
  for (fe_idx = format_entry_tree_RB_MINMAX(&from->tree, -1); (&fe[fe_idx]) != 0; fe_idx = format_entry_tree_RB_NEXT(fe_idx))
  {
    if (fe->value != 0)
    {
      format_add(ft, fe->key, "%s", fe->value);
    }
  }

}


----------------------------
static void format_cb_host_short(struct format_tree *ft, struct format_entry *fe)
{
  char host[255 + 1];
  char *cp;
  unsigned int cp_idx = 0;
  if (gethostname(host, sizeof(host)) != 0)
  {
    fe->value = xstrdup("");
  }
  else
  {
    if ((cp_idx = strchr(host, '.')) != 0)
    {
      cp[cp_idx] = '\0';
    }
    fe->value = xstrdup(host);
  }
}


----------------------------
None
----------------------------
***/


static char *format_skip(char *s)
{
  unsigned int s_idx = 0;
  int brackets = 0;
  for (; s[s_idx] != '\0'; s_idx += 1)
  {
    if (s[s_idx] == '{')
    {
      brackets += 1;
    }
    if (s[s_idx] == '}')
    {
      brackets -= 1;
    }
    if ((s[s_idx] == ',') && (brackets == 0))
    {
      break;
    }
  }

  if (s[s_idx] == '\0')
  {
    return 0;
  }
  return s;
}


/*** DEPENDENCIES:
***/


static int format_choose(char *s, char **left, char **right)
{
  char *cp;
  unsigned int cp_idx = 0;
  cp_idx = format_skip(s);
  if ((&cp[cp_idx]) == 0)
  {
    return -1;
  }
  cp[cp_idx] = '\0';
  *left = s;
  *right = (&cp[cp_idx]) + 1;
  return 0;
}


/*** DEPENDENCIES:
static char *format_skip(char *s)
{
  unsigned int s_idx = 0;
  int brackets = 0;
  for (; s[s_idx] != '\0'; s_idx += 1)
  {
    if (s[s_idx] == '{')
    {
      brackets += 1;
    }
    if (s[s_idx] == '}')
    {
      brackets -= 1;
    }
    if ((s[s_idx] == ',') && (brackets == 0))
    {
      break;
    }
  }

  if (s[s_idx] == '\0')
  {
    return 0;
  }
  return s;
}


----------------------------
***/


int format_true(const char *s)
{
  if (((s != 0) && ((*s) != '\0')) && ((s[0] != '0') || (s[1] != '\0')))
  {
    return 1;
  }
  return 0;
}


/*** DEPENDENCIES:
***/


// hint:  ['found_idx_ref is a mutable refrence to unsigned int']
char *helper_format_find_2(unsigned int * const found_idx_ref, struct format_tree * const ft, int modifiers, struct format_entry * const fe, static char s[64])
{
  unsigned int found_idx = *found_idx_ref;
  if (modifiers & 0x1)
  {
    if (fe->t == 0)
    {
      return 0;
    }
    ctime_r(&fe->t, s);
    s[strcspn(s, "\n")] = '\0';
    found_idx = s;
    goto found;
  }
  if (fe->t != 0)
  {
    xsnprintf(s, sizeof(s), "%lld", (long long) fe->t);
    found_idx = s;
    goto found;
  }
  if ((fe->value == 0) && (fe->cb != 0))
  {
    fe->cb(ft, fe);
    if (fe->value == 0)
    {
      fe->value = xstrdup("");
    }
  }
  found_idx = fe->value;
  goto found;
  *found_idx_ref = found_idx;
}


/*** DEPENDENCIES:
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
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
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


// hint:  ['o_idx_ref is a mutable refrence to unsigned int', 'found_idx_ref is a mutable refrence to unsigned int']
void helper_format_find_1(unsigned int * const o_idx_ref, unsigned int * const found_idx_ref, struct format_tree * const ft, const char * const key, struct options_entry * const o, int idx)
{
  unsigned int o_idx = *o_idx_ref;
  unsigned int found_idx = *found_idx_ref;
  o_idx = options_parse_get(global_options, key, &idx, 0);
  if (((&o[o_idx]) == 0) && (ft->w != 0))
  {
    o_idx = options_parse_get(ft->w->options, key, &idx, 0);
  }
  if ((&o[o_idx]) == 0)
  {
    o_idx = options_parse_get(global_w_options, key, &idx, 0);
  }
  if (((&o[o_idx]) == 0) && (ft->s != 0))
  {
    o_idx = options_parse_get(ft->s->options, key, &idx, 0);
  }
  if ((&o[o_idx]) == 0)
  {
    o_idx = options_parse_get(global_s_options, key, &idx, 0);
  }
  if ((&o[o_idx]) != 0)
  {
    found_idx = options_tostring(o, idx, 1);
    goto found;
  }
  *o_idx_ref = o_idx;
  *found_idx_ref = found_idx;
}


/*** DEPENDENCIES:
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


----------------------------
None
----------------------------
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


----------------------------
None
----------------------------
***/


struct format_entry *format_entry_tree_RB_FIND(struct format_entry_tree *head, struct format_entry *elm)
{
  struct format_entry *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  int comp;
  while (tmp)
  {
    comp = format_entry_cmp(elm, tmp);
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
static int format_entry_cmp(struct format_entry *fe1, struct format_entry *fe2)
{
  return strcmp(fe1->key, fe2->key);
}


----------------------------
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


static char *format_find(struct format_tree *ft, const char *key, int modifiers)
{
  struct format_entry *fe;
  unsigned int fe_idx = 0;
  struct format_entry fe_find;
  struct environ_entry *envent;
  unsigned int envent_idx = 0;
  static char s[64];
  struct options_entry *o;
  unsigned int o_idx = 0;
  const char *found;
  unsigned int found_idx = 0;
  int idx;
  char *copy;
  unsigned int copy_idx = 0;
  char *saved;
  unsigned int saved_idx = 0;
  if ((~modifiers) & 0x1)
  {
    helper_format_find_1(&o_idx, &found_idx, ft, key, o, idx);
  }
  found_idx = 0;
  fe_find.key = (char *) key;
  fe_idx = format_entry_tree_RB_FIND(&ft->tree, &fe_find);
  if ((&fe[fe_idx]) != 0)
  {
    helper_format_find_2(&found_idx, ft, modifiers, fe, s);
  }
  if ((~modifiers) & 0x1)
  {
    envent_idx = 0;
    if (ft->s != 0)
    {
      envent_idx = environ_find(ft->s->environ, key);
    }
    if ((&envent[envent_idx]) == 0)
    {
      envent_idx = environ_find(global_environ, key);
    }
    if ((&envent[envent_idx]) != 0)
    {
      found_idx = envent->value;
      goto found;
    }
  }
  return 0;
  found:
  if ((&found[found_idx]) == 0)
  {
    return 0;
  }

  copy_idx = xstrdup(found);
  if (modifiers & 0x2)
  {
    saved_idx = &copy[copy_idx];
    copy_idx = xstrdup(basename(saved));
    free(saved);
  }
  if (modifiers & 0x4)
  {
    saved_idx = &copy[copy_idx];
    copy_idx = xstrdup(dirname(saved));
    free(saved);
  }
  return copy;
}


/*** DEPENDENCIES:
None
----------------------------
char *helper_format_find_2(unsigned int * const found_idx_ref, struct format_tree * const ft, int modifiers, struct format_entry * const fe, static char s[64])
{
  unsigned int found_idx = *found_idx_ref;
  if (modifiers & 0x1)
  {
    if (fe->t == 0)
    {
      return 0;
    }
    ctime_r(&fe->t, s);
    s[strcspn(s, "\n")] = '\0';
    found_idx = s;
    goto found;
  }
  if (fe->t != 0)
  {
    xsnprintf(s, sizeof(s), "%lld", (long long) fe->t);
    found_idx = s;
    goto found;
  }
  if ((fe->value == 0) && (fe->cb != 0))
  {
    fe->cb(ft, fe);
    if (fe->value == 0)
    {
      fe->value = xstrdup("");
    }
  }
  found_idx = fe->value;
  goto found;
  *found_idx_ref = found_idx;
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
struct environ_entry *environ_find(struct environ *env, const char *name)
{
  struct environ_entry envent;
  envent.name = (char *) name;
  return environ_RB_FIND(env, &envent);
}


----------------------------
void helper_format_find_1(unsigned int * const o_idx_ref, unsigned int * const found_idx_ref, struct format_tree * const ft, const char * const key, struct options_entry * const o, int idx)
{
  unsigned int o_idx = *o_idx_ref;
  unsigned int found_idx = *found_idx_ref;
  o_idx = options_parse_get(global_options, key, &idx, 0);
  if (((&o[o_idx]) == 0) && (ft->w != 0))
  {
    o_idx = options_parse_get(ft->w->options, key, &idx, 0);
  }
  if ((&o[o_idx]) == 0)
  {
    o_idx = options_parse_get(global_w_options, key, &idx, 0);
  }
  if (((&o[o_idx]) == 0) && (ft->s != 0))
  {
    o_idx = options_parse_get(ft->s->options, key, &idx, 0);
  }
  if ((&o[o_idx]) == 0)
  {
    o_idx = options_parse_get(global_s_options, key, &idx, 0);
  }
  if ((&o[o_idx]) != 0)
  {
    found_idx = options_tostring(o, idx, 1);
    goto found;
  }
  *o_idx_ref = o_idx;
  *found_idx_ref = found_idx;
}


----------------------------
None
----------------------------
struct format_entry *format_entry_tree_RB_FIND(struct format_entry_tree *head, struct format_entry *elm)
{
  struct format_entry *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  int comp;
  while (tmp)
  {
    comp = format_entry_cmp(elm, tmp);
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
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
None
----------------------------
***/


// hint:  ['copy_idx_ref is a mutable refrence to unsigned int', 'ptr_idx_ref is a mutable refrence to unsigned int', 'new_idx_ref is a mutable refrence to unsigned int', 'newlen_ref is a mutable refrence to size_t', 'used_ref is a mutable refrence to size_t']
void helper_helper_format_replace_5_1(unsigned int * const copy_idx_ref, unsigned int * const ptr_idx_ref, unsigned int * const new_idx_ref, size_t * const newlen_ref, size_t * const used_ref, char * const copy, char * const ptr, char * const new, char * const from, char * const to, size_t fromlen, size_t tolen)
{
  unsigned int copy_idx = *copy_idx_ref;
  unsigned int ptr_idx = *ptr_idx_ref;
  unsigned int new_idx = *new_idx_ref;
  size_t newlen = *newlen_ref;
  size_t used = *used_ref;
  if (strncmp(ptr, from, fromlen) != 0)
  {
    new[new_idx] = ptr[ptr_idx];
    ptr_idx += 1;
    new_idx += 1;
    continue;
  }
  used = (&new[new_idx]) - (&copy[copy_idx]);
  newlen += tolen;
  copy_idx = xrealloc(copy_idx, newlen);
  new_idx = (&copy[copy_idx]) + used;
  memcpy(new, to, tolen);
  new_idx += tolen;
  ptr_idx += fromlen;
  *copy_idx_ref = copy_idx;
  *ptr_idx_ref = ptr_idx;
  *new_idx_ref = new_idx;
  *newlen_ref = newlen;
  *used_ref = used;
}


/*** DEPENDENCIES:
void *xrealloc(void *ptr, size_t size)
{
  return xreallocarray(ptr, 1, size);
}


----------------------------
***/


// hint:  ['copy_idx_ref is a mutable refrence to unsigned int', 'ptr_idx_ref is a mutable refrence to unsigned int', 'new_idx_ref is a mutable refrence to unsigned int', 'value_idx_ref is a mutable refrence to unsigned int', 'newlen_ref is a mutable refrence to size_t', 'fromlen_ref is a mutable refrence to size_t', 'tolen_ref is a mutable refrence to size_t', 'used_ref is a mutable refrence to size_t']
void helper_format_replace_5(unsigned int * const copy_idx_ref, unsigned int * const ptr_idx_ref, unsigned int * const new_idx_ref, unsigned int * const value_idx_ref, size_t * const newlen_ref, size_t * const fromlen_ref, size_t * const tolen_ref, size_t * const used_ref, char * const copy, char * const ptr, char * const new, char * const value, char * const from, char * const to)
{
  unsigned int copy_idx = *copy_idx_ref;
  unsigned int ptr_idx = *ptr_idx_ref;
  unsigned int new_idx = *new_idx_ref;
  unsigned int value_idx = *value_idx_ref;
  size_t newlen = *newlen_ref;
  size_t fromlen = *fromlen_ref;
  size_t tolen = *tolen_ref;
  size_t used = *used_ref;
  fromlen = strlen(from);
  tolen = strlen(to);
  newlen = strlen(value) + 1;
  copy_idx = (new = &new[new_idx + new_idx]);
  for (ptr_idx = &value[value_idx]; ptr[ptr_idx] != '\0';)
  {
    helper_helper_format_replace_5_1(&copy_idx, &ptr_idx, &new_idx, &newlen, &used, copy, ptr, new, from, to, fromlen, tolen);
  }

  new[new_idx] = '\0';
  free(value);
  value_idx = &copy[copy_idx];
  *copy_idx_ref = copy_idx;
  *ptr_idx_ref = ptr_idx;
  *new_idx_ref = new_idx;
  *value_idx_ref = value_idx;
  *newlen_ref = newlen;
  *fromlen_ref = fromlen;
  *tolen_ref = tolen;
  *used_ref = used;
}


/*** DEPENDENCIES:
void helper_helper_format_replace_5_1(unsigned int * const copy_idx_ref, unsigned int * const ptr_idx_ref, unsigned int * const new_idx_ref, size_t * const newlen_ref, size_t * const used_ref, char * const copy, char * const ptr, char * const new, char * const from, char * const to, size_t fromlen, size_t tolen)
{
  unsigned int copy_idx = *copy_idx_ref;
  unsigned int ptr_idx = *ptr_idx_ref;
  unsigned int new_idx = *new_idx_ref;
  size_t newlen = *newlen_ref;
  size_t used = *used_ref;
  if (strncmp(ptr, from, fromlen) != 0)
  {
    new[new_idx] = ptr[ptr_idx];
    ptr_idx += 1;
    new_idx += 1;
    continue;
  }
  used = (&new[new_idx]) - (&copy[copy_idx]);
  newlen += tolen;
  copy_idx = xrealloc(copy_idx, newlen);
  new_idx = (&copy[copy_idx]) + used;
  memcpy(new, to, tolen);
  new_idx += tolen;
  ptr_idx += fromlen;
  *copy_idx_ref = copy_idx;
  *ptr_idx_ref = ptr_idx;
  *new_idx_ref = new_idx;
  *newlen_ref = newlen;
  *used_ref = used;
}


----------------------------
***/


// hint:  ['copy_idx_ref is a mutable refrence to unsigned int', 'from_idx_ref is a mutable refrence to unsigned int', 'to_idx_ref is a mutable refrence to unsigned int', 'modifiers_ref is a mutable refrence to int']
void helper_format_replace_4(unsigned int * const copy_idx_ref, unsigned int * const from_idx_ref, unsigned int * const to_idx_ref, int * const modifiers_ref, char * const copy, char * const copy0, unsigned int copy0_idx, char * const from, char * const to)
{
  unsigned int copy_idx = *copy_idx_ref;
  unsigned int from_idx = *from_idx_ref;
  unsigned int to_idx = *to_idx_ref;
  int modifiers = *modifiers_ref;
  if (copy[1 + copy_idx] != '/')
  {
    break;
  }
  from_idx = (&copy[copy_idx]) + 2;
  for (copy_idx = &from[from_idx]; (copy[copy_idx] != '\0') && (copy[copy_idx] != '/'); copy_idx += 1)
  {
    ;
  }

  if ((copy[0 + copy_idx] != '/') || ((&copy[copy_idx]) == (&from[from_idx])))
  {
    copy_idx = &copy0[copy0_idx];
    break;
  }
  copy[0 + copy_idx] = '\0';
  to_idx = (&copy[copy_idx]) + 1;
  for (copy_idx = &to[to_idx]; (copy[copy_idx] != '\0') && (copy[copy_idx] != '/'); copy_idx += 1)
  {
    ;
  }

  if ((copy[0 + copy_idx] != '/') || (copy[1 + copy_idx] != ':'))
  {
    copy_idx = &copy0[copy0_idx];
    break;
  }
  copy[0 + copy_idx] = '\0';
  modifiers |= 0x8;
  copy_idx += 2;
  break;
  *copy_idx_ref = copy_idx;
  *from_idx_ref = from_idx;
  *to_idx_ref = to_idx;
  *modifiers_ref = modifiers;
}


/*** DEPENDENCIES:
***/


// hint:  ['ptr_idx_ref is a mutable refrence to unsigned int', 'found_idx_ref is a mutable refrence to unsigned int', 'value_idx_ref is a mutable refrence to unsigned int']
void helper_format_replace_3(unsigned int * const ptr_idx_ref, unsigned int * const found_idx_ref, unsigned int * const value_idx_ref, struct format_tree * const ft, char * const copy, unsigned int copy_idx, char * const ptr, char * const found, char * const left, unsigned int left_idx, char * const right, unsigned int right_idx, int modifiers)
{
  unsigned int ptr_idx = *ptr_idx_ref;
  unsigned int found_idx = *found_idx_ref;
  unsigned int value_idx = *value_idx_ref;
  ptr_idx = format_skip(copy);
  if ((&ptr[ptr_idx]) == 0)
  {
    goto fail;
  }
  ptr[ptr_idx] = '\0';
  found_idx = format_find(ft, (&copy[copy_idx]) + 1, modifiers);
  if ((&found[found_idx]) == 0)
  {
    found_idx = format_expand(ft, (&copy[copy_idx]) + 1);
  }
  if (format_choose((&ptr[ptr_idx]) + 1, &(&left[left_idx]), &(&right[right_idx])) != 0)
  {
    goto fail;
  }
  if (format_true(found))
  {
    value_idx = format_expand(ft, left);
  }
  else
    value_idx = format_expand(ft, right);
  free(found);
  *ptr_idx_ref = ptr_idx;
  *found_idx_ref = found_idx;
  *value_idx_ref = value_idx;
}


/*** DEPENDENCIES:
static int format_choose(char *s, char **left, char **right)
{
  char *cp;
  unsigned int cp_idx = 0;
  cp_idx = format_skip(s);
  if ((&cp[cp_idx]) == 0)
  {
    return -1;
  }
  cp[cp_idx] = '\0';
  *left = s;
  *right = (&cp[cp_idx]) + 1;
  return 0;
}


----------------------------
static char *format_skip(char *s)
{
  unsigned int s_idx = 0;
  int brackets = 0;
  for (; s[s_idx] != '\0'; s_idx += 1)
  {
    if (s[s_idx] == '{')
    {
      brackets += 1;
    }
    if (s[s_idx] == '}')
    {
      brackets -= 1;
    }
    if ((s[s_idx] == ',') && (brackets == 0))
    {
      break;
    }
  }

  if (s[s_idx] == '\0')
  {
    return 0;
  }
  return s;
}


----------------------------
int format_true(const char *s)
{
  if (((s != 0) && ((*s) != '\0')) && ((s[0] != '0') || (s[1] != '\0')))
  {
    return 1;
  }
  return 0;
}


----------------------------
static char *format_find(struct format_tree *ft, const char *key, int modifiers)
{
  struct format_entry *fe;
  unsigned int fe_idx = 0;
  struct format_entry fe_find;
  struct environ_entry *envent;
  unsigned int envent_idx = 0;
  static char s[64];
  struct options_entry *o;
  unsigned int o_idx = 0;
  const char *found;
  unsigned int found_idx = 0;
  int idx;
  char *copy;
  unsigned int copy_idx = 0;
  char *saved;
  unsigned int saved_idx = 0;
  if ((~modifiers) & 0x1)
  {
    helper_format_find_1(&o_idx, &found_idx, ft, key, o, idx);
  }
  found_idx = 0;
  fe_find.key = (char *) key;
  fe_idx = format_entry_tree_RB_FIND(&ft->tree, &fe_find);
  if ((&fe[fe_idx]) != 0)
  {
    helper_format_find_2(&found_idx, ft, modifiers, fe, s);
  }
  if ((~modifiers) & 0x1)
  {
    envent_idx = 0;
    if (ft->s != 0)
    {
      envent_idx = environ_find(ft->s->environ, key);
    }
    if ((&envent[envent_idx]) == 0)
    {
      envent_idx = environ_find(global_environ, key);
    }
    if ((&envent[envent_idx]) != 0)
    {
      found_idx = envent->value;
      goto found;
    }
  }
  return 0;
  found:
  if ((&found[found_idx]) == 0)
  {
    return 0;
  }

  copy_idx = xstrdup(found);
  if (modifiers & 0x2)
  {
    saved_idx = &copy[copy_idx];
    copy_idx = xstrdup(basename(saved));
    free(saved);
  }
  if (modifiers & 0x4)
  {
    saved_idx = &copy[copy_idx];
    copy_idx = xstrdup(dirname(saved));
    free(saved);
  }
  return copy;
}


----------------------------
None
----------------------------
None
----------------------------
***/


// hint:  ['copy_idx_ref is a mutable refrence to unsigned int', 'limit_ref is a mutable refrence to long', 'compare_ref is a mutable refrence to int']
void helper_format_replace_1(unsigned int * const copy_idx_ref, long * const limit_ref, int * const compare_ref, char * const copy, char * const endptr)
{
  unsigned int copy_idx = *copy_idx_ref;
  long limit = *limit_ref;
  int compare = *compare_ref;
  if ((copy[1 + copy_idx] == '=') && (copy[2 + copy_idx] == ':'))
  {
    compare = 1;
    copy_idx += 3;
    break;
  }
  errno = 0;
  limit = strtol((&copy[copy_idx]) + 1, &endptr, 10);
  if ((errno == ERANGE) && ((limit == (-9223372036854775808L)) || (limit == 9223372036854775807L)))
  {
    break;
  }
  if ((*endptr) != ':')
  {
    break;
  }
  copy_idx = endptr + 1;
  break;
  *copy_idx_ref = copy_idx;
  *limit_ref = limit;
  *compare_ref = compare;
}


/*** DEPENDENCIES:
***/


static void format_job_complete(struct job *job)
{
  struct format_job *fj = job->data;
  char *line;
  unsigned int line_idx = 0;
  char *buf;
  unsigned int buf_idx = 0;
  size_t len;
  fj->job = 0;
  buf_idx = 0;
  if ((line_idx = evbuffer_readline(job->event->input)) == 0)
  {
    len = EVBUFFER_LENGTH(job->event->input);
    buf_idx = xmalloc(len + 1);
    if (len != 0)
    {
      memcpy(buf, EVBUFFER_DATA(job->event->input), len);
    }
    buf[len + buf_idx] = '\0';
  }
  else
    buf_idx = &line[line_idx];
  log_debug("%s: %p %s: %s", __func__, fj, fj->cmd, buf);
  if ((buf[buf_idx] != '\0') || (!fj->updated))
  {
    free(fj->out);
    fj->out = &buf[buf_idx];
  }
  else
    free(buf);
  if (fj->status)
  {
    if (fj->client != 0)
    {
      server_status_client(fj->client);
    }
    fj->status = 0;
  }
}


/*** DEPENDENCIES:
void server_status_client(struct client *c)
{
  c->flags |= 0x10;
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
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
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
None
----------------------------
***/


static void format_job_update(struct job *job)
{
  struct format_job *fj = job->data;
  struct evbuffer *evb = job->event->input;
  char *line = 0;
  unsigned int line_idx = 0;
  char *next;
  unsigned int next_idx = 0;
  time_t t;
  while ((next_idx = evbuffer_readline(evb)) != 0)
  {
    free(line);
    line_idx = &next[next_idx];
  }

  if ((&line[line_idx]) == 0)
  {
    return;
  }
  fj->updated = 1;
  free(fj->out);
  fj->out = &line[line_idx];
  log_debug("%s: %p %s: %s", __func__, fj, fj->cmd, fj->out);
  t = time(0);
  if (fj->status && (fj->last != t))
  {
    if (fj->client != 0)
    {
      server_status_client(fj->client);
    }
    fj->last = t;
  }
}


/*** DEPENDENCIES:
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
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
void server_status_client(struct client *c)
{
  c->flags |= 0x10;
}


----------------------------
pub time: Time
----------------------------
None
----------------------------
***/


static int format_job_cmp(struct format_job *fj1, struct format_job *fj2)
{
  if (fj1->tag < fj2->tag)
  {
    return -1;
  }
  if (fj1->tag > fj2->tag)
  {
    return 1;
  }
  return strcmp(fj1->cmd, fj2->cmd);
}


/*** DEPENDENCIES:
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
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_format_job_tree_RB_INSERT_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const elm, struct format_job * const parent, struct format_job * const tmp)
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
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_format_job_tree_RB_INSERT_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const gparent, struct format_job * const tmp, unsigned int gparent_idx)
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
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_format_job_tree_RB_INSERT_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const elm, struct format_job * const parent, struct format_job * const gparent, struct format_job * const tmp, unsigned int gparent_idx)
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
    helper_helper_helper_format_job_tree_RB_INSERT_COLOR_1_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_format_job_tree_RB_INSERT_COLOR_1_1_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
void helper_helper_helper_format_job_tree_RB_INSERT_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const elm, struct format_job * const parent, struct format_job * const tmp)
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
void helper_helper_helper_format_job_tree_RB_INSERT_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const gparent, struct format_job * const tmp, unsigned int gparent_idx)
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
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_format_job_tree_RB_INSERT_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const gparent, struct format_job * const tmp, unsigned int gparent_idx)
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
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_format_job_tree_RB_INSERT_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const elm, struct format_job * const parent, struct format_job * const tmp)
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
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_format_job_tree_RB_INSERT_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const elm, struct format_job * const parent, struct format_job * const gparent, struct format_job * const tmp, unsigned int gparent_idx)
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
    helper_helper_helper_format_job_tree_RB_INSERT_COLOR_1_2_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_format_job_tree_RB_INSERT_COLOR_1_2_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
void helper_helper_helper_format_job_tree_RB_INSERT_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const gparent, struct format_job * const tmp, unsigned int gparent_idx)
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
void helper_helper_helper_format_job_tree_RB_INSERT_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const elm, struct format_job * const parent, struct format_job * const tmp)
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
void helper_format_job_tree_RB_INSERT_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const gparent_idx_ref, unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const elm, struct format_job * const parent, struct format_job * const gparent, struct format_job * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int gparent_idx = *gparent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  gparent_idx = parent->entry.rbe_parent;
  if ((&parent[parent_idx]) == gparent->entry.rbe_left)
  {
    helper_helper_format_job_tree_RB_INSERT_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  else
  {
    helper_helper_format_job_tree_RB_INSERT_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *gparent_idx_ref = gparent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
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
void helper_helper_format_job_tree_RB_INSERT_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const elm, struct format_job * const parent, struct format_job * const gparent, struct format_job * const tmp, unsigned int gparent_idx)
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
    helper_helper_helper_format_job_tree_RB_INSERT_COLOR_1_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_format_job_tree_RB_INSERT_COLOR_1_1_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_format_job_tree_RB_INSERT_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const elm, struct format_job * const parent, struct format_job * const gparent, struct format_job * const tmp, unsigned int gparent_idx)
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
    helper_helper_helper_format_job_tree_RB_INSERT_COLOR_1_2_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_format_job_tree_RB_INSERT_COLOR_1_2_1(&tmp_idx, head, gparent, tmp, gparent_idx);
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


static void format_job_tree_RB_INSERT_COLOR(struct format_job_tree *head, struct format_job *elm)
{
  unsigned int elm_idx = 0;
  struct format_job *parent;
  unsigned int parent_idx = 0;
  struct format_job *gparent;
  unsigned int gparent_idx = 0;
  struct format_job *tmp;
  unsigned int tmp_idx = 0;
  while ((parent_idx = elm->entry.rbe_parent) && (parent->entry.rbe_color == 1))
  {
    helper_format_job_tree_RB_INSERT_COLOR_1(&elm_idx, &parent_idx, &gparent_idx, &tmp_idx, head, elm, parent, gparent, tmp);
  }

  head->rbh_root->entry.rbe_color = 0;
}


/*** DEPENDENCIES:
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
void helper_format_job_tree_RB_INSERT_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const gparent_idx_ref, unsigned int * const tmp_idx_ref, struct format_job_tree * const head, struct format_job * const elm, struct format_job * const parent, struct format_job * const gparent, struct format_job * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int gparent_idx = *gparent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  gparent_idx = parent->entry.rbe_parent;
  if ((&parent[parent_idx]) == gparent->entry.rbe_left)
  {
    helper_helper_format_job_tree_RB_INSERT_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  else
  {
    helper_helper_format_job_tree_RB_INSERT_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
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


static struct format_job *format_job_tree_RB_INSERT(struct format_job_tree *head, struct format_job *elm)
{
  struct format_job *tmp;
  unsigned int tmp_idx = 0;
  struct format_job *parent = 0;
  unsigned int parent_idx = 0;
  int comp = 0;
  tmp_idx = head->rbh_root;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    comp = format_job_cmp(elm, parent);
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
  format_job_tree_RB_INSERT_COLOR(head, elm);
  return 0;
}


/*** DEPENDENCIES:
static int format_job_cmp(struct format_job *fj1, struct format_job *fj2)
{
  if (fj1->tag < fj2->tag)
  {
    return -1;
  }
  if (fj1->tag > fj2->tag)
  {
    return 1;
  }
  return strcmp(fj1->cmd, fj2->cmd);
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
static void format_job_tree_RB_INSERT_COLOR(struct format_job_tree *head, struct format_job *elm)
{
  unsigned int elm_idx = 0;
  struct format_job *parent;
  unsigned int parent_idx = 0;
  struct format_job *gparent;
  unsigned int gparent_idx = 0;
  struct format_job *tmp;
  unsigned int tmp_idx = 0;
  while ((parent_idx = elm->entry.rbe_parent) && (parent->entry.rbe_color == 1))
  {
    helper_format_job_tree_RB_INSERT_COLOR_1(&elm_idx, &parent_idx, &gparent_idx, &tmp_idx, head, elm, parent, gparent, tmp);
  }

  head->rbh_root->entry.rbe_color = 0;
}


----------------------------
None
----------------------------
***/


static struct format_job *format_job_tree_RB_FIND(struct format_job_tree *head, struct format_job *elm)
{
  struct format_job *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  int comp;
  while (tmp)
  {
    comp = format_job_cmp(elm, tmp);
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
static int format_job_cmp(struct format_job *fj1, struct format_job *fj2)
{
  if (fj1->tag < fj2->tag)
  {
    return -1;
  }
  if (fj1->tag > fj2->tag)
  {
    return 1;
  }
  return strcmp(fj1->cmd, fj2->cmd);
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
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'child_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'color_ref is a mutable refrence to int']
void helper_format_entry_tree_RB_REMOVE_1(unsigned int * const elm_idx_ref, unsigned int * const child_idx_ref, unsigned int * const parent_idx_ref, int * const color_ref, struct format_entry_tree * const head, struct format_entry * const elm, struct format_entry * const child, struct format_entry * const parent, struct format_entry * const old)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int child_idx = *child_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  int color = *color_ref;
  struct format_entry *left;
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
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_2_2_1(unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const parent, struct format_entry * const tmp, unsigned int parent_idx)
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
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_2_2_2(unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const parent, struct format_entry * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct format_entry *oright;
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
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const parent, struct format_entry * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_2_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_left)
  {
    tmp->entry.rbe_left->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_2_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
void helper_helper_helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_2_2_1(unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const parent, struct format_entry * const tmp, unsigned int parent_idx)
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
void helper_helper_helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_2_2_2(unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const parent, struct format_entry * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct format_entry *oright;
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
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const parent, struct format_entry * const tmp, unsigned int parent_idx)
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
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const parent, struct format_entry * const elm, struct format_entry * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_left;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_2_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
void helper_helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const parent, struct format_entry * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_2_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_left)
  {
    tmp->entry.rbe_left->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_2_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const parent, struct format_entry * const tmp, unsigned int parent_idx)
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
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const parent, struct format_entry * const tmp, unsigned int parent_idx)
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
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_1_2_1(unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const parent, struct format_entry * const tmp, unsigned int parent_idx)
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
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_1_2_2(unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const parent, struct format_entry * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct format_entry *oleft;
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
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const parent, struct format_entry * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_1_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_right)
  {
    tmp->entry.rbe_right->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
void helper_helper_helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_1_2_1(unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const parent, struct format_entry * const tmp, unsigned int parent_idx)
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
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
void helper_helper_helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_1_2_2(unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const parent, struct format_entry * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct format_entry *oleft;
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
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const parent, struct format_entry * const elm, struct format_entry * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_right;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_1_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_1_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
void helper_helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const parent, struct format_entry * const tmp, unsigned int parent_idx)
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
void helper_helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const parent, struct format_entry * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_1_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_right)
  {
    tmp->entry.rbe_right->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_format_entry_tree_RB_REMOVE_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const parent, struct format_entry * const elm, struct format_entry * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if (parent->entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  else
  {
    helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
void helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const parent, struct format_entry * const elm, struct format_entry * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_left;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_2_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
void helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const parent, struct format_entry * const elm, struct format_entry * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_right;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_1_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_1_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
***/


void format_entry_tree_RB_REMOVE_COLOR(struct format_entry_tree *head, struct format_entry *parent, struct format_entry *elm)
{
  unsigned int elm_idx = 0;
  unsigned int parent_idx = 0;
  struct format_entry *tmp;
  unsigned int tmp_idx = 0;
  while ((((&elm[elm_idx]) == 0) || (elm->entry.rbe_color == 0)) && ((&elm[elm_idx]) != head->rbh_root))
  {
    helper_format_entry_tree_RB_REMOVE_COLOR_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }

  if (elm)
  {
    elm->entry.rbe_color = 0;
  }
}


/*** DEPENDENCIES:
void helper_format_entry_tree_RB_REMOVE_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct format_entry_tree * const head, struct format_entry * const parent, struct format_entry * const elm, struct format_entry * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if (parent->entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  else
  {
    helper_helper_format_entry_tree_RB_REMOVE_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


struct format_entry *format_entry_tree_RB_REMOVE(struct format_entry_tree *head, struct format_entry *elm)
{
  unsigned int elm_idx = 0;
  struct format_entry *child;
  unsigned int child_idx = 0;
  struct format_entry *parent;
  unsigned int parent_idx = 0;
  struct format_entry *old = elm;
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
    helper_format_entry_tree_RB_REMOVE_1(&elm_idx, &child_idx, &parent_idx, &color, head, elm, child, parent, old);
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
    format_entry_tree_RB_REMOVE_COLOR(head, parent, child);
  }

  return old;
}


/*** DEPENDENCIES:
void helper_format_entry_tree_RB_REMOVE_1(unsigned int * const elm_idx_ref, unsigned int * const child_idx_ref, unsigned int * const parent_idx_ref, int * const color_ref, struct format_entry_tree * const head, struct format_entry * const elm, struct format_entry * const child, struct format_entry * const parent, struct format_entry * const old)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int child_idx = *child_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  int color = *color_ref;
  struct format_entry *left;
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
void format_entry_tree_RB_REMOVE_COLOR(struct format_entry_tree *head, struct format_entry *parent, struct format_entry *elm)
{
  unsigned int elm_idx = 0;
  unsigned int parent_idx = 0;
  struct format_entry *tmp;
  unsigned int tmp_idx = 0;
  while ((((&elm[elm_idx]) == 0) || (elm->entry.rbe_color == 0)) && ((&elm[elm_idx]) != head->rbh_root))
  {
    helper_format_entry_tree_RB_REMOVE_COLOR_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }

  if (elm)
  {
    elm->entry.rbe_color = 0;
  }
}


----------------------------
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


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


/*** DEPENDENCIES:
struct format_entry *format_entry_tree_RB_MINMAX(struct format_entry_tree *head, int val)
{
  struct format_entry *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct format_entry *parent = 0;
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
struct format_entry *format_entry_tree_RB_NEXT(struct format_entry *elm)
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
void server_client_unref(struct client *c)
{
  log_debug("unref client %p (%d references)", c, c->references);
  c->references -= 1;
  if (c->references == 0)
  {
    event_once(-1, EV_TIMEOUT, server_client_free, c, 0);
  }
}


----------------------------
struct format_entry *format_entry_tree_RB_REMOVE(struct format_entry_tree *head, struct format_entry *elm)
{
  unsigned int elm_idx = 0;
  struct format_entry *child;
  unsigned int child_idx = 0;
  struct format_entry *parent;
  unsigned int parent_idx = 0;
  struct format_entry *old = elm;
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
    helper_format_entry_tree_RB_REMOVE_1(&elm_idx, &child_idx, &parent_idx, &color, head, elm, child, parent, old);
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
    format_entry_tree_RB_REMOVE_COLOR(head, parent, child);
  }

  return old;
}


----------------------------
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
None
----------------------------
***/


static void format_defaults_client(struct format_tree *ft, struct client *c)
{
  struct session *s;
  unsigned int s_idx = 0;
  const char *name;
  unsigned int name_idx = 0;
  struct tty *tty = &c->tty;
  const char *types[] = {"VT100", "VT101", "VT102", "VT220", "VT320", "VT420", "Unknown"};
  if (ft->s == 0)
  {
    ft->s = c->session;
  }
  format_add(ft, "client_name", "%s", c->name);
  format_add(ft, "client_pid", "%ld", (long) c->pid);
  format_add(ft, "client_height", "%u", tty->sy);
  format_add(ft, "client_width", "%u", tty->sx);
  format_add(ft, "client_tty", "%s", c->ttyname);
  format_add(ft, "client_control_mode", "%d", !(!(c->flags & 0x2000)));
  if (tty->term_name != 0)
  {
    format_add(ft, "client_termname", "%s", tty->term_name);
  }
  if (tty->term_name != 0)
  {
    format_add(ft, "client_termtype", "%s", types[tty->term_type]);
  }
  format_add_tv(ft, "client_created", &c->creation_time);
  format_add_tv(ft, "client_activity", &c->activity_time);
  format_add(ft, "client_written", "%zu", c->written);
  format_add(ft, "client_discarded", "%zu", c->discarded);
  name_idx = server_client_get_key_table(c);
  if (strcmp(c->keytable->name, name) == 0)
  {
    format_add(ft, "client_prefix", "%d", 0);
  }
  else
    format_add(ft, "client_prefix", "%d", 1);
  format_add(ft, "client_key_table", "%s", c->keytable->name);
  if (tty->flags & 0x8)
  {
    format_add(ft, "client_utf8", "%d", 1);
  }
  else
    format_add(ft, "client_utf8", "%d", 0);
  if (c->flags & 0x800)
  {
    format_add(ft, "client_readonly", "%d", 1);
  }
  else
    format_add(ft, "client_readonly", "%d", 0);
  s_idx = c->session;
  if ((&s[s_idx]) != 0)
  {
    format_add(ft, "client_session", "%s", s->name);
  }
  s_idx = c->last_session;
  if (((&s[s_idx]) != 0) && session_alive(s))
  {
    format_add(ft, "client_last_session", "%s", s->name);
  }
}


/*** DEPENDENCIES:
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
int session_alive(struct session *s)
{
  struct session *s_loop;
  unsigned int s_loop_idx = 0;
  for (s_loop_idx = sessions_RB_MINMAX(&sessions, -1); (&s_loop[s_loop_idx]) != 0; s_loop_idx = sessions_RB_NEXT(s_loop_idx))
  {
    if ((&s_loop[s_loop_idx]) == s)
    {
      return 1;
    }
  }

  return 0;
}


----------------------------
const char *server_client_get_key_table(struct client *c)
{
  struct session *s = c->session;
  const char *name;
  unsigned int name_idx = 0;
  if (s == 0)
  {
    return "root";
  }
  name_idx = options_get_string(s->options, "key-table");
  if (name[name_idx] == '\0')
  {
    return "root";
  }
  return name;
}


----------------------------
static void format_add_tv(struct format_tree *ft, const char *key, struct timeval *tv)
{
  struct format_entry *fe;
  unsigned int fe_idx = 0;
  struct format_entry *fe_now;
  unsigned int fe_now_idx = 0;
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
  fe->t = tv->tv_sec;
  fe->value = 0;
}


----------------------------
None
----------------------------
***/


static void format_cb_session_group_list(struct format_tree *ft, struct format_entry *fe)
{
  struct session *s = ft->s;
  struct session_group *sg;
  unsigned int sg_idx = 0;
  struct session *loop;
  unsigned int loop_idx = 0;
  struct evbuffer *buffer;
  unsigned int buffer_idx = 0;
  int size;
  if (s == 0)
  {
    return;
  }
  sg_idx = session_group_contains(s);
  if ((&sg[sg_idx]) == 0)
  {
    return;
  }
  buffer_idx = evbuffer_new();
  for (loop_idx = (&sg->sessions)->tqh_first; (&loop[loop_idx]) != 0; loop_idx = loop_idx->gentry.tqe_next)
  {
    if (EVBUFFER_LENGTH(buffer) > 0)
    {
      evbuffer_add(buffer, ",", 1);
    }
    evbuffer_add_printf(buffer, "%s", loop->name);
  }

  if ((size = EVBUFFER_LENGTH(buffer)) != 0)
  {
    xasprintf(&fe->value, "%.*s", size, EVBUFFER_DATA(buffer));
  }
  evbuffer_free(buffer);
}


/*** DEPENDENCIES:
struct session_group *session_group_contains(struct session *target)
{
  struct session_group *sg;
  unsigned int sg_idx = 0;
  struct session *s;
  unsigned int s_idx = 0;
  for (sg_idx = session_groups_RB_MINMAX(&session_groups, -1); (&sg[sg_idx]) != 0; sg_idx = session_groups_RB_NEXT(sg_idx))
  {
    for (s_idx = (&sg->sessions)->tqh_first; (&s[s_idx]) != 0; s_idx = s_idx->gentry.tqe_next)
    {
      if ((&s[s_idx]) == target)
      {
        return sg;
      }
    }

  }

  return 0;
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
struct sessions
{
  struct session *rbh_root;
}
----------------------------
struct session_group
{
  const char *name;
  struct 
  {
    struct session *tqh_first;
    struct session **tqh_last;
  } sessions;
  struct 
  {
    struct session_group *rbe_left;
    struct session_group *rbe_right;
    struct session_group *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
None
----------------------------
***/


static void format_cb_session_stack(struct format_tree *ft, struct format_entry *fe)
{
  struct session *s = ft->s;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  char result[1024];
  char tmp[16];
  if (s == 0)
  {
    return;
  }
  xsnprintf(result, sizeof(result), "%u", s->curw->idx);
  for (wl_idx = (&s->lastw)->tqh_first; (&wl[wl_idx]) != 0; wl_idx = wl_idx->sentry.tqe_next)
  {
    xsnprintf(tmp, sizeof(tmp), "%u", wl->idx);
    if ((*result) != '\0')
    {
      strlcat(result, ",", sizeof(result));
    }
    strlcat(result, tmp, sizeof(result));
  }

  fe->value = xstrdup(result);
}


/*** DEPENDENCIES:
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
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
None
----------------------------
***/


static void format_cb_session_alerts(struct format_tree *ft, struct format_entry *fe)
{
  struct session *s = ft->s;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  char alerts[1024];
  char tmp[16];
  if (s == 0)
  {
    return;
  }
  *alerts = '\0';
  for (wl_idx = winlinks_RB_MINMAX(&s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    if ((wl->flags & ((0x1 | 0x2) | 0x4)) == 0)
    {
      continue;
    }
    xsnprintf(tmp, sizeof(tmp), "%u", wl->idx);
    if ((*alerts) != '\0')
    {
      strlcat(alerts, ",", sizeof(alerts));
    }
    strlcat(alerts, tmp, sizeof(alerts));
    if (wl->flags & 0x2)
    {
      strlcat(alerts, "#", sizeof(alerts));
    }
    if (wl->flags & 0x1)
    {
      strlcat(alerts, "!", sizeof(alerts));
    }
    if (wl->flags & 0x4)
    {
      strlcat(alerts, "~", sizeof(alerts));
    }
  }

  fe->value = xstrdup(alerts);
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
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
None
----------------------------
***/


static void format_defaults_session(struct format_tree *ft, struct session *s)
{
  struct session_group *sg;
  unsigned int sg_idx = 0;
  ft->s = s;
  format_add(ft, "session_name", "%s", s->name);
  format_add(ft, "session_windows", "%u", winlink_count(&s->windows));
  format_add(ft, "session_width", "%u", s->sx);
  format_add(ft, "session_height", "%u", s->sy);
  format_add(ft, "session_id", "$%u", s->id);
  sg_idx = session_group_contains(s);
  format_add(ft, "session_grouped", "%d", (&sg[sg_idx]) != 0);
  if ((&sg[sg_idx]) != 0)
  {
    format_add(ft, "session_group", "%s", sg->name);
    format_add(ft, "session_group_size", "%u", session_group_count(sg));
    format_add_cb(ft, "session_group_list", format_cb_session_group_list);
  }
  format_add_tv(ft, "session_created", &s->creation_time);
  format_add_tv(ft, "session_last_attached", &s->last_attached_time);
  format_add_tv(ft, "session_activity", &s->activity_time);
  format_add(ft, "session_attached", "%u", s->attached);
  format_add(ft, "session_many_attached", "%d", s->attached > 1);
  format_add_cb(ft, "session_alerts", format_cb_session_alerts);
  format_add_cb(ft, "session_stack", format_cb_session_stack);
}


/*** DEPENDENCIES:
struct session_group *session_group_contains(struct session *target)
{
  struct session_group *sg;
  unsigned int sg_idx = 0;
  struct session *s;
  unsigned int s_idx = 0;
  for (sg_idx = session_groups_RB_MINMAX(&session_groups, -1); (&sg[sg_idx]) != 0; sg_idx = session_groups_RB_NEXT(sg_idx))
  {
    for (s_idx = (&sg->sessions)->tqh_first; (&s[s_idx]) != 0; s_idx = s_idx->gentry.tqe_next)
    {
      if ((&s[s_idx]) == target)
      {
        return sg;
      }
    }

  }

  return 0;
}


----------------------------
static void format_add_tv(struct format_tree *ft, const char *key, struct timeval *tv)
{
  struct format_entry *fe;
  unsigned int fe_idx = 0;
  struct format_entry *fe_now;
  unsigned int fe_now_idx = 0;
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
  fe->t = tv->tv_sec;
  fe->value = 0;
}


----------------------------
struct windows
{
  struct window *rbh_root;
}
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
static void format_cb_session_group_list(struct format_tree *ft, struct format_entry *fe)
{
  struct session *s = ft->s;
  struct session_group *sg;
  unsigned int sg_idx = 0;
  struct session *loop;
  unsigned int loop_idx = 0;
  struct evbuffer *buffer;
  unsigned int buffer_idx = 0;
  int size;
  if (s == 0)
  {
    return;
  }
  sg_idx = session_group_contains(s);
  if ((&sg[sg_idx]) == 0)
  {
    return;
  }
  buffer_idx = evbuffer_new();
  for (loop_idx = (&sg->sessions)->tqh_first; (&loop[loop_idx]) != 0; loop_idx = loop_idx->gentry.tqe_next)
  {
    if (EVBUFFER_LENGTH(buffer) > 0)
    {
      evbuffer_add(buffer, ",", 1);
    }
    evbuffer_add_printf(buffer, "%s", loop->name);
  }

  if ((size = EVBUFFER_LENGTH(buffer)) != 0)
  {
    xasprintf(&fe->value, "%.*s", size, EVBUFFER_DATA(buffer));
  }
  evbuffer_free(buffer);
}


----------------------------
static void format_cb_session_stack(struct format_tree *ft, struct format_entry *fe)
{
  struct session *s = ft->s;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  char result[1024];
  char tmp[16];
  if (s == 0)
  {
    return;
  }
  xsnprintf(result, sizeof(result), "%u", s->curw->idx);
  for (wl_idx = (&s->lastw)->tqh_first; (&wl[wl_idx]) != 0; wl_idx = wl_idx->sentry.tqe_next)
  {
    xsnprintf(tmp, sizeof(tmp), "%u", wl->idx);
    if ((*result) != '\0')
    {
      strlcat(result, ",", sizeof(result));
    }
    strlcat(result, tmp, sizeof(result));
  }

  fe->value = xstrdup(result);
}


----------------------------
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


----------------------------
static void format_cb_session_alerts(struct format_tree *ft, struct format_entry *fe)
{
  struct session *s = ft->s;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  char alerts[1024];
  char tmp[16];
  if (s == 0)
  {
    return;
  }
  *alerts = '\0';
  for (wl_idx = winlinks_RB_MINMAX(&s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    if ((wl->flags & ((0x1 | 0x2) | 0x4)) == 0)
    {
      continue;
    }
    xsnprintf(tmp, sizeof(tmp), "%u", wl->idx);
    if ((*alerts) != '\0')
    {
      strlcat(alerts, ",", sizeof(alerts));
    }
    strlcat(alerts, tmp, sizeof(alerts));
    if (wl->flags & 0x2)
    {
      strlcat(alerts, "#", sizeof(alerts));
    }
    if (wl->flags & 0x1)
    {
      strlcat(alerts, "!", sizeof(alerts));
    }
    if (wl->flags & 0x4)
    {
      strlcat(alerts, "~", sizeof(alerts));
    }
  }

  fe->value = xstrdup(alerts);
}


----------------------------
static void format_add_cb(struct format_tree *ft, const char *key, format_cb cb)
{
  struct format_entry *fe;
  unsigned int fe_idx = 0;
  struct format_entry *fe_now;
  unsigned int fe_now_idx = 0;
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
  fe->cb = cb;
  fe->t = 0;
  fe->value = 0;
}


----------------------------
u_int session_group_count(struct session_group *sg)
{
  struct session *s;
  unsigned int s_idx = 0;
  u_int n;
  n = 0;
  for (s_idx = (&sg->sessions)->tqh_first; (&s[s_idx]) != 0; s_idx = s_idx->gentry.tqe_next)
  {
    n += 1;
  }

  return n;
}


----------------------------
struct session_group
{
  const char *name;
  struct 
  {
    struct session *tqh_first;
    struct session **tqh_last;
  } sessions;
  struct 
  {
    struct session_group *rbe_left;
    struct session_group *rbe_right;
    struct session_group *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
None
----------------------------
***/


static void format_cb_current_command(struct format_tree *ft, struct format_entry *fe)
{
  struct window_pane *wp = ft->wp;
  char *cmd;
  unsigned int cmd_idx = 0;
  if (wp == 0)
  {
    return;
  }
  cmd_idx = osdep_get_name(wp->fd, wp->tty);
  if (((&cmd[cmd_idx]) == 0) || (cmd[cmd_idx] == '\0'))
  {
    free(cmd);
    cmd_idx = cmd_stringify_argv(wp->argc, wp->argv);
    if (((&cmd[cmd_idx]) == 0) || (cmd[cmd_idx] == '\0'))
    {
      free(cmd);
      cmd_idx = xstrdup(wp->shell);
    }
  }
  fe->value = parse_window_name(cmd);
  free(cmd);
}


/*** DEPENDENCIES:
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
char *parse_window_name(const char *in)
{
  char *copy;
  char *name;
  unsigned int name_idx = 0;
  char *ptr;
  unsigned int ptr_idx = 0;
  name_idx = (copy = xstrdup(in));
  if (strncmp(name, "exec ", (sizeof("exec ")) - 1) == 0)
  {
    name_idx = (name_idx + (sizeof("exec "))) - 1;
  }
  while ((name[name_idx] == ' ') || (name[name_idx] == '-'))
  {
    name_idx += 1;
  }

  if ((ptr_idx = strchr(name, ' ')) != 0)
  {
    ptr[ptr_idx] = '\0';
  }
  if (name[name_idx] != '\0')
  {
    ptr_idx = ((&name[name_idx]) + strlen(name)) - 1;
    while ((((&ptr[ptr_idx]) > (&name[name_idx])) && (!isalnum((u_char) (*(&ptr[ptr_idx]))))) && (!ispunct((u_char) (*(&ptr[ptr_idx])))))
    {
      ptr[ptr_idx] = '\0';
      ptr_idx -= 1;
    }

  }
  if (name[name_idx] == '/')
  {
    name_idx = basename(name_idx);
  }
  name_idx = xstrdup(name_idx);
  free(copy);
  return name;
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
char *osdep_get_name(int fd, char *tty)
{
  FILE *f;
  unsigned int f_idx = 0;
  char *path;
  char *buf;
  unsigned int buf_idx = 0;
  size_t len;
  int ch;
  pid_t pgrp;
  if ((pgrp = tcgetpgrp(fd)) == (-1))
  {
    return 0;
  }
  xasprintf(&path, "/proc/%lld/cmdline", (long long) pgrp);
  if ((f_idx = fopen(path, "r")) == 0)
  {
    free(path);
    return 0;
  }
  free(path);
  len = 0;
  buf_idx = 0;
  while ((ch = fgetc(f)) != EOF)
  {
    if (ch == '\0')
    {
      break;
    }
    buf_idx = xrealloc(buf_idx, len + 2);
    buf[len + buf_idx] = ch;
    len += 1;
  }

  if ((&buf[buf_idx]) != 0)
  {
    buf[len + buf_idx] = '\0';
  }
  fclose(f);
  return buf;
}


----------------------------
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
None
----------------------------
***/


static void format_cb_pane_tabs(struct format_tree *ft, struct format_entry *fe)
{
  struct window_pane *wp = ft->wp;
  struct evbuffer *buffer;
  unsigned int buffer_idx = 0;
  u_int i;
  int size;
  if (wp == 0)
  {
    return;
  }
  buffer_idx = evbuffer_new();
  for (i = 0; i < wp->base.grid->sx; i += 1)
  {
    if (!(wp->base.tabs[i >> 3] & (1 << (i & 0x7))))
    {
      continue;
    }
    if (EVBUFFER_LENGTH(buffer) > 0)
    {
      evbuffer_add(buffer, ",", 1);
    }
    evbuffer_add_printf(buffer, "%u", i);
  }

  if ((size = EVBUFFER_LENGTH(buffer)) != 0)
  {
    xasprintf(&fe->value, "%.*s", size, EVBUFFER_DATA(buffer));
  }
  evbuffer_free(buffer);
}


/*** DEPENDENCIES:
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
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


static void format_cb_start_command(struct format_tree *ft, struct format_entry *fe)
{
  struct window_pane *wp = ft->wp;
  if (wp == 0)
  {
    return;
  }
  fe->value = cmd_stringify_argv(wp->argc, wp->argv);
}


/*** DEPENDENCIES:
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
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
None
----------------------------
***/


static void format_cb_current_path(struct format_tree *ft, struct format_entry *fe)
{
  struct window_pane *wp = ft->wp;
  char *cwd;
  unsigned int cwd_idx = 0;
  if (wp == 0)
  {
    return;
  }
  cwd_idx = osdep_get_cwd(wp->fd);
  if ((&cwd[cwd_idx]) != 0)
  {
    fe->value = xstrdup(cwd);
  }
}


/*** DEPENDENCIES:
char *osdep_get_cwd(int fd)
{
  static char target[MAXPATHLEN + 1];
  char *path;
  pid_t pgrp;
  pid_t sid;
  ssize_t n;
  if ((pgrp = tcgetpgrp(fd)) == (-1))
  {
    return 0;
  }
  xasprintf(&path, "/proc/%lld/cwd", (long long) pgrp);
  n = readlink(path, target, MAXPATHLEN);
  free(path);
  if ((n == (-1)) && (ioctl(fd, TIOCGSID, &sid) != (-1)))
  {
    xasprintf(&path, "/proc/%lld/cwd", (long long) sid);
    n = readlink(path, target, MAXPATHLEN);
    free(path);
  }
  if (n > 0)
  {
    target[n] = '\0';
    return target;
  }
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
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
None
----------------------------
***/


static void format_cb_history_bytes(struct format_tree *ft, struct format_entry *fe)
{
  struct window_pane *wp = ft->wp;
  struct grid *gd;
  unsigned int gd_idx = 0;
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  unsigned long long size;
  u_int i;
  if (wp == 0)
  {
    return;
  }
  gd_idx = wp->base.grid;
  size = 0;
  for (i = 0; i < gd->hsize; i += 1)
  {
    gl_idx = &gd->linedata[i];
    size += gl->cellsize * (sizeof(*gl->celldata));
    size += gl->extdsize * (sizeof(*gl->extddata));
  }

  size += gd->hsize * (sizeof(*gd->linedata));
  xasprintf(&fe->value, "%llu", size);
}


/*** DEPENDENCIES:
None
----------------------------
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
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


void format_defaults_pane(struct format_tree *ft, struct window_pane *wp)
{
  struct grid *gd = wp->base.grid;
  int status = wp->status;
  u_int idx;
  if (ft->w == 0)
  {
    ft->w = wp->window;
  }
  ft->wp = wp;
  format_add(ft, "history_size", "%u", gd->hsize);
  format_add(ft, "history_limit", "%u", gd->hlimit);
  format_add_cb(ft, "history_bytes", format_cb_history_bytes);
  if (window_pane_index(wp, &idx) != 0)
  {
    fatalx("index not found");
  }
  format_add(ft, "pane_index", "%u", idx);
  format_add(ft, "pane_width", "%u", wp->sx);
  format_add(ft, "pane_height", "%u", wp->sy);
  format_add(ft, "pane_title", "%s", wp->base.title);
  format_add(ft, "pane_id", "%%%u", wp->id);
  format_add(ft, "pane_active", "%d", wp == wp->window->active);
  format_add(ft, "pane_input_off", "%d", !(!(wp->flags & 0x40)));
  format_add(ft, "pane_pipe", "%d", wp->pipe_fd != (-1));
  if ((wp->flags & 0x200) && WIFEXITED(status))
  {
    format_add(ft, "pane_dead_status", "%d", WEXITSTATUS(status));
  }
  format_add(ft, "pane_dead", "%d", wp->fd == (-1));
  if (window_pane_visible(wp))
  {
    format_add(ft, "pane_left", "%u", wp->xoff);
    format_add(ft, "pane_top", "%u", wp->yoff);
    format_add(ft, "pane_right", "%u", (wp->xoff + wp->sx) - 1);
    format_add(ft, "pane_bottom", "%u", (wp->yoff + wp->sy) - 1);
    format_add(ft, "pane_at_left", "%d", wp->xoff == 0);
    format_add(ft, "pane_at_top", "%d", wp->yoff == 0);
    format_add(ft, "pane_at_right", "%d", (wp->xoff + wp->sx) == wp->window->sx);
    format_add(ft, "pane_at_bottom", "%d", (wp->yoff + wp->sy) == wp->window->sy);
  }
  format_add(ft, "pane_in_mode", "%d", wp->screen != (&wp->base));
  if (wp->mode != 0)
  {
    format_add(ft, "pane_mode", "%s", wp->mode->name);
  }
  format_add(ft, "pane_synchronized", "%d", !(!options_get_number(wp->window->options, "synchronize-panes")));
  if (wp->searchstr != 0)
  {
    format_add(ft, "pane_search_string", "%s", wp->searchstr);
  }
  format_add(ft, "pane_tty", "%s", wp->tty);
  format_add(ft, "pane_pid", "%ld", (long) wp->pid);
  format_add_cb(ft, "pane_start_command", format_cb_start_command);
  format_add_cb(ft, "pane_current_command", format_cb_current_command);
  format_add_cb(ft, "pane_current_path", format_cb_current_path);
  format_add(ft, "cursor_x", "%u", wp->base.cx);
  format_add(ft, "cursor_y", "%u", wp->base.cy);
  format_add(ft, "scroll_region_upper", "%u", wp->base.rupper);
  format_add(ft, "scroll_region_lower", "%u", wp->base.rlower);
  window_copy_add_formats(wp, ft);
  format_add(ft, "alternate_on", "%d", (wp->saved_grid) ? (1) : (0));
  format_add(ft, "alternate_saved_x", "%u", wp->saved_cx);
  format_add(ft, "alternate_saved_y", "%u", wp->saved_cy);
  format_add(ft, "cursor_flag", "%d", !(!(wp->base.mode & 0x1)));
  format_add(ft, "insert_flag", "%d", !(!(wp->base.mode & 0x2)));
  format_add(ft, "keypad_cursor_flag", "%d", !(!(wp->base.mode & 0x4)));
  format_add(ft, "keypad_flag", "%d", !(!(wp->base.mode & 0x8)));
  format_add(ft, "wrap_flag", "%d", !(!(wp->base.mode & 0x10)));
  format_add(ft, "mouse_any_flag", "%d", !(!(wp->base.mode & ((0x20 | 0x40) | 0x1000))));
  format_add(ft, "mouse_standard_flag", "%d", !(!(wp->base.mode & 0x20)));
  format_add(ft, "mouse_button_flag", "%d", !(!(wp->base.mode & 0x40)));
  format_add(ft, "mouse_all_flag", "%d", !(!(wp->base.mode & 0x1000)));
  format_add_cb(ft, "pane_tabs", format_cb_pane_tabs);
}


/*** DEPENDENCIES:
static void format_cb_current_command(struct format_tree *ft, struct format_entry *fe)
{
  struct window_pane *wp = ft->wp;
  char *cmd;
  unsigned int cmd_idx = 0;
  if (wp == 0)
  {
    return;
  }
  cmd_idx = osdep_get_name(wp->fd, wp->tty);
  if (((&cmd[cmd_idx]) == 0) || (cmd[cmd_idx] == '\0'))
  {
    free(cmd);
    cmd_idx = cmd_stringify_argv(wp->argc, wp->argv);
    if (((&cmd[cmd_idx]) == 0) || (cmd[cmd_idx] == '\0'))
    {
      free(cmd);
      cmd_idx = xstrdup(wp->shell);
    }
  }
  fe->value = parse_window_name(cmd);
  free(cmd);
}


----------------------------
static void format_cb_pane_tabs(struct format_tree *ft, struct format_entry *fe)
{
  struct window_pane *wp = ft->wp;
  struct evbuffer *buffer;
  unsigned int buffer_idx = 0;
  u_int i;
  int size;
  if (wp == 0)
  {
    return;
  }
  buffer_idx = evbuffer_new();
  for (i = 0; i < wp->base.grid->sx; i += 1)
  {
    if (!(wp->base.tabs[i >> 3] & (1 << (i & 0x7))))
    {
      continue;
    }
    if (EVBUFFER_LENGTH(buffer) > 0)
    {
      evbuffer_add(buffer, ",", 1);
    }
    evbuffer_add_printf(buffer, "%u", i);
  }

  if ((size = EVBUFFER_LENGTH(buffer)) != 0)
  {
    xasprintf(&fe->value, "%.*s", size, EVBUFFER_DATA(buffer));
  }
  evbuffer_free(buffer);
}


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
static void format_cb_start_command(struct format_tree *ft, struct format_entry *fe)
{
  struct window_pane *wp = ft->wp;
  if (wp == 0)
  {
    return;
  }
  fe->value = cmd_stringify_argv(wp->argc, wp->argv);
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
static void format_cb_current_path(struct format_tree *ft, struct format_entry *fe)
{
  struct window_pane *wp = ft->wp;
  char *cwd;
  unsigned int cwd_idx = 0;
  if (wp == 0)
  {
    return;
  }
  cwd_idx = osdep_get_cwd(wp->fd);
  if ((&cwd[cwd_idx]) != 0)
  {
    fe->value = xstrdup(cwd);
  }
}


----------------------------
static void format_add_cb(struct format_tree *ft, const char *key, format_cb cb)
{
  struct format_entry *fe;
  unsigned int fe_idx = 0;
  struct format_entry *fe_now;
  unsigned int fe_now_idx = 0;
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
  fe->cb = cb;
  fe->t = 0;
  fe->value = 0;
}


----------------------------
static void format_cb_history_bytes(struct format_tree *ft, struct format_entry *fe)
{
  struct window_pane *wp = ft->wp;
  struct grid *gd;
  unsigned int gd_idx = 0;
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  unsigned long long size;
  u_int i;
  if (wp == 0)
  {
    return;
  }
  gd_idx = wp->base.grid;
  size = 0;
  for (i = 0; i < gd->hsize; i += 1)
  {
    gl_idx = &gd->linedata[i];
    size += gl->cellsize * (sizeof(*gl->celldata));
    size += gl->extdsize * (sizeof(*gl->extddata));
  }

  size += gd->hsize * (sizeof(*gd->linedata));
  xasprintf(&fe->value, "%llu", size);
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


----------------------------
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


----------------------------
None
----------------------------
***/


static void format_cb_window_stack_index(struct format_tree *ft, struct format_entry *fe)
{
  struct session *s = ft->wl->session;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  u_int idx;
  idx = 0;
  for (wl_idx = (&s->lastw)->tqh_first; (&wl[wl_idx]) != 0; wl_idx = wl_idx->sentry.tqe_next)
  {
    idx += 1;
    if ((&wl[wl_idx]) == ft->wl)
    {
      break;
    }
  }

  if ((&wl[wl_idx]) != 0)
  {
    xasprintf(&fe->value, "%u", idx);
  }
  else
    fe->value = xstrdup("0");
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
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
None
----------------------------
***/


static void format_cb_window_visible_layout(struct format_tree *ft, struct format_entry *fe)
{
  struct window *w = ft->w;
  if (w == 0)
  {
    return;
  }
  fe->value = layout_dump(w->layout_root);
}


/*** DEPENDENCIES:
char *layout_dump(struct layout_cell *root)
{
  char layout[1024];
  char *out;
  *layout = '\0';
  if (layout_append(root, layout, sizeof(layout)) != 0)
  {
    return 0;
  }
  xasprintf(&out, "%04hx,%s", layout_checksum(layout), layout);
  return out;
}


----------------------------
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
None
----------------------------
***/


static void format_cb_window_layout(struct format_tree *ft, struct format_entry *fe)
{
  struct window *w = ft->w;
  if (w == 0)
  {
    return;
  }
  if (w->saved_layout_root != 0)
  {
    fe->value = layout_dump(w->saved_layout_root);
  }
  else
    fe->value = layout_dump(w->layout_root);
}


/*** DEPENDENCIES:
char *layout_dump(struct layout_cell *root)
{
  char layout[1024];
  char *out;
  *layout = '\0';
  if (layout_append(root, layout, sizeof(layout)) != 0)
  {
    return 0;
  }
  xasprintf(&out, "%04hx,%s", layout_checksum(layout), layout);
  return out;
}


----------------------------
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
None
----------------------------
***/


void format_defaults_window(struct format_tree *ft, struct window *w)
{
  ft->w = w;
  format_add_tv(ft, "window_activity", &w->activity_time);
  format_add(ft, "window_id", "@%u", w->id);
  format_add(ft, "window_name", "%s", w->name);
  format_add(ft, "window_width", "%u", w->sx);
  format_add(ft, "window_height", "%u", w->sy);
  format_add_cb(ft, "window_layout", format_cb_window_layout);
  format_add_cb(ft, "window_visible_layout", format_cb_window_visible_layout);
  format_add(ft, "window_panes", "%u", window_count_panes(w));
  format_add(ft, "window_zoomed_flag", "%d", !(!(w->flags & 0x1000)));
}


/*** DEPENDENCIES:
static void format_cb_window_visible_layout(struct format_tree *ft, struct format_entry *fe)
{
  struct window *w = ft->w;
  if (w == 0)
  {
    return;
  }
  fe->value = layout_dump(w->layout_root);
}


----------------------------
static void format_add_tv(struct format_tree *ft, const char *key, struct timeval *tv)
{
  struct format_entry *fe;
  unsigned int fe_idx = 0;
  struct format_entry *fe_now;
  unsigned int fe_now_idx = 0;
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
  fe->t = tv->tv_sec;
  fe->value = 0;
}


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
static void format_add_cb(struct format_tree *ft, const char *key, format_cb cb)
{
  struct format_entry *fe;
  unsigned int fe_idx = 0;
  struct format_entry *fe_now;
  unsigned int fe_now_idx = 0;
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
  fe->cb = cb;
  fe->t = 0;
  fe->value = 0;
}


----------------------------
static void format_cb_window_layout(struct format_tree *ft, struct format_entry *fe)
{
  struct window *w = ft->w;
  if (w == 0)
  {
    return;
  }
  if (w->saved_layout_root != 0)
  {
    fe->value = layout_dump(w->saved_layout_root);
  }
  else
    fe->value = layout_dump(w->layout_root);
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
None
----------------------------
***/


static void format_defaults_winlink(struct format_tree *ft, struct winlink *wl)
{
  struct session *s = wl->session;
  struct window *w = wl->window;
  if (ft->w == 0)
  {
    ft->w = wl->window;
  }
  ft->wl = wl;
  format_defaults_window(ft, w);
  format_add(ft, "window_index", "%d", wl->idx);
  format_add_cb(ft, "window_stack_index", format_cb_window_stack_index);
  format_add(ft, "window_flags", "%s", window_printable_flags(wl));
  format_add(ft, "window_active", "%d", wl == s->curw);
  format_add(ft, "window_bell_flag", "%d", !(!(wl->flags & 0x1)));
  format_add(ft, "window_activity_flag", "%d", !(!(wl->flags & 0x2)));
  format_add(ft, "window_silence_flag", "%d", !(!(wl->flags & 0x4)));
  format_add(ft, "window_last_flag", "%d", !(!(wl == (&s->lastw)->tqh_first)));
  format_add(ft, "window_linked", "%d", session_is_linked(s, wl->window));
}


/*** DEPENDENCIES:
static void format_cb_window_stack_index(struct format_tree *ft, struct format_entry *fe)
{
  struct session *s = ft->wl->session;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  u_int idx;
  idx = 0;
  for (wl_idx = (&s->lastw)->tqh_first; (&wl[wl_idx]) != 0; wl_idx = wl_idx->sentry.tqe_next)
  {
    idx += 1;
    if ((&wl[wl_idx]) == ft->wl)
    {
      break;
    }
  }

  if ((&wl[wl_idx]) != 0)
  {
    xasprintf(&fe->value, "%u", idx);
  }
  else
    fe->value = xstrdup("0");
}


----------------------------
int session_is_linked(struct session *s, struct window *w)
{
  struct session_group *sg;
  unsigned int sg_idx = 0;
  if ((sg_idx = session_group_contains(s)) != 0)
  {
    return w->references != session_group_count(sg);
  }
  return w->references != 1;
}


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
void format_defaults_window(struct format_tree *ft, struct window *w)
{
  ft->w = w;
  format_add_tv(ft, "window_activity", &w->activity_time);
  format_add(ft, "window_id", "@%u", w->id);
  format_add(ft, "window_name", "%s", w->name);
  format_add(ft, "window_width", "%u", w->sx);
  format_add(ft, "window_height", "%u", w->sy);
  format_add_cb(ft, "window_layout", format_cb_window_layout);
  format_add_cb(ft, "window_visible_layout", format_cb_window_visible_layout);
  format_add(ft, "window_panes", "%u", window_count_panes(w));
  format_add(ft, "window_zoomed_flag", "%d", !(!(w->flags & 0x1000)));
}


----------------------------
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


----------------------------
static void format_add_cb(struct format_tree *ft, const char *key, format_cb cb)
{
  struct format_entry *fe;
  unsigned int fe_idx = 0;
  struct format_entry *fe_now;
  unsigned int fe_now_idx = 0;
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
  fe->cb = cb;
  fe->t = 0;
  fe->value = 0;
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
static void format_defaults_client(struct format_tree *ft, struct client *c)
{
  struct session *s;
  unsigned int s_idx = 0;
  const char *name;
  unsigned int name_idx = 0;
  struct tty *tty = &c->tty;
  const char *types[] = {"VT100", "VT101", "VT102", "VT220", "VT320", "VT420", "Unknown"};
  if (ft->s == 0)
  {
    ft->s = c->session;
  }
  format_add(ft, "client_name", "%s", c->name);
  format_add(ft, "client_pid", "%ld", (long) c->pid);
  format_add(ft, "client_height", "%u", tty->sy);
  format_add(ft, "client_width", "%u", tty->sx);
  format_add(ft, "client_tty", "%s", c->ttyname);
  format_add(ft, "client_control_mode", "%d", !(!(c->flags & 0x2000)));
  if (tty->term_name != 0)
  {
    format_add(ft, "client_termname", "%s", tty->term_name);
  }
  if (tty->term_name != 0)
  {
    format_add(ft, "client_termtype", "%s", types[tty->term_type]);
  }
  format_add_tv(ft, "client_created", &c->creation_time);
  format_add_tv(ft, "client_activity", &c->activity_time);
  format_add(ft, "client_written", "%zu", c->written);
  format_add(ft, "client_discarded", "%zu", c->discarded);
  name_idx = server_client_get_key_table(c);
  if (strcmp(c->keytable->name, name) == 0)
  {
    format_add(ft, "client_prefix", "%d", 0);
  }
  else
    format_add(ft, "client_prefix", "%d", 1);
  format_add(ft, "client_key_table", "%s", c->keytable->name);
  if (tty->flags & 0x8)
  {
    format_add(ft, "client_utf8", "%d", 1);
  }
  else
    format_add(ft, "client_utf8", "%d", 0);
  if (c->flags & 0x800)
  {
    format_add(ft, "client_readonly", "%d", 1);
  }
  else
    format_add(ft, "client_readonly", "%d", 0);
  s_idx = c->session;
  if ((&s[s_idx]) != 0)
  {
    format_add(ft, "client_session", "%s", s->name);
  }
  s_idx = c->last_session;
  if (((&s[s_idx]) != 0) && session_alive(s))
  {
    format_add(ft, "client_last_session", "%s", s->name);
  }
}


----------------------------
static void format_defaults_session(struct format_tree *ft, struct session *s)
{
  struct session_group *sg;
  unsigned int sg_idx = 0;
  ft->s = s;
  format_add(ft, "session_name", "%s", s->name);
  format_add(ft, "session_windows", "%u", winlink_count(&s->windows));
  format_add(ft, "session_width", "%u", s->sx);
  format_add(ft, "session_height", "%u", s->sy);
  format_add(ft, "session_id", "$%u", s->id);
  sg_idx = session_group_contains(s);
  format_add(ft, "session_grouped", "%d", (&sg[sg_idx]) != 0);
  if ((&sg[sg_idx]) != 0)
  {
    format_add(ft, "session_group", "%s", sg->name);
    format_add(ft, "session_group_size", "%u", session_group_count(sg));
    format_add_cb(ft, "session_group_list", format_cb_session_group_list);
  }
  format_add_tv(ft, "session_created", &s->creation_time);
  format_add_tv(ft, "session_last_attached", &s->last_attached_time);
  format_add_tv(ft, "session_activity", &s->activity_time);
  format_add(ft, "session_attached", "%u", s->attached);
  format_add(ft, "session_many_attached", "%d", s->attached > 1);
  format_add_cb(ft, "session_alerts", format_cb_session_alerts);
  format_add_cb(ft, "session_stack", format_cb_session_stack);
}


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
void format_defaults_pane(struct format_tree *ft, struct window_pane *wp)
{
  struct grid *gd = wp->base.grid;
  int status = wp->status;
  u_int idx;
  if (ft->w == 0)
  {
    ft->w = wp->window;
  }
  ft->wp = wp;
  format_add(ft, "history_size", "%u", gd->hsize);
  format_add(ft, "history_limit", "%u", gd->hlimit);
  format_add_cb(ft, "history_bytes", format_cb_history_bytes);
  if (window_pane_index(wp, &idx) != 0)
  {
    fatalx("index not found");
  }
  format_add(ft, "pane_index", "%u", idx);
  format_add(ft, "pane_width", "%u", wp->sx);
  format_add(ft, "pane_height", "%u", wp->sy);
  format_add(ft, "pane_title", "%s", wp->base.title);
  format_add(ft, "pane_id", "%%%u", wp->id);
  format_add(ft, "pane_active", "%d", wp == wp->window->active);
  format_add(ft, "pane_input_off", "%d", !(!(wp->flags & 0x40)));
  format_add(ft, "pane_pipe", "%d", wp->pipe_fd != (-1));
  if ((wp->flags & 0x200) && WIFEXITED(status))
  {
    format_add(ft, "pane_dead_status", "%d", WEXITSTATUS(status));
  }
  format_add(ft, "pane_dead", "%d", wp->fd == (-1));
  if (window_pane_visible(wp))
  {
    format_add(ft, "pane_left", "%u", wp->xoff);
    format_add(ft, "pane_top", "%u", wp->yoff);
    format_add(ft, "pane_right", "%u", (wp->xoff + wp->sx) - 1);
    format_add(ft, "pane_bottom", "%u", (wp->yoff + wp->sy) - 1);
    format_add(ft, "pane_at_left", "%d", wp->xoff == 0);
    format_add(ft, "pane_at_top", "%d", wp->yoff == 0);
    format_add(ft, "pane_at_right", "%d", (wp->xoff + wp->sx) == wp->window->sx);
    format_add(ft, "pane_at_bottom", "%d", (wp->yoff + wp->sy) == wp->window->sy);
  }
  format_add(ft, "pane_in_mode", "%d", wp->screen != (&wp->base));
  if (wp->mode != 0)
  {
    format_add(ft, "pane_mode", "%s", wp->mode->name);
  }
  format_add(ft, "pane_synchronized", "%d", !(!options_get_number(wp->window->options, "synchronize-panes")));
  if (wp->searchstr != 0)
  {
    format_add(ft, "pane_search_string", "%s", wp->searchstr);
  }
  format_add(ft, "pane_tty", "%s", wp->tty);
  format_add(ft, "pane_pid", "%ld", (long) wp->pid);
  format_add_cb(ft, "pane_start_command", format_cb_start_command);
  format_add_cb(ft, "pane_current_command", format_cb_current_command);
  format_add_cb(ft, "pane_current_path", format_cb_current_path);
  format_add(ft, "cursor_x", "%u", wp->base.cx);
  format_add(ft, "cursor_y", "%u", wp->base.cy);
  format_add(ft, "scroll_region_upper", "%u", wp->base.rupper);
  format_add(ft, "scroll_region_lower", "%u", wp->base.rlower);
  window_copy_add_formats(wp, ft);
  format_add(ft, "alternate_on", "%d", (wp->saved_grid) ? (1) : (0));
  format_add(ft, "alternate_saved_x", "%u", wp->saved_cx);
  format_add(ft, "alternate_saved_y", "%u", wp->saved_cy);
  format_add(ft, "cursor_flag", "%d", !(!(wp->base.mode & 0x1)));
  format_add(ft, "insert_flag", "%d", !(!(wp->base.mode & 0x2)));
  format_add(ft, "keypad_cursor_flag", "%d", !(!(wp->base.mode & 0x4)));
  format_add(ft, "keypad_flag", "%d", !(!(wp->base.mode & 0x8)));
  format_add(ft, "wrap_flag", "%d", !(!(wp->base.mode & 0x10)));
  format_add(ft, "mouse_any_flag", "%d", !(!(wp->base.mode & ((0x20 | 0x40) | 0x1000))));
  format_add(ft, "mouse_standard_flag", "%d", !(!(wp->base.mode & 0x20)));
  format_add(ft, "mouse_button_flag", "%d", !(!(wp->base.mode & 0x40)));
  format_add(ft, "mouse_all_flag", "%d", !(!(wp->base.mode & 0x1000)));
  format_add_cb(ft, "pane_tabs", format_cb_pane_tabs);
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
static void format_defaults_winlink(struct format_tree *ft, struct winlink *wl)
{
  struct session *s = wl->session;
  struct window *w = wl->window;
  if (ft->w == 0)
  {
    ft->w = wl->window;
  }
  ft->wl = wl;
  format_defaults_window(ft, w);
  format_add(ft, "window_index", "%d", wl->idx);
  format_add_cb(ft, "window_stack_index", format_cb_window_stack_index);
  format_add(ft, "window_flags", "%s", window_printable_flags(wl));
  format_add(ft, "window_active", "%d", wl == s->curw);
  format_add(ft, "window_bell_flag", "%d", !(!(wl->flags & 0x1)));
  format_add(ft, "window_activity_flag", "%d", !(!(wl->flags & 0x2)));
  format_add(ft, "window_silence_flag", "%d", !(!(wl->flags & 0x4)));
  format_add(ft, "window_last_flag", "%d", !(!(wl == (&s->lastw)->tqh_first)));
  format_add(ft, "window_linked", "%d", session_is_linked(s, wl->window));
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
None
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


struct format_entry *format_entry_tree_RB_PREV(struct format_entry *elm)
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
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


void format_lost_client(struct client *c)
{
  if (c->jobs != 0)
  {
    format_job_tidy(c->jobs, 1);
  }
  free(c->jobs);
}


/*** DEPENDENCIES:
static void format_job_tidy(struct format_job_tree *jobs, int force)
{
  struct format_job *fj;
  unsigned int fj_idx = 0;
  struct format_job *fj1;
  unsigned int fj1_idx = 0;
  time_t now;
  now = time(0);
  for (fj_idx = format_job_tree_RB_MINMAX(jobs, -1); ((&fj[fj_idx]) != 0) && ((fj1_idx = format_job_tree_RB_NEXT(fj), 1)); fj_idx = &fj1[fj1_idx])
  {
    if ((!force) && ((fj->last > now) || ((now - fj->last) < 3600)))
    {
      continue;
    }
    format_job_tree_RB_REMOVE(jobs, fj);
    log_debug("%s: %s", __func__, fj->cmd);
    if (fj->job != 0)
    {
      job_free(fj->job);
    }
    free((void *) fj->expanded);
    free((void *) fj->cmd);
    free(fj->out);
    free(fj);
  }

}


----------------------------
None
----------------------------
***/


static struct format_job *format_job_tree_RB_PREV(struct format_job *elm)
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
None
----------------------------
***/


struct format_entry *format_entry_tree_RB_NFIND(struct format_entry_tree *head, struct format_entry *elm)
{
  struct format_entry *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct format_entry *res = 0;
  unsigned int res_idx = 0;
  int comp;
  while (tmp)
  {
    comp = format_entry_cmp(elm, tmp);
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
static int format_entry_cmp(struct format_entry *fe1, struct format_entry *fe2)
{
  return strcmp(fe1->key, fe2->key);
}


----------------------------
struct format_entry
{
  char *key;
  char *value;
  time_t t;
  format_cb cb;
  struct 
  {
    struct format_entry *rbe_left;
    struct format_entry *rbe_right;
    struct format_entry *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


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


/*** DEPENDENCIES:
None
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


static struct format_job *format_job_tree_RB_NFIND(struct format_job_tree *head, struct format_job *elm)
{
  struct format_job *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct format_job *res = 0;
  unsigned int res_idx = 0;
  int comp;
  while (tmp)
  {
    comp = format_job_cmp(elm, tmp);
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
static int format_job_cmp(struct format_job *fj1, struct format_job *fj2)
{
  if (fj1->tag < fj2->tag)
  {
    return -1;
  }
  if (fj1->tag > fj2->tag)
  {
    return 1;
  }
  return strcmp(fj1->cmd, fj2->cmd);
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
None
----------------------------
***/


void format_defaults_paste_buffer(struct format_tree *ft, struct paste_buffer *pb)
{
  struct timeval tv;
  size_t size;
  char *s;
  unsigned int s_idx = 0;
  timerclear(&tv);
  tv.tv_sec = paste_buffer_created(pb);
  paste_buffer_data(pb, &size);
  format_add(ft, "buffer_size", "%zu", size);
  format_add(ft, "buffer_name", "%s", paste_buffer_name(pb));
  format_add_tv(ft, "buffer_created", &tv);
  s_idx = paste_make_sample(pb);
  format_add(ft, "buffer_sample", "%s", s);
  free(s);
}


/*** DEPENDENCIES:
time_t paste_buffer_created(struct paste_buffer *pb)
{
  return pb->created;
}


----------------------------
const char *paste_buffer_name(struct paste_buffer *pb)
{
  return pb->name;
}


----------------------------
static void format_add_tv(struct format_tree *ft, const char *key, struct timeval *tv)
{
  struct format_entry *fe;
  unsigned int fe_idx = 0;
  struct format_entry *fe_now;
  unsigned int fe_now_idx = 0;
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
  fe->t = tv->tv_sec;
  fe->value = 0;
}


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
char *paste_make_sample(struct paste_buffer *pb)
{
  char *buf;
  unsigned int buf_idx = 0;
  size_t len;
  size_t used;
  const int flags = (0x01 | 0x08) | 0x10;
  const size_t width = 200;
  len = pb->size;
  if (len > width)
  {
    len = width;
  }
  buf_idx = xreallocarray(0, len, 4 + 4);
  used = utf8_strvis(buf, pb->data, len, flags);
  if ((pb->size > width) || (used > width))
  {
    strlcpy((&buf[buf_idx]) + width, "...", 4);
  }
  return buf;
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


