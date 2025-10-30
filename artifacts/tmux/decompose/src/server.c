int server_check_marked(void)
{
  return cmd_find_valid_state(&marked_pane);
}


/*** DEPENDENCIES:
extern struct cmd_find_state marked_pane
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
***/


void server_clear_marked(void)
{
  cmd_find_clear_state(&marked_pane, 0);
}


/*** DEPENDENCIES:
extern struct cmd_find_state marked_pane
----------------------------
void cmd_find_clear_state(struct cmd_find_state *fs, int flags)
{
  memset(fs, 0, sizeof(*fs));
  fs->flags = flags;
  fs->idx = -1;
}


----------------------------
***/


static enum cmd_retval server_start_error(struct cmdq_item *item, void *data)
{
  char *error = data;
  cmdq_error(item, "%s", error);
  free(error);
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
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


int server_is_marked(struct session *s, struct winlink *wl, struct window_pane *wp)
{
  if (((s == 0) || (wl == 0)) || (wp == 0))
  {
    return 0;
  }
  if ((marked_pane.s != s) || (marked_pane.wl != wl))
  {
    return 0;
  }
  if (marked_pane.wp != wp)
  {
    return 0;
  }
  return server_check_marked();
}


/*** DEPENDENCIES:
extern struct cmd_find_state marked_pane
----------------------------
int server_check_marked(void)
{
  return cmd_find_valid_state(&marked_pane);
}


----------------------------
None
----------------------------
***/


static int server_loop(void)
{
  struct client *c;
  unsigned int c_idx = 0;
  u_int items;
  struct job *job;
  unsigned int job_idx = 0;
  do
  {
    items = cmdq_next(0);
    for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
    {
      if (c->flags & 0x40000)
      {
        items += cmdq_next(c);
      }
    }

  }
  while (items != 0);
  server_client_loop();
  if ((!options_get_number(global_options, "exit-empty")) && (!server_exit))
  {
    return 0;
  }
  if (!options_get_number(global_options, "exit-unattached"))
  {
    if (!((&sessions)->rbh_root == 0))
    {
      return 0;
    }
  }
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (c->session != 0)
    {
      return 0;
    }
  }

  cmd_wait_for_flush();
  if (!((&clients)->tqh_first == 0))
  {
    return 0;
  }
  for (job_idx = (&all_jobs)->lh_first; (&job[job_idx]) != 0; job_idx = job_idx->entry.le_next)
  {
    if (((~job->flags) & 0x1) && (job->state == JOB_RUNNING))
    {
      return 0;
    }
  }

  return 1;
}


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
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


----------------------------
extern struct joblist all_jobs
----------------------------
struct sessions
{
  struct session *rbh_root;
}
----------------------------
static int server_exit
----------------------------
void server_client_loop(void)
{
  struct client *c;
  unsigned int c_idx = 0;
  struct window *w;
  unsigned int w_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  int focus;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    server_client_check_exit(c);
    if (c->session != 0)
    {
      server_client_check_redraw(c);
      server_client_reset_state(c);
    }
  }

  focus = options_get_number(global_options, "focus-events");
  for (w_idx = windows_RB_MINMAX(&windows, -1); (&w[w_idx]) != 0; w_idx = windows_RB_NEXT(w_idx))
  {
    for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
    {
      if (wp->fd != (-1))
      {
        if (focus)
        {
          server_client_check_focus(wp);
        }
        server_client_check_resize(wp);
      }
      wp->flags &= ~0x1;
    }

    check_window_name(w);
  }

}


----------------------------
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


----------------------------
None
----------------------------
***/


