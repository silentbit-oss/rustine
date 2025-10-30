// hint:  ['buffersize_ref is a mutable refrence to size_t', 'len_ref is a mutable refrence to size_t', 'orig_buffersize_ref is a mutable refrence to size_t', 'pending_shell_escape_end_ref is a mutable refrence to bool']
void helper_helper_helper_quotearg_buffer_restyled_2_3_1(size_t * const buffersize_ref, size_t * const len_ref, size_t * const orig_buffersize_ref, bool * const pending_shell_escape_end_ref, char * const buffer, bool elide_outer_quotes)
{
  size_t buffersize = *buffersize_ref;
  size_t len = *len_ref;
  size_t orig_buffersize = *orig_buffersize_ref;
  bool pending_shell_escape_end = *pending_shell_escape_end_ref;
  if (elide_outer_quotes)
  {
    goto force_outer_quoting_style;
  }
  if (buffersize && (!orig_buffersize))
  {
    orig_buffersize = buffersize;
    buffersize = 0;
  }
  do
  {
    if (len < buffersize)
    {
      buffer[len] = '\'';
    }
    len += 1;
  }
  while (0);
  do
  {
    if (len < buffersize)
    {
      buffer[len] = '\\';
    }
    len += 1;
  }
  while (0);
  do
  {
    if (len < buffersize)
    {
      buffer[len] = '\'';
    }
    len += 1;
  }
  while (0);
  pending_shell_escape_end = 0;
  *buffersize_ref = buffersize;
  *len_ref = len;
  *orig_buffersize_ref = orig_buffersize;
  *pending_shell_escape_end_ref = pending_shell_escape_end;
}


/*** DEPENDENCIES:
***/


// hint:  ['i_ref is a mutable refrence to size_t', 'len_ref is a mutable refrence to size_t', 'c_ref is a mutable refrence to unsigned char']
void helper_helper_helper_helper_quotearg_buffer_restyled_2_4_1_1(size_t * const i_ref, size_t * const len_ref, unsigned char * const c_ref, char * const buffer, const char * const arg, bool elide_outer_quotes, size_t buffersize)
{
  size_t i = *i_ref;
  size_t len = *len_ref;
  unsigned char c = *c_ref;
  switch (arg[i + 2])
  {
    case '!':

    case '\'':

    case '(':

    case ')':

    case '-':

    case '/':

    case '<':

    case '=':

    case '>':
    {
      if (elide_outer_quotes)
      {
        goto force_outer_quoting_style;
      }
      c = arg[i + 2];
      i += 2;
      do
      {
        if (len < buffersize)
        {
          buffer[len] = '?';
        }
        len += 1;
      }
      while (0);
      do
      {
        if (len < buffersize)
        {
          buffer[len] = '"';
        }
        len += 1;
      }
      while (0);
      do
      {
        if (len < buffersize)
        {
          buffer[len] = '"';
        }
        len += 1;
      }
      while (0);
      do
      {
        if (len < buffersize)
        {
          buffer[len] = '?';
        }
        len += 1;
      }
      while (0);
      break;
    }

    default:
    {
      break;
    }

  }

  *i_ref = i;
  *len_ref = len;
  *c_ref = c;
}


/*** DEPENDENCIES:
***/


static const char *gettext_quote(const char *msgid, enum quoting_style s)
{
  const char *translation = gettext(msgid);
  const char *locale_code;
  unsigned int locale_code_idx = 0;
  if (translation != msgid)
  {
    return translation;
  }
  locale_code_idx = locale_charset();
  if (c_strcasecmp(locale_code, "UTF-8") == 0)
  {
    return (msgid[0] == '`') ? ("\xe2\x80\x98") : ("\xe2\x80\x99");
  }
  if (c_strcasecmp(locale_code, "GB18030") == 0)
  {
    return (msgid[0] == '`') ? ("\xa1\ae") : ("\xa1\xaf");
  }
  return (s == clocale_quoting_style) ? ("\"") : ("'");
}


/*** DEPENDENCIES:
int c_strcasecmp(const char *s1, const char *s2)
{
  register const unsigned char *p1 = (const unsigned char *) s1;
  unsigned int p1_idx = 0;
  register const unsigned char *p2 = (const unsigned char *) s2;
  unsigned int p2_idx = 0;
  unsigned char c1;
  unsigned char c2;
  if ((&p1[p1_idx]) == (&p2[p2_idx]))
  {
    return 0;
  }
  do
  {
    c1 = c_tolower(*(&p1[p1_idx]));
    c2 = c_tolower(*(&p2[p2_idx]));
    if (c1 == '\0')
    {
      break;
    }
    p1_idx += 1;
    p2_idx += 1;
  }
  while (c1 == c2);
  if (255 <= 2147483647)
  {
    return c1 - c2;
  }
  else
    return (c1 > c2) - (c1 < c2);
}


----------------------------
const char *locale_charset(void)
{
  const char *codeset;
  unsigned int codeset_idx = 0;
  codeset_idx = nl_langinfo(CODESET);
  if ((&codeset[codeset_idx]) == 0)
  {
    codeset_idx = "";
  }
  {
    {
      if (codeset[0 + codeset_idx] == '\0')
      {
        codeset_idx = "ASCII";
      }
    }
  }
  return codeset;
}


----------------------------
enum quoting_style
{
  literal_quoting_style,
  shell_quoting_style,
  shell_always_quoting_style,
  shell_escape_quoting_style,
  shell_escape_always_quoting_style,
  c_quoting_style,
  c_maybe_quoting_style,
  escape_quoting_style,
  locale_quoting_style,
  clocale_quoting_style,
  custom_quoting_style
}
----------------------------
***/


// hint:  ['right_quote_idx_ref is a mutable refrence to unsigned int', 'left_quote_idx_ref is a mutable refrence to unsigned int', 'len_ref is a mutable refrence to size_t', 'quote_string_idx_ref is a mutable refrence to unsigned int', 'quote_string_len_ref is a mutable refrence to size_t', 'backslash_escapes_ref is a mutable refrence to bool']
void helper_quotearg_buffer_restyled_1(unsigned int * const right_quote_idx_ref, unsigned int * const left_quote_idx_ref, size_t * const len_ref, unsigned int * const quote_string_idx_ref, size_t * const quote_string_len_ref, bool * const backslash_escapes_ref, char * const buffer, size_t buffersize, enum quoting_style quoting_style, const char * const left_quote, const char * const right_quote, const char * const quote_string, bool elide_outer_quotes)
{
  unsigned int right_quote_idx = *right_quote_idx_ref;
  unsigned int left_quote_idx = *left_quote_idx_ref;
  size_t len = *len_ref;
  unsigned int quote_string_idx = *quote_string_idx_ref;
  size_t quote_string_len = *quote_string_len_ref;
  bool backslash_escapes = *backslash_escapes_ref;
  {
    if (quoting_style != custom_quoting_style)
    {
      left_quote_idx = gettext_quote("`", quoting_style);
      right_quote_idx = gettext_quote("'", quoting_style);
    }
    if (!elide_outer_quotes)
    {
      for (quote_string_idx = &left_quote[left_quote_idx]; quote_string[quote_string_idx]; quote_string_idx += 1)
      {
        do
        {
          if (len < buffersize)
          {
            buffer[len] = quote_string[quote_string_idx];
          }
          len += 1;
        }
        while (0);
      }

    }
    backslash_escapes = 1;
    quote_string_idx = &right_quote[right_quote_idx];
    quote_string_len = strlen(quote_string);
  }
  break;
  *right_quote_idx_ref = right_quote_idx;
  *left_quote_idx_ref = left_quote_idx;
  *len_ref = len;
  *quote_string_idx_ref = quote_string_idx;
  *quote_string_len_ref = quote_string_len;
  *backslash_escapes_ref = backslash_escapes;
}


/*** DEPENDENCIES:
enum quoting_style
{
  literal_quoting_style,
  shell_quoting_style,
  shell_always_quoting_style,
  shell_escape_quoting_style,
  shell_escape_always_quoting_style,
  c_quoting_style,
  c_maybe_quoting_style,
  escape_quoting_style,
  locale_quoting_style,
  clocale_quoting_style,
  custom_quoting_style
}
----------------------------
static const char *gettext_quote(const char *msgid, enum quoting_style s)
{
  const char *translation = gettext(msgid);
  const char *locale_code;
  unsigned int locale_code_idx = 0;
  if (translation != msgid)
  {
    return translation;
  }
  locale_code_idx = locale_charset();
  if (c_strcasecmp(locale_code, "UTF-8") == 0)
  {
    return (msgid[0] == '`') ? ("\xe2\x80\x98") : ("\xe2\x80\x99");
  }
  if (c_strcasecmp(locale_code, "GB18030") == 0)
  {
    return (msgid[0] == '`') ? ("\xa1\ae") : ("\xa1\xaf");
  }
  return (s == clocale_quoting_style) ? ("\"") : ("'");
}


----------------------------
***/


// hint:  ['len_ref is a mutable refrence to size_t', 'pending_shell_escape_end_ref is a mutable refrence to bool', 'escaping_ref is a mutable refrence to bool']
void helper_helper_quotearg_buffer_restyled_2_2(size_t * const len_ref, bool * const pending_shell_escape_end_ref, bool * const escaping_ref, char * const buffer, enum quoting_style quoting_style, bool elide_outer_quotes, size_t buffersize)
{
  size_t len = *len_ref;
  bool pending_shell_escape_end = *pending_shell_escape_end_ref;
  bool escaping = *escaping_ref;
  if (elide_outer_quotes)
  {
    goto force_outer_quoting_style;
  }
  escaping = 1;
  if ((quoting_style == shell_always_quoting_style) && (!pending_shell_escape_end))
  {
    do
    {
      if (len < buffersize)
      {
        buffer[len] = '\'';
      }
      len += 1;
    }
    while (0);
    do
    {
      if (len < buffersize)
      {
        buffer[len] = '$';
      }
      len += 1;
    }
    while (0);
    do
    {
      if (len < buffersize)
      {
        buffer[len] = '\'';
      }
      len += 1;
    }
    while (0);
    pending_shell_escape_end = 1;
  }
  do
  {
    if (len < buffersize)
    {
      buffer[len] = '\\';
    }
    len += 1;
  }
  while (0);
  *len_ref = len;
  *pending_shell_escape_end_ref = pending_shell_escape_end;
  *escaping_ref = escaping;
}


/*** DEPENDENCIES:
enum quoting_style
{
  literal_quoting_style,
  shell_quoting_style,
  shell_always_quoting_style,
  shell_escape_quoting_style,
  shell_escape_always_quoting_style,
  c_quoting_style,
  c_maybe_quoting_style,
  escape_quoting_style,
  locale_quoting_style,
  clocale_quoting_style,
  custom_quoting_style
}
----------------------------
***/


// hint:  ['m_ref is a mutable refrence to size_t', 'printable_ref is a mutable refrence to bool']
void helper_helper_helper_helper_quotearg_buffer_restyled_2_6_1_1(size_t * const m_ref, bool * const printable_ref, const char * const arg, enum quoting_style quoting_style, bool elide_outer_quotes, size_t i, size_t argsize, mbstate_t mbstate)
{
  size_t m = *m_ref;
  bool printable = *printable_ref;
  char32_t w;
  size_t bytes = mbrtoc32(&w, &arg[i + m], argsize - (i + m), &mbstate);
  if (bytes == 0)
  {
    break;
  }
  else
    if (bytes == ((size_t) (-1)))
  {
    printable = 0;
    break;
  }
  else
    if (bytes == ((size_t) (-2)))
  {
    printable = 0;
    while (((i + m) < argsize) && arg[i + m])
    {
      m += 1;
    }

    break;
  }
  else
  {
    if ((('[' == 0x5b) && elide_outer_quotes) && (quoting_style == shell_always_quoting_style))
    {
      size_t j;
      for (j = 1; j < bytes; j += 1)
      {
        switch (arg[(i + m) + j])
        {
          case '[':

          case '\\':

          case '^':

          case '`':

          case '|':
          {
            goto force_outer_quoting_style;
          }

          default:
          {
            break;
          }

        }

      }

    }
    if (!c32isprint(w))
    {
      printable = 0;
    }
    m += bytes;
  }
  break;
  *m_ref = m;
  *printable_ref = printable;
}


/*** DEPENDENCIES:
size_t mbrtoc32(char32_t *pwc, const char *s, size_t n, mbstate_t *ps)
{
  unsigned int ps_idx = 0;
  unsigned int s_idx = 0;
  unsigned int pwc_idx = 0;
  if ((&s[s_idx]) == 0)
  {
    pwc_idx = 0;
    s_idx = "";
    n = 1;
  }
  if ((&ps[ps_idx]) == 0)
  {
    ps_idx = &internal_state;
  }
  size_t ret = mbrtoc32(pwc, s, n, ps);
  if ((ret < ((size_t) (-3))) && (!mbsinit(ps)))
  {
    mbszero(ps);
  }
  if (ret == ((size_t) (-3)))
  {
    abort();
  }
  if (((((size_t) (-2)) <= ret) && (n != 0)) && (!hard_locale(LC_CTYPE)))
  {
    if ((&pwc[pwc_idx]) != 0)
    {
      pwc[pwc_idx] = (unsigned char) s[s_idx];
    }
    return 1;
  }
  return ret;
}


----------------------------
enum quoting_style
{
  literal_quoting_style,
  shell_quoting_style,
  shell_always_quoting_style,
  shell_escape_quoting_style,
  shell_escape_always_quoting_style,
  c_quoting_style,
  c_maybe_quoting_style,
  escape_quoting_style,
  locale_quoting_style,
  clocale_quoting_style,
  custom_quoting_style
}
----------------------------
int c32isprint(wint_t wc)
{
  if (wc != WEOF)
  {
    return uc_is_print(wc);
  }
  else
    return 0;
}


----------------------------
***/


// hint:  ['argsize_ref is a mutable refrence to size_t', 'm_ref is a mutable refrence to size_t', 'printable_ref is a mutable refrence to bool']
void helper_helper_helper_quotearg_buffer_restyled_2_6_1(size_t * const argsize_ref, size_t * const m_ref, bool * const printable_ref, const char * const arg, enum quoting_style quoting_style, bool elide_outer_quotes, size_t i)
{
  size_t argsize = *argsize_ref;
  size_t m = *m_ref;
  bool printable = *printable_ref;
  mbstate_t mbstate;
  mbszero(&mbstate);
  m = 0;
  printable = 1;
  if (argsize == ((size_t) (-1)))
  {
    argsize = strlen(arg);
  }
  for (;;)
  {
    helper_helper_helper_helper_quotearg_buffer_restyled_2_6_1_1(&m, &printable, arg, quoting_style, elide_outer_quotes, i, argsize, mbstate);
  }

  *argsize_ref = argsize;
  *m_ref = m;
  *printable_ref = printable;
}


/*** DEPENDENCIES:
enum quoting_style
{
  literal_quoting_style,
  shell_quoting_style,
  shell_always_quoting_style,
  shell_escape_quoting_style,
  shell_escape_always_quoting_style,
  c_quoting_style,
  c_maybe_quoting_style,
  escape_quoting_style,
  locale_quoting_style,
  clocale_quoting_style,
  custom_quoting_style
}
----------------------------
void helper_helper_helper_helper_quotearg_buffer_restyled_2_6_1_1(size_t * const m_ref, bool * const printable_ref, const char * const arg, enum quoting_style quoting_style, bool elide_outer_quotes, size_t i, size_t argsize, mbstate_t mbstate)
{
  size_t m = *m_ref;
  bool printable = *printable_ref;
  char32_t w;
  size_t bytes = mbrtoc32(&w, &arg[i + m], argsize - (i + m), &mbstate);
  if (bytes == 0)
  {
    break;
  }
  else
    if (bytes == ((size_t) (-1)))
  {
    printable = 0;
    break;
  }
  else
    if (bytes == ((size_t) (-2)))
  {
    printable = 0;
    while (((i + m) < argsize) && arg[i + m])
    {
      m += 1;
    }

    break;
  }
  else
  {
    if ((('[' == 0x5b) && elide_outer_quotes) && (quoting_style == shell_always_quoting_style))
    {
      size_t j;
      for (j = 1; j < bytes; j += 1)
      {
        switch (arg[(i + m) + j])
        {
          case '[':

          case '\\':

          case '^':

          case '`':

          case '|':
          {
            goto force_outer_quoting_style;
          }

          default:
          {
            break;
          }

        }

      }

    }
    if (!c32isprint(w))
    {
      printable = 0;
    }
    m += bytes;
  }
  break;
  *m_ref = m;
  *printable_ref = printable;
}


----------------------------
***/


