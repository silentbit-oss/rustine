static int isescaped(const char *sp, const char *p, int esc)
{
  const char *cp;
  unsigned int cp_idx = 0;
  size_t ne;
  if (esc == '\0')
  {
    return 1;
  }
  for (ne = 0, cp_idx = p; ((--(&cp[cp_idx])) >= sp) && (cp[cp_idx] == esc); ne += 1)
  {
    continue;
  }

  return (ne & 1) != 0;
}


/*** DEPENDENCIES:
***/


// hint:  ['ptr_idx_ref is a mutable refrence to unsigned int', 'cp_idx_ref is a mutable refrence to unsigned int']
void helper_helper_fparseln_1_1(unsigned int * const ptr_idx_ref, unsigned int * const cp_idx_ref, int flags, char * const ptr, char * const cp, char esc, char con, char com)
{
  unsigned int ptr_idx = *ptr_idx_ref;
  unsigned int cp_idx = *cp_idx_ref;
  int skipesc;
  while ((cp[0 + cp_idx] != '\0') && (cp[0 + cp_idx] != esc))
  {
    ptr[ptr_idx] = cp[cp_idx];
    cp_idx += 1;
    ptr_idx += 1;
  }

  if ((cp[0 + cp_idx] == '\0') || (cp[1 + cp_idx] == '\0'))
  {
    break;
  }
  skipesc = 0;
  if (cp[1 + cp_idx] == com)
  {
    skipesc += flags & 0x04;
  }
  if (cp[1 + cp_idx] == con)
  {
    skipesc += flags & 0x02;
  }
  if (cp[1 + cp_idx] == esc)
  {
    skipesc += flags & 0x01;
  }
  if (((cp[1 + cp_idx] != com) && (cp[1 + cp_idx] != con)) && (cp[1 + cp_idx] != esc))
  {
    skipesc = flags & 0x08;
  }
  if (skipesc)
  {
    cp_idx += 1;
  }
  else
    ptr[ptr_idx] = cp[cp_idx];
  cp_idx += 1;
  ptr_idx += 1;
  ptr[ptr_idx] = cp[cp_idx];
  cp_idx += 1;
  ptr_idx += 1;
  *ptr_idx_ref = ptr_idx;
  *cp_idx_ref = cp_idx;
}


/*** DEPENDENCIES:
***/


// hint:  ['ptr_idx_ref is a mutable refrence to unsigned int', 'cp_idx_ref is a mutable refrence to unsigned int', 'len_ref is a mutable refrence to size_t']
void helper_fparseln_1(unsigned int * const ptr_idx_ref, unsigned int * const cp_idx_ref, size_t * const len_ref, int flags, char * const buf, char * const ptr, char * const cp, char esc, char con, char com)
{
  unsigned int ptr_idx = *ptr_idx_ref;
  unsigned int cp_idx = *cp_idx_ref;
  size_t len = *len_ref;
  ptr_idx = (cp = &cp[cp_idx + cp_idx]);
  while (cp[0 + cp_idx] != '\0')
  {
    helper_helper_fparseln_1_1(&ptr_idx, &cp_idx, flags, ptr, cp, esc, con, com);
  }

  ptr[ptr_idx] = '\0';
  len = strlen(buf);
  *ptr_idx_ref = ptr_idx;
  *cp_idx_ref = cp_idx;
  *len_ref = len;
}


/*** DEPENDENCIES:
void helper_helper_fparseln_1_1(unsigned int * const ptr_idx_ref, unsigned int * const cp_idx_ref, int flags, char * const ptr, char * const cp, char esc, char con, char com)
{
  unsigned int ptr_idx = *ptr_idx_ref;
  unsigned int cp_idx = *cp_idx_ref;
  int skipesc;
  while ((cp[0 + cp_idx] != '\0') && (cp[0 + cp_idx] != esc))
  {
    ptr[ptr_idx] = cp[cp_idx];
    cp_idx += 1;
    ptr_idx += 1;
  }

  if ((cp[0 + cp_idx] == '\0') || (cp[1 + cp_idx] == '\0'))
  {
    break;
  }
  skipesc = 0;
  if (cp[1 + cp_idx] == com)
  {
    skipesc += flags & 0x04;
  }
  if (cp[1 + cp_idx] == con)
  {
    skipesc += flags & 0x02;
  }
  if (cp[1 + cp_idx] == esc)
  {
    skipesc += flags & 0x01;
  }
  if (((cp[1 + cp_idx] != com) && (cp[1 + cp_idx] != con)) && (cp[1 + cp_idx] != esc))
  {
    skipesc = flags & 0x08;
  }
  if (skipesc)
  {
    cp_idx += 1;
  }
  else
    ptr[ptr_idx] = cp[cp_idx];
  cp_idx += 1;
  ptr_idx += 1;
  ptr[ptr_idx] = cp[cp_idx];
  cp_idx += 1;
  ptr_idx += 1;
  *ptr_idx_ref = ptr_idx;
  *cp_idx_ref = cp_idx;
}


----------------------------
***/


