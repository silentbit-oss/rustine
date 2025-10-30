int session_has(struct session *s, struct window *w)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  for (wl_idx = (&w->winlinks)->tqh_first; (&wl[wl_idx]) != 0; wl_idx = wl_idx->wentry.tqe_next)
  {
    if (wl->session == s)
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


struct session *sessions_RB_NEXT(struct session *elm)
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


struct session *sessions_RB_MINMAX(struct sessions *head, int val)
{
  struct session *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct session *parent = 0;
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
struct sessions
{
  struct session *rbh_root;
}
----------------------------
None
----------------------------
***/


void session_add_ref(struct session *s, const char *from)
{
  s->references += 1;
  log_debug("%s: %s %s, now %d", __func__, s->name, from, s->references);
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


/*** DEPENDENCIES:
struct sessions
{
  struct session *rbh_root;
}
----------------------------
struct session *sessions_RB_NEXT(struct session *elm)
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
struct session *sessions_RB_MINMAX(struct sessions *head, int val)
{
  struct session *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct session *parent = 0;
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


static void session_free(int fd, short events, void *arg)
{
  struct session *s = arg;
  log_debug("session %s freed (%d references)", s->name, s->references);
  if (s->references == 0)
  {
    environ_free(s->environ);
    options_free(s->options);
    hooks_free(s->hooks);
    free(s->name);
    free(s);
  }
}


/*** DEPENDENCIES:
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


----------------------------
void hooks_free(struct hooks *hooks)
{
  struct hook *hook;
  unsigned int hook_idx = 0;
  struct hook *hook1;
  unsigned int hook1_idx = 0;
  for (hook_idx = hooks_tree_RB_MINMAX(&hooks->tree, -1); ((&hook[hook_idx]) != 0) && ((hook1_idx = hooks_tree_RB_NEXT(hook), 1)); hook_idx = &hook1[hook1_idx])
  {
    hooks_free1(hooks, hook);
  }

  free(hooks);
}


----------------------------
void environ_free(struct environ *env)
{
  struct environ_entry *envent;
  unsigned int envent_idx = 0;
  struct environ_entry *envent1;
  unsigned int envent1_idx = 0;
  for (envent_idx = environ_RB_MINMAX(env, -1); ((&envent[envent_idx]) != 0) && ((envent1_idx = environ_RB_NEXT(envent), 1)); envent_idx = &envent1[envent1_idx])
  {
    environ_RB_REMOVE(env, envent);
    free(envent->name);
    free(envent->value);
    free(envent);
  }

  free(env);
}


----------------------------
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
None
----------------------------
***/


void session_remove_ref(struct session *s, const char *from)
{
  s->references -= 1;
  log_debug("%s: %s %s, now %d", __func__, s->name, from, s->references);
  if (s->references == 0)
  {
    event_once(-1, EV_TIMEOUT, session_free, s, 0);
  }
}


/*** DEPENDENCIES:
static void session_free(int fd, short events, void *arg)
{
  struct session *s = arg;
  log_debug("session %s freed (%d references)", s->name, s->references);
  if (s->references == 0)
  {
    environ_free(s->environ);
    options_free(s->options);
    hooks_free(s->hooks);
    free(s->name);
    free(s);
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
None
----------------------------
***/


struct session_group *session_groups_RB_MINMAX(struct session_groups *head, int val)
{
  struct session_group *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct session_group *parent = 0;
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
struct session_groups
{
  struct session_group *rbh_root;
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


struct session_group *session_groups_RB_NEXT(struct session_group *elm)
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


/*** DEPENDENCIES:
struct session_group *session_groups_RB_MINMAX(struct session_groups *head, int val)
{
  struct session_group *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct session_group *parent = 0;
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
struct sessions
{
  struct session *rbh_root;
}
----------------------------
struct session_groups
{
  struct session_group *rbh_root;
}
----------------------------
struct session_group *session_groups_RB_NEXT(struct session_group *elm)
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


/*** DEPENDENCIES:
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
None
----------------------------
***/


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
None
----------------------------
***/


int session_check_name(const char *name)
{
  return ((*name) != '\0') && (name[strcspn(name, ":.")] == '\0');
}


/*** DEPENDENCIES:
***/


int session_cmp(struct session *s1, struct session *s2)
{
  return strcmp(s1->name, s2->name);
}


/*** DEPENDENCIES:
None
----------------------------
***/


struct session *sessions_RB_PREV(struct session *elm)
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


int session_group_cmp(struct session_group *s1, struct session_group *s2)
{
  return strcmp(s1->name, s2->name);
}


/*** DEPENDENCIES:
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


struct session_group *session_groups_RB_PREV(struct session_group *elm)
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


static struct winlink *session_next_alert(struct winlink *wl)
{
  unsigned int wl_idx = 0;
  while ((&wl[wl_idx]) != 0)
  {
    if (wl->flags & ((0x1 | 0x2) | 0x4))
    {
      break;
    }
    wl_idx = winlink_next(wl_idx);
  }

  return wl;
}


/*** DEPENDENCIES:
struct winlink *winlink_next(struct winlink *wl)
{
  return winlinks_RB_NEXT(wl);
}


----------------------------
None
----------------------------
***/


static struct winlink *session_previous_alert(struct winlink *wl)
{
  unsigned int wl_idx = 0;
  while ((&wl[wl_idx]) != 0)
  {
    if (wl->flags & ((0x1 | 0x2) | 0x4))
    {
      break;
    }
    wl_idx = winlink_previous(wl_idx);
  }

  return wl;
}


/*** DEPENDENCIES:
struct winlink *winlink_previous(struct winlink *wl)
{
  return winlinks_RB_PREV(wl);
}


----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'child_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'color_ref is a mutable refrence to int']
void helper_sessions_RB_REMOVE_1(unsigned int * const elm_idx_ref, unsigned int * const child_idx_ref, unsigned int * const parent_idx_ref, int * const color_ref, struct sessions * const head, struct session * const elm, struct session * const child, struct session * const parent, struct session * const old)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int child_idx = *child_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  int color = *color_ref;
  struct session *left;
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
struct sessions
{
  struct session *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_sessions_RB_INSERT_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const gparent, struct session * const tmp, unsigned int gparent_idx)
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
struct sessions
{
  struct session *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_sessions_RB_INSERT_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const elm, struct session * const parent, struct session * const tmp)
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
struct sessions
{
  struct session *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_sessions_RB_INSERT_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const gparent, struct session * const tmp, unsigned int gparent_idx)
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
struct sessions
{
  struct session *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_sessions_RB_INSERT_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const elm, struct session * const parent, struct session * const tmp)
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
struct sessions
{
  struct session *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_sessions_RB_REMOVE_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const parent, struct session * const tmp, unsigned int parent_idx)
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
struct sessions
{
  struct session *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_sessions_RB_REMOVE_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const parent, struct session * const tmp, unsigned int parent_idx)
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
struct sessions
{
  struct session *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_sessions_RB_REMOVE_COLOR_1_1_2_1(unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const parent, struct session * const tmp, unsigned int parent_idx)
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
struct sessions
{
  struct session *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_sessions_RB_REMOVE_COLOR_1_1_2_2(unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const parent, struct session * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct session *oleft;
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
struct sessions
{
  struct session *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_sessions_RB_REMOVE_COLOR_1_2_2_1(unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const parent, struct session * const tmp, unsigned int parent_idx)
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
struct sessions
{
  struct session *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_sessions_RB_REMOVE_COLOR_1_2_2_2(unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const parent, struct session * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct session *oright;
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
struct sessions
{
  struct session *rbh_root;
}
----------------------------
None
----------------------------
***/


struct session *session_find_by_id(u_int id)
{
  struct session *s;
  unsigned int s_idx = 0;
  for (s_idx = sessions_RB_MINMAX(&sessions, -1); (&s[s_idx]) != 0; s_idx = sessions_RB_NEXT(s_idx))
  {
    if (s->id == id)
    {
      return s;
    }
  }

  return 0;
}


/*** DEPENDENCIES:
struct sessions
{
  struct session *rbh_root;
}
----------------------------
struct session *sessions_RB_NEXT(struct session *elm)
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
struct session *sessions_RB_MINMAX(struct sessions *head, int val)
{
  struct session *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct session *parent = 0;
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


struct session *sessions_RB_FIND(struct sessions *head, struct session *elm)
{
  struct session *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  int comp;
  while (tmp)
  {
    comp = session_cmp(elm, tmp);
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
struct sessions
{
  struct session *rbh_root;
}
----------------------------
int session_cmp(struct session *s1, struct session *s2)
{
  return strcmp(s1->name, s2->name);
}


----------------------------
None
----------------------------
***/


struct session *session_find(const char *name)
{
  struct session s;
  s.name = (char *) name;
  return sessions_RB_FIND(&sessions, &s);
}


/*** DEPENDENCIES:
struct sessions
{
  struct session *rbh_root;
}
----------------------------
struct session *sessions_RB_FIND(struct sessions *head, struct session *elm)
{
  struct session *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  int comp;
  while (tmp)
  {
    comp = session_cmp(elm, tmp);
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


struct session *session_find_by_id_str(const char *s)
{
  const char *errstr;
  u_int id;
  if ((*s) != '$')
  {
    return 0;
  }
  id = strtonum(s + 1, 0, 4294967295U, &errstr);
  if (errstr != 0)
  {
    return 0;
  }
  return session_find_by_id(id);
}


/*** DEPENDENCIES:
struct session *session_find_by_id(u_int id)
{
  struct session *s;
  unsigned int s_idx = 0;
  for (s_idx = sessions_RB_MINMAX(&sessions, -1); (&s[s_idx]) != 0; s_idx = sessions_RB_NEXT(s_idx))
  {
    if (s->id == id)
    {
      return s;
    }
  }

  return 0;
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


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'child_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'color_ref is a mutable refrence to int']
void helper_session_groups_RB_REMOVE_1(unsigned int * const elm_idx_ref, unsigned int * const child_idx_ref, unsigned int * const parent_idx_ref, int * const color_ref, struct session_groups * const head, struct session_group * const elm, struct session_group * const child, struct session_group * const parent, struct session_group * const old)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int child_idx = *child_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  int color = *color_ref;
  struct session_group *left;
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
struct session_groups
{
  struct session_group *rbh_root;
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


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_session_groups_RB_REMOVE_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const parent, struct session_group * const tmp, unsigned int parent_idx)
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
struct session_groups
{
  struct session_group *rbh_root;
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


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_session_groups_RB_REMOVE_COLOR_1_1_2_2(unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const parent, struct session_group * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct session_group *oleft;
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
struct session_groups
{
  struct session_group *rbh_root;
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


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_session_groups_RB_REMOVE_COLOR_1_1_2_1(unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const parent, struct session_group * const tmp, unsigned int parent_idx)
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
struct session_groups
{
  struct session_group *rbh_root;
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


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_session_groups_RB_REMOVE_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const parent, struct session_group * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_session_groups_RB_REMOVE_COLOR_1_1_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_right)
  {
    tmp->entry.rbe_right->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_session_groups_RB_REMOVE_COLOR_1_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct session_groups
{
  struct session_group *rbh_root;
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
void helper_helper_helper_helper_session_groups_RB_REMOVE_COLOR_1_1_2_2(unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const parent, struct session_group * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct session_group *oleft;
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
void helper_helper_helper_helper_session_groups_RB_REMOVE_COLOR_1_1_2_1(unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const parent, struct session_group * const tmp, unsigned int parent_idx)
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
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_session_groups_RB_REMOVE_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const parent, struct session_group * const elm, struct session_group * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_right;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_session_groups_RB_REMOVE_COLOR_1_1_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_session_groups_RB_REMOVE_COLOR_1_1_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct session_groups
{
  struct session_group *rbh_root;
}
----------------------------
void helper_helper_helper_session_groups_RB_REMOVE_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const parent, struct session_group * const tmp, unsigned int parent_idx)
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
void helper_helper_helper_session_groups_RB_REMOVE_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const parent, struct session_group * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_session_groups_RB_REMOVE_COLOR_1_1_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_right)
  {
    tmp->entry.rbe_right->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_session_groups_RB_REMOVE_COLOR_1_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
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


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_session_groups_RB_REMOVE_COLOR_1_2_2_1(unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const parent, struct session_group * const tmp, unsigned int parent_idx)
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
struct session_groups
{
  struct session_group *rbh_root;
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


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_helper_session_groups_RB_REMOVE_COLOR_1_2_2_2(unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const parent, struct session_group * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct session_group *oright;
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
struct session_groups
{
  struct session_group *rbh_root;
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


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_session_groups_RB_REMOVE_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const parent, struct session_group * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_session_groups_RB_REMOVE_COLOR_1_2_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_left)
  {
    tmp->entry.rbe_left->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_session_groups_RB_REMOVE_COLOR_1_2_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct session_groups
{
  struct session_group *rbh_root;
}
----------------------------
void helper_helper_helper_helper_session_groups_RB_REMOVE_COLOR_1_2_2_1(unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const parent, struct session_group * const tmp, unsigned int parent_idx)
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
void helper_helper_helper_helper_session_groups_RB_REMOVE_COLOR_1_2_2_2(unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const parent, struct session_group * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct session_group *oright;
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
void helper_helper_helper_session_groups_RB_REMOVE_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const parent, struct session_group * const tmp, unsigned int parent_idx)
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
struct session_groups
{
  struct session_group *rbh_root;
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


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_session_groups_RB_REMOVE_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const parent, struct session_group * const elm, struct session_group * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_left;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_session_groups_RB_REMOVE_COLOR_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_session_groups_RB_REMOVE_COLOR_1_2_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct session_groups
{
  struct session_group *rbh_root;
}
----------------------------
void helper_helper_helper_session_groups_RB_REMOVE_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const parent, struct session_group * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_session_groups_RB_REMOVE_COLOR_1_2_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_left)
  {
    tmp->entry.rbe_left->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_session_groups_RB_REMOVE_COLOR_1_2_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
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
void helper_helper_helper_session_groups_RB_REMOVE_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const parent, struct session_group * const tmp, unsigned int parent_idx)
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


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_session_groups_RB_REMOVE_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const parent, struct session_group * const elm, struct session_group * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if (parent->entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_session_groups_RB_REMOVE_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  else
  {
    helper_helper_session_groups_RB_REMOVE_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct session_groups
{
  struct session_group *rbh_root;
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
void helper_helper_session_groups_RB_REMOVE_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const parent, struct session_group * const elm, struct session_group * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_right;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_session_groups_RB_REMOVE_COLOR_1_1_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_session_groups_RB_REMOVE_COLOR_1_1_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_session_groups_RB_REMOVE_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const parent, struct session_group * const elm, struct session_group * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_left;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_session_groups_RB_REMOVE_COLOR_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_session_groups_RB_REMOVE_COLOR_1_2_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


void session_groups_RB_REMOVE_COLOR(struct session_groups *head, struct session_group *parent, struct session_group *elm)
{
  unsigned int elm_idx = 0;
  unsigned int parent_idx = 0;
  struct session_group *tmp;
  unsigned int tmp_idx = 0;
  while ((((&elm[elm_idx]) == 0) || (elm->entry.rbe_color == 0)) && ((&elm[elm_idx]) != head->rbh_root))
  {
    helper_session_groups_RB_REMOVE_COLOR_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }

  if (elm)
  {
    elm->entry.rbe_color = 0;
  }
}


/*** DEPENDENCIES:
struct session_groups
{
  struct session_group *rbh_root;
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
void helper_session_groups_RB_REMOVE_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const parent, struct session_group * const elm, struct session_group * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if (parent->entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_session_groups_RB_REMOVE_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  else
  {
    helper_helper_session_groups_RB_REMOVE_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


struct session_group *session_groups_RB_REMOVE(struct session_groups *head, struct session_group *elm)
{
  unsigned int elm_idx = 0;
  struct session_group *child;
  unsigned int child_idx = 0;
  struct session_group *parent;
  unsigned int parent_idx = 0;
  struct session_group *old = elm;
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
    helper_session_groups_RB_REMOVE_1(&elm_idx, &child_idx, &parent_idx, &color, head, elm, child, parent, old);
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
    session_groups_RB_REMOVE_COLOR(head, parent, child);
  }

  return old;
}


/*** DEPENDENCIES:
struct session_groups
{
  struct session_group *rbh_root;
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
void helper_session_groups_RB_REMOVE_1(unsigned int * const elm_idx_ref, unsigned int * const child_idx_ref, unsigned int * const parent_idx_ref, int * const color_ref, struct session_groups * const head, struct session_group * const elm, struct session_group * const child, struct session_group * const parent, struct session_group * const old)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int child_idx = *child_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  int color = *color_ref;
  struct session_group *left;
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
void session_groups_RB_REMOVE_COLOR(struct session_groups *head, struct session_group *parent, struct session_group *elm)
{
  unsigned int elm_idx = 0;
  unsigned int parent_idx = 0;
  struct session_group *tmp;
  unsigned int tmp_idx = 0;
  while ((((&elm[elm_idx]) == 0) || (elm->entry.rbe_color == 0)) && ((&elm[elm_idx]) != head->rbh_root))
  {
    helper_session_groups_RB_REMOVE_COLOR_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }

  if (elm)
  {
    elm->entry.rbe_color = 0;
  }
}


----------------------------
None
----------------------------
***/


static void session_group_remove(struct session *s)
{
  struct session_group *sg;
  unsigned int sg_idx = 0;
  if ((sg_idx = session_group_contains(s)) == 0)
  {
    return;
  }
  do
  {
    if (s->gentry.tqe_next != 0)
    {
      s->gentry.tqe_next->gentry.tqe_prev = s->gentry.tqe_prev;
    }
    else
      (&sg->sessions)->tqh_last = s->gentry.tqe_prev;
    *s->gentry.tqe_prev = s->gentry.tqe_next;
    ;
    ;
  }
  while (0);
  if ((&sg->sessions)->tqh_first == 0)
  {
    session_groups_RB_REMOVE(&session_groups, sg);
    free(sg);
  }
}


/*** DEPENDENCIES:
struct session_group *session_groups_RB_REMOVE(struct session_groups *head, struct session_group *elm)
{
  unsigned int elm_idx = 0;
  struct session_group *child;
  unsigned int child_idx = 0;
  struct session_group *parent;
  unsigned int parent_idx = 0;
  struct session_group *old = elm;
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
    helper_session_groups_RB_REMOVE_1(&elm_idx, &child_idx, &parent_idx, &color, head, elm, child, parent, old);
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
    session_groups_RB_REMOVE_COLOR(head, parent, child);
  }

  return old;
}


----------------------------
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
struct session_groups
{
  struct session_group *rbh_root;
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
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_sessions_RB_REMOVE_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const parent, struct session * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_sessions_RB_REMOVE_COLOR_1_1_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_right)
  {
    tmp->entry.rbe_right->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_sessions_RB_REMOVE_COLOR_1_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct sessions
{
  struct session *rbh_root;
}
----------------------------
void helper_helper_helper_helper_sessions_RB_REMOVE_COLOR_1_1_2_2(unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const parent, struct session * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct session *oleft;
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
void helper_helper_helper_helper_sessions_RB_REMOVE_COLOR_1_1_2_1(unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const parent, struct session * const tmp, unsigned int parent_idx)
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
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_sessions_RB_REMOVE_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const parent, struct session * const elm, struct session * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_right;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_sessions_RB_REMOVE_COLOR_1_1_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_sessions_RB_REMOVE_COLOR_1_1_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
void helper_helper_helper_sessions_RB_REMOVE_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const parent, struct session * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_sessions_RB_REMOVE_COLOR_1_1_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_right)
  {
    tmp->entry.rbe_right->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_sessions_RB_REMOVE_COLOR_1_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
struct sessions
{
  struct session *rbh_root;
}
----------------------------
void helper_helper_helper_sessions_RB_REMOVE_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const parent, struct session * const tmp, unsigned int parent_idx)
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


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_sessions_RB_REMOVE_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const parent, struct session * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_sessions_RB_REMOVE_COLOR_1_2_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_left)
  {
    tmp->entry.rbe_left->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_sessions_RB_REMOVE_COLOR_1_2_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
void helper_helper_helper_helper_sessions_RB_REMOVE_COLOR_1_2_2_2(unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const parent, struct session * const tmp)
{
  unsigned int tmp_idx = *tmp_idx_ref;
  struct session *oright;
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
void helper_helper_helper_helper_sessions_RB_REMOVE_COLOR_1_2_2_1(unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const parent, struct session * const tmp, unsigned int parent_idx)
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
struct sessions
{
  struct session *rbh_root;
}
----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_sessions_RB_REMOVE_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const parent, struct session * const elm, struct session * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_left;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_sessions_RB_REMOVE_COLOR_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_sessions_RB_REMOVE_COLOR_1_2_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct sessions
{
  struct session *rbh_root;
}
----------------------------
void helper_helper_helper_sessions_RB_REMOVE_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const parent, struct session * const tmp, unsigned int parent_idx)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if ((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0))
  {
    helper_helper_helper_helper_sessions_RB_REMOVE_COLOR_1_2_2_2(&tmp_idx, head, parent, tmp);
  }
  tmp->entry.rbe_color = parent->entry.rbe_color;
  parent->entry.rbe_color = 0;
  if (tmp->entry.rbe_left)
  {
    tmp->entry.rbe_left->entry.rbe_color = 0;
  }
  do
  {
    helper_helper_helper_helper_sessions_RB_REMOVE_COLOR_1_2_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  while (0);
  elm_idx = head->rbh_root;
  break;
  *elm_idx_ref = elm_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_helper_sessions_RB_REMOVE_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const parent, struct session * const tmp, unsigned int parent_idx)
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


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_sessions_RB_REMOVE_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const parent, struct session * const elm, struct session * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if (parent->entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_sessions_RB_REMOVE_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  else
  {
    helper_helper_sessions_RB_REMOVE_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct sessions
{
  struct session *rbh_root;
}
----------------------------
void helper_helper_sessions_RB_REMOVE_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const parent, struct session * const elm, struct session * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_right;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_sessions_RB_REMOVE_COLOR_1_1_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_sessions_RB_REMOVE_COLOR_1_1_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_sessions_RB_REMOVE_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const parent, struct session * const elm, struct session * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  tmp_idx = parent->entry.rbe_left;
  if (tmp->entry.rbe_color == 1)
  {
    helper_helper_helper_sessions_RB_REMOVE_COLOR_1_2_1(&tmp_idx, head, parent, tmp, parent_idx);
  }
  if (((tmp->entry.rbe_left == 0) || (tmp->entry.rbe_left->entry.rbe_color == 0)) && ((tmp->entry.rbe_right == 0) || (tmp->entry.rbe_right->entry.rbe_color == 0)))
  {
    tmp->entry.rbe_color = 1;
    elm_idx = &parent[parent_idx];
    parent_idx = elm->entry.rbe_parent;
  }
  else
  {
    helper_helper_helper_sessions_RB_REMOVE_COLOR_1_2_2(&elm_idx, &tmp_idx, head, parent, tmp, parent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


void sessions_RB_REMOVE_COLOR(struct sessions *head, struct session *parent, struct session *elm)
{
  unsigned int elm_idx = 0;
  unsigned int parent_idx = 0;
  struct session *tmp;
  unsigned int tmp_idx = 0;
  while ((((&elm[elm_idx]) == 0) || (elm->entry.rbe_color == 0)) && ((&elm[elm_idx]) != head->rbh_root))
  {
    helper_sessions_RB_REMOVE_COLOR_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }

  if (elm)
  {
    elm->entry.rbe_color = 0;
  }
}


/*** DEPENDENCIES:
struct sessions
{
  struct session *rbh_root;
}
----------------------------
void helper_sessions_RB_REMOVE_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const parent, struct session * const elm, struct session * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  if (parent->entry.rbe_left == (&elm[elm_idx]))
  {
    helper_helper_sessions_RB_REMOVE_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  else
  {
    helper_helper_sessions_RB_REMOVE_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
None
----------------------------
***/


struct session *sessions_RB_REMOVE(struct sessions *head, struct session *elm)
{
  unsigned int elm_idx = 0;
  struct session *child;
  unsigned int child_idx = 0;
  struct session *parent;
  unsigned int parent_idx = 0;
  struct session *old = elm;
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
    helper_sessions_RB_REMOVE_1(&elm_idx, &child_idx, &parent_idx, &color, head, elm, child, parent, old);
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
    sessions_RB_REMOVE_COLOR(head, parent, child);
  }

  return old;
}


/*** DEPENDENCIES:
struct sessions
{
  struct session *rbh_root;
}
----------------------------
void helper_sessions_RB_REMOVE_1(unsigned int * const elm_idx_ref, unsigned int * const child_idx_ref, unsigned int * const parent_idx_ref, int * const color_ref, struct sessions * const head, struct session * const elm, struct session * const child, struct session * const parent, struct session * const old)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int child_idx = *child_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  int color = *color_ref;
  struct session *left;
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
void sessions_RB_REMOVE_COLOR(struct sessions *head, struct session *parent, struct session *elm)
{
  unsigned int elm_idx = 0;
  unsigned int parent_idx = 0;
  struct session *tmp;
  unsigned int tmp_idx = 0;
  while ((((&elm[elm_idx]) == 0) || (elm->entry.rbe_color == 0)) && ((&elm[elm_idx]) != head->rbh_root))
  {
    helper_sessions_RB_REMOVE_COLOR_1(&elm_idx, &parent_idx, &tmp_idx, head, parent, elm, tmp);
  }

  if (elm)
  {
    elm->entry.rbe_color = 0;
  }
}


----------------------------
None
----------------------------
***/


void session_destroy(struct session *s, const char *from)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  log_debug("session %s destroyed (%s)", s->name, from);
  s->curw = 0;
  sessions_RB_REMOVE(&sessions, s);
  notify_session("session-closed", s);
  free(s->tio);
  if (event_initialized(&s->lock_timer))
  {
    event_del(&s->lock_timer);
  }
  session_group_remove(s);
  while (!((&s->lastw)->tqh_first == 0))
  {
    winlink_stack_remove(&s->lastw, (&s->lastw)->tqh_first);
  }

  while (!((&s->windows)->rbh_root == 0))
  {
    wl_idx = (&s->windows)->rbh_root;
    notify_session_window("window-unlinked", s, wl->window);
    winlink_remove(&s->windows, wl);
  }

  free((void *) s->cwd);
  session_remove_ref(s, __func__);
}


/*** DEPENDENCIES:
void notify_session_window(const char *name, struct session *s, struct window *w)
{
  struct cmd_find_state fs;
  cmd_find_from_session_window(&fs, s, w, 0);
  notify_add(name, &fs, 0, s, w, 0);
}


----------------------------
static void session_group_remove(struct session *s)
{
  struct session_group *sg;
  unsigned int sg_idx = 0;
  if ((sg_idx = session_group_contains(s)) == 0)
  {
    return;
  }
  do
  {
    if (s->gentry.tqe_next != 0)
    {
      s->gentry.tqe_next->gentry.tqe_prev = s->gentry.tqe_prev;
    }
    else
      (&sg->sessions)->tqh_last = s->gentry.tqe_prev;
    *s->gentry.tqe_prev = s->gentry.tqe_next;
    ;
    ;
  }
  while (0);
  if ((&sg->sessions)->tqh_first == 0)
  {
    session_groups_RB_REMOVE(&session_groups, sg);
    free(sg);
  }
}


----------------------------
struct windows
{
  struct window *rbh_root;
}
----------------------------
struct session *sessions_RB_REMOVE(struct sessions *head, struct session *elm)
{
  unsigned int elm_idx = 0;
  struct session *child;
  unsigned int child_idx = 0;
  struct session *parent;
  unsigned int parent_idx = 0;
  struct session *old = elm;
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
    helper_sessions_RB_REMOVE_1(&elm_idx, &child_idx, &parent_idx, &color, head, elm, child, parent, old);
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
    sessions_RB_REMOVE_COLOR(head, parent, child);
  }

  return old;
}


----------------------------
void notify_session(const char *name, struct session *s)
{
  struct cmd_find_state fs;
  if (session_alive(s))
  {
    cmd_find_from_session(&fs, s, 0);
  }
  else
    cmd_find_from_nothing(&fs, 0);
  notify_add(name, &fs, 0, s, 0, 0);
}


----------------------------
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
void session_remove_ref(struct session *s, const char *from)
{
  s->references -= 1;
  log_debug("%s: %s %s, now %d", __func__, s->name, from, s->references);
  if (s->references == 0)
  {
    event_once(-1, EV_TIMEOUT, session_free, s, 0);
  }
}


----------------------------
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


----------------------------
struct sessions
{
  struct session *rbh_root;
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


static void session_lock_timer(int fd, short events, void *arg)
{
  struct session *s = arg;
  if (s->flags & 0x1)
  {
    return;
  }
  log_debug("session %s locked, activity time %lld", s->name, (long long) s->activity_time.tv_sec);
  server_lock_session(s);
  recalculate_sizes();
}


/*** DEPENDENCIES:
void server_lock_session(struct session *s)
{
  struct client *c;
  unsigned int c_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (c->session == s)
    {
      server_lock_client(c);
    }
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
void recalculate_sizes(void)
{
  struct session *s;
  unsigned int s_idx = 0;
  struct client *c;
  unsigned int c_idx = 0;
  struct window *w;
  unsigned int w_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int ssx;
  u_int ssy;
  u_int has;
  u_int limit;
  u_int lines;
  int flag;
  int is_zoomed;
  int forced;
  for (s_idx = sessions_RB_MINMAX(&sessions, -1); (&s[s_idx]) != 0; s_idx = sessions_RB_NEXT(s_idx))
  {
    helper_recalculate_sizes_1(&c_idx, &ssx, &ssy, &lines, s, s_idx, c);
  }

  for (w_idx = windows_RB_MINMAX(&windows, -1); (&w[w_idx]) != 0; w_idx = windows_RB_NEXT(w_idx))
  {
    helper_recalculate_sizes_2(&s_idx, &wp_idx, &ssx, &ssy, &has, &limit, &flag, &is_zoomed, &forced, s, w, w_idx, wp);
  }

}


----------------------------
None
----------------------------
***/


void session_update_activity(struct session *s, struct timeval *from)
{
  struct timeval *last = &s->last_activity_time;
  struct timeval tv;
  memcpy(last, &s->activity_time, sizeof(*last));
  if (from == 0)
  {
    gettimeofday(&s->activity_time, 0);
  }
  else
    memcpy(&s->activity_time, from, sizeof(s->activity_time));
  log_debug("session %s activity %lld.%06d (last %lld.%06d)", s->name, (long long) s->activity_time.tv_sec, (int) s->activity_time.tv_usec, (long long) last->tv_sec, (int) last->tv_usec);
  if (evtimer_initialized(&s->lock_timer))
  {
    evtimer_del(&s->lock_timer);
  }
  else
    evtimer_set(&s->lock_timer, session_lock_timer, s);
  if ((~s->flags) & 0x1)
  {
    timerclear(&tv);
    tv.tv_sec = options_get_number(s->options, "lock-after-time");
    if (tv.tv_sec != 0)
    {
      evtimer_add(&s->lock_timer, &tv);
    }
  }
}


/*** DEPENDENCIES:
static void session_lock_timer(int fd, short events, void *arg)
{
  struct session *s = arg;
  if (s->flags & 0x1)
  {
    return;
  }
  log_debug("session %s locked, activity time %lld", s->name, (long long) s->activity_time.tv_sec);
  server_lock_session(s);
  recalculate_sizes();
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


void session_renumber_windows(struct session *s)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct winlink *wl1;
  unsigned int wl1_idx = 0;
  struct winlink *wl_new;
  unsigned int wl_new_idx = 0;
  struct winlinks old_wins;
  struct winlink_stack old_lastw;
  int new_idx;
  int new_curw_idx;
  memcpy(&old_wins, &s->windows, sizeof(old_wins));
  do
  {
    (&s->windows)->rbh_root = 0;
  }
  while (0);
  new_idx = options_get_number(s->options, "base-index");
  new_curw_idx = 0;
  for (wl_idx = winlinks_RB_MINMAX(&old_wins, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    wl_new_idx = winlink_add(&s->windows, new_idx);
    wl_new->session = s;
    winlink_set_window(wl_new, wl->window);
    wl_new->flags |= wl->flags & ((0x1 | 0x2) | 0x4);
    if ((&wl[wl_idx]) == s->curw)
    {
      new_curw_idx = wl_new->idx;
    }
    new_idx += 1;
  }

  memcpy(&old_lastw, &s->lastw, sizeof(old_lastw));
  do
  {
    (&s->lastw)->tqh_first = 0;
    (&s->lastw)->tqh_last = &(&s->lastw)->tqh_first;
  }
  while (0);
  for (wl_idx = (&old_lastw)->tqh_first; (&wl[wl_idx]) != 0; wl_idx = wl_idx->sentry.tqe_next)
  {
    wl_new_idx = winlink_find_by_window(&s->windows, wl->window);
    if ((&wl_new[wl_new_idx]) != 0)
    {
      do
      {
        wl_new->sentry.tqe_next = 0;
        wl_new->sentry.tqe_prev = (&s->lastw)->tqh_last;
        *(&s->lastw)->tqh_last = &wl_new[wl_new_idx];
        (&s->lastw)->tqh_last = &wl_new->sentry.tqe_next;
      }
      while (0);
    }
  }

  s->curw = winlink_find_by_index(&s->windows, new_curw_idx);
  for (wl_idx = winlinks_RB_MINMAX(&old_wins, -1); ((&wl[wl_idx]) != 0) && ((wl1_idx = winlinks_RB_NEXT(wl), 1)); wl_idx = &wl1[wl1_idx])
  {
    winlink_remove(&old_wins, wl);
  }

}


/*** DEPENDENCIES:
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


----------------------------
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


----------------------------
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


----------------------------
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


int session_set_current(struct session *s, struct winlink *wl)
{
  if (wl == 0)
  {
    return -1;
  }
  if (wl == s->curw)
  {
    return 1;
  }
  winlink_stack_remove(&s->lastw, wl);
  winlink_stack_push(&s->lastw, s->curw);
  s->curw = wl;
  winlink_clear_flags(wl);
  window_update_activity(wl->window);
  notify_session("session-window-changed", s);
  return 0;
}


/*** DEPENDENCIES:
void notify_session(const char *name, struct session *s)
{
  struct cmd_find_state fs;
  if (session_alive(s))
  {
    cmd_find_from_session(&fs, s, 0);
  }
  else
    cmd_find_from_nothing(&fs, 0);
  notify_add(name, &fs, 0, s, 0, 0);
}


----------------------------
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


----------------------------
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


int session_previous(struct session *s, int alert)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  if (s->curw == 0)
  {
    return -1;
  }
  wl_idx = winlink_previous(s->curw);
  if (alert)
  {
    wl_idx = session_previous_alert(wl_idx);
  }
  if ((&wl[wl_idx]) == 0)
  {
    wl_idx = winlinks_RB_MINMAX(&s->windows, 1);
    if (alert && ((wl_idx = session_previous_alert(wl_idx)) == 0))
    {
      return -1;
    }
  }
  return session_set_current(s, wl);
}


/*** DEPENDENCIES:
int session_set_current(struct session *s, struct winlink *wl)
{
  if (wl == 0)
  {
    return -1;
  }
  if (wl == s->curw)
  {
    return 1;
  }
  winlink_stack_remove(&s->lastw, wl);
  winlink_stack_push(&s->lastw, s->curw);
  s->curw = wl;
  winlink_clear_flags(wl);
  window_update_activity(wl->window);
  notify_session("session-window-changed", s);
  return 0;
}


----------------------------
struct windows
{
  struct window *rbh_root;
}
----------------------------
static struct winlink *session_previous_alert(struct winlink *wl)
{
  unsigned int wl_idx = 0;
  while ((&wl[wl_idx]) != 0)
  {
    if (wl->flags & ((0x1 | 0x2) | 0x4))
    {
      break;
    }
    wl_idx = winlink_previous(wl_idx);
  }

  return wl;
}


----------------------------
struct winlink *winlink_previous(struct winlink *wl)
{
  return winlinks_RB_PREV(wl);
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


int session_last(struct session *s)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  wl_idx = (&s->lastw)->tqh_first;
  if ((&wl[wl_idx]) == 0)
  {
    return -1;
  }
  if ((&wl[wl_idx]) == s->curw)
  {
    return 1;
  }
  return session_set_current(s, wl);
}


/*** DEPENDENCIES:
int session_set_current(struct session *s, struct winlink *wl)
{
  if (wl == 0)
  {
    return -1;
  }
  if (wl == s->curw)
  {
    return 1;
  }
  winlink_stack_remove(&s->lastw, wl);
  winlink_stack_push(&s->lastw, s->curw);
  s->curw = wl;
  winlink_clear_flags(wl);
  window_update_activity(wl->window);
  notify_session("session-window-changed", s);
  return 0;
}


----------------------------
None
----------------------------
***/


int session_next(struct session *s, int alert)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  if (s->curw == 0)
  {
    return -1;
  }
  wl_idx = winlink_next(s->curw);
  if (alert)
  {
    wl_idx = session_next_alert(wl_idx);
  }
  if ((&wl[wl_idx]) == 0)
  {
    wl_idx = winlinks_RB_MINMAX(&s->windows, -1);
    if (alert && ((wl_idx = session_next_alert(wl_idx)) == 0))
    {
      return -1;
    }
  }
  return session_set_current(s, wl);
}


/*** DEPENDENCIES:
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
int session_set_current(struct session *s, struct winlink *wl)
{
  if (wl == 0)
  {
    return -1;
  }
  if (wl == s->curw)
  {
    return 1;
  }
  winlink_stack_remove(&s->lastw, wl);
  winlink_stack_push(&s->lastw, s->curw);
  s->curw = wl;
  winlink_clear_flags(wl);
  window_update_activity(wl->window);
  notify_session("session-window-changed", s);
  return 0;
}


----------------------------
struct windows
{
  struct window *rbh_root;
}
----------------------------
struct winlink *winlink_next(struct winlink *wl)
{
  return winlinks_RB_NEXT(wl);
}


----------------------------
static struct winlink *session_next_alert(struct winlink *wl)
{
  unsigned int wl_idx = 0;
  while ((&wl[wl_idx]) != 0)
  {
    if (wl->flags & ((0x1 | 0x2) | 0x4))
    {
      break;
    }
    wl_idx = winlink_next(wl_idx);
  }

  return wl;
}


----------------------------
None
----------------------------
***/


static void session_group_synchronize1(struct session *target, struct session *s)
{
  struct winlinks old_windows;
  struct winlinks *ww;
  unsigned int ww_idx = 0;
  struct winlink_stack old_lastw;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct winlink *wl2;
  unsigned int wl2_idx = 0;
  ww_idx = &target->windows;
  if (ww->rbh_root == 0)
  {
    return;
  }
  if ((((s->curw != 0) && (winlink_find_by_index(ww, s->curw->idx) == 0)) && (session_last(s) != 0)) && (session_previous(s, 0) != 0))
  {
    session_next(s, 0);
  }
  memcpy(&old_windows, &s->windows, sizeof(old_windows));
  do
  {
    (&s->windows)->rbh_root = 0;
  }
  while (0);
  for (wl_idx = winlinks_RB_MINMAX(ww, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    wl2_idx = winlink_add(&s->windows, wl->idx);
    wl2->session = s;
    winlink_set_window(wl2, wl->window);
    notify_session_window("window-linked", s, wl2->window);
    wl2->flags |= wl->flags & ((0x1 | 0x2) | 0x4);
  }

  if (s->curw != 0)
  {
    s->curw = winlink_find_by_index(&s->windows, s->curw->idx);
  }
  else
    s->curw = winlink_find_by_index(&s->windows, target->curw->idx);
  memcpy(&old_lastw, &s->lastw, sizeof(old_lastw));
  do
  {
    (&s->lastw)->tqh_first = 0;
    (&s->lastw)->tqh_last = &(&s->lastw)->tqh_first;
  }
  while (0);
  for (wl_idx = (&old_lastw)->tqh_first; (&wl[wl_idx]) != 0; wl_idx = wl_idx->sentry.tqe_next)
  {
    wl2_idx = winlink_find_by_index(&s->windows, wl->idx);
    if ((&wl2[wl2_idx]) != 0)
    {
      do
      {
        wl2->sentry.tqe_next = 0;
        wl2->sentry.tqe_prev = (&s->lastw)->tqh_last;
        *(&s->lastw)->tqh_last = &wl2[wl2_idx];
        (&s->lastw)->tqh_last = &wl2->sentry.tqe_next;
      }
      while (0);
    }
  }

  while (!((&old_windows)->rbh_root == 0))
  {
    wl_idx = (&old_windows)->rbh_root;
    wl2_idx = winlink_find_by_window_id(&s->windows, wl->window->id);
    if ((&wl2[wl2_idx]) == 0)
    {
      notify_session_window("window-unlinked", s, wl->window);
    }
    winlink_remove(&old_windows, wl);
  }

}


/*** DEPENDENCIES:
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


----------------------------
struct windows
{
  struct window *rbh_root;
}
----------------------------
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
int session_previous(struct session *s, int alert)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  if (s->curw == 0)
  {
    return -1;
  }
  wl_idx = winlink_previous(s->curw);
  if (alert)
  {
    wl_idx = session_previous_alert(wl_idx);
  }
  if ((&wl[wl_idx]) == 0)
  {
    wl_idx = winlinks_RB_MINMAX(&s->windows, 1);
    if (alert && ((wl_idx = session_previous_alert(wl_idx)) == 0))
    {
      return -1;
    }
  }
  return session_set_current(s, wl);
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


----------------------------
int session_last(struct session *s)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  wl_idx = (&s->lastw)->tqh_first;
  if ((&wl[wl_idx]) == 0)
  {
    return -1;
  }
  if ((&wl[wl_idx]) == s->curw)
  {
    return 1;
  }
  return session_set_current(s, wl);
}


----------------------------
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


----------------------------
void notify_session_window(const char *name, struct session *s, struct window *w)
{
  struct cmd_find_state fs;
  cmd_find_from_session_window(&fs, s, w, 0);
  notify_add(name, &fs, 0, s, w, 0);
}


----------------------------
int session_next(struct session *s, int alert)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  if (s->curw == 0)
  {
    return -1;
  }
  wl_idx = winlink_next(s->curw);
  if (alert)
  {
    wl_idx = session_next_alert(wl_idx);
  }
  if ((&wl[wl_idx]) == 0)
  {
    wl_idx = winlinks_RB_MINMAX(&s->windows, -1);
    if (alert && ((wl_idx = session_next_alert(wl_idx)) == 0))
    {
      return -1;
    }
  }
  return session_set_current(s, wl);
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


void session_group_synchronize_from(struct session *target)
{
  struct session_group *sg;
  unsigned int sg_idx = 0;
  struct session *s;
  unsigned int s_idx = 0;
  if ((sg_idx = session_group_contains(target)) == 0)
  {
    return;
  }
  for (s_idx = (&sg->sessions)->tqh_first; (&s[s_idx]) != 0; s_idx = s_idx->gentry.tqe_next)
  {
    if ((&s[s_idx]) != target)
    {
      session_group_synchronize1(target, s);
    }
  }

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
struct sessions
{
  struct session *rbh_root;
}
----------------------------
static void session_group_synchronize1(struct session *target, struct session *s)
{
  struct winlinks old_windows;
  struct winlinks *ww;
  unsigned int ww_idx = 0;
  struct winlink_stack old_lastw;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct winlink *wl2;
  unsigned int wl2_idx = 0;
  ww_idx = &target->windows;
  if (ww->rbh_root == 0)
  {
    return;
  }
  if ((((s->curw != 0) && (winlink_find_by_index(ww, s->curw->idx) == 0)) && (session_last(s) != 0)) && (session_previous(s, 0) != 0))
  {
    session_next(s, 0);
  }
  memcpy(&old_windows, &s->windows, sizeof(old_windows));
  do
  {
    (&s->windows)->rbh_root = 0;
  }
  while (0);
  for (wl_idx = winlinks_RB_MINMAX(ww, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    wl2_idx = winlink_add(&s->windows, wl->idx);
    wl2->session = s;
    winlink_set_window(wl2, wl->window);
    notify_session_window("window-linked", s, wl2->window);
    wl2->flags |= wl->flags & ((0x1 | 0x2) | 0x4);
  }

  if (s->curw != 0)
  {
    s->curw = winlink_find_by_index(&s->windows, s->curw->idx);
  }
  else
    s->curw = winlink_find_by_index(&s->windows, target->curw->idx);
  memcpy(&old_lastw, &s->lastw, sizeof(old_lastw));
  do
  {
    (&s->lastw)->tqh_first = 0;
    (&s->lastw)->tqh_last = &(&s->lastw)->tqh_first;
  }
  while (0);
  for (wl_idx = (&old_lastw)->tqh_first; (&wl[wl_idx]) != 0; wl_idx = wl_idx->sentry.tqe_next)
  {
    wl2_idx = winlink_find_by_index(&s->windows, wl->idx);
    if ((&wl2[wl2_idx]) != 0)
    {
      do
      {
        wl2->sentry.tqe_next = 0;
        wl2->sentry.tqe_prev = (&s->lastw)->tqh_last;
        *(&s->lastw)->tqh_last = &wl2[wl2_idx];
        (&s->lastw)->tqh_last = &wl2->sentry.tqe_next;
      }
      while (0);
    }
  }

  while (!((&old_windows)->rbh_root == 0))
  {
    wl_idx = (&old_windows)->rbh_root;
    wl2_idx = winlink_find_by_window_id(&s->windows, wl->window->id);
    if ((&wl2[wl2_idx]) == 0)
    {
      notify_session_window("window-unlinked", s, wl->window);
    }
    winlink_remove(&old_windows, wl);
  }

}


----------------------------
None
----------------------------
***/


int session_detach(struct session *s, struct winlink *wl)
{
  if (((s->curw == wl) && (session_last(s) != 0)) && (session_previous(s, 0) != 0))
  {
    session_next(s, 0);
  }
  wl->flags &= ~((0x1 | 0x2) | 0x4);
  notify_session_window("window-unlinked", s, wl->window);
  winlink_stack_remove(&s->lastw, wl);
  winlink_remove(&s->windows, wl);
  session_group_synchronize_from(s);
  if ((&s->windows)->rbh_root == 0)
  {
    session_destroy(s, __func__);
    return 1;
  }
  return 0;
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
int session_previous(struct session *s, int alert)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  if (s->curw == 0)
  {
    return -1;
  }
  wl_idx = winlink_previous(s->curw);
  if (alert)
  {
    wl_idx = session_previous_alert(wl_idx);
  }
  if ((&wl[wl_idx]) == 0)
  {
    wl_idx = winlinks_RB_MINMAX(&s->windows, 1);
    if (alert && ((wl_idx = session_previous_alert(wl_idx)) == 0))
    {
      return -1;
    }
  }
  return session_set_current(s, wl);
}


----------------------------
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
void session_group_synchronize_from(struct session *target)
{
  struct session_group *sg;
  unsigned int sg_idx = 0;
  struct session *s;
  unsigned int s_idx = 0;
  if ((sg_idx = session_group_contains(target)) == 0)
  {
    return;
  }
  for (s_idx = (&sg->sessions)->tqh_first; (&s[s_idx]) != 0; s_idx = s_idx->gentry.tqe_next)
  {
    if ((&s[s_idx]) != target)
    {
      session_group_synchronize1(target, s);
    }
  }

}


----------------------------
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


----------------------------
int session_last(struct session *s)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  wl_idx = (&s->lastw)->tqh_first;
  if ((&wl[wl_idx]) == 0)
  {
    return -1;
  }
  if ((&wl[wl_idx]) == s->curw)
  {
    return 1;
  }
  return session_set_current(s, wl);
}


----------------------------
void notify_session_window(const char *name, struct session *s, struct window *w)
{
  struct cmd_find_state fs;
  cmd_find_from_session_window(&fs, s, w, 0);
  notify_add(name, &fs, 0, s, w, 0);
}


----------------------------
void session_destroy(struct session *s, const char *from)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  log_debug("session %s destroyed (%s)", s->name, from);
  s->curw = 0;
  sessions_RB_REMOVE(&sessions, s);
  notify_session("session-closed", s);
  free(s->tio);
  if (event_initialized(&s->lock_timer))
  {
    event_del(&s->lock_timer);
  }
  session_group_remove(s);
  while (!((&s->lastw)->tqh_first == 0))
  {
    winlink_stack_remove(&s->lastw, (&s->lastw)->tqh_first);
  }

  while (!((&s->windows)->rbh_root == 0))
  {
    wl_idx = (&s->windows)->rbh_root;
    notify_session_window("window-unlinked", s, wl->window);
    winlink_remove(&s->windows, wl);
  }

  free((void *) s->cwd);
  session_remove_ref(s, __func__);
}


----------------------------
int session_next(struct session *s, int alert)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  if (s->curw == 0)
  {
    return -1;
  }
  wl_idx = winlink_next(s->curw);
  if (alert)
  {
    wl_idx = session_next_alert(wl_idx);
  }
  if ((&wl[wl_idx]) == 0)
  {
    wl_idx = winlinks_RB_MINMAX(&s->windows, -1);
    if (alert && ((wl_idx = session_next_alert(wl_idx)) == 0))
    {
      return -1;
    }
  }
  return session_set_current(s, wl);
}


