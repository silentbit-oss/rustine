#include <assert.h>
#include <csv.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct csv_parser
{
  int pstate;
  int quoted;
  size_t spaces;
  unsigned char *entry_buf;
  size_t entry_pos;
  size_t entry_size;
  int status;
  unsigned char options;
  unsigned char quote_char;
  unsigned char delim_char;
  int (*is_space)(unsigned char);
  int (*is_term)(unsigned char);
  size_t blk_size;
  void *(*malloc_func)(size_t);
  void *(*realloc_func)(void *, size_t);
  void (*free_func)(void *);
};
int csv_init(struct csv_parser *p, unsigned char options);
int csv_fini(struct csv_parser *p, void (*cb1)(void *, size_t, void *), void (*cb2)(int, void *), void *data);
void csv_free(struct csv_parser *p);
int csv_error(const struct csv_parser *p);
const char *csv_strerror(int error);
size_t csv_parse(struct csv_parser *p, const void *s, size_t len, void (*cb1)(void *, size_t, void *), void (*cb2)(int, void *), void *data);
size_t csv_write(void *dest, size_t dest_size, const void *src, size_t src_size);
int csv_fwrite(FILE *fp, const void *src, size_t src_size);
size_t csv_write2(void *dest, size_t dest_size, const void *src, size_t src_size, unsigned char quote);
int csv_fwrite2(FILE *fp, const void *src, size_t src_size, unsigned char quote);
int csv_get_opts(const struct csv_parser *p);
int csv_set_opts(struct csv_parser *p, unsigned char options);
void csv_set_delim(struct csv_parser *p, unsigned char c);
void csv_set_quote(struct csv_parser *p, unsigned char c);
unsigned char csv_get_delim(const struct csv_parser *p);
unsigned char csv_get_quote(const struct csv_parser *p);
void csv_set_space_func(struct csv_parser *p, int (*f)(unsigned char));
void csv_set_term_func(struct csv_parser *p, int (*f)(unsigned char));
void csv_set_realloc_func(struct csv_parser *p, void *(*)(void *, size_t));
void csv_set_free_func(struct csv_parser *p, void (*)(void *));
void csv_set_blk_size(struct csv_parser *p, size_t);
size_t csv_get_buffer_size(const struct csv_parser *p);
static const char *csv_errors[] = {"success", "error parsing data while strict checking enabled", "memory exhausted while increasing buffer size", "data size too large", "invalid status code"};
int csv_error(const struct csv_parser *p)
{
  assert(p && "received null csv_parser");
  return p->status;
}

const char *csv_strerror(int status)
{
  if ((status >= 4) || (status < 0))
  {
    return csv_errors[4];
  }
  else
    return csv_errors[status];
}

int csv_get_opts(const struct csv_parser *p)
{
  if (p == 0)
  {
    return -1;
  }
  return p->options;
}

int csv_set_opts(struct csv_parser *p, unsigned char options)
{
  if (p == 0)
  {
    return -1;
  }
  p->options = options;
  return 0;
}

int csv_init(struct csv_parser *p, unsigned char options)
{
  if (p == 0)
  {
    return -1;
  }
  p->entry_buf = 0;
  p->pstate = 0;
  p->quoted = 0;
  p->spaces = 0;
  p->entry_pos = 0;
  p->entry_size = 0;
  p->status = 0;
  p->options = options;
  p->quote_char = 0x22;
  p->delim_char = 0x2c;
  p->is_space = 0;
  p->is_term = 0;
  p->blk_size = 128;
  p->malloc_func = 0;
  p->realloc_func = realloc;
  p->free_func = free;
  return 0;
}

void csv_free(struct csv_parser *p)
{
  if (p == 0)
  {
    return;
  }
  if (p->entry_buf && p->free_func)
  {
    p->free_func(p->entry_buf);
  }
  p->entry_buf = 0;
  p->entry_size = 0;
  return;
}

int csv_fini(struct csv_parser *p, void (*cb1)(void *, size_t, void *), void (*cb2)(int c, void *), void *data)
{
  if (p == 0)
  {
    return -1;
  }
  int quoted = p->quoted;
  int pstate = p->pstate;
  size_t spaces = p->spaces;
  size_t entry_pos = p->entry_pos;
  if ((((pstate == 2) && p->quoted) && (p->options & 1)) && (p->options & 4))
  {
    p->status = 1;
    return -1;
  }
  switch (pstate)
  {
    case 3:
      p->entry_pos -= p->spaces + 1;
      entry_pos = p->entry_pos;

    case 1:

    case 2:
      do
    {
      if (!quoted)
      {
        entry_pos -= spaces;
      }
      if (p->options & 8)
      {
        p->entry_buf[entry_pos] = '\0';
      }
      if (((cb1 && (p->options & 16)) && (!quoted)) && (entry_pos == 0))
      {
        cb1(0, entry_pos, data);
      }
      else
        if (cb1)
      {
        cb1(p->entry_buf, entry_pos, data);
      }
      pstate = 1;
      entry_pos = (quoted = (spaces = 0));
    }
    while (0);
      do
    {
      if (cb2)
      {
        cb2(-1, data);
      }
      pstate = 0;
      entry_pos = (quoted = (spaces = 0));
    }
    while (0);
      break;

    case 0:
      ;

  }

  p->spaces = (p->quoted = (p->entry_pos = (p->status = 0)));
  p->pstate = 0;
  return 0;
}

