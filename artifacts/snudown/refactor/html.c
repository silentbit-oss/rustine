#include <autolink.h>
#include <buffer.h>
#include <ctype.h>
#include <houdini.h>
#include <html.h>
#include <markdown.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
extern void houdini_escape_html(struct buf *ob, const uint8_t *src, size_t size);
extern void houdini_escape_html0(struct buf *ob, const uint8_t *src, size_t size, int secure);
extern void houdini_unescape_html(struct buf *ob, const uint8_t *src, size_t size);
extern void houdini_escape_xml(struct buf *ob, const uint8_t *src, size_t size);
extern void houdini_escape_uri(struct buf *ob, const uint8_t *src, size_t size);
extern void houdini_escape_url(struct buf *ob, const uint8_t *src, size_t size);
extern void houdini_escape_href(struct buf *ob, const uint8_t *src, size_t size);
extern void houdini_unescape_uri(struct buf *ob, const uint8_t *src, size_t size);
extern void houdini_unescape_url(struct buf *ob, const uint8_t *src, size_t size);
extern void houdini_escape_js(struct buf *ob, const uint8_t *src, size_t size);
extern void houdini_unescape_js(struct buf *ob, const uint8_t *src, size_t size);
int sdhtml_is_tag(const uint8_t *tag_data, size_t tag_size, const char *tagname)
{
  unsigned int tagname_idx = 0;
  size_t i;
  int closed = 0;
  if ((tag_size < 3) || (tag_data[0] != '<'))
  {
    return HTML_TAG_NONE;
  }
  i = 1;
  if (tag_data[i] == '/')
  {
    closed = 1;
    i += 1;
  }
  for (; i < tag_size; i += 1, tagname_idx += 1)
  {
    if (tagname[tagname_idx] == 0)
    {
      break;
    }
    if (tag_data[i] != tagname[tagname_idx])
    {
      return HTML_TAG_NONE;
    }
  }

  if (i == tag_size)
  {
    return HTML_TAG_NONE;
  }
  if (isspace(tag_data[i]) || (tag_data[i] == '>'))
  {
    return (closed) ? (HTML_TAG_CLOSE) : (HTML_TAG_OPEN);
  }
  return HTML_TAG_NONE;
}

inline static void escape_html(struct buf *ob, const uint8_t *source, size_t length)
{
  houdini_escape_html0(ob, source, length, 0);
}

inline static void escape_href(struct buf *ob, const uint8_t *source, size_t length)
{
  houdini_escape_href(ob, source, length);
}

static int rndr_autolink(struct buf *ob, const struct buf *link, enum mkd_autolink type, void *opaque)
{
  struct html_renderopt *options = opaque;
  uint8_t offset = 0;
  if ((!link) || (!link->size))
  {
    return 0;
  }
  if ((((options->flags & HTML_SAFELINK) != 0) && (!sd_autolink_issafe(link->data, link->size))) && (type != MKDA_EMAIL))
  {
    return 0;
  }
  bufput(ob, "<a href=\"", (sizeof("<a href=\"")) - 1);
  if (type == MKDA_EMAIL)
  {
    bufput(ob, "mailto:", (sizeof("mailto:")) - 1);
  }
  escape_href(ob, link->data + offset, link->size - offset);
  if (options->link_attributes)
  {
    bufputc(ob, '\"');
    options->link_attributes(ob, link, opaque);
    bufputc(ob, '>');
  }
  else
  {
    bufput(ob, "\">", (sizeof("\">")) - 1);
  }
  if (bufprefix(link, "mailto:") == 0)
  {
    escape_html(ob, link->data + 7, link->size - 7);
  }
  else
  {
    escape_html(ob, link->data, link->size);
  }
  bufput(ob, "</a>", (sizeof("</a>")) - 1);
  return 1;
}

static void rndr_blockcode(struct buf *ob, const struct buf *text, const struct buf *lang, void *opaque)
{
  if (ob->size)
  {
    bufputc(ob, '\n');
  }
  if (lang && lang->size)
  {
    size_t i;
    size_t cls;
    bufput(ob, "<pre><code class=\"", (sizeof("<pre><code class=\"")) - 1);
    for (i = 0, cls = 0; i < lang->size; i += 1, cls += 1)
    {
      while ((i < lang->size) && isspace(lang->data[i]))
      {
        i += 1;
      }

      if (i < lang->size)
      {
        size_t org = i;
        while ((i < lang->size) && (!isspace(lang->data[i])))
        {
          i += 1;
        }

        if (lang->data[org] == '.')
        {
          org += 1;
        }
        if (cls)
        {
          bufputc(ob, ' ');
        }
        escape_html(ob, lang->data + org, i - org);
      }
    }

    bufput(ob, "\">", (sizeof("\">")) - 1);
  }
  else
    bufput(ob, "<pre><code>", (sizeof("<pre><code>")) - 1);
  if (text)
  {
    escape_html(ob, text->data, text->size);
  }
  bufput(ob, "</code></pre>\n", (sizeof("</code></pre>\n")) - 1);
}

