static const char HREF_SAFE[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
/*** DEPENDENCIES:
***/


static const char HTML_ESCAPE_TABLE[] = {7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 7, 7, 0, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 0, 0, 1, 0, 0, 0, 2, 3, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
/*** DEPENDENCIES:
***/


static const char *HTML_ESCAPES[] = {"", "&quot;", "&amp;", "&#39;", "&#47;", "&lt;", "&gt;", ""}
/*** DEPENDENCIES:
***/


static const uint8_t smartypants_cb_chars[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 5, 3, 2, 0, 0, 0, 0, 1, 6, 0, 0, 7, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
/*** DEPENDENCIES:
***/


const unsigned MAX_NUM_ENTITY_VAL = 0x10ffff
/*** DEPENDENCIES:
***/


const size_t MAX_NUM_ENTITY_LEN = 7
/*** DEPENDENCIES:
***/


int sip_hash_key_init = 0
/*** DEPENDENCIES:
***/


uint8_t sip_hash_key[16]
/*** DEPENDENCIES:
***/


static char *html_element_whitelist[] = {"tr", "th", "td", "table", "tbody", "thead", "tfoot", "caption", 0}
/*** DEPENDENCIES:
***/


static char *html_attr_whitelist[] = {"colspan", "rowspan", "cellspacing", "cellpadding", "scope", 0}
/*** DEPENDENCIES:
***/


static const char snudown_module__doc__[] = "When does the narwhal bacon? At Sundown."
/*** DEPENDENCIES:
***/


static const char snudown_md__doc__[] = "Render a Markdown document"
/*** DEPENDENCIES:
***/


static const unsigned int snudown_default_md_flags = (((MKDEXT_NO_INTRA_EMPHASIS | MKDEXT_SUPERSCRIPT) | MKDEXT_AUTOLINK) | MKDEXT_STRIKETHROUGH) | MKDEXT_TABLES
/*** DEPENDENCIES:
***/


static const unsigned int snudown_default_render_flags = (((HTML_SKIP_HTML | HTML_SKIP_IMAGES) | HTML_SAFELINK) | HTML_ESCAPE) | HTML_USE_XHTML
/*** DEPENDENCIES:
***/


static const unsigned int snudown_wiki_render_flags = (((HTML_SKIP_HTML | HTML_SAFELINK) | HTML_ALLOW_ELEMENT_WHITELIST) | HTML_ESCAPE) | HTML_USE_XHTML
/*** DEPENDENCIES:
***/


static struct snudown_renderer sundown[RENDERER_COUNT]
/*** DEPENDENCIES:
struct snudown_renderer
{
  struct sd_markdown *main_renderer;
  struct sd_markdown *toc_renderer;
  struct module_state *state;
  struct module_state *toc_state;
}
----------------------------
***/


static struct module_state usertext_toc_state
/*** DEPENDENCIES:
struct module_state
{
  struct sd_callbacks callbacks;
  struct snudown_renderopt options;
}
----------------------------
***/


static struct module_state wiki_toc_state
/*** DEPENDENCIES:
struct module_state
{
  struct sd_callbacks callbacks;
  struct snudown_renderopt options;
}
----------------------------
***/


static struct module_state usertext_state
/*** DEPENDENCIES:
struct module_state
{
  struct sd_callbacks callbacks;
  struct snudown_renderopt options;
}
----------------------------
***/


static struct module_state wiki_state
/*** DEPENDENCIES:
struct module_state
{
  struct sd_callbacks callbacks;
  struct snudown_renderopt options;
}
----------------------------
***/


static char_trigger markdown_char_ptrs[] = {0, &char_emphasis, &char_codespan, &char_linebreak, &char_link, &char_langle_tag, &char_escape, &char_entity, &char_autolink_url, &char_autolink_email, &char_autolink_www, &char_autolink_subreddit_or_username, &char_superscript}
/*** DEPENDENCIES:
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


----------------------------
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


----------------------------
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


----------------------------
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


----------------------------
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


----------------------------
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


----------------------------
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


----------------------------
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


----------------------------
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


----------------------------
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


----------------------------
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


----------------------------
typedef size_t (*char_trigger)(struct buf *ob, struct sd_markdown *rndr, uint8_t *data, size_t max_rewind, size_t max_lookbehind, size_t size)
----------------------------
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


----------------------------
***/


static PyMethodDef snudown_methods[] = {{"markdown", (PyCFunction) snudown_md, METH_VARARGS | METH_KEYWORDS, snudown_md__doc__}, {0, 0, 0, 0}}
/*** DEPENDENCIES:
typedef struct PyMethodDef PyMethodDef
----------------------------
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


----------------------------
***/


static size_t (*smartypants_cb_ptrs[])(struct buf *, struct smartypants_data *, uint8_t, const uint8_t *, size_t) = {0, smartypants_cb__dash, smartypants_cb__parens, smartypants_cb__squote, smartypants_cb__dquote, smartypants_cb__amp, smartypants_cb__period, smartypants_cb__number, smartypants_cb__ltag, smartypants_cb__backtick, smartypants_cb__escape}
/*** DEPENDENCIES:
static size_t smartypants_cb__escape(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
  if (size < 2)
  {
    return 0;
  }
  switch (text[1])
  {
    case '\\':

    case '"':

    case '\'':

    case '.':

    case '-':

    case '`':
    {
      bufputc(ob, text[1]);
      return 1;
    }

    default:
    {
      bufputc(ob, '\\');
      return 0;
    }

  }

}


----------------------------
static size_t smartypants_cb__squote(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
  if (size >= 2)
  {
    uint8_t t1 = tolower(text[1]);
    if (t1 == '\'')
    {
      if (smartypants_quotes(ob, previous_char, (size >= 3) ? (text[2]) : (0), 'd', &smrt->in_dquote))
      {
        return 1;
      }
    }
    if (((((t1 == 's') || (t1 == 't')) || (t1 == 'm')) || (t1 == 'd')) && ((size == 3) || word_boundary(text[2])))
    {
      bufput(ob, "&rsquo;", (sizeof("&rsquo;")) - 1);
      return 0;
    }
    if (size >= 3)
    {
      uint8_t t2 = tolower(text[2]);
      if (((((t1 == 'r') && (t2 == 'e')) || ((t1 == 'l') && (t2 == 'l'))) || ((t1 == 'v') && (t2 == 'e'))) && ((size == 4) || word_boundary(text[3])))
      {
        bufput(ob, "&rsquo;", (sizeof("&rsquo;")) - 1);
        return 0;
      }
    }
  }
  if (smartypants_quotes(ob, previous_char, (size > 0) ? (text[1]) : (0), 's', &smrt->in_squote))
  {
    return 0;
  }
  bufputc(ob, text[0]);
  return 0;
}


----------------------------
static size_t smartypants_cb__dquote(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
  if (!smartypants_quotes(ob, previous_char, (size > 0) ? (text[1]) : (0), 'd', &smrt->in_dquote))
  {
    bufput(ob, "&quot;", (sizeof("&quot;")) - 1);
  }
  return 0;
}


----------------------------
static size_t smartypants_cb__number(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
  if (word_boundary(previous_char) && (size >= 3))
  {
    if (((text[0] == '1') && (text[1] == '/')) && (text[2] == '2'))
    {
      if ((size == 3) || word_boundary(text[3]))
      {
        bufput(ob, "&frac12;", (sizeof("&frac12;")) - 1);
        return 2;
      }
    }
    if (((text[0] == '1') && (text[1] == '/')) && (text[2] == '4'))
    {
      if (((size == 3) || word_boundary(text[3])) || (((size >= 5) && (tolower(text[3]) == 't')) && (tolower(text[4]) == 'h')))
      {
        bufput(ob, "&frac14;", (sizeof("&frac14;")) - 1);
        return 2;
      }
    }
    if (((text[0] == '3') && (text[1] == '/')) && (text[2] == '4'))
    {
      if (((size == 3) || word_boundary(text[3])) || ((((size >= 6) && (tolower(text[3]) == 't')) && (tolower(text[4]) == 'h')) && (tolower(text[5]) == 's')))
      {
        bufput(ob, "&frac34;", (sizeof("&frac34;")) - 1);
        return 2;
      }
    }
  }
  bufputc(ob, text[0]);
  return 0;
}


----------------------------
static size_t smartypants_cb__backtick(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
  if ((size >= 2) && (text[1] == '`'))
  {
    if (smartypants_quotes(ob, previous_char, (size >= 3) ? (text[2]) : (0), 'd', &smrt->in_dquote))
    {
      return 1;
    }
  }
  return 0;
}


----------------------------
struct smartypants_data
{
  int in_squote;
  int in_dquote;
}
----------------------------
static size_t smartypants_cb__period(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
  if (((size >= 3) && (text[1] == '.')) && (text[2] == '.'))
  {
    bufput(ob, "&hellip;", (sizeof("&hellip;")) - 1);
    return 2;
  }
  if (((((size >= 5) && (text[1] == ' ')) && (text[2] == '.')) && (text[3] == ' ')) && (text[4] == '.'))
  {
    bufput(ob, "&hellip;", (sizeof("&hellip;")) - 1);
    return 4;
  }
  bufputc(ob, text[0]);
  return 0;
}


----------------------------
static size_t smartypants_cb__dash(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
  if (((size >= 3) && (text[1] == '-')) && (text[2] == '-'))
  {
    bufput(ob, "&mdash;", (sizeof("&mdash;")) - 1);
    return 2;
  }
  if ((size >= 2) && (text[1] == '-'))
  {
    bufput(ob, "&ndash;", (sizeof("&ndash;")) - 1);
    return 1;
  }
  bufputc(ob, text[0]);
  return 0;
}


----------------------------
static size_t smartypants_cb__ltag(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
  static const char *skip_tags[] = {"pre", "code", "var", "samp", "kbd", "math", "script", "style"};
  static const size_t skip_tags_count = 8;
  size_t tag;
  size_t i = 0;
  while ((i < size) && (text[i] != '>'))
  {
    i += 1;
  }

  for (tag = 0; tag < skip_tags_count; tag += 1)
  {
    if (sdhtml_is_tag(text, size, skip_tags[tag]) == HTML_TAG_OPEN)
    {
      break;
    }
  }

  if (tag < skip_tags_count)
  {
    for (;;)
    {
      while ((i < size) && (text[i] != '<'))
      {
        i += 1;
      }

      if (i == size)
      {
        break;
      }
      if (sdhtml_is_tag(text + i, size - i, skip_tags[tag]) == HTML_TAG_CLOSE)
      {
        break;
      }
      i += 1;
    }

    while ((i < size) && (text[i] != '>'))
    {
      i += 1;
    }

  }
  bufput(ob, text, i + 1);
  return i;
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
static size_t smartypants_cb__amp(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
  if ((size >= 6) && (memcmp(text, "&quot;", 6) == 0))
  {
    if (smartypants_quotes(ob, previous_char, (size >= 7) ? (text[6]) : (0), 'd', &smrt->in_dquote))
    {
      return 5;
    }
  }
  if ((size >= 4) && (memcmp(text, "&#0;", 4) == 0))
  {
    return 3;
  }
  bufputc(ob, '&');
  return 0;
}


----------------------------
static size_t smartypants_cb__parens(struct buf *ob, struct smartypants_data *smrt, uint8_t previous_char, const uint8_t *text, size_t size)
{
  if (size >= 3)
  {
    uint8_t t1 = tolower(text[1]);
    uint8_t t2 = tolower(text[2]);
    if ((t1 == 'c') && (t2 == ')'))
    {
      bufput(ob, "&copy;", (sizeof("&copy;")) - 1);
      return 2;
    }
    if ((t1 == 'r') && (t2 == ')'))
    {
      bufput(ob, "&reg;", (sizeof("&reg;")) - 1);
      return 2;
    }
    if ((((size >= 4) && (t1 == 't')) && (t2 == 'm')) && (text[3] == ')'))
    {
      bufput(ob, "&trade;", (sizeof("&trade;")) - 1);
      return 3;
    }
  }
  bufputc(ob, text[0]);
  return 0;
}


----------------------------
***/


