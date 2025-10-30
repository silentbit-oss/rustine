// element in merge of:  helper_format_replace_2,helper_helper_format_expand_1_3,format_expand,format_replace,helper_format_expand_1,helper_helper_format_expand_1_1,format_job_get,helper_helper_format_expand_1_2
// hint:  ['value_idx_ref is a mutable refrence to unsigned int', 'left_idx_ref is a mutable refrence to unsigned int', 'right_idx_ref is a mutable refrence to unsigned int']
void helper_format_replace_2(unsigned int * const value_idx_ref, unsigned int * const left_idx_ref, unsigned int * const right_idx_ref, struct format_tree * const ft, char * const copy, char * const left, char * const right, int compare)
{
  unsigned int value_idx = *value_idx_ref;
  unsigned int left_idx = *left_idx_ref;
  unsigned int right_idx = *right_idx_ref;
  if (format_choose(copy, &(&left[left_idx]), &(&right[right_idx])) != 0)
  {
    goto fail;
  }
  left_idx = format_expand(ft, left_idx);
  right_idx = format_expand(ft, right_idx);
  if ((compare == (-3)) && (format_true(left) || format_true(right)))
  {
    value_idx = xstrdup("1");
  }
  else
    if ((compare == (-4)) && (format_true(left) && format_true(right)))
  {
    value_idx = xstrdup("1");
  }
  else
    if ((compare == 1) && (strcmp(left, right) == 0))
  {
    value_idx = xstrdup("1");
  }
  else
    if ((compare == (-1)) && (strcmp(left, right) != 0))
  {
    value_idx = xstrdup("1");
  }
  else
    if ((compare == (-2)) && (fnmatch(left, right, 0) == 0))
  {
    value_idx = xstrdup("1");
  }
  else
    value_idx = xstrdup("0");
  free(right);
  free(left);
  *value_idx_ref = value_idx;
  *left_idx_ref = left_idx;
  *right_idx_ref = right_idx;
}


/*** DEPENDENCIES:
None
----------------------------
char *xstrdup(const char *str)
{
  char *cp;
  unsigned int cp_idx = 0;
  if ((cp_idx = strdup(str)) == 0)
  {
    fatalx("xstrdup: %s", strerror(errno));
  }
  return cp;
}


----------------------------
static int format_choose(char *s, char **left, char **right)
{
  char *cp;
  unsigned int cp_idx = 0;
  cp_idx = format_skip(s);
  if ((&cp[cp_idx]) == 0)
  {
    return -1;
  }
  cp[cp_idx] = '\0';
  *left = s;
  *right = (&cp[cp_idx]) + 1;
  return 0;
}


----------------------------
int format_true(const char *s)
{
  if (((s != 0) && ((*s) != '\0')) && ((s[0] != '0') || (s[1] != '\0')))
  {
    return 1;
  }
  return 0;
}


----------------------------
None
----------------------------
***/


// element in merge of:  helper_format_replace_2,helper_helper_format_expand_1_3,format_expand,format_replace,helper_format_expand_1,helper_helper_format_expand_1_1,format_job_get,helper_helper_format_expand_1_2
// hint:  ['fmt_idx_ref is a mutable refrence to unsigned int', 'buf_idx_ref is a mutable refrence to unsigned int', 'out_idx_ref is a mutable refrence to unsigned int', 'name_idx_ref is a mutable refrence to unsigned int', 'ptr_idx_ref is a mutable refrence to unsigned int', 'off_ref is a mutable refrence to size_t', 'len_ref is a mutable refrence to size_t', 'n_ref is a mutable refrence to size_t', 'outlen_ref is a mutable refrence to size_t', 'brackets_ref is a mutable refrence to int']
void helper_helper_format_expand_1_3(unsigned int * const fmt_idx_ref, unsigned int * const buf_idx_ref, unsigned int * const out_idx_ref, unsigned int * const name_idx_ref, unsigned int * const ptr_idx_ref, size_t * const off_ref, size_t * const len_ref, size_t * const n_ref, size_t * const outlen_ref, int * const brackets_ref, struct format_tree * const ft, const char * const fmt, char * const buf, char * const out, char * const name, const char * const ptr)
{
  unsigned int fmt_idx = *fmt_idx_ref;
  unsigned int buf_idx = *buf_idx_ref;
  unsigned int out_idx = *out_idx_ref;
  unsigned int name_idx = *name_idx_ref;
  unsigned int ptr_idx = *ptr_idx_ref;
  size_t off = *off_ref;
  size_t len = *len_ref;
  size_t n = *n_ref;
  size_t outlen = *outlen_ref;
  int brackets = *brackets_ref;
  brackets = 1;
  for (ptr_idx = &fmt[fmt_idx]; ptr[ptr_idx] != '\0'; ptr_idx += 1)
  {
    if (ptr[ptr_idx] == '(')
    {
      brackets += 1;
    }
    if ((ptr[ptr_idx] == ')') && ((--brackets) == 0))
    {
      break;
    }
  }

  if ((ptr[ptr_idx] != ')') || (brackets != 0))
  {
    break;
  }
  n = (&ptr[ptr_idx]) - (&fmt[fmt_idx]);
  if (ft->flags & 0x4)
  {
    out_idx = xstrdup("");
  }
  else
  {
    name_idx = xstrndup(fmt, n);
    out_idx = format_job_get(ft, name);
    free(name);
  }
  outlen = strlen(out);
  while ((len - off) < (outlen + 1))
  {
    buf_idx = xreallocarray(buf_idx, 2, len);
    len *= 2;
  }

  memcpy((&buf[buf_idx]) + off, out, outlen);
  off += outlen;
  free(out);
  fmt_idx += n + 1;
  continue;
  *fmt_idx_ref = fmt_idx;
  *buf_idx_ref = buf_idx;
  *out_idx_ref = out_idx;
  *name_idx_ref = name_idx;
  *ptr_idx_ref = ptr_idx;
  *off_ref = off;
  *len_ref = len;
  *n_ref = n;
  *outlen_ref = outlen;
  *brackets_ref = brackets;
}


