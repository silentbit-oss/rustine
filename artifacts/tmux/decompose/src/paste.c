static struct paste_buffer *paste_time_tree_RB_MINMAX(struct paste_time_tree *head, int val)
{
  struct paste_buffer *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct paste_buffer *parent = 0;
  unsigned int parent_idx = 0;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    if (val < 0)
    {
      tmp_idx = tmp_idx->time_entry.rbe_left;
    }
    else
      tmp_idx = tmp_idx->time_entry.rbe_right;
  }

  return parent;
}


/*** DEPENDENCIES:
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
***/


static int paste_cmp_names(const struct paste_buffer *a, const struct paste_buffer *b)
{
  return strcmp(a->name, b->name);
}


/*** DEPENDENCIES:
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
***/


static struct paste_buffer *paste_name_tree_RB_FIND(struct paste_name_tree *head, struct paste_buffer *elm)
{
  struct paste_buffer *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  int comp;
  while (tmp)
  {
    comp = paste_cmp_names(elm, tmp);
    if (comp < 0)
    {
      tmp_idx = tmp_idx->name_entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->name_entry.rbe_right;
    }
    else
      return tmp;
  }

  return 0;
}


/*** DEPENDENCIES:
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
static int paste_cmp_names(const struct paste_buffer *a, const struct paste_buffer *b)
{
  return strcmp(a->name, b->name);
}


----------------------------
***/


struct paste_buffer *paste_get_name(const char *name)
{
  struct paste_buffer pbfind;
  if ((name == 0) || ((*name) == '\0'))
  {
    return 0;
  }
  pbfind.name = (char *) name;
  return paste_name_tree_RB_FIND(&paste_by_name, &pbfind);
}


/*** DEPENDENCIES:
static struct paste_buffer *paste_name_tree_RB_FIND(struct paste_name_tree *head, struct paste_buffer *elm)
{
  struct paste_buffer *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  int comp;
  while (tmp)
  {
    comp = paste_cmp_names(elm, tmp);
    if (comp < 0)
    {
      tmp_idx = tmp_idx->name_entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->name_entry.rbe_right;
    }
    else
      return tmp;
  }

  return 0;
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
static struct paste_name_tree
{
  struct paste_buffer *rbh_root;
} paste_by_name
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_paste_name_tree_RB_INSERT_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const elm, struct paste_buffer * const parent, struct paste_buffer * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp_idx = parent->name_entry.rbe_left;
    if (parent->name_entry.rbe_left = tmp->name_entry.rbe_right)
    {
      tmp->name_entry.rbe_right->name_entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->name_entry.rbe_parent = parent->name_entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->name_entry.rbe_parent->name_entry.rbe_left)
      {
        parent->name_entry.rbe_parent->name_entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->name_entry.rbe_parent->name_entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->name_entry.rbe_right = &parent[parent_idx];
    parent->name_entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->name_entry.rbe_parent)
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
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_paste_name_tree_RB_INSERT_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const gparent, struct paste_buffer * const tmp, unsigned int gparent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->name_entry.rbe_right;
  if (gparent->name_entry.rbe_right = tmp->name_entry.rbe_left)
  {
    tmp->name_entry.rbe_left->name_entry.rbe_parent = &gparent[gparent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->name_entry.rbe_parent = gparent->name_entry.rbe_parent)
  {
    if ((&gparent[gparent_idx]) == gparent->name_entry.rbe_parent->name_entry.rbe_left)
    {
      gparent->name_entry.rbe_parent->name_entry.rbe_left = &tmp[tmp_idx];
    }
    else
      gparent->name_entry.rbe_parent->name_entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->name_entry.rbe_left = &gparent[gparent_idx];
  gparent->name_entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->name_entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
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
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_paste_name_tree_RB_INSERT_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const elm, struct paste_buffer * const parent, struct paste_buffer * const gparent, struct paste_buffer * const tmp, unsigned int gparent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->name_entry.rbe_left;
  if ((&tmp[tmp_idx]) && (tmp->name_entry.rbe_color == 1))
  {
    tmp->name_entry.rbe_color = 0;
    do
    {
      parent->name_entry.rbe_color = 0;
      gparent->name_entry.rbe_color = 1;
    }
    while (0);
    elm_idx = &gparent[gparent_idx];
    continue;
  }
  if (parent->name_entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_helper_paste_name_tree_RB_INSERT_COLOR_1_2_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->name_entry.rbe_color = 0;
    gparent->name_entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_paste_name_tree_RB_INSERT_COLOR_1_2_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
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
void helper_helper_helper_paste_name_tree_RB_INSERT_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const elm, struct paste_buffer * const parent, struct paste_buffer * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp_idx = parent->name_entry.rbe_left;
    if (parent->name_entry.rbe_left = tmp->name_entry.rbe_right)
    {
      tmp->name_entry.rbe_right->name_entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->name_entry.rbe_parent = parent->name_entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->name_entry.rbe_parent->name_entry.rbe_left)
      {
        parent->name_entry.rbe_parent->name_entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->name_entry.rbe_parent->name_entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->name_entry.rbe_right = &parent[parent_idx];
    parent->name_entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->name_entry.rbe_parent)
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
void helper_helper_helper_paste_name_tree_RB_INSERT_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const gparent, struct paste_buffer * const tmp, unsigned int gparent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->name_entry.rbe_right;
  if (gparent->name_entry.rbe_right = tmp->name_entry.rbe_left)
  {
    tmp->name_entry.rbe_left->name_entry.rbe_parent = &gparent[gparent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->name_entry.rbe_parent = gparent->name_entry.rbe_parent)
  {
    if ((&gparent[gparent_idx]) == gparent->name_entry.rbe_parent->name_entry.rbe_left)
    {
      gparent->name_entry.rbe_parent->name_entry.rbe_left = &tmp[tmp_idx];
    }
    else
      gparent->name_entry.rbe_parent->name_entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->name_entry.rbe_left = &gparent[gparent_idx];
  gparent->name_entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->name_entry.rbe_parent)
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
void helper_helper_helper_paste_name_tree_RB_INSERT_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const elm, struct paste_buffer * const parent, struct paste_buffer * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp_idx = parent->name_entry.rbe_right;
    if (parent->name_entry.rbe_right = tmp->name_entry.rbe_left)
    {
      tmp->name_entry.rbe_left->name_entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->name_entry.rbe_parent = parent->name_entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->name_entry.rbe_parent->name_entry.rbe_left)
      {
        parent->name_entry.rbe_parent->name_entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->name_entry.rbe_parent->name_entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->name_entry.rbe_left = &parent[parent_idx];
    parent->name_entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->name_entry.rbe_parent)
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
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_paste_name_tree_RB_INSERT_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const gparent, struct paste_buffer * const tmp, unsigned int gparent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->name_entry.rbe_left;
  if (gparent->name_entry.rbe_left = tmp->name_entry.rbe_right)
  {
    tmp->name_entry.rbe_right->name_entry.rbe_parent = &gparent[gparent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->name_entry.rbe_parent = gparent->name_entry.rbe_parent)
  {
    if ((&gparent[gparent_idx]) == gparent->name_entry.rbe_parent->name_entry.rbe_left)
    {
      gparent->name_entry.rbe_parent->name_entry.rbe_left = &tmp[tmp_idx];
    }
    else
      gparent->name_entry.rbe_parent->name_entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->name_entry.rbe_right = &gparent[gparent_idx];
  gparent->name_entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->name_entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
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
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_paste_name_tree_RB_INSERT_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const elm, struct paste_buffer * const parent, struct paste_buffer * const gparent, struct paste_buffer * const tmp, unsigned int gparent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->name_entry.rbe_right;
  if ((&tmp[tmp_idx]) && (tmp->name_entry.rbe_color == 1))
  {
    tmp->name_entry.rbe_color = 0;
    do
    {
      parent->name_entry.rbe_color = 0;
      gparent->name_entry.rbe_color = 1;
    }
    while (0);
    elm_idx = &gparent[gparent_idx];
    continue;
  }
  if (parent->name_entry.rbe_right == (&elm[elm_idx]))
  {
    helper_helper_helper_paste_name_tree_RB_INSERT_COLOR_1_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->name_entry.rbe_color = 0;
    gparent->name_entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_paste_name_tree_RB_INSERT_COLOR_1_1_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
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
void helper_helper_helper_paste_name_tree_RB_INSERT_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const elm, struct paste_buffer * const parent, struct paste_buffer * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp_idx = parent->name_entry.rbe_right;
    if (parent->name_entry.rbe_right = tmp->name_entry.rbe_left)
    {
      tmp->name_entry.rbe_left->name_entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->name_entry.rbe_parent = parent->name_entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->name_entry.rbe_parent->name_entry.rbe_left)
      {
        parent->name_entry.rbe_parent->name_entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->name_entry.rbe_parent->name_entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->name_entry.rbe_left = &parent[parent_idx];
    parent->name_entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->name_entry.rbe_parent)
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
void helper_helper_helper_paste_name_tree_RB_INSERT_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const gparent, struct paste_buffer * const tmp, unsigned int gparent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->name_entry.rbe_left;
  if (gparent->name_entry.rbe_left = tmp->name_entry.rbe_right)
  {
    tmp->name_entry.rbe_right->name_entry.rbe_parent = &gparent[gparent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->name_entry.rbe_parent = gparent->name_entry.rbe_parent)
  {
    if ((&gparent[gparent_idx]) == gparent->name_entry.rbe_parent->name_entry.rbe_left)
    {
      gparent->name_entry.rbe_parent->name_entry.rbe_left = &tmp[tmp_idx];
    }
    else
      gparent->name_entry.rbe_parent->name_entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->name_entry.rbe_right = &gparent[gparent_idx];
  gparent->name_entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->name_entry.rbe_parent)
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
void helper_paste_name_tree_RB_INSERT_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const gparent_idx_ref, unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const elm, struct paste_buffer * const parent, struct paste_buffer * const gparent, struct paste_buffer * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int gparent_idx = *gparent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  gparent_idx = parent->name_entry.rbe_parent;
  if ((&parent[parent_idx]) == gparent->name_entry.rbe_left)
  {
    helper_helper_paste_name_tree_RB_INSERT_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  else
  {
    helper_helper_paste_name_tree_RB_INSERT_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *gparent_idx_ref = gparent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
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
void helper_helper_paste_name_tree_RB_INSERT_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const elm, struct paste_buffer * const parent, struct paste_buffer * const gparent, struct paste_buffer * const tmp, unsigned int gparent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->name_entry.rbe_left;
  if ((&tmp[tmp_idx]) && (tmp->name_entry.rbe_color == 1))
  {
    tmp->name_entry.rbe_color = 0;
    do
    {
      parent->name_entry.rbe_color = 0;
      gparent->name_entry.rbe_color = 1;
    }
    while (0);
    elm_idx = &gparent[gparent_idx];
    continue;
  }
  if (parent->name_entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_helper_paste_name_tree_RB_INSERT_COLOR_1_2_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->name_entry.rbe_color = 0;
    gparent->name_entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_paste_name_tree_RB_INSERT_COLOR_1_2_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_paste_name_tree_RB_INSERT_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const elm, struct paste_buffer * const parent, struct paste_buffer * const gparent, struct paste_buffer * const tmp, unsigned int gparent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->name_entry.rbe_right;
  if ((&tmp[tmp_idx]) && (tmp->name_entry.rbe_color == 1))
  {
    tmp->name_entry.rbe_color = 0;
    do
    {
      parent->name_entry.rbe_color = 0;
      gparent->name_entry.rbe_color = 1;
    }
    while (0);
    elm_idx = &gparent[gparent_idx];
    continue;
  }
  if (parent->name_entry.rbe_right == (&elm[elm_idx]))
  {
    helper_helper_helper_paste_name_tree_RB_INSERT_COLOR_1_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->name_entry.rbe_color = 0;
    gparent->name_entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_paste_name_tree_RB_INSERT_COLOR_1_1_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
***/


static void paste_name_tree_RB_INSERT_COLOR(struct paste_name_tree *head, struct paste_buffer *elm)
{
  unsigned int elm_idx = 0;
  struct paste_buffer *parent;
  unsigned int parent_idx = 0;
  struct paste_buffer *gparent;
  unsigned int gparent_idx = 0;
  struct paste_buffer *tmp;
  unsigned int tmp_idx = 0;
  while ((parent_idx = elm->name_entry.rbe_parent) && (parent->name_entry.rbe_color == 1))
  {
    helper_paste_name_tree_RB_INSERT_COLOR_1(&elm_idx, &parent_idx, &gparent_idx, &tmp_idx, head, elm, parent, gparent, tmp);
  }

  head->rbh_root->name_entry.rbe_color = 0;
}


