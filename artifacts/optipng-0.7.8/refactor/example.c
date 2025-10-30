#include <example.c>
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
  const Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  const char *msg;
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
typedef unsigned (*in_func)(void *, const unsigned char **);
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
static const char hello[] = "hello, hello!";
static const char dictionary[] = "hello";
static uLong dictId;
static alloc_func zalloc = (alloc_func) 0;
static free_func zfree = (free_func) 0;
void test_compress(Byte *compr, uLong comprLen, Byte *uncompr, uLong uncomprLen)
{
  int err;
  uLong len = ((uLong) strlen(hello)) + 1;
  err = compress(compr, &comprLen, (const Bytef *) hello, len);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "compress", err);
      exit(1);
    }
  }
  ;
  strcpy((char *) uncompr, "garbage");
  err = uncompress(uncompr, &uncomprLen, compr, comprLen);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "uncompress", err);
      exit(1);
    }
  }
  ;
  if (strcmp((char *) uncompr, hello))
  {
    fprintf(stderr, "bad uncompress\n");
    exit(1);
  }
  else
  {
    printf("uncompress(): %s\n", (char *) uncompr);
  }
}

void test_gzio(const char *fname, Byte *uncompr, uLong uncomprLen)
{
  fprintf(stderr, "NO_GZCOMPRESS -- gz* functions cannot compress\n");
}

void test_deflate(Byte *compr, uLong comprLen)
{
  z_stream c_stream;
  int err;
  uLong len = ((uLong) strlen(hello)) + 1;
  c_stream.zalloc = zalloc;
  c_stream.zfree = zfree;
  c_stream.opaque = (voidpf) 0;
  err = deflateInit_(&c_stream, -1, "1.3-optipng", (int) (sizeof(z_stream)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateInit", err);
      exit(1);
    }
  }
  ;
  c_stream.next_in = (const unsigned char *) hello;
  c_stream.next_out = compr;
  while ((c_stream.total_in != len) && (c_stream.total_out < comprLen))
  {
    c_stream.avail_in = (c_stream.avail_out = 1);
    err = deflate(&c_stream, 0);
    {
      if (err != 0)
      {
        fprintf(stderr, "%s error: %d\n", "deflate", err);
        exit(1);
      }
    }
    ;
  }

  for (;;)
  {
    c_stream.avail_out = 1;
    err = deflate(&c_stream, 4);
    if (err == 1)
    {
      break;
    }
    {
      if (err != 0)
      {
        fprintf(stderr, "%s error: %d\n", "deflate", err);
        exit(1);
      }
    }
    ;
  }

  err = deflateEnd(&c_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateEnd", err);
      exit(1);
    }
  }
  ;
}

void test_inflate(Byte *compr, uLong comprLen, Byte *uncompr, uLong uncomprLen)
{
  int err;
  z_stream d_stream;
  strcpy((char *) uncompr, "garbage");
  d_stream.zalloc = zalloc;
  d_stream.zfree = zfree;
  d_stream.opaque = (voidpf) 0;
  d_stream.next_in = compr;
  d_stream.avail_in = 0;
  d_stream.next_out = uncompr;
  err = inflateInit_(&d_stream, "1.3-optipng", (int) (sizeof(z_stream)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateInit", err);
      exit(1);
    }
  }
  ;
  while ((d_stream.total_out < uncomprLen) && (d_stream.total_in < comprLen))
  {
    d_stream.avail_in = (d_stream.avail_out = 1);
    err = inflate(&d_stream, 0);
    if (err == 1)
    {
      break;
    }
    {
      if (err != 0)
      {
        fprintf(stderr, "%s error: %d\n", "inflate", err);
        exit(1);
      }
    }
    ;
  }

  err = inflateEnd(&d_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateEnd", err);
      exit(1);
    }
  }
  ;
  if (strcmp((char *) uncompr, hello))
  {
    fprintf(stderr, "bad inflate\n");
    exit(1);
  }
  else
  {
    printf("inflate(): %s\n", (char *) uncompr);
  }
}

