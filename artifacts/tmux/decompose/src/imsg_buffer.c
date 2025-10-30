void ibuf_free(struct ibuf *buf)
{
  if (buf == 0)
  {
    return;
  }
  freezero(buf->buf, buf->size);
  free(buf);
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
***/


static void ibuf_dequeue(struct msgbuf *msgbuf, struct ibuf *buf)
{
  do
  {
    if (buf->entry.tqe_next != 0)
    {
      buf->entry.tqe_next->entry.tqe_prev = buf->entry.tqe_prev;
    }
    else
      (&msgbuf->bufs)->tqh_last = buf->entry.tqe_prev;
    *buf->entry.tqe_prev = buf->entry.tqe_next;
    ;
    ;
  }
  while (0);
  if (buf->fd != (-1))
  {
    close(buf->fd);
  }
  msgbuf->queued -= 1;
  ibuf_free(buf);
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
***/


void msgbuf_drain(struct msgbuf *msgbuf, size_t n)
{
  struct ibuf *buf;
  unsigned int buf_idx = 0;
  struct ibuf *next;
  unsigned int next_idx = 0;
  for (buf_idx = (&msgbuf->bufs)->tqh_first; ((&buf[buf_idx]) != 0) && (n > 0); buf_idx = &next[next_idx])
  {
    next_idx = buf->entry.tqe_next;
    if ((buf->rpos + n) >= buf->wpos)
    {
      n -= buf->wpos - buf->rpos;
      ibuf_dequeue(msgbuf, buf);
    }
    else
    {
      buf->rpos += n;
      n = 0;
    }
  }

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
static void ibuf_dequeue(struct msgbuf *msgbuf, struct ibuf *buf)
{
  do
  {
    if (buf->entry.tqe_next != 0)
    {
      buf->entry.tqe_next->entry.tqe_prev = buf->entry.tqe_prev;
    }
    else
      (&msgbuf->bufs)->tqh_last = buf->entry.tqe_prev;
    *buf->entry.tqe_prev = buf->entry.tqe_next;
    ;
    ;
  }
  while (0);
  if (buf->fd != (-1))
  {
    close(buf->fd);
  }
  msgbuf->queued -= 1;
  ibuf_free(buf);
}


----------------------------
***/


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


/*** DEPENDENCIES:
void msgbuf_drain(struct msgbuf *msgbuf, size_t n)
{
  struct ibuf *buf;
  unsigned int buf_idx = 0;
  struct ibuf *next;
  unsigned int next_idx = 0;
  for (buf_idx = (&msgbuf->bufs)->tqh_first; ((&buf[buf_idx]) != 0) && (n > 0); buf_idx = &next[next_idx])
  {
    next_idx = buf->entry.tqe_next;
    if ((buf->rpos + n) >= buf->wpos)
    {
      n -= buf->wpos - buf->rpos;
      ibuf_dequeue(msgbuf, buf);
    }
    else
    {
      buf->rpos += n;
      n = 0;
    }
  }

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
***/


static int ibuf_realloc(struct ibuf *buf, size_t len)
{
  u_char *b;
  unsigned int b_idx = 0;
  if ((buf->wpos + len) > buf->max)
  {
    errno = ERANGE;
    return -1;
  }
  b_idx = recallocarray(buf->buf, buf->size, buf->wpos + len, 1);
  if ((&b[b_idx]) == 0)
  {
    return -1;
  }
  buf->buf = &b[b_idx];
  buf->size = buf->wpos + len;
  return 0;
}


/*** DEPENDENCIES:
void *recallocarray(void *ptr, size_t oldnmemb, size_t newnmemb, size_t size)
{
  size_t oldsize;
  size_t newsize;
  void *newptr;
  unsigned int newptr_idx = 0;
  if (ptr == 0)
  {
    return calloc(newnmemb, size);
  }
  if ((((newnmemb >= (((size_t) 1) << ((sizeof(size_t)) * 4))) || (size >= (((size_t) 1) << ((sizeof(size_t)) * 4)))) && (newnmemb > 0)) && ((SIZE_MAX / newnmemb) < size))
  {
    errno = ENOMEM;
    return 0;
  }
  newsize = newnmemb * size;
  if ((((oldnmemb >= (((size_t) 1) << ((sizeof(size_t)) * 4))) || (size >= (((size_t) 1) << ((sizeof(size_t)) * 4)))) && (oldnmemb > 0)) && ((SIZE_MAX / oldnmemb) < size))
  {
    errno = EINVAL;
    return 0;
  }
  oldsize = oldnmemb * size;
  if (newsize <= oldsize)
  {
    size_t d = oldsize - newsize;
    if ((d < (oldsize / 2)) && (d < ((size_t) getpagesize())))
    {
      memset(((char *) ptr) + newsize, 0, d);
      return ptr;
    }
  }
  newptr_idx = malloc(newsize);
  if ((&newptr[newptr_idx]) == 0)
  {
    return 0;
  }
  if (newsize > oldsize)
  {
    memcpy(newptr, ptr, oldsize);
    memset(((char *) newptr) + oldsize, 0, newsize - oldsize);
  }
  else
    memcpy(newptr, ptr, newsize);
  explicit_bzero(ptr, oldsize);
  free(ptr);
  return newptr;
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
***/


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


/*** DEPENDENCIES:
static int ibuf_realloc(struct ibuf *buf, size_t len)
{
  u_char *b;
  unsigned int b_idx = 0;
  if ((buf->wpos + len) > buf->max)
  {
    errno = ERANGE;
    return -1;
  }
  b_idx = recallocarray(buf->buf, buf->size, buf->wpos + len, 1);
  if ((&b[b_idx]) == 0)
  {
    return -1;
  }
  buf->buf = &b[b_idx];
  buf->size = buf->wpos + len;
  return 0;
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
***/


struct ibuf *ibuf_open(size_t len)
{
  struct ibuf *buf;
  unsigned int buf_idx = 0;
  if ((buf_idx = calloc(1, sizeof(struct ibuf))) == 0)
  {
    return 0;
  }
  if ((buf->buf = malloc(len)) == 0)
  {
    free(buf);
    return 0;
  }
  buf->size = (buf->max = len);
  buf->fd = -1;
  return buf;
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
***/


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


/*** DEPENDENCIES:
struct ibuf *ibuf_open(size_t len)
{
  struct ibuf *buf;
  unsigned int buf_idx = 0;
  if ((buf_idx = calloc(1, sizeof(struct ibuf))) == 0)
  {
    return 0;
  }
  if ((buf->buf = malloc(len)) == 0)
  {
    free(buf);
    return 0;
  }
  buf->size = (buf->max = len);
  buf->fd = -1;
  return buf;
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
***/


static void ibuf_enqueue(struct msgbuf *msgbuf, struct ibuf *buf)
{
  do
  {
    buf->entry.tqe_next = 0;
    buf->entry.tqe_prev = (&msgbuf->bufs)->tqh_last;
    *(&msgbuf->bufs)->tqh_last = buf;
    (&msgbuf->bufs)->tqh_last = &buf->entry.tqe_next;
  }
  while (0);
  msgbuf->queued += 1;
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
***/


void ibuf_close(struct msgbuf *msgbuf, struct ibuf *buf)
{
  ibuf_enqueue(msgbuf, buf);
}


/*** DEPENDENCIES:
static void ibuf_enqueue(struct msgbuf *msgbuf, struct ibuf *buf)
{
  do
  {
    buf->entry.tqe_next = 0;
    buf->entry.tqe_prev = (&msgbuf->bufs)->tqh_last;
    *(&msgbuf->bufs)->tqh_last = buf;
    (&msgbuf->bufs)->tqh_last = &buf->entry.tqe_next;
  }
  while (0);
  msgbuf->queued += 1;
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
***/


void *ibuf_seek(struct ibuf *buf, size_t pos, size_t len)
{
  if ((pos + len) > buf->wpos)
  {
    return 0;
  }
  return buf->buf + pos;
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
***/


size_t ibuf_size(struct ibuf *buf)
{
  return buf->wpos;
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
***/


size_t ibuf_left(struct ibuf *buf)
{
  return buf->max - buf->wpos;
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
***/


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
***/


void *ibuf_reserve(struct ibuf *buf, size_t len)
{
  void *b;
  unsigned int b_idx = 0;
  if ((buf->wpos + len) > buf->size)
  {
    if (ibuf_realloc(buf, len) == (-1))
    {
      return 0;
    }
  }
  b_idx = buf->buf + buf->wpos;
  buf->wpos += len;
  return b;
}


/*** DEPENDENCIES:
static int ibuf_realloc(struct ibuf *buf, size_t len)
{
  u_char *b;
  unsigned int b_idx = 0;
  if ((buf->wpos + len) > buf->max)
  {
    errno = ERANGE;
    return -1;
  }
  b_idx = recallocarray(buf->buf, buf->size, buf->wpos + len, 1);
  if ((&b[b_idx]) == 0)
  {
    return -1;
  }
  buf->buf = &b[b_idx];
  buf->size = buf->wpos + len;
  return 0;
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
***/


void msgbuf_clear(struct msgbuf *msgbuf)
{
  struct ibuf *buf;
  unsigned int buf_idx = 0;
  while ((buf_idx = (&msgbuf->bufs)->tqh_first) != 0)
  {
    ibuf_dequeue(msgbuf, buf);
  }

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
static void ibuf_dequeue(struct msgbuf *msgbuf, struct ibuf *buf)
{
  do
  {
    if (buf->entry.tqe_next != 0)
    {
      buf->entry.tqe_next->entry.tqe_prev = buf->entry.tqe_prev;
    }
    else
      (&msgbuf->bufs)->tqh_last = buf->entry.tqe_prev;
    *buf->entry.tqe_prev = buf->entry.tqe_next;
    ;
    ;
  }
  while (0);
  if (buf->fd != (-1))
  {
    close(buf->fd);
  }
  msgbuf->queued -= 1;
  ibuf_free(buf);
}


----------------------------
***/


int ibuf_write(struct msgbuf *msgbuf)
{
  struct iovec iov[IOV_MAX];
  struct ibuf *buf;
  unsigned int buf_idx = 0;
  unsigned int i = 0;
  ssize_t n;
  memset(&iov, 0, sizeof(iov));
  for (buf_idx = (&msgbuf->bufs)->tqh_first; (&buf[buf_idx]) != 0; buf_idx = buf_idx->entry.tqe_next)
  {
    if (i >= IOV_MAX)
    {
      break;
    }
    iov[i].iov_base = buf->buf + buf->rpos;
    iov[i].iov_len = buf->wpos - buf->rpos;
    i += 1;
  }

  again:
  if ((n = writev(msgbuf->fd, iov, i)) == (-1))
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
  msgbuf_drain(msgbuf, n);
  return 1;
}


/*** DEPENDENCIES:
void msgbuf_drain(struct msgbuf *msgbuf, size_t n)
{
  struct ibuf *buf;
  unsigned int buf_idx = 0;
  struct ibuf *next;
  unsigned int next_idx = 0;
  for (buf_idx = (&msgbuf->bufs)->tqh_first; ((&buf[buf_idx]) != 0) && (n > 0); buf_idx = &next[next_idx])
  {
    next_idx = buf->entry.tqe_next;
    if ((buf->rpos + n) >= buf->wpos)
    {
      n -= buf->wpos - buf->rpos;
      ibuf_dequeue(msgbuf, buf);
    }
    else
    {
      buf->rpos += n;
      n = 0;
    }
  }

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
***/


