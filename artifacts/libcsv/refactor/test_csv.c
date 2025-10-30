#include <assert.h>
#include <csv.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <test_csv.c>

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
};
int csv_init(struct csv_parser *p, unsigned char options);
int csv_fini(struct csv_parser *p, void (*cb1)(void *, size_t, void *), void (*cb2)(int, void *), void *data);
void csv_free(struct csv_parser *p);
int csv_error(const struct csv_parser *p);
const char *csv_strerror(int error);
size_t csv_parse(struct csv_parser *p, const void *s, size_t len, void (*cb1)(void *, size_t, void *), void (*cb2)(int, void *), void *data);
size_t csv_write(void *dest, size_t dest_size, const void *src, size_t src_size);
int csv_fwrite(FILE *fp, const void *src, size_t src_size);
size_t csv_write2(void *dest, size_t dest_size, const void *src, size_t src_size, unsigned char quote);
int csv_fwrite2(FILE *fp, const void *src, size_t src_size, unsigned char quote);
int csv_get_opts(const struct csv_parser *p);
int csv_set_opts(struct csv_parser *p, unsigned char options);
void csv_set_delim(struct csv_parser *p, unsigned char c);
void csv_set_quote(struct csv_parser *p, unsigned char c);
unsigned char csv_get_delim(const struct csv_parser *p);
unsigned char csv_get_quote(const struct csv_parser *p);
void csv_set_space_func(struct csv_parser *p, int (*f)(unsigned char));
void csv_set_term_func(struct csv_parser *p, int (*f)(unsigned char));
void csv_set_realloc_func(struct csv_parser *p, void *(*)(void *, size_t));
void csv_set_free_func(struct csv_parser *p, void (*)(void *));
void csv_set_blk_size(struct csv_parser *p, size_t);
size_t csv_get_buffer_size(const struct csv_parser *p);
struct event
{
  int event_type;
  int retval;
  size_t size;
  char *data;
};
struct event *event_ptr;
int event_idx;
size_t row;
size_t col;
void fail_parser(char *test_name, char *message)
{
  fprintf(stderr, "Parser test %s failed on event %d: %s\n", test_name, event_idx, message);
  exit(1);
}

void fail_writer(char *test_name, char *message)
{
  fprintf(stderr, "Writer test %s failed: %s\n", test_name, message);
  exit(1);
}

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

void test_parser(char *test_name, unsigned char options, void *input, size_t len, struct event expected[], char delimiter, char quote, int (*space_func)(unsigned char), int (*term_func)(unsigned char))
{
  int result = 0;
  size_t retval;
  struct csv_parser p;
  size_t size;
  for (size = 1; size <= len; size += 1)
  {
    helper_test_parser_1(&result, &retval, test_name, options, input, len, expected, delimiter, quote, space_func, term_func, p, size);
  }

}

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
};
int csv_init(struct csv_parser *p, unsigned char options);
int csv_fini(struct csv_parser *p, void (*cb1)(void *, size_t, void *), void (*cb2)(int, void *), void *data);
void csv_free(struct csv_parser *p);
int csv_error(const struct csv_parser *p);
const char *csv_strerror(int error);
size_t csv_parse(struct csv_parser *p, const void *s, size_t len, void (*cb1)(void *, size_t, void *), void (*cb2)(int, void *), void *data);
size_t csv_write(void *dest, size_t dest_size, const void *src, size_t src_size);
int csv_fwrite(FILE *fp, const void *src, size_t src_size);
size_t csv_write2(void *dest, size_t dest_size, const void *src, size_t src_size, unsigned char quote);
int csv_fwrite2(FILE *fp, const void *src, size_t src_size, unsigned char quote);
int csv_get_opts(const struct csv_parser *p);
int csv_set_opts(struct csv_parser *p, unsigned char options);
void csv_set_delim(struct csv_parser *p, unsigned char c);
void csv_set_quote(struct csv_parser *p, unsigned char c);
unsigned char csv_get_delim(const struct csv_parser *p);
unsigned char csv_get_quote(const struct csv_parser *p);
void csv_set_space_func(struct csv_parser *p, int (*f)(unsigned char));
void csv_set_term_func(struct csv_parser *p, int (*f)(unsigned char));
void csv_set_realloc_func(struct csv_parser *p, void *(*)(void *, size_t));
void csv_set_free_func(struct csv_parser *p, void (*)(void *));
void csv_set_blk_size(struct csv_parser *p, size_t);
size_t csv_get_buffer_size(const struct csv_parser *p);
struct event
{
  int event_type;
  int retval;
  size_t size;
  char *data;
};
struct event *event_ptr;
int event_idx;
size_t row;
size_t col;
void fail_parser(char *test_name, char *message)
{
  fprintf(stderr, "Parser test %s failed on event %d: %s\n", test_name, event_idx, message);
  exit(1);
}

void fail_writer(char *test_name, char *message)
{
  fprintf(stderr, "Writer test %s failed: %s\n", test_name, message);
  exit(1);
}

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

void helper_test_parser_1(int * const result_ref, size_t * const retval_ref, char * const test_name, unsigned char options, void * const input, size_t len, struct event expected[], char delimiter, char quote, int (* const space_func)(unsigned char), int (* const term_func)(unsigned char), struct csv_parser p, size_t size)
{
  int result = *result_ref;
  size_t retval = *retval_ref;
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
  *result_ref = result;
  *retval_ref = retval;
}