/*** DEPENDENCIES:
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
void helper_paste_name_tree_RB_INSERT_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const gparent_idx_ref, unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const elm, struct paste_buffer * const parent, struct paste_buffer * const gparent, struct paste_buffer * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int gparent_idx = *gparent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  gparent_idx = parent->name_entry.rbe_parent;
  if ((&parent[parent_idx]) == gparent->name_entry.rbe_left)
  {
    helper_helper_paste_name_tree_RB_INSERT_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  else
  {
    helper_helper_paste_name_tree_RB_INSERT_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *gparent_idx_ref = gparent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
***/


static struct paste_buffer *paste_name_tree_RB_INSERT(struct paste_name_tree *head, struct paste_buffer *elm)
{
  struct paste_buffer *tmp;
  unsigned int tmp_idx = 0;
  struct paste_buffer *parent = 0;
  unsigned int parent_idx = 0;
  int comp = 0;
  tmp_idx = head->rbh_root;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    comp = paste_cmp_names(elm, parent);
    if (comp < 0)
    {
      tmp_idx = tmp_idx->name_entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->name_entry.rbe_right;
    }
    else
      return tmp;
  }

  do
  {
    elm->name_entry.rbe_parent = &parent[parent_idx];
    elm->name_entry.rbe_left = (elm->name_entry.rbe_right = 0);
    elm->name_entry.rbe_color = 1;
  }
  while (0);
  if ((&parent[parent_idx]) != 0)
  {
    if (comp < 0)
    {
      parent->name_entry.rbe_left = elm;
    }
    else
      parent->name_entry.rbe_right = elm;
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = elm;
  paste_name_tree_RB_INSERT_COLOR(head, elm);
  return 0;
}


/*** DEPENDENCIES:
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
static int paste_cmp_names(const struct paste_buffer *a, const struct paste_buffer *b)
{
  return strcmp(a->name, b->name);
}


----------------------------
static void paste_name_tree_RB_INSERT_COLOR(struct paste_name_tree *head, struct paste_buffer *elm)
{
  unsigned int elm_idx = 0;
  struct paste_buffer *parent;
  unsigned int parent_idx = 0;
  struct paste_buffer *gparent;
  unsigned int gparent_idx = 0;
  struct paste_buffer *tmp;
  unsigned int tmp_idx = 0;
  while ((parent_idx = elm->name_entry.rbe_parent) && (parent->name_entry.rbe_color == 1))
  {
    helper_paste_name_tree_RB_INSERT_COLOR_1(&elm_idx, &parent_idx, &gparent_idx, &tmp_idx, head, elm, parent, gparent, tmp);
  }

  head->rbh_root->name_entry.rbe_color = 0;
}


----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp->name_entry.rbe_color = 0;
    parent->name_entry.rbe_color = 1;
  }
  while (0);
  do
  {
    tmp_idx = parent->name_entry.rbe_right;
    if (parent->name_entry.rbe_right = tmp->name_entry.rbe_left)
    {
      tmp->name_entry.rbe_left->name_entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->name_entry.rbe_parent = parent->name_entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->name_entry.rbe_parent->name_entry.rbe_left)
      {
        parent->name_entry.rbe_parent->name_entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->name_entry.rbe_parent->name_entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->name_entry.rbe_left = &parent[parent_idx];
    parent->name_entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->name_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->name_entry.rbe_right;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
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
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_1_2_2(unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct paste_buffer *oleft;
  unsigned int oleft_idx = 0;
  if (oleft_idx = tmp->name_entry.rbe_left)
  {
    oleft->name_entry.rbe_color = 0;
  }
  tmp->name_entry.rbe_color = 1;
  do
  {
    oleft_idx = tmp->name_entry.rbe_left;
    if (tmp->name_entry.rbe_left = oleft->name_entry.rbe_right)
    {
      oleft->name_entry.rbe_right->name_entry.rbe_parent = &tmp[tmp_idx];
    }
    do
    {
    }
    while (0);
    if (oleft->name_entry.rbe_parent = tmp->name_entry.rbe_parent)
    {
      if ((&tmp[tmp_idx]) == tmp->name_entry.rbe_parent->name_entry.rbe_left)
      {
        tmp->name_entry.rbe_parent->name_entry.rbe_left = &oleft[oleft_idx];
      }
      else
        tmp->name_entry.rbe_parent->name_entry.rbe_right = &oleft[oleft_idx];
    }
    else
      head->rbh_root = &oleft[oleft_idx];
    oleft->name_entry.rbe_right = &tmp[tmp_idx];
    tmp->name_entry.rbe_parent = &oleft[oleft_idx];
    do
    {
    }
    while (0);
    if (oleft->name_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->name_entry.rbe_right;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
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
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_1_2_1(unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->name_entry.rbe_right;
  if (parent->name_entry.rbe_right = tmp->name_entry.rbe_left)
  {
    tmp->name_entry.rbe_left->name_entry.rbe_parent = &parent[parent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->name_entry.rbe_parent = parent->name_entry.rbe_parent)
  {
    if ((&parent[parent_idx]) == parent->name_entry.rbe_parent->name_entry.rbe_left)
    {
      parent->name_entry.rbe_parent->name_entry.rbe_left = &tmp[tmp_idx];
    }
    else
      parent->name_entry.rbe_parent->name_entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->name_entry.rbe_left = &parent[parent_idx];
  parent->name_entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->name_entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
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
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->name_entry.rbe_right == 0) || (tmp->name_entry.rbe_right->name_entry.rbe_color == 0))
  {
    helper_helper_helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_1_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->name_entry.rbe_color = parent->name_entry.rbe_color;
  parent->name_entry.rbe_color = 0;
  if (tmp->name_entry.rbe_right)
  {
    tmp->name_entry.rbe_right->name_entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
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
void helper_helper_helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_1_2_2(unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct paste_buffer *oleft;
  unsigned int oleft_idx = 0;
  if (oleft_idx = tmp->name_entry.rbe_left)
  {
    oleft->name_entry.rbe_color = 0;
  }
  tmp->name_entry.rbe_color = 1;
  do
  {
    oleft_idx = tmp->name_entry.rbe_left;
    if (tmp->name_entry.rbe_left = oleft->name_entry.rbe_right)
    {
      oleft->name_entry.rbe_right->name_entry.rbe_parent = &tmp[tmp_idx];
    }
    do
    {
    }
    while (0);
    if (oleft->name_entry.rbe_parent = tmp->name_entry.rbe_parent)
    {
      if ((&tmp[tmp_idx]) == tmp->name_entry.rbe_parent->name_entry.rbe_left)
      {
        tmp->name_entry.rbe_parent->name_entry.rbe_left = &oleft[oleft_idx];
      }
      else
        tmp->name_entry.rbe_parent->name_entry.rbe_right = &oleft[oleft_idx];
    }
    else
      head->rbh_root = &oleft[oleft_idx];
    oleft->name_entry.rbe_right = &tmp[tmp_idx];
    tmp->name_entry.rbe_parent = &oleft[oleft_idx];
    do
    {
    }
    while (0);
    if (oleft->name_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->name_entry.rbe_right;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_1_2_1(unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->name_entry.rbe_right;
  if (parent->name_entry.rbe_right = tmp->name_entry.rbe_left)
  {
    tmp->name_entry.rbe_left->name_entry.rbe_parent = &parent[parent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->name_entry.rbe_parent = parent->name_entry.rbe_parent)
  {
    if ((&parent[parent_idx]) == parent->name_entry.rbe_parent->name_entry.rbe_left)
    {
      parent->name_entry.rbe_parent->name_entry.rbe_left = &tmp[tmp_idx];
    }
    else
      parent->name_entry.rbe_parent->name_entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->name_entry.rbe_left = &parent[parent_idx];
  parent->name_entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->name_entry.rbe_parent)
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
void helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const elm, struct paste_buffer * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->name_entry.rbe_right;
  if (tmp->name_entry.rbe_color == 1)
  {
    helper_helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_1_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->name_entry.rbe_left == 0) || (tmp->name_entry.rbe_left->name_entry.rbe_color == 0)) && ((tmp->name_entry.rbe_right == 0) || (tmp->name_entry.rbe_right->name_entry.rbe_color == 0)))
  {
    tmp->name_entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->name_entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_1_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
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
void helper_helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp->name_entry.rbe_color = 0;
    parent->name_entry.rbe_color = 1;
  }
  while (0);
  do
  {
    tmp_idx = parent->name_entry.rbe_right;
    if (parent->name_entry.rbe_right = tmp->name_entry.rbe_left)
    {
      tmp->name_entry.rbe_left->name_entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->name_entry.rbe_parent = parent->name_entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->name_entry.rbe_parent->name_entry.rbe_left)
      {
        parent->name_entry.rbe_parent->name_entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->name_entry.rbe_parent->name_entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->name_entry.rbe_left = &parent[parent_idx];
    parent->name_entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->name_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->name_entry.rbe_right;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->name_entry.rbe_right == 0) || (tmp->name_entry.rbe_right->name_entry.rbe_color == 0))
  {
    helper_helper_helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_1_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->name_entry.rbe_color = parent->name_entry.rbe_color;
  parent->name_entry.rbe_color = 0;
  if (tmp->name_entry.rbe_right)
  {
    tmp->name_entry.rbe_right->name_entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp->name_entry.rbe_color = 0;
    parent->name_entry.rbe_color = 1;
  }
  while (0);
  do
  {
    tmp_idx = parent->name_entry.rbe_left;
    if (parent->name_entry.rbe_left = tmp->name_entry.rbe_right)
    {
      tmp->name_entry.rbe_right->name_entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->name_entry.rbe_parent = parent->name_entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->name_entry.rbe_parent->name_entry.rbe_left)
      {
        parent->name_entry.rbe_parent->name_entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->name_entry.rbe_parent->name_entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->name_entry.rbe_right = &parent[parent_idx];
    parent->name_entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->name_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->name_entry.rbe_left;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
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
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_2_2_2(unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct paste_buffer *oright;
  unsigned int oright_idx = 0;
  if (oright_idx = tmp->name_entry.rbe_right)
  {
    oright->name_entry.rbe_color = 0;
  }
  tmp->name_entry.rbe_color = 1;
  do
  {
    oright_idx = tmp->name_entry.rbe_right;
    if (tmp->name_entry.rbe_right = oright->name_entry.rbe_left)
    {
      oright->name_entry.rbe_left->name_entry.rbe_parent = &tmp[tmp_idx];
    }
    do
    {
    }
    while (0);
    if (oright->name_entry.rbe_parent = tmp->name_entry.rbe_parent)
    {
      if ((&tmp[tmp_idx]) == tmp->name_entry.rbe_parent->name_entry.rbe_left)
      {
        tmp->name_entry.rbe_parent->name_entry.rbe_left = &oright[oright_idx];
      }
      else
        tmp->name_entry.rbe_parent->name_entry.rbe_right = &oright[oright_idx];
    }
    else
      head->rbh_root = &oright[oright_idx];
    oright->name_entry.rbe_left = &tmp[tmp_idx];
    tmp->name_entry.rbe_parent = &oright[oright_idx];
    do
    {
    }
    while (0);
    if (oright->name_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->name_entry.rbe_left;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
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
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_2_2_1(unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->name_entry.rbe_left;
  if (parent->name_entry.rbe_left = tmp->name_entry.rbe_right)
  {
    tmp->name_entry.rbe_right->name_entry.rbe_parent = &parent[parent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->name_entry.rbe_parent = parent->name_entry.rbe_parent)
  {
    if ((&parent[parent_idx]) == parent->name_entry.rbe_parent->name_entry.rbe_left)
    {
      parent->name_entry.rbe_parent->name_entry.rbe_left = &tmp[tmp_idx];
    }
    else
      parent->name_entry.rbe_parent->name_entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->name_entry.rbe_right = &parent[parent_idx];
  parent->name_entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->name_entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
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
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->name_entry.rbe_left == 0) || (tmp->name_entry.rbe_left->name_entry.rbe_color == 0))
  {
    helper_helper_helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_2_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->name_entry.rbe_color = parent->name_entry.rbe_color;
  parent->name_entry.rbe_color = 0;
  if (tmp->name_entry.rbe_left)
  {
    tmp->name_entry.rbe_left->name_entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_2_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
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
void helper_helper_helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_2_2_2(unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct paste_buffer *oright;
  unsigned int oright_idx = 0;
  if (oright_idx = tmp->name_entry.rbe_right)
  {
    oright->name_entry.rbe_color = 0;
  }
  tmp->name_entry.rbe_color = 1;
  do
  {
    oright_idx = tmp->name_entry.rbe_right;
    if (tmp->name_entry.rbe_right = oright->name_entry.rbe_left)
    {
      oright->name_entry.rbe_left->name_entry.rbe_parent = &tmp[tmp_idx];
    }
    do
    {
    }
    while (0);
    if (oright->name_entry.rbe_parent = tmp->name_entry.rbe_parent)
    {
      if ((&tmp[tmp_idx]) == tmp->name_entry.rbe_parent->name_entry.rbe_left)
      {
        tmp->name_entry.rbe_parent->name_entry.rbe_left = &oright[oright_idx];
      }
      else
        tmp->name_entry.rbe_parent->name_entry.rbe_right = &oright[oright_idx];
    }
    else
      head->rbh_root = &oright[oright_idx];
    oright->name_entry.rbe_left = &tmp[tmp_idx];
    tmp->name_entry.rbe_parent = &oright[oright_idx];
    do
    {
    }
    while (0);
    if (oright->name_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->name_entry.rbe_left;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_2_2_1(unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->name_entry.rbe_left;
  if (parent->name_entry.rbe_left = tmp->name_entry.rbe_right)
  {
    tmp->name_entry.rbe_right->name_entry.rbe_parent = &parent[parent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->name_entry.rbe_parent = parent->name_entry.rbe_parent)
  {
    if ((&parent[parent_idx]) == parent->name_entry.rbe_parent->name_entry.rbe_left)
    {
      parent->name_entry.rbe_parent->name_entry.rbe_left = &tmp[tmp_idx];
    }
    else
      parent->name_entry.rbe_parent->name_entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->name_entry.rbe_right = &parent[parent_idx];
  parent->name_entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->name_entry.rbe_parent)
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
void helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const elm, struct paste_buffer * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->name_entry.rbe_left;
  if (tmp->name_entry.rbe_color == 1)
  {
    helper_helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->name_entry.rbe_left == 0) || (tmp->name_entry.rbe_left->name_entry.rbe_color == 0)) && ((tmp->name_entry.rbe_right == 0) || (tmp->name_entry.rbe_right->name_entry.rbe_color == 0)))
  {
    tmp->name_entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->name_entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_2_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
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
void helper_helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp->name_entry.rbe_color = 0;
    parent->name_entry.rbe_color = 1;
  }
  while (0);
  do
  {
    tmp_idx = parent->name_entry.rbe_left;
    if (parent->name_entry.rbe_left = tmp->name_entry.rbe_right)
    {
      tmp->name_entry.rbe_right->name_entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->name_entry.rbe_parent = parent->name_entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->name_entry.rbe_parent->name_entry.rbe_left)
      {
        parent->name_entry.rbe_parent->name_entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->name_entry.rbe_parent->name_entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->name_entry.rbe_right = &parent[parent_idx];
    parent->name_entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->name_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->name_entry.rbe_left;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->name_entry.rbe_left == 0) || (tmp->name_entry.rbe_left->name_entry.rbe_color == 0))
  {
    helper_helper_helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_2_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->name_entry.rbe_color = parent->name_entry.rbe_color;
  parent->name_entry.rbe_color = 0;
  if (tmp->name_entry.rbe_left)
  {
    tmp->name_entry.rbe_left->name_entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_2_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_paste_name_tree_RB_REMOVE_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const elm, struct paste_buffer * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if (parent->name_entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  else
  {
    helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
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
void helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const elm, struct paste_buffer * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->name_entry.rbe_right;
  if (tmp->name_entry.rbe_color == 1)
  {
    helper_helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_1_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->name_entry.rbe_left == 0) || (tmp->name_entry.rbe_left->name_entry.rbe_color == 0)) && ((tmp->name_entry.rbe_right == 0) || (tmp->name_entry.rbe_right->name_entry.rbe_color == 0)))
  {
    tmp->name_entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->name_entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_1_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const elm, struct paste_buffer * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->name_entry.rbe_left;
  if (tmp->name_entry.rbe_color == 1)
  {
    helper_helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->name_entry.rbe_left == 0) || (tmp->name_entry.rbe_left->name_entry.rbe_color == 0)) && ((tmp->name_entry.rbe_right == 0) || (tmp->name_entry.rbe_right->name_entry.rbe_color == 0)))
  {
    tmp->name_entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->name_entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_2_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
***/


