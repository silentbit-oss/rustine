static int window_tree_cmp_session_name(const void *a0, const void *b0)
{
  const struct session * const *a = a0;
  const struct session * const *b = b0;
  return strcmp((*a)->name, (*b)->name);
}


/*** DEPENDENCIES:
None
----------------------------
***/


static int window_tree_cmp_session_time(const void *a0, const void *b0)
{
  const struct session * const *a = a0;
  const struct session * const *b = b0;
  if (((&(*a)->activity_time)->tv_sec == (&(*b)->activity_time)->tv_sec) ? ((&(*a)->activity_time)->tv_usec > (&(*b)->activity_time)->tv_usec) : ((&(*a)->activity_time)->tv_sec > (&(*b)->activity_time)->tv_sec))
  {
    return -1;
  }
  if (((&(*a)->activity_time)->tv_sec == (&(*b)->activity_time)->tv_sec) ? ((&(*a)->activity_time)->tv_usec < (&(*b)->activity_time)->tv_usec) : ((&(*a)->activity_time)->tv_sec < (&(*b)->activity_time)->tv_sec))
  {
    return 1;
  }
  return strcmp((*a)->name, (*b)->name);
}


/*** DEPENDENCIES:
None
----------------------------
***/


static int window_tree_cmp_window_name(const void *a0, const void *b0)
{
  const struct winlink * const *a = a0;
  const struct winlink * const *b = b0;
  return strcmp((*a)->window->name, (*b)->window->name);
}


/*** DEPENDENCIES:
None
----------------------------
***/


static int window_tree_cmp_window_time(const void *a0, const void *b0)
{
  const struct winlink * const *a = a0;
  const struct winlink * const *b = b0;
  if (((&(*a)->window->activity_time)->tv_sec == (&(*b)->window->activity_time)->tv_sec) ? ((&(*a)->window->activity_time)->tv_usec > (&(*b)->window->activity_time)->tv_usec) : ((&(*a)->window->activity_time)->tv_sec > (&(*b)->window->activity_time)->tv_sec))
  {
    return -1;
  }
  if (((&(*a)->window->activity_time)->tv_sec == (&(*b)->window->activity_time)->tv_sec) ? ((&(*a)->window->activity_time)->tv_usec < (&(*b)->window->activity_time)->tv_usec) : ((&(*a)->window->activity_time)->tv_sec < (&(*b)->window->activity_time)->tv_sec))
  {
    return 1;
  }
  return strcmp((*a)->window->name, (*b)->window->name);
}


/*** DEPENDENCIES:
None
----------------------------
***/


static void window_tree_free_item(struct window_tree_itemdata *item)
{
  free(item);
}


/*** DEPENDENCIES:
struct window_tree_itemdata
{
  enum window_tree_type type;
  int session;
  int winlink;
  int pane;
}
----------------------------
None
----------------------------
***/


static int window_tree_cmp_pane_time(const void *a0, const void *b0)
{
  const struct window_pane * const *a = a0;
  const struct window_pane * const *b = b0;
  if ((*a)->active_point < (*b)->active_point)
  {
    return -1;
  }
  if ((*a)->active_point > (*b)->active_point)
  {
    return 1;
  }
  return 0;
}


/*** DEPENDENCIES:
None
----------------------------
***/


static void window_tree_destroy(struct window_tree_modedata *data)
{
  u_int i;
  if ((--data->references) != 0)
  {
    return;
  }
  for (i = 0; i < data->item_size; i += 1)
  {
    window_tree_free_item(data->item_list[i]);
  }

  free(data->item_list);
  free(data->format);
  free(data->command);
  free(data);
}


/*** DEPENDENCIES:
static void window_tree_free_item(struct window_tree_itemdata *item)
{
  free(item);
}


----------------------------
struct window_tree_modedata
{
  struct window_pane *wp;
  int dead;
  int references;
  struct mode_tree_data *data;
  char *format;
  char *command;
  int squash_groups;
  struct window_tree_itemdata **item_list;
  u_int item_size;
  const char *entered;
  struct cmd_find_state fs;
  enum window_tree_type type;
  int offset;
  int left;
  int right;
  u_int start;
  u_int end;
  u_int each;
}
----------------------------
None
----------------------------
***/


static void window_tree_command_free(void *modedata)
{
  struct window_tree_modedata *data = modedata;
  window_tree_destroy(data);
}


/*** DEPENDENCIES:
static void window_tree_destroy(struct window_tree_modedata *data)
{
  u_int i;
  if ((--data->references) != 0)
  {
    return;
  }
  for (i = 0; i < data->item_size; i += 1)
  {
    window_tree_free_item(data->item_list[i]);
  }

  free(data->item_list);
  free(data->format);
  free(data->command);
  free(data);
}


----------------------------
struct window_tree_modedata
{
  struct window_pane *wp;
  int dead;
  int references;
  struct mode_tree_data *data;
  char *format;
  char *command;
  int squash_groups;
  struct window_tree_itemdata **item_list;
  u_int item_size;
  const char *entered;
  struct cmd_find_state fs;
  enum window_tree_type type;
  int offset;
  int left;
  int right;
  u_int start;
  u_int end;
  u_int each;
}
----------------------------
None
----------------------------
***/


static void window_tree_resize(struct window_pane *wp, u_int sx, u_int sy)
{
  struct window_tree_modedata *data = wp->modedata;
  mode_tree_resize(data->data, sx, sy);
}


/*** DEPENDENCIES:
void mode_tree_resize(struct mode_tree_data *mtd, u_int sx, u_int sy)
{
  struct screen *s = &mtd->screen;
  screen_resize(s, sx, sy, 0);
  mode_tree_build(mtd);
  mode_tree_draw(mtd);
  mtd->wp->flags |= 0x1;
}


----------------------------
struct window_tree_modedata
{
  struct window_pane *wp;
  int dead;
  int references;
  struct mode_tree_data *data;
  char *format;
  char *command;
  int squash_groups;
  struct window_tree_itemdata **item_list;
  u_int item_size;
  const char *entered;
  struct cmd_find_state fs;
  enum window_tree_type type;
  int offset;
  int left;
  int right;
  u_int start;
  u_int end;
  u_int each;
}
----------------------------
None
----------------------------
***/


static void window_tree_free(struct window_pane *wp)
{
  struct window_tree_modedata *data = wp->modedata;
  if (data == 0)
  {
    return;
  }
  data->dead = 1;
  mode_tree_free(data->data);
  window_tree_destroy(data);
}


/*** DEPENDENCIES:
static void window_tree_destroy(struct window_tree_modedata *data)
{
  u_int i;
  if ((--data->references) != 0)
  {
    return;
  }
  for (i = 0; i < data->item_size; i += 1)
  {
    window_tree_free_item(data->item_list[i]);
  }

  free(data->item_list);
  free(data->format);
  free(data->command);
  free(data);
}


----------------------------
void mode_tree_free(struct mode_tree_data *mtd)
{
  struct window_pane *wp = mtd->wp;
  if (mtd->zoomed == 0)
  {
    server_unzoom_window(wp->window);
  }
  mode_tree_free_items(&mtd->children);
  mode_tree_clear_lines(mtd);
  screen_free(&mtd->screen);
  free(mtd->search);
  free(mtd->filter);
  mtd->dead = 1;
  mode_tree_remove_ref(mtd);
}


----------------------------
struct window_tree_modedata
{
  struct window_pane *wp;
  int dead;
  int references;
  struct mode_tree_data *data;
  char *format;
  char *command;
  int squash_groups;
  struct window_tree_itemdata **item_list;
  u_int item_size;
  const char *entered;
  struct cmd_find_state fs;
  enum window_tree_type type;
  int offset;
  int left;
  int right;
  u_int start;
  u_int end;
  u_int each;
}
----------------------------
None
----------------------------
***/


static struct window_tree_itemdata *window_tree_add_item(struct window_tree_modedata *data)
{
  struct window_tree_itemdata *item;
  unsigned int item_idx = 0;
  data->item_list = xreallocarray(data->item_list, data->item_size + 1, sizeof(*data->item_list));
  item_idx = (data->item_list[data->item_size++] = xcalloc(1, sizeof(*item_idx)));
  return item;
}


/*** DEPENDENCIES:
void *xreallocarray(void *ptr, size_t nmemb, size_t size)
{
  void *new_ptr;
  unsigned int new_ptr_idx = 0;
  if ((nmemb == 0) || (size == 0))
  {
    fatalx("xreallocarray: zero size");
  }
  new_ptr_idx = reallocarray(ptr, nmemb, size);
  if ((&new_ptr[new_ptr_idx]) == 0)
  {
    fatalx("xreallocarray: allocating %zu * %zu bytes: %s", nmemb, size, strerror(errno));
  }
  return new_ptr;
}


----------------------------
struct window_tree_itemdata
{
  enum window_tree_type type;
  int session;
  int winlink;
  int pane;
}
----------------------------
struct window_tree_modedata
{
  struct window_pane *wp;
  int dead;
  int references;
  struct mode_tree_data *data;
  char *format;
  char *command;
  int squash_groups;
  struct window_tree_itemdata **item_list;
  u_int item_size;
  const char *entered;
  struct cmd_find_state fs;
  enum window_tree_type type;
  int offset;
  int left;
  int right;
  u_int start;
  u_int end;
  u_int each;
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
None
----------------------------
***/


static int window_tree_filter_pane(struct session *s, struct winlink *wl, struct window_pane *wp, const char *filter)
{
  char *cp;
  unsigned int cp_idx = 0;
  int result;
  if (filter == 0)
  {
    return 1;
  }
  cp_idx = format_single(0, filter, 0, s, wl, wp);
  result = format_true(cp);
  free(cp);
  return result;
}


/*** DEPENDENCIES:
char *format_single(struct cmdq_item *item, const char *fmt, struct client *c, struct session *s, struct winlink *wl, struct window_pane *wp)
{
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  char *expanded;
  unsigned int expanded_idx = 0;
  if (item != 0)
  {
    ft_idx = format_create(item->client, item, 0, 0);
  }
  else
    ft_idx = format_create(0, item, 0, 0);
  format_defaults(ft, c, s, wl, wp);
  expanded_idx = format_expand(ft, fmt);
  format_free(ft);
  return expanded;
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
None
----------------------------
***/


