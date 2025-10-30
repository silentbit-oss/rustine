void fail_writer(char *test_name, char *message)
{
  fprintf(stderr, "Writer test %s failed: %s\n", test_name, message);
  exit(1);
}


/*** DEPENDENCIES:
***/


void fail_parser(char *test_name, char *message)
{
  fprintf(stderr, "Parser test %s failed on event %d: %s\n", test_name, event_idx, message);
  exit(1);
}


/*** DEPENDENCIES:
int event_idx
----------------------------
***/


void test_writer(char *test_name, char *input, size_t input_len, char *expected, size_t expected_len)
{
  size_t actual_len;
  char *temp = malloc((input_len * 2) + 2);
  if (!temp)
  {
    fprintf(stderr, "Failed to allocate memory in test_writer!\n");
    exit(1);
  }
  actual_len = csv_write(temp, (input_len * 2) + 2, input, input_len);
  if (actual_len != expected_len)
  {
    fail_writer(test_name, "actual length doesn't match expected length");
  }
  if (memcmp(temp, expected, actual_len) != 0)
  {
    fail_writer(test_name, "actual data doesn't match expected data");
  }
}


/*** DEPENDENCIES:
size_t csv_write(void *dest, size_t dest_size, const void *src, size_t src_size)
{
  return csv_write2(dest, dest_size, src, src_size, 0x22);
}


----------------------------
void fail_writer(char *test_name, char *message)
{
  fprintf(stderr, "Writer test %s failed: %s\n", test_name, message);
  exit(1);
}


----------------------------
***/


void test_writer2(char *test_name, char *input, size_t input_len, char *expected, size_t expected_len, char quote)
{
  size_t actual_len;
  char *temp = malloc((input_len * 2) + 2);
  if (!temp)
  {
    fprintf(stderr, "Failed to allocate memory in test_writer!\n");
    exit(1);
  }
  actual_len = csv_write2(temp, (input_len * 2) + 2, input, input_len, quote);
  if (actual_len != expected_len)
  {
    fail_writer(test_name, "actual length doesn't match expected length");
  }
  if (memcmp(temp, expected, actual_len) != 0)
  {
    fail_writer(test_name, "actual data doesn't match expected data");
  }
}


/*** DEPENDENCIES:
void fail_writer(char *test_name, char *message)
{
  fprintf(stderr, "Writer test %s failed: %s\n", test_name, message);
  exit(1);
}


----------------------------
size_t csv_write2(void *dest, size_t dest_size, const void *src, size_t src_size, unsigned char quote)
{
  unsigned char *cdest = dest;
  unsigned int cdest_idx = 0;
  const unsigned char *csrc = src;
  unsigned int csrc_idx = 0;
  size_t chars = 0;
  if (src == 0)
  {
    return 0;
  }
  if (dest == 0)
  {
    dest_size = 0;
  }
  if (dest_size > 0)
  {
    cdest[cdest_idx] = quote;
    cdest_idx += 1;
  }
  chars += 1;
  while (src_size)
  {
    if (csrc[csrc_idx] == quote)
    {
      if (dest_size > chars)
      {
        cdest[cdest_idx] = quote;
        cdest_idx += 1;
      }
      if (chars < SIZE_MAX)
      {
        chars += 1;
      }
    }
    if (dest_size > chars)
    {
      cdest[cdest_idx] = csrc[csrc_idx];
      cdest_idx += 1;
    }
    if (chars < SIZE_MAX)
    {
      chars += 1;
    }
    src_size -= 1;
    csrc_idx += 1;
  }

  if (dest_size > chars)
  {
    cdest[cdest_idx] = quote;
  }
  if (chars < SIZE_MAX)
  {
    chars += 1;
  }
  return chars;
}


----------------------------
***/


void cb2(int c, void *t)
{
  char *test_name = t;
  if (event_ptr->event_type != 2)
  {
    fail_parser(test_name, "didn't expect end of row");
  }
  if (event_ptr->retval != c)
  {
    fail_parser(test_name, "row ended with unexpected character");
  }
  event_idx += 1;
  event_ptr += 1;
  col = 1;
  row += 1;
}