static void rndr_blockquote(struct buf *ob, const struct buf *text, void *opaque)
{
  if (ob->size)
  {
    bufputc(ob, '\n');
  }
  bufput(ob, "<blockquote>\n", (sizeof("<blockquote>\n")) - 1);
  if (text)
  {
    bufput(ob, text->data, text->size);
  }
  bufput(ob, "</blockquote>\n", (sizeof("</blockquote>\n")) - 1);
}

static void rndr_blockspoiler(struct buf *ob, const struct buf *text, void *opaque)
{
  if (ob->size)
  {
    bufputc(ob, '\n');
  }
  bufput(ob, "<blockquote class=\"md-spoiler-text\">\n", (sizeof("<blockquote class=\"md-spoiler-text\">\n")) - 1);
  if (text)
  {
    bufput(ob, text->data, text->size);
  }
  bufput(ob, "</blockquote>\n", (sizeof("</blockquote>\n")) - 1);
}

static int rndr_codespan(struct buf *ob, const struct buf *text, void *opaque)
{
  bufput(ob, "<code>", (sizeof("<code>")) - 1);
  if (text)
  {
    escape_html(ob, text->data, text->size);
  }
  bufput(ob, "</code>", (sizeof("</code>")) - 1);
  return 1;
}

static int rndr_spoilerspan(struct buf *ob, const struct buf *text, void *opaque)
{
  if ((!text) || (!text->size))
  {
    return 0;
  }
  bufput(ob, "<span class=\"md-spoiler-text\">", (sizeof("<span class=\"md-spoiler-text\">")) - 1);
  bufput(ob, text->data, text->size);
  bufput(ob, "</span>", (sizeof("</span>")) - 1);
  return 1;
}

static int rndr_strikethrough(struct buf *ob, const struct buf *text, void *opaque)
{
  if ((!text) || (!text->size))
  {
    return 0;
  }
  bufput(ob, "<del>", (sizeof("<del>")) - 1);
  bufput(ob, text->data, text->size);
  bufput(ob, "</del>", (sizeof("</del>")) - 1);
  return 1;
}

static int rndr_double_emphasis(struct buf *ob, const struct buf *text, void *opaque)
{
  if ((!text) || (!text->size))
  {
    return 0;
  }
  bufput(ob, "<strong>", (sizeof("<strong>")) - 1);
  bufput(ob, text->data, text->size);
  bufput(ob, "</strong>", (sizeof("</strong>")) - 1);
  return 1;
}

static int rndr_emphasis(struct buf *ob, const struct buf *text, void *opaque)
{
  if ((!text) || (!text->size))
  {
    return 0;
  }
  bufput(ob, "<em>", (sizeof("<em>")) - 1);
  if (text)
  {
    bufput(ob, text->data, text->size);
  }
  bufput(ob, "</em>", (sizeof("</em>")) - 1);
  return 1;
}

static int rndr_linebreak(struct buf *ob, void *opaque)
{
  struct html_renderopt *options = opaque;
  bufputs(ob, (options->flags & HTML_USE_XHTML) ? ("<br/>\n") : ("<br>\n"));
  return 1;
}

static void rndr_header(struct buf *ob, const struct buf *text, int level, void *opaque)
{
  struct html_renderopt *options = opaque;
  if (ob->size)
  {
    bufputc(ob, '\n');
  }
  if (options->flags & HTML_TOC)
  {
    bufprintf(ob, "<h%d id=\"", level);
    if (options->toc_id_prefix)
    {
      bufputs(ob, options->toc_id_prefix);
    }
    bufprintf(ob, "toc_%d\">", options->toc_data.header_count++);
  }
  else
  {
    bufprintf(ob, "<h%d>", level);
  }
  if (text)
  {
    bufput(ob, text->data, text->size);
  }
  bufprintf(ob, "</h%d>\n", level);
}

