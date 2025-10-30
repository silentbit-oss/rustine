// hint:  ['dst_idx_ref is a mutable refrence to unsigned int']
void helper_vis_1(unsigned int * const dst_idx_ref, char * const dst, int c, int nextc)
{
  unsigned int dst_idx = *dst_idx_ref;
  switch (c)
  {
    case '\n':
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
      dst[dst_idx] = 'n';
      dst_idx += 1;
      goto done;
    }

    case '\r':
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
      dst[dst_idx] = 'r';
      dst_idx += 1;
      goto done;
    }

    case '\b':
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
      dst[dst_idx] = 'b';
      dst_idx += 1;
      goto done;
    }

    case '\a':
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
      dst[dst_idx] = 'a';
      dst_idx += 1;
      goto done;
    }

    case '\v':
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
      dst[dst_idx] = 'v';
      dst_idx += 1;
      goto done;
    }

    case '\t':
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
      dst[dst_idx] = 't';
      dst_idx += 1;
      goto done;
    }

    case '\f':
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
      dst[dst_idx] = 'f';
      dst_idx += 1;
      goto done;
    }

    case ' ':
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
      dst[dst_idx] = 's';
      dst_idx += 1;
      goto done;
    }

    case '\0':
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
      dst[dst_idx] = '0';
      dst_idx += 1;
      if ((((u_char) nextc) >= '0') && (((u_char) nextc) <= '7'))
      {
        dst[dst_idx] = '0';
        dst_idx += 1;
        dst[dst_idx] = '0';
        dst_idx += 1;
      }
      goto done;
    }

  }

  *dst_idx_ref = dst_idx;
}


/*** DEPENDENCIES:
***/


char *vis(char *dst, int c, int flag, int nextc)
{
  unsigned int dst_idx = 0;
  if (((c == '\\') || ((flag & 0x400) == 0)) && ((((((((((u_int) c) <= 255) && isascii((u_char) c)) && (((((c != '*') && (c != '?')) && (c != '[')) && (c != '#')) || ((flag & 0x100) == 0))) && isgraph((u_char) c)) || (((flag & 0x04) == 0) && (c == ' '))) || (((flag & 0x08) == 0) && (c == '\t'))) || (((flag & 0x10) == 0) && (c == '\n'))) || ((flag & 0x20) && ((((c == '\b') || (c == '\007')) || (c == '\r')) || isgraph((u_char) c)))))
  {
    if (((c == '"') && ((flag & 0x200) != 0)) || ((c == '\\') && ((flag & 0x40) == 0)))
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
    }
    dst[dst_idx] = c;
    dst_idx += 1;
    dst[dst_idx] = '\0';
    return dst;
  }
  if (flag & 0x02)
  {
    helper_vis_1(&dst_idx, dst, c, nextc);
  }
  if ((((c & 0177) == ' ') || (flag & 0x01)) || ((flag & 0x100) && ((((c == '*') || (c == '?')) || (c == '[')) || (c == '#'))))
  {
    dst[dst_idx] = '\\';
    dst_idx += 1;
    dst[dst_idx] = ((((u_char) c) >> 6) & 07) + '0';
    dst_idx += 1;
    dst[dst_idx] = ((((u_char) c) >> 3) & 07) + '0';
    dst_idx += 1;
    dst[dst_idx] = (((u_char) c) & 07) + '0';
    dst_idx += 1;
    goto done;
  }
  if ((flag & 0x40) == 0)
  {
    dst[dst_idx] = '\\';
    dst_idx += 1;
  }
  if (c & 0200)
  {
    c &= 0177;
    dst[dst_idx] = 'M';
    dst_idx += 1;
  }
  if (iscntrl((u_char) c))
  {
    dst[dst_idx] = '^';
    dst_idx += 1;
    if (c == 0177)
    {
      dst[dst_idx] = '?';
      dst_idx += 1;
    }
    else
      dst[dst_idx] = c + '@';
    dst_idx += 1;
  }
  else
  {
    dst[dst_idx] = '-';
    dst_idx += 1;
    dst[dst_idx] = c;
    dst_idx += 1;
  }
  done:
  dst[dst_idx] = '\0';

  return dst;
}


