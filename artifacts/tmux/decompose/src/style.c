const char *style_tostring(struct grid_cell *gc)
{
  int off = 0;
  int comma = 0;
  static char s[256];
  *s = '\0';
  if (gc->fg != 8)
  {
    off += xsnprintf(s, sizeof(s), "fg=%s", colour_tostring(gc->fg));
    comma = 1;
  }
  if (gc->bg != 8)
  {
    off += xsnprintf(s + off, (sizeof(s)) - off, "%sbg=%s", (comma) ? (",") : (""), colour_tostring(gc->bg));
    comma = 1;
  }
  if ((gc->attr != 0) && (gc->attr != 0x80))
  {
    xsnprintf(s + off, (sizeof(s)) - off, "%s%s", (comma) ? (",") : (""), attributes_tostring(gc->attr));
  }
  if ((*s) == '\0')
  {
    return "default";
  }
  return s;
}


/*** DEPENDENCIES:
const char *colour_tostring(int c)
{
  static char s[32];
  u_char r;
  u_char g;
  u_char b;
  if (c & 0x02000000)
  {
    colour_split_rgb(c, &r, &g, &b);
    xsnprintf(s, sizeof(s), "#%02x%02x%02x", r, g, b);
    return s;
  }
  if (c & 0x01000000)
  {
    xsnprintf(s, sizeof(s), "colour%u", c & 0xff);
    return s;
  }
  switch (c)
  {
    case 0:
    {
      return "black";
    }

    case 1:
    {
      return "red";
    }

    case 2:
    {
      return "green";
    }

    case 3:
    {
      return "yellow";
    }

    case 4:
    {
      return "blue";
    }

    case 5:
    {
      return "magenta";
    }

    case 6:
    {
      return "cyan";
    }

    case 7:
    {
      return "white";
    }

    case 8:
    {
      return "default";
    }

    case 90:
    {
      return "brightblack";
    }

    case 91:
    {
      return "brightred";
    }

    case 92:
    {
      return "brightgreen";
    }

    case 93:
    {
      return "brightyellow";
    }

    case 94:
    {
      return "brightblue";
    }

    case 95:
    {
      return "brightmagenta";
    }

    case 96:
    {
      return "brightcyan";
    }

    case 97:
    {
      return "brightwhite";
    }

  }

  return 0;
}


----------------------------
int xsnprintf(char *str, size_t len, const char *fmt, ...)
{
  va_list ap;
  int i;
  __builtin_va_start(ap);
  i = xvsnprintf(str, len, fmt, ap);
  ;
  return i;
}


----------------------------
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
const char *attributes_tostring(int attr)
{
  static char buf[128];
  size_t len;
  if (attr == 0)
  {
    return "none";
  }
  len = xsnprintf(buf, sizeof(buf), "%s%s%s%s%s%s%s%s", (attr & 0x1) ? ("bright,") : (""), (attr & 0x2) ? ("dim,") : (""), (attr & 0x4) ? ("underscore,") : (""), (attr & 0x8) ? ("blink,") : (""), (attr & 0x10) ? ("reverse,") : (""), (attr & 0x20) ? ("hidden,") : (""), (attr & 0x40) ? ("italics,") : (""), (attr & 0x100) ? ("strikethrough,") : (""));
  if (len > 0)
  {
    buf[len - 1] = '\0';
  }
  return buf;
}


----------------------------
None
----------------------------
***/


