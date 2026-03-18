#include <Python.h>
#include <autolink.h>
#include <buffer.h>
#include <html.h>
#include <markdown.h>
#include <snudown.c>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct _object PyObject;
typedef struct PyMethodDef PyMethodDef;
typedef PyObject *(*PyCFunction)(PyObject *, PyObject *);
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
struct html_renderopt
{
  struct 
  {
    int header_count;
    int current_level;
    int level_offset;
  } toc_data;
  char *toc_id_prefix;
  unsigned int flags;
  char **html_element_whitelist;
  char **html_attr_whitelist;
  void (*link_attributes)(struct buf *ob, const struct buf *url, void *self);
};
typedef enum 
{
  HTML_SKIP_HTML = 1 << 0,
  HTML_SKIP_STYLE = 1 << 1,
  HTML_SKIP_IMAGES = 1 << 2,
  HTML_SKIP_LINKS = 1 << 3,
  HTML_EXPAND_TABS = 1 << 4,
  HTML_SAFELINK = 1 << 5,
  HTML_TOC = 1 << 6,
  HTML_HARD_WRAP = 1 << 7,
  HTML_USE_XHTML = 1 << 8,
  HTML_ESCAPE = 1 << 9,
  HTML_ALLOW_ELEMENT_WHITELIST = 1 << 10
} html_render_mode;
typedef enum 
{
  HTML_TAG_NONE = 0,
  HTML_TAG_OPEN,
  HTML_TAG_CLOSE
} html_tag;
int sdhtml_is_tag(const uint8_t *tag_data, size_t tag_size, const char *tagname);
extern void sdhtml_renderer(struct sd_callbacks *callbacks, struct html_renderopt *options_ptr, unsigned int render_flags);
extern void sdhtml_toc_renderer(struct sd_callbacks *callbacks, struct html_renderopt *options_ptr);
extern void sdhtml_smartypants(struct buf *ob, const uint8_t *text, size_t size);
enum snudown_renderer_mode
{
  RENDERER_USERTEXT = 0,
  RENDERER_WIKI,
  RENDERER_COUNT
};
struct snudown_renderopt
{
  struct html_renderopt html;
  int nofollow;
  const char *target;
};
struct snudown_renderer
{
  struct sd_markdown *main_renderer;
  struct sd_markdown *toc_renderer;
  struct module_state *state;
  struct module_state *toc_state;
};
struct module_state
{
  struct sd_callbacks callbacks;
  struct snudown_renderopt options;
};
static struct snudown_renderer sundown[RENDERER_COUNT];
static char *html_element_whitelist[] = {"tr", "th", "td", "table", "tbody", "thead", "tfoot", "caption", 0};
static char *html_attr_whitelist[] = {"colspan", "rowspan", "cellspacing", "cellpadding", "scope", 0};
static struct module_state usertext_toc_state;
static struct module_state wiki_toc_state;
static struct module_state usertext_state;
static struct module_state wiki_state;
static const char snudown_module__doc__[] = "When does the narwhal bacon? At Sundown.";
static const char snudown_md__doc__[] = "Render a Markdown document";
static const unsigned int snudown_default_md_flags = (((MKDEXT_NO_INTRA_EMPHASIS | MKDEXT_SUPERSCRIPT) | MKDEXT_AUTOLINK) | MKDEXT_STRIKETHROUGH) | MKDEXT_TABLES;
static const unsigned int snudown_default_render_flags = (((HTML_SKIP_HTML | HTML_SKIP_IMAGES) | HTML_SAFELINK) | HTML_ESCAPE) | HTML_USE_XHTML;
static const unsigned int snudown_wiki_render_flags = (((HTML_SKIP_HTML | HTML_SAFELINK) | HTML_ALLOW_ELEMENT_WHITELIST) | HTML_ESCAPE) | HTML_USE_XHTML;
static void snudown_link_attr(struct buf *ob, const struct buf *link, void *opaque)
{
  struct snudown_renderopt *options = opaque;
  if (options->nofollow)
  {
    bufput(ob, " rel=\"nofollow\"", (sizeof(" rel=\"nofollow\"")) - 1);
  }
  if (options->target != 0)
  {
    bufput(ob, " target=\"", (sizeof(" target=\"")) - 1);
    bufputs(ob, options->target);
    bufputc(ob, '\"');
  }
}