/*** DEPENDENCIES:
void helper_vis_1(unsigned int * const dst_idx_ref, char * const dst, int c, int nextc)
{
  unsigned int dst_idx = *dst_idx_ref;
  switch (c)
  {
    case '\n':
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
      dst[dst_idx] = 'n';
      dst_idx += 1;
      goto done;
    }

    case '\r':
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
      dst[dst_idx] = 'r';
      dst_idx += 1;
      goto done;
    }

    case '\b':
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
      dst[dst_idx] = 'b';
      dst_idx += 1;
      goto done;
    }

    case '\a':
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
      dst[dst_idx] = 'a';
      dst_idx += 1;
      goto done;
    }

    case '\v':
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
      dst[dst_idx] = 'v';
      dst_idx += 1;
      goto done;
    }

    case '\t':
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
      dst[dst_idx] = 't';
      dst_idx += 1;
      goto done;
    }

    case '\f':
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
      dst[dst_idx] = 'f';
      dst_idx += 1;
      goto done;
    }

    case ' ':
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
      dst[dst_idx] = 's';
      dst_idx += 1;
      goto done;
    }

    case '\0':
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
      dst[dst_idx] = '0';
      dst_idx += 1;
      if ((((u_char) nextc) >= '0') && (((u_char) nextc) <= '7'))
      {
        dst[dst_idx] = '0';
        dst_idx += 1;
        dst[dst_idx] = '0';
        dst_idx += 1;
      }
      goto done;
    }

  }

  *dst_idx_ref = dst_idx;
}


----------------------------
***/


int strvis(char *dst, const char *src, int flag)
{
  unsigned int src_idx = 0;
  unsigned int dst_idx = 0;
  char c;
  char *start;
  unsigned int start_idx = 0;
  for (start_idx = &dst[dst_idx]; c = src[src_idx];)
  {
    src_idx += 1;
    dst_idx = vis(dst_idx, c, flag, *(&src[src_idx]));
  }

  dst[dst_idx] = '\0';
  return (&dst[dst_idx]) - (&start[start_idx]);
}


/*** DEPENDENCIES:
char *vis(char *dst, int c, int flag, int nextc)
{
  unsigned int dst_idx = 0;
  if (((c == '\\') || ((flag & 0x400) == 0)) && ((((((((((u_int) c) <= 255) && isascii((u_char) c)) && (((((c != '*') && (c != '?')) && (c != '[')) && (c != '#')) || ((flag & 0x100) == 0))) && isgraph((u_char) c)) || (((flag & 0x04) == 0) && (c == ' '))) || (((flag & 0x08) == 0) && (c == '\t'))) || (((flag & 0x10) == 0) && (c == '\n'))) || ((flag & 0x20) && ((((c == '\b') || (c == '\007')) || (c == '\r')) || isgraph((u_char) c)))))
  {
    if (((c == '"') && ((flag & 0x200) != 0)) || ((c == '\\') && ((flag & 0x40) == 0)))
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
    }
    dst[dst_idx] = c;
    dst_idx += 1;
    dst[dst_idx] = '\0';
    return dst;
  }
  if (flag & 0x02)
  {
    helper_vis_1(&dst_idx, dst, c, nextc);
  }
  if ((((c & 0177) == ' ') || (flag & 0x01)) || ((flag & 0x100) && ((((c == '*') || (c == '?')) || (c == '[')) || (c == '#'))))
  {
    dst[dst_idx] = '\\';
    dst_idx += 1;
    dst[dst_idx] = ((((u_char) c) >> 6) & 07) + '0';
    dst_idx += 1;
    dst[dst_idx] = ((((u_char) c) >> 3) & 07) + '0';
    dst_idx += 1;
    dst[dst_idx] = (((u_char) c) & 07) + '0';
    dst_idx += 1;
    goto done;
  }
  if ((flag & 0x40) == 0)
  {
    dst[dst_idx] = '\\';
    dst_idx += 1;
  }
  if (c & 0200)
  {
    c &= 0177;
    dst[dst_idx] = 'M';
    dst_idx += 1;
  }
  if (iscntrl((u_char) c))
  {
    dst[dst_idx] = '^';
    dst_idx += 1;
    if (c == 0177)
    {
      dst[dst_idx] = '?';
      dst_idx += 1;
    }
    else
      dst[dst_idx] = c + '@';
    dst_idx += 1;
  }
  else
  {
    dst[dst_idx] = '-';
    dst_idx += 1;
    dst[dst_idx] = c;
    dst_idx += 1;
  }
  done:
  dst[dst_idx] = '\0';

  return dst;
}


----------------------------
***/


