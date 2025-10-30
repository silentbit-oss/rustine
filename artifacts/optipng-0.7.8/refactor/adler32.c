#include <adler32.c>
#include <limits.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <types.h>
#include <unistd.h>
#include <zconf.h>
#include <zlib.h>
#include <zutil.h>

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
typedef unsigned char uch;
typedef uch uchf;
typedef unsigned short ush;
typedef ush ushf;
typedef unsigned long ulg;
extern const char * const z_errmsg[10];
extern uLong adler32_combine64(uLong, uLong, off_t);
extern uLong crc32_combine64(uLong, uLong, off_t);
extern uLong crc32_combine_gen64(off_t);
voidpf zcalloc(voidpf opaque, unsigned items, unsigned size);
void zcfree(voidpf opaque, voidpf ptr);
uLong adler32_z(uLong adler, const Bytef *buf, z_size_t len)
{
  unsigned int buf_idx = 0;
  unsigned long sum2;
  unsigned n;
  sum2 = (adler >> 16) & 0xffff;
  adler &= 0xffff;
  if (len == 1)
  {
    adler += buf[0 + buf_idx];
    if (adler >= 65521U)
    {
      adler -= 65521U;
    }
    sum2 += adler;
    if (sum2 >= 65521U)
    {
      sum2 -= 65521U;
    }
    return adler | (sum2 << 16);
  }
  if ((&buf[buf_idx]) == 0)
  {
    return 1L;
  }
  if (len < 16)
  {
    while (len--)
    {
      adler += buf[buf_idx];
      buf_idx += 1;
      sum2 += adler;
    }

    if (adler >= 65521U)
    {
      adler -= 65521U;
    }
    sum2 %= 65521U;
    return adler | (sum2 << 16);
  }
  while (len >= 5552)
  {
    helper_adler32_z_1(&adler, &len, &buf_idx, &sum2, &n, buf);
  }

  if (len)
  {
    helper_adler32_z_2(&adler, &len, &buf_idx, &sum2, buf);
  }
  return adler | (sum2 << 16);
}

uLong adler32(uLong adler, const Bytef *buf, uInt len)
{
  return adler32_z(adler, buf, len);
}

static uLong adler32_combine_(uLong adler1, uLong adler2, off_t len2)
{
  unsigned long sum1;
  unsigned long sum2;
  unsigned rem;
  if (len2 < 0)
  {
    return 0xffffffffUL;
  }
  len2 %= 65521U;
  rem = (unsigned) len2;
  sum1 = adler1 & 0xffff;
  sum2 = rem * sum1;
  sum2 %= 65521U;
  sum1 += ((adler2 & 0xffff) + 65521U) - 1;
  sum2 += ((((adler1 >> 16) & 0xffff) + ((adler2 >> 16) & 0xffff)) + 65521U) - rem;
  if (sum1 >= 65521U)
  {
    sum1 -= 65521U;
  }
  if (sum1 >= 65521U)
  {
    sum1 -= 65521U;
  }
  if (sum2 >= (((unsigned long) 65521U) << 1))
  {
    sum2 -= ((unsigned long) 65521U) << 1;
  }
  if (sum2 >= 65521U)
  {
    sum2 -= 65521U;
  }
  return sum1 | (sum2 << 16);
}

uLong adler32_combine(uLong adler1, uLong adler2, off_t len2)
{
  return adler32_combine_(adler1, adler2, len2);
}

