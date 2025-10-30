#include <errno.h>
#include <fcntl.h>
#include <gzguts.h>
#include <gzread.c>
#include <limits.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <types.h>
#include <unistd.h>
#include <zconf.h>
#include <zlib.h>

typedef size_t z_size_t;
typedef unsigned char Byte;
typedef unsigned int uInt;
typedef unsigned long uLong;
typedef Byte Bytef;
typedef char charf;
typedef int intf;
typedef uInt uIntf;
typedef uLong uLongf;
typedef const void *voidpc;
typedef void *voidpf;
typedef void *voidp;
typedef unsigned z_crc_t;
typedef voidpf (*alloc_func)(voidpf opaque, uInt items, uInt size);
typedef void (*free_func)(voidpf opaque, voidpf address);
struct internal_state;
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream;
typedef z_stream *z_streamp;
typedef struct gz_header_s
{
  int text;
  uLong time;
  int xflags;
  int os;
  Bytef *extra;
  uInt extra_len;
  uInt extra_max;
  Bytef *name;
  uInt name_max;
  Bytef *comment;
  uInt comm_max;
  int hcrc;
  int done;
} gz_header;
typedef gz_header *gz_headerp;
extern const char *zlibVersion(void);
extern int deflate(z_streamp strm, int flush);
extern int deflateEnd(z_streamp strm);
extern int inflate(z_streamp strm, int flush);
extern int inflateEnd(z_streamp strm);
extern int deflateSetDictionary(z_streamp strm, const Bytef *dictionary, uInt dictLength);
extern int deflateGetDictionary(z_streamp strm, Bytef *dictionary, uInt *dictLength);
extern int deflateCopy(z_streamp dest, z_streamp source);
extern int deflateReset(z_streamp strm);
extern int deflateParams(z_streamp strm, int level, int strategy);
extern int deflateTune(z_streamp strm, int good_length, int max_lazy, int nice_length, int max_chain);
extern uLong deflateBound(z_streamp strm, uLong sourceLen);
extern int deflatePending(z_streamp strm, unsigned *pending, int *bits);
extern int deflatePrime(z_streamp strm, int bits, int value);
extern int deflateSetHeader(z_streamp strm, gz_headerp head);
extern int inflateSetDictionary(z_streamp strm, const Bytef *dictionary, uInt dictLength);
extern int inflateGetDictionary(z_streamp strm, Bytef *dictionary, uInt *dictLength);
extern int inflateSync(z_streamp strm);
extern int inflateCopy(z_streamp dest, z_streamp source);
extern int inflateReset(z_streamp strm);
extern int inflateReset2(z_streamp strm, int windowBits);
extern int inflatePrime(z_streamp strm, int bits, int value);
extern long inflateMark(z_streamp strm);
extern int inflateGetHeader(z_streamp strm, gz_headerp head);
typedef unsigned (*in_func)(void *, unsigned char **);
typedef int (*out_func)(void *, unsigned char *, unsigned);
extern int inflateBack(z_streamp strm, in_func in, void *in_desc, out_func out, void *out_desc);
extern int inflateBackEnd(z_streamp strm);
extern uLong zlibCompileFlags(void);
extern int compress(Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen);
extern int compress2(Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen, int level);
extern uLong compressBound(uLong sourceLen);
extern int uncompress(Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen);
extern int uncompress2(Bytef *dest, uLongf *destLen, const Bytef *source, uLong *sourceLen);
typedef struct gzFile_s *gzFile;
extern gzFile gzdopen(int fd, const char *mode);
extern int gzbuffer(gzFile file, unsigned size);
extern int gzsetparams(gzFile file, int level, int strategy);
extern int gzread(gzFile file, voidp buf, unsigned len);
extern z_size_t gzfread(voidp buf, z_size_t size, z_size_t nitems, gzFile file);
extern int gzwrite(gzFile file, voidpc buf, unsigned len);
extern z_size_t gzfwrite(voidpc buf, z_size_t size, z_size_t nitems, gzFile file);
extern int gzprintf(gzFile file, const char *format, ...);
extern int gzputs(gzFile file, const char *s);
extern char *gzgets(gzFile file, char *buf, int len);
extern int gzputc(gzFile file, int c);
extern int gzgetc(gzFile file);
extern int gzungetc(int c, gzFile file);
extern int gzflush(gzFile file, int flush);
extern int gzrewind(gzFile file);
extern int gzeof(gzFile file);
extern int gzdirect(gzFile file);
extern int gzclose(gzFile file);
extern int gzclose_r(gzFile file);
extern int gzclose_w(gzFile file);
extern const char *gzerror(gzFile file, int *errnum);
extern void gzclearerr(gzFile file);
extern uLong adler32(uLong adler, const Bytef *buf, uInt len);
extern uLong adler32_z(uLong adler, const Bytef *buf, z_size_t len);
extern uLong crc32(uLong crc, const Bytef *buf, uInt len);
extern uLong crc32_z(uLong crc, const Bytef *buf, z_size_t len);
extern uLong crc32_combine_op(uLong crc1, uLong crc2, uLong op);
extern int deflateInit_(z_streamp strm, int level, const char *version, int stream_size);
extern int inflateInit_(z_streamp strm, const char *version, int stream_size);
extern int deflateInit2_(z_streamp strm, int level, int method, int windowBits, int memLevel, int strategy, const char *version, int stream_size);
extern int inflateInit2_(z_streamp strm, int windowBits, const char *version, int stream_size);
extern int inflateBackInit_(z_streamp strm, int windowBits, unsigned char *window, const char *version, int stream_size);
struct gzFile_s
{
  unsigned have;
  unsigned char *next;
  off_t pos;
};
extern int gzgetc_(gzFile file);
extern gzFile gzopen(const char *, const char *);
extern off_t gzseek(gzFile, off_t, int);
extern off_t gztell(gzFile);
extern off_t gzoffset(gzFile);
extern uLong adler32_combine(uLong, uLong, off_t);
extern uLong crc32_combine(uLong, uLong, off_t);
extern uLong crc32_combine_gen(off_t);
extern const char *zError(int);
extern int inflateSyncPoint(z_streamp);
extern const z_crc_t *get_crc_table(void);
extern int inflateUndermine(z_streamp, int);
extern int inflateValidate(z_streamp, int);
extern unsigned long inflateCodesUsed(z_streamp);
extern int inflateResetKeep(z_streamp);
extern int deflateResetKeep(z_streamp);
extern int gzvprintf(gzFile file, const char *format, va_list va);
extern gzFile gzopen64(const char *, const char *);
extern off_t gzseek64(gzFile, off_t, int);
extern off_t gztell64(gzFile);
extern off_t gzoffset64(gzFile);
typedef struct 
{
  struct gzFile_s x;
  int mode;
  int fd;
  char *path;
  unsigned size;
  unsigned want;
  unsigned char *in;
  unsigned char *out;
  int direct;
  int how;
  off_t start;
  int eof;
  int past;
  int level;
  int strategy;
  int reset;
  off_t skip;
  int seek;
  int err;
  char *msg;
  z_stream strm;
} gz_state;
typedef gz_state *gz_statep;
void gz_error(gz_statep, int, const char *);
static int gz_load(gz_statep state, unsigned char *buf, unsigned len, unsigned *have)
{
  int ret;
  unsigned get;
  unsigned max = (((unsigned) (-1)) >> 2) + 1;
  *have = 0;
  do
  {
    get = len - (*have);
    if (get > max)
    {
      get = max;
    }
    ret = read(state->fd, buf + (*have), get);
    if (ret <= 0)
    {
      break;
    }
    *have += (unsigned) ret;
  }
  while ((*have) < len);
  if (ret < 0)
  {
    gz_error(state, -1, strerror(errno));
    return -1;
  }
  if (ret == 0)
  {
    state->eof = 1;
  }
  return 0;
}

