static char *cmd_capture_pane_append(char *buf, size_t *len, char *line, size_t linelen)
{
  unsigned int buf_idx = 0;
  buf_idx = xrealloc(buf_idx, ((*len) + linelen) + 1);
  memcpy((&buf[buf_idx]) + (*len), line, linelen);
  *len += linelen;
  return buf;
}


/*** DEPENDENCIES:
void *xrealloc(void *ptr, size_t size)
{
  return xreallocarray(ptr, 1, size);
}


----------------------------
***/


static char *cmd_capture_pane_pending(struct args *args, struct window_pane *wp, size_t *len)
{
  struct evbuffer *pending;
  unsigned int pending_idx = 0;
  char *buf;
  unsigned int buf_idx = 0;
  char *line;
  unsigned int line_idx = 0;
  char tmp[5];
  size_t linelen;
  u_int i;
  pending_idx = input_pending(wp);
  if ((&pending[pending_idx]) == 0)
  {
    return xstrdup("");
  }
  line_idx = EVBUFFER_DATA(pending);
  linelen = EVBUFFER_LENGTH(pending);
  buf_idx = xstrdup("");
  if (args_has(args, 'C'))
  {
    for (i = 0; i < linelen; i += 1)
    {
      if ((line[i + line_idx] >= ' ') && (line[i + line_idx] != '\\'))
      {
        tmp[0] = line[i + line_idx];
        tmp[1] = '\0';
      }
      else
        xsnprintf(tmp, sizeof(tmp), "\\%03hho", line[i + line_idx]);
      buf_idx = cmd_capture_pane_append(buf_idx, len, tmp, strlen(tmp));
    }

  }
  else
    buf_idx = cmd_capture_pane_append(buf_idx, len, line, linelen);
  return buf;
}