/*** DEPENDENCIES:
void *xreallocarray(void *ptr, size_t nmemb, size_t size)
{
  void *new_ptr;
  unsigned int new_ptr_idx = 0;
  if ((nmemb == 0) || (size == 0))
  {
    fatalx("xreallocarray: zero size");
  }
  new_ptr_idx = reallocarray(ptr, nmemb, size);
  if ((&new_ptr[new_ptr_idx]) == 0)
  {
    fatalx("xreallocarray: allocating %zu * %zu bytes: %s", nmemb, size, strerror(errno));
  }
  return new_ptr;
}


----------------------------
None
----------------------------
char *xstrdup(const char *str)
{
  char *cp;
  unsigned int cp_idx = 0;
  if ((cp_idx = strdup(str)) == 0)
  {
    fatalx("xstrdup: %s", strerror(errno));
  }
  return cp;
}


----------------------------
char *xstrndup(const char *str, size_t maxlen)
{
  char *cp;
  unsigned int cp_idx = 0;
  if ((cp_idx = strndup(str, maxlen)) == 0)
  {
    fatalx("xstrndup: %s", strerror(errno));
  }
  return cp;
}


----------------------------
None
----------------------------
***/


// element in merge of:  helper_format_replace_2,helper_helper_format_expand_1_3,format_expand,format_replace,helper_format_expand_1,helper_helper_format_expand_1_1,format_job_get,helper_helper_format_expand_1_2
char *format_expand(struct format_tree *ft, const char *fmt)
{
  unsigned int fmt_idx = 0;
  char *buf;
  unsigned int buf_idx = 0;
  char *out;
  unsigned int out_idx = 0;
  char *name;
  unsigned int name_idx = 0;
  const char *ptr;
  unsigned int ptr_idx = 0;
  const char *s;
  unsigned int s_idx = 0;
  const char *saved = fmt;
  size_t off;
  size_t len;
  size_t n;
  size_t outlen;
  int ch;
  int brackets;
  if ((&fmt[fmt_idx]) == 0)
  {
    return xstrdup("");
  }
  len = 64;
  buf_idx = xmalloc(len);
  off = 0;
  while (fmt[fmt_idx] != '\0')
  {
    helper_format_expand_1(&fmt_idx, &buf_idx, &out_idx, &name_idx, &ptr_idx, &s_idx, &off, &len, &n, &outlen, &ch, &brackets, ft, fmt, buf, out, name, ptr, s);
  }

  buf[off + buf_idx] = '\0';
  log_debug("format '%s' -> '%s'", saved, buf);
  return buf;
}


/*** DEPENDENCIES:
None
----------------------------
void log_debug(const char *msg, ...)
{
  va_list ap;
  __builtin_va_start(ap);
  log_vwrite(msg, ap);
  ;
}


----------------------------
void *xmalloc(size_t size)
{
  void *ptr;
  unsigned int ptr_idx = 0;
  if (size == 0)
  {
    fatalx("xmalloc: zero size");
  }
  ptr_idx = malloc(size);
  if ((&ptr[ptr_idx]) == 0)
  {
    fatalx("xmalloc: allocating %zu bytes: %s", size, strerror(errno));
  }
  return ptr;
}


----------------------------
char *xstrdup(const char *str)
{
  char *cp;
  unsigned int cp_idx = 0;
  if ((cp_idx = strdup(str)) == 0)
  {
    fatalx("xstrdup: %s", strerror(errno));
  }
  return cp;
}


----------------------------
None
----------------------------
***/


