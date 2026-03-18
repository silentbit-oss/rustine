// element in merge of:  parse_block,parse_list,parse_blockquote,parse_listitem,parse_blockspoiler
static void parse_block(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  size_t beg;
  size_t end;
  size_t i;
  uint8_t *txt_data;
  unsigned int txt_data_idx = 0;
  beg = 0;
  if ((rndr->work_bufs[1].size + rndr->work_bufs[0].size) > rndr->max_nesting)
  {
    return;
  }
  while (beg < size)
  {
    txt_data_idx = data + beg;
    end = size - beg;
    if (is_atxheader(rndr, txt_data, end))
    {
      beg += parse_atxheader(ob, rndr, txt_data, end);
    }
    else
      if (((data[beg] == '<') && rndr->cb.blockhtml) && ((i = parse_htmlblock(ob, rndr, txt_data, end, 1)) != 0))
    {
      beg += i;
    }
    else
      if ((i = is_empty(txt_data, end)) != 0)
    {
      beg += i;
    }
    else
      if (is_hrule(txt_data, end))
    {
      if (rndr->cb.hrule)
      {
        rndr->cb.hrule(ob, rndr->opaque);
      }
      while ((beg < size) && (data[beg] != '\n'))
      {
        beg += 1;
      }

      beg += 1;
    }
    else
      if (((rndr->ext_flags & MKDEXT_FENCED_CODE) != 0) && ((i = parse_fencedcode(ob, rndr, txt_data, end)) != 0))
    {
      beg += i;
    }
    else
      if (((rndr->ext_flags & MKDEXT_TABLES) != 0) && ((i = parse_table(ob, rndr, txt_data, end)) != 0))
    {
      beg += i;
    }
    else
      if (prefix_quote(txt_data, end))
    {
      beg += parse_blockquote(ob, rndr, txt_data, end);
    }
    else
      if (prefix_blockspoiler(txt_data, end))
    {
      beg += parse_blockspoiler(ob, rndr, txt_data, end);
    }
    else
      if (prefix_code(txt_data, end))
    {
      beg += parse_blockcode(ob, rndr, txt_data, end);
    }
    else
      if (prefix_uli(txt_data, end))
    {
      beg += parse_list(ob, rndr, txt_data, end, 0);
    }
    else
      if (prefix_oli(txt_data, end))
    {
      beg += parse_list(ob, rndr, txt_data, end, 1);
    }
    else
      beg += parse_paragraph(ob, rndr, txt_data, end);
  }

}