static int gz_avail(gz_statep state)
{
  unsigned got;
  z_streamp strm = &state->strm;
  if ((state->err != 0) && (state->err != (-5)))
  {
    return -1;
  }
  if (state->eof == 0)
  {
    if (strm->avail_in)
    {
      unsigned char *p = state->in;
      unsigned int p_idx = 0;
      const unsigned char *q = strm->next_in;
      unsigned int q_idx = 0;
      unsigned n = strm->avail_in;
      do
      {
        p[p_idx] = q[q_idx];
        q_idx += 1;
        p_idx += 1;
      }
      while (--n);
    }
    if (gz_load(state, state->in + strm->avail_in, state->size - strm->avail_in, &got) == (-1))
    {
      return -1;
    }
    strm->avail_in += got;
    strm->next_in = state->in;
  }
  return 0;
}

static int gz_look(gz_statep state)
{
  z_streamp strm = &state->strm;
  if (state->size == 0)
  {
    helper_gz_look_1(&state);
  }
  if (strm->avail_in < 2)
  {
    if (gz_avail(state) == (-1))
    {
      return -1;
    }
    if (strm->avail_in == 0)
    {
      return 0;
    }
  }
  if (((strm->avail_in > 1) && (strm->next_in[0] == 31)) && (strm->next_in[1] == 139))
  {
    inflateReset(strm);
    state->how = 2;
    state->direct = 0;
    return 0;
  }
  if (state->direct == 0)
  {
    strm->avail_in = 0;
    state->eof = 1;
    state->x.have = 0;
    return 0;
  }
  state->x.next = state->out;
  memcpy(state->x.next, strm->next_in, strm->avail_in);
  state->x.have = strm->avail_in;
  strm->avail_in = 0;
  state->how = 1;
  state->direct = 1;
  return 0;
}

static int gz_decomp(gz_statep state)
{
  int ret = 0;
  unsigned had;
  z_streamp strm = &state->strm;
  had = strm->avail_out;
  do
  {
    if ((strm->avail_in == 0) && (gz_avail(state) == (-1)))
    {
      return -1;
    }
    if (strm->avail_in == 0)
    {
      gz_error(state, -5, "unexpected end of file");
      break;
    }
    ret = inflate(strm, 0);
    if ((ret == (-2)) || (ret == 2))
    {
      gz_error(state, -2, "internal error: inflate stream corrupt");
      return -1;
    }
    if (ret == (-4))
    {
      gz_error(state, -4, "out of memory");
      return -1;
    }
    if (ret == (-3))
    {
      gz_error(state, -3, (strm->msg == 0) ? ("compressed data error") : (strm->msg));
      return -1;
    }
  }
  while (strm->avail_out && (ret != 1));
  state->x.have = had - strm->avail_out;
  state->x.next = strm->next_out - state->x.have;
  if (ret == 1)
  {
    state->how = 0;
  }
  return 0;
}

