#include <errno.h>
#include <fcntl.h>
#include <gzguts.h>
#include <gzlib.c>
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
static void gz_reset(gz_statep state)
{
  state->x.have = 0;
  if (state->mode == 7247)
  {
    state->eof = 0;
    state->past = 0;
    state->how = 0;
  }
  else
    state->reset = 0;
  state->seek = 0;
  gz_error(state, 0, 0);
  state->x.pos = 0;
  state->strm.avail_in = 0;
}

static gzFile gz_open(const void *path, int fd, const char *mode)
{
  unsigned int mode_idx = 0;
  gz_statep state;
  z_size_t len;
  int oflag;
  if (path == 0)
  {
    return 0;
  }
  state = (gz_statep) malloc(sizeof(gz_state));
  if (state == 0)
  {
    return 0;
  }
  state->size = 0;
  state->want = 8192;
  state->msg = 0;
  state->mode = 0;
  state->level = -1;
  state->strategy = 0;
  state->direct = 0;
  while (mode[mode_idx])
  {
    helper_gz_open_1(&mode_idx, &state, mode);
  }

  if (state->mode == 0)
  {
    free(state);
    return 0;
  }
  if (state->mode == 7247)
  {
    if (state->direct)
    {
      free(state);
      return 0;
    }
    state->direct = 1;
  }
  len = strlen((const char *) path);
  state->path = (char *) malloc(len + 1);
  if (state->path == 0)
  {
    free(state);
    return 0;
  }
  (void) snprintf(state->path, len + 1, "%s", (const char *) path);
  oflag = (state->mode == 7247) ? (O_RDONLY) : ((O_WRONLY | O_CREAT) | ((state->mode == 31153) ? (O_TRUNC) : (O_APPEND)));
  state->fd = (fd > (-1)) ? (fd) : (open((const char *) path, oflag, 0666));
  if (state->fd == (-1))
  {
    free(state->path);
    free(state);
    return 0;
  }
  if (state->mode == 1)
  {
    lseek(state->fd, 0, 2);
    state->mode = 31153;
  }
  if (state->mode == 7247)
  {
    state->start = lseek(state->fd, 0, 1);
    if (state->start == (-1))
    {
      state->start = 0;
    }
  }
  gz_reset(state);
  return (gzFile) state;
}

gzFile gzopen(const char *path, const char *mode)
{
  return gz_open(path, -1, mode);
}

gzFile gzopen64(const char *path, const char *mode)
{
  return gz_open(path, -1, mode);
}

gzFile gzdopen(int fd, const char *mode)
{
  char *path;
  unsigned int path_idx = 0;
  gzFile gz;
  if ((fd == (-1)) || ((path_idx = (char *) malloc(7 + (3 * (sizeof(int))))) == 0))
  {
    return 0;
  }
  (void) snprintf(path, 7 + (3 * (sizeof(int))), "<fd:%d>", fd);
  gz = gz_open(path, fd, mode);
  free(path);
  return gz;
}

int gzbuffer(gzFile file, unsigned size)
{
  gz_statep state;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) && (state->mode != 31153))
  {
    return -1;
  }
  if (state->size != 0)
  {
    return -1;
  }
  if ((size << 1) < size)
  {
    return -1;
  }
  if (size < 8)
  {
    size = 8;
  }
  state->want = size;
  return 0;
}

int gzrewind(gzFile file)
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
  if (lseek(state->fd, state->start, 0) == (-1))
  {
    return -1;
  }
  gz_reset(state);
  return 0;
}

off_t gzseek64(gzFile file, off_t offset, int whence)
{
  unsigned n;
  off_t ret;
  gz_statep state;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) && (state->mode != 31153))
  {
    return -1;
  }
  if ((state->err != 0) && (state->err != (-5)))
  {
    return -1;
  }
  if ((whence != 0) && (whence != 1))
  {
    return -1;
  }
  if (whence == 0)
  {
    offset -= state->x.pos;
  }
  else
    if (state->seek)
  {
    offset += state->skip;
  }
  state->seek = 0;
  if (((state->mode == 7247) && (state->how == 1)) && ((state->x.pos + offset) >= 0))
  {
    helper_gzseek64_1(&ret, &state, offset);
  }
  if (offset < 0)
  {
    if (state->mode != 7247)
    {
      return -1;
    }
    offset += state->x.pos;
    if (offset < 0)
    {
      return -1;
    }
    if (gzrewind(file) == (-1))
    {
      return -1;
    }
  }
  if (state->mode == 7247)
  {
    n = ((((sizeof(int)) == (sizeof(off_t))) && (state->x.have > 2147483647)) || (((off_t) state->x.have) > offset)) ? ((unsigned) offset) : (state->x.have);
    state->x.have -= n;
    state->x.next += n;
    state->x.pos += n;
    offset -= n;
  }
  if (offset)
  {
    state->seek = 1;
    state->skip = offset;
  }
  return state->x.pos + offset;
}

