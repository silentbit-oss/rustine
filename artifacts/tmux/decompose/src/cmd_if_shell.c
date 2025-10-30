static void cmd_if_shell_free(void *data)
{
  struct cmd_if_shell_data *cdata = data;
  if (cdata->client != 0)
  {
    server_client_unref(cdata->client);
  }
  free(cdata->cmd_else);
  free(cdata->cmd_if);
  free(cdata->file);
  free(cdata);
}


/*** DEPENDENCIES:
struct cmd_if_shell_data
{
  char *file;
  u_int line;
  char *cmd_if;
  char *cmd_else;
  struct client *client;
  struct cmdq_item *item;
  struct mouse_event mouse;
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


// hint:  ['cmd_idx_ref is a mutable refrence to unsigned int', 'cmdlist_idx_ref is a mutable refrence to unsigned int', 'new_item_idx_ref is a mutable refrence to unsigned int']
enum cmd_retval helper_cmd_if_shell_exec_1(unsigned int * const cmd_idx_ref, unsigned int * const cmdlist_idx_ref, unsigned int * const new_item_idx_ref, struct cmdq_item * const item, struct args * const args, struct cmdq_shared * const shared, char * const shellcmd, unsigned int shellcmd_idx, char * const cmd, char * const cause, struct cmd_list * const cmdlist, struct cmdq_item * const new_item)
{
  unsigned int cmd_idx = *cmd_idx_ref;
  unsigned int cmdlist_idx = *cmdlist_idx_ref;
  unsigned int new_item_idx = *new_item_idx_ref;
  cmd_idx = 0;
  if ((shellcmd[shellcmd_idx] != '0') && (shellcmd[shellcmd_idx] != '\0'))
  {
    cmd_idx = args->argv[1];
  }
  else
    if (args->argc == 3)
  {
    cmd_idx = args->argv[2];
  }
  free(shellcmd);
  if ((&cmd[cmd_idx]) == 0)
  {
    return CMD_RETURN_NORMAL;
  }
  cmdlist_idx = cmd_string_parse(cmd, 0, 0, &cause);
  if ((&cmdlist[cmdlist_idx]) == 0)
  {
    if (cause != 0)
    {
      cmdq_error(item, "%s", cause);
      free(cause);
    }
    return CMD_RETURN_ERROR;
  }
  new_item_idx = cmdq_get_command(cmdlist, 0, &shared->mouse, 0);
  cmdq_insert_after(item, new_item);
  cmd_list_free(cmdlist);
  return CMD_RETURN_NORMAL;
  *cmd_idx_ref = cmd_idx;
  *cmdlist_idx_ref = cmdlist_idx;
  *new_item_idx_ref = new_item_idx;
}


/*** DEPENDENCIES:
struct cmd_list *cmd_string_parse(const char *s, const char *file, u_int line, char **cause)
{
  struct cmd_list *cmdlist = 0;
  unsigned int cmdlist_idx = 0;
  int argc;
  char **argv;
  *cause = 0;
  if (cmd_string_split(s, &argc, &argv) != 0)
  {
    xasprintf(cause, "invalid or unknown command: %s", s);
    return 0;
  }
  if (argc != 0)
  {
    cmdlist_idx = cmd_list_parse(argc, argv, file, line, cause);
    if ((&cmdlist[cmdlist_idx]) == 0)
    {
      cmd_free_argv(argc, argv);
      return 0;
    }
  }
  cmd_free_argv(argc, argv);
  return cmdlist;
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
enum cmd_retval
{
  CMD_RETURN_ERROR = -1,
  CMD_RETURN_NORMAL = 0,
  CMD_RETURN_WAIT,
  CMD_RETURN_STOP
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
None
----------------------------
***/


