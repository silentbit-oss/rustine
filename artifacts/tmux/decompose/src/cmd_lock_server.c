static enum cmd_retval cmd_lock_server_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct client *c;
  unsigned int c_idx = 0;
  if (self->entry == (&cmd_lock_server_entry))
  {
    server_lock();
  }
  else
    if (self->entry == (&cmd_lock_session_entry))
  {
    server_lock_session(item->target.s);
  }
  else
  {
    if ((c_idx = cmd_find_client(item, args_get(args, 't'), 0)) == 0)
    {
      return CMD_RETURN_ERROR;
    }
    server_lock_client(c);
  }
  recalculate_sizes();
  return CMD_RETURN_NORMAL;
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
void server_lock_client(struct client *c)
{
  const char *cmd;
  unsigned int cmd_idx = 0;
  if (c->flags & 0x2000)
  {
    return;
  }
  if (c->flags & 0x40)
  {
    return;
  }
  cmd_idx = options_get_string(c->session->options, "lock-command");
  if ((cmd[cmd_idx] == '\0') || ((strlen(cmd) + 1) > (16384 - (sizeof(struct imsg_hdr)))))
  {
    return;
  }
  tty_stop_tty(&c->tty);
  tty_raw(&c->tty, tty_term_string(c->tty.term, TTYC_SMCUP));
  tty_raw(&c->tty, tty_term_string(c->tty.term, TTYC_CLEAR));
  tty_raw(&c->tty, tty_term_string(c->tty.term, TTYC_E3));
  c->flags |= 0x40;
  proc_send(c->peer, MSG_LOCK, -1, cmd, strlen(cmd) + 1);
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
extern const struct cmd_entry cmd_lock_server_entry
----------------------------
extern const struct cmd_entry cmd_lock_session_entry
----------------------------
void server_lock(void)
{
  struct client *c;
  unsigned int c_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (c->session != 0)
    {
      server_lock_client(c);
    }
  }

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
None
----------------------------
***/