// element in merge of:  helper_format_replace_2,helper_helper_format_expand_1_3,format_expand,format_replace,helper_format_expand_1,helper_helper_format_expand_1_1,format_job_get,helper_helper_format_expand_1_2
static int format_replace(struct format_tree *ft, const char *key, size_t keylen, char **buf, size_t *len, size_t *off)
{
  struct window_pane *wp = ft->wp;
  char *copy;
  unsigned int copy_idx = 0;
  char *copy0;
  unsigned int copy0_idx = 0;
  char *endptr;
  char *ptr;
  unsigned int ptr_idx = 0;
  char *found;
  unsigned int found_idx = 0;
  char *new;
  unsigned int new_idx = 0;
  char *value;
  unsigned int value_idx = 0;
  char *from = 0;
  unsigned int from_idx = 0;
  char *to = 0;
  unsigned int to_idx = 0;
  char *left;
  unsigned int left_idx = 0;
  char *right;
  unsigned int right_idx = 0;
  size_t valuelen;
  size_t newlen;
  size_t fromlen;
  size_t tolen;
  size_t used;
  long limit = 0;
  int modifiers = 0;
  int compare = 0;
  int search = 0;
  copy0_idx = (copy = &copy[copy_idx + copy_idx]);
  memcpy(copy, key, keylen);
  copy[keylen + copy_idx] = '\0';
  switch (copy[0 + copy_idx])
  {
    case 'm':
    {
      if (copy[1 + copy_idx] != ':')
      {
        break;
      }
      compare = -2;
      copy_idx += 2;
      break;
    }

    case 'C':
    {
      if (copy[1 + copy_idx] != ':')
      {
        break;
      }
      search = 1;
      copy_idx += 2;
      break;
    }

    case '|':
    {
      if ((copy[1 + copy_idx] != '|') || (copy[2 + copy_idx] != ':'))
      {
        break;
      }
      compare = -3;
      copy_idx += 3;
      break;
    }

    case '&':
    {
      if ((copy[1 + copy_idx] != '&') || (copy[2 + copy_idx] != ':'))
      {
        break;
      }
      compare = -4;
      copy_idx += 3;
      break;
    }

    case '!':
    {
      if ((copy[1 + copy_idx] == '=') && (copy[2 + copy_idx] == ':'))
      {
        compare = -1;
        copy_idx += 3;
        break;
      }
      break;
    }

    case '=':
    {
      helper_format_replace_1(&copy_idx, &limit, &compare, copy, endptr);
    }

    case 'b':
    {
      if (copy[1 + copy_idx] != ':')
      {
        break;
      }
      modifiers |= 0x2;
      copy_idx += 2;
      break;
    }

    case 'd':
    {
      if (copy[1 + copy_idx] != ':')
      {
        break;
      }
      modifiers |= 0x4;
      copy_idx += 2;
      break;
    }

    case 't':
    {
      if (copy[1 + copy_idx] != ':')
      {
        break;
      }
      modifiers |= 0x1;
      copy_idx += 2;
      break;
    }

    case 's':
    {
      helper_format_replace_4(&copy_idx, &from_idx, &to_idx, &modifiers, copy, copy0, copy0_idx, from, to);
    }

  }

  if (search)
  {
    if (wp == 0)
    {
      value_idx = xstrdup("0");
    }
    else
      xasprintf(&(&value[value_idx]), "%u", window_pane_search(wp, copy));
  }
  else
    if (compare != 0)
  {
    helper_format_replace_2(&value_idx, &left_idx, &right_idx, ft, copy, left, right, compare);
  }
  else
    if (copy[copy_idx] == '?')
  {
    helper_format_replace_3(&ptr_idx, &found_idx, &value_idx, ft, copy, copy_idx, ptr, found, left, left_idx, right, right_idx, modifiers);
  }
  else
  {
    value_idx = format_find(ft, copy, modifiers);
    if ((&value[value_idx]) == 0)
    {
      value_idx = xstrdup("");
    }
  }
  if (modifiers & 0x8)
  {
    helper_format_replace_5(&copy_idx, &ptr_idx, &new_idx, &value_idx, &newlen, &fromlen, &tolen, &used, copy, ptr, new, value, from, to);
  }
  if (limit > 0)
  {
    new_idx = utf8_trimcstr(value, limit);
    free(value);
    value_idx = &new[new_idx];
  }
  else
    if (limit < 0)
  {
    new_idx = utf8_rtrimcstr(value, -limit);
    free(value);
    value_idx = &new[new_idx];
  }
  valuelen = strlen(value);
  while (((*len) - (*off)) < (valuelen + 1))
  {
    *buf = xreallocarray(*buf, 2, *len);
    *len *= 2;
  }

  memcpy((*buf) + (*off), value, valuelen);
  *off += valuelen;
  free(value);
  free(copy0);
  return 0;
  fail:
  free(copy0);

  return -1;
}