int stravis(char **outp, const char *src, int flag)
{
  char *buf;
  unsigned int buf_idx = 0;
  int len;
  int serrno;
  buf_idx = calloc(4, strlen(src) + 1);
  if ((&buf[buf_idx]) == 0)
  {
    return -1;
  }
  len = strvis(buf, src, flag);
  serrno = errno;
  *outp = realloc(buf, len + 1);
  if ((*outp) == 0)
  {
    *outp = &buf[buf_idx];
    errno = serrno;
  }
  return len;
}


/*** DEPENDENCIES:
int strvis(char *dst, const char *src, int flag)
{
  unsigned int src_idx = 0;
  unsigned int dst_idx = 0;
  char c;
  char *start;
  unsigned int start_idx = 0;
  for (start_idx = &dst[dst_idx]; c = src[src_idx];)
  {
    src_idx += 1;
    dst_idx = vis(dst_idx, c, flag, *(&src[src_idx]));
  }

  dst[dst_idx] = '\0';
  return (&dst[dst_idx]) - (&start[start_idx]);
}


----------------------------
***/


int strvisx(char *dst, const char *src, size_t len, int flag)
{
  unsigned int src_idx = 0;
  unsigned int dst_idx = 0;
  char c;
  char *start;
  unsigned int start_idx = 0;
  for (start_idx = &dst[dst_idx]; len > 1; len -= 1)
  {
    c = src[src_idx];
    src_idx += 1;
    dst_idx = vis(dst_idx, c, flag, *(&src[src_idx]));
  }

  if (len)
  {
    dst_idx = vis(dst_idx, *(&src[src_idx]), flag, '\0');
  }
  dst[dst_idx] = '\0';
  return (&dst[dst_idx]) - (&start[start_idx]);
}


