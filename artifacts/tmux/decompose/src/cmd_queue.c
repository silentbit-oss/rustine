static struct cmdq_list *cmdq_get(struct client *c)
{
  if (c == 0)
  {
    return &global_queue;
  }
  return &c->queue;
}


/*** DEPENDENCIES:
static struct cmdq_list global_queue = {0, &global_queue.tqh_first}
----------------------------
None
----------------------------
***/


void cmdq_append(struct client *c, struct cmdq_item *item)
{
  unsigned int item_idx = 0;
  struct cmdq_list *queue = cmdq_get(c);
  struct cmdq_item *next;
  unsigned int next_idx = 0;
  do
  {
    next_idx = item->next_idx;
    item->next = 0;
    if (c != 0)
    {
      c->references += 1;
    }
    item->client = c;
    item->queue = queue;
    do
    {
      item->entry.tqe_next = 0;
      item->entry.tqe_prev = queue->tqh_last;
      *queue->tqh_last = &item[item_idx];
      queue->tqh_last = &item->entry.tqe_next;
    }
    while (0);
    item_idx = &next[next_idx];
  }
  while ((&item[item_idx]) != 0);
}


/*** DEPENDENCIES:
static struct cmdq_list *cmdq_get(struct client *c)
{
  if (c == 0)
  {
    return &global_queue;
  }
  return &c->queue;
}


----------------------------
None
----------------------------
***/


struct cmdq_item *cmdq_get_callback1(const char *name, cmdq_cb cb, void *data)
{
  struct cmdq_item *item;
  unsigned int item_idx = 0;
  char *tmp;
  xasprintf(&tmp, "callback[%s]", name);
  item_idx = xcalloc(1, sizeof(*item_idx));
  item->name = tmp;
  item->type = CMDQ_CALLBACK;
  item->group = 0;
  item->flags = 0;
  item->cb = cb;
  item->data = data;
  return item;
}


/*** DEPENDENCIES:
typedef enum cmd_retval (*cmdq_cb)(struct cmdq_item *, void *)
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


// hint:  ['flags_ref is a mutable refrence to int', 'item_idx_ref is a mutable refrence to unsigned int', 'first_idx_ref is a mutable refrence to unsigned int', 'last_idx_ref is a mutable refrence to unsigned int', 'group_ref is a mutable refrence to u_int']
void helper_cmdq_get_command_1(int * const flags_ref, unsigned int * const item_idx_ref, unsigned int * const first_idx_ref, unsigned int * const last_idx_ref, u_int * const group_ref, struct cmd_list * const cmdlist, struct cmdq_item * const item, struct cmdq_item * const first, struct cmdq_item * const last, struct cmd * const cmd, unsigned int cmd_idx, char * const tmp, struct cmdq_shared * const shared, unsigned int shared_idx)
{
  int flags = *flags_ref;
  unsigned int item_idx = *item_idx_ref;
  unsigned int first_idx = *first_idx_ref;
  unsigned int last_idx = *last_idx_ref;
  u_int group = *group_ref;
  xasprintf(&tmp, "command[%s]", cmd->entry->name);
  item_idx = xcalloc(1, sizeof(*item_idx));
  item->name = tmp;
  item->type = CMDQ_COMMAND;
  item->group = group;
  item->flags = flags;
  item->shared = &shared[shared_idx];
  item->cmdlist = cmdlist;
  item->cmd = &cmd[cmd_idx];
  shared->references += 1;
  cmdlist->references += 1;
  if ((&first[first_idx]) == 0)
  {
    first_idx = &item[item_idx];
  }
  if ((&last[last_idx]) != 0)
  {
    last->next = &item[item_idx];
  }
  last_idx = &item[item_idx];
  *flags_ref = flags;
  *item_idx_ref = item_idx;
  *first_idx_ref = first_idx;
  *last_idx_ref = last_idx;
  *group_ref = group;
}


/*** DEPENDENCIES:
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


static u_int cmdq_next_group(void)
{
  static u_int group;
  group += 1;
  return ++group;
}


/*** DEPENDENCIES:
***/


