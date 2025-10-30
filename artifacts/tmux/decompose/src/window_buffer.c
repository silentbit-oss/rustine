static void window_buffer_free_item(struct window_buffer_itemdata *item)
{
  free((void *) item->name);
  free(item);
}


/*** DEPENDENCIES:
struct window_buffer_itemdata
{
  const char *name;
  u_int order;
  size_t size;
}
----------------------------
None
----------------------------
***/


static int window_buffer_cmp_name(const void *a0, const void *b0)
{
  const struct window_buffer_itemdata * const *a = a0;
  const struct window_buffer_itemdata * const *b = b0;
  return strcmp((*a)->name, (*b)->name);
}


/*** DEPENDENCIES:
struct window_buffer_itemdata
{
  const char *name;
  u_int order;
  size_t size;
}
----------------------------
None
----------------------------
***/


static int window_buffer_cmp_time(const void *a0, const void *b0)
{
  const struct window_buffer_itemdata * const *a = a0;
  const struct window_buffer_itemdata * const *b = b0;
  if ((*a)->order > (*b)->order)
  {
    return -1;
  }
  if ((*a)->order < (*b)->order)
  {
    return 1;
  }
  return strcmp((*a)->name, (*b)->name);
}


/*** DEPENDENCIES:
struct window_buffer_itemdata
{
  const char *name;
  u_int order;
  size_t size;
}
----------------------------
None
----------------------------
***/


static int window_buffer_cmp_size(const void *a0, const void *b0)
{
  const struct window_buffer_itemdata * const *a = a0;
  const struct window_buffer_itemdata * const *b = b0;
  if ((*a)->size > (*b)->size)
  {
    return -1;
  }
  if ((*a)->size < (*b)->size)
  {
    return 1;
  }
  return strcmp((*a)->name, (*b)->name);
}


/*** DEPENDENCIES:
struct window_buffer_itemdata
{
  const char *name;
  u_int order;
  size_t size;
}
----------------------------
None
----------------------------
***/