static int rndr_link(struct buf *ob, const struct buf *link, const struct buf *title, const struct buf *content, void *opaque)
{
  struct html_renderopt *options = opaque;
  if (((link != 0) && ((options->flags & HTML_SAFELINK) != 0)) && (!sd_autolink_issafe(link->data, link->size)))
  {
    return 0;
  }
  bufput(ob, "<a href=\"", (sizeof("<a href=\"")) - 1);
  if (link && link->size)
  {
    escape_href(ob, link->data, link->size);
  }
  if (title && title->size)
  {
    bufput(ob, "\" title=\"", (sizeof("\" title=\"")) - 1);
    escape_html(ob, title->data, title->size);
  }
  if (options->link_attributes)
  {
    bufputc(ob, '\"');
    options->link_attributes(ob, link, opaque);
    bufputc(ob, '>');
  }
  else
  {
    bufput(ob, "\">", (sizeof("\">")) - 1);
  }
  if (content && content->size)
  {
    bufput(ob, content->data, content->size);
  }
  bufput(ob, "</a>", (sizeof("</a>")) - 1);
  return 1;
}

static void rndr_list(struct buf *ob, const struct buf *text, int flags, void *opaque)
{
  if (ob->size)
  {
    bufputc(ob, '\n');
  }
  bufput(ob, (flags & 1) ? ("<ol>\n") : ("<ul>\n"), 5);
  if (text)
  {
    bufput(ob, text->data, text->size);
  }
  bufput(ob, (flags & 1) ? ("</ol>\n") : ("</ul>\n"), 6);
}

static void rndr_listitem(struct buf *ob, const struct buf *text, int flags, void *opaque)
{
  bufput(ob, "<li>", (sizeof("<li>")) - 1);
  if (text)
  {
    size_t size = text->size;
    while (size && (text->data[size - 1] == '\n'))
    {
      size -= 1;
    }

    bufput(ob, text->data, size);
  }
  bufput(ob, "</li>\n", (sizeof("</li>\n")) - 1);
}

static void rndr_paragraph(struct buf *ob, const struct buf *text, void *opaque)
{
  struct html_renderopt *options = opaque;
  size_t i = 0;
  if (ob->size)
  {
    bufputc(ob, '\n');
  }
  if ((!text) || (!text->size))
  {
    return;
  }
  while ((i < text->size) && isspace(text->data[i]))
  {
    i += 1;
  }

  if (i == text->size)
  {
    return;
  }
  bufput(ob, "<p>", (sizeof("<p>")) - 1);
  if (options->flags & HTML_HARD_WRAP)
  {
    size_t org;
    while (i < text->size)
    {
      org = i;
      while ((i < text->size) && (text->data[i] != '\n'))
      {
        i += 1;
      }

      if (i > org)
      {
        bufput(ob, text->data + org, i - org);
      }
      if (i >= (text->size - 1))
      {
        break;
      }
      rndr_linebreak(ob, opaque);
      i += 1;
    }

  }
  else
  {
    bufput(ob, &text->data[i], text->size - i);
  }
  bufput(ob, "</p>\n", (sizeof("</p>\n")) - 1);
}

static void rndr_raw_block(struct buf *ob, const struct buf *text, void *opaque)
{
  size_t org;
  size_t sz;
  if (!text)
  {
    return;
  }
  sz = text->size;
  while ((sz > 0) && (text->data[sz - 1] == '\n'))
  {
    sz -= 1;
  }

  org = 0;
  while ((org < sz) && (text->data[org] == '\n'))
  {
    org += 1;
  }

  if (org >= sz)
  {
    return;
  }
  if (ob->size)
  {
    bufputc(ob, '\n');
  }
  bufput(ob, text->data + org, sz - org);
  bufputc(ob, '\n');
}

static int rndr_triple_emphasis(struct buf *ob, const struct buf *text, void *opaque)
{
  if ((!text) || (!text->size))
  {
    return 0;
  }
  bufput(ob, "<strong><em>", (sizeof("<strong><em>")) - 1);
  bufput(ob, text->data, text->size);
  bufput(ob, "</em></strong>", (sizeof("</em></strong>")) - 1);
  return 1;
}

static void rndr_hrule(struct buf *ob, void *opaque)
{
  struct html_renderopt *options = opaque;
  if (ob->size)
  {
    bufputc(ob, '\n');
  }
  bufputs(ob, (options->flags & HTML_USE_XHTML) ? ("<hr/>\n") : ("<hr>\n"));
}

