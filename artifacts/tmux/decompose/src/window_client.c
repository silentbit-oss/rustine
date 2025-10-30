static int window_client_cmp_name(const void *a0, const void *b0)
{
  const struct window_client_itemdata * const *a = a0;
  const struct window_client_itemdata * const *b = b0;
  return strcmp((*a)->c->name, (*b)->c->name);
}


/*** DEPENDENCIES:
struct window_client_itemdata
{
  struct client *c;
}
----------------------------
None
----------------------------
***/


static int window_client_cmp_size(const void *a0, const void *b0)
{
  const struct window_client_itemdata * const *a = a0;
  const struct window_client_itemdata * const *b = b0;
  if ((*a)->c->tty.sx < (*b)->c->tty.sx)
  {
    return -1;
  }
  if ((*a)->c->tty.sx > (*b)->c->tty.sx)
  {
    return 1;
  }
  if ((*a)->c->tty.sy < (*b)->c->tty.sy)
  {
    return -1;
  }
  if ((*a)->c->tty.sy > (*b)->c->tty.sy)
  {
    return 1;
  }
  return strcmp((*a)->c->name, (*b)->c->name);
}


/*** DEPENDENCIES:
struct window_client_itemdata
{
  struct client *c;
}
----------------------------
None
----------------------------
***/


static int window_client_cmp_creation_time(const void *a0, const void *b0)
{
  const struct window_client_itemdata * const *a = a0;
  const struct window_client_itemdata * const *b = b0;
  if (((&(*a)->c->creation_time)->tv_sec == (&(*b)->c->creation_time)->tv_sec) ? ((&(*a)->c->creation_time)->tv_usec > (&(*b)->c->creation_time)->tv_usec) : ((&(*a)->c->creation_time)->tv_sec > (&(*b)->c->creation_time)->tv_sec))
  {
    return -1;
  }
  if (((&(*a)->c->creation_time)->tv_sec == (&(*b)->c->creation_time)->tv_sec) ? ((&(*a)->c->creation_time)->tv_usec < (&(*b)->c->creation_time)->tv_usec) : ((&(*a)->c->creation_time)->tv_sec < (&(*b)->c->creation_time)->tv_sec))
  {
    return 1;
  }
  return strcmp((*a)->c->name, (*b)->c->name);
}


/*** DEPENDENCIES:
struct window_client_itemdata
{
  struct client *c;
}
----------------------------
None
----------------------------
***/


static int window_client_cmp_activity_time(const void *a0, const void *b0)
{
  const struct window_client_itemdata * const *a = a0;
  const struct window_client_itemdata * const *b = b0;
  if (((&(*a)->c->activity_time)->tv_sec == (&(*b)->c->activity_time)->tv_sec) ? ((&(*a)->c->activity_time)->tv_usec > (&(*b)->c->activity_time)->tv_usec) : ((&(*a)->c->activity_time)->tv_sec > (&(*b)->c->activity_time)->tv_sec))
  {
    return -1;
  }
  if (((&(*a)->c->activity_time)->tv_sec == (&(*b)->c->activity_time)->tv_sec) ? ((&(*a)->c->activity_time)->tv_usec < (&(*b)->c->activity_time)->tv_usec) : ((&(*a)->c->activity_time)->tv_sec < (&(*b)->c->activity_time)->tv_sec))
  {
    return 1;
  }
  return strcmp((*a)->c->name, (*b)->c->name);
}


/*** DEPENDENCIES:
struct window_client_itemdata
{
  struct client *c;
}
----------------------------
None
----------------------------
***/


static void window_client_free_item(struct window_client_itemdata *item)
{
  server_client_unref(item->c);
  free(item);
}


/*** DEPENDENCIES:
struct window_client_itemdata
{
  struct client *c;
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


static void window_client_resize(struct window_pane *wp, u_int sx, u_int sy)
{
  struct window_client_modedata *data = wp->modedata;
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
struct window_client_modedata
{
  struct mode_tree_data *data;
  char *format;
  char *command;
  struct window_client_itemdata **item_list;
  u_int item_size;
}
----------------------------
None
----------------------------
***/


