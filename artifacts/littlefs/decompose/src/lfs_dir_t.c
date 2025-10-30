typedef struct lfs_dir
{
  struct lfs_dir *next;
  uint16_t id;
  uint8_t type;
  lfs_mdir_t m;
  lfs_off_t pos;
  lfs_block_t head[2];
} lfs_dir_t
/*** DEPENDENCIES:
typedef uint32_t lfs_block_t
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
***/