off_t gzseek(gzFile file, off_t offset, int whence)
{
  off_t ret;
  ret = gzseek64(file, (off_t) offset, whence);
  return (ret == ((off_t) ret)) ? ((off_t) ret) : (-1);
}

off_t gztell64(gzFile file)
{
  gz_statep state;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) && (state->mode != 31153))
  {
    return -1;
  }
  return state->x.pos + ((state->seek) ? (state->skip) : (0));
}

off_t gztell(gzFile file)
{
  off_t ret;
  ret = gztell64(file);
  return (ret == ((off_t) ret)) ? ((off_t) ret) : (-1);
}

off_t gzoffset64(gzFile file)
{
  off_t offset;
  gz_statep state;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) && (state->mode != 31153))
  {
    return -1;
  }
  offset = lseek(state->fd, 0, 1);
  if (offset == (-1))
  {
    return -1;
  }
  if (state->mode == 7247)
  {
    offset -= state->strm.avail_in;
  }
  return offset;
}

off_t gzoffset(gzFile file)
{
  off_t ret;
  ret = gzoffset64(file);
  return (ret == ((off_t) ret)) ? ((off_t) ret) : (-1);
}

int gzeof(gzFile file)
{
  gz_statep state;
  if (file == 0)
  {
    return 0;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) && (state->mode != 31153))
  {
    return 0;
  }
  return (state->mode == 7247) ? (state->past) : (0);
}

const char *gzerror(gzFile file, int *errnum)
{
  gz_statep state;
  if (file == 0)
  {
    return 0;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) && (state->mode != 31153))
  {
    return 0;
  }
  if (errnum != 0)
  {
    *errnum = state->err;
  }
  return (state->err == (-4)) ? ("out of memory") : ((state->msg == 0) ? ("") : (state->msg));
}

void gzclearerr(gzFile file)
{
  gz_statep state;
  if (file == 0)
  {
    return;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) && (state->mode != 31153))
  {
    return;
  }
  if (state->mode == 7247)
  {
    state->eof = 0;
    state->past = 0;
  }
  gz_error(state, 0, 0);
}