// hint:  ['wp_idx_ref is a mutable refrence to unsigned int', 'loop_ref is a mutable refrence to u_int']
key_code helper_window_tree_mouse_2(unsigned int * const wp_idx_ref, u_int * const loop_ref, struct window_tree_modedata * const data, u_int x, struct winlink * const wl, unsigned int wl_idx, struct window_pane * const wp)
{
  unsigned int wp_idx = *wp_idx_ref;
  u_int loop = *loop_ref;
  if ((&wl[wl_idx]) == 0)
  {
    return 0xffff00000000ULL;
  }
  mode_tree_expand_current(data->data);
  loop = 0;
  for (wp_idx = (&wl->window->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    if (loop == (data->start + x))
    {
      break;
    }
    loop += 1;
  }

  if ((&wp[wp_idx]) != 0)
  {
    mode_tree_set_current(data->data, (uint64_t) wp);
  }
  return '\r';
  *wp_idx_ref = wp_idx;
  *loop_ref = loop;
}


/*** DEPENDENCIES:
void mode_tree_expand_current(struct mode_tree_data *mtd)
{
  if (!mtd->line_list[mtd->current].item->expanded)
  {
    mtd->line_list[mtd->current].item->expanded = 1;
    mode_tree_build(mtd);
  }
}


----------------------------
struct window_tree_modedata
{
  struct window_pane *wp;
  int dead;
  int references;
  struct mode_tree_data *data;
  char *format;
  char *command;
  int squash_groups;
  struct window_tree_itemdata **item_list;
  u_int item_size;
  const char *entered;
  struct cmd_find_state fs;
  enum window_tree_type type;
  int offset;
  int left;
  int right;
  u_int start;
  u_int end;
  u_int each;
}
----------------------------
void mode_tree_set_current(struct mode_tree_data *mtd, uint64_t tag)
{
  u_int i;
  for (i = 0; i < mtd->line_size; i += 1)
  {
    if (mtd->line_list[i].item->tag == tag)
    {
      break;
    }
  }

  if (i != mtd->line_size)
  {
    mtd->current = i;
    if (mtd->current > (mtd->height - 1))
    {
      mtd->offset = (mtd->current - mtd->height) + 1;
    }
    else
      mtd->offset = 0;
  }
  else
  {
    mtd->current = 0;
    mtd->offset = 0;
  }
}


----------------------------
None
----------------------------
***/


static void window_tree_draw_label(struct screen_write_ctx *ctx, u_int px, u_int py, u_int sx, u_int sy, const struct grid_cell *gc, const char *label)
{
  size_t len;
  u_int ox;
  u_int oy;
  len = strlen(label);
  if (((sx == 0) || (sy == 1)) || (len > sx))
  {
    return;
  }
  ox = ((sx - len) + 1) / 2;
  oy = (sy + 1) / 2;
  if (((ox > 1) && ((ox + len) < (sx - 1))) && (sy >= 3))
  {
    screen_write_cursormove(ctx, (px + ox) - 1, (py + oy) - 1);
    screen_write_box(ctx, len + 2, 3);
  }
  screen_write_cursormove(ctx, px + ox, py + oy);
  screen_write_puts(ctx, gc, "%s", label);
}


/*** DEPENDENCIES:
void screen_write_cursormove(struct screen_write_ctx *ctx, u_int px, u_int py)
{
  struct screen *s = ctx->s;
  if (px > (s->grid->sx - 1))
  {
    px = s->grid->sx - 1;
  }
  if (py > (s->grid->sy - 1))
  {
    py = s->grid->sy - 1;
  }
  s->cx = px;
  s->cy = py;
}


----------------------------
None
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
void screen_write_puts(struct screen_write_ctx *ctx, const struct grid_cell *gcp, const char *fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  screen_write_vnputs(ctx, -1, gcp, fmt, ap);
  ;
}


----------------------------
void screen_write_box(struct screen_write_ctx *ctx, u_int nx, u_int ny)
{
  struct screen *s = ctx->s;
  struct grid_cell gc;
  u_int cx;
  u_int cy;
  u_int i;
  cx = s->cx;
  cy = s->cy;
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  gc.attr |= 0x80;
  screen_write_putc(ctx, &gc, 'l');
  for (i = 1; i < (nx - 1); i += 1)
  {
    screen_write_putc(ctx, &gc, 'q');
  }

  screen_write_putc(ctx, &gc, 'k');
  screen_write_cursormove(ctx, cx, (cy + ny) - 1);
  screen_write_putc(ctx, &gc, 'm');
  for (i = 1; i < (nx - 1); i += 1)
  {
    screen_write_putc(ctx, &gc, 'q');
  }

  screen_write_putc(ctx, &gc, 'j');
  for (i = 1; i < (ny - 1); i += 1)
  {
    screen_write_cursormove(ctx, cx, cy + i);
    screen_write_putc(ctx, &gc, 'x');
  }

  for (i = 1; i < (ny - 1); i += 1)
  {
    screen_write_cursormove(ctx, (cx + nx) - 1, cy + i);
    screen_write_putc(ctx, &gc, 'x');
  }

  screen_write_cursormove(ctx, cx, cy);
}


----------------------------
None
----------------------------
None
----------------------------
***/


static void window_tree_pull_item(struct window_tree_itemdata *item, struct session **sp, struct winlink **wlp, struct window_pane **wp)
{
  *wp = 0;
  *wlp = 0;
  *sp = session_find_by_id(item->session);
  if ((*sp) == 0)
  {
    return;
  }
  if (item->type == WINDOW_TREE_SESSION)
  {
    *wlp = (*sp)->curw;
    *wp = (*wlp)->window->active;
    return;
  }
  *wlp = winlink_find_by_index(&(*sp)->windows, item->winlink);
  if ((*wlp) == 0)
  {
    *sp = 0;
    return;
  }
  if (item->type == WINDOW_TREE_WINDOW)
  {
    *wp = (*wlp)->window->active;
    return;
  }
  *wp = window_pane_find_by_id(item->pane);
  if (!window_has_pane((*wlp)->window, *wp))
  {
    *wp = 0;
  }
  if ((*wp) == 0)
  {
    *sp = 0;
    *wlp = 0;
    return;
  }
}


/*** DEPENDENCIES:
struct window_pane *window_pane_find_by_id(u_int id)
{
  struct window_pane wp;
  wp.id = id;
  return window_pane_tree_RB_FIND(&all_window_panes, &wp);
}


----------------------------
int window_has_pane(struct window *w, struct window_pane *wp)
{
  struct window_pane *wp1;
  unsigned int wp1_idx = 0;
  for (wp1_idx = (&w->panes)->tqh_first; (&wp1[wp1_idx]) != 0; wp1_idx = wp1_idx->entry.tqe_next)
  {
    if ((&wp1[wp1_idx]) == wp)
    {
      return 1;
    }
  }

  return 0;
}


----------------------------
struct windows
{
  struct window *rbh_root;
}
----------------------------
struct window_tree_itemdata
{
  enum window_tree_type type;
  int session;
  int winlink;
  int pane;
}
----------------------------
struct winlink *winlink_find_by_index(struct winlinks *wwl, int idx)
{
  struct winlink wl;
  if (idx < 0)
  {
    fatalx("bad index");
  }
  wl.idx = idx;
  return winlinks_RB_FIND(wwl, &wl);
}


----------------------------
struct session *session_find_by_id(u_int id)
{
  struct session *s;
  unsigned int s_idx = 0;
  for (s_idx = sessions_RB_MINMAX(&sessions, -1); (&s[s_idx]) != 0; s_idx = sessions_RB_NEXT(s_idx))
  {
    if (s->id == id)
    {
      return s;
    }
  }

  return 0;
}


----------------------------
None
----------------------------
***/


static int window_tree_search(void *modedata, void *itemdata, const char *ss)
{
  struct window_tree_itemdata *item = itemdata;
  struct session *s;
  struct winlink *wl;
  struct window_pane *wp;
  const char *cmd;
  unsigned int cmd_idx = 0;
  window_tree_pull_item(item, &s, &wl, &wp);
  switch (item->type)
  {
    case WINDOW_TREE_NONE:
    {
      return 0;
    }

    case WINDOW_TREE_SESSION:
    {
      if (s == 0)
      {
        return 0;
      }
      return strstr(s->name, ss) != 0;
    }

    case WINDOW_TREE_WINDOW:
    {
      if ((s == 0) || (wl == 0))
      {
        return 0;
      }
      return strstr(wl->window->name, ss) != 0;
    }

    case WINDOW_TREE_PANE:
    {
      if (((s == 0) || (wl == 0)) || (wp == 0))
      {
        break;
      }
      cmd_idx = osdep_get_name(wp->fd, wp->tty);
      if (((&cmd[cmd_idx]) == 0) || (cmd[cmd_idx] == '\0'))
      {
        return 0;
      }
      return strstr(cmd, ss) != 0;
    }

  }

  return 0;
}


/*** DEPENDENCIES:
struct window_tree_itemdata
{
  enum window_tree_type type;
  int session;
  int winlink;
  int pane;
}
----------------------------
static void window_tree_pull_item(struct window_tree_itemdata *item, struct session **sp, struct winlink **wlp, struct window_pane **wp)
{
  *wp = 0;
  *wlp = 0;
  *sp = session_find_by_id(item->session);
  if ((*sp) == 0)
  {
    return;
  }
  if (item->type == WINDOW_TREE_SESSION)
  {
    *wlp = (*sp)->curw;
    *wp = (*wlp)->window->active;
    return;
  }
  *wlp = winlink_find_by_index(&(*sp)->windows, item->winlink);
  if ((*wlp) == 0)
  {
    *sp = 0;
    return;
  }
  if (item->type == WINDOW_TREE_WINDOW)
  {
    *wp = (*wlp)->window->active;
    return;
  }
  *wp = window_pane_find_by_id(item->pane);
  if (!window_has_pane((*wlp)->window, *wp))
  {
    *wp = 0;
  }
  if ((*wp) == 0)
  {
    *sp = 0;
    *wlp = 0;
    return;
  }
}


----------------------------
char *osdep_get_name(int fd, char *tty)
{
  FILE *f;
  unsigned int f_idx = 0;
  char *path;
  char *buf;
  unsigned int buf_idx = 0;
  size_t len;
  int ch;
  pid_t pgrp;
  if ((pgrp = tcgetpgrp(fd)) == (-1))
  {
    return 0;
  }
  xasprintf(&path, "/proc/%lld/cmdline", (long long) pgrp);
  if ((f_idx = fopen(path, "r")) == 0)
  {
    free(path);
    return 0;
  }
  free(path);
  len = 0;
  buf_idx = 0;
  while ((ch = fgetc(f)) != EOF)
  {
    if (ch == '\0')
    {
      break;
    }
    buf_idx = xrealloc(buf_idx, len + 2);
    buf[len + buf_idx] = ch;
    len += 1;
  }

  if ((&buf[buf_idx]) != 0)
  {
    buf[len + buf_idx] = '\0';
  }
  fclose(f);
  return buf;
}


----------------------------
None
----------------------------
***/


static enum cmd_retval window_tree_command_done(struct cmdq_item *item, void *modedata)
{
  struct window_tree_modedata *data = modedata;
  if (!data->dead)
  {
    mode_tree_build(data->data);
    mode_tree_draw(data->data);
    data->wp->flags |= 0x1;
  }
  window_tree_destroy(data);
  return CMD_RETURN_NORMAL;
}


/*** DEPENDENCIES:
struct window_tree_modedata
{
  struct window_pane *wp;
  int dead;
  int references;
  struct mode_tree_data *data;
  char *format;
  char *command;
  int squash_groups;
  struct window_tree_itemdata **item_list;
  u_int item_size;
  const char *entered;
  struct cmd_find_state fs;
  enum window_tree_type type;
  int offset;
  int left;
  int right;
  u_int start;
  u_int end;
  u_int each;
}
----------------------------
static void window_tree_destroy(struct window_tree_modedata *data)
{
  u_int i;
  if ((--data->references) != 0)
  {
    return;
  }
  for (i = 0; i < data->item_size; i += 1)
  {
    window_tree_free_item(data->item_list[i]);
  }

  free(data->item_list);
  free(data->format);
  free(data->command);
  free(data);
}


----------------------------
void mode_tree_draw(struct mode_tree_data *mtd)
{
  struct window_pane *wp = mtd->wp;
  struct screen *s = &mtd->screen;
  struct mode_tree_line *line;
  unsigned int line_idx = 0;
  struct mode_tree_item *mti;
  unsigned int mti_idx = 0;
  struct options *oo = wp->window->options;
  struct screen_write_ctx ctx;
  struct grid_cell gc0;
  struct grid_cell gc;
  u_int w;
  u_int h;
  u_int i;
  u_int j;
  u_int sy;
  u_int box_x;
  u_int box_y;
  char *text;
  char *start;
  unsigned int start_idx = 0;
  char key[7];
  const char *tag;
  unsigned int tag_idx = 0;
  const char *symbol;
  unsigned int symbol_idx = 0;
  size_t size;
  size_t n;
  int keylen;
  if (mtd->line_size == 0)
  {
    return;
  }
  memcpy(&gc0, &grid_default_cell, sizeof(gc0));
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  style_apply(&gc, oo, "mode-style");
  w = mtd->width;
  h = mtd->height;
  screen_write_start(&ctx, 0, s);
  screen_write_clearscreen(&ctx, 8);
  if (mtd->line_size > 10)
  {
    keylen = 6;
  }
  else
    keylen = 4;
  for (i = 0; i < mtd->line_size; i += 1)
  {
    helper_mode_tree_draw_1(&line_idx, &mti_idx, &gc0, &gc, &j, &start_idx, &tag_idx, &symbol_idx, &size, mtd, line, mti, ctx, w, h, i, text, start, key, tag, symbol, keylen);
  }

  sy = s->grid->sy;
  if (((((!mtd->preview) || (sy <= 4)) || (h <= 4)) || ((sy - h) <= 4)) || (w <= 4))
  {
    screen_write_stop(&ctx);
    return;
  }
  line_idx = &mtd->line_list[mtd->current];
  mti_idx = line->item;
  screen_write_cursormove(&ctx, 0, h);
  screen_write_box(&ctx, w, sy - h);
  xasprintf(&text, " %s (sort: %s)", mti->name, mtd->sort_list[mtd->sort_type]);
  if ((w - 2) >= strlen(text))
  {
    screen_write_cursormove(&ctx, 1, h);
    screen_write_puts(&ctx, &gc0, "%s", text);
    if (mtd->no_matches)
    {
      n = (sizeof("no matches")) - 1;
    }
    else
      n = (sizeof("active")) - 1;
    if ((mtd->filter != 0) && ((w - 2) >= (((strlen(text) + 10) + n) + 2)))
    {
      screen_write_puts(&ctx, &gc0, " (filter: ");
      if (mtd->no_matches)
      {
        screen_write_puts(&ctx, &gc, "no matches");
      }
      else
        screen_write_puts(&ctx, &gc0, "active");
      screen_write_puts(&ctx, &gc0, ") ");
    }
  }
  free(text);
  box_x = w - 4;
  box_y = (sy - h) - 2;
  if ((box_x != 0) && (box_y != 0))
  {
    screen_write_cursormove(&ctx, 2, h + 1);
    mtd->drawcb(mtd->modedata, mti->itemdata, &ctx, box_x, box_y);
  }
  screen_write_stop(&ctx);
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
void mode_tree_build(struct mode_tree_data *mtd)
{
  struct screen *s = &mtd->screen;
  uint64_t tag;
  if (mtd->line_list != 0)
  {
    tag = mtd->line_list[mtd->current].item->tag;
  }
  else
    tag = 0;
  do
  {
    if (!((&mtd->children)->tqh_first == 0))
    {
      *(&mtd->saved)->tqh_last = (&mtd->children)->tqh_first;
      (&mtd->children)->tqh_first->entry.tqe_prev = (&mtd->saved)->tqh_last;
      (&mtd->saved)->tqh_last = (&mtd->children)->tqh_last;
      do
      {
        (&mtd->children)->tqh_first = 0;
        (&mtd->children)->tqh_last = &(&mtd->children)->tqh_first;
      }
      while (0);
    }
  }
  while (0);
  do
  {
    (&mtd->children)->tqh_first = 0;
    (&mtd->children)->tqh_last = &(&mtd->children)->tqh_first;
  }
  while (0);
  mtd->buildcb(mtd->modedata, mtd->sort_type, &tag, mtd->filter);
  mtd->no_matches = (&mtd->children)->tqh_first == 0;
  if (mtd->no_matches)
  {
    mtd->buildcb(mtd->modedata, mtd->sort_type, &tag, 0);
  }
  mode_tree_free_items(&mtd->saved);
  do
  {
    (&mtd->saved)->tqh_first = 0;
    (&mtd->saved)->tqh_last = &(&mtd->saved)->tqh_first;
  }
  while (0);
  mode_tree_clear_lines(mtd);
  mode_tree_build_lines(mtd, &mtd->children, 0);
  mode_tree_set_current(mtd, tag);
  mtd->width = s->grid->sx;
  if (mtd->preview)
  {
    mtd->height = (s->grid->sy / 3) * 2;
    if (mtd->height > mtd->line_size)
    {
      mtd->height = s->grid->sy / 2;
    }
    if (mtd->height < 10)
    {
      mtd->height = s->grid->sy;
    }
    if ((s->grid->sy - mtd->height) < 2)
    {
      mtd->height = s->grid->sy;
    }
  }
  else
    mtd->height = s->grid->sy;
  mode_tree_check_selected(mtd);
}


----------------------------
None
----------------------------
***/


static char *window_tree_get_target(struct window_tree_itemdata *item, struct cmd_find_state *fs)
{
  struct session *s;
  struct winlink *wl;
  struct window_pane *wp;
  char *target;
  unsigned int target_idx = 0;
  window_tree_pull_item(item, &s, &wl, &wp);
  target_idx = 0;
  switch (item->type)
  {
    case WINDOW_TREE_NONE:
    {
      break;
    }

    case WINDOW_TREE_SESSION:
    {
      if (s == 0)
      {
        break;
      }
      xasprintf(&(&target[target_idx]), "=%s:", s->name);
      break;
    }

    case WINDOW_TREE_WINDOW:
    {
      if ((s == 0) || (wl == 0))
      {
        break;
      }
      xasprintf(&(&target[target_idx]), "=%s:%u.", s->name, wl->idx);
      break;
    }

    case WINDOW_TREE_PANE:
    {
      if (((s == 0) || (wl == 0)) || (wp == 0))
      {
        break;
      }
      xasprintf(&(&target[target_idx]), "=%s:%u.%%%u", s->name, wl->idx, wp->id);
      break;
    }

  }

  if ((&target[target_idx]) == 0)
  {
    cmd_find_clear_state(fs, 0);
  }
  else
    cmd_find_from_winlink_pane(fs, wl, wp, 0);
  return target;
}


/*** DEPENDENCIES:
static void window_tree_pull_item(struct window_tree_itemdata *item, struct session **sp, struct winlink **wlp, struct window_pane **wp)
{
  *wp = 0;
  *wlp = 0;
  *sp = session_find_by_id(item->session);
  if ((*sp) == 0)
  {
    return;
  }
  if (item->type == WINDOW_TREE_SESSION)
  {
    *wlp = (*sp)->curw;
    *wp = (*wlp)->window->active;
    return;
  }
  *wlp = winlink_find_by_index(&(*sp)->windows, item->winlink);
  if ((*wlp) == 0)
  {
    *sp = 0;
    return;
  }
  if (item->type == WINDOW_TREE_WINDOW)
  {
    *wp = (*wlp)->window->active;
    return;
  }
  *wp = window_pane_find_by_id(item->pane);
  if (!window_has_pane((*wlp)->window, *wp))
  {
    *wp = 0;
  }
  if ((*wp) == 0)
  {
    *sp = 0;
    *wlp = 0;
    return;
  }
}


----------------------------
struct window_tree_itemdata
{
  enum window_tree_type type;
  int session;
  int winlink;
  int pane;
}
----------------------------
void cmd_find_clear_state(struct cmd_find_state *fs, int flags)
{
  memset(fs, 0, sizeof(*fs));
  fs->flags = flags;
  fs->idx = -1;
}


----------------------------
void cmd_find_from_winlink_pane(struct cmd_find_state *fs, struct winlink *wl, struct window_pane *wp, int flags)
{
  cmd_find_clear_state(fs, flags);
  fs->s = wl->session;
  fs->wl = wl;
  fs->idx = fs->wl->idx;
  fs->w = fs->wl->window;
  fs->wp = wp;
  cmd_find_log_state(__func__, fs);
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
None
----------------------------
***/


static void window_tree_command_each(void *modedata, void *itemdata, struct client *c, key_code key)
{
  struct window_tree_modedata *data = modedata;
  struct window_tree_itemdata *item = itemdata;
  char *name;
  unsigned int name_idx = 0;
  struct cmd_find_state fs;
  name_idx = window_tree_get_target(item, &fs);
  if ((&name[name_idx]) != 0)
  {
    mode_tree_run_command(c, &fs, data->entered, name);
  }
  free(name);
}


/*** DEPENDENCIES:
typedef unsigned long long key_code
----------------------------
struct window_tree_modedata
{
  struct window_pane *wp;
  int dead;
  int references;
  struct mode_tree_data *data;
  char *format;
  char *command;
  int squash_groups;
  struct window_tree_itemdata **item_list;
  u_int item_size;
  const char *entered;
  struct cmd_find_state fs;
  enum window_tree_type type;
  int offset;
  int left;
  int right;
  u_int start;
  u_int end;
  u_int each;
}
----------------------------
void mode_tree_run_command(struct client *c, struct cmd_find_state *fs, const char *template, const char *name)
{
  struct cmdq_item *new_item;
  unsigned int new_item_idx = 0;
  struct cmd_list *cmdlist;
  unsigned int cmdlist_idx = 0;
  char *command;
  unsigned int command_idx = 0;
  char *cause;
  command_idx = cmd_template_replace(template, name, 1);
  if (((&command[command_idx]) == 0) || (command[command_idx] == '\0'))
  {
    free(command);
    return;
  }
  cmdlist_idx = cmd_string_parse(command, 0, 0, &cause);
  if ((&cmdlist[cmdlist_idx]) == 0)
  {
    if ((cause != 0) && (c != 0))
    {
      *cause = toupper((u_char) (*cause));
      status_message_set(c, "%s", cause);
    }
    free(cause);
  }
  else
  {
    new_item_idx = cmdq_get_command(cmdlist, fs, 0, 0);
    cmdq_append(c, new_item);
    cmd_list_free(cmdlist);
  }
  free(command);
}


----------------------------
struct window_tree_itemdata
{
  enum window_tree_type type;
  int session;
  int winlink;
  int pane;
}
----------------------------
static char *window_tree_get_target(struct window_tree_itemdata *item, struct cmd_find_state *fs)
{
  struct session *s;
  struct winlink *wl;
  struct window_pane *wp;
  char *target;
  unsigned int target_idx = 0;
  window_tree_pull_item(item, &s, &wl, &wp);
  target_idx = 0;
  switch (item->type)
  {
    case WINDOW_TREE_NONE:
    {
      break;
    }

    case WINDOW_TREE_SESSION:
    {
      if (s == 0)
      {
        break;
      }
      xasprintf(&(&target[target_idx]), "=%s:", s->name);
      break;
    }

    case WINDOW_TREE_WINDOW:
    {
      if ((s == 0) || (wl == 0))
      {
        break;
      }
      xasprintf(&(&target[target_idx]), "=%s:%u.", s->name, wl->idx);
      break;
    }

    case WINDOW_TREE_PANE:
    {
      if (((s == 0) || (wl == 0)) || (wp == 0))
      {
        break;
      }
      xasprintf(&(&target[target_idx]), "=%s:%u.%%%u", s->name, wl->idx, wp->id);
      break;
    }

  }

  if ((&target[target_idx]) == 0)
  {
    cmd_find_clear_state(fs, 0);
  }
  else
    cmd_find_from_winlink_pane(fs, wl, wp, 0);
  return target;
}


----------------------------
None
----------------------------
***/


static int window_tree_command_callback(struct client *c, void *modedata, const char *s, int done)
{
  struct window_tree_modedata *data = modedata;
  if (((s == 0) || ((*s) == '\0')) || data->dead)
  {
    return 0;
  }
  data->entered = s;
  mode_tree_each_tagged(data->data, window_tree_command_each, c, 0xffff00000000ULL, 1);
  data->entered = 0;
  data->references += 1;
  cmdq_append(c, cmdq_get_callback1("window_tree_command_done", window_tree_command_done, data));
  return 0;
}


/*** DEPENDENCIES:
struct window_tree_modedata
{
  struct window_pane *wp;
  int dead;
  int references;
  struct mode_tree_data *data;
  char *format;
  char *command;
  int squash_groups;
  struct window_tree_itemdata **item_list;
  u_int item_size;
  const char *entered;
  struct cmd_find_state fs;
  enum window_tree_type type;
  int offset;
  int left;
  int right;
  u_int start;
  u_int end;
  u_int each;
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
static enum cmd_retval window_tree_command_done(struct cmdq_item *item, void *modedata)
{
  struct window_tree_modedata *data = modedata;
  if (!data->dead)
  {
    mode_tree_build(data->data);
    mode_tree_draw(data->data);
    data->wp->flags |= 0x1;
  }
  window_tree_destroy(data);
  return CMD_RETURN_NORMAL;
}


----------------------------
static void window_tree_command_each(void *modedata, void *itemdata, struct client *c, key_code key)
{
  struct window_tree_modedata *data = modedata;
  struct window_tree_itemdata *item = itemdata;
  char *name;
  unsigned int name_idx = 0;
  struct cmd_find_state fs;
  name_idx = window_tree_get_target(item, &fs);
  if ((&name[name_idx]) != 0)
  {
    mode_tree_run_command(c, &fs, data->entered, name);
  }
  free(name);
}


----------------------------
void mode_tree_each_tagged(struct mode_tree_data *mtd, mode_tree_each_cb cb, struct client *c, key_code key, int current)
{
  struct mode_tree_item *mti;
  unsigned int mti_idx = 0;
  u_int i;
  int fired;
  fired = 0;
  for (i = 0; i < mtd->line_size; i += 1)
  {
    mti_idx = mtd->line_list[i].item;
    if (mti->tagged)
    {
      fired = 1;
      cb(mtd->modedata, mti->itemdata, c, key);
    }
  }

  if ((!fired) && current)
  {
    mti_idx = mtd->line_list[mtd->current].item;
    cb(mtd->modedata, mti->itemdata, c, key);
  }
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


static void window_tree_kill_each(void *modedata, void *itemdata, struct client *c, key_code key)
{
  struct window_tree_itemdata *item = itemdata;
  struct session *s;
  struct winlink *wl;
  struct window_pane *wp;
  window_tree_pull_item(item, &s, &wl, &wp);
  switch (item->type)
  {
    case WINDOW_TREE_NONE:
    {
      break;
    }

    case WINDOW_TREE_SESSION:
    {
      if (s != 0)
      {
        server_destroy_session(s);
        session_destroy(s, __func__);
      }
      break;
    }

    case WINDOW_TREE_WINDOW:
    {
      if (wl != 0)
      {
        server_kill_window(wl->window);
      }
      break;
    }

    case WINDOW_TREE_PANE:
    {
      if (wp != 0)
      {
        server_kill_pane(wp);
      }
      break;
    }

  }

}


/*** DEPENDENCIES:
static void window_tree_pull_item(struct window_tree_itemdata *item, struct session **sp, struct winlink **wlp, struct window_pane **wp)
{
  *wp = 0;
  *wlp = 0;
  *sp = session_find_by_id(item->session);
  if ((*sp) == 0)
  {
    return;
  }
  if (item->type == WINDOW_TREE_SESSION)
  {
    *wlp = (*sp)->curw;
    *wp = (*wlp)->window->active;
    return;
  }
  *wlp = winlink_find_by_index(&(*sp)->windows, item->winlink);
  if ((*wlp) == 0)
  {
    *sp = 0;
    return;
  }
  if (item->type == WINDOW_TREE_WINDOW)
  {
    *wp = (*wlp)->window->active;
    return;
  }
  *wp = window_pane_find_by_id(item->pane);
  if (!window_has_pane((*wlp)->window, *wp))
  {
    *wp = 0;
  }
  if ((*wp) == 0)
  {
    *sp = 0;
    *wlp = 0;
    return;
  }
}


----------------------------
typedef unsigned long long key_code
----------------------------
void server_destroy_session(struct session *s)
{
  struct client *c;
  unsigned int c_idx = 0;
  struct session *s_new;
  unsigned int s_new_idx = 0;
  if (!options_get_number(s->options, "detach-on-destroy"))
  {
    s_new_idx = server_next_session(s);
  }
  else
    s_new_idx = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if (c->session != s)
    {
      continue;
    }
    if ((&s_new[s_new_idx]) == 0)
    {
      c->session = 0;
      c->flags |= 0x4;
    }
    else
    {
      c->last_session = 0;
      c->session = &s_new[s_new_idx];
      server_client_set_key_table(c, 0);
      status_timer_start(c);
      notify_client("client-session-changed", c);
      session_update_activity(s_new, 0);
      gettimeofday(&s_new->last_attached_time, 0);
      server_redraw_client(c);
      alerts_check_session(s_new);
    }
  }

  recalculate_sizes();
}


----------------------------
struct window_tree_itemdata
{
  enum window_tree_type type;
  int session;
  int winlink;
  int pane;
}
----------------------------
void session_destroy(struct session *s, const char *from)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  log_debug("session %s destroyed (%s)", s->name, from);
  s->curw = 0;
  sessions_RB_REMOVE(&sessions, s);
  notify_session("session-closed", s);
  free(s->tio);
  if (event_initialized(&s->lock_timer))
  {
    event_del(&s->lock_timer);
  }
  session_group_remove(s);
  while (!((&s->lastw)->tqh_first == 0))
  {
    winlink_stack_remove(&s->lastw, (&s->lastw)->tqh_first);
  }

  while (!((&s->windows)->rbh_root == 0))
  {
    wl_idx = (&s->windows)->rbh_root;
    notify_session_window("window-unlinked", s, wl->window);
    winlink_remove(&s->windows, wl);
  }

  free((void *) s->cwd);
  session_remove_ref(s, __func__);
}


----------------------------
void server_kill_pane(struct window_pane *wp)
{
  struct window *w = wp->window;
  if (window_count_panes(w) == 1)
  {
    server_kill_window(w);
    recalculate_sizes();
  }
  else
  {
    server_unzoom_window(w);
    layout_close_pane(wp);
    window_remove_pane(w, wp);
    server_redraw_window(w);
  }
}


----------------------------
void server_kill_window(struct window *w)
{
  struct session *s;
  unsigned int s_idx = 0;
  struct session *next_s;
  unsigned int next_s_idx = 0;
  struct session *target_s;
  unsigned int target_s_idx = 0;
  struct session_group *sg;
  unsigned int sg_idx = 0;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  next_s_idx = sessions_RB_MINMAX(&sessions, -1);
  while ((&next_s[next_s_idx]) != 0)
  {
    s_idx = &next_s[next_s_idx];
    next_s_idx = sessions_RB_NEXT(s);
    if (!session_has(s, w))
    {
      continue;
    }
    server_unzoom_window(w);
    while ((wl_idx = winlink_find_by_window(&s->windows, w)) != 0)
    {
      if (session_detach(s, wl))
      {
        server_destroy_session_group(s);
        break;
      }
      else
        server_redraw_session_group(s);
    }

    if (options_get_number(s->options, "renumber-windows"))
    {
      if ((sg_idx = session_group_contains(s)) != 0)
      {
        for (target_s_idx = (&sg->sessions)->tqh_first; (&target_s[target_s_idx]) != 0; target_s_idx = target_s_idx->gentry.tqe_next)
        {
          session_renumber_windows(target_s);
        }

      }
      else
        session_renumber_windows(s);
    }
  }

  recalculate_sizes();
}


----------------------------
None
----------------------------
***/


static int window_tree_kill_current_callback(struct client *c, void *modedata, const char *s, int done)
{
  struct window_tree_modedata *data = modedata;
  struct mode_tree_data *mtd = data->data;
  if (((s == 0) || ((*s) == '\0')) || data->dead)
  {
    return 0;
  }
  if ((tolower((u_char) s[0]) != 'y') || (s[1] != '\0'))
  {
    return 0;
  }
  window_tree_kill_each(data, mode_tree_get_current(mtd), c, 0xffff00000000ULL);
  data->references += 1;
  cmdq_append(c, cmdq_get_callback1("window_tree_command_done", window_tree_command_done, data));
  return 0;
}


/*** DEPENDENCIES:
struct window_tree_modedata
{
  struct window_pane *wp;
  int dead;
  int references;
  struct mode_tree_data *data;
  char *format;
  char *command;
  int squash_groups;
  struct window_tree_itemdata **item_list;
  u_int item_size;
  const char *entered;
  struct cmd_find_state fs;
  enum window_tree_type type;
  int offset;
  int left;
  int right;
  u_int start;
  u_int end;
  u_int each;
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
struct mode_tree_data
{
  int dead;
  u_int references;
  int zoomed;
  struct window_pane *wp;
  void *modedata;
  const char **sort_list;
  u_int sort_size;
  u_int sort_type;
  mode_tree_build_cb buildcb;
  mode_tree_draw_cb drawcb;
  mode_tree_search_cb searchcb;
  struct mode_tree_list children;
  struct mode_tree_list saved;
  struct mode_tree_line *line_list;
  u_int line_size;
  u_int depth;
  u_int width;
  u_int height;
  u_int offset;
  u_int current;
  struct screen screen;
  int preview;
  char *search;
  char *filter;
  int no_matches;
}
----------------------------
static enum cmd_retval window_tree_command_done(struct cmdq_item *item, void *modedata)
{
  struct window_tree_modedata *data = modedata;
  if (!data->dead)
  {
    mode_tree_build(data->data);
    mode_tree_draw(data->data);
    data->wp->flags |= 0x1;
  }
  window_tree_destroy(data);
  return CMD_RETURN_NORMAL;
}


----------------------------
static void window_tree_kill_each(void *modedata, void *itemdata, struct client *c, key_code key)
{
  struct window_tree_itemdata *item = itemdata;
  struct session *s;
  struct winlink *wl;
  struct window_pane *wp;
  window_tree_pull_item(item, &s, &wl, &wp);
  switch (item->type)
  {
    case WINDOW_TREE_NONE:
    {
      break;
    }

    case WINDOW_TREE_SESSION:
    {
      if (s != 0)
      {
        server_destroy_session(s);
        session_destroy(s, __func__);
      }
      break;
    }

    case WINDOW_TREE_WINDOW:
    {
      if (wl != 0)
      {
        server_kill_window(wl->window);
      }
      break;
    }

    case WINDOW_TREE_PANE:
    {
      if (wp != 0)
      {
        server_kill_pane(wp);
      }
      break;
    }

  }

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
void *mode_tree_get_current(struct mode_tree_data *mtd)
{
  return mtd->line_list[mtd->current].item->itemdata;
}


----------------------------
None
----------------------------
***/


static int window_tree_kill_tagged_callback(struct client *c, void *modedata, const char *s, int done)
{
  struct window_tree_modedata *data = modedata;
  struct mode_tree_data *mtd = data->data;
  if (((s == 0) || ((*s) == '\0')) || data->dead)
  {
    return 0;
  }
  if ((tolower((u_char) s[0]) != 'y') || (s[1] != '\0'))
  {
    return 0;
  }
  mode_tree_each_tagged(mtd, window_tree_kill_each, c, 0xffff00000000ULL, 1);
  data->references += 1;
  cmdq_append(c, cmdq_get_callback1("window_tree_command_done", window_tree_command_done, data));
  return 0;
}


/*** DEPENDENCIES:
struct window_tree_modedata
{
  struct window_pane *wp;
  int dead;
  int references;
  struct mode_tree_data *data;
  char *format;
  char *command;
  int squash_groups;
  struct window_tree_itemdata **item_list;
  u_int item_size;
  const char *entered;
  struct cmd_find_state fs;
  enum window_tree_type type;
  int offset;
  int left;
  int right;
  u_int start;
  u_int end;
  u_int each;
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
struct mode_tree_data
{
  int dead;
  u_int references;
  int zoomed;
  struct window_pane *wp;
  void *modedata;
  const char **sort_list;
  u_int sort_size;
  u_int sort_type;
  mode_tree_build_cb buildcb;
  mode_tree_draw_cb drawcb;
  mode_tree_search_cb searchcb;
  struct mode_tree_list children;
  struct mode_tree_list saved;
  struct mode_tree_line *line_list;
  u_int line_size;
  u_int depth;
  u_int width;
  u_int height;
  u_int offset;
  u_int current;
  struct screen screen;
  int preview;
  char *search;
  char *filter;
  int no_matches;
}
----------------------------
static enum cmd_retval window_tree_command_done(struct cmdq_item *item, void *modedata)
{
  struct window_tree_modedata *data = modedata;
  if (!data->dead)
  {
    mode_tree_build(data->data);
    mode_tree_draw(data->data);
    data->wp->flags |= 0x1;
  }
  window_tree_destroy(data);
  return CMD_RETURN_NORMAL;
}


----------------------------
static void window_tree_kill_each(void *modedata, void *itemdata, struct client *c, key_code key)
{
  struct window_tree_itemdata *item = itemdata;
  struct session *s;
  struct winlink *wl;
  struct window_pane *wp;
  window_tree_pull_item(item, &s, &wl, &wp);
  switch (item->type)
  {
    case WINDOW_TREE_NONE:
    {
      break;
    }

    case WINDOW_TREE_SESSION:
    {
      if (s != 0)
      {
        server_destroy_session(s);
        session_destroy(s, __func__);
      }
      break;
    }

    case WINDOW_TREE_WINDOW:
    {
      if (wl != 0)
      {
        server_kill_window(wl->window);
      }
      break;
    }

    case WINDOW_TREE_PANE:
    {
      if (wp != 0)
      {
        server_kill_pane(wp);
      }
      break;
    }

  }

}


----------------------------
void mode_tree_each_tagged(struct mode_tree_data *mtd, mode_tree_each_cb cb, struct client *c, key_code key, int current)
{
  struct mode_tree_item *mti;
  unsigned int mti_idx = 0;
  u_int i;
  int fired;
  fired = 0;
  for (i = 0; i < mtd->line_size; i += 1)
  {
    mti_idx = mtd->line_list[i].item;
    if (mti->tagged)
    {
      fired = 1;
      cb(mtd->modedata, mti->itemdata, c, key);
    }
  }

  if ((!fired) && current)
  {
    mti_idx = mtd->line_list[mtd->current].item;
    cb(mtd->modedata, mti->itemdata, c, key);
  }
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


// hint:  ['wl_idx_ref is a mutable refrence to unsigned int', 'loop_ref is a mutable refrence to u_int']
key_code helper_window_tree_mouse_1(unsigned int * const wl_idx_ref, u_int * const loop_ref, struct window_tree_modedata * const data, u_int x, struct session * const s, struct winlink * const wl)
{
  unsigned int wl_idx = *wl_idx_ref;
  u_int loop = *loop_ref;
  if (s == 0)
  {
    return 0xffff00000000ULL;
  }
  mode_tree_expand_current(data->data);
  loop = 0;
  for (wl_idx = winlinks_RB_MINMAX(&s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    if (loop == (data->start + x))
    {
      break;
    }
    loop += 1;
  }

  if ((&wl[wl_idx]) != 0)
  {
    mode_tree_set_current(data->data, (uint64_t) wl);
  }
  return '\r';
  *wl_idx_ref = wl_idx;
  *loop_ref = loop;
}


/*** DEPENDENCIES:
struct window_tree_modedata
{
  struct window_pane *wp;
  int dead;
  int references;
  struct mode_tree_data *data;
  char *format;
  char *command;
  int squash_groups;
  struct window_tree_itemdata **item_list;
  u_int item_size;
  const char *entered;
  struct cmd_find_state fs;
  enum window_tree_type type;
  int offset;
  int left;
  int right;
  u_int start;
  u_int end;
  u_int each;
}
----------------------------
struct windows
{
  struct window *rbh_root;
}
----------------------------
struct winlink *winlinks_RB_NEXT(struct winlink *elm)
{
  unsigned int elm_idx = 0;
  if (elm->entry.rbe_right)
  {
    elm_idx = elm_idx->entry.rbe_right;
    while (elm->entry.rbe_left)
    {
      elm_idx = elm_idx->entry.rbe_left;
    }

  }
  else
  {
    if (elm->entry.rbe_parent && ((&elm[elm_idx]) == elm->entry.rbe_parent->entry.rbe_left))
    {
      elm_idx = elm_idx->entry.rbe_parent;
    }
    else
    {
      while (elm->entry.rbe_parent && ((&elm[elm_idx]) == elm->entry.rbe_parent->entry.rbe_right))
      {
        elm_idx = elm_idx->entry.rbe_parent;
      }

      elm_idx = elm_idx->entry.rbe_parent;
    }
  }
  return elm;
}


----------------------------
void mode_tree_expand_current(struct mode_tree_data *mtd)
{
  if (!mtd->line_list[mtd->current].item->expanded)
  {
    mtd->line_list[mtd->current].item->expanded = 1;
    mode_tree_build(mtd);
  }
}


----------------------------
struct winlink *winlinks_RB_MINMAX(struct winlinks *head, int val)
{
  struct winlink *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct winlink *parent = 0;
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
void mode_tree_set_current(struct mode_tree_data *mtd, uint64_t tag)
{
  u_int i;
  for (i = 0; i < mtd->line_size; i += 1)
  {
    if (mtd->line_list[i].item->tag == tag)
    {
      break;
    }
  }

  if (i != mtd->line_size)
  {
    mtd->current = i;
    if (mtd->current > (mtd->height - 1))
    {
      mtd->offset = (mtd->current - mtd->height) + 1;
    }
    else
      mtd->offset = 0;
  }
  else
  {
    mtd->current = 0;
    mtd->offset = 0;
  }
}


----------------------------
None
----------------------------
***/


static key_code window_tree_mouse(struct window_tree_modedata *data, key_code key, u_int x, struct window_tree_itemdata *item)
{
  struct session *s;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int loop;
  if (key != KEYC_MOUSEDOWN1_PANE)
  {
    return 0xffff00000000ULL;
  }
  if ((data->left != (-1)) && (x <= ((u_int) data->left)))
  {
    return '<';
  }
  if ((data->right != (-1)) && (x >= ((u_int) data->right)))
  {
    return '>';
  }
  if (data->left != (-1))
  {
    x -= data->left;
  }
  else
    if (x != 0)
  {
    x -= 1;
  }
  if ((x == 0) || (data->end == 0))
  {
    x = 0;
  }
  else
  {
    x = x / data->each;
    if ((data->start + x) >= data->end)
    {
      x = data->end - 1;
    }
  }
  window_tree_pull_item(item, &s, &(&wl[wl_idx]), &(&wp[wp_idx]));
  if (item->type == WINDOW_TREE_SESSION)
  {
    helper_window_tree_mouse_1(&wl_idx, &loop, data, x, s, wl);
  }
  if (item->type == WINDOW_TREE_WINDOW)
  {
    helper_window_tree_mouse_2(&wp_idx, &loop, data, x, wl, wl_idx, wp);
  }
  return 0xffff00000000ULL;
}


/*** DEPENDENCIES:
static void window_tree_pull_item(struct window_tree_itemdata *item, struct session **sp, struct winlink **wlp, struct window_pane **wp)
{
  *wp = 0;
  *wlp = 0;
  *sp = session_find_by_id(item->session);
  if ((*sp) == 0)
  {
    return;
  }
  if (item->type == WINDOW_TREE_SESSION)
  {
    *wlp = (*sp)->curw;
    *wp = (*wlp)->window->active;
    return;
  }
  *wlp = winlink_find_by_index(&(*sp)->windows, item->winlink);
  if ((*wlp) == 0)
  {
    *sp = 0;
    return;
  }
  if (item->type == WINDOW_TREE_WINDOW)
  {
    *wp = (*wlp)->window->active;
    return;
  }
  *wp = window_pane_find_by_id(item->pane);
  if (!window_has_pane((*wlp)->window, *wp))
  {
    *wp = 0;
  }
  if ((*wp) == 0)
  {
    *sp = 0;
    *wlp = 0;
    return;
  }
}


----------------------------
typedef unsigned long long key_code
----------------------------
struct window_tree_modedata
{
  struct window_pane *wp;
  int dead;
  int references;
  struct mode_tree_data *data;
  char *format;
  char *command;
  int squash_groups;
  struct window_tree_itemdata **item_list;
  u_int item_size;
  const char *entered;
  struct cmd_find_state fs;
  enum window_tree_type type;
  int offset;
  int left;
  int right;
  u_int start;
  u_int end;
  u_int each;
}
----------------------------
struct window_tree_itemdata
{
  enum window_tree_type type;
  int session;
  int winlink;
  int pane;
}
----------------------------
key_code helper_window_tree_mouse_2(unsigned int * const wp_idx_ref, u_int * const loop_ref, struct window_tree_modedata * const data, u_int x, struct winlink * const wl, unsigned int wl_idx, struct window_pane * const wp)
{
  unsigned int wp_idx = *wp_idx_ref;
  u_int loop = *loop_ref;
  if ((&wl[wl_idx]) == 0)
  {
    return 0xffff00000000ULL;
  }
  mode_tree_expand_current(data->data);
  loop = 0;
  for (wp_idx = (&wl->window->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    if (loop == (data->start + x))
    {
      break;
    }
    loop += 1;
  }

  if ((&wp[wp_idx]) != 0)
  {
    mode_tree_set_current(data->data, (uint64_t) wp);
  }
  return '\r';
  *wp_idx_ref = wp_idx;
  *loop_ref = loop;
}


----------------------------
key_code helper_window_tree_mouse_1(unsigned int * const wl_idx_ref, u_int * const loop_ref, struct window_tree_modedata * const data, u_int x, struct session * const s, struct winlink * const wl)
{
  unsigned int wl_idx = *wl_idx_ref;
  u_int loop = *loop_ref;
  if (s == 0)
  {
    return 0xffff00000000ULL;
  }
  mode_tree_expand_current(data->data);
  loop = 0;
  for (wl_idx = winlinks_RB_MINMAX(&s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    if (loop == (data->start + x))
    {
      break;
    }
    loop += 1;
  }

  if ((&wl[wl_idx]) != 0)
  {
    mode_tree_set_current(data->data, (uint64_t) wl);
  }
  return '\r';
  *wl_idx_ref = wl_idx;
  *loop_ref = loop;
}


----------------------------
None
----------------------------
***/


// hint:  ['loop_ref is a mutable refrence to u_int', 'width_ref is a mutable refrence to u_int', 'offset_ref is a mutable refrence to u_int', 'i_ref is a mutable refrence to u_int', 'gc_ref is a mutable refrence to ', 'pane_idx_ref is a mutable refrence to int']
void helper_window_tree_draw_window_1(u_int * const loop_ref, u_int * const width_ref, u_int * const offset_ref, u_int * const i_ref, struct grid_cell * const gc_ref, int * const pane_idx_ref, struct window * const w, struct screen_write_ctx * const ctx, u_int sy, struct window_pane * const wp, unsigned int wp_idx, u_int cx, u_int cy, u_int each, u_int start, u_int end, u_int remaining, int colour, int active_colour, int left, char * const label)
{
  u_int loop = *loop_ref;
  u_int width = *width_ref;
  u_int offset = *offset_ref;
  u_int i = *i_ref;
  struct grid_cell gc = *gc_ref;
  int pane_idx = *pane_idx_ref;
  if (loop == end)
  {
    break;
  }
  if (loop < start)
  {
    loop += 1;
    continue;
  }
  if ((&wp[wp_idx]) == w->active)
  {
    gc.fg = active_colour;
  }
  else
    gc.fg = colour;
  if (left)
  {
    offset = 3 + (i * each);
  }
  else
    offset = i * each;
  if (loop == (end - 1))
  {
    width = each + remaining;
  }
  else
    width = each - 1;
  screen_write_cursormove(ctx, cx + offset, cy);
  screen_write_preview(ctx, &wp->base, width, sy);
  if (window_pane_index(wp, &pane_idx) != 0)
  {
    pane_idx = loop;
  }
  xasprintf(&label, " %u ", pane_idx);
  window_tree_draw_label(ctx, cx + offset, cy, each, sy, &gc, label);
  free(label);
  if (loop != (end - 1))
  {
    screen_write_cursormove(ctx, (cx + offset) + width, cy);
    screen_write_vline(ctx, sy, 0, 0);
  }
  loop += 1;
  i += 1;
  *loop_ref = loop;
  *width_ref = width;
  *offset_ref = offset;
  *i_ref = i;
  *gc_ref = gc;
  *pane_idx_ref = pane_idx;
}


/*** DEPENDENCIES:
void screen_write_cursormove(struct screen_write_ctx *ctx, u_int px, u_int py)
{
  struct screen *s = ctx->s;
  if (px > (s->grid->sx - 1))
  {
    px = s->grid->sx - 1;
  }
  if (py > (s->grid->sy - 1))
  {
    py = s->grid->sy - 1;
  }
  s->cx = px;
  s->cy = py;
}


----------------------------
None
----------------------------
void screen_write_vline(struct screen_write_ctx *ctx, u_int ny, int top, int bottom)
{
  struct screen *s = ctx->s;
  struct grid_cell gc;
  u_int cx;
  u_int cy;
  u_int i;
  cx = s->cx;
  cy = s->cy;
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  gc.attr |= 0x80;
  screen_write_putc(ctx, &gc, (top) ? ('w') : ('x'));
  for (i = 1; i < (ny - 1); i += 1)
  {
    screen_write_cursormove(ctx, cx, cy + i);
    screen_write_putc(ctx, &gc, 'x');
  }

  screen_write_cursormove(ctx, cx, (cy + ny) - 1);
  screen_write_putc(ctx, &gc, (bottom) ? ('v') : ('x'));
  screen_write_cursormove(ctx, cx, cy);
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
static void window_tree_draw_label(struct screen_write_ctx *ctx, u_int px, u_int py, u_int sx, u_int sy, const struct grid_cell *gc, const char *label)
{
  size_t len;
  u_int ox;
  u_int oy;
  len = strlen(label);
  if (((sx == 0) || (sy == 1)) || (len > sx))
  {
    return;
  }
  ox = ((sx - len) + 1) / 2;
  oy = (sy + 1) / 2;
  if (((ox > 1) && ((ox + len) < (sx - 1))) && (sy >= 3))
  {
    screen_write_cursormove(ctx, (px + ox) - 1, (py + oy) - 1);
    screen_write_box(ctx, len + 2, 3);
  }
  screen_write_cursormove(ctx, px + ox, py + oy);
  screen_write_puts(ctx, gc, "%s", label);
}


----------------------------
None
----------------------------
void screen_write_preview(struct screen_write_ctx *ctx, struct screen *src, u_int nx, u_int ny)
{
  struct screen *s = ctx->s;
  struct grid_cell gc;
  u_int cx;
  u_int cy;
  u_int px;
  u_int py;
  cx = s->cx;
  cy = s->cy;
  if (src->mode & 0x1)
  {
    px = src->cx;
    if (px < (nx / 3))
    {
      px = 0;
    }
    else
      px = px - (nx / 3);
    if ((px + nx) > src->grid->sx)
    {
      if (nx > src->grid->sx)
      {
        px = 0;
      }
      else
        px = src->grid->sx - nx;
    }
    py = src->cy;
    if (py < (ny / 3))
    {
      py = 0;
    }
    else
      py = py - (ny / 3);
    if ((py + ny) > src->grid->sy)
    {
      if (ny > src->grid->sy)
      {
        py = 0;
      }
      else
        py = src->grid->sy - ny;
    }
  }
  else
  {
    px = 0;
    py = 0;
  }
  screen_write_fast_copy(ctx, src, px, src->grid->hsize + py, nx, ny);
  if (src->mode & 0x1)
  {
    grid_view_get_cell(src->grid, src->cx, src->cy, &gc);
    gc.attr |= 0x10;
    screen_write_cursormove(ctx, cx + (src->cx - px), cy + (src->cy - py));
    screen_write_cell(ctx, &gc);
  }
}


----------------------------
int window_pane_index(struct window_pane *wp, u_int *i)
{
  struct window_pane *wq;
  unsigned int wq_idx = 0;
  struct window *w = wp->window;
  *i = options_get_number(w->options, "pane-base-index");
  for (wq_idx = (&w->panes)->tqh_first; (&wq[wq_idx]) != 0; wq_idx = wq_idx->entry.tqe_next)
  {
    if (wp == (&wq[wq_idx]))
    {
      return 0;
    }
    *i += 1;
  }

  return -1;
}


----------------------------
None
----------------------------
***/


static void window_tree_draw_window(struct window_tree_modedata *data, struct session *s, struct window *w, struct screen_write_ctx *ctx, u_int sx, u_int sy)
{
  struct options *oo = s->options;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int cx = ctx->s->cx;
  u_int cy = ctx->s->cy;
  u_int loop;
  u_int total;
  u_int visible;
  u_int each;
  u_int width;
  u_int offset;
  u_int current;
  u_int start;
  u_int end;
  u_int remaining;
  u_int i;
  struct grid_cell gc;
  int colour;
  int active_colour;
  int left;
  int right;
  int pane_idx;
  char *label;
  total = window_count_panes(w);
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  colour = options_get_number(oo, "display-panes-colour");
  active_colour = options_get_number(oo, "display-panes-active-colour");
  if ((sx / total) < 24)
  {
    visible = sx / 24;
    if (visible == 0)
    {
      visible = 1;
    }
  }
  else
    visible = total;
  current = 0;
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    if ((&wp[wp_idx]) == w->active)
    {
      break;
    }
    current += 1;
  }

  if (current < visible)
  {
    start = 0;
    end = visible;
  }
  else
    if (current >= (total - visible))
  {
    start = total - visible;
    end = total;
  }
  else
  {
    start = current - (visible / 2);
    end = start + visible;
  }
  if (data->offset < (-((int) start)))
  {
    data->offset = -((int) start);
  }
  if (data->offset > ((int) (total - end)))
  {
    data->offset = (int) (total - end);
  }
  start += data->offset;
  end += data->offset;
  left = start != 0;
  right = end != total;
  if (((left && right) && (sx <= 6)) || ((left || right) && (sx <= 3)))
  {
    left = (right = 0);
  }
  if (left && right)
  {
    each = (sx - 6) / visible;
    remaining = (sx - 6) - (visible * each);
  }
  else
    if (left || right)
  {
    each = (sx - 3) / visible;
    remaining = (sx - 3) - (visible * each);
  }
  else
  {
    each = sx / visible;
    remaining = sx - (visible * each);
  }
  if (each == 0)
  {
    return;
  }
  if (left)
  {
    data->left = cx + 2;
    screen_write_cursormove(ctx, cx + 2, cy);
    screen_write_vline(ctx, sy, 0, 0);
    screen_write_cursormove(ctx, cx, cy + (sy / 2));
    screen_write_puts(ctx, &grid_default_cell, "<");
  }
  else
    data->left = -1;
  if (right)
  {
    data->right = (cx + sx) - 3;
    screen_write_cursormove(ctx, (cx + sx) - 3, cy);
    screen_write_vline(ctx, sy, 0, 0);
    screen_write_cursormove(ctx, (cx + sx) - 1, cy + (sy / 2));
    screen_write_puts(ctx, &grid_default_cell, ">");
  }
  else
    data->right = -1;
  data->start = start;
  data->end = end;
  data->each = each;
  i = (loop = 0);
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    helper_window_tree_draw_window_1(&loop, &width, &offset, &i, &gc, &pane_idx, w, ctx, sy, wp, wp_idx, cx, cy, each, start, end, remaining, colour, active_colour, left, label);
  }

}