static int gz_fetch(gz_statep state)
{
  z_streamp strm = &state->strm;
  do
  {
    switch (state->how)
    {
      case 0:
      {
        if (gz_look(state) == (-1))
        {
          return -1;
        }
        if (state->how == 0)
        {
          return 0;
        }
        break;
      }

      case 1:
      {
        if (gz_load(state, state->out, state->size << 1, &state->x.have) == (-1))
        {
          return -1;
        }
        state->x.next = state->out;
        return 0;
      }

      case 2:
      {
        strm->avail_out = state->size << 1;
        strm->next_out = state->out;
        if (gz_decomp(state) == (-1))
        {
          return -1;
        }
      }

    }

  }
  while ((state->x.have == 0) && ((!state->eof) || strm->avail_in));
  return 0;
}

static int gz_skip(gz_statep state, off_t len)
{
  unsigned n;
  while (len)
  {
    if (state->x.have)
    {
      n = ((((sizeof(int)) == (sizeof(off_t))) && (state->x.have > 2147483647)) || (((off_t) state->x.have) > len)) ? ((unsigned) len) : (state->x.have);
      state->x.have -= n;
      state->x.next += n;
      state->x.pos += n;
      len -= n;
    }
    else
      if (state->eof && (state->strm.avail_in == 0))
    {
      break;
    }
    else
    {
      if (gz_fetch(state) == (-1))
      {
        return -1;
      }
    }
  }

  return 0;
}

static z_size_t gz_read(gz_statep state, voidp buf, z_size_t len)
{
  z_size_t got;
  unsigned n;
  if (len == 0)
  {
    return 0;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_skip(state, state->skip) == (-1))
    {
      return 0;
    }
  }
  got = 0;
  do
  {
    helper_gz_read_1(&state, &buf, &len, &got, &n);
  }
  while (len);
  return got;
}

int gzread(gzFile file, voidp buf, unsigned len)
{
  gz_statep state;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) || ((state->err != 0) && (state->err != (-5))))
  {
    return -1;
  }
  if (((int) len) < 0)
  {
    gz_error(state, -2, "request does not fit in an int");
    return -1;
  }
  len = (unsigned) gz_read(state, buf, len);
  if (((len == 0) && (state->err != 0)) && (state->err != (-5)))
  {
    return -1;
  }
  return (int) len;
}

z_size_t gzfread(voidp buf, z_size_t size, z_size_t nitems, gzFile file)
{
  z_size_t len;
  gz_statep state;
  if (file == 0)
  {
    return 0;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) || ((state->err != 0) && (state->err != (-5))))
  {
    return 0;
  }
  len = nitems * size;
  if (size && ((len / size) != nitems))
  {
    gz_error(state, -2, "request does not fit in a size_t");
    return 0;
  }
  return (len) ? (gz_read(state, buf, len) / size) : (0);
}

int gzgetc(gzFile file)
{
  unsigned char buf[1];
  gz_statep state;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) || ((state->err != 0) && (state->err != (-5))))
  {
    return -1;
  }
  if (state->x.have)
  {
    state->x.have -= 1;
    state->x.pos += 1;
    return *(state->x.next++);
  }
  return (gz_read(state, buf, 1) < 1) ? (-1) : (buf[0]);
}

int gzgetc_(gzFile file)
{
  return gzgetc(file);
}

int gzungetc(int c, gzFile file)
{
  gz_statep state;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  if (((state->mode == 7247) && (state->how == 0)) && (state->x.have == 0))
  {
    (void) gz_look(state);
  }
  if ((state->mode != 7247) || ((state->err != 0) && (state->err != (-5))))
  {
    return -1;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_skip(state, state->skip) == (-1))
    {
      return -1;
    }
  }
  if (c < 0)
  {
    return -1;
  }
  if (state->x.have == 0)
  {
    state->x.have = 1;
    state->x.next = (state->out + (state->size << 1)) - 1;
    state->x.next[0] = (unsigned char) c;
    state->x.pos -= 1;
    state->past = 0;
    return c;
  }
  if (state->x.have == (state->size << 1))
  {
    gz_error(state, -3, "out of room to push characters");
    return -1;
  }
  if (state->x.next == state->out)
  {
    unsigned char *src = state->out + state->x.have;
    unsigned int src_idx = 0;
    unsigned char *dest = state->out + (state->size << 1);
    unsigned int dest_idx = 0;
    while ((&src[src_idx]) > state->out)
    {
      src_idx -= 1;
      dest_idx -= 1;
      dest[dest_idx] = src[src_idx];
    }

    state->x.next = &dest[dest_idx];
  }
  state->x.have += 1;
  state->x.next -= 1;
  state->x.next[0] = (unsigned char) c;
  state->x.pos -= 1;
  state->past = 0;
  return c;
}

