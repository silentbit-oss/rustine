struct link_ref
{
  unsigned int id;
  struct buf *link;
  struct buf *label;
  struct buf *title;
  struct link_ref *next;
}
/*** DEPENDENCIES:
struct buf
{
  uint8_t *data;
  size_t size;
  size_t asize;
  size_t unit;
}
----------------------------
***/


