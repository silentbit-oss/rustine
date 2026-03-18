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


/*** DEPENDENCIES:
struct snudown_renderer
{
  struct sd_markdown *main_renderer;
  struct sd_markdown *toc_renderer;
  struct module_state *state;
  struct module_state *toc_state;
}
----------------------------
typedef struct _object PyObject
----------------------------
static struct snudown_renderer sundown[RENDERER_COUNT]
----------------------------
struct snudown_renderopt
{
  struct html_renderopt html;
  int nofollow;
  const char *target;
}
----------------------------
void bufrelease(struct buf *buf)
{
  if (!buf)
  {
    return;
  }
  free(buf->data);
  free(buf);
}


----------------------------
struct buf
{
  uint8_t *data;
  size_t size;
  size_t asize;
  size_t unit;
}
----------------------------
struct buf *bufnew(size_t unit)
{
  struct buf *ret;
  unsigned int ret_idx = 0;
  ret_idx = malloc(sizeof(struct buf));
  if (ret)
  {
    ret->data = 0;
    ret->size = (ret->asize = 0);
    ret->unit = unit;
  }
  return ret;
}


----------------------------
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


----------------------------
***/


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


/*** DEPENDENCIES:
void bufputc(struct buf *buf, int c)
{
  assert(buf && buf->unit);
  if (((buf->size + 1) > buf->asize) && (bufgrow(buf, buf->size + 1) < 0))
  {
    return;
  }
  buf->data[buf->size] = c;
  buf->size += 1;
}


----------------------------
void bufput(struct buf *buf, const void *data, size_t len)
{
  assert(buf && buf->unit);
  if (((buf->size + len) > buf->asize) && (bufgrow(buf, buf->size + len) < 0))
  {
    return;
  }
  memcpy(buf->data + buf->size, data, len);
  buf->size += len;
}


----------------------------
void bufputs(struct buf *buf, const char *str)
{
  bufput(buf, str, strlen(str));
}


----------------------------
struct snudown_renderopt
{
  struct html_renderopt html;
  int nofollow;
  const char *target;
}
----------------------------
struct buf
{
  uint8_t *data;
  size_t size;
  size_t asize;
  size_t unit;
}
----------------------------
***/


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


/*** DEPENDENCIES:
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
}
----------------------------
void sdhtml_renderer(struct sd_callbacks *callbacks, struct html_renderopt *options, unsigned int render_flags)
{
  static const struct sd_callbacks cb_default = {rndr_blockcode, rndr_blockquote, rndr_blockspoiler, rndr_raw_block, rndr_header, rndr_hrule, rndr_list, rndr_listitem, rndr_paragraph, rndr_table, rndr_tablerow, rndr_tablecell, rndr_autolink, rndr_codespan, rndr_spoilerspan, rndr_double_emphasis, rndr_emphasis, rndr_image, rndr_linebreak, rndr_link, rndr_raw_html, rndr_triple_emphasis, rndr_strikethrough, rndr_superscript, 0, rndr_normal_text, 0, reset_toc};
  memset(options, 0x0, sizeof(struct html_renderopt));
  options->flags = render_flags;
  memcpy(callbacks, &cb_default, sizeof(struct sd_callbacks));
  if (render_flags & HTML_SKIP_IMAGES)
  {
    callbacks->image = 0;
  }
  if (render_flags & HTML_SKIP_LINKS)
  {
    callbacks->link = 0;
    callbacks->autolink = 0;
  }
  if ((render_flags & HTML_SKIP_HTML) || (render_flags & HTML_ESCAPE))
  {
    callbacks->blockhtml = 0;
  }
}


----------------------------
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


----------------------------
struct module_state
{
  struct sd_callbacks callbacks;
  struct snudown_renderopt options;
}
----------------------------
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


----------------------------
static char *html_attr_whitelist[] = {"colspan", "rowspan", "cellspacing", "cellpadding", "scope", 0}
----------------------------
static char *html_element_whitelist[] = {"tr", "th", "td", "table", "tbody", "thead", "tfoot", "caption", 0}
----------------------------
void sdhtml_toc_renderer(struct sd_callbacks *callbacks, struct html_renderopt *options)
{
  static const struct sd_callbacks cb_default = {0, 0, 0, toc_header, 0, 0, 0, 0, 0, 0, 0, 0, rndr_codespan, rndr_spoilerspan, rndr_double_emphasis, rndr_emphasis, 0, 0, toc_link, 0, rndr_triple_emphasis, rndr_strikethrough, rndr_superscript, 0, 0, 0, toc_finalize};
  memset(options, 0x0, sizeof(struct html_renderopt));
  options->flags = HTML_TOC | HTML_SKIP_HTML;
  memcpy(callbacks, &cb_default, sizeof(struct sd_callbacks));
}


----------------------------
***/


