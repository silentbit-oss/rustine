// element in merge of:  window_copy_cursor_end_of_line,window_copy_cursor_start_of_line,window_copy_cursor_down,window_copy_cursor_up
static void window_copy_cursor_end_of_line(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *back_s = data->backing;
  struct screen *s = &data->screen;
  struct grid *gd = back_s->grid;
  u_int px;
  u_int py;
  py = (back_s->grid->hsize + data->cy) - data->oy;
  px = window_copy_find_length(wp, py);
  if ((data->cx == px) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    if (data->screen.sel.flag && data->rectflag)
    {
      px = back_s->grid->sx;
    }
    if (gd->linedata[py].flags & 0x1)
    {
      while ((py < (gd->sy + gd->hsize)) && (gd->linedata[py].flags & 0x1))
      {
        window_copy_cursor_down(wp, 0);
        py = (back_s->grid->hsize + data->cy) - data->oy;
      }

      px = window_copy_find_length(wp, py);
    }
  }
  window_copy_update_cursor(wp, px, data->cy);
  if (window_copy_update_selection(wp, 1))
  {
    window_copy_redraw_lines(wp, data->cy, 1);
  }
}


/*** DEPENDENCIES:
static int window_copy_update_selection(struct window_pane *wp, int may_redraw)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct options *oo = wp->window->options;
  struct grid_cell gc;
  u_int sx;
  u_int sy;
  u_int cy;
  u_int endsx;
  u_int endsy;
  int startrelpos;
  int endrelpos;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return 0;
  }
  window_copy_synchronize_cursor(wp);
  sx = data->selx;
  sy = data->sely;
  startrelpos = window_copy_adjust_selection(wp, &sx, &sy);
  endsx = data->endselx;
  endsy = data->endsely;
  endrelpos = window_copy_adjust_selection(wp, &endsx, &endsy);
  if ((startrelpos == endrelpos) && (startrelpos != WINDOW_COPY_REL_POS_ON_SCREEN))
  {
    screen_hide_selection(s);
    return 0;
  }
  style_apply(&gc, oo, "mode-style");
  gc.flags |= 0x20;
  screen_set_selection(s, sx, sy, endsx, endsy, data->rectflag, &gc);
  if (data->rectflag && may_redraw)
  {
    cy = data->cy;
    if (data->cursordrag == CURSORDRAG_ENDSEL)
    {
      if (sy < cy)
      {
        window_copy_redraw_lines(wp, sy, (cy - sy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (sy - cy) + 1);
    }
    else
    {
      if (endsy < cy)
      {
        window_copy_redraw_lines(wp, endsy, (cy - endsy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (endsy - cy) + 1);
    }
  }
  return 1;
}


----------------------------
static u_int window_copy_find_length(struct window_pane *wp, u_int py)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = data->backing;
  struct grid_cell gc;
  u_int px;
  px = s->grid->linedata[py].cellsize;
  if (px > s->grid->sx)
  {
    px = s->grid->sx;
  }
  while (px > 0)
  {
    grid_get_cell(s->grid, px - 1, py, &gc);
    if ((gc.data.size != 1) || ((*gc.data.data) != ' '))
    {
      break;
    }
    px -= 1;
  }

  return px;
}


----------------------------
static void window_copy_redraw_lines(struct window_pane *wp, u_int py, u_int ny)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen_write_ctx ctx;
  u_int i;
  screen_write_start(&ctx, wp, 0);
  for (i = py; i < (py + ny); i += 1)
  {
    window_copy_write_line(wp, &ctx, i);
  }

  screen_write_cursormove(&ctx, data->cx, data->cy);
  screen_write_stop(&ctx);
}


----------------------------
None
----------------------------
None
----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
None
----------------------------
static void window_copy_update_cursor(struct window_pane *wp, u_int cx, u_int cy)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct screen_write_ctx ctx;
  u_int old_cx;
  u_int old_cy;
  old_cx = data->cx;
  old_cy = data->cy;
  data->cx = cx;
  data->cy = cy;
  if (old_cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, old_cy, 1);
  }
  if (data->cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, data->cy, 1);
  }
  else
  {
    screen_write_start(&ctx, wp, 0);
    screen_write_cursormove(&ctx, data->cx, data->cy);
    screen_write_stop(&ctx);
  }
}


----------------------------
None
----------------------------
***/


