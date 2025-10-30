static void test_case_parse(void)
{
  struct json_tokener *tok;
  unsigned int tok_idx = 0;
  json_object *new_obj;
  unsigned int new_obj_idx = 0;
  tok_idx = json_tokener_new();
  json_tokener_set_flags(tok, 0x01);
  new_obj_idx = json_tokener_parse_ex(tok, "True", 4);
  assert((&new_obj[new_obj_idx]) == 0);
  new_obj_idx = json_tokener_parse_ex(tok, "False", 5);
  assert((&new_obj[new_obj_idx]) == 0);
  new_obj_idx = json_tokener_parse_ex(tok, "Null", 4);
  assert((&new_obj[new_obj_idx]) == 0);
  printf("OK\n");
  json_tokener_free(tok);
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
void json_tokener_set_flags(struct json_tokener *tok, int flags)
{
  tok->flags = flags;
}


----------------------------
struct json_tokener *json_tokener_new(void)
{
  return json_tokener_new_ex(32);
}


----------------------------
None
----------------------------
***/


int main(int argc, char **argv)
{
  if (0)
  {
    mc_set_debug(1);
  }
  test_case_parse();
  return 0;
}


/*** DEPENDENCIES:
static void test_case_parse(void)
{
  struct json_tokener *tok;
  unsigned int tok_idx = 0;
  json_object *new_obj;
  unsigned int new_obj_idx = 0;
  tok_idx = json_tokener_new();
  json_tokener_set_flags(tok, 0x01);
  new_obj_idx = json_tokener_parse_ex(tok, "True", 4);
  assert((&new_obj[new_obj_idx]) == 0);
  new_obj_idx = json_tokener_parse_ex(tok, "False", 5);
  assert((&new_obj[new_obj_idx]) == 0);
  new_obj_idx = json_tokener_parse_ex(tok, "Null", 4);
  assert((&new_obj[new_obj_idx]) == 0);
  printf("OK\n");
  json_tokener_free(tok);
}


----------------------------
void mc_set_debug(int debug)
{
  _debug = debug;
}


----------------------------
***/


