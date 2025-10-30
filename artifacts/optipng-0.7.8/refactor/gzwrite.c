#include <errno.h>
#include <fcntl.h>
#include <gzguts.h>
#include <gzwrite.c>
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
static int gz_init(gz_statep state)
{
  int ret;
  z_streamp strm = &state->strm;
  state->in = (unsigned char *) malloc(state->want << 1);
  if (state->in == 0)
  {
    gz_error(state, -4, "out of memory");
    return -1;
  }
  if (!state->direct)
  {
    state->out = (unsigned char *) malloc(state->want);
    if (state->out == 0)
    {
      free(state->in);
      gz_error(state, -4, "out of memory");
      return -1;
    }
    strm->zalloc = 0;
    strm->zfree = 0;
    strm->opaque = 0;
    ret = deflateInit2_(strm, state->level, 8, 15 + 16, 8, state->strategy, "1.3-optipng", (int) (sizeof(z_stream)));
    if (ret != 0)
    {
      free(state->out);
      free(state->in);
      gz_error(state, -4, "out of memory");
      return -1;
    }
    strm->next_in = 0;
  }
  state->size = state->want;
  if (!state->direct)
  {
    strm->avail_out = state->size;
    strm->next_out = state->out;
    state->x.next = strm->next_out;
  }
  return 0;
}

static int gz_comp(gz_statep state, int flush)
{
  int ret;
  int writ;
  unsigned have;
  unsigned put;
  unsigned max = (((unsigned) (-1)) >> 2) + 1;
  z_streamp strm = &state->strm;
  if ((state->size == 0) && (gz_init(state) == (-1)))
  {
    return -1;
  }
  if (state->direct)
  {
    while (strm->avail_in)
    {
      put = (strm->avail_in > max) ? (max) : (strm->avail_in);
      writ = write(state->fd, strm->next_in, put);
      if (writ < 0)
      {
        gz_error(state, -1, strerror(errno));
        return -1;
      }
      strm->avail_in -= (unsigned) writ;
      strm->next_in += writ;
    }

    return 0;
  }
  if (state->reset)
  {
    if (strm->avail_in == 0)
    {
      return 0;
    }
    deflateReset(strm);
    state->reset = 0;
  }
  ret = 0;
  do
  {
    helper_gz_comp_1(&state, &ret, &writ, &have, &put, &strm, flush, max);
  }
  while (have);
  if (flush == 4)
  {
    state->reset = 1;
  }
  return 0;
}

static int gz_zero(gz_statep state, off_t len)
{
  int first;
  unsigned n;
  z_streamp strm = &state->strm;
  if (strm->avail_in && (gz_comp(state, 0) == (-1)))
  {
    return -1;
  }
  first = 1;
  while (len)
  {
    n = ((((sizeof(int)) == (sizeof(off_t))) && (state->size > 2147483647)) || (((off_t) state->size) > len)) ? ((unsigned) len) : (state->size);
    if (first)
    {
      memset(state->in, 0, n);
      first = 0;
    }
    strm->avail_in = n;
    strm->next_in = state->in;
    state->x.pos += n;
    if (gz_comp(state, 0) == (-1))
    {
      return -1;
    }
    len -= n;
  }

  return 0;
}

static z_size_t gz_write(gz_statep state, voidpc buf, z_size_t len)
{
  z_size_t put = len;
  if (len == 0)
  {
    return 0;
  }
  if ((state->size == 0) && (gz_init(state) == (-1)))
  {
    return 0;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_zero(state, state->skip) == (-1))
    {
      return 0;
    }
  }
  if (len < state->size)
  {
    helper_gz_write_2(&state, &buf, &len);
  }
  else
  {
    helper_gz_write_1(&state, &len, buf);
  }
  return put;
}

int gzwrite(gzFile file, voidpc buf, unsigned len)
{
  gz_statep state;
  if (file == 0)
  {
    return 0;
  }
  state = (gz_statep) file;
  if ((state->mode != 31153) || (state->err != 0))
  {
    return 0;
  }
  if (((int) len) < 0)
  {
    gz_error(state, -3, "requested length does not fit in int");
    return 0;
  }
  return (int) gz_write(state, buf, len);
}