// element in merge of:  window_copy_cursor_end_of_line,window_copy_cursor_start_of_line,window_copy_cursor_down,window_copy_cursor_up
static void window_copy_cursor_start_of_line(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *back_s = data->backing;
  struct screen *s = &data->screen;
  struct grid *gd = back_s->grid;
  u_int py;
  if ((data->cx == 0) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    py = (back_s->grid->hsize + data->cy) - data->oy;
    while ((py > 0) && (gd->linedata[py - 1].flags & 0x1))
    {
      window_copy_cursor_up(wp, 0);
      py = (back_s->grid->hsize + data->cy) - data->oy;
    }

  }
  window_copy_update_cursor(wp, 0, data->cy);
  if (window_copy_update_selection(wp, 1))
  {
    window_copy_redraw_lines(wp, data->cy, 1);
  }
}


/*** DEPENDENCIES:
static int window_copy_update_selection(struct window_pane *wp, int may_redraw)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct options *oo = wp->window->options;
  struct grid_cell gc;
  u_int sx;
  u_int sy;
  u_int cy;
  u_int endsx;
  u_int endsy;
  int startrelpos;
  int endrelpos;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return 0;
  }
  window_copy_synchronize_cursor(wp);
  sx = data->selx;
  sy = data->sely;
  startrelpos = window_copy_adjust_selection(wp, &sx, &sy);
  endsx = data->endselx;
  endsy = data->endsely;
  endrelpos = window_copy_adjust_selection(wp, &endsx, &endsy);
  if ((startrelpos == endrelpos) && (startrelpos != WINDOW_COPY_REL_POS_ON_SCREEN))
  {
    screen_hide_selection(s);
    return 0;
  }
  style_apply(&gc, oo, "mode-style");
  gc.flags |= 0x20;
  screen_set_selection(s, sx, sy, endsx, endsy, data->rectflag, &gc);
  if (data->rectflag && may_redraw)
  {
    cy = data->cy;
    if (data->cursordrag == CURSORDRAG_ENDSEL)
    {
      if (sy < cy)
      {
        window_copy_redraw_lines(wp, sy, (cy - sy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (sy - cy) + 1);
    }
    else
    {
      if (endsy < cy)
      {
        window_copy_redraw_lines(wp, endsy, (cy - endsy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (endsy - cy) + 1);
    }
  }
  return 1;
}


----------------------------
static void window_copy_redraw_lines(struct window_pane *wp, u_int py, u_int ny)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen_write_ctx ctx;
  u_int i;
  screen_write_start(&ctx, wp, 0);
  for (i = py; i < (py + ny); i += 1)
  {
    window_copy_write_line(wp, &ctx, i);
  }

  screen_write_cursormove(&ctx, data->cx, data->cy);
  screen_write_stop(&ctx);
}


----------------------------
None
----------------------------
None
----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
None
----------------------------
static void window_copy_update_cursor(struct window_pane *wp, u_int cx, u_int cy)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct screen_write_ctx ctx;
  u_int old_cx;
  u_int old_cy;
  old_cx = data->cx;
  old_cy = data->cy;
  data->cx = cx;
  data->cy = cy;
  if (old_cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, old_cy, 1);
  }
  if (data->cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, data->cy, 1);
  }
  else
  {
    screen_write_start(&ctx, wp, 0);
    screen_write_cursormove(&ctx, data->cx, data->cy);
    screen_write_stop(&ctx);
  }
}


----------------------------
None
----------------------------
***/