static void cmd_if_shell_callback(struct job *job)
{
  struct cmd_if_shell_data *cdata = job->data;
  struct client *c = cdata->client;
  struct cmd_list *cmdlist;
  unsigned int cmdlist_idx = 0;
  struct cmdq_item *new_item;
  unsigned int new_item_idx = 0;
  char *cause;
  char *cmd;
  unsigned int cmd_idx = 0;
  char *file = cdata->file;
  u_int line = cdata->line;
  if ((!WIFEXITED(job->status)) || (WEXITSTATUS(job->status) != 0))
  {
    cmd_idx = cdata->cmd_else;
  }
  else
    cmd_idx = cdata->cmd_if;
  if ((&cmd[cmd_idx]) == 0)
  {
    goto out;
  }
  cmdlist_idx = cmd_string_parse(cmd, file, line, &cause);
  if ((&cmdlist[cmdlist_idx]) == 0)
  {
    if ((cause != 0) && (cdata->item != 0))
    {
      cmdq_error(cdata->item, "%s", cause);
    }
    free(cause);
    new_item_idx = 0;
  }
  else
  {
    new_item_idx = cmdq_get_command(cmdlist, 0, &cdata->mouse, 0);
    cmd_list_free(cmdlist);
  }
  if ((&new_item[new_item_idx]) != 0)
  {
    if (cdata->item == 0)
    {
      cmdq_append(c, new_item);
    }
    else
      cmdq_insert_after(cdata->item, new_item);
  }
  out:
  if (cdata->item != 0)
  {
    cdata->item->flags &= ~0x2;
  }

}