// hint:  ['i_ref is a mutable refrence to size_t', 'len_ref is a mutable refrence to size_t', 'pending_shell_escape_end_ref is a mutable refrence to bool', 'c_ref is a mutable refrence to unsigned char', 'is_right_quote_ref is a mutable refrence to bool', 'escaping_ref is a mutable refrence to bool']
void helper_helper_helper_helper_quotearg_buffer_restyled_2_6_2_1(size_t * const i_ref, size_t * const len_ref, bool * const pending_shell_escape_end_ref, unsigned char * const c_ref, bool * const is_right_quote_ref, bool * const escaping_ref, char * const buffer, const char * const arg, enum quoting_style quoting_style, bool backslash_escapes, bool elide_outer_quotes, size_t buffersize, bool printable, size_t ilim)
{
  size_t i = *i_ref;
  size_t len = *len_ref;
  bool pending_shell_escape_end = *pending_shell_escape_end_ref;
  unsigned char c = *c_ref;
  bool is_right_quote = *is_right_quote_ref;
  bool escaping = *escaping_ref;
  if (backslash_escapes && (!printable))
  {
    do
    {
      if (elide_outer_quotes)
      {
        goto force_outer_quoting_style;
      }
      escaping = 1;
      if ((quoting_style == shell_always_quoting_style) && (!pending_shell_escape_end))
      {
        do
        {
          if (len < buffersize)
          {
            buffer[len] = '\'';
          }
          len += 1;
        }
        while (0);
        do
        {
          if (len < buffersize)
          {
            buffer[len] = '$';
          }
          len += 1;
        }
        while (0);
        do
        {
          if (len < buffersize)
          {
            buffer[len] = '\'';
          }
          len += 1;
        }
        while (0);
        pending_shell_escape_end = 1;
      }
      do
      {
        if (len < buffersize)
        {
          buffer[len] = '\\';
        }
        len += 1;
      }
      while (0);
    }
    while (0);
    do
    {
      if (len < buffersize)
      {
        buffer[len] = '0' + (c >> 6);
      }
      len += 1;
    }
    while (0);
    do
    {
      if (len < buffersize)
      {
        buffer[len] = '0' + ((c >> 3) & 7);
      }
      len += 1;
    }
    while (0);
    c = '0' + (c & 7);
  }
  else
    if (is_right_quote)
  {
    do
    {
      if (len < buffersize)
      {
        buffer[len] = '\\';
      }
      len += 1;
    }
    while (0);
    is_right_quote = 0;
  }
  if (ilim <= (i + 1))
  {
    break;
  }
  do
  {
    if (pending_shell_escape_end && (!escaping))
    {
      do
      {
        if (len < buffersize)
        {
          buffer[len] = '\'';
        }
        len += 1;
      }
      while (0);
      do
      {
        if (len < buffersize)
        {
          buffer[len] = '\'';
        }
        len += 1;
      }
      while (0);
      pending_shell_escape_end = 0;
    }
  }
  while (0);
  do
  {
    if (len < buffersize)
    {
      buffer[len] = c;
    }
    len += 1;
  }
  while (0);
  i += 1;
  c = arg[i];
  *i_ref = i;
  *len_ref = len;
  *pending_shell_escape_end_ref = pending_shell_escape_end;
  *c_ref = c;
  *is_right_quote_ref = is_right_quote;
  *escaping_ref = escaping;
}


/*** DEPENDENCIES:
enum quoting_style
{
  literal_quoting_style,
  shell_quoting_style,
  shell_always_quoting_style,
  shell_escape_quoting_style,
  shell_escape_always_quoting_style,
  c_quoting_style,
  c_maybe_quoting_style,
  escape_quoting_style,
  locale_quoting_style,
  clocale_quoting_style,
  custom_quoting_style
}
----------------------------
***/


// hint:  ['i_ref is a mutable refrence to size_t', 'len_ref is a mutable refrence to size_t', 'pending_shell_escape_end_ref is a mutable refrence to bool', 'c_ref is a mutable refrence to unsigned char', 'is_right_quote_ref is a mutable refrence to bool', 'escaping_ref is a mutable refrence to bool']
void helper_helper_helper_quotearg_buffer_restyled_2_6_2(size_t * const i_ref, size_t * const len_ref, bool * const pending_shell_escape_end_ref, unsigned char * const c_ref, bool * const is_right_quote_ref, bool * const escaping_ref, char * const buffer, const char * const arg, enum quoting_style quoting_style, bool backslash_escapes, bool elide_outer_quotes, size_t buffersize, size_t m, bool printable)
{
  size_t i = *i_ref;
  size_t len = *len_ref;
  bool pending_shell_escape_end = *pending_shell_escape_end_ref;
  unsigned char c = *c_ref;
  bool is_right_quote = *is_right_quote_ref;
  bool escaping = *escaping_ref;
  size_t ilim = i + m;
  for (;;)
  {
    helper_helper_helper_helper_quotearg_buffer_restyled_2_6_2_1(&i, &len, &pending_shell_escape_end, &c, &is_right_quote, &escaping, buffer, arg, quoting_style, backslash_escapes, elide_outer_quotes, buffersize, printable, ilim);
  }

  goto store_c;
  *i_ref = i;
  *len_ref = len;
  *pending_shell_escape_end_ref = pending_shell_escape_end;
  *c_ref = c;
  *is_right_quote_ref = is_right_quote;
  *escaping_ref = escaping;
}


/*** DEPENDENCIES:
void helper_helper_helper_helper_quotearg_buffer_restyled_2_6_2_1(size_t * const i_ref, size_t * const len_ref, bool * const pending_shell_escape_end_ref, unsigned char * const c_ref, bool * const is_right_quote_ref, bool * const escaping_ref, char * const buffer, const char * const arg, enum quoting_style quoting_style, bool backslash_escapes, bool elide_outer_quotes, size_t buffersize, bool printable, size_t ilim)
{
  size_t i = *i_ref;
  size_t len = *len_ref;
  bool pending_shell_escape_end = *pending_shell_escape_end_ref;
  unsigned char c = *c_ref;
  bool is_right_quote = *is_right_quote_ref;
  bool escaping = *escaping_ref;
  if (backslash_escapes && (!printable))
  {
    do
    {
      if (elide_outer_quotes)
      {
        goto force_outer_quoting_style;
      }
      escaping = 1;
      if ((quoting_style == shell_always_quoting_style) && (!pending_shell_escape_end))
      {
        do
        {
          if (len < buffersize)
          {
            buffer[len] = '\'';
          }
          len += 1;
        }
        while (0);
        do
        {
          if (len < buffersize)
          {
            buffer[len] = '$';
          }
          len += 1;
        }
        while (0);
        do
        {
          if (len < buffersize)
          {
            buffer[len] = '\'';
          }
          len += 1;
        }
        while (0);
        pending_shell_escape_end = 1;
      }
      do
      {
        if (len < buffersize)
        {
          buffer[len] = '\\';
        }
        len += 1;
      }
      while (0);
    }
    while (0);
    do
    {
      if (len < buffersize)
      {
        buffer[len] = '0' + (c >> 6);
      }
      len += 1;
    }
    while (0);
    do
    {
      if (len < buffersize)
      {
        buffer[len] = '0' + ((c >> 3) & 7);
      }
      len += 1;
    }
    while (0);
    c = '0' + (c & 7);
  }
  else
    if (is_right_quote)
  {
    do
    {
      if (len < buffersize)
      {
        buffer[len] = '\\';
      }
      len += 1;
    }
    while (0);
    is_right_quote = 0;
  }
  if (ilim <= (i + 1))
  {
    break;
  }
  do
  {
    if (pending_shell_escape_end && (!escaping))
    {
      do
      {
        if (len < buffersize)
        {
          buffer[len] = '\'';
        }
        len += 1;
      }
      while (0);
      do
      {
        if (len < buffersize)
        {
          buffer[len] = '\'';
        }
        len += 1;
      }
      while (0);
      pending_shell_escape_end = 0;
    }
  }
  while (0);
  do
  {
    if (len < buffersize)
    {
      buffer[len] = c;
    }
    len += 1;
  }
  while (0);
  i += 1;
  c = arg[i];
  *i_ref = i;
  *len_ref = len;
  *pending_shell_escape_end_ref = pending_shell_escape_end;
  *c_ref = c;
  *is_right_quote_ref = is_right_quote;
  *escaping_ref = escaping;
}


----------------------------
enum quoting_style
{
  literal_quoting_style,
  shell_quoting_style,
  shell_always_quoting_style,
  shell_escape_quoting_style,
  shell_escape_always_quoting_style,
  c_quoting_style,
  c_maybe_quoting_style,
  escape_quoting_style,
  locale_quoting_style,
  clocale_quoting_style,
  custom_quoting_style
}
----------------------------
***/


// hint:  ['argsize_ref is a mutable refrence to size_t', 'i_ref is a mutable refrence to size_t', 'len_ref is a mutable refrence to size_t', 'pending_shell_escape_end_ref is a mutable refrence to bool', 'c_ref is a mutable refrence to unsigned char', 'is_right_quote_ref is a mutable refrence to bool', 'escaping_ref is a mutable refrence to bool', 'c_and_shell_quote_compat_ref is a mutable refrence to bool']
void helper_helper_quotearg_buffer_restyled_2_6(size_t * const argsize_ref, size_t * const i_ref, size_t * const len_ref, bool * const pending_shell_escape_end_ref, unsigned char * const c_ref, bool * const is_right_quote_ref, bool * const escaping_ref, bool * const c_and_shell_quote_compat_ref, char * const buffer, const char * const arg, enum quoting_style quoting_style, bool backslash_escapes, bool unibyte_locale, bool elide_outer_quotes, size_t buffersize)
{
  size_t argsize = *argsize_ref;
  size_t i = *i_ref;
  size_t len = *len_ref;
  bool pending_shell_escape_end = *pending_shell_escape_end_ref;
  unsigned char c = *c_ref;
  bool is_right_quote = *is_right_quote_ref;
  bool escaping = *escaping_ref;
  bool c_and_shell_quote_compat = *c_and_shell_quote_compat_ref;
  size_t m;
  bool printable;
  if (unibyte_locale)
  {
    m = 1;
    printable = isprint(c) != 0;
  }
  else
  {
    helper_helper_helper_quotearg_buffer_restyled_2_6_1(&argsize, &m, &printable, arg, quoting_style, elide_outer_quotes, i);
  }
  c_and_shell_quote_compat = printable;
  if ((1 < m) || (backslash_escapes && (!printable)))
  {
    helper_helper_helper_quotearg_buffer_restyled_2_6_2(&i, &len, &pending_shell_escape_end, &c, &is_right_quote, &escaping, buffer, arg, quoting_style, backslash_escapes, elide_outer_quotes, buffersize, m, printable);
  }
  *argsize_ref = argsize;
  *i_ref = i;
  *len_ref = len;
  *pending_shell_escape_end_ref = pending_shell_escape_end;
  *c_ref = c;
  *is_right_quote_ref = is_right_quote;
  *escaping_ref = escaping;
  *c_and_shell_quote_compat_ref = c_and_shell_quote_compat;
}


/*** DEPENDENCIES:
void helper_helper_helper_quotearg_buffer_restyled_2_6_1(size_t * const argsize_ref, size_t * const m_ref, bool * const printable_ref, const char * const arg, enum quoting_style quoting_style, bool elide_outer_quotes, size_t i)
{
  size_t argsize = *argsize_ref;
  size_t m = *m_ref;
  bool printable = *printable_ref;
  mbstate_t mbstate;
  mbszero(&mbstate);
  m = 0;
  printable = 1;
  if (argsize == ((size_t) (-1)))
  {
    argsize = strlen(arg);
  }
  for (;;)
  {
    helper_helper_helper_helper_quotearg_buffer_restyled_2_6_1_1(&m, &printable, arg, quoting_style, elide_outer_quotes, i, argsize, mbstate);
  }

  *argsize_ref = argsize;
  *m_ref = m;
  *printable_ref = printable;
}


----------------------------
void helper_helper_helper_quotearg_buffer_restyled_2_6_2(size_t * const i_ref, size_t * const len_ref, bool * const pending_shell_escape_end_ref, unsigned char * const c_ref, bool * const is_right_quote_ref, bool * const escaping_ref, char * const buffer, const char * const arg, enum quoting_style quoting_style, bool backslash_escapes, bool elide_outer_quotes, size_t buffersize, size_t m, bool printable)
{
  size_t i = *i_ref;
  size_t len = *len_ref;
  bool pending_shell_escape_end = *pending_shell_escape_end_ref;
  unsigned char c = *c_ref;
  bool is_right_quote = *is_right_quote_ref;
  bool escaping = *escaping_ref;
  size_t ilim = i + m;
  for (;;)
  {
    helper_helper_helper_helper_quotearg_buffer_restyled_2_6_2_1(&i, &len, &pending_shell_escape_end, &c, &is_right_quote, &escaping, buffer, arg, quoting_style, backslash_escapes, elide_outer_quotes, buffersize, printable, ilim);
  }

  goto store_c;
  *i_ref = i;
  *len_ref = len;
  *pending_shell_escape_end_ref = pending_shell_escape_end;
  *c_ref = c;
  *is_right_quote_ref = is_right_quote;
  *escaping_ref = escaping;
}


----------------------------
enum quoting_style
{
  literal_quoting_style,
  shell_quoting_style,
  shell_always_quoting_style,
  shell_escape_quoting_style,
  shell_escape_always_quoting_style,
  c_quoting_style,
  c_maybe_quoting_style,
  escape_quoting_style,
  locale_quoting_style,
  clocale_quoting_style,
  custom_quoting_style
}
----------------------------
***/


// hint:  ['c_ref is a mutable refrence to unsigned char', 'esc_ref is a mutable refrence to unsigned char']
void helper_helper_quotearg_buffer_restyled_2_1(unsigned char * const c_ref, unsigned char * const esc_ref, enum quoting_style quoting_style, size_t quote_string_len, bool backslash_escapes, bool elide_outer_quotes)
{
  unsigned char c = *c_ref;
  unsigned char esc = *esc_ref;
  esc = c;
  if (quoting_style == shell_always_quoting_style)
  {
    if (elide_outer_quotes)
    {
      goto force_outer_quoting_style;
    }
    goto store_c;
  }
  if ((backslash_escapes && elide_outer_quotes) && quote_string_len)
  {
    goto store_c;
  }
  c_and_shell_escape:
  if ((quoting_style == shell_always_quoting_style) && elide_outer_quotes)
  {
    goto force_outer_quoting_style;
  }

  c_escape:
  if (backslash_escapes)
  {
    c = esc;
    goto store_escape;
  }

  break;
  *c_ref = c;
  *esc_ref = esc;
}


/*** DEPENDENCIES:
enum quoting_style
{
  literal_quoting_style,
  shell_quoting_style,
  shell_always_quoting_style,
  shell_escape_quoting_style,
  shell_escape_always_quoting_style,
  c_quoting_style,
  c_maybe_quoting_style,
  escape_quoting_style,
  locale_quoting_style,
  clocale_quoting_style,
  custom_quoting_style
}
----------------------------
***/


