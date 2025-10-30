typedef struct lfs_file
{
  struct lfs_file *next;
  uint16_t id;
  uint8_t type;
  lfs_mdir_t m;
  struct lfs_ctz
  {
    lfs_block_t head;
    lfs_size_t size;
  } ctz;
  uint32_t flags;
  lfs_off_t pos;
  lfs_block_t block;
  lfs_off_t off;
  lfs_cache_t cache;
  const struct lfs_file_config *cfg;
} lfs_file_t
/*** DEPENDENCIES:
typedef uint32_t lfs_block_t
----------------------------
typedef struct lfs_cache
{
  lfs_block_t block;
  lfs_off_t off;
  lfs_size_t size;
  uint8_t *buffer;
} lfs_cache_t
----------------------------
struct lfs_file_config
{
  void *buffer;
  struct lfs_attr *attrs;
  lfs_size_t attr_count;
}
----------------------------
typedef struct lfs_mdir
{
  lfs_block_t pair[2];
  uint32_t rev;
  lfs_off_t off;
  uint32_t etag;
  uint16_t count;
  bool erased;
  bool split;
  lfs_block_t tail[2];
} lfs_mdir_t
----------------------------
typedef uint32_t lfs_off_t
----------------------------
typedef uint32_t lfs_size_t
----------------------------
***/


