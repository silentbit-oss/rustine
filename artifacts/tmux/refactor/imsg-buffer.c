#include <bitstring.h>
#include <compat.h>
#include <errno.h>
#include <imsg-buffer.c>
#include <imsg.h>
#include <inttypes.h>
#include <ioctl.h>
#include <limits.h>
#include <queue.h>
#include <socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <tree.h>
#include <types.h>
#include <uio.h>
#include <unistd.h>
#include <vis.h>
#include <wchar.h>

void err(int, const char *, ...);
void errx(int, const char *, ...);
void warn(const char *, ...);
void warnx(const char *, ...);
typedef unsigned char bitstr_t;
char *vis(char *, int, int, int);
int strvis(char *, const char *, int);
int stravis(char **, const char *, int);
int strnvis(char *, const char *, size_t, int);
int strvisx(char *, const char *, size_t, int);
int strunvis(char *, const char *);
int unvis(char *, char, int *, int);
ssize_t strnunvis(char *, const char *, size_t);
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
};
struct msgbuf
{
  struct 
  {
    struct ibuf *tqh_first;
    struct ibuf **tqh_last;
  } bufs;
  uint32_t queued;
  int fd;
};
struct ibuf_read
{
  u_char buf[65535];
  u_char *rptr;
  size_t wpos;
};
struct imsg_fd
{
  struct 
  {
    struct imsg_fd *tqe_next;
    struct imsg_fd **tqe_prev;
  } entry;
  int fd;
};
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
};
struct imsg_hdr
{
  uint32_t type;
  uint16_t len;
  uint16_t flags;
  uint32_t peerid;
  uint32_t pid;
};
struct imsg
{
  struct imsg_hdr hdr;
  int fd;
  void *data;
};
struct ibuf *ibuf_open(size_t);
struct ibuf *ibuf_dynamic(size_t, size_t);
int ibuf_add(struct ibuf *, const void *, size_t);
void *ibuf_reserve(struct ibuf *, size_t);
void *ibuf_seek(struct ibuf *, size_t, size_t);
size_t ibuf_size(struct ibuf *);
size_t ibuf_left(struct ibuf *);
void ibuf_close(struct msgbuf *, struct ibuf *);
int ibuf_write(struct msgbuf *);
void ibuf_free(struct ibuf *);
void msgbuf_init(struct msgbuf *);
void msgbuf_clear(struct msgbuf *);
int msgbuf_write(struct msgbuf *);
void msgbuf_drain(struct msgbuf *, size_t);
void imsg_init(struct imsgbuf *, int);
ssize_t imsg_read(struct imsgbuf *);
ssize_t imsg_get(struct imsgbuf *, struct imsg *);
int imsg_compose(struct imsgbuf *, uint32_t, uint32_t, pid_t, int, const void *, uint16_t);
int imsg_composev(struct imsgbuf *, uint32_t, uint32_t, pid_t, int, const struct iovec *, int);
struct ibuf *imsg_create(struct imsgbuf *, uint32_t, uint32_t, pid_t, uint16_t);
int imsg_add(struct ibuf *, const void *, uint16_t);
void imsg_close(struct imsgbuf *, struct ibuf *);
void imsg_free(struct imsg *);
int imsg_flush(struct imsgbuf *);
void imsg_clear(struct imsgbuf *);
void explicit_bzero(void *, size_t);
int getdtablecount(void);
void closefrom(int);
char *strcasestr(const char *, const char *);
char *strsep(char **, const char *);
long long strtonum(const char *, long long, long long, const char **);
size_t strlcpy(char *, const char *, size_t);
size_t strlcat(char *, const char *, size_t);
size_t strnlen(const char *, size_t);
char *strndup(const char *, size_t);
void *memmem(const void *, size_t, const void *, size_t);
int daemon(int, int);
const char *getprogname(void);
void setproctitle(const char *, ...);
int b64_ntop(const char *, size_t, char *, size_t);
int b64_pton(const char *, u_char *, size_t);
int getptmfd(void);
pid_t fdforkpty(int, int *, char *, struct termios *, struct winsize *);
pid_t forkpty(int *, char *, struct termios *, struct winsize *);
int asprintf(char **, const char *, ...);
int vasprintf(char **, const char *, va_list);
char *fgetln(FILE *, size_t *);
char *fparseln(FILE *, size_t *, size_t *, const char *, int);
int setenv(const char *, const char *, int);
int unsetenv(const char *);
void cfmakeraw(struct termios *);
void freezero(void *, size_t);
void *reallocarray(void *, size_t, size_t);
void *recallocarray(void *, size_t, size_t, size_t);
extern int BSDopterr;
extern int BSDoptind;
extern int BSDoptopt;
extern int BSDoptreset;
extern char *BSDoptarg;
int BSDgetopt(int, char * const *, const char *);
static int ibuf_realloc(struct ibuf *, size_t);
static void ibuf_enqueue(struct msgbuf *, struct ibuf *);
static void ibuf_dequeue(struct msgbuf *, struct ibuf *);
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

