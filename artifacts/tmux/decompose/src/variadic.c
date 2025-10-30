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


/*** DEPENDENCIES:
void log_vwrite(const char *msg, va_list ap)
{
  char *fmt;
  char *out;
  struct timeval tv;
  if (log_file == 0)
  {
    return;
  }
  if (vasprintf(&fmt, msg, ap) == (-1))
  {
    exit(1);
  }
  if (stravis(&out, fmt, ((0x01 | 0x02) | 0x08) | 0x10) == (-1))
  {
    exit(1);
  }
  gettimeofday(&tv, 0);
  if (fprintf(log_file, "%lld.%06d %s\n", (long long) tv.tv_sec, (int) tv.tv_usec, out) == (-1))
  {
    exit(1);
  }
  fflush(log_file);
  free(out);
  free(fmt);
}


----------------------------
***/


void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


/*** DEPENDENCIES:
void log_vwrite(const char *msg, va_list ap)
{
  char *fmt;
  char *out;
  struct timeval tv;
  if (log_file == 0)
  {
    return;
  }
  if (vasprintf(&fmt, msg, ap) == (-1))
  {
    exit(1);
  }
  if (stravis(&out, fmt, ((0x01 | 0x02) | 0x08) | 0x10) == (-1))
  {
    exit(1);
  }
  gettimeofday(&tv, 0);
  if (fprintf(log_file, "%lld.%06d %s\n", (long long) tv.tv_sec, (int) tv.tv_usec, out) == (-1))
  {
    exit(1);
  }
  fflush(log_file);
  free(out);
  free(fmt);
}


----------------------------
***/


int xasprintf(char **ret, const char *fmt, ...)
{
  va_list ap;
  int i;
  __builtin_va_start(ap);
  i = xvasprintf(ret, fmt, ap);
  ;
  return i;
}


/*** DEPENDENCIES:
int xvasprintf(char **ret, const char *fmt, va_list ap)
{
  int i;
  i = vasprintf(ret, fmt, ap);
  if ((i < 0) || ((*ret) == 0))
  {
    fatalx("xasprintf: %s", strerror(errno));
  }
  return i;
}


----------------------------
***/


