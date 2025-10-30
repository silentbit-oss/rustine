static u_short layout_checksum(const char *layout)
{
  unsigned int layout_idx = 0;
  u_short csum;
  csum = 0;
  for (; layout[layout_idx] != '\0'; layout_idx += 1)
  {
    csum = (csum >> 1) + ((csum & 1) << 15);
    csum += layout[layout_idx];
  }

  return csum;
}


/*** DEPENDENCIES:
***/


static int layout_append(struct layout_cell *lc, char *buf, size_t len)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  char tmp[64];
  size_t tmplen;
  const char *brackets = "][";
  unsigned int brackets_idx = 0;
  if (len == 0)
  {
    return -1;
  }
  if (lc->wp != 0)
  {
    tmplen = xsnprintf(tmp, sizeof(tmp), "%ux%u,%u,%u,%u", lc->sx, lc->sy, lc->xoff, lc->yoff, lc->wp->id);
  }
  else
  {
    tmplen = xsnprintf(tmp, sizeof(tmp), "%ux%u,%u,%u", lc->sx, lc->sy, lc->xoff, lc->yoff);
  }
  if (tmplen > ((sizeof(tmp)) - 1))
  {
    return -1;
  }
  if (strlcat(buf, tmp, len) >= len)
  {
    return -1;
  }
  switch (lc->type)
  {
    case LAYOUT_LEFTRIGHT:
    {
      brackets_idx = "}{";
    }

    case LAYOUT_TOPBOTTOM:
    {
      if (strlcat(buf, &brackets[1 + brackets_idx], len) >= len)
      {
        return -1;
      }
      for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
      {
        if (layout_append(lcchild, buf, len) != 0)
        {
          return -1;
        }
        if (strlcat(buf, ",", len) >= len)
        {
          return -1;
        }
      }

      buf[strlen(buf) - 1] = brackets[0 + brackets_idx];
      break;
    }

    case LAYOUT_WINDOWPANE:
    {
      break;
    }

  }

  return 0;
}


/*** DEPENDENCIES:
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
None
----------------------------
***/


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


/*** DEPENDENCIES:
static u_short layout_checksum(const char *layout)
{
  unsigned int layout_idx = 0;
  u_short csum;
  csum = 0;
  for (; layout[layout_idx] != '\0'; layout_idx += 1)
  {
    csum = (csum >> 1) + ((csum & 1) << 15);
    csum += layout[layout_idx];
  }

  return csum;
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
static int layout_append(struct layout_cell *lc, char *buf, size_t len)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  char tmp[64];
  size_t tmplen;
  const char *brackets = "][";
  unsigned int brackets_idx = 0;
  if (len == 0)
  {
    return -1;
  }
  if (lc->wp != 0)
  {
    tmplen = xsnprintf(tmp, sizeof(tmp), "%ux%u,%u,%u,%u", lc->sx, lc->sy, lc->xoff, lc->yoff, lc->wp->id);
  }
  else
  {
    tmplen = xsnprintf(tmp, sizeof(tmp), "%ux%u,%u,%u", lc->sx, lc->sy, lc->xoff, lc->yoff);
  }
  if (tmplen > ((sizeof(tmp)) - 1))
  {
    return -1;
  }
  if (strlcat(buf, tmp, len) >= len)
  {
    return -1;
  }
  switch (lc->type)
  {
    case LAYOUT_LEFTRIGHT:
    {
      brackets_idx = "}{";
    }

    case LAYOUT_TOPBOTTOM:
    {
      if (strlcat(buf, &brackets[1 + brackets_idx], len) >= len)
      {
        return -1;
      }
      for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
      {
        if (layout_append(lcchild, buf, len) != 0)
        {
          return -1;
        }
        if (strlcat(buf, ",", len) >= len)
        {
          return -1;
        }
      }

      buf[strlen(buf) - 1] = brackets[0 + brackets_idx];
      break;
    }

    case LAYOUT_WINDOWPANE:
    {
      break;
    }

  }

  return 0;
}


----------------------------
None
----------------------------
***/


static struct layout_cell *layout_find_bottomright(struct layout_cell *lc)
{
  unsigned int lc_idx = 0;
  if (lc->type == LAYOUT_WINDOWPANE)
  {
    return lc;
  }
  lc_idx = *((struct layout_cells *) (&lc_idx->cells)->tqh_last)->tqh_last;
  return layout_find_bottomright(lc);
}


/*** DEPENDENCIES:
None
----------------------------
***/


