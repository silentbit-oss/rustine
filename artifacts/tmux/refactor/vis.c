#include <bitstring.h>
#include <compat.h>
#include <ctype.h>
#include <errno.h>
#include <imsg.h>
#include <inttypes.h>
#include <ioctl.h>
#include <limits.h>
#include <queue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <tree.h>
#include <types.h>
#include <uio.h>
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
char *vis(char *dst, int c, int flag, int nextc)
{
  unsigned int dst_idx = 0;
  if (((c == '\\') || ((flag & 0x400) == 0)) && ((((((((((u_int) c) <= 255) && isascii((u_char) c)) && (((((c != '*') && (c != '?')) && (c != '[')) && (c != '#')) || ((flag & 0x100) == 0))) && isgraph((u_char) c)) || (((flag & 0x04) == 0) && (c == ' '))) || (((flag & 0x08) == 0) && (c == '\t'))) || (((flag & 0x10) == 0) && (c == '\n'))) || ((flag & 0x20) && ((((c == '\b') || (c == '\007')) || (c == '\r')) || isgraph((u_char) c)))))
  {
    if (((c == '"') && ((flag & 0x200) != 0)) || ((c == '\\') && ((flag & 0x40) == 0)))
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
    }
    dst[dst_idx] = c;
    dst_idx += 1;
    dst[dst_idx] = '\0';
    return dst;
  }
  if (flag & 0x02)
  {
    helper_vis_1(&dst_idx, dst, c, nextc);
  }
  if ((((c & 0177) == ' ') || (flag & 0x01)) || ((flag & 0x100) && ((((c == '*') || (c == '?')) || (c == '[')) || (c == '#'))))
  {
    dst[dst_idx] = '\\';
    dst_idx += 1;
    dst[dst_idx] = ((((u_char) c) >> 6) & 07) + '0';
    dst_idx += 1;
    dst[dst_idx] = ((((u_char) c) >> 3) & 07) + '0';
    dst_idx += 1;
    dst[dst_idx] = (((u_char) c) & 07) + '0';
    dst_idx += 1;
    goto done;
  }
  if ((flag & 0x40) == 0)
  {
    dst[dst_idx] = '\\';
    dst_idx += 1;
  }
  if (c & 0200)
  {
    c &= 0177;
    dst[dst_idx] = 'M';
    dst_idx += 1;
  }
  if (iscntrl((u_char) c))
  {
    dst[dst_idx] = '^';
    dst_idx += 1;
    if (c == 0177)
    {
      dst[dst_idx] = '?';
      dst_idx += 1;
    }
    else
      dst[dst_idx] = c + '@';
    dst_idx += 1;
  }
  else
  {
    dst[dst_idx] = '-';
    dst_idx += 1;
    dst[dst_idx] = c;
    dst_idx += 1;
  }
  done:
  dst[dst_idx] = '\0';

  return dst;
}

int strvis(char *dst, const char *src, int flag)
{
  unsigned int src_idx = 0;
  unsigned int dst_idx = 0;
  char c;
  char *start;
  unsigned int start_idx = 0;
  for (start_idx = &dst[dst_idx]; c = src[src_idx];)
  {
    src_idx += 1;
    dst_idx = vis(dst_idx, c, flag, *(&src[src_idx]));
  }

  dst[dst_idx] = '\0';
  return (&dst[dst_idx]) - (&start[start_idx]);
}

int strnvis(char *dst, const char *src, size_t siz, int flag)
{
  unsigned int src_idx = 0;
  unsigned int dst_idx = 0;
  char *start;
  unsigned int start_idx = 0;
  char *end;
  unsigned int end_idx = 0;
  char tbuf[5];
  int c;
  int i;
  i = 0;
  for (start_idx = &dst[dst_idx], end_idx = ((&start[start_idx]) + siz) - 1; (c = src[src_idx]) && ((&dst[dst_idx]) < (&end[end_idx]));)
  {
    helper_strnvis_1(&src_idx, &dst_idx, &i, dst, src, flag, end, end_idx, tbuf, c);
  }

  if (siz > 0)
  {
    dst[dst_idx] = '\0';
  }
  if (((&dst[dst_idx]) + i) > (&end[end_idx]))
  {
    while (c = src[src_idx])
    {
      src_idx += 1;
      dst_idx += vis(tbuf, c, flag, *(&src[src_idx])) - tbuf;
    }

  }
  return (&dst[dst_idx]) - (&start[start_idx]);
}