/*** DEPENDENCIES:
extern const struct grid_cell grid_default_cell
----------------------------
struct window_tree_modedata
{
  struct window_pane *wp;
  int dead;
  int references;
  struct mode_tree_data *data;
  char *format;
  char *command;
  int squash_groups;
  struct window_tree_itemdata **item_list;
  u_int item_size;
  const char *entered;
  struct cmd_find_state fs;
  enum window_tree_type type;
  int offset;
  int left;
  int right;
  u_int start;
  u_int end;
  u_int each;
}
----------------------------
void helper_window_tree_draw_window_1(u_int * const loop_ref, u_int * const width_ref, u_int * const offset_ref, u_int * const i_ref, struct grid_cell * const gc_ref, int * const pane_idx_ref, struct window * const w, struct screen_write_ctx * const ctx, u_int sy, struct window_pane * const wp, unsigned int wp_idx, u_int cx, u_int cy, u_int each, u_int start, u_int end, u_int remaining, int colour, int active_colour, int left, char * const label)
{
  u_int loop = *loop_ref;
  u_int width = *width_ref;
  u_int offset = *offset_ref;
  u_int i = *i_ref;
  struct grid_cell gc = *gc_ref;
  int pane_idx = *pane_idx_ref;
  if (loop == end)
  {
    break;
  }
  if (loop < start)
  {
    loop += 1;
    continue;
  }
  if ((&wp[wp_idx]) == w->active)
  {
    gc.fg = active_colour;
  }
  else
    gc.fg = colour;
  if (left)
  {
    offset = 3 + (i * each);
  }
  else
    offset = i * each;
  if (loop == (end - 1))
  {
    width = each + remaining;
  }
  else
    width = each - 1;
  screen_write_cursormove(ctx, cx + offset, cy);
  screen_write_preview(ctx, &wp->base, width, sy);
  if (window_pane_index(wp, &pane_idx) != 0)
  {
    pane_idx = loop;
  }
  xasprintf(&label, " %u ", pane_idx);
  window_tree_draw_label(ctx, cx + offset, cy, each, sy, &gc, label);
  free(label);
  if (loop != (end - 1))
  {
    screen_write_cursormove(ctx, (cx + offset) + width, cy);
    screen_write_vline(ctx, sy, 0, 0);
  }
  loop += 1;
  i += 1;
  *loop_ref = loop;
  *width_ref = width;
  *offset_ref = offset;
  *i_ref = i;
  *gc_ref = gc;
  *pane_idx_ref = pane_idx;
}


----------------------------
void screen_write_cursormove(struct screen_write_ctx *ctx, u_int px, u_int py)
{
  struct screen *s = ctx->s;
  if (px > (s->grid->sx - 1))
  {
    px = s->grid->sx - 1;
  }
  if (py > (s->grid->sy - 1))
  {
    py = s->grid->sy - 1;
  }
  s->cx = px;
  s->cy = py;
}


----------------------------
None
----------------------------
void screen_write_vline(struct screen_write_ctx *ctx, u_int ny, int top, int bottom)
{
  struct screen *s = ctx->s;
  struct grid_cell gc;
  u_int cx;
  u_int cy;
  u_int i;
  cx = s->cx;
  cy = s->cy;
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  gc.attr |= 0x80;
  screen_write_putc(ctx, &gc, (top) ? ('w') : ('x'));
  for (i = 1; i < (ny - 1); i += 1)
  {
    screen_write_cursormove(ctx, cx, cy + i);
    screen_write_putc(ctx, &gc, 'x');
  }

  screen_write_cursormove(ctx, cx, (cy + ny) - 1);
  screen_write_putc(ctx, &gc, (bottom) ? ('v') : ('x'));
  screen_write_cursormove(ctx, cx, cy);
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
void screen_write_puts(struct screen_write_ctx *ctx, const struct grid_cell *gcp, const char *fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  screen_write_vnputs(ctx, -1, gcp, fmt, ap);
  ;
}


----------------------------
long long options_get_number(struct options *oo, const char *name)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_get(oo, name);
  if ((&o[o_idx]) == 0)
  {
    fatalx("missing option %s", name);
  }
  if (!((o->tableentry != 0) && ((((((o->tableentry->type == OPTIONS_TABLE_NUMBER) || (o->tableentry->type == OPTIONS_TABLE_KEY)) || (o->tableentry->type == OPTIONS_TABLE_COLOUR)) || (o->tableentry->type == OPTIONS_TABLE_ATTRIBUTES)) || (o->tableentry->type == OPTIONS_TABLE_FLAG)) || (o->tableentry->type == OPTIONS_TABLE_CHOICE))))
  {
    fatalx("option %s is not a number", name);
  }
  return o->number;
}


----------------------------
u_int window_count_panes(struct window *w)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int n;
  n = 0;
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    n += 1;
  }

  return n;
}


----------------------------
None
----------------------------
None
----------------------------
None
----------------------------
***/