/*** DEPENDENCIES:
static size_t prefix_oli(uint8_t *data, size_t size)
{
  size_t i = 0;
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if (((i >= size) || (data[i] < '0')) || (data[i] > '9'))
  {
    return 0;
  }
  while (((i < size) && (data[i] >= '0')) && (data[i] <= '9'))
  {
    i += 1;
  }

  if ((((i + 1) >= size) || (data[i] != '.')) || (data[i + 1] != ' '))
  {
    return 0;
  }
  if (is_next_headerline(data + i, size - i))
  {
    return 0;
  }
  return i + 2;
}


----------------------------
struct sd_markdown
{
  struct sd_callbacks cb;
  void *opaque;
  struct link_ref *refs[8];
  uint8_t active_char[256];
  struct stack work_bufs[2];
  unsigned int ext_flags;
  size_t max_nesting;
  size_t max_table_cols;
  int in_link_body;
}
----------------------------
static size_t parse_fencedcode(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  size_t beg;
  size_t end;
  struct buf *work = 0;
  unsigned int work_idx = 0;
  struct buf lang = {0, 0, 0, 0};
  beg = is_codefence(data, size, &lang);
  if (beg == 0)
  {
    return 0;
  }
  work_idx = rndr_newbuf(rndr, 0);
  while (beg < size)
  {
    size_t fence_end;
    struct buf fence_trail = {0, 0, 0, 0};
    fence_end = is_codefence(data + beg, size - beg, &fence_trail);
    if ((fence_end != 0) && (fence_trail.size == 0))
    {
      beg += fence_end;
      break;
    }
    for (end = beg + 1; (end < size) && (data[end - 1] != '\n'); end += 1)
    {
      ;
    }

    if (beg < end)
    {
      if (is_empty(data + beg, end - beg))
      {
        bufputc(work, '\n');
      }
      else
        bufput(work, data + beg, end - beg);
    }
    beg = end;
  }

  if (work->size && (work->data[work->size - 1] != '\n'))
  {
    bufputc(work, '\n');
  }
  if (rndr->cb.blockcode)
  {
    rndr->cb.blockcode(ob, work, (lang.size) ? (&lang) : (0), rndr->opaque);
  }
  rndr_popbuf(rndr, 0);
  return beg;
}


----------------------------
static size_t parse_table(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  size_t i;
  struct buf *header_work = 0;
  unsigned int header_work_idx = 0;
  struct buf *body_work = 0;
  unsigned int body_work_idx = 0;
  size_t columns;
  int *col_data = 0;
  header_work_idx = rndr_newbuf(rndr, 1);
  body_work_idx = rndr_newbuf(rndr, 0);
  i = parse_table_header(header_work, rndr, data, size, &columns, &col_data);
  if (i > 0)
  {
    while (i < size)
    {
      size_t row_start;
      int pipes = 0;
      row_start = i;
      while ((i < size) && (data[i] != '\n'))
      {
        if (data[i++] == '|')
        {
          pipes += 1;
        }
      }

      if ((pipes == 0) || (i == size))
      {
        i = row_start;
        break;
      }
      parse_table_row(body_work, rndr, data + row_start, i - row_start, columns, col_data, 0);
      i += 1;
    }

    if (rndr->cb.table)
    {
      rndr->cb.table(ob, header_work, body_work, rndr->opaque);
    }
  }
  free(col_data);
  rndr_popbuf(rndr, 1);
  rndr_popbuf(rndr, 0);
  return i;
}


----------------------------
struct buf
{
  uint8_t *data;
  size_t size;
  size_t asize;
  size_t unit;
}
----------------------------
static size_t parse_htmlblock(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size, int do_render)
{
  size_t i;
  size_t j = 0;
  size_t tag_end;
  const char *curtag = 0;
  unsigned int curtag_idx = 0;
  struct buf work = {data, 0, 0, 0};
  if ((size < 2) || (data[0] != '<'))
  {
    return 0;
  }
  i = 1;
  while (((i < size) && (data[i] != '>')) && (data[i] != ' '))
  {
    i += 1;
  }

  if (i < size)
  {
    curtag_idx = find_block_tag(((char *) data) + 1, ((int) i) - 1);
  }
  if (!(&curtag[curtag_idx]))
  {
    helper_parse_htmlblock_1(&size, &i, &j, &work, ob, rndr, data, do_render);
  }
  tag_end = htmlblock_end(curtag, rndr, data, size, 1);
  if (((!tag_end) && (strcmp(curtag, "ins") != 0)) && (strcmp(curtag, "del") != 0))
  {
    tag_end = htmlblock_end(curtag, rndr, data, size, 0);
  }
  if (!tag_end)
  {
    return 0;
  }
  work.size = tag_end;
  if (do_render && rndr->cb.blockhtml)
  {
    rndr->cb.blockhtml(ob, &work, rndr->opaque);
  }
  return tag_end;
}


----------------------------
static int is_hrule(uint8_t *data, size_t size)
{
  size_t i = 0;
  size_t n = 0;
  uint8_t c;
  if (size < 3)
  {
    return 0;
  }
  if (data[0] == ' ')
  {
    i += 1;
    if (data[1] == ' ')
    {
      i += 1;
      if (data[2] == ' ')
      {
        i += 1;
      }
    }
  }
  if (((i + 2) >= size) || (((data[i] != '*') && (data[i] != '-')) && (data[i] != '_')))
  {
    return 0;
  }
  c = data[i];
  while ((i < size) && (data[i] != '\n'))
  {
    if (data[i] == c)
    {
      n += 1;
    }
    else
      if (data[i] != ' ')
    {
      return 0;
    }
    i += 1;
  }

  return n >= 3;
}


----------------------------
static size_t prefix_quote(uint8_t *data, size_t size)
{
  size_t i = 0;
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if (((i < size) && (data[i] == '>')) && (((i + 1) < size) && (data[i + 1] != '!')))
  {
    if (((i + 1) < size) && (data[i + 1] == ' '))
    {
      return i + 2;
    }
    return i + 1;
  }
  return 0;
}


----------------------------
static size_t parse_blockcode(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  size_t beg;
  size_t end;
  size_t pre;
  struct buf *work = 0;
  unsigned int work_idx = 0;
  work_idx = rndr_newbuf(rndr, 0);
  beg = 0;
  while (beg < size)
  {
    for (end = beg + 1; (end < size) && (data[end - 1] != '\n'); end += 1)
    {
    }

    ;
    pre = prefix_code(data + beg, end - beg);
    if (pre)
    {
      beg += pre;
    }
    else
      if (!is_empty(data + beg, end - beg))
    {
      break;
    }
    if (beg < end)
    {
      if (is_empty(data + beg, end - beg))
      {
        bufputc(work, '\n');
      }
      else
        bufput(work, data + beg, end - beg);
    }
    beg = end;
  }

  while (work->size && (work->data[work->size - 1] == '\n'))
  {
    work->size -= 1;
  }

  bufputc(work, '\n');
  if (rndr->cb.blockcode)
  {
    rndr->cb.blockcode(ob, work, 0, rndr->opaque);
  }
  rndr_popbuf(rndr, 0);
  return beg;
}


----------------------------
static size_t prefix_blockspoiler(uint8_t *data, size_t size)
{
  size_t i = 0;
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((((i + 1) < size) && (data[i] == '>')) && (data[i + 1] == '!'))
  {
    size_t spoilerspan = find_emph_char((data + i) + 1, (size - i) - 1, '<');
    if ((((i + spoilerspan) < size) && (spoilerspan > 0)) && (data[i + spoilerspan] == '!'))
    {
      return 0;
    }
    if (((i + 2) < size) && (data[i + 2] == ' '))
    {
      return i + 3;
    }
    return i + 2;
  }
  return 0;
}


----------------------------
static size_t is_empty(uint8_t *data, size_t size)
{
  size_t i;
  for (i = 0; (i < size) && (data[i] != '\n'); i += 1)
  {
    if (data[i] != ' ')
    {
      return 0;
    }
  }

  return i + 1;
}


----------------------------
static size_t parse_atxheader(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  size_t level = 0;
  size_t i;
  size_t end;
  size_t skip;
  while (((level < size) && (level < 6)) && (data[level] == '#'))
  {
    level += 1;
  }

  for (i = level; (i < size) && (data[i] == ' '); i += 1)
  {
    ;
  }

  for (end = i; (end < size) && (data[end] != '\n'); end += 1)
  {
    ;
  }

  skip = end;
  while (end && (data[end - 1] == '#'))
  {
    end -= 1;
  }

  while (end && (data[end - 1] == ' '))
  {
    end -= 1;
  }

  if (end > i)
  {
    struct buf *work = rndr_newbuf(rndr, 1);
    parse_inline(work, rndr, data + i, end - i);
    if (rndr->cb.header)
    {
      rndr->cb.header(ob, work, (int) level, rndr->opaque);
    }
    rndr_popbuf(rndr, 1);
  }
  return skip;
}


----------------------------
static size_t prefix_uli(uint8_t *data, size_t size)
{
  size_t i = 0;
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((((i + 1) >= size) || (((data[i] != '*') && (data[i] != '+')) && (data[i] != '-'))) || (data[i + 1] != ' '))
  {
    return 0;
  }
  if (is_next_headerline(data + i, size - i))
  {
    return 0;
  }
  return i + 2;
}


----------------------------
static size_t parse_paragraph(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  size_t i = 0;
  size_t end = 0;
  int level = 0;
  struct buf work = {data, 0, 0, 0};
  while (i < size)
  {
    helper_parse_paragraph_1(&i, &end, &level, ob, rndr, data, size);
  }

  work.size = i;
  while (work.size && (data[work.size - 1] == '\n'))
  {
    work.size -= 1;
  }

  if (!level)
  {
    struct buf *tmp = rndr_newbuf(rndr, 0);
    parse_inline(tmp, rndr, work.data, work.size);
    if (rndr->cb.paragraph)
    {
      rndr->cb.paragraph(ob, tmp, rndr->opaque);
    }
    rndr_popbuf(rndr, 0);
  }
  else
  {
    helper_parse_paragraph_2(&i, &work, ob, rndr, data, level);
  }
  return end;
}


----------------------------
static int is_atxheader(struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  if (data[0] != '#')
  {
    return 0;
  }
  if (rndr->ext_flags & MKDEXT_SPACE_HEADERS)
  {
    size_t level = 0;
    while (((level < size) && (level < 6)) && (data[level] == '#'))
    {
      level += 1;
    }

    if ((level < size) && (data[level] != ' '))
    {
      return 0;
    }
  }
  return 1;
}


----------------------------
static size_t prefix_code(uint8_t *data, size_t size)
{
  if (((((size > 3) && (data[0] == ' ')) && (data[1] == ' ')) && (data[2] == ' ')) && (data[3] == ' '))
  {
    return 4;
  }
  return 0;
}


----------------------------
None
----------------------------
***/


