#include <deflate.c>
#include <deflate.h>
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
typedef struct ct_data_s
{
  union 
  {
    ush freq;
    ush code;
  } fc;
  union 
  {
    ush dad;
    ush len;
  } dl;
} ct_data;
typedef struct static_tree_desc_s static_tree_desc;
typedef struct tree_desc_s
{
  ct_data *dyn_tree;
  int max_code;
  const static_tree_desc *stat_desc;
} tree_desc;
typedef ush Pos;
typedef Pos Posf;
typedef unsigned IPos;
typedef struct internal_state
{
  z_streamp strm;
  int status;
  Bytef *pending_buf;
  ulg pending_buf_size;
  Bytef *pending_out;
  ulg pending;
  int wrap;
  gz_headerp gzhead;
  ulg gzindex;
  Byte method;
  int last_flush;
  uInt w_size;
  uInt w_bits;
  uInt w_mask;
  Bytef *window;
  ulg window_size;
  Posf *prev;
  Posf *head;
  uInt ins_h;
  uInt hash_size;
  uInt hash_bits;
  uInt hash_mask;
  uInt hash_shift;
  long block_start;
  uInt match_length;
  IPos prev_match;
  int match_available;
  uInt strstart;
  uInt match_start;
  uInt lookahead;
  uInt prev_length;
  uInt max_chain_length;
  uInt max_lazy_match;
  int level;
  int strategy;
  uInt good_match;
  int nice_match;
  struct ct_data_s dyn_ltree[(2 * ((256 + 1) + 29)) + 1];
  struct ct_data_s dyn_dtree[(2 * 30) + 1];
  struct ct_data_s bl_tree[(2 * 19) + 1];
  struct tree_desc_s l_desc;
  struct tree_desc_s d_desc;
  struct tree_desc_s bl_desc;
  ush bl_count[15 + 1];
  int heap[(2 * ((256 + 1) + 29)) + 1];
  int heap_len;
  int heap_max;
  uch depth[(2 * ((256 + 1) + 29)) + 1];
  uchf *sym_buf;
  uInt lit_bufsize;
  uInt sym_next;
  uInt sym_end;
  ulg opt_len;
  ulg static_len;
  uInt matches;
  uInt insert;
  ush bi_buf;
  int bi_valid;
  ulg high_water;
} deflate_state;
void _tr_init(deflate_state *s);
int _tr_tally(deflate_state *s, unsigned dist, unsigned lc);
void _tr_flush_block(deflate_state *s, charf *buf, ulg stored_len, int last);
void _tr_flush_bits(deflate_state *s);
void _tr_align(deflate_state *s);
void _tr_stored_block(deflate_state *s, charf *buf, ulg stored_len, int last);
extern const uch _length_code[];
extern const uch _dist_code[];
const char deflate_copyright[] = " deflate 1.3 Copyright 1995-2023 Jean-loup Gailly and Mark Adler ";
typedef enum 
{
  need_more,
  block_done,
  finish_started,
  finish_done
} block_state;
typedef block_state (*compress_func)(deflate_state *s, int flush);
static block_state deflate_stored(deflate_state *s, int flush);
static block_state deflate_fast(deflate_state *s, int flush);
static block_state deflate_slow(deflate_state *s, int flush);
static block_state deflate_rle(deflate_state *s, int flush);
static block_state deflate_huff(deflate_state *s, int flush);
typedef struct config_s
{
  ush good_length;
  ush max_lazy;
  ush nice_length;
  ush max_chain;
  compress_func func;
} config;
static const config configuration_table[10] = {{0, 0, 0, 0, deflate_stored}, {4, 4, 8, 4, deflate_fast}, {4, 5, 16, 8, deflate_fast}, {4, 6, 32, 32, deflate_fast}, {4, 4, 16, 16, deflate_slow}, {8, 16, 32, 32, deflate_slow}, {8, 16, 128, 128, deflate_slow}, {8, 32, 128, 256, deflate_slow}, {32, 128, 258, 1024, deflate_slow}, {32, 258, 258, 4096, deflate_slow}};
static void slide_hash(deflate_state *s)
{
  unsigned n;
  unsigned m;
  Posf *p;
  unsigned int p_idx = 0;
  uInt wsize = s->w_size;
  n = s->hash_size;
  p_idx = &s->head[n];
  do
  {
    p_idx -= 1;
    m = p[p_idx];
    p[p_idx] = (Pos) ((m >= wsize) ? (m - wsize) : (0));
  }
  while (--n);
  n = wsize;
  p_idx = &s->prev[n];
  do
  {
    p_idx -= 1;
    m = p[p_idx];
    p[p_idx] = (Pos) ((m >= wsize) ? (m - wsize) : (0));
  }
  while (--n);
}

static unsigned read_buf(z_streamp strm, Bytef *buf, unsigned size)
{
  unsigned len = strm->avail_in;
  if (len > size)
  {
    len = size;
  }
  if (len == 0)
  {
    return 0;
  }
  strm->avail_in -= len;
  memcpy(buf, strm->next_in, len);
  if (strm->state->wrap == 1)
  {
    strm->adler = adler32(strm->adler, buf, len);
  }
  strm->next_in += len;
  strm->total_in += len;
  return len;
}

static void fill_window(deflate_state *s)
{
  unsigned n;
  unsigned more;
  uInt wsize = s->w_size;
  ;
  do
  {
    helper_fill_window_2(&n, &more, s, wsize);
  }
  while ((s->lookahead < ((258 + 3) + 1)) && (s->strm->avail_in != 0));
  if (s->high_water < s->window_size)
  {
    helper_fill_window_1(s);
  }
  ;
}

int deflateInit_(z_streamp strm, int level, const char *version, int stream_size)
{
  return deflateInit2_(strm, level, 8, 15, 8, 0, version, stream_size);
}

int deflateInit2_(z_streamp strm, int level, int method, int windowBits, int memLevel, int strategy, const char *version, int stream_size)
{
  deflate_state *s;
  unsigned int s_idx = 0;
  int wrap = 1;
  static const char my_version[] = "1.3-optipng";
  if (((version == 0) || (version[0] != my_version[0])) || (stream_size != (sizeof(z_stream))))
  {
    return -6;
  }
  if (strm == 0)
  {
    return -2;
  }
  strm->msg = 0;
  if (strm->zalloc == ((alloc_func) 0))
  {
    strm->zalloc = zcalloc;
    strm->opaque = (voidpf) 0;
  }
  if (strm->zfree == ((free_func) 0))
  {
    strm->zfree = zcfree;
  }
  if (level == (-1))
  {
    level = 6;
  }
  if (windowBits < 0)
  {
    wrap = 0;
    if (windowBits < (-15))
    {
      return -2;
    }
    windowBits = -windowBits;
  }
  if ((((((((((memLevel < 1) || (memLevel > 9)) || (method != 8)) || (windowBits < 8)) || (windowBits > 15)) || (level < 0)) || (level > 9)) || (strategy < 0)) || (strategy > 4)) || ((windowBits == 8) && (wrap != 1)))
  {
    return -2;
  }
  if (windowBits == 8)
  {
    windowBits = 9;
  }
  s_idx = (deflate_state *) (*strm->zalloc)(strm->opaque, 1, sizeof(deflate_state));
  if ((&s[s_idx]) == 0)
  {
    return -4;
  }
  strm->state = (struct internal_state *) s;
  s->strm = strm;
  s->status = 42;
  s->wrap = wrap;
  s->gzhead = 0;
  s->w_bits = (uInt) windowBits;
  s->w_size = 1 << s->w_bits;
  s->w_mask = s->w_size - 1;
  s->hash_bits = ((uInt) memLevel) + 7;
  s->hash_size = 1 << s->hash_bits;
  s->hash_mask = s->hash_size - 1;
  s->hash_shift = ((s->hash_bits + 3) - 1) / 3;
  s->window = (Bytef *) (*strm->zalloc)(strm->opaque, s->w_size, 2 * (sizeof(Byte)));
  s->prev = (Posf *) (*strm->zalloc)(strm->opaque, s->w_size, sizeof(Pos));
  s->head = (Posf *) (*strm->zalloc)(strm->opaque, s->hash_size, sizeof(Pos));
  s->high_water = 0;
  s->lit_bufsize = 1 << (memLevel + 6);
  s->pending_buf = (uchf *) (*strm->zalloc)(strm->opaque, s->lit_bufsize, 4);
  s->pending_buf_size = ((ulg) s->lit_bufsize) * 4;
  if ((((s->window == 0) || (s->prev == 0)) || (s->head == 0)) || (s->pending_buf == 0))
  {
    s->status = 666;
    strm->msg = z_errmsg[2 - (-4)];
    deflateEnd(strm);
    return -4;
  }
  s->sym_buf = s->pending_buf + s->lit_bufsize;
  s->sym_end = (s->lit_bufsize - 1) * 3;
  s->level = level;
  s->strategy = strategy;
  s->method = (Byte) method;
  return deflateReset(strm);
}

static int deflateStateCheck(z_streamp strm)
{
  deflate_state *s;
  unsigned int s_idx = 0;
  if (((strm == 0) || (strm->zalloc == ((alloc_func) 0))) || (strm->zfree == ((free_func) 0)))
  {
    return 1;
  }
  s_idx = strm->state;
  if ((((&s[s_idx]) == 0) || (s->strm != strm)) || (((((((s->status != 42) && (s->status != 69)) && (s->status != 73)) && (s->status != 91)) && (s->status != 103)) && (s->status != 113)) && (s->status != 666)))
  {
    return 1;
  }
  return 0;
}

int deflateSetDictionary(z_streamp strm, const Bytef *dictionary, uInt dictLength)
{
  unsigned int dictionary_idx = 0;
  deflate_state *s;
  unsigned int s_idx = 0;
  uInt str;
  uInt n;
  int wrap;
  unsigned avail;
  const unsigned char *next;
  unsigned int next_idx = 0;
  if (deflateStateCheck(strm) || ((&dictionary[dictionary_idx]) == 0))
  {
    return -2;
  }
  s_idx = strm->state;
  wrap = s->wrap;
  if (((wrap == 2) || ((wrap == 1) && (s->status != 42))) || s->lookahead)
  {
    return -2;
  }
  if (wrap == 1)
  {
    strm->adler = adler32(strm->adler, dictionary, dictLength);
  }
  s->wrap = 0;
  if (dictLength >= s->w_size)
  {
    if (wrap == 0)
    {
      do
      {
        s->head[s->hash_size - 1] = 0;
        memset((Bytef *) s->head, 0, ((unsigned) (s->hash_size - 1)) * (sizeof(*s->head)));
      }
      while (0);
      s->strstart = 0;
      s->block_start = 0L;
      s->insert = 0;
    }
    dictionary_idx += dictLength - s->w_size;
    dictLength = s->w_size;
  }
  avail = strm->avail_in;
  next_idx = strm->next_in;
  strm->avail_in = dictLength;
  strm->next_in = (const Bytef *) dictionary;
  fill_window(s);
  while (s->lookahead >= 3)
  {
    str = s->strstart;
    n = s->lookahead - (3 - 1);
    do
    {
      s->ins_h = ((s->ins_h << s->hash_shift) ^ s->window[(str + 3) - 1]) & s->hash_mask;
      s->prev[str & s->w_mask] = s->head[s->ins_h];
      s->head[s->ins_h] = (Pos) str;
      str += 1;
    }
    while (--n);
    s->strstart = str;
    s->lookahead = 3 - 1;
    fill_window(s);
  }

  s->strstart += s->lookahead;
  s->block_start = (long) s->strstart;
  s->insert = s->lookahead;
  s->lookahead = 0;
  s->match_length = (s->prev_length = 3 - 1);
  s->match_available = 0;
  strm->next_in = &next[next_idx];
  strm->avail_in = avail;
  s->wrap = wrap;
  return 0;
}

int deflateGetDictionary(z_streamp strm, Bytef *dictionary, uInt *dictLength)
{
  deflate_state *s;
  unsigned int s_idx = 0;
  uInt len;
  if (deflateStateCheck(strm))
  {
    return -2;
  }
  s_idx = strm->state;
  len = s->strstart + s->lookahead;
  if (len > s->w_size)
  {
    len = s->w_size;
  }
  if ((dictionary != 0) && len)
  {
    memcpy(dictionary, ((s->window + s->strstart) + s->lookahead) - len, len);
  }
  if (dictLength != 0)
  {
    *dictLength = len;
  }
  return 0;
}

int deflateResetKeep(z_streamp strm)
{
  deflate_state *s;
  unsigned int s_idx = 0;
  if (deflateStateCheck(strm))
  {
    return -2;
  }
  strm->total_in = (strm->total_out = 0);
  strm->msg = 0;
  strm->data_type = 2;
  s_idx = (deflate_state *) strm->state;
  s->pending = 0;
  s->pending_out = s->pending_buf;
  if (s->wrap < 0)
  {
    s->wrap = -s->wrap;
  }
  s->status = 42;
  strm->adler = adler32(0L, 0, 0);
  s->last_flush = -2;
  _tr_init(s);
  return 0;
}

static void lm_init(deflate_state *s)
{
  s->window_size = ((ulg) 2L) * s->w_size;
  do
  {
    s->head[s->hash_size - 1] = 0;
    memset((Bytef *) s->head, 0, ((unsigned) (s->hash_size - 1)) * (sizeof(*s->head)));
  }
  while (0);
  s->max_lazy_match = configuration_table[s->level].max_lazy;
  s->good_match = configuration_table[s->level].good_length;
  s->nice_match = configuration_table[s->level].nice_length;
  s->max_chain_length = configuration_table[s->level].max_chain;
  s->strstart = 0;
  s->block_start = 0L;
  s->lookahead = 0;
  s->insert = 0;
  s->match_length = (s->prev_length = 3 - 1);
  s->match_available = 0;
  s->ins_h = 0;
}

int deflateReset(z_streamp strm)
{
  int ret;
  ret = deflateResetKeep(strm);
  if (ret == 0)
  {
    lm_init(strm->state);
  }
  return ret;
}

