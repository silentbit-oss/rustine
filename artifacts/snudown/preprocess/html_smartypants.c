# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/html_smartypants.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/html_smartypants.c"
# 17 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/html_smartypants.c"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/buffer.h" 1
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/buffer.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1



typedef int START_DELIMETER;
typedef int socklen_t;
typedef int size_t;
typedef int __builtin_va_list;
typedef int __gnuc_va_list;
typedef int va_list;
typedef int __int8_t;
typedef int __uint8_t;
typedef int __int16_t;
typedef int __uint16_t;
typedef int __int_least16_t;
typedef int __uint_least16_t;
typedef int __int32_t;
typedef int __uint32_t;
typedef int __int64_t;
typedef int __uint64_t;
typedef int __int_least32_t;
typedef int __uint_least32_t;
typedef int __s8;
typedef int __u8;
typedef int __s16;
typedef int __u16;
typedef int __s32;
typedef int __u32;
typedef int __s64;
typedef int __u64;
typedef int _LOCK_T;
typedef int _LOCK_RECURSIVE_T;
typedef int _off_t;
typedef int __dev_t;
typedef int __uid_t;
typedef int __gid_t;
typedef int _off64_t;
typedef int _fpos_t;
typedef int _ssize_t;
typedef int wint_t;
typedef int _mbstate_t;
typedef int _flock_t;
typedef int _iconv_t;
typedef int __ULong;
typedef int __FILE;
typedef int ptrdiff_t;
typedef int wchar_t;
typedef int char16_t;
typedef int char32_t;
typedef int __off_t;
typedef int __pid_t;
typedef int __loff_t;
typedef int u_char;
typedef int u_short;
typedef int u_int;
typedef int u_long;
typedef int ushort;
typedef int uint;
typedef int clock_t;
typedef int time_t;
typedef int daddr_t;
typedef int caddr_t;
typedef int ino_t;
typedef int off_t;
typedef int dev_t;
typedef int uid_t;
typedef int gid_t;
typedef int pid_t;
typedef int key_t;
typedef int ssize_t;
typedef int mode_t;
typedef int nlink_t;
typedef int fd_mask;
typedef int _types_fd_set;
typedef int clockid_t;
typedef int timer_t;
typedef int useconds_t;
typedef int suseconds_t;
typedef int FILE;
typedef int fpos_t;
typedef int cookie_read_function_t;
typedef int cookie_write_function_t;
typedef int cookie_seek_function_t;
typedef int cookie_close_function_t;
typedef int cookie_io_functions_t;
typedef int div_t;
typedef int ldiv_t;
typedef int lldiv_t;
typedef int sigset_t;
typedef int __sigset_t;
typedef int _sig_func_ptr;
typedef int sig_atomic_t;
typedef int __tzrule_type;
typedef int __tzinfo_type;
typedef int mbstate_t;
typedef int sem_t;
typedef int pthread_t;
typedef int pthread_attr_t;
typedef int pthread_mutex_t;
typedef int pthread_mutexattr_t;
typedef int pthread_cond_t;
typedef int pthread_condattr_t;
typedef int pthread_key_t;
typedef int pthread_once_t;
typedef int pthread_rwlock_t;
typedef int pthread_rwlockattr_t;
typedef int pthread_spinlock_t;
typedef int pthread_barrier_t;
typedef int pthread_barrierattr_t;
typedef int jmp_buf;
typedef int rlim_t;
typedef int sa_family_t;
typedef int sigjmp_buf;
typedef int stack_t;
typedef int siginfo_t;
typedef int z_stream;


typedef int int8_t;
typedef int uint8_t;
typedef int int16_t;
typedef int uint16_t;
typedef int int32_t;
typedef int uint32_t;
typedef int int64_t;
typedef int uint64_t;


typedef int int_least8_t;
typedef int uint_least8_t;
typedef int int_least16_t;
typedef int uint_least16_t;
typedef int int_least32_t;
typedef int uint_least32_t;
typedef int int_least64_t;
typedef int uint_least64_t;


typedef int int_fast8_t;
typedef int uint_fast8_t;
typedef int int_fast16_t;
typedef int uint_fast16_t;
typedef int int_fast32_t;
typedef int uint_fast32_t;
typedef int int_fast64_t;
typedef int uint_fast64_t;


typedef int intptr_t;
typedef int uintptr_t;


typedef int intmax_t;
typedef int uintmax_t;


typedef _Bool bool;


typedef void* MirEGLNativeWindowType;
typedef void* MirEGLNativeDisplayType;
typedef struct MirConnection MirConnection;
typedef struct MirSurface MirSurface;
typedef struct MirSurfaceSpec MirSurfaceSpec;
typedef struct MirScreencast MirScreencast;
typedef struct MirPromptSession MirPromptSession;
typedef struct MirBufferStream MirBufferStream;
typedef struct MirPersistentId MirPersistentId;
typedef struct MirBlob MirBlob;
typedef struct MirDisplayConfig MirDisplayConfig;


typedef struct xcb_connection_t xcb_connection_t;
typedef uint32_t xcb_window_t;
typedef uint32_t xcb_visualid_t;


