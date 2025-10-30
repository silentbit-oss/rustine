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


/*** DEPENDENCIES:
***/


void test_buffer_slice__range_error()
{
  buffer_t *buf = buffer_new_with_copy("Tobi Ferret");
  buffer_t *a = buffer_slice(buf, 10, 2);
  assert(0 == a);
  buffer_free(buf);
}


/*** DEPENDENCIES:
void buffer_free(buffer_t *self)
{
  free(self->alloc);
  free(self);
}


----------------------------
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
buffer_t *buffer_new_with_copy(char *str)
{
  size_t len = strlen(str);
  buffer_t *self = buffer_new_with_size(len);
  if (!self)
  {
    return 0;
  }
  memcpy(self->alloc, str, len);
  self->data = self->alloc;
  return self;
}


----------------------------
buffer_t *buffer_slice(buffer_t *buf, size_t from, ssize_t to)
{
  size_t len = strlen(buf->data);
  if (to < from)
  {
    return 0;
  }
  if (to < 0)
  {
    to = len - (~to);
  }
  if (to > len)
  {
    to = len;
  }
  size_t n = to - from;
  buffer_t *self = buffer_new_with_size(n);
  memcpy(self->data, buf->data + from, n);
  return self;
}


----------------------------
***/


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


/*** DEPENDENCIES:
ssize_t buffer_indexof(buffer_t *self, char *str)
{
  char *sub = strstr(self->data, str);
  if (!sub)
  {
    return -1;
  }
  return sub - self->data;
}


----------------------------
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
buffer_t *buffer_new_with_copy(char *str)
{
  size_t len = strlen(str);
  buffer_t *self = buffer_new_with_size(len);
  if (!self)
  {
    return 0;
  }
  memcpy(self->alloc, str, len);
  self->data = self->alloc;
  return self;
}


----------------------------
void buffer_free(buffer_t *self)
{
  free(self->alloc);
  free(self);
}


----------------------------
***/


void test_buffer_new()
{
  buffer_t *buf = buffer_new();
  assert(64 == buffer_size(buf));
  assert(0 == buffer_length(buf));
  buffer_free(buf);
}


/*** DEPENDENCIES:
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
void buffer_free(buffer_t *self)
{
  free(self->alloc);
  free(self);
}


----------------------------
size_t buffer_size(buffer_t *self)
{
  return self->len;
}


----------------------------
size_t buffer_length(buffer_t *self)
{
  return strlen(self->data);
}


----------------------------
buffer_t *buffer_new()
{
  return buffer_new_with_size(64);
}


----------------------------
***/


void test_buffer_new_with_size()
{
  buffer_t *buf = buffer_new_with_size(1024);
  assert(1024 == buffer_size(buf));
  assert(0 == buffer_length(buf));
  buffer_free(buf);
}


/*** DEPENDENCIES:
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
buffer_t *buffer_new_with_size(size_t n)
{
  buffer_t *self = malloc(sizeof(buffer_t));
  if (!self)
  {
    return 0;
  }
  self->len = n;
  self->data = (self->alloc = calloc(n + 1, 1));
  return self;
}


----------------------------
void buffer_free(buffer_t *self)
{
  free(self->alloc);
  free(self);
}


----------------------------
size_t buffer_size(buffer_t *self)
{
  return self->len;
}


----------------------------
size_t buffer_length(buffer_t *self)
{
  return strlen(self->data);
}


----------------------------
***/


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


/*** DEPENDENCIES:
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
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


----------------------------
void buffer_free(buffer_t *self)
{
  free(self->alloc);
  free(self);
}


----------------------------
buffer_t *buffer_new_with_copy(char *str)
{
  size_t len = strlen(str);
  buffer_t *self = buffer_new_with_size(len);
  if (!self)
  {
    return 0;
  }
  memcpy(self->alloc, str, len);
  self->data = self->alloc;
  return self;
}


----------------------------
buffer_t *buffer_slice(buffer_t *buf, size_t from, ssize_t to)
{
  size_t len = strlen(buf->data);
  if (to < from)
  {
    return 0;
  }
  if (to < 0)
  {
    to = len - (~to);
  }
  if (to > len)
  {
    to = len;
  }
  size_t n = to - from;
  buffer_t *self = buffer_new_with_size(n);
  memcpy(self->data, buf->data + from, n);
  return self;
}


----------------------------
***/


void test_buffer_slice__end_overflow()
{
  buffer_t *buf = buffer_new_with_copy("Tobi Ferret");
  buffer_t *a = buffer_slice(buf, 5, 1000);
  equal("Tobi Ferret", buf->data);
  equal("Ferret", a->data);
  buffer_free(a);
  buffer_free(buf);
}


