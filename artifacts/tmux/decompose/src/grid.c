static void grid_free_line(struct grid *gd, u_int py)
{
  free(gd->linedata[py].celldata);
  gd->linedata[py].celldata = 0;
  free(gd->linedata[py].extddata);
  gd->linedata[py].extddata = 0;
}


/*** DEPENDENCIES:
None
----------------------------
***/


static void grid_free_lines(struct grid *gd, u_int py, u_int ny)
{
  u_int yy;
  for (yy = py; yy < (py + ny); yy += 1)
  {
    grid_free_line(gd, yy);
  }

}


/*** DEPENDENCIES:
static void grid_free_line(struct grid *gd, u_int py)
{
  free(gd->linedata[py].celldata);
  gd->linedata[py].celldata = 0;
  free(gd->linedata[py].extddata);
  gd->linedata[py].extddata = 0;
}


----------------------------
None
----------------------------
***/


void grid_destroy(struct grid *gd)
{
  grid_free_lines(gd, 0, gd->hsize + gd->sy);
  free(gd->linedata);
  free(gd);
}


/*** DEPENDENCIES:
static void grid_free_lines(struct grid *gd, u_int py, u_int ny)
{
  u_int yy;
  for (yy = py; yy < (py + ny); yy += 1)
  {
    grid_free_line(gd, yy);
  }

}


----------------------------
None
----------------------------
***/


// hint:  ['n_ref is a mutable refrence to size_t']
void helper_grid_string_cells_bg_1(size_t * const n_ref, const struct grid_cell * const gc, int * const values, u_char r, u_char g, u_char b)
{
  size_t n = *n_ref;
  values[n] = 48;
  n += 1;
  values[n] = 2;
  n += 1;
  colour_split_rgb(gc->bg, &r, &g, &b);
  values[n] = r;
  n += 1;
  values[n] = g;
  n += 1;
  values[n] = b;
  n += 1;
  *n_ref = n;
}


/*** DEPENDENCIES:
void colour_split_rgb(int c, u_char *r, u_char *g, u_char *b)
{
  *r = (c >> 16) & 0xff;
  *g = (c >> 8) & 0xff;
  *b = c & 0xff;
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
None
----------------------------
***/


static size_t grid_string_cells_bg(const struct grid_cell *gc, int *values)
{
  size_t n;
  u_char r;
  u_char g;
  u_char b;
  n = 0;
  if (gc->bg & 0x01000000)
  {
    values[n] = 48;
    n += 1;
    values[n] = 5;
    n += 1;
    values[n] = gc->bg & 0xff;
    n += 1;
  }
  else
    if (gc->bg & 0x02000000)
  {
    helper_grid_string_cells_bg_1(&n, gc, values, r, g, b);
  }
  else
  {
    switch (gc->bg)
    {
      case 0:

      case 1:

      case 2:

      case 3:

      case 4:

      case 5:

      case 6:

      case 7:
      {
        values[n] = gc->bg + 40;
        n += 1;
        break;
      }

      case 8:
      {
        values[n] = 49;
        n += 1;
        break;
      }

      case 100:

      case 101:

      case 102:

      case 103:

      case 104:

      case 105:

      case 106:

      case 107:
      {
        values[n] = gc->bg - 10;
        n += 1;
        break;
      }

    }

  }
  return n;
}


/*** DEPENDENCIES:
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
void helper_grid_string_cells_bg_1(size_t * const n_ref, const struct grid_cell * const gc, int * const values, u_char r, u_char g, u_char b)
{
  size_t n = *n_ref;
  values[n] = 48;
  n += 1;
  values[n] = 2;
  n += 1;
  colour_split_rgb(gc->bg, &r, &g, &b);
  values[n] = r;
  n += 1;
  values[n] = g;
  n += 1;
  values[n] = b;
  n += 1;
  *n_ref = n;
}


----------------------------
None
----------------------------
***/


// hint:  ['n_ref is a mutable refrence to size_t']
void helper_grid_string_cells_fg_1(size_t * const n_ref, const struct grid_cell * const gc, int * const values, u_char r, u_char g, u_char b)
{
  size_t n = *n_ref;
  values[n] = 38;
  n += 1;
  values[n] = 2;
  n += 1;
  colour_split_rgb(gc->fg, &r, &g, &b);
  values[n] = r;
  n += 1;
  values[n] = g;
  n += 1;
  values[n] = b;
  n += 1;
  *n_ref = n;
}


/*** DEPENDENCIES:
void colour_split_rgb(int c, u_char *r, u_char *g, u_char *b)
{
  *r = (c >> 16) & 0xff;
  *g = (c >> 8) & 0xff;
  *b = c & 0xff;
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
None
----------------------------
***/


static size_t grid_string_cells_fg(const struct grid_cell *gc, int *values)
{
  size_t n;
  u_char r;
  u_char g;
  u_char b;
  n = 0;
  if (gc->fg & 0x01000000)
  {
    values[n] = 38;
    n += 1;
    values[n] = 5;
    n += 1;
    values[n] = gc->fg & 0xff;
    n += 1;
  }
  else
    if (gc->fg & 0x02000000)
  {
    helper_grid_string_cells_fg_1(&n, gc, values, r, g, b);
  }
  else
  {
    switch (gc->fg)
    {
      case 0:

      case 1:

      case 2:

      case 3:

      case 4:

      case 5:

      case 6:

      case 7:
      {
        values[n] = gc->fg + 30;
        n += 1;
        break;
      }

      case 8:
      {
        values[n] = 39;
        n += 1;
        break;
      }

      case 90:

      case 91:

      case 92:

      case 93:

      case 94:

      case 95:

      case 96:

      case 97:
      {
        values[n] = gc->fg;
        n += 1;
        break;
      }

    }

  }
  return n;
}


/*** DEPENDENCIES:
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
void helper_grid_string_cells_fg_1(size_t * const n_ref, const struct grid_cell * const gc, int * const values, u_char r, u_char g, u_char b)
{
  size_t n = *n_ref;
  values[n] = 38;
  n += 1;
  values[n] = 2;
  n += 1;
  colour_split_rgb(gc->fg, &r, &g, &b);
  values[n] = r;
  n += 1;
  values[n] = g;
  n += 1;
  values[n] = b;
  n += 1;
  *n_ref = n;
}


----------------------------
None
----------------------------
***/


static void grid_string_cells_code(const struct grid_cell *lastgc, const struct grid_cell *gc, char *buf, size_t len, int escape_c0)
{
  int oldc[64];
  int newc[64];
  int s[128];
  size_t noldc;
  size_t nnewc;
  size_t n;
  size_t i;
  u_int attr = gc->attr;
  u_int lastattr = lastgc->attr;
  char tmp[64];
  struct 
  {
    u_int mask;
    u_int code;
  } attrs[] = {{0x1, 1}, {0x2, 2}, {0x40, 3}, {0x4, 4}, {0x8, 5}, {0x10, 7}, {0x20, 8}, {0x100, 9}};
  n = 0;
  for (i = 0; i < ((sizeof(attrs)) / (sizeof(attrs[0]))); i += 1)
  {
    if ((!(attr & attrs[i].mask)) && (lastattr & attrs[i].mask))
    {
      s[n] = 0;
      n += 1;
      lastattr &= 0x80;
      break;
    }
  }

  for (i = 0; i < ((sizeof(attrs)) / (sizeof(attrs[0]))); i += 1)
  {
    if ((attr & attrs[i].mask) && (!(lastattr & attrs[i].mask)))
    {
      s[n] = attrs[i].code;
      n += 1;
    }
  }

  *buf = '\0';
  if (n > 0)
  {
    if (escape_c0)
    {
      strlcat(buf, "\\033[", len);
    }
    else
      strlcat(buf, "\033[", len);
    for (i = 0; i < n; i += 1)
    {
      if ((i + 1) < n)
      {
        xsnprintf(tmp, sizeof(tmp), "%d;", s[i]);
      }
      else
        xsnprintf(tmp, sizeof(tmp), "%d", s[i]);
      strlcat(buf, tmp, len);
    }

    strlcat(buf, "m", len);
  }
  nnewc = grid_string_cells_fg(gc, newc);
  noldc = grid_string_cells_fg(lastgc, oldc);
  if (((nnewc != noldc) || (memcmp(newc, oldc, nnewc * (sizeof(newc[0]))) != 0)) || ((n != 0) && (s[0] == 0)))
  {
    if (escape_c0)
    {
      strlcat(buf, "\\033[", len);
    }
    else
      strlcat(buf, "\033[", len);
    for (i = 0; i < nnewc; i += 1)
    {
      if ((i + 1) < nnewc)
      {
        xsnprintf(tmp, sizeof(tmp), "%d;", newc[i]);
      }
      else
        xsnprintf(tmp, sizeof(tmp), "%d", newc[i]);
      strlcat(buf, tmp, len);
    }

    strlcat(buf, "m", len);
  }
  nnewc = grid_string_cells_bg(gc, newc);
  noldc = grid_string_cells_bg(lastgc, oldc);
  if (((nnewc != noldc) || (memcmp(newc, oldc, nnewc * (sizeof(newc[0]))) != 0)) || ((n != 0) && (s[0] == 0)))
  {
    if (escape_c0)
    {
      strlcat(buf, "\\033[", len);
    }
    else
      strlcat(buf, "\033[", len);
    for (i = 0; i < nnewc; i += 1)
    {
      if ((i + 1) < nnewc)
      {
        xsnprintf(tmp, sizeof(tmp), "%d;", newc[i]);
      }
      else
        xsnprintf(tmp, sizeof(tmp), "%d", newc[i]);
      strlcat(buf, tmp, len);
    }

    strlcat(buf, "m", len);
  }
  if ((attr & 0x80) && (!(lastattr & 0x80)))
  {
    if (escape_c0)
    {
      strlcat(buf, "\\016", len);
    }
    else
      strlcat(buf, "\016", len);
  }
  if ((!(attr & 0x80)) && (lastattr & 0x80))
  {
    if (escape_c0)
    {
      strlcat(buf, "\\017", len);
    }
    else
      strlcat(buf, "\017", len);
  }
}