z_size_t gzfwrite(voidpc buf, z_size_t size, z_size_t nitems, gzFile file)
{
  z_size_t len;
  gz_statep state;
  if (file == 0)
  {
    return 0;
  }
  state = (gz_statep) file;
  if ((state->mode != 31153) || (state->err != 0))
  {
    return 0;
  }
  len = nitems * size;
  if (size && ((len / size) != nitems))
  {
    gz_error(state, -2, "request does not fit in a size_t");
    return 0;
  }
  return (len) ? (gz_write(state, buf, len) / size) : (0);
}

int gzputc(gzFile file, int c)
{
  unsigned have;
  unsigned char buf[1];
  gz_statep state;
  z_streamp strm;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  strm = &state->strm;
  if ((state->mode != 31153) || (state->err != 0))
  {
    return -1;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_zero(state, state->skip) == (-1))
    {
      return -1;
    }
  }
  if (state->size)
  {
    if (strm->avail_in == 0)
    {
      strm->next_in = state->in;
    }
    have = (unsigned) ((strm->next_in + strm->avail_in) - state->in);
    if (have < state->size)
    {
      state->in[have] = (unsigned char) c;
      strm->avail_in += 1;
      state->x.pos += 1;
      return c & 0xff;
    }
  }
  buf[0] = (unsigned char) c;
  if (gz_write(state, buf, 1) != 1)
  {
    return -1;
  }
  return c & 0xff;
}

int gzputs(gzFile file, const char *s)
{
  z_size_t len;
  z_size_t put;
  gz_statep state;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  if ((state->mode != 31153) || (state->err != 0))
  {
    return -1;
  }
  len = strlen(s);
  if ((((int) len) < 0) || (((unsigned) len) != len))
  {
    gz_error(state, -2, "string length does not fit in int");
    return -1;
  }
  put = gz_write(state, s, len);
  return (put < len) ? (-1) : ((int) len);
}

int gzvprintf(gzFile file, const char *format, va_list va)
{
  int len;
  unsigned left;
  char *next;
  unsigned int next_idx = 0;
  gz_statep state;
  z_streamp strm;
  if (file == 0)
  {
    return -2;
  }
  state = (gz_statep) file;
  strm = &state->strm;
  if ((state->mode != 31153) || (state->err != 0))
  {
    return -2;
  }
  if ((state->size == 0) && (gz_init(state) == (-1)))
  {
    return state->err;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_zero(state, state->skip) == (-1))
    {
      return state->err;
    }
  }
  if (strm->avail_in == 0)
  {
    strm->next_in = state->in;
  }
  next_idx = (char *) ((state->in + (strm->next_in - state->in)) + strm->avail_in);
  next[(state->size - 1) + next_idx] = 0;
  len = vsnprintf(next, state->size, format, va);
  if (((len == 0) || (((unsigned) len) >= state->size)) || (next[(state->size - 1) + next_idx] != 0))
  {
    return 0;
  }
  strm->avail_in += (unsigned) len;
  state->x.pos += len;
  if (strm->avail_in >= state->size)
  {
    left = strm->avail_in - state->size;
    strm->avail_in = state->size;
    if (gz_comp(state, 0) == (-1))
    {
      return state->err;
    }
    memmove(state->in, state->in + state->size, left);
    strm->next_in = state->in;
    strm->avail_in = left;
  }
  return len;
}

int gzprintf(gzFile file, const char *format, ...)
{
  va_list va;
  int ret;
  __builtin_va_start(va);
  ret = gzvprintf(file, format, va);
  ;
  return ret;
}

int gzflush(gzFile file, int flush)
{
  gz_statep state;
  if (file == 0)
  {
    return -2;
  }
  state = (gz_statep) file;
  if ((state->mode != 31153) || (state->err != 0))
  {
    return -2;
  }
  if ((flush < 0) || (flush > 4))
  {
    return -2;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_zero(state, state->skip) == (-1))
    {
      return state->err;
    }
  }
  (void) gz_comp(state, flush);
  return state->err;
}