// hint:  ['buffersize_ref is a mutable refrence to size_t', 'len_ref is a mutable refrence to size_t', 'orig_buffersize_ref is a mutable refrence to size_t', 'encountered_single_quote_ref is a mutable refrence to bool', 'pending_shell_escape_end_ref is a mutable refrence to bool', 'c_and_shell_quote_compat_ref is a mutable refrence to bool']
void helper_helper_quotearg_buffer_restyled_2_3(size_t * const buffersize_ref, size_t * const len_ref, size_t * const orig_buffersize_ref, bool * const encountered_single_quote_ref, bool * const pending_shell_escape_end_ref, bool * const c_and_shell_quote_compat_ref, char * const buffer, enum quoting_style quoting_style, bool elide_outer_quotes)
{
  size_t buffersize = *buffersize_ref;
  size_t len = *len_ref;
  size_t orig_buffersize = *orig_buffersize_ref;
  bool encountered_single_quote = *encountered_single_quote_ref;
  bool pending_shell_escape_end = *pending_shell_escape_end_ref;
  bool c_and_shell_quote_compat = *c_and_shell_quote_compat_ref;
  encountered_single_quote = 1;
  c_and_shell_quote_compat = 1;
  if (quoting_style == shell_always_quoting_style)
  {
    helper_helper_helper_quotearg_buffer_restyled_2_3_1(&buffersize, &len, &orig_buffersize, &pending_shell_escape_end, buffer, elide_outer_quotes);
  }
  break;
  *buffersize_ref = buffersize;
  *len_ref = len;
  *orig_buffersize_ref = orig_buffersize;
  *encountered_single_quote_ref = encountered_single_quote;
  *pending_shell_escape_end_ref = pending_shell_escape_end;
  *c_and_shell_quote_compat_ref = c_and_shell_quote_compat;
}


/*** DEPENDENCIES:
void helper_helper_helper_quotearg_buffer_restyled_2_3_1(size_t * const buffersize_ref, size_t * const len_ref, size_t * const orig_buffersize_ref, bool * const pending_shell_escape_end_ref, char * const buffer, bool elide_outer_quotes)
{
  size_t buffersize = *buffersize_ref;
  size_t len = *len_ref;
  size_t orig_buffersize = *orig_buffersize_ref;
  bool pending_shell_escape_end = *pending_shell_escape_end_ref;
  if (elide_outer_quotes)
  {
    goto force_outer_quoting_style;
  }
  if (buffersize && (!orig_buffersize))
  {
    orig_buffersize = buffersize;
    buffersize = 0;
  }
  do
  {
    if (len < buffersize)
    {
      buffer[len] = '\'';
    }
    len += 1;
  }
  while (0);
  do
  {
    if (len < buffersize)
    {
      buffer[len] = '\\';
    }
    len += 1;
  }
  while (0);
  do
  {
    if (len < buffersize)
    {
      buffer[len] = '\'';
    }
    len += 1;
  }
  while (0);
  pending_shell_escape_end = 0;
  *buffersize_ref = buffersize;
  *len_ref = len;
  *orig_buffersize_ref = orig_buffersize;
  *pending_shell_escape_end_ref = pending_shell_escape_end;
}


----------------------------
enum quoting_style
{
  literal_quoting_style,
  shell_quoting_style,
  shell_always_quoting_style,
  shell_escape_quoting_style,
  shell_escape_always_quoting_style,
  c_quoting_style,
  c_maybe_quoting_style,
  escape_quoting_style,
  locale_quoting_style,
  clocale_quoting_style,
  custom_quoting_style
}
----------------------------
***/


// hint:  ['i_ref is a mutable refrence to size_t', 'len_ref is a mutable refrence to size_t', 'c_ref is a mutable refrence to unsigned char']
void helper_helper_helper_quotearg_buffer_restyled_2_4_1(size_t * const i_ref, size_t * const len_ref, unsigned char * const c_ref, char * const buffer, const char * const arg, int flags, bool elide_outer_quotes, size_t buffersize, size_t argsize)
{
  size_t i = *i_ref;
  size_t len = *len_ref;
  unsigned char c = *c_ref;
  if (((flags & QA_SPLIT_TRIGRAPHS) && ((i + 2) < argsize)) && (arg[i + 1] == '?'))
  {
    helper_helper_helper_helper_quotearg_buffer_restyled_2_4_1_1(&i, &len, &c, buffer, arg, elide_outer_quotes, buffersize);
  }
  break;
  *i_ref = i;
  *len_ref = len;
  *c_ref = c;
}


/*** DEPENDENCIES:
void helper_helper_helper_helper_quotearg_buffer_restyled_2_4_1_1(size_t * const i_ref, size_t * const len_ref, unsigned char * const c_ref, char * const buffer, const char * const arg, bool elide_outer_quotes, size_t buffersize)
{
  size_t i = *i_ref;
  size_t len = *len_ref;
  unsigned char c = *c_ref;
  switch (arg[i + 2])
  {
    case '!':

    case '\'':

    case '(':

    case ')':

    case '-':

    case '/':

    case '<':

    case '=':

    case '>':
    {
      if (elide_outer_quotes)
      {
        goto force_outer_quoting_style;
      }
      c = arg[i + 2];
      i += 2;
      do
      {
        if (len < buffersize)
        {
          buffer[len] = '?';
        }
        len += 1;
      }
      while (0);
      do
      {
        if (len < buffersize)
        {
          buffer[len] = '"';
        }
        len += 1;
      }
      while (0);
      do
      {
        if (len < buffersize)
        {
          buffer[len] = '"';
        }
        len += 1;
      }
      while (0);
      do
      {
        if (len < buffersize)
        {
          buffer[len] = '?';
        }
        len += 1;
      }
      while (0);
      break;
    }

    default:
    {
      break;
    }

  }

  *i_ref = i;
  *len_ref = len;
  *c_ref = c;
}


----------------------------
***/


// hint:  ['i_ref is a mutable refrence to size_t', 'len_ref is a mutable refrence to size_t', 'c_ref is a mutable refrence to unsigned char']
void helper_helper_quotearg_buffer_restyled_2_4(size_t * const i_ref, size_t * const len_ref, unsigned char * const c_ref, char * const buffer, const char * const arg, enum quoting_style quoting_style, int flags, bool elide_outer_quotes, size_t buffersize, size_t argsize)
{
  size_t i = *i_ref;
  size_t len = *len_ref;
  unsigned char c = *c_ref;
  switch (quoting_style)
  {
    case shell_always_quoting_style:
    {
      if (elide_outer_quotes)
      {
        goto force_outer_quoting_style;
      }
      break;
    }

    case c_quoting_style:
    {
      helper_helper_helper_quotearg_buffer_restyled_2_4_1(&i, &len, &c, buffer, arg, flags, elide_outer_quotes, buffersize, argsize);
    }

    default:
    {
      break;
    }

  }

  break;
  *i_ref = i;
  *len_ref = len;
  *c_ref = c;
}


/*** DEPENDENCIES:
void helper_helper_helper_quotearg_buffer_restyled_2_4_1(size_t * const i_ref, size_t * const len_ref, unsigned char * const c_ref, char * const buffer, const char * const arg, int flags, bool elide_outer_quotes, size_t buffersize, size_t argsize)
{
  size_t i = *i_ref;
  size_t len = *len_ref;
  unsigned char c = *c_ref;
  if (((flags & QA_SPLIT_TRIGRAPHS) && ((i + 2) < argsize)) && (arg[i + 1] == '?'))
  {
    helper_helper_helper_helper_quotearg_buffer_restyled_2_4_1_1(&i, &len, &c, buffer, arg, elide_outer_quotes, buffersize);
  }
  break;
  *i_ref = i;
  *len_ref = len;
  *c_ref = c;
}


----------------------------
enum quoting_style
{
  literal_quoting_style,
  shell_quoting_style,
  shell_always_quoting_style,
  shell_escape_quoting_style,
  shell_escape_always_quoting_style,
  c_quoting_style,
  c_maybe_quoting_style,
  escape_quoting_style,
  locale_quoting_style,
  clocale_quoting_style,
  custom_quoting_style
}
----------------------------
***/


// hint:  ['len_ref is a mutable refrence to size_t', 'pending_shell_escape_end_ref is a mutable refrence to bool', 'escaping_ref is a mutable refrence to bool']
void helper_helper_helper_helper_quotearg_buffer_restyled_2_5_1_1(size_t * const len_ref, bool * const pending_shell_escape_end_ref, bool * const escaping_ref, char * const buffer, enum quoting_style quoting_style, bool elide_outer_quotes, size_t buffersize)
{
  size_t len = *len_ref;
  bool pending_shell_escape_end = *pending_shell_escape_end_ref;
  bool escaping = *escaping_ref;
  if (elide_outer_quotes)
  {
    goto force_outer_quoting_style;
  }
  escaping = 1;
  if ((quoting_style == shell_always_quoting_style) && (!pending_shell_escape_end))
  {
    do
    {
      if (len < buffersize)
      {
        buffer[len] = '\'';
      }
      len += 1;
    }
    while (0);
    do
    {
      if (len < buffersize)
      {
        buffer[len] = '$';
      }
      len += 1;
    }
    while (0);
    do
    {
      if (len < buffersize)
      {
        buffer[len] = '\'';
      }
      len += 1;
    }
    while (0);
    pending_shell_escape_end = 1;
  }
  do
  {
    if (len < buffersize)
    {
      buffer[len] = '\\';
    }
    len += 1;
  }
  while (0);
  *len_ref = len;
  *pending_shell_escape_end_ref = pending_shell_escape_end;
  *escaping_ref = escaping;
}


/*** DEPENDENCIES:
enum quoting_style
{
  literal_quoting_style,
  shell_quoting_style,
  shell_always_quoting_style,
  shell_escape_quoting_style,
  shell_escape_always_quoting_style,
  c_quoting_style,
  c_maybe_quoting_style,
  escape_quoting_style,
  locale_quoting_style,
  clocale_quoting_style,
  custom_quoting_style
}
----------------------------
***/


// hint:  ['len_ref is a mutable refrence to size_t', 'pending_shell_escape_end_ref is a mutable refrence to bool', 'c_ref is a mutable refrence to unsigned char', 'escaping_ref is a mutable refrence to bool']
void helper_helper_helper_quotearg_buffer_restyled_2_5_1(size_t * const len_ref, bool * const pending_shell_escape_end_ref, unsigned char * const c_ref, bool * const escaping_ref, char * const buffer, const char * const arg, enum quoting_style quoting_style, bool elide_outer_quotes, size_t buffersize, size_t argsize, size_t i)
{
  size_t len = *len_ref;
  bool pending_shell_escape_end = *pending_shell_escape_end_ref;
  unsigned char c = *c_ref;
  bool escaping = *escaping_ref;
  do
  {
    helper_helper_helper_helper_quotearg_buffer_restyled_2_5_1_1(&len, &pending_shell_escape_end, &escaping, buffer, quoting_style, elide_outer_quotes, buffersize);
  }
  while (0);
  if ((((quoting_style != shell_always_quoting_style) && ((i + 1) < argsize)) && ('0' <= arg[i + 1])) && (arg[i + 1] <= '9'))
  {
    do
    {
      if (len < buffersize)
      {
        buffer[len] = '0';
      }
      len += 1;
    }
    while (0);
    do
    {
      if (len < buffersize)
      {
        buffer[len] = '0';
      }
      len += 1;
    }
    while (0);
  }
  c = '0';
  *len_ref = len;
  *pending_shell_escape_end_ref = pending_shell_escape_end;
  *c_ref = c;
  *escaping_ref = escaping;
}


/*** DEPENDENCIES:
void helper_helper_helper_helper_quotearg_buffer_restyled_2_5_1_1(size_t * const len_ref, bool * const pending_shell_escape_end_ref, bool * const escaping_ref, char * const buffer, enum quoting_style quoting_style, bool elide_outer_quotes, size_t buffersize)
{
  size_t len = *len_ref;
  bool pending_shell_escape_end = *pending_shell_escape_end_ref;
  bool escaping = *escaping_ref;
  if (elide_outer_quotes)
  {
    goto force_outer_quoting_style;
  }
  escaping = 1;
  if ((quoting_style == shell_always_quoting_style) && (!pending_shell_escape_end))
  {
    do
    {
      if (len < buffersize)
      {
        buffer[len] = '\'';
      }
      len += 1;
    }
    while (0);
    do
    {
      if (len < buffersize)
      {
        buffer[len] = '$';
      }
      len += 1;
    }
    while (0);
    do
    {
      if (len < buffersize)
      {
        buffer[len] = '\'';
      }
      len += 1;
    }
    while (0);
    pending_shell_escape_end = 1;
  }
  do
  {
    if (len < buffersize)
    {
      buffer[len] = '\\';
    }
    len += 1;
  }
  while (0);
  *len_ref = len;
  *pending_shell_escape_end_ref = pending_shell_escape_end;
  *escaping_ref = escaping;
}


----------------------------
enum quoting_style
{
  literal_quoting_style,
  shell_quoting_style,
  shell_always_quoting_style,
  shell_escape_quoting_style,
  shell_escape_always_quoting_style,
  c_quoting_style,
  c_maybe_quoting_style,
  escape_quoting_style,
  locale_quoting_style,
  clocale_quoting_style,
  custom_quoting_style
}
----------------------------
***/


// hint:  ['len_ref is a mutable refrence to size_t', 'pending_shell_escape_end_ref is a mutable refrence to bool', 'c_ref is a mutable refrence to unsigned char', 'escaping_ref is a mutable refrence to bool']
void helper_helper_quotearg_buffer_restyled_2_5(size_t * const len_ref, bool * const pending_shell_escape_end_ref, unsigned char * const c_ref, bool * const escaping_ref, char * const buffer, const char * const arg, enum quoting_style quoting_style, int flags, bool backslash_escapes, bool elide_outer_quotes, size_t buffersize, size_t argsize, size_t i)
{
  size_t len = *len_ref;
  bool pending_shell_escape_end = *pending_shell_escape_end_ref;
  unsigned char c = *c_ref;
  bool escaping = *escaping_ref;
  if (backslash_escapes)
  {
    helper_helper_helper_quotearg_buffer_restyled_2_5_1(&len, &pending_shell_escape_end, &c, &escaping, buffer, arg, quoting_style, elide_outer_quotes, buffersize, argsize, i);
  }
  else
    if (flags & QA_ELIDE_NULL_BYTES)
  {
    continue;
  }
  break;
  *len_ref = len;
  *pending_shell_escape_end_ref = pending_shell_escape_end;
  *c_ref = c;
  *escaping_ref = escaping;
}


/*** DEPENDENCIES:
void helper_helper_helper_quotearg_buffer_restyled_2_5_1(size_t * const len_ref, bool * const pending_shell_escape_end_ref, unsigned char * const c_ref, bool * const escaping_ref, char * const buffer, const char * const arg, enum quoting_style quoting_style, bool elide_outer_quotes, size_t buffersize, size_t argsize, size_t i)
{
  size_t len = *len_ref;
  bool pending_shell_escape_end = *pending_shell_escape_end_ref;
  unsigned char c = *c_ref;
  bool escaping = *escaping_ref;
  do
  {
    helper_helper_helper_helper_quotearg_buffer_restyled_2_5_1_1(&len, &pending_shell_escape_end, &escaping, buffer, quoting_style, elide_outer_quotes, buffersize);
  }
  while (0);
  if ((((quoting_style != shell_always_quoting_style) && ((i + 1) < argsize)) && ('0' <= arg[i + 1])) && (arg[i + 1] <= '9'))
  {
    do
    {
      if (len < buffersize)
      {
        buffer[len] = '0';
      }
      len += 1;
    }
    while (0);
    do
    {
      if (len < buffersize)
      {
        buffer[len] = '0';
      }
      len += 1;
    }
    while (0);
  }
  c = '0';
  *len_ref = len;
  *pending_shell_escape_end_ref = pending_shell_escape_end;
  *c_ref = c;
  *escaping_ref = escaping;
}


----------------------------
enum quoting_style
{
  literal_quoting_style,
  shell_quoting_style,
  shell_always_quoting_style,
  shell_escape_quoting_style,
  shell_escape_always_quoting_style,
  c_quoting_style,
  c_maybe_quoting_style,
  escape_quoting_style,
  locale_quoting_style,
  clocale_quoting_style,
  custom_quoting_style
}
----------------------------
***/


