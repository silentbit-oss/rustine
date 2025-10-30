#include <inffast.c>
#include <inffast.h>
#include <inflate.h>
#include <inftrees.h>
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
typedef struct 
{
  unsigned char op;
  unsigned char bits;
  unsigned short val;
} code;
typedef enum 
{
  CODES,
  LENS,
  DISTS
} codetype;
int inflate_table(codetype type, unsigned short *lens, unsigned codes, code **table, unsigned *bits, unsigned short *work);
typedef enum 
{
  HEAD = 16180,
  FLAGS,
  TIME,
  OS,
  EXLEN,
  EXTRA,
  NAME,
  COMMENT,
  HCRC,
  DICTID,
  DICT,
  TYPE,
  TYPEDO,
  STORED,
  COPY_,
  COPY,
  TABLE,
  LENLENS,
  CODELENS,
  LEN_,
  LEN,
  LENEXT,
  DIST,
  DISTEXT,
  MATCH,
  LIT,
  CHECK,
  LENGTH,
  DONE,
  BAD,
  MEM,
  SYNC
} inflate_mode;
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
};
void inflate_fast(z_streamp strm, unsigned start);
void inflate_fast(z_streamp strm, unsigned start)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  const unsigned char *in;
  unsigned int in_idx = 0;
  const unsigned char *last;
  unsigned int last_idx = 0;
  unsigned char *out;
  unsigned int out_idx = 0;
  unsigned char *beg;
  unsigned int beg_idx = 0;
  unsigned char *end;
  unsigned int end_idx = 0;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned int window_idx = 0;
  unsigned long hold;
  unsigned bits;
  const code *lcode;
  unsigned int lcode_idx = 0;
  const code *dcode;
  unsigned int dcode_idx = 0;
  unsigned lmask;
  unsigned dmask;
  const code *here;
  unsigned int here_idx = 0;
  unsigned op;
  unsigned len;
  unsigned dist;
  unsigned char *from;
  unsigned int from_idx = 0;
  state_idx = (struct inflate_state *) strm->state_idx;
  in_idx = strm->next_in;
  last_idx = (&in[in_idx]) + (strm->avail_in - 5);
  out_idx = strm->next_out;
  beg_idx = (&out[out_idx]) - (start - strm->avail_out);
  end_idx = (&out[out_idx]) + (strm->avail_out - 257);
  wsize = state->wsize;
  whave = state->whave;
  wnext = state->wnext;
  window_idx = state->window_idx;
  hold = state->hold;
  bits = state->bits;
  lcode_idx = state->lencode;
  dcode_idx = state->distcode;
  lmask = (1U << state->lenbits) - 1;
  dmask = (1U << state->distbits) - 1;
  do
  {
    helper_inflate_fast_1(&strm, &in_idx, &out_idx, &hold, &bits, &here_idx, &op, &len, &dist, &from_idx, state, in, out, beg, beg_idx, wsize, whave, wnext, window, window_idx, lcode, lcode_idx, dcode, dcode_idx, lmask, dmask, here, from);
  }
  while (((&in[in_idx]) < (&last[last_idx])) && ((&out[out_idx]) < (&end[end_idx])));
  len = bits >> 3;
  in_idx -= len;
  bits -= len << 3;
  hold &= (1U << bits) - 1;
  strm->next_in = &in[in_idx];
  strm->next_out = &out[out_idx];
  strm->avail_in = (unsigned) (((&in[in_idx]) < (&last[last_idx])) ? (5 + ((&last[last_idx]) - (&in[in_idx]))) : (5 - ((&in[in_idx]) - (&last[last_idx]))));
  strm->avail_out = (unsigned) (((&out[out_idx]) < (&end[end_idx])) ? (257 + ((&end[end_idx]) - (&out[out_idx]))) : (257 - ((&out[out_idx]) - (&end[end_idx]))));
  state->hold = hold;
  state->bits = bits;
  return;
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
typedef struct 
{
  unsigned char op;
  unsigned char bits;
  unsigned short val;
} code;
typedef enum 
{
  CODES,
  LENS,
  DISTS
} codetype;
int inflate_table(codetype type, unsigned short *lens, unsigned codes, code **table, unsigned *bits, unsigned short *work);
typedef enum 
{
  HEAD = 16180,
  FLAGS,
  TIME,
  OS,
  EXLEN,
  EXTRA,
  NAME,
  COMMENT,
  HCRC,
  DICTID,
  DICT,
  TYPE,
  TYPEDO,
  STORED,
  COPY_,
  COPY,
  TABLE,
  LENLENS,
  CODELENS,
  LEN_,
  LEN,
  LENEXT,
  DIST,
  DISTEXT,
  MATCH,
  LIT,
  CHECK,
  LENGTH,
  DONE,
  BAD,
  MEM,
  SYNC
} inflate_mode;
struct inflate_state
{
  z_streamp strm;
  inflate_mode mode;
  int last;
  int wrap;
  int havedict;
  int flags;
  unsigned dmax;
  unsigned long check;
  unsigned long total;
  gz_headerp head;
  unsigned wbits;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned long hold;
  unsigned bits;
  unsigned length;
  unsigned offset;
  unsigned extra;
  const code *lencode;
  const code *distcode;
  unsigned lenbits;
  unsigned distbits;
  unsigned ncode;
  unsigned nlen;
  unsigned ndist;
  unsigned have;
  code *next;
  unsigned short lens[320];
  unsigned short work[288];
  code codes[852 + 592];
  int sane;
  int back;
  unsigned was;
};
void inflate_fast(z_streamp strm, unsigned start);
void inflate_fast(z_streamp strm, unsigned start)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  const unsigned char *in;
  unsigned int in_idx = 0;
  const unsigned char *last;
  unsigned int last_idx = 0;
  unsigned char *out;
  unsigned int out_idx = 0;
  unsigned char *beg;
  unsigned int beg_idx = 0;
  unsigned char *end;
  unsigned int end_idx = 0;
  unsigned wsize;
  unsigned whave;
  unsigned wnext;
  unsigned char *window;
  unsigned int window_idx = 0;
  unsigned long hold;
  unsigned bits;
  const code *lcode;
  unsigned int lcode_idx = 0;
  const code *dcode;
  unsigned int dcode_idx = 0;
  unsigned lmask;
  unsigned dmask;
  const code *here;
  unsigned int here_idx = 0;
  unsigned op;
  unsigned len;
  unsigned dist;
  unsigned char *from;
  unsigned int from_idx = 0;
  state_idx = (struct inflate_state *) strm->state_idx;
  in_idx = strm->next_in;
  last_idx = (&in[in_idx]) + (strm->avail_in - 5);
  out_idx = strm->next_out;
  beg_idx = (&out[out_idx]) - (start - strm->avail_out);
  end_idx = (&out[out_idx]) + (strm->avail_out - 257);
  wsize = state->wsize;
  whave = state->whave;
  wnext = state->wnext;
  window_idx = state->window_idx;
  hold = state->hold;
  bits = state->bits;
  lcode_idx = state->lencode;
  dcode_idx = state->distcode;
  lmask = (1U << state->lenbits) - 1;
  dmask = (1U << state->distbits) - 1;
  do
  {
    if (bits < 15)
    {
      hold += ((unsigned long) in[in_idx]) << bits;
      in_idx += 1;
      bits += 8;
      hold += ((unsigned long) in[in_idx]) << bits;
      in_idx += 1;
      bits += 8;
    }
    here_idx = (&lcode[lcode_idx]) + (hold & lmask);
    dolen:
    op = (unsigned) here->bits;

    hold >>= op;
    bits -= op;
    op = (unsigned) here->op;
    if (op == 0)
    {
      ;
      out[out_idx] = (unsigned char) here->val;
      out_idx += 1;
    }
    else
      if (op & 16)
    {
      len = (unsigned) here->val;
      op &= 15;
      if (op)
      {
        if (bits < op)
        {
          hold += ((unsigned long) in[in_idx]) << bits;
          in_idx += 1;
          bits += 8;
        }
        len += ((unsigned) hold) & ((1U << op) - 1);
        hold >>= op;
        bits -= op;
      }
      ;
      if (bits < 15)
      {
        hold += ((unsigned long) in[in_idx]) << bits;
        in_idx += 1;
        bits += 8;
        hold += ((unsigned long) in[in_idx]) << bits;
        in_idx += 1;
        bits += 8;
      }
      here_idx = (&dcode[dcode_idx]) + (hold & dmask);
      dodist:
      op = (unsigned) here->bits;

      hold >>= op;
      bits -= op;
      op = (unsigned) here->op;
      if (op & 16)
      {
        dist = (unsigned) here->val;
        op &= 15;
        if (bits < op)
        {
          hold += ((unsigned long) in[in_idx]) << bits;
          in_idx += 1;
          bits += 8;
          if (bits < op)
          {
            hold += ((unsigned long) in[in_idx]) << bits;
            in_idx += 1;
            bits += 8;
          }
        }
        dist += ((unsigned) hold) & ((1U << op) - 1);
        hold >>= op;
        bits -= op;
        ;
        op = (unsigned) ((&out[out_idx]) - (&beg[beg_idx]));
        if (dist > op)
        {
          op = dist - op;
          if (op > whave)
          {
            if (state->sane)
            {
              strm->msg = (char *) "invalid distance too far back";
              state->mode = BAD;
              break;
            }
          }
          from_idx = &window[window_idx];
          if (wnext == 0)
          {
            from_idx += wsize - op;
            if (op < len)
            {
              len -= op;
              do
              {
                out[out_idx] = from[from_idx];
                from_idx += 1;
                out_idx += 1;
              }
              while (--op);
              from_idx = (&out[out_idx]) - dist;
            }
          }
          else
            if (wnext < op)
          {
            from_idx += (wsize + wnext) - op;
            op -= wnext;
            if (op < len)
            {
              len -= op;
              do
              {
                out[out_idx] = from[from_idx];
                from_idx += 1;
                out_idx += 1;
              }
              while (--op);
              from_idx = &window[window_idx];
              if (wnext < len)
              {
                op = wnext;
                len -= op;
                do
                {
                  out[out_idx] = from[from_idx];
                  from_idx += 1;
                  out_idx += 1;
                }
                while (--op);
                from_idx = (&out[out_idx]) - dist;
              }
            }
          }
          else
          {
            from_idx += wnext - op;
            if (op < len)
            {
              len -= op;
              do
              {
                out[out_idx] = from[from_idx];
                from_idx += 1;
                out_idx += 1;
              }
              while (--op);
              from_idx = (&out[out_idx]) - dist;
            }
          }
          while (len > 2)
          {
            out[out_idx] = from[from_idx];
            from_idx += 1;
            out_idx += 1;
            out[out_idx] = from[from_idx];
            from_idx += 1;
            out_idx += 1;
            out[out_idx] = from[from_idx];
            from_idx += 1;
            out_idx += 1;
            len -= 3;
          }

          if (len)
          {
            out[out_idx] = from[from_idx];
            from_idx += 1;
            out_idx += 1;
            if (len > 1)
            {
              out[out_idx] = from[from_idx];
              from_idx += 1;
              out_idx += 1;
            }
          }
        }
        else
        {
          from_idx = (&out[out_idx]) - dist;
          do
          {
            out[out_idx] = from[from_idx];
            from_idx += 1;
            out_idx += 1;
            out[out_idx] = from[from_idx];
            from_idx += 1;
            out_idx += 1;
            out[out_idx] = from[from_idx];
            from_idx += 1;
            out_idx += 1;
            len -= 3;
          }
          while (len > 2);
          if (len)
          {
            out[out_idx] = from[from_idx];
            from_idx += 1;
            out_idx += 1;
            if (len > 1)
            {
              out[out_idx] = from[from_idx];
              from_idx += 1;
              out_idx += 1;
            }
          }
        }
      }
      else
        if ((op & 64) == 0)
      {
        here_idx = ((&dcode[dcode_idx]) + here_idx->val) + (hold & ((1U << op) - 1));
        goto dodist;
      }
      else
      {
        strm->msg = (char *) "invalid distance code";
        state->mode = BAD;
        break;
      }
    }
    else
      if ((op & 64) == 0)
    {
      here_idx = ((&lcode[lcode_idx]) + here_idx->val) + (hold & ((1U << op) - 1));
      goto dolen;
    }
    else
      if (op & 32)
    {
      ;
      state->mode = TYPE;
      break;
    }
    else
    {
      strm->msg = (char *) "invalid literal/length code";
      state->mode = BAD;
      break;
    }
  }
  while (((&in[in_idx]) < (&last[last_idx])) && ((&out[out_idx]) < (&end[end_idx])));
  len = bits >> 3;
  in_idx -= len;
  bits -= len << 3;
  hold &= (1U << bits) - 1;
  strm->next_in = &in[in_idx];
  strm->next_out = &out[out_idx];
  strm->avail_in = (unsigned) (((&in[in_idx]) < (&last[last_idx])) ? (5 + ((&last[last_idx]) - (&in[in_idx]))) : (5 - ((&in[in_idx]) - (&last[last_idx]))));
  strm->avail_out = (unsigned) (((&out[out_idx]) < (&end[end_idx])) ? (257 + ((&end[end_idx]) - (&out[out_idx]))) : (257 - ((&out[out_idx]) - (&end[end_idx]))));
  state->hold = hold;
  state->bits = bits;
  return;
}