// element in merge of:  parse_block,parse_list,parse_blockquote,parse_listitem,parse_blockspoiler
static size_t parse_list(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size, int flags)
{
  struct buf *work = 0;
  unsigned int work_idx = 0;
  size_t i = 0;
  size_t j;
  work_idx = rndr_newbuf(rndr, 0);
  while (i < size)
  {
    j = parse_listitem(work, rndr, data + i, size - i, &flags);
    i += j;
    if ((!j) || (flags & 8))
    {
      break;
    }
  }

  if (rndr->cb.list)
  {
    rndr->cb.list(ob, work, flags, rndr->opaque);
  }
  rndr_popbuf(rndr, 0);
  return i;
}


/*** DEPENDENCIES:
struct sd_markdown
{
  struct sd_callbacks cb;
  void *opaque;
  struct link_ref *refs[8];
  uint8_t active_char[256];
  struct stack work_bufs[2];
  unsigned int ext_flags;
  size_t max_nesting;
  size_t max_table_cols;
  int in_link_body;
}
----------------------------
inline static void rndr_popbuf(struct sd_markdown *rndr, int type)
{
  rndr->work_bufs[type].size -= 1;
}


----------------------------
struct buf
{
  uint8_t *data;
  size_t size;
  size_t asize;
  size_t unit;
}
----------------------------
inline static struct buf *rndr_newbuf(struct sd_markdown *rndr, int type)
{
  static const size_t buf_size[2] = {256, 64};
  struct buf *work = 0;
  unsigned int work_idx = 0;
  struct stack *pool = &rndr->work_bufs[type];
  if ((pool->size < pool->asize) && (pool->item[pool->size] != 0))
  {
    work_idx = pool->item[pool->size++];
    work->size = 0;
  }
  else
  {
    work_idx = bufnew(buf_size[type]);
    stack_push(pool, work);
  }
  return work;
}


----------------------------
None
----------------------------
***/