static void paste_name_tree_RB_REMOVE_COLOR(struct paste_name_tree *head, struct paste_buffer *parent, struct paste_buffer *elm)
{
  unsigned int elm_idx = 0;
  unsigned int parent_idx = 0;
  struct paste_buffer *tmp;
  unsigned int tmp_idx = 0;
  while ((((&elm[elm_idx]) == 0) || (elm->name_entry.rbe_color == 0)) && ((&elm[elm_idx]) != head->rbh_root))
  {
    helper_paste_name_tree_RB_REMOVE_COLOR_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }

  if (elm)
  {
    elm->name_entry.rbe_color = 0;
  }
}


/*** DEPENDENCIES:
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
void helper_paste_name_tree_RB_REMOVE_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct paste_name_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const elm, struct paste_buffer * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if (parent->name_entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  else
  {
    helper_helper_paste_name_tree_RB_REMOVE_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'child_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'color_ref is a mutable refrence to int']
void helper_paste_name_tree_RB_REMOVE_1(unsigned int * const elm_idx_ref, unsigned int * const child_idx_ref, unsigned int * const parent_idx_ref, int * const color_ref, struct paste_name_tree * const head, struct paste_buffer * const elm, struct paste_buffer * const child, struct paste_buffer * const parent, struct paste_buffer * const old)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int child_idx = *child_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  int color = *color_ref;
  struct paste_buffer *left;
  unsigned int left_idx = 0;
  elm_idx = elm_idx->name_entry.rbe_right;
  while (left_idx = elm->name_entry.rbe_left)
  {
    elm_idx = &left[left_idx];
  }

  child_idx = elm->name_entry.rbe_right;
  parent_idx = elm->name_entry.rbe_parent;
  color = elm->name_entry.rbe_color;
  if (child)
  {
    child->name_entry.rbe_parent = &parent[parent_idx];
  }
  if (parent)
  {
    if (parent->name_entry.rbe_left == (&elm[elm_idx]))
    {
      parent->name_entry.rbe_left = &child[child_idx];
    }
    else
      parent->name_entry.rbe_right = &child[child_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &child[child_idx];
  if (elm->name_entry.rbe_parent == old)
  {
    parent_idx = &elm[elm_idx];
  }
  elm->name_entry = old->name_entry;
  if (old->name_entry.rbe_parent)
  {
    if (old->name_entry.rbe_parent->name_entry.rbe_left == old)
    {
      old->name_entry.rbe_parent->name_entry.rbe_left = &elm[elm_idx];
    }
    else
      old->name_entry.rbe_parent->name_entry.rbe_right = &elm[elm_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &elm[elm_idx];
  old->name_entry.rbe_left->name_entry.rbe_parent = &elm[elm_idx];
  if (old->name_entry.rbe_right)
  {
    old->name_entry.rbe_right->name_entry.rbe_parent = &elm[elm_idx];
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
    while (left_idx = left_idx->name_entry.rbe_parent);
  }
  goto color;
  *elm_idx_ref = elm_idx;
  *child_idx_ref = child_idx;
  *parent_idx_ref = parent_idx;
  *color_ref = color;
}


/*** DEPENDENCIES:
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
***/


static struct paste_buffer *paste_name_tree_RB_REMOVE(struct paste_name_tree *head, struct paste_buffer *elm)
{
  unsigned int elm_idx = 0;
  struct paste_buffer *child;
  unsigned int child_idx = 0;
  struct paste_buffer *parent;
  unsigned int parent_idx = 0;
  struct paste_buffer *old = elm;
  int color;
  if (elm->name_entry.rbe_left == 0)
  {
    child_idx = elm->name_entry.rbe_right;
  }
  else
    if (elm->name_entry.rbe_right == 0)
  {
    child_idx = elm->name_entry.rbe_left;
  }
  else
  {
    helper_paste_name_tree_RB_REMOVE_1(&elm_idx, &child_idx, &parent_idx, &color, head, elm, child, parent, old);
  }
  parent_idx = elm->name_entry.rbe_parent;
  color = elm->name_entry.rbe_color;
  if (child)
  {
    child->name_entry.rbe_parent = &parent[parent_idx];
  }
  if (parent)
  {
    if (parent->name_entry.rbe_left == (&elm[elm_idx]))
    {
      parent->name_entry.rbe_left = &child[child_idx];
    }
    else
      parent->name_entry.rbe_right = &child[child_idx];
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
    paste_name_tree_RB_REMOVE_COLOR(head, parent, child);
  }

  return old;
}