void helper_inflate_fast_1(z_streamp * const strm_ref, unsigned int * const in_idx_ref, unsigned int * const out_idx_ref, unsigned long * const hold_ref, unsigned * const bits_ref, unsigned int * const here_idx_ref, unsigned * const op_ref, unsigned * const len_ref, unsigned * const dist_ref, unsigned int * const from_idx_ref, struct inflate_state * const state, const unsigned char * const in, unsigned char * const out, unsigned char * const beg, unsigned int beg_idx, unsigned wsize, unsigned whave, unsigned wnext, unsigned char * const window, unsigned int window_idx, const code * const lcode, unsigned int lcode_idx, const code * const dcode, unsigned int dcode_idx, unsigned lmask, unsigned dmask, const code * const here, unsigned char * const from)
{
  z_streamp strm = *strm_ref;
  unsigned int in_idx = *in_idx_ref;
  unsigned int out_idx = *out_idx_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  unsigned int here_idx = *here_idx_ref;
  unsigned op = *op_ref;
  unsigned len = *len_ref;
  unsigned dist = *dist_ref;
  unsigned int from_idx = *from_idx_ref;
  if (bits < 15)
  {
    hold += ((unsigned long) in[in_idx]) << bits;
    in_idx += 1;
    bits += 8;
    hold += ((unsigned long) in[in_idx]) << bits;
    in_idx += 1;
    bits += 8;
  }
  here_idx = (&lcode[lcode_idx]) + (hold & lmask);
  dolen:
  op = (unsigned) here->bits;

  hold >>= op;
  bits -= op;
  op = (unsigned) here->op;
  if (op == 0)
  {
    ;
    out[out_idx] = (unsigned char) here->val;
    out_idx += 1;
  }
  else
    if (op & 16)
  {
    helper_helper_inflate_fast_1_1(&strm, &in_idx, &out_idx, &hold, &bits, &here_idx, &op, &len, &dist, &from_idx, state, in, out, beg, beg_idx, wsize, whave, wnext, window, window_idx, dcode, dcode_idx, dmask, here, from);
  }
  else
    if ((op & 64) == 0)
  {
    here_idx = ((&lcode[lcode_idx]) + here_idx->val) + (hold & ((1U << op) - 1));
    goto dolen;
  }
  else
    if (op & 32)
  {
    ;
    state->mode = TYPE;
    break;
  }
  else
  {
    strm->msg = (char *) "invalid literal/length code";
    state->mode = BAD;
    break;
  }
  *strm_ref = strm;
  *in_idx_ref = in_idx;
  *out_idx_ref = out_idx;
  *hold_ref = hold;
  *bits_ref = bits;
  *here_idx_ref = here_idx;
  *op_ref = op;
  *len_ref = len;
  *dist_ref = dist;
  *from_idx_ref = from_idx;
}