/*** DEPENDENCIES:
int event_idx
----------------------------
void fail_parser(char *test_name, char *message)
{
  fprintf(stderr, "Parser test %s failed on event %d: %s\n", test_name, event_idx, message);
  exit(1);
}


----------------------------
size_t col
----------------------------
size_t row
----------------------------
***/


void cb1(void *data, size_t len, void *t)
{
  char *test_name = t;
  if (event_ptr->event_type != 1)
  {
    fail_parser(test_name, "didn't expect a column");
  }
  if (event_ptr->size != len)
  {
    fail_parser(test_name, "actual data length doesn't match expected data length");
  }
  if ((event_ptr->data == 0) || (data == 0))
  {
    if (event_ptr->data != data)
    {
      fail_parser(test_name, "actual data doesn't match expected data");
    }
  }
  else
    if (memcmp(event_ptr->data, data, len) != 0)
  {
    fail_parser(test_name, "actual data doesn't match expected data");
  }
  event_idx += 1;
  event_ptr += 1;
  col += 1;
}


/*** DEPENDENCIES:
int event_idx
----------------------------
void fail_parser(char *test_name, char *message)
{
  fprintf(stderr, "Parser test %s failed on event %d: %s\n", test_name, event_idx, message);
  exit(1);
}


----------------------------
size_t col
----------------------------
***/


void test_parser(char *test_name, unsigned char options, void *input, size_t len, struct event expected[], char delimiter, char quote, int (*space_func)(unsigned char), int (*term_func)(unsigned char))
{
  int result = 0;
  size_t retval;
  struct csv_parser p;
  size_t size;
  for (size = 1; size <= len; size += 1)
  {
    size_t bytes_processed = 0;
    csv_init(&p, options);
    csv_set_delim(&p, delimiter);
    csv_set_quote(&p, quote);
    csv_set_space_func(&p, space_func);
    csv_set_term_func(&p, term_func);
    row = (col = 1);
    event_ptr = &expected[0];
    event_idx = 1;
    do
    {
      size_t bytes = (size < (len - bytes_processed)) ? (size) : (len - bytes_processed);
      retval = csv_parse(&p, input + bytes_processed, bytes, cb1, cb2, test_name);
      if (retval != bytes)
      {
        if (event_ptr->event_type != 3)
        {
          fail_parser(test_name, "unexpected parse error occurred");
        }
        else
        {
          csv_free(&p);
          return;
        }
      }
      bytes_processed += bytes;
    }
    while (bytes_processed < len);
    result = csv_fini(&p, cb1, cb2, test_name);
    if (result != 0)
    {
      if (event_ptr->event_type != 3)
      {
        fail_parser(test_name, "unexpected parse error occurred");
      }
      else
      {
        csv_free(&p);
        return;
      }
    }
    csv_free(&p);
    if (event_ptr->event_type != 0)
    {
      fail_parser(test_name, "unexpected end of input");
    }
  }

}


