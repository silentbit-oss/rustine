void *mode_tree_get_current(struct mode_tree_data *mtd)
{
  return mtd->line_list[mtd->current].item->itemdata;
}


/*** DEPENDENCIES:
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
***/


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


/*** DEPENDENCIES:
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
***/


void mode_tree_up(struct mode_tree_data *mtd, int wrap)
{
  if (mtd->current == 0)
  {
    if (wrap)
    {
      mtd->current = mtd->line_size - 1;
      if (mtd->line_size >= mtd->height)
      {
        mtd->offset = mtd->line_size - mtd->height;
      }
    }
  }
  else
  {
    mtd->current -= 1;
    if (mtd->current < mtd->offset)
    {
      mtd->offset -= 1;
    }
  }
}


/*** DEPENDENCIES:
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
***/


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


/*** DEPENDENCIES:
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
***/


static void mode_tree_check_selected(struct mode_tree_data *mtd)
{
  if (mtd->current > (mtd->height - 1))
  {
    mtd->offset = (mtd->current - mtd->height) + 1;
  }
}


/*** DEPENDENCIES:
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
***/


static void mode_tree_clear_lines(struct mode_tree_data *mtd)
{
  free(mtd->line_list);
  mtd->line_list = 0;
  mtd->line_size = 0;
}


/*** DEPENDENCIES:
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
***/


static void mode_tree_remove_ref(struct mode_tree_data *mtd)
{
  if ((--mtd->references) == 0)
  {
    free(mtd);
  }
}


/*** DEPENDENCIES:
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
***/


static void mode_tree_search_free(void *data)
{
  mode_tree_remove_ref(data);
}


/*** DEPENDENCIES:
static void mode_tree_remove_ref(struct mode_tree_data *mtd)
{
  if ((--mtd->references) == 0)
  {
    free(mtd);
  }
}


----------------------------
***/


static void mode_tree_filter_free(void *data)
{
  mode_tree_remove_ref(data);
}


/*** DEPENDENCIES:
static void mode_tree_remove_ref(struct mode_tree_data *mtd)
{
  if ((--mtd->references) == 0)
  {
    free(mtd);
  }
}


----------------------------
***/


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


/*** DEPENDENCIES:
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
None
----------------------------
***/


