const char *key_string_lookup_key(key_code key)
{
  static char out[32];
  char tmp[8];
  u_int i;
  struct utf8_data ud;
  size_t off;
  *out = '\0';
  if (key == 0xffff00000000ULL)
  {
    return "None";
  }
  if (key == 0xfffe00000000ULL)
  {
    return "Unknown";
  }
  if (key == KEYC_FOCUS_IN)
  {
    return "FocusIn";
  }
  if (key == KEYC_FOCUS_OUT)
  {
    return "FocusOut";
  }
  if (key == KEYC_PASTE_START)
  {
    return "PasteStart";
  }
  if (key == KEYC_PASTE_END)
  {
    return "PasteEnd";
  }
  if (key == KEYC_MOUSE)
  {
    return "Mouse";
  }
  if (key == KEYC_DRAGGING)
  {
    return "Dragging";
  }
  if (key == KEYC_MOUSEMOVE_PANE)
  {
    return "MouseMovePane";
  }
  if (key == KEYC_MOUSEMOVE_STATUS)
  {
    return "MouseMoveStatus";
  }
  if (key == KEYC_MOUSEMOVE_BORDER)
  {
    return "MouseMoveBorder";
  }
  if ((key >= 0x000020000000ULL) && (key < (0x000020000000ULL + 1000)))
  {
    snprintf(out, sizeof(out), "User%u", (u_int) (key - 0x000020000000ULL));
    return out;
  }
  if ((key & (~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL))) == 0)
  {
    key = (' ' | 0x400000000000ULL) | (key & (((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL));
  }
  if (key & 0x400000000000ULL)
  {
    strlcat(out, "C-", sizeof(out));
  }
  if (key & 0x200000000000ULL)
  {
    strlcat(out, "M-", sizeof(out));
  }
  if (key & 0x800000000000ULL)
  {
    strlcat(out, "S-", sizeof(out));
  }
  key &= ~(((0x200000000000ULL | 0x400000000000ULL) | 0x800000000000ULL) | 0x1000000000000ULL);
  for (i = 0; i < ((sizeof(key_string_table)) / (sizeof(key_string_table[0]))); i += 1)
  {
    if (key == key_string_table[i].key)
    {
      break;
    }
  }

  if (i != ((sizeof(key_string_table)) / (sizeof(key_string_table[0]))))
  {
    strlcat(out, key_string_table[i].string, sizeof(out));
    return out;
  }
  if ((key > 127) && (key < 0x000010000000ULL))
  {
    if (utf8_split(key, &ud) == UTF8_DONE)
    {
      off = strlen(out);
      memcpy(out + off, ud.data, ud.size);
      out[off + ud.size] = '\0';
      return out;
    }
  }
  if ((key == 127) || (key > 255))
  {
    snprintf(out, sizeof(out), "Invalid#%llx", key);
    return out;
  }
  if (key <= 32)
  {
    if ((key == 0) || (key > 26))
    {
      xsnprintf(tmp, sizeof(tmp), "C-%c", (int) (64 + key));
    }
    else
      xsnprintf(tmp, sizeof(tmp), "C-%c", (int) (96 + key));
  }
  else
    if ((key >= 32) && (key <= 126))
  {
    tmp[0] = key;
    tmp[1] = '\0';
  }
  else
    if (key >= 128)
  {
    xsnprintf(tmp, sizeof(tmp), "\\%llo", key);
  }
  strlcat(out, tmp, sizeof(out));
  return out;
}


/*** DEPENDENCIES:
typedef unsigned long long key_code
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
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
}
----------------------------
static const struct 
{
  const char *string;
  key_code key;
} key_string_table[] = {{"F1", KEYC_F1}, {"F2", KEYC_F2}, {"F3", KEYC_F3}, {"F4", KEYC_F4}, {"F5", KEYC_F5}, {"F6", KEYC_F6}, {"F7", KEYC_F7}, {"F8", KEYC_F8}, {"F9", KEYC_F9}, {"F10", KEYC_F10}, {"F11", KEYC_F11}, {"F12", KEYC_F12}, {"IC", KEYC_IC}, {"DC", KEYC_DC}, {"Home", KEYC_HOME}, {"End", KEYC_END}, {"NPage", KEYC_NPAGE}, {"PageDown", KEYC_NPAGE}, {"PgDn", KEYC_NPAGE}, {"PPage", KEYC_PPAGE}, {"PageUp", KEYC_PPAGE}, {"PgUp", KEYC_PPAGE}, {"Tab", '\011'}, {"BTab", KEYC_BTAB}, {"Space", ' '}, {"BSpace", KEYC_BSPACE}, {"Enter", '\r'}, {"Escape", '\033'}, {"Up", KEYC_UP}, {"Down", KEYC_DOWN}, {"Left", KEYC_LEFT}, {"Right", KEYC_RIGHT}, {"KP/", KEYC_KP_SLASH}, {"KP*", KEYC_KP_STAR}, {"KP-", KEYC_KP_MINUS}, {"KP7", KEYC_KP_SEVEN}, {"KP8", KEYC_KP_EIGHT}, {"KP9", KEYC_KP_NINE}, {"KP+", KEYC_KP_PLUS}, {"KP4", KEYC_KP_FOUR}, {"KP5", KEYC_KP_FIVE}, {"KP6", KEYC_KP_SIX}, {"KP1", KEYC_KP_ONE}, {"KP2", KEYC_KP_TWO}, {"KP3", KEYC_KP_THREE}, {"KPEnter", KEYC_KP_ENTER}, {"KP0", KEYC_KP_ZERO}, {"KP.", KEYC_KP_PERIOD}, {"MouseDown1Pane", KEYC_MOUSEDOWN1_PANE}, {"MouseDown1Status", KEYC_MOUSEDOWN1_STATUS}, {"MouseDown1Border", KEYC_MOUSEDOWN1_BORDER}, {"MouseDown2Pane", KEYC_MOUSEDOWN2_PANE}, {"MouseDown2Status", KEYC_MOUSEDOWN2_STATUS}, {"MouseDown2Border", KEYC_MOUSEDOWN2_BORDER}, {"MouseDown3Pane", KEYC_MOUSEDOWN3_PANE}, {"MouseDown3Status", KEYC_MOUSEDOWN3_STATUS}, {"MouseDown3Border", KEYC_MOUSEDOWN3_BORDER}, {"MouseUp1Pane", KEYC_MOUSEUP1_PANE}, {"MouseUp1Status", KEYC_MOUSEUP1_STATUS}, {"MouseUp1Border", KEYC_MOUSEUP1_BORDER}, {"MouseUp2Pane", KEYC_MOUSEUP2_PANE}, {"MouseUp2Status", KEYC_MOUSEUP2_STATUS}, {"MouseUp2Border", KEYC_MOUSEUP2_BORDER}, {"MouseUp3Pane", KEYC_MOUSEUP3_PANE}, {"MouseUp3Status", KEYC_MOUSEUP3_STATUS}, {"MouseUp3Border", KEYC_MOUSEUP3_BORDER}, {"MouseDrag1Pane", KEYC_MOUSEDRAG1_PANE}, {"MouseDrag1Status", KEYC_MOUSEDRAG1_STATUS}, {"MouseDrag1Border", KEYC_MOUSEDRAG1_BORDER}, {"MouseDrag2Pane", KEYC_MOUSEDRAG2_PANE}, {"MouseDrag2Status", KEYC_MOUSEDRAG2_STATUS}, {"MouseDrag2Border", KEYC_MOUSEDRAG2_BORDER}, {"MouseDrag3Pane", KEYC_MOUSEDRAG3_PANE}, {"MouseDrag3Status", KEYC_MOUSEDRAG3_STATUS}, {"MouseDrag3Border", KEYC_MOUSEDRAG3_BORDER}, {"MouseDragEnd1Pane", KEYC_MOUSEDRAGEND1_PANE}, {"MouseDragEnd1Status", KEYC_MOUSEDRAGEND1_STATUS}, {"MouseDragEnd1Border", KEYC_MOUSEDRAGEND1_BORDER}, {"MouseDragEnd2Pane", KEYC_MOUSEDRAGEND2_PANE}, {"MouseDragEnd2Status", KEYC_MOUSEDRAGEND2_STATUS}, {"MouseDragEnd2Border", KEYC_MOUSEDRAGEND2_BORDER}, {"MouseDragEnd3Pane", KEYC_MOUSEDRAGEND3_PANE}, {"MouseDragEnd3Status", KEYC_MOUSEDRAGEND3_STATUS}, {"MouseDragEnd3Border", KEYC_MOUSEDRAGEND3_BORDER}, {"WheelUpPane", KEYC_WHEELUP_PANE}, {"WheelUpStatus", KEYC_WHEELUP_STATUS}, {"WheelUpBorder", KEYC_WHEELUP_BORDER}, {"WheelDownPane", KEYC_WHEELDOWN_PANE}, {"WheelDownStatus", KEYC_WHEELDOWN_STATUS}, {"WheelDownBorder", KEYC_WHEELDOWN_BORDER}, {"DoubleClick1Pane", KEYC_DOUBLECLICK1_PANE}, {"DoubleClick1Status", KEYC_DOUBLECLICK1_STATUS}, {"DoubleClick1Border", KEYC_DOUBLECLICK1_BORDER}, {"DoubleClick2Pane", KEYC_DOUBLECLICK2_PANE}, {"DoubleClick2Status", KEYC_DOUBLECLICK2_STATUS}, {"DoubleClick2Border", KEYC_DOUBLECLICK2_BORDER}, {"DoubleClick3Pane", KEYC_DOUBLECLICK3_PANE}, {"DoubleClick3Status", KEYC_DOUBLECLICK3_STATUS}, {"DoubleClick3Border", KEYC_DOUBLECLICK3_BORDER}, {"TripleClick1Pane", KEYC_TRIPLECLICK1_PANE}, {"TripleClick1Status", KEYC_TRIPLECLICK1_STATUS}, {"TripleClick1Border", KEYC_TRIPLECLICK1_BORDER}, {"TripleClick2Pane", KEYC_TRIPLECLICK2_PANE}, {"TripleClick2Status", KEYC_TRIPLECLICK2_STATUS}, {"TripleClick2Border", KEYC_TRIPLECLICK2_BORDER}, {"TripleClick3Pane", KEYC_TRIPLECLICK3_PANE}, {"TripleClick3Status", KEYC_TRIPLECLICK3_STATUS}, {"TripleClick3Border", KEYC_TRIPLECLICK3_BORDER}}
----------------------------
enum utf8_state utf8_split(wchar_t wc, struct utf8_data *ud)
{
  char s[MB_LEN_MAX];
  int slen;
  slen = wctomb(s, wc);
  if ((slen <= 0) || (slen > ((int) (sizeof(ud->data)))))
  {
    return UTF8_ERROR;
  }
  memcpy(ud->data, s, slen);
  ud->size = slen;
  ud->width = utf8_width(wc);
  return UTF8_DONE;
}


----------------------------
***/


static key_code key_string_search_table(const char *string)
{
  u_int i;
  u_int user;
  for (i = 0; i < ((sizeof(key_string_table)) / (sizeof(key_string_table[0]))); i += 1)
  {
    if (strcasecmp(string, key_string_table[i].string) == 0)
    {
      return key_string_table[i].key;
    }
  }

  if ((sscanf(string, "User%u", &user) == 1) && (user < 1000))
  {
    return 0x000020000000ULL + user;
  }
  return 0xfffe00000000ULL;
}


/*** DEPENDENCIES:
static const struct 
{
  const char *string;
  key_code key;
} key_string_table[] = {{"F1", KEYC_F1}, {"F2", KEYC_F2}, {"F3", KEYC_F3}, {"F4", KEYC_F4}, {"F5", KEYC_F5}, {"F6", KEYC_F6}, {"F7", KEYC_F7}, {"F8", KEYC_F8}, {"F9", KEYC_F9}, {"F10", KEYC_F10}, {"F11", KEYC_F11}, {"F12", KEYC_F12}, {"IC", KEYC_IC}, {"DC", KEYC_DC}, {"Home", KEYC_HOME}, {"End", KEYC_END}, {"NPage", KEYC_NPAGE}, {"PageDown", KEYC_NPAGE}, {"PgDn", KEYC_NPAGE}, {"PPage", KEYC_PPAGE}, {"PageUp", KEYC_PPAGE}, {"PgUp", KEYC_PPAGE}, {"Tab", '\011'}, {"BTab", KEYC_BTAB}, {"Space", ' '}, {"BSpace", KEYC_BSPACE}, {"Enter", '\r'}, {"Escape", '\033'}, {"Up", KEYC_UP}, {"Down", KEYC_DOWN}, {"Left", KEYC_LEFT}, {"Right", KEYC_RIGHT}, {"KP/", KEYC_KP_SLASH}, {"KP*", KEYC_KP_STAR}, {"KP-", KEYC_KP_MINUS}, {"KP7", KEYC_KP_SEVEN}, {"KP8", KEYC_KP_EIGHT}, {"KP9", KEYC_KP_NINE}, {"KP+", KEYC_KP_PLUS}, {"KP4", KEYC_KP_FOUR}, {"KP5", KEYC_KP_FIVE}, {"KP6", KEYC_KP_SIX}, {"KP1", KEYC_KP_ONE}, {"KP2", KEYC_KP_TWO}, {"KP3", KEYC_KP_THREE}, {"KPEnter", KEYC_KP_ENTER}, {"KP0", KEYC_KP_ZERO}, {"KP.", KEYC_KP_PERIOD}, {"MouseDown1Pane", KEYC_MOUSEDOWN1_PANE}, {"MouseDown1Status", KEYC_MOUSEDOWN1_STATUS}, {"MouseDown1Border", KEYC_MOUSEDOWN1_BORDER}, {"MouseDown2Pane", KEYC_MOUSEDOWN2_PANE}, {"MouseDown2Status", KEYC_MOUSEDOWN2_STATUS}, {"MouseDown2Border", KEYC_MOUSEDOWN2_BORDER}, {"MouseDown3Pane", KEYC_MOUSEDOWN3_PANE}, {"MouseDown3Status", KEYC_MOUSEDOWN3_STATUS}, {"MouseDown3Border", KEYC_MOUSEDOWN3_BORDER}, {"MouseUp1Pane", KEYC_MOUSEUP1_PANE}, {"MouseUp1Status", KEYC_MOUSEUP1_STATUS}, {"MouseUp1Border", KEYC_MOUSEUP1_BORDER}, {"MouseUp2Pane", KEYC_MOUSEUP2_PANE}, {"MouseUp2Status", KEYC_MOUSEUP2_STATUS}, {"MouseUp2Border", KEYC_MOUSEUP2_BORDER}, {"MouseUp3Pane", KEYC_MOUSEUP3_PANE}, {"MouseUp3Status", KEYC_MOUSEUP3_STATUS}, {"MouseUp3Border", KEYC_MOUSEUP3_BORDER}, {"MouseDrag1Pane", KEYC_MOUSEDRAG1_PANE}, {"MouseDrag1Status", KEYC_MOUSEDRAG1_STATUS}, {"MouseDrag1Border", KEYC_MOUSEDRAG1_BORDER}, {"MouseDrag2Pane", KEYC_MOUSEDRAG2_PANE}, {"MouseDrag2Status", KEYC_MOUSEDRAG2_STATUS}, {"MouseDrag2Border", KEYC_MOUSEDRAG2_BORDER}, {"MouseDrag3Pane", KEYC_MOUSEDRAG3_PANE}, {"MouseDrag3Status", KEYC_MOUSEDRAG3_STATUS}, {"MouseDrag3Border", KEYC_MOUSEDRAG3_BORDER}, {"MouseDragEnd1Pane", KEYC_MOUSEDRAGEND1_PANE}, {"MouseDragEnd1Status", KEYC_MOUSEDRAGEND1_STATUS}, {"MouseDragEnd1Border", KEYC_MOUSEDRAGEND1_BORDER}, {"MouseDragEnd2Pane", KEYC_MOUSEDRAGEND2_PANE}, {"MouseDragEnd2Status", KEYC_MOUSEDRAGEND2_STATUS}, {"MouseDragEnd2Border", KEYC_MOUSEDRAGEND2_BORDER}, {"MouseDragEnd3Pane", KEYC_MOUSEDRAGEND3_PANE}, {"MouseDragEnd3Status", KEYC_MOUSEDRAGEND3_STATUS}, {"MouseDragEnd3Border", KEYC_MOUSEDRAGEND3_BORDER}, {"WheelUpPane", KEYC_WHEELUP_PANE}, {"WheelUpStatus", KEYC_WHEELUP_STATUS}, {"WheelUpBorder", KEYC_WHEELUP_BORDER}, {"WheelDownPane", KEYC_WHEELDOWN_PANE}, {"WheelDownStatus", KEYC_WHEELDOWN_STATUS}, {"WheelDownBorder", KEYC_WHEELDOWN_BORDER}, {"DoubleClick1Pane", KEYC_DOUBLECLICK1_PANE}, {"DoubleClick1Status", KEYC_DOUBLECLICK1_STATUS}, {"DoubleClick1Border", KEYC_DOUBLECLICK1_BORDER}, {"DoubleClick2Pane", KEYC_DOUBLECLICK2_PANE}, {"DoubleClick2Status", KEYC_DOUBLECLICK2_STATUS}, {"DoubleClick2Border", KEYC_DOUBLECLICK2_BORDER}, {"DoubleClick3Pane", KEYC_DOUBLECLICK3_PANE}, {"DoubleClick3Status", KEYC_DOUBLECLICK3_STATUS}, {"DoubleClick3Border", KEYC_DOUBLECLICK3_BORDER}, {"TripleClick1Pane", KEYC_TRIPLECLICK1_PANE}, {"TripleClick1Status", KEYC_TRIPLECLICK1_STATUS}, {"TripleClick1Border", KEYC_TRIPLECLICK1_BORDER}, {"TripleClick2Pane", KEYC_TRIPLECLICK2_PANE}, {"TripleClick2Status", KEYC_TRIPLECLICK2_STATUS}, {"TripleClick2Border", KEYC_TRIPLECLICK2_BORDER}, {"TripleClick3Pane", KEYC_TRIPLECLICK3_PANE}, {"TripleClick3Status", KEYC_TRIPLECLICK3_STATUS}, {"TripleClick3Border", KEYC_TRIPLECLICK3_BORDER}}
----------------------------
***/


static key_code key_string_get_modifiers(const char **string)
{
  key_code modifiers;
  modifiers = 0;
  while (((*string)[0] != '\0') && ((*string)[1] == '-'))
  {
    switch ((*string)[0])
    {
      case 'C':

      case 'c':
      {
        modifiers |= 0x400000000000ULL;
        break;
      }

      case 'M':

      case 'm':
      {
        modifiers |= 0x200000000000ULL;
        break;
      }

      case 'S':

      case 's':
      {
        modifiers |= 0x800000000000ULL;
        break;
      }

      default:
      {
        *string = 0;
        return 0;
      }

    }

    *string += 2;
  }

  return modifiers;
}


/*** DEPENDENCIES:
typedef unsigned long long key_code
----------------------------
***/


// hint:  ['key_ref is a mutable refrence to key_code', 'i_ref is a mutable refrence to u_int', 'more_ref is a mutable refrence to ']
key_code helper_key_string_lookup_string_1(key_code * const key_ref, u_int * const i_ref, enum utf8_state * const more_ref, const char * const string, unsigned int string_idx, key_code modifiers, struct utf8_data ud, wchar_t wc)
{
  key_code key = *key_ref;
  u_int i = *i_ref;
  enum utf8_state more = *more_ref;
  if ((more = utf8_open(&ud, (u_char) string[string_idx])) == UTF8_MORE)
  {
    if (strlen(string) != ud.size)
    {
      return 0xfffe00000000ULL;
    }
    for (i = 1; i < ud.size; i += 1)
    {
      more = utf8_append(&ud, (u_char) string[i + string_idx]);
    }

    if (more != UTF8_DONE)
    {
      return 0xfffe00000000ULL;
    }
    if (utf8_combine(&ud, &wc) != UTF8_DONE)
    {
      return 0xfffe00000000ULL;
    }
    return wc | modifiers;
  }
  key = key_string_search_table(string);
  if (key == 0xfffe00000000ULL)
  {
    return 0xfffe00000000ULL;
  }
  *key_ref = key;
  *i_ref = i;
  *more_ref = more;
}


/*** DEPENDENCIES:
typedef unsigned long long key_code
----------------------------
enum utf8_state utf8_combine(const struct utf8_data *ud, wchar_t *wc)
{
  switch (mbtowc(wc, ud->data, ud->size))
  {
    case -1:
    {
      log_debug("UTF-8 %.*s, mbtowc() %d", (int) ud->size, ud->data, errno);
      mbtowc(0, 0, MB_CUR_MAX);
      return UTF8_ERROR;
    }

    case 0:
    {
      return UTF8_ERROR;
    }

    default:
    {
      return UTF8_DONE;
    }

  }

}


----------------------------
static key_code key_string_search_table(const char *string)
{
  u_int i;
  u_int user;
  for (i = 0; i < ((sizeof(key_string_table)) / (sizeof(key_string_table[0]))); i += 1)
  {
    if (strcasecmp(string, key_string_table[i].string) == 0)
    {
      return key_string_table[i].key;
    }
  }

  if ((sscanf(string, "User%u", &user) == 1) && (user < 1000))
  {
    return 0x000020000000ULL + user;
  }
  return 0xfffe00000000ULL;
}


----------------------------
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
}
----------------------------
enum utf8_state utf8_open(struct utf8_data *ud, u_char ch)
{
  memset(ud, 0, sizeof(*ud));
  if ((ch >= 0xc2) && (ch <= 0xdf))
  {
    ud->size = 2;
  }
  else
    if ((ch >= 0xe0) && (ch <= 0xef))
  {
    ud->size = 3;
  }
  else
    if ((ch >= 0xf0) && (ch <= 0xf4))
  {
    ud->size = 4;
  }
  else
    return UTF8_ERROR;
  utf8_append(ud, ch);
  return UTF8_MORE;
}


----------------------------
enum utf8_state
{
  UTF8_MORE,
  UTF8_DONE,
  UTF8_ERROR
}
----------------------------
enum utf8_state utf8_append(struct utf8_data *ud, u_char ch)
{
  wchar_t wc;
  int width;
  if (ud->have >= ud->size)
  {
    fatalx("UTF-8 character overflow");
  }
  if (ud->size > (sizeof(ud->data)))
  {
    fatalx("UTF-8 character size too large");
  }
  if ((ud->have != 0) && ((ch & 0xc0) != 0x80))
  {
    ud->width = 0xff;
  }
  ud->data[ud->have++] = ch;
  if (ud->have != ud->size)
  {
    return UTF8_MORE;
  }
  if (ud->width == 0xff)
  {
    return UTF8_ERROR;
  }
  if (utf8_combine(ud, &wc) != UTF8_DONE)
  {
    return UTF8_ERROR;
  }
  if ((width = utf8_width(wc)) < 0)
  {
    return UTF8_ERROR;
  }
  ud->width = width;
  return UTF8_DONE;
}


----------------------------
***/


key_code key_string_lookup_string(const char *string)
{
  unsigned int string_idx = 0;
  static const char *other = "!#()+,-.0123456789:;<=>?'\r\t";
  key_code key;
  u_int u;
  key_code modifiers;
  struct utf8_data ud;
  u_int i;
  enum utf8_state more;
  wchar_t wc;
  if (strcasecmp(string, "None") == 0)
  {
    return 0xffff00000000ULL;
  }
  if ((string[0 + string_idx] == '0') && (string[1 + string_idx] == 'x'))
  {
    if (sscanf((&string[string_idx]) + 2, "%x", &u) != 1)
    {
      return 0xfffe00000000ULL;
    }
    if (u > 0x1fffff)
    {
      return 0xfffe00000000ULL;
    }
    return u;
  }
  modifiers = 0;
  if ((string[0 + string_idx] == '^') && (string[1 + string_idx] != '\0'))
  {
    modifiers |= 0x400000000000ULL;
    string_idx += 1;
  }
  modifiers |= key_string_get_modifiers(&(&string[string_idx]));
  if (((&string[string_idx]) == 0) || (string[0 + string_idx] == '\0'))
  {
    return 0xfffe00000000ULL;
  }
  if ((string[1 + string_idx] == '\0') && (((u_char) string[0 + string_idx]) <= 127))
  {
    key = (u_char) string[0 + string_idx];
    if ((key < 32) || (key == 127))
    {
      return 0xfffe00000000ULL;
    }
  }
  else
  {
    helper_key_string_lookup_string_1(&key, &i, &more, string, string_idx, modifiers, ud, wc);
  }
  if (((key < 0x000010000000ULL) && (modifiers & 0x400000000000ULL)) && (!strchr(other, key)))
  {
    if ((key >= 97) && (key <= 122))
    {
      key -= 96;
    }
    else
      if ((key >= 64) && (key <= 95))
    {
      key -= 64;
    }
    else
      if (key == 32)
    {
      key = 0;
    }
    else
      if (key == 63)
    {
      key = KEYC_BSPACE;
    }
    else
      return 0xfffe00000000ULL;
    modifiers &= ~0x400000000000ULL;
  }
  return key | modifiers;
}


/*** DEPENDENCIES:
key_code helper_key_string_lookup_string_1(key_code * const key_ref, u_int * const i_ref, enum utf8_state * const more_ref, const char * const string, unsigned int string_idx, key_code modifiers, struct utf8_data ud, wchar_t wc)
{
  key_code key = *key_ref;
  u_int i = *i_ref;
  enum utf8_state more = *more_ref;
  if ((more = utf8_open(&ud, (u_char) string[string_idx])) == UTF8_MORE)
  {
    if (strlen(string) != ud.size)
    {
      return 0xfffe00000000ULL;
    }
    for (i = 1; i < ud.size; i += 1)
    {
      more = utf8_append(&ud, (u_char) string[i + string_idx]);
    }

    if (more != UTF8_DONE)
    {
      return 0xfffe00000000ULL;
    }
    if (utf8_combine(&ud, &wc) != UTF8_DONE)
    {
      return 0xfffe00000000ULL;
    }
    return wc | modifiers;
  }
  key = key_string_search_table(string);
  if (key == 0xfffe00000000ULL)
  {
    return 0xfffe00000000ULL;
  }
  *key_ref = key;
  *i_ref = i;
  *more_ref = more;
}


----------------------------
typedef unsigned long long key_code
----------------------------
static key_code key_string_get_modifiers(const char **string)
{
  key_code modifiers;
  modifiers = 0;
  while (((*string)[0] != '\0') && ((*string)[1] == '-'))
  {
    switch ((*string)[0])
    {
      case 'C':

      case 'c':
      {
        modifiers |= 0x400000000000ULL;
        break;
      }

      case 'M':

      case 'm':
      {
        modifiers |= 0x200000000000ULL;
        break;
      }

      case 'S':

      case 's':
      {
        modifiers |= 0x800000000000ULL;
        break;
      }

      default:
      {
        *string = 0;
        return 0;
      }

    }

    *string += 2;
  }

  return modifiers;
}


----------------------------
struct utf8_data
{
  u_char data[9];
  u_char have;
  u_char size;
  u_char width;
}
----------------------------
enum utf8_state
{
  UTF8_MORE,
  UTF8_DONE,
  UTF8_ERROR
}
----------------------------
***/


