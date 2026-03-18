#include <assert.h>
#include <buffer.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <test.c>
#include <types.h>

typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t;
buffer_t *buffer_new();
buffer_t *buffer_new_with_size(size_t n);
buffer_t *buffer_new_with_string(char *str);
buffer_t *buffer_new_with_string_length(char *str, size_t len);
buffer_t *buffer_new_with_copy(char *str);
size_t buffer_size(buffer_t *self);
size_t buffer_length(buffer_t *self);
void buffer_free(buffer_t *self);
int buffer_prepend(buffer_t *self, char *str);
int buffer_append(buffer_t *self, const char *str);
int buffer_appendf(buffer_t *self, const char *format, ...);
int buffer_append_n(buffer_t *self, const char *str, size_t len);
int buffer_equals(buffer_t *self, buffer_t *other);
ssize_t buffer_indexof(buffer_t *self, char *str);
buffer_t *buffer_slice(buffer_t *self, size_t from, ssize_t to);
ssize_t buffer_compact(buffer_t *self);
void buffer_fill(buffer_t *self, int c);
void buffer_clear(buffer_t *self);
void buffer_trim_left(buffer_t *self);
void buffer_trim_right(buffer_t *self);
void buffer_trim(buffer_t *self);
void buffer_print(buffer_t *self);
void equal(char *a, char *b)
{
  if (strcmp(a, b))
  {
    printf("\n");
    printf("  expected: '%s'\n", a);
    printf("    actual: '%s'\n", b);
    printf("\n");
    exit(1);
  }
}

void test_buffer_new()
{
  buffer_t *buf = buffer_new();
  assert(64 == buffer_size(buf));
  assert(0 == buffer_length(buf));
  buffer_free(buf);
}

void test_buffer_new_with_size()
{
  buffer_t *buf = buffer_new_with_size(1024);
  assert(1024 == buffer_size(buf));
  assert(0 == buffer_length(buf));
  buffer_free(buf);
}

void test_buffer_append()
{
  buffer_t *buf = buffer_new();
  assert(0 == buffer_append(buf, "Hello"));
  assert(0 == buffer_append(buf, " World"));
  assert(strlen("Hello World") == buffer_length(buf));
  equal("Hello World", buf->data);
  buffer_free(buf);
}

void test_buffer_append_n()
{
  buffer_t *buf = buffer_new();
  assert(0 == buffer_append_n(buf, "subway", 3));
  assert(0 == buffer_append_n(buf, "marines", 6));
  assert(strlen("submarine") == buffer_length(buf));
  equal("submarine", buf->data);
  buffer_free(buf);
}

void test_buffer_append__grow()
{
  buffer_t *buf = buffer_new_with_size(10);
  assert(0 == buffer_append(buf, "Hello"));
  assert(0 == buffer_append(buf, " tobi"));
  assert(0 == buffer_append(buf, " was"));
  assert(0 == buffer_append(buf, " here"));
  char *str = "Hello tobi was here";
  equal(str, buf->data);
  assert(1024 == buffer_size(buf));
  assert(strlen(str) == buffer_length(buf));
  buffer_free(buf);
}

void test_buffer_prepend()
{
  buffer_t *buf = buffer_new();
  assert(0 == buffer_append(buf, " World"));
  assert(0 == buffer_prepend(buf, "Hello"));
  assert(strlen("Hello World") == buffer_length(buf));
  equal("Hello World", buf->data);
  buffer_free(buf);
}

void test_buffer_slice()
{
  buffer_t *buf = buffer_new();
  buffer_append(buf, "Tobi Ferret");
  buffer_t *a = buffer_slice(buf, 2, 8);
  equal("Tobi Ferret", buf->data);
  equal("bi Fer", a->data);
  buffer_free(buf);
  buffer_free(a);
}

void test_buffer_slice__range_error()
{
  buffer_t *buf = buffer_new_with_copy("Tobi Ferret");
  buffer_t *a = buffer_slice(buf, 10, 2);
  assert(0 == a);
  buffer_free(buf);
}