void init_default_renderer(PyObject *module)
{
  PyModule_AddIntConstant(module, "RENDERER_USERTEXT", RENDERER_USERTEXT);
  sundown[RENDERER_USERTEXT].main_renderer = make_custom_renderer(&usertext_state, snudown_default_render_flags, snudown_default_md_flags, 0);
  sundown[RENDERER_USERTEXT].toc_renderer = make_custom_renderer(&usertext_toc_state, snudown_default_render_flags, snudown_default_md_flags, 1);
  sundown[RENDERER_USERTEXT].state = &usertext_state;
  sundown[RENDERER_USERTEXT].toc_state = &usertext_toc_state;
}


/*** DEPENDENCIES:
static struct module_state usertext_state
----------------------------
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


----------------------------
typedef struct _object PyObject
----------------------------
static struct module_state usertext_toc_state
----------------------------
static struct snudown_renderer sundown[RENDERER_COUNT]
----------------------------
static const unsigned int snudown_default_render_flags = (((HTML_SKIP_HTML | HTML_SKIP_IMAGES) | HTML_SAFELINK) | HTML_ESCAPE) | HTML_USE_XHTML
----------------------------
static const unsigned int snudown_default_md_flags = (((MKDEXT_NO_INTRA_EMPHASIS | MKDEXT_SUPERSCRIPT) | MKDEXT_AUTOLINK) | MKDEXT_STRIKETHROUGH) | MKDEXT_TABLES
----------------------------
***/


void init_wiki_renderer(PyObject *module)
{
  PyModule_AddIntConstant(module, "RENDERER_WIKI", RENDERER_WIKI);
  sundown[RENDERER_WIKI].main_renderer = make_custom_renderer(&wiki_state, snudown_wiki_render_flags, snudown_default_md_flags, 0);
  sundown[RENDERER_WIKI].toc_renderer = make_custom_renderer(&wiki_toc_state, snudown_wiki_render_flags, snudown_default_md_flags, 1);
  sundown[RENDERER_WIKI].state = &wiki_state;
  sundown[RENDERER_WIKI].toc_state = &wiki_toc_state;
}


/*** DEPENDENCIES:
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


----------------------------
typedef struct _object PyObject
----------------------------
static const unsigned int snudown_wiki_render_flags = (((HTML_SKIP_HTML | HTML_SAFELINK) | HTML_ALLOW_ELEMENT_WHITELIST) | HTML_ESCAPE) | HTML_USE_XHTML
----------------------------
static struct module_state wiki_toc_state
----------------------------
static struct snudown_renderer sundown[RENDERER_COUNT]
----------------------------
static const unsigned int snudown_default_md_flags = (((MKDEXT_NO_INTRA_EMPHASIS | MKDEXT_SUPERSCRIPT) | MKDEXT_AUTOLINK) | MKDEXT_STRIKETHROUGH) | MKDEXT_TABLES
----------------------------
static struct module_state wiki_state
----------------------------
***/


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


/*** DEPENDENCIES:
void init_default_renderer(PyObject *module)
{
  PyModule_AddIntConstant(module, "RENDERER_USERTEXT", RENDERER_USERTEXT);
  sundown[RENDERER_USERTEXT].main_renderer = make_custom_renderer(&usertext_state, snudown_default_render_flags, snudown_default_md_flags, 0);
  sundown[RENDERER_USERTEXT].toc_renderer = make_custom_renderer(&usertext_toc_state, snudown_default_render_flags, snudown_default_md_flags, 1);
  sundown[RENDERER_USERTEXT].state = &usertext_state;
  sundown[RENDERER_USERTEXT].toc_state = &usertext_toc_state;
}


----------------------------
static const char snudown_module__doc__[] = "When does the narwhal bacon? At Sundown."
----------------------------
typedef struct _object PyObject
----------------------------
static PyMethodDef snudown_methods[] = {{"markdown", (PyCFunction) snudown_md, METH_VARARGS | METH_KEYWORDS, snudown_md__doc__}, {0, 0, 0, 0}}
----------------------------
void init_wiki_renderer(PyObject *module)
{
  PyModule_AddIntConstant(module, "RENDERER_WIKI", RENDERER_WIKI);
  sundown[RENDERER_WIKI].main_renderer = make_custom_renderer(&wiki_state, snudown_wiki_render_flags, snudown_default_md_flags, 0);
  sundown[RENDERER_WIKI].toc_renderer = make_custom_renderer(&wiki_toc_state, snudown_wiki_render_flags, snudown_default_md_flags, 1);
  sundown[RENDERER_WIKI].state = &wiki_state;
  sundown[RENDERER_WIKI].toc_state = &wiki_toc_state;
}


----------------------------
***/


