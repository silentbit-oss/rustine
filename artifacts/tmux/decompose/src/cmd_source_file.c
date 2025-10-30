static enum cmd_retval cmd_source_file_done(struct cmdq_item *item, void *data)
{
  cfg_print_causes(item);
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
enum cmd_retval
{
  CMD_RETURN_ERROR = -1,
  CMD_RETURN_NORMAL = 0,
  CMD_RETURN_WAIT,
  CMD_RETURN_STOP
}
----------------------------
void cfg_print_causes(struct cmdq_item *item)
{
  u_int i;
  for (i = 0; i < cfg_ncauses; i += 1)
  {
    cmdq_print(item, "%s", cfg_causes[i]);
    free(cfg_causes[i]);
  }

  free(cfg_causes);
  cfg_causes = 0;
  cfg_ncauses = 0;
}


----------------------------
None
----------------------------
***/


static enum cmd_retval cmd_source_file_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  int quiet = args_has(args, 'q');
  struct client *c = item->client;
  struct cmdq_item *new_item;
  unsigned int new_item_idx = 0;
  enum cmd_retval retval;
  char *pattern;
  unsigned int pattern_idx = 0;
  char *tmp;
  const char *path = args->argv[0];
  glob_t g;
  u_int i;
  if ((*path) == '/')
  {
    pattern_idx = xstrdup(path);
  }
  else
  {
    utf8_stravis(&tmp, server_client_get_cwd(c), 0x100);
    xasprintf(&(&pattern[pattern_idx]), "%s/%s", tmp, path);
    free(tmp);
  }
  log_debug("%s: %s", __func__, pattern);
  retval = CMD_RETURN_NORMAL;
  if (glob(pattern, 0, 0, &g) != 0)
  {
    if ((!quiet) || (errno != ENOENT))
    {
      cmdq_error(item, "%s: %s", path, strerror(errno));
      retval = CMD_RETURN_ERROR;
    }
    free(pattern);
    return retval;
  }
  free(pattern);
  for (i = 0; i < ((u_int) g.gl_pathc); i += 1)
  {
    if (load_cfg(g.gl_pathv[i], c, item, quiet) < 0)
    {
      retval = CMD_RETURN_ERROR;
    }
  }

  if (cfg_finished)
  {
    new_item_idx = cmdq_get_callback1("cmd_source_file_done", cmd_source_file_done, 0);
    cmdq_insert_after(item, new_item);
  }
  globfree(&g);
  return retval;
}


/*** DEPENDENCIES:
extern int cfg_finished
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
int load_cfg(const char *path, struct client *c, struct cmdq_item *item, int quiet)
{
  FILE *f;
  unsigned int f_idx = 0;
  const char delim[3] = {'\\', '\\', '\0'};
  u_int found = 0;
  size_t line = 0;
  char *buf;
  unsigned int buf_idx = 0;
  char *cause1;
  char *p;
  unsigned int p_idx = 0;
  char *q;
  unsigned int q_idx = 0;
  struct cmd_list *cmdlist;
  unsigned int cmdlist_idx = 0;
  struct cmdq_item *new_item;
  unsigned int new_item_idx = 0;
  struct cfg_cond *cond;
  unsigned int cond_idx = 0;
  struct cfg_cond *cond1;
  unsigned int cond1_idx = 0;
  struct cfg_conds conds;
  do
  {
    (&conds)->tqh_first = 0;
    (&conds)->tqh_last = &(&conds)->tqh_first;
  }
  while (0);
  log_debug("loading %s", path);
  if ((f_idx = fopen(path, "rb")) == 0)
  {
    if ((errno == ENOENT) && quiet)
    {
      return 0;
    }
    cfg_add_cause("%s: %s", path, strerror(errno));
    return -1;
  }
  while ((buf_idx = fparseln(f, 0, &line, delim, 0)) != 0)
  {
    helper_load_cfg_1(&found, &p_idx, &q_idx, &cmdlist_idx, &new_item_idx, &cond_idx, path, c, item, line, buf, buf_idx, cause1, p, q, cmdlist, new_item, cond, conds);
  }

  fclose(f);
  for (cond_idx = *((struct cfg_conds *) (&conds)->tqh_last)->tqh_last; ((&cond[cond_idx]) != 0) && ((cond1_idx = *((struct cfg_conds *) cond->entry.tqe_prev)->tqh_last, 1)); cond_idx = &cond1[cond1_idx])
  {
    cfg_add_cause("%s:%zu: unterminated %%if", path, cond->line);
    do
    {
      if (cond->entry.tqe_next != 0)
      {
        cond->entry.tqe_next->entry.tqe_prev = cond->entry.tqe_prev;
      }
      else
        (&conds)->tqh_last = cond->entry.tqe_prev;
      *cond->entry.tqe_prev = cond->entry.tqe_next;
      ;
      ;
    }
    while (0);
    free(cond);
  }

  return found;
}


----------------------------
None
----------------------------
const char *server_client_get_cwd(struct client *c)
{
  struct session *s;
  unsigned int s_idx = 0;
  if (((c != 0) && (c->session == 0)) && (c->cwd != 0))
  {
    return c->cwd;
  }
  if (((c != 0) && ((s_idx = c->session) != 0)) && (s->cwd != 0))
  {
    return s->cwd;
  }
  return ".";
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
int utf8_stravis(char **dst, const char *src, int flag)
{
  char *buf;
  unsigned int buf_idx = 0;
  int len;
  buf_idx = xreallocarray(0, 4, strlen(src) + 1);
  len = utf8_strvis(buf, src, strlen(src), flag);
  *dst = xrealloc(buf, len + 1);
  return len;
}


----------------------------
typedef struct 
{
} glob_t
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
static enum cmd_retval cmd_source_file_done(struct cmdq_item *item, void *data)
{
  cfg_print_causes(item);
  return CMD_RETURN_NORMAL;
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
int args_has(struct args *args, u_char ch)
{
  return args_find(args, ch) != 0;
}


----------------------------
None
----------------------------
***/