/*** DEPENDENCIES:
static char *cmd_capture_pane_append(char *buf, size_t *len, char *line, size_t linelen)
{
  unsigned int buf_idx = 0;
  buf_idx = xrealloc(buf_idx, ((*len) + linelen) + 1);
  memcpy((&buf[buf_idx]) + (*len), line, linelen);
  *len += linelen;
  return buf;
}


----------------------------
int xsnprintf(char *str, size_t len, const char *fmt, ...)
{
  va_list ap;
  int i;
  __builtin_va_start(ap);
  i = xvsnprintf(str, len, fmt, ap);
  ;
  return i;
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
None
----------------------------
struct evbuffer *input_pending(struct window_pane *wp)
{
  return wp->ictx->since_ground;
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


static char *cmd_capture_pane_history(struct args *args, struct cmdq_item *item, struct window_pane *wp, size_t *len)
{
  struct grid *gd;
  unsigned int gd_idx = 0;
  const struct grid_line *gl;
  unsigned int gl_idx = 0;
  struct grid_cell *gc = 0;
  int n;
  int with_codes;
  int escape_c0;
  int join_lines;
  u_int i;
  u_int sx;
  u_int top;
  u_int bottom;
  u_int tmp;
  char *cause;
  char *buf;
  unsigned int buf_idx = 0;
  char *line;
  unsigned int line_idx = 0;
  const char *Sflag;
  unsigned int Sflag_idx = 0;
  const char *Eflag;
  unsigned int Eflag_idx = 0;
  size_t linelen;
  sx = (&wp->base)->grid->sx;
  if (args_has(args, 'a'))
  {
    gd_idx = wp->saved_grid;
    if ((&gd[gd_idx]) == 0)
    {
      if (!args_has(args, 'q'))
      {
        cmdq_error(item, "no alternate screen");
        return 0;
      }
      return xstrdup("");
    }
  }
  else
    gd_idx = wp->base.grid;
  Sflag_idx = args_get(args, 'S');
  if (((&Sflag[Sflag_idx]) != 0) && (strcmp(Sflag, "-") == 0))
  {
    top = 0;
  }
  else
  {
    n = args_strtonum(args, 'S', -2147483648, 32767, &cause);
    if (cause != 0)
    {
      top = gd->hsize;
      free(cause);
    }
    else
      if ((n < 0) && (((u_int) (-n)) > gd->hsize))
    {
      top = 0;
    }
    else
      top = gd->hsize + n;
    if (top > ((gd->hsize + gd->sy) - 1))
    {
      top = (gd->hsize + gd->sy) - 1;
    }
  }
  Eflag_idx = args_get(args, 'E');
  if (((&Eflag[Eflag_idx]) != 0) && (strcmp(Eflag, "-") == 0))
  {
    bottom = (gd->hsize + gd->sy) - 1;
  }
  else
  {
    n = args_strtonum(args, 'E', -2147483648, 32767, &cause);
    if (cause != 0)
    {
      bottom = (gd->hsize + gd->sy) - 1;
      free(cause);
    }
    else
      if ((n < 0) && (((u_int) (-n)) > gd->hsize))
    {
      bottom = 0;
    }
    else
      bottom = gd->hsize + n;
    if (bottom > ((gd->hsize + gd->sy) - 1))
    {
      bottom = (gd->hsize + gd->sy) - 1;
    }
  }
  if (bottom < top)
  {
    tmp = bottom;
    bottom = top;
    top = tmp;
  }
  with_codes = args_has(args, 'e');
  escape_c0 = args_has(args, 'C');
  join_lines = args_has(args, 'J');
  buf_idx = 0;
  for (i = top; i <= bottom; i += 1)
  {
    line_idx = grid_string_cells(gd, 0, i, sx, &gc, with_codes, escape_c0, !join_lines);
    linelen = strlen(line);
    buf_idx = cmd_capture_pane_append(buf_idx, len, line, linelen);
    gl_idx = grid_peek_line(gd, i);
    if ((!join_lines) || (!(gl->flags & 0x1)))
    {
      buf[((*len)++) + buf_idx] = '\n';
    }
    free(line);
  }

  return buf;
}


/*** DEPENDENCIES:
None
----------------------------
static char *cmd_capture_pane_append(char *buf, size_t *len, char *line, size_t linelen)
{
  unsigned int buf_idx = 0;
  buf_idx = xrealloc(buf_idx, ((*len) + linelen) + 1);
  memcpy((&buf[buf_idx]) + (*len), line, linelen);
  *len += linelen;
  return buf;
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
int args_has(struct args *args, u_char ch)
{
  return args_find(args, ch) != 0;
}


----------------------------
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
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
char *grid_string_cells(struct grid *gd, u_int px, u_int py, u_int nx, struct grid_cell **lastgc, int with_codes, int escape_c0, int trim)
{
  struct grid_cell gc;
  static struct grid_cell lastgc1;
  const char *data;
  unsigned int data_idx = 0;
  char *buf;
  unsigned int buf_idx = 0;
  char code[128];
  size_t len;
  size_t off;
  size_t size;
  size_t codelen;
  u_int xx;
  const struct grid_line *gl;
  unsigned int gl_idx = 0;
  if ((lastgc != 0) && ((*lastgc) == 0))
  {
    memcpy(&lastgc1, &grid_default_cell, sizeof(lastgc1));
    *lastgc = &lastgc1;
  }
  len = 128;
  buf_idx = xmalloc(len);
  off = 0;
  gl_idx = grid_peek_line(gd, py);
  for (xx = px; xx < (px + nx); xx += 1)
  {
    helper_grid_string_cells_1(&data_idx, &buf_idx, &len, &off, &size, &codelen, gd, py, lastgc, with_codes, escape_c0, gc, data, buf, code, xx, gl, gl_idx);
  }

  if (trim)
  {
    while ((off > 0) && (buf[(off - 1) + buf_idx] == ' '))
    {
      off -= 1;
    }

  }
  buf[off + buf_idx] = '\0';
  return buf;
}


----------------------------
None
----------------------------
const struct grid_line *grid_peek_line(struct grid *gd, u_int py)
{
  if (grid_check_y(gd, __func__, py) != 0)
  {
    return 0;
  }
  return &gd->linedata[py];
}


----------------------------
long long args_strtonum(struct args *args, u_char ch, long long minval, long long maxval, char **cause)
{
  const char *errstr;
  long long ll;
  struct args_entry *entry;
  unsigned int entry_idx = 0;
  if ((entry_idx = args_find(args, ch)) == 0)
  {
    *cause = xstrdup("missing");
    return 0;
  }
  ll = strtonum(entry->value, minval, maxval, &errstr);
  if (errstr != 0)
  {
    *cause = xstrdup(errstr);
    return 0;
  }
  *cause = 0;
  return ll;
}


----------------------------
None
----------------------------
***/


