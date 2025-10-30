struct imsg
{
  struct imsg_hdr hdr;
  int fd;
  void *data;
}
/*** DEPENDENCIES:
struct imsg_hdr
{
  uint32_t type;
  uint16_t len;
  uint16_t flags;
  uint32_t peerid;
  uint32_t pid;
}
----------------------------
***/


static int imsg_get_fd(struct imsgbuf *ibuf)
{
  int fd;
  struct imsg_fd *ifd;
  unsigned int ifd_idx = 0;
  if ((ifd_idx = (&ibuf->fds)->tqh_first) == 0)
  {
    return -1;
  }
  fd = ifd->fd;
  do
  {
    if (ifd->entry.tqe_next != 0)
    {
      ifd->entry.tqe_next->entry.tqe_prev = ifd->entry.tqe_prev;
    }
    else
      (&ibuf->fds)->tqh_last = ifd->entry.tqe_prev;
    *ifd->entry.tqe_prev = ifd->entry.tqe_next;
    ;
    ;
  }
  while (0);
  free(ifd);
  return fd;
}


/*** DEPENDENCIES:
struct imsg
{
  struct imsg_hdr hdr;
  int fd;
  void *data;
}
----------------------------
struct imsg_fd
{
  struct 
  {
    struct imsg_fd *tqe_next;
    struct imsg_fd **tqe_prev;
  } entry;
  int fd;
}
----------------------------
struct imsgbuf
{
  struct 
  {
    struct imsg_fd *tqh_first;
    struct imsg_fd **tqh_last;
  } fds;
  struct ibuf_read r;
  struct msgbuf w;
  int fd;
  pid_t pid;
}
----------------------------
struct msgbuf
{
  struct 
  {
    struct ibuf *tqh_first;
    struct ibuf **tqh_last;
  } bufs;
  uint32_t queued;
  int fd;
}
----------------------------
***/


ssize_t imsg_get(struct imsgbuf *ibuf, struct imsg *imsg)
{
  size_t av;
  size_t left;
  size_t datalen;
  av = ibuf->r.wpos;
  if ((sizeof(struct imsg_hdr)) > av)
  {
    return 0;
  }
  memcpy(&imsg->hdr, ibuf->r.buf, sizeof(imsg->hdr));
  if ((imsg->hdr.len < (sizeof(struct imsg_hdr))) || (imsg->hdr.len > 16384))
  {
    errno = ERANGE;
    return -1;
  }
  if (imsg->hdr.len > av)
  {
    return 0;
  }
  datalen = imsg->hdr.len - (sizeof(struct imsg_hdr));
  ibuf->r.rptr = ibuf->r.buf + (sizeof(struct imsg_hdr));
  if (datalen == 0)
  {
    imsg->data = 0;
  }
  else
    if ((imsg->data = malloc(datalen)) == 0)
  {
    return -1;
  }
  if (imsg->hdr.flags & 1)
  {
    imsg->fd = imsg_get_fd(ibuf);
  }
  else
    imsg->fd = -1;
  memcpy(imsg->data, ibuf->r.rptr, datalen);
  if (imsg->hdr.len < av)
  {
    left = av - imsg->hdr.len;
    memmove(&ibuf->r.buf, ibuf->r.buf + imsg->hdr.len, left);
    ibuf->r.wpos = left;
  }
  else
    ibuf->r.wpos = 0;
  return datalen + (sizeof(struct imsg_hdr));
}