int gzsetparams(gzFile file, int level, int strategy)
{
  gz_statep state;
  z_streamp strm;
  if (file == 0)
  {
    return -2;
  }
  state = (gz_statep) file;
  strm = &state->strm;
  if (((state->mode != 31153) || (state->err != 0)) || state->direct)
  {
    return -2;
  }
  if ((level == state->level) && (strategy == state->strategy))
  {
    return 0;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_zero(state, state->skip) == (-1))
    {
      return state->err;
    }
  }
  if (state->size)
  {
    if (strm->avail_in && (gz_comp(state, 5) == (-1)))
    {
      return state->err;
    }
    deflateParams(strm, level, strategy);
  }
  state->level = level;
  state->strategy = strategy;
  return 0;
}

int gzclose_w(gzFile file)
{
  int ret = 0;
  gz_statep state;
  if (file == 0)
  {
    return -2;
  }
  state = (gz_statep) file;
  if (state->mode != 31153)
  {
    return -2;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_zero(state, state->skip) == (-1))
    {
      ret = state->err;
    }
  }
  if (gz_comp(state, 4) == (-1))
  {
    ret = state->err;
  }
  if (state->size)
  {
    if (!state->direct)
    {
      (void) deflateEnd(&state->strm);
      free(state->out);
    }
    free(state->in);
  }
  gz_error(state, 0, 0);
  free(state->path);
  if (close(state->fd) == (-1))
  {
    ret = -1;
  }
  free(state);
  return ret;
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
static int gz_init(gz_statep state)
{
  int ret;
  z_streamp strm = &state->strm;
  state->in = (unsigned char *) malloc(state->want << 1);
  if (state->in == 0)
  {
    gz_error(state, -4, "out of memory");
    return -1;
  }
  if (!state->direct)
  {
    state->out = (unsigned char *) malloc(state->want);
    if (state->out == 0)
    {
      free(state->in);
      gz_error(state, -4, "out of memory");
      return -1;
    }
    strm->zalloc = 0;
    strm->zfree = 0;
    strm->opaque = 0;
    ret = deflateInit2_(strm, state->level, 8, 15 + 16, 8, state->strategy, "1.3-optipng", (int) (sizeof(z_stream)));
    if (ret != 0)
    {
      free(state->out);
      free(state->in);
      gz_error(state, -4, "out of memory");
      return -1;
    }
    strm->next_in = 0;
  }
  state->size = state->want;
  if (!state->direct)
  {
    strm->avail_out = state->size;
    strm->next_out = state->out;
    state->x.next = strm->next_out;
  }
  return 0;
}

static int gz_comp(gz_statep state, int flush)
{
  int ret;
  int writ;
  unsigned have;
  unsigned put;
  unsigned max = (((unsigned) (-1)) >> 2) + 1;
  z_streamp strm = &state->strm;
  if ((state->size == 0) && (gz_init(state) == (-1)))
  {
    return -1;
  }
  if (state->direct)
  {
    while (strm->avail_in)
    {
      put = (strm->avail_in > max) ? (max) : (strm->avail_in);
      writ = write(state->fd, strm->next_in, put);
      if (writ < 0)
      {
        gz_error(state, -1, strerror(errno));
        return -1;
      }
      strm->avail_in -= (unsigned) writ;
      strm->next_in += writ;
    }

    return 0;
  }
  if (state->reset)
  {
    if (strm->avail_in == 0)
    {
      return 0;
    }
    deflateReset(strm);
    state->reset = 0;
  }
  ret = 0;
  do
  {
    if ((strm->avail_out == 0) || ((flush != 0) && ((flush != 4) || (ret == 1))))
    {
      while (strm->next_out > state->x.next)
      {
        put = ((strm->next_out - state->x.next) > ((int) max)) ? (max) : ((unsigned) (strm->next_out - state->x.next));
        writ = write(state->fd, state->x.next, put);
        if (writ < 0)
        {
          gz_error(state, -1, strerror(errno));
          return -1;
        }
        state->x.next += writ;
      }

      if (strm->avail_out == 0)
      {
        strm->avail_out = state->size;
        strm->next_out = state->out;
        state->x.next = state->out;
      }
    }
    have = strm->avail_out;
    ret = deflate(strm, flush);
    if (ret == (-2))
    {
      gz_error(state, -2, "internal error: deflate stream corrupt");
      return -1;
    }
    have -= strm->avail_out;
  }
  while (have);
  if (flush == 4)
  {
    state->reset = 1;
  }
  return 0;
}