void csv_set_delim(struct csv_parser *p, unsigned char c)
{
  if (p)
  {
    p->delim_char = c;
  }
}

void csv_set_quote(struct csv_parser *p, unsigned char c)
{
  if (p)
  {
    p->quote_char = c;
  }
}

unsigned char csv_get_delim(const struct csv_parser *p)
{
  assert(p && "received null csv_parser");
  return p->delim_char;
}

unsigned char csv_get_quote(const struct csv_parser *p)
{
  assert(p && "received null csv_parser");
  return p->quote_char;
}

void csv_set_space_func(struct csv_parser *p, int (*f)(unsigned char))
{
  if (p)
  {
    p->is_space = f;
  }
}

void csv_set_term_func(struct csv_parser *p, int (*f)(unsigned char))
{
  if (p)
  {
    p->is_term = f;
  }
}

void csv_set_realloc_func(struct csv_parser *p, void *(*f)(void *, size_t))
{
  if (p && f)
  {
    p->realloc_func = f;
  }
}

void csv_set_free_func(struct csv_parser *p, void (*f)(void *))
{
  if (p && f)
  {
    p->free_func = f;
  }
}

void csv_set_blk_size(struct csv_parser *p, size_t size)
{
  if (p)
  {
    p->blk_size = size;
  }
}

size_t csv_get_buffer_size(const struct csv_parser *p)
{
  if (p)
  {
    return p->entry_size;
  }
  return 0;
}

static int csv_increase_buffer(struct csv_parser *p)
{
  if (p == 0)
  {
    return 0;
  }
  if (p->realloc_func == 0)
  {
    return 0;
  }
  size_t to_add = p->blk_size;
  void *vp;
  unsigned int vp_idx = 0;
  if (p->entry_size >= (SIZE_MAX - to_add))
  {
    to_add = SIZE_MAX - p->entry_size;
  }
  if (!to_add)
  {
    p->status = 3;
    return -1;
  }
  while ((vp_idx = p->realloc_func(p->entry_buf, p->entry_size + to_add)) == 0)
  {
    to_add /= 2;
    if (!to_add)
    {
      p->status = 2;
      return -1;
    }
  }

  p->entry_buf = &vp[vp_idx];
  p->entry_size += to_add;
  return 0;
}

