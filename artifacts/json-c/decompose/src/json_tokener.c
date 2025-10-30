inline static int is_ws_char(char c)
{
  return (((c == ' ') || (c == '\t')) || (c == '\n')) || (c == '\r');
}


/*** DEPENDENCIES:
***/


inline static int is_hex_char(char c)
{
  return (((c >= '0') && (c <= '9')) || ((c >= 'A') && (c <= 'F'))) || ((c >= 'a') && (c <= 'f'));
}


/*** DEPENDENCIES:
***/


static json_bool json_tokener_validate_utf8(const char c, unsigned int *nBytes)
{
  unsigned char chr = c;
  if ((*nBytes) == 0)
  {
    if (chr >= 0x80)
    {
      if ((chr & 0xe0) == 0xc0)
      {
        *nBytes = 1;
      }
      else
        if ((chr & 0xf0) == 0xe0)
      {
        *nBytes = 2;
      }
      else
        if ((chr & 0xf8) == 0xf0)
      {
        *nBytes = 3;
      }
      else
        return 0;
    }
  }
  else
  {
    if ((chr & 0xC0) != 0x80)
    {
      return 0;
    }
    *nBytes -= 1;
  }
  return 1;
}


/*** DEPENDENCIES:
***/


static int json_tokener_parse_double(const char *buf, int len, double *retval)
{
  char *end;
  *retval = strtod(buf, &end);
  if ((buf + len) == end)
  {
    return 0;
  }
  return 1;
}


/*** DEPENDENCIES:
***/


size_t json_tokener_get_parse_end(struct json_tokener *tok)
{
  assert(tok->char_offset >= 0);
  return (size_t) tok->char_offset;
}


/*** DEPENDENCIES:
None
----------------------------
***/


void json_tokener_set_flags(struct json_tokener *tok, int flags)
{
  tok->flags = flags;
}


/*** DEPENDENCIES:
None
----------------------------
***/


// hint:  ['is_exponent_ref is a mutable refrence to int', 'neg_sign_ok_ref is a mutable refrence to int', 'pos_sign_ok_ref is a mutable refrence to int']
void helper_helper_helper_helper_json_tokener_parse_ex_1_16_2_1(int * const is_exponent_ref, int * const neg_sign_ok_ref, int * const pos_sign_ok_ref, struct json_tokener * const tok)
{
  int is_exponent = *is_exponent_ref;
  int neg_sign_ok = *neg_sign_ok_ref;
  int pos_sign_ok = *pos_sign_ok_ref;
  char *e_loc = strchr(tok->pb->buf, 'e');
  unsigned int e_loc_idx = 0;
  if (!(&e_loc[e_loc_idx]))
  {
    e_loc_idx = strchr(tok->pb->buf, 'E');
  }
  if (e_loc)
  {
    char *last_saved_char = &tok->pb->buf[tok->pb->bpos - 1];
    is_exponent = 1;
    pos_sign_ok = (neg_sign_ok = 1);
    if ((&e_loc[e_loc_idx]) != last_saved_char)
    {
      neg_sign_ok = 0;
      pos_sign_ok = 0;
    }
  }
  *is_exponent_ref = is_exponent;
  *neg_sign_ok_ref = neg_sign_ok;
  *pos_sign_ok_ref = pos_sign_ok;
}


/*** DEPENDENCIES:
None
----------------------------
***/


