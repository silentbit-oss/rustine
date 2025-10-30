#include <bitstring.h>
#include <compat.h>
#include <ctype.h>
#include <imsg.h>
#include <inttypes.h>
#include <ioctl.h>
#include <limits.h>
#include <queue.h>
#include <stdio.h>
#include <termios.h>
#include <tree.h>
#include <types.h>
#include <uio.h>
#include <unvis.c>
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
int unvis(char *cp, char c, int *astate, int flag)
{
  if (flag & 1)
  {
    if (((*astate) == 5) || ((*astate) == 6))
    {
      *astate = 0;
      return 1;
    }
    return ((*astate) == 0) ? (3) : (-1);
  }
  switch (*astate)
  {
    case 0:
    {
      *cp = 0;
      if (c == '\\')
      {
        *astate = 1;
        return 0;
      }
      *cp = c;
      return 1;
    }

    case 1:
    {
      helper_unvis_1(cp, c, astate);
    }

    case 2:
    {
      if (c == '-')
      {
        *astate = 3;
      }
      else
        if (c == '^')
      {
        *astate = 4;
      }
      else
      {
        *astate = 0;
        return -1;
      }
      return 0;
    }

    case 3:
    {
      *astate = 0;
      *cp |= c;
      return 1;
    }

    case 4:
    {
      if (c == '?')
      {
        *cp |= 0177;
      }
      else
        *cp |= c & 037;
      *astate = 0;
      return 1;
    }

    case 5:
    {
      if ((((u_char) c) >= '0') && (((u_char) c) <= '7'))
      {
        *cp = ((*cp) << 3) + (c - '0');
        *astate = 6;
        return 0;
      }
      *astate = 0;
      return 2;
    }

    case 6:
    {
      *astate = 0;
      if ((((u_char) c) >= '0') && (((u_char) c) <= '7'))
      {
        *cp = ((*cp) << 3) + (c - '0');
        return 1;
      }
      return 2;
    }

    default:
    {
      *astate = 0;
      return -1;
    }

  }

}

int strunvis(char *dst, const char *src)
{
  unsigned int dst_idx = 0;
  char c;
  char *start = dst;
  int state = 0;
  while (c = *(src++))
  {
    again:
    switch (unvis(dst, c, &state, 0))
    {
      case 1:
      {
        dst_idx += 1;
        break;
      }

      case 2:
      {
        dst_idx += 1;
        goto again;
      }

      case 0:

      case 3:
      {
        break;
      }

      default:
      {
        dst[dst_idx] = '\0';
        return -1;
      }

    }


  }

  if (unvis(dst, c, &state, 1) == 1)
  {
    dst_idx += 1;
  }
  dst[dst_idx] = '\0';
  return (&dst[dst_idx]) - start;
}