static enum cmd_retval cmd_capture_pane_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct client *c;
  unsigned int c_idx = 0;
  struct window_pane *wp = item->target.wp;
  char *buf;
  unsigned int buf_idx = 0;
  char *cause;
  const char *bufname;
  unsigned int bufname_idx = 0;
  size_t len;
  if (self->entry == (&cmd_clear_history_entry))
  {
    if (wp->mode == (&window_copy_mode))
    {
      window_pane_reset_mode(wp);
    }
    grid_clear_history(wp->base.grid);
    return CMD_RETURN_NORMAL;
  }
  len = 0;
  if (args_has(args, 'P'))
  {
    buf_idx = cmd_capture_pane_pending(args, wp, &len);
  }
  else
    buf_idx = cmd_capture_pane_history(args, item, wp, &len);
  if ((&buf[buf_idx]) == 0)
  {
    return CMD_RETURN_ERROR;
  }
  if (args_has(args, 'p'))
  {
    c_idx = item->client;
    if (((&c[c_idx]) == 0) || ((c->session != 0) && (!(c->flags & 0x2000))))
    {
      cmdq_error(item, "can't write to stdout");
      free(buf);
      return CMD_RETURN_ERROR;
    }
    evbuffer_add(c->stdout_data, buf, len);
    free(buf);
    if (args_has(args, 'P') && (len > 0))
    {
      evbuffer_add(c->stdout_data, "\n", 1);
    }
    server_client_push_stdout(c);
  }
  else
  {
    bufname_idx = 0;
    if (args_has(args, 'b'))
    {
      bufname_idx = args_get(args, 'b');
    }
    if (paste_set(buf, len, bufname, &cause) != 0)
    {
      cmdq_error(item, "%s", cause);
      free(cause);
      free(buf);
      return CMD_RETURN_ERROR;
    }
  }
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
extern const struct window_mode window_copy_mode
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
None
----------------------------
extern const struct cmd_entry cmd_clear_history_entry
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
static char *cmd_capture_pane_pending(struct args *args, struct window_pane *wp, size_t *len)
{
  struct evbuffer *pending;
  unsigned int pending_idx = 0;
  char *buf;
  unsigned int buf_idx = 0;
  char *line;
  unsigned int line_idx = 0;
  char tmp[5];
  size_t linelen;
  u_int i;
  pending_idx = input_pending(wp);
  if ((&pending[pending_idx]) == 0)
  {
    return xstrdup("");
  }
  line_idx = EVBUFFER_DATA(pending);
  linelen = EVBUFFER_LENGTH(pending);
  buf_idx = xstrdup("");
  if (args_has(args, 'C'))
  {
    for (i = 0; i < linelen; i += 1)
    {
      if ((line[i + line_idx] >= ' ') && (line[i + line_idx] != '\\'))
      {
        tmp[0] = line[i + line_idx];
        tmp[1] = '\0';
      }
      else
        xsnprintf(tmp, sizeof(tmp), "\\%03hho", line[i + line_idx]);
      buf_idx = cmd_capture_pane_append(buf_idx, len, tmp, strlen(tmp));
    }

  }
  else
    buf_idx = cmd_capture_pane_append(buf_idx, len, line, linelen);
  return buf;
}


