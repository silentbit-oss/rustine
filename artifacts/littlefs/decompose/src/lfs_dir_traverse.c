struct lfs_dir_traverse
{
  const lfs_mdir_t *dir;
  lfs_off_t off;
  lfs_tag_t ptag;
  const struct lfs_mattr *attrs;
  int attrcount;
  lfs_tag_t tmask;
  lfs_tag_t ttag;
  uint16_t begin;
  uint16_t end;
  int16_t diff;
  int (*cb)(void *data, lfs_tag_t tag, const void *buffer);
  void *data;
  lfs_tag_t tag;
  const void *buffer;
  struct lfs_diskoff disk;
}
/*** DEPENDENCIES:
struct lfs_diskoff
{
  lfs_block_t block;
  lfs_off_t off;
}
----------------------------
struct lfs_mattr
{
  lfs_tag_t tag;
  const void *buffer;
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