// hint:  ['in_idx_ref is a mutable refrence to unsigned int', 'val_ref is a mutable refrence to int', 'fg_ref is a mutable refrence to int', 'bg_ref is a mutable refrence to int', 'attr_ref is a mutable refrence to int', 'flags_ref is a mutable refrence to int', 'end_ref is a mutable refrence to size_t']
void helper_style_parse_1(unsigned int * const in_idx_ref, int * const val_ref, int * const fg_ref, int * const bg_ref, int * const attr_ref, int * const flags_ref, size_t * const end_ref, const struct grid_cell * const defgc, const char * const in, const char delimiters[], char tmp[32])
{
  unsigned int in_idx = *in_idx_ref;
  int val = *val_ref;
  int fg = *fg_ref;
  int bg = *bg_ref;
  int attr = *attr_ref;
  int flags = *flags_ref;
  size_t end = *end_ref;
  end = strcspn(in, delimiters);
  if (end > ((sizeof(tmp)) - 1))
  {
    goto error;
  }
  memcpy(tmp, in, end);
  tmp[end] = '\0';
  if (strcasecmp(tmp, "default") == 0)
  {
    fg = defgc->fg;
    bg = defgc->bg;
    attr = defgc->attr;
    flags = defgc->flags;
  }
  else
    if ((end > 3) && (strncasecmp(tmp + 1, "g=", 2) == 0))
  {
    if ((val = colour_fromstring(tmp + 3)) == (-1))
    {
      goto error;
    }
    if ((in[in_idx] == 'f') || (in[in_idx] == 'F'))
    {
      if (val != 8)
      {
        fg = val;
      }
      else
        fg = defgc->fg;
    }
    else
      if ((in[in_idx] == 'b') || (in[in_idx] == 'B'))
    {
      if (val != 8)
      {
        bg = val;
      }
      else
        bg = defgc->bg;
    }
    else
      goto error;
  }
  else
    if (strcasecmp(tmp, "none") == 0)
  {
    attr = 0;
  }
  else
    if ((end > 2) && (strncasecmp(tmp, "no", 2) == 0))
  {
    if ((val = attributes_fromstring(tmp + 2)) == (-1))
    {
      goto error;
    }
    attr &= ~val;
  }
  else
  {
    if ((val = attributes_fromstring(tmp)) == (-1))
    {
      goto error;
    }
    attr |= val;
  }
  in_idx += end + strspn(in_idx + end, delimiters);
  *in_idx_ref = in_idx;
  *val_ref = val;
  *fg_ref = fg;
  *bg_ref = bg;
  *attr_ref = attr;
  *flags_ref = flags;
  *end_ref = end;
}


