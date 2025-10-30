typedef struct lfs_superblock
{
  uint32_t version;
  lfs_size_t block_size;
  lfs_size_t block_count;
  lfs_size_t name_max;
  lfs_size_t file_max;
  lfs_size_t attr_max;
} lfs_superblock_t
/*** DEPENDENCIES:
typedef uint32_t lfs_size_t
----------------------------
***/


