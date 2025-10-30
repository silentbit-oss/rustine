static int wait_channel_cmp(struct wait_channel *wc1, struct wait_channel *wc2)
{
  return strcmp(wc1->name, wc2->name);
}


/*** DEPENDENCIES:
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


static struct wait_channel *wait_channels_RB_NEXT(struct wait_channel *elm)
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
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


static struct wait_channel *wait_channels_RB_PREV(struct wait_channel *elm)
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
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


static struct wait_channel *wait_channels_RB_MINMAX(struct wait_channels *head, int val)
{
  struct wait_channel *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct wait_channel *parent = 0;
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
struct wait_channels
{
  struct wait_channel *rbh_root;
}
----------------------------
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'child_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'color_ref is a mutable refrence to int']
void helper_wait_channels_RB_REMOVE_1(unsigned int * const elm_idx_ref, unsigned int * const child_idx_ref, unsigned int * const parent_idx_ref, int * const color_ref, struct wait_channels * const head, struct wait_channel * const elm, struct wait_channel * const child, struct wait_channel * const parent, struct wait_channel * const old)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int child_idx = *child_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  int color = *color_ref;
  struct wait_channel *left;
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
struct wait_channels
{
  struct wait_channel *rbh_root;
}
----------------------------
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_wait_channels_RB_INSERT_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const gparent, struct wait_channel * const tmp, unsigned int gparent_idx)
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
struct wait_channels
{
  struct wait_channel *rbh_root;
}
----------------------------
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_wait_channels_RB_INSERT_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const elm, struct wait_channel * const parent, struct wait_channel * const tmp)
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
struct wait_channels
{
  struct wait_channel *rbh_root;
}
----------------------------
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_wait_channels_RB_INSERT_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const gparent, struct wait_channel * const tmp, unsigned int gparent_idx)
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
struct wait_channels
{
  struct wait_channel *rbh_root;
}
----------------------------
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_wait_channels_RB_INSERT_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const elm, struct wait_channel * const parent, struct wait_channel * const tmp)
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
struct wait_channels
{
  struct wait_channel *rbh_root;
}
----------------------------
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_wait_channels_RB_REMOVE_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const parent, struct wait_channel * const tmp, unsigned int parent_idx)
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
struct wait_channels
{
  struct wait_channel *rbh_root;
}
----------------------------
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_wait_channels_RB_REMOVE_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const parent, struct wait_channel * const tmp, unsigned int parent_idx)
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
struct wait_channels
{
  struct wait_channel *rbh_root;
}
----------------------------
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_wait_channels_RB_REMOVE_COLOR_1_1_2_1(unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const parent, struct wait_channel * const tmp, unsigned int parent_idx)
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
struct wait_channels
{
  struct wait_channel *rbh_root;
}
----------------------------
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_wait_channels_RB_REMOVE_COLOR_1_1_2_2(unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const parent, struct wait_channel * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct wait_channel *oleft;
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
struct wait_channels
{
  struct wait_channel *rbh_root;
}
----------------------------
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_wait_channels_RB_REMOVE_COLOR_1_2_2_1(unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const parent, struct wait_channel * const tmp, unsigned int parent_idx)
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
struct wait_channels
{
  struct wait_channel *rbh_root;
}
----------------------------
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_wait_channels_RB_REMOVE_COLOR_1_2_2_2(unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const parent, struct wait_channel * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct wait_channel *oright;
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
struct wait_channels
{
  struct wait_channel *rbh_root;
}
----------------------------
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_wait_channels_RB_REMOVE_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const parent, struct wait_channel * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_wait_channels_RB_REMOVE_COLOR_1_1_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_right)
  {
    tmp->entry.rbe_right->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_wait_channels_RB_REMOVE_COLOR_1_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct wait_channels
{
  struct wait_channel *rbh_root;
}
----------------------------
void helper_helper_helper_helper_wait_channels_RB_REMOVE_COLOR_1_1_2_2(unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const parent, struct wait_channel * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct wait_channel *oleft;
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
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
void helper_helper_helper_helper_wait_channels_RB_REMOVE_COLOR_1_1_2_1(unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const parent, struct wait_channel * const tmp, unsigned int parent_idx)
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
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_wait_channels_RB_REMOVE_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const parent, struct wait_channel * const elm, struct wait_channel * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_right;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_wait_channels_RB_REMOVE_COLOR_1_1_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_wait_channels_RB_REMOVE_COLOR_1_1_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct wait_channels
{
  struct wait_channel *rbh_root;
}
----------------------------
void helper_helper_helper_wait_channels_RB_REMOVE_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const parent, struct wait_channel * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_wait_channels_RB_REMOVE_COLOR_1_1_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_right)
  {
    tmp->entry.rbe_right->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_wait_channels_RB_REMOVE_COLOR_1_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
void helper_helper_helper_wait_channels_RB_REMOVE_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const parent, struct wait_channel * const tmp, unsigned int parent_idx)
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
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_wait_channels_RB_REMOVE_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const parent, struct wait_channel * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_wait_channels_RB_REMOVE_COLOR_1_2_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_left)
  {
    tmp->entry.rbe_left->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_wait_channels_RB_REMOVE_COLOR_1_2_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct wait_channels
{
  struct wait_channel *rbh_root;
}
----------------------------
void helper_helper_helper_helper_wait_channels_RB_REMOVE_COLOR_1_2_2_1(unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const parent, struct wait_channel * const tmp, unsigned int parent_idx)
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
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
void helper_helper_helper_helper_wait_channels_RB_REMOVE_COLOR_1_2_2_2(unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const parent, struct wait_channel * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct wait_channel *oright;
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
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_wait_channels_RB_REMOVE_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const parent, struct wait_channel * const elm, struct wait_channel * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_left;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_wait_channels_RB_REMOVE_COLOR_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_wait_channels_RB_REMOVE_COLOR_1_2_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct wait_channels
{
  struct wait_channel *rbh_root;
}
----------------------------
void helper_helper_helper_wait_channels_RB_REMOVE_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const parent, struct wait_channel * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_wait_channels_RB_REMOVE_COLOR_1_2_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_left)
  {
    tmp->entry.rbe_left->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_wait_channels_RB_REMOVE_COLOR_1_2_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
void helper_helper_helper_wait_channels_RB_REMOVE_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const parent, struct wait_channel * const tmp, unsigned int parent_idx)
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


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_wait_channels_RB_REMOVE_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const parent, struct wait_channel * const elm, struct wait_channel * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if (parent->entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_wait_channels_RB_REMOVE_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  else
  {
    helper_helper_wait_channels_RB_REMOVE_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct wait_channels
{
  struct wait_channel *rbh_root;
}
----------------------------
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
void helper_helper_wait_channels_RB_REMOVE_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const parent, struct wait_channel * const elm, struct wait_channel * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_right;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_wait_channels_RB_REMOVE_COLOR_1_1_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_wait_channels_RB_REMOVE_COLOR_1_1_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_wait_channels_RB_REMOVE_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const parent, struct wait_channel * const elm, struct wait_channel * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_left;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_wait_channels_RB_REMOVE_COLOR_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_wait_channels_RB_REMOVE_COLOR_1_2_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
***/