void test_buffer_slice__end()
{
  buffer_t *buf = buffer_new_with_copy("Tobi Ferret");
  buffer_t *a = buffer_slice(buf, 5, -1);
  equal("Tobi Ferret", buf->data);
  equal("Ferret", a->data);
  buffer_t *b = buffer_slice(buf, 5, -3);
  equal("Ferr", b->data);
  buffer_t *c = buffer_slice(buf, 8, -1);
  equal("ret", c->data);
  buffer_free(buf);
  buffer_free(a);
  buffer_free(b);
  buffer_free(c);
}

void test_buffer_slice__end_overflow()
{
  buffer_t *buf = buffer_new_with_copy("Tobi Ferret");
  buffer_t *a = buffer_slice(buf, 5, 1000);
  equal("Tobi Ferret", buf->data);
  equal("Ferret", a->data);
  buffer_free(a);
  buffer_free(buf);
}

void test_buffer_equals()
{
  buffer_t *a = buffer_new_with_copy("Hello");
  buffer_t *b = buffer_new_with_copy("Hello");
  assert(1 == buffer_equals(a, b));
  buffer_append(b, " World");
  assert(0 == buffer_equals(a, b));
  buffer_free(a);
  buffer_free(b);
}

void test_buffer_formatting()
{
  buffer_t *buf = buffer_new();
  int result = buffer_appendf(buf, "%d %s", 3, "cow");
  assert(0 == result);
  equal("3 cow", buf->data);
  result = buffer_appendf(buf, " - 0x%08X", 0xdeadbeef);
  assert(0 == result);
  equal("3 cow - 0xDEADBEEF", buf->data);
  buffer_free(buf);
}

void test_buffer_indexof()
{
  buffer_t *buf = buffer_new_with_copy("Tobi is a ferret");
  ssize_t i = buffer_indexof(buf, "is");
  assert(5 == i);
  i = buffer_indexof(buf, "a");
  assert(8 == i);
  i = buffer_indexof(buf, "something");
  assert((-1) == i);
  buffer_free(buf);
}

void test_buffer_fill()
{
  buffer_t *buf = buffer_new_with_copy("Hello");
  assert(5 == buffer_length(buf));
  buffer_fill(buf, 0);
  assert(0 == buffer_length(buf));
  buffer_free(buf);
}

void test_buffer_clear()
{
  buffer_t *buf = buffer_new_with_copy("Hello");
  assert(5 == buffer_length(buf));
  buffer_clear(buf);
  assert(0 == buffer_length(buf));
  buffer_free(buf);
}

void test_buffer_trim()
{
  buffer_t *buf = buffer_new_with_copy("  Hello\n\n ");
  unsigned int buf_idx = 0;
  buffer_trim(buf);
  equal("Hello", buf->data);
  buffer_free(buf);
  buf_idx = buffer_new_with_copy("  Hello\n\n ");
  buffer_trim_left(buf);
  equal("Hello\n\n ", buf->data);
  buffer_free(buf);
  buf_idx = buffer_new_with_copy("  Hello\n\n ");
  buffer_trim_right(buf);
  equal("  Hello", buf->data);
  buffer_free(buf);
}

void test_buffer_compact()
{
  buffer_t *buf = buffer_new_with_copy("  Hello\n\n ");
  buffer_trim(buf);
  assert(5 == buffer_length(buf));
  assert(10 == buffer_size(buf));
  ssize_t removed = buffer_compact(buf);
  assert(5 == removed);
  assert(5 == buffer_length(buf));
  assert(5 == buffer_size(buf));
  equal("Hello", buf->data);
  buffer_free(buf);
}

int main()
{
  test_buffer_new();
  test_buffer_new_with_size();
  test_buffer_append();
  test_buffer_append__grow();
  test_buffer_append_n();
  test_buffer_prepend();
  test_buffer_slice();
  test_buffer_slice__range_error();
  test_buffer_slice__end();
  test_buffer_slice__end_overflow();
  test_buffer_equals();
  test_buffer_formatting();
  test_buffer_indexof();
  test_buffer_fill();
  test_buffer_clear();
  test_buffer_trim();
  test_buffer_compact();
  printf("\n  \e[32m\u2713 \e[90mok\e[0m\n\n");
  return 0;
}


typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t;
buffer_t *buffer_new();
buffer_t *buffer_new_with_size(size_t n);
buffer_t *buffer_new_with_string(char *str);
buffer_t *buffer_new_with_string_length(char *str, size_t len);
buffer_t *buffer_new_with_copy(char *str);
size_t buffer_size(buffer_t *self);
size_t buffer_length(buffer_t *self);
void buffer_free(buffer_t *self);
int buffer_prepend(buffer_t *self, char *str);
int buffer_append(buffer_t *self, const char *str);
int buffer_appendf(buffer_t *self, const char *format, ...);
int buffer_append_n(buffer_t *self, const char *str, size_t len);
int buffer_equals(buffer_t *self, buffer_t *other);
ssize_t buffer_indexof(buffer_t *self, char *str);
buffer_t *buffer_slice(buffer_t *self, size_t from, ssize_t to);
ssize_t buffer_compact(buffer_t *self);
void buffer_fill(buffer_t *self, int c);
void buffer_clear(buffer_t *self);
void buffer_trim_left(buffer_t *self);
void buffer_trim_right(buffer_t *self);
void buffer_trim(buffer_t *self);
void buffer_print(buffer_t *self);
void equal(char *a, char *b)
{
  if (strcmp(a, b))
  {
    printf("\n");
    printf("  expected: '%s'\n", a);
    printf("    actual: '%s'\n", b);
    printf("\n");
    exit(1);
  }
}

void test_buffer_new()
{
  buffer_t *buf = buffer_new();
  assert(64 == buffer_size(buf));
  assert(0 == buffer_length(buf));
  buffer_free(buf);
}

void test_buffer_new_with_size()
{
  buffer_t *buf = buffer_new_with_size(1024);
  assert(1024 == buffer_size(buf));
  assert(0 == buffer_length(buf));
  buffer_free(buf);
}

void test_buffer_append()
{
  buffer_t *buf = buffer_new();
  assert(0 == buffer_append(buf, "Hello"));
  assert(0 == buffer_append(buf, " World"));
  assert(strlen("Hello World") == buffer_length(buf));
  equal("Hello World", buf->data);
  buffer_free(buf);
}

void test_buffer_append_n()
{
  buffer_t *buf = buffer_new();
  assert(0 == buffer_append_n(buf, "subway", 3));
  assert(0 == buffer_append_n(buf, "marines", 6));
  assert(strlen("submarine") == buffer_length(buf));
  equal("submarine", buf->data);
  buffer_free(buf);
}

void test_buffer_append__grow()
{
  buffer_t *buf = buffer_new_with_size(10);
  assert(0 == buffer_append(buf, "Hello"));
  assert(0 == buffer_append(buf, " tobi"));
  assert(0 == buffer_append(buf, " was"));
  assert(0 == buffer_append(buf, " here"));
  char *str = "Hello tobi was here";
  equal(str, buf->data);
  assert(1024 == buffer_size(buf));
  assert(strlen(str) == buffer_length(buf));
  buffer_free(buf);
}

void test_buffer_prepend()
{
  buffer_t *buf = buffer_new();
  assert(0 == buffer_append(buf, " World"));
  assert(0 == buffer_prepend(buf, "Hello"));
  assert(strlen("Hello World") == buffer_length(buf));
  equal("Hello World", buf->data);
  buffer_free(buf);
}

void test_buffer_slice()
{
  buffer_t *buf = buffer_new();
  buffer_append(buf, "Tobi Ferret");
  buffer_t *a = buffer_slice(buf, 2, 8);
  equal("Tobi Ferret", buf->data);
  equal("bi Fer", a->data);
  buffer_free(buf);
  buffer_free(a);
}

void test_buffer_slice__range_error()
{
  buffer_t *buf = buffer_new_with_copy("Tobi Ferret");
  buffer_t *a = buffer_slice(buf, 10, 2);
  assert(0 == a);
  buffer_free(buf);
}