static int gz_zero(gz_statep state, off_t len)
{
  int first;
  unsigned n;
  z_streamp strm = &state->strm;
  if (strm->avail_in && (gz_comp(state, 0) == (-1)))
  {
    return -1;
  }
  first = 1;
  while (len)
  {
    n = ((((sizeof(int)) == (sizeof(off_t))) && (state->size > 2147483647)) || (((off_t) state->size) > len)) ? ((unsigned) len) : (state->size);
    if (first)
    {
      memset(state->in, 0, n);
      first = 0;
    }
    strm->avail_in = n;
    strm->next_in = state->in;
    state->x.pos += n;
    if (gz_comp(state, 0) == (-1))
    {
      return -1;
    }
    len -= n;
  }

  return 0;
}

static z_size_t gz_write(gz_statep state, voidpc buf, z_size_t len)
{
  z_size_t put = len;
  if (len == 0)
  {
    return 0;
  }
  if ((state->size == 0) && (gz_init(state) == (-1)))
  {
    return 0;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_zero(state, state->skip) == (-1))
    {
      return 0;
    }
  }
  if (len < state->size)
  {
    do
    {
      unsigned have;
      unsigned copy;
      if (state->strm.avail_in == 0)
      {
        state->strm.next_in = state->in;
      }
      have = (unsigned) ((state->strm.next_in + state->strm.avail_in) - state->in);
      copy = state->size - have;
      if (copy > len)
      {
        copy = (unsigned) len;
      }
      memcpy(state->in + have, buf, copy);
      state->strm.avail_in += copy;
      state->x.pos += copy;
      buf = ((const char *) buf) + copy;
      len -= copy;
      if (len && (gz_comp(state, 0) == (-1)))
      {
        return 0;
      }
    }
    while (len);
  }
  else
  {
    if (state->strm.avail_in && (gz_comp(state, 0) == (-1)))
    {
      return 0;
    }
    state->strm.next_in = (Bytef *) buf;
    do
    {
      unsigned n = (unsigned) (-1);
      if (n > len)
      {
        n = (unsigned) len;
      }
      state->strm.avail_in = n;
      state->x.pos += n;
      if (gz_comp(state, 0) == (-1))
      {
        return 0;
      }
      len -= n;
    }
    while (len);
  }
  return put;
}

int gzwrite(gzFile file, voidpc buf, unsigned len)
{
  gz_statep state;
  if (file == 0)
  {
    return 0;
  }
  state = (gz_statep) file;
  if ((state->mode != 31153) || (state->err != 0))
  {
    return 0;
  }
  if (((int) len) < 0)
  {
    gz_error(state, -3, "requested length does not fit in int");
    return 0;
  }
  return (int) gz_write(state, buf, len);
}

z_size_t gzfwrite(voidpc buf, z_size_t size, z_size_t nitems, gzFile file)
{
  z_size_t len;
  gz_statep state;
  if (file == 0)
  {
    return 0;
  }
  state = (gz_statep) file;
  if ((state->mode != 31153) || (state->err != 0))
  {
    return 0;
  }
  len = nitems * size;
  if (size && ((len / size) != nitems))
  {
    gz_error(state, -2, "request does not fit in a size_t");
    return 0;
  }
  return (len) ? (gz_write(state, buf, len) / size) : (0);
}