int deflateSetHeader(z_streamp strm, gz_headerp head)
{
  if (deflateStateCheck(strm) || (strm->state->wrap != 2))
  {
    return -2;
  }
  strm->state->gzhead = head;
  return 0;
}

int deflatePending(z_streamp strm, unsigned *pending, int *bits)
{
  if (deflateStateCheck(strm))
  {
    return -2;
  }
  if (pending != 0)
  {
    *pending = strm->state->pending;
  }
  if (bits != 0)
  {
    *bits = strm->state->bi_valid;
  }
  return 0;
}

int deflatePrime(z_streamp strm, int bits, int value)
{
  deflate_state *s;
  unsigned int s_idx = 0;
  int put;
  if (deflateStateCheck(strm))
  {
    return -2;
  }
  s_idx = strm->state;
  if (((bits < 0) || (bits > 16)) || (s->sym_buf < (s->pending_out + ((16 + 7) >> 3))))
  {
    return -5;
  }
  do
  {
    put = 16 - s->bi_valid;
    if (put > bits)
    {
      put = bits;
    }
    s->bi_buf |= (ush) ((value & ((1 << put) - 1)) << s->bi_valid);
    s->bi_valid += put;
    _tr_flush_bits(s);
    value >>= put;
    bits -= put;
  }
  while (bits);
  return 0;
}

int deflateParams(z_streamp strm, int level, int strategy)
{
  deflate_state *s;
  unsigned int s_idx = 0;
  compress_func func;
  if (deflateStateCheck(strm))
  {
    return -2;
  }
  s_idx = strm->state;
  if (level == (-1))
  {
    level = 6;
  }
  if ((((level < 0) || (level > 9)) || (strategy < 0)) || (strategy > 4))
  {
    return -2;
  }
  func = configuration_table[s->level].func;
  if (((strategy != s->strategy) || (func != configuration_table[level].func)) && (s->last_flush != (-2)))
  {
    int err = deflate(strm, 5);
    if (err == (-2))
    {
      return err;
    }
    if (strm->avail_in || ((s->strstart - s->block_start) + s->lookahead))
    {
      return -5;
    }
  }
  if (s->level != level)
  {
    helper_deflateParams_1(&level, s);
  }
  s->strategy = strategy;
  return 0;
}

int deflateTune(z_streamp strm, int good_length, int max_lazy, int nice_length, int max_chain)
{
  deflate_state *s;
  unsigned int s_idx = 0;
  if (deflateStateCheck(strm))
  {
    return -2;
  }
  s_idx = strm->state;
  s->good_match = (uInt) good_length;
  s->max_lazy_match = (uInt) max_lazy;
  s->nice_match = nice_length;
  s->max_chain_length = (uInt) max_chain;
  return 0;
}

uLong deflateBound(z_streamp strm, uLong sourceLen)
{
  deflate_state *s;
  unsigned int s_idx = 0;
  uLong fixedlen;
  uLong storelen;
  uLong wraplen;
  fixedlen = (((sourceLen + (sourceLen >> 3)) + (sourceLen >> 8)) + (sourceLen >> 9)) + 4;
  storelen = (((sourceLen + (sourceLen >> 5)) + (sourceLen >> 7)) + (sourceLen >> 11)) + 7;
  if (deflateStateCheck(strm))
  {
    return ((fixedlen > storelen) ? (fixedlen) : (storelen)) + 6;
  }
  s_idx = strm->state;
  switch (s->wrap)
  {
    case 0:
    {
      wraplen = 0;
      break;
    }

    case 1:
    {
      wraplen = 6 + ((s->strstart) ? (4) : (0));
      break;
    }

    default:
    {
      wraplen = 6;
    }

  }

  if ((s->w_bits != 15) || (s->hash_bits != (8 + 7)))
  {
    return (((s->w_bits <= s->hash_bits) && s->level) ? (fixedlen) : (storelen)) + wraplen;
  }
  return (((((sourceLen + (sourceLen >> 12)) + (sourceLen >> 14)) + (sourceLen >> 25)) + 13) - 6) + wraplen;
}

static void putShortMSB(deflate_state *s, uInt b)
{
  {
    s->pending_buf[s->pending++] = (Bytef) ((Byte) (b >> 8));
  }
  ;
  {
    s->pending_buf[s->pending++] = (Bytef) ((Byte) (b & 0xff));
  }
  ;
}

static void flush_pending(z_streamp strm)
{
  unsigned len;
  deflate_state *s = strm->state;
  _tr_flush_bits(s);
  len = s->pending;
  if (len > strm->avail_out)
  {
    len = strm->avail_out;
  }
  if (len == 0)
  {
    return;
  }
  memcpy(strm->next_out, s->pending_out, len);
  strm->next_out += len;
  s->pending_out += len;
  strm->total_out += len;
  strm->avail_out -= len;
  s->pending -= len;
  if (s->pending == 0)
  {
    s->pending_out = s->pending_buf;
  }
}

int deflate(z_streamp strm, int flush)
{
  int old_flush;
  deflate_state *s;
  unsigned int s_idx = 0;
  if ((deflateStateCheck(strm) || (flush > 5)) || (flush < 0))
  {
    return -2;
  }
  s_idx = strm->state;
  if (((strm->next_out == 0) || ((strm->avail_in != 0) && (strm->next_in == 0))) || ((s->status == 666) && (flush != 4)))
  {
    return strm->msg = z_errmsg[2 - (-2)], -2;
  }
  if (strm->avail_out == 0)
  {
    return strm->msg = z_errmsg[2 - (-5)], -5;
  }
  old_flush = s->last_flush;
  s->last_flush = flush;
  if (s->pending != 0)
  {
    flush_pending(strm);
    if (strm->avail_out == 0)
    {
      s->last_flush = -1;
      return 0;
    }
  }
  else
    if (((strm->avail_in == 0) && (((flush * 2) - ((flush > 4) ? (9) : (0))) <= ((old_flush * 2) - ((old_flush > 4) ? (9) : (0))))) && (flush != 4))
  {
    return strm->msg = z_errmsg[2 - (-5)], -5;
  }
  if ((s->status == 666) && (strm->avail_in != 0))
  {
    return strm->msg = z_errmsg[2 - (-5)], -5;
  }
  if ((s->status == 42) && (s->wrap == 0))
  {
    s->status = 113;
  }
  if (s->status == 42)
  {
    helper_deflate_1(&strm, s);
  }
  if (((strm->avail_in != 0) || (s->lookahead != 0)) || ((flush != 0) && (s->status != 666)))
  {
    helper_deflate_2(strm, flush, s);
  }
  if (flush != 4)
  {
    return 0;
  }
  if (s->wrap <= 0)
  {
    return 1;
  }
  {
    putShortMSB(s, (uInt) (strm->adler >> 16));
    putShortMSB(s, (uInt) (strm->adler & 0xffff));
  }
  flush_pending(strm);
  if (s->wrap > 0)
  {
    s->wrap = -s->wrap;
  }
  return (s->pending != 0) ? (0) : (1);
}

int deflateEnd(z_streamp strm)
{
  int status;
  if (deflateStateCheck(strm))
  {
    return -2;
  }
  status = strm->state->status;
  {
    if (strm->state->pending_buf)
    {
      (*strm->zfree)(strm->opaque, (voidpf) strm->state->pending_buf);
    }
  }
  ;
  {
    if (strm->state->head)
    {
      (*strm->zfree)(strm->opaque, (voidpf) strm->state->head);
    }
  }
  ;
  {
    if (strm->state->prev)
    {
      (*strm->zfree)(strm->opaque, (voidpf) strm->state->prev);
    }
  }
  ;
  {
    if (strm->state->window)
    {
      (*strm->zfree)(strm->opaque, (voidpf) strm->state->window);
    }
  }
  ;
  (*strm->zfree)(strm->opaque, (voidpf) strm->state);
  strm->state = 0;
  return (status == 113) ? (-3) : (0);
}

int deflateCopy(z_streamp dest, z_streamp source)
{
  deflate_state *ds;
  unsigned int ds_idx = 0;
  deflate_state *ss;
  unsigned int ss_idx = 0;
  if (deflateStateCheck(source) || (dest == 0))
  {
    return -2;
  }
  ss_idx = source->state;
  memcpy((voidpf) dest, (voidpf) source, sizeof(z_stream));
  ds_idx = (deflate_state *) (*dest->zalloc)(dest->opaque, 1, sizeof(deflate_state));
  if ((&ds[ds_idx]) == 0)
  {
    return -4;
  }
  dest->state = (struct internal_state *) ds;
  memcpy((voidpf) ds, (voidpf) ss, sizeof(deflate_state));
  ds->strm = dest;
  ds->window = (Bytef *) (*dest->zalloc)(dest->opaque, ds->w_size, 2 * (sizeof(Byte)));
  ds->prev = (Posf *) (*dest->zalloc)(dest->opaque, ds->w_size, sizeof(Pos));
  ds->head = (Posf *) (*dest->zalloc)(dest->opaque, ds->hash_size, sizeof(Pos));
  ds->pending_buf = (uchf *) (*dest->zalloc)(dest->opaque, ds->lit_bufsize, 4);
  if ((((ds->window == 0) || (ds->prev == 0)) || (ds->head == 0)) || (ds->pending_buf == 0))
  {
    deflateEnd(dest);
    return -4;
  }
  memcpy(ds->window, ss->window, (ds->w_size * 2) * (sizeof(Byte)));
  memcpy((voidpf) ds->prev, (voidpf) ss->prev, ds->w_size * (sizeof(Pos)));
  memcpy((voidpf) ds->head, (voidpf) ss->head, ds->hash_size * (sizeof(Pos)));
  memcpy(ds->pending_buf, ss->pending_buf, (uInt) ds->pending_buf_size);
  ds->pending_out = ds->pending_buf + (ss->pending_out - ss->pending_buf);
  ds->sym_buf = ds->pending_buf + ds->lit_bufsize;
  ds->l_desc.dyn_tree = ds->dyn_ltree;
  ds->d_desc.dyn_tree = ds->dyn_dtree;
  ds->bl_desc.dyn_tree = ds->bl_tree;
  return 0;
}

static uInt longest_match(deflate_state *s, IPos cur_match)
{
  unsigned chain_length = s->max_chain_length;
  register Bytef *scan = s->window + s->strstart;
  unsigned int scan_idx = 0;
  register Bytef *match;
  unsigned int match_idx = 0;
  register int len;
  int best_len = (int) s->prev_length;
  int nice_match = s->nice_match;
  IPos limit = (s->strstart > ((IPos) (s->w_size - ((258 + 3) + 1)))) ? (s->strstart - ((IPos) (s->w_size - ((258 + 3) + 1)))) : (0);
  Posf *prev = s->prev;
  uInt wmask = s->w_mask;
  register Bytef *strend = (s->window + s->strstart) + 258;
  register Byte scan_end1 = scan[(best_len - 1) + scan_idx];
  register Byte scan_end = scan[best_len + scan_idx];
  ;
  if (s->prev_length >= s->good_match)
  {
    chain_length >>= 2;
  }
  if (((uInt) nice_match) > s->lookahead)
  {
    nice_match = (int) s->lookahead;
  }
  ;
  do
  {
    helper_longest_match_1(&scan_idx, &match_idx, &len, &best_len, &scan_end1, &scan_end, s, cur_match, scan, match, nice_match, strend);
  }
  while (((cur_match = prev[cur_match & wmask]) > limit) && ((--chain_length) != 0));
  if (((uInt) best_len) <= s->lookahead)
  {
    return (uInt) best_len;
  }
  return s->lookahead;
}

static block_state deflate_stored(deflate_state *s, int flush)
{
  unsigned min_block = ((s->pending_buf_size - 5) > s->w_size) ? (s->w_size) : (s->pending_buf_size - 5);
  unsigned len;
  unsigned left;
  unsigned have;
  unsigned last = 0;
  unsigned used = s->strm->avail_in;
  do
  {
    helper_deflate_stored_2(&len, &left, &have, &last, s, flush, min_block);
  }
  while (last == 0);
  used -= s->strm->avail_in;
  if (used)
  {
    helper_deflate_stored_1(s, used);
  }
  if (s->high_water < s->strstart)
  {
    s->high_water = s->strstart;
  }
  if (last)
  {
    return finish_done;
  }
  if ((((flush != 0) && (flush != 4)) && (s->strm->avail_in == 0)) && (((long) s->strstart) == s->block_start))
  {
    return block_done;
  }
  have = s->window_size - s->strstart;
  if ((s->strm->avail_in > have) && (s->block_start >= ((long) s->w_size)))
  {
    s->block_start -= s->w_size;
    s->strstart -= s->w_size;
    memcpy(s->window, s->window + s->w_size, s->strstart);
    if (s->matches < 2)
    {
      s->matches += 1;
    }
    have += s->w_size;
    if (s->insert > s->strstart)
    {
      s->insert = s->strstart;
    }
  }
  if (have > s->strm->avail_in)
  {
    have = s->strm->avail_in;
  }
  if (have)
  {
    read_buf(s->strm, s->window + s->strstart, have);
    s->strstart += have;
    s->insert += (have > (s->w_size - s->insert)) ? (s->w_size - s->insert) : (have);
  }
  if (s->high_water < s->strstart)
  {
    s->high_water = s->strstart;
  }
  have = (s->bi_valid + 42) >> 3;
  have = ((s->pending_buf_size - have) > 65535) ? (65535) : (s->pending_buf_size - have);
  min_block = (have > s->w_size) ? (s->w_size) : (have);
  left = s->strstart - s->block_start;
  if ((left >= min_block) || ((((left || (flush == 4)) && (flush != 0)) && (s->strm->avail_in == 0)) && (left <= have)))
  {
    len = (left > have) ? (have) : (left);
    last = (((flush == 4) && (s->strm->avail_in == 0)) && (len == left)) ? (1) : (0);
    _tr_stored_block(s, ((charf *) s->window) + s->block_start, len, last);
    s->block_start += len;
    flush_pending(s->strm);
  }
  return (last) ? (finish_started) : (need_more);
}

