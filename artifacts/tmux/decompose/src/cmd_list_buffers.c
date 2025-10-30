static enum cmd_retval cmd_list_buffers_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  char *line;
  unsigned int line_idx = 0;
  const char *template;
  unsigned int template_idx = 0;
  if ((template_idx = args_get(args, 'F')) == 0)
  {
    template_idx = "#{buffer_name}: #{buffer_size} bytes: \"#{buffer_sample}\"";
  }
  pb_idx = 0;
  while ((pb_idx = paste_walk(pb_idx)) != 0)
  {
    ft_idx = format_create(item->client, item, 0, 0);
    format_defaults_paste_buffer(ft, pb);
    line_idx = format_expand(ft, template);
    cmdq_print(item, "%s", line);
    free(line);
    format_free(ft);
  }

  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
struct paste_buffer *paste_walk(struct paste_buffer *pb)
{
  if (pb == 0)
  {
    return paste_time_tree_RB_MINMAX(&paste_by_time, -1);
  }
  return paste_time_tree_RB_NEXT(pb);
}


----------------------------
void format_free(struct format_tree *ft)
{
  struct format_entry *fe;
  unsigned int fe_idx = 0;
  struct format_entry *fe1;
  unsigned int fe1_idx = 0;
  for (fe_idx = format_entry_tree_RB_MINMAX(&ft->tree, -1); ((&fe[fe_idx]) != 0) && ((fe1_idx = format_entry_tree_RB_NEXT(fe), 1)); fe_idx = &fe1[fe1_idx])
  {
    format_entry_tree_RB_REMOVE(&ft->tree, fe);
    free(fe->value);
    free(fe->key);
    free(fe);
  }

  if (ft->client != 0)
  {
    server_client_unref(ft->client);
  }
  free(ft);
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
struct format_tree *format_create(struct client *c, struct cmdq_item *item, int tag, int flags)
{
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  if (!event_initialized(&format_job_event))
  {
    evtimer_set(&format_job_event, format_job_timer, 0);
    format_job_timer(-1, 0, 0);
  }
  ft_idx = xcalloc(1, sizeof(*ft_idx));
  do
  {
    (&ft->tree)->rbh_root = 0;
  }
  while (0);
  if (c != 0)
  {
    ft->client = c;
    ft->client->references += 1;
  }
  ft->tag = tag;
  ft->flags = flags;
  format_add(ft, "version", "%s", VERSION);
  format_add_cb(ft, "host", format_cb_host);
  format_add_cb(ft, "host_short", format_cb_host_short);
  format_add_cb(ft, "pid", format_cb_pid);
  format_add(ft, "socket_path", "%s", socket_path);
  format_add_tv(ft, "start_time", &start_time);
  if (item != 0)
  {
    if (item->cmd != 0)
    {
      format_add(ft, "command", "%s", item->cmd->entry->name);
    }
    if ((item->shared != 0) && (item->shared->formats != 0))
    {
      format_merge(ft, item->shared->formats);
    }
  }
  return ft;
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
None
----------------------------
enum cmd_retval
{
  CMD_RETURN_ERROR = -1,
  CMD_RETURN_NORMAL = 0,
  CMD_RETURN_WAIT,
  CMD_RETURN_STOP
}
----------------------------
void format_defaults_paste_buffer(struct format_tree *ft, struct paste_buffer *pb)
{
  struct timeval tv;
  size_t size;
  char *s;
  unsigned int s_idx = 0;
  timerclear(&tv);
  tv.tv_sec = paste_buffer_created(pb);
  paste_buffer_data(pb, &size);
  format_add(ft, "buffer_size", "%zu", size);
  format_add(ft, "buffer_name", "%s", paste_buffer_name(pb));
  format_add_tv(ft, "buffer_created", &tv);
  s_idx = paste_make_sample(pb);
  format_add(ft, "buffer_sample", "%s", s);
  free(s);
}


----------------------------
None
----------------------------
None
----------------------------
***/


