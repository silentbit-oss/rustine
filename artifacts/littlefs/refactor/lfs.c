#include <assert.h>
#include <inttypes.h>
#include <lfs.h>
#include <lfs_util.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

inline static uint32_t lfs_max(uint32_t a, uint32_t b)
{
  return (a > b) ? (a) : (b);
}

inline static uint32_t lfs_min(uint32_t a, uint32_t b)
{
  return (a < b) ? (a) : (b);
}

inline static uint32_t lfs_aligndown(uint32_t a, uint32_t alignment)
{
  return a - (a % alignment);
}

inline static uint32_t lfs_alignup(uint32_t a, uint32_t alignment)
{
  return lfs_aligndown((a + alignment) - 1, alignment);
}

inline static uint32_t lfs_npw2(uint32_t a)
{
  return 32 - __builtin_clz(a - 1);
}

inline static uint32_t lfs_ctz(uint32_t a)
{
  return __builtin_ctz(a);
}

inline static uint32_t lfs_popc(uint32_t a)
{
  return __builtin_popcount(a);
}

inline static int lfs_scmp(uint32_t a, uint32_t b)
{
  return (int) ((unsigned) (a - b));
}

inline static uint32_t lfs_fromle32(uint32_t a)
{
  return a;
}

inline static uint32_t lfs_tole32(uint32_t a)
{
  return lfs_fromle32(a);
}

inline static uint32_t lfs_frombe32(uint32_t a)
{
  return __builtin_bswap32(a);
}

inline static uint32_t lfs_tobe32(uint32_t a)
{
  return lfs_frombe32(a);
}

uint32_t lfs_crc(uint32_t crc, const void *buffer, size_t size);
inline static void *lfs_malloc(size_t size)
{
  return malloc(size);
}

inline static void lfs_free(void *p)
{
  free(p);
}

typedef uint32_t lfs_size_t;
typedef uint32_t lfs_off_t;
typedef int32_t lfs_ssize_t;
typedef int32_t lfs_soff_t;
typedef uint32_t lfs_block_t;
enum lfs_error
{
  LFS_ERR_OK = 0,
  LFS_ERR_IO = -5,
  LFS_ERR_CORRUPT = -84,
  LFS_ERR_NOENT = -2,
  LFS_ERR_EXIST = -17,
  LFS_ERR_NOTDIR = -20,
  LFS_ERR_ISDIR = -21,
  LFS_ERR_NOTEMPTY = -39,
  LFS_ERR_BADF = -9,
  LFS_ERR_FBIG = -27,
  LFS_ERR_INVAL = -22,
  LFS_ERR_NOSPC = -28,
  LFS_ERR_NOMEM = -12,
  LFS_ERR_NOATTR = -61,
  LFS_ERR_NAMETOOLONG = -36
};
enum lfs_type
{
  LFS_TYPE_REG = 0x001,
  LFS_TYPE_DIR = 0x002,
  LFS_TYPE_SPLICE = 0x400,
  LFS_TYPE_NAME = 0x000,
  LFS_TYPE_STRUCT = 0x200,
  LFS_TYPE_USERATTR = 0x300,
  LFS_TYPE_FROM = 0x100,
  LFS_TYPE_TAIL = 0x600,
  LFS_TYPE_GLOBALS = 0x700,
  LFS_TYPE_CRC = 0x500,
  LFS_TYPE_CREATE = 0x401,
  LFS_TYPE_DELETE = 0x4ff,
  LFS_TYPE_SUPERBLOCK = 0x0ff,
  LFS_TYPE_DIRSTRUCT = 0x200,
  LFS_TYPE_CTZSTRUCT = 0x202,
  LFS_TYPE_INLINESTRUCT = 0x201,
  LFS_TYPE_SOFTTAIL = 0x600,
  LFS_TYPE_HARDTAIL = 0x601,
  LFS_TYPE_MOVESTATE = 0x7ff,
  LFS_TYPE_CCRC = 0x500,
  LFS_TYPE_FCRC = 0x5ff,
  LFS_FROM_NOOP = 0x000,
  LFS_FROM_MOVE = 0x101,
  LFS_FROM_USERATTRS = 0x102
};
enum lfs_open_flags
{
  LFS_O_RDONLY = 1,
  LFS_O_WRONLY = 2,
  LFS_O_RDWR = 3,
  LFS_O_CREAT = 0x0100,
  LFS_O_EXCL = 0x0200,
  LFS_O_TRUNC = 0x0400,
  LFS_O_APPEND = 0x0800,
  LFS_F_DIRTY = 0x010000,
  LFS_F_WRITING = 0x020000,
  LFS_F_READING = 0x040000,
  LFS_F_ERRED = 0x080000,
  LFS_F_INLINE = 0x100000
};
enum lfs_whence_flags
{
  LFS_SEEK_SET = 0,
  LFS_SEEK_CUR = 1,
  LFS_SEEK_END = 2
};
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
};
struct lfs_info
{
  uint8_t type;
  lfs_size_t size;
  char name[255 + 1];
};
struct lfs_fsinfo
{
  uint32_t disk_version;
  lfs_size_t block_size;
  lfs_size_t block_count;
  lfs_size_t name_max;
  lfs_size_t file_max;
  lfs_size_t attr_max;
};
struct lfs_attr
{
  uint8_t type;
  void *buffer;
  lfs_size_t size;
};
struct lfs_file_config
{
  void *buffer;
  struct lfs_attr *attrs;
  lfs_size_t attr_count;
};
typedef struct lfs_cache
{
  lfs_block_t block;
  lfs_off_t off;
  lfs_size_t size;
  uint8_t *buffer;
} lfs_cache_t;
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
} lfs_mdir_t;
typedef struct lfs_dir
{
  struct lfs_dir *next;
  uint16_t id;
  uint8_t type;
  lfs_mdir_t m;
  lfs_off_t pos;
  lfs_block_t head[2];
} lfs_dir_t;
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
} lfs_file_t;
typedef struct lfs_superblock
{
  uint32_t version;
  lfs_size_t block_size;
  lfs_size_t block_count;
  lfs_size_t name_max;
  lfs_size_t file_max;
  lfs_size_t attr_max;
} lfs_superblock_t;
typedef struct lfs_gstate
{
  uint32_t tag;
  lfs_block_t pair[2];
} lfs_gstate_t;
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
} lfs_t;
int lfs_format(lfs_t *lfs, const struct lfs_config *config);
int lfs_mount(lfs_t *lfs, const struct lfs_config *config);
int lfs_unmount(lfs_t *lfs);
int lfs_remove(lfs_t *lfs, const char *path);
int lfs_rename(lfs_t *lfs, const char *oldpath, const char *newpath);
int lfs_stat(lfs_t *lfs, const char *path, struct lfs_info *info);
lfs_ssize_t lfs_getattr(lfs_t *lfs, const char *path, uint8_t type, void *buffer, lfs_size_t size);
int lfs_setattr(lfs_t *lfs, const char *path, uint8_t type, const void *buffer, lfs_size_t size);
int lfs_removeattr(lfs_t *lfs, const char *path, uint8_t type);
int lfs_file_open(lfs_t *lfs, lfs_file_t *file, const char *path, int flags);
int lfs_file_opencfg(lfs_t *lfs, lfs_file_t *file, const char *path, int flags, const struct lfs_file_config *config);
int lfs_file_close(lfs_t *lfs, lfs_file_t *file);
int lfs_file_sync(lfs_t *lfs, lfs_file_t *file);
lfs_ssize_t lfs_file_read(lfs_t *lfs, lfs_file_t *file, void *buffer, lfs_size_t size);
lfs_ssize_t lfs_file_write(lfs_t *lfs, lfs_file_t *file, const void *buffer, lfs_size_t size);
lfs_soff_t lfs_file_seek(lfs_t *lfs, lfs_file_t *file, lfs_soff_t off, int whence);
int lfs_file_truncate(lfs_t *lfs, lfs_file_t *file, lfs_off_t size);
lfs_soff_t lfs_file_tell(lfs_t *lfs, lfs_file_t *file);
int lfs_file_rewind(lfs_t *lfs, lfs_file_t *file);
lfs_soff_t lfs_file_size(lfs_t *lfs, lfs_file_t *file);
int lfs_mkdir(lfs_t *lfs, const char *path);
int lfs_dir_open(lfs_t *lfs, lfs_dir_t *dir, const char *path);
int lfs_dir_close(lfs_t *lfs, lfs_dir_t *dir);
int lfs_dir_read(lfs_t *lfs, lfs_dir_t *dir, struct lfs_info *info);
int lfs_dir_seek(lfs_t *lfs, lfs_dir_t *dir, lfs_off_t off);
lfs_soff_t lfs_dir_tell(lfs_t *lfs, lfs_dir_t *dir);
int lfs_dir_rewind(lfs_t *lfs, lfs_dir_t *dir);
int lfs_fs_stat(lfs_t *lfs, struct lfs_fsinfo *fsinfo);
lfs_ssize_t lfs_fs_size(lfs_t *lfs);
int lfs_fs_traverse(lfs_t *lfs, int (*cb)(void *, lfs_block_t), void *data);
int lfs_fs_mkconsistent(lfs_t *lfs);
int lfs_fs_gc(lfs_t *lfs);
int lfs_fs_grow(lfs_t *lfs, lfs_size_t block_count);
enum 
{
  LFS_OK_RELOCATED = 1,
  LFS_OK_DROPPED = 2,
  LFS_OK_ORPHANED = 3
};
enum 
{
  LFS_CMP_EQ = 0,
  LFS_CMP_LT = 1,
  LFS_CMP_GT = 2
};
inline static void lfs_cache_drop(lfs_t *lfs, lfs_cache_t *rcache)
{
  (void) lfs;
  rcache->block = (lfs_block_t) (-1);
}

inline static void lfs_cache_zero(lfs_t *lfs, lfs_cache_t *pcache)
{
  memset(pcache->buffer, 0xff, lfs->cfg->cache_size);
  pcache->block = (lfs_block_t) (-1);
}

static int lfs_bd_read(lfs_t *lfs, const lfs_cache_t *pcache, lfs_cache_t *rcache, lfs_size_t hint, lfs_block_t block, lfs_off_t off, void *buffer, lfs_size_t size)
{
  uint8_t *data = buffer;
  unsigned int data_idx = 0;
  if (((off + size) > lfs->cfg->block_size) || (lfs->block_count && (block >= lfs->block_count)))
  {
    return LFS_ERR_CORRUPT;
  }
  while (size > 0)
  {
    helper_lfs_bd_read_1(&block, &off, &size, &data_idx, lfs, pcache, rcache, hint, data);
  }

  return 0;
}

static int lfs_bd_cmp(lfs_t *lfs, const lfs_cache_t *pcache, lfs_cache_t *rcache, lfs_size_t hint, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size)
{
  const uint8_t *data = buffer;
  lfs_size_t diff = 0;
  for (lfs_off_t i = 0; i < size; i += diff)
  {
    uint8_t dat[8];
    diff = lfs_min(size - i, sizeof(dat));
    int err = lfs_bd_read(lfs, pcache, rcache, hint - i, block, off + i, &dat, diff);
    if (err)
    {
      return err;
    }
    int res = memcmp(dat, data + i, diff);
    if (res)
    {
      return (res < 0) ? (LFS_CMP_LT) : (LFS_CMP_GT);
    }
  }

  return LFS_CMP_EQ;
}

static int lfs_bd_crc(lfs_t *lfs, const lfs_cache_t *pcache, lfs_cache_t *rcache, lfs_size_t hint, lfs_block_t block, lfs_off_t off, lfs_size_t size, uint32_t *crc)
{
  lfs_size_t diff = 0;
  for (lfs_off_t i = 0; i < size; i += diff)
  {
    uint8_t dat[8];
    diff = lfs_min(size - i, sizeof(dat));
    int err = lfs_bd_read(lfs, pcache, rcache, hint - i, block, off + i, &dat, diff);
    if (err)
    {
      return err;
    }
    *crc = lfs_crc(*crc, &dat, diff);
  }

  return 0;
}

static int lfs_bd_flush(lfs_t *lfs, lfs_cache_t *pcache, lfs_cache_t *rcache, bool validate)
{
  if ((pcache->block != ((lfs_block_t) (-1))) && (pcache->block != ((lfs_block_t) (-2))))
  {
    assert(pcache->block < lfs->block_count);
    lfs_size_t diff = lfs_alignup(pcache->size, lfs->cfg->prog_size);
    int err = lfs->cfg->prog(lfs->cfg, pcache->block, pcache->off, pcache->buffer, diff);
    assert(err <= 0);
    if (err)
    {
      return err;
    }
    if (validate)
    {
      lfs_cache_drop(lfs, rcache);
      int res = lfs_bd_cmp(lfs, 0, rcache, diff, pcache->block, pcache->off, pcache->buffer, diff);
      if (res < 0)
      {
        return res;
      }
      if (res != LFS_CMP_EQ)
      {
        return LFS_ERR_CORRUPT;
      }
    }
    lfs_cache_zero(lfs, pcache);
  }
  return 0;
}

static int lfs_bd_sync(lfs_t *lfs, lfs_cache_t *pcache, lfs_cache_t *rcache, bool validate)
{
  lfs_cache_drop(lfs, rcache);
  int err = lfs_bd_flush(lfs, pcache, rcache, validate);
  if (err)
  {
    return err;
  }
  err = lfs->cfg->sync(lfs->cfg);
  assert(err <= 0);
  return err;
}

static int lfs_bd_prog(lfs_t *lfs, lfs_cache_t *pcache, lfs_cache_t *rcache, bool validate, lfs_block_t block, lfs_off_t off, const void *buffer, lfs_size_t size)
{
  const uint8_t *data = buffer;
  unsigned int data_idx = 0;
  assert((block == ((lfs_block_t) (-2))) || (block < lfs->block_count));
  assert((off + size) <= lfs->cfg->block_size);
  while (size > 0)
  {
    if (((block == pcache->block) && (off >= pcache->off)) && (off < (pcache->off + lfs->cfg->cache_size)))
    {
      lfs_size_t diff = lfs_min(size, lfs->cfg->cache_size - (off - pcache->off));
      memcpy(&pcache->buffer[off - pcache->off], data, diff);
      data_idx += diff;
      off += diff;
      size -= diff;
      pcache->size = lfs_max(pcache->size, off - pcache->off);
      if (pcache->size == lfs->cfg->cache_size)
      {
        int err = lfs_bd_flush(lfs, pcache, rcache, validate);
        if (err)
        {
          return err;
        }
      }
      continue;
    }
    assert(pcache->block == ((lfs_block_t) (-1)));
    pcache->block = block;
    pcache->off = lfs_aligndown(off, lfs->cfg->prog_size);
    pcache->size = 0;
  }

  return 0;
}

static int lfs_bd_erase(lfs_t *lfs, lfs_block_t block)
{
  assert(block < lfs->block_count);
  int err = lfs->cfg->erase(lfs->cfg, block);
  assert(err <= 0);
  return err;
}

inline static lfs_size_t lfs_path_namelen(const char *path)
{
  return strcspn(path, "/");
}

inline static bool lfs_path_islast(const char *path)
{
  lfs_size_t namelen = lfs_path_namelen(path);
  return path[namelen + strspn(path + namelen, "/")] == '\0';
}

inline static bool lfs_path_isdir(const char *path)
{
  return path[lfs_path_namelen(path)] != '\0';
}

inline static void lfs_pair_swap(lfs_block_t pair[2])
{
  lfs_block_t t = pair[0];
  pair[0] = pair[1];
  pair[1] = t;
}

inline static bool lfs_pair_isnull(const lfs_block_t pair[2])
{
  return (pair[0] == ((lfs_block_t) (-1))) || (pair[1] == ((lfs_block_t) (-1)));
}

inline static int lfs_pair_cmp(const lfs_block_t paira[2], const lfs_block_t pairb[2])
{
  return !((((paira[0] == pairb[0]) || (paira[1] == pairb[1])) || (paira[0] == pairb[1])) || (paira[1] == pairb[0]));
}

inline static bool lfs_pair_issync(const lfs_block_t paira[2], const lfs_block_t pairb[2])
{
  return ((paira[0] == pairb[0]) && (paira[1] == pairb[1])) || ((paira[0] == pairb[1]) && (paira[1] == pairb[0]));
}

inline static void lfs_pair_fromle32(lfs_block_t pair[2])
{
  pair[0] = lfs_fromle32(pair[0]);
  pair[1] = lfs_fromle32(pair[1]);
}

inline static void lfs_pair_tole32(lfs_block_t pair[2])
{
  pair[0] = lfs_tole32(pair[0]);
  pair[1] = lfs_tole32(pair[1]);
}

typedef uint32_t lfs_tag_t;
typedef int32_t lfs_stag_t;
inline static bool lfs_tag_isvalid(lfs_tag_t tag)
{
  return !(tag & 0x80000000);
}

inline static bool lfs_tag_isdelete(lfs_tag_t tag)
{
  return (((int32_t) (tag << 22)) >> 22) == (-1);
}

inline static uint16_t lfs_tag_type1(lfs_tag_t tag)
{
  return (tag & 0x70000000) >> 20;
}

inline static uint16_t lfs_tag_type2(lfs_tag_t tag)
{
  return (tag & 0x78000000) >> 20;
}

inline static uint16_t lfs_tag_type3(lfs_tag_t tag)
{
  return (tag & 0x7ff00000) >> 20;
}

inline static uint8_t lfs_tag_chunk(lfs_tag_t tag)
{
  return (tag & 0x0ff00000) >> 20;
}

inline static int8_t lfs_tag_splice(lfs_tag_t tag)
{
  return (int8_t) lfs_tag_chunk(tag);
}

inline static uint16_t lfs_tag_id(lfs_tag_t tag)
{
  return (tag & 0x000ffc00) >> 10;
}

inline static lfs_size_t lfs_tag_size(lfs_tag_t tag)
{
  return tag & 0x000003ff;
}

inline static lfs_size_t lfs_tag_dsize(lfs_tag_t tag)
{
  return (sizeof(tag)) + lfs_tag_size(tag + lfs_tag_isdelete(tag));
}

struct lfs_mattr
{
  lfs_tag_t tag;
  const void *buffer;
};
struct lfs_diskoff
{
  lfs_block_t block;
  lfs_off_t off;
};
inline static void lfs_gstate_xor(lfs_gstate_t *a, const lfs_gstate_t *b)
{
  a->tag ^= b->tag;
  a->pair[0] ^= b->pair[0];
  a->pair[1] ^= b->pair[1];
}

inline static bool lfs_gstate_iszero(const lfs_gstate_t *a)
{
  return ((a->tag == 0) && (a->pair[0] == 0)) && (a->pair[1] == 0);
}

inline static bool lfs_gstate_hasorphans(const lfs_gstate_t *a)
{
  return lfs_tag_size(a->tag);
}

inline static uint8_t lfs_gstate_getorphans(const lfs_gstate_t *a)
{
  return lfs_tag_size(a->tag) & 0x1ff;
}

inline static bool lfs_gstate_hasmove(const lfs_gstate_t *a)
{
  return lfs_tag_type1(a->tag);
}

inline static bool lfs_gstate_needssuperblock(const lfs_gstate_t *a)
{
  return lfs_tag_size(a->tag) >> 9;
}

inline static bool lfs_gstate_hasmovehere(const lfs_gstate_t *a, const lfs_block_t *pair)
{
  return lfs_tag_type1(a->tag) && (lfs_pair_cmp(a->pair, pair) == 0);
}

inline static void lfs_gstate_fromle32(lfs_gstate_t *a)
{
  a->tag = lfs_fromle32(a->tag);
  a->pair[0] = lfs_fromle32(a->pair[0]);
  a->pair[1] = lfs_fromle32(a->pair[1]);
}

inline static void lfs_gstate_tole32(lfs_gstate_t *a)
{
  a->tag = lfs_tole32(a->tag);
  a->pair[0] = lfs_tole32(a->pair[0]);
  a->pair[1] = lfs_tole32(a->pair[1]);
}

struct lfs_fcrc
{
  lfs_size_t size;
  uint32_t crc;
};
static void lfs_fcrc_fromle32(struct lfs_fcrc *fcrc)
{
  fcrc->size = lfs_fromle32(fcrc->size);
  fcrc->crc = lfs_fromle32(fcrc->crc);
}

static void lfs_fcrc_tole32(struct lfs_fcrc *fcrc)
{
  fcrc->size = lfs_tole32(fcrc->size);
  fcrc->crc = lfs_tole32(fcrc->crc);
}

static void lfs_ctz_fromle32(struct lfs_ctz *ctz)
{
  ctz->head = lfs_fromle32(ctz->head);
  ctz->size = lfs_fromle32(ctz->size);
}

static void lfs_ctz_tole32(struct lfs_ctz *ctz)
{
  ctz->head = lfs_tole32(ctz->head);
  ctz->size = lfs_tole32(ctz->size);
}

inline static void lfs_superblock_fromle32(lfs_superblock_t *superblock)
{
  superblock->version = lfs_fromle32(superblock->version);
  superblock->block_size = lfs_fromle32(superblock->block_size);
  superblock->block_count = lfs_fromle32(superblock->block_count);
  superblock->name_max = lfs_fromle32(superblock->name_max);
  superblock->file_max = lfs_fromle32(superblock->file_max);
  superblock->attr_max = lfs_fromle32(superblock->attr_max);
}

inline static void lfs_superblock_tole32(lfs_superblock_t *superblock)
{
  superblock->version = lfs_tole32(superblock->version);
  superblock->block_size = lfs_tole32(superblock->block_size);
  superblock->block_count = lfs_tole32(superblock->block_count);
  superblock->name_max = lfs_tole32(superblock->name_max);
  superblock->file_max = lfs_tole32(superblock->file_max);
  superblock->attr_max = lfs_tole32(superblock->attr_max);
}

static bool lfs_mlist_isopen(struct lfs_mlist *head, struct lfs_mlist *node)
{
  for (struct lfs_mlist **p = &head; p[p_idx]; p_idx = &(*p_idx)->next)
  {
    if (p[p_idx] == ((struct lfs_mlist *) node))
    {
      return 1;
    }
  }

  unsigned int p_idx = 0;
  return 0;
}

static void lfs_mlist_remove(lfs_t *lfs, struct lfs_mlist *mlist)
{
  for (struct lfs_mlist **p = &lfs->mlist; p[p_idx]; p_idx = &(*p_idx)->next)
  {
    if (p[p_idx] == mlist)
    {
      p[p_idx] = p[p_idx]->next;
      break;
    }
  }

  unsigned int p_idx = 0;
}

static void lfs_mlist_append(lfs_t *lfs, struct lfs_mlist *mlist)
{
  mlist->next = lfs->mlist;
  lfs->mlist = mlist;
}

static uint32_t lfs_fs_disk_version(lfs_t *lfs)
{
  (void) lfs;
  {
    return 0x00020001;
  }
}

static uint16_t lfs_fs_disk_version_major(lfs_t *lfs)
{
  return 0xffff & (lfs_fs_disk_version(lfs) >> 16);
}

static uint16_t lfs_fs_disk_version_minor(lfs_t *lfs)
{
  return 0xffff & (lfs_fs_disk_version(lfs) >> 0);
}

static int lfs_dir_commit(lfs_t *lfs, lfs_mdir_t *dir, const struct lfs_mattr *attrs, int attrcount);
static int lfs_dir_compact(lfs_t *lfs, lfs_mdir_t *dir, const struct lfs_mattr *attrs, int attrcount, lfs_mdir_t *source, uint16_t begin, uint16_t end);
static lfs_ssize_t lfs_file_flushedwrite(lfs_t *lfs, lfs_file_t *file, const void *buffer, lfs_size_t size);
static lfs_ssize_t lfs_file_write_(lfs_t *lfs, lfs_file_t *file, const void *buffer, lfs_size_t size);
static int lfs_file_sync_(lfs_t *lfs, lfs_file_t *file);
static int lfs_file_outline(lfs_t *lfs, lfs_file_t *file);
static int lfs_file_flush(lfs_t *lfs, lfs_file_t *file);
static int lfs_fs_deorphan(lfs_t *lfs, bool powerloss);
static int lfs_fs_preporphans(lfs_t *lfs, int8_t orphans);
static void lfs_fs_prepmove(lfs_t *lfs, uint16_t id, const lfs_block_t pair[2]);
static int lfs_fs_pred(lfs_t *lfs, const lfs_block_t dir[2], lfs_mdir_t *pdir);
static lfs_stag_t lfs_fs_parent(lfs_t *lfs, const lfs_block_t dir[2], lfs_mdir_t *parent);
static int lfs_fs_forceconsistency(lfs_t *lfs);
static void lfs_fs_prepsuperblock(lfs_t *lfs, bool needssuperblock);
static int lfs_dir_rewind_(lfs_t *lfs, lfs_dir_t *dir);
static lfs_ssize_t lfs_file_flushedread(lfs_t *lfs, lfs_file_t *file, void *buffer, lfs_size_t size);
static lfs_ssize_t lfs_file_read_(lfs_t *lfs, lfs_file_t *file, void *buffer, lfs_size_t size);
static int lfs_file_close_(lfs_t *lfs, lfs_file_t *file);
static lfs_soff_t lfs_file_size_(lfs_t *lfs, lfs_file_t *file);
static lfs_ssize_t lfs_fs_size_(lfs_t *lfs);
static int lfs_fs_traverse_(lfs_t *lfs, int (*cb)(void *data, lfs_block_t block), void *data, bool includeorphans);
static int lfs_deinit(lfs_t *lfs);
static int lfs_unmount_(lfs_t *lfs);
static void lfs_alloc_ckpoint(lfs_t *lfs)
{
  lfs->lookahead.ckpoint = lfs->block_count;
}

static void lfs_alloc_drop(lfs_t *lfs)
{
  lfs->lookahead.size = 0;
  lfs->lookahead.next = 0;
  lfs_alloc_ckpoint(lfs);
}

static int lfs_alloc_lookahead(void *p, lfs_block_t block)
{
  lfs_t *lfs = (lfs_t *) p;
  lfs_block_t off = ((block - lfs->lookahead.start) + lfs->block_count) % lfs->block_count;
  if (off < lfs->lookahead.size)
  {
    lfs->lookahead.buffer[off / 8] |= 1U << (off % 8);
  }
  return 0;
}

static int lfs_alloc_scan(lfs_t *lfs)
{
  lfs->lookahead.start = (lfs->lookahead.start + lfs->lookahead.next) % lfs->block_count;
  lfs->lookahead.next = 0;
  lfs->lookahead.size = lfs_min(8 * lfs->cfg->lookahead_size, lfs->lookahead.ckpoint);
  memset(lfs->lookahead.buffer, 0, lfs->cfg->lookahead_size);
  int err = lfs_fs_traverse_(lfs, lfs_alloc_lookahead, lfs, 1);
  if (err)
  {
    lfs_alloc_drop(lfs);
    return err;
  }
  return 0;
}

