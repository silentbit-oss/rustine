char *grid_view_string_cells(struct grid *gd, u_int px, u_int py, u_int nx)
{
  px = px;
  py = gd->hsize + py;
  return grid_string_cells(gd, px, py, nx, 0, 0, 0, 0);
}


/*** DEPENDENCIES:
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
***/


void grid_view_get_cell(struct grid *gd, u_int px, u_int py, struct grid_cell *gc)
{
  grid_get_cell(gd, px, gd->hsize + py, gc);
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


void grid_view_set_cells(struct grid *gd, u_int px, u_int py, const struct grid_cell *gc, const char *s, size_t slen)
{
  grid_set_cells(gd, px, gd->hsize + py, gc, s, slen);
}


/*** DEPENDENCIES:
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


void grid_view_set_cell(struct grid *gd, u_int px, u_int py, const struct grid_cell *gc)
{
  grid_set_cell(gd, px, gd->hsize + py, gc);
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
None
----------------------------
***/


void grid_view_delete_lines(struct grid *gd, u_int py, u_int ny, u_int bg)
{
  u_int sy;
  py = gd->hsize + py;
  sy = gd->hsize + gd->sy;
  grid_move_lines(gd, py, py + ny, (sy - py) - ny, bg);
  grid_clear(gd, 0, sy - ny, gd->sx, (py + ny) - (sy - ny), bg);
}


/*** DEPENDENCIES:
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


----------------------------
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


----------------------------
None
----------------------------
***/


void grid_view_clear(struct grid *gd, u_int px, u_int py, u_int nx, u_int ny, u_int bg)
{
  px = px;
  py = gd->hsize + py;
  grid_clear(gd, px, py, nx, ny, bg);
}


/*** DEPENDENCIES:
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


----------------------------
None
----------------------------
***/


void grid_view_scroll_region_down(struct grid *gd, u_int rupper, u_int rlower, u_int bg)
{
  rupper = gd->hsize + rupper;
  rlower = gd->hsize + rlower;
  grid_move_lines(gd, rupper + 1, rupper, rlower - rupper, bg);
}


/*** DEPENDENCIES:
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


----------------------------
None
----------------------------
***/


void grid_view_insert_lines(struct grid *gd, u_int py, u_int ny, u_int bg)
{
  u_int sy;
  py = gd->hsize + py;
  sy = gd->hsize + gd->sy;
  grid_move_lines(gd, py + ny, py, (sy - py) - ny, bg);
}


/*** DEPENDENCIES:
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


----------------------------
None
----------------------------
***/


void grid_view_insert_cells(struct grid *gd, u_int px, u_int py, u_int nx, u_int bg)
{
  u_int sx;
  px = px;
  py = gd->hsize + py;
  sx = gd->sx;
  if (px >= (sx - 1))
  {
    grid_clear(gd, px, py, 1, 1, bg);
  }
  else
    grid_move_cells(gd, px + nx, px, py, (sx - px) - nx, bg);
}


/*** DEPENDENCIES:
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
None
----------------------------
***/


void grid_view_scroll_region_up(struct grid *gd, u_int rupper, u_int rlower, u_int bg)
{
  if (gd->flags & 0x1)
  {
    grid_collect_history(gd);
    if ((rupper == 0) && (rlower == (gd->sy - 1)))
    {
      grid_scroll_history(gd, bg);
    }
    else
    {
      rupper = gd->hsize + rupper;
      rlower = gd->hsize + rlower;
      grid_scroll_history_region(gd, rupper, rlower, bg);
    }
  }
  else
  {
    rupper = gd->hsize + rupper;
    rlower = gd->hsize + rlower;
    grid_move_lines(gd, rupper, rupper + 1, rlower - rupper, bg);
  }
}


/*** DEPENDENCIES:
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


----------------------------
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


----------------------------
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


----------------------------
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


----------------------------
None
----------------------------
***/


void grid_view_insert_lines_region(struct grid *gd, u_int rlower, u_int py, u_int ny, u_int bg)
{
  u_int ny2;
  rlower = gd->hsize + rlower;
  py = gd->hsize + py;
  ny2 = ((rlower + 1) - py) - ny;
  grid_move_lines(gd, (rlower + 1) - ny2, py, ny2, bg);
  grid_clear(gd, 0, py + ny2, gd->sx, ny - ny2, bg);
}


/*** DEPENDENCIES:
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


----------------------------
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


----------------------------
None
----------------------------
***/


void grid_view_delete_lines_region(struct grid *gd, u_int rlower, u_int py, u_int ny, u_int bg)
{
  u_int ny2;
  rlower = gd->hsize + rlower;
  py = gd->hsize + py;
  ny2 = ((rlower + 1) - py) - ny;
  grid_move_lines(gd, py, py + ny, ny2, bg);
  grid_clear(gd, 0, py + ny2, gd->sx, ny - ny2, bg);
}


/*** DEPENDENCIES:
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


----------------------------
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


----------------------------
None
----------------------------
***/


void grid_view_delete_cells(struct grid *gd, u_int px, u_int py, u_int nx, u_int bg)
{
  u_int sx;
  px = px;
  py = gd->hsize + py;
  sx = gd->sx;
  grid_move_cells(gd, px, px + nx, py, (sx - px) - nx, bg);
  grid_clear(gd, sx - nx, py, (px + nx) - (sx - nx), 1, bg);
}


/*** DEPENDENCIES:
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
None
----------------------------
***/


void grid_view_clear_history(struct grid *gd, u_int bg)
{
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  u_int yy;
  u_int last;
  last = 0;
  for (yy = 0; yy < gd->sy; yy += 1)
  {
    gl_idx = &gd->linedata[gd->hsize + yy];
    if (gl->cellused != 0)
    {
      last = yy + 1;
    }
  }

  if (last == 0)
  {
    grid_view_clear(gd, 0, 0, gd->sx, gd->sy, bg);
    return;
  }
  for (yy = 0; yy < last; yy += 1)
  {
    grid_collect_history(gd);
    grid_scroll_history(gd, bg);
  }

  if (last < gd->sy)
  {
    grid_view_clear(gd, 0, 0, gd->sx, gd->sy - last, bg);
  }
  gd->hscrolled = 0;
}


/*** DEPENDENCIES:
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


----------------------------
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


----------------------------
void grid_view_clear(struct grid *gd, u_int px, u_int py, u_int nx, u_int ny, u_int bg)
{
  px = px;
  py = gd->hsize + py;
  grid_clear(gd, px, py, nx, ny, bg);
}


----------------------------
None
----------------------------
***/