char *gzgets(gzFile file, char *buf, int len)
{
  unsigned int buf_idx = 0;
  unsigned left;
  unsigned n;
  char *str;
  unsigned int str_idx = 0;
  unsigned char *eol;
  unsigned int eol_idx = 0;
  gz_statep state;
  if (((file == 0) || ((&buf[buf_idx]) == 0)) || (len < 1))
  {
    return 0;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) || ((state->err != 0) && (state->err != (-5))))
  {
    return 0;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_skip(state, state->skip) == (-1))
    {
      return 0;
    }
  }
  str_idx = &buf[buf_idx];
  left = ((unsigned) len) - 1;
  if (left)
  {
    helper_gzgets_1(&buf_idx, &left, &n, &eol_idx, &state, buf, eol);
  }
  if ((&buf[buf_idx]) == (&str[str_idx]))
  {
    return 0;
  }
  buf[0 + buf_idx] = 0;
  return str;
}

int gzdirect(gzFile file)
{
  gz_statep state;
  if (file == 0)
  {
    return 0;
  }
  state = (gz_statep) file;
  if (((state->mode == 7247) && (state->how == 0)) && (state->x.have == 0))
  {
    (void) gz_look(state);
  }
  return state->direct;
}

int gzclose_r(gzFile file)
{
  int ret;
  int err;
  gz_statep state;
  if (file == 0)
  {
    return -2;
  }
  state = (gz_statep) file;
  if (state->mode != 7247)
  {
    return -2;
  }
  if (state->size)
  {
    inflateEnd(&state->strm);
    free(state->out);
    free(state->in);
  }
  err = (state->err == (-5)) ? (-5) : (0);
  gz_error(state, 0, 0);
  free(state->path);
  ret = close(state->fd);
  free(state);
  return (ret) ? (-1) : (err);
}