typedef _Atomic(_Bool) atomic_bool;
typedef _Atomic(char) atomic_char;
typedef _Atomic(signed char) atomic_schar;
typedef _Atomic(unsigned char) atomic_uchar;
typedef _Atomic(short) atomic_short;
typedef _Atomic(unsigned short) atomic_ushort;
typedef _Atomic(int) atomic_int;
typedef _Atomic(unsigned int) atomic_uint;
typedef _Atomic(long) atomic_long;
typedef _Atomic(unsigned long) atomic_ulong;
typedef _Atomic(long long) atomic_llong;
typedef _Atomic(unsigned long long) atomic_ullong;
typedef _Atomic(uint_least16_t) atomic_char16_t;
typedef _Atomic(uint_least32_t) atomic_char32_t;
typedef _Atomic(wchar_t) atomic_wchar_t;
typedef _Atomic(int_least8_t) atomic_int_least8_t;
typedef _Atomic(uint_least8_t) atomic_uint_least8_t;
typedef _Atomic(int_least16_t) atomic_int_least16_t;
typedef _Atomic(uint_least16_t) atomic_uint_least16_t;
typedef _Atomic(int_least32_t) atomic_int_least32_t;
typedef _Atomic(uint_least32_t) atomic_uint_least32_t;
typedef _Atomic(int_least64_t) atomic_int_least64_t;
typedef _Atomic(uint_least64_t) atomic_uint_least64_t;
typedef _Atomic(int_fast8_t) atomic_int_fast8_t;
typedef _Atomic(uint_fast8_t) atomic_uint_fast8_t;
typedef _Atomic(int_fast16_t) atomic_int_fast16_t;
typedef _Atomic(uint_fast16_t) atomic_uint_fast16_t;
typedef _Atomic(int_fast32_t) atomic_int_fast32_t;
typedef _Atomic(uint_fast32_t) atomic_uint_fast32_t;
typedef _Atomic(int_fast64_t) atomic_int_fast64_t;
typedef _Atomic(uint_fast64_t) atomic_uint_fast64_t;
typedef _Atomic(intptr_t) atomic_intptr_t;
typedef _Atomic(uintptr_t) atomic_uintptr_t;
typedef _Atomic(size_t) atomic_size_t;
typedef _Atomic(ptrdiff_t) atomic_ptrdiff_t;
typedef _Atomic(intmax_t) atomic_intmax_t;
typedef _Atomic(uintmax_t) atomic_uintmax_t;
typedef struct atomic_flag { atomic_bool _Value; } atomic_flag;
typedef enum memory_order {
  memory_order_relaxed,
  memory_order_consume,
  memory_order_acquire,
  memory_order_release,
  memory_order_acq_rel,
  memory_order_seq_cst
} memory_order;

typedef struct __locale_struct *__locale_t;
typedef __locale_t locale_t;
typedef int END_DELIMETER;
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 2
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/buffer.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdarg.h" 1
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/buffer.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/buffer.h" 2
# 34 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/buffer.h"
typedef enum {
 BUF_OK = 0,
 BUF_ENOMEM = -1,
 BUF_EINVALIDIDX = -2,
} buferror_t;


struct buf {
 uint8_t *data;
 size_t size;
 size_t asize;
 size_t unit;
};
# 61 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/buffer.h"
int bufgrow(struct buf *, size_t);


struct buf *bufnew(size_t) ;


const char *bufcstr(struct buf *);


int bufprefix(const struct buf *buf, const char *prefix);


void bufput(struct buf *, const void *, size_t);


void bufputs(struct buf *, const char *);


void bufputc(struct buf *, int);


void bufrelease(struct buf *);


void bufreset(struct buf *);


void bufslurp(struct buf *, size_t);


void bufprintf(struct buf *, const char *, ...) ;


int buftruncate(struct buf *buf, size_t size);
# 18 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/html_smartypants.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/html.h" 1
# 20 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/html.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/markdown.h" 1
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/markdown.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/autolink.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/autolink.h"
enum {
 SD_AUTOLINK_SHORT_DOMAINS = (1 << 0),
};

int
sd_autolink_issafe(const uint8_t *link, size_t link_len);

size_t
sd_autolink__www(size_t *rewind_p, struct buf *link,
 uint8_t *data, size_t max_rewind, size_t size, unsigned int flags);

size_t
sd_autolink__email(size_t *rewind_p, struct buf *link,
 uint8_t *data, size_t max_rewind, size_t size, unsigned int flags);

size_t
sd_autolink__url(size_t *rewind_p, struct buf *link,
 uint8_t *data, size_t max_rewind, size_t size, unsigned int flags);

extern size_t
sd_autolink__subreddit(size_t *rewind_p, struct buf *link, uint8_t *data,
 size_t max_rewind, size_t max_lookbehind, size_t size, int *no_slash);

extern size_t
sd_autolink__username(size_t *rewind_p, struct buf *link, uint8_t *data,
 size_t max_rewind, size_t max_lookbehind, size_t size, int *no_slash);
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/markdown.h" 2
# 39 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/markdown.h"
enum mkd_autolink {
 MKDA_NOT_AUTOLINK,
 MKDA_NORMAL,
 MKDA_EMAIL,
};

enum mkd_tableflags {
 MKD_TABLE_ALIGN_L = 1,
 MKD_TABLE_ALIGN_R = 2,
 MKD_TABLE_ALIGN_CENTER = 3,
 MKD_TABLE_ALIGNMASK = 3,
 MKD_TABLE_HEADER = 4
};

enum mkd_extensions {
 MKDEXT_NO_INTRA_EMPHASIS = (1 << 0),
 MKDEXT_TABLES = (1 << 1),
 MKDEXT_FENCED_CODE = (1 << 2),
 MKDEXT_AUTOLINK = (1 << 3),
 MKDEXT_STRIKETHROUGH = (1 << 4),
 MKDEXT_SPACE_HEADERS = (1 << 6),
 MKDEXT_SUPERSCRIPT = (1 << 7),
 MKDEXT_LAX_SPACING = (1 << 8),
 MKDEXT_NO_EMAIL_AUTOLINK = (1 << 9),
};


struct sd_callbacks {