// element in merge of:  window_copy_cursor_end_of_line,window_copy_cursor_start_of_line,window_copy_cursor_down,window_copy_cursor_up
static void window_copy_cursor_down(struct window_pane *wp, int scroll_only)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  u_int ox;
  u_int oy;
  u_int px;
  u_int py;
  oy = (data->backing->grid->hsize + data->cy) - data->oy;
  ox = window_copy_find_length(wp, oy);
  if (data->cx != ox)
  {
    data->lastcx = data->cx;
    data->lastsx = ox;
  }
  if ((s->sel.lineflag == LINE_SEL_RIGHT_LEFT) && (oy == data->endsely))
  {
    window_copy_other_end(wp);
  }
  data->cx = data->lastcx;
  if (scroll_only || (data->cy == (s->grid->sy - 1)))
  {
    window_copy_scroll_up(wp, 1);
    if (scroll_only && (data->cy > 0))
    {
      window_copy_redraw_lines(wp, data->cy - 1, 2);
    }
  }
  else
  {
    window_copy_update_cursor(wp, data->cx, data->cy + 1);
    if (window_copy_update_selection(wp, 1))
    {
      window_copy_redraw_lines(wp, data->cy - 1, 2);
    }
  }
  if ((!data->screen.sel.flag) || (!data->rectflag))
  {
    py = (data->backing->grid->hsize + data->cy) - data->oy;
    px = window_copy_find_length(wp, py);
    if (((data->cx >= data->lastsx) && (data->cx != px)) || (data->cx > px))
    {
      window_copy_cursor_end_of_line(wp);
    }
  }
  if (s->sel.lineflag == LINE_SEL_LEFT_RIGHT)
  {
    window_copy_cursor_end_of_line(wp);
  }
  else
    if (s->sel.lineflag == LINE_SEL_RIGHT_LEFT)
  {
    window_copy_cursor_start_of_line(wp);
  }
}


