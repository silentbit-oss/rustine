static void cmd_run_shell_free(void *data)
{
  struct cmd_run_shell_data *cdata = data;
  free(cdata->cmd);
  free(cdata);
}


/*** DEPENDENCIES:
struct cmd_run_shell_data
{
  char *cmd;
  struct cmdq_item *item;
  int wp_id;
}
----------------------------
None
----------------------------
***/


static void cmd_run_shell_print(struct job *job, const char *msg)
{
  struct cmd_run_shell_data *cdata = job->data;
  struct window_pane *wp = 0;
  unsigned int wp_idx = 0;
  struct cmd_find_state fs;
  if (cdata->wp_id != (-1))
  {
    wp_idx = window_pane_find_by_id(cdata->wp_id);
  }
  if ((&wp[wp_idx]) == 0)
  {
    if (cdata->item != 0)
    {
      cmdq_print(cdata->item, "%s", msg);
      return;
    }
    if (cmd_find_from_nothing(&fs, 0) != 0)
    {
      return;
    }
    wp_idx = fs.wp_idx;
    if ((&wp[wp_idx]) == 0)
    {
      return;
    }
  }
  if (window_pane_set_mode(wp, &window_copy_mode, 0, 0) == 0)
  {
    window_copy_init_for_output(wp);
  }
  if (wp->mode == (&window_copy_mode))
  {
    window_copy_add(wp, "%s", msg);
  }
}


/*** DEPENDENCIES:
extern const struct window_mode window_copy_mode
----------------------------
struct window_pane *window_pane_find_by_id(u_int id)
{
  struct window_pane wp;
  wp.id = id;
  return window_pane_tree_RB_FIND(&all_window_panes, &wp);
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


----------------------------
struct cmd_run_shell_data
{
  char *cmd;
  struct cmdq_item *item;
  int wp_id;
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
void window_copy_init_for_output(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  data->backing = xmalloc(sizeof(*data->backing));
  screen_init(data->backing, (&wp->base)->grid->sx, (&wp->base)->grid->sy, 4294967295U);
}


----------------------------
void window_copy_add(struct window_pane *wp, const char *fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  window_copy_vadd(wp, fmt, ap);
  ;
}


----------------------------
None
----------------------------
***/


static void cmd_run_shell_callback(struct job *job)
{
  struct cmd_run_shell_data *cdata = job->data;
  char *cmd = cdata->cmd;
  char *msg;
  unsigned int msg_idx = 0;
  char *line;
  unsigned int line_idx = 0;
  size_t size;
  int retcode;
  do
  {
    if ((line_idx = evbuffer_readline(job->event->input)) != 0)
    {
      cmd_run_shell_print(job, line);
      free(line);
    }
  }
  while ((&line[line_idx]) != 0);
  size = EVBUFFER_LENGTH(job->event->input);
  if (size != 0)
  {
    line_idx = xmalloc(size + 1);
    memcpy(line, EVBUFFER_DATA(job->event->input), size);
    line[size + line_idx] = '\0';
    cmd_run_shell_print(job, line);
    free(line);
  }
  msg_idx = 0;
  if (WIFEXITED(job->status))
  {
    if ((retcode = WEXITSTATUS(job->status)) != 0)
    {
      xasprintf(&(&msg[msg_idx]), "'%s' returned %d", cmd, retcode);
    }
  }
  else
    if (WIFSIGNALED(job->status))
  {
    retcode = WTERMSIG(job->status);
    xasprintf(&(&msg[msg_idx]), "'%s' terminated by signal %d", cmd, retcode);
  }
  if ((&msg[msg_idx]) != 0)
  {
    cmd_run_shell_print(job, msg);
  }
  free(msg);
  if (cdata->item != 0)
  {
    cdata->item->flags &= ~0x2;
  }
}