static int lfs_alloc(lfs_t *lfs, lfs_block_t *block)
{
  while (1)
  {
    while (lfs->lookahead.next < lfs->lookahead.size)
    {
      if (!(lfs->lookahead.buffer[lfs->lookahead.next / 8] & (1U << (lfs->lookahead.next % 8))))
      {
        *block = (lfs->lookahead.start + lfs->lookahead.next) % lfs->block_count;
        while (1)
        {
          lfs->lookahead.next += 1;
          lfs->lookahead.ckpoint -= 1;
          if ((lfs->lookahead.next >= lfs->lookahead.size) || (!(lfs->lookahead.buffer[lfs->lookahead.next / 8] & (1U << (lfs->lookahead.next % 8)))))
          {
            return 0;
          }
        }

      }
      lfs->lookahead.next += 1;
      lfs->lookahead.ckpoint -= 1;
    }

    if (lfs->lookahead.ckpoint <= 0)
    {
      printf("%s:%d:error: No more free space 0x%x%s\n", "/home/ubuntu/C2RustTranslation/subjects/littlefs/lfs.c", 702, (lfs->lookahead.start + lfs->lookahead.next) % lfs->block_count, "");
      return LFS_ERR_NOSPC;
    }
    int err = lfs_alloc_scan(lfs);
    if (err)
    {
      return err;
    }
  }

}