void gz_error(gz_statep state, int err, const char *msg)
{
  if (state->msg != 0)
  {
    if (state->err != (-4))
    {
      free(state->msg);
    }
    state->msg = 0;
  }
  if ((err != 0) && (err != (-5)))
  {
    state->x.have = 0;
  }
  state->err = err;
  if (msg == 0)
  {
    return;
  }
  if (err == (-4))
  {
    return;
  }
  if ((state->msg = (char *) malloc((strlen(state->path) + strlen(msg)) + 3)) == 0)
  {
    state->err = -4;
    return;
  }
  (void) snprintf(state->msg, (strlen(state->path) + strlen(msg)) + 3, "%s%s%s", state->path, ": ", msg);
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
static void gz_reset(gz_statep state)
{
  state->x.have = 0;
  if (state->mode == 7247)
  {
    state->eof = 0;
    state->past = 0;
    state->how = 0;
  }
  else
    state->reset = 0;
  state->seek = 0;
  gz_error(state, 0, 0);
  state->x.pos = 0;
  state->strm.avail_in = 0;
}

static gzFile gz_open(const void *path, int fd, const char *mode)
{
  unsigned int mode_idx = 0;
  gz_statep state;
  z_size_t len;
  int oflag;
  if (path == 0)
  {
    return 0;
  }
  state = (gz_statep) malloc(sizeof(gz_state));
  if (state == 0)
  {
    return 0;
  }
  state->size = 0;
  state->want = 8192;
  state->msg = 0;
  state->mode = 0;
  state->level = -1;
  state->strategy = 0;
  state->direct = 0;
  while (mode[mode_idx])
  {
    if ((mode[mode_idx] >= '0') && (mode[mode_idx] <= '9'))
    {
      state->level = mode[mode_idx] - '0';
    }
    else
      switch (mode[mode_idx])
    {
      case 'r':
        state->mode = 7247;
        break;

      case '+':
        free(state);
        return 0;

      case 'b':
        break;

      case 'f':
        state->strategy = 1;
        break;

      case 'h':
        state->strategy = 2;
        break;

      case 'R':
        state->strategy = 3;
        break;

      case 'F':
        state->strategy = 4;
        break;

      case 'T':
        state->direct = 1;
        break;

      default:
        ;

    }

    mode_idx += 1;
  }

  if (state->mode == 0)
  {
    free(state);
    return 0;
  }
  if (state->mode == 7247)
  {
    if (state->direct)
    {
      free(state);
      return 0;
    }
    state->direct = 1;
  }
  len = strlen((const char *) path);
  state->path = (char *) malloc(len + 1);
  if (state->path == 0)
  {
    free(state);
    return 0;
  }
  (void) snprintf(state->path, len + 1, "%s", (const char *) path);
  oflag = (state->mode == 7247) ? (O_RDONLY) : ((O_WRONLY | O_CREAT) | ((state->mode == 31153) ? (O_TRUNC) : (O_APPEND)));
  state->fd = (fd > (-1)) ? (fd) : (open((const char *) path, oflag, 0666));
  if (state->fd == (-1))
  {
    free(state->path);
    free(state);
    return 0;
  }
  if (state->mode == 1)
  {
    lseek(state->fd, 0, 2);
    state->mode = 31153;
  }
  if (state->mode == 7247)
  {
    state->start = lseek(state->fd, 0, 1);
    if (state->start == (-1))
    {
      state->start = 0;
    }
  }
  gz_reset(state);
  return (gzFile) state;
}

gzFile gzopen(const char *path, const char *mode)
{
  return gz_open(path, -1, mode);
}

gzFile gzopen64(const char *path, const char *mode)
{
  return gz_open(path, -1, mode);
}

gzFile gzdopen(int fd, const char *mode)
{
  char *path;
  unsigned int path_idx = 0;
  gzFile gz;
  if ((fd == (-1)) || ((path_idx = (char *) malloc(7 + (3 * (sizeof(int))))) == 0))
  {
    return 0;
  }
  (void) snprintf(path, 7 + (3 * (sizeof(int))), "<fd:%d>", fd);
  gz = gz_open(path, fd, mode);
  free(path);
  return gz;
}

int gzbuffer(gzFile file, unsigned size)
{
  gz_statep state;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) && (state->mode != 31153))
  {
    return -1;
  }
  if (state->size != 0)
  {
    return -1;
  }
  if ((size << 1) < size)
  {
    return -1;
  }
  if (size < 8)
  {
    size = 8;
  }
  state->want = size;
  return 0;
}

int gzrewind(gzFile file)
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
  if (lseek(state->fd, state->start, 0) == (-1))
  {
    return -1;
  }
  gz_reset(state);
  return 0;
}

off_t gzseek64(gzFile file, off_t offset, int whence)
{
  unsigned n;
  off_t ret;
  gz_statep state;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) && (state->mode != 31153))
  {
    return -1;
  }
  if ((state->err != 0) && (state->err != (-5)))
  {
    return -1;
  }
  if ((whence != 0) && (whence != 1))
  {
    return -1;
  }
  if (whence == 0)
  {
    offset -= state->x.pos;
  }
  else
    if (state->seek)
  {
    offset += state->skip;
  }
  state->seek = 0;
  if (((state->mode == 7247) && (state->how == 1)) && ((state->x.pos + offset) >= 0))
  {
    ret = lseek(state->fd, offset - ((off_t) state->x.have), 1);
    if (ret == (-1))
    {
      return -1;
    }
    state->x.have = 0;
    state->eof = 0;
    state->past = 0;
    state->seek = 0;
    gz_error(state, 0, 0);
    state->strm.avail_in = 0;
    state->x.pos += offset;
    return state->x.pos;
  }
  if (offset < 0)
  {
    if (state->mode != 7247)
    {
      return -1;
    }
    offset += state->x.pos;
    if (offset < 0)
    {
      return -1;
    }
    if (gzrewind(file) == (-1))
    {
      return -1;
    }
  }
  if (state->mode == 7247)
  {
    n = ((((sizeof(int)) == (sizeof(off_t))) && (state->x.have > 2147483647)) || (((off_t) state->x.have) > offset)) ? ((unsigned) offset) : (state->x.have);
    state->x.have -= n;
    state->x.next += n;
    state->x.pos += n;
    offset -= n;
  }
  if (offset)
  {
    state->seek = 1;
    state->skip = offset;
  }
  return state->x.pos + offset;
}