void test_large_deflate(Byte *compr, uLong comprLen, Byte *uncompr, uLong uncomprLen)
{
  z_stream c_stream;
  int err;
  c_stream.zalloc = zalloc;
  c_stream.zfree = zfree;
  c_stream.opaque = (voidpf) 0;
  err = deflateInit_(&c_stream, 1, "1.3-optipng", (int) (sizeof(z_stream)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateInit", err);
      exit(1);
    }
  }
  ;
  c_stream.next_out = compr;
  c_stream.avail_out = (uInt) comprLen;
  c_stream.next_in = uncompr;
  c_stream.avail_in = (uInt) uncomprLen;
  err = deflate(&c_stream, 0);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflate", err);
      exit(1);
    }
  }
  ;
  if (c_stream.avail_in != 0)
  {
    fprintf(stderr, "deflate not greedy\n");
    exit(1);
  }
  deflateParams(&c_stream, 0, 0);
  c_stream.next_in = compr;
  c_stream.avail_in = ((uInt) uncomprLen) / 2;
  err = deflate(&c_stream, 0);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflate", err);
      exit(1);
    }
  }
  ;
  deflateParams(&c_stream, 9, 1);
  c_stream.next_in = uncompr;
  c_stream.avail_in = (uInt) uncomprLen;
  err = deflate(&c_stream, 0);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflate", err);
      exit(1);
    }
  }
  ;
  err = deflate(&c_stream, 4);
  if (err != 1)
  {
    fprintf(stderr, "deflate should report Z_STREAM_END\n");
    exit(1);
  }
  err = deflateEnd(&c_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateEnd", err);
      exit(1);
    }
  }
  ;
}

void test_large_inflate(Byte *compr, uLong comprLen, Byte *uncompr, uLong uncomprLen)
{
  int err;
  z_stream d_stream;
  strcpy((char *) uncompr, "garbage");
  d_stream.zalloc = zalloc;
  d_stream.zfree = zfree;
  d_stream.opaque = (voidpf) 0;
  d_stream.next_in = compr;
  d_stream.avail_in = (uInt) comprLen;
  err = inflateInit_(&d_stream, "1.3-optipng", (int) (sizeof(z_stream)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateInit", err);
      exit(1);
    }
  }
  ;
  for (;;)
  {
    d_stream.next_out = uncompr;
    d_stream.avail_out = (uInt) uncomprLen;
    err = inflate(&d_stream, 0);
    if (err == 1)
    {
      break;
    }
    {
      if (err != 0)
      {
        fprintf(stderr, "%s error: %d\n", "large inflate", err);
        exit(1);
      }
    }
    ;
  }

  err = inflateEnd(&d_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateEnd", err);
      exit(1);
    }
  }
  ;
  if (d_stream.total_out != ((2 * uncomprLen) + (uncomprLen / 2)))
  {
    fprintf(stderr, "bad large inflate: %ld\n", d_stream.total_out);
    exit(1);
  }
  else
  {
    printf("large_inflate(): OK\n");
  }
}

void test_flush(Byte *compr, uLong *comprLen)
{
  z_stream c_stream;
  int err;
  uInt len = ((uInt) strlen(hello)) + 1;
  c_stream.zalloc = zalloc;
  c_stream.zfree = zfree;
  c_stream.opaque = (voidpf) 0;
  err = deflateInit_(&c_stream, -1, "1.3-optipng", (int) (sizeof(z_stream)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateInit", err);
      exit(1);
    }
  }
  ;
  c_stream.next_in = (const unsigned char *) hello;
  c_stream.next_out = compr;
  c_stream.avail_in = 3;
  c_stream.avail_out = (uInt) (*comprLen);
  err = deflate(&c_stream, 3);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflate", err);
      exit(1);
    }
  }
  ;
  compr[3] += 1;
  c_stream.avail_in = len - 3;
  err = deflate(&c_stream, 4);
  if (err != 1)
  {
    {
      if (err != 0)
      {
        fprintf(stderr, "%s error: %d\n", "deflate", err);
        exit(1);
      }
    }
    ;
  }
  err = deflateEnd(&c_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateEnd", err);
      exit(1);
    }
  }
  ;
  *comprLen = c_stream.total_out;
}