/*** DEPENDENCIES:
static void paste_name_tree_RB_REMOVE_COLOR(struct paste_name_tree *head, struct paste_buffer *parent, struct paste_buffer *elm)
{
  unsigned int elm_idx = 0;
  unsigned int parent_idx = 0;
  struct paste_buffer *tmp;
  unsigned int tmp_idx = 0;
  while ((((&elm[elm_idx]) == 0) || (elm->name_entry.rbe_color == 0)) && ((&elm[elm_idx]) != head->rbh_root))
  {
    helper_paste_name_tree_RB_REMOVE_COLOR_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }

  if (elm)
  {
    elm->name_entry.rbe_color = 0;
  }
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
void helper_paste_name_tree_RB_REMOVE_1(unsigned int * const elm_idx_ref, unsigned int * const child_idx_ref, unsigned int * const parent_idx_ref, int * const color_ref, struct paste_name_tree * const head, struct paste_buffer * const elm, struct paste_buffer * const child, struct paste_buffer * const parent, struct paste_buffer * const old)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int child_idx = *child_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  int color = *color_ref;
  struct paste_buffer *left;
  unsigned int left_idx = 0;
  elm_idx = elm_idx->name_entry.rbe_right;
  while (left_idx = elm->name_entry.rbe_left)
  {
    elm_idx = &left[left_idx];
  }

  child_idx = elm->name_entry.rbe_right;
  parent_idx = elm->name_entry.rbe_parent;
  color = elm->name_entry.rbe_color;
  if (child)
  {
    child->name_entry.rbe_parent = &parent[parent_idx];
  }
  if (parent)
  {
    if (parent->name_entry.rbe_left == (&elm[elm_idx]))
    {
      parent->name_entry.rbe_left = &child[child_idx];
    }
    else
      parent->name_entry.rbe_right = &child[child_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &child[child_idx];
  if (elm->name_entry.rbe_parent == old)
  {
    parent_idx = &elm[elm_idx];
  }
  elm->name_entry = old->name_entry;
  if (old->name_entry.rbe_parent)
  {
    if (old->name_entry.rbe_parent->name_entry.rbe_left == old)
    {
      old->name_entry.rbe_parent->name_entry.rbe_left = &elm[elm_idx];
    }
    else
      old->name_entry.rbe_parent->name_entry.rbe_right = &elm[elm_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &elm[elm_idx];
  old->name_entry.rbe_left->name_entry.rbe_parent = &elm[elm_idx];
  if (old->name_entry.rbe_right)
  {
    old->name_entry.rbe_right->name_entry.rbe_parent = &elm[elm_idx];
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
    while (left_idx = left_idx->name_entry.rbe_parent);
  }
  goto color;
  *elm_idx_ref = elm_idx;
  *child_idx_ref = child_idx;
  *parent_idx_ref = parent_idx;
  *color_ref = color;
}


----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp->time_entry.rbe_color = 0;
    parent->time_entry.rbe_color = 1;
  }
  while (0);
  do
  {
    tmp_idx = parent->time_entry.rbe_left;
    if (parent->time_entry.rbe_left = tmp->time_entry.rbe_right)
    {
      tmp->time_entry.rbe_right->time_entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->time_entry.rbe_parent = parent->time_entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->time_entry.rbe_parent->time_entry.rbe_left)
      {
        parent->time_entry.rbe_parent->time_entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->time_entry.rbe_parent->time_entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->time_entry.rbe_right = &parent[parent_idx];
    parent->time_entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->time_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->time_entry.rbe_left;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
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
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_2_2_2(unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct paste_buffer *oright;
  unsigned int oright_idx = 0;
  if (oright_idx = tmp->time_entry.rbe_right)
  {
    oright->time_entry.rbe_color = 0;
  }
  tmp->time_entry.rbe_color = 1;
  do
  {
    oright_idx = tmp->time_entry.rbe_right;
    if (tmp->time_entry.rbe_right = oright->time_entry.rbe_left)
    {
      oright->time_entry.rbe_left->time_entry.rbe_parent = &tmp[tmp_idx];
    }
    do
    {
    }
    while (0);
    if (oright->time_entry.rbe_parent = tmp->time_entry.rbe_parent)
    {
      if ((&tmp[tmp_idx]) == tmp->time_entry.rbe_parent->time_entry.rbe_left)
      {
        tmp->time_entry.rbe_parent->time_entry.rbe_left = &oright[oright_idx];
      }
      else
        tmp->time_entry.rbe_parent->time_entry.rbe_right = &oright[oright_idx];
    }
    else
      head->rbh_root = &oright[oright_idx];
    oright->time_entry.rbe_left = &tmp[tmp_idx];
    tmp->time_entry.rbe_parent = &oright[oright_idx];
    do
    {
    }
    while (0);
    if (oright->time_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->time_entry.rbe_left;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
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
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_2_2_1(unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->time_entry.rbe_left;
  if (parent->time_entry.rbe_left = tmp->time_entry.rbe_right)
  {
    tmp->time_entry.rbe_right->time_entry.rbe_parent = &parent[parent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->time_entry.rbe_parent = parent->time_entry.rbe_parent)
  {
    if ((&parent[parent_idx]) == parent->time_entry.rbe_parent->time_entry.rbe_left)
    {
      parent->time_entry.rbe_parent->time_entry.rbe_left = &tmp[tmp_idx];
    }
    else
      parent->time_entry.rbe_parent->time_entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->time_entry.rbe_right = &parent[parent_idx];
  parent->time_entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->time_entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
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
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->time_entry.rbe_left == 0) || (tmp->time_entry.rbe_left->time_entry.rbe_color == 0))
  {
    helper_helper_helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_2_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->time_entry.rbe_color = parent->time_entry.rbe_color;
  parent->time_entry.rbe_color = 0;
  if (tmp->time_entry.rbe_left)
  {
    tmp->time_entry.rbe_left->time_entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_2_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
void helper_helper_helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_2_2_2(unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct paste_buffer *oright;
  unsigned int oright_idx = 0;
  if (oright_idx = tmp->time_entry.rbe_right)
  {
    oright->time_entry.rbe_color = 0;
  }
  tmp->time_entry.rbe_color = 1;
  do
  {
    oright_idx = tmp->time_entry.rbe_right;
    if (tmp->time_entry.rbe_right = oright->time_entry.rbe_left)
    {
      oright->time_entry.rbe_left->time_entry.rbe_parent = &tmp[tmp_idx];
    }
    do
    {
    }
    while (0);
    if (oright->time_entry.rbe_parent = tmp->time_entry.rbe_parent)
    {
      if ((&tmp[tmp_idx]) == tmp->time_entry.rbe_parent->time_entry.rbe_left)
      {
        tmp->time_entry.rbe_parent->time_entry.rbe_left = &oright[oright_idx];
      }
      else
        tmp->time_entry.rbe_parent->time_entry.rbe_right = &oright[oright_idx];
    }
    else
      head->rbh_root = &oright[oright_idx];
    oright->time_entry.rbe_left = &tmp[tmp_idx];
    tmp->time_entry.rbe_parent = &oright[oright_idx];
    do
    {
    }
    while (0);
    if (oright->time_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->time_entry.rbe_left;
  *tmp_idx_ref = tmp_idx;
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
void helper_helper_helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_2_2_1(unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->time_entry.rbe_left;
  if (parent->time_entry.rbe_left = tmp->time_entry.rbe_right)
  {
    tmp->time_entry.rbe_right->time_entry.rbe_parent = &parent[parent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->time_entry.rbe_parent = parent->time_entry.rbe_parent)
  {
    if ((&parent[parent_idx]) == parent->time_entry.rbe_parent->time_entry.rbe_left)
    {
      parent->time_entry.rbe_parent->time_entry.rbe_left = &tmp[tmp_idx];
    }
    else
      parent->time_entry.rbe_parent->time_entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->time_entry.rbe_right = &parent[parent_idx];
  parent->time_entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->time_entry.rbe_parent)
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
void helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const elm, struct paste_buffer * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->time_entry.rbe_left;
  if (tmp->time_entry.rbe_color == 1)
  {
    helper_helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->time_entry.rbe_left == 0) || (tmp->time_entry.rbe_left->time_entry.rbe_color == 0)) && ((tmp->time_entry.rbe_right == 0) || (tmp->time_entry.rbe_right->time_entry.rbe_color == 0)))
  {
    tmp->time_entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->time_entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_2_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
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
void helper_helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp->time_entry.rbe_color = 0;
    parent->time_entry.rbe_color = 1;
  }
  while (0);
  do
  {
    tmp_idx = parent->time_entry.rbe_left;
    if (parent->time_entry.rbe_left = tmp->time_entry.rbe_right)
    {
      tmp->time_entry.rbe_right->time_entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->time_entry.rbe_parent = parent->time_entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->time_entry.rbe_parent->time_entry.rbe_left)
      {
        parent->time_entry.rbe_parent->time_entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->time_entry.rbe_parent->time_entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->time_entry.rbe_right = &parent[parent_idx];
    parent->time_entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->time_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->time_entry.rbe_left;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->time_entry.rbe_left == 0) || (tmp->time_entry.rbe_left->time_entry.rbe_color == 0))
  {
    helper_helper_helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_2_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->time_entry.rbe_color = parent->time_entry.rbe_color;
  parent->time_entry.rbe_color = 0;
  if (tmp->time_entry.rbe_left)
  {
    tmp->time_entry.rbe_left->time_entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_2_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp->time_entry.rbe_color = 0;
    parent->time_entry.rbe_color = 1;
  }
  while (0);
  do
  {
    tmp_idx = parent->time_entry.rbe_right;
    if (parent->time_entry.rbe_right = tmp->time_entry.rbe_left)
    {
      tmp->time_entry.rbe_left->time_entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->time_entry.rbe_parent = parent->time_entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->time_entry.rbe_parent->time_entry.rbe_left)
      {
        parent->time_entry.rbe_parent->time_entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->time_entry.rbe_parent->time_entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->time_entry.rbe_left = &parent[parent_idx];
    parent->time_entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->time_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->time_entry.rbe_right;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
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
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_1_2_1(unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->time_entry.rbe_right;
  if (parent->time_entry.rbe_right = tmp->time_entry.rbe_left)
  {
    tmp->time_entry.rbe_left->time_entry.rbe_parent = &parent[parent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->time_entry.rbe_parent = parent->time_entry.rbe_parent)
  {
    if ((&parent[parent_idx]) == parent->time_entry.rbe_parent->time_entry.rbe_left)
    {
      parent->time_entry.rbe_parent->time_entry.rbe_left = &tmp[tmp_idx];
    }
    else
      parent->time_entry.rbe_parent->time_entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->time_entry.rbe_left = &parent[parent_idx];
  parent->time_entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->time_entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
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
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_1_2_2(unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct paste_buffer *oleft;
  unsigned int oleft_idx = 0;
  if (oleft_idx = tmp->time_entry.rbe_left)
  {
    oleft->time_entry.rbe_color = 0;
  }
  tmp->time_entry.rbe_color = 1;
  do
  {
    oleft_idx = tmp->time_entry.rbe_left;
    if (tmp->time_entry.rbe_left = oleft->time_entry.rbe_right)
    {
      oleft->time_entry.rbe_right->time_entry.rbe_parent = &tmp[tmp_idx];
    }
    do
    {
    }
    while (0);
    if (oleft->time_entry.rbe_parent = tmp->time_entry.rbe_parent)
    {
      if ((&tmp[tmp_idx]) == tmp->time_entry.rbe_parent->time_entry.rbe_left)
      {
        tmp->time_entry.rbe_parent->time_entry.rbe_left = &oleft[oleft_idx];
      }
      else
        tmp->time_entry.rbe_parent->time_entry.rbe_right = &oleft[oleft_idx];
    }
    else
      head->rbh_root = &oleft[oleft_idx];
    oleft->time_entry.rbe_right = &tmp[tmp_idx];
    tmp->time_entry.rbe_parent = &oleft[oleft_idx];
    do
    {
    }
    while (0);
    if (oleft->time_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->time_entry.rbe_right;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
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
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->time_entry.rbe_right == 0) || (tmp->time_entry.rbe_right->time_entry.rbe_color == 0))
  {
    helper_helper_helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_1_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->time_entry.rbe_color = parent->time_entry.rbe_color;
  parent->time_entry.rbe_color = 0;
  if (tmp->time_entry.rbe_right)
  {
    tmp->time_entry.rbe_right->time_entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
void helper_helper_helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_1_2_1(unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->time_entry.rbe_right;
  if (parent->time_entry.rbe_right = tmp->time_entry.rbe_left)
  {
    tmp->time_entry.rbe_left->time_entry.rbe_parent = &parent[parent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->time_entry.rbe_parent = parent->time_entry.rbe_parent)
  {
    if ((&parent[parent_idx]) == parent->time_entry.rbe_parent->time_entry.rbe_left)
    {
      parent->time_entry.rbe_parent->time_entry.rbe_left = &tmp[tmp_idx];
    }
    else
      parent->time_entry.rbe_parent->time_entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->time_entry.rbe_left = &parent[parent_idx];
  parent->time_entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->time_entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
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
void helper_helper_helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_1_2_2(unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct paste_buffer *oleft;
  unsigned int oleft_idx = 0;
  if (oleft_idx = tmp->time_entry.rbe_left)
  {
    oleft->time_entry.rbe_color = 0;
  }
  tmp->time_entry.rbe_color = 1;
  do
  {
    oleft_idx = tmp->time_entry.rbe_left;
    if (tmp->time_entry.rbe_left = oleft->time_entry.rbe_right)
    {
      oleft->time_entry.rbe_right->time_entry.rbe_parent = &tmp[tmp_idx];
    }
    do
    {
    }
    while (0);
    if (oleft->time_entry.rbe_parent = tmp->time_entry.rbe_parent)
    {
      if ((&tmp[tmp_idx]) == tmp->time_entry.rbe_parent->time_entry.rbe_left)
      {
        tmp->time_entry.rbe_parent->time_entry.rbe_left = &oleft[oleft_idx];
      }
      else
        tmp->time_entry.rbe_parent->time_entry.rbe_right = &oleft[oleft_idx];
    }
    else
      head->rbh_root = &oleft[oleft_idx];
    oleft->time_entry.rbe_right = &tmp[tmp_idx];
    tmp->time_entry.rbe_parent = &oleft[oleft_idx];
    do
    {
    }
    while (0);
    if (oleft->time_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->time_entry.rbe_right;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const elm, struct paste_buffer * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->time_entry.rbe_right;
  if (tmp->time_entry.rbe_color == 1)
  {
    helper_helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_1_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->time_entry.rbe_left == 0) || (tmp->time_entry.rbe_left->time_entry.rbe_color == 0)) && ((tmp->time_entry.rbe_right == 0) || (tmp->time_entry.rbe_right->time_entry.rbe_color == 0)))
  {
    tmp->time_entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->time_entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_1_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
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
void helper_helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const tmp, unsigned int parent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp->time_entry.rbe_color = 0;
    parent->time_entry.rbe_color = 1;
  }
  while (0);
  do
  {
    tmp_idx = parent->time_entry.rbe_right;
    if (parent->time_entry.rbe_right = tmp->time_entry.rbe_left)
    {
      tmp->time_entry.rbe_left->time_entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->time_entry.rbe_parent = parent->time_entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->time_entry.rbe_parent->time_entry.rbe_left)
      {
        parent->time_entry.rbe_parent->time_entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->time_entry.rbe_parent->time_entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->time_entry.rbe_left = &parent[parent_idx];
    parent->time_entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->time_entry.rbe_parent)
    {
      do
      {
      }
      while (0);
    }
  }
  while (0);
  tmp_idx = parent->time_entry.rbe_right;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->time_entry.rbe_right == 0) || (tmp->time_entry.rbe_right->time_entry.rbe_color == 0))
  {
    helper_helper_helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_1_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->time_entry.rbe_color = parent->time_entry.rbe_color;
  parent->time_entry.rbe_color = 0;
  if (tmp->time_entry.rbe_right)
  {
    tmp->time_entry.rbe_right->time_entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_paste_time_tree_RB_REMOVE_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const elm, struct paste_buffer * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if (parent->time_entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  else
  {
    helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
void helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const elm, struct paste_buffer * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->time_entry.rbe_left;
  if (tmp->time_entry.rbe_color == 1)
  {
    helper_helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->time_entry.rbe_left == 0) || (tmp->time_entry.rbe_left->time_entry.rbe_color == 0)) && ((tmp->time_entry.rbe_right == 0) || (tmp->time_entry.rbe_right->time_entry.rbe_color == 0)))
  {
    tmp->time_entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->time_entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_2_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
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
void helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const elm, struct paste_buffer * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->time_entry.rbe_right;
  if (tmp->time_entry.rbe_color == 1)
  {
    helper_helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_1_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->time_entry.rbe_left == 0) || (tmp->time_entry.rbe_left->time_entry.rbe_color == 0)) && ((tmp->time_entry.rbe_right == 0) || (tmp->time_entry.rbe_right->time_entry.rbe_color == 0)))
  {
    tmp->time_entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->time_entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_1_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
***/


static void paste_time_tree_RB_REMOVE_COLOR(struct paste_time_tree *head, struct paste_buffer *parent, struct paste_buffer *elm)
{
  unsigned int elm_idx = 0;
  unsigned int parent_idx = 0;
  struct paste_buffer *tmp;
  unsigned int tmp_idx = 0;
  while ((((&elm[elm_idx]) == 0) || (elm->time_entry.rbe_color == 0)) && ((&elm[elm_idx]) != head->rbh_root))
  {
    helper_paste_time_tree_RB_REMOVE_COLOR_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }

  if (elm)
  {
    elm->time_entry.rbe_color = 0;
  }
}


