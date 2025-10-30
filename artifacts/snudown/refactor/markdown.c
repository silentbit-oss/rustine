#include <assert.h>
#include <autolink.h>
#include <buffer.h>
#include <ctype.h>
#include <html_blocks.h>
#include <html_entities.h>
#include <markdown.c>
#include <markdown.h>
#include <siphash.h>
#include <stack.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syscall.h>

typedef enum 
{
  BUF_OK = 0,
  BUF_ENOMEM = -1,
  BUF_EINVALIDIDX = -2
} buferror_t;
struct buf
{
  uint8_t *data;
  size_t size;
  size_t asize;
  size_t unit;
};
int bufgrow(struct buf *, size_t);
struct buf *bufnew(size_t);
const char *bufcstr(struct buf *);
int bufprefix(const struct buf *buf, const char *prefix);
void bufput(struct buf *, const void *, size_t);
void bufputs(struct buf *, const char *);
void bufputc(struct buf *, int);
void bufrelease(struct buf *);
void bufreset(struct buf *);
void bufslurp(struct buf *, size_t);
void bufprintf(struct buf *, const char *, ...);
int buftruncate(struct buf *buf, size_t size);
enum 
{
  SD_AUTOLINK_SHORT_DOMAINS = 1 << 0
};
int sd_autolink_issafe(const uint8_t *link, size_t link_len);
size_t sd_autolink__www(size_t *rewind_p, struct buf *link, uint8_t *data, size_t max_rewind, size_t size, unsigned int flags);
size_t sd_autolink__email(size_t *rewind_p, struct buf *link, uint8_t *data, size_t max_rewind, size_t size, unsigned int flags);
size_t sd_autolink__url(size_t *rewind_p, struct buf *link, uint8_t *data, size_t max_rewind, size_t size, unsigned int flags);
extern size_t sd_autolink__subreddit(size_t *rewind_p, struct buf *link, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size, int *no_slash);
extern size_t sd_autolink__username(size_t *rewind_p, struct buf *link, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size, int *no_slash);
enum mkd_autolink
{
  MKDA_NOT_AUTOLINK,
  MKDA_NORMAL,
  MKDA_EMAIL
};
enum mkd_tableflags
{
  MKD_TABLE_ALIGN_L = 1,
  MKD_TABLE_ALIGN_R = 2,
  MKD_TABLE_ALIGN_CENTER = 3,
  MKD_TABLE_ALIGNMASK = 3,
  MKD_TABLE_HEADER = 4
};
enum mkd_extensions
{
  MKDEXT_NO_INTRA_EMPHASIS = 1 << 0,
  MKDEXT_TABLES = 1 << 1,
  MKDEXT_FENCED_CODE = 1 << 2,
  MKDEXT_AUTOLINK = 1 << 3,
  MKDEXT_STRIKETHROUGH = 1 << 4,
  MKDEXT_SPACE_HEADERS = 1 << 6,
  MKDEXT_SUPERSCRIPT = 1 << 7,
  MKDEXT_LAX_SPACING = 1 << 8,
  MKDEXT_NO_EMAIL_AUTOLINK = 1 << 9
};
struct sd_callbacks
{
  void (*blockcode)(struct buf *ob, const struct buf *text, const struct buf *lang, void *opaque);
  void (*blockquote)(struct buf *ob, const struct buf *text, void *opaque);
  void (*blockspoiler)(struct buf *ob, const struct buf *text, void *opaque);
  void (*blockhtml)(struct buf *ob, const struct buf *text, void *opaque);
  void (*header)(struct buf *ob, const struct buf *text, int level, void *opaque);
  void (*hrule)(struct buf *ob, void *opaque);
  void (*list)(struct buf *ob, const struct buf *text, int flags, void *opaque);
  void (*listitem)(struct buf *ob, const struct buf *text, int flags, void *opaque);
  void (*paragraph)(struct buf *ob, const struct buf *text, void *opaque);
  void (*table)(struct buf *ob, const struct buf *header, const struct buf *body, void *opaque);
  void (*table_row)(struct buf *ob, const struct buf *text, void *opaque);
  void (*table_cell)(struct buf *ob, const struct buf *text, int flags, void *opaque, int col_span);
  int (*autolink)(struct buf *ob, const struct buf *link, enum mkd_autolink type, void *opaque);
  int (*codespan)(struct buf *ob, const struct buf *text, void *opaque);
  int (*spoilerspan)(struct buf *ob, const struct buf *text, void *opaque);
  int (*double_emphasis)(struct buf *ob, const struct buf *text, void *opaque);
  int (*emphasis)(struct buf *ob, const struct buf *text, void *opaque);
  int (*image)(struct buf *ob, const struct buf *link, const struct buf *title, const struct buf *alt, void *opaque);
  int (*linebreak)(struct buf *ob, void *opaque);
  int (*link)(struct buf *ob, const struct buf *link, const struct buf *title, const struct buf *content, void *opaque);
  int (*raw_html_tag)(struct buf *ob, const struct buf *tag, void *opaque);
  int (*triple_emphasis)(struct buf *ob, const struct buf *text, void *opaque);
  int (*strikethrough)(struct buf *ob, const struct buf *text, void *opaque);
  int (*superscript)(struct buf *ob, const struct buf *text, void *opaque);
  void (*entity)(struct buf *ob, const struct buf *entity, void *opaque);
  void (*normal_text)(struct buf *ob, const struct buf *text, void *opaque);
  void (*doc_header)(struct buf *ob, void *opaque);
  void (*doc_footer)(struct buf *ob, void *opaque);
};
struct sd_markdown;
extern struct sd_markdown *sd_markdown_new(unsigned int extensions, size_t max_nesting, size_t max_table_cols, const struct sd_callbacks *callbacks, void *opaque);
extern void sd_markdown_render(struct buf *ob, const uint8_t *document, size_t doc_size, struct sd_markdown *md);
extern void sd_markdown_free(struct sd_markdown *md);
extern void sd_version(int *major, int *minor, int *revision);
struct stack
{
  void **item;
  size_t size;
  size_t asize;
};
void stack_free(struct stack *);
int stack_grow(struct stack *, size_t);
int stack_init(struct stack *, size_t);
int stack_push(struct stack *, void *);
void *stack_pop(struct stack *);
void *stack_top(struct stack *);
uint64_t siphash(const uint8_t *in, const size_t inlen, const uint8_t *k);
uint64_t siphash_nocase(const uint8_t *in, const size_t inlen, const uint8_t *k);
static unsigned int hash_block_tag(const char *str, unsigned int len)
{
  static const unsigned char asso_values[] = {38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 8, 30, 25, 20, 15, 10, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 0, 38, 0, 38, 5, 5, 5, 15, 0, 38, 38, 0, 15, 10, 0, 38, 38, 15, 0, 5, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 0, 38, 0, 38, 5, 5, 5, 15, 0, 38, 38, 0, 15, 10, 0, 38, 38, 15, 0, 5, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38};
  int hval = len;
  switch (hval)
  {
    default:
    {
      hval += asso_values[((unsigned char) str[1]) + 1];
    }

    case 1:
    {
      hval += asso_values[(unsigned char) str[0]];
      break;
    }

  }

  return hval;
}

const char *find_block_tag(const char *str, unsigned int len)
{
  enum 
  {
    TOTAL_KEYWORDS = 24,
    MIN_WORD_LENGTH = 1,
    MAX_WORD_LENGTH = 10,
    MIN_HASH_VALUE = 1,
    MAX_HASH_VALUE = 37
  };
  static const char * const wordlist[] = {"", "p", "dl", "div", "math", "table", "", "ul", "del", "form", "blockquote", "figure", "ol", "fieldset", "", "h1", "", "h6", "pre", "", "", "script", "h5", "noscript", "", "style", "iframe", "h4", "ins", "", "", "", "h3", "", "", "", "", "h2", "span"};
  if ((len <= MAX_WORD_LENGTH) && (len >= MIN_WORD_LENGTH))
  {
    int key = hash_block_tag(str, len);
    if ((key <= MAX_HASH_VALUE) && (key >= 0))
    {
      const char *s = wordlist[key];
      if (((((((unsigned char) (*str)) ^ ((unsigned char) (*s))) & (~32)) == 0) && (!strncasecmp(str, s, len))) && (s[len] == '\0'))
      {
        return s;
      }
    }
  }
  return 0;
}

const unsigned MAX_NUM_ENTITY_VAL = 0x10ffff;
const size_t MAX_NUM_ENTITY_LEN = 7;
inline int is_valid_numeric_entity(uint32_t entity_val)
{
  return (((((entity_val > 8) && ((entity_val != 11) && (entity_val != 12))) && ((entity_val < 14) || (entity_val > 31))) && ((entity_val < 55296) || (entity_val > 57343))) && ((entity_val != 65534) && (entity_val != 65535))) && (entity_val <= MAX_NUM_ENTITY_VAL);
}

static unsigned int hash_html_entity(register const char *str, register size_t len)
{
  static const unsigned short asso_values[] = {771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 0, 95, 90, 0, 771, 771, 771, 771, 771, 771, 0, 771, 771, 771, 771, 771, 115, 94, 55, 0, 150, 25, 0, 30, 195, 771, 30, 30, 5, 35, 45, 45, 771, 10, 0, 50, 125, 771, 771, 5, 85, 75, 771, 771, 771, 771, 771, 771, 40, 65, 20, 25, 60, 240, 240, 223, 10, 102, 20, 35, 135, 0, 5, 10, 183, 20, 5, 0, 50, 75, 10, 75, 175, 85, 15, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771};
  register unsigned int hval = len;
  switch (hval)
  {
    default:
    {
      hval += asso_values[(unsigned char) str[6]];
    }

    case 6:
    {
      hval += asso_values[(unsigned char) str[5]];
    }

    case 5:
    {
      hval += asso_values[(unsigned char) str[4]];
    }

    case 4:
    {
      hval += asso_values[(unsigned char) str[3]];
    }

    case 3:
    {
      hval += asso_values[((unsigned char) str[2]) + 1];
    }

    case 2:
    {
      hval += asso_values[(unsigned char) str[1]];
      break;
    }

  }

  return hval;
}

const char *is_allowed_named_entity(register const char *str, register size_t len)
{
  enum 
  {
    TOTAL_KEYWORDS = 253,
    MIN_WORD_LENGTH = 4,
    MAX_WORD_LENGTH = 10,
    MIN_HASH_VALUE = 14,
    MAX_HASH_VALUE = 770
  };
  static const char * const wordlist[] = {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "&or;", "&not;", "", "", "", "", "&int;", "", "", "", "", "&psi;", "&isin;", "&notin;", "", "", "&Rho;", "", "", "", "", "&phi;", "&prop;", "", "", "", "&rho;", "&nbsp;", "&thorn;", "&thinsp;", "", "&chi;", "", "", "", "", "", "&prod;", "", "", "", "&amp;", "", "", "", "", "&Psi;", "", "", "", "", "", "&iota;", "", "", "&omicron;", "&Phi;", "", "", "", "", "&and;", "&sdot;", "", "", "&nu;", "&Chi;", "&emsp;", "", "", "&Mu;", "", "&ensp;", "&ocirc;", "", "&lt;", "&uml;", "", "&icirc;", "", "", "&sup;", "&sup1;", "", "&Scaron;", "", "&cap;", "&part;", "&pound;", "&scaron;", "", "", "&ni;", "", "&lowast;", "&Omicron;", "&cup;", "&Xi;", "&crarr;", "", "&Nu;", "", "&pi;", "&theta;", "", "", "&tau;", "&nsub;", "&acirc;", "", "", "&thetasym;", "", "&Ocirc;", "", "", "", "&rarr;", "&ucirc;", "", "", "&loz;", "&darr;", "&trade;", "", "", "", "&para;", "&ecirc;", "", "", "", "&larr;", "&radic;", "", "", "&sub;", "&Pi;", "&kappa;", "&iquest;", "", "&eta;", "&supe;", "&rceil;", "&there4;", "", "&rArr;", "&uarr;", "&Kappa;", "", "", "&dArr;", "&euro;", "&Theta;", "&circ;", "", "&Tau;", "", "&lceil;", "", "", "&lArr;", "&ordm;", "", "", "", "&lrm;", "&xi;", "&acute;", "&ccedil;", "", "", "&sup3;", "", "&ntilde;", "", "&uArr;", "&sup2;", "&piv;", "&otilde;", "", "&shy;", "", "&Acirc;", "", "", "", "", "", "&curren;", "", "", "", "&Ucirc;", "&oacute;", "", "", "&sube;", "&nabla;", "&iacute;", "&mu;", "", "&bull;", "&oline;", "&Ccedil;", "", "&sum;", "&copy;", "&equiv;", "&Ntilde;", "", "", "", "&prime;", "&atilde;", "&tilde;", "", "", "&Ecirc;", "&Otilde;", "", "", "", "", "", "&apos;", "", "", "", "&aacute;", "&ne;", "&Eta;", "&macr;", "&sim;", "&Oacute;", "", "", "&Iota;", "&empty;", "&uacute;", "", "", "&ouml;", "&exist;", "", "", "", "&iuml;", "&Prime;", "&eacute;", "", "&rsquo;", "&cent;", "&zwj;", "&zwnj;", "&quot;", "&sbquo;", "&sect;", "&infin;", "&otimes;", "", "", "&cong;", "&Icirc;", "&brvbar;", "&le;", "&lsquo;", "&ordf;", "&clubs;", "", "", "&oplus;", "&perp;", "", "&Yacute;", "&micro;", "&ang;", "&auml;", "", "", "&gt;", "&rlm;", "&Ouml;", "&upsilon;", "", "&minus;", "&middot;", "&uuml;", "&aring;", "&Atilde;", "", "&divide;", "&rsaquo;", "&epsilon;", "", "&times;", "&ETH;", "&euml;", "&szlig;", "&frac14;", "&diams;", "", "&oslash;", "", "&Aacute;", "", "", "&lsaquo;", "&Delta;", "", "", "&rdquo;", "&spades;", "", "&Uacute;", "", "&raquo;", "&rang;", "&frasl;", "&rfloor;", "&harr;", "&ndash;", "&Yuml;", "&cedil;", "&eth;", "", "&ldquo;", "&real;", "&THORN;", "&plusmn;", "", "&laquo;", "&lang;", "&delta;", "&lfloor;", "", "", "&beta;", "&omega;", "&Eacute;", "", "", "&Oslash;", "&image;", "&weierp;", "", "", "&Zeta;", "&OElig;", "&hArr;", "", "", "&Auml;", "&asymp;", "&Lambda;", "", "&bdquo;", "&zeta;", "&Upsilon;", "&lambda;", "", "", "&Uuml;", "&Aring;", "&yacute;", "", "&Beta;", "", "&Gamma;", "", "", "", "", "&iexcl;", "&forall;", "", "", "", "&Omega;", "", "", "", "", "&Epsilon;", "&Iacute;", "", "", "&Euml;", "", "&frac34;", "", "", "", "", "&frac12;", "", "", "", "", "", "", "", "", "", "", "", "&yen;", "", "", "", "", "", "&yuml;", "", "", "", "", "&ograve;", "&AElig;", "", "", "", "&igrave;", "", "", "", "", "", "", "", "", "", "&Iuml;", "", "", "", "", "", "", "", "", "&alpha;", "", "", "&permil;", "", "", "", "", "", "", "", "&agrave;", "", "", "", "&mdash;", "&Ograve;", "", "", "", "", "&ugrave;", "", "&upsih;", "", "", "", "", "", "&ge;", "", "&egrave;", "", "", "", "", "", "", "", "", "", "&fnof;", "", "", "", "", "", "", "", "", "&reg;", "", "", "", "", "&deg;", "", "", "", "", "", "", "", "", "", "", "", "", "", "&Sigma;", "", "", "", "", "&sigma;", "&Alpha;", "", "", "", "", "", "&hearts;", "&oelig;", "", "", "", "&Agrave;", "", "", "", "", "", "", "", "", "", "&Ugrave;", "", "", "", "", "", "", "", "", "", "&hellip;", "", "", "", "", "", "", "", "", "", "", "&aelig;", "", "", "", "&Egrave;", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "&Igrave;", "&gamma;", "", "", "", "", "", "", "", "", "", "", "&Dagger;", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "&dagger;", "", "", "", "", "", "&alefsym;", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "&sigmaf;"};
  if ((len <= MAX_WORD_LENGTH) && (len >= MIN_WORD_LENGTH))
  {
    register unsigned int key = hash_html_entity(str, len);
    if (key <= MAX_HASH_VALUE)
    {
      register const char *s = wordlist[key];
      if ((((*str) == (*s)) && (!strncmp(str + 1, s + 1, len - 1))) && (s[len] == '\0'))
      {
        return s;
      }
    }
  }
  return 0;
}

struct link_ref
{
  unsigned int id;
  struct buf *link;
  struct buf *label;
  struct buf *title;
  struct link_ref *next;
};
struct sd_markdown;
typedef size_t (*char_trigger)(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size);
static size_t char_emphasis(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size);
static size_t char_linebreak(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size);
static size_t char_codespan(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size);
static size_t char_escape(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size);
static size_t char_entity(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size);
static size_t char_langle_tag(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size);
static size_t char_autolink_url(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size);
static size_t char_autolink_email(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size);
static size_t char_autolink_www(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size);
static size_t char_autolink_subreddit_or_username(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size);
static size_t char_link(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size);
static size_t char_superscript(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size);
enum markdown_char_t
{
  MD_CHAR_NONE = 0,
  MD_CHAR_EMPHASIS,
  MD_CHAR_CODESPAN,
  MD_CHAR_LINEBREAK,
  MD_CHAR_LINK,
  MD_CHAR_LANGLE,
  MD_CHAR_ESCAPE,
  MD_CHAR_ENTITITY,
  MD_CHAR_AUTOLINK_URL,
  MD_CHAR_AUTOLINK_EMAIL,
  MD_CHAR_AUTOLINK_WWW,
  MD_CHAR_AUTOLINK_SUBREDDIT_OR_USERNAME,
  MD_CHAR_SUPERSCRIPT
};
static char_trigger markdown_char_ptrs[] = {0, &char_emphasis, &char_codespan, &char_linebreak, &char_link, &char_langle_tag, &char_escape, &char_entity, &char_autolink_url, &char_autolink_email, &char_autolink_www, &char_autolink_subreddit_or_username, &char_superscript};
struct sd_markdown
{
  struct sd_callbacks cb;
  void *opaque;
  struct link_ref *refs[8];
  uint8_t active_char[256];
  struct stack work_bufs[2];
  unsigned int ext_flags;
  size_t max_nesting;
  size_t max_table_cols;
  int in_link_body;
};
int sip_hash_key_init = 0;
uint8_t sip_hash_key[16];
int backport_getrandom(void *buf, size_t buflen, unsigned int flags)
{
  return (int) syscall(SYS_getrandom, buf, buflen, flags);
}

inline static struct buf *rndr_newbuf(struct sd_markdown *rndr, int type)
{
  static const size_t buf_size[2] = {256, 64};
  struct buf *work = 0;
  unsigned int work_idx = 0;
  struct stack *pool = &rndr->work_bufs[type];
  if ((pool->size < pool->asize) && (pool->item[pool->size] != 0))
  {
    work_idx = pool->item[pool->size++];
    work->size = 0;
  }
  else
  {
    work_idx = bufnew(buf_size[type]);
    stack_push(pool, work);
  }
  return work;
}

inline static void rndr_popbuf(struct sd_markdown *rndr, int type)
{
  rndr->work_bufs[type].size -= 1;
}

static void unscape_text(struct buf *ob, struct buf *src)
{
  size_t i = 0;
  size_t org;
  while (i < src->size)
  {
    org = i;
    while ((i < src->size) && (src->data[i] != '\\'))
    {
      i += 1;
    }

    if (i > org)
    {
      bufput(ob, src->data + org, i - org);
    }
    if ((i + 1) >= src->size)
    {
      break;
    }
    bufputc(ob, src->data[i + 1]);
    i += 2;
  }

}

static unsigned int hash_link_ref(const uint8_t *link_ref, size_t length)
{
  return siphash_nocase(link_ref, length, sip_hash_key);
}

static struct link_ref *add_link_ref(struct link_ref **references, const uint8_t *name, size_t name_size)
{
  unsigned int hash;
  struct link_ref *ref;
  unsigned int ref_idx = 0;
  hash = hash_link_ref(name, name_size);
  ref_idx = references[hash % 8];
  while ((&ref[ref_idx]) != 0)
  {
    if ((ref->id == hash) && (ref->label->size == name_size))
    {
      if (strncasecmp((char *) ref->label->data, (char *) name, name_size) == 0)
      {
        bufrelease(ref->label);
        bufrelease(ref->link);
        bufrelease(ref->title);
        return ref;
      }
    }
    ref_idx = ref_idx->next;
  }

  ref_idx = calloc(1, sizeof(struct link_ref));
  if (!(&ref[ref_idx]))
  {
    return 0;
  }
  ref->id = hash;
  ref->next = references[ref->id % 8];
  references[ref->id % 8] = &ref[ref_idx];
  return ref;
}

static struct link_ref *find_link_ref(struct link_ref **references, uint8_t *name, size_t length)
{
  unsigned int hash = hash_link_ref(name, length);
  struct link_ref *ref = 0;
  unsigned int ref_idx = 0;
  ref_idx = references[hash % 8];
  while ((&ref[ref_idx]) != 0)
  {
    if ((ref->id == hash) && (ref->label->size == length))
    {
      if (strncasecmp((char *) ref->label->data, (char *) name, length) == 0)
      {
        return ref;
      }
    }
    ref_idx = ref_idx->next;
  }

  return 0;
}

static void free_link_refs(struct link_ref **references)
{
  size_t i;
  for (i = 0; i < 8; i += 1)
  {
    struct link_ref *r = references[i];
    unsigned int r_idx = 0;
    struct link_ref *next;
    unsigned int next_idx = 0;
    while (r)
    {
      next_idx = r->next_idx;
      bufrelease(r->label);
      bufrelease(r->link);
      bufrelease(r->title);
      free(r);
      r_idx = &next[next_idx];
    }

  }

}

inline static int _isspace(int c)
{
  return (c == ' ') || (c == '\n');
}

static size_t is_mail_autolink(uint8_t *data, size_t size)
{
  size_t i = 0;
  size_t nb = 0;
  for (i = 0; i < size; i += 1)
  {
    if (isalnum(data[i]))
    {
      continue;
    }
    switch (data[i])
    {
      case '@':
      {
        nb += 1;
      }

      case '-':

      case '.':

      case '_':
      {
        break;
      }

      case '>':
      {
        return (nb == 1) ? (i + 1) : (0);
      }

      default:
      {
        return 0;
      }

    }

  }

  return 0;
}

static size_t tag_length(uint8_t *data, size_t size, enum mkd_autolink *autolink)
{
  size_t i;
  size_t j;
  if (size < 3)
  {
    return 0;
  }
  if (data[0] != '<')
  {
    return 0;
  }
  i = (data[1] == '/') ? (2) : (1);
  if (!isalnum(data[i]))
  {
    return 0;
  }
  *autolink = MKDA_NOT_AUTOLINK;
  while ((i < size) && (((isalnum(data[i]) || (data[i] == '.')) || (data[i] == '+')) || (data[i] == '-')))
  {
    i += 1;
  }

  if ((i > 1) && (data[i] == '@'))
  {
    if ((j = is_mail_autolink(data + i, size - i)) != 0)
    {
      *autolink = MKDA_EMAIL;
      return i + j;
    }
  }
  if ((i > 2) && (data[i] == ':'))
  {
    *autolink = MKDA_NORMAL;
    i += 1;
  }
  if (i >= size)
  {
    *autolink = MKDA_NOT_AUTOLINK;
  }
  else
    if (*autolink)
  {
    helper_tag_length_1(&i, &j, data, size, autolink);
  }
  while ((i < size) && (data[i] != '>'))
  {
    i += 1;
  }

  if (i >= size)
  {
    return 0;
  }
  return i + 1;
}