static void mode_tree_build_lines(struct mode_tree_data *mtd, struct mode_tree_list *mtl, u_int depth)
{
  struct mode_tree_item *mti;
  unsigned int mti_idx = 0;
  struct mode_tree_line *line;
  unsigned int line_idx = 0;
  u_int i;
  int flat = 1;
  mtd->depth = depth;
  for (mti_idx = mtl->tqh_first; (&mti[mti_idx]) != 0; mti_idx = mti_idx->entry.tqe_next)
  {
    mtd->line_list = xreallocarray(mtd->line_list, mtd->line_size + 1, sizeof(*mtd->line_list));
    line_idx = &mtd->line_list[mtd->line_size++];
    line->item = &mti[mti_idx];
    line->depth = depth;
    line->last = (&mti[mti_idx]) == (*((struct mode_tree_list *) mtl->tqh_last)->tqh_last);
    mti->line = mtd->line_size - 1;
    if (!((&mti->children)->tqh_first == 0))
    {
      flat = 0;
    }
    if (mti->expanded)
    {
      mode_tree_build_lines(mtd, &mti->children, depth + 1);
    }
  }

  for (mti_idx = mtl->tqh_first; (&mti[mti_idx]) != 0; mti_idx = mti_idx->entry.tqe_next)
  {
    for (i = 0; i < mtd->line_size; i += 1)
    {
      line_idx = &mtd->line_list[i];
      if (line->item == (&mti[mti_idx]))
      {
        line->flat = flat;
      }
    }

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
struct mode_tree_line
{
  struct mode_tree_item *item;
  u_int depth;
  int last;
  int flat;
}
----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
None
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
static void mode_tree_clear_lines(struct mode_tree_data *mtd)
{
  free(mtd->line_list);
  mtd->line_list = 0;
  mtd->line_size = 0;
}


----------------------------
static void mode_tree_check_selected(struct mode_tree_data *mtd)
{
  if (mtd->current > (mtd->height - 1))
  {
    mtd->offset = (mtd->current - mtd->height) + 1;
  }
}


----------------------------
static void mode_tree_build_lines(struct mode_tree_data *mtd, struct mode_tree_list *mtl, u_int depth)
{
  struct mode_tree_item *mti;
  unsigned int mti_idx = 0;
  struct mode_tree_line *line;
  unsigned int line_idx = 0;
  u_int i;
  int flat = 1;
  mtd->depth = depth;
  for (mti_idx = mtl->tqh_first; (&mti[mti_idx]) != 0; mti_idx = mti_idx->entry.tqe_next)
  {
    mtd->line_list = xreallocarray(mtd->line_list, mtd->line_size + 1, sizeof(*mtd->line_list));
    line_idx = &mtd->line_list[mtd->line_size++];
    line->item = &mti[mti_idx];
    line->depth = depth;
    line->last = (&mti[mti_idx]) == (*((struct mode_tree_list *) mtl->tqh_last)->tqh_last);
    mti->line = mtd->line_size - 1;
    if (!((&mti->children)->tqh_first == 0))
    {
      flat = 0;
    }
    if (mti->expanded)
    {
      mode_tree_build_lines(mtd, &mti->children, depth + 1);
    }
  }

  for (mti_idx = mtl->tqh_first; (&mti[mti_idx]) != 0; mti_idx = mti_idx->entry.tqe_next)
  {
    for (i = 0; i < mtd->line_size; i += 1)
    {
      line_idx = &mtd->line_list[i];
      if (line->item == (&mti[mti_idx]))
      {
        line->flat = flat;
      }
    }

  }

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


void mode_tree_expand_current(struct mode_tree_data *mtd)
{
  if (!mtd->line_list[mtd->current].item->expanded)
  {
    mtd->line_list[mtd->current].item->expanded = 1;
    mode_tree_build(mtd);
  }
}


/*** DEPENDENCIES:
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
***/


static struct mode_tree_item *mode_tree_search_for(struct mode_tree_data *mtd)
{
  struct mode_tree_item *mti;
  unsigned int mti_idx = 0;
  struct mode_tree_item *last;
  struct mode_tree_item *next;
  unsigned int next_idx = 0;
  if (mtd->search == 0)
  {
    return 0;
  }
  mti_idx = (last = mtd->line_list[mtd->current].item);
  for (;;)
  {
    if (!((&mti->children)->tqh_first == 0))
    {
      mti_idx = (&mti_idx->children)->tqh_first;
    }
    else
      if ((next_idx = mti->entry.tqe_next) != 0)
    {
      mti_idx = &next[next_idx];
    }
    else
    {
      for (;;)
      {
        mti_idx = mti_idx->parent;
        if ((&mti[mti_idx]) == 0)
        {
          break;
        }
        if ((next_idx = mti->entry.tqe_next) != 0)
        {
          mti_idx = &next[next_idx];
          break;
        }
      }

    }
    if ((&mti[mti_idx]) == 0)
    {
      mti_idx = (&mtd->children)->tqh_first;
    }
    if ((&mti[mti_idx]) == last)
    {
      break;
    }
    if (mtd->searchcb == 0)
    {
      if (strstr(mti->name, mtd->search) != 0)
      {
        return mti;
      }
      continue;
    }
    if (mtd->searchcb(mtd->modedata, mti->itemdata, mtd->search))
    {
      return mti;
    }
  }

  return 0;
}


/*** DEPENDENCIES:
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
None
----------------------------
***/


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


/*** DEPENDENCIES:
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
None
----------------------------
None
----------------------------
***/


static struct mode_tree_item *mode_tree_find_item(struct mode_tree_list *mtl, uint64_t tag)
{
  struct mode_tree_item *mti;
  unsigned int mti_idx = 0;
  struct mode_tree_item *child;
  unsigned int child_idx = 0;
  for (mti_idx = mtl->tqh_first; (&mti[mti_idx]) != 0; mti_idx = mti_idx->entry.tqe_next)
  {
    if (mti->tag == tag)
    {
      return mti;
    }
    child_idx = mode_tree_find_item(&mti->children, tag);
    if ((&child[child_idx]) != 0)
    {
      return child;
    }
  }

  return 0;
}


/*** DEPENDENCIES:
None
----------------------------
***/


static void mode_tree_clear_tagged(struct mode_tree_list *mtl)
{
  struct mode_tree_item *mti;
  unsigned int mti_idx = 0;
  for (mti_idx = mtl->tqh_first; (&mti[mti_idx]) != 0; mti_idx = mti_idx->entry.tqe_next)
  {
    mti->tagged = 0;
    mode_tree_clear_tagged(&mti->children);
  }

}


/*** DEPENDENCIES:
None
----------------------------
***/


// hint:  ['line_idx_ref is a mutable refrence to unsigned int', 'mti_idx_ref is a mutable refrence to unsigned int', 'gc0_ref is a mutable refrence to ', 'gc_ref is a mutable refrence to ', 'j_ref is a mutable refrence to u_int', 'start_idx_ref is a mutable refrence to unsigned int', 'tag_idx_ref is a mutable refrence to unsigned int', 'symbol_idx_ref is a mutable refrence to unsigned int', 'size_ref is a mutable refrence to size_t']
void helper_mode_tree_draw_1(unsigned int * const line_idx_ref, unsigned int * const mti_idx_ref, struct grid_cell * const gc0_ref, struct grid_cell * const gc_ref, u_int * const j_ref, unsigned int * const start_idx_ref, unsigned int * const tag_idx_ref, unsigned int * const symbol_idx_ref, size_t * const size_ref, struct mode_tree_data * const mtd, struct mode_tree_line * const line, struct mode_tree_item * const mti, struct screen_write_ctx ctx, u_int w, u_int h, u_int i, char * const text, char * const start, char key[7], const char * const tag, const char * const symbol, int keylen)
{
  unsigned int line_idx = *line_idx_ref;
  unsigned int mti_idx = *mti_idx_ref;
  struct grid_cell gc0 = *gc0_ref;
  struct grid_cell gc = *gc_ref;
  u_int j = *j_ref;
  unsigned int start_idx = *start_idx_ref;
  unsigned int tag_idx = *tag_idx_ref;
  unsigned int symbol_idx = *symbol_idx_ref;
  size_t size = *size_ref;
  if (i < mtd->offset)
  {
    continue;
  }
  if (i > ((mtd->offset + h) - 1))
  {
    break;
  }
  line_idx = &mtd->line_list[i];
  mti_idx = line->item;
  screen_write_cursormove(&ctx, 0, i - mtd->offset);
  if (i < 10)
  {
    snprintf(key, sizeof(key), "(%c)  ", '0' + i);
  }
  else
    if (i < 36)
  {
    snprintf(key, sizeof(key), "(M-%c)", 'a' + (i - 10));
  }
  else
    *key = '\0';
  if (line->flat)
  {
    symbol_idx = "";
  }
  else
    if ((&mti->children)->tqh_first == 0)
  {
    symbol_idx = "  ";
  }
  else
    if (mti->expanded)
  {
    symbol_idx = "- ";
  }
  else
    symbol_idx = "+ ";
  if (line->depth == 0)
  {
    start_idx = xstrdup(symbol);
  }
  else
  {
    size = (4 * line->depth) + 32;
    start_idx = xcalloc(1, size);
    for (j = 1; j < line->depth; j += 1)
    {
      if ((mti->parent != 0) && mtd->line_list[mti->parent->line].last)
      {
        strlcat(start, "    ", size);
      }
      else
        strlcat(start, "\001x\001   ", size);
    }

    if (line->last)
    {
      strlcat(start, "\001mq\001> ", size);
    }
    else
      strlcat(start, "\001tq\001> ", size);
    strlcat(start, symbol, size);
  }
  if (mti->tagged)
  {
    tag_idx = "*";
  }
  else
    tag_idx = "";
  xasprintf(&text, "%-*s%s%s%s: %s", keylen, key, start, mti->name, tag, mti->text);
  free(start);
  if (mti->tagged)
  {
    gc.attr ^= 0x1;
    gc0.attr ^= 0x1;
  }
  if (i != mtd->current)
  {
    screen_write_nputs(&ctx, w, &gc0, "%s", text);
    screen_write_clearendofline(&ctx, 8);
  }
  else
  {
    screen_write_nputs(&ctx, w, &gc, "%s", text);
    screen_write_clearendofline(&ctx, gc.bg);
  }
  free(text);
  if (mti->tagged)
  {
    gc.attr ^= 0x1;
    gc0.attr ^= 0x1;
  }
  *line_idx_ref = line_idx;
  *mti_idx_ref = mti_idx;
  *gc0_ref = gc0;
  *gc_ref = gc;
  *j_ref = j;
  *start_idx_ref = start_idx;
  *tag_idx_ref = tag_idx;
  *symbol_idx_ref = symbol_idx;
  *size_ref = size;
}


/*** DEPENDENCIES:
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
struct mode_tree_line
{
  struct mode_tree_item *item;
  u_int depth;
  int last;
  int flat;
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
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
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
void screen_write_nputs(struct screen_write_ctx *ctx, ssize_t maxlen, const struct grid_cell *gcp, const char *fmt, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  screen_write_vnputs(ctx, maxlen, gcp, fmt, ap);
  ;
}


----------------------------
None
----------------------------
void screen_write_clearendofline(struct screen_write_ctx *ctx, u_int bg)
{
  struct screen *s = ctx->s;
  struct grid_line *gl;
  unsigned int gl_idx = 0;
  struct tty_ctx ttyctx;
  u_int sx = s->grid->sx;
  gl_idx = &s->grid->linedata[s->grid->hsize + s->cy];
  if ((s->cx > (sx - 1)) || ((s->cx >= gl->cellsize) && (bg == 8)))
  {
    return;
  }
  screen_write_initctx(ctx, &ttyctx);
  ttyctx.bg = bg;
  grid_view_clear(s->grid, s->cx, s->cy, sx - s->cx, 1, bg);
  if (s->cx == 0)
  {
    screen_write_collect_clear(ctx, s->cy, 1);
  }
  screen_write_collect_flush(ctx, 0);
  tty_write(tty_cmd_clearendofline, &ttyctx);
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
void style_apply(struct grid_cell *gc, struct options *oo, const char *name)
{
  const struct grid_cell *gcp;
  unsigned int gcp_idx = 0;
  memcpy(gc, &grid_default_cell, sizeof(*gc));
  gcp_idx = options_get_style(oo, name);
  gc->fg = gcp->fg;
  gc->bg = gcp->bg;
  gc->attr |= gcp->attr;
}


----------------------------
struct mode_tree_line
{
  struct mode_tree_item *item;
  u_int depth;
  int last;
  int flat;
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
void screen_write_stop(struct screen_write_ctx *ctx)
{
  screen_write_collect_end(ctx);
  screen_write_collect_flush(ctx, 0);
  log_debug("%s: %u cells (%u written, %u skipped)", __func__, ctx->cells, ctx->written, ctx->skipped);
  free(ctx->item);
  free(ctx->list);
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
void screen_write_clearscreen(struct screen_write_ctx *ctx, u_int bg)
{
  struct screen *s = ctx->s;
  struct tty_ctx ttyctx;
  u_int sx = s->grid->sx;
  u_int sy = s->grid->sy;
  screen_write_initctx(ctx, &ttyctx);
  ttyctx.bg = bg;
  if (s->grid->flags & 0x1)
  {
    grid_view_clear_history(s->grid, bg);
  }
  else
    grid_view_clear(s->grid, 0, 0, sx, sy, bg);
  screen_write_collect_clear(ctx, 0, sy);
  tty_write(tty_cmd_clearscreen, &ttyctx);
}


----------------------------
extern const struct grid_cell grid_default_cell
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
void screen_write_start(struct screen_write_ctx *ctx, struct window_pane *wp, struct screen *s)
{
  char tmp[16];
  u_int y;
  memset(ctx, 0, sizeof(*ctx));
  ctx->wp = wp;
  if ((wp != 0) && (s == 0))
  {
    ctx->s = wp->screen;
  }
  else
    ctx->s = s;
  ctx->list = xcalloc(ctx->s->grid->sy, sizeof(*ctx->list));
  for (y = 0; y < ctx->s->grid->sy; y += 1)
  {
    do
    {
      (&ctx->list[y].items)->tqh_first = 0;
      (&ctx->list[y].items)->tqh_last = &(&ctx->list[y].items)->tqh_first;
    }
    while (0);
  }

  ctx->item = xcalloc(1, sizeof(*ctx->item));
  ctx->scrolled = 0;
  ctx->bg = 8;
  if (wp != 0)
  {
    snprintf(tmp, sizeof(tmp), "pane %%%u", wp->id);
  }
  log_debug("%s: size %ux%u, %s", __func__, ctx->s->grid->sx, ctx->s->grid->sy, (wp == 0) ? ("no pane") : (tmp));
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
void helper_mode_tree_draw_1(unsigned int * const line_idx_ref, unsigned int * const mti_idx_ref, struct grid_cell * const gc0_ref, struct grid_cell * const gc_ref, u_int * const j_ref, unsigned int * const start_idx_ref, unsigned int * const tag_idx_ref, unsigned int * const symbol_idx_ref, size_t * const size_ref, struct mode_tree_data * const mtd, struct mode_tree_line * const line, struct mode_tree_item * const mti, struct screen_write_ctx ctx, u_int w, u_int h, u_int i, char * const text, char * const start, char key[7], const char * const tag, const char * const symbol, int keylen)
{
  unsigned int line_idx = *line_idx_ref;
  unsigned int mti_idx = *mti_idx_ref;
  struct grid_cell gc0 = *gc0_ref;
  struct grid_cell gc = *gc_ref;
  u_int j = *j_ref;
  unsigned int start_idx = *start_idx_ref;
  unsigned int tag_idx = *tag_idx_ref;
  unsigned int symbol_idx = *symbol_idx_ref;
  size_t size = *size_ref;
  if (i < mtd->offset)
  {
    continue;
  }
  if (i > ((mtd->offset + h) - 1))
  {
    break;
  }
  line_idx = &mtd->line_list[i];
  mti_idx = line->item;
  screen_write_cursormove(&ctx, 0, i - mtd->offset);
  if (i < 10)
  {
    snprintf(key, sizeof(key), "(%c)  ", '0' + i);
  }
  else
    if (i < 36)
  {
    snprintf(key, sizeof(key), "(M-%c)", 'a' + (i - 10));
  }
  else
    *key = '\0';
  if (line->flat)
  {
    symbol_idx = "";
  }
  else
    if ((&mti->children)->tqh_first == 0)
  {
    symbol_idx = "  ";
  }
  else
    if (mti->expanded)
  {
    symbol_idx = "- ";
  }
  else
    symbol_idx = "+ ";
  if (line->depth == 0)
  {
    start_idx = xstrdup(symbol);
  }
  else
  {
    size = (4 * line->depth) + 32;
    start_idx = xcalloc(1, size);
    for (j = 1; j < line->depth; j += 1)
    {
      if ((mti->parent != 0) && mtd->line_list[mti->parent->line].last)
      {
        strlcat(start, "    ", size);
      }
      else
        strlcat(start, "\001x\001   ", size);
    }

    if (line->last)
    {
      strlcat(start, "\001mq\001> ", size);
    }
    else
      strlcat(start, "\001tq\001> ", size);
    strlcat(start, symbol, size);
  }
  if (mti->tagged)
  {
    tag_idx = "*";
  }
  else
    tag_idx = "";
  xasprintf(&text, "%-*s%s%s%s: %s", keylen, key, start, mti->name, tag, mti->text);
  free(start);
  if (mti->tagged)
  {
    gc.attr ^= 0x1;
    gc0.attr ^= 0x1;
  }
  if (i != mtd->current)
  {
    screen_write_nputs(&ctx, w, &gc0, "%s", text);
    screen_write_clearendofline(&ctx, 8);
  }
  else
  {
    screen_write_nputs(&ctx, w, &gc, "%s", text);
    screen_write_clearendofline(&ctx, gc.bg);
  }
  free(text);
  if (mti->tagged)
  {
    gc.attr ^= 0x1;
    gc0.attr ^= 0x1;
  }
  *line_idx_ref = line_idx;
  *mti_idx_ref = mti_idx;
  *gc0_ref = gc0;
  *gc_ref = gc;
  *j_ref = j;
  *start_idx_ref = start_idx;
  *tag_idx_ref = tag_idx;
  *symbol_idx_ref = symbol_idx;
  *size_ref = size;
}


----------------------------
None
----------------------------
None
----------------------------
***/


static void mode_tree_search_set(struct mode_tree_data *mtd)
{
  struct mode_tree_item *mti;
  unsigned int mti_idx = 0;
  struct mode_tree_item *loop;
  unsigned int loop_idx = 0;
  uint64_t tag;
  mti_idx = mode_tree_search_for(mtd);
  if ((&mti[mti_idx]) == 0)
  {
    return;
  }
  tag = mti->tag;
  loop_idx = mti->parent;
  while ((&loop[loop_idx]) != 0)
  {
    loop->expanded = 1;
    loop_idx = loop_idx->parent;
  }

  mode_tree_build(mtd);
  mode_tree_set_current(mtd, tag);
  mode_tree_draw(mtd);
  mtd->wp->flags |= 0x1;
}


/*** DEPENDENCIES:
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
static struct mode_tree_item *mode_tree_search_for(struct mode_tree_data *mtd)
{
  struct mode_tree_item *mti;
  unsigned int mti_idx = 0;
  struct mode_tree_item *last;
  struct mode_tree_item *next;
  unsigned int next_idx = 0;
  if (mtd->search == 0)
  {
    return 0;
  }
  mti_idx = (last = mtd->line_list[mtd->current].item);
  for (;;)
  {
    if (!((&mti->children)->tqh_first == 0))
    {
      mti_idx = (&mti_idx->children)->tqh_first;
    }
    else
      if ((next_idx = mti->entry.tqe_next) != 0)
    {
      mti_idx = &next[next_idx];
    }
    else
    {
      for (;;)
      {
        mti_idx = mti_idx->parent;
        if ((&mti[mti_idx]) == 0)
        {
          break;
        }
        if ((next_idx = mti->entry.tqe_next) != 0)
        {
          mti_idx = &next[next_idx];
          break;
        }
      }

    }
    if ((&mti[mti_idx]) == 0)
    {
      mti_idx = (&mtd->children)->tqh_first;
    }
    if ((&mti[mti_idx]) == last)
    {
      break;
    }
    if (mtd->searchcb == 0)
    {
      if (strstr(mti->name, mtd->search) != 0)
      {
        return mti;
      }
      continue;
    }
    if (mtd->searchcb(mtd->modedata, mti->itemdata, mtd->search))
    {
      return mti;
    }
  }

  return 0;
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


static int mode_tree_search_callback(struct client *c, void *data, const char *s, int done)
{
  struct mode_tree_data *mtd = data;
  if (mtd->dead)
  {
    return 0;
  }
  free(mtd->search);
  if ((s == 0) || ((*s) == '\0'))
  {
    mtd->search = 0;
    return 0;
  }
  mtd->search = xstrdup(s);
  mode_tree_search_set(mtd);
  return 0;
}


/*** DEPENDENCIES:
static void mode_tree_search_set(struct mode_tree_data *mtd)
{
  struct mode_tree_item *mti;
  unsigned int mti_idx = 0;
  struct mode_tree_item *loop;
  unsigned int loop_idx = 0;
  uint64_t tag;
  mti_idx = mode_tree_search_for(mtd);
  if ((&mti[mti_idx]) == 0)
  {
    return;
  }
  tag = mti->tag;
  loop_idx = mti->parent;
  while ((&loop[loop_idx]) != 0)
  {
    loop->expanded = 1;
    loop_idx = loop_idx->parent;
  }

  mode_tree_build(mtd);
  mode_tree_set_current(mtd, tag);
  mode_tree_draw(mtd);
  mtd->wp->flags |= 0x1;
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
***/


int helper_mode_tree_key_1(struct mode_tree_data * const mtd, key_code * const key, struct mouse_event * const m, u_int * const xp, u_int * const yp, u_int x, u_int y)
{
  if (cmd_mouse_at(mtd->wp, m, &x, &y, 0) != 0)
  {
    *key = 0xffff00000000ULL;
    return 0;
  }
  if (xp != 0)
  {
    *xp = x;
  }
  if (yp != 0)
  {
    *yp = y;
  }
  if ((x > mtd->width) || (y > mtd->height))
  {
    if (!mtd->preview)
    {
      *key = 0xffff00000000ULL;
    }
    return 0;
  }
  if ((mtd->offset + y) < mtd->line_size)
  {
    if (((*key) == KEYC_MOUSEDOWN1_PANE) || ((*key) == KEYC_DOUBLECLICK1_PANE))
    {
      mtd->current = mtd->offset + y;
    }
    if ((*key) == KEYC_DOUBLECLICK1_PANE)
    {
      *key = '\r';
    }
    else
      *key = 0xffff00000000ULL;
  }
  else
    *key = 0xffff00000000ULL;
  return 0;
}


/*** DEPENDENCIES:
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
typedef unsigned long long key_code
----------------------------
int cmd_mouse_at(struct window_pane *wp, struct mouse_event *m, u_int *xp, u_int *yp, int last)
{
  u_int x;
  u_int y;
  if (last)
  {
    x = m->lx;
    y = m->ly;
  }
  else
  {
    x = m->x;
    y = m->y;
  }
  if ((m->statusat == 0) && (y > 0))
  {
    y -= 1;
  }
  else
    if ((m->statusat > 0) && (y >= ((u_int) m->statusat)))
  {
    y = m->statusat - 1;
  }
  if ((x < wp->xoff) || (x >= (wp->xoff + wp->sx)))
  {
    return -1;
  }
  if ((y < wp->yoff) || (y >= (wp->yoff + wp->sy)))
  {
    return -1;
  }
  if (xp != 0)
  {
    *xp = x - wp->xoff;
  }
  if (yp != 0)
  {
    *yp = y - wp->yoff;
  }
  return 0;
}


----------------------------
***/


void mode_tree_resize(struct mode_tree_data *mtd, u_int sx, u_int sy)
{
  struct screen *s = &mtd->screen;
  screen_resize(s, sx, sy, 0);
  mode_tree_build(mtd);
  mode_tree_draw(mtd);
  mtd->wp->flags |= 0x1;
}


/*** DEPENDENCIES:
void screen_resize(struct screen *s, u_int sx, u_int sy, int reflow)
{
  if (sx < 1)
  {
    sx = 1;
  }
  if (sy < 1)
  {
    sy = 1;
  }
  if (sx != s->grid->sx)
  {
    screen_resize_x(s, sx);
    screen_reset_tabs(s);
  }
  else
    reflow = 0;
  if (sy != s->grid->sy)
  {
    screen_resize_y(s, sy);
  }
  if (reflow)
  {
    screen_reflow(s, sx);
  }
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
None
----------------------------
***/


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


/*** DEPENDENCIES:
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
None
----------------------------
typedef unsigned long long key_code
----------------------------
typedef void (*mode_tree_each_cb)(void *, void *, struct client *, key_code)
----------------------------
None
----------------------------
***/


static int mode_tree_filter_callback(struct client *c, void *data, const char *s, int done)
{
  struct mode_tree_data *mtd = data;
  if (mtd->dead)
  {
    return 0;
  }
  if (mtd->filter != 0)
  {
    free(mtd->filter);
  }
  if ((s == 0) || ((*s) == '\0'))
  {
    mtd->filter = 0;
  }
  else
    mtd->filter = xstrdup(s);
  mode_tree_build(mtd);
  mode_tree_draw(mtd);
  mtd->wp->flags |= 0x1;
  return 0;
}


/*** DEPENDENCIES:
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
***/


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


/*** DEPENDENCIES:
void server_unzoom_window(struct window *w)
{
  if (window_unzoom(w) == 0)
  {
    server_redraw_window(w);
  }
}


----------------------------
static void mode_tree_remove_ref(struct mode_tree_data *mtd)
{
  if ((--mtd->references) == 0)
  {
    free(mtd);
  }
}


----------------------------
None
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
static void mode_tree_clear_lines(struct mode_tree_data *mtd)
{
  free(mtd->line_list);
  mtd->line_list = 0;
  mtd->line_size = 0;
}


----------------------------
void screen_free(struct screen *s)
{
  free(s->tabs);
  free(s->title);
  free(s->ccolour);
  grid_destroy(s->grid);
  screen_free_titles(s);
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
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
static struct mode_tree_item *mode_tree_find_item(struct mode_tree_list *mtl, uint64_t tag)
{
  struct mode_tree_item *mti;
  unsigned int mti_idx = 0;
  struct mode_tree_item *child;
  unsigned int child_idx = 0;
  for (mti_idx = mtl->tqh_first; (&mti[mti_idx]) != 0; mti_idx = mti_idx->entry.tqe_next)
  {
    if (mti->tag == tag)
    {
      return mti;
    }
    child_idx = mode_tree_find_item(&mti->children, tag);
    if ((&child[child_idx]) != 0)
    {
      return child;
    }
  }

  return 0;
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


/*** DEPENDENCIES:
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
int window_zoom(struct window_pane *wp)
{
  struct window *w = wp->window;
  struct window_pane *wp1;
  unsigned int wp1_idx = 0;
  if (w->flags & 0x1000)
  {
    return -1;
  }
  if (!window_pane_visible(wp))
  {
    return -1;
  }
  if (window_count_panes(w) == 1)
  {
    return -1;
  }
  if (w->active != wp)
  {
    window_set_active_pane(w, wp);
  }
  for (wp1_idx = (&w->panes)->tqh_first; (&wp1[wp1_idx]) != 0; wp1_idx = wp1_idx->entry.tqe_next)
  {
    wp1->saved_layout_cell = wp1->layout_cell;
    wp1->layout_cell = 0;
  }

  w->saved_layout_root = w->layout_root;
  layout_init(w, wp);
  w->flags |= 0x1000;
  notify_window("window-layout-changed", w);
  return 0;
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


/*** DEPENDENCIES:
struct cmd_list *cmd_string_parse(const char *s, const char *file, u_int line, char **cause)
{
  struct cmd_list *cmdlist = 0;
  unsigned int cmdlist_idx = 0;
  int argc;
  char **argv;
  *cause = 0;
  if (cmd_string_split(s, &argc, &argv) != 0)
  {
    xasprintf(cause, "invalid or unknown command: %s", s);
    return 0;
  }
  if (argc != 0)
  {
    cmdlist_idx = cmd_list_parse(argc, argv, file, line, cause);
    if ((&cmdlist[cmdlist_idx]) == 0)
    {
      cmd_free_argv(argc, argv);
      return 0;
    }
  }
  cmd_free_argv(argc, argv);
  return cmdlist;
}


----------------------------
struct cmdq_item *cmdq_get_command(struct cmd_list *cmdlist, struct cmd_find_state *current, struct mouse_event *m, int flags)
{
  struct cmdq_item *item;
  unsigned int item_idx = 0;
  struct cmdq_item *first = 0;
  unsigned int first_idx = 0;
  struct cmdq_item *last = 0;
  unsigned int last_idx = 0;
  struct cmd *cmd;
  unsigned int cmd_idx = 0;
  u_int group = cmdq_next_group();
  char *tmp;
  struct cmdq_shared *shared;
  unsigned int shared_idx = 0;
  shared_idx = xcalloc(1, sizeof(*shared_idx));
  if (current != 0)
  {
    cmd_find_copy_state(&shared->current, current);
  }
  else
    cmd_find_clear_state(&shared->current, 0);
  if (m != 0)
  {
    memcpy(&shared->mouse, m, sizeof(shared->mouse));
  }
  for (cmd_idx = (&cmdlist->list)->tqh_first; (&cmd[cmd_idx]) != 0; cmd_idx = cmd_idx->qentry.tqe_next)
  {
    helper_cmdq_get_command_1(&flags, &item_idx, &first_idx, &last_idx, &group, cmdlist, item, first, last, cmd, cmd_idx, tmp, shared, shared_idx);
  }

  return first;
}


----------------------------
void status_message_set(struct client *c, const char *fmt, ...)
{
  struct timeval tv;
  va_list ap;
  int delay;
  status_message_clear(c);
  if (c->status.old_status == 0)
  {
    c->status.old_status = xmalloc(sizeof(*c->status.old_status));
    memcpy(c->status.old_status, &c->status.status, sizeof(*c->status.old_status));
    screen_init(&c->status.status, c->tty.sx, 1, 0);
  }
  __builtin_va_start(ap);
  xvasprintf(&c->message_string, fmt, ap);
  ;
  server_client_add_message(c, "%s", c->message_string);
  delay = options_get_number(c->session->options, "display-time");
  if (delay > 0)
  {
    tv.tv_sec = delay / 1000;
    tv.tv_usec = (delay % 1000) * 1000L;
    if (event_initialized(&c->message_timer))
    {
      evtimer_del(&c->message_timer);
    }
    evtimer_set(&c->message_timer, status_message_callback, c);
    evtimer_add(&c->message_timer, &tv);
  }
  c->tty.flags |= 0x1 | 0x2;
  c->flags |= 0x10;
}


----------------------------
void cmd_list_free(struct cmd_list *cmdlist)
{
  struct cmd *cmd;
  unsigned int cmd_idx = 0;
  struct cmd *cmd1;
  unsigned int cmd1_idx = 0;
  if ((--cmdlist->references) != 0)
  {
    return;
  }
  for (cmd_idx = (&cmdlist->list)->tqh_first; ((&cmd[cmd_idx]) != 0) && ((cmd1_idx = cmd->qentry.tqe_next, 1)); cmd_idx = &cmd1[cmd1_idx])
  {
    do
    {
      if (cmd->qentry.tqe_next != 0)
      {
        cmd->qentry.tqe_next->qentry.tqe_prev = cmd->qentry.tqe_prev;
      }
      else
        (&cmdlist->list)->tqh_last = cmd->qentry.tqe_prev;
      *cmd->qentry.tqe_prev = cmd->qentry.tqe_next;
      ;
      ;
    }
    while (0);
    args_free(cmd->args);
    free(cmd->file);
    free(cmd);
  }

  free(cmdlist);
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
char *cmd_template_replace(const char *template, const char *s, int idx)
{
  char ch;
  char *buf;
  unsigned int buf_idx = 0;
  const char *ptr;
  unsigned int ptr_idx = 0;
  const char *cp;
  unsigned int cp_idx = 0;
  const char quote[] = "\"\\$";
  int replaced;
  int quoted;
  size_t len;
  if (strchr(template, '%') == 0)
  {
    return xstrdup(template);
  }
  buf_idx = xmalloc(1);
  buf[buf_idx] = '\0';
  len = 0;
  replaced = 0;
  ptr_idx = template;
  while (ptr[ptr_idx] != '\0')
  {
    helper_cmd_template_replace_1(&ch, &buf_idx, &ptr_idx, &cp_idx, &replaced, &quoted, &len, s, idx, buf, ptr, cp, quote);
  }

  return buf;
}


----------------------------
None
----------------------------
***/


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


/*** DEPENDENCIES:
None
----------------------------
void screen_init(struct screen *s, u_int sx, u_int sy, u_int hlimit)
{
  s->grid = grid_create(sx, sy, hlimit);
  s->title = xstrdup("");
  s->titles = 0;
  s->cstyle = 0;
  s->ccolour = xstrdup("");
  s->tabs = 0;
  screen_reinit(s);
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
typedef void (*mode_tree_build_cb)(void *, u_int, uint64_t *, const char *)
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
typedef void (*mode_tree_draw_cb)(void *, void *, struct screen_write_ctx *, u_int, u_int)
----------------------------
None
----------------------------
typedef int (*mode_tree_search_cb)(void *, void *, const char *)
----------------------------
int args_has(struct args *args, u_char ch)
{
  return args_find(args, ch) != 0;
}


----------------------------
None
----------------------------
***/


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
typedef unsigned long long key_code
----------------------------
static void mode_tree_search_free(void *data)
{
  mode_tree_remove_ref(data);
}


----------------------------
static void mode_tree_filter_free(void *data)
{
  mode_tree_remove_ref(data);
}


----------------------------
static void mode_tree_search_set(struct mode_tree_data *mtd)
{
  struct mode_tree_item *mti;
  unsigned int mti_idx = 0;
  struct mode_tree_item *loop;
  unsigned int loop_idx = 0;
  uint64_t tag;
  mti_idx = mode_tree_search_for(mtd);
  if ((&mti[mti_idx]) == 0)
  {
    return;
  }
  tag = mti->tag;
  loop_idx = mti->parent;
  while ((&loop[loop_idx]) != 0)
  {
    loop->expanded = 1;
    loop_idx = loop_idx->parent;
  }

  mode_tree_build(mtd);
  mode_tree_set_current(mtd, tag);
  mode_tree_draw(mtd);
  mtd->wp->flags |= 0x1;
}


----------------------------
static int mode_tree_search_callback(struct client *c, void *data, const char *s, int done)
{
  struct mode_tree_data *mtd = data;
  if (mtd->dead)
  {
    return 0;
  }
  free(mtd->search);
  if ((s == 0) || ((*s) == '\0'))
  {
    mtd->search = 0;
    return 0;
  }
  mtd->search = xstrdup(s);
  mode_tree_search_set(mtd);
  return 0;
}


----------------------------
struct mode_tree_line
{
  struct mode_tree_item *item;
  u_int depth;
  int last;
  int flat;
}
----------------------------
void mode_tree_up(struct mode_tree_data *mtd, int wrap)
{
  if (mtd->current == 0)
  {
    if (wrap)
    {
      mtd->current = mtd->line_size - 1;
      if (mtd->line_size >= mtd->height)
      {
        mtd->offset = mtd->line_size - mtd->height;
      }
    }
  }
  else
  {
    mtd->current -= 1;
    if (mtd->current < mtd->offset)
    {
      mtd->offset -= 1;
    }
  }
}


----------------------------
static void mode_tree_clear_tagged(struct mode_tree_list *mtl)
{
  struct mode_tree_item *mti;
  unsigned int mti_idx = 0;
  for (mti_idx = mtl->tqh_first; (&mti[mti_idx]) != 0; mti_idx = mti_idx->entry.tqe_next)
  {
    mti->tagged = 0;
    mode_tree_clear_tagged(&mti->children);
  }

}


----------------------------
None
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
int helper_mode_tree_key_1(struct mode_tree_data * const mtd, key_code * const key, struct mouse_event * const m, u_int * const xp, u_int * const yp, u_int x, u_int y)
{
  if (cmd_mouse_at(mtd->wp, m, &x, &y, 0) != 0)
  {
    *key = 0xffff00000000ULL;
    return 0;
  }
  if (xp != 0)
  {
    *xp = x;
  }
  if (yp != 0)
  {
    *yp = y;
  }
  if ((x > mtd->width) || (y > mtd->height))
  {
    if (!mtd->preview)
    {
      *key = 0xffff00000000ULL;
    }
    return 0;
  }
  if ((mtd->offset + y) < mtd->line_size)
  {
    if (((*key) == KEYC_MOUSEDOWN1_PANE) || ((*key) == KEYC_DOUBLECLICK1_PANE))
    {
      mtd->current = mtd->offset + y;
    }
    if ((*key) == KEYC_DOUBLECLICK1_PANE)
    {
      *key = '\r';
    }
    else
      *key = 0xffff00000000ULL;
  }
  else
    *key = 0xffff00000000ULL;
  return 0;
}


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
static int mode_tree_filter_callback(struct client *c, void *data, const char *s, int done)
{
  struct mode_tree_data *mtd = data;
  if (mtd->dead)
  {
    return 0;
  }
  if (mtd->filter != 0)
  {
    free(mtd->filter);
  }
  if ((s == 0) || ((*s) == '\0'))
  {
    mtd->filter = 0;
  }
  else
    mtd->filter = xstrdup(s);
  mode_tree_build(mtd);
  mode_tree_draw(mtd);
  mtd->wp->flags |= 0x1;
  return 0;
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
static void mode_tree_check_selected(struct mode_tree_data *mtd)
{
  if (mtd->current > (mtd->height - 1))
  {
    mtd->offset = (mtd->current - mtd->height) + 1;
  }
}


----------------------------
None
----------------------------
***/


