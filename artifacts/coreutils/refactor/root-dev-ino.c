#include <assert.h>
#include <config.h>
#include <dev-ino.h>
#include <root-dev-ino.c>
#include <root-dev-ino.h>
#include <same-inode.h>
#include <stat.h>
#include <stdbool.h>
#include <stdlib.h>
#include <types.h>

struct dev_ino
{
  ino_t st_ino;
  dev_t st_dev;
};
inline bool psame_inode(const struct stat *a, const struct stat *b)
{
  return !((a->st_dev ^ b->st_dev) | (a->st_ino ^ b->st_ino));
}

struct dev_ino *get_root_dev_ino(struct dev_ino *root_d_i);
struct dev_ino *get_root_dev_ino(struct dev_ino *root_d_i)
{
  struct stat statbuf;
  if (lstat("/", &statbuf))
  {
    return (void *) 0;
  }
  root_d_i->st_ino = statbuf.st_ino;
  root_d_i->st_dev = statbuf.st_dev;
  return root_d_i;
}


struct dev_ino
{
  ino_t st_ino;
  dev_t st_dev;
};
inline bool psame_inode(const struct stat *a, const struct stat *b)
{
  return !((a->st_dev ^ b->st_dev) | (a->st_ino ^ b->st_ino));
}

struct dev_ino *get_root_dev_ino(struct dev_ino *root_d_i);
struct dev_ino *get_root_dev_ino(struct dev_ino *root_d_i)
{
  struct stat statbuf;
  if (lstat("/", &statbuf))
  {
    return (void *) 0;
  }
  root_d_i->st_ino = statbuf.st_ino;
  root_d_i->st_dev = statbuf.st_dev;
  return root_d_i;
}

