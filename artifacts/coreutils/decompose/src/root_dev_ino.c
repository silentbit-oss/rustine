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


/*** DEPENDENCIES:
struct dev_ino
{
  ino_t st_ino;
  dev_t st_dev;
}
----------------------------
***/