/*** DEPENDENCIES:
struct imsg
{
  struct imsg_hdr hdr;
  int fd;
  void *data;
}
----------------------------
static int imsg_get_fd(struct imsgbuf *ibuf)
{
  int fd;
  struct imsg_fd *ifd;
  unsigned int ifd_idx = 0;
  if ((ifd_idx = (&ibuf->fds)->tqh_first) == 0)
  {
    return -1;
  }
  fd = ifd->fd;
  do
  {
    if (ifd->entry.tqe_next != 0)
    {
      ifd->entry.tqe_next->entry.tqe_prev = ifd->entry.tqe_prev;
    }
    else
      (&ibuf->fds)->tqh_last = ifd->entry.tqe_prev;
    *ifd->entry.tqe_prev = ifd->entry.tqe_next;
    ;
    ;
  }
  while (0);
  free(ifd);
  return fd;
}


----------------------------
struct imsgbuf
{
  struct 
  {
    struct imsg_fd *tqh_first;
    struct imsg_fd **tqh_last;
  } fds;
  struct ibuf_read r;
  struct msgbuf w;
  int fd;
  pid_t pid;
}
----------------------------
struct msgbuf
{
  struct 
  {
    struct ibuf *tqh_first;
    struct ibuf **tqh_last;
  } bufs;
  uint32_t queued;
  int fd;
}
----------------------------
***/


void imsg_free(struct imsg *imsg)
{
  freezero(imsg->data, imsg->hdr.len - (sizeof(struct imsg_hdr)));
}


/*** DEPENDENCIES:
void freezero(void *ptr, size_t size)
{
  if (ptr != 0)
  {
    memset(ptr, 0, size);
    free(ptr);
  }
}


----------------------------
struct imsg
{
  struct imsg_hdr hdr;
  int fd;
  void *data;
}
----------------------------
***/


// hint:  ['fd_ref is a mutable refrence to int', 'ifd_idx_ref is a mutable refrence to unsigned int']
void helper_imsg_read_1(int * const fd_ref, unsigned int * const ifd_idx_ref, struct imsgbuf * const ibuf, struct cmsghdr * const cmsg, struct imsg_fd * const ifd)
{
  int fd = *fd_ref;
  unsigned int ifd_idx = *ifd_idx_ref;
  if ((cmsg->cmsg_level == SOL_SOCKET) && (cmsg->cmsg_type == SCM_RIGHTS))
  {
    int i;
    int j;
    j = ((((char *) cmsg) + cmsg->cmsg_len) - ((char *) CMSG_DATA(cmsg))) / (sizeof(int));
    for (i = 0; i < j; i += 1)
    {
      fd = ((int *) CMSG_DATA(cmsg))[i];
      if ((&ifd[ifd_idx]) != 0)
      {
        ifd->fd = fd;
        do
        {
          ifd->entry.tqe_next = 0;
          ifd->entry.tqe_prev = (&ibuf->fds)->tqh_last;
          *(&ibuf->fds)->tqh_last = &ifd[ifd_idx];
          (&ibuf->fds)->tqh_last = &ifd->entry.tqe_next;
        }
        while (0);
        ifd_idx = 0;
      }
      else
        close(fd);
    }

  }
  *fd_ref = fd;
  *ifd_idx_ref = ifd_idx;
}


/*** DEPENDENCIES:
struct imsg
{
  struct imsg_hdr hdr;
  int fd;
  void *data;
}
----------------------------
struct imsg_fd
{
  struct 
  {
    struct imsg_fd *tqe_next;
    struct imsg_fd **tqe_prev;
  } entry;
  int fd;
}
----------------------------
struct imsgbuf
{
  struct 
  {
    struct imsg_fd *tqh_first;
    struct imsg_fd **tqh_last;
  } fds;
  struct ibuf_read r;
  struct msgbuf w;
  int fd;
  pid_t pid;
}
----------------------------
struct msgbuf
{
  struct 
  {
    struct ibuf *tqh_first;
    struct ibuf **tqh_last;
  } bufs;
  uint32_t queued;
  int fd;
}
----------------------------
***/