----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_sessions_RB_INSERT_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const elm, struct session * const parent, struct session * const gparent, struct session * const tmp, unsigned int gparent_idx)
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
    helper_helper_helper_sessions_RB_INSERT_COLOR_1_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_sessions_RB_INSERT_COLOR_1_1_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct sessions
{
  struct session *rbh_root;
}
----------------------------
void helper_helper_helper_sessions_RB_INSERT_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const elm, struct session * const parent, struct session * const tmp)
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
void helper_helper_helper_sessions_RB_INSERT_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const gparent, struct session * const tmp, unsigned int gparent_idx)
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


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_sessions_RB_INSERT_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const elm, struct session * const parent, struct session * const gparent, struct session * const tmp, unsigned int gparent_idx)
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
    helper_helper_helper_sessions_RB_INSERT_COLOR_1_2_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_sessions_RB_INSERT_COLOR_1_2_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct sessions
{
  struct session *rbh_root;
}
----------------------------
void helper_helper_helper_sessions_RB_INSERT_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const gparent, struct session * const tmp, unsigned int gparent_idx)
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
void helper_helper_helper_sessions_RB_INSERT_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const elm, struct session * const parent, struct session * const tmp)
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
void helper_sessions_RB_INSERT_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const gparent_idx_ref, unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const elm, struct session * const parent, struct session * const gparent, struct session * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int gparent_idx = *gparent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  gparent_idx = parent->entry.rbe_parent;
  if ((&parent[parent_idx]) == gparent->entry.rbe_left)
  {
    helper_helper_sessions_RB_INSERT_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  else
  {
    helper_helper_sessions_RB_INSERT_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *gparent_idx_ref = gparent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct sessions
{
  struct session *rbh_root;
}
----------------------------
void helper_helper_sessions_RB_INSERT_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const elm, struct session * const parent, struct session * const gparent, struct session * const tmp, unsigned int gparent_idx)
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
    helper_helper_helper_sessions_RB_INSERT_COLOR_1_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_sessions_RB_INSERT_COLOR_1_1_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_sessions_RB_INSERT_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const elm, struct session * const parent, struct session * const gparent, struct session * const tmp, unsigned int gparent_idx)
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
    helper_helper_helper_sessions_RB_INSERT_COLOR_1_2_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_sessions_RB_INSERT_COLOR_1_2_1(&tmp_idx, head, gparent, tmp, gparent_idx);
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