static void parse_inline(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  size_t i = 0;
  size_t end = 0;
  size_t last_special = 0;
  uint8_t action = 0;
  struct buf work = {0, 0, 0, 0};
  if ((rndr->work_bufs[1].size + rndr->work_bufs[0].size) > rndr->max_nesting)
  {
    return;
  }
  while (i < size)
  {
    while ((end < size) && ((action = rndr->active_char[data[end]]) == 0))
    {
      end += 1;
    }

    if (rndr->cb.normal_text)
    {
      work.data = data + i;
      work.size = end - i;
      rndr->cb.normal_text(ob, &work, rndr->opaque);
    }
    else
      bufput(ob, data + i, end - i);
    if (end >= size)
    {
      break;
    }
    i = end;
    end = markdown_char_ptrs[(int) action](ob, rndr, data + i, i - last_special, i, size - i);
    if (!end)
    {
      end = i + 1;
    }
    else
    {
      i += end;
      last_special = (end = i);
    }
  }

}

static size_t find_emph_char(uint8_t *data, size_t size, uint8_t c)
{
  size_t i = 1;
  while (i < size)
  {
    helper_find_emph_char_1(&i, data, size, c);
  }

  return 0;
}

static size_t parse_emph1(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size, uint8_t c)
{
  size_t i = 0;
  size_t len;
  struct buf *work = 0;
  unsigned int work_idx = 0;
  int r;
  if (!rndr->cb.emphasis)
  {
    return 0;
  }
  if (((size > 1) && (data[0] == c)) && (data[1] == c))
  {
    i = 1;
  }
  while (i < size)
  {
    len = find_emph_char(data + i, size - i, c);
    if (!len)
    {
      return 0;
    }
    i += len;
    if (i >= size)
    {
      return 0;
    }
    if ((data[i] == c) && (!_isspace(data[i - 1])))
    {
      if ((rndr->ext_flags & MKDEXT_NO_INTRA_EMPHASIS) && (c == '_'))
      {
        if (!((((i + 1) == size) || _isspace(data[i + 1])) || ispunct(data[i + 1])))
        {
          continue;
        }
      }
      work_idx = rndr_newbuf(rndr, 1);
      parse_inline(work, rndr, data, i);
      r = rndr->cb.emphasis(ob, work, rndr->opaque);
      rndr_popbuf(rndr, 1);
      return (r) ? (i + 1) : (0);
    }
  }

  return 0;
}

static size_t parse_emph2(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size, uint8_t c)
{
  int (*render_method)(struct buf *ob, const struct buf *text, void *opaque);
  unsigned int render_method_idx = 0;
  size_t i = 0;
  size_t len;
  struct buf *work = 0;
  unsigned int work_idx = 0;
  int r;
  render_method_idx = (c == '~') ? (rndr->cb.strikethrough) : (rndr->cb.double_emphasis);
  if (!(&render_method[render_method_idx]))
  {
    return 0;
  }
  while (i < size)
  {
    len = find_emph_char(data + i, size - i, c);
    if (!len)
    {
      return 0;
    }
    i += len;
    if ((((((i + 1) < size) && (data[i] == c)) && (data[i + 1] == c)) && i) && (!_isspace(data[i - 1])))
    {
      work_idx = rndr_newbuf(rndr, 1);
      parse_inline(work, rndr, data, i);
      r = render_method(ob, work, rndr->opaque);
      rndr_popbuf(rndr, 1);
      return (r) ? (i + 2) : (0);
    }
    i += 1;
  }

  return 0;
}

static size_t parse_emph3(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size, uint8_t c)
{
  size_t i = 0;
  size_t len;
  int r;
  while (i < size)
  {
    len = find_emph_char(data + i, size - i, c);
    if (!len)
    {
      return 0;
    }
    i += len;
    if ((data[i] != c) || _isspace(data[i - 1]))
    {
      continue;
    }
    if (((((i + 2) < size) && (data[i + 1] == c)) && (data[i + 2] == c)) && rndr->cb.triple_emphasis)
    {
      struct buf *work = rndr_newbuf(rndr, 1);
      parse_inline(work, rndr, data, i);
      r = rndr->cb.triple_emphasis(ob, work, rndr->opaque);
      rndr_popbuf(rndr, 1);
      return (r) ? (i + 3) : (0);
    }
    else
      if (((i + 1) < size) && (data[i + 1] == c))
    {
      len = parse_emph1(ob, rndr, data - 2, size + 2, c);
      if (!len)
      {
        return 0;
      }
      else
        return len - 2;
    }
    else
    {
      len = parse_emph2(ob, rndr, data - 1, size + 1, c);
      if (!len)
      {
        return 0;
      }
      else
        return len - 1;
    }
  }

  return 0;
}

static size_t parse_spoilerspan(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  int (*render_method)(struct buf *ob, const struct buf *text, void *opaque);
  unsigned int render_method_idx = 0;
  size_t len;
  size_t i = 0;
  struct buf *work = 0;
  unsigned int work_idx = 0;
  int r;
  render_method_idx = rndr->cb.spoilerspan;
  if (!(&render_method[render_method_idx]))
  {
    return 0;
  }
  while (i < size)
  {
    len = find_emph_char(data + i, size - i, '<');
    if (!len)
    {
      return 0;
    }
    i += len;
    if (((i < size) && (data[i] == '<')) && (data[i - 1] == '!'))
    {
      work_idx = rndr_newbuf(rndr, 1);
      parse_inline(work, rndr, data, i - 1);
      r = render_method(ob, work, rndr->opaque);
      rndr_popbuf(rndr, 1);
      if (!r)
      {
        return 0;
      }
      return i + 1;
    }
    i += 1;
  }

  return 0;
}

static size_t char_emphasis(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size)
{
  uint8_t c = data[0];
  size_t ret;
  if (((size > 3) && (c == '>')) && (data[1] == '!'))
  {
    if (_isspace(data[2]) || ((ret = parse_spoilerspan(ob, rndr, data + 2, size - 2)) == 0))
    {
      return 0;
    }
    return ret + 2;
  }
  if ((size > 2) && (data[1] != c))
  {
    if ((((c == '~') || (c == '>')) || _isspace(data[1])) || ((ret = parse_emph1(ob, rndr, data + 1, size - 1, c)) == 0))
    {
      return 0;
    }
    return ret + 1;
  }
  if (((size > 3) && (data[1] == c)) && (data[2] != c))
  {
    if (_isspace(data[2]) || ((ret = parse_emph2(ob, rndr, data + 2, size - 2, c)) == 0))
    {
      return 0;
    }
    return ret + 2;
  }
  if ((((size > 4) && (data[1] == c)) && (data[2] == c)) && (data[3] != c))
  {
    if ((((c == '~') || (c == '>')) || _isspace(data[3])) || ((ret = parse_emph3(ob, rndr, data + 3, size - 3, c)) == 0))
    {
      return 0;
    }
    return ret + 3;
  }
  return 0;
}

static size_t char_linebreak(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size)
{
  if (((max_rewind < 2) || (data[-1] != ' ')) || (data[-2] != ' '))
  {
    return 0;
  }
  while (ob->size && (ob->data[ob->size - 1] == ' '))
  {
    ob->size -= 1;
  }

  return (rndr->cb.linebreak(ob, rndr->opaque)) ? (1) : (0);
}

static size_t char_codespan(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size)
{
  size_t end;
  size_t nb = 0;
  size_t i;
  size_t f_begin;
  size_t f_end;
  while ((nb < size) && (data[nb] == '`'))
  {
    nb += 1;
  }

  i = 0;
  for (end = nb; (end < size) && (i < nb); end += 1)
  {
    if (data[end] == '`')
    {
      i += 1;
    }
    else
      i = 0;
  }

  if ((i < nb) && (end >= size))
  {
    return 0;
  }
  f_begin = nb;
  while ((f_begin < end) && (data[f_begin] == ' '))
  {
    f_begin += 1;
  }

  f_end = end - nb;
  while ((f_end > nb) && (data[f_end - 1] == ' '))
  {
    f_end -= 1;
  }

  if (f_begin < f_end)
  {
    struct buf work = {data + f_begin, f_end - f_begin, 0, 0};
    if (!rndr->cb.codespan(ob, &work, rndr->opaque))
    {
      end = 0;
    }
  }
  else
  {
    if (!rndr->cb.codespan(ob, 0, rndr->opaque))
    {
      end = 0;
    }
  }
  return end;
}

static size_t char_escape(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size)
{
  static const char *escape_chars = "\\`*_{}[]()#+-.!:|&<>/^~";
  struct buf work = {0, 0, 0, 0};
  if (size > 1)
  {
    if (strchr(escape_chars, data[1]) == 0)
    {
      return 0;
    }
    if (rndr->cb.normal_text)
    {
      work.data = data + 1;
      work.size = 1;
      rndr->cb.normal_text(ob, &work, rndr->opaque);
    }
    else
      bufputc(ob, data[1]);
  }
  else
    if (size == 1)
  {
    bufputc(ob, data[0]);
  }
  return 2;
}

static size_t char_entity(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size)
{
  size_t end = 1;
  size_t content_start;
  size_t content_end;
  struct buf work = {0, 0, 0, 0};
  int numeric = 0;
  int hex = 0;
  int entity_base;
  uint32_t entity_val;
  if ((end < size) && (data[end] == '#'))
  {
    numeric = 1;
    end += 1;
  }
  if (((end < size) && numeric) && (tolower(data[end]) == 'x'))
  {
    hex = 1;
    end += 1;
  }
  content_start = end;
  while (end < size)
  {
    const char c = data[end];
    if (hex)
    {
      if (!isxdigit(c))
      {
        break;
      }
    }
    else
      if (numeric)
    {
      if (!isdigit(c))
      {
        break;
      }
    }
    else
      if (!isalnum(c))
    {
      break;
    }
    end += 1;
  }

  content_end = end;
  if (((end > content_start) && (end < size)) && (data[end] == ';'))
  {
    end += 1;
  }
  else
    return 0;
  if (numeric && ((content_end - content_start) > MAX_NUM_ENTITY_LEN))
  {
    return 0;
  }
  if (numeric)
  {
    if (hex)
    {
      entity_base = 16;
    }
    else
      entity_base = 10;
    entity_val = strtol(((char *) data) + content_start, 0, entity_base);
    if (!is_valid_numeric_entity(entity_val))
    {
      return 0;
    }
  }
  else
  {
    if (!is_allowed_named_entity((const char *) data, end))
    {
      return 0;
    }
  }
  if (rndr->cb.entity)
  {
    work.data = data;
    work.size = end;
    rndr->cb.entity(ob, &work, rndr->opaque);
  }
  else
  {
    bufputc(ob, '&');
    if (numeric)
    {
      bufputc(ob, '#');
    }
    if (hex)
    {
      bufputc(ob, 'x');
    }
    bufput(ob, data + content_start, end - content_start);
  }
  return end;
}

static size_t char_langle_tag(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size)
{
  enum mkd_autolink altype = MKDA_NOT_AUTOLINK;
  size_t end = tag_length(data, size, &altype);
  struct buf work = {data, end, 0, 0};
  int ret = 0;
  if (end > 2)
  {
    if (rndr->cb.autolink && (altype != MKDA_NOT_AUTOLINK))
    {
      struct buf *u_link = rndr_newbuf(rndr, 1);
      work.data = data + 1;
      work.size = end - 2;
      unscape_text(u_link, &work);
      ret = rndr->cb.autolink(ob, u_link, altype, rndr->opaque);
      rndr_popbuf(rndr, 1);
    }
    else
      if (rndr->cb.raw_html_tag)
    {
      ret = rndr->cb.raw_html_tag(ob, &work, rndr->opaque);
    }
  }
  if (!ret)
  {
    return 0;
  }
  else
    return end;
}

static size_t char_autolink_www(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size)
{
  struct buf *link;
  unsigned int link_idx = 0;
  struct buf *link_url;
  unsigned int link_url_idx = 0;
  struct buf *link_text;
  unsigned int link_text_idx = 0;
  size_t link_len;
  size_t rewind;
  if ((!rndr->cb.link) || rndr->in_link_body)
  {
    return 0;
  }
  link_idx = rndr_newbuf(rndr, 1);
  if ((link_len = sd_autolink__www(&rewind, link, data, max_rewind, size, 0)) > 0)
  {
    link_url_idx = rndr_newbuf(rndr, 1);
    bufput(link_url, "http://", (sizeof("http://")) - 1);
    bufput(link_url, link->data, link->size);
    buftruncate(ob, ob->size - rewind);
    if (rndr->cb.normal_text)
    {
      link_text_idx = rndr_newbuf(rndr, 1);
      rndr->cb.normal_text(link_text, link, rndr->opaque);
      rndr->cb.link(ob, link_url, 0, link_text, rndr->opaque);
      rndr_popbuf(rndr, 1);
    }
    else
    {
      rndr->cb.link(ob, link_url, 0, link, rndr->opaque);
    }
    rndr_popbuf(rndr, 1);
  }
  rndr_popbuf(rndr, 1);
  return link_len;
}

static size_t char_autolink_subreddit_or_username(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size)
{
  struct buf *link;
  unsigned int link_idx = 0;
  struct buf *link_text;
  unsigned int link_text_idx = 0;
  struct buf *link_url;
  unsigned int link_url_idx = 0;
  size_t link_len;
  size_t rewind;
  int no_slash;
  if ((!rndr->cb.autolink) || rndr->in_link_body)
  {
    return 0;
  }
  link_idx = rndr_newbuf(rndr, 1);
  link_len = sd_autolink__subreddit(&rewind, link, data, max_rewind, max_lookbehind, size, &no_slash);
  if (link_len == 0)
  {
    link_len = sd_autolink__username(&rewind, link, data, max_rewind, max_lookbehind, size, &no_slash);
  }
  if (link_len > 0)
  {
    link_url_idx = rndr_newbuf(rndr, 1);
    if (no_slash)
    {
      bufputc(link_url, '/');
    }
    bufput(link_url, link->data, link->size);
    buftruncate(ob, ob->size - rewind);
    if (rndr->cb.normal_text)
    {
      link_text_idx = rndr_newbuf(rndr, 1);
      rndr->cb.normal_text(link_text, link, rndr->opaque);
      rndr->cb.link(ob, link_url, 0, link_text, rndr->opaque);
      rndr_popbuf(rndr, 1);
    }
    else
    {
      rndr->cb.link(ob, link_url, 0, link, rndr->opaque);
    }
    rndr_popbuf(rndr, 1);
  }
  rndr_popbuf(rndr, 1);
  return link_len;
}

static size_t char_autolink_email(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size)
{
  struct buf *link;
  unsigned int link_idx = 0;
  size_t link_len;
  size_t rewind;
  if ((!rndr->cb.autolink) || rndr->in_link_body)
  {
    return 0;
  }
  link_idx = rndr_newbuf(rndr, 1);
  if ((link_len = sd_autolink__email(&rewind, link, data, max_rewind, size, 0)) > 0)
  {
    buftruncate(ob, ob->size - rewind);
    rndr->cb.autolink(ob, link, MKDA_EMAIL, rndr->opaque);
  }
  rndr_popbuf(rndr, 1);
  return link_len;
}

static size_t char_autolink_url(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size)
{
  struct buf *link;
  unsigned int link_idx = 0;
  size_t link_len;
  size_t rewind;
  if ((!rndr->cb.autolink) || rndr->in_link_body)
  {
    return 0;
  }
  link_idx = rndr_newbuf(rndr, 1);
  if ((link_len = sd_autolink__url(&rewind, link, data, max_rewind, size, 0)) > 0)
  {
    buftruncate(ob, ob->size - rewind);
    rndr->cb.autolink(ob, link, MKDA_NORMAL, rndr->opaque);
  }
  rndr_popbuf(rndr, 1);
  return link_len;
}

static size_t char_link(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size)
{
  int is_img = max_rewind && (data[-1] == '!');
  int level;
  size_t i = 1;
  size_t txt_e;
  size_t link_b = 0;
  size_t link_e = 0;
  size_t title_b = 0;
  size_t title_e = 0;
  struct buf *content = 0;
  unsigned int content_idx = 0;
  struct buf *link = 0;
  unsigned int link_idx = 0;
  struct buf *title = 0;
  unsigned int title_idx = 0;
  struct buf *u_link = 0;
  unsigned int u_link_idx = 0;
  size_t org_work_size = rndr->work_bufs[1].size;
  int text_has_nl = 0;
  int ret = 0;
  int in_title = 0;
  int qtype = 0;
  if ((is_img && (!rndr->cb.image)) || ((!is_img) && (!rndr->cb.link)))
  {
    goto cleanup;
  }
  for (level = 1; i < size; i += 1)
  {
    if (data[i] == '\n')
    {
      text_has_nl = 1;
    }
    else
      if (data[i - 1] == '\\')
    {
      continue;
    }
    else
      if (data[i] == '[')
    {
      level += 1;
    }
    else
      if (data[i] == ']')
    {
      level -= 1;
      if (level <= 0)
      {
        break;
      }
    }
  }

  if (i >= size)
  {
    goto cleanup;
  }
  txt_e = i;
  i += 1;
  while ((i < size) && _isspace(data[i]))
  {
    i += 1;
  }

  if ((i < size) && (data[i] == '('))
  {
    helper_char_link_3(&i, &link_b, &link_e, &title_b, &title_e, &link_idx, &title_idx, &in_title, &qtype, rndr, data, size, link, title);
  }
  else
    if ((i < size) && (data[i] == '['))
  {
    helper_char_link_2(&size, &i, &link_b, &link_e, &link_idx, &title_idx, rndr, data, txt_e, text_has_nl);
  }
  else
  {
    helper_char_link_1(&i, &link_idx, &title_idx, rndr, data, txt_e, text_has_nl);
  }
  if (txt_e > 1)
  {
    content_idx = rndr_newbuf(rndr, 1);
    if (is_img)
    {
      bufput(content, data + 1, txt_e - 1);
    }
    else
    {
      rndr->in_link_body = 1;
      parse_inline(content, rndr, data + 1, txt_e - 1);
      rndr->in_link_body = 0;
    }
  }
  if (link)
  {
    u_link_idx = rndr_newbuf(rndr, 1);
    unscape_text(u_link, link);
  }
  else
  {
    goto cleanup;
  }
  if (is_img)
  {
    if (ob->size && (ob->data[ob->size - 1] == '!'))
    {
      ob->size -= 1;
    }
    ret = rndr->cb.image(ob, u_link, title, content, rndr->opaque);
  }
  else
  {
    ret = rndr->cb.link(ob, u_link, title, content, rndr->opaque);
  }
  cleanup:
  rndr->work_bufs[1].size = (int) org_work_size;

  return (ret) ? (i) : (0);
}

static size_t char_superscript(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size)
{
  size_t sup_start;
  size_t sup_len;
  struct buf *sup;
  unsigned int sup_idx = 0;
  if (!rndr->cb.superscript)
  {
    return 0;
  }
  if (size < 2)
  {
    return 0;
  }
  if (data[1] == '(')
  {
    sup_start = (sup_len = 2);
    while (((sup_len < size) && (data[sup_len] != ')')) && (data[sup_len - 1] != '\\'))
    {
      sup_len += 1;
    }

    if (sup_len == size)
    {
      return 0;
    }
  }
  else
  {
    sup_start = (sup_len = 1);
    while ((sup_len < size) && (!_isspace(data[sup_len])))
    {
      sup_len += 1;
    }

  }
  if ((sup_len - sup_start) == 0)
  {
    return (sup_start == 2) ? (3) : (0);
  }
  sup_idx = rndr_newbuf(rndr, 1);
  parse_inline(sup, rndr, data + sup_start, sup_len - sup_start);
  rndr->cb.superscript(ob, sup, rndr->opaque);
  rndr_popbuf(rndr, 1);
  return (sup_start == 2) ? (sup_len + 1) : (sup_len);
}

static size_t is_empty(uint8_t *data, size_t size)
{
  size_t i;
  for (i = 0; (i < size) && (data[i] != '\n'); i += 1)
  {
    if (data[i] != ' ')
    {
      return 0;
    }
  }

  return i + 1;
}

static int is_hrule(uint8_t *data, size_t size)
{
  size_t i = 0;
  size_t n = 0;
  uint8_t c;
  if (size < 3)
  {
    return 0;
  }
  if (data[0] == ' ')
  {
    i += 1;
    if (data[1] == ' ')
    {
      i += 1;
      if (data[2] == ' ')
      {
        i += 1;
      }
    }
  }
  if (((i + 2) >= size) || (((data[i] != '*') && (data[i] != '-')) && (data[i] != '_')))
  {
    return 0;
  }
  c = data[i];
  while ((i < size) && (data[i] != '\n'))
  {
    if (data[i] == c)
    {
      n += 1;
    }
    else
      if (data[i] != ' ')
    {
      return 0;
    }
    i += 1;
  }

  return n >= 3;
}

static size_t prefix_codefence(uint8_t *data, size_t size)
{
  size_t i = 0;
  size_t n = 0;
  uint8_t c;
  if (size < 3)
  {
    return 0;
  }
  if (data[0] == ' ')
  {
    i += 1;
    if (data[1] == ' ')
    {
      i += 1;
      if (data[2] == ' ')
      {
        i += 1;
      }
    }
  }
  if (((i + 2) >= size) || (!((data[i] == '~') || (data[i] == '`'))))
  {
    return 0;
  }
  c = data[i];
  while ((i < size) && (data[i] == c))
  {
    n += 1;
    i += 1;
  }

  if (n < 3)
  {
    return 0;
  }
  return i;
}

static size_t is_codefence(uint8_t *data, size_t size, struct buf *syntax)
{
  size_t i = 0;
  size_t syn_len = 0;
  uint8_t *syn_start;
  unsigned int syn_start_idx = 0;
  i = prefix_codefence(data, size);
  if (i == 0)
  {
    return 0;
  }
  while ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }

  syn_start_idx = data + i;
  if ((i < size) && (data[i] == '{'))
  {
    helper_is_codefence_1(&i, &syn_len, &syn_start_idx, data, size, syn_start);
  }
  else
  {
    while ((i < size) && (!_isspace(data[i])))
    {
      syn_len += 1;
      i += 1;
    }

  }
  if (syntax)
  {
    syntax->data = &syn_start[syn_start_idx];
    syntax->size = syn_len;
  }
  while ((i < size) && (data[i] != '\n'))
  {
    if (!_isspace(data[i]))
    {
      return 0;
    }
    i += 1;
  }

  return i + 1;
}

static int is_atxheader(struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  if (data[0] != '#')
  {
    return 0;
  }
  if (rndr->ext_flags & MKDEXT_SPACE_HEADERS)
  {
    size_t level = 0;
    while (((level < size) && (level < 6)) && (data[level] == '#'))
    {
      level += 1;
    }

    if ((level < size) && (data[level] != ' '))
    {
      return 0;
    }
  }
  return 1;
}

static int is_headerline(uint8_t *data, size_t size)
{
  size_t i = 0;
  if (data[i] == '=')
  {
    for (i = 1; (i < size) && (data[i] == '='); i += 1)
    {
      ;
    }

    while ((i < size) && (data[i] == ' '))
    {
      i += 1;
    }

    return ((i >= size) || (data[i] == '\n')) ? (1) : (0);
  }
  if (data[i] == '-')
  {
    for (i = 1; (i < size) && (data[i] == '-'); i += 1)
    {
      ;
    }

    while ((i < size) && (data[i] == ' '))
    {
      i += 1;
    }

    return ((i >= size) || (data[i] == '\n')) ? (2) : (0);
  }
  return 0;
}

static int is_next_headerline(uint8_t *data, size_t size)
{
  size_t i = 0;
  while ((i < size) && (data[i] != '\n'))
  {
    i += 1;
  }

  if ((++i) >= size)
  {
    return 0;
  }
  return is_headerline(data + i, size - i);
}

static size_t prefix_quote(uint8_t *data, size_t size)
{
  size_t i = 0;
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if (((i < size) && (data[i] == '>')) && (((i + 1) < size) && (data[i + 1] != '!')))
  {
    if (((i + 1) < size) && (data[i + 1] == ' '))
    {
      return i + 2;
    }
    return i + 1;
  }
  return 0;
}

