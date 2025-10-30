static void cmd_load_buffer_callback(struct client *c, int closed, void *data)
{
  struct cmd_load_buffer_data *cdata = data;
  char *pdata;
  unsigned int pdata_idx = 0;
  char *cause;
  unsigned int cause_idx = 0;
  char *saved;
  unsigned int saved_idx = 0;
  size_t psize;
  if (!closed)
  {
    return;
  }
  c->stdin_callback = 0;
  server_client_unref(c);
  if (c->flags & 0x200)
  {
    goto out;
  }
  psize = EVBUFFER_LENGTH(c->stdin_data);
  if ((psize == 0) || ((pdata_idx = malloc(psize + 1)) == 0))
  {
    goto out;
  }
  memcpy(pdata, EVBUFFER_DATA(c->stdin_data), psize);
  pdata[psize + pdata_idx] = '\0';
  evbuffer_drain(c->stdin_data, psize);
  if (paste_set(pdata, psize, cdata->bufname, &(&cause[cause_idx])) != 0)
  {
    if ((~c->flags) & 0x10000)
    {
      saved_idx = &cause[cause_idx];
      cause_idx = utf8_sanitize(saved);
      free(saved);
    }
    evbuffer_add_printf(c->stderr_data, "%s", cause);
    server_client_push_stderr(c);
    free(pdata);
    free(cause);
  }
  out:
  cdata->item->flags &= ~0x2;

  free(cdata->bufname);
  free(cdata);
}


/*** DEPENDENCIES:
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
None
----------------------------
struct cmd_load_buffer_data
{
  struct cmdq_item *item;
  char *bufname;
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


static enum cmd_retval cmd_load_buffer_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct cmd_load_buffer_data *cdata;
  unsigned int cdata_idx = 0;
  struct client *c = item->client;
  FILE *f;
  unsigned int f_idx = 0;
  const char *path;
  unsigned int path_idx = 0;
  const char *bufname;
  unsigned int bufname_idx = 0;
  char *pdata = 0;
  unsigned int pdata_idx = 0;
  char *new_pdata;
  unsigned int new_pdata_idx = 0;
  char *cause;
  char *file;
  unsigned int file_idx = 0;
  size_t psize;
  int ch;
  int error;
  bufname_idx = 0;
  if (args_has(args, 'b'))
  {
    bufname_idx = args_get(args, 'b');
  }
  path_idx = args->argv[0];
  if (strcmp(path, "-") == 0)
  {
    cdata_idx = xcalloc(1, sizeof(*cdata_idx));
    cdata->item = item;
    if ((&bufname[bufname_idx]) != 0)
    {
      cdata->bufname = xstrdup(bufname);
    }
    error = server_set_stdin_callback(c, cmd_load_buffer_callback, cdata, &cause);
    if (error != 0)
    {
      cmdq_error(item, "%s: %s", path, cause);
      free(cause);
      return CMD_RETURN_ERROR;
    }
    return CMD_RETURN_WAIT;
  }
  file_idx = server_client_get_path(c, path);
  f_idx = fopen(file, "rb");
  if ((&f[f_idx]) == 0)
  {
    cmdq_error(item, "%s: %s", file, strerror(errno));
    goto error;
  }
  pdata_idx = 0;
  psize = 0;
  while ((ch = getc(f)) != EOF)
  {
    if ((new_pdata_idx = realloc(pdata, psize + 2)) == 0)
    {
      cmdq_error(item, "realloc error: %s", strerror(errno));
      goto error;
    }
    pdata_idx = &new_pdata[new_pdata_idx];
    pdata[psize + pdata_idx] = ch;
    psize += 1;
  }

  if (ferror(f))
  {
    cmdq_error(item, "%s: read error", file);
    goto error;
  }
  if ((&pdata[pdata_idx]) != 0)
  {
    pdata[psize + pdata_idx] = '\0';
  }
  fclose(f);
  free(file);
  if (paste_set(pdata, psize, bufname, &cause) != 0)
  {
    cmdq_error(item, "%s", cause);
    free(pdata);
    free(cause);
    return CMD_RETURN_ERROR;
  }
  return CMD_RETURN_NORMAL;
  error:
  free(pdata);

  if ((&f[f_idx]) != 0)
  {
    fclose(f);
  }
  free(file);
  return CMD_RETURN_ERROR;
}


/*** DEPENDENCIES:
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
static void cmd_load_buffer_callback(struct client *c, int closed, void *data)
{
  struct cmd_load_buffer_data *cdata = data;
  char *pdata;
  unsigned int pdata_idx = 0;
  char *cause;
  unsigned int cause_idx = 0;
  char *saved;
  unsigned int saved_idx = 0;
  size_t psize;
  if (!closed)
  {
    return;
  }
  c->stdin_callback = 0;
  server_client_unref(c);
  if (c->flags & 0x200)
  {
    goto out;
  }
  psize = EVBUFFER_LENGTH(c->stdin_data);
  if ((psize == 0) || ((pdata_idx = malloc(psize + 1)) == 0))
  {
    goto out;
  }
  memcpy(pdata, EVBUFFER_DATA(c->stdin_data), psize);
  pdata[psize + pdata_idx] = '\0';
  evbuffer_drain(c->stdin_data, psize);
  if (paste_set(pdata, psize, cdata->bufname, &(&cause[cause_idx])) != 0)
  {
    if ((~c->flags) & 0x10000)
    {
      saved_idx = &cause[cause_idx];
      cause_idx = utf8_sanitize(saved);
      free(saved);
    }
    evbuffer_add_printf(c->stderr_data, "%s", cause);
    server_client_push_stderr(c);
    free(pdata);
    free(cause);
  }
  out:
  cdata->item->flags &= ~0x2;

  free(cdata->bufname);
  free(cdata);
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
int server_set_stdin_callback(struct client *c, void (*cb)(struct client *, int, void *), void *cb_data, char **cause)
{
  if ((c == 0) || (c->session != 0))
  {
    *cause = xstrdup("no client with stdin");
    return -1;
  }
  if (c->flags & 0x1)
  {
    *cause = xstrdup("stdin is a tty");
    return -1;
  }
  if (c->stdin_callback != 0)
  {
    *cause = xstrdup("stdin in use");
    return -1;
  }
  c->stdin_callback_data = cb_data;
  c->stdin_callback = cb;
  c->references += 1;
  if (c->stdin_closed)
  {
    c->stdin_callback(c, 1, c->stdin_callback_data);
  }
  proc_send(c->peer, MSG_STDIN, -1, 0, 0);
  return 0;
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
struct cmd_load_buffer_data
{
  struct cmdq_item *item;
  char *bufname;
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