/*** DEPENDENCIES:
void csv_set_space_func(struct csv_parser *p, int (*f)(unsigned char))
{
  if (p)
  {
    p->is_space = f;
  }
}


----------------------------
size_t csv_parse(struct csv_parser *p, const void *s, size_t len, void (*cb1)(void *, size_t, void *), void (*cb2)(int c, void *), void *data)
{
  assert(p && "received null csv_parser");
  if (s == 0)
  {
    return 0;
  }
  const unsigned char *us = s;
  unsigned char c;
  size_t pos = 0;
  unsigned char delim = p->delim_char;
  unsigned char quote = p->quote_char;
  int (*is_space)(unsigned char) = p->is_space;
  int (*is_term)(unsigned char) = p->is_term;
  int quoted = p->quoted;
  int pstate = p->pstate;
  size_t spaces = p->spaces;
  size_t entry_pos = p->entry_pos;
  if ((!p->entry_buf) && (pos < len))
  {
    if (csv_increase_buffer(p) != 0)
    {
      p->quoted = quoted, p->pstate = pstate, p->spaces = spaces, p->entry_pos = entry_pos;
      return pos;
    }
  }
  while (pos < len)
  {
    helper_csv_parse_1(&c, &c, &pos, &quoted, &pstate, &spaces, &entry_pos, p, cb1, cb2, data, us, delim, quote, is_space, is_term);
  }

  p->quoted = quoted, p->pstate = pstate, p->spaces = spaces, p->entry_pos = entry_pos;
  return pos;
}


----------------------------
void csv_set_delim(struct csv_parser *p, unsigned char c)
{
  if (p)
  {
    p->delim_char = c;
  }
}


----------------------------
size_t col
----------------------------
void cb2(int c, void *t)
{
  char *test_name = t;
  if (event_ptr->event_type != 2)
  {
    fail_parser(test_name, "didn't expect end of row");
  }
  if (event_ptr->retval != c)
  {
    fail_parser(test_name, "row ended with unexpected character");
  }
  event_idx += 1;
  event_ptr += 1;
  col = 1;
  row += 1;
}


----------------------------
void csv_free(struct csv_parser *p)
{
  if (p == 0)
  {
    return;
  }
  if (p->entry_buf && p->free_func)
  {
    p->free_func(p->entry_buf);
  }
  p->entry_buf = 0;
  p->entry_size = 0;
  return;
}


----------------------------
void cb1(void *data, size_t len, void *t)
{
  char *test_name = t;
  if (event_ptr->event_type != 1)
  {
    fail_parser(test_name, "didn't expect a column");
  }
  if (event_ptr->size != len)
  {
    fail_parser(test_name, "actual data length doesn't match expected data length");
  }
  if ((event_ptr->data == 0) || (data == 0))
  {
    if (event_ptr->data != data)
    {
      fail_parser(test_name, "actual data doesn't match expected data");
    }
  }
  else
    if (memcmp(event_ptr->data, data, len) != 0)
  {
    fail_parser(test_name, "actual data doesn't match expected data");
  }
  event_idx += 1;
  event_ptr += 1;
  col += 1;
}


----------------------------
void csv_set_quote(struct csv_parser *p, unsigned char c)
{
  if (p)
  {
    p->quote_char = c;
  }
}


----------------------------
struct csv_parser
{
  int pstate;
  int quoted;
  size_t spaces;
  unsigned char *entry_buf;
  size_t entry_pos;
  size_t entry_size;
  int status;
  unsigned char options;
  unsigned char quote_char;
  unsigned char delim_char;
  int (*is_space)(unsigned char);
  int (*is_term)(unsigned char);
  size_t blk_size;
  void *(*malloc_func)(size_t);
  void *(*realloc_func)(void *, size_t);
  void (*free_func)(void *);
}
----------------------------
int csv_init(struct csv_parser *p, unsigned char options)
{
  if (p == 0)
  {
    return -1;
  }
  p->entry_buf = 0;
  p->pstate = 0;
  p->quoted = 0;
  p->spaces = 0;
  p->entry_pos = 0;
  p->entry_size = 0;
  p->status = 0;
  p->options = options;
  p->quote_char = 0x22;
  p->delim_char = 0x2c;
  p->is_space = 0;
  p->is_term = 0;
  p->blk_size = 128;
  p->malloc_func = 0;
  p->realloc_func = realloc;
  p->free_func = free;
  return 0;
}


----------------------------
struct event
{
  int event_type;
  int retval;
  size_t size;
  char *data;
}
----------------------------
int event_idx
----------------------------
size_t row
----------------------------
int csv_fini(struct csv_parser *p, void (*cb1)(void *, size_t, void *), void (*cb2)(int c, void *), void *data)
{
  if (p == 0)
  {
    return -1;
  }
  int quoted = p->quoted;
  int pstate = p->pstate;
  size_t spaces = p->spaces;
  size_t entry_pos = p->entry_pos;
  if ((((pstate == 2) && p->quoted) && (p->options & 1)) && (p->options & 4))
  {
    p->status = 1;
    return -1;
  }
  switch (pstate)
  {
    case 3:
    {
      p->entry_pos -= p->spaces + 1;
      entry_pos = p->entry_pos;
    }

    case 1:

    case 2:
    {
      do
      {
        if (!quoted)
        {
          entry_pos -= spaces;
        }
        if (p->options & 8)
        {
          p->entry_buf[entry_pos] = '\0';
        }
        if (((cb1 && (p->options & 16)) && (!quoted)) && (entry_pos == 0))
        {
          cb1(0, entry_pos, data);
        }
        else
          if (cb1)
        {
          cb1(p->entry_buf, entry_pos, data);
        }
        pstate = 1;
        entry_pos = (quoted = (spaces = 0));
      }
      while (0);
      do
      {
        if (cb2)
        {
          cb2(-1, data);
        }
        pstate = 0;
        entry_pos = (quoted = (spaces = 0));
      }
      while (0);
      break;
    }

    case 0:
    {
      ;
    }

  }

  p->spaces = (p->quoted = (p->entry_pos = (p->status = 0)));
  p->pstate = 0;
  return 0;
}


----------------------------
void fail_parser(char *test_name, char *message)
{
  fprintf(stderr, "Parser test %s failed on event %d: %s\n", test_name, event_idx, message);
  exit(1);
}


----------------------------
void csv_set_term_func(struct csv_parser *p, int (*f)(unsigned char))
{
  if (p)
  {
    p->is_term = f;
  }
}


----------------------------
***/


