struct lfs_commit
{
  lfs_block_t block;
  lfs_off_t off;
  lfs_tag_t ptag;
  uint32_t crc;
  lfs_off_t begin;
  lfs_off_t end;
}
/*** DEPENDENCIES:
typedef uint32_t lfs_block_t
----------------------------
typedef uint32_t lfs_off_t
----------------------------
typedef struct lfs
{
  lfs_cache_t rcache;
  lfs_cache_t pcache;
  lfs_block_t root[2];
  struct lfs_mlist
  {
    struct lfs_mlist *next;
    uint16_t id;
    uint8_t type;
    lfs_mdir_t m;
  } *mlist;
  uint32_t seed;
  lfs_gstate_t gstate;
  lfs_gstate_t gdisk;
  lfs_gstate_t gdelta;
  struct lfs_lookahead
  {
    lfs_block_t start;
    lfs_block_t size;
    lfs_block_t next;
    lfs_block_t ckpoint;
    uint8_t *buffer;
  } lookahead;
  const struct lfs_config *cfg;
  lfs_size_t block_count;
  lfs_size_t name_max;
  lfs_size_t file_max;
  lfs_size_t attr_max;
  lfs_size_t inline_max;
} lfs_t
----------------------------
typedef uint32_t lfs_tag_t
----------------------------
***/