int stravis(char **outp, const char *src, int flag)
{
  char *buf;
  unsigned int buf_idx = 0;
  int len;
  int serrno;
  buf_idx = calloc(4, strlen(src) + 1);
  if ((&buf[buf_idx]) == 0)
  {
    return -1;
  }
  len = strvis(buf, src, flag);
  serrno = errno;
  *outp = realloc(buf, len + 1);
  if ((*outp) == 0)
  {
    *outp = &buf[buf_idx];
    errno = serrno;
  }
  return len;
}

int strvisx(char *dst, const char *src, size_t len, int flag)
{
  unsigned int src_idx = 0;
  unsigned int dst_idx = 0;
  char c;
  char *start;
  unsigned int start_idx = 0;
  for (start_idx = &dst[dst_idx]; len > 1; len -= 1)
  {
    c = src[src_idx];
    src_idx += 1;
    dst_idx = vis(dst_idx, c, flag, *(&src[src_idx]));
  }

  if (len)
  {
    dst_idx = vis(dst_idx, *(&src[src_idx]), flag, '\0');
  }
  dst[dst_idx] = '\0';
  return (&dst[dst_idx]) - (&start[start_idx]);
}

void helper_vis_1(unsigned int * const dst_idx_ref, char * const dst, int c, int nextc)
{
  unsigned int dst_idx = *dst_idx_ref;
  switch (c)
  {
    case '\n':
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
      dst[dst_idx] = 'n';
      dst_idx += 1;
      goto done;
    }

    case '\r':
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
      dst[dst_idx] = 'r';
      dst_idx += 1;
      goto done;
    }

    case '\b':
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
      dst[dst_idx] = 'b';
      dst_idx += 1;
      goto done;
    }

    case '\a':
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
      dst[dst_idx] = 'a';
      dst_idx += 1;
      goto done;
    }

    case '\v':
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
      dst[dst_idx] = 'v';
      dst_idx += 1;
      goto done;
    }

    case '\t':
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
      dst[dst_idx] = 't';
      dst_idx += 1;
      goto done;
    }

    case '\f':
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
      dst[dst_idx] = 'f';
      dst_idx += 1;
      goto done;
    }

    case ' ':
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
      dst[dst_idx] = 's';
      dst_idx += 1;
      goto done;
    }

    case '\0':
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
      dst[dst_idx] = '0';
      dst_idx += 1;
      if ((((u_char) nextc) >= '0') && (((u_char) nextc) <= '7'))
      {
        dst[dst_idx] = '0';
        dst_idx += 1;
        dst[dst_idx] = '0';
        dst_idx += 1;
      }
      goto done;
    }

  }

  *dst_idx_ref = dst_idx;
}

void helper_strnvis_1(unsigned int * const src_idx_ref, unsigned int * const dst_idx_ref, int * const i_ref, char * const dst, const char * const src, int flag, char * const end, unsigned int end_idx, char tbuf[5], int c)
{
  unsigned int src_idx = *src_idx_ref;
  unsigned int dst_idx = *dst_idx_ref;
  int i = *i_ref;
  if (((c == '\\') || ((flag & 0x400) == 0)) && ((((((((((u_int) c) <= 255) && isascii((u_char) c)) && (((((c != '*') && (c != '?')) && (c != '[')) && (c != '#')) || ((flag & 0x100) == 0))) && isgraph((u_char) c)) || (((flag & 0x04) == 0) && (c == ' '))) || (((flag & 0x08) == 0) && (c == '\t'))) || (((flag & 0x10) == 0) && (c == '\n'))) || ((flag & 0x20) && ((((c == '\b') || (c == '\007')) || (c == '\r')) || isgraph((u_char) c)))))
  {
    if (((c == '"') && ((flag & 0x200) != 0)) || ((c == '\\') && ((flag & 0x40) == 0)))
    {
      if (((&dst[dst_idx]) + 1) >= (&end[end_idx]))
      {
        i = 2;
        break;
      }
      dst[dst_idx] = '\\';
      dst_idx += 1;
    }
    i = 1;
    dst[dst_idx] = c;
    dst_idx += 1;
    src_idx += 1;
  }
  else
  {
    src_idx += 1;
    i = vis(tbuf, c, flag, *(&src[src_idx])) - tbuf;
    if (((&dst[dst_idx]) + i) <= (&end[end_idx]))
    {
      memcpy(dst, tbuf, i);
      dst_idx += i;
    }
    else
    {
      src_idx -= 1;
      break;
    }
  }
  *src_idx_ref = src_idx;
  *dst_idx_ref = dst_idx;
  *i_ref = i;
}