static void wait_channels_RB_REMOVE_COLOR(struct wait_channels *head, struct wait_channel *parent, struct wait_channel *elm)
{
  unsigned int elm_idx = 0;
  unsigned int parent_idx = 0;
  struct wait_channel *tmp;
  unsigned int tmp_idx = 0;
  while ((((&elm[elm_idx]) == 0) || (elm->entry.rbe_color == 0)) && ((&elm[elm_idx]) != head->rbh_root))
  {
    helper_wait_channels_RB_REMOVE_COLOR_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }

  if (elm)
  {
    elm->entry.rbe_color = 0;
  }
}


/*** DEPENDENCIES:
struct wait_channels
{
  struct wait_channel *rbh_root;
}
----------------------------
void helper_wait_channels_RB_REMOVE_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const parent, struct wait_channel * const elm, struct wait_channel * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if (parent->entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_wait_channels_RB_REMOVE_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  else
  {
    helper_helper_wait_channels_RB_REMOVE_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


static struct wait_channel *wait_channels_RB_REMOVE(struct wait_channels *head, struct wait_channel *elm)
{
  unsigned int elm_idx = 0;
  struct wait_channel *child;
  unsigned int child_idx = 0;
  struct wait_channel *parent;
  unsigned int parent_idx = 0;
  struct wait_channel *old = elm;
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
    helper_wait_channels_RB_REMOVE_1(&elm_idx, &child_idx, &parent_idx, &color, head, elm, child, parent, old);
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
    wait_channels_RB_REMOVE_COLOR(head, parent, child);
  }

  return old;
}


/*** DEPENDENCIES:
struct wait_channels
{
  struct wait_channel *rbh_root;
}
----------------------------
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
void helper_wait_channels_RB_REMOVE_1(unsigned int * const elm_idx_ref, unsigned int * const child_idx_ref, unsigned int * const parent_idx_ref, int * const color_ref, struct wait_channels * const head, struct wait_channel * const elm, struct wait_channel * const child, struct wait_channel * const parent, struct wait_channel * const old)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int child_idx = *child_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  int color = *color_ref;
  struct wait_channel *left;
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
static void wait_channels_RB_REMOVE_COLOR(struct wait_channels *head, struct wait_channel *parent, struct wait_channel *elm)
{
  unsigned int elm_idx = 0;
  unsigned int parent_idx = 0;
  struct wait_channel *tmp;
  unsigned int tmp_idx = 0;
  while ((((&elm[elm_idx]) == 0) || (elm->entry.rbe_color == 0)) && ((&elm[elm_idx]) != head->rbh_root))
  {
    helper_wait_channels_RB_REMOVE_COLOR_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }

  if (elm)
  {
    elm->entry.rbe_color = 0;
  }
}


----------------------------
***/


static void cmd_wait_for_remove(struct wait_channel *wc)
{
  if (wc->locked)
  {
    return;
  }
  if ((!((&wc->waiters)->tqh_first == 0)) || (!wc->woken))
  {
    return;
  }
  log_debug("remove wait channel %s", wc->name);
  wait_channels_RB_REMOVE(&wait_channels, wc);
  free((void *) wc->name);
  free(wc);
}