void sessions_RB_INSERT_COLOR(struct sessions *head, struct session *elm)
{
  unsigned int elm_idx = 0;
  struct session *parent;
  unsigned int parent_idx = 0;
  struct session *gparent;
  unsigned int gparent_idx = 0;
  struct session *tmp;
  unsigned int tmp_idx = 0;
  while ((parent_idx = elm->entry.rbe_parent) && (parent->entry.rbe_color == 1))
  {
    helper_sessions_RB_INSERT_COLOR_1(&elm_idx, &parent_idx, &gparent_idx, &tmp_idx, head, elm, parent, gparent, tmp);
  }

  head->rbh_root->entry.rbe_color = 0;
}


/*** DEPENDENCIES:
struct sessions
{
  struct session *rbh_root;
}
----------------------------
void helper_sessions_RB_INSERT_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const gparent_idx_ref, unsigned int * const tmp_idx_ref, struct sessions * const head, struct session * const elm, struct session * const parent, struct session * const gparent, struct session * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int gparent_idx = *gparent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  gparent_idx = parent->entry.rbe_parent;
  if ((&parent[parent_idx]) == gparent->entry.rbe_left)
  {
    helper_helper_sessions_RB_INSERT_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  else
  {
    helper_helper_sessions_RB_INSERT_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
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


struct session *sessions_RB_NFIND(struct sessions *head, struct session *elm)
{
  struct session *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct session *res = 0;
  unsigned int res_idx = 0;
  int comp;
  while (tmp)
  {
    comp = session_cmp(elm, tmp);
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
struct sessions
{
  struct session *rbh_root;
}
----------------------------
int session_cmp(struct session *s1, struct session *s2)
{
  return strcmp(s1->name, s2->name);
}


----------------------------
None
----------------------------
***/


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_session_groups_RB_INSERT_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const gparent, struct session_group * const tmp, unsigned int gparent_idx)
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
struct session_groups
{
  struct session_group *rbh_root;
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


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_session_groups_RB_INSERT_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const elm, struct session_group * const parent, struct session_group * const tmp)
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
struct session_groups
{
  struct session_group *rbh_root;
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


// hint:  ['tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_session_groups_RB_INSERT_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const gparent, struct session_group * const tmp, unsigned int gparent_idx)
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
struct session_groups
{
  struct session_group *rbh_root;
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


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper_session_groups_RB_INSERT_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const elm, struct session_group * const parent, struct session_group * const tmp)
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
struct session_groups
{
  struct session_group *rbh_root;
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


struct session *sessions_RB_INSERT(struct sessions *head, struct session *elm)
{
  struct session *tmp;
  unsigned int tmp_idx = 0;
  struct session *parent = 0;
  unsigned int parent_idx = 0;
  int comp = 0;
  tmp_idx = head->rbh_root;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    comp = session_cmp(elm, parent);
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
  sessions_RB_INSERT_COLOR(head, elm);
  return 0;
}


/*** DEPENDENCIES:
struct sessions
{
  struct session *rbh_root;
}
----------------------------
void sessions_RB_INSERT_COLOR(struct sessions *head, struct session *elm)
{
  unsigned int elm_idx = 0;
  struct session *parent;
  unsigned int parent_idx = 0;
  struct session *gparent;
  unsigned int gparent_idx = 0;
  struct session *tmp;
  unsigned int tmp_idx = 0;
  while ((parent_idx = elm->entry.rbe_parent) && (parent->entry.rbe_color == 1))
  {
    helper_sessions_RB_INSERT_COLOR_1(&elm_idx, &parent_idx, &gparent_idx, &tmp_idx, head, elm, parent, gparent, tmp);
  }

  head->rbh_root->entry.rbe_color = 0;
}


----------------------------
int session_cmp(struct session *s1, struct session *s2)
{
  return strcmp(s1->name, s2->name);
}


----------------------------
None
----------------------------
***/


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_session_groups_RB_INSERT_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const elm, struct session_group * const parent, struct session_group * const gparent, struct session_group * const tmp, unsigned int gparent_idx)
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
    helper_helper_helper_session_groups_RB_INSERT_COLOR_1_2_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_session_groups_RB_INSERT_COLOR_1_2_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct session_groups
{
  struct session_group *rbh_root;
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
void helper_helper_helper_session_groups_RB_INSERT_COLOR_1_2_1(unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const gparent, struct session_group * const tmp, unsigned int gparent_idx)
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
void helper_helper_helper_session_groups_RB_INSERT_COLOR_1_2_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const elm, struct session_group * const parent, struct session_group * const tmp)
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


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_session_groups_RB_INSERT_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const elm, struct session_group * const parent, struct session_group * const gparent, struct session_group * const tmp, unsigned int gparent_idx)
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
    helper_helper_helper_session_groups_RB_INSERT_COLOR_1_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_session_groups_RB_INSERT_COLOR_1_1_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct session_groups
{
  struct session_group *rbh_root;
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
void helper_helper_helper_session_groups_RB_INSERT_COLOR_1_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const elm, struct session_group * const parent, struct session_group * const tmp)
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
void helper_helper_helper_session_groups_RB_INSERT_COLOR_1_1_1(unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const gparent, struct session_group * const tmp, unsigned int gparent_idx)
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