void test_sync(Byte *compr, uLong comprLen, Byte *uncompr, uLong uncomprLen)
{
  int err;
  z_stream d_stream;
  strcpy((char *) uncompr, "garbage");
  d_stream.zalloc = zalloc;
  d_stream.zfree = zfree;
  d_stream.opaque = (voidpf) 0;
  d_stream.next_in = compr;
  d_stream.avail_in = 2;
  err = inflateInit_(&d_stream, "1.3-optipng", (int) (sizeof(z_stream)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateInit", err);
      exit(1);
    }
  }
  ;
  d_stream.next_out = uncompr;
  d_stream.avail_out = (uInt) uncomprLen;
  err = inflate(&d_stream, 0);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflate", err);
      exit(1);
    }
  }
  ;
  d_stream.avail_in = ((uInt) comprLen) - 2;
  err = inflateSync(&d_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateSync", err);
      exit(1);
    }
  }
  ;
  err = inflate(&d_stream, 4);
  if (err != 1)
  {
    fprintf(stderr, "inflate should report Z_STREAM_END\n");
    exit(1);
  }
  err = inflateEnd(&d_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateEnd", err);
      exit(1);
    }
  }
  ;
  printf("after inflateSync(): hel%s\n", (char *) uncompr);
}

void test_dict_deflate(Byte *compr, uLong comprLen)
{
  z_stream c_stream;
  int err;
  c_stream.zalloc = zalloc;
  c_stream.zfree = zfree;
  c_stream.opaque = (voidpf) 0;
  err = deflateInit_(&c_stream, 9, "1.3-optipng", (int) (sizeof(z_stream)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateInit", err);
      exit(1);
    }
  }
  ;
  err = deflateSetDictionary(&c_stream, (const Bytef *) dictionary, (int) (sizeof(dictionary)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateSetDictionary", err);
      exit(1);
    }
  }
  ;
  dictId = c_stream.adler;
  c_stream.next_out = compr;
  c_stream.avail_out = (uInt) comprLen;
  c_stream.next_in = (const unsigned char *) hello;
  c_stream.avail_in = ((uInt) strlen(hello)) + 1;
  err = deflate(&c_stream, 4);
  if (err != 1)
  {
    fprintf(stderr, "deflate should report Z_STREAM_END\n");
    exit(1);
  }
  err = deflateEnd(&c_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateEnd", err);
      exit(1);
    }
  }
  ;
}

void test_dict_inflate(Byte *compr, uLong comprLen, Byte *uncompr, uLong uncomprLen)
{
  int err;
  z_stream d_stream;
  strcpy((char *) uncompr, "garbage");
  d_stream.zalloc = zalloc;
  d_stream.zfree = zfree;
  d_stream.opaque = (voidpf) 0;
  d_stream.next_in = compr;
  d_stream.avail_in = (uInt) comprLen;
  err = inflateInit_(&d_stream, "1.3-optipng", (int) (sizeof(z_stream)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateInit", err);
      exit(1);
    }
  }
  ;
  d_stream.next_out = uncompr;
  d_stream.avail_out = (uInt) uncomprLen;
  for (;;)
  {
    err = inflate(&d_stream, 0);
    if (err == 1)
    {
      break;
    }
    if (err == 2)
    {
      if (d_stream.adler != dictId)
      {
        fprintf(stderr, "unexpected dictionary");
        exit(1);
      }
      err = inflateSetDictionary(&d_stream, (const Bytef *) dictionary, (int) (sizeof(dictionary)));
    }
    {
      if (err != 0)
      {
        fprintf(stderr, "%s error: %d\n", "inflate with dict", err);
        exit(1);
      }
    }
    ;
  }

  err = inflateEnd(&d_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateEnd", err);
      exit(1);
    }
  }
  ;
  if (strcmp((char *) uncompr, hello))
  {
    fprintf(stderr, "bad inflate with dict\n");
    exit(1);
  }
  else
  {
    printf("inflate with dictionary: %s\n", (char *) uncompr);
  }
}