static void window_client_free(struct window_pane *wp)
{
  struct window_client_modedata *data = wp->modedata;
  u_int i;
  if (data == 0)
  {
    return;
  }
  mode_tree_free(data->data);
  for (i = 0; i < data->item_size; i += 1)
  {
    window_client_free_item(data->item_list[i]);
  }

  free(data->item_list);
  free(data->format);
  free(data->command);
  free(data);
}


/*** DEPENDENCIES:
static void window_client_free_item(struct window_client_itemdata *item)
{
  server_client_unref(item->c);
  free(item);
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
struct window_client_modedata
{
  struct mode_tree_data *data;
  char *format;
  char *command;
  struct window_client_itemdata **item_list;
  u_int item_size;
}
----------------------------
None
----------------------------
***/


static struct window_client_itemdata *window_client_add_item(struct window_client_modedata *data)
{
  struct window_client_itemdata *item;
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
struct window_client_itemdata
{
  struct client *c;
}
----------------------------
struct window_client_modedata
{
  struct mode_tree_data *data;
  char *format;
  char *command;
  struct window_client_itemdata **item_list;
  u_int item_size;
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


// hint:  ['item_idx_ref is a mutable refrence to unsigned int', 'c_idx_ref is a mutable refrence to unsigned int', 'text_idx_ref is a mutable refrence to unsigned int', 'cp_idx_ref is a mutable refrence to unsigned int']
void helper_window_client_build_1(unsigned int * const item_idx_ref, unsigned int * const c_idx_ref, unsigned int * const text_idx_ref, unsigned int * const cp_idx_ref, const char * const filter, struct window_client_modedata * const data, struct window_client_itemdata * const item, u_int i, struct client * const c, char * const text, char * const cp)
{
  unsigned int item_idx = *item_idx_ref;
  unsigned int c_idx = *c_idx_ref;
  unsigned int text_idx = *text_idx_ref;
  unsigned int cp_idx = *cp_idx_ref;
  item_idx = data->item_list[i];
  c_idx = item->c_idx;
  if (filter != 0)
  {
    cp_idx = format_single(0, filter, c, 0, 0, 0);
    if (!format_true(cp))
    {
      free(cp);
      continue;
    }
    free(cp);
  }
  text_idx = format_single(0, data->format, c, 0, 0, 0);
  mode_tree_add(data->data, 0, item, (uint64_t) c, c->name, text, -1);
  free(text);
  *item_idx_ref = item_idx;
  *c_idx_ref = c_idx;
  *text_idx_ref = text_idx;
  *cp_idx_ref = cp_idx;
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
int format_true(const char *s)
{
  if (((s != 0) && ((*s) != '\0')) && ((s[0] != '0') || (s[1] != '\0')))
  {
    return 1;
  }
  return 0;
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
struct window_client_modedata
{
  struct mode_tree_data *data;
  char *format;
  char *command;
  struct window_client_itemdata **item_list;
  u_int item_size;
}
----------------------------
struct window_client_itemdata
{
  struct client *c;
}
----------------------------
None
----------------------------
***/


static void window_client_do_detach(void *modedata, void *itemdata, struct client *c, key_code key)
{
  struct window_client_modedata *data = modedata;
  struct window_client_itemdata *item = itemdata;
  if (item == mode_tree_get_current(data->data))
  {
    mode_tree_down(data->data, 0);
  }
  if ((key == 'd') || (key == 'D'))
  {
    server_client_detach(item->c, MSG_DETACH);
  }
  else
    if ((key == 'x') || (key == 'X'))
  {
    server_client_detach(item->c, MSG_DETACHKILL);
  }
  else
    if ((key == 'z') || (key == 'Z'))
  {
    server_client_suspend(item->c);
  }
}


/*** DEPENDENCIES:
void server_client_detach(struct client *c, enum msgtype msgtype)
{
  struct session *s = c->session;
  if ((s == 0) || (c->flags & 0x1000))
  {
    return;
  }
  c->flags |= 0x1000;
  notify_client("client-detached", c);
  proc_send(c->peer, msgtype, -1, s->name, strlen(s->name) + 1);
}


----------------------------
typedef unsigned long long key_code
----------------------------
void server_client_suspend(struct client *c)
{
  struct session *s = c->session;
  if ((s == 0) || (c->flags & 0x1000))
  {
    return;
  }
  tty_stop_tty(&c->tty);
  c->flags |= 0x40;
  proc_send(c->peer, MSG_SUSPEND, -1, 0, 0);
}


----------------------------
struct window_client_modedata
{
  struct mode_tree_data *data;
  char *format;
  char *command;
  struct window_client_itemdata **item_list;
  u_int item_size;
}
----------------------------
struct window_client_itemdata
{
  struct client *c;
}
----------------------------
void mode_tree_down(struct mode_tree_data *mtd, int wrap)
{
  if (mtd->current == (mtd->line_size - 1))
  {
    if (wrap)
    {
      mtd->current = 0;
      mtd->offset = 0;
    }
  }
  else
  {
    mtd->current += 1;
    if (mtd->current > ((mtd->offset + mtd->height) - 1))
    {
      mtd->offset += 1;
    }
  }
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


static void window_client_draw(void *modedata, void *itemdata, struct screen_write_ctx *ctx, u_int sx, u_int sy)
{
  struct window_client_itemdata *item = itemdata;
  struct client *c = item->c;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int cx = ctx->s->cx;
  u_int cy = ctx->s->cy;
  if ((c->session == 0) || (c->flags & (0x200 | 0x1000)))
  {
    return;
  }
  wp_idx = c->session->curw->window->active;
  screen_write_preview(ctx, &wp->base, sx, sy - 3);
  screen_write_cursormove(ctx, cx, (cy + sy) - 2);
  screen_write_hline(ctx, sx, 0, 0);
  screen_write_cursormove(ctx, cx, (cy + sy) - 1);
  if (c->status.old_status != 0)
  {
    screen_write_fast_copy(ctx, c->status.old_status, 0, 0, sx, 1);
  }
  else
    screen_write_fast_copy(ctx, &c->status.status, 0, 0, sx, 1);
}


/*** DEPENDENCIES:
void screen_write_hline(struct screen_write_ctx *ctx, u_int nx, int left, int right)
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
  screen_write_putc(ctx, &gc, (left) ? ('t') : ('q'));
  for (i = 1; i < (nx - 1); i += 1)
  {
    screen_write_putc(ctx, &gc, 'q');
  }

  screen_write_putc(ctx, &gc, (right) ? ('u') : ('q'));
  screen_write_cursormove(ctx, cx, cy);
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
void screen_write_fast_copy(struct screen_write_ctx *ctx, struct screen *src, u_int px, u_int py, u_int nx, u_int ny)
{
  struct screen *s = ctx->s;
  struct grid *gd = src->grid;
  struct grid_cell gc;
  u_int xx;
  u_int yy;
  u_int cx;
  u_int cy;
  if ((nx == 0) || (ny == 0))
  {
    return;
  }
  cy = s->cy;
  for (yy = py; yy < (py + ny); yy += 1)
  {
    if (yy >= (gd->hsize + gd->sy))
    {
      break;
    }
    cx = s->cx;
    for (xx = px; xx < (px + nx); xx += 1)
    {
      if (xx >= gd->linedata[yy].cellsize)
      {
        break;
      }
      grid_get_cell(gd, xx, yy, &gc);
      if ((xx + gc.data.width) > (px + nx))
      {
        break;
      }
      if (!grid_cells_equal(&gc, &grid_default_cell))
      {
        grid_view_set_cell(ctx->s->grid, cx, cy, &gc);
      }
      cx += 1;
    }

    cy += 1;
  }

}


----------------------------
struct window_client_itemdata
{
  struct client *c;
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


static void window_client_build(void *modedata, u_int sort_type, uint64_t *tag, const char *filter)
{
  struct window_client_modedata *data = modedata;
  struct window_client_itemdata *item;
  unsigned int item_idx = 0;
  u_int i;
  struct client *c;
  unsigned int c_idx = 0;
  char *text;
  unsigned int text_idx = 0;
  char *cp;
  unsigned int cp_idx = 0;
  for (i = 0; i < data->item_size; i += 1)
  {
    window_client_free_item(data->item_list[i]);
  }

  free(data->item_list);
  data->item_list = 0;
  data->item_size = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if ((c->session == 0) || (c->flags & 0x1000))
    {
      continue;
    }
    item_idx = window_client_add_item(data);
    item->c = &c[c_idx];
    c->references += 1;
  }

  switch (sort_type)
  {
    case WINDOW_CLIENT_BY_NAME:
    {
      qsort(data->item_list, data->item_size, sizeof(*data->item_list), window_client_cmp_name);
      break;
    }

    case WINDOW_CLIENT_BY_SIZE:
    {
      qsort(data->item_list, data->item_size, sizeof(*data->item_list), window_client_cmp_size);
      break;
    }

    case WINDOW_CLIENT_BY_CREATION_TIME:
    {
      qsort(data->item_list, data->item_size, sizeof(*data->item_list), window_client_cmp_creation_time);
      break;
    }

    case WINDOW_CLIENT_BY_ACTIVITY_TIME:
    {
      qsort(data->item_list, data->item_size, sizeof(*data->item_list), window_client_cmp_activity_time);
      break;
    }

  }

  for (i = 0; i < data->item_size; i += 1)
  {
    helper_window_client_build_1(&item_idx, &c_idx, &text_idx, &cp_idx, filter, data, item, i, c, text, cp);
  }

}


/*** DEPENDENCIES:
struct clients
{
  struct client *tqh_first;
  struct client **tqh_last;
}
----------------------------
static void window_client_free_item(struct window_client_itemdata *item)
{
  server_client_unref(item->c);
  free(item);
}


----------------------------
static int window_client_cmp_activity_time(const void *a0, const void *b0)
{
  const struct window_client_itemdata * const *a = a0;
  const struct window_client_itemdata * const *b = b0;
  if (((&(*a)->c->activity_time)->tv_sec == (&(*b)->c->activity_time)->tv_sec) ? ((&(*a)->c->activity_time)->tv_usec > (&(*b)->c->activity_time)->tv_usec) : ((&(*a)->c->activity_time)->tv_sec > (&(*b)->c->activity_time)->tv_sec))
  {
    return -1;
  }
  if (((&(*a)->c->activity_time)->tv_sec == (&(*b)->c->activity_time)->tv_sec) ? ((&(*a)->c->activity_time)->tv_usec < (&(*b)->c->activity_time)->tv_usec) : ((&(*a)->c->activity_time)->tv_sec < (&(*b)->c->activity_time)->tv_sec))
  {
    return 1;
  }
  return strcmp((*a)->c->name, (*b)->c->name);
}


----------------------------
static int window_client_cmp_size(const void *a0, const void *b0)
{
  const struct window_client_itemdata * const *a = a0;
  const struct window_client_itemdata * const *b = b0;
  if ((*a)->c->tty.sx < (*b)->c->tty.sx)
  {
    return -1;
  }
  if ((*a)->c->tty.sx > (*b)->c->tty.sx)
  {
    return 1;
  }
  if ((*a)->c->tty.sy < (*b)->c->tty.sy)
  {
    return -1;
  }
  if ((*a)->c->tty.sy > (*b)->c->tty.sy)
  {
    return 1;
  }
  return strcmp((*a)->c->name, (*b)->c->name);
}


----------------------------
static int window_client_cmp_name(const void *a0, const void *b0)
{
  const struct window_client_itemdata * const *a = a0;
  const struct window_client_itemdata * const *b = b0;
  return strcmp((*a)->c->name, (*b)->c->name);
}


----------------------------
static int window_client_cmp_creation_time(const void *a0, const void *b0)
{
  const struct window_client_itemdata * const *a = a0;
  const struct window_client_itemdata * const *b = b0;
  if (((&(*a)->c->creation_time)->tv_sec == (&(*b)->c->creation_time)->tv_sec) ? ((&(*a)->c->creation_time)->tv_usec > (&(*b)->c->creation_time)->tv_usec) : ((&(*a)->c->creation_time)->tv_sec > (&(*b)->c->creation_time)->tv_sec))
  {
    return -1;
  }
  if (((&(*a)->c->creation_time)->tv_sec == (&(*b)->c->creation_time)->tv_sec) ? ((&(*a)->c->creation_time)->tv_usec < (&(*b)->c->creation_time)->tv_usec) : ((&(*a)->c->creation_time)->tv_sec < (&(*b)->c->creation_time)->tv_sec))
  {
    return 1;
  }
  return strcmp((*a)->c->name, (*b)->c->name);
}


----------------------------
struct window_client_modedata
{
  struct mode_tree_data *data;
  char *format;
  char *command;
  struct window_client_itemdata **item_list;
  u_int item_size;
}
----------------------------
static struct window_client_itemdata *window_client_add_item(struct window_client_modedata *data)
{
  struct window_client_itemdata *item;
  unsigned int item_idx = 0;
  data->item_list = xreallocarray(data->item_list, data->item_size + 1, sizeof(*data->item_list));
  item_idx = (data->item_list[data->item_size++] = xcalloc(1, sizeof(*item_idx)));
  return item;
}


----------------------------
struct window_client_itemdata
{
  struct client *c;
}
----------------------------
void helper_window_client_build_1(unsigned int * const item_idx_ref, unsigned int * const c_idx_ref, unsigned int * const text_idx_ref, unsigned int * const cp_idx_ref, const char * const filter, struct window_client_modedata * const data, struct window_client_itemdata * const item, u_int i, struct client * const c, char * const text, char * const cp)
{
  unsigned int item_idx = *item_idx_ref;
  unsigned int c_idx = *c_idx_ref;
  unsigned int text_idx = *text_idx_ref;
  unsigned int cp_idx = *cp_idx_ref;
  item_idx = data->item_list[i];
  c_idx = item->c_idx;
  if (filter != 0)
  {
    cp_idx = format_single(0, filter, c, 0, 0, 0);
    if (!format_true(cp))
    {
      free(cp);
      continue;
    }
    free(cp);
  }
  text_idx = format_single(0, data->format, c, 0, 0, 0);
  mode_tree_add(data->data, 0, item, (uint64_t) c, c->name, text, -1);
  free(text);
  *item_idx_ref = item_idx;
  *c_idx_ref = c_idx;
  *text_idx_ref = text_idx;
  *cp_idx_ref = cp_idx;
}


----------------------------
None
----------------------------
***/


static void window_client_key(struct window_pane *wp, struct client *c, struct session *s, key_code key, struct mouse_event *m)
{
  struct window_client_modedata *data = wp->modedata;
  struct mode_tree_data *mtd = data->data;
  struct window_client_itemdata *item;
  unsigned int item_idx = 0;
  int finished;
  finished = mode_tree_key(mtd, c, &key, m, 0, 0);
  switch (key)
  {
    case 'd':

    case 'x':

    case 'z':
    {
      item_idx = mode_tree_get_current(mtd);
      window_client_do_detach(data, item, c, key);
      mode_tree_build(mtd);
      break;
    }

    case 'D':

    case 'X':

    case 'Z':
    {
      mode_tree_each_tagged(mtd, window_client_do_detach, c, key, 0);
      mode_tree_build(mtd);
      break;
    }

    case '\r':
    {
      item_idx = mode_tree_get_current(mtd);
      mode_tree_run_command(c, 0, data->command, item->c->ttyname);
      finished = 1;
      break;
    }

  }

  if (finished || (server_client_how_many() == 0))
  {
    window_pane_reset_mode(wp);
  }
  else
  {
    mode_tree_draw(mtd);
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
None
----------------------------
typedef unsigned long long key_code
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
struct window_client_modedata
{
  struct mode_tree_data *data;
  char *format;
  char *command;
  struct window_client_itemdata **item_list;
  u_int item_size;
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
static void window_client_do_detach(void *modedata, void *itemdata, struct client *c, key_code key)
{
  struct window_client_modedata *data = modedata;
  struct window_client_itemdata *item = itemdata;
  if (item == mode_tree_get_current(data->data))
  {
    mode_tree_down(data->data, 0);
  }
  if ((key == 'd') || (key == 'D'))
  {
    server_client_detach(item->c, MSG_DETACH);
  }
  else
    if ((key == 'x') || (key == 'X'))
  {
    server_client_detach(item->c, MSG_DETACHKILL);
  }
  else
    if ((key == 'z') || (key == 'Z'))
  {
    server_client_suspend(item->c);
  }
}


----------------------------
struct window_client_itemdata
{
  struct client *c;
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
void *mode_tree_get_current(struct mode_tree_data *mtd)
{
  return mtd->line_list[mtd->current].item->itemdata;
}


----------------------------
None
----------------------------
***/


static struct screen *window_client_init(struct window_pane *wp, struct cmd_find_state *fs, struct args *args)
{
  struct window_client_modedata *data;
  struct screen *s;
  wp->modedata = (data = xcalloc(1, sizeof(*data)));
  if ((args == 0) || (!args_has(args, 'F')))
  {
    data->format = xstrdup("session #{session_name} (#{client_width}x#{client_height}, #{t:client_activity})");
  }
  else
    data->format = xstrdup(args_get(args, 'F'));
  if ((args == 0) || (args->argc == 0))
  {
    data->command = xstrdup("detach-client -t '%%'");
  }
  else
    data->command = xstrdup(args->argv[0]);
  data->data = mode_tree_start(wp, args, window_client_build, window_client_draw, 0, data, window_client_sort_list, (sizeof(window_client_sort_list)) / (sizeof(window_client_sort_list[0])), &s);
  mode_tree_zoom(data->data, args);
  mode_tree_build(data->data);
  mode_tree_draw(data->data);
  return s;
}


/*** DEPENDENCIES:
static void window_client_build(void *modedata, u_int sort_type, uint64_t *tag, const char *filter)
{
  struct window_client_modedata *data = modedata;
  struct window_client_itemdata *item;
  unsigned int item_idx = 0;
  u_int i;
  struct client *c;
  unsigned int c_idx = 0;
  char *text;
  unsigned int text_idx = 0;
  char *cp;
  unsigned int cp_idx = 0;
  for (i = 0; i < data->item_size; i += 1)
  {
    window_client_free_item(data->item_list[i]);
  }

  free(data->item_list);
  data->item_list = 0;
  data->item_size = 0;
  for (c_idx = (&clients)->tqh_first; (&c[c_idx]) != 0; c_idx = c_idx->entry.tqe_next)
  {
    if ((c->session == 0) || (c->flags & 0x1000))
    {
      continue;
    }
    item_idx = window_client_add_item(data);
    item->c = &c[c_idx];
    c->references += 1;
  }

  switch (sort_type)
  {
    case WINDOW_CLIENT_BY_NAME:
    {
      qsort(data->item_list, data->item_size, sizeof(*data->item_list), window_client_cmp_name);
      break;
    }

    case WINDOW_CLIENT_BY_SIZE:
    {
      qsort(data->item_list, data->item_size, sizeof(*data->item_list), window_client_cmp_size);
      break;
    }

    case WINDOW_CLIENT_BY_CREATION_TIME:
    {
      qsort(data->item_list, data->item_size, sizeof(*data->item_list), window_client_cmp_creation_time);
      break;
    }

    case WINDOW_CLIENT_BY_ACTIVITY_TIME:
    {
      qsort(data->item_list, data->item_size, sizeof(*data->item_list), window_client_cmp_activity_time);
      break;
    }

  }

  for (i = 0; i < data->item_size; i += 1)
  {
    helper_window_client_build_1(&item_idx, &c_idx, &text_idx, &cp_idx, filter, data, item, i, c, text, cp);
  }

}


----------------------------
static void window_client_draw(void *modedata, void *itemdata, struct screen_write_ctx *ctx, u_int sx, u_int sy)
{
  struct window_client_itemdata *item = itemdata;
  struct client *c = item->c;
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  u_int cx = ctx->s->cx;
  u_int cy = ctx->s->cy;
  if ((c->session == 0) || (c->flags & (0x200 | 0x1000)))
  {
    return;
  }
  wp_idx = c->session->curw->window->active;
  screen_write_preview(ctx, &wp->base, sx, sy - 3);
  screen_write_cursormove(ctx, cx, (cy + sy) - 2);
  screen_write_hline(ctx, sx, 0, 0);
  screen_write_cursormove(ctx, cx, (cy + sy) - 1);
  if (c->status.old_status != 0)
  {
    screen_write_fast_copy(ctx, c->status.old_status, 0, 0, sx, 1);
  }
  else
    screen_write_fast_copy(ctx, &c->status.status, 0, 0, sx, 1);
}


----------------------------
None
----------------------------
static const char *window_client_sort_list[] = {"name", "size", "creation", "activity"}
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
struct window_client_modedata
{
  struct mode_tree_data *data;
  char *format;
  char *command;
  struct window_client_itemdata **item_list;
  u_int item_size;
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


