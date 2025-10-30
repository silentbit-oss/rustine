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
/*** DEPENDENCIES:
typedef uint32_t lfs_block_t
----------------------------
typedef uint32_t lfs_off_t
----------------------------
***/


