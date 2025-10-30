#include <limits.h>
#include <minigzip.c>
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
static char *prog;
void error(const char *msg)
{
  fprintf(stderr, "%s: %s\n", prog, msg);
  exit(1);
}

void gz_compress(FILE *in, gzFile out)
{
  char buf[16384];
  int len;
  int err;
  for (;;)
  {
    len = (int) fread(buf, 1, sizeof(buf), in);
    if (ferror(in))
    {
      perror("fread");
      exit(1);
    }
    if (len == 0)
    {
      break;
    }
    if (gzwrite(out, buf, (unsigned) len) != len)
    {
      error(gzerror(out, &err));
    }
  }

  fclose(in);
  if (gzclose(out) != 0)
  {
    error("failed gzclose");
  }
}

void gz_uncompress(gzFile in, FILE *out)
{
  char buf[16384];
  int len;
  int err;
  for (;;)
  {
    len = gzread(in, buf, sizeof(buf));
    if (len < 0)
    {
      error(gzerror(in, &err));
    }
    if (len == 0)
    {
      break;
    }
    if (((int) fwrite(buf, 1, (unsigned) len, out)) != len)
    {
      error("failed fwrite");
    }
  }

  if (fclose(out))
  {
    error("failed fclose");
  }
  if (gzclose(in) != 0)
  {
    error("failed gzclose");
  }
}

void file_compress(char *file, char *mode)
{
  char outfile[1024];
  FILE *in;
  unsigned int in_idx = 0;
  gzFile out;
  if ((strlen(file) + strlen(".gz")) >= (sizeof(outfile)))
  {
    fprintf(stderr, "%s: filename too long\n", prog);
    exit(1);
  }
  snprintf(outfile, sizeof(outfile), "%s%s", file, ".gz");
  in_idx = fopen(file, "rb");
  if ((&in[in_idx]) == 0)
  {
    perror(file);
    exit(1);
  }
  out = gzopen(outfile, mode);
  if (out == 0)
  {
    fprintf(stderr, "%s: can't gzopen %s\n", prog, outfile);
    exit(1);
  }
  gz_compress(in, out);
  unlink(file);
}

void file_uncompress(char *file)
{
  char buf[1024];
  char *infile;
  unsigned int infile_idx = 0;
  char *outfile;
  unsigned int outfile_idx = 0;
  FILE *out;
  unsigned int out_idx = 0;
  gzFile in;
  z_size_t len = strlen(file);
  if ((len + strlen(".gz")) >= (sizeof(buf)))
  {
    fprintf(stderr, "%s: filename too long\n", prog);
    exit(1);
  }
  snprintf(buf, sizeof(buf), "%s", file);
  if ((len > ((sizeof(".gz")) - 1)) && (strcmp((file + len) - ((sizeof(".gz")) - 1), ".gz") == 0))
  {
    infile_idx = file;
    outfile_idx = buf;
    outfile[(len - 3) + outfile_idx] = '\0';
  }
  else
  {
    outfile_idx = file;
    infile_idx = buf;
    snprintf(buf + len, (sizeof(buf)) - len, "%s", ".gz");
  }
  in = gzopen(infile, "rb");
  if (in == 0)
  {
    fprintf(stderr, "%s: can't gzopen %s\n", prog, infile);
    exit(1);
  }
  out_idx = fopen(outfile, "wb");
  if ((&out[out_idx]) == 0)
  {
    perror(file);
    exit(1);
  }
  gz_uncompress(in, out);
  unlink(infile);
}