/*** DEPENDENCIES:
static size_t grid_string_cells_bg(const struct grid_cell *gc, int *values)
{
  size_t n;
  u_char r;
  u_char g;
  u_char b;
  n = 0;
  if (gc->bg & 0x01000000)
  {
    values[n] = 48;
    n += 1;
    values[n] = 5;
    n += 1;
    values[n] = gc->bg & 0xff;
    n += 1;
  }
  else
    if (gc->bg & 0x02000000)
  {
    helper_grid_string_cells_bg_1(&n, gc, values, r, g, b);
  }
  else
  {
    switch (gc->bg)
    {
      case 0:

      case 1:

      case 2:

      case 3:

      case 4:

      case 5:

      case 6:

      case 7:
      {
        values[n] = gc->bg + 40;
        n += 1;
        break;
      }

      case 8:
      {
        values[n] = 49;
        n += 1;
        break;
      }

      case 100:

      case 101:

      case 102:

      case 103:

      case 104:

      case 105:

      case 106:

      case 107:
      {
        values[n] = gc->bg - 10;
        n += 1;
        break;
      }

    }

  }
  return n;
}


----------------------------
static size_t grid_string_cells_fg(const struct grid_cell *gc, int *values)
{
  size_t n;
  u_char r;
  u_char g;
  u_char b;
  n = 0;
  if (gc->fg & 0x01000000)
  {
    values[n] = 38;
    n += 1;
    values[n] = 5;
    n += 1;
    values[n] = gc->fg & 0xff;
    n += 1;
  }
  else
    if (gc->fg & 0x02000000)
  {
    helper_grid_string_cells_fg_1(&n, gc, values, r, g, b);
  }
  else
  {
    switch (gc->fg)
    {
      case 0:

      case 1:

      case 2:

      case 3:

      case 4:

      case 5:

      case 6:

      case 7:
      {
        values[n] = gc->fg + 30;
        n += 1;
        break;
      }

      case 8:
      {
        values[n] = 39;
        n += 1;
        break;
      }

      case 90:

      case 91:

      case 92:

      case 93:

      case 94:

      case 95:

      case 96:

      case 97:
      {
        values[n] = gc->fg;
        n += 1;
        break;
      }

    }

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


static int grid_check_y(struct grid *gd, const char *from, u_int py)
{
  if (py >= (gd->hsize + gd->sy))
  {
    log_debug("%s: y out of range: %u", from, py);
    return -1;
  }
  return 0;
}


/*** DEPENDENCIES:
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


static void grid_get_cell1(struct grid_line *gl, u_int px, struct grid_cell *gc)
{
  struct grid_cell_entry *gce = &gl->celldata[px];
  if (gce->flags & 0x8)
  {
    if (gce->offset >= gl->extdsize)
    {
      memcpy(gc, &grid_default_cell, sizeof(*gc));
    }
    else
      memcpy(gc, &gl->extddata[gce->offset], sizeof(*gc));
    return;
  }
  gc->flags = gce->flags & (~(0x1 | 0x2));
  gc->attr = gce->data.attr;
  gc->fg = gce->data.fg;
  if (gce->flags & 0x1)
  {
    gc->fg |= 0x01000000;
  }
  gc->bg = gce->data.bg;
  if (gce->flags & 0x2)
  {
    gc->bg |= 0x01000000;
  }
  utf8_set(&gc->data, gce->data.data);
}


/*** DEPENDENCIES:
void utf8_set(struct utf8_data *ud, u_char ch)
{
  static const struct utf8_data empty = {{0}, 1, 1, 1};
  memcpy(ud, &empty, sizeof(*ud));
  *ud->data = ch;
}


----------------------------
struct grid_cell_entry
{
  u_char flags;
  union 
  {
    u_int offset;
    struct 
    {
      u_char attr;
      u_char fg;
      u_char bg;
      u_char data;
    } data;
  };
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
extern const struct grid_cell grid_default_cell
----------------------------
None
----------------------------
***/


void grid_get_cell(struct grid *gd, u_int px, u_int py, struct grid_cell *gc)
{
  if ((grid_check_y(gd, __func__, py) != 0) || (px >= gd->linedata[py].cellsize))
  {
    memcpy(gc, &grid_default_cell, sizeof(*gc));
    return;
  }
  return grid_get_cell1(&gd->linedata[py], px, gc);
}


/*** DEPENDENCIES:
static int grid_check_y(struct grid *gd, const char *from, u_int py)
{
  if (py >= (gd->hsize + gd->sy))
  {
    log_debug("%s: y out of range: %u", from, py);
    return -1;
  }
  return 0;
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
static void grid_get_cell1(struct grid_line *gl, u_int px, struct grid_cell *gc)
{
  struct grid_cell_entry *gce = &gl->celldata[px];
  if (gce->flags & 0x8)
  {
    if (gce->offset >= gl->extdsize)
    {
      memcpy(gc, &grid_default_cell, sizeof(*gc));
    }
    else
      memcpy(gc, &gl->extddata[gce->offset], sizeof(*gc));
    return;
  }
  gc->flags = gce->flags & (~(0x1 | 0x2));
  gc->attr = gce->data.attr;
  gc->fg = gce->data.fg;
  if (gce->flags & 0x1)
  {
    gc->fg |= 0x01000000;
  }
  gc->bg = gce->data.bg;
  if (gce->flags & 0x2)
  {
    gc->bg |= 0x01000000;
  }
  utf8_set(&gc->data, gce->data.data);
}


----------------------------
extern const struct grid_cell grid_default_cell
----------------------------
None
----------------------------
***/