void control_write(struct client *c, const char *fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  evbuffer_add_vprintf(c->stdout_data, fmt, ap);
  ;
  evbuffer_add(c->stdout_data, "\n", 1);
  server_client_push_stdout(c);
}


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
int xvasprintf(char **ret, const char *fmt, va_list ap)
{
  int i;
  i = vasprintf(ret, fmt, ap);
  if ((i < 0) || ((*ret) == 0))
  {
    fatalx("xasprintf: %s", strerror(errno));
  }
  return i;
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
None
----------------------------
***/


void cmdq_format(struct cmdq_item *item, const char *key, const char *fmt, ...)
{
  struct cmdq_shared *shared = item->shared;
  va_list ap;
  char *value;
  __builtin_va_start(ap);
  xvasprintf(&value, fmt, ap);
  ;
  if (shared->formats == 0)
  {
    shared->formats = format_create(0, 0, 0, 0);
  }
  format_add(shared->formats, key, "%s", value);
  free(value);
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
int xvasprintf(char **ret, const char *fmt, va_list ap)
{
  int i;
  i = vasprintf(ret, fmt, ap);
  if ((i < 0) || ((*ret) == 0))
  {
    fatalx("xasprintf: %s", strerror(errno));
  }
  return i;
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
None
----------------------------
***/


int xsnprintf(char *str, size_t len, const char *fmt, ...)
{
  va_list ap;
  int i;
  __builtin_va_start(ap);
  i = xvsnprintf(str, len, fmt, ap);
  ;
  return i;
}


/*** DEPENDENCIES:
int xvsnprintf(char *str, size_t len, const char *fmt, va_list ap)
{
  int i;
  if (len > 2147483647)
  {
    fatalx("xsnprintf: len > INT_MAX");
  }
  i = vsnprintf(str, len, fmt, ap);
  if ((i < 0) || (i >= ((int) len)))
  {
    fatalx("xsnprintf: overflow");
  }
  return i;
}


----------------------------
***/


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


/*** DEPENDENCIES:
int xvasprintf(char **ret, const char *fmt, va_list ap)
{
  int i;
  i = vasprintf(ret, fmt, ap);
  if ((i < 0) || ((*ret) == 0))
  {
    fatalx("xasprintf: %s", strerror(errno));
  }
  return i;
}


----------------------------
struct environ_entry *environ_RB_INSERT(struct environ *head, struct environ_entry *elm)
{
  struct environ_entry *tmp;
  unsigned int tmp_idx = 0;
  struct environ_entry *parent = 0;
  unsigned int parent_idx = 0;
  int comp = 0;
  tmp_idx = head->rbh_root;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    comp = environ_cmp(elm, parent);
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
  environ_RB_INSERT_COLOR(head, elm);
  return 0;
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


/*** DEPENDENCIES:
void log_vwrite(const char *msg, va_list ap)
{
  char *fmt;
  char *out;
  struct timeval tv;
  if (log_file == 0)
  {
    return;
  }
  if (vasprintf(&fmt, msg, ap) == (-1))
  {
    exit(1);
  }
  if (stravis(&out, fmt, ((0x01 | 0x02) | 0x08) | 0x10) == (-1))
  {
    exit(1);
  }
  gettimeofday(&tv, 0);
  if (fprintf(log_file, "%lld.%06d %s\n", (long long) tv.tv_sec, (int) tv.tv_usec, out) == (-1))
  {
    exit(1);
  }
  fflush(log_file);
  free(out);
  free(fmt);
}


----------------------------
***/


void setproctitle(const char *fmt, ...)
{
}


/*** DEPENDENCIES:
***/


void server_client_add_message(struct client *c, const char *fmt, ...)
{
  struct message_entry *msg;
  unsigned int msg_idx = 0;
  struct message_entry *msg1;
  unsigned int msg1_idx = 0;
  char *s;
  va_list ap;
  u_int limit;
  __builtin_va_start(ap);
  xvasprintf(&s, fmt, ap);
  ;
  log_debug("message %s (client %p)", s, c);
  msg_idx = xcalloc(1, sizeof(*msg_idx));
  msg->msg_time = time(0);
  msg->msg_num = c->message_next++;
  msg->msg = s;
  do
  {
    msg->entry.tqe_next = 0;
    msg->entry.tqe_prev = (&c->message_log)->tqh_last;
    *(&c->message_log)->tqh_last = &msg[msg_idx];
    (&c->message_log)->tqh_last = &msg->entry.tqe_next;
  }
  while (0);
  limit = options_get_number(global_options, "message-limit");
  for (msg_idx = (&c->message_log)->tqh_first; ((&msg[msg_idx]) != 0) && ((msg1_idx = msg->entry.tqe_next, 1)); msg_idx = &msg1[msg1_idx])
  {
    if ((msg->msg_num + limit) >= c->message_next)
    {
      break;
    }
    free(msg->msg);
    do
    {
      if (msg->entry.tqe_next != 0)
      {
        msg->entry.tqe_next->entry.tqe_prev = msg->entry.tqe_prev;
      }
      else
        (&c->message_log)->tqh_last = msg->entry.tqe_prev;
      *msg->entry.tqe_prev = msg->entry.tqe_next;
      ;
      ;
    }
    while (0);
    free(msg);
  }

}


/*** DEPENDENCIES:
int xvasprintf(char **ret, const char *fmt, va_list ap)
{
  int i;
  i = vasprintf(ret, fmt, ap);
  if ((i < 0) || ((*ret) == 0))
  {
    fatalx("xasprintf: %s", strerror(errno));
  }
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
pub time: Time
----------------------------
struct message_entry
{
  char *msg;
  u_int msg_num;
  time_t msg_time;
  struct 
  {
    struct message_entry *tqe_next;
    struct message_entry **tqe_prev;
  } entry;
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


void status_message_set(struct client *c, const char *fmt, ...)
{
  struct timeval tv;
  va_list ap;
  int delay;
  status_message_clear(c);
  if (c->status.old_status == 0)
  {
    c->status.old_status = xmalloc(sizeof(*c->status.old_status));
    memcpy(c->status.old_status, &c->status.status, sizeof(*c->status.old_status));
    screen_init(&c->status.status, c->tty.sx, 1, 0);
  }
  __builtin_va_start(ap);
  xvasprintf(&c->message_string, fmt, ap);
  ;
  server_client_add_message(c, "%s", c->message_string);
  delay = options_get_number(c->session->options, "display-time");
  if (delay > 0)
  {
    tv.tv_sec = delay / 1000;
    tv.tv_usec = (delay % 1000) * 1000L;
    if (event_initialized(&c->message_timer))
    {
      evtimer_del(&c->message_timer);
    }
    evtimer_set(&c->message_timer, status_message_callback, c);
    evtimer_add(&c->message_timer, &tv);
  }
  c->tty.flags |= 0x1 | 0x2;
  c->flags |= 0x10;
}


/*** DEPENDENCIES:
int xvasprintf(char **ret, const char *fmt, va_list ap)
{
  int i;
  i = vasprintf(ret, fmt, ap);
  if ((i < 0) || ((*ret) == 0))
  {
    fatalx("xasprintf: %s", strerror(errno));
  }
  return i;
}


----------------------------
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
void status_message_clear(struct client *c)
{
  if (c->message_string == 0)
  {
    return;
  }
  free(c->message_string);
  c->message_string = 0;
  if (c->prompt_string == 0)
  {
    c->tty.flags &= ~(0x1 | 0x2);
  }
  c->flags |= 0x8;
  screen_reinit(&c->status.status);
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
void server_client_add_message(struct client *c, const char *fmt, ...)
{
  struct message_entry *msg;
  unsigned int msg_idx = 0;
  struct message_entry *msg1;
  unsigned int msg1_idx = 0;
  char *s;
  va_list ap;
  u_int limit;
  __builtin_va_start(ap);
  xvasprintf(&s, fmt, ap);
  ;
  log_debug("message %s (client %p)", s, c);
  msg_idx = xcalloc(1, sizeof(*msg_idx));
  msg->msg_time = time(0);
  msg->msg_num = c->message_next++;
  msg->msg = s;
  do
  {
    msg->entry.tqe_next = 0;
    msg->entry.tqe_prev = (&c->message_log)->tqh_last;
    *(&c->message_log)->tqh_last = &msg[msg_idx];
    (&c->message_log)->tqh_last = &msg->entry.tqe_next;
  }
  while (0);
  limit = options_get_number(global_options, "message-limit");
  for (msg_idx = (&c->message_log)->tqh_first; ((&msg[msg_idx]) != 0) && ((msg1_idx = msg->entry.tqe_next, 1)); msg_idx = &msg1[msg1_idx])
  {
    if ((msg->msg_num + limit) >= c->message_next)
    {
      break;
    }
    free(msg->msg);
    do
    {
      if (msg->entry.tqe_next != 0)
      {
        msg->entry.tqe_next->entry.tqe_prev = msg->entry.tqe_prev;
      }
      else
        (&c->message_log)->tqh_last = msg->entry.tqe_prev;
      *msg->entry.tqe_prev = msg->entry.tqe_next;
      ;
      ;
    }
    while (0);
    free(msg);
  }

}


----------------------------
void status_message_callback(int fd, short event, void *data)
{
  struct client *c = data;
  status_message_clear(c);
}


----------------------------
None
----------------------------
***/


void args_print_add(char **buf, size_t *len, const char *fmt, ...)
{
  va_list ap;
  char *s;
  size_t slen;
  __builtin_va_start(ap);
  slen = xvasprintf(&s, fmt, ap);
  ;
  *len += slen;
  *buf = xrealloc(*buf, *len);
  strlcat(*buf, s, *len);
  free(s);
}


/*** DEPENDENCIES:
int xvasprintf(char **ret, const char *fmt, va_list ap)
{
  int i;
  i = vasprintf(ret, fmt, ap);
  if ((i < 0) || ((*ret) == 0))
  {
    fatalx("xasprintf: %s", strerror(errno));
  }
  return i;
}


----------------------------
void *xrealloc(void *ptr, size_t size)
{
  return xreallocarray(ptr, 1, size);
}


----------------------------
***/


void input_reply(struct input_ctx *ictx, const char *fmt, ...)
{
  va_list ap;
  char *reply;
  __builtin_va_start(ap);
  xvasprintf(&reply, fmt, ap);
  ;
  bufferevent_write(ictx->wp->event, reply, strlen(reply));
  free(reply);
}


/*** DEPENDENCIES:
int xvasprintf(char **ret, const char *fmt, va_list ap)
{
  int i;
  i = vasprintf(ret, fmt, ap);
  if ((i < 0) || ((*ret) == 0))
  {
    fatalx("xasprintf: %s", strerror(errno));
  }
  return i;
}


----------------------------
None
----------------------------
***/


void cfg_add_cause(const char *fmt, ...)
{
  va_list ap;
  char *msg;
  __builtin_va_start(ap);
  xvasprintf(&msg, fmt, ap);
  ;
  cfg_ncauses += 1;
  cfg_causes = xreallocarray(cfg_causes, cfg_ncauses, sizeof(*cfg_causes));
  cfg_causes[cfg_ncauses - 1] = msg;
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
int xvasprintf(char **ret, const char *fmt, va_list ap)
{
  int i;
  i = vasprintf(ret, fmt, ap);
  if ((i < 0) || ((*ret) == 0))
  {
    fatalx("xasprintf: %s", strerror(errno));
  }
  return i;
}


----------------------------
extern char **cfg_causes
----------------------------
extern u_int cfg_ncauses
----------------------------
***/


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


/*** DEPENDENCIES:
int xvasprintf(char **ret, const char *fmt, va_list ap)
{
  int i;
  i = vasprintf(ret, fmt, ap);
  if ((i < 0) || ((*ret) == 0))
  {
    fatalx("xasprintf: %s", strerror(errno));
  }
  return i;
}


----------------------------
void cfg_add_cause(const char *fmt, ...)
{
  va_list ap;
  char *msg;
  __builtin_va_start(ap);
  xvasprintf(&msg, fmt, ap);
  ;
  cfg_ncauses += 1;
  cfg_causes = xreallocarray(cfg_causes, cfg_ncauses, sizeof(*cfg_causes));
  cfg_causes[cfg_ncauses - 1] = msg;
}


----------------------------
char *utf8_sanitize(const char *src)
{
  unsigned int src_idx = 0;
  char *dst;
  unsigned int dst_idx = 0;
  size_t n;
  enum utf8_state more;
  struct utf8_data ud;
  u_int i;
  dst_idx = 0;
  n = 0;
  while (src[src_idx] != '\0')
  {
    dst_idx = xreallocarray(dst_idx, n + 1, sizeof(*dst_idx));
    if ((more = utf8_open(&ud, *(&src[src_idx]))) == UTF8_MORE)
    {
      while (((*(++(&src[src_idx]))) != '\0') && (more == UTF8_MORE))
      {
        more = utf8_append(&ud, *(&src[src_idx]));
      }

      if (more == UTF8_DONE)
      {
        dst_idx = xreallocarray(dst_idx, n + ud.width, sizeof(*dst_idx));
        for (i = 0; i < ud.width; i += 1)
        {
          dst[n + dst_idx] = '_';
          n += 1;
        }

        continue;
      }
      src_idx -= ud.have;
    }
    if ((src[src_idx] > 0x1f) && (src[src_idx] < 0x7f))
    {
      dst[n + dst_idx] = src[src_idx];
      n += 1;
    }
    else
      dst[n + dst_idx] = '_';
    n += 1;
    src_idx += 1;
  }

  dst_idx = xreallocarray(dst_idx, n + 1, sizeof(*dst_idx));
  dst[n + dst_idx] = '\0';
  return dst;
}


----------------------------
void status_message_set(struct client *c, const char *fmt, ...)
{
  struct timeval tv;
  va_list ap;
  int delay;
  status_message_clear(c);
  if (c->status.old_status == 0)
  {
    c->status.old_status = xmalloc(sizeof(*c->status.old_status));
    memcpy(c->status.old_status, &c->status.status, sizeof(*c->status.old_status));
    screen_init(&c->status.status, c->tty.sx, 1, 0);
  }
  __builtin_va_start(ap);
  xvasprintf(&c->message_string, fmt, ap);
  ;
  server_client_add_message(c, "%s", c->message_string);
  delay = options_get_number(c->session->options, "display-time");
  if (delay > 0)
  {
    tv.tv_sec = delay / 1000;
    tv.tv_usec = (delay % 1000) * 1000L;
    if (event_initialized(&c->message_timer))
    {
      evtimer_del(&c->message_timer);
    }
    evtimer_set(&c->message_timer, status_message_callback, c);
    evtimer_add(&c->message_timer, &tv);
  }
  c->tty.flags |= 0x1 | 0x2;
  c->flags |= 0x10;
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


size_t screen_write_strlen(const char *fmt, ...)
{
  va_list ap;
  char *msg;
  struct utf8_data ud;
  u_char *ptr;
  unsigned int ptr_idx = 0;
  size_t left;
  size_t size = 0;
  enum utf8_state more;
  __builtin_va_start(ap);
  xvasprintf(&msg, fmt, ap);
  ;
  ptr_idx = msg;
  while (ptr[ptr_idx] != '\0')
  {
    if ((ptr[ptr_idx] > 0x7f) && (utf8_open(&ud, *(&ptr[ptr_idx])) == UTF8_MORE))
    {
      ptr_idx += 1;
      left = strlen(ptr);
      if (left < (((size_t) ud.size) - 1))
      {
        break;
      }
      while ((more = utf8_append(&ud, *(&ptr[ptr_idx]))) == UTF8_MORE)
      {
        ptr_idx += 1;
      }

      ptr_idx += 1;
      if (more == UTF8_DONE)
      {
        size += ud.width;
      }
    }
    else
    {
      if ((ptr[ptr_idx] > 0x1f) && (ptr[ptr_idx] < 0x7f))
      {
        size += 1;
      }
      ptr_idx += 1;
    }
  }

  free(msg);
  return size;
}


/*** DEPENDENCIES:
int xvasprintf(char **ret, const char *fmt, va_list ap)
{
  int i;
  i = vasprintf(ret, fmt, ap);
  if ((i < 0) || ((*ret) == 0))
  {
    fatalx("xasprintf: %s", strerror(errno));
  }
  return i;
}


----------------------------
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
}
----------------------------
enum utf8_state utf8_open(struct utf8_data *ud, u_char ch)
{
  memset(ud, 0, sizeof(*ud));
  if ((ch >= 0xc2) && (ch <= 0xdf))
  {
    ud->size = 2;
  }
  else
    if ((ch >= 0xe0) && (ch <= 0xef))
  {
    ud->size = 3;
  }
  else
    if ((ch >= 0xf0) && (ch <= 0xf4))
  {
    ud->size = 4;
  }
  else
    return UTF8_ERROR;
  utf8_append(ud, ch);
  return UTF8_MORE;
}


----------------------------
enum utf8_state
{
  UTF8_MORE,
  UTF8_DONE,
  UTF8_ERROR
}
----------------------------
enum utf8_state utf8_append(struct utf8_data *ud, u_char ch)
{
  wchar_t wc;
  int width;
  if (ud->have >= ud->size)
  {
    fatalx("UTF-8 character overflow");
  }
  if (ud->size > (sizeof(ud->data)))
  {
    fatalx("UTF-8 character size too large");
  }
  if ((ud->have != 0) && ((ch & 0xc0) != 0x80))
  {
    ud->width = 0xff;
  }
  ud->data[ud->have++] = ch;
  if (ud->have != ud->size)
  {
    return UTF8_MORE;
  }
  if (ud->width == 0xff)
  {
    return UTF8_ERROR;
  }
  if (utf8_combine(ud, &wc) != UTF8_DONE)
  {
    return UTF8_ERROR;
  }
  if ((width = utf8_width(wc)) < 0)
  {
    return UTF8_ERROR;
  }
  ud->width = width;
  return UTF8_DONE;
}


----------------------------
***/


void screen_write_nputs(struct screen_write_ctx *ctx, ssize_t maxlen, const struct grid_cell *gcp, const char *fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  screen_write_vnputs(ctx, maxlen, gcp, fmt, ap);
  ;
}


/*** DEPENDENCIES:
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
void screen_write_vnputs(struct screen_write_ctx *ctx, ssize_t maxlen, const struct grid_cell *gcp, const char *fmt, va_list ap)
{
  struct grid_cell gc;
  struct utf8_data *ud = &gc.data;
  char *msg;
  u_char *ptr;
  unsigned int ptr_idx = 0;
  size_t left;
  size_t size = 0;
  enum utf8_state more;
  memcpy(&gc, gcp, sizeof(gc));
  xvasprintf(&msg, fmt, ap);
  ptr_idx = msg;
  while (ptr[ptr_idx] != '\0')
  {
    helper_screen_write_vnputs_1(&gc, &ptr_idx, &left, &size, &more, ctx, maxlen, ud, ptr);
  }

  free(msg);
}


----------------------------
None
----------------------------
None
----------------------------
***/


// hint:  ['ptr_idx_ref is a mutable refrence to unsigned int', 'left_ref is a mutable refrence to size_t', 'size_ref is a mutable refrence to size_t', 'more_ref is a mutable refrence to ']
void helper_helper_screen_write_cnputs_1_1(unsigned int * const ptr_idx_ref, size_t * const left_ref, size_t * const size_ref, enum utf8_state * const more_ref, struct screen_write_ctx * const ctx, ssize_t maxlen, struct grid_cell gc, struct utf8_data * const ud, u_char * const ptr)
{
  unsigned int ptr_idx = *ptr_idx_ref;
  size_t left = *left_ref;
  size_t size = *size_ref;
  enum utf8_state more = *more_ref;
  ptr_idx += 1;
  left = strlen(ptr);
  if (left < (((size_t) ud->size) - 1))
  {
    break;
  }
  while ((more = utf8_append(ud, *(&ptr[ptr_idx]))) == UTF8_MORE)
  {
    ptr_idx += 1;
  }

  ptr_idx += 1;
  if (more != UTF8_DONE)
  {
    continue;
  }
  if ((maxlen > 0) && ((size + ud->width) > ((size_t) maxlen)))
  {
    while (size < ((size_t) maxlen))
    {
      screen_write_putc(ctx, &gc, ' ');
      size += 1;
    }

    break;
  }
  size += ud->width;
  screen_write_cell(ctx, &gc);
  *ptr_idx_ref = ptr_idx;
  *left_ref = left;
  *size_ref = size;
  *more_ref = more;
}


/*** DEPENDENCIES:
None
----------------------------
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
}
----------------------------
void screen_write_cell(struct screen_write_ctx *ctx, const struct grid_cell *gc)
{
  unsigned int gc_idx = 0;
  struct screen *s = ctx->s;
  struct grid *gd = s->grid;
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  struct grid_cell_entry *gce;
  unsigned int gce_idx = 0;
  struct grid_cell tmp_gc;
  struct grid_cell now_gc;
  struct tty_ctx ttyctx;
  u_int sx = s->grid->sx;
  u_int sy = s->grid->sy;
  u_int width = gc->data.width;
  u_int xx;
  u_int last;
  u_int cx;
  u_int cy;
  int selected;
  int skip = 1;
  if (gc->flags & 0x4)
  {
    return;
  }
  ctx->cells += 1;
  if (width == 0)
  {
    helper_screen_write_cell_1(&gc_idx, &ttyctx, &cx, &cy, ctx, gc, s, xx);
  }
  screen_write_collect_flush(ctx, 1);
  if ((((~s->mode) & 0x10) && (width > 1)) && ((width > sx) || ((s->cx != sx) && (s->cx > (sx - width)))))
  {
    return;
  }
  if (s->mode & 0x2)
  {
    grid_view_insert_cells(s->grid, s->cx, s->cy, width, 8);
    skip = 0;
  }
  if ((s->mode & 0x10) && (s->cx > (sx - width)))
  {
    log_debug("%s: wrapped at %u,%u", __func__, s->cx, s->cy);
    screen_write_linefeed(ctx, 1, 8);
    s->cx = 0;
    screen_write_collect_flush(ctx, 1);
  }
  if ((s->cx > (sx - width)) || (s->cy > (sy - 1)))
  {
    return;
  }
  screen_write_initctx(ctx, &ttyctx);
  gl_idx = &s->grid->linedata[s->grid->hsize + s->cy];
  if (gl->flags & 0x2)
  {
    grid_view_get_cell(gd, s->cx, s->cy, &now_gc);
    if (screen_write_overwrite(ctx, &now_gc, width))
    {
      skip = 0;
    }
  }
  for (xx = s->cx + 1; xx < (s->cx + width); xx += 1)
  {
    log_debug("%s: new padding at %u,%u", __func__, xx, s->cy);
    grid_view_set_cell(gd, xx, s->cy, &screen_write_pad_cell);
    skip = 0;
  }

  if (skip)
  {
    helper_screen_write_cell_2(&gce_idx, &skip, gc, s, gl, gce);
  }
  selected = screen_check_selection(s, s->cx, s->cy);
  if (selected && ((~gc->flags) & 0x10))
  {
    memcpy(&tmp_gc, gc, sizeof(tmp_gc));
    tmp_gc.flags |= 0x10;
    grid_view_set_cell(gd, s->cx, s->cy, &tmp_gc);
  }
  else
    if ((!selected) && (gc->flags & 0x10))
  {
    memcpy(&tmp_gc, gc, sizeof(tmp_gc));
    tmp_gc.flags &= ~0x10;
    grid_view_set_cell(gd, s->cx, s->cy, &tmp_gc);
  }
  else
    if (!skip)
  {
    grid_view_set_cell(gd, s->cx, s->cy, gc);
  }
  if (selected)
  {
    skip = 0;
  }
  last = !(s->mode & 0x10);
  if (s->cx <= ((sx - last) - width))
  {
    s->cx += width;
  }
  else
    s->cx = sx - last;
  if (s->mode & 0x2)
  {
    screen_write_collect_flush(ctx, 0);
    ttyctx.num = width;
    tty_write(tty_cmd_insertcharacter, &ttyctx);
  }
  if (!skip)
  {
    if (selected)
    {
      screen_select_cell(s, &tmp_gc, gc);
      ttyctx.cell = &tmp_gc;
    }
    else
      ttyctx.cell = &gc[gc_idx];
    tty_write(tty_cmd_cell, &ttyctx);
    ctx->written += 1;
  }
  else
    ctx->skipped++;
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
enum utf8_state
{
  UTF8_MORE,
  UTF8_DONE,
  UTF8_ERROR
}
----------------------------
enum utf8_state utf8_append(struct utf8_data *ud, u_char ch)
{
  wchar_t wc;
  int width;
  if (ud->have >= ud->size)
  {
    fatalx("UTF-8 character overflow");
  }
  if (ud->size > (sizeof(ud->data)))
  {
    fatalx("UTF-8 character size too large");
  }
  if ((ud->have != 0) && ((ch & 0xc0) != 0x80))
  {
    ud->width = 0xff;
  }
  ud->data[ud->have++] = ch;
  if (ud->have != ud->size)
  {
    return UTF8_MORE;
  }
  if (ud->width == 0xff)
  {
    return UTF8_ERROR;
  }
  if (utf8_combine(ud, &wc) != UTF8_DONE)
  {
    return UTF8_ERROR;
  }
  if ((width = utf8_width(wc)) < 0)
  {
    return UTF8_ERROR;
  }
  ud->width = width;
  return UTF8_DONE;
}


----------------------------
None
----------------------------
void screen_write_putc(struct screen_write_ctx *ctx, const struct grid_cell *gcp, u_char ch)
{
  struct grid_cell gc;
  memcpy(&gc, gcp, sizeof(gc));
  utf8_set(&gc.data, ch);
  screen_write_cell(ctx, &gc);
}


----------------------------
None
----------------------------
***/


// hint:  ['ptr_idx_ref is a mutable refrence to unsigned int', 'last_idx_ref is a mutable refrence to unsigned int', 'left_ref is a mutable refrence to size_t', 'size_ref is a mutable refrence to size_t', 'more_ref is a mutable refrence to ']
void helper_screen_write_cnputs_1(unsigned int * const ptr_idx_ref, unsigned int * const last_idx_ref, size_t * const left_ref, size_t * const size_ref, enum utf8_state * const more_ref, struct screen_write_ctx * const ctx, ssize_t maxlen, const struct grid_cell * const gcp, struct grid_cell gc, struct utf8_data * const ud, u_char * const ptr, u_char * const last)
{
  unsigned int ptr_idx = *ptr_idx_ref;
  unsigned int last_idx = *last_idx_ref;
  size_t left = *left_ref;
  size_t size = *size_ref;
  enum utf8_state more = *more_ref;
  if ((ptr[0 + ptr_idx] == '#') && (ptr[1 + ptr_idx] == '['))
  {
    ptr_idx += 2;
    last_idx = (&ptr[ptr_idx]) + strcspn(ptr, "]");
    if (last[last_idx] == '\0')
    {
      break;
    }
    last[last_idx] = '\0';
    style_parse(gcp, &gc, ptr);
    ptr_idx = (&last[last_idx]) + 1;
    continue;
  }
  if ((ptr[ptr_idx] > 0x7f) && (utf8_open(ud, *(&ptr[ptr_idx])) == UTF8_MORE))
  {
    helper_helper_screen_write_cnputs_1_1(&ptr_idx, &left, &size, &more, ctx, maxlen, gc, ud, ptr);
  }
  else
  {
    if ((maxlen > 0) && ((size + 1) > ((size_t) maxlen)))
    {
      break;
    }
    if ((ptr[ptr_idx] > 0x1f) && (ptr[ptr_idx] < 0x7f))
    {
      size += 1;
      screen_write_putc(ctx, &gc, *(&ptr[ptr_idx]));
    }
    ptr_idx += 1;
  }
  *ptr_idx_ref = ptr_idx;
  *last_idx_ref = last_idx;
  *left_ref = left;
  *size_ref = size;
  *more_ref = more;
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
None
----------------------------
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
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
enum utf8_state utf8_open(struct utf8_data *ud, u_char ch)
{
  memset(ud, 0, sizeof(*ud));
  if ((ch >= 0xc2) && (ch <= 0xdf))
  {
    ud->size = 2;
  }
  else
    if ((ch >= 0xe0) && (ch <= 0xef))
  {
    ud->size = 3;
  }
  else
    if ((ch >= 0xf0) && (ch <= 0xf4))
  {
    ud->size = 4;
  }
  else
    return UTF8_ERROR;
  utf8_append(ud, ch);
  return UTF8_MORE;
}


----------------------------
enum utf8_state
{
  UTF8_MORE,
  UTF8_DONE,
  UTF8_ERROR
}
----------------------------
None
----------------------------
void screen_write_putc(struct screen_write_ctx *ctx, const struct grid_cell *gcp, u_char ch)
{
  struct grid_cell gc;
  memcpy(&gc, gcp, sizeof(gc));
  utf8_set(&gc.data, ch);
  screen_write_cell(ctx, &gc);
}


----------------------------
void helper_helper_screen_write_cnputs_1_1(unsigned int * const ptr_idx_ref, size_t * const left_ref, size_t * const size_ref, enum utf8_state * const more_ref, struct screen_write_ctx * const ctx, ssize_t maxlen, struct grid_cell gc, struct utf8_data * const ud, u_char * const ptr)
{
  unsigned int ptr_idx = *ptr_idx_ref;
  size_t left = *left_ref;
  size_t size = *size_ref;
  enum utf8_state more = *more_ref;
  ptr_idx += 1;
  left = strlen(ptr);
  if (left < (((size_t) ud->size) - 1))
  {
    break;
  }
  while ((more = utf8_append(ud, *(&ptr[ptr_idx]))) == UTF8_MORE)
  {
    ptr_idx += 1;
  }

  ptr_idx += 1;
  if (more != UTF8_DONE)
  {
    continue;
  }
  if ((maxlen > 0) && ((size + ud->width) > ((size_t) maxlen)))
  {
    while (size < ((size_t) maxlen))
    {
      screen_write_putc(ctx, &gc, ' ');
      size += 1;
    }

    break;
  }
  size += ud->width;
  screen_write_cell(ctx, &gc);
  *ptr_idx_ref = ptr_idx;
  *left_ref = left;
  *size_ref = size;
  *more_ref = more;
}


----------------------------
None
----------------------------
***/


void screen_write_cnputs(struct screen_write_ctx *ctx, ssize_t maxlen, const struct grid_cell *gcp, const char *fmt, ...)
{
  struct grid_cell gc;
  struct utf8_data *ud = &gc.data;
  va_list ap;
  char *msg;
  u_char *ptr;
  unsigned int ptr_idx = 0;
  u_char *last;
  unsigned int last_idx = 0;
  size_t left;
  size_t size = 0;
  enum utf8_state more;
  memcpy(&gc, gcp, sizeof(gc));
  __builtin_va_start(ap);
  xvasprintf(&msg, fmt, ap);
  ;
  ptr_idx = msg;
  while (ptr[ptr_idx] != '\0')
  {
    helper_screen_write_cnputs_1(&ptr_idx, &last_idx, &left, &size, &more, ctx, maxlen, gcp, gc, ud, ptr, last);
  }

  free(msg);
}


/*** DEPENDENCIES:
int xvasprintf(char **ret, const char *fmt, va_list ap)
{
  int i;
  i = vasprintf(ret, fmt, ap);
  if ((i < 0) || ((*ret) == 0))
  {
    fatalx("xasprintf: %s", strerror(errno));
  }
  return i;
}


----------------------------
None
----------------------------
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
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
enum utf8_state
{
  UTF8_MORE,
  UTF8_DONE,
  UTF8_ERROR
}
----------------------------
void helper_screen_write_cnputs_1(unsigned int * const ptr_idx_ref, unsigned int * const last_idx_ref, size_t * const left_ref, size_t * const size_ref, enum utf8_state * const more_ref, struct screen_write_ctx * const ctx, ssize_t maxlen, const struct grid_cell * const gcp, struct grid_cell gc, struct utf8_data * const ud, u_char * const ptr, u_char * const last)
{
  unsigned int ptr_idx = *ptr_idx_ref;
  unsigned int last_idx = *last_idx_ref;
  size_t left = *left_ref;
  size_t size = *size_ref;
  enum utf8_state more = *more_ref;
  if ((ptr[0 + ptr_idx] == '#') && (ptr[1 + ptr_idx] == '['))
  {
    ptr_idx += 2;
    last_idx = (&ptr[ptr_idx]) + strcspn(ptr, "]");
    if (last[last_idx] == '\0')
    {
      break;
    }
    last[last_idx] = '\0';
    style_parse(gcp, &gc, ptr);
    ptr_idx = (&last[last_idx]) + 1;
    continue;
  }
  if ((ptr[ptr_idx] > 0x7f) && (utf8_open(ud, *(&ptr[ptr_idx])) == UTF8_MORE))
  {
    helper_helper_screen_write_cnputs_1_1(&ptr_idx, &left, &size, &more, ctx, maxlen, gc, ud, ptr);
  }
  else
  {
    if ((maxlen > 0) && ((size + 1) > ((size_t) maxlen)))
    {
      break;
    }
    if ((ptr[ptr_idx] > 0x1f) && (ptr[ptr_idx] < 0x7f))
    {
      size += 1;
      screen_write_putc(ctx, &gc, *(&ptr[ptr_idx]));
    }
    ptr_idx += 1;
  }
  *ptr_idx_ref = ptr_idx;
  *last_idx_ref = last_idx;
  *left_ref = left;
  *size_ref = size;
  *more_ref = more;
}


----------------------------
None
----------------------------
None
----------------------------
***/


size_t screen_write_cstrlen(const char *fmt, ...)
{
  va_list ap;
  char *msg;
  char *msg2;
  unsigned int msg2_idx = 0;
  char *ptr;
  unsigned int ptr_idx = 0;
  char *ptr2;
  unsigned int ptr2_idx = 0;
  size_t size;
  __builtin_va_start(ap);
  xvasprintf(&msg, fmt, ap);
  ;
  msg2_idx = xmalloc(strlen(msg) + 1);
  ptr_idx = msg;
  ptr2_idx = &msg2[msg2_idx];
  while (ptr[ptr_idx] != '\0')
  {
    if ((ptr[0 + ptr_idx] == '#') && (ptr[1 + ptr_idx] == '['))
    {
      while ((ptr[ptr_idx] != ']') && (ptr[ptr_idx] != '\0'))
      {
        ptr_idx += 1;
      }

      if (ptr[ptr_idx] == ']')
      {
        ptr_idx += 1;
      }
      continue;
    }
    ptr2[ptr2_idx] = ptr[ptr_idx];
    ptr_idx += 1;
    ptr2_idx += 1;
  }

  ptr2[ptr2_idx] = '\0';
  size = screen_write_strlen("%s", msg2);
  free(msg);
  free(msg2);
  return size;
}


/*** DEPENDENCIES:
int xvasprintf(char **ret, const char *fmt, va_list ap)
{
  int i;
  i = vasprintf(ret, fmt, ap);
  if ((i < 0) || ((*ret) == 0))
  {
    fatalx("xasprintf: %s", strerror(errno));
  }
  return i;
}


----------------------------
size_t screen_write_strlen(const char *fmt, ...)
{
  va_list ap;
  char *msg;
  struct utf8_data ud;
  u_char *ptr;
  unsigned int ptr_idx = 0;
  size_t left;
  size_t size = 0;
  enum utf8_state more;
  __builtin_va_start(ap);
  xvasprintf(&msg, fmt, ap);
  ;
  ptr_idx = msg;
  while (ptr[ptr_idx] != '\0')
  {
    if ((ptr[ptr_idx] > 0x7f) && (utf8_open(&ud, *(&ptr[ptr_idx])) == UTF8_MORE))
    {
      ptr_idx += 1;
      left = strlen(ptr);
      if (left < (((size_t) ud.size) - 1))
      {
        break;
      }
      while ((more = utf8_append(&ud, *(&ptr[ptr_idx]))) == UTF8_MORE)
      {
        ptr_idx += 1;
      }

      ptr_idx += 1;
      if (more == UTF8_DONE)
      {
        size += ud.width;
      }
    }
    else
    {
      if ((ptr[ptr_idx] > 0x1f) && (ptr[ptr_idx] < 0x7f))
      {
        size += 1;
      }
      ptr_idx += 1;
    }
  }

  free(msg);
  return size;
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
***/


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


/*** DEPENDENCIES:
int xvasprintf(char **ret, const char *fmt, va_list ap)
{
  int i;
  i = vasprintf(ret, fmt, ap);
  if ((i < 0) || ((*ret) == 0))
  {
    fatalx("xasprintf: %s", strerror(errno));
  }
  return i;
}


----------------------------
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


----------------------------
struct hook *hooks_find(struct hooks *hooks, const char *name)
{
  unsigned int hooks_idx = 0;
  struct hook hook0;
  struct hook *hook;
  unsigned int hook_idx = 0;
  hook0.name = name;
  hook_idx = hooks_tree_RB_FIND(&hooks->tree, &hook0);
  while ((&hook[hook_idx]) == 0)
  {
    hooks_idx = hooks_idx->parent;
    if ((&hooks[hooks_idx]) == 0)
    {
      break;
    }
    hook_idx = hooks_tree_RB_FIND(&hooks->tree, &hook0);
  }

  return hook;
}


----------------------------
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


----------------------------
void cmdq_format(struct cmdq_item *item, const char *key, const char *fmt, ...)
{
  struct cmdq_shared *shared = item->shared;
  va_list ap;
  char *value;
  __builtin_va_start(ap);
  xvasprintf(&value, fmt, ap);
  ;
  if (shared->formats == 0)
  {
    shared->formats = format_create(0, 0, 0, 0);
  }
  format_add(shared->formats, key, "%s", value);
  free(value);
}


----------------------------
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


void screen_write_puts(struct screen_write_ctx *ctx, const struct grid_cell *gcp, const char *fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  screen_write_vnputs(ctx, -1, gcp, fmt, ap);
  ;
}


/*** DEPENDENCIES:
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
void screen_write_vnputs(struct screen_write_ctx *ctx, ssize_t maxlen, const struct grid_cell *gcp, const char *fmt, va_list ap)
{
  struct grid_cell gc;
  struct utf8_data *ud = &gc.data;
  char *msg;
  u_char *ptr;
  unsigned int ptr_idx = 0;
  size_t left;
  size_t size = 0;
  enum utf8_state more;
  memcpy(&gc, gcp, sizeof(gc));
  xvasprintf(&msg, fmt, ap);
  ptr_idx = msg;
  while (ptr[ptr_idx] != '\0')
  {
    helper_screen_write_vnputs_1(&gc, &ptr_idx, &left, &size, &more, ctx, maxlen, ud, ptr);
  }

  free(msg);
}


----------------------------
None
----------------------------
None
----------------------------
***/


void window_copy_add(struct window_pane *wp, const char *fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  window_copy_vadd(wp, fmt, ap);
  ;
}


/*** DEPENDENCIES:
void window_copy_vadd(struct window_pane *wp, const char *fmt, va_list ap)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *backing = data->backing;
  struct screen_write_ctx back_ctx;
  struct screen_write_ctx ctx;
  struct grid_cell gc;
  u_int old_hsize;
  u_int old_cy;
  if (backing == (&wp->base))
  {
    return;
  }
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  old_hsize = data->backing->grid->hsize;
  screen_write_start(&back_ctx, 0, backing);
  if (data->backing_written)
  {
    screen_write_carriagereturn(&back_ctx);
    screen_write_linefeed(&back_ctx, 0, 8);
  }
  else
    data->backing_written = 1;
  old_cy = backing->cy;
  screen_write_vnputs(&back_ctx, 0, &gc, fmt, ap);
  screen_write_stop(&back_ctx);
  data->oy += data->backing->grid->hsize - old_hsize;
  screen_write_start(&ctx, wp, &data->screen);
  if (data->backing->grid->hsize)
  {
    window_copy_redraw_lines(wp, 0, 1);
  }
  window_copy_redraw_lines(wp, old_cy, (backing->cy - old_cy) + 1);
  screen_write_stop(&ctx);
}


----------------------------
None
----------------------------
***/


void cmdq_print(struct cmdq_item *item, const char *fmt, ...)
{
  struct client *c = item->client;
  struct window *w;
  unsigned int w_idx = 0;
  va_list ap;
  char *tmp;
  char *msg;
  unsigned int msg_idx = 0;
  __builtin_va_start(ap);
  if (c == 0)
  {
    ;
  }
  else
    if ((c->session == 0) || (c->flags & 0x2000))
  {
    if ((~c->flags) & 0x10000)
    {
      xvasprintf(&tmp, fmt, ap);
      msg_idx = utf8_sanitize(tmp);
      free(tmp);
      evbuffer_add(c->stdout_data, msg, strlen(msg));
      free(msg);
    }
    else
      evbuffer_add_vprintf(c->stdout_data, fmt, ap);
    evbuffer_add(c->stdout_data, "\n", 1);
    server_client_push_stdout(c);
  }
  else
  {
    w_idx = c->session->curw->window;
    if (w->active->mode != (&window_copy_mode))
    {
      window_pane_reset_mode(w->active);
      window_pane_set_mode(w->active, &window_copy_mode, 0, 0);
      window_copy_init_for_output(w->active);
    }
    window_copy_vadd(w->active, fmt, ap);
  }
  ;
}


/*** DEPENDENCIES:
extern const struct window_mode window_copy_mode
----------------------------
int xvasprintf(char **ret, const char *fmt, va_list ap)
{
  int i;
  i = vasprintf(ret, fmt, ap);
  if ((i < 0) || ((*ret) == 0))
  {
    fatalx("xasprintf: %s", strerror(errno));
  }
  return i;
}


----------------------------
None
----------------------------
char *utf8_sanitize(const char *src)
{
  unsigned int src_idx = 0;
  char *dst;
  unsigned int dst_idx = 0;
  size_t n;
  enum utf8_state more;
  struct utf8_data ud;
  u_int i;
  dst_idx = 0;
  n = 0;
  while (src[src_idx] != '\0')
  {
    dst_idx = xreallocarray(dst_idx, n + 1, sizeof(*dst_idx));
    if ((more = utf8_open(&ud, *(&src[src_idx]))) == UTF8_MORE)
    {
      while (((*(++(&src[src_idx]))) != '\0') && (more == UTF8_MORE))
      {
        more = utf8_append(&ud, *(&src[src_idx]));
      }

      if (more == UTF8_DONE)
      {
        dst_idx = xreallocarray(dst_idx, n + ud.width, sizeof(*dst_idx));
        for (i = 0; i < ud.width; i += 1)
        {
          dst[n + dst_idx] = '_';
          n += 1;
        }

        continue;
      }
      src_idx -= ud.have;
    }
    if ((src[src_idx] > 0x1f) && (src[src_idx] < 0x7f))
    {
      dst[n + dst_idx] = src[src_idx];
      n += 1;
    }
    else
      dst[n + dst_idx] = '_';
    n += 1;
    src_idx += 1;
  }

  dst_idx = xreallocarray(dst_idx, n + 1, sizeof(*dst_idx));
  dst[n + dst_idx] = '\0';
  return dst;
}


----------------------------
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


----------------------------
void window_copy_init_for_output(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  data->backing = xmalloc(sizeof(*data->backing));
  screen_init(data->backing, (&wp->base)->grid->sx, (&wp->base)->grid->sy, 4294967295U);
}


----------------------------
void window_copy_vadd(struct window_pane *wp, const char *fmt, va_list ap)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *backing = data->backing;
  struct screen_write_ctx back_ctx;
  struct screen_write_ctx ctx;
  struct grid_cell gc;
  u_int old_hsize;
  u_int old_cy;
  if (backing == (&wp->base))
  {
    return;
  }
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  old_hsize = data->backing->grid->hsize;
  screen_write_start(&back_ctx, 0, backing);
  if (data->backing_written)
  {
    screen_write_carriagereturn(&back_ctx);
    screen_write_linefeed(&back_ctx, 0, 8);
  }
  else
    data->backing_written = 1;
  old_cy = backing->cy;
  screen_write_vnputs(&back_ctx, 0, &gc, fmt, ap);
  screen_write_stop(&back_ctx);
  data->oy += data->backing->grid->hsize - old_hsize;
  screen_write_start(&ctx, wp, &data->screen);
  if (data->backing->grid->hsize)
  {
    window_copy_redraw_lines(wp, 0, 1);
  }
  window_copy_redraw_lines(wp, old_cy, (backing->cy - old_cy) + 1);
  screen_write_stop(&ctx);
}


----------------------------
None
----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
struct environ_entry *environ_RB_MINMAX(struct environ *head, int val)
{
  struct environ_entry *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct environ_entry *parent = 0;
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
struct environ_entry *environ_RB_NEXT(struct environ_entry *elm)
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


struct options_entry *options_set_string(struct options *oo, const char *name, int append, const char *fmt, ...)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  va_list ap;
  char *s;
  char *value;
  unsigned int value_idx = 0;
  __builtin_va_start(ap);
  xvasprintf(&s, fmt, ap);
  ;
  o_idx = options_get_only(oo, name);
  if ((((&o[o_idx]) != 0) && append) && ((o->tableentry == 0) || (o->tableentry->type == OPTIONS_TABLE_STRING)))
  {
    xasprintf(&(&value[value_idx]), "%s%s", o->string, s);
    free(s);
  }
  else
    value_idx = s;
  if (((&o[o_idx]) == 0) && ((*name) == '@'))
  {
    o_idx = options_add(oo, name);
  }
  else
    if ((&o[o_idx]) == 0)
  {
    o_idx = options_default(oo, options_parent_table_entry(oo, name));
    if ((&o[o_idx]) == 0)
    {
      return 0;
    }
  }
  if (!((o->tableentry == 0) || (o->tableentry->type == OPTIONS_TABLE_STRING)))
  {
    fatalx("option %s is not a string", name);
  }
  free(o->string);
  o->string = &value[value_idx];
  return o;
}


/*** DEPENDENCIES:
int xvasprintf(char **ret, const char *fmt, va_list ap)
{
  int i;
  i = vasprintf(ret, fmt, ap);
  if ((i < 0) || ((*ret) == 0))
  {
    fatalx("xasprintf: %s", strerror(errno));
  }
  return i;
}


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
struct options_entry *options_get_only(struct options *oo, const char *name)
{
  struct options_entry o;
  o.name = name;
  return options_tree_RB_FIND(&oo->tree, &o);
}


----------------------------
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