size_t csv_parse(struct csv_parser *p, const void *s, size_t len, void (*cb1)(void *, size_t, void *), void (*cb2)(int c, void *), void *data)
{
  assert(p && "received null csv_parser");
  if (s == 0)
  {
    return 0;
  }
  const unsigned char *us = s;
  unsigned char c;
  size_t pos = 0;
  unsigned char delim = p->delim_char;
  unsigned char quote = p->quote_char;
  int (*is_space)(unsigned char) = p->is_space;
  int (*is_term)(unsigned char) = p->is_term;
  int quoted = p->quoted;
  int pstate = p->pstate;
  size_t spaces = p->spaces;
  size_t entry_pos = p->entry_pos;
  if ((!p->entry_buf) && (pos < len))
  {
    if (csv_increase_buffer(p) != 0)
    {
      p->quoted = quoted, p->pstate = pstate, p->spaces = spaces, p->entry_pos = entry_pos;
      return pos;
    }
  }
  while (pos < len)
  {
    if (entry_pos == ((p->options & 8) ? (p->entry_size - 1) : (p->entry_size)))
    {
      if (csv_increase_buffer(p) != 0)
      {
        p->quoted = quoted, p->pstate = pstate, p->spaces = spaces, p->entry_pos = entry_pos;
        return pos;
      }
    }
    c = us[pos];
    pos += 1;
    switch (pstate)
    {
      case 0:

      case 1:
        if (((is_space) ? (is_space(c)) : ((c == 0x20) || (c == 0x09))) && (c != delim))
      {
        continue;
      }
      else
        if ((is_term) ? (is_term(c)) : ((c == 0x0d) || (c == 0x0a)))
      {
        if (pstate == 1)
        {
          do
          {
            if (!quoted)
            {
              entry_pos -= spaces;
            }
            if (p->options & 8)
            {
              p->entry_buf[entry_pos] = '\0';
            }
            if (((cb1 && (p->options & 16)) && (!quoted)) && (entry_pos == 0))
            {
              cb1(0, entry_pos, data);
            }
            else
              if (cb1)
            {
              cb1(p->entry_buf, entry_pos, data);
            }
            pstate = 1;
            entry_pos = (quoted = (spaces = 0));
          }
          while (0);
          do
          {
            if (cb2)
            {
              cb2(c, data);
            }
            pstate = 0;
            entry_pos = (quoted = (spaces = 0));
          }
          while (0);
        }
        else
        {
          if (p->options & 2)
          {
            do
            {
              if (cb2)
              {
                cb2(c, data);
              }
              pstate = 0;
              entry_pos = (quoted = (spaces = 0));
            }
            while (0);
          }
        }
        continue;
      }
      else
        if (c == delim)
      {
        do
        {
          if (!quoted)
          {
            entry_pos -= spaces;
          }
          if (p->options & 8)
          {
            p->entry_buf[entry_pos] = '\0';
          }
          if (((cb1 && (p->options & 16)) && (!quoted)) && (entry_pos == 0))
          {
            cb1(0, entry_pos, data);
          }
          else
            if (cb1)
          {
            cb1(p->entry_buf, entry_pos, data);
          }
          pstate = 1;
          entry_pos = (quoted = (spaces = 0));
        }
        while (0);
        break;
      }
      else
        if (c == quote)
      {
        pstate = 2;
        quoted = 1;
      }
      else
      {
        pstate = 2;
        quoted = 0;
        p->entry_buf[entry_pos] = c;
        entry_pos += 1;
      }
        break;

      case 2:
        if (c == quote)
      {
        if (quoted)
        {
          p->entry_buf[entry_pos] = c;
          entry_pos += 1;
          pstate = 3;
        }
        else
        {
          if (p->options & 1)
          {
            p->status = 1;
            p->quoted = quoted, p->pstate = pstate, p->spaces = spaces, p->entry_pos = entry_pos;
            return pos - 1;
          }
          p->entry_buf[entry_pos] = c;
          entry_pos += 1;
          spaces = 0;
        }
      }
      else
        if (c == delim)
      {
        if (quoted)
        {
          p->entry_buf[entry_pos] = c;
          entry_pos += 1;
        }
        else
        {
          do
          {
            if (!quoted)
            {
              entry_pos -= spaces;
            }
            if (p->options & 8)
            {
              p->entry_buf[entry_pos] = '\0';
            }
            if (((cb1 && (p->options & 16)) && (!quoted)) && (entry_pos == 0))
            {
              cb1(0, entry_pos, data);
            }
            else
              if (cb1)
            {
              cb1(p->entry_buf, entry_pos, data);
            }
            pstate = 1;
            entry_pos = (quoted = (spaces = 0));
          }
          while (0);
        }
      }
      else
        if ((is_term) ? (is_term(c)) : ((c == 0x0d) || (c == 0x0a)))
      {
        if (!quoted)
        {
          do
          {
            if (!quoted)
            {
              entry_pos -= spaces;
            }
            if (p->options & 8)
            {
              p->entry_buf[entry_pos] = '\0';
            }
            if (((cb1 && (p->options & 16)) && (!quoted)) && (entry_pos == 0))
            {
              cb1(0, entry_pos, data);
            }
            else
              if (cb1)
            {
              cb1(p->entry_buf, entry_pos, data);
            }
            pstate = 1;
            entry_pos = (quoted = (spaces = 0));
          }
          while (0);
          do
          {
            if (cb2)
            {
              cb2(c, data);
            }
            pstate = 0;
            entry_pos = (quoted = (spaces = 0));
          }
          while (0);
        }
        else
        {
          p->entry_buf[entry_pos] = c;
          entry_pos += 1;
        }
      }
      else
        if ((!quoted) && ((is_space) ? (is_space(c)) : ((c == 0x20) || (c == 0x09))))
      {
        p->entry_buf[entry_pos] = c;
        entry_pos += 1;
        spaces += 1;
      }
      else
      {
        p->entry_buf[entry_pos] = c;
        entry_pos += 1;
        spaces = 0;
      }
        break;

      case 3:
        if (c == delim)
      {
        entry_pos -= spaces + 1;
        do
        {
          if (!quoted)
          {
            entry_pos -= spaces;
          }
          if (p->options & 8)
          {
            p->entry_buf[entry_pos] = '\0';
          }
          if (((cb1 && (p->options & 16)) && (!quoted)) && (entry_pos == 0))
          {
            cb1(0, entry_pos, data);
          }
          else
            if (cb1)
          {
            cb1(p->entry_buf, entry_pos, data);
          }
          pstate = 1;
          entry_pos = (quoted = (spaces = 0));
        }
        while (0);
      }
      else
        if ((is_term) ? (is_term(c)) : ((c == 0x0d) || (c == 0x0a)))
      {
        entry_pos -= spaces + 1;
        do
        {
          if (!quoted)
          {
            entry_pos -= spaces;
          }
          if (p->options & 8)
          {
            p->entry_buf[entry_pos] = '\0';
          }
          if (((cb1 && (p->options & 16)) && (!quoted)) && (entry_pos == 0))
          {
            cb1(0, entry_pos, data);
          }
          else
            if (cb1)
          {
            cb1(p->entry_buf, entry_pos, data);
          }
          pstate = 1;
          entry_pos = (quoted = (spaces = 0));
        }
        while (0);
        do
        {
          if (cb2)
          {
            cb2(c, data);
          }
          pstate = 0;
          entry_pos = (quoted = (spaces = 0));
        }
        while (0);
      }
      else
        if ((is_space) ? (is_space(c)) : ((c == 0x20) || (c == 0x09)))
      {
        p->entry_buf[entry_pos] = c;
        entry_pos += 1;
        spaces += 1;
      }
      else
        if (c == quote)
      {
        if (spaces)
        {
          if (p->options & 1)
          {
            p->status = 1;
            p->quoted = quoted, p->pstate = pstate, p->spaces = spaces, p->entry_pos = entry_pos;
            return pos - 1;
          }
          spaces = 0;
          p->entry_buf[entry_pos] = c;
          entry_pos += 1;
        }
        else
        {
          pstate = 2;
        }
      }
      else
      {
        if (p->options & 1)
        {
          p->status = 1;
          p->quoted = quoted, p->pstate = pstate, p->spaces = spaces, p->entry_pos = entry_pos;
          return pos - 1;
        }
        pstate = 2;
        spaces = 0;
        p->entry_buf[entry_pos] = c;
        entry_pos += 1;
      }
        break;

      default:
        break;

    }

  }

  p->quoted = quoted, p->pstate = pstate, p->spaces = spaces, p->entry_pos = entry_pos;
  return pos;
}