void test_buffer_slice__end()
{
  buffer_t *buf = buffer_new_with_copy("Tobi Ferret");
  buffer_t *a = buffer_slice(buf, 5, -1);
  equal("Tobi Ferret", buf->data);
  equal("Ferret", a->data);
  buffer_t *b = buffer_slice(buf, 5, -3);
  equal("Ferr", b->data);
  buffer_t *c = buffer_slice(buf, 8, -1);
  equal("ret", c->data);
  buffer_free(buf);
  buffer_free(a);
  buffer_free(b);
  buffer_free(c);
}

void test_buffer_slice__end_overflow()
{
  buffer_t *buf = buffer_new_with_copy("Tobi Ferret");
  buffer_t *a = buffer_slice(buf, 5, 1000);
  equal("Tobi Ferret", buf->data);
  equal("Ferret", a->data);
  buffer_free(a);
  buffer_free(buf);
}

void test_buffer_equals()
{
  buffer_t *a = buffer_new_with_copy("Hello");
  buffer_t *b = buffer_new_with_copy("Hello");
  assert(1 == buffer_equals(a, b));
  buffer_append(b, " World");
  assert(0 == buffer_equals(a, b));
  buffer_free(a);
  buffer_free(b);
}

void test_buffer_formatting()
{
  buffer_t *buf = buffer_new();
  int result = buffer_appendf(buf, "%d %s", 3, "cow");
  assert(0 == result);
  equal("3 cow", buf->data);
  result = buffer_appendf(buf, " - 0x%08X", 0xdeadbeef);
  assert(0 == result);
  equal("3 cow - 0xDEADBEEF", buf->data);
  buffer_free(buf);
}

void test_buffer_indexof()
{
  buffer_t *buf = buffer_new_with_copy("Tobi is a ferret");
  ssize_t i = buffer_indexof(buf, "is");
  assert(5 == i);
  i = buffer_indexof(buf, "a");
  assert(8 == i);
  i = buffer_indexof(buf, "something");
  assert((-1) == i);
  buffer_free(buf);
}

void test_buffer_fill()
{
  buffer_t *buf = buffer_new_with_copy("Hello");
  assert(5 == buffer_length(buf));
  buffer_fill(buf, 0);
  assert(0 == buffer_length(buf));
  buffer_free(buf);
}

void test_buffer_clear()
{
  buffer_t *buf = buffer_new_with_copy("Hello");
  assert(5 == buffer_length(buf));
  buffer_clear(buf);
  assert(0 == buffer_length(buf));
  buffer_free(buf);
}

void test_buffer_trim()
{
  buffer_t *buf = buffer_new_with_copy("  Hello\n\n ");
  unsigned int buf_idx = 0;
  buffer_trim(buf);
  equal("Hello", buf->data);
  buffer_free(buf);
  buf_idx = buffer_new_with_copy("  Hello\n\n ");
  buffer_trim_left(buf);
  equal("Hello\n\n ", buf->data);
  buffer_free(buf);
  buf_idx = buffer_new_with_copy("  Hello\n\n ");
  buffer_trim_right(buf);
  equal("  Hello", buf->data);
  buffer_free(buf);
}

void test_buffer_compact()
{
  buffer_t *buf = buffer_new_with_copy("  Hello\n\n ");
  buffer_trim(buf);
  assert(5 == buffer_length(buf));
  assert(10 == buffer_size(buf));
  ssize_t removed = buffer_compact(buf);
  assert(5 == removed);
  assert(5 == buffer_length(buf));
  assert(5 == buffer_size(buf));
  equal("Hello", buf->data);
  buffer_free(buf);
}

int main()
{
  test_buffer_new();
  test_buffer_new_with_size();
  test_buffer_append();
  test_buffer_append__grow();
  test_buffer_append_n();
  test_buffer_prepend();
  test_buffer_slice();
  test_buffer_slice__range_error();
  test_buffer_slice__end();
  test_buffer_slice__end_overflow();
  test_buffer_equals();
  test_buffer_formatting();
  test_buffer_indexof();
  test_buffer_fill();
  test_buffer_clear();
  test_buffer_trim();
  test_buffer_compact();
  printf("\n  \e[32m\u2713 \e[90mok\e[0m\n\n");
  return 0;
}

