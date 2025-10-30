#include <bitstring.h>
#include <compat.h>
#include <errno.h>
#include <imsg.c>
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
int imsg_fd_overhead = 0;
static int imsg_get_fd(struct imsgbuf *);
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

void imsg_free(struct imsg *imsg)
{
  freezero(imsg->data, imsg->hdr.len - (sizeof(struct imsg_hdr)));
}

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

void imsg_clear(struct imsgbuf *ibuf)
{
  int fd;
  msgbuf_clear(&ibuf->w);
  while ((fd = imsg_get_fd(ibuf)) != (-1))
  {
    close(fd);
  }

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
int imsg_fd_overhead = 0;
static int imsg_get_fd(struct imsgbuf *);
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
  }

  fail:
  free(ifd);

  return n;
}

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

void imsg_free(struct imsg *imsg)
{
  freezero(imsg->data, imsg->hdr.len - (sizeof(struct imsg_hdr)));
}

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

void imsg_clear(struct imsgbuf *ibuf)
{
  int fd;
  msgbuf_clear(&ibuf->w);
  while ((fd = imsg_get_fd(ibuf)) != (-1))
  {
    close(fd);
  }

}

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