/*** DEPENDENCIES:
static void cmd_run_shell_print(struct job *job, const char *msg)
{
  struct cmd_run_shell_data *cdata = job->data;
  struct window_pane *wp = 0;
  unsigned int wp_idx = 0;
  struct cmd_find_state fs;
  if (cdata->wp_id != (-1))
  {
    wp_idx = window_pane_find_by_id(cdata->wp_id);
  }
  if ((&wp[wp_idx]) == 0)
  {
    if (cdata->item != 0)
    {
      cmdq_print(cdata->item, "%s", msg);
      return;
    }
    if (cmd_find_from_nothing(&fs, 0) != 0)
    {
      return;
    }
    wp_idx = fs.wp_idx;
    if ((&wp[wp_idx]) == 0)
    {
      return;
    }
  }
  if (window_pane_set_mode(wp, &window_copy_mode, 0, 0) == 0)
  {
    window_copy_init_for_output(wp);
  }
  if (wp->mode == (&window_copy_mode))
  {
    window_copy_add(wp, "%s", msg);
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
struct cmd_run_shell_data
{
  char *cmd;
  struct cmdq_item *item;
  int wp_id;
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


static enum cmd_retval cmd_run_shell_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct cmd_run_shell_data *cdata;
  unsigned int cdata_idx = 0;
  struct client *c = cmd_find_client(item, 0, 1);
  struct session *s = item->target.s;
  struct winlink *wl = item->target.wl;
  struct window_pane *wp = item->target.wp;
  const char *cwd;
  unsigned int cwd_idx = 0;
  if ((item->client != 0) && (item->client->session == 0))
  {
    cwd_idx = item->client->cwd_idx;
  }
  else
    if (s != 0)
  {
    cwd_idx = s->cwd_idx;
  }
  else
    cwd_idx = 0;
  cdata_idx = xcalloc(1, sizeof(*cdata_idx));
  cdata->cmd = format_single(item, args->argv[0], c, s, wl, wp);
  if (args_has(args, 't') && (wp != 0))
  {
    cdata->wp_id = wp->id;
  }
  else
    cdata->wp_id = -1;
  if (!args_has(args, 'b'))
  {
    cdata->item = item;
  }
  job_run(cdata->cmd, s, cwd, 0, cmd_run_shell_callback, cmd_run_shell_free, cdata, 0);
  if (args_has(args, 'b'))
  {
    return CMD_RETURN_NORMAL;
  }
  return CMD_RETURN_WAIT;
}


/*** DEPENDENCIES:
struct job *job_run(const char *cmd, struct session *s, const char *cwd, job_update_cb updatecb, job_complete_cb completecb, job_free_cb freecb, void *data, int flags)
{
  struct job *job;
  unsigned int job_idx = 0;
  struct environ *env;
  unsigned int env_idx = 0;
  pid_t pid;
  int nullfd;
  int out[2];
  const char *home;
  unsigned int home_idx = 0;
  sigset_t set;
  sigset_t oldset;
  if (socketpair(AF_UNIX, SOCK_STREAM, PF_UNSPEC, out) != 0)
  {
    return 0;
  }
  env_idx = environ_for_session(s, !cfg_finished);
  sigfillset(&set);
  sigprocmask(SIG_BLOCK, &set, &oldset);
  switch (pid = fork())
  {
    case -1:
    {
      sigprocmask(SIG_SETMASK, &oldset, 0);
      environ_free(env);
      close(out[0]);
      close(out[1]);
      return 0;
    }

    case 0:
    {
      helper_job_run_1(&nullfd, &home_idx, cmd, cwd, env, out, home, oldset);
    }

  }

  sigprocmask(SIG_SETMASK, &oldset, 0);
  environ_free(env);
  close(out[1]);
  job_idx = xmalloc(sizeof(*job_idx));
  job->state = JOB_RUNNING;
  job->flags = flags;
  job->cmd = xstrdup(cmd);
  job->pid = pid;
  job->status = 0;
  do
  {
    if ((job->entry.le_next = (&all_jobs)->lh_first) != 0)
    {
      (&all_jobs)->lh_first->entry.le_prev = &job->entry.le_next;
    }
    (&all_jobs)->lh_first = &job[job_idx];
    job->entry.le_prev = &(&all_jobs)->lh_first;
  }
  while (0);
  job->updatecb = updatecb;
  job->completecb = completecb;
  job->freecb = freecb;
  job->data = data;
  job->fd = out[0];
  setblocking(job->fd, 0);
  job->event = bufferevent_new(job->fd, job_read_callback, job_write_callback, job_error_callback, job);
  bufferevent_enable(job->event, EV_READ | EV_WRITE);
  log_debug("run job %p: %s, pid %ld", job, job->cmd, (long) job->pid);
  return job;
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


----------------------------
struct cmd_run_shell_data
{
  char *cmd;
  struct cmdq_item *item;
  int wp_id;
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
static void cmd_run_shell_free(void *data)
{
  struct cmd_run_shell_data *cdata = data;
  free(cdata->cmd);
  free(cdata);
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
None
----------------------------
static void cmd_run_shell_callback(struct job *job)
{
  struct cmd_run_shell_data *cdata = job->data;
  char *cmd = cdata->cmd;
  char *msg;
  unsigned int msg_idx = 0;
  char *line;
  unsigned int line_idx = 0;
  size_t size;
  int retcode;
  do
  {
    if ((line_idx = evbuffer_readline(job->event->input)) != 0)
    {
      cmd_run_shell_print(job, line);
      free(line);
    }
  }
  while ((&line[line_idx]) != 0);
  size = EVBUFFER_LENGTH(job->event->input);
  if (size != 0)
  {
    line_idx = xmalloc(size + 1);
    memcpy(line, EVBUFFER_DATA(job->event->input), size);
    line[size + line_idx] = '\0';
    cmd_run_shell_print(job, line);
    free(line);
  }
  msg_idx = 0;
  if (WIFEXITED(job->status))
  {
    if ((retcode = WEXITSTATUS(job->status)) != 0)
    {
      xasprintf(&(&msg[msg_idx]), "'%s' returned %d", cmd, retcode);
    }
  }
  else
    if (WIFSIGNALED(job->status))
  {
    retcode = WTERMSIG(job->status);
    xasprintf(&(&msg[msg_idx]), "'%s' terminated by signal %d", cmd, retcode);
  }
  if ((&msg[msg_idx]) != 0)
  {
    cmd_run_shell_print(job, msg);
  }
  free(msg);
  if (cdata->item != 0)
  {
    cdata->item->flags &= ~0x2;
  }
}


----------------------------
int args_has(struct args *args, u_char ch)
{
  return args_find(args, ch) != 0;
}


----------------------------
None
----------------------------
***/