ssize_t imsg_read(struct imsgbuf *ibuf)
{
  struct msghdr msg;
  struct cmsghdr *cmsg;
  unsigned int cmsg_idx = 0;
  union 
  {
    struct cmsghdr hdr;
    char buf[((((sizeof(struct cmsghdr)) + (sizeof(long))) - 1) & (~((sizeof(long)) - 1))) + (((((sizeof(int)) * 1) + (sizeof(long))) - 1) & (~((sizeof(long)) - 1)))];
  } cmsgbuf;
  struct iovec iov;
  ssize_t n = -1;
  int fd;
  struct imsg_fd *ifd;
  unsigned int ifd_idx = 0;
  memset(&msg, 0, sizeof(msg));
  memset(&cmsgbuf, 0, sizeof(cmsgbuf));
  iov.iov_base = ibuf->r.buf + ibuf->r.wpos;
  iov.iov_len = (sizeof(ibuf->r.buf)) - ibuf->r.wpos;
  msg.msg_iov = &iov;
  msg.msg_iovlen = 1;
  msg.msg_control = &cmsgbuf.buf;
  msg.msg_controllen = sizeof(cmsgbuf.buf);
  if ((ifd_idx = calloc(1, sizeof(struct imsg_fd))) == 0)
  {
    return -1;
  }
  again:
  if (((getdtablecount() + imsg_fd_overhead) + ((int) (((((((sizeof(struct cmsghdr)) + (sizeof(long))) - 1) & (~((sizeof(long)) - 1))) + ((((sizeof(int)) + (sizeof(long))) - 1) & (~((sizeof(long)) - 1)))) - (((((sizeof(struct cmsghdr)) + (sizeof(long))) - 1) & (~((sizeof(long)) - 1))) + (((0 + (sizeof(long))) - 1) & (~((sizeof(long)) - 1))))) / (sizeof(int))))) >= getdtablesize())
  {
    errno = EAGAIN;
    free(ifd);
    return -1;
  }

  if ((n = recvmsg(ibuf->fd, &msg, 0)) == (-1))
  {
    if (errno == EINTR)
    {
      goto again;
    }
    goto fail;
  }
  ibuf->r.wpos += n;
  for (cmsg_idx = CMSG_FIRSTHDR(&msg); (&cmsg[cmsg_idx]) != 0; cmsg_idx = CMSG_NXTHDR(&msg, cmsg_idx))
  {
    helper_imsg_read_1(&fd, &ifd_idx, ibuf, cmsg, ifd);
  }

  fail:
  free(ifd);

  return n;
}


/*** DEPENDENCIES:
int getdtablecount(void)
{
  return 0;
}


----------------------------
struct imsg_fd
{
  struct 
  {
    struct imsg_fd *tqe_next;
    struct imsg_fd **tqe_prev;
  } entry;
  int fd;
}
----------------------------
struct msgbuf
{
  struct 
  {
    struct ibuf *tqh_first;
    struct ibuf **tqh_last;
  } bufs;
  uint32_t queued;
  int fd;
}
----------------------------
int imsg_fd_overhead = 0
----------------------------
struct imsg
{
  struct imsg_hdr hdr;
  int fd;
  void *data;
}
----------------------------
struct imsgbuf
{
  struct 
  {
    struct imsg_fd *tqh_first;
    struct imsg_fd **tqh_last;
  } fds;
  struct ibuf_read r;
  struct msgbuf w;
  int fd;
  pid_t pid;
}
----------------------------
void helper_imsg_read_1(int * const fd_ref, unsigned int * const ifd_idx_ref, struct imsgbuf * const ibuf, struct cmsghdr * const cmsg, struct imsg_fd * const ifd)
{
  int fd = *fd_ref;
  unsigned int ifd_idx = *ifd_idx_ref;
  if ((cmsg->cmsg_level == SOL_SOCKET) && (cmsg->cmsg_type == SCM_RIGHTS))
  {
    int i;
    int j;
    j = ((((char *) cmsg) + cmsg->cmsg_len) - ((char *) CMSG_DATA(cmsg))) / (sizeof(int));
    for (i = 0; i < j; i += 1)
    {
      fd = ((int *) CMSG_DATA(cmsg))[i];
      if ((&ifd[ifd_idx]) != 0)
      {
        ifd->fd = fd;
        do
        {
          ifd->entry.tqe_next = 0;
          ifd->entry.tqe_prev = (&ibuf->fds)->tqh_last;
          *(&ibuf->fds)->tqh_last = &ifd[ifd_idx];
          (&ibuf->fds)->tqh_last = &ifd->entry.tqe_next;
        }
        while (0);
        ifd_idx = 0;
      }
      else
        close(fd);
    }

  }
  *fd_ref = fd;
  *ifd_idx_ref = ifd_idx;
}


----------------------------
***/