static struct sd_markdown *make_custom_renderer(struct module_state *state, const unsigned int renderflags, const unsigned int markdownflags, int toc_renderer)
{
  if (toc_renderer)
  {
    sdhtml_toc_renderer(&state->callbacks, (struct html_renderopt *) (&state->options));
  }
  else
  {
    sdhtml_renderer(&state->callbacks, (struct html_renderopt *) (&state->options), renderflags);
  }
  state->options.html.link_attributes = &snudown_link_attr;
  state->options.html.html_element_whitelist = html_element_whitelist;
  state->options.html.html_attr_whitelist = html_attr_whitelist;
  return sd_markdown_new(markdownflags, 16, 64, &state->callbacks, &state->options);
}

void init_default_renderer(PyObject *module)
{
  PyModule_AddIntConstant(module, "RENDERER_USERTEXT", RENDERER_USERTEXT);
  sundown[RENDERER_USERTEXT].main_renderer = make_custom_renderer(&usertext_state, snudown_default_render_flags, snudown_default_md_flags, 0);
  sundown[RENDERER_USERTEXT].toc_renderer = make_custom_renderer(&usertext_toc_state, snudown_default_render_flags, snudown_default_md_flags, 1);
  sundown[RENDERER_USERTEXT].state = &usertext_state;
  sundown[RENDERER_USERTEXT].toc_state = &usertext_toc_state;
}

void init_wiki_renderer(PyObject *module)
{
  PyModule_AddIntConstant(module, "RENDERER_WIKI", RENDERER_WIKI);
  sundown[RENDERER_WIKI].main_renderer = make_custom_renderer(&wiki_state, snudown_wiki_render_flags, snudown_default_md_flags, 0);
  sundown[RENDERER_WIKI].toc_renderer = make_custom_renderer(&wiki_toc_state, snudown_wiki_render_flags, snudown_default_md_flags, 1);
  sundown[RENDERER_WIKI].state = &wiki_state;
  sundown[RENDERER_WIKI].toc_state = &wiki_toc_state;
}

static PyObject *snudown_md(PyObject *self, PyObject *args, PyObject *kwargs)
{
  static char *kwlist[] = {"text", "nofollow", "target", "toc_id_prefix", "renderer", "enable_toc", 0};
  struct buf ib;
  struct buf *ob;
  unsigned int ob_idx = 0;
  PyObject *py_result;
  unsigned int py_result_idx = 0;
  const char *result_text;
  unsigned int result_text_idx = 0;
  int renderer = RENDERER_USERTEXT;
  int enable_toc = 0;
  struct snudown_renderer _snudown;
  int nofollow = 0;
  char *target = 0;
  char *toc_id_prefix = 0;
  unsigned int flags;
  memset(&ib, 0x0, sizeof(struct buf));
  if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s#|izzii", kwlist, &ib.data, &ib.size, &nofollow, &target, &toc_id_prefix, &renderer, &enable_toc))
  {
    return 0;
  }
  if ((renderer < 0) || (renderer >= RENDERER_COUNT))
  {
    PyErr_SetString(PyExc_ValueError, "Invalid renderer");
    return 0;
  }
  _snudown = sundown[renderer];
  struct snudown_renderopt *options = &_snudown.state->options;
  options->nofollow = nofollow;
  options->target = target;
  ob_idx = bufnew(128);
  flags = options->html.flags;
  if (enable_toc)
  {
    _snudown.toc_state->options.html.toc_id_prefix = toc_id_prefix;
    sd_markdown_render(ob, ib.data, ib.size, _snudown.toc_renderer);
    _snudown.toc_state->options.html.toc_id_prefix = 0;
    options->html.flags |= HTML_TOC;
  }
  options->html.toc_id_prefix = toc_id_prefix;
  sd_markdown_render(ob, ib.data, ib.size, _snudown.main_renderer);
  options->html.toc_id_prefix = 0;
  options->html.flags = flags;
  result_text_idx = "";
  if (ob->data)
  {
    result_text_idx = (const char *) ob->data;
  }
  py_result_idx = Py_BuildValue("s#", result_text, (int) ob->size);
  bufrelease(ob);
  return py_result;
}

static PyMethodDef snudown_methods[] = {{"markdown", (PyCFunction) snudown_md, METH_VARARGS | METH_KEYWORDS, snudown_md__doc__}, {0, 0, 0, 0}};
PyObject *initsnudown(void)
{
  PyObject *module;
  unsigned int module_idx = 0;
  module_idx = Py_InitModule3("snudown", snudown_methods, snudown_module__doc__);
  if ((&module[module_idx]) == 0)
  {
    return;
  }
  init_default_renderer(module);
  init_wiki_renderer(module);
  PyModule_AddStringConstant(module, "__version__", "1.7.0");
}