// element in merge of:  parse_block,parse_list,parse_blockquote,parse_listitem,parse_blockspoiler
static size_t parse_blockquote(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  size_t beg;
  size_t end = 0;
  size_t pre;
  size_t work_size = 0;
  uint8_t *work_data = 0;
  unsigned int work_data_idx = 0;
  struct buf *out = 0;
  unsigned int out_idx = 0;
  out_idx = rndr_newbuf(rndr, 0);
  beg = 0;
  while (beg < size)
  {
    for (end = beg + 1; (end < size) && (data[end - 1] != '\n'); end += 1)
    {
      ;
    }

    pre = prefix_quote(data + beg, end - beg);
    if (pre)
    {
      beg += pre;
    }
    else
      if (is_empty(data + beg, end - beg) && ((end >= size) || ((prefix_quote(data + end, size - end) == 0) && (!is_empty(data + end, size - end)))))
    {
      break;
    }
    if (beg < end)
    {
      if (!(&work_data[work_data_idx]))
      {
        work_data_idx = data + beg;
      }
      else
        if ((data + beg) != ((&work_data[work_data_idx]) + work_size))
      {
        memmove((&work_data[work_data_idx]) + work_size, data + beg, end - beg);
      }
      work_size += end - beg;
    }
    beg = end;
  }

  parse_block(out, rndr, work_data, work_size);
  if (rndr->cb.blockquote)
  {
    rndr->cb.blockquote(ob, out, rndr->opaque);
  }
  rndr_popbuf(rndr, 0);
  return end;
}