// hint:  ['buffersize_ref is a mutable refrence to size_t', 'argsize_ref is a mutable refrence to size_t', 'i_ref is a mutable refrence to size_t', 'len_ref is a mutable refrence to size_t', 'orig_buffersize_ref is a mutable refrence to size_t', 'encountered_single_quote_ref is a mutable refrence to bool', 'all_c_and_shell_quote_compat_ref is a mutable refrence to bool', 'pending_shell_escape_end_ref is a mutable refrence to bool']
void helper_quotearg_buffer_restyled_2(size_t * const buffersize_ref, size_t * const argsize_ref, size_t * const i_ref, size_t * const len_ref, size_t * const orig_buffersize_ref, bool * const encountered_single_quote_ref, bool * const all_c_and_shell_quote_compat_ref, bool * const pending_shell_escape_end_ref, char * const buffer, const char * const arg, enum quoting_style quoting_style, int flags, const unsigned int * const quote_these_too, const char * const quote_string, size_t quote_string_len, bool backslash_escapes, bool unibyte_locale, bool elide_outer_quotes)
{
  size_t buffersize = *buffersize_ref;
  size_t argsize = *argsize_ref;
  size_t i = *i_ref;
  size_t len = *len_ref;
  size_t orig_buffersize = *orig_buffersize_ref;
  bool encountered_single_quote = *encountered_single_quote_ref;
  bool all_c_and_shell_quote_compat = *all_c_and_shell_quote_compat_ref;
  bool pending_shell_escape_end = *pending_shell_escape_end_ref;
  unsigned char c;
  unsigned char esc;
  bool is_right_quote = 0;
  bool escaping = 0;
  bool c_and_shell_quote_compat = 0;
  if ((((backslash_escapes && (quoting_style != shell_always_quoting_style)) && quote_string_len) && ((i + quote_string_len) <= (((argsize == ((size_t) (-1))) && (1 < quote_string_len)) ? (argsize = strlen(arg)) : (argsize)))) && (memcmp(arg + i, quote_string, quote_string_len) == 0))
  {
    if (elide_outer_quotes)
    {
      goto force_outer_quoting_style;
    }
    is_right_quote = 1;
  }
  c = arg[i];
  switch (c)
  {
    case '\0':
    {
      helper_helper_quotearg_buffer_restyled_2_5(&len, &pending_shell_escape_end, &c, &escaping, buffer, arg, quoting_style, flags, backslash_escapes, elide_outer_quotes, buffersize, argsize, i);
    }

    case '?':
    {
      helper_helper_quotearg_buffer_restyled_2_4(&i, &len, &c, buffer, arg, quoting_style, flags, elide_outer_quotes, buffersize, argsize);
    }

    case '\a':
    {
      esc = 'a';
      goto c_escape;
    }

    case '\b':
    {
      esc = 'b';
      goto c_escape;
    }

    case '\f':
    {
      esc = 'f';
      goto c_escape;
    }

    case '\n':
    {
      esc = 'n';
      goto c_and_shell_escape;
    }

    case '\r':
    {
      esc = 'r';
      goto c_and_shell_escape;
    }

    case '\t':
    {
      esc = 't';
      goto c_and_shell_escape;
    }

    case '\v':
    {
      esc = 'v';
      goto c_escape;
    }

    case '\\':
    {
      helper_helper_quotearg_buffer_restyled_2_1(&c, &esc, quoting_style, quote_string_len, backslash_escapes, elide_outer_quotes);
    }

    case '{':

    case '}':
    {
      if (!((argsize == ((size_t) (-1))) ? (arg[1] == '\0') : (argsize == 1)))
      {
        break;
      }
      ;
    }

    case '#':

    case '~':
    {
      if (i != 0)
      {
        break;
      }
      ;
    }

    case ' ':
    {
      c_and_shell_quote_compat = 1;
      ;
    }

    case '!':

    case '"':

    case '$':

    case '&':

    case '(':

    case ')':

    case '*':

    case ';':

    case '<':

    case '=':

    case '>':

    case '[':

    case '^':

    case '`':

    case '|':
    {
      if ((quoting_style == shell_always_quoting_style) && elide_outer_quotes)
      {
        goto force_outer_quoting_style;
      }
      break;
    }

    case '\'':
    {
      helper_helper_quotearg_buffer_restyled_2_3(&buffersize, &len, &orig_buffersize, &encountered_single_quote, &pending_shell_escape_end, &c_and_shell_quote_compat, buffer, quoting_style, elide_outer_quotes);
    }

    case '%':

    case '+':

    case ',':

    case '-':

    case '.':

    case '/':

    case '0':

    case '1':

    case '2':

    case '3':

    case '4':

    case '5':

    case '6':

    case '7':

    case '8':

    case '9':

    case ':':

    case 'A':

    case 'B':

    case 'C':

    case 'D':

    case 'E':

    case 'F':

    case 'G':

    case 'H':

    case 'I':

    case 'J':

    case 'K':

    case 'L':

    case 'M':

    case 'N':

    case 'O':

    case 'P':

    case 'Q':

    case 'R':

    case 'S':

    case 'T':

    case 'U':

    case 'V':

    case 'W':

    case 'X':

    case 'Y':

    case 'Z':

    case ']':

    case '_':

    case 'a':

    case 'b':

    case 'c':

    case 'd':

    case 'e':

    case 'f':

    case 'g':

    case 'h':

    case 'i':

    case 'j':

    case 'k':

    case 'l':

    case 'm':

    case 'n':

    case 'o':

    case 'p':

    case 'q':

    case 'r':

    case 's':

    case 't':

    case 'u':

    case 'v':

    case 'w':

    case 'x':

    case 'y':

    case 'z':
    {
      c_and_shell_quote_compat = 1;
      break;
    }

    default:
    {
      helper_helper_quotearg_buffer_restyled_2_6(&argsize, &i, &len, &pending_shell_escape_end, &c, &is_right_quote, &escaping, &c_and_shell_quote_compat, buffer, arg, quoting_style, backslash_escapes, unibyte_locale, elide_outer_quotes, buffersize);
    }

  }

  if ((!((((backslash_escapes && (quoting_style != shell_always_quoting_style)) || elide_outer_quotes) && quote_these_too) && ((quote_these_too[c / ((sizeof(int)) * 8)] >> (c % ((sizeof(int)) * 8))) & 1))) && (!is_right_quote))
  {
    goto store_c;
  }
  store_escape:
  do
  {
    helper_helper_quotearg_buffer_restyled_2_2(&len, &pending_shell_escape_end, &escaping, buffer, quoting_style, elide_outer_quotes, buffersize);
  }
  while (0);

  store_c:
  do
  {
    if (pending_shell_escape_end && (!escaping))
    {
      do
      {
        if (len < buffersize)
        {
          buffer[len] = '\'';
        }
        len += 1;
      }
      while (0);
      do
      {
        if (len < buffersize)
        {
          buffer[len] = '\'';
        }
        len += 1;
      }
      while (0);
      pending_shell_escape_end = 0;
    }
  }
  while (0);

  do
  {
    if (len < buffersize)
    {
      buffer[len] = c;
    }
    len += 1;
  }
  while (0);
  if (!c_and_shell_quote_compat)
  {
    all_c_and_shell_quote_compat = 0;
  }
  *buffersize_ref = buffersize;
  *argsize_ref = argsize;
  *i_ref = i;
  *len_ref = len;
  *orig_buffersize_ref = orig_buffersize;
  *encountered_single_quote_ref = encountered_single_quote;
  *all_c_and_shell_quote_compat_ref = all_c_and_shell_quote_compat;
  *pending_shell_escape_end_ref = pending_shell_escape_end;
}


/*** DEPENDENCIES:
void helper_helper_quotearg_buffer_restyled_2_2(size_t * const len_ref, bool * const pending_shell_escape_end_ref, bool * const escaping_ref, char * const buffer, enum quoting_style quoting_style, bool elide_outer_quotes, size_t buffersize)
{
  size_t len = *len_ref;
  bool pending_shell_escape_end = *pending_shell_escape_end_ref;
  bool escaping = *escaping_ref;
  if (elide_outer_quotes)
  {
    goto force_outer_quoting_style;
  }
  escaping = 1;
  if ((quoting_style == shell_always_quoting_style) && (!pending_shell_escape_end))
  {
    do
    {
      if (len < buffersize)
      {
        buffer[len] = '\'';
      }
      len += 1;
    }
    while (0);
    do
    {
      if (len < buffersize)
      {
        buffer[len] = '$';
      }
      len += 1;
    }
    while (0);
    do
    {
      if (len < buffersize)
      {
        buffer[len] = '\'';
      }
      len += 1;
    }
    while (0);
    pending_shell_escape_end = 1;
  }
  do
  {
    if (len < buffersize)
    {
      buffer[len] = '\\';
    }
    len += 1;
  }
  while (0);
  *len_ref = len;
  *pending_shell_escape_end_ref = pending_shell_escape_end;
  *escaping_ref = escaping;
}


----------------------------
void helper_helper_quotearg_buffer_restyled_2_6(size_t * const argsize_ref, size_t * const i_ref, size_t * const len_ref, bool * const pending_shell_escape_end_ref, unsigned char * const c_ref, bool * const is_right_quote_ref, bool * const escaping_ref, bool * const c_and_shell_quote_compat_ref, char * const buffer, const char * const arg, enum quoting_style quoting_style, bool backslash_escapes, bool unibyte_locale, bool elide_outer_quotes, size_t buffersize)
{
  size_t argsize = *argsize_ref;
  size_t i = *i_ref;
  size_t len = *len_ref;
  bool pending_shell_escape_end = *pending_shell_escape_end_ref;
  unsigned char c = *c_ref;
  bool is_right_quote = *is_right_quote_ref;
  bool escaping = *escaping_ref;
  bool c_and_shell_quote_compat = *c_and_shell_quote_compat_ref;
  size_t m;
  bool printable;
  if (unibyte_locale)
  {
    m = 1;
    printable = isprint(c) != 0;
  }
  else
  {
    helper_helper_helper_quotearg_buffer_restyled_2_6_1(&argsize, &m, &printable, arg, quoting_style, elide_outer_quotes, i);
  }
  c_and_shell_quote_compat = printable;
  if ((1 < m) || (backslash_escapes && (!printable)))
  {
    helper_helper_helper_quotearg_buffer_restyled_2_6_2(&i, &len, &pending_shell_escape_end, &c, &is_right_quote, &escaping, buffer, arg, quoting_style, backslash_escapes, elide_outer_quotes, buffersize, m, printable);
  }
  *argsize_ref = argsize;
  *i_ref = i;
  *len_ref = len;
  *pending_shell_escape_end_ref = pending_shell_escape_end;
  *c_ref = c;
  *is_right_quote_ref = is_right_quote;
  *escaping_ref = escaping;
  *c_and_shell_quote_compat_ref = c_and_shell_quote_compat;
}


----------------------------
void helper_helper_quotearg_buffer_restyled_2_1(unsigned char * const c_ref, unsigned char * const esc_ref, enum quoting_style quoting_style, size_t quote_string_len, bool backslash_escapes, bool elide_outer_quotes)
{
  unsigned char c = *c_ref;
  unsigned char esc = *esc_ref;
  esc = c;
  if (quoting_style == shell_always_quoting_style)
  {
    if (elide_outer_quotes)
    {
      goto force_outer_quoting_style;
    }
    goto store_c;
  }
  if ((backslash_escapes && elide_outer_quotes) && quote_string_len)
  {
    goto store_c;
  }
  c_and_shell_escape:
  if ((quoting_style == shell_always_quoting_style) && elide_outer_quotes)
  {
    goto force_outer_quoting_style;
  }

  c_escape:
  if (backslash_escapes)
  {
    c = esc;
    goto store_escape;
  }

  break;
  *c_ref = c;
  *esc_ref = esc;
}


----------------------------
enum quoting_style
{
  literal_quoting_style,
  shell_quoting_style,
  shell_always_quoting_style,
  shell_escape_quoting_style,
  shell_escape_always_quoting_style,
  c_quoting_style,
  c_maybe_quoting_style,
  escape_quoting_style,
  locale_quoting_style,
  clocale_quoting_style,
  custom_quoting_style
}
----------------------------
void helper_helper_quotearg_buffer_restyled_2_3(size_t * const buffersize_ref, size_t * const len_ref, size_t * const orig_buffersize_ref, bool * const encountered_single_quote_ref, bool * const pending_shell_escape_end_ref, bool * const c_and_shell_quote_compat_ref, char * const buffer, enum quoting_style quoting_style, bool elide_outer_quotes)
{
  size_t buffersize = *buffersize_ref;
  size_t len = *len_ref;
  size_t orig_buffersize = *orig_buffersize_ref;
  bool encountered_single_quote = *encountered_single_quote_ref;
  bool pending_shell_escape_end = *pending_shell_escape_end_ref;
  bool c_and_shell_quote_compat = *c_and_shell_quote_compat_ref;
  encountered_single_quote = 1;
  c_and_shell_quote_compat = 1;
  if (quoting_style == shell_always_quoting_style)
  {
    helper_helper_helper_quotearg_buffer_restyled_2_3_1(&buffersize, &len, &orig_buffersize, &pending_shell_escape_end, buffer, elide_outer_quotes);
  }
  break;
  *buffersize_ref = buffersize;
  *len_ref = len;
  *orig_buffersize_ref = orig_buffersize;
  *encountered_single_quote_ref = encountered_single_quote;
  *pending_shell_escape_end_ref = pending_shell_escape_end;
  *c_and_shell_quote_compat_ref = c_and_shell_quote_compat;
}


----------------------------
void helper_helper_quotearg_buffer_restyled_2_4(size_t * const i_ref, size_t * const len_ref, unsigned char * const c_ref, char * const buffer, const char * const arg, enum quoting_style quoting_style, int flags, bool elide_outer_quotes, size_t buffersize, size_t argsize)
{
  size_t i = *i_ref;
  size_t len = *len_ref;
  unsigned char c = *c_ref;
  switch (quoting_style)
  {
    case shell_always_quoting_style:
    {
      if (elide_outer_quotes)
      {
        goto force_outer_quoting_style;
      }
      break;
    }

    case c_quoting_style:
    {
      helper_helper_helper_quotearg_buffer_restyled_2_4_1(&i, &len, &c, buffer, arg, flags, elide_outer_quotes, buffersize, argsize);
    }

    default:
    {
      break;
    }

  }

  break;
  *i_ref = i;
  *len_ref = len;
  *c_ref = c;
}


----------------------------
void helper_helper_quotearg_buffer_restyled_2_5(size_t * const len_ref, bool * const pending_shell_escape_end_ref, unsigned char * const c_ref, bool * const escaping_ref, char * const buffer, const char * const arg, enum quoting_style quoting_style, int flags, bool backslash_escapes, bool elide_outer_quotes, size_t buffersize, size_t argsize, size_t i)
{
  size_t len = *len_ref;
  bool pending_shell_escape_end = *pending_shell_escape_end_ref;
  unsigned char c = *c_ref;
  bool escaping = *escaping_ref;
  if (backslash_escapes)
  {
    helper_helper_helper_quotearg_buffer_restyled_2_5_1(&len, &pending_shell_escape_end, &c, &escaping, buffer, arg, quoting_style, elide_outer_quotes, buffersize, argsize, i);
  }
  else
    if (flags & QA_ELIDE_NULL_BYTES)
  {
    continue;
  }
  break;
  *len_ref = len;
  *pending_shell_escape_end_ref = pending_shell_escape_end;
  *c_ref = c;
  *escaping_ref = escaping;
}


----------------------------
***/


