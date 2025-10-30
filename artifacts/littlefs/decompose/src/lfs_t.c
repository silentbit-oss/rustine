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
struct lfs_config
{
  void *context;
  int (*read)(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size);
  int (*prog)(const struct lfs_config *c, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size);
  int (*erase)(const struct lfs_config *c, lfs_block_t block);
  int (*sync)(const struct lfs_config *c);
  lfs_size_t read_size;
  lfs_size_t prog_size;
  lfs_size_t block_size;
  lfs_size_t block_count;
  int32_t block_cycles;
  lfs_size_t cache_size;
  lfs_size_t lookahead_size;
  lfs_size_t compact_thresh;
  void *read_buffer;
  void *prog_buffer;
  void *lookahead_buffer;
  lfs_size_t name_max;
  lfs_size_t file_max;
  lfs_size_t attr_max;
  lfs_size_t metadata_max;
  lfs_size_t inline_max;
}
----------------------------
typedef struct lfs_gstate
{
  uint32_t tag;
  lfs_block_t pair[2];
} lfs_gstate_t
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
typedef uint32_t lfs_size_t
----------------------------
***/