/*** DEPENDENCIES:
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
void helper_paste_time_tree_RB_REMOVE_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const parent, struct paste_buffer * const elm, struct paste_buffer * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if (parent->time_entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  else
  {
    helper_helper_paste_time_tree_RB_REMOVE_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'child_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'color_ref is a mutable refrence to int']
void helper_paste_time_tree_RB_REMOVE_1(unsigned int * const elm_idx_ref, unsigned int * const child_idx_ref, unsigned int * const parent_idx_ref, int * const color_ref, struct paste_time_tree * const head, struct paste_buffer * const elm, struct paste_buffer * const child, struct paste_buffer * const parent, struct paste_buffer * const old)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int child_idx = *child_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  int color = *color_ref;
  struct paste_buffer *left;
  unsigned int left_idx = 0;
  elm_idx = elm_idx->time_entry.rbe_right;
  while (left_idx = elm->time_entry.rbe_left)
  {
    elm_idx = &left[left_idx];
  }

  child_idx = elm->time_entry.rbe_right;
  parent_idx = elm->time_entry.rbe_parent;
  color = elm->time_entry.rbe_color;
  if (child)
  {
    child->time_entry.rbe_parent = &parent[parent_idx];
  }
  if (parent)
  {
    if (parent->time_entry.rbe_left == (&elm[elm_idx]))
    {
      parent->time_entry.rbe_left = &child[child_idx];
    }
    else
      parent->time_entry.rbe_right = &child[child_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &child[child_idx];
  if (elm->time_entry.rbe_parent == old)
  {
    parent_idx = &elm[elm_idx];
  }
  elm->time_entry = old->time_entry;
  if (old->time_entry.rbe_parent)
  {
    if (old->time_entry.rbe_parent->time_entry.rbe_left == old)
    {
      old->time_entry.rbe_parent->time_entry.rbe_left = &elm[elm_idx];
    }
    else
      old->time_entry.rbe_parent->time_entry.rbe_right = &elm[elm_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &elm[elm_idx];
  old->time_entry.rbe_left->time_entry.rbe_parent = &elm[elm_idx];
  if (old->time_entry.rbe_right)
  {
    old->time_entry.rbe_right->time_entry.rbe_parent = &elm[elm_idx];
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
    while (left_idx = left_idx->time_entry.rbe_parent);
  }
  goto color;
  *elm_idx_ref = elm_idx;
  *child_idx_ref = child_idx;
  *parent_idx_ref = parent_idx;
  *color_ref = color;
}


/*** DEPENDENCIES:
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
***/


static struct paste_buffer *paste_time_tree_RB_REMOVE(struct paste_time_tree *head, struct paste_buffer *elm)
{
  unsigned int elm_idx = 0;
  struct paste_buffer *child;
  unsigned int child_idx = 0;
  struct paste_buffer *parent;
  unsigned int parent_idx = 0;
  struct paste_buffer *old = elm;
  int color;
  if (elm->time_entry.rbe_left == 0)
  {
    child_idx = elm->time_entry.rbe_right;
  }
  else
    if (elm->time_entry.rbe_right == 0)
  {
    child_idx = elm->time_entry.rbe_left;
  }
  else
  {
    helper_paste_time_tree_RB_REMOVE_1(&elm_idx, &child_idx, &parent_idx, &color, head, elm, child, parent, old);
  }
  parent_idx = elm->time_entry.rbe_parent;
  color = elm->time_entry.rbe_color;
  if (child)
  {
    child->time_entry.rbe_parent = &parent[parent_idx];
  }
  if (parent)
  {
    if (parent->time_entry.rbe_left == (&elm[elm_idx]))
    {
      parent->time_entry.rbe_left = &child[child_idx];
    }
    else
      parent->time_entry.rbe_right = &child[child_idx];
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
    paste_time_tree_RB_REMOVE_COLOR(head, parent, child);
  }

  return old;
}


/*** DEPENDENCIES:
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
static void paste_time_tree_RB_REMOVE_COLOR(struct paste_time_tree *head, struct paste_buffer *parent, struct paste_buffer *elm)
{
  unsigned int elm_idx = 0;
  unsigned int parent_idx = 0;
  struct paste_buffer *tmp;
  unsigned int tmp_idx = 0;
  while ((((&elm[elm_idx]) == 0) || (elm->time_entry.rbe_color == 0)) && ((&elm[elm_idx]) != head->rbh_root))
  {
    helper_paste_time_tree_RB_REMOVE_COLOR_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }

  if (elm)
  {
    elm->time_entry.rbe_color = 0;
  }
}


----------------------------
void helper_paste_time_tree_RB_REMOVE_1(unsigned int * const elm_idx_ref, unsigned int * const child_idx_ref, unsigned int * const parent_idx_ref, int * const color_ref, struct paste_time_tree * const head, struct paste_buffer * const elm, struct paste_buffer * const child, struct paste_buffer * const parent, struct paste_buffer * const old)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int child_idx = *child_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  int color = *color_ref;
  struct paste_buffer *left;
  unsigned int left_idx = 0;
  elm_idx = elm_idx->time_entry.rbe_right;
  while (left_idx = elm->time_entry.rbe_left)
  {
    elm_idx = &left[left_idx];
  }

  child_idx = elm->time_entry.rbe_right;
  parent_idx = elm->time_entry.rbe_parent;
  color = elm->time_entry.rbe_color;
  if (child)
  {
    child->time_entry.rbe_parent = &parent[parent_idx];
  }
  if (parent)
  {
    if (parent->time_entry.rbe_left == (&elm[elm_idx]))
    {
      parent->time_entry.rbe_left = &child[child_idx];
    }
    else
      parent->time_entry.rbe_right = &child[child_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &child[child_idx];
  if (elm->time_entry.rbe_parent == old)
  {
    parent_idx = &elm[elm_idx];
  }
  elm->time_entry = old->time_entry;
  if (old->time_entry.rbe_parent)
  {
    if (old->time_entry.rbe_parent->time_entry.rbe_left == old)
    {
      old->time_entry.rbe_parent->time_entry.rbe_left = &elm[elm_idx];
    }
    else
      old->time_entry.rbe_parent->time_entry.rbe_right = &elm[elm_idx];
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = &elm[elm_idx];
  old->time_entry.rbe_left->time_entry.rbe_parent = &elm[elm_idx];
  if (old->time_entry.rbe_right)
  {
    old->time_entry.rbe_right->time_entry.rbe_parent = &elm[elm_idx];
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
    while (left_idx = left_idx->time_entry.rbe_parent);
  }
  goto color;
  *elm_idx_ref = elm_idx;
  *child_idx_ref = child_idx;
  *parent_idx_ref = parent_idx;
  *color_ref = color;
}


----------------------------
***/


void paste_free(struct paste_buffer *pb)
{
  paste_name_tree_RB_REMOVE(&paste_by_name, pb);
  paste_time_tree_RB_REMOVE(&paste_by_time, pb);
  if (pb->automatic)
  {
    paste_num_automatic -= 1;
  }
  free(pb->data);
  free(pb->name);
  free(pb);
}


/*** DEPENDENCIES:
static struct paste_buffer *paste_name_tree_RB_REMOVE(struct paste_name_tree *head, struct paste_buffer *elm)
{
  unsigned int elm_idx = 0;
  struct paste_buffer *child;
  unsigned int child_idx = 0;
  struct paste_buffer *parent;
  unsigned int parent_idx = 0;
  struct paste_buffer *old = elm;
  int color;
  if (elm->name_entry.rbe_left == 0)
  {
    child_idx = elm->name_entry.rbe_right;
  }
  else
    if (elm->name_entry.rbe_right == 0)
  {
    child_idx = elm->name_entry.rbe_left;
  }
  else
  {
    helper_paste_name_tree_RB_REMOVE_1(&elm_idx, &child_idx, &parent_idx, &color, head, elm, child, parent, old);
  }
  parent_idx = elm->name_entry.rbe_parent;
  color = elm->name_entry.rbe_color;
  if (child)
  {
    child->name_entry.rbe_parent = &parent[parent_idx];
  }
  if (parent)
  {
    if (parent->name_entry.rbe_left == (&elm[elm_idx]))
    {
      parent->name_entry.rbe_left = &child[child_idx];
    }
    else
      parent->name_entry.rbe_right = &child[child_idx];
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
    paste_name_tree_RB_REMOVE_COLOR(head, parent, child);
  }

  return old;
}


----------------------------
static struct paste_name_tree
{
  struct paste_buffer *rbh_root;
} paste_by_name
----------------------------
static struct paste_buffer *paste_time_tree_RB_REMOVE(struct paste_time_tree *head, struct paste_buffer *elm)
{
  unsigned int elm_idx = 0;
  struct paste_buffer *child;
  unsigned int child_idx = 0;
  struct paste_buffer *parent;
  unsigned int parent_idx = 0;
  struct paste_buffer *old = elm;
  int color;
  if (elm->time_entry.rbe_left == 0)
  {
    child_idx = elm->time_entry.rbe_right;
  }
  else
    if (elm->time_entry.rbe_right == 0)
  {
    child_idx = elm->time_entry.rbe_left;
  }
  else
  {
    helper_paste_time_tree_RB_REMOVE_1(&elm_idx, &child_idx, &parent_idx, &color, head, elm, child, parent, old);
  }
  parent_idx = elm->time_entry.rbe_parent;
  color = elm->time_entry.rbe_color;
  if (child)
  {
    child->time_entry.rbe_parent = &parent[parent_idx];
  }
  if (parent)
  {
    if (parent->time_entry.rbe_left == (&elm[elm_idx]))
    {
      parent->time_entry.rbe_left = &child[child_idx];
    }
    else
      parent->time_entry.rbe_right = &child[child_idx];
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
    paste_time_tree_RB_REMOVE_COLOR(head, parent, child);
  }

  return old;
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
static struct paste_time_tree
{
  struct paste_buffer *rbh_root;
} paste_by_time
----------------------------
static u_int paste_num_automatic
----------------------------
***/


static struct paste_buffer *paste_time_tree_RB_PREV(struct paste_buffer *elm)
{
  unsigned int elm_idx = 0;
  if (elm->time_entry.rbe_left)
  {
    elm_idx = elm_idx->time_entry.rbe_left;
    while (elm->time_entry.rbe_right)
    {
      elm_idx = elm_idx->time_entry.rbe_right;
    }

  }
  else
  {
    if (elm->time_entry.rbe_parent && ((&elm[elm_idx]) == elm->time_entry.rbe_parent->time_entry.rbe_right))
    {
      elm_idx = elm_idx->time_entry.rbe_parent;
    }
    else
    {
      while (elm->time_entry.rbe_parent && ((&elm[elm_idx]) == elm->time_entry.rbe_parent->time_entry.rbe_left))
      {
        elm_idx = elm_idx->time_entry.rbe_parent;
      }

      elm_idx = elm_idx->time_entry.rbe_parent;
    }
  }
  return elm;
}