int main(int argc, char *argv[])
{
  Byte *compr;
  unsigned int compr_idx = 0;
  Byte *uncompr;
  unsigned int uncompr_idx = 0;
  uLong uncomprLen = 20000;
  uLong comprLen = 3 * uncomprLen;
  static const char *myVersion = "1.3-optipng";
  if (zlibVersion()[0] != myVersion[0])
  {
    fprintf(stderr, "incompatible zlib version\n");
    exit(1);
  }
  else
    if (strcmp(zlibVersion(), "1.3-optipng") != 0)
  {
    fprintf(stderr, "warning: different zlib version linked: %s\n", zlibVersion());
  }
  printf("zlib version %s = 0x%04x, compile flags = 0x%lx\n", "1.3-optipng", 0x130f, zlibCompileFlags());
  compr_idx = (Byte *) calloc((uInt) comprLen, 1);
  uncompr_idx = (Byte *) calloc((uInt) uncomprLen, 1);
  if (((&compr[compr_idx]) == 0) || ((&uncompr[uncompr_idx]) == 0))
  {
    printf("out of memory\n");
    exit(1);
  }
  test_compress(compr, comprLen, uncompr, uncomprLen);
  test_gzio((argc > 1) ? (argv[1]) : ("foo.gz"), uncompr, uncomprLen);
  test_deflate(compr, comprLen);
  test_inflate(compr, comprLen, uncompr, uncomprLen);
  test_large_deflate(compr, comprLen, uncompr, uncomprLen);
  test_large_inflate(compr, comprLen, uncompr, uncomprLen);
  test_flush(compr, &comprLen);
  test_sync(compr, comprLen, uncompr, uncomprLen);
  comprLen = 3 * uncomprLen;
  test_dict_deflate(compr, comprLen);
  test_dict_inflate(compr, comprLen, uncompr, uncomprLen);
  free(compr);
  free(uncompr);
  return 0;
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
  const Bytef *next_in;
  uInt avail_in;
  uLong total_in;
  Bytef *next_out;
  uInt avail_out;
  uLong total_out;
  const char *msg;
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
typedef unsigned (*in_func)(void *, const unsigned char **);
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
static const char hello[] = "hello, hello!";
static const char dictionary[] = "hello";
static uLong dictId;
static alloc_func zalloc = (alloc_func) 0;
static free_func zfree = (free_func) 0;
void test_compress(Byte *compr, uLong comprLen, Byte *uncompr, uLong uncomprLen)
{
  int err;
  uLong len = ((uLong) strlen(hello)) + 1;
  err = compress(compr, &comprLen, (const Bytef *) hello, len);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "compress", err);
      exit(1);
    }
  }
  ;
  strcpy((char *) uncompr, "garbage");
  err = uncompress(uncompr, &uncomprLen, compr, comprLen);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "uncompress", err);
      exit(1);
    }
  }
  ;
  if (strcmp((char *) uncompr, hello))
  {
    fprintf(stderr, "bad uncompress\n");
    exit(1);
  }
  else
  {
    printf("uncompress(): %s\n", (char *) uncompr);
  }
}

void test_gzio(const char *fname, Byte *uncompr, uLong uncomprLen)
{
  fprintf(stderr, "NO_GZCOMPRESS -- gz* functions cannot compress\n");
}

void test_deflate(Byte *compr, uLong comprLen)
{
  z_stream c_stream;
  int err;
  uLong len = ((uLong) strlen(hello)) + 1;
  c_stream.zalloc = zalloc;
  c_stream.zfree = zfree;
  c_stream.opaque = (voidpf) 0;
  err = deflateInit_(&c_stream, -1, "1.3-optipng", (int) (sizeof(z_stream)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateInit", err);
      exit(1);
    }
  }
  ;
  c_stream.next_in = (const unsigned char *) hello;
  c_stream.next_out = compr;
  while ((c_stream.total_in != len) && (c_stream.total_out < comprLen))
  {
    c_stream.avail_in = (c_stream.avail_out = 1);
    err = deflate(&c_stream, 0);
    {
      if (err != 0)
      {
        fprintf(stderr, "%s error: %d\n", "deflate", err);
        exit(1);
      }
    }
    ;
  }

  for (;;)
  {
    c_stream.avail_out = 1;
    err = deflate(&c_stream, 4);
    if (err == 1)
    {
      break;
    }
    {
      if (err != 0)
      {
        fprintf(stderr, "%s error: %d\n", "deflate", err);
        exit(1);
      }
    }
    ;
  }

  err = deflateEnd(&c_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateEnd", err);
      exit(1);
    }
  }
  ;
}