ssize_t strnunvis(char *dst, const char *src, size_t sz)
{
  unsigned int dst_idx = 0;
  char c;
  char p;
  char *start = dst;
  char *end = ((&dst[dst_idx]) + sz) - 1;
  int state = 0;
  if (sz > 0)
  {
    *end = '\0';
  }
  while (c = *(src++))
  {
    again:
    switch (unvis(&p, c, &state, 0))
    {
      case 1:
      {
        if ((&dst[dst_idx]) < end)
        {
          dst[dst_idx] = p;
        }
        dst_idx += 1;
        break;
      }

      case 2:
      {
        if ((&dst[dst_idx]) < end)
        {
          dst[dst_idx] = p;
        }
        dst_idx += 1;
        goto again;
      }

      case 0:

      case 3:
      {
        break;
      }

      default:
      {
        if ((&dst[dst_idx]) <= end)
        {
          dst[dst_idx] = '\0';
        }
        return -1;
      }

    }


  }

  if (unvis(&p, c, &state, 1) == 1)
  {
    if ((&dst[dst_idx]) < end)
    {
      dst[dst_idx] = p;
    }
    dst_idx += 1;
  }
  if ((&dst[dst_idx]) <= end)
  {
    dst[dst_idx] = '\0';
  }
  return (&dst[dst_idx]) - start;
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
int unvis(char *cp, char c, int *astate, int flag)
{
  if (flag & 1)
  {
    if (((*astate) == 5) || ((*astate) == 6))
    {
      *astate = 0;
      return 1;
    }
    return ((*astate) == 0) ? (3) : (-1);
  }
  switch (*astate)
  {
    case 0:
      *cp = 0;
      if (c == '\\')
    {
      *astate = 1;
      return 0;
    }
      *cp = c;
      return 1;

    case 1:
      switch (c)
    {
      case '\\':
        *cp = c;
        *astate = 0;
        return 1;

      case '0':

      case '1':

      case '2':

      case '3':

      case '4':

      case '5':

      case '6':

      case '7':
        *cp = c - '0';
        *astate = 5;
        return 0;

      case 'M':
        *cp = (char) 0200;
        *astate = 2;
        return 0;

      case '^':
        *astate = 4;
        return 0;

      case 'n':
        *cp = '\n';
        *astate = 0;
        return 1;

      case 'r':
        *cp = '\r';
        *astate = 0;
        return 1;

      case 'b':
        *cp = '\b';
        *astate = 0;
        return 1;

      case 'a':
        *cp = '\007';
        *astate = 0;
        return 1;

      case 'v':
        *cp = '\v';
        *astate = 0;
        return 1;

      case 't':
        *cp = '\t';
        *astate = 0;
        return 1;

      case 'f':
        *cp = '\f';
        *astate = 0;
        return 1;

      case 's':
        *cp = ' ';
        *astate = 0;
        return 1;

      case 'E':
        *cp = '\033';
        *astate = 0;
        return 1;

      case '\n':
        *astate = 0;
        return 3;

      case '$':
        *astate = 0;
        return 3;

    }

      *astate = 0;
      return -1;

    case 2:
      if (c == '-')
    {
      *astate = 3;
    }
    else
      if (c == '^')
    {
      *astate = 4;
    }
    else
    {
      *astate = 0;
      return -1;
    }
      return 0;

    case 3:
      *astate = 0;
      *cp |= c;
      return 1;

    case 4:
      if (c == '?')
    {
      *cp |= 0177;
    }
    else
      *cp |= c & 037;
      *astate = 0;
      return 1;

    case 5:
      if ((((u_char) c) >= '0') && (((u_char) c) <= '7'))
    {
      *cp = ((*cp) << 3) + (c - '0');
      *astate = 6;
      return 0;
    }
      *astate = 0;
      return 2;

    case 6:
      *astate = 0;
      if ((((u_char) c) >= '0') && (((u_char) c) <= '7'))
    {
      *cp = ((*cp) << 3) + (c - '0');
      return 1;
    }
      return 2;

    default:
      *astate = 0;
      return -1;

  }

}

int strunvis(char *dst, const char *src)
{
  unsigned int dst_idx = 0;
  char c;
  char *start = dst;
  int state = 0;
  while (c = *(src++))
  {
    again:
    switch (unvis(dst, c, &state, 0))
    {
      case 1:
        dst_idx += 1;
        break;

      case 2:
        dst_idx += 1;
        goto again;

      case 0:

      case 3:
        break;

      default:
        dst[dst_idx] = '\0';
        return -1;

    }


  }

  if (unvis(dst, c, &state, 1) == 1)
  {
    dst_idx += 1;
  }
  dst[dst_idx] = '\0';
  return (&dst[dst_idx]) - start;
}

ssize_t strnunvis(char *dst, const char *src, size_t sz)
{
  unsigned int dst_idx = 0;
  char c;
  char p;
  char *start = dst;
  char *end = ((&dst[dst_idx]) + sz) - 1;
  int state = 0;
  if (sz > 0)
  {
    *end = '\0';
  }
  while (c = *(src++))
  {
    again:
    switch (unvis(&p, c, &state, 0))
    {
      case 1:
        if ((&dst[dst_idx]) < end)
      {
        dst[dst_idx] = p;
      }
        dst_idx += 1;
        break;

      case 2:
        if ((&dst[dst_idx]) < end)
      {
        dst[dst_idx] = p;
      }
        dst_idx += 1;
        goto again;

      case 0:

      case 3:
        break;

      default:
        if ((&dst[dst_idx]) <= end)
      {
        dst[dst_idx] = '\0';
      }
        return -1;

    }


  }

  if (unvis(&p, c, &state, 1) == 1)
  {
    if ((&dst[dst_idx]) < end)
    {
      dst[dst_idx] = p;
    }
    dst_idx += 1;
  }
  if ((&dst[dst_idx]) <= end)
  {
    dst[dst_idx] = '\0';
  }
  return (&dst[dst_idx]) - start;
}

int helper_unvis_1(char * const cp, char c, int * const astate)
{
  switch (c)
  {
    case '\\':
    {
      *cp = c;
      *astate = 0;
      return 1;
    }

    case '0':

    case '1':

    case '2':

    case '3':

    case '4':

    case '5':

    case '6':

    case '7':
    {
      *cp = c - '0';
      *astate = 5;
      return 0;
    }

    case 'M':
    {
      *cp = (char) 0200;
      *astate = 2;
      return 0;
    }

    case '^':
    {
      *astate = 4;
      return 0;
    }

    case 'n':
    {
      *cp = '\n';
      *astate = 0;
      return 1;
    }

    case 'r':
    {
      *cp = '\r';
      *astate = 0;
      return 1;
    }

    case 'b':
    {
      *cp = '\b';
      *astate = 0;
      return 1;
    }

    case 'a':
    {
      *cp = '\007';
      *astate = 0;
      return 1;
    }

    case 'v':
    {
      *cp = '\v';
      *astate = 0;
      return 1;
    }

    case 't':
    {
      *cp = '\t';
      *astate = 0;
      return 1;
    }

    case 'f':
    {
      *cp = '\f';
      *astate = 0;
      return 1;
    }

    case 's':
    {
      *cp = ' ';
      *astate = 0;
      return 1;
    }

    case 'E':
    {
      *cp = '\033';
      *astate = 0;
      return 1;
    }

    case '\n':
    {
      *astate = 0;
      return 3;
    }

    case '$':
    {
      *astate = 0;
      return 3;
    }

  }

  *astate = 0;
  return -1;
}