static block_state deflate_fast(deflate_state *s, int flush)
{
  IPos hash_head;
  int bflush;
  for (;;)
  {
    helper_deflate_fast_2(&hash_head, &bflush, s, flush);
  }

  s->insert = (s->strstart < (3 - 1)) ? (s->strstart) : (3 - 1);
  if (flush == 4)
  {
    helper_deflate_fast_1(s);
  }
  if (s->sym_next)
  {
    {
      _tr_flush_block(s, (s->block_start >= 0L) ? ((charf *) (&s->window[(unsigned) s->block_start])) : ((charf *) 0), (ulg) (((long) s->strstart) - s->block_start), 0);
      s->block_start = s->strstart;
      flush_pending(s->strm);
      ;
    }
    ;
    if (s->strm->avail_out == 0)
    {
      return (0) ? (finish_started) : (need_more);
    }
  }
  ;
  return block_done;
}

static block_state deflate_slow(deflate_state *s, int flush)
{
  IPos hash_head;
  int bflush;
  for (;;)
  {
    helper_deflate_slow_2(&hash_head, &bflush, s, flush);
  }

  ;
  if (s->match_available)
  {
    ;
    {
      uch cc = s->window[s->strstart - 1];
      s->sym_buf[s->sym_next++] = 0;
      s->sym_buf[s->sym_next++] = 0;
      s->sym_buf[s->sym_next++] = cc;
      s->dyn_ltree[cc].fc.freq += 1;
      bflush = s->sym_next == s->sym_end;
    }
    ;
    s->match_available = 0;
  }
  s->insert = (s->strstart < (3 - 1)) ? (s->strstart) : (3 - 1);
  if (flush == 4)
  {
    helper_deflate_slow_1(s);
  }
  if (s->sym_next)
  {
    {
      _tr_flush_block(s, (s->block_start >= 0L) ? ((charf *) (&s->window[(unsigned) s->block_start])) : ((charf *) 0), (ulg) (((long) s->strstart) - s->block_start), 0);
      s->block_start = s->strstart;
      flush_pending(s->strm);
      ;
    }
    ;
    if (s->strm->avail_out == 0)
    {
      return (0) ? (finish_started) : (need_more);
    }
  }
  ;
  return block_done;
}

static block_state deflate_rle(deflate_state *s, int flush)
{
  int bflush;
  uInt prev;
  Bytef *scan;
  unsigned int scan_idx = 0;
  Bytef *strend;
  unsigned int strend_idx = 0;
  for (;;)
  {
    helper_deflate_rle_2(&bflush, &prev, &scan_idx, &strend_idx, s, flush, scan, strend);
  }

  s->insert = 0;
  if (flush == 4)
  {
    helper_deflate_rle_1(s);
  }
  if (s->sym_next)
  {
    {
      _tr_flush_block(s, (s->block_start >= 0L) ? ((charf *) (&s->window[(unsigned) s->block_start])) : ((charf *) 0), (ulg) (((long) s->strstart) - s->block_start), 0);
      s->block_start = s->strstart;
      flush_pending(s->strm);
      ;
    }
    ;
    if (s->strm->avail_out == 0)
    {
      return (0) ? (finish_started) : (need_more);
    }
  }
  ;
  return block_done;
}

