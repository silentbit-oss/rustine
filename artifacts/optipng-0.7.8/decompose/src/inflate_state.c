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
}
/*** DEPENDENCIES:
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
} gz_header
----------------------------
typedef struct 
{
  unsigned char op;
  unsigned char bits;
  unsigned short val;
} code
----------------------------
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
} inflate_mode
----------------------------
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
} z_stream
----------------------------
typedef gz_header *gz_headerp
----------------------------
typedef z_stream *z_streamp
----------------------------
***/


