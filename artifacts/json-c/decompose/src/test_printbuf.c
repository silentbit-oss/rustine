static void test_printbuf_memset_length(void)
{
  struct printbuf *pb;
  unsigned int pb_idx = 0;
  printf("%s: starting test\n", __FUNCTION__);
  pb_idx = printbuf_new();
  printbuf_memset(pb, -1, ' ', 0);
  printbuf_memset(pb, -1, ' ', 0);
  printbuf_memset(pb, -1, ' ', 0);
  printbuf_memset(pb, -1, ' ', 0);
  printbuf_memset(pb, -1, ' ', 0);
  printf("Buffer length: %d\n", pb->bpos);
  printbuf_memset(pb, -1, ' ', 2);
  printbuf_memset(pb, -1, ' ', 4);
  printbuf_memset(pb, -1, ' ', 6);
  printf("Buffer length: %d\n", pb->bpos);
  printbuf_memset(pb, -1, ' ', 6);
  printf("Buffer length: %d\n", pb->bpos);
  printbuf_memset(pb, -1, ' ', 8);
  printbuf_memset(pb, -1, ' ', 10);
  printbuf_memset(pb, -1, ' ', 10);
  printbuf_memset(pb, -1, ' ', 10);
  printbuf_memset(pb, -1, ' ', 20);
  printf("Buffer length: %d\n", pb->bpos);
  printbuf_memset(pb, 0, 'x', 30);
  printf("Buffer length: %d\n", pb->bpos);
  printbuf_memset(pb, 0, 'x', pb->bpos + 1);
  printf("Buffer length: %d\n", pb->bpos);
  printbuf_free(pb);
  printf("%s: end test\n", __FUNCTION__);
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
int printbuf_memset(struct printbuf *pb, int offset, int charvalue, int len)
{
  int size_needed;
  if (offset == (-1))
  {
    offset = pb->bpos;
  }
  if (((len < 0) || (offset < (-1))) || (len > (2147483647 - offset)))
  {
    errno = EFBIG;
    return -1;
  }
  size_needed = offset + len;
  if (pb->size < size_needed)
  {
    if (printbuf_extend(pb, size_needed) < 0)
    {
      return -1;
    }
  }
  if (pb->bpos < offset)
  {
    memset(pb->buf + pb->bpos, '\0', offset - pb->bpos);
  }
  memset(pb->buf + offset, charvalue, len);
  if (pb->bpos < size_needed)
  {
    pb->bpos = size_needed;
  }
  return 0;
}


----------------------------
void printbuf_free(struct printbuf *p)
{
  if (p)
  {
    free(p->buf);
    free(p);
  }
}


----------------------------
struct printbuf
{
  char *buf;
  int bpos;
  int size;
}
----------------------------
***/


static void test_basic_printbuf_memset(void)
{
  struct printbuf *pb;
  unsigned int pb_idx = 0;
  printf("%s: starting test\n", __FUNCTION__);
  pb_idx = printbuf_new();
  sprintbuf(pb, "blue:%d", 1);
  printbuf_memset(pb, -1, 'x', 52);
  printf("Buffer contents:%.*s\n", pb->bpos, pb->buf);
  printbuf_free(pb);
  printf("%s: end test\n", __FUNCTION__);
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
int printbuf_memset(struct printbuf *pb, int offset, int charvalue, int len)
{
  int size_needed;
  if (offset == (-1))
  {
    offset = pb->bpos;
  }
  if (((len < 0) || (offset < (-1))) || (len > (2147483647 - offset)))
  {
    errno = EFBIG;
    return -1;
  }
  size_needed = offset + len;
  if (pb->size < size_needed)
  {
    if (printbuf_extend(pb, size_needed) < 0)
    {
      return -1;
    }
  }
  if (pb->bpos < offset)
  {
    memset(pb->buf + pb->bpos, '\0', offset - pb->bpos);
  }
  memset(pb->buf + offset, charvalue, len);
  if (pb->bpos < size_needed)
  {
    pb->bpos = size_needed;
  }
  return 0;
}


----------------------------
void printbuf_free(struct printbuf *p)
{
  if (p)
  {
    free(p->buf);
    free(p);
  }
}


----------------------------
int sprintbuf(struct printbuf *p, const char *msg, ...)
{
  va_list ap;
  char *t;
  int size;
  char buf[128];
  __builtin_va_start(ap);
  size = vsnprintf(buf, 128, msg, ap);
  ;
  if ((size < 0) || (size > 127))
  {
    __builtin_va_start(ap);
    if ((size = vasprintf(&t, msg, ap)) < 0)
    {
      ;
      return -1;
    }
    ;
    size = printbuf_memappend(p, t, size);
    free(t);
  }
  else
  {
    size = printbuf_memappend(p, buf, size);
  }
  return size;
}


----------------------------
struct printbuf
{
  char *buf;
  int bpos;
  int size;
}
----------------------------
***/


static void test_printbuf_memappend(int *before_resize)
{
  struct printbuf *pb;
  unsigned int pb_idx = 0;
  int initial_size;
  printf("%s: starting test\n", __FUNCTION__);
  pb_idx = printbuf_new();
  printf("Buffer length: %d\n", pb->bpos);
  initial_size = pb->size;
  while (pb->size == initial_size)
  {
    do
    {
      if ((pb->size - pb->bpos) > 1)
      {
        memcpy(pb->buf + pb->bpos, "x", 1);
        pb->bpos += 1;
        pb->buf[pb->bpos] = '\0';
      }
      else
      {
        printbuf_memappend(pb, "x", 1);
      }
    }
    while (0);
  }

  *before_resize = pb->bpos - 1;
  printf("Appended %d bytes for resize: [%s]\n", (*before_resize) + 1, pb->buf);
  printbuf_reset(pb);
  do
  {
    if ((pb->size - pb->bpos) > 3)
    {
      memcpy(pb->buf + pb->bpos, "bluexyz123", 3);
      pb->bpos += 3;
      pb->buf[pb->bpos] = '\0';
    }
    else
    {
      printbuf_memappend(pb, "bluexyz123", 3);
    }
  }
  while (0);
  printf("Partial append: %d, [%s]\n", pb->bpos, pb->buf);
  char with_nulls[] = {'a', 'b', '\0', 'c'};
  printbuf_reset(pb);
  do
  {
    if ((pb->size - pb->bpos) > ((int) (sizeof(with_nulls))))
    {
      memcpy(pb->buf + pb->bpos, with_nulls, (int) (sizeof(with_nulls)));
      pb->bpos += (int) (sizeof(with_nulls));
      pb->buf[pb->bpos] = '\0';
    }
    else
    {
      printbuf_memappend(pb, with_nulls, (int) (sizeof(with_nulls)));
    }
  }
  while (0);
  printf("With embedded \\0 character: %d, [%s]\n", pb->bpos, pb->buf);
  printbuf_free(pb);
  pb_idx = printbuf_new();
  char *data = malloc(*before_resize);
  unsigned int data_idx = 0;
  memset(data, 'X', *before_resize);
  do
  {
    if ((pb->size - pb->bpos) > (*before_resize))
    {
      memcpy(pb->buf + pb->bpos, data, *before_resize);
      pb->bpos += *before_resize;
      pb->buf[pb->bpos] = '\0';
    }
    else
    {
      printbuf_memappend(pb, data, *before_resize);
    }
  }
  while (0);
  printf("Append to just before resize: %d, [%s]\n", pb->bpos, pb->buf);
  free(data);
  printbuf_free(pb);
  pb_idx = printbuf_new();
  data_idx = malloc((*before_resize) + 1);
  memset(data, 'X', (*before_resize) + 1);
  do
  {
    if ((pb->size - pb->bpos) > ((*before_resize) + 1))
    {
      memcpy(pb->buf + pb->bpos, data, (*before_resize) + 1);
      pb->bpos += (*before_resize) + 1;
      pb->buf[pb->bpos] = '\0';
    }
    else
    {
      printbuf_memappend(pb, data, (*before_resize) + 1);
    }
  }
  while (0);
  printf("Append to just after resize: %d, [%s]\n", pb->bpos, pb->buf);
  free(data);
  printbuf_free(pb);
  pb_idx = printbuf_new();
  printbuf_memappend(pb, "XXXXXXXXXXXXXXXX", (sizeof("XXXXXXXXXXXXXXXX")) - 1);
  printf("Buffer size after printbuf_strappend(): %d, [%s]\n", pb->bpos, pb->buf);
  printbuf_free(pb);
  printf("%s: end test\n", __FUNCTION__);
}


/*** DEPENDENCIES:
void printbuf_reset(struct printbuf *p)
{
  p->buf[0] = '\0';
  p->bpos = 0;
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
void printbuf_free(struct printbuf *p)
{
  if (p)
  {
    free(p->buf);
    free(p);
  }
}


----------------------------
struct printbuf
{
  char *buf;
  int bpos;
  int size;
}
----------------------------
***/


static void test_sprintbuf(int before_resize)
{
  struct printbuf *pb;
  unsigned int pb_idx = 0;
  const char *max_char = "if string is greater than stack buffer, then use dynamic string with vasprintf.  Note: some implementation of vsnprintf return -1  if output is truncated whereas some return the number of bytes that  would have been written - this code handles both cases.";
  printf("%s: starting test\n", __FUNCTION__);
  pb_idx = printbuf_new();
  printf("Buffer length: %d\n", pb->bpos);
  char *data = malloc((before_resize + 1) + 1);
  memset(data, 'X', (before_resize + 1) + 1);
  data[before_resize + 1] = '\0';
  sprintbuf(pb, "%s", data);
  free(data);
  printf("sprintbuf to just after resize(%d+1): %d, [%s], strlen(buf)=%d\n", before_resize, pb->bpos, pb->buf, (int) strlen(pb->buf));
  printbuf_reset(pb);
  sprintbuf(pb, "plain");
  printf("%d, [%s]\n", pb->bpos, pb->buf);
  sprintbuf(pb, "%d", 1);
  printf("%d, [%s]\n", pb->bpos, pb->buf);
  sprintbuf(pb, "%d", 2147483647);
  printf("%d, [%s]\n", pb->bpos, pb->buf);
  sprintbuf(pb, "%d", -2147483648);
  printf("%d, [%s]\n", pb->bpos, pb->buf);
  sprintbuf(pb, "%s", "%s");
  printf("%d, [%s]\n", pb->bpos, pb->buf);
  sprintbuf(pb, max_char);
  printf("%d, [%s]\n", pb->bpos, pb->buf);
  printbuf_free(pb);
  printf("%s: end test\n", __FUNCTION__);
}


/*** DEPENDENCIES:
void printbuf_reset(struct printbuf *p)
{
  p->buf[0] = '\0';
  p->bpos = 0;
}


----------------------------
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
void printbuf_free(struct printbuf *p)
{
  if (p)
  {
    free(p->buf);
    free(p);
  }
}


----------------------------
int sprintbuf(struct printbuf *p, const char *msg, ...)
{
  va_list ap;
  char *t;
  int size;
  char buf[128];
  __builtin_va_start(ap);
  size = vsnprintf(buf, 128, msg, ap);
  ;
  if ((size < 0) || (size > 127))
  {
    __builtin_va_start(ap);
    if ((size = vasprintf(&t, msg, ap)) < 0)
    {
      ;
      return -1;
    }
    ;
    size = printbuf_memappend(p, t, size);
    free(t);
  }
  else
  {
    size = printbuf_memappend(p, buf, size);
  }
  return size;
}


----------------------------
struct printbuf
{
  char *buf;
  int bpos;
  int size;
}
----------------------------
***/


int main(int argc, char **argv)
{
  int before_resize = 0;
  if (0)
  {
    mc_set_debug(1);
  }
  test_basic_printbuf_memset();
  printf("========================================\n");
  test_printbuf_memset_length();
  printf("========================================\n");
  test_printbuf_memappend(&before_resize);
  printf("========================================\n");
  test_sprintbuf(before_resize);
  printf("========================================\n");
  return 0;
}


/*** DEPENDENCIES:
void mc_set_debug(int debug)
{
  _debug = debug;
}


----------------------------
static void test_basic_printbuf_memset(void)
{
  struct printbuf *pb;
  unsigned int pb_idx = 0;
  printf("%s: starting test\n", __FUNCTION__);
  pb_idx = printbuf_new();
  sprintbuf(pb, "blue:%d", 1);
  printbuf_memset(pb, -1, 'x', 52);
  printf("Buffer contents:%.*s\n", pb->bpos, pb->buf);
  printbuf_free(pb);
  printf("%s: end test\n", __FUNCTION__);
}


----------------------------
static void test_printbuf_memset_length(void)
{
  struct printbuf *pb;
  unsigned int pb_idx = 0;
  printf("%s: starting test\n", __FUNCTION__);
  pb_idx = printbuf_new();
  printbuf_memset(pb, -1, ' ', 0);
  printbuf_memset(pb, -1, ' ', 0);
  printbuf_memset(pb, -1, ' ', 0);
  printbuf_memset(pb, -1, ' ', 0);
  printbuf_memset(pb, -1, ' ', 0);
  printf("Buffer length: %d\n", pb->bpos);
  printbuf_memset(pb, -1, ' ', 2);
  printbuf_memset(pb, -1, ' ', 4);
  printbuf_memset(pb, -1, ' ', 6);
  printf("Buffer length: %d\n", pb->bpos);
  printbuf_memset(pb, -1, ' ', 6);
  printf("Buffer length: %d\n", pb->bpos);
  printbuf_memset(pb, -1, ' ', 8);
  printbuf_memset(pb, -1, ' ', 10);
  printbuf_memset(pb, -1, ' ', 10);
  printbuf_memset(pb, -1, ' ', 10);
  printbuf_memset(pb, -1, ' ', 20);
  printf("Buffer length: %d\n", pb->bpos);
  printbuf_memset(pb, 0, 'x', 30);
  printf("Buffer length: %d\n", pb->bpos);
  printbuf_memset(pb, 0, 'x', pb->bpos + 1);
  printf("Buffer length: %d\n", pb->bpos);
  printbuf_free(pb);
  printf("%s: end test\n", __FUNCTION__);
}


----------------------------
static void test_sprintbuf(int before_resize)
{
  struct printbuf *pb;
  unsigned int pb_idx = 0;
  const char *max_char = "if string is greater than stack buffer, then use dynamic string with vasprintf.  Note: some implementation of vsnprintf return -1  if output is truncated whereas some return the number of bytes that  would have been written - this code handles both cases.";
  printf("%s: starting test\n", __FUNCTION__);
  pb_idx = printbuf_new();
  printf("Buffer length: %d\n", pb->bpos);
  char *data = malloc((before_resize + 1) + 1);
  memset(data, 'X', (before_resize + 1) + 1);
  data[before_resize + 1] = '\0';
  sprintbuf(pb, "%s", data);
  free(data);
  printf("sprintbuf to just after resize(%d+1): %d, [%s], strlen(buf)=%d\n", before_resize, pb->bpos, pb->buf, (int) strlen(pb->buf));
  printbuf_reset(pb);
  sprintbuf(pb, "plain");
  printf("%d, [%s]\n", pb->bpos, pb->buf);
  sprintbuf(pb, "%d", 1);
  printf("%d, [%s]\n", pb->bpos, pb->buf);
  sprintbuf(pb, "%d", 2147483647);
  printf("%d, [%s]\n", pb->bpos, pb->buf);
  sprintbuf(pb, "%d", -2147483648);
  printf("%d, [%s]\n", pb->bpos, pb->buf);
  sprintbuf(pb, "%s", "%s");
  printf("%d, [%s]\n", pb->bpos, pb->buf);
  sprintbuf(pb, max_char);
  printf("%d, [%s]\n", pb->bpos, pb->buf);
  printbuf_free(pb);
  printf("%s: end test\n", __FUNCTION__);
}


----------------------------
static void test_printbuf_memappend(int *before_resize)
{
  struct printbuf *pb;
  unsigned int pb_idx = 0;
  int initial_size;
  printf("%s: starting test\n", __FUNCTION__);
  pb_idx = printbuf_new();
  printf("Buffer length: %d\n", pb->bpos);
  initial_size = pb->size;
  while (pb->size == initial_size)
  {
    do
    {
      if ((pb->size - pb->bpos) > 1)
      {
        memcpy(pb->buf + pb->bpos, "x", 1);
        pb->bpos += 1;
        pb->buf[pb->bpos] = '\0';
      }
      else
      {
        printbuf_memappend(pb, "x", 1);
      }
    }
    while (0);
  }

  *before_resize = pb->bpos - 1;
  printf("Appended %d bytes for resize: [%s]\n", (*before_resize) + 1, pb->buf);
  printbuf_reset(pb);
  do
  {
    if ((pb->size - pb->bpos) > 3)
    {
      memcpy(pb->buf + pb->bpos, "bluexyz123", 3);
      pb->bpos += 3;
      pb->buf[pb->bpos] = '\0';
    }
    else
    {
      printbuf_memappend(pb, "bluexyz123", 3);
    }
  }
  while (0);
  printf("Partial append: %d, [%s]\n", pb->bpos, pb->buf);
  char with_nulls[] = {'a', 'b', '\0', 'c'};
  printbuf_reset(pb);
  do
  {
    if ((pb->size - pb->bpos) > ((int) (sizeof(with_nulls))))
    {
      memcpy(pb->buf + pb->bpos, with_nulls, (int) (sizeof(with_nulls)));
      pb->bpos += (int) (sizeof(with_nulls));
      pb->buf[pb->bpos] = '\0';
    }
    else
    {
      printbuf_memappend(pb, with_nulls, (int) (sizeof(with_nulls)));
    }
  }
  while (0);
  printf("With embedded \\0 character: %d, [%s]\n", pb->bpos, pb->buf);
  printbuf_free(pb);
  pb_idx = printbuf_new();
  char *data = malloc(*before_resize);
  unsigned int data_idx = 0;
  memset(data, 'X', *before_resize);
  do
  {
    if ((pb->size - pb->bpos) > (*before_resize))
    {
      memcpy(pb->buf + pb->bpos, data, *before_resize);
      pb->bpos += *before_resize;
      pb->buf[pb->bpos] = '\0';
    }
    else
    {
      printbuf_memappend(pb, data, *before_resize);
    }
  }
  while (0);
  printf("Append to just before resize: %d, [%s]\n", pb->bpos, pb->buf);
  free(data);
  printbuf_free(pb);
  pb_idx = printbuf_new();
  data_idx = malloc((*before_resize) + 1);
  memset(data, 'X', (*before_resize) + 1);
  do
  {
    if ((pb->size - pb->bpos) > ((*before_resize) + 1))
    {
      memcpy(pb->buf + pb->bpos, data, (*before_resize) + 1);
      pb->bpos += (*before_resize) + 1;
      pb->buf[pb->bpos] = '\0';
    }
    else
    {
      printbuf_memappend(pb, data, (*before_resize) + 1);
    }
  }
  while (0);
  printf("Append to just after resize: %d, [%s]\n", pb->bpos, pb->buf);
  free(data);
  printbuf_free(pb);
  pb_idx = printbuf_new();
  printbuf_memappend(pb, "XXXXXXXXXXXXXXXX", (sizeof("XXXXXXXXXXXXXXXX")) - 1);
  printf("Buffer size after printbuf_strappend(): %d, [%s]\n", pb->bpos, pb->buf);
  printbuf_free(pb);
  printf("%s: end test\n", __FUNCTION__);
}


----------------------------
***/