void test_inflate(Byte *compr, uLong comprLen, Byte *uncompr, uLong uncomprLen)
{
  int err;
  z_stream d_stream;
  strcpy((char *) uncompr, "garbage");
  d_stream.zalloc = zalloc;
  d_stream.zfree = zfree;
  d_stream.opaque = (voidpf) 0;
  d_stream.next_in = compr;
  d_stream.avail_in = 0;
  d_stream.next_out = uncompr;
  err = inflateInit_(&d_stream, "1.3-optipng", (int) (sizeof(z_stream)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateInit", err);
      exit(1);
    }
  }
  ;
  while ((d_stream.total_out < uncomprLen) && (d_stream.total_in < comprLen))
  {
    d_stream.avail_in = (d_stream.avail_out = 1);
    err = inflate(&d_stream, 0);
    if (err == 1)
    {
      break;
    }
    {
      if (err != 0)
      {
        fprintf(stderr, "%s error: %d\n", "inflate", err);
        exit(1);
      }
    }
    ;
  }

  err = inflateEnd(&d_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateEnd", err);
      exit(1);
    }
  }
  ;
  if (strcmp((char *) uncompr, hello))
  {
    fprintf(stderr, "bad inflate\n");
    exit(1);
  }
  else
  {
    printf("inflate(): %s\n", (char *) uncompr);
  }
}

void test_large_deflate(Byte *compr, uLong comprLen, Byte *uncompr, uLong uncomprLen)
{
  z_stream c_stream;
  int err;
  c_stream.zalloc = zalloc;
  c_stream.zfree = zfree;
  c_stream.opaque = (voidpf) 0;
  err = deflateInit_(&c_stream, 1, "1.3-optipng", (int) (sizeof(z_stream)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateInit", err);
      exit(1);
    }
  }
  ;
  c_stream.next_out = compr;
  c_stream.avail_out = (uInt) comprLen;
  c_stream.next_in = uncompr;
  c_stream.avail_in = (uInt) uncomprLen;
  err = deflate(&c_stream, 0);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflate", err);
      exit(1);
    }
  }
  ;
  if (c_stream.avail_in != 0)
  {
    fprintf(stderr, "deflate not greedy\n");
    exit(1);
  }
  deflateParams(&c_stream, 0, 0);
  c_stream.next_in = compr;
  c_stream.avail_in = ((uInt) uncomprLen) / 2;
  err = deflate(&c_stream, 0);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflate", err);
      exit(1);
    }
  }
  ;
  deflateParams(&c_stream, 9, 1);
  c_stream.next_in = uncompr;
  c_stream.avail_in = (uInt) uncomprLen;
  err = deflate(&c_stream, 0);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflate", err);
      exit(1);
    }
  }
  ;
  err = deflate(&c_stream, 4);
  if (err != 1)
  {
    fprintf(stderr, "deflate should report Z_STREAM_END\n");
    exit(1);
  }
  err = deflateEnd(&c_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateEnd", err);
      exit(1);
    }
  }
  ;
}