static size_t prefix_blockspoiler(uint8_t *data, size_t size)
{
  size_t i = 0;
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((((i + 1) < size) && (data[i] == '>')) && (data[i + 1] == '!'))
  {
    size_t spoilerspan = find_emph_char((data + i) + 1, (size - i) - 1, '<');
    if ((((i + spoilerspan) < size) && (spoilerspan > 0)) && (data[i + spoilerspan] == '!'))
    {
      return 0;
    }
    if (((i + 2) < size) && (data[i + 2] == ' '))
    {
      return i + 3;
    }
    return i + 2;
  }
  return 0;
}

static size_t prefix_code(uint8_t *data, size_t size)
{
  if (((((size > 3) && (data[0] == ' ')) && (data[1] == ' ')) && (data[2] == ' ')) && (data[3] == ' '))
  {
    return 4;
  }
  return 0;
}

static size_t prefix_oli(uint8_t *data, size_t size)
{
  size_t i = 0;
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if (((i >= size) || (data[i] < '0')) || (data[i] > '9'))
  {
    return 0;
  }
  while (((i < size) && (data[i] >= '0')) && (data[i] <= '9'))
  {
    i += 1;
  }

  if ((((i + 1) >= size) || (data[i] != '.')) || (data[i + 1] != ' '))
  {
    return 0;
  }
  if (is_next_headerline(data + i, size - i))
  {
    return 0;
  }
  return i + 2;
}

static size_t prefix_uli(uint8_t *data, size_t size)
{
  size_t i = 0;
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((((i + 1) >= size) || (((data[i] != '*') && (data[i] != '+')) && (data[i] != '-'))) || (data[i + 1] != ' '))
  {
    return 0;
  }
  if (is_next_headerline(data + i, size - i))
  {
    return 0;
  }
  return i + 2;
}

static void parse_block(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size);
static size_t parse_blockquote(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  size_t beg;
  size_t end = 0;
  size_t pre;
  size_t work_size = 0;
  uint8_t *work_data = 0;
  unsigned int work_data_idx = 0;
  struct buf *out = 0;
  unsigned int out_idx = 0;
  out_idx = rndr_newbuf(rndr, 0);
  beg = 0;
  while (beg < size)
  {
    for (end = beg + 1; (end < size) && (data[end - 1] != '\n'); end += 1)
    {
      ;
    }

    pre = prefix_quote(data + beg, end - beg);
    if (pre)
    {
      beg += pre;
    }
    else
      if (is_empty(data + beg, end - beg) && ((end >= size) || ((prefix_quote(data + end, size - end) == 0) && (!is_empty(data + end, size - end)))))
    {
      break;
    }
    if (beg < end)
    {
      if (!(&work_data[work_data_idx]))
      {
        work_data_idx = data + beg;
      }
      else
        if ((data + beg) != ((&work_data[work_data_idx]) + work_size))
      {
        memmove((&work_data[work_data_idx]) + work_size, data + beg, end - beg);
      }
      work_size += end - beg;
    }
    beg = end;
  }

  parse_block(out, rndr, work_data, work_size);
  if (rndr->cb.blockquote)
  {
    rndr->cb.blockquote(ob, out, rndr->opaque);
  }
  rndr_popbuf(rndr, 0);
  return end;
}

static size_t parse_blockspoiler(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  size_t beg;
  size_t end = 0;
  size_t pre;
  size_t work_size = 0;
  uint8_t *work_data = 0;
  unsigned int work_data_idx = 0;
  struct buf *out = 0;
  unsigned int out_idx = 0;
  out_idx = rndr_newbuf(rndr, 0);
  beg = 0;
  while (beg < size)
  {
    for (end = beg + 1; (end < size) && (data[end - 1] != '\n'); end += 1)
    {
      ;
    }

    pre = prefix_blockspoiler(data + beg, end - beg);
    if (pre)
    {
      beg += pre;
    }
    else
      if (is_empty(data + beg, end - beg) && ((end >= size) || ((prefix_blockspoiler(data + end, size - end) == 0) && (!is_empty(data + end, size - end)))))
    {
      break;
    }
    if (beg < end)
    {
      if (!(&work_data[work_data_idx]))
      {
        work_data_idx = data + beg;
      }
      else
        if ((data + beg) != ((&work_data[work_data_idx]) + work_size))
      {
        memmove((&work_data[work_data_idx]) + work_size, data + beg, end - beg);
      }
      work_size += end - beg;
    }
    beg = end;
  }

  parse_block(out, rndr, work_data, work_size);
  if (rndr->cb.blockspoiler)
  {
    rndr->cb.blockspoiler(ob, out, rndr->opaque);
  }
  rndr_popbuf(rndr, 0);
  return end;
}

static size_t parse_htmlblock(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size, int do_render);
static size_t parse_paragraph(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  size_t i = 0;
  size_t end = 0;
  int level = 0;
  struct buf work = {data, 0, 0, 0};
  while (i < size)
  {
    helper_parse_paragraph_1(&i, &end, &level, ob, rndr, data, size);
  }

  work.size = i;
  while (work.size && (data[work.size - 1] == '\n'))
  {
    work.size -= 1;
  }

  if (!level)
  {
    struct buf *tmp = rndr_newbuf(rndr, 0);
    parse_inline(tmp, rndr, work.data, work.size);
    if (rndr->cb.paragraph)
    {
      rndr->cb.paragraph(ob, tmp, rndr->opaque);
    }
    rndr_popbuf(rndr, 0);
  }
  else
  {
    helper_parse_paragraph_2(&i, &work, ob, rndr, data, level);
  }
  return end;
}

static size_t parse_fencedcode(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  size_t beg;
  size_t end;
  struct buf *work = 0;
  unsigned int work_idx = 0;
  struct buf lang = {0, 0, 0, 0};
  beg = is_codefence(data, size, &lang);
  if (beg == 0)
  {
    return 0;
  }
  work_idx = rndr_newbuf(rndr, 0);
  while (beg < size)
  {
    size_t fence_end;
    struct buf fence_trail = {0, 0, 0, 0};
    fence_end = is_codefence(data + beg, size - beg, &fence_trail);
    if ((fence_end != 0) && (fence_trail.size == 0))
    {
      beg += fence_end;
      break;
    }
    for (end = beg + 1; (end < size) && (data[end - 1] != '\n'); end += 1)
    {
      ;
    }

    if (beg < end)
    {
      if (is_empty(data + beg, end - beg))
      {
        bufputc(work, '\n');
      }
      else
        bufput(work, data + beg, end - beg);
    }
    beg = end;
  }

  if (work->size && (work->data[work->size - 1] != '\n'))
  {
    bufputc(work, '\n');
  }
  if (rndr->cb.blockcode)
  {
    rndr->cb.blockcode(ob, work, (lang.size) ? (&lang) : (0), rndr->opaque);
  }
  rndr_popbuf(rndr, 0);
  return beg;
}

static size_t parse_blockcode(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  size_t beg;
  size_t end;
  size_t pre;
  struct buf *work = 0;
  unsigned int work_idx = 0;
  work_idx = rndr_newbuf(rndr, 0);
  beg = 0;
  while (beg < size)
  {
    for (end = beg + 1; (end < size) && (data[end - 1] != '\n'); end += 1)
    {
    }

    ;
    pre = prefix_code(data + beg, end - beg);
    if (pre)
    {
      beg += pre;
    }
    else
      if (!is_empty(data + beg, end - beg))
    {
      break;
    }
    if (beg < end)
    {
      if (is_empty(data + beg, end - beg))
      {
        bufputc(work, '\n');
      }
      else
        bufput(work, data + beg, end - beg);
    }
    beg = end;
  }

  while (work->size && (work->data[work->size - 1] == '\n'))
  {
    work->size -= 1;
  }

  bufputc(work, '\n');
  if (rndr->cb.blockcode)
  {
    rndr->cb.blockcode(ob, work, 0, rndr->opaque);
  }
  rndr_popbuf(rndr, 0);
  return beg;
}

static size_t parse_listitem(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size, int *flags)
{
  struct buf *work = 0;
  unsigned int work_idx = 0;
  struct buf *inter = 0;
  unsigned int inter_idx = 0;
  size_t beg = 0;
  size_t end;
  size_t pre;
  size_t sublist = 0;
  size_t orgpre = 0;
  size_t i;
  int in_empty = 0;
  int has_inside_empty = 0;
  int in_fence = 0;
  while (((orgpre < 3) && (orgpre < size)) && (data[orgpre] == ' '))
  {
    orgpre += 1;
  }

  beg = prefix_uli(data, size);
  if (!beg)
  {
    beg = prefix_oli(data, size);
  }
  if (!beg)
  {
    return 0;
  }
  end = beg;
  while ((end < size) && (data[end - 1] != '\n'))
  {
    end += 1;
  }

  work_idx = rndr_newbuf(rndr, 1);
  inter_idx = rndr_newbuf(rndr, 1);
  bufput(work, data + beg, end - beg);
  beg = end;
  while (beg < size)
  {
    helper_parse_listitem_1(&beg, &end, &pre, &sublist, &i, &in_empty, &has_inside_empty, &in_fence, rndr, data, size, flags, work, orgpre);
  }

  if (has_inside_empty)
  {
    *flags |= 2;
  }
  if ((*flags) & 2)
  {
    if (sublist && (sublist < work->size))
    {
      parse_block(inter, rndr, work->data, sublist);
      parse_block(inter, rndr, work->data + sublist, work->size - sublist);
    }
    else
      parse_block(inter, rndr, work->data, work->size);
  }
  else
  {
    if (sublist && (sublist < work->size))
    {
      parse_inline(inter, rndr, work->data, sublist);
      parse_block(inter, rndr, work->data + sublist, work->size - sublist);
    }
    else
      parse_inline(inter, rndr, work->data, work->size);
  }
  if (rndr->cb.listitem)
  {
    rndr->cb.listitem(ob, inter, *flags, rndr->opaque);
  }
  rndr_popbuf(rndr, 1);
  rndr_popbuf(rndr, 1);
  return beg;
}

static size_t parse_list(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size, int flags)
{
  struct buf *work = 0;
  unsigned int work_idx = 0;
  size_t i = 0;
  size_t j;
  work_idx = rndr_newbuf(rndr, 0);
  while (i < size)
  {
    j = parse_listitem(work, rndr, data + i, size - i, &flags);
    i += j;
    if ((!j) || (flags & 8))
    {
      break;
    }
  }

  if (rndr->cb.list)
  {
    rndr->cb.list(ob, work, flags, rndr->opaque);
  }
  rndr_popbuf(rndr, 0);
  return i;
}

static size_t parse_atxheader(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  size_t level = 0;
  size_t i;
  size_t end;
  size_t skip;
  while (((level < size) && (level < 6)) && (data[level] == '#'))
  {
    level += 1;
  }

  for (i = level; (i < size) && (data[i] == ' '); i += 1)
  {
    ;
  }

  for (end = i; (end < size) && (data[end] != '\n'); end += 1)
  {
    ;
  }

  skip = end;
  while (end && (data[end - 1] == '#'))
  {
    end -= 1;
  }

  while (end && (data[end - 1] == ' '))
  {
    end -= 1;
  }

  if (end > i)
  {
    struct buf *work = rndr_newbuf(rndr, 1);
    parse_inline(work, rndr, data + i, end - i);
    if (rndr->cb.header)
    {
      rndr->cb.header(ob, work, (int) level, rndr->opaque);
    }
    rndr_popbuf(rndr, 1);
  }
  return skip;
}

static size_t htmlblock_end_tag(const char *tag, size_t tag_len, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  size_t i;
  size_t w;
  if ((((tag_len + 3) >= size) || (strncasecmp(((char *) data) + 2, tag, tag_len) != 0)) || (data[tag_len + 2] != '>'))
  {
    return 0;
  }
  i = tag_len + 3;
  w = 0;
  if ((i < size) && ((w = is_empty(data + i, size - i)) == 0))
  {
    return 0;
  }
  i += w;
  w = 0;
  if (i < size)
  {
    w = is_empty(data + i, size - i);
  }
  return i + w;
}

static size_t htmlblock_end(const char *curtag, struct sd_markdown *rndr, uint8_t *data, size_t size, int start_of_line)
{
  size_t tag_size = strlen(curtag);
  size_t i = 1;
  size_t end_tag;
  int block_lines = 0;
  while (i < size)
  {
    i += 1;
    while ((i < size) && (!((data[i - 1] == '<') && (data[i] == '/'))))
    {
      if (data[i] == '\n')
      {
        block_lines += 1;
      }
      i += 1;
    }

    if ((start_of_line && (block_lines > 0)) && (data[i - 2] != '\n'))
    {
      continue;
    }
    if (((i + 2) + tag_size) >= size)
    {
      break;
    }
    end_tag = htmlblock_end_tag(curtag, tag_size, rndr, (data + i) - 1, (size - i) + 1);
    if (end_tag)
    {
      return (i + end_tag) - 1;
    }
  }

  return 0;
}

static size_t parse_htmlblock(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size, int do_render)
{
  size_t i;
  size_t j = 0;
  size_t tag_end;
  const char *curtag = 0;
  unsigned int curtag_idx = 0;
  struct buf work = {data, 0, 0, 0};
  if ((size < 2) || (data[0] != '<'))
  {
    return 0;
  }
  i = 1;
  while (((i < size) && (data[i] != '>')) && (data[i] != ' '))
  {
    i += 1;
  }

  if (i < size)
  {
    curtag_idx = find_block_tag(((char *) data) + 1, ((int) i) - 1);
  }
  if (!(&curtag[curtag_idx]))
  {
    helper_parse_htmlblock_1(&size, &i, &j, &work, ob, rndr, data, do_render);
  }
  tag_end = htmlblock_end(curtag, rndr, data, size, 1);
  if (((!tag_end) && (strcmp(curtag, "ins") != 0)) && (strcmp(curtag, "del") != 0))
  {
    tag_end = htmlblock_end(curtag, rndr, data, size, 0);
  }
  if (!tag_end)
  {
    return 0;
  }
  work.size = tag_end;
  if (do_render && rndr->cb.blockhtml)
  {
    rndr->cb.blockhtml(ob, &work, rndr->opaque);
  }
  return tag_end;
}

static void parse_table_row(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size, size_t columns, int *col_data, int header_flag)
{
  size_t i = 0;
  size_t col;
  size_t cols_left;
  struct buf *row_work = 0;
  unsigned int row_work_idx = 0;
  if ((!rndr->cb.table_cell) || (!rndr->cb.table_row))
  {
    return;
  }
  row_work_idx = rndr_newbuf(rndr, 1);
  if ((i < size) && (data[i] == '|'))
  {
    i += 1;
  }
  for (col = 0; (col < columns) && (i < size); col += 1)
  {
    helper_parse_table_row_1(&i, rndr, data, size, col_data, header_flag, col, row_work);
  }

  cols_left = columns - col;
  if (cols_left > 0)
  {
    struct buf empty_cell = {0, 0, 0, 0};
    rndr->cb.table_cell(row_work, &empty_cell, col_data[col] | header_flag, rndr->opaque, cols_left);
  }
  rndr->cb.table_row(ob, row_work, rndr->opaque);
  rndr_popbuf(rndr, 1);
}

static size_t parse_table_header(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size, size_t *columns, int **column_data)
{
  int pipes;
  size_t i = 0;
  size_t col;
  size_t header_end;
  size_t under_end;
  pipes = 0;
  while ((i < size) && (data[i] != '\n'))
  {
    if (data[i++] == '|')
    {
      pipes += 1;
    }
  }

  if ((i == size) || (pipes == 0))
  {
    return 0;
  }
  header_end = i;
  while ((header_end > 0) && _isspace(data[header_end - 1]))
  {
    header_end -= 1;
  }

  if (data[0] == '|')
  {
    pipes -= 1;
  }
  if (header_end && (data[header_end - 1] == '|'))
  {
    pipes -= 1;
  }
  if ((pipes + 1) > rndr->max_table_cols)
  {
    return 0;
  }
  *columns = pipes + 1;
  *column_data = calloc(*columns, sizeof(int));
  i += 1;
  if ((i < size) && (data[i] == '|'))
  {
    i += 1;
  }
  under_end = i;
  while ((under_end < size) && (data[under_end] != '\n'))
  {
    under_end += 1;
  }

  for (col = 0; (col < (*columns)) && (i < under_end); col += 1)
  {
    helper_parse_table_header_1(&i, &col, data, column_data, under_end);
  }

  if (col < (*columns))
  {
    return 0;
  }
  parse_table_row(ob, rndr, data, header_end, *columns, *column_data, MKD_TABLE_HEADER);
  return under_end + 1;
}

static size_t parse_table(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  size_t i;
  struct buf *header_work = 0;
  unsigned int header_work_idx = 0;
  struct buf *body_work = 0;
  unsigned int body_work_idx = 0;
  size_t columns;
  int *col_data = 0;
  header_work_idx = rndr_newbuf(rndr, 1);
  body_work_idx = rndr_newbuf(rndr, 0);
  i = parse_table_header(header_work, rndr, data, size, &columns, &col_data);
  if (i > 0)
  {
    while (i < size)
    {
      size_t row_start;
      int pipes = 0;
      row_start = i;
      while ((i < size) && (data[i] != '\n'))
      {
        if (data[i++] == '|')
        {
          pipes += 1;
        }
      }

      if ((pipes == 0) || (i == size))
      {
        i = row_start;
        break;
      }
      parse_table_row(body_work, rndr, data + row_start, i - row_start, columns, col_data, 0);
      i += 1;
    }

    if (rndr->cb.table)
    {
      rndr->cb.table(ob, header_work, body_work, rndr->opaque);
    }
  }
  free(col_data);
  rndr_popbuf(rndr, 1);
  rndr_popbuf(rndr, 0);
  return i;
}

static void parse_block(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  size_t beg;
  size_t end;
  size_t i;
  uint8_t *txt_data;
  unsigned int txt_data_idx = 0;
  beg = 0;
  if ((rndr->work_bufs[1].size + rndr->work_bufs[0].size) > rndr->max_nesting)
  {
    return;
  }
  while (beg < size)
  {
    txt_data_idx = data + beg;
    end = size - beg;
    if (is_atxheader(rndr, txt_data, end))
    {
      beg += parse_atxheader(ob, rndr, txt_data, end);
    }
    else
      if (((data[beg] == '<') && rndr->cb.blockhtml) && ((i = parse_htmlblock(ob, rndr, txt_data, end, 1)) != 0))
    {
      beg += i;
    }
    else
      if ((i = is_empty(txt_data, end)) != 0)
    {
      beg += i;
    }
    else
      if (is_hrule(txt_data, end))
    {
      if (rndr->cb.hrule)
      {
        rndr->cb.hrule(ob, rndr->opaque);
      }
      while ((beg < size) && (data[beg] != '\n'))
      {
        beg += 1;
      }

      beg += 1;
    }
    else
      if (((rndr->ext_flags & MKDEXT_FENCED_CODE) != 0) && ((i = parse_fencedcode(ob, rndr, txt_data, end)) != 0))
    {
      beg += i;
    }
    else
      if (((rndr->ext_flags & MKDEXT_TABLES) != 0) && ((i = parse_table(ob, rndr, txt_data, end)) != 0))
    {
      beg += i;
    }
    else
      if (prefix_quote(txt_data, end))
    {
      beg += parse_blockquote(ob, rndr, txt_data, end);
    }
    else
      if (prefix_blockspoiler(txt_data, end))
    {
      beg += parse_blockspoiler(ob, rndr, txt_data, end);
    }
    else
      if (prefix_code(txt_data, end))
    {
      beg += parse_blockcode(ob, rndr, txt_data, end);
    }
    else
      if (prefix_uli(txt_data, end))
    {
      beg += parse_list(ob, rndr, txt_data, end, 0);
    }
    else
      if (prefix_oli(txt_data, end))
    {
      beg += parse_list(ob, rndr, txt_data, end, 1);
    }
    else
      beg += parse_paragraph(ob, rndr, txt_data, end);
  }

}

static int is_ref(const uint8_t *data, size_t beg, size_t end, size_t *last, struct link_ref **refs)
{
  size_t i = 0;
  size_t id_offset;
  size_t id_end;
  size_t link_offset;
  size_t link_end;
  size_t title_offset;
  size_t title_end;
  size_t line_end;
  if ((beg + 3) >= end)
  {
    return 0;
  }
  if (data[beg] == ' ')
  {
    i = 1;
    if (data[beg + 1] == ' ')
    {
      i = 2;
      if (data[beg + 2] == ' ')
      {
        i = 3;
        if (data[beg + 3] == ' ')
        {
          return 0;
        }
      }
    }
  }
  i += beg;
  if (data[i] != '[')
  {
    return 0;
  }
  i += 1;
  id_offset = i;
  while ((((i < end) && (data[i] != '\n')) && (data[i] != '\r')) && (data[i] != ']'))
  {
    i += 1;
  }

  if ((i >= end) || (data[i] != ']'))
  {
    return 0;
  }
  id_end = i;
  i += 1;
  if ((i >= end) || (data[i] != ':'))
  {
    return 0;
  }
  i += 1;
  while ((i < end) && (data[i] == ' '))
  {
    i += 1;
  }

  if ((i < end) && ((data[i] == '\n') || (data[i] == '\r')))
  {
    i += 1;
    if (((i < end) && (data[i] == '\r')) && (data[i - 1] == '\n'))
    {
      i += 1;
    }
  }
  while ((i < end) && (data[i] == ' '))
  {
    i += 1;
  }

  if (i >= end)
  {
    return 0;
  }
  if (data[i] == '<')
  {
    i += 1;
  }
  link_offset = i;
  while ((((i < end) && (data[i] != ' ')) && (data[i] != '\n')) && (data[i] != '\r'))
  {
    i += 1;
  }

  if (data[i - 1] == '>')
  {
    link_end = i - 1;
  }
  else
    link_end = i;
  while ((i < end) && (data[i] == ' '))
  {
    i += 1;
  }

  if ((((((i < end) && (data[i] != '\n')) && (data[i] != '\r')) && (data[i] != '\'')) && (data[i] != '"')) && (data[i] != '('))
  {
    return 0;
  }
  line_end = 0;
  if (((i >= end) || (data[i] == '\r')) || (data[i] == '\n'))
  {
    line_end = i;
  }
  if ((((i + 1) < end) && (data[i] == '\n')) && (data[i + 1] == '\r'))
  {
    line_end = i + 1;
  }
  if (line_end)
  {
    i = line_end + 1;
    while ((i < end) && (data[i] == ' '))
    {
      i += 1;
    }

  }
  title_offset = (title_end = 0);
  if (((i + 1) < end) && (((data[i] == '\'') || (data[i] == '"')) || (data[i] == '(')))
  {
    helper_is_ref_1(&i, &title_offset, &title_end, &line_end, data, end);
  }
  if ((!line_end) || (link_end == link_offset))
  {
    return 0;
  }
  if (last)
  {
    *last = line_end;
  }
  if (refs)
  {
    helper_is_ref_2(data, refs, id_offset, id_end, link_offset, link_end, title_offset, title_end);
  }
  return 1;
}

static void expand_tabs(struct buf *ob, const uint8_t *line, size_t size)
{
  size_t i = 0;
  size_t tab = 0;
  while (i < size)
  {
    size_t org = i;
    while ((i < size) && (line[i] != '\t'))
    {
      i += 1;
      tab += 1;
    }

    if (i > org)
    {
      bufput(ob, line + org, i - org);
    }
    if (i >= size)
    {
      break;
    }
    do
    {
      bufputc(ob, ' ');
      tab += 1;
    }
    while (tab % 4);
    i += 1;
  }

}