int imsg_add(struct ibuf *msg, const void *data, uint16_t datalen)
{
  if (datalen)
  {
    if (ibuf_add(msg, data, datalen) == (-1))
    {
      ibuf_free(msg);
      return -1;
    }
  }
  return datalen;
}


/*** DEPENDENCIES:
struct ibuf
{
  struct 
  {
    struct ibuf *tqe_next;
    struct ibuf **tqe_prev;
  } entry;
  u_char *buf;
  size_t size;
  size_t max;
  size_t wpos;
  size_t rpos;
  int fd;
}
----------------------------
void ibuf_free(struct ibuf *buf)
{
  if (buf == 0)
  {
    return;
  }
  freezero(buf->buf, buf->size);
  free(buf);
}


----------------------------
int ibuf_add(struct ibuf *buf, const void *data, size_t len)
{
  if ((buf->wpos + len) > buf->size)
  {
    if (ibuf_realloc(buf, len) == (-1))
    {
      return -1;
    }
  }
  memcpy(buf->buf + buf->wpos, data, len);
  buf->wpos += len;
  return 0;
}


----------------------------
***/


struct ibuf *imsg_create(struct imsgbuf *ibuf, uint32_t type, uint32_t peerid, pid_t pid, uint16_t datalen)
{
  struct ibuf *wbuf;
  unsigned int wbuf_idx = 0;
  struct imsg_hdr hdr;
  datalen += sizeof(struct imsg_hdr);
  if (datalen > 16384)
  {
    errno = ERANGE;
    return 0;
  }
  hdr.type = type;
  hdr.flags = 0;
  hdr.peerid = peerid;
  if ((hdr.pid = pid) == 0)
  {
    hdr.pid = ibuf->pid;
  }
  if ((wbuf_idx = ibuf_dynamic(datalen, 16384)) == 0)
  {
    return 0;
  }
  if (imsg_add(wbuf, &hdr, sizeof(hdr)) == (-1))
  {
    return 0;
  }
  return wbuf;
}


/*** DEPENDENCIES:
struct msgbuf
{
  struct 
  {
    struct ibuf *tqh_first;
    struct ibuf **tqh_last;
  } bufs;
  uint32_t queued;
  int fd;
}
----------------------------
struct imsg
{
  struct imsg_hdr hdr;
  int fd;
  void *data;
}
----------------------------
struct imsg_hdr
{
  uint32_t type;
  uint16_t len;
  uint16_t flags;
  uint32_t peerid;
  uint32_t pid;
}
----------------------------
int imsg_add(struct ibuf *msg, const void *data, uint16_t datalen)
{
  if (datalen)
  {
    if (ibuf_add(msg, data, datalen) == (-1))
    {
      ibuf_free(msg);
      return -1;
    }
  }
  return datalen;
}


----------------------------
struct ibuf
{
  struct 
  {
    struct ibuf *tqe_next;
    struct ibuf **tqe_prev;
  } entry;
  u_char *buf;
  size_t size;
  size_t max;
  size_t wpos;
  size_t rpos;
  int fd;
}
----------------------------
struct ibuf *ibuf_dynamic(size_t len, size_t max)
{
  struct ibuf *buf;
  unsigned int buf_idx = 0;
  if (max < len)
  {
    return 0;
  }
  if ((buf_idx = ibuf_open(len)) == 0)
  {
    return 0;
  }
  if (max > 0)
  {
    buf->max = max;
  }
  return buf;
}


----------------------------
struct imsgbuf
{
  struct 
  {
    struct imsg_fd *tqh_first;
    struct imsg_fd **tqh_last;
  } fds;
  struct ibuf_read r;
  struct msgbuf w;
  int fd;
  pid_t pid;
}
----------------------------
***/