// hint:  ['elm_idx_ref is a mutable refrence to unsigned int', 'parent_idx_ref is a mutable refrence to unsigned int', 'gparent_idx_ref is a mutable refrence to unsigned int', 'tmp_idx_ref is a mutable refrence to unsigned int']
void helper_session_groups_RB_INSERT_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const gparent_idx_ref, unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const elm, struct session_group * const parent, struct session_group * const gparent, struct session_group * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int gparent_idx = *gparent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  gparent_idx = parent->entry.rbe_parent;
  if ((&parent[parent_idx]) == gparent->entry.rbe_left)
  {
    helper_helper_session_groups_RB_INSERT_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  else
  {
    helper_helper_session_groups_RB_INSERT_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *gparent_idx_ref = gparent_idx;
  *tmp_idx_ref = tmp_idx;
}


/*** DEPENDENCIES:
struct session_groups
{
  struct session_group *rbh_root;
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
void helper_helper_session_groups_RB_INSERT_COLOR_1_2(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const elm, struct session_group * const parent, struct session_group * const gparent, struct session_group * const tmp, unsigned int gparent_idx)
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
    helper_helper_helper_session_groups_RB_INSERT_COLOR_1_2_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_session_groups_RB_INSERT_COLOR_1_2_1(&tmp_idx, head, gparent, tmp, gparent_idx);
  }
  while (0);
  *elm_idx_ref = elm_idx;
  *parent_idx_ref = parent_idx;
  *tmp_idx_ref = tmp_idx;
}


----------------------------
void helper_helper_session_groups_RB_INSERT_COLOR_1_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const elm, struct session_group * const parent, struct session_group * const gparent, struct session_group * const tmp, unsigned int gparent_idx)
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
    helper_helper_helper_session_groups_RB_INSERT_COLOR_1_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, tmp);
  }
  do
  {
    parent->entry.rbe_color = 0;
    gparent->entry.rbe_color = 1;
  }
  while (0);
  do
  {
    helper_helper_helper_session_groups_RB_INSERT_COLOR_1_1_1(&tmp_idx, head, gparent, tmp, gparent_idx);
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


void session_groups_RB_INSERT_COLOR(struct session_groups *head, struct session_group *elm)
{
  unsigned int elm_idx = 0;
  struct session_group *parent;
  unsigned int parent_idx = 0;
  struct session_group *gparent;
  unsigned int gparent_idx = 0;
  struct session_group *tmp;
  unsigned int tmp_idx = 0;
  while ((parent_idx = elm->entry.rbe_parent) && (parent->entry.rbe_color == 1))
  {
    helper_session_groups_RB_INSERT_COLOR_1(&elm_idx, &parent_idx, &gparent_idx, &tmp_idx, head, elm, parent, gparent, tmp);
  }

  head->rbh_root->entry.rbe_color = 0;
}


/*** DEPENDENCIES:
struct session_groups
{
  struct session_group *rbh_root;
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
void helper_session_groups_RB_INSERT_COLOR_1(unsigned int * const elm_idx_ref, unsigned int * const parent_idx_ref, unsigned int * const gparent_idx_ref, unsigned int * const tmp_idx_ref, struct session_groups * const head, struct session_group * const elm, struct session_group * const parent, struct session_group * const gparent, struct session_group * const tmp)
{
  unsigned int elm_idx = *elm_idx_ref;
  unsigned int parent_idx = *parent_idx_ref;
  unsigned int gparent_idx = *gparent_idx_ref;
  unsigned int tmp_idx = *tmp_idx_ref;
  gparent_idx = parent->entry.rbe_parent;
  if ((&parent[parent_idx]) == gparent->entry.rbe_left)
  {
    helper_helper_session_groups_RB_INSERT_COLOR_1_1(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
  }
  else
  {
    helper_helper_session_groups_RB_INSERT_COLOR_1_2(&elm_idx, &parent_idx, &tmp_idx, head, elm, parent, gparent, tmp, gparent_idx);
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


struct session_group *session_groups_RB_FIND(struct session_groups *head, struct session_group *elm)
{
  struct session_group *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  int comp;
  while (tmp)
  {
    comp = session_group_cmp(elm, tmp);
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
struct session_groups
{
  struct session_group *rbh_root;
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
int session_group_cmp(struct session_group *s1, struct session_group *s2)
{
  return strcmp(s1->name, s2->name);
}


----------------------------
None
----------------------------
***/


struct session_group *session_groups_RB_NFIND(struct session_groups *head, struct session_group *elm)
{
  struct session_group *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct session_group *res = 0;
  unsigned int res_idx = 0;
  int comp;
  while (tmp)
  {
    comp = session_group_cmp(elm, tmp);
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
struct session_groups
{
  struct session_group *rbh_root;
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
int session_group_cmp(struct session_group *s1, struct session_group *s2)
{
  return strcmp(s1->name, s2->name);
}


----------------------------
None
----------------------------
***/


struct session_group *session_group_find(const char *name)
{
  struct session_group sg;
  sg.name = name;
  return session_groups_RB_FIND(&session_groups, &sg);
}


/*** DEPENDENCIES:
struct session_groups
{
  struct session_group *rbh_root;
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
struct session_group *session_groups_RB_FIND(struct session_groups *head, struct session_group *elm)
{
  struct session_group *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  int comp;
  while (tmp)
  {
    comp = session_group_cmp(elm, tmp);
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


void session_group_add(struct session_group *sg, struct session *s)
{
  if (session_group_contains(s) == 0)
  {
    do
    {
      s->gentry.tqe_next = 0;
      s->gentry.tqe_prev = (&sg->sessions)->tqh_last;
      *(&sg->sessions)->tqh_last = s;
      (&sg->sessions)->tqh_last = &s->gentry.tqe_next;
    }
    while (0);
  }
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
struct sessions
{
  struct session *rbh_root;
}
----------------------------
None
----------------------------
***/


struct session_group *session_groups_RB_INSERT(struct session_groups *head, struct session_group *elm)
{
  struct session_group *tmp;
  unsigned int tmp_idx = 0;
  struct session_group *parent = 0;
  unsigned int parent_idx = 0;
  int comp = 0;
  tmp_idx = head->rbh_root;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    comp = session_group_cmp(elm, parent);
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
  session_groups_RB_INSERT_COLOR(head, elm);
  return 0;
}


/*** DEPENDENCIES:
struct session_groups
{
  struct session_group *rbh_root;
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
void session_groups_RB_INSERT_COLOR(struct session_groups *head, struct session_group *elm)
{
  unsigned int elm_idx = 0;
  struct session_group *parent;
  unsigned int parent_idx = 0;
  struct session_group *gparent;
  unsigned int gparent_idx = 0;
  struct session_group *tmp;
  unsigned int tmp_idx = 0;
  while ((parent_idx = elm->entry.rbe_parent) && (parent->entry.rbe_color == 1))
  {
    helper_session_groups_RB_INSERT_COLOR_1(&elm_idx, &parent_idx, &gparent_idx, &tmp_idx, head, elm, parent, gparent, tmp);
  }

  head->rbh_root->entry.rbe_color = 0;
}


----------------------------
int session_group_cmp(struct session_group *s1, struct session_group *s2)
{
  return strcmp(s1->name, s2->name);
}


----------------------------
None
----------------------------
***/


struct session *session_next_session(struct session *s)
{
  struct session *s2;
  unsigned int s2_idx = 0;
  if (((&sessions)->rbh_root == 0) || (!session_alive(s)))
  {
    return 0;
  }
  s2_idx = sessions_RB_NEXT(s);
  if ((&s2[s2_idx]) == 0)
  {
    s2_idx = sessions_RB_MINMAX(&sessions, -1);
  }
  if ((&s2[s2_idx]) == s)
  {
    return 0;
  }
  return s2;
}


/*** DEPENDENCIES:
struct session *sessions_RB_MINMAX(struct sessions *head, int val)
{
  struct session *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct session *parent = 0;
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
struct sessions
{
  struct session *rbh_root;
}
----------------------------
struct session *sessions_RB_NEXT(struct session *elm)
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


struct session *session_previous_session(struct session *s)
{
  struct session *s2;
  unsigned int s2_idx = 0;
  if (((&sessions)->rbh_root == 0) || (!session_alive(s)))
  {
    return 0;
  }
  s2_idx = sessions_RB_PREV(s);
  if ((&s2[s2_idx]) == 0)
  {
    s2_idx = sessions_RB_MINMAX(&sessions, 1);
  }
  if ((&s2[s2_idx]) == s)
  {
    return 0;
  }
  return s2;
}


/*** DEPENDENCIES:
struct session *sessions_RB_PREV(struct session *elm)
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
struct sessions
{
  struct session *rbh_root;
}
----------------------------
struct session *sessions_RB_MINMAX(struct sessions *head, int val)
{
  struct session *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct session *parent = 0;
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


int session_select(struct session *s, int idx)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  wl_idx = winlink_find_by_index(&s->windows, idx);
  return session_set_current(s, wl);
}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
int session_set_current(struct session *s, struct winlink *wl)
{
  if (wl == 0)
  {
    return -1;
  }
  if (wl == s->curw)
  {
    return 1;
  }
  winlink_stack_remove(&s->lastw, wl);
  winlink_stack_push(&s->lastw, s->curw);
  s->curw = wl;
  winlink_clear_flags(wl);
  window_update_activity(wl->window);
  notify_session("session-window-changed", s);
  return 0;
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


void session_group_synchronize_to(struct session *s)
{
  struct session_group *sg;
  unsigned int sg_idx = 0;
  struct session *target;
  unsigned int target_idx = 0;
  if ((sg_idx = session_group_contains(s)) == 0)
  {
    return;
  }
  target_idx = 0;
  for (target_idx = (&sg->sessions)->tqh_first; (&target[target_idx]) != 0; target_idx = target_idx->gentry.tqe_next)
  {
    if ((&target[target_idx]) != s)
    {
      break;
    }
  }

  if ((&target[target_idx]) != 0)
  {
    session_group_synchronize1(target, s);
  }
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
struct sessions
{
  struct session *rbh_root;
}
----------------------------
static void session_group_synchronize1(struct session *target, struct session *s)
{
  struct winlinks old_windows;
  struct winlinks *ww;
  unsigned int ww_idx = 0;
  struct winlink_stack old_lastw;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct winlink *wl2;
  unsigned int wl2_idx = 0;
  ww_idx = &target->windows;
  if (ww->rbh_root == 0)
  {
    return;
  }
  if ((((s->curw != 0) && (winlink_find_by_index(ww, s->curw->idx) == 0)) && (session_last(s) != 0)) && (session_previous(s, 0) != 0))
  {
    session_next(s, 0);
  }
  memcpy(&old_windows, &s->windows, sizeof(old_windows));
  do
  {
    (&s->windows)->rbh_root = 0;
  }
  while (0);
  for (wl_idx = winlinks_RB_MINMAX(ww, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    wl2_idx = winlink_add(&s->windows, wl->idx);
    wl2->session = s;
    winlink_set_window(wl2, wl->window);
    notify_session_window("window-linked", s, wl2->window);
    wl2->flags |= wl->flags & ((0x1 | 0x2) | 0x4);
  }

  if (s->curw != 0)
  {
    s->curw = winlink_find_by_index(&s->windows, s->curw->idx);
  }
  else
    s->curw = winlink_find_by_index(&s->windows, target->curw->idx);
  memcpy(&old_lastw, &s->lastw, sizeof(old_lastw));
  do
  {
    (&s->lastw)->tqh_first = 0;
    (&s->lastw)->tqh_last = &(&s->lastw)->tqh_first;
  }
  while (0);
  for (wl_idx = (&old_lastw)->tqh_first; (&wl[wl_idx]) != 0; wl_idx = wl_idx->sentry.tqe_next)
  {
    wl2_idx = winlink_find_by_index(&s->windows, wl->idx);
    if ((&wl2[wl2_idx]) != 0)
    {
      do
      {
        wl2->sentry.tqe_next = 0;
        wl2->sentry.tqe_prev = (&s->lastw)->tqh_last;
        *(&s->lastw)->tqh_last = &wl2[wl2_idx];
        (&s->lastw)->tqh_last = &wl2->sentry.tqe_next;
      }
      while (0);
    }
  }

  while (!((&old_windows)->rbh_root == 0))
  {
    wl_idx = (&old_windows)->rbh_root;
    wl2_idx = winlink_find_by_window_id(&s->windows, wl->window->id);
    if ((&wl2[wl2_idx]) == 0)
    {
      notify_session_window("window-unlinked", s, wl->window);
    }
    winlink_remove(&old_windows, wl);
  }

}


----------------------------
None
----------------------------
***/


struct winlink *session_attach(struct session *s, struct window *w, int idx, char **cause)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  if ((wl_idx = winlink_add(&s->windows, idx)) == 0)
  {
    xasprintf(cause, "index in use: %d", idx);
    return 0;
  }
  wl->session = s;
  winlink_set_window(wl, w);
  notify_session_window("window-linked", s, w);
  session_group_synchronize_from(s);
  return wl;
}


/*** DEPENDENCIES:
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


----------------------------
struct windows
{
  struct window *rbh_root;
}
----------------------------
void session_group_synchronize_from(struct session *target)
{
  struct session_group *sg;
  unsigned int sg_idx = 0;
  struct session *s;
  unsigned int s_idx = 0;
  if ((sg_idx = session_group_contains(target)) == 0)
  {
    return;
  }
  for (s_idx = (&sg->sessions)->tqh_first; (&s[s_idx]) != 0; s_idx = s_idx->gentry.tqe_next)
  {
    if ((&s[s_idx]) != target)
    {
      session_group_synchronize1(target, s);
    }
  }

}


----------------------------
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
void notify_session_window(const char *name, struct session *s, struct window *w)
{
  struct cmd_find_state fs;
  cmd_find_from_session_window(&fs, s, w, 0);
  notify_add(name, &fs, 0, s, w, 0);
}


----------------------------
None
----------------------------
***/


struct session_group *session_group_new(const char *name)
{
  struct session_group *sg;
  unsigned int sg_idx = 0;
  if ((sg_idx = session_group_find(name)) != 0)
  {
    return sg;
  }
  sg_idx = xcalloc(1, sizeof(*sg_idx));
  sg->name = xstrdup(name);
  do
  {
    (&sg->sessions)->tqh_first = 0;
    (&sg->sessions)->tqh_last = &(&sg->sessions)->tqh_first;
  }
  while (0);
  session_groups_RB_INSERT(&session_groups, sg);
  return sg;
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
struct session_groups
{
  struct session_group *rbh_root;
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
struct session_group *session_groups_RB_INSERT(struct session_groups *head, struct session_group *elm)
{
  struct session_group *tmp;
  unsigned int tmp_idx = 0;
  struct session_group *parent = 0;
  unsigned int parent_idx = 0;
  int comp = 0;
  tmp_idx = head->rbh_root;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    comp = session_group_cmp(elm, parent);
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
  session_groups_RB_INSERT_COLOR(head, elm);
  return 0;
}


----------------------------
struct session_group *session_group_find(const char *name)
{
  struct session_group sg;
  sg.name = name;
  return session_groups_RB_FIND(&session_groups, &sg);
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
None
----------------------------
***/


struct winlink *session_new(struct session *s, const char *name, int argc, char **argv, const char *path, const char *cwd, int idx, char **cause)
{
  struct window *w;
  unsigned int w_idx = 0;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct environ *env;
  unsigned int env_idx = 0;
  const char *shell;
  unsigned int shell_idx = 0;
  u_int hlimit;
  if ((wl_idx = winlink_add(&s->windows, idx)) == 0)
  {
    xasprintf(cause, "index in use: %d", idx);
    return 0;
  }
  wl->session = s;
  shell_idx = options_get_string(s->options, "default-shell");
  if ((shell[shell_idx] == '\0') || areshell(shell))
  {
    shell_idx = "/bin/sh";
  }
  hlimit = options_get_number(s->options, "history-limit");
  env_idx = environ_for_session(s, 0);
  w_idx = window_create_spawn(name, argc, argv, path, shell, cwd, env, s->tio, s->sx, s->sy, hlimit, cause);
  if ((&w[w_idx]) == 0)
  {
    winlink_remove(&s->windows, wl);
    environ_free(env);
    return 0;
  }
  winlink_set_window(wl, w);
  environ_free(env);
  notify_session_window("window-linked", s, w);
  session_group_synchronize_from(s);
  return wl;
}


/*** DEPENDENCIES:
struct environ *environ_for_session(struct session *s, int no_TERM)
{
  struct environ *env;
  unsigned int env_idx = 0;
  const char *value;
  unsigned int value_idx = 0;
  int idx;
  env_idx = environ_create();
  environ_copy(global_environ, env);
  if (s != 0)
  {
    environ_copy(s->environ, env);
  }
  if (!no_TERM)
  {
    value_idx = options_get_string(global_options, "default-terminal");
    environ_set(env, "TERM", "%s", value);
  }
  if (s != 0)
  {
    idx = s->id;
  }
  else
    idx = -1;
  environ_set(env, "TMUX", "%s,%ld,%d", socket_path, (long) getpid(), idx);
  return env;
}


----------------------------
void environ_free(struct environ *env)
{
  struct environ_entry *envent;
  unsigned int envent_idx = 0;
  struct environ_entry *envent1;
  unsigned int envent1_idx = 0;
  for (envent_idx = environ_RB_MINMAX(env, -1); ((&envent[envent_idx]) != 0) && ((envent1_idx = environ_RB_NEXT(envent), 1)); envent_idx = &envent1[envent1_idx])
  {
    environ_RB_REMOVE(env, envent);
    free(envent->name);
    free(envent->value);
    free(envent);
  }

  free(env);
}


----------------------------
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


----------------------------
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


----------------------------
struct windows
{
  struct window *rbh_root;
}
----------------------------
int areshell(const char *shell)
{
  const char *progname;
  unsigned int progname_idx = 0;
  const char *ptr;
  unsigned int ptr_idx = 0;
  if ((ptr_idx = strrchr(shell, '/')) != 0)
  {
    ptr_idx += 1;
  }
  else
    ptr_idx = shell;
  progname_idx = getprogname();
  if (progname[progname_idx] == '-')
  {
    progname_idx += 1;
  }
  if (strcmp(ptr, progname) == 0)
  {
    return 1;
  }
  return 0;
}


----------------------------
void session_group_synchronize_from(struct session *target)
{
  struct session_group *sg;
  unsigned int sg_idx = 0;
  struct session *s;
  unsigned int s_idx = 0;
  if ((sg_idx = session_group_contains(target)) == 0)
  {
    return;
  }
  for (s_idx = (&sg->sessions)->tqh_first; (&s[s_idx]) != 0; s_idx = s_idx->gentry.tqe_next)
  {
    if ((&s[s_idx]) != target)
    {
      session_group_synchronize1(target, s);
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


----------------------------
void notify_session_window(const char *name, struct session *s, struct window *w)
{
  struct cmd_find_state fs;
  cmd_find_from_session_window(&fs, s, w, 0);
  notify_add(name, &fs, 0, s, w, 0);
}


----------------------------
None
----------------------------
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


----------------------------
None
----------------------------
***/


struct session *session_create(const char *prefix, const char *name, int argc, char **argv, const char *path, const char *cwd, struct environ *env, struct termios *tio, int idx, u_int sx, u_int sy, char **cause)
{
  struct session *s;
  unsigned int s_idx = 0;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  s_idx = xcalloc(1, sizeof(*s_idx));
  s->references = 1;
  s->flags = 0;
  s->cwd = xstrdup(cwd);
  s->curw = 0;
  do
  {
    (&s->lastw)->tqh_first = 0;
    (&s->lastw)->tqh_last = &(&s->lastw)->tqh_first;
  }
  while (0);
  do
  {
    (&s->windows)->rbh_root = 0;
  }
  while (0);
  s->environ = environ_create();
  if (env != 0)
  {
    environ_copy(env, s->environ);
  }
  s->options = options_create(global_s_options);
  s->hooks = hooks_create(global_hooks);
  status_update_saved(s);
  s->tio = 0;
  if (tio != 0)
  {
    s->tio = xmalloc(sizeof(*s->tio));
    memcpy(s->tio, tio, sizeof(*s->tio));
  }
  s->sx = sx;
  s->sy = sy;
  if (name != 0)
  {
    s->name = xstrdup(name);
    s->id = next_session_id;
    next_session_id += 1;
  }
  else
  {
    s->name = 0;
    do
    {
      s->id = next_session_id;
      next_session_id += 1;
      free(s->name);
      if (prefix != 0)
      {
        xasprintf(&s->name, "%s-%u", prefix, s->id);
      }
      else
        xasprintf(&s->name, "%u", s->id);
    }
    while (sessions_RB_FIND(&sessions, s) != 0);
  }
  sessions_RB_INSERT(&sessions, s);
  log_debug("new session %s $%u", s->name, s->id);
  if (gettimeofday(&s->creation_time, 0) != 0)
  {
    fatal("gettimeofday failed");
  }
  session_update_activity(s, &s->creation_time);
  if (argc >= 0)
  {
    wl_idx = session_new(s, 0, argc, argv, path, cwd, idx, cause);
    if ((&wl[wl_idx]) == 0)
    {
      session_destroy(s, __func__);
      return 0;
    }
    session_select(s, (&s->windows)->rbh_root->idx);
  }
  log_debug("session %s created", s->name);
  return s;
}


/*** DEPENDENCIES:
struct environ *environ_create(void)
{
  struct environ *env;
  unsigned int env_idx = 0;
  env_idx = xcalloc(1, sizeof(*env_idx));
  do
  {
    env->rbh_root = 0;
  }
  while (0);
  return env;
}


----------------------------
struct winlink *session_new(struct session *s, const char *name, int argc, char **argv, const char *path, const char *cwd, int idx, char **cause)
{
  struct window *w;
  unsigned int w_idx = 0;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct environ *env;
  unsigned int env_idx = 0;
  const char *shell;
  unsigned int shell_idx = 0;
  u_int hlimit;
  if ((wl_idx = winlink_add(&s->windows, idx)) == 0)
  {
    xasprintf(cause, "index in use: %d", idx);
    return 0;
  }
  wl->session = s;
  shell_idx = options_get_string(s->options, "default-shell");
  if ((shell[shell_idx] == '\0') || areshell(shell))
  {
    shell_idx = "/bin/sh";
  }
  hlimit = options_get_number(s->options, "history-limit");
  env_idx = environ_for_session(s, 0);
  w_idx = window_create_spawn(name, argc, argv, path, shell, cwd, env, s->tio, s->sx, s->sy, hlimit, cause);
  if ((&w[w_idx]) == 0)
  {
    winlink_remove(&s->windows, wl);
    environ_free(env);
    return 0;
  }
  winlink_set_window(wl, w);
  environ_free(env);
  notify_session_window("window-linked", s, w);
  session_group_synchronize_from(s);
  return wl;
}


----------------------------
struct windows
{
  struct window *rbh_root;
}
----------------------------
static u_int next_session_id
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
void session_destroy(struct session *s, const char *from)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  log_debug("session %s destroyed (%s)", s->name, from);
  s->curw = 0;
  sessions_RB_REMOVE(&sessions, s);
  notify_session("session-closed", s);
  free(s->tio);
  if (event_initialized(&s->lock_timer))
  {
    event_del(&s->lock_timer);
  }
  session_group_remove(s);
  while (!((&s->lastw)->tqh_first == 0))
  {
    winlink_stack_remove(&s->lastw, (&s->lastw)->tqh_first);
  }

  while (!((&s->windows)->rbh_root == 0))
  {
    wl_idx = (&s->windows)->rbh_root;
    notify_session_window("window-unlinked", s, wl->window);
    winlink_remove(&s->windows, wl);
  }

  free((void *) s->cwd);
  session_remove_ref(s, __func__);
}


----------------------------
struct session *sessions_RB_INSERT(struct sessions *head, struct session *elm)
{
  struct session *tmp;
  unsigned int tmp_idx = 0;
  struct session *parent = 0;
  unsigned int parent_idx = 0;
  int comp = 0;
  tmp_idx = head->rbh_root;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    comp = session_cmp(elm, parent);
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
  sessions_RB_INSERT_COLOR(head, elm);
  return 0;
}


----------------------------
None
----------------------------
struct sessions
{
  struct session *rbh_root;
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
int session_select(struct session *s, int idx)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  wl_idx = winlink_find_by_index(&s->windows, idx);
  return session_set_current(s, wl);
}


----------------------------
void session_update_activity(struct session *s, struct timeval *from)
{
  struct timeval *last = &s->last_activity_time;
  struct timeval tv;
  memcpy(last, &s->activity_time, sizeof(*last));
  if (from == 0)
  {
    gettimeofday(&s->activity_time, 0);
  }
  else
    memcpy(&s->activity_time, from, sizeof(s->activity_time));
  log_debug("session %s activity %lld.%06d (last %lld.%06d)", s->name, (long long) s->activity_time.tv_sec, (int) s->activity_time.tv_usec, (long long) last->tv_sec, (int) last->tv_usec);
  if (evtimer_initialized(&s->lock_timer))
  {
    evtimer_del(&s->lock_timer);
  }
  else
    evtimer_set(&s->lock_timer, session_lock_timer, s);
  if ((~s->flags) & 0x1)
  {
    timerclear(&tv);
    tv.tv_sec = options_get_number(s->options, "lock-after-time");
    if (tv.tv_sec != 0)
    {
      evtimer_add(&s->lock_timer, &tv);
    }
  }
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
struct hooks *hooks_create(struct hooks *parent)
{
  struct hooks *hooks;
  unsigned int hooks_idx = 0;
  hooks_idx = xcalloc(1, sizeof(*hooks_idx));
  do
  {
    (&hooks->tree)->rbh_root = 0;
  }
  while (0);
  hooks->parent = parent;
  return hooks;
}


----------------------------
void environ_copy(struct environ *srcenv, struct environ *dstenv)
{
  struct environ_entry *envent;
  unsigned int envent_idx = 0;
  for (envent_idx = environ_RB_MINMAX(srcenv, -1); (&envent[envent_idx]) != 0; envent_idx = environ_RB_NEXT(envent_idx))
  {
    if (envent->value == 0)
    {
      environ_clear(dstenv, envent->name);
    }
    else
      environ_set(dstenv, envent->name, "%s", envent->value);
  }

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
void status_update_saved(struct session *s)
{
  if (!options_get_number(s->options, "status"))
  {
    s->statusat = -1;
  }
  else
    if (options_get_number(s->options, "status-position") == 0)
  {
    s->statusat = 0;
  }
  else
    s->statusat = 1;
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
struct session *sessions_RB_FIND(struct sessions *head, struct session *elm)
{
  struct session *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  int comp;
  while (tmp)
  {
    comp = session_cmp(elm, tmp);
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