/*** DEPENDENCIES:
char *vis(char *dst, int c, int flag, int nextc)
{
  unsigned int dst_idx = 0;
  if (((c == '\\') || ((flag & 0x400) == 0)) && ((((((((((u_int) c) <= 255) && isascii((u_char) c)) && (((((c != '*') && (c != '?')) && (c != '[')) && (c != '#')) || ((flag & 0x100) == 0))) && isgraph((u_char) c)) || (((flag & 0x04) == 0) && (c == ' '))) || (((flag & 0x08) == 0) && (c == '\t'))) || (((flag & 0x10) == 0) && (c == '\n'))) || ((flag & 0x20) && ((((c == '\b') || (c == '\007')) || (c == '\r')) || isgraph((u_char) c)))))
  {
    if (((c == '"') && ((flag & 0x200) != 0)) || ((c == '\\') && ((flag & 0x40) == 0)))
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
    }
    dst[dst_idx] = c;
    dst_idx += 1;
    dst[dst_idx] = '\0';
    return dst;
  }
  if (flag & 0x02)
  {
    helper_vis_1(&dst_idx, dst, c, nextc);
  }
  if ((((c & 0177) == ' ') || (flag & 0x01)) || ((flag & 0x100) && ((((c == '*') || (c == '?')) || (c == '[')) || (c == '#'))))
  {
    dst[dst_idx] = '\\';
    dst_idx += 1;
    dst[dst_idx] = ((((u_char) c) >> 6) & 07) + '0';
    dst_idx += 1;
    dst[dst_idx] = ((((u_char) c) >> 3) & 07) + '0';
    dst_idx += 1;
    dst[dst_idx] = (((u_char) c) & 07) + '0';
    dst_idx += 1;
    goto done;
  }
  if ((flag & 0x40) == 0)
  {
    dst[dst_idx] = '\\';
    dst_idx += 1;
  }
  if (c & 0200)
  {
    c &= 0177;
    dst[dst_idx] = 'M';
    dst_idx += 1;
  }
  if (iscntrl((u_char) c))
  {
    dst[dst_idx] = '^';
    dst_idx += 1;
    if (c == 0177)
    {
      dst[dst_idx] = '?';
      dst_idx += 1;
    }
    else
      dst[dst_idx] = c + '@';
    dst_idx += 1;
  }
  else
  {
    dst[dst_idx] = '-';
    dst_idx += 1;
    dst[dst_idx] = c;
    dst_idx += 1;
  }
  done:
  dst[dst_idx] = '\0';

  return dst;
}


----------------------------
***/


// hint:  ['src_idx_ref is a mutable refrence to unsigned int', 'dst_idx_ref is a mutable refrence to unsigned int', 'i_ref is a mutable refrence to int']
void helper_strnvis_1(unsigned int * const src_idx_ref, unsigned int * const dst_idx_ref, int * const i_ref, char * const dst, const char * const src, int flag, char * const end, unsigned int end_idx, char tbuf[5], int c)
{
  unsigned int src_idx = *src_idx_ref;
  unsigned int dst_idx = *dst_idx_ref;
  int i = *i_ref;
  if (((c == '\\') || ((flag & 0x400) == 0)) && ((((((((((u_int) c) <= 255) && isascii((u_char) c)) && (((((c != '*') && (c != '?')) && (c != '[')) && (c != '#')) || ((flag & 0x100) == 0))) && isgraph((u_char) c)) || (((flag & 0x04) == 0) && (c == ' '))) || (((flag & 0x08) == 0) && (c == '\t'))) || (((flag & 0x10) == 0) && (c == '\n'))) || ((flag & 0x20) && ((((c == '\b') || (c == '\007')) || (c == '\r')) || isgraph((u_char) c)))))
  {
    if (((c == '"') && ((flag & 0x200) != 0)) || ((c == '\\') && ((flag & 0x40) == 0)))
    {
      if (((&dst[dst_idx]) + 1) >= (&end[end_idx]))
      {
        i = 2;
        break;
      }
      dst[dst_idx] = '\\';
      dst_idx += 1;
    }
    i = 1;
    dst[dst_idx] = c;
    dst_idx += 1;
    src_idx += 1;
  }
  else
  {
    src_idx += 1;
    i = vis(tbuf, c, flag, *(&src[src_idx])) - tbuf;
    if (((&dst[dst_idx]) + i) <= (&end[end_idx]))
    {
      memcpy(dst, tbuf, i);
      dst_idx += i;
    }
    else
    {
      src_idx -= 1;
      break;
    }
  }
  *src_idx_ref = src_idx;
  *dst_idx_ref = dst_idx;
  *i_ref = i;
}


