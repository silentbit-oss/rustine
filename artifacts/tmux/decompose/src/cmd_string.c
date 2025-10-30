static int cmd_string_getc(const char *s, size_t *p)
{
  const u_char *ucs = s;
  if (ucs[*p] == '\0')
  {
    return EOF;
  }
  return ucs[(*p)++];
}


/*** DEPENDENCIES:
***/


static void cmd_string_ungetc(size_t *p)
{
  *p -= 1;
}


/*** DEPENDENCIES:
***/


static void cmd_string_copy(char **dst, char *src, size_t *len)
{
  size_t srclen;
  srclen = strlen(src);
  *dst = xrealloc(*dst, ((*len) + srclen) + 1);
  strlcpy((*dst) + (*len), src, srclen + 1);
  *len += srclen;
  free(src);
}


/*** DEPENDENCIES:
void *xrealloc(void *ptr, size_t size)
{
  return xreallocarray(ptr, 1, size);
}


----------------------------
***/


// hint:  ['ch_ref is a mutable refrence to int']
void helper_helper_cmd_string_string_1_1(int * const ch_ref, const char * const s, size_t * const p, int esc)
{
  int ch = *ch_ref;
  if (!esc)
  {
    break;
  }
  switch (ch = cmd_string_getc(s, p))
  {
    case EOF:
    {
      goto error;
    }

    case 'e':
    {
      ch = '\033';
      break;
    }

    case 'r':
    {
      ch = '\r';
      break;
    }

    case 'n':
    {
      ch = '\n';
      break;
    }

    case 't':
    {
      ch = '\t';
      break;
    }

  }

  break;
  *ch_ref = ch;
}


/*** DEPENDENCIES:
static int cmd_string_getc(const char *s, size_t *p)
{
  const u_char *ucs = s;
  if (ucs[*p] == '\0')
  {
    return EOF;
  }
  return ucs[(*p)++];
}


----------------------------
***/