/*** DEPENDENCIES:
struct wait_channels
{
  struct wait_channel *rbh_root;
}
----------------------------
static struct wait_channel *wait_channels_RB_REMOVE(struct wait_channels *head, struct wait_channel *elm)
{
  unsigned int elm_idx = 0;
  struct wait_channel *child;
  unsigned int child_idx = 0;
  struct wait_channel *parent;
  unsigned int parent_idx = 0;
  struct wait_channel *old = elm;
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
    helper_wait_channels_RB_REMOVE_1(&elm_idx, &child_idx, &parent_idx, &color, head, elm, child, parent, old);
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
    wait_channels_RB_REMOVE_COLOR(head, parent, child);
  }

  return old;
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
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


void cmd_wait_for_flush(void)
{
  struct wait_channel *wc;
  unsigned int wc_idx = 0;
  struct wait_channel *wc1;
  unsigned int wc1_idx = 0;
  struct wait_item *wi;
  unsigned int wi_idx = 0;
  struct wait_item *wi1;
  unsigned int wi1_idx = 0;
  for (wc_idx = wait_channels_RB_MINMAX(&wait_channels, -1); ((&wc[wc_idx]) != 0) && ((wc1_idx = wait_channels_RB_NEXT(wc), 1)); wc_idx = &wc1[wc1_idx])
  {
    for (wi_idx = (&wc->waiters)->tqh_first; ((&wi[wi_idx]) != 0) && ((wi1_idx = wi->entry.tqe_next, 1)); wi_idx = &wi1[wi1_idx])
    {
      wi->item->flags &= ~0x2;
      do
      {
        if (wi->entry.tqe_next != 0)
        {
          wi->entry.tqe_next->entry.tqe_prev = wi->entry.tqe_prev;
        }
        else
          (&wc->waiters)->tqh_last = wi->entry.tqe_prev;
        *wi->entry.tqe_prev = wi->entry.tqe_next;
        ;
        ;
      }
      while (0);
      free(wi);
    }

    wc->woken = 1;
    for (wi_idx = (&wc->lockers)->tqh_first; ((&wi[wi_idx]) != 0) && ((wi1_idx = wi->entry.tqe_next, 1)); wi_idx = &wi1[wi1_idx])
    {
      wi->item->flags &= ~0x2;
      do
      {
        if (wi->entry.tqe_next != 0)
        {
          wi->entry.tqe_next->entry.tqe_prev = wi->entry.tqe_prev;
        }
        else
          (&wc->lockers)->tqh_last = wi->entry.tqe_prev;
        *wi->entry.tqe_prev = wi->entry.tqe_next;
        ;
        ;
      }
      while (0);
      free(wi);
    }

    wc->locked = 0;
    cmd_wait_for_remove(wc);
  }

}


/*** DEPENDENCIES:
static struct wait_channel *wait_channels_RB_MINMAX(struct wait_channels *head, int val)
{
  struct wait_channel *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct wait_channel *parent = 0;
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
static void cmd_wait_for_remove(struct wait_channel *wc)
{
  if (wc->locked)
  {
    return;
  }
  if ((!((&wc->waiters)->tqh_first == 0)) || (!wc->woken))
  {
    return;
  }
  log_debug("remove wait channel %s", wc->name);
  wait_channels_RB_REMOVE(&wait_channels, wc);
  free((void *) wc->name);
  free(wc);
}


----------------------------
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
static struct wait_channel *wait_channels_RB_NEXT(struct wait_channel *elm)
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
struct wait_item
{
  struct cmdq_item *item;
  struct 
  {
    struct wait_item *tqe_next;
    struct wait_item **tqe_prev;
  } entry;
}
----------------------------
struct wait_channels
{
  struct wait_channel *rbh_root;
}
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_wait_channels_RB_INSERT_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const elm, struct wait_channel * const parent, struct wait_channel * const gparent, struct wait_channel * const tmp, unsigned int gparent_idx)
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
    helper_helper_helper_wait_channels_RB_INSERT_COLOR_1_2_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_wait_channels_RB_INSERT_COLOR_1_2_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct wait_channels
{
  struct wait_channel *rbh_root;
}
----------------------------
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
void helper_helper_helper_wait_channels_RB_INSERT_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const elm, struct wait_channel * const parent, struct wait_channel * const tmp)
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
void helper_helper_helper_wait_channels_RB_INSERT_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const gparent, struct wait_channel * const tmp, unsigned int gparent_idx)
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


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_wait_channels_RB_INSERT_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const elm, struct wait_channel * const parent, struct wait_channel * const gparent, struct wait_channel * const tmp, unsigned int gparent_idx)
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
    helper_helper_helper_wait_channels_RB_INSERT_COLOR_1_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_wait_channels_RB_INSERT_COLOR_1_1_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct wait_channels
{
  struct wait_channel *rbh_root;
}
----------------------------
void helper_helper_helper_wait_channels_RB_INSERT_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const elm, struct wait_channel * const parent, struct wait_channel * const tmp)
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
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
void helper_helper_helper_wait_channels_RB_INSERT_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const gparent, struct wait_channel * const tmp, unsigned int gparent_idx)
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
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'gparent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_wait_channels_RB_INSERT_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const gparent_idx_ref, unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const elm, struct wait_channel * const parent, struct wait_channel * const gparent, struct wait_channel * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int gparent_idx = *gparent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  gparent_idx = parent->entry.rbe_parent;
  if ((&parent[parent_idx]) == gparent->entry.rbe_left)
  {
    helper_helper_wait_channels_RB_INSERT_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  else
  {
    helper_helper_wait_channels_RB_INSERT_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *gparent_idx_ref = gparent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct wait_channels
{
  struct wait_channel *rbh_root;
}
----------------------------
void helper_helper_wait_channels_RB_INSERT_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const elm, struct wait_channel * const parent, struct wait_channel * const gparent, struct wait_channel * const tmp, unsigned int gparent_idx)
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
    helper_helper_helper_wait_channels_RB_INSERT_COLOR_1_2_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_wait_channels_RB_INSERT_COLOR_1_2_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
void helper_helper_wait_channels_RB_INSERT_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const elm, struct wait_channel * const parent, struct wait_channel * const gparent, struct wait_channel * const tmp, unsigned int gparent_idx)
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
    helper_helper_helper_wait_channels_RB_INSERT_COLOR_1_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_wait_channels_RB_INSERT_COLOR_1_1_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
***/