void server_update_socket(void)
{
  struct session *s;
  unsigned int s_idx = 0;
  static int last = -1;
  int n;
  int mode;
  struct stat sb;
  n = 0;
  for (s_idx = sessions_RB_MINMAX(&sessions, -1); (&s[s_idx]) != 0; s_idx = sessions_RB_NEXT(s_idx))
  {
    if (!(s->flags & 0x1))
    {
      n += 1;
      break;
    }
  }

  if (n != last)
  {
    last = n;
    if (stat(socket_path, &sb) != 0)
    {
      return;
    }
    mode = sb.st_mode & ((S_IRWXU | S_IRWXG) | S_IRWXO);
    if (n != 0)
    {
      if (mode & S_IRUSR)
      {
        mode |= S_IXUSR;
      }
      if (mode & S_IRGRP)
      {
        mode |= S_IXGRP;
      }
      if (mode & S_IROTH)
      {
        mode |= S_IXOTH;
      }
    }
    else
      mode &= ~((S_IXUSR | S_IXGRP) | S_IXOTH);
    chmod(socket_path, mode);
  }
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
extern const char *socket_path
----------------------------
None
----------------------------
***/


static void server_send_exit(void)
{
  struct client *c;
  unsigned int c_idx = 0;
  struct client *c1;
  unsigned int c1_idx = 0;
  struct session *s;
  unsigned int s_idx = 0;
  struct session *s1;
  unsigned int s1_idx = 0;
  cmd_wait_for_flush();
  for (c_idx = (&clients)->tqh_first; ((&c[c_idx]) != 0) && ((c1_idx = c->entry.tqe_next, 1)); c_idx = &c1[c1_idx])
  {
    if (c->flags & 0x40)
    {
      server_client_lost(c);
    }
    else
    {
      if (c->flags & 0x80)
      {
        notify_client("client-detached", c);
      }
      proc_send(c->peer, MSG_SHUTDOWN, -1, 0, 0);
    }
    c->session = 0;
  }

  for (s_idx = sessions_RB_MINMAX(&sessions, -1); ((&s[s_idx]) != 0) && ((s1_idx = sessions_RB_NEXT(s), 1)); s_idx = &s1[s1_idx])
  {
    session_destroy(s, __func__);
  }

}


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
}
----------------------------
void notify_client(const char *name, struct client *c)
{
  struct cmd_find_state fs;
  cmd_find_from_client(&fs, c, 0);
  notify_add(name, &fs, c, 0, 0, 0);
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
struct sessions
{
  struct session *rbh_root;
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
None
----------------------------
***/


static void server_child_stopped(pid_t pid, int status)
{
  struct window *w;
  unsigned int w_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  if ((WSTOPSIG(status) == SIGTTIN) || (WSTOPSIG(status) == SIGTTOU))
  {
    return;
  }
  for (w_idx = windows_RB_MINMAX(&windows, -1); (&w[w_idx]) != 0; w_idx = windows_RB_NEXT(w_idx))
  {
    for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
    {
      if (wp->pid == pid)
      {
        if (killpg(pid, SIGCONT) != 0)
        {
          kill(pid, SIGCONT);
        }
      }
    }

  }

}


/*** DEPENDENCIES:
struct windows
{
  struct window *rbh_root;
}
----------------------------
struct window *windows_RB_MINMAX(struct windows *head, int val)
{
  struct window *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct window *parent = 0;
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
struct window *windows_RB_NEXT(struct window *elm)
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


static void server_child_exited(pid_t pid, int status)
{
  struct window *w;
  unsigned int w_idx = 0;
  struct window *w1;
  unsigned int w1_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  struct job *job;
  unsigned int job_idx = 0;
  for (w_idx = windows_RB_MINMAX(&windows, -1); ((&w[w_idx]) != 0) && ((w1_idx = windows_RB_NEXT(w), 1)); w_idx = &w1[w1_idx])
  {
    for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
    {
      if (wp->pid == pid)
      {
        wp->status = status;
        wp->flags |= 0x200;
        log_debug("%%%u exited", wp->id);
        wp->flags |= 0x100;
        if (window_pane_destroy_ready(wp))
        {
          server_destroy_pane(wp, 1);
        }
        break;
      }
    }

  }

  for (job_idx = (&all_jobs)->lh_first; (&job[job_idx]) != 0; job_idx = job_idx->entry.le_next)
  {
    if (pid == job->pid)
    {
      job_died(job, status);
      break;
    }
  }

}


/*** DEPENDENCIES:
struct window *windows_RB_NEXT(struct window *elm)
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
struct windows
{
  struct window *rbh_root;
}
----------------------------
void job_died(struct job *job, int status)
{
  log_debug("job died %p: %s, pid %ld", job, job->cmd, (long) job->pid);
  job->status = status;
  if (job->state == JOB_CLOSED)
  {
    if (job->completecb != 0)
    {
      job->completecb(job);
    }
    job_free(job);
  }
  else
  {
    job->pid = -1;
    job->state = JOB_DEAD;
  }
}


----------------------------
struct window *windows_RB_MINMAX(struct windows *head, int val)
{
  struct window *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct window *parent = 0;
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
void server_destroy_pane(struct window_pane *wp, int notify)
{
  struct window *w = wp->window;
  struct screen_write_ctx ctx;
  struct grid_cell gc;
  time_t t;
  char tim[26];
  if (wp->fd != (-1))
  {
    bufferevent_free(wp->event);
    close(wp->fd);
    wp->fd = -1;
  }
  if (options_get_number(w->options, "remain-on-exit"))
  {
    helper_server_destroy_pane_1(wp, notify, ctx, gc, t, tim);
  }
  if (notify)
  {
    notify_pane("pane-exited", wp);
  }
  server_unzoom_window(w);
  layout_close_pane(wp);
  window_remove_pane(w, wp);
  if ((&w->panes)->tqh_first == 0)
  {
    server_kill_window(w);
  }
  else
    server_redraw_window(w);
}


----------------------------
extern struct joblist all_jobs
----------------------------
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
int window_pane_destroy_ready(struct window_pane *wp)
{
  int n;
  if (wp->pipe_fd != (-1))
  {
    if (EVBUFFER_LENGTH(wp->pipe_event->output) != 0)
    {
      return 0;
    }
    if ((ioctl(wp->fd, FIONREAD, &n) != (-1)) && (n > 0))
    {
      return 0;
    }
  }
  if ((~wp->flags) & 0x100)
  {
    return 0;
  }
  return 1;
}


----------------------------
None
----------------------------
***/


static void server_child_signal(void)
{
  int status;
  pid_t pid;
  for (;;)
  {
    switch (pid = waitpid(-1, &status, WNOHANG | WUNTRACED))
    {
      case -1:
      {
        if (errno == ECHILD)
        {
          return;
        }
        fatal("waitpid failed");
      }

      case 0:
      {
        return;
      }

    }

    if (WIFSTOPPED(status))
    {
      server_child_stopped(pid, status);
    }
    else
      if (WIFEXITED(status) || WIFSIGNALED(status))
    {
      server_child_exited(pid, status);
    }
  }

}


/*** DEPENDENCIES:
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
static void server_child_stopped(pid_t pid, int status)
{
  struct window *w;
  unsigned int w_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  if ((WSTOPSIG(status) == SIGTTIN) || (WSTOPSIG(status) == SIGTTOU))
  {
    return;
  }
  for (w_idx = windows_RB_MINMAX(&windows, -1); (&w[w_idx]) != 0; w_idx = windows_RB_NEXT(w_idx))
  {
    for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
    {
      if (wp->pid == pid)
      {
        if (killpg(pid, SIGCONT) != 0)
        {
          kill(pid, SIGCONT);
        }
      }
    }

  }

}


----------------------------
static void server_child_exited(pid_t pid, int status)
{
  struct window *w;
  unsigned int w_idx = 0;
  struct window *w1;
  unsigned int w1_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  struct job *job;
  unsigned int job_idx = 0;
  for (w_idx = windows_RB_MINMAX(&windows, -1); ((&w[w_idx]) != 0) && ((w1_idx = windows_RB_NEXT(w), 1)); w_idx = &w1[w1_idx])
  {
    for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
    {
      if (wp->pid == pid)
      {
        wp->status = status;
        wp->flags |= 0x200;
        log_debug("%%%u exited", wp->id);
        wp->flags |= 0x100;
        if (window_pane_destroy_ready(wp))
        {
          server_destroy_pane(wp, 1);
        }
        break;
      }
    }

  }

  for (job_idx = (&all_jobs)->lh_first; (&job[job_idx]) != 0; job_idx = job_idx->entry.le_next)
  {
    if (pid == job->pid)
    {
      job_died(job, status);
      break;
    }
  }

}


----------------------------
***/


static int server_create_socket(char **cause)
{
  struct sockaddr_un sa;
  size_t size;
  mode_t mask;
  int fd;
  int saved_errno;
  memset(&sa, 0, sizeof(sa));
  sa.sun_family = AF_UNIX;
  size = strlcpy(sa.sun_path, socket_path, sizeof(sa.sun_path));
  if (size >= (sizeof(sa.sun_path)))
  {
    errno = ENAMETOOLONG;
    goto fail;
  }
  unlink(sa.sun_path);
  if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == (-1))
  {
    goto fail;
  }
  mask = umask((S_IXUSR | S_IXGRP) | S_IRWXO);
  if (bind(fd, (struct sockaddr *) (&sa), sizeof(sa)) == (-1))
  {
    saved_errno = errno;
    close(fd);
    errno = saved_errno;
    goto fail;
  }
  umask(mask);
  if (listen(fd, 128) == (-1))
  {
    saved_errno = errno;
    close(fd);
    errno = saved_errno;
    goto fail;
  }
  setblocking(fd, 0);
  return fd;
  fail:
  if (cause != 0)
  {
    xasprintf(cause, "error creating %s (%s)", socket_path, strerror(errno));
  }

  return -1;
}


/*** DEPENDENCIES:
void setblocking(int fd, int state)
{
  int mode;
  if ((mode = fcntl(fd, F_GETFL)) != (-1))
  {
    if (!state)
    {
      mode |= O_NONBLOCK;
    }
    else
      mode &= ~O_NONBLOCK;
    fcntl(fd, F_SETFL, mode);
  }
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
extern const char *socket_path
----------------------------
***/


static void server_signal(int sig)
{
  int fd;
  log_debug("%s: %s", __func__, strsignal(sig));
  switch (sig)
  {
    case SIGTERM:
    {
      server_exit = 1;
      server_send_exit();
      break;
    }

    case SIGCHLD:
    {
      server_child_signal();
      break;
    }

    case SIGUSR1:
    {
      event_del(&server_ev_accept);
      fd = server_create_socket(0);
      if (fd != (-1))
      {
        close(server_fd);
        server_fd = fd;
        server_update_socket();
      }
      server_add_accept(0);
      break;
    }

    case SIGUSR2:
    {
      proc_toggle_log(server_proc);
      break;
    }

  }

}


/*** DEPENDENCIES:
void server_update_socket(void)
{
  struct session *s;
  unsigned int s_idx = 0;
  static int last = -1;
  int n;
  int mode;
  struct stat sb;
  n = 0;
  for (s_idx = sessions_RB_MINMAX(&sessions, -1); (&s[s_idx]) != 0; s_idx = sessions_RB_NEXT(s_idx))
  {
    if (!(s->flags & 0x1))
    {
      n += 1;
      break;
    }
  }

  if (n != last)
  {
    last = n;
    if (stat(socket_path, &sb) != 0)
    {
      return;
    }
    mode = sb.st_mode & ((S_IRWXU | S_IRWXG) | S_IRWXO);
    if (n != 0)
    {
      if (mode & S_IRUSR)
      {
        mode |= S_IXUSR;
      }
      if (mode & S_IRGRP)
      {
        mode |= S_IXGRP;
      }
      if (mode & S_IROTH)
      {
        mode |= S_IXOTH;
      }
    }
    else
      mode &= ~((S_IXUSR | S_IXGRP) | S_IXOTH);
    chmod(socket_path, mode);
  }
}


----------------------------
static int server_fd
----------------------------
static void server_send_exit(void)
{
  struct client *c;
  unsigned int c_idx = 0;
  struct client *c1;
  unsigned int c1_idx = 0;
  struct session *s;
  unsigned int s_idx = 0;
  struct session *s1;
  unsigned int s1_idx = 0;
  cmd_wait_for_flush();
  for (c_idx = (&clients)->tqh_first; ((&c[c_idx]) != 0) && ((c1_idx = c->entry.tqe_next, 1)); c_idx = &c1[c1_idx])
  {
    if (c->flags & 0x40)
    {
      server_client_lost(c);
    }
    else
    {
      if (c->flags & 0x80)
      {
        notify_client("client-detached", c);
      }
      proc_send(c->peer, MSG_SHUTDOWN, -1, 0, 0);
    }
    c->session = 0;
  }

  for (s_idx = sessions_RB_MINMAX(&sessions, -1); ((&s[s_idx]) != 0) && ((s1_idx = sessions_RB_NEXT(s), 1)); s_idx = &s1[s1_idx])
  {
    session_destroy(s, __func__);
  }

}


----------------------------
static void server_child_signal(void)
{
  int status;
  pid_t pid;
  for (;;)
  {
    switch (pid = waitpid(-1, &status, WNOHANG | WUNTRACED))
    {
      case -1:
      {
        if (errno == ECHILD)
        {
          return;
        }
        fatal("waitpid failed");
      }

      case 0:
      {
        return;
      }

    }

    if (WIFSTOPPED(status))
    {
      server_child_stopped(pid, status);
    }
    else
      if (WIFEXITED(status) || WIFSIGNALED(status))
    {
      server_child_exited(pid, status);
    }
  }

}


----------------------------
void proc_toggle_log(struct tmuxproc *tp)
{
  log_toggle(tp->name);
}


----------------------------
static int server_create_socket(char **cause)
{
  struct sockaddr_un sa;
  size_t size;
  mode_t mask;
  int fd;
  int saved_errno;
  memset(&sa, 0, sizeof(sa));
  sa.sun_family = AF_UNIX;
  size = strlcpy(sa.sun_path, socket_path, sizeof(sa.sun_path));
  if (size >= (sizeof(sa.sun_path)))
  {
    errno = ENAMETOOLONG;
    goto fail;
  }
  unlink(sa.sun_path);
  if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == (-1))
  {
    goto fail;
  }
  mask = umask((S_IXUSR | S_IXGRP) | S_IRWXO);
  if (bind(fd, (struct sockaddr *) (&sa), sizeof(sa)) == (-1))
  {
    saved_errno = errno;
    close(fd);
    errno = saved_errno;
    goto fail;
  }
  umask(mask);
  if (listen(fd, 128) == (-1))
  {
    saved_errno = errno;
    close(fd);
    errno = saved_errno;
    goto fail;
  }
  setblocking(fd, 0);
  return fd;
  fail:
  if (cause != 0)
  {
    xasprintf(cause, "error creating %s (%s)", socket_path, strerror(errno));
  }

  return -1;
}


----------------------------
static int server_exit
----------------------------
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
static struct event server_ev_accept
----------------------------
None
----------------------------
***/


int server_start(struct tmuxproc *client, struct event_base *base, int lockfd, char *lockfile)
{
  int pair[2];
  struct job *job;
  unsigned int job_idx = 0;
  sigset_t set;
  sigset_t oldset;
  struct client *c;
  unsigned int c_idx = 0;
  char *cause = 0;
  if (socketpair(AF_UNIX, SOCK_STREAM, PF_UNSPEC, pair) != 0)
  {
    fatal("socketpair failed");
  }
  sigfillset(&set);
  sigprocmask(SIG_BLOCK, &set, &oldset);
  switch (fork())
  {
    case -1:
    {
      fatal("fork failed");
    }

    case 0:
    {
      break;
    }

    default:
    {
      sigprocmask(SIG_SETMASK, &oldset, 0);
      close(pair[1]);
      return pair[0];
    }

  }

  close(pair[0]);
  if (daemon(1, 0) != 0)
  {
    fatal("daemon failed");
  }
  proc_clear_signals(client, 0);
  if (event_reinit(base) != 0)
  {
    fatalx("event_reinit failed");
  }
  server_proc = proc_start("server");
  proc_set_signals(server_proc, server_signal);
  sigprocmask(SIG_SETMASK, &oldset, 0);
  if (log_get_level() > 1)
  {
    tty_create_log();
  }
  if (0 != 0)
  {
    fatal("pledge failed");
  }
  do
  {
    (&windows)->rbh_root = 0;
  }
  while (0);
  do
  {
    (&all_window_panes)->rbh_root = 0;
  }
  while (0);
  do
  {
    (&clients)->tqh_first = 0;
    (&clients)->tqh_last = &(&clients)->tqh_first;
  }
  while (0);
  do
  {
    (&sessions)->rbh_root = 0;
  }
  while (0);
  do
  {
    (&session_groups)->rbh_root = 0;
  }
  while (0);
  key_bindings_init();
  gettimeofday(&start_time, 0);
  server_fd = server_create_socket(&cause);
  if (server_fd != (-1))
  {
    server_update_socket();
  }
  c_idx = server_client_create(pair[1]);
  if (lockfd >= 0)
  {
    unlink(lockfile);
    free(lockfile);
    close(lockfd);
  }
  if (cause != 0)
  {
    cmdq_append(c, cmdq_get_callback1("server_start_error", server_start_error, cause));
    c->flags |= 0x4;
  }
  start_cfg();
  server_add_accept(0);
  proc_loop(server_proc, server_loop);
  for (job_idx = (&all_jobs)->lh_first; (&job[job_idx]) != 0; job_idx = job_idx->entry.le_next)
  {
    if (job->pid != (-1))
    {
      kill(job->pid, SIGTERM);
    }
  }

  status_prompt_save_history();
  exit(0);
}


/*** DEPENDENCIES:
void tty_create_log(void)
{
  char name[64];
  xsnprintf(name, sizeof(name), "tmux-out-%ld.log", (long) getpid());
  tty_log_fd = open(name, (O_WRONLY | O_CREAT) | O_TRUNC, 0644);
  if ((tty_log_fd != (-1)) && (fcntl(tty_log_fd, F_SETFD, FD_CLOEXEC) == (-1)))
  {
    fatal("fcntl failed");
  }
}


----------------------------
extern struct timeval start_time
----------------------------
struct windows
{
  struct window *rbh_root;
}
----------------------------
void proc_clear_signals(struct tmuxproc *tp, int defaults)
{
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  sa.sa_handler = SIG_DFL;
  sigaction(SIGINT, &sa, 0);
  sigaction(SIGPIPE, &sa, 0);
  sigaction(SIGTSTP, &sa, 0);
  signal_del(&tp->ev_sighup);
  signal_del(&tp->ev_sigchld);
  signal_del(&tp->ev_sigcont);
  signal_del(&tp->ev_sigterm);
  signal_del(&tp->ev_sigusr1);
  signal_del(&tp->ev_sigusr2);
  signal_del(&tp->ev_sigwinch);
  if (defaults)
  {
    sigaction(SIGHUP, &sa, 0);
    sigaction(SIGCHLD, &sa, 0);
    sigaction(SIGCONT, &sa, 0);
    sigaction(SIGTERM, &sa, 0);
    sigaction(SIGUSR1, &sa, 0);
    sigaction(SIGUSR2, &sa, 0);
    sigaction(SIGWINCH, &sa, 0);
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
void proc_loop(struct tmuxproc *tp, int (*loopcb)(void))
{
  log_debug("%s loop enter", tp->name);
  do
  {
    event_loop(EVLOOP_ONCE);
  }
  while ((!tp->exit) && ((loopcb == 0) || (!loopcb())));
  log_debug("%s loop exit", tp->name);
}


----------------------------
extern struct window_pane_tree all_window_panes
----------------------------
struct tmuxproc
{
  const char *name;
  int exit;
  void (*signalcb)(int);
  struct event ev_sighup;
  struct event ev_sigchld;
  struct event ev_sigcont;
  struct event ev_sigterm;
  struct event ev_sigusr1;
  struct event ev_sigusr2;
  struct event ev_sigwinch;
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
static enum cmd_retval server_start_error(struct cmdq_item *item, void *data)
{
  char *error = data;
  cmdq_error(item, "%s", error);
  free(error);
  return CMD_RETURN_NORMAL;
}


----------------------------
static int server_loop(void)
{
  struct client *c;
  unsigned int c_idx = 0;
  u_int items;
  struct job *job;
  unsigned int job_idx = 0;
  do
  {
    items = cmdq_next(0);
    for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
    {
      if (c->flags & 0x40000)
      {
        items += cmdq_next(c);
      }
    }

  }
  while (items != 0);
  server_client_loop();
  if ((!options_get_number(global_options, "exit-empty")) && (!server_exit))
  {
    return 0;
  }
  if (!options_get_number(global_options, "exit-unattached"))
  {
    if (!((&sessions)->rbh_root == 0))
    {
      return 0;
    }
  }
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (c->session != 0)
    {
      return 0;
    }
  }

  cmd_wait_for_flush();
  if (!((&clients)->tqh_first == 0))
  {
    return 0;
  }
  for (job_idx = (&all_jobs)->lh_first; (&job[job_idx]) != 0; job_idx = job_idx->entry.le_next)
  {
    if (((~job->flags) & 0x1) && (job->state == JOB_RUNNING))
    {
      return 0;
    }
  }

  return 1;
}


----------------------------
extern struct joblist all_jobs
----------------------------
void proc_set_signals(struct tmuxproc *tp, void (*signalcb)(int))
{
  struct sigaction sa;
  tp->signalcb = signalcb;
  memset(&sa, 0, sizeof(sa));
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  sa.sa_handler = SIG_IGN;
  sigaction(SIGINT, &sa, 0);
  sigaction(SIGPIPE, &sa, 0);
  sigaction(SIGTSTP, &sa, 0);
  signal_set(&tp->ev_sighup, SIGHUP, proc_signal_cb, tp);
  signal_add(&tp->ev_sighup, 0);
  signal_set(&tp->ev_sigchld, SIGCHLD, proc_signal_cb, tp);
  signal_add(&tp->ev_sigchld, 0);
  signal_set(&tp->ev_sigcont, SIGCONT, proc_signal_cb, tp);
  signal_add(&tp->ev_sigcont, 0);
  signal_set(&tp->ev_sigterm, SIGTERM, proc_signal_cb, tp);
  signal_add(&tp->ev_sigterm, 0);
  signal_set(&tp->ev_sigusr1, SIGUSR1, proc_signal_cb, tp);
  signal_add(&tp->ev_sigusr1, 0);
  signal_set(&tp->ev_sigusr2, SIGUSR2, proc_signal_cb, tp);
  signal_add(&tp->ev_sigusr2, 0);
  signal_set(&tp->ev_sigwinch, SIGWINCH, proc_signal_cb, tp);
  signal_add(&tp->ev_sigwinch, 0);
}


----------------------------
static void server_signal(int sig)
{
  int fd;
  log_debug("%s: %s", __func__, strsignal(sig));
  switch (sig)
  {
    case SIGTERM:
    {
      server_exit = 1;
      server_send_exit();
      break;
    }

    case SIGCHLD:
    {
      server_child_signal();
      break;
    }

    case SIGUSR1:
    {
      event_del(&server_ev_accept);
      fd = server_create_socket(0);
      if (fd != (-1))
      {
        close(server_fd);
        server_fd = fd;
        server_update_socket();
      }
      server_add_accept(0);
      break;
    }

    case SIGUSR2:
    {
      proc_toggle_log(server_proc);
      break;
    }

  }

}


----------------------------
void status_prompt_save_history(void)
{
  FILE *f;
  unsigned int f_idx = 0;
  u_int i;
  char *history_file;
  unsigned int history_file_idx = 0;
  if ((history_file_idx = status_prompt_find_history_file()) == 0)
  {
    return;
  }
  log_debug("saving history to %s", history_file);
  f_idx = fopen(history_file, "w");
  if ((&f[f_idx]) == 0)
  {
    log_debug("%s: %s", history_file, strerror(errno));
    free(history_file);
    return;
  }
  free(history_file);
  for (i = 0; i < status_prompt_hsize; i += 1)
  {
    fputs(status_prompt_hlist[i], f);
    fputc('\n', f);
  }

  fclose(f);
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
int log_get_level(void)
{
  return log_level;
}


----------------------------
static int server_create_socket(char **cause)
{
  struct sockaddr_un sa;
  size_t size;
  mode_t mask;
  int fd;
  int saved_errno;
  memset(&sa, 0, sizeof(sa));
  sa.sun_family = AF_UNIX;
  size = strlcpy(sa.sun_path, socket_path, sizeof(sa.sun_path));
  if (size >= (sizeof(sa.sun_path)))
  {
    errno = ENAMETOOLONG;
    goto fail;
  }
  unlink(sa.sun_path);
  if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) == (-1))
  {
    goto fail;
  }
  mask = umask((S_IXUSR | S_IXGRP) | S_IRWXO);
  if (bind(fd, (struct sockaddr *) (&sa), sizeof(sa)) == (-1))
  {
    saved_errno = errno;
    close(fd);
    errno = saved_errno;
    goto fail;
  }
  umask(mask);
  if (listen(fd, 128) == (-1))
  {
    saved_errno = errno;
    close(fd);
    errno = saved_errno;
    goto fail;
  }
  setblocking(fd, 0);
  return fd;
  fail:
  if (cause != 0)
  {
    xasprintf(cause, "error creating %s (%s)", socket_path, strerror(errno));
  }

  return -1;
}


----------------------------
struct sessions
{
  struct session *rbh_root;
}
----------------------------
static int server_fd
----------------------------
None
----------------------------
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
}
----------------------------
void server_update_socket(void)
{
  struct session *s;
  unsigned int s_idx = 0;
  static int last = -1;
  int n;
  int mode;
  struct stat sb;
  n = 0;
  for (s_idx = sessions_RB_MINMAX(&sessions, -1); (&s[s_idx]) != 0; s_idx = sessions_RB_NEXT(s_idx))
  {
    if (!(s->flags & 0x1))
    {
      n += 1;
      break;
    }
  }

  if (n != last)
  {
    last = n;
    if (stat(socket_path, &sb) != 0)
    {
      return;
    }
    mode = sb.st_mode & ((S_IRWXU | S_IRWXG) | S_IRWXO);
    if (n != 0)
    {
      if (mode & S_IRUSR)
      {
        mode |= S_IXUSR;
      }
      if (mode & S_IRGRP)
      {
        mode |= S_IXGRP;
      }
      if (mode & S_IROTH)
      {
        mode |= S_IXOTH;
      }
    }
    else
      mode &= ~((S_IXUSR | S_IXGRP) | S_IXOTH);
    chmod(socket_path, mode);
  }
}


----------------------------
void start_cfg(void)
{
  const char *home;
  unsigned int home_idx = 0;
  int quiet = 0;
  struct client *c;
  unsigned int c_idx = 0;
  c_idx = (&clients)->tqh_first;
  if ((&c[c_idx]) != 0)
  {
    cfg_item = cmdq_get_callback1("cfg_client_done", cfg_client_done, 0);
    cmdq_append(c, cfg_item);
  }
  load_cfg("/etc/tmux.conf", 0, 0, 1);
  if ((cfg_file == 0) && ((home_idx = find_home()) != 0))
  {
    xasprintf(&cfg_file, "%s/.tmux.conf", home);
    quiet = 1;
  }
  if (cfg_file != 0)
  {
    load_cfg(cfg_file, 0, 0, quiet);
  }
  cmdq_append(0, cmdq_get_callback1("cfg_done", cfg_done, 0));
}


----------------------------
struct tmuxproc *proc_start(const char *name)
{
  struct tmuxproc *tp;
  unsigned int tp_idx = 0;
  struct utsname u;
  log_open(name);
  setproctitle("%s (%s)", name, socket_path);
  if (uname(&u) < 0)
  {
    memset(&u, 0, sizeof(u));
  }
  log_debug("%s started (%ld): version %s, socket %s, protocol %d", name, (long) getpid(), VERSION, socket_path, 8);
  log_debug("on %s %s %s; libevent %s (%s)", u.sysname, u.release, u.version, event_get_version(), event_get_method());
  tp_idx = xcalloc(1, sizeof(*tp_idx));
  tp->name = xstrdup(name);
  return tp;
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
struct session_groups
{
  struct session_group *rbh_root;
}
----------------------------
void key_bindings_init(void)
{
  static const char *defaults[] = {"bind C-b send-prefix", "bind C-o rotate-window", "bind C-z suspend-client", "bind Space next-layout", "bind ! break-pane", "bind '\"' split-window", "bind '#' list-buffers", "bind '$' command-prompt -I'#S' \"rename-session -- '%%'\"", "bind % split-window -h", "bind & confirm-before -p\"kill-window #W? (y/n)\" kill-window", "bind \"'\" command-prompt -pindex \"select-window -t ':%%'\"", "bind ( switch-client -p", "bind ) switch-client -n", "bind , command-prompt -I'#W' \"rename-window -- '%%'\"", "bind - delete-buffer", "bind . command-prompt \"move-window -t '%%'\"", "bind 0 select-window -t:=0", "bind 1 select-window -t:=1", "bind 2 select-window -t:=2", "bind 3 select-window -t:=3", "bind 4 select-window -t:=4", "bind 5 select-window -t:=5", "bind 6 select-window -t:=6", "bind 7 select-window -t:=7", "bind 8 select-window -t:=8", "bind 9 select-window -t:=9", "bind : command-prompt", "bind \\; last-pane", "bind = choose-buffer -Z", "bind ? list-keys", "bind D choose-client -Z", "bind E select-layout -E", "bind L switch-client -l", "bind M select-pane -M", "bind [ copy-mode", "bind ] paste-buffer", "bind c new-window", "bind d detach-client", "bind f command-prompt \"find-window -- '%%'\"", "bind i display-message", "bind l last-window", "bind m select-pane -m", "bind n next-window", "bind o select-pane -t:.+", "bind p previous-window", "bind q display-panes", "bind r refresh-client", "bind s choose-tree -Zs", "bind t clock-mode", "bind w choose-tree -Zw", "bind x confirm-before -p\"kill-pane #P? (y/n)\" kill-pane", "bind z resize-pane -Z", "bind { swap-pane -U", "bind } swap-pane -D", "bind '~' show-messages", "bind PPage copy-mode -u", "bind -r Up select-pane -U", "bind -r Down select-pane -D", "bind -r Left select-pane -L", "bind -r Right select-pane -R", "bind M-1 select-layout even-horizontal", "bind M-2 select-layout even-vertical", "bind M-3 select-layout main-horizontal", "bind M-4 select-layout main-vertical", "bind M-5 select-layout tiled", "bind M-n next-window -a", "bind M-o rotate-window -D", "bind M-p previous-window -a", "bind -r M-Up resize-pane -U 5", "bind -r M-Down resize-pane -D 5", "bind -r M-Left resize-pane -L 5", "bind -r M-Right resize-pane -R 5", "bind -r C-Up resize-pane -U", "bind -r C-Down resize-pane -D", "bind -r C-Left resize-pane -L", "bind -r C-Right resize-pane -R", "bind -n MouseDown1Pane select-pane -t=\\; send-keys -M", "bind -n MouseDrag1Border resize-pane -M", "bind -n MouseDown1Status select-window -t=", "bind -n WheelDownStatus next-window", "bind -n WheelUpStatus previous-window", "bind -n MouseDrag1Pane if -Ft= '#{mouse_any_flag}' 'if -Ft= \"#{pane_in_mode}\" \"copy-mode -M\" \"send-keys -M\"' 'copy-mode -M'", "bind -n MouseDown3Pane if-shell -Ft= '#{mouse_any_flag}' 'select-pane -t=; send-keys -M' 'select-pane -mt='", "bind -n WheelUpPane if-shell -Ft= '#{mouse_any_flag}' 'send-keys -M' 'if -Ft= \"#{pane_in_mode}\" \"send-keys -M\" \"copy-mode -et=\"'", "bind -Tcopy-mode C-Space send -X begin-selection", "bind -Tcopy-mode C-a send -X start-of-line", "bind -Tcopy-mode C-c send -X cancel", "bind -Tcopy-mode C-e send -X end-of-line", "bind -Tcopy-mode C-f send -X cursor-right", "bind -Tcopy-mode C-b send -X cursor-left", "bind -Tcopy-mode C-g send -X clear-selection", "bind -Tcopy-mode C-k send -X copy-end-of-line", "bind -Tcopy-mode C-n send -X cursor-down", "bind -Tcopy-mode C-p send -X cursor-up", "bind -Tcopy-mode C-r command-prompt -ip'(search up)' -I'#{pane_search_string}' 'send -X search-backward-incremental \"%%%\"'", "bind -Tcopy-mode C-s command-prompt -ip'(search down)' -I'#{pane_search_string}' 'send -X search-forward-incremental \"%%%\"'", "bind -Tcopy-mode C-v send -X page-down", "bind -Tcopy-mode C-w send -X copy-selection-and-cancel", "bind -Tcopy-mode Escape send -X cancel", "bind -Tcopy-mode Space send -X page-down", "bind -Tcopy-mode , send -X jump-reverse", "bind -Tcopy-mode \\; send -X jump-again", "bind -Tcopy-mode F command-prompt -1p'(jump backward)' 'send -X jump-backward \"%%%\"'", "bind -Tcopy-mode N send -X search-reverse", "bind -Tcopy-mode R send -X rectangle-toggle", "bind -Tcopy-mode T command-prompt -1p'(jump to backward)' 'send -X jump-to-backward \"%%%\"'", "bind -Tcopy-mode f command-prompt -1p'(jump forward)' 'send -X jump-forward \"%%%\"'", "bind -Tcopy-mode g command-prompt -p'(goto line)' 'send -X goto-line \"%%%\"'", "bind -Tcopy-mode n send -X search-again", "bind -Tcopy-mode q send -X cancel", "bind -Tcopy-mode t command-prompt -1p'(jump to forward)' 'send -X jump-to-forward \"%%%\"'", "bind -Tcopy-mode Home send -X start-of-line", "bind -Tcopy-mode End send -X end-of-line", "bind -Tcopy-mode MouseDown1Pane select-pane", "bind -Tcopy-mode MouseDrag1Pane select-pane\\; send -X begin-selection", "bind -Tcopy-mode MouseDragEnd1Pane send -X copy-selection-and-cancel", "bind -Tcopy-mode WheelUpPane select-pane\\; send -N5 -X scroll-up", "bind -Tcopy-mode WheelDownPane select-pane\\; send -N5 -X scroll-down", "bind -Tcopy-mode DoubleClick1Pane select-pane\\; send -X select-word", "bind -Tcopy-mode TripleClick1Pane select-pane\\; send -X select-line", "bind -Tcopy-mode NPage send -X page-down", "bind -Tcopy-mode PPage send -X page-up", "bind -Tcopy-mode Up send -X cursor-up", "bind -Tcopy-mode Down send -X cursor-down", "bind -Tcopy-mode Left send -X cursor-left", "bind -Tcopy-mode Right send -X cursor-right", "bind -Tcopy-mode M-1 command-prompt -Np'(repeat)' -I1 'send -N \"%%%\"'", "bind -Tcopy-mode M-2 command-prompt -Np'(repeat)' -I2 'send -N \"%%%\"'", "bind -Tcopy-mode M-3 command-prompt -Np'(repeat)' -I3 'send -N \"%%%\"'", "bind -Tcopy-mode M-4 command-prompt -Np'(repeat)' -I4 'send -N \"%%%\"'", "bind -Tcopy-mode M-5 command-prompt -Np'(repeat)' -I5 'send -N \"%%%\"'", "bind -Tcopy-mode M-6 command-prompt -Np'(repeat)' -I6 'send -N \"%%%\"'", "bind -Tcopy-mode M-7 command-prompt -Np'(repeat)' -I7 'send -N \"%%%\"'", "bind -Tcopy-mode M-8 command-prompt -Np'(repeat)' -I8 'send -N \"%%%\"'", "bind -Tcopy-mode M-9 command-prompt -Np'(repeat)' -I9 'send -N \"%%%\"'", "bind -Tcopy-mode M-< send -X history-top", "bind -Tcopy-mode M-> send -X history-bottom", "bind -Tcopy-mode M-R send -X top-line", "bind -Tcopy-mode M-b send -X previous-word", "bind -Tcopy-mode M-f send -X next-word-end", "bind -Tcopy-mode M-m send -X back-to-indentation", "bind -Tcopy-mode M-r send -X middle-line", "bind -Tcopy-mode M-v send -X page-up", "bind -Tcopy-mode M-w send -X copy-selection-and-cancel", "bind -Tcopy-mode M-{ send -X previous-paragraph", "bind -Tcopy-mode M-} send -X next-paragraph", "bind -Tcopy-mode M-Up send -X halfpage-up", "bind -Tcopy-mode M-Down send -X halfpage-down", "bind -Tcopy-mode C-Up send -X scroll-up", "bind -Tcopy-mode C-Down send -X scroll-down", "bind -Tcopy-mode-vi C-c send -X cancel", "bind -Tcopy-mode-vi C-d send -X halfpage-down", "bind -Tcopy-mode-vi C-e send -X scroll-down", "bind -Tcopy-mode-vi C-b send -X page-up", "bind -Tcopy-mode-vi C-f send -X page-down", "bind -Tcopy-mode-vi C-h send -X cursor-left", "bind -Tcopy-mode-vi C-j send -X copy-selection-and-cancel", "bind -Tcopy-mode-vi Enter send -X copy-selection-and-cancel", "bind -Tcopy-mode-vi C-u send -X halfpage-up", "bind -Tcopy-mode-vi C-v send -X rectangle-toggle", "bind -Tcopy-mode-vi C-y send -X scroll-up", "bind -Tcopy-mode-vi Escape send -X clear-selection", "bind -Tcopy-mode-vi Space send -X begin-selection", "bind -Tcopy-mode-vi '$' send -X end-of-line", "bind -Tcopy-mode-vi , send -X jump-reverse", "bind -Tcopy-mode-vi / command-prompt -p'(search down)' 'send -X search-forward \"%%%\"'", "bind -Tcopy-mode-vi 0 send -X start-of-line", "bind -Tcopy-mode-vi 1 command-prompt -Np'(repeat)' -I1 'send -N \"%%%\"'", "bind -Tcopy-mode-vi 2 command-prompt -Np'(repeat)' -I2 'send -N \"%%%\"'", "bind -Tcopy-mode-vi 3 command-prompt -Np'(repeat)' -I3 'send -N \"%%%\"'", "bind -Tcopy-mode-vi 4 command-prompt -Np'(repeat)' -I4 'send -N \"%%%\"'", "bind -Tcopy-mode-vi 5 command-prompt -Np'(repeat)' -I5 'send -N \"%%%\"'", "bind -Tcopy-mode-vi 6 command-prompt -Np'(repeat)' -I6 'send -N \"%%%\"'", "bind -Tcopy-mode-vi 7 command-prompt -Np'(repeat)' -I7 'send -N \"%%%\"'", "bind -Tcopy-mode-vi 8 command-prompt -Np'(repeat)' -I8 'send -N \"%%%\"'", "bind -Tcopy-mode-vi 9 command-prompt -Np'(repeat)' -I9 'send -N \"%%%\"'", "bind -Tcopy-mode-vi : command-prompt -p'(goto line)' 'send -X goto-line \"%%%\"'", "bind -Tcopy-mode-vi \\; send -X jump-again", "bind -Tcopy-mode-vi ? command-prompt -p'(search up)' 'send -X search-backward \"%%%\"'", "bind -Tcopy-mode-vi A send -X append-selection-and-cancel", "bind -Tcopy-mode-vi B send -X previous-space", "bind -Tcopy-mode-vi D send -X copy-end-of-line", "bind -Tcopy-mode-vi E send -X next-space-end", "bind -Tcopy-mode-vi F command-prompt -1p'(jump backward)' 'send -X jump-backward \"%%%\"'", "bind -Tcopy-mode-vi G send -X history-bottom", "bind -Tcopy-mode-vi H send -X top-line", "bind -Tcopy-mode-vi J send -X scroll-down", "bind -Tcopy-mode-vi K send -X scroll-up", "bind -Tcopy-mode-vi L send -X bottom-line", "bind -Tcopy-mode-vi M send -X middle-line", "bind -Tcopy-mode-vi N send -X search-reverse", "bind -Tcopy-mode-vi T command-prompt -1p'(jump to backward)' 'send -X jump-to-backward \"%%%\"'", "bind -Tcopy-mode-vi V send -X select-line", "bind -Tcopy-mode-vi W send -X next-space", "bind -Tcopy-mode-vi ^ send -X back-to-indentation", "bind -Tcopy-mode-vi b send -X previous-word", "bind -Tcopy-mode-vi e send -X next-word-end", "bind -Tcopy-mode-vi f command-prompt -1p'(jump forward)' 'send -X jump-forward \"%%%\"'", "bind -Tcopy-mode-vi g send -X history-top", "bind -Tcopy-mode-vi h send -X cursor-left", "bind -Tcopy-mode-vi j send -X cursor-down", "bind -Tcopy-mode-vi k send -X cursor-up", "bind -Tcopy-mode-vi l send -X cursor-right", "bind -Tcopy-mode-vi n send -X search-again", "bind -Tcopy-mode-vi o send -X other-end", "bind -Tcopy-mode-vi q send -X cancel", "bind -Tcopy-mode-vi t command-prompt -1p'(jump to forward)' 'send -X jump-to-forward \"%%%\"'", "bind -Tcopy-mode-vi v send -X rectangle-toggle", "bind -Tcopy-mode-vi w send -X next-word", "bind -Tcopy-mode-vi { send -X previous-paragraph", "bind -Tcopy-mode-vi } send -X next-paragraph", "bind -Tcopy-mode-vi MouseDown1Pane select-pane", "bind -Tcopy-mode-vi MouseDrag1Pane select-pane\\; send -X begin-selection", "bind -Tcopy-mode-vi MouseDragEnd1Pane send -X copy-selection-and-cancel", "bind -Tcopy-mode-vi WheelUpPane select-pane\\; send -N5 -X scroll-up", "bind -Tcopy-mode-vi WheelDownPane select-pane\\; send -N5 -X scroll-down", "bind -Tcopy-mode-vi DoubleClick1Pane select-pane\\; send -X select-word", "bind -Tcopy-mode-vi TripleClick1Pane select-pane\\; send -X select-line", "bind -Tcopy-mode-vi BSpace send -X cursor-left", "bind -Tcopy-mode-vi NPage send -X page-down", "bind -Tcopy-mode-vi PPage send -X page-up", "bind -Tcopy-mode-vi Up send -X cursor-up", "bind -Tcopy-mode-vi Down send -X cursor-down", "bind -Tcopy-mode-vi Left send -X cursor-left", "bind -Tcopy-mode-vi Right send -X cursor-right", "bind -Tcopy-mode-vi C-Up send -X scroll-up", "bind -Tcopy-mode-vi C-Down send -X scroll-down"};
  u_int i;
  struct cmd_list *cmdlist;
  unsigned int cmdlist_idx = 0;
  char *cause;
  for (i = 0; i < ((sizeof(defaults)) / (sizeof(defaults[0]))); i += 1)
  {
    cmdlist_idx = cmd_string_parse(defaults[i], "<default>", i, &cause);
    if ((&cmdlist[cmdlist_idx]) == 0)
    {
      fatalx("bad default key: %s", defaults[i]);
    }
    cmdq_append(0, cmdq_get_command(cmdlist, 0, 0, 0));
    cmd_list_free(cmdlist);
  }

}


----------------------------
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


----------------------------
None
----------------------------
***/


void server_set_marked(struct session *s, struct winlink *wl, struct window_pane *wp)
{
  cmd_find_clear_state(&marked_pane, 0);
  marked_pane.s = s;
  marked_pane.wl = wl;
  marked_pane.w = wl->window;
  marked_pane.wp = wp;
}


/*** DEPENDENCIES:
extern struct cmd_find_state marked_pane
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