static block_state deflate_huff(deflate_state *s, int flush)
{
  int bflush;
  for (;;)
  {
    helper_deflate_huff_2(&bflush, s, flush);
  }

  s->insert = 0;
  if (flush == 4)
  {
    helper_deflate_huff_1(s);
  }
  if (s->sym_next)
  {
    {
      _tr_flush_block(s, (s->block_start >= 0L) ? ((charf *) (&s->window[(unsigned) s->block_start])) : ((charf *) 0), (ulg) (((long) s->strstart) - s->block_start), 0);
      s->block_start = s->strstart;
      flush_pending(s->strm);
      ;
    }
    ;
    if (s->strm->avail_out == 0)
    {
      return (0) ? (finish_started) : (need_more);
    }
  }
  ;
  return block_done;
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
typedef struct ct_data_s
{
  union 
  {
    ush freq;
    ush code;
  } fc;
  union 
  {
    ush dad;
    ush len;
  } dl;
} ct_data;
typedef struct static_tree_desc_s static_tree_desc;
typedef struct tree_desc_s
{
  ct_data *dyn_tree;
  int max_code;
  const static_tree_desc *stat_desc;
} tree_desc;
typedef ush Pos;
typedef Pos Posf;
typedef unsigned IPos;
typedef struct internal_state
{
  z_streamp strm;
  int status;
  Bytef *pending_buf;
  ulg pending_buf_size;
  Bytef *pending_out;
  ulg pending;
  int wrap;
  gz_headerp gzhead;
  ulg gzindex;
  Byte method;
  int last_flush;
  uInt w_size;
  uInt w_bits;
  uInt w_mask;
  Bytef *window;
  ulg window_size;
  Posf *prev;
  Posf *head;
  uInt ins_h;
  uInt hash_size;
  uInt hash_bits;
  uInt hash_mask;
  uInt hash_shift;
  long block_start;
  uInt match_length;
  IPos prev_match;
  int match_available;
  uInt strstart;
  uInt match_start;
  uInt lookahead;
  uInt prev_length;
  uInt max_chain_length;
  uInt max_lazy_match;
  int level;
  int strategy;
  uInt good_match;
  int nice_match;
  struct ct_data_s dyn_ltree[(2 * ((256 + 1) + 29)) + 1];
  struct ct_data_s dyn_dtree[(2 * 30) + 1];
  struct ct_data_s bl_tree[(2 * 19) + 1];
  struct tree_desc_s l_desc;
  struct tree_desc_s d_desc;
  struct tree_desc_s bl_desc;
  ush bl_count[15 + 1];
  int heap[(2 * ((256 + 1) + 29)) + 1];
  int heap_len;
  int heap_max;
  uch depth[(2 * ((256 + 1) + 29)) + 1];
  uchf *sym_buf;
  uInt lit_bufsize;
  uInt sym_next;
  uInt sym_end;
  ulg opt_len;
  ulg static_len;
  uInt matches;
  uInt insert;
  ush bi_buf;
  int bi_valid;
  ulg high_water;
} deflate_state;
void _tr_init(deflate_state *s);
int _tr_tally(deflate_state *s, unsigned dist, unsigned lc);
void _tr_flush_block(deflate_state *s, charf *buf, ulg stored_len, int last);
void _tr_flush_bits(deflate_state *s);
void _tr_align(deflate_state *s);
void _tr_stored_block(deflate_state *s, charf *buf, ulg stored_len, int last);
extern const uch _length_code[];
extern const uch _dist_code[];
const char deflate_copyright[] = " deflate 1.3 Copyright 1995-2023 Jean-loup Gailly and Mark Adler ";
typedef enum 
{
  need_more,
  block_done,
  finish_started,
  finish_done
} block_state;
typedef block_state (*compress_func)(deflate_state *s, int flush);
static block_state deflate_stored(deflate_state *s, int flush);
static block_state deflate_fast(deflate_state *s, int flush);
static block_state deflate_slow(deflate_state *s, int flush);
static block_state deflate_rle(deflate_state *s, int flush);
static block_state deflate_huff(deflate_state *s, int flush);
typedef struct config_s
{
  ush good_length;
  ush max_lazy;
  ush nice_length;
  ush max_chain;
  compress_func func;
} config;
static const config configuration_table[10] = {{0, 0, 0, 0, deflate_stored}, {4, 4, 8, 4, deflate_fast}, {4, 5, 16, 8, deflate_fast}, {4, 6, 32, 32, deflate_fast}, {4, 4, 16, 16, deflate_slow}, {8, 16, 32, 32, deflate_slow}, {8, 16, 128, 128, deflate_slow}, {8, 32, 128, 256, deflate_slow}, {32, 128, 258, 1024, deflate_slow}, {32, 258, 258, 4096, deflate_slow}};
static void slide_hash(deflate_state *s)
{
  unsigned n;
  unsigned m;
  Posf *p;
  unsigned int p_idx = 0;
  uInt wsize = s->w_size;
  n = s->hash_size;
  p_idx = &s->head[n];
  do
  {
    p_idx -= 1;
    m = p[p_idx];
    p[p_idx] = (Pos) ((m >= wsize) ? (m - wsize) : (0));
  }
  while (--n);
  n = wsize;
  p_idx = &s->prev[n];
  do
  {
    p_idx -= 1;
    m = p[p_idx];
    p[p_idx] = (Pos) ((m >= wsize) ? (m - wsize) : (0));
  }
  while (--n);
}

static unsigned read_buf(z_streamp strm, Bytef *buf, unsigned size)
{
  unsigned len = strm->avail_in;
  if (len > size)
  {
    len = size;
  }
  if (len == 0)
  {
    return 0;
  }
  strm->avail_in -= len;
  memcpy(buf, strm->next_in, len);
  if (strm->state->wrap == 1)
  {
    strm->adler = adler32(strm->adler, buf, len);
  }
  strm->next_in += len;
  strm->total_in += len;
  return len;
}

static void fill_window(deflate_state *s)
{
  unsigned n;
  unsigned more;
  uInt wsize = s->w_size;
  ;
  do
  {
    more = (unsigned) ((s->window_size - ((ulg) s->lookahead)) - ((ulg) s->strstart));
    if ((sizeof(int)) <= 2)
    {
      if (((more == 0) && (s->strstart == 0)) && (s->lookahead == 0))
      {
        more = wsize;
      }
      else
        if (more == ((unsigned) (-1)))
      {
        more -= 1;
      }
    }
    if (s->strstart >= (wsize + (s->w_size - ((258 + 3) + 1))))
    {
      memcpy(s->window, s->window + wsize, ((unsigned) wsize) - more);
      s->match_start -= wsize;
      s->strstart -= wsize;
      s->block_start -= (long) wsize;
      if (s->insert > s->strstart)
      {
        s->insert = s->strstart;
      }
      slide_hash(s);
      more += wsize;
    }
    if (s->strm->avail_in == 0)
    {
      break;
    }
    ;
    n = read_buf(s->strm, (s->window + s->strstart) + s->lookahead, more);
    s->lookahead += n;
    if ((s->lookahead + s->insert) >= 3)
    {
      uInt str = s->strstart - s->insert;
      s->ins_h = s->window[str];
      s->ins_h = ((s->ins_h << s->hash_shift) ^ s->window[str + 1]) & s->hash_mask;
      while (s->insert)
      {
        s->ins_h = ((s->ins_h << s->hash_shift) ^ s->window[(str + 3) - 1]) & s->hash_mask;
        s->prev[str & s->w_mask] = s->head[s->ins_h];
        s->head[s->ins_h] = (Pos) str;
        str += 1;
        s->insert -= 1;
        if ((s->lookahead + s->insert) < 3)
        {
          break;
        }
      }

    }
  }
  while ((s->lookahead < ((258 + 3) + 1)) && (s->strm->avail_in != 0));
  if (s->high_water < s->window_size)
  {
    ulg curr = s->strstart + ((ulg) s->lookahead);
    ulg init;
    if (s->high_water < curr)
    {
      init = s->window_size - curr;
      if (init > 258)
      {
        init = 258;
      }
      memset(s->window + curr, 0, (unsigned) init);
      s->high_water = curr + init;
    }
    else
      if (s->high_water < (((ulg) curr) + 258))
    {
      init = (((ulg) curr) + 258) - s->high_water;
      if (init > (s->window_size - s->high_water))
      {
        init = s->window_size - s->high_water;
      }
      memset(s->window + s->high_water, 0, (unsigned) init);
      s->high_water += init;
    }
  }
  ;
}

int deflateInit_(z_streamp strm, int level, const char *version, int stream_size)
{
  return deflateInit2_(strm, level, 8, 15, 8, 0, version, stream_size);
}

int deflateInit2_(z_streamp strm, int level, int method, int windowBits, int memLevel, int strategy, const char *version, int stream_size)
{
  deflate_state *s;
  unsigned int s_idx = 0;
  int wrap = 1;
  static const char my_version[] = "1.3-optipng";
  if (((version == 0) || (version[0] != my_version[0])) || (stream_size != (sizeof(z_stream))))
  {
    return -6;
  }
  if (strm == 0)
  {
    return -2;
  }
  strm->msg = 0;
  if (strm->zalloc == ((alloc_func) 0))
  {
    strm->zalloc = zcalloc;
    strm->opaque = (voidpf) 0;
  }
  if (strm->zfree == ((free_func) 0))
  {
    strm->zfree = zcfree;
  }
  if (level == (-1))
  {
    level = 6;
  }
  if (windowBits < 0)
  {
    wrap = 0;
    if (windowBits < (-15))
    {
      return -2;
    }
    windowBits = -windowBits;
  }
  if ((((((((((memLevel < 1) || (memLevel > 9)) || (method != 8)) || (windowBits < 8)) || (windowBits > 15)) || (level < 0)) || (level > 9)) || (strategy < 0)) || (strategy > 4)) || ((windowBits == 8) && (wrap != 1)))
  {
    return -2;
  }
  if (windowBits == 8)
  {
    windowBits = 9;
  }
  s_idx = (deflate_state *) (*strm->zalloc)(strm->opaque, 1, sizeof(deflate_state));
  if ((&s[s_idx]) == 0)
  {
    return -4;
  }
  strm->state = (struct internal_state *) s;
  s->strm = strm;
  s->status = 42;
  s->wrap = wrap;
  s->gzhead = 0;
  s->w_bits = (uInt) windowBits;
  s->w_size = 1 << s->w_bits;
  s->w_mask = s->w_size - 1;
  s->hash_bits = ((uInt) memLevel) + 7;
  s->hash_size = 1 << s->hash_bits;
  s->hash_mask = s->hash_size - 1;
  s->hash_shift = ((s->hash_bits + 3) - 1) / 3;
  s->window = (Bytef *) (*strm->zalloc)(strm->opaque, s->w_size, 2 * (sizeof(Byte)));
  s->prev = (Posf *) (*strm->zalloc)(strm->opaque, s->w_size, sizeof(Pos));
  s->head = (Posf *) (*strm->zalloc)(strm->opaque, s->hash_size, sizeof(Pos));
  s->high_water = 0;
  s->lit_bufsize = 1 << (memLevel + 6);
  s->pending_buf = (uchf *) (*strm->zalloc)(strm->opaque, s->lit_bufsize, 4);
  s->pending_buf_size = ((ulg) s->lit_bufsize) * 4;
  if ((((s->window == 0) || (s->prev == 0)) || (s->head == 0)) || (s->pending_buf == 0))
  {
    s->status = 666;
    strm->msg = z_errmsg[2 - (-4)];
    deflateEnd(strm);
    return -4;
  }
  s->sym_buf = s->pending_buf + s->lit_bufsize;
  s->sym_end = (s->lit_bufsize - 1) * 3;
  s->level = level;
  s->strategy = strategy;
  s->method = (Byte) method;
  return deflateReset(strm);
}

static int deflateStateCheck(z_streamp strm)
{
  deflate_state *s;
  unsigned int s_idx = 0;
  if (((strm == 0) || (strm->zalloc == ((alloc_func) 0))) || (strm->zfree == ((free_func) 0)))
  {
    return 1;
  }
  s_idx = strm->state;
  if ((((&s[s_idx]) == 0) || (s->strm != strm)) || (((((((s->status != 42) && (s->status != 69)) && (s->status != 73)) && (s->status != 91)) && (s->status != 103)) && (s->status != 113)) && (s->status != 666)))
  {
    return 1;
  }
  return 0;
}

int deflateSetDictionary(z_streamp strm, const Bytef *dictionary, uInt dictLength)
{
  unsigned int dictionary_idx = 0;
  deflate_state *s;
  unsigned int s_idx = 0;
  uInt str;
  uInt n;
  int wrap;
  unsigned avail;
  const unsigned char *next;
  unsigned int next_idx = 0;
  if (deflateStateCheck(strm) || ((&dictionary[dictionary_idx]) == 0))
  {
    return -2;
  }
  s_idx = strm->state;
  wrap = s->wrap;
  if (((wrap == 2) || ((wrap == 1) && (s->status != 42))) || s->lookahead)
  {
    return -2;
  }
  if (wrap == 1)
  {
    strm->adler = adler32(strm->adler, dictionary, dictLength);
  }
  s->wrap = 0;
  if (dictLength >= s->w_size)
  {
    if (wrap == 0)
    {
      do
      {
        s->head[s->hash_size - 1] = 0;
        memset((Bytef *) s->head, 0, ((unsigned) (s->hash_size - 1)) * (sizeof(*s->head)));
      }
      while (0);
      s->strstart = 0;
      s->block_start = 0L;
      s->insert = 0;
    }
    dictionary_idx += dictLength - s->w_size;
    dictLength = s->w_size;
  }
  avail = strm->avail_in;
  next_idx = strm->next_in;
  strm->avail_in = dictLength;
  strm->next_in = (const Bytef *) dictionary;
  fill_window(s);
  while (s->lookahead >= 3)
  {
    str = s->strstart;
    n = s->lookahead - (3 - 1);
    do
    {
      s->ins_h = ((s->ins_h << s->hash_shift) ^ s->window[(str + 3) - 1]) & s->hash_mask;
      s->prev[str & s->w_mask] = s->head[s->ins_h];
      s->head[s->ins_h] = (Pos) str;
      str += 1;
    }
    while (--n);
    s->strstart = str;
    s->lookahead = 3 - 1;
    fill_window(s);
  }

  s->strstart += s->lookahead;
  s->block_start = (long) s->strstart;
  s->insert = s->lookahead;
  s->lookahead = 0;
  s->match_length = (s->prev_length = 3 - 1);
  s->match_available = 0;
  strm->next_in = &next[next_idx];
  strm->avail_in = avail;
  s->wrap = wrap;
  return 0;
}

int deflateGetDictionary(z_streamp strm, Bytef *dictionary, uInt *dictLength)
{
  deflate_state *s;
  unsigned int s_idx = 0;
  uInt len;
  if (deflateStateCheck(strm))
  {
    return -2;
  }
  s_idx = strm->state;
  len = s->strstart + s->lookahead;
  if (len > s->w_size)
  {
    len = s->w_size;
  }
  if ((dictionary != 0) && len)
  {
    memcpy(dictionary, ((s->window + s->strstart) + s->lookahead) - len, len);
  }
  if (dictLength != 0)
  {
    *dictLength = len;
  }
  return 0;
}

int deflateResetKeep(z_streamp strm)
{
  deflate_state *s;
  unsigned int s_idx = 0;
  if (deflateStateCheck(strm))
  {
    return -2;
  }
  strm->total_in = (strm->total_out = 0);
  strm->msg = 0;
  strm->data_type = 2;
  s_idx = (deflate_state *) strm->state;
  s->pending = 0;
  s->pending_out = s->pending_buf;
  if (s->wrap < 0)
  {
    s->wrap = -s->wrap;
  }
  s->status = 42;
  strm->adler = adler32(0L, 0, 0);
  s->last_flush = -2;
  _tr_init(s);
  return 0;
}

static void lm_init(deflate_state *s)
{
  s->window_size = ((ulg) 2L) * s->w_size;
  do
  {
    s->head[s->hash_size - 1] = 0;
    memset((Bytef *) s->head, 0, ((unsigned) (s->hash_size - 1)) * (sizeof(*s->head)));
  }
  while (0);
  s->max_lazy_match = configuration_table[s->level].max_lazy;
  s->good_match = configuration_table[s->level].good_length;
  s->nice_match = configuration_table[s->level].nice_length;
  s->max_chain_length = configuration_table[s->level].max_chain;
  s->strstart = 0;
  s->block_start = 0L;
  s->lookahead = 0;
  s->insert = 0;
  s->match_length = (s->prev_length = 3 - 1);
  s->match_available = 0;
  s->ins_h = 0;
}

int deflateReset(z_streamp strm)
{
  int ret;
  ret = deflateResetKeep(strm);
  if (ret == 0)
  {
    lm_init(strm->state);
  }
  return ret;
}

int deflateSetHeader(z_streamp strm, gz_headerp head)
{
  if (deflateStateCheck(strm) || (strm->state->wrap != 2))
  {
    return -2;
  }
  strm->state->gzhead = head;
  return 0;
}

int deflatePending(z_streamp strm, unsigned *pending, int *bits)
{
  if (deflateStateCheck(strm))
  {
    return -2;
  }
  if (pending != 0)
  {
    *pending = strm->state->pending;
  }
  if (bits != 0)
  {
    *bits = strm->state->bi_valid;
  }
  return 0;
}

int deflatePrime(z_streamp strm, int bits, int value)
{
  deflate_state *s;
  unsigned int s_idx = 0;
  int put;
  if (deflateStateCheck(strm))
  {
    return -2;
  }
  s_idx = strm->state;
  if (((bits < 0) || (bits > 16)) || (s->sym_buf < (s->pending_out + ((16 + 7) >> 3))))
  {
    return -5;
  }
  do
  {
    put = 16 - s->bi_valid;
    if (put > bits)
    {
      put = bits;
    }
    s->bi_buf |= (ush) ((value & ((1 << put) - 1)) << s->bi_valid);
    s->bi_valid += put;
    _tr_flush_bits(s);
    value >>= put;
    bits -= put;
  }
  while (bits);
  return 0;
}

int deflateParams(z_streamp strm, int level, int strategy)
{
  deflate_state *s;
  unsigned int s_idx = 0;
  compress_func func;
  if (deflateStateCheck(strm))
  {
    return -2;
  }
  s_idx = strm->state;
  if (level == (-1))
  {
    level = 6;
  }
  if ((((level < 0) || (level > 9)) || (strategy < 0)) || (strategy > 4))
  {
    return -2;
  }
  func = configuration_table[s->level].func;
  if (((strategy != s->strategy) || (func != configuration_table[level].func)) && (s->last_flush != (-2)))
  {
    int err = deflate(strm, 5);
    if (err == (-2))
    {
      return err;
    }
    if (strm->avail_in || ((s->strstart - s->block_start) + s->lookahead))
    {
      return -5;
    }
  }
  if (s->level != level)
  {
    if ((s->level == 0) && (s->matches != 0))
    {
      if (s->matches == 1)
      {
        slide_hash(s);
      }
      else
        do
      {
        s->head[s->hash_size - 1] = 0;
        memset((Bytef *) s->head, 0, ((unsigned) (s->hash_size - 1)) * (sizeof(*s->head)));
      }
      while (0);
      s->matches = 0;
    }
    s->level = level;
    s->max_lazy_match = configuration_table[level].max_lazy;
    s->good_match = configuration_table[level].good_length;
    s->nice_match = configuration_table[level].nice_length;
    s->max_chain_length = configuration_table[level].max_chain;
  }
  s->strategy = strategy;
  return 0;
}

int deflateTune(z_streamp strm, int good_length, int max_lazy, int nice_length, int max_chain)
{
  deflate_state *s;
  unsigned int s_idx = 0;
  if (deflateStateCheck(strm))
  {
    return -2;
  }
  s_idx = strm->state;
  s->good_match = (uInt) good_length;
  s->max_lazy_match = (uInt) max_lazy;
  s->nice_match = nice_length;
  s->max_chain_length = (uInt) max_chain;
  return 0;
}

uLong deflateBound(z_streamp strm, uLong sourceLen)
{
  deflate_state *s;
  unsigned int s_idx = 0;
  uLong fixedlen;
  uLong storelen;
  uLong wraplen;
  fixedlen = (((sourceLen + (sourceLen >> 3)) + (sourceLen >> 8)) + (sourceLen >> 9)) + 4;
  storelen = (((sourceLen + (sourceLen >> 5)) + (sourceLen >> 7)) + (sourceLen >> 11)) + 7;
  if (deflateStateCheck(strm))
  {
    return ((fixedlen > storelen) ? (fixedlen) : (storelen)) + 6;
  }
  s_idx = strm->state;
  switch (s->wrap)
  {
    case 0:
      wraplen = 0;
      break;

    case 1:
      wraplen = 6 + ((s->strstart) ? (4) : (0));
      break;

    default:
      wraplen = 6;

  }

  if ((s->w_bits != 15) || (s->hash_bits != (8 + 7)))
  {
    return (((s->w_bits <= s->hash_bits) && s->level) ? (fixedlen) : (storelen)) + wraplen;
  }
  return (((((sourceLen + (sourceLen >> 12)) + (sourceLen >> 14)) + (sourceLen >> 25)) + 13) - 6) + wraplen;
}

static void putShortMSB(deflate_state *s, uInt b)
{
  {
    s->pending_buf[s->pending++] = (Bytef) ((Byte) (b >> 8));
  }
  ;
  {
    s->pending_buf[s->pending++] = (Bytef) ((Byte) (b & 0xff));
  }
  ;
}

static void flush_pending(z_streamp strm)
{
  unsigned len;
  deflate_state *s = strm->state;
  _tr_flush_bits(s);
  len = s->pending;
  if (len > strm->avail_out)
  {
    len = strm->avail_out;
  }
  if (len == 0)
  {
    return;
  }
  memcpy(strm->next_out, s->pending_out, len);
  strm->next_out += len;
  s->pending_out += len;
  strm->total_out += len;
  strm->avail_out -= len;
  s->pending -= len;
  if (s->pending == 0)
  {
    s->pending_out = s->pending_buf;
  }
}

int deflate(z_streamp strm, int flush)
{
  int old_flush;
  deflate_state *s;
  unsigned int s_idx = 0;
  if ((deflateStateCheck(strm) || (flush > 5)) || (flush < 0))
  {
    return -2;
  }
  s_idx = strm->state;
  if (((strm->next_out == 0) || ((strm->avail_in != 0) && (strm->next_in == 0))) || ((s->status == 666) && (flush != 4)))
  {
    return strm->msg = z_errmsg[2 - (-2)], -2;
  }
  if (strm->avail_out == 0)
  {
    return strm->msg = z_errmsg[2 - (-5)], -5;
  }
  old_flush = s->last_flush;
  s->last_flush = flush;
  if (s->pending != 0)
  {
    flush_pending(strm);
    if (strm->avail_out == 0)
    {
      s->last_flush = -1;
      return 0;
    }
  }
  else
    if (((strm->avail_in == 0) && (((flush * 2) - ((flush > 4) ? (9) : (0))) <= ((old_flush * 2) - ((old_flush > 4) ? (9) : (0))))) && (flush != 4))
  {
    return strm->msg = z_errmsg[2 - (-5)], -5;
  }
  if ((s->status == 666) && (strm->avail_in != 0))
  {
    return strm->msg = z_errmsg[2 - (-5)], -5;
  }
  if ((s->status == 42) && (s->wrap == 0))
  {
    s->status = 113;
  }
  if (s->status == 42)
  {
    uInt header = (8 + ((s->w_bits - 8) << 4)) << 8;
    uInt level_flags;
    if ((s->strategy >= 2) || (s->level < 2))
    {
      level_flags = 0;
    }
    else
      if (s->level < 6)
    {
      level_flags = 1;
    }
    else
      if (s->level == 6)
    {
      level_flags = 2;
    }
    else
      level_flags = 3;
    header |= level_flags << 6;
    if (s->strstart != 0)
    {
      header |= 0x20;
    }
    header += 31 - (header % 31);
    putShortMSB(s, header);
    if (s->strstart != 0)
    {
      putShortMSB(s, (uInt) (strm->adler >> 16));
      putShortMSB(s, (uInt) (strm->adler & 0xffff));
    }
    strm->adler = adler32(0L, 0, 0);
    s->status = 113;
    flush_pending(strm);
    if (s->pending != 0)
    {
      s->last_flush = -1;
      return 0;
    }
  }
  if (((strm->avail_in != 0) || (s->lookahead != 0)) || ((flush != 0) && (s->status != 666)))
  {
    block_state bstate;
    bstate = (s->level == 0) ? (deflate_stored(s, flush)) : ((s->strategy == 2) ? (deflate_huff(s, flush)) : ((s->strategy == 3) ? (deflate_rle(s, flush)) : ((*configuration_table[s->level].func)(s, flush))));
    if ((bstate == finish_started) || (bstate == finish_done))
    {
      s->status = 666;
    }
    if ((bstate == need_more) || (bstate == finish_started))
    {
      if (strm->avail_out == 0)
      {
        s->last_flush = -1;
      }
      return 0;
    }
    if (bstate == block_done)
    {
      if (flush == 1)
      {
        _tr_align(s);
      }
      else
        if (flush != 5)
      {
        _tr_stored_block(s, (char *) 0, 0L, 0);
        if (flush == 3)
        {
          do
          {
            s->head[s->hash_size - 1] = 0;
            memset((Bytef *) s->head, 0, ((unsigned) (s->hash_size - 1)) * (sizeof(*s->head)));
          }
          while (0);
          if (s->lookahead == 0)
          {
            s->strstart = 0;
            s->block_start = 0L;
            s->insert = 0;
          }
        }
      }
      flush_pending(strm);
      if (strm->avail_out == 0)
      {
        s->last_flush = -1;
        return 0;
      }
    }
  }
  if (flush != 4)
  {
    return 0;
  }
  if (s->wrap <= 0)
  {
    return 1;
  }
  {
    putShortMSB(s, (uInt) (strm->adler >> 16));
    putShortMSB(s, (uInt) (strm->adler & 0xffff));
  }
  flush_pending(strm);
  if (s->wrap > 0)
  {
    s->wrap = -s->wrap;
  }
  return (s->pending != 0) ? (0) : (1);
}

int deflateEnd(z_streamp strm)
{
  int status;
  if (deflateStateCheck(strm))
  {
    return -2;
  }
  status = strm->state->status;
  {
    if (strm->state->pending_buf)
    {
      (*strm->zfree)(strm->opaque, (voidpf) strm->state->pending_buf);
    }
  }
  ;
  {
    if (strm->state->head)
    {
      (*strm->zfree)(strm->opaque, (voidpf) strm->state->head);
    }
  }
  ;
  {
    if (strm->state->prev)
    {
      (*strm->zfree)(strm->opaque, (voidpf) strm->state->prev);
    }
  }
  ;
  {
    if (strm->state->window)
    {
      (*strm->zfree)(strm->opaque, (voidpf) strm->state->window);
    }
  }
  ;
  (*strm->zfree)(strm->opaque, (voidpf) strm->state);
  strm->state = 0;
  return (status == 113) ? (-3) : (0);
}

int deflateCopy(z_streamp dest, z_streamp source)
{
  deflate_state *ds;
  unsigned int ds_idx = 0;
  deflate_state *ss;
  unsigned int ss_idx = 0;
  if (deflateStateCheck(source) || (dest == 0))
  {
    return -2;
  }
  ss_idx = source->state;
  memcpy((voidpf) dest, (voidpf) source, sizeof(z_stream));
  ds_idx = (deflate_state *) (*dest->zalloc)(dest->opaque, 1, sizeof(deflate_state));
  if ((&ds[ds_idx]) == 0)
  {
    return -4;
  }
  dest->state = (struct internal_state *) ds;
  memcpy((voidpf) ds, (voidpf) ss, sizeof(deflate_state));
  ds->strm = dest;
  ds->window = (Bytef *) (*dest->zalloc)(dest->opaque, ds->w_size, 2 * (sizeof(Byte)));
  ds->prev = (Posf *) (*dest->zalloc)(dest->opaque, ds->w_size, sizeof(Pos));
  ds->head = (Posf *) (*dest->zalloc)(dest->opaque, ds->hash_size, sizeof(Pos));
  ds->pending_buf = (uchf *) (*dest->zalloc)(dest->opaque, ds->lit_bufsize, 4);
  if ((((ds->window == 0) || (ds->prev == 0)) || (ds->head == 0)) || (ds->pending_buf == 0))
  {
    deflateEnd(dest);
    return -4;
  }
  memcpy(ds->window, ss->window, (ds->w_size * 2) * (sizeof(Byte)));
  memcpy((voidpf) ds->prev, (voidpf) ss->prev, ds->w_size * (sizeof(Pos)));
  memcpy((voidpf) ds->head, (voidpf) ss->head, ds->hash_size * (sizeof(Pos)));
  memcpy(ds->pending_buf, ss->pending_buf, (uInt) ds->pending_buf_size);
  ds->pending_out = ds->pending_buf + (ss->pending_out - ss->pending_buf);
  ds->sym_buf = ds->pending_buf + ds->lit_bufsize;
  ds->l_desc.dyn_tree = ds->dyn_ltree;
  ds->d_desc.dyn_tree = ds->dyn_dtree;
  ds->bl_desc.dyn_tree = ds->bl_tree;
  return 0;
}

static uInt longest_match(deflate_state *s, IPos cur_match)
{
  unsigned chain_length = s->max_chain_length;
  register Bytef *scan = s->window + s->strstart;
  unsigned int scan_idx = 0;
  register Bytef *match;
  unsigned int match_idx = 0;
  register int len;
  int best_len = (int) s->prev_length;
  int nice_match = s->nice_match;
  IPos limit = (s->strstart > ((IPos) (s->w_size - ((258 + 3) + 1)))) ? (s->strstart - ((IPos) (s->w_size - ((258 + 3) + 1)))) : (0);
  Posf *prev = s->prev;
  uInt wmask = s->w_mask;
  register Bytef *strend = (s->window + s->strstart) + 258;
  register Byte scan_end1 = scan[(best_len - 1) + scan_idx];
  register Byte scan_end = scan[best_len + scan_idx];
  ;
  if (s->prev_length >= s->good_match)
  {
    chain_length >>= 2;
  }
  if (((uInt) nice_match) > s->lookahead)
  {
    nice_match = (int) s->lookahead;
  }
  ;
  do
  {
    ;
    match_idx = s->window + cur_match;
    if ((((match[best_len + match_idx] != scan_end) || (match[(best_len - 1) + match_idx] != scan_end1)) || (match[match_idx] != scan[scan_idx])) || ((*(++(&match[match_idx]))) != scan[1 + scan_idx]))
    {
      continue;
    }
    scan_idx += 2, (&match[match_idx])++;
    match_idx += 1;
    ;
    do
    {
    }
    while ((((((((((*(++(&scan[scan_idx]))) == (*(++(&match[match_idx])))) && ((*(++(&scan[scan_idx]))) == (*(++(&match[match_idx]))))) && ((*(++(&scan[scan_idx]))) == (*(++(&match[match_idx]))))) && ((*(++(&scan[scan_idx]))) == (*(++(&match[match_idx]))))) && ((*(++(&scan[scan_idx]))) == (*(++(&match[match_idx]))))) && ((*(++(&scan[scan_idx]))) == (*(++(&match[match_idx]))))) && ((*(++(&scan[scan_idx]))) == (*(++(&match[match_idx]))))) && ((*(++(&scan[scan_idx]))) == (*(++(&match[match_idx]))))) && ((&scan[scan_idx]) < strend));
    ;
    len = 258 - ((int) (strend - (&scan[scan_idx])));
    scan_idx = strend - 258;
    if (len > best_len)
    {
      s->match_start = cur_match;
      best_len = len;
      if (len >= nice_match)
      {
        break;
      }
      scan_end1 = scan[(best_len - 1) + scan_idx];
      scan_end = scan[best_len + scan_idx];
    }
  }
  while (((cur_match = prev[cur_match & wmask]) > limit) && ((--chain_length) != 0));
  if (((uInt) best_len) <= s->lookahead)
  {
    return (uInt) best_len;
  }
  return s->lookahead;
}

static block_state deflate_stored(deflate_state *s, int flush)
{
  unsigned min_block = ((s->pending_buf_size - 5) > s->w_size) ? (s->w_size) : (s->pending_buf_size - 5);
  unsigned len;
  unsigned left;
  unsigned have;
  unsigned last = 0;
  unsigned used = s->strm->avail_in;
  do
  {
    len = 65535;
    have = (s->bi_valid + 42) >> 3;
    if (s->strm->avail_out < have)
    {
      break;
    }
    have = s->strm->avail_out - have;
    left = s->strstart - s->block_start;
    if (len > (((ulg) left) + s->strm->avail_in))
    {
      len = left + s->strm->avail_in;
    }
    if (len > have)
    {
      len = have;
    }
    if ((len < min_block) && ((((len == 0) && (flush != 4)) || (flush == 0)) || (len != (left + s->strm->avail_in))))
    {
      break;
    }
    last = ((flush == 4) && (len == (left + s->strm->avail_in))) ? (1) : (0);
    _tr_stored_block(s, (char *) 0, 0L, last);
    s->pending_buf[s->pending - 4] = len;
    s->pending_buf[s->pending - 3] = len >> 8;
    s->pending_buf[s->pending - 2] = ~len;
    s->pending_buf[s->pending - 1] = (~len) >> 8;
    flush_pending(s->strm);
    if (left)
    {
      if (left > len)
      {
        left = len;
      }
      memcpy(s->strm->next_out, s->window + s->block_start, left);
      s->strm->next_out += left;
      s->strm->avail_out -= left;
      s->strm->total_out += left;
      s->block_start += left;
      len -= left;
    }
    if (len)
    {
      read_buf(s->strm, s->strm->next_out, len);
      s->strm->next_out += len;
      s->strm->avail_out -= len;
      s->strm->total_out += len;
    }
  }
  while (last == 0);
  used -= s->strm->avail_in;
  if (used)
  {
    if (used >= s->w_size)
    {
      s->matches = 2;
      memcpy(s->window, s->strm->next_in - s->w_size, s->w_size);
      s->strstart = s->w_size;
      s->insert = s->strstart;
    }
    else
    {
      if ((s->window_size - s->strstart) <= used)
      {
        s->strstart -= s->w_size;
        memcpy(s->window, s->window + s->w_size, s->strstart);
        if (s->matches < 2)
        {
          s->matches += 1;
        }
        if (s->insert > s->strstart)
        {
          s->insert = s->strstart;
        }
      }
      memcpy(s->window + s->strstart, s->strm->next_in - used, used);
      s->strstart += used;
      s->insert += (used > (s->w_size - s->insert)) ? (s->w_size - s->insert) : (used);
    }
    s->block_start = s->strstart;
  }
  if (s->high_water < s->strstart)
  {
    s->high_water = s->strstart;
  }
  if (last)
  {
    return finish_done;
  }
  if ((((flush != 0) && (flush != 4)) && (s->strm->avail_in == 0)) && (((long) s->strstart) == s->block_start))
  {
    return block_done;
  }
  have = s->window_size - s->strstart;
  if ((s->strm->avail_in > have) && (s->block_start >= ((long) s->w_size)))
  {
    s->block_start -= s->w_size;
    s->strstart -= s->w_size;
    memcpy(s->window, s->window + s->w_size, s->strstart);
    if (s->matches < 2)
    {
      s->matches += 1;
    }
    have += s->w_size;
    if (s->insert > s->strstart)
    {
      s->insert = s->strstart;
    }
  }
  if (have > s->strm->avail_in)
  {
    have = s->strm->avail_in;
  }
  if (have)
  {
    read_buf(s->strm, s->window + s->strstart, have);
    s->strstart += have;
    s->insert += (have > (s->w_size - s->insert)) ? (s->w_size - s->insert) : (have);
  }
  if (s->high_water < s->strstart)
  {
    s->high_water = s->strstart;
  }
  have = (s->bi_valid + 42) >> 3;
  have = ((s->pending_buf_size - have) > 65535) ? (65535) : (s->pending_buf_size - have);
  min_block = (have > s->w_size) ? (s->w_size) : (have);
  left = s->strstart - s->block_start;
  if ((left >= min_block) || ((((left || (flush == 4)) && (flush != 0)) && (s->strm->avail_in == 0)) && (left <= have)))
  {
    len = (left > have) ? (have) : (left);
    last = (((flush == 4) && (s->strm->avail_in == 0)) && (len == left)) ? (1) : (0);
    _tr_stored_block(s, ((charf *) s->window) + s->block_start, len, last);
    s->block_start += len;
    flush_pending(s->strm);
  }
  return (last) ? (finish_started) : (need_more);
}

static block_state deflate_fast(deflate_state *s, int flush)
{
  IPos hash_head;
  int bflush;
  for (;;)
  {
    if (s->lookahead < ((258 + 3) + 1))
    {
      fill_window(s);
      if ((s->lookahead < ((258 + 3) + 1)) && (flush == 0))
      {
        return need_more;
      }
      if (s->lookahead == 0)
      {
        break;
      }
    }
    hash_head = 0;
    if (s->lookahead >= 3)
    {
      s->ins_h = ((s->ins_h << s->hash_shift) ^ s->window[s->strstart + (3 - 1)]) & s->hash_mask, hash_head = (s->prev[s->strstart & s->w_mask] = s->head[s->ins_h]), s->head[s->ins_h] = (Pos) s->strstart;
    }
    if ((hash_head != 0) && ((s->strstart - hash_head) <= (s->w_size - ((258 + 3) + 1))))
    {
      s->match_length = longest_match(s, hash_head);
    }
    if (s->match_length >= 3)
    {
      ;
      {
        uch len = (uch) (s->match_length - 3);
        ush dist = (ush) (s->strstart - s->match_start);
        s->sym_buf[s->sym_next++] = (uch) dist;
        s->sym_buf[s->sym_next++] = (uch) (dist >> 8);
        s->sym_buf[s->sym_next++] = len;
        dist -= 1;
        s->dyn_ltree[(_length_code[len] + 256) + 1].fc.freq += 1;
        s->dyn_dtree[(dist < 256) ? (_dist_code[dist]) : (_dist_code[256 + (dist >> 7)])].fc.freq += 1;
        bflush = s->sym_next == s->sym_end;
      }
      ;
      s->lookahead -= s->match_length;
      if ((s->match_length <= s->max_lazy_match) && (s->lookahead >= 3))
      {
        s->match_length -= 1;
        do
        {
          s->strstart += 1;
          s->ins_h = ((s->ins_h << s->hash_shift) ^ s->window[s->strstart + (3 - 1)]) & s->hash_mask, hash_head = (s->prev[s->strstart & s->w_mask] = s->head[s->ins_h]), s->head[s->ins_h] = (Pos) s->strstart;
        }
        while ((--s->match_length) != 0);
        s->strstart += 1;
      }
      else
      {
        s->strstart += s->match_length;
        s->match_length = 0;
        s->ins_h = s->window[s->strstart];
        s->ins_h = ((s->ins_h << s->hash_shift) ^ s->window[s->strstart + 1]) & s->hash_mask;
      }
    }
    else
    {
      ;
      {
        uch cc = s->window[s->strstart];
        s->sym_buf[s->sym_next++] = 0;
        s->sym_buf[s->sym_next++] = 0;
        s->sym_buf[s->sym_next++] = cc;
        s->dyn_ltree[cc].fc.freq += 1;
        bflush = s->sym_next == s->sym_end;
      }
      ;
      s->lookahead -= 1;
      s->strstart += 1;
    }
    if (bflush)
    {
      {
        _tr_flush_block(s, (s->block_start >= 0L) ? ((charf *) (&s->window[(unsigned) s->block_start])) : ((charf *) 0), (ulg) (((long) s->strstart) - s->block_start), 0);
        s->block_start = s->strstart;
        flush_pending(s->strm);
        ;
      }
      ;
      if (s->strm->avail_out == 0)
      {
        return (0) ? (finish_started) : (need_more);
      }
    }
    ;
  }

  s->insert = (s->strstart < (3 - 1)) ? (s->strstart) : (3 - 1);
  if (flush == 4)
  {
    {
      {
        _tr_flush_block(s, (s->block_start >= 0L) ? ((charf *) (&s->window[(unsigned) s->block_start])) : ((charf *) 0), (ulg) (((long) s->strstart) - s->block_start), 1);
        s->block_start = s->strstart;
        flush_pending(s->strm);
        ;
      }
      ;
      if (s->strm->avail_out == 0)
      {
        return (1) ? (finish_started) : (need_more);
      }
    }
    ;
    return finish_done;
  }
  if (s->sym_next)
  {
    {
      _tr_flush_block(s, (s->block_start >= 0L) ? ((charf *) (&s->window[(unsigned) s->block_start])) : ((charf *) 0), (ulg) (((long) s->strstart) - s->block_start), 0);
      s->block_start = s->strstart;
      flush_pending(s->strm);
      ;
    }
    ;
    if (s->strm->avail_out == 0)
    {
      return (0) ? (finish_started) : (need_more);
    }
  }
  ;
  return block_done;
}

static block_state deflate_slow(deflate_state *s, int flush)
{
  IPos hash_head;
  int bflush;
  for (;;)
  {
    if (s->lookahead < ((258 + 3) + 1))
    {
      fill_window(s);
      if ((s->lookahead < ((258 + 3) + 1)) && (flush == 0))
      {
        return need_more;
      }
      if (s->lookahead == 0)
      {
        break;
      }
    }
    hash_head = 0;
    if (s->lookahead >= 3)
    {
      s->ins_h = ((s->ins_h << s->hash_shift) ^ s->window[s->strstart + (3 - 1)]) & s->hash_mask, hash_head = (s->prev[s->strstart & s->w_mask] = s->head[s->ins_h]), s->head[s->ins_h] = (Pos) s->strstart;
    }
    s->prev_length = s->match_length, s->prev_match = s->match_start;
    s->match_length = 3 - 1;
    if (((hash_head != 0) && (s->prev_length < s->max_lazy_match)) && ((s->strstart - hash_head) <= (s->w_size - ((258 + 3) + 1))))
    {
      s->match_length = longest_match(s, hash_head);
      if ((s->match_length <= 5) && (s->strategy == 1))
      {
        s->match_length = 3 - 1;
      }
    }
    if ((s->prev_length >= 3) && (s->match_length <= s->prev_length))
    {
      uInt max_insert = (s->strstart + s->lookahead) - 3;
      ;
      {
        uch len = (uch) (s->prev_length - 3);
        ush dist = (ush) ((s->strstart - 1) - s->prev_match);
        s->sym_buf[s->sym_next++] = (uch) dist;
        s->sym_buf[s->sym_next++] = (uch) (dist >> 8);
        s->sym_buf[s->sym_next++] = len;
        dist -= 1;
        s->dyn_ltree[(_length_code[len] + 256) + 1].fc.freq += 1;
        s->dyn_dtree[(dist < 256) ? (_dist_code[dist]) : (_dist_code[256 + (dist >> 7)])].fc.freq += 1;
        bflush = s->sym_next == s->sym_end;
      }
      ;
      s->lookahead -= s->prev_length - 1;
      s->prev_length -= 2;
      do
      {
        if ((++s->strstart) <= max_insert)
        {
          s->ins_h = ((s->ins_h << s->hash_shift) ^ s->window[s->strstart + (3 - 1)]) & s->hash_mask, hash_head = (s->prev[s->strstart & s->w_mask] = s->head[s->ins_h]), s->head[s->ins_h] = (Pos) s->strstart;
        }
      }
      while ((--s->prev_length) != 0);
      s->match_available = 0;
      s->match_length = 3 - 1;
      s->strstart += 1;
      if (bflush)
      {
        {
          _tr_flush_block(s, (s->block_start >= 0L) ? ((charf *) (&s->window[(unsigned) s->block_start])) : ((charf *) 0), (ulg) (((long) s->strstart) - s->block_start), 0);
          s->block_start = s->strstart;
          flush_pending(s->strm);
          ;
        }
        ;
        if (s->strm->avail_out == 0)
        {
          return (0) ? (finish_started) : (need_more);
        }
      }
      ;
    }
    else
      if (s->match_available)
    {
      ;
      {
        uch cc = s->window[s->strstart - 1];
        s->sym_buf[s->sym_next++] = 0;
        s->sym_buf[s->sym_next++] = 0;
        s->sym_buf[s->sym_next++] = cc;
        s->dyn_ltree[cc].fc.freq += 1;
        bflush = s->sym_next == s->sym_end;
      }
      ;
      if (bflush)
      {
        {
          _tr_flush_block(s, (s->block_start >= 0L) ? ((charf *) (&s->window[(unsigned) s->block_start])) : ((charf *) 0), (ulg) (((long) s->strstart) - s->block_start), 0);
          s->block_start = s->strstart;
          flush_pending(s->strm);
          ;
        }
        ;
      }
      s->strstart += 1;
      s->lookahead -= 1;
      if (s->strm->avail_out == 0)
      {
        return need_more;
      }
    }
    else
    {
      s->match_available = 1;
      s->strstart += 1;
      s->lookahead -= 1;
    }
  }

  ;
  if (s->match_available)
  {
    ;
    {
      uch cc = s->window[s->strstart - 1];
      s->sym_buf[s->sym_next++] = 0;
      s->sym_buf[s->sym_next++] = 0;
      s->sym_buf[s->sym_next++] = cc;
      s->dyn_ltree[cc].fc.freq += 1;
      bflush = s->sym_next == s->sym_end;
    }
    ;
    s->match_available = 0;
  }
  s->insert = (s->strstart < (3 - 1)) ? (s->strstart) : (3 - 1);
  if (flush == 4)
  {
    {
      {
        _tr_flush_block(s, (s->block_start >= 0L) ? ((charf *) (&s->window[(unsigned) s->block_start])) : ((charf *) 0), (ulg) (((long) s->strstart) - s->block_start), 1);
        s->block_start = s->strstart;
        flush_pending(s->strm);
        ;
      }
      ;
      if (s->strm->avail_out == 0)
      {
        return (1) ? (finish_started) : (need_more);
      }
    }
    ;
    return finish_done;
  }
  if (s->sym_next)
  {
    {
      _tr_flush_block(s, (s->block_start >= 0L) ? ((charf *) (&s->window[(unsigned) s->block_start])) : ((charf *) 0), (ulg) (((long) s->strstart) - s->block_start), 0);
      s->block_start = s->strstart;
      flush_pending(s->strm);
      ;
    }
    ;
    if (s->strm->avail_out == 0)
    {
      return (0) ? (finish_started) : (need_more);
    }
  }
  ;
  return block_done;
}

static block_state deflate_rle(deflate_state *s, int flush)
{
  int bflush;
  uInt prev;
  Bytef *scan;
  unsigned int scan_idx = 0;
  Bytef *strend;
  unsigned int strend_idx = 0;
  for (;;)
  {
    if (s->lookahead <= 258)
    {
      fill_window(s);
      if ((s->lookahead <= 258) && (flush == 0))
      {
        return need_more;
      }
      if (s->lookahead == 0)
      {
        break;
      }
    }
    s->match_length = 0;
    if ((s->lookahead >= 3) && (s->strstart > 0))
    {
      scan_idx = (s->window + s->strstart) - 1;
      prev = scan[scan_idx];
      if (((prev == (*(++(&scan[scan_idx])))) && (prev == (*(++(&scan[scan_idx]))))) && (prev == (*(++(&scan[scan_idx])))))
      {
        strend_idx = (s->window + s->strstart) + 258;
        do
        {
        }
        while (((((((((prev == (*(++(&scan[scan_idx])))) && (prev == (*(++(&scan[scan_idx]))))) && (prev == (*(++(&scan[scan_idx]))))) && (prev == (*(++(&scan[scan_idx]))))) && (prev == (*(++(&scan[scan_idx]))))) && (prev == (*(++(&scan[scan_idx]))))) && (prev == (*(++(&scan[scan_idx]))))) && (prev == (*(++(&scan[scan_idx]))))) && ((&scan[scan_idx]) < (&strend[strend_idx])));
        s->match_length = 258 - ((uInt) ((&strend[strend_idx]) - (&scan[scan_idx])));
        if (s->match_length > s->lookahead)
        {
          s->match_length = s->lookahead;
        }
      }
      ;
    }
    if (s->match_length >= 3)
    {
      ;
      {
        uch len = (uch) (s->match_length - 3);
        ush dist = (ush) 1;
        s->sym_buf[s->sym_next++] = (uch) dist;
        s->sym_buf[s->sym_next++] = (uch) (dist >> 8);
        s->sym_buf[s->sym_next++] = len;
        dist -= 1;
        s->dyn_ltree[(_length_code[len] + 256) + 1].fc.freq += 1;
        s->dyn_dtree[(dist < 256) ? (_dist_code[dist]) : (_dist_code[256 + (dist >> 7)])].fc.freq += 1;
        bflush = s->sym_next == s->sym_end;
      }
      ;
      s->lookahead -= s->match_length;
      s->strstart += s->match_length;
      s->match_length = 0;
    }
    else
    {
      ;
      {
        uch cc = s->window[s->strstart];
        s->sym_buf[s->sym_next++] = 0;
        s->sym_buf[s->sym_next++] = 0;
        s->sym_buf[s->sym_next++] = cc;
        s->dyn_ltree[cc].fc.freq += 1;
        bflush = s->sym_next == s->sym_end;
      }
      ;
      s->lookahead -= 1;
      s->strstart += 1;
    }
    if (bflush)
    {
      {
        _tr_flush_block(s, (s->block_start >= 0L) ? ((charf *) (&s->window[(unsigned) s->block_start])) : ((charf *) 0), (ulg) (((long) s->strstart) - s->block_start), 0);
        s->block_start = s->strstart;
        flush_pending(s->strm);
        ;
      }
      ;
      if (s->strm->avail_out == 0)
      {
        return (0) ? (finish_started) : (need_more);
      }
    }
    ;
  }

  s->insert = 0;
  if (flush == 4)
  {
    {
      {
        _tr_flush_block(s, (s->block_start >= 0L) ? ((charf *) (&s->window[(unsigned) s->block_start])) : ((charf *) 0), (ulg) (((long) s->strstart) - s->block_start), 1);
        s->block_start = s->strstart;
        flush_pending(s->strm);
        ;
      }
      ;
      if (s->strm->avail_out == 0)
      {
        return (1) ? (finish_started) : (need_more);
      }
    }
    ;
    return finish_done;
  }
  if (s->sym_next)
  {
    {
      _tr_flush_block(s, (s->block_start >= 0L) ? ((charf *) (&s->window[(unsigned) s->block_start])) : ((charf *) 0), (ulg) (((long) s->strstart) - s->block_start), 0);
      s->block_start = s->strstart;
      flush_pending(s->strm);
      ;
    }
    ;
    if (s->strm->avail_out == 0)
    {
      return (0) ? (finish_started) : (need_more);
    }
  }
  ;
  return block_done;
}

static block_state deflate_huff(deflate_state *s, int flush)
{
  int bflush;
  for (;;)
  {
    if (s->lookahead == 0)
    {
      fill_window(s);
      if (s->lookahead == 0)
      {
        if (flush == 0)
        {
          return need_more;
        }
        break;
      }
    }
    s->match_length = 0;
    ;
    {
      uch cc = s->window[s->strstart];
      s->sym_buf[s->sym_next++] = 0;
      s->sym_buf[s->sym_next++] = 0;
      s->sym_buf[s->sym_next++] = cc;
      s->dyn_ltree[cc].fc.freq += 1;
      bflush = s->sym_next == s->sym_end;
    }
    ;
    s->lookahead -= 1;
    s->strstart += 1;
    if (bflush)
    {
      {
        _tr_flush_block(s, (s->block_start >= 0L) ? ((charf *) (&s->window[(unsigned) s->block_start])) : ((charf *) 0), (ulg) (((long) s->strstart) - s->block_start), 0);
        s->block_start = s->strstart;
        flush_pending(s->strm);
        ;
      }
      ;
      if (s->strm->avail_out == 0)
      {
        return (0) ? (finish_started) : (need_more);
      }
    }
    ;
  }

  s->insert = 0;
  if (flush == 4)
  {
    {
      {
        _tr_flush_block(s, (s->block_start >= 0L) ? ((charf *) (&s->window[(unsigned) s->block_start])) : ((charf *) 0), (ulg) (((long) s->strstart) - s->block_start), 1);
        s->block_start = s->strstart;
        flush_pending(s->strm);
        ;
      }
      ;
      if (s->strm->avail_out == 0)
      {
        return (1) ? (finish_started) : (need_more);
      }
    }
    ;
    return finish_done;
  }
  if (s->sym_next)
  {
    {
      _tr_flush_block(s, (s->block_start >= 0L) ? ((charf *) (&s->window[(unsigned) s->block_start])) : ((charf *) 0), (ulg) (((long) s->strstart) - s->block_start), 0);
      s->block_start = s->strstart;
      flush_pending(s->strm);
      ;
    }
    ;
    if (s->strm->avail_out == 0)
    {
      return (0) ? (finish_started) : (need_more);
    }
  }
  ;
  return block_done;
}

void helper_fill_window_1(deflate_state * const s)
{
  ulg curr = s->strstart + ((ulg) s->lookahead);
  ulg init;
  if (s->high_water < curr)
  {
    init = s->window_size - curr;
    if (init > 258)
    {
      init = 258;
    }
    memset(s->window + curr, 0, (unsigned) init);
    s->high_water = curr + init;
  }
  else
    if (s->high_water < (((ulg) curr) + 258))
  {
    init = (((ulg) curr) + 258) - s->high_water;
    if (init > (s->window_size - s->high_water))
    {
      init = s->window_size - s->high_water;
    }
    memset(s->window + s->high_water, 0, (unsigned) init);
    s->high_water += init;
  }
}

void helper_fill_window_2(unsigned * const n_ref, unsigned * const more_ref, deflate_state * const s, uInt wsize)
{
  unsigned n = *n_ref;
  unsigned more = *more_ref;
  more = (unsigned) ((s->window_size - ((ulg) s->lookahead)) - ((ulg) s->strstart));
  if ((sizeof(int)) <= 2)
  {
    if (((more == 0) && (s->strstart == 0)) && (s->lookahead == 0))
    {
      more = wsize;
    }
    else
      if (more == ((unsigned) (-1)))
    {
      more -= 1;
    }
  }
  if (s->strstart >= (wsize + (s->w_size - ((258 + 3) + 1))))
  {
    memcpy(s->window, s->window + wsize, ((unsigned) wsize) - more);
    s->match_start -= wsize;
    s->strstart -= wsize;
    s->block_start -= (long) wsize;
    if (s->insert > s->strstart)
    {
      s->insert = s->strstart;
    }
    slide_hash(s);
    more += wsize;
  }
  if (s->strm->avail_in == 0)
  {
    break;
  }
  ;
  n = read_buf(s->strm, (s->window + s->strstart) + s->lookahead, more);
  s->lookahead += n;
  if ((s->lookahead + s->insert) >= 3)
  {
    helper_helper_fill_window_2_1(s);
  }
  *n_ref = n;
  *more_ref = more;
}

void helper_deflateParams_1(int * const level_ref, deflate_state * const s)
{
  int level = *level_ref;
  if ((s->level == 0) && (s->matches != 0))
  {
    if (s->matches == 1)
    {
      slide_hash(s);
    }
    else
      do
    {
      s->head[s->hash_size - 1] = 0;
      memset((Bytef *) s->head, 0, ((unsigned) (s->hash_size - 1)) * (sizeof(*s->head)));
    }
    while (0);
    s->matches = 0;
  }
  s->level = level;
  s->max_lazy_match = configuration_table[level].max_lazy;
  s->good_match = configuration_table[level].good_length;
  s->nice_match = configuration_table[level].nice_length;
  s->max_chain_length = configuration_table[level].max_chain;
  *level_ref = level;
}

int helper_deflate_1(z_streamp * const strm_ref, deflate_state * const s)
{
  z_streamp strm = *strm_ref;
  uInt header = (8 + ((s->w_bits - 8) << 4)) << 8;
  uInt level_flags;
  if ((s->strategy >= 2) || (s->level < 2))
  {
    level_flags = 0;
  }
  else
    if (s->level < 6)
  {
    level_flags = 1;
  }
  else
    if (s->level == 6)
  {
    level_flags = 2;
  }
  else
    level_flags = 3;
  header |= level_flags << 6;
  if (s->strstart != 0)
  {
    header |= 0x20;
  }
  header += 31 - (header % 31);
  putShortMSB(s, header);
  if (s->strstart != 0)
  {
    putShortMSB(s, (uInt) (strm->adler >> 16));
    putShortMSB(s, (uInt) (strm->adler & 0xffff));
  }
  strm->adler = adler32(0L, 0, 0);
  s->status = 113;
  flush_pending(strm);
  if (s->pending != 0)
  {
    s->last_flush = -1;
    return 0;
  }
  *strm_ref = strm;
}

int helper_deflate_2(z_streamp strm, int flush, deflate_state * const s)
{
  block_state bstate;
  bstate = (s->level == 0) ? (deflate_stored(s, flush)) : ((s->strategy == 2) ? (deflate_huff(s, flush)) : ((s->strategy == 3) ? (deflate_rle(s, flush)) : ((*configuration_table[s->level].func)(s, flush))));
  if ((bstate == finish_started) || (bstate == finish_done))
  {
    s->status = 666;
  }
  if ((bstate == need_more) || (bstate == finish_started))
  {
    if (strm->avail_out == 0)
    {
      s->last_flush = -1;
    }
    return 0;
  }
  if (bstate == block_done)
  {
    if (flush == 1)
    {
      _tr_align(s);
    }
    else
      if (flush != 5)
    {
      _tr_stored_block(s, (char *) 0, 0L, 0);
      if (flush == 3)
      {
        do
        {
          s->head[s->hash_size - 1] = 0;
          memset((Bytef *) s->head, 0, ((unsigned) (s->hash_size - 1)) * (sizeof(*s->head)));
        }
        while (0);
        if (s->lookahead == 0)
        {
          s->strstart = 0;
          s->block_start = 0L;
          s->insert = 0;
        }
      }
    }
    flush_pending(strm);
    if (strm->avail_out == 0)
    {
      s->last_flush = -1;
      return 0;
    }
  }
}

void helper_longest_match_1(unsigned int * const scan_idx_ref, unsigned int * const match_idx_ref, register int * const len_ref, int * const best_len_ref, register Byte * const scan_end1_ref, register Byte * const scan_end_ref, deflate_state * const s, IPos cur_match, register Bytef * const scan, register Bytef * const match, int nice_match, register Bytef * const strend)
{
  unsigned int scan_idx = *scan_idx_ref;
  unsigned int match_idx = *match_idx_ref;
  register int len = *len_ref;
  int best_len = *best_len_ref;
  register Byte scan_end1 = *scan_end1_ref;
  register Byte scan_end = *scan_end_ref;
  ;
  match_idx = s->window + cur_match;
  if ((((match[best_len + match_idx] != scan_end) || (match[(best_len - 1) + match_idx] != scan_end1)) || (match[match_idx] != scan[scan_idx])) || ((*(++(&match[match_idx]))) != scan[1 + scan_idx]))
  {
    continue;
  }
  scan_idx += 2, (&match[match_idx])++;
  match_idx += 1;
  ;
  do
  {
  }
  while ((((((((((*(++(&scan[scan_idx]))) == (*(++(&match[match_idx])))) && ((*(++(&scan[scan_idx]))) == (*(++(&match[match_idx]))))) && ((*(++(&scan[scan_idx]))) == (*(++(&match[match_idx]))))) && ((*(++(&scan[scan_idx]))) == (*(++(&match[match_idx]))))) && ((*(++(&scan[scan_idx]))) == (*(++(&match[match_idx]))))) && ((*(++(&scan[scan_idx]))) == (*(++(&match[match_idx]))))) && ((*(++(&scan[scan_idx]))) == (*(++(&match[match_idx]))))) && ((*(++(&scan[scan_idx]))) == (*(++(&match[match_idx]))))) && ((&scan[scan_idx]) < strend));
  ;
  len = 258 - ((int) (strend - (&scan[scan_idx])));
  scan_idx = strend - 258;
  if (len > best_len)
  {
    s->match_start = cur_match;
    best_len = len;
    if (len >= nice_match)
    {
      break;
    }
    scan_end1 = scan[(best_len - 1) + scan_idx];
    scan_end = scan[best_len + scan_idx];
  }
  *scan_idx_ref = scan_idx;
  *match_idx_ref = match_idx;
  *len_ref = len;
  *best_len_ref = best_len;
  *scan_end1_ref = scan_end1;
  *scan_end_ref = scan_end;
}

void helper_deflate_stored_1(deflate_state * const s, unsigned used)
{
  if (used >= s->w_size)
  {
    s->matches = 2;
    memcpy(s->window, s->strm->next_in - s->w_size, s->w_size);
    s->strstart = s->w_size;
    s->insert = s->strstart;
  }
  else
  {
    if ((s->window_size - s->strstart) <= used)
    {
      s->strstart -= s->w_size;
      memcpy(s->window, s->window + s->w_size, s->strstart);
      if (s->matches < 2)
      {
        s->matches += 1;
      }
      if (s->insert > s->strstart)
      {
        s->insert = s->strstart;
      }
    }
    memcpy(s->window + s->strstart, s->strm->next_in - used, used);
    s->strstart += used;
    s->insert += (used > (s->w_size - s->insert)) ? (s->w_size - s->insert) : (used);
  }
  s->block_start = s->strstart;
}

void helper_deflate_stored_2(unsigned * const len_ref, unsigned * const left_ref, unsigned * const have_ref, unsigned * const last_ref, deflate_state * const s, int flush, unsigned min_block)
{
  unsigned len = *len_ref;
  unsigned left = *left_ref;
  unsigned have = *have_ref;
  unsigned last = *last_ref;
  len = 65535;
  have = (s->bi_valid + 42) >> 3;
  if (s->strm->avail_out < have)
  {
    break;
  }
  have = s->strm->avail_out - have;
  left = s->strstart - s->block_start;
  if (len > (((ulg) left) + s->strm->avail_in))
  {
    len = left + s->strm->avail_in;
  }
  if (len > have)
  {
    len = have;
  }
  if ((len < min_block) && ((((len == 0) && (flush != 4)) || (flush == 0)) || (len != (left + s->strm->avail_in))))
  {
    break;
  }
  last = ((flush == 4) && (len == (left + s->strm->avail_in))) ? (1) : (0);
  _tr_stored_block(s, (char *) 0, 0L, last);
  s->pending_buf[s->pending - 4] = len;
  s->pending_buf[s->pending - 3] = len >> 8;
  s->pending_buf[s->pending - 2] = ~len;
  s->pending_buf[s->pending - 1] = (~len) >> 8;
  flush_pending(s->strm);
  if (left)
  {
    if (left > len)
    {
      left = len;
    }
    memcpy(s->strm->next_out, s->window + s->block_start, left);
    s->strm->next_out += left;
    s->strm->avail_out -= left;
    s->strm->total_out += left;
    s->block_start += left;
    len -= left;
  }
  if (len)
  {
    read_buf(s->strm, s->strm->next_out, len);
    s->strm->next_out += len;
    s->strm->avail_out -= len;
    s->strm->total_out += len;
  }
  *len_ref = len;
  *left_ref = left;
  *have_ref = have;
  *last_ref = last;
}

block_state helper_deflate_fast_1(deflate_state * const s)
{
  {
    {
      _tr_flush_block(s, (s->block_start >= 0L) ? ((charf *) (&s->window[(unsigned) s->block_start])) : ((charf *) 0), (ulg) (((long) s->strstart) - s->block_start), 1);
      s->block_start = s->strstart;
      flush_pending(s->strm);
      ;
    }
    ;
    if (s->strm->avail_out == 0)
    {
      return (1) ? (finish_started) : (need_more);
    }
  }
  ;
  return finish_done;
}

block_state helper_deflate_fast_2(IPos * const hash_head_ref, int * const bflush_ref, deflate_state * const s, int flush)
{
  IPos hash_head = *hash_head_ref;
  int bflush = *bflush_ref;
  if (s->lookahead < ((258 + 3) + 1))
  {
    fill_window(s);
    if ((s->lookahead < ((258 + 3) + 1)) && (flush == 0))
    {
      return need_more;
    }
    if (s->lookahead == 0)
    {
      break;
    }
  }
  hash_head = 0;
  if (s->lookahead >= 3)
  {
    s->ins_h = ((s->ins_h << s->hash_shift) ^ s->window[s->strstart + (3 - 1)]) & s->hash_mask, hash_head = (s->prev[s->strstart & s->w_mask] = s->head[s->ins_h]), s->head[s->ins_h] = (Pos) s->strstart;
  }
  if ((hash_head != 0) && ((s->strstart - hash_head) <= (s->w_size - ((258 + 3) + 1))))
  {
    s->match_length = longest_match(s, hash_head);
  }
  if (s->match_length >= 3)
  {
    helper_helper_deflate_fast_2_2(&hash_head, &bflush, s);
  }
  else
  {
    helper_helper_deflate_fast_2_1(&bflush, s);
  }
  if (bflush)
  {
    {
      _tr_flush_block(s, (s->block_start >= 0L) ? ((charf *) (&s->window[(unsigned) s->block_start])) : ((charf *) 0), (ulg) (((long) s->strstart) - s->block_start), 0);
      s->block_start = s->strstart;
      flush_pending(s->strm);
      ;
    }
    ;
    if (s->strm->avail_out == 0)
    {
      return (0) ? (finish_started) : (need_more);
    }
  }
  ;
  *hash_head_ref = hash_head;
  *bflush_ref = bflush;
}

block_state helper_deflate_slow_1(deflate_state * const s)
{
  {
    {
      _tr_flush_block(s, (s->block_start >= 0L) ? ((charf *) (&s->window[(unsigned) s->block_start])) : ((charf *) 0), (ulg) (((long) s->strstart) - s->block_start), 1);
      s->block_start = s->strstart;
      flush_pending(s->strm);
      ;
    }
    ;
    if (s->strm->avail_out == 0)
    {
      return (1) ? (finish_started) : (need_more);
    }
  }
  ;
  return finish_done;
}

block_state helper_deflate_slow_2(IPos * const hash_head_ref, int * const bflush_ref, deflate_state * const s, int flush)
{
  IPos hash_head = *hash_head_ref;
  int bflush = *bflush_ref;
  if (s->lookahead < ((258 + 3) + 1))
  {
    fill_window(s);
    if ((s->lookahead < ((258 + 3) + 1)) && (flush == 0))
    {
      return need_more;
    }
    if (s->lookahead == 0)
    {
      break;
    }
  }
  hash_head = 0;
  if (s->lookahead >= 3)
  {
    s->ins_h = ((s->ins_h << s->hash_shift) ^ s->window[s->strstart + (3 - 1)]) & s->hash_mask, hash_head = (s->prev[s->strstart & s->w_mask] = s->head[s->ins_h]), s->head[s->ins_h] = (Pos) s->strstart;
  }
  s->prev_length = s->match_length, s->prev_match = s->match_start;
  s->match_length = 3 - 1;
  if (((hash_head != 0) && (s->prev_length < s->max_lazy_match)) && ((s->strstart - hash_head) <= (s->w_size - ((258 + 3) + 1))))
  {
    s->match_length = longest_match(s, hash_head);
    if ((s->match_length <= 5) && (s->strategy == 1))
    {
      s->match_length = 3 - 1;
    }
  }
  if ((s->prev_length >= 3) && (s->match_length <= s->prev_length))
  {
    helper_helper_deflate_slow_2_2(&hash_head, &bflush, s);
  }
  else
    if (s->match_available)
  {
    helper_helper_deflate_slow_2_1(&bflush, s);
  }
  else
  {
    s->match_available = 1;
    s->strstart += 1;
    s->lookahead -= 1;
  }
  *hash_head_ref = hash_head;
  *bflush_ref = bflush;
}

block_state helper_deflate_rle_1(deflate_state * const s)
{
  {
    {
      _tr_flush_block(s, (s->block_start >= 0L) ? ((charf *) (&s->window[(unsigned) s->block_start])) : ((charf *) 0), (ulg) (((long) s->strstart) - s->block_start), 1);
      s->block_start = s->strstart;
      flush_pending(s->strm);
      ;
    }
    ;
    if (s->strm->avail_out == 0)
    {
      return (1) ? (finish_started) : (need_more);
    }
  }
  ;
  return finish_done;
}

block_state helper_deflate_rle_2(int * const bflush_ref, uInt * const prev_ref, unsigned int * const scan_idx_ref, unsigned int * const strend_idx_ref, deflate_state * const s, int flush, Bytef * const scan, Bytef * const strend)
{
  int bflush = *bflush_ref;
  uInt prev = *prev_ref;
  unsigned int scan_idx = *scan_idx_ref;
  unsigned int strend_idx = *strend_idx_ref;
  if (s->lookahead <= 258)
  {
    fill_window(s);
    if ((s->lookahead <= 258) && (flush == 0))
    {
      return need_more;
    }
    if (s->lookahead == 0)
    {
      break;
    }
  }
  s->match_length = 0;
  if ((s->lookahead >= 3) && (s->strstart > 0))
  {
    scan_idx = (s->window + s->strstart) - 1;
    prev = scan[scan_idx];
    if (((prev == (*(++(&scan[scan_idx])))) && (prev == (*(++(&scan[scan_idx]))))) && (prev == (*(++(&scan[scan_idx])))))
    {
      strend_idx = (s->window + s->strstart) + 258;
      do
      {
      }
      while (((((((((prev == (*(++(&scan[scan_idx])))) && (prev == (*(++(&scan[scan_idx]))))) && (prev == (*(++(&scan[scan_idx]))))) && (prev == (*(++(&scan[scan_idx]))))) && (prev == (*(++(&scan[scan_idx]))))) && (prev == (*(++(&scan[scan_idx]))))) && (prev == (*(++(&scan[scan_idx]))))) && (prev == (*(++(&scan[scan_idx]))))) && ((&scan[scan_idx]) < (&strend[strend_idx])));
      s->match_length = 258 - ((uInt) ((&strend[strend_idx]) - (&scan[scan_idx])));
      if (s->match_length > s->lookahead)
      {
        s->match_length = s->lookahead;
      }
    }
    ;
  }
  if (s->match_length >= 3)
  {
    helper_helper_deflate_rle_2_2(&bflush, s);
  }
  else
  {
    helper_helper_deflate_rle_2_1(&bflush, s);
  }
  if (bflush)
  {
    {
      _tr_flush_block(s, (s->block_start >= 0L) ? ((charf *) (&s->window[(unsigned) s->block_start])) : ((charf *) 0), (ulg) (((long) s->strstart) - s->block_start), 0);
      s->block_start = s->strstart;
      flush_pending(s->strm);
      ;
    }
    ;
    if (s->strm->avail_out == 0)
    {
      return (0) ? (finish_started) : (need_more);
    }
  }
  ;
  *bflush_ref = bflush;
  *prev_ref = prev;
  *scan_idx_ref = scan_idx;
  *strend_idx_ref = strend_idx;
}

block_state helper_deflate_huff_1(deflate_state * const s)
{
  {
    {
      _tr_flush_block(s, (s->block_start >= 0L) ? ((charf *) (&s->window[(unsigned) s->block_start])) : ((charf *) 0), (ulg) (((long) s->strstart) - s->block_start), 1);
      s->block_start = s->strstart;
      flush_pending(s->strm);
      ;
    }
    ;
    if (s->strm->avail_out == 0)
    {
      return (1) ? (finish_started) : (need_more);
    }
  }
  ;
  return finish_done;
}

block_state helper_deflate_huff_2(int * const bflush_ref, deflate_state * const s, int flush)
{
  int bflush = *bflush_ref;
  if (s->lookahead == 0)
  {
    fill_window(s);
    if (s->lookahead == 0)
    {
      if (flush == 0)
      {
        return need_more;
      }
      break;
    }
  }
  s->match_length = 0;
  ;
  {
    uch cc = s->window[s->strstart];
    s->sym_buf[s->sym_next++] = 0;
    s->sym_buf[s->sym_next++] = 0;
    s->sym_buf[s->sym_next++] = cc;
    s->dyn_ltree[cc].fc.freq += 1;
    bflush = s->sym_next == s->sym_end;
  }
  ;
  s->lookahead -= 1;
  s->strstart += 1;
  if (bflush)
  {
    {
      _tr_flush_block(s, (s->block_start >= 0L) ? ((charf *) (&s->window[(unsigned) s->block_start])) : ((charf *) 0), (ulg) (((long) s->strstart) - s->block_start), 0);
      s->block_start = s->strstart;
      flush_pending(s->strm);
      ;
    }
    ;
    if (s->strm->avail_out == 0)
    {
      return (0) ? (finish_started) : (need_more);
    }
  }
  ;
  *bflush_ref = bflush;
}

void helper_helper_fill_window_2_1(deflate_state * const s)
{
  uInt str = s->strstart - s->insert;
  s->ins_h = s->window[str];
  s->ins_h = ((s->ins_h << s->hash_shift) ^ s->window[str + 1]) & s->hash_mask;
  while (s->insert)
  {
    s->ins_h = ((s->ins_h << s->hash_shift) ^ s->window[(str + 3) - 1]) & s->hash_mask;
    s->prev[str & s->w_mask] = s->head[s->ins_h];
    s->head[s->ins_h] = (Pos) str;
    str += 1;
    s->insert -= 1;
    if ((s->lookahead + s->insert) < 3)
    {
      break;
    }
  }

}

void helper_helper_deflate_fast_2_1(int * const bflush_ref, deflate_state * const s)
{
  int bflush = *bflush_ref;
  ;
  {
    uch cc = s->window[s->strstart];
    s->sym_buf[s->sym_next++] = 0;
    s->sym_buf[s->sym_next++] = 0;
    s->sym_buf[s->sym_next++] = cc;
    s->dyn_ltree[cc].fc.freq += 1;
    bflush = s->sym_next == s->sym_end;
  }
  ;
  s->lookahead -= 1;
  s->strstart += 1;
  *bflush_ref = bflush;
}

void helper_helper_deflate_fast_2_2(IPos * const hash_head_ref, int * const bflush_ref, deflate_state * const s)
{
  IPos hash_head = *hash_head_ref;
  int bflush = *bflush_ref;
  ;
  {
    uch len = (uch) (s->match_length - 3);
    ush dist = (ush) (s->strstart - s->match_start);
    s->sym_buf[s->sym_next++] = (uch) dist;
    s->sym_buf[s->sym_next++] = (uch) (dist >> 8);
    s->sym_buf[s->sym_next++] = len;
    dist -= 1;
    s->dyn_ltree[(_length_code[len] + 256) + 1].fc.freq += 1;
    s->dyn_dtree[(dist < 256) ? (_dist_code[dist]) : (_dist_code[256 + (dist >> 7)])].fc.freq += 1;
    bflush = s->sym_next == s->sym_end;
  }
  ;
  s->lookahead -= s->match_length;
  if ((s->match_length <= s->max_lazy_match) && (s->lookahead >= 3))
  {
    s->match_length -= 1;
    do
    {
      s->strstart += 1;
      s->ins_h = ((s->ins_h << s->hash_shift) ^ s->window[s->strstart + (3 - 1)]) & s->hash_mask, hash_head = (s->prev[s->strstart & s->w_mask] = s->head[s->ins_h]), s->head[s->ins_h] = (Pos) s->strstart;
    }
    while ((--s->match_length) != 0);
    s->strstart += 1;
  }
  else
  {
    s->strstart += s->match_length;
    s->match_length = 0;
    s->ins_h = s->window[s->strstart];
    s->ins_h = ((s->ins_h << s->hash_shift) ^ s->window[s->strstart + 1]) & s->hash_mask;
  }
  *hash_head_ref = hash_head;
  *bflush_ref = bflush;
}

block_state helper_helper_deflate_slow_2_1(int * const bflush_ref, deflate_state * const s)
{
  int bflush = *bflush_ref;
  ;
  {
    uch cc = s->window[s->strstart - 1];
    s->sym_buf[s->sym_next++] = 0;
    s->sym_buf[s->sym_next++] = 0;
    s->sym_buf[s->sym_next++] = cc;
    s->dyn_ltree[cc].fc.freq += 1;
    bflush = s->sym_next == s->sym_end;
  }
  ;
  if (bflush)
  {
    {
      _tr_flush_block(s, (s->block_start >= 0L) ? ((charf *) (&s->window[(unsigned) s->block_start])) : ((charf *) 0), (ulg) (((long) s->strstart) - s->block_start), 0);
      s->block_start = s->strstart;
      flush_pending(s->strm);
      ;
    }
    ;
  }
  s->strstart += 1;
  s->lookahead -= 1;
  if (s->strm->avail_out == 0)
  {
    return need_more;
  }
  *bflush_ref = bflush;
}

block_state helper_helper_deflate_slow_2_2(IPos * const hash_head_ref, int * const bflush_ref, deflate_state * const s)
{
  IPos hash_head = *hash_head_ref;
  int bflush = *bflush_ref;
  uInt max_insert = (s->strstart + s->lookahead) - 3;
  ;
  {
    uch len = (uch) (s->prev_length - 3);
    ush dist = (ush) ((s->strstart - 1) - s->prev_match);
    s->sym_buf[s->sym_next++] = (uch) dist;
    s->sym_buf[s->sym_next++] = (uch) (dist >> 8);
    s->sym_buf[s->sym_next++] = len;
    dist -= 1;
    s->dyn_ltree[(_length_code[len] + 256) + 1].fc.freq += 1;
    s->dyn_dtree[(dist < 256) ? (_dist_code[dist]) : (_dist_code[256 + (dist >> 7)])].fc.freq += 1;
    bflush = s->sym_next == s->sym_end;
  }
  ;
  s->lookahead -= s->prev_length - 1;
  s->prev_length -= 2;
  do
  {
    if ((++s->strstart) <= max_insert)
    {
      s->ins_h = ((s->ins_h << s->hash_shift) ^ s->window[s->strstart + (3 - 1)]) & s->hash_mask, hash_head = (s->prev[s->strstart & s->w_mask] = s->head[s->ins_h]), s->head[s->ins_h] = (Pos) s->strstart;
    }
  }
  while ((--s->prev_length) != 0);
  s->match_available = 0;
  s->match_length = 3 - 1;
  s->strstart += 1;
  if (bflush)
  {
    {
      _tr_flush_block(s, (s->block_start >= 0L) ? ((charf *) (&s->window[(unsigned) s->block_start])) : ((charf *) 0), (ulg) (((long) s->strstart) - s->block_start), 0);
      s->block_start = s->strstart;
      flush_pending(s->strm);
      ;
    }
    ;
    if (s->strm->avail_out == 0)
    {
      return (0) ? (finish_started) : (need_more);
    }
  }
  ;
  *hash_head_ref = hash_head;
  *bflush_ref = bflush;
}

void helper_helper_deflate_rle_2_1(int * const bflush_ref, deflate_state * const s)
{
  int bflush = *bflush_ref;
  ;
  {
    uch cc = s->window[s->strstart];
    s->sym_buf[s->sym_next++] = 0;
    s->sym_buf[s->sym_next++] = 0;
    s->sym_buf[s->sym_next++] = cc;
    s->dyn_ltree[cc].fc.freq += 1;
    bflush = s->sym_next == s->sym_end;
  }
  ;
  s->lookahead -= 1;
  s->strstart += 1;
  *bflush_ref = bflush;
}

void helper_helper_deflate_rle_2_2(int * const bflush_ref, deflate_state * const s)
{
  int bflush = *bflush_ref;
  ;
  {
    uch len = (uch) (s->match_length - 3);
    ush dist = (ush) 1;
    s->sym_buf[s->sym_next++] = (uch) dist;
    s->sym_buf[s->sym_next++] = (uch) (dist >> 8);
    s->sym_buf[s->sym_next++] = len;
    dist -= 1;
    s->dyn_ltree[(_length_code[len] + 256) + 1].fc.freq += 1;
    s->dyn_dtree[(dist < 256) ? (_dist_code[dist]) : (_dist_code[256 + (dist >> 7)])].fc.freq += 1;
    bflush = s->sym_next == s->sym_end;
  }
  ;
  s->lookahead -= s->match_length;
  s->strstart += s->match_length;
  s->match_length = 0;
  *bflush_ref = bflush;
}