static void wait_channels_RB_INSERT_COLOR(struct wait_channels *head, struct wait_channel *elm)
{
  unsigned int elm_idx = 0;
  struct wait_channel *parent;
  unsigned int parent_idx = 0;
  struct wait_channel *gparent;
  unsigned int gparent_idx = 0;
  struct wait_channel *tmp;
  unsigned int tmp_idx = 0;
  while ((parent_idx = elm->entry.rbe_parent) && (parent->entry.rbe_color == 1))
  {
    helper_wait_channels_RB_INSERT_COLOR_1(&elm_idx, &parent_idx, &gparent_idx, &tmp_idx, head, elm, parent, gparent, tmp);
  }

  head->rbh_root->entry.rbe_color = 0;
}


/*** DEPENDENCIES:
struct wait_channels
{
  struct wait_channel *rbh_root;
}
----------------------------
void helper_wait_channels_RB_INSERT_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const gparent_idx_ref, unsigned int * const tmp_idx_ref, struct wait_channels * const head, struct wait_channel * const elm, struct wait_channel * const parent, struct wait_channel * const gparent, struct wait_channel * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int gparent_idx = *gparent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  gparent_idx = parent->entry.rbe_parent;
  if ((&parent[parent_idx]) == gparent->entry.rbe_left)
  {
    helper_helper_wait_channels_RB_INSERT_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  else
  {
    helper_helper_wait_channels_RB_INSERT_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *gparent_idx_ref = gparent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
***/