/*** DEPENDENCIES:
void *xreallocarray(void *ptr, size_t nmemb, size_t size)
{
  void *new_ptr;
  unsigned int new_ptr_idx = 0;
  if ((nmemb == 0) || (size == 0))
  {
    fatalx("xreallocarray: zero size");
  }
  new_ptr_idx = reallocarray(ptr, nmemb, size);
  if ((&new_ptr[new_ptr_idx]) == 0)
  {
    fatalx("xreallocarray: allocating %zu * %zu bytes: %s", nmemb, size, strerror(errno));
  }
  return new_ptr;
}


----------------------------
static char *format_find(struct format_tree *ft, const char *key, int modifiers)
{
  struct format_entry *fe;
  unsigned int fe_idx = 0;
  struct format_entry fe_find;
  struct environ_entry *envent;
  unsigned int envent_idx = 0;
  static char s[64];
  struct options_entry *o;
  unsigned int o_idx = 0;
  const char *found;
  unsigned int found_idx = 0;
  int idx;
  char *copy;
  unsigned int copy_idx = 0;
  char *saved;
  unsigned int saved_idx = 0;
  if ((~modifiers) & 0x1)
  {
    helper_format_find_1(&o_idx, &found_idx, ft, key, o, idx);
  }
  found_idx = 0;
  fe_find.key = (char *) key;
  fe_idx = format_entry_tree_RB_FIND(&ft->tree, &fe_find);
  if ((&fe[fe_idx]) != 0)
  {
    helper_format_find_2(&found_idx, ft, modifiers, fe, s);
  }
  if ((~modifiers) & 0x1)
  {
    envent_idx = 0;
    if (ft->s != 0)
    {
      envent_idx = environ_find(ft->s->environ, key);
    }
    if ((&envent[envent_idx]) == 0)
    {
      envent_idx = environ_find(global_environ, key);
    }
    if ((&envent[envent_idx]) != 0)
    {
      found_idx = envent->value;
      goto found;
    }
  }
  return 0;
  found:
  if ((&found[found_idx]) == 0)
  {
    return 0;
  }

  copy_idx = xstrdup(found);
  if (modifiers & 0x2)
  {
    saved_idx = &copy[copy_idx];
    copy_idx = xstrdup(basename(saved));
    free(saved);
  }
  if (modifiers & 0x4)
  {
    saved_idx = &copy[copy_idx];
    copy_idx = xstrdup(dirname(saved));
    free(saved);
  }
  return copy;
}


----------------------------
void helper_format_replace_5(unsigned int * const copy_idx_ref, unsigned int * const ptr_idx_ref, unsigned int * const new_idx_ref, unsigned int * const value_idx_ref, size_t * const newlen_ref, size_t * const fromlen_ref, size_t * const tolen_ref, size_t * const used_ref, char * const copy, char * const ptr, char * const new, char * const value, char * const from, char * const to)
{
  unsigned int copy_idx = *copy_idx_ref;
  unsigned int ptr_idx = *ptr_idx_ref;
  unsigned int new_idx = *new_idx_ref;
  unsigned int value_idx = *value_idx_ref;
  size_t newlen = *newlen_ref;
  size_t fromlen = *fromlen_ref;
  size_t tolen = *tolen_ref;
  size_t used = *used_ref;
  fromlen = strlen(from);
  tolen = strlen(to);
  newlen = strlen(value) + 1;
  copy_idx = (new = &new[new_idx + new_idx]);
  for (ptr_idx = &value[value_idx]; ptr[ptr_idx] != '\0';)
  {
    helper_helper_format_replace_5_1(&copy_idx, &ptr_idx, &new_idx, &newlen, &used, copy, ptr, new, from, to, fromlen, tolen);
  }

  new[new_idx] = '\0';
  free(value);
  value_idx = &copy[copy_idx];
  *copy_idx_ref = copy_idx;
  *ptr_idx_ref = ptr_idx;
  *new_idx_ref = new_idx;
  *value_idx_ref = value_idx;
  *newlen_ref = newlen;
  *fromlen_ref = fromlen;
  *tolen_ref = tolen;
  *used_ref = used;
}


----------------------------
char *utf8_rtrimcstr(const char *s, u_int width)
{
  struct utf8_data *tmp;
  unsigned int tmp_idx = 0;
  struct utf8_data *next;
  unsigned int next_idx = 0;
  struct utf8_data *end;
  unsigned int end_idx = 0;
  char *out;
  unsigned int out_idx = 0;
  u_int at;
  tmp_idx = utf8_fromcstr(s);
  for (end_idx = &tmp[tmp_idx]; end->size != 0; end_idx += 1)
  {
    ;
  }

  if ((&end[end_idx]) == (&tmp[tmp_idx]))
  {
    free(tmp);
    return xstrdup("");
  }
  next_idx = (&end[end_idx]) - 1;
  at = 0;
  for (;;)
  {
    if ((at + next->width) > width)
    {
      next_idx += 1;
      break;
    }
    at += next->width;
    if ((&next[next_idx]) == (&tmp[tmp_idx]))
    {
      break;
    }
    next_idx -= 1;
  }

  out_idx = utf8_tocstr(next);
  free(tmp);
  return out;
}


----------------------------
None
----------------------------
u_int window_pane_search(struct window_pane *wp, const char *searchstr)
{
  struct screen *s = &wp->base;
  char *newsearchstr;
  char *line;
  unsigned int line_idx = 0;
  u_int i;
  xasprintf(&newsearchstr, "*%s*", searchstr);
  for (i = 0; i < s->grid->sy; i += 1)
  {
    line_idx = grid_view_string_cells(s->grid, 0, i, s->grid->sx);
    if (fnmatch(newsearchstr, line, 0) == 0)
    {
      free(line);
      break;
    }
    free(line);
  }

  free(newsearchstr);
  if (i == s->grid->sy)
  {
    return 0;
  }
  return i + 1;
}


----------------------------
char *utf8_trimcstr(const char *s, u_int width)
{
  struct utf8_data *tmp;
  unsigned int tmp_idx = 0;
  struct utf8_data *next;
  unsigned int next_idx = 0;
  char *out;
  unsigned int out_idx = 0;
  u_int at;
  tmp_idx = utf8_fromcstr(s);
  at = 0;
  for (next_idx = &tmp[tmp_idx]; next->size != 0; next_idx += 1)
  {
    if ((at + next->width) > width)
    {
      next->size = 0;
      break;
    }
    at += next->width;
  }

  out_idx = utf8_tocstr(tmp);
  free(tmp);
  return out;
}


----------------------------
char *xstrdup(const char *str)
{
  char *cp;
  unsigned int cp_idx = 0;
  if ((cp_idx = strdup(str)) == 0)
  {
    fatalx("xstrdup: %s", strerror(errno));
  }
  return cp;
}


----------------------------
int xasprintf(char **ret, const char *fmt, ...)
{
  va_list ap;
  int i;
  __builtin_va_start(ap);
  i = xvasprintf(ret, fmt, ap);
  ;
  return i;
}


----------------------------
void helper_format_replace_4(unsigned int * const copy_idx_ref, unsigned int * const from_idx_ref, unsigned int * const to_idx_ref, int * const modifiers_ref, char * const copy, char * const copy0, unsigned int copy0_idx, char * const from, char * const to)
{
  unsigned int copy_idx = *copy_idx_ref;
  unsigned int from_idx = *from_idx_ref;
  unsigned int to_idx = *to_idx_ref;
  int modifiers = *modifiers_ref;
  if (copy[1 + copy_idx] != '/')
  {
    break;
  }
  from_idx = (&copy[copy_idx]) + 2;
  for (copy_idx = &from[from_idx]; (copy[copy_idx] != '\0') && (copy[copy_idx] != '/'); copy_idx += 1)
  {
    ;
  }

  if ((copy[0 + copy_idx] != '/') || ((&copy[copy_idx]) == (&from[from_idx])))
  {
    copy_idx = &copy0[copy0_idx];
    break;
  }
  copy[0 + copy_idx] = '\0';
  to_idx = (&copy[copy_idx]) + 1;
  for (copy_idx = &to[to_idx]; (copy[copy_idx] != '\0') && (copy[copy_idx] != '/'); copy_idx += 1)
  {
    ;
  }

  if ((copy[0 + copy_idx] != '/') || (copy[1 + copy_idx] != ':'))
  {
    copy_idx = &copy0[copy0_idx];
    break;
  }
  copy[0 + copy_idx] = '\0';
  modifiers |= 0x8;
  copy_idx += 2;
  break;
  *copy_idx_ref = copy_idx;
  *from_idx_ref = from_idx;
  *to_idx_ref = to_idx;
  *modifiers_ref = modifiers;
}


----------------------------
void helper_format_replace_3(unsigned int * const ptr_idx_ref, unsigned int * const found_idx_ref, unsigned int * const value_idx_ref, struct format_tree * const ft, char * const copy, unsigned int copy_idx, char * const ptr, char * const found, char * const left, unsigned int left_idx, char * const right, unsigned int right_idx, int modifiers)
{
  unsigned int ptr_idx = *ptr_idx_ref;
  unsigned int found_idx = *found_idx_ref;
  unsigned int value_idx = *value_idx_ref;
  ptr_idx = format_skip(copy);
  if ((&ptr[ptr_idx]) == 0)
  {
    goto fail;
  }
  ptr[ptr_idx] = '\0';
  found_idx = format_find(ft, (&copy[copy_idx]) + 1, modifiers);
  if ((&found[found_idx]) == 0)
  {
    found_idx = format_expand(ft, (&copy[copy_idx]) + 1);
  }
  if (format_choose((&ptr[ptr_idx]) + 1, &(&left[left_idx]), &(&right[right_idx])) != 0)
  {
    goto fail;
  }
  if (format_true(found))
  {
    value_idx = format_expand(ft, left);
  }
  else
    value_idx = format_expand(ft, right);
  free(found);
  *ptr_idx_ref = ptr_idx;
  *found_idx_ref = found_idx;
  *value_idx_ref = value_idx;
}


----------------------------
void helper_format_replace_1(unsigned int * const copy_idx_ref, long * const limit_ref, int * const compare_ref, char * const copy, char * const endptr)
{
  unsigned int copy_idx = *copy_idx_ref;
  long limit = *limit_ref;
  int compare = *compare_ref;
  if ((copy[1 + copy_idx] == '=') && (copy[2 + copy_idx] == ':'))
  {
    compare = 1;
    copy_idx += 3;
    break;
  }
  errno = 0;
  limit = strtol((&copy[copy_idx]) + 1, &endptr, 10);
  if ((errno == ERANGE) && ((limit == (-9223372036854775808L)) || (limit == 9223372036854775807L)))
  {
    break;
  }
  if ((*endptr) != ':')
  {
    break;
  }
  copy_idx = endptr + 1;
  break;
  *copy_idx_ref = copy_idx;
  *limit_ref = limit;
  *compare_ref = compare;
}


----------------------------
None
----------------------------
***/