// hint:  ['argc_ref is a mutable refrence to int', 'argv_idx_ref is a mutable refrence to unsigned int', 'buf_idx_ref is a mutable refrence to unsigned int', 'whitespace_idx_ref is a mutable refrence to unsigned int', 'equals_idx_ref is a mutable refrence to unsigned int', 'len_ref is a mutable refrence to size_t']
void helper_helper_cmd_string_split_1_1(int * const argc_ref, unsigned int * const argv_idx_ref, unsigned int * const buf_idx_ref, unsigned int * const whitespace_idx_ref, unsigned int * const equals_idx_ref, size_t * const len_ref, char ** const argv, char * const buf, const char * const whitespace, const char * const equals, int ch)
{
  int argc = *argc_ref;
  unsigned int argv_idx = *argv_idx_ref;
  unsigned int buf_idx = *buf_idx_ref;
  unsigned int whitespace_idx = *whitespace_idx_ref;
  unsigned int equals_idx = *equals_idx_ref;
  size_t len = *len_ref;
  if ((&buf[buf_idx]) != 0)
  {
    buf_idx = xrealloc(buf_idx, len + 1);
    buf[len + buf_idx] = '\0';
    argv_idx = xreallocarray(argv_idx, argc + 1, sizeof(*argv_idx));
    argv[argc + argv_idx] = &buf[buf_idx];
    argc += 1;
    buf_idx = 0;
    len = 0;
  }
  if (ch != EOF)
  {
    break;
  }
  while (argc != 0)
  {
    equals_idx = strchr(argv[0 + argv_idx], '=');
    whitespace_idx = argv[0 + argv_idx] + strcspn(argv[0 + argv_idx], " \t");
    if (((&equals[equals_idx]) == 0) || ((&equals[equals_idx]) > (&whitespace[whitespace_idx])))
    {
      break;
    }
    environ_put(global_environ, argv[0 + argv_idx]);
    argc -= 1;
    memmove(argv, (&argv[argv_idx]) + 1, argc * (sizeof(*(&argv[argv_idx]))));
  }

  goto done;
  *argc_ref = argc;
  *argv_idx_ref = argv_idx;
  *buf_idx_ref = buf_idx;
  *whitespace_idx_ref = whitespace_idx;
  *equals_idx_ref = equals_idx;
  *len_ref = len;
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
void environ_put(struct environ *env, const char *var)
{
  char *name;
  unsigned int name_idx = 0;
  char *value;
  unsigned int value_idx = 0;
  value_idx = strchr(var, '=');
  if ((&value[value_idx]) == 0)
  {
    return;
  }
  value_idx += 1;
  name_idx = xstrdup(var);
  name[strcspn(name, "=") + name_idx] = '\0';
  environ_set(env, name, "%s", value);
  free(name);
}


----------------------------
void *xrealloc(void *ptr, size_t size)
{
  return xreallocarray(ptr, 1, size);
}


----------------------------
***/


// hint:  ['ch_ref is a mutable refrence to int', 'buf_idx_ref is a mutable refrence to unsigned int', 'len_ref is a mutable refrence to size_t']
char *helper_cmd_string_variable_1(int * const ch_ref, unsigned int * const buf_idx_ref, size_t * const len_ref, const char * const s, size_t * const p, char * const buf, char * const t)
{
  int ch = *ch_ref;
  unsigned int buf_idx = *buf_idx_ref;
  size_t len = *len_ref;
  if (!(((ch == '_') || ((ch >= 'a') && (ch <= 'z'))) || ((ch >= 'A') && (ch <= 'Z'))))
  {
    xasprintf(&t, "$%c", ch);
    return t;
  }
  buf_idx = xrealloc(buf_idx, len + 1);
  buf[len + buf_idx] = ch;
  len += 1;
  for (;;)
  {
    ch = cmd_string_getc(s, p);
    if ((ch == EOF) || (!((((ch == '_') || ((ch >= 'a') && (ch <= 'z'))) || ((ch >= 'A') && (ch <= 'Z'))) || ((ch >= '0') && (ch <= '9')))))
    {
      break;
    }
    else
    {
      if (len >= (SIZE_MAX - 3))
      {
        goto error;
      }
      buf_idx = xrealloc(buf_idx, len + 1);
      buf[len + buf_idx] = ch;
      len += 1;
    }
  }

  *ch_ref = ch;
  *buf_idx_ref = buf_idx;
  *len_ref = len;
}


/*** DEPENDENCIES:
static int cmd_string_getc(const char *s, size_t *p)
{
  const u_char *ucs = s;
  if (ucs[*p] == '\0')
  {
    return EOF;
  }
  return ucs[(*p)++];
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
void *xrealloc(void *ptr, size_t size)
{
  return xreallocarray(ptr, 1, size);
}


----------------------------
***/


static char *cmd_string_variable(const char *s, size_t *p)
{
  int ch;
  int fch;
  char *buf;
  unsigned int buf_idx = 0;
  char *t;
  size_t len;
  struct environ_entry *envent;
  unsigned int envent_idx = 0;
  buf_idx = 0;
  len = 0;
  fch = EOF;
  switch (ch = cmd_string_getc(s, p))
  {
    case EOF:
    {
      goto error;
    }

    case '{':
    {
      fch = '{';
      ch = cmd_string_getc(s, p);
      if (!(((ch == '_') || ((ch >= 'a') && (ch <= 'z'))) || ((ch >= 'A') && (ch <= 'Z'))))
      {
        goto error;
      }
    }

    default:
    {
      helper_cmd_string_variable_1(&ch, &buf_idx, &len, s, p, buf, t);
    }

  }

  if ((fch == '{') && (ch != '}'))
  {
    goto error;
  }
  if ((ch != EOF) && (fch != '{'))
  {
    cmd_string_ungetc(p);
  }
  buf_idx = xrealloc(buf_idx, len + 1);
  buf[len + buf_idx] = '\0';
  envent_idx = environ_find(global_environ, buf);
  free(buf);
  if ((&envent[envent_idx]) == 0)
  {
    return xstrdup("");
  }
  return xstrdup(envent->value);
  error:
  free(buf);

  return 0;
}


/*** DEPENDENCIES:
static void cmd_string_ungetc(size_t *p)
{
  *p -= 1;
}


----------------------------
static int cmd_string_getc(const char *s, size_t *p)
{
  const u_char *ucs = s;
  if (ucs[*p] == '\0')
  {
    return EOF;
  }
  return ucs[(*p)++];
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
struct environ_entry *environ_find(struct environ *env, const char *name)
{
  struct environ_entry envent;
  envent.name = (char *) name;
  return environ_RB_FIND(env, &envent);
}


----------------------------
char *helper_cmd_string_variable_1(int * const ch_ref, unsigned int * const buf_idx_ref, size_t * const len_ref, const char * const s, size_t * const p, char * const buf, char * const t)
{
  int ch = *ch_ref;
  unsigned int buf_idx = *buf_idx_ref;
  size_t len = *len_ref;
  if (!(((ch == '_') || ((ch >= 'a') && (ch <= 'z'))) || ((ch >= 'A') && (ch <= 'Z'))))
  {
    xasprintf(&t, "$%c", ch);
    return t;
  }
  buf_idx = xrealloc(buf_idx, len + 1);
  buf[len + buf_idx] = ch;
  len += 1;
  for (;;)
  {
    ch = cmd_string_getc(s, p);
    if ((ch == EOF) || (!((((ch == '_') || ((ch >= 'a') && (ch <= 'z'))) || ((ch >= 'A') && (ch <= 'Z'))) || ((ch >= '0') && (ch <= '9')))))
    {
      break;
    }
    else
    {
      if (len >= (SIZE_MAX - 3))
      {
        goto error;
      }
      buf_idx = xrealloc(buf_idx, len + 1);
      buf[len + buf_idx] = ch;
      len += 1;
    }
  }

  *ch_ref = ch;
  *buf_idx_ref = buf_idx;
  *len_ref = len;
}


----------------------------
void *xrealloc(void *ptr, size_t size)
{
  return xreallocarray(ptr, 1, size);
}


----------------------------
None
----------------------------
***/


// hint:  ['ch_ref is a mutable refrence to int', 'buf_idx_ref is a mutable refrence to unsigned int', 't_idx_ref is a mutable refrence to unsigned int', 'len_ref is a mutable refrence to size_t']
void helper_cmd_string_string_1(int * const ch_ref, unsigned int * const buf_idx_ref, unsigned int * const t_idx_ref, size_t * const len_ref, const char * const s, size_t * const p, int esc, char * const buf, char * const t)
{
  int ch = *ch_ref;
  unsigned int buf_idx = *buf_idx_ref;
  unsigned int t_idx = *t_idx_ref;
  size_t len = *len_ref;
  switch (ch)
  {
    case EOF:
    {
      goto error;
    }

    case '\\':
    {
      helper_helper_cmd_string_string_1_1(&ch, s, p, esc);
    }

    case '$':
    {
      if (!esc)
      {
        break;
      }
      if ((t_idx = cmd_string_variable(s, p)) == 0)
      {
        goto error;
      }
      cmd_string_copy(&(&buf[buf_idx]), t, &len);
      continue;
    }

  }

  if (len >= (SIZE_MAX - 2))
  {
    goto error;
  }
  buf_idx = xrealloc(buf_idx, len + 1);
  buf[len + buf_idx] = ch;
  len += 1;
  *ch_ref = ch;
  *buf_idx_ref = buf_idx;
  *t_idx_ref = t_idx;
  *len_ref = len;
}


/*** DEPENDENCIES:
static void cmd_string_copy(char **dst, char *src, size_t *len)
{
  size_t srclen;
  srclen = strlen(src);
  *dst = xrealloc(*dst, ((*len) + srclen) + 1);
  strlcpy((*dst) + (*len), src, srclen + 1);
  *len += srclen;
  free(src);
}


----------------------------
void helper_helper_cmd_string_string_1_1(int * const ch_ref, const char * const s, size_t * const p, int esc)
{
  int ch = *ch_ref;
  if (!esc)
  {
    break;
  }
  switch (ch = cmd_string_getc(s, p))
  {
    case EOF:
    {
      goto error;
    }

    case 'e':
    {
      ch = '\033';
      break;
    }

    case 'r':
    {
      ch = '\r';
      break;
    }

    case 'n':
    {
      ch = '\n';
      break;
    }

    case 't':
    {
      ch = '\t';
      break;
    }

  }

  break;
  *ch_ref = ch;
}


----------------------------
static char *cmd_string_variable(const char *s, size_t *p)
{
  int ch;
  int fch;
  char *buf;
  unsigned int buf_idx = 0;
  char *t;
  size_t len;
  struct environ_entry *envent;
  unsigned int envent_idx = 0;
  buf_idx = 0;
  len = 0;
  fch = EOF;
  switch (ch = cmd_string_getc(s, p))
  {
    case EOF:
    {
      goto error;
    }

    case '{':
    {
      fch = '{';
      ch = cmd_string_getc(s, p);
      if (!(((ch == '_') || ((ch >= 'a') && (ch <= 'z'))) || ((ch >= 'A') && (ch <= 'Z'))))
      {
        goto error;
      }
    }

    default:
    {
      helper_cmd_string_variable_1(&ch, &buf_idx, &len, s, p, buf, t);
    }

  }

  if ((fch == '{') && (ch != '}'))
  {
    goto error;
  }
  if ((ch != EOF) && (fch != '{'))
  {
    cmd_string_ungetc(p);
  }
  buf_idx = xrealloc(buf_idx, len + 1);
  buf[len + buf_idx] = '\0';
  envent_idx = environ_find(global_environ, buf);
  free(buf);
  if ((&envent[envent_idx]) == 0)
  {
    return xstrdup("");
  }
  return xstrdup(envent->value);
  error:
  free(buf);

  return 0;
}


----------------------------
void *xrealloc(void *ptr, size_t size)
{
  return xreallocarray(ptr, 1, size);
}


----------------------------
***/


static char *cmd_string_string(const char *s, size_t *p, char endch, int esc)
{
  int ch;
  char *buf;
  unsigned int buf_idx = 0;
  char *t;
  unsigned int t_idx = 0;
  size_t len;
  buf_idx = 0;
  len = 0;
  while ((ch = cmd_string_getc(s, p)) != endch)
  {
    helper_cmd_string_string_1(&ch, &buf_idx, &t_idx, &len, s, p, esc, buf, t);
  }

  buf_idx = xrealloc(buf_idx, len + 1);
  buf[len + buf_idx] = '\0';
  return buf;
  error:
  free(buf);

  return 0;
}


/*** DEPENDENCIES:
void *xrealloc(void *ptr, size_t size)
{
  return xreallocarray(ptr, 1, size);
}


----------------------------
void helper_cmd_string_string_1(int * const ch_ref, unsigned int * const buf_idx_ref, unsigned int * const t_idx_ref, size_t * const len_ref, const char * const s, size_t * const p, int esc, char * const buf, char * const t)
{
  int ch = *ch_ref;
  unsigned int buf_idx = *buf_idx_ref;
  unsigned int t_idx = *t_idx_ref;
  size_t len = *len_ref;
  switch (ch)
  {
    case EOF:
    {
      goto error;
    }

    case '\\':
    {
      helper_helper_cmd_string_string_1_1(&ch, s, p, esc);
    }

    case '$':
    {
      if (!esc)
      {
        break;
      }
      if ((t_idx = cmd_string_variable(s, p)) == 0)
      {
        goto error;
      }
      cmd_string_copy(&(&buf[buf_idx]), t, &len);
      continue;
    }

  }

  if (len >= (SIZE_MAX - 2))
  {
    goto error;
  }
  buf_idx = xrealloc(buf_idx, len + 1);
  buf[len + buf_idx] = ch;
  len += 1;
  *ch_ref = ch;
  *buf_idx_ref = buf_idx;
  *t_idx_ref = t_idx;
  *len_ref = len;
}


----------------------------
static int cmd_string_getc(const char *s, size_t *p)
{
  const u_char *ucs = s;
  if (ucs[*p] == '\0')
  {
    return EOF;
  }
  return ucs[(*p)++];
}


----------------------------
***/


// hint:  ['pw_idx_ref is a mutable refrence to unsigned int', 'home_idx_ref is a mutable refrence to unsigned int', 'cp_idx_ref is a mutable refrence to unsigned int', 'last_ref is a mutable refrence to int']
void helper_cmd_string_expand_tilde_1(unsigned int * const pw_idx_ref, unsigned int * const home_idx_ref, unsigned int * const cp_idx_ref, int * const last_ref, const char * const s, size_t * const p, struct passwd * const pw, char * const user, char * const cp)
{
  unsigned int pw_idx = *pw_idx_ref;
  unsigned int home_idx = *home_idx_ref;
  unsigned int cp_idx = *cp_idx_ref;
  int last = *last_ref;
  cmd_string_ungetc(p);
  cp_idx = (user = xmalloc(strlen(s)));
  for (;;)
  {
    last = cmd_string_getc(s, p);
    if ((((last == EOF) || (last == '/')) || (last == ' ')) || (last == '\t'))
    {
      break;
    }
    cp[cp_idx] = last;
    cp_idx += 1;
  }

  cp[cp_idx] = '\0';
  if ((pw_idx = getpwnam(user)) != 0)
  {
    home_idx = pw->pw_dir;
  }
  free(user);
  *pw_idx_ref = pw_idx;
  *home_idx_ref = home_idx;
  *cp_idx_ref = cp_idx;
  *last_ref = last;
}


/*** DEPENDENCIES:
static void cmd_string_ungetc(size_t *p)
{
  *p -= 1;
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
static int cmd_string_getc(const char *s, size_t *p)
{
  const u_char *ucs = s;
  if (ucs[*p] == '\0')
  {
    return EOF;
  }
  return ucs[(*p)++];
}


----------------------------
***/


static char *cmd_string_expand_tilde(const char *s, size_t *p)
{
  struct passwd *pw;
  unsigned int pw_idx = 0;
  struct environ_entry *envent;
  unsigned int envent_idx = 0;
  char *home;
  unsigned int home_idx = 0;
  char *path;
  char *user;
  char *cp;
  unsigned int cp_idx = 0;
  int last;
  home_idx = 0;
  last = cmd_string_getc(s, p);
  if ((((last == EOF) || (last == '/')) || (last == ' ')) || (last == '\t'))
  {
    envent_idx = environ_find(global_environ, "HOME");
    if (((&envent[envent_idx]) != 0) && ((*envent->value) != '\0'))
    {
      home_idx = envent->value;
    }
    else
      if ((pw_idx = getpwuid(getuid())) != 0)
    {
      home_idx = pw->pw_dir;
    }
  }
  else
  {
    helper_cmd_string_expand_tilde_1(&pw_idx, &home_idx, &cp_idx, &last, s, p, pw, user, cp);
  }
  if ((&home[home_idx]) == 0)
  {
    return 0;
  }
  if (last != EOF)
  {
    xasprintf(&path, "%s%c", home, last);
  }
  else
    xasprintf(&path, "%s", home);
  return path;
}


/*** DEPENDENCIES:
void helper_cmd_string_expand_tilde_1(unsigned int * const pw_idx_ref, unsigned int * const home_idx_ref, unsigned int * const cp_idx_ref, int * const last_ref, const char * const s, size_t * const p, struct passwd * const pw, char * const user, char * const cp)
{
  unsigned int pw_idx = *pw_idx_ref;
  unsigned int home_idx = *home_idx_ref;
  unsigned int cp_idx = *cp_idx_ref;
  int last = *last_ref;
  cmd_string_ungetc(p);
  cp_idx = (user = xmalloc(strlen(s)));
  for (;;)
  {
    last = cmd_string_getc(s, p);
    if ((((last == EOF) || (last == '/')) || (last == ' ')) || (last == '\t'))
    {
      break;
    }
    cp[cp_idx] = last;
    cp_idx += 1;
  }

  cp[cp_idx] = '\0';
  if ((pw_idx = getpwnam(user)) != 0)
  {
    home_idx = pw->pw_dir;
  }
  free(user);
  *pw_idx_ref = pw_idx;
  *home_idx_ref = home_idx;
  *cp_idx_ref = cp_idx;
  *last_ref = last;
}


----------------------------
struct environ_entry *environ_find(struct environ *env, const char *name)
{
  struct environ_entry envent;
  envent.name = (char *) name;
  return environ_RB_FIND(env, &envent);
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
static int cmd_string_getc(const char *s, size_t *p)
{
  const u_char *ucs = s;
  if (ucs[*p] == '\0')
  {
    return EOF;
  }
  return ucs[(*p)++];
}


----------------------------
None
----------------------------
***/


// hint:  ['ch_ref is a mutable refrence to int', 'argc_ref is a mutable refrence to int', 'append_ref is a mutable refrence to int', 'argv_idx_ref is a mutable refrence to unsigned int', 'buf_idx_ref is a mutable refrence to unsigned int', 't_idx_ref is a mutable refrence to unsigned int', 'whitespace_idx_ref is a mutable refrence to unsigned int', 'equals_idx_ref is a mutable refrence to unsigned int', 'len_ref is a mutable refrence to size_t']
void helper_cmd_string_split_1(int * const ch_ref, int * const argc_ref, int * const append_ref, unsigned int * const argv_idx_ref, unsigned int * const buf_idx_ref, unsigned int * const t_idx_ref, unsigned int * const whitespace_idx_ref, unsigned int * const equals_idx_ref, size_t * const len_ref, const char * const s, size_t p, char ** const argv, char * const buf, char * const t, const char * const whitespace, const char * const equals)
{
  int ch = *ch_ref;
  int argc = *argc_ref;
  int append = *append_ref;
  unsigned int argv_idx = *argv_idx_ref;
  unsigned int buf_idx = *buf_idx_ref;
  unsigned int t_idx = *t_idx_ref;
  unsigned int whitespace_idx = *whitespace_idx_ref;
  unsigned int equals_idx = *equals_idx_ref;
  size_t len = *len_ref;
  ch = cmd_string_getc(s, &p);
  switch (ch)
  {
    case '\'':
    {
      if ((t_idx = cmd_string_string(s, &p, '\'', 0)) == 0)
      {
        goto error;
      }
      cmd_string_copy(&(&buf[buf_idx]), t, &len);
      break;
    }

    case '"':
    {
      if ((t_idx = cmd_string_string(s, &p, '"', 1)) == 0)
      {
        goto error;
      }
      cmd_string_copy(&(&buf[buf_idx]), t, &len);
      break;
    }

    case '$':
    {
      if ((t_idx = cmd_string_variable(s, &p)) == 0)
      {
        goto error;
      }
      cmd_string_copy(&(&buf[buf_idx]), t, &len);
      break;
    }

    case '#':
    {
      while ((ch = cmd_string_getc(s, &p)) != EOF)
      {
        ;
      }

    }

    case EOF:

    case ' ':

    case '\t':
    {
      helper_helper_cmd_string_split_1_1(&argc, &argv_idx, &buf_idx, &whitespace_idx, &equals_idx, &len, argv, buf, whitespace, equals, ch);
    }

    case '~':
    {
      if ((&buf[buf_idx]) != 0)
      {
        append = 1;
        break;
      }
      t_idx = cmd_string_expand_tilde(s, &p);
      if ((&t[t_idx]) == 0)
      {
        goto error;
      }
      cmd_string_copy(&(&buf[buf_idx]), t, &len);
      break;
    }

    default:
    {
      append = 1;
      break;
    }

  }

  if (append)
  {
    if (len >= (SIZE_MAX - 2))
    {
      goto error;
    }
    buf_idx = xrealloc(buf_idx, len + 1);
    buf[len + buf_idx] = ch;
    len += 1;
  }
  append = 0;
  *ch_ref = ch;
  *argc_ref = argc;
  *append_ref = append;
  *argv_idx_ref = argv_idx;
  *buf_idx_ref = buf_idx;
  *t_idx_ref = t_idx;
  *whitespace_idx_ref = whitespace_idx;
  *equals_idx_ref = equals_idx;
  *len_ref = len;
}


/*** DEPENDENCIES:
void helper_helper_cmd_string_split_1_1(int * const argc_ref, unsigned int * const argv_idx_ref, unsigned int * const buf_idx_ref, unsigned int * const whitespace_idx_ref, unsigned int * const equals_idx_ref, size_t * const len_ref, char ** const argv, char * const buf, const char * const whitespace, const char * const equals, int ch)
{
  int argc = *argc_ref;
  unsigned int argv_idx = *argv_idx_ref;
  unsigned int buf_idx = *buf_idx_ref;
  unsigned int whitespace_idx = *whitespace_idx_ref;
  unsigned int equals_idx = *equals_idx_ref;
  size_t len = *len_ref;
  if ((&buf[buf_idx]) != 0)
  {
    buf_idx = xrealloc(buf_idx, len + 1);
    buf[len + buf_idx] = '\0';
    argv_idx = xreallocarray(argv_idx, argc + 1, sizeof(*argv_idx));
    argv[argc + argv_idx] = &buf[buf_idx];
    argc += 1;
    buf_idx = 0;
    len = 0;
  }
  if (ch != EOF)
  {
    break;
  }
  while (argc != 0)
  {
    equals_idx = strchr(argv[0 + argv_idx], '=');
    whitespace_idx = argv[0 + argv_idx] + strcspn(argv[0 + argv_idx], " \t");
    if (((&equals[equals_idx]) == 0) || ((&equals[equals_idx]) > (&whitespace[whitespace_idx])))
    {
      break;
    }
    environ_put(global_environ, argv[0 + argv_idx]);
    argc -= 1;
    memmove(argv, (&argv[argv_idx]) + 1, argc * (sizeof(*(&argv[argv_idx]))));
  }

  goto done;
  *argc_ref = argc;
  *argv_idx_ref = argv_idx;
  *buf_idx_ref = buf_idx;
  *whitespace_idx_ref = whitespace_idx;
  *equals_idx_ref = equals_idx;
  *len_ref = len;
}


----------------------------
static char *cmd_string_string(const char *s, size_t *p, char endch, int esc)
{
  int ch;
  char *buf;
  unsigned int buf_idx = 0;
  char *t;
  unsigned int t_idx = 0;
  size_t len;
  buf_idx = 0;
  len = 0;
  while ((ch = cmd_string_getc(s, p)) != endch)
  {
    helper_cmd_string_string_1(&ch, &buf_idx, &t_idx, &len, s, p, esc, buf, t);
  }

  buf_idx = xrealloc(buf_idx, len + 1);
  buf[len + buf_idx] = '\0';
  return buf;
  error:
  free(buf);

  return 0;
}


----------------------------
static void cmd_string_copy(char **dst, char *src, size_t *len)
{
  size_t srclen;
  srclen = strlen(src);
  *dst = xrealloc(*dst, ((*len) + srclen) + 1);
  strlcpy((*dst) + (*len), src, srclen + 1);
  *len += srclen;
  free(src);
}


----------------------------
static char *cmd_string_expand_tilde(const char *s, size_t *p)
{
  struct passwd *pw;
  unsigned int pw_idx = 0;
  struct environ_entry *envent;
  unsigned int envent_idx = 0;
  char *home;
  unsigned int home_idx = 0;
  char *path;
  char *user;
  char *cp;
  unsigned int cp_idx = 0;
  int last;
  home_idx = 0;
  last = cmd_string_getc(s, p);
  if ((((last == EOF) || (last == '/')) || (last == ' ')) || (last == '\t'))
  {
    envent_idx = environ_find(global_environ, "HOME");
    if (((&envent[envent_idx]) != 0) && ((*envent->value) != '\0'))
    {
      home_idx = envent->value;
    }
    else
      if ((pw_idx = getpwuid(getuid())) != 0)
    {
      home_idx = pw->pw_dir;
    }
  }
  else
  {
    helper_cmd_string_expand_tilde_1(&pw_idx, &home_idx, &cp_idx, &last, s, p, pw, user, cp);
  }
  if ((&home[home_idx]) == 0)
  {
    return 0;
  }
  if (last != EOF)
  {
    xasprintf(&path, "%s%c", home, last);
  }
  else
    xasprintf(&path, "%s", home);
  return path;
}


----------------------------
static int cmd_string_getc(const char *s, size_t *p)
{
  const u_char *ucs = s;
  if (ucs[*p] == '\0')
  {
    return EOF;
  }
  return ucs[(*p)++];
}


----------------------------
static char *cmd_string_variable(const char *s, size_t *p)
{
  int ch;
  int fch;
  char *buf;
  unsigned int buf_idx = 0;
  char *t;
  size_t len;
  struct environ_entry *envent;
  unsigned int envent_idx = 0;
  buf_idx = 0;
  len = 0;
  fch = EOF;
  switch (ch = cmd_string_getc(s, p))
  {
    case EOF:
    {
      goto error;
    }

    case '{':
    {
      fch = '{';
      ch = cmd_string_getc(s, p);
      if (!(((ch == '_') || ((ch >= 'a') && (ch <= 'z'))) || ((ch >= 'A') && (ch <= 'Z'))))
      {
        goto error;
      }
    }

    default:
    {
      helper_cmd_string_variable_1(&ch, &buf_idx, &len, s, p, buf, t);
    }

  }

  if ((fch == '{') && (ch != '}'))
  {
    goto error;
  }
  if ((ch != EOF) && (fch != '{'))
  {
    cmd_string_ungetc(p);
  }
  buf_idx = xrealloc(buf_idx, len + 1);
  buf[len + buf_idx] = '\0';
  envent_idx = environ_find(global_environ, buf);
  free(buf);
  if ((&envent[envent_idx]) == 0)
  {
    return xstrdup("");
  }
  return xstrdup(envent->value);
  error:
  free(buf);

  return 0;
}


----------------------------
void *xrealloc(void *ptr, size_t size)
{
  return xreallocarray(ptr, 1, size);
}


----------------------------
***/


int cmd_string_split(const char *s, int *rargc, char ***rargv)
{
  size_t p = 0;
  int ch;
  int argc = 0;
  int append = 0;
  char **argv = 0;
  unsigned int argv_idx = 0;
  char *buf = 0;
  unsigned int buf_idx = 0;
  char *t;
  unsigned int t_idx = 0;
  const char *whitespace;
  unsigned int whitespace_idx = 0;
  const char *equals;
  unsigned int equals_idx = 0;
  size_t len = 0;
  for (;;)
  {
    helper_cmd_string_split_1(&ch, &argc, &append, &argv_idx, &buf_idx, &t_idx, &whitespace_idx, &equals_idx, &len, s, p, argv, buf, t, whitespace, equals);
  }

  done:
  *rargc = argc;

  *rargv = &argv[argv_idx];
  free(buf);
  return 0;
  error:
  if ((&argv[argv_idx]) != 0)
  {
    cmd_free_argv(argc, argv);
  }

  free(buf);
  return -1;
}


/*** DEPENDENCIES:
void helper_cmd_string_split_1(int * const ch_ref, int * const argc_ref, int * const append_ref, unsigned int * const argv_idx_ref, unsigned int * const buf_idx_ref, unsigned int * const t_idx_ref, unsigned int * const whitespace_idx_ref, unsigned int * const equals_idx_ref, size_t * const len_ref, const char * const s, size_t p, char ** const argv, char * const buf, char * const t, const char * const whitespace, const char * const equals)
{
  int ch = *ch_ref;
  int argc = *argc_ref;
  int append = *append_ref;
  unsigned int argv_idx = *argv_idx_ref;
  unsigned int buf_idx = *buf_idx_ref;
  unsigned int t_idx = *t_idx_ref;
  unsigned int whitespace_idx = *whitespace_idx_ref;
  unsigned int equals_idx = *equals_idx_ref;
  size_t len = *len_ref;
  ch = cmd_string_getc(s, &p);
  switch (ch)
  {
    case '\'':
    {
      if ((t_idx = cmd_string_string(s, &p, '\'', 0)) == 0)
      {
        goto error;
      }
      cmd_string_copy(&(&buf[buf_idx]), t, &len);
      break;
    }

    case '"':
    {
      if ((t_idx = cmd_string_string(s, &p, '"', 1)) == 0)
      {
        goto error;
      }
      cmd_string_copy(&(&buf[buf_idx]), t, &len);
      break;
    }

    case '$':
    {
      if ((t_idx = cmd_string_variable(s, &p)) == 0)
      {
        goto error;
      }
      cmd_string_copy(&(&buf[buf_idx]), t, &len);
      break;
    }

    case '#':
    {
      while ((ch = cmd_string_getc(s, &p)) != EOF)
      {
        ;
      }

    }

    case EOF:

    case ' ':

    case '\t':
    {
      helper_helper_cmd_string_split_1_1(&argc, &argv_idx, &buf_idx, &whitespace_idx, &equals_idx, &len, argv, buf, whitespace, equals, ch);
    }

    case '~':
    {
      if ((&buf[buf_idx]) != 0)
      {
        append = 1;
        break;
      }
      t_idx = cmd_string_expand_tilde(s, &p);
      if ((&t[t_idx]) == 0)
      {
        goto error;
      }
      cmd_string_copy(&(&buf[buf_idx]), t, &len);
      break;
    }

    default:
    {
      append = 1;
      break;
    }

  }

  if (append)
  {
    if (len >= (SIZE_MAX - 2))
    {
      goto error;
    }
    buf_idx = xrealloc(buf_idx, len + 1);
    buf[len + buf_idx] = ch;
    len += 1;
  }
  append = 0;
  *ch_ref = ch;
  *argc_ref = argc;
  *append_ref = append;
  *argv_idx_ref = argv_idx;
  *buf_idx_ref = buf_idx;
  *t_idx_ref = t_idx;
  *whitespace_idx_ref = whitespace_idx;
  *equals_idx_ref = equals_idx;
  *len_ref = len;
}


----------------------------
void cmd_free_argv(int argc, char **argv)
{
  int i;
  if (argc == 0)
  {
    return;
  }
  for (i = 0; i < argc; i += 1)
  {
    free(argv[i]);
  }

  free(argv);
}


----------------------------
***/


struct cmd_list *cmd_string_parse(const char *s, const char *file, u_int line, char **cause)
{
  struct cmd_list *cmdlist = 0;
  unsigned int cmdlist_idx = 0;
  int argc;
  char **argv;
  *cause = 0;
  if (cmd_string_split(s, &argc, &argv) != 0)
  {
    xasprintf(cause, "invalid or unknown command: %s", s);
    return 0;
  }
  if (argc != 0)
  {
    cmdlist_idx = cmd_list_parse(argc, argv, file, line, cause);
    if ((&cmdlist[cmdlist_idx]) == 0)
    {
      cmd_free_argv(argc, argv);
      return 0;
    }
  }
  cmd_free_argv(argc, argv);
  return cmdlist;
}


/*** DEPENDENCIES:
struct cmd_list *cmd_list_parse(int argc, char **argv, const char *file, u_int line, char **cause)
{
  struct cmd_list *cmdlist;
  unsigned int cmdlist_idx = 0;
  struct cmd *cmd;
  unsigned int cmd_idx = 0;
  int i;
  int lastsplit;
  size_t arglen;
  size_t new_argc;
  char **copy_argv;
  unsigned int copy_argv_idx = 0;
  char **new_argv;
  unsigned int new_argv_idx = 0;
  copy_argv_idx = cmd_copy_argv(argc, argv);
  cmdlist_idx = xcalloc(1, sizeof(*cmdlist_idx));
  cmdlist->references = 1;
  do
  {
    (&cmdlist->list)->tqh_first = 0;
    (&cmdlist->list)->tqh_last = &(&cmdlist->list)->tqh_first;
  }
  while (0);
  lastsplit = 0;
  for (i = 0; i < argc; i += 1)
  {
    helper_cmd_list_parse_1(&cmd_idx, &i, &lastsplit, &arglen, &new_argc, &copy_argv_idx, &new_argv_idx, file, line, cause, cmdlist, cmd, copy_argv, new_argv);
  }

  if (lastsplit != argc)
  {
    cmd_idx = cmd_parse(argc - lastsplit, (&copy_argv[copy_argv_idx]) + lastsplit, file, line, cause);
    if ((&cmd[cmd_idx]) == 0)
    {
      goto bad;
    }
    do
    {
      cmd->qentry.tqe_next = 0;
      cmd->qentry.tqe_prev = (&cmdlist->list)->tqh_last;
      *(&cmdlist->list)->tqh_last = &cmd[cmd_idx];
      (&cmdlist->list)->tqh_last = &cmd->qentry.tqe_next;
    }
    while (0);
  }
  cmd_free_argv(argc, copy_argv);
  return cmdlist;
  bad:
  cmd_list_free(cmdlist);

  cmd_free_argv(argc, copy_argv);
  return 0;
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
int cmd_string_split(const char *s, int *rargc, char ***rargv)
{
  size_t p = 0;
  int ch;
  int argc = 0;
  int append = 0;
  char **argv = 0;
  unsigned int argv_idx = 0;
  char *buf = 0;
  unsigned int buf_idx = 0;
  char *t;
  unsigned int t_idx = 0;
  const char *whitespace;
  unsigned int whitespace_idx = 0;
  const char *equals;
  unsigned int equals_idx = 0;
  size_t len = 0;
  for (;;)
  {
    helper_cmd_string_split_1(&ch, &argc, &append, &argv_idx, &buf_idx, &t_idx, &whitespace_idx, &equals_idx, &len, s, p, argv, buf, t, whitespace, equals);
  }

  done:
  *rargc = argc;

  *rargv = &argv[argv_idx];
  free(buf);
  return 0;
  error:
  if ((&argv[argv_idx]) != 0)
  {
    cmd_free_argv(argc, argv);
  }

  free(buf);
  return -1;
}


----------------------------
void cmd_free_argv(int argc, char **argv)
{
  int i;
  if (argc == 0)
  {
    return;
  }
  for (i = 0; i < argc; i += 1)
  {
    free(argv[i]);
  }

  free(argv);
}


----------------------------
None
----------------------------
***/