// hint:  ['w_idx_ref is a mutable refrence to unsigned int', 'loop_ref is a mutable refrence to u_int', 'width_ref is a mutable refrence to u_int', 'offset_ref is a mutable refrence to u_int', 'i_ref is a mutable refrence to u_int', 'gc_ref is a mutable refrence to ']
void helper_window_tree_draw_session_1(unsigned int * const w_idx_ref, u_int * const loop_ref, u_int * const width_ref, u_int * const offset_ref, u_int * const i_ref, struct grid_cell * const gc_ref, struct session * const s, struct screen_write_ctx * const ctx, u_int sy, struct winlink * const wl, unsigned int wl_idx, struct window * const w, u_int cx, u_int cy, u_int each, u_int start, u_int end, u_int remaining, int colour, int active_colour, int left, char * const label)
{
  unsigned int w_idx = *w_idx_ref;
  u_int loop = *loop_ref;
  u_int width = *width_ref;
  u_int offset = *offset_ref;
  u_int i = *i_ref;
  struct grid_cell gc = *gc_ref;
  if (loop == end)
  {
    break;
  }
  if (loop < start)
  {
    loop += 1;
    continue;
  }
  w_idx = wl->window;
  if ((&wl[wl_idx]) == s->curw)
  {
    gc.fg = active_colour;
  }
  else
    gc.fg = colour;
  if (left)
  {
    offset = 3 + (i * each);
  }
  else
    offset = i * each;
  if (loop == (end - 1))
  {
    width = each + remaining;
  }
  else
    width = each - 1;
  screen_write_cursormove(ctx, cx + offset, cy);
  screen_write_preview(ctx, &w->active->base, width, sy);
  xasprintf(&label, " %u:%s ", wl->idx, w->name);
  if (strlen(label) > width)
  {
    xasprintf(&label, " %u ", wl->idx);
  }
  window_tree_draw_label(ctx, cx + offset, cy, width, sy, &gc, label);
  free(label);
  if (loop != (end - 1))
  {
    screen_write_cursormove(ctx, (cx + offset) + width, cy);
    screen_write_vline(ctx, sy, 0, 0);
  }
  loop += 1;
  i += 1;
  *w_idx_ref = w_idx;
  *loop_ref = loop;
  *width_ref = width;
  *offset_ref = offset;
  *i_ref = i;
  *gc_ref = gc;
}


/*** DEPENDENCIES:
void screen_write_cursormove(struct screen_write_ctx *ctx, u_int px, u_int py)
{
  struct screen *s = ctx->s;
  if (px > (s->grid->sx - 1))
  {
    px = s->grid->sx - 1;
  }
  if (py > (s->grid->sy - 1))
  {
    py = s->grid->sy - 1;
  }
  s->cx = px;
  s->cy = py;
}


----------------------------
None
----------------------------
void screen_write_vline(struct screen_write_ctx *ctx, u_int ny, int top, int bottom)
{
  struct screen *s = ctx->s;
  struct grid_cell gc;
  u_int cx;
  u_int cy;
  u_int i;
  cx = s->cx;
  cy = s->cy;
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  gc.attr |= 0x80;
  screen_write_putc(ctx, &gc, (top) ? ('w') : ('x'));
  for (i = 1; i < (ny - 1); i += 1)
  {
    screen_write_cursormove(ctx, cx, cy + i);
    screen_write_putc(ctx, &gc, 'x');
  }

  screen_write_cursormove(ctx, cx, (cy + ny) - 1);
  screen_write_putc(ctx, &gc, (bottom) ? ('v') : ('x'));
  screen_write_cursormove(ctx, cx, cy);
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
static void window_tree_draw_label(struct screen_write_ctx *ctx, u_int px, u_int py, u_int sx, u_int sy, const struct grid_cell *gc, const char *label)
{
  size_t len;
  u_int ox;
  u_int oy;
  len = strlen(label);
  if (((sx == 0) || (sy == 1)) || (len > sx))
  {
    return;
  }
  ox = ((sx - len) + 1) / 2;
  oy = (sy + 1) / 2;
  if (((ox > 1) && ((ox + len) < (sx - 1))) && (sy >= 3))
  {
    screen_write_cursormove(ctx, (px + ox) - 1, (py + oy) - 1);
    screen_write_box(ctx, len + 2, 3);
  }
  screen_write_cursormove(ctx, px + ox, py + oy);
  screen_write_puts(ctx, gc, "%s", label);
}


----------------------------
None
----------------------------
void screen_write_preview(struct screen_write_ctx *ctx, struct screen *src, u_int nx, u_int ny)
{
  struct screen *s = ctx->s;
  struct grid_cell gc;
  u_int cx;
  u_int cy;
  u_int px;
  u_int py;
  cx = s->cx;
  cy = s->cy;
  if (src->mode & 0x1)
  {
    px = src->cx;
    if (px < (nx / 3))
    {
      px = 0;
    }
    else
      px = px - (nx / 3);
    if ((px + nx) > src->grid->sx)
    {
      if (nx > src->grid->sx)
      {
        px = 0;
      }
      else
        px = src->grid->sx - nx;
    }
    py = src->cy;
    if (py < (ny / 3))
    {
      py = 0;
    }
    else
      py = py - (ny / 3);
    if ((py + ny) > src->grid->sy)
    {
      if (ny > src->grid->sy)
      {
        py = 0;
      }
      else
        py = src->grid->sy - ny;
    }
  }
  else
  {
    px = 0;
    py = 0;
  }
  screen_write_fast_copy(ctx, src, px, src->grid->hsize + py, nx, ny);
  if (src->mode & 0x1)
  {
    grid_view_get_cell(src->grid, src->cx, src->cy, &gc);
    gc.attr |= 0x10;
    screen_write_cursormove(ctx, cx + (src->cx - px), cy + (src->cy - py));
    screen_write_cell(ctx, &gc);
  }
}


----------------------------
None
----------------------------
***/


