void set_cfg_file(const char *path)
{
  free(cfg_file);
  cfg_file = xstrdup(path);
}


/*** DEPENDENCIES:
static char *cfg_file
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
***/


static void cfg_handle_else(const char *path, size_t line, struct cfg_conds *conds)
{
  struct cfg_cond *cond = conds->tqh_first;
  if ((cond == 0) || cond->saw_else)
  {
    cfg_add_cause("%s:%zu: unexpected %%else", path, line);
    return;
  }
  cond->saw_else = 1;
  cond->met = !cond->skip;
  cond->skip = 1;
}


/*** DEPENDENCIES:
struct cfg_cond
{
  size_t line;
  int met;
  int skip;
  int saw_else;
  struct 
  {
    struct cfg_cond *tqe_next;
    struct cfg_cond **tqe_prev;
  } entry;
}
----------------------------
void cfg_add_cause(const char *fmt, ...)
{
  va_list ap;
  char *msg;
  __builtin_va_start(ap);
  xvasprintf(&msg, fmt, ap);
  ;
  cfg_ncauses += 1;
  cfg_causes = xreallocarray(cfg_causes, cfg_ncauses, sizeof(*cfg_causes));
  cfg_causes[cfg_ncauses - 1] = msg;
}


----------------------------
struct cfg_conds
{
  struct cfg_cond *tqh_first;
  struct cfg_cond **tqh_last;
}
----------------------------
***/


static void cfg_handle_endif(const char *path, size_t line, struct cfg_conds *conds)
{
  struct cfg_cond *cond = conds->tqh_first;
  if (cond == 0)
  {
    cfg_add_cause("%s:%zu: unexpected %%endif", path, line);
    return;
  }
  do
  {
    if (cond->entry.tqe_next != 0)
    {
      cond->entry.tqe_next->entry.tqe_prev = cond->entry.tqe_prev;
    }
    else
      conds->tqh_last = cond->entry.tqe_prev;
    *cond->entry.tqe_prev = cond->entry.tqe_next;
    ;
    ;
  }
  while (0);
  free(cond);
}


/*** DEPENDENCIES:
struct cfg_cond
{
  size_t line;
  int met;
  int skip;
  int saw_else;
  struct 
  {
    struct cfg_cond *tqe_next;
    struct cfg_cond **tqe_prev;
  } entry;
}
----------------------------
void cfg_add_cause(const char *fmt, ...)
{
  va_list ap;
  char *msg;
  __builtin_va_start(ap);
  xvasprintf(&msg, fmt, ap);
  ;
  cfg_ncauses += 1;
  cfg_causes = xreallocarray(cfg_causes, cfg_ncauses, sizeof(*cfg_causes));
  cfg_causes[cfg_ncauses - 1] = msg;
}


----------------------------
struct cfg_conds
{
  struct cfg_cond *tqh_first;
  struct cfg_cond **tqh_last;
}
----------------------------
***/


void cfg_show_causes(struct session *s)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int i;
  if ((s == 0) || (cfg_ncauses == 0))
  {
    return;
  }
  wp_idx = s->curw->window->active;
  window_pane_set_mode(wp, &window_copy_mode, 0, 0);
  window_copy_init_for_output(wp);
  for (i = 0; i < cfg_ncauses; i += 1)
  {
    window_copy_add(wp, "%s", cfg_causes[i]);
    free(cfg_causes[i]);
  }

  free(cfg_causes);
  cfg_causes = 0;
  cfg_ncauses = 0;
}


/*** DEPENDENCIES:
extern const struct window_mode window_copy_mode
----------------------------
extern u_int cfg_ncauses
----------------------------
int window_pane_set_mode(struct window_pane *wp, const struct window_mode *mode, struct cmd_find_state *fs, struct args *args)
{
  struct screen *s;
  unsigned int s_idx = 0;
  struct timeval tv = {.tv_sec = 10};
  if (wp->mode != 0)
  {
    return 1;
  }
  wp->mode = mode;
  wp->modelast = time(0);
  evtimer_set(&wp->modetimer, window_pane_mode_timer, wp);
  evtimer_add(&wp->modetimer, &tv);
  if ((s_idx = wp->mode->init(wp, fs, args)) != 0)
  {
    wp->screen = &s[s_idx];
  }
  wp->flags |= 0x1 | 0x80;
  server_status_window(wp->window);
  notify_pane("pane-mode-changed", wp);
  return 0;
}


----------------------------
void window_copy_init_for_output(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  data->backing = xmalloc(sizeof(*data->backing));
  screen_init(data->backing, (&wp->base)->grid->sx, (&wp->base)->grid->sy, 4294967295U);
}


----------------------------
void window_copy_add(struct window_pane *wp, const char *fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  window_copy_vadd(wp, fmt, ap);
  ;
}


----------------------------
extern char **cfg_causes
----------------------------
None
----------------------------
***/