struct sd_markdown *sd_markdown_new(unsigned int extensions, size_t max_nesting, size_t max_table_cols, const struct sd_callbacks *callbacks, void *opaque)
{
  struct sd_markdown *md = 0;
  unsigned int md_idx = 0;
  assert(((max_nesting > 0) && (max_table_cols > 0)) && callbacks);
  md_idx = malloc(sizeof(struct sd_markdown));
  if (!(&md[md_idx]))
  {
    return 0;
  }
  if (!sip_hash_key_init)
  {
    if (backport_getrandom(sip_hash_key, 16, 0) < 16)
    {
      return 0;
    }
    sip_hash_key_init = 1;
  }
  memcpy(&md->cb, callbacks, sizeof(struct sd_callbacks));
  stack_init(&md->work_bufs[0], 4);
  stack_init(&md->work_bufs[1], 8);
  memset(md->active_char, 0x0, 256);
  if ((md->cb.emphasis || md->cb.double_emphasis) || md->cb.triple_emphasis)
  {
    md->active_char['*'] = MD_CHAR_EMPHASIS;
    md->active_char['_'] = MD_CHAR_EMPHASIS;
    md->active_char['>'] = MD_CHAR_EMPHASIS;
    if (extensions & MKDEXT_STRIKETHROUGH)
    {
      md->active_char['~'] = MD_CHAR_EMPHASIS;
    }
  }
  if (md->cb.codespan)
  {
    md->active_char['`'] = MD_CHAR_CODESPAN;
  }
  if (md->cb.linebreak)
  {
    md->active_char['\n'] = MD_CHAR_LINEBREAK;
  }
  if (md->cb.image || md->cb.link)
  {
    md->active_char['['] = MD_CHAR_LINK;
  }
  md->active_char['<'] = MD_CHAR_LANGLE;
  md->active_char['\\'] = MD_CHAR_ESCAPE;
  md->active_char['&'] = MD_CHAR_ENTITITY;
  if (extensions & MKDEXT_AUTOLINK)
  {
    if (!(extensions & MKDEXT_NO_EMAIL_AUTOLINK))
    {
      md->active_char['@'] = MD_CHAR_AUTOLINK_EMAIL;
    }
    md->active_char[':'] = MD_CHAR_AUTOLINK_URL;
    md->active_char['w'] = MD_CHAR_AUTOLINK_WWW;
    md->active_char['/'] = MD_CHAR_AUTOLINK_SUBREDDIT_OR_USERNAME;
  }
  if (extensions & MKDEXT_SUPERSCRIPT)
  {
    md->active_char['^'] = MD_CHAR_SUPERSCRIPT;
  }
  md->ext_flags = extensions;
  md->opaque = opaque;
  md->max_nesting = max_nesting;
  md->max_table_cols = max_table_cols;
  md->in_link_body = 0;
  return md;
}

void sd_markdown_render(struct buf *ob, const uint8_t *document, size_t doc_size, struct sd_markdown *md)
{
  static const char UTF8_BOM[] = {0xEF, 0xBB, 0xBF};
  struct buf *text;
  unsigned int text_idx = 0;
  size_t beg;
  size_t end;
  text_idx = bufnew(64);
  if (!(&text[text_idx]))
  {
    return;
  }
  bufgrow(text, doc_size);
  memset(&md->refs, 0x0, 8 * (sizeof(void *)));
  beg = 0;
  if ((doc_size >= 3) && (memcmp(document, UTF8_BOM, 3) == 0))
  {
    beg += 3;
  }
  while (beg < doc_size)
  {
    helper_sd_markdown_render_1(&beg, &end, document, doc_size, md, text);
  }

  bufgrow(ob, text->size + (text->size >> 1));
  if (md->cb.doc_header)
  {
    md->cb.doc_header(ob, md->opaque);
  }
  if (text->size)
  {
    if ((text->data[text->size - 1] != '\n') && (text->data[text->size - 1] != '\r'))
    {
      bufputc(text, '\n');
    }
    parse_block(ob, md, text->data, text->size);
  }
  if (md->cb.doc_footer)
  {
    md->cb.doc_footer(ob, md->opaque);
  }
  bufrelease(text);
  free_link_refs(md->refs);
  assert(md->work_bufs[1].size == 0);
  assert(md->work_bufs[0].size == 0);
}

void sd_markdown_free(struct sd_markdown *md)
{
  size_t i;
  for (i = 0; i < ((size_t) md->work_bufs[1].asize); i += 1)
  {
    bufrelease(md->work_bufs[1].item[i]);
  }

  for (i = 0; i < ((size_t) md->work_bufs[0].asize); i += 1)
  {
    bufrelease(md->work_bufs[0].item[i]);
  }

  stack_free(&md->work_bufs[1]);
  stack_free(&md->work_bufs[0]);
  free(md);
}

void sd_version(int *ver_major, int *ver_minor, int *ver_revision)
{
  *ver_major = 1;
  *ver_minor = 16;
  *ver_revision = 0;
}


typedef enum 
{
  BUF_OK = 0,
  BUF_ENOMEM = -1,
  BUF_EINVALIDIDX = -2
} buferror_t;
struct buf
{
  uint8_t *data;
  size_t size;
  size_t asize;
  size_t unit;
};
int bufgrow(struct buf *, size_t);
struct buf *bufnew(size_t);
const char *bufcstr(struct buf *);
int bufprefix(const struct buf *buf, const char *prefix);
void bufput(struct buf *, const void *, size_t);
void bufputs(struct buf *, const char *);
void bufputc(struct buf *, int);
void bufrelease(struct buf *);
void bufreset(struct buf *);
void bufslurp(struct buf *, size_t);
void bufprintf(struct buf *, const char *, ...);
int buftruncate(struct buf *buf, size_t size);
enum 
{
  SD_AUTOLINK_SHORT_DOMAINS = 1 << 0
};
int sd_autolink_issafe(const uint8_t *link, size_t link_len);
size_t sd_autolink__www(size_t *rewind_p, struct buf *link, uint8_t *data, size_t max_rewind, size_t size, unsigned int flags);
size_t sd_autolink__email(size_t *rewind_p, struct buf *link, uint8_t *data, size_t max_rewind, size_t size, unsigned int flags);
size_t sd_autolink__url(size_t *rewind_p, struct buf *link, uint8_t *data, size_t max_rewind, size_t size, unsigned int flags);
extern size_t sd_autolink__subreddit(size_t *rewind_p, struct buf *link, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size, int *no_slash);
extern size_t sd_autolink__username(size_t *rewind_p, struct buf *link, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size, int *no_slash);
enum mkd_autolink
{
  MKDA_NOT_AUTOLINK,
  MKDA_NORMAL,
  MKDA_EMAIL
};
enum mkd_tableflags
{
  MKD_TABLE_ALIGN_L = 1,
  MKD_TABLE_ALIGN_R = 2,
  MKD_TABLE_ALIGN_CENTER = 3,
  MKD_TABLE_ALIGNMASK = 3,
  MKD_TABLE_HEADER = 4
};
enum mkd_extensions
{
  MKDEXT_NO_INTRA_EMPHASIS = 1 << 0,
  MKDEXT_TABLES = 1 << 1,
  MKDEXT_FENCED_CODE = 1 << 2,
  MKDEXT_AUTOLINK = 1 << 3,
  MKDEXT_STRIKETHROUGH = 1 << 4,
  MKDEXT_SPACE_HEADERS = 1 << 6,
  MKDEXT_SUPERSCRIPT = 1 << 7,
  MKDEXT_LAX_SPACING = 1 << 8,
  MKDEXT_NO_EMAIL_AUTOLINK = 1 << 9
};
struct sd_callbacks
{
  void (*blockcode)(struct buf *ob, const struct buf *text, const struct buf *lang, void *opaque);
  void (*blockquote)(struct buf *ob, const struct buf *text, void *opaque);
  void (*blockspoiler)(struct buf *ob, const struct buf *text, void *opaque);
  void (*blockhtml)(struct buf *ob, const struct buf *text, void *opaque);
  void (*header)(struct buf *ob, const struct buf *text, int level, void *opaque);
  void (*hrule)(struct buf *ob, void *opaque);
  void (*list)(struct buf *ob, const struct buf *text, int flags, void *opaque);
  void (*listitem)(struct buf *ob, const struct buf *text, int flags, void *opaque);
  void (*paragraph)(struct buf *ob, const struct buf *text, void *opaque);
  void (*table)(struct buf *ob, const struct buf *header, const struct buf *body, void *opaque);
  void (*table_row)(struct buf *ob, const struct buf *text, void *opaque);
  void (*table_cell)(struct buf *ob, const struct buf *text, int flags, void *opaque, int col_span);
  int (*autolink)(struct buf *ob, const struct buf *link, enum mkd_autolink type, void *opaque);
  int (*codespan)(struct buf *ob, const struct buf *text, void *opaque);
  int (*spoilerspan)(struct buf *ob, const struct buf *text, void *opaque);
  int (*double_emphasis)(struct buf *ob, const struct buf *text, void *opaque);
  int (*emphasis)(struct buf *ob, const struct buf *text, void *opaque);
  int (*image)(struct buf *ob, const struct buf *link, const struct buf *title, const struct buf *alt, void *opaque);
  int (*linebreak)(struct buf *ob, void *opaque);
  int (*link)(struct buf *ob, const struct buf *link, const struct buf *title, const struct buf *content, void *opaque);
  int (*raw_html_tag)(struct buf *ob, const struct buf *tag, void *opaque);
  int (*triple_emphasis)(struct buf *ob, const struct buf *text, void *opaque);
  int (*strikethrough)(struct buf *ob, const struct buf *text, void *opaque);
  int (*superscript)(struct buf *ob, const struct buf *text, void *opaque);
  void (*entity)(struct buf *ob, const struct buf *entity, void *opaque);
  void (*normal_text)(struct buf *ob, const struct buf *text, void *opaque);
  void (*doc_header)(struct buf *ob, void *opaque);
  void (*doc_footer)(struct buf *ob, void *opaque);
};
struct sd_markdown;
extern struct sd_markdown *sd_markdown_new(unsigned int extensions, size_t max_nesting, size_t max_table_cols, const struct sd_callbacks *callbacks, void *opaque);
extern void sd_markdown_render(struct buf *ob, const uint8_t *document, size_t doc_size, struct sd_markdown *md);
extern void sd_markdown_free(struct sd_markdown *md);
extern void sd_version(int *major, int *minor, int *revision);
struct stack
{
  void **item;
  size_t size;
  size_t asize;
};
void stack_free(struct stack *);
int stack_grow(struct stack *, size_t);
int stack_init(struct stack *, size_t);
int stack_push(struct stack *, void *);
void *stack_pop(struct stack *);
void *stack_top(struct stack *);
uint64_t siphash(const uint8_t *in, const size_t inlen, const uint8_t *k);
uint64_t siphash_nocase(const uint8_t *in, const size_t inlen, const uint8_t *k);
static unsigned int hash_block_tag(const char *str, unsigned int len)
{
  static const unsigned char asso_values[] = {38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 8, 30, 25, 20, 15, 10, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 0, 38, 0, 38, 5, 5, 5, 15, 0, 38, 38, 0, 15, 10, 0, 38, 38, 15, 0, 5, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 0, 38, 0, 38, 5, 5, 5, 15, 0, 38, 38, 0, 15, 10, 0, 38, 38, 15, 0, 5, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38, 38};
  int hval = len;
  switch (hval)
  {
    default:
      hval += asso_values[((unsigned char) str[1]) + 1];

    case 1:
      hval += asso_values[(unsigned char) str[0]];
      break;

  }

  return hval;
}

const char *find_block_tag(const char *str, unsigned int len)
{
  enum 
  {
    TOTAL_KEYWORDS = 24,
    MIN_WORD_LENGTH = 1,
    MAX_WORD_LENGTH = 10,
    MIN_HASH_VALUE = 1,
    MAX_HASH_VALUE = 37
  };
  static const char * const wordlist[] = {"", "p", "dl", "div", "math", "table", "", "ul", "del", "form", "blockquote", "figure", "ol", "fieldset", "", "h1", "", "h6", "pre", "", "", "script", "h5", "noscript", "", "style", "iframe", "h4", "ins", "", "", "", "h3", "", "", "", "", "h2", "span"};
  if ((len <= MAX_WORD_LENGTH) && (len >= MIN_WORD_LENGTH))
  {
    int key = hash_block_tag(str, len);
    if ((key <= MAX_HASH_VALUE) && (key >= 0))
    {
      const char *s = wordlist[key];
      if (((((((unsigned char) (*str)) ^ ((unsigned char) (*s))) & (~32)) == 0) && (!strncasecmp(str, s, len))) && (s[len] == '\0'))
      {
        return s;
      }
    }
  }
  return 0;
}

const unsigned MAX_NUM_ENTITY_VAL = 0x10ffff;
const size_t MAX_NUM_ENTITY_LEN = 7;
inline int is_valid_numeric_entity(uint32_t entity_val)
{
  return (((((entity_val > 8) && ((entity_val != 11) && (entity_val != 12))) && ((entity_val < 14) || (entity_val > 31))) && ((entity_val < 55296) || (entity_val > 57343))) && ((entity_val != 65534) && (entity_val != 65535))) && (entity_val <= MAX_NUM_ENTITY_VAL);
}

static unsigned int hash_html_entity(register const char *str, register size_t len)
{
  static const unsigned short asso_values[] = {771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 0, 95, 90, 0, 771, 771, 771, 771, 771, 771, 0, 771, 771, 771, 771, 771, 115, 94, 55, 0, 150, 25, 0, 30, 195, 771, 30, 30, 5, 35, 45, 45, 771, 10, 0, 50, 125, 771, 771, 5, 85, 75, 771, 771, 771, 771, 771, 771, 40, 65, 20, 25, 60, 240, 240, 223, 10, 102, 20, 35, 135, 0, 5, 10, 183, 20, 5, 0, 50, 75, 10, 75, 175, 85, 15, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771, 771};
  register unsigned int hval = len;
  switch (hval)
  {
    default:
      hval += asso_values[(unsigned char) str[6]];

    case 6:
      hval += asso_values[(unsigned char) str[5]];

    case 5:
      hval += asso_values[(unsigned char) str[4]];

    case 4:
      hval += asso_values[(unsigned char) str[3]];

    case 3:
      hval += asso_values[((unsigned char) str[2]) + 1];

    case 2:
      hval += asso_values[(unsigned char) str[1]];
      break;

  }

  return hval;
}

const char *is_allowed_named_entity(register const char *str, register size_t len)
{
  enum 
  {
    TOTAL_KEYWORDS = 253,
    MIN_WORD_LENGTH = 4,
    MAX_WORD_LENGTH = 10,
    MIN_HASH_VALUE = 14,
    MAX_HASH_VALUE = 770
  };
  static const char * const wordlist[] = {"", "", "", "", "", "", "", "", "", "", "", "", "", "", "&or;", "&not;", "", "", "", "", "&int;", "", "", "", "", "&psi;", "&isin;", "&notin;", "", "", "&Rho;", "", "", "", "", "&phi;", "&prop;", "", "", "", "&rho;", "&nbsp;", "&thorn;", "&thinsp;", "", "&chi;", "", "", "", "", "", "&prod;", "", "", "", "&amp;", "", "", "", "", "&Psi;", "", "", "", "", "", "&iota;", "", "", "&omicron;", "&Phi;", "", "", "", "", "&and;", "&sdot;", "", "", "&nu;", "&Chi;", "&emsp;", "", "", "&Mu;", "", "&ensp;", "&ocirc;", "", "&lt;", "&uml;", "", "&icirc;", "", "", "&sup;", "&sup1;", "", "&Scaron;", "", "&cap;", "&part;", "&pound;", "&scaron;", "", "", "&ni;", "", "&lowast;", "&Omicron;", "&cup;", "&Xi;", "&crarr;", "", "&Nu;", "", "&pi;", "&theta;", "", "", "&tau;", "&nsub;", "&acirc;", "", "", "&thetasym;", "", "&Ocirc;", "", "", "", "&rarr;", "&ucirc;", "", "", "&loz;", "&darr;", "&trade;", "", "", "", "&para;", "&ecirc;", "", "", "", "&larr;", "&radic;", "", "", "&sub;", "&Pi;", "&kappa;", "&iquest;", "", "&eta;", "&supe;", "&rceil;", "&there4;", "", "&rArr;", "&uarr;", "&Kappa;", "", "", "&dArr;", "&euro;", "&Theta;", "&circ;", "", "&Tau;", "", "&lceil;", "", "", "&lArr;", "&ordm;", "", "", "", "&lrm;", "&xi;", "&acute;", "&ccedil;", "", "", "&sup3;", "", "&ntilde;", "", "&uArr;", "&sup2;", "&piv;", "&otilde;", "", "&shy;", "", "&Acirc;", "", "", "", "", "", "&curren;", "", "", "", "&Ucirc;", "&oacute;", "", "", "&sube;", "&nabla;", "&iacute;", "&mu;", "", "&bull;", "&oline;", "&Ccedil;", "", "&sum;", "&copy;", "&equiv;", "&Ntilde;", "", "", "", "&prime;", "&atilde;", "&tilde;", "", "", "&Ecirc;", "&Otilde;", "", "", "", "", "", "&apos;", "", "", "", "&aacute;", "&ne;", "&Eta;", "&macr;", "&sim;", "&Oacute;", "", "", "&Iota;", "&empty;", "&uacute;", "", "", "&ouml;", "&exist;", "", "", "", "&iuml;", "&Prime;", "&eacute;", "", "&rsquo;", "&cent;", "&zwj;", "&zwnj;", "&quot;", "&sbquo;", "&sect;", "&infin;", "&otimes;", "", "", "&cong;", "&Icirc;", "&brvbar;", "&le;", "&lsquo;", "&ordf;", "&clubs;", "", "", "&oplus;", "&perp;", "", "&Yacute;", "&micro;", "&ang;", "&auml;", "", "", "&gt;", "&rlm;", "&Ouml;", "&upsilon;", "", "&minus;", "&middot;", "&uuml;", "&aring;", "&Atilde;", "", "&divide;", "&rsaquo;", "&epsilon;", "", "&times;", "&ETH;", "&euml;", "&szlig;", "&frac14;", "&diams;", "", "&oslash;", "", "&Aacute;", "", "", "&lsaquo;", "&Delta;", "", "", "&rdquo;", "&spades;", "", "&Uacute;", "", "&raquo;", "&rang;", "&frasl;", "&rfloor;", "&harr;", "&ndash;", "&Yuml;", "&cedil;", "&eth;", "", "&ldquo;", "&real;", "&THORN;", "&plusmn;", "", "&laquo;", "&lang;", "&delta;", "&lfloor;", "", "", "&beta;", "&omega;", "&Eacute;", "", "", "&Oslash;", "&image;", "&weierp;", "", "", "&Zeta;", "&OElig;", "&hArr;", "", "", "&Auml;", "&asymp;", "&Lambda;", "", "&bdquo;", "&zeta;", "&Upsilon;", "&lambda;", "", "", "&Uuml;", "&Aring;", "&yacute;", "", "&Beta;", "", "&Gamma;", "", "", "", "", "&iexcl;", "&forall;", "", "", "", "&Omega;", "", "", "", "", "&Epsilon;", "&Iacute;", "", "", "&Euml;", "", "&frac34;", "", "", "", "", "&frac12;", "", "", "", "", "", "", "", "", "", "", "", "&yen;", "", "", "", "", "", "&yuml;", "", "", "", "", "&ograve;", "&AElig;", "", "", "", "&igrave;", "", "", "", "", "", "", "", "", "", "&Iuml;", "", "", "", "", "", "", "", "", "&alpha;", "", "", "&permil;", "", "", "", "", "", "", "", "&agrave;", "", "", "", "&mdash;", "&Ograve;", "", "", "", "", "&ugrave;", "", "&upsih;", "", "", "", "", "", "&ge;", "", "&egrave;", "", "", "", "", "", "", "", "", "", "&fnof;", "", "", "", "", "", "", "", "", "&reg;", "", "", "", "", "&deg;", "", "", "", "", "", "", "", "", "", "", "", "", "", "&Sigma;", "", "", "", "", "&sigma;", "&Alpha;", "", "", "", "", "", "&hearts;", "&oelig;", "", "", "", "&Agrave;", "", "", "", "", "", "", "", "", "", "&Ugrave;", "", "", "", "", "", "", "", "", "", "&hellip;", "", "", "", "", "", "", "", "", "", "", "&aelig;", "", "", "", "&Egrave;", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "&Igrave;", "&gamma;", "", "", "", "", "", "", "", "", "", "", "&Dagger;", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "&dagger;", "", "", "", "", "", "&alefsym;", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "&sigmaf;"};
  if ((len <= MAX_WORD_LENGTH) && (len >= MIN_WORD_LENGTH))
  {
    register unsigned int key = hash_html_entity(str, len);
    if (key <= MAX_HASH_VALUE)
    {
      register const char *s = wordlist[key];
      if ((((*str) == (*s)) && (!strncmp(str + 1, s + 1, len - 1))) && (s[len] == '\0'))
      {
        return s;
      }
    }
  }
  return 0;
}

struct link_ref
{
  unsigned int id;
  struct buf *link;
  struct buf *label;
  struct buf *title;
  struct link_ref *next;
};
struct sd_markdown;
typedef size_t (*char_trigger)(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size);
static size_t char_emphasis(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size);
static size_t char_linebreak(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size);
static size_t char_codespan(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size);
static size_t char_escape(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size);
static size_t char_entity(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size);
static size_t char_langle_tag(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size);
static size_t char_autolink_url(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size);
static size_t char_autolink_email(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size);
static size_t char_autolink_www(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size);
static size_t char_autolink_subreddit_or_username(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size);
static size_t char_link(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size);
static size_t char_superscript(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size);
enum markdown_char_t
{
  MD_CHAR_NONE = 0,
  MD_CHAR_EMPHASIS,
  MD_CHAR_CODESPAN,
  MD_CHAR_LINEBREAK,
  MD_CHAR_LINK,
  MD_CHAR_LANGLE,
  MD_CHAR_ESCAPE,
  MD_CHAR_ENTITITY,
  MD_CHAR_AUTOLINK_URL,
  MD_CHAR_AUTOLINK_EMAIL,
  MD_CHAR_AUTOLINK_WWW,
  MD_CHAR_AUTOLINK_SUBREDDIT_OR_USERNAME,
  MD_CHAR_SUPERSCRIPT
};
static char_trigger markdown_char_ptrs[] = {0, &char_emphasis, &char_codespan, &char_linebreak, &char_link, &char_langle_tag, &char_escape, &char_entity, &char_autolink_url, &char_autolink_email, &char_autolink_www, &char_autolink_subreddit_or_username, &char_superscript};
struct sd_markdown
{
  struct sd_callbacks cb;
  void *opaque;
  struct link_ref *refs[8];
  uint8_t active_char[256];
  struct stack work_bufs[2];
  unsigned int ext_flags;
  size_t max_nesting;
  size_t max_table_cols;
  int in_link_body;
};
int sip_hash_key_init = 0;
uint8_t sip_hash_key[16];
int backport_getrandom(void *buf, size_t buflen, unsigned int flags)
{
  return (int) syscall(SYS_getrandom, buf, buflen, flags);
}

inline static struct buf *rndr_newbuf(struct sd_markdown *rndr, int type)
{
  static const size_t buf_size[2] = {256, 64};
  struct buf *work = 0;
  unsigned int work_idx = 0;
  struct stack *pool = &rndr->work_bufs[type];
  if ((pool->size < pool->asize) && (pool->item[pool->size] != 0))
  {
    work_idx = pool->item[pool->size++];
    work->size = 0;
  }
  else
  {
    work_idx = bufnew(buf_size[type]);
    stack_push(pool, work);
  }
  return work;
}

inline static void rndr_popbuf(struct sd_markdown *rndr, int type)
{
  rndr->work_bufs[type].size -= 1;
}

static void unscape_text(struct buf *ob, struct buf *src)
{
  size_t i = 0;
  size_t org;
  while (i < src->size)
  {
    org = i;
    while ((i < src->size) && (src->data[i] != '\\'))
    {
      i += 1;
    }

    if (i > org)
    {
      bufput(ob, src->data + org, i - org);
    }
    if ((i + 1) >= src->size)
    {
      break;
    }
    bufputc(ob, src->data[i + 1]);
    i += 2;
  }

}