----------------------------
void grid_clear_history(struct grid *gd)
{
  grid_free_lines(gd, 0, gd->hsize);
  memmove(&gd->linedata[0], &gd->linedata[gd->hsize], gd->sy * (sizeof(*gd->linedata)));
  gd->hscrolled = 0;
  gd->hsize = 0;
  gd->linedata = xreallocarray(gd->linedata, gd->sy, sizeof(*gd->linedata));
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
static char *cmd_capture_pane_history(struct args *args, struct cmdq_item *item, struct window_pane *wp, size_t *len)
{
  struct grid *gd;
  unsigned int gd_idx = 0;
  const struct grid_line *gl;
  unsigned int gl_idx = 0;
  struct grid_cell *gc = 0;
  int n;
  int with_codes;
  int escape_c0;
  int join_lines;
  u_int i;
  u_int sx;
  u_int top;
  u_int bottom;
  u_int tmp;
  char *cause;
  char *buf;
  unsigned int buf_idx = 0;
  char *line;
  unsigned int line_idx = 0;
  const char *Sflag;
  unsigned int Sflag_idx = 0;
  const char *Eflag;
  unsigned int Eflag_idx = 0;
  size_t linelen;
  sx = (&wp->base)->grid->sx;
  if (args_has(args, 'a'))
  {
    gd_idx = wp->saved_grid;
    if ((&gd[gd_idx]) == 0)
    {
      if (!args_has(args, 'q'))
      {
        cmdq_error(item, "no alternate screen");
        return 0;
      }
      return xstrdup("");
    }
  }
  else
    gd_idx = wp->base.grid;
  Sflag_idx = args_get(args, 'S');
  if (((&Sflag[Sflag_idx]) != 0) && (strcmp(Sflag, "-") == 0))
  {
    top = 0;
  }
  else
  {
    n = args_strtonum(args, 'S', -2147483648, 32767, &cause);
    if (cause != 0)
    {
      top = gd->hsize;
      free(cause);
    }
    else
      if ((n < 0) && (((u_int) (-n)) > gd->hsize))
    {
      top = 0;
    }
    else
      top = gd->hsize + n;
    if (top > ((gd->hsize + gd->sy) - 1))
    {
      top = (gd->hsize + gd->sy) - 1;
    }
  }
  Eflag_idx = args_get(args, 'E');
  if (((&Eflag[Eflag_idx]) != 0) && (strcmp(Eflag, "-") == 0))
  {
    bottom = (gd->hsize + gd->sy) - 1;
  }
  else
  {
    n = args_strtonum(args, 'E', -2147483648, 32767, &cause);
    if (cause != 0)
    {
      bottom = (gd->hsize + gd->sy) - 1;
      free(cause);
    }
    else
      if ((n < 0) && (((u_int) (-n)) > gd->hsize))
    {
      bottom = 0;
    }
    else
      bottom = gd->hsize + n;
    if (bottom > ((gd->hsize + gd->sy) - 1))
    {
      bottom = (gd->hsize + gd->sy) - 1;
    }
  }
  if (bottom < top)
  {
    tmp = bottom;
    bottom = top;
    top = tmp;
  }
  with_codes = args_has(args, 'e');
  escape_c0 = args_has(args, 'C');
  join_lines = args_has(args, 'J');
  buf_idx = 0;
  for (i = top; i <= bottom; i += 1)
  {
    line_idx = grid_string_cells(gd, 0, i, sx, &gc, with_codes, escape_c0, !join_lines);
    linelen = strlen(line);
    buf_idx = cmd_capture_pane_append(buf_idx, len, line, linelen);
    gl_idx = grid_peek_line(gd, i);
    if ((!join_lines) || (!(gl->flags & 0x1)))
    {
      buf[((*len)++) + buf_idx] = '\n';
    }
    free(line);
  }

  return buf;
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