typedef size_t z_size_t;
typedef unsigned char Byte;
typedef unsigned int uInt;
typedef unsigned long uLong;
typedef Byte Bytef;
typedef char charf;
typedef int intf;
typedef uInt uIntf;
typedef uLong uLongf;
typedef const void *voidpc;
typedef void *voidpf;
typedef void *voidp;
typedef unsigned z_crc_t;
typedef voidpf (*alloc_func)(voidpf opaque, uInt items, uInt size);
typedef void (*free_func)(voidpf opaque, voidpf address);
struct internal_state;
typedef struct z_stream_s
{
  Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  char *msg;
  struct internal_state *state;
  alloc_func zalloc;
  free_func zfree;
  voidpf opaque;
  int data_type;
  uLong adler;
  uLong reserved;
} z_stream;
typedef z_stream *z_streamp;
typedef struct gz_header_s
{
  int text;
  uLong time;
  int xflags;
  int os;
  Bytef *extra;
  uInt extra_len;
  uInt extra_max;
  Bytef *name;
  uInt name_max;
  Bytef *comment;
  uInt comm_max;
  int hcrc;
  int done;
} gz_header;
typedef gz_header *gz_headerp;
extern const char *zlibVersion(void);
extern int deflate(z_streamp strm, int flush);
extern int deflateEnd(z_streamp strm);
extern int inflate(z_streamp strm, int flush);
extern int inflateEnd(z_streamp strm);
extern int deflateSetDictionary(z_streamp strm, const Bytef *dictionary, uInt dictLength);
extern int deflateGetDictionary(z_streamp strm, Bytef *dictionary, uInt *dictLength);
extern int deflateCopy(z_streamp dest, z_streamp source);
extern int deflateReset(z_streamp strm);
extern int deflateParams(z_streamp strm, int level, int strategy);
extern int deflateTune(z_streamp strm, int good_length, int max_lazy, int nice_length, int max_chain);
extern uLong deflateBound(z_streamp strm, uLong sourceLen);
extern int deflatePending(z_streamp strm, unsigned *pending, int *bits);
extern int deflatePrime(z_streamp strm, int bits, int value);
extern int deflateSetHeader(z_streamp strm, gz_headerp head);
extern int inflateSetDictionary(z_streamp strm, const Bytef *dictionary, uInt dictLength);
extern int inflateGetDictionary(z_streamp strm, Bytef *dictionary, uInt *dictLength);
extern int inflateSync(z_streamp strm);
extern int inflateCopy(z_streamp dest, z_streamp source);
extern int inflateReset(z_streamp strm);
extern int inflateReset2(z_streamp strm, int windowBits);
extern int inflatePrime(z_streamp strm, int bits, int value);
extern long inflateMark(z_streamp strm);
extern int inflateGetHeader(z_streamp strm, gz_headerp head);
typedef unsigned (*in_func)(void *, unsigned char **);
typedef int (*out_func)(void *, unsigned char *, unsigned);
extern int inflateBack(z_streamp strm, in_func in, void *in_desc, out_func out, void *out_desc);
extern int inflateBackEnd(z_streamp strm);
extern uLong zlibCompileFlags(void);
extern int compress(Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen);
extern int compress2(Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen, int level);
extern uLong compressBound(uLong sourceLen);
extern int uncompress(Bytef *dest, uLongf *destLen, const Bytef *source, uLong sourceLen);
extern int uncompress2(Bytef *dest, uLongf *destLen, const Bytef *source, uLong *sourceLen);
typedef struct gzFile_s *gzFile;
extern gzFile gzdopen(int fd, const char *mode);
extern int gzbuffer(gzFile file, unsigned size);
extern int gzsetparams(gzFile file, int level, int strategy);
extern int gzread(gzFile file, voidp buf, unsigned len);
extern z_size_t gzfread(voidp buf, z_size_t size, z_size_t nitems, gzFile file);
extern int gzwrite(gzFile file, voidpc buf, unsigned len);
extern z_size_t gzfwrite(voidpc buf, z_size_t size, z_size_t nitems, gzFile file);
extern int gzprintf(gzFile file, const char *format, ...);
extern int gzputs(gzFile file, const char *s);
extern char *gzgets(gzFile file, char *buf, int len);
extern int gzputc(gzFile file, int c);
extern int gzgetc(gzFile file);
extern int gzungetc(int c, gzFile file);
extern int gzflush(gzFile file, int flush);
extern int gzrewind(gzFile file);
extern int gzeof(gzFile file);
extern int gzdirect(gzFile file);
extern int gzclose(gzFile file);
extern int gzclose_r(gzFile file);
extern int gzclose_w(gzFile file);
extern const char *gzerror(gzFile file, int *errnum);
extern void gzclearerr(gzFile file);
extern uLong adler32(uLong adler, const Bytef *buf, uInt len);
extern uLong adler32_z(uLong adler, const Bytef *buf, z_size_t len);
extern uLong crc32(uLong crc, const Bytef *buf, uInt len);
extern uLong crc32_z(uLong crc, const Bytef *buf, z_size_t len);
extern uLong crc32_combine_op(uLong crc1, uLong crc2, uLong op);
extern int deflateInit_(z_streamp strm, int level, const char *version, int stream_size);
extern int inflateInit_(z_streamp strm, const char *version, int stream_size);
extern int deflateInit2_(z_streamp strm, int level, int method, int windowBits, int memLevel, int strategy, const char *version, int stream_size);
extern int inflateInit2_(z_streamp strm, int windowBits, const char *version, int stream_size);
extern int inflateBackInit_(z_streamp strm, int windowBits, unsigned char *window, const char *version, int stream_size);
struct gzFile_s
{
  unsigned have;
  unsigned char *next;
  off_t pos;
};
extern int gzgetc_(gzFile file);
extern gzFile gzopen(const char *, const char *);
extern off_t gzseek(gzFile, off_t, int);
extern off_t gztell(gzFile);
extern off_t gzoffset(gzFile);
extern uLong adler32_combine(uLong, uLong, off_t);
extern uLong crc32_combine(uLong, uLong, off_t);
extern uLong crc32_combine_gen(off_t);
extern const char *zError(int);
extern int inflateSyncPoint(z_streamp);
extern const z_crc_t *get_crc_table(void);
extern int inflateUndermine(z_streamp, int);
extern int inflateValidate(z_streamp, int);
extern unsigned long inflateCodesUsed(z_streamp);
extern int inflateResetKeep(z_streamp);
extern int deflateResetKeep(z_streamp);
extern int gzvprintf(gzFile file, const char *format, va_list va);
extern gzFile gzopen64(const char *, const char *);
extern off_t gzseek64(gzFile, off_t, int);
extern off_t gztell64(gzFile);
extern off_t gzoffset64(gzFile);
typedef struct 
{
  struct gzFile_s x;
  int mode;
  int fd;
  char *path;
  unsigned size;
  unsigned want;
  unsigned char *in;
  unsigned char *out;
  int direct;
  int how;
  off_t start;
  int eof;
  int past;
  int level;
  int strategy;
  int reset;
  off_t skip;
  int seek;
  int err;
  char *msg;
  z_stream strm;
} gz_state;
typedef gz_state *gz_statep;
void gz_error(gz_statep, int, const char *);
static int gz_load(gz_statep state, unsigned char *buf, unsigned len, unsigned *have)
{
  int ret;
  unsigned get;
  unsigned max = (((unsigned) (-1)) >> 2) + 1;
  *have = 0;
  do
  {
    get = len - (*have);
    if (get > max)
    {
      get = max;
    }
    ret = read(state->fd, buf + (*have), get);
    if (ret <= 0)
    {
      break;
    }
    *have += (unsigned) ret;
  }
  while ((*have) < len);
  if (ret < 0)
  {
    gz_error(state, -1, strerror(errno));
    return -1;
  }
  if (ret == 0)
  {
    state->eof = 1;
  }
  return 0;
}