void imsg_close(struct imsgbuf *ibuf, struct ibuf *msg)
{
  struct imsg_hdr *hdr;
  unsigned int hdr_idx = 0;
  hdr_idx = (struct imsg_hdr *) msg->buf;
  hdr->flags &= ~1;
  if (msg->fd != (-1))
  {
    hdr->flags |= 1;
  }
  hdr->len = (uint16_t) msg->wpos;
  ibuf_close(&ibuf->w, msg);
}


/*** DEPENDENCIES:
void ibuf_close(struct msgbuf *msgbuf, struct ibuf *buf)
{
  ibuf_enqueue(msgbuf, buf);
}


----------------------------
struct msgbuf
{
  struct 
  {
    struct ibuf *tqh_first;
    struct ibuf **tqh_last;
  } bufs;
  uint32_t queued;
  int fd;
}
----------------------------
struct imsg
{
  struct imsg_hdr hdr;
  int fd;
  void *data;
}
----------------------------
struct imsg_hdr
{
  uint32_t type;
  uint16_t len;
  uint16_t flags;
  uint32_t peerid;
  uint32_t pid;
}
----------------------------
struct ibuf
{
  struct 
  {
    struct ibuf *tqe_next;
    struct ibuf **tqe_prev;
  } entry;
  u_char *buf;
  size_t size;
  size_t max;
  size_t wpos;
  size_t rpos;
  int fd;
}
----------------------------
struct imsgbuf
{
  struct 
  {
    struct imsg_fd *tqh_first;
    struct imsg_fd **tqh_last;
  } fds;
  struct ibuf_read r;
  struct msgbuf w;
  int fd;
  pid_t pid;
}
----------------------------
***/


int imsg_compose(struct imsgbuf *ibuf, uint32_t type, uint32_t peerid, pid_t pid, int fd, const void *data, uint16_t datalen)
{
  struct ibuf *wbuf;
  unsigned int wbuf_idx = 0;
  if ((wbuf_idx = imsg_create(ibuf, type, peerid, pid, datalen)) == 0)
  {
    return -1;
  }
  if (imsg_add(wbuf, data, datalen) == (-1))
  {
    return -1;
  }
  wbuf->fd = fd;
  imsg_close(ibuf, wbuf);
  return 1;
}