static size_t quotearg_buffer_restyled(char *buffer, size_t buffersize, const char *arg, size_t argsize, enum quoting_style quoting_style, int flags, const unsigned int *quote_these_too, const char *left_quote, const char *right_quote)
{
  unsigned int right_quote_idx = 0;
  unsigned int left_quote_idx = 0;
  size_t i;
  size_t len = 0;
  size_t orig_buffersize = 0;
  const char *quote_string = 0;
  unsigned int quote_string_idx = 0;
  size_t quote_string_len = 0;
  bool backslash_escapes = 0;
  bool unibyte_locale = MB_CUR_MAX == 1;
  bool elide_outer_quotes = (flags & QA_ELIDE_OUTER_QUOTES) != 0;
  bool encountered_single_quote = 0;
  bool all_c_and_shell_quote_compat = 1;
  process_input:
  ;

  bool pending_shell_escape_end = 0;
  switch (quoting_style)
  {
    case c_maybe_quoting_style:
    {
      quoting_style = c_quoting_style;
      elide_outer_quotes = 1;
      ;
    }

    case c_quoting_style:
    {
      if (!elide_outer_quotes)
      {
        do
        {
          if (len < buffersize)
          {
            buffer[len] = '"';
          }
          len += 1;
        }
        while (0);
      }
      backslash_escapes = 1;
      quote_string_idx = "\"";
      quote_string_len = 1;
      break;
    }

    case escape_quoting_style:
    {
      backslash_escapes = 1;
      elide_outer_quotes = 0;
      break;
    }

    case locale_quoting_style:

    case clocale_quoting_style:

    case custom_quoting_style:
    {
      helper_quotearg_buffer_restyled_1(&right_quote_idx, &left_quote_idx, &len, &quote_string_idx, &quote_string_len, &backslash_escapes, buffer, buffersize, quoting_style, left_quote, right_quote, quote_string, elide_outer_quotes);
    }

    case shell_escape_quoting_style:
    {
      backslash_escapes = 1;
      ;
    }

    case shell_quoting_style:
    {
      elide_outer_quotes = 1;
      ;
    }

    case shell_escape_always_quoting_style:
    {
      if (!elide_outer_quotes)
      {
        backslash_escapes = 1;
      }
      ;
    }

    case shell_always_quoting_style:
    {
      quoting_style = shell_always_quoting_style;
      if (!elide_outer_quotes)
      {
        do
        {
          if (len < buffersize)
          {
            buffer[len] = '\'';
          }
          len += 1;
        }
        while (0);
      }
      quote_string_idx = "'";
      quote_string_len = 1;
      break;
    }

    case literal_quoting_style:
    {
      elide_outer_quotes = 0;
      break;
    }

    default:
    {
      abort();
    }

  }

  for (i = 0; !((argsize == ((size_t) (-1))) ? (arg[i] == '\0') : (i == argsize)); i += 1)
  {
    helper_quotearg_buffer_restyled_2(&buffersize, &argsize, &i, &len, &orig_buffersize, &encountered_single_quote, &all_c_and_shell_quote_compat, &pending_shell_escape_end, buffer, arg, quoting_style, flags, quote_these_too, quote_string, quote_string_len, backslash_escapes, unibyte_locale, elide_outer_quotes);
  }

  if (((len == 0) && (quoting_style == shell_always_quoting_style)) && elide_outer_quotes)
  {
    goto force_outer_quoting_style;
  }
  if (((quoting_style == shell_always_quoting_style) && (!elide_outer_quotes)) && encountered_single_quote)
  {
    if (all_c_and_shell_quote_compat)
    {
      return quotearg_buffer_restyled(buffer, orig_buffersize, arg, argsize, c_quoting_style, flags, quote_these_too, left_quote, right_quote);
    }
    else
      if ((!buffersize) && orig_buffersize)
    {
      buffersize = orig_buffersize;
      len = 0;
      goto process_input;
    }
  }
  if ((&quote_string[quote_string_idx]) && (!elide_outer_quotes))
  {
    for (; quote_string[quote_string_idx]; quote_string_idx += 1)
    {
      do
      {
        if (len < buffersize)
        {
          buffer[len] = quote_string[quote_string_idx];
        }
        len += 1;
      }
      while (0);
    }

  }
  if (len < buffersize)
  {
    buffer[len] = '\0';
  }
  return len;
  force_outer_quoting_style:
  if ((quoting_style == shell_always_quoting_style) && backslash_escapes)
  {
    quoting_style = shell_escape_always_quoting_style;
  }

  return quotearg_buffer_restyled(buffer, buffersize, arg, argsize, quoting_style, flags & (~QA_ELIDE_OUTER_QUOTES), 0, left_quote, right_quote);
}


/*** DEPENDENCIES:
void helper_quotearg_buffer_restyled_1(unsigned int * const right_quote_idx_ref, unsigned int * const left_quote_idx_ref, size_t * const len_ref, unsigned int * const quote_string_idx_ref, size_t * const quote_string_len_ref, bool * const backslash_escapes_ref, char * const buffer, size_t buffersize, enum quoting_style quoting_style, const char * const left_quote, const char * const right_quote, const char * const quote_string, bool elide_outer_quotes)
{
  unsigned int right_quote_idx = *right_quote_idx_ref;
  unsigned int left_quote_idx = *left_quote_idx_ref;
  size_t len = *len_ref;
  unsigned int quote_string_idx = *quote_string_idx_ref;
  size_t quote_string_len = *quote_string_len_ref;
  bool backslash_escapes = *backslash_escapes_ref;
  {
    if (quoting_style != custom_quoting_style)
    {
      left_quote_idx = gettext_quote("`", quoting_style);
      right_quote_idx = gettext_quote("'", quoting_style);
    }
    if (!elide_outer_quotes)
    {
      for (quote_string_idx = &left_quote[left_quote_idx]; quote_string[quote_string_idx]; quote_string_idx += 1)
      {
        do
        {
          if (len < buffersize)
          {
            buffer[len] = quote_string[quote_string_idx];
          }
          len += 1;
        }
        while (0);
      }

    }
    backslash_escapes = 1;
    quote_string_idx = &right_quote[right_quote_idx];
    quote_string_len = strlen(quote_string);
  }
  break;
  *right_quote_idx_ref = right_quote_idx;
  *left_quote_idx_ref = left_quote_idx;
  *len_ref = len;
  *quote_string_idx_ref = quote_string_idx;
  *quote_string_len_ref = quote_string_len;
  *backslash_escapes_ref = backslash_escapes;
}


----------------------------
void helper_quotearg_buffer_restyled_2(size_t * const buffersize_ref, size_t * const argsize_ref, size_t * const i_ref, size_t * const len_ref, size_t * const orig_buffersize_ref, bool * const encountered_single_quote_ref, bool * const all_c_and_shell_quote_compat_ref, bool * const pending_shell_escape_end_ref, char * const buffer, const char * const arg, enum quoting_style quoting_style, int flags, const unsigned int * const quote_these_too, const char * const quote_string, size_t quote_string_len, bool backslash_escapes, bool unibyte_locale, bool elide_outer_quotes)
{
  size_t buffersize = *buffersize_ref;
  size_t argsize = *argsize_ref;
  size_t i = *i_ref;
  size_t len = *len_ref;
  size_t orig_buffersize = *orig_buffersize_ref;
  bool encountered_single_quote = *encountered_single_quote_ref;
  bool all_c_and_shell_quote_compat = *all_c_and_shell_quote_compat_ref;
  bool pending_shell_escape_end = *pending_shell_escape_end_ref;
  unsigned char c;
  unsigned char esc;
  bool is_right_quote = 0;
  bool escaping = 0;
  bool c_and_shell_quote_compat = 0;
  if ((((backslash_escapes && (quoting_style != shell_always_quoting_style)) && quote_string_len) && ((i + quote_string_len) <= (((argsize == ((size_t) (-1))) && (1 < quote_string_len)) ? (argsize = strlen(arg)) : (argsize)))) && (memcmp(arg + i, quote_string, quote_string_len) == 0))
  {
    if (elide_outer_quotes)
    {
      goto force_outer_quoting_style;
    }
    is_right_quote = 1;
  }
  c = arg[i];
  switch (c)
  {
    case '\0':
    {
      helper_helper_quotearg_buffer_restyled_2_5(&len, &pending_shell_escape_end, &c, &escaping, buffer, arg, quoting_style, flags, backslash_escapes, elide_outer_quotes, buffersize, argsize, i);
    }

    case '?':
    {
      helper_helper_quotearg_buffer_restyled_2_4(&i, &len, &c, buffer, arg, quoting_style, flags, elide_outer_quotes, buffersize, argsize);
    }

    case '\a':
    {
      esc = 'a';
      goto c_escape;
    }

    case '\b':
    {
      esc = 'b';
      goto c_escape;
    }

    case '\f':
    {
      esc = 'f';
      goto c_escape;
    }

    case '\n':
    {
      esc = 'n';
      goto c_and_shell_escape;
    }

    case '\r':
    {
      esc = 'r';
      goto c_and_shell_escape;
    }

    case '\t':
    {
      esc = 't';
      goto c_and_shell_escape;
    }

    case '\v':
    {
      esc = 'v';
      goto c_escape;
    }

    case '\\':
    {
      helper_helper_quotearg_buffer_restyled_2_1(&c, &esc, quoting_style, quote_string_len, backslash_escapes, elide_outer_quotes);
    }

    case '{':

    case '}':
    {
      if (!((argsize == ((size_t) (-1))) ? (arg[1] == '\0') : (argsize == 1)))
      {
        break;
      }
      ;
    }

    case '#':

    case '~':
    {
      if (i != 0)
      {
        break;
      }
      ;
    }

    case ' ':
    {
      c_and_shell_quote_compat = 1;
      ;
    }

    case '!':

    case '"':

    case '$':

    case '&':

    case '(':

    case ')':

    case '*':

    case ';':

    case '<':

    case '=':

    case '>':

    case '[':

    case '^':

    case '`':

    case '|':
    {
      if ((quoting_style == shell_always_quoting_style) && elide_outer_quotes)
      {
        goto force_outer_quoting_style;
      }
      break;
    }

    case '\'':
    {
      helper_helper_quotearg_buffer_restyled_2_3(&buffersize, &len, &orig_buffersize, &encountered_single_quote, &pending_shell_escape_end, &c_and_shell_quote_compat, buffer, quoting_style, elide_outer_quotes);
    }

    case '%':

    case '+':

    case ',':

    case '-':

    case '.':

    case '/':

    case '0':

    case '1':

    case '2':

    case '3':

    case '4':

    case '5':

    case '6':

    case '7':

    case '8':

    case '9':

    case ':':

    case 'A':

    case 'B':

    case 'C':

    case 'D':

    case 'E':

    case 'F':

    case 'G':

    case 'H':

    case 'I':

    case 'J':

    case 'K':

    case 'L':

    case 'M':

    case 'N':

    case 'O':

    case 'P':

    case 'Q':

    case 'R':

    case 'S':

    case 'T':

    case 'U':

    case 'V':

    case 'W':

    case 'X':

    case 'Y':

    case 'Z':

    case ']':

    case '_':

    case 'a':

    case 'b':

    case 'c':

    case 'd':

    case 'e':

    case 'f':

    case 'g':

    case 'h':

    case 'i':

    case 'j':

    case 'k':

    case 'l':

    case 'm':

    case 'n':

    case 'o':

    case 'p':

    case 'q':

    case 'r':

    case 's':

    case 't':

    case 'u':

    case 'v':

    case 'w':

    case 'x':

    case 'y':

    case 'z':
    {
      c_and_shell_quote_compat = 1;
      break;
    }

    default:
    {
      helper_helper_quotearg_buffer_restyled_2_6(&argsize, &i, &len, &pending_shell_escape_end, &c, &is_right_quote, &escaping, &c_and_shell_quote_compat, buffer, arg, quoting_style, backslash_escapes, unibyte_locale, elide_outer_quotes, buffersize);
    }

  }

  if ((!((((backslash_escapes && (quoting_style != shell_always_quoting_style)) || elide_outer_quotes) && quote_these_too) && ((quote_these_too[c / ((sizeof(int)) * 8)] >> (c % ((sizeof(int)) * 8))) & 1))) && (!is_right_quote))
  {
    goto store_c;
  }
  store_escape:
  do
  {
    helper_helper_quotearg_buffer_restyled_2_2(&len, &pending_shell_escape_end, &escaping, buffer, quoting_style, elide_outer_quotes, buffersize);
  }
  while (0);

  store_c:
  do
  {
    if (pending_shell_escape_end && (!escaping))
    {
      do
      {
        if (len < buffersize)
        {
          buffer[len] = '\'';
        }
        len += 1;
      }
      while (0);
      do
      {
        if (len < buffersize)
        {
          buffer[len] = '\'';
        }
        len += 1;
      }
      while (0);
      pending_shell_escape_end = 0;
    }
  }
  while (0);

  do
  {
    if (len < buffersize)
    {
      buffer[len] = c;
    }
    len += 1;
  }
  while (0);
  if (!c_and_shell_quote_compat)
  {
    all_c_and_shell_quote_compat = 0;
  }
  *buffersize_ref = buffersize;
  *argsize_ref = argsize;
  *i_ref = i;
  *len_ref = len;
  *orig_buffersize_ref = orig_buffersize;
  *encountered_single_quote_ref = encountered_single_quote;
  *all_c_and_shell_quote_compat_ref = all_c_and_shell_quote_compat;
  *pending_shell_escape_end_ref = pending_shell_escape_end;
}


----------------------------
enum quoting_style
{
  literal_quoting_style,
  shell_quoting_style,
  shell_always_quoting_style,
  shell_escape_quoting_style,
  shell_escape_always_quoting_style,
  c_quoting_style,
  c_maybe_quoting_style,
  escape_quoting_style,
  locale_quoting_style,
  clocale_quoting_style,
  custom_quoting_style
}
----------------------------
***/


static char *quotearg_n_options(int n, const char *arg, size_t argsize, const struct quoting_options *options)
{
  int e = errno;
  struct slotvec *sv = slotvec;
  int nslots_max = (2147483647 < PTRDIFF_MAX) ? (2147483647) : (PTRDIFF_MAX);
  if (!((0 <= n) && (n < nslots_max)))
  {
    abort();
  }
  if (nslots <= n)
  {
    bool preallocated = sv == (&slotvec0);
    idx_t new_nslots = nslots;
    slotvec = (sv = xpalloc((preallocated) ? (0) : (sv), &new_nslots, (n - nslots) + 1, nslots_max, sizeof(*sv)));
    if (preallocated)
    {
      *sv = slotvec0;
    }
    memset(sv + nslots, 0, (new_nslots - nslots) * (sizeof(*sv)));
    nslots = new_nslots;
  }
  {
    size_t size = sv[n].size;
    char *val = sv[n].val;
    int flags = options->flags | QA_ELIDE_NULL_BYTES;
    size_t qsize = quotearg_buffer_restyled(val, size, arg, argsize, options->style, flags, options->quote_these_too, options->left_quote, options->right_quote);
    if (size <= qsize)
    {
      sv[n].size = (size = qsize + 1);
      if (val != slot0)
      {
        free(val);
      }
      sv[n].val = (val = xcharalloc(size));
      quotearg_buffer_restyled(val, size, arg, argsize, options->style, flags, options->quote_these_too, options->left_quote, options->right_quote);
    }
    errno = e;
    return val;
  }
}


