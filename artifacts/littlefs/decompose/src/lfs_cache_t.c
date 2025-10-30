typedef struct lfs_cache
{
  lfs_block_t block;
  lfs_off_t off;
  lfs_size_t size;
  uint8_t *buffer;
} lfs_cache_t
/*** DEPENDENCIES:
typedef uint32_t lfs_block_t
----------------------------
typedef uint32_t lfs_off_t
----------------------------
typedef uint32_t lfs_size_t
----------------------------
***/