/*** DEPENDENCIES:
struct ibuf *imsg_create(struct imsgbuf *ibuf, uint32_t type, uint32_t peerid, pid_t pid, uint16_t datalen)
{
  struct ibuf *wbuf;
  unsigned int wbuf_idx = 0;
  struct imsg_hdr hdr;
  datalen += sizeof(struct imsg_hdr);
  if (datalen > 16384)
  {
    errno = ERANGE;
    return 0;
  }
  hdr.type = type;
  hdr.flags = 0;
  hdr.peerid = peerid;
  if ((hdr.pid = pid) == 0)
  {
    hdr.pid = ibuf->pid;
  }
  if ((wbuf_idx = ibuf_dynamic(datalen, 16384)) == 0)
  {
    return 0;
  }
  if (imsg_add(wbuf, &hdr, sizeof(hdr)) == (-1))
  {
    return 0;
  }
  return wbuf;
}


----------------------------
struct msgbuf
{
  struct 
  {
    struct ibuf *tqh_first;
    struct ibuf **tqh_last;
  } bufs;
  uint32_t queued;
  int fd;
}
----------------------------
void imsg_close(struct imsgbuf *ibuf, struct ibuf *msg)
{
  struct imsg_hdr *hdr;
  unsigned int hdr_idx = 0;
  hdr_idx = (struct imsg_hdr *) msg->buf;
  hdr->flags &= ~1;
  if (msg->fd != (-1))
  {
    hdr->flags |= 1;
  }
  hdr->len = (uint16_t) msg->wpos;
  ibuf_close(&ibuf->w, msg);
}


----------------------------
struct imsg
{
  struct imsg_hdr hdr;
  int fd;
  void *data;
}
----------------------------
int imsg_add(struct ibuf *msg, const void *data, uint16_t datalen)
{
  if (datalen)
  {
    if (ibuf_add(msg, data, datalen) == (-1))
    {
      ibuf_free(msg);
      return -1;
    }
  }
  return datalen;
}


----------------------------
struct ibuf
{
  struct 
  {
    struct ibuf *tqe_next;
    struct ibuf **tqe_prev;
  } entry;
  u_char *buf;
  size_t size;
  size_t max;
  size_t wpos;
  size_t rpos;
  int fd;
}
----------------------------
struct imsgbuf
{
  struct 
  {
    struct imsg_fd *tqh_first;
    struct imsg_fd **tqh_last;
  } fds;
  struct ibuf_read r;
  struct msgbuf w;
  int fd;
  pid_t pid;
}
----------------------------
***/


void imsg_clear(struct imsgbuf *ibuf)
{
  int fd;
  msgbuf_clear(&ibuf->w);
  while ((fd = imsg_get_fd(ibuf)) != (-1))
  {
    close(fd);
  }

}


/*** DEPENDENCIES:
struct msgbuf
{
  struct 
  {
    struct ibuf *tqh_first;
    struct ibuf **tqh_last;
  } bufs;
  uint32_t queued;
  int fd;
}
----------------------------
struct imsg
{
  struct imsg_hdr hdr;
  int fd;
  void *data;
}
----------------------------
void msgbuf_clear(struct msgbuf *msgbuf)
{
  struct ibuf *buf;
  unsigned int buf_idx = 0;
  while ((buf_idx = (&msgbuf->bufs)->tqh_first) != 0)
  {
    ibuf_dequeue(msgbuf, buf);
  }

}


----------------------------
static int imsg_get_fd(struct imsgbuf *ibuf)
{
  int fd;
  struct imsg_fd *ifd;
  unsigned int ifd_idx = 0;
  if ((ifd_idx = (&ibuf->fds)->tqh_first) == 0)
  {
    return -1;
  }
  fd = ifd->fd;
  do
  {
    if (ifd->entry.tqe_next != 0)
    {
      ifd->entry.tqe_next->entry.tqe_prev = ifd->entry.tqe_prev;
    }
    else
      (&ibuf->fds)->tqh_last = ifd->entry.tqe_prev;
    *ifd->entry.tqe_prev = ifd->entry.tqe_next;
    ;
    ;
  }
  while (0);
  free(ifd);
  return fd;
}


----------------------------
struct imsgbuf
{
  struct 
  {
    struct imsg_fd *tqh_first;
    struct imsg_fd **tqh_last;
  } fds;
  struct ibuf_read r;
  struct msgbuf w;
  int fd;
  pid_t pid;
}
----------------------------
***/


void imsg_init(struct imsgbuf *ibuf, int fd)
{
  msgbuf_init(&ibuf->w);
  memset(&ibuf->r, 0, sizeof(ibuf->r));
  ibuf->fd = fd;
  ibuf->w.fd = fd;
  ibuf->pid = getpid();
  do
  {
    (&ibuf->fds)->tqh_first = 0;
    (&ibuf->fds)->tqh_last = &(&ibuf->fds)->tqh_first;
  }
  while (0);
}