/*** DEPENDENCIES:
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
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


----------------------------
void buffer_free(buffer_t *self)
{
  free(self->alloc);
  free(self);
}


----------------------------
buffer_t *buffer_new_with_copy(char *str)
{
  size_t len = strlen(str);
  buffer_t *self = buffer_new_with_size(len);
  if (!self)
  {
    return 0;
  }
  memcpy(self->alloc, str, len);
  self->data = self->alloc;
  return self;
}


----------------------------
buffer_t *buffer_slice(buffer_t *buf, size_t from, ssize_t to)
{
  size_t len = strlen(buf->data);
  if (to < from)
  {
    return 0;
  }
  if (to < 0)
  {
    to = len - (~to);
  }
  if (to > len)
  {
    to = len;
  }
  size_t n = to - from;
  buffer_t *self = buffer_new_with_size(n);
  memcpy(self->data, buf->data + from, n);
  return self;
}


----------------------------
***/


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


/*** DEPENDENCIES:
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
int buffer_equals(buffer_t *self, buffer_t *other)
{
  return 0 == strcmp(self->data, other->data);
}


----------------------------
void buffer_free(buffer_t *self)
{
  free(self->alloc);
  free(self);
}


----------------------------
buffer_t *buffer_new_with_copy(char *str)
{
  size_t len = strlen(str);
  buffer_t *self = buffer_new_with_size(len);
  if (!self)
  {
    return 0;
  }
  memcpy(self->alloc, str, len);
  self->data = self->alloc;
  return self;
}


----------------------------
int buffer_append(buffer_t *self, const char *str)
{
  return buffer_append_n(self, str, strlen(str));
}


----------------------------
***/


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


/*** DEPENDENCIES:
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
void buffer_free(buffer_t *self)
{
  free(self->alloc);
  free(self);
}


----------------------------
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


----------------------------
int buffer_appendf(buffer_t *self, const char *format, ...)
{
  va_list ap;
  va_list tmpa;
  char *dst = 0;
  unsigned int dst_idx = 0;
  int length = 0;
  int required = 0;
  int bytes = 0;
  __builtin_va_start(ap);
  length = buffer_length(self);
  va_copy(tmpa, ap);
  required = vsnprintf(0, 0, format, tmpa);
  ;
  if ((-1) == buffer_resize(self, length + required))
  {
    ;
    return -1;
  }
  dst_idx = self->data + length;
  bytes = vsnprintf(dst, 1 + required, format, ap);
  ;
  return (bytes < 0) ? (-1) : (0);
}


----------------------------
buffer_t *buffer_new()
{
  return buffer_new_with_size(64);
}


----------------------------
***/


void test_buffer_fill()
{
  buffer_t *buf = buffer_new_with_copy("Hello");
  assert(5 == buffer_length(buf));
  buffer_fill(buf, 0);
  assert(0 == buffer_length(buf));
  buffer_free(buf);
}


/*** DEPENDENCIES:
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
void buffer_free(buffer_t *self)
{
  free(self->alloc);
  free(self);
}


----------------------------
buffer_t *buffer_new_with_copy(char *str)
{
  size_t len = strlen(str);
  buffer_t *self = buffer_new_with_size(len);
  if (!self)
  {
    return 0;
  }
  memcpy(self->alloc, str, len);
  self->data = self->alloc;
  return self;
}


----------------------------
size_t buffer_length(buffer_t *self)
{
  return strlen(self->data);
}


----------------------------
void buffer_fill(buffer_t *self, int c)
{
  memset(self->data, c, self->len);
}


----------------------------
***/


void test_buffer_clear()
{
  buffer_t *buf = buffer_new_with_copy("Hello");
  assert(5 == buffer_length(buf));
  buffer_clear(buf);
  assert(0 == buffer_length(buf));
  buffer_free(buf);
}


/*** DEPENDENCIES:
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
void buffer_free(buffer_t *self)
{
  free(self->alloc);
  free(self);
}


----------------------------
buffer_t *buffer_new_with_copy(char *str)
{
  size_t len = strlen(str);
  buffer_t *self = buffer_new_with_size(len);
  if (!self)
  {
    return 0;
  }
  memcpy(self->alloc, str, len);
  self->data = self->alloc;
  return self;
}


----------------------------
size_t buffer_length(buffer_t *self)
{
  return strlen(self->data);
}


----------------------------
void buffer_clear(buffer_t *self)
{
  buffer_fill(self, 0);
}


----------------------------
***/


void test_buffer_append()
{
  buffer_t *buf = buffer_new();
  assert(0 == buffer_append(buf, "Hello"));
  assert(0 == buffer_append(buf, " World"));
  assert(strlen("Hello World") == buffer_length(buf));
  equal("Hello World", buf->data);
  buffer_free(buf);
}