static int rndr_image(struct buf *ob, const struct buf *link, const struct buf *title, const struct buf *alt, void *opaque)
{
  struct html_renderopt *options = opaque;
  if ((!link) || (!link->size))
  {
    return 0;
  }
  bufput(ob, "<img src=\"", (sizeof("<img src=\"")) - 1);
  escape_href(ob, link->data, link->size);
  bufput(ob, "\" alt=\"", (sizeof("\" alt=\"")) - 1);
  if (alt && alt->size)
  {
    escape_html(ob, alt->data, alt->size);
  }
  if (title && title->size)
  {
    bufput(ob, "\" title=\"", (sizeof("\" title=\"")) - 1);
    escape_html(ob, title->data, title->size);
  }
  bufputs(ob, (options->flags & HTML_USE_XHTML) ? ("\"/>") : ("\">"));
  return 1;
}

static void rndr_html_tag(struct buf *ob, const struct buf *text, void *opaque, char *tagname, char **whitelist, int tagtype)
{
  size_t i;
  size_t x;
  size_t z;
  size_t in_str = 0;
  size_t seen_equals = 0;
  size_t done = 0;
  size_t done_attr = 0;
  size_t reset = 0;
  struct buf *attr;
  unsigned int attr_idx = 0;
  struct buf *value;
  unsigned int value_idx = 0;
  char c;
  bufputc(ob, '<');
  if (tagtype == HTML_TAG_CLOSE)
  {
    bufputc(ob, '/');
    bufputs(ob, tagname);
    bufputc(ob, '>');
    return;
  }
  bufputs(ob, tagname);
  i = 1 + strlen(tagname);
  attr_idx = bufnew(16);
  value_idx = bufnew(16);
  for (; (i < text->size) && (!done); i += 1)
  {
    helper_rndr_html_tag_1(&x, &z, &in_str, &seen_equals, &done, &done_attr, &reset, &c, ob, text, whitelist, i, attr, value);
  }

  bufrelease(attr);
  bufrelease(value);
  bufputc(ob, '>');
}

static int rndr_raw_html(struct buf *ob, const struct buf *text, void *opaque)
{
  struct html_renderopt *options = opaque;
  char **whitelist = options->html_element_whitelist;
  int i;
  int tagtype;
  if (((options->flags & HTML_ALLOW_ELEMENT_WHITELIST) != 0) && whitelist)
  {
    for (i = 0; whitelist[i]; i += 1)
    {
      tagtype = sdhtml_is_tag(text->data, text->size, whitelist[i]);
      if (tagtype != HTML_TAG_NONE)
      {
        rndr_html_tag(ob, text, opaque, whitelist[i], options->html_attr_whitelist, tagtype);
        return 1;
      }
    }

  }
  if ((options->flags & HTML_ESCAPE) != 0)
  {
    escape_html(ob, text->data, text->size);
    return 1;
  }
  if ((options->flags & HTML_SKIP_HTML) != 0)
  {
    return 1;
  }
  if (((options->flags & HTML_SKIP_STYLE) != 0) && sdhtml_is_tag(text->data, text->size, "style"))
  {
    return 1;
  }
  if (((options->flags & HTML_SKIP_LINKS) != 0) && sdhtml_is_tag(text->data, text->size, "a"))
  {
    return 1;
  }
  if (((options->flags & HTML_SKIP_IMAGES) != 0) && sdhtml_is_tag(text->data, text->size, "img"))
  {
    return 1;
  }
  bufput(ob, text->data, text->size);
  return 1;
}

static void rndr_table(struct buf *ob, const struct buf *header, const struct buf *body, void *opaque)
{
  if (ob->size)
  {
    bufputc(ob, '\n');
  }
  bufput(ob, "<table><thead>\n", (sizeof("<table><thead>\n")) - 1);
  if (header)
  {
    bufput(ob, header->data, header->size);
  }
  bufput(ob, "</thead><tbody>\n", (sizeof("</thead><tbody>\n")) - 1);
  if (body)
  {
    bufput(ob, body->data, body->size);
  }
  bufput(ob, "</tbody></table>\n", (sizeof("</tbody></table>\n")) - 1);
}

static void rndr_tablerow(struct buf *ob, const struct buf *text, void *opaque)
{
  bufput(ob, "<tr>\n", (sizeof("<tr>\n")) - 1);
  if (text)
  {
    bufput(ob, text->data, text->size);
  }
  bufput(ob, "</tr>\n", (sizeof("</tr>\n")) - 1);
}