static struct layout_cell *layout_construct(struct layout_cell *lcparent, const char **layout)
{
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  u_int sx;
  u_int sy;
  u_int xoff;
  u_int yoff;
  const char *saved;
  unsigned int saved_idx = 0;
  if (!isdigit((u_char) (*(*layout))))
  {
    return 0;
  }
  if (sscanf(*layout, "%ux%u,%u,%u", &sx, &sy, &xoff, &yoff) != 4)
  {
    return 0;
  }
  while (isdigit((u_char) (*(*layout))))
  {
    *layout += 1;
  }

  if ((*(*layout)) != 'x')
  {
    return 0;
  }
  *layout += 1;
  while (isdigit((u_char) (*(*layout))))
  {
    *layout += 1;
  }

  if ((*(*layout)) != ',')
  {
    return 0;
  }
  *layout += 1;
  while (isdigit((u_char) (*(*layout))))
  {
    *layout += 1;
  }

  if ((*(*layout)) != ',')
  {
    return 0;
  }
  *layout += 1;
  while (isdigit((u_char) (*(*layout))))
  {
    *layout += 1;
  }

  if ((*(*layout)) == ',')
  {
    saved_idx = *layout;
    *layout += 1;
    while (isdigit((u_char) (*(*layout))))
    {
      *layout += 1;
    }

    if ((*(*layout)) == 'x')
    {
      *layout = &saved[saved_idx];
    }
  }
  lc_idx = layout_create_cell(lcparent);
  lc->sx = sx;
  lc->sy = sy;
  lc->xoff = xoff;
  lc->yoff = yoff;
  switch (*(*layout))
  {
    case ',':

    case '}':

    case ']':

    case '\0':
    {
      return lc;
    }

    case '{':
    {
      lc->type = LAYOUT_LEFTRIGHT;
      break;
    }

    case '[':
    {
      lc->type = LAYOUT_TOPBOTTOM;
      break;
    }

    default:
    {
      goto fail;
    }

  }

  do
  {
    *layout += 1;
    lcchild_idx = layout_construct(lc, layout);
    if ((&lcchild[lcchild_idx]) == 0)
    {
      goto fail;
    }
    do
    {
      lcchild->entry.tqe_next = 0;
      lcchild->entry.tqe_prev = (&lc->cells)->tqh_last;
      *(&lc->cells)->tqh_last = &lcchild[lcchild_idx];
      (&lc->cells)->tqh_last = &lcchild->entry.tqe_next;
    }
    while (0);
  }
  while ((*(*layout)) == ',');
  switch (lc->type)
  {
    case LAYOUT_LEFTRIGHT:
    {
      if ((*(*layout)) != '}')
      {
        goto fail;
      }
      break;
    }

    case LAYOUT_TOPBOTTOM:
    {
      if ((*(*layout)) != ']')
      {
        goto fail;
      }
      break;
    }

    default:
    {
      goto fail;
    }

  }

  *layout += 1;
  return lc;
  fail:
  layout_free_cell(lc);

  return 0;
}


/*** DEPENDENCIES:
void layout_free_cell(struct layout_cell *lc)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  switch (lc->type)
  {
    case LAYOUT_LEFTRIGHT:

    case LAYOUT_TOPBOTTOM:
    {
      while (!((&lc->cells)->tqh_first == 0))
      {
        lcchild_idx = (&lc->cells)->tqh_first;
        do
        {
          if (lcchild->entry.tqe_next != 0)
          {
            lcchild->entry.tqe_next->entry.tqe_prev = lcchild->entry.tqe_prev;
          }
          else
            (&lc->cells)->tqh_last = lcchild->entry.tqe_prev;
          *lcchild->entry.tqe_prev = lcchild->entry.tqe_next;
          ;
          ;
        }
        while (0);
        layout_free_cell(lcchild);
      }

      break;
    }

    case LAYOUT_WINDOWPANE:
    {
      if (lc->wp != 0)
      {
        lc->wp->layout_cell = 0;
      }
      break;
    }

  }

  free(lc);
}


----------------------------
struct layout_cell *layout_create_cell(struct layout_cell *lcparent)
{
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  lc_idx = xmalloc(sizeof(*lc_idx));
  lc->type = LAYOUT_WINDOWPANE;
  lc->parent = lcparent;
  do
  {
    (&lc->cells)->tqh_first = 0;
    (&lc->cells)->tqh_last = &(&lc->cells)->tqh_first;
  }
  while (0);
  lc->sx = 4294967295U;
  lc->sy = 4294967295U;
  lc->xoff = 4294967295U;
  lc->yoff = 4294967295U;
  lc->wp = 0;
  return lc;
}


----------------------------
None
----------------------------
***/