void helper_helper_inflate_fast_1_1(z_streamp * const strm_ref, unsigned int * const in_idx_ref, unsigned int * const out_idx_ref, unsigned long * const hold_ref, unsigned * const bits_ref, unsigned int * const here_idx_ref, unsigned * const op_ref, unsigned * const len_ref, unsigned * const dist_ref, unsigned int * const from_idx_ref, struct inflate_state * const state, const unsigned char * const in, unsigned char * const out, unsigned char * const beg, unsigned int beg_idx, unsigned wsize, unsigned whave, unsigned wnext, unsigned char * const window, unsigned int window_idx, const code * const dcode, unsigned int dcode_idx, unsigned dmask, const code * const here, unsigned char * const from)
{
  z_streamp strm = *strm_ref;
  unsigned int in_idx = *in_idx_ref;
  unsigned int out_idx = *out_idx_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  unsigned int here_idx = *here_idx_ref;
  unsigned op = *op_ref;
  unsigned len = *len_ref;
  unsigned dist = *dist_ref;
  unsigned int from_idx = *from_idx_ref;
  len = (unsigned) here->val;
  op &= 15;
  if (op)
  {
    if (bits < op)
    {
      hold += ((unsigned long) in[in_idx]) << bits;
      in_idx += 1;
      bits += 8;
    }
    len += ((unsigned) hold) & ((1U << op) - 1);
    hold >>= op;
    bits -= op;
  }
  ;
  if (bits < 15)
  {
    hold += ((unsigned long) in[in_idx]) << bits;
    in_idx += 1;
    bits += 8;
    hold += ((unsigned long) in[in_idx]) << bits;
    in_idx += 1;
    bits += 8;
  }
  here_idx = (&dcode[dcode_idx]) + (hold & dmask);
  dodist:
  op = (unsigned) here->bits;

  hold >>= op;
  bits -= op;
  op = (unsigned) here->op;
  if (op & 16)
  {
    helper_helper_helper_inflate_fast_1_1_1(&strm, &in_idx, &out_idx, &hold, &bits, &op, &len, &dist, &from_idx, state, in, out, beg, beg_idx, wsize, whave, wnext, window, window_idx, here, from);
  }
  else
    if ((op & 64) == 0)
  {
    here_idx = ((&dcode[dcode_idx]) + here_idx->val) + (hold & ((1U << op) - 1));
    goto dodist;
  }
  else
  {
    strm->msg = (char *) "invalid distance code";
    state->mode = BAD;
    break;
  }
  *strm_ref = strm;
  *in_idx_ref = in_idx;
  *out_idx_ref = out_idx;
  *hold_ref = hold;
  *bits_ref = bits;
  *here_idx_ref = here_idx;
  *op_ref = op;
  *len_ref = len;
  *dist_ref = dist;
  *from_idx_ref = from_idx;
}