/*** DEPENDENCIES:
void msgbuf_init(struct msgbuf *msgbuf)
{
  msgbuf->queued = 0;
  msgbuf->fd = -1;
  do
  {
    (&msgbuf->bufs)->tqh_first = 0;
    (&msgbuf->bufs)->tqh_last = &(&msgbuf->bufs)->tqh_first;
  }
  while (0);
}


----------------------------
struct imsg
{
  struct imsg_hdr hdr;
  int fd;
  void *data;
}
----------------------------
struct imsgbuf
{
  struct 
  {
    struct imsg_fd *tqh_first;
    struct imsg_fd **tqh_last;
  } fds;
  struct ibuf_read r;
  struct msgbuf w;
  int fd;
  pid_t pid;
}
----------------------------
struct msgbuf
{
  struct 
  {
    struct ibuf *tqh_first;
    struct ibuf **tqh_last;
  } bufs;
  uint32_t queued;
  int fd;
}
----------------------------
***/


int imsg_flush(struct imsgbuf *ibuf)
{
  while (ibuf->w.queued)
  {
    if (msgbuf_write(&ibuf->w) <= 0)
    {
      return -1;
    }
  }

  return 0;
}


/*** DEPENDENCIES:
int msgbuf_write(struct msgbuf *msgbuf)
{
  struct iovec iov[IOV_MAX];
  struct ibuf *buf;
  unsigned int buf_idx = 0;
  unsigned int i = 0;
  ssize_t n;
  struct msghdr msg;
  struct cmsghdr *cmsg;
  unsigned int cmsg_idx = 0;
  union 
  {
    struct cmsghdr hdr;
    char buf[((((sizeof(struct cmsghdr)) + (sizeof(long))) - 1) & (~((sizeof(long)) - 1))) + ((((sizeof(int)) + (sizeof(long))) - 1) & (~((sizeof(long)) - 1)))];
  } cmsgbuf;
  memset(&iov, 0, sizeof(iov));
  memset(&msg, 0, sizeof(msg));
  memset(&cmsgbuf, 0, sizeof(cmsgbuf));
  for (buf_idx = (&msgbuf->bufs)->tqh_first; (&buf[buf_idx]) != 0; buf_idx = buf_idx->entry.tqe_next)
  {
    if (i >= IOV_MAX)
    {
      break;
    }
    iov[i].iov_base = buf->buf + buf->rpos;
    iov[i].iov_len = buf->wpos - buf->rpos;
    i += 1;
    if (buf->fd != (-1))
    {
      break;
    }
  }

  msg.msg_iov = iov;
  msg.msg_iovlen = i;
  if (((&buf[buf_idx]) != 0) && (buf->fd != (-1)))
  {
    msg.msg_control = (caddr_t) (&cmsgbuf.buf);
    msg.msg_controllen = sizeof(cmsgbuf.buf);
    cmsg_idx = CMSG_FIRSTHDR(&msg);
    cmsg->cmsg_len = ((((sizeof(struct cmsghdr)) + (sizeof(long))) - 1) & (~((sizeof(long)) - 1))) + (sizeof(int));
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    *((int *) CMSG_DATA(cmsg)) = buf->fd;
  }
  again:
  if ((n = sendmsg(msgbuf->fd, &msg, 0)) == (-1))
  {
    if (errno == EINTR)
    {
      goto again;
    }
    if (errno == ENOBUFS)
    {
      errno = EAGAIN;
    }
    return -1;
  }

  if (n == 0)
  {
    errno = 0;
    return 0;
  }
  if (((&buf[buf_idx]) != 0) && (buf->fd != (-1)))
  {
    close(buf->fd);
    buf->fd = -1;
  }
  msgbuf_drain(msgbuf, n);
  return 1;
}


----------------------------
struct imsg
{
  struct imsg_hdr hdr;
  int fd;
  void *data;
}
----------------------------
struct imsgbuf
{
  struct 
  {
    struct imsg_fd *tqh_first;
    struct imsg_fd **tqh_last;
  } fds;
  struct ibuf_read r;
  struct msgbuf w;
  int fd;
  pid_t pid;
}
----------------------------
struct msgbuf
{
  struct 
  {
    struct ibuf *tqh_first;
    struct ibuf **tqh_last;
  } bufs;
  uint32_t queued;
  int fd;
}
----------------------------
***/