void helper_helper_json_tokener_parse_ex_1_1(struct json_tokener * const tok, char c)
{
  if ((!c) || (c != '\\'))
  {
    do
    {
      if (printbuf_memappend(tok->pb, (char *) utf8_replacement_char, 3) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
    tok->high_surrogate = 0;
    tok->ucs_char = 0;
    tok->st_pos = 0;
    tok->stack[tok->depth].state = tok->stack[tok->depth].saved_state;
    goto redo_char;
  }
  tok->stack[tok->depth].state = json_tokener_state_escape_unicode_need_u;
  break;
}


/*** DEPENDENCIES:
int printbuf_memappend(struct printbuf *p, const char *buf, int size)
{
  if ((size < 0) || (size > ((2147483647 - p->bpos) - 1)))
  {
    errno = EFBIG;
    return -1;
  }
  if (p->size <= ((p->bpos + size) + 1))
  {
    if (printbuf_extend(p, (p->bpos + size) + 1) < 0)
    {
      return -1;
    }
  }
  memcpy(p->buf + p->bpos, buf, size);
  p->bpos += size;
  p->buf[p->bpos] = '\0';
  return size;
}


----------------------------
static unsigned char utf8_replacement_char[3] = {0xEF, 0xBF, 0xBD}
----------------------------
None
----------------------------
***/


void helper_helper_json_tokener_parse_ex_1_2(struct json_tokener * const tok, char c)
{
  if ((!c) || (c != 'u'))
  {
    do
    {
      if (printbuf_memappend(tok->pb, (char *) utf8_replacement_char, 3) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
    tok->high_surrogate = 0;
    tok->ucs_char = 0;
    tok->st_pos = 0;
    tok->stack[tok->depth].state = json_tokener_state_string_escape;
    goto redo_char;
  }
  tok->stack[tok->depth].state = json_tokener_state_escape_unicode;
  break;
}


/*** DEPENDENCIES:
int printbuf_memappend(struct printbuf *p, const char *buf, int size)
{
  if ((size < 0) || (size > ((2147483647 - p->bpos) - 1)))
  {
    errno = EFBIG;
    return -1;
  }
  if (p->size <= ((p->bpos + size) + 1))
  {
    if (printbuf_extend(p, (p->bpos + size) + 1) < 0)
    {
      return -1;
    }
  }
  memcpy(p->buf + p->bpos, buf, size);
  p->bpos += size;
  p->buf[p->bpos] = '\0';
  return size;
}


----------------------------
static unsigned char utf8_replacement_char[3] = {0xEF, 0xBF, 0xBD}
----------------------------
None
----------------------------
***/


void helper_helper_json_tokener_parse_ex_1_9(struct json_tokener * const tok, char c)
{
  {
    int size;
    int size_nan;
    do
    {
      if (printbuf_memappend(tok->pb, &c, 1) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
    size = ((tok->st_pos + 1) < json_null_str_len) ? (tok->st_pos + 1) : (json_null_str_len);
    size_nan = ((tok->st_pos + 1) < json_nan_str_len) ? (tok->st_pos + 1) : (json_nan_str_len);
    if (((!(tok->flags & 0x01)) && (strncasecmp(json_null_str, tok->pb->buf, size) == 0)) || (strncmp(json_null_str, tok->pb->buf, size) == 0))
    {
      if (tok->st_pos == json_null_str_len)
      {
        tok->stack[tok->depth].current = 0;
        tok->stack[tok->depth].saved_state = json_tokener_state_finish;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
        goto redo_char;
      }
    }
    else
      if (((!(tok->flags & 0x01)) && (strncasecmp(json_nan_str, tok->pb->buf, size_nan) == 0)) || (strncmp(json_nan_str, tok->pb->buf, size_nan) == 0))
    {
      if (tok->st_pos == json_nan_str_len)
      {
        tok->stack[tok->depth].current = json_object_new_double(nan(""));
        if (tok->stack[tok->depth].current == 0)
        {
          tok->err = json_tokener_error_memory;
          goto out;
        }
        tok->stack[tok->depth].saved_state = json_tokener_state_finish;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
        goto redo_char;
      }
    }
    else
    {
      tok->err = json_tokener_error_parse_null;
      goto out;
    }
    tok->st_pos += 1;
  }
  break;
}


/*** DEPENDENCIES:
static const int json_null_str_len = (sizeof(json_null_str)) - 1
----------------------------
static const char json_nan_str[] = "NaN"
----------------------------
static const int json_nan_str_len = (sizeof(json_nan_str)) - 1
----------------------------
int printbuf_memappend(struct printbuf *p, const char *buf, int size)
{
  if ((size < 0) || (size > ((2147483647 - p->bpos) - 1)))
  {
    errno = EFBIG;
    return -1;
  }
  if (p->size <= ((p->bpos + size) + 1))
  {
    if (printbuf_extend(p, (p->bpos + size) + 1) < 0)
    {
      return -1;
    }
  }
  memcpy(p->buf + p->bpos, buf, size);
  p->bpos += size;
  p->buf[p->bpos] = '\0';
  return size;
}


----------------------------
static const char json_null_str[] = "null"
----------------------------
struct json_object *json_object_new_double(double d)
{
  struct json_object_double *jso = (struct json_object_double *) json_object_new(json_type_double, sizeof(struct json_object_double), &json_object_double_to_json_string);
  if (!jso)
  {
    return 0;
  }
  jso->base._to_json_string = &json_object_double_to_json_string_default;
  jso->c_double = d;
  return &jso->base;
}


----------------------------
None
----------------------------
***/


// hint:  ['c_ref is a mutable refrence to char']
void helper_helper_json_tokener_parse_ex_1_4(char * const c_ref, struct json_tokener * const tok, const char * const str, int len, unsigned int * const nBytesp, unsigned int str_idx)
{
  char c = *c_ref;
  while (is_ws_char(c))
  {
    if ((!((++(&str[str_idx]), tok->char_offset++, c))) || (!((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = *(&str[str_idx]), 1))))))
    {
      goto out;
    }
  }

  if ((c == '/') && (!(tok->flags & 0x01)))
  {
    printbuf_reset(tok->pb);
    do
    {
      if (printbuf_memappend(tok->pb, &c, 1) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
    tok->stack[tok->depth].state = json_tokener_state_comment_start;
  }
  else
  {
    tok->stack[tok->depth].state = tok->stack[tok->depth].saved_state;
    goto redo_char;
  }
  break;
  *c_ref = c;
}


/*** DEPENDENCIES:
int printbuf_memappend(struct printbuf *p, const char *buf, int size)
{
  if ((size < 0) || (size > ((2147483647 - p->bpos) - 1)))
  {
    errno = EFBIG;
    return -1;
  }
  if (p->size <= ((p->bpos + size) + 1))
  {
    if (printbuf_extend(p, (p->bpos + size) + 1) < 0)
    {
      return -1;
    }
  }
  memcpy(p->buf + p->bpos, buf, size);
  p->bpos += size;
  p->buf[p->bpos] = '\0';
  return size;
}


----------------------------
static json_bool json_tokener_validate_utf8(const char c, unsigned int *nBytes)
{
  unsigned char chr = c;
  if ((*nBytes) == 0)
  {
    if (chr >= 0x80)
    {
      if ((chr & 0xe0) == 0xc0)
      {
        *nBytes = 1;
      }
      else
        if ((chr & 0xf0) == 0xe0)
      {
        *nBytes = 2;
      }
      else
        if ((chr & 0xf8) == 0xf0)
      {
        *nBytes = 3;
      }
      else
        return 0;
    }
  }
  else
  {
    if ((chr & 0xC0) != 0x80)
    {
      return 0;
    }
    *nBytes -= 1;
  }
  return 1;
}


----------------------------
inline static int is_ws_char(char c)
{
  return (((c == ' ') || (c == '\t')) || (c == '\n')) || (c == '\r');
}


----------------------------
void printbuf_reset(struct printbuf *p)
{
  p->buf[0] = '\0';
  p->bpos = 0;
}


----------------------------
None
----------------------------
***/


static void json_tokener_reset_level(struct json_tokener *tok, int depth)
{
  tok->stack[depth].state = json_tokener_state_eatws;
  tok->stack[depth].saved_state = json_tokener_state_start;
  json_object_put(tok->stack[depth].current);
  tok->stack[depth].current = 0;
  free(tok->stack[depth].obj_field_name);
  tok->stack[depth].obj_field_name = 0;
}


/*** DEPENDENCIES:
int json_object_put(struct json_object *jso)
{
  if (!jso)
  {
    return 0;
  }
  assert(jso->_ref_count > 0);
  if ((--jso->_ref_count) > 0)
  {
    return 0;
  }
  if (jso->_user_delete)
  {
    jso->_user_delete(jso, jso->_userdata);
  }
  switch (jso->o_type)
  {
    case json_type_object:
    {
      json_object_object_delete(jso);
      break;
    }

    case json_type_array:
    {
      json_object_array_delete(jso);
      break;
    }

    case json_type_string:
    {
      json_object_string_delete(jso);
      break;
    }

    default:
    {
      json_object_generic_delete(jso);
      break;
    }

  }

  return 1;
}


----------------------------
None
----------------------------
***/


void helper_helper_json_tokener_parse_ex_1_11(struct json_tokener * const tok, char c)
{
  {
    int size1;
    int size2;
    do
    {
      if (printbuf_memappend(tok->pb, &c, 1) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
    size1 = ((tok->st_pos + 1) < json_true_str_len) ? (tok->st_pos + 1) : (json_true_str_len);
    size2 = ((tok->st_pos + 1) < json_false_str_len) ? (tok->st_pos + 1) : (json_false_str_len);
    if (((!(tok->flags & 0x01)) && (strncasecmp(json_true_str, tok->pb->buf, size1) == 0)) || (strncmp(json_true_str, tok->pb->buf, size1) == 0))
    {
      if (tok->st_pos == json_true_str_len)
      {
        tok->stack[tok->depth].current = json_object_new_boolean(1);
        if (tok->stack[tok->depth].current == 0)
        {
          tok->err = json_tokener_error_memory;
          goto out;
        }
        tok->stack[tok->depth].saved_state = json_tokener_state_finish;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
        goto redo_char;
      }
    }
    else
      if (((!(tok->flags & 0x01)) && (strncasecmp(json_false_str, tok->pb->buf, size2) == 0)) || (strncmp(json_false_str, tok->pb->buf, size2) == 0))
    {
      if (tok->st_pos == json_false_str_len)
      {
        tok->stack[tok->depth].current = json_object_new_boolean(0);
        if (tok->stack[tok->depth].current == 0)
        {
          tok->err = json_tokener_error_memory;
          goto out;
        }
        tok->stack[tok->depth].saved_state = json_tokener_state_finish;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
        goto redo_char;
      }
    }
    else
    {
      tok->err = json_tokener_error_parse_boolean;
      goto out;
    }
    tok->st_pos += 1;
  }
  break;
}


/*** DEPENDENCIES:
static const int json_false_str_len = (sizeof(json_false_str)) - 1
----------------------------
static const char json_true_str[] = "true"
----------------------------
static const int json_true_str_len = (sizeof(json_true_str)) - 1
----------------------------
int printbuf_memappend(struct printbuf *p, const char *buf, int size)
{
  if ((size < 0) || (size > ((2147483647 - p->bpos) - 1)))
  {
    errno = EFBIG;
    return -1;
  }
  if (p->size <= ((p->bpos + size) + 1))
  {
    if (printbuf_extend(p, (p->bpos + size) + 1) < 0)
    {
      return -1;
    }
  }
  memcpy(p->buf + p->bpos, buf, size);
  p->bpos += size;
  p->buf[p->bpos] = '\0';
  return size;
}


----------------------------
static const char json_false_str[] = "false"
----------------------------
struct json_object *json_object_new_boolean(json_bool b)
{
  struct json_object_boolean *jso = (struct json_object_boolean *) json_object_new(json_type_boolean, sizeof(struct json_object_boolean), &json_object_boolean_to_json_string);
  if (!jso)
  {
    return 0;
  }
  jso->c_boolean = b;
  return &jso->base;
}


----------------------------
None
----------------------------
***/


// hint:  ['str_idx_ref is a mutable refrence to unsigned int', 'c_ref is a mutable refrence to char']
void helper_helper_helper_helper_json_tokener_parse_ex_1_15_1_1(unsigned int * const str_idx_ref, char * const c_ref, struct json_tokener * const tok, const char * const str, int len, unsigned int * const nBytesp)
{
  unsigned int str_idx = *str_idx_ref;
  char c = *c_ref;
  if ((!c) || (!is_hex_char(c)))
  {
    tok->err = json_tokener_error_parse_string;
    goto out;
  }
  tok->ucs_char |= ((unsigned int) ((c <= '9') ? (c - '0') : ((c & 7) + 9))) << ((3 - tok->st_pos) * 4);
  tok->st_pos += 1;
  if (tok->st_pos >= 4)
  {
    break;
  }
  str_idx += 1;
  (void) ((++(&str[str_idx]), tok->char_offset++, c));
  if (!((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = *(&str[str_idx]), 1)))))
  {
    goto out;
  }
  *str_idx_ref = str_idx;
  *c_ref = c;
}


/*** DEPENDENCIES:
inline static int is_hex_char(char c)
{
  return (((c >= '0') && (c <= '9')) || ((c >= 'A') && (c <= 'F'))) || ((c >= 'a') && (c <= 'f'));
}


----------------------------
static json_bool json_tokener_validate_utf8(const char c, unsigned int *nBytes)
{
  unsigned char chr = c;
  if ((*nBytes) == 0)
  {
    if (chr >= 0x80)
    {
      if ((chr & 0xe0) == 0xc0)
      {
        *nBytes = 1;
      }
      else
        if ((chr & 0xf0) == 0xe0)
      {
        *nBytes = 2;
      }
      else
        if ((chr & 0xf8) == 0xf0)
      {
        *nBytes = 3;
      }
      else
        return 0;
    }
  }
  else
  {
    if ((chr & 0xC0) != 0x80)
    {
      return 0;
    }
    *nBytes -= 1;
  }
  return 1;
}


----------------------------
None
----------------------------
***/


// hint:  ['str_idx_ref is a mutable refrence to unsigned int', 'c_ref is a mutable refrence to char']
void helper_helper_helper_json_tokener_parse_ex_1_15_1(unsigned int * const str_idx_ref, char * const c_ref, struct json_tokener * const tok, const char * const str, int len, unsigned int * const nBytesp)
{
  unsigned int str_idx = *str_idx_ref;
  char c = *c_ref;
  while (1)
  {
    helper_helper_helper_helper_json_tokener_parse_ex_1_15_1_1(&str_idx, &c, tok, str, len, nBytesp);
  }

  tok->st_pos = 0;
  if (tok->high_surrogate)
  {
    if ((tok->ucs_char & 0xFC00) == 0xDC00)
    {
      tok->ucs_char = (((tok->high_surrogate & 0x3FF) << 10) + (tok->ucs_char & 0x3FF)) + 0x10000;
    }
    else
    {
      do
      {
        if (printbuf_memappend(tok->pb, (char *) utf8_replacement_char, 3) < 0)
        {
          tok->err = json_tokener_error_memory;
          goto out;
        }
      }
      while (0);
    }
    tok->high_surrogate = 0;
  }
  if (tok->ucs_char < 0x80)
  {
    unsigned char unescaped_utf[1];
    unescaped_utf[0] = tok->ucs_char;
    do
    {
      if (printbuf_memappend(tok->pb, (char *) unescaped_utf, 1) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
  }
  else
    if (tok->ucs_char < 0x800)
  {
    unsigned char unescaped_utf[2];
    unescaped_utf[0] = 0xc0 | (tok->ucs_char >> 6);
    unescaped_utf[1] = 0x80 | (tok->ucs_char & 0x3f);
    do
    {
      if (printbuf_memappend(tok->pb, (char *) unescaped_utf, 2) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
  }
  else
    if ((tok->ucs_char & 0xFC00) == 0xD800)
  {
    tok->high_surrogate = tok->ucs_char;
    tok->ucs_char = 0;
    tok->stack[tok->depth].state = json_tokener_state_escape_unicode_need_escape;
    break;
  }
  else
    if ((tok->ucs_char & 0xFC00) == 0xDC00)
  {
    do
    {
      if (printbuf_memappend(tok->pb, (char *) utf8_replacement_char, 3) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
  }
  else
    if (tok->ucs_char < 0x10000)
  {
    unsigned char unescaped_utf[3];
    unescaped_utf[0] = 0xe0 | (tok->ucs_char >> 12);
    unescaped_utf[1] = 0x80 | ((tok->ucs_char >> 6) & 0x3f);
    unescaped_utf[2] = 0x80 | (tok->ucs_char & 0x3f);
    do
    {
      if (printbuf_memappend(tok->pb, (char *) unescaped_utf, 3) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
  }
  else
    if (tok->ucs_char < 0x110000)
  {
    unsigned char unescaped_utf[4];
    unescaped_utf[0] = 0xf0 | ((tok->ucs_char >> 18) & 0x07);
    unescaped_utf[1] = 0x80 | ((tok->ucs_char >> 12) & 0x3f);
    unescaped_utf[2] = 0x80 | ((tok->ucs_char >> 6) & 0x3f);
    unescaped_utf[3] = 0x80 | (tok->ucs_char & 0x3f);
    do
    {
      if (printbuf_memappend(tok->pb, (char *) unescaped_utf, 4) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
  }
  else
  {
    do
    {
      if (printbuf_memappend(tok->pb, (char *) utf8_replacement_char, 3) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
  }
  tok->stack[tok->depth].state = tok->stack[tok->depth].saved_state;
  *str_idx_ref = str_idx;
  *c_ref = c;
}


/*** DEPENDENCIES:
int printbuf_memappend(struct printbuf *p, const char *buf, int size)
{
  if ((size < 0) || (size > ((2147483647 - p->bpos) - 1)))
  {
    errno = EFBIG;
    return -1;
  }
  if (p->size <= ((p->bpos + size) + 1))
  {
    if (printbuf_extend(p, (p->bpos + size) + 1) < 0)
    {
      return -1;
    }
  }
  memcpy(p->buf + p->bpos, buf, size);
  p->bpos += size;
  p->buf[p->bpos] = '\0';
  return size;
}


----------------------------
static unsigned char utf8_replacement_char[3] = {0xEF, 0xBF, 0xBD}
----------------------------
void helper_helper_helper_helper_json_tokener_parse_ex_1_15_1_1(unsigned int * const str_idx_ref, char * const c_ref, struct json_tokener * const tok, const char * const str, int len, unsigned int * const nBytesp)
{
  unsigned int str_idx = *str_idx_ref;
  char c = *c_ref;
  if ((!c) || (!is_hex_char(c)))
  {
    tok->err = json_tokener_error_parse_string;
    goto out;
  }
  tok->ucs_char |= ((unsigned int) ((c <= '9') ? (c - '0') : ((c & 7) + 9))) << ((3 - tok->st_pos) * 4);
  tok->st_pos += 1;
  if (tok->st_pos >= 4)
  {
    break;
  }
  str_idx += 1;
  (void) ((++(&str[str_idx]), tok->char_offset++, c));
  if (!((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = *(&str[str_idx]), 1)))))
  {
    goto out;
  }
  *str_idx_ref = str_idx;
  *c_ref = c;
}


----------------------------
None
----------------------------
***/


// hint:  ['str_idx_ref is a mutable refrence to unsigned int', 'c_ref is a mutable refrence to char']
void helper_helper_json_tokener_parse_ex_1_15(unsigned int * const str_idx_ref, char * const c_ref, struct json_tokener * const tok, const char * const str, int len, unsigned int * const nBytesp)
{
  unsigned int str_idx = *str_idx_ref;
  char c = *c_ref;
  {
    helper_helper_helper_json_tokener_parse_ex_1_15_1(&str_idx, &c, tok, str, len, nBytesp);
  }
  break;
  *str_idx_ref = str_idx;
  *c_ref = c;
}


/*** DEPENDENCIES:
void helper_helper_helper_json_tokener_parse_ex_1_15_1(unsigned int * const str_idx_ref, char * const c_ref, struct json_tokener * const tok, const char * const str, int len, unsigned int * const nBytesp)
{
  unsigned int str_idx = *str_idx_ref;
  char c = *c_ref;
  while (1)
  {
    helper_helper_helper_helper_json_tokener_parse_ex_1_15_1_1(&str_idx, &c, tok, str, len, nBytesp);
  }

  tok->st_pos = 0;
  if (tok->high_surrogate)
  {
    if ((tok->ucs_char & 0xFC00) == 0xDC00)
    {
      tok->ucs_char = (((tok->high_surrogate & 0x3FF) << 10) + (tok->ucs_char & 0x3FF)) + 0x10000;
    }
    else
    {
      do
      {
        if (printbuf_memappend(tok->pb, (char *) utf8_replacement_char, 3) < 0)
        {
          tok->err = json_tokener_error_memory;
          goto out;
        }
      }
      while (0);
    }
    tok->high_surrogate = 0;
  }
  if (tok->ucs_char < 0x80)
  {
    unsigned char unescaped_utf[1];
    unescaped_utf[0] = tok->ucs_char;
    do
    {
      if (printbuf_memappend(tok->pb, (char *) unescaped_utf, 1) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
  }
  else
    if (tok->ucs_char < 0x800)
  {
    unsigned char unescaped_utf[2];
    unescaped_utf[0] = 0xc0 | (tok->ucs_char >> 6);
    unescaped_utf[1] = 0x80 | (tok->ucs_char & 0x3f);
    do
    {
      if (printbuf_memappend(tok->pb, (char *) unescaped_utf, 2) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
  }
  else
    if ((tok->ucs_char & 0xFC00) == 0xD800)
  {
    tok->high_surrogate = tok->ucs_char;
    tok->ucs_char = 0;
    tok->stack[tok->depth].state = json_tokener_state_escape_unicode_need_escape;
    break;
  }
  else
    if ((tok->ucs_char & 0xFC00) == 0xDC00)
  {
    do
    {
      if (printbuf_memappend(tok->pb, (char *) utf8_replacement_char, 3) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
  }
  else
    if (tok->ucs_char < 0x10000)
  {
    unsigned char unescaped_utf[3];
    unescaped_utf[0] = 0xe0 | (tok->ucs_char >> 12);
    unescaped_utf[1] = 0x80 | ((tok->ucs_char >> 6) & 0x3f);
    unescaped_utf[2] = 0x80 | (tok->ucs_char & 0x3f);
    do
    {
      if (printbuf_memappend(tok->pb, (char *) unescaped_utf, 3) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
  }
  else
    if (tok->ucs_char < 0x110000)
  {
    unsigned char unescaped_utf[4];
    unescaped_utf[0] = 0xf0 | ((tok->ucs_char >> 18) & 0x07);
    unescaped_utf[1] = 0x80 | ((tok->ucs_char >> 12) & 0x3f);
    unescaped_utf[2] = 0x80 | ((tok->ucs_char >> 6) & 0x3f);
    unescaped_utf[3] = 0x80 | (tok->ucs_char & 0x3f);
    do
    {
      if (printbuf_memappend(tok->pb, (char *) unescaped_utf, 4) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
  }
  else
  {
    do
    {
      if (printbuf_memappend(tok->pb, (char *) utf8_replacement_char, 3) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
  }
  tok->stack[tok->depth].state = tok->stack[tok->depth].saved_state;
  *str_idx_ref = str_idx;
  *c_ref = c;
}


----------------------------
None
----------------------------
***/


// hint:  ['c_ref is a mutable refrence to char']
void helper_helper_helper_json_tokener_parse_ex_1_10_1(char * const c_ref, struct json_tokener * const tok, const char * const str, int len, unsigned int * const nBytesp, unsigned int str_idx)
{
  char c = *c_ref;
  const char *case_start = str;
  while (1)
  {
    if (c == tok->quote_char)
    {
      do
      {
        if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
        {
          tok->err = json_tokener_error_memory;
          goto out;
        }
      }
      while (0);
      tok->stack[tok->depth].obj_field_name = strdup(tok->pb->buf);
      if (tok->stack[tok->depth].obj_field_name == 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
      tok->stack[tok->depth].saved_state = json_tokener_state_object_field_end;
      tok->stack[tok->depth].state = json_tokener_state_eatws;
      break;
    }
    else
      if (c == '\\')
    {
      do
      {
        if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
        {
          tok->err = json_tokener_error_memory;
          goto out;
        }
      }
      while (0);
      tok->stack[tok->depth].saved_state = json_tokener_state_object_field;
      tok->stack[tok->depth].state = json_tokener_state_string_escape;
      break;
    }
    if ((!((++(&str[str_idx]), tok->char_offset++, c))) || (!((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = *(&str[str_idx]), 1))))))
    {
      do
      {
        if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
        {
          tok->err = json_tokener_error_memory;
          goto out;
        }
      }
      while (0);
      goto out;
    }
  }

  *c_ref = c;
}


/*** DEPENDENCIES:
int printbuf_memappend(struct printbuf *p, const char *buf, int size)
{
  if ((size < 0) || (size > ((2147483647 - p->bpos) - 1)))
  {
    errno = EFBIG;
    return -1;
  }
  if (p->size <= ((p->bpos + size) + 1))
  {
    if (printbuf_extend(p, (p->bpos + size) + 1) < 0)
    {
      return -1;
    }
  }
  memcpy(p->buf + p->bpos, buf, size);
  p->bpos += size;
  p->buf[p->bpos] = '\0';
  return size;
}


----------------------------
static json_bool json_tokener_validate_utf8(const char c, unsigned int *nBytes)
{
  unsigned char chr = c;
  if ((*nBytes) == 0)
  {
    if (chr >= 0x80)
    {
      if ((chr & 0xe0) == 0xc0)
      {
        *nBytes = 1;
      }
      else
        if ((chr & 0xf0) == 0xe0)
      {
        *nBytes = 2;
      }
      else
        if ((chr & 0xf8) == 0xf0)
      {
        *nBytes = 3;
      }
      else
        return 0;
    }
  }
  else
  {
    if ((chr & 0xC0) != 0x80)
    {
      return 0;
    }
    *nBytes -= 1;
  }
  return 1;
}


----------------------------
None
----------------------------
***/


// hint:  ['c_ref is a mutable refrence to char']
void helper_helper_json_tokener_parse_ex_1_10(char * const c_ref, struct json_tokener * const tok, const char * const str, int len, unsigned int * const nBytesp, unsigned int str_idx)
{
  char c = *c_ref;
  {
    helper_helper_helper_json_tokener_parse_ex_1_10_1(&c, tok, str, len, nBytesp, str_idx);
  }
  break;
  *c_ref = c;
}


/*** DEPENDENCIES:
void helper_helper_helper_json_tokener_parse_ex_1_10_1(char * const c_ref, struct json_tokener * const tok, const char * const str, int len, unsigned int * const nBytesp, unsigned int str_idx)
{
  char c = *c_ref;
  const char *case_start = str;
  while (1)
  {
    if (c == tok->quote_char)
    {
      do
      {
        if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
        {
          tok->err = json_tokener_error_memory;
          goto out;
        }
      }
      while (0);
      tok->stack[tok->depth].obj_field_name = strdup(tok->pb->buf);
      if (tok->stack[tok->depth].obj_field_name == 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
      tok->stack[tok->depth].saved_state = json_tokener_state_object_field_end;
      tok->stack[tok->depth].state = json_tokener_state_eatws;
      break;
    }
    else
      if (c == '\\')
    {
      do
      {
        if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
        {
          tok->err = json_tokener_error_memory;
          goto out;
        }
      }
      while (0);
      tok->stack[tok->depth].saved_state = json_tokener_state_object_field;
      tok->stack[tok->depth].state = json_tokener_state_string_escape;
      break;
    }
    if ((!((++(&str[str_idx]), tok->char_offset++, c))) || (!((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = *(&str[str_idx]), 1))))))
    {
      do
      {
        if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
        {
          tok->err = json_tokener_error_memory;
          goto out;
        }
      }
      while (0);
      goto out;
    }
  }

  *c_ref = c;
}


----------------------------
None
----------------------------
***/


void helper_helper_helper_json_tokener_parse_ex_1_13_1(struct json_tokener * const tok, char c)
{
  if (c == 'b')
  {
    do
    {
      if (printbuf_memappend(tok->pb, "\b", 1) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
  }
  else
    if (c == 'n')
  {
    do
    {
      if (printbuf_memappend(tok->pb, "\n", 1) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
  }
  else
    if (c == 'r')
  {
    do
    {
      if (printbuf_memappend(tok->pb, "\r", 1) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
  }
  else
    if (c == 't')
  {
    do
    {
      if (printbuf_memappend(tok->pb, "\t", 1) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
  }
  else
    if (c == 'f')
  {
    do
    {
      if (printbuf_memappend(tok->pb, "\f", 1) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
  }
  tok->stack[tok->depth].state = tok->stack[tok->depth].saved_state;
  break;
}


/*** DEPENDENCIES:
int printbuf_memappend(struct printbuf *p, const char *buf, int size)
{
  if ((size < 0) || (size > ((2147483647 - p->bpos) - 1)))
  {
    errno = EFBIG;
    return -1;
  }
  if (p->size <= ((p->bpos + size) + 1))
  {
    if (printbuf_extend(p, (p->bpos + size) + 1) < 0)
    {
      return -1;
    }
  }
  memcpy(p->buf + p->bpos, buf, size);
  p->bpos += size;
  p->buf[p->bpos] = '\0';
  return size;
}


----------------------------
None
----------------------------
***/


void helper_helper_json_tokener_parse_ex_1_13(struct json_tokener * const tok, char c)
{
  switch (c)
  {
    case '"':

    case '\\':

    case '/':
    {
      do
      {
        if (printbuf_memappend(tok->pb, &c, 1) < 0)
        {
          tok->err = json_tokener_error_memory;
          goto out;
        }
      }
      while (0);
      tok->stack[tok->depth].state = tok->stack[tok->depth].saved_state;
      break;
    }

    case 'b':

    case 'n':

    case 'r':

    case 't':

    case 'f':
    {
      helper_helper_helper_json_tokener_parse_ex_1_13_1(tok, c);
    }

    case 'u':
    {
      tok->ucs_char = 0;
      tok->st_pos = 0;
      tok->stack[tok->depth].state = json_tokener_state_escape_unicode;
      break;
    }

    default:
    {
      tok->err = json_tokener_error_parse_string;
      goto out;
    }

  }

  break;
}


/*** DEPENDENCIES:
int printbuf_memappend(struct printbuf *p, const char *buf, int size)
{
  if ((size < 0) || (size > ((2147483647 - p->bpos) - 1)))
  {
    errno = EFBIG;
    return -1;
  }
  if (p->size <= ((p->bpos + size) + 1))
  {
    if (printbuf_extend(p, (p->bpos + size) + 1) < 0)
    {
      return -1;
    }
  }
  memcpy(p->buf + p->bpos, buf, size);
  p->bpos += size;
  p->buf[p->bpos] = '\0';
  return size;
}


----------------------------
void helper_helper_helper_json_tokener_parse_ex_1_13_1(struct json_tokener * const tok, char c)
{
  if (c == 'b')
  {
    do
    {
      if (printbuf_memappend(tok->pb, "\b", 1) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
  }
  else
    if (c == 'n')
  {
    do
    {
      if (printbuf_memappend(tok->pb, "\n", 1) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
  }
  else
    if (c == 'r')
  {
    do
    {
      if (printbuf_memappend(tok->pb, "\r", 1) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
  }
  else
    if (c == 't')
  {
    do
    {
      if (printbuf_memappend(tok->pb, "\t", 1) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
  }
  else
    if (c == 'f')
  {
    do
    {
      if (printbuf_memappend(tok->pb, "\f", 1) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
  }
  tok->stack[tok->depth].state = tok->stack[tok->depth].saved_state;
  break;
}


----------------------------
None
----------------------------
***/


// hint:  ['c_ref is a mutable refrence to char']
void helper_helper_json_tokener_parse_ex_1_5(char * const c_ref, struct json_tokener * const tok, const char * const str, int len, unsigned int * const nBytesp, unsigned int str_idx)
{
  char c = *c_ref;
  {
    const char *case_start = str;
    while (c != '*')
    {
      if ((!((++(&str[str_idx]), tok->char_offset++, c))) || (!((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = *(&str[str_idx]), 1))))))
      {
        do
        {
          if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
          {
            tok->err = json_tokener_error_memory;
            goto out;
          }
        }
        while (0);
        goto out;
      }
    }

    do
    {
      if (printbuf_memappend(tok->pb, case_start, (1 + (&str[str_idx])) - case_start) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
    tok->stack[tok->depth].state = json_tokener_state_comment_end;
  }
  break;
  *c_ref = c;
}


/*** DEPENDENCIES:
int printbuf_memappend(struct printbuf *p, const char *buf, int size)
{
  if ((size < 0) || (size > ((2147483647 - p->bpos) - 1)))
  {
    errno = EFBIG;
    return -1;
  }
  if (p->size <= ((p->bpos + size) + 1))
  {
    if (printbuf_extend(p, (p->bpos + size) + 1) < 0)
    {
      return -1;
    }
  }
  memcpy(p->buf + p->bpos, buf, size);
  p->bpos += size;
  p->buf[p->bpos] = '\0';
  return size;
}


----------------------------
static json_bool json_tokener_validate_utf8(const char c, unsigned int *nBytes)
{
  unsigned char chr = c;
  if ((*nBytes) == 0)
  {
    if (chr >= 0x80)
    {
      if ((chr & 0xe0) == 0xc0)
      {
        *nBytes = 1;
      }
      else
        if ((chr & 0xf0) == 0xe0)
      {
        *nBytes = 2;
      }
      else
        if ((chr & 0xf8) == 0xf0)
      {
        *nBytes = 3;
      }
      else
        return 0;
    }
  }
  else
  {
    if ((chr & 0xC0) != 0x80)
    {
      return 0;
    }
    *nBytes -= 1;
  }
  return 1;
}


----------------------------
None
----------------------------
***/


// hint:  ['str_idx_ref is a mutable refrence to unsigned int', 'c_ref is a mutable refrence to char']
void helper_helper_json_tokener_parse_ex_1_8(unsigned int * const str_idx_ref, char * const c_ref, struct json_tokener * const tok, const char * const str, int len, unsigned int * const nBytesp)
{
  unsigned int str_idx = *str_idx_ref;
  char c = *c_ref;
  {
    int is_negative = 0;
    while (tok->st_pos < ((int) json_inf_str_len))
    {
      char inf_char = str[str_idx];
      if ((inf_char != json_inf_str[tok->st_pos]) && ((tok->flags & 0x01) || (inf_char != json_inf_str_invert[tok->st_pos])))
      {
        tok->err = json_tokener_error_parse_unexpected;
        goto out;
      }
      tok->st_pos += 1;
      str_idx += 1;
      (void) ((++(&str[str_idx]), tok->char_offset++, c));
      if (!((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = *(&str[str_idx]), 1)))))
      {
        goto out;
      }
    }

    if ((tok->pb->bpos > 0) && ((*tok->pb->buf) == '-'))
    {
      is_negative = 1;
    }
    tok->stack[tok->depth].current = json_object_new_double((is_negative) ? (-INFINITY) : (INFINITY));
    if (tok->stack[tok->depth].current == 0)
    {
      tok->err = json_tokener_error_memory;
      goto out;
    }
    tok->stack[tok->depth].saved_state = json_tokener_state_finish;
    tok->stack[tok->depth].state = json_tokener_state_eatws;
    goto redo_char;
  }
  break;
  *str_idx_ref = str_idx;
  *c_ref = c;
}


/*** DEPENDENCIES:
static const unsigned int json_inf_str_len = (sizeof(json_inf_str)) - 1
----------------------------
static const char json_inf_str_invert[] = "iNFINITY"
----------------------------
static json_bool json_tokener_validate_utf8(const char c, unsigned int *nBytes)
{
  unsigned char chr = c;
  if ((*nBytes) == 0)
  {
    if (chr >= 0x80)
    {
      if ((chr & 0xe0) == 0xc0)
      {
        *nBytes = 1;
      }
      else
        if ((chr & 0xf0) == 0xe0)
      {
        *nBytes = 2;
      }
      else
        if ((chr & 0xf8) == 0xf0)
      {
        *nBytes = 3;
      }
      else
        return 0;
    }
  }
  else
  {
    if ((chr & 0xC0) != 0x80)
    {
      return 0;
    }
    *nBytes -= 1;
  }
  return 1;
}


----------------------------
struct json_object *json_object_new_double(double d)
{
  struct json_object_double *jso = (struct json_object_double *) json_object_new(json_type_double, sizeof(struct json_object_double), &json_object_double_to_json_string);
  if (!jso)
  {
    return 0;
  }
  jso->base._to_json_string = &json_object_double_to_json_string_default;
  jso->c_double = d;
  return &jso->base;
}


----------------------------
static const char json_inf_str[] = "Infinity"
----------------------------
None
----------------------------
***/


void helper_helper_json_tokener_parse_ex_1_3(struct json_tokener * const tok, char c)
{
  if (c == '}')
  {
    if ((tok->stack[tok->depth].state == json_tokener_state_object_field_start_after_sep) && (tok->flags & 0x01))
    {
      tok->err = json_tokener_error_parse_unexpected;
      goto out;
    }
    tok->stack[tok->depth].saved_state = json_tokener_state_finish;
    tok->stack[tok->depth].state = json_tokener_state_eatws;
  }
  else
    if ((c == '"') || (c == '\''))
  {
    tok->quote_char = c;
    printbuf_reset(tok->pb);
    tok->stack[tok->depth].state = json_tokener_state_object_field;
  }
  else
  {
    tok->err = json_tokener_error_parse_object_key_name;
    goto out;
  }
  break;
}


/*** DEPENDENCIES:
void printbuf_reset(struct printbuf *p)
{
  p->buf[0] = '\0';
  p->bpos = 0;
}


----------------------------
None
----------------------------
***/


void helper_helper_json_tokener_parse_ex_1_6(struct json_tokener * const tok, char c)
{
  if (c == ']')
  {
    json_object_array_shrink(tok->stack[tok->depth].current, 0);
    if ((tok->stack[tok->depth].state == json_tokener_state_array_after_sep) && (tok->flags & 0x01))
    {
      tok->err = json_tokener_error_parse_unexpected;
      goto out;
    }
    tok->stack[tok->depth].saved_state = json_tokener_state_finish;
    tok->stack[tok->depth].state = json_tokener_state_eatws;
  }
  else
  {
    if (tok->depth >= (tok->max_depth - 1))
    {
      tok->err = json_tokener_error_depth;
      goto out;
    }
    tok->stack[tok->depth].state = json_tokener_state_array_add;
    tok->depth += 1;
    json_tokener_reset_level(tok, tok->depth);
    goto redo_char;
  }
  break;
}


/*** DEPENDENCIES:
static void json_tokener_reset_level(struct json_tokener *tok, int depth)
{
  tok->stack[depth].state = json_tokener_state_eatws;
  tok->stack[depth].saved_state = json_tokener_state_start;
  json_object_put(tok->stack[depth].current);
  tok->stack[depth].current = 0;
  free(tok->stack[depth].obj_field_name);
  tok->stack[depth].obj_field_name = 0;
}


----------------------------
int json_object_array_shrink(struct json_object *jso, int empty_slots)
{
  if (empty_slots < 0)
  {
    json_abort("json_object_array_shrink called with negative empty_slots");
  }
  return array_list_shrink(JC_ARRAY(jso)->c_array, empty_slots);
}


----------------------------
None
----------------------------
***/


// hint:  ['c_ref is a mutable refrence to char']
void helper_helper_json_tokener_parse_ex_1_7(char * const c_ref, struct json_tokener * const tok, const char * const str, int len, unsigned int * const nBytesp, unsigned int str_idx)
{
  char c = *c_ref;
  {
    const char *case_start = str;
    while (c != '\n')
    {
      if ((!((++(&str[str_idx]), tok->char_offset++, c))) || (!((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = *(&str[str_idx]), 1))))))
      {
        do
        {
          if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
          {
            tok->err = json_tokener_error_memory;
            goto out;
          }
        }
        while (0);
        goto out;
      }
    }

    do
    {
      if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
    if (0)
    {
      mc_debug("json_tokener_comment: %s\n", tok->pb->buf);
    }
    tok->stack[tok->depth].state = json_tokener_state_eatws;
  }
  break;
  *c_ref = c;
}


/*** DEPENDENCIES:
int printbuf_memappend(struct printbuf *p, const char *buf, int size)
{
  if ((size < 0) || (size > ((2147483647 - p->bpos) - 1)))
  {
    errno = EFBIG;
    return -1;
  }
  if (p->size <= ((p->bpos + size) + 1))
  {
    if (printbuf_extend(p, (p->bpos + size) + 1) < 0)
    {
      return -1;
    }
  }
  memcpy(p->buf + p->bpos, buf, size);
  p->bpos += size;
  p->buf[p->bpos] = '\0';
  return size;
}


----------------------------
static json_bool json_tokener_validate_utf8(const char c, unsigned int *nBytes)
{
  unsigned char chr = c;
  if ((*nBytes) == 0)
  {
    if (chr >= 0x80)
    {
      if ((chr & 0xe0) == 0xc0)
      {
        *nBytes = 1;
      }
      else
        if ((chr & 0xf0) == 0xe0)
      {
        *nBytes = 2;
      }
      else
        if ((chr & 0xf8) == 0xf0)
      {
        *nBytes = 3;
      }
      else
        return 0;
    }
  }
  else
  {
    if ((chr & 0xC0) != 0x80)
    {
      return 0;
    }
    *nBytes -= 1;
  }
  return 1;
}


----------------------------
void mc_debug(const char *msg, ...)
{
  va_list ap;
  if (_debug)
  {
    __builtin_va_start(ap);
    if (_syslog)
    {
      vsyslog(LOG_DEBUG, msg, ap);
    }
    else
      vprintf(msg, ap);
    ;
  }
}


----------------------------
None
----------------------------
***/


// hint:  ['c_ref is a mutable refrence to char']
void helper_helper_helper_helper_json_tokener_parse_ex_1_12_1_1(char * const c_ref, struct json_tokener * const tok, const char * const str, int len, unsigned int * const nBytesp, unsigned int str_idx, const char * const case_start)
{
  char c = *c_ref;
  if (c == tok->quote_char)
  {
    do
    {
      if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
    tok->stack[tok->depth].current = json_object_new_string_len(tok->pb->buf, tok->pb->bpos);
    if (tok->stack[tok->depth].current == 0)
    {
      tok->err = json_tokener_error_memory;
      goto out;
    }
    tok->stack[tok->depth].saved_state = json_tokener_state_finish;
    tok->stack[tok->depth].state = json_tokener_state_eatws;
    break;
  }
  else
    if (c == '\\')
  {
    do
    {
      if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
    tok->stack[tok->depth].saved_state = json_tokener_state_string;
    tok->stack[tok->depth].state = json_tokener_state_string_escape;
    break;
  }
  else
    if ((tok->flags & 0x01) && (((unsigned char) c) <= 0x1f))
  {
    tok->err = json_tokener_error_parse_string;
    goto out;
  }
  if ((!((++(&str[str_idx]), tok->char_offset++, c))) || (!((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = *(&str[str_idx]), 1))))))
  {
    do
    {
      if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
    goto out;
  }
  *c_ref = c;
}


/*** DEPENDENCIES:
int printbuf_memappend(struct printbuf *p, const char *buf, int size)
{
  if ((size < 0) || (size > ((2147483647 - p->bpos) - 1)))
  {
    errno = EFBIG;
    return -1;
  }
  if (p->size <= ((p->bpos + size) + 1))
  {
    if (printbuf_extend(p, (p->bpos + size) + 1) < 0)
    {
      return -1;
    }
  }
  memcpy(p->buf + p->bpos, buf, size);
  p->bpos += size;
  p->buf[p->bpos] = '\0';
  return size;
}


----------------------------
static json_bool json_tokener_validate_utf8(const char c, unsigned int *nBytes)
{
  unsigned char chr = c;
  if ((*nBytes) == 0)
  {
    if (chr >= 0x80)
    {
      if ((chr & 0xe0) == 0xc0)
      {
        *nBytes = 1;
      }
      else
        if ((chr & 0xf0) == 0xe0)
      {
        *nBytes = 2;
      }
      else
        if ((chr & 0xf8) == 0xf0)
      {
        *nBytes = 3;
      }
      else
        return 0;
    }
  }
  else
  {
    if ((chr & 0xC0) != 0x80)
    {
      return 0;
    }
    *nBytes -= 1;
  }
  return 1;
}


----------------------------
struct json_object *json_object_new_string_len(const char *s, const int len)
{
  return _json_object_new_string(s, len);
}


----------------------------
None
----------------------------
***/


// hint:  ['c_ref is a mutable refrence to char']
void helper_helper_helper_json_tokener_parse_ex_1_12_1(char * const c_ref, struct json_tokener * const tok, const char * const str, int len, unsigned int * const nBytesp, unsigned int str_idx)
{
  char c = *c_ref;
  const char *case_start = str;
  while (1)
  {
    helper_helper_helper_helper_json_tokener_parse_ex_1_12_1_1(&c, tok, str, len, nBytesp, str_idx, case_start);
  }

  *c_ref = c;
}


/*** DEPENDENCIES:
void helper_helper_helper_helper_json_tokener_parse_ex_1_12_1_1(char * const c_ref, struct json_tokener * const tok, const char * const str, int len, unsigned int * const nBytesp, unsigned int str_idx, const char * const case_start)
{
  char c = *c_ref;
  if (c == tok->quote_char)
  {
    do
    {
      if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
    tok->stack[tok->depth].current = json_object_new_string_len(tok->pb->buf, tok->pb->bpos);
    if (tok->stack[tok->depth].current == 0)
    {
      tok->err = json_tokener_error_memory;
      goto out;
    }
    tok->stack[tok->depth].saved_state = json_tokener_state_finish;
    tok->stack[tok->depth].state = json_tokener_state_eatws;
    break;
  }
  else
    if (c == '\\')
  {
    do
    {
      if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
    tok->stack[tok->depth].saved_state = json_tokener_state_string;
    tok->stack[tok->depth].state = json_tokener_state_string_escape;
    break;
  }
  else
    if ((tok->flags & 0x01) && (((unsigned char) c) <= 0x1f))
  {
    tok->err = json_tokener_error_parse_string;
    goto out;
  }
  if ((!((++(&str[str_idx]), tok->char_offset++, c))) || (!((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = *(&str[str_idx]), 1))))))
  {
    do
    {
      if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
    goto out;
  }
  *c_ref = c;
}


----------------------------
None
----------------------------
***/


// hint:  ['c_ref is a mutable refrence to char']
void helper_helper_json_tokener_parse_ex_1_12(char * const c_ref, struct json_tokener * const tok, const char * const str, int len, unsigned int * const nBytesp, unsigned int str_idx)
{
  char c = *c_ref;
  {
    helper_helper_helper_json_tokener_parse_ex_1_12_1(&c, tok, str, len, nBytesp, str_idx);
  }
  break;
  *c_ref = c;
}


/*** DEPENDENCIES:
void helper_helper_helper_json_tokener_parse_ex_1_12_1(char * const c_ref, struct json_tokener * const tok, const char * const str, int len, unsigned int * const nBytesp, unsigned int str_idx)
{
  char c = *c_ref;
  const char *case_start = str;
  while (1)
  {
    helper_helper_helper_helper_json_tokener_parse_ex_1_12_1_1(&c, tok, str, len, nBytesp, str_idx, case_start);
  }

  *c_ref = c;
}


----------------------------
None
----------------------------
***/


void helper_helper_json_tokener_parse_ex_1_14(struct json_tokener * const tok, char c)
{
  switch (c)
  {
    case '{':
    {
      tok->stack[tok->depth].state = json_tokener_state_eatws;
      tok->stack[tok->depth].saved_state = json_tokener_state_object_field_start;
      tok->stack[tok->depth].current = json_object_new_object();
      if (tok->stack[tok->depth].current == 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
      break;
    }

    case '[':
    {
      tok->stack[tok->depth].state = json_tokener_state_eatws;
      tok->stack[tok->depth].saved_state = json_tokener_state_array;
      tok->stack[tok->depth].current = json_object_new_array();
      if (tok->stack[tok->depth].current == 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
      break;
    }

    case 'I':

    case 'i':
    {
      tok->stack[tok->depth].state = json_tokener_state_inf;
      printbuf_reset(tok->pb);
      tok->st_pos = 0;
      goto redo_char;
    }

    case 'N':

    case 'n':
    {
      tok->stack[tok->depth].state = json_tokener_state_null;
      printbuf_reset(tok->pb);
      tok->st_pos = 0;
      goto redo_char;
    }

    case '\'':
    {
      if (tok->flags & 0x01)
      {
        tok->err = json_tokener_error_parse_unexpected;
        goto out;
      }
    }

    case '"':
    {
      tok->stack[tok->depth].state = json_tokener_state_string;
      printbuf_reset(tok->pb);
      tok->quote_char = c;
      break;
    }

    case 'T':

    case 't':

    case 'F':

    case 'f':
    {
      tok->stack[tok->depth].state = json_tokener_state_boolean;
      printbuf_reset(tok->pb);
      tok->st_pos = 0;
      goto redo_char;
    }

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

    case '-':
    {
      tok->stack[tok->depth].state = json_tokener_state_number;
      printbuf_reset(tok->pb);
      tok->is_double = 0;
      goto redo_char;
    }

    default:
    {
      tok->err = json_tokener_error_parse_unexpected;
      goto out;
    }

  }

  break;
}


/*** DEPENDENCIES:
struct json_object *json_object_new_array(void)
{
  return json_object_new_array_ext(32);
}


----------------------------
struct json_object *json_object_new_object(void)
{
  struct json_object_object *jso = (struct json_object_object *) json_object_new(json_type_object, sizeof(struct json_object_object), &json_object_object_to_json_string);
  if (!jso)
  {
    return 0;
  }
  jso->c_object = lh_kchar_table_new(16, &json_object_lh_entry_free);
  if (!jso->c_object)
  {
    json_object_generic_delete(&jso->base);
    errno = ENOMEM;
    return 0;
  }
  return &jso->base;
}


----------------------------
void printbuf_reset(struct printbuf *p)
{
  p->buf[0] = '\0';
  p->bpos = 0;
}


----------------------------
None
----------------------------
***/


// hint:  ['num64_ref is a mutable refrence to int64_t']
void helper_helper_helper_helper_json_tokener_parse_ex_1_16_1_1(int64_t * const num64_ref, struct json_tokener * const tok, uint64_t numuint64)
{
  int64_t num64 = *num64_ref;
  if ((errno == ERANGE) && (tok->flags & 0x01))
  {
    tok->err = json_tokener_error_parse_number;
    goto out;
  }
  if ((numuint64 && (tok->pb->buf[0] == '0')) && (tok->flags & 0x01))
  {
    tok->err = json_tokener_error_parse_number;
    goto out;
  }
  if (numuint64 <= INT64_MAX)
  {
    num64 = (uint64_t) numuint64;
    tok->stack[tok->depth].current = json_object_new_int64(num64);
    if (tok->stack[tok->depth].current == 0)
    {
      tok->err = json_tokener_error_memory;
      goto out;
    }
  }
  else
  {
    tok->stack[tok->depth].current = json_object_new_uint64(numuint64);
    if (tok->stack[tok->depth].current == 0)
    {
      tok->err = json_tokener_error_memory;
      goto out;
    }
  }
  *num64_ref = num64;
}


/*** DEPENDENCIES:
struct json_object *json_object_new_uint64(uint64_t i)
{
  struct json_object_int *jso = (struct json_object_int *) json_object_new(json_type_int, sizeof(struct json_object_int), &json_object_int_to_json_string);
  if (!jso)
  {
    return 0;
  }
  jso->cint.c_uint64 = i;
  jso->cint_type = json_object_int_type_uint64;
  return &jso->base;
}


----------------------------
struct json_object *json_object_new_int64(int64_t i)
{
  struct json_object_int *jso = (struct json_object_int *) json_object_new(json_type_int, sizeof(struct json_object_int), &json_object_int_to_json_string);
  if (!jso)
  {
    return 0;
  }
  jso->cint.c_int64 = i;
  jso->cint_type = json_object_int_type_int64;
  return &jso->base;
}


----------------------------
None
----------------------------
***/


void helper_helper_helper_json_tokener_parse_ex_1_16_1(struct json_tokener * const tok)
{
  int64_t num64;
  uint64_t numuint64;
  double numd;
  if (((!tok->is_double) && (tok->pb->buf[0] == '-')) && (json_parse_int64(tok->pb->buf, &num64) == 0))
  {
    if ((errno == ERANGE) && (tok->flags & 0x01))
    {
      tok->err = json_tokener_error_parse_number;
      goto out;
    }
    tok->stack[tok->depth].current = json_object_new_int64(num64);
    if (tok->stack[tok->depth].current == 0)
    {
      tok->err = json_tokener_error_memory;
      goto out;
    }
  }
  else
    if (((!tok->is_double) && (tok->pb->buf[0] != '-')) && (json_parse_uint64(tok->pb->buf, &numuint64) == 0))
  {
    helper_helper_helper_helper_json_tokener_parse_ex_1_16_1_1(&num64, tok, numuint64);
  }
  else
    if (tok->is_double && (json_tokener_parse_double(tok->pb->buf, tok->pb->bpos, &numd) == 0))
  {
    tok->stack[tok->depth].current = json_object_new_double_s(numd, tok->pb->buf);
    if (tok->stack[tok->depth].current == 0)
    {
      tok->err = json_tokener_error_memory;
      goto out;
    }
  }
  else
  {
    tok->err = json_tokener_error_parse_number;
    goto out;
  }
  tok->stack[tok->depth].saved_state = json_tokener_state_finish;
  tok->stack[tok->depth].state = json_tokener_state_eatws;
  goto redo_char;
}


/*** DEPENDENCIES:
void helper_helper_helper_helper_json_tokener_parse_ex_1_16_1_1(int64_t * const num64_ref, struct json_tokener * const tok, uint64_t numuint64)
{
  int64_t num64 = *num64_ref;
  if ((errno == ERANGE) && (tok->flags & 0x01))
  {
    tok->err = json_tokener_error_parse_number;
    goto out;
  }
  if ((numuint64 && (tok->pb->buf[0] == '0')) && (tok->flags & 0x01))
  {
    tok->err = json_tokener_error_parse_number;
    goto out;
  }
  if (numuint64 <= INT64_MAX)
  {
    num64 = (uint64_t) numuint64;
    tok->stack[tok->depth].current = json_object_new_int64(num64);
    if (tok->stack[tok->depth].current == 0)
    {
      tok->err = json_tokener_error_memory;
      goto out;
    }
  }
  else
  {
    tok->stack[tok->depth].current = json_object_new_uint64(numuint64);
    if (tok->stack[tok->depth].current == 0)
    {
      tok->err = json_tokener_error_memory;
      goto out;
    }
  }
  *num64_ref = num64;
}


----------------------------
int json_parse_uint64(const char *buf, uint64_t *retval)
{
  unsigned int buf_idx = 0;
  char *end = 0;
  uint64_t val;
  errno = 0;
  while (buf[buf_idx] == ' ')
  {
    buf_idx += 1;
  }

  if (buf[buf_idx] == '-')
  {
    return 1;
  }
  val = strtoull(buf, &end, 10);
  if (end != (&buf[buf_idx]))
  {
    *retval = val;
  }
  if (((val == 0) && (errno != 0)) || (end == (&buf[buf_idx])))
  {
    errno = EINVAL;
    return 1;
  }
  return 0;
}


----------------------------
struct json_object *json_object_new_double_s(double d, const char *ds)
{
  char *new_ds;
  unsigned int new_ds_idx = 0;
  struct json_object *jso = json_object_new_double(d);
  if (!jso)
  {
    return 0;
  }
  new_ds_idx = strdup(ds);
  if (!(&new_ds[new_ds_idx]))
  {
    json_object_generic_delete(jso);
    errno = ENOMEM;
    return 0;
  }
  json_object_set_serializer(jso, _json_object_userdata_to_json_string, new_ds, json_object_free_userdata);
  return jso;
}


----------------------------
int json_parse_int64(const char *buf, int64_t *retval)
{
  char *end = 0;
  int64_t val;
  errno = 0;
  val = strtoll(buf, &end, 10);
  if (end != buf)
  {
    *retval = val;
  }
  if (((val == 0) && (errno != 0)) || (end == buf))
  {
    errno = EINVAL;
    return 1;
  }
  return 0;
}


----------------------------
static int json_tokener_parse_double(const char *buf, int len, double *retval)
{
  char *end;
  *retval = strtod(buf, &end);
  if ((buf + len) == end)
  {
    return 0;
  }
  return 1;
}


----------------------------
struct json_object *json_object_new_int64(int64_t i)
{
  struct json_object_int *jso = (struct json_object_int *) json_object_new(json_type_int, sizeof(struct json_object_int), &json_object_int_to_json_string);
  if (!jso)
  {
    return 0;
  }
  jso->cint.c_int64 = i;
  jso->cint_type = json_object_int_type_int64;
  return &jso->base;
}


----------------------------
None
----------------------------
***/


// hint:  ['c_ref is a mutable refrence to char', 'case_len_ref is a mutable refrence to int', 'is_exponent_ref is a mutable refrence to int', 'neg_sign_ok_ref is a mutable refrence to int', 'pos_sign_ok_ref is a mutable refrence to int']
void helper_helper_helper_helper_json_tokener_parse_ex_1_16_2_2(char * const c_ref, int * const case_len_ref, int * const is_exponent_ref, int * const neg_sign_ok_ref, int * const pos_sign_ok_ref, struct json_tokener * const tok, const char * const str, int len, unsigned int * const nBytesp, unsigned int str_idx, const char * const case_start)
{
  char c = *c_ref;
  int case_len = *case_len_ref;
  int is_exponent = *is_exponent_ref;
  int neg_sign_ok = *neg_sign_ok_ref;
  int pos_sign_ok = *pos_sign_ok_ref;
  pos_sign_ok = (neg_sign_ok = 0);
  case_len += 1;
  switch (c)
  {
    case '.':
    {
      tok->is_double = 1;
      pos_sign_ok = 1;
      neg_sign_ok = 1;
      break;
    }

    case 'e':

    case 'E':
    {
      is_exponent = 1;
      tok->is_double = 1;
      pos_sign_ok = (neg_sign_ok = 1);
      break;
    }

    default:
    {
      break;
    }

  }

  if ((!((++(&str[str_idx]), tok->char_offset++, c))) || (!((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = *(&str[str_idx]), 1))))))
  {
    do
    {
      if (printbuf_memappend(tok->pb, case_start, case_len) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
    goto out;
  }
  *c_ref = c;
  *case_len_ref = case_len;
  *is_exponent_ref = is_exponent;
  *neg_sign_ok_ref = neg_sign_ok;
  *pos_sign_ok_ref = pos_sign_ok;
}


/*** DEPENDENCIES:
int printbuf_memappend(struct printbuf *p, const char *buf, int size)
{
  if ((size < 0) || (size > ((2147483647 - p->bpos) - 1)))
  {
    errno = EFBIG;
    return -1;
  }
  if (p->size <= ((p->bpos + size) + 1))
  {
    if (printbuf_extend(p, (p->bpos + size) + 1) < 0)
    {
      return -1;
    }
  }
  memcpy(p->buf + p->bpos, buf, size);
  p->bpos += size;
  p->buf[p->bpos] = '\0';
  return size;
}


----------------------------
static json_bool json_tokener_validate_utf8(const char c, unsigned int *nBytes)
{
  unsigned char chr = c;
  if ((*nBytes) == 0)
  {
    if (chr >= 0x80)
    {
      if ((chr & 0xe0) == 0xc0)
      {
        *nBytes = 1;
      }
      else
        if ((chr & 0xf0) == 0xe0)
      {
        *nBytes = 2;
      }
      else
        if ((chr & 0xf8) == 0xf0)
      {
        *nBytes = 3;
      }
      else
        return 0;
    }
  }
  else
  {
    if ((chr & 0xC0) != 0x80)
    {
      return 0;
    }
    *nBytes -= 1;
  }
  return 1;
}


----------------------------
None
----------------------------
***/


// hint:  ['c_ref is a mutable refrence to char']
void helper_helper_helper_json_tokener_parse_ex_1_16_2(char * const c_ref, struct json_tokener * const tok, const char * const str, int len, unsigned int * const nBytesp, unsigned int str_idx)
{
  char c = *c_ref;
  const char *case_start = str;
  int case_len = 0;
  int is_exponent = 0;
  int neg_sign_ok = 1;
  int pos_sign_ok = 0;
  if (tok->pb->bpos > 0)
  {
    helper_helper_helper_helper_json_tokener_parse_ex_1_16_2_1(&is_exponent, &neg_sign_ok, &pos_sign_ok, tok);
  }
  while (c && ((((((c >= '0') && (c <= '9')) || ((!is_exponent) && ((c == 'e') || (c == 'E')))) || (neg_sign_ok && (c == '-'))) || (pos_sign_ok && (c == '+'))) || ((!tok->is_double) && (c == '.'))))
  {
    helper_helper_helper_helper_json_tokener_parse_ex_1_16_2_2(&c, &case_len, &is_exponent, &neg_sign_ok, &pos_sign_ok, tok, str, len, nBytesp, str_idx, case_start);
  }

  if ((((((((tok->depth > 0) && (c != ',')) && (c != ']')) && (c != '}')) && (c != '/')) && (c != 'I')) && (c != 'i')) && (!is_ws_char(c)))
  {
    tok->err = json_tokener_error_parse_number;
    goto out;
  }
  if (case_len > 0)
  {
    do
    {
      if (printbuf_memappend(tok->pb, case_start, case_len) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
  }
  if (((tok->pb->buf[0] == '-') && (case_len <= 1)) && ((c == 'i') || (c == 'I')))
  {
    tok->stack[tok->depth].state = json_tokener_state_inf;
    tok->st_pos = 0;
    goto redo_char;
  }
  if (tok->is_double && (!(tok->flags & 0x01)))
  {
    while (tok->pb->bpos > 1)
    {
      char last_char = tok->pb->buf[tok->pb->bpos - 1];
      if ((((last_char != 'e') && (last_char != 'E')) && (last_char != '-')) && (last_char != '+'))
      {
        break;
      }
      tok->pb->buf[tok->pb->bpos - 1] = '\0';
      tok->pb->bpos -= 1;
    }

  }
  *c_ref = c;
}


/*** DEPENDENCIES:
int printbuf_memappend(struct printbuf *p, const char *buf, int size)
{
  if ((size < 0) || (size > ((2147483647 - p->bpos) - 1)))
  {
    errno = EFBIG;
    return -1;
  }
  if (p->size <= ((p->bpos + size) + 1))
  {
    if (printbuf_extend(p, (p->bpos + size) + 1) < 0)
    {
      return -1;
    }
  }
  memcpy(p->buf + p->bpos, buf, size);
  p->bpos += size;
  p->buf[p->bpos] = '\0';
  return size;
}


----------------------------
void helper_helper_helper_helper_json_tokener_parse_ex_1_16_2_2(char * const c_ref, int * const case_len_ref, int * const is_exponent_ref, int * const neg_sign_ok_ref, int * const pos_sign_ok_ref, struct json_tokener * const tok, const char * const str, int len, unsigned int * const nBytesp, unsigned int str_idx, const char * const case_start)
{
  char c = *c_ref;
  int case_len = *case_len_ref;
  int is_exponent = *is_exponent_ref;
  int neg_sign_ok = *neg_sign_ok_ref;
  int pos_sign_ok = *pos_sign_ok_ref;
  pos_sign_ok = (neg_sign_ok = 0);
  case_len += 1;
  switch (c)
  {
    case '.':
    {
      tok->is_double = 1;
      pos_sign_ok = 1;
      neg_sign_ok = 1;
      break;
    }

    case 'e':

    case 'E':
    {
      is_exponent = 1;
      tok->is_double = 1;
      pos_sign_ok = (neg_sign_ok = 1);
      break;
    }

    default:
    {
      break;
    }

  }

  if ((!((++(&str[str_idx]), tok->char_offset++, c))) || (!((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = *(&str[str_idx]), 1))))))
  {
    do
    {
      if (printbuf_memappend(tok->pb, case_start, case_len) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
    goto out;
  }
  *c_ref = c;
  *case_len_ref = case_len;
  *is_exponent_ref = is_exponent;
  *neg_sign_ok_ref = neg_sign_ok;
  *pos_sign_ok_ref = pos_sign_ok;
}


----------------------------
inline static int is_ws_char(char c)
{
  return (((c == ' ') || (c == '\t')) || (c == '\n')) || (c == '\r');
}


----------------------------
void helper_helper_helper_helper_json_tokener_parse_ex_1_16_2_1(int * const is_exponent_ref, int * const neg_sign_ok_ref, int * const pos_sign_ok_ref, struct json_tokener * const tok)
{
  int is_exponent = *is_exponent_ref;
  int neg_sign_ok = *neg_sign_ok_ref;
  int pos_sign_ok = *pos_sign_ok_ref;
  char *e_loc = strchr(tok->pb->buf, 'e');
  unsigned int e_loc_idx = 0;
  if (!(&e_loc[e_loc_idx]))
  {
    e_loc_idx = strchr(tok->pb->buf, 'E');
  }
  if (e_loc)
  {
    char *last_saved_char = &tok->pb->buf[tok->pb->bpos - 1];
    is_exponent = 1;
    pos_sign_ok = (neg_sign_ok = 1);
    if ((&e_loc[e_loc_idx]) != last_saved_char)
    {
      neg_sign_ok = 0;
      pos_sign_ok = 0;
    }
  }
  *is_exponent_ref = is_exponent;
  *neg_sign_ok_ref = neg_sign_ok;
  *pos_sign_ok_ref = pos_sign_ok;
}


----------------------------
None
----------------------------
***/


// hint:  ['c_ref is a mutable refrence to char']
void helper_helper_json_tokener_parse_ex_1_16(char * const c_ref, struct json_tokener * const tok, const char * const str, int len, unsigned int * const nBytesp, unsigned int str_idx)
{
  char c = *c_ref;
  {
    helper_helper_helper_json_tokener_parse_ex_1_16_2(&c, tok, str, len, nBytesp, str_idx);
  }
  {
    helper_helper_helper_json_tokener_parse_ex_1_16_1(tok);
  }
  break;
  *c_ref = c;
}


/*** DEPENDENCIES:
void helper_helper_helper_json_tokener_parse_ex_1_16_1(struct json_tokener * const tok)
{
  int64_t num64;
  uint64_t numuint64;
  double numd;
  if (((!tok->is_double) && (tok->pb->buf[0] == '-')) && (json_parse_int64(tok->pb->buf, &num64) == 0))
  {
    if ((errno == ERANGE) && (tok->flags & 0x01))
    {
      tok->err = json_tokener_error_parse_number;
      goto out;
    }
    tok->stack[tok->depth].current = json_object_new_int64(num64);
    if (tok->stack[tok->depth].current == 0)
    {
      tok->err = json_tokener_error_memory;
      goto out;
    }
  }
  else
    if (((!tok->is_double) && (tok->pb->buf[0] != '-')) && (json_parse_uint64(tok->pb->buf, &numuint64) == 0))
  {
    helper_helper_helper_helper_json_tokener_parse_ex_1_16_1_1(&num64, tok, numuint64);
  }
  else
    if (tok->is_double && (json_tokener_parse_double(tok->pb->buf, tok->pb->bpos, &numd) == 0))
  {
    tok->stack[tok->depth].current = json_object_new_double_s(numd, tok->pb->buf);
    if (tok->stack[tok->depth].current == 0)
    {
      tok->err = json_tokener_error_memory;
      goto out;
    }
  }
  else
  {
    tok->err = json_tokener_error_parse_number;
    goto out;
  }
  tok->stack[tok->depth].saved_state = json_tokener_state_finish;
  tok->stack[tok->depth].state = json_tokener_state_eatws;
  goto redo_char;
}


----------------------------
void helper_helper_helper_json_tokener_parse_ex_1_16_2(char * const c_ref, struct json_tokener * const tok, const char * const str, int len, unsigned int * const nBytesp, unsigned int str_idx)
{
  char c = *c_ref;
  const char *case_start = str;
  int case_len = 0;
  int is_exponent = 0;
  int neg_sign_ok = 1;
  int pos_sign_ok = 0;
  if (tok->pb->bpos > 0)
  {
    helper_helper_helper_helper_json_tokener_parse_ex_1_16_2_1(&is_exponent, &neg_sign_ok, &pos_sign_ok, tok);
  }
  while (c && ((((((c >= '0') && (c <= '9')) || ((!is_exponent) && ((c == 'e') || (c == 'E')))) || (neg_sign_ok && (c == '-'))) || (pos_sign_ok && (c == '+'))) || ((!tok->is_double) && (c == '.'))))
  {
    helper_helper_helper_helper_json_tokener_parse_ex_1_16_2_2(&c, &case_len, &is_exponent, &neg_sign_ok, &pos_sign_ok, tok, str, len, nBytesp, str_idx, case_start);
  }

  if ((((((((tok->depth > 0) && (c != ',')) && (c != ']')) && (c != '}')) && (c != '/')) && (c != 'I')) && (c != 'i')) && (!is_ws_char(c)))
  {
    tok->err = json_tokener_error_parse_number;
    goto out;
  }
  if (case_len > 0)
  {
    do
    {
      if (printbuf_memappend(tok->pb, case_start, case_len) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
  }
  if (((tok->pb->buf[0] == '-') && (case_len <= 1)) && ((c == 'i') || (c == 'I')))
  {
    tok->stack[tok->depth].state = json_tokener_state_inf;
    tok->st_pos = 0;
    goto redo_char;
  }
  if (tok->is_double && (!(tok->flags & 0x01)))
  {
    while (tok->pb->bpos > 1)
    {
      char last_char = tok->pb->buf[tok->pb->bpos - 1];
      if ((((last_char != 'e') && (last_char != 'E')) && (last_char != '-')) && (last_char != '+'))
      {
        break;
      }
      tok->pb->buf[tok->pb->bpos - 1] = '\0';
      tok->pb->bpos -= 1;
    }

  }
  *c_ref = c;
}


----------------------------
None
----------------------------
***/


// hint:  ['str_idx_ref is a mutable refrence to unsigned int', 'obj_idx_ref is a mutable refrence to unsigned int', 'c_ref is a mutable refrence to char']
void helper_json_tokener_parse_ex_1(unsigned int * const str_idx_ref, unsigned int * const obj_idx_ref, char * const c_ref, struct json_tokener * const tok, const char * const str, int len, struct json_object * const obj, unsigned int * const nBytesp)
{
  unsigned int str_idx = *str_idx_ref;
  unsigned int obj_idx = *obj_idx_ref;
  char c = *c_ref;
  redo_char:
  switch (tok->stack[tok->depth].state)
  {
    case json_tokener_state_eatws:
    {
      helper_helper_json_tokener_parse_ex_1_4(&c, tok, str, len, nBytesp, str_idx);
    }

    case json_tokener_state_start:
    {
      helper_helper_json_tokener_parse_ex_1_14(tok, c);
    }

    case json_tokener_state_finish:
    {
      if (tok->depth == 0)
      {
        goto out;
      }
      obj_idx = json_object_get(tok->stack[tok->depth].current);
      json_tokener_reset_level(tok, tok->depth);
      tok->depth -= 1;
      goto redo_char;
    }

    case json_tokener_state_inf:
    {
      helper_helper_json_tokener_parse_ex_1_8(&str_idx, &c, tok, str, len, nBytesp);
    }

    case json_tokener_state_null:
    {
      helper_helper_json_tokener_parse_ex_1_9(tok, c);
    }

    case json_tokener_state_comment_start:
    {
      if (c == '*')
      {
        tok->stack[tok->depth].state = json_tokener_state_comment;
      }
      else
        if (c == '/')
      {
        tok->stack[tok->depth].state = json_tokener_state_comment_eol;
      }
      else
      {
        tok->err = json_tokener_error_parse_comment;
        goto out;
      }
      do
      {
        if (printbuf_memappend(tok->pb, &c, 1) < 0)
        {
          tok->err = json_tokener_error_memory;
          goto out;
        }
      }
      while (0);
      break;
    }

    case json_tokener_state_comment:
    {
      helper_helper_json_tokener_parse_ex_1_5(&c, tok, str, len, nBytesp, str_idx);
    }

    case json_tokener_state_comment_eol:
    {
      helper_helper_json_tokener_parse_ex_1_7(&c, tok, str, len, nBytesp, str_idx);
    }

    case json_tokener_state_comment_end:
    {
      do
      {
        if (printbuf_memappend(tok->pb, &c, 1) < 0)
        {
          tok->err = json_tokener_error_memory;
          goto out;
        }
      }
      while (0);
      if (c == '/')
      {
        if (0)
        {
          mc_debug("json_tokener_comment: %s\n", tok->pb->buf);
        }
        tok->stack[tok->depth].state = json_tokener_state_eatws;
      }
      else
      {
        tok->stack[tok->depth].state = json_tokener_state_comment;
      }
      break;
    }

    case json_tokener_state_string:
    {
      helper_helper_json_tokener_parse_ex_1_12(&c, tok, str, len, nBytesp, str_idx);
    }

    case json_tokener_state_string_escape:
    {
      helper_helper_json_tokener_parse_ex_1_13(tok, c);
    }

    case json_tokener_state_escape_unicode:
    {
      helper_helper_json_tokener_parse_ex_1_15(&str_idx, &c, tok, str, len, nBytesp);
    }

    case json_tokener_state_escape_unicode_need_escape:
    {
      helper_helper_json_tokener_parse_ex_1_1(tok, c);
    }

    case json_tokener_state_escape_unicode_need_u:
    {
      helper_helper_json_tokener_parse_ex_1_2(tok, c);
    }

    case json_tokener_state_boolean:
    {
      helper_helper_json_tokener_parse_ex_1_11(tok, c);
    }

    case json_tokener_state_number:
    {
      helper_helper_json_tokener_parse_ex_1_16(&c, tok, str, len, nBytesp, str_idx);
    }

    case json_tokener_state_array_after_sep:

    case json_tokener_state_array:
    {
      helper_helper_json_tokener_parse_ex_1_6(tok, c);
    }

    case json_tokener_state_array_add:
    {
      if (json_object_array_add(tok->stack[tok->depth].current, obj) != 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
      tok->stack[tok->depth].saved_state = json_tokener_state_array_sep;
      tok->stack[tok->depth].state = json_tokener_state_eatws;
      goto redo_char;
    }

    case json_tokener_state_array_sep:
    {
      if (c == ']')
      {
        json_object_array_shrink(tok->stack[tok->depth].current, 0);
        tok->stack[tok->depth].saved_state = json_tokener_state_finish;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
      }
      else
        if (c == ',')
      {
        tok->stack[tok->depth].saved_state = json_tokener_state_array_after_sep;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
      }
      else
      {
        tok->err = json_tokener_error_parse_array;
        goto out;
      }
      break;
    }

    case json_tokener_state_object_field_start:

    case json_tokener_state_object_field_start_after_sep:
    {
      helper_helper_json_tokener_parse_ex_1_3(tok, c);
    }

    case json_tokener_state_object_field:
    {
      helper_helper_json_tokener_parse_ex_1_10(&c, tok, str, len, nBytesp, str_idx);
    }

    case json_tokener_state_object_field_end:
    {
      if (c == ':')
      {
        tok->stack[tok->depth].saved_state = json_tokener_state_object_value;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
      }
      else
      {
        tok->err = json_tokener_error_parse_object_key_sep;
        goto out;
      }
      break;
    }

    case json_tokener_state_object_value:
    {
      if (tok->depth >= (tok->max_depth - 1))
      {
        tok->err = json_tokener_error_depth;
        goto out;
      }
      tok->stack[tok->depth].state = json_tokener_state_object_value_add;
      tok->depth += 1;
      json_tokener_reset_level(tok, tok->depth);
      goto redo_char;
    }

    case json_tokener_state_object_value_add:
    {
      if (json_object_object_add(tok->stack[tok->depth].current, tok->stack[tok->depth].obj_field_name, obj) != 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
      free(tok->stack[tok->depth].obj_field_name);
      tok->stack[tok->depth].obj_field_name = 0;
      tok->stack[tok->depth].saved_state = json_tokener_state_object_sep;
      tok->stack[tok->depth].state = json_tokener_state_eatws;
      goto redo_char;
    }

    case json_tokener_state_object_sep:
    {
      if (c == '}')
      {
        tok->stack[tok->depth].saved_state = json_tokener_state_finish;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
      }
      else
        if (c == ',')
      {
        tok->stack[tok->depth].saved_state = json_tokener_state_object_field_start_after_sep;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
      }
      else
      {
        tok->err = json_tokener_error_parse_object_value_sep;
        goto out;
      }
      break;
    }

  }


  str_idx += 1;
  (void) ((++(&str[str_idx]), tok->char_offset++, c));
  if (!c)
  {
    break;
  }
  *str_idx_ref = str_idx;
  *obj_idx_ref = obj_idx;
  *c_ref = c;
}


/*** DEPENDENCIES:
void helper_helper_json_tokener_parse_ex_1_1(struct json_tokener * const tok, char c)
{
  if ((!c) || (c != '\\'))
  {
    do
    {
      if (printbuf_memappend(tok->pb, (char *) utf8_replacement_char, 3) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
    tok->high_surrogate = 0;
    tok->ucs_char = 0;
    tok->st_pos = 0;
    tok->stack[tok->depth].state = tok->stack[tok->depth].saved_state;
    goto redo_char;
  }
  tok->stack[tok->depth].state = json_tokener_state_escape_unicode_need_u;
  break;
}


----------------------------
void helper_helper_json_tokener_parse_ex_1_2(struct json_tokener * const tok, char c)
{
  if ((!c) || (c != 'u'))
  {
    do
    {
      if (printbuf_memappend(tok->pb, (char *) utf8_replacement_char, 3) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
    tok->high_surrogate = 0;
    tok->ucs_char = 0;
    tok->st_pos = 0;
    tok->stack[tok->depth].state = json_tokener_state_string_escape;
    goto redo_char;
  }
  tok->stack[tok->depth].state = json_tokener_state_escape_unicode;
  break;
}


----------------------------
void helper_helper_json_tokener_parse_ex_1_9(struct json_tokener * const tok, char c)
{
  {
    int size;
    int size_nan;
    do
    {
      if (printbuf_memappend(tok->pb, &c, 1) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
    size = ((tok->st_pos + 1) < json_null_str_len) ? (tok->st_pos + 1) : (json_null_str_len);
    size_nan = ((tok->st_pos + 1) < json_nan_str_len) ? (tok->st_pos + 1) : (json_nan_str_len);
    if (((!(tok->flags & 0x01)) && (strncasecmp(json_null_str, tok->pb->buf, size) == 0)) || (strncmp(json_null_str, tok->pb->buf, size) == 0))
    {
      if (tok->st_pos == json_null_str_len)
      {
        tok->stack[tok->depth].current = 0;
        tok->stack[tok->depth].saved_state = json_tokener_state_finish;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
        goto redo_char;
      }
    }
    else
      if (((!(tok->flags & 0x01)) && (strncasecmp(json_nan_str, tok->pb->buf, size_nan) == 0)) || (strncmp(json_nan_str, tok->pb->buf, size_nan) == 0))
    {
      if (tok->st_pos == json_nan_str_len)
      {
        tok->stack[tok->depth].current = json_object_new_double(nan(""));
        if (tok->stack[tok->depth].current == 0)
        {
          tok->err = json_tokener_error_memory;
          goto out;
        }
        tok->stack[tok->depth].saved_state = json_tokener_state_finish;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
        goto redo_char;
      }
    }
    else
    {
      tok->err = json_tokener_error_parse_null;
      goto out;
    }
    tok->st_pos += 1;
  }
  break;
}


----------------------------
struct json_object *json_object_get(struct json_object *jso)
{
  if (!jso)
  {
    return jso;
  }
  assert(jso->_ref_count < UINT32_MAX);
  jso->_ref_count += 1;
  return jso;
}


----------------------------
void helper_helper_json_tokener_parse_ex_1_4(char * const c_ref, struct json_tokener * const tok, const char * const str, int len, unsigned int * const nBytesp, unsigned int str_idx)
{
  char c = *c_ref;
  while (is_ws_char(c))
  {
    if ((!((++(&str[str_idx]), tok->char_offset++, c))) || (!((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = *(&str[str_idx]), 1))))))
    {
      goto out;
    }
  }

  if ((c == '/') && (!(tok->flags & 0x01)))
  {
    printbuf_reset(tok->pb);
    do
    {
      if (printbuf_memappend(tok->pb, &c, 1) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
    tok->stack[tok->depth].state = json_tokener_state_comment_start;
  }
  else
  {
    tok->stack[tok->depth].state = tok->stack[tok->depth].saved_state;
    goto redo_char;
  }
  break;
  *c_ref = c;
}


----------------------------
static void json_tokener_reset_level(struct json_tokener *tok, int depth)
{
  tok->stack[depth].state = json_tokener_state_eatws;
  tok->stack[depth].saved_state = json_tokener_state_start;
  json_object_put(tok->stack[depth].current);
  tok->stack[depth].current = 0;
  free(tok->stack[depth].obj_field_name);
  tok->stack[depth].obj_field_name = 0;
}


----------------------------
void helper_helper_json_tokener_parse_ex_1_11(struct json_tokener * const tok, char c)
{
  {
    int size1;
    int size2;
    do
    {
      if (printbuf_memappend(tok->pb, &c, 1) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
    size1 = ((tok->st_pos + 1) < json_true_str_len) ? (tok->st_pos + 1) : (json_true_str_len);
    size2 = ((tok->st_pos + 1) < json_false_str_len) ? (tok->st_pos + 1) : (json_false_str_len);
    if (((!(tok->flags & 0x01)) && (strncasecmp(json_true_str, tok->pb->buf, size1) == 0)) || (strncmp(json_true_str, tok->pb->buf, size1) == 0))
    {
      if (tok->st_pos == json_true_str_len)
      {
        tok->stack[tok->depth].current = json_object_new_boolean(1);
        if (tok->stack[tok->depth].current == 0)
        {
          tok->err = json_tokener_error_memory;
          goto out;
        }
        tok->stack[tok->depth].saved_state = json_tokener_state_finish;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
        goto redo_char;
      }
    }
    else
      if (((!(tok->flags & 0x01)) && (strncasecmp(json_false_str, tok->pb->buf, size2) == 0)) || (strncmp(json_false_str, tok->pb->buf, size2) == 0))
    {
      if (tok->st_pos == json_false_str_len)
      {
        tok->stack[tok->depth].current = json_object_new_boolean(0);
        if (tok->stack[tok->depth].current == 0)
        {
          tok->err = json_tokener_error_memory;
          goto out;
        }
        tok->stack[tok->depth].saved_state = json_tokener_state_finish;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
        goto redo_char;
      }
    }
    else
    {
      tok->err = json_tokener_error_parse_boolean;
      goto out;
    }
    tok->st_pos += 1;
  }
  break;
}


----------------------------
void helper_helper_json_tokener_parse_ex_1_15(unsigned int * const str_idx_ref, char * const c_ref, struct json_tokener * const tok, const char * const str, int len, unsigned int * const nBytesp)
{
  unsigned int str_idx = *str_idx_ref;
  char c = *c_ref;
  {
    helper_helper_helper_json_tokener_parse_ex_1_15_1(&str_idx, &c, tok, str, len, nBytesp);
  }
  break;
  *str_idx_ref = str_idx;
  *c_ref = c;
}


----------------------------
void helper_helper_json_tokener_parse_ex_1_10(char * const c_ref, struct json_tokener * const tok, const char * const str, int len, unsigned int * const nBytesp, unsigned int str_idx)
{
  char c = *c_ref;
  {
    helper_helper_helper_json_tokener_parse_ex_1_10_1(&c, tok, str, len, nBytesp, str_idx);
  }
  break;
  *c_ref = c;
}


----------------------------
int json_object_object_add(struct json_object *jso, const char *key, struct json_object *val)
{
  return json_object_object_add_ex(jso, key, val, 0);
}


----------------------------
int json_object_array_shrink(struct json_object *jso, int empty_slots)
{
  if (empty_slots < 0)
  {
    json_abort("json_object_array_shrink called with negative empty_slots");
  }
  return array_list_shrink(JC_ARRAY(jso)->c_array, empty_slots);
}


----------------------------
None
----------------------------
void helper_helper_json_tokener_parse_ex_1_13(struct json_tokener * const tok, char c)
{
  switch (c)
  {
    case '"':

    case '\\':

    case '/':
    {
      do
      {
        if (printbuf_memappend(tok->pb, &c, 1) < 0)
        {
          tok->err = json_tokener_error_memory;
          goto out;
        }
      }
      while (0);
      tok->stack[tok->depth].state = tok->stack[tok->depth].saved_state;
      break;
    }

    case 'b':

    case 'n':

    case 'r':

    case 't':

    case 'f':
    {
      helper_helper_helper_json_tokener_parse_ex_1_13_1(tok, c);
    }

    case 'u':
    {
      tok->ucs_char = 0;
      tok->st_pos = 0;
      tok->stack[tok->depth].state = json_tokener_state_escape_unicode;
      break;
    }

    default:
    {
      tok->err = json_tokener_error_parse_string;
      goto out;
    }

  }

  break;
}


----------------------------
void helper_helper_json_tokener_parse_ex_1_5(char * const c_ref, struct json_tokener * const tok, const char * const str, int len, unsigned int * const nBytesp, unsigned int str_idx)
{
  char c = *c_ref;
  {
    const char *case_start = str;
    while (c != '*')
    {
      if ((!((++(&str[str_idx]), tok->char_offset++, c))) || (!((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = *(&str[str_idx]), 1))))))
      {
        do
        {
          if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
          {
            tok->err = json_tokener_error_memory;
            goto out;
          }
        }
        while (0);
        goto out;
      }
    }

    do
    {
      if (printbuf_memappend(tok->pb, case_start, (1 + (&str[str_idx])) - case_start) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
    tok->stack[tok->depth].state = json_tokener_state_comment_end;
  }
  break;
  *c_ref = c;
}


----------------------------
void helper_helper_json_tokener_parse_ex_1_8(unsigned int * const str_idx_ref, char * const c_ref, struct json_tokener * const tok, const char * const str, int len, unsigned int * const nBytesp)
{
  unsigned int str_idx = *str_idx_ref;
  char c = *c_ref;
  {
    int is_negative = 0;
    while (tok->st_pos < ((int) json_inf_str_len))
    {
      char inf_char = str[str_idx];
      if ((inf_char != json_inf_str[tok->st_pos]) && ((tok->flags & 0x01) || (inf_char != json_inf_str_invert[tok->st_pos])))
      {
        tok->err = json_tokener_error_parse_unexpected;
        goto out;
      }
      tok->st_pos += 1;
      str_idx += 1;
      (void) ((++(&str[str_idx]), tok->char_offset++, c));
      if (!((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = *(&str[str_idx]), 1)))))
      {
        goto out;
      }
    }

    if ((tok->pb->bpos > 0) && ((*tok->pb->buf) == '-'))
    {
      is_negative = 1;
    }
    tok->stack[tok->depth].current = json_object_new_double((is_negative) ? (-INFINITY) : (INFINITY));
    if (tok->stack[tok->depth].current == 0)
    {
      tok->err = json_tokener_error_memory;
      goto out;
    }
    tok->stack[tok->depth].saved_state = json_tokener_state_finish;
    tok->stack[tok->depth].state = json_tokener_state_eatws;
    goto redo_char;
  }
  break;
  *str_idx_ref = str_idx;
  *c_ref = c;
}


----------------------------
int printbuf_memappend(struct printbuf *p, const char *buf, int size)
{
  if ((size < 0) || (size > ((2147483647 - p->bpos) - 1)))
  {
    errno = EFBIG;
    return -1;
  }
  if (p->size <= ((p->bpos + size) + 1))
  {
    if (printbuf_extend(p, (p->bpos + size) + 1) < 0)
    {
      return -1;
    }
  }
  memcpy(p->buf + p->bpos, buf, size);
  p->bpos += size;
  p->buf[p->bpos] = '\0';
  return size;
}


----------------------------
void helper_helper_json_tokener_parse_ex_1_3(struct json_tokener * const tok, char c)
{
  if (c == '}')
  {
    if ((tok->stack[tok->depth].state == json_tokener_state_object_field_start_after_sep) && (tok->flags & 0x01))
    {
      tok->err = json_tokener_error_parse_unexpected;
      goto out;
    }
    tok->stack[tok->depth].saved_state = json_tokener_state_finish;
    tok->stack[tok->depth].state = json_tokener_state_eatws;
  }
  else
    if ((c == '"') || (c == '\''))
  {
    tok->quote_char = c;
    printbuf_reset(tok->pb);
    tok->stack[tok->depth].state = json_tokener_state_object_field;
  }
  else
  {
    tok->err = json_tokener_error_parse_object_key_name;
    goto out;
  }
  break;
}


----------------------------
void helper_helper_json_tokener_parse_ex_1_6(struct json_tokener * const tok, char c)
{
  if (c == ']')
  {
    json_object_array_shrink(tok->stack[tok->depth].current, 0);
    if ((tok->stack[tok->depth].state == json_tokener_state_array_after_sep) && (tok->flags & 0x01))
    {
      tok->err = json_tokener_error_parse_unexpected;
      goto out;
    }
    tok->stack[tok->depth].saved_state = json_tokener_state_finish;
    tok->stack[tok->depth].state = json_tokener_state_eatws;
  }
  else
  {
    if (tok->depth >= (tok->max_depth - 1))
    {
      tok->err = json_tokener_error_depth;
      goto out;
    }
    tok->stack[tok->depth].state = json_tokener_state_array_add;
    tok->depth += 1;
    json_tokener_reset_level(tok, tok->depth);
    goto redo_char;
  }
  break;
}


----------------------------
void mc_debug(const char *msg, ...)
{
  va_list ap;
  if (_debug)
  {
    __builtin_va_start(ap);
    if (_syslog)
    {
      vsyslog(LOG_DEBUG, msg, ap);
    }
    else
      vprintf(msg, ap);
    ;
  }
}


----------------------------
void helper_helper_json_tokener_parse_ex_1_7(char * const c_ref, struct json_tokener * const tok, const char * const str, int len, unsigned int * const nBytesp, unsigned int str_idx)
{
  char c = *c_ref;
  {
    const char *case_start = str;
    while (c != '\n')
    {
      if ((!((++(&str[str_idx]), tok->char_offset++, c))) || (!((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = *(&str[str_idx]), 1))))))
      {
        do
        {
          if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
          {
            tok->err = json_tokener_error_memory;
            goto out;
          }
        }
        while (0);
        goto out;
      }
    }

    do
    {
      if (printbuf_memappend(tok->pb, case_start, (&str[str_idx]) - case_start) < 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
    }
    while (0);
    if (0)
    {
      mc_debug("json_tokener_comment: %s\n", tok->pb->buf);
    }
    tok->stack[tok->depth].state = json_tokener_state_eatws;
  }
  break;
  *c_ref = c;
}


----------------------------
void helper_helper_json_tokener_parse_ex_1_12(char * const c_ref, struct json_tokener * const tok, const char * const str, int len, unsigned int * const nBytesp, unsigned int str_idx)
{
  char c = *c_ref;
  {
    helper_helper_helper_json_tokener_parse_ex_1_12_1(&c, tok, str, len, nBytesp, str_idx);
  }
  break;
  *c_ref = c;
}


----------------------------
void helper_helper_json_tokener_parse_ex_1_14(struct json_tokener * const tok, char c)
{
  switch (c)
  {
    case '{':
    {
      tok->stack[tok->depth].state = json_tokener_state_eatws;
      tok->stack[tok->depth].saved_state = json_tokener_state_object_field_start;
      tok->stack[tok->depth].current = json_object_new_object();
      if (tok->stack[tok->depth].current == 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
      break;
    }

    case '[':
    {
      tok->stack[tok->depth].state = json_tokener_state_eatws;
      tok->stack[tok->depth].saved_state = json_tokener_state_array;
      tok->stack[tok->depth].current = json_object_new_array();
      if (tok->stack[tok->depth].current == 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
      break;
    }

    case 'I':

    case 'i':
    {
      tok->stack[tok->depth].state = json_tokener_state_inf;
      printbuf_reset(tok->pb);
      tok->st_pos = 0;
      goto redo_char;
    }

    case 'N':

    case 'n':
    {
      tok->stack[tok->depth].state = json_tokener_state_null;
      printbuf_reset(tok->pb);
      tok->st_pos = 0;
      goto redo_char;
    }

    case '\'':
    {
      if (tok->flags & 0x01)
      {
        tok->err = json_tokener_error_parse_unexpected;
        goto out;
      }
    }

    case '"':
    {
      tok->stack[tok->depth].state = json_tokener_state_string;
      printbuf_reset(tok->pb);
      tok->quote_char = c;
      break;
    }

    case 'T':

    case 't':

    case 'F':

    case 'f':
    {
      tok->stack[tok->depth].state = json_tokener_state_boolean;
      printbuf_reset(tok->pb);
      tok->st_pos = 0;
      goto redo_char;
    }

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

    case '-':
    {
      tok->stack[tok->depth].state = json_tokener_state_number;
      printbuf_reset(tok->pb);
      tok->is_double = 0;
      goto redo_char;
    }

    default:
    {
      tok->err = json_tokener_error_parse_unexpected;
      goto out;
    }

  }

  break;
}


----------------------------
void helper_helper_json_tokener_parse_ex_1_16(char * const c_ref, struct json_tokener * const tok, const char * const str, int len, unsigned int * const nBytesp, unsigned int str_idx)
{
  char c = *c_ref;
  {
    helper_helper_helper_json_tokener_parse_ex_1_16_2(&c, tok, str, len, nBytesp, str_idx);
  }
  {
    helper_helper_helper_json_tokener_parse_ex_1_16_1(tok);
  }
  break;
  *c_ref = c;
}


----------------------------
int json_object_array_add(struct json_object *jso, struct json_object *val)
{
  assert(json_object_get_type(jso) == json_type_array);
  return array_list_add(JC_ARRAY(jso)->c_array, val);
}


----------------------------
None
----------------------------
***/


struct json_object *json_tokener_parse_ex(struct json_tokener *tok, const char *str, int len)
{
  unsigned int str_idx = 0;
  struct json_object *obj = 0;
  unsigned int obj_idx = 0;
  char c = '\1';
  unsigned int nBytes = 0;
  unsigned int *nBytesp = &nBytes;
  locale_t oldlocale = uselocale(0);
  locale_t newloc;
  tok->char_offset = 0;
  tok->err = json_tokener_success;
  if ((len < (-1)) || ((len == (-1)) && (strlen(str) > INT32_MAX)))
  {
    tok->err = json_tokener_error_size;
    return 0;
  }
  {
    locale_t duploc = duplocale(oldlocale);
    if ((duploc == 0) && (errno == ENOMEM))
    {
      tok->err = json_tokener_error_memory;
      return 0;
    }
    newloc = newlocale(LC_NUMERIC_MASK, "C", duploc);
    if (newloc == 0)
    {
      tok->err = json_tokener_error_memory;
      freelocale(duploc);
      return 0;
    }
    uselocale(newloc);
  }
  while ((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = str[str_idx], 1))))
  {
    helper_json_tokener_parse_ex_1(&str_idx, &obj_idx, &c, tok, str, len, obj, nBytesp);
  }

  out:
  if ((tok->flags & 0x10) && (nBytes != 0))
  {
    tok->err = json_tokener_error_parse_utf8_string;
  }

  if (((c && (tok->stack[tok->depth].state == json_tokener_state_finish)) && (tok->depth == 0)) && ((tok->flags & (0x01 | 0x02)) == 0x01))
  {
    tok->err = json_tokener_error_parse_unexpected;
  }
  if (!c)
  {
    if ((tok->stack[tok->depth].state != json_tokener_state_finish) && (tok->stack[tok->depth].saved_state != json_tokener_state_finish))
    {
      tok->err = json_tokener_error_parse_eof;
    }
  }
  uselocale(oldlocale);
  freelocale(newloc);
  if (tok->err == json_tokener_success)
  {
    json_object *ret = json_object_get(tok->stack[tok->depth].current);
    int ii;
    for (ii = tok->depth; ii >= 0; ii -= 1)
    {
      json_tokener_reset_level(tok, ii);
    }

    return ret;
  }
  if (0)
  {
    mc_debug("json_tokener_parse_ex: error %s at offset %d\n", json_tokener_errors[tok->err], tok->char_offset);
  }
  return 0;
}


/*** DEPENDENCIES:
None
----------------------------
struct json_object *json_object_get(struct json_object *jso)
{
  if (!jso)
  {
    return jso;
  }
  assert(jso->_ref_count < UINT32_MAX);
  jso->_ref_count += 1;
  return jso;
}


----------------------------
void helper_json_tokener_parse_ex_1(unsigned int * const str_idx_ref, unsigned int * const obj_idx_ref, char * const c_ref, struct json_tokener * const tok, const char * const str, int len, struct json_object * const obj, unsigned int * const nBytesp)
{
  unsigned int str_idx = *str_idx_ref;
  unsigned int obj_idx = *obj_idx_ref;
  char c = *c_ref;
  redo_char:
  switch (tok->stack[tok->depth].state)
  {
    case json_tokener_state_eatws:
    {
      helper_helper_json_tokener_parse_ex_1_4(&c, tok, str, len, nBytesp, str_idx);
    }

    case json_tokener_state_start:
    {
      helper_helper_json_tokener_parse_ex_1_14(tok, c);
    }

    case json_tokener_state_finish:
    {
      if (tok->depth == 0)
      {
        goto out;
      }
      obj_idx = json_object_get(tok->stack[tok->depth].current);
      json_tokener_reset_level(tok, tok->depth);
      tok->depth -= 1;
      goto redo_char;
    }

    case json_tokener_state_inf:
    {
      helper_helper_json_tokener_parse_ex_1_8(&str_idx, &c, tok, str, len, nBytesp);
    }

    case json_tokener_state_null:
    {
      helper_helper_json_tokener_parse_ex_1_9(tok, c);
    }

    case json_tokener_state_comment_start:
    {
      if (c == '*')
      {
        tok->stack[tok->depth].state = json_tokener_state_comment;
      }
      else
        if (c == '/')
      {
        tok->stack[tok->depth].state = json_tokener_state_comment_eol;
      }
      else
      {
        tok->err = json_tokener_error_parse_comment;
        goto out;
      }
      do
      {
        if (printbuf_memappend(tok->pb, &c, 1) < 0)
        {
          tok->err = json_tokener_error_memory;
          goto out;
        }
      }
      while (0);
      break;
    }

    case json_tokener_state_comment:
    {
      helper_helper_json_tokener_parse_ex_1_5(&c, tok, str, len, nBytesp, str_idx);
    }

    case json_tokener_state_comment_eol:
    {
      helper_helper_json_tokener_parse_ex_1_7(&c, tok, str, len, nBytesp, str_idx);
    }

    case json_tokener_state_comment_end:
    {
      do
      {
        if (printbuf_memappend(tok->pb, &c, 1) < 0)
        {
          tok->err = json_tokener_error_memory;
          goto out;
        }
      }
      while (0);
      if (c == '/')
      {
        if (0)
        {
          mc_debug("json_tokener_comment: %s\n", tok->pb->buf);
        }
        tok->stack[tok->depth].state = json_tokener_state_eatws;
      }
      else
      {
        tok->stack[tok->depth].state = json_tokener_state_comment;
      }
      break;
    }

    case json_tokener_state_string:
    {
      helper_helper_json_tokener_parse_ex_1_12(&c, tok, str, len, nBytesp, str_idx);
    }

    case json_tokener_state_string_escape:
    {
      helper_helper_json_tokener_parse_ex_1_13(tok, c);
    }

    case json_tokener_state_escape_unicode:
    {
      helper_helper_json_tokener_parse_ex_1_15(&str_idx, &c, tok, str, len, nBytesp);
    }

    case json_tokener_state_escape_unicode_need_escape:
    {
      helper_helper_json_tokener_parse_ex_1_1(tok, c);
    }

    case json_tokener_state_escape_unicode_need_u:
    {
      helper_helper_json_tokener_parse_ex_1_2(tok, c);
    }

    case json_tokener_state_boolean:
    {
      helper_helper_json_tokener_parse_ex_1_11(tok, c);
    }

    case json_tokener_state_number:
    {
      helper_helper_json_tokener_parse_ex_1_16(&c, tok, str, len, nBytesp, str_idx);
    }

    case json_tokener_state_array_after_sep:

    case json_tokener_state_array:
    {
      helper_helper_json_tokener_parse_ex_1_6(tok, c);
    }

    case json_tokener_state_array_add:
    {
      if (json_object_array_add(tok->stack[tok->depth].current, obj) != 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
      tok->stack[tok->depth].saved_state = json_tokener_state_array_sep;
      tok->stack[tok->depth].state = json_tokener_state_eatws;
      goto redo_char;
    }

    case json_tokener_state_array_sep:
    {
      if (c == ']')
      {
        json_object_array_shrink(tok->stack[tok->depth].current, 0);
        tok->stack[tok->depth].saved_state = json_tokener_state_finish;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
      }
      else
        if (c == ',')
      {
        tok->stack[tok->depth].saved_state = json_tokener_state_array_after_sep;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
      }
      else
      {
        tok->err = json_tokener_error_parse_array;
        goto out;
      }
      break;
    }

    case json_tokener_state_object_field_start:

    case json_tokener_state_object_field_start_after_sep:
    {
      helper_helper_json_tokener_parse_ex_1_3(tok, c);
    }

    case json_tokener_state_object_field:
    {
      helper_helper_json_tokener_parse_ex_1_10(&c, tok, str, len, nBytesp, str_idx);
    }

    case json_tokener_state_object_field_end:
    {
      if (c == ':')
      {
        tok->stack[tok->depth].saved_state = json_tokener_state_object_value;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
      }
      else
      {
        tok->err = json_tokener_error_parse_object_key_sep;
        goto out;
      }
      break;
    }

    case json_tokener_state_object_value:
    {
      if (tok->depth >= (tok->max_depth - 1))
      {
        tok->err = json_tokener_error_depth;
        goto out;
      }
      tok->stack[tok->depth].state = json_tokener_state_object_value_add;
      tok->depth += 1;
      json_tokener_reset_level(tok, tok->depth);
      goto redo_char;
    }

    case json_tokener_state_object_value_add:
    {
      if (json_object_object_add(tok->stack[tok->depth].current, tok->stack[tok->depth].obj_field_name, obj) != 0)
      {
        tok->err = json_tokener_error_memory;
        goto out;
      }
      free(tok->stack[tok->depth].obj_field_name);
      tok->stack[tok->depth].obj_field_name = 0;
      tok->stack[tok->depth].saved_state = json_tokener_state_object_sep;
      tok->stack[tok->depth].state = json_tokener_state_eatws;
      goto redo_char;
    }

    case json_tokener_state_object_sep:
    {
      if (c == '}')
      {
        tok->stack[tok->depth].saved_state = json_tokener_state_finish;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
      }
      else
        if (c == ',')
      {
        tok->stack[tok->depth].saved_state = json_tokener_state_object_field_start_after_sep;
        tok->stack[tok->depth].state = json_tokener_state_eatws;
      }
      else
      {
        tok->err = json_tokener_error_parse_object_value_sep;
        goto out;
      }
      break;
    }

  }


  str_idx += 1;
  (void) ((++(&str[str_idx]), tok->char_offset++, c));
  if (!c)
  {
    break;
  }
  *str_idx_ref = str_idx;
  *obj_idx_ref = obj_idx;
  *c_ref = c;
}


----------------------------
static void json_tokener_reset_level(struct json_tokener *tok, int depth)
{
  tok->stack[depth].state = json_tokener_state_eatws;
  tok->stack[depth].saved_state = json_tokener_state_start;
  json_object_put(tok->stack[depth].current);
  tok->stack[depth].current = 0;
  free(tok->stack[depth].obj_field_name);
  tok->stack[depth].obj_field_name = 0;
}


----------------------------
void mc_debug(const char *msg, ...)
{
  va_list ap;
  if (_debug)
  {
    __builtin_va_start(ap);
    if (_syslog)
    {
      vsyslog(LOG_DEBUG, msg, ap);
    }
    else
      vprintf(msg, ap);
    ;
  }
}


----------------------------
static const char *json_tokener_errors[] = {"success", "continue", "nesting too deep", "unexpected end of data", "unexpected character", "null expected", "boolean expected", "number expected", "array value separator ',' expected", "quoted object property name expected", "object property name separator ':' expected", "object value separator ',' expected", "invalid string sequence", "expected comment", "invalid utf-8 string", "buffer size overflow", "out of memory"}
----------------------------
static json_bool json_tokener_validate_utf8(const char c, unsigned int *nBytes)
{
  unsigned char chr = c;
  if ((*nBytes) == 0)
  {
    if (chr >= 0x80)
    {
      if ((chr & 0xe0) == 0xc0)
      {
        *nBytes = 1;
      }
      else
        if ((chr & 0xf0) == 0xe0)
      {
        *nBytes = 2;
      }
      else
        if ((chr & 0xf8) == 0xf0)
      {
        *nBytes = 3;
      }
      else
        return 0;
    }
  }
  else
  {
    if ((chr & 0xC0) != 0x80)
    {
      return 0;
    }
    *nBytes -= 1;
  }
  return 1;
}


----------------------------
None
----------------------------
***/


void json_tokener_reset(struct json_tokener *tok)
{
  int i;
  if (!tok)
  {
    return;
  }
  for (i = tok->depth; i >= 0; i -= 1)
  {
    json_tokener_reset_level(tok, i);
  }

  tok->depth = 0;
  tok->err = json_tokener_success;
}


/*** DEPENDENCIES:
static void json_tokener_reset_level(struct json_tokener *tok, int depth)
{
  tok->stack[depth].state = json_tokener_state_eatws;
  tok->stack[depth].saved_state = json_tokener_state_start;
  json_object_put(tok->stack[depth].current);
  tok->stack[depth].current = 0;
  free(tok->stack[depth].obj_field_name);
  tok->stack[depth].obj_field_name = 0;
}


----------------------------
None
----------------------------
***/


void json_tokener_free(struct json_tokener *tok)
{
  if (!tok)
  {
    return;
  }
  json_tokener_reset(tok);
  if (tok->pb)
  {
    printbuf_free(tok->pb);
  }
  free(tok->stack);
  free(tok);
}


/*** DEPENDENCIES:
void printbuf_free(struct printbuf *p)
{
  if (p)
  {
    free(p->buf);
    free(p);
  }
}


----------------------------
void json_tokener_reset(struct json_tokener *tok)
{
  int i;
  if (!tok)
  {
    return;
  }
  for (i = tok->depth; i >= 0; i -= 1)
  {
    json_tokener_reset_level(tok, i);
  }

  tok->depth = 0;
  tok->err = json_tokener_success;
}


----------------------------
None
----------------------------
***/


struct json_tokener *json_tokener_new_ex(int depth)
{
  struct json_tokener *tok;
  unsigned int tok_idx = 0;
  if (depth < 1)
  {
    return 0;
  }
  tok_idx = (struct json_tokener *) calloc(1, sizeof(struct json_tokener));
  if (!(&tok[tok_idx]))
  {
    return 0;
  }
  tok->stack = (struct json_tokener_srec *) calloc(depth, sizeof(struct json_tokener_srec));
  if (!tok->stack)
  {
    free(tok);
    return 0;
  }
  tok->pb = printbuf_new();
  if (!tok->pb)
  {
    free(tok->stack);
    free(tok);
    return 0;
  }
  tok->max_depth = depth;
  json_tokener_reset(tok);
  return tok;
}


/*** DEPENDENCIES:
struct printbuf *printbuf_new(void)
{
  struct printbuf *p;
  unsigned int p_idx = 0;
  p_idx = (struct printbuf *) calloc(1, sizeof(struct printbuf));
  if (!(&p[p_idx]))
  {
    return 0;
  }
  p->size = 32;
  p->bpos = 0;
  if (!(p->buf = (char *) malloc(p->size)))
  {
    free(p);
    return 0;
  }
  p->buf[0] = '\0';
  return p;
}


----------------------------
void json_tokener_reset(struct json_tokener *tok)
{
  int i;
  if (!tok)
  {
    return;
  }
  for (i = tok->depth; i >= 0; i -= 1)
  {
    json_tokener_reset_level(tok, i);
  }

  tok->depth = 0;
  tok->err = json_tokener_success;
}


----------------------------
None
----------------------------
***/


struct json_tokener *json_tokener_new(void)
{
  return json_tokener_new_ex(32);
}


/*** DEPENDENCIES:
struct json_tokener *json_tokener_new_ex(int depth)
{
  struct json_tokener *tok;
  unsigned int tok_idx = 0;
  if (depth < 1)
  {
    return 0;
  }
  tok_idx = (struct json_tokener *) calloc(1, sizeof(struct json_tokener));
  if (!(&tok[tok_idx]))
  {
    return 0;
  }
  tok->stack = (struct json_tokener_srec *) calloc(depth, sizeof(struct json_tokener_srec));
  if (!tok->stack)
  {
    free(tok);
    return 0;
  }
  tok->pb = printbuf_new();
  if (!tok->pb)
  {
    free(tok->stack);
    free(tok);
    return 0;
  }
  tok->max_depth = depth;
  json_tokener_reset(tok);
  return tok;
}


----------------------------
None
----------------------------
***/


struct json_object *json_tokener_parse_verbose(const char *str, enum json_tokener_error *error)
{
  struct json_tokener *tok;
  unsigned int tok_idx = 0;
  struct json_object *obj;
  unsigned int obj_idx = 0;
  tok_idx = json_tokener_new();
  if (!(&tok[tok_idx]))
  {
    *error = json_tokener_error_memory;
    return 0;
  }
  obj_idx = json_tokener_parse_ex(tok, str, -1);
  *error = tok->err;
  if (tok->err != json_tokener_success)
  {
    if ((&obj[obj_idx]) != 0)
    {
      json_object_put(obj);
    }
    obj_idx = 0;
  }
  json_tokener_free(tok);
  return obj;
}


/*** DEPENDENCIES:
None
----------------------------
struct json_object *json_tokener_parse_ex(struct json_tokener *tok, const char *str, int len)
{
  unsigned int str_idx = 0;
  struct json_object *obj = 0;
  unsigned int obj_idx = 0;
  char c = '\1';
  unsigned int nBytes = 0;
  unsigned int *nBytesp = &nBytes;
  locale_t oldlocale = uselocale(0);
  locale_t newloc;
  tok->char_offset = 0;
  tok->err = json_tokener_success;
  if ((len < (-1)) || ((len == (-1)) && (strlen(str) > INT32_MAX)))
  {
    tok->err = json_tokener_error_size;
    return 0;
  }
  {
    locale_t duploc = duplocale(oldlocale);
    if ((duploc == 0) && (errno == ENOMEM))
    {
      tok->err = json_tokener_error_memory;
      return 0;
    }
    newloc = newlocale(LC_NUMERIC_MASK, "C", duploc);
    if (newloc == 0)
    {
      tok->err = json_tokener_error_memory;
      freelocale(duploc);
      return 0;
    }
    uselocale(newloc);
  }
  while ((tok->char_offset == len) ? ((((tok->depth == 0) && (tok->stack[tok->depth].state == json_tokener_state_eatws)) && (tok->stack[tok->depth].saved_state == json_tokener_state_finish)) ? ((tok->err = json_tokener_success, 0)) : ((tok->err = json_tokener_continue, 0))) : (((tok->flags & 0x10) && (!json_tokener_validate_utf8(*(&str[str_idx]), nBytesp))) ? ((tok->err = json_tokener_error_parse_utf8_string, 0)) : ((c = str[str_idx], 1))))
  {
    helper_json_tokener_parse_ex_1(&str_idx, &obj_idx, &c, tok, str, len, obj, nBytesp);
  }

  out:
  if ((tok->flags & 0x10) && (nBytes != 0))
  {
    tok->err = json_tokener_error_parse_utf8_string;
  }

  if (((c && (tok->stack[tok->depth].state == json_tokener_state_finish)) && (tok->depth == 0)) && ((tok->flags & (0x01 | 0x02)) == 0x01))
  {
    tok->err = json_tokener_error_parse_unexpected;
  }
  if (!c)
  {
    if ((tok->stack[tok->depth].state != json_tokener_state_finish) && (tok->stack[tok->depth].saved_state != json_tokener_state_finish))
    {
      tok->err = json_tokener_error_parse_eof;
    }
  }
  uselocale(oldlocale);
  freelocale(newloc);
  if (tok->err == json_tokener_success)
  {
    json_object *ret = json_object_get(tok->stack[tok->depth].current);
    int ii;
    for (ii = tok->depth; ii >= 0; ii -= 1)
    {
      json_tokener_reset_level(tok, ii);
    }

    return ret;
  }
  if (0)
  {
    mc_debug("json_tokener_parse_ex: error %s at offset %d\n", json_tokener_errors[tok->err], tok->char_offset);
  }
  return 0;
}


----------------------------
enum json_tokener_error
{
  json_tokener_success,
  json_tokener_continue,
  json_tokener_error_depth,
  json_tokener_error_parse_eof,
  json_tokener_error_parse_unexpected,
  json_tokener_error_parse_null,
  json_tokener_error_parse_boolean,
  json_tokener_error_parse_number,
  json_tokener_error_parse_array,
  json_tokener_error_parse_object_key_name,
  json_tokener_error_parse_object_key_sep,
  json_tokener_error_parse_object_value_sep,
  json_tokener_error_parse_string,
  json_tokener_error_parse_comment,
  json_tokener_error_parse_utf8_string,
  json_tokener_error_size,
  json_tokener_error_memory
}
----------------------------
void json_tokener_free(struct json_tokener *tok)
{
  if (!tok)
  {
    return;
  }
  json_tokener_reset(tok);
  if (tok->pb)
  {
    printbuf_free(tok->pb);
  }
  free(tok->stack);
  free(tok);
}


----------------------------
struct json_tokener *json_tokener_new(void)
{
  return json_tokener_new_ex(32);
}


----------------------------
int json_object_put(struct json_object *jso)
{
  if (!jso)
  {
    return 0;
  }
  assert(jso->_ref_count > 0);
  if ((--jso->_ref_count) > 0)
  {
    return 0;
  }
  if (jso->_user_delete)
  {
    jso->_user_delete(jso, jso->_userdata);
  }
  switch (jso->o_type)
  {
    case json_type_object:
    {
      json_object_object_delete(jso);
      break;
    }

    case json_type_array:
    {
      json_object_array_delete(jso);
      break;
    }

    case json_type_string:
    {
      json_object_string_delete(jso);
      break;
    }

    default:
    {
      json_object_generic_delete(jso);
      break;
    }

  }

  return 1;
}


----------------------------
None
----------------------------
***/


struct json_object *json_tokener_parse(const char *str)
{
  enum json_tokener_error jerr_ignored;
  struct json_object *obj;
  unsigned int obj_idx = 0;
  obj_idx = json_tokener_parse_verbose(str, &jerr_ignored);
  return obj;
}


/*** DEPENDENCIES:
struct json_object *json_tokener_parse_verbose(const char *str, enum json_tokener_error *error)
{
  struct json_tokener *tok;
  unsigned int tok_idx = 0;
  struct json_object *obj;
  unsigned int obj_idx = 0;
  tok_idx = json_tokener_new();
  if (!(&tok[tok_idx]))
  {
    *error = json_tokener_error_memory;
    return 0;
  }
  obj_idx = json_tokener_parse_ex(tok, str, -1);
  *error = tok->err;
  if (tok->err != json_tokener_success)
  {
    if ((&obj[obj_idx]) != 0)
    {
      json_object_put(obj);
    }
    obj_idx = 0;
  }
  json_tokener_free(tok);
  return obj;
}


----------------------------
None
----------------------------
enum json_tokener_error
{
  json_tokener_success,
  json_tokener_continue,
  json_tokener_error_depth,
  json_tokener_error_parse_eof,
  json_tokener_error_parse_unexpected,
  json_tokener_error_parse_null,
  json_tokener_error_parse_boolean,
  json_tokener_error_parse_number,
  json_tokener_error_parse_array,
  json_tokener_error_parse_object_key_name,
  json_tokener_error_parse_object_key_sep,
  json_tokener_error_parse_object_value_sep,
  json_tokener_error_parse_string,
  json_tokener_error_parse_comment,
  json_tokener_error_parse_utf8_string,
  json_tokener_error_size,
  json_tokener_error_memory
}
----------------------------
None
----------------------------
***/


enum json_tokener_error json_tokener_get_error(struct json_tokener *tok)
{
  return tok->err;
}


/*** DEPENDENCIES:
enum json_tokener_error
{
  json_tokener_success,
  json_tokener_continue,
  json_tokener_error_depth,
  json_tokener_error_parse_eof,
  json_tokener_error_parse_unexpected,
  json_tokener_error_parse_null,
  json_tokener_error_parse_boolean,
  json_tokener_error_parse_number,
  json_tokener_error_parse_array,
  json_tokener_error_parse_object_key_name,
  json_tokener_error_parse_object_key_sep,
  json_tokener_error_parse_object_value_sep,
  json_tokener_error_parse_string,
  json_tokener_error_parse_comment,
  json_tokener_error_parse_utf8_string,
  json_tokener_error_size,
  json_tokener_error_memory
}
----------------------------
None
----------------------------
***/


const char *json_tokener_error_desc(enum json_tokener_error jerr)
{
  int jerr_int = (int) jerr;
  if ((jerr_int < 0) || (jerr_int >= ((int) ((sizeof(json_tokener_errors)) / (sizeof(json_tokener_errors[0]))))))
  {
    return "Unknown error, invalid json_tokener_error value passed to json_tokener_error_desc()";
  }
  return json_tokener_errors[jerr];
}


/*** DEPENDENCIES:
static const char *json_tokener_errors[] = {"success", "continue", "nesting too deep", "unexpected end of data", "unexpected character", "null expected", "boolean expected", "number expected", "array value separator ',' expected", "quoted object property name expected", "object property name separator ':' expected", "object value separator ',' expected", "invalid string sequence", "expected comment", "invalid utf-8 string", "buffer size overflow", "out of memory"}
----------------------------
enum json_tokener_error
{
  json_tokener_success,
  json_tokener_continue,
  json_tokener_error_depth,
  json_tokener_error_parse_eof,
  json_tokener_error_parse_unexpected,
  json_tokener_error_parse_null,
  json_tokener_error_parse_boolean,
  json_tokener_error_parse_number,
  json_tokener_error_parse_array,
  json_tokener_error_parse_object_key_name,
  json_tokener_error_parse_object_key_sep,
  json_tokener_error_parse_object_value_sep,
  json_tokener_error_parse_string,
  json_tokener_error_parse_comment,
  json_tokener_error_parse_utf8_string,
  json_tokener_error_size,
  json_tokener_error_memory
}
----------------------------
None
----------------------------
***/