/*** DEPENDENCIES:
static char slot0[256]
----------------------------
struct slotvec
{
  size_t size;
  char *val;
}
----------------------------
char *xcharalloc(size_t n)
{
  return (char *) (((sizeof(char)) == 1) ? (xmalloc(n)) : (xnmalloc(n, sizeof(char))));
}


----------------------------
static int nslots = 1
----------------------------
void *xpalloc(void *pa, idx_t *pn, idx_t n_incr_min, ptrdiff_t n_max, idx_t s)
{
  unsigned int pa_idx = 0;
  idx_t n0 = *pn;
  enum 
  {
    DEFAULT_MXFAST = (64 * (sizeof(size_t))) / 4
  };
  idx_t n;
  if ((bool) __builtin_add_overflow(n0, n0 >> 1, &n))
  {
    n = PTRDIFF_MAX;
  }
  if ((0 <= n_max) && (n_max < n))
  {
    n = n_max;
  }
  idx_t nbytes;
  idx_t adjusted_nbytes = ((bool) __builtin_mul_overflow(n, s, &nbytes)) ? ((PTRDIFF_MAX < SIZE_MAX) ? (PTRDIFF_MAX) : (SIZE_MAX)) : ((nbytes < DEFAULT_MXFAST) ? (DEFAULT_MXFAST) : (0));
  if (adjusted_nbytes)
  {
    n = adjusted_nbytes / s;
    nbytes = adjusted_nbytes - (adjusted_nbytes % s);
  }
  if (!(&pa[pa_idx]))
  {
    *pn = 0;
  }
  if (((n - n0) < n_incr_min) && ((((bool) __builtin_add_overflow(n0, n_incr_min, &n)) || ((0 <= n_max) && (n_max < n))) || ((bool) __builtin_mul_overflow(n, s, &nbytes))))
  {
    xalloc_die();
  }
  pa_idx = xrealloc(pa_idx, nbytes);
  *pn = n;
  return pa;
}


----------------------------
typedef ptrdiff_t idx_t
----------------------------
static struct slotvec slotvec0 = {sizeof(slot0), slot0}
----------------------------
static size_t quotearg_buffer_restyled(char *buffer, size_t buffersize, const char *arg, size_t argsize, enum quoting_style quoting_style, int flags, const unsigned int *quote_these_too, const char *left_quote, const char *right_quote)
{
  unsigned int right_quote_idx = 0;
  unsigned int left_quote_idx = 0;
  size_t i;
  size_t len = 0;
  size_t orig_buffersize = 0;
  const char *quote_string = 0;
  unsigned int quote_string_idx = 0;
  size_t quote_string_len = 0;
  bool backslash_escapes = 0;
  bool unibyte_locale = MB_CUR_MAX == 1;
  bool elide_outer_quotes = (flags & QA_ELIDE_OUTER_QUOTES) != 0;
  bool encountered_single_quote = 0;
  bool all_c_and_shell_quote_compat = 1;
  process_input:
  ;

  bool pending_shell_escape_end = 0;
  switch (quoting_style)
  {
    case c_maybe_quoting_style:
    {
      quoting_style = c_quoting_style;
      elide_outer_quotes = 1;
      ;
    }

    case c_quoting_style:
    {
      if (!elide_outer_quotes)
      {
        do
        {
          if (len < buffersize)
          {
            buffer[len] = '"';
          }
          len += 1;
        }
        while (0);
      }
      backslash_escapes = 1;
      quote_string_idx = "\"";
      quote_string_len = 1;
      break;
    }

    case escape_quoting_style:
    {
      backslash_escapes = 1;
      elide_outer_quotes = 0;
      break;
    }

    case locale_quoting_style:

    case clocale_quoting_style:

    case custom_quoting_style:
    {
      helper_quotearg_buffer_restyled_1(&right_quote_idx, &left_quote_idx, &len, &quote_string_idx, &quote_string_len, &backslash_escapes, buffer, buffersize, quoting_style, left_quote, right_quote, quote_string, elide_outer_quotes);
    }

    case shell_escape_quoting_style:
    {
      backslash_escapes = 1;
      ;
    }

    case shell_quoting_style:
    {
      elide_outer_quotes = 1;
      ;
    }

    case shell_escape_always_quoting_style:
    {
      if (!elide_outer_quotes)
      {
        backslash_escapes = 1;
      }
      ;
    }

    case shell_always_quoting_style:
    {
      quoting_style = shell_always_quoting_style;
      if (!elide_outer_quotes)
      {
        do
        {
          if (len < buffersize)
          {
            buffer[len] = '\'';
          }
          len += 1;
        }
        while (0);
      }
      quote_string_idx = "'";
      quote_string_len = 1;
      break;
    }

    case literal_quoting_style:
    {
      elide_outer_quotes = 0;
      break;
    }

    default:
    {
      abort();
    }

  }

  for (i = 0; !((argsize == ((size_t) (-1))) ? (arg[i] == '\0') : (i == argsize)); i += 1)
  {
    helper_quotearg_buffer_restyled_2(&buffersize, &argsize, &i, &len, &orig_buffersize, &encountered_single_quote, &all_c_and_shell_quote_compat, &pending_shell_escape_end, buffer, arg, quoting_style, flags, quote_these_too, quote_string, quote_string_len, backslash_escapes, unibyte_locale, elide_outer_quotes);
  }

  if (((len == 0) && (quoting_style == shell_always_quoting_style)) && elide_outer_quotes)
  {
    goto force_outer_quoting_style;
  }
  if (((quoting_style == shell_always_quoting_style) && (!elide_outer_quotes)) && encountered_single_quote)
  {
    if (all_c_and_shell_quote_compat)
    {
      return quotearg_buffer_restyled(buffer, orig_buffersize, arg, argsize, c_quoting_style, flags, quote_these_too, left_quote, right_quote);
    }
    else
      if ((!buffersize) && orig_buffersize)
    {
      buffersize = orig_buffersize;
      len = 0;
      goto process_input;
    }
  }
  if ((&quote_string[quote_string_idx]) && (!elide_outer_quotes))
  {
    for (; quote_string[quote_string_idx]; quote_string_idx += 1)
    {
      do
      {
        if (len < buffersize)
        {
          buffer[len] = quote_string[quote_string_idx];
        }
        len += 1;
      }
      while (0);
    }

  }
  if (len < buffersize)
  {
    buffer[len] = '\0';
  }
  return len;
  force_outer_quoting_style:
  if ((quoting_style == shell_always_quoting_style) && backslash_escapes)
  {
    quoting_style = shell_escape_always_quoting_style;
  }

  return quotearg_buffer_restyled(buffer, buffersize, arg, argsize, quoting_style, flags & (~QA_ELIDE_OUTER_QUOTES), 0, left_quote, right_quote);
}


----------------------------
struct quoting_options
{
  enum quoting_style style;
  int flags;
  unsigned int quote_these_too[(255 / ((sizeof(int)) * 8)) + 1];
  const char *left_quote;
  const char *right_quote;
}
----------------------------
***/


char *quotearg_n(int n, const char *arg)
{
  return quotearg_n_options(n, arg, (size_t) (-1), &default_quoting_options);
}


/*** DEPENDENCIES:
static struct quoting_options default_quoting_options
----------------------------
static char *quotearg_n_options(int n, const char *arg, size_t argsize, const struct quoting_options *options)
{
  int e = errno;
  struct slotvec *sv = slotvec;
  int nslots_max = (2147483647 < PTRDIFF_MAX) ? (2147483647) : (PTRDIFF_MAX);
  if (!((0 <= n) && (n < nslots_max)))
  {
    abort();
  }
  if (nslots <= n)
  {
    bool preallocated = sv == (&slotvec0);
    idx_t new_nslots = nslots;
    slotvec = (sv = xpalloc((preallocated) ? (0) : (sv), &new_nslots, (n - nslots) + 1, nslots_max, sizeof(*sv)));
    if (preallocated)
    {
      *sv = slotvec0;
    }
    memset(sv + nslots, 0, (new_nslots - nslots) * (sizeof(*sv)));
    nslots = new_nslots;
  }
  {
    size_t size = sv[n].size;
    char *val = sv[n].val;
    int flags = options->flags | QA_ELIDE_NULL_BYTES;
    size_t qsize = quotearg_buffer_restyled(val, size, arg, argsize, options->style, flags, options->quote_these_too, options->left_quote, options->right_quote);
    if (size <= qsize)
    {
      sv[n].size = (size = qsize + 1);
      if (val != slot0)
      {
        free(val);
      }
      sv[n].val = (val = xcharalloc(size));
      quotearg_buffer_restyled(val, size, arg, argsize, options->style, flags, options->quote_these_too, options->left_quote, options->right_quote);
    }
    errno = e;
    return val;
  }
}


----------------------------
***/


char *quotearg(const char *arg)
{
  return quotearg_n(0, arg);
}


/*** DEPENDENCIES:
char *quotearg_n(int n, const char *arg)
{
  return quotearg_n_options(n, arg, (size_t) (-1), &default_quoting_options);
}


----------------------------
***/


char *quotearg_n_mem(int n, const char *arg, size_t argsize)
{
  return quotearg_n_options(n, arg, argsize, &default_quoting_options);
}


/*** DEPENDENCIES:
static struct quoting_options default_quoting_options
----------------------------
static char *quotearg_n_options(int n, const char *arg, size_t argsize, const struct quoting_options *options)
{
  int e = errno;
  struct slotvec *sv = slotvec;
  int nslots_max = (2147483647 < PTRDIFF_MAX) ? (2147483647) : (PTRDIFF_MAX);
  if (!((0 <= n) && (n < nslots_max)))
  {
    abort();
  }
  if (nslots <= n)
  {
    bool preallocated = sv == (&slotvec0);
    idx_t new_nslots = nslots;
    slotvec = (sv = xpalloc((preallocated) ? (0) : (sv), &new_nslots, (n - nslots) + 1, nslots_max, sizeof(*sv)));
    if (preallocated)
    {
      *sv = slotvec0;
    }
    memset(sv + nslots, 0, (new_nslots - nslots) * (sizeof(*sv)));
    nslots = new_nslots;
  }
  {
    size_t size = sv[n].size;
    char *val = sv[n].val;
    int flags = options->flags | QA_ELIDE_NULL_BYTES;
    size_t qsize = quotearg_buffer_restyled(val, size, arg, argsize, options->style, flags, options->quote_these_too, options->left_quote, options->right_quote);
    if (size <= qsize)
    {
      sv[n].size = (size = qsize + 1);
      if (val != slot0)
      {
        free(val);
      }
      sv[n].val = (val = xcharalloc(size));
      quotearg_buffer_restyled(val, size, arg, argsize, options->style, flags, options->quote_these_too, options->left_quote, options->right_quote);
    }
    errno = e;
    return val;
  }
}


----------------------------
***/


char *quotearg_mem(const char *arg, size_t argsize)
{
  return quotearg_n_mem(0, arg, argsize);
}


/*** DEPENDENCIES:
char *quotearg_n_mem(int n, const char *arg, size_t argsize)
{
  return quotearg_n_options(n, arg, argsize, &default_quoting_options);
}


----------------------------
***/


int set_char_quoting(struct quoting_options *o, char c, int i)
{
  unsigned char uc = c;
  unsigned int *p = ((o) ? (o) : (&default_quoting_options))->quote_these_too + (uc / ((sizeof(int)) * 8));
  int shift = uc % ((sizeof(int)) * 8);
  int r = ((*p) >> shift) & 1;
  *p ^= ((i & 1) ^ r) << shift;
  return r;
}


/*** DEPENDENCIES:
static struct quoting_options default_quoting_options
----------------------------
struct quoting_options
{
  enum quoting_style style;
  int flags;
  unsigned int quote_these_too[(255 / ((sizeof(int)) * 8)) + 1];
  const char *left_quote;
  const char *right_quote;
}
----------------------------
***/


char *quotearg_char_mem(const char *arg, size_t argsize, char ch)
{
  struct quoting_options options;
  options = default_quoting_options;
  set_char_quoting(&options, ch, 1);
  return quotearg_n_options(0, arg, argsize, &options);
}


/*** DEPENDENCIES:
static struct quoting_options default_quoting_options
----------------------------
struct quoting_options
{
  enum quoting_style style;
  int flags;
  unsigned int quote_these_too[(255 / ((sizeof(int)) * 8)) + 1];
  const char *left_quote;
  const char *right_quote;
}
----------------------------
static char *quotearg_n_options(int n, const char *arg, size_t argsize, const struct quoting_options *options)
{
  int e = errno;
  struct slotvec *sv = slotvec;
  int nslots_max = (2147483647 < PTRDIFF_MAX) ? (2147483647) : (PTRDIFF_MAX);
  if (!((0 <= n) && (n < nslots_max)))
  {
    abort();
  }
  if (nslots <= n)
  {
    bool preallocated = sv == (&slotvec0);
    idx_t new_nslots = nslots;
    slotvec = (sv = xpalloc((preallocated) ? (0) : (sv), &new_nslots, (n - nslots) + 1, nslots_max, sizeof(*sv)));
    if (preallocated)
    {
      *sv = slotvec0;
    }
    memset(sv + nslots, 0, (new_nslots - nslots) * (sizeof(*sv)));
    nslots = new_nslots;
  }
  {
    size_t size = sv[n].size;
    char *val = sv[n].val;
    int flags = options->flags | QA_ELIDE_NULL_BYTES;
    size_t qsize = quotearg_buffer_restyled(val, size, arg, argsize, options->style, flags, options->quote_these_too, options->left_quote, options->right_quote);
    if (size <= qsize)
    {
      sv[n].size = (size = qsize + 1);
      if (val != slot0)
      {
        free(val);
      }
      sv[n].val = (val = xcharalloc(size));
      quotearg_buffer_restyled(val, size, arg, argsize, options->style, flags, options->quote_these_too, options->left_quote, options->right_quote);
    }
    errno = e;
    return val;
  }
}


----------------------------
int set_char_quoting(struct quoting_options *o, char c, int i)
{
  unsigned char uc = c;
  unsigned int *p = ((o) ? (o) : (&default_quoting_options))->quote_these_too + (uc / ((sizeof(int)) * 8));
  int shift = uc % ((sizeof(int)) * 8);
  int r = ((*p) >> shift) & 1;
  *p ^= ((i & 1) ^ r) << shift;
  return r;
}


----------------------------
***/


char *quotearg_char(const char *arg, char ch)
{
  return quotearg_char_mem(arg, (size_t) (-1), ch);
}


/*** DEPENDENCIES:
char *quotearg_char_mem(const char *arg, size_t argsize, char ch)
{
  struct quoting_options options;
  options = default_quoting_options;
  set_char_quoting(&options, ch, 1);
  return quotearg_n_options(0, arg, argsize, &options);
}


----------------------------
***/


char *quotearg_colon(const char *arg)
{
  return quotearg_char(arg, ':');
}


/*** DEPENDENCIES:
char *quotearg_char(const char *arg, char ch)
{
  return quotearg_char_mem(arg, (size_t) (-1), ch);
}


----------------------------
***/


char *quotearg_colon_mem(const char *arg, size_t argsize)
{
  return quotearg_char_mem(arg, argsize, ':');
}


/*** DEPENDENCIES:
char *quotearg_char_mem(const char *arg, size_t argsize, char ch)
{
  struct quoting_options options;
  options = default_quoting_options;
  set_char_quoting(&options, ch, 1);
  return quotearg_n_options(0, arg, argsize, &options);
}


----------------------------
***/


void set_custom_quoting(struct quoting_options *o, const char *left_quote, const char *right_quote)
{
  unsigned int o_idx = 0;
  if (!(&o[o_idx]))
  {
    o_idx = &default_quoting_options;
  }
  o->style = custom_quoting_style;
  if ((!left_quote) || (!right_quote))
  {
    abort();
  }
  o->left_quote = left_quote;
  o->right_quote = right_quote;
}


/*** DEPENDENCIES:
static struct quoting_options default_quoting_options
----------------------------
struct quoting_options
{
  enum quoting_style style;
  int flags;
  unsigned int quote_these_too[(255 / ((sizeof(int)) * 8)) + 1];
  const char *left_quote;
  const char *right_quote;
}
----------------------------
***/


char *quotearg_n_custom_mem(int n, const char *left_quote, const char *right_quote, const char *arg, size_t argsize)
{
  struct quoting_options o = default_quoting_options;
  set_custom_quoting(&o, left_quote, right_quote);
  return quotearg_n_options(n, arg, argsize, &o);
}


/*** DEPENDENCIES:
void set_custom_quoting(struct quoting_options *o, const char *left_quote, const char *right_quote)
{
  unsigned int o_idx = 0;
  if (!(&o[o_idx]))
  {
    o_idx = &default_quoting_options;
  }
  o->style = custom_quoting_style;
  if ((!left_quote) || (!right_quote))
  {
    abort();
  }
  o->left_quote = left_quote;
  o->right_quote = right_quote;
}


----------------------------
static struct quoting_options default_quoting_options
----------------------------
struct quoting_options
{
  enum quoting_style style;
  int flags;
  unsigned int quote_these_too[(255 / ((sizeof(int)) * 8)) + 1];
  const char *left_quote;
  const char *right_quote;
}
----------------------------
static char *quotearg_n_options(int n, const char *arg, size_t argsize, const struct quoting_options *options)
{
  int e = errno;
  struct slotvec *sv = slotvec;
  int nslots_max = (2147483647 < PTRDIFF_MAX) ? (2147483647) : (PTRDIFF_MAX);
  if (!((0 <= n) && (n < nslots_max)))
  {
    abort();
  }
  if (nslots <= n)
  {
    bool preallocated = sv == (&slotvec0);
    idx_t new_nslots = nslots;
    slotvec = (sv = xpalloc((preallocated) ? (0) : (sv), &new_nslots, (n - nslots) + 1, nslots_max, sizeof(*sv)));
    if (preallocated)
    {
      *sv = slotvec0;
    }
    memset(sv + nslots, 0, (new_nslots - nslots) * (sizeof(*sv)));
    nslots = new_nslots;
  }
  {
    size_t size = sv[n].size;
    char *val = sv[n].val;
    int flags = options->flags | QA_ELIDE_NULL_BYTES;
    size_t qsize = quotearg_buffer_restyled(val, size, arg, argsize, options->style, flags, options->quote_these_too, options->left_quote, options->right_quote);
    if (size <= qsize)
    {
      sv[n].size = (size = qsize + 1);
      if (val != slot0)
      {
        free(val);
      }
      sv[n].val = (val = xcharalloc(size));
      quotearg_buffer_restyled(val, size, arg, argsize, options->style, flags, options->quote_these_too, options->left_quote, options->right_quote);
    }
    errno = e;
    return val;
  }
}


----------------------------
***/