int imsg_composev(struct imsgbuf *ibuf, uint32_t type, uint32_t peerid, pid_t pid, int fd, const struct iovec *iov, int iovcnt)
{
  struct ibuf *wbuf;
  unsigned int wbuf_idx = 0;
  int i;
  int datalen = 0;
  for (i = 0; i < iovcnt; i += 1)
  {
    datalen += iov[i].iov_len;
  }

  if ((wbuf_idx = imsg_create(ibuf, type, peerid, pid, datalen)) == 0)
  {
    return -1;
  }
  for (i = 0; i < iovcnt; i += 1)
  {
    if (imsg_add(wbuf, iov[i].iov_base, iov[i].iov_len) == (-1))
    {
      return -1;
    }
  }

  wbuf->fd = fd;
  imsg_close(ibuf, wbuf);
  return 1;
}


/*** DEPENDENCIES:
struct ibuf *imsg_create(struct imsgbuf *ibuf, uint32_t type, uint32_t peerid, pid_t pid, uint16_t datalen)
{
  struct ibuf *wbuf;
  unsigned int wbuf_idx = 0;
  struct imsg_hdr hdr;
  datalen += sizeof(struct imsg_hdr);
  if (datalen > 16384)
  {
    errno = ERANGE;
    return 0;
  }
  hdr.type = type;
  hdr.flags = 0;
  hdr.peerid = peerid;
  if ((hdr.pid = pid) == 0)
  {
    hdr.pid = ibuf->pid;
  }
  if ((wbuf_idx = ibuf_dynamic(datalen, 16384)) == 0)
  {
    return 0;
  }
  if (imsg_add(wbuf, &hdr, sizeof(hdr)) == (-1))
  {
    return 0;
  }
  return wbuf;
}


----------------------------
struct msgbuf
{
  struct 
  {
    struct ibuf *tqh_first;
    struct ibuf **tqh_last;
  } bufs;
  uint32_t queued;
  int fd;
}
----------------------------
void imsg_close(struct imsgbuf *ibuf, struct ibuf *msg)
{
  struct imsg_hdr *hdr;
  unsigned int hdr_idx = 0;
  hdr_idx = (struct imsg_hdr *) msg->buf;
  hdr->flags &= ~1;
  if (msg->fd != (-1))
  {
    hdr->flags |= 1;
  }
  hdr->len = (uint16_t) msg->wpos;
  ibuf_close(&ibuf->w, msg);
}


----------------------------
struct imsg
{
  struct imsg_hdr hdr;
  int fd;
  void *data;
}
----------------------------
int imsg_add(struct ibuf *msg, const void *data, uint16_t datalen)
{
  if (datalen)
  {
    if (ibuf_add(msg, data, datalen) == (-1))
    {
      ibuf_free(msg);
      return -1;
    }
  }
  return datalen;
}


----------------------------
struct ibuf
{
  struct 
  {
    struct ibuf *tqe_next;
    struct ibuf **tqe_prev;
  } entry;
  u_char *buf;
  size_t size;
  size_t max;
  size_t wpos;
  size_t rpos;
  int fd;
}
----------------------------
struct imsgbuf
{
  struct 
  {
    struct imsg_fd *tqh_first;
    struct imsg_fd **tqh_last;
  } fds;
  struct ibuf_read r;
  struct msgbuf w;
  int fd;
  pid_t pid;
}
----------------------------
***/