size_t csv_write(void *dest, size_t dest_size, const void *src, size_t src_size)
{
  return csv_write2(dest, dest_size, src, src_size, 0x22);
}

int csv_fwrite(FILE *fp, const void *src, size_t src_size)
{
  return csv_fwrite2(fp, src, src_size, 0x22);
}

size_t csv_write2(void *dest, size_t dest_size, const void *src, size_t src_size, unsigned char quote)
{
  unsigned char *cdest = dest;
  unsigned int cdest_idx = 0;
  const unsigned char *csrc = src;
  unsigned int csrc_idx = 0;
  size_t chars = 0;
  if (src == 0)
  {
    return 0;
  }
  if (dest == 0)
  {
    dest_size = 0;
  }
  if (dest_size > 0)
  {
    cdest[cdest_idx] = quote;
    cdest_idx += 1;
  }
  chars += 1;
  while (src_size)
  {
    if (csrc[csrc_idx] == quote)
    {
      if (dest_size > chars)
      {
        cdest[cdest_idx] = quote;
        cdest_idx += 1;
      }
      if (chars < SIZE_MAX)
      {
        chars += 1;
      }
    }
    if (dest_size > chars)
    {
      cdest[cdest_idx] = csrc[csrc_idx];
      cdest_idx += 1;
    }
    if (chars < SIZE_MAX)
    {
      chars += 1;
    }
    src_size -= 1;
    csrc_idx += 1;
  }

  if (dest_size > chars)
  {
    cdest[cdest_idx] = quote;
  }
  if (chars < SIZE_MAX)
  {
    chars += 1;
  }
  return chars;
}

int csv_fwrite2(FILE *fp, const void *src, size_t src_size, unsigned char quote)
{
  const unsigned char *csrc = src;
  unsigned int csrc_idx = 0;
  if ((fp == 0) || (src == 0))
  {
    return 0;
  }
  if (fputc(quote, fp) == EOF)
  {
    return EOF;
  }
  while (src_size)
  {
    if (csrc[csrc_idx] == quote)
    {
      if (fputc(quote, fp) == EOF)
      {
        return EOF;
      }
    }
    if (fputc(*(&csrc[csrc_idx]), fp) == EOF)
    {
      return EOF;
    }
    src_size -= 1;
    csrc_idx += 1;
  }

  if (fputc(quote, fp) == EOF)
  {
    return EOF;
  }
  return 0;
}