/*** DEPENDENCIES:
char *vis(char *dst, int c, int flag, int nextc)
{
  unsigned int dst_idx = 0;
  if (((c == '\\') || ((flag & 0x400) == 0)) && ((((((((((u_int) c) <= 255) && isascii((u_char) c)) && (((((c != '*') && (c != '?')) && (c != '[')) && (c != '#')) || ((flag & 0x100) == 0))) && isgraph((u_char) c)) || (((flag & 0x04) == 0) && (c == ' '))) || (((flag & 0x08) == 0) && (c == '\t'))) || (((flag & 0x10) == 0) && (c == '\n'))) || ((flag & 0x20) && ((((c == '\b') || (c == '\007')) || (c == '\r')) || isgraph((u_char) c)))))
  {
    if (((c == '"') && ((flag & 0x200) != 0)) || ((c == '\\') && ((flag & 0x40) == 0)))
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
    }
    dst[dst_idx] = c;
    dst_idx += 1;
    dst[dst_idx] = '\0';
    return dst;
  }
  if (flag & 0x02)
  {
    helper_vis_1(&dst_idx, dst, c, nextc);
  }
  if ((((c & 0177) == ' ') || (flag & 0x01)) || ((flag & 0x100) && ((((c == '*') || (c == '?')) || (c == '[')) || (c == '#'))))
  {
    dst[dst_idx] = '\\';
    dst_idx += 1;
    dst[dst_idx] = ((((u_char) c) >> 6) & 07) + '0';
    dst_idx += 1;
    dst[dst_idx] = ((((u_char) c) >> 3) & 07) + '0';
    dst_idx += 1;
    dst[dst_idx] = (((u_char) c) & 07) + '0';
    dst_idx += 1;
    goto done;
  }
  if ((flag & 0x40) == 0)
  {
    dst[dst_idx] = '\\';
    dst_idx += 1;
  }
  if (c & 0200)
  {
    c &= 0177;
    dst[dst_idx] = 'M';
    dst_idx += 1;
  }
  if (iscntrl((u_char) c))
  {
    dst[dst_idx] = '^';
    dst_idx += 1;
    if (c == 0177)
    {
      dst[dst_idx] = '?';
      dst_idx += 1;
    }
    else
      dst[dst_idx] = c + '@';
    dst_idx += 1;
  }
  else
  {
    dst[dst_idx] = '-';
    dst_idx += 1;
    dst[dst_idx] = c;
    dst_idx += 1;
  }
  done:
  dst[dst_idx] = '\0';

  return dst;
}


----------------------------
***/


int strnvis(char *dst, const char *src, size_t siz, int flag)
{
  unsigned int src_idx = 0;
  unsigned int dst_idx = 0;
  char *start;
  unsigned int start_idx = 0;
  char *end;
  unsigned int end_idx = 0;
  char tbuf[5];
  int c;
  int i;
  i = 0;
  for (start_idx = &dst[dst_idx], end_idx = ((&start[start_idx]) + siz) - 1; (c = src[src_idx]) && ((&dst[dst_idx]) < (&end[end_idx]));)
  {
    helper_strnvis_1(&src_idx, &dst_idx, &i, dst, src, flag, end, end_idx, tbuf, c);
  }

  if (siz > 0)
  {
    dst[dst_idx] = '\0';
  }
  if (((&dst[dst_idx]) + i) > (&end[end_idx]))
  {
    while (c = src[src_idx])
    {
      src_idx += 1;
      dst_idx += vis(tbuf, c, flag, *(&src[src_idx])) - tbuf;
    }

  }
  return (&dst[dst_idx]) - (&start[start_idx]);
}


