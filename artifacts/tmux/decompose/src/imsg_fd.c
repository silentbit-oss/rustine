struct imsg_fd
{
  struct 
  {
    struct imsg_fd *tqe_next;
    struct imsg_fd **tqe_prev;
  } entry;
  int fd;
}
/*** DEPENDENCIES:
struct imsg
{
  struct imsg_hdr hdr;
  int fd;
  void *data;
}
----------------------------
***/