void test_large_inflate(Byte *compr, uLong comprLen, Byte *uncompr, uLong uncomprLen)
{
  int err;
  z_stream d_stream;
  strcpy((char *) uncompr, "garbage");
  d_stream.zalloc = zalloc;
  d_stream.zfree = zfree;
  d_stream.opaque = (voidpf) 0;
  d_stream.next_in = compr;
  d_stream.avail_in = (uInt) comprLen;
  err = inflateInit_(&d_stream, "1.3-optipng", (int) (sizeof(z_stream)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateInit", err);
      exit(1);
    }
  }
  ;
  for (;;)
  {
    d_stream.next_out = uncompr;
    d_stream.avail_out = (uInt) uncomprLen;
    err = inflate(&d_stream, 0);
    if (err == 1)
    {
      break;
    }
    {
      if (err != 0)
      {
        fprintf(stderr, "%s error: %d\n", "large inflate", err);
        exit(1);
      }
    }
    ;
  }

  err = inflateEnd(&d_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateEnd", err);
      exit(1);
    }
  }
  ;
  if (d_stream.total_out != ((2 * uncomprLen) + (uncomprLen / 2)))
  {
    fprintf(stderr, "bad large inflate: %ld\n", d_stream.total_out);
    exit(1);
  }
  else
  {
    printf("large_inflate(): OK\n");
  }
}

void test_flush(Byte *compr, uLong *comprLen)
{
  z_stream c_stream;
  int err;
  uInt len = ((uInt) strlen(hello)) + 1;
  c_stream.zalloc = zalloc;
  c_stream.zfree = zfree;
  c_stream.opaque = (voidpf) 0;
  err = deflateInit_(&c_stream, -1, "1.3-optipng", (int) (sizeof(z_stream)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateInit", err);
      exit(1);
    }
  }
  ;
  c_stream.next_in = (const unsigned char *) hello;
  c_stream.next_out = compr;
  c_stream.avail_in = 3;
  c_stream.avail_out = (uInt) (*comprLen);
  err = deflate(&c_stream, 3);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflate", err);
      exit(1);
    }
  }
  ;
  compr[3] += 1;
  c_stream.avail_in = len - 3;
  err = deflate(&c_stream, 4);
  if (err != 1)
  {
    {
      if (err != 0)
      {
        fprintf(stderr, "%s error: %d\n", "deflate", err);
        exit(1);
      }
    }
    ;
  }
  err = deflateEnd(&c_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateEnd", err);
      exit(1);
    }
  }
  ;
  *comprLen = c_stream.total_out;
}

void test_sync(Byte *compr, uLong comprLen, Byte *uncompr, uLong uncomprLen)
{
  int err;
  z_stream d_stream;
  strcpy((char *) uncompr, "garbage");
  d_stream.zalloc = zalloc;
  d_stream.zfree = zfree;
  d_stream.opaque = (voidpf) 0;
  d_stream.next_in = compr;
  d_stream.avail_in = 2;
  err = inflateInit_(&d_stream, "1.3-optipng", (int) (sizeof(z_stream)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateInit", err);
      exit(1);
    }
  }
  ;
  d_stream.next_out = uncompr;
  d_stream.avail_out = (uInt) uncomprLen;
  err = inflate(&d_stream, 0);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflate", err);
      exit(1);
    }
  }
  ;
  d_stream.avail_in = ((uInt) comprLen) - 2;
  err = inflateSync(&d_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateSync", err);
      exit(1);
    }
  }
  ;
  err = inflate(&d_stream, 4);
  if (err != 1)
  {
    fprintf(stderr, "inflate should report Z_STREAM_END\n");
    exit(1);
  }
  err = inflateEnd(&d_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateEnd", err);
      exit(1);
    }
  }
  ;
  printf("after inflateSync(): hel%s\n", (char *) uncompr);
}

void test_dict_deflate(Byte *compr, uLong comprLen)
{
  z_stream c_stream;
  int err;
  c_stream.zalloc = zalloc;
  c_stream.zfree = zfree;
  c_stream.opaque = (voidpf) 0;
  err = deflateInit_(&c_stream, 9, "1.3-optipng", (int) (sizeof(z_stream)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateInit", err);
      exit(1);
    }
  }
  ;
  err = deflateSetDictionary(&c_stream, (const Bytef *) dictionary, (int) (sizeof(dictionary)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateSetDictionary", err);
      exit(1);
    }
  }
  ;
  dictId = c_stream.adler;
  c_stream.next_out = compr;
  c_stream.avail_out = (uInt) comprLen;
  c_stream.next_in = (const unsigned char *) hello;
  c_stream.avail_in = ((uInt) strlen(hello)) + 1;
  err = deflate(&c_stream, 4);
  if (err != 1)
  {
    fprintf(stderr, "deflate should report Z_STREAM_END\n");
    exit(1);
  }
  err = deflateEnd(&c_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "deflateEnd", err);
      exit(1);
    }
  }
  ;
}