static void rndr_tablecell(struct buf *ob, const struct buf *text, int flags, void *opaque, int col_span)
{
  if (flags & MKD_TABLE_HEADER)
  {
    bufput(ob, "<th", (sizeof("<th")) - 1);
  }
  else
  {
    bufput(ob, "<td", (sizeof("<td")) - 1);
  }
  if (col_span > 1)
  {
    bufprintf(ob, " colspan=\"%d\" ", col_span);
  }
  switch (flags & MKD_TABLE_ALIGNMASK)
  {
    case MKD_TABLE_ALIGN_CENTER:
    {
      bufput(ob, " align=\"center\">", (sizeof(" align=\"center\">")) - 1);
      break;
    }

    case MKD_TABLE_ALIGN_L:
    {
      bufput(ob, " align=\"left\">", (sizeof(" align=\"left\">")) - 1);
      break;
    }

    case MKD_TABLE_ALIGN_R:
    {
      bufput(ob, " align=\"right\">", (sizeof(" align=\"right\">")) - 1);
      break;
    }

    default:
    {
      bufput(ob, ">", (sizeof(">")) - 1);
    }

  }

  if (text)
  {
    bufput(ob, text->data, text->size);
  }
  if (flags & MKD_TABLE_HEADER)
  {
    bufput(ob, "</th>\n", (sizeof("</th>\n")) - 1);
  }
  else
  {
    bufput(ob, "</td>\n", (sizeof("</td>\n")) - 1);
  }
}

static int rndr_superscript(struct buf *ob, const struct buf *text, void *opaque)
{
  if ((!text) || (!text->size))
  {
    return 0;
  }
  bufput(ob, "<sup>", (sizeof("<sup>")) - 1);
  bufput(ob, text->data, text->size);
  bufput(ob, "</sup>", (sizeof("</sup>")) - 1);
  return 1;
}

static void rndr_normal_text(struct buf *ob, const struct buf *text, void *opaque)
{
  if (text)
  {
    escape_html(ob, text->data, text->size);
  }
}

static void toc_header(struct buf *ob, const struct buf *text, int level, void *opaque)
{
  struct html_renderopt *options = opaque;
  if (options->toc_data.current_level == 0)
  {
    bufput(ob, "<div class=\"toc\">\n", (sizeof("<div class=\"toc\">\n")) - 1);
    options->toc_data.level_offset = level - 1;
  }
  level -= options->toc_data.level_offset;
  if (level > options->toc_data.current_level)
  {
    while (level > options->toc_data.current_level)
    {
      bufput(ob, "<ul>\n<li>\n", (sizeof("<ul>\n<li>\n")) - 1);
      options->toc_data.current_level += 1;
    }

  }
  else
    if (level < options->toc_data.current_level)
  {
    bufput(ob, "</li>\n", (sizeof("</li>\n")) - 1);
    while (level < options->toc_data.current_level)
    {
      bufput(ob, "</ul>\n</li>\n", (sizeof("</ul>\n</li>\n")) - 1);
      options->toc_data.current_level -= 1;
    }

    bufput(ob, "<li>\n", (sizeof("<li>\n")) - 1);
  }
  else
  {
    bufput(ob, "</li>\n<li>\n", (sizeof("</li>\n<li>\n")) - 1);
  }
  bufput(ob, "<a href=\"#", (sizeof("<a href=\"#")) - 1);
  if (options->toc_id_prefix)
  {
    bufputs(ob, options->toc_id_prefix);
  }
  bufprintf(ob, "toc_%d\">", options->toc_data.header_count++);
  if (text)
  {
    escape_html(ob, text->data, text->size);
  }
  bufput(ob, "</a>\n", (sizeof("</a>\n")) - 1);
}

static int toc_link(struct buf *ob, const struct buf *link, const struct buf *title, const struct buf *content, void *opaque)
{
  if (content && content->size)
  {
    bufput(ob, content->data, content->size);
  }
  return 1;
}

static void reset_toc(struct buf *ob, void *opaque)
{
  struct html_renderopt *options = opaque;
  memset(&options->toc_data, 0, sizeof(options->toc_data));
}