/*** DEPENDENCIES:
struct sd_markdown
{
  struct sd_callbacks cb;
  void *opaque;
  struct link_ref *refs[8];
  uint8_t active_char[256];
  struct stack work_bufs[2];
  unsigned int ext_flags;
  size_t max_nesting;
  size_t max_table_cols;
  int in_link_body;
}
----------------------------
inline static void rndr_popbuf(struct sd_markdown *rndr, int type)
{
  rndr->work_bufs[type].size -= 1;
}


----------------------------
static size_t prefix_quote(uint8_t *data, size_t size)
{
  size_t i = 0;
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if (((i < size) && (data[i] == '>')) && (((i + 1) < size) && (data[i + 1] != '!')))
  {
    if (((i + 1) < size) && (data[i + 1] == ' '))
    {
      return i + 2;
    }
    return i + 1;
  }
  return 0;
}


----------------------------
inline static struct buf *rndr_newbuf(struct sd_markdown *rndr, int type)
{
  static const size_t buf_size[2] = {256, 64};
  struct buf *work = 0;
  unsigned int work_idx = 0;
  struct stack *pool = &rndr->work_bufs[type];
  if ((pool->size < pool->asize) && (pool->item[pool->size] != 0))
  {
    work_idx = pool->item[pool->size++];
    work->size = 0;
  }
  else
  {
    work_idx = bufnew(buf_size[type]);
    stack_push(pool, work);
  }
  return work;
}


----------------------------
static size_t is_empty(uint8_t *data, size_t size)
{
  size_t i;
  for (i = 0; (i < size) && (data[i] != '\n'); i += 1)
  {
    if (data[i] != ' ')
    {
      return 0;
    }
  }

  return i + 1;
}


----------------------------
struct buf
{
  uint8_t *data;
  size_t size;
  size_t asize;
  size_t unit;
}
----------------------------
None
----------------------------
***/