static unsigned int hash_link_ref(const uint8_t *link_ref, size_t length)
{
  return siphash_nocase(link_ref, length, sip_hash_key);
}

static struct link_ref *add_link_ref(struct link_ref **references, const uint8_t *name, size_t name_size)
{
  unsigned int hash;
  struct link_ref *ref;
  unsigned int ref_idx = 0;
  hash = hash_link_ref(name, name_size);
  ref_idx = references[hash % 8];
  while ((&ref[ref_idx]) != 0)
  {
    if ((ref->id == hash) && (ref->label->size == name_size))
    {
      if (strncasecmp((char *) ref->label->data, (char *) name, name_size) == 0)
      {
        bufrelease(ref->label);
        bufrelease(ref->link);
        bufrelease(ref->title);
        return ref;
      }
    }
    ref_idx = ref_idx->next;
  }

  ref_idx = calloc(1, sizeof(struct link_ref));
  if (!(&ref[ref_idx]))
  {
    return 0;
  }
  ref->id = hash;
  ref->next = references[ref->id % 8];
  references[ref->id % 8] = &ref[ref_idx];
  return ref;
}

static struct link_ref *find_link_ref(struct link_ref **references, uint8_t *name, size_t length)
{
  unsigned int hash = hash_link_ref(name, length);
  struct link_ref *ref = 0;
  unsigned int ref_idx = 0;
  ref_idx = references[hash % 8];
  while ((&ref[ref_idx]) != 0)
  {
    if ((ref->id == hash) && (ref->label->size == length))
    {
      if (strncasecmp((char *) ref->label->data, (char *) name, length) == 0)
      {
        return ref;
      }
    }
    ref_idx = ref_idx->next;
  }

  return 0;
}

static void free_link_refs(struct link_ref **references)
{
  size_t i;
  for (i = 0; i < 8; i += 1)
  {
    struct link_ref *r = references[i];
    unsigned int r_idx = 0;
    struct link_ref *next;
    unsigned int next_idx = 0;
    while (r)
    {
      next_idx = r->next_idx;
      bufrelease(r->label);
      bufrelease(r->link);
      bufrelease(r->title);
      free(r);
      r_idx = &next[next_idx];
    }

  }

}

inline static int _isspace(int c)
{
  return (c == ' ') || (c == '\n');
}

static size_t is_mail_autolink(uint8_t *data, size_t size)
{
  size_t i = 0;
  size_t nb = 0;
  for (i = 0; i < size; i += 1)
  {
    if (isalnum(data[i]))
    {
      continue;
    }
    switch (data[i])
    {
      case '@':
        nb += 1;

      case '-':

      case '.':

      case '_':
        break;

      case '>':
        return (nb == 1) ? (i + 1) : (0);

      default:
        return 0;

    }

  }

  return 0;
}

static size_t tag_length(uint8_t *data, size_t size, enum mkd_autolink *autolink)
{
  size_t i;
  size_t j;
  if (size < 3)
  {
    return 0;
  }
  if (data[0] != '<')
  {
    return 0;
  }
  i = (data[1] == '/') ? (2) : (1);
  if (!isalnum(data[i]))
  {
    return 0;
  }
  *autolink = MKDA_NOT_AUTOLINK;
  while ((i < size) && (((isalnum(data[i]) || (data[i] == '.')) || (data[i] == '+')) || (data[i] == '-')))
  {
    i += 1;
  }

  if ((i > 1) && (data[i] == '@'))
  {
    if ((j = is_mail_autolink(data + i, size - i)) != 0)
    {
      *autolink = MKDA_EMAIL;
      return i + j;
    }
  }
  if ((i > 2) && (data[i] == ':'))
  {
    *autolink = MKDA_NORMAL;
    i += 1;
  }
  if (i >= size)
  {
    *autolink = MKDA_NOT_AUTOLINK;
  }
  else
    if (*autolink)
  {
    j = i;
    while (i < size)
    {
      if (data[i] == '\\')
      {
        i += 2;
      }
      else
        if (((((data[i] == '>') || (data[i] == '\'')) || (data[i] == '"')) || (data[i] == ' ')) || (data[i] == '\n'))
      {
        break;
      }
      else
        i++;
      i += 1;
    }

    if (i >= size)
    {
      return 0;
    }
    if ((i > j) && (data[i] == '>'))
    {
      return i + 1;
    }
    *autolink = MKDA_NOT_AUTOLINK;
  }
  while ((i < size) && (data[i] != '>'))
  {
    i += 1;
  }

  if (i >= size)
  {
    return 0;
  }
  return i + 1;
}

static void parse_inline(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  size_t i = 0;
  size_t end = 0;
  size_t last_special = 0;
  uint8_t action = 0;
  struct buf work = {0, 0, 0, 0};
  if ((rndr->work_bufs[1].size + rndr->work_bufs[0].size) > rndr->max_nesting)
  {
    return;
  }
  while (i < size)
  {
    while ((end < size) && ((action = rndr->active_char[data[end]]) == 0))
    {
      end += 1;
    }

    if (rndr->cb.normal_text)
    {
      work.data = data + i;
      work.size = end - i;
      rndr->cb.normal_text(ob, &work, rndr->opaque);
    }
    else
      bufput(ob, data + i, end - i);
    if (end >= size)
    {
      break;
    }
    i = end;
    end = markdown_char_ptrs[(int) action](ob, rndr, data + i, i - last_special, i, size - i);
    if (!end)
    {
      end = i + 1;
    }
    else
    {
      i += end;
      last_special = (end = i);
    }
  }

}

static size_t find_emph_char(uint8_t *data, size_t size, uint8_t c)
{
  size_t i = 1;
  while (i < size)
  {
    while ((((i < size) && (data[i] != c)) && (data[i] != '`')) && (data[i] != '['))
    {
      i += 1;
    }

    if (i == size)
    {
      return 0;
    }
    if ((((i < size) && (c == '<')) && (data[i] == c)) && (data[i - 1] == '!'))
    {
      return i;
    }
    if (data[i] == c)
    {
      return i;
    }
    if (i && (data[i - 1] == '\\'))
    {
      i += 1;
      continue;
    }
    if (data[i] == '`')
    {
      size_t span_nb = 0;
      size_t bt;
      size_t tmp_i = 0;
      while ((i < size) && (data[i] == '`'))
      {
        i += 1;
        span_nb += 1;
      }

      if (i >= size)
      {
        return 0;
      }
      bt = 0;
      while ((i < size) && (bt < span_nb))
      {
        if ((!tmp_i) && (data[i] == c))
        {
          tmp_i = i;
        }
        if (data[i] == '`')
        {
          bt += 1;
        }
        else
          bt = 0;
        i += 1;
      }

      if (i >= size)
      {
        return tmp_i;
      }
    }
    else
      if (data[i] == '[')
    {
      size_t tmp_i = 0;
      uint8_t cc;
      i += 1;
      while ((i < size) && (data[i] != ']'))
      {
        if ((!tmp_i) && (data[i] == c))
        {
          tmp_i = i;
        }
        i += 1;
      }

      i += 1;
      while ((i < size) && ((data[i] == ' ') || (data[i] == '\n')))
      {
        i += 1;
      }

      if (i >= size)
      {
        return tmp_i;
      }
      switch (data[i])
      {
        case '[':
          cc = ']';
          break;

        case '(':
          cc = ')';
          break;

        default:
          if (tmp_i)
        {
          return tmp_i;
        }
        else
          continue;

      }

      i += 1;
      while ((i < size) && (data[i] != cc))
      {
        if ((!tmp_i) && (data[i] == c))
        {
          tmp_i = i;
        }
        i += 1;
      }

      if (i >= size)
      {
        return tmp_i;
      }
      i += 1;
    }
  }

  return 0;
}

static size_t parse_emph1(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size, uint8_t c)
{
  size_t i = 0;
  size_t len;
  struct buf *work = 0;
  unsigned int work_idx = 0;
  int r;
  if (!rndr->cb.emphasis)
  {
    return 0;
  }
  if (((size > 1) && (data[0] == c)) && (data[1] == c))
  {
    i = 1;
  }
  while (i < size)
  {
    len = find_emph_char(data + i, size - i, c);
    if (!len)
    {
      return 0;
    }
    i += len;
    if (i >= size)
    {
      return 0;
    }
    if ((data[i] == c) && (!_isspace(data[i - 1])))
    {
      if ((rndr->ext_flags & MKDEXT_NO_INTRA_EMPHASIS) && (c == '_'))
      {
        if (!((((i + 1) == size) || _isspace(data[i + 1])) || ispunct(data[i + 1])))
        {
          continue;
        }
      }
      work_idx = rndr_newbuf(rndr, 1);
      parse_inline(work, rndr, data, i);
      r = rndr->cb.emphasis(ob, work, rndr->opaque);
      rndr_popbuf(rndr, 1);
      return (r) ? (i + 1) : (0);
    }
  }

  return 0;
}

static size_t parse_emph2(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size, uint8_t c)
{
  int (*render_method)(struct buf *ob, const struct buf *text, void *opaque);
  unsigned int render_method_idx = 0;
  size_t i = 0;
  size_t len;
  struct buf *work = 0;
  unsigned int work_idx = 0;
  int r;
  render_method_idx = (c == '~') ? (rndr->cb.strikethrough) : (rndr->cb.double_emphasis);
  if (!(&render_method[render_method_idx]))
  {
    return 0;
  }
  while (i < size)
  {
    len = find_emph_char(data + i, size - i, c);
    if (!len)
    {
      return 0;
    }
    i += len;
    if ((((((i + 1) < size) && (data[i] == c)) && (data[i + 1] == c)) && i) && (!_isspace(data[i - 1])))
    {
      work_idx = rndr_newbuf(rndr, 1);
      parse_inline(work, rndr, data, i);
      r = render_method(ob, work, rndr->opaque);
      rndr_popbuf(rndr, 1);
      return (r) ? (i + 2) : (0);
    }
    i += 1;
  }

  return 0;
}

static size_t parse_emph3(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size, uint8_t c)
{
  size_t i = 0;
  size_t len;
  int r;
  while (i < size)
  {
    len = find_emph_char(data + i, size - i, c);
    if (!len)
    {
      return 0;
    }
    i += len;
    if ((data[i] != c) || _isspace(data[i - 1]))
    {
      continue;
    }
    if (((((i + 2) < size) && (data[i + 1] == c)) && (data[i + 2] == c)) && rndr->cb.triple_emphasis)
    {
      struct buf *work = rndr_newbuf(rndr, 1);
      parse_inline(work, rndr, data, i);
      r = rndr->cb.triple_emphasis(ob, work, rndr->opaque);
      rndr_popbuf(rndr, 1);
      return (r) ? (i + 3) : (0);
    }
    else
      if (((i + 1) < size) && (data[i + 1] == c))
    {
      len = parse_emph1(ob, rndr, data - 2, size + 2, c);
      if (!len)
      {
        return 0;
      }
      else
        return len - 2;
    }
    else
    {
      len = parse_emph2(ob, rndr, data - 1, size + 1, c);
      if (!len)
      {
        return 0;
      }
      else
        return len - 1;
    }
  }

  return 0;
}

static size_t parse_spoilerspan(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  int (*render_method)(struct buf *ob, const struct buf *text, void *opaque);
  unsigned int render_method_idx = 0;
  size_t len;
  size_t i = 0;
  struct buf *work = 0;
  unsigned int work_idx = 0;
  int r;
  render_method_idx = rndr->cb.spoilerspan;
  if (!(&render_method[render_method_idx]))
  {
    return 0;
  }
  while (i < size)
  {
    len = find_emph_char(data + i, size - i, '<');
    if (!len)
    {
      return 0;
    }
    i += len;
    if (((i < size) && (data[i] == '<')) && (data[i - 1] == '!'))
    {
      work_idx = rndr_newbuf(rndr, 1);
      parse_inline(work, rndr, data, i - 1);
      r = render_method(ob, work, rndr->opaque);
      rndr_popbuf(rndr, 1);
      if (!r)
      {
        return 0;
      }
      return i + 1;
    }
    i += 1;
  }

  return 0;
}

static size_t char_emphasis(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size)
{
  uint8_t c = data[0];
  size_t ret;
  if (((size > 3) && (c == '>')) && (data[1] == '!'))
  {
    if (_isspace(data[2]) || ((ret = parse_spoilerspan(ob, rndr, data + 2, size - 2)) == 0))
    {
      return 0;
    }
    return ret + 2;
  }
  if ((size > 2) && (data[1] != c))
  {
    if ((((c == '~') || (c == '>')) || _isspace(data[1])) || ((ret = parse_emph1(ob, rndr, data + 1, size - 1, c)) == 0))
    {
      return 0;
    }
    return ret + 1;
  }
  if (((size > 3) && (data[1] == c)) && (data[2] != c))
  {
    if (_isspace(data[2]) || ((ret = parse_emph2(ob, rndr, data + 2, size - 2, c)) == 0))
    {
      return 0;
    }
    return ret + 2;
  }
  if ((((size > 4) && (data[1] == c)) && (data[2] == c)) && (data[3] != c))
  {
    if ((((c == '~') || (c == '>')) || _isspace(data[3])) || ((ret = parse_emph3(ob, rndr, data + 3, size - 3, c)) == 0))
    {
      return 0;
    }
    return ret + 3;
  }
  return 0;
}

static size_t char_linebreak(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size)
{
  if (((max_rewind < 2) || (data[-1] != ' ')) || (data[-2] != ' '))
  {
    return 0;
  }
  while (ob->size && (ob->data[ob->size - 1] == ' '))
  {
    ob->size -= 1;
  }

  return (rndr->cb.linebreak(ob, rndr->opaque)) ? (1) : (0);
}

static size_t char_codespan(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size)
{
  size_t end;
  size_t nb = 0;
  size_t i;
  size_t f_begin;
  size_t f_end;
  while ((nb < size) && (data[nb] == '`'))
  {
    nb += 1;
  }

  i = 0;
  for (end = nb; (end < size) && (i < nb); end += 1)
  {
    if (data[end] == '`')
    {
      i += 1;
    }
    else
      i = 0;
  }

  if ((i < nb) && (end >= size))
  {
    return 0;
  }
  f_begin = nb;
  while ((f_begin < end) && (data[f_begin] == ' '))
  {
    f_begin += 1;
  }

  f_end = end - nb;
  while ((f_end > nb) && (data[f_end - 1] == ' '))
  {
    f_end -= 1;
  }

  if (f_begin < f_end)
  {
    struct buf work = {data + f_begin, f_end - f_begin, 0, 0};
    if (!rndr->cb.codespan(ob, &work, rndr->opaque))
    {
      end = 0;
    }
  }
  else
  {
    if (!rndr->cb.codespan(ob, 0, rndr->opaque))
    {
      end = 0;
    }
  }
  return end;
}

static size_t char_escape(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size)
{
  static const char *escape_chars = "\\`*_{}[]()#+-.!:|&<>/^~";
  struct buf work = {0, 0, 0, 0};
  if (size > 1)
  {
    if (strchr(escape_chars, data[1]) == 0)
    {
      return 0;
    }
    if (rndr->cb.normal_text)
    {
      work.data = data + 1;
      work.size = 1;
      rndr->cb.normal_text(ob, &work, rndr->opaque);
    }
    else
      bufputc(ob, data[1]);
  }
  else
    if (size == 1)
  {
    bufputc(ob, data[0]);
  }
  return 2;
}

static size_t char_entity(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size)
{
  size_t end = 1;
  size_t content_start;
  size_t content_end;
  struct buf work = {0, 0, 0, 0};
  int numeric = 0;
  int hex = 0;
  int entity_base;
  uint32_t entity_val;
  if ((end < size) && (data[end] == '#'))
  {
    numeric = 1;
    end += 1;
  }
  if (((end < size) && numeric) && (tolower(data[end]) == 'x'))
  {
    hex = 1;
    end += 1;
  }
  content_start = end;
  while (end < size)
  {
    const char c = data[end];
    if (hex)
    {
      if (!isxdigit(c))
      {
        break;
      }
    }
    else
      if (numeric)
    {
      if (!isdigit(c))
      {
        break;
      }
    }
    else
      if (!isalnum(c))
    {
      break;
    }
    end += 1;
  }

  content_end = end;
  if (((end > content_start) && (end < size)) && (data[end] == ';'))
  {
    end += 1;
  }
  else
    return 0;
  if (numeric && ((content_end - content_start) > MAX_NUM_ENTITY_LEN))
  {
    return 0;
  }
  if (numeric)
  {
    if (hex)
    {
      entity_base = 16;
    }
    else
      entity_base = 10;
    entity_val = strtol(((char *) data) + content_start, 0, entity_base);
    if (!is_valid_numeric_entity(entity_val))
    {
      return 0;
    }
  }
  else
  {
    if (!is_allowed_named_entity((const char *) data, end))
    {
      return 0;
    }
  }
  if (rndr->cb.entity)
  {
    work.data = data;
    work.size = end;
    rndr->cb.entity(ob, &work, rndr->opaque);
  }
  else
  {
    bufputc(ob, '&');
    if (numeric)
    {
      bufputc(ob, '#');
    }
    if (hex)
    {
      bufputc(ob, 'x');
    }
    bufput(ob, data + content_start, end - content_start);
  }
  return end;
}

static size_t char_langle_tag(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size)
{
  enum mkd_autolink altype = MKDA_NOT_AUTOLINK;
  size_t end = tag_length(data, size, &altype);
  struct buf work = {data, end, 0, 0};
  int ret = 0;
  if (end > 2)
  {
    if (rndr->cb.autolink && (altype != MKDA_NOT_AUTOLINK))
    {
      struct buf *u_link = rndr_newbuf(rndr, 1);
      work.data = data + 1;
      work.size = end - 2;
      unscape_text(u_link, &work);
      ret = rndr->cb.autolink(ob, u_link, altype, rndr->opaque);
      rndr_popbuf(rndr, 1);
    }
    else
      if (rndr->cb.raw_html_tag)
    {
      ret = rndr->cb.raw_html_tag(ob, &work, rndr->opaque);
    }
  }
  if (!ret)
  {
    return 0;
  }
  else
    return end;
}

static size_t char_autolink_www(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size)
{
  struct buf *link;
  unsigned int link_idx = 0;
  struct buf *link_url;
  unsigned int link_url_idx = 0;
  struct buf *link_text;
  unsigned int link_text_idx = 0;
  size_t link_len;
  size_t rewind;
  if ((!rndr->cb.link) || rndr->in_link_body)
  {
    return 0;
  }
  link_idx = rndr_newbuf(rndr, 1);
  if ((link_len = sd_autolink__www(&rewind, link, data, max_rewind, size, 0)) > 0)
  {
    link_url_idx = rndr_newbuf(rndr, 1);
    bufput(link_url, "http://", (sizeof("http://")) - 1);
    bufput(link_url, link->data, link->size);
    buftruncate(ob, ob->size - rewind);
    if (rndr->cb.normal_text)
    {
      link_text_idx = rndr_newbuf(rndr, 1);
      rndr->cb.normal_text(link_text, link, rndr->opaque);
      rndr->cb.link(ob, link_url, 0, link_text, rndr->opaque);
      rndr_popbuf(rndr, 1);
    }
    else
    {
      rndr->cb.link(ob, link_url, 0, link, rndr->opaque);
    }
    rndr_popbuf(rndr, 1);
  }
  rndr_popbuf(rndr, 1);
  return link_len;
}

static size_t char_autolink_subreddit_or_username(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size)
{
  struct buf *link;
  unsigned int link_idx = 0;
  struct buf *link_text;
  unsigned int link_text_idx = 0;
  struct buf *link_url;
  unsigned int link_url_idx = 0;
  size_t link_len;
  size_t rewind;
  int no_slash;
  if ((!rndr->cb.autolink) || rndr->in_link_body)
  {
    return 0;
  }
  link_idx = rndr_newbuf(rndr, 1);
  link_len = sd_autolink__subreddit(&rewind, link, data, max_rewind, max_lookbehind, size, &no_slash);
  if (link_len == 0)
  {
    link_len = sd_autolink__username(&rewind, link, data, max_rewind, max_lookbehind, size, &no_slash);
  }
  if (link_len > 0)
  {
    link_url_idx = rndr_newbuf(rndr, 1);
    if (no_slash)
    {
      bufputc(link_url, '/');
    }
    bufput(link_url, link->data, link->size);
    buftruncate(ob, ob->size - rewind);
    if (rndr->cb.normal_text)
    {
      link_text_idx = rndr_newbuf(rndr, 1);
      rndr->cb.normal_text(link_text, link, rndr->opaque);
      rndr->cb.link(ob, link_url, 0, link_text, rndr->opaque);
      rndr_popbuf(rndr, 1);
    }
    else
    {
      rndr->cb.link(ob, link_url, 0, link, rndr->opaque);
    }
    rndr_popbuf(rndr, 1);
  }
  rndr_popbuf(rndr, 1);
  return link_len;
}

static size_t char_autolink_email(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size)
{
  struct buf *link;
  unsigned int link_idx = 0;
  size_t link_len;
  size_t rewind;
  if ((!rndr->cb.autolink) || rndr->in_link_body)
  {
    return 0;
  }
  link_idx = rndr_newbuf(rndr, 1);
  if ((link_len = sd_autolink__email(&rewind, link, data, max_rewind, size, 0)) > 0)
  {
    buftruncate(ob, ob->size - rewind);
    rndr->cb.autolink(ob, link, MKDA_EMAIL, rndr->opaque);
  }
  rndr_popbuf(rndr, 1);
  return link_len;
}

static size_t char_autolink_url(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size)
{
  struct buf *link;
  unsigned int link_idx = 0;
  size_t link_len;
  size_t rewind;
  if ((!rndr->cb.autolink) || rndr->in_link_body)
  {
    return 0;
  }
  link_idx = rndr_newbuf(rndr, 1);
  if ((link_len = sd_autolink__url(&rewind, link, data, max_rewind, size, 0)) > 0)
  {
    buftruncate(ob, ob->size - rewind);
    rndr->cb.autolink(ob, link, MKDA_NORMAL, rndr->opaque);
  }
  rndr_popbuf(rndr, 1);
  return link_len;
}