/*** DEPENDENCIES:
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
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_paste_time_tree_RB_INSERT_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const elm, struct paste_buffer * const parent, struct paste_buffer * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp_idx = parent->time_entry.rbe_left;
    if (parent->time_entry.rbe_left = tmp->time_entry.rbe_right)
    {
      tmp->time_entry.rbe_right->time_entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->time_entry.rbe_parent = parent->time_entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->time_entry.rbe_parent->time_entry.rbe_left)
      {
        parent->time_entry.rbe_parent->time_entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->time_entry.rbe_parent->time_entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->time_entry.rbe_right = &parent[parent_idx];
    parent->time_entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->time_entry.rbe_parent)
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
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_paste_time_tree_RB_INSERT_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const gparent, struct paste_buffer * const tmp, unsigned int gparent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->time_entry.rbe_right;
  if (gparent->time_entry.rbe_right = tmp->time_entry.rbe_left)
  {
    tmp->time_entry.rbe_left->time_entry.rbe_parent = &gparent[gparent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->time_entry.rbe_parent = gparent->time_entry.rbe_parent)
  {
    if ((&gparent[gparent_idx]) == gparent->time_entry.rbe_parent->time_entry.rbe_left)
    {
      gparent->time_entry.rbe_parent->time_entry.rbe_left = &tmp[tmp_idx];
    }
    else
      gparent->time_entry.rbe_parent->time_entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->time_entry.rbe_left = &gparent[gparent_idx];
  gparent->time_entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->time_entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
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
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_paste_time_tree_RB_INSERT_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const elm, struct paste_buffer * const parent, struct paste_buffer * const gparent, struct paste_buffer * const tmp, unsigned int gparent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->time_entry.rbe_left;
  if ((&tmp[tmp_idx]) && (tmp->time_entry.rbe_color == 1))
  {
    tmp->time_entry.rbe_color = 0;
    do
    {
      parent->time_entry.rbe_color = 0;
      gparent->time_entry.rbe_color = 1;
    }
    while (0);
    elm_idx = &gparent[gparent_idx];
    continue;
  }
  if (parent->time_entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_helper_paste_time_tree_RB_INSERT_COLOR_1_2_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->time_entry.rbe_color = 0;
    gparent->time_entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_paste_time_tree_RB_INSERT_COLOR_1_2_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
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
void helper_helper_helper_paste_time_tree_RB_INSERT_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const elm, struct paste_buffer * const parent, struct paste_buffer * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp_idx = parent->time_entry.rbe_left;
    if (parent->time_entry.rbe_left = tmp->time_entry.rbe_right)
    {
      tmp->time_entry.rbe_right->time_entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->time_entry.rbe_parent = parent->time_entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->time_entry.rbe_parent->time_entry.rbe_left)
      {
        parent->time_entry.rbe_parent->time_entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->time_entry.rbe_parent->time_entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->time_entry.rbe_right = &parent[parent_idx];
    parent->time_entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->time_entry.rbe_parent)
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
void helper_helper_helper_paste_time_tree_RB_INSERT_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const gparent, struct paste_buffer * const tmp, unsigned int gparent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->time_entry.rbe_right;
  if (gparent->time_entry.rbe_right = tmp->time_entry.rbe_left)
  {
    tmp->time_entry.rbe_left->time_entry.rbe_parent = &gparent[gparent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->time_entry.rbe_parent = gparent->time_entry.rbe_parent)
  {
    if ((&gparent[gparent_idx]) == gparent->time_entry.rbe_parent->time_entry.rbe_left)
    {
      gparent->time_entry.rbe_parent->time_entry.rbe_left = &tmp[tmp_idx];
    }
    else
      gparent->time_entry.rbe_parent->time_entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->time_entry.rbe_left = &gparent[gparent_idx];
  gparent->time_entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->time_entry.rbe_parent)
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
void helper_helper_helper_paste_time_tree_RB_INSERT_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const elm, struct paste_buffer * const parent, struct paste_buffer * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp_idx = parent->time_entry.rbe_right;
    if (parent->time_entry.rbe_right = tmp->time_entry.rbe_left)
    {
      tmp->time_entry.rbe_left->time_entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->time_entry.rbe_parent = parent->time_entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->time_entry.rbe_parent->time_entry.rbe_left)
      {
        parent->time_entry.rbe_parent->time_entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->time_entry.rbe_parent->time_entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->time_entry.rbe_left = &parent[parent_idx];
    parent->time_entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->time_entry.rbe_parent)
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
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_paste_time_tree_RB_INSERT_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const gparent, struct paste_buffer * const tmp, unsigned int gparent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->time_entry.rbe_left;
  if (gparent->time_entry.rbe_left = tmp->time_entry.rbe_right)
  {
    tmp->time_entry.rbe_right->time_entry.rbe_parent = &gparent[gparent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->time_entry.rbe_parent = gparent->time_entry.rbe_parent)
  {
    if ((&gparent[gparent_idx]) == gparent->time_entry.rbe_parent->time_entry.rbe_left)
    {
      gparent->time_entry.rbe_parent->time_entry.rbe_left = &tmp[tmp_idx];
    }
    else
      gparent->time_entry.rbe_parent->time_entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->time_entry.rbe_right = &gparent[gparent_idx];
  gparent->time_entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->time_entry.rbe_parent)
  {
    do
    {
    }
    while (0);
  }
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
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
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_paste_time_tree_RB_INSERT_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const elm, struct paste_buffer * const parent, struct paste_buffer * const gparent, struct paste_buffer * const tmp, unsigned int gparent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->time_entry.rbe_right;
  if ((&tmp[tmp_idx]) && (tmp->time_entry.rbe_color == 1))
  {
    tmp->time_entry.rbe_color = 0;
    do
    {
      parent->time_entry.rbe_color = 0;
      gparent->time_entry.rbe_color = 1;
    }
    while (0);
    elm_idx = &gparent[gparent_idx];
    continue;
  }
  if (parent->time_entry.rbe_right == (&elm[elm_idx]))
  {
    helper_helper_helper_paste_time_tree_RB_INSERT_COLOR_1_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->time_entry.rbe_color = 0;
    gparent->time_entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_paste_time_tree_RB_INSERT_COLOR_1_1_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
void helper_helper_helper_paste_time_tree_RB_INSERT_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const elm, struct paste_buffer * const parent, struct paste_buffer * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  do
  {
    tmp_idx = parent->time_entry.rbe_right;
    if (parent->time_entry.rbe_right = tmp->time_entry.rbe_left)
    {
      tmp->time_entry.rbe_left->time_entry.rbe_parent = &parent[parent_idx];
    }
    do
    {
    }
    while (0);
    if (tmp->time_entry.rbe_parent = parent->time_entry.rbe_parent)
    {
      if ((&parent[parent_idx]) == parent->time_entry.rbe_parent->time_entry.rbe_left)
      {
        parent->time_entry.rbe_parent->time_entry.rbe_left = &tmp[tmp_idx];
      }
      else
        parent->time_entry.rbe_parent->time_entry.rbe_right = &tmp[tmp_idx];
    }
    else
      head->rbh_root = &tmp[tmp_idx];
    tmp->time_entry.rbe_left = &parent[parent_idx];
    parent->time_entry.rbe_parent = &tmp[tmp_idx];
    do
    {
    }
    while (0);
    if (tmp->time_entry.rbe_parent)
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
void helper_helper_helper_paste_time_tree_RB_INSERT_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const gparent, struct paste_buffer * const tmp, unsigned int gparent_idx)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->time_entry.rbe_left;
  if (gparent->time_entry.rbe_left = tmp->time_entry.rbe_right)
  {
    tmp->time_entry.rbe_right->time_entry.rbe_parent = &gparent[gparent_idx];
  }
  do
  {
  }
  while (0);
  if (tmp->time_entry.rbe_parent = gparent->time_entry.rbe_parent)
  {
    if ((&gparent[gparent_idx]) == gparent->time_entry.rbe_parent->time_entry.rbe_left)
    {
      gparent->time_entry.rbe_parent->time_entry.rbe_left = &tmp[tmp_idx];
    }
    else
      gparent->time_entry.rbe_parent->time_entry.rbe_right = &tmp[tmp_idx];
  }
  else
    head->rbh_root = &tmp[tmp_idx];
  tmp->time_entry.rbe_right = &gparent[gparent_idx];
  gparent->time_entry.rbe_parent = &tmp[tmp_idx];
  do
  {
  }
  while (0);
  if (tmp->time_entry.rbe_parent)
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
void helper_paste_time_tree_RB_INSERT_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const gparent_idx_ref, unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const elm, struct paste_buffer * const parent, struct paste_buffer * const gparent, struct paste_buffer * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int gparent_idx = *gparent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  gparent_idx = parent->time_entry.rbe_parent;
  if ((&parent[parent_idx]) == gparent->time_entry.rbe_left)
  {
    helper_helper_paste_time_tree_RB_INSERT_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  else
  {
    helper_helper_paste_time_tree_RB_INSERT_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *gparent_idx_ref = gparent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
void helper_helper_paste_time_tree_RB_INSERT_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const elm, struct paste_buffer * const parent, struct paste_buffer * const gparent, struct paste_buffer * const tmp, unsigned int gparent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->time_entry.rbe_left;
  if ((&tmp[tmp_idx]) && (tmp->time_entry.rbe_color == 1))
  {
    tmp->time_entry.rbe_color = 0;
    do
    {
      parent->time_entry.rbe_color = 0;
      gparent->time_entry.rbe_color = 1;
    }
    while (0);
    elm_idx = &gparent[gparent_idx];
    continue;
  }
  if (parent->time_entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_helper_paste_time_tree_RB_INSERT_COLOR_1_2_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->time_entry.rbe_color = 0;
    gparent->time_entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_paste_time_tree_RB_INSERT_COLOR_1_2_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
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
void helper_helper_paste_time_tree_RB_INSERT_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const elm, struct paste_buffer * const parent, struct paste_buffer * const gparent, struct paste_buffer * const tmp, unsigned int gparent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = gparent->time_entry.rbe_right;
  if ((&tmp[tmp_idx]) && (tmp->time_entry.rbe_color == 1))
  {
    tmp->time_entry.rbe_color = 0;
    do
    {
      parent->time_entry.rbe_color = 0;
      gparent->time_entry.rbe_color = 1;
    }
    while (0);
    elm_idx = &gparent[gparent_idx];
    continue;
  }
  if (parent->time_entry.rbe_right == (&elm[elm_idx]))
  {
    helper_helper_helper_paste_time_tree_RB_INSERT_COLOR_1_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->time_entry.rbe_color = 0;
    gparent->time_entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_paste_time_tree_RB_INSERT_COLOR_1_1_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
***/


static void paste_time_tree_RB_INSERT_COLOR(struct paste_time_tree *head, struct paste_buffer *elm)
{
  unsigned int elm_idx = 0;
  struct paste_buffer *parent;
  unsigned int parent_idx = 0;
  struct paste_buffer *gparent;
  unsigned int gparent_idx = 0;
  struct paste_buffer *tmp;
  unsigned int tmp_idx = 0;
  while ((parent_idx = elm->time_entry.rbe_parent) && (parent->time_entry.rbe_color == 1))
  {
    helper_paste_time_tree_RB_INSERT_COLOR_1(&elm_idx, &parent_idx, &gparent_idx, &tmp_idx, head, elm, parent, gparent, tmp);
  }

  head->rbh_root->time_entry.rbe_color = 0;
}


/*** DEPENDENCIES:
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
void helper_paste_time_tree_RB_INSERT_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const gparent_idx_ref, unsigned int * const tmp_idx_ref, struct paste_time_tree * const head, struct paste_buffer * const elm, struct paste_buffer * const parent, struct paste_buffer * const gparent, struct paste_buffer * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int gparent_idx = *gparent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  gparent_idx = parent->time_entry.rbe_parent;
  if ((&parent[parent_idx]) == gparent->time_entry.rbe_left)
  {
    helper_helper_paste_time_tree_RB_INSERT_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  else
  {
    helper_helper_paste_time_tree_RB_INSERT_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *gparent_idx_ref = gparent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
***/


static int paste_cmp_times(const struct paste_buffer *a, const struct paste_buffer *b)
{
  if (a->order > b->order)
  {
    return -1;
  }
  if (a->order < b->order)
  {
    return 1;
  }
  return 0;
}


/*** DEPENDENCIES:
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
***/


static struct paste_buffer *paste_time_tree_RB_INSERT(struct paste_time_tree *head, struct paste_buffer *elm)
{
  struct paste_buffer *tmp;
  unsigned int tmp_idx = 0;
  struct paste_buffer *parent = 0;
  unsigned int parent_idx = 0;
  int comp = 0;
  tmp_idx = head->rbh_root;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    comp = paste_cmp_times(elm, parent);
    if (comp < 0)
    {
      tmp_idx = tmp_idx->time_entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->time_entry.rbe_right;
    }
    else
      return tmp;
  }

  do
  {
    elm->time_entry.rbe_parent = &parent[parent_idx];
    elm->time_entry.rbe_left = (elm->time_entry.rbe_right = 0);
    elm->time_entry.rbe_color = 1;
  }
  while (0);
  if ((&parent[parent_idx]) != 0)
  {
    if (comp < 0)
    {
      parent->time_entry.rbe_left = elm;
    }
    else
      parent->time_entry.rbe_right = elm;
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = elm;
  paste_time_tree_RB_INSERT_COLOR(head, elm);
  return 0;
}


/*** DEPENDENCIES:
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
static void paste_time_tree_RB_INSERT_COLOR(struct paste_time_tree *head, struct paste_buffer *elm)
{
  unsigned int elm_idx = 0;
  struct paste_buffer *parent;
  unsigned int parent_idx = 0;
  struct paste_buffer *gparent;
  unsigned int gparent_idx = 0;
  struct paste_buffer *tmp;
  unsigned int tmp_idx = 0;
  while ((parent_idx = elm->time_entry.rbe_parent) && (parent->time_entry.rbe_color == 1))
  {
    helper_paste_time_tree_RB_INSERT_COLOR_1(&elm_idx, &parent_idx, &gparent_idx, &tmp_idx, head, elm, parent, gparent, tmp);
  }

  head->rbh_root->time_entry.rbe_color = 0;
}


----------------------------
static int paste_cmp_times(const struct paste_buffer *a, const struct paste_buffer *b)
{
  if (a->order > b->order)
  {
    return -1;
  }
  if (a->order < b->order)
  {
    return 1;
  }
  return 0;
}


----------------------------
***/


