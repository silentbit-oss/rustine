#include <assert.h>
#include <config.h>
#include <same-inode.c>
#include <same-inode.h>
#include <stat.h>
#include <stdbool.h>

inline extern bool psame_inode(const struct stat *a, const struct stat *b)
{
  return !((a->st_dev ^ b->st_dev) | (a->st_ino ^ b->st_ino));
}


inline extern bool psame_inode(const struct stat *a, const struct stat *b)
{
  return !((a->st_dev ^ b->st_dev) | (a->st_ino ^ b->st_ino));
}