void helper_helper_helper_inflate_fast_1_1_1(z_streamp * const strm_ref, unsigned int * const in_idx_ref, unsigned int * const out_idx_ref, unsigned long * const hold_ref, unsigned * const bits_ref, unsigned * const op_ref, unsigned * const len_ref, unsigned * const dist_ref, unsigned int * const from_idx_ref, struct inflate_state * const state, const unsigned char * const in, unsigned char * const out, unsigned char * const beg, unsigned int beg_idx, unsigned wsize, unsigned whave, unsigned wnext, unsigned char * const window, unsigned int window_idx, const code * const here, unsigned char * const from)
{
  z_streamp strm = *strm_ref;
  unsigned int in_idx = *in_idx_ref;
  unsigned int out_idx = *out_idx_ref;
  unsigned long hold = *hold_ref;
  unsigned bits = *bits_ref;
  unsigned op = *op_ref;
  unsigned len = *len_ref;
  unsigned dist = *dist_ref;
  unsigned int from_idx = *from_idx_ref;
  dist = (unsigned) here->val;
  op &= 15;
  if (bits < op)
  {
    hold += ((unsigned long) in[in_idx]) << bits;
    in_idx += 1;
    bits += 8;
    if (bits < op)
    {
      hold += ((unsigned long) in[in_idx]) << bits;
      in_idx += 1;
      bits += 8;
    }
  }
  dist += ((unsigned) hold) & ((1U << op) - 1);
  hold >>= op;
  bits -= op;
  ;
  op = (unsigned) ((&out[out_idx]) - (&beg[beg_idx]));
  if (dist > op)
  {
    helper_helper_helper_helper_inflate_fast_1_1_1_2(&strm, &out_idx, &op, &len, &from_idx, state, out, wsize, whave, wnext, window, window_idx, from, dist);
  }
  else
  {
    helper_helper_helper_helper_inflate_fast_1_1_1_1(&out_idx, &len, &from_idx, out, from, dist);
  }
  *strm_ref = strm;
  *in_idx_ref = in_idx;
  *out_idx_ref = out_idx;
  *hold_ref = hold;
  *bits_ref = bits;
  *op_ref = op;
  *len_ref = len;
  *dist_ref = dist;
  *from_idx_ref = from_idx;
}

