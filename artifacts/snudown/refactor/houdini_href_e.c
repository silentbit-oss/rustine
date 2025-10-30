#include <assert.h>
#include <buffer.h>
#include <houdini.h>
#include <houdini_href_e.c>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
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
static const char HREF_SAFE[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
void houdini_escape_href(struct buf *ob, const uint8_t *src, size_t size)
{
  static const char hex_chars[] = "0123456789ABCDEF";
  size_t i = 0;
  size_t org;
  char hex_str[3];
  bufgrow(ob, (size * 12) / 10);
  hex_str[0] = '%';
  while (i < size)
  {
    org = i;
    while ((i < size) && (HREF_SAFE[src[i]] == 1))
    {
      i += 1;
    }

    if (i > org)
    {
      bufput(ob, src + org, i - org);
    }
    if (i >= size)
    {
      break;
    }
    if (HREF_SAFE[src[i]] == 2)
    {
      i += 1;
      continue;
    }
    switch (src[i])
    {
      case '&':
      {
        bufput(ob, "&amp;", (sizeof("&amp;")) - 1);
        break;
      }

      case '\'':
      {
        bufput(ob, "&#x27;", (sizeof("&#x27;")) - 1);
        break;
      }

      default:
      {
        hex_str[1] = hex_chars[(src[i] >> 4) & 0xF];
        hex_str[2] = hex_chars[src[i] & 0xF];
        bufput(ob, hex_str, 3);
      }

    }

    i += 1;
  }

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
static const char HREF_SAFE[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 2, 2, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
void houdini_escape_href(struct buf *ob, const uint8_t *src, size_t size)
{
  static const char hex_chars[] = "0123456789ABCDEF";
  size_t i = 0;
  size_t org;
  char hex_str[3];
  bufgrow(ob, (size * 12) / 10);
  hex_str[0] = '%';
  while (i < size)
  {
    org = i;
    while ((i < size) && (HREF_SAFE[src[i]] == 1))
    {
      i += 1;
    }

    if (i > org)
    {
      bufput(ob, src + org, i - org);
    }
    if (i >= size)
    {
      break;
    }
    if (HREF_SAFE[src[i]] == 2)
    {
      i += 1;
      continue;
    }
    switch (src[i])
    {
      case '&':
        bufput(ob, "&amp;", (sizeof("&amp;")) - 1);
        break;

      case '\'':
        bufput(ob, "&#x27;", (sizeof("&#x27;")) - 1);
        break;

      default:
        hex_str[1] = hex_chars[(src[i] >> 4) & 0xF];
        hex_str[2] = hex_chars[src[i] & 0xF];
        bufput(ob, hex_str, 3);

    }

    i += 1;
  }

}