// element in merge of:  parse_block,parse_list,parse_blockquote,parse_listitem,parse_blockspoiler
static size_t parse_listitem(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size, int *flags)
{
  struct buf *work = 0;
  unsigned int work_idx = 0;
  struct buf *inter = 0;
  unsigned int inter_idx = 0;
  size_t beg = 0;
  size_t end;
  size_t pre;
  size_t sublist = 0;
  size_t orgpre = 0;
  size_t i;
  int in_empty = 0;
  int has_inside_empty = 0;
  int in_fence = 0;
  while (((orgpre < 3) && (orgpre < size)) && (data[orgpre] == ' '))
  {
    orgpre += 1;
  }

  beg = prefix_uli(data, size);
  if (!beg)
  {
    beg = prefix_oli(data, size);
  }
  if (!beg)
  {
    return 0;
  }
  end = beg;
  while ((end < size) && (data[end - 1] != '\n'))
  {
    end += 1;
  }

  work_idx = rndr_newbuf(rndr, 1);
  inter_idx = rndr_newbuf(rndr, 1);
  bufput(work, data + beg, end - beg);
  beg = end;
  while (beg < size)
  {
    helper_parse_listitem_1(&beg, &end, &pre, &sublist, &i, &in_empty, &has_inside_empty, &in_fence, rndr, data, size, flags, work, orgpre);
  }

  if (has_inside_empty)
  {
    *flags |= 2;
  }
  if ((*flags) & 2)
  {
    if (sublist && (sublist < work->size))
    {
      parse_block(inter, rndr, work->data, sublist);
      parse_block(inter, rndr, work->data + sublist, work->size - sublist);
    }
    else
      parse_block(inter, rndr, work->data, work->size);
  }
  else
  {
    if (sublist && (sublist < work->size))
    {
      parse_inline(inter, rndr, work->data, sublist);
      parse_block(inter, rndr, work->data + sublist, work->size - sublist);
    }
    else
      parse_inline(inter, rndr, work->data, work->size);
  }
  if (rndr->cb.listitem)
  {
    rndr->cb.listitem(ob, inter, *flags, rndr->opaque);
  }
  rndr_popbuf(rndr, 1);
  rndr_popbuf(rndr, 1);
  return beg;
}


