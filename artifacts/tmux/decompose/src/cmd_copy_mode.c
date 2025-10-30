static enum cmd_retval cmd_copy_mode_exec(struct cmd *self, struct cmdq_item *item)
{
  struct args *args = self->args;
  struct cmdq_shared *shared = item->shared;
  struct client *c = item->client;
  struct session *s;
  struct window_pane *wp = item->target.wp;
  unsigned int wp_idx = 0;
  int flag;
  if (args_has(args, 'M'))
  {
    if ((wp_idx = cmd_mouse_pane(&shared->mouse, &s, 0)) == 0)
    {
      return CMD_RETURN_NORMAL;
    }
    if ((c == 0) || (c->session != s))
    {
      return CMD_RETURN_NORMAL;
    }
  }
  if (self->entry == (&cmd_clock_mode_entry))
  {
    window_pane_set_mode(wp, &window_clock_mode, 0, 0);
    return CMD_RETURN_NORMAL;
  }
  if (wp->mode != (&window_copy_mode))
  {
    flag = window_pane_set_mode(wp, &window_copy_mode, 0, 0);
    if (flag != 0)
    {
      return CMD_RETURN_NORMAL;
    }
    window_copy_init_from_pane(wp, args_has(self->args, 'e'));
  }
  if (args_has(args, 'M'))
  {
    if ((wp->mode != 0) && (wp->mode != (&window_copy_mode)))
    {
      return CMD_RETURN_NORMAL;
    }
    window_copy_start_drag(c, &shared->mouse);
  }
  if ((wp->mode == (&window_copy_mode)) && args_has(self->args, 'u'))
  {
    window_copy_pageup(wp, 0);
  }
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
extern const struct window_mode window_copy_mode
----------------------------
extern const struct cmd_entry cmd_clock_mode_entry
----------------------------
void window_copy_pageup(struct window_pane *wp, int half_page)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  u_int n;
  u_int ox;
  u_int oy;
  u_int px;
  u_int py;
  oy = (data->backing->grid->hsize + data->cy) - data->oy;
  ox = window_copy_find_length(wp, oy);
  if ((s->sel.lineflag == LINE_SEL_LEFT_RIGHT) && (oy == data->sely))
  {
    window_copy_other_end(wp);
  }
  if (data->cx != ox)
  {
    data->lastcx = data->cx;
    data->lastsx = ox;
  }
  data->cx = data->lastcx;
  n = 1;
  if (s->grid->sy > 2)
  {
    if (half_page)
    {
      n = s->grid->sy / 2;
    }
    else
      n = s->grid->sy - 2;
  }
  if ((data->oy + n) > data->backing->grid->hsize)
  {
    data->oy = data->backing->grid->hsize;
  }
  else
    data->oy += n;
  if ((!data->screen.sel.flag) || (!data->rectflag))
  {
    py = (data->backing->grid->hsize + data->cy) - data->oy;
    px = window_copy_find_length(wp, py);
    if (((data->cx >= data->lastsx) && (data->cx != px)) || (data->cx > px))
    {
      window_copy_cursor_end_of_line(wp);
    }
  }
  window_copy_update_selection(wp, 1);
  window_copy_redraw_screen(wp);
}


----------------------------
void window_copy_start_drag(struct client *c, struct mouse_event *m)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int x;
  u_int y;
  if (c == 0)
  {
    return;
  }
  wp_idx = cmd_mouse_pane(m, 0, 0);
  if (((&wp[wp_idx]) == 0) || (wp->mode != (&window_copy_mode)))
  {
    return;
  }
  if (cmd_mouse_at(wp, m, &x, &y, 1) != 0)
  {
    return;
  }
  c->tty.mouse_drag_update = window_copy_drag_update;
  c->tty.mouse_drag_release = 0;
  window_copy_update_cursor(wp, x, y);
  window_copy_start_selection(wp);
  window_copy_redraw_screen(wp);
}


----------------------------
struct window_pane *cmd_mouse_pane(struct mouse_event *m, struct session **sp, struct winlink **wlp)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  if ((wl_idx = cmd_mouse_window(m, sp)) == 0)
  {
    return 0;
  }
  if ((wp_idx = window_pane_find_by_id(m->wp_idx)) == 0)
  {
    return 0;
  }
  if (!window_has_pane(wl->window, wp))
  {
    return 0;
  }
  if (wlp != 0)
  {
    *wlp = &wl[wl_idx];
  }
  return wp;
}


----------------------------
extern const struct window_mode window_clock_mode
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
void window_copy_init_from_pane(struct window_pane *wp, int scroll_exit)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct screen_write_ctx ctx;
  u_int i;
  if (wp->mode != (&window_copy_mode))
  {
    fatalx("not in copy mode");
  }
  data->backing = &wp->base;
  data->cx = data->backing->cx;
  data->cy = data->backing->cy;
  data->scroll_exit = scroll_exit;
  s->cx = data->cx;
  s->cy = data->cy;
  screen_write_start(&ctx, 0, s);
  for (i = 0; i < s->grid->sy; i += 1)
  {
    window_copy_write_line(wp, &ctx, i);
  }

  screen_write_cursormove(&ctx, data->cx, data->cy);
  screen_write_stop(&ctx);
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