int main(void)
{
  char test01_data[] = " 1,2 ,  3         ,4,5\x0d\x0a";
  char test02_data[] = ",,,,,\x0a";
  char test03_data[] = "\",\",\",\",\"\"";
  char test04_data[] = "\"I call our world Flatland,\x0anot because we call it so,\x0abut to make its nature clearer\x0ato you, my happy readers,\x0awho are privileged to live in Space.\"";
  char test05_data[] = "\"\"\"a,b\"\"\",,\" \"\"\"\" \",\"\"\"\"\" \",\" \"\"\"\"\",\"\"\"\"\"\"";
  char test06_data[] = "\" a, b ,c \", a b  c,";
  char test07_data[] = "\" \"\" \" \" \"\" \"";
  char test07b_data[] = "\" \"\" \" \" \"\" \"";
  char test08_data[] = "\" abc\"                                                                                                                                                                                                                                                                                                                                                                                                                                                                          \", \"123\"";
  char test09_data[] = "";
  char test10_data[] = "a\x0a";
  char test11_data[] = "1,2 ,3,4\x0a";
  char test12_data[] = "\x0a\x0a\x0a\x0a";
  char test12b_data[] = "\x0a\x0a\x0a\x0a";
  char test13_data[] = "\"abc\"";
  char test14_data[] = "1, 2, 3,\x0a\x0d\x0a  \"4\", \x0d,";
  char test15_data[] = "1, 2, 3,\x0a\x0d\x0a  \"4\", \x0d\"\"";
  char test16_data[] = "\"1\",\"2\",\" 3 ";
  char test16b_data[] = "\"1\",\"2\",\" 3 ";
  char test17_data[] = " a\0b\0c ";
  char test18_data[] = "12345678901234567890123456789012";
  char test19_data[] = "  , \"\" ,";
  char custom01_data[] = "'''a;b''';;' '''' ';''''' ';' ''''';''''''";
  struct event test01_results[] = {{1, 0, 1, "1"}, {1, 0, 1, "2"}, {1, 0, 1, "3"}, {1, 0, 1, "4"}, {1, 0, 1, "5"}, {2, '\x0d', 1, 0}, {0, 0, 0, 0}};
  struct event test02_results[] = {{1, 0, 0, ""}, {1, 0, 0, ""}, {1, 0, 0, ""}, {1, 0, 0, ""}, {1, 0, 0, ""}, {1, 0, 0, ""}, {2, '\x0a', 1, 0}, {0, 0, 0, 0}};
  struct event test03_results[] = {{1, 0, 1, ","}, {1, 0, 1, ","}, {1, 0, 0, ""}, {2, -1, 1, 0}, {0, 0, 0, 0}};
  struct event test04_results[] = {{1, 0, 147, "I call our world Flatland,\x0anot because we call it so,\x0abut to make its nature clearer\x0ato you, my happy readers,\x0awho are privileged to live in Space."}, {2, -1, 1, 0}, {0, 0, 0, 0}};
  struct event test05_results[] = {{1, 0, 5, "\"a,b\""}, {1, 0, 0, ""}, {1, 0, 4, " \"\" "}, {1, 0, 3, "\"\" "}, {1, 0, 3, " \"\""}, {1, 0, 2, "\"\""}, {2, -1, 1, 0}, {0, 0, 0, 0}};
  struct event test06_results[] = {{1, 0, 9, " a, b ,c "}, {1, 0, 6, "a b  c"}, {1, 0, 0, ""}, {2, -1, 1, 0}, {0, 0, 0, 0}};
  struct event test07_results[] = {{1, 0, 9, " \" \" \" \" "}, {2, -1, 1, 0}, {0, 0, 0, 0}};
  struct event test07b_results[] = {{3, 0, 0, 0}};
  struct event test08_results[] = {{1, 0, 463, " abc\"                                                                                                                                                                                                                                                                                                                                                                                                                                                                          "}, {1, 0, 3, "123"}, {2, -1, 1, 0}, {0, 0, 0, 0}};
  struct event test09_results[] = {{0, 0, 0, 0}};
  struct event test10_results[] = {{1, 0, 1, "a"}, {2, '\x0a', 1, 0}, {0, 0, 0, 0}};
  struct event test11_results[] = {{1, 0, 1, "1"}, {1, 0, 1, "2"}, {1, 0, 1, "3"}, {1, 0, 1, "4"}, {2, '\x0a', 1, 0}, {0, 0, 0, 0}};
  struct event test12_results[] = {{0, 0, 0, 0}};
  struct event test12b_results[] = {{2, '\x0a', 1, 0}, {2, '\x0a', 1, 0}, {2, '\x0a', 1, 0}, {2, '\x0a', 1, 0}, {0, 0, 0, 0}};
  struct event test13_results[] = {{1, 0, 3, "abc"}, {2, -1, 1, 0}, {0, 0, 0, 0}};
  struct event test14_results[] = {{1, 0, 1, "1"}, {1, 0, 1, "2"}, {1, 0, 1, "3"}, {1, 0, 0, ""}, {2, '\x0a', 1, 0}, {1, 0, 1, "4"}, {1, 0, 0, ""}, {2, '\x0d', 1, 0}, {1, 0, 0, ""}, {1, 0, 0, ""}, {2, -1, 0, 0}, {0, 0, 0, 0}};
  struct event test15_results[] = {{1, 0, 1, "1"}, {1, 0, 1, "2"}, {1, 0, 1, "3"}, {1, 0, 0, ""}, {2, '\x0a', 1, 0}, {1, 0, 1, "4"}, {1, 0, 0, ""}, {2, '\x0d', 1, 0}, {1, 0, 0, ""}, {2, -1, 0, 0}, {0, 0, 0, 0}};
  struct event test16_results[] = {{1, 0, 1, "1"}, {1, 0, 1, "2"}, {1, 0, 3, " 3 "}, {2, -1, 1, 0}, {0, 0, 0, 0}};
  struct event test16b_results[] = {{1, 0, 1, "1"}, {1, 0, 1, "2"}, {3, 0, 0, 0}};
  struct event test17_results[] = {{1, 0, 5, "a\0b\0c"}, {2, -1, 1, 0}, {0, 0, 0, 0}};
  struct event test19_results[] = {{1, 0, 0, 0}, {1, 0, 0, ""}, {1, 0, 0, 0}, {2, -1, 1, 0}, {0, 0, 0, 0}};
  struct event custom01_results[] = {{1, 0, 5, "'a;b'"}, {1, 0, 0, ""}, {1, 0, 4, " '' "}, {1, 0, 3, "'' "}, {1, 0, 3, " ''"}, {1, 0, 2, "''"}, {2, -1, 1, 0}, {0, 0, 0, 0}};
  test_parser("test01", 0, test01_data, (sizeof(test01_data)) - 1, test01_results, 0x2c, 0x22, 0, 0);
  test_parser("test01", 1, test01_data, (sizeof(test01_data)) - 1, test01_results, 0x2c, 0x22, 0, 0);
  test_parser("test01", 1 | 16, test01_data, (sizeof(test01_data)) - 1, test01_results, 0x2c, 0x22, 0, 0);
  test_parser("test02", 0, test02_data, (sizeof(test02_data)) - 1, test02_results, 0x2c, 0x22, 0, 0);
  test_parser("test02", 1, test02_data, (sizeof(test02_data)) - 1, test02_results, 0x2c, 0x22, 0, 0);
  test_parser("test03", 0, test03_data, (sizeof(test03_data)) - 1, test03_results, 0x2c, 0x22, 0, 0);
  test_parser("test03", 1, test03_data, (sizeof(test03_data)) - 1, test03_results, 0x2c, 0x22, 0, 0);
  test_parser("test04", 0, test04_data, (sizeof(test04_data)) - 1, test04_results, 0x2c, 0x22, 0, 0);
  test_parser("test04", 1, test04_data, (sizeof(test04_data)) - 1, test04_results, 0x2c, 0x22, 0, 0);
  test_parser("test05", 0, test05_data, (sizeof(test05_data)) - 1, test05_results, 0x2c, 0x22, 0, 0);
  test_parser("test05", 1, test05_data, (sizeof(test05_data)) - 1, test05_results, 0x2c, 0x22, 0, 0);
  test_parser("test05", 1 | 4, test05_data, (sizeof(test05_data)) - 1, test05_results, 0x2c, 0x22, 0, 0);
  test_parser("test06", 0, test06_data, (sizeof(test06_data)) - 1, test06_results, 0x2c, 0x22, 0, 0);
  test_parser("test06", 1, test06_data, (sizeof(test06_data)) - 1, test06_results, 0x2c, 0x22, 0, 0);
  test_parser("test07", 0, test07_data, (sizeof(test07_data)) - 1, test07_results, 0x2c, 0x22, 0, 0);
  test_parser("test07b", 1, test07b_data, (sizeof(test07b_data)) - 1, test07b_results, 0x2c, 0x22, 0, 0);
  test_parser("test08", 0, test08_data, (sizeof(test08_data)) - 1, test08_results, 0x2c, 0x22, 0, 0);
  test_parser("test09", 0, test09_data, (sizeof(test09_data)) - 1, test09_results, 0x2c, 0x22, 0, 0);
  test_parser("test09", 16, test09_data, (sizeof(test09_data)) - 1, test09_results, 0x2c, 0x22, 0, 0);
  test_parser("test10", 0, test10_data, (sizeof(test10_data)) - 1, test10_results, 0x2c, 0x22, 0, 0);
  test_parser("test11", 0, test11_data, (sizeof(test11_data)) - 1, test11_results, 0x2c, 0x22, 0, 0);
  test_parser("test11", 16, test11_data, (sizeof(test11_data)) - 1, test11_results, 0x2c, 0x22, 0, 0);
  test_parser("test12", 0, test12_data, (sizeof(test12_data)) - 1, test12_results, 0x2c, 0x22, 0, 0);
  test_parser("test12", 16, test12_data, (sizeof(test12_data)) - 1, test12_results, 0x2c, 0x22, 0, 0);
  test_parser("test12b", 2, test12b_data, (sizeof(test12b_data)) - 1, test12b_results, 0x2c, 0x22, 0, 0);
  test_parser("test12b", 2 | 16, test12b_data, (sizeof(test12b_data)) - 1, test12b_results, 0x2c, 0x22, 0, 0);
  test_parser("test13", 0, test13_data, (sizeof(test13_data)) - 1, test13_results, 0x2c, 0x22, 0, 0);
  test_parser("test14", 0, test14_data, (sizeof(test14_data)) - 1, test14_results, 0x2c, 0x22, 0, 0);
  test_parser("test14", 1, test14_data, (sizeof(test14_data)) - 1, test14_results, 0x2c, 0x22, 0, 0);
  test_parser("test15", 0, test15_data, (sizeof(test15_data)) - 1, test15_results, 0x2c, 0x22, 0, 0);
  test_parser("test15", 1, test15_data, (sizeof(test15_data)) - 1, test15_results, 0x2c, 0x22, 0, 0);
  test_parser("test16", 0, test16_data, (sizeof(test16_data)) - 1, test16_results, 0x2c, 0x22, 0, 0);
  test_parser("test16", 1, test16_data, (sizeof(test16_data)) - 1, test16_results, 0x2c, 0x22, 0, 0);
  test_parser("test16b", 1 | 4, test16b_data, (sizeof(test16b_data)) - 1, test16b_results, 0x2c, 0x22, 0, 0);
  test_parser("test16", 0, test16_data, (sizeof(test16_data)) - 1, test16_results, 0x2c, 0x22, 0, 0);
  test_parser("test16", 1, test16_data, (sizeof(test16_data)) - 1, test16_results, 0x2c, 0x22, 0, 0);
  test_parser("test17", 0, test17_data, (sizeof(test17_data)) - 1, test17_results, 0x2c, 0x22, 0, 0);
  test_parser("test17", 1, test17_data, (sizeof(test17_data)) - 1, test17_results, 0x2c, 0x22, 0, 0);
  test_parser("test17", 1 | 16, test17_data, (sizeof(test17_data)) - 1, test17_results, 0x2c, 0x22, 0, 0);
  test_parser("test19", 16, test19_data, (sizeof(test19_data)) - 1, test19_results, 0x2c, 0x22, 0, 0);
  test_parser("custom01", 0, custom01_data, (sizeof(custom01_data)) - 1, custom01_results, ';', '\'', 0, 0);
  test_writer("1", "abc", 3, "\"abc\"", 5);
  test_writer("2", "\"\"\"\"\"\"\"\"", 8, "\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"\"", 18);
  test_writer2("1", "abc", 3, "'abc'", 5, '\'');
  test_writer2("2", "''''''''", 8, "''''''''''''''''''", 18, '\'');
  puts("All tests passed");
  return 0;
}


