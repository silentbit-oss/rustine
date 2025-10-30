typedef size_t (*char_trigger)(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size)
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
struct buf
{
  uint8_t *data;
  size_t size;
  size_t asize;
  size_t unit;
}
----------------------------
***/


