void cmd_find_copy_state(struct cmd_find_state *dst, struct cmd_find_state *src)
{
  dst->s = src->s;
  dst->wl = src->wl;
  dst->idx = src->idx;
  dst->w = src->w;
  dst->wp = src->wp;
}


/*** DEPENDENCIES:
None
----------------------------
***/


void cmd_find_clear_state(struct cmd_find_state *fs, int flags)
{
  memset(fs, 0, sizeof(*fs));
  fs->flags = flags;
  fs->idx = -1;
}


/*** DEPENDENCIES:
None
----------------------------
***/


int cmd_find_valid_state(struct cmd_find_state *fs)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  if ((((fs->s == 0) || (fs->wl == 0)) || (fs->w == 0)) || (fs->wp == 0))
  {
    return 0;
  }
  if (!session_alive(fs->s))
  {
    return 0;
  }
  for (wl_idx = winlinks_RB_MINMAX(&fs->s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    if ((wl->window == fs->w) && ((&wl[wl_idx]) == fs->wl))
    {
      break;
    }
  }

  if ((&wl[wl_idx]) == 0)
  {
    return 0;
  }
  if (fs->w != fs->wl->window)
  {
    return 0;
  }
  return window_has_pane(fs->w, fs->wp);
}


/*** DEPENDENCIES:
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


----------------------------
struct windows
{
  struct window *rbh_root;
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


void cmd_find_log_state(const char *prefix, struct cmd_find_state *fs)
{
  if (fs->s != 0)
  {
    log_debug("%s: s=$%u", prefix, fs->s->id);
  }
  else
    log_debug("%s: s=none", prefix);
  if (fs->wl != 0)
  {
    log_debug("%s: wl=%u %d w=@%u %s", prefix, fs->wl->idx, fs->wl->window == fs->w, fs->w->id, fs->w->name);
  }
  else
    log_debug("%s: wl=none", prefix);
  if (fs->wp != 0)
  {
    log_debug("%s: wp=%%%u", prefix, fs->wp->id);
  }
  else
    log_debug("%s: wp=none", prefix);
  if (fs->idx != (-1))
  {
    log_debug("%s: idx=%d", prefix, fs->idx);
  }
  else
    log_debug("%s: idx=none", prefix);
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


static int cmd_find_session_better(struct session *s, struct session *than, int flags)
{
  int attached;
  if (than == 0)
  {
    return 1;
  }
  if (flags & 0x1)
  {
    attached = (~than->flags) & 0x1;
    if (attached && (s->flags & 0x1))
    {
      return 1;
    }
    else
      if ((!attached) && ((~s->flags) & 0x1))
    {
      return 0;
    }
  }
  return ((&s->activity_time)->tv_sec == (&than->activity_time)->tv_sec) ? ((&s->activity_time)->tv_usec > (&than->activity_time)->tv_usec) : ((&s->activity_time)->tv_sec > (&than->activity_time)->tv_sec);
}


/*** DEPENDENCIES:
None
----------------------------
***/


static struct session *cmd_find_best_session(struct session **slist, u_int ssize, int flags)
{
  struct session *s_loop;
  unsigned int s_loop_idx = 0;
  struct session *s;
  unsigned int s_idx = 0;
  u_int i;
  s_idx = 0;
  if (slist != 0)
  {
    for (i = 0; i < ssize; i += 1)
    {
      if (cmd_find_session_better(slist[i], s, flags))
      {
        s_idx = slist[i];
      }
    }

  }
  else
  {
    for (s_loop_idx = sessions_RB_MINMAX(&sessions, -1); (&s_loop[s_loop_idx]) != 0; s_loop_idx = sessions_RB_NEXT(s_loop_idx))
    {
      if (cmd_find_session_better(s_loop, s, flags))
      {
        s_idx = &s_loop[s_loop_idx];
      }
    }

  }
  return s;
}


/*** DEPENDENCIES:
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
static int cmd_find_session_better(struct session *s, struct session *than, int flags)
{
  int attached;
  if (than == 0)
  {
    return 1;
  }
  if (flags & 0x1)
  {
    attached = (~than->flags) & 0x1;
    if (attached && (s->flags & 0x1))
    {
      return 1;
    }
    else
      if ((!attached) && ((~s->flags) & 0x1))
    {
      return 0;
    }
  }
  return ((&s->activity_time)->tv_sec == (&than->activity_time)->tv_sec) ? ((&s->activity_time)->tv_usec > (&than->activity_time)->tv_usec) : ((&s->activity_time)->tv_sec > (&than->activity_time)->tv_sec);
}


----------------------------
None
----------------------------
***/


int cmd_find_from_nothing(struct cmd_find_state *fs, int flags)
{
  cmd_find_clear_state(fs, flags);
  fs->s = cmd_find_best_session(0, 0, flags);
  if (fs->s == 0)
  {
    cmd_find_clear_state(fs, flags);
    return -1;
  }
  fs->wl = fs->s->curw;
  fs->idx = fs->wl->idx;
  fs->w = fs->wl->window;
  fs->wp = fs->w->active;
  cmd_find_log_state(__func__, fs);
  return 0;
}


/*** DEPENDENCIES:
void cmd_find_log_state(const char *prefix, struct cmd_find_state *fs)
{
  if (fs->s != 0)
  {
    log_debug("%s: s=$%u", prefix, fs->s->id);
  }
  else
    log_debug("%s: s=none", prefix);
  if (fs->wl != 0)
  {
    log_debug("%s: wl=%u %d w=@%u %s", prefix, fs->wl->idx, fs->wl->window == fs->w, fs->w->id, fs->w->name);
  }
  else
    log_debug("%s: wl=none", prefix);
  if (fs->wp != 0)
  {
    log_debug("%s: wp=%%%u", prefix, fs->wp->id);
  }
  else
    log_debug("%s: wp=none", prefix);
  if (fs->idx != (-1))
  {
    log_debug("%s: idx=%d", prefix, fs->idx);
  }
  else
    log_debug("%s: idx=none", prefix);
}


----------------------------
void cmd_find_clear_state(struct cmd_find_state *fs, int flags)
{
  memset(fs, 0, sizeof(*fs));
  fs->flags = flags;
  fs->idx = -1;
}


----------------------------
static struct session *cmd_find_best_session(struct session **slist, u_int ssize, int flags)
{
  struct session *s_loop;
  unsigned int s_loop_idx = 0;
  struct session *s;
  unsigned int s_idx = 0;
  u_int i;
  s_idx = 0;
  if (slist != 0)
  {
    for (i = 0; i < ssize; i += 1)
    {
      if (cmd_find_session_better(slist[i], s, flags))
      {
        s_idx = slist[i];
      }
    }

  }
  else
  {
    for (s_loop_idx = sessions_RB_MINMAX(&sessions, -1); (&s_loop[s_loop_idx]) != 0; s_loop_idx = sessions_RB_NEXT(s_loop_idx))
    {
      if (cmd_find_session_better(s_loop, s, flags))
      {
        s_idx = &s_loop[s_loop_idx];
      }
    }

  }
  return s;
}


----------------------------
None
----------------------------
***/


int cmd_find_empty_state(struct cmd_find_state *fs)
{
  if ((((fs->s == 0) && (fs->wl == 0)) && (fs->w == 0)) && (fs->wp == 0))
  {
    return 1;
  }
  return 0;
}


/*** DEPENDENCIES:
None
----------------------------
***/


static int cmd_find_best_winlink_with_window(struct cmd_find_state *fs)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct winlink *wl_loop;
  unsigned int wl_loop_idx = 0;
  wl_idx = 0;
  if ((fs->s->curw != 0) && (fs->s->curw->window == fs->w))
  {
    wl_idx = fs->s->curw;
  }
  else
  {
    for (wl_loop_idx = winlinks_RB_MINMAX(&fs->s->windows, -1); (&wl_loop[wl_loop_idx]) != 0; wl_loop_idx = winlinks_RB_NEXT(wl_loop_idx))
    {
      if (wl_loop->window == fs->w)
      {
        wl_idx = &wl_loop[wl_loop_idx];
        break;
      }
    }

  }
  if ((&wl[wl_idx]) == 0)
  {
    return -1;
  }
  fs->wl = &wl[wl_idx];
  fs->idx = fs->wl->idx;
  return 0;
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


static int cmd_find_best_session_with_window(struct cmd_find_state *fs)
{
  struct session **slist = 0;
  unsigned int slist_idx = 0;
  u_int ssize;
  struct session *s;
  unsigned int s_idx = 0;
  ssize = 0;
  for (s_idx = sessions_RB_MINMAX(&sessions, -1); (&s[s_idx]) != 0; s_idx = sessions_RB_NEXT(s_idx))
  {
    if (!session_has(s, fs->w))
    {
      continue;
    }
    slist_idx = xreallocarray(slist_idx, ssize + 1, sizeof(*slist_idx));
    slist[ssize + slist_idx] = &s[s_idx];
    ssize += 1;
  }

  if (ssize == 0)
  {
    goto fail;
  }
  fs->s = cmd_find_best_session(slist, ssize, fs->flags);
  if (fs->s == 0)
  {
    goto fail;
  }
  free(slist);
  return cmd_find_best_winlink_with_window(fs);
  fail:
  free(slist);

  return -1;
}


/*** DEPENDENCIES:
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


----------------------------
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
static struct session *cmd_find_best_session(struct session **slist, u_int ssize, int flags)
{
  struct session *s_loop;
  unsigned int s_loop_idx = 0;
  struct session *s;
  unsigned int s_idx = 0;
  u_int i;
  s_idx = 0;
  if (slist != 0)
  {
    for (i = 0; i < ssize; i += 1)
    {
      if (cmd_find_session_better(slist[i], s, flags))
      {
        s_idx = slist[i];
      }
    }

  }
  else
  {
    for (s_loop_idx = sessions_RB_MINMAX(&sessions, -1); (&s_loop[s_loop_idx]) != 0; s_loop_idx = sessions_RB_NEXT(s_loop_idx))
    {
      if (cmd_find_session_better(s_loop, s, flags))
      {
        s_idx = &s_loop[s_loop_idx];
      }
    }

  }
  return s;
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
static int cmd_find_best_winlink_with_window(struct cmd_find_state *fs)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct winlink *wl_loop;
  unsigned int wl_loop_idx = 0;
  wl_idx = 0;
  if ((fs->s->curw != 0) && (fs->s->curw->window == fs->w))
  {
    wl_idx = fs->s->curw;
  }
  else
  {
    for (wl_loop_idx = winlinks_RB_MINMAX(&fs->s->windows, -1); (&wl_loop[wl_loop_idx]) != 0; wl_loop_idx = winlinks_RB_NEXT(wl_loop_idx))
    {
      if (wl_loop->window == fs->w)
      {
        wl_idx = &wl_loop[wl_loop_idx];
        break;
      }
    }

  }
  if ((&wl[wl_idx]) == 0)
  {
    return -1;
  }
  fs->wl = &wl[wl_idx];
  fs->idx = fs->wl->idx;
  return 0;
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


int cmd_find_from_window(struct cmd_find_state *fs, struct window *w, int flags)
{
  cmd_find_clear_state(fs, flags);
  fs->w = w;
  if (cmd_find_best_session_with_window(fs) != 0)
  {
    cmd_find_clear_state(fs, flags);
    return -1;
  }
  if (cmd_find_best_winlink_with_window(fs) != 0)
  {
    cmd_find_clear_state(fs, flags);
    return -1;
  }
  fs->wp = fs->w->active;
  cmd_find_log_state(__func__, fs);
  return 0;
}


/*** DEPENDENCIES:
static int cmd_find_best_session_with_window(struct cmd_find_state *fs)
{
  struct session **slist = 0;
  unsigned int slist_idx = 0;
  u_int ssize;
  struct session *s;
  unsigned int s_idx = 0;
  ssize = 0;
  for (s_idx = sessions_RB_MINMAX(&sessions, -1); (&s[s_idx]) != 0; s_idx = sessions_RB_NEXT(s_idx))
  {
    if (!session_has(s, fs->w))
    {
      continue;
    }
    slist_idx = xreallocarray(slist_idx, ssize + 1, sizeof(*slist_idx));
    slist[ssize + slist_idx] = &s[s_idx];
    ssize += 1;
  }

  if (ssize == 0)
  {
    goto fail;
  }
  fs->s = cmd_find_best_session(slist, ssize, fs->flags);
  if (fs->s == 0)
  {
    goto fail;
  }
  free(slist);
  return cmd_find_best_winlink_with_window(fs);
  fail:
  free(slist);

  return -1;
}


----------------------------
void cmd_find_log_state(const char *prefix, struct cmd_find_state *fs)
{
  if (fs->s != 0)
  {
    log_debug("%s: s=$%u", prefix, fs->s->id);
  }
  else
    log_debug("%s: s=none", prefix);
  if (fs->wl != 0)
  {
    log_debug("%s: wl=%u %d w=@%u %s", prefix, fs->wl->idx, fs->wl->window == fs->w, fs->w->id, fs->w->name);
  }
  else
    log_debug("%s: wl=none", prefix);
  if (fs->wp != 0)
  {
    log_debug("%s: wp=%%%u", prefix, fs->wp->id);
  }
  else
    log_debug("%s: wp=none", prefix);
  if (fs->idx != (-1))
  {
    log_debug("%s: idx=%d", prefix, fs->idx);
  }
  else
    log_debug("%s: idx=none", prefix);
}


----------------------------
void cmd_find_clear_state(struct cmd_find_state *fs, int flags)
{
  memset(fs, 0, sizeof(*fs));
  fs->flags = flags;
  fs->idx = -1;
}


----------------------------
static int cmd_find_best_winlink_with_window(struct cmd_find_state *fs)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct winlink *wl_loop;
  unsigned int wl_loop_idx = 0;
  wl_idx = 0;
  if ((fs->s->curw != 0) && (fs->s->curw->window == fs->w))
  {
    wl_idx = fs->s->curw;
  }
  else
  {
    for (wl_loop_idx = winlinks_RB_MINMAX(&fs->s->windows, -1); (&wl_loop[wl_loop_idx]) != 0; wl_loop_idx = winlinks_RB_NEXT(wl_loop_idx))
    {
      if (wl_loop->window == fs->w)
      {
        wl_idx = &wl_loop[wl_loop_idx];
        break;
      }
    }

  }
  if ((&wl[wl_idx]) == 0)
  {
    return -1;
  }
  fs->wl = &wl[wl_idx];
  fs->idx = fs->wl->idx;
  return 0;
}


----------------------------
None
----------------------------
***/