static size_t char_link(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size)
{
  int is_img = max_rewind && (data[-1] == '!');
  int level;
  size_t i = 1;
  size_t txt_e;
  size_t link_b = 0;
  size_t link_e = 0;
  size_t title_b = 0;
  size_t title_e = 0;
  struct buf *content = 0;
  unsigned int content_idx = 0;
  struct buf *link = 0;
  unsigned int link_idx = 0;
  struct buf *title = 0;
  unsigned int title_idx = 0;
  struct buf *u_link = 0;
  unsigned int u_link_idx = 0;
  size_t org_work_size = rndr->work_bufs[1].size;
  int text_has_nl = 0;
  int ret = 0;
  int in_title = 0;
  int qtype = 0;
  if ((is_img && (!rndr->cb.image)) || ((!is_img) && (!rndr->cb.link)))
  {
    goto cleanup;
  }
  for (level = 1; i < size; i += 1)
  {
    if (data[i] == '\n')
    {
      text_has_nl = 1;
    }
    else
      if (data[i - 1] == '\\')
    {
      continue;
    }
    else
      if (data[i] == '[')
    {
      level += 1;
    }
    else
      if (data[i] == ']')
    {
      level -= 1;
      if (level <= 0)
      {
        break;
      }
    }
  }

  if (i >= size)
  {
    goto cleanup;
  }
  txt_e = i;
  i += 1;
  while ((i < size) && _isspace(data[i]))
  {
    i += 1;
  }

  if ((i < size) && (data[i] == '('))
  {
    i += 1;
    while ((i < size) && _isspace(data[i]))
    {
      i += 1;
    }

    link_b = i;
    while (i < size)
    {
      if (data[i] == '\\')
      {
        i += 2;
      }
      else
        if (data[i] == ')')
      {
        break;
      }
      else
        if (((i >= 1) && _isspace(data[i - 1])) && ((data[i] == '\'') || (data[i] == '"')))
      {
        break;
      }
      else
        i++;
      i += 1;
    }

    if (i >= size)
    {
      goto cleanup;
    }
    link_e = i;
    if ((data[i] == '\'') || (data[i] == '"'))
    {
      qtype = data[i];
      in_title = 1;
      i += 1;
      title_b = i;
      while (i < size)
      {
        if (data[i] == '\\')
        {
          i += 2;
        }
        else
          if (data[i] == qtype)
        {
          in_title = 0;
          i += 1;
        }
        else
          if ((data[i] == ')') && (!in_title))
        {
          break;
        }
        else
          i++;
        i += 1;
      }

      if (i >= size)
      {
        goto cleanup;
      }
      title_e = i - 1;
      while ((title_e > title_b) && _isspace(data[title_e]))
      {
        title_e -= 1;
      }

      if ((data[title_e] != '\'') && (data[title_e] != '"'))
      {
        title_b = (title_e = 0);
        link_e = i;
      }
    }
    while ((link_e > link_b) && _isspace(data[link_e - 1]))
    {
      link_e -= 1;
    }

    if (data[link_b] == '<')
    {
      link_b += 1;
    }
    if (data[link_e - 1] == '>')
    {
      link_e -= 1;
    }
    if (link_e > link_b)
    {
      link_idx = rndr_newbuf(rndr, 1);
      bufput(link, data + link_b, link_e - link_b);
    }
    if (title_e > title_b)
    {
      title_idx = rndr_newbuf(rndr, 1);
      bufput(title, data + title_b, title_e - title_b);
    }
    i += 1;
  }
  else
    if ((i < size) && (data[i] == '['))
  {
    struct buf id = {0, 0, 0, 0};
    struct link_ref *lr;
    unsigned int lr_idx = 0;
    i += 1;
    link_b = i;
    while ((i < size) && (data[i] != ']'))
    {
      i += 1;
    }

    if (i >= size)
    {
      goto cleanup;
    }
    link_e = i;
    if (link_b == link_e)
    {
      if (text_has_nl)
      {
        struct buf *b = rndr_newbuf(rndr, 1);
        size_t j;
        for (j = 1; j < txt_e; j += 1)
        {
          if (data[j] != '\n')
          {
            bufputc(b, data[j]);
          }
          else
            if (data[j - 1] != ' ')
          {
            bufputc(b, ' ');
          }
        }

        id.data = b->data;
        id.size = b->size;
      }
      else
      {
        id.data = data + 1;
        id.size = txt_e - 1;
      }
    }
    else
    {
      id.data = data + link_b;
      id.size = link_e - link_b;
    }
    lr_idx = find_link_ref(rndr->refs, id.data, id.size);
    if (!(&lr[lr_idx]))
    {
      goto cleanup;
    }
    link_idx = lr->link_idx;
    title_idx = lr->title_idx;
    i += 1;
  }
  else
  {
    struct buf id = {0, 0, 0, 0};
    struct link_ref *lr;
    unsigned int lr_idx = 0;
    if (text_has_nl)
    {
      struct buf *b = rndr_newbuf(rndr, 1);
      size_t j;
      for (j = 1; j < txt_e; j += 1)
      {
        if (data[j] != '\n')
        {
          bufputc(b, data[j]);
        }
        else
          if (data[j - 1] != ' ')
        {
          bufputc(b, ' ');
        }
      }

      id.data = b->data;
      id.size = b->size;
    }
    else
    {
      id.data = data + 1;
      id.size = txt_e - 1;
    }
    lr_idx = find_link_ref(rndr->refs, id.data, id.size);
    if (!(&lr[lr_idx]))
    {
      goto cleanup;
    }
    link_idx = lr->link_idx;
    title_idx = lr->title_idx;
    i = txt_e + 1;
  }
  if (txt_e > 1)
  {
    content_idx = rndr_newbuf(rndr, 1);
    if (is_img)
    {
      bufput(content, data + 1, txt_e - 1);
    }
    else
    {
      rndr->in_link_body = 1;
      parse_inline(content, rndr, data + 1, txt_e - 1);
      rndr->in_link_body = 0;
    }
  }
  if (link)
  {
    u_link_idx = rndr_newbuf(rndr, 1);
    unscape_text(u_link, link);
  }
  else
  {
    goto cleanup;
  }
  if (is_img)
  {
    if (ob->size && (ob->data[ob->size - 1] == '!'))
    {
      ob->size -= 1;
    }
    ret = rndr->cb.image(ob, u_link, title, content, rndr->opaque);
  }
  else
  {
    ret = rndr->cb.link(ob, u_link, title, content, rndr->opaque);
  }
  cleanup:
  rndr->work_bufs[1].size = (int) org_work_size;

  return (ret) ? (i) : (0);
}

static size_t char_superscript(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size)
{
  size_t sup_start;
  size_t sup_len;
  struct buf *sup;
  unsigned int sup_idx = 0;
  if (!rndr->cb.superscript)
  {
    return 0;
  }
  if (size < 2)
  {
    return 0;
  }
  if (data[1] == '(')
  {
    sup_start = (sup_len = 2);
    while (((sup_len < size) && (data[sup_len] != ')')) && (data[sup_len - 1] != '\\'))
    {
      sup_len += 1;
    }

    if (sup_len == size)
    {
      return 0;
    }
  }
  else
  {
    sup_start = (sup_len = 1);
    while ((sup_len < size) && (!_isspace(data[sup_len])))
    {
      sup_len += 1;
    }

  }
  if ((sup_len - sup_start) == 0)
  {
    return (sup_start == 2) ? (3) : (0);
  }
  sup_idx = rndr_newbuf(rndr, 1);
  parse_inline(sup, rndr, data + sup_start, sup_len - sup_start);
  rndr->cb.superscript(ob, sup, rndr->opaque);
  rndr_popbuf(rndr, 1);
  return (sup_start == 2) ? (sup_len + 1) : (sup_len);
}

static size_t is_empty(uint8_t *data, size_t size)
{
  size_t i;
  for (i = 0; (i < size) && (data[i] != '\n'); i += 1)
  {
    if (data[i] != ' ')
    {
      return 0;
    }
  }

  return i + 1;
}

static int is_hrule(uint8_t *data, size_t size)
{
  size_t i = 0;
  size_t n = 0;
  uint8_t c;
  if (size < 3)
  {
    return 0;
  }
  if (data[0] == ' ')
  {
    i += 1;
    if (data[1] == ' ')
    {
      i += 1;
      if (data[2] == ' ')
      {
        i += 1;
      }
    }
  }
  if (((i + 2) >= size) || (((data[i] != '*') && (data[i] != '-')) && (data[i] != '_')))
  {
    return 0;
  }
  c = data[i];
  while ((i < size) && (data[i] != '\n'))
  {
    if (data[i] == c)
    {
      n += 1;
    }
    else
      if (data[i] != ' ')
    {
      return 0;
    }
    i += 1;
  }

  return n >= 3;
}

static size_t prefix_codefence(uint8_t *data, size_t size)
{
  size_t i = 0;
  size_t n = 0;
  uint8_t c;
  if (size < 3)
  {
    return 0;
  }
  if (data[0] == ' ')
  {
    i += 1;
    if (data[1] == ' ')
    {
      i += 1;
      if (data[2] == ' ')
      {
        i += 1;
      }
    }
  }
  if (((i + 2) >= size) || (!((data[i] == '~') || (data[i] == '`'))))
  {
    return 0;
  }
  c = data[i];
  while ((i < size) && (data[i] == c))
  {
    n += 1;
    i += 1;
  }

  if (n < 3)
  {
    return 0;
  }
  return i;
}

static size_t is_codefence(uint8_t *data, size_t size, struct buf *syntax)
{
  size_t i = 0;
  size_t syn_len = 0;
  uint8_t *syn_start;
  unsigned int syn_start_idx = 0;
  i = prefix_codefence(data, size);
  if (i == 0)
  {
    return 0;
  }
  while ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }

  syn_start_idx = data + i;
  if ((i < size) && (data[i] == '{'))
  {
    i += 1;
    syn_start_idx += 1;
    while (((i < size) && (data[i] != '}')) && (data[i] != '\n'))
    {
      syn_len += 1;
      i += 1;
    }

    if ((i == size) || (data[i] != '}'))
    {
      return 0;
    }
    while ((syn_len > 0) && _isspace(syn_start[0 + syn_start_idx]))
    {
      syn_start_idx += 1;
      syn_len -= 1;
    }

    while ((syn_len > 0) && _isspace(syn_start[(syn_len - 1) + syn_start_idx]))
    {
      syn_len -= 1;
    }

    i += 1;
  }
  else
  {
    while ((i < size) && (!_isspace(data[i])))
    {
      syn_len += 1;
      i += 1;
    }

  }
  if (syntax)
  {
    syntax->data = &syn_start[syn_start_idx];
    syntax->size = syn_len;
  }
  while ((i < size) && (data[i] != '\n'))
  {
    if (!_isspace(data[i]))
    {
      return 0;
    }
    i += 1;
  }

  return i + 1;
}

static int is_atxheader(struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  if (data[0] != '#')
  {
    return 0;
  }
  if (rndr->ext_flags & MKDEXT_SPACE_HEADERS)
  {
    size_t level = 0;
    while (((level < size) && (level < 6)) && (data[level] == '#'))
    {
      level += 1;
    }

    if ((level < size) && (data[level] != ' '))
    {
      return 0;
    }
  }
  return 1;
}

static int is_headerline(uint8_t *data, size_t size)
{
  size_t i = 0;
  if (data[i] == '=')
  {
    for (i = 1; (i < size) && (data[i] == '='); i += 1)
    {
      ;
    }

    while ((i < size) && (data[i] == ' '))
    {
      i += 1;
    }

    return ((i >= size) || (data[i] == '\n')) ? (1) : (0);
  }
  if (data[i] == '-')
  {
    for (i = 1; (i < size) && (data[i] == '-'); i += 1)
    {
      ;
    }

    while ((i < size) && (data[i] == ' '))
    {
      i += 1;
    }

    return ((i >= size) || (data[i] == '\n')) ? (2) : (0);
  }
  return 0;
}

static int is_next_headerline(uint8_t *data, size_t size)
{
  size_t i = 0;
  while ((i < size) && (data[i] != '\n'))
  {
    i += 1;
  }

  if ((++i) >= size)
  {
    return 0;
  }
  return is_headerline(data + i, size - i);
}

static size_t prefix_quote(uint8_t *data, size_t size)
{
  size_t i = 0;
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if (((i < size) && (data[i] == '>')) && (((i + 1) < size) && (data[i + 1] != '!')))
  {
    if (((i + 1) < size) && (data[i + 1] == ' '))
    {
      return i + 2;
    }
    return i + 1;
  }
  return 0;
}

static size_t prefix_blockspoiler(uint8_t *data, size_t size)
{
  size_t i = 0;
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((((i + 1) < size) && (data[i] == '>')) && (data[i + 1] == '!'))
  {
    size_t spoilerspan = find_emph_char((data + i) + 1, (size - i) - 1, '<');
    if ((((i + spoilerspan) < size) && (spoilerspan > 0)) && (data[i + spoilerspan] == '!'))
    {
      return 0;
    }
    if (((i + 2) < size) && (data[i + 2] == ' '))
    {
      return i + 3;
    }
    return i + 2;
  }
  return 0;
}

static size_t prefix_code(uint8_t *data, size_t size)
{
  if (((((size > 3) && (data[0] == ' ')) && (data[1] == ' ')) && (data[2] == ' ')) && (data[3] == ' '))
  {
    return 4;
  }
  return 0;
}

static size_t prefix_oli(uint8_t *data, size_t size)
{
  size_t i = 0;
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if (((i >= size) || (data[i] < '0')) || (data[i] > '9'))
  {
    return 0;
  }
  while (((i < size) && (data[i] >= '0')) && (data[i] <= '9'))
  {
    i += 1;
  }

  if ((((i + 1) >= size) || (data[i] != '.')) || (data[i + 1] != ' '))
  {
    return 0;
  }
  if (is_next_headerline(data + i, size - i))
  {
    return 0;
  }
  return i + 2;
}

static size_t prefix_uli(uint8_t *data, size_t size)
{
  size_t i = 0;
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((i < size) && (data[i] == ' '))
  {
    i += 1;
  }
  if ((((i + 1) >= size) || (((data[i] != '*') && (data[i] != '+')) && (data[i] != '-'))) || (data[i + 1] != ' '))
  {
    return 0;
  }
  if (is_next_headerline(data + i, size - i))
  {
    return 0;
  }
  return i + 2;
}

static void parse_block(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size);
static size_t parse_blockquote(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  size_t beg;
  size_t end = 0;
  size_t pre;
  size_t work_size = 0;
  uint8_t *work_data = 0;
  unsigned int work_data_idx = 0;
  struct buf *out = 0;
  unsigned int out_idx = 0;
  out_idx = rndr_newbuf(rndr, 0);
  beg = 0;
  while (beg < size)
  {
    for (end = beg + 1; (end < size) && (data[end - 1] != '\n'); end += 1)
    {
      ;
    }

    pre = prefix_quote(data + beg, end - beg);
    if (pre)
    {
      beg += pre;
    }
    else
      if (is_empty(data + beg, end - beg) && ((end >= size) || ((prefix_quote(data + end, size - end) == 0) && (!is_empty(data + end, size - end)))))
    {
      break;
    }
    if (beg < end)
    {
      if (!(&work_data[work_data_idx]))
      {
        work_data_idx = data + beg;
      }
      else
        if ((data + beg) != ((&work_data[work_data_idx]) + work_size))
      {
        memmove((&work_data[work_data_idx]) + work_size, data + beg, end - beg);
      }
      work_size += end - beg;
    }
    beg = end;
  }

  parse_block(out, rndr, work_data, work_size);
  if (rndr->cb.blockquote)
  {
    rndr->cb.blockquote(ob, out, rndr->opaque);
  }
  rndr_popbuf(rndr, 0);
  return end;
}

static size_t parse_blockspoiler(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  size_t beg;
  size_t end = 0;
  size_t pre;
  size_t work_size = 0;
  uint8_t *work_data = 0;
  unsigned int work_data_idx = 0;
  struct buf *out = 0;
  unsigned int out_idx = 0;
  out_idx = rndr_newbuf(rndr, 0);
  beg = 0;
  while (beg < size)
  {
    for (end = beg + 1; (end < size) && (data[end - 1] != '\n'); end += 1)
    {
      ;
    }

    pre = prefix_blockspoiler(data + beg, end - beg);
    if (pre)
    {
      beg += pre;
    }
    else
      if (is_empty(data + beg, end - beg) && ((end >= size) || ((prefix_blockspoiler(data + end, size - end) == 0) && (!is_empty(data + end, size - end)))))
    {
      break;
    }
    if (beg < end)
    {
      if (!(&work_data[work_data_idx]))
      {
        work_data_idx = data + beg;
      }
      else
        if ((data + beg) != ((&work_data[work_data_idx]) + work_size))
      {
        memmove((&work_data[work_data_idx]) + work_size, data + beg, end - beg);
      }
      work_size += end - beg;
    }
    beg = end;
  }

  parse_block(out, rndr, work_data, work_size);
  if (rndr->cb.blockspoiler)
  {
    rndr->cb.blockspoiler(ob, out, rndr->opaque);
  }
  rndr_popbuf(rndr, 0);
  return end;
}

static size_t parse_htmlblock(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size, int do_render);
static size_t parse_paragraph(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  size_t i = 0;
  size_t end = 0;
  int level = 0;
  struct buf work = {data, 0, 0, 0};
  while (i < size)
  {
    for (end = i + 1; (end < size) && (data[end - 1] != '\n'); end += 1)
    {
      ;
    }

    if (prefix_quote(data + i, end - i) != 0)
    {
      end = i;
      break;
    }
    if (is_empty(data + i, size - i))
    {
      break;
    }
    if ((level = is_headerline(data + i, size - i)) != 0)
    {
      break;
    }
    if ((is_atxheader(rndr, data + i, size - i) || is_hrule(data + i, size - i)) || prefix_quote(data + i, size - i))
    {
      end = i;
      break;
    }
    if ((rndr->ext_flags & MKDEXT_LAX_SPACING) && (!isalnum(data[i])))
    {
      if (prefix_oli(data + i, size - i) || prefix_uli(data + i, size - i))
      {
        end = i;
        break;
      }
      if (((data[i] == '<') && rndr->cb.blockhtml) && parse_htmlblock(ob, rndr, data + i, size - i, 0))
      {
        end = i;
        break;
      }
      if (((rndr->ext_flags & MKDEXT_FENCED_CODE) != 0) && (is_codefence(data + i, size - i, 0) != 0))
      {
        end = i;
        break;
      }
    }
    i = end;
  }

  work.size = i;
  while (work.size && (data[work.size - 1] == '\n'))
  {
    work.size -= 1;
  }

  if (!level)
  {
    struct buf *tmp = rndr_newbuf(rndr, 0);
    parse_inline(tmp, rndr, work.data, work.size);
    if (rndr->cb.paragraph)
    {
      rndr->cb.paragraph(ob, tmp, rndr->opaque);
    }
    rndr_popbuf(rndr, 0);
  }
  else
  {
    struct buf *header_work;
    unsigned int header_work_idx = 0;
    if (work.size)
    {
      size_t beg;
      i = work.size;
      work.size -= 1;
      while (work.size && (data[work.size] != '\n'))
      {
        work.size -= 1;
      }

      beg = work.size + 1;
      while (work.size && (data[work.size - 1] == '\n'))
      {
        work.size -= 1;
      }

      if (work.size > 0)
      {
        struct buf *tmp = rndr_newbuf(rndr, 0);
        parse_inline(tmp, rndr, work.data, work.size);
        if (rndr->cb.paragraph)
        {
          rndr->cb.paragraph(ob, tmp, rndr->opaque);
        }
        rndr_popbuf(rndr, 0);
        work.data += beg;
        work.size = i - beg;
      }
      else
        work.size = i;
    }
    header_work_idx = rndr_newbuf(rndr, 1);
    parse_inline(header_work, rndr, work.data, work.size);
    if (rndr->cb.header)
    {
      rndr->cb.header(ob, header_work, (int) level, rndr->opaque);
    }
    rndr_popbuf(rndr, 1);
  }
  return end;
}

static size_t parse_fencedcode(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  size_t beg;
  size_t end;
  struct buf *work = 0;
  unsigned int work_idx = 0;
  struct buf lang = {0, 0, 0, 0};
  beg = is_codefence(data, size, &lang);
  if (beg == 0)
  {
    return 0;
  }
  work_idx = rndr_newbuf(rndr, 0);
  while (beg < size)
  {
    size_t fence_end;
    struct buf fence_trail = {0, 0, 0, 0};
    fence_end = is_codefence(data + beg, size - beg, &fence_trail);
    if ((fence_end != 0) && (fence_trail.size == 0))
    {
      beg += fence_end;
      break;
    }
    for (end = beg + 1; (end < size) && (data[end - 1] != '\n'); end += 1)
    {
      ;
    }

    if (beg < end)
    {
      if (is_empty(data + beg, end - beg))
      {
        bufputc(work, '\n');
      }
      else
        bufput(work, data + beg, end - beg);
    }
    beg = end;
  }

  if (work->size && (work->data[work->size - 1] != '\n'))
  {
    bufputc(work, '\n');
  }
  if (rndr->cb.blockcode)
  {
    rndr->cb.blockcode(ob, work, (lang.size) ? (&lang) : (0), rndr->opaque);
  }
  rndr_popbuf(rndr, 0);
  return beg;
}

static size_t parse_blockcode(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  size_t beg;
  size_t end;
  size_t pre;
  struct buf *work = 0;
  unsigned int work_idx = 0;
  work_idx = rndr_newbuf(rndr, 0);
  beg = 0;
  while (beg < size)
  {
    for (end = beg + 1; (end < size) && (data[end - 1] != '\n'); end += 1)
    {
    }

    ;
    pre = prefix_code(data + beg, end - beg);
    if (pre)
    {
      beg += pre;
    }
    else
      if (!is_empty(data + beg, end - beg))
    {
      break;
    }
    if (beg < end)
    {
      if (is_empty(data + beg, end - beg))
      {
        bufputc(work, '\n');
      }
      else
        bufput(work, data + beg, end - beg);
    }
    beg = end;
  }

  while (work->size && (work->data[work->size - 1] == '\n'))
  {
    work->size -= 1;
  }

  bufputc(work, '\n');
  if (rndr->cb.blockcode)
  {
    rndr->cb.blockcode(ob, work, 0, rndr->opaque);
  }
  rndr_popbuf(rndr, 0);
  return beg;
}

static size_t parse_listitem(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size, int *flags)
{
  struct buf *work = 0;
  unsigned int work_idx = 0;
  struct buf *inter = 0;
  unsigned int inter_idx = 0;
  size_t beg = 0;
  size_t end;
  size_t pre;
  size_t sublist = 0;
  size_t orgpre = 0;
  size_t i;
  int in_empty = 0;
  int has_inside_empty = 0;
  int in_fence = 0;
  while (((orgpre < 3) && (orgpre < size)) && (data[orgpre] == ' '))
  {
    orgpre += 1;
  }

  beg = prefix_uli(data, size);
  if (!beg)
  {
    beg = prefix_oli(data, size);
  }
  if (!beg)
  {
    return 0;
  }
  end = beg;
  while ((end < size) && (data[end - 1] != '\n'))
  {
    end += 1;
  }

  work_idx = rndr_newbuf(rndr, 1);
  inter_idx = rndr_newbuf(rndr, 1);
  bufput(work, data + beg, end - beg);
  beg = end;
  while (beg < size)
  {
    size_t has_next_uli = 0;
    size_t has_next_oli = 0;
    end += 1;
    while ((end < size) && (data[end - 1] != '\n'))
    {
      end += 1;
    }

    if (is_empty(data + beg, end - beg))
    {
      in_empty = 1;
      beg = end;
      continue;
    }
    i = 0;
    while (((i < 4) && ((beg + i) < end)) && (data[beg + i] == ' '))
    {
      i += 1;
    }

    pre = i;
    if (rndr->ext_flags & MKDEXT_FENCED_CODE)
    {
      if (is_codefence((data + beg) + i, (end - beg) - i, 0) != 0)
      {
        in_fence = !in_fence;
      }
    }
    if (!in_fence)
    {
      has_next_uli = prefix_uli((data + beg) + i, (end - beg) - i);
      has_next_oli = prefix_oli((data + beg) + i, (end - beg) - i);
    }
    if (in_empty && ((((*flags) & 1) && has_next_uli) || ((!((*flags) & 1)) && has_next_oli)))
    {
      *flags |= 8;
      break;
    }
    if ((has_next_uli && (!is_hrule((data + beg) + i, (end - beg) - i))) || has_next_oli)
    {
      if (in_empty)
      {
        has_inside_empty = 1;
      }
      if (pre == orgpre)
      {
        break;
      }
      if (!sublist)
      {
        sublist = work->size;
      }
    }
    else
      if (in_empty && (pre == 0))
    {
      *flags |= 8;
      break;
    }
    else
      if (in_empty)
    {
      bufputc(work, '\n');
      has_inside_empty = 1;
    }
    in_empty = 0;
    bufput(work, (data + beg) + i, (end - beg) - i);
    beg = end;
  }

  if (has_inside_empty)
  {
    *flags |= 2;
  }
  if ((*flags) & 2)
  {
    if (sublist && (sublist < work->size))
    {
      parse_block(inter, rndr, work->data, sublist);
      parse_block(inter, rndr, work->data + sublist, work->size - sublist);
    }
    else
      parse_block(inter, rndr, work->data, work->size);
  }
  else
  {
    if (sublist && (sublist < work->size))
    {
      parse_inline(inter, rndr, work->data, sublist);
      parse_block(inter, rndr, work->data + sublist, work->size - sublist);
    }
    else
      parse_inline(inter, rndr, work->data, work->size);
  }
  if (rndr->cb.listitem)
  {
    rndr->cb.listitem(ob, inter, *flags, rndr->opaque);
  }
  rndr_popbuf(rndr, 1);
  rndr_popbuf(rndr, 1);
  return beg;
}