/*** DEPENDENCIES:
struct sd_markdown
{
  struct sd_callbacks cb;
  void *opaque;
  struct link_ref *refs[8];
  uint8_t active_char[256];
  struct stack work_bufs[2];
  unsigned int ext_flags;
  size_t max_nesting;
  size_t max_table_cols;
  int in_link_body;
}
----------------------------
inline static void rndr_popbuf(struct sd_markdown *rndr, int type)
{
  rndr->work_bufs[type].size -= 1;
}


----------------------------
void bufput(struct buf *buf, const void *data, size_t len)
{
  assert(buf && buf->unit);
  if (((buf->size + len) > buf->asize) && (bufgrow(buf, buf->size + len) < 0))
  {
    return;
  }
  memcpy(buf->data + buf->size, data, len);
  buf->size += len;
}


----------------------------
static size_t prefix_oli(uint8_t *data, size_t size)
{
  size_t i = 0;
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if (((i >= size) || (data[i] < '0')) || (data[i] > '9'))
  {
    return 0;
  }
  while (((i < size) && (data[i] >= '0')) && (data[i] <= '9'))
  {
    i += 1;
  }

  if ((((i + 1) >= size) || (data[i] != '.')) || (data[i + 1] != ' '))
  {
    return 0;
  }
  if (is_next_headerline(data + i, size - i))
  {
    return 0;
  }
  return i + 2;
}


----------------------------
static void parse_inline(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  size_t i = 0;
  size_t end = 0;
  size_t last_special = 0;
  uint8_t action = 0;
  struct buf work = {0, 0, 0, 0};
  if ((rndr->work_bufs[1].size + rndr->work_bufs[0].size) > rndr->max_nesting)
  {
    return;
  }
  while (i < size)
  {
    while ((end < size) && ((action = rndr->active_char[data[end]]) == 0))
    {
      end += 1;
    }

    if (rndr->cb.normal_text)
    {
      work.data = data + i;
      work.size = end - i;
      rndr->cb.normal_text(ob, &work, rndr->opaque);
    }
    else
      bufput(ob, data + i, end - i);
    if (end >= size)
    {
      break;
    }
    i = end;
    end = markdown_char_ptrs[(int) action](ob, rndr, data + i, i - last_special, i, size - i);
    if (!end)
    {
      end = i + 1;
    }
    else
    {
      i += end;
      last_special = (end = i);
    }
  }

}


----------------------------
inline static struct buf *rndr_newbuf(struct sd_markdown *rndr, int type)
{
  static const size_t buf_size[2] = {256, 64};
  struct buf *work = 0;
  unsigned int work_idx = 0;
  struct stack *pool = &rndr->work_bufs[type];
  if ((pool->size < pool->asize) && (pool->item[pool->size] != 0))
  {
    work_idx = pool->item[pool->size++];
    work->size = 0;
  }
  else
  {
    work_idx = bufnew(buf_size[type]);
    stack_push(pool, work);
  }
  return work;
}


----------------------------
static size_t prefix_uli(uint8_t *data, size_t size)
{
  size_t i = 0;
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((((i + 1) >= size) || (((data[i] != '*') && (data[i] != '+')) && (data[i] != '-'))) || (data[i + 1] != ' '))
  {
    return 0;
  }
  if (is_next_headerline(data + i, size - i))
  {
    return 0;
  }
  return i + 2;
}


----------------------------
void helper_parse_listitem_1(size_t * const beg_ref, size_t * const end_ref, size_t * const pre_ref, size_t * const sublist_ref, size_t * const i_ref, int * const in_empty_ref, int * const has_inside_empty_ref, int * const in_fence_ref, struct sd_markdown * const rndr, uint8_t * const data, size_t size, int * const flags, struct buf * const work, size_t orgpre)
{
  size_t beg = *beg_ref;
  size_t end = *end_ref;
  size_t pre = *pre_ref;
  size_t sublist = *sublist_ref;
  size_t i = *i_ref;
  int in_empty = *in_empty_ref;
  int has_inside_empty = *has_inside_empty_ref;
  int in_fence = *in_fence_ref;
  size_t has_next_uli = 0;
  size_t has_next_oli = 0;
  end += 1;
  while ((end < size) && (data[end - 1] != '\n'))
  {
    end += 1;
  }

  if (is_empty(data + beg, end - beg))
  {
    in_empty = 1;
    beg = end;
    continue;
  }
  i = 0;
  while (((i < 4) && ((beg + i) < end)) && (data[beg + i] == ' '))
  {
    i += 1;
  }

  pre = i;
  if (rndr->ext_flags & MKDEXT_FENCED_CODE)
  {
    if (is_codefence((data + beg) + i, (end - beg) - i, 0) != 0)
    {
      in_fence = !in_fence;
    }
  }
  if (!in_fence)
  {
    has_next_uli = prefix_uli((data + beg) + i, (end - beg) - i);
    has_next_oli = prefix_oli((data + beg) + i, (end - beg) - i);
  }
  if (in_empty && ((((*flags) & 1) && has_next_uli) || ((!((*flags) & 1)) && has_next_oli)))
  {
    *flags |= 8;
    break;
  }
  if ((has_next_uli && (!is_hrule((data + beg) + i, (end - beg) - i))) || has_next_oli)
  {
    if (in_empty)
    {
      has_inside_empty = 1;
    }
    if (pre == orgpre)
    {
      break;
    }
    if (!sublist)
    {
      sublist = work->size;
    }
  }
  else
    if (in_empty && (pre == 0))
  {
    *flags |= 8;
    break;
  }
  else
    if (in_empty)
  {
    bufputc(work, '\n');
    has_inside_empty = 1;
  }
  in_empty = 0;
  bufput(work, (data + beg) + i, (end - beg) - i);
  beg = end;
  *beg_ref = beg;
  *end_ref = end;
  *pre_ref = pre;
  *sublist_ref = sublist;
  *i_ref = i;
  *in_empty_ref = in_empty;
  *has_inside_empty_ref = has_inside_empty;
  *in_fence_ref = in_fence;
}


----------------------------
struct buf
{
  uint8_t *data;
  size_t size;
  size_t asize;
  size_t unit;
}
----------------------------
None
----------------------------
***/