int gzputc(gzFile file, int c)
{
  unsigned have;
  unsigned char buf[1];
  gz_statep state;
  z_streamp strm;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  strm = &state->strm;
  if ((state->mode != 31153) || (state->err != 0))
  {
    return -1;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_zero(state, state->skip) == (-1))
    {
      return -1;
    }
  }
  if (state->size)
  {
    if (strm->avail_in == 0)
    {
      strm->next_in = state->in;
    }
    have = (unsigned) ((strm->next_in + strm->avail_in) - state->in);
    if (have < state->size)
    {
      state->in[have] = (unsigned char) c;
      strm->avail_in += 1;
      state->x.pos += 1;
      return c & 0xff;
    }
  }
  buf[0] = (unsigned char) c;
  if (gz_write(state, buf, 1) != 1)
  {
    return -1;
  }
  return c & 0xff;
}

int gzputs(gzFile file, const char *s)
{
  z_size_t len;
  z_size_t put;
  gz_statep state;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  if ((state->mode != 31153) || (state->err != 0))
  {
    return -1;
  }
  len = strlen(s);
  if ((((int) len) < 0) || (((unsigned) len) != len))
  {
    gz_error(state, -2, "string length does not fit in int");
    return -1;
  }
  put = gz_write(state, s, len);
  return (put < len) ? (-1) : ((int) len);
}

int gzvprintf(gzFile file, const char *format, va_list va)
{
  int len;
  unsigned left;
  char *next;
  unsigned int next_idx = 0;
  gz_statep state;
  z_streamp strm;
  if (file == 0)
  {
    return -2;
  }
  state = (gz_statep) file;
  strm = &state->strm;
  if ((state->mode != 31153) || (state->err != 0))
  {
    return -2;
  }
  if ((state->size == 0) && (gz_init(state) == (-1)))
  {
    return state->err;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_zero(state, state->skip) == (-1))
    {
      return state->err;
    }
  }
  if (strm->avail_in == 0)
  {
    strm->next_in = state->in;
  }
  next_idx = (char *) ((state->in + (strm->next_in - state->in)) + strm->avail_in);
  next[(state->size - 1) + next_idx] = 0;
  len = vsnprintf(next, state->size, format, va);
  if (((len == 0) || (((unsigned) len) >= state->size)) || (next[(state->size - 1) + next_idx] != 0))
  {
    return 0;
  }
  strm->avail_in += (unsigned) len;
  state->x.pos += len;
  if (strm->avail_in >= state->size)
  {
    left = strm->avail_in - state->size;
    strm->avail_in = state->size;
    if (gz_comp(state, 0) == (-1))
    {
      return state->err;
    }
    memmove(state->in, state->in + state->size, left);
    strm->next_in = state->in;
    strm->avail_in = left;
  }
  return len;
}

int gzprintf(gzFile file, const char *format, ...)
{
  va_list va;
  int ret;
  __builtin_va_start(va);
  ret = gzvprintf(file, format, va);
  ;
  return ret;
}

int gzflush(gzFile file, int flush)
{
  gz_statep state;
  if (file == 0)
  {
    return -2;
  }
  state = (gz_statep) file;
  if ((state->mode != 31153) || (state->err != 0))
  {
    return -2;
  }
  if ((flush < 0) || (flush > 4))
  {
    return -2;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_zero(state, state->skip) == (-1))
    {
      return state->err;
    }
  }
  (void) gz_comp(state, flush);
  return state->err;
}

int gzsetparams(gzFile file, int level, int strategy)
{
  gz_statep state;
  z_streamp strm;
  if (file == 0)
  {
    return -2;
  }
  state = (gz_statep) file;
  strm = &state->strm;
  if (((state->mode != 31153) || (state->err != 0)) || state->direct)
  {
    return -2;
  }
  if ((level == state->level) && (strategy == state->strategy))
  {
    return 0;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_zero(state, state->skip) == (-1))
    {
      return state->err;
    }
  }
  if (state->size)
  {
    if (strm->avail_in && (gz_comp(state, 5) == (-1)))
    {
      return state->err;
    }
    deflateParams(strm, level, strategy);
  }
  state->level = level;
  state->strategy = strategy;
  return 0;
}