// element in merge of:  helper_format_replace_2,helper_helper_format_expand_1_3,format_expand,format_replace,helper_format_expand_1,helper_helper_format_expand_1_1,format_job_get,helper_helper_format_expand_1_2
// hint:  ['fmt_idx_ref is a mutable refrence to unsigned int', 'buf_idx_ref is a mutable refrence to unsigned int', 'out_idx_ref is a mutable refrence to unsigned int', 'name_idx_ref is a mutable refrence to unsigned int', 'ptr_idx_ref is a mutable refrence to unsigned int', 's_idx_ref is a mutable refrence to unsigned int', 'off_ref is a mutable refrence to size_t', 'len_ref is a mutable refrence to size_t', 'n_ref is a mutable refrence to size_t', 'outlen_ref is a mutable refrence to size_t', 'ch_ref is a mutable refrence to int', 'brackets_ref is a mutable refrence to int']
void helper_format_expand_1(unsigned int * const fmt_idx_ref, unsigned int * const buf_idx_ref, unsigned int * const out_idx_ref, unsigned int * const name_idx_ref, unsigned int * const ptr_idx_ref, unsigned int * const s_idx_ref, size_t * const off_ref, size_t * const len_ref, size_t * const n_ref, size_t * const outlen_ref, int * const ch_ref, int * const brackets_ref, struct format_tree * const ft, const char * const fmt, char * const buf, char * const out, char * const name, const char * const ptr, const char * const s)
{
  unsigned int fmt_idx = *fmt_idx_ref;
  unsigned int buf_idx = *buf_idx_ref;
  unsigned int out_idx = *out_idx_ref;
  unsigned int name_idx = *name_idx_ref;
  unsigned int ptr_idx = *ptr_idx_ref;
  unsigned int s_idx = *s_idx_ref;
  size_t off = *off_ref;
  size_t len = *len_ref;
  size_t n = *n_ref;
  size_t outlen = *outlen_ref;
  int ch = *ch_ref;
  int brackets = *brackets_ref;
  if (fmt[fmt_idx] != '#')
  {
    while ((len - off) < 2)
    {
      buf_idx = xreallocarray(buf_idx, 2, len);
      len *= 2;
    }

    buf[off + buf_idx] = fmt[fmt_idx];
    fmt_idx += 1;
    off += 1;
    continue;
  }
  fmt_idx += 1;
  ch = (u_char) fmt[fmt_idx];
  fmt_idx += 1;
  switch (ch)
  {
    case '(':
    {
      helper_helper_format_expand_1_3(&fmt_idx, &buf_idx, &out_idx, &name_idx, &ptr_idx, &off, &len, &n, &outlen, &brackets, ft, fmt, buf, out, name, ptr);
    }

    case '{':
    {
      helper_helper_format_expand_1_1(&fmt_idx, &ptr_idx, &n, &brackets, ft, fmt, buf, ptr, buf_idx, off, len);
    }

    case '#':
    {
      while ((len - off) < 2)
      {
        buf_idx = xreallocarray(buf_idx, 2, len);
        len *= 2;
      }

      buf[off + buf_idx] = '#';
      off += 1;
      continue;
    }

    default:
    {
      helper_helper_format_expand_1_2(&buf_idx, &s_idx, &off, &len, &n, ft, buf, s, ch);
    }

  }

  break;
  *fmt_idx_ref = fmt_idx;
  *buf_idx_ref = buf_idx;
  *out_idx_ref = out_idx;
  *name_idx_ref = name_idx;
  *ptr_idx_ref = ptr_idx;
  *s_idx_ref = s_idx;
  *off_ref = off;
  *len_ref = len;
  *n_ref = n;
  *outlen_ref = outlen;
  *ch_ref = ch;
  *brackets_ref = brackets;
}