static int gz_avail(gz_statep state)
{
  unsigned got;
  z_streamp strm = &state->strm;
  if ((state->err != 0) && (state->err != (-5)))
  {
    return -1;
  }
  if (state->eof == 0)
  {
    if (strm->avail_in)
    {
      unsigned char *p = state->in;
      unsigned int p_idx = 0;
      const unsigned char *q = strm->next_in;
      unsigned int q_idx = 0;
      unsigned n = strm->avail_in;
      do
      {
        p[p_idx] = q[q_idx];
        q_idx += 1;
        p_idx += 1;
      }
      while (--n);
    }
    if (gz_load(state, state->in + strm->avail_in, state->size - strm->avail_in, &got) == (-1))
    {
      return -1;
    }
    strm->avail_in += got;
    strm->next_in = state->in;
  }
  return 0;
}

static int gz_look(gz_statep state)
{
  z_streamp strm = &state->strm;
  if (state->size == 0)
  {
    state->in = (unsigned char *) malloc(state->want);
    state->out = (unsigned char *) malloc(state->want << 1);
    if ((state->in == 0) || (state->out == 0))
    {
      free(state->out);
      free(state->in);
      gz_error(state, -4, "out of memory");
      return -1;
    }
    state->size = state->want;
    state->strm.zalloc = 0;
    state->strm.zfree = 0;
    state->strm.opaque = 0;
    state->strm.avail_in = 0;
    state->strm.next_in = 0;
    if (inflateInit2_(&state->strm, 15 + 16, "1.3-optipng", (int) (sizeof(z_stream))) != 0)
    {
      free(state->out);
      free(state->in);
      state->size = 0;
      gz_error(state, -4, "out of memory");
      return -1;
    }
  }
  if (strm->avail_in < 2)
  {
    if (gz_avail(state) == (-1))
    {
      return -1;
    }
    if (strm->avail_in == 0)
    {
      return 0;
    }
  }
  if (((strm->avail_in > 1) && (strm->next_in[0] == 31)) && (strm->next_in[1] == 139))
  {
    inflateReset(strm);
    state->how = 2;
    state->direct = 0;
    return 0;
  }
  if (state->direct == 0)
  {
    strm->avail_in = 0;
    state->eof = 1;
    state->x.have = 0;
    return 0;
  }
  state->x.next = state->out;
  memcpy(state->x.next, strm->next_in, strm->avail_in);
  state->x.have = strm->avail_in;
  strm->avail_in = 0;
  state->how = 1;
  state->direct = 1;
  return 0;
}

static int gz_decomp(gz_statep state)
{
  int ret = 0;
  unsigned had;
  z_streamp strm = &state->strm;
  had = strm->avail_out;
  do
  {
    if ((strm->avail_in == 0) && (gz_avail(state) == (-1)))
    {
      return -1;
    }
    if (strm->avail_in == 0)
    {
      gz_error(state, -5, "unexpected end of file");
      break;
    }
    ret = inflate(strm, 0);
    if ((ret == (-2)) || (ret == 2))
    {
      gz_error(state, -2, "internal error: inflate stream corrupt");
      return -1;
    }
    if (ret == (-4))
    {
      gz_error(state, -4, "out of memory");
      return -1;
    }
    if (ret == (-3))
    {
      gz_error(state, -3, (strm->msg == 0) ? ("compressed data error") : (strm->msg));
      return -1;
    }
  }
  while (strm->avail_out && (ret != 1));
  state->x.have = had - strm->avail_out;
  state->x.next = strm->next_out - state->x.have;
  if (ret == 1)
  {
    state->how = 0;
  }
  return 0;
}

static int gz_fetch(gz_statep state)
{
  z_streamp strm = &state->strm;
  do
  {
    switch (state->how)
    {
      case 0:
        if (gz_look(state) == (-1))
      {
        return -1;
      }
        if (state->how == 0)
      {
        return 0;
      }
        break;

      case 1:
        if (gz_load(state, state->out, state->size << 1, &state->x.have) == (-1))
      {
        return -1;
      }
        state->x.next = state->out;
        return 0;

      case 2:
        strm->avail_out = state->size << 1;
        strm->next_out = state->out;
        if (gz_decomp(state) == (-1))
      {
        return -1;
      }

    }

  }
  while ((state->x.have == 0) && ((!state->eof) || strm->avail_in));
  return 0;
}

static int gz_skip(gz_statep state, off_t len)
{
  unsigned n;
  while (len)
  {
    if (state->x.have)
    {
      n = ((((sizeof(int)) == (sizeof(off_t))) && (state->x.have > 2147483647)) || (((off_t) state->x.have) > len)) ? ((unsigned) len) : (state->x.have);
      state->x.have -= n;
      state->x.next += n;
      state->x.pos += n;
      len -= n;
    }
    else
      if (state->eof && (state->strm.avail_in == 0))
    {
      break;
    }
    else
    {
      if (gz_fetch(state) == (-1))
      {
        return -1;
      }
    }
  }

  return 0;
}