/*** DEPENDENCIES:
void test_parser(char *test_name, unsigned char options, void *input, size_t len, struct event expected[], char delimiter, char quote, int (*space_func)(unsigned char), int (*term_func)(unsigned char))
{
  int result = 0;
  size_t retval;
  struct csv_parser p;
  size_t size;
  for (size = 1; size <= len; size += 1)
  {
    size_t bytes_processed = 0;
    csv_init(&p, options);
    csv_set_delim(&p, delimiter);
    csv_set_quote(&p, quote);
    csv_set_space_func(&p, space_func);
    csv_set_term_func(&p, term_func);
    row = (col = 1);
    event_ptr = &expected[0];
    event_idx = 1;
    do
    {
      size_t bytes = (size < (len - bytes_processed)) ? (size) : (len - bytes_processed);
      retval = csv_parse(&p, input + bytes_processed, bytes, cb1, cb2, test_name);
      if (retval != bytes)
      {
        if (event_ptr->event_type != 3)
        {
          fail_parser(test_name, "unexpected parse error occurred");
        }
        else
        {
          csv_free(&p);
          return;
        }
      }
      bytes_processed += bytes;
    }
    while (bytes_processed < len);
    result = csv_fini(&p, cb1, cb2, test_name);
    if (result != 0)
    {
      if (event_ptr->event_type != 3)
      {
        fail_parser(test_name, "unexpected parse error occurred");
      }
      else
      {
        csv_free(&p);
        return;
      }
    }
    csv_free(&p);
    if (event_ptr->event_type != 0)
    {
      fail_parser(test_name, "unexpected end of input");
    }
  }

}


----------------------------
void test_writer(char *test_name, char *input, size_t input_len, char *expected, size_t expected_len)
{
  size_t actual_len;
  char *temp = malloc((input_len * 2) + 2);
  if (!temp)
  {
    fprintf(stderr, "Failed to allocate memory in test_writer!\n");
    exit(1);
  }
  actual_len = csv_write(temp, (input_len * 2) + 2, input, input_len);
  if (actual_len != expected_len)
  {
    fail_writer(test_name, "actual length doesn't match expected length");
  }
  if (memcmp(temp, expected, actual_len) != 0)
  {
    fail_writer(test_name, "actual data doesn't match expected data");
  }
}


----------------------------
struct event
{
  int event_type;
  int retval;
  size_t size;
  char *data;
}
----------------------------
void test_writer2(char *test_name, char *input, size_t input_len, char *expected, size_t expected_len, char quote)
{
  size_t actual_len;
  char *temp = malloc((input_len * 2) + 2);
  if (!temp)
  {
    fprintf(stderr, "Failed to allocate memory in test_writer!\n");
    exit(1);
  }
  actual_len = csv_write2(temp, (input_len * 2) + 2, input, input_len, quote);
  if (actual_len != expected_len)
  {
    fail_writer(test_name, "actual length doesn't match expected length");
  }
  if (memcmp(temp, expected, actual_len) != 0)
  {
    fail_writer(test_name, "actual data doesn't match expected data");
  }
}


----------------------------
***/