/*** DEPENDENCIES:
int colour_fromstring(const char *s)
{
  const char *errstr;
  const char *cp;
  unsigned int cp_idx = 0;
  int n;
  u_char r;
  u_char g;
  u_char b;
  if (((*s) == '#') && (strlen(s) == 7))
  {
    for (cp_idx = s + 1; isxdigit((u_char) cp[cp_idx]); cp_idx += 1)
    {
      ;
    }

    if (cp[cp_idx] != '\0')
    {
      return -1;
    }
    n = sscanf(s + 1, "%2hhx%2hhx%2hhx", &r, &g, &b);
    if (n != 3)
    {
      return -1;
    }
    return colour_join_rgb(r, g, b);
  }
  if (strncasecmp(s, "colour", (sizeof("colour")) - 1) == 0)
  {
    n = strtonum((s + (sizeof("colour"))) - 1, 0, 255, &errstr);
    if (errstr != 0)
    {
      return -1;
    }
    return n | 0x01000000;
  }
  if ((strcasecmp(s, "black") == 0) || (strcmp(s, "0") == 0))
  {
    return 0;
  }
  if ((strcasecmp(s, "red") == 0) || (strcmp(s, "1") == 0))
  {
    return 1;
  }
  if ((strcasecmp(s, "green") == 0) || (strcmp(s, "2") == 0))
  {
    return 2;
  }
  if ((strcasecmp(s, "yellow") == 0) || (strcmp(s, "3") == 0))
  {
    return 3;
  }
  if ((strcasecmp(s, "blue") == 0) || (strcmp(s, "4") == 0))
  {
    return 4;
  }
  if ((strcasecmp(s, "magenta") == 0) || (strcmp(s, "5") == 0))
  {
    return 5;
  }
  if ((strcasecmp(s, "cyan") == 0) || (strcmp(s, "6") == 0))
  {
    return 6;
  }
  if ((strcasecmp(s, "white") == 0) || (strcmp(s, "7") == 0))
  {
    return 7;
  }
  if ((strcasecmp(s, "default") == 0) || (strcmp(s, "8") == 0))
  {
    return 8;
  }
  if ((strcasecmp(s, "brightblack") == 0) || (strcmp(s, "90") == 0))
  {
    return 90;
  }
  if ((strcasecmp(s, "brightred") == 0) || (strcmp(s, "91") == 0))
  {
    return 91;
  }
  if ((strcasecmp(s, "brightgreen") == 0) || (strcmp(s, "92") == 0))
  {
    return 92;
  }
  if ((strcasecmp(s, "brightyellow") == 0) || (strcmp(s, "93") == 0))
  {
    return 93;
  }
  if ((strcasecmp(s, "brightblue") == 0) || (strcmp(s, "94") == 0))
  {
    return 94;
  }
  if ((strcasecmp(s, "brightmagenta") == 0) || (strcmp(s, "95") == 0))
  {
    return 95;
  }
  if ((strcasecmp(s, "brightcyan") == 0) || (strcmp(s, "96") == 0))
  {
    return 96;
  }
  if ((strcasecmp(s, "brightwhite") == 0) || (strcmp(s, "97") == 0))
  {
    return 97;
  }
  return -1;
}


----------------------------
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
int attributes_fromstring(const char *str)
{
  unsigned int str_idx = 0;
  const char delimiters[] = " ,|";
  int attr;
  size_t end;
  if ((str[str_idx] == '\0') || (strcspn(str, delimiters) == 0))
  {
    return -1;
  }
  if (strchr(delimiters, str[(strlen(str) - 1) + str_idx]) != 0)
  {
    return -1;
  }
  if ((strcasecmp(str, "default") == 0) || (strcasecmp(str, "none") == 0))
  {
    return 0;
  }
  attr = 0;
  do
  {
    end = strcspn(str, delimiters);
    if (((end == 6) && (strncasecmp(str, "bright", end) == 0)) || ((end == 4) && (strncasecmp(str, "bold", end) == 0)))
    {
      attr |= 0x1;
    }
    else
      if ((end == 3) && (strncasecmp(str, "dim", end) == 0))
    {
      attr |= 0x2;
    }
    else
      if ((end == 10) && (strncasecmp(str, "underscore", end) == 0))
    {
      attr |= 0x4;
    }
    else
      if ((end == 5) && (strncasecmp(str, "blink", end) == 0))
    {
      attr |= 0x8;
    }
    else
      if ((end == 7) && (strncasecmp(str, "reverse", end) == 0))
    {
      attr |= 0x10;
    }
    else
      if ((end == 6) && (strncasecmp(str, "hidden", end) == 0))
    {
      attr |= 0x20;
    }
    else
      if ((end == 7) && (strncasecmp(str, "italics", end) == 0))
    {
      attr |= 0x40;
    }
    else
      if ((end == 13) && (strncasecmp(str, "strikethrough", end) == 0))
    {
      attr |= 0x100;
    }
    else
      return -1;
    str_idx += end + strspn(str_idx + end, delimiters);
  }
  while (str[str_idx] != '\0');
  return attr;
}


----------------------------
None
----------------------------
***/


int style_parse(const struct grid_cell *defgc, struct grid_cell *gc, const char *in)
{
  unsigned int in_idx = 0;
  struct grid_cell savedgc;
  const char delimiters[] = " ,";
  char tmp[32];
  int val;
  int fg;
  int bg;
  int attr;
  int flags;
  size_t end;
  if (in[in_idx] == '\0')
  {
    return 0;
  }
  if (strchr(delimiters, in[(strlen(in) - 1) + in_idx]) != 0)
  {
    return -1;
  }
  memcpy(&savedgc, gc, sizeof(savedgc));
  fg = gc->fg;
  bg = gc->bg;
  attr = gc->attr;
  flags = gc->flags;
  do
  {
    helper_style_parse_1(&in_idx, &val, &fg, &bg, &attr, &flags, &end, defgc, in, delimiters, tmp);
  }
  while (in[in_idx] != '\0');
  gc->fg = fg;
  gc->bg = bg;
  gc->attr = attr;
  gc->flags = flags;
  return 0;
  error:
  memcpy(gc, &savedgc, sizeof(*gc));

  return -1;
}