 void (*blockcode)(struct buf *ob, const struct buf *text, const struct buf *lang, void *opaque);
 void (*blockquote)(struct buf *ob, const struct buf *text, void *opaque);
 void (*blockspoiler)(struct buf *ob, const struct buf *text, void *opaque);
 void (*blockhtml)(struct buf *ob,const struct buf *text, void *opaque);
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
# 119 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/markdown.h"
extern struct sd_markdown *
sd_markdown_new(
 unsigned int extensions,
 size_t max_nesting,
 size_t max_table_cols,
 const struct sd_callbacks *callbacks,
 void *opaque);

extern void
sd_markdown_render(struct buf *ob, const uint8_t *document, size_t doc_size, struct sd_markdown *md);

extern void
sd_markdown_free(struct sd_markdown *md);

extern void
sd_version(int *major, int *minor, int *revision);
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/html.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/html.h" 2





struct html_renderopt {
 struct {
  int header_count;
  int current_level;
  int level_offset;
 } toc_data;

 char* toc_id_prefix;

 unsigned int flags;

 char** html_element_whitelist;
 char** html_attr_whitelist;


 void (*link_attributes)(struct buf *ob, const struct buf *url, void *self);
};

typedef enum {
 HTML_SKIP_HTML = (1 << 0),
 HTML_SKIP_STYLE = (1 << 1),
 HTML_SKIP_IMAGES = (1 << 2),
 HTML_SKIP_LINKS = (1 << 3),
 HTML_EXPAND_TABS = (1 << 4),
 HTML_SAFELINK = (1 << 5),
 HTML_TOC = (1 << 6),
 HTML_HARD_WRAP = (1 << 7),
 HTML_USE_XHTML = (1 << 8),
 HTML_ESCAPE = (1 << 9),
 HTML_ALLOW_ELEMENT_WHITELIST = (1 << 10),
} html_render_mode;

typedef enum {
 HTML_TAG_NONE = 0,
 HTML_TAG_OPEN,
 HTML_TAG_CLOSE,
} html_tag;

int
sdhtml_is_tag(const uint8_t *tag_data, size_t tag_size, const char *tagname);

extern void
sdhtml_renderer(struct sd_callbacks *callbacks, struct html_renderopt *options_ptr, unsigned int render_flags);

extern void
sdhtml_toc_renderer(struct sd_callbacks *callbacks, struct html_renderopt *options_ptr);

extern void
sdhtml_smartypants(struct buf *ob, const uint8_t *text, size_t size);
# 19 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/html_smartypants.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/html_smartypants.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/html_smartypants.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/html_smartypants.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/ctype.h" 1
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/html_smartypants.c" 2





struct smartypants_data {
 int in_squote;
 int in_dquote;
};

static size_t smartypants_cb__ltag(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size);
static size_t smartypants_cb__dquote(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size);
static size_t smartypants_cb__amp(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size);
static size_t smartypants_cb__period(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size);
static size_t smartypants_cb__number(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size);
static size_t smartypants_cb__dash(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size);
static size_t smartypants_cb__parens(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size);
static size_t smartypants_cb__squote(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size);
static size_t smartypants_cb__backtick(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size);
static size_t smartypants_cb__escape(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size);

static size_t (*smartypants_cb_ptrs[])
 (struct buf *, struct smartypants_data *, uint8_t, const uint8_t *, size_t) =
{
 0,
 smartypants_cb__dash,
 smartypants_cb__parens,
 smartypants_cb__squote,
 smartypants_cb__dquote,
 smartypants_cb__amp,
 smartypants_cb__period,
 smartypants_cb__number,
 smartypants_cb__ltag,
 smartypants_cb__backtick,
 smartypants_cb__escape,
};

static const uint8_t smartypants_cb_chars[] = {
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 4, 0, 0, 0, 5, 3, 2, 0, 0, 0, 0, 1, 6, 0,
 0, 7, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0,
 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

static inline int
word_boundary(uint8_t c)
{
 return c == 0 || isspace(c) || ispunct(c);
}

static int
smartypants_quotes(struct buf *ob, uint8_t previous_char, uint8_t next_char, uint8_t quote, int *is_open)
{
 char ent[8];

 if (*is_open && !word_boundary(next_char))
  return 0;

 if (!(*is_open) && !word_boundary(previous_char))
  return 0;

 snprintf(ent, sizeof(ent), "&%c%cquo;", (*is_open) ? 'r' : 'l', quote);
 *is_open = !(*is_open);
 bufputs(ob, ent);
 return 1;
}

static size_t
smartypants_cb__squote(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
 if (size >= 2) {
  uint8_t t1 = tolower(text[1]);

  if (t1 == '\'') {
   if (smartypants_quotes(ob, previous_char, size >= 3 ? text[2] : 0, 'd', &smrt->in_dquote))
    return 1;
  }

  if ((t1 == 's' || t1 == 't' || t1 == 'm' || t1 == 'd') &&
   (size == 3 || word_boundary(text[2]))) {
   bufput(ob, "&rsquo;", sizeof "&rsquo;" - 1);
   return 0;
  }

  if (size >= 3) {
   uint8_t t2 = tolower(text[2]);

   if (((t1 == 'r' && t2 == 'e') ||
    (t1 == 'l' && t2 == 'l') ||
    (t1 == 'v' && t2 == 'e')) &&
    (size == 4 || word_boundary(text[3]))) {
    bufput(ob, "&rsquo;", sizeof "&rsquo;" - 1);
    return 0;
   }
  }
 }

 if (smartypants_quotes(ob, previous_char, size > 0 ? text[1] : 0, 's', &smrt->in_squote))
  return 0;

 bufputc(ob, text[0]);
 return 0;
}

static size_t
smartypants_cb__parens(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
 if (size >= 3) {
  uint8_t t1 = tolower(text[1]);
  uint8_t t2 = tolower(text[2]);

  if (t1 == 'c' && t2 == ')') {
   bufput(ob, "&copy;", sizeof "&copy;" - 1);
   return 2;
  }

  if (t1 == 'r' && t2 == ')') {
   bufput(ob, "&reg;", sizeof "&reg;" - 1);
   return 2;
  }

  if (size >= 4 && t1 == 't' && t2 == 'm' && text[3] == ')') {
   bufput(ob, "&trade;", sizeof "&trade;" - 1);
   return 3;
  }
 }

 bufputc(ob, text[0]);
 return 0;
}

static size_t
smartypants_cb__dash(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
 if (size >= 3 && text[1] == '-' && text[2] == '-') {
  bufput(ob, "&mdash;", sizeof "&mdash;" - 1);
  return 2;
 }

 if (size >= 2 && text[1] == '-') {
  bufput(ob, "&ndash;", sizeof "&ndash;" - 1);
  return 1;
 }

 bufputc(ob, text[0]);
 return 0;
}

static size_t
smartypants_cb__amp(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
 if (size >= 6 && memcmp(text, "&quot;", 6) == 0) {
  if (smartypants_quotes(ob, previous_char, size >= 7 ? text[6] : 0, 'd', &smrt->in_dquote))
   return 5;
 }

 if (size >= 4 && memcmp(text, "&#0;", 4) == 0)
  return 3;

 bufputc(ob, '&');
 return 0;
}

static size_t
smartypants_cb__period(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
 if (size >= 3 && text[1] == '.' && text[2] == '.') {
  bufput(ob, "&hellip;", sizeof "&hellip;" - 1);
  return 2;
 }

 if (size >= 5 && text[1] == ' ' && text[2] == '.' && text[3] == ' ' && text[4] == '.') {
  bufput(ob, "&hellip;", sizeof "&hellip;" - 1);
  return 4;
 }

 bufputc(ob, text[0]);
 return 0;
}

static size_t
smartypants_cb__backtick(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
 if (size >= 2 && text[1] == '`') {
  if (smartypants_quotes(ob, previous_char, size >= 3 ? text[2] : 0, 'd', &smrt->in_dquote))
   return 1;
 }

 return 0;
}

static size_t
smartypants_cb__number(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
 if (word_boundary(previous_char) && size >= 3) {
  if (text[0] == '1' && text[1] == '/' && text[2] == '2') {
   if (size == 3 || word_boundary(text[3])) {
    bufput(ob, "&frac12;", sizeof "&frac12;" - 1);
    return 2;
   }
  }

  if (text[0] == '1' && text[1] == '/' && text[2] == '4') {
   if (size == 3 || word_boundary(text[3]) ||
    (size >= 5 && tolower(text[3]) == 't' && tolower(text[4]) == 'h')) {
    bufput(ob, "&frac14;", sizeof "&frac14;" - 1);
    return 2;
   }
  }

  if (text[0] == '3' && text[1] == '/' && text[2] == '4') {
   if (size == 3 || word_boundary(text[3]) ||
    (size >= 6 && tolower(text[3]) == 't' && tolower(text[4]) == 'h' && tolower(text[5]) == 's')) {
    bufput(ob, "&frac34;", sizeof "&frac34;" - 1);
    return 2;
   }
  }
 }

 bufputc(ob, text[0]);
 return 0;
}

static size_t
smartypants_cb__dquote(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
 if (!smartypants_quotes(ob, previous_char, size > 0 ? text[1] : 0, 'd', &smrt->in_dquote))
  bufput(ob, "&quot;", sizeof "&quot;" - 1);

 return 0;
}

static size_t
smartypants_cb__ltag(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
 static const char *skip_tags[] = {
   "pre", "code", "var", "samp", "kbd", "math", "script", "style"
 };
 static const size_t skip_tags_count = 8;

 size_t tag, i = 0;

 while (i < size && text[i] != '>')
  i++;

 for (tag = 0; tag < skip_tags_count; ++tag) {
  if (sdhtml_is_tag(text, size, skip_tags[tag]) == HTML_TAG_OPEN)
   break;
 }

 if (tag < skip_tags_count) {
  for (;;) {
   while (i < size && text[i] != '<')
    i++;

   if (i == size)
    break;

   if (sdhtml_is_tag(text + i, size - i, skip_tags[tag]) == HTML_TAG_CLOSE)
    break;

   i++;
  }

  while (i < size && text[i] != '>')
   i++;
 }

 bufput(ob, text, i + 1);
 return i;
}

static size_t
smartypants_cb__escape(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
 if (size < 2)
  return 0;

 switch (text[1]) {
 case '\\':
 case '"':
 case '\'':
 case '.':
 case '-':
 case '`':
  bufputc(ob, text[1]);
  return 1;

 default:
  bufputc(ob, '\\');
  return 0;
 }
}
# 360 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/html_smartypants.c"
void
sdhtml_smartypants(struct buf *ob, const uint8_t *text, size_t size)
{
 size_t i;
 struct smartypants_data smrt = {0, 0};

 if (!text)
  return;

 bufgrow(ob, size);

 for (i = 0; i < size; ++i) {
  size_t org;
  uint8_t action = 0;

  org = i;
  while (i < size && (action = smartypants_cb_chars[text[i]]) == 0)
   i++;

  if (i > org)
   bufput(ob, text + org, i - org);

  if (i < size) {
   i += smartypants_cb_ptrs[(int)action]
    (ob, &smrt, i ? text[i - 1] : 0, text + i, size - i);
  }
 }
}
# 0 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/html_smartypants.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/html_smartypants.c"
# 17 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/html_smartypants.c"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/buffer.h" 1
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/buffer.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 1
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_defines.h" 1
# 2 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/_fake_typedefs.h" 1



typedef int START_DELIMETER;
typedef int socklen_t;
typedef int size_t;
typedef int __builtin_va_list;
typedef int __gnuc_va_list;
typedef int va_list;
typedef int __int8_t;
typedef int __uint8_t;
typedef int __int16_t;
typedef int __uint16_t;
typedef int __int_least16_t;
typedef int __uint_least16_t;
typedef int __int32_t;
typedef int __uint32_t;
typedef int __int64_t;
typedef int __uint64_t;
typedef int __int_least32_t;
typedef int __uint_least32_t;
typedef int __s8;
typedef int __u8;
typedef int __s16;
typedef int __u16;
typedef int __s32;
typedef int __u32;
typedef int __s64;
typedef int __u64;
typedef int _LOCK_T;
typedef int _LOCK_RECURSIVE_T;
typedef int _off_t;
typedef int __dev_t;
typedef int __uid_t;
typedef int __gid_t;
typedef int _off64_t;
typedef int _fpos_t;
typedef int _ssize_t;
typedef int wint_t;
typedef int _mbstate_t;
typedef int _flock_t;
typedef int _iconv_t;
typedef int __ULong;
typedef int __FILE;
typedef int ptrdiff_t;
typedef int wchar_t;
typedef int char16_t;
typedef int char32_t;
typedef int __off_t;
typedef int __pid_t;
typedef int __loff_t;
typedef int u_char;
typedef int u_short;
typedef int u_int;
typedef int u_long;
typedef int ushort;
typedef int uint;
typedef int clock_t;
typedef int time_t;
typedef int daddr_t;
typedef int caddr_t;
typedef int ino_t;
typedef int off_t;
typedef int dev_t;
typedef int uid_t;
typedef int gid_t;
typedef int pid_t;
typedef int key_t;
typedef int ssize_t;
typedef int mode_t;
typedef int nlink_t;
typedef int fd_mask;
typedef int _types_fd_set;
typedef int clockid_t;
typedef int timer_t;
typedef int useconds_t;
typedef int suseconds_t;
typedef int FILE;
typedef int fpos_t;
typedef int cookie_read_function_t;
typedef int cookie_write_function_t;
typedef int cookie_seek_function_t;
typedef int cookie_close_function_t;
typedef int cookie_io_functions_t;
typedef int div_t;
typedef int ldiv_t;
typedef int lldiv_t;
typedef int sigset_t;
typedef int __sigset_t;
typedef int _sig_func_ptr;
typedef int sig_atomic_t;
typedef int __tzrule_type;
typedef int __tzinfo_type;
typedef int mbstate_t;
typedef int sem_t;
typedef int pthread_t;
typedef int pthread_attr_t;
typedef int pthread_mutex_t;
typedef int pthread_mutexattr_t;
typedef int pthread_cond_t;
typedef int pthread_condattr_t;
typedef int pthread_key_t;
typedef int pthread_once_t;
typedef int pthread_rwlock_t;
typedef int pthread_rwlockattr_t;
typedef int pthread_spinlock_t;
typedef int pthread_barrier_t;
typedef int pthread_barrierattr_t;
typedef int jmp_buf;
typedef int rlim_t;
typedef int sa_family_t;
typedef int sigjmp_buf;
typedef int stack_t;
typedef int siginfo_t;
typedef int z_stream;


typedef int int8_t;
typedef int uint8_t;
typedef int int16_t;
typedef int uint16_t;
typedef int int32_t;
typedef int uint32_t;
typedef int int64_t;
typedef int uint64_t;


typedef int int_least8_t;
typedef int uint_least8_t;
typedef int int_least16_t;
typedef int uint_least16_t;
typedef int int_least32_t;
typedef int uint_least32_t;
typedef int int_least64_t;
typedef int uint_least64_t;


typedef int int_fast8_t;
typedef int uint_fast8_t;
typedef int int_fast16_t;
typedef int uint_fast16_t;
typedef int int_fast32_t;
typedef int uint_fast32_t;
typedef int int_fast64_t;
typedef int uint_fast64_t;


typedef int intptr_t;
typedef int uintptr_t;


typedef int intmax_t;
typedef int uintmax_t;


typedef _Bool bool;


typedef void* MirEGLNativeWindowType;
typedef void* MirEGLNativeDisplayType;
typedef struct MirConnection MirConnection;
typedef struct MirSurface MirSurface;
typedef struct MirSurfaceSpec MirSurfaceSpec;
typedef struct MirScreencast MirScreencast;
typedef struct MirPromptSession MirPromptSession;
typedef struct MirBufferStream MirBufferStream;
typedef struct MirPersistentId MirPersistentId;
typedef struct MirBlob MirBlob;
typedef struct MirDisplayConfig MirDisplayConfig;


typedef struct xcb_connection_t xcb_connection_t;
typedef uint32_t xcb_window_t;
typedef uint32_t xcb_visualid_t;


typedef _Atomic(_Bool) atomic_bool;
typedef _Atomic(char) atomic_char;
typedef _Atomic(signed char) atomic_schar;
typedef _Atomic(unsigned char) atomic_uchar;
typedef _Atomic(short) atomic_short;
typedef _Atomic(unsigned short) atomic_ushort;
typedef _Atomic(int) atomic_int;
typedef _Atomic(unsigned int) atomic_uint;
typedef _Atomic(long) atomic_long;
typedef _Atomic(unsigned long) atomic_ulong;
typedef _Atomic(long long) atomic_llong;
typedef _Atomic(unsigned long long) atomic_ullong;
typedef _Atomic(uint_least16_t) atomic_char16_t;
typedef _Atomic(uint_least32_t) atomic_char32_t;
typedef _Atomic(wchar_t) atomic_wchar_t;
typedef _Atomic(int_least8_t) atomic_int_least8_t;
typedef _Atomic(uint_least8_t) atomic_uint_least8_t;
typedef _Atomic(int_least16_t) atomic_int_least16_t;
typedef _Atomic(uint_least16_t) atomic_uint_least16_t;
typedef _Atomic(int_least32_t) atomic_int_least32_t;
typedef _Atomic(uint_least32_t) atomic_uint_least32_t;
typedef _Atomic(int_least64_t) atomic_int_least64_t;
typedef _Atomic(uint_least64_t) atomic_uint_least64_t;
typedef _Atomic(int_fast8_t) atomic_int_fast8_t;
typedef _Atomic(uint_fast8_t) atomic_uint_fast8_t;
typedef _Atomic(int_fast16_t) atomic_int_fast16_t;
typedef _Atomic(uint_fast16_t) atomic_uint_fast16_t;
typedef _Atomic(int_fast32_t) atomic_int_fast32_t;
typedef _Atomic(uint_fast32_t) atomic_uint_fast32_t;
typedef _Atomic(int_fast64_t) atomic_int_fast64_t;
typedef _Atomic(uint_fast64_t) atomic_uint_fast64_t;
typedef _Atomic(intptr_t) atomic_intptr_t;
typedef _Atomic(uintptr_t) atomic_uintptr_t;
typedef _Atomic(size_t) atomic_size_t;
typedef _Atomic(ptrdiff_t) atomic_ptrdiff_t;
typedef _Atomic(intmax_t) atomic_intmax_t;
typedef _Atomic(uintmax_t) atomic_uintmax_t;
typedef struct atomic_flag { atomic_bool _Value; } atomic_flag;
typedef enum memory_order {
  memory_order_relaxed,
  memory_order_consume,
  memory_order_acquire,
  memory_order_release,
  memory_order_acq_rel,
  memory_order_seq_cst
} memory_order;

typedef struct __locale_struct *__locale_t;
typedef __locale_t locale_t;
typedef int END_DELIMETER;
# 3 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stddef.h" 2
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/buffer.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdarg.h" 1
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/buffer.h" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdint.h" 1
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/buffer.h" 2
# 34 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/buffer.h"
typedef enum {
 BUF_OK = 0,
 BUF_ENOMEM = -1,
 BUF_EINVALIDIDX = -2,
} buferror_t;


struct buf {
 uint8_t *data;
 size_t size;
 size_t asize;
 size_t unit;
};
# 61 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/buffer.h"
int bufgrow(struct buf *, size_t);


struct buf *bufnew(size_t) ;


const char *bufcstr(struct buf *);


int bufprefix(const struct buf *buf, const char *prefix);


void bufput(struct buf *, const void *, size_t);


void bufputs(struct buf *, const char *);


void bufputc(struct buf *, int);


void bufrelease(struct buf *);


void bufreset(struct buf *);


void bufslurp(struct buf *, size_t);


void bufprintf(struct buf *, const char *, ...) ;


int buftruncate(struct buf *buf, size_t size);
# 18 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/html_smartypants.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/html.h" 1
# 20 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/html.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/markdown.h" 1
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/markdown.h"
# 1 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/autolink.h" 1
# 26 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/autolink.h"
enum {
 SD_AUTOLINK_SHORT_DOMAINS = (1 << 0),
};

int
sd_autolink_issafe(const uint8_t *link, size_t link_len);

size_t
sd_autolink__www(size_t *rewind_p, struct buf *link,
 uint8_t *data, size_t max_rewind, size_t size, unsigned int flags);

size_t
sd_autolink__email(size_t *rewind_p, struct buf *link,
 uint8_t *data, size_t max_rewind, size_t size, unsigned int flags);

size_t
sd_autolink__url(size_t *rewind_p, struct buf *link,
 uint8_t *data, size_t max_rewind, size_t size, unsigned int flags);

extern size_t
sd_autolink__subreddit(size_t *rewind_p, struct buf *link, uint8_t *data,
 size_t max_rewind, size_t max_lookbehind, size_t size, int *no_slash);

extern size_t
sd_autolink__username(size_t *rewind_p, struct buf *link, uint8_t *data,
 size_t max_rewind, size_t max_lookbehind, size_t size, int *no_slash);
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/markdown.h" 2
# 39 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/markdown.h"
enum mkd_autolink {
 MKDA_NOT_AUTOLINK,
 MKDA_NORMAL,
 MKDA_EMAIL,
};

enum mkd_tableflags {
 MKD_TABLE_ALIGN_L = 1,
 MKD_TABLE_ALIGN_R = 2,
 MKD_TABLE_ALIGN_CENTER = 3,
 MKD_TABLE_ALIGNMASK = 3,
 MKD_TABLE_HEADER = 4
};

enum mkd_extensions {
 MKDEXT_NO_INTRA_EMPHASIS = (1 << 0),
 MKDEXT_TABLES = (1 << 1),
 MKDEXT_FENCED_CODE = (1 << 2),
 MKDEXT_AUTOLINK = (1 << 3),
 MKDEXT_STRIKETHROUGH = (1 << 4),
 MKDEXT_SPACE_HEADERS = (1 << 6),
 MKDEXT_SUPERSCRIPT = (1 << 7),
 MKDEXT_LAX_SPACING = (1 << 8),
 MKDEXT_NO_EMAIL_AUTOLINK = (1 << 9),
};


struct sd_callbacks {

 void (*blockcode)(struct buf *ob, const struct buf *text, const struct buf *lang, void *opaque);
 void (*blockquote)(struct buf *ob, const struct buf *text, void *opaque);
 void (*blockspoiler)(struct buf *ob, const struct buf *text, void *opaque);
 void (*blockhtml)(struct buf *ob,const struct buf *text, void *opaque);
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
# 119 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/markdown.h"
extern struct sd_markdown *
sd_markdown_new(
 unsigned int extensions,
 size_t max_nesting,
 size_t max_table_cols,
 const struct sd_callbacks *callbacks,
 void *opaque);

extern void
sd_markdown_render(struct buf *ob, const uint8_t *document, size_t doc_size, struct sd_markdown *md);

extern void
sd_markdown_free(struct sd_markdown *md);

extern void
sd_version(int *major, int *minor, int *revision);
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/html.h" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/html.h" 2





struct html_renderopt {
 struct {
  int header_count;
  int current_level;
  int level_offset;
 } toc_data;

 char* toc_id_prefix;

 unsigned int flags;

 char** html_element_whitelist;
 char** html_attr_whitelist;


 void (*link_attributes)(struct buf *ob, const struct buf *url, void *self);
};

typedef enum {
 HTML_SKIP_HTML = (1 << 0),
 HTML_SKIP_STYLE = (1 << 1),
 HTML_SKIP_IMAGES = (1 << 2),
 HTML_SKIP_LINKS = (1 << 3),
 HTML_EXPAND_TABS = (1 << 4),
 HTML_SAFELINK = (1 << 5),
 HTML_TOC = (1 << 6),
 HTML_HARD_WRAP = (1 << 7),
 HTML_USE_XHTML = (1 << 8),
 HTML_ESCAPE = (1 << 9),
 HTML_ALLOW_ELEMENT_WHITELIST = (1 << 10),
} html_render_mode;

typedef enum {
 HTML_TAG_NONE = 0,
 HTML_TAG_OPEN,
 HTML_TAG_CLOSE,
} html_tag;

int
sdhtml_is_tag(const uint8_t *tag_data, size_t tag_size, const char *tagname);

extern void
sdhtml_renderer(struct sd_callbacks *callbacks, struct html_renderopt *options_ptr, unsigned int render_flags);

extern void
sdhtml_toc_renderer(struct sd_callbacks *callbacks, struct html_renderopt *options_ptr);

extern void
sdhtml_smartypants(struct buf *ob, const uint8_t *text, size_t size);
# 19 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/html_smartypants.c" 2

# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/string.h" 1
# 21 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/html_smartypants.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdlib.h" 1
# 22 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/html_smartypants.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/stdio.h" 1
# 23 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/html_smartypants.c" 2
# 1 "/home/enumclass/Documents/C2RustTranslation/pipeline/preprocess/fake_libc_include/ctype.h" 1
# 24 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/html_smartypants.c" 2





struct smartypants_data {
 int in_squote;
 int in_dquote;
};

static size_t smartypants_cb__ltag(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size);
static size_t smartypants_cb__dquote(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size);
static size_t smartypants_cb__amp(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size);
static size_t smartypants_cb__period(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size);
static size_t smartypants_cb__number(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size);
static size_t smartypants_cb__dash(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size);
static size_t smartypants_cb__parens(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size);
static size_t smartypants_cb__squote(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size);
static size_t smartypants_cb__backtick(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size);
static size_t smartypants_cb__escape(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size);

static size_t (*smartypants_cb_ptrs[])
 (struct buf *, struct smartypants_data *, uint8_t, const uint8_t *, size_t) =
{
 0,
 smartypants_cb__dash,
 smartypants_cb__parens,
 smartypants_cb__squote,
 smartypants_cb__dquote,
 smartypants_cb__amp,
 smartypants_cb__period,
 smartypants_cb__number,
 smartypants_cb__ltag,
 smartypants_cb__backtick,
 smartypants_cb__escape,
};

static const uint8_t smartypants_cb_chars[] = {
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 4, 0, 0, 0, 5, 3, 2, 0, 0, 0, 0, 1, 6, 0,
 0, 7, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0,
 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

static inline int
word_boundary(uint8_t c)
{
 return c == 0 || isspace(c) || ispunct(c);
}

static int
smartypants_quotes(struct buf *ob, uint8_t previous_char, uint8_t next_char, uint8_t quote, int *is_open)
{
 char ent[8];

 if (*is_open && !word_boundary(next_char))
  return 0;

 if (!(*is_open) && !word_boundary(previous_char))
  return 0;

 snprintf(ent, sizeof(ent), "&%c%cquo;", (*is_open) ? 'r' : 'l', quote);
 *is_open = !(*is_open);
 bufputs(ob, ent);
 return 1;
}

static size_t
smartypants_cb__squote(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
 if (size >= 2) {
  uint8_t t1 = tolower(text[1]);

  if (t1 == '\'') {
   if (smartypants_quotes(ob, previous_char, size >= 3 ? text[2] : 0, 'd', &smrt->in_dquote))
    return 1;
  }

  if ((t1 == 's' || t1 == 't' || t1 == 'm' || t1 == 'd') &&
   (size == 3 || word_boundary(text[2]))) {
   bufput(ob, "&rsquo;", sizeof "&rsquo;" - 1);
   return 0;
  }

  if (size >= 3) {
   uint8_t t2 = tolower(text[2]);

   if (((t1 == 'r' && t2 == 'e') ||
    (t1 == 'l' && t2 == 'l') ||
    (t1 == 'v' && t2 == 'e')) &&
    (size == 4 || word_boundary(text[3]))) {
    bufput(ob, "&rsquo;", sizeof "&rsquo;" - 1);
    return 0;
   }
  }
 }

 if (smartypants_quotes(ob, previous_char, size > 0 ? text[1] : 0, 's', &smrt->in_squote))
  return 0;

 bufputc(ob, text[0]);
 return 0;
}

static size_t
smartypants_cb__parens(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
 if (size >= 3) {
  uint8_t t1 = tolower(text[1]);
  uint8_t t2 = tolower(text[2]);

  if (t1 == 'c' && t2 == ')') {
   bufput(ob, "&copy;", sizeof "&copy;" - 1);
   return 2;
  }

  if (t1 == 'r' && t2 == ')') {
   bufput(ob, "&reg;", sizeof "&reg;" - 1);
   return 2;
  }

  if (size >= 4 && t1 == 't' && t2 == 'm' && text[3] == ')') {
   bufput(ob, "&trade;", sizeof "&trade;" - 1);
   return 3;
  }
 }

 bufputc(ob, text[0]);
 return 0;
}

static size_t
smartypants_cb__dash(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
 if (size >= 3 && text[1] == '-' && text[2] == '-') {
  bufput(ob, "&mdash;", sizeof "&mdash;" - 1);
  return 2;
 }

 if (size >= 2 && text[1] == '-') {
  bufput(ob, "&ndash;", sizeof "&ndash;" - 1);
  return 1;
 }

 bufputc(ob, text[0]);
 return 0;
}

static size_t
smartypants_cb__amp(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
 if (size >= 6 && memcmp(text, "&quot;", 6) == 0) {
  if (smartypants_quotes(ob, previous_char, size >= 7 ? text[6] : 0, 'd', &smrt->in_dquote))
   return 5;
 }

 if (size >= 4 && memcmp(text, "&#0;", 4) == 0)
  return 3;

 bufputc(ob, '&');
 return 0;
}

static size_t
smartypants_cb__period(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
 if (size >= 3 && text[1] == '.' && text[2] == '.') {
  bufput(ob, "&hellip;", sizeof "&hellip;" - 1);
  return 2;
 }

 if (size >= 5 && text[1] == ' ' && text[2] == '.' && text[3] == ' ' && text[4] == '.') {
  bufput(ob, "&hellip;", sizeof "&hellip;" - 1);
  return 4;
 }

 bufputc(ob, text[0]);
 return 0;
}

static size_t
smartypants_cb__backtick(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
 if (size >= 2 && text[1] == '`') {
  if (smartypants_quotes(ob, previous_char, size >= 3 ? text[2] : 0, 'd', &smrt->in_dquote))
   return 1;
 }

 return 0;
}

static size_t
smartypants_cb__number(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
 if (word_boundary(previous_char) && size >= 3) {
  if (text[0] == '1' && text[1] == '/' && text[2] == '2') {
   if (size == 3 || word_boundary(text[3])) {
    bufput(ob, "&frac12;", sizeof "&frac12;" - 1);
    return 2;
   }
  }

  if (text[0] == '1' && text[1] == '/' && text[2] == '4') {
   if (size == 3 || word_boundary(text[3]) ||
    (size >= 5 && tolower(text[3]) == 't' && tolower(text[4]) == 'h')) {
    bufput(ob, "&frac14;", sizeof "&frac14;" - 1);
    return 2;
   }
  }

  if (text[0] == '3' && text[1] == '/' && text[2] == '4') {
   if (size == 3 || word_boundary(text[3]) ||
    (size >= 6 && tolower(text[3]) == 't' && tolower(text[4]) == 'h' && tolower(text[5]) == 's')) {
    bufput(ob, "&frac34;", sizeof "&frac34;" - 1);
    return 2;
   }
  }
 }

 bufputc(ob, text[0]);
 return 0;
}

static size_t
smartypants_cb__dquote(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
 if (!smartypants_quotes(ob, previous_char, size > 0 ? text[1] : 0, 'd', &smrt->in_dquote))
  bufput(ob, "&quot;", sizeof "&quot;" - 1);

 return 0;
}

static size_t
smartypants_cb__ltag(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
 static const char *skip_tags[] = {
   "pre", "code", "var", "samp", "kbd", "math", "script", "style"
 };
 static const size_t skip_tags_count = 8;

 size_t tag, i = 0;

 while (i < size && text[i] != '>')
  i++;

 for (tag = 0; tag < skip_tags_count; ++tag) {
  if (sdhtml_is_tag(text, size, skip_tags[tag]) == HTML_TAG_OPEN)
   break;
 }

 if (tag < skip_tags_count) {
  for (;;) {
   while (i < size && text[i] != '<')
    i++;

   if (i == size)
    break;

   if (sdhtml_is_tag(text + i, size - i, skip_tags[tag]) == HTML_TAG_CLOSE)
    break;

   i++;
  }

  while (i < size && text[i] != '>')
   i++;
 }

 bufput(ob, text, i + 1);
 return i;
}

static size_t
smartypants_cb__escape(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
 if (size < 2)
  return 0;

 switch (text[1]) {
 case '\\':
 case '"':
 case '\'':
 case '.':
 case '-':
 case '`':
  bufputc(ob, text[1]);
  return 1;

 default:
  bufputc(ob, '\\');
  return 0;
 }
}
# 360 "/home/enumclass/Documents/C2RustTranslation/bkp/snudown/html_smartypants.c"
void
sdhtml_smartypants(struct buf *ob, const uint8_t *text, size_t size)
{
 size_t i;
 struct smartypants_data smrt = {0, 0};

 if (!text)
  return;

 bufgrow(ob, size);

 for (i = 0; i < size; ++i) {
  size_t org;
  uint8_t action = 0;

  org = i;
  while (i < size && (action = smartypants_cb_chars[text[i]]) == 0)
   i++;

  if (i > org)
   bufput(ob, text + org, i - org);

  if (i < size) {
   i += smartypants_cb_ptrs[(int)action]
    (ob, &smrt, i ? text[i - 1] : 0, text + i, size - i);
  }
 }
}