// hint:  ['buf_idx_ref is a mutable refrence to unsigned int', 'ptr_idx_ref is a mutable refrence to unsigned int', 'cp_idx_ref is a mutable refrence to unsigned int', 's_ref is a mutable refrence to size_t', 'len_ref is a mutable refrence to size_t', 'cnt_ref is a mutable refrence to int']
char *helper_fparseln_2(unsigned int * const buf_idx_ref, unsigned int * const ptr_idx_ref, unsigned int * const cp_idx_ref, size_t * const s_ref, size_t * const len_ref, int * const cnt_ref, FILE * const fp, size_t * const lineno, char * const buf, char * const ptr, char * const cp, char esc, char con, char nl, char com)
{
  unsigned int buf_idx = *buf_idx_ref;
  unsigned int ptr_idx = *ptr_idx_ref;
  unsigned int cp_idx = *cp_idx_ref;
  size_t s = *s_ref;
  size_t len = *len_ref;
  int cnt = *cnt_ref;
  cnt = 0;
  if (lineno)
  {
    *lineno += 1;
  }
  if ((ptr_idx = fgetln(fp, &s)) == 0)
  {
    break;
  }
  if (s && com)
  {
    for (cp_idx = &ptr[ptr_idx]; (&cp[cp_idx]) < ((&ptr[ptr_idx]) + s); cp_idx += 1)
    {
      if ((cp[cp_idx] == com) && (!isescaped(ptr, cp, esc)))
      {
        s = (&cp[cp_idx]) - (&ptr[ptr_idx]);
        cnt = (s == 0) && ((&buf[buf_idx]) == 0);
        break;
      }
    }

  }
  if (s && nl)
  {
    cp_idx = &ptr[(s - 1) + ptr_idx];
    if (cp[cp_idx] == nl)
    {
      s -= 1;
    }
  }
  if (s && con)
  {
    cp_idx = &ptr[(s - 1) + ptr_idx];
    if ((cp[cp_idx] == con) && (!isescaped(ptr, cp, esc)))
    {
      s -= 1;
      cnt = 1;
    }
  }
  if ((s == 0) && ((&buf[buf_idx]) != 0))
  {
    continue;
  }
  if ((cp_idx = realloc(buf, (len + s) + 1)) == 0)
  {
    free(buf);
    return 0;
  }
  buf_idx = &cp[cp_idx];
  (void) memcpy((&buf[buf_idx]) + len, ptr, s);
  len += s;
  buf[len + buf_idx] = '\0';
  *buf_idx_ref = buf_idx;
  *ptr_idx_ref = ptr_idx;
  *cp_idx_ref = cp_idx;
  *s_ref = s;
  *len_ref = len;
  *cnt_ref = cnt;
}


/*** DEPENDENCIES:
char *fgetln(FILE *fp, size_t *len)
{
  static char *buf = 0;
  unsigned int buf_idx = 0;
  static size_t bufsz = 0;
  size_t r = 0;
  char *p;
  unsigned int p_idx = 0;
  int c;
  int e;
  if ((!fp) || (!len))
  {
    errno = EINVAL;
    return 0;
  }
  if (!(&buf[buf_idx]))
  {
    if (!(buf_idx = calloc(1, 1024)))
    {
      return 0;
    }
    bufsz = 1024;
  }
  while ((c = getc(fp)) != EOF)
  {
    buf[r + buf_idx] = c;
    r += 1;
    if (r == bufsz)
    {
      if (!(p_idx = reallocarray(buf, 2, bufsz)))
      {
        e = errno;
        free(buf);
        errno = e;
        buf_idx = 0, bufsz = 0;
        return 0;
      }
      buf_idx = &p[p_idx], bufsz = 2 * bufsz;
    }
    if (c == '\n')
    {
      break;
    }
  }

  return (*len = r) ? (buf) : (0);
}


----------------------------
static int isescaped(const char *sp, const char *p, int esc)
{
  const char *cp;
  unsigned int cp_idx = 0;
  size_t ne;
  if (esc == '\0')
  {
    return 1;
  }
  for (ne = 0, cp_idx = p; ((--(&cp[cp_idx])) >= sp) && (cp[cp_idx] == esc); ne += 1)
  {
    continue;
  }

  return (ne & 1) != 0;
}


----------------------------
***/