static void layout_assign(struct window_pane **wp, struct layout_cell *lc)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  switch (lc->type)
  {
    case LAYOUT_WINDOWPANE:
    {
      layout_make_leaf(lc, *wp);
      *wp = (*wp)->entry.tqe_next;
      return;
    }

    case LAYOUT_LEFTRIGHT:

    case LAYOUT_TOPBOTTOM:
    {
      for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
      {
        layout_assign(wp, lcchild);
      }

      return;
    }

  }

}


/*** DEPENDENCIES:
void layout_make_leaf(struct layout_cell *lc, struct window_pane *wp)
{
  lc->type = LAYOUT_WINDOWPANE;
  do
  {
    (&lc->cells)->tqh_first = 0;
    (&lc->cells)->tqh_last = &(&lc->cells)->tqh_first;
  }
  while (0);
  wp->layout_cell = lc;
  lc->wp = wp;
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
void layout_fix_panes(struct window *w, u_int wsx, u_int wsy)
{
  struct window_pane *wp;
  unsigned int wp_idx = 0;
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  u_int sx;
  u_int sy;
  int shift;
  int status;
  int at_top;
  status = options_get_number(w->options, "pane-border-status");
  at_top = status == 1;
  for (wp_idx = (&w->panes)->tqh_first; (&wp[wp_idx]) != 0; wp_idx = wp_idx->entry.tqe_next)
  {
    helper_layout_fix_panes_1(&lc_idx, &sx, &sy, &shift, wsx, wsy, wp, lc, status, at_top);
  }

}


----------------------------
void notify_window(const char *name, struct window *w)
{
  struct cmd_find_state fs;
  cmd_find_from_window(&fs, w, 0);
  notify_add(name, &fs, 0, 0, w, 0);
}


----------------------------
void layout_resize(struct window *w, u_int sx, u_int sy)
{
  struct layout_cell *lc = w->layout_root;
  int xlimit;
  int ylimit;
  int xchange;
  int ychange;
  xchange = sx - w->sx;
  xlimit = layout_resize_check(w, lc, LAYOUT_LEFTRIGHT);
  if ((xchange < 0) && (xchange < (-xlimit)))
  {
    xchange = -xlimit;
  }
  if (xlimit == 0)
  {
    if (sx <= lc->sx)
    {
      xchange = 0;
    }
    else
      xchange = sx - lc->sx;
  }
  if (xchange != 0)
  {
    layout_resize_adjust(w, lc, LAYOUT_LEFTRIGHT, xchange);
  }
  ychange = sy - w->sy;
  ylimit = layout_resize_check(w, lc, LAYOUT_TOPBOTTOM);
  if ((ychange < 0) && (ychange < (-ylimit)))
  {
    ychange = -ylimit;
  }
  if (ylimit == 0)
  {
    if (sy <= lc->sy)
    {
      ychange = 0;
    }
    else
      ychange = sy - lc->sy;
  }
  if (ychange != 0)
  {
    layout_resize_adjust(w, lc, LAYOUT_TOPBOTTOM, ychange);
  }
  layout_fix_offsets(lc);
  layout_fix_panes(w, sx, sy);
}


----------------------------
static u_short layout_checksum(const char *layout)
{
  unsigned int layout_idx = 0;
  u_short csum;
  csum = 0;
  for (; layout[layout_idx] != '\0'; layout_idx += 1)
  {
    csum = (csum >> 1) + ((csum & 1) << 15);
    csum += layout[layout_idx];
  }

  return csum;
}


----------------------------
void window_resize(struct window *w, u_int sx, u_int sy)
{
  w->sx = sx;
  w->sy = sy;
}


----------------------------
static struct layout_cell *layout_find_bottomright(struct layout_cell *lc)
{
  unsigned int lc_idx = 0;
  if (lc->type == LAYOUT_WINDOWPANE)
  {
    return lc;
  }
  lc_idx = *((struct layout_cells *) (&lc_idx->cells)->tqh_last)->tqh_last;
  return layout_find_bottomright(lc);
}


----------------------------
void layout_destroy_cell(struct window *w, struct layout_cell *lc, struct layout_cell **lcroot)
{
  unsigned int lc_idx = 0;
  struct layout_cell *lcother;
  unsigned int lcother_idx = 0;
  struct layout_cell *lcparent;
  unsigned int lcparent_idx = 0;
  lcparent_idx = lc->parent;
  if ((&lcparent[lcparent_idx]) == 0)
  {
    layout_free_cell(lc);
    *lcroot = 0;
    return;
  }
  if ((&lc[lc_idx]) == (&lcparent->cells)->tqh_first)
  {
    lcother_idx = lc->entry.tqe_next;
  }
  else
    lcother_idx = *((struct layout_cells *) lc->entry.tqe_prev)->tqh_last;
  if (lcparent->type == LAYOUT_LEFTRIGHT)
  {
    layout_resize_adjust(w, lcother, lcparent->type, lc->sx + 1);
  }
  else
    layout_resize_adjust(w, lcother, lcparent->type, lc->sy + 1);
  do
  {
    if (lc->entry.tqe_next != 0)
    {
      lc->entry.tqe_next->entry.tqe_prev = lc->entry.tqe_prev;
    }
    else
      (&lcparent->cells)->tqh_last = lc->entry.tqe_prev;
    *lc->entry.tqe_prev = lc->entry.tqe_next;
    ;
    ;
  }
  while (0);
  layout_free_cell(lc);
  lc_idx = (&lcparent->cells)->tqh_first;
  if (lc->entry.tqe_next == 0)
  {
    helper_layout_destroy_cell_1(lc, lcroot, lc_idx, lcparent);
  }
}


----------------------------
static void layout_assign(struct window_pane **wp, struct layout_cell *lc)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  switch (lc->type)
  {
    case LAYOUT_WINDOWPANE:
    {
      layout_make_leaf(lc, *wp);
      *wp = (*wp)->entry.tqe_next;
      return;
    }

    case LAYOUT_LEFTRIGHT:

    case LAYOUT_TOPBOTTOM:
    {
      for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
      {
        layout_assign(wp, lcchild);
      }

      return;
    }

  }

}


----------------------------
static struct layout_cell *layout_construct(struct layout_cell *lcparent, const char **layout)
{
  struct layout_cell *lc;
  unsigned int lc_idx = 0;
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  u_int sx;
  u_int sy;
  u_int xoff;
  u_int yoff;
  const char *saved;
  unsigned int saved_idx = 0;
  if (!isdigit((u_char) (*(*layout))))
  {
    return 0;
  }
  if (sscanf(*layout, "%ux%u,%u,%u", &sx, &sy, &xoff, &yoff) != 4)
  {
    return 0;
  }
  while (isdigit((u_char) (*(*layout))))
  {
    *layout += 1;
  }

  if ((*(*layout)) != 'x')
  {
    return 0;
  }
  *layout += 1;
  while (isdigit((u_char) (*(*layout))))
  {
    *layout += 1;
  }

  if ((*(*layout)) != ',')
  {
    return 0;
  }
  *layout += 1;
  while (isdigit((u_char) (*(*layout))))
  {
    *layout += 1;
  }

  if ((*(*layout)) != ',')
  {
    return 0;
  }
  *layout += 1;
  while (isdigit((u_char) (*(*layout))))
  {
    *layout += 1;
  }

  if ((*(*layout)) == ',')
  {
    saved_idx = *layout;
    *layout += 1;
    while (isdigit((u_char) (*(*layout))))
    {
      *layout += 1;
    }

    if ((*(*layout)) == 'x')
    {
      *layout = &saved[saved_idx];
    }
  }
  lc_idx = layout_create_cell(lcparent);
  lc->sx = sx;
  lc->sy = sy;
  lc->xoff = xoff;
  lc->yoff = yoff;
  switch (*(*layout))
  {
    case ',':

    case '}':

    case ']':

    case '\0':
    {
      return lc;
    }

    case '{':
    {
      lc->type = LAYOUT_LEFTRIGHT;
      break;
    }

    case '[':
    {
      lc->type = LAYOUT_TOPBOTTOM;
      break;
    }

    default:
    {
      goto fail;
    }

  }

  do
  {
    *layout += 1;
    lcchild_idx = layout_construct(lc, layout);
    if ((&lcchild[lcchild_idx]) == 0)
    {
      goto fail;
    }
    do
    {
      lcchild->entry.tqe_next = 0;
      lcchild->entry.tqe_prev = (&lc->cells)->tqh_last;
      *(&lc->cells)->tqh_last = &lcchild[lcchild_idx];
      (&lc->cells)->tqh_last = &lcchild->entry.tqe_next;
    }
    while (0);
  }
  while ((*(*layout)) == ',');
  switch (lc->type)
  {
    case LAYOUT_LEFTRIGHT:
    {
      if ((*(*layout)) != '}')
      {
        goto fail;
      }
      break;
    }

    case LAYOUT_TOPBOTTOM:
    {
      if ((*(*layout)) != ']')
      {
        goto fail;
      }
      break;
    }

    default:
    {
      goto fail;
    }

  }

  *layout += 1;
  return lc;
  fail:
  layout_free_cell(lc);

  return 0;
}


----------------------------
void layout_free_cell(struct layout_cell *lc)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  switch (lc->type)
  {
    case LAYOUT_LEFTRIGHT:

    case LAYOUT_TOPBOTTOM:
    {
      while (!((&lc->cells)->tqh_first == 0))
      {
        lcchild_idx = (&lc->cells)->tqh_first;
        do
        {
          if (lcchild->entry.tqe_next != 0)
          {
            lcchild->entry.tqe_next->entry.tqe_prev = lcchild->entry.tqe_prev;
          }
          else
            (&lc->cells)->tqh_last = lcchild->entry.tqe_prev;
          *lcchild->entry.tqe_prev = lcchild->entry.tqe_next;
          ;
          ;
        }
        while (0);
        layout_free_cell(lcchild);
      }

      break;
    }

    case LAYOUT_WINDOWPANE:
    {
      if (lc->wp != 0)
      {
        lc->wp->layout_cell = 0;
      }
      break;
    }

  }

  free(lc);
}


----------------------------
void layout_print_cell(struct layout_cell *lc, const char *hdr, u_int n)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  const char *type;
  unsigned int type_idx = 0;
  switch (lc->type)
  {
    case LAYOUT_LEFTRIGHT:
    {
      type_idx = "LEFTRIGHT";
      break;
    }

    case LAYOUT_TOPBOTTOM:
    {
      type_idx = "TOPBOTTOM";
      break;
    }

    case LAYOUT_WINDOWPANE:
    {
      type_idx = "WINDOWPANE";
      break;
    }

    default:
    {
      type_idx = "UNKNOWN";
      break;
    }

  }

  log_debug("%s:%*s%p type %s [parent %p] wp=%p [%u,%u %ux%u]", hdr, n, " ", lc, type, lc->parent, lc->wp, lc->xoff, lc->yoff, lc->sx, lc->sy);
  switch (lc->type)
  {
    case LAYOUT_LEFTRIGHT:

    case LAYOUT_TOPBOTTOM:
    {
      for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
      {
        layout_print_cell(lcchild, hdr, n + 1);
      }

      break;
    }

    case LAYOUT_WINDOWPANE:
    {
      break;
    }

  }

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
void layout_fix_offsets(struct layout_cell *lc)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  u_int xoff;
  u_int yoff;
  if (lc->type == LAYOUT_LEFTRIGHT)
  {
    xoff = lc->xoff;
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      lcchild->xoff = xoff;
      lcchild->yoff = lc->yoff;
      if (lcchild->type != LAYOUT_WINDOWPANE)
      {
        layout_fix_offsets(lcchild);
      }
      xoff += lcchild->sx + 1;
    }

  }
  else
  {
    yoff = lc->yoff;
    for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
    {
      lcchild->xoff = lc->xoff;
      lcchild->yoff = yoff;
      if (lcchild->type != LAYOUT_WINDOWPANE)
      {
        layout_fix_offsets(lcchild);
      }
      yoff += lcchild->sy + 1;
    }

  }
}


----------------------------
u_int layout_count_cells(struct layout_cell *lc)
{
  struct layout_cell *lcchild;
  unsigned int lcchild_idx = 0;
  u_int count;
  switch (lc->type)
  {
    case LAYOUT_WINDOWPANE:
    {
      return 1;
    }

    case LAYOUT_LEFTRIGHT:

    case LAYOUT_TOPBOTTOM:
    {
      count = 0;
      for (lcchild_idx = (&lc->cells)->tqh_first; (&lcchild[lcchild_idx]) != 0; lcchild_idx = lcchild_idx->entry.tqe_next)
      {
        count += layout_count_cells(lcchild);
      }

      return count;
    }

    default:
    {
      fatalx("bad layout type");
    }

  }

}


----------------------------
None
----------------------------
***/