int cmd_find_from_pane(struct cmd_find_state *fs, struct window_pane *wp, int flags)
{
  if (cmd_find_from_window(fs, wp->window, flags) != 0)
  {
    return -1;
  }
  fs->wp = wp;
  cmd_find_log_state(__func__, fs);
  return 0;
}


/*** DEPENDENCIES:
void cmd_find_log_state(const char *prefix, struct cmd_find_state *fs)
{
  if (fs->s != 0)
  {
    log_debug("%s: s=$%u", prefix, fs->s->id);
  }
  else
    log_debug("%s: s=none", prefix);
  if (fs->wl != 0)
  {
    log_debug("%s: wl=%u %d w=@%u %s", prefix, fs->wl->idx, fs->wl->window == fs->w, fs->w->id, fs->w->name);
  }
  else
    log_debug("%s: wl=none", prefix);
  if (fs->wp != 0)
  {
    log_debug("%s: wp=%%%u", prefix, fs->wp->id);
  }
  else
    log_debug("%s: wp=none", prefix);
  if (fs->idx != (-1))
  {
    log_debug("%s: idx=%d", prefix, fs->idx);
  }
  else
    log_debug("%s: idx=none", prefix);
}


----------------------------
int cmd_find_from_window(struct cmd_find_state *fs, struct window *w, int flags)
{
  cmd_find_clear_state(fs, flags);
  fs->w = w;
  if (cmd_find_best_session_with_window(fs) != 0)
  {
    cmd_find_clear_state(fs, flags);
    return -1;
  }
  if (cmd_find_best_winlink_with_window(fs) != 0)
  {
    cmd_find_clear_state(fs, flags);
    return -1;
  }
  fs->wp = fs->w->active;
  cmd_find_log_state(__func__, fs);
  return 0;
}


----------------------------
None
----------------------------
***/


static const char *cmd_find_map_table(const char *table[][2], const char *s)
{
  u_int i;
  for (i = 0; table[i][0] != 0; i += 1)
  {
    if (strcmp(s, table[i][0]) == 0)
    {
      return table[i][1];
    }
  }

  return s;
}


/*** DEPENDENCIES:
***/


static int cmd_find_client_better(struct client *c, struct client *than)
{
  if (than == 0)
  {
    return 1;
  }
  return ((&c->activity_time)->tv_sec == (&than->activity_time)->tv_sec) ? ((&c->activity_time)->tv_usec > (&than->activity_time)->tv_usec) : ((&c->activity_time)->tv_sec > (&than->activity_time)->tv_sec);
}


/*** DEPENDENCIES:
None
----------------------------
***/


// hint:  ['session_idx_ref is a mutable refrence to unsigned int', 'window_idx_ref is a mutable refrence to unsigned int', 'pane_idx_ref is a mutable refrence to unsigned int']
void helper_cmd_find_target_1(unsigned int * const session_idx_ref, unsigned int * const window_idx_ref, unsigned int * const pane_idx_ref, enum cmd_find_type type, char * const copy, unsigned int copy_idx)
{
  unsigned int session_idx = *session_idx_ref;
  unsigned int window_idx = *window_idx_ref;
  unsigned int pane_idx = *pane_idx_ref;
  if (copy[copy_idx] == '$')
  {
    session_idx = &copy[copy_idx];
  }
  else
    if (copy[copy_idx] == '@')
  {
    window_idx = &copy[copy_idx];
  }
  else
    if (copy[copy_idx] == '%')
  {
    pane_idx = &copy[copy_idx];
  }
  else
  {
    switch (type)
    {
      case CMD_FIND_SESSION:
      {
        session_idx = &copy[copy_idx];
        break;
      }

      case CMD_FIND_WINDOW:
      {
        window_idx = &copy[copy_idx];
        break;
      }

      case CMD_FIND_PANE:
      {
        pane_idx = &copy[copy_idx];
        break;
      }

    }

  }
  *session_idx_ref = session_idx;
  *window_idx_ref = window_idx;
  *pane_idx_ref = pane_idx;
}


/*** DEPENDENCIES:
enum cmd_find_type
{
  CMD_FIND_PANE,
  CMD_FIND_WINDOW,
  CMD_FIND_SESSION
}
----------------------------
None
----------------------------
***/


void cmd_find_from_winlink(struct cmd_find_state *fs, struct winlink *wl, int flags)
{
  cmd_find_clear_state(fs, flags);
  fs->s = wl->session;
  fs->wl = wl;
  fs->w = wl->window;
  fs->wp = wl->window->active;
  cmd_find_log_state(__func__, fs);
}


/*** DEPENDENCIES:
void cmd_find_log_state(const char *prefix, struct cmd_find_state *fs)
{
  if (fs->s != 0)
  {
    log_debug("%s: s=$%u", prefix, fs->s->id);
  }
  else
    log_debug("%s: s=none", prefix);
  if (fs->wl != 0)
  {
    log_debug("%s: wl=%u %d w=@%u %s", prefix, fs->wl->idx, fs->wl->window == fs->w, fs->w->id, fs->w->name);
  }
  else
    log_debug("%s: wl=none", prefix);
  if (fs->wp != 0)
  {
    log_debug("%s: wp=%%%u", prefix, fs->wp->id);
  }
  else
    log_debug("%s: wp=none", prefix);
  if (fs->idx != (-1))
  {
    log_debug("%s: idx=%d", prefix, fs->idx);
  }
  else
    log_debug("%s: idx=none", prefix);
}


----------------------------
void cmd_find_clear_state(struct cmd_find_state *fs, int flags)
{
  memset(fs, 0, sizeof(*fs));
  fs->flags = flags;
  fs->idx = -1;
}


----------------------------
None
----------------------------
***/


static struct session *cmd_find_try_TMUX(struct client *c)
{
  struct environ_entry *envent;
  unsigned int envent_idx = 0;
  char tmp[256];
  long long pid;
  u_int session;
  envent_idx = environ_find(c->environ, "TMUX");
  if ((&envent[envent_idx]) == 0)
  {
    return 0;
  }
  if (sscanf(envent->value, "%255[^,],%lld,%d", tmp, &pid, &session) != 3)
  {
    return 0;
  }
  if (pid != getpid())
  {
    return 0;
  }
  log_debug("client %p TMUX %s (session @%u)", c, envent->value, session);
  return session_find_by_id(session);
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
struct environ_entry *environ_find(struct environ *env, const char *name)
{
  struct environ_entry envent;
  envent.name = (char *) name;
  return environ_RB_FIND(env, &envent);
}


----------------------------
None
----------------------------
***/


static struct window_pane *cmd_find_inside_pane(struct client *c)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  if (c == 0)
  {
    return 0;
  }
  for (wp_idx = window_pane_tree_RB_MINMAX(&all_window_panes, -1); (&wp[wp_idx]) != 0; wp_idx = window_pane_tree_RB_NEXT(wp_idx))
  {
    if (strcmp(wp->tty, c->ttyname) == 0)
    {
      break;
    }
  }

  return wp;
}


/*** DEPENDENCIES:
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


----------------------------
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


----------------------------
extern struct window_pane_tree all_window_panes
----------------------------
None
----------------------------
***/


void cmd_find_from_session(struct cmd_find_state *fs, struct session *s, int flags)
{
  cmd_find_clear_state(fs, flags);
  fs->s = s;
  fs->wl = fs->s->curw;
  fs->w = fs->wl->window;
  fs->wp = fs->w->active;
  cmd_find_log_state(__func__, fs);
}


/*** DEPENDENCIES:
void cmd_find_log_state(const char *prefix, struct cmd_find_state *fs)
{
  if (fs->s != 0)
  {
    log_debug("%s: s=$%u", prefix, fs->s->id);
  }
  else
    log_debug("%s: s=none", prefix);
  if (fs->wl != 0)
  {
    log_debug("%s: wl=%u %d w=@%u %s", prefix, fs->wl->idx, fs->wl->window == fs->w, fs->w->id, fs->w->name);
  }
  else
    log_debug("%s: wl=none", prefix);
  if (fs->wp != 0)
  {
    log_debug("%s: wp=%%%u", prefix, fs->wp->id);
  }
  else
    log_debug("%s: wp=none", prefix);
  if (fs->idx != (-1))
  {
    log_debug("%s: idx=%d", prefix, fs->idx);
  }
  else
    log_debug("%s: idx=none", prefix);
}


----------------------------
void cmd_find_clear_state(struct cmd_find_state *fs, int flags)
{
  memset(fs, 0, sizeof(*fs));
  fs->flags = flags;
  fs->idx = -1;
}


----------------------------
None
----------------------------
***/