static void window_tree_draw_session(struct window_tree_modedata *data, struct session *s, struct screen_write_ctx *ctx, u_int sx, u_int sy)
{
  struct options *oo = s->options;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct window *w;
  unsigned int w_idx = 0;
  u_int cx = ctx->s->cx;
  u_int cy = ctx->s->cy;
  u_int loop;
  u_int total;
  u_int visible;
  u_int each;
  u_int width;
  u_int offset;
  u_int current;
  u_int start;
  u_int end;
  u_int remaining;
  u_int i;
  struct grid_cell gc;
  int colour;
  int active_colour;
  int left;
  int right;
  char *label;
  total = winlink_count(&s->windows);
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  colour = options_get_number(oo, "display-panes-colour");
  active_colour = options_get_number(oo, "display-panes-active-colour");
  if ((sx / total) < 24)
  {
    visible = sx / 24;
    if (visible == 0)
    {
      visible = 1;
    }
  }
  else
    visible = total;
  current = 0;
  for (wl_idx = winlinks_RB_MINMAX(&s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    if ((&wl[wl_idx]) == s->curw)
    {
      break;
    }
    current += 1;
  }

  if (current < visible)
  {
    start = 0;
    end = visible;
  }
  else
    if (current >= (total - visible))
  {
    start = total - visible;
    end = total;
  }
  else
  {
    start = current - (visible / 2);
    end = start + visible;
  }
  if (data->offset < (-((int) start)))
  {
    data->offset = -((int) start);
  }
  if (data->offset > ((int) (total - end)))
  {
    data->offset = (int) (total - end);
  }
  start += data->offset;
  end += data->offset;
  left = start != 0;
  right = end != total;
  if (((left && right) && (sx <= 6)) || ((left || right) && (sx <= 3)))
  {
    left = (right = 0);
  }
  if (left && right)
  {
    each = (sx - 6) / visible;
    remaining = (sx - 6) - (visible * each);
  }
  else
    if (left || right)
  {
    each = (sx - 3) / visible;
    remaining = (sx - 3) - (visible * each);
  }
  else
  {
    each = sx / visible;
    remaining = sx - (visible * each);
  }
  if (each == 0)
  {
    return;
  }
  if (left)
  {
    data->left = cx + 2;
    screen_write_cursormove(ctx, cx + 2, cy);
    screen_write_vline(ctx, sy, 0, 0);
    screen_write_cursormove(ctx, cx, cy + (sy / 2));
    screen_write_puts(ctx, &grid_default_cell, "<");
  }
  else
    data->left = -1;
  if (right)
  {
    data->right = (cx + sx) - 3;
    screen_write_cursormove(ctx, (cx + sx) - 3, cy);
    screen_write_vline(ctx, sy, 0, 0);
    screen_write_cursormove(ctx, (cx + sx) - 1, cy + (sy / 2));
    screen_write_puts(ctx, &grid_default_cell, ">");
  }
  else
    data->right = -1;
  data->start = start;
  data->end = end;
  data->each = each;
  i = (loop = 0);
  for (wl_idx = winlinks_RB_MINMAX(&s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    helper_window_tree_draw_session_1(&w_idx, &loop, &width, &offset, &i, &gc, s, ctx, sy, wl, wl_idx, w, cx, cy, each, start, end, remaining, colour, active_colour, left, label);
  }

}


/*** DEPENDENCIES:
void helper_window_tree_draw_session_1(unsigned int * const w_idx_ref, u_int * const loop_ref, u_int * const width_ref, u_int * const offset_ref, u_int * const i_ref, struct grid_cell * const gc_ref, struct session * const s, struct screen_write_ctx * const ctx, u_int sy, struct winlink * const wl, unsigned int wl_idx, struct window * const w, u_int cx, u_int cy, u_int each, u_int start, u_int end, u_int remaining, int colour, int active_colour, int left, char * const label)
{
  unsigned int w_idx = *w_idx_ref;
  u_int loop = *loop_ref;
  u_int width = *width_ref;
  u_int offset = *offset_ref;
  u_int i = *i_ref;
  struct grid_cell gc = *gc_ref;
  if (loop == end)
  {
    break;
  }
  if (loop < start)
  {
    loop += 1;
    continue;
  }
  w_idx = wl->window;
  if ((&wl[wl_idx]) == s->curw)
  {
    gc.fg = active_colour;
  }
  else
    gc.fg = colour;
  if (left)
  {
    offset = 3 + (i * each);
  }
  else
    offset = i * each;
  if (loop == (end - 1))
  {
    width = each + remaining;
  }
  else
    width = each - 1;
  screen_write_cursormove(ctx, cx + offset, cy);
  screen_write_preview(ctx, &w->active->base, width, sy);
  xasprintf(&label, " %u:%s ", wl->idx, w->name);
  if (strlen(label) > width)
  {
    xasprintf(&label, " %u ", wl->idx);
  }
  window_tree_draw_label(ctx, cx + offset, cy, width, sy, &gc, label);
  free(label);
  if (loop != (end - 1))
  {
    screen_write_cursormove(ctx, (cx + offset) + width, cy);
    screen_write_vline(ctx, sy, 0, 0);
  }
  loop += 1;
  i += 1;
  *w_idx_ref = w_idx;
  *loop_ref = loop;
  *width_ref = width;
  *offset_ref = offset;
  *i_ref = i;
  *gc_ref = gc;
}


----------------------------
struct window_tree_modedata
{
  struct window_pane *wp;
  int dead;
  int references;
  struct mode_tree_data *data;
  char *format;
  char *command;
  int squash_groups;
  struct window_tree_itemdata **item_list;
  u_int item_size;
  const char *entered;
  struct cmd_find_state fs;
  enum window_tree_type type;
  int offset;
  int left;
  int right;
  u_int start;
  u_int end;
  u_int each;
}
----------------------------
struct windows
{
  struct window *rbh_root;
}
----------------------------
void screen_write_cursormove(struct screen_write_ctx *ctx, u_int px, u_int py)
{
  struct screen *s = ctx->s;
  if (px > (s->grid->sx - 1))
  {
    px = s->grid->sx - 1;
  }
  if (py > (s->grid->sy - 1))
  {
    py = s->grid->sy - 1;
  }
  s->cx = px;
  s->cy = py;
}


----------------------------
None
----------------------------
u_int winlink_count(struct winlinks *wwl)
{
  struct winlink *wl;
  unsigned int wl_idx = 0;
  u_int n;
  n = 0;
  for (wl_idx = winlinks_RB_MINMAX(wwl, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    n += 1;
  }

  return n;
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
void screen_write_puts(struct screen_write_ctx *ctx, const struct grid_cell *gcp, const char *fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  screen_write_vnputs(ctx, -1, gcp, fmt, ap);
  ;
}


----------------------------
None
----------------------------
struct winlink *winlinks_RB_MINMAX(struct winlinks *head, int val)
{
  struct winlink *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct winlink *parent = 0;
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
extern const struct grid_cell grid_default_cell
----------------------------
struct winlink *winlinks_RB_NEXT(struct winlink *elm)
{
  unsigned int elm_idx = 0;
  if (elm->entry.rbe_right)
  {
    elm_idx = elm_idx->entry.rbe_right;
    while (elm->entry.rbe_left)
    {
      elm_idx = elm_idx->entry.rbe_left;
    }

  }
  else
  {
    if (elm->entry.rbe_parent && ((&elm[elm_idx]) == elm->entry.rbe_parent->entry.rbe_left))
    {
      elm_idx = elm_idx->entry.rbe_parent;
    }
    else
    {
      while (elm->entry.rbe_parent && ((&elm[elm_idx]) == elm->entry.rbe_parent->entry.rbe_right))
      {
        elm_idx = elm_idx->entry.rbe_parent;
      }

      elm_idx = elm_idx->entry.rbe_parent;
    }
  }
  return elm;
}


----------------------------
void screen_write_vline(struct screen_write_ctx *ctx, u_int ny, int top, int bottom)
{
  struct screen *s = ctx->s;
  struct grid_cell gc;
  u_int cx;
  u_int cy;
  u_int i;
  cx = s->cx;
  cy = s->cy;
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  gc.attr |= 0x80;
  screen_write_putc(ctx, &gc, (top) ? ('w') : ('x'));
  for (i = 1; i < (ny - 1); i += 1)
  {
    screen_write_cursormove(ctx, cx, cy + i);
    screen_write_putc(ctx, &gc, 'x');
  }

  screen_write_cursormove(ctx, cx, (cy + ny) - 1);
  screen_write_putc(ctx, &gc, (bottom) ? ('v') : ('x'));
  screen_write_cursormove(ctx, cx, cy);
}


----------------------------
long long options_get_number(struct options *oo, const char *name)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_get(oo, name);
  if ((&o[o_idx]) == 0)
  {
    fatalx("missing option %s", name);
  }
  if (!((o->tableentry != 0) && ((((((o->tableentry->type == OPTIONS_TABLE_NUMBER) || (o->tableentry->type == OPTIONS_TABLE_KEY)) || (o->tableentry->type == OPTIONS_TABLE_COLOUR)) || (o->tableentry->type == OPTIONS_TABLE_ATTRIBUTES)) || (o->tableentry->type == OPTIONS_TABLE_FLAG)) || (o->tableentry->type == OPTIONS_TABLE_CHOICE))))
  {
    fatalx("option %s is not a number", name);
  }
  return o->number;
}


----------------------------
None
----------------------------
None
----------------------------
***/


static void window_tree_draw(void *modedata, void *itemdata, struct screen_write_ctx *ctx, u_int sx, u_int sy)
{
  struct window_tree_itemdata *item = itemdata;
  struct session *sp;
  struct winlink *wlp;
  struct window_pane *wp;
  window_tree_pull_item(item, &sp, &wlp, &wp);
  if (wp == 0)
  {
    return;
  }
  switch (item->type)
  {
    case WINDOW_TREE_NONE:
    {
      break;
    }

    case WINDOW_TREE_SESSION:
    {
      window_tree_draw_session(modedata, sp, ctx, sx, sy);
      break;
    }

    case WINDOW_TREE_WINDOW:
    {
      window_tree_draw_window(modedata, sp, wlp->window, ctx, sx, sy);
      break;
    }

    case WINDOW_TREE_PANE:
    {
      screen_write_preview(ctx, &wp->base, sx, sy);
      break;
    }

  }

}


/*** DEPENDENCIES:
static void window_tree_pull_item(struct window_tree_itemdata *item, struct session **sp, struct winlink **wlp, struct window_pane **wp)
{
  *wp = 0;
  *wlp = 0;
  *sp = session_find_by_id(item->session);
  if ((*sp) == 0)
  {
    return;
  }
  if (item->type == WINDOW_TREE_SESSION)
  {
    *wlp = (*sp)->curw;
    *wp = (*wlp)->window->active;
    return;
  }
  *wlp = winlink_find_by_index(&(*sp)->windows, item->winlink);
  if ((*wlp) == 0)
  {
    *sp = 0;
    return;
  }
  if (item->type == WINDOW_TREE_WINDOW)
  {
    *wp = (*wlp)->window->active;
    return;
  }
  *wp = window_pane_find_by_id(item->pane);
  if (!window_has_pane((*wlp)->window, *wp))
  {
    *wp = 0;
  }
  if ((*wp) == 0)
  {
    *sp = 0;
    *wlp = 0;
    return;
  }
}


----------------------------
struct window_tree_itemdata
{
  enum window_tree_type type;
  int session;
  int winlink;
  int pane;
}
----------------------------
static void window_tree_draw_window(struct window_tree_modedata *data, struct session *s, struct window *w, struct screen_write_ctx *ctx, u_int sx, u_int sy)
{
  struct options *oo = s->options;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int cx = ctx->s->cx;
  u_int cy = ctx->s->cy;
  u_int loop;
  u_int total;
  u_int visible;
  u_int each;
  u_int width;
  u_int offset;
  u_int current;
  u_int start;
  u_int end;
  u_int remaining;
  u_int i;
  struct grid_cell gc;
  int colour;
  int active_colour;
  int left;
  int right;
  int pane_idx;
  char *label;
  total = window_count_panes(w);
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  colour = options_get_number(oo, "display-panes-colour");
  active_colour = options_get_number(oo, "display-panes-active-colour");
  if ((sx / total) < 24)
  {
    visible = sx / 24;
    if (visible == 0)
    {
      visible = 1;
    }
  }
  else
    visible = total;
  current = 0;
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    if ((&wp[wp_idx]) == w->active)
    {
      break;
    }
    current += 1;
  }

  if (current < visible)
  {
    start = 0;
    end = visible;
  }
  else
    if (current >= (total - visible))
  {
    start = total - visible;
    end = total;
  }
  else
  {
    start = current - (visible / 2);
    end = start + visible;
  }
  if (data->offset < (-((int) start)))
  {
    data->offset = -((int) start);
  }
  if (data->offset > ((int) (total - end)))
  {
    data->offset = (int) (total - end);
  }
  start += data->offset;
  end += data->offset;
  left = start != 0;
  right = end != total;
  if (((left && right) && (sx <= 6)) || ((left || right) && (sx <= 3)))
  {
    left = (right = 0);
  }
  if (left && right)
  {
    each = (sx - 6) / visible;
    remaining = (sx - 6) - (visible * each);
  }
  else
    if (left || right)
  {
    each = (sx - 3) / visible;
    remaining = (sx - 3) - (visible * each);
  }
  else
  {
    each = sx / visible;
    remaining = sx - (visible * each);
  }
  if (each == 0)
  {
    return;
  }
  if (left)
  {
    data->left = cx + 2;
    screen_write_cursormove(ctx, cx + 2, cy);
    screen_write_vline(ctx, sy, 0, 0);
    screen_write_cursormove(ctx, cx, cy + (sy / 2));
    screen_write_puts(ctx, &grid_default_cell, "<");
  }
  else
    data->left = -1;
  if (right)
  {
    data->right = (cx + sx) - 3;
    screen_write_cursormove(ctx, (cx + sx) - 3, cy);
    screen_write_vline(ctx, sy, 0, 0);
    screen_write_cursormove(ctx, (cx + sx) - 1, cy + (sy / 2));
    screen_write_puts(ctx, &grid_default_cell, ">");
  }
  else
    data->right = -1;
  data->start = start;
  data->end = end;
  data->each = each;
  i = (loop = 0);
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    helper_window_tree_draw_window_1(&loop, &width, &offset, &i, &gc, &pane_idx, w, ctx, sy, wp, wp_idx, cx, cy, each, start, end, remaining, colour, active_colour, left, label);
  }

}


----------------------------
None
----------------------------
void screen_write_preview(struct screen_write_ctx *ctx, struct screen *src, u_int nx, u_int ny)
{
  struct screen *s = ctx->s;
  struct grid_cell gc;
  u_int cx;
  u_int cy;
  u_int px;
  u_int py;
  cx = s->cx;
  cy = s->cy;
  if (src->mode & 0x1)
  {
    px = src->cx;
    if (px < (nx / 3))
    {
      px = 0;
    }
    else
      px = px - (nx / 3);
    if ((px + nx) > src->grid->sx)
    {
      if (nx > src->grid->sx)
      {
        px = 0;
      }
      else
        px = src->grid->sx - nx;
    }
    py = src->cy;
    if (py < (ny / 3))
    {
      py = 0;
    }
    else
      py = py - (ny / 3);
    if ((py + ny) > src->grid->sy)
    {
      if (ny > src->grid->sy)
      {
        py = 0;
      }
      else
        py = src->grid->sy - ny;
    }
  }
  else
  {
    px = 0;
    py = 0;
  }
  screen_write_fast_copy(ctx, src, px, src->grid->hsize + py, nx, ny);
  if (src->mode & 0x1)
  {
    grid_view_get_cell(src->grid, src->cx, src->cy, &gc);
    gc.attr |= 0x10;
    screen_write_cursormove(ctx, cx + (src->cx - px), cy + (src->cy - py));
    screen_write_cell(ctx, &gc);
  }
}


----------------------------
static void window_tree_draw_session(struct window_tree_modedata *data, struct session *s, struct screen_write_ctx *ctx, u_int sx, u_int sy)
{
  struct options *oo = s->options;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct window *w;
  unsigned int w_idx = 0;
  u_int cx = ctx->s->cx;
  u_int cy = ctx->s->cy;
  u_int loop;
  u_int total;
  u_int visible;
  u_int each;
  u_int width;
  u_int offset;
  u_int current;
  u_int start;
  u_int end;
  u_int remaining;
  u_int i;
  struct grid_cell gc;
  int colour;
  int active_colour;
  int left;
  int right;
  char *label;
  total = winlink_count(&s->windows);
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  colour = options_get_number(oo, "display-panes-colour");
  active_colour = options_get_number(oo, "display-panes-active-colour");
  if ((sx / total) < 24)
  {
    visible = sx / 24;
    if (visible == 0)
    {
      visible = 1;
    }
  }
  else
    visible = total;
  current = 0;
  for (wl_idx = winlinks_RB_MINMAX(&s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    if ((&wl[wl_idx]) == s->curw)
    {
      break;
    }
    current += 1;
  }

  if (current < visible)
  {
    start = 0;
    end = visible;
  }
  else
    if (current >= (total - visible))
  {
    start = total - visible;
    end = total;
  }
  else
  {
    start = current - (visible / 2);
    end = start + visible;
  }
  if (data->offset < (-((int) start)))
  {
    data->offset = -((int) start);
  }
  if (data->offset > ((int) (total - end)))
  {
    data->offset = (int) (total - end);
  }
  start += data->offset;
  end += data->offset;
  left = start != 0;
  right = end != total;
  if (((left && right) && (sx <= 6)) || ((left || right) && (sx <= 3)))
  {
    left = (right = 0);
  }
  if (left && right)
  {
    each = (sx - 6) / visible;
    remaining = (sx - 6) - (visible * each);
  }
  else
    if (left || right)
  {
    each = (sx - 3) / visible;
    remaining = (sx - 3) - (visible * each);
  }
  else
  {
    each = sx / visible;
    remaining = sx - (visible * each);
  }
  if (each == 0)
  {
    return;
  }
  if (left)
  {
    data->left = cx + 2;
    screen_write_cursormove(ctx, cx + 2, cy);
    screen_write_vline(ctx, sy, 0, 0);
    screen_write_cursormove(ctx, cx, cy + (sy / 2));
    screen_write_puts(ctx, &grid_default_cell, "<");
  }
  else
    data->left = -1;
  if (right)
  {
    data->right = (cx + sx) - 3;
    screen_write_cursormove(ctx, (cx + sx) - 3, cy);
    screen_write_vline(ctx, sy, 0, 0);
    screen_write_cursormove(ctx, (cx + sx) - 1, cy + (sy / 2));
    screen_write_puts(ctx, &grid_default_cell, ">");
  }
  else
    data->right = -1;
  data->start = start;
  data->end = end;
  data->each = each;
  i = (loop = 0);
  for (wl_idx = winlinks_RB_MINMAX(&s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    helper_window_tree_draw_session_1(&w_idx, &loop, &width, &offset, &i, &gc, s, ctx, sy, wl, wl_idx, w, cx, cy, each, start, end, remaining, colour, active_colour, left, label);
  }

}


----------------------------
None
----------------------------
***/


static void window_tree_build_pane(struct session *s, struct winlink *wl, struct window_pane *wp, void *modedata, struct mode_tree_item *parent)
{
  struct window_tree_modedata *data = modedata;
  struct window_tree_itemdata *item;
  unsigned int item_idx = 0;
  char *name;
  char *text;
  unsigned int text_idx = 0;
  u_int idx;
  window_pane_index(wp, &idx);
  item_idx = window_tree_add_item(data);
  item->type = WINDOW_TREE_PANE;
  item->session = s->id;
  item->winlink = wl->idx;
  item->pane = wp->id;
  text_idx = format_single(0, data->format, 0, s, wl, wp);
  xasprintf(&name, "%u", idx);
  mode_tree_add(data->data, parent, item, (uint64_t) wp, name, text, -1);
  free(text);
  free(name);
}


/*** DEPENDENCIES:
struct mode_tree_item *mode_tree_add(struct mode_tree_data *mtd, struct mode_tree_item *parent, void *itemdata, uint64_t tag, const char *name, const char *text, int expanded)
{
  struct mode_tree_item *mti;
  unsigned int mti_idx = 0;
  struct mode_tree_item *saved;
  unsigned int saved_idx = 0;
  log_debug("%s: %llu, %s %s", __func__, (unsigned long long) tag, name, text);
  mti_idx = xcalloc(1, sizeof(*mti_idx));
  mti->parent = parent;
  mti->itemdata = itemdata;
  mti->tag = tag;
  mti->name = xstrdup(name);
  mti->text = xstrdup(text);
  saved_idx = mode_tree_find_item(&mtd->saved_idx, tag);
  if ((&saved[saved_idx]) != 0)
  {
    if ((parent == 0) || ((parent != 0) && parent->expanded))
    {
      mti->tagged = saved->tagged;
    }
    mti->expanded = saved->expanded;
  }
  else
    if (expanded == (-1))
  {
    mti->expanded = 1;
  }
  else
    mti->expanded = expanded;
  do
  {
    (&mti->children)->tqh_first = 0;
    (&mti->children)->tqh_last = &(&mti->children)->tqh_first;
  }
  while (0);
  if (parent != 0)
  {
    do
    {
      mti->entry.tqe_next = 0;
      mti->entry.tqe_prev = (&parent->children)->tqh_last;
      *(&parent->children)->tqh_last = &mti[mti_idx];
      (&parent->children)->tqh_last = &mti->entry.tqe_next;
    }
    while (0);
  }
  else
    do
  {
    mti->entry.tqe_next = 0;
    mti->entry.tqe_prev = (&mtd->children)->tqh_last;
    *(&mtd->children)->tqh_last = &mti[mti_idx];
    (&mtd->children)->tqh_last = &mti->entry.tqe_next;
  }
  while (0);
  return mti;
}


----------------------------
struct window_tree_modedata
{
  struct window_pane *wp;
  int dead;
  int references;
  struct mode_tree_data *data;
  char *format;
  char *command;
  int squash_groups;
  struct window_tree_itemdata **item_list;
  u_int item_size;
  const char *entered;
  struct cmd_find_state fs;
  enum window_tree_type type;
  int offset;
  int left;
  int right;
  u_int start;
  u_int end;
  u_int each;
}
----------------------------
char *format_single(struct cmdq_item *item, const char *fmt, struct client *c, struct session *s, struct winlink *wl, struct window_pane *wp)
{
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  char *expanded;
  unsigned int expanded_idx = 0;
  if (item != 0)
  {
    ft_idx = format_create(item->client, item, 0, 0);
  }
  else
    ft_idx = format_create(0, item, 0, 0);
  format_defaults(ft, c, s, wl, wp);
  expanded_idx = format_expand(ft, fmt);
  format_free(ft);
  return expanded;
}


----------------------------
struct window_tree_itemdata
{
  enum window_tree_type type;
  int session;
  int winlink;
  int pane;
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
static struct window_tree_itemdata *window_tree_add_item(struct window_tree_modedata *data)
{
  struct window_tree_itemdata *item;
  unsigned int item_idx = 0;
  data->item_list = xreallocarray(data->item_list, data->item_size + 1, sizeof(*data->item_list));
  item_idx = (data->item_list[data->item_size++] = xcalloc(1, sizeof(*item_idx)));
  return item;
}


----------------------------
None
----------------------------
int window_pane_index(struct window_pane *wp, u_int *i)
{
  struct window_pane *wq;
  unsigned int wq_idx = 0;
  struct window *w = wp->window;
  *i = options_get_number(w->options, "pane-base-index");
  for (wq_idx = (&w->panes)->tqh_first; (&wq[wq_idx]) != 0; wq_idx = wq_idx->entry.tqe_next)
  {
    if (wp == (&wq[wq_idx]))
    {
      return 0;
    }
    *i += 1;
  }

  return -1;
}


----------------------------
None
----------------------------
***/


void helper_window_tree_key_1(struct client * const c, struct window_tree_modedata * const data, struct window_tree_itemdata * const item, char * const prompt, u_int idx, struct session * const ns, struct winlink * const nwl, struct window_pane * const nwp)
{
  window_tree_pull_item(item, &ns, &nwl, &nwp);
  switch (item->type)
  {
    case WINDOW_TREE_NONE:
    {
      break;
    }

    case WINDOW_TREE_SESSION:
    {
      if (ns == 0)
      {
        break;
      }
      xasprintf(&prompt, "Kill session %s? ", ns->name);
      break;
    }

    case WINDOW_TREE_WINDOW:
    {
      if (nwl == 0)
      {
        break;
      }
      xasprintf(&prompt, "Kill window %u? ", nwl->idx);
      break;
    }

    case WINDOW_TREE_PANE:
    {
      if ((nwp == 0) || (window_pane_index(nwp, &idx) != 0))
      {
        break;
      }
      xasprintf(&prompt, "Kill pane %u? ", idx);
      break;
    }

  }

  if (prompt == 0)
  {
    break;
  }
  data->references += 1;
  status_prompt_set(c, prompt, "", window_tree_kill_current_callback, window_tree_command_free, data, 0x1 | 0x8);
  free(prompt);
  break;
}


/*** DEPENDENCIES:
void status_prompt_set(struct client *c, const char *msg, const char *input, prompt_input_cb inputcb, prompt_free_cb freecb, void *data, int flags)
{
  unsigned int input_idx = 0;
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  time_t t;
  char *tmp;
  unsigned int tmp_idx = 0;
  char *cp;
  ft_idx = format_create(c, 0, 0, 0);
  format_defaults(ft, c, 0, 0, 0);
  t = time(0);
  if ((&input[input_idx]) == 0)
  {
    input_idx = "";
  }
  if (flags & 0x8)
  {
    tmp_idx = xstrdup(input);
  }
  else
    tmp_idx = format_expand_time(ft, input, t);
  status_message_clear(c);
  status_prompt_clear(c);
  if (c->status.old_status == 0)
  {
    c->status.old_status = xmalloc(sizeof(*c->status.old_status));
    memcpy(c->status.old_status, &c->status.status, sizeof(*c->status.old_status));
    screen_init(&c->status.status, c->tty.sx, 1, 0);
  }
  c->prompt_string = format_expand_time(ft, msg, t);
  c->prompt_buffer = utf8_fromcstr(tmp);
  c->prompt_index = utf8_strlen(c->prompt_buffer);
  c->prompt_inputcb = inputcb;
  c->prompt_freecb = freecb;
  c->prompt_data = data;
  c->prompt_hindex = 0;
  c->prompt_flags = flags;
  c->prompt_mode = PROMPT_ENTRY;
  if ((~flags) & 0x4)
  {
    c->tty.flags |= 0x1 | 0x2;
  }
  c->flags |= 0x10;
  if ((flags & 0x4) && (tmp[tmp_idx] != '\0'))
  {
    xasprintf(&cp, "=%s", tmp);
    c->prompt_inputcb(c, c->prompt_data, cp, 0);
    free(cp);
  }
  free(tmp);
  format_free(ft);
}


----------------------------
static void window_tree_pull_item(struct window_tree_itemdata *item, struct session **sp, struct winlink **wlp, struct window_pane **wp)
{
  *wp = 0;
  *wlp = 0;
  *sp = session_find_by_id(item->session);
  if ((*sp) == 0)
  {
    return;
  }
  if (item->type == WINDOW_TREE_SESSION)
  {
    *wlp = (*sp)->curw;
    *wp = (*wlp)->window->active;
    return;
  }
  *wlp = winlink_find_by_index(&(*sp)->windows, item->winlink);
  if ((*wlp) == 0)
  {
    *sp = 0;
    return;
  }
  if (item->type == WINDOW_TREE_WINDOW)
  {
    *wp = (*wlp)->window->active;
    return;
  }
  *wp = window_pane_find_by_id(item->pane);
  if (!window_has_pane((*wlp)->window, *wp))
  {
    *wp = 0;
  }
  if ((*wp) == 0)
  {
    *sp = 0;
    *wlp = 0;
    return;
  }
}


----------------------------
struct window_tree_modedata
{
  struct window_pane *wp;
  int dead;
  int references;
  struct mode_tree_data *data;
  char *format;
  char *command;
  int squash_groups;
  struct window_tree_itemdata **item_list;
  u_int item_size;
  const char *entered;
  struct cmd_find_state fs;
  enum window_tree_type type;
  int offset;
  int left;
  int right;
  u_int start;
  u_int end;
  u_int each;
}
----------------------------
struct window_tree_itemdata
{
  enum window_tree_type type;
  int session;
  int winlink;
  int pane;
}
----------------------------
static int window_tree_kill_current_callback(struct client *c, void *modedata, const char *s, int done)
{
  struct window_tree_modedata *data = modedata;
  struct mode_tree_data *mtd = data->data;
  if (((s == 0) || ((*s) == '\0')) || data->dead)
  {
    return 0;
  }
  if ((tolower((u_char) s[0]) != 'y') || (s[1] != '\0'))
  {
    return 0;
  }
  window_tree_kill_each(data, mode_tree_get_current(mtd), c, 0xffff00000000ULL);
  data->references += 1;
  cmdq_append(c, cmdq_get_callback1("window_tree_command_done", window_tree_command_done, data));
  return 0;
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
static void window_tree_command_free(void *modedata)
{
  struct window_tree_modedata *data = modedata;
  window_tree_destroy(data);
}


----------------------------
int window_pane_index(struct window_pane *wp, u_int *i)
{
  struct window_pane *wq;
  unsigned int wq_idx = 0;
  struct window *w = wp->window;
  *i = options_get_number(w->options, "pane-base-index");
  for (wq_idx = (&w->panes)->tqh_first; (&wq[wq_idx]) != 0; wq_idx = wq_idx->entry.tqe_next)
  {
    if (wp == (&wq[wq_idx]))
    {
      return 0;
    }
    *i += 1;
  }

  return -1;
}


----------------------------
None
----------------------------
***/


static int window_tree_build_window(struct session *s, struct winlink *wl, void *modedata, u_int sort_type, struct mode_tree_item *parent, const char *filter)
{
  struct window_tree_modedata *data = modedata;
  struct window_tree_itemdata *item;
  unsigned int item_idx = 0;
  struct mode_tree_item *mti;
  unsigned int mti_idx = 0;
  char *name;
  char *text;
  unsigned int text_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  struct window_pane **l;
  unsigned int l_idx = 0;
  u_int n;
  u_int i;
  int expanded;
  item_idx = window_tree_add_item(data);
  item->type = WINDOW_TREE_WINDOW;
  item->session = s->id;
  item->winlink = wl->idx;
  item->pane = -1;
  text_idx = format_single(0, data->format, 0, s, wl, 0);
  xasprintf(&name, "%u", wl->idx);
  if ((data->type == WINDOW_TREE_SESSION) || (data->type == WINDOW_TREE_WINDOW))
  {
    expanded = 0;
  }
  else
    expanded = 1;
  mti_idx = mode_tree_add(data->data, parent, item, (uint64_t) wl, name, text, expanded);
  free(text);
  free(name);
  if ((wp_idx = (&wl->window->panes)->tqh_first) == 0)
  {
    goto empty;
  }
  if (wp->entry.tqe_next == 0)
  {
    if (!window_tree_filter_pane(s, wl, wp, filter))
    {
      goto empty;
    }
    return 1;
  }
  l_idx = 0;
  n = 0;
  for (wp_idx = (&wl->window->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    if (!window_tree_filter_pane(s, wl, wp, filter))
    {
      continue;
    }
    l_idx = xreallocarray(l_idx, n + 1, sizeof(*l_idx));
    l[n + l_idx] = &wp[wp_idx];
    n += 1;
  }

  if (n == 0)
  {
    goto empty;
  }
  switch (sort_type)
  {
    case WINDOW_TREE_BY_INDEX:
    {
      break;
    }

    case WINDOW_TREE_BY_NAME:
    {
      break;
    }

    case WINDOW_TREE_BY_TIME:
    {
      qsort(l, n, sizeof(*(&l[l_idx])), window_tree_cmp_pane_time);
      break;
    }

  }

  for (i = 0; i < n; i += 1)
  {
    window_tree_build_pane(s, wl, l[i + l_idx], modedata, mti);
  }

  free(l);
  return 1;
  empty:
  window_tree_free_item(item);

  data->item_size -= 1;
  mode_tree_remove(data->data, mti);
  return 0;
}


/*** DEPENDENCIES:
struct mode_tree_item *mode_tree_add(struct mode_tree_data *mtd, struct mode_tree_item *parent, void *itemdata, uint64_t tag, const char *name, const char *text, int expanded)
{
  struct mode_tree_item *mti;
  unsigned int mti_idx = 0;
  struct mode_tree_item *saved;
  unsigned int saved_idx = 0;
  log_debug("%s: %llu, %s %s", __func__, (unsigned long long) tag, name, text);
  mti_idx = xcalloc(1, sizeof(*mti_idx));
  mti->parent = parent;
  mti->itemdata = itemdata;
  mti->tag = tag;
  mti->name = xstrdup(name);
  mti->text = xstrdup(text);
  saved_idx = mode_tree_find_item(&mtd->saved_idx, tag);
  if ((&saved[saved_idx]) != 0)
  {
    if ((parent == 0) || ((parent != 0) && parent->expanded))
    {
      mti->tagged = saved->tagged;
    }
    mti->expanded = saved->expanded;
  }
  else
    if (expanded == (-1))
  {
    mti->expanded = 1;
  }
  else
    mti->expanded = expanded;
  do
  {
    (&mti->children)->tqh_first = 0;
    (&mti->children)->tqh_last = &(&mti->children)->tqh_first;
  }
  while (0);
  if (parent != 0)
  {
    do
    {
      mti->entry.tqe_next = 0;
      mti->entry.tqe_prev = (&parent->children)->tqh_last;
      *(&parent->children)->tqh_last = &mti[mti_idx];
      (&parent->children)->tqh_last = &mti->entry.tqe_next;
    }
    while (0);
  }
  else
    do
  {
    mti->entry.tqe_next = 0;
    mti->entry.tqe_prev = (&mtd->children)->tqh_last;
    *(&mtd->children)->tqh_last = &mti[mti_idx];
    (&mtd->children)->tqh_last = &mti->entry.tqe_next;
  }
  while (0);
  return mti;
}


----------------------------
void mode_tree_remove(struct mode_tree_data *mtd, struct mode_tree_item *mti)
{
  struct mode_tree_item *parent = mti->parent;
  if (parent != 0)
  {
    do
    {
      if (mti->entry.tqe_next != 0)
      {
        mti->entry.tqe_next->entry.tqe_prev = mti->entry.tqe_prev;
      }
      else
        (&parent->children)->tqh_last = mti->entry.tqe_prev;
      *mti->entry.tqe_prev = mti->entry.tqe_next;
      ;
      ;
    }
    while (0);
  }
  else
    do
  {
    if (mti->entry.tqe_next != 0)
    {
      mti->entry.tqe_next->entry.tqe_prev = mti->entry.tqe_prev;
    }
    else
      (&mtd->children)->tqh_last = mti->entry.tqe_prev;
    *mti->entry.tqe_prev = mti->entry.tqe_next;
    ;
    ;
  }
  while (0);
  mode_tree_free_item(mti);
}


----------------------------
struct window_tree_modedata
{
  struct window_pane *wp;
  int dead;
  int references;
  struct mode_tree_data *data;
  char *format;
  char *command;
  int squash_groups;
  struct window_tree_itemdata **item_list;
  u_int item_size;
  const char *entered;
  struct cmd_find_state fs;
  enum window_tree_type type;
  int offset;
  int left;
  int right;
  u_int start;
  u_int end;
  u_int each;
}
----------------------------
static int window_tree_cmp_pane_time(const void *a0, const void *b0)
{
  const struct window_pane * const *a = a0;
  const struct window_pane * const *b = b0;
  if ((*a)->active_point < (*b)->active_point)
  {
    return -1;
  }
  if ((*a)->active_point > (*b)->active_point)
  {
    return 1;
  }
  return 0;
}


----------------------------
void *xreallocarray(void *ptr, size_t nmemb, size_t size)
{
  void *new_ptr;
  unsigned int new_ptr_idx = 0;
  if ((nmemb == 0) || (size == 0))
  {
    fatalx("xreallocarray: zero size");
  }
  new_ptr_idx = reallocarray(ptr, nmemb, size);
  if ((&new_ptr[new_ptr_idx]) == 0)
  {
    fatalx("xreallocarray: allocating %zu * %zu bytes: %s", nmemb, size, strerror(errno));
  }
  return new_ptr;
}


----------------------------
char *format_single(struct cmdq_item *item, const char *fmt, struct client *c, struct session *s, struct winlink *wl, struct window_pane *wp)
{
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  char *expanded;
  unsigned int expanded_idx = 0;
  if (item != 0)
  {
    ft_idx = format_create(item->client, item, 0, 0);
  }
  else
    ft_idx = format_create(0, item, 0, 0);
  format_defaults(ft, c, s, wl, wp);
  expanded_idx = format_expand(ft, fmt);
  format_free(ft);
  return expanded;
}


----------------------------
struct window_tree_itemdata
{
  enum window_tree_type type;
  int session;
  int winlink;
  int pane;
}
----------------------------
static void window_tree_build_pane(struct session *s, struct winlink *wl, struct window_pane *wp, void *modedata, struct mode_tree_item *parent)
{
  struct window_tree_modedata *data = modedata;
  struct window_tree_itemdata *item;
  unsigned int item_idx = 0;
  char *name;
  char *text;
  unsigned int text_idx = 0;
  u_int idx;
  window_pane_index(wp, &idx);
  item_idx = window_tree_add_item(data);
  item->type = WINDOW_TREE_PANE;
  item->session = s->id;
  item->winlink = wl->idx;
  item->pane = wp->id;
  text_idx = format_single(0, data->format, 0, s, wl, wp);
  xasprintf(&name, "%u", idx);
  mode_tree_add(data->data, parent, item, (uint64_t) wp, name, text, -1);
  free(text);
  free(name);
}


----------------------------
static int window_tree_filter_pane(struct session *s, struct winlink *wl, struct window_pane *wp, const char *filter)
{
  char *cp;
  unsigned int cp_idx = 0;
  int result;
  if (filter == 0)
  {
    return 1;
  }
  cp_idx = format_single(0, filter, 0, s, wl, wp);
  result = format_true(cp);
  free(cp);
  return result;
}


----------------------------
static void window_tree_free_item(struct window_tree_itemdata *item)
{
  free(item);
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
static struct window_tree_itemdata *window_tree_add_item(struct window_tree_modedata *data)
{
  struct window_tree_itemdata *item;
  unsigned int item_idx = 0;
  data->item_list = xreallocarray(data->item_list, data->item_size + 1, sizeof(*data->item_list));
  item_idx = (data->item_list[data->item_size++] = xcalloc(1, sizeof(*item_idx)));
  return item;
}


----------------------------
None
----------------------------
None
----------------------------
***/


static void window_tree_build_session(struct session *s, void *modedata, u_int sort_type, const char *filter)
{
  struct window_tree_modedata *data = modedata;
  struct window_tree_itemdata *item;
  unsigned int item_idx = 0;
  struct mode_tree_item *mti;
  unsigned int mti_idx = 0;
  char *text;
  unsigned int text_idx = 0;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct winlink **l;
  unsigned int l_idx = 0;
  u_int n;
  u_int i;
  u_int empty;
  int expanded;
  item_idx = window_tree_add_item(data);
  item->type = WINDOW_TREE_SESSION;
  item->session = s->id;
  item->winlink = -1;
  item->pane = -1;
  text_idx = format_single(0, data->format, 0, s, 0, 0);
  if (data->type == WINDOW_TREE_SESSION)
  {
    expanded = 0;
  }
  else
    expanded = 1;
  mti_idx = mode_tree_add(data->data, 0, item, (uint64_t) s, s->name, text, expanded);
  free(text);
  l_idx = 0;
  n = 0;
  for (wl_idx = winlinks_RB_MINMAX(&s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    l_idx = xreallocarray(l_idx, n + 1, sizeof(*l_idx));
    l[n + l_idx] = &wl[wl_idx];
    n += 1;
  }

  switch (sort_type)
  {
    case WINDOW_TREE_BY_INDEX:
    {
      break;
    }

    case WINDOW_TREE_BY_NAME:
    {
      qsort(l, n, sizeof(*(&l[l_idx])), window_tree_cmp_window_name);
      break;
    }

    case WINDOW_TREE_BY_TIME:
    {
      qsort(l, n, sizeof(*(&l[l_idx])), window_tree_cmp_window_time);
      break;
    }

  }

  empty = 0;
  for (i = 0; i < n; i += 1)
  {
    if (!window_tree_build_window(s, l[i + l_idx], modedata, sort_type, mti, filter))
    {
      empty += 1;
    }
  }

  if (empty == n)
  {
    window_tree_free_item(item);
    data->item_size -= 1;
    mode_tree_remove(data->data, mti);
  }
  free(l);
}


/*** DEPENDENCIES:
static int window_tree_cmp_window_time(const void *a0, const void *b0)
{
  const struct winlink * const *a = a0;
  const struct winlink * const *b = b0;
  if (((&(*a)->window->activity_time)->tv_sec == (&(*b)->window->activity_time)->tv_sec) ? ((&(*a)->window->activity_time)->tv_usec > (&(*b)->window->activity_time)->tv_usec) : ((&(*a)->window->activity_time)->tv_sec > (&(*b)->window->activity_time)->tv_sec))
  {
    return -1;
  }
  if (((&(*a)->window->activity_time)->tv_sec == (&(*b)->window->activity_time)->tv_sec) ? ((&(*a)->window->activity_time)->tv_usec < (&(*b)->window->activity_time)->tv_usec) : ((&(*a)->window->activity_time)->tv_sec < (&(*b)->window->activity_time)->tv_sec))
  {
    return 1;
  }
  return strcmp((*a)->window->name, (*b)->window->name);
}


----------------------------
struct mode_tree_item *mode_tree_add(struct mode_tree_data *mtd, struct mode_tree_item *parent, void *itemdata, uint64_t tag, const char *name, const char *text, int expanded)
{
  struct mode_tree_item *mti;
  unsigned int mti_idx = 0;
  struct mode_tree_item *saved;
  unsigned int saved_idx = 0;
  log_debug("%s: %llu, %s %s", __func__, (unsigned long long) tag, name, text);
  mti_idx = xcalloc(1, sizeof(*mti_idx));
  mti->parent = parent;
  mti->itemdata = itemdata;
  mti->tag = tag;
  mti->name = xstrdup(name);
  mti->text = xstrdup(text);
  saved_idx = mode_tree_find_item(&mtd->saved_idx, tag);
  if ((&saved[saved_idx]) != 0)
  {
    if ((parent == 0) || ((parent != 0) && parent->expanded))
    {
      mti->tagged = saved->tagged;
    }
    mti->expanded = saved->expanded;
  }
  else
    if (expanded == (-1))
  {
    mti->expanded = 1;
  }
  else
    mti->expanded = expanded;
  do
  {
    (&mti->children)->tqh_first = 0;
    (&mti->children)->tqh_last = &(&mti->children)->tqh_first;
  }
  while (0);
  if (parent != 0)
  {
    do
    {
      mti->entry.tqe_next = 0;
      mti->entry.tqe_prev = (&parent->children)->tqh_last;
      *(&parent->children)->tqh_last = &mti[mti_idx];
      (&parent->children)->tqh_last = &mti->entry.tqe_next;
    }
    while (0);
  }
  else
    do
  {
    mti->entry.tqe_next = 0;
    mti->entry.tqe_prev = (&mtd->children)->tqh_last;
    *(&mtd->children)->tqh_last = &mti[mti_idx];
    (&mtd->children)->tqh_last = &mti->entry.tqe_next;
  }
  while (0);
  return mti;
}


----------------------------
void mode_tree_remove(struct mode_tree_data *mtd, struct mode_tree_item *mti)
{
  struct mode_tree_item *parent = mti->parent;
  if (parent != 0)
  {
    do
    {
      if (mti->entry.tqe_next != 0)
      {
        mti->entry.tqe_next->entry.tqe_prev = mti->entry.tqe_prev;
      }
      else
        (&parent->children)->tqh_last = mti->entry.tqe_prev;
      *mti->entry.tqe_prev = mti->entry.tqe_next;
      ;
      ;
    }
    while (0);
  }
  else
    do
  {
    if (mti->entry.tqe_next != 0)
    {
      mti->entry.tqe_next->entry.tqe_prev = mti->entry.tqe_prev;
    }
    else
      (&mtd->children)->tqh_last = mti->entry.tqe_prev;
    *mti->entry.tqe_prev = mti->entry.tqe_next;
    ;
    ;
  }
  while (0);
  mode_tree_free_item(mti);
}


----------------------------
struct window_tree_modedata
{
  struct window_pane *wp;
  int dead;
  int references;
  struct mode_tree_data *data;
  char *format;
  char *command;
  int squash_groups;
  struct window_tree_itemdata **item_list;
  u_int item_size;
  const char *entered;
  struct cmd_find_state fs;
  enum window_tree_type type;
  int offset;
  int left;
  int right;
  u_int start;
  u_int end;
  u_int each;
}
----------------------------
struct windows
{
  struct window *rbh_root;
}
----------------------------
void *xreallocarray(void *ptr, size_t nmemb, size_t size)
{
  void *new_ptr;
  unsigned int new_ptr_idx = 0;
  if ((nmemb == 0) || (size == 0))
  {
    fatalx("xreallocarray: zero size");
  }
  new_ptr_idx = reallocarray(ptr, nmemb, size);
  if ((&new_ptr[new_ptr_idx]) == 0)
  {
    fatalx("xreallocarray: allocating %zu * %zu bytes: %s", nmemb, size, strerror(errno));
  }
  return new_ptr;
}


----------------------------
static void window_tree_free_item(struct window_tree_itemdata *item)
{
  free(item);
}


----------------------------
None
----------------------------
struct winlink *winlinks_RB_MINMAX(struct winlinks *head, int val)
{
  struct winlink *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  struct winlink *parent = 0;
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
static int window_tree_cmp_window_name(const void *a0, const void *b0)
{
  const struct winlink * const *a = a0;
  const struct winlink * const *b = b0;
  return strcmp((*a)->window->name, (*b)->window->name);
}


----------------------------
struct winlink *winlinks_RB_NEXT(struct winlink *elm)
{
  unsigned int elm_idx = 0;
  if (elm->entry.rbe_right)
  {
    elm_idx = elm_idx->entry.rbe_right;
    while (elm->entry.rbe_left)
    {
      elm_idx = elm_idx->entry.rbe_left;
    }

  }
  else
  {
    if (elm->entry.rbe_parent && ((&elm[elm_idx]) == elm->entry.rbe_parent->entry.rbe_left))
    {
      elm_idx = elm_idx->entry.rbe_parent;
    }
    else
    {
      while (elm->entry.rbe_parent && ((&elm[elm_idx]) == elm->entry.rbe_parent->entry.rbe_right))
      {
        elm_idx = elm_idx->entry.rbe_parent;
      }

      elm_idx = elm_idx->entry.rbe_parent;
    }
  }
  return elm;
}


----------------------------
char *format_single(struct cmdq_item *item, const char *fmt, struct client *c, struct session *s, struct winlink *wl, struct window_pane *wp)
{
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  char *expanded;
  unsigned int expanded_idx = 0;
  if (item != 0)
  {
    ft_idx = format_create(item->client, item, 0, 0);
  }
  else
    ft_idx = format_create(0, item, 0, 0);
  format_defaults(ft, c, s, wl, wp);
  expanded_idx = format_expand(ft, fmt);
  format_free(ft);
  return expanded;
}


----------------------------
struct window_tree_itemdata
{
  enum window_tree_type type;
  int session;
  int winlink;
  int pane;
}
----------------------------
static int window_tree_build_window(struct session *s, struct winlink *wl, void *modedata, u_int sort_type, struct mode_tree_item *parent, const char *filter)
{
  struct window_tree_modedata *data = modedata;
  struct window_tree_itemdata *item;
  unsigned int item_idx = 0;
  struct mode_tree_item *mti;
  unsigned int mti_idx = 0;
  char *name;
  char *text;
  unsigned int text_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  struct window_pane **l;
  unsigned int l_idx = 0;
  u_int n;
  u_int i;
  int expanded;
  item_idx = window_tree_add_item(data);
  item->type = WINDOW_TREE_WINDOW;
  item->session = s->id;
  item->winlink = wl->idx;
  item->pane = -1;
  text_idx = format_single(0, data->format, 0, s, wl, 0);
  xasprintf(&name, "%u", wl->idx);
  if ((data->type == WINDOW_TREE_SESSION) || (data->type == WINDOW_TREE_WINDOW))
  {
    expanded = 0;
  }
  else
    expanded = 1;
  mti_idx = mode_tree_add(data->data, parent, item, (uint64_t) wl, name, text, expanded);
  free(text);
  free(name);
  if ((wp_idx = (&wl->window->panes)->tqh_first) == 0)
  {
    goto empty;
  }
  if (wp->entry.tqe_next == 0)
  {
    if (!window_tree_filter_pane(s, wl, wp, filter))
    {
      goto empty;
    }
    return 1;
  }
  l_idx = 0;
  n = 0;
  for (wp_idx = (&wl->window->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    if (!window_tree_filter_pane(s, wl, wp, filter))
    {
      continue;
    }
    l_idx = xreallocarray(l_idx, n + 1, sizeof(*l_idx));
    l[n + l_idx] = &wp[wp_idx];
    n += 1;
  }

  if (n == 0)
  {
    goto empty;
  }
  switch (sort_type)
  {
    case WINDOW_TREE_BY_INDEX:
    {
      break;
    }

    case WINDOW_TREE_BY_NAME:
    {
      break;
    }

    case WINDOW_TREE_BY_TIME:
    {
      qsort(l, n, sizeof(*(&l[l_idx])), window_tree_cmp_pane_time);
      break;
    }

  }

  for (i = 0; i < n; i += 1)
  {
    window_tree_build_pane(s, wl, l[i + l_idx], modedata, mti);
  }

  free(l);
  return 1;
  empty:
  window_tree_free_item(item);

  data->item_size -= 1;
  mode_tree_remove(data->data, mti);
  return 0;
}


----------------------------
static struct window_tree_itemdata *window_tree_add_item(struct window_tree_modedata *data)
{
  struct window_tree_itemdata *item;
  unsigned int item_idx = 0;
  data->item_list = xreallocarray(data->item_list, data->item_size + 1, sizeof(*data->item_list));
  item_idx = (data->item_list[data->item_size++] = xcalloc(1, sizeof(*item_idx)));
  return item;
}


----------------------------
None
----------------------------
***/


static void window_tree_build(void *modedata, u_int sort_type, uint64_t *tag, const char *filter)
{
  struct window_tree_modedata *data = modedata;
  struct session *s;
  unsigned int s_idx = 0;
  struct session **l;
  unsigned int l_idx = 0;
  struct session_group *sg;
  unsigned int sg_idx = 0;
  struct session_group *current;
  unsigned int current_idx = 0;
  u_int n;
  u_int i;
  current_idx = session_group_contains(data->fs.s);
  for (i = 0; i < data->item_size; i += 1)
  {
    window_tree_free_item(data->item_list[i]);
  }

  free(data->item_list);
  data->item_list = 0;
  data->item_size = 0;
  l_idx = 0;
  n = 0;
  for (s_idx = sessions_RB_MINMAX(&sessions, -1); (&s[s_idx]) != 0; s_idx = sessions_RB_NEXT(s_idx))
  {
    if (data->squash_groups && ((sg_idx = session_group_contains(s)) != 0))
    {
      if ((((&sg[sg_idx]) == (&current[current_idx])) && ((&s[s_idx]) != data->fs.s)) || (((&sg[sg_idx]) != (&current[current_idx])) && ((&s[s_idx]) != (&sg->sessions)->tqh_first)))
      {
        continue;
      }
    }
    l_idx = xreallocarray(l_idx, n + 1, sizeof(*l_idx));
    l[n + l_idx] = &s[s_idx];
    n += 1;
  }

  switch (sort_type)
  {
    case WINDOW_TREE_BY_INDEX:
    {
      break;
    }

    case WINDOW_TREE_BY_NAME:
    {
      qsort(l, n, sizeof(*(&l[l_idx])), window_tree_cmp_session_name);
      break;
    }

    case WINDOW_TREE_BY_TIME:
    {
      qsort(l, n, sizeof(*(&l[l_idx])), window_tree_cmp_session_time);
      break;
    }

  }

  for (i = 0; i < n; i += 1)
  {
    window_tree_build_session(l[i + l_idx], modedata, sort_type, filter);
  }

  free(l);
  switch (data->type)
  {
    case WINDOW_TREE_NONE:
    {
      break;
    }

    case WINDOW_TREE_SESSION:
    {
      *tag = (uint64_t) data->fs.s;
      break;
    }

    case WINDOW_TREE_WINDOW:
    {
      *tag = (uint64_t) data->fs.wl;
      break;
    }

    case WINDOW_TREE_PANE:
    {
      if (window_count_panes(data->fs.wl->window) == 1)
      {
        *tag = (uint64_t) data->fs.wl;
      }
      else
        *tag = (uint64_t) data->fs.wp;
      break;
    }

  }

}


/*** DEPENDENCIES:
struct session_group *session_group_contains(struct session *target)
{
  struct session_group *sg;
  unsigned int sg_idx = 0;
  struct session *s;
  unsigned int s_idx = 0;
  for (sg_idx = session_groups_RB_MINMAX(&session_groups, -1); (&sg[sg_idx]) != 0; sg_idx = session_groups_RB_NEXT(sg_idx))
  {
    for (s_idx = (&sg->sessions)->tqh_first; (&s[s_idx]) != 0; s_idx = s_idx->gentry.tqe_next)
    {
      if ((&s[s_idx]) == target)
      {
        return sg;
      }
    }

  }

  return 0;
}


----------------------------
static int window_tree_cmp_session_time(const void *a0, const void *b0)
{
  const struct session * const *a = a0;
  const struct session * const *b = b0;
  if (((&(*a)->activity_time)->tv_sec == (&(*b)->activity_time)->tv_sec) ? ((&(*a)->activity_time)->tv_usec > (&(*b)->activity_time)->tv_usec) : ((&(*a)->activity_time)->tv_sec > (&(*b)->activity_time)->tv_sec))
  {
    return -1;
  }
  if (((&(*a)->activity_time)->tv_sec == (&(*b)->activity_time)->tv_sec) ? ((&(*a)->activity_time)->tv_usec < (&(*b)->activity_time)->tv_usec) : ((&(*a)->activity_time)->tv_sec < (&(*b)->activity_time)->tv_sec))
  {
    return 1;
  }
  return strcmp((*a)->name, (*b)->name);
}


----------------------------
struct window_tree_modedata
{
  struct window_pane *wp;
  int dead;
  int references;
  struct mode_tree_data *data;
  char *format;
  char *command;
  int squash_groups;
  struct window_tree_itemdata **item_list;
  u_int item_size;
  const char *entered;
  struct cmd_find_state fs;
  enum window_tree_type type;
  int offset;
  int left;
  int right;
  u_int start;
  u_int end;
  u_int each;
}
----------------------------
static void window_tree_build_session(struct session *s, void *modedata, u_int sort_type, const char *filter)
{
  struct window_tree_modedata *data = modedata;
  struct window_tree_itemdata *item;
  unsigned int item_idx = 0;
  struct mode_tree_item *mti;
  unsigned int mti_idx = 0;
  char *text;
  unsigned int text_idx = 0;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct winlink **l;
  unsigned int l_idx = 0;
  u_int n;
  u_int i;
  u_int empty;
  int expanded;
  item_idx = window_tree_add_item(data);
  item->type = WINDOW_TREE_SESSION;
  item->session = s->id;
  item->winlink = -1;
  item->pane = -1;
  text_idx = format_single(0, data->format, 0, s, 0, 0);
  if (data->type == WINDOW_TREE_SESSION)
  {
    expanded = 0;
  }
  else
    expanded = 1;
  mti_idx = mode_tree_add(data->data, 0, item, (uint64_t) s, s->name, text, expanded);
  free(text);
  l_idx = 0;
  n = 0;
  for (wl_idx = winlinks_RB_MINMAX(&s->windows, -1); (&wl[wl_idx]) != 0; wl_idx = winlinks_RB_NEXT(wl_idx))
  {
    l_idx = xreallocarray(l_idx, n + 1, sizeof(*l_idx));
    l[n + l_idx] = &wl[wl_idx];
    n += 1;
  }

  switch (sort_type)
  {
    case WINDOW_TREE_BY_INDEX:
    {
      break;
    }

    case WINDOW_TREE_BY_NAME:
    {
      qsort(l, n, sizeof(*(&l[l_idx])), window_tree_cmp_window_name);
      break;
    }

    case WINDOW_TREE_BY_TIME:
    {
      qsort(l, n, sizeof(*(&l[l_idx])), window_tree_cmp_window_time);
      break;
    }

  }

  empty = 0;
  for (i = 0; i < n; i += 1)
  {
    if (!window_tree_build_window(s, l[i + l_idx], modedata, sort_type, mti, filter))
    {
      empty += 1;
    }
  }

  if (empty == n)
  {
    window_tree_free_item(item);
    data->item_size -= 1;
    mode_tree_remove(data->data, mti);
  }
  free(l);
}


----------------------------
void *xreallocarray(void *ptr, size_t nmemb, size_t size)
{
  void *new_ptr;
  unsigned int new_ptr_idx = 0;
  if ((nmemb == 0) || (size == 0))
  {
    fatalx("xreallocarray: zero size");
  }
  new_ptr_idx = reallocarray(ptr, nmemb, size);
  if ((&new_ptr[new_ptr_idx]) == 0)
  {
    fatalx("xreallocarray: allocating %zu * %zu bytes: %s", nmemb, size, strerror(errno));
  }
  return new_ptr;
}


----------------------------
struct session *sessions_RB_NEXT(struct session *elm)
{
  unsigned int elm_idx = 0;
  if (elm->entry.rbe_right)
  {
    elm_idx = elm_idx->entry.rbe_right;
    while (elm->entry.rbe_left)
    {
      elm_idx = elm_idx->entry.rbe_left;
    }

  }
  else
  {
    if (elm->entry.rbe_parent && ((&elm[elm_idx]) == elm->entry.rbe_parent->entry.rbe_left))
    {
      elm_idx = elm_idx->entry.rbe_parent;
    }
    else
    {
      while (elm->entry.rbe_parent && ((&elm[elm_idx]) == elm->entry.rbe_parent->entry.rbe_right))
      {
        elm_idx = elm_idx->entry.rbe_parent;
      }

      elm_idx = elm_idx->entry.rbe_parent;
    }
  }
  return elm;
}


----------------------------
static int window_tree_cmp_session_name(const void *a0, const void *b0)
{
  const struct session * const *a = a0;
  const struct session * const *b = b0;
  return strcmp((*a)->name, (*b)->name);
}


----------------------------
static void window_tree_free_item(struct window_tree_itemdata *item)
{
  free(item);
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
u_int window_count_panes(struct window *w)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int n;
  n = 0;
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    n += 1;
  }

  return n;
}


----------------------------
struct sessions
{
  struct session *rbh_root;
}
----------------------------
struct session_group
{
  const char *name;
  struct 
  {
    struct session *tqh_first;
    struct session **tqh_last;
  } sessions;
  struct 
  {
    struct session_group *rbe_left;
    struct session_group *rbe_right;
    struct session_group *rbe_parent;
    int rbe_color;
  } entry;
}
----------------------------
None
----------------------------
***/


static struct screen *window_tree_init(struct window_pane *wp, struct cmd_find_state *fs, struct args *args)
{
  struct window_tree_modedata *data;
  struct screen *s;
  wp->modedata = (data = xcalloc(1, sizeof(*data)));
  if (args_has(args, 's'))
  {
    data->type = WINDOW_TREE_SESSION;
  }
  else
    if (args_has(args, 'w'))
  {
    data->type = WINDOW_TREE_WINDOW;
  }
  else
    data->type = WINDOW_TREE_PANE;
  memcpy(&data->fs, fs, sizeof(data->fs));
  data->wp = wp;
  data->references = 1;
  if ((args == 0) || (!args_has(args, 'F')))
  {
    data->format = xstrdup("#{?pane_format,#{pane_current_command} \"#{pane_title}\",#{?window_format,#{window_name}#{window_flags} (#{window_panes} panes)#{?#{==:#{window_panes},1}, \"#{pane_title}\",},#{session_windows} windows#{?session_grouped, (group #{session_group}: #{session_group_list}),}#{?session_attached, (attached),}}}");
  }
  else
    data->format = xstrdup(args_get(args, 'F'));
  if ((args == 0) || (args->argc == 0))
  {
    data->command = xstrdup("switch-client -t '%%'");
  }
  else
    data->command = xstrdup(args->argv[0]);
  data->squash_groups = !args_has(args, 'G');
  data->data = mode_tree_start(wp, args, window_tree_build, window_tree_draw, window_tree_search, data, window_tree_sort_list, (sizeof(window_tree_sort_list)) / (sizeof(window_tree_sort_list[0])), &s);
  mode_tree_zoom(data->data, args);
  mode_tree_build(data->data);
  mode_tree_draw(data->data);
  data->type = WINDOW_TREE_NONE;
  return s;
}


/*** DEPENDENCIES:
static int window_tree_search(void *modedata, void *itemdata, const char *ss)
{
  struct window_tree_itemdata *item = itemdata;
  struct session *s;
  struct winlink *wl;
  struct window_pane *wp;
  const char *cmd;
  unsigned int cmd_idx = 0;
  window_tree_pull_item(item, &s, &wl, &wp);
  switch (item->type)
  {
    case WINDOW_TREE_NONE:
    {
      return 0;
    }

    case WINDOW_TREE_SESSION:
    {
      if (s == 0)
      {
        return 0;
      }
      return strstr(s->name, ss) != 0;
    }

    case WINDOW_TREE_WINDOW:
    {
      if ((s == 0) || (wl == 0))
      {
        return 0;
      }
      return strstr(wl->window->name, ss) != 0;
    }

    case WINDOW_TREE_PANE:
    {
      if (((s == 0) || (wl == 0)) || (wp == 0))
      {
        break;
      }
      cmd_idx = osdep_get_name(wp->fd, wp->tty);
      if (((&cmd[cmd_idx]) == 0) || (cmd[cmd_idx] == '\0'))
      {
        return 0;
      }
      return strstr(cmd, ss) != 0;
    }

  }

  return 0;
}


----------------------------
struct window_tree_modedata
{
  struct window_pane *wp;
  int dead;
  int references;
  struct mode_tree_data *data;
  char *format;
  char *command;
  int squash_groups;
  struct window_tree_itemdata **item_list;
  u_int item_size;
  const char *entered;
  struct cmd_find_state fs;
  enum window_tree_type type;
  int offset;
  int left;
  int right;
  u_int start;
  u_int end;
  u_int each;
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
static void window_tree_build(void *modedata, u_int sort_type, uint64_t *tag, const char *filter)
{
  struct window_tree_modedata *data = modedata;
  struct session *s;
  unsigned int s_idx = 0;
  struct session **l;
  unsigned int l_idx = 0;
  struct session_group *sg;
  unsigned int sg_idx = 0;
  struct session_group *current;
  unsigned int current_idx = 0;
  u_int n;
  u_int i;
  current_idx = session_group_contains(data->fs.s);
  for (i = 0; i < data->item_size; i += 1)
  {
    window_tree_free_item(data->item_list[i]);
  }

  free(data->item_list);
  data->item_list = 0;
  data->item_size = 0;
  l_idx = 0;
  n = 0;
  for (s_idx = sessions_RB_MINMAX(&sessions, -1); (&s[s_idx]) != 0; s_idx = sessions_RB_NEXT(s_idx))
  {
    if (data->squash_groups && ((sg_idx = session_group_contains(s)) != 0))
    {
      if ((((&sg[sg_idx]) == (&current[current_idx])) && ((&s[s_idx]) != data->fs.s)) || (((&sg[sg_idx]) != (&current[current_idx])) && ((&s[s_idx]) != (&sg->sessions)->tqh_first)))
      {
        continue;
      }
    }
    l_idx = xreallocarray(l_idx, n + 1, sizeof(*l_idx));
    l[n + l_idx] = &s[s_idx];
    n += 1;
  }

  switch (sort_type)
  {
    case WINDOW_TREE_BY_INDEX:
    {
      break;
    }

    case WINDOW_TREE_BY_NAME:
    {
      qsort(l, n, sizeof(*(&l[l_idx])), window_tree_cmp_session_name);
      break;
    }

    case WINDOW_TREE_BY_TIME:
    {
      qsort(l, n, sizeof(*(&l[l_idx])), window_tree_cmp_session_time);
      break;
    }

  }

  for (i = 0; i < n; i += 1)
  {
    window_tree_build_session(l[i + l_idx], modedata, sort_type, filter);
  }

  free(l);
  switch (data->type)
  {
    case WINDOW_TREE_NONE:
    {
      break;
    }

    case WINDOW_TREE_SESSION:
    {
      *tag = (uint64_t) data->fs.s;
      break;
    }

    case WINDOW_TREE_WINDOW:
    {
      *tag = (uint64_t) data->fs.wl;
      break;
    }

    case WINDOW_TREE_PANE:
    {
      if (window_count_panes(data->fs.wl->window) == 1)
      {
        *tag = (uint64_t) data->fs.wl;
      }
      else
        *tag = (uint64_t) data->fs.wp;
      break;
    }

  }

}


----------------------------
static const char *window_tree_sort_list[] = {"index", "name", "time"}
----------------------------
void mode_tree_build(struct mode_tree_data *mtd)
{
  struct screen *s = &mtd->screen;
  uint64_t tag;
  if (mtd->line_list != 0)
  {
    tag = mtd->line_list[mtd->current].item->tag;
  }
  else
    tag = 0;
  do
  {
    if (!((&mtd->children)->tqh_first == 0))
    {
      *(&mtd->saved)->tqh_last = (&mtd->children)->tqh_first;
      (&mtd->children)->tqh_first->entry.tqe_prev = (&mtd->saved)->tqh_last;
      (&mtd->saved)->tqh_last = (&mtd->children)->tqh_last;
      do
      {
        (&mtd->children)->tqh_first = 0;
        (&mtd->children)->tqh_last = &(&mtd->children)->tqh_first;
      }
      while (0);
    }
  }
  while (0);
  do
  {
    (&mtd->children)->tqh_first = 0;
    (&mtd->children)->tqh_last = &(&mtd->children)->tqh_first;
  }
  while (0);
  mtd->buildcb(mtd->modedata, mtd->sort_type, &tag, mtd->filter);
  mtd->no_matches = (&mtd->children)->tqh_first == 0;
  if (mtd->no_matches)
  {
    mtd->buildcb(mtd->modedata, mtd->sort_type, &tag, 0);
  }
  mode_tree_free_items(&mtd->saved);
  do
  {
    (&mtd->saved)->tqh_first = 0;
    (&mtd->saved)->tqh_last = &(&mtd->saved)->tqh_first;
  }
  while (0);
  mode_tree_clear_lines(mtd);
  mode_tree_build_lines(mtd, &mtd->children, 0);
  mode_tree_set_current(mtd, tag);
  mtd->width = s->grid->sx;
  if (mtd->preview)
  {
    mtd->height = (s->grid->sy / 3) * 2;
    if (mtd->height > mtd->line_size)
    {
      mtd->height = s->grid->sy / 2;
    }
    if (mtd->height < 10)
    {
      mtd->height = s->grid->sy;
    }
    if ((s->grid->sy - mtd->height) < 2)
    {
      mtd->height = s->grid->sy;
    }
  }
  else
    mtd->height = s->grid->sy;
  mode_tree_check_selected(mtd);
}


----------------------------
None
----------------------------
struct mode_tree_data *mode_tree_start(struct window_pane *wp, struct args *args, mode_tree_build_cb buildcb, mode_tree_draw_cb drawcb, mode_tree_search_cb searchcb, void *modedata, const char **sort_list, u_int sort_size, struct screen **s)
{
  struct mode_tree_data *mtd;
  unsigned int mtd_idx = 0;
  const char *sort;
  unsigned int sort_idx = 0;
  u_int i;
  mtd_idx = xcalloc(1, sizeof(*mtd_idx));
  mtd->references = 1;
  mtd->wp = wp;
  mtd->modedata = modedata;
  mtd->sort_list = sort_list;
  mtd->sort_size = sort_size;
  mtd->sort_type = 0;
  mtd->preview = !args_has(args, 'N');
  sort_idx = args_get(args, 'O');
  if ((&sort[sort_idx]) != 0)
  {
    for (i = 0; i < sort_size; i += 1)
    {
      if (strcasecmp(sort, sort_list[i]) == 0)
      {
        mtd->sort_type = i;
      }
    }

  }
  if (args_has(args, 'f'))
  {
    mtd->filter = xstrdup(args_get(args, 'f'));
  }
  else
    mtd->filter = 0;
  mtd->buildcb = buildcb;
  mtd->drawcb = drawcb;
  mtd->searchcb = searchcb;
  do
  {
    (&mtd->children)->tqh_first = 0;
    (&mtd->children)->tqh_last = &(&mtd->children)->tqh_first;
  }
  while (0);
  *s = &mtd->screen;
  screen_init(*s, (&wp->base)->grid->sx, (&wp->base)->grid->sy, 0);
  (*s)->mode &= ~0x1;
  return mtd;
}


----------------------------
None
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
void mode_tree_draw(struct mode_tree_data *mtd)
{
  struct window_pane *wp = mtd->wp;
  struct screen *s = &mtd->screen;
  struct mode_tree_line *line;
  unsigned int line_idx = 0;
  struct mode_tree_item *mti;
  unsigned int mti_idx = 0;
  struct options *oo = wp->window->options;
  struct screen_write_ctx ctx;
  struct grid_cell gc0;
  struct grid_cell gc;
  u_int w;
  u_int h;
  u_int i;
  u_int j;
  u_int sy;
  u_int box_x;
  u_int box_y;
  char *text;
  char *start;
  unsigned int start_idx = 0;
  char key[7];
  const char *tag;
  unsigned int tag_idx = 0;
  const char *symbol;
  unsigned int symbol_idx = 0;
  size_t size;
  size_t n;
  int keylen;
  if (mtd->line_size == 0)
  {
    return;
  }
  memcpy(&gc0, &grid_default_cell, sizeof(gc0));
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  style_apply(&gc, oo, "mode-style");
  w = mtd->width;
  h = mtd->height;
  screen_write_start(&ctx, 0, s);
  screen_write_clearscreen(&ctx, 8);
  if (mtd->line_size > 10)
  {
    keylen = 6;
  }
  else
    keylen = 4;
  for (i = 0; i < mtd->line_size; i += 1)
  {
    helper_mode_tree_draw_1(&line_idx, &mti_idx, &gc0, &gc, &j, &start_idx, &tag_idx, &symbol_idx, &size, mtd, line, mti, ctx, w, h, i, text, start, key, tag, symbol, keylen);
  }

  sy = s->grid->sy;
  if (((((!mtd->preview) || (sy <= 4)) || (h <= 4)) || ((sy - h) <= 4)) || (w <= 4))
  {
    screen_write_stop(&ctx);
    return;
  }
  line_idx = &mtd->line_list[mtd->current];
  mti_idx = line->item;
  screen_write_cursormove(&ctx, 0, h);
  screen_write_box(&ctx, w, sy - h);
  xasprintf(&text, " %s (sort: %s)", mti->name, mtd->sort_list[mtd->sort_type]);
  if ((w - 2) >= strlen(text))
  {
    screen_write_cursormove(&ctx, 1, h);
    screen_write_puts(&ctx, &gc0, "%s", text);
    if (mtd->no_matches)
    {
      n = (sizeof("no matches")) - 1;
    }
    else
      n = (sizeof("active")) - 1;
    if ((mtd->filter != 0) && ((w - 2) >= (((strlen(text) + 10) + n) + 2)))
    {
      screen_write_puts(&ctx, &gc0, " (filter: ");
      if (mtd->no_matches)
      {
        screen_write_puts(&ctx, &gc, "no matches");
      }
      else
        screen_write_puts(&ctx, &gc0, "active");
      screen_write_puts(&ctx, &gc0, ") ");
    }
  }
  free(text);
  box_x = w - 4;
  box_y = (sy - h) - 2;
  if ((box_x != 0) && (box_y != 0))
  {
    screen_write_cursormove(&ctx, 2, h + 1);
    mtd->drawcb(mtd->modedata, mti->itemdata, &ctx, box_x, box_y);
  }
  screen_write_stop(&ctx);
}


----------------------------
static void window_tree_draw(void *modedata, void *itemdata, struct screen_write_ctx *ctx, u_int sx, u_int sy)
{
  struct window_tree_itemdata *item = itemdata;
  struct session *sp;
  struct winlink *wlp;
  struct window_pane *wp;
  window_tree_pull_item(item, &sp, &wlp, &wp);
  if (wp == 0)
  {
    return;
  }
  switch (item->type)
  {
    case WINDOW_TREE_NONE:
    {
      break;
    }

    case WINDOW_TREE_SESSION:
    {
      window_tree_draw_session(modedata, sp, ctx, sx, sy);
      break;
    }

    case WINDOW_TREE_WINDOW:
    {
      window_tree_draw_window(modedata, sp, wlp->window, ctx, sx, sy);
      break;
    }

    case WINDOW_TREE_PANE:
    {
      screen_write_preview(ctx, &wp->base, sx, sy);
      break;
    }

  }

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
void mode_tree_zoom(struct mode_tree_data *mtd, struct args *args)
{
  struct window_pane *wp = mtd->wp;
  if (args_has(args, 'Z'))
  {
    mtd->zoomed = wp->window->flags & 0x1000;
    if ((!mtd->zoomed) && (window_zoom(wp) == 0))
    {
      server_redraw_window(wp->window);
    }
  }
  else
    mtd->zoomed = -1;
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


static void window_tree_key(struct window_pane *wp, struct client *c, struct session *s, key_code key, struct mouse_event *m)
{
  struct window_tree_modedata *data = wp->modedata;
  struct window_tree_itemdata *item;
  unsigned int item_idx = 0;
  struct window_tree_itemdata *new_item;
  unsigned int new_item_idx = 0;
  char *name;
  unsigned int name_idx = 0;
  char *prompt = 0;
  struct cmd_find_state fs;
  int finished;
  u_int tagged;
  u_int x;
  u_int y;
  u_int idx;
  struct session *ns;
  struct winlink *nwl;
  struct window_pane *nwp;
  item_idx = mode_tree_get_current(data->data);
  finished = mode_tree_key(data->data, c, &key, m, &x, &y);
  if ((&item[item_idx]) != (new_item_idx = mode_tree_get_current(data->data)))
  {
    item_idx = &new_item[new_item_idx];
    data->offset = 0;
  }
  if (((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) >= KEYC_MOUSE) && ((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) < KEYC_BSPACE))
  {
    key = window_tree_mouse(data, key, x, item);
  }
  switch (key)
  {
    case '<':
    {
      data->offset -= 1;
      break;
    }

    case '>':
    {
      data->offset += 1;
      break;
    }

    case 'x':
    {
      helper_window_tree_key_1(c, data, item, prompt, idx, ns, nwl, nwp);
    }

    case 'X':
    {
      tagged = mode_tree_count_tagged(data->data);
      if (tagged == 0)
      {
        break;
      }
      xasprintf(&prompt, "Kill %u tagged? ", tagged);
      data->references += 1;
      status_prompt_set(c, prompt, "", window_tree_kill_tagged_callback, window_tree_command_free, data, 0x1 | 0x8);
      free(prompt);
      break;
    }

    case ':':
    {
      tagged = mode_tree_count_tagged(data->data);
      if (tagged != 0)
      {
        xasprintf(&prompt, "(%u tagged) ", tagged);
      }
      else
        xasprintf(&prompt, "(current) ");
      data->references += 1;
      status_prompt_set(c, prompt, "", window_tree_command_callback, window_tree_command_free, data, 0x8);
      free(prompt);
      break;
    }

    case '\r':
    {
      item_idx = mode_tree_get_current(data->data);
      name_idx = window_tree_get_target(item, &fs);
      if ((&name[name_idx]) != 0)
      {
        mode_tree_run_command(c, 0, data->command, name);
      }
      finished = 1;
      free(name);
      break;
    }

  }

  if (finished)
  {
    window_pane_reset_mode(wp);
  }
  else
  {
    mode_tree_draw(data->data);
    wp->flags |= 0x1;
  }
}


/*** DEPENDENCIES:
struct mouse_event
{
  int valid;
  key_code key;
  int statusat;
  u_int x;
  u_int y;
  u_int b;
  u_int lx;
  u_int ly;
  u_int lb;
  int s;
  int w;
  int wp;
  u_int sgr_type;
  u_int sgr_b;
}
----------------------------
None
----------------------------
void status_prompt_set(struct client *c, const char *msg, const char *input, prompt_input_cb inputcb, prompt_free_cb freecb, void *data, int flags)
{
  unsigned int input_idx = 0;
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  time_t t;
  char *tmp;
  unsigned int tmp_idx = 0;
  char *cp;
  ft_idx = format_create(c, 0, 0, 0);
  format_defaults(ft, c, 0, 0, 0);
  t = time(0);
  if ((&input[input_idx]) == 0)
  {
    input_idx = "";
  }
  if (flags & 0x8)
  {
    tmp_idx = xstrdup(input);
  }
  else
    tmp_idx = format_expand_time(ft, input, t);
  status_message_clear(c);
  status_prompt_clear(c);
  if (c->status.old_status == 0)
  {
    c->status.old_status = xmalloc(sizeof(*c->status.old_status));
    memcpy(c->status.old_status, &c->status.status, sizeof(*c->status.old_status));
    screen_init(&c->status.status, c->tty.sx, 1, 0);
  }
  c->prompt_string = format_expand_time(ft, msg, t);
  c->prompt_buffer = utf8_fromcstr(tmp);
  c->prompt_index = utf8_strlen(c->prompt_buffer);
  c->prompt_inputcb = inputcb;
  c->prompt_freecb = freecb;
  c->prompt_data = data;
  c->prompt_hindex = 0;
  c->prompt_flags = flags;
  c->prompt_mode = PROMPT_ENTRY;
  if ((~flags) & 0x4)
  {
    c->tty.flags |= 0x1 | 0x2;
  }
  c->flags |= 0x10;
  if ((flags & 0x4) && (tmp[tmp_idx] != '\0'))
  {
    xasprintf(&cp, "=%s", tmp);
    c->prompt_inputcb(c, c->prompt_data, cp, 0);
    free(cp);
  }
  free(tmp);
  format_free(ft);
}


----------------------------
static int window_tree_kill_tagged_callback(struct client *c, void *modedata, const char *s, int done)
{
  struct window_tree_modedata *data = modedata;
  struct mode_tree_data *mtd = data->data;
  if (((s == 0) || ((*s) == '\0')) || data->dead)
  {
    return 0;
  }
  if ((tolower((u_char) s[0]) != 'y') || (s[1] != '\0'))
  {
    return 0;
  }
  mode_tree_each_tagged(mtd, window_tree_kill_each, c, 0xffff00000000ULL, 1);
  data->references += 1;
  cmdq_append(c, cmdq_get_callback1("window_tree_command_done", window_tree_command_done, data));
  return 0;
}


----------------------------
struct window_tree_modedata
{
  struct window_pane *wp;
  int dead;
  int references;
  struct mode_tree_data *data;
  char *format;
  char *command;
  int squash_groups;
  struct window_tree_itemdata **item_list;
  u_int item_size;
  const char *entered;
  struct cmd_find_state fs;
  enum window_tree_type type;
  int offset;
  int left;
  int right;
  u_int start;
  u_int end;
  u_int each;
}
----------------------------
static int window_tree_command_callback(struct client *c, void *modedata, const char *s, int done)
{
  struct window_tree_modedata *data = modedata;
  if (((s == 0) || ((*s) == '\0')) || data->dead)
  {
    return 0;
  }
  data->entered = s;
  mode_tree_each_tagged(data->data, window_tree_command_each, c, 0xffff00000000ULL, 1);
  data->entered = 0;
  data->references += 1;
  cmdq_append(c, cmdq_get_callback1("window_tree_command_done", window_tree_command_done, data));
  return 0;
}


----------------------------
int mode_tree_key(struct mode_tree_data *mtd, struct client *c, key_code *key, struct mouse_event *m, u_int *xp, u_int *yp)
{
  struct mode_tree_line *line;
  unsigned int line_idx = 0;
  struct mode_tree_item *current;
  unsigned int current_idx = 0;
  struct mode_tree_item *parent;
  unsigned int parent_idx = 0;
  u_int i;
  u_int x;
  u_int y;
  int choice;
  key_code tmp;
  if ((((*key) & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) >= KEYC_MOUSE) && (((*key) & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) < KEYC_BSPACE))
  {
    helper_mode_tree_key_1(mtd, key, m, xp, yp, x, y);
  }
  line_idx = &mtd->line_list[mtd->current];
  current_idx = line->item;
  choice = -1;
  if (((*key) >= '0') && ((*key) <= '9'))
  {
    choice = (*key) - '0';
  }
  else
    if (((*key) & (((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL)) == 0x200000000000ULL)
  {
    tmp = (*key) & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL));
    if ((tmp >= 'a') && (tmp <= 'z'))
    {
      choice = 10 + (tmp - 'a');
    }
  }
  if (choice != (-1))
  {
    if (((u_int) choice) > (mtd->line_size - 1))
    {
      *key = 0xffff00000000ULL;
      return 0;
    }
    mtd->current = choice;
    *key = '\r';
    return 0;
  }
  switch (*key)
  {
    case 'q':

    case '\033':

    case '\007':
    {
      return 1;
    }

    case KEYC_UP:

    case 'k':

    case KEYC_WHEELUP_PANE:

    case '\020':
    {
      mode_tree_up(mtd, 1);
      break;
    }

    case KEYC_DOWN:

    case 'j':

    case KEYC_WHEELDOWN_PANE:

    case '\016':
    {
      mode_tree_down(mtd, 1);
      break;
    }

    case KEYC_PPAGE:

    case '\002':
    {
      for (i = 0; i < mtd->height; i += 1)
      {
        if (mtd->current == 0)
        {
          break;
        }
        mode_tree_up(mtd, 1);
      }

      break;
    }

    case KEYC_NPAGE:

    case '\006':
    {
      for (i = 0; i < mtd->height; i += 1)
      {
        if (mtd->current == (mtd->line_size - 1))
        {
          break;
        }
        mode_tree_down(mtd, 1);
      }

      break;
    }

    case KEYC_HOME:
    {
      mtd->current = 0;
      mtd->offset = 0;
      break;
    }

    case KEYC_END:
    {
      mtd->current = mtd->line_size - 1;
      if (mtd->current > (mtd->height - 1))
      {
        mtd->offset = (mtd->current - mtd->height) + 1;
      }
      else
        mtd->offset = 0;
      break;
    }

    case 't':
    {
      if (!current->tagged)
      {
        parent_idx = current->parent_idx;
        while ((&parent[parent_idx]) != 0)
        {
          parent->tagged = 0;
          parent_idx = parent_idx->parent_idx;
        }

        mode_tree_clear_tagged(&current->children);
        current->tagged = 1;
      }
      else
        current->tagged = 0;
      mode_tree_down(mtd, 0);
      break;
    }

    case 'T':
    {
      for (i = 0; i < mtd->line_size; i += 1)
      {
        mtd->line_list[i].item->tagged = 0;
      }

      break;
    }

    case '\024':
    {
      for (i = 0; i < mtd->line_size; i += 1)
      {
        if (mtd->line_list[i].item->parent == 0)
        {
          mtd->line_list[i].item->tagged = 1;
        }
        else
          mtd->line_list[i].item->tagged = 0;
      }

      break;
    }

    case 'O':
    {
      mtd->sort_type += 1;
      if (mtd->sort_type == mtd->sort_size)
      {
        mtd->sort_type = 0;
      }
      mode_tree_build(mtd);
      break;
    }

    case KEYC_LEFT:

    case 'h':

    case '-':
    {
      if (line->flat || (!current->expanded))
      {
        current_idx = current_idx->parent;
      }
      if ((&current[current_idx]) == 0)
      {
        mode_tree_up(mtd, 0);
      }
      else
      {
        current->expanded = 0;
        mtd->current = current->line;
        mode_tree_build(mtd);
      }
      break;
    }

    case KEYC_RIGHT:

    case 'l':

    case '+':
    {
      if (line->flat || current->expanded)
      {
        mode_tree_down(mtd, 0);
      }
      else
        if (!line->flat)
      {
        current->expanded = 1;
        mode_tree_build(mtd);
      }
      break;
    }

    case '\023':
    {
      mtd->references += 1;
      status_prompt_set(c, "(search) ", "", mode_tree_search_callback, mode_tree_search_free, mtd, 0x8);
      break;
    }

    case 'n':
    {
      mode_tree_search_set(mtd);
      break;
    }

    case 'f':
    {
      mtd->references += 1;
      status_prompt_set(c, "(filter) ", mtd->filter, mode_tree_filter_callback, mode_tree_filter_free, mtd, 0x8);
      break;
    }

    case 'v':
    {
      mtd->preview = !mtd->preview;
      mode_tree_build(mtd);
      if (mtd->preview)
      {
        mode_tree_check_selected(mtd);
      }
      break;
    }

  }

  return 0;
}


----------------------------
typedef unsigned long long key_code
----------------------------
void mode_tree_run_command(struct client *c, struct cmd_find_state *fs, const char *template, const char *name)
{
  struct cmdq_item *new_item;
  unsigned int new_item_idx = 0;
  struct cmd_list *cmdlist;
  unsigned int cmdlist_idx = 0;
  char *command;
  unsigned int command_idx = 0;
  char *cause;
  command_idx = cmd_template_replace(template, name, 1);
  if (((&command[command_idx]) == 0) || (command[command_idx] == '\0'))
  {
    free(command);
    return;
  }
  cmdlist_idx = cmd_string_parse(command, 0, 0, &cause);
  if ((&cmdlist[cmdlist_idx]) == 0)
  {
    if ((cause != 0) && (c != 0))
    {
      *cause = toupper((u_char) (*cause));
      status_message_set(c, "%s", cause);
    }
    free(cause);
  }
  else
  {
    new_item_idx = cmdq_get_command(cmdlist, fs, 0, 0);
    cmdq_append(c, new_item);
    cmd_list_free(cmdlist);
  }
  free(command);
}


----------------------------
struct window_tree_itemdata
{
  enum window_tree_type type;
  int session;
  int winlink;
  int pane;
}
----------------------------
void mode_tree_draw(struct mode_tree_data *mtd)
{
  struct window_pane *wp = mtd->wp;
  struct screen *s = &mtd->screen;
  struct mode_tree_line *line;
  unsigned int line_idx = 0;
  struct mode_tree_item *mti;
  unsigned int mti_idx = 0;
  struct options *oo = wp->window->options;
  struct screen_write_ctx ctx;
  struct grid_cell gc0;
  struct grid_cell gc;
  u_int w;
  u_int h;
  u_int i;
  u_int j;
  u_int sy;
  u_int box_x;
  u_int box_y;
  char *text;
  char *start;
  unsigned int start_idx = 0;
  char key[7];
  const char *tag;
  unsigned int tag_idx = 0;
  const char *symbol;
  unsigned int symbol_idx = 0;
  size_t size;
  size_t n;
  int keylen;
  if (mtd->line_size == 0)
  {
    return;
  }
  memcpy(&gc0, &grid_default_cell, sizeof(gc0));
  memcpy(&gc, &grid_default_cell, sizeof(gc));
  style_apply(&gc, oo, "mode-style");
  w = mtd->width;
  h = mtd->height;
  screen_write_start(&ctx, 0, s);
  screen_write_clearscreen(&ctx, 8);
  if (mtd->line_size > 10)
  {
    keylen = 6;
  }
  else
    keylen = 4;
  for (i = 0; i < mtd->line_size; i += 1)
  {
    helper_mode_tree_draw_1(&line_idx, &mti_idx, &gc0, &gc, &j, &start_idx, &tag_idx, &symbol_idx, &size, mtd, line, mti, ctx, w, h, i, text, start, key, tag, symbol, keylen);
  }

  sy = s->grid->sy;
  if (((((!mtd->preview) || (sy <= 4)) || (h <= 4)) || ((sy - h) <= 4)) || (w <= 4))
  {
    screen_write_stop(&ctx);
    return;
  }
  line_idx = &mtd->line_list[mtd->current];
  mti_idx = line->item;
  screen_write_cursormove(&ctx, 0, h);
  screen_write_box(&ctx, w, sy - h);
  xasprintf(&text, " %s (sort: %s)", mti->name, mtd->sort_list[mtd->sort_type]);
  if ((w - 2) >= strlen(text))
  {
    screen_write_cursormove(&ctx, 1, h);
    screen_write_puts(&ctx, &gc0, "%s", text);
    if (mtd->no_matches)
    {
      n = (sizeof("no matches")) - 1;
    }
    else
      n = (sizeof("active")) - 1;
    if ((mtd->filter != 0) && ((w - 2) >= (((strlen(text) + 10) + n) + 2)))
    {
      screen_write_puts(&ctx, &gc0, " (filter: ");
      if (mtd->no_matches)
      {
        screen_write_puts(&ctx, &gc, "no matches");
      }
      else
        screen_write_puts(&ctx, &gc0, "active");
      screen_write_puts(&ctx, &gc0, ") ");
    }
  }
  free(text);
  box_x = w - 4;
  box_y = (sy - h) - 2;
  if ((box_x != 0) && (box_y != 0))
  {
    screen_write_cursormove(&ctx, 2, h + 1);
    mtd->drawcb(mtd->modedata, mti->itemdata, &ctx, box_x, box_y);
  }
  screen_write_stop(&ctx);
}


----------------------------
static key_code window_tree_mouse(struct window_tree_modedata *data, key_code key, u_int x, struct window_tree_itemdata *item)
{
  struct session *s;
  struct winlink *wl;
  unsigned int wl_idx = 0;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int loop;
  if (key != KEYC_MOUSEDOWN1_PANE)
  {
    return 0xffff00000000ULL;
  }
  if ((data->left != (-1)) && (x <= ((u_int) data->left)))
  {
    return '<';
  }
  if ((data->right != (-1)) && (x >= ((u_int) data->right)))
  {
    return '>';
  }
  if (data->left != (-1))
  {
    x -= data->left;
  }
  else
    if (x != 0)
  {
    x -= 1;
  }
  if ((x == 0) || (data->end == 0))
  {
    x = 0;
  }
  else
  {
    x = x / data->each;
    if ((data->start + x) >= data->end)
    {
      x = data->end - 1;
    }
  }
  window_tree_pull_item(item, &s, &(&wl[wl_idx]), &(&wp[wp_idx]));
  if (item->type == WINDOW_TREE_SESSION)
  {
    helper_window_tree_mouse_1(&wl_idx, &loop, data, x, s, wl);
  }
  if (item->type == WINDOW_TREE_WINDOW)
  {
    helper_window_tree_mouse_2(&wp_idx, &loop, data, x, wl, wl_idx, wp);
  }
  return 0xffff00000000ULL;
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
u_int mode_tree_count_tagged(struct mode_tree_data *mtd)
{
  struct mode_tree_item *mti;
  unsigned int mti_idx = 0;
  u_int i;
  u_int tagged;
  tagged = 0;
  for (i = 0; i < mtd->line_size; i += 1)
  {
    mti_idx = mtd->line_list[i].item;
    if (mti->tagged)
    {
      tagged += 1;
    }
  }

  return tagged;
}


----------------------------
static void window_tree_command_free(void *modedata)
{
  struct window_tree_modedata *data = modedata;
  window_tree_destroy(data);
}


----------------------------
void *mode_tree_get_current(struct mode_tree_data *mtd)
{
  return mtd->line_list[mtd->current].item->itemdata;
}


----------------------------
void helper_window_tree_key_1(struct client * const c, struct window_tree_modedata * const data, struct window_tree_itemdata * const item, char * const prompt, u_int idx, struct session * const ns, struct winlink * const nwl, struct window_pane * const nwp)
{
  window_tree_pull_item(item, &ns, &nwl, &nwp);
  switch (item->type)
  {
    case WINDOW_TREE_NONE:
    {
      break;
    }

    case WINDOW_TREE_SESSION:
    {
      if (ns == 0)
      {
        break;
      }
      xasprintf(&prompt, "Kill session %s? ", ns->name);
      break;
    }

    case WINDOW_TREE_WINDOW:
    {
      if (nwl == 0)
      {
        break;
      }
      xasprintf(&prompt, "Kill window %u? ", nwl->idx);
      break;
    }

    case WINDOW_TREE_PANE:
    {
      if ((nwp == 0) || (window_pane_index(nwp, &idx) != 0))
      {
        break;
      }
      xasprintf(&prompt, "Kill pane %u? ", idx);
      break;
    }

  }

  if (prompt == 0)
  {
    break;
  }
  data->references += 1;
  status_prompt_set(c, prompt, "", window_tree_kill_current_callback, window_tree_command_free, data, 0x1 | 0x8);
  free(prompt);
  break;
}


----------------------------
static char *window_tree_get_target(struct window_tree_itemdata *item, struct cmd_find_state *fs)
{
  struct session *s;
  struct winlink *wl;
  struct window_pane *wp;
  char *target;
  unsigned int target_idx = 0;
  window_tree_pull_item(item, &s, &wl, &wp);
  target_idx = 0;
  switch (item->type)
  {
    case WINDOW_TREE_NONE:
    {
      break;
    }

    case WINDOW_TREE_SESSION:
    {
      if (s == 0)
      {
        break;
      }
      xasprintf(&(&target[target_idx]), "=%s:", s->name);
      break;
    }

    case WINDOW_TREE_WINDOW:
    {
      if ((s == 0) || (wl == 0))
      {
        break;
      }
      xasprintf(&(&target[target_idx]), "=%s:%u.", s->name, wl->idx);
      break;
    }

    case WINDOW_TREE_PANE:
    {
      if (((s == 0) || (wl == 0)) || (wp == 0))
      {
        break;
      }
      xasprintf(&(&target[target_idx]), "=%s:%u.%%%u", s->name, wl->idx, wp->id);
      break;
    }

  }

  if ((&target[target_idx]) == 0)
  {
    cmd_find_clear_state(fs, 0);
  }
  else
    cmd_find_from_winlink_pane(fs, wl, wp, 0);
  return target;
}


----------------------------
None
----------------------------
***/