/*** DEPENDENCIES:
void *xreallocarray(void *ptr, size_t nmemb, size_t size)
{
  void *new_ptr;
  unsigned int new_ptr_idx = 0;
  if ((nmemb == 0) || (size == 0))
  {
    fatalx("xreallocarray: zero size");
  }
  new_ptr_idx = reallocarray(ptr, nmemb, size);
  if ((&new_ptr[new_ptr_idx]) == 0)
  {
    fatalx("xreallocarray: allocating %zu * %zu bytes: %s", nmemb, size, strerror(errno));
  }
  return new_ptr;
}


----------------------------
None
----------------------------
None
----------------------------
***/


// element in merge of:  helper_format_replace_2,helper_helper_format_expand_1_3,format_expand,format_replace,helper_format_expand_1,helper_helper_format_expand_1_1,format_job_get,helper_helper_format_expand_1_2
// hint:  ['fmt_idx_ref is a mutable refrence to unsigned int', 'ptr_idx_ref is a mutable refrence to unsigned int', 'n_ref is a mutable refrence to size_t', 'brackets_ref is a mutable refrence to int']
void helper_helper_format_expand_1_1(unsigned int * const fmt_idx_ref, unsigned int * const ptr_idx_ref, size_t * const n_ref, int * const brackets_ref, struct format_tree * const ft, const char * const fmt, char * const buf, const char * const ptr, unsigned int buf_idx, size_t off, size_t len)
{
  unsigned int fmt_idx = *fmt_idx_ref;
  unsigned int ptr_idx = *ptr_idx_ref;
  size_t n = *n_ref;
  int brackets = *brackets_ref;
  brackets = 1;
  for (ptr_idx = &fmt[fmt_idx]; ptr[ptr_idx] != '\0'; ptr_idx += 1)
  {
    if (ptr[ptr_idx] == '{')
    {
      brackets += 1;
    }
    if ((ptr[ptr_idx] == '}') && ((--brackets) == 0))
    {
      break;
    }
  }

  if ((ptr[ptr_idx] != '}') || (brackets != 0))
  {
    break;
  }
  n = (&ptr[ptr_idx]) - (&fmt[fmt_idx]);
  if (format_replace(ft, fmt, n, &(&buf[buf_idx]), &len, &off) != 0)
  {
    break;
  }
  fmt_idx += n + 1;
  continue;
  *fmt_idx_ref = fmt_idx;
  *ptr_idx_ref = ptr_idx;
  *n_ref = n;
  *brackets_ref = brackets;
}


/*** DEPENDENCIES:
None
----------------------------
None
----------------------------
***/


// element in merge of:  helper_format_replace_2,helper_helper_format_expand_1_3,format_expand,format_replace,helper_format_expand_1,helper_helper_format_expand_1_1,format_job_get,helper_helper_format_expand_1_2
static char *format_job_get(struct format_tree *ft, const char *cmd)
{
  struct format_job_tree *jobs;
  unsigned int jobs_idx = 0;
  struct format_job fj0;
  struct format_job *fj;
  unsigned int fj_idx = 0;
  time_t t;
  char *expanded;
  unsigned int expanded_idx = 0;
  int force;
  if (ft->client == 0)
  {
    jobs_idx = &format_jobs;
  }
  else
    if (ft->client->jobs != 0)
  {
    jobs_idx = ft->client->jobs_idx;
  }
  else
  {
    jobs_idx = (ft->client->jobs_idx = xmalloc(sizeof(*ft->client->jobs_idx)));
    do
    {
      jobs->rbh_root = 0;
    }
    while (0);
  }
  fj0.tag = ft->tag;
  fj0.cmd = cmd;
  if ((fj_idx = format_job_tree_RB_FIND(jobs, &fj0)) == 0)
  {
    fj_idx = xcalloc(1, sizeof(*fj_idx));
    fj->client = ft->client;
    fj->tag = ft->tag;
    fj->cmd = xstrdup(cmd);
    fj->expanded = 0;
    xasprintf(&fj->out, "<'%s' not ready>", fj->cmd);
    format_job_tree_RB_INSERT(jobs, fj);
  }
  expanded_idx = format_expand(ft, cmd);
  if ((fj->expanded == 0) || (strcmp(expanded, fj->expanded) != 0))
  {
    free((void *) fj->expanded);
    fj->expanded = xstrdup(expanded);
    force = 1;
  }
  else
    force = ft->flags & 0x2;
  t = time(0);
  if ((fj->job == 0) && (force || (fj->last != t)))
  {
    fj->job = job_run(expanded, 0, 0, format_job_update, format_job_complete, 0, fj, 0x1);
    if (fj->job == 0)
    {
      free(fj->out);
      xasprintf(&fj->out, "<'%s' didn't start>", fj->cmd);
    }
    fj->last = t;
    fj->updated = 0;
  }
  if (ft->flags & 0x1)
  {
    fj->status = 1;
  }
  free(expanded);
  return format_expand(ft, fj->out);
}