/*** DEPENDENCIES:
static int window_copy_update_selection(struct window_pane *wp, int may_redraw)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct options *oo = wp->window->options;
  struct grid_cell gc;
  u_int sx;
  u_int sy;
  u_int cy;
  u_int endsx;
  u_int endsy;
  int startrelpos;
  int endrelpos;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return 0;
  }
  window_copy_synchronize_cursor(wp);
  sx = data->selx;
  sy = data->sely;
  startrelpos = window_copy_adjust_selection(wp, &sx, &sy);
  endsx = data->endselx;
  endsy = data->endsely;
  endrelpos = window_copy_adjust_selection(wp, &endsx, &endsy);
  if ((startrelpos == endrelpos) && (startrelpos != WINDOW_COPY_REL_POS_ON_SCREEN))
  {
    screen_hide_selection(s);
    return 0;
  }
  style_apply(&gc, oo, "mode-style");
  gc.flags |= 0x20;
  screen_set_selection(s, sx, sy, endsx, endsy, data->rectflag, &gc);
  if (data->rectflag && may_redraw)
  {
    cy = data->cy;
    if (data->cursordrag == CURSORDRAG_ENDSEL)
    {
      if (sy < cy)
      {
        window_copy_redraw_lines(wp, sy, (cy - sy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (sy - cy) + 1);
    }
    else
    {
      if (endsy < cy)
      {
        window_copy_redraw_lines(wp, endsy, (cy - endsy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (endsy - cy) + 1);
    }
  }
  return 1;
}


----------------------------
static void window_copy_other_end(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  u_int selx;
  u_int sely;
  u_int cy;
  u_int yy;
  u_int hsize;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return;
  }
  if (s->sel.lineflag == LINE_SEL_LEFT_RIGHT)
  {
    s->sel.lineflag = LINE_SEL_RIGHT_LEFT;
  }
  else
    if (s->sel.lineflag == LINE_SEL_RIGHT_LEFT)
  {
    s->sel.lineflag = LINE_SEL_LEFT_RIGHT;
  }
  switch (data->cursordrag)
  {
    case CURSORDRAG_NONE:

    case CURSORDRAG_SEL:
    {
      data->cursordrag = CURSORDRAG_ENDSEL;
      break;
    }

    case CURSORDRAG_ENDSEL:
    {
      data->cursordrag = CURSORDRAG_SEL;
      break;
    }

  }

  selx = data->endselx;
  sely = data->endsely;
  if (data->cursordrag == CURSORDRAG_SEL)
  {
    selx = data->selx;
    sely = data->sely;
  }
  cy = data->cy;
  yy = (data->backing->grid->hsize + data->cy) - data->oy;
  data->cx = selx;
  hsize = data->backing->grid->hsize;
  if (sely < (hsize - data->oy))
  {
    data->oy = hsize - sely;
    data->cy = 0;
  }
  else
    if (sely > ((hsize - data->oy) + s->grid->sy))
  {
    data->oy = ((hsize - sely) + s->grid->sy) - 1;
    data->cy = s->grid->sy - 1;
  }
  else
    data->cy = (cy + sely) - yy;
  window_copy_update_selection(wp, 1);
  window_copy_redraw_screen(wp);
}


----------------------------
static u_int window_copy_find_length(struct window_pane *wp, u_int py)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = data->backing;
  struct grid_cell gc;
  u_int px;
  px = s->grid->linedata[py].cellsize;
  if (px > s->grid->sx)
  {
    px = s->grid->sx;
  }
  while (px > 0)
  {
    grid_get_cell(s->grid, px - 1, py, &gc);
    if ((gc.data.size != 1) || ((*gc.data.data) != ' '))
    {
      break;
    }
    px -= 1;
  }

  return px;
}


----------------------------
static void window_copy_scroll_up(struct window_pane *wp, u_int ny)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct screen_write_ctx ctx;
  if (data->oy < ny)
  {
    ny = data->oy;
  }
  if (ny == 0)
  {
    return;
  }
  data->oy -= ny;
  window_copy_update_selection(wp, 0);
  screen_write_start(&ctx, wp, 0);
  screen_write_cursormove(&ctx, 0, 0);
  screen_write_deleteline(&ctx, ny, 8);
  window_copy_write_lines(wp, &ctx, s->grid->sy - ny, ny);
  window_copy_write_line(wp, &ctx, 0);
  if (s->grid->sy > 1)
  {
    window_copy_write_line(wp, &ctx, 1);
  }
  if (s->grid->sy > 3)
  {
    window_copy_write_line(wp, &ctx, s->grid->sy - 2);
  }
  if (s->sel.flag && (s->grid->sy > ny))
  {
    window_copy_write_line(wp, &ctx, (s->grid->sy - ny) - 1);
  }
  screen_write_cursormove(&ctx, data->cx, data->cy);
  screen_write_stop(&ctx);
}


----------------------------
static void window_copy_redraw_lines(struct window_pane *wp, u_int py, u_int ny)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen_write_ctx ctx;
  u_int i;
  screen_write_start(&ctx, wp, 0);
  for (i = py; i < (py + ny); i += 1)
  {
    window_copy_write_line(wp, &ctx, i);
  }

  screen_write_cursormove(&ctx, data->cx, data->cy);
  screen_write_stop(&ctx);
}


----------------------------
None
----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
None
----------------------------
static void window_copy_update_cursor(struct window_pane *wp, u_int cx, u_int cy)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct screen_write_ctx ctx;
  u_int old_cx;
  u_int old_cy;
  old_cx = data->cx;
  old_cy = data->cy;
  data->cx = cx;
  data->cy = cy;
  if (old_cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, old_cy, 1);
  }
  if (data->cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, data->cy, 1);
  }
  else
  {
    screen_write_start(&ctx, wp, 0);
    screen_write_cursormove(&ctx, data->cx, data->cy);
    screen_write_stop(&ctx);
  }
}


----------------------------
None
----------------------------
***/