off_t gzseek(gzFile file, off_t offset, int whence)
{
  off_t ret;
  ret = gzseek64(file, (off_t) offset, whence);
  return (ret == ((off_t) ret)) ? ((off_t) ret) : (-1);
}

off_t gztell64(gzFile file)
{
  gz_statep state;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) && (state->mode != 31153))
  {
    return -1;
  }
  return state->x.pos + ((state->seek) ? (state->skip) : (0));
}

off_t gztell(gzFile file)
{
  off_t ret;
  ret = gztell64(file);
  return (ret == ((off_t) ret)) ? ((off_t) ret) : (-1);
}

off_t gzoffset64(gzFile file)
{
  off_t offset;
  gz_statep state;
  if (file == 0)
  {
    return -1;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) && (state->mode != 31153))
  {
    return -1;
  }
  offset = lseek(state->fd, 0, 1);
  if (offset == (-1))
  {
    return -1;
  }
  if (state->mode == 7247)
  {
    offset -= state->strm.avail_in;
  }
  return offset;
}

off_t gzoffset(gzFile file)
{
  off_t ret;
  ret = gzoffset64(file);
  return (ret == ((off_t) ret)) ? ((off_t) ret) : (-1);
}

int gzeof(gzFile file)
{
  gz_statep state;
  if (file == 0)
  {
    return 0;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) && (state->mode != 31153))
  {
    return 0;
  }
  return (state->mode == 7247) ? (state->past) : (0);
}

const char *gzerror(gzFile file, int *errnum)
{
  gz_statep state;
  if (file == 0)
  {
    return 0;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) && (state->mode != 31153))
  {
    return 0;
  }
  if (errnum != 0)
  {
    *errnum = state->err;
  }
  return (state->err == (-4)) ? ("out of memory") : ((state->msg == 0) ? ("") : (state->msg));
}

void gzclearerr(gzFile file)
{
  gz_statep state;
  if (file == 0)
  {
    return;
  }
  state = (gz_statep) file;
  if ((state->mode != 7247) && (state->mode != 31153))
  {
    return;
  }
  if (state->mode == 7247)
  {
    state->eof = 0;
    state->past = 0;
  }
  gz_error(state, 0, 0);
}

void gz_error(gz_statep state, int err, const char *msg)
{
  if (state->msg != 0)
  {
    if (state->err != (-4))
    {
      free(state->msg);
    }
    state->msg = 0;
  }
  if ((err != 0) && (err != (-5)))
  {
    state->x.have = 0;
  }
  state->err = err;
  if (msg == 0)
  {
    return;
  }
  if (err == (-4))
  {
    return;
  }
  if ((state->msg = (char *) malloc((strlen(state->path) + strlen(msg)) + 3)) == 0)
  {
    state->err = -4;
    return;
  }
  (void) snprintf(state->msg, (strlen(state->path) + strlen(msg)) + 3, "%s%s%s", state->path, ": ", msg);
}

gzFile helper_gz_open_1(unsigned int * const mode_idx_ref, gz_statep * const state_ref, const char * const mode)
{
  unsigned int mode_idx = *mode_idx_ref;
  gz_statep state = *state_ref;
  if ((mode[mode_idx] >= '0') && (mode[mode_idx] <= '9'))
  {
    state->level = mode[mode_idx] - '0';
  }
  else
    switch (mode[mode_idx])
  {
    case 'r':
    {
      state->mode = 7247;
      break;
    }

    case '+':
    {
      free(state);
      return 0;
    }

    case 'b':
    {
      break;
    }

    case 'f':
    {
      state->strategy = 1;
      break;
    }

    case 'h':
    {
      state->strategy = 2;
      break;
    }

    case 'R':
    {
      state->strategy = 3;
      break;
    }

    case 'F':
    {
      state->strategy = 4;
      break;
    }

    case 'T':
    {
      state->direct = 1;
      break;
    }

    default:
    {
      ;
    }

  }

  mode_idx += 1;
  *mode_idx_ref = mode_idx;
  *state_ref = state;
}

off_t helper_gzseek64_1(off_t * const ret_ref, gz_statep * const state_ref, off_t offset)
{
  off_t ret = *ret_ref;
  gz_statep state = *state_ref;
  ret = lseek(state->fd, offset - ((off_t) state->x.have), 1);
  if (ret == (-1))
  {
    return -1;
  }
  state->x.have = 0;
  state->eof = 0;
  state->past = 0;
  state->seek = 0;
  gz_error(state, 0, 0);
  state->strm.avail_in = 0;
  state->x.pos += offset;
  return state->x.pos;
  *ret_ref = ret;
  *state_ref = state;
}