/*** DEPENDENCIES:
static void format_job_complete(struct job *job)
{
  struct format_job *fj = job->data;
  char *line;
  unsigned int line_idx = 0;
  char *buf;
  unsigned int buf_idx = 0;
  size_t len;
  fj->job = 0;
  buf_idx = 0;
  if ((line_idx = evbuffer_readline(job->event->input)) == 0)
  {
    len = EVBUFFER_LENGTH(job->event->input);
    buf_idx = xmalloc(len + 1);
    if (len != 0)
    {
      memcpy(buf, EVBUFFER_DATA(job->event->input), len);
    }
    buf[len + buf_idx] = '\0';
  }
  else
    buf_idx = &line[line_idx];
  log_debug("%s: %p %s: %s", __func__, fj, fj->cmd, buf);
  if ((buf[buf_idx] != '\0') || (!fj->updated))
  {
    free(fj->out);
    fj->out = &buf[buf_idx];
  }
  else
    free(buf);
  if (fj->status)
  {
    if (fj->client != 0)
    {
      server_status_client(fj->client);
    }
    fj->status = 0;
  }
}


----------------------------
struct job *job_run(const char *cmd, struct session *s, const char *cwd, job_update_cb updatecb, job_complete_cb completecb, job_free_cb freecb, void *data, int flags)
{
  struct job *job;
  unsigned int job_idx = 0;
  struct environ *env;
  unsigned int env_idx = 0;
  pid_t pid;
  int nullfd;
  int out[2];
  const char *home;
  unsigned int home_idx = 0;
  sigset_t set;
  sigset_t oldset;
  if (socketpair(AF_UNIX, SOCK_STREAM, PF_UNSPEC, out) != 0)
  {
    return 0;
  }
  env_idx = environ_for_session(s, !cfg_finished);
  sigfillset(&set);
  sigprocmask(SIG_BLOCK, &set, &oldset);
  switch (pid = fork())
  {
    case -1:
    {
      sigprocmask(SIG_SETMASK, &oldset, 0);
      environ_free(env);
      close(out[0]);
      close(out[1]);
      return 0;
    }

    case 0:
    {
      helper_job_run_1(&nullfd, &home_idx, cmd, cwd, env, out, home, oldset);
    }

  }

  sigprocmask(SIG_SETMASK, &oldset, 0);
  environ_free(env);
  close(out[1]);
  job_idx = xmalloc(sizeof(*job_idx));
  job->state = JOB_RUNNING;
  job->flags = flags;
  job->cmd = xstrdup(cmd);
  job->pid = pid;
  job->status = 0;
  do
  {
    if ((job->entry.le_next = (&all_jobs)->lh_first) != 0)
    {
      (&all_jobs)->lh_first->entry.le_prev = &job->entry.le_next;
    }
    (&all_jobs)->lh_first = &job[job_idx];
    job->entry.le_prev = &(&all_jobs)->lh_first;
  }
  while (0);
  job->updatecb = updatecb;
  job->completecb = completecb;
  job->freecb = freecb;
  job->data = data;
  job->fd = out[0];
  setblocking(job->fd, 0);
  job->event = bufferevent_new(job->fd, job_read_callback, job_write_callback, job_error_callback, job);
  bufferevent_enable(job->event, EV_READ | EV_WRITE);
  log_debug("run job %p: %s, pid %ld", job, job->cmd, (long) job->pid);
  return job;
}


----------------------------
void *xmalloc(size_t size)
{
  void *ptr;
  unsigned int ptr_idx = 0;
  if (size == 0)
  {
    fatalx("xmalloc: zero size");
  }
  ptr_idx = malloc(size);
  if ((&ptr[ptr_idx]) == 0)
  {
    fatalx("xmalloc: allocating %zu bytes: %s", size, strerror(errno));
  }
  return ptr;
}


----------------------------
static void format_job_update(struct job *job)
{
  struct format_job *fj = job->data;
  struct evbuffer *evb = job->event->input;
  char *line = 0;
  unsigned int line_idx = 0;
  char *next;
  unsigned int next_idx = 0;
  time_t t;
  while ((next_idx = evbuffer_readline(evb)) != 0)
  {
    free(line);
    line_idx = &next[next_idx];
  }

  if ((&line[line_idx]) == 0)
  {
    return;
  }
  fj->updated = 1;
  free(fj->out);
  fj->out = &line[line_idx];
  log_debug("%s: %p %s: %s", __func__, fj, fj->cmd, fj->out);
  t = time(0);
  if (fj->status && (fj->last != t))
  {
    if (fj->client != 0)
    {
      server_status_client(fj->client);
    }
    fj->last = t;
  }
}


----------------------------
void *xcalloc(size_t nmemb, size_t size)
{
  void *ptr;
  unsigned int ptr_idx = 0;
  if ((size == 0) || (nmemb == 0))
  {
    fatalx("xcalloc: zero size");
  }
  ptr_idx = calloc(nmemb, size);
  if ((&ptr[ptr_idx]) == 0)
  {
    fatalx("xcalloc: allocating %zu * %zu bytes: %s", nmemb, size, strerror(errno));
  }
  return ptr;
}


----------------------------
static struct format_job_tree
{
  struct format_job *rbh_root;
} format_jobs = {0}
----------------------------
static struct format_job *format_job_tree_RB_INSERT(struct format_job_tree *head, struct format_job *elm)
{
  struct format_job *tmp;
  unsigned int tmp_idx = 0;
  struct format_job *parent = 0;
  unsigned int parent_idx = 0;
  int comp = 0;
  tmp_idx = head->rbh_root;
  while (tmp)
  {
    parent_idx = &tmp[tmp_idx];
    comp = format_job_cmp(elm, parent);
    if (comp < 0)
    {
      tmp_idx = tmp_idx->entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->entry.rbe_right;
    }
    else
      return tmp;
  }

  do
  {
    elm->entry.rbe_parent = &parent[parent_idx];
    elm->entry.rbe_left = (elm->entry.rbe_right = 0);
    elm->entry.rbe_color = 1;
  }
  while (0);
  if ((&parent[parent_idx]) != 0)
  {
    if (comp < 0)
    {
      parent->entry.rbe_left = elm;
    }
    else
      parent->entry.rbe_right = elm;
    do
    {
    }
    while (0);
  }
  else
    head->rbh_root = elm;
  format_job_tree_RB_INSERT_COLOR(head, elm);
  return 0;
}


----------------------------
pub time: Time
----------------------------
None
----------------------------
struct job
{
  enum 
  {
    JOB_RUNNING,
    JOB_DEAD,
    JOB_CLOSED
  } state;
  int flags;
  char *cmd;
  pid_t pid;
  int status;
  int fd;
  struct bufferevent *event;
  job_update_cb updatecb;
  job_complete_cb completecb;
  job_free_cb freecb;
  void *data;
  struct 
  {
    struct job *le_next;
    struct job **le_prev;
  } entry;
}
----------------------------
static struct format_job *format_job_tree_RB_FIND(struct format_job_tree *head, struct format_job *elm)
{
  struct format_job *tmp = head->rbh_root;
  unsigned int tmp_idx = 0;
  int comp;
  while (tmp)
  {
    comp = format_job_cmp(elm, tmp);
    if (comp < 0)
    {
      tmp_idx = tmp_idx->entry.rbe_left;
    }
    else
      if (comp > 0)
    {
      tmp_idx = tmp_idx->entry.rbe_right;
    }
    else
      return tmp;
  }

  return 0;
}


----------------------------
char *xstrdup(const char *str)
{
  char *cp;
  unsigned int cp_idx = 0;
  if ((cp_idx = strdup(str)) == 0)
  {
    fatalx("xstrdup: %s", strerror(errno));
  }
  return cp;
}


----------------------------
int xasprintf(char **ret, const char *fmt, ...)
{
  va_list ap;
  int i;
  __builtin_va_start(ap);
  i = xvasprintf(ret, fmt, ap);
  ;
  return i;
}


----------------------------
None
----------------------------
***/


