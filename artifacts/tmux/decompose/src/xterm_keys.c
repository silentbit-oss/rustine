static int xterm_keys_modifiers(const char *buf, size_t len, size_t *pos, key_code *modifiers)
{
  u_int flags;
  if ((len - (*pos)) < 2)
  {
    return 1;
  }
  if ((buf[*pos] < '0') || (buf[*pos] > '9'))
  {
    return -1;
  }
  flags = buf[(*pos)++] - '0';
  if ((buf[*pos] >= '0') && (buf[*pos] <= '9'))
  {
    flags = (flags * 10) + (buf[(*pos)++] - '0');
  }
  flags -= 1;
  *modifiers = 0;
  if (flags & 1)
  {
    *modifiers |= 0x800000000000ULL;
  }
  if (flags & 2)
  {
    *modifiers |= 0x200000000000ULL;
  }
  if (flags & 4)
  {
    *modifiers |= 0x400000000000ULL;
  }
  if (flags & 8)
  {
    *modifiers |= 0x200000000000ULL;
  }
  return 0;
}


/*** DEPENDENCIES:
typedef unsigned long long key_code
----------------------------
***/


static int xterm_keys_match(const char *template, const char *buf, size_t len, size_t *size, key_code *modifiers)
{
  size_t pos;
  int retval;
  *modifiers = 0;
  if (len == 0)
  {
    return 0;
  }
  pos = 0;
  do
  {
    if ((*template) == '_')
    {
      retval = xterm_keys_modifiers(buf, len, &pos, modifiers);
      if (retval != 0)
      {
        return retval;
      }
      continue;
    }
    if (buf[pos] != (*template))
    {
      return -1;
    }
    pos += 1;
  }
  while (((*(++template)) != '\0') && (pos != len));
  if ((*template) != '\0')
  {
    return 1;
  }
  *size = pos;
  return 0;
}


/*** DEPENDENCIES:
static int xterm_keys_modifiers(const char *buf, size_t len, size_t *pos, key_code *modifiers)
{
  u_int flags;
  if ((len - (*pos)) < 2)
  {
    return 1;
  }
  if ((buf[*pos] < '0') || (buf[*pos] > '9'))
  {
    return -1;
  }
  flags = buf[(*pos)++] - '0';
  if ((buf[*pos] >= '0') && (buf[*pos] <= '9'))
  {
    flags = (flags * 10) + (buf[(*pos)++] - '0');
  }
  flags -= 1;
  *modifiers = 0;
  if (flags & 1)
  {
    *modifiers |= 0x800000000000ULL;
  }
  if (flags & 2)
  {
    *modifiers |= 0x200000000000ULL;
  }
  if (flags & 4)
  {
    *modifiers |= 0x400000000000ULL;
  }
  if (flags & 8)
  {
    *modifiers |= 0x200000000000ULL;
  }
  return 0;
}


----------------------------
typedef unsigned long long key_code
----------------------------
***/


int xterm_keys_find(const char *buf, size_t len, size_t *size, key_code *key)
{
  const struct xterm_keys_entry *entry;
  unsigned int entry_idx = 0;
  u_int i;
  int matched;
  key_code modifiers;
  for (i = 0; i < ((sizeof(xterm_keys_table)) / (sizeof(xterm_keys_table[0]))); i += 1)
  {
    entry_idx = &xterm_keys_table[i];
    matched = xterm_keys_match(entry->template, buf, len, size, &modifiers);
    if (matched == (-1))
    {
      continue;
    }
    if (matched == 0)
    {
      *key = (entry->key | modifiers) | 0x1000000000000ULL;
    }
    return matched;
  }

  return -1;
}


/*** DEPENDENCIES:
static const struct xterm_keys_entry xterm_keys_table[] = {{KEYC_F1, "\033[1;_P"}, {KEYC_F1, "\033O1;_P"}, {KEYC_F1, "\033O_P"}, {KEYC_F2, "\033[1;_Q"}, {KEYC_F2, "\033O1;_Q"}, {KEYC_F2, "\033O_Q"}, {KEYC_F3, "\033[1;_R"}, {KEYC_F3, "\033O1;_R"}, {KEYC_F3, "\033O_R"}, {KEYC_F4, "\033[1;_S"}, {KEYC_F4, "\033O1;_S"}, {KEYC_F4, "\033O_S"}, {KEYC_F5, "\033[15;_~"}, {KEYC_F6, "\033[17;_~"}, {KEYC_F7, "\033[18;_~"}, {KEYC_F8, "\033[19;_~"}, {KEYC_F9, "\033[20;_~"}, {KEYC_F10, "\033[21;_~"}, {KEYC_F11, "\033[23;_~"}, {KEYC_F12, "\033[24;_~"}, {KEYC_UP, "\033[1;_A"}, {KEYC_DOWN, "\033[1;_B"}, {KEYC_RIGHT, "\033[1;_C"}, {KEYC_LEFT, "\033[1;_D"}, {KEYC_HOME, "\033[1;_H"}, {KEYC_END, "\033[1;_F"}, {KEYC_PPAGE, "\033[5;_~"}, {KEYC_NPAGE, "\033[6;_~"}, {KEYC_IC, "\033[2;_~"}, {KEYC_DC, "\033[3;_~"}, {'!', "\033[27;_;33~"}, {'#', "\033[27;_;35~"}, {'(', "\033[27;_;40~"}, {')', "\033[27;_;41~"}, {'+', "\033[27;_;43~"}, {',', "\033[27;_;44~"}, {'-', "\033[27;_;45~"}, {'.', "\033[27;_;46~"}, {'0', "\033[27;_;48~"}, {'1', "\033[27;_;49~"}, {'2', "\033[27;_;50~"}, {'3', "\033[27;_;51~"}, {'4', "\033[27;_;52~"}, {'5', "\033[27;_;53~"}, {'6', "\033[27;_;54~"}, {'7', "\033[27;_;55~"}, {'8', "\033[27;_;56~"}, {'9', "\033[27;_;57~"}, {':', "\033[27;_;58~"}, {';', "\033[27;_;59~"}, {'<', "\033[27;_;60~"}, {'=', "\033[27;_;61~"}, {'>', "\033[27;_;62~"}, {'?', "\033[27;_;63~"}, {'\'', "\033[27;_;39~"}, {'\r', "\033[27;_;13~"}, {'\t', "\033[27;_;9~"}}
----------------------------
static int xterm_keys_match(const char *template, const char *buf, size_t len, size_t *size, key_code *modifiers)
{
  size_t pos;
  int retval;
  *modifiers = 0;
  if (len == 0)
  {
    return 0;
  }
  pos = 0;
  do
  {
    if ((*template) == '_')
    {
      retval = xterm_keys_modifiers(buf, len, &pos, modifiers);
      if (retval != 0)
      {
        return retval;
      }
      continue;
    }
    if (buf[pos] != (*template))
    {
      return -1;
    }
    pos += 1;
  }
  while (((*(++template)) != '\0') && (pos != len));
  if ((*template) != '\0')
  {
    return 1;
  }
  *size = pos;
  return 0;
}


----------------------------
typedef unsigned long long key_code
----------------------------
struct xterm_keys_entry
{
  key_code key;
  const char *template;
}
----------------------------
***/