int cmd_find_from_client(struct cmd_find_state *fs, struct client *c, int flags)
{
  struct session *s;
  unsigned int s_idx = 0;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  if (c == 0)
  {
    return cmd_find_from_nothing(fs, flags);
  }
  if (c->session != 0)
  {
    cmd_find_from_session(fs, c->session, flags);
    return 0;
  }
  cmd_find_clear_state(fs, flags);
  wp_idx = cmd_find_inside_pane(c);
  if ((&wp[wp_idx]) == 0)
  {
    goto unknown_pane;
  }
  s_idx = cmd_find_try_TMUX(c);
  if ((&s[s_idx]) != 0)
  {
    for (wl_idx = winlinks_RB_MINMAX(&s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
    {
      if (window_has_pane(wl->window, wp))
      {
        break;
      }
    }

    if ((&wl[wl_idx]) != 0)
    {
      fs->s = &s[s_idx];
      fs->wl = s->curw;
      fs->w = fs->wl->window;
      fs->wp = fs->w->active;
      cmd_find_log_state(__func__, fs);
      return 0;
    }
  }
  fs->w = wp->window;
  if (cmd_find_best_session_with_window(fs) != 0)
  {
    goto unknown_pane;
  }
  fs->wl = fs->s->curw;
  fs->w = fs->wl->window;
  fs->wp = fs->w->active;
  cmd_find_log_state(__func__, fs);
  return 0;
  unknown_pane:
  s_idx = cmd_find_try_TMUX(c);

  if ((&s[s_idx]) != 0)
  {
    cmd_find_from_session(fs, s, flags);
    return 0;
  }
  return cmd_find_from_nothing(fs, flags);
}


/*** DEPENDENCIES:
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


----------------------------
struct windows
{
  struct window *rbh_root;
}
----------------------------
int cmd_find_from_nothing(struct cmd_find_state *fs, int flags)
{
  cmd_find_clear_state(fs, flags);
  fs->s = cmd_find_best_session(0, 0, flags);
  if (fs->s == 0)
  {
    cmd_find_clear_state(fs, flags);
    return -1;
  }
  fs->wl = fs->s->curw;
  fs->idx = fs->wl->idx;
  fs->w = fs->wl->window;
  fs->wp = fs->w->active;
  cmd_find_log_state(__func__, fs);
  return 0;
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
void cmd_find_clear_state(struct cmd_find_state *fs, int flags)
{
  memset(fs, 0, sizeof(*fs));
  fs->flags = flags;
  fs->idx = -1;
}


----------------------------
static struct session *cmd_find_try_TMUX(struct client *c)
{
  struct environ_entry *envent;
  unsigned int envent_idx = 0;
  char tmp[256];
  long long pid;
  u_int session;
  envent_idx = environ_find(c->environ, "TMUX");
  if ((&envent[envent_idx]) == 0)
  {
    return 0;
  }
  if (sscanf(envent->value, "%255[^,],%lld,%d", tmp, &pid, &session) != 3)
  {
    return 0;
  }
  if (pid != getpid())
  {
    return 0;
  }
  log_debug("client %p TMUX %s (session @%u)", c, envent->value, session);
  return session_find_by_id(session);
}


----------------------------
static struct window_pane *cmd_find_inside_pane(struct client *c)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  if (c == 0)
  {
    return 0;
  }
  for (wp_idx = window_pane_tree_RB_MINMAX(&all_window_panes, -1); (&wp[wp_idx]) != 0; wp_idx = window_pane_tree_RB_NEXT(wp_idx))
  {
    if (strcmp(wp->tty, c->ttyname) == 0)
    {
      break;
    }
  }

  return wp;
}


----------------------------
void cmd_find_log_state(const char *prefix, struct cmd_find_state *fs)
{
  if (fs->s != 0)
  {
    log_debug("%s: s=$%u", prefix, fs->s->id);
  }
  else
    log_debug("%s: s=none", prefix);
  if (fs->wl != 0)
  {
    log_debug("%s: wl=%u %d w=@%u %s", prefix, fs->wl->idx, fs->wl->window == fs->w, fs->w->id, fs->w->name);
  }
  else
    log_debug("%s: wl=none", prefix);
  if (fs->wp != 0)
  {
    log_debug("%s: wp=%%%u", prefix, fs->wp->id);
  }
  else
    log_debug("%s: wp=none", prefix);
  if (fs->idx != (-1))
  {
    log_debug("%s: idx=%d", prefix, fs->idx);
  }
  else
    log_debug("%s: idx=none", prefix);
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
static int cmd_find_best_session_with_window(struct cmd_find_state *fs)
{
  struct session **slist = 0;
  unsigned int slist_idx = 0;
  u_int ssize;
  struct session *s;
  unsigned int s_idx = 0;
  ssize = 0;
  for (s_idx = sessions_RB_MINMAX(&sessions, -1); (&s[s_idx]) != 0; s_idx = sessions_RB_NEXT(s_idx))
  {
    if (!session_has(s, fs->w))
    {
      continue;
    }
    slist_idx = xreallocarray(slist_idx, ssize + 1, sizeof(*slist_idx));
    slist[ssize + slist_idx] = &s[s_idx];
    ssize += 1;
  }

  if (ssize == 0)
  {
    goto fail;
  }
  fs->s = cmd_find_best_session(slist, ssize, fs->flags);
  if (fs->s == 0)
  {
    goto fail;
  }
  free(slist);
  return cmd_find_best_winlink_with_window(fs);
  fail:
  free(slist);

  return -1;
}


----------------------------
void cmd_find_from_session(struct cmd_find_state *fs, struct session *s, int flags)
{
  cmd_find_clear_state(fs, flags);
  fs->s = s;
  fs->wl = fs->s->curw;
  fs->w = fs->wl->window;
  fs->wp = fs->w->active;
  cmd_find_log_state(__func__, fs);
}


----------------------------
None
----------------------------
***/


static int cmd_find_get_pane_with_window(struct cmd_find_state *fs, const char *pane)
{
  const char *errstr;
  int idx;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int n;
  log_debug("%s: %s", __func__, pane);
  if ((*pane) == '%')
  {
    fs->wp = window_pane_find_by_id_str(pane);
    if (fs->wp == 0)
    {
      return -1;
    }
    if (fs->wp->window != fs->w)
    {
      return -1;
    }
    return 0;
  }
  if (strcmp(pane, "!") == 0)
  {
    fs->wp = fs->w->last;
    if (fs->wp == 0)
    {
      return -1;
    }
    return 0;
  }
  else
    if (strcmp(pane, "{up-of}") == 0)
  {
    fs->wp = window_pane_find_up(fs->w->active);
    if (fs->wp == 0)
    {
      return -1;
    }
    return 0;
  }
  else
    if (strcmp(pane, "{down-of}") == 0)
  {
    fs->wp = window_pane_find_down(fs->w->active);
    if (fs->wp == 0)
    {
      return -1;
    }
    return 0;
  }
  else
    if (strcmp(pane, "{left-of}") == 0)
  {
    fs->wp = window_pane_find_left(fs->w->active);
    if (fs->wp == 0)
    {
      return -1;
    }
    return 0;
  }
  else
    if (strcmp(pane, "{right-of}") == 0)
  {
    fs->wp = window_pane_find_right(fs->w->active);
    if (fs->wp == 0)
    {
      return -1;
    }
    return 0;
  }
  if ((pane[0] == '+') || (pane[0] == '-'))
  {
    if (pane[1] != '\0')
    {
      n = strtonum(pane + 1, 1, 2147483647, 0);
    }
    else
      n = 1;
    wp_idx = fs->w->active;
    if (pane[0] == '+')
    {
      fs->wp = window_pane_next_by_number(fs->w, wp, n);
    }
    else
      fs->wp = window_pane_previous_by_number(fs->w, wp, n);
    if (fs->wp != 0)
    {
      return 0;
    }
  }
  idx = strtonum(pane, 0, 2147483647, &errstr);
  if (errstr == 0)
  {
    fs->wp = window_pane_at_index(fs->w, idx);
    if (fs->wp != 0)
    {
      return 0;
    }
  }
  fs->wp = window_find_string(fs->w, pane);
  if (fs->wp != 0)
  {
    return 0;
  }
  return -1;
}


/*** DEPENDENCIES:
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


----------------------------
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


----------------------------
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


----------------------------
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


----------------------------
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


----------------------------
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


----------------------------
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


----------------------------
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
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


----------------------------
None
----------------------------
***/


// hint:  ['m_idx_ref is a mutable refrence to unsigned int']
void helper_cmd_find_target_2(unsigned int * const m_idx_ref, struct cmd_find_state * const fs, struct cmdq_item * const item, enum cmd_find_type type, int flags, struct mouse_event * const m)
{
  unsigned int m_idx = *m_idx_ref;
  m_idx = &item->shared->mouse;
  switch (type)
  {
    case CMD_FIND_PANE:
    {
      fs->wp = cmd_mouse_pane(m, &fs->s, &fs->wl);
      if (fs->wp != 0)
      {
        fs->w = fs->wl->window;
      }
      break;
    }

    case CMD_FIND_WINDOW:

    case CMD_FIND_SESSION:
    {
      fs->wl = cmd_mouse_window(m, &fs->s);
      if (fs->wl != 0)
      {
        fs->w = fs->wl->window;
        fs->wp = fs->w->active;
      }
      break;
    }

  }

  if (fs->wp == 0)
  {
    if ((~flags) & 0x2)
    {
      cmdq_error(item, "no mouse target");
    }
    goto error;
  }
  goto found;
  *m_idx_ref = m_idx;
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
enum cmd_find_type
{
  CMD_FIND_PANE,
  CMD_FIND_WINDOW,
  CMD_FIND_SESSION
}
----------------------------
struct winlink *cmd_mouse_window(struct mouse_event *m, struct session **sp)
{
  struct session *s;
  unsigned int s_idx = 0;
  struct window *w;
  unsigned int w_idx = 0;
  if (((!m->valid) || (m->s == (-1))) || (m->w == (-1)))
  {
    return 0;
  }
  if ((s_idx = session_find_by_id(m->s_idx)) == 0)
  {
    return 0;
  }
  if ((w_idx = window_find_by_id(m->w_idx)) == 0)
  {
    return 0;
  }
  if (sp != 0)
  {
    *sp = &s[s_idx];
  }
  return winlink_find_by_window(&s->windows, w);
}


----------------------------
struct window_pane *cmd_mouse_pane(struct mouse_event *m, struct session **sp, struct winlink **wlp)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  if ((wl_idx = cmd_mouse_window(m, sp)) == 0)
  {
    return 0;
  }
  if ((wp_idx = window_pane_find_by_id(m->wp_idx)) == 0)
  {
    return 0;
  }
  if (!window_has_pane(wl->window, wp))
  {
    return 0;
  }
  if (wlp != 0)
  {
    *wlp = &wl[wl_idx];
  }
  return wp;
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


int helper_cmd_find_get_window_with_session_2(struct cmd_find_state * const fs, const char * const window)
{
  if (strcmp(window, "!") == 0)
  {
    fs->wl = (&fs->s->lastw)->tqh_first;
    if (fs->wl == 0)
    {
      return -1;
    }
    fs->idx = fs->wl->idx;
    fs->w = fs->wl->window;
    return 0;
  }
  else
    if (strcmp(window, "^") == 0)
  {
    fs->wl = winlinks_RB_MINMAX(&fs->s->windows, -1);
    if (fs->wl == 0)
    {
      return -1;
    }
    fs->idx = fs->wl->idx;
    fs->w = fs->wl->window;
    return 0;
  }
  else
    if (strcmp(window, "$") == 0)
  {
    fs->wl = winlinks_RB_MINMAX(&fs->s->windows, 1);
    if (fs->wl == 0)
    {
      return -1;
    }
    fs->idx = fs->wl->idx;
    fs->w = fs->wl->window;
    return 0;
  }
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
None
----------------------------
***/


// hint:  ['n_ref is a mutable refrence to int', 's_idx_ref is a mutable refrence to unsigned int']
int helper_cmd_find_get_window_with_session_1(int * const n_ref, unsigned int * const s_idx_ref, struct cmd_find_state * const fs, const char * const window, struct session * const s)
{
  int n = *n_ref;
  unsigned int s_idx = *s_idx_ref;
  if (window[1] != '\0')
  {
    n = strtonum(window + 1, 1, 2147483647, 0);
  }
  else
    n = 1;
  s_idx = fs->s_idx;
  if (fs->flags & 0x4)
  {
    if (window[0] == '+')
    {
      if ((2147483647 - s->curw->idx) < n)
      {
        return -1;
      }
      fs->idx = s->curw->idx + n;
    }
    else
    {
      if (n > s->curw->idx)
      {
        return -1;
      }
      fs->idx = s->curw->idx - n;
    }
    return 0;
  }
  if (window[0] == '+')
  {
    fs->wl = winlink_next_by_number(s->curw, s, n);
  }
  else
    fs->wl = winlink_previous_by_number(s->curw, s, n);
  if (fs->wl != 0)
  {
    fs->idx = fs->wl->idx;
    fs->w = fs->wl->window;
    return 0;
  }
  *n_ref = n;
  *s_idx_ref = s_idx;
}


/*** DEPENDENCIES:
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


----------------------------
None
----------------------------
***/


static int cmd_find_get_window_with_session(struct cmd_find_state *fs, const char *window)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  const char *errstr;
  int idx;
  int n;
  int exact;
  struct session *s;
  unsigned int s_idx = 0;
  log_debug("%s: %s", __func__, window);
  exact = fs->flags & 0x20;
  fs->wl = fs->s->curw;
  fs->w = fs->wl->window;
  if ((*window) == '@')
  {
    fs->w = window_find_by_id_str(window);
    if ((fs->w == 0) || (!session_has(fs->s, fs->w)))
    {
      return -1;
    }
    return cmd_find_best_winlink_with_window(fs);
  }
  if ((!exact) && ((window[0] == '+') || (window[0] == '-')))
  {
    helper_cmd_find_get_window_with_session_1(&n, &s_idx, fs, window, s);
  }
  if (!exact)
  {
    helper_cmd_find_get_window_with_session_2(fs, window);
  }
  if ((window[0] != '+') && (window[0] != '-'))
  {
    idx = strtonum(window, 0, 2147483647, &errstr);
    if (errstr == 0)
    {
      if (fs->flags & 0x4)
      {
        fs->idx = idx;
        return 0;
      }
      fs->wl = winlink_find_by_index(&fs->s->windows, idx);
      if (fs->wl != 0)
      {
        fs->w = fs->wl->window;
        return 0;
      }
    }
  }
  fs->wl = 0;
  for (wl_idx = winlinks_RB_MINMAX(&fs->s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    if (strcmp(window, wl->window->name) == 0)
    {
      if (fs->wl != 0)
      {
        return -1;
      }
      fs->wl = &wl[wl_idx];
    }
  }

  if (fs->wl != 0)
  {
    fs->idx = fs->wl->idx;
    fs->w = fs->wl->window;
    return 0;
  }
  if (exact)
  {
    return -1;
  }
  fs->wl = 0;
  for (wl_idx = winlinks_RB_MINMAX(&fs->s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    if (strncmp(window, wl->window->name, strlen(window)) == 0)
    {
      if (fs->wl != 0)
      {
        return -1;
      }
      fs->wl = &wl[wl_idx];
    }
  }

  if (fs->wl != 0)
  {
    fs->idx = fs->wl->idx;
    fs->w = fs->wl->window;
    return 0;
  }
  fs->wl = 0;
  for (wl_idx = winlinks_RB_MINMAX(&fs->s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    if (fnmatch(window, wl->window->name, 0) == 0)
    {
      if (fs->wl != 0)
      {
        return -1;
      }
      fs->wl = &wl[wl_idx];
    }
  }

  if (fs->wl != 0)
  {
    fs->idx = fs->wl->idx;
    fs->w = fs->wl->window;
    return 0;
  }
  return -1;
}


/*** DEPENDENCIES:
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
int helper_cmd_find_get_window_with_session_2(struct cmd_find_state * const fs, const char * const window)
{
  if (strcmp(window, "!") == 0)
  {
    fs->wl = (&fs->s->lastw)->tqh_first;
    if (fs->wl == 0)
    {
      return -1;
    }
    fs->idx = fs->wl->idx;
    fs->w = fs->wl->window;
    return 0;
  }
  else
    if (strcmp(window, "^") == 0)
  {
    fs->wl = winlinks_RB_MINMAX(&fs->s->windows, -1);
    if (fs->wl == 0)
    {
      return -1;
    }
    fs->idx = fs->wl->idx;
    fs->w = fs->wl->window;
    return 0;
  }
  else
    if (strcmp(window, "$") == 0)
  {
    fs->wl = winlinks_RB_MINMAX(&fs->s->windows, 1);
    if (fs->wl == 0)
    {
      return -1;
    }
    fs->idx = fs->wl->idx;
    fs->w = fs->wl->window;
    return 0;
  }
}


----------------------------
int helper_cmd_find_get_window_with_session_1(int * const n_ref, unsigned int * const s_idx_ref, struct cmd_find_state * const fs, const char * const window, struct session * const s)
{
  int n = *n_ref;
  unsigned int s_idx = *s_idx_ref;
  if (window[1] != '\0')
  {
    n = strtonum(window + 1, 1, 2147483647, 0);
  }
  else
    n = 1;
  s_idx = fs->s_idx;
  if (fs->flags & 0x4)
  {
    if (window[0] == '+')
    {
      if ((2147483647 - s->curw->idx) < n)
      {
        return -1;
      }
      fs->idx = s->curw->idx + n;
    }
    else
    {
      if (n > s->curw->idx)
      {
        return -1;
      }
      fs->idx = s->curw->idx - n;
    }
    return 0;
  }
  if (window[0] == '+')
  {
    fs->wl = winlink_next_by_number(s->curw, s, n);
  }
  else
    fs->wl = winlink_previous_by_number(s->curw, s, n);
  if (fs->wl != 0)
  {
    fs->idx = fs->wl->idx;
    fs->w = fs->wl->window;
    return 0;
  }
  *n_ref = n;
  *s_idx_ref = s_idx;
}


----------------------------
static int cmd_find_best_winlink_with_window(struct cmd_find_state *fs)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct winlink *wl_loop;
  unsigned int wl_loop_idx = 0;
  wl_idx = 0;
  if ((fs->s->curw != 0) && (fs->s->curw->window == fs->w))
  {
    wl_idx = fs->s->curw;
  }
  else
  {
    for (wl_loop_idx = winlinks_RB_MINMAX(&fs->s->windows, -1); (&wl_loop[wl_loop_idx]) != 0; wl_loop_idx = winlinks_RB_NEXT(wl_loop_idx))
    {
      if (wl_loop->window == fs->w)
      {
        wl_idx = &wl_loop[wl_loop_idx];
        break;
      }
    }

  }
  if ((&wl[wl_idx]) == 0)
  {
    return -1;
  }
  fs->wl = &wl[wl_idx];
  fs->idx = fs->wl->idx;
  return 0;
}


----------------------------
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


struct client *cmd_find_best_client(struct session *s)
{
  unsigned int s_idx = 0;
  struct client *c_loop;
  unsigned int c_loop_idx = 0;
  struct client *c;
  unsigned int c_idx = 0;
  if (s->flags & 0x1)
  {
    s_idx = 0;
  }
  c_idx = 0;
  for (c_loop_idx = (&clients)->tqh_first; (&c_loop[c_loop_idx]) != 0; c_loop_idx = c_loop_idx->entry.tqe_next)
  {
    if (c_loop->session == 0)
    {
      continue;
    }
    if (((&s[s_idx]) != 0) && (c_loop->session != (&s[s_idx])))
    {
      continue;
    }
    if (cmd_find_client_better(c_loop, c))
    {
      c_idx = &c_loop[c_loop_idx];
    }
  }

  return c;
}


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
}
----------------------------
static int cmd_find_client_better(struct client *c, struct client *than)
{
  if (than == 0)
  {
    return 1;
  }
  return ((&c->activity_time)->tv_sec == (&than->activity_time)->tv_sec) ? ((&c->activity_time)->tv_usec > (&than->activity_time)->tv_usec) : ((&c->activity_time)->tv_sec > (&than->activity_time)->tv_sec);
}


----------------------------
None
----------------------------
***/


static struct client *cmd_find_current_client(struct cmdq_item *item, int quiet)
{
  struct client *c;
  unsigned int c_idx = 0;
  struct session *s;
  unsigned int s_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  struct cmd_find_state fs;
  if ((item->client != 0) && (item->client->session != 0))
  {
    return item->client;
  }
  c_idx = 0;
  if ((wp_idx = cmd_find_inside_pane(item->client)) != 0)
  {
    cmd_find_clear_state(&fs, 0x2);
    fs.w = wp->window;
    if (cmd_find_best_session_with_window(&fs) == 0)
    {
      c_idx = cmd_find_best_client(fs.s);
    }
  }
  else
  {
    s_idx = cmd_find_best_session(0, 0, 0x2);
    if ((&s[s_idx]) != 0)
    {
      c_idx = cmd_find_best_client(s);
    }
  }
  if (((&c[c_idx]) == 0) && (!quiet))
  {
    cmdq_error(item, "no current client");
  }
  log_debug("%s: no target, return %p", __func__, c);
  return c;
}


/*** DEPENDENCIES:
void cmd_find_clear_state(struct cmd_find_state *fs, int flags)
{
  memset(fs, 0, sizeof(*fs));
  fs->flags = flags;
  fs->idx = -1;
}


----------------------------
static struct window_pane *cmd_find_inside_pane(struct client *c)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  if (c == 0)
  {
    return 0;
  }
  for (wp_idx = window_pane_tree_RB_MINMAX(&all_window_panes, -1); (&wp[wp_idx]) != 0; wp_idx = window_pane_tree_RB_NEXT(wp_idx))
  {
    if (strcmp(wp->tty, c->ttyname) == 0)
    {
      break;
    }
  }

  return wp;
}


----------------------------
struct client *cmd_find_best_client(struct session *s)
{
  unsigned int s_idx = 0;
  struct client *c_loop;
  unsigned int c_loop_idx = 0;
  struct client *c;
  unsigned int c_idx = 0;
  if (s->flags & 0x1)
  {
    s_idx = 0;
  }
  c_idx = 0;
  for (c_loop_idx = (&clients)->tqh_first; (&c_loop[c_loop_idx]) != 0; c_loop_idx = c_loop_idx->entry.tqe_next)
  {
    if (c_loop->session == 0)
    {
      continue;
    }
    if (((&s[s_idx]) != 0) && (c_loop->session != (&s[s_idx])))
    {
      continue;
    }
    if (cmd_find_client_better(c_loop, c))
    {
      c_idx = &c_loop[c_loop_idx];
    }
  }

  return c;
}


----------------------------
static struct session *cmd_find_best_session(struct session **slist, u_int ssize, int flags)
{
  struct session *s_loop;
  unsigned int s_loop_idx = 0;
  struct session *s;
  unsigned int s_idx = 0;
  u_int i;
  s_idx = 0;
  if (slist != 0)
  {
    for (i = 0; i < ssize; i += 1)
    {
      if (cmd_find_session_better(slist[i], s, flags))
      {
        s_idx = slist[i];
      }
    }

  }
  else
  {
    for (s_loop_idx = sessions_RB_MINMAX(&sessions, -1); (&s_loop[s_loop_idx]) != 0; s_loop_idx = sessions_RB_NEXT(s_loop_idx))
    {
      if (cmd_find_session_better(s_loop, s, flags))
      {
        s_idx = &s_loop[s_loop_idx];
      }
    }

  }
  return s;
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
static int cmd_find_best_session_with_window(struct cmd_find_state *fs)
{
  struct session **slist = 0;
  unsigned int slist_idx = 0;
  u_int ssize;
  struct session *s;
  unsigned int s_idx = 0;
  ssize = 0;
  for (s_idx = sessions_RB_MINMAX(&sessions, -1); (&s[s_idx]) != 0; s_idx = sessions_RB_NEXT(s_idx))
  {
    if (!session_has(s, fs->w))
    {
      continue;
    }
    slist_idx = xreallocarray(slist_idx, ssize + 1, sizeof(*slist_idx));
    slist[ssize + slist_idx] = &s[s_idx];
    ssize += 1;
  }

  if (ssize == 0)
  {
    goto fail;
  }
  fs->s = cmd_find_best_session(slist, ssize, fs->flags);
  if (fs->s == 0)
  {
    goto fail;
  }
  free(slist);
  return cmd_find_best_winlink_with_window(fs);
  fail:
  free(slist);

  return -1;
}


----------------------------
None
----------------------------
***/


struct client *cmd_find_client(struct cmdq_item *item, const char *target, int quiet)
{
  struct client *c;
  unsigned int c_idx = 0;
  char *copy;
  unsigned int copy_idx = 0;
  size_t size;
  if (target == 0)
  {
    return cmd_find_current_client(item, quiet);
  }
  copy_idx = xstrdup(target);
  size = strlen(copy);
  if ((size != 0) && (copy[(size - 1) + copy_idx] == ':'))
  {
    copy[(size - 1) + copy_idx] = '\0';
  }
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (c->session == 0)
    {
      continue;
    }
    if (strcmp(copy, c->name) == 0)
    {
      break;
    }
    if ((*c->ttyname) == '\0')
    {
      continue;
    }
    if (strcmp(copy, c->ttyname) == 0)
    {
      break;
    }
    if (strncmp(c->ttyname, "/dev/", (sizeof("/dev/")) - 1) != 0)
    {
      continue;
    }
    if (strcmp(copy, (c->ttyname + (sizeof("/dev/"))) - 1) == 0)
    {
      break;
    }
  }

  if (((&c[c_idx]) == 0) && (!quiet))
  {
    cmdq_error(item, "can't find client %s", copy);
  }
  free(copy);
  log_debug("%s: target %s, return %p", __func__, target, c);
  return c;
}


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
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
static struct client *cmd_find_current_client(struct cmdq_item *item, int quiet)
{
  struct client *c;
  unsigned int c_idx = 0;
  struct session *s;
  unsigned int s_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  struct cmd_find_state fs;
  if ((item->client != 0) && (item->client->session != 0))
  {
    return item->client;
  }
  c_idx = 0;
  if ((wp_idx = cmd_find_inside_pane(item->client)) != 0)
  {
    cmd_find_clear_state(&fs, 0x2);
    fs.w = wp->window;
    if (cmd_find_best_session_with_window(&fs) == 0)
    {
      c_idx = cmd_find_best_client(fs.s);
    }
  }
  else
  {
    s_idx = cmd_find_best_session(0, 0, 0x2);
    if ((&s[s_idx]) != 0)
    {
      c_idx = cmd_find_best_client(s);
    }
  }
  if (((&c[c_idx]) == 0) && (!quiet))
  {
    cmdq_error(item, "no current client");
  }
  log_debug("%s: no target, return %p", __func__, c);
  return c;
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


static int cmd_find_get_session(struct cmd_find_state *fs, const char *session)
{
  struct session *s;
  unsigned int s_idx = 0;
  struct session *s_loop;
  unsigned int s_loop_idx = 0;
  struct client *c;
  unsigned int c_idx = 0;
  log_debug("%s: %s", __func__, session);
  if ((*session) == '$')
  {
    fs->s = session_find_by_id_str(session);
    if (fs->s == 0)
    {
      return -1;
    }
    return 0;
  }
  fs->s = session_find(session);
  if (fs->s != 0)
  {
    return 0;
  }
  c_idx = cmd_find_client(0, session, 1);
  if (((&c[c_idx]) != 0) && (c->session != 0))
  {
    fs->s = c->session;
    return 0;
  }
  if (fs->flags & 0x10)
  {
    return -1;
  }
  s_idx = 0;
  for (s_loop_idx = sessions_RB_MINMAX(&sessions, -1); (&s_loop[s_loop_idx]) != 0; s_loop_idx = sessions_RB_NEXT(s_loop_idx))
  {
    if (strncmp(session, s_loop->name, strlen(session)) == 0)
    {
      if ((&s[s_idx]) != 0)
      {
        return -1;
      }
      s_idx = &s_loop[s_loop_idx];
    }
  }

  if ((&s[s_idx]) != 0)
  {
    fs->s = &s[s_idx];
    return 0;
  }
  s_idx = 0;
  for (s_loop_idx = sessions_RB_MINMAX(&sessions, -1); (&s_loop[s_loop_idx]) != 0; s_loop_idx = sessions_RB_NEXT(s_loop_idx))
  {
    if (fnmatch(session, s_loop->name, 0) == 0)
    {
      if ((&s[s_idx]) != 0)
      {
        return -1;
      }
      s_idx = &s_loop[s_loop_idx];
    }
  }

  if ((&s[s_idx]) != 0)
  {
    fs->s = &s[s_idx];
    return 0;
  }
  return -1;
}


/*** DEPENDENCIES:
struct session *session_find(const char *name)
{
  struct session s;
  s.name = (char *) name;
  return sessions_RB_FIND(&sessions, &s);
}


----------------------------
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
struct sessions
{
  struct session *rbh_root;
}
----------------------------
struct client *cmd_find_client(struct cmdq_item *item, const char *target, int quiet)
{
  struct client *c;
  unsigned int c_idx = 0;
  char *copy;
  unsigned int copy_idx = 0;
  size_t size;
  if (target == 0)
  {
    return cmd_find_current_client(item, quiet);
  }
  copy_idx = xstrdup(target);
  size = strlen(copy);
  if ((size != 0) && (copy[(size - 1) + copy_idx] == ':'))
  {
    copy[(size - 1) + copy_idx] = '\0';
  }
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (c->session == 0)
    {
      continue;
    }
    if (strcmp(copy, c->name) == 0)
    {
      break;
    }
    if ((*c->ttyname) == '\0')
    {
      continue;
    }
    if (strcmp(copy, c->ttyname) == 0)
    {
      break;
    }
    if (strncmp(c->ttyname, "/dev/", (sizeof("/dev/")) - 1) != 0)
    {
      continue;
    }
    if (strcmp(copy, (c->ttyname + (sizeof("/dev/"))) - 1) == 0)
    {
      break;
    }
  }

  if (((&c[c_idx]) == 0) && (!quiet))
  {
    cmdq_error(item, "can't find client %s", copy);
  }
  free(copy);
  log_debug("%s: target %s, return %p", __func__, target, c);
  return c;
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


static int cmd_find_get_window(struct cmd_find_state *fs, const char *window, int only)
{
  log_debug("%s: %s", __func__, window);
  if ((*window) == '@')
  {
    fs->w = window_find_by_id_str(window);
    if (fs->w == 0)
    {
      return -1;
    }
    return cmd_find_best_session_with_window(fs);
  }
  fs->s = fs->current->s;
  if (cmd_find_get_window_with_session(fs, window) == 0)
  {
    return 0;
  }
  if ((!only) && (cmd_find_get_session(fs, window) == 0))
  {
    fs->wl = fs->s->curw;
    fs->w = fs->wl->window;
    if ((~fs->flags) & 0x4)
    {
      fs->idx = fs->wl->idx;
    }
    return 0;
  }
  return -1;
}


/*** DEPENDENCIES:
static int cmd_find_get_window_with_session(struct cmd_find_state *fs, const char *window)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  const char *errstr;
  int idx;
  int n;
  int exact;
  struct session *s;
  unsigned int s_idx = 0;
  log_debug("%s: %s", __func__, window);
  exact = fs->flags & 0x20;
  fs->wl = fs->s->curw;
  fs->w = fs->wl->window;
  if ((*window) == '@')
  {
    fs->w = window_find_by_id_str(window);
    if ((fs->w == 0) || (!session_has(fs->s, fs->w)))
    {
      return -1;
    }
    return cmd_find_best_winlink_with_window(fs);
  }
  if ((!exact) && ((window[0] == '+') || (window[0] == '-')))
  {
    helper_cmd_find_get_window_with_session_1(&n, &s_idx, fs, window, s);
  }
  if (!exact)
  {
    helper_cmd_find_get_window_with_session_2(fs, window);
  }
  if ((window[0] != '+') && (window[0] != '-'))
  {
    idx = strtonum(window, 0, 2147483647, &errstr);
    if (errstr == 0)
    {
      if (fs->flags & 0x4)
      {
        fs->idx = idx;
        return 0;
      }
      fs->wl = winlink_find_by_index(&fs->s->windows, idx);
      if (fs->wl != 0)
      {
        fs->w = fs->wl->window;
        return 0;
      }
    }
  }
  fs->wl = 0;
  for (wl_idx = winlinks_RB_MINMAX(&fs->s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    if (strcmp(window, wl->window->name) == 0)
    {
      if (fs->wl != 0)
      {
        return -1;
      }
      fs->wl = &wl[wl_idx];
    }
  }

  if (fs->wl != 0)
  {
    fs->idx = fs->wl->idx;
    fs->w = fs->wl->window;
    return 0;
  }
  if (exact)
  {
    return -1;
  }
  fs->wl = 0;
  for (wl_idx = winlinks_RB_MINMAX(&fs->s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    if (strncmp(window, wl->window->name, strlen(window)) == 0)
    {
      if (fs->wl != 0)
      {
        return -1;
      }
      fs->wl = &wl[wl_idx];
    }
  }

  if (fs->wl != 0)
  {
    fs->idx = fs->wl->idx;
    fs->w = fs->wl->window;
    return 0;
  }
  fs->wl = 0;
  for (wl_idx = winlinks_RB_MINMAX(&fs->s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    if (fnmatch(window, wl->window->name, 0) == 0)
    {
      if (fs->wl != 0)
      {
        return -1;
      }
      fs->wl = &wl[wl_idx];
    }
  }

  if (fs->wl != 0)
  {
    fs->idx = fs->wl->idx;
    fs->w = fs->wl->window;
    return 0;
  }
  return -1;
}


----------------------------
static int cmd_find_get_session(struct cmd_find_state *fs, const char *session)
{
  struct session *s;
  unsigned int s_idx = 0;
  struct session *s_loop;
  unsigned int s_loop_idx = 0;
  struct client *c;
  unsigned int c_idx = 0;
  log_debug("%s: %s", __func__, session);
  if ((*session) == '$')
  {
    fs->s = session_find_by_id_str(session);
    if (fs->s == 0)
    {
      return -1;
    }
    return 0;
  }
  fs->s = session_find(session);
  if (fs->s != 0)
  {
    return 0;
  }
  c_idx = cmd_find_client(0, session, 1);
  if (((&c[c_idx]) != 0) && (c->session != 0))
  {
    fs->s = c->session;
    return 0;
  }
  if (fs->flags & 0x10)
  {
    return -1;
  }
  s_idx = 0;
  for (s_loop_idx = sessions_RB_MINMAX(&sessions, -1); (&s_loop[s_loop_idx]) != 0; s_loop_idx = sessions_RB_NEXT(s_loop_idx))
  {
    if (strncmp(session, s_loop->name, strlen(session)) == 0)
    {
      if ((&s[s_idx]) != 0)
      {
        return -1;
      }
      s_idx = &s_loop[s_loop_idx];
    }
  }

  if ((&s[s_idx]) != 0)
  {
    fs->s = &s[s_idx];
    return 0;
  }
  s_idx = 0;
  for (s_loop_idx = sessions_RB_MINMAX(&sessions, -1); (&s_loop[s_loop_idx]) != 0; s_loop_idx = sessions_RB_NEXT(s_loop_idx))
  {
    if (fnmatch(session, s_loop->name, 0) == 0)
    {
      if ((&s[s_idx]) != 0)
      {
        return -1;
      }
      s_idx = &s_loop[s_loop_idx];
    }
  }

  if ((&s[s_idx]) != 0)
  {
    fs->s = &s[s_idx];
    return 0;
  }
  return -1;
}


----------------------------
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


----------------------------
static int cmd_find_best_session_with_window(struct cmd_find_state *fs)
{
  struct session **slist = 0;
  unsigned int slist_idx = 0;
  u_int ssize;
  struct session *s;
  unsigned int s_idx = 0;
  ssize = 0;
  for (s_idx = sessions_RB_MINMAX(&sessions, -1); (&s[s_idx]) != 0; s_idx = sessions_RB_NEXT(s_idx))
  {
    if (!session_has(s, fs->w))
    {
      continue;
    }
    slist_idx = xreallocarray(slist_idx, ssize + 1, sizeof(*slist_idx));
    slist[ssize + slist_idx] = &s[s_idx];
    ssize += 1;
  }

  if (ssize == 0)
  {
    goto fail;
  }
  fs->s = cmd_find_best_session(slist, ssize, fs->flags);
  if (fs->s == 0)
  {
    goto fail;
  }
  free(slist);
  return cmd_find_best_winlink_with_window(fs);
  fail:
  free(slist);

  return -1;
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


static int cmd_find_get_pane(struct cmd_find_state *fs, const char *pane, int only)
{
  log_debug("%s: %s", __func__, pane);
  if ((*pane) == '%')
  {
    fs->wp = window_pane_find_by_id_str(pane);
    if (fs->wp == 0)
    {
      return -1;
    }
    fs->w = fs->wp->window;
    return cmd_find_best_session_with_window(fs);
  }
  fs->s = fs->current->s;
  fs->wl = fs->current->wl;
  fs->idx = fs->current->idx;
  fs->w = fs->current->w;
  if (cmd_find_get_pane_with_window(fs, pane) == 0)
  {
    return 0;
  }
  if ((!only) && (cmd_find_get_window(fs, pane, 0) == 0))
  {
    fs->wp = fs->w->active;
    return 0;
  }
  return -1;
}


/*** DEPENDENCIES:
static int cmd_find_get_pane_with_window(struct cmd_find_state *fs, const char *pane)
{
  const char *errstr;
  int idx;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int n;
  log_debug("%s: %s", __func__, pane);
  if ((*pane) == '%')
  {
    fs->wp = window_pane_find_by_id_str(pane);
    if (fs->wp == 0)
    {
      return -1;
    }
    if (fs->wp->window != fs->w)
    {
      return -1;
    }
    return 0;
  }
  if (strcmp(pane, "!") == 0)
  {
    fs->wp = fs->w->last;
    if (fs->wp == 0)
    {
      return -1;
    }
    return 0;
  }
  else
    if (strcmp(pane, "{up-of}") == 0)
  {
    fs->wp = window_pane_find_up(fs->w->active);
    if (fs->wp == 0)
    {
      return -1;
    }
    return 0;
  }
  else
    if (strcmp(pane, "{down-of}") == 0)
  {
    fs->wp = window_pane_find_down(fs->w->active);
    if (fs->wp == 0)
    {
      return -1;
    }
    return 0;
  }
  else
    if (strcmp(pane, "{left-of}") == 0)
  {
    fs->wp = window_pane_find_left(fs->w->active);
    if (fs->wp == 0)
    {
      return -1;
    }
    return 0;
  }
  else
    if (strcmp(pane, "{right-of}") == 0)
  {
    fs->wp = window_pane_find_right(fs->w->active);
    if (fs->wp == 0)
    {
      return -1;
    }
    return 0;
  }
  if ((pane[0] == '+') || (pane[0] == '-'))
  {
    if (pane[1] != '\0')
    {
      n = strtonum(pane + 1, 1, 2147483647, 0);
    }
    else
      n = 1;
    wp_idx = fs->w->active;
    if (pane[0] == '+')
    {
      fs->wp = window_pane_next_by_number(fs->w, wp, n);
    }
    else
      fs->wp = window_pane_previous_by_number(fs->w, wp, n);
    if (fs->wp != 0)
    {
      return 0;
    }
  }
  idx = strtonum(pane, 0, 2147483647, &errstr);
  if (errstr == 0)
  {
    fs->wp = window_pane_at_index(fs->w, idx);
    if (fs->wp != 0)
    {
      return 0;
    }
  }
  fs->wp = window_find_string(fs->w, pane);
  if (fs->wp != 0)
  {
    return 0;
  }
  return -1;
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


----------------------------
static int cmd_find_best_session_with_window(struct cmd_find_state *fs)
{
  struct session **slist = 0;
  unsigned int slist_idx = 0;
  u_int ssize;
  struct session *s;
  unsigned int s_idx = 0;
  ssize = 0;
  for (s_idx = sessions_RB_MINMAX(&sessions, -1); (&s[s_idx]) != 0; s_idx = sessions_RB_NEXT(s_idx))
  {
    if (!session_has(s, fs->w))
    {
      continue;
    }
    slist_idx = xreallocarray(slist_idx, ssize + 1, sizeof(*slist_idx));
    slist[ssize + slist_idx] = &s[s_idx];
    ssize += 1;
  }

  if (ssize == 0)
  {
    goto fail;
  }
  fs->s = cmd_find_best_session(slist, ssize, fs->flags);
  if (fs->s == 0)
  {
    goto fail;
  }
  free(slist);
  return cmd_find_best_winlink_with_window(fs);
  fail:
  free(slist);

  return -1;
}


----------------------------
static int cmd_find_get_window(struct cmd_find_state *fs, const char *window, int only)
{
  log_debug("%s: %s", __func__, window);
  if ((*window) == '@')
  {
    fs->w = window_find_by_id_str(window);
    if (fs->w == 0)
    {
      return -1;
    }
    return cmd_find_best_session_with_window(fs);
  }
  fs->s = fs->current->s;
  if (cmd_find_get_window_with_session(fs, window) == 0)
  {
    return 0;
  }
  if ((!only) && (cmd_find_get_session(fs, window) == 0))
  {
    fs->wl = fs->s->curw;
    fs->w = fs->wl->window;
    if ((~fs->flags) & 0x4)
    {
      fs->idx = fs->wl->idx;
    }
    return 0;
  }
  return -1;
}


----------------------------
None
----------------------------
***/


static int cmd_find_get_pane_with_session(struct cmd_find_state *fs, const char *pane)
{
  log_debug("%s: %s", __func__, pane);
  if ((*pane) == '%')
  {
    fs->wp = window_pane_find_by_id_str(pane);
    if (fs->wp == 0)
    {
      return -1;
    }
    fs->w = fs->wp->window;
    return cmd_find_best_winlink_with_window(fs);
  }
  fs->wl = fs->s->curw;
  fs->idx = fs->wl->idx;
  fs->w = fs->wl->window;
  return cmd_find_get_pane_with_window(fs, pane);
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


----------------------------
static int cmd_find_get_pane_with_window(struct cmd_find_state *fs, const char *pane)
{
  const char *errstr;
  int idx;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int n;
  log_debug("%s: %s", __func__, pane);
  if ((*pane) == '%')
  {
    fs->wp = window_pane_find_by_id_str(pane);
    if (fs->wp == 0)
    {
      return -1;
    }
    if (fs->wp->window != fs->w)
    {
      return -1;
    }
    return 0;
  }
  if (strcmp(pane, "!") == 0)
  {
    fs->wp = fs->w->last;
    if (fs->wp == 0)
    {
      return -1;
    }
    return 0;
  }
  else
    if (strcmp(pane, "{up-of}") == 0)
  {
    fs->wp = window_pane_find_up(fs->w->active);
    if (fs->wp == 0)
    {
      return -1;
    }
    return 0;
  }
  else
    if (strcmp(pane, "{down-of}") == 0)
  {
    fs->wp = window_pane_find_down(fs->w->active);
    if (fs->wp == 0)
    {
      return -1;
    }
    return 0;
  }
  else
    if (strcmp(pane, "{left-of}") == 0)
  {
    fs->wp = window_pane_find_left(fs->w->active);
    if (fs->wp == 0)
    {
      return -1;
    }
    return 0;
  }
  else
    if (strcmp(pane, "{right-of}") == 0)
  {
    fs->wp = window_pane_find_right(fs->w->active);
    if (fs->wp == 0)
    {
      return -1;
    }
    return 0;
  }
  if ((pane[0] == '+') || (pane[0] == '-'))
  {
    if (pane[1] != '\0')
    {
      n = strtonum(pane + 1, 1, 2147483647, 0);
    }
    else
      n = 1;
    wp_idx = fs->w->active;
    if (pane[0] == '+')
    {
      fs->wp = window_pane_next_by_number(fs->w, wp, n);
    }
    else
      fs->wp = window_pane_previous_by_number(fs->w, wp, n);
    if (fs->wp != 0)
    {
      return 0;
    }
  }
  idx = strtonum(pane, 0, 2147483647, &errstr);
  if (errstr == 0)
  {
    fs->wp = window_pane_at_index(fs->w, idx);
    if (fs->wp != 0)
    {
      return 0;
    }
  }
  fs->wp = window_find_string(fs->w, pane);
  if (fs->wp != 0)
  {
    return 0;
  }
  return -1;
}


----------------------------
static int cmd_find_best_winlink_with_window(struct cmd_find_state *fs)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct winlink *wl_loop;
  unsigned int wl_loop_idx = 0;
  wl_idx = 0;
  if ((fs->s->curw != 0) && (fs->s->curw->window == fs->w))
  {
    wl_idx = fs->s->curw;
  }
  else
  {
    for (wl_loop_idx = winlinks_RB_MINMAX(&fs->s->windows, -1); (&wl_loop[wl_loop_idx]) != 0; wl_loop_idx = winlinks_RB_NEXT(wl_loop_idx))
    {
      if (wl_loop->window == fs->w)
      {
        wl_idx = &wl_loop[wl_loop_idx];
        break;
      }
    }

  }
  if ((&wl[wl_idx]) == 0)
  {
    return -1;
  }
  fs->wl = &wl[wl_idx];
  fs->idx = fs->wl->idx;
  return 0;
}


----------------------------
None
----------------------------
***/


void helper_cmd_find_target_3(struct cmd_find_state * const fs, const char * const session, const char * const window, unsigned int window_idx, const char * const pane, unsigned int pane_idx)
{
  if (cmd_find_get_session(fs, session) != 0)
  {
    goto no_session;
  }
  if (((&window[window_idx]) == 0) && ((&pane[pane_idx]) == 0))
  {
    fs->wl = fs->s->curw;
    fs->idx = -1;
    fs->w = fs->wl->window;
    fs->wp = fs->w->active;
    goto found;
  }
  if (((&window[window_idx]) != 0) && ((&pane[pane_idx]) == 0))
  {
    if (cmd_find_get_window_with_session(fs, window) != 0)
    {
      goto no_window;
    }
    fs->wp = fs->wl->window->active;
    goto found;
  }
  if (((&window[window_idx]) == 0) && ((&pane[pane_idx]) != 0))
  {
    if (cmd_find_get_pane_with_session(fs, pane) != 0)
    {
      goto no_pane;
    }
    goto found;
  }
  if (cmd_find_get_window_with_session(fs, window) != 0)
  {
    goto no_window;
  }
  if (cmd_find_get_pane_with_window(fs, pane) != 0)
  {
    goto no_pane;
  }
  goto found;
}


/*** DEPENDENCIES:
static int cmd_find_get_window_with_session(struct cmd_find_state *fs, const char *window)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  const char *errstr;
  int idx;
  int n;
  int exact;
  struct session *s;
  unsigned int s_idx = 0;
  log_debug("%s: %s", __func__, window);
  exact = fs->flags & 0x20;
  fs->wl = fs->s->curw;
  fs->w = fs->wl->window;
  if ((*window) == '@')
  {
    fs->w = window_find_by_id_str(window);
    if ((fs->w == 0) || (!session_has(fs->s, fs->w)))
    {
      return -1;
    }
    return cmd_find_best_winlink_with_window(fs);
  }
  if ((!exact) && ((window[0] == '+') || (window[0] == '-')))
  {
    helper_cmd_find_get_window_with_session_1(&n, &s_idx, fs, window, s);
  }
  if (!exact)
  {
    helper_cmd_find_get_window_with_session_2(fs, window);
  }
  if ((window[0] != '+') && (window[0] != '-'))
  {
    idx = strtonum(window, 0, 2147483647, &errstr);
    if (errstr == 0)
    {
      if (fs->flags & 0x4)
      {
        fs->idx = idx;
        return 0;
      }
      fs->wl = winlink_find_by_index(&fs->s->windows, idx);
      if (fs->wl != 0)
      {
        fs->w = fs->wl->window;
        return 0;
      }
    }
  }
  fs->wl = 0;
  for (wl_idx = winlinks_RB_MINMAX(&fs->s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    if (strcmp(window, wl->window->name) == 0)
    {
      if (fs->wl != 0)
      {
        return -1;
      }
      fs->wl = &wl[wl_idx];
    }
  }

  if (fs->wl != 0)
  {
    fs->idx = fs->wl->idx;
    fs->w = fs->wl->window;
    return 0;
  }
  if (exact)
  {
    return -1;
  }
  fs->wl = 0;
  for (wl_idx = winlinks_RB_MINMAX(&fs->s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    if (strncmp(window, wl->window->name, strlen(window)) == 0)
    {
      if (fs->wl != 0)
      {
        return -1;
      }
      fs->wl = &wl[wl_idx];
    }
  }

  if (fs->wl != 0)
  {
    fs->idx = fs->wl->idx;
    fs->w = fs->wl->window;
    return 0;
  }
  fs->wl = 0;
  for (wl_idx = winlinks_RB_MINMAX(&fs->s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    if (fnmatch(window, wl->window->name, 0) == 0)
    {
      if (fs->wl != 0)
      {
        return -1;
      }
      fs->wl = &wl[wl_idx];
    }
  }

  if (fs->wl != 0)
  {
    fs->idx = fs->wl->idx;
    fs->w = fs->wl->window;
    return 0;
  }
  return -1;
}


----------------------------
static int cmd_find_get_pane_with_window(struct cmd_find_state *fs, const char *pane)
{
  const char *errstr;
  int idx;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int n;
  log_debug("%s: %s", __func__, pane);
  if ((*pane) == '%')
  {
    fs->wp = window_pane_find_by_id_str(pane);
    if (fs->wp == 0)
    {
      return -1;
    }
    if (fs->wp->window != fs->w)
    {
      return -1;
    }
    return 0;
  }
  if (strcmp(pane, "!") == 0)
  {
    fs->wp = fs->w->last;
    if (fs->wp == 0)
    {
      return -1;
    }
    return 0;
  }
  else
    if (strcmp(pane, "{up-of}") == 0)
  {
    fs->wp = window_pane_find_up(fs->w->active);
    if (fs->wp == 0)
    {
      return -1;
    }
    return 0;
  }
  else
    if (strcmp(pane, "{down-of}") == 0)
  {
    fs->wp = window_pane_find_down(fs->w->active);
    if (fs->wp == 0)
    {
      return -1;
    }
    return 0;
  }
  else
    if (strcmp(pane, "{left-of}") == 0)
  {
    fs->wp = window_pane_find_left(fs->w->active);
    if (fs->wp == 0)
    {
      return -1;
    }
    return 0;
  }
  else
    if (strcmp(pane, "{right-of}") == 0)
  {
    fs->wp = window_pane_find_right(fs->w->active);
    if (fs->wp == 0)
    {
      return -1;
    }
    return 0;
  }
  if ((pane[0] == '+') || (pane[0] == '-'))
  {
    if (pane[1] != '\0')
    {
      n = strtonum(pane + 1, 1, 2147483647, 0);
    }
    else
      n = 1;
    wp_idx = fs->w->active;
    if (pane[0] == '+')
    {
      fs->wp = window_pane_next_by_number(fs->w, wp, n);
    }
    else
      fs->wp = window_pane_previous_by_number(fs->w, wp, n);
    if (fs->wp != 0)
    {
      return 0;
    }
  }
  idx = strtonum(pane, 0, 2147483647, &errstr);
  if (errstr == 0)
  {
    fs->wp = window_pane_at_index(fs->w, idx);
    if (fs->wp != 0)
    {
      return 0;
    }
  }
  fs->wp = window_find_string(fs->w, pane);
  if (fs->wp != 0)
  {
    return 0;
  }
  return -1;
}


----------------------------
static int cmd_find_get_session(struct cmd_find_state *fs, const char *session)
{
  struct session *s;
  unsigned int s_idx = 0;
  struct session *s_loop;
  unsigned int s_loop_idx = 0;
  struct client *c;
  unsigned int c_idx = 0;
  log_debug("%s: %s", __func__, session);
  if ((*session) == '$')
  {
    fs->s = session_find_by_id_str(session);
    if (fs->s == 0)
    {
      return -1;
    }
    return 0;
  }
  fs->s = session_find(session);
  if (fs->s != 0)
  {
    return 0;
  }
  c_idx = cmd_find_client(0, session, 1);
  if (((&c[c_idx]) != 0) && (c->session != 0))
  {
    fs->s = c->session;
    return 0;
  }
  if (fs->flags & 0x10)
  {
    return -1;
  }
  s_idx = 0;
  for (s_loop_idx = sessions_RB_MINMAX(&sessions, -1); (&s_loop[s_loop_idx]) != 0; s_loop_idx = sessions_RB_NEXT(s_loop_idx))
  {
    if (strncmp(session, s_loop->name, strlen(session)) == 0)
    {
      if ((&s[s_idx]) != 0)
      {
        return -1;
      }
      s_idx = &s_loop[s_loop_idx];
    }
  }

  if ((&s[s_idx]) != 0)
  {
    fs->s = &s[s_idx];
    return 0;
  }
  s_idx = 0;
  for (s_loop_idx = sessions_RB_MINMAX(&sessions, -1); (&s_loop[s_loop_idx]) != 0; s_loop_idx = sessions_RB_NEXT(s_loop_idx))
  {
    if (fnmatch(session, s_loop->name, 0) == 0)
    {
      if ((&s[s_idx]) != 0)
      {
        return -1;
      }
      s_idx = &s_loop[s_loop_idx];
    }
  }

  if ((&s[s_idx]) != 0)
  {
    fs->s = &s[s_idx];
    return 0;
  }
  return -1;
}


----------------------------
static int cmd_find_get_pane_with_session(struct cmd_find_state *fs, const char *pane)
{
  log_debug("%s: %s", __func__, pane);
  if ((*pane) == '%')
  {
    fs->wp = window_pane_find_by_id_str(pane);
    if (fs->wp == 0)
    {
      return -1;
    }
    fs->w = fs->wp->window;
    return cmd_find_best_winlink_with_window(fs);
  }
  fs->wl = fs->s->curw;
  fs->idx = fs->wl->idx;
  fs->w = fs->wl->window;
  return cmd_find_get_pane_with_window(fs, pane);
}


----------------------------
None
----------------------------
***/


int cmd_find_target(struct cmd_find_state *fs, struct cmdq_item *item, const char *target, enum cmd_find_type type, int flags)
{
  struct mouse_event *m;
  unsigned int m_idx = 0;
  struct cmd_find_state current;
  char *colon;
  unsigned int colon_idx = 0;
  char *period;
  unsigned int period_idx = 0;
  char *copy = 0;
  unsigned int copy_idx = 0;
  const char *session;
  unsigned int session_idx = 0;
  const char *window;
  unsigned int window_idx = 0;
  const char *pane;
  unsigned int pane_idx = 0;
  const char *s;
  unsigned int s_idx = 0;
  int window_only = 0;
  int pane_only = 0;
  if (flags & 0x40)
  {
    flags |= 0x2;
  }
  if (type == CMD_FIND_PANE)
  {
    s_idx = "pane";
  }
  else
    if (type == CMD_FIND_WINDOW)
  {
    s_idx = "window";
  }
  else
    if (type == CMD_FIND_SESSION)
  {
    s_idx = "session";
  }
  else
    s_idx = "unknown";
  if (target == 0)
  {
    log_debug("%s: target none, type %s", __func__, s);
  }
  else
    log_debug("%s: target %s, type %s", __func__, target, s);
  log_debug("%s: item %p, flags %#x", __func__, item, flags);
  cmd_find_clear_state(fs, flags);
  if (server_check_marked() && (flags & 0x8))
  {
    fs->current = &marked_pane;
    log_debug("%s: current is marked pane", __func__);
  }
  else
    if (cmd_find_valid_state(&item->shared->current))
  {
    fs->current = &item->shared->current;
    log_debug("%s: current is from queue", __func__);
  }
  else
    if (cmd_find_from_client(&current, item->client, flags) == 0)
  {
    fs->current = &current;
    log_debug("%s: current is from client", __func__);
  }
  else
  {
    if ((~flags) & 0x2)
    {
      cmdq_error(item, "no current target");
    }
    goto error;
  }
  if (!cmd_find_valid_state(fs->current))
  {
    fatalx("invalid current find state");
  }
  if ((target == 0) || ((*target) == '\0'))
  {
    goto current;
  }
  if ((strcmp(target, "=") == 0) || (strcmp(target, "{mouse}") == 0))
  {
    helper_cmd_find_target_2(&m_idx, fs, item, type, flags, m);
  }
  if ((strcmp(target, "~") == 0) || (strcmp(target, "{marked}") == 0))
  {
    if (!server_check_marked())
    {
      if ((~flags) & 0x2)
      {
        cmdq_error(item, "no marked target");
      }
      goto error;
    }
    cmd_find_copy_state(fs, &marked_pane);
    goto found;
  }
  copy_idx = xstrdup(target);
  colon_idx = strchr(copy, ':');
  if ((&colon[colon_idx]) != 0)
  {
    colon[colon_idx] = '\0';
    colon_idx += 1;
  }
  if ((&colon[colon_idx]) == 0)
  {
    period_idx = strchr(copy, '.');
  }
  else
    period_idx = strchr(colon, '.');
  if ((&period[period_idx]) != 0)
  {
    period[period_idx] = '\0';
    period_idx += 1;
  }
  session_idx = (window = &window[window_idx + window_idx]);
  if (((&colon[colon_idx]) != 0) && ((&period[period_idx]) != 0))
  {
    session_idx = &copy[copy_idx];
    window_idx = &colon[colon_idx];
    window_only = 1;
    pane_idx = &period[period_idx];
    pane_only = 1;
  }
  else
    if (((&colon[colon_idx]) != 0) && ((&period[period_idx]) == 0))
  {
    session_idx = &copy[copy_idx];
    window_idx = &colon[colon_idx];
    window_only = 1;
  }
  else
    if (((&colon[colon_idx]) == 0) && ((&period[period_idx]) != 0))
  {
    window_idx = &copy[copy_idx];
    pane_idx = &period[period_idx];
    pane_only = 1;
  }
  else
  {
    helper_cmd_find_target_1(&session_idx, &window_idx, &pane_idx, type, copy, copy_idx);
  }
  if (((&session[session_idx]) != 0) && (session[session_idx] == '='))
  {
    session_idx += 1;
    fs->flags |= 0x10;
  }
  if (((&window[window_idx]) != 0) && (window[window_idx] == '='))
  {
    window_idx += 1;
    fs->flags |= 0x20;
  }
  if (((&session[session_idx]) != 0) && (session[session_idx] == '\0'))
  {
    session_idx = 0;
  }
  if (((&window[window_idx]) != 0) && (window[window_idx] == '\0'))
  {
    window_idx = 0;
  }
  if (((&pane[pane_idx]) != 0) && (pane[pane_idx] == '\0'))
  {
    pane_idx = 0;
  }
  if ((&session[session_idx]) != 0)
  {
    session_idx = cmd_find_map_table(cmd_find_session_table, session_idx);
  }
  if ((&window[window_idx]) != 0)
  {
    window_idx = cmd_find_map_table(cmd_find_window_table, window_idx);
  }
  if ((&pane[pane_idx]) != 0)
  {
    pane_idx = cmd_find_map_table(cmd_find_pane_table, pane_idx);
  }
  log_debug("%s: target %s (flags %#x): session=%s, window=%s, pane=%s", __func__, target, flags, ((&session[session_idx]) == 0) ? ("none") : (session), ((&window[window_idx]) == 0) ? ("none") : (window), ((&pane[pane_idx]) == 0) ? ("none") : (pane));
  if (((&pane[pane_idx]) != 0) && (flags & 0x4))
  {
    if ((~flags) & 0x2)
    {
      cmdq_error(item, "can't specify pane here");
    }
    goto error;
  }
  if ((&session[session_idx]) != 0)
  {
    helper_cmd_find_target_3(fs, session, window, window_idx, pane, pane_idx);
  }
  if (((&window[window_idx]) != 0) && ((&pane[pane_idx]) != 0))
  {
    if (cmd_find_get_window(fs, window, window_only) != 0)
    {
      goto no_window;
    }
    if (cmd_find_get_pane_with_window(fs, pane) != 0)
    {
      goto no_pane;
    }
    goto found;
  }
  if (((&window[window_idx]) != 0) && ((&pane[pane_idx]) == 0))
  {
    if (cmd_find_get_window(fs, window, window_only) != 0)
    {
      goto no_window;
    }
    fs->wp = fs->wl->window->active;
    goto found;
  }
  if (((&window[window_idx]) == 0) && ((&pane[pane_idx]) != 0))
  {
    if (cmd_find_get_pane(fs, pane, pane_only) != 0)
    {
      goto no_pane;
    }
    goto found;
  }
  current:
  cmd_find_copy_state(fs, fs->current);

  if (flags & 0x4)
  {
    fs->idx = -1;
  }
  goto found;
  error:
  fs->current = 0;

  log_debug("%s: error", __func__);
  free(copy);
  if (flags & 0x40)
  {
    return 0;
  }
  return -1;
  found:
  fs->current = 0;

  cmd_find_log_state(__func__, fs);
  free(copy);
  return 0;
  no_session:
  if ((~flags) & 0x2)
  {
    cmdq_error(item, "can't find session %s", session);
  }

  goto error;
  no_window:
  if ((~flags) & 0x2)
  {
    cmdq_error(item, "can't find window %s", window);
  }

  goto error;
  no_pane:
  if ((~flags) & 0x2)
  {
    cmdq_error(item, "can't find pane %s", pane);
  }

  goto error;
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
extern struct cmd_find_state marked_pane
----------------------------
static int cmd_find_get_pane_with_window(struct cmd_find_state *fs, const char *pane)
{
  const char *errstr;
  int idx;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int n;
  log_debug("%s: %s", __func__, pane);
  if ((*pane) == '%')
  {
    fs->wp = window_pane_find_by_id_str(pane);
    if (fs->wp == 0)
    {
      return -1;
    }
    if (fs->wp->window != fs->w)
    {
      return -1;
    }
    return 0;
  }
  if (strcmp(pane, "!") == 0)
  {
    fs->wp = fs->w->last;
    if (fs->wp == 0)
    {
      return -1;
    }
    return 0;
  }
  else
    if (strcmp(pane, "{up-of}") == 0)
  {
    fs->wp = window_pane_find_up(fs->w->active);
    if (fs->wp == 0)
    {
      return -1;
    }
    return 0;
  }
  else
    if (strcmp(pane, "{down-of}") == 0)
  {
    fs->wp = window_pane_find_down(fs->w->active);
    if (fs->wp == 0)
    {
      return -1;
    }
    return 0;
  }
  else
    if (strcmp(pane, "{left-of}") == 0)
  {
    fs->wp = window_pane_find_left(fs->w->active);
    if (fs->wp == 0)
    {
      return -1;
    }
    return 0;
  }
  else
    if (strcmp(pane, "{right-of}") == 0)
  {
    fs->wp = window_pane_find_right(fs->w->active);
    if (fs->wp == 0)
    {
      return -1;
    }
    return 0;
  }
  if ((pane[0] == '+') || (pane[0] == '-'))
  {
    if (pane[1] != '\0')
    {
      n = strtonum(pane + 1, 1, 2147483647, 0);
    }
    else
      n = 1;
    wp_idx = fs->w->active;
    if (pane[0] == '+')
    {
      fs->wp = window_pane_next_by_number(fs->w, wp, n);
    }
    else
      fs->wp = window_pane_previous_by_number(fs->w, wp, n);
    if (fs->wp != 0)
    {
      return 0;
    }
  }
  idx = strtonum(pane, 0, 2147483647, &errstr);
  if (errstr == 0)
  {
    fs->wp = window_pane_at_index(fs->w, idx);
    if (fs->wp != 0)
    {
      return 0;
    }
  }
  fs->wp = window_find_string(fs->w, pane);
  if (fs->wp != 0)
  {
    return 0;
  }
  return -1;
}


----------------------------
int cmd_find_valid_state(struct cmd_find_state *fs)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  if ((((fs->s == 0) || (fs->wl == 0)) || (fs->w == 0)) || (fs->wp == 0))
  {
    return 0;
  }
  if (!session_alive(fs->s))
  {
    return 0;
  }
  for (wl_idx = winlinks_RB_MINMAX(&fs->s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    if ((wl->window == fs->w) && ((&wl[wl_idx]) == fs->wl))
    {
      break;
    }
  }

  if ((&wl[wl_idx]) == 0)
  {
    return 0;
  }
  if (fs->w != fs->wl->window)
  {
    return 0;
  }
  return window_has_pane(fs->w, fs->wp);
}


----------------------------
enum cmd_find_type
{
  CMD_FIND_PANE,
  CMD_FIND_WINDOW,
  CMD_FIND_SESSION
}
----------------------------
int cmd_find_from_client(struct cmd_find_state *fs, struct client *c, int flags)
{
  struct session *s;
  unsigned int s_idx = 0;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  if (c == 0)
  {
    return cmd_find_from_nothing(fs, flags);
  }
  if (c->session != 0)
  {
    cmd_find_from_session(fs, c->session, flags);
    return 0;
  }
  cmd_find_clear_state(fs, flags);
  wp_idx = cmd_find_inside_pane(c);
  if ((&wp[wp_idx]) == 0)
  {
    goto unknown_pane;
  }
  s_idx = cmd_find_try_TMUX(c);
  if ((&s[s_idx]) != 0)
  {
    for (wl_idx = winlinks_RB_MINMAX(&s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
    {
      if (window_has_pane(wl->window, wp))
      {
        break;
      }
    }

    if ((&wl[wl_idx]) != 0)
    {
      fs->s = &s[s_idx];
      fs->wl = s->curw;
      fs->w = fs->wl->window;
      fs->wp = fs->w->active;
      cmd_find_log_state(__func__, fs);
      return 0;
    }
  }
  fs->w = wp->window;
  if (cmd_find_best_session_with_window(fs) != 0)
  {
    goto unknown_pane;
  }
  fs->wl = fs->s->curw;
  fs->w = fs->wl->window;
  fs->wp = fs->w->active;
  cmd_find_log_state(__func__, fs);
  return 0;
  unknown_pane:
  s_idx = cmd_find_try_TMUX(c);

  if ((&s[s_idx]) != 0)
  {
    cmd_find_from_session(fs, s, flags);
    return 0;
  }
  return cmd_find_from_nothing(fs, flags);
}


----------------------------
static const char *cmd_find_session_table[][2] = {{0, 0}}
----------------------------
void cmd_find_copy_state(struct cmd_find_state *dst, struct cmd_find_state *src)
{
  dst->s = src->s;
  dst->wl = src->wl;
  dst->idx = src->idx;
  dst->w = src->w;
  dst->wp = src->wp;
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
void helper_cmd_find_target_2(unsigned int * const m_idx_ref, struct cmd_find_state * const fs, struct cmdq_item * const item, enum cmd_find_type type, int flags, struct mouse_event * const m)
{
  unsigned int m_idx = *m_idx_ref;
  m_idx = &item->shared->mouse;
  switch (type)
  {
    case CMD_FIND_PANE:
    {
      fs->wp = cmd_mouse_pane(m, &fs->s, &fs->wl);
      if (fs->wp != 0)
      {
        fs->w = fs->wl->window;
      }
      break;
    }

    case CMD_FIND_WINDOW:

    case CMD_FIND_SESSION:
    {
      fs->wl = cmd_mouse_window(m, &fs->s);
      if (fs->wl != 0)
      {
        fs->w = fs->wl->window;
        fs->wp = fs->w->active;
      }
      break;
    }

  }

  if (fs->wp == 0)
  {
    if ((~flags) & 0x2)
    {
      cmdq_error(item, "no mouse target");
    }
    goto error;
  }
  goto found;
  *m_idx_ref = m_idx;
}


----------------------------
static const char *cmd_find_pane_table[][2] = {{"{last}", "!"}, {"{next}", "+"}, {"{previous}", "-"}, {"{top}", "top"}, {"{bottom}", "bottom"}, {"{left}", "left"}, {"{right}", "right"}, {"{top-left}", "top-left"}, {"{top-right}", "top-right"}, {"{bottom-left}", "bottom-left"}, {"{bottom-right}", "bottom-right"}, {"{up-of}", "{up-of}"}, {"{down-of}", "{down-of}"}, {"{left-of}", "{left-of}"}, {"{right-of}", "{right-of}"}, {0, 0}}
----------------------------
int server_check_marked(void)
{
  return cmd_find_valid_state(&marked_pane);
}


----------------------------
void helper_cmd_find_target_1(unsigned int * const session_idx_ref, unsigned int * const window_idx_ref, unsigned int * const pane_idx_ref, enum cmd_find_type type, char * const copy, unsigned int copy_idx)
{
  unsigned int session_idx = *session_idx_ref;
  unsigned int window_idx = *window_idx_ref;
  unsigned int pane_idx = *pane_idx_ref;
  if (copy[copy_idx] == '$')
  {
    session_idx = &copy[copy_idx];
  }
  else
    if (copy[copy_idx] == '@')
  {
    window_idx = &copy[copy_idx];
  }
  else
    if (copy[copy_idx] == '%')
  {
    pane_idx = &copy[copy_idx];
  }
  else
  {
    switch (type)
    {
      case CMD_FIND_SESSION:
      {
        session_idx = &copy[copy_idx];
        break;
      }

      case CMD_FIND_WINDOW:
      {
        window_idx = &copy[copy_idx];
        break;
      }

      case CMD_FIND_PANE:
      {
        pane_idx = &copy[copy_idx];
        break;
      }

    }

  }
  *session_idx_ref = session_idx;
  *window_idx_ref = window_idx;
  *pane_idx_ref = pane_idx;
}


----------------------------
void cmd_find_clear_state(struct cmd_find_state *fs, int flags)
{
  memset(fs, 0, sizeof(*fs));
  fs->flags = flags;
  fs->idx = -1;
}


----------------------------
void cmd_find_log_state(const char *prefix, struct cmd_find_state *fs)
{
  if (fs->s != 0)
  {
    log_debug("%s: s=$%u", prefix, fs->s->id);
  }
  else
    log_debug("%s: s=none", prefix);
  if (fs->wl != 0)
  {
    log_debug("%s: wl=%u %d w=@%u %s", prefix, fs->wl->idx, fs->wl->window == fs->w, fs->w->id, fs->w->name);
  }
  else
    log_debug("%s: wl=none", prefix);
  if (fs->wp != 0)
  {
    log_debug("%s: wp=%%%u", prefix, fs->wp->id);
  }
  else
    log_debug("%s: wp=none", prefix);
  if (fs->idx != (-1))
  {
    log_debug("%s: idx=%d", prefix, fs->idx);
  }
  else
    log_debug("%s: idx=none", prefix);
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
static const char *cmd_find_map_table(const char *table[][2], const char *s)
{
  u_int i;
  for (i = 0; table[i][0] != 0; i += 1)
  {
    if (strcmp(s, table[i][0]) == 0)
    {
      return table[i][1];
    }
  }

  return s;
}


----------------------------
static int cmd_find_get_pane(struct cmd_find_state *fs, const char *pane, int only)
{
  log_debug("%s: %s", __func__, pane);
  if ((*pane) == '%')
  {
    fs->wp = window_pane_find_by_id_str(pane);
    if (fs->wp == 0)
    {
      return -1;
    }
    fs->w = fs->wp->window;
    return cmd_find_best_session_with_window(fs);
  }
  fs->s = fs->current->s;
  fs->wl = fs->current->wl;
  fs->idx = fs->current->idx;
  fs->w = fs->current->w;
  if (cmd_find_get_pane_with_window(fs, pane) == 0)
  {
    return 0;
  }
  if ((!only) && (cmd_find_get_window(fs, pane, 0) == 0))
  {
    fs->wp = fs->w->active;
    return 0;
  }
  return -1;
}


----------------------------
static const char *cmd_find_window_table[][2] = {{"{start}", "^"}, {"{last}", "!"}, {"{end}", "$"}, {"{next}", "+"}, {"{previous}", "-"}, {0, 0}}
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
void helper_cmd_find_target_3(struct cmd_find_state * const fs, const char * const session, const char * const window, unsigned int window_idx, const char * const pane, unsigned int pane_idx)
{
  if (cmd_find_get_session(fs, session) != 0)
  {
    goto no_session;
  }
  if (((&window[window_idx]) == 0) && ((&pane[pane_idx]) == 0))
  {
    fs->wl = fs->s->curw;
    fs->idx = -1;
    fs->w = fs->wl->window;
    fs->wp = fs->w->active;
    goto found;
  }
  if (((&window[window_idx]) != 0) && ((&pane[pane_idx]) == 0))
  {
    if (cmd_find_get_window_with_session(fs, window) != 0)
    {
      goto no_window;
    }
    fs->wp = fs->wl->window->active;
    goto found;
  }
  if (((&window[window_idx]) == 0) && ((&pane[pane_idx]) != 0))
  {
    if (cmd_find_get_pane_with_session(fs, pane) != 0)
    {
      goto no_pane;
    }
    goto found;
  }
  if (cmd_find_get_window_with_session(fs, window) != 0)
  {
    goto no_window;
  }
  if (cmd_find_get_pane_with_window(fs, pane) != 0)
  {
    goto no_pane;
  }
  goto found;
}


----------------------------
static int cmd_find_get_window(struct cmd_find_state *fs, const char *window, int only)
{
  log_debug("%s: %s", __func__, window);
  if ((*window) == '@')
  {
    fs->w = window_find_by_id_str(window);
    if (fs->w == 0)
    {
      return -1;
    }
    return cmd_find_best_session_with_window(fs);
  }
  fs->s = fs->current->s;
  if (cmd_find_get_window_with_session(fs, window) == 0)
  {
    return 0;
  }
  if ((!only) && (cmd_find_get_session(fs, window) == 0))
  {
    fs->wl = fs->s->curw;
    fs->w = fs->wl->window;
    if ((~fs->flags) & 0x4)
    {
      fs->idx = fs->wl->idx;
    }
    return 0;
  }
  return -1;
}


----------------------------
None
----------------------------
***/


int cmd_find_from_session_window(struct cmd_find_state *fs, struct session *s, struct window *w, int flags)
{
  cmd_find_clear_state(fs, flags);
  fs->s = s;
  fs->w = w;
  if (cmd_find_best_winlink_with_window(fs) != 0)
  {
    cmd_find_clear_state(fs, flags);
    return -1;
  }
  fs->wp = fs->w->active;
  cmd_find_log_state(__func__, fs);
  return 0;
}


/*** DEPENDENCIES:
void cmd_find_log_state(const char *prefix, struct cmd_find_state *fs)
{
  if (fs->s != 0)
  {
    log_debug("%s: s=$%u", prefix, fs->s->id);
  }
  else
    log_debug("%s: s=none", prefix);
  if (fs->wl != 0)
  {
    log_debug("%s: wl=%u %d w=@%u %s", prefix, fs->wl->idx, fs->wl->window == fs->w, fs->w->id, fs->w->name);
  }
  else
    log_debug("%s: wl=none", prefix);
  if (fs->wp != 0)
  {
    log_debug("%s: wp=%%%u", prefix, fs->wp->id);
  }
  else
    log_debug("%s: wp=none", prefix);
  if (fs->idx != (-1))
  {
    log_debug("%s: idx=%d", prefix, fs->idx);
  }
  else
    log_debug("%s: idx=none", prefix);
}


----------------------------
void cmd_find_clear_state(struct cmd_find_state *fs, int flags)
{
  memset(fs, 0, sizeof(*fs));
  fs->flags = flags;
  fs->idx = -1;
}


----------------------------
static int cmd_find_best_winlink_with_window(struct cmd_find_state *fs)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct winlink *wl_loop;
  unsigned int wl_loop_idx = 0;
  wl_idx = 0;
  if ((fs->s->curw != 0) && (fs->s->curw->window == fs->w))
  {
    wl_idx = fs->s->curw;
  }
  else
  {
    for (wl_loop_idx = winlinks_RB_MINMAX(&fs->s->windows, -1); (&wl_loop[wl_loop_idx]) != 0; wl_loop_idx = winlinks_RB_NEXT(wl_loop_idx))
    {
      if (wl_loop->window == fs->w)
      {
        wl_idx = &wl_loop[wl_loop_idx];
        break;
      }
    }

  }
  if ((&wl[wl_idx]) == 0)
  {
    return -1;
  }
  fs->wl = &wl[wl_idx];
  fs->idx = fs->wl->idx;
  return 0;
}


----------------------------
None
----------------------------
***/


int cmd_find_from_mouse(struct cmd_find_state *fs, struct mouse_event *m, int flags)
{
  cmd_find_clear_state(fs, flags);
  if (!m->valid)
  {
    return -1;
  }
  fs->wp = cmd_mouse_pane(m, &fs->s, &fs->wl);
  if (fs->wp == 0)
  {
    cmd_find_clear_state(fs, flags);
    return -1;
  }
  fs->w = fs->wl->window;
  cmd_find_log_state(__func__, fs);
  return 0;
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
void cmd_find_log_state(const char *prefix, struct cmd_find_state *fs)
{
  if (fs->s != 0)
  {
    log_debug("%s: s=$%u", prefix, fs->s->id);
  }
  else
    log_debug("%s: s=none", prefix);
  if (fs->wl != 0)
  {
    log_debug("%s: wl=%u %d w=@%u %s", prefix, fs->wl->idx, fs->wl->window == fs->w, fs->w->id, fs->w->name);
  }
  else
    log_debug("%s: wl=none", prefix);
  if (fs->wp != 0)
  {
    log_debug("%s: wp=%%%u", prefix, fs->wp->id);
  }
  else
    log_debug("%s: wp=none", prefix);
  if (fs->idx != (-1))
  {
    log_debug("%s: idx=%d", prefix, fs->idx);
  }
  else
    log_debug("%s: idx=none", prefix);
}


----------------------------
void cmd_find_clear_state(struct cmd_find_state *fs, int flags)
{
  memset(fs, 0, sizeof(*fs));
  fs->flags = flags;
  fs->idx = -1;
}


----------------------------
struct window_pane *cmd_mouse_pane(struct mouse_event *m, struct session **sp, struct winlink **wlp)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  if ((wl_idx = cmd_mouse_window(m, sp)) == 0)
  {
    return 0;
  }
  if ((wp_idx = window_pane_find_by_id(m->wp_idx)) == 0)
  {
    return 0;
  }
  if (!window_has_pane(wl->window, wp))
  {
    return 0;
  }
  if (wlp != 0)
  {
    *wlp = &wl[wl_idx];
  }
  return wp;
}


----------------------------
None
----------------------------
***/


void cmd_find_from_winlink_pane(struct cmd_find_state *fs, struct winlink *wl, struct window_pane *wp, int flags)
{
  cmd_find_clear_state(fs, flags);
  fs->s = wl->session;
  fs->wl = wl;
  fs->idx = fs->wl->idx;
  fs->w = fs->wl->window;
  fs->wp = wp;
  cmd_find_log_state(__func__, fs);
}


/*** DEPENDENCIES:
void cmd_find_log_state(const char *prefix, struct cmd_find_state *fs)
{
  if (fs->s != 0)
  {
    log_debug("%s: s=$%u", prefix, fs->s->id);
  }
  else
    log_debug("%s: s=none", prefix);
  if (fs->wl != 0)
  {
    log_debug("%s: wl=%u %d w=@%u %s", prefix, fs->wl->idx, fs->wl->window == fs->w, fs->w->id, fs->w->name);
  }
  else
    log_debug("%s: wl=none", prefix);
  if (fs->wp != 0)
  {
    log_debug("%s: wp=%%%u", prefix, fs->wp->id);
  }
  else
    log_debug("%s: wp=none", prefix);
  if (fs->idx != (-1))
  {
    log_debug("%s: idx=%d", prefix, fs->idx);
  }
  else
    log_debug("%s: idx=none", prefix);
}


----------------------------
void cmd_find_clear_state(struct cmd_find_state *fs, int flags)
{
  memset(fs, 0, sizeof(*fs));
  fs->flags = flags;
  fs->idx = -1;
}


----------------------------
None
----------------------------
***/