void paste_add(char *data, size_t size)
{
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  struct paste_buffer *pb1;
  unsigned int pb1_idx = 0;
  u_int limit;
  if (size == 0)
  {
    free(data);
    return;
  }
  limit = options_get_number(global_options, "buffer-limit");
  for (pb_idx = paste_time_tree_RB_MINMAX(&paste_by_time, 1); ((&pb[pb_idx]) != 0) && ((pb1_idx = paste_time_tree_RB_PREV(pb), 1)); pb_idx = &pb1[pb1_idx])
  {
    if (paste_num_automatic < limit)
    {
      break;
    }
    if (pb->automatic)
    {
      paste_free(pb);
    }
  }

  pb_idx = xmalloc(sizeof(*pb_idx));
  pb->name = 0;
  do
  {
    free(pb->name);
    xasprintf(&pb->name, "buffer%04u", paste_next_index);
    paste_next_index += 1;
  }
  while (paste_get_name(pb->name) != 0);
  pb->data = data;
  pb->size = size;
  pb->automatic = 1;
  paste_num_automatic += 1;
  pb->created = time(0);
  pb->order = paste_next_order;
  paste_next_order += 1;
  paste_name_tree_RB_INSERT(&paste_by_name, pb);
  paste_time_tree_RB_INSERT(&paste_by_time, pb);
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
static struct paste_name_tree
{
  struct paste_buffer *rbh_root;
} paste_by_name
----------------------------
static struct paste_buffer *paste_time_tree_RB_MINMAX(struct paste_time_tree *head, int val)
{
  struct paste_buffer *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct paste_buffer *parent = 0;
  unsigned int parent_idx = 0;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    if (val < 0)
    {
      tmp_idx = tmp_idx->time_entry.rbe_left;
    }
    else
      tmp_idx = tmp_idx->time_entry.rbe_right;
  }

  return parent;
}


----------------------------
static u_int paste_next_index
----------------------------
static struct paste_time_tree
{
  struct paste_buffer *rbh_root;
} paste_by_time
----------------------------
struct paste_buffer *paste_get_name(const char *name)
{
  struct paste_buffer pbfind;
  if ((name == 0) || ((*name) == '\0'))
  {
    return 0;
  }
  pbfind.name = (char *) name;
  return paste_name_tree_RB_FIND(&paste_by_name, &pbfind);
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
static struct paste_buffer *paste_name_tree_RB_INSERT(struct paste_name_tree *head, struct paste_buffer *elm)
{
  struct paste_buffer *tmp;
  unsigned int tmp_idx = 0;
  struct paste_buffer *parent = 0;
  unsigned int parent_idx = 0;
  int comp = 0;
  tmp_idx = head->rbh_root;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    comp = paste_cmp_names(elm, parent);
    if (comp < 0)
    {
      tmp_idx = tmp_idx->name_entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->name_entry.rbe_right;
    }
    else
      return tmp;
  }

  do
  {
    elm->name_entry.rbe_parent = &parent[parent_idx];
    elm->name_entry.rbe_left = (elm->name_entry.rbe_right = 0);
    elm->name_entry.rbe_color = 1;
  }
  while (0);
  if ((&parent[parent_idx]) != 0)
  {
    if (comp < 0)
    {
      parent->name_entry.rbe_left = elm;
    }
    else
      parent->name_entry.rbe_right = elm;
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = elm;
  paste_name_tree_RB_INSERT_COLOR(head, elm);
  return 0;
}


----------------------------
void paste_free(struct paste_buffer *pb)
{
  paste_name_tree_RB_REMOVE(&paste_by_name, pb);
  paste_time_tree_RB_REMOVE(&paste_by_time, pb);
  if (pb->automatic)
  {
    paste_num_automatic -= 1;
  }
  free(pb->data);
  free(pb->name);
  free(pb);
}


----------------------------
static u_int paste_num_automatic
----------------------------
static struct paste_buffer *paste_time_tree_RB_PREV(struct paste_buffer *elm)
{
  unsigned int elm_idx = 0;
  if (elm->time_entry.rbe_left)
  {
    elm_idx = elm_idx->time_entry.rbe_left;
    while (elm->time_entry.rbe_right)
    {
      elm_idx = elm_idx->time_entry.rbe_right;
    }

  }
  else
  {
    if (elm->time_entry.rbe_parent && ((&elm[elm_idx]) == elm->time_entry.rbe_parent->time_entry.rbe_right))
    {
      elm_idx = elm_idx->time_entry.rbe_parent;
    }
    else
    {
      while (elm->time_entry.rbe_parent && ((&elm[elm_idx]) == elm->time_entry.rbe_parent->time_entry.rbe_left))
      {
        elm_idx = elm_idx->time_entry.rbe_parent;
      }

      elm_idx = elm_idx->time_entry.rbe_parent;
    }
  }
  return elm;
}


----------------------------
static u_int paste_next_order
----------------------------
static struct paste_buffer *paste_time_tree_RB_INSERT(struct paste_time_tree *head, struct paste_buffer *elm)
{
  struct paste_buffer *tmp;
  unsigned int tmp_idx = 0;
  struct paste_buffer *parent = 0;
  unsigned int parent_idx = 0;
  int comp = 0;
  tmp_idx = head->rbh_root;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    comp = paste_cmp_times(elm, parent);
    if (comp < 0)
    {
      tmp_idx = tmp_idx->time_entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->time_entry.rbe_right;
    }
    else
      return tmp;
  }

  do
  {
    elm->time_entry.rbe_parent = &parent[parent_idx];
    elm->time_entry.rbe_left = (elm->time_entry.rbe_right = 0);
    elm->time_entry.rbe_color = 1;
  }
  while (0);
  if ((&parent[parent_idx]) != 0)
  {
    if (comp < 0)
    {
      parent->time_entry.rbe_left = elm;
    }
    else
      parent->time_entry.rbe_right = elm;
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = elm;
  paste_time_tree_RB_INSERT_COLOR(head, elm);
  return 0;
}


----------------------------
pub time: Time
----------------------------
***/


const char *paste_buffer_name(struct paste_buffer *pb)
{
  return pb->name;
}


/*** DEPENDENCIES:
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
***/


u_int paste_buffer_order(struct paste_buffer *pb)
{
  return pb->order;
}


/*** DEPENDENCIES:
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
***/


time_t paste_buffer_created(struct paste_buffer *pb)
{
  return pb->created;
}


/*** DEPENDENCIES:
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
***/


const char *paste_buffer_data(struct paste_buffer *pb, size_t *size)
{
  if (size != 0)
  {
    *size = pb->size;
  }
  return pb->data;
}


/*** DEPENDENCIES:
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
***/


static struct paste_buffer *paste_name_tree_RB_NEXT(struct paste_buffer *elm)
{
  unsigned int elm_idx = 0;
  if (elm->name_entry.rbe_right)
  {
    elm_idx = elm_idx->name_entry.rbe_right;
    while (elm->name_entry.rbe_left)
    {
      elm_idx = elm_idx->name_entry.rbe_left;
    }

  }
  else
  {
    if (elm->name_entry.rbe_parent && ((&elm[elm_idx]) == elm->name_entry.rbe_parent->name_entry.rbe_left))
    {
      elm_idx = elm_idx->name_entry.rbe_parent;
    }
    else
    {
      while (elm->name_entry.rbe_parent && ((&elm[elm_idx]) == elm->name_entry.rbe_parent->name_entry.rbe_right))
      {
        elm_idx = elm_idx->name_entry.rbe_parent;
      }

      elm_idx = elm_idx->name_entry.rbe_parent;
    }
  }
  return elm;
}


/*** DEPENDENCIES:
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
***/


static struct paste_buffer *paste_name_tree_RB_PREV(struct paste_buffer *elm)
{
  unsigned int elm_idx = 0;
  if (elm->name_entry.rbe_left)
  {
    elm_idx = elm_idx->name_entry.rbe_left;
    while (elm->name_entry.rbe_right)
    {
      elm_idx = elm_idx->name_entry.rbe_right;
    }

  }
  else
  {
    if (elm->name_entry.rbe_parent && ((&elm[elm_idx]) == elm->name_entry.rbe_parent->name_entry.rbe_right))
    {
      elm_idx = elm_idx->name_entry.rbe_parent;
    }
    else
    {
      while (elm->name_entry.rbe_parent && ((&elm[elm_idx]) == elm->name_entry.rbe_parent->name_entry.rbe_left))
      {
        elm_idx = elm_idx->name_entry.rbe_parent;
      }

      elm_idx = elm_idx->name_entry.rbe_parent;
    }
  }
  return elm;
}


/*** DEPENDENCIES:
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
***/


static struct paste_buffer *paste_name_tree_RB_MINMAX(struct paste_name_tree *head, int val)
{
  struct paste_buffer *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct paste_buffer *parent = 0;
  unsigned int parent_idx = 0;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    if (val < 0)
    {
      tmp_idx = tmp_idx->name_entry.rbe_left;
    }
    else
      tmp_idx = tmp_idx->name_entry.rbe_right;
  }

  return parent;
}


/*** DEPENDENCIES:
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
***/


static struct paste_buffer *paste_time_tree_RB_NEXT(struct paste_buffer *elm)
{
  unsigned int elm_idx = 0;
  if (elm->time_entry.rbe_right)
  {
    elm_idx = elm_idx->time_entry.rbe_right;
    while (elm->time_entry.rbe_left)
    {
      elm_idx = elm_idx->time_entry.rbe_left;
    }

  }
  else
  {
    if (elm->time_entry.rbe_parent && ((&elm[elm_idx]) == elm->time_entry.rbe_parent->time_entry.rbe_left))
    {
      elm_idx = elm_idx->time_entry.rbe_parent;
    }
    else
    {
      while (elm->time_entry.rbe_parent && ((&elm[elm_idx]) == elm->time_entry.rbe_parent->time_entry.rbe_right))
      {
        elm_idx = elm_idx->time_entry.rbe_parent;
      }

      elm_idx = elm_idx->time_entry.rbe_parent;
    }
  }
  return elm;
}


/*** DEPENDENCIES:
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
***/


static struct paste_buffer *paste_name_tree_RB_NFIND(struct paste_name_tree *head, struct paste_buffer *elm)
{
  struct paste_buffer *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct paste_buffer *res = 0;
  unsigned int res_idx = 0;
  int comp;
  while (tmp)
  {
    comp = paste_cmp_names(elm, tmp);
    if (comp < 0)
    {
      res_idx = &tmp[tmp_idx];
      tmp_idx = tmp_idx->name_entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->name_entry.rbe_right;
    }
    else
      return tmp;
  }

  return res;
}


/*** DEPENDENCIES:
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
static int paste_cmp_names(const struct paste_buffer *a, const struct paste_buffer *b)
{
  return strcmp(a->name, b->name);
}


----------------------------
***/


static struct paste_buffer *paste_time_tree_RB_FIND(struct paste_time_tree *head, struct paste_buffer *elm)
{
  struct paste_buffer *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  int comp;
  while (tmp)
  {
    comp = paste_cmp_times(elm, tmp);
    if (comp < 0)
    {
      tmp_idx = tmp_idx->time_entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->time_entry.rbe_right;
    }
    else
      return tmp;
  }

  return 0;
}


/*** DEPENDENCIES:
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
static int paste_cmp_times(const struct paste_buffer *a, const struct paste_buffer *b)
{
  if (a->order > b->order)
  {
    return -1;
  }
  if (a->order < b->order)
  {
    return 1;
  }
  return 0;
}


----------------------------
***/


static struct paste_buffer *paste_time_tree_RB_NFIND(struct paste_time_tree *head, struct paste_buffer *elm)
{
  struct paste_buffer *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct paste_buffer *res = 0;
  unsigned int res_idx = 0;
  int comp;
  while (tmp)
  {
    comp = paste_cmp_times(elm, tmp);
    if (comp < 0)
    {
      res_idx = &tmp[tmp_idx];
      tmp_idx = tmp_idx->time_entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->time_entry.rbe_right;
    }
    else
      return tmp;
  }

  return res;
}


/*** DEPENDENCIES:
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
static int paste_cmp_times(const struct paste_buffer *a, const struct paste_buffer *b)
{
  if (a->order > b->order)
  {
    return -1;
  }
  if (a->order < b->order)
  {
    return 1;
  }
  return 0;
}


----------------------------
***/


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


