static enum cmd_retval cmd_save_buffer_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct client *c = item->client;
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  const char *path;
  unsigned int path_idx = 0;
  const char *bufname;
  unsigned int bufname_idx = 0;
  const char *bufdata;
  unsigned int bufdata_idx = 0;
  const char *start;
  unsigned int start_idx = 0;
  const char *end;
  unsigned int end_idx = 0;
  const char *flags;
  unsigned int flags_idx = 0;
  char *msg;
  unsigned int msg_idx = 0;
  char *file;
  unsigned int file_idx = 0;
  size_t size;
  size_t used;
  size_t msglen;
  size_t bufsize;
  FILE *f;
  unsigned int f_idx = 0;
  if (!args_has(args, 'b'))
  {
    if ((pb_idx = paste_get_top(0)) == 0)
    {
      cmdq_error(item, "no buffers");
      return CMD_RETURN_ERROR;
    }
  }
  else
  {
    bufname_idx = args_get(args, 'b');
    pb_idx = paste_get_name(bufname);
    if ((&pb[pb_idx]) == 0)
    {
      cmdq_error(item, "no buffer %s", bufname);
      return CMD_RETURN_ERROR;
    }
  }
  bufdata_idx = paste_buffer_data(pb, &bufsize);
  if (self->entry == (&cmd_show_buffer_entry))
  {
    path_idx = "-";
  }
  else
    path_idx = args->argv[0];
  if (strcmp(path, "-") == 0)
  {
    if (c == 0)
    {
      cmdq_error(item, "can't write to stdout");
      return CMD_RETURN_ERROR;
    }
    if ((c->session == 0) || (c->flags & 0x2000))
    {
      goto do_stdout;
    }
    goto do_print;
  }
  flags_idx = "wb";
  if (args_has(self->args, 'a'))
  {
    flags_idx = "ab";
  }
  file_idx = server_client_get_path(c, path);
  f_idx = fopen(file, flags);
  if ((&f[f_idx]) == 0)
  {
    cmdq_error(item, "%s: %s", file, strerror(errno));
    free(file);
    return CMD_RETURN_ERROR;
  }
  if (fwrite(bufdata, 1, bufsize, f) != bufsize)
  {
    cmdq_error(item, "%s: write error", file);
    fclose(f);
    free(file);
    return CMD_RETURN_ERROR;
  }
  fclose(f);
  free(file);
  return CMD_RETURN_NORMAL;
  do_stdout:
  evbuffer_add(c->stdout_data, bufdata, bufsize);

  server_client_push_stdout(c);
  return CMD_RETURN_NORMAL;
  do_print:
  if (bufsize > ((2147483647 / 4) - 1))
  {
    cmdq_error(item, "buffer too big");
    return CMD_RETURN_ERROR;
  }

  msg_idx = 0;
  used = 0;
  while (used != bufsize)
  {
    start_idx = (&bufdata[bufdata_idx]) + used;
    end_idx = memchr(start, '\n', bufsize - used);
    if ((&end[end_idx]) != 0)
    {
      size = (&end[end_idx]) - (&start[start_idx]);
    }
    else
      size = bufsize - used;
    msglen = (size * 4) + 1;
    msg_idx = xrealloc(msg_idx, msglen);
    strvisx(msg, start, size, 0x01 | 0x08);
    cmdq_print(item, "%s", msg);
    used += size + ((&end[end_idx]) != 0);
  }

  free(msg);
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
extern const struct cmd_entry cmd_show_buffer_entry
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
int strvisx(char *dst, const char *src, size_t len, int flag)
{
  unsigned int src_idx = 0;
  unsigned int dst_idx = 0;
  char c;
  char *start;
  unsigned int start_idx = 0;
  for (start_idx = &dst[dst_idx]; len > 1; len -= 1)
  {
    c = src[src_idx];
    src_idx += 1;
    dst_idx = vis(dst_idx, c, flag, *(&src[src_idx]));
  }

  if (len)
  {
    dst_idx = vis(dst_idx, *(&src[src_idx]), flag, '\0');
  }
  dst[dst_idx] = '\0';
  return (&dst[dst_idx]) - (&start[start_idx]);
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
None
----------------------------
int args_has(struct args *args, u_char ch)
{
  return args_find(args, ch) != 0;
}


----------------------------
void *xrealloc(void *ptr, size_t size)
{
  return xreallocarray(ptr, 1, size);
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
char *server_client_get_path(struct client *c, const char *file)
{
  char *path;
  unsigned int path_idx = 0;
  char resolved[PATH_MAX];
  if ((*file) == '/')
  {
    path_idx = xstrdup(file);
  }
  else
    xasprintf(&(&path[path_idx]), "%s/%s", server_client_get_cwd(c), file);
  if (realpath(path, resolved) == 0)
  {
    return path;
  }
  free(path);
  return xstrdup(resolved);
}


----------------------------
None
----------------------------
***/