// element in merge of:  helper_format_replace_2,helper_helper_format_expand_1_3,format_expand,format_replace,helper_format_expand_1,helper_helper_format_expand_1_1,format_job_get,helper_helper_format_expand_1_2
// hint:  ['buf_idx_ref is a mutable refrence to unsigned int', 's_idx_ref is a mutable refrence to unsigned int', 'off_ref is a mutable refrence to size_t', 'len_ref is a mutable refrence to size_t', 'n_ref is a mutable refrence to size_t']
void helper_helper_format_expand_1_2(unsigned int * const buf_idx_ref, unsigned int * const s_idx_ref, size_t * const off_ref, size_t * const len_ref, size_t * const n_ref, struct format_tree * const ft, char * const buf, const char * const s, int ch)
{
  unsigned int buf_idx = *buf_idx_ref;
  unsigned int s_idx = *s_idx_ref;
  size_t off = *off_ref;
  size_t len = *len_ref;
  size_t n = *n_ref;
  s_idx = 0;
  if ((ch >= 'A') && (ch <= 'Z'))
  {
    s_idx = format_upper[ch - 'A'];
  }
  else
    if ((ch >= 'a') && (ch <= 'z'))
  {
    s_idx = format_lower[ch - 'a'];
  }
  if ((&s[s_idx]) == 0)
  {
    while ((len - off) < 3)
    {
      buf_idx = xreallocarray(buf_idx, 2, len);
      len *= 2;
    }

    buf[off + buf_idx] = '#';
    off += 1;
    buf[off + buf_idx] = ch;
    off += 1;
    continue;
  }
  n = strlen(s);
  if (format_replace(ft, s, n, &(&buf[buf_idx]), &len, &off) != 0)
  {
    break;
  }
  continue;
  *buf_idx_ref = buf_idx;
  *s_idx_ref = s_idx;
  *off_ref = off;
  *len_ref = len;
  *n_ref = n;
}


/*** DEPENDENCIES:
static const char *format_upper[] = {0, 0, 0, "pane_id", 0, "window_flags", 0, "host", "window_index", 0, 0, 0, 0, 0, 0, "pane_index", 0, 0, "session_name", "pane_title", 0, 0, "window_name", 0, 0, 0}
----------------------------
None
----------------------------
void *xreallocarray(void *ptr, size_t nmemb, size_t size)
{
  void *new_ptr;
  unsigned int new_ptr_idx = 0;
  if ((nmemb == 0) || (size == 0))
  {
    fatalx("xreallocarray: zero size");
  }
  new_ptr_idx = reallocarray(ptr, nmemb, size);
  if ((&new_ptr[new_ptr_idx]) == 0)
  {
    fatalx("xreallocarray: allocating %zu * %zu bytes: %s", nmemb, size, strerror(errno));
  }
  return new_ptr;
}


----------------------------
static const char *format_lower[] = {0, 0, 0, 0, 0, 0, 0, "host_short", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
----------------------------
None
----------------------------
***/


