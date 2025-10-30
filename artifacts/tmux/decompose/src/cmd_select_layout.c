static enum cmd_retval cmd_select_layout_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct winlink *wl = item->target.wl;
  struct window *w = wl->window;
  struct window_pane *wp = item->target.wp;
  const char *layoutname;
  unsigned int layoutname_idx = 0;
  char *oldlayout;
  unsigned int oldlayout_idx = 0;
  int next;
  int previous;
  int layout;
  server_unzoom_window(w);
  next = self->entry == (&cmd_next_layout_entry);
  if (args_has(args, 'n'))
  {
    next = 1;
  }
  previous = self->entry == (&cmd_previous_layout_entry);
  if (args_has(args, 'p'))
  {
    previous = 1;
  }
  oldlayout_idx = w->old_layout;
  w->old_layout = layout_dump(w->layout_root);
  if (next || previous)
  {
    if (next)
    {
      layout_set_next(w);
    }
    else
      layout_set_previous(w);
    goto changed;
  }
  if (args_has(args, 'E'))
  {
    layout_spread_out(wp);
    goto changed;
  }
  if (!args_has(args, 'o'))
  {
    if (args->argc == 0)
    {
      layout = w->lastlayout;
    }
    else
      layout = layout_set_lookup(args->argv[0]);
    if (layout != (-1))
    {
      layout_set_select(w, layout);
      goto changed;
    }
  }
  if (args->argc != 0)
  {
    layoutname_idx = args->argv[0];
  }
  else
    if (args_has(args, 'o'))
  {
    layoutname_idx = &oldlayout[oldlayout_idx];
  }
  else
    layoutname_idx = 0;
  if ((&layoutname[layoutname_idx]) != 0)
  {
    if (layout_parse(w, layoutname) == (-1))
    {
      cmdq_error(item, "can't set layout: %s", layoutname);
      goto error;
    }
    goto changed;
  }
  free(oldlayout);
  return CMD_RETURN_NORMAL;
  changed:
  free(oldlayout);

  server_redraw_window(w);
  return CMD_RETURN_NORMAL;
  error:
  free(w->old_layout);

  w->old_layout = &oldlayout[oldlayout_idx];
  return CMD_RETURN_ERROR;
}


/*** DEPENDENCIES:
int layout_set_lookup(const char *name)
{
  u_int i;
  int matched = -1;
  for (i = 0; i < ((sizeof(layout_sets)) / (sizeof(layout_sets[0]))); i += 1)
  {
    if (strncmp(layout_sets[i].name, name, strlen(name)) == 0)
    {
      if (matched != (-1))
      {
        return -1;
      }
      matched = i;
    }
  }

  return matched;
}


----------------------------
void server_unzoom_window(struct window *w)
{
  if (window_unzoom(w) == 0)
  {
    server_redraw_window(w);
  }
}


----------------------------
u_int layout_set_select(struct window *w, u_int layout)
{
  if (layout > (((sizeof(layout_sets)) / (sizeof(layout_sets[0]))) - 1))
  {
    layout = ((sizeof(layout_sets)) / (sizeof(layout_sets[0]))) - 1;
  }
  if (layout_sets[layout].arrange != 0)
  {
    layout_sets[layout].arrange(w);
  }
  w->lastlayout = layout;
  return layout;
}


----------------------------
extern const struct cmd_entry cmd_previous_layout_entry
----------------------------
u_int layout_set_previous(struct window *w)
{
  u_int layout;
  if (w->lastlayout == (-1))
  {
    layout = ((sizeof(layout_sets)) / (sizeof(layout_sets[0]))) - 1;
  }
  else
  {
    layout = w->lastlayout;
    if (layout == 0)
    {
      layout = ((sizeof(layout_sets)) / (sizeof(layout_sets[0]))) - 1;
    }
    else
      layout--;
    layout -= 1;
  }
  if (layout_sets[layout].arrange != 0)
  {
    layout_sets[layout].arrange(w);
  }
  w->lastlayout = layout;
  return layout;
}


----------------------------
void server_redraw_window(struct window *w)
{
  struct client *c;
  unsigned int c_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if ((c->session != 0) && (c->session->curw->window == w))
    {
      server_redraw_client(c);
    }
  }

}


----------------------------
char *layout_dump(struct layout_cell *root)
{
  char layout[1024];
  char *out;
  *layout = '\0';
  if (layout_append(root, layout, sizeof(layout)) != 0)
  {
    return 0;
  }
  xasprintf(&out, "%04hx,%s", layout_checksum(layout), layout);
  return out;
}


----------------------------
None
----------------------------
extern const struct cmd_entry cmd_next_layout_entry
----------------------------
u_int layout_set_next(struct window *w)
{
  u_int layout;
  if (w->lastlayout == (-1))
  {
    layout = 0;
  }
  else
  {
    layout = w->lastlayout + 1;
    if (layout > (((sizeof(layout_sets)) / (sizeof(layout_sets[0]))) - 1))
    {
      layout = 0;
    }
  }
  if (layout_sets[layout].arrange != 0)
  {
    layout_sets[layout].arrange(w);
  }
  w->lastlayout = layout;
  return layout;
}


----------------------------
int layout_parse(struct window *w, const char *layout)
{
  unsigned int layout_idx = 0;
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int npanes;
  u_int ncells;
  u_int sx;
  u_int sy;
  u_short csum;
  if (sscanf(layout, "%hx,", &csum) != 1)
  {
    return -1;
  }
  layout_idx += 5;
  if (csum != layout_checksum(layout))
  {
    return -1;
  }
  lc_idx = layout_construct(0, &(&layout[layout_idx]));
  if ((&lc[lc_idx]) == 0)
  {
    return -1;
  }
  if (layout[layout_idx] != '\0')
  {
    goto fail;
  }
  for (;;)
  {
    npanes = window_count_panes(w);
    ncells = layout_count_cells(lc);
    if (npanes > ncells)
    {
      goto fail;
    }
    if (npanes == ncells)
    {
      break;
    }
    lcchild_idx = layout_find_bottomright(lc);
    layout_destroy_cell(w, lcchild, &(&lc[lc_idx]));
  }

  sx = w->sx;
  sy = w->sy;
  window_resize(w, lc->sx, lc->sy);
  layout_free_cell(w->layout_root);
  w->layout_root = &lc[lc_idx];
  wp_idx = (&w->panes)->tqh_first;
  layout_assign(&(&wp[wp_idx]), lc);
  layout_fix_offsets(lc);
  layout_fix_panes(w, lc->sx, lc->sy);
  layout_resize(w, sx, sy);
  window_resize(w, sx, sy);
  layout_print_cell(lc, __func__, 0);
  notify_window("window-layout-changed", w);
  return 0;
  fail:
  layout_free_cell(lc);

  return -1;
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
void layout_spread_out(struct window_pane *wp)
{
  struct layout_cell *parent;
  unsigned int parent_idx = 0;
  struct window *w = wp->window;
  parent_idx = wp->layout_cell->parent_idx;
  if ((&parent[parent_idx]) == 0)
  {
    return;
  }
  do
  {
    if (layout_spread_cell(w, parent))
    {
      layout_fix_offsets(parent);
      layout_fix_panes(w, w->sx, w->sy);
      break;
    }
  }
  while ((parent_idx = parent_idx->parent_idx) != 0);
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