static enum cmd_retval cfg_done(struct cmdq_item *item, void *data)
{
  if (cfg_finished)
  {
    return CMD_RETURN_NORMAL;
  }
  cfg_finished = 1;
  if (!((&sessions)->rbh_root == 0))
  {
    cfg_show_causes(sessions_RB_MINMAX(&sessions, -1));
  }
  if (cfg_item != 0)
  {
    cfg_item->flags &= ~0x2;
  }
  status_prompt_load_history();
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
void cfg_show_causes(struct session *s)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int i;
  if ((s == 0) || (cfg_ncauses == 0))
  {
    return;
  }
  wp_idx = s->curw->window->active;
  window_pane_set_mode(wp, &window_copy_mode, 0, 0);
  window_copy_init_for_output(wp);
  for (i = 0; i < cfg_ncauses; i += 1)
  {
    window_copy_add(wp, "%s", cfg_causes[i]);
    free(cfg_causes[i]);
  }

  free(cfg_causes);
  cfg_causes = 0;
  cfg_ncauses = 0;
}


----------------------------
extern int cfg_finished
----------------------------
void status_prompt_load_history(void)
{
  FILE *f;
  unsigned int f_idx = 0;
  char *history_file;
  unsigned int history_file_idx = 0;
  char *line;
  unsigned int line_idx = 0;
  char *tmp;
  unsigned int tmp_idx = 0;
  size_t length;
  if ((history_file_idx = status_prompt_find_history_file()) == 0)
  {
    return;
  }
  log_debug("loading history from %s", history_file);
  f_idx = fopen(history_file, "r");
  if ((&f[f_idx]) == 0)
  {
    log_debug("%s: %s", history_file, strerror(errno));
    free(history_file);
    return;
  }
  free(history_file);
  for (;;)
  {
    helper_status_prompt_load_history_1(&line_idx, &tmp_idx, &length, f, line, tmp);
  }

  fclose(f);
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
struct sessions
{
  struct session *rbh_root;
}
----------------------------
None
----------------------------
***/


static enum cmd_retval cfg_client_done(struct cmdq_item *item, void *data)
{
  if (!cfg_finished)
  {
    return CMD_RETURN_WAIT;
  }
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
extern int cfg_finished
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


static int cfg_check_condition(const char *path, size_t line, const char *p, int *skip)
{
  unsigned int p_idx = 0;
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  char *s;
  unsigned int s_idx = 0;
  int result;
  while (isspace((u_char) p[p_idx]))
  {
    p_idx += 1;
  }

  if (p[0 + p_idx] == '\0')
  {
    cfg_add_cause("%s:%zu: invalid condition", path, line);
    *skip = 1;
    return 0;
  }
  ft_idx = format_create(0, 0, 0, 0x4);
  s_idx = format_expand(ft, p);
  result = format_true(s);
  free(s);
  format_free(ft);
  *skip = result;
  return result;
}


/*** DEPENDENCIES:
void cfg_add_cause(const char *fmt, ...)
{
  va_list ap;
  char *msg;
  __builtin_va_start(ap);
  xvasprintf(&msg, fmt, ap);
  ;
  cfg_ncauses += 1;
  cfg_causes = xreallocarray(cfg_causes, cfg_ncauses, sizeof(*cfg_causes));
  cfg_causes[cfg_ncauses - 1] = msg;
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
int format_true(const char *s)
{
  if (((s != 0) && ((*s) != '\0')) && ((s[0] != '0') || (s[1] != '\0')))
  {
    return 1;
  }
  return 0;
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
None
----------------------------
None
----------------------------
***/


static void cfg_handle_if(const char *path, size_t line, struct cfg_conds *conds, const char *p)
{
  struct cfg_cond *cond;
  unsigned int cond_idx = 0;
  struct cfg_cond *parent = conds->tqh_first;
  cond_idx = xcalloc(1, sizeof(*cond_idx));
  cond->line = line;
  if ((parent == 0) || parent->met)
  {
    cond->met = cfg_check_condition(path, line, p, &cond->skip);
  }
  else
    cond->skip = 1;
  cond->saw_else = 0;
  do
  {
    if ((cond->entry.tqe_next = conds->tqh_first) != 0)
    {
      conds->tqh_first->entry.tqe_prev = &cond->entry.tqe_next;
    }
    else
      conds->tqh_last = &cond->entry.tqe_next;
    conds->tqh_first = &cond[cond_idx];
    cond->entry.tqe_prev = &conds->tqh_first;
  }
  while (0);
}


/*** DEPENDENCIES:
struct cfg_conds
{
  struct cfg_cond *tqh_first;
  struct cfg_cond **tqh_last;
}
----------------------------
struct cfg_cond
{
  size_t line;
  int met;
  int skip;
  int saw_else;
  struct 
  {
    struct cfg_cond *tqe_next;
    struct cfg_cond **tqe_prev;
  } entry;
}
----------------------------
static int cfg_check_condition(const char *path, size_t line, const char *p, int *skip)
{
  unsigned int p_idx = 0;
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  char *s;
  unsigned int s_idx = 0;
  int result;
  while (isspace((u_char) p[p_idx]))
  {
    p_idx += 1;
  }

  if (p[0 + p_idx] == '\0')
  {
    cfg_add_cause("%s:%zu: invalid condition", path, line);
    *skip = 1;
    return 0;
  }
  ft_idx = format_create(0, 0, 0, 0x4);
  s_idx = format_expand(ft, p);
  result = format_true(s);
  free(s);
  format_free(ft);
  *skip = result;
  return result;
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
***/


static void cfg_handle_elif(const char *path, size_t line, struct cfg_conds *conds, const char *p)
{
  struct cfg_cond *cond = conds->tqh_first;
  if ((cond == 0) || cond->saw_else)
  {
    cfg_add_cause("%s:%zu: unexpected %%elif", path, line);
  }
  else
    if (!cond->skip)
  {
    cond->met = cfg_check_condition(path, line, p, &cond->skip);
  }
  else
    cond->met = 0;
}


/*** DEPENDENCIES:
struct cfg_conds
{
  struct cfg_cond *tqh_first;
  struct cfg_cond **tqh_last;
}
----------------------------
struct cfg_cond
{
  size_t line;
  int met;
  int skip;
  int saw_else;
  struct 
  {
    struct cfg_cond *tqe_next;
    struct cfg_cond **tqe_prev;
  } entry;
}
----------------------------
void cfg_add_cause(const char *fmt, ...)
{
  va_list ap;
  char *msg;
  __builtin_va_start(ap);
  xvasprintf(&msg, fmt, ap);
  ;
  cfg_ncauses += 1;
  cfg_causes = xreallocarray(cfg_causes, cfg_ncauses, sizeof(*cfg_causes));
  cfg_causes[cfg_ncauses - 1] = msg;
}


----------------------------
static int cfg_check_condition(const char *path, size_t line, const char *p, int *skip)
{
  unsigned int p_idx = 0;
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  char *s;
  unsigned int s_idx = 0;
  int result;
  while (isspace((u_char) p[p_idx]))
  {
    p_idx += 1;
  }

  if (p[0 + p_idx] == '\0')
  {
    cfg_add_cause("%s:%zu: invalid condition", path, line);
    *skip = 1;
    return 0;
  }
  ft_idx = format_create(0, 0, 0, 0x4);
  s_idx = format_expand(ft, p);
  result = format_true(s);
  free(s);
  format_free(ft);
  *skip = result;
  return result;
}


----------------------------
***/


static void cfg_handle_directive(const char *p, const char *path, size_t line, struct cfg_conds *conds)
{
  int n = 0;
  while ((p[n] != '\0') && (!isspace((u_char) p[n])))
  {
    n += 1;
  }

  if (strncmp(p, "%if", n) == 0)
  {
    cfg_handle_if(path, line, conds, p + n);
  }
  else
    if (strncmp(p, "%elif", n) == 0)
  {
    cfg_handle_elif(path, line, conds, p + n);
  }
  else
    if (strcmp(p, "%else") == 0)
  {
    cfg_handle_else(path, line, conds);
  }
  else
    if (strcmp(p, "%endif") == 0)
  {
    cfg_handle_endif(path, line, conds);
  }
  else
    cfg_add_cause("%s:%zu: invalid directive: %s", path, line, p);
}


/*** DEPENDENCIES:
struct cfg_cond
{
  size_t line;
  int met;
  int skip;
  int saw_else;
  struct 
  {
    struct cfg_cond *tqe_next;
    struct cfg_cond **tqe_prev;
  } entry;
}
----------------------------
void cfg_add_cause(const char *fmt, ...)
{
  va_list ap;
  char *msg;
  __builtin_va_start(ap);
  xvasprintf(&msg, fmt, ap);
  ;
  cfg_ncauses += 1;
  cfg_causes = xreallocarray(cfg_causes, cfg_ncauses, sizeof(*cfg_causes));
  cfg_causes[cfg_ncauses - 1] = msg;
}


----------------------------
static void cfg_handle_if(const char *path, size_t line, struct cfg_conds *conds, const char *p)
{
  struct cfg_cond *cond;
  unsigned int cond_idx = 0;
  struct cfg_cond *parent = conds->tqh_first;
  cond_idx = xcalloc(1, sizeof(*cond_idx));
  cond->line = line;
  if ((parent == 0) || parent->met)
  {
    cond->met = cfg_check_condition(path, line, p, &cond->skip);
  }
  else
    cond->skip = 1;
  cond->saw_else = 0;
  do
  {
    if ((cond->entry.tqe_next = conds->tqh_first) != 0)
    {
      conds->tqh_first->entry.tqe_prev = &cond->entry.tqe_next;
    }
    else
      conds->tqh_last = &cond->entry.tqe_next;
    conds->tqh_first = &cond[cond_idx];
    cond->entry.tqe_prev = &conds->tqh_first;
  }
  while (0);
}


----------------------------
static void cfg_handle_else(const char *path, size_t line, struct cfg_conds *conds)
{
  struct cfg_cond *cond = conds->tqh_first;
  if ((cond == 0) || cond->saw_else)
  {
    cfg_add_cause("%s:%zu: unexpected %%else", path, line);
    return;
  }
  cond->saw_else = 1;
  cond->met = !cond->skip;
  cond->skip = 1;
}


----------------------------
static void cfg_handle_elif(const char *path, size_t line, struct cfg_conds *conds, const char *p)
{
  struct cfg_cond *cond = conds->tqh_first;
  if ((cond == 0) || cond->saw_else)
  {
    cfg_add_cause("%s:%zu: unexpected %%elif", path, line);
  }
  else
    if (!cond->skip)
  {
    cond->met = cfg_check_condition(path, line, p, &cond->skip);
  }
  else
    cond->met = 0;
}


----------------------------
struct cfg_conds
{
  struct cfg_cond *tqh_first;
  struct cfg_cond **tqh_last;
}
----------------------------
static void cfg_handle_endif(const char *path, size_t line, struct cfg_conds *conds)
{
  struct cfg_cond *cond = conds->tqh_first;
  if (cond == 0)
  {
    cfg_add_cause("%s:%zu: unexpected %%endif", path, line);
    return;
  }
  do
  {
    if (cond->entry.tqe_next != 0)
    {
      cond->entry.tqe_next->entry.tqe_prev = cond->entry.tqe_prev;
    }
    else
      conds->tqh_last = cond->entry.tqe_prev;
    *cond->entry.tqe_prev = cond->entry.tqe_next;
    ;
    ;
  }
  while (0);
  free(cond);
}


----------------------------
***/


// hint:  ['found_ref is a mutable refrence to u_int', 'p_idx_ref is a mutable refrence to unsigned int', 'q_idx_ref is a mutable refrence to unsigned int', 'cmdlist_idx_ref is a mutable refrence to unsigned int', 'new_item_idx_ref is a mutable refrence to unsigned int', 'cond_idx_ref is a mutable refrence to unsigned int']
void helper_load_cfg_1(u_int * const found_ref, unsigned int * const p_idx_ref, unsigned int * const q_idx_ref, unsigned int * const cmdlist_idx_ref, unsigned int * const new_item_idx_ref, unsigned int * const cond_idx_ref, const char * const path, struct client * const c, struct cmdq_item * const item, size_t line, char * const buf, unsigned int buf_idx, char * const cause1, char * const p, char * const q, struct cmd_list * const cmdlist, struct cmdq_item * const new_item, struct cfg_cond * const cond, struct cfg_conds conds)
{
  u_int found = *found_ref;
  unsigned int p_idx = *p_idx_ref;
  unsigned int q_idx = *q_idx_ref;
  unsigned int cmdlist_idx = *cmdlist_idx_ref;
  unsigned int new_item_idx = *new_item_idx_ref;
  unsigned int cond_idx = *cond_idx_ref;
  log_debug("%s: %s", path, buf);
  p_idx = &buf[buf_idx];
  while (isspace((u_char) p[p_idx]))
  {
    p_idx += 1;
  }

  if (p[p_idx] == '\0')
  {
    free(buf);
    continue;
  }
  q_idx = ((&p[p_idx]) + strlen(p)) - 1;
  while (((&q[q_idx]) != (&p[p_idx])) && isspace((u_char) q[q_idx]))
  {
    q[q_idx] = '\0';
    q_idx -= 1;
  }

  if (p[p_idx] == '%')
  {
    cfg_handle_directive(p, path, line, &conds);
    continue;
  }
  cond_idx = (&conds)->tqh_first;
  if (((&cond[cond_idx]) != 0) && (!cond->met))
  {
    continue;
  }
  cmdlist_idx = cmd_string_parse(p, path, line, &cause1);
  if ((&cmdlist[cmdlist_idx]) == 0)
  {
    free(buf);
    if (cause1 == 0)
    {
      continue;
    }
    cfg_add_cause("%s:%zu: %s", path, line, cause1);
    free(cause1);
    continue;
  }
  free(buf);
  new_item_idx = cmdq_get_command(cmdlist, 0, 0, 0);
  if (item != 0)
  {
    cmdq_insert_after(item, new_item);
  }
  else
    cmdq_append(c, new_item);
  cmd_list_free(cmdlist);
  found += 1;
  *found_ref = found;
  *p_idx_ref = p_idx;
  *q_idx_ref = q_idx;
  *cmdlist_idx_ref = cmdlist_idx;
  *new_item_idx_ref = new_item_idx;
  *cond_idx_ref = cond_idx;
}


/*** DEPENDENCIES:
struct cmd_list *cmd_string_parse(const char *s, const char *file, u_int line, char **cause)
{
  struct cmd_list *cmdlist = 0;
  unsigned int cmdlist_idx = 0;
  int argc;
  char **argv;
  *cause = 0;
  if (cmd_string_split(s, &argc, &argv) != 0)
  {
    xasprintf(cause, "invalid or unknown command: %s", s);
    return 0;
  }
  if (argc != 0)
  {
    cmdlist_idx = cmd_list_parse(argc, argv, file, line, cause);
    if ((&cmdlist[cmdlist_idx]) == 0)
    {
      cmd_free_argv(argc, argv);
      return 0;
    }
  }
  cmd_free_argv(argc, argv);
  return cmdlist;
}


----------------------------
void cfg_add_cause(const char *fmt, ...)
{
  va_list ap;
  char *msg;
  __builtin_va_start(ap);
  xvasprintf(&msg, fmt, ap);
  ;
  cfg_ncauses += 1;
  cfg_causes = xreallocarray(cfg_causes, cfg_ncauses, sizeof(*cfg_causes));
  cfg_causes[cfg_ncauses - 1] = msg;
}


----------------------------
struct cmdq_item *cmdq_get_command(struct cmd_list *cmdlist, struct cmd_find_state *current, struct mouse_event *m, int flags)
{
  struct cmdq_item *item;
  unsigned int item_idx = 0;
  struct cmdq_item *first = 0;
  unsigned int first_idx = 0;
  struct cmdq_item *last = 0;
  unsigned int last_idx = 0;
  struct cmd *cmd;
  unsigned int cmd_idx = 0;
  u_int group = cmdq_next_group();
  char *tmp;
  struct cmdq_shared *shared;
  unsigned int shared_idx = 0;
  shared_idx = xcalloc(1, sizeof(*shared_idx));
  if (current != 0)
  {
    cmd_find_copy_state(&shared->current, current);
  }
  else
    cmd_find_clear_state(&shared->current, 0);
  if (m != 0)
  {
    memcpy(&shared->mouse, m, sizeof(shared->mouse));
  }
  for (cmd_idx = (&cmdlist->list)->tqh_first; (&cmd[cmd_idx]) != 0; cmd_idx = cmd_idx->qentry.tqe_next)
  {
    helper_cmdq_get_command_1(&flags, &item_idx, &first_idx, &last_idx, &group, cmdlist, item, first, last, cmd, cmd_idx, tmp, shared, shared_idx);
  }

  return first;
}


----------------------------
struct cfg_cond
{
  size_t line;
  int met;
  int skip;
  int saw_else;
  struct 
  {
    struct cfg_cond *tqe_next;
    struct cfg_cond **tqe_prev;
  } entry;
}
----------------------------
void cmd_list_free(struct cmd_list *cmdlist)
{
  struct cmd *cmd;
  unsigned int cmd_idx = 0;
  struct cmd *cmd1;
  unsigned int cmd1_idx = 0;
  if ((--cmdlist->references) != 0)
  {
    return;
  }
  for (cmd_idx = (&cmdlist->list)->tqh_first; ((&cmd[cmd_idx]) != 0) && ((cmd1_idx = cmd->qentry.tqe_next, 1)); cmd_idx = &cmd1[cmd1_idx])
  {
    do
    {
      if (cmd->qentry.tqe_next != 0)
      {
        cmd->qentry.tqe_next->qentry.tqe_prev = cmd->qentry.tqe_prev;
      }
      else
        (&cmdlist->list)->tqh_last = cmd->qentry.tqe_prev;
      *cmd->qentry.tqe_prev = cmd->qentry.tqe_next;
      ;
      ;
    }
    while (0);
    args_free(cmd->args);
    free(cmd->file);
    free(cmd);
  }

  free(cmdlist);
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
struct cfg_conds
{
  struct cfg_cond *tqh_first;
  struct cfg_cond **tqh_last;
}
----------------------------
static void cfg_handle_directive(const char *p, const char *path, size_t line, struct cfg_conds *conds)
{
  int n = 0;
  while ((p[n] != '\0') && (!isspace((u_char) p[n])))
  {
    n += 1;
  }

  if (strncmp(p, "%if", n) == 0)
  {
    cfg_handle_if(path, line, conds, p + n);
  }
  else
    if (strncmp(p, "%elif", n) == 0)
  {
    cfg_handle_elif(path, line, conds, p + n);
  }
  else
    if (strcmp(p, "%else") == 0)
  {
    cfg_handle_else(path, line, conds);
  }
  else
    if (strcmp(p, "%endif") == 0)
  {
    cfg_handle_endif(path, line, conds);
  }
  else
    cfg_add_cause("%s:%zu: invalid directive: %s", path, line, p);
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


/*** DEPENDENCIES:
struct cfg_cond
{
  size_t line;
  int met;
  int skip;
  int saw_else;
  struct 
  {
    struct cfg_cond *tqe_next;
    struct cfg_cond **tqe_prev;
  } entry;
}
----------------------------
void cfg_add_cause(const char *fmt, ...)
{
  va_list ap;
  char *msg;
  __builtin_va_start(ap);
  xvasprintf(&msg, fmt, ap);
  ;
  cfg_ncauses += 1;
  cfg_causes = xreallocarray(cfg_causes, cfg_ncauses, sizeof(*cfg_causes));
  cfg_causes[cfg_ncauses - 1] = msg;
}


----------------------------
void helper_load_cfg_1(u_int * const found_ref, unsigned int * const p_idx_ref, unsigned int * const q_idx_ref, unsigned int * const cmdlist_idx_ref, unsigned int * const new_item_idx_ref, unsigned int * const cond_idx_ref, const char * const path, struct client * const c, struct cmdq_item * const item, size_t line, char * const buf, unsigned int buf_idx, char * const cause1, char * const p, char * const q, struct cmd_list * const cmdlist, struct cmdq_item * const new_item, struct cfg_cond * const cond, struct cfg_conds conds)
{
  u_int found = *found_ref;
  unsigned int p_idx = *p_idx_ref;
  unsigned int q_idx = *q_idx_ref;
  unsigned int cmdlist_idx = *cmdlist_idx_ref;
  unsigned int new_item_idx = *new_item_idx_ref;
  unsigned int cond_idx = *cond_idx_ref;
  log_debug("%s: %s", path, buf);
  p_idx = &buf[buf_idx];
  while (isspace((u_char) p[p_idx]))
  {
    p_idx += 1;
  }

  if (p[p_idx] == '\0')
  {
    free(buf);
    continue;
  }
  q_idx = ((&p[p_idx]) + strlen(p)) - 1;
  while (((&q[q_idx]) != (&p[p_idx])) && isspace((u_char) q[q_idx]))
  {
    q[q_idx] = '\0';
    q_idx -= 1;
  }

  if (p[p_idx] == '%')
  {
    cfg_handle_directive(p, path, line, &conds);
    continue;
  }
  cond_idx = (&conds)->tqh_first;
  if (((&cond[cond_idx]) != 0) && (!cond->met))
  {
    continue;
  }
  cmdlist_idx = cmd_string_parse(p, path, line, &cause1);
  if ((&cmdlist[cmdlist_idx]) == 0)
  {
    free(buf);
    if (cause1 == 0)
    {
      continue;
    }
    cfg_add_cause("%s:%zu: %s", path, line, cause1);
    free(cause1);
    continue;
  }
  free(buf);
  new_item_idx = cmdq_get_command(cmdlist, 0, 0, 0);
  if (item != 0)
  {
    cmdq_insert_after(item, new_item);
  }
  else
    cmdq_append(c, new_item);
  cmd_list_free(cmdlist);
  found += 1;
  *found_ref = found;
  *p_idx_ref = p_idx;
  *q_idx_ref = q_idx;
  *cmdlist_idx_ref = cmdlist_idx;
  *new_item_idx_ref = new_item_idx;
  *cond_idx_ref = cond_idx;
}


----------------------------
char *fparseln(FILE *fp, size_t *size, size_t *lineno, const char str[3], int flags)
{
  static const char dstr[3] = {'\\', '\\', '#'};
  char *buf = 0;
  unsigned int buf_idx = 0;
  char *ptr;
  unsigned int ptr_idx = 0;
  char *cp;
  unsigned int cp_idx = 0;
  char esc;
  char con;
  char nl;
  char com;
  size_t s;
  size_t len = 0;
  int cnt = 1;
  if (str == 0)
  {
    str = dstr;
  }
  esc = str[0];
  con = str[1];
  com = str[2];
  nl = '\n';
  while (cnt)
  {
    helper_fparseln_2(&buf_idx, &ptr_idx, &cp_idx, &s, &len, &cnt, fp, lineno, buf, ptr, cp, esc, con, nl, com);
  }

  if (((((flags & 0x0f) != 0) && esc) && ((&buf[buf_idx]) != 0)) && (strchr(buf, esc) != 0))
  {
    helper_fparseln_1(&ptr_idx, &cp_idx, &len, flags, buf, ptr, cp, esc, con, com);
  }
  if (size)
  {
    *size = len;
  }
  return buf;
}


----------------------------
struct cfg_conds
{
  struct cfg_cond *tqh_first;
  struct cfg_cond **tqh_last;
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


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
}
----------------------------
static char *cfg_file
----------------------------
const char *find_home(void)
{
  struct passwd *pw;
  unsigned int pw_idx = 0;
  static const char *home;
  unsigned int home_idx = 0;
  if ((&home[home_idx]) != 0)
  {
    return home;
  }
  home_idx = getenv("HOME");
  if (((&home[home_idx]) == 0) || (home[home_idx] == '\0'))
  {
    pw_idx = getpwuid(getuid());
    if ((&pw[pw_idx]) != 0)
    {
      home_idx = pw->pw_dir;
    }
    else
      home_idx = 0;
  }
  return home;
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
static enum cmd_retval cfg_done(struct cmdq_item *item, void *data)
{
  if (cfg_finished)
  {
    return CMD_RETURN_NORMAL;
  }
  cfg_finished = 1;
  if (!((&sessions)->rbh_root == 0))
  {
    cfg_show_causes(sessions_RB_MINMAX(&sessions, -1));
  }
  if (cfg_item != 0)
  {
    cfg_item->flags &= ~0x2;
  }
  status_prompt_load_history();
  return CMD_RETURN_NORMAL;
}


----------------------------
static enum cmd_retval cfg_client_done(struct cmdq_item *item, void *data)
{
  if (!cfg_finished)
  {
    return CMD_RETURN_WAIT;
  }
  return CMD_RETURN_NORMAL;
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


/*** DEPENDENCIES:
extern char **cfg_causes
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
extern u_int cfg_ncauses
----------------------------
None
----------------------------
***/