void test_dict_inflate(Byte *compr, uLong comprLen, Byte *uncompr, uLong uncomprLen)
{
  int err;
  z_stream d_stream;
  strcpy((char *) uncompr, "garbage");
  d_stream.zalloc = zalloc;
  d_stream.zfree = zfree;
  d_stream.opaque = (voidpf) 0;
  d_stream.next_in = compr;
  d_stream.avail_in = (uInt) comprLen;
  err = inflateInit_(&d_stream, "1.3-optipng", (int) (sizeof(z_stream)));
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateInit", err);
      exit(1);
    }
  }
  ;
  d_stream.next_out = uncompr;
  d_stream.avail_out = (uInt) uncomprLen;
  for (;;)
  {
    err = inflate(&d_stream, 0);
    if (err == 1)
    {
      break;
    }
    if (err == 2)
    {
      if (d_stream.adler != dictId)
      {
        fprintf(stderr, "unexpected dictionary");
        exit(1);
      }
      err = inflateSetDictionary(&d_stream, (const Bytef *) dictionary, (int) (sizeof(dictionary)));
    }
    {
      if (err != 0)
      {
        fprintf(stderr, "%s error: %d\n", "inflate with dict", err);
        exit(1);
      }
    }
    ;
  }

  err = inflateEnd(&d_stream);
  {
    if (err != 0)
    {
      fprintf(stderr, "%s error: %d\n", "inflateEnd", err);
      exit(1);
    }
  }
  ;
  if (strcmp((char *) uncompr, hello))
  {
    fprintf(stderr, "bad inflate with dict\n");
    exit(1);
  }
  else
  {
    printf("inflate with dictionary: %s\n", (char *) uncompr);
  }
}

int main(int argc, char *argv[])
{
  Byte *compr;
  unsigned int compr_idx = 0;
  Byte *uncompr;
  unsigned int uncompr_idx = 0;
  uLong uncomprLen = 20000;
  uLong comprLen = 3 * uncomprLen;
  static const char *myVersion = "1.3-optipng";
  if (zlibVersion()[0] != myVersion[0])
  {
    fprintf(stderr, "incompatible zlib version\n");
    exit(1);
  }
  else
    if (strcmp(zlibVersion(), "1.3-optipng") != 0)
  {
    fprintf(stderr, "warning: different zlib version linked: %s\n", zlibVersion());
  }
  printf("zlib version %s = 0x%04x, compile flags = 0x%lx\n", "1.3-optipng", 0x130f, zlibCompileFlags());
  compr_idx = (Byte *) calloc((uInt) comprLen, 1);
  uncompr_idx = (Byte *) calloc((uInt) uncomprLen, 1);
  if (((&compr[compr_idx]) == 0) || ((&uncompr[uncompr_idx]) == 0))
  {
    printf("out of memory\n");
    exit(1);
  }
  test_compress(compr, comprLen, uncompr, uncomprLen);
  test_gzio((argc > 1) ? (argv[1]) : ("foo.gz"), uncompr, uncomprLen);
  test_deflate(compr, comprLen);
  test_inflate(compr, comprLen, uncompr, uncomprLen);
  test_large_deflate(compr, comprLen, uncompr, uncomprLen);
  test_large_inflate(compr, comprLen, uncompr, uncomprLen);
  test_flush(compr, &comprLen);
  test_sync(compr, comprLen, uncompr, uncomprLen);
  comprLen = 3 * uncomprLen;
  test_dict_deflate(compr, comprLen);
  test_dict_inflate(compr, comprLen, uncompr, uncomprLen);
  free(compr);
  free(uncompr);
  return 0;
}