/*** DEPENDENCIES:
void helper_style_parse_1(unsigned int * const in_idx_ref, int * const val_ref, int * const fg_ref, int * const bg_ref, int * const attr_ref, int * const flags_ref, size_t * const end_ref, const struct grid_cell * const defgc, const char * const in, const char delimiters[], char tmp[32])
{
  unsigned int in_idx = *in_idx_ref;
  int val = *val_ref;
  int fg = *fg_ref;
  int bg = *bg_ref;
  int attr = *attr_ref;
  int flags = *flags_ref;
  size_t end = *end_ref;
  end = strcspn(in, delimiters);
  if (end > ((sizeof(tmp)) - 1))
  {
    goto error;
  }
  memcpy(tmp, in, end);
  tmp[end] = '\0';
  if (strcasecmp(tmp, "default") == 0)
  {
    fg = defgc->fg;
    bg = defgc->bg;
    attr = defgc->attr;
    flags = defgc->flags;
  }
  else
    if ((end > 3) && (strncasecmp(tmp + 1, "g=", 2) == 0))
  {
    if ((val = colour_fromstring(tmp + 3)) == (-1))
    {
      goto error;
    }
    if ((in[in_idx] == 'f') || (in[in_idx] == 'F'))
    {
      if (val != 8)
      {
        fg = val;
      }
      else
        fg = defgc->fg;
    }
    else
      if ((in[in_idx] == 'b') || (in[in_idx] == 'B'))
    {
      if (val != 8)
      {
        bg = val;
      }
      else
        bg = defgc->bg;
    }
    else
      goto error;
  }
  else
    if (strcasecmp(tmp, "none") == 0)
  {
    attr = 0;
  }
  else
    if ((end > 2) && (strncasecmp(tmp, "no", 2) == 0))
  {
    if ((val = attributes_fromstring(tmp + 2)) == (-1))
    {
      goto error;
    }
    attr &= ~val;
  }
  else
  {
    if ((val = attributes_fromstring(tmp)) == (-1))
    {
      goto error;
    }
    attr |= val;
  }
  in_idx += end + strspn(in_idx + end, delimiters);
  *in_idx_ref = in_idx;
  *val_ref = val;
  *fg_ref = fg;
  *bg_ref = bg;
  *attr_ref = attr;
  *flags_ref = flags;
  *end_ref = end;
}


----------------------------
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
None
----------------------------
***/


int style_equal(const struct grid_cell *gc1, const struct grid_cell *gc2)
{
  return (((gc1->fg == gc2->fg) && (gc1->bg == gc2->bg)) && ((gc1->flags & (~0x4)) == (gc2->flags & (~0x4)))) && ((gc1->attr & (~0x80)) == (gc2->attr & (~0x80)));
}


/*** DEPENDENCIES:
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
None
----------------------------
***/


void style_apply(struct grid_cell *gc, struct options *oo, const char *name)
{
  const struct grid_cell *gcp;
  unsigned int gcp_idx = 0;
  memcpy(gc, &grid_default_cell, sizeof(*gc));
  gcp_idx = options_get_style(oo, name);
  gc->fg = gcp->fg;
  gc->bg = gcp->bg;
  gc->attr |= gcp->attr;
}


/*** DEPENDENCIES:
const struct grid_cell *options_get_style(struct options *oo, const char *name)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_get(oo, name);
  if ((&o[o_idx]) == 0)
  {
    fatalx("missing option %s", name);
  }
  if (!((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_STYLE)))
  {
    fatalx("option %s is not a style", name);
  }
  return &o->style;
}


----------------------------
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
extern const struct grid_cell grid_default_cell
----------------------------
None
----------------------------
None
----------------------------
***/


void style_apply_update(struct grid_cell *gc, struct options *oo, const char *name)
{
  const struct grid_cell *gcp;
  unsigned int gcp_idx = 0;
  gcp_idx = options_get_style(oo, name);
  if (gcp->fg != 8)
  {
    gc->fg = gcp->fg;
  }
  if (gcp->bg != 8)
  {
    gc->bg = gcp->bg;
  }
  if (gcp->attr != 0)
  {
    gc->attr |= gcp->attr;
  }
}


/*** DEPENDENCIES:
const struct grid_cell *options_get_style(struct options *oo, const char *name)
{
  struct options_entry *o;
  unsigned int o_idx = 0;
  o_idx = options_get(oo, name);
  if ((&o[o_idx]) == 0)
  {
    fatalx("missing option %s", name);
  }
  if (!((o->tableentry != 0) && (o->tableentry->type == OPTIONS_TABLE_STYLE)))
  {
    fatalx("option %s is not a style", name);
  }
  return &o->style;
}


----------------------------
struct grid_cell
{
  u_char flags;
  u_short attr;
  int fg;
  int bg;
  struct utf8_data data;
}
----------------------------
None
----------------------------
None
----------------------------
***/