// element in merge of:  parse_block,parse_list,parse_blockquote,parse_listitem,parse_blockspoiler
static size_t parse_blockspoiler(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  size_t beg;
  size_t end = 0;
  size_t pre;
  size_t work_size = 0;
  uint8_t *work_data = 0;
  unsigned int work_data_idx = 0;
  struct buf *out = 0;
  unsigned int out_idx = 0;
  out_idx = rndr_newbuf(rndr, 0);
  beg = 0;
  while (beg < size)
  {
    for (end = beg + 1; (end < size) && (data[end - 1] != '\n'); end += 1)
    {
      ;
    }

    pre = prefix_blockspoiler(data + beg, end - beg);
    if (pre)
    {
      beg += pre;
    }
    else
      if (is_empty(data + beg, end - beg) && ((end >= size) || ((prefix_blockspoiler(data + end, size - end) == 0) && (!is_empty(data + end, size - end)))))
    {
      break;
    }
    if (beg < end)
    {
      if (!(&work_data[work_data_idx]))
      {
        work_data_idx = data + beg;
      }
      else
        if ((data + beg) != ((&work_data[work_data_idx]) + work_size))
      {
        memmove((&work_data[work_data_idx]) + work_size, data + beg, end - beg);
      }
      work_size += end - beg;
    }
    beg = end;
  }

  parse_block(out, rndr, work_data, work_size);
  if (rndr->cb.blockspoiler)
  {
    rndr->cb.blockspoiler(ob, out, rndr->opaque);
  }
  rndr_popbuf(rndr, 0);
  return end;
}


/*** DEPENDENCIES:
struct sd_markdown
{
  struct sd_callbacks cb;
  void *opaque;
  struct link_ref *refs[8];
  uint8_t active_char[256];
  struct stack work_bufs[2];
  unsigned int ext_flags;
  size_t max_nesting;
  size_t max_table_cols;
  int in_link_body;
}
----------------------------
inline static void rndr_popbuf(struct sd_markdown *rndr, int type)
{
  rndr->work_bufs[type].size -= 1;
}


----------------------------
inline static struct buf *rndr_newbuf(struct sd_markdown *rndr, int type)
{
  static const size_t buf_size[2] = {256, 64};
  struct buf *work = 0;
  unsigned int work_idx = 0;
  struct stack *pool = &rndr->work_bufs[type];
  if ((pool->size < pool->asize) && (pool->item[pool->size] != 0))
  {
    work_idx = pool->item[pool->size++];
    work->size = 0;
  }
  else
  {
    work_idx = bufnew(buf_size[type]);
    stack_push(pool, work);
  }
  return work;
}


----------------------------
static size_t prefix_blockspoiler(uint8_t *data, size_t size)
{
  size_t i = 0;
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((((i + 1) < size) && (data[i] == '>')) && (data[i + 1] == '!'))
  {
    size_t spoilerspan = find_emph_char((data + i) + 1, (size - i) - 1, '<');
    if ((((i + spoilerspan) < size) && (spoilerspan > 0)) && (data[i + spoilerspan] == '!'))
    {
      return 0;
    }
    if (((i + 2) < size) && (data[i + 2] == ' '))
    {
      return i + 3;
    }
    return i + 2;
  }
  return 0;
}


----------------------------
static size_t is_empty(uint8_t *data, size_t size)
{
  size_t i;
  for (i = 0; (i < size) && (data[i] != '\n'); i += 1)
  {
    if (data[i] != ' ')
    {
      return 0;
    }
  }

  return i + 1;
}


----------------------------
struct buf
{
  uint8_t *data;
  size_t size;
  size_t asize;
  size_t unit;
}
----------------------------
None
----------------------------
***/