int main(int argc, char *argv[])
{
  int copyout = 0;
  int uncompr = 0;
  gzFile file;
  char *bname;
  unsigned int bname_idx = 0;
  char outmode[20];
  snprintf(outmode, sizeof(outmode), "%s", "wb6 ");
  prog = argv[0];
  bname_idx = strrchr(argv[0], '/');
  if (bname)
  {
    bname_idx += 1;
  }
  else
    bname_idx = argv[0];
  argc--, argv++;
  argv += 1;
  argc -= 1;
  if (!strcmp(bname, "gunzip"))
  {
    uncompr = 1;
  }
  else
    if (!strcmp(bname, "zcat"))
  {
    copyout = (uncompr = 1);
  }
  while (argc > 0)
  {
    if (strcmp(*argv, "-c") == 0)
    {
      copyout = 1;
    }
    else
      if (strcmp(*argv, "-d") == 0)
    {
      uncompr = 1;
    }
    else
      if (strcmp(*argv, "-f") == 0)
    {
      outmode[3] = 'f';
    }
    else
      if (strcmp(*argv, "-h") == 0)
    {
      outmode[3] = 'h';
    }
    else
      if (strcmp(*argv, "-r") == 0)
    {
      outmode[3] = 'R';
    }
    else
      if (((((*argv)[0] == '-') && ((*argv)[1] >= '1')) && ((*argv)[1] <= '9')) && ((*argv)[2] == 0))
    {
      outmode[2] = (*argv)[1];
    }
    else
      break;
    argc--, argv++;
    argv += 1;
    argc -= 1;
  }

  if (outmode[3] == ' ')
  {
    outmode[3] = 0;
  }
  if (argc == 0)
  {
    ;
    ;
    if (uncompr)
    {
      file = gzdopen(fileno(stdin), "rb");
      if (file == 0)
      {
        error("can't gzdopen stdin");
      }
      gz_uncompress(file, stdout);
    }
    else
    {
      file = gzdopen(fileno(stdout), outmode);
      if (file == 0)
      {
        error("can't gzdopen stdout");
      }
      gz_compress(stdin, file);
    }
  }
  else
  {
    if (copyout)
    {
      ;
    }
    do
    {
      if (uncompr)
      {
        if (copyout)
        {
          file = gzopen(*argv, "rb");
          if (file == 0)
          {
            fprintf(stderr, "%s: can't gzopen %s\n", prog, *argv);
          }
          else
            gz_uncompress(file, stdout);
        }
        else
        {
          file_uncompress(*argv);
        }
      }
      else
      {
        if (copyout)
        {
          FILE *in = fopen(*argv, "rb");
          if (in == 0)
          {
            perror(*argv);
          }
          else
          {
            file = gzdopen(fileno(stdout), outmode);
            if (file == 0)
            {
              error("can't gzdopen stdout");
            }
            gz_compress(in, file);
          }
        }
        else
        {
          file_compress(*argv, outmode);
        }
      }
    }
    while (argv++, --argc);
  }
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
static char *prog;
void error(const char *msg)
{
  fprintf(stderr, "%s: %s\n", prog, msg);
  exit(1);
}

void gz_compress(FILE *in, gzFile out)
{
  char buf[16384];
  int len;
  int err;
  for (;;)
  {
    len = (int) fread(buf, 1, sizeof(buf), in);
    if (ferror(in))
    {
      perror("fread");
      exit(1);
    }
    if (len == 0)
    {
      break;
    }
    if (gzwrite(out, buf, (unsigned) len) != len)
    {
      error(gzerror(out, &err));
    }
  }

  fclose(in);
  if (gzclose(out) != 0)
  {
    error("failed gzclose");
  }
}

void gz_uncompress(gzFile in, FILE *out)
{
  char buf[16384];
  int len;
  int err;
  for (;;)
  {
    len = gzread(in, buf, sizeof(buf));
    if (len < 0)
    {
      error(gzerror(in, &err));
    }
    if (len == 0)
    {
      break;
    }
    if (((int) fwrite(buf, 1, (unsigned) len, out)) != len)
    {
      error("failed fwrite");
    }
  }

  if (fclose(out))
  {
    error("failed fclose");
  }
  if (gzclose(in) != 0)
  {
    error("failed gzclose");
  }
}

void file_compress(char *file, char *mode)
{
  char outfile[1024];
  FILE *in;
  unsigned int in_idx = 0;
  gzFile out;
  if ((strlen(file) + strlen(".gz")) >= (sizeof(outfile)))
  {
    fprintf(stderr, "%s: filename too long\n", prog);
    exit(1);
  }
  snprintf(outfile, sizeof(outfile), "%s%s", file, ".gz");
  in_idx = fopen(file, "rb");
  if ((&in[in_idx]) == 0)
  {
    perror(file);
    exit(1);
  }
  out = gzopen(outfile, mode);
  if (out == 0)
  {
    fprintf(stderr, "%s: can't gzopen %s\n", prog, outfile);
    exit(1);
  }
  gz_compress(in, out);
  unlink(file);
}

void file_uncompress(char *file)
{
  char buf[1024];
  char *infile;
  unsigned int infile_idx = 0;
  char *outfile;
  unsigned int outfile_idx = 0;
  FILE *out;
  unsigned int out_idx = 0;
  gzFile in;
  z_size_t len = strlen(file);
  if ((len + strlen(".gz")) >= (sizeof(buf)))
  {
    fprintf(stderr, "%s: filename too long\n", prog);
    exit(1);
  }
  snprintf(buf, sizeof(buf), "%s", file);
  if ((len > ((sizeof(".gz")) - 1)) && (strcmp((file + len) - ((sizeof(".gz")) - 1), ".gz") == 0))
  {
    infile_idx = file;
    outfile_idx = buf;
    outfile[(len - 3) + outfile_idx] = '\0';
  }
  else
  {
    outfile_idx = file;
    infile_idx = buf;
    snprintf(buf + len, (sizeof(buf)) - len, "%s", ".gz");
  }
  in = gzopen(infile, "rb");
  if (in == 0)
  {
    fprintf(stderr, "%s: can't gzopen %s\n", prog, infile);
    exit(1);
  }
  out_idx = fopen(outfile, "wb");
  if ((&out[out_idx]) == 0)
  {
    perror(file);
    exit(1);
  }
  gz_uncompress(in, out);
  unlink(infile);
}

int main(int argc, char *argv[])
{
  int copyout = 0;
  int uncompr = 0;
  gzFile file;
  char *bname;
  unsigned int bname_idx = 0;
  char outmode[20];
  snprintf(outmode, sizeof(outmode), "%s", "wb6 ");
  prog = argv[0];
  bname_idx = strrchr(argv[0], '/');
  if (bname)
  {
    bname_idx += 1;
  }
  else
    bname_idx = argv[0];
  argc--, argv++;
  argv += 1;
  argc -= 1;
  if (!strcmp(bname, "gunzip"))
  {
    uncompr = 1;
  }
  else
    if (!strcmp(bname, "zcat"))
  {
    copyout = (uncompr = 1);
  }
  while (argc > 0)
  {
    if (strcmp(*argv, "-c") == 0)
    {
      copyout = 1;
    }
    else
      if (strcmp(*argv, "-d") == 0)
    {
      uncompr = 1;
    }
    else
      if (strcmp(*argv, "-f") == 0)
    {
      outmode[3] = 'f';
    }
    else
      if (strcmp(*argv, "-h") == 0)
    {
      outmode[3] = 'h';
    }
    else
      if (strcmp(*argv, "-r") == 0)
    {
      outmode[3] = 'R';
    }
    else
      if (((((*argv)[0] == '-') && ((*argv)[1] >= '1')) && ((*argv)[1] <= '9')) && ((*argv)[2] == 0))
    {
      outmode[2] = (*argv)[1];
    }
    else
      break;
    argc--, argv++;
    argv += 1;
    argc -= 1;
  }

  if (outmode[3] == ' ')
  {
    outmode[3] = 0;
  }
  if (argc == 0)
  {
    ;
    ;
    if (uncompr)
    {
      file = gzdopen(fileno(stdin), "rb");
      if (file == 0)
      {
        error("can't gzdopen stdin");
      }
      gz_uncompress(file, stdout);
    }
    else
    {
      file = gzdopen(fileno(stdout), outmode);
      if (file == 0)
      {
        error("can't gzdopen stdout");
      }
      gz_compress(stdin, file);
    }
  }
  else
  {
    if (copyout)
    {
      ;
    }
    do
    {
      if (uncompr)
      {
        if (copyout)
        {
          file = gzopen(*argv, "rb");
          if (file == 0)
          {
            fprintf(stderr, "%s: can't gzopen %s\n", prog, *argv);
          }
          else
            gz_uncompress(file, stdout);
        }
        else
        {
          file_uncompress(*argv);
        }
      }
      else
      {
        if (copyout)
        {
          FILE *in = fopen(*argv, "rb");
          if (in == 0)
          {
            perror(*argv);
          }
          else
          {
            file = gzdopen(fileno(stdout), outmode);
            if (file == 0)
            {
              error("can't gzdopen stdout");
            }
            gz_compress(in, file);
          }
        }
        else
        {
          file_compress(*argv, outmode);
        }
      }
    }
    while (argv++, --argc);
  }
  return 0;
}

