// hint:  ['sepstr_idx_ref is a mutable refrence to unsigned int', 'bufdata_idx_ref is a mutable refrence to unsigned int', 'bufend_idx_ref is a mutable refrence to unsigned int', 'line_idx_ref is a mutable refrence to unsigned int', 'seplen_ref is a mutable refrence to size_t']
void helper_cmd_paste_buffer_exec_1(unsigned int * const sepstr_idx_ref, unsigned int * const bufdata_idx_ref, unsigned int * const bufend_idx_ref, unsigned int * const line_idx_ref, size_t * const seplen_ref, struct args * const args, struct window_pane * const wp, struct paste_buffer * const pb, const char * const sepstr, const char * const bufdata, const char * const bufend, const char * const line, size_t bufsize, int bracket)
{
  unsigned int sepstr_idx = *sepstr_idx_ref;
  unsigned int bufdata_idx = *bufdata_idx_ref;
  unsigned int bufend_idx = *bufend_idx_ref;
  unsigned int line_idx = *line_idx_ref;
  size_t seplen = *seplen_ref;
  sepstr_idx = args_get(args, 's');
  if ((&sepstr[sepstr_idx]) == 0)
  {
    if (args_has(args, 'r'))
    {
      sepstr_idx = "\n";
    }
    else
      sepstr_idx = "\r";
  }
  seplen = strlen(sepstr);
  if (bracket && (wp->screen->mode & 0x400))
  {
    bufferevent_write(wp->event, "\033[200~", 6);
  }
  bufdata_idx = paste_buffer_data(pb, &bufsize);
  bufend_idx = (&bufdata[bufdata_idx]) + bufsize;
  for (;;)
  {
    line_idx = memchr(bufdata, '\n', (&bufend[bufend_idx]) - (&bufdata[bufdata_idx]));
    if ((&line[line_idx]) == 0)
    {
      break;
    }
    bufferevent_write(wp->event, bufdata, (&line[line_idx]) - (&bufdata[bufdata_idx]));
    bufferevent_write(wp->event, sepstr, seplen);
    bufdata_idx = (&line[line_idx]) + 1;
  }

  if ((&bufdata[bufdata_idx]) != (&bufend[bufend_idx]))
  {
    bufferevent_write(wp->event, bufdata, (&bufend[bufend_idx]) - (&bufdata[bufdata_idx]));
  }
  if (bracket && (wp->screen->mode & 0x400))
  {
    bufferevent_write(wp->event, "\033[201~", 6);
  }
  *sepstr_idx_ref = sepstr_idx;
  *bufdata_idx_ref = bufdata_idx;
  *bufend_idx_ref = bufend_idx;
  *line_idx_ref = line_idx;
  *seplen_ref = seplen;
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
struct paste_buffer
{
  char *data;
  size_t size;
  char *name;
  time_t created;
  int automatic;
  u_int order;
  struct 
  {
    struct paste_buffer *rbe_left;
    struct paste_buffer *rbe_right;
    struct paste_buffer *rbe_parent;
    int rbe_color;
  } name_entry;
  struct 
  {
    struct paste_buffer *rbe_left;
    struct paste_buffer *rbe_right;
    struct paste_buffer *rbe_parent;
    int rbe_color;
  } time_entry;
}
----------------------------
const char *paste_buffer_data(struct paste_buffer *pb, size_t *size)
{
  if (size != 0)
  {
    *size = pb->size;
  }
  return pb->data;
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


static enum cmd_retval cmd_paste_buffer_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct window_pane *wp = item->target.wp;
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  const char *sepstr;
  unsigned int sepstr_idx = 0;
  const char *bufname;
  unsigned int bufname_idx = 0;
  const char *bufdata;
  unsigned int bufdata_idx = 0;
  const char *bufend;
  unsigned int bufend_idx = 0;
  const char *line;
  unsigned int line_idx = 0;
  size_t seplen;
  size_t bufsize;
  int bracket = args_has(args, 'p');
  bufname_idx = 0;
  if (args_has(args, 'b'))
  {
    bufname_idx = args_get(args, 'b');
  }
  if ((&bufname[bufname_idx]) == 0)
  {
    pb_idx = paste_get_top(0);
  }
  else
  {
    pb_idx = paste_get_name(bufname);
    if ((&pb[pb_idx]) == 0)
    {
      cmdq_error(item, "no buffer %s", bufname);
      return CMD_RETURN_ERROR;
    }
  }
  if (((&pb[pb_idx]) != 0) && ((~wp->flags) & 0x40))
  {
    helper_cmd_paste_buffer_exec_1(&sepstr_idx, &bufdata_idx, &bufend_idx, &line_idx, &seplen, args, wp, pb, sepstr, bufdata, bufend, line, bufsize, bracket);
  }
  if (((&pb[pb_idx]) != 0) && args_has(args, 'd'))
  {
    paste_free(pb);
  }
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
struct paste_buffer *paste_get_top(const char **name)
{
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  pb_idx = paste_time_tree_RB_MINMAX(&paste_by_time, -1);
  if ((&pb[pb_idx]) == 0)
  {
    return 0;
  }
  if (name != 0)
  {
    *name = pb->name;
  }
  return pb;
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
void helper_cmd_paste_buffer_exec_1(unsigned int * const sepstr_idx_ref, unsigned int * const bufdata_idx_ref, unsigned int * const bufend_idx_ref, unsigned int * const line_idx_ref, size_t * const seplen_ref, struct args * const args, struct window_pane * const wp, struct paste_buffer * const pb, const char * const sepstr, const char * const bufdata, const char * const bufend, const char * const line, size_t bufsize, int bracket)
{
  unsigned int sepstr_idx = *sepstr_idx_ref;
  unsigned int bufdata_idx = *bufdata_idx_ref;
  unsigned int bufend_idx = *bufend_idx_ref;
  unsigned int line_idx = *line_idx_ref;
  size_t seplen = *seplen_ref;
  sepstr_idx = args_get(args, 's');
  if ((&sepstr[sepstr_idx]) == 0)
  {
    if (args_has(args, 'r'))
    {
      sepstr_idx = "\n";
    }
    else
      sepstr_idx = "\r";
  }
  seplen = strlen(sepstr);
  if (bracket && (wp->screen->mode & 0x400))
  {
    bufferevent_write(wp->event, "\033[200~", 6);
  }
  bufdata_idx = paste_buffer_data(pb, &bufsize);
  bufend_idx = (&bufdata[bufdata_idx]) + bufsize;
  for (;;)
  {
    line_idx = memchr(bufdata, '\n', (&bufend[bufend_idx]) - (&bufdata[bufdata_idx]));
    if ((&line[line_idx]) == 0)
    {
      break;
    }
    bufferevent_write(wp->event, bufdata, (&line[line_idx]) - (&bufdata[bufdata_idx]));
    bufferevent_write(wp->event, sepstr, seplen);
    bufdata_idx = (&line[line_idx]) + 1;
  }

  if ((&bufdata[bufdata_idx]) != (&bufend[bufend_idx]))
  {
    bufferevent_write(wp->event, bufdata, (&bufend[bufend_idx]) - (&bufdata[bufdata_idx]));
  }
  if (bracket && (wp->screen->mode & 0x400))
  {
    bufferevent_write(wp->event, "\033[201~", 6);
  }
  *sepstr_idx_ref = sepstr_idx;
  *bufdata_idx_ref = bufdata_idx;
  *bufend_idx_ref = bufend_idx;
  *line_idx_ref = line_idx;
  *seplen_ref = seplen;
}


----------------------------
struct paste_buffer *paste_get_name(const char *name)
{
  struct paste_buffer pbfind;
  if ((name == 0) || ((*name) == '\0'))
  {
    return 0;
  }
  pbfind.name = (char *) name;
  return paste_name_tree_RB_FIND(&paste_by_name, &pbfind);
}


----------------------------
struct paste_buffer
{
  char *data;
  size_t size;
  char *name;
  time_t created;
  int automatic;
  u_int order;
  struct 
  {
    struct paste_buffer *rbe_left;
    struct paste_buffer *rbe_right;
    struct paste_buffer *rbe_parent;
    int rbe_color;
  } name_entry;
  struct 
  {
    struct paste_buffer *rbe_left;
    struct paste_buffer *rbe_right;
    struct paste_buffer *rbe_parent;
    int rbe_color;
  } time_entry;
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
void paste_free(struct paste_buffer *pb)
{
  paste_name_tree_RB_REMOVE(&paste_by_name, pb);
  paste_time_tree_RB_REMOVE(&paste_by_time, pb);
  if (pb->automatic)
  {
    paste_num_automatic -= 1;
  }
  free(pb->data);
  free(pb->name);
  free(pb);
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
int args_has(struct args *args, u_char ch)
{
  return args_find(args, ch) != 0;
}


----------------------------
None
----------------------------
***/