void helper_helper_helper_helper_inflate_fast_1_1_1_1(unsigned int * const out_idx_ref, unsigned * const len_ref, unsigned int * const from_idx_ref, unsigned char * const out, unsigned char * const from, unsigned dist)
{
  unsigned int out_idx = *out_idx_ref;
  unsigned len = *len_ref;
  unsigned int from_idx = *from_idx_ref;
  from_idx = (&out[out_idx]) - dist;
  do
  {
    out[out_idx] = from[from_idx];
    from_idx += 1;
    out_idx += 1;
    out[out_idx] = from[from_idx];
    from_idx += 1;
    out_idx += 1;
    out[out_idx] = from[from_idx];
    from_idx += 1;
    out_idx += 1;
    len -= 3;
  }
  while (len > 2);
  if (len)
  {
    out[out_idx] = from[from_idx];
    from_idx += 1;
    out_idx += 1;
    if (len > 1)
    {
      out[out_idx] = from[from_idx];
      from_idx += 1;
      out_idx += 1;
    }
  }
  *out_idx_ref = out_idx;
  *len_ref = len;
  *from_idx_ref = from_idx;
}

void helper_helper_helper_helper_inflate_fast_1_1_1_2(z_streamp * const strm_ref, unsigned int * const out_idx_ref, unsigned * const op_ref, unsigned * const len_ref, unsigned int * const from_idx_ref, struct inflate_state * const state, unsigned char * const out, unsigned wsize, unsigned whave, unsigned wnext, unsigned char * const window, unsigned int window_idx, unsigned char * const from, unsigned dist)
{
  z_streamp strm = *strm_ref;
  unsigned int out_idx = *out_idx_ref;
  unsigned op = *op_ref;
  unsigned len = *len_ref;
  unsigned int from_idx = *from_idx_ref;
  op = dist - op;
  if (op > whave)
  {
    if (state->sane)
    {
      strm->msg = (char *) "invalid distance too far back";
      state->mode = BAD;
      break;
    }
  }
  from_idx = &window[window_idx];
  if (wnext == 0)
  {
    from_idx += wsize - op;
    if (op < len)
    {
      len -= op;
      do
      {
        out[out_idx] = from[from_idx];
        from_idx += 1;
        out_idx += 1;
      }
      while (--op);
      from_idx = (&out[out_idx]) - dist;
    }
  }
  else
    if (wnext < op)
  {
    from_idx += (wsize + wnext) - op;
    op -= wnext;
    if (op < len)
    {
      len -= op;
      do
      {
        out[out_idx] = from[from_idx];
        from_idx += 1;
        out_idx += 1;
      }
      while (--op);
      from_idx = &window[window_idx];
      if (wnext < len)
      {
        op = wnext;
        len -= op;
        do
        {
          out[out_idx] = from[from_idx];
          from_idx += 1;
          out_idx += 1;
        }
        while (--op);
        from_idx = (&out[out_idx]) - dist;
      }
    }
  }
  else
  {
    from_idx += wnext - op;
    if (op < len)
    {
      len -= op;
      do
      {
        out[out_idx] = from[from_idx];
        from_idx += 1;
        out_idx += 1;
      }
      while (--op);
      from_idx = (&out[out_idx]) - dist;
    }
  }
  while (len > 2)
  {
    out[out_idx] = from[from_idx];
    from_idx += 1;
    out_idx += 1;
    out[out_idx] = from[from_idx];
    from_idx += 1;
    out_idx += 1;
    out[out_idx] = from[from_idx];
    from_idx += 1;
    out_idx += 1;
    len -= 3;
  }

  if (len)
  {
    out[out_idx] = from[from_idx];
    from_idx += 1;
    out_idx += 1;
    if (len > 1)
    {
      out[out_idx] = from[from_idx];
      from_idx += 1;
      out_idx += 1;
    }
  }
  *strm_ref = strm;
  *out_idx_ref = out_idx;
  *op_ref = op;
  *len_ref = len;
  *from_idx_ref = from_idx;
}