static struct wait_channel *wait_channels_RB_FIND(struct wait_channels *head, struct wait_channel *elm)
{
  struct wait_channel *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  int comp;
  while (tmp)
  {
    comp = wait_channel_cmp(elm, tmp);
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
struct wait_channels
{
  struct wait_channel *rbh_root;
}
----------------------------
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
static int wait_channel_cmp(struct wait_channel *wc1, struct wait_channel *wc2)
{
  return strcmp(wc1->name, wc2->name);
}


----------------------------
***/


static struct wait_channel *wait_channels_RB_NFIND(struct wait_channels *head, struct wait_channel *elm)
{
  struct wait_channel *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct wait_channel *res = 0;
  unsigned int res_idx = 0;
  int comp;
  while (tmp)
  {
    comp = wait_channel_cmp(elm, tmp);
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
struct wait_channels
{
  struct wait_channel *rbh_root;
}
----------------------------
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
static int wait_channel_cmp(struct wait_channel *wc1, struct wait_channel *wc2)
{
  return strcmp(wc1->name, wc2->name);
}


----------------------------
***/


static struct wait_channel *wait_channels_RB_INSERT(struct wait_channels *head, struct wait_channel *elm)
{
  struct wait_channel *tmp;
  unsigned int tmp_idx = 0;
  struct wait_channel *parent = 0;
  unsigned int parent_idx = 0;
  int comp = 0;
  tmp_idx = head->rbh_root;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    comp = wait_channel_cmp(elm, parent);
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
  wait_channels_RB_INSERT_COLOR(head, elm);
  return 0;
}


/*** DEPENDENCIES:
struct wait_channels
{
  struct wait_channel *rbh_root;
}
----------------------------
static void wait_channels_RB_INSERT_COLOR(struct wait_channels *head, struct wait_channel *elm)
{
  unsigned int elm_idx = 0;
  struct wait_channel *parent;
  unsigned int parent_idx = 0;
  struct wait_channel *gparent;
  unsigned int gparent_idx = 0;
  struct wait_channel *tmp;
  unsigned int tmp_idx = 0;
  while ((parent_idx = elm->entry.rbe_parent) && (parent->entry.rbe_color == 1))
  {
    helper_wait_channels_RB_INSERT_COLOR_1(&elm_idx, &parent_idx, &gparent_idx, &tmp_idx, head, elm, parent, gparent, tmp);
  }

  head->rbh_root->entry.rbe_color = 0;
}


----------------------------
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
static int wait_channel_cmp(struct wait_channel *wc1, struct wait_channel *wc2)
{
  return strcmp(wc1->name, wc2->name);
}


----------------------------
***/


static struct wait_channel *cmd_wait_for_add(const char *name)
{
  struct wait_channel *wc;
  unsigned int wc_idx = 0;
  wc_idx = xmalloc(sizeof(*wc_idx));
  wc->name = xstrdup(name);
  wc->locked = 0;
  wc->woken = 0;
  do
  {
    (&wc->waiters)->tqh_first = 0;
    (&wc->waiters)->tqh_last = &(&wc->waiters)->tqh_first;
  }
  while (0);
  do
  {
    (&wc->lockers)->tqh_first = 0;
    (&wc->lockers)->tqh_last = &(&wc->lockers)->tqh_first;
  }
  while (0);
  wait_channels_RB_INSERT(&wait_channels, wc);
  log_debug("add wait channel %s", wc->name);
  return wc;
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
static struct wait_channel *wait_channels_RB_INSERT(struct wait_channels *head, struct wait_channel *elm)
{
  struct wait_channel *tmp;
  unsigned int tmp_idx = 0;
  struct wait_channel *parent = 0;
  unsigned int parent_idx = 0;
  int comp = 0;
  tmp_idx = head->rbh_root;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    comp = wait_channel_cmp(elm, parent);
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
  wait_channels_RB_INSERT_COLOR(head, elm);
  return 0;
}


----------------------------
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
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
struct wait_channels
{
  struct wait_channel *rbh_root;
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
***/


static enum cmd_retval cmd_wait_for_unlock(struct cmdq_item *item, const char *name, struct wait_channel *wc)
{
  struct wait_item *wi;
  unsigned int wi_idx = 0;
  if ((wc == 0) || (!wc->locked))
  {
    cmdq_error(item, "channel %s not locked", name);
    return CMD_RETURN_ERROR;
  }
  if ((wi_idx = (&wc->lockers)->tqh_first) != 0)
  {
    wi->item->flags &= ~0x2;
    do
    {
      if (wi->entry.tqe_next != 0)
      {
        wi->entry.tqe_next->entry.tqe_prev = wi->entry.tqe_prev;
      }
      else
        (&wc->lockers)->tqh_last = wi->entry.tqe_prev;
      *wi->entry.tqe_prev = wi->entry.tqe_next;
      ;
      ;
    }
    while (0);
    free(wi);
  }
  else
  {
    wc->locked = 0;
    cmd_wait_for_remove(wc);
  }
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
static void cmd_wait_for_remove(struct wait_channel *wc)
{
  if (wc->locked)
  {
    return;
  }
  if ((!((&wc->waiters)->tqh_first == 0)) || (!wc->woken))
  {
    return;
  }
  log_debug("remove wait channel %s", wc->name);
  wait_channels_RB_REMOVE(&wait_channels, wc);
  free((void *) wc->name);
  free(wc);
}


----------------------------
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
enum cmd_retval
{
  CMD_RETURN_ERROR = -1,
  CMD_RETURN_NORMAL = 0,
  CMD_RETURN_WAIT,
  CMD_RETURN_STOP
}
----------------------------
struct wait_item
{
  struct cmdq_item *item;
  struct 
  {
    struct wait_item *tqe_next;
    struct wait_item **tqe_prev;
  } entry;
}
----------------------------
void cmdq_error(struct cmdq_item *item, const char *fmt, ...)
{
  struct client *c = item->client;
  struct cmd *cmd = item->cmd;
  va_list ap;
  char *msg;
  unsigned int msg_idx = 0;
  size_t msglen;
  char *tmp;
  unsigned int tmp_idx = 0;
  __builtin_va_start(ap);
  msglen = xvasprintf(&(&msg[msg_idx]), fmt, ap);
  ;
  log_debug("%s: %s", __func__, msg);
  if (c == 0)
  {
    cfg_add_cause("%s:%u: %s", cmd->file, cmd->line, msg);
  }
  else
    if ((c->session == 0) || (c->flags & 0x2000))
  {
    if ((~c->flags) & 0x10000)
    {
      tmp_idx = &msg[msg_idx];
      msg_idx = utf8_sanitize(tmp);
      free(tmp);
      msglen = strlen(msg);
    }
    evbuffer_add(c->stderr_data, msg, msglen);
    evbuffer_add(c->stderr_data, "\n", 1);
    server_client_push_stderr(c);
    c->retval = 1;
  }
  else
  {
    msg[msg_idx] = toupper((u_char) msg[msg_idx]);
    status_message_set(c, "%s", msg);
  }
  free(msg);
}


----------------------------
None
----------------------------
***/


static enum cmd_retval cmd_wait_for_signal(struct cmdq_item *item, const char *name, struct wait_channel *wc)
{
  unsigned int wc_idx = 0;
  struct wait_item *wi;
  unsigned int wi_idx = 0;
  struct wait_item *wi1;
  unsigned int wi1_idx = 0;
  if ((&wc[wc_idx]) == 0)
  {
    wc_idx = cmd_wait_for_add(name);
  }
  if (((&wc->waiters)->tqh_first == 0) && (!wc->woken))
  {
    log_debug("signal wait channel %s, no waiters", wc->name);
    wc->woken = 1;
    return CMD_RETURN_NORMAL;
  }
  log_debug("signal wait channel %s, with waiters", wc->name);
  for (wi_idx = (&wc->waiters)->tqh_first; ((&wi[wi_idx]) != 0) && ((wi1_idx = wi->entry.tqe_next, 1)); wi_idx = &wi1[wi1_idx])
  {
    wi->item->flags &= ~0x2;
    do
    {
      if (wi->entry.tqe_next != 0)
      {
        wi->entry.tqe_next->entry.tqe_prev = wi->entry.tqe_prev;
      }
      else
        (&wc->waiters)->tqh_last = wi->entry.tqe_prev;
      *wi->entry.tqe_prev = wi->entry.tqe_next;
      ;
      ;
    }
    while (0);
    free(wi);
  }

  cmd_wait_for_remove(wc);
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
static void cmd_wait_for_remove(struct wait_channel *wc)
{
  if (wc->locked)
  {
    return;
  }
  if ((!((&wc->waiters)->tqh_first == 0)) || (!wc->woken))
  {
    return;
  }
  log_debug("remove wait channel %s", wc->name);
  wait_channels_RB_REMOVE(&wait_channels, wc);
  free((void *) wc->name);
  free(wc);
}


----------------------------
static struct wait_channel *cmd_wait_for_add(const char *name)
{
  struct wait_channel *wc;
  unsigned int wc_idx = 0;
  wc_idx = xmalloc(sizeof(*wc_idx));
  wc->name = xstrdup(name);
  wc->locked = 0;
  wc->woken = 0;
  do
  {
    (&wc->waiters)->tqh_first = 0;
    (&wc->waiters)->tqh_last = &(&wc->waiters)->tqh_first;
  }
  while (0);
  do
  {
    (&wc->lockers)->tqh_first = 0;
    (&wc->lockers)->tqh_last = &(&wc->lockers)->tqh_first;
  }
  while (0);
  wait_channels_RB_INSERT(&wait_channels, wc);
  log_debug("add wait channel %s", wc->name);
  return wc;
}


----------------------------
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
enum cmd_retval
{
  CMD_RETURN_ERROR = -1,
  CMD_RETURN_NORMAL = 0,
  CMD_RETURN_WAIT,
  CMD_RETURN_STOP
}
----------------------------
struct wait_item
{
  struct cmdq_item *item;
  struct 
  {
    struct wait_item *tqe_next;
    struct wait_item **tqe_prev;
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
None
----------------------------
***/


static enum cmd_retval cmd_wait_for_lock(struct cmdq_item *item, const char *name, struct wait_channel *wc)
{
  unsigned int wc_idx = 0;
  struct wait_item *wi;
  unsigned int wi_idx = 0;
  if ((item->client == 0) || (item->client->session != 0))
  {
    cmdq_error(item, "not able to lock");
    return CMD_RETURN_ERROR;
  }
  if ((&wc[wc_idx]) == 0)
  {
    wc_idx = cmd_wait_for_add(name);
  }
  if (wc->locked)
  {
    wi_idx = xcalloc(1, sizeof(*wi_idx));
    wi->item = item;
    do
    {
      wi->entry.tqe_next = 0;
      wi->entry.tqe_prev = (&wc->lockers)->tqh_last;
      *(&wc->lockers)->tqh_last = &wi[wi_idx];
      (&wc->lockers)->tqh_last = &wi->entry.tqe_next;
    }
    while (0);
    return CMD_RETURN_WAIT;
  }
  wc->locked = 1;
  return CMD_RETURN_NORMAL;
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
static struct wait_channel *cmd_wait_for_add(const char *name)
{
  struct wait_channel *wc;
  unsigned int wc_idx = 0;
  wc_idx = xmalloc(sizeof(*wc_idx));
  wc->name = xstrdup(name);
  wc->locked = 0;
  wc->woken = 0;
  do
  {
    (&wc->waiters)->tqh_first = 0;
    (&wc->waiters)->tqh_last = &(&wc->waiters)->tqh_first;
  }
  while (0);
  do
  {
    (&wc->lockers)->tqh_first = 0;
    (&wc->lockers)->tqh_last = &(&wc->lockers)->tqh_first;
  }
  while (0);
  wait_channels_RB_INSERT(&wait_channels, wc);
  log_debug("add wait channel %s", wc->name);
  return wc;
}


----------------------------
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
enum cmd_retval
{
  CMD_RETURN_ERROR = -1,
  CMD_RETURN_NORMAL = 0,
  CMD_RETURN_WAIT,
  CMD_RETURN_STOP
}
----------------------------
struct wait_item
{
  struct cmdq_item *item;
  struct 
  {
    struct wait_item *tqe_next;
    struct wait_item **tqe_prev;
  } entry;
}
----------------------------
void cmdq_error(struct cmdq_item *item, const char *fmt, ...)
{
  struct client *c = item->client;
  struct cmd *cmd = item->cmd;
  va_list ap;
  char *msg;
  unsigned int msg_idx = 0;
  size_t msglen;
  char *tmp;
  unsigned int tmp_idx = 0;
  __builtin_va_start(ap);
  msglen = xvasprintf(&(&msg[msg_idx]), fmt, ap);
  ;
  log_debug("%s: %s", __func__, msg);
  if (c == 0)
  {
    cfg_add_cause("%s:%u: %s", cmd->file, cmd->line, msg);
  }
  else
    if ((c->session == 0) || (c->flags & 0x2000))
  {
    if ((~c->flags) & 0x10000)
    {
      tmp_idx = &msg[msg_idx];
      msg_idx = utf8_sanitize(tmp);
      free(tmp);
      msglen = strlen(msg);
    }
    evbuffer_add(c->stderr_data, msg, msglen);
    evbuffer_add(c->stderr_data, "\n", 1);
    server_client_push_stderr(c);
    c->retval = 1;
  }
  else
  {
    msg[msg_idx] = toupper((u_char) msg[msg_idx]);
    status_message_set(c, "%s", msg);
  }
  free(msg);
}


----------------------------
None
----------------------------
***/


static enum cmd_retval cmd_wait_for_wait(struct cmdq_item *item, const char *name, struct wait_channel *wc)
{
  unsigned int wc_idx = 0;
  struct client *c = item->client;
  struct wait_item *wi;
  unsigned int wi_idx = 0;
  if ((c == 0) || (c->session != 0))
  {
    cmdq_error(item, "not able to wait");
    return CMD_RETURN_ERROR;
  }
  if ((&wc[wc_idx]) == 0)
  {
    wc_idx = cmd_wait_for_add(name);
  }
  if (wc->woken)
  {
    log_debug("wait channel %s already woken (%p)", wc->name, c);
    cmd_wait_for_remove(wc);
    return CMD_RETURN_NORMAL;
  }
  log_debug("wait channel %s not woken (%p)", wc->name, c);
  wi_idx = xcalloc(1, sizeof(*wi_idx));
  wi->item = item;
  do
  {
    wi->entry.tqe_next = 0;
    wi->entry.tqe_prev = (&wc->waiters)->tqh_last;
    *(&wc->waiters)->tqh_last = &wi[wi_idx];
    (&wc->waiters)->tqh_last = &wi->entry.tqe_next;
  }
  while (0);
  return CMD_RETURN_WAIT;
}


/*** DEPENDENCIES:
static void cmd_wait_for_remove(struct wait_channel *wc)
{
  if (wc->locked)
  {
    return;
  }
  if ((!((&wc->waiters)->tqh_first == 0)) || (!wc->woken))
  {
    return;
  }
  log_debug("remove wait channel %s", wc->name);
  wait_channels_RB_REMOVE(&wait_channels, wc);
  free((void *) wc->name);
  free(wc);
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
static struct wait_channel *cmd_wait_for_add(const char *name)
{
  struct wait_channel *wc;
  unsigned int wc_idx = 0;
  wc_idx = xmalloc(sizeof(*wc_idx));
  wc->name = xstrdup(name);
  wc->locked = 0;
  wc->woken = 0;
  do
  {
    (&wc->waiters)->tqh_first = 0;
    (&wc->waiters)->tqh_last = &(&wc->waiters)->tqh_first;
  }
  while (0);
  do
  {
    (&wc->lockers)->tqh_first = 0;
    (&wc->lockers)->tqh_last = &(&wc->lockers)->tqh_first;
  }
  while (0);
  wait_channels_RB_INSERT(&wait_channels, wc);
  log_debug("add wait channel %s", wc->name);
  return wc;
}


----------------------------
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
enum cmd_retval
{
  CMD_RETURN_ERROR = -1,
  CMD_RETURN_NORMAL = 0,
  CMD_RETURN_WAIT,
  CMD_RETURN_STOP
}
----------------------------
struct wait_item
{
  struct cmdq_item *item;
  struct 
  {
    struct wait_item *tqe_next;
    struct wait_item **tqe_prev;
  } entry;
}
----------------------------
void cmdq_error(struct cmdq_item *item, const char *fmt, ...)
{
  struct client *c = item->client;
  struct cmd *cmd = item->cmd;
  va_list ap;
  char *msg;
  unsigned int msg_idx = 0;
  size_t msglen;
  char *tmp;
  unsigned int tmp_idx = 0;
  __builtin_va_start(ap);
  msglen = xvasprintf(&(&msg[msg_idx]), fmt, ap);
  ;
  log_debug("%s: %s", __func__, msg);
  if (c == 0)
  {
    cfg_add_cause("%s:%u: %s", cmd->file, cmd->line, msg);
  }
  else
    if ((c->session == 0) || (c->flags & 0x2000))
  {
    if ((~c->flags) & 0x10000)
    {
      tmp_idx = &msg[msg_idx];
      msg_idx = utf8_sanitize(tmp);
      free(tmp);
      msglen = strlen(msg);
    }
    evbuffer_add(c->stderr_data, msg, msglen);
    evbuffer_add(c->stderr_data, "\n", 1);
    server_client_push_stderr(c);
    c->retval = 1;
  }
  else
  {
    msg[msg_idx] = toupper((u_char) msg[msg_idx]);
    status_message_set(c, "%s", msg);
  }
  free(msg);
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


static enum cmd_retval cmd_wait_for_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  const char *name = args->argv[0];
  struct wait_channel *wc;
  unsigned int wc_idx = 0;
  struct wait_channel wc0;
  wc0.name = name;
  wc_idx = wait_channels_RB_FIND(&wait_channels, &wc0);
  if (args_has(args, 'S'))
  {
    return cmd_wait_for_signal(item, name, wc);
  }
  if (args_has(args, 'L'))
  {
    return cmd_wait_for_lock(item, name, wc);
  }
  if (args_has(args, 'U'))
  {
    return cmd_wait_for_unlock(item, name, wc);
  }
  return cmd_wait_for_wait(item, name, wc);
}


/*** DEPENDENCIES:
static enum cmd_retval cmd_wait_for_signal(struct cmdq_item *item, const char *name, struct wait_channel *wc)
{
  unsigned int wc_idx = 0;
  struct wait_item *wi;
  unsigned int wi_idx = 0;
  struct wait_item *wi1;
  unsigned int wi1_idx = 0;
  if ((&wc[wc_idx]) == 0)
  {
    wc_idx = cmd_wait_for_add(name);
  }
  if (((&wc->waiters)->tqh_first == 0) && (!wc->woken))
  {
    log_debug("signal wait channel %s, no waiters", wc->name);
    wc->woken = 1;
    return CMD_RETURN_NORMAL;
  }
  log_debug("signal wait channel %s, with waiters", wc->name);
  for (wi_idx = (&wc->waiters)->tqh_first; ((&wi[wi_idx]) != 0) && ((wi1_idx = wi->entry.tqe_next, 1)); wi_idx = &wi1[wi1_idx])
  {
    wi->item->flags &= ~0x2;
    do
    {
      if (wi->entry.tqe_next != 0)
      {
        wi->entry.tqe_next->entry.tqe_prev = wi->entry.tqe_prev;
      }
      else
        (&wc->waiters)->tqh_last = wi->entry.tqe_prev;
      *wi->entry.tqe_prev = wi->entry.tqe_next;
      ;
      ;
    }
    while (0);
    free(wi);
  }

  cmd_wait_for_remove(wc);
  return CMD_RETURN_NORMAL;
}


----------------------------
static enum cmd_retval cmd_wait_for_wait(struct cmdq_item *item, const char *name, struct wait_channel *wc)
{
  unsigned int wc_idx = 0;
  struct client *c = item->client;
  struct wait_item *wi;
  unsigned int wi_idx = 0;
  if ((c == 0) || (c->session != 0))
  {
    cmdq_error(item, "not able to wait");
    return CMD_RETURN_ERROR;
  }
  if ((&wc[wc_idx]) == 0)
  {
    wc_idx = cmd_wait_for_add(name);
  }
  if (wc->woken)
  {
    log_debug("wait channel %s already woken (%p)", wc->name, c);
    cmd_wait_for_remove(wc);
    return CMD_RETURN_NORMAL;
  }
  log_debug("wait channel %s not woken (%p)", wc->name, c);
  wi_idx = xcalloc(1, sizeof(*wi_idx));
  wi->item = item;
  do
  {
    wi->entry.tqe_next = 0;
    wi->entry.tqe_prev = (&wc->waiters)->tqh_last;
    *(&wc->waiters)->tqh_last = &wi[wi_idx];
    (&wc->waiters)->tqh_last = &wi->entry.tqe_next;
  }
  while (0);
  return CMD_RETURN_WAIT;
}


----------------------------
int args_has(struct args *args, u_char ch)
{
  return args_find(args, ch) != 0;
}


----------------------------
struct wait_channel
{
  const char *name;
  int locked;
  int woken;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } waiters;
  struct 
  {
    struct wait_item *tqh_first;
    struct wait_item **tqh_last;
  } lockers;
  struct 
  {
    struct wait_channel *rbe_left;
    struct wait_channel *rbe_right;
    struct wait_channel *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
static struct wait_channel *wait_channels_RB_FIND(struct wait_channels *head, struct wait_channel *elm)
{
  struct wait_channel *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  int comp;
  while (tmp)
  {
    comp = wait_channel_cmp(elm, tmp);
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
enum cmd_retval
{
  CMD_RETURN_ERROR = -1,
  CMD_RETURN_NORMAL = 0,
  CMD_RETURN_WAIT,
  CMD_RETURN_STOP
}
----------------------------
struct wait_channels
{
  struct wait_channel *rbh_root;
}
----------------------------
None
----------------------------
static enum cmd_retval cmd_wait_for_lock(struct cmdq_item *item, const char *name, struct wait_channel *wc)
{
  unsigned int wc_idx = 0;
  struct wait_item *wi;
  unsigned int wi_idx = 0;
  if ((item->client == 0) || (item->client->session != 0))
  {
    cmdq_error(item, "not able to lock");
    return CMD_RETURN_ERROR;
  }
  if ((&wc[wc_idx]) == 0)
  {
    wc_idx = cmd_wait_for_add(name);
  }
  if (wc->locked)
  {
    wi_idx = xcalloc(1, sizeof(*wi_idx));
    wi->item = item;
    do
    {
      wi->entry.tqe_next = 0;
      wi->entry.tqe_prev = (&wc->lockers)->tqh_last;
      *(&wc->lockers)->tqh_last = &wi[wi_idx];
      (&wc->lockers)->tqh_last = &wi->entry.tqe_next;
    }
    while (0);
    return CMD_RETURN_WAIT;
  }
  wc->locked = 1;
  return CMD_RETURN_NORMAL;
}


----------------------------
static enum cmd_retval cmd_wait_for_unlock(struct cmdq_item *item, const char *name, struct wait_channel *wc)
{
  struct wait_item *wi;
  unsigned int wi_idx = 0;
  if ((wc == 0) || (!wc->locked))
  {
    cmdq_error(item, "channel %s not locked", name);
    return CMD_RETURN_ERROR;
  }
  if ((wi_idx = (&wc->lockers)->tqh_first) != 0)
  {
    wi->item->flags &= ~0x2;
    do
    {
      if (wi->entry.tqe_next != 0)
      {
        wi->entry.tqe_next->entry.tqe_prev = wi->entry.tqe_prev;
      }
      else
        (&wc->lockers)->tqh_last = wi->entry.tqe_prev;
      *wi->entry.tqe_prev = wi->entry.tqe_next;
      ;
      ;
    }
    while (0);
    free(wi);
  }
  else
  {
    wc->locked = 0;
    cmd_wait_for_remove(wc);
  }
  return CMD_RETURN_NORMAL;
}


----------------------------
None
----------------------------
***/