int gzclose_w(gzFile file)
{
  int ret = 0;
  gz_statep state;
  if (file == 0)
  {
    return -2;
  }
  state = (gz_statep) file;
  if (state->mode != 31153)
  {
    return -2;
  }
  if (state->seek)
  {
    state->seek = 0;
    if (gz_zero(state, state->skip) == (-1))
    {
      ret = state->err;
    }
  }
  if (gz_comp(state, 4) == (-1))
  {
    ret = state->err;
  }
  if (state->size)
  {
    if (!state->direct)
    {
      (void) deflateEnd(&state->strm);
      free(state->out);
    }
    free(state->in);
  }
  gz_error(state, 0, 0);
  free(state->path);
  if (close(state->fd) == (-1))
  {
    ret = -1;
  }
  free(state);
  return ret;
}

int helper_gz_comp_1(gz_statep * const state_ref, int * const ret_ref, int * const writ_ref, unsigned * const have_ref, unsigned * const put_ref, z_streamp * const strm_ref, int flush, unsigned max)
{
  gz_statep state = *state_ref;
  int ret = *ret_ref;
  int writ = *writ_ref;
  unsigned have = *have_ref;
  unsigned put = *put_ref;
  z_streamp strm = *strm_ref;
  if ((strm->avail_out == 0) || ((flush != 0) && ((flush != 4) || (ret == 1))))
  {
    while (strm->next_out > state->x.next)
    {
      put = ((strm->next_out - state->x.next) > ((int) max)) ? (max) : ((unsigned) (strm->next_out - state->x.next));
      writ = write(state->fd, state->x.next, put);
      if (writ < 0)
      {
        gz_error(state, -1, strerror(errno));
        return -1;
      }
      state->x.next += writ;
    }

    if (strm->avail_out == 0)
    {
      strm->avail_out = state->size;
      strm->next_out = state->out;
      state->x.next = state->out;
    }
  }
  have = strm->avail_out;
  ret = deflate(strm, flush);
  if (ret == (-2))
  {
    gz_error(state, -2, "internal error: deflate stream corrupt");
    return -1;
  }
  have -= strm->avail_out;
  *state_ref = state;
  *ret_ref = ret;
  *writ_ref = writ;
  *have_ref = have;
  *put_ref = put;
  *strm_ref = strm;
}

z_size_t helper_gz_write_1(gz_statep * const state_ref, z_size_t * const len_ref, voidpc buf)
{
  gz_statep state = *state_ref;
  z_size_t len = *len_ref;
  if (state->strm.avail_in && (gz_comp(state, 0) == (-1)))
  {
    return 0;
  }
  state->strm.next_in = (Bytef *) buf;
  do
  {
    unsigned n = (unsigned) (-1);
    if (n > len)
    {
      n = (unsigned) len;
    }
    state->strm.avail_in = n;
    state->x.pos += n;
    if (gz_comp(state, 0) == (-1))
    {
      return 0;
    }
    len -= n;
  }
  while (len);
  *state_ref = state;
  *len_ref = len;
}

z_size_t helper_gz_write_2(gz_statep * const state_ref, voidpc * const buf_ref, z_size_t * const len_ref)
{
  gz_statep state = *state_ref;
  voidpc buf = *buf_ref;
  z_size_t len = *len_ref;
  do
  {
    unsigned have;
    unsigned copy;
    if (state->strm.avail_in == 0)
    {
      state->strm.next_in = state->in;
    }
    have = (unsigned) ((state->strm.next_in + state->strm.avail_in) - state->in);
    copy = state->size - have;
    if (copy > len)
    {
      copy = (unsigned) len;
    }
    memcpy(state->in + have, buf, copy);
    state->strm.avail_in += copy;
    state->x.pos += copy;
    buf = ((const char *) buf) + copy;
    len -= copy;
    if (len && (gz_comp(state, 0) == (-1)))
    {
      return 0;
    }
  }
  while (len);
  *state_ref = state;
  *buf_ref = buf;
  *len_ref = len;
}