/*** DEPENDENCIES:
char *vis(char *dst, int c, int flag, int nextc)
{
  unsigned int dst_idx = 0;
  if (((c == '\\') || ((flag & 0x400) == 0)) && ((((((((((u_int) c) <= 255) && isascii((u_char) c)) && (((((c != '*') && (c != '?')) && (c != '[')) && (c != '#')) || ((flag & 0x100) == 0))) && isgraph((u_char) c)) || (((flag & 0x04) == 0) && (c == ' '))) || (((flag & 0x08) == 0) && (c == '\t'))) || (((flag & 0x10) == 0) && (c == '\n'))) || ((flag & 0x20) && ((((c == '\b') || (c == '\007')) || (c == '\r')) || isgraph((u_char) c)))))
  {
    if (((c == '"') && ((flag & 0x200) != 0)) || ((c == '\\') && ((flag & 0x40) == 0)))
    {
      dst[dst_idx] = '\\';
      dst_idx += 1;
    }
    dst[dst_idx] = c;
    dst_idx += 1;
    dst[dst_idx] = '\0';
    return dst;
  }
  if (flag & 0x02)
  {
    helper_vis_1(&dst_idx, dst, c, nextc);
  }
  if ((((c & 0177) == ' ') || (flag & 0x01)) || ((flag & 0x100) && ((((c == '*') || (c == '?')) || (c == '[')) || (c == '#'))))
  {
    dst[dst_idx] = '\\';
    dst_idx += 1;
    dst[dst_idx] = ((((u_char) c) >> 6) & 07) + '0';
    dst_idx += 1;
    dst[dst_idx] = ((((u_char) c) >> 3) & 07) + '0';
    dst_idx += 1;
    dst[dst_idx] = (((u_char) c) & 07) + '0';
    dst_idx += 1;
    goto done;
  }
  if ((flag & 0x40) == 0)
  {
    dst[dst_idx] = '\\';
    dst_idx += 1;
  }
  if (c & 0200)
  {
    c &= 0177;
    dst[dst_idx] = 'M';
    dst_idx += 1;
  }
  if (iscntrl((u_char) c))
  {
    dst[dst_idx] = '^';
    dst_idx += 1;
    if (c == 0177)
    {
      dst[dst_idx] = '?';
      dst_idx += 1;
    }
    else
      dst[dst_idx] = c + '@';
    dst_idx += 1;
  }
  else
  {
    dst[dst_idx] = '-';
    dst_idx += 1;
    dst[dst_idx] = c;
    dst_idx += 1;
  }
  done:
  dst[dst_idx] = '\0';

  return dst;
}


----------------------------
void helper_strnvis_1(unsigned int * const src_idx_ref, unsigned int * const dst_idx_ref, int * const i_ref, char * const dst, const char * const src, int flag, char * const end, unsigned int end_idx, char tbuf[5], int c)
{
  unsigned int src_idx = *src_idx_ref;
  unsigned int dst_idx = *dst_idx_ref;
  int i = *i_ref;
  if (((c == '\\') || ((flag & 0x400) == 0)) && ((((((((((u_int) c) <= 255) && isascii((u_char) c)) && (((((c != '*') && (c != '?')) && (c != '[')) && (c != '#')) || ((flag & 0x100) == 0))) && isgraph((u_char) c)) || (((flag & 0x04) == 0) && (c == ' '))) || (((flag & 0x08) == 0) && (c == '\t'))) || (((flag & 0x10) == 0) && (c == '\n'))) || ((flag & 0x20) && ((((c == '\b') || (c == '\007')) || (c == '\r')) || isgraph((u_char) c)))))
  {
    if (((c == '"') && ((flag & 0x200) != 0)) || ((c == '\\') && ((flag & 0x40) == 0)))
    {
      if (((&dst[dst_idx]) + 1) >= (&end[end_idx]))
      {
        i = 2;
        break;
      }
      dst[dst_idx] = '\\';
      dst_idx += 1;
    }
    i = 1;
    dst[dst_idx] = c;
    dst_idx += 1;
    src_idx += 1;
  }
  else
  {
    src_idx += 1;
    i = vis(tbuf, c, flag, *(&src[src_idx])) - tbuf;
    if (((&dst[dst_idx]) + i) <= (&end[end_idx]))
    {
      memcpy(dst, tbuf, i);
      dst_idx += i;
    }
    else
    {
      src_idx -= 1;
      break;
    }
  }
  *src_idx_ref = src_idx;
  *dst_idx_ref = dst_idx;
  *i_ref = i;
}


----------------------------
***/