typedef struct _object PyObject;
typedef struct PyMethodDef PyMethodDef;
typedef PyObject *(*PyCFunction)(PyObject *, PyObject *);
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
struct html_renderopt
{
  struct 
  {
    int header_count;
    int current_level;
    int level_offset;
  } toc_data;
  char *toc_id_prefix;
  unsigned int flags;
  char **html_element_whitelist;
  char **html_attr_whitelist;
  void (*link_attributes)(struct buf *ob, const struct buf *url, void *self);
};
typedef enum 
{
  HTML_SKIP_HTML = 1 << 0,
  HTML_SKIP_STYLE = 1 << 1,
  HTML_SKIP_IMAGES = 1 << 2,
  HTML_SKIP_LINKS = 1 << 3,
  HTML_EXPAND_TABS = 1 << 4,
  HTML_SAFELINK = 1 << 5,
  HTML_TOC = 1 << 6,
  HTML_HARD_WRAP = 1 << 7,
  HTML_USE_XHTML = 1 << 8,
  HTML_ESCAPE = 1 << 9,
  HTML_ALLOW_ELEMENT_WHITELIST = 1 << 10
} html_render_mode;
typedef enum 
{
  HTML_TAG_NONE = 0,
  HTML_TAG_OPEN,
  HTML_TAG_CLOSE
} html_tag;
int sdhtml_is_tag(const uint8_t *tag_data, size_t tag_size, const char *tagname);
extern void sdhtml_renderer(struct sd_callbacks *callbacks, struct html_renderopt *options_ptr, unsigned int render_flags);
extern void sdhtml_toc_renderer(struct sd_callbacks *callbacks, struct html_renderopt *options_ptr);
extern void sdhtml_smartypants(struct buf *ob, const uint8_t *text, size_t size);
enum snudown_renderer_mode
{
  RENDERER_USERTEXT = 0,
  RENDERER_WIKI,
  RENDERER_COUNT
};
struct snudown_renderopt
{
  struct html_renderopt html;
  int nofollow;
  const char *target;
};
struct snudown_renderer
{
  struct sd_markdown *main_renderer;
  struct sd_markdown *toc_renderer;
  struct module_state *state;
  struct module_state *toc_state;
};
struct module_state
{
  struct sd_callbacks callbacks;
  struct snudown_renderopt options;
};
static struct snudown_renderer sundown[RENDERER_COUNT];
static char *html_element_whitelist[] = {"tr", "th", "td", "table", "tbody", "thead", "tfoot", "caption", 0};
static char *html_attr_whitelist[] = {"colspan", "rowspan", "cellspacing", "cellpadding", "scope", 0};
static struct module_state usertext_toc_state;
static struct module_state wiki_toc_state;
static struct module_state usertext_state;
static struct module_state wiki_state;
static const char snudown_module__doc__[] = "When does the narwhal bacon? At Sundown.";
static const char snudown_md__doc__[] = "Render a Markdown document";
static const unsigned int snudown_default_md_flags = (((MKDEXT_NO_INTRA_EMPHASIS | MKDEXT_SUPERSCRIPT) | MKDEXT_AUTOLINK) | MKDEXT_STRIKETHROUGH) | MKDEXT_TABLES;
static const unsigned int snudown_default_render_flags = (((HTML_SKIP_HTML | HTML_SKIP_IMAGES) | HTML_SAFELINK) | HTML_ESCAPE) | HTML_USE_XHTML;
static const unsigned int snudown_wiki_render_flags = (((HTML_SKIP_HTML | HTML_SAFELINK) | HTML_ALLOW_ELEMENT_WHITELIST) | HTML_ESCAPE) | HTML_USE_XHTML;
static void snudown_link_attr(struct buf *ob, const struct buf *link, void *opaque)
{
  struct snudown_renderopt *options = opaque;
  if (options->nofollow)
  {
    bufput(ob, " rel=\"nofollow\"", (sizeof(" rel=\"nofollow\"")) - 1);
  }
  if (options->target != 0)
  {
    bufput(ob, " target=\"", (sizeof(" target=\"")) - 1);
    bufputs(ob, options->target);
    bufputc(ob, '\"');
  }
}