static size_t parse_list(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size, int flags)
{
  struct buf *work = 0;
  unsigned int work_idx = 0;
  size_t i = 0;
  size_t j;
  work_idx = rndr_newbuf(rndr, 0);
  while (i < size)
  {
    j = parse_listitem(work, rndr, data + i, size - i, &flags);
    i += j;
    if ((!j) || (flags & 8))
    {
      break;
    }
  }

  if (rndr->cb.list)
  {
    rndr->cb.list(ob, work, flags, rndr->opaque);
  }
  rndr_popbuf(rndr, 0);
  return i;
}

static size_t parse_atxheader(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  size_t level = 0;
  size_t i;
  size_t end;
  size_t skip;
  while (((level < size) && (level < 6)) && (data[level] == '#'))
  {
    level += 1;
  }

  for (i = level; (i < size) && (data[i] == ' '); i += 1)
  {
    ;
  }

  for (end = i; (end < size) && (data[end] != '\n'); end += 1)
  {
    ;
  }

  skip = end;
  while (end && (data[end - 1] == '#'))
  {
    end -= 1;
  }

  while (end && (data[end - 1] == ' '))
  {
    end -= 1;
  }

  if (end > i)
  {
    struct buf *work = rndr_newbuf(rndr, 1);
    parse_inline(work, rndr, data + i, end - i);
    if (rndr->cb.header)
    {
      rndr->cb.header(ob, work, (int) level, rndr->opaque);
    }
    rndr_popbuf(rndr, 1);
  }
  return skip;
}

static size_t htmlblock_end_tag(const char *tag, size_t tag_len, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  size_t i;
  size_t w;
  if ((((tag_len + 3) >= size) || (strncasecmp(((char *) data) + 2, tag, tag_len) != 0)) || (data[tag_len + 2] != '>'))
  {
    return 0;
  }
  i = tag_len + 3;
  w = 0;
  if ((i < size) && ((w = is_empty(data + i, size - i)) == 0))
  {
    return 0;
  }
  i += w;
  w = 0;
  if (i < size)
  {
    w = is_empty(data + i, size - i);
  }
  return i + w;
}

static size_t htmlblock_end(const char *curtag, struct sd_markdown *rndr, uint8_t *data, size_t size, int start_of_line)
{
  size_t tag_size = strlen(curtag);
  size_t i = 1;
  size_t end_tag;
  int block_lines = 0;
  while (i < size)
  {
    i += 1;
    while ((i < size) && (!((data[i - 1] == '<') && (data[i] == '/'))))
    {
      if (data[i] == '\n')
      {
        block_lines += 1;
      }
      i += 1;
    }

    if ((start_of_line && (block_lines > 0)) && (data[i - 2] != '\n'))
    {
      continue;
    }
    if (((i + 2) + tag_size) >= size)
    {
      break;
    }
    end_tag = htmlblock_end_tag(curtag, tag_size, rndr, (data + i) - 1, (size - i) + 1);
    if (end_tag)
    {
      return (i + end_tag) - 1;
    }
  }

  return 0;
}

static size_t parse_htmlblock(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size, int do_render)
{
  size_t i;
  size_t j = 0;
  size_t tag_end;
  const char *curtag = 0;
  unsigned int curtag_idx = 0;
  struct buf work = {data, 0, 0, 0};
  if ((size < 2) || (data[0] != '<'))
  {
    return 0;
  }
  i = 1;
  while (((i < size) && (data[i] != '>')) && (data[i] != ' '))
  {
    i += 1;
  }

  if (i < size)
  {
    curtag_idx = find_block_tag(((char *) data) + 1, ((int) i) - 1);
  }
  if (!(&curtag[curtag_idx]))
  {
    if ((((size > 5) && (data[1] == '!')) && (data[2] == '-')) && (data[3] == '-'))
    {
      i = 5;
      while ((i < size) && (!(((data[i - 2] == '-') && (data[i - 1] == '-')) && (data[i] == '>'))))
      {
        i += 1;
      }

      i += 1;
      if (i < size)
      {
        j = is_empty(data + i, size - i);
      }
      if (j)
      {
        work.size = i + j;
        if (do_render && rndr->cb.blockhtml)
        {
          rndr->cb.blockhtml(ob, &work, rndr->opaque);
        }
        return work.size;
      }
    }
    if (((size > 4) && ((data[1] == 'h') || (data[1] == 'H'))) && ((data[2] == 'r') || (data[2] == 'R')))
    {
      i = 3;
      while ((i < size) && (data[i] != '>'))
      {
        i += 1;
      }

      if ((i + 1) < size)
      {
        i += 1;
        j = is_empty(data + i, size - i);
        if (j)
        {
          work.size = i + j;
          if (do_render && rndr->cb.blockhtml)
          {
            rndr->cb.blockhtml(ob, &work, rndr->opaque);
          }
          return work.size;
        }
      }
    }
    return 0;
  }
  tag_end = htmlblock_end(curtag, rndr, data, size, 1);
  if (((!tag_end) && (strcmp(curtag, "ins") != 0)) && (strcmp(curtag, "del") != 0))
  {
    tag_end = htmlblock_end(curtag, rndr, data, size, 0);
  }
  if (!tag_end)
  {
    return 0;
  }
  work.size = tag_end;
  if (do_render && rndr->cb.blockhtml)
  {
    rndr->cb.blockhtml(ob, &work, rndr->opaque);
  }
  return tag_end;
}

static void parse_table_row(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size, size_t columns, int *col_data, int header_flag)
{
  size_t i = 0;
  size_t col;
  size_t cols_left;
  struct buf *row_work = 0;
  unsigned int row_work_idx = 0;
  if ((!rndr->cb.table_cell) || (!rndr->cb.table_row))
  {
    return;
  }
  row_work_idx = rndr_newbuf(rndr, 1);
  if ((i < size) && (data[i] == '|'))
  {
    i += 1;
  }
  for (col = 0; (col < columns) && (i < size); col += 1)
  {
    size_t cell_start;
    size_t cell_end;
    struct buf *cell_work;
    unsigned int cell_work_idx = 0;
    cell_work_idx = rndr_newbuf(rndr, 1);
    while ((i < size) && _isspace(data[i]))
    {
      i += 1;
    }

    cell_start = i;
    while ((i < size) && (data[i] != '|'))
    {
      i += 1;
    }

    cell_end = i - 1;
    while ((cell_end > cell_start) && _isspace(data[cell_end]))
    {
      cell_end -= 1;
    }

    parse_inline(cell_work, rndr, data + cell_start, (1 + cell_end) - cell_start);
    rndr->cb.table_cell(row_work, cell_work, col_data[col] | header_flag, rndr->opaque, 0);
    rndr_popbuf(rndr, 1);
    i += 1;
  }

  cols_left = columns - col;
  if (cols_left > 0)
  {
    struct buf empty_cell = {0, 0, 0, 0};
    rndr->cb.table_cell(row_work, &empty_cell, col_data[col] | header_flag, rndr->opaque, cols_left);
  }
  rndr->cb.table_row(ob, row_work, rndr->opaque);
  rndr_popbuf(rndr, 1);
}

static size_t parse_table_header(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size, size_t *columns, int **column_data)
{
  int pipes;
  size_t i = 0;
  size_t col;
  size_t header_end;
  size_t under_end;
  pipes = 0;
  while ((i < size) && (data[i] != '\n'))
  {
    if (data[i++] == '|')
    {
      pipes += 1;
    }
  }

  if ((i == size) || (pipes == 0))
  {
    return 0;
  }
  header_end = i;
  while ((header_end > 0) && _isspace(data[header_end - 1]))
  {
    header_end -= 1;
  }

  if (data[0] == '|')
  {
    pipes -= 1;
  }
  if (header_end && (data[header_end - 1] == '|'))
  {
    pipes -= 1;
  }
  if ((pipes + 1) > rndr->max_table_cols)
  {
    return 0;
  }
  *columns = pipes + 1;
  *column_data = calloc(*columns, sizeof(int));
  i += 1;
  if ((i < size) && (data[i] == '|'))
  {
    i += 1;
  }
  under_end = i;
  while ((under_end < size) && (data[under_end] != '\n'))
  {
    under_end += 1;
  }

  for (col = 0; (col < (*columns)) && (i < under_end); col += 1)
  {
    size_t dashes = 0;
    while ((i < under_end) && (data[i] == ' '))
    {
      i += 1;
    }

    if (data[i] == ':')
    {
      i += 1;
      (*column_data)[col] |= MKD_TABLE_ALIGN_L;
      dashes += 1;
    }
    while ((i < under_end) && (data[i] == '-'))
    {
      i += 1;
      dashes += 1;
    }

    if ((i < under_end) && (data[i] == ':'))
    {
      i += 1;
      (*column_data)[col] |= MKD_TABLE_ALIGN_R;
      dashes += 1;
    }
    while ((i < under_end) && (data[i] == ' '))
    {
      i += 1;
    }

    if ((i < under_end) && (data[i] != '|'))
    {
      break;
    }
    if (dashes < 1)
    {
      break;
    }
    i += 1;
  }

  if (col < (*columns))
  {
    return 0;
  }
  parse_table_row(ob, rndr, data, header_end, *columns, *column_data, MKD_TABLE_HEADER);
  return under_end + 1;
}

static size_t parse_table(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  size_t i;
  struct buf *header_work = 0;
  unsigned int header_work_idx = 0;
  struct buf *body_work = 0;
  unsigned int body_work_idx = 0;
  size_t columns;
  int *col_data = 0;
  header_work_idx = rndr_newbuf(rndr, 1);
  body_work_idx = rndr_newbuf(rndr, 0);
  i = parse_table_header(header_work, rndr, data, size, &columns, &col_data);
  if (i > 0)
  {
    while (i < size)
    {
      size_t row_start;
      int pipes = 0;
      row_start = i;
      while ((i < size) && (data[i] != '\n'))
      {
        if (data[i++] == '|')
        {
          pipes += 1;
        }
      }

      if ((pipes == 0) || (i == size))
      {
        i = row_start;
        break;
      }
      parse_table_row(body_work, rndr, data + row_start, i - row_start, columns, col_data, 0);
      i += 1;
    }

    if (rndr->cb.table)
    {
      rndr->cb.table(ob, header_work, body_work, rndr->opaque);
    }
  }
  free(col_data);
  rndr_popbuf(rndr, 1);
  rndr_popbuf(rndr, 0);
  return i;
}

static void parse_block(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t size)
{
  size_t beg;
  size_t end;
  size_t i;
  uint8_t *txt_data;
  unsigned int txt_data_idx = 0;
  beg = 0;
  if ((rndr->work_bufs[1].size + rndr->work_bufs[0].size) > rndr->max_nesting)
  {
    return;
  }
  while (beg < size)
  {
    txt_data_idx = data + beg;
    end = size - beg;
    if (is_atxheader(rndr, txt_data, end))
    {
      beg += parse_atxheader(ob, rndr, txt_data, end);
    }
    else
      if (((data[beg] == '<') && rndr->cb.blockhtml) && ((i = parse_htmlblock(ob, rndr, txt_data, end, 1)) != 0))
    {
      beg += i;
    }
    else
      if ((i = is_empty(txt_data, end)) != 0)
    {
      beg += i;
    }
    else
      if (is_hrule(txt_data, end))
    {
      if (rndr->cb.hrule)
      {
        rndr->cb.hrule(ob, rndr->opaque);
      }
      while ((beg < size) && (data[beg] != '\n'))
      {
        beg += 1;
      }

      beg += 1;
    }
    else
      if (((rndr->ext_flags & MKDEXT_FENCED_CODE) != 0) && ((i = parse_fencedcode(ob, rndr, txt_data, end)) != 0))
    {
      beg += i;
    }
    else
      if (((rndr->ext_flags & MKDEXT_TABLES) != 0) && ((i = parse_table(ob, rndr, txt_data, end)) != 0))
    {
      beg += i;
    }
    else
      if (prefix_quote(txt_data, end))
    {
      beg += parse_blockquote(ob, rndr, txt_data, end);
    }
    else
      if (prefix_blockspoiler(txt_data, end))
    {
      beg += parse_blockspoiler(ob, rndr, txt_data, end);
    }
    else
      if (prefix_code(txt_data, end))
    {
      beg += parse_blockcode(ob, rndr, txt_data, end);
    }
    else
      if (prefix_uli(txt_data, end))
    {
      beg += parse_list(ob, rndr, txt_data, end, 0);
    }
    else
      if (prefix_oli(txt_data, end))
    {
      beg += parse_list(ob, rndr, txt_data, end, 1);
    }
    else
      beg += parse_paragraph(ob, rndr, txt_data, end);
  }

}

static int is_ref(const uint8_t *data, size_t beg, size_t end, size_t *last, struct link_ref **refs)
{
  size_t i = 0;
  size_t id_offset;
  size_t id_end;
  size_t link_offset;
  size_t link_end;
  size_t title_offset;
  size_t title_end;
  size_t line_end;
  if ((beg + 3) >= end)
  {
    return 0;
  }
  if (data[beg] == ' ')
  {
    i = 1;
    if (data[beg + 1] == ' ')
    {
      i = 2;
      if (data[beg + 2] == ' ')
      {
        i = 3;
        if (data[beg + 3] == ' ')
        {
          return 0;
        }
      }
    }
  }
  i += beg;
  if (data[i] != '[')
  {
    return 0;
  }
  i += 1;
  id_offset = i;
  while ((((i < end) && (data[i] != '\n')) && (data[i] != '\r')) && (data[i] != ']'))
  {
    i += 1;
  }

  if ((i >= end) || (data[i] != ']'))
  {
    return 0;
  }
  id_end = i;
  i += 1;
  if ((i >= end) || (data[i] != ':'))
  {
    return 0;
  }
  i += 1;
  while ((i < end) && (data[i] == ' '))
  {
    i += 1;
  }

  if ((i < end) && ((data[i] == '\n') || (data[i] == '\r')))
  {
    i += 1;
    if (((i < end) && (data[i] == '\r')) && (data[i - 1] == '\n'))
    {
      i += 1;
    }
  }
  while ((i < end) && (data[i] == ' '))
  {
    i += 1;
  }

  if (i >= end)
  {
    return 0;
  }
  if (data[i] == '<')
  {
    i += 1;
  }
  link_offset = i;
  while ((((i < end) && (data[i] != ' ')) && (data[i] != '\n')) && (data[i] != '\r'))
  {
    i += 1;
  }

  if (data[i - 1] == '>')
  {
    link_end = i - 1;
  }
  else
    link_end = i;
  while ((i < end) && (data[i] == ' '))
  {
    i += 1;
  }

  if ((((((i < end) && (data[i] != '\n')) && (data[i] != '\r')) && (data[i] != '\'')) && (data[i] != '"')) && (data[i] != '('))
  {
    return 0;
  }
  line_end = 0;
  if (((i >= end) || (data[i] == '\r')) || (data[i] == '\n'))
  {
    line_end = i;
  }
  if ((((i + 1) < end) && (data[i] == '\n')) && (data[i + 1] == '\r'))
  {
    line_end = i + 1;
  }
  if (line_end)
  {
    i = line_end + 1;
    while ((i < end) && (data[i] == ' '))
    {
      i += 1;
    }

  }
  title_offset = (title_end = 0);
  if (((i + 1) < end) && (((data[i] == '\'') || (data[i] == '"')) || (data[i] == '(')))
  {
    i += 1;
    title_offset = i;
    while (((i < end) && (data[i] != '\n')) && (data[i] != '\r'))
    {
      i += 1;
    }

    if ((((i + 1) < end) && (data[i] == '\n')) && (data[i + 1] == '\r'))
    {
      title_end = i + 1;
    }
    else
      title_end = i;
    i -= 1;
    while ((i > title_offset) && (data[i] == ' '))
    {
      i -= 1;
    }

    if ((i > title_offset) && (((data[i] == '\'') || (data[i] == '"')) || (data[i] == ')')))
    {
      line_end = title_end;
      title_end = i;
    }
  }
  if ((!line_end) || (link_end == link_offset))
  {
    return 0;
  }
  if (last)
  {
    *last = line_end;
  }
  if (refs)
  {
    struct link_ref *ref;
    unsigned int ref_idx = 0;
    ref_idx = add_link_ref(refs, data + id_offset, id_end - id_offset);
    if (!(&ref[ref_idx]))
    {
      return 0;
    }
    ref->label = bufnew(id_end - id_offset);
    bufput(ref->label, data + id_offset, id_end - id_offset);
    ref->link = bufnew(link_end - link_offset);
    bufput(ref->link, data + link_offset, link_end - link_offset);
    if (title_end > title_offset)
    {
      ref->title = bufnew(title_end - title_offset);
      bufput(ref->title, data + title_offset, title_end - title_offset);
    }
  }
  return 1;
}

static void expand_tabs(struct buf *ob, const uint8_t *line, size_t size)
{
  size_t i = 0;
  size_t tab = 0;
  while (i < size)
  {
    size_t org = i;
    while ((i < size) && (line[i] != '\t'))
    {
      i += 1;
      tab += 1;
    }

    if (i > org)
    {
      bufput(ob, line + org, i - org);
    }
    if (i >= size)
    {
      break;
    }
    do
    {
      bufputc(ob, ' ');
      tab += 1;
    }
    while (tab % 4);
    i += 1;
  }

}

struct sd_markdown *sd_markdown_new(unsigned int extensions, size_t max_nesting, size_t max_table_cols, const struct sd_callbacks *callbacks, void *opaque)
{
  struct sd_markdown *md = 0;
  unsigned int md_idx = 0;
  assert(((max_nesting > 0) && (max_table_cols > 0)) && callbacks);
  md_idx = malloc(sizeof(struct sd_markdown));
  if (!(&md[md_idx]))
  {
    return 0;
  }
  if (!sip_hash_key_init)
  {
    if (backport_getrandom(sip_hash_key, 16, 0) < 16)
    {
      return 0;
    }
    sip_hash_key_init = 1;
  }
  memcpy(&md->cb, callbacks, sizeof(struct sd_callbacks));
  stack_init(&md->work_bufs[0], 4);
  stack_init(&md->work_bufs[1], 8);
  memset(md->active_char, 0x0, 256);
  if ((md->cb.emphasis || md->cb.double_emphasis) || md->cb.triple_emphasis)
  {
    md->active_char['*'] = MD_CHAR_EMPHASIS;
    md->active_char['_'] = MD_CHAR_EMPHASIS;
    md->active_char['>'] = MD_CHAR_EMPHASIS;
    if (extensions & MKDEXT_STRIKETHROUGH)
    {
      md->active_char['~'] = MD_CHAR_EMPHASIS;
    }
  }
  if (md->cb.codespan)
  {
    md->active_char['`'] = MD_CHAR_CODESPAN;
  }
  if (md->cb.linebreak)
  {
    md->active_char['\n'] = MD_CHAR_LINEBREAK;
  }
  if (md->cb.image || md->cb.link)
  {
    md->active_char['['] = MD_CHAR_LINK;
  }
  md->active_char['<'] = MD_CHAR_LANGLE;
  md->active_char['\\'] = MD_CHAR_ESCAPE;
  md->active_char['&'] = MD_CHAR_ENTITITY;
  if (extensions & MKDEXT_AUTOLINK)
  {
    if (!(extensions & MKDEXT_NO_EMAIL_AUTOLINK))
    {
      md->active_char['@'] = MD_CHAR_AUTOLINK_EMAIL;
    }
    md->active_char[':'] = MD_CHAR_AUTOLINK_URL;
    md->active_char['w'] = MD_CHAR_AUTOLINK_WWW;
    md->active_char['/'] = MD_CHAR_AUTOLINK_SUBREDDIT_OR_USERNAME;
  }
  if (extensions & MKDEXT_SUPERSCRIPT)
  {
    md->active_char['^'] = MD_CHAR_SUPERSCRIPT;
  }
  md->ext_flags = extensions;
  md->opaque = opaque;
  md->max_nesting = max_nesting;
  md->max_table_cols = max_table_cols;
  md->in_link_body = 0;
  return md;
}

void sd_markdown_render(struct buf *ob, const uint8_t *document, size_t doc_size, struct sd_markdown *md)
{
  static const char UTF8_BOM[] = {0xEF, 0xBB, 0xBF};
  struct buf *text;
  unsigned int text_idx = 0;
  size_t beg;
  size_t end;
  text_idx = bufnew(64);
  if (!(&text[text_idx]))
  {
    return;
  }
  bufgrow(text, doc_size);
  memset(&md->refs, 0x0, 8 * (sizeof(void *)));
  beg = 0;
  if ((doc_size >= 3) && (memcmp(document, UTF8_BOM, 3) == 0))
  {
    beg += 3;
  }
  while (beg < doc_size)
  {
    if (is_ref(document, beg, doc_size, &end, md->refs))
    {
      beg = end;
    }
    else
    {
      end = beg;
      while (((end < doc_size) && (document[end] != '\n')) && (document[end] != '\r'))
      {
        end += 1;
      }

      if (end > beg)
      {
        expand_tabs(text, document + beg, end - beg);
      }
      while ((end < doc_size) && ((document[end] == '\n') || (document[end] == '\r')))
      {
        if ((document[end] == '\n') || (((end + 1) < doc_size) && (document[end + 1] != '\n')))
        {
          bufputc(text, '\n');
        }
        end += 1;
      }

      beg = end;
    }
  }

  bufgrow(ob, text->size + (text->size >> 1));
  if (md->cb.doc_header)
  {
    md->cb.doc_header(ob, md->opaque);
  }
  if (text->size)
  {
    if ((text->data[text->size - 1] != '\n') && (text->data[text->size - 1] != '\r'))
    {
      bufputc(text, '\n');
    }
    parse_block(ob, md, text->data, text->size);
  }
  if (md->cb.doc_footer)
  {
    md->cb.doc_footer(ob, md->opaque);
  }
  bufrelease(text);
  free_link_refs(md->refs);
  assert(md->work_bufs[1].size == 0);
  assert(md->work_bufs[0].size == 0);
}

void sd_markdown_free(struct sd_markdown *md)
{
  size_t i;
  for (i = 0; i < ((size_t) md->work_bufs[1].asize); i += 1)
  {
    bufrelease(md->work_bufs[1].item[i]);
  }

  for (i = 0; i < ((size_t) md->work_bufs[0].asize); i += 1)
  {
    bufrelease(md->work_bufs[0].item[i]);
  }

  stack_free(&md->work_bufs[1]);
  stack_free(&md->work_bufs[0]);
  free(md);
}

void sd_version(int *ver_major, int *ver_minor, int *ver_revision)
{
  *ver_major = 1;
  *ver_minor = 16;
  *ver_revision = 0;
}

size_t helper_tag_length_1(size_t * const i_ref, size_t * const j_ref, uint8_t * const data, size_t size, enum mkd_autolink * const autolink)
{
  size_t i = *i_ref;
  size_t j = *j_ref;
  j = i;
  while (i < size)
  {
    if (data[i] == '\\')
    {
      i += 2;
    }
    else
      if (((((data[i] == '>') || (data[i] == '\'')) || (data[i] == '"')) || (data[i] == ' ')) || (data[i] == '\n'))
    {
      break;
    }
    else
      i++;
    i += 1;
  }

  if (i >= size)
  {
    return 0;
  }
  if ((i > j) && (data[i] == '>'))
  {
    return i + 1;
  }
  *autolink = MKDA_NOT_AUTOLINK;
  *i_ref = i;
  *j_ref = j;
}

size_t helper_find_emph_char_1(size_t * const i_ref, uint8_t * const data, size_t size, uint8_t c)
{
  size_t i = *i_ref;
  while ((((i < size) && (data[i] != c)) && (data[i] != '`')) && (data[i] != '['))
  {
    i += 1;
  }

  if (i == size)
  {
    return 0;
  }
  if ((((i < size) && (c == '<')) && (data[i] == c)) && (data[i - 1] == '!'))
  {
    return i;
  }
  if (data[i] == c)
  {
    return i;
  }
  if (i && (data[i - 1] == '\\'))
  {
    i += 1;
    continue;
  }
  if (data[i] == '`')
  {
    helper_helper_find_emph_char_1_1(&i, data, size, c);
  }
  else
    if (data[i] == '[')
  {
    helper_helper_find_emph_char_1_2(&i, data, size, c);
  }
  *i_ref = i;
}

