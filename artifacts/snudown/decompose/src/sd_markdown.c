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
/*** DEPENDENCIES:
struct stack
{
  void **item;
  size_t size;
  size_t asize;
}
----------------------------
struct link_ref
{
  unsigned int id;
  struct buf *link;
  struct buf *label;
  struct buf *title;
  struct link_ref *next;
}
----------------------------
struct sd_callbacks
{
  void (*blockcode)(struct buf *ob, const struct buf *text, const struct buf *lang, void *opaque);
  void (*blockquote)(struct buf *ob, const struct buf *text, void *opaque);
  void (*blockspoiler)(struct buf *ob, const struct buf *text, void *opaque);
  void (*blockhtml)(struct buf *ob, const struct buf *text, void *opaque);
  void (*header)(struct buf *ob, const struct buf *text, int level, void *opaque);
  void (*hrule)(struct buf *ob, void *opaque);
  void (*list)(struct buf *ob, const struct buf *text, int flags, void *opaque);
  void (*listitem)(struct buf *ob, const struct buf *text, int flags, void *opaque);
  void (*paragraph)(struct buf *ob, const struct buf *text, void *opaque);
  void (*table)(struct buf *ob, const struct buf *header, const struct buf *body, void *opaque);
  void (*table_row)(struct buf *ob, const struct buf *text, void *opaque);
  void (*table_cell)(struct buf *ob, const struct buf *text, int flags, void *opaque, int col_span);
  int (*autolink)(struct buf *ob, const struct buf *link, enum mkd_autolink type, void *opaque);
  int (*codespan)(struct buf *ob, const struct buf *text, void *opaque);
  int (*spoilerspan)(struct buf *ob, const struct buf *text, void *opaque);
  int (*double_emphasis)(struct buf *ob, const struct buf *text, void *opaque);
  int (*emphasis)(struct buf *ob, const struct buf *text, void *opaque);
  int (*image)(struct buf *ob, const struct buf *link, const struct buf *title, const struct buf *alt, void *opaque);
  int (*linebreak)(struct buf *ob, void *opaque);
  int (*link)(struct buf *ob, const struct buf *link, const struct buf *title, const struct buf *content, void *opaque);
  int (*raw_html_tag)(struct buf *ob, const struct buf *tag, void *opaque);
  int (*triple_emphasis)(struct buf *ob, const struct buf *text, void *opaque);
  int (*strikethrough)(struct buf *ob, const struct buf *text, void *opaque);
  int (*superscript)(struct buf *ob, const struct buf *text, void *opaque);
  void (*entity)(struct buf *ob, const struct buf *entity, void *opaque);
  void (*normal_text)(struct buf *ob, const struct buf *text, void *opaque);
  void (*doc_header)(struct buf *ob, void *opaque);
  void (*doc_footer)(struct buf *ob, void *opaque);
}
----------------------------
***/