struct cmdq_item *cmdq_get_command(struct cmd_list *cmdlist, struct cmd_find_state *current, struct mouse_event *m, int flags)
{
  struct cmdq_item *item;
  unsigned int item_idx = 0;
  struct cmdq_item *first = 0;
  unsigned int first_idx = 0;
  struct cmdq_item *last = 0;
  unsigned int last_idx = 0;
  struct cmd *cmd;
  unsigned int cmd_idx = 0;
  u_int group = cmdq_next_group();
  char *tmp;
  struct cmdq_shared *shared;
  unsigned int shared_idx = 0;
  shared_idx = xcalloc(1, sizeof(*shared_idx));
  if (current != 0)
  {
    cmd_find_copy_state(&shared->current, current);
  }
  else
    cmd_find_clear_state(&shared->current, 0);
  if (m != 0)
  {
    memcpy(&shared->mouse, m, sizeof(shared->mouse));
  }
  for (cmd_idx = (&cmdlist->list)->tqh_first; (&cmd[cmd_idx]) != 0; cmd_idx = cmd_idx->qentry.tqe_next)
  {
    helper_cmdq_get_command_1(&flags, &item_idx, &first_idx, &last_idx, &group, cmdlist, item, first, last, cmd, cmd_idx, tmp, shared, shared_idx);
  }