void helper_char_link_1(size_t * const i_ref, unsigned int * const link_idx_ref, unsigned int * const title_idx_ref, struct sd_markdown * const rndr, uint8_t * const data, size_t txt_e, int text_has_nl)
{
  size_t i = *i_ref;
  unsigned int link_idx = *link_idx_ref;
  unsigned int title_idx = *title_idx_ref;
  struct buf id = {0, 0, 0, 0};
  struct link_ref *lr;
  unsigned int lr_idx = 0;
  if (text_has_nl)
  {
    struct buf *b = rndr_newbuf(rndr, 1);
    size_t j;
    for (j = 1; j < txt_e; j += 1)
    {
      if (data[j] != '\n')
      {
        bufputc(b, data[j]);
      }
      else
        if (data[j - 1] != ' ')
      {
        bufputc(b, ' ');
      }
    }

    id.data = b->data;
    id.size = b->size;
  }
  else
  {
    id.data = data + 1;
    id.size = txt_e - 1;
  }
  lr_idx = find_link_ref(rndr->refs, id.data, id.size);
  if (!(&lr[lr_idx]))
  {
    goto cleanup;
  }
  link_idx = lr->link_idx;
  title_idx = lr->title_idx;
  i = txt_e + 1;
  *i_ref = i;
  *link_idx_ref = link_idx;
  *title_idx_ref = title_idx;
}

void helper_char_link_2(size_t * const size_ref, size_t * const i_ref, size_t * const link_b_ref, size_t * const link_e_ref, unsigned int * const link_idx_ref, unsigned int * const title_idx_ref, struct sd_markdown * const rndr, uint8_t * const data, size_t txt_e, int text_has_nl)
{
  size_t size = *size_ref;
  size_t i = *i_ref;
  size_t link_b = *link_b_ref;
  size_t link_e = *link_e_ref;
  unsigned int link_idx = *link_idx_ref;
  unsigned int title_idx = *title_idx_ref;
  struct buf id = {0, 0, 0, 0};
  struct link_ref *lr;
  unsigned int lr_idx = 0;
  i += 1;
  link_b = i;
  while ((i < size) && (data[i] != ']'))
  {
    i += 1;
  }

  if (i >= size)
  {
    goto cleanup;
  }
  link_e = i;
  if (link_b == link_e)
  {
    helper_helper_char_link_2_1(&id, rndr, data, txt_e, text_has_nl);
  }
  else
  {
    id.data = data + link_b;
    id.size = link_e - link_b;
  }
  lr_idx = find_link_ref(rndr->refs, id.data, id.size);
  if (!(&lr[lr_idx]))
  {
    goto cleanup;
  }
  link_idx = lr->link_idx;
  title_idx = lr->title_idx;
  i += 1;
  *size_ref = size;
  *i_ref = i;
  *link_b_ref = link_b;
  *link_e_ref = link_e;
  *link_idx_ref = link_idx;
  *title_idx_ref = title_idx;
}

void helper_char_link_3(size_t * const i_ref, size_t * const link_b_ref, size_t * const link_e_ref, size_t * const title_b_ref, size_t * const title_e_ref, unsigned int * const link_idx_ref, unsigned int * const title_idx_ref, int * const in_title_ref, int * const qtype_ref, struct sd_markdown * const rndr, uint8_t * const data, size_t size, struct buf * const link, struct buf * const title)
{
  size_t i = *i_ref;
  size_t link_b = *link_b_ref;
  size_t link_e = *link_e_ref;
  size_t title_b = *title_b_ref;
  size_t title_e = *title_e_ref;
  unsigned int link_idx = *link_idx_ref;
  unsigned int title_idx = *title_idx_ref;
  int in_title = *in_title_ref;
  int qtype = *qtype_ref;
  i += 1;
  while ((i < size) && _isspace(data[i]))
  {
    i += 1;
  }

  link_b = i;
  while (i < size)
  {
    if (data[i] == '\\')
    {
      i += 2;
    }
    else
      if (data[i] == ')')
    {
      break;
    }
    else
      if (((i >= 1) && _isspace(data[i - 1])) && ((data[i] == '\'') || (data[i] == '"')))
    {
      break;
    }
    else
      i++;
    i += 1;
  }

  if (i >= size)
  {
    goto cleanup;
  }
  link_e = i;
  if ((data[i] == '\'') || (data[i] == '"'))
  {
    helper_helper_char_link_3_1(&i, &link_e, &title_b, &title_e, &in_title, &qtype, data, size);
  }
  while ((link_e > link_b) && _isspace(data[link_e - 1]))
  {
    link_e -= 1;
  }

  if (data[link_b] == '<')
  {
    link_b += 1;
  }
  if (data[link_e - 1] == '>')
  {
    link_e -= 1;
  }
  if (link_e > link_b)
  {
    link_idx = rndr_newbuf(rndr, 1);
    bufput(link, data + link_b, link_e - link_b);
  }
  if (title_e > title_b)
  {
    title_idx = rndr_newbuf(rndr, 1);
    bufput(title, data + title_b, title_e - title_b);
  }
  i += 1;
  *i_ref = i;
  *link_b_ref = link_b;
  *link_e_ref = link_e;
  *title_b_ref = title_b;
  *title_e_ref = title_e;
  *link_idx_ref = link_idx;
  *title_idx_ref = title_idx;
  *in_title_ref = in_title;
  *qtype_ref = qtype;
}

size_t helper_is_codefence_1(size_t * const i_ref, size_t * const syn_len_ref, unsigned int * const syn_start_idx_ref, uint8_t * const data, size_t size, uint8_t * const syn_start)
{
  size_t i = *i_ref;
  size_t syn_len = *syn_len_ref;
  unsigned int syn_start_idx = *syn_start_idx_ref;
  i += 1;
  syn_start_idx += 1;
  while (((i < size) && (data[i] != '}')) && (data[i] != '\n'))
  {
    syn_len += 1;
    i += 1;
  }

  if ((i == size) || (data[i] != '}'))
  {
    return 0;
  }
  while ((syn_len > 0) && _isspace(syn_start[0 + syn_start_idx]))
  {
    syn_start_idx += 1;
    syn_len -= 1;
  }

  while ((syn_len > 0) && _isspace(syn_start[(syn_len - 1) + syn_start_idx]))
  {
    syn_len -= 1;
  }

  i += 1;
  *i_ref = i;
  *syn_len_ref = syn_len;
  *syn_start_idx_ref = syn_start_idx;
}

void helper_parse_paragraph_1(size_t * const i_ref, size_t * const end_ref, int * const level_ref, struct buf * const ob, struct sd_markdown * const rndr, uint8_t * const data, size_t size)
{
  size_t i = *i_ref;
  size_t end = *end_ref;
  int level = *level_ref;
  for (end = i + 1; (end < size) && (data[end - 1] != '\n'); end += 1)
  {
    ;
  }

  if (prefix_quote(data + i, end - i) != 0)
  {
    end = i;
    break;
  }
  if (is_empty(data + i, size - i))
  {
    break;
  }
  if ((level = is_headerline(data + i, size - i)) != 0)
  {
    break;
  }
  if ((is_atxheader(rndr, data + i, size - i) || is_hrule(data + i, size - i)) || prefix_quote(data + i, size - i))
  {
    end = i;
    break;
  }
  if ((rndr->ext_flags & MKDEXT_LAX_SPACING) && (!isalnum(data[i])))
  {
    if (prefix_oli(data + i, size - i) || prefix_uli(data + i, size - i))
    {
      end = i;
      break;
    }
    if (((data[i] == '<') && rndr->cb.blockhtml) && parse_htmlblock(ob, rndr, data + i, size - i, 0))
    {
      end = i;
      break;
    }
    if (((rndr->ext_flags & MKDEXT_FENCED_CODE) != 0) && (is_codefence(data + i, size - i, 0) != 0))
    {
      end = i;
      break;
    }
  }
  i = end;
  *i_ref = i;
  *end_ref = end;
  *level_ref = level;
}

void helper_parse_paragraph_2(size_t * const i_ref, struct buf * const work_ref, struct buf * const ob, struct sd_markdown * const rndr, uint8_t * const data, int level)
{
  size_t i = *i_ref;
  struct buf work = *work_ref;
  struct buf *header_work;
  unsigned int header_work_idx = 0;
  if (work.size)
  {
    size_t beg;
    i = work.size;
    work.size -= 1;
    while (work.size && (data[work.size] != '\n'))
    {
      work.size -= 1;
    }

    beg = work.size + 1;
    while (work.size && (data[work.size - 1] == '\n'))
    {
      work.size -= 1;
    }

    if (work.size > 0)
    {
      struct buf *tmp = rndr_newbuf(rndr, 0);
      parse_inline(tmp, rndr, work.data, work.size);
      if (rndr->cb.paragraph)
      {
        rndr->cb.paragraph(ob, tmp, rndr->opaque);
      }
      rndr_popbuf(rndr, 0);
      work.data += beg;
      work.size = i - beg;
    }
    else
      work.size = i;
  }
  header_work_idx = rndr_newbuf(rndr, 1);
  parse_inline(header_work, rndr, work.data, work.size);
  if (rndr->cb.header)
  {
    rndr->cb.header(ob, header_work, (int) level, rndr->opaque);
  }
  rndr_popbuf(rndr, 1);
  *i_ref = i;
  *work_ref = work;
}

void helper_parse_listitem_1(size_t * const beg_ref, size_t * const end_ref, size_t * const pre_ref, size_t * const sublist_ref, size_t * const i_ref, int * const in_empty_ref, int * const has_inside_empty_ref, int * const in_fence_ref, struct sd_markdown * const rndr, uint8_t * const data, size_t size, int * const flags, struct buf * const work, size_t orgpre)
{
  size_t beg = *beg_ref;
  size_t end = *end_ref;
  size_t pre = *pre_ref;
  size_t sublist = *sublist_ref;
  size_t i = *i_ref;
  int in_empty = *in_empty_ref;
  int has_inside_empty = *has_inside_empty_ref;
  int in_fence = *in_fence_ref;
  size_t has_next_uli = 0;
  size_t has_next_oli = 0;
  end += 1;
  while ((end < size) && (data[end - 1] != '\n'))
  {
    end += 1;
  }

  if (is_empty(data + beg, end - beg))
  {
    in_empty = 1;
    beg = end;
    continue;
  }
  i = 0;
  while (((i < 4) && ((beg + i) < end)) && (data[beg + i] == ' '))
  {
    i += 1;
  }

  pre = i;
  if (rndr->ext_flags & MKDEXT_FENCED_CODE)
  {
    if (is_codefence((data + beg) + i, (end - beg) - i, 0) != 0)
    {
      in_fence = !in_fence;
    }
  }
  if (!in_fence)
  {
    has_next_uli = prefix_uli((data + beg) + i, (end - beg) - i);
    has_next_oli = prefix_oli((data + beg) + i, (end - beg) - i);
  }
  if (in_empty && ((((*flags) & 1) && has_next_uli) || ((!((*flags) & 1)) && has_next_oli)))
  {
    *flags |= 8;
    break;
  }
  if ((has_next_uli && (!is_hrule((data + beg) + i, (end - beg) - i))) || has_next_oli)
  {
    if (in_empty)
    {
      has_inside_empty = 1;
    }
    if (pre == orgpre)
    {
      break;
    }
    if (!sublist)
    {
      sublist = work->size;
    }
  }
  else
    if (in_empty && (pre == 0))
  {
    *flags |= 8;
    break;
  }
  else
    if (in_empty)
  {
    bufputc(work, '\n');
    has_inside_empty = 1;
  }
  in_empty = 0;
  bufput(work, (data + beg) + i, (end - beg) - i);
  beg = end;
  *beg_ref = beg;
  *end_ref = end;
  *pre_ref = pre;
  *sublist_ref = sublist;
  *i_ref = i;
  *in_empty_ref = in_empty;
  *has_inside_empty_ref = has_inside_empty;
  *in_fence_ref = in_fence;
}

size_t helper_parse_htmlblock_1(size_t * const size_ref, size_t * const i_ref, size_t * const j_ref, struct buf * const work_ref, struct buf * const ob, struct sd_markdown * const rndr, uint8_t * const data, int do_render)
{
  size_t size = *size_ref;
  size_t i = *i_ref;
  size_t j = *j_ref;
  struct buf work = *work_ref;
  if ((((size > 5) && (data[1] == '!')) && (data[2] == '-')) && (data[3] == '-'))
  {
    helper_helper_parse_htmlblock_1_1(&size, &i, &j, &work, ob, rndr, data, do_render);
  }
  if (((size > 4) && ((data[1] == 'h') || (data[1] == 'H'))) && ((data[2] == 'r') || (data[2] == 'R')))
  {
    helper_helper_parse_htmlblock_1_2(&size, &i, &j, &work, ob, rndr, data, do_render);
  }
  return 0;
  *size_ref = size;
  *i_ref = i;
  *j_ref = j;
  *work_ref = work;
}

void helper_parse_table_row_1(size_t * const i_ref, struct sd_markdown * const rndr, uint8_t * const data, size_t size, int * const col_data, int header_flag, size_t col, struct buf * const row_work)
{
  size_t i = *i_ref;
  size_t cell_start;
  size_t cell_end;
  struct buf *cell_work;
  unsigned int cell_work_idx = 0;
  cell_work_idx = rndr_newbuf(rndr, 1);
  while ((i < size) && _isspace(data[i]))
  {
    i += 1;
  }

  cell_start = i;
  while ((i < size) && (data[i] != '|'))
  {
    i += 1;
  }

  cell_end = i - 1;
  while ((cell_end > cell_start) && _isspace(data[cell_end]))
  {
    cell_end -= 1;
  }

  parse_inline(cell_work, rndr, data + cell_start, (1 + cell_end) - cell_start);
  rndr->cb.table_cell(row_work, cell_work, col_data[col] | header_flag, rndr->opaque, 0);
  rndr_popbuf(rndr, 1);
  i += 1;
  *i_ref = i;
}

void helper_parse_table_header_1(size_t * const i_ref, size_t * const col_ref, uint8_t * const data, int ** const column_data, size_t under_end)
{
  size_t i = *i_ref;
  size_t col = *col_ref;
  size_t dashes = 0;
  while ((i < under_end) && (data[i] == ' '))
  {
    i += 1;
  }

  if (data[i] == ':')
  {
    i += 1;
    (*column_data)[col] |= MKD_TABLE_ALIGN_L;
    dashes += 1;
  }
  while ((i < under_end) && (data[i] == '-'))
  {
    i += 1;
    dashes += 1;
  }

  if ((i < under_end) && (data[i] == ':'))
  {
    i += 1;
    (*column_data)[col] |= MKD_TABLE_ALIGN_R;
    dashes += 1;
  }
  while ((i < under_end) && (data[i] == ' '))
  {
    i += 1;
  }

  if ((i < under_end) && (data[i] != '|'))
  {
    break;
  }
  if (dashes < 1)
  {
    break;
  }
  i += 1;
  *i_ref = i;
  *col_ref = col;
}

void helper_is_ref_1(size_t * const i_ref, size_t * const title_offset_ref, size_t * const title_end_ref, size_t * const line_end_ref, const uint8_t * const data, size_t end)
{
  size_t i = *i_ref;
  size_t title_offset = *title_offset_ref;
  size_t title_end = *title_end_ref;
  size_t line_end = *line_end_ref;
  i += 1;
  title_offset = i;
  while (((i < end) && (data[i] != '\n')) && (data[i] != '\r'))
  {
    i += 1;
  }

  if ((((i + 1) < end) && (data[i] == '\n')) && (data[i + 1] == '\r'))
  {
    title_end = i + 1;
  }
  else
    title_end = i;
  i -= 1;
  while ((i > title_offset) && (data[i] == ' '))
  {
    i -= 1;
  }

  if ((i > title_offset) && (((data[i] == '\'') || (data[i] == '"')) || (data[i] == ')')))
  {
    line_end = title_end;
    title_end = i;
  }
  *i_ref = i;
  *title_offset_ref = title_offset;
  *title_end_ref = title_end;
  *line_end_ref = line_end;
}

int helper_is_ref_2(const uint8_t * const data, struct link_ref ** const refs, size_t id_offset, size_t id_end, size_t link_offset, size_t link_end, size_t title_offset, size_t title_end)
{
  struct link_ref *ref;
  unsigned int ref_idx = 0;
  ref_idx = add_link_ref(refs, data + id_offset, id_end - id_offset);
  if (!(&ref[ref_idx]))
  {
    return 0;
  }
  ref->label = bufnew(id_end - id_offset);
  bufput(ref->label, data + id_offset, id_end - id_offset);
  ref->link = bufnew(link_end - link_offset);
  bufput(ref->link, data + link_offset, link_end - link_offset);
  if (title_end > title_offset)
  {
    ref->title = bufnew(title_end - title_offset);
    bufput(ref->title, data + title_offset, title_end - title_offset);
  }
}

void helper_sd_markdown_render_1(size_t * const beg_ref, size_t * const end_ref, const uint8_t * const document, size_t doc_size, struct sd_markdown * const md, struct buf * const text)
{
  size_t beg = *beg_ref;
  size_t end = *end_ref;
  if (is_ref(document, beg, doc_size, &end, md->refs))
  {
    beg = end;
  }
  else
  {
    end = beg;
    while (((end < doc_size) && (document[end] != '\n')) && (document[end] != '\r'))
    {
      end += 1;
    }

    if (end > beg)
    {
      expand_tabs(text, document + beg, end - beg);
    }
    while ((end < doc_size) && ((document[end] == '\n') || (document[end] == '\r')))
    {
      if ((document[end] == '\n') || (((end + 1) < doc_size) && (document[end + 1] != '\n')))
      {
        bufputc(text, '\n');
      }
      end += 1;
    }

    beg = end;
  }
  *beg_ref = beg;
  *end_ref = end;
}

size_t helper_helper_find_emph_char_1_1(size_t * const i_ref, uint8_t * const data, size_t size, uint8_t c)
{
  size_t i = *i_ref;
  size_t span_nb = 0;
  size_t bt;
  size_t tmp_i = 0;
  while ((i < size) && (data[i] == '`'))
  {
    i += 1;
    span_nb += 1;
  }

  if (i >= size)
  {
    return 0;
  }
  bt = 0;
  while ((i < size) && (bt < span_nb))
  {
    if ((!tmp_i) && (data[i] == c))
    {
      tmp_i = i;
    }
    if (data[i] == '`')
    {
      bt += 1;
    }
    else
      bt = 0;
    i += 1;
  }

  if (i >= size)
  {
    return tmp_i;
  }
  *i_ref = i;
}

size_t helper_helper_find_emph_char_1_2(size_t * const i_ref, uint8_t * const data, size_t size, uint8_t c)
{
  size_t i = *i_ref;
  size_t tmp_i = 0;
  uint8_t cc;
  i += 1;
  while ((i < size) && (data[i] != ']'))
  {
    if ((!tmp_i) && (data[i] == c))
    {
      tmp_i = i;
    }
    i += 1;
  }

  i += 1;
  while ((i < size) && ((data[i] == ' ') || (data[i] == '\n')))
  {
    i += 1;
  }

  if (i >= size)
  {
    return tmp_i;
  }
  switch (data[i])
  {
    case '[':
    {
      cc = ']';
      break;
    }

    case '(':
    {
      cc = ')';
      break;
    }

    default:
    {
      if (tmp_i)
      {
        return tmp_i;
      }
      else
        continue;
    }

  }

  i += 1;
  while ((i < size) && (data[i] != cc))
  {
    if ((!tmp_i) && (data[i] == c))
    {
      tmp_i = i;
    }
    i += 1;
  }

  if (i >= size)
  {
    return tmp_i;
  }
  i += 1;
  *i_ref = i;
}

void helper_helper_char_link_2_1(struct buf * const id_ref, struct sd_markdown * const rndr, uint8_t * const data, size_t txt_e, int text_has_nl)
{
  struct buf id = *id_ref;
  if (text_has_nl)
  {
    struct buf *b = rndr_newbuf(rndr, 1);
    size_t j;
    for (j = 1; j < txt_e; j += 1)
    {
      if (data[j] != '\n')
      {
        bufputc(b, data[j]);
      }
      else
        if (data[j - 1] != ' ')
      {
        bufputc(b, ' ');
      }
    }

    id.data = b->data;
    id.size = b->size;
  }
  else
  {
    id.data = data + 1;
    id.size = txt_e - 1;
  }
  *id_ref = id;
}

void helper_helper_char_link_3_1(size_t * const i_ref, size_t * const link_e_ref, size_t * const title_b_ref, size_t * const title_e_ref, int * const in_title_ref, int * const qtype_ref, uint8_t * const data, size_t size)
{
  size_t i = *i_ref;
  size_t link_e = *link_e_ref;
  size_t title_b = *title_b_ref;
  size_t title_e = *title_e_ref;
  int in_title = *in_title_ref;
  int qtype = *qtype_ref;
  qtype = data[i];
  in_title = 1;
  i += 1;
  title_b = i;
  while (i < size)
  {
    if (data[i] == '\\')
    {
      i += 2;
    }
    else
      if (data[i] == qtype)
    {
      in_title = 0;
      i += 1;
    }
    else
      if ((data[i] == ')') && (!in_title))
    {
      break;
    }
    else
      i++;
    i += 1;
  }

  if (i >= size)
  {
    goto cleanup;
  }
  title_e = i - 1;
  while ((title_e > title_b) && _isspace(data[title_e]))
  {
    title_e -= 1;
  }

  if ((data[title_e] != '\'') && (data[title_e] != '"'))
  {
    title_b = (title_e = 0);
    link_e = i;
  }
  *i_ref = i;
  *link_e_ref = link_e;
  *title_b_ref = title_b;
  *title_e_ref = title_e;
  *in_title_ref = in_title;
  *qtype_ref = qtype;
}

size_t helper_helper_parse_htmlblock_1_1(size_t * const size_ref, size_t * const i_ref, size_t * const j_ref, struct buf * const work_ref, struct buf * const ob, struct sd_markdown * const rndr, uint8_t * const data, int do_render)
{
  size_t size = *size_ref;
  size_t i = *i_ref;
  size_t j = *j_ref;
  struct buf work = *work_ref;
  i = 5;
  while ((i < size) && (!(((data[i - 2] == '-') && (data[i - 1] == '-')) && (data[i] == '>'))))
  {
    i += 1;
  }

  i += 1;
  if (i < size)
  {
    j = is_empty(data + i, size - i);
  }
  if (j)
  {
    work.size = i + j;
    if (do_render && rndr->cb.blockhtml)
    {
      rndr->cb.blockhtml(ob, &work, rndr->opaque);
    }
    return work.size;
  }
  *size_ref = size;
  *i_ref = i;
  *j_ref = j;
  *work_ref = work;
}

size_t helper_helper_parse_htmlblock_1_2(size_t * const size_ref, size_t * const i_ref, size_t * const j_ref, struct buf * const work_ref, struct buf * const ob, struct sd_markdown * const rndr, uint8_t * const data, int do_render)
{
  size_t size = *size_ref;
  size_t i = *i_ref;
  size_t j = *j_ref;
  struct buf work = *work_ref;
  i = 3;
  while ((i < size) && (data[i] != '>'))
  {
    i += 1;
  }

  if ((i + 1) < size)
  {
    i += 1;
    j = is_empty(data + i, size - i);
    if (j)
    {
      work.size = i + j;
      if (do_render && rndr->cb.blockhtml)
      {
        rndr->cb.blockhtml(ob, &work, rndr->opaque);
      }
      return work.size;
    }
  }
  *size_ref = size;
  *i_ref = i;
  *j_ref = j;
  *work_ref = work;
}