static z_size_t gz_read(gz_statep state, voidp buf, z_size_t len)
{
  z_size_t got;
  unsigned n;
  if (len == 0)
  {
    return 0;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_skip(state, state->skip) == (-1))
    {
      return 0;
    }
  }
  got = 0;
  do
  {
    n = (unsigned) (-1);
    if (n > len)
    {
      n = (unsigned) len;
    }
    if (state->x.have)
    {
      if (state->x.have < n)
      {
        n = state->x.have;
      }
      memcpy(buf, state->x.next, n);
      state->x.next += n;
      state->x.have -= n;
    }
    else
      if (state->eof && (state->strm.avail_in == 0))
    {
      state->past = 1;
      break;
    }
    else
      if ((state->how == 0) || (n < (state->size << 1)))
    {
      if (gz_fetch(state) == (-1))
      {
        return 0;
      }
      continue;
    }
    else
      if (state->how == 1)
    {
      if (gz_load(state, (unsigned char *) buf, n, &n) == (-1))
      {
        return 0;
      }
    }
    else
    {
      state->strm.avail_out = n;
      state->strm.next_out = (unsigned char *) buf;
      if (gz_decomp(state) == (-1))
      {
        return 0;
      }
      n = state->x.have;
      state->x.have = 0;
    }
    len -= n;
    buf = ((char *) buf) + n;
    got += n;
    state->x.pos += n;
  }
  while (len);
  return got;
}

int gzread(gzFile file, voidp buf, unsigned len)
{
  gz_statep state;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) || ((state->err != 0) && (state->err != (-5))))
  {
    return -1;
  }
  if (((int) len) < 0)
  {
    gz_error(state, -2, "request does not fit in an int");
    return -1;
  }
  len = (unsigned) gz_read(state, buf, len);
  if (((len == 0) && (state->err != 0)) && (state->err != (-5)))
  {
    return -1;
  }
  return (int) len;
}

z_size_t gzfread(voidp buf, z_size_t size, z_size_t nitems, gzFile file)
{
  z_size_t len;
  gz_statep state;
  if (file == 0)
  {
    return 0;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) || ((state->err != 0) && (state->err != (-5))))
  {
    return 0;
  }
  len = nitems * size;
  if (size && ((len / size) != nitems))
  {
    gz_error(state, -2, "request does not fit in a size_t");
    return 0;
  }
  return (len) ? (gz_read(state, buf, len) / size) : (0);
}

int gzgetc(gzFile file)
{
  unsigned char buf[1];
  gz_statep state;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) || ((state->err != 0) && (state->err != (-5))))
  {
    return -1;
  }
  if (state->x.have)
  {
    state->x.have -= 1;
    state->x.pos += 1;
    return *(state->x.next++);
  }
  return (gz_read(state, buf, 1) < 1) ? (-1) : (buf[0]);
}

int gzgetc_(gzFile file)
{
  return gzgetc(file);
}

int gzungetc(int c, gzFile file)
{
  gz_statep state;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  if (((state->mode == 7247) && (state->how == 0)) && (state->x.have == 0))
  {
    (void) gz_look(state);
  }
  if ((state->mode != 7247) || ((state->err != 0) && (state->err != (-5))))
  {
    return -1;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_skip(state, state->skip) == (-1))
    {
      return -1;
    }
  }
  if (c < 0)
  {
    return -1;
  }
  if (state->x.have == 0)
  {
    state->x.have = 1;
    state->x.next = (state->out + (state->size << 1)) - 1;
    state->x.next[0] = (unsigned char) c;
    state->x.pos -= 1;
    state->past = 0;
    return c;
  }
  if (state->x.have == (state->size << 1))
  {
    gz_error(state, -3, "out of room to push characters");
    return -1;
  }
  if (state->x.next == state->out)
  {
    unsigned char *src = state->out + state->x.have;
    unsigned int src_idx = 0;
    unsigned char *dest = state->out + (state->size << 1);
    unsigned int dest_idx = 0;
    while ((&src[src_idx]) > state->out)
    {
      src_idx -= 1;
      dest_idx -= 1;
      dest[dest_idx] = src[src_idx];
    }

    state->x.next = &dest[dest_idx];
  }
  state->x.have += 1;
  state->x.next -= 1;
  state->x.next[0] = (unsigned char) c;
  state->x.pos -= 1;
  state->past = 0;
  return c;
}

char *gzgets(gzFile file, char *buf, int len)
{
  unsigned int buf_idx = 0;
  unsigned left;
  unsigned n;
  char *str;
  unsigned int str_idx = 0;
  unsigned char *eol;
  unsigned int eol_idx = 0;
  gz_statep state;
  if (((file == 0) || ((&buf[buf_idx]) == 0)) || (len < 1))
  {
    return 0;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) || ((state->err != 0) && (state->err != (-5))))
  {
    return 0;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_skip(state, state->skip) == (-1))
    {
      return 0;
    }
  }
  str_idx = &buf[buf_idx];
  left = ((unsigned) len) - 1;
  if (left)
  {
    do
    {
      if ((state->x.have == 0) && (gz_fetch(state) == (-1)))
      {
        return 0;
      }
      if (state->x.have == 0)
      {
        state->past = 1;
        break;
      }
      n = (state->x.have > left) ? (left) : (state->x.have);
      eol_idx = (unsigned char *) memchr(state->x.next, '\n', n);
      if ((&eol[eol_idx]) != 0)
      {
        n = ((unsigned) ((&eol[eol_idx]) - state->x.next)) + 1;
      }
      memcpy(buf, state->x.next, n);
      state->x.have -= n;
      state->x.next += n;
      state->x.pos += n;
      left -= n;
      buf_idx += n;
    }
    while (left && ((&eol[eol_idx]) == 0));
  }
  if ((&buf[buf_idx]) == (&str[str_idx]))
  {
    return 0;
  }
  buf[0 + buf_idx] = 0;
  return str;
}

