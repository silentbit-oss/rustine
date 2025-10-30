static enum cmd_retval cmd_set_buffer_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  char *bufdata;
  unsigned int bufdata_idx = 0;
  char *cause;
  const char *bufname;
  unsigned int bufname_idx = 0;
  const char *olddata;
  unsigned int olddata_idx = 0;
  size_t bufsize;
  size_t newsize;
  bufname_idx = args_get(args, 'b');
  if ((&bufname[bufname_idx]) == 0)
  {
    pb_idx = 0;
  }
  else
    pb_idx = paste_get_name(bufname);
  if (self->entry == (&cmd_delete_buffer_entry))
  {
    if ((&pb[pb_idx]) == 0)
    {
      pb_idx = paste_get_top(&(&bufname[bufname_idx]));
    }
    if ((&pb[pb_idx]) == 0)
    {
      cmdq_error(item, "no buffer");
      return CMD_RETURN_ERROR;
    }
    paste_free(pb);
    return CMD_RETURN_NORMAL;
  }
  if (args_has(args, 'n'))
  {
    if ((&pb[pb_idx]) == 0)
    {
      pb_idx = paste_get_top(&(&bufname[bufname_idx]));
    }
    if ((&pb[pb_idx]) == 0)
    {
      cmdq_error(item, "no buffer");
      return CMD_RETURN_ERROR;
    }
    if (paste_rename(bufname, args_get(args, 'n'), &cause) != 0)
    {
      cmdq_error(item, "%s", cause);
      free(cause);
      return CMD_RETURN_ERROR;
    }
    return CMD_RETURN_NORMAL;
  }
  if (args->argc != 1)
  {
    cmdq_error(item, "no data specified");
    return CMD_RETURN_ERROR;
  }
  if ((newsize = strlen(args->argv[0])) == 0)
  {
    return CMD_RETURN_NORMAL;
  }
  bufsize = 0;
  bufdata_idx = 0;
  if (args_has(args, 'a') && ((&pb[pb_idx]) != 0))
  {
    olddata_idx = paste_buffer_data(pb, &bufsize);
    bufdata_idx = xmalloc(bufsize);
    memcpy(bufdata, olddata, bufsize);
  }
  bufdata_idx = xrealloc(bufdata_idx, bufsize + newsize);
  memcpy((&bufdata[bufdata_idx]) + bufsize, args->argv[0], newsize);
  bufsize += newsize;
  if (paste_set(bufdata, bufsize, bufname, &cause) != 0)
  {
    cmdq_error(item, "%s", cause);
    free(bufdata);
    free(cause);
    return CMD_RETURN_ERROR;
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
int paste_set(char *data, size_t size, const char *name, char **cause)
{
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  struct paste_buffer *old;
  unsigned int old_idx = 0;
  if (cause != 0)
  {
    *cause = 0;
  }
  if (size == 0)
  {
    free(data);
    return 0;
  }
  if (name == 0)
  {
    paste_add(data, size);
    return 0;
  }
  if ((*name) == '\0')
  {
    if (cause != 0)
    {
      *cause = xstrdup("empty buffer name");
    }
    return -1;
  }
  pb_idx = xmalloc(sizeof(*pb_idx));
  pb->name = xstrdup(name);
  pb->data = data;
  pb->size = size;
  pb->automatic = 0;
  pb->order = paste_next_order;
  paste_next_order += 1;
  pb->created = time(0);
  if ((old_idx = paste_get_name(name)) != 0)
  {
    paste_free(old);
  }
  paste_name_tree_RB_INSERT(&paste_by_name, pb);
  paste_time_tree_RB_INSERT(&paste_by_time, pb);
  return 0;
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
extern const struct cmd_entry cmd_delete_buffer_entry
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
void *xrealloc(void *ptr, size_t size)
{
  return xreallocarray(ptr, 1, size);
}


----------------------------
int paste_rename(const char *oldname, const char *newname, char **cause)
{
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  struct paste_buffer *pb_new;
  unsigned int pb_new_idx = 0;
  if (cause != 0)
  {
    *cause = 0;
  }
  if ((oldname == 0) || ((*oldname) == '\0'))
  {
    if (cause != 0)
    {
      *cause = xstrdup("no buffer");
    }
    return -1;
  }
  if ((newname == 0) || ((*newname) == '\0'))
  {
    if (cause != 0)
    {
      *cause = xstrdup("new name is empty");
    }
    return -1;
  }
  pb_idx = paste_get_name(oldname);
  if ((&pb[pb_idx]) == 0)
  {
    if (cause != 0)
    {
      xasprintf(cause, "no buffer %s", oldname);
    }
    return -1;
  }
  pb_new_idx = paste_get_name(newname);
  if ((&pb_new[pb_new_idx]) != 0)
  {
    if (cause != 0)
    {
      xasprintf(cause, "buffer %s already exists", newname);
    }
    return -1;
  }
  paste_name_tree_RB_REMOVE(&paste_by_name, pb);
  free(pb->name);
  pb->name = xstrdup(newname);
  if (pb->automatic)
  {
    paste_num_automatic -= 1;
  }
  pb->automatic = 0;
  paste_name_tree_RB_INSERT(&paste_by_name, pb);
  return 0;
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
int args_has(struct args *args, u_char ch)
{
  return args_find(args, ch) != 0;
}


----------------------------
None
----------------------------
***/


