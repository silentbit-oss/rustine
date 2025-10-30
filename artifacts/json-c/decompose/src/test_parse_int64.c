void checkit(const char *buf)
{
  int64_t cint64 = -666;
  int retval = json_parse_int64(buf, &cint64);
  printf("buf=%s parseit=%d, value=%d \n", buf, retval, cint64);
}


/*** DEPENDENCIES:
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
***/


void checkit_uint(const char *buf)
{
  uint64_t cuint64 = 666;
  int retval = json_parse_uint64(buf, &cuint64);
  printf("buf=%s parseit=%d, value=%u \n", buf, retval, cuint64);
}


/*** DEPENDENCIES:
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
***/


int main(int argc, char **argv)
{
  char buf[100];
  printf("==========json_parse_int64() test===========\n");
  checkit("x");
  checkit("0");
  checkit("-0");
  checkit("00000000");
  checkit("-00000000");
  checkit("1");
  strcpy(buf, "2147483647");
  checkit(buf);
  strcpy(buf, "-1");
  checkit(buf);
  strcpy(buf, "   -1");
  checkit(buf);
  strcpy(buf, "00001234");
  checkit(buf);
  strcpy(buf, "0001234x");
  checkit(buf);
  strcpy(buf, "-00001234");
  checkit(buf);
  strcpy(buf, "-00001234x");
  checkit(buf);
  strcpy(buf, "4294967295");
  checkit(buf);
  strcpy(buf, "4294967296");
  checkit(buf);
  strcpy(buf, "21474836470");
  checkit(buf);
  strcpy(buf, "31474836470");
  checkit(buf);
  strcpy(buf, "-2147483647");
  checkit(buf);
  strcpy(buf, "-2147483648");
  checkit(buf);
  strcpy(buf, "-2147483649");
  checkit(buf);
  strcpy(buf, "-21474836480");
  checkit(buf);
  strcpy(buf, "9223372036854775806");
  checkit(buf);
  strcpy(buf, "9223372036854775807");
  checkit(buf);
  strcpy(buf, "9223372036854775808");
  checkit(buf);
  strcpy(buf, "-9223372036854775808");
  checkit(buf);
  strcpy(buf, "-9223372036854775809");
  checkit(buf);
  strcpy(buf, "18446744073709551614");
  checkit(buf);
  strcpy(buf, "18446744073709551615");
  checkit(buf);
  strcpy(buf, "18446744073709551616");
  checkit(buf);
  strcpy(buf, "-18446744073709551616");
  checkit(buf);
  strcpy(buf, "123");
  checkit(buf);
  printf("\n==========json_parse_uint64() test===========\n");
  checkit_uint("x");
  checkit_uint("0");
  checkit_uint("-0");
  checkit_uint("00000000");
  checkit_uint("-00000000");
  checkit_uint("1");
  strcpy(buf, "2147483647");
  checkit_uint(buf);
  strcpy(buf, "-1");
  checkit_uint(buf);
  strcpy(buf, "-9223372036854775808");
  checkit_uint(buf);
  strcpy(buf, "   1");
  checkit_uint(buf);
  strcpy(buf, "00001234");
  checkit_uint(buf);
  strcpy(buf, "0001234x");
  checkit_uint(buf);
  strcpy(buf, "4294967295");
  checkit_uint(buf);
  strcpy(buf, "4294967296");
  checkit_uint(buf);
  strcpy(buf, "21474836470");
  checkit_uint(buf);
  strcpy(buf, "31474836470");
  checkit_uint(buf);
  strcpy(buf, "9223372036854775806");
  checkit_uint(buf);
  strcpy(buf, "9223372036854775807");
  checkit_uint(buf);
  strcpy(buf, "9223372036854775808");
  checkit_uint(buf);
  strcpy(buf, "18446744073709551614");
  checkit_uint(buf);
  strcpy(buf, "18446744073709551615");
  checkit_uint(buf);
  strcpy(buf, "18446744073709551616");
  checkit_uint(buf);
  strcpy(buf, "123");
  checkit_uint(buf);
  return 0;
}


/*** DEPENDENCIES:
void checkit(const char *buf)
{
  int64_t cint64 = -666;
  int retval = json_parse_int64(buf, &cint64);
  printf("buf=%s parseit=%d, value=%d \n", buf, retval, cint64);
}


----------------------------
void checkit_uint(const char *buf)
{
  uint64_t cuint64 = 666;
  int retval = json_parse_uint64(buf, &cuint64);
  printf("buf=%s parseit=%d, value=%u \n", buf, retval, cuint64);
}


----------------------------
***/