// element in merge of:  window_copy_cursor_end_of_line,window_copy_cursor_start_of_line,window_copy_cursor_down,window_copy_cursor_up
static void window_copy_cursor_up(struct window_pane *wp, int scroll_only)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  u_int ox;
  u_int oy;
  u_int px;
  u_int py;
  oy = (data->backing->grid->hsize + data->cy) - data->oy;
  ox = window_copy_find_length(wp, oy);
  if (data->cx != ox)
  {
    data->lastcx = data->cx;
    data->lastsx = ox;
  }
  if ((s->sel.lineflag == LINE_SEL_LEFT_RIGHT) && (oy == data->sely))
  {
    window_copy_other_end(wp);
  }
  data->cx = data->lastcx;
  if (scroll_only || (data->cy == 0))
  {
    window_copy_scroll_down(wp, 1);
    if (scroll_only)
    {
      if (data->cy == (s->grid->sy - 1))
      {
        window_copy_redraw_lines(wp, data->cy, 1);
      }
      else
        window_copy_redraw_lines(wp, data->cy, 2);
    }
  }
  else
  {
    window_copy_update_cursor(wp, data->cx, data->cy - 1);
    if (window_copy_update_selection(wp, 1))
    {
      if (data->cy == (s->grid->sy - 1))
      {
        window_copy_redraw_lines(wp, data->cy, 1);
      }
      else
        window_copy_redraw_lines(wp, data->cy, 2);
    }
  }
  if ((!data->screen.sel.flag) || (!data->rectflag))
  {
    py = (data->backing->grid->hsize + data->cy) - data->oy;
    px = window_copy_find_length(wp, py);
    if (((data->cx >= data->lastsx) && (data->cx != px)) || (data->cx > px))
    {
      window_copy_cursor_end_of_line(wp);
    }
  }
  if (s->sel.lineflag == LINE_SEL_LEFT_RIGHT)
  {
    window_copy_cursor_end_of_line(wp);
  }
  else
    if (s->sel.lineflag == LINE_SEL_RIGHT_LEFT)
  {
    window_copy_cursor_start_of_line(wp);
  }
}