void *ibuf_seek(struct ibuf *buf, size_t pos, size_t len)
{
  if ((pos + len) > buf->wpos)
  {
    return 0;
  }
  return buf->buf + pos;
}

size_t ibuf_size(struct ibuf *buf)
{
  return buf->wpos;
}

size_t ibuf_left(struct ibuf *buf)
{
  return buf->max - buf->wpos;
}

void ibuf_close(struct msgbuf *msgbuf, struct ibuf *buf)
{
  ibuf_enqueue(msgbuf, buf);
}

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

void ibuf_free(struct ibuf *buf)
{
  if (buf == 0)
  {
    return;
  }
  freezero(buf->buf, buf->size);
  free(buf);
}

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

void msgbuf_clear(struct msgbuf *msgbuf)
{
  struct ibuf *buf;
  unsigned int buf_idx = 0;
  while ((buf_idx = (&msgbuf->bufs)->tqh_first) != 0)
  {
    ibuf_dequeue(msgbuf, buf);
  }

}

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


void err(int, const char *, ...);
void errx(int, const char *, ...);
void warn(const char *, ...);
void warnx(const char *, ...);
typedef unsigned char bitstr_t;
char *vis(char *, int, int, int);
int strvis(char *, const char *, int);
int stravis(char **, const char *, int);
int strnvis(char *, const char *, size_t, int);
int strvisx(char *, const char *, size_t, int);
int strunvis(char *, const char *);
int unvis(char *, char, int *, int);
ssize_t strnunvis(char *, const char *, size_t);
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
};
struct msgbuf
{
  struct 
  {
    struct ibuf *tqh_first;
    struct ibuf **tqh_last;
  } bufs;
  uint32_t queued;
  int fd;
};
struct ibuf_read
{
  u_char buf[65535];
  u_char *rptr;
  size_t wpos;
};
struct imsg_fd
{
  struct 
  {
    struct imsg_fd *tqe_next;
    struct imsg_fd **tqe_prev;
  } entry;
  int fd;
};
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
};
struct imsg_hdr
{
  uint32_t type;
  uint16_t len;
  uint16_t flags;
  uint32_t peerid;
  uint32_t pid;
};
struct imsg
{
  struct imsg_hdr hdr;
  int fd;
  void *data;
};
struct ibuf *ibuf_open(size_t);
struct ibuf *ibuf_dynamic(size_t, size_t);
int ibuf_add(struct ibuf *, const void *, size_t);
void *ibuf_reserve(struct ibuf *, size_t);
void *ibuf_seek(struct ibuf *, size_t, size_t);
size_t ibuf_size(struct ibuf *);
size_t ibuf_left(struct ibuf *);
void ibuf_close(struct msgbuf *, struct ibuf *);
int ibuf_write(struct msgbuf *);
void ibuf_free(struct ibuf *);
void msgbuf_init(struct msgbuf *);
void msgbuf_clear(struct msgbuf *);
int msgbuf_write(struct msgbuf *);
void msgbuf_drain(struct msgbuf *, size_t);
void imsg_init(struct imsgbuf *, int);
ssize_t imsg_read(struct imsgbuf *);
ssize_t imsg_get(struct imsgbuf *, struct imsg *);
int imsg_compose(struct imsgbuf *, uint32_t, uint32_t, pid_t, int, const void *, uint16_t);
int imsg_composev(struct imsgbuf *, uint32_t, uint32_t, pid_t, int, const struct iovec *, int);
struct ibuf *imsg_create(struct imsgbuf *, uint32_t, uint32_t, pid_t, uint16_t);
int imsg_add(struct ibuf *, const void *, uint16_t);
void imsg_close(struct imsgbuf *, struct ibuf *);
void imsg_free(struct imsg *);
int imsg_flush(struct imsgbuf *);
void imsg_clear(struct imsgbuf *);
void explicit_bzero(void *, size_t);
int getdtablecount(void);
void closefrom(int);
char *strcasestr(const char *, const char *);
char *strsep(char **, const char *);
long long strtonum(const char *, long long, long long, const char **);
size_t strlcpy(char *, const char *, size_t);
size_t strlcat(char *, const char *, size_t);
size_t strnlen(const char *, size_t);
char *strndup(const char *, size_t);
void *memmem(const void *, size_t, const void *, size_t);
int daemon(int, int);
const char *getprogname(void);
void setproctitle(const char *, ...);
int b64_ntop(const char *, size_t, char *, size_t);
int b64_pton(const char *, u_char *, size_t);
int getptmfd(void);
pid_t fdforkpty(int, int *, char *, struct termios *, struct winsize *);
pid_t forkpty(int *, char *, struct termios *, struct winsize *);
int asprintf(char **, const char *, ...);
int vasprintf(char **, const char *, va_list);
char *fgetln(FILE *, size_t *);
char *fparseln(FILE *, size_t *, size_t *, const char *, int);
int setenv(const char *, const char *, int);
int unsetenv(const char *);
void cfmakeraw(struct termios *);
void freezero(void *, size_t);
void *reallocarray(void *, size_t, size_t);
void *recallocarray(void *, size_t, size_t, size_t);
extern int BSDopterr;
extern int BSDoptind;
extern int BSDoptopt;
extern int BSDoptreset;
extern char *BSDoptarg;
int BSDgetopt(int, char * const *, const char *);
static int ibuf_realloc(struct ibuf *, size_t);
static void ibuf_enqueue(struct msgbuf *, struct ibuf *);
static void ibuf_dequeue(struct msgbuf *, struct ibuf *);
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

void *ibuf_seek(struct ibuf *buf, size_t pos, size_t len)
{
  if ((pos + len) > buf->wpos)
  {
    return 0;
  }
  return buf->buf + pos;
}

size_t ibuf_size(struct ibuf *buf)
{
  return buf->wpos;
}

size_t ibuf_left(struct ibuf *buf)
{
  return buf->max - buf->wpos;
}

void ibuf_close(struct msgbuf *msgbuf, struct ibuf *buf)
{
  ibuf_enqueue(msgbuf, buf);
}

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

void ibuf_free(struct ibuf *buf)
{
  if (buf == 0)
  {
    return;
  }
  freezero(buf->buf, buf->size);
  free(buf);
}

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

void msgbuf_clear(struct msgbuf *msgbuf)
{
  struct ibuf *buf;
  unsigned int buf_idx = 0;
  while ((buf_idx = (&msgbuf->bufs)->tqh_first) != 0)
  {
    ibuf_dequeue(msgbuf, buf);
  }

}

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

