// element in merge of:  server_add_accept,server_client_lost,server_accept,server_client_dispatch,server_client_create
void server_add_accept(int timeout)
{
  struct timeval tv = {timeout, 0};
  if (event_initialized(&server_ev_accept))
  {
    event_del(&server_ev_accept);
  }
  if (timeout == 0)
  {
    event_set(&server_ev_accept, server_fd, EV_READ, server_accept, 0);
    event_add(&server_ev_accept, 0);
  }
  else
  {
    event_set(&server_ev_accept, server_fd, EV_TIMEOUT, server_accept, 0);
    event_add(&server_ev_accept, &tv);
  }
}


/*** DEPENDENCIES:
static int server_fd
----------------------------
static struct event server_ev_accept
----------------------------
None
----------------------------
***/


// element in merge of:  server_add_accept,server_client_lost,server_accept,server_client_dispatch,server_client_create
void server_client_lost(struct client *c)
{
  struct message_entry *msg;
  unsigned int msg_idx = 0;
  struct message_entry *msg1;
  unsigned int msg1_idx = 0;
  c->flags |= 0x200;
  server_client_clear_identify(c, 0);
  status_prompt_clear(c);
  status_message_clear(c);
  if (c->stdin_callback != 0)
  {
    c->stdin_callback(c, 1, c->stdin_callback_data);
  }
  do
  {
    if (c->entry.tqe_next != 0)
    {
      c->entry.tqe_next->entry.tqe_prev = c->entry.tqe_prev;
    }
    else
      (&clients)->tqh_last = c->entry.tqe_prev;
    *c->entry.tqe_prev = c->entry.tqe_next;
    ;
    ;
  }
  while (0);
  log_debug("lost client %p", c);
  if (c->flags & 0x1)
  {
    tty_free(&c->tty);
  }
  free(c->ttyname);
  free(c->term);
  evbuffer_free(c->stdin_data);
  evbuffer_free(c->stdout_data);
  if (c->stderr_data != c->stdout_data)
  {
    evbuffer_free(c->stderr_data);
  }
  if (event_initialized(&c->status.timer))
  {
    evtimer_del(&c->status.timer);
  }
  screen_free(&c->status.status);
  if (c->status.old_status != 0)
  {
    screen_free(c->status.old_status);
    free(c->status.old_status);
  }
  free(c->title);
  free((void *) c->cwd);
  evtimer_del(&c->repeat_timer);
  evtimer_del(&c->click_timer);
  key_bindings_unref_table(c->keytable);
  if (event_initialized(&c->identify_timer))
  {
    evtimer_del(&c->identify_timer);
  }
  free(c->message_string);
  if (event_initialized(&c->message_timer))
  {
    evtimer_del(&c->message_timer);
  }
  for (msg_idx = (&c->message_log)->tqh_first; ((&msg[msg_idx]) != 0) && ((msg1_idx = msg->entry.tqe_next, 1)); msg_idx = &msg1[msg1_idx])
  {
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

  free(c->prompt_string);
  free(c->prompt_buffer);
  format_lost_client(c);
  environ_free(c->environ);
  proc_remove_peer(c->peer);
  c->peer = 0;
  server_client_unref(c);
  server_add_accept(0);
  recalculate_sizes();
  server_check_unattached();
  server_update_socket();
}


/*** DEPENDENCIES:
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
void screen_free(struct screen *s)
{
  free(s->tabs);
  free(s->title);
  free(s->ccolour);
  grid_destroy(s->grid);
  screen_free_titles(s);
}


----------------------------
void key_bindings_unref_table(struct key_table *table)
{
  struct key_binding *bd;
  unsigned int bd_idx = 0;
  struct key_binding *bd1;
  unsigned int bd1_idx = 0;
  if ((--table->references) != 0)
  {
    return;
  }
  for (bd_idx = key_bindings_RB_MINMAX(&table->key_bindings, -1); ((&bd[bd_idx]) != 0) && ((bd1_idx = key_bindings_RB_NEXT(bd), 1)); bd_idx = &bd1[bd1_idx])
  {
    key_bindings_RB_REMOVE(&table->key_bindings, bd);
    cmd_list_free(bd->cmdlist);
    free(bd);
  }

  free((void *) table->name);
  free(table);
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
void server_check_unattached(void)
{
  struct session *s;
  unsigned int s_idx = 0;
  for (s_idx = sessions_RB_MINMAX(&sessions, -1); (&s[s_idx]) != 0; s_idx = sessions_RB_NEXT(s_idx))
  {
    if (!(s->flags & 0x1))
    {
      continue;
    }
    if (options_get_number(s->options, "destroy-unattached"))
    {
      session_destroy(s, __func__);
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
void status_prompt_clear(struct client *c)
{
  if (c->prompt_string == 0)
  {
    return;
  }
  if ((c->prompt_freecb != 0) && (c->prompt_data != 0))
  {
    c->prompt_freecb(c->prompt_data);
  }
  free(c->prompt_string);
  c->prompt_string = 0;
  free(c->prompt_buffer);
  c->prompt_buffer = 0;
  c->tty.flags &= ~(0x1 | 0x2);
  c->flags |= 0x8;
  screen_reinit(&c->status.status);
}


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
void tty_free(struct tty *tty)
{
  tty_close(tty);
  free(tty->ccolour);
  free(tty->term_name);
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
void format_lost_client(struct client *c)
{
  if (c->jobs != 0)
  {
    format_job_tidy(c->jobs, 1);
  }
  free(c->jobs);
}


----------------------------
void server_client_clear_identify(struct client *c, struct window_pane *wp)
{
  if ((~c->flags) & 0x100)
  {
    return;
  }
  c->flags &= ~0x100;
  if (c->identify_callback != 0)
  {
    c->identify_callback(c, wp);
  }
  c->tty.flags &= ~(0x2 | 0x1);
  server_redraw_client(c);
}


----------------------------
void proc_remove_peer(struct tmuxpeer *peer)
{
  log_debug("remove peer %p", peer);
  event_del(&peer->event);
  imsg_clear(&peer->ibuf);
  close(peer->ibuf.fd);
  free(peer);
}


----------------------------
None
----------------------------
***/


// element in merge of:  server_add_accept,server_client_lost,server_accept,server_client_dispatch,server_client_create
static void server_accept(int fd, short events, void *data)
{
  struct sockaddr_storage sa;
  socklen_t slen = sizeof(sa);
  int newfd;
  server_add_accept(0);
  if (!(events & EV_READ))
  {
    return;
  }
  newfd = accept(fd, (struct sockaddr *) (&sa), &slen);
  if (newfd == (-1))
  {
    if (((errno == EAGAIN) || (errno == EINTR)) || (errno == ECONNABORTED))
    {
      return;
    }
    if ((errno == ENFILE) || (errno == EMFILE))
    {
      server_add_accept(1);
      return;
    }
    fatal("accept failed");
  }
  if (server_exit)
  {
    close(newfd);
    return;
  }
  server_client_create(newfd);
}


/*** DEPENDENCIES:
static int server_exit
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
None
----------------------------
***/


// element in merge of:  server_add_accept,server_client_lost,server_accept,server_client_dispatch,server_client_create
static void server_client_dispatch(struct imsg *imsg, void *arg)
{
  struct client *c = arg;
  struct msg_stdin_data stdindata;
  const char *data;
  unsigned int data_idx = 0;
  ssize_t datalen;
  struct session *s;
  unsigned int s_idx = 0;
  if (c->flags & 0x200)
  {
    return;
  }
  if (imsg == 0)
  {
    server_client_lost(c);
    return;
  }
  data_idx = imsg->data_idx;
  datalen = imsg->hdr.len - (sizeof(struct imsg_hdr));
  switch (imsg->hdr.type)
  {
    case MSG_IDENTIFY_FLAGS:

    case MSG_IDENTIFY_TERM:

    case MSG_IDENTIFY_TTYNAME:

    case MSG_IDENTIFY_CWD:

    case MSG_IDENTIFY_STDIN:

    case MSG_IDENTIFY_ENVIRON:

    case MSG_IDENTIFY_CLIENTPID:

    case MSG_IDENTIFY_DONE:
    {
      server_client_dispatch_identify(c, imsg);
      break;
    }

    case MSG_COMMAND:
    {
      server_client_dispatch_command(c, imsg);
      break;
    }

    case MSG_STDIN:
    {
      if (datalen != (sizeof(stdindata)))
      {
        fatalx("bad MSG_STDIN size");
      }
      memcpy(&stdindata, data, sizeof(stdindata));
      if (c->stdin_callback == 0)
      {
        break;
      }
      if (stdindata.size <= 0)
      {
        c->stdin_closed = 1;
      }
      else
      {
        evbuffer_add(c->stdin_data, stdindata.data, stdindata.size);
      }
      c->stdin_callback(c, c->stdin_closed, c->stdin_callback_data);
      break;
    }

    case MSG_RESIZE:
    {
      if (datalen != 0)
      {
        fatalx("bad MSG_RESIZE size");
      }
      if (c->flags & 0x2000)
      {
        break;
      }
      tty_resize(&c->tty);
      recalculate_sizes();
      server_redraw_client(c);
      if (c->session != 0)
      {
        notify_client("client-resized", c);
      }
      break;
    }

    case MSG_EXITING:
    {
      if (datalen != 0)
      {
        fatalx("bad MSG_EXITING size");
      }
      c->session = 0;
      tty_close(&c->tty);
      proc_send(c->peer, MSG_EXITED, -1, 0, 0);
      break;
    }

    case MSG_WAKEUP:

    case MSG_UNLOCK:
    {
      helper_server_client_dispatch_1(&s_idx, c, datalen, s);
    }

    case MSG_SHELL:
    {
      if (datalen != 0)
      {
        fatalx("bad MSG_SHELL size");
      }
      server_client_dispatch_shell(c);
      break;
    }

  }

}


/*** DEPENDENCIES:
void helper_server_client_dispatch_1(unsigned int * const s_idx_ref, struct client * const c, ssize_t datalen, struct session * const s)
{
  unsigned int s_idx = *s_idx_ref;
  if (datalen != 0)
  {
    fatalx("bad MSG_WAKEUP size");
  }
  if (!(c->flags & 0x40))
  {
    break;
  }
  c->flags &= ~0x40;
  if (c->tty.fd == (-1))
  {
    break;
  }
  s_idx = c->session;
  if (gettimeofday(&c->activity_time, 0) != 0)
  {
    fatal("gettimeofday failed");
  }
  tty_start_tty(&c->tty);
  server_redraw_client(c);
  recalculate_sizes();
  if ((&s[s_idx]) != 0)
  {
    session_update_activity(s, &c->activity_time);
  }
  break;
  *s_idx_ref = s_idx;
}


----------------------------
void notify_client(const char *name, struct client *c)
{
  struct cmd_find_state fs;
  cmd_find_from_client(&fs, c, 0);
  notify_add(name, &fs, c, 0, 0, 0);
}


----------------------------
static void server_client_dispatch_identify(struct client *c, struct imsg *imsg)
{
  const char *data;
  unsigned int data_idx = 0;
  const char *home;
  unsigned int home_idx = 0;
  size_t datalen;
  int flags;
  char *name;
  unsigned int name_idx = 0;
  if (c->flags & 0x40000)
  {
    fatalx("out-of-order identify message");
  }
  data_idx = imsg->data_idx;
  datalen = imsg->hdr.len - (sizeof(struct imsg_hdr));
  switch (imsg->hdr.type)
  {
    case MSG_IDENTIFY_FLAGS:
    {
      if (datalen != (sizeof(flags)))
      {
        fatalx("bad MSG_IDENTIFY_FLAGS size");
      }
      memcpy(&flags, data, sizeof(flags));
      c->flags |= flags;
      log_debug("client %p IDENTIFY_FLAGS %#x", c, flags);
      break;
    }

    case MSG_IDENTIFY_TERM:
    {
      if ((datalen == 0) || (data[(datalen - 1) + data_idx] != '\0'))
      {
        fatalx("bad MSG_IDENTIFY_TERM string");
      }
      c->term = xstrdup(data);
      log_debug("client %p IDENTIFY_TERM %s", c, data);
      break;
    }

    case MSG_IDENTIFY_TTYNAME:
    {
      if ((datalen == 0) || (data[(datalen - 1) + data_idx] != '\0'))
      {
        fatalx("bad MSG_IDENTIFY_TTYNAME string");
      }
      c->ttyname = xstrdup(data);
      log_debug("client %p IDENTIFY_TTYNAME %s", c, data);
      break;
    }

    case MSG_IDENTIFY_CWD:
    {
      if ((datalen == 0) || (data[(datalen - 1) + data_idx] != '\0'))
      {
        fatalx("bad MSG_IDENTIFY_CWD string");
      }
      if (access(data, X_OK) == 0)
      {
        c->cwd = xstrdup(data);
      }
      else
        if ((home_idx = find_home()) != 0)
      {
        c->cwd = xstrdup(home);
      }
      else
        c->cwd = xstrdup("/");
      log_debug("client %p IDENTIFY_CWD %s", c, data);
      break;
    }

    case MSG_IDENTIFY_STDIN:
    {
      if (datalen != 0)
      {
        fatalx("bad MSG_IDENTIFY_STDIN size");
      }
      c->fd = imsg->fd;
      log_debug("client %p IDENTIFY_STDIN %d", c, imsg->fd);
      break;
    }

    case MSG_IDENTIFY_ENVIRON:
    {
      if ((datalen == 0) || (data[(datalen - 1) + data_idx] != '\0'))
      {
        fatalx("bad MSG_IDENTIFY_ENVIRON string");
      }
      if (strchr(data, '=') != 0)
      {
        environ_put(c->environ, data);
      }
      log_debug("client %p IDENTIFY_ENVIRON %s", c, data);
      break;
    }

    case MSG_IDENTIFY_CLIENTPID:
    {
      if (datalen != (sizeof(c->pid)))
      {
        fatalx("bad MSG_IDENTIFY_CLIENTPID size");
      }
      memcpy(&c->pid, data, sizeof(c->pid));
      log_debug("client %p IDENTIFY_CLIENTPID %ld", c, (long) c->pid);
      break;
    }

    default:
    {
      break;
    }

  }

  if (imsg->hdr.type != MSG_IDENTIFY_DONE)
  {
    return;
  }
  c->flags |= 0x40000;
  if ((*c->ttyname) != '\0')
  {
    name_idx = xstrdup(c->ttyname);
  }
  else
    xasprintf(&(&name[name_idx]), "client-%ld", (long) c->pid);
  c->name = &name[name_idx];
  log_debug("client %p name is %s", c, c->name);
  if (c->flags & 0x2000)
  {
    c->stdin_callback = control_callback;
    evbuffer_free(c->stderr_data);
    c->stderr_data = c->stdout_data;
    if (c->flags & 0x4000)
    {
      evbuffer_add_printf(c->stdout_data, "\033P1000p");
    }
    proc_send(c->peer, MSG_STDIN, -1, 0, 0);
    c->tty.fd = -1;
    close(c->fd);
    c->fd = -1;
    return;
  }
  if (c->fd == (-1))
  {
    return;
  }
  if (tty_init(&c->tty, c, c->fd, c->term) != 0)
  {
    close(c->fd);
    c->fd = -1;
    return;
  }
  if (c->flags & 0x10000)
  {
    c->tty.flags |= 0x8;
  }
  if (c->flags & 0x20000)
  {
    c->tty.term_flags |= 0x1;
  }
  tty_resize(&c->tty);
  if (!(c->flags & 0x2000))
  {
    c->flags |= 0x1;
  }
}


----------------------------
void tty_resize(struct tty *tty)
{
  struct client *c = tty->client;
  struct winsize ws;
  u_int sx;
  u_int sy;
  if (ioctl(tty->fd, TIOCGWINSZ, &ws) != (-1))
  {
    sx = ws.ws_col;
    if (sx == 0)
    {
      sx = 80;
    }
    sy = ws.ws_row;
    if (sy == 0)
    {
      sy = 24;
    }
  }
  else
  {
    sx = 80;
    sy = 24;
  }
  log_debug("%s: %s now %ux%u", __func__, c->name, sx, sy);
  tty_set_size(tty, sx, sy);
  tty_invalidate(tty);
}


----------------------------
struct msg_stdin_data
{
  ssize_t size;
  char data[1024];
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
void server_redraw_client(struct client *c)
{
  c->flags |= 0x8;
}


----------------------------
static void server_client_dispatch_command(struct client *c, struct imsg *imsg)
{
  struct msg_command_data data;
  char *buf;
  unsigned int buf_idx = 0;
  size_t len;
  struct cmd_list *cmdlist = 0;
  unsigned int cmdlist_idx = 0;
  int argc;
  char **argv;
  unsigned int argv_idx = 0;
  char *cause;
  unsigned int cause_idx = 0;
  if (c->flags & 0x4)
  {
    return;
  }
  if ((imsg->hdr.len - (sizeof(struct imsg_hdr))) < (sizeof(data)))
  {
    fatalx("bad MSG_COMMAND size");
  }
  memcpy(&data, imsg->data, sizeof(data));
  buf_idx = ((char *) imsg->data) + (sizeof(data));
  len = (imsg->hdr.len - (sizeof(struct imsg_hdr))) - (sizeof(data));
  if ((len > 0) && (buf[(len - 1) + buf_idx] != '\0'))
  {
    fatalx("bad MSG_COMMAND string");
  }
  argc = data.argc;
  if (cmd_unpack_argv(buf, len, argc, &(&argv[argv_idx])) != 0)
  {
    cause_idx = xstrdup("command too long");
    goto error;
  }
  if (argc == 0)
  {
    argc = 1;
    argv_idx = xcalloc(1, sizeof(*argv_idx));
    argv[argv_idx] = xstrdup("new-session");
  }
  if ((cmdlist_idx = cmd_list_parse(argc, argv, 0, 0, &(&cause[cause_idx]))) == 0)
  {
    cmd_free_argv(argc, argv);
    goto error;
  }
  cmd_free_argv(argc, argv);
  cmdq_append(c, cmdq_get_command(cmdlist, 0, 0, 0));
  cmdq_append(c, cmdq_get_callback1("server_client_command_done", server_client_command_done, 0));
  cmd_list_free(cmdlist);
  return;
  error:
  cmdq_append(c, cmdq_get_callback1("server_client_command_error", server_client_command_error, cause));

  if ((&cmdlist[cmdlist_idx]) != 0)
  {
    cmd_list_free(cmdlist);
  }
  c->flags |= 0x4;
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
struct imsg
{
  struct imsg_hdr hdr;
  int fd;
  void *data;
}
----------------------------
static void server_client_dispatch_shell(struct client *c)
{
  const char *shell;
  unsigned int shell_idx = 0;
  shell_idx = options_get_string(global_s_options, "default-shell");
  if ((shell[shell_idx] == '\0') || areshell(shell))
  {
    shell_idx = "/bin/sh";
  }
  proc_send(c->peer, MSG_SHELL, -1, shell, strlen(shell) + 1);
  proc_kill_peer(c->peer);
}


----------------------------
void tty_close(struct tty *tty)
{
  if (event_initialized(&tty->key_timer))
  {
    evtimer_del(&tty->key_timer);
  }
  tty_stop_tty(tty);
  if (tty->flags & 0x20)
  {
    evbuffer_free(tty->in);
    event_del(&tty->event_in);
    evbuffer_free(tty->out);
    event_del(&tty->event_out);
    tty_term_free(tty->term);
    tty_keys_free(tty);
    tty->flags &= ~0x20;
  }
  if (tty->fd != (-1))
  {
    close(tty->fd);
    tty->fd = -1;
  }
}


----------------------------
None
----------------------------
None
----------------------------
None
----------------------------
***/


// element in merge of:  server_add_accept,server_client_lost,server_accept,server_client_dispatch,server_client_create
struct client *server_client_create(int fd)
{
  struct client *c;
  unsigned int c_idx = 0;
  setblocking(fd, 0);
  c_idx = xcalloc(1, sizeof(*c_idx));
  c->references = 1;
  c->peer = proc_add_peer(server_proc, fd, server_client_dispatch, c);
  if (gettimeofday(&c->creation_time, 0) != 0)
  {
    fatal("gettimeofday failed");
  }
  memcpy(&c->activity_time, &c->creation_time, sizeof(c->activity_time));
  c->environ = environ_create();
  c->fd = -1;
  c->cwd = 0;
  do
  {
    (&c->queue)->tqh_first = 0;
    (&c->queue)->tqh_last = &(&c->queue)->tqh_first;
  }
  while (0);
  c->stdin_data = evbuffer_new();
  c->stdout_data = evbuffer_new();
  c->stderr_data = evbuffer_new();
  c->tty.fd = -1;
  c->title = 0;
  c->session = 0;
  c->last_session = 0;
  c->tty.sx = 80;
  c->tty.sy = 24;
  screen_init(&c->status.status, c->tty.sx, 1, 0);
  c->message_string = 0;
  do
  {
    (&c->message_log)->tqh_first = 0;
    (&c->message_log)->tqh_last = &(&c->message_log)->tqh_first;
  }
  while (0);
  c->prompt_string = 0;
  c->prompt_buffer = 0;
  c->prompt_index = 0;
  c->flags |= 0x8000;
  c->keytable = key_bindings_get_table("root", 1);
  c->keytable->references += 1;
  evtimer_set(&c->repeat_timer, server_client_repeat_timer, c);
  evtimer_set(&c->click_timer, server_client_click_timer, c);
  do
  {
    c->entry.tqe_next = 0;
    c->entry.tqe_prev = (&clients)->tqh_last;
    *(&clients)->tqh_last = &c[c_idx];
    (&clients)->tqh_last = &c->entry.tqe_next;
  }
  while (0);
  log_debug("new client %p", c);
  return c;
}


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
}
----------------------------
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
static void server_client_click_timer(int fd, short events, void *data)
{
  struct client *c = data;
  c->flags &= ~(0x100000 | 0x200000);
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
struct key_table *key_bindings_get_table(const char *name, int create)
{
  struct key_table table_find;
  struct key_table *table;
  unsigned int table_idx = 0;
  table_find.name = name;
  table_idx = key_tables_RB_FIND(&key_tables, &table_find);
  if (((&table[table_idx]) != 0) || (!create))
  {
    return table;
  }
  table_idx = xmalloc(sizeof(*table_idx));
  table->name = xstrdup(name);
  do
  {
    (&table->key_bindings)->rbh_root = 0;
  }
  while (0);
  table->references = 1;
  key_tables_RB_INSERT(&key_tables, table);
  return table;
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
struct tmuxpeer *proc_add_peer(struct tmuxproc *tp, int fd, void (*dispatchcb)(struct imsg *, void *), void *arg)
{
  struct tmuxpeer *peer;
  unsigned int peer_idx = 0;
  peer_idx = xcalloc(1, sizeof(*peer_idx));
  peer->parent = tp;
  peer->dispatchcb = dispatchcb;
  peer->arg = arg;
  imsg_init(&peer->ibuf, fd);
  event_set(&peer->event, fd, EV_READ, proc_event_cb, peer);
  log_debug("add peer %p: %d (%p)", peer, fd, arg);
  proc_update_event(peer);
  return peer;
}


----------------------------
static void server_client_repeat_timer(int fd, short events, void *data)
{
  struct client *c = data;
  if (c->flags & 0x20)
  {
    server_client_set_key_table(c, 0);
    c->flags &= ~0x20;
    server_status_client(c);
  }
}


----------------------------
None
----------------------------
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