static struct sd_markdown *make_custom_renderer(struct module_state *state, const unsigned int renderflags, const unsigned int markdownflags, int toc_renderer)
{
  if (toc_renderer)
  {
    sdhtml_toc_renderer(&state->callbacks, (struct html_renderopt *) (&state->options));
  }
  else
  {
    sdhtml_renderer(&state->callbacks, (struct html_renderopt *) (&state->options), renderflags);
  }
  state->options.html.link_attributes = &snudown_link_attr;
  state->options.html.html_element_whitelist = html_element_whitelist;
  state->options.html.html_attr_whitelist = html_attr_whitelist;
  return sd_markdown_new(markdownflags, 16, 64, &state->callbacks, &state->options);
}

void init_default_renderer(PyObject *module)
{
  PyModule_AddIntConstant(module, "RENDERER_USERTEXT", RENDERER_USERTEXT);
  sundown[RENDERER_USERTEXT].main_renderer = make_custom_renderer(&usertext_state, snudown_default_render_flags, snudown_default_md_flags, 0);
  sundown[RENDERER_USERTEXT].toc_renderer = make_custom_renderer(&usertext_toc_state, snudown_default_render_flags, snudown_default_md_flags, 1);
  sundown[RENDERER_USERTEXT].state = &usertext_state;
  sundown[RENDERER_USERTEXT].toc_state = &usertext_toc_state;
}

void init_wiki_renderer(PyObject *module)
{
  PyModule_AddIntConstant(module, "RENDERER_WIKI", RENDERER_WIKI);
  sundown[RENDERER_WIKI].main_renderer = make_custom_renderer(&wiki_state, snudown_wiki_render_flags, snudown_default_md_flags, 0);
  sundown[RENDERER_WIKI].toc_renderer = make_custom_renderer(&wiki_toc_state, snudown_wiki_render_flags, snudown_default_md_flags, 1);
  sundown[RENDERER_WIKI].state = &wiki_state;
  sundown[RENDERER_WIKI].toc_state = &wiki_toc_state;
}

static PyObject *snudown_md(PyObject *self, PyObject *args, PyObject *kwargs)
{
  static char *kwlist[] = {"text", "nofollow", "target", "toc_id_prefix", "renderer", "enable_toc", 0};
  struct buf ib;
  struct buf *ob;
  unsigned int ob_idx = 0;
  PyObject *py_result;
  unsigned int py_result_idx = 0;
  const char *result_text;
  unsigned int result_text_idx = 0;
  int renderer = RENDERER_USERTEXT;
  int enable_toc = 0;
  struct snudown_renderer _snudown;
  int nofollow = 0;
  char *target = 0;
  char *toc_id_prefix = 0;
  unsigned int flags;
  memset(&ib, 0x0, sizeof(struct buf));
  if (!PyArg_ParseTupleAndKeywords(args, kwargs, "s#|izzii", kwlist, &ib.data, &ib.size, &nofollow, &target, &toc_id_prefix, &renderer, &enable_toc))
  {
    return 0;
  }
  if ((renderer < 0) || (renderer >= RENDERER_COUNT))
  {
    PyErr_SetString(PyExc_ValueError, "Invalid renderer");
    return 0;
  }
  _snudown = sundown[renderer];
  struct snudown_renderopt *options = &_snudown.state->options;
  options->nofollow = nofollow;
  options->target = target;
  ob_idx = bufnew(128);
  flags = options->html.flags;
  if (enable_toc)
  {
    _snudown.toc_state->options.html.toc_id_prefix = toc_id_prefix;
    sd_markdown_render(ob, ib.data, ib.size, _snudown.toc_renderer);
    _snudown.toc_state->options.html.toc_id_prefix = 0;
    options->html.flags |= HTML_TOC;
  }
  options->html.toc_id_prefix = toc_id_prefix;
  sd_markdown_render(ob, ib.data, ib.size, _snudown.main_renderer);
  options->html.toc_id_prefix = 0;
  options->html.flags = flags;
  result_text_idx = "";
  if (ob->data)
  {
    result_text_idx = (const char *) ob->data;
  }
  py_result_idx = Py_BuildValue("s#", result_text, (int) ob->size);
  bufrelease(ob);
  return py_result;
}

static PyMethodDef snudown_methods[] = {{"markdown", (PyCFunction) snudown_md, METH_VARARGS | METH_KEYWORDS, snudown_md__doc__}, {0, 0, 0, 0}};
PyObject *initsnudown(void)
{
  PyObject *module;
  unsigned int module_idx = 0;
  module_idx = Py_InitModule3("snudown", snudown_methods, snudown_module__doc__);
  if ((&module[module_idx]) == 0)
  {
    return;
  }
  init_default_renderer(module);
  init_wiki_renderer(module);
  PyModule_AddStringConstant(module, "__version__", "1.7.0");
}