// hint:  ['data_idx_ref is a mutable refrence to unsigned int', 'buf_idx_ref is a mutable refrence to unsigned int', 'len_ref is a mutable refrence to size_t', 'off_ref is a mutable refrence to size_t', 'size_ref is a mutable refrence to size_t', 'codelen_ref is a mutable refrence to size_t']
void helper_grid_string_cells_1(unsigned int * const data_idx_ref, unsigned int * const buf_idx_ref, size_t * const len_ref, size_t * const off_ref, size_t * const size_ref, size_t * const codelen_ref, struct grid * const gd, u_int py, struct grid_cell ** const lastgc, int with_codes, int escape_c0, struct grid_cell gc, const char * const data, char * const buf, char code[128], u_int xx, const struct grid_line * const gl, unsigned int gl_idx)
{
  unsigned int data_idx = *data_idx_ref;
  unsigned int buf_idx = *buf_idx_ref;
  size_t len = *len_ref;
  size_t off = *off_ref;
  size_t size = *size_ref;
  size_t codelen = *codelen_ref;
  if (((&gl[gl_idx]) == 0) || (xx >= gl->cellsize))
  {
    break;
  }
  grid_get_cell(gd, xx, py, &gc);
  if (gc.flags & 0x4)
  {
    continue;
  }
  if (with_codes)
  {
    grid_string_cells_code(*lastgc, &gc, code, sizeof(code), escape_c0);
    codelen = strlen(code);
    memcpy(*lastgc, &gc, sizeof(*(*lastgc)));
  }
  else
    codelen = 0;
  data_idx = gc.data_idx.data_idx;
  size = gc.data.size;
  if ((escape_c0 && (size == 1)) && (data[data_idx] == '\\'))
  {
    data_idx = "\\\\";
    size = 2;
  }
  while (len < (((off + size) + codelen) + 1))
  {
    buf_idx = xreallocarray(buf_idx, 2, len);
    len *= 2;
  }

  if (codelen != 0)
  {
    memcpy((&buf[buf_idx]) + off, code, codelen);
    off += codelen;
  }
  memcpy((&buf[buf_idx]) + off, data, size);
  off += size;
  *data_idx_ref = data_idx;
  *buf_idx_ref = buf_idx;
  *len_ref = len;
  *off_ref = off;
  *size_ref = size;
  *codelen_ref = codelen;
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
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
static void grid_string_cells_code(const struct grid_cell *lastgc, const struct grid_cell *gc, char *buf, size_t len, int escape_c0)
{
  int oldc[64];
  int newc[64];
  int s[128];
  size_t noldc;
  size_t nnewc;
  size_t n;
  size_t i;
  u_int attr = gc->attr;
  u_int lastattr = lastgc->attr;
  char tmp[64];
  struct 
  {
    u_int mask;
    u_int code;
  } attrs[] = {{0x1, 1}, {0x2, 2}, {0x40, 3}, {0x4, 4}, {0x8, 5}, {0x10, 7}, {0x20, 8}, {0x100, 9}};
  n = 0;
  for (i = 0; i < ((sizeof(attrs)) / (sizeof(attrs[0]))); i += 1)
  {
    if ((!(attr & attrs[i].mask)) && (lastattr & attrs[i].mask))
    {
      s[n] = 0;
      n += 1;
      lastattr &= 0x80;
      break;
    }
  }

  for (i = 0; i < ((sizeof(attrs)) / (sizeof(attrs[0]))); i += 1)
  {
    if ((attr & attrs[i].mask) && (!(lastattr & attrs[i].mask)))
    {
      s[n] = attrs[i].code;
      n += 1;
    }
  }

  *buf = '\0';
  if (n > 0)
  {
    if (escape_c0)
    {
      strlcat(buf, "\\033[", len);
    }
    else
      strlcat(buf, "\033[", len);
    for (i = 0; i < n; i += 1)
    {
      if ((i + 1) < n)
      {
        xsnprintf(tmp, sizeof(tmp), "%d;", s[i]);
      }
      else
        xsnprintf(tmp, sizeof(tmp), "%d", s[i]);
      strlcat(buf, tmp, len);
    }

    strlcat(buf, "m", len);
  }
  nnewc = grid_string_cells_fg(gc, newc);
  noldc = grid_string_cells_fg(lastgc, oldc);
  if (((nnewc != noldc) || (memcmp(newc, oldc, nnewc * (sizeof(newc[0]))) != 0)) || ((n != 0) && (s[0] == 0)))
  {
    if (escape_c0)
    {
      strlcat(buf, "\\033[", len);
    }
    else
      strlcat(buf, "\033[", len);
    for (i = 0; i < nnewc; i += 1)
    {
      if ((i + 1) < nnewc)
      {
        xsnprintf(tmp, sizeof(tmp), "%d;", newc[i]);
      }
      else
        xsnprintf(tmp, sizeof(tmp), "%d", newc[i]);
      strlcat(buf, tmp, len);
    }

    strlcat(buf, "m", len);
  }
  nnewc = grid_string_cells_bg(gc, newc);
  noldc = grid_string_cells_bg(lastgc, oldc);
  if (((nnewc != noldc) || (memcmp(newc, oldc, nnewc * (sizeof(newc[0]))) != 0)) || ((n != 0) && (s[0] == 0)))
  {
    if (escape_c0)
    {
      strlcat(buf, "\\033[", len);
    }
    else
      strlcat(buf, "\033[", len);
    for (i = 0; i < nnewc; i += 1)
    {
      if ((i + 1) < nnewc)
      {
        xsnprintf(tmp, sizeof(tmp), "%d;", newc[i]);
      }
      else
        xsnprintf(tmp, sizeof(tmp), "%d", newc[i]);
      strlcat(buf, tmp, len);
    }

    strlcat(buf, "m", len);
  }
  if ((attr & 0x80) && (!(lastattr & 0x80)))
  {
    if (escape_c0)
    {
      strlcat(buf, "\\016", len);
    }
    else
      strlcat(buf, "\016", len);
  }
  if ((!(attr & 0x80)) && (lastattr & 0x80))
  {
    if (escape_c0)
    {
      strlcat(buf, "\\017", len);
    }
    else
      strlcat(buf, "\017", len);
  }
}


----------------------------
void grid_get_cell(struct grid *gd, u_int px, u_int py, struct grid_cell *gc)
{
  if ((grid_check_y(gd, __func__, py) != 0) || (px >= gd->linedata[py].cellsize))
  {
    memcpy(gc, &grid_default_cell, sizeof(*gc));
    return;
  }
  return grid_get_cell1(&gd->linedata[py], px, gc);
}


----------------------------
None
----------------------------
***/


const struct grid_line *grid_peek_line(struct grid *gd, u_int py)
{
  if (grid_check_y(gd, __func__, py) != 0)
  {
    return 0;
  }
  return &gd->linedata[py];
}


/*** DEPENDENCIES:
static int grid_check_y(struct grid *gd, const char *from, u_int py)
{
  if (py >= (gd->hsize + gd->sy))
  {
    log_debug("%s: y out of range: %u", from, py);
    return -1;
  }
  return 0;
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
void *xmalloc(size_t size)
{
  void *ptr;
  unsigned int ptr_idx = 0;
  if (size == 0)
  {
    fatalx("xmalloc: zero size");
  }
  ptr_idx = malloc(size);
  if ((&ptr[ptr_idx]) == 0)
  {
    fatalx("xmalloc: allocating %zu bytes: %s", size, strerror(errno));
  }
  return ptr;
}


----------------------------
extern const struct grid_cell grid_default_cell
----------------------------
void helper_grid_string_cells_1(unsigned int * const data_idx_ref, unsigned int * const buf_idx_ref, size_t * const len_ref, size_t * const off_ref, size_t * const size_ref, size_t * const codelen_ref, struct grid * const gd, u_int py, struct grid_cell ** const lastgc, int with_codes, int escape_c0, struct grid_cell gc, const char * const data, char * const buf, char code[128], u_int xx, const struct grid_line * const gl, unsigned int gl_idx)
{
  unsigned int data_idx = *data_idx_ref;
  unsigned int buf_idx = *buf_idx_ref;
  size_t len = *len_ref;
  size_t off = *off_ref;
  size_t size = *size_ref;
  size_t codelen = *codelen_ref;
  if (((&gl[gl_idx]) == 0) || (xx >= gl->cellsize))
  {
    break;
  }
  grid_get_cell(gd, xx, py, &gc);
  if (gc.flags & 0x4)
  {
    continue;
  }
  if (with_codes)
  {
    grid_string_cells_code(*lastgc, &gc, code, sizeof(code), escape_c0);
    codelen = strlen(code);
    memcpy(*lastgc, &gc, sizeof(*(*lastgc)));
  }
  else
    codelen = 0;
  data_idx = gc.data_idx.data_idx;
  size = gc.data.size;
  if ((escape_c0 && (size == 1)) && (data[data_idx] == '\\'))
  {
    data_idx = "\\\\";
    size = 2;
  }
  while (len < (((off + size) + codelen) + 1))
  {
    buf_idx = xreallocarray(buf_idx, 2, len);
    len *= 2;
  }

  if (codelen != 0)
  {
    memcpy((&buf[buf_idx]) + off, code, codelen);
    off += codelen;
  }
  memcpy((&buf[buf_idx]) + off, data, size);
  off += size;
  *data_idx_ref = data_idx;
  *buf_idx_ref = buf_idx;
  *len_ref = len;
  *off_ref = off;
  *size_ref = size;
  *codelen_ref = codelen;
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
const struct grid_line *grid_peek_line(struct grid *gd, u_int py)
{
  if (grid_check_y(gd, __func__, py) != 0)
  {
    return 0;
  }
  return &gd->linedata[py];
}


----------------------------
None
----------------------------
***/


static int grid_need_extended_cell(const struct grid_cell_entry *gce, const struct grid_cell *gc)
{
  if (gce->flags & 0x8)
  {
    return 1;
  }
  if (gc->attr > 0xff)
  {
    return 1;
  }
  if ((gc->data.size != 1) || (gc->data.width != 1))
  {
    return 1;
  }
  if ((gc->fg & 0x02000000) || (gc->bg & 0x02000000))
  {
    return 1;
  }
  return 0;
}


/*** DEPENDENCIES:
struct grid_cell_entry
{
  u_char flags;
  union 
  {
    u_int offset;
    struct 
    {
      u_char attr;
      u_char fg;
      u_char bg;
      u_char data;
    } data;
  };
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
None
----------------------------
***/


static struct grid_cell *grid_extended_cell(struct grid_line *gl, struct grid_cell_entry *gce, const struct grid_cell *gc)
{
  struct grid_cell *gcp;
  unsigned int gcp_idx = 0;
  gl->flags |= 0x2;
  if ((~gce->flags) & 0x8)
  {
    gl->extddata = xreallocarray(gl->extddata, gl->extdsize + 1, sizeof(*gl->extddata));
    gce->offset = gl->extdsize++;
    gce->flags = gc->flags | 0x8;
  }
  if (gce->offset >= gl->extdsize)
  {
    fatalx("offset too big");
  }
  gcp_idx = &gl->extddata[gce->offset];
  memcpy(gcp, gc, sizeof(*(&gcp[gcp_idx])));
  return gcp;
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
struct grid_cell_entry
{
  u_char flags;
  union 
  {
    u_int offset;
    struct 
    {
      u_char attr;
      u_char fg;
      u_char bg;
      u_char data;
    } data;
  };
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
void fatalx(const char *msg, ...)
{
  char *fmt;
  va_list ap;
  __builtin_va_start(ap);
  if (asprintf(&fmt, "fatal: %s", msg) == (-1))
  {
    exit(1);
  }
  log_vwrite(fmt, ap);
  ;
  exit(1);
}


----------------------------
None
----------------------------
***/


static void grid_store_cell(struct grid_cell_entry *gce, const struct grid_cell *gc, u_char c)
{
  gce->flags = gc->flags;
  gce->data.fg = gc->fg & 0xff;
  if (gc->fg & 0x01000000)
  {
    gce->flags |= 0x1;
  }
  gce->data.bg = gc->bg & 0xff;
  if (gc->bg & 0x01000000)
  {
    gce->flags |= 0x2;
  }
  gce->data.attr = gc->attr;
  gce->data.data = c;
}


/*** DEPENDENCIES:
struct grid_cell_entry
{
  u_char flags;
  union 
  {
    u_int offset;
    struct 
    {
      u_char attr;
      u_char fg;
      u_char bg;
      u_char data;
    } data;
  };
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
None
----------------------------
***/


static void grid_clear_cell(struct grid *gd, u_int px, u_int py, u_int bg)
{
  struct grid_line *gl = &gd->linedata[py];
  struct grid_cell_entry *gce = &gl->celldata[px];
  struct grid_cell *gc;
  unsigned int gc_idx = 0;
  memcpy(gce, &grid_default_entry, sizeof(*gce));
  if (bg & 0x02000000)
  {
    gc_idx = grid_extended_cell(gl, gce, &grid_default_cell);
    gc->bg = bg;
  }
  else
  {
    if (bg & 0x01000000)
    {
      gce->flags |= 0x2;
    }
    gce->data.bg = bg;
  }
}


/*** DEPENDENCIES:
struct grid_cell_entry
{
  u_char flags;
  union 
  {
    u_int offset;
    struct 
    {
      u_char attr;
      u_char fg;
      u_char bg;
      u_char data;
    } data;
  };
}
----------------------------
extern const struct grid_cell grid_default_cell
----------------------------
static const struct grid_cell_entry grid_default_entry = {0, {.data = {0, 8, 8, ' '}}}
----------------------------
static struct grid_cell *grid_extended_cell(struct grid_line *gl, struct grid_cell_entry *gce, const struct grid_cell *gc)
{
  struct grid_cell *gcp;
  unsigned int gcp_idx = 0;
  gl->flags |= 0x2;
  if ((~gce->flags) & 0x8)
  {
    gl->extddata = xreallocarray(gl->extddata, gl->extdsize + 1, sizeof(*gl->extddata));
    gce->offset = gl->extdsize++;
    gce->flags = gc->flags | 0x8;
  }
  if (gce->offset >= gl->extdsize)
  {
    fatalx("offset too big");
  }
  gcp_idx = &gl->extddata[gce->offset];
  memcpy(gcp, gc, sizeof(*(&gcp[gcp_idx])));
  return gcp;
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
None
----------------------------
***/


static void grid_expand_line(struct grid *gd, u_int py, u_int sx, u_int bg)
{
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  u_int xx;
  gl_idx = &gd->linedata[py];
  if (sx <= gl->cellsize)
  {
    return;
  }
  if (sx < (gd->sx / 4))
  {
    sx = gd->sx / 4;
  }
  else
    if (sx < (gd->sx / 2))
  {
    sx = gd->sx / 2;
  }
  else
    sx = gd->sx;
  gl->celldata = xreallocarray(gl->celldata, sx, sizeof(*gl->celldata));
  for (xx = gl->cellsize; xx < sx; xx += 1)
  {
    grid_clear_cell(gd, xx, py, bg);
  }

  gl->cellsize = sx;
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
static void grid_clear_cell(struct grid *gd, u_int px, u_int py, u_int bg)
{
  struct grid_line *gl = &gd->linedata[py];
  struct grid_cell_entry *gce = &gl->celldata[px];
  struct grid_cell *gc;
  unsigned int gc_idx = 0;
  memcpy(gce, &grid_default_entry, sizeof(*gce));
  if (bg & 0x02000000)
  {
    gc_idx = grid_extended_cell(gl, gce, &grid_default_cell);
    gc->bg = bg;
  }
  else
  {
    if (bg & 0x01000000)
    {
      gce->flags |= 0x2;
    }
    gce->data.bg = bg;
  }
}


----------------------------
None
----------------------------
***/


void grid_set_cells(struct grid *gd, u_int px, u_int py, const struct grid_cell *gc, const char *s, size_t slen)
{
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  struct grid_cell_entry *gce;
  unsigned int gce_idx = 0;
  struct grid_cell *gcp;
  unsigned int gcp_idx = 0;
  u_int i;
  if (grid_check_y(gd, __func__, py) != 0)
  {
    return;
  }
  grid_expand_line(gd, py, px + slen, 8);
  gl_idx = &gd->linedata[py];
  if ((px + slen) > gl->cellused)
  {
    gl->cellused = px + slen;
  }
  for (i = 0; i < slen; i += 1)
  {
    gce_idx = &gl->celldata[px + i];
    if (grid_need_extended_cell(gce, gc))
    {
      gcp_idx = grid_extended_cell(gl, gce, gc);
      utf8_set(&gcp->data, s[i]);
    }
    else
      grid_store_cell(gce, gc, s[i]);
  }

}


/*** DEPENDENCIES:
void utf8_set(struct utf8_data *ud, u_char ch)
{
  static const struct utf8_data empty = {{0}, 1, 1, 1};
  memcpy(ud, &empty, sizeof(*ud));
  *ud->data = ch;
}


----------------------------
static int grid_check_y(struct grid *gd, const char *from, u_int py)
{
  if (py >= (gd->hsize + gd->sy))
  {
    log_debug("%s: y out of range: %u", from, py);
    return -1;
  }
  return 0;
}


----------------------------
struct grid_cell_entry
{
  u_char flags;
  union 
  {
    u_int offset;
    struct 
    {
      u_char attr;
      u_char fg;
      u_char bg;
      u_char data;
    } data;
  };
}
----------------------------
static int grid_need_extended_cell(const struct grid_cell_entry *gce, const struct grid_cell *gc)
{
  if (gce->flags & 0x8)
  {
    return 1;
  }
  if (gc->attr > 0xff)
  {
    return 1;
  }
  if ((gc->data.size != 1) || (gc->data.width != 1))
  {
    return 1;
  }
  if ((gc->fg & 0x02000000) || (gc->bg & 0x02000000))
  {
    return 1;
  }
  return 0;
}


----------------------------
static struct grid_cell *grid_extended_cell(struct grid_line *gl, struct grid_cell_entry *gce, const struct grid_cell *gc)
{
  struct grid_cell *gcp;
  unsigned int gcp_idx = 0;
  gl->flags |= 0x2;
  if ((~gce->flags) & 0x8)
  {
    gl->extddata = xreallocarray(gl->extddata, gl->extdsize + 1, sizeof(*gl->extddata));
    gce->offset = gl->extdsize++;
    gce->flags = gc->flags | 0x8;
  }
  if (gce->offset >= gl->extdsize)
  {
    fatalx("offset too big");
  }
  gcp_idx = &gl->extddata[gce->offset];
  memcpy(gcp, gc, sizeof(*(&gcp[gcp_idx])));
  return gcp;
}


----------------------------
static void grid_store_cell(struct grid_cell_entry *gce, const struct grid_cell *gc, u_char c)
{
  gce->flags = gc->flags;
  gce->data.fg = gc->fg & 0xff;
  if (gc->fg & 0x01000000)
  {
    gce->flags |= 0x1;
  }
  gce->data.bg = gc->bg & 0xff;
  if (gc->bg & 0x01000000)
  {
    gce->flags |= 0x2;
  }
  gce->data.attr = gc->attr;
  gce->data.data = c;
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
static void grid_expand_line(struct grid *gd, u_int py, u_int sx, u_int bg)
{
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  u_int xx;
  gl_idx = &gd->linedata[py];
  if (sx <= gl->cellsize)
  {
    return;
  }
  if (sx < (gd->sx / 4))
  {
    sx = gd->sx / 4;
  }
  else
    if (sx < (gd->sx / 2))
  {
    sx = gd->sx / 2;
  }
  else
    sx = gd->sx;
  gl->celldata = xreallocarray(gl->celldata, sx, sizeof(*gl->celldata));
  for (xx = gl->cellsize; xx < sx; xx += 1)
  {
    grid_clear_cell(gd, xx, py, bg);
  }

  gl->cellsize = sx;
}


----------------------------
None
----------------------------
***/


void grid_set_cell(struct grid *gd, u_int px, u_int py, const struct grid_cell *gc)
{
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  struct grid_cell_entry *gce;
  unsigned int gce_idx = 0;
  if (grid_check_y(gd, __func__, py) != 0)
  {
    return;
  }
  grid_expand_line(gd, py, px + 1, 8);
  gl_idx = &gd->linedata[py];
  if ((px + 1) > gl->cellused)
  {
    gl->cellused = px + 1;
  }
  gce_idx = &gl->celldata[px];
  if (grid_need_extended_cell(gce, gc))
  {
    grid_extended_cell(gl, gce, gc);
  }
  else
    grid_store_cell(gce, gc, gc->data.data[0]);
}


/*** DEPENDENCIES:
static int grid_check_y(struct grid *gd, const char *from, u_int py)
{
  if (py >= (gd->hsize + gd->sy))
  {
    log_debug("%s: y out of range: %u", from, py);
    return -1;
  }
  return 0;
}


----------------------------
struct grid_cell_entry
{
  u_char flags;
  union 
  {
    u_int offset;
    struct 
    {
      u_char attr;
      u_char fg;
      u_char bg;
      u_char data;
    } data;
  };
}
----------------------------
static int grid_need_extended_cell(const struct grid_cell_entry *gce, const struct grid_cell *gc)
{
  if (gce->flags & 0x8)
  {
    return 1;
  }
  if (gc->attr > 0xff)
  {
    return 1;
  }
  if ((gc->data.size != 1) || (gc->data.width != 1))
  {
    return 1;
  }
  if ((gc->fg & 0x02000000) || (gc->bg & 0x02000000))
  {
    return 1;
  }
  return 0;
}


----------------------------
static struct grid_cell *grid_extended_cell(struct grid_line *gl, struct grid_cell_entry *gce, const struct grid_cell *gc)
{
  struct grid_cell *gcp;
  unsigned int gcp_idx = 0;
  gl->flags |= 0x2;
  if ((~gce->flags) & 0x8)
  {
    gl->extddata = xreallocarray(gl->extddata, gl->extdsize + 1, sizeof(*gl->extddata));
    gce->offset = gl->extdsize++;
    gce->flags = gc->flags | 0x8;
  }
  if (gce->offset >= gl->extdsize)
  {
    fatalx("offset too big");
  }
  gcp_idx = &gl->extddata[gce->offset];
  memcpy(gcp, gc, sizeof(*(&gcp[gcp_idx])));
  return gcp;
}


----------------------------
static void grid_store_cell(struct grid_cell_entry *gce, const struct grid_cell *gc, u_char c)
{
  gce->flags = gc->flags;
  gce->data.fg = gc->fg & 0xff;
  if (gc->fg & 0x01000000)
  {
    gce->flags |= 0x1;
  }
  gce->data.bg = gc->bg & 0xff;
  if (gc->bg & 0x01000000)
  {
    gce->flags |= 0x2;
  }
  gce->data.attr = gc->attr;
  gce->data.data = c;
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
static void grid_expand_line(struct grid *gd, u_int py, u_int sx, u_int bg)
{
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  u_int xx;
  gl_idx = &gd->linedata[py];
  if (sx <= gl->cellsize)
  {
    return;
  }
  if (sx < (gd->sx / 4))
  {
    sx = gd->sx / 4;
  }
  else
    if (sx < (gd->sx / 2))
  {
    sx = gd->sx / 2;
  }
  else
    sx = gd->sx;
  gl->celldata = xreallocarray(gl->celldata, sx, sizeof(*gl->celldata));
  for (xx = gl->cellsize; xx < sx; xx += 1)
  {
    grid_clear_cell(gd, xx, py, bg);
  }

  gl->cellsize = sx;
}


----------------------------
None
----------------------------
***/


int grid_cells_equal(const struct grid_cell *gca, const struct grid_cell *gcb)
{
  if ((gca->fg != gcb->fg) || (gca->bg != gcb->bg))
  {
    return 0;
  }
  if ((gca->attr != gcb->attr) || (gca->flags != gcb->flags))
  {
    return 0;
  }
  if (gca->data.width != gcb->data.width)
  {
    return 0;
  }
  if (gca->data.size != gcb->data.size)
  {
    return 0;
  }
  return memcmp(gca->data.data, gcb->data.data, gca->data.size) == 0;
}


/*** DEPENDENCIES:
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
None
----------------------------
***/


struct grid *grid_create(u_int sx, u_int sy, u_int hlimit)
{
  struct grid *gd;
  unsigned int gd_idx = 0;
  gd_idx = xmalloc(sizeof(*gd_idx));
  gd->sx = sx;
  gd->sy = sy;
  gd->flags = 0x1;
  gd->hscrolled = 0;
  gd->hsize = 0;
  gd->hlimit = hlimit;
  if (gd->sy != 0)
  {
    gd->linedata = xcalloc(gd->sy, sizeof(*gd->linedata));
  }
  else
    gd->linedata = 0;
  return gd;
}


/*** DEPENDENCIES:
void *xmalloc(size_t size)
{
  void *ptr;
  unsigned int ptr_idx = 0;
  if (size == 0)
  {
    fatalx("xmalloc: zero size");
  }
  ptr_idx = malloc(size);
  if ((&ptr[ptr_idx]) == 0)
  {
    fatalx("xmalloc: allocating %zu bytes: %s", size, strerror(errno));
  }
  return ptr;
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


static struct grid_line *grid_reflow_add(struct grid *gd, u_int n)
{
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  u_int sy = gd->sy + n;
  gd->linedata = xreallocarray(gd->linedata, sy, sizeof(*gd->linedata));
  gl_idx = &gd->linedata[gd->sy];
  memset(gl, 0, n * (sizeof(*(&gl[gl_idx]))));
  gd->sy = sy;
  return gl;
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
None
----------------------------
***/


static void grid_reflow_dead(struct grid_line *gl)
{
  memset(gl, 0, sizeof(*gl));
  gl->flags = 0x4;
}


/*** DEPENDENCIES:
None
----------------------------
***/


static struct grid_line *grid_reflow_move(struct grid *gd, struct grid_line *from)
{
  struct grid_line *to;
  unsigned int to_idx = 0;
  to_idx = grid_reflow_add(gd, 1);
  memcpy(to, from, sizeof(*(&to[to_idx])));
  grid_reflow_dead(from);
  return to;
}


/*** DEPENDENCIES:
static void grid_reflow_dead(struct grid_line *gl)
{
  memset(gl, 0, sizeof(*gl));
  gl->flags = 0x4;
}


----------------------------
static struct grid_line *grid_reflow_add(struct grid *gd, u_int n)
{
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  u_int sy = gd->sy + n;
  gd->linedata = xreallocarray(gd->linedata, sy, sizeof(*gd->linedata));
  gl_idx = &gd->linedata[gd->sy];
  memset(gl, 0, n * (sizeof(*(&gl[gl_idx]))));
  gd->sy = sy;
  return gl;
}


----------------------------
None
----------------------------
***/


void grid_move_cells(struct grid *gd, u_int dx, u_int px, u_int py, u_int nx, u_int bg)
{
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  u_int xx;
  if ((nx == 0) || (px == dx))
  {
    return;
  }
  if (grid_check_y(gd, __func__, py) != 0)
  {
    return;
  }
  gl_idx = &gd->linedata[py];
  grid_expand_line(gd, py, px + nx, 8);
  grid_expand_line(gd, py, dx + nx, 8);
  memmove(&gl->celldata[dx], &gl->celldata[px], nx * (sizeof(*gl->celldata)));
  if ((dx + nx) > gl->cellused)
  {
    gl->cellused = dx + nx;
  }
  for (xx = px; xx < (px + nx); xx += 1)
  {
    if ((xx >= dx) && (xx < (dx + nx)))
    {
      continue;
    }
    grid_clear_cell(gd, xx, py, bg);
  }

}


/*** DEPENDENCIES:
static void grid_expand_line(struct grid *gd, u_int py, u_int sx, u_int bg)
{
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  u_int xx;
  gl_idx = &gd->linedata[py];
  if (sx <= gl->cellsize)
  {
    return;
  }
  if (sx < (gd->sx / 4))
  {
    sx = gd->sx / 4;
  }
  else
    if (sx < (gd->sx / 2))
  {
    sx = gd->sx / 2;
  }
  else
    sx = gd->sx;
  gl->celldata = xreallocarray(gl->celldata, sx, sizeof(*gl->celldata));
  for (xx = gl->cellsize; xx < sx; xx += 1)
  {
    grid_clear_cell(gd, xx, py, bg);
  }

  gl->cellsize = sx;
}


----------------------------
static int grid_check_y(struct grid *gd, const char *from, u_int py)
{
  if (py >= (gd->hsize + gd->sy))
  {
    log_debug("%s: y out of range: %u", from, py);
    return -1;
  }
  return 0;
}


----------------------------
static void grid_clear_cell(struct grid *gd, u_int px, u_int py, u_int bg)
{
  struct grid_line *gl = &gd->linedata[py];
  struct grid_cell_entry *gce = &gl->celldata[px];
  struct grid_cell *gc;
  unsigned int gc_idx = 0;
  memcpy(gce, &grid_default_entry, sizeof(*gce));
  if (bg & 0x02000000)
  {
    gc_idx = grid_extended_cell(gl, gce, &grid_default_cell);
    gc->bg = bg;
  }
  else
  {
    if (bg & 0x01000000)
    {
      gce->flags |= 0x2;
    }
    gce->data.bg = bg;
  }
}


----------------------------
None
----------------------------
***/


// hint:  ['width_ref is a mutable refrence to u_int', 'from_idx_ref is a mutable refrence to unsigned int', 'lines_ref is a mutable refrence to u_int', 'want_ref is a mutable refrence to u_int', 'line_ref is a mutable refrence to u_int', 'at_ref is a mutable refrence to u_int', 'wrapped_ref is a mutable refrence to int']
void helper_grid_reflow_join_1(u_int * const width_ref, unsigned int * const from_idx_ref, u_int * const lines_ref, u_int * const want_ref, u_int * const line_ref, u_int * const at_ref, int * const wrapped_ref, struct grid * const target, struct grid * const gd, u_int sx, u_int yy, struct grid_line * const from, struct grid_cell gc, u_int to)
{
  u_int width = *width_ref;
  unsigned int from_idx = *from_idx_ref;
  u_int lines = *lines_ref;
  u_int want = *want_ref;
  u_int line = *line_ref;
  u_int at = *at_ref;
  int wrapped = *wrapped_ref;
  if ((yy + lines) == (gd->hsize + gd->sy))
  {
    break;
  }
  line = (yy + 1) + lines;
  if ((~gd->linedata[line].flags) & 0x1)
  {
    wrapped = 0;
  }
  if (gd->linedata[line].cellused == 0)
  {
    if (!wrapped)
    {
      break;
    }
    continue;
  }
  grid_get_cell1(&gd->linedata[line], 0, &gc);
  if ((width + gc.data.width) > sx)
  {
    break;
  }
  width += gc.data.width;
  grid_set_cell(target, at, to, &gc);
  at += 1;
  from_idx = &gd->linedata[line];
  for (want = 1; want < from->cellused; want += 1)
  {
    grid_get_cell1(from, want, &gc);
    if ((width + gc.data.width) > sx)
    {
      break;
    }
    width += gc.data.width;
    grid_set_cell(target, at, to, &gc);
    at += 1;
  }

  lines += 1;
  if (((!wrapped) || (want != from->cellused)) || (width == sx))
  {
    break;
  }
  *width_ref = width;
  *from_idx_ref = from_idx;
  *lines_ref = lines;
  *want_ref = want;
  *line_ref = line;
  *at_ref = at;
  *wrapped_ref = wrapped;
}


/*** DEPENDENCIES:
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
void grid_set_cell(struct grid *gd, u_int px, u_int py, const struct grid_cell *gc)
{
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  struct grid_cell_entry *gce;
  unsigned int gce_idx = 0;
  if (grid_check_y(gd, __func__, py) != 0)
  {
    return;
  }
  grid_expand_line(gd, py, px + 1, 8);
  gl_idx = &gd->linedata[py];
  if ((px + 1) > gl->cellused)
  {
    gl->cellused = px + 1;
  }
  gce_idx = &gl->celldata[px];
  if (grid_need_extended_cell(gce, gc))
  {
    grid_extended_cell(gl, gce, gc);
  }
  else
    grid_store_cell(gce, gc, gc->data.data[0]);
}


----------------------------
static void grid_get_cell1(struct grid_line *gl, u_int px, struct grid_cell *gc)
{
  struct grid_cell_entry *gce = &gl->celldata[px];
  if (gce->flags & 0x8)
  {
    if (gce->offset >= gl->extdsize)
    {
      memcpy(gc, &grid_default_cell, sizeof(*gc));
    }
    else
      memcpy(gc, &gl->extddata[gce->offset], sizeof(*gc));
    return;
  }
  gc->flags = gce->flags & (~(0x1 | 0x2));
  gc->attr = gce->data.attr;
  gc->fg = gce->data.fg;
  if (gce->flags & 0x1)
  {
    gc->fg |= 0x01000000;
  }
  gc->bg = gce->data.bg;
  if (gce->flags & 0x2)
  {
    gc->bg |= 0x01000000;
  }
  utf8_set(&gc->data, gce->data.data);
}


----------------------------
None
----------------------------
***/


static void grid_reflow_join(struct grid *target, struct grid *gd, u_int sx, u_int yy, u_int width, u_int *cy, int already)
{
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  struct grid_line *from;
  unsigned int from_idx = 0;
  struct grid_cell gc;
  u_int lines;
  u_int want;
  u_int left;
  u_int i;
  u_int to;
  u_int line;
  u_int at;
  int wrapped = 1;
  if (!already)
  {
    to = target->sy;
    gl_idx = grid_reflow_move(target, &gd->linedata[yy]);
  }
  else
  {
    to = target->sy - 1;
    gl_idx = &target->linedata[to];
  }
  at = gl->cellused;
  lines = 0;
  for (;;)
  {
    helper_grid_reflow_join_1(&width, &from_idx, &lines, &want, &line, &at, &wrapped, target, gd, sx, yy, from, gc, to);
  }

  if (lines == 0)
  {
    return;
  }
  left = from->cellused - want;
  if (left != 0)
  {
    grid_move_cells(gd, 0, want, yy + lines, left, 8);
    from->cellsize = (from->cellused = left);
    lines -= 1;
  }
  else
    if (!wrapped)
  {
    gl->flags &= ~0x1;
  }
  for (i = yy + 1; i < ((yy + 1) + lines); i += 1)
  {
    free(gd->linedata[i].celldata);
    free(gd->linedata[i].extddata);
    grid_reflow_dead(&gd->linedata[i]);
  }

  if ((*cy) > (to + lines))
  {
    *cy -= lines;
  }
  else
    if ((*cy) > to)
  {
    *cy = to;
  }
  if (gd->hscrolled > (to + lines))
  {
    gd->hscrolled -= lines;
  }
  else
    if (gd->hscrolled > to)
  {
    gd->hscrolled = to;
  }
}


/*** DEPENDENCIES:
static struct grid_line *grid_reflow_move(struct grid *gd, struct grid_line *from)
{
  struct grid_line *to;
  unsigned int to_idx = 0;
  to_idx = grid_reflow_add(gd, 1);
  memcpy(to, from, sizeof(*(&to[to_idx])));
  grid_reflow_dead(from);
  return to;
}


----------------------------
void grid_move_cells(struct grid *gd, u_int dx, u_int px, u_int py, u_int nx, u_int bg)
{
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  u_int xx;
  if ((nx == 0) || (px == dx))
  {
    return;
  }
  if (grid_check_y(gd, __func__, py) != 0)
  {
    return;
  }
  gl_idx = &gd->linedata[py];
  grid_expand_line(gd, py, px + nx, 8);
  grid_expand_line(gd, py, dx + nx, 8);
  memmove(&gl->celldata[dx], &gl->celldata[px], nx * (sizeof(*gl->celldata)));
  if ((dx + nx) > gl->cellused)
  {
    gl->cellused = dx + nx;
  }
  for (xx = px; xx < (px + nx); xx += 1)
  {
    if ((xx >= dx) && (xx < (dx + nx)))
    {
      continue;
    }
    grid_clear_cell(gd, xx, py, bg);
  }

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
static void grid_reflow_dead(struct grid_line *gl)
{
  memset(gl, 0, sizeof(*gl));
  gl->flags = 0x4;
}


----------------------------
void helper_grid_reflow_join_1(u_int * const width_ref, unsigned int * const from_idx_ref, u_int * const lines_ref, u_int * const want_ref, u_int * const line_ref, u_int * const at_ref, int * const wrapped_ref, struct grid * const target, struct grid * const gd, u_int sx, u_int yy, struct grid_line * const from, struct grid_cell gc, u_int to)
{
  u_int width = *width_ref;
  unsigned int from_idx = *from_idx_ref;
  u_int lines = *lines_ref;
  u_int want = *want_ref;
  u_int line = *line_ref;
  u_int at = *at_ref;
  int wrapped = *wrapped_ref;
  if ((yy + lines) == (gd->hsize + gd->sy))
  {
    break;
  }
  line = (yy + 1) + lines;
  if ((~gd->linedata[line].flags) & 0x1)
  {
    wrapped = 0;
  }
  if (gd->linedata[line].cellused == 0)
  {
    if (!wrapped)
    {
      break;
    }
    continue;
  }
  grid_get_cell1(&gd->linedata[line], 0, &gc);
  if ((width + gc.data.width) > sx)
  {
    break;
  }
  width += gc.data.width;
  grid_set_cell(target, at, to, &gc);
  at += 1;
  from_idx = &gd->linedata[line];
  for (want = 1; want < from->cellused; want += 1)
  {
    grid_get_cell1(from, want, &gc);
    if ((width + gc.data.width) > sx)
    {
      break;
    }
    width += gc.data.width;
    grid_set_cell(target, at, to, &gc);
    at += 1;
  }

  lines += 1;
  if (((!wrapped) || (want != from->cellused)) || (width == sx))
  {
    break;
  }
  *width_ref = width;
  *from_idx_ref = from_idx;
  *lines_ref = lines;
  *want_ref = want;
  *line_ref = line;
  *at_ref = at;
  *wrapped_ref = wrapped;
}


----------------------------
None
----------------------------
***/


static void grid_reflow_split(struct grid *target, struct grid *gd, u_int sx, u_int yy, u_int at, u_int *cy)
{
  struct grid_line *gl = &gd->linedata[yy];
  struct grid_line *first;
  unsigned int first_idx = 0;
  struct grid_cell gc;
  u_int line;
  u_int lines;
  u_int width;
  u_int i;
  u_int xx;
  u_int used = gl->cellused;
  int flags = gl->flags;
  if ((~gl->flags) & 0x2)
  {
    lines = 1 + ((gl->cellused - 1) / sx);
  }
  else
  {
    lines = 2;
    width = 0;
    for (i = at; i < used; i += 1)
    {
      grid_get_cell1(gl, i, &gc);
      if ((width + gc.data.width) > sx)
      {
        lines += 1;
        width = 0;
      }
      width += gc.data.width;
    }

  }
  line = target->sy + 1;
  first_idx = grid_reflow_add(target, lines);
  width = 0;
  xx = 0;
  for (i = at; i < used; i += 1)
  {
    grid_get_cell1(gl, i, &gc);
    if ((width + gc.data.width) > sx)
    {
      target->linedata[line].flags |= 0x1;
      line += 1;
      width = 0;
      xx = 0;
    }
    width += gc.data.width;
    grid_set_cell(target, xx, line, &gc);
    xx += 1;
  }

  if (flags & 0x1)
  {
    target->linedata[line].flags |= 0x1;
  }
  gl->cellsize = (gl->cellused = at);
  gl->flags |= 0x1;
  memcpy(first, gl, sizeof(*(&first[first_idx])));
  grid_reflow_dead(gl);
  if (yy <= (*cy))
  {
    *cy += lines - 1;
  }
  if (yy <= gd->hscrolled)
  {
    gd->hscrolled += lines - 1;
  }
  if ((width < sx) && (flags & 0x1))
  {
    grid_reflow_join(target, gd, sx, yy, width, cy, 1);
  }
}


/*** DEPENDENCIES:
static void grid_get_cell1(struct grid_line *gl, u_int px, struct grid_cell *gc)
{
  struct grid_cell_entry *gce = &gl->celldata[px];
  if (gce->flags & 0x8)
  {
    if (gce->offset >= gl->extdsize)
    {
      memcpy(gc, &grid_default_cell, sizeof(*gc));
    }
    else
      memcpy(gc, &gl->extddata[gce->offset], sizeof(*gc));
    return;
  }
  gc->flags = gce->flags & (~(0x1 | 0x2));
  gc->attr = gce->data.attr;
  gc->fg = gce->data.fg;
  if (gce->flags & 0x1)
  {
    gc->fg |= 0x01000000;
  }
  gc->bg = gce->data.bg;
  if (gce->flags & 0x2)
  {
    gc->bg |= 0x01000000;
  }
  utf8_set(&gc->data, gce->data.data);
}


----------------------------
static void grid_reflow_join(struct grid *target, struct grid *gd, u_int sx, u_int yy, u_int width, u_int *cy, int already)
{
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  struct grid_line *from;
  unsigned int from_idx = 0;
  struct grid_cell gc;
  u_int lines;
  u_int want;
  u_int left;
  u_int i;
  u_int to;
  u_int line;
  u_int at;
  int wrapped = 1;
  if (!already)
  {
    to = target->sy;
    gl_idx = grid_reflow_move(target, &gd->linedata[yy]);
  }
  else
  {
    to = target->sy - 1;
    gl_idx = &target->linedata[to];
  }
  at = gl->cellused;
  lines = 0;
  for (;;)
  {
    helper_grid_reflow_join_1(&width, &from_idx, &lines, &want, &line, &at, &wrapped, target, gd, sx, yy, from, gc, to);
  }

  if (lines == 0)
  {
    return;
  }
  left = from->cellused - want;
  if (left != 0)
  {
    grid_move_cells(gd, 0, want, yy + lines, left, 8);
    from->cellsize = (from->cellused = left);
    lines -= 1;
  }
  else
    if (!wrapped)
  {
    gl->flags &= ~0x1;
  }
  for (i = yy + 1; i < ((yy + 1) + lines); i += 1)
  {
    free(gd->linedata[i].celldata);
    free(gd->linedata[i].extddata);
    grid_reflow_dead(&gd->linedata[i]);
  }

  if ((*cy) > (to + lines))
  {
    *cy -= lines;
  }
  else
    if ((*cy) > to)
  {
    *cy = to;
  }
  if (gd->hscrolled > (to + lines))
  {
    gd->hscrolled -= lines;
  }
  else
    if (gd->hscrolled > to)
  {
    gd->hscrolled = to;
  }
}


----------------------------
static struct grid_line *grid_reflow_add(struct grid *gd, u_int n)
{
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  u_int sy = gd->sy + n;
  gd->linedata = xreallocarray(gd->linedata, sy, sizeof(*gd->linedata));
  gl_idx = &gd->linedata[gd->sy];
  memset(gl, 0, n * (sizeof(*(&gl[gl_idx]))));
  gd->sy = sy;
  return gl;
}


----------------------------
void grid_set_cell(struct grid *gd, u_int px, u_int py, const struct grid_cell *gc)
{
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  struct grid_cell_entry *gce;
  unsigned int gce_idx = 0;
  if (grid_check_y(gd, __func__, py) != 0)
  {
    return;
  }
  grid_expand_line(gd, py, px + 1, 8);
  gl_idx = &gd->linedata[py];
  if ((px + 1) > gl->cellused)
  {
    gl->cellused = px + 1;
  }
  gce_idx = &gl->celldata[px];
  if (grid_need_extended_cell(gce, gc))
  {
    grid_extended_cell(gl, gce, gc);
  }
  else
    grid_store_cell(gce, gc, gc->data.data[0]);
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
static void grid_reflow_dead(struct grid_line *gl)
{
  memset(gl, 0, sizeof(*gl));
  gl->flags = 0x4;
}


----------------------------
None
----------------------------
***/


// hint:  ['gl_idx_ref is a mutable refrence to unsigned int', 'width_ref is a mutable refrence to u_int', 'i_ref is a mutable refrence to u_int', 'at_ref is a mutable refrence to u_int', 'first_ref is a mutable refrence to u_int']
void helper_grid_reflow_1(unsigned int * const gl_idx_ref, u_int * const width_ref, u_int * const i_ref, u_int * const at_ref, u_int * const first_ref, struct grid * const gd, u_int sx, struct grid * const target, struct grid_line * const gl, struct grid_cell gc, u_int yy, u_int cy)
{
  unsigned int gl_idx = *gl_idx_ref;
  u_int width = *width_ref;
  u_int i = *i_ref;
  u_int at = *at_ref;
  u_int first = *first_ref;
  gl_idx = &gd->linedata[yy];
  if (gl->flags & 0x4)
  {
    continue;
  }
  first = (at = (width = 0));
  if ((~gl->flags) & 0x2)
  {
    first = 1;
    width = gl->cellused;
    if (width > sx)
    {
      at = sx;
    }
    else
      at = width;
  }
  else
  {
    for (i = 0; i < gl->cellused; i += 1)
    {
      grid_get_cell1(gl, i, &gc);
      if (i == 0)
      {
        first = gc.data.width;
      }
      if ((at == 0) && ((width + gc.data.width) > sx))
      {
        at = i;
      }
      width += gc.data.width;
    }

  }
  if ((width == sx) || (first > sx))
  {
    grid_reflow_move(target, gl);
    continue;
  }
  if (width > sx)
  {
    grid_reflow_split(target, gd, sx, yy, at, &cy);
    continue;
  }
  if (gl->flags & 0x1)
  {
    grid_reflow_join(target, gd, sx, yy, width, &cy, 0);
  }
  else
    grid_reflow_move(target, gl);
  *gl_idx_ref = gl_idx;
  *width_ref = width;
  *i_ref = i;
  *at_ref = at;
  *first_ref = first;
}


/*** DEPENDENCIES:
static struct grid_line *grid_reflow_move(struct grid *gd, struct grid_line *from)
{
  struct grid_line *to;
  unsigned int to_idx = 0;
  to_idx = grid_reflow_add(gd, 1);
  memcpy(to, from, sizeof(*(&to[to_idx])));
  grid_reflow_dead(from);
  return to;
}


----------------------------
static void grid_get_cell1(struct grid_line *gl, u_int px, struct grid_cell *gc)
{
  struct grid_cell_entry *gce = &gl->celldata[px];
  if (gce->flags & 0x8)
  {
    if (gce->offset >= gl->extdsize)
    {
      memcpy(gc, &grid_default_cell, sizeof(*gc));
    }
    else
      memcpy(gc, &gl->extddata[gce->offset], sizeof(*gc));
    return;
  }
  gc->flags = gce->flags & (~(0x1 | 0x2));
  gc->attr = gce->data.attr;
  gc->fg = gce->data.fg;
  if (gce->flags & 0x1)
  {
    gc->fg |= 0x01000000;
  }
  gc->bg = gce->data.bg;
  if (gce->flags & 0x2)
  {
    gc->bg |= 0x01000000;
  }
  utf8_set(&gc->data, gce->data.data);
}


----------------------------
static void grid_reflow_join(struct grid *target, struct grid *gd, u_int sx, u_int yy, u_int width, u_int *cy, int already)
{
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  struct grid_line *from;
  unsigned int from_idx = 0;
  struct grid_cell gc;
  u_int lines;
  u_int want;
  u_int left;
  u_int i;
  u_int to;
  u_int line;
  u_int at;
  int wrapped = 1;
  if (!already)
  {
    to = target->sy;
    gl_idx = grid_reflow_move(target, &gd->linedata[yy]);
  }
  else
  {
    to = target->sy - 1;
    gl_idx = &target->linedata[to];
  }
  at = gl->cellused;
  lines = 0;
  for (;;)
  {
    helper_grid_reflow_join_1(&width, &from_idx, &lines, &want, &line, &at, &wrapped, target, gd, sx, yy, from, gc, to);
  }

  if (lines == 0)
  {
    return;
  }
  left = from->cellused - want;
  if (left != 0)
  {
    grid_move_cells(gd, 0, want, yy + lines, left, 8);
    from->cellsize = (from->cellused = left);
    lines -= 1;
  }
  else
    if (!wrapped)
  {
    gl->flags &= ~0x1;
  }
  for (i = yy + 1; i < ((yy + 1) + lines); i += 1)
  {
    free(gd->linedata[i].celldata);
    free(gd->linedata[i].extddata);
    grid_reflow_dead(&gd->linedata[i]);
  }

  if ((*cy) > (to + lines))
  {
    *cy -= lines;
  }
  else
    if ((*cy) > to)
  {
    *cy = to;
  }
  if (gd->hscrolled > (to + lines))
  {
    gd->hscrolled -= lines;
  }
  else
    if (gd->hscrolled > to)
  {
    gd->hscrolled = to;
  }
}


----------------------------
static void grid_reflow_split(struct grid *target, struct grid *gd, u_int sx, u_int yy, u_int at, u_int *cy)
{
  struct grid_line *gl = &gd->linedata[yy];
  struct grid_line *first;
  unsigned int first_idx = 0;
  struct grid_cell gc;
  u_int line;
  u_int lines;
  u_int width;
  u_int i;
  u_int xx;
  u_int used = gl->cellused;
  int flags = gl->flags;
  if ((~gl->flags) & 0x2)
  {
    lines = 1 + ((gl->cellused - 1) / sx);
  }
  else
  {
    lines = 2;
    width = 0;
    for (i = at; i < used; i += 1)
    {
      grid_get_cell1(gl, i, &gc);
      if ((width + gc.data.width) > sx)
      {
        lines += 1;
        width = 0;
      }
      width += gc.data.width;
    }

  }
  line = target->sy + 1;
  first_idx = grid_reflow_add(target, lines);
  width = 0;
  xx = 0;
  for (i = at; i < used; i += 1)
  {
    grid_get_cell1(gl, i, &gc);
    if ((width + gc.data.width) > sx)
    {
      target->linedata[line].flags |= 0x1;
      line += 1;
      width = 0;
      xx = 0;
    }
    width += gc.data.width;
    grid_set_cell(target, xx, line, &gc);
    xx += 1;
  }

  if (flags & 0x1)
  {
    target->linedata[line].flags |= 0x1;
  }
  gl->cellsize = (gl->cellused = at);
  gl->flags |= 0x1;
  memcpy(first, gl, sizeof(*(&first[first_idx])));
  grid_reflow_dead(gl);
  if (yy <= (*cy))
  {
    *cy += lines - 1;
  }
  if (yy <= gd->hscrolled)
  {
    gd->hscrolled += lines - 1;
  }
  if ((width < sx) && (flags & 0x1))
  {
    grid_reflow_join(target, gd, sx, yy, width, cy, 1);
  }
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
None
----------------------------
***/


void grid_reflow(struct grid *gd, u_int sx, u_int *cursor)
{
  struct grid *target;
  unsigned int target_idx = 0;
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  struct grid_cell gc;
  u_int yy;
  u_int cy;
  u_int width;
  u_int i;
  u_int at;
  u_int first;
  struct timeval start;
  struct timeval tv;
  gettimeofday(&start, 0);
  log_debug("%s: %u lines, new width %u", __func__, gd->hsize + gd->sy, sx);
  cy = gd->hsize + (*cursor);
  target_idx = grid_create(gd->sx, 0, 0);
  for (yy = 0; yy < (gd->hsize + gd->sy); yy += 1)
  {
    helper_grid_reflow_1(&gl_idx, &width, &i, &at, &first, gd, sx, target, gl, gc, yy, cy);
  }

  if (target->sy < gd->sy)
  {
    grid_reflow_add(target, gd->sy - target->sy);
  }
  gd->hsize = target->sy - gd->sy;
  free(gd->linedata);
  gd->linedata = target->linedata;
  free(target);
  if (gd->hscrolled > gd->hsize)
  {
    gd->hscrolled = gd->hsize;
  }
  if (cy < gd->hsize)
  {
    *cursor = 0;
  }
  else
    *cursor = cy - gd->hsize;
  gettimeofday(&tv, 0);
  do
  {
    (&tv)->tv_sec = (&tv)->tv_sec - (&start)->tv_sec;
    (&tv)->tv_usec = (&tv)->tv_usec - (&start)->tv_usec;
    if ((&tv)->tv_usec < 0)
    {
      (&tv)->tv_sec -= 1;
      (&tv)->tv_usec += 1000000;
    }
  }
  while (0);
  log_debug("%s: now %u lines (in %llu.%06u seconds)", __func__, gd->hsize + gd->sy, (unsigned long long) tv.tv_sec, (u_int) tv.tv_usec);
}


/*** DEPENDENCIES:
struct grid *grid_create(u_int sx, u_int sy, u_int hlimit)
{
  struct grid *gd;
  unsigned int gd_idx = 0;
  gd_idx = xmalloc(sizeof(*gd_idx));
  gd->sx = sx;
  gd->sy = sy;
  gd->flags = 0x1;
  gd->hscrolled = 0;
  gd->hsize = 0;
  gd->hlimit = hlimit;
  if (gd->sy != 0)
  {
    gd->linedata = xcalloc(gd->sy, sizeof(*gd->linedata));
  }
  else
    gd->linedata = 0;
  return gd;
}


----------------------------
static struct grid_line *grid_reflow_add(struct grid *gd, u_int n)
{
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  u_int sy = gd->sy + n;
  gd->linedata = xreallocarray(gd->linedata, sy, sizeof(*gd->linedata));
  gl_idx = &gd->linedata[gd->sy];
  memset(gl, 0, n * (sizeof(*(&gl[gl_idx]))));
  gd->sy = sy;
  return gl;
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
void helper_grid_reflow_1(unsigned int * const gl_idx_ref, u_int * const width_ref, u_int * const i_ref, u_int * const at_ref, u_int * const first_ref, struct grid * const gd, u_int sx, struct grid * const target, struct grid_line * const gl, struct grid_cell gc, u_int yy, u_int cy)
{
  unsigned int gl_idx = *gl_idx_ref;
  u_int width = *width_ref;
  u_int i = *i_ref;
  u_int at = *at_ref;
  u_int first = *first_ref;
  gl_idx = &gd->linedata[yy];
  if (gl->flags & 0x4)
  {
    continue;
  }
  first = (at = (width = 0));
  if ((~gl->flags) & 0x2)
  {
    first = 1;
    width = gl->cellused;
    if (width > sx)
    {
      at = sx;
    }
    else
      at = width;
  }
  else
  {
    for (i = 0; i < gl->cellused; i += 1)
    {
      grid_get_cell1(gl, i, &gc);
      if (i == 0)
      {
        first = gc.data.width;
      }
      if ((at == 0) && ((width + gc.data.width) > sx))
      {
        at = i;
      }
      width += gc.data.width;
    }

  }
  if ((width == sx) || (first > sx))
  {
    grid_reflow_move(target, gl);
    continue;
  }
  if (width > sx)
  {
    grid_reflow_split(target, gd, sx, yy, at, &cy);
    continue;
  }
  if (gl->flags & 0x1)
  {
    grid_reflow_join(target, gd, sx, yy, width, &cy, 0);
  }
  else
    grid_reflow_move(target, gl);
  *gl_idx_ref = gl_idx;
  *width_ref = width;
  *i_ref = i;
  *at_ref = at;
  *first_ref = first;
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


static void grid_empty_line(struct grid *gd, u_int py, u_int bg)
{
  memset(&gd->linedata[py], 0, sizeof(gd->linedata[py]));
  if (bg != 8)
  {
    grid_expand_line(gd, py, gd->sx, bg);
  }
}


/*** DEPENDENCIES:
static void grid_expand_line(struct grid *gd, u_int py, u_int sx, u_int bg)
{
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  u_int xx;
  gl_idx = &gd->linedata[py];
  if (sx <= gl->cellsize)
  {
    return;
  }
  if (sx < (gd->sx / 4))
  {
    sx = gd->sx / 4;
  }
  else
    if (sx < (gd->sx / 2))
  {
    sx = gd->sx / 2;
  }
  else
    sx = gd->sx;
  gl->celldata = xreallocarray(gl->celldata, sx, sizeof(*gl->celldata));
  for (xx = gl->cellsize; xx < sx; xx += 1)
  {
    grid_clear_cell(gd, xx, py, bg);
  }

  gl->cellsize = sx;
}


----------------------------
None
----------------------------
***/


void grid_clear_lines(struct grid *gd, u_int py, u_int ny, u_int bg)
{
  u_int yy;
  if (ny == 0)
  {
    return;
  }
  if (grid_check_y(gd, __func__, py) != 0)
  {
    return;
  }
  if (grid_check_y(gd, __func__, (py + ny) - 1) != 0)
  {
    return;
  }
  for (yy = py; yy < (py + ny); yy += 1)
  {
    grid_free_line(gd, yy);
    grid_empty_line(gd, yy, bg);
  }

}


/*** DEPENDENCIES:
static int grid_check_y(struct grid *gd, const char *from, u_int py)
{
  if (py >= (gd->hsize + gd->sy))
  {
    log_debug("%s: y out of range: %u", from, py);
    return -1;
  }
  return 0;
}


----------------------------
static void grid_empty_line(struct grid *gd, u_int py, u_int bg)
{
  memset(&gd->linedata[py], 0, sizeof(gd->linedata[py]));
  if (bg != 8)
  {
    grid_expand_line(gd, py, gd->sx, bg);
  }
}


----------------------------
static void grid_free_line(struct grid *gd, u_int py)
{
  free(gd->linedata[py].celldata);
  gd->linedata[py].celldata = 0;
  free(gd->linedata[py].extddata);
  gd->linedata[py].extddata = 0;
}


----------------------------
None
----------------------------
***/


void grid_clear(struct grid *gd, u_int px, u_int py, u_int nx, u_int ny, u_int bg)
{
  u_int xx;
  u_int yy;
  if ((nx == 0) || (ny == 0))
  {
    return;
  }
  if ((px == 0) && (nx == gd->sx))
  {
    grid_clear_lines(gd, py, ny, bg);
    return;
  }
  if (grid_check_y(gd, __func__, py) != 0)
  {
    return;
  }
  if (grid_check_y(gd, __func__, (py + ny) - 1) != 0)
  {
    return;
  }
  for (yy = py; yy < (py + ny); yy += 1)
  {
    if (((px + nx) >= gd->sx) && (px < gd->linedata[yy].cellused))
    {
      gd->linedata[yy].cellused = px;
    }
    if ((px > gd->linedata[yy].cellsize) && (bg == 8))
    {
      continue;
    }
    if (((px + nx) >= gd->linedata[yy].cellsize) && (bg == 8))
    {
      gd->linedata[yy].cellsize = px;
      continue;
    }
    grid_expand_line(gd, yy, px + nx, 8);
    for (xx = px; xx < (px + nx); xx += 1)
    {
      grid_clear_cell(gd, xx, yy, bg);
    }

  }

}


/*** DEPENDENCIES:
static void grid_expand_line(struct grid *gd, u_int py, u_int sx, u_int bg)
{
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  u_int xx;
  gl_idx = &gd->linedata[py];
  if (sx <= gl->cellsize)
  {
    return;
  }
  if (sx < (gd->sx / 4))
  {
    sx = gd->sx / 4;
  }
  else
    if (sx < (gd->sx / 2))
  {
    sx = gd->sx / 2;
  }
  else
    sx = gd->sx;
  gl->celldata = xreallocarray(gl->celldata, sx, sizeof(*gl->celldata));
  for (xx = gl->cellsize; xx < sx; xx += 1)
  {
    grid_clear_cell(gd, xx, py, bg);
  }

  gl->cellsize = sx;
}


----------------------------
static int grid_check_y(struct grid *gd, const char *from, u_int py)
{
  if (py >= (gd->hsize + gd->sy))
  {
    log_debug("%s: y out of range: %u", from, py);
    return -1;
  }
  return 0;
}


----------------------------
void grid_clear_lines(struct grid *gd, u_int py, u_int ny, u_int bg)
{
  u_int yy;
  if (ny == 0)
  {
    return;
  }
  if (grid_check_y(gd, __func__, py) != 0)
  {
    return;
  }
  if (grid_check_y(gd, __func__, (py + ny) - 1) != 0)
  {
    return;
  }
  for (yy = py; yy < (py + ny); yy += 1)
  {
    grid_free_line(gd, yy);
    grid_empty_line(gd, yy, bg);
  }

}


----------------------------
static void grid_clear_cell(struct grid *gd, u_int px, u_int py, u_int bg)
{
  struct grid_line *gl = &gd->linedata[py];
  struct grid_cell_entry *gce = &gl->celldata[px];
  struct grid_cell *gc;
  unsigned int gc_idx = 0;
  memcpy(gce, &grid_default_entry, sizeof(*gce));
  if (bg & 0x02000000)
  {
    gc_idx = grid_extended_cell(gl, gce, &grid_default_cell);
    gc->bg = bg;
  }
  else
  {
    if (bg & 0x01000000)
    {
      gce->flags |= 0x2;
    }
    gce->data.bg = bg;
  }
}


----------------------------
None
----------------------------
***/


void grid_move_lines(struct grid *gd, u_int dy, u_int py, u_int ny, u_int bg)
{
  u_int yy;
  if ((ny == 0) || (py == dy))
  {
    return;
  }
  if (grid_check_y(gd, __func__, py) != 0)
  {
    return;
  }
  if (grid_check_y(gd, __func__, (py + ny) - 1) != 0)
  {
    return;
  }
  if (grid_check_y(gd, __func__, dy) != 0)
  {
    return;
  }
  if (grid_check_y(gd, __func__, (dy + ny) - 1) != 0)
  {
    return;
  }
  for (yy = dy; yy < (dy + ny); yy += 1)
  {
    if ((yy >= py) && (yy < (py + ny)))
    {
      continue;
    }
    grid_free_line(gd, yy);
  }

  memmove(&gd->linedata[dy], &gd->linedata[py], ny * (sizeof(*gd->linedata)));
  for (yy = py; yy < (py + ny); yy += 1)
  {
    if ((yy < dy) || (yy >= (dy + ny)))
    {
      grid_empty_line(gd, yy, bg);
    }
  }

}


/*** DEPENDENCIES:
static int grid_check_y(struct grid *gd, const char *from, u_int py)
{
  if (py >= (gd->hsize + gd->sy))
  {
    log_debug("%s: y out of range: %u", from, py);
    return -1;
  }
  return 0;
}


----------------------------
static void grid_empty_line(struct grid *gd, u_int py, u_int bg)
{
  memset(&gd->linedata[py], 0, sizeof(gd->linedata[py]));
  if (bg != 8)
  {
    grid_expand_line(gd, py, gd->sx, bg);
  }
}


----------------------------
static void grid_free_line(struct grid *gd, u_int py)
{
  free(gd->linedata[py].celldata);
  gd->linedata[py].celldata = 0;
  free(gd->linedata[py].extddata);
  gd->linedata[py].extddata = 0;
}


----------------------------
None
----------------------------
***/


void grid_collect_history(struct grid *gd)
{
  u_int ny;
  if ((gd->hsize == 0) || (gd->hsize < gd->hlimit))
  {
    return;
  }
  ny = gd->hlimit / 10;
  if (ny < 1)
  {
    ny = 1;
  }
  if (ny > gd->hsize)
  {
    ny = gd->hsize;
  }
  grid_free_lines(gd, 0, ny);
  memmove(&gd->linedata[0], &gd->linedata[ny], ((gd->hsize + gd->sy) - ny) * (sizeof(*gd->linedata)));
  gd->hsize -= ny;
  if (gd->hscrolled > gd->hsize)
  {
    gd->hscrolled = gd->hsize;
  }
}


/*** DEPENDENCIES:
static void grid_free_lines(struct grid *gd, u_int py, u_int ny)
{
  u_int yy;
  for (yy = py; yy < (py + ny); yy += 1)
  {
    grid_free_line(gd, yy);
  }

}


----------------------------
None
----------------------------
***/


static void grid_compact_line(struct grid_line *gl)
{
  int new_extdsize = 0;
  struct grid_cell *new_extddata;
  unsigned int new_extddata_idx = 0;
  struct grid_cell_entry *gce;
  unsigned int gce_idx = 0;
  struct grid_cell *gc;
  unsigned int gc_idx = 0;
  u_int px;
  u_int idx;
  if (gl->extdsize == 0)
  {
    return;
  }
  for (px = 0; px < gl->cellsize; px += 1)
  {
    gce_idx = &gl->celldata[px];
    if (gce->flags & 0x8)
    {
      new_extdsize += 1;
    }
  }

  if (new_extdsize == 0)
  {
    free(gl->extddata);
    gl->extddata = 0;
    gl->extdsize = 0;
    return;
  }
  new_extddata_idx = xreallocarray(0, new_extdsize, sizeof(*gl->extddata));
  idx = 0;
  for (px = 0; px < gl->cellsize; px += 1)
  {
    gce_idx = &gl->celldata[px];
    if (gce->flags & 0x8)
    {
      gc_idx = &gl->extddata[gce->offset];
      memcpy(&new_extddata[idx + new_extddata_idx], gc, sizeof(*(&gc[gc_idx])));
      gce->offset = idx;
      idx += 1;
    }
  }

  free(gl->extddata);
  gl->extddata = &new_extddata[new_extddata_idx];
  gl->extdsize = new_extdsize;
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
struct grid_cell_entry
{
  u_char flags;
  union 
  {
    u_int offset;
    struct 
    {
      u_char attr;
      u_char fg;
      u_char bg;
      u_char data;
    } data;
  };
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
None
----------------------------
***/


void grid_scroll_history(struct grid *gd, u_int bg)
{
  u_int yy;
  yy = gd->hsize + gd->sy;
  gd->linedata = xreallocarray(gd->linedata, yy + 1, sizeof(*gd->linedata));
  grid_empty_line(gd, yy, bg);
  gd->hscrolled += 1;
  grid_compact_line(&gd->linedata[gd->hsize]);
  gd->hsize += 1;
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
static void grid_compact_line(struct grid_line *gl)
{
  int new_extdsize = 0;
  struct grid_cell *new_extddata;
  unsigned int new_extddata_idx = 0;
  struct grid_cell_entry *gce;
  unsigned int gce_idx = 0;
  struct grid_cell *gc;
  unsigned int gc_idx = 0;
  u_int px;
  u_int idx;
  if (gl->extdsize == 0)
  {
    return;
  }
  for (px = 0; px < gl->cellsize; px += 1)
  {
    gce_idx = &gl->celldata[px];
    if (gce->flags & 0x8)
    {
      new_extdsize += 1;
    }
  }

  if (new_extdsize == 0)
  {
    free(gl->extddata);
    gl->extddata = 0;
    gl->extdsize = 0;
    return;
  }
  new_extddata_idx = xreallocarray(0, new_extdsize, sizeof(*gl->extddata));
  idx = 0;
  for (px = 0; px < gl->cellsize; px += 1)
  {
    gce_idx = &gl->celldata[px];
    if (gce->flags & 0x8)
    {
      gc_idx = &gl->extddata[gce->offset];
      memcpy(&new_extddata[idx + new_extddata_idx], gc, sizeof(*(&gc[gc_idx])));
      gce->offset = idx;
      idx += 1;
    }
  }

  free(gl->extddata);
  gl->extddata = &new_extddata[new_extddata_idx];
  gl->extdsize = new_extdsize;
}


----------------------------
static void grid_empty_line(struct grid *gd, u_int py, u_int bg)
{
  memset(&gd->linedata[py], 0, sizeof(gd->linedata[py]));
  if (bg != 8)
  {
    grid_expand_line(gd, py, gd->sx, bg);
  }
}


----------------------------
None
----------------------------
***/


void grid_scroll_history_region(struct grid *gd, u_int upper, u_int lower, u_int bg)
{
  struct grid_line *gl_history;
  unsigned int gl_history_idx = 0;
  struct grid_line *gl_upper;
  unsigned int gl_upper_idx = 0;
  u_int yy;
  yy = gd->hsize + gd->sy;
  gd->linedata = xreallocarray(gd->linedata, yy + 1, sizeof(*gd->linedata));
  gl_history_idx = &gd->linedata[gd->hsize];
  memmove((&gl_history[gl_history_idx]) + 1, gl_history, gd->sy * (sizeof(*(&gl_history[gl_history_idx]))));
  upper += 1;
  gl_upper_idx = &gd->linedata[upper];
  lower += 1;
  memcpy(gl_history, gl_upper, sizeof(*(&gl_history[gl_history_idx])));
  memmove(gl_upper, (&gl_upper[gl_upper_idx]) + 1, (lower - upper) * (sizeof(*(&gl_upper[gl_upper_idx]))));
  grid_empty_line(gd, lower, bg);
  gd->hscrolled += 1;
  gd->hsize += 1;
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
static void grid_empty_line(struct grid *gd, u_int py, u_int bg)
{
  memset(&gd->linedata[py], 0, sizeof(gd->linedata[py]));
  if (bg != 8)
  {
    grid_expand_line(gd, py, gd->sx, bg);
  }
}


----------------------------
None
----------------------------
***/


int grid_compare(struct grid *ga, struct grid *gb)
{
  struct grid_line *gla;
  unsigned int gla_idx = 0;
  struct grid_line *glb;
  unsigned int glb_idx = 0;
  struct grid_cell gca;
  struct grid_cell gcb;
  u_int xx;
  u_int yy;
  if ((ga->sx != gb->sx) || (ga->sy != gb->sy))
  {
    return 1;
  }
  for (yy = 0; yy < ga->sy; yy += 1)
  {
    gla_idx = &ga->linedata[yy];
    glb_idx = &gb->linedata[yy];
    if (gla->cellsize != glb->cellsize)
    {
      return 1;
    }
    for (xx = 0; xx < gla->cellsize; xx += 1)
    {
      grid_get_cell(ga, xx, yy, &gca);
      grid_get_cell(gb, xx, yy, &gcb);
      if (!grid_cells_equal(&gca, &gcb))
      {
        return 1;
      }
    }

  }

  return 0;
}


/*** DEPENDENCIES:
int grid_cells_equal(const struct grid_cell *gca, const struct grid_cell *gcb)
{
  if ((gca->fg != gcb->fg) || (gca->bg != gcb->bg))
  {
    return 0;
  }
  if ((gca->attr != gcb->attr) || (gca->flags != gcb->flags))
  {
    return 0;
  }
  if (gca->data.width != gcb->data.width)
  {
    return 0;
  }
  if (gca->data.size != gcb->data.size)
  {
    return 0;
  }
  return memcmp(gca->data.data, gcb->data.data, gca->data.size) == 0;
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
void grid_get_cell(struct grid *gd, u_int px, u_int py, struct grid_cell *gc)
{
  if ((grid_check_y(gd, __func__, py) != 0) || (px >= gd->linedata[py].cellsize))
  {
    memcpy(gc, &grid_default_cell, sizeof(*gc));
    return;
  }
  return grid_get_cell1(&gd->linedata[py], px, gc);
}


----------------------------
None
----------------------------
***/


void grid_clear_history(struct grid *gd)
{
  grid_free_lines(gd, 0, gd->hsize);
  memmove(&gd->linedata[0], &gd->linedata[gd->hsize], gd->sy * (sizeof(*gd->linedata)));
  gd->hscrolled = 0;
  gd->hsize = 0;
  gd->linedata = xreallocarray(gd->linedata, gd->sy, sizeof(*gd->linedata));
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
static void grid_free_lines(struct grid *gd, u_int py, u_int ny)
{
  u_int yy;
  for (yy = py; yy < (py + ny); yy += 1)
  {
    grid_free_line(gd, yy);
  }

}


----------------------------
None
----------------------------
***/


void grid_duplicate_lines(struct grid *dst, u_int dy, struct grid *src, u_int sy, u_int ny)
{
  struct grid_line *dstl;
  unsigned int dstl_idx = 0;
  struct grid_line *srcl;
  unsigned int srcl_idx = 0;
  u_int yy;
  if ((dy + ny) > (dst->hsize + dst->sy))
  {
    ny = (dst->hsize + dst->sy) - dy;
  }
  if ((sy + ny) > (src->hsize + src->sy))
  {
    ny = (src->hsize + src->sy) - sy;
  }
  grid_free_lines(dst, dy, ny);
  for (yy = 0; yy < ny; yy += 1)
  {
    srcl_idx = &src->linedata[sy];
    dstl_idx = &dst->linedata[dy];
    memcpy(dstl, srcl, sizeof(*(&dstl[dstl_idx])));
    if (srcl->cellsize != 0)
    {
      dstl->celldata = xreallocarray(0, srcl->cellsize, sizeof(*dstl->celldata));
      memcpy(dstl->celldata, srcl->celldata, srcl->cellsize * (sizeof(*dstl->celldata)));
    }
    else
      dstl->celldata = 0;
    if (srcl->extdsize != 0)
    {
      dstl->extdsize = srcl->extdsize;
      dstl->extddata = xreallocarray(0, dstl->extdsize, sizeof(*dstl->extddata));
      memcpy(dstl->extddata, srcl->extddata, dstl->extdsize * (sizeof(*dstl->extddata)));
    }
    sy += 1;
    dy += 1;
  }

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
static void grid_free_lines(struct grid *gd, u_int py, u_int ny)
{
  u_int yy;
  for (yy = py; yy < (py + ny); yy += 1)
  {
    grid_free_line(gd, yy);
  }

}


----------------------------
None
----------------------------
***/