char *xterm_keys_lookup(key_code key)
{
  const struct xterm_keys_entry *entry;
  unsigned int entry_idx = 0;
  u_int i;
  key_code modifiers;
  char *out;
  unsigned int out_idx = 0;
  modifiers = 1;
  if (key & 0x800000000000ULL)
  {
    modifiers += 1;
  }
  if (key & 0x200000000000ULL)
  {
    modifiers += 2;
  }
  if (key & 0x400000000000ULL)
  {
    modifiers += 4;
  }
  if (modifiers == 1)
  {
    return 0;
  }
  if ((key & (0x200000000000ULL | 0x1000000000000ULL)) == 0x200000000000ULL)
  {
    return 0;
  }
  key &= ~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL);
  for (i = 0; i < ((sizeof(xterm_keys_table)) / (sizeof(xterm_keys_table[0]))); i += 1)
  {
    entry_idx = &xterm_keys_table[i];
    if (key == entry->key)
    {
      break;
    }
  }

  if (i == ((sizeof(xterm_keys_table)) / (sizeof(xterm_keys_table[0]))))
  {
    return 0;
  }
  out_idx = xstrdup(entry->template);
  out[strcspn(out, "_") + out_idx] = '0' + modifiers;
  return out;
}


/*** DEPENDENCIES:
struct xterm_keys_entry
{
  key_code key;
  const char *template;
}
----------------------------
static const struct xterm_keys_entry xterm_keys_table[] = {{KEYC_F1, "\033[1;_P"}, {KEYC_F1, "\033O1;_P"}, {KEYC_F1, "\033O_P"}, {KEYC_F2, "\033[1;_Q"}, {KEYC_F2, "\033O1;_Q"}, {KEYC_F2, "\033O_Q"}, {KEYC_F3, "\033[1;_R"}, {KEYC_F3, "\033O1;_R"}, {KEYC_F3, "\033O_R"}, {KEYC_F4, "\033[1;_S"}, {KEYC_F4, "\033O1;_S"}, {KEYC_F4, "\033O_S"}, {KEYC_F5, "\033[15;_~"}, {KEYC_F6, "\033[17;_~"}, {KEYC_F7, "\033[18;_~"}, {KEYC_F8, "\033[19;_~"}, {KEYC_F9, "\033[20;_~"}, {KEYC_F10, "\033[21;_~"}, {KEYC_F11, "\033[23;_~"}, {KEYC_F12, "\033[24;_~"}, {KEYC_UP, "\033[1;_A"}, {KEYC_DOWN, "\033[1;_B"}, {KEYC_RIGHT, "\033[1;_C"}, {KEYC_LEFT, "\033[1;_D"}, {KEYC_HOME, "\033[1;_H"}, {KEYC_END, "\033[1;_F"}, {KEYC_PPAGE, "\033[5;_~"}, {KEYC_NPAGE, "\033[6;_~"}, {KEYC_IC, "\033[2;_~"}, {KEYC_DC, "\033[3;_~"}, {'!', "\033[27;_;33~"}, {'#', "\033[27;_;35~"}, {'(', "\033[27;_;40~"}, {')', "\033[27;_;41~"}, {'+', "\033[27;_;43~"}, {',', "\033[27;_;44~"}, {'-', "\033[27;_;45~"}, {'.', "\033[27;_;46~"}, {'0', "\033[27;_;48~"}, {'1', "\033[27;_;49~"}, {'2', "\033[27;_;50~"}, {'3', "\033[27;_;51~"}, {'4', "\033[27;_;52~"}, {'5', "\033[27;_;53~"}, {'6', "\033[27;_;54~"}, {'7', "\033[27;_;55~"}, {'8', "\033[27;_;56~"}, {'9', "\033[27;_;57~"}, {':', "\033[27;_;58~"}, {';', "\033[27;_;59~"}, {'<', "\033[27;_;60~"}, {'=', "\033[27;_;61~"}, {'>', "\033[27;_;62~"}, {'?', "\033[27;_;63~"}, {'\'', "\033[27;_;39~"}, {'\r', "\033[27;_;13~"}, {'\t', "\033[27;_;9~"}}
----------------------------
typedef unsigned long long key_code
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
***/