static lfs_stag_t lfs_dir_getslice(lfs_t *lfs, const lfs_mdir_t *dir, lfs_tag_t gmask, lfs_tag_t gtag, lfs_off_t goff, void *gbuffer, lfs_size_t gsize)
{
  lfs_off_t off = dir->off;
  lfs_tag_t ntag = dir->etag;
  lfs_stag_t gdiff = 0;
  if (lfs_gstate_hasmovehere(&lfs->gdisk, dir->pair) && (lfs_tag_id(gmask) != 0))
  {
    if (lfs_tag_id(lfs->gdisk.tag) == lfs_tag_id(gtag))
    {
      return LFS_ERR_NOENT;
    }
    else
      if (lfs_tag_id(lfs->gdisk.tag) < lfs_tag_id(gtag))
    {
      gdiff -= ((((lfs_tag_t) 0) << 20) | (((lfs_tag_t) 1) << 10)) | ((lfs_tag_t) 0);
    }
  }
  while (off >= ((sizeof(lfs_tag_t)) + lfs_tag_dsize(ntag)))
  {
    off -= lfs_tag_dsize(ntag);
    lfs_tag_t tag = ntag;
    int err = lfs_bd_read(lfs, 0, &lfs->rcache, sizeof(ntag), dir->pair[0], off, &ntag, sizeof(ntag));
    assert(err <= 0);
    if (err)
    {
      return err;
    }
    ntag = (lfs_frombe32(ntag) ^ tag) & 0x7fffffff;
    if (((lfs_tag_id(gmask) != 0) && (lfs_tag_type1(tag) == LFS_TYPE_SPLICE)) && (lfs_tag_id(tag) <= lfs_tag_id(gtag - gdiff)))
    {
      if (tag == ((((((lfs_tag_t) LFS_TYPE_CREATE) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 0)) | ((((((lfs_tag_t) 0) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 0)) & (gtag - gdiff))))
      {
        return LFS_ERR_NOENT;
      }
      gdiff += ((((lfs_tag_t) 0) << 20) | (((lfs_tag_t) lfs_tag_splice(tag)) << 10)) | ((lfs_tag_t) 0);
    }
    if ((gmask & tag) == (gmask & (gtag - gdiff)))
    {
      if (lfs_tag_isdelete(tag))
      {
        return LFS_ERR_NOENT;
      }
      lfs_size_t diff = lfs_min(lfs_tag_size(tag), gsize);
      err = lfs_bd_read(lfs, 0, &lfs->rcache, diff, dir->pair[0], (off + (sizeof(tag))) + goff, gbuffer, diff);
      assert(err <= 0);
      if (err)
      {
        return err;
      }
      memset(((uint8_t *) gbuffer) + diff, 0, gsize - diff);
      return tag + gdiff;
    }
  }

  return LFS_ERR_NOENT;
}

static lfs_stag_t lfs_dir_get(lfs_t *lfs, const lfs_mdir_t *dir, lfs_tag_t gmask, lfs_tag_t gtag, void *buffer)
{
  return lfs_dir_getslice(lfs, dir, gmask, gtag, 0, buffer, lfs_tag_size(gtag));
}

static int lfs_dir_getread(lfs_t *lfs, const lfs_mdir_t *dir, const lfs_cache_t *pcache, lfs_cache_t *rcache, lfs_size_t hint, lfs_tag_t gmask, lfs_tag_t gtag, lfs_off_t off, void *buffer, lfs_size_t size)
{
  uint8_t *data = buffer;
  unsigned int data_idx = 0;
  if ((off + size) > lfs->cfg->block_size)
  {
    return LFS_ERR_CORRUPT;
  }
  while (size > 0)
  {
    lfs_size_t diff = size;
    if ((pcache && (pcache->block == ((lfs_block_t) (-2)))) && (off < (pcache->off + pcache->size)))
    {
      if (off >= pcache->off)
      {
        diff = lfs_min(diff, pcache->size - (off - pcache->off));
        memcpy(data, &pcache->buffer[off - pcache->off], diff);
        data_idx += diff;
        off += diff;
        size -= diff;
        continue;
      }
      diff = lfs_min(diff, pcache->off - off);
    }
    if ((rcache->block == ((lfs_block_t) (-2))) && (off < (rcache->off + rcache->size)))
    {
      if (off >= rcache->off)
      {
        diff = lfs_min(diff, rcache->size - (off - rcache->off));
        memcpy(data, &rcache->buffer[off - rcache->off], diff);
        data_idx += diff;
        off += diff;
        size -= diff;
        continue;
      }
    }
    rcache->block = (lfs_block_t) (-2);
    rcache->off = lfs_aligndown(off, lfs->cfg->read_size);
    rcache->size = lfs_min(lfs_alignup(off + hint, lfs->cfg->read_size), lfs->cfg->cache_size);
    int err = lfs_dir_getslice(lfs, dir, gmask, gtag, rcache->off, rcache->buffer, rcache->size);
    if (err < 0)
    {
      return err;
    }
  }

  return 0;
}

static int lfs_dir_traverse_filter(void *p, lfs_tag_t tag, const void *buffer)
{
  lfs_tag_t *filtertag = p;
  (void) buffer;
  uint32_t mask = (tag & (((((lfs_tag_t) 0x100) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 0))) ? (((((lfs_tag_t) 0x7ff) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 0)) : (((((lfs_tag_t) 0x700) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 0));
  if ((((mask & tag) == (mask & (*filtertag))) || lfs_tag_isdelete(*filtertag)) || (((((((lfs_tag_t) 0x7ff) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 0)) & tag) == ((((((lfs_tag_t) LFS_TYPE_DELETE) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 0)) | ((((((lfs_tag_t) 0) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 0)) & (*filtertag)))))
  {
    *filtertag = ((((lfs_tag_t) LFS_FROM_NOOP) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 0);
    return 1;
  }
  if ((lfs_tag_type1(tag) == LFS_TYPE_SPLICE) && (lfs_tag_id(tag) <= lfs_tag_id(*filtertag)))
  {
    *filtertag += ((((lfs_tag_t) 0) << 20) | (((lfs_tag_t) lfs_tag_splice(tag)) << 10)) | ((lfs_tag_t) 0);
  }
  return 0;
}

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
};
static int lfs_dir_traverse(lfs_t *lfs, const lfs_mdir_t *dir, lfs_off_t off, lfs_tag_t ptag, const struct lfs_mattr *attrs, int attrcount, lfs_tag_t tmask, lfs_tag_t ttag, uint16_t begin, uint16_t end, int16_t diff, int (*cb)(void *data, lfs_tag_t tag, const void *buffer), void *data)
{
  unsigned int data_idx = 0;
  unsigned int cb_idx = 0;
  unsigned int attrs_idx = 0;
  unsigned int dir_idx = 0;
  struct lfs_dir_traverse stack[3 - 1];
  unsigned sp = 0;
  int res;
  lfs_tag_t tag;
  const void *buffer;
  unsigned int buffer_idx = 0;
  struct lfs_diskoff disk = {0};
  while (1)
  {
    helper_lfs_dir_traverse_2(&off, &ptag, &attrcount, &tmask, &ttag, &begin, &end, &diff, &tag, &data_idx, &cb_idx, &attrs_idx, &dir_idx, &sp, &res, &tag, &buffer_idx, &disk, lfs, dir, attrs, cb, data, buffer, data, stack, buffer);
  }

  if (sp > 0)
  {
    helper_lfs_dir_traverse_1(&off, &ptag, &attrcount, &tmask, &ttag, &begin, &end, &diff, &tag, &data_idx, &cb_idx, &attrs_idx, &dir_idx, &sp, &tag, &buffer_idx, &disk, stack);
  }
  else
  {
    return res;
  }
}

static lfs_stag_t lfs_dir_fetchmatch(lfs_t *lfs, lfs_mdir_t *dir, const lfs_block_t pair[2], lfs_tag_t fmask, lfs_tag_t ftag, uint16_t *id, int (*cb)(void *data, lfs_tag_t tag, const void *buffer), void *data)
{
  lfs_stag_t besttag = -1;
  if (lfs->block_count && ((pair[0] >= lfs->block_count) || (pair[1] >= lfs->block_count)))
  {
    return LFS_ERR_CORRUPT;
  }
  uint32_t revs[2] = {0, 0};
  int r = 0;
  for (int i = 0; i < 2; i += 1)
  {
    int err = lfs_bd_read(lfs, 0, &lfs->rcache, sizeof(revs[i]), pair[i], 0, &revs[i], sizeof(revs[i]));
    revs[i] = lfs_fromle32(revs[i]);
    if (err && (err != LFS_ERR_CORRUPT))
    {
      return err;
    }
    if ((err != LFS_ERR_CORRUPT) && (lfs_scmp(revs[i], revs[(i + 1) % 2]) > 0))
    {
      r = i;
    }
  }

  dir->pair[0] = pair[(r + 0) % 2];
  dir->pair[1] = pair[(r + 1) % 2];
  dir->rev = revs[(r + 0) % 2];
  dir->off = 0;
  for (int i = 0; i < 2; i += 1)
  {
    helper_lfs_dir_fetchmatch_1(&besttag, lfs, dir, fmask, ftag, id, data, data, revs, r);
  }

  printf("%s:%d:error: Corrupted dir pair at {0x%x, 0x%x}%s\n", "/home/ubuntu/C2RustTranslation/subjects/littlefs/lfs.c", 1382, dir->pair[0], dir->pair[1], "");
  return LFS_ERR_CORRUPT;
}

static int lfs_dir_fetch(lfs_t *lfs, lfs_mdir_t *dir, const lfs_block_t pair[2])
{
  return (int) lfs_dir_fetchmatch(lfs, dir, pair, (lfs_tag_t) (-1), (lfs_tag_t) (-1), 0, 0, 0);
}

static int lfs_dir_getgstate(lfs_t *lfs, const lfs_mdir_t *dir, lfs_gstate_t *gstate)
{
  lfs_gstate_t temp;
  lfs_stag_t res = lfs_dir_get(lfs, dir, ((((lfs_tag_t) 0x7ff) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 0), ((((lfs_tag_t) LFS_TYPE_MOVESTATE) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) (sizeof(temp))), &temp);
  if ((res < 0) && (res != LFS_ERR_NOENT))
  {
    return res;
  }
  if (res != LFS_ERR_NOENT)
  {
    lfs_gstate_fromle32(&temp);
    lfs_gstate_xor(gstate, &temp);
  }
  return 0;
}

static int lfs_dir_getinfo(lfs_t *lfs, lfs_mdir_t *dir, uint16_t id, struct lfs_info *info)
{
  if (id == 0x3ff)
  {
    strcpy(info->name, "/");
    info->type = LFS_TYPE_DIR;
    return 0;
  }
  lfs_stag_t tag = lfs_dir_get(lfs, dir, ((((lfs_tag_t) 0x780) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 0), ((((lfs_tag_t) LFS_TYPE_NAME) << 20) | (((lfs_tag_t) id) << 10)) | ((lfs_tag_t) (lfs->name_max + 1)), info->name);
  if (tag < 0)
  {
    return (int) tag;
  }
  info->type = lfs_tag_type3(tag);
  struct lfs_ctz ctz;
  tag = lfs_dir_get(lfs, dir, ((((lfs_tag_t) 0x700) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 0), ((((lfs_tag_t) LFS_TYPE_STRUCT) << 20) | (((lfs_tag_t) id) << 10)) | ((lfs_tag_t) (sizeof(ctz))), &ctz);
  if (tag < 0)
  {
    return (int) tag;
  }
  lfs_ctz_fromle32(&ctz);
  if (lfs_tag_type3(tag) == LFS_TYPE_CTZSTRUCT)
  {
    info->size = ctz.size;
  }
  else
    if (lfs_tag_type3(tag) == LFS_TYPE_INLINESTRUCT)
  {
    info->size = lfs_tag_size(tag);
  }
  return 0;
}

struct lfs_dir_find_match
{
  lfs_t *lfs;
  const void *name;
  lfs_size_t size;
};
static int lfs_dir_find_match(void *data, lfs_tag_t tag, const void *buffer)
{
  struct lfs_dir_find_match *name = data;
  lfs_t *lfs = name->lfs;
  const struct lfs_diskoff *disk = buffer;
  lfs_size_t diff = lfs_min(name->size, lfs_tag_size(tag));
  int res = lfs_bd_cmp(lfs, 0, &lfs->rcache, diff, disk->block, disk->off, name->name, diff);
  if (res != LFS_CMP_EQ)
  {
    return res;
  }
  if (name->size != lfs_tag_size(tag))
  {
    return (name->size < lfs_tag_size(tag)) ? (LFS_CMP_LT) : (LFS_CMP_GT);
  }
  return LFS_CMP_EQ;
}

static lfs_stag_t lfs_dir_find(lfs_t *lfs, lfs_mdir_t *dir, const char **path, uint16_t *id)
{
  const char *name = *path;
  unsigned int name_idx = 0;
  lfs_stag_t tag = ((((lfs_tag_t) LFS_TYPE_DIR) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 0);
  dir->tail[0] = lfs->root[0];
  dir->tail[1] = lfs->root[1];
  if (name[name_idx] == '\0')
  {
    return LFS_ERR_INVAL;
  }
  while (1)
  {
    helper_lfs_dir_find_1(&name_idx, &tag, lfs, dir, path, id, name);
  }

}

struct lfs_commit
{
  lfs_block_t block;
  lfs_off_t off;
  lfs_tag_t ptag;
  uint32_t crc;
  lfs_off_t begin;
  lfs_off_t end;
};
static int lfs_dir_commitprog(lfs_t *lfs, struct lfs_commit *commit, const void *buffer, lfs_size_t size)
{
  int err = lfs_bd_prog(lfs, &lfs->pcache, &lfs->rcache, 0, commit->block, commit->off, (const uint8_t *) buffer, size);
  if (err)
  {
    return err;
  }
  commit->crc = lfs_crc(commit->crc, buffer, size);
  commit->off += size;
  return 0;
}

static int lfs_dir_commitattr(lfs_t *lfs, struct lfs_commit *commit, lfs_tag_t tag, const void *buffer)
{
  lfs_size_t dsize = lfs_tag_dsize(tag);
  if ((commit->off + dsize) > commit->end)
  {
    return LFS_ERR_NOSPC;
  }
  lfs_tag_t ntag = lfs_tobe32((tag & 0x7fffffff) ^ commit->ptag);
  int err = lfs_dir_commitprog(lfs, commit, &ntag, sizeof(ntag));
  if (err)
  {
    return err;
  }
  if (!(tag & 0x80000000))
  {
    err = lfs_dir_commitprog(lfs, commit, buffer, dsize - (sizeof(tag)));
    if (err)
    {
      return err;
    }
  }
  else
  {
    const struct lfs_diskoff *disk = buffer;
    for (lfs_off_t i = 0; i < (dsize - (sizeof(tag))); i += 1)
    {
      uint8_t dat;
      err = lfs_bd_read(lfs, 0, &lfs->rcache, (dsize - (sizeof(tag))) - i, disk->block, disk->off + i, &dat, 1);
      if (err)
      {
        return err;
      }
      err = lfs_dir_commitprog(lfs, commit, &dat, 1);
      if (err)
      {
        return err;
      }
    }

  }
  commit->ptag = tag & 0x7fffffff;
  return 0;
}

static int lfs_dir_commitcrc(lfs_t *lfs, struct lfs_commit *commit)
{
  const lfs_off_t end = lfs_alignup(lfs_min(commit->off + (5 * (sizeof(uint32_t))), lfs->cfg->block_size), lfs->cfg->prog_size);
  lfs_off_t off1 = 0;
  uint32_t crc1 = 0;
  while (commit->off < end)
  {
    helper_lfs_dir_commitcrc_1(&off1, &crc1, &crc, &crc, lfs, commit, end);
  }

  lfs_off_t off = commit->begin;
  uint32_t crc = 0xffffffff;
  int err = lfs_bd_crc(lfs, 0, &lfs->rcache, off1 + (sizeof(uint32_t)), commit->block, off, off1 - off, &crc);
  if (err)
  {
    return err;
  }
  if (crc != crc1)
  {
    return LFS_ERR_CORRUPT;
  }
  err = lfs_bd_crc(lfs, 0, &lfs->rcache, sizeof(uint32_t), commit->block, off1, sizeof(uint32_t), &crc);
  if (err)
  {
    return err;
  }
  if (crc != 0)
  {
    return LFS_ERR_CORRUPT;
  }
  return 0;
}

static int lfs_dir_alloc(lfs_t *lfs, lfs_mdir_t *dir)
{
  for (int i = 0; i < 2; i += 1)
  {
    int err = lfs_alloc(lfs, &dir->pair[(i + 1) % 2]);
    if (err)
    {
      return err;
    }
  }

  dir->rev = 0;
  int err = lfs_bd_read(lfs, 0, &lfs->rcache, sizeof(dir->rev), dir->pair[0], 0, &dir->rev, sizeof(dir->rev));
  dir->rev = lfs_fromle32(dir->rev);
  if (err && (err != LFS_ERR_CORRUPT))
  {
    return err;
  }
  if (lfs->cfg->block_cycles > 0)
  {
    dir->rev = lfs_alignup(dir->rev, (lfs->cfg->block_cycles + 1) | 1);
  }
  dir->off = sizeof(dir->rev);
  dir->etag = 0xffffffff;
  dir->count = 0;
  dir->tail[0] = (lfs_block_t) (-1);
  dir->tail[1] = (lfs_block_t) (-1);
  dir->erased = 0;
  dir->split = 0;
  return 0;
}

static int lfs_dir_drop(lfs_t *lfs, lfs_mdir_t *dir, lfs_mdir_t *tail)
{
  int err = lfs_dir_getgstate(lfs, tail, &lfs->gdelta);
  if (err)
  {
    return err;
  }
  lfs_pair_tole32(tail->tail);
  err = lfs_dir_commit(lfs, dir, (struct lfs_mattr []){{((((lfs_tag_t) (LFS_TYPE_TAIL + tail->split)) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 8), tail->tail}}, (sizeof((struct lfs_mattr []){{((((lfs_tag_t) (LFS_TYPE_TAIL + tail->split)) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 8), tail->tail}})) / (sizeof(struct lfs_mattr)));
  lfs_pair_fromle32(tail->tail);
  if (err)
  {
    return err;
  }
  return 0;
}

static int lfs_dir_split(lfs_t *lfs, lfs_mdir_t *dir, const struct lfs_mattr *attrs, int attrcount, lfs_mdir_t *source, uint16_t split, uint16_t end)
{
  lfs_mdir_t tail;
  int err = lfs_dir_alloc(lfs, &tail);
  if (err)
  {
    return err;
  }
  tail.split = dir->split;
  tail.tail[0] = dir->tail[0];
  tail.tail[1] = dir->tail[1];
  int res = lfs_dir_compact(lfs, &tail, attrs, attrcount, source, split, end);
  if (res < 0)
  {
    return res;
  }
  dir->tail[0] = tail.pair[0];
  dir->tail[1] = tail.pair[1];
  dir->split = 1;
  if ((lfs_pair_cmp(dir->pair, lfs->root) == 0) && (split == 0))
  {
    lfs->root[0] = tail.pair[0];
    lfs->root[1] = tail.pair[1];
  }
  return 0;
}

static int lfs_dir_commit_size(void *p, lfs_tag_t tag, const void *buffer)
{
  lfs_size_t *size = p;
  (void) buffer;
  *size += lfs_tag_dsize(tag);
  return 0;
}

struct lfs_dir_commit_commit
{
  lfs_t *lfs;
  struct lfs_commit *commit;
};
static int lfs_dir_commit_commit(void *p, lfs_tag_t tag, const void *buffer)
{
  struct lfs_dir_commit_commit *commit = p;
  return lfs_dir_commitattr(commit->lfs, commit->commit, tag, buffer);
}

static bool lfs_dir_needsrelocation(lfs_t *lfs, lfs_mdir_t *dir)
{
  return (lfs->cfg->block_cycles > 0) && (((dir->rev + 1) % ((lfs->cfg->block_cycles + 1) | 1)) == 0);
}

static int lfs_dir_compact(lfs_t *lfs, lfs_mdir_t *dir, const struct lfs_mattr *attrs, int attrcount, lfs_mdir_t *source, uint16_t begin, uint16_t end)
{
  bool relocated = 0;
  bool tired = lfs_dir_needsrelocation(lfs, dir);
  dir->rev += 1;
  if (tired && (lfs_pair_cmp(dir->pair, (const lfs_block_t [2]){0, 1}) != 0))
  {
    goto relocate;
  }
  while (1)
  {
    helper_lfs_dir_compact_1(&relocated, &tired, lfs, dir, attrs, attrcount, source, begin, end);
  }

  return (relocated) ? (LFS_OK_RELOCATED) : (0);
}

static int lfs_dir_splittingcompact(lfs_t *lfs, lfs_mdir_t *dir, const struct lfs_mattr *attrs, int attrcount, lfs_mdir_t *source, uint16_t begin, uint16_t end)
{
  while (1)
  {
    helper_lfs_dir_splittingcompact_2(&end, lfs, dir, attrs, attrcount, source, begin);
  }

  if (lfs_dir_needsrelocation(lfs, dir) && (lfs_pair_cmp(dir->pair, (const lfs_block_t [2]){0, 1}) == 0))
  {
    helper_lfs_dir_splittingcompact_1(&end, lfs, dir, attrs, attrcount, source, begin);
  }
  return lfs_dir_compact(lfs, dir, attrs, attrcount, source, begin, end);
}

static int lfs_dir_relocatingcommit(lfs_t *lfs, lfs_mdir_t *dir, const lfs_block_t pair[2], const struct lfs_mattr *attrs, int attrcount, lfs_mdir_t *pdir)
{
  int state = 0;
  bool hasdelete = 0;
  for (int i = 0; i < attrcount; i += 1)
  {
    if (lfs_tag_type3(attrs[i].tag) == LFS_TYPE_CREATE)
    {
      dir->count += 1;
    }
    else
      if (lfs_tag_type3(attrs[i].tag) == LFS_TYPE_DELETE)
    {
      assert(dir->count > 0);
      dir->count -= 1;
      hasdelete = 1;
    }
    else
      if (lfs_tag_type1(attrs[i].tag) == LFS_TYPE_TAIL)
    {
      dir->tail[0] = ((lfs_block_t *) attrs[i].buffer)[0];
      dir->tail[1] = ((lfs_block_t *) attrs[i].buffer)[1];
      dir->split = lfs_tag_chunk(attrs[i].tag) & 1;
      lfs_pair_fromle32(dir->tail);
    }
  }

  if (hasdelete && (dir->count == 0))
  {
    assert(pdir);
    int err = lfs_fs_pred(lfs, dir->pair, pdir);
    if (err && (err != LFS_ERR_NOENT))
    {
      return err;
    }
    if ((err != LFS_ERR_NOENT) && pdir->split)
    {
      state = LFS_OK_DROPPED;
      goto fixmlist;
    }
  }
  if (dir->erased && (dir->count < 0xff))
  {
    helper_lfs_dir_relocatingcommit_2(lfs, dir, attrs, attrcount);
  }
  compact:
  lfs_cache_drop(lfs, &lfs->pcache);

  state = lfs_dir_splittingcompact(lfs, dir, attrs, attrcount, dir, 0, dir->count);
  if (state < 0)
  {
    return state;
  }
  goto fixmlist;
  fixmlist:
  ;

  lfs_block_t oldpair[2] = {pair[0], pair[1]};
  for (struct lfs_mlist *d = lfs->mlist; d; d_idx = d_idx->next)
  {
    helper_lfs_dir_relocatingcommit_1(lfs, dir, pair, attrs, attrcount, oldpair, d);
  }

  unsigned int d_idx = 0;
  return state;
}

static int lfs_dir_orphaningcommit(lfs_t *lfs, lfs_mdir_t *dir, const struct lfs_mattr *attrs, int attrcount)
{
  for (lfs_file_t *f = (lfs_file_t *) lfs->mlist; f; f_idx = f_idx->next)
  {
    if (((((dir != (&f->m)) && (lfs_pair_cmp(f->m.pair, dir->pair) == 0)) && (f->type == LFS_TYPE_REG)) && (f->flags & LFS_F_INLINE)) && (f->ctz.size > lfs->cfg->cache_size))
    {
      int err = lfs_file_outline(lfs, f);
      if (err)
      {
        return err;
      }
      err = lfs_file_flush(lfs, f);
      if (err)
      {
        return err;
      }
    }
  }

  unsigned int f_idx = 0;
  lfs_block_t lpair[2] = {dir->pair[0], dir->pair[1]};
  lfs_mdir_t ldir = *dir;
  lfs_mdir_t pdir;
  int state = lfs_dir_relocatingcommit(lfs, &ldir, dir->pair, attrs, attrcount, &pdir);
  if (state < 0)
  {
    return state;
  }
  if (lfs_pair_cmp(dir->pair, lpair) == 0)
  {
    *dir = ldir;
  }
  if (state == LFS_OK_DROPPED)
  {
    helper_lfs_dir_orphaningcommit_1(&ldir, &state, lfs, dir, lpair, pdir);
  }
  bool orphans = 0;
  while (state == LFS_OK_RELOCATED)
  {
    helper_lfs_dir_orphaningcommit_2(&ldir, &state, &orphans, &d_idx, lfs, lpair, pdir);
  }

  return (orphans) ? (LFS_OK_ORPHANED) : (0);
}

static int lfs_dir_commit(lfs_t *lfs, lfs_mdir_t *dir, const struct lfs_mattr *attrs, int attrcount)
{
  int orphans = lfs_dir_orphaningcommit(lfs, dir, attrs, attrcount);
  if (orphans < 0)
  {
    return orphans;
  }
  if (orphans)
  {
    int err = lfs_fs_deorphan(lfs, 0);
    if (err)
    {
      return err;
    }
  }
  return 0;
}

static int lfs_mkdir_(lfs_t *lfs, const char *path)
{
  int err = lfs_fs_forceconsistency(lfs);
  if (err)
  {
    return err;
  }
  struct lfs_mlist cwd;
  cwd.next = lfs->mlist;
  uint16_t id;
  err = lfs_dir_find(lfs, &cwd.m, &path, &id);
  if (!((err == LFS_ERR_NOENT) && lfs_path_islast(path)))
  {
    return (err < 0) ? (err) : (LFS_ERR_EXIST);
  }
  lfs_size_t nlen = lfs_path_namelen(path);
  if (nlen > lfs->name_max)
  {
    return LFS_ERR_NAMETOOLONG;
  }
  lfs_alloc_ckpoint(lfs);
  lfs_mdir_t dir;
  err = lfs_dir_alloc(lfs, &dir);
  if (err)
  {
    return err;
  }
  lfs_mdir_t pred = cwd.m;
  while (pred.split)
  {
    err = lfs_dir_fetch(lfs, &pred, pred.tail);
    if (err)
    {
      return err;
    }
  }

  lfs_pair_tole32(pred.tail);
  err = lfs_dir_commit(lfs, &dir, (struct lfs_mattr []){{((((lfs_tag_t) LFS_TYPE_SOFTTAIL) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 8), pred.tail}}, (sizeof((struct lfs_mattr []){{((((lfs_tag_t) LFS_TYPE_SOFTTAIL) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 8), pred.tail}})) / (sizeof(struct lfs_mattr)));
  lfs_pair_fromle32(pred.tail);
  if (err)
  {
    return err;
  }
  if (cwd.m.split)
  {
    helper_lfs_mkdir__1(&err, &cwd, lfs, dir, pred);
  }
  lfs_pair_tole32(dir.pair);
  err = lfs_dir_commit(lfs, &cwd.m, (struct lfs_mattr []){{((((lfs_tag_t) LFS_TYPE_CREATE) << 20) | (((lfs_tag_t) id) << 10)) | ((lfs_tag_t) 0), 0}, {((((lfs_tag_t) LFS_TYPE_DIR) << 20) | (((lfs_tag_t) id) << 10)) | ((lfs_tag_t) nlen), path}, {((((lfs_tag_t) LFS_TYPE_DIRSTRUCT) << 20) | (((lfs_tag_t) id) << 10)) | ((lfs_tag_t) 8), dir.pair}, {(!cwd.m.split) ? (((((lfs_tag_t) LFS_TYPE_SOFTTAIL) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 8)) : (((((lfs_tag_t) LFS_FROM_NOOP) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 0)), dir.pair}}, (sizeof((struct lfs_mattr []){{((((lfs_tag_t) LFS_TYPE_CREATE) << 20) | (((lfs_tag_t) id) << 10)) | ((lfs_tag_t) 0), 0}, {((((lfs_tag_t) LFS_TYPE_DIR) << 20) | (((lfs_tag_t) id) << 10)) | ((lfs_tag_t) nlen), path}, {((((lfs_tag_t) LFS_TYPE_DIRSTRUCT) << 20) | (((lfs_tag_t) id) << 10)) | ((lfs_tag_t) 8), dir.pair}, {(!cwd.m.split) ? (((((lfs_tag_t) LFS_TYPE_SOFTTAIL) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 8)) : (((((lfs_tag_t) LFS_FROM_NOOP) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 0)), dir.pair}})) / (sizeof(struct lfs_mattr)));
  lfs_pair_fromle32(dir.pair);
  if (err)
  {
    return err;
  }
  return 0;
}

static int lfs_dir_open_(lfs_t *lfs, lfs_dir_t *dir, const char *path)
{
  lfs_stag_t tag = lfs_dir_find(lfs, &dir->m, &path, 0);
  if (tag < 0)
  {
    return tag;
  }
  if (lfs_tag_type3(tag) != LFS_TYPE_DIR)
  {
    return LFS_ERR_NOTDIR;
  }
  lfs_block_t pair[2];
  if (lfs_tag_id(tag) == 0x3ff)
  {
    pair[0] = lfs->root[0];
    pair[1] = lfs->root[1];
  }
  else
  {
    lfs_stag_t res = lfs_dir_get(lfs, &dir->m, ((((lfs_tag_t) 0x700) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 0), ((((lfs_tag_t) LFS_TYPE_STRUCT) << 20) | (((lfs_tag_t) lfs_tag_id(tag)) << 10)) | ((lfs_tag_t) 8), pair);
    if (res < 0)
    {
      return res;
    }
    lfs_pair_fromle32(pair);
  }
  int err = lfs_dir_fetch(lfs, &dir->m, pair);
  if (err)
  {
    return err;
  }
  dir->head[0] = dir->m.pair[0];
  dir->head[1] = dir->m.pair[1];
  dir->id = 0;
  dir->pos = 0;
  dir->type = LFS_TYPE_DIR;
  lfs_mlist_append(lfs, (struct lfs_mlist *) dir);
  return 0;
}

static int lfs_dir_close_(lfs_t *lfs, lfs_dir_t *dir)
{
  lfs_mlist_remove(lfs, (struct lfs_mlist *) dir);
  return 0;
}

static int lfs_dir_read_(lfs_t *lfs, lfs_dir_t *dir, struct lfs_info *info)
{
  memset(info, 0, sizeof(*info));
  if (dir->pos == 0)
  {
    info->type = LFS_TYPE_DIR;
    strcpy(info->name, ".");
    dir->pos += 1;
    return 1;
  }
  else
    if (dir->pos == 1)
  {
    info->type = LFS_TYPE_DIR;
    strcpy(info->name, "..");
    dir->pos += 1;
    return 1;
  }
  while (1)
  {
    if (dir->id == dir->m.count)
    {
      if (!dir->m.split)
      {
        return 0;
      }
      int err = lfs_dir_fetch(lfs, &dir->m, dir->m.tail);
      if (err)
      {
        return err;
      }
      dir->id = 0;
    }
    int err = lfs_dir_getinfo(lfs, &dir->m, dir->id, info);
    if (err && (err != LFS_ERR_NOENT))
    {
      return err;
    }
    dir->id += 1;
    if (err != LFS_ERR_NOENT)
    {
      break;
    }
  }

  dir->pos += 1;
  return 1;
}

static int lfs_dir_seek_(lfs_t *lfs, lfs_dir_t *dir, lfs_off_t off)
{
  int err = lfs_dir_rewind_(lfs, dir);
  if (err)
  {
    return err;
  }
  dir->pos = lfs_min(2, off);
  off -= dir->pos;
  dir->id = (off > 0) && (lfs_pair_cmp(dir->head, lfs->root) == 0);
  while (off > 0)
  {
    if (dir->id == dir->m.count)
    {
      if (!dir->m.split)
      {
        return LFS_ERR_INVAL;
      }
      err = lfs_dir_fetch(lfs, &dir->m, dir->m.tail);
      if (err)
      {
        return err;
      }
      dir->id = 0;
    }
    int diff = lfs_min(dir->m.count - dir->id, off);
    dir->id += diff;
    dir->pos += diff;
    off -= diff;
  }

  return 0;
}

static lfs_soff_t lfs_dir_tell_(lfs_t *lfs, lfs_dir_t *dir)
{
  (void) lfs;
  return dir->pos;
}

static int lfs_dir_rewind_(lfs_t *lfs, lfs_dir_t *dir)
{
  int err = lfs_dir_fetch(lfs, &dir->m, dir->head);
  if (err)
  {
    return err;
  }
  dir->id = 0;
  dir->pos = 0;
  return 0;
}

static int lfs_ctz_index(lfs_t *lfs, lfs_off_t *off)
{
  lfs_off_t size = *off;
  lfs_off_t b = lfs->cfg->block_size - (2 * 4);
  lfs_off_t i = size / b;
  if (i == 0)
  {
    return 0;
  }
  i = (size - (4 * (lfs_popc(i - 1) + 2))) / b;
  *off = (size - (b * i)) - (4 * lfs_popc(i));
  return i;
}

static int lfs_ctz_find(lfs_t *lfs, const lfs_cache_t *pcache, lfs_cache_t *rcache, lfs_block_t head, lfs_size_t size, lfs_size_t pos, lfs_block_t *block, lfs_off_t *off)
{
  if (size == 0)
  {
    *block = (lfs_block_t) (-1);
    *off = 0;
    return 0;
  }
  lfs_off_t current = lfs_ctz_index(lfs, &((lfs_off_t){size - 1}));
  lfs_off_t target = lfs_ctz_index(lfs, &pos);
  while (current > target)
  {
    lfs_size_t skip = lfs_min(lfs_npw2((current - target) + 1) - 1, lfs_ctz(current));
    int err = lfs_bd_read(lfs, pcache, rcache, sizeof(head), head, 4 * skip, &head, sizeof(head));
    head = lfs_fromle32(head);
    if (err)
    {
      return err;
    }
    current -= 1 << skip;
  }

  *block = head;
  *off = pos;
  return 0;
}

static int lfs_ctz_extend(lfs_t *lfs, lfs_cache_t *pcache, lfs_cache_t *rcache, lfs_block_t head, lfs_size_t size, lfs_block_t *block, lfs_off_t *off)
{
  while (1)
  {
    helper_lfs_ctz_extend_1(lfs, pcache, rcache, head, size, block, off);
  }

}

static int lfs_ctz_traverse(lfs_t *lfs, const lfs_cache_t *pcache, lfs_cache_t *rcache, lfs_block_t head, lfs_size_t size, int (*cb)(void *, lfs_block_t), void *data)
{
  if (size == 0)
  {
    return 0;
  }
  lfs_off_t index = lfs_ctz_index(lfs, &((lfs_off_t){size - 1}));
  while (1)
  {
    int err = cb(data, head);
    if (err)
    {
      return err;
    }
    if (index == 0)
    {
      return 0;
    }
    lfs_block_t heads[2];
    int count = 2 - (index & 1);
    err = lfs_bd_read(lfs, pcache, rcache, count * (sizeof(head)), head, 0, &heads, count * (sizeof(head)));
    heads[0] = lfs_fromle32(heads[0]);
    heads[1] = lfs_fromle32(heads[1]);
    if (err)
    {
      return err;
    }
    for (int i = 0; i < (count - 1); i += 1)
    {
      err = cb(data, heads[i]);
      if (err)
      {
        return err;
      }
    }

    head = heads[count - 1];
    index -= count;
  }

}

static int lfs_file_opencfg_(lfs_t *lfs, lfs_file_t *file, const char *path, int flags, const struct lfs_file_config *cfg)
{
  if ((flags & LFS_O_WRONLY) == LFS_O_WRONLY)
  {
    int err = lfs_fs_forceconsistency(lfs);
    if (err)
    {
      return err;
    }
  }
  int err;
  file->cfg = cfg;
  file->flags = flags;
  file->pos = 0;
  file->off = 0;
  file->cache.buffer = 0;
  lfs_stag_t tag = lfs_dir_find(lfs, &file->m, &path, &file->id);
  if ((tag < 0) && (!((tag == LFS_ERR_NOENT) && lfs_path_islast(path))))
  {
    err = tag;
    goto cleanup;
  }
  file->type = LFS_TYPE_REG;
  lfs_mlist_append(lfs, (struct lfs_mlist *) file);
  if (tag == LFS_ERR_NOENT)
  {
    helper_lfs_file_opencfg__2(&err, &err, &tag, lfs, file, path, flags);
  }
  else
    if (flags & LFS_O_EXCL)
  {
    err = LFS_ERR_EXIST;
    goto cleanup;
  }
  else
    if (lfs_tag_type3(tag) != LFS_TYPE_REG)
  {
    err = LFS_ERR_ISDIR;
    goto cleanup;
  }
  else
    if (flags & LFS_O_TRUNC)
  {
    tag = ((((lfs_tag_t) LFS_TYPE_INLINESTRUCT) << 20) | (((lfs_tag_t) file->id) << 10)) | ((lfs_tag_t) 0);
    file->flags |= LFS_F_DIRTY;
  }
  else
  {
    tag = lfs_dir_get(lfs, &file->m, ((((lfs_tag_t) 0x700) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 0), ((((lfs_tag_t) LFS_TYPE_STRUCT) << 20) | (((lfs_tag_t) file->id) << 10)) | ((lfs_tag_t) 8), &file->ctz);
    if (tag < 0)
    {
      err = tag;
      goto cleanup;
    }
    lfs_ctz_fromle32(&file->ctz);
  }
  for (unsigned i = 0; i < file->cfg->attr_count; i += 1)
  {
    if ((file->flags & LFS_O_RDONLY) == LFS_O_RDONLY)
    {
      lfs_stag_t res = lfs_dir_get(lfs, &file->m, ((((lfs_tag_t) 0x7ff) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 0), ((((lfs_tag_t) (LFS_TYPE_USERATTR + file->cfg->attrs[i].type)) << 20) | (((lfs_tag_t) file->id) << 10)) | ((lfs_tag_t) file->cfg->attrs[i].size), file->cfg->attrs[i].buffer);
      if ((res < 0) && (res != LFS_ERR_NOENT))
      {
        err = res;
        goto cleanup;
      }
    }
    if ((file->flags & LFS_O_WRONLY) == LFS_O_WRONLY)
    {
      if (file->cfg->attrs[i].size > lfs->attr_max)
      {
        err = LFS_ERR_NOSPC;
        goto cleanup;
      }
      file->flags |= LFS_F_DIRTY;
    }
  }

  if (file->cfg->buffer)
  {
    file->cache.buffer = file->cfg->buffer;
  }
  else
  {
    file->cache.buffer = lfs_malloc(lfs->cfg->cache_size);
    if (!file->cache.buffer)
    {
      err = LFS_ERR_NOMEM;
      goto cleanup;
    }
  }
  lfs_cache_zero(lfs, &file->cache);
  if (lfs_tag_type3(tag) == LFS_TYPE_INLINESTRUCT)
  {
    helper_lfs_file_opencfg__1(&err, &err, lfs, file, tag);
  }
  return 0;
  cleanup:
  file->flags |= LFS_F_ERRED;

  lfs_file_close_(lfs, file);
  return err;
}

static int lfs_file_open_(lfs_t *lfs, lfs_file_t *file, const char *path, int flags)
{
  static const struct lfs_file_config defaults = {0};
  int err = lfs_file_opencfg_(lfs, file, path, flags, &defaults);
  return err;
}

static int lfs_file_close_(lfs_t *lfs, lfs_file_t *file)
{
  int err = lfs_file_sync_(lfs, file);
  lfs_mlist_remove(lfs, (struct lfs_mlist *) file);
  if (!file->cfg->buffer)
  {
    lfs_free(file->cache.buffer);
  }
  return err;
}

static int lfs_file_relocate(lfs_t *lfs, lfs_file_t *file)
{
  while (1)
  {
    helper_lfs_file_relocate_1(lfs, file);
  }

}

static int lfs_file_outline(lfs_t *lfs, lfs_file_t *file)
{
  file->off = file->pos;
  lfs_alloc_ckpoint(lfs);
  int err = lfs_file_relocate(lfs, file);
  if (err)
  {
    return err;
  }
  file->flags &= ~LFS_F_INLINE;
  return 0;
}

static int lfs_file_flush(lfs_t *lfs, lfs_file_t *file)
{
  if (file->flags & LFS_F_READING)
  {
    if (!(file->flags & LFS_F_INLINE))
    {
      lfs_cache_drop(lfs, &file->cache);
    }
    file->flags &= ~LFS_F_READING;
  }
  if (file->flags & LFS_F_WRITING)
  {
    helper_lfs_file_flush_1(lfs, file);
  }
  return 0;
}

static int lfs_file_sync_(lfs_t *lfs, lfs_file_t *file)
{
  if (file->flags & LFS_F_ERRED)
  {
    return 0;
  }
  int err = lfs_file_flush(lfs, file);
  if (err)
  {
    file->flags |= LFS_F_ERRED;
    return err;
  }
  if ((file->flags & LFS_F_DIRTY) && (!lfs_pair_isnull(file->m.pair)))
  {
    helper_lfs_file_sync__1(&err, lfs, file);
  }
  return 0;
}

static lfs_ssize_t lfs_file_flushedread(lfs_t *lfs, lfs_file_t *file, void *buffer, lfs_size_t size)
{
  uint8_t *data = buffer;
  unsigned int data_idx = 0;
  lfs_size_t nsize = size;
  if (file->pos >= file->ctz.size)
  {
    return 0;
  }
  size = lfs_min(size, file->ctz.size - file->pos);
  nsize = size;
  while (nsize > 0)
  {
    if ((!(file->flags & LFS_F_READING)) || (file->off == lfs->cfg->block_size))
    {
      if (!(file->flags & LFS_F_INLINE))
      {
        int err = lfs_ctz_find(lfs, 0, &file->cache, file->ctz.head, file->ctz.size, file->pos, &file->block, &file->off);
        if (err)
        {
          return err;
        }
      }
      else
      {
        file->block = (lfs_block_t) (-2);
        file->off = file->pos;
      }
      file->flags |= LFS_F_READING;
    }
    lfs_size_t diff = lfs_min(nsize, lfs->cfg->block_size - file->off);
    if (file->flags & LFS_F_INLINE)
    {
      int err = lfs_dir_getread(lfs, &file->m, 0, &file->cache, lfs->cfg->block_size, ((((lfs_tag_t) 0xfff) << 20) | (((lfs_tag_t) 0x1ff) << 10)) | ((lfs_tag_t) 0), ((((lfs_tag_t) LFS_TYPE_INLINESTRUCT) << 20) | (((lfs_tag_t) file->id) << 10)) | ((lfs_tag_t) 0), file->off, data, diff);
      if (err)
      {
        return err;
      }
    }
    else
    {
      int err = lfs_bd_read(lfs, 0, &file->cache, lfs->cfg->block_size, file->block, file->off, data, diff);
      if (err)
      {
        return err;
      }
    }
    file->pos += diff;
    file->off += diff;
    data_idx += diff;
    nsize -= diff;
  }

  return size;
}

static lfs_ssize_t lfs_file_read_(lfs_t *lfs, lfs_file_t *file, void *buffer, lfs_size_t size)
{
  assert((file->flags & LFS_O_RDONLY) == LFS_O_RDONLY);
  if (file->flags & LFS_F_WRITING)
  {
    int err = lfs_file_flush(lfs, file);
    if (err)
    {
      return err;
    }
  }
  return lfs_file_flushedread(lfs, file, buffer, size);
}

static lfs_ssize_t lfs_file_flushedwrite(lfs_t *lfs, lfs_file_t *file, const void *buffer, lfs_size_t size)
{
  const uint8_t *data = buffer;
  unsigned int data_idx = 0;
  lfs_size_t nsize = size;
  if ((file->flags & LFS_F_INLINE) && (lfs_max(file->pos + nsize, file->ctz.size) > lfs->inline_max))
  {
    int err = lfs_file_outline(lfs, file);
    if (err)
    {
      file->flags |= LFS_F_ERRED;
      return err;
    }
  }
  while (nsize > 0)
  {
    helper_lfs_file_flushedwrite_1(&data_idx, &nsize, lfs, file, data);
  }

  return size;
}

static lfs_ssize_t lfs_file_write_(lfs_t *lfs, lfs_file_t *file, const void *buffer, lfs_size_t size)
{
  assert((file->flags & LFS_O_WRONLY) == LFS_O_WRONLY);
  if (file->flags & LFS_F_READING)
  {
    int err = lfs_file_flush(lfs, file);
    if (err)
    {
      return err;
    }
  }
  if ((file->flags & LFS_O_APPEND) && (file->pos < file->ctz.size))
  {
    file->pos = file->ctz.size;
  }
  if ((file->pos + size) > lfs->file_max)
  {
    return LFS_ERR_FBIG;
  }
  if ((!(file->flags & LFS_F_WRITING)) && (file->pos > file->ctz.size))
  {
    lfs_off_t pos = file->pos;
    file->pos = file->ctz.size;
    while (file->pos < pos)
    {
      lfs_ssize_t res = lfs_file_flushedwrite(lfs, file, &((uint8_t){0}), 1);
      if (res < 0)
      {
        return res;
      }
    }

  }
  lfs_ssize_t nsize = lfs_file_flushedwrite(lfs, file, buffer, size);
  if (nsize < 0)
  {
    return nsize;
  }
  file->flags &= ~LFS_F_ERRED;
  return nsize;
}

static lfs_soff_t lfs_file_seek_(lfs_t *lfs, lfs_file_t *file, lfs_soff_t off, int whence)
{
  lfs_off_t npos = file->pos;
  if (whence == LFS_SEEK_SET)
  {
    npos = off;
  }
  else
    if (whence == LFS_SEEK_CUR)
  {
    npos = file->pos + ((lfs_off_t) off);
  }
  else
    if (whence == LFS_SEEK_END)
  {
    npos = ((lfs_off_t) lfs_file_size_(lfs, file)) + ((lfs_off_t) off);
  }
  if (npos > lfs->file_max)
  {
    return LFS_ERR_INVAL;
  }
  if (file->pos == npos)
  {
    return npos;
  }
  if ((file->flags & LFS_F_READING) && (file->off != lfs->cfg->block_size))
  {
    int oindex = lfs_ctz_index(lfs, &((lfs_off_t){file->pos}));
    lfs_off_t noff = npos;
    int nindex = lfs_ctz_index(lfs, &noff);
    if (((oindex == nindex) && (noff >= file->cache.off)) && (noff < (file->cache.off + file->cache.size)))
    {
      file->pos = npos;
      file->off = noff;
      return npos;
    }
  }
  int err = lfs_file_flush(lfs, file);
  if (err)
  {
    return err;
  }
  file->pos = npos;
  return npos;
}

static int lfs_file_truncate_(lfs_t *lfs, lfs_file_t *file, lfs_off_t size)
{
  assert((file->flags & LFS_O_WRONLY) == LFS_O_WRONLY);
  if (size > 2147483647)
  {
    return LFS_ERR_INVAL;
  }
  lfs_off_t pos = file->pos;
  lfs_off_t oldsize = lfs_file_size_(lfs, file);
  if (size < oldsize)
  {
    helper_lfs_file_truncate__1(&size, lfs, file);
  }
  else
    if (size > oldsize)
  {
    lfs_soff_t res = lfs_file_seek_(lfs, file, 0, LFS_SEEK_END);
    if (res < 0)
    {
      return (int) res;
    }
    while (file->pos < size)
    {
      res = lfs_file_write_(lfs, file, &((uint8_t){0}), 1);
      if (res < 0)
      {
        return (int) res;
      }
    }

  }
  lfs_soff_t res = lfs_file_seek_(lfs, file, pos, LFS_SEEK_SET);
  if (res < 0)
  {
    return (int) res;
  }
  return 0;
}

static lfs_soff_t lfs_file_tell_(lfs_t *lfs, lfs_file_t *file)
{
  (void) lfs;
  return file->pos;
}

static int lfs_file_rewind_(lfs_t *lfs, lfs_file_t *file)
{
  lfs_soff_t res = lfs_file_seek_(lfs, file, 0, LFS_SEEK_SET);
  if (res < 0)
  {
    return (int) res;
  }
  return 0;
}

static lfs_soff_t lfs_file_size_(lfs_t *lfs, lfs_file_t *file)
{
  (void) lfs;
  if (file->flags & LFS_F_WRITING)
  {
    return lfs_max(file->pos, file->ctz.size);
  }
  return file->ctz.size;
}

static int lfs_stat_(lfs_t *lfs, const char *path, struct lfs_info *info)
{
  lfs_mdir_t cwd;
  lfs_stag_t tag = lfs_dir_find(lfs, &cwd, &path, 0);
  if (tag < 0)
  {
    return (int) tag;
  }
  if ((strchr(path, '/') != 0) && (lfs_tag_type3(tag) != LFS_TYPE_DIR))
  {
    return LFS_ERR_NOTDIR;
  }
  return lfs_dir_getinfo(lfs, &cwd, lfs_tag_id(tag), info);
}

static int lfs_remove_(lfs_t *lfs, const char *path)
{
  int err = lfs_fs_forceconsistency(lfs);
  if (err)
  {
    return err;
  }
  lfs_mdir_t cwd;
  lfs_stag_t tag = lfs_dir_find(lfs, &cwd, &path, 0);
  if ((tag < 0) || (lfs_tag_id(tag) == 0x3ff))
  {
    return (tag < 0) ? ((int) tag) : (LFS_ERR_INVAL);
  }
  struct lfs_mlist dir;
  dir.next = lfs->mlist;
  if (lfs_tag_type3(tag) == LFS_TYPE_DIR)
  {
    helper_lfs_remove__1(&err, &dir, lfs, cwd, tag);
  }
  err = lfs_dir_commit(lfs, &cwd, (struct lfs_mattr []){{((((lfs_tag_t) LFS_TYPE_DELETE) << 20) | (((lfs_tag_t) lfs_tag_id(tag)) << 10)) | ((lfs_tag_t) 0), 0}}, (sizeof((struct lfs_mattr []){{((((lfs_tag_t) LFS_TYPE_DELETE) << 20) | (((lfs_tag_t) lfs_tag_id(tag)) << 10)) | ((lfs_tag_t) 0), 0}})) / (sizeof(struct lfs_mattr)));
  if (err)
  {
    lfs->mlist = dir.next;
    return err;
  }
  lfs->mlist = dir.next;
  if (lfs_gstate_hasorphans(&lfs->gstate))
  {
    assert(lfs_tag_type3(tag) == LFS_TYPE_DIR);
    err = lfs_fs_preporphans(lfs, -1);
    if (err)
    {
      return err;
    }
    err = lfs_fs_pred(lfs, dir.m.pair, &cwd);
    if (err)
    {
      return err;
    }
    err = lfs_dir_drop(lfs, &cwd, &dir.m);
    if (err)
    {
      return err;
    }
  }
  return 0;
}

static int lfs_rename_(lfs_t *lfs, const char *oldpath, const char *newpath)
{
  int err = lfs_fs_forceconsistency(lfs);
  if (err)
  {
    return err;
  }
  lfs_mdir_t oldcwd;
  lfs_stag_t oldtag = lfs_dir_find(lfs, &oldcwd, &oldpath, 0);
  if ((oldtag < 0) || (lfs_tag_id(oldtag) == 0x3ff))
  {
    return (oldtag < 0) ? ((int) oldtag) : (LFS_ERR_INVAL);
  }
  lfs_mdir_t newcwd;
  uint16_t newid;
  lfs_stag_t prevtag = lfs_dir_find(lfs, &newcwd, &newpath, &newid);
  if (((prevtag < 0) || (lfs_tag_id(prevtag) == 0x3ff)) && (!((prevtag == LFS_ERR_NOENT) && lfs_path_islast(newpath))))
  {
    return (prevtag < 0) ? ((int) prevtag) : (LFS_ERR_INVAL);
  }
  bool samepair = lfs_pair_cmp(oldcwd.pair, newcwd.pair) == 0;
  uint16_t newoldid = lfs_tag_id(oldtag);
  struct lfs_mlist prevdir;
  prevdir.next = lfs->mlist;
  if (prevtag == LFS_ERR_NOENT)
  {
    if (lfs_path_isdir(newpath) && (lfs_tag_type3(oldtag) != LFS_TYPE_DIR))
    {
      return LFS_ERR_NOTDIR;
    }
    lfs_size_t nlen = lfs_path_namelen(newpath);
    if (nlen > lfs->name_max)
    {
      return LFS_ERR_NAMETOOLONG;
    }
    if (samepair && (newid <= newoldid))
    {
      newoldid += 1;
    }
  }
  else
    if (lfs_tag_type3(prevtag) != lfs_tag_type3(oldtag))
  {
    return (lfs_tag_type3(prevtag) == LFS_TYPE_DIR) ? (LFS_ERR_ISDIR) : (LFS_ERR_NOTDIR);
  }
  else
    if (samepair && (newid == newoldid))
  {
    return 0;
  }
  else
    if (lfs_tag_type3(prevtag) == LFS_TYPE_DIR)
  {
    helper_lfs_rename__1(&err, &prevdir, lfs, newcwd, newid);
  }
  if (!samepair)
  {
    lfs_fs_prepmove(lfs, newoldid, oldcwd.pair);
  }
  err = lfs_dir_commit(lfs, &newcwd, (struct lfs_mattr []){{(prevtag != LFS_ERR_NOENT) ? (((((lfs_tag_t) LFS_TYPE_DELETE) << 20) | (((lfs_tag_t) newid) << 10)) | ((lfs_tag_t) 0)) : (((((lfs_tag_t) LFS_FROM_NOOP) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 0)), 0}, {((((lfs_tag_t) LFS_TYPE_CREATE) << 20) | (((lfs_tag_t) newid) << 10)) | ((lfs_tag_t) 0), 0}, {((((lfs_tag_t) lfs_tag_type3(oldtag)) << 20) | (((lfs_tag_t) newid) << 10)) | ((lfs_tag_t) lfs_path_namelen(newpath)), newpath}, {((((lfs_tag_t) LFS_FROM_MOVE) << 20) | (((lfs_tag_t) newid) << 10)) | ((lfs_tag_t) lfs_tag_id(oldtag)), &oldcwd}, {(samepair) ? (((((lfs_tag_t) LFS_TYPE_DELETE) << 20) | (((lfs_tag_t) newoldid) << 10)) | ((lfs_tag_t) 0)) : (((((lfs_tag_t) LFS_FROM_NOOP) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 0)), 0}}, (sizeof((struct lfs_mattr []){{(prevtag != LFS_ERR_NOENT) ? (((((lfs_tag_t) LFS_TYPE_DELETE) << 20) | (((lfs_tag_t) newid) << 10)) | ((lfs_tag_t) 0)) : (((((lfs_tag_t) LFS_FROM_NOOP) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 0)), 0}, {((((lfs_tag_t) LFS_TYPE_CREATE) << 20) | (((lfs_tag_t) newid) << 10)) | ((lfs_tag_t) 0), 0}, {((((lfs_tag_t) lfs_tag_type3(oldtag)) << 20) | (((lfs_tag_t) newid) << 10)) | ((lfs_tag_t) lfs_path_namelen(newpath)), newpath}, {((((lfs_tag_t) LFS_FROM_MOVE) << 20) | (((lfs_tag_t) newid) << 10)) | ((lfs_tag_t) lfs_tag_id(oldtag)), &oldcwd}, {(samepair) ? (((((lfs_tag_t) LFS_TYPE_DELETE) << 20) | (((lfs_tag_t) newoldid) << 10)) | ((lfs_tag_t) 0)) : (((((lfs_tag_t) LFS_FROM_NOOP) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 0)), 0}})) / (sizeof(struct lfs_mattr)));
  if (err)
  {
    lfs->mlist = prevdir.next;
    return err;
  }
  if ((!samepair) && lfs_gstate_hasmove(&lfs->gstate))
  {
    lfs_fs_prepmove(lfs, 0x3ff, 0);
    err = lfs_dir_commit(lfs, &oldcwd, (struct lfs_mattr []){{((((lfs_tag_t) LFS_TYPE_DELETE) << 20) | (((lfs_tag_t) lfs_tag_id(oldtag)) << 10)) | ((lfs_tag_t) 0), 0}}, (sizeof((struct lfs_mattr []){{((((lfs_tag_t) LFS_TYPE_DELETE) << 20) | (((lfs_tag_t) lfs_tag_id(oldtag)) << 10)) | ((lfs_tag_t) 0), 0}})) / (sizeof(struct lfs_mattr)));
    if (err)
    {
      lfs->mlist = prevdir.next;
      return err;
    }
  }
  lfs->mlist = prevdir.next;
  if (lfs_gstate_hasorphans(&lfs->gstate))
  {
    assert((prevtag != LFS_ERR_NOENT) && (lfs_tag_type3(prevtag) == LFS_TYPE_DIR));
    err = lfs_fs_preporphans(lfs, -1);
    if (err)
    {
      return err;
    }
    err = lfs_fs_pred(lfs, prevdir.m.pair, &newcwd);
    if (err)
    {
      return err;
    }
    err = lfs_dir_drop(lfs, &newcwd, &prevdir.m);
    if (err)
    {
      return err;
    }
  }
  return 0;
}

static lfs_ssize_t lfs_getattr_(lfs_t *lfs, const char *path, uint8_t type, void *buffer, lfs_size_t size)
{
  lfs_mdir_t cwd;
  lfs_stag_t tag = lfs_dir_find(lfs, &cwd, &path, 0);
  if (tag < 0)
  {
    return tag;
  }
  uint16_t id = lfs_tag_id(tag);
  if (id == 0x3ff)
  {
    id = 0;
    int err = lfs_dir_fetch(lfs, &cwd, lfs->root);
    if (err)
    {
      return err;
    }
  }
  tag = lfs_dir_get(lfs, &cwd, ((((lfs_tag_t) 0x7ff) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 0), ((((lfs_tag_t) (LFS_TYPE_USERATTR + type)) << 20) | (((lfs_tag_t) id) << 10)) | ((lfs_tag_t) lfs_min(size, lfs->attr_max)), buffer);
  if (tag < 0)
  {
    if (tag == LFS_ERR_NOENT)
    {
      return LFS_ERR_NOATTR;
    }
    return tag;
  }
  return lfs_tag_size(tag);
}

static int lfs_commitattr(lfs_t *lfs, const char *path, uint8_t type, const void *buffer, lfs_size_t size)
{
  lfs_mdir_t cwd;
  lfs_stag_t tag = lfs_dir_find(lfs, &cwd, &path, 0);
  if (tag < 0)
  {
    return tag;
  }
  uint16_t id = lfs_tag_id(tag);
  if (id == 0x3ff)
  {
    id = 0;
    int err = lfs_dir_fetch(lfs, &cwd, lfs->root);
    if (err)
    {
      return err;
    }
  }
  return lfs_dir_commit(lfs, &cwd, (struct lfs_mattr []){{((((lfs_tag_t) (LFS_TYPE_USERATTR + type)) << 20) | (((lfs_tag_t) id) << 10)) | ((lfs_tag_t) size), buffer}}, (sizeof((struct lfs_mattr []){{((((lfs_tag_t) (LFS_TYPE_USERATTR + type)) << 20) | (((lfs_tag_t) id) << 10)) | ((lfs_tag_t) size), buffer}})) / (sizeof(struct lfs_mattr)));
}

static int lfs_setattr_(lfs_t *lfs, const char *path, uint8_t type, const void *buffer, lfs_size_t size)
{
  if (size > lfs->attr_max)
  {
    return LFS_ERR_NOSPC;
  }
  return lfs_commitattr(lfs, path, type, buffer, size);
}

static int lfs_removeattr_(lfs_t *lfs, const char *path, uint8_t type)
{
  return lfs_commitattr(lfs, path, type, 0, 0x3ff);
}

static int lfs_init(lfs_t *lfs, const struct lfs_config *cfg)
{
  lfs->cfg = cfg;
  lfs->block_count = cfg->block_count;
  int err = 0;
  assert((bool) 0x80000000);
  assert(lfs->cfg->read != 0);
  assert(lfs->cfg->prog != 0);
  assert(lfs->cfg->erase != 0);
  assert(lfs->cfg->sync != 0);
  assert(lfs->cfg->read_size != 0);
  assert(lfs->cfg->prog_size != 0);
  assert(lfs->cfg->cache_size != 0);
  assert((lfs->cfg->cache_size % lfs->cfg->read_size) == 0);
  assert((lfs->cfg->cache_size % lfs->cfg->prog_size) == 0);
  assert((lfs->cfg->block_size % lfs->cfg->cache_size) == 0);
  assert(lfs->cfg->block_size >= 128);
  assert((4 * lfs_npw2(0xffffffff / (lfs->cfg->block_size - (2 * 4)))) <= lfs->cfg->block_size);
  assert(lfs->cfg->block_cycles != 0);
  assert((lfs->cfg->compact_thresh == 0) || (lfs->cfg->compact_thresh >= (lfs->cfg->block_size / 2)));
  assert((lfs->cfg->compact_thresh == ((lfs_size_t) (-1))) || (lfs->cfg->compact_thresh <= lfs->cfg->block_size));
  assert((!lfs->cfg->metadata_max) || ((lfs->cfg->metadata_max % lfs->cfg->read_size) == 0));
  assert((!lfs->cfg->metadata_max) || ((lfs->cfg->metadata_max % lfs->cfg->prog_size) == 0));
  assert((!lfs->cfg->metadata_max) || ((lfs->cfg->block_size % lfs->cfg->metadata_max) == 0));
  if (lfs->cfg->read_buffer)
  {
    lfs->rcache.buffer = lfs->cfg->read_buffer;
  }
  else
  {
    lfs->rcache.buffer = lfs_malloc(lfs->cfg->cache_size);
    if (!lfs->rcache.buffer)
    {
      err = LFS_ERR_NOMEM;
      goto cleanup;
    }
  }
  if (lfs->cfg->prog_buffer)
  {
    lfs->pcache.buffer = lfs->cfg->prog_buffer;
  }
  else
  {
    lfs->pcache.buffer = lfs_malloc(lfs->cfg->cache_size);
    if (!lfs->pcache.buffer)
    {
      err = LFS_ERR_NOMEM;
      goto cleanup;
    }
  }
  lfs_cache_zero(lfs, &lfs->rcache);
  lfs_cache_zero(lfs, &lfs->pcache);
  assert(lfs->cfg->lookahead_size > 0);
  if (lfs->cfg->lookahead_buffer)
  {
    lfs->lookahead.buffer = lfs->cfg->lookahead_buffer;
  }
  else
  {
    lfs->lookahead.buffer = lfs_malloc(lfs->cfg->lookahead_size);
    if (!lfs->lookahead.buffer)
    {
      err = LFS_ERR_NOMEM;
      goto cleanup;
    }
  }
  assert(lfs->cfg->name_max <= 255);
  lfs->name_max = lfs->cfg->name_max;
  if (!lfs->name_max)
  {
    lfs->name_max = 255;
  }
  assert(lfs->cfg->file_max <= 2147483647);
  lfs->file_max = lfs->cfg->file_max;
  if (!lfs->file_max)
  {
    lfs->file_max = 2147483647;
  }
  assert(lfs->cfg->attr_max <= 1022);
  lfs->attr_max = lfs->cfg->attr_max;
  if (!lfs->attr_max)
  {
    lfs->attr_max = 1022;
  }
  assert(lfs->cfg->metadata_max <= lfs->cfg->block_size);
  assert((lfs->cfg->inline_max == ((lfs_size_t) (-1))) || (lfs->cfg->inline_max <= lfs->cfg->cache_size));
  assert((lfs->cfg->inline_max == ((lfs_size_t) (-1))) || (lfs->cfg->inline_max <= lfs->attr_max));
  assert((lfs->cfg->inline_max == ((lfs_size_t) (-1))) || (lfs->cfg->inline_max <= (((lfs->cfg->metadata_max) ? (lfs->cfg->metadata_max) : (lfs->cfg->block_size)) / 8)));
  lfs->inline_max = lfs->cfg->inline_max;
  if (lfs->inline_max == ((lfs_size_t) (-1)))
  {
    lfs->inline_max = 0;
  }
  else
    if (lfs->inline_max == 0)
  {
    lfs->inline_max = lfs_min(lfs->cfg->cache_size, lfs_min(lfs->attr_max, ((lfs->cfg->metadata_max) ? (lfs->cfg->metadata_max) : (lfs->cfg->block_size)) / 8));
  }
  lfs->root[0] = (lfs_block_t) (-1);
  lfs->root[1] = (lfs_block_t) (-1);
  lfs->mlist = 0;
  lfs->seed = 0;
  lfs->gdisk = (lfs_gstate_t){0};
  lfs->gstate = (lfs_gstate_t){0};
  lfs->gdelta = (lfs_gstate_t){0};
  return 0;
  cleanup:
  lfs_deinit(lfs);

  return err;
}

static int lfs_deinit(lfs_t *lfs)
{
  if (!lfs->cfg->read_buffer)
  {
    lfs_free(lfs->rcache.buffer);
  }
  if (!lfs->cfg->prog_buffer)
  {
    lfs_free(lfs->pcache.buffer);
  }
  if (!lfs->cfg->lookahead_buffer)
  {
    lfs_free(lfs->lookahead.buffer);
  }
  return 0;
}

static int lfs_format_(lfs_t *lfs, const struct lfs_config *cfg)
{
  int err = 0;
  {
    err = lfs_init(lfs, cfg);
    if (err)
    {
      return err;
    }
    assert(cfg->block_count != 0);
    memset(lfs->lookahead.buffer, 0, lfs->cfg->lookahead_size);
    lfs->lookahead.start = 0;
    lfs->lookahead.size = lfs_min(8 * lfs->cfg->lookahead_size, lfs->block_count);
    lfs->lookahead.next = 0;
    lfs_alloc_ckpoint(lfs);
    lfs_mdir_t root;
    err = lfs_dir_alloc(lfs, &root);
    if (err)
    {
      goto cleanup;
    }
    lfs_superblock_t superblock = {.version = lfs_fs_disk_version(lfs), .block_size = lfs->cfg->block_size, .block_count = lfs->block_count, .name_max = lfs->name_max, .file_max = lfs->file_max, .attr_max = lfs->attr_max};
    lfs_superblock_tole32(&superblock);
    err = lfs_dir_commit(lfs, &root, (struct lfs_mattr []){{((((lfs_tag_t) LFS_TYPE_CREATE) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 0), 0}, {((((lfs_tag_t) LFS_TYPE_SUPERBLOCK) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 8), "littlefs"}, {((((lfs_tag_t) LFS_TYPE_INLINESTRUCT) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) (sizeof(superblock))), &superblock}}, (sizeof((struct lfs_mattr []){{((((lfs_tag_t) LFS_TYPE_CREATE) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 0), 0}, {((((lfs_tag_t) LFS_TYPE_SUPERBLOCK) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 8), "littlefs"}, {((((lfs_tag_t) LFS_TYPE_INLINESTRUCT) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) (sizeof(superblock))), &superblock}})) / (sizeof(struct lfs_mattr)));
    if (err)
    {
      goto cleanup;
    }
    root.erased = 0;
    err = lfs_dir_commit(lfs, &root, 0, 0);
    if (err)
    {
      goto cleanup;
    }
    err = lfs_dir_fetch(lfs, &root, (const lfs_block_t [2]){0, 1});
    if (err)
    {
      goto cleanup;
    }
  }
  cleanup:
  lfs_deinit(lfs);

  return err;
}

struct lfs_tortoise_t
{
  lfs_block_t pair[2];
  lfs_size_t i;
  lfs_size_t period;
};
static int lfs_tortoise_detectcycles(const lfs_mdir_t *dir, struct lfs_tortoise_t *tortoise)
{
  if (lfs_pair_issync(dir->tail, tortoise->pair))
  {
    printf("%s:%d:warn: Cycle detected in tail list%s\n", "/home/ubuntu/C2RustTranslation/subjects/littlefs/lfs.c", 4468, "");
    return LFS_ERR_CORRUPT;
  }
  if (tortoise->i == tortoise->period)
  {
    tortoise->pair[0] = dir->tail[0];
    tortoise->pair[1] = dir->tail[1];
    tortoise->i = 0;
    tortoise->period *= 2;
  }
  tortoise->i += 1;
  return LFS_ERR_OK;
}

static int lfs_mount_(lfs_t *lfs, const struct lfs_config *cfg)
{
  int err = lfs_init(lfs, cfg);
  if (err)
  {
    return err;
  }
  lfs_mdir_t dir = {.tail = {0, 1}};
  struct lfs_tortoise_t tortoise = {.pair = {(lfs_block_t) (-1), (lfs_block_t) (-1)}, .i = 1, .period = 1};
  while (!lfs_pair_isnull(dir.tail))
  {
    helper_lfs_mount__1(&err, lfs, dir, tortoise);
  }

  if (!lfs_gstate_iszero(&lfs->gstate))
  {
    printf("%s:%d:debug: Found pending gstate 0x%08x%08x%08x%s\n", "/home/ubuntu/C2RustTranslation/subjects/littlefs/lfs.c", 4627, lfs->gstate.tag, lfs->gstate.pair[0], lfs->gstate.pair[1], "");
  }
  lfs->gstate.tag += !lfs_tag_isvalid(lfs->gstate.tag);
  lfs->gdisk = lfs->gstate;
  lfs->lookahead.start = lfs->seed % lfs->block_count;
  lfs_alloc_drop(lfs);
  return 0;
  cleanup:
  lfs_unmount_(lfs);

  return err;
}

static int lfs_unmount_(lfs_t *lfs)
{
  return lfs_deinit(lfs);
}

static int lfs_fs_stat_(lfs_t *lfs, struct lfs_fsinfo *fsinfo)
{
  if (!lfs_gstate_needssuperblock(&lfs->gstate))
  {
    fsinfo->disk_version = lfs_fs_disk_version(lfs);
  }
  else
  {
    lfs_mdir_t dir;
    int err = lfs_dir_fetch(lfs, &dir, lfs->root);
    if (err)
    {
      return err;
    }
    lfs_superblock_t superblock;
    lfs_stag_t tag = lfs_dir_get(lfs, &dir, ((((lfs_tag_t) 0x7ff) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 0), ((((lfs_tag_t) LFS_TYPE_INLINESTRUCT) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) (sizeof(superblock))), &superblock);
    if (tag < 0)
    {
      return tag;
    }
    lfs_superblock_fromle32(&superblock);
    fsinfo->disk_version = superblock.version;
  }
  fsinfo->block_size = lfs->cfg->block_size;
  fsinfo->block_count = lfs->block_count;
  fsinfo->name_max = lfs->name_max;
  fsinfo->file_max = lfs->file_max;
  fsinfo->attr_max = lfs->attr_max;
  return 0;
}

int lfs_fs_traverse_(lfs_t *lfs, int (*cb)(void *data, lfs_block_t block), void *data, bool includeorphans)
{
  lfs_mdir_t dir = {.tail = {0, 1}};
  struct lfs_tortoise_t tortoise = {.pair = {(lfs_block_t) (-1), (lfs_block_t) (-1)}, .i = 1, .period = 1};
  int err = LFS_ERR_OK;
  while (!lfs_pair_isnull(dir.tail))
  {
    helper_lfs_fs_traverse__1(&err, &err, &err, &err, &err, lfs, cb, data, data, includeorphans, dir, tortoise);
  }

  for (lfs_file_t *f = (lfs_file_t *) lfs->mlist; f; f_idx = f_idx->next)
  {
    if (f->type != LFS_TYPE_REG)
    {
      continue;
    }
    if ((f->flags & LFS_F_DIRTY) && (!(f->flags & LFS_F_INLINE)))
    {
      int err = lfs_ctz_traverse(lfs, &f->cache, &lfs->rcache, f->ctz.head, f->ctz.size, cb, data);
      if (err)
      {
        return err;
      }
    }
    if ((f->flags & LFS_F_WRITING) && (!(f->flags & LFS_F_INLINE)))
    {
      int err = lfs_ctz_traverse(lfs, &f->cache, &lfs->rcache, f->block, f->pos, cb, data);
      if (err)
      {
        return err;
      }
    }
  }

  unsigned int f_idx = 0;
  return 0;
}

static int lfs_fs_pred(lfs_t *lfs, const lfs_block_t pair[2], lfs_mdir_t *pdir)
{
  pdir->tail[0] = 0;
  pdir->tail[1] = 1;
  struct lfs_tortoise_t tortoise = {.pair = {(lfs_block_t) (-1), (lfs_block_t) (-1)}, .i = 1, .period = 1};
  int err = LFS_ERR_OK;
  while (!lfs_pair_isnull(pdir->tail))
  {
    err = lfs_tortoise_detectcycles(pdir, &tortoise);
    if (err < 0)
    {
      return LFS_ERR_CORRUPT;
    }
    if (lfs_pair_cmp(pdir->tail, pair) == 0)
    {
      return 0;
    }
    int err = lfs_dir_fetch(lfs, pdir, pdir->tail);
    if (err)
    {
      return err;
    }
  }

  return LFS_ERR_NOENT;
}

struct lfs_fs_parent_match
{
  lfs_t *lfs;
  const lfs_block_t pair[2];
};
static int lfs_fs_parent_match(void *data, lfs_tag_t tag, const void *buffer)
{
  struct lfs_fs_parent_match *find = data;
  lfs_t *lfs = find->lfs;
  const struct lfs_diskoff *disk = buffer;
  (void) tag;
  lfs_block_t child[2];
  int err = lfs_bd_read(lfs, &lfs->pcache, &lfs->rcache, lfs->cfg->block_size, disk->block, disk->off, &child, sizeof(child));
  if (err)
  {
    return err;
  }
  lfs_pair_fromle32(child);
  return (lfs_pair_cmp(child, find->pair) == 0) ? (LFS_CMP_EQ) : (LFS_CMP_LT);
}

static lfs_stag_t lfs_fs_parent(lfs_t *lfs, const lfs_block_t pair[2], lfs_mdir_t *parent)
{
  parent->tail[0] = 0;
  parent->tail[1] = 1;
  struct lfs_tortoise_t tortoise = {.pair = {(lfs_block_t) (-1), (lfs_block_t) (-1)}, .i = 1, .period = 1};
  int err = LFS_ERR_OK;
  while (!lfs_pair_isnull(parent->tail))
  {
    err = lfs_tortoise_detectcycles(parent, &tortoise);
    if (err < 0)
    {
      return err;
    }
    lfs_stag_t tag = lfs_dir_fetchmatch(lfs, parent, parent->tail, ((((lfs_tag_t) 0x7ff) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 0x3ff), ((((lfs_tag_t) LFS_TYPE_DIRSTRUCT) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 8), 0, lfs_fs_parent_match, &((struct lfs_fs_parent_match){lfs, {pair[0], pair[1]}}));
    if (tag && (tag != LFS_ERR_NOENT))
    {
      return tag;
    }
  }

  return LFS_ERR_NOENT;
}

static void lfs_fs_prepsuperblock(lfs_t *lfs, bool needssuperblock)
{
  lfs->gstate.tag = (lfs->gstate.tag & (~(((((lfs_tag_t) 0) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 0x200)))) | (((uint32_t) needssuperblock) << 9);
}

static int lfs_fs_preporphans(lfs_t *lfs, int8_t orphans)
{
  assert((lfs_tag_size(lfs->gstate.tag) > 0x000) || (orphans >= 0));
  assert((lfs_tag_size(lfs->gstate.tag) < 0x1ff) || (orphans <= 0));
  lfs->gstate.tag += orphans;
  lfs->gstate.tag = (lfs->gstate.tag & (~(((((lfs_tag_t) 0x800) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 0)))) | (((uint32_t) lfs_gstate_hasorphans(&lfs->gstate)) << 31);
  return 0;
}

static void lfs_fs_prepmove(lfs_t *lfs, uint16_t id, const lfs_block_t pair[2])
{
  lfs->gstate.tag = (lfs->gstate.tag & (~(((((lfs_tag_t) 0x7ff) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 0)))) | ((id != 0x3ff) ? (((((lfs_tag_t) LFS_TYPE_DELETE) << 20) | (((lfs_tag_t) id) << 10)) | ((lfs_tag_t) 0)) : (0));
  lfs->gstate.pair[0] = (id != 0x3ff) ? (pair[0]) : (0);
  lfs->gstate.pair[1] = (id != 0x3ff) ? (pair[1]) : (0);
}

static int lfs_fs_desuperblock(lfs_t *lfs)
{
  if (!lfs_gstate_needssuperblock(&lfs->gstate))
  {
    return 0;
  }
  printf("%s:%d:debug: Rewriting superblock {0x%x, 0x%x}%s\n", "/home/ubuntu/C2RustTranslation/subjects/littlefs/lfs.c", 4921, lfs->root[0], lfs->root[1], "");
  lfs_mdir_t root;
  int err = lfs_dir_fetch(lfs, &root, lfs->root);
  if (err)
  {
    return err;
  }
  lfs_superblock_t superblock = {.version = lfs_fs_disk_version(lfs), .block_size = lfs->cfg->block_size, .block_count = lfs->block_count, .name_max = lfs->name_max, .file_max = lfs->file_max, .attr_max = lfs->attr_max};
  lfs_superblock_tole32(&superblock);
  err = lfs_dir_commit(lfs, &root, (struct lfs_mattr []){{((((lfs_tag_t) LFS_TYPE_INLINESTRUCT) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) (sizeof(superblock))), &superblock}}, (sizeof((struct lfs_mattr []){{((((lfs_tag_t) LFS_TYPE_INLINESTRUCT) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) (sizeof(superblock))), &superblock}})) / (sizeof(struct lfs_mattr)));
  if (err)
  {
    return err;
  }
  lfs_fs_prepsuperblock(lfs, 0);
  return 0;
}

static int lfs_fs_demove(lfs_t *lfs)
{
  if (!lfs_gstate_hasmove(&lfs->gdisk))
  {
    return 0;
  }
  printf("%s:%d:debug: Fixing move {0x%x, 0x%x} 0x%x%s\n", "/home/ubuntu/C2RustTranslation/subjects/littlefs/lfs.c", 4961, lfs->gdisk.pair[0], lfs->gdisk.pair[1], lfs_tag_id(lfs->gdisk.tag), "");
  assert(lfs_tag_type3(lfs->gdisk.tag) == LFS_TYPE_DELETE);
  lfs_mdir_t movedir;
  int err = lfs_dir_fetch(lfs, &movedir, lfs->gdisk.pair);
  if (err)
  {
    return err;
  }
  uint16_t moveid = lfs_tag_id(lfs->gdisk.tag);
  lfs_fs_prepmove(lfs, 0x3ff, 0);
  err = lfs_dir_commit(lfs, &movedir, (struct lfs_mattr []){{((((lfs_tag_t) LFS_TYPE_DELETE) << 20) | (((lfs_tag_t) moveid) << 10)) | ((lfs_tag_t) 0), 0}}, (sizeof((struct lfs_mattr []){{((((lfs_tag_t) LFS_TYPE_DELETE) << 20) | (((lfs_tag_t) moveid) << 10)) | ((lfs_tag_t) 0), 0}})) / (sizeof(struct lfs_mattr)));
  if (err)
  {
    return err;
  }
  return 0;
}

static int lfs_fs_deorphan(lfs_t *lfs, bool powerloss)
{
  if (!lfs_gstate_hasorphans(&lfs->gstate))
  {
    return 0;
  }
  int pass = 0;
  while (pass < 2)
  {
    helper_lfs_fs_deorphan_1(&pass, lfs, powerloss);
  }

  return lfs_fs_preporphans(lfs, -lfs_gstate_getorphans(&lfs->gstate));
}

static int lfs_fs_forceconsistency(lfs_t *lfs)
{
  int err = lfs_fs_desuperblock(lfs);
  if (err)
  {
    return err;
  }
  err = lfs_fs_demove(lfs);
  if (err)
  {
    return err;
  }
  err = lfs_fs_deorphan(lfs, 1);
  if (err)
  {
    return err;
  }
  return 0;
}

static int lfs_fs_mkconsistent_(lfs_t *lfs)
{
  int err = lfs_fs_forceconsistency(lfs);
  if (err)
  {
    return err;
  }
  lfs_gstate_t delta = {0};
  lfs_gstate_xor(&delta, &lfs->gdisk);
  lfs_gstate_xor(&delta, &lfs->gstate);
  if (!lfs_gstate_iszero(&delta))
  {
    lfs_mdir_t root;
    err = lfs_dir_fetch(lfs, &root, lfs->root);
    if (err)
    {
      return err;
    }
    err = lfs_dir_commit(lfs, &root, 0, 0);
    if (err)
    {
      return err;
    }
  }
  return 0;
}

static int lfs_fs_size_count(void *p, lfs_block_t block)
{
  (void) block;
  lfs_size_t *size = p;
  *size += 1;
  return 0;
}

static lfs_ssize_t lfs_fs_size_(lfs_t *lfs)
{
  lfs_size_t size = 0;
  int err = lfs_fs_traverse_(lfs, lfs_fs_size_count, &size, 0);
  if (err)
  {
    return err;
  }
  return size;
}

static int lfs_fs_gc_(lfs_t *lfs)
{
  int err = lfs_fs_forceconsistency(lfs);
  if (err)
  {
    return err;
  }
  if (lfs->cfg->compact_thresh < (lfs->cfg->block_size - lfs->cfg->prog_size))
  {
    lfs_mdir_t mdir = {.tail = {0, 1}};
    while (!lfs_pair_isnull(mdir.tail))
    {
      err = lfs_dir_fetch(lfs, &mdir, mdir.tail);
      if (err)
      {
        return err;
      }
      if ((!mdir.erased) || ((lfs->cfg->compact_thresh == 0) ? (mdir.off > (lfs->cfg->block_size - (lfs->cfg->block_size / 8))) : (mdir.off > lfs->cfg->compact_thresh)))
      {
        mdir.erased = 0;
        err = lfs_dir_commit(lfs, &mdir, 0, 0);
        if (err)
        {
          return err;
        }
      }
    }

  }
  if (lfs->lookahead.size < lfs_min(8 * lfs->cfg->lookahead_size, lfs->block_count))
  {
    err = lfs_alloc_scan(lfs);
    if (err)
    {
      return err;
    }
  }
  return 0;
}

static int lfs_fs_grow_(lfs_t *lfs, lfs_size_t block_count)
{
  int err;
  if (block_count == lfs->block_count)
  {
    return 0;
  }
  assert(block_count >= lfs->block_count);
  lfs->block_count = block_count;
  lfs_mdir_t root;
  err = lfs_dir_fetch(lfs, &root, lfs->root);
  if (err)
  {
    return err;
  }
  lfs_superblock_t superblock;
  lfs_stag_t tag = lfs_dir_get(lfs, &root, ((((lfs_tag_t) 0x7ff) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 0), ((((lfs_tag_t) LFS_TYPE_INLINESTRUCT) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) (sizeof(superblock))), &superblock);
  if (tag < 0)
  {
    return tag;
  }
  lfs_superblock_fromle32(&superblock);
  superblock.block_count = lfs->block_count;
  lfs_superblock_tole32(&superblock);
  err = lfs_dir_commit(lfs, &root, (struct lfs_mattr []){{tag, &superblock}}, (sizeof((struct lfs_mattr []){{tag, &superblock}})) / (sizeof(struct lfs_mattr)));
  if (err)
  {
    return err;
  }
  return 0;
}

int lfs_format(lfs_t *lfs, const struct lfs_config *cfg)
{
  int err = ((void) cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  err = lfs_format_(lfs, cfg);
  ;
  (void) cfg;
  return err;
}

int lfs_mount(lfs_t *lfs, const struct lfs_config *cfg)
{
  int err = ((void) cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  err = lfs_mount_(lfs, cfg);
  ;
  (void) cfg;
  return err;
}

int lfs_unmount(lfs_t *lfs)
{
  int err = ((void) lfs->cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  err = lfs_unmount_(lfs);
  ;
  (void) lfs->cfg;
  return err;
}

int lfs_remove(lfs_t *lfs, const char *path)
{
  int err = ((void) lfs->cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  err = lfs_remove_(lfs, path);
  ;
  (void) lfs->cfg;
  return err;
}

int lfs_rename(lfs_t *lfs, const char *oldpath, const char *newpath)
{
  int err = ((void) lfs->cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  err = lfs_rename_(lfs, oldpath, newpath);
  ;
  (void) lfs->cfg;
  return err;
}

int lfs_stat(lfs_t *lfs, const char *path, struct lfs_info *info)
{
  int err = ((void) lfs->cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  err = lfs_stat_(lfs, path, info);
  ;
  (void) lfs->cfg;
  return err;
}

lfs_ssize_t lfs_getattr(lfs_t *lfs, const char *path, uint8_t type, void *buffer, lfs_size_t size)
{
  int err = ((void) lfs->cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  lfs_ssize_t res = lfs_getattr_(lfs, path, type, buffer, size);
  ;
  (void) lfs->cfg;
  return res;
}

int lfs_setattr(lfs_t *lfs, const char *path, uint8_t type, const void *buffer, lfs_size_t size)
{
  int err = ((void) lfs->cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  err = lfs_setattr_(lfs, path, type, buffer, size);
  ;
  (void) lfs->cfg;
  return err;
}

int lfs_removeattr(lfs_t *lfs, const char *path, uint8_t type)
{
  int err = ((void) lfs->cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  err = lfs_removeattr_(lfs, path, type);
  ;
  (void) lfs->cfg;
  return err;
}

int lfs_file_open(lfs_t *lfs, lfs_file_t *file, const char *path, int flags)
{
  int err = ((void) lfs->cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  assert(!lfs_mlist_isopen(lfs->mlist, (struct lfs_mlist *) file));
  err = lfs_file_open_(lfs, file, path, flags);
  ;
  (void) lfs->cfg;
  return err;
}

int lfs_file_opencfg(lfs_t *lfs, lfs_file_t *file, const char *path, int flags, const struct lfs_file_config *cfg)
{
  int err = ((void) lfs->cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  assert(!lfs_mlist_isopen(lfs->mlist, (struct lfs_mlist *) file));
  err = lfs_file_opencfg_(lfs, file, path, flags, cfg);
  ;
  (void) lfs->cfg;
  return err;
}

int lfs_file_close(lfs_t *lfs, lfs_file_t *file)
{
  int err = ((void) lfs->cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  assert(lfs_mlist_isopen(lfs->mlist, (struct lfs_mlist *) file));
  err = lfs_file_close_(lfs, file);
  ;
  (void) lfs->cfg;
  return err;
}

int lfs_file_sync(lfs_t *lfs, lfs_file_t *file)
{
  int err = ((void) lfs->cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  assert(lfs_mlist_isopen(lfs->mlist, (struct lfs_mlist *) file));
  err = lfs_file_sync_(lfs, file);
  ;
  (void) lfs->cfg;
  return err;
}

lfs_ssize_t lfs_file_read(lfs_t *lfs, lfs_file_t *file, void *buffer, lfs_size_t size)
{
  int err = ((void) lfs->cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  assert(lfs_mlist_isopen(lfs->mlist, (struct lfs_mlist *) file));
  lfs_ssize_t res = lfs_file_read_(lfs, file, buffer, size);
  ;
  (void) lfs->cfg;
  return res;
}

lfs_ssize_t lfs_file_write(lfs_t *lfs, lfs_file_t *file, const void *buffer, lfs_size_t size)
{
  int err = ((void) lfs->cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  assert(lfs_mlist_isopen(lfs->mlist, (struct lfs_mlist *) file));
  lfs_ssize_t res = lfs_file_write_(lfs, file, buffer, size);
  ;
  (void) lfs->cfg;
  return res;
}

lfs_soff_t lfs_file_seek(lfs_t *lfs, lfs_file_t *file, lfs_soff_t off, int whence)
{
  int err = ((void) lfs->cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  assert(lfs_mlist_isopen(lfs->mlist, (struct lfs_mlist *) file));
  lfs_soff_t res = lfs_file_seek_(lfs, file, off, whence);
  ;
  (void) lfs->cfg;
  return res;
}

int lfs_file_truncate(lfs_t *lfs, lfs_file_t *file, lfs_off_t size)
{
  int err = ((void) lfs->cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  assert(lfs_mlist_isopen(lfs->mlist, (struct lfs_mlist *) file));
  err = lfs_file_truncate_(lfs, file, size);
  ;
  (void) lfs->cfg;
  return err;
}

lfs_soff_t lfs_file_tell(lfs_t *lfs, lfs_file_t *file)
{
  int err = ((void) lfs->cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  assert(lfs_mlist_isopen(lfs->mlist, (struct lfs_mlist *) file));
  lfs_soff_t res = lfs_file_tell_(lfs, file);
  ;
  (void) lfs->cfg;
  return res;
}

int lfs_file_rewind(lfs_t *lfs, lfs_file_t *file)
{
  int err = ((void) lfs->cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  err = lfs_file_rewind_(lfs, file);
  ;
  (void) lfs->cfg;
  return err;
}

lfs_soff_t lfs_file_size(lfs_t *lfs, lfs_file_t *file)
{
  int err = ((void) lfs->cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  assert(lfs_mlist_isopen(lfs->mlist, (struct lfs_mlist *) file));
  lfs_soff_t res = lfs_file_size_(lfs, file);
  ;
  (void) lfs->cfg;
  return res;
}

int lfs_mkdir(lfs_t *lfs, const char *path)
{
  int err = ((void) lfs->cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  err = lfs_mkdir_(lfs, path);
  ;
  (void) lfs->cfg;
  return err;
}

int lfs_dir_open(lfs_t *lfs, lfs_dir_t *dir, const char *path)
{
  int err = ((void) lfs->cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  assert(!lfs_mlist_isopen(lfs->mlist, (struct lfs_mlist *) dir));
  err = lfs_dir_open_(lfs, dir, path);
  ;
  (void) lfs->cfg;
  return err;
}

int lfs_dir_close(lfs_t *lfs, lfs_dir_t *dir)
{
  int err = ((void) lfs->cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  err = lfs_dir_close_(lfs, dir);
  ;
  (void) lfs->cfg;
  return err;
}

int lfs_dir_read(lfs_t *lfs, lfs_dir_t *dir, struct lfs_info *info)
{
  int err = ((void) lfs->cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  err = lfs_dir_read_(lfs, dir, info);
  ;
  (void) lfs->cfg;
  return err;
}

int lfs_dir_seek(lfs_t *lfs, lfs_dir_t *dir, lfs_off_t off)
{
  int err = ((void) lfs->cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  err = lfs_dir_seek_(lfs, dir, off);
  ;
  (void) lfs->cfg;
  return err;
}

lfs_soff_t lfs_dir_tell(lfs_t *lfs, lfs_dir_t *dir)
{
  int err = ((void) lfs->cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  lfs_soff_t res = lfs_dir_tell_(lfs, dir);
  ;
  (void) lfs->cfg;
  return res;
}

int lfs_dir_rewind(lfs_t *lfs, lfs_dir_t *dir)
{
  int err = ((void) lfs->cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  err = lfs_dir_rewind_(lfs, dir);
  ;
  (void) lfs->cfg;
  return err;
}

int lfs_fs_stat(lfs_t *lfs, struct lfs_fsinfo *fsinfo)
{
  int err = ((void) lfs->cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  err = lfs_fs_stat_(lfs, fsinfo);
  ;
  (void) lfs->cfg;
  return err;
}

lfs_ssize_t lfs_fs_size(lfs_t *lfs)
{
  int err = ((void) lfs->cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  lfs_ssize_t res = lfs_fs_size_(lfs);
  ;
  (void) lfs->cfg;
  return res;
}

int lfs_fs_traverse(lfs_t *lfs, int (*cb)(void *, lfs_block_t), void *data)
{
  int err = ((void) lfs->cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  err = lfs_fs_traverse_(lfs, cb, data, 1);
  ;
  (void) lfs->cfg;
  return err;
}

int lfs_fs_mkconsistent(lfs_t *lfs)
{
  int err = ((void) lfs->cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  err = lfs_fs_mkconsistent_(lfs);
  ;
  (void) lfs->cfg;
  return err;
}

int lfs_fs_gc(lfs_t *lfs)
{
  int err = ((void) lfs->cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  err = lfs_fs_gc_(lfs);
  ;
  (void) lfs->cfg;
  return err;
}

int lfs_fs_grow(lfs_t *lfs, lfs_size_t block_count)
{
  int err = ((void) lfs->cfg, 0);
  if (err)
  {
    return err;
  }
  ;
  err = lfs_fs_grow_(lfs, block_count);
  ;
  (void) lfs->cfg;
  return err;
}

int helper_lfs_bd_read_1(lfs_block_t * const block_ref, lfs_off_t * const off_ref, lfs_size_t * const size_ref, unsigned int * const data_idx_ref, lfs_t * const lfs, const lfs_cache_t * const pcache, lfs_cache_t * const rcache, lfs_size_t hint, uint8_t * const data)
{
  lfs_block_t block = *block_ref;
  lfs_off_t off = *off_ref;
  lfs_size_t size = *size_ref;
  unsigned int data_idx = *data_idx_ref;
  lfs_size_t diff = size;
  if ((pcache && (block == pcache->block)) && (off < (pcache->off + pcache->size)))
  {
    if (off >= pcache->off)
    {
      diff = lfs_min(diff, pcache->size - (off - pcache->off));
      memcpy(data, &pcache->buffer[off - pcache->off], diff);
      data_idx += diff;
      off += diff;
      size -= diff;
      continue;
    }
    diff = lfs_min(diff, pcache->off - off);
  }
  if ((block == rcache->block) && (off < (rcache->off + rcache->size)))
  {
    if (off >= rcache->off)
    {
      diff = lfs_min(diff, rcache->size - (off - rcache->off));
      memcpy(data, &rcache->buffer[off - rcache->off], diff);
      data_idx += diff;
      off += diff;
      size -= diff;
      continue;
    }
    diff = lfs_min(diff, rcache->off - off);
  }
  if (((size >= hint) && ((off % lfs->cfg->read_size) == 0)) && (size >= lfs->cfg->read_size))
  {
    diff = lfs_aligndown(diff, lfs->cfg->read_size);
    int err = lfs->cfg->read(lfs->cfg, block, off, data, diff);
    assert(err <= 0);
    if (err)
    {
      return err;
    }
    data_idx += diff;
    off += diff;
    size -= diff;
    continue;
  }
  assert((!lfs->block_count) || (block < lfs->block_count));
  rcache->block = block;
  rcache->off = lfs_aligndown(off, lfs->cfg->read_size);
  rcache->size = lfs_min(lfs_min(lfs_alignup(off + hint, lfs->cfg->read_size), lfs->cfg->block_size) - rcache->off, lfs->cfg->cache_size);
  int err = lfs->cfg->read(lfs->cfg, rcache->block, rcache->off, rcache->buffer, rcache->size);
  assert(err <= 0);
  if (err)
  {
    return err;
  }
  *block_ref = block;
  *off_ref = off;
  *size_ref = size;
  *data_idx_ref = data_idx;
}

void helper_lfs_dir_traverse_1(lfs_off_t * const off_ref, lfs_tag_t * const ptag_ref, int * const attrcount_ref, lfs_tag_t * const tmask_ref, lfs_tag_t * const ttag_ref, uint16_t * const begin_ref, uint16_t * const end_ref, int16_t * const diff_ref, lfs_tag_t * const tag_ref, unsigned int * const data_idx_ref, unsigned int * const cb_idx_ref, unsigned int * const attrs_idx_ref, unsigned int * const dir_idx_ref, unsigned * const sp_ref, lfs_tag_t * const tag_ref, unsigned int * const buffer_idx_ref, struct lfs_diskoff * const disk_ref, struct lfs_dir_traverse stack[3 - 1])
{
  lfs_off_t off = *off_ref;
  lfs_tag_t ptag = *ptag_ref;
  int attrcount = *attrcount_ref;
  lfs_tag_t tmask = *tmask_ref;
  lfs_tag_t ttag = *ttag_ref;
  uint16_t begin = *begin_ref;
  uint16_t end = *end_ref;
  int16_t diff = *diff_ref;
  lfs_tag_t tag = *tag_ref;
  unsigned int data_idx = *data_idx_ref;
  unsigned int cb_idx = *cb_idx_ref;
  unsigned int attrs_idx = *attrs_idx_ref;
  unsigned int dir_idx = *dir_idx_ref;
  unsigned sp = *sp_ref;
  lfs_tag_t tag = *tag_ref;
  unsigned int buffer_idx = *buffer_idx_ref;
  struct lfs_diskoff disk = *disk_ref;
  dir_idx = stack[sp - 1].dir_idx;
  off = stack[sp - 1].off;
  ptag = stack[sp - 1].ptag;
  attrs_idx = stack[sp - 1].attrs_idx;
  attrcount = stack[sp - 1].attrcount;
  tmask = stack[sp - 1].tmask;
  ttag = stack[sp - 1].ttag;
  begin = stack[sp - 1].begin;
  end = stack[sp - 1].end;
  diff = stack[sp - 1].diff;
  cb_idx = stack[sp - 1].cb_idx;
  data_idx = stack[sp - 1].data_idx;
  tag = stack[sp - 1].tag;
  buffer_idx = stack[sp - 1].buffer_idx;
  disk = stack[sp - 1].disk;
  sp -= 1;
  goto popped;
  *off_ref = off;
  *ptag_ref = ptag;
  *attrcount_ref = attrcount;
  *tmask_ref = tmask;
  *ttag_ref = ttag;
  *begin_ref = begin;
  *end_ref = end;
  *diff_ref = diff;
  *tag_ref = tag;
  *data_idx_ref = data_idx;
  *cb_idx_ref = cb_idx;
  *attrs_idx_ref = attrs_idx;
  *dir_idx_ref = dir_idx;
  *sp_ref = sp;
  *tag_ref = tag;
  *buffer_idx_ref = buffer_idx;
  *disk_ref = disk;
}

int helper_lfs_dir_traverse_2(lfs_off_t * const off_ref, lfs_tag_t * const ptag_ref, int * const attrcount_ref, lfs_tag_t * const tmask_ref, lfs_tag_t * const ttag_ref, uint16_t * const begin_ref, uint16_t * const end_ref, int16_t * const diff_ref, lfs_tag_t * const tag_ref, unsigned int * const data_idx_ref, unsigned int * const cb_idx_ref, unsigned int * const attrs_idx_ref, unsigned int * const dir_idx_ref, unsigned * const sp_ref, int * const res_ref, lfs_tag_t * const tag_ref, unsigned int * const buffer_idx_ref, struct lfs_diskoff * const disk_ref, lfs_t * const lfs, const lfs_mdir_t * const dir, const struct lfs_mattr * const attrs, int (* const cb)(void *data, lfs_tag_t tag, const void *buffer), void * const data, const void * const buffer, void * const data, struct lfs_dir_traverse stack[3 - 1], const void * const buffer)
{
  lfs_off_t off = *off_ref;
  lfs_tag_t ptag = *ptag_ref;
  int attrcount = *attrcount_ref;
  lfs_tag_t tmask = *tmask_ref;
  lfs_tag_t ttag = *ttag_ref;
  uint16_t begin = *begin_ref;
  uint16_t end = *end_ref;
  int16_t diff = *diff_ref;
  lfs_tag_t tag = *tag_ref;
  unsigned int data_idx = *data_idx_ref;
  unsigned int cb_idx = *cb_idx_ref;
  unsigned int attrs_idx = *attrs_idx_ref;
  unsigned int dir_idx = *dir_idx_ref;
  unsigned sp = *sp_ref;
  int res = *res_ref;
  lfs_tag_t tag = *tag_ref;
  unsigned int buffer_idx = *buffer_idx_ref;
  struct lfs_diskoff disk = *disk_ref;
  {
    helper_helper_lfs_dir_traverse_2_2(&tag, &off, &ptag, &attrcount, &tmask, &ttag, &begin, &end, &diff, &tag, &data_idx, &cb_idx, &attrs_idx, &sp, &res, &tag, &buffer_idx, &disk, lfs, dir, attrs, cb, data, buffer, data, buffer, data, stack, buffer);
  }
  popped:
  if ((lfs_tag_id(tmask) != 0) && (!((lfs_tag_id(tag) >= begin) && (lfs_tag_id(tag) < end))))
  {
    continue;
  }

  if (lfs_tag_type3(tag) == LFS_FROM_NOOP)
  {
  }
  else
    if (lfs_tag_type3(tag) == LFS_FROM_MOVE)
  {
    helper_helper_lfs_dir_traverse_2_1(&off, &ptag, &attrcount, &tmask, &ttag, &begin, &end, &diff, &attrs_idx, &dir_idx, &sp, dir, attrs, cb, data, tag, buffer, data, buffer, data, stack, buffer, tag, cb_idx, tag, buffer_idx);
  }
  else
    if (lfs_tag_type3(tag) == LFS_FROM_USERATTRS)
  {
    for (unsigned i = 0; i < lfs_tag_size(tag); i += 1)
    {
      const struct lfs_attr *a = buffer;
      res = cb(data, ((((lfs_tag_t) (LFS_TYPE_USERATTR + a[i].type)) << 20) | (((lfs_tag_t) (lfs_tag_id(tag) + diff)) << 10)) | ((lfs_tag_t) a[i].size), a[i].buffer);
      if (res < 0)
      {
        return res;
      }
      if (res)
      {
        break;
      }
    }

  }
  else
  {
    res = cb(data, tag + (((((lfs_tag_t) 0) << 20) | (((lfs_tag_t) diff) << 10)) | ((lfs_tag_t) 0)), buffer);
    if (res < 0)
    {
      return res;
    }
    if (res)
    {
      break;
    }
  }
  *off_ref = off;
  *ptag_ref = ptag;
  *attrcount_ref = attrcount;
  *tmask_ref = tmask;
  *ttag_ref = ttag;
  *begin_ref = begin;
  *end_ref = end;
  *diff_ref = diff;
  *tag_ref = tag;
  *data_idx_ref = data_idx;
  *cb_idx_ref = cb_idx;
  *attrs_idx_ref = attrs_idx;
  *dir_idx_ref = dir_idx;
  *sp_ref = sp;
  *res_ref = res;
  *tag_ref = tag;
  *buffer_idx_ref = buffer_idx;
  *disk_ref = disk;
}

lfs_stag_t helper_lfs_dir_fetchmatch_1(lfs_stag_t * const besttag_ref, lfs_t * const lfs, lfs_mdir_t * const dir, lfs_tag_t fmask, lfs_tag_t ftag, uint16_t * const id, void * const data, void * const data, uint32_t revs[2], int r)
{
  lfs_stag_t besttag = *besttag_ref;
  lfs_off_t off = 0;
  lfs_tag_t ptag = 0xffffffff;
  uint16_t tempcount = 0;
  lfs_block_t temptail[2] = {(lfs_block_t) (-1), (lfs_block_t) (-1)};
  bool tempsplit = 0;
  lfs_stag_t tempbesttag = besttag;
  bool maybeerased = 0;
  bool hasfcrc = 0;
  struct lfs_fcrc fcrc;
  dir->rev = lfs_tole32(dir->rev);
  uint32_t crc = lfs_crc(0xffffffff, &dir->rev, sizeof(dir->rev));
  dir->rev = lfs_fromle32(dir->rev);
  while (1)
  {
    helper_helper_lfs_dir_fetchmatch_1_1(&besttag, &off, &ptag, &tempcount, &tempsplit, &tempbesttag, &maybeerased, &hasfcrc, &crc, lfs, dir, fmask, ftag, data, data, temptail, fcrc);
  }

  if (dir->off == 0)
  {
    lfs_pair_swap(dir->pair);
    dir->rev = revs[(r + 1) % 2];
    continue;
  }
  dir->erased = 0;
  if (maybeerased && ((dir->off % lfs->cfg->prog_size) == 0))
  {
    if (hasfcrc)
    {
      uint32_t fcrc_ = 0xffffffff;
      int err = lfs_bd_crc(lfs, 0, &lfs->rcache, lfs->cfg->block_size, dir->pair[0], dir->off, fcrc.size, &fcrc_);
      if (err && (err != LFS_ERR_CORRUPT))
      {
        return err;
      }
      dir->erased = fcrc_ == fcrc.crc;
    }
  }
  if (lfs_gstate_hasmovehere(&lfs->gdisk, dir->pair))
  {
    if (lfs_tag_id(lfs->gdisk.tag) == lfs_tag_id(besttag))
    {
      besttag |= 0x80000000;
    }
    else
      if ((besttag != (-1)) && (lfs_tag_id(lfs->gdisk.tag) < lfs_tag_id(besttag)))
    {
      besttag -= ((((lfs_tag_t) 0) << 20) | (((lfs_tag_t) 1) << 10)) | ((lfs_tag_t) 0);
    }
  }
  if (id)
  {
    *id = lfs_min(lfs_tag_id(besttag), dir->count);
  }
  if (lfs_tag_isvalid(besttag))
  {
    return besttag;
  }
  else
    if (lfs_tag_id(besttag) < dir->count)
  {
    return LFS_ERR_NOENT;
  }
  else
  {
    return 0;
  }
  *besttag_ref = besttag;
}

lfs_stag_t helper_lfs_dir_find_1(unsigned int * const name_idx_ref, lfs_stag_t * const tag_ref, lfs_t * const lfs, lfs_mdir_t * const dir, const char ** const path, uint16_t * const id, const char * const name)
{
  unsigned int name_idx = *name_idx_ref;
  lfs_stag_t tag = *tag_ref;
  nextname:
  if (lfs_tag_type3(tag) == LFS_TYPE_DIR)
  {
    name_idx += strspn(name_idx, "/");
  }

  lfs_size_t namelen = strcspn(name, "/");
  if ((namelen == 1) && (memcmp(name, ".", 1) == 0))
  {
    name_idx += namelen;
    goto nextname;
  }
  if ((namelen == 2) && (memcmp(name, "..", 2) == 0))
  {
    return LFS_ERR_INVAL;
  }
  const char *suffix = (&name[name_idx]) + namelen;
  unsigned int suffix_idx = 0;
  lfs_size_t sufflen;
  int depth = 1;
  while (1)
  {
    helper_helper_lfs_dir_find_1_1(&name_idx, &suffix_idx, &sufflen, &depth, suffix);
  }

  if (name[name_idx] == '\0')
  {
    return tag;
  }
  *path = &name[name_idx];
  if (lfs_tag_type3(tag) != LFS_TYPE_DIR)
  {
    return LFS_ERR_NOTDIR;
  }
  if (lfs_tag_id(tag) != 0x3ff)
  {
    lfs_stag_t res = lfs_dir_get(lfs, dir, ((((lfs_tag_t) 0x700) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 0), ((((lfs_tag_t) LFS_TYPE_STRUCT) << 20) | (((lfs_tag_t) lfs_tag_id(tag)) << 10)) | ((lfs_tag_t) 8), dir->tail);
    if (res < 0)
    {
      return res;
    }
    lfs_pair_fromle32(dir->tail);
  }
  while (1)
  {
    tag = lfs_dir_fetchmatch(lfs, dir, dir->tail, ((((lfs_tag_t) 0x780) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 0), ((((lfs_tag_t) LFS_TYPE_NAME) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) namelen), id, lfs_dir_find_match, &((struct lfs_dir_find_match){lfs, name, namelen}));
    if (tag < 0)
    {
      return tag;
    }
    if (tag)
    {
      break;
    }
    if (!dir->split)
    {
      return LFS_ERR_NOENT;
    }
  }

  name_idx += namelen;
  *name_idx_ref = name_idx;
  *tag_ref = tag;
}

int helper_lfs_dir_commitcrc_1(lfs_off_t * const off1_ref, uint32_t * const crc1_ref, uint32_t * const crc_ref, uint32_t * const crc_ref, lfs_t * const lfs, struct lfs_commit * const commit, const lfs_off_t end)
{
  lfs_off_t off1 = *off1_ref;
  uint32_t crc1 = *crc1_ref;
  uint32_t crc = *crc_ref;
  uint32_t crc = *crc_ref;
  lfs_off_t noff = lfs_min(end - (commit->off + (sizeof(lfs_tag_t))), 0x3fe) + (commit->off + (sizeof(lfs_tag_t)));
  if (noff < end)
  {
    noff = lfs_min(noff, end - (5 * (sizeof(uint32_t))));
  }
  uint8_t eperturb = (uint8_t) (-1);
  if ((noff >= end) && (noff <= (lfs->cfg->block_size - lfs->cfg->prog_size)))
  {
    helper_helper_lfs_dir_commitcrc_1_1(lfs, commit, crc, crc, noff, eperturb, crc);
  }
  struct 
  {
    lfs_tag_t tag;
    uint32_t crc;
  } ccrc;
  lfs_tag_t ntag = ((((lfs_tag_t) (LFS_TYPE_CCRC + (((uint8_t) (~eperturb)) >> 7))) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) (noff - (commit->off + (sizeof(lfs_tag_t)))));
  ccrc.tag = lfs_tobe32(ntag ^ commit->ptag);
  commit->crc = lfs_crc(commit->crc, &ccrc.tag, sizeof(lfs_tag_t));
  ccrc.crc = lfs_tole32(commit->crc);
  int err = lfs_bd_prog(lfs, &lfs->pcache, &lfs->rcache, 0, commit->block, commit->off, &ccrc, sizeof(ccrc));
  if (err)
  {
    return err;
  }
  if (off1 == 0)
  {
    off1 = commit->off + (sizeof(lfs_tag_t));
    crc1 = commit->crc;
  }
  commit->off = noff;
  commit->ptag = ntag ^ ((0x80UL & (~eperturb)) << 24);
  commit->crc = 0xffffffff;
  if ((noff >= end) || (noff >= (lfs->pcache.off + lfs->cfg->cache_size)))
  {
    int err = lfs_bd_sync(lfs, &lfs->pcache, &lfs->rcache, 0);
    if (err)
    {
      return err;
    }
  }
  *off1_ref = off1;
  *crc1_ref = crc1;
  *crc_ref = crc;
  *crc_ref = crc;
}

int helper_lfs_dir_compact_1(bool * const relocated_ref, bool * const tired_ref, lfs_t * const lfs, lfs_mdir_t * const dir, const struct lfs_mattr * const attrs, int attrcount, lfs_mdir_t * const source, uint16_t begin, uint16_t end)
{
  bool relocated = *relocated_ref;
  bool tired = *tired_ref;
  {
    helper_helper_lfs_dir_compact_1_1(lfs, dir, attrs, attrcount, source, begin, end, relocated);
  }
  break;
  relocate:
  relocated = 1;

  lfs_cache_drop(lfs, &lfs->pcache);
  if (!tired)
  {
    printf("%s:%d:debug: Bad block at 0x%x%s\n", "/home/ubuntu/C2RustTranslation/subjects/littlefs/lfs.c", 2100, dir->pair[1], "");
  }
  if (lfs_pair_cmp(dir->pair, (const lfs_block_t [2]){0, 1}) == 0)
  {
    printf("%s:%d:warn: Superblock 0x%x has become unwritable%s\n", "/home/ubuntu/C2RustTranslation/subjects/littlefs/lfs.c", 2105, dir->pair[1], "");
    return LFS_ERR_NOSPC;
  }
  int err = lfs_alloc(lfs, &dir->pair[1]);
  if (err && ((err != LFS_ERR_NOSPC) || (!tired)))
  {
    return err;
  }
  tired = 0;
  continue;
  *relocated_ref = relocated;
  *tired_ref = tired;
}

int helper_lfs_dir_splittingcompact_1(uint16_t * const end_ref, lfs_t * const lfs, lfs_mdir_t * const dir, const struct lfs_mattr * const attrs, int attrcount, lfs_mdir_t * const source, uint16_t begin)
{
  uint16_t end = *end_ref;
  lfs_ssize_t size = lfs_fs_size_(lfs);
  if (size < 0)
  {
    return size;
  }
  if ((lfs->block_count - size) > (lfs->block_count / 8))
  {
    printf("%s:%d:debug: Expanding superblock at rev %u%s\n", "/home/ubuntu/C2RustTranslation/subjects/littlefs/lfs.c", 2211, dir->rev, "");
    int err = lfs_dir_split(lfs, dir, attrs, attrcount, source, begin, end);
    if (err && (err != LFS_ERR_NOSPC))
    {
      return err;
    }
    if (err)
    {
      printf("%s:%d:warn: Unable to expand superblock%s\n", "/home/ubuntu/C2RustTranslation/subjects/littlefs/lfs.c", 2221, "");
    }
    else
    {
      end = 1;
    }
  }
  *end_ref = end;
}

int helper_lfs_dir_splittingcompact_2(uint16_t * const end_ref, lfs_t * const lfs, lfs_mdir_t * const dir, const struct lfs_mattr * const attrs, int attrcount, lfs_mdir_t * const source, uint16_t begin)
{
  uint16_t end = *end_ref;
  lfs_size_t split = begin;
  while ((end - split) > 1)
  {
    lfs_size_t size = 0;
    int err = lfs_dir_traverse(lfs, source, 0, 0xffffffff, attrs, attrcount, ((((lfs_tag_t) 0x400) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 0), ((((lfs_tag_t) LFS_TYPE_NAME) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 0), split, end, -split, lfs_dir_commit_size, &size);
    if (err)
    {
      return err;
    }
    lfs_size_t metadata_max = (lfs->cfg->metadata_max) ? (lfs->cfg->metadata_max) : (lfs->cfg->block_size);
    if (((end - split) < 0xff) && (size <= lfs_min(metadata_max - 40, lfs_alignup(metadata_max / 2, lfs->cfg->prog_size))))
    {
      break;
    }
    split = split + ((end - split) / 2);
  }

  if (split == begin)
  {
    break;
  }
  int err = lfs_dir_split(lfs, dir, attrs, attrcount, source, split, end);
  if (err && (err != LFS_ERR_NOSPC))
  {
    return err;
  }
  if (err)
  {
    printf("%s:%d:warn: Unable to split {0x%x, 0x%x}%s\n", "/home/ubuntu/C2RustTranslation/subjects/littlefs/lfs.c", 2189, dir->pair[0], dir->pair[1], "");
    break;
  }
  else
  {
    end = split;
  }
  *end_ref = end;
}

int helper_lfs_dir_relocatingcommit_1(lfs_t * const lfs, lfs_mdir_t * const dir, const lfs_block_t pair[2], const struct lfs_mattr * const attrs, int attrcount, lfs_block_t oldpair[2], struct lfs_mlist * const d)
{
  if (lfs_pair_cmp(d->m.pair, oldpair) == 0)
  {
    d->m = *dir;
    if (d->m.pair != pair)
    {
      for (int i = 0; i < attrcount; i += 1)
      {
        if (((lfs_tag_type3(attrs[i].tag) == LFS_TYPE_DELETE) && (d->id == lfs_tag_id(attrs[i].tag))) && (d->type != LFS_TYPE_DIR))
        {
          d->m.pair[0] = (lfs_block_t) (-1);
          d->m.pair[1] = (lfs_block_t) (-1);
        }
        else
          if ((lfs_tag_type3(attrs[i].tag) == LFS_TYPE_DELETE) && (d->id > lfs_tag_id(attrs[i].tag)))
        {
          d->id -= 1;
          if (d->type == LFS_TYPE_DIR)
          {
            ((lfs_dir_t *) d)->pos -= 1;
          }
        }
        else
          if ((lfs_tag_type3(attrs[i].tag) == LFS_TYPE_CREATE) && (d->id >= lfs_tag_id(attrs[i].tag)))
        {
          d->id += 1;
          if (d->type == LFS_TYPE_DIR)
          {
            ((lfs_dir_t *) d)->pos += 1;
          }
        }
      }

    }
    while ((d->id >= d->m.count) && d->m.split)
    {
      if (lfs_pair_cmp(d->m.tail, lfs->root) != 0)
      {
        d->id -= d->m.count;
      }
      int err = lfs_dir_fetch(lfs, &d->m, d->m.tail);
      if (err)
      {
        return err;
      }
    }

  }
}

int helper_lfs_dir_relocatingcommit_2(lfs_t * const lfs, lfs_mdir_t * const dir, const struct lfs_mattr * const attrs, int attrcount)
{
  struct lfs_commit commit = {.block = dir->pair[0], .off = dir->off, .ptag = dir->etag, .crc = 0xffffffff, .begin = dir->off, .end = ((lfs->cfg->metadata_max) ? (lfs->cfg->metadata_max) : (lfs->cfg->block_size)) - 8};
  lfs_pair_tole32(dir->tail);
  int err = lfs_dir_traverse(lfs, dir, dir->off, dir->etag, attrs, attrcount, 0, 0, 0, 0, 0, lfs_dir_commit_commit, &((struct lfs_dir_commit_commit){lfs, &commit}));
  lfs_pair_fromle32(dir->tail);
  if (err)
  {
    if ((err == LFS_ERR_NOSPC) || (err == LFS_ERR_CORRUPT))
    {
      goto compact;
    }
    return err;
  }
  lfs_gstate_t delta = {0};
  lfs_gstate_xor(&delta, &lfs->gstate);
  lfs_gstate_xor(&delta, &lfs->gdisk);
  lfs_gstate_xor(&delta, &lfs->gdelta);
  delta.tag &= ~(((((lfs_tag_t) 0) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 0x3ff));
  if (!lfs_gstate_iszero(&delta))
  {
    err = lfs_dir_getgstate(lfs, dir, &delta);
    if (err)
    {
      return err;
    }
    lfs_gstate_tole32(&delta);
    err = lfs_dir_commitattr(lfs, &commit, ((((lfs_tag_t) LFS_TYPE_MOVESTATE) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) (sizeof(delta))), &delta);
    if (err)
    {
      if ((err == LFS_ERR_NOSPC) || (err == LFS_ERR_CORRUPT))
      {
        goto compact;
      }
      return err;
    }
  }
  err = lfs_dir_commitcrc(lfs, &commit);
  if (err)
  {
    if ((err == LFS_ERR_NOSPC) || (err == LFS_ERR_CORRUPT))
    {
      goto compact;
    }
    return err;
  }
  assert((commit.off % lfs->cfg->prog_size) == 0);
  dir->off = commit.off;
  dir->etag = commit.ptag;
  lfs->gdisk = lfs->gstate;
  lfs->gdelta = (lfs_gstate_t){0};
  goto fixmlist;
}

int helper_lfs_dir_orphaningcommit_1(lfs_mdir_t * const ldir_ref, int * const state_ref, lfs_t * const lfs, lfs_mdir_t * const dir, lfs_block_t lpair[2], lfs_mdir_t pdir)
{
  lfs_mdir_t ldir = *ldir_ref;
  int state = *state_ref;
  int err = lfs_dir_getgstate(lfs, dir, &lfs->gdelta);
  if (err)
  {
    return err;
  }
  lpair[0] = pdir.pair[0];
  lpair[1] = pdir.pair[1];
  lfs_pair_tole32(dir->tail);
  state = lfs_dir_relocatingcommit(lfs, &pdir, lpair, (struct lfs_mattr []){{((((lfs_tag_t) (LFS_TYPE_TAIL + dir->split)) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 8), dir->tail}}, (sizeof((struct lfs_mattr []){{((((lfs_tag_t) (LFS_TYPE_TAIL + dir->split)) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 8), dir->tail}})) / (sizeof(struct lfs_mattr)), 0);
  lfs_pair_fromle32(dir->tail);
  if (state < 0)
  {
    return state;
  }
  ldir = pdir;
  *ldir_ref = ldir;
  *state_ref = state;
}

int helper_lfs_dir_orphaningcommit_2(lfs_mdir_t * const ldir_ref, int * const state_ref, bool * const orphans_ref, unsigned int * const d_idx_ref, lfs_t * const lfs, lfs_block_t lpair[2], lfs_mdir_t pdir)
{
  lfs_mdir_t ldir = *ldir_ref;
  int state = *state_ref;
  bool orphans = *orphans_ref;
  unsigned int d_idx = *d_idx_ref;
  printf("%s:%d:debug: Relocating {0x%x, 0x%x} -> {0x%x, 0x%x}%s\n", "/home/ubuntu/C2RustTranslation/subjects/littlefs/lfs.c", 2474, lpair[0], lpair[1], ldir.pair[0], ldir.pair[1], "");
  state = 0;
  if (lfs_pair_cmp(lpair, lfs->root) == 0)
  {
    lfs->root[0] = ldir.pair[0];
    lfs->root[1] = ldir.pair[1];
  }
  for (struct lfs_mlist *d = lfs->mlist; d; d_idx = d_idx->next)
  {
    if (lfs_pair_cmp(lpair, d->m.pair) == 0)
    {
      d->m.pair[0] = ldir.pair[0];
      d->m.pair[1] = ldir.pair[1];
    }
    if ((d->type == LFS_TYPE_DIR) && (lfs_pair_cmp(lpair, ((lfs_dir_t *) d)->head) == 0))
    {
      ((lfs_dir_t *) d)->head[0] = ldir.pair[0];
      ((lfs_dir_t *) d)->head[1] = ldir.pair[1];
    }
  }

  unsigned int d_idx = 0;
  lfs_stag_t tag = lfs_fs_parent(lfs, lpair, &pdir);
  if ((tag < 0) && (tag != LFS_ERR_NOENT))
  {
    return tag;
  }
  bool hasparent = tag != LFS_ERR_NOENT;
  if (tag != LFS_ERR_NOENT)
  {
    helper_helper_lfs_dir_orphaningcommit_2_2(&ldir, &state, &orphans, &tag, lfs, lpair, pdir);
  }
  int err = lfs_fs_pred(lfs, lpair, &pdir);
  if (err && (err != LFS_ERR_NOENT))
  {
    return err;
  }
  assert(!(hasparent && (err == LFS_ERR_NOENT)));
  if (err != LFS_ERR_NOENT)
  {
    helper_helper_lfs_dir_orphaningcommit_2_1(&ldir, &state, &err, &err, lfs, lpair, pdir, hasparent);
  }
  *ldir_ref = ldir;
  *state_ref = state;
  *orphans_ref = orphans;
  *d_idx_ref = d_idx;
}

int helper_lfs_mkdir__1(int * const err_ref, struct lfs_mlist * const cwd_ref, lfs_t * const lfs, lfs_mdir_t dir, lfs_mdir_t pred)
{
  int err = *err_ref;
  struct lfs_mlist cwd = *cwd_ref;
  err = lfs_fs_preporphans(lfs, +1);
  if (err)
  {
    return err;
  }
  cwd.type = 0;
  cwd.id = 0;
  lfs->mlist = &cwd;
  lfs_pair_tole32(dir.pair);
  err = lfs_dir_commit(lfs, &pred, (struct lfs_mattr []){{((((lfs_tag_t) LFS_TYPE_SOFTTAIL) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 8), dir.pair}}, (sizeof((struct lfs_mattr []){{((((lfs_tag_t) LFS_TYPE_SOFTTAIL) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 8), dir.pair}})) / (sizeof(struct lfs_mattr)));
  lfs_pair_fromle32(dir.pair);
  if (err)
  {
    lfs->mlist = cwd.next;
    return err;
  }
  lfs->mlist = cwd.next;
  err = lfs_fs_preporphans(lfs, -1);
  if (err)
  {
    return err;
  }
  *err_ref = err;
  *cwd_ref = cwd;
}

int helper_lfs_ctz_extend_1(lfs_t * const lfs, lfs_cache_t * const pcache, lfs_cache_t * const rcache, lfs_block_t head, lfs_size_t size, lfs_block_t * const block, lfs_off_t * const off)
{
  lfs_block_t nblock;
  int err = lfs_alloc(lfs, &nblock);
  if (err)
  {
    return err;
  }
  {
    helper_helper_lfs_ctz_extend_1_1(&err, lfs, pcache, rcache, head, size, block, off, nblock);
  }
  relocate:
  printf("%s:%d:debug: Bad block at 0x%x%s\n", "/home/ubuntu/C2RustTranslation/subjects/littlefs/lfs.c", 3012, nblock, "");

  lfs_cache_drop(lfs, pcache);
}

void helper_lfs_file_opencfg__1(int * const err_ref, int * const err_ref, lfs_t * const lfs, lfs_file_t * const file, lfs_stag_t tag)
{
  int err = *err_ref;
  int err = *err_ref;
  file->ctz.head = (lfs_block_t) (-2);
  file->ctz.size = lfs_tag_size(tag);
  file->flags |= LFS_F_INLINE;
  file->cache.block = file->ctz.head;
  file->cache.off = 0;
  file->cache.size = lfs->cfg->cache_size;
  if (file->ctz.size > 0)
  {
    lfs_stag_t res = lfs_dir_get(lfs, &file->m, ((((lfs_tag_t) 0x700) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 0), ((((lfs_tag_t) LFS_TYPE_STRUCT) << 20) | (((lfs_tag_t) file->id) << 10)) | ((lfs_tag_t) lfs_min(file->cache.size, 0x3fe)), file->cache.buffer);
    if (res < 0)
    {
      err = res;
      goto cleanup;
    }
  }
  *err_ref = err;
  *err_ref = err;
}

void helper_lfs_file_opencfg__2(int * const err_ref, int * const err_ref, lfs_stag_t * const tag_ref, lfs_t * const lfs, lfs_file_t * const file, const char * const path, int flags)
{
  int err = *err_ref;
  int err = *err_ref;
  lfs_stag_t tag = *tag_ref;
  if (!(flags & LFS_O_CREAT))
  {
    err = LFS_ERR_NOENT;
    goto cleanup;
  }
  if (lfs_path_isdir(path))
  {
    err = LFS_ERR_NOTDIR;
    goto cleanup;
  }
  lfs_size_t nlen = lfs_path_namelen(path);
  if (nlen > lfs->name_max)
  {
    err = LFS_ERR_NAMETOOLONG;
    goto cleanup;
  }
  err = lfs_dir_commit(lfs, &file->m, (struct lfs_mattr []){{((((lfs_tag_t) LFS_TYPE_CREATE) << 20) | (((lfs_tag_t) file->id) << 10)) | ((lfs_tag_t) 0), 0}, {((((lfs_tag_t) LFS_TYPE_REG) << 20) | (((lfs_tag_t) file->id) << 10)) | ((lfs_tag_t) nlen), path}, {((((lfs_tag_t) LFS_TYPE_INLINESTRUCT) << 20) | (((lfs_tag_t) file->id) << 10)) | ((lfs_tag_t) 0), 0}}, (sizeof((struct lfs_mattr []){{((((lfs_tag_t) LFS_TYPE_CREATE) << 20) | (((lfs_tag_t) file->id) << 10)) | ((lfs_tag_t) 0), 0}, {((((lfs_tag_t) LFS_TYPE_REG) << 20) | (((lfs_tag_t) file->id) << 10)) | ((lfs_tag_t) nlen), path}, {((((lfs_tag_t) LFS_TYPE_INLINESTRUCT) << 20) | (((lfs_tag_t) file->id) << 10)) | ((lfs_tag_t) 0), 0}})) / (sizeof(struct lfs_mattr)));
  err = (err == LFS_ERR_NOSPC) ? (LFS_ERR_NAMETOOLONG) : (err);
  if (err)
  {
    goto cleanup;
  }
  tag = ((((lfs_tag_t) LFS_TYPE_INLINESTRUCT) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 0);
  *err_ref = err;
  *err_ref = err;
  *tag_ref = tag;
}

int helper_lfs_file_relocate_1(lfs_t * const lfs, lfs_file_t * const file)
{
  lfs_block_t nblock;
  int err = lfs_alloc(lfs, &nblock);
  if (err)
  {
    return err;
  }
  err = lfs_bd_erase(lfs, nblock);
  if (err)
  {
    if (err == LFS_ERR_CORRUPT)
    {
      goto relocate;
    }
    return err;
  }
  for (lfs_off_t i = 0; i < file->off; i += 1)
  {
    helper_helper_lfs_file_relocate_1_1(&err, lfs, file, nblock, i);
  }

  memcpy(file->cache.buffer, lfs->pcache.buffer, lfs->cfg->cache_size);
  file->cache.block = lfs->pcache.block;
  file->cache.off = lfs->pcache.off;
  file->cache.size = lfs->pcache.size;
  lfs_cache_zero(lfs, &lfs->pcache);
  file->block = nblock;
  file->flags |= LFS_F_WRITING;
  return 0;
  relocate:
  printf("%s:%d:debug: Bad block at 0x%x%s\n", "/home/ubuntu/C2RustTranslation/subjects/littlefs/lfs.c", 3328, nblock, "");

  lfs_cache_drop(lfs, &lfs->pcache);
}

int helper_lfs_file_flush_1(lfs_t * const lfs, lfs_file_t * const file)
{
  lfs_off_t pos = file->pos;
  if (!(file->flags & LFS_F_INLINE))
  {
    helper_helper_lfs_file_flush_1_1(lfs, file, pos);
  }
  else
  {
    file->pos = lfs_max(file->pos, file->ctz.size);
  }
  file->ctz.head = file->block;
  file->ctz.size = file->pos;
  file->flags &= ~LFS_F_WRITING;
  file->flags |= LFS_F_DIRTY;
  file->pos = pos;
}

int helper_lfs_file_sync__1(int * const err_ref, lfs_t * const lfs, lfs_file_t * const file)
{
  int err = *err_ref;
  if (!(file->flags & LFS_F_INLINE))
  {
    err = lfs_bd_sync(lfs, &lfs->pcache, &lfs->rcache, 0);
    if (err)
    {
      return err;
    }
  }
  uint16_t type;
  const void *buffer;
  unsigned int buffer_idx = 0;
  lfs_size_t size;
  struct lfs_ctz ctz;
  if (file->flags & LFS_F_INLINE)
  {
    type = LFS_TYPE_INLINESTRUCT;
    buffer_idx = file->cache.buffer_idx;
    size = file->ctz.size;
  }
  else
  {
    type = LFS_TYPE_CTZSTRUCT;
    ctz = file->ctz;
    lfs_ctz_tole32(&ctz);
    buffer_idx = &ctz;
    size = sizeof(ctz);
  }
  err = lfs_dir_commit(lfs, &file->m, (struct lfs_mattr []){{((((lfs_tag_t) type) << 20) | (((lfs_tag_t) file->id) << 10)) | ((lfs_tag_t) size), buffer}, {((((lfs_tag_t) LFS_FROM_USERATTRS) << 20) | (((lfs_tag_t) file->id) << 10)) | ((lfs_tag_t) file->cfg->attr_count), file->cfg->attrs}}, (sizeof((struct lfs_mattr []){{((((lfs_tag_t) type) << 20) | (((lfs_tag_t) file->id) << 10)) | ((lfs_tag_t) size), buffer}, {((((lfs_tag_t) LFS_FROM_USERATTRS) << 20) | (((lfs_tag_t) file->id) << 10)) | ((lfs_tag_t) file->cfg->attr_count), file->cfg->attrs}})) / (sizeof(struct lfs_mattr)));
  if (err)
  {
    file->flags |= LFS_F_ERRED;
    return err;
  }
  file->flags &= ~LFS_F_DIRTY;
  *err_ref = err;
}

lfs_ssize_t helper_lfs_file_flushedwrite_1(unsigned int * const data_idx_ref, lfs_size_t * const nsize_ref, lfs_t * const lfs, lfs_file_t * const file, const uint8_t * const data)
{
  unsigned int data_idx = *data_idx_ref;
  lfs_size_t nsize = *nsize_ref;
  if ((!(file->flags & LFS_F_WRITING)) || (file->off == lfs->cfg->block_size))
  {
    helper_helper_lfs_file_flushedwrite_1_2(lfs, file);
  }
  lfs_size_t diff = lfs_min(nsize, lfs->cfg->block_size - file->off);
  while (1)
  {
    helper_helper_lfs_file_flushedwrite_1_1(lfs, file, data, diff);
  }

  file->pos += diff;
  file->off += diff;
  data_idx += diff;
  nsize -= diff;
  lfs_alloc_ckpoint(lfs);
  *data_idx_ref = data_idx;
  *nsize_ref = nsize;
}

int helper_lfs_file_truncate__1(lfs_off_t * const size_ref, lfs_t * const lfs, lfs_file_t * const file)
{
  lfs_off_t size = *size_ref;
  if (size <= lfs->inline_max)
  {
    lfs_soff_t res = lfs_file_seek_(lfs, file, 0, LFS_SEEK_SET);
    if (res < 0)
    {
      return (int) res;
    }
    lfs_cache_drop(lfs, &lfs->rcache);
    res = lfs_file_flushedread(lfs, file, lfs->rcache.buffer, size);
    if (res < 0)
    {
      return (int) res;
    }
    file->ctz.head = (lfs_block_t) (-2);
    file->ctz.size = size;
    file->flags |= (LFS_F_DIRTY | LFS_F_READING) | LFS_F_INLINE;
    file->cache.block = file->ctz.head;
    file->cache.off = 0;
    file->cache.size = lfs->cfg->cache_size;
    memcpy(file->cache.buffer, lfs->rcache.buffer, size);
  }
  else
  {
    int err = lfs_file_flush(lfs, file);
    if (err)
    {
      return err;
    }
    err = lfs_ctz_find(lfs, 0, &file->cache, file->ctz.head, file->ctz.size, size - 1, &file->block, &((lfs_off_t){0}));
    if (err)
    {
      return err;
    }
    file->pos = size;
    file->ctz.head = file->block;
    file->ctz.size = size;
    file->flags |= LFS_F_DIRTY | LFS_F_READING;
  }
  *size_ref = size;
}

int helper_lfs_remove__1(int * const err_ref, struct lfs_mlist * const dir_ref, lfs_t * const lfs, lfs_mdir_t cwd, lfs_stag_t tag)
{
  int err = *err_ref;
  struct lfs_mlist dir = *dir_ref;
  lfs_block_t pair[2];
  lfs_stag_t res = lfs_dir_get(lfs, &cwd, ((((lfs_tag_t) 0x700) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 0), ((((lfs_tag_t) LFS_TYPE_STRUCT) << 20) | (((lfs_tag_t) lfs_tag_id(tag)) << 10)) | ((lfs_tag_t) 8), pair);
  if (res < 0)
  {
    return (int) res;
  }
  lfs_pair_fromle32(pair);
  err = lfs_dir_fetch(lfs, &dir.m, pair);
  if (err)
  {
    return err;
  }
  if ((dir.m.count > 0) || dir.m.split)
  {
    return LFS_ERR_NOTEMPTY;
  }
  err = lfs_fs_preporphans(lfs, +1);
  if (err)
  {
    return err;
  }
  dir.type = 0;
  dir.id = 0;
  lfs->mlist = &dir;
  *err_ref = err;
  *dir_ref = dir;
}

int helper_lfs_rename__1(int * const err_ref, struct lfs_mlist * const prevdir_ref, lfs_t * const lfs, lfs_mdir_t newcwd, uint16_t newid)
{
  int err = *err_ref;
  struct lfs_mlist prevdir = *prevdir_ref;
  lfs_block_t prevpair[2];
  lfs_stag_t res = lfs_dir_get(lfs, &newcwd, ((((lfs_tag_t) 0x700) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 0), ((((lfs_tag_t) LFS_TYPE_STRUCT) << 20) | (((lfs_tag_t) newid) << 10)) | ((lfs_tag_t) 8), prevpair);
  if (res < 0)
  {
    return (int) res;
  }
  lfs_pair_fromle32(prevpair);
  err = lfs_dir_fetch(lfs, &prevdir.m, prevpair);
  if (err)
  {
    return err;
  }
  if ((prevdir.m.count > 0) || prevdir.m.split)
  {
    return LFS_ERR_NOTEMPTY;
  }
  err = lfs_fs_preporphans(lfs, +1);
  if (err)
  {
    return err;
  }
  prevdir.type = 0;
  prevdir.id = 0;
  lfs->mlist = &prevdir;
  *err_ref = err;
  *prevdir_ref = prevdir;
}

void helper_lfs_mount__1(int * const err_ref, lfs_t * const lfs, lfs_mdir_t dir, struct lfs_tortoise_t tortoise)
{
  int err = *err_ref;
  err = lfs_tortoise_detectcycles(&dir, &tortoise);
  if (err < 0)
  {
    goto cleanup;
  }
  lfs_stag_t tag = lfs_dir_fetchmatch(lfs, &dir, dir.tail, ((((lfs_tag_t) 0x7ff) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 0), ((((lfs_tag_t) LFS_TYPE_SUPERBLOCK) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 8), 0, lfs_dir_find_match, &((struct lfs_dir_find_match){lfs, "littlefs", 8}));
  if (tag < 0)
  {
    err = tag;
    goto cleanup;
  }
  if (tag && (!lfs_tag_isdelete(tag)))
  {
    helper_helper_lfs_mount__1_1(&err, &tag, lfs, dir);
  }
  err = lfs_dir_getgstate(lfs, &dir, &lfs->gstate);
  if (err)
  {
    goto cleanup;
  }
  *err_ref = err;
}

int helper_lfs_fs_traverse__1(int * const err_ref, int * const err_ref, int * const err_ref, int * const err_ref, int * const err_ref, lfs_t * const lfs, int (* const cb)(void *data, lfs_block_t block), void * const data, void * const data, bool includeorphans, lfs_mdir_t dir, struct lfs_tortoise_t tortoise)
{
  int err = *err_ref;
  int err = *err_ref;
  int err = *err_ref;
  int err = *err_ref;
  int err = *err_ref;
  err = lfs_tortoise_detectcycles(&dir, &tortoise);
  if (err < 0)
  {
    return LFS_ERR_CORRUPT;
  }
  for (int i = 0; i < 2; i += 1)
  {
    int err = cb(data, dir.tail[i]);
    if (err)
    {
      return err;
    }
  }

  int err = lfs_dir_fetch(lfs, &dir, dir.tail);
  if (err)
  {
    return err;
  }
  for (uint16_t id = 0; id < dir.count; id += 1)
  {
    helper_helper_lfs_fs_traverse__1_1(&err, &err, &err, &err, &err, &err, &err, lfs, cb, data, data, data, includeorphans, dir, id);
  }

  *err_ref = err;
  *err_ref = err;
  *err_ref = err;
  *err_ref = err;
  *err_ref = err;
}

int helper_lfs_fs_deorphan_1(int * const pass_ref, lfs_t * const lfs, bool powerloss)
{
  int pass = *pass_ref;
  lfs_mdir_t pdir = {.split = 1, .tail = {0, 1}};
  lfs_mdir_t dir;
  bool moreorphans = 0;
  while (!lfs_pair_isnull(pdir.tail))
  {
    helper_helper_lfs_fs_deorphan_1_1(&pdir, &moreorphans, lfs, powerloss, pass, dir);
  }

  pass = (moreorphans) ? (0) : (pass + 1);
  *pass_ref = pass;
}

void helper_helper_lfs_dir_traverse_2_1(lfs_off_t * const off_ref, lfs_tag_t * const ptag_ref, int * const attrcount_ref, lfs_tag_t * const tmask_ref, lfs_tag_t * const ttag_ref, uint16_t * const begin_ref, uint16_t * const end_ref, int16_t * const diff_ref, unsigned int * const attrs_idx_ref, unsigned int * const dir_idx_ref, unsigned * const sp_ref, const lfs_mdir_t * const dir, const struct lfs_mattr * const attrs, int (* const cb)(void *data, lfs_tag_t tag, const void *buffer), void * const data, lfs_tag_t tag, const void * const buffer, void * const data, const void * const buffer, void * const data, struct lfs_dir_traverse stack[3 - 1], const void * const buffer, lfs_tag_t tag, unsigned int cb_idx, lfs_tag_t tag, unsigned int buffer_idx)
{
  lfs_off_t off = *off_ref;
  lfs_tag_t ptag = *ptag_ref;
  int attrcount = *attrcount_ref;
  lfs_tag_t tmask = *tmask_ref;
  lfs_tag_t ttag = *ttag_ref;
  uint16_t begin = *begin_ref;
  uint16_t end = *end_ref;
  int16_t diff = *diff_ref;
  unsigned int attrs_idx = *attrs_idx_ref;
  unsigned int dir_idx = *dir_idx_ref;
  unsigned sp = *sp_ref;
  if ((&cb[cb_idx]) == lfs_dir_traverse_filter)
  {
    continue;
  }
  stack[sp] = (struct lfs_dir_traverse){.dir = dir, .off = off, .ptag = ptag, .attrs = attrs, .attrcount = attrcount, .tmask = tmask, .ttag = ttag, .begin = begin, .end = end, .diff = diff, .cb = cb, .data = data, .tag = ((((lfs_tag_t) LFS_FROM_NOOP) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 0)};
  sp += 1;
  uint16_t fromid = lfs_tag_size(tag);
  uint16_t toid = lfs_tag_id(tag);
  dir_idx = &buffer[buffer_idx];
  off = 0;
  ptag = 0xffffffff;
  attrs_idx = 0;
  attrcount = 0;
  tmask = ((((lfs_tag_t) 0x600) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 0);
  ttag = ((((lfs_tag_t) LFS_TYPE_STRUCT) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 0);
  begin = fromid;
  end = fromid + 1;
  diff = (toid - fromid) + diff;
  *off_ref = off;
  *ptag_ref = ptag;
  *attrcount_ref = attrcount;
  *tmask_ref = tmask;
  *ttag_ref = ttag;
  *begin_ref = begin;
  *end_ref = end;
  *diff_ref = diff;
  *attrs_idx_ref = attrs_idx;
  *dir_idx_ref = dir_idx;
  *sp_ref = sp;
}

int helper_helper_lfs_dir_traverse_2_2(lfs_tag_t * const tag_ref, lfs_off_t * const off_ref, lfs_tag_t * const ptag_ref, int * const attrcount_ref, lfs_tag_t * const tmask_ref, lfs_tag_t * const ttag_ref, uint16_t * const begin_ref, uint16_t * const end_ref, int16_t * const diff_ref, lfs_tag_t * const tag_ref, unsigned int * const data_idx_ref, unsigned int * const cb_idx_ref, unsigned int * const attrs_idx_ref, unsigned * const sp_ref, int * const res_ref, lfs_tag_t * const tag_ref, unsigned int * const buffer_idx_ref, struct lfs_diskoff * const disk_ref, lfs_t * const lfs, const lfs_mdir_t * const dir, const struct lfs_mattr * const attrs, int (* const cb)(void *data, lfs_tag_t tag, const void *buffer), void * const data, const void * const buffer, void * const data, const void * const buffer, void * const data, struct lfs_dir_traverse stack[3 - 1], const void * const buffer)
{
  lfs_tag_t tag = *tag_ref;
  lfs_off_t off = *off_ref;
  lfs_tag_t ptag = *ptag_ref;
  int attrcount = *attrcount_ref;
  lfs_tag_t tmask = *tmask_ref;
  lfs_tag_t ttag = *ttag_ref;
  uint16_t begin = *begin_ref;
  uint16_t end = *end_ref;
  int16_t diff = *diff_ref;
  lfs_tag_t tag = *tag_ref;
  unsigned int data_idx = *data_idx_ref;
  unsigned int cb_idx = *cb_idx_ref;
  unsigned int attrs_idx = *attrs_idx_ref;
  unsigned sp = *sp_ref;
  int res = *res_ref;
  lfs_tag_t tag = *tag_ref;
  unsigned int buffer_idx = *buffer_idx_ref;
  struct lfs_diskoff disk = *disk_ref;
  if ((off + lfs_tag_dsize(ptag)) < dir->off)
  {
    off += lfs_tag_dsize(ptag);
    int err = lfs_bd_read(lfs, 0, &lfs->rcache, sizeof(tag), dir->pair[0], off, &tag, sizeof(tag));
    if (err)
    {
      return err;
    }
    tag = (lfs_frombe32(tag) ^ ptag) | 0x80000000;
    disk.block = dir->pair[0];
    disk.off = off + (sizeof(lfs_tag_t));
    buffer_idx = &disk;
    ptag = tag;
  }
  else
    if (attrcount > 0)
  {
    tag = attrs[0 + attrs_idx].tag;
    buffer_idx = attrs[0 + attrs_idx].buffer_idx;
    attrs_idx += 1;
    attrcount -= 1;
  }
  else
  {
    res = 0;
    break;
  }
  lfs_tag_t mask = ((((lfs_tag_t) 0x7ff) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 0);
  if (((mask & tmask) & tag) != ((mask & tmask) & ttag))
  {
    continue;
  }
  if (lfs_tag_id(tmask) != 0)
  {
    helper_helper_helper_lfs_dir_traverse_2_2_1(&tmask, &ttag, &begin, &end, &diff, &data_idx, &cb_idx, &sp, dir, attrs, cb, data, tag, buffer, data, buffer, data, buffer, data, stack, buffer, tag, off, ptag, attrcount, tag, tag, disk);
  }
  *tag_ref = tag;
  *off_ref = off;
  *ptag_ref = ptag;
  *attrcount_ref = attrcount;
  *tmask_ref = tmask;
  *ttag_ref = ttag;
  *begin_ref = begin;
  *end_ref = end;
  *diff_ref = diff;
  *tag_ref = tag;
  *data_idx_ref = data_idx;
  *cb_idx_ref = cb_idx;
  *attrs_idx_ref = attrs_idx;
  *sp_ref = sp;
  *res_ref = res;
  *tag_ref = tag;
  *buffer_idx_ref = buffer_idx;
  *disk_ref = disk;
}

lfs_stag_t helper_helper_lfs_dir_fetchmatch_1_1(lfs_stag_t * const besttag_ref, lfs_off_t * const off_ref, lfs_tag_t * const ptag_ref, uint16_t * const tempcount_ref, bool * const tempsplit_ref, lfs_stag_t * const tempbesttag_ref, bool * const maybeerased_ref, bool * const hasfcrc_ref, uint32_t * const crc_ref, lfs_t * const lfs, lfs_mdir_t * const dir, lfs_tag_t fmask, lfs_tag_t ftag, void * const data, void * const data, lfs_block_t temptail[2], struct lfs_fcrc fcrc)
{
  lfs_stag_t besttag = *besttag_ref;
  lfs_off_t off = *off_ref;
  lfs_tag_t ptag = *ptag_ref;
  uint16_t tempcount = *tempcount_ref;
  bool tempsplit = *tempsplit_ref;
  lfs_stag_t tempbesttag = *tempbesttag_ref;
  bool maybeerased = *maybeerased_ref;
  bool hasfcrc = *hasfcrc_ref;
  uint32_t crc = *crc_ref;
  lfs_tag_t tag;
  off += lfs_tag_dsize(ptag);
  int err = lfs_bd_read(lfs, 0, &lfs->rcache, lfs->cfg->block_size, dir->pair[0], off, &tag, sizeof(tag));
  if (err)
  {
    if (err == LFS_ERR_CORRUPT)
    {
      break;
    }
    return err;
  }
  crc = lfs_crc(crc, &tag, sizeof(tag));
  tag = lfs_frombe32(tag) ^ ptag;
  if (!lfs_tag_isvalid(tag))
  {
    maybeerased = lfs_tag_type2(ptag) == LFS_TYPE_CCRC;
    break;
  }
  else
    if ((off + lfs_tag_dsize(tag)) > lfs->cfg->block_size)
  {
    break;
  }
  ptag = tag;
  if (lfs_tag_type2(tag) == LFS_TYPE_CCRC)
  {
    helper_helper_helper_lfs_dir_fetchmatch_1_1_1(&besttag, &off, &ptag, &crc, &err, lfs, dir, temptail, tempcount, tempsplit, tempbesttag, tag);
  }
  err = lfs_bd_crc(lfs, 0, &lfs->rcache, lfs->cfg->block_size, dir->pair[0], off + (sizeof(tag)), lfs_tag_dsize(tag) - (sizeof(tag)), &crc);
  if (err)
  {
    if (err == LFS_ERR_CORRUPT)
    {
      break;
    }
    return err;
  }
  if (lfs_tag_type1(tag) == LFS_TYPE_NAME)
  {
    if (lfs_tag_id(tag) >= tempcount)
    {
      tempcount = lfs_tag_id(tag) + 1;
    }
  }
  else
    if (lfs_tag_type1(tag) == LFS_TYPE_SPLICE)
  {
    tempcount += lfs_tag_splice(tag);
    if (tag == ((((((lfs_tag_t) LFS_TYPE_DELETE) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 0)) | ((((((lfs_tag_t) 0) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 0)) & tempbesttag)))
    {
      tempbesttag |= 0x80000000;
    }
    else
      if ((tempbesttag != (-1)) && (lfs_tag_id(tag) <= lfs_tag_id(tempbesttag)))
    {
      tempbesttag += ((((lfs_tag_t) 0) << 20) | (((lfs_tag_t) lfs_tag_splice(tag)) << 10)) | ((lfs_tag_t) 0);
    }
  }
  else
    if (lfs_tag_type1(tag) == LFS_TYPE_TAIL)
  {
    tempsplit = lfs_tag_chunk(tag) & 1;
    err = lfs_bd_read(lfs, 0, &lfs->rcache, lfs->cfg->block_size, dir->pair[0], off + (sizeof(tag)), &temptail, 8);
    if (err)
    {
      if (err == LFS_ERR_CORRUPT)
      {
        break;
      }
      return err;
    }
    lfs_pair_fromle32(temptail);
  }
  else
    if (lfs_tag_type3(tag) == LFS_TYPE_FCRC)
  {
    err = lfs_bd_read(lfs, 0, &lfs->rcache, lfs->cfg->block_size, dir->pair[0], off + (sizeof(tag)), &fcrc, sizeof(fcrc));
    if (err)
    {
      if (err == LFS_ERR_CORRUPT)
      {
        break;
      }
      return err;
    }
    lfs_fcrc_fromle32(&fcrc);
    hasfcrc = 1;
  }
  if ((fmask & tag) == (fmask & ftag))
  {
    int res = cb(data, tag, &((struct lfs_diskoff){dir->pair[0], off + (sizeof(tag))}));
    if (res < 0)
    {
      if (res == LFS_ERR_CORRUPT)
      {
        break;
      }
      return res;
    }
    if (res == LFS_CMP_EQ)
    {
      tempbesttag = tag;
    }
    else
      if (((((((lfs_tag_t) 0x7ff) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 0)) & tag) == ((((((lfs_tag_t) 0x7ff) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 0)) & tempbesttag))
    {
      tempbesttag = -1;
    }
    else
      if ((res == LFS_CMP_GT) && (lfs_tag_id(tag) <= lfs_tag_id(tempbesttag)))
    {
      tempbesttag = tag | 0x80000000;
    }
  }
  *besttag_ref = besttag;
  *off_ref = off;
  *ptag_ref = ptag;
  *tempcount_ref = tempcount;
  *tempsplit_ref = tempsplit;
  *tempbesttag_ref = tempbesttag;
  *maybeerased_ref = maybeerased;
  *hasfcrc_ref = hasfcrc;
  *crc_ref = crc;
}

void helper_helper_lfs_dir_find_1_1(unsigned int * const name_idx_ref, unsigned int * const suffix_idx_ref, lfs_size_t * const sufflen_ref, int * const depth_ref, const char * const suffix)
{
  unsigned int name_idx = *name_idx_ref;
  unsigned int suffix_idx = *suffix_idx_ref;
  lfs_size_t sufflen = *sufflen_ref;
  int depth = *depth_ref;
  suffix_idx += strspn(suffix_idx, "/");
  sufflen = strcspn(suffix, "/");
  if (sufflen == 0)
  {
    break;
  }
  if ((sufflen == 1) && (memcmp(suffix, ".", 1) == 0))
  {
  }
  else
    if ((sufflen == 2) && (memcmp(suffix, "..", 2) == 0))
  {
    depth -= 1;
    if (depth == 0)
    {
      name_idx = (&suffix[suffix_idx]) + sufflen;
      goto nextname;
    }
  }
  else
  {
    depth += 1;
  }
  suffix_idx += sufflen;
  *name_idx_ref = name_idx;
  *suffix_idx_ref = suffix_idx;
  *sufflen_ref = sufflen;
  *depth_ref = depth;
}

int helper_helper_lfs_dir_commitcrc_1_1(lfs_t * const lfs, struct lfs_commit * const commit, uint32_t crc, uint32_t crc, lfs_off_t noff, uint8_t eperturb, uint32_t crc)
{
  int err = lfs_bd_read(lfs, 0, &lfs->rcache, lfs->cfg->prog_size, commit->block, noff, &eperturb, 1);
  if (err && (err != LFS_ERR_CORRUPT))
  {
    return err;
  }
  {
    struct lfs_fcrc fcrc = {.size = lfs->cfg->prog_size, .crc = 0xffffffff};
    err = lfs_bd_crc(lfs, 0, &lfs->rcache, lfs->cfg->prog_size, commit->block, noff, fcrc.size, &fcrc.crc);
    if (err && (err != LFS_ERR_CORRUPT))
    {
      return err;
    }
    lfs_fcrc_tole32(&fcrc);
    err = lfs_dir_commitattr(lfs, commit, ((((lfs_tag_t) LFS_TYPE_FCRC) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) (sizeof(struct lfs_fcrc))), &fcrc);
    if (err)
    {
      return err;
    }
  }
}

int helper_helper_lfs_dir_compact_1_1(lfs_t * const lfs, lfs_mdir_t * const dir, const struct lfs_mattr * const attrs, int attrcount, lfs_mdir_t * const source, uint16_t begin, uint16_t end, bool relocated)
{
  struct lfs_commit commit = {.block = dir->pair[1], .off = 0, .ptag = 0xffffffff, .crc = 0xffffffff, .begin = 0, .end = ((lfs->cfg->metadata_max) ? (lfs->cfg->metadata_max) : (lfs->cfg->block_size)) - 8};
  int err = lfs_bd_erase(lfs, dir->pair[1]);
  if (err)
  {
    if (err == LFS_ERR_CORRUPT)
    {
      goto relocate;
    }
    return err;
  }
  dir->rev = lfs_tole32(dir->rev);
  err = lfs_dir_commitprog(lfs, &commit, &dir->rev, sizeof(dir->rev));
  dir->rev = lfs_fromle32(dir->rev);
  if (err)
  {
    if (err == LFS_ERR_CORRUPT)
    {
      goto relocate;
    }
    return err;
  }
  err = lfs_dir_traverse(lfs, source, 0, 0xffffffff, attrs, attrcount, ((((lfs_tag_t) 0x400) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 0), ((((lfs_tag_t) LFS_TYPE_NAME) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 0), begin, end, -begin, lfs_dir_commit_commit, &((struct lfs_dir_commit_commit){lfs, &commit}));
  if (err)
  {
    if (err == LFS_ERR_CORRUPT)
    {
      goto relocate;
    }
    return err;
  }
  if (!lfs_pair_isnull(dir->tail))
  {
    lfs_pair_tole32(dir->tail);
    err = lfs_dir_commitattr(lfs, &commit, ((((lfs_tag_t) (LFS_TYPE_TAIL + dir->split)) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 8), dir->tail);
    lfs_pair_fromle32(dir->tail);
    if (err)
    {
      if (err == LFS_ERR_CORRUPT)
      {
        goto relocate;
      }
      return err;
    }
  }
  lfs_gstate_t delta = {0};
  if (!relocated)
  {
    lfs_gstate_xor(&delta, &lfs->gdisk);
    lfs_gstate_xor(&delta, &lfs->gstate);
  }
  lfs_gstate_xor(&delta, &lfs->gdelta);
  delta.tag &= ~(((((lfs_tag_t) 0) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 0x3ff));
  err = lfs_dir_getgstate(lfs, dir, &delta);
  if (err)
  {
    return err;
  }
  if (!lfs_gstate_iszero(&delta))
  {
    lfs_gstate_tole32(&delta);
    err = lfs_dir_commitattr(lfs, &commit, ((((lfs_tag_t) LFS_TYPE_MOVESTATE) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) (sizeof(delta))), &delta);
    if (err)
    {
      if (err == LFS_ERR_CORRUPT)
      {
        goto relocate;
      }
      return err;
    }
  }
  err = lfs_dir_commitcrc(lfs, &commit);
  if (err)
  {
    if (err == LFS_ERR_CORRUPT)
    {
      goto relocate;
    }
    return err;
  }
  assert((commit.off % lfs->cfg->prog_size) == 0);
  lfs_pair_swap(dir->pair);
  dir->count = end - begin;
  dir->off = commit.off;
  dir->etag = commit.ptag;
  lfs->gdelta = (lfs_gstate_t){0};
  if (!relocated)
  {
    lfs->gdisk = lfs->gstate;
  }
}

int helper_helper_lfs_dir_orphaningcommit_2_1(lfs_mdir_t * const ldir_ref, int * const state_ref, int * const err_ref, int * const err_ref, lfs_t * const lfs, lfs_block_t lpair[2], lfs_mdir_t pdir, bool hasparent)
{
  lfs_mdir_t ldir = *ldir_ref;
  int state = *state_ref;
  int err = *err_ref;
  int err = *err_ref;
  if (lfs_gstate_hasorphans(&lfs->gstate))
  {
    err = lfs_fs_preporphans(lfs, -((int8_t) hasparent));
    if (err)
    {
      return err;
    }
  }
  uint16_t moveid = 0x3ff;
  if (lfs_gstate_hasmovehere(&lfs->gstate, pdir.pair))
  {
    moveid = lfs_tag_id(lfs->gstate.tag);
    printf("%s:%d:debug: Fixing move while relocating {0x%x, 0x%x} 0x%x\n%s\n", "/home/ubuntu/C2RustTranslation/subjects/littlefs/lfs.c", 2571, pdir.pair[0], pdir.pair[1], moveid, "");
    lfs_fs_prepmove(lfs, 0x3ff, 0);
  }
  lpair[0] = pdir.pair[0];
  lpair[1] = pdir.pair[1];
  lfs_pair_tole32(ldir.pair);
  state = lfs_dir_relocatingcommit(lfs, &pdir, lpair, (struct lfs_mattr []){{(moveid != 0x3ff) ? (((((lfs_tag_t) LFS_TYPE_DELETE) << 20) | (((lfs_tag_t) moveid) << 10)) | ((lfs_tag_t) 0)) : (((((lfs_tag_t) LFS_FROM_NOOP) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 0)), 0}, {((((lfs_tag_t) (LFS_TYPE_TAIL + pdir.split)) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 8), ldir.pair}}, (sizeof((struct lfs_mattr []){{(moveid != 0x3ff) ? (((((lfs_tag_t) LFS_TYPE_DELETE) << 20) | (((lfs_tag_t) moveid) << 10)) | ((lfs_tag_t) 0)) : (((((lfs_tag_t) LFS_FROM_NOOP) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 0)), 0}, {((((lfs_tag_t) (LFS_TYPE_TAIL + pdir.split)) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 8), ldir.pair}})) / (sizeof(struct lfs_mattr)), 0);
  lfs_pair_fromle32(ldir.pair);
  if (state < 0)
  {
    return state;
  }
  ldir = pdir;
  *ldir_ref = ldir;
  *state_ref = state;
  *err_ref = err;
  *err_ref = err;
}

int helper_helper_lfs_dir_orphaningcommit_2_2(lfs_mdir_t * const ldir_ref, int * const state_ref, bool * const orphans_ref, lfs_stag_t * const tag_ref, lfs_t * const lfs, lfs_block_t lpair[2], lfs_mdir_t pdir)
{
  lfs_mdir_t ldir = *ldir_ref;
  int state = *state_ref;
  bool orphans = *orphans_ref;
  lfs_stag_t tag = *tag_ref;
  int err = lfs_fs_preporphans(lfs, +1);
  if (err)
  {
    return err;
  }
  uint16_t moveid = 0x3ff;
  if (lfs_gstate_hasmovehere(&lfs->gstate, pdir.pair))
  {
    moveid = lfs_tag_id(lfs->gstate.tag);
    printf("%s:%d:debug: Fixing move while relocating {0x%x, 0x%x} 0x%x\n%s\n", "/home/ubuntu/C2RustTranslation/subjects/littlefs/lfs.c", 2519, pdir.pair[0], pdir.pair[1], moveid, "");
    lfs_fs_prepmove(lfs, 0x3ff, 0);
    if (moveid < lfs_tag_id(tag))
    {
      tag -= ((((lfs_tag_t) 0) << 20) | (((lfs_tag_t) 1) << 10)) | ((lfs_tag_t) 0);
    }
  }
  lfs_block_t ppair[2] = {pdir.pair[0], pdir.pair[1]};
  lfs_pair_tole32(ldir.pair);
  state = lfs_dir_relocatingcommit(lfs, &pdir, ppair, (struct lfs_mattr []){{(moveid != 0x3ff) ? (((((lfs_tag_t) LFS_TYPE_DELETE) << 20) | (((lfs_tag_t) moveid) << 10)) | ((lfs_tag_t) 0)) : (((((lfs_tag_t) LFS_FROM_NOOP) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 0)), 0}, {tag, ldir.pair}}, (sizeof((struct lfs_mattr []){{(moveid != 0x3ff) ? (((((lfs_tag_t) LFS_TYPE_DELETE) << 20) | (((lfs_tag_t) moveid) << 10)) | ((lfs_tag_t) 0)) : (((((lfs_tag_t) LFS_FROM_NOOP) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 0)), 0}, {tag, ldir.pair}})) / (sizeof(struct lfs_mattr)), 0);
  lfs_pair_fromle32(ldir.pair);
  if (state < 0)
  {
    return state;
  }
  if (state == LFS_OK_RELOCATED)
  {
    lpair[0] = ppair[0];
    lpair[1] = ppair[1];
    ldir = pdir;
    orphans = 1;
    continue;
  }
  *ldir_ref = ldir;
  *state_ref = state;
  *orphans_ref = orphans;
  *tag_ref = tag;
}

int helper_helper_lfs_ctz_extend_1_1(int * const err_ref, lfs_t * const lfs, lfs_cache_t * const pcache, lfs_cache_t * const rcache, lfs_block_t head, lfs_size_t size, lfs_block_t * const block, lfs_off_t * const off, lfs_block_t nblock)
{
  int err = *err_ref;
  err = lfs_bd_erase(lfs, nblock);
  if (err)
  {
    if (err == LFS_ERR_CORRUPT)
    {
      goto relocate;
    }
    return err;
  }
  if (size == 0)
  {
    *block = nblock;
    *off = 0;
    return 0;
  }
  lfs_size_t noff = size - 1;
  lfs_off_t index = lfs_ctz_index(lfs, &noff);
  noff = noff + 1;
  if (noff != lfs->cfg->block_size)
  {
    helper_helper_helper_lfs_ctz_extend_1_1_2(&err, lfs, pcache, rcache, head, block, off, nblock, noff);
  }
  index += 1;
  lfs_size_t skips = lfs_ctz(index) + 1;
  lfs_block_t nhead = head;
  for (lfs_off_t i = 0; i < skips; i += 1)
  {
    helper_helper_helper_lfs_ctz_extend_1_1_1(&err, &nhead, lfs, pcache, rcache, nblock, i, skips, i);
  }

  *block = nblock;
  *off = 4 * skips;
  return 0;
  *err_ref = err;
}

int helper_helper_lfs_file_relocate_1_1(int * const err_ref, lfs_t * const lfs, lfs_file_t * const file, lfs_block_t nblock, lfs_off_t i)
{
  int err = *err_ref;
  uint8_t data;
  if (file->flags & LFS_F_INLINE)
  {
    err = lfs_dir_getread(lfs, &file->m, 0, &file->cache, file->off - i, ((((lfs_tag_t) 0xfff) << 20) | (((lfs_tag_t) 0x1ff) << 10)) | ((lfs_tag_t) 0), ((((lfs_tag_t) LFS_TYPE_INLINESTRUCT) << 20) | (((lfs_tag_t) file->id) << 10)) | ((lfs_tag_t) 0), i, &data, 1);
    if (err)
    {
      return err;
    }
  }
  else
  {
    err = lfs_bd_read(lfs, &file->cache, &lfs->rcache, file->off - i, file->block, i, &data, 1);
    if (err)
    {
      return err;
    }
  }
  err = lfs_bd_prog(lfs, &lfs->pcache, &lfs->rcache, 1, nblock, i, &data, 1);
  if (err)
  {
    if (err == LFS_ERR_CORRUPT)
    {
      goto relocate;
    }
    return err;
  }
  *err_ref = err;
}

int helper_helper_lfs_file_flush_1_1(lfs_t * const lfs, lfs_file_t * const file, lfs_off_t pos)
{
  lfs_file_t orig = {.ctz.head = file->ctz.head, .ctz.size = file->ctz.size, .flags = LFS_O_RDONLY, .pos = file->pos, .cache = lfs->rcache};
  lfs_cache_drop(lfs, &lfs->rcache);
  while (file->pos < file->ctz.size)
  {
    uint8_t data;
    lfs_ssize_t res = lfs_file_flushedread(lfs, &orig, &data, 1);
    if (res < 0)
    {
      return res;
    }
    res = lfs_file_flushedwrite(lfs, file, &data, 1);
    if (res < 0)
    {
      return res;
    }
    if (lfs->rcache.block != ((lfs_block_t) (-1)))
    {
      lfs_cache_drop(lfs, &orig.cache);
      lfs_cache_drop(lfs, &lfs->rcache);
    }
  }

  while (1)
  {
    int err = lfs_bd_flush(lfs, &file->cache, &lfs->rcache, 1);
    if (err)
    {
      if (err == LFS_ERR_CORRUPT)
      {
        goto relocate;
      }
      return err;
    }
    break;
    relocate:
    printf("%s:%d:debug: Bad block at 0x%x%s\n", "/home/ubuntu/C2RustTranslation/subjects/littlefs/lfs.c", 3407, file->block, "");

    err = lfs_file_relocate(lfs, file);
    if (err)
    {
      return err;
    }
  }

}

lfs_ssize_t helper_helper_lfs_file_flushedwrite_1_1(lfs_t * const lfs, lfs_file_t * const file, const uint8_t * const data, lfs_size_t diff)
{
  int err = lfs_bd_prog(lfs, &file->cache, &lfs->rcache, 1, file->block, file->off, data, diff);
  if (err)
  {
    if (err == LFS_ERR_CORRUPT)
    {
      goto relocate;
    }
    file->flags |= LFS_F_ERRED;
    return err;
  }
  break;
  relocate:
  err = lfs_file_relocate(lfs, file);

  if (err)
  {
    file->flags |= LFS_F_ERRED;
    return err;
  }
}

lfs_ssize_t helper_helper_lfs_file_flushedwrite_1_2(lfs_t * const lfs, lfs_file_t * const file)
{
  if (!(file->flags & LFS_F_INLINE))
  {
    if ((!(file->flags & LFS_F_WRITING)) && (file->pos > 0))
    {
      int err = lfs_ctz_find(lfs, 0, &file->cache, file->ctz.head, file->ctz.size, file->pos - 1, &file->block, &((lfs_off_t){0}));
      if (err)
      {
        file->flags |= LFS_F_ERRED;
        return err;
      }
      lfs_cache_zero(lfs, &file->cache);
    }
    lfs_alloc_ckpoint(lfs);
    int err = lfs_ctz_extend(lfs, &file->cache, &lfs->rcache, file->block, file->pos, &file->block, &file->off);
    if (err)
    {
      file->flags |= LFS_F_ERRED;
      return err;
    }
  }
  else
  {
    file->block = (lfs_block_t) (-2);
    file->off = file->pos;
  }
  file->flags |= LFS_F_WRITING;
}

void helper_helper_lfs_mount__1_1(int * const err_ref, lfs_stag_t * const tag_ref, lfs_t * const lfs, lfs_mdir_t dir)
{
  int err = *err_ref;
  lfs_stag_t tag = *tag_ref;
  lfs->root[0] = dir.pair[0];
  lfs->root[1] = dir.pair[1];
  lfs_superblock_t superblock;
  tag = lfs_dir_get(lfs, &dir, ((((lfs_tag_t) 0x7ff) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 0), ((((lfs_tag_t) LFS_TYPE_INLINESTRUCT) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) (sizeof(superblock))), &superblock);
  if (tag < 0)
  {
    err = tag;
    goto cleanup;
  }
  lfs_superblock_fromle32(&superblock);
  uint16_t major_version = 0xffff & (superblock.version >> 16);
  uint16_t minor_version = 0xffff & (superblock.version >> 0);
  if ((major_version != lfs_fs_disk_version_major(lfs)) || (minor_version > lfs_fs_disk_version_minor(lfs)))
  {
    printf("%s:%d:error: Invalid version v%u.%u != v%u.%u%s\n", "/home/ubuntu/C2RustTranslation/subjects/littlefs/lfs.c", 4535, major_version, minor_version, lfs_fs_disk_version_major(lfs), lfs_fs_disk_version_minor(lfs), "");
    err = LFS_ERR_INVAL;
    goto cleanup;
  }
  bool needssuperblock = 0;
  if (minor_version < lfs_fs_disk_version_minor(lfs))
  {
    printf("%s:%d:debug: Found older minor version v%u.%u < v%u.%u%s\n", "/home/ubuntu/C2RustTranslation/subjects/littlefs/lfs.c", 4550, major_version, minor_version, lfs_fs_disk_version_major(lfs), lfs_fs_disk_version_minor(lfs), "");
    needssuperblock = 1;
  }
  lfs_fs_prepsuperblock(lfs, needssuperblock);
  if (superblock.name_max)
  {
    if (superblock.name_max > lfs->name_max)
    {
      printf("%s:%d:error: Unsupported name_max (%u > %u)%s\n", "/home/ubuntu/C2RustTranslation/subjects/littlefs/lfs.c", 4565, superblock.name_max, lfs->name_max, "");
      err = LFS_ERR_INVAL;
      goto cleanup;
    }
    lfs->name_max = superblock.name_max;
  }
  if (superblock.file_max)
  {
    if (superblock.file_max > lfs->file_max)
    {
      printf("%s:%d:error: Unsupported file_max (%u > %u)%s\n", "/home/ubuntu/C2RustTranslation/subjects/littlefs/lfs.c", 4576, superblock.file_max, lfs->file_max, "");
      err = LFS_ERR_INVAL;
      goto cleanup;
    }
    lfs->file_max = superblock.file_max;
  }
  if (superblock.attr_max)
  {
    if (superblock.attr_max > lfs->attr_max)
    {
      printf("%s:%d:error: Unsupported attr_max (%u > %u)%s\n", "/home/ubuntu/C2RustTranslation/subjects/littlefs/lfs.c", 4587, superblock.attr_max, lfs->attr_max, "");
      err = LFS_ERR_INVAL;
      goto cleanup;
    }
    lfs->attr_max = superblock.attr_max;
    lfs->inline_max = lfs_min(lfs->inline_max, lfs->attr_max);
  }
  if (lfs->cfg->block_count && (superblock.block_count != lfs->cfg->block_count))
  {
    printf("%s:%d:error: Invalid block count (%u != %u)%s\n", "/home/ubuntu/C2RustTranslation/subjects/littlefs/lfs.c", 4602, superblock.block_count, lfs->cfg->block_count, "");
    err = LFS_ERR_INVAL;
    goto cleanup;
  }
  lfs->block_count = superblock.block_count;
  if (superblock.block_size != lfs->cfg->block_size)
  {
    printf("%s:%d:error: Invalid block size (%u != %u)%s\n", "/home/ubuntu/C2RustTranslation/subjects/littlefs/lfs.c", 4611, superblock.block_size, lfs->cfg->block_size, "");
    err = LFS_ERR_INVAL;
    goto cleanup;
  }
  *err_ref = err;
  *tag_ref = tag;
}

int helper_helper_lfs_fs_traverse__1_1(int * const err_ref, int * const err_ref, int * const err_ref, int * const err_ref, int * const err_ref, int * const err_ref, int * const err_ref, lfs_t * const lfs, int (* const cb)(void *data, lfs_block_t block), void * const data, void * const data, void * const data, bool includeorphans, lfs_mdir_t dir, uint16_t id)
{
  int err = *err_ref;
  int err = *err_ref;
  int err = *err_ref;
  int err = *err_ref;
  int err = *err_ref;
  int err = *err_ref;
  int err = *err_ref;
  struct lfs_ctz ctz;
  lfs_stag_t tag = lfs_dir_get(lfs, &dir, ((((lfs_tag_t) 0x700) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 0), ((((lfs_tag_t) LFS_TYPE_STRUCT) << 20) | (((lfs_tag_t) id) << 10)) | ((lfs_tag_t) (sizeof(ctz))), &ctz);
  if (tag < 0)
  {
    if (tag == LFS_ERR_NOENT)
    {
      continue;
    }
    return tag;
  }
  lfs_ctz_fromle32(&ctz);
  if (lfs_tag_type3(tag) == LFS_TYPE_CTZSTRUCT)
  {
    err = lfs_ctz_traverse(lfs, 0, &lfs->rcache, ctz.head, ctz.size, cb, data);
    if (err)
    {
      return err;
    }
  }
  else
    if (includeorphans && (lfs_tag_type3(tag) == LFS_TYPE_DIRSTRUCT))
  {
    for (int i = 0; i < 2; i += 1)
    {
      err = cb(data, (&ctz.head)[i]);
      if (err)
      {
        return err;
      }
    }

  }
  *err_ref = err;
  *err_ref = err;
  *err_ref = err;
  *err_ref = err;
  *err_ref = err;
  *err_ref = err;
  *err_ref = err;
}

int helper_helper_lfs_fs_deorphan_1_1(lfs_mdir_t * const pdir_ref, bool * const moreorphans_ref, lfs_t * const lfs, bool powerloss, int pass, lfs_mdir_t dir)
{
  lfs_mdir_t pdir = *pdir_ref;
  bool moreorphans = *moreorphans_ref;
  int err = lfs_dir_fetch(lfs, &dir, pdir.tail);
  if (err)
  {
    return err;
  }
  if (!pdir.split)
  {
    helper_helper_helper_lfs_fs_deorphan_1_1_1(&moreorphans, &err, lfs, powerloss, pass, dir, pdir);
  }
  pdir = dir;
  *pdir_ref = pdir;
  *moreorphans_ref = moreorphans;
}

void helper_helper_helper_lfs_dir_traverse_2_2_1(lfs_tag_t * const tmask_ref, lfs_tag_t * const ttag_ref, uint16_t * const begin_ref, uint16_t * const end_ref, int16_t * const diff_ref, unsigned int * const data_idx_ref, unsigned int * const cb_idx_ref, unsigned * const sp_ref, const lfs_mdir_t * const dir, const struct lfs_mattr * const attrs, int (* const cb)(void *data, lfs_tag_t tag, const void *buffer), void * const data, lfs_tag_t tag, const void * const buffer, void * const data, const void * const buffer, void * const data, const void * const buffer, void * const data, struct lfs_dir_traverse stack[3 - 1], const void * const buffer, lfs_tag_t tag, lfs_off_t off, lfs_tag_t ptag, int attrcount, lfs_tag_t tag, lfs_tag_t tag, struct lfs_diskoff disk)
{
  lfs_tag_t tmask = *tmask_ref;
  lfs_tag_t ttag = *ttag_ref;
  uint16_t begin = *begin_ref;
  uint16_t end = *end_ref;
  int16_t diff = *diff_ref;
  unsigned int data_idx = *data_idx_ref;
  unsigned int cb_idx = *cb_idx_ref;
  unsigned sp = *sp_ref;
  assert(sp < 3);
  stack[sp] = (struct lfs_dir_traverse){.dir = dir, .off = off, .ptag = ptag, .attrs = attrs, .attrcount = attrcount, .tmask = tmask, .ttag = ttag, .begin = begin, .end = end, .diff = diff, .cb = cb, .data = data, .tag = tag, .buffer = buffer, .disk = disk};
  sp += 1;
  tmask = 0;
  ttag = 0;
  begin = 0;
  end = 0;
  diff = 0;
  cb_idx = lfs_dir_traverse_filter;
  data_idx = &stack[sp - 1].tag;
  continue;
  *tmask_ref = tmask;
  *ttag_ref = ttag;
  *begin_ref = begin;
  *end_ref = end;
  *diff_ref = diff;
  *data_idx_ref = data_idx;
  *cb_idx_ref = cb_idx;
  *sp_ref = sp;
}

lfs_stag_t helper_helper_helper_lfs_dir_fetchmatch_1_1_1(lfs_stag_t * const besttag_ref, lfs_off_t * const off_ref, lfs_tag_t * const ptag_ref, uint32_t * const crc_ref, int * const err_ref, lfs_t * const lfs, lfs_mdir_t * const dir, lfs_block_t temptail[2], uint16_t tempcount, bool tempsplit, lfs_stag_t tempbesttag, lfs_tag_t tag)
{
  lfs_stag_t besttag = *besttag_ref;
  lfs_off_t off = *off_ref;
  lfs_tag_t ptag = *ptag_ref;
  uint32_t crc = *crc_ref;
  int err = *err_ref;
  uint32_t dcrc;
  err = lfs_bd_read(lfs, 0, &lfs->rcache, lfs->cfg->block_size, dir->pair[0], off + (sizeof(tag)), &dcrc, sizeof(dcrc));
  if (err)
  {
    if (err == LFS_ERR_CORRUPT)
    {
      break;
    }
    return err;
  }
  dcrc = lfs_fromle32(dcrc);
  if (crc != dcrc)
  {
    break;
  }
  ptag ^= ((lfs_tag_t) (lfs_tag_chunk(tag) & 1U)) << 31;
  lfs->seed = lfs_crc(lfs->seed, &crc, sizeof(crc));
  besttag = tempbesttag;
  dir->off = off + lfs_tag_dsize(tag);
  dir->etag = ptag;
  dir->count = tempcount;
  dir->tail[0] = temptail[0];
  dir->tail[1] = temptail[1];
  dir->split = tempsplit;
  crc = 0xffffffff;
  continue;
  *besttag_ref = besttag;
  *off_ref = off;
  *ptag_ref = ptag;
  *crc_ref = crc;
  *err_ref = err;
}

int helper_helper_helper_lfs_ctz_extend_1_1_1(int * const err_ref, lfs_block_t * const nhead_ref, lfs_t * const lfs, lfs_cache_t * const pcache, lfs_cache_t * const rcache, lfs_block_t nblock, lfs_off_t i, lfs_size_t skips, lfs_off_t i)
{
  int err = *err_ref;
  lfs_block_t nhead = *nhead_ref;
  nhead = lfs_tole32(nhead);
  err = lfs_bd_prog(lfs, pcache, rcache, 1, nblock, 4 * i, &nhead, 4);
  nhead = lfs_fromle32(nhead);
  if (err)
  {
    if (err == LFS_ERR_CORRUPT)
    {
      goto relocate;
    }
    return err;
  }
  if (i != (skips - 1))
  {
    err = lfs_bd_read(lfs, 0, rcache, sizeof(nhead), nhead, 4 * i, &nhead, sizeof(nhead));
    nhead = lfs_fromle32(nhead);
    if (err)
    {
      return err;
    }
  }
  *err_ref = err;
  *nhead_ref = nhead;
}

int helper_helper_helper_lfs_ctz_extend_1_1_2(int * const err_ref, lfs_t * const lfs, lfs_cache_t * const pcache, lfs_cache_t * const rcache, lfs_block_t head, lfs_block_t * const block, lfs_off_t * const off, lfs_block_t nblock, lfs_size_t noff)
{
  int err = *err_ref;
  for (lfs_off_t i = 0; i < noff; i += 1)
  {
    uint8_t data;
    err = lfs_bd_read(lfs, 0, rcache, noff - i, head, i, &data, 1);
    if (err)
    {
      return err;
    }
    err = lfs_bd_prog(lfs, pcache, rcache, 1, nblock, i, &data, 1);
    if (err)
    {
      if (err == LFS_ERR_CORRUPT)
      {
        goto relocate;
      }
      return err;
    }
  }

  *block = nblock;
  *off = noff;
  return 0;
  *err_ref = err;
}

int helper_helper_helper_lfs_fs_deorphan_1_1_1(bool * const moreorphans_ref, int * const err_ref, lfs_t * const lfs, bool powerloss, int pass, lfs_mdir_t dir, lfs_mdir_t pdir)
{
  bool moreorphans = *moreorphans_ref;
  int err = *err_ref;
  lfs_mdir_t parent;
  lfs_stag_t tag = lfs_fs_parent(lfs, pdir.tail, &parent);
  if ((tag < 0) && (tag != LFS_ERR_NOENT))
  {
    return tag;
  }
  if ((pass == 0) && (tag != LFS_ERR_NOENT))
  {
    helper_helper_helper_helper_lfs_fs_deorphan_1_1_1_2(&moreorphans, lfs, pdir, parent, tag);
  }
  if (((pass == 1) && (tag == LFS_ERR_NOENT)) && powerloss)
  {
    helper_helper_helper_helper_lfs_fs_deorphan_1_1_1_1(&moreorphans, &err, lfs, dir, pdir);
  }
  *moreorphans_ref = moreorphans;
  *err_ref = err;
}

int helper_helper_helper_helper_lfs_fs_deorphan_1_1_1_1(bool * const moreorphans_ref, int * const err_ref, lfs_t * const lfs, lfs_mdir_t dir, lfs_mdir_t pdir)
{
  bool moreorphans = *moreorphans_ref;
  int err = *err_ref;
  printf("%s:%d:debug: Fixing orphan {0x%x, 0x%x}%s\n", "/home/ubuntu/C2RustTranslation/subjects/littlefs/lfs.c", 5081, pdir.tail[0], pdir.tail[1], "");
  err = lfs_dir_getgstate(lfs, &dir, &lfs->gdelta);
  if (err)
  {
    return err;
  }
  lfs_pair_tole32(dir.tail);
  int state = lfs_dir_orphaningcommit(lfs, &pdir, (struct lfs_mattr []){{((((lfs_tag_t) (LFS_TYPE_TAIL + dir.split)) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 8), dir.tail}}, (sizeof((struct lfs_mattr []){{((((lfs_tag_t) (LFS_TYPE_TAIL + dir.split)) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 8), dir.tail}})) / (sizeof(struct lfs_mattr)));
  lfs_pair_fromle32(dir.tail);
  if (state < 0)
  {
    return state;
  }
  if (state == LFS_OK_ORPHANED)
  {
    moreorphans = 1;
  }
  continue;
  *moreorphans_ref = moreorphans;
  *err_ref = err;
}

int helper_helper_helper_helper_lfs_fs_deorphan_1_1_1_2(bool * const moreorphans_ref, lfs_t * const lfs, lfs_mdir_t pdir, lfs_mdir_t parent, lfs_stag_t tag)
{
  bool moreorphans = *moreorphans_ref;
  lfs_block_t pair[2];
  lfs_stag_t state = lfs_dir_get(lfs, &parent, ((((lfs_tag_t) 0x7ff) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 0), tag, pair);
  if (state < 0)
  {
    return state;
  }
  lfs_pair_fromle32(pair);
  if (!lfs_pair_issync(pair, pdir.tail))
  {
    printf("%s:%d:debug: Fixing half-orphan {0x%x, 0x%x} -> {0x%x, 0x%x}%s\n", "/home/ubuntu/C2RustTranslation/subjects/littlefs/lfs.c", 5038, pdir.tail[0], pdir.tail[1], pair[0], pair[1], "");
    uint16_t moveid = 0x3ff;
    if (lfs_gstate_hasmovehere(&lfs->gstate, pdir.pair))
    {
      moveid = lfs_tag_id(lfs->gstate.tag);
      printf("%s:%d:debug: Fixing move while fixing orphans {0x%x, 0x%x} 0x%x\n%s\n", "/home/ubuntu/C2RustTranslation/subjects/littlefs/lfs.c", 5049, pdir.pair[0], pdir.pair[1], moveid, "");
      lfs_fs_prepmove(lfs, 0x3ff, 0);
    }
    lfs_pair_tole32(pair);
    state = lfs_dir_orphaningcommit(lfs, &pdir, (struct lfs_mattr []){{(moveid != 0x3ff) ? (((((lfs_tag_t) LFS_TYPE_DELETE) << 20) | (((lfs_tag_t) moveid) << 10)) | ((lfs_tag_t) 0)) : (((((lfs_tag_t) LFS_FROM_NOOP) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 0)), 0}, {((((lfs_tag_t) LFS_TYPE_SOFTTAIL) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 8), pair}}, (sizeof((struct lfs_mattr []){{(moveid != 0x3ff) ? (((((lfs_tag_t) LFS_TYPE_DELETE) << 20) | (((lfs_tag_t) moveid) << 10)) | ((lfs_tag_t) 0)) : (((((lfs_tag_t) LFS_FROM_NOOP) << 20) | (((lfs_tag_t) 0) << 10)) | ((lfs_tag_t) 0)), 0}, {((((lfs_tag_t) LFS_TYPE_SOFTTAIL) << 20) | (((lfs_tag_t) 0x3ff) << 10)) | ((lfs_tag_t) 8), pair}})) / (sizeof(struct lfs_mattr)));
    lfs_pair_fromle32(pair);
    if (state < 0)
    {
      return state;
    }
    if (state == LFS_OK_ORPHANED)
    {
      moreorphans = 1;
    }
    continue;
  }
  *moreorphans_ref = moreorphans;
}