char *quotearg_n_custom(int n, const char *left_quote, const char *right_quote, const char *arg)
{
  return quotearg_n_custom_mem(n, left_quote, right_quote, arg, (size_t) (-1));
}


/*** DEPENDENCIES:
char *quotearg_n_custom_mem(int n, const char *left_quote, const char *right_quote, const char *arg, size_t argsize)
{
  struct quoting_options o = default_quoting_options;
  set_custom_quoting(&o, left_quote, right_quote);
  return quotearg_n_options(n, arg, argsize, &o);
}


----------------------------
***/


char *quotearg_custom(const char *left_quote, const char *right_quote, const char *arg)
{
  return quotearg_n_custom(0, left_quote, right_quote, arg);
}


/*** DEPENDENCIES:
char *quotearg_n_custom(int n, const char *left_quote, const char *right_quote, const char *arg)
{
  return quotearg_n_custom_mem(n, left_quote, right_quote, arg, (size_t) (-1));
}


----------------------------
***/


char *quotearg_custom_mem(const char *left_quote, const char *right_quote, const char *arg, size_t argsize)
{
  return quotearg_n_custom_mem(0, left_quote, right_quote, arg, argsize);
}


/*** DEPENDENCIES:
char *quotearg_n_custom_mem(int n, const char *left_quote, const char *right_quote, const char *arg, size_t argsize)
{
  struct quoting_options o = default_quoting_options;
  set_custom_quoting(&o, left_quote, right_quote);
  return quotearg_n_options(n, arg, argsize, &o);
}


----------------------------
***/


const char *quote_n_mem(int n, const char *arg, size_t argsize)
{
  return quotearg_n_options(n, arg, argsize, &quote_quoting_options);
}


/*** DEPENDENCIES:
extern struct quoting_options quote_quoting_options
----------------------------
static char *quotearg_n_options(int n, const char *arg, size_t argsize, const struct quoting_options *options)
{
  int e = errno;
  struct slotvec *sv = slotvec;
  int nslots_max = (2147483647 < PTRDIFF_MAX) ? (2147483647) : (PTRDIFF_MAX);
  if (!((0 <= n) && (n < nslots_max)))
  {
    abort();
  }
  if (nslots <= n)
  {
    bool preallocated = sv == (&slotvec0);
    idx_t new_nslots = nslots;
    slotvec = (sv = xpalloc((preallocated) ? (0) : (sv), &new_nslots, (n - nslots) + 1, nslots_max, sizeof(*sv)));
    if (preallocated)
    {
      *sv = slotvec0;
    }
    memset(sv + nslots, 0, (new_nslots - nslots) * (sizeof(*sv)));
    nslots = new_nslots;
  }
  {
    size_t size = sv[n].size;
    char *val = sv[n].val;
    int flags = options->flags | QA_ELIDE_NULL_BYTES;
    size_t qsize = quotearg_buffer_restyled(val, size, arg, argsize, options->style, flags, options->quote_these_too, options->left_quote, options->right_quote);
    if (size <= qsize)
    {
      sv[n].size = (size = qsize + 1);
      if (val != slot0)
      {
        free(val);
      }
      sv[n].val = (val = xcharalloc(size));
      quotearg_buffer_restyled(val, size, arg, argsize, options->style, flags, options->quote_these_too, options->left_quote, options->right_quote);
    }
    errno = e;
    return val;
  }
}


----------------------------
***/


const char *quote_mem(const char *arg, size_t argsize)
{
  return quote_n_mem(0, arg, argsize);
}


/*** DEPENDENCIES:
const char *quote_n_mem(int n, const char *arg, size_t argsize)
{
  return quotearg_n_options(n, arg, argsize, &quote_quoting_options);
}


----------------------------
***/


const char *quote_n(int n, const char *arg)
{
  return quote_n_mem(n, arg, (size_t) (-1));
}


/*** DEPENDENCIES:
const char *quote_n_mem(int n, const char *arg, size_t argsize)
{
  return quotearg_n_options(n, arg, argsize, &quote_quoting_options);
}


----------------------------
***/


const char *quote(const char *arg)
{
  return quote_n(0, arg);
}


/*** DEPENDENCIES:
const char *quote_n(int n, const char *arg)
{
  return quote_n_mem(n, arg, (size_t) (-1));
}


----------------------------
***/


int set_quoting_flags(struct quoting_options *o, int i)
{
  unsigned int o_idx = 0;
  int r;
  if (!(&o[o_idx]))
  {
    o_idx = &default_quoting_options;
  }
  r = o->flags;
  o->flags = i;
  return r;
}


/*** DEPENDENCIES:
static struct quoting_options default_quoting_options
----------------------------
struct quoting_options
{
  enum quoting_style style;
  int flags;
  unsigned int quote_these_too[(255 / ((sizeof(int)) * 8)) + 1];
  const char *left_quote;
  const char *right_quote;
}
----------------------------
***/


char *quotearg_alloc_mem(const char *arg, size_t argsize, size_t *size, const struct quoting_options *o)
{
  const struct quoting_options *p = (o) ? (o) : (&default_quoting_options);
  int e = errno;
  int flags = p->flags | ((size) ? (0) : (QA_ELIDE_NULL_BYTES));
  size_t bufsize = quotearg_buffer_restyled(0, 0, arg, argsize, p->style, flags, p->quote_these_too, p->left_quote, p->right_quote) + 1;
  char *buf = xcharalloc(bufsize);
  quotearg_buffer_restyled(buf, bufsize, arg, argsize, p->style, flags, p->quote_these_too, p->left_quote, p->right_quote);
  errno = e;
  if (size)
  {
    *size = bufsize - 1;
  }
  return buf;
}


/*** DEPENDENCIES:
static size_t quotearg_buffer_restyled(char *buffer, size_t buffersize, const char *arg, size_t argsize, enum quoting_style quoting_style, int flags, const unsigned int *quote_these_too, const char *left_quote, const char *right_quote)
{
  unsigned int right_quote_idx = 0;
  unsigned int left_quote_idx = 0;
  size_t i;
  size_t len = 0;
  size_t orig_buffersize = 0;
  const char *quote_string = 0;
  unsigned int quote_string_idx = 0;
  size_t quote_string_len = 0;
  bool backslash_escapes = 0;
  bool unibyte_locale = MB_CUR_MAX == 1;
  bool elide_outer_quotes = (flags & QA_ELIDE_OUTER_QUOTES) != 0;
  bool encountered_single_quote = 0;
  bool all_c_and_shell_quote_compat = 1;
  process_input:
  ;

  bool pending_shell_escape_end = 0;
  switch (quoting_style)
  {
    case c_maybe_quoting_style:
    {
      quoting_style = c_quoting_style;
      elide_outer_quotes = 1;
      ;
    }

    case c_quoting_style:
    {
      if (!elide_outer_quotes)
      {
        do
        {
          if (len < buffersize)
          {
            buffer[len] = '"';
          }
          len += 1;
        }
        while (0);
      }
      backslash_escapes = 1;
      quote_string_idx = "\"";
      quote_string_len = 1;
      break;
    }

    case escape_quoting_style:
    {
      backslash_escapes = 1;
      elide_outer_quotes = 0;
      break;
    }

    case locale_quoting_style:

    case clocale_quoting_style:

    case custom_quoting_style:
    {
      helper_quotearg_buffer_restyled_1(&right_quote_idx, &left_quote_idx, &len, &quote_string_idx, &quote_string_len, &backslash_escapes, buffer, buffersize, quoting_style, left_quote, right_quote, quote_string, elide_outer_quotes);
    }

    case shell_escape_quoting_style:
    {
      backslash_escapes = 1;
      ;
    }

    case shell_quoting_style:
    {
      elide_outer_quotes = 1;
      ;
    }

    case shell_escape_always_quoting_style:
    {
      if (!elide_outer_quotes)
      {
        backslash_escapes = 1;
      }
      ;
    }

    case shell_always_quoting_style:
    {
      quoting_style = shell_always_quoting_style;
      if (!elide_outer_quotes)
      {
        do
        {
          if (len < buffersize)
          {
            buffer[len] = '\'';
          }
          len += 1;
        }
        while (0);
      }
      quote_string_idx = "'";
      quote_string_len = 1;
      break;
    }

    case literal_quoting_style:
    {
      elide_outer_quotes = 0;
      break;
    }

    default:
    {
      abort();
    }

  }

  for (i = 0; !((argsize == ((size_t) (-1))) ? (arg[i] == '\0') : (i == argsize)); i += 1)
  {
    helper_quotearg_buffer_restyled_2(&buffersize, &argsize, &i, &len, &orig_buffersize, &encountered_single_quote, &all_c_and_shell_quote_compat, &pending_shell_escape_end, buffer, arg, quoting_style, flags, quote_these_too, quote_string, quote_string_len, backslash_escapes, unibyte_locale, elide_outer_quotes);
  }

  if (((len == 0) && (quoting_style == shell_always_quoting_style)) && elide_outer_quotes)
  {
    goto force_outer_quoting_style;
  }
  if (((quoting_style == shell_always_quoting_style) && (!elide_outer_quotes)) && encountered_single_quote)
  {
    if (all_c_and_shell_quote_compat)
    {
      return quotearg_buffer_restyled(buffer, orig_buffersize, arg, argsize, c_quoting_style, flags, quote_these_too, left_quote, right_quote);
    }
    else
      if ((!buffersize) && orig_buffersize)
    {
      buffersize = orig_buffersize;
      len = 0;
      goto process_input;
    }
  }
  if ((&quote_string[quote_string_idx]) && (!elide_outer_quotes))
  {
    for (; quote_string[quote_string_idx]; quote_string_idx += 1)
    {
      do
      {
        if (len < buffersize)
        {
          buffer[len] = quote_string[quote_string_idx];
        }
        len += 1;
      }
      while (0);
    }

  }
  if (len < buffersize)
  {
    buffer[len] = '\0';
  }
  return len;
  force_outer_quoting_style:
  if ((quoting_style == shell_always_quoting_style) && backslash_escapes)
  {
    quoting_style = shell_escape_always_quoting_style;
  }

  return quotearg_buffer_restyled(buffer, buffersize, arg, argsize, quoting_style, flags & (~QA_ELIDE_OUTER_QUOTES), 0, left_quote, right_quote);
}


----------------------------
static struct quoting_options default_quoting_options
----------------------------
struct quoting_options
{
  enum quoting_style style;
  int flags;
  unsigned int quote_these_too[(255 / ((sizeof(int)) * 8)) + 1];
  const char *left_quote;
  const char *right_quote;
}
----------------------------
char *xcharalloc(size_t n)
{
  return (char *) (((sizeof(char)) == 1) ? (xmalloc(n)) : (xnmalloc(n, sizeof(char))));
}


----------------------------
***/


char *quotearg_alloc(const char *arg, size_t argsize, const struct quoting_options *o)
{
  return quotearg_alloc_mem(arg, argsize, 0, o);
}


/*** DEPENDENCIES:
struct quoting_options
{
  enum quoting_style style;
  int flags;
  unsigned int quote_these_too[(255 / ((sizeof(int)) * 8)) + 1];
  const char *left_quote;
  const char *right_quote;
}
----------------------------
char *quotearg_alloc_mem(const char *arg, size_t argsize, size_t *size, const struct quoting_options *o)
{
  const struct quoting_options *p = (o) ? (o) : (&default_quoting_options);
  int e = errno;
  int flags = p->flags | ((size) ? (0) : (QA_ELIDE_NULL_BYTES));
  size_t bufsize = quotearg_buffer_restyled(0, 0, arg, argsize, p->style, flags, p->quote_these_too, p->left_quote, p->right_quote) + 1;
  char *buf = xcharalloc(bufsize);
  quotearg_buffer_restyled(buf, bufsize, arg, argsize, p->style, flags, p->quote_these_too, p->left_quote, p->right_quote);
  errno = e;
  if (size)
  {
    *size = bufsize - 1;
  }
  return buf;
}


----------------------------
***/


static struct quoting_options quoting_options_from_style(enum quoting_style style)
{
  struct quoting_options o = {literal_quoting_style, 0, {0}, 0, 0};
  if (style == custom_quoting_style)
  {
    abort();
  }
  o.style = style;
  return o;
}


/*** DEPENDENCIES:
struct quoting_options
{
  enum quoting_style style;
  int flags;
  unsigned int quote_these_too[(255 / ((sizeof(int)) * 8)) + 1];
  const char *left_quote;
  const char *right_quote;
}
----------------------------
enum quoting_style
{
  literal_quoting_style,
  shell_quoting_style,
  shell_always_quoting_style,
  shell_escape_quoting_style,
  shell_escape_always_quoting_style,
  c_quoting_style,
  c_maybe_quoting_style,
  escape_quoting_style,
  locale_quoting_style,
  clocale_quoting_style,
  custom_quoting_style
}
----------------------------
***/


char *quotearg_n_style(int n, enum quoting_style s, const char *arg)
{
  const struct quoting_options o = quoting_options_from_style(s);
  return quotearg_n_options(n, arg, (size_t) (-1), &o);
}


/*** DEPENDENCIES:
struct quoting_options
{
  enum quoting_style style;
  int flags;
  unsigned int quote_these_too[(255 / ((sizeof(int)) * 8)) + 1];
  const char *left_quote;
  const char *right_quote;
}
----------------------------
static struct quoting_options quoting_options_from_style(enum quoting_style style)
{
  struct quoting_options o = {literal_quoting_style, 0, {0}, 0, 0};
  if (style == custom_quoting_style)
  {
    abort();
  }
  o.style = style;
  return o;
}


----------------------------
enum quoting_style
{
  literal_quoting_style,
  shell_quoting_style,
  shell_always_quoting_style,
  shell_escape_quoting_style,
  shell_escape_always_quoting_style,
  c_quoting_style,
  c_maybe_quoting_style,
  escape_quoting_style,
  locale_quoting_style,
  clocale_quoting_style,
  custom_quoting_style
}
----------------------------
static char *quotearg_n_options(int n, const char *arg, size_t argsize, const struct quoting_options *options)
{
  int e = errno;
  struct slotvec *sv = slotvec;
  int nslots_max = (2147483647 < PTRDIFF_MAX) ? (2147483647) : (PTRDIFF_MAX);
  if (!((0 <= n) && (n < nslots_max)))
  {
    abort();
  }
  if (nslots <= n)
  {
    bool preallocated = sv == (&slotvec0);
    idx_t new_nslots = nslots;
    slotvec = (sv = xpalloc((preallocated) ? (0) : (sv), &new_nslots, (n - nslots) + 1, nslots_max, sizeof(*sv)));
    if (preallocated)
    {
      *sv = slotvec0;
    }
    memset(sv + nslots, 0, (new_nslots - nslots) * (sizeof(*sv)));
    nslots = new_nslots;
  }
  {
    size_t size = sv[n].size;
    char *val = sv[n].val;
    int flags = options->flags | QA_ELIDE_NULL_BYTES;
    size_t qsize = quotearg_buffer_restyled(val, size, arg, argsize, options->style, flags, options->quote_these_too, options->left_quote, options->right_quote);
    if (size <= qsize)
    {
      sv[n].size = (size = qsize + 1);
      if (val != slot0)
      {
        free(val);
      }
      sv[n].val = (val = xcharalloc(size));
      quotearg_buffer_restyled(val, size, arg, argsize, options->style, flags, options->quote_these_too, options->left_quote, options->right_quote);
    }
    errno = e;
    return val;
  }
}


----------------------------
***/


