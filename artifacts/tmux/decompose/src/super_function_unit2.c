// element in merge of:  peer_check_version,proc_event_cb,proc_update_event,proc_send
static int peer_check_version(struct tmuxpeer *peer, struct imsg *imsg)
{
  int version;
  version = imsg->hdr.peerid & 0xff;
  if ((imsg->hdr.type != MSG_VERSION) && (version != 8))
  {
    log_debug("peer %p bad version %d", peer, version);
    proc_send(peer, MSG_VERSION, -1, 0, 0);
    peer->flags |= 0x1;
    return -1;
  }
  return 0;
}


/*** DEPENDENCIES:
struct tmuxpeer
{
  struct tmuxproc *parent;
  struct imsgbuf ibuf;
  struct event event;
  int flags;
  void (*dispatchcb)(struct imsg *, void *);
  void *arg;
}
----------------------------
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
struct imsg
{
  struct imsg_hdr hdr;
  int fd;
  void *data;
}
----------------------------
None
----------------------------
***/


// element in merge of:  peer_check_version,proc_event_cb,proc_update_event,proc_send
static void proc_event_cb(int fd, short events, void *arg)
{
  struct tmuxpeer *peer = arg;
  ssize_t n;
  struct imsg imsg;
  if ((!(peer->flags & 0x1)) && (events & EV_READ))
  {
    if ((((n = imsg_read(&peer->ibuf)) == (-1)) && (errno != EAGAIN)) || (n == 0))
    {
      peer->dispatchcb(0, peer->arg);
      return;
    }
    for (;;)
    {
      if ((n = imsg_get(&peer->ibuf, &imsg)) == (-1))
      {
        peer->dispatchcb(0, peer->arg);
        return;
      }
      if (n == 0)
      {
        break;
      }
      log_debug("peer %p message %d", peer, imsg.hdr.type);
      if (peer_check_version(peer, &imsg) != 0)
      {
        if (imsg.fd != (-1))
        {
          close(imsg.fd);
        }
        imsg_free(&imsg);
        break;
      }
      peer->dispatchcb(&imsg, peer->arg);
      imsg_free(&imsg);
    }

  }
  if (events & EV_WRITE)
  {
    if ((msgbuf_write(&peer->ibuf.w) <= 0) && (errno != EAGAIN))
    {
      peer->dispatchcb(0, peer->arg);
      return;
    }
  }
  if ((peer->flags & 0x1) && (peer->ibuf.w.queued == 0))
  {
    peer->dispatchcb(0, peer->arg);
    return;
  }
  proc_update_event(peer);
}


/*** DEPENDENCIES:
struct tmuxpeer
{
  struct tmuxproc *parent;
  struct imsgbuf ibuf;
  struct event event;
  int flags;
  void (*dispatchcb)(struct imsg *, void *);
  void *arg;
}
----------------------------
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


----------------------------
struct imsg
{
  struct imsg_hdr hdr;
  int fd;
  void *data;
}
----------------------------
void imsg_free(struct imsg *imsg)
{
  freezero(imsg->data, imsg->hdr.len - (sizeof(struct imsg_hdr)));
}


----------------------------
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


----------------------------
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
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
None
----------------------------
***/


// element in merge of:  peer_check_version,proc_event_cb,proc_update_event,proc_send
static void proc_update_event(struct tmuxpeer *peer)
{
  short events;
  event_del(&peer->event);
  events = EV_READ;
  if (peer->ibuf.w.queued > 0)
  {
    events |= EV_WRITE;
  }
  event_set(&peer->event, peer->ibuf.fd, events, proc_event_cb, peer);
  event_add(&peer->event, 0);
}


/*** DEPENDENCIES:
struct tmuxpeer
{
  struct tmuxproc *parent;
  struct imsgbuf ibuf;
  struct event event;
  int flags;
  void (*dispatchcb)(struct imsg *, void *);
  void *arg;
}
----------------------------
None
----------------------------
***/


// element in merge of:  peer_check_version,proc_event_cb,proc_update_event,proc_send
int proc_send(struct tmuxpeer *peer, enum msgtype type, int fd, const void *buf, size_t len)
{
  struct imsgbuf *ibuf = &peer->ibuf;
  void *vp = (void *) buf;
  int retval;
  if (peer->flags & 0x1)
  {
    return -1;
  }
  log_debug("sending message %d to peer %p (%zu bytes)", type, peer, len);
  retval = imsg_compose(ibuf, type, 8, -1, fd, vp, len);
  if (retval != 1)
  {
    return -1;
  }
  proc_update_event(peer);
  return 0;
}


/*** DEPENDENCIES:
struct tmuxpeer
{
  struct tmuxproc *parent;
  struct imsgbuf ibuf;
  struct event event;
  int flags;
  void (*dispatchcb)(struct imsg *, void *);
  void *arg;
}
----------------------------
enum msgtype
{
  MSG_VERSION = 12,
  MSG_IDENTIFY_FLAGS = 100,
  MSG_IDENTIFY_TERM,
  MSG_IDENTIFY_TTYNAME,
  MSG_IDENTIFY_OLDCWD,
  MSG_IDENTIFY_STDIN,
  MSG_IDENTIFY_ENVIRON,
  MSG_IDENTIFY_DONE,
  MSG_IDENTIFY_CLIENTPID,
  MSG_IDENTIFY_CWD,
  MSG_COMMAND = 200,
  MSG_DETACH,
  MSG_DETACHKILL,
  MSG_EXIT,
  MSG_EXITED,
  MSG_EXITING,
  MSG_LOCK,
  MSG_READY,
  MSG_RESIZE,
  MSG_SHELL,
  MSG_SHUTDOWN,
  MSG_STDERR,
  MSG_STDIN,
  MSG_STDOUT,
  MSG_SUSPEND,
  MSG_UNLOCK,
  MSG_WAKEUP,
  MSG_EXEC
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


----------------------------
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
None
----------------------------
***/