/*** DEPENDENCIES:
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
static struct paste_time_tree
{
  struct paste_buffer *rbh_root;
} paste_by_time
----------------------------
static struct paste_buffer *paste_time_tree_RB_MINMAX(struct paste_time_tree *head, int val)
{
  struct paste_buffer *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct paste_buffer *parent = 0;
  unsigned int parent_idx = 0;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    if (val < 0)
    {
      tmp_idx = tmp_idx->time_entry.rbe_left;
    }
    else
      tmp_idx = tmp_idx->time_entry.rbe_right;
  }

  return parent;
}


----------------------------
***/


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
int utf8_strvis(char *dst, const char *src, size_t len, int flag)
{
  unsigned int src_idx = 0;
  unsigned int dst_idx = 0;
  struct utf8_data ud;
  const char *start;
  unsigned int start_idx = 0;
  const char *end;
  unsigned int end_idx = 0;
  enum utf8_state more;
  size_t i;
  start_idx = &dst[dst_idx];
  end_idx = (&src[src_idx]) + len;
  while ((&src[src_idx]) < (&end[end_idx]))
  {
    if ((more = utf8_open(&ud, *(&src[src_idx]))) == UTF8_MORE)
    {
      while (((++(&src[src_idx])) < (&end[end_idx])) && (more == UTF8_MORE))
      {
        more = utf8_append(&ud, *(&src[src_idx]));
      }

      if (more == UTF8_DONE)
      {
        for (i = 0; i < ud.size; i += 1)
        {
          dst[dst_idx] = ud.data[i];
          dst_idx += 1;
        }

        continue;
      }
      src_idx -= ud.have;
    }
    if ((&src[src_idx]) < ((&end[end_idx]) - 1))
    {
      dst_idx = vis(dst_idx, src[0 + src_idx], flag, src[1 + src_idx]);
    }
    else
      if ((&src[src_idx]) < (&end[end_idx]))
    {
      dst_idx = vis(dst_idx, src[0 + src_idx], flag, '\0');
    }
    src_idx += 1;
  }

  dst[dst_idx] = '\0';
  return (&dst[dst_idx]) - (&start[start_idx]);
}


----------------------------
***/


struct paste_buffer *paste_walk(struct paste_buffer *pb)
{
  if (pb == 0)
  {
    return paste_time_tree_RB_MINMAX(&paste_by_time, -1);
  }
  return paste_time_tree_RB_NEXT(pb);
}


/*** DEPENDENCIES:
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
static struct paste_buffer *paste_time_tree_RB_NEXT(struct paste_buffer *elm)
{
  unsigned int elm_idx = 0;
  if (elm->time_entry.rbe_right)
  {
    elm_idx = elm_idx->time_entry.rbe_right;
    while (elm->time_entry.rbe_left)
    {
      elm_idx = elm_idx->time_entry.rbe_left;
    }

  }
  else
  {
    if (elm->time_entry.rbe_parent && ((&elm[elm_idx]) == elm->time_entry.rbe_parent->time_entry.rbe_left))
    {
      elm_idx = elm_idx->time_entry.rbe_parent;
    }
    else
    {
      while (elm->time_entry.rbe_parent && ((&elm[elm_idx]) == elm->time_entry.rbe_parent->time_entry.rbe_right))
      {
        elm_idx = elm_idx->time_entry.rbe_parent;
      }

      elm_idx = elm_idx->time_entry.rbe_parent;
    }
  }
  return elm;
}


----------------------------
static struct paste_time_tree
{
  struct paste_buffer *rbh_root;
} paste_by_time
----------------------------
static struct paste_buffer *paste_time_tree_RB_MINMAX(struct paste_time_tree *head, int val)
{
  struct paste_buffer *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct paste_buffer *parent = 0;
  unsigned int parent_idx = 0;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    if (val < 0)
    {
      tmp_idx = tmp_idx->time_entry.rbe_left;
    }
    else
      tmp_idx = tmp_idx->time_entry.rbe_right;
  }

  return parent;
}


----------------------------
***/


int paste_set(char *data, size_t size, const char *name, char **cause)
{
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  struct paste_buffer *old;
  unsigned int old_idx = 0;
  if (cause != 0)
  {
    *cause = 0;
  }
  if (size == 0)
  {
    free(data);
    return 0;
  }
  if (name == 0)
  {
    paste_add(data, size);
    return 0;
  }
  if ((*name) == '\0')
  {
    if (cause != 0)
    {
      *cause = xstrdup("empty buffer name");
    }
    return -1;
  }
  pb_idx = xmalloc(sizeof(*pb_idx));
  pb->name = xstrdup(name);
  pb->data = data;
  pb->size = size;
  pb->automatic = 0;
  pb->order = paste_next_order;
  paste_next_order += 1;
  pb->created = time(0);
  if ((old_idx = paste_get_name(name)) != 0)
  {
    paste_free(old);
  }
  paste_name_tree_RB_INSERT(&paste_by_name, pb);
  paste_time_tree_RB_INSERT(&paste_by_time, pb);
  return 0;
}


/*** DEPENDENCIES:
static struct paste_name_tree
{
  struct paste_buffer *rbh_root;
} paste_by_name
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
void paste_add(char *data, size_t size)
{
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  struct paste_buffer *pb1;
  unsigned int pb1_idx = 0;
  u_int limit;
  if (size == 0)
  {
    free(data);
    return;
  }
  limit = options_get_number(global_options, "buffer-limit");
  for (pb_idx = paste_time_tree_RB_MINMAX(&paste_by_time, 1); ((&pb[pb_idx]) != 0) && ((pb1_idx = paste_time_tree_RB_PREV(pb), 1)); pb_idx = &pb1[pb1_idx])
  {
    if (paste_num_automatic < limit)
    {
      break;
    }
    if (pb->automatic)
    {
      paste_free(pb);
    }
  }

  pb_idx = xmalloc(sizeof(*pb_idx));
  pb->name = 0;
  do
  {
    free(pb->name);
    xasprintf(&pb->name, "buffer%04u", paste_next_index);
    paste_next_index += 1;
  }
  while (paste_get_name(pb->name) != 0);
  pb->data = data;
  pb->size = size;
  pb->automatic = 1;
  paste_num_automatic += 1;
  pb->created = time(0);
  pb->order = paste_next_order;
  paste_next_order += 1;
  paste_name_tree_RB_INSERT(&paste_by_name, pb);
  paste_time_tree_RB_INSERT(&paste_by_time, pb);
}


----------------------------
static struct paste_time_tree
{
  struct paste_buffer *rbh_root;
} paste_by_time
----------------------------
struct paste_buffer *paste_get_name(const char *name)
{
  struct paste_buffer pbfind;
  if ((name == 0) || ((*name) == '\0'))
  {
    return 0;
  }
  pbfind.name = (char *) name;
  return paste_name_tree_RB_FIND(&paste_by_name, &pbfind);
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
static struct paste_buffer *paste_name_tree_RB_INSERT(struct paste_name_tree *head, struct paste_buffer *elm)
{
  struct paste_buffer *tmp;
  unsigned int tmp_idx = 0;
  struct paste_buffer *parent = 0;
  unsigned int parent_idx = 0;
  int comp = 0;
  tmp_idx = head->rbh_root;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    comp = paste_cmp_names(elm, parent);
    if (comp < 0)
    {
      tmp_idx = tmp_idx->name_entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->name_entry.rbe_right;
    }
    else
      return tmp;
  }

  do
  {
    elm->name_entry.rbe_parent = &parent[parent_idx];
    elm->name_entry.rbe_left = (elm->name_entry.rbe_right = 0);
    elm->name_entry.rbe_color = 1;
  }
  while (0);
  if ((&parent[parent_idx]) != 0)
  {
    if (comp < 0)
    {
      parent->name_entry.rbe_left = elm;
    }
    else
      parent->name_entry.rbe_right = elm;
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = elm;
  paste_name_tree_RB_INSERT_COLOR(head, elm);
  return 0;
}


----------------------------
void paste_free(struct paste_buffer *pb)
{
  paste_name_tree_RB_REMOVE(&paste_by_name, pb);
  paste_time_tree_RB_REMOVE(&paste_by_time, pb);
  if (pb->automatic)
  {
    paste_num_automatic -= 1;
  }
  free(pb->data);
  free(pb->name);
  free(pb);
}


----------------------------
static u_int paste_next_order
----------------------------
static struct paste_buffer *paste_time_tree_RB_INSERT(struct paste_time_tree *head, struct paste_buffer *elm)
{
  struct paste_buffer *tmp;
  unsigned int tmp_idx = 0;
  struct paste_buffer *parent = 0;
  unsigned int parent_idx = 0;
  int comp = 0;
  tmp_idx = head->rbh_root;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    comp = paste_cmp_times(elm, parent);
    if (comp < 0)
    {
      tmp_idx = tmp_idx->time_entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->time_entry.rbe_right;
    }
    else
      return tmp;
  }

  do
  {
    elm->time_entry.rbe_parent = &parent[parent_idx];
    elm->time_entry.rbe_left = (elm->time_entry.rbe_right = 0);
    elm->time_entry.rbe_color = 1;
  }
  while (0);
  if ((&parent[parent_idx]) != 0)
  {
    if (comp < 0)
    {
      parent->time_entry.rbe_left = elm;
    }
    else
      parent->time_entry.rbe_right = elm;
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = elm;
  paste_time_tree_RB_INSERT_COLOR(head, elm);
  return 0;
}


----------------------------
pub time: Time
----------------------------
***/


int paste_rename(const char *oldname, const char *newname, char **cause)
{
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  struct paste_buffer *pb_new;
  unsigned int pb_new_idx = 0;
  if (cause != 0)
  {
    *cause = 0;
  }
  if ((oldname == 0) || ((*oldname) == '\0'))
  {
    if (cause != 0)
    {
      *cause = xstrdup("no buffer");
    }
    return -1;
  }
  if ((newname == 0) || ((*newname) == '\0'))
  {
    if (cause != 0)
    {
      *cause = xstrdup("new name is empty");
    }
    return -1;
  }
  pb_idx = paste_get_name(oldname);
  if ((&pb[pb_idx]) == 0)
  {
    if (cause != 0)
    {
      xasprintf(cause, "no buffer %s", oldname);
    }
    return -1;
  }
  pb_new_idx = paste_get_name(newname);
  if ((&pb_new[pb_new_idx]) != 0)
  {
    if (cause != 0)
    {
      xasprintf(cause, "buffer %s already exists", newname);
    }
    return -1;
  }
  paste_name_tree_RB_REMOVE(&paste_by_name, pb);
  free(pb->name);
  pb->name = xstrdup(newname);
  if (pb->automatic)
  {
    paste_num_automatic -= 1;
  }
  pb->automatic = 0;
  paste_name_tree_RB_INSERT(&paste_by_name, pb);
  return 0;
}


/*** DEPENDENCIES:
static struct paste_buffer *paste_name_tree_RB_REMOVE(struct paste_name_tree *head, struct paste_buffer *elm)
{
  unsigned int elm_idx = 0;
  struct paste_buffer *child;
  unsigned int child_idx = 0;
  struct paste_buffer *parent;
  unsigned int parent_idx = 0;
  struct paste_buffer *old = elm;
  int color;
  if (elm->name_entry.rbe_left == 0)
  {
    child_idx = elm->name_entry.rbe_right;
  }
  else
    if (elm->name_entry.rbe_right == 0)
  {
    child_idx = elm->name_entry.rbe_left;
  }
  else
  {
    helper_paste_name_tree_RB_REMOVE_1(&elm_idx, &child_idx, &parent_idx, &color, head, elm, child, parent, old);
  }
  parent_idx = elm->name_entry.rbe_parent;
  color = elm->name_entry.rbe_color;
  if (child)
  {
    child->name_entry.rbe_parent = &parent[parent_idx];
  }
  if (parent)
  {
    if (parent->name_entry.rbe_left == (&elm[elm_idx]))
    {
      parent->name_entry.rbe_left = &child[child_idx];
    }
    else
      parent->name_entry.rbe_right = &child[child_idx];
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
    paste_name_tree_RB_REMOVE_COLOR(head, parent, child);
  }

  return old;
}


----------------------------
static struct paste_name_tree
{
  struct paste_buffer *rbh_root;
} paste_by_name
----------------------------
struct paste_buffer *paste_get_name(const char *name)
{
  struct paste_buffer pbfind;
  if ((name == 0) || ((*name) == '\0'))
  {
    return 0;
  }
  pbfind.name = (char *) name;
  return paste_name_tree_RB_FIND(&paste_by_name, &pbfind);
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
static struct paste_buffer *paste_name_tree_RB_INSERT(struct paste_name_tree *head, struct paste_buffer *elm)
{
  struct paste_buffer *tmp;
  unsigned int tmp_idx = 0;
  struct paste_buffer *parent = 0;
  unsigned int parent_idx = 0;
  int comp = 0;
  tmp_idx = head->rbh_root;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    comp = paste_cmp_names(elm, parent);
    if (comp < 0)
    {
      tmp_idx = tmp_idx->name_entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->name_entry.rbe_right;
    }
    else
      return tmp;
  }

  do
  {
    elm->name_entry.rbe_parent = &parent[parent_idx];
    elm->name_entry.rbe_left = (elm->name_entry.rbe_right = 0);
    elm->name_entry.rbe_color = 1;
  }
  while (0);
  if ((&parent[parent_idx]) != 0)
  {
    if (comp < 0)
    {
      parent->name_entry.rbe_left = elm;
    }
    else
      parent->name_entry.rbe_right = elm;
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = elm;
  paste_name_tree_RB_INSERT_COLOR(head, elm);
  return 0;
}


----------------------------
static u_int paste_num_automatic
----------------------------
***/