/*** DEPENDENCIES:
struct cmd_list *cmd_string_parse(const char *s, const char *file, u_int line, char **cause)
{
  struct cmd_list *cmdlist = 0;
  unsigned int cmdlist_idx = 0;
  int argc;
  char **argv;
  *cause = 0;
  if (cmd_string_split(s, &argc, &argv) != 0)
  {
    xasprintf(cause, "invalid or unknown command: %s", s);
    return 0;
  }
  if (argc != 0)
  {
    cmdlist_idx = cmd_list_parse(argc, argv, file, line, cause);
    if ((&cmdlist[cmdlist_idx]) == 0)
    {
      cmd_free_argv(argc, argv);
      return 0;
    }
  }
  cmd_free_argv(argc, argv);
  return cmdlist;
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
struct cmd_if_shell_data
{
  char *file;
  u_int line;
  char *cmd_if;
  char *cmd_else;
  struct client *client;
  struct cmdq_item *item;
  struct mouse_event mouse;
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


static enum cmd_retval cmd_if_shell_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct cmdq_shared *shared = item->shared;
  struct cmd_if_shell_data *cdata;
  unsigned int cdata_idx = 0;
  char *shellcmd;
  unsigned int shellcmd_idx = 0;
  char *cmd;
  unsigned int cmd_idx = 0;
  char *cause;
  struct cmd_list *cmdlist;
  unsigned int cmdlist_idx = 0;
  struct cmdq_item *new_item;
  unsigned int new_item_idx = 0;
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
  shellcmd_idx = format_single(item, args->argv[0], c, s, wl, wp);
  if (args_has(args, 'F'))
  {
    helper_cmd_if_shell_exec_1(&cmd_idx, &cmdlist_idx, &new_item_idx, item, args, shared, shellcmd, shellcmd_idx, cmd, cause, cmdlist, new_item);
  }
  cdata_idx = xcalloc(1, sizeof(*cdata_idx));
  if (self->file != 0)
  {
    cdata->file = xstrdup(self->file);
    cdata->line = self->line;
  }
  cdata->cmd_if = xstrdup(args->argv[1]);
  if (args->argc == 3)
  {
    cdata->cmd_else = xstrdup(args->argv[2]);
  }
  else
    cdata->cmd_else = 0;
  cdata->client = item->client;
  if (cdata->client != 0)
  {
    cdata->client->references += 1;
  }
  if (!args_has(args, 'b'))
  {
    cdata->item = item;
  }
  else
    cdata->item = 0;
  memcpy(&cdata->mouse, &shared->mouse, sizeof(cdata->mouse));
  job_run(shellcmd, s, cwd, 0, cmd_if_shell_callback, cmd_if_shell_free, cdata, 0);
  free(shellcmd);
  if (args_has(args, 'b'))
  {
    return CMD_RETURN_NORMAL;
  }
  return CMD_RETURN_WAIT;
}


/*** DEPENDENCIES:
enum cmd_retval helper_cmd_if_shell_exec_1(unsigned int * const cmd_idx_ref, unsigned int * const cmdlist_idx_ref, unsigned int * const new_item_idx_ref, struct cmdq_item * const item, struct args * const args, struct cmdq_shared * const shared, char * const shellcmd, unsigned int shellcmd_idx, char * const cmd, char * const cause, struct cmd_list * const cmdlist, struct cmdq_item * const new_item)
{
  unsigned int cmd_idx = *cmd_idx_ref;
  unsigned int cmdlist_idx = *cmdlist_idx_ref;
  unsigned int new_item_idx = *new_item_idx_ref;
  cmd_idx = 0;
  if ((shellcmd[shellcmd_idx] != '0') && (shellcmd[shellcmd_idx] != '\0'))
  {
    cmd_idx = args->argv[1];
  }
  else
    if (args->argc == 3)
  {
    cmd_idx = args->argv[2];
  }
  free(shellcmd);
  if ((&cmd[cmd_idx]) == 0)
  {
    return CMD_RETURN_NORMAL;
  }
  cmdlist_idx = cmd_string_parse(cmd, 0, 0, &cause);
  if ((&cmdlist[cmdlist_idx]) == 0)
  {
    if (cause != 0)
    {
      cmdq_error(item, "%s", cause);
      free(cause);
    }
    return CMD_RETURN_ERROR;
  }
  new_item_idx = cmdq_get_command(cmdlist, 0, &shared->mouse, 0);
  cmdq_insert_after(item, new_item);
  cmd_list_free(cmdlist);
  return CMD_RETURN_NORMAL;
  *cmd_idx_ref = cmd_idx;
  *cmdlist_idx_ref = cmdlist_idx;
  *new_item_idx_ref = new_item_idx;
}


----------------------------
struct cmd_if_shell_data
{
  char *file;
  u_int line;
  char *cmd_if;
  char *cmd_else;
  struct client *client;
  struct cmdq_item *item;
  struct mouse_event mouse;
}
----------------------------
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
static void cmd_if_shell_callback(struct job *job)
{
  struct cmd_if_shell_data *cdata = job->data;
  struct client *c = cdata->client;
  struct cmd_list *cmdlist;
  unsigned int cmdlist_idx = 0;
  struct cmdq_item *new_item;
  unsigned int new_item_idx = 0;
  char *cause;
  char *cmd;
  unsigned int cmd_idx = 0;
  char *file = cdata->file;
  u_int line = cdata->line;
  if ((!WIFEXITED(job->status)) || (WEXITSTATUS(job->status) != 0))
  {
    cmd_idx = cdata->cmd_else;
  }
  else
    cmd_idx = cdata->cmd_if;
  if ((&cmd[cmd_idx]) == 0)
  {
    goto out;
  }
  cmdlist_idx = cmd_string_parse(cmd, file, line, &cause);
  if ((&cmdlist[cmdlist_idx]) == 0)
  {
    if ((cause != 0) && (cdata->item != 0))
    {
      cmdq_error(cdata->item, "%s", cause);
    }
    free(cause);
    new_item_idx = 0;
  }
  else
  {
    new_item_idx = cmdq_get_command(cmdlist, 0, &cdata->mouse, 0);
    cmd_list_free(cmdlist);
  }
  if ((&new_item[new_item_idx]) != 0)
  {
    if (cdata->item == 0)
    {
      cmdq_append(c, new_item);
    }
    else
      cmdq_insert_after(cdata->item, new_item);
  }
  out:
  if (cdata->item != 0)
  {
    cdata->item->flags &= ~0x2;
  }

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
enum cmd_retval
{
  CMD_RETURN_ERROR = -1,
  CMD_RETURN_NORMAL = 0,
  CMD_RETURN_WAIT,
  CMD_RETURN_STOP
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
static void cmd_if_shell_free(void *data)
{
  struct cmd_if_shell_data *cdata = data;
  if (cdata->client != 0)
  {
    server_client_unref(cdata->client);
  }
  free(cdata->cmd_else);
  free(cdata->cmd_if);
  free(cdata->file);
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
int args_has(struct args *args, u_char ch)
{
  return args_find(args, ch) != 0;
}


----------------------------
None
----------------------------
***/