static void toc_finalize(struct buf *ob, void *opaque)
{
  struct html_renderopt *options = opaque;
  bool has_toc = 0;
  while (options->toc_data.current_level > 0)
  {
    bufput(ob, "</li>\n</ul>\n", (sizeof("</li>\n</ul>\n")) - 1);
    options->toc_data.current_level -= 1;
    has_toc = 1;
  }

  if (has_toc)
  {
    bufput(ob, "</div>\n", (sizeof("</div>\n")) - 1);
  }
  reset_toc(ob, opaque);
}

void sdhtml_toc_renderer(struct sd_callbacks *callbacks, struct html_renderopt *options)
{
  static const struct sd_callbacks cb_default = {0, 0, 0, toc_header, 0, 0, 0, 0, 0, 0, 0, 0, rndr_codespan, rndr_spoilerspan, rndr_double_emphasis, rndr_emphasis, 0, 0, toc_link, 0, rndr_triple_emphasis, rndr_strikethrough, rndr_superscript, 0, 0, 0, toc_finalize};
  memset(options, 0x0, sizeof(struct html_renderopt));
  options->flags = HTML_TOC | HTML_SKIP_HTML;
  memcpy(callbacks, &cb_default, sizeof(struct sd_callbacks));
}

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

void helper_rndr_html_tag_1(size_t * const x_ref, size_t * const z_ref, size_t * const in_str_ref, size_t * const seen_equals_ref, size_t * const done_ref, size_t * const done_attr_ref, size_t * const reset_ref, char * const c_ref, struct buf * const ob, const struct buf * const text, char ** const whitelist, size_t i, struct buf * const attr, struct buf * const value)
{
  size_t x = *x_ref;
  size_t z = *z_ref;
  size_t in_str = *in_str_ref;
  size_t seen_equals = *seen_equals_ref;
  size_t done = *done_ref;
  size_t done_attr = *done_attr_ref;
  size_t reset = *reset_ref;
  char c = *c_ref;
  c = text->data[i];
  done = 0;
  reset = 0;
  done_attr = 0;
  switch (c)
  {
    case '>':
    {
      done = 1;
      break;
    }

    case '\'':

    case '"':
    {
      if (!seen_equals)
      {
        reset = 1;
      }
      else
        if (!in_str)
      {
        in_str = c;
      }
      else
        if (in_str == c)
      {
        in_str = 0;
        done_attr = 1;
      }
      else
      {
        bufputc(value, c);
      }
      break;
    }

    case ' ':
    {
      if (in_str)
      {
        bufputc(value, ' ');
      }
      else
      {
        reset = 1;
      }
      break;
    }

    case '=':
    {
      if (seen_equals)
      {
        reset = 1;
        break;
      }
      seen_equals = 1;
      break;
    }

    default:
    {
      if ((seen_equals && in_str) || (!seen_equals))
      {
        bufputc((seen_equals) ? (value) : (attr), c);
      }
      break;
    }

  }

  if (done_attr)
  {
    helper_helper_rndr_html_tag_1_1(&x, &z, &reset, ob, whitelist, attr, value);
  }
  if (reset)
  {
    seen_equals = 0;
    in_str = 0;
    bufreset(attr);
    bufreset(value);
  }
  *x_ref = x;
  *z_ref = z;
  *in_str_ref = in_str;
  *seen_equals_ref = seen_equals;
  *done_ref = done;
  *done_attr_ref = done_attr;
  *reset_ref = reset;
  *c_ref = c;
}

void helper_helper_rndr_html_tag_1_1(size_t * const x_ref, size_t * const z_ref, size_t * const reset_ref, struct buf * const ob, char ** const whitelist, struct buf * const attr, struct buf * const value)
{
  size_t x = *x_ref;
  size_t z = *z_ref;
  size_t reset = *reset_ref;
  int valid = 0;
  for (z = 0; whitelist[z]; z += 1)
  {
    if (strlen(whitelist[z]) != attr->size)
    {
      continue;
    }
    for (x = 0; x < attr->size; x += 1)
    {
      if (tolower(whitelist[z][x]) != tolower(attr->data[x]))
      {
        break;
      }
    }

    if (x == attr->size)
    {
      valid = 1;
      break;
    }
  }

  if ((valid && value->size) && attr->size)
  {
    bufputc(ob, ' ');
    escape_html(ob, attr->data, attr->size);
    bufputs(ob, "=\"");
    escape_html(ob, value->data, value->size);
    bufputc(ob, '"');
  }
  reset = 1;
  *x_ref = x;
  *z_ref = z;
  *reset_ref = reset;
}