char *fparseln(FILE *fp, size_t *size, size_t *lineno, const char str[3], int flags)
{
  static const char dstr[3] = {'\\', '\\', '#'};
  char *buf = 0;
  unsigned int buf_idx = 0;
  char *ptr;
  unsigned int ptr_idx = 0;
  char *cp;
  unsigned int cp_idx = 0;
  char esc;
  char con;
  char nl;
  char com;
  size_t s;
  size_t len = 0;
  int cnt = 1;
  if (str == 0)
  {
    str = dstr;
  }
  esc = str[0];
  con = str[1];
  com = str[2];
  nl = '\n';
  while (cnt)
  {
    helper_fparseln_2(&buf_idx, &ptr_idx, &cp_idx, &s, &len, &cnt, fp, lineno, buf, ptr, cp, esc, con, nl, com);
  }

  if (((((flags & 0x0f) != 0) && esc) && ((&buf[buf_idx]) != 0)) && (strchr(buf, esc) != 0))
  {
    helper_fparseln_1(&ptr_idx, &cp_idx, &len, flags, buf, ptr, cp, esc, con, com);
  }
  if (size)
  {
    *size = len;
  }
  return buf;
}


/*** DEPENDENCIES:
char *helper_fparseln_2(unsigned int * const buf_idx_ref, unsigned int * const ptr_idx_ref, unsigned int * const cp_idx_ref, size_t * const s_ref, size_t * const len_ref, int * const cnt_ref, FILE * const fp, size_t * const lineno, char * const buf, char * const ptr, char * const cp, char esc, char con, char nl, char com)
{
  unsigned int buf_idx = *buf_idx_ref;
  unsigned int ptr_idx = *ptr_idx_ref;
  unsigned int cp_idx = *cp_idx_ref;
  size_t s = *s_ref;
  size_t len = *len_ref;
  int cnt = *cnt_ref;
  cnt = 0;
  if (lineno)
  {
    *lineno += 1;
  }
  if ((ptr_idx = fgetln(fp, &s)) == 0)
  {
    break;
  }
  if (s && com)
  {
    for (cp_idx = &ptr[ptr_idx]; (&cp[cp_idx]) < ((&ptr[ptr_idx]) + s); cp_idx += 1)
    {
      if ((cp[cp_idx] == com) && (!isescaped(ptr, cp, esc)))
      {
        s = (&cp[cp_idx]) - (&ptr[ptr_idx]);
        cnt = (s == 0) && ((&buf[buf_idx]) == 0);
        break;
      }
    }

  }
  if (s && nl)
  {
    cp_idx = &ptr[(s - 1) + ptr_idx];
    if (cp[cp_idx] == nl)
    {
      s -= 1;
    }
  }
  if (s && con)
  {
    cp_idx = &ptr[(s - 1) + ptr_idx];
    if ((cp[cp_idx] == con) && (!isescaped(ptr, cp, esc)))
    {
      s -= 1;
      cnt = 1;
    }
  }
  if ((s == 0) && ((&buf[buf_idx]) != 0))
  {
    continue;
  }
  if ((cp_idx = realloc(buf, (len + s) + 1)) == 0)
  {
    free(buf);
    return 0;
  }
  buf_idx = &cp[cp_idx];
  (void) memcpy((&buf[buf_idx]) + len, ptr, s);
  len += s;
  buf[len + buf_idx] = '\0';
  *buf_idx_ref = buf_idx;
  *ptr_idx_ref = ptr_idx;
  *cp_idx_ref = cp_idx;
  *s_ref = s;
  *len_ref = len;
  *cnt_ref = cnt;
}


----------------------------
void helper_fparseln_1(unsigned int * const ptr_idx_ref, unsigned int * const cp_idx_ref, size_t * const len_ref, int flags, char * const buf, char * const ptr, char * const cp, char esc, char con, char com)
{
  unsigned int ptr_idx = *ptr_idx_ref;
  unsigned int cp_idx = *cp_idx_ref;
  size_t len = *len_ref;
  ptr_idx = (cp = &cp[cp_idx + cp_idx]);
  while (cp[0 + cp_idx] != '\0')
  {
    helper_helper_fparseln_1_1(&ptr_idx, &cp_idx, flags, ptr, cp, esc, con, com);
  }

  ptr[ptr_idx] = '\0';
  len = strlen(buf);
  *ptr_idx_ref = ptr_idx;
  *cp_idx_ref = cp_idx;
  *len_ref = len;
}


----------------------------
***/