/*** DEPENDENCIES:
static int window_copy_update_selection(struct window_pane *wp, int may_redraw)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct options *oo = wp->window->options;
  struct grid_cell gc;
  u_int sx;
  u_int sy;
  u_int cy;
  u_int endsx;
  u_int endsy;
  int startrelpos;
  int endrelpos;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return 0;
  }
  window_copy_synchronize_cursor(wp);
  sx = data->selx;
  sy = data->sely;
  startrelpos = window_copy_adjust_selection(wp, &sx, &sy);
  endsx = data->endselx;
  endsy = data->endsely;
  endrelpos = window_copy_adjust_selection(wp, &endsx, &endsy);
  if ((startrelpos == endrelpos) && (startrelpos != WINDOW_COPY_REL_POS_ON_SCREEN))
  {
    screen_hide_selection(s);
    return 0;
  }
  style_apply(&gc, oo, "mode-style");
  gc.flags |= 0x20;
  screen_set_selection(s, sx, sy, endsx, endsy, data->rectflag, &gc);
  if (data->rectflag && may_redraw)
  {
    cy = data->cy;
    if (data->cursordrag == CURSORDRAG_ENDSEL)
    {
      if (sy < cy)
      {
        window_copy_redraw_lines(wp, sy, (cy - sy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (sy - cy) + 1);
    }
    else
    {
      if (endsy < cy)
      {
        window_copy_redraw_lines(wp, endsy, (cy - endsy) + 1);
      }
      else
        window_copy_redraw_lines(wp, cy, (endsy - cy) + 1);
    }
  }
  return 1;
}


----------------------------
static void window_copy_other_end(struct window_pane *wp)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  u_int selx;
  u_int sely;
  u_int cy;
  u_int yy;
  u_int hsize;
  if ((!s->sel.flag) && (s->sel.lineflag == LINE_SEL_NONE))
  {
    return;
  }
  if (s->sel.lineflag == LINE_SEL_LEFT_RIGHT)
  {
    s->sel.lineflag = LINE_SEL_RIGHT_LEFT;
  }
  else
    if (s->sel.lineflag == LINE_SEL_RIGHT_LEFT)
  {
    s->sel.lineflag = LINE_SEL_LEFT_RIGHT;
  }
  switch (data->cursordrag)
  {
    case CURSORDRAG_NONE:

    case CURSORDRAG_SEL:
    {
      data->cursordrag = CURSORDRAG_ENDSEL;
      break;
    }

    case CURSORDRAG_ENDSEL:
    {
      data->cursordrag = CURSORDRAG_SEL;
      break;
    }

  }

  selx = data->endselx;
  sely = data->endsely;
  if (data->cursordrag == CURSORDRAG_SEL)
  {
    selx = data->selx;
    sely = data->sely;
  }
  cy = data->cy;
  yy = (data->backing->grid->hsize + data->cy) - data->oy;
  data->cx = selx;
  hsize = data->backing->grid->hsize;
  if (sely < (hsize - data->oy))
  {
    data->oy = hsize - sely;
    data->cy = 0;
  }
  else
    if (sely > ((hsize - data->oy) + s->grid->sy))
  {
    data->oy = ((hsize - sely) + s->grid->sy) - 1;
    data->cy = s->grid->sy - 1;
  }
  else
    data->cy = (cy + sely) - yy;
  window_copy_update_selection(wp, 1);
  window_copy_redraw_screen(wp);
}


----------------------------
static u_int window_copy_find_length(struct window_pane *wp, u_int py)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = data->backing;
  struct grid_cell gc;
  u_int px;
  px = s->grid->linedata[py].cellsize;
  if (px > s->grid->sx)
  {
    px = s->grid->sx;
  }
  while (px > 0)
  {
    grid_get_cell(s->grid, px - 1, py, &gc);
    if ((gc.data.size != 1) || ((*gc.data.data) != ' '))
    {
      break;
    }
    px -= 1;
  }

  return px;
}


----------------------------
static void window_copy_redraw_lines(struct window_pane *wp, u_int py, u_int ny)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen_write_ctx ctx;
  u_int i;
  screen_write_start(&ctx, wp, 0);
  for (i = py; i < (py + ny); i += 1)
  {
    window_copy_write_line(wp, &ctx, i);
  }

  screen_write_cursormove(&ctx, data->cx, data->cy);
  screen_write_stop(&ctx);
}


----------------------------
None
----------------------------
struct window_copy_mode_data
{
  struct screen screen;
  struct screen *backing;
  int backing_written;
  u_int oy;
  u_int selx;
  u_int sely;
  u_int endselx;
  u_int endsely;
  enum 
  {
    CURSORDRAG_NONE,
    CURSORDRAG_ENDSEL,
    CURSORDRAG_SEL
  } cursordrag;
  int rectflag;
  int scroll_exit;
  u_int cx;
  u_int cy;
  u_int lastcx;
  u_int lastsx;
  int searchtype;
  char *searchstr;
  bitstr_t *searchmark;
  u_int searchcount;
  int searchthis;
  int searchx;
  int searchy;
  int searcho;
  int jumptype;
  char jumpchar;
}
----------------------------
static void window_copy_scroll_down(struct window_pane *wp, u_int ny)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct screen_write_ctx ctx;
  if (ny > data->backing->grid->hsize)
  {
    return;
  }
  if (data->oy > (data->backing->grid->hsize - ny))
  {
    ny = data->backing->grid->hsize - data->oy;
  }
  if (ny == 0)
  {
    return;
  }
  data->oy += ny;
  window_copy_update_selection(wp, 0);
  screen_write_start(&ctx, wp, 0);
  screen_write_cursormove(&ctx, 0, 0);
  screen_write_insertline(&ctx, ny, 8);
  window_copy_write_lines(wp, &ctx, 0, ny);
  if (s->sel.flag && (s->grid->sy > ny))
  {
    window_copy_write_line(wp, &ctx, ny);
  }
  else
    if (ny == 1)
  {
    window_copy_write_line(wp, &ctx, 1);
  }
  screen_write_cursormove(&ctx, data->cx, data->cy);
  screen_write_stop(&ctx);
}


----------------------------
None
----------------------------
static void window_copy_update_cursor(struct window_pane *wp, u_int cx, u_int cy)
{
  struct window_copy_mode_data *data = wp->modedata;
  struct screen *s = &data->screen;
  struct screen_write_ctx ctx;
  u_int old_cx;
  u_int old_cy;
  old_cx = data->cx;
  old_cy = data->cy;
  data->cx = cx;
  data->cy = cy;
  if (old_cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, old_cy, 1);
  }
  if (data->cx == s->grid->sx)
  {
    window_copy_redraw_lines(wp, data->cy, 1);
  }
  else
  {
    screen_write_start(&ctx, wp, 0);
    screen_write_cursormove(&ctx, data->cx, data->cy);
    screen_write_stop(&ctx);
  }
}


----------------------------
None
----------------------------
***/