uLong adler32_combine64(uLong adler1, uLong adler2, off_t len2)
{
  return adler32_combine_(adler1, adler2, len2);
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
typedef unsigned char uch;
typedef uch uchf;
typedef unsigned short ush;
typedef ush ushf;
typedef unsigned long ulg;
extern const char * const z_errmsg[10];
extern uLong adler32_combine64(uLong, uLong, off_t);
extern uLong crc32_combine64(uLong, uLong, off_t);
extern uLong crc32_combine_gen64(off_t);
voidpf zcalloc(voidpf opaque, unsigned items, unsigned size);
void zcfree(voidpf opaque, voidpf ptr);
uLong adler32_z(uLong adler, const Bytef *buf, z_size_t len)
{
  unsigned int buf_idx = 0;
  unsigned long sum2;
  unsigned n;
  sum2 = (adler >> 16) & 0xffff;
  adler &= 0xffff;
  if (len == 1)
  {
    adler += buf[0 + buf_idx];
    if (adler >= 65521U)
    {
      adler -= 65521U;
    }
    sum2 += adler;
    if (sum2 >= 65521U)
    {
      sum2 -= 65521U;
    }
    return adler | (sum2 << 16);
  }
  if ((&buf[buf_idx]) == 0)
  {
    return 1L;
  }
  if (len < 16)
  {
    while (len--)
    {
      adler += buf[buf_idx];
      buf_idx += 1;
      sum2 += adler;
    }

    if (adler >= 65521U)
    {
      adler -= 65521U;
    }
    sum2 %= 65521U;
    return adler | (sum2 << 16);
  }
  while (len >= 5552)
  {
    len -= 5552;
    n = 5552 / 16;
    do
    {
      {
        adler += buf[0 + buf_idx];
        sum2 += adler;
      }
      ;
      {
        adler += buf[(0 + 1) + buf_idx];
        sum2 += adler;
      }
      ;
      ;
      {
        adler += buf[(0 + 2) + buf_idx];
        sum2 += adler;
      }
      ;
      {
        adler += buf[((0 + 2) + 1) + buf_idx];
        sum2 += adler;
      }
      ;
      ;
      ;
      {
        adler += buf[(0 + 4) + buf_idx];
        sum2 += adler;
      }
      ;
      {
        adler += buf[((0 + 4) + 1) + buf_idx];
        sum2 += adler;
      }
      ;
      ;
      {
        adler += buf[((0 + 4) + 2) + buf_idx];
        sum2 += adler;
      }
      ;
      {
        adler += buf[(((0 + 4) + 2) + 1) + buf_idx];
        sum2 += adler;
      }
      ;
      ;
      ;
      ;
      {
        adler += buf[8 + buf_idx];
        sum2 += adler;
      }
      ;
      {
        adler += buf[(8 + 1) + buf_idx];
        sum2 += adler;
      }
      ;
      ;
      {
        adler += buf[(8 + 2) + buf_idx];
        sum2 += adler;
      }
      ;
      {
        adler += buf[((8 + 2) + 1) + buf_idx];
        sum2 += adler;
      }
      ;
      ;
      ;
      {
        adler += buf[(8 + 4) + buf_idx];
        sum2 += adler;
      }
      ;
      {
        adler += buf[((8 + 4) + 1) + buf_idx];
        sum2 += adler;
      }
      ;
      ;
      {
        adler += buf[((8 + 4) + 2) + buf_idx];
        sum2 += adler;
      }
      ;
      {
        adler += buf[(((8 + 4) + 2) + 1) + buf_idx];
        sum2 += adler;
      }
      ;
      ;
      ;
      ;
      ;
      buf_idx += 16;
    }
    while (--n);
    adler %= 65521U;
    sum2 %= 65521U;
  }

  if (len)
  {
    while (len >= 16)
    {
      len -= 16;
      {
        adler += buf[0 + buf_idx];
        sum2 += adler;
      }
      ;
      {
        adler += buf[(0 + 1) + buf_idx];
        sum2 += adler;
      }
      ;
      ;
      {
        adler += buf[(0 + 2) + buf_idx];
        sum2 += adler;
      }
      ;
      {
        adler += buf[((0 + 2) + 1) + buf_idx];
        sum2 += adler;
      }
      ;
      ;
      ;
      {
        adler += buf[(0 + 4) + buf_idx];
        sum2 += adler;
      }
      ;
      {
        adler += buf[((0 + 4) + 1) + buf_idx];
        sum2 += adler;
      }
      ;
      ;
      {
        adler += buf[((0 + 4) + 2) + buf_idx];
        sum2 += adler;
      }
      ;
      {
        adler += buf[(((0 + 4) + 2) + 1) + buf_idx];
        sum2 += adler;
      }
      ;
      ;
      ;
      ;
      {
        adler += buf[8 + buf_idx];
        sum2 += adler;
      }
      ;
      {
        adler += buf[(8 + 1) + buf_idx];
        sum2 += adler;
      }
      ;
      ;
      {
        adler += buf[(8 + 2) + buf_idx];
        sum2 += adler;
      }
      ;
      {
        adler += buf[((8 + 2) + 1) + buf_idx];
        sum2 += adler;
      }
      ;
      ;
      ;
      {
        adler += buf[(8 + 4) + buf_idx];
        sum2 += adler;
      }
      ;
      {
        adler += buf[((8 + 4) + 1) + buf_idx];
        sum2 += adler;
      }
      ;
      ;
      {
        adler += buf[((8 + 4) + 2) + buf_idx];
        sum2 += adler;
      }
      ;
      {
        adler += buf[(((8 + 4) + 2) + 1) + buf_idx];
        sum2 += adler;
      }
      ;
      ;
      ;
      ;
      ;
      buf_idx += 16;
    }

    while (len--)
    {
      adler += buf[buf_idx];
      buf_idx += 1;
      sum2 += adler;
    }

    adler %= 65521U;
    sum2 %= 65521U;
  }
  return adler | (sum2 << 16);
}

uLong adler32(uLong adler, const Bytef *buf, uInt len)
{
  return adler32_z(adler, buf, len);
}

static uLong adler32_combine_(uLong adler1, uLong adler2, off_t len2)
{
  unsigned long sum1;
  unsigned long sum2;
  unsigned rem;
  if (len2 < 0)
  {
    return 0xffffffffUL;
  }
  len2 %= 65521U;
  rem = (unsigned) len2;
  sum1 = adler1 & 0xffff;
  sum2 = rem * sum1;
  sum2 %= 65521U;
  sum1 += ((adler2 & 0xffff) + 65521U) - 1;
  sum2 += ((((adler1 >> 16) & 0xffff) + ((adler2 >> 16) & 0xffff)) + 65521U) - rem;
  if (sum1 >= 65521U)
  {
    sum1 -= 65521U;
  }
  if (sum1 >= 65521U)
  {
    sum1 -= 65521U;
  }
  if (sum2 >= (((unsigned long) 65521U) << 1))
  {
    sum2 -= ((unsigned long) 65521U) << 1;
  }
  if (sum2 >= 65521U)
  {
    sum2 -= 65521U;
  }
  return sum1 | (sum2 << 16);
}

uLong adler32_combine(uLong adler1, uLong adler2, off_t len2)
{
  return adler32_combine_(adler1, adler2, len2);
}

uLong adler32_combine64(uLong adler1, uLong adler2, off_t len2)
{
  return adler32_combine_(adler1, adler2, len2);
}

void helper_adler32_z_1(uLong * const adler_ref, z_size_t * const len_ref, unsigned int * const buf_idx_ref, unsigned long * const sum2_ref, unsigned * const n_ref, const Bytef * const buf)
{
  uLong adler = *adler_ref;
  z_size_t len = *len_ref;
  unsigned int buf_idx = *buf_idx_ref;
  unsigned long sum2 = *sum2_ref;
  unsigned n = *n_ref;
  len -= 5552;
  n = 5552 / 16;
  do
  {
    helper_helper_adler32_z_1_1(&adler, &buf_idx, &sum2, buf);
  }
  while (--n);
  adler %= 65521U;
  sum2 %= 65521U;
  *adler_ref = adler;
  *len_ref = len;
  *buf_idx_ref = buf_idx;
  *sum2_ref = sum2;
  *n_ref = n;
}

void helper_adler32_z_2(uLong * const adler_ref, z_size_t * const len_ref, unsigned int * const buf_idx_ref, unsigned long * const sum2_ref, const Bytef * const buf)
{
  uLong adler = *adler_ref;
  z_size_t len = *len_ref;
  unsigned int buf_idx = *buf_idx_ref;
  unsigned long sum2 = *sum2_ref;
  while (len >= 16)
  {
    helper_helper_adler32_z_2_1(&adler, &len, &buf_idx, &sum2, buf);
  }

  while (len--)
  {
    adler += buf[buf_idx];
    buf_idx += 1;
    sum2 += adler;
  }

  adler %= 65521U;
  sum2 %= 65521U;
  *adler_ref = adler;
  *len_ref = len;
  *buf_idx_ref = buf_idx;
  *sum2_ref = sum2;
}

void helper_helper_adler32_z_1_1(uLong * const adler_ref, unsigned int * const buf_idx_ref, unsigned long * const sum2_ref, const Bytef * const buf)
{
  uLong adler = *adler_ref;
  unsigned int buf_idx = *buf_idx_ref;
  unsigned long sum2 = *sum2_ref;
  {
    adler += buf[0 + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[(0 + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  {
    adler += buf[(0 + 2) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[((0 + 2) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  ;
  {
    adler += buf[(0 + 4) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[((0 + 4) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  {
    adler += buf[((0 + 4) + 2) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[(((0 + 4) + 2) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  ;
  ;
  {
    adler += buf[8 + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[(8 + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  {
    adler += buf[(8 + 2) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[((8 + 2) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  ;
  {
    adler += buf[(8 + 4) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[((8 + 4) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  {
    adler += buf[((8 + 4) + 2) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[(((8 + 4) + 2) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  ;
  ;
  ;
  buf_idx += 16;
  *adler_ref = adler;
  *buf_idx_ref = buf_idx;
  *sum2_ref = sum2;
}

void helper_helper_adler32_z_2_1(uLong * const adler_ref, z_size_t * const len_ref, unsigned int * const buf_idx_ref, unsigned long * const sum2_ref, const Bytef * const buf)
{
  uLong adler = *adler_ref;
  z_size_t len = *len_ref;
  unsigned int buf_idx = *buf_idx_ref;
  unsigned long sum2 = *sum2_ref;
  len -= 16;
  {
    adler += buf[0 + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[(0 + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  {
    adler += buf[(0 + 2) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[((0 + 2) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  ;
  {
    adler += buf[(0 + 4) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[((0 + 4) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  {
    adler += buf[((0 + 4) + 2) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[(((0 + 4) + 2) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  ;
  ;
  {
    adler += buf[8 + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[(8 + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  {
    adler += buf[(8 + 2) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[((8 + 2) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  ;
  {
    adler += buf[(8 + 4) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[((8 + 4) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  {
    adler += buf[((8 + 4) + 2) + buf_idx];
    sum2 += adler;
  }
  ;
  {
    adler += buf[(((8 + 4) + 2) + 1) + buf_idx];
    sum2 += adler;
  }
  ;
  ;
  ;
  ;
  ;
  buf_idx += 16;
  *adler_ref = adler;
  *len_ref = len;
  *buf_idx_ref = buf_idx;
  *sum2_ref = sum2;
}