static void window_buffer_resize(struct window_pane *wp, u_int sx, u_int sy)
{
  struct window_buffer_modedata *data = wp->modedata;
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
struct window_buffer_modedata
{
  struct mode_tree_data *data;
  char *command;
  char *format;
  struct window_buffer_itemdata **item_list;
  u_int item_size;
}
----------------------------
None
----------------------------
***/


static void window_buffer_free(struct window_pane *wp)
{
  struct window_buffer_modedata *data = wp->modedata;
  u_int i;
  if (data == 0)
  {
    return;
  }
  mode_tree_free(data->data);
  for (i = 0; i < data->item_size; i += 1)
  {
    window_buffer_free_item(data->item_list[i]);
  }

  free(data->item_list);
  free(data->format);
  free(data->command);
  free(data);
}


/*** DEPENDENCIES:
static void window_buffer_free_item(struct window_buffer_itemdata *item)
{
  free((void *) item->name);
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
struct window_buffer_modedata
{
  struct mode_tree_data *data;
  char *command;
  char *format;
  struct window_buffer_itemdata **item_list;
  u_int item_size;
}
----------------------------
None
----------------------------
***/


static struct window_buffer_itemdata *window_buffer_add_item(struct window_buffer_modedata *data)
{
  struct window_buffer_itemdata *item;
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
struct window_buffer_itemdata
{
  const char *name;
  u_int order;
  size_t size;
}
----------------------------
struct window_buffer_modedata
{
  struct mode_tree_data *data;
  char *command;
  char *format;
  struct window_buffer_itemdata **item_list;
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


static int window_buffer_search(void *modedata, void *itemdata, const char *ss)
{
  struct window_buffer_itemdata *item = itemdata;
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  const char *bufdata;
  unsigned int bufdata_idx = 0;
  size_t bufsize;
  if ((pb_idx = paste_get_name(item->name)) == 0)
  {
    return 0;
  }
  if (strstr(item->name, ss) != 0)
  {
    return 1;
  }
  bufdata_idx = paste_buffer_data(pb, &bufsize);
  return memmem(bufdata, bufsize, ss, strlen(ss)) != 0;
}


/*** DEPENDENCIES:
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
struct window_buffer_itemdata
{
  const char *name;
  u_int order;
  size_t size;
}
----------------------------
const char *paste_buffer_data(struct paste_buffer *pb, size_t *size)
{
  if (size != 0)
  {
    *size = pb->size;
  }
  return pb->data;
}


----------------------------
struct paste_buffer *paste_get_name(const char *name)
{
  struct paste_buffer pbfind;
  if ((name == 0) || ((*name) == '\0'))
  {
    return 0;
  }
  pbfind.name = (char *) name;
  return paste_name_tree_RB_FIND(&paste_by_name, &pbfind);
}


----------------------------
None
----------------------------
***/


// hint:  ['end_idx_ref is a mutable refrence to unsigned int', 'cp_idx_ref is a mutable refrence to unsigned int', 'at_ref is a mutable refrence to size_t']
void helper_window_buffer_draw_1(unsigned int * const end_idx_ref, unsigned int * const cp_idx_ref, size_t * const at_ref, struct screen_write_ctx * const ctx, u_int sx, char line[1024], const char * const pdata, unsigned int pdata_idx, const char * const end, const char * const cp, size_t psize, u_int i, u_int cx, u_int cy)
{
  unsigned int end_idx = *end_idx_ref;
  unsigned int cp_idx = *cp_idx_ref;
  size_t at = *at_ref;
  at = 0;
  while (((&end[end_idx]) != ((&pdata[pdata_idx]) + psize)) && (end[end_idx] != '\n'))
  {
    if (((sizeof(line)) - at) > 5)
    {
      cp_idx = vis(line + at, *(&end[end_idx]), 0x08 | 0x01, 0);
      at = (&cp[cp_idx]) - line;
    }
    end_idx += 1;
  }

  if (at > sx)
  {
    at = sx;
  }
  line[at] = '\0';
  if ((*line) != '\0')
  {
    screen_write_cursormove(ctx, cx, cy + i);
    screen_write_puts(ctx, &grid_default_cell, "%s", line);
  }
  if ((&end[end_idx]) == ((&pdata[pdata_idx]) + psize))
  {
    break;
  }
  end_idx += 1;
  *end_idx_ref = end_idx;
  *cp_idx_ref = cp_idx;
  *at_ref = at;
}


/*** DEPENDENCIES:
extern const struct grid_cell grid_default_cell
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
char *vis(char *dst, int c, int flag, int nextc)
{
  unsigned int dst_idx = 0;
  if (((c == '\\') || ((flag & 0x400) == 0)) && ((((((((((u_int) c) <= 255) && isascii((u_char) c)) && (((((c != '*') && (c != '?')) && (c != '[')) && (c != '#')) || ((flag & 0x100) == 0))) && isgraph((u_char) c)) || (((flag & 0x04) == 0) && (c == ' '))) || (((flag & 0x08) == 0) && (c == '\t'))) || (((flag & 0x10) == 0) && (c == '\n'))) || ((flag & 0x20) && ((((c == '\b') || (c == '\007')) || (c == '\r')) || isgraph((u_char) c)))))
  {
    if (((c == '"') && ((flag & 0x200) != 0)) || ((c == '\\') && ((flag & 0x40) == 0)))
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
    }
    dst[dst_idx] = c;
    dst_idx += 1;
    dst[dst_idx] = '\0';
    return dst;
  }
  if (flag & 0x02)
  {
    helper_vis_1(&dst_idx, dst, c, nextc);
  }
  if ((((c & 0177) == ' ') || (flag & 0x01)) || ((flag & 0x100) && ((((c == '*') || (c == '?')) || (c == '[')) || (c == '#'))))
  {
    dst[dst_idx] = '\\';
    dst_idx += 1;
    dst[dst_idx] = ((((u_char) c) >> 6) & 07) + '0';
    dst_idx += 1;
    dst[dst_idx] = ((((u_char) c) >> 3) & 07) + '0';
    dst_idx += 1;
    dst[dst_idx] = (((u_char) c) & 07) + '0';
    dst_idx += 1;
    goto done;
  }
  if ((flag & 0x40) == 0)
  {
    dst[dst_idx] = '\\';
    dst_idx += 1;
  }
  if (c & 0200)
  {
    c &= 0177;
    dst[dst_idx] = 'M';
    dst_idx += 1;
  }
  if (iscntrl((u_char) c))
  {
    dst[dst_idx] = '^';
    dst_idx += 1;
    if (c == 0177)
    {
      dst[dst_idx] = '?';
      dst_idx += 1;
    }
    else
      dst[dst_idx] = c + '@';
    dst_idx += 1;
  }
  else
  {
    dst[dst_idx] = '-';
    dst_idx += 1;
    dst[dst_idx] = c;
    dst_idx += 1;
  }
  done:
  dst[dst_idx] = '\0';

  return dst;
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
None
----------------------------
***/


static void window_buffer_draw(void *modedata, void *itemdata, struct screen_write_ctx *ctx, u_int sx, u_int sy)
{
  struct window_buffer_itemdata *item = itemdata;
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  char line[1024];
  const char *pdata;
  unsigned int pdata_idx = 0;
  const char *end;
  unsigned int end_idx = 0;
  const char *cp;
  unsigned int cp_idx = 0;
  size_t psize;
  size_t at;
  u_int i;
  u_int cx = ctx->s->cx;
  u_int cy = ctx->s->cy;
  pb_idx = paste_get_name(item->name);
  if ((&pb[pb_idx]) == 0)
  {
    return;
  }
  pdata_idx = (end = &end[end_idx + end_idx]);
  for (i = 0; i < sy; i += 1)
  {
    helper_window_buffer_draw_1(&end_idx, &cp_idx, &at, ctx, sx, line, pdata, pdata_idx, end, cp, psize, i, cx, cy);
  }

}


/*** DEPENDENCIES:
void helper_window_buffer_draw_1(unsigned int * const end_idx_ref, unsigned int * const cp_idx_ref, size_t * const at_ref, struct screen_write_ctx * const ctx, u_int sx, char line[1024], const char * const pdata, unsigned int pdata_idx, const char * const end, const char * const cp, size_t psize, u_int i, u_int cx, u_int cy)
{
  unsigned int end_idx = *end_idx_ref;
  unsigned int cp_idx = *cp_idx_ref;
  size_t at = *at_ref;
  at = 0;
  while (((&end[end_idx]) != ((&pdata[pdata_idx]) + psize)) && (end[end_idx] != '\n'))
  {
    if (((sizeof(line)) - at) > 5)
    {
      cp_idx = vis(line + at, *(&end[end_idx]), 0x08 | 0x01, 0);
      at = (&cp[cp_idx]) - line;
    }
    end_idx += 1;
  }

  if (at > sx)
  {
    at = sx;
  }
  line[at] = '\0';
  if ((*line) != '\0')
  {
    screen_write_cursormove(ctx, cx, cy + i);
    screen_write_puts(ctx, &grid_default_cell, "%s", line);
  }
  if ((&end[end_idx]) == ((&pdata[pdata_idx]) + psize))
  {
    break;
  }
  end_idx += 1;
  *end_idx_ref = end_idx;
  *cp_idx_ref = cp_idx;
  *at_ref = at;
}


----------------------------
struct window_buffer_itemdata
{
  const char *name;
  u_int order;
  size_t size;
}
----------------------------
struct paste_buffer *paste_get_name(const char *name)
{
  struct paste_buffer pbfind;
  if ((name == 0) || ((*name) == '\0'))
  {
    return 0;
  }
  pbfind.name = (char *) name;
  return paste_name_tree_RB_FIND(&paste_by_name, &pbfind);
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
None
----------------------------
***/


static void window_buffer_do_paste(void *modedata, void *itemdata, struct client *c, key_code key)
{
  struct window_buffer_modedata *data = modedata;
  struct window_buffer_itemdata *item = itemdata;
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  if ((pb_idx = paste_get_name(item->name)) != 0)
  {
    mode_tree_run_command(c, 0, data->command, item->name);
  }
}


/*** DEPENDENCIES:
typedef unsigned long long key_code
----------------------------
struct window_buffer_modedata
{
  struct mode_tree_data *data;
  char *command;
  char *format;
  struct window_buffer_itemdata **item_list;
  u_int item_size;
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
struct window_buffer_itemdata
{
  const char *name;
  u_int order;
  size_t size;
}
----------------------------
struct paste_buffer *paste_get_name(const char *name)
{
  struct paste_buffer pbfind;
  if ((name == 0) || ((*name) == '\0'))
  {
    return 0;
  }
  pbfind.name = (char *) name;
  return paste_name_tree_RB_FIND(&paste_by_name, &pbfind);
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
***/


static void window_buffer_do_delete(void *modedata, void *itemdata, struct client *c, key_code key)
{
  struct window_buffer_modedata *data = modedata;
  struct window_buffer_itemdata *item = itemdata;
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  if (item == mode_tree_get_current(data->data))
  {
    mode_tree_down(data->data, 0);
  }
  if ((pb_idx = paste_get_name(item->name)) != 0)
  {
    paste_free(pb);
  }
}


/*** DEPENDENCIES:
typedef unsigned long long key_code
----------------------------
struct window_buffer_modedata
{
  struct mode_tree_data *data;
  char *command;
  char *format;
  struct window_buffer_itemdata **item_list;
  u_int item_size;
}
----------------------------
struct window_buffer_itemdata
{
  const char *name;
  u_int order;
  size_t size;
}
----------------------------
struct paste_buffer *paste_get_name(const char *name)
{
  struct paste_buffer pbfind;
  if ((name == 0) || ((*name) == '\0'))
  {
    return 0;
  }
  pbfind.name = (char *) name;
  return paste_name_tree_RB_FIND(&paste_by_name, &pbfind);
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
void paste_free(struct paste_buffer *pb)
{
  paste_name_tree_RB_REMOVE(&paste_by_name, pb);
  paste_time_tree_RB_REMOVE(&paste_by_time, pb);
  if (pb->automatic)
  {
    paste_num_automatic -= 1;
  }
  free(pb->data);
  free(pb->name);
  free(pb);
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


// hint:  ['item_idx_ref is a mutable refrence to unsigned int', 'pb_idx_ref is a mutable refrence to unsigned int', 'text_idx_ref is a mutable refrence to unsigned int', 'cp_idx_ref is a mutable refrence to unsigned int', 'ft_idx_ref is a mutable refrence to unsigned int']
void helper_window_buffer_build_1(unsigned int * const item_idx_ref, unsigned int * const pb_idx_ref, unsigned int * const text_idx_ref, unsigned int * const cp_idx_ref, unsigned int * const ft_idx_ref, const char * const filter, struct window_buffer_modedata * const data, struct window_buffer_itemdata * const item, u_int i, struct paste_buffer * const pb, char * const text, char * const cp, struct format_tree * const ft)
{
  unsigned int item_idx = *item_idx_ref;
  unsigned int pb_idx = *pb_idx_ref;
  unsigned int text_idx = *text_idx_ref;
  unsigned int cp_idx = *cp_idx_ref;
  unsigned int ft_idx = *ft_idx_ref;
  item_idx = data->item_list[i];
  pb_idx = paste_get_name(item->name);
  if ((&pb[pb_idx]) == 0)
  {
    continue;
  }
  ft_idx = format_create(0, 0, 0, 0);
  format_defaults_paste_buffer(ft, pb);
  if (filter != 0)
  {
    cp_idx = format_expand(ft, filter);
    if (!format_true(cp))
    {
      free(cp);
      format_free(ft);
      continue;
    }
    free(cp);
  }
  text_idx = format_expand(ft, data->format);
  mode_tree_add(data->data, 0, item, item->order, item->name, text, -1);
  free(text);
  format_free(ft);
  *item_idx_ref = item_idx;
  *pb_idx_ref = pb_idx;
  *text_idx_ref = text_idx;
  *cp_idx_ref = cp_idx;
  *ft_idx_ref = ft_idx;
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
struct window_buffer_modedata
{
  struct mode_tree_data *data;
  char *command;
  char *format;
  struct window_buffer_itemdata **item_list;
  u_int item_size;
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
struct window_buffer_itemdata
{
  const char *name;
  u_int order;
  size_t size;
}
----------------------------
struct paste_buffer *paste_get_name(const char *name)
{
  struct paste_buffer pbfind;
  if ((name == 0) || ((*name) == '\0'))
  {
    return 0;
  }
  pbfind.name = (char *) name;
  return paste_name_tree_RB_FIND(&paste_by_name, &pbfind);
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
***/


static void window_buffer_build(void *modedata, u_int sort_type, uint64_t *tag, const char *filter)
{
  struct window_buffer_modedata *data = modedata;
  struct window_buffer_itemdata *item;
  unsigned int item_idx = 0;
  u_int i;
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  char *text;
  unsigned int text_idx = 0;
  char *cp;
  unsigned int cp_idx = 0;
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  for (i = 0; i < data->item_size; i += 1)
  {
    window_buffer_free_item(data->item_list[i]);
  }

  free(data->item_list);
  data->item_list = 0;
  data->item_size = 0;
  pb_idx = 0;
  while ((pb_idx = paste_walk(pb_idx)) != 0)
  {
    item_idx = window_buffer_add_item(data);
    item->name = xstrdup(paste_buffer_name(pb));
    paste_buffer_data(pb, &item->size);
    item->order = paste_buffer_order(pb);
  }

  switch (sort_type)
  {
    case WINDOW_BUFFER_BY_NAME:
    {
      qsort(data->item_list, data->item_size, sizeof(*data->item_list), window_buffer_cmp_name);
      break;
    }

    case WINDOW_BUFFER_BY_TIME:
    {
      qsort(data->item_list, data->item_size, sizeof(*data->item_list), window_buffer_cmp_time);
      break;
    }

    case WINDOW_BUFFER_BY_SIZE:
    {
      qsort(data->item_list, data->item_size, sizeof(*data->item_list), window_buffer_cmp_size);
      break;
    }

  }

  for (i = 0; i < data->item_size; i += 1)
  {
    helper_window_buffer_build_1(&item_idx, &pb_idx, &text_idx, &cp_idx, &ft_idx, filter, data, item, i, pb, text, cp, ft);
  }

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
static void window_buffer_free_item(struct window_buffer_itemdata *item)
{
  free((void *) item->name);
  free(item);
}


----------------------------
static struct window_buffer_itemdata *window_buffer_add_item(struct window_buffer_modedata *data)
{
  struct window_buffer_itemdata *item;
  unsigned int item_idx = 0;
  data->item_list = xreallocarray(data->item_list, data->item_size + 1, sizeof(*data->item_list));
  item_idx = (data->item_list[data->item_size++] = xcalloc(1, sizeof(*item_idx)));
  return item;
}


----------------------------
const char *paste_buffer_name(struct paste_buffer *pb)
{
  return pb->name;
}


----------------------------
struct window_buffer_modedata
{
  struct mode_tree_data *data;
  char *command;
  char *format;
  struct window_buffer_itemdata **item_list;
  u_int item_size;
}
----------------------------
static int window_buffer_cmp_time(const void *a0, const void *b0)
{
  const struct window_buffer_itemdata * const *a = a0;
  const struct window_buffer_itemdata * const *b = b0;
  if ((*a)->order > (*b)->order)
  {
    return -1;
  }
  if ((*a)->order < (*b)->order)
  {
    return 1;
  }
  return strcmp((*a)->name, (*b)->name);
}


----------------------------
struct window_buffer_itemdata
{
  const char *name;
  u_int order;
  size_t size;
}
----------------------------
void helper_window_buffer_build_1(unsigned int * const item_idx_ref, unsigned int * const pb_idx_ref, unsigned int * const text_idx_ref, unsigned int * const cp_idx_ref, unsigned int * const ft_idx_ref, const char * const filter, struct window_buffer_modedata * const data, struct window_buffer_itemdata * const item, u_int i, struct paste_buffer * const pb, char * const text, char * const cp, struct format_tree * const ft)
{
  unsigned int item_idx = *item_idx_ref;
  unsigned int pb_idx = *pb_idx_ref;
  unsigned int text_idx = *text_idx_ref;
  unsigned int cp_idx = *cp_idx_ref;
  unsigned int ft_idx = *ft_idx_ref;
  item_idx = data->item_list[i];
  pb_idx = paste_get_name(item->name);
  if ((&pb[pb_idx]) == 0)
  {
    continue;
  }
  ft_idx = format_create(0, 0, 0, 0);
  format_defaults_paste_buffer(ft, pb);
  if (filter != 0)
  {
    cp_idx = format_expand(ft, filter);
    if (!format_true(cp))
    {
      free(cp);
      format_free(ft);
      continue;
    }
    free(cp);
  }
  text_idx = format_expand(ft, data->format);
  mode_tree_add(data->data, 0, item, item->order, item->name, text, -1);
  free(text);
  format_free(ft);
  *item_idx_ref = item_idx;
  *pb_idx_ref = pb_idx;
  *text_idx_ref = text_idx;
  *cp_idx_ref = cp_idx;
  *ft_idx_ref = ft_idx;
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
u_int paste_buffer_order(struct paste_buffer *pb)
{
  return pb->order;
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
static int window_buffer_cmp_size(const void *a0, const void *b0)
{
  const struct window_buffer_itemdata * const *a = a0;
  const struct window_buffer_itemdata * const *b = b0;
  if ((*a)->size > (*b)->size)
  {
    return -1;
  }
  if ((*a)->size < (*b)->size)
  {
    return 1;
  }
  return strcmp((*a)->name, (*b)->name);
}


----------------------------
const char *paste_buffer_data(struct paste_buffer *pb, size_t *size)
{
  if (size != 0)
  {
    *size = pb->size;
  }
  return pb->data;
}


----------------------------
static int window_buffer_cmp_name(const void *a0, const void *b0)
{
  const struct window_buffer_itemdata * const *a = a0;
  const struct window_buffer_itemdata * const *b = b0;
  return strcmp((*a)->name, (*b)->name);
}


----------------------------
None
----------------------------
***/


static void window_buffer_key(struct window_pane *wp, struct client *c, struct session *s, key_code key, struct mouse_event *m)
{
  struct window_buffer_modedata *data = wp->modedata;
  struct mode_tree_data *mtd = data->data;
  struct window_buffer_itemdata *item;
  unsigned int item_idx = 0;
  int finished;
  finished = mode_tree_key(mtd, c, &key, m, 0, 0);
  switch (key)
  {
    case 'd':
    {
      item_idx = mode_tree_get_current(mtd);
      window_buffer_do_delete(data, item, c, key);
      mode_tree_build(mtd);
      break;
    }

    case 'D':
    {
      mode_tree_each_tagged(mtd, window_buffer_do_delete, c, key, 0);
      mode_tree_build(mtd);
      break;
    }

    case 'P':
    {
      mode_tree_each_tagged(mtd, window_buffer_do_paste, c, key, 0);
      finished = 1;
      break;
    }

    case 'p':

    case '\r':
    {
      item_idx = mode_tree_get_current(mtd);
      window_buffer_do_paste(data, item, c, key);
      finished = 1;
      break;
    }

  }

  if (finished || (paste_get_top(0) == 0))
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
typedef unsigned long long key_code
----------------------------
struct window_buffer_modedata
{
  struct mode_tree_data *data;
  char *command;
  char *format;
  struct window_buffer_itemdata **item_list;
  u_int item_size;
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
struct window_buffer_itemdata
{
  const char *name;
  u_int order;
  size_t size;
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
static void window_buffer_do_delete(void *modedata, void *itemdata, struct client *c, key_code key)
{
  struct window_buffer_modedata *data = modedata;
  struct window_buffer_itemdata *item = itemdata;
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  if (item == mode_tree_get_current(data->data))
  {
    mode_tree_down(data->data, 0);
  }
  if ((pb_idx = paste_get_name(item->name)) != 0)
  {
    paste_free(pb);
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
static void window_buffer_do_paste(void *modedata, void *itemdata, struct client *c, key_code key)
{
  struct window_buffer_modedata *data = modedata;
  struct window_buffer_itemdata *item = itemdata;
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  if ((pb_idx = paste_get_name(item->name)) != 0)
  {
    mode_tree_run_command(c, 0, data->command, item->name);
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


static struct screen *window_buffer_init(struct window_pane *wp, struct cmd_find_state *fs, struct args *args)
{
  struct window_buffer_modedata *data;
  struct screen *s;
  wp->modedata = (data = xcalloc(1, sizeof(*data)));
  if ((args == 0) || (!args_has(args, 'F')))
  {
    data->format = xstrdup("#{buffer_size} bytes (#{t:buffer_created})");
  }
  else
    data->format = xstrdup(args_get(args, 'F'));
  if ((args == 0) || (args->argc == 0))
  {
    data->command = xstrdup("paste-buffer -b '%%'");
  }
  else
    data->command = xstrdup(args->argv[0]);
  data->data = mode_tree_start(wp, args, window_buffer_build, window_buffer_draw, window_buffer_search, data, window_buffer_sort_list, (sizeof(window_buffer_sort_list)) / (sizeof(window_buffer_sort_list[0])), &s);
  mode_tree_zoom(data->data, args);
  mode_tree_build(data->data);
  mode_tree_draw(data->data);
  return s;
}


/*** DEPENDENCIES:
static void window_buffer_draw(void *modedata, void *itemdata, struct screen_write_ctx *ctx, u_int sx, u_int sy)
{
  struct window_buffer_itemdata *item = itemdata;
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  char line[1024];
  const char *pdata;
  unsigned int pdata_idx = 0;
  const char *end;
  unsigned int end_idx = 0;
  const char *cp;
  unsigned int cp_idx = 0;
  size_t psize;
  size_t at;
  u_int i;
  u_int cx = ctx->s->cx;
  u_int cy = ctx->s->cy;
  pb_idx = paste_get_name(item->name);
  if ((&pb[pb_idx]) == 0)
  {
    return;
  }
  pdata_idx = (end = &end[end_idx + end_idx]);
  for (i = 0; i < sy; i += 1)
  {
    helper_window_buffer_draw_1(&end_idx, &cp_idx, &at, ctx, sx, line, pdata, pdata_idx, end, cp, psize, i, cx, cy);
  }

}


----------------------------
struct window_buffer_modedata
{
  struct mode_tree_data *data;
  char *command;
  char *format;
  struct window_buffer_itemdata **item_list;
  u_int item_size;
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
static int window_buffer_search(void *modedata, void *itemdata, const char *ss)
{
  struct window_buffer_itemdata *item = itemdata;
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  const char *bufdata;
  unsigned int bufdata_idx = 0;
  size_t bufsize;
  if ((pb_idx = paste_get_name(item->name)) == 0)
  {
    return 0;
  }
  if (strstr(item->name, ss) != 0)
  {
    return 1;
  }
  bufdata_idx = paste_buffer_data(pb, &bufsize);
  return memmem(bufdata, bufsize, ss, strlen(ss)) != 0;
}


----------------------------
static const char *window_buffer_sort_list[] = {"time", "name", "size"}
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
static void window_buffer_build(void *modedata, u_int sort_type, uint64_t *tag, const char *filter)
{
  struct window_buffer_modedata *data = modedata;
  struct window_buffer_itemdata *item;
  unsigned int item_idx = 0;
  u_int i;
  struct paste_buffer *pb;
  unsigned int pb_idx = 0;
  char *text;
  unsigned int text_idx = 0;
  char *cp;
  unsigned int cp_idx = 0;
  struct format_tree *ft;
  unsigned int ft_idx = 0;
  for (i = 0; i < data->item_size; i += 1)
  {
    window_buffer_free_item(data->item_list[i]);
  }

  free(data->item_list);
  data->item_list = 0;
  data->item_size = 0;
  pb_idx = 0;
  while ((pb_idx = paste_walk(pb_idx)) != 0)
  {
    item_idx = window_buffer_add_item(data);
    item->name = xstrdup(paste_buffer_name(pb));
    paste_buffer_data(pb, &item->size);
    item->order = paste_buffer_order(pb);
  }

  switch (sort_type)
  {
    case WINDOW_BUFFER_BY_NAME:
    {
      qsort(data->item_list, data->item_size, sizeof(*data->item_list), window_buffer_cmp_name);
      break;
    }

    case WINDOW_BUFFER_BY_TIME:
    {
      qsort(data->item_list, data->item_size, sizeof(*data->item_list), window_buffer_cmp_time);
      break;
    }

    case WINDOW_BUFFER_BY_SIZE:
    {
      qsort(data->item_list, data->item_size, sizeof(*data->item_list), window_buffer_cmp_size);
      break;
    }

  }

  for (i = 0; i < data->item_size; i += 1)
  {
    helper_window_buffer_build_1(&item_idx, &pb_idx, &text_idx, &cp_idx, &ft_idx, filter, data, item, i, pb, text, cp, ft);
  }

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