/*** DEPENDENCIES:
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
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


----------------------------
void buffer_free(buffer_t *self)
{
  free(self->alloc);
  free(self);
}


----------------------------
int buffer_append(buffer_t *self, const char *str)
{
  return buffer_append_n(self, str, strlen(str));
}


----------------------------
size_t buffer_length(buffer_t *self)
{
  return strlen(self->data);
}


----------------------------
buffer_t *buffer_new()
{
  return buffer_new_with_size(64);
}


----------------------------
***/


void test_buffer_append_n()
{
  buffer_t *buf = buffer_new();
  assert(0 == buffer_append_n(buf, "subway", 3));
  assert(0 == buffer_append_n(buf, "marines", 6));
  assert(strlen("submarine") == buffer_length(buf));
  equal("submarine", buf->data);
  buffer_free(buf);
}


/*** DEPENDENCIES:
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
int buffer_append_n(buffer_t *self, const char *str, size_t len)
{
  size_t prev = strlen(self->data);
  size_t needed = len + prev;
  if (self->len > needed)
  {
    strncat(self->data, str, len);
    return 0;
  }
  int ret = buffer_resize(self, needed);
  if ((-1) == ret)
  {
    return -1;
  }
  strncat(self->data, str, len);
  return 0;
}


----------------------------
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


----------------------------
void buffer_free(buffer_t *self)
{
  free(self->alloc);
  free(self);
}


----------------------------
size_t buffer_length(buffer_t *self)
{
  return strlen(self->data);
}


----------------------------
buffer_t *buffer_new()
{
  return buffer_new_with_size(64);
}


----------------------------
***/


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


/*** DEPENDENCIES:
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
void buffer_free(buffer_t *self)
{
  free(self->alloc);
  free(self);
}


----------------------------
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


----------------------------
int buffer_append(buffer_t *self, const char *str)
{
  return buffer_append_n(self, str, strlen(str));
}


----------------------------
buffer_t *buffer_new()
{
  return buffer_new_with_size(64);
}


----------------------------
buffer_t *buffer_slice(buffer_t *buf, size_t from, ssize_t to)
{
  size_t len = strlen(buf->data);
  if (to < from)
  {
    return 0;
  }
  if (to < 0)
  {
    to = len - (~to);
  }
  if (to > len)
  {
    to = len;
  }
  size_t n = to - from;
  buffer_t *self = buffer_new_with_size(n);
  memcpy(self->data, buf->data + from, n);
  return self;
}


----------------------------
***/


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


/*** DEPENDENCIES:
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
buffer_t *buffer_new_with_size(size_t n)
{
  buffer_t *self = malloc(sizeof(buffer_t));
  if (!self)
  {
    return 0;
  }
  self->len = n;
  self->data = (self->alloc = calloc(n + 1, 1));
  return self;
}


----------------------------
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


----------------------------
void buffer_free(buffer_t *self)
{
  free(self->alloc);
  free(self);
}


----------------------------
size_t buffer_size(buffer_t *self)
{
  return self->len;
}


----------------------------
int buffer_append(buffer_t *self, const char *str)
{
  return buffer_append_n(self, str, strlen(str));
}


----------------------------
size_t buffer_length(buffer_t *self)
{
  return strlen(self->data);
}


----------------------------
***/


void test_buffer_prepend()
{
  buffer_t *buf = buffer_new();
  assert(0 == buffer_append(buf, " World"));
  assert(0 == buffer_prepend(buf, "Hello"));
  assert(strlen("Hello World") == buffer_length(buf));
  equal("Hello World", buf->data);
  buffer_free(buf);
}


/*** DEPENDENCIES:
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
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


----------------------------
void buffer_free(buffer_t *self)
{
  free(self->alloc);
  free(self);
}


----------------------------
int buffer_append(buffer_t *self, const char *str)
{
  return buffer_append_n(self, str, strlen(str));
}


----------------------------
size_t buffer_length(buffer_t *self)
{
  return strlen(self->data);
}


----------------------------
int buffer_prepend(buffer_t *self, char *str)
{
  size_t len = strlen(str);
  size_t prev = strlen(self->data);
  size_t needed = len + prev;
  if (self->len > needed)
  {
    goto move;
  }
  int ret = buffer_resize(self, needed);
  if ((-1) == ret)
  {
    return -1;
  }
  move:
  memmove(self->data + len, self->data, len + 1);

  memcpy(self->data, str, len);
  return 0;
}


----------------------------
buffer_t *buffer_new()
{
  return buffer_new_with_size(64);
}


----------------------------
***/


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


