struct lfs_file_config
{
  void *buffer;
  struct lfs_attr *attrs;
  lfs_size_t attr_count;
}
/*** DEPENDENCIES:
struct lfs_attr
{
  uint8_t type;
  void *buffer;
  lfs_size_t size;
}
----------------------------
typedef uint32_t lfs_size_t
----------------------------
***/