int gzdirect(gzFile file)
{
  gz_statep state;
  if (file == 0)
  {
    return 0;
  }
  state = (gz_statep) file;
  if (((state->mode == 7247) && (state->how == 0)) && (state->x.have == 0))
  {
    (void) gz_look(state);
  }
  return state->direct;
}

int gzclose_r(gzFile file)
{
  int ret;
  int err;
  gz_statep state;
  if (file == 0)
  {
    return -2;
  }
  state = (gz_statep) file;
  if (state->mode != 7247)
  {
    return -2;
  }
  if (state->size)
  {
    inflateEnd(&state->strm);
    free(state->out);
    free(state->in);
  }
  err = (state->err == (-5)) ? (-5) : (0);
  gz_error(state, 0, 0);
  free(state->path);
  ret = close(state->fd);
  free(state);
  return (ret) ? (-1) : (err);
}

int helper_gz_look_1(gz_statep * const state_ref)
{
  gz_statep state = *state_ref;
  state->in = (unsigned char *) malloc(state->want);
  state->out = (unsigned char *) malloc(state->want << 1);
  if ((state->in == 0) || (state->out == 0))
  {
    free(state->out);
    free(state->in);
    gz_error(state, -4, "out of memory");
    return -1;
  }
  state->size = state->want;
  state->strm.zalloc = 0;
  state->strm.zfree = 0;
  state->strm.opaque = 0;
  state->strm.avail_in = 0;
  state->strm.next_in = 0;
  if (inflateInit2_(&state->strm, 15 + 16, "1.3-optipng", (int) (sizeof(z_stream))) != 0)
  {
    free(state->out);
    free(state->in);
    state->size = 0;
    gz_error(state, -4, "out of memory");
    return -1;
  }
  *state_ref = state;
}

z_size_t helper_gz_read_1(gz_statep * const state_ref, voidp * const buf_ref, z_size_t * const len_ref, z_size_t * const got_ref, unsigned * const n_ref)
{
  gz_statep state = *state_ref;
  voidp buf = *buf_ref;
  z_size_t len = *len_ref;
  z_size_t got = *got_ref;
  unsigned n = *n_ref;
  n = (unsigned) (-1);
  if (n > len)
  {
    n = (unsigned) len;
  }
  if (state->x.have)
  {
    if (state->x.have < n)
    {
      n = state->x.have;
    }
    memcpy(buf, state->x.next, n);
    state->x.next += n;
    state->x.have -= n;
  }
  else
    if (state->eof && (state->strm.avail_in == 0))
  {
    state->past = 1;
    break;
  }
  else
    if ((state->how == 0) || (n < (state->size << 1)))
  {
    if (gz_fetch(state) == (-1))
    {
      return 0;
    }
    continue;
  }
  else
    if (state->how == 1)
  {
    if (gz_load(state, (unsigned char *) buf, n, &n) == (-1))
    {
      return 0;
    }
  }
  else
  {
    state->strm.avail_out = n;
    state->strm.next_out = (unsigned char *) buf;
    if (gz_decomp(state) == (-1))
    {
      return 0;
    }
    n = state->x.have;
    state->x.have = 0;
  }
  len -= n;
  buf = ((char *) buf) + n;
  got += n;
  state->x.pos += n;
  *state_ref = state;
  *buf_ref = buf;
  *len_ref = len;
  *got_ref = got;
  *n_ref = n;
}

char *helper_gzgets_1(unsigned int * const buf_idx_ref, unsigned * const left_ref, unsigned * const n_ref, unsigned int * const eol_idx_ref, gz_statep * const state_ref, char * const buf, unsigned char * const eol)
{
  unsigned int buf_idx = *buf_idx_ref;
  unsigned left = *left_ref;
  unsigned n = *n_ref;
  unsigned int eol_idx = *eol_idx_ref;
  gz_statep state = *state_ref;
  do
  {
    if ((state->x.have == 0) && (gz_fetch(state) == (-1)))
    {
      return 0;
    }
    if (state->x.have == 0)
    {
      state->past = 1;
      break;
    }
    n = (state->x.have > left) ? (left) : (state->x.have);
    eol_idx = (unsigned char *) memchr(state->x.next, '\n', n);
    if ((&eol[eol_idx]) != 0)
    {
      n = ((unsigned) ((&eol[eol_idx]) - state->x.next)) + 1;
    }
    memcpy(buf, state->x.next, n);
    state->x.have -= n;
    state->x.next += n;
    state->x.pos += n;
    left -= n;
    buf_idx += n;
  }
  while (left && ((&eol[eol_idx]) == 0));
  *buf_idx_ref = buf_idx;
  *left_ref = left;
  *n_ref = n;
  *eol_idx_ref = eol_idx;
  *state_ref = state;
}