/*** DEPENDENCIES:
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
void buffer_free(buffer_t *self)
{
  free(self->alloc);
  free(self);
}


----------------------------
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


----------------------------
void buffer_trim_left(buffer_t *self)
{
  int c;
  while ((c = *self->data) && isspace(c))
  {
    self->data += 1;
  }

}


----------------------------
void buffer_trim(buffer_t *self)
{
  buffer_trim_left(self);
  buffer_trim_right(self);
}


----------------------------
buffer_t *buffer_new_with_copy(char *str)
{
  size_t len = strlen(str);
  buffer_t *self = buffer_new_with_size(len);
  if (!self)
  {
    return 0;
  }
  memcpy(self->alloc, str, len);
  self->data = self->alloc;
  return self;
}


----------------------------
void buffer_trim_right(buffer_t *self)
{
  int c;
  size_t i = buffer_length(self) - 1;
  while ((c = self->data[i]) && isspace(c))
  {
    self->data[i] = 0;
    i -= 1;
  }

}


----------------------------
***/


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


/*** DEPENDENCIES:
typedef struct 
{
  size_t len;
  char *alloc;
  char *data;
} buffer_t
----------------------------
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


----------------------------
void buffer_free(buffer_t *self)
{
  free(self->alloc);
  free(self);
}


----------------------------
ssize_t buffer_compact(buffer_t *self)
{
  size_t len = buffer_length(self);
  size_t rem = self->len - len;
  char *buf = calloc(len + 1, 1);
  if (!buf)
  {
    return -1;
  }
  memcpy(buf, self->data, len);
  free(self->alloc);
  self->len = len;
  self->data = (self->alloc = buf);
  return rem;
}


----------------------------
size_t buffer_size(buffer_t *self)
{
  return self->len;
}


----------------------------
void buffer_trim(buffer_t *self)
{
  buffer_trim_left(self);
  buffer_trim_right(self);
}


----------------------------
buffer_t *buffer_new_with_copy(char *str)
{
  size_t len = strlen(str);
  buffer_t *self = buffer_new_with_size(len);
  if (!self)
  {
    return 0;
  }
  memcpy(self->alloc, str, len);
  self->data = self->alloc;
  return self;
}


----------------------------
size_t buffer_length(buffer_t *self)
{
  return strlen(self->data);
}


----------------------------
***/


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


/*** DEPENDENCIES:
void test_buffer_clear()
{
  buffer_t *buf = buffer_new_with_copy("Hello");
  assert(5 == buffer_length(buf));
  buffer_clear(buf);
  assert(0 == buffer_length(buf));
  buffer_free(buf);
}


----------------------------
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


----------------------------
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


----------------------------
void test_buffer_new_with_size()
{
  buffer_t *buf = buffer_new_with_size(1024);
  assert(1024 == buffer_size(buf));
  assert(0 == buffer_length(buf));
  buffer_free(buf);
}


----------------------------
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


----------------------------
void test_buffer_append()
{
  buffer_t *buf = buffer_new();
  assert(0 == buffer_append(buf, "Hello"));
  assert(0 == buffer_append(buf, " World"));
  assert(strlen("Hello World") == buffer_length(buf));
  equal("Hello World", buf->data);
  buffer_free(buf);
}


----------------------------
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


----------------------------
void test_buffer_prepend()
{
  buffer_t *buf = buffer_new();
  assert(0 == buffer_append(buf, " World"));
  assert(0 == buffer_prepend(buf, "Hello"));
  assert(strlen("Hello World") == buffer_length(buf));
  equal("Hello World", buf->data);
  buffer_free(buf);
}


----------------------------
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


----------------------------
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


----------------------------
void test_buffer_fill()
{
  buffer_t *buf = buffer_new_with_copy("Hello");
  assert(5 == buffer_length(buf));
  buffer_fill(buf, 0);
  assert(0 == buffer_length(buf));
  buffer_free(buf);
}


----------------------------
void test_buffer_slice__end_overflow()
{
  buffer_t *buf = buffer_new_with_copy("Tobi Ferret");
  buffer_t *a = buffer_slice(buf, 5, 1000);
  equal("Tobi Ferret", buf->data);
  equal("Ferret", a->data);
  buffer_free(a);
  buffer_free(buf);
}


----------------------------
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


----------------------------
void test_buffer_slice__range_error()
{
  buffer_t *buf = buffer_new_with_copy("Tobi Ferret");
  buffer_t *a = buffer_slice(buf, 10, 2);
  assert(0 == a);
  buffer_free(buf);
}


----------------------------
void test_buffer_append_n()
{
  buffer_t *buf = buffer_new();
  assert(0 == buffer_append_n(buf, "subway", 3));
  assert(0 == buffer_append_n(buf, "marines", 6));
  assert(strlen("submarine") == buffer_length(buf));
  equal("submarine", buf->data);
  buffer_free(buf);
}


----------------------------
void test_buffer_new()
{
  buffer_t *buf = buffer_new();
  assert(64 == buffer_size(buf));
  assert(0 == buffer_length(buf));
  buffer_free(buf);
}


----------------------------
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


----------------------------
***/


