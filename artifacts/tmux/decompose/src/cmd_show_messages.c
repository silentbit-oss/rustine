static int cmd_show_messages_jobs(struct cmdq_item *item, int blank)
{
  struct job *job;
  unsigned int job_idx = 0;
  u_int n;
  n = 0;
  for (job_idx = (&all_jobs)->lh_first; (&job[job_idx]) != 0; job_idx = job_idx->entry.le_next)
  {
    if (blank)
    {
      cmdq_print(item, "%s", "");
      blank = 0;
    }
    cmdq_print(item, "Job %u: %s [fd=%d, pid=%ld, status=%d]", n, job->cmd, job->fd, (long) job->pid, job->status);
    n += 1;
  }

  return n != 0;
}


/*** DEPENDENCIES:
extern struct joblist all_jobs
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
None
----------------------------
***/


static int cmd_show_messages_terminals(struct cmdq_item *item, int blank)
{
  struct tty_term *term;
  unsigned int term_idx = 0;
  u_int i;
  u_int n;
  n = 0;
  for (term_idx = (&tty_terms)->lh_first; (&term[term_idx]) != 0; term_idx = term_idx->entry.le_next)
  {
    if (blank)
    {
      cmdq_print(item, "%s", "");
      blank = 0;
    }
    cmdq_print(item, "Terminal %u: %s [references=%u, flags=0x%x]:", n, term->name, term->references, term->flags);
    n += 1;
    for (i = 0; i < tty_term_ncodes(); i += 1)
    {
      cmdq_print(item, "%s", tty_term_describe(term, i));
    }

  }

  return n != 0;
}


/*** DEPENDENCIES:
const char *tty_term_describe(struct tty_term *term, enum tty_code_code code)
{
  static char s[256];
  char out[128];
  switch (term->codes[code].type)
  {
    case TTYCODE_NONE:
    {
      xsnprintf(s, sizeof(s), "%4u: %s: [missing]", code, tty_term_codes[code].name);
      break;
    }

    case TTYCODE_STRING:
    {
      strnvis(out, term->codes[code].value.string, sizeof(out), (0x01 | 0x08) | 0x10);
      xsnprintf(s, sizeof(s), "%4u: %s: (string) %s", code, tty_term_codes[code].name, out);
      break;
    }

    case TTYCODE_NUMBER:
    {
      xsnprintf(s, sizeof(s), "%4u: %s: (number) %d", code, tty_term_codes[code].name, term->codes[code].value.number);
      break;
    }

    case TTYCODE_FLAG:
    {
      xsnprintf(s, sizeof(s), "%4u: %s: (flag) %s", code, tty_term_codes[code].name, (term->codes[code].value.flag) ? ("true") : ("false"));
      break;
    }

  }

  return s;
}


----------------------------
struct tty_terms
{
  struct tty_term *lh_first;
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
u_int tty_term_ncodes(void)
{
  return (sizeof(tty_term_codes)) / (sizeof(tty_term_codes[0]));
}


----------------------------
None
----------------------------
***/


static enum cmd_retval cmd_show_messages_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct client *c;
  unsigned int c_idx = 0;
  struct message_entry *msg;
  unsigned int msg_idx = 0;
  char *tim;
  unsigned int tim_idx = 0;
  int done;
  int blank;
  if ((c_idx = cmd_find_client(item, args_get(args, 't'), 0)) == 0)
  {
    return CMD_RETURN_ERROR;
  }
  done = (blank = 0);
  if (args_has(args, 'T'))
  {
    blank = cmd_show_messages_terminals(item, blank);
    done = 1;
  }
  if (args_has(args, 'J'))
  {
    cmd_show_messages_jobs(item, blank);
    done = 1;
  }
  if (done)
  {
    return CMD_RETURN_NORMAL;
  }
  for (msg_idx = (&c->message_log)->tqh_first; (&msg[msg_idx]) != 0; msg_idx = msg_idx->entry.tqe_next)
  {
    tim_idx = ctime(&msg->msg_time);
    *strchr(tim, '\n') = '\0';
    cmdq_print(item, "%s %s", tim, msg->msg);
  }

  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
static int cmd_show_messages_jobs(struct cmdq_item *item, int blank)
{
  struct job *job;
  unsigned int job_idx = 0;
  u_int n;
  n = 0;
  for (job_idx = (&all_jobs)->lh_first; (&job[job_idx]) != 0; job_idx = job_idx->entry.le_next)
  {
    if (blank)
    {
      cmdq_print(item, "%s", "");
      blank = 0;
    }
    cmdq_print(item, "Job %u: %s [fd=%d, pid=%ld, status=%d]", n, job->cmd, job->fd, (long) job->pid, job->status);
    n += 1;
  }

  return n != 0;
}


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
enum cmd_retval
{
  CMD_RETURN_ERROR = -1,
  CMD_RETURN_NORMAL = 0,
  CMD_RETURN_WAIT,
  CMD_RETURN_STOP
}
----------------------------
static int cmd_show_messages_terminals(struct cmdq_item *item, int blank)
{
  struct tty_term *term;
  unsigned int term_idx = 0;
  u_int i;
  u_int n;
  n = 0;
  for (term_idx = (&tty_terms)->lh_first; (&term[term_idx]) != 0; term_idx = term_idx->entry.le_next)
  {
    if (blank)
    {
      cmdq_print(item, "%s", "");
      blank = 0;
    }
    cmdq_print(item, "Terminal %u: %s [references=%u, flags=0x%x]:", n, term->name, term->references, term->flags);
    n += 1;
    for (i = 0; i < tty_term_ncodes(); i += 1)
    {
      cmdq_print(item, "%s", tty_term_describe(term, i));
    }

  }

  return n != 0;
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