char *quotearg_style(enum quoting_style s, const char *arg)
{
  return quotearg_n_style(0, s, arg);
}


/*** DEPENDENCIES:
char *quotearg_n_style(int n, enum quoting_style s, const char *arg)
{
  const struct quoting_options o = quoting_options_from_style(s);
  return quotearg_n_options(n, arg, (size_t) (-1), &o);
}


----------------------------
enum quoting_style
{
  literal_quoting_style,
  shell_quoting_style,
  shell_always_quoting_style,
  shell_escape_quoting_style,
  shell_escape_always_quoting_style,
  c_quoting_style,
  c_maybe_quoting_style,
  escape_quoting_style,
  locale_quoting_style,
  clocale_quoting_style,
  custom_quoting_style
}
----------------------------
***/


char *quotearg_n_style_mem(int n, enum quoting_style s, const char *arg, size_t argsize)
{
  const struct quoting_options o = quoting_options_from_style(s);
  return quotearg_n_options(n, arg, argsize, &o);
}


/*** DEPENDENCIES:
struct quoting_options
{
  enum quoting_style style;
  int flags;
  unsigned int quote_these_too[(255 / ((sizeof(int)) * 8)) + 1];
  const char *left_quote;
  const char *right_quote;
}
----------------------------
static struct quoting_options quoting_options_from_style(enum quoting_style style)
{
  struct quoting_options o = {literal_quoting_style, 0, {0}, 0, 0};
  if (style == custom_quoting_style)
  {
    abort();
  }
  o.style = style;
  return o;
}


----------------------------
enum quoting_style
{
  literal_quoting_style,
  shell_quoting_style,
  shell_always_quoting_style,
  shell_escape_quoting_style,
  shell_escape_always_quoting_style,
  c_quoting_style,
  c_maybe_quoting_style,
  escape_quoting_style,
  locale_quoting_style,
  clocale_quoting_style,
  custom_quoting_style
}
----------------------------
static char *quotearg_n_options(int n, const char *arg, size_t argsize, const struct quoting_options *options)
{
  int e = errno;
  struct slotvec *sv = slotvec;
  int nslots_max = (2147483647 < PTRDIFF_MAX) ? (2147483647) : (PTRDIFF_MAX);
  if (!((0 <= n) && (n < nslots_max)))
  {
    abort();
  }
  if (nslots <= n)
  {
    bool preallocated = sv == (&slotvec0);
    idx_t new_nslots = nslots;
    slotvec = (sv = xpalloc((preallocated) ? (0) : (sv), &new_nslots, (n - nslots) + 1, nslots_max, sizeof(*sv)));
    if (preallocated)
    {
      *sv = slotvec0;
    }
    memset(sv + nslots, 0, (new_nslots - nslots) * (sizeof(*sv)));
    nslots = new_nslots;
  }
  {
    size_t size = sv[n].size;
    char *val = sv[n].val;
    int flags = options->flags | QA_ELIDE_NULL_BYTES;
    size_t qsize = quotearg_buffer_restyled(val, size, arg, argsize, options->style, flags, options->quote_these_too, options->left_quote, options->right_quote);
    if (size <= qsize)
    {
      sv[n].size = (size = qsize + 1);
      if (val != slot0)
      {
        free(val);
      }
      sv[n].val = (val = xcharalloc(size));
      quotearg_buffer_restyled(val, size, arg, argsize, options->style, flags, options->quote_these_too, options->left_quote, options->right_quote);
    }
    errno = e;
    return val;
  }
}


----------------------------
***/


char *quotearg_style_mem(enum quoting_style s, const char *arg, size_t argsize)
{
  return quotearg_n_style_mem(0, s, arg, argsize);
}


/*** DEPENDENCIES:
char *quotearg_n_style_mem(int n, enum quoting_style s, const char *arg, size_t argsize)
{
  const struct quoting_options o = quoting_options_from_style(s);
  return quotearg_n_options(n, arg, argsize, &o);
}


----------------------------
enum quoting_style
{
  literal_quoting_style,
  shell_quoting_style,
  shell_always_quoting_style,
  shell_escape_quoting_style,
  shell_escape_always_quoting_style,
  c_quoting_style,
  c_maybe_quoting_style,
  escape_quoting_style,
  locale_quoting_style,
  clocale_quoting_style,
  custom_quoting_style
}
----------------------------
***/


struct quoting_options *clone_quoting_options(struct quoting_options *o)
{
  int e = errno;
  struct quoting_options *p = xmemdup((o) ? (o) : (&default_quoting_options), sizeof(*o));
  errno = e;
  return p;
}


/*** DEPENDENCIES:
static struct quoting_options default_quoting_options
----------------------------
void *xmemdup(const void *p, size_t s)
{
  return memcpy(xmalloc(s), p, s);
}


----------------------------
struct quoting_options
{
  enum quoting_style style;
  int flags;
  unsigned int quote_these_too[(255 / ((sizeof(int)) * 8)) + 1];
  const char *left_quote;
  const char *right_quote;
}
----------------------------
***/


enum quoting_style get_quoting_style(const struct quoting_options *o)
{
  return ((o) ? (o) : (&default_quoting_options))->style;
}


/*** DEPENDENCIES:
static struct quoting_options default_quoting_options
----------------------------
struct quoting_options
{
  enum quoting_style style;
  int flags;
  unsigned int quote_these_too[(255 / ((sizeof(int)) * 8)) + 1];
  const char *left_quote;
  const char *right_quote;
}
----------------------------
enum quoting_style
{
  literal_quoting_style,
  shell_quoting_style,
  shell_always_quoting_style,
  shell_escape_quoting_style,
  shell_escape_always_quoting_style,
  c_quoting_style,
  c_maybe_quoting_style,
  escape_quoting_style,
  locale_quoting_style,
  clocale_quoting_style,
  custom_quoting_style
}
----------------------------
***/


void set_quoting_style(struct quoting_options *o, enum quoting_style s)
{
  ((o) ? (o) : (&default_quoting_options))->style = s;
}


/*** DEPENDENCIES:
static struct quoting_options default_quoting_options
----------------------------
struct quoting_options
{
  enum quoting_style style;
  int flags;
  unsigned int quote_these_too[(255 / ((sizeof(int)) * 8)) + 1];
  const char *left_quote;
  const char *right_quote;
}
----------------------------
enum quoting_style
{
  literal_quoting_style,
  shell_quoting_style,
  shell_always_quoting_style,
  shell_escape_quoting_style,
  shell_escape_always_quoting_style,
  c_quoting_style,
  c_maybe_quoting_style,
  escape_quoting_style,
  locale_quoting_style,
  clocale_quoting_style,
  custom_quoting_style
}
----------------------------
***/


size_t quotearg_buffer(char *buffer, size_t buffersize, const char *arg, size_t argsize, const struct quoting_options *o)
{
  const struct quoting_options *p = (o) ? (o) : (&default_quoting_options);
  int e = errno;
  size_t r = quotearg_buffer_restyled(buffer, buffersize, arg, argsize, p->style, p->flags, p->quote_these_too, p->left_quote, p->right_quote);
  errno = e;
  return r;
}


/*** DEPENDENCIES:
static size_t quotearg_buffer_restyled(char *buffer, size_t buffersize, const char *arg, size_t argsize, enum quoting_style quoting_style, int flags, const unsigned int *quote_these_too, const char *left_quote, const char *right_quote)
{
  unsigned int right_quote_idx = 0;
  unsigned int left_quote_idx = 0;
  size_t i;
  size_t len = 0;
  size_t orig_buffersize = 0;
  const char *quote_string = 0;
  unsigned int quote_string_idx = 0;
  size_t quote_string_len = 0;
  bool backslash_escapes = 0;
  bool unibyte_locale = MB_CUR_MAX == 1;
  bool elide_outer_quotes = (flags & QA_ELIDE_OUTER_QUOTES) != 0;
  bool encountered_single_quote = 0;
  bool all_c_and_shell_quote_compat = 1;
  process_input:
  ;

  bool pending_shell_escape_end = 0;
  switch (quoting_style)
  {
    case c_maybe_quoting_style:
    {
      quoting_style = c_quoting_style;
      elide_outer_quotes = 1;
      ;
    }

    case c_quoting_style:
    {
      if (!elide_outer_quotes)
      {
        do
        {
          if (len < buffersize)
          {
            buffer[len] = '"';
          }
          len += 1;
        }
        while (0);
      }
      backslash_escapes = 1;
      quote_string_idx = "\"";
      quote_string_len = 1;
      break;
    }

    case escape_quoting_style:
    {
      backslash_escapes = 1;
      elide_outer_quotes = 0;
      break;
    }

    case locale_quoting_style:

    case clocale_quoting_style:

    case custom_quoting_style:
    {
      helper_quotearg_buffer_restyled_1(&right_quote_idx, &left_quote_idx, &len, &quote_string_idx, &quote_string_len, &backslash_escapes, buffer, buffersize, quoting_style, left_quote, right_quote, quote_string, elide_outer_quotes);
    }

    case shell_escape_quoting_style:
    {
      backslash_escapes = 1;
      ;
    }

    case shell_quoting_style:
    {
      elide_outer_quotes = 1;
      ;
    }

    case shell_escape_always_quoting_style:
    {
      if (!elide_outer_quotes)
      {
        backslash_escapes = 1;
      }
      ;
    }

    case shell_always_quoting_style:
    {
      quoting_style = shell_always_quoting_style;
      if (!elide_outer_quotes)
      {
        do
        {
          if (len < buffersize)
          {
            buffer[len] = '\'';
          }
          len += 1;
        }
        while (0);
      }
      quote_string_idx = "'";
      quote_string_len = 1;
      break;
    }

    case literal_quoting_style:
    {
      elide_outer_quotes = 0;
      break;
    }

    default:
    {
      abort();
    }

  }

  for (i = 0; !((argsize == ((size_t) (-1))) ? (arg[i] == '\0') : (i == argsize)); i += 1)
  {
    helper_quotearg_buffer_restyled_2(&buffersize, &argsize, &i, &len, &orig_buffersize, &encountered_single_quote, &all_c_and_shell_quote_compat, &pending_shell_escape_end, buffer, arg, quoting_style, flags, quote_these_too, quote_string, quote_string_len, backslash_escapes, unibyte_locale, elide_outer_quotes);
  }

  if (((len == 0) && (quoting_style == shell_always_quoting_style)) && elide_outer_quotes)
  {
    goto force_outer_quoting_style;
  }
  if (((quoting_style == shell_always_quoting_style) && (!elide_outer_quotes)) && encountered_single_quote)
  {
    if (all_c_and_shell_quote_compat)
    {
      return quotearg_buffer_restyled(buffer, orig_buffersize, arg, argsize, c_quoting_style, flags, quote_these_too, left_quote, right_quote);
    }
    else
      if ((!buffersize) && orig_buffersize)
    {
      buffersize = orig_buffersize;
      len = 0;
      goto process_input;
    }
  }
  if ((&quote_string[quote_string_idx]) && (!elide_outer_quotes))
  {
    for (; quote_string[quote_string_idx]; quote_string_idx += 1)
    {
      do
      {
        if (len < buffersize)
        {
          buffer[len] = quote_string[quote_string_idx];
        }
        len += 1;
      }
      while (0);
    }

  }
  if (len < buffersize)
  {
    buffer[len] = '\0';
  }
  return len;
  force_outer_quoting_style:
  if ((quoting_style == shell_always_quoting_style) && backslash_escapes)
  {
    quoting_style = shell_escape_always_quoting_style;
  }

  return quotearg_buffer_restyled(buffer, buffersize, arg, argsize, quoting_style, flags & (~QA_ELIDE_OUTER_QUOTES), 0, left_quote, right_quote);
}


----------------------------
static struct quoting_options default_quoting_options
----------------------------
struct quoting_options
{
  enum quoting_style style;
  int flags;
  unsigned int quote_these_too[(255 / ((sizeof(int)) * 8)) + 1];
  const char *left_quote;
  const char *right_quote;
}
----------------------------
***/


void quotearg_free(void)
{
  struct slotvec *sv = slotvec;
  int i;
  for (i = 1; i < nslots; i += 1)
  {
    free(sv[i].val);
  }

  if (sv[0].val != slot0)
  {
    free(sv[0].val);
    slotvec0.size = sizeof(slot0);
    slotvec0.val = slot0;
  }
  if (sv != (&slotvec0))
  {
    free(sv);
    slotvec = &slotvec0;
  }
  nslots = 1;
}


/*** DEPENDENCIES:
static int nslots = 1
----------------------------
static char slot0[256]
----------------------------
static struct slotvec slotvec0 = {sizeof(slot0), slot0}
----------------------------
struct slotvec
{
  size_t size;
  char *val;
}
----------------------------
***/


char *quotearg_n_style_colon(int n, enum quoting_style s, const char *arg)
{
  struct quoting_options options;
  options = quoting_options_from_style(s);
  set_char_quoting(&options, ':', 1);
  return quotearg_n_options(n, arg, (size_t) (-1), &options);
}


/*** DEPENDENCIES:
static struct quoting_options quoting_options_from_style(enum quoting_style style)
{
  struct quoting_options o = {literal_quoting_style, 0, {0}, 0, 0};
  if (style == custom_quoting_style)
  {
    abort();
  }
  o.style = style;
  return o;
}


----------------------------
enum quoting_style
{
  literal_quoting_style,
  shell_quoting_style,
  shell_always_quoting_style,
  shell_escape_quoting_style,
  shell_escape_always_quoting_style,
  c_quoting_style,
  c_maybe_quoting_style,
  escape_quoting_style,
  locale_quoting_style,
  clocale_quoting_style,
  custom_quoting_style
}
----------------------------
static char *quotearg_n_options(int n, const char *arg, size_t argsize, const struct quoting_options *options)
{
  int e = errno;
  struct slotvec *sv = slotvec;
  int nslots_max = (2147483647 < PTRDIFF_MAX) ? (2147483647) : (PTRDIFF_MAX);
  if (!((0 <= n) && (n < nslots_max)))
  {
    abort();
  }
  if (nslots <= n)
  {
    bool preallocated = sv == (&slotvec0);
    idx_t new_nslots = nslots;
    slotvec = (sv = xpalloc((preallocated) ? (0) : (sv), &new_nslots, (n - nslots) + 1, nslots_max, sizeof(*sv)));
    if (preallocated)
    {
      *sv = slotvec0;
    }
    memset(sv + nslots, 0, (new_nslots - nslots) * (sizeof(*sv)));
    nslots = new_nslots;
  }
  {
    size_t size = sv[n].size;
    char *val = sv[n].val;
    int flags = options->flags | QA_ELIDE_NULL_BYTES;
    size_t qsize = quotearg_buffer_restyled(val, size, arg, argsize, options->style, flags, options->quote_these_too, options->left_quote, options->right_quote);
    if (size <= qsize)
    {
      sv[n].size = (size = qsize + 1);
      if (val != slot0)
      {
        free(val);
      }
      sv[n].val = (val = xcharalloc(size));
      quotearg_buffer_restyled(val, size, arg, argsize, options->style, flags, options->quote_these_too, options->left_quote, options->right_quote);
    }
    errno = e;
    return val;
  }
}


----------------------------
int set_char_quoting(struct quoting_options *o, char c, int i)
{
  unsigned char uc = c;
  unsigned int *p = ((o) ? (o) : (&default_quoting_options))->quote_these_too + (uc / ((sizeof(int)) * 8));
  int shift = uc % ((sizeof(int)) * 8);
  int r = ((*p) >> shift) & 1;
  *p ^= ((i & 1) ^ r) << shift;
  return r;
}


----------------------------
struct quoting_options
{
  enum quoting_style style;
  int flags;
  unsigned int quote_these_too[(255 / ((sizeof(int)) * 8)) + 1];
  const char *left_quote;
  const char *right_quote;
}
----------------------------
***/


