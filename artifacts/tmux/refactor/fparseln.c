#include <bitstring.h>
#include <compat.h>
#include <fparseln.c>
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
static int isescaped(const char *, const char *, int);
static int isescaped(const char *sp, const char *p, int esc)
{
  const char *cp;
  unsigned int cp_idx = 0;
  size_t ne;
  if (esc == '\0')
  {
    return 1;
  }
  for (ne = 0, cp_idx = p; ((--(&cp[cp_idx])) >= sp) && (cp[cp_idx] == esc); ne += 1)
  {
    continue;
  }

  return (ne & 1) != 0;
}

char *fparseln(FILE *fp, size_t *size, size_t *lineno, const char str[3], int flags)
{
  static const char dstr[3] = {'\\', '\\', '#'};
  char *buf = 0;
  unsigned int buf_idx = 0;
  char *ptr;
  unsigned int ptr_idx = 0;
  char *cp;
  unsigned int cp_idx = 0;
  char esc;
  char con;
  char nl;
  char com;
  size_t s;
  size_t len = 0;
  int cnt = 1;
  if (str == 0)
  {
    str = dstr;
  }
  esc = str[0];
  con = str[1];
  com = str[2];
  nl = '\n';
  while (cnt)
  {
    helper_fparseln_2(&buf_idx, &ptr_idx, &cp_idx, &s, &len, &cnt, fp, lineno, buf, ptr, cp, esc, con, nl, com);
  }

  if (((((flags & 0x0f) != 0) && esc) && ((&buf[buf_idx]) != 0)) && (strchr(buf, esc) != 0))
  {
    helper_fparseln_1(&ptr_idx, &cp_idx, &len, flags, buf, ptr, cp, esc, con, com);
  }
  if (size)
  {
    *size = len;
  }
  return buf;
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
static int isescaped(const char *, const char *, int);
static int isescaped(const char *sp, const char *p, int esc)
{
  const char *cp;
  unsigned int cp_idx = 0;
  size_t ne;
  if (esc == '\0')
  {
    return 1;
  }
  for (ne = 0, cp_idx = p; ((--(&cp[cp_idx])) >= sp) && (cp[cp_idx] == esc); ne += 1)
  {
    continue;
  }

  return (ne & 1) != 0;
}

char *fparseln(FILE *fp, size_t *size, size_t *lineno, const char str[3], int flags)
{
  static const char dstr[3] = {'\\', '\\', '#'};
  char *buf = 0;
  unsigned int buf_idx = 0;
  char *ptr;
  unsigned int ptr_idx = 0;
  char *cp;
  unsigned int cp_idx = 0;
  char esc;
  char con;
  char nl;
  char com;
  size_t s;
  size_t len = 0;
  int cnt = 1;
  if (str == 0)
  {
    str = dstr;
  }
  esc = str[0];
  con = str[1];
  com = str[2];
  nl = '\n';
  while (cnt)
  {
    cnt = 0;
    if (lineno)
    {
      *lineno += 1;
    }
    if ((ptr_idx = fgetln(fp, &s)) == 0)
    {
      break;
    }
    if (s && com)
    {
      for (cp_idx = &ptr[ptr_idx]; (&cp[cp_idx]) < ((&ptr[ptr_idx]) + s); cp_idx += 1)
      {
        if ((cp[cp_idx] == com) && (!isescaped(ptr, cp, esc)))
        {
          s = (&cp[cp_idx]) - (&ptr[ptr_idx]);
          cnt = (s == 0) && ((&buf[buf_idx]) == 0);
          break;
        }
      }

    }
    if (s && nl)
    {
      cp_idx = &ptr[(s - 1) + ptr_idx];
      if (cp[cp_idx] == nl)
      {
        s -= 1;
      }
    }
    if (s && con)
    {
      cp_idx = &ptr[(s - 1) + ptr_idx];
      if ((cp[cp_idx] == con) && (!isescaped(ptr, cp, esc)))
      {
        s -= 1;
        cnt = 1;
      }
    }
    if ((s == 0) && ((&buf[buf_idx]) != 0))
    {
      continue;
    }
    if ((cp_idx = realloc(buf, (len + s) + 1)) == 0)
    {
      free(buf);
      return 0;
    }
    buf_idx = &cp[cp_idx];
    (void) memcpy((&buf[buf_idx]) + len, ptr, s);
    len += s;
    buf[len + buf_idx] = '\0';
  }

  if (((((flags & 0x0f) != 0) && esc) && ((&buf[buf_idx]) != 0)) && (strchr(buf, esc) != 0))
  {
    ptr_idx = (cp = &cp[cp_idx + cp_idx]);
    while (cp[0 + cp_idx] != '\0')
    {
      int skipesc;
      while ((cp[0 + cp_idx] != '\0') && (cp[0 + cp_idx] != esc))
      {
        ptr[ptr_idx] = cp[cp_idx];
        cp_idx += 1;
        ptr_idx += 1;
      }

      if ((cp[0 + cp_idx] == '\0') || (cp[1 + cp_idx] == '\0'))
      {
        break;
      }
      skipesc = 0;
      if (cp[1 + cp_idx] == com)
      {
        skipesc += flags & 0x04;
      }
      if (cp[1 + cp_idx] == con)
      {
        skipesc += flags & 0x02;
      }
      if (cp[1 + cp_idx] == esc)
      {
        skipesc += flags & 0x01;
      }
      if (((cp[1 + cp_idx] != com) && (cp[1 + cp_idx] != con)) && (cp[1 + cp_idx] != esc))
      {
        skipesc = flags & 0x08;
      }
      if (skipesc)
      {
        cp_idx += 1;
      }
      else
        ptr[ptr_idx] = cp[cp_idx];
      cp_idx += 1;
      ptr_idx += 1;
      ptr[ptr_idx] = cp[cp_idx];
      cp_idx += 1;
      ptr_idx += 1;
    }

    ptr[ptr_idx] = '\0';
    len = strlen(buf);
  }
  if (size)
  {
    *size = len;
  }
  return buf;
}

void helper_fparseln_1(unsigned int * const ptr_idx_ref, unsigned int * const cp_idx_ref, size_t * const len_ref, int flags, char * const buf, char * const ptr, char * const cp, char esc, char con, char com)
{
  unsigned int ptr_idx = *ptr_idx_ref;
  unsigned int cp_idx = *cp_idx_ref;
  size_t len = *len_ref;
  ptr_idx = (cp = &cp[cp_idx + cp_idx]);
  while (cp[0 + cp_idx] != '\0')
  {
    helper_helper_fparseln_1_1(&ptr_idx, &cp_idx, flags, ptr, cp, esc, con, com);
  }

  ptr[ptr_idx] = '\0';
  len = strlen(buf);
  *ptr_idx_ref = ptr_idx;
  *cp_idx_ref = cp_idx;
  *len_ref = len;
}

char *helper_fparseln_2(unsigned int * const buf_idx_ref, unsigned int * const ptr_idx_ref, unsigned int * const cp_idx_ref, size_t * const s_ref, size_t * const len_ref, int * const cnt_ref, FILE * const fp, size_t * const lineno, char * const buf, char * const ptr, char * const cp, char esc, char con, char nl, char com)
{
  unsigned int buf_idx = *buf_idx_ref;
  unsigned int ptr_idx = *ptr_idx_ref;
  unsigned int cp_idx = *cp_idx_ref;
  size_t s = *s_ref;
  size_t len = *len_ref;
  int cnt = *cnt_ref;
  cnt = 0;
  if (lineno)
  {
    *lineno += 1;
  }
  if ((ptr_idx = fgetln(fp, &s)) == 0)
  {
    break;
  }
  if (s && com)
  {
    for (cp_idx = &ptr[ptr_idx]; (&cp[cp_idx]) < ((&ptr[ptr_idx]) + s); cp_idx += 1)
    {
      if ((cp[cp_idx] == com) && (!isescaped(ptr, cp, esc)))
      {
        s = (&cp[cp_idx]) - (&ptr[ptr_idx]);
        cnt = (s == 0) && ((&buf[buf_idx]) == 0);
        break;
      }
    }

  }
  if (s && nl)
  {
    cp_idx = &ptr[(s - 1) + ptr_idx];
    if (cp[cp_idx] == nl)
    {
      s -= 1;
    }
  }
  if (s && con)
  {
    cp_idx = &ptr[(s - 1) + ptr_idx];
    if ((cp[cp_idx] == con) && (!isescaped(ptr, cp, esc)))
    {
      s -= 1;
      cnt = 1;
    }
  }
  if ((s == 0) && ((&buf[buf_idx]) != 0))
  {
    continue;
  }
  if ((cp_idx = realloc(buf, (len + s) + 1)) == 0)
  {
    free(buf);
    return 0;
  }
  buf_idx = &cp[cp_idx];
  (void) memcpy((&buf[buf_idx]) + len, ptr, s);
  len += s;
  buf[len + buf_idx] = '\0';
  *buf_idx_ref = buf_idx;
  *ptr_idx_ref = ptr_idx;
  *cp_idx_ref = cp_idx;
  *s_ref = s;
  *len_ref = len;
  *cnt_ref = cnt;
}

void helper_helper_fparseln_1_1(unsigned int * const ptr_idx_ref, unsigned int * const cp_idx_ref, int flags, char * const ptr, char * const cp, char esc, char con, char com)
{
  unsigned int ptr_idx = *ptr_idx_ref;
  unsigned int cp_idx = *cp_idx_ref;
  int skipesc;
  while ((cp[0 + cp_idx] != '\0') && (cp[0 + cp_idx] != esc))
  {
    ptr[ptr_idx] = cp[cp_idx];
    cp_idx += 1;
    ptr_idx += 1;
  }

  if ((cp[0 + cp_idx] == '\0') || (cp[1 + cp_idx] == '\0'))
  {
    break;
  }
  skipesc = 0;
  if (cp[1 + cp_idx] == com)
  {
    skipesc += flags & 0x04;
  }
  if (cp[1 + cp_idx] == con)
  {
    skipesc += flags & 0x02;
  }
  if (cp[1 + cp_idx] == esc)
  {
    skipesc += flags & 0x01;
  }
  if (((cp[1 + cp_idx] != com) && (cp[1 + cp_idx] != con)) && (cp[1 + cp_idx] != esc))
  {
    skipesc = flags & 0x08;
  }
  if (skipesc)
  {
    cp_idx += 1;
  }
  else
    ptr[ptr_idx] = cp[cp_idx];
  cp_idx += 1;
  ptr_idx += 1;
  ptr[ptr_idx] = cp[cp_idx];
  cp_idx += 1;
  ptr_idx += 1;
  *ptr_idx_ref = ptr_idx;
  *cp_idx_ref = cp_idx;
}