  return first;
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
void helper_cmdq_get_command_1(int * const flags_ref, unsigned int * const item_idx_ref, unsigned int * const first_idx_ref, unsigned int * const last_idx_ref, u_int * const group_ref, struct cmd_list * const cmdlist, struct cmdq_item * const item, struct cmdq_item * const first, struct cmdq_item * const last, struct cmd * const cmd, unsigned int cmd_idx, char * const tmp, struct cmdq_shared * const shared, unsigned int shared_idx)
{
  int flags = *flags_ref;
  unsigned int item_idx = *item_idx_ref;
  unsigned int first_idx = *first_idx_ref;
  unsigned int last_idx = *last_idx_ref;
  u_int group = *group_ref;
  xasprintf(&tmp, "command[%s]", cmd->entry->name);
  item_idx = xcalloc(1, sizeof(*item_idx));
  item->name = tmp;
  item->type = CMDQ_COMMAND;
  item->group = group;
  item->flags = flags;
  item->shared = &shared[shared_idx];
  item->cmdlist = cmdlist;
  item->cmd = &cmd[cmd_idx];
  shared->references += 1;
  cmdlist->references += 1;
  if ((&first[first_idx]) == 0)
  {
    first_idx = &item[item_idx];
  }
  if ((&last[last_idx]) != 0)
  {
    last->next = &item[item_idx];
  }
  last_idx = &item[item_idx];
  *flags_ref = flags;
  *item_idx_ref = item_idx;
  *first_idx_ref = first_idx;
  *last_idx_ref = last_idx;
  *group_ref = group;
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
void cmd_find_clear_state(struct cmd_find_state *fs, int flags)
{
  memset(fs, 0, sizeof(*fs));
  fs->flags = flags;
  fs->idx = -1;
}


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
static u_int cmdq_next_group(void)
{
  static u_int group;
  group += 1;
  return ++group;
}


----------------------------
None
----------------------------
***/


void cmdq_insert_after(struct cmdq_item *after, struct cmdq_item *item)
{
  unsigned int item_idx = 0;
  struct client *c = after->client;
  struct cmdq_list *queue = after->queue;
  struct cmdq_item *next;
  unsigned int next_idx = 0;
  do
  {
    next_idx = item->next_idx;
    item->next = 0;
    if (c != 0)
    {
      c->references += 1;
    }
    item->client = c;
    item->queue = queue;
    if (after->next != 0)
    {
      do
      {
        if ((item->entry.tqe_next = after->next->entry.tqe_next) != 0)
        {
          item->entry.tqe_next->entry.tqe_prev = &item->entry.tqe_next;
        }
        else
          queue->tqh_last = &item->entry.tqe_next;
        after->next->entry.tqe_next = &item[item_idx];
        item->entry.tqe_prev = &after->next->entry.tqe_next;
      }
      while (0);
    }
    else
      do
    {
      if ((item->entry.tqe_next = after->entry.tqe_next) != 0)
      {
        item->entry.tqe_next->entry.tqe_prev = &item->entry.tqe_next;
      }
      else
        queue->tqh_last = &item->entry.tqe_next;
      after->entry.tqe_next = &item[item_idx];
      item->entry.tqe_prev = &after->entry.tqe_next;
    }
    while (0);
    after->next = &item[item_idx];
    item_idx = &next[next_idx];
  }
  while ((&item[item_idx]) != 0);
}


/*** DEPENDENCIES:
None
----------------------------
***/


static const char *cmdq_name(struct client *c)
{
  static char s[32];
  if (c == 0)
  {
    return "<global>";
  }
  xsnprintf(s, sizeof(s), "<%p>", c);
  return s;
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
None
----------------------------
***/


static void cmdq_remove(struct cmdq_item *item)
{
  if ((item->shared != 0) && ((--item->shared->references) == 0))
  {
    if (item->shared->formats != 0)
    {
      format_free(item->shared->formats);
    }
    free(item->shared);
  }
  if (item->client != 0)
  {
    server_client_unref(item->client);
  }
  if (item->type == CMDQ_COMMAND)
  {
    cmd_list_free(item->cmdlist);
  }
  do
  {
    if (item->entry.tqe_next != 0)
    {
      item->entry.tqe_next->entry.tqe_prev = item->entry.tqe_prev;
    }
    else
      item->queue->tqh_last = item->entry.tqe_prev;
    *item->entry.tqe_prev = item->entry.tqe_next;
    ;
    ;
  }
  while (0);
  free((void *) item->name);
  free(item);
}


/*** DEPENDENCIES:
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
void cmd_list_free(struct cmd_list *cmdlist)
{
  struct cmd *cmd;
  unsigned int cmd_idx = 0;
  struct cmd *cmd1;
  unsigned int cmd1_idx = 0;
  if ((--cmdlist->references) != 0)
  {
    return;
  }
  for (cmd_idx = (&cmdlist->list)->tqh_first; ((&cmd[cmd_idx]) != 0) && ((cmd1_idx = cmd->qentry.tqe_next, 1)); cmd_idx = &cmd1[cmd1_idx])
  {
    do
    {
      if (cmd->qentry.tqe_next != 0)
      {
        cmd->qentry.tqe_next->qentry.tqe_prev = cmd->qentry.tqe_prev;
      }
      else
        (&cmdlist->list)->tqh_last = cmd->qentry.tqe_prev;
      *cmd->qentry.tqe_prev = cmd->qentry.tqe_next;
      ;
      ;
    }
    while (0);
    args_free(cmd->args);
    free(cmd->file);
    free(cmd);
  }

  free(cmdlist);
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
None
----------------------------
***/


static void cmdq_remove_group(struct cmdq_item *item)
{
  struct cmdq_item *this;
  unsigned int this_idx = 0;
  struct cmdq_item *next;
  unsigned int next_idx = 0;
  this_idx = item->entry.tqe_next;
  while ((&this[this_idx]) != 0)
  {
    next_idx = this->entry.tqe_next;
    if (this->group == item->group)
    {
      cmdq_remove(this);
    }
    this_idx = &next[next_idx];
  }

}


/*** DEPENDENCIES:
static void cmdq_remove(struct cmdq_item *item)
{
  if ((item->shared != 0) && ((--item->shared->references) == 0))
  {
    if (item->shared->formats != 0)
    {
      format_free(item->shared->formats);
    }
    free(item->shared);
  }
  if (item->client != 0)
  {
    server_client_unref(item->client);
  }
  if (item->type == CMDQ_COMMAND)
  {
    cmd_list_free(item->cmdlist);
  }
  do
  {
    if (item->entry.tqe_next != 0)
    {
      item->entry.tqe_next->entry.tqe_prev = item->entry.tqe_prev;
    }
    else
      item->queue->tqh_last = item->entry.tqe_prev;
    *item->entry.tqe_prev = item->entry.tqe_next;
    ;
    ;
  }
  while (0);
  free((void *) item->name);
  free(item);
}


----------------------------
None
----------------------------
***/


static enum cmd_retval cmdq_fire_callback(struct cmdq_item *item)
{
  return item->cb(item, item->data);
}


/*** DEPENDENCIES:
enum cmd_retval
{
  CMD_RETURN_ERROR = -1,
  CMD_RETURN_NORMAL = 0,
  CMD_RETURN_WAIT,
  CMD_RETURN_STOP
}
----------------------------
None
----------------------------
***/


static enum cmd_retval cmdq_find_flag(struct cmdq_item *item, struct cmd_find_state *fs, const struct cmd_entry_flag *flag)
{
  const char *value;
  unsigned int value_idx = 0;
  if (flag->flag == 0)
  {
    cmd_find_clear_state(fs, 0);
    return CMD_RETURN_NORMAL;
  }
  value_idx = args_get(item->cmd->args, flag->flag);
  if (cmd_find_target(fs, item, value, flag->type, flag->flags) != 0)
  {
    cmd_find_clear_state(fs, 0);
    return CMD_RETURN_ERROR;
  }
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
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
enum cmd_retval
{
  CMD_RETURN_ERROR = -1,
  CMD_RETURN_NORMAL = 0,
  CMD_RETURN_WAIT,
  CMD_RETURN_STOP
}
----------------------------
void cmd_find_clear_state(struct cmd_find_state *fs, int flags)
{
  memset(fs, 0, sizeof(*fs));
  fs->flags = flags;
  fs->idx = -1;
}


----------------------------
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


----------------------------
None
----------------------------
***/


void cmdq_guard(struct cmdq_item *item, const char *guard, int flags)
{
  struct client *c = item->client;
  if ((c == 0) || (!(c->flags & 0x2000)))
  {
    return;
  }
  evbuffer_add_printf(c->stdout_data, "%%%s %ld %u %d\n", guard, (long) item->time, item->number, flags);
  server_client_push_stdout(c);
}


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
***/


static enum cmd_retval cmdq_fire_command(struct cmdq_item *item)
{
  struct client *c = item->client;
  struct cmd *cmd = item->cmd;
  const struct cmd_entry *entry = cmd->entry;
  enum cmd_retval retval;
  struct cmd_find_state *fsp;
  unsigned int fsp_idx = 0;
  struct cmd_find_state fs;
  int flags;
  flags = !(!(cmd->flags & 0x1));
  cmdq_guard(item, "begin", flags);
  if (item->client == 0)
  {
    item->client = cmd_find_client(item, 0, 1);
  }
  retval = cmdq_find_flag(item, &item->source, &entry->source);
  if (retval == CMD_RETURN_ERROR)
  {
    goto out;
  }
  retval = cmdq_find_flag(item, &item->target, &entry->target);
  if (retval == CMD_RETURN_ERROR)
  {
    goto out;
  }
  retval = entry->exec(cmd, item);
  if (retval == CMD_RETURN_ERROR)
  {
    goto out;
  }
  if (entry->flags & 0x4)
  {
    if (cmd_find_valid_state(&item->target))
    {
      fsp_idx = &item->target;
    }
    else
      if (cmd_find_valid_state(&item->shared->current))
    {
      fsp_idx = &item->shared->current;
    }
    else
      if (cmd_find_from_client(&fs, item->client, 0) == 0)
    {
      fsp_idx = &fs;
    }
    else
      goto out;
    hooks_insert(fsp->s->hooks, item, fsp, "after-%s", entry->name);
  }
  out:
  item->client = c;

  if (retval == CMD_RETURN_ERROR)
  {
    cmdq_guard(item, "error", flags);
  }
  else
    cmdq_guard(item, "end", flags);
  return retval;
}


/*** DEPENDENCIES:
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
enum cmd_retval
{
  CMD_RETURN_ERROR = -1,
  CMD_RETURN_NORMAL = 0,
  CMD_RETURN_WAIT,
  CMD_RETURN_STOP
}
----------------------------
static enum cmd_retval cmdq_find_flag(struct cmdq_item *item, struct cmd_find_state *fs, const struct cmd_entry_flag *flag)
{
  const char *value;
  unsigned int value_idx = 0;
  if (flag->flag == 0)
  {
    cmd_find_clear_state(fs, 0);
    return CMD_RETURN_NORMAL;
  }
  value_idx = args_get(item->cmd->args, flag->flag);
  if (cmd_find_target(fs, item, value, flag->type, flag->flags) != 0)
  {
    cmd_find_clear_state(fs, 0);
    return CMD_RETURN_ERROR;
  }
  return CMD_RETURN_NORMAL;
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
void hooks_insert(struct hooks *hooks, struct cmdq_item *item, struct cmd_find_state *fs, const char *fmt, ...)
{
  struct hook *hook;
  unsigned int hook_idx = 0;
  va_list ap;
  char *name;
  struct cmdq_item *new_item;
  unsigned int new_item_idx = 0;
  if (item->flags & 0x4)
  {
    return;
  }
  __builtin_va_start(ap);
  xvasprintf(&name, fmt, ap);
  ;
  hook_idx = hooks_find(hooks, name);
  if ((&hook[hook_idx]) == 0)
  {
    free(name);
    return;
  }
  log_debug("running hook %s (parent %p)", name, item);
  new_item_idx = cmdq_get_command(hook->cmdlist, fs, 0, 0x4);
  cmdq_format(new_item, "hook", "%s", name);
  if (item != 0)
  {
    cmdq_insert_after(item, new_item);
  }
  else
    cmdq_append(0, new_item);
  free(name);
}


----------------------------
void cmdq_guard(struct cmdq_item *item, const char *guard, int flags)
{
  struct client *c = item->client;
  if ((c == 0) || (!(c->flags & 0x2000)))
  {
    return;
  }
  evbuffer_add_printf(c->stdout_data, "%%%s %ld %u %d\n", guard, (long) item->time, item->number, flags);
  server_client_push_stdout(c);
}


----------------------------
None
----------------------------
***/


// hint:  ['retval_ref is a mutable refrence to ', 'items_ref is a mutable refrence to u_int', 'number_ref is a mutable refrence to u_int']
void helper_helper_cmdq_next_1_1(enum cmd_retval * const retval_ref, u_int * const items_ref, static u_int * const number_ref, struct cmdq_item * const item)
{
  enum cmd_retval retval = *retval_ref;
  u_int items = *items_ref;
  static u_int number = *number_ref;
  item->time = time(0);
  number += 1;
  item->number = number;
  switch (item->type)
  {
    case CMDQ_COMMAND:
    {
      retval = cmdq_fire_command(item);
      if (retval == CMD_RETURN_ERROR)
      {
        cmdq_remove_group(item);
      }
      break;
    }

    case CMDQ_CALLBACK:
    {
      retval = cmdq_fire_callback(item);
      break;
    }

    default:
    {
      retval = CMD_RETURN_ERROR;
      break;
    }

  }

  item->flags |= 0x1;
  if (retval == CMD_RETURN_WAIT)
  {
    item->flags |= 0x2;
    goto waiting;
  }
  items += 1;
  *retval_ref = retval;
  *items_ref = items;
  *number_ref = number;
}


/*** DEPENDENCIES:
static void cmdq_remove_group(struct cmdq_item *item)
{
  struct cmdq_item *this;
  unsigned int this_idx = 0;
  struct cmdq_item *next;
  unsigned int next_idx = 0;
  this_idx = item->entry.tqe_next;
  while ((&this[this_idx]) != 0)
  {
    next_idx = this->entry.tqe_next;
    if (this->group == item->group)
    {
      cmdq_remove(this);
    }
    this_idx = &next[next_idx];
  }

}


----------------------------
pub time: Time
----------------------------
static enum cmd_retval cmdq_fire_callback(struct cmdq_item *item)
{
  return item->cb(item, item->data);
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
static enum cmd_retval cmdq_fire_command(struct cmdq_item *item)
{
  struct client *c = item->client;
  struct cmd *cmd = item->cmd;
  const struct cmd_entry *entry = cmd->entry;
  enum cmd_retval retval;
  struct cmd_find_state *fsp;
  unsigned int fsp_idx = 0;
  struct cmd_find_state fs;
  int flags;
  flags = !(!(cmd->flags & 0x1));
  cmdq_guard(item, "begin", flags);
  if (item->client == 0)
  {
    item->client = cmd_find_client(item, 0, 1);
  }
  retval = cmdq_find_flag(item, &item->source, &entry->source);
  if (retval == CMD_RETURN_ERROR)
  {
    goto out;
  }
  retval = cmdq_find_flag(item, &item->target, &entry->target);
  if (retval == CMD_RETURN_ERROR)
  {
    goto out;
  }
  retval = entry->exec(cmd, item);
  if (retval == CMD_RETURN_ERROR)
  {
    goto out;
  }
  if (entry->flags & 0x4)
  {
    if (cmd_find_valid_state(&item->target))
    {
      fsp_idx = &item->target;
    }
    else
      if (cmd_find_valid_state(&item->shared->current))
    {
      fsp_idx = &item->shared->current;
    }
    else
      if (cmd_find_from_client(&fs, item->client, 0) == 0)
    {
      fsp_idx = &fs;
    }
    else
      goto out;
    hooks_insert(fsp->s->hooks, item, fsp, "after-%s", entry->name);
  }
  out:
  item->client = c;

  if (retval == CMD_RETURN_ERROR)
  {
    cmdq_guard(item, "error", flags);
  }
  else
    cmdq_guard(item, "end", flags);
  return retval;
}


----------------------------
None
----------------------------
***/


// hint:  ['item_idx_ref is a mutable refrence to unsigned int', 'retval_ref is a mutable refrence to ', 'items_ref is a mutable refrence to u_int', 'number_ref is a mutable refrence to u_int']
void helper_cmdq_next_1(unsigned int * const item_idx_ref, enum cmd_retval * const retval_ref, u_int * const items_ref, static u_int * const number_ref, struct cmdq_list * const queue, const char * const name, struct cmdq_item * const item)
{
  unsigned int item_idx = *item_idx_ref;
  enum cmd_retval retval = *retval_ref;
  u_int items = *items_ref;
  static u_int number = *number_ref;
  item_idx = queue->tqh_first;
  if ((&item[item_idx]) == 0)
  {
    break;
  }
  log_debug("%s %s: %s (%d), flags %x", __func__, name, item->name, item->type, item->flags);
  if (item->flags & 0x2)
  {
    goto waiting;
  }
  if ((~item->flags) & 0x1)
  {
    helper_helper_cmdq_next_1_1(&retval, &items, &number, item);
  }
  cmdq_remove(item);
  *item_idx_ref = item_idx;
  *retval_ref = retval;
  *items_ref = items;
  *number_ref = number;
}


/*** DEPENDENCIES:
static void cmdq_remove(struct cmdq_item *item)
{
  if ((item->shared != 0) && ((--item->shared->references) == 0))
  {
    if (item->shared->formats != 0)
    {
      format_free(item->shared->formats);
    }
    free(item->shared);
  }
  if (item->client != 0)
  {
    server_client_unref(item->client);
  }
  if (item->type == CMDQ_COMMAND)
  {
    cmd_list_free(item->cmdlist);
  }
  do
  {
    if (item->entry.tqe_next != 0)
    {
      item->entry.tqe_next->entry.tqe_prev = item->entry.tqe_prev;
    }
    else
      item->queue->tqh_last = item->entry.tqe_prev;
    *item->entry.tqe_prev = item->entry.tqe_next;
    ;
    ;
  }
  while (0);
  free((void *) item->name);
  free(item);
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
void helper_helper_cmdq_next_1_1(enum cmd_retval * const retval_ref, u_int * const items_ref, static u_int * const number_ref, struct cmdq_item * const item)
{
  enum cmd_retval retval = *retval_ref;
  u_int items = *items_ref;
  static u_int number = *number_ref;
  item->time = time(0);
  number += 1;
  item->number = number;
  switch (item->type)
  {
    case CMDQ_COMMAND:
    {
      retval = cmdq_fire_command(item);
      if (retval == CMD_RETURN_ERROR)
      {
        cmdq_remove_group(item);
      }
      break;
    }

    case CMDQ_CALLBACK:
    {
      retval = cmdq_fire_callback(item);
      break;
    }

    default:
    {
      retval = CMD_RETURN_ERROR;
      break;
    }

  }

  item->flags |= 0x1;
  if (retval == CMD_RETURN_WAIT)
  {
    item->flags |= 0x2;
    goto waiting;
  }
  items += 1;
  *retval_ref = retval;
  *items_ref = items;
  *number_ref = number;
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


u_int cmdq_next(struct client *c)
{
  struct cmdq_list *queue = cmdq_get(c);
  const char *name = cmdq_name(c);
  struct cmdq_item *item;
  unsigned int item_idx = 0;
  enum cmd_retval retval;
  u_int items = 0;
  static u_int number;
  if (queue->tqh_first == 0)
  {
    log_debug("%s %s: empty", __func__, name);
    return 0;
  }
  if (queue->tqh_first->flags & 0x2)
  {
    log_debug("%s %s: waiting", __func__, name);
    return 0;
  }
  log_debug("%s %s: enter", __func__, name);
  for (;;)
  {
    helper_cmdq_next_1(&item_idx, &retval, &items, &number, queue, name, item);
  }

  log_debug("%s %s: exit (empty)", __func__, name);
  return items;
  waiting:
  log_debug("%s %s: exit (wait)", __func__, name);

  return items;
}


/*** DEPENDENCIES:
enum cmd_retval
{
  CMD_RETURN_ERROR = -1,
  CMD_RETURN_NORMAL = 0,
  CMD_RETURN_WAIT,
  CMD_RETURN_STOP
}
----------------------------
static const char *cmdq_name(struct client *c)
{
  static char s[32];
  if (c == 0)
  {
    return "<global>";
  }
  xsnprintf(s, sizeof(s), "<%p>", c);
  return s;
}


----------------------------
void helper_cmdq_next_1(unsigned int * const item_idx_ref, enum cmd_retval * const retval_ref, u_int * const items_ref, static u_int * const number_ref, struct cmdq_list * const queue, const char * const name, struct cmdq_item * const item)
{
  unsigned int item_idx = *item_idx_ref;
  enum cmd_retval retval = *retval_ref;
  u_int items = *items_ref;
  static u_int number = *number_ref;
  item_idx = queue->tqh_first;
  if ((&item[item_idx]) == 0)
  {
    break;
  }
  log_debug("%s %s: %s (%d), flags %x", __func__, name, item->name, item->type, item->flags);
  if (item->flags & 0x2)
  {
    goto waiting;
  }
  if ((~item->flags) & 0x1)
  {
    helper_helper_cmdq_next_1_1(&retval, &items, &number, item);
  }
  cmdq_remove(item);
  *item_idx_ref = item_idx;
  *retval_ref = retval;
  *items_ref = items;
  *number_ref = number;
}


----------------------------
static struct cmdq_list *cmdq_get(struct client *c)
{
  if (c == 0)
  {
    return &global_queue;
  }
  return &c->queue;
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


