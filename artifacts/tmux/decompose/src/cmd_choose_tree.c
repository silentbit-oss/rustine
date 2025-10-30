static enum cmd_retval cmd_choose_tree_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct window_pane *wp = item->target.wp;
  const struct window_mode *mode;
  unsigned int mode_idx = 0;
  if (self->entry == (&cmd_choose_buffer_entry))
  {
    if (paste_get_top(0) == 0)
    {
      return CMD_RETURN_NORMAL;
    }
    mode_idx = &window_buffer_mode;
  }
  else
    if (self->entry == (&cmd_choose_client_entry))
  {
    if (server_client_how_many() == 0)
    {
      return CMD_RETURN_NORMAL;
    }
    mode_idx = &window_client_mode;
  }
  else
    mode_idx = &window_tree_mode;
  window_pane_set_mode(wp, mode, &item->target, args);
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
extern const struct cmd_entry cmd_choose_buffer_entry
----------------------------
u_int server_client_how_many(void)
{
  struct client *c;
  unsigned int c_idx = 0;
  u_int n;
  n = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if ((c->session != 0) && ((~c->flags) & 0x1000))
    {
      n += 1;
    }
  }

  return n;
}


----------------------------
extern const struct window_mode window_buffer_mode
----------------------------
extern const struct window_mode window_tree_mode
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
enum cmd_retval
{
  CMD_RETURN_ERROR = -1,
  CMD_RETURN_NORMAL = 0,
  CMD_RETURN_WAIT,
  CMD_RETURN_STOP
}
----------------------------
extern const struct cmd_entry cmd_choose_client_entry
----------------------------
None
----------------------------
extern const struct window_mode window_client_mode
----------------------------
None
----------------------------
***/


