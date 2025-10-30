char *stripchr(char *mainstr, int separator)
{
  char *ptr;
  unsigned int ptr_idx = 0;
  if (mainstr == 0)
  {
    return 0;
  }
  ptr_idx = strchr(mainstr, separator);
  if ((&ptr[ptr_idx]) == 0)
  {
    return 0;
  }
  ptr[0 + ptr_idx] = '\0';
  ptr_idx += 1;
  return ptr;
}


/*** DEPENDENCIES:
***/


void test_value_copy()
{
  printf("testing binn value copy... ");
  puts("TODO!!!");
}


/*** DEPENDENCIES:
***/


char *date_to_str(unsigned short date)
{
  int day;
  int month;
  int year;
  day = (date & 0xf800) >> 11;
  month = (date & 0x0780) >> 7;
  year = date & 0x007f;
  sprintf(tmp, "%.4d-%.2d-%.2d", year + 1900, month, day);
  return tmp;
}


/*** DEPENDENCIES:
char tmp[128]
----------------------------
***/


int64 str_to_currency(char *str)
{
  unsigned int str_idx = 0;
  char *next;
  unsigned int next_idx = 0;
  int size;
  int i;
  if ((&str[str_idx]) == 0)
  {
    return 0;
  }
  strcpy(tmp, str);
  str_idx = tmp;
  next_idx = strchr(str, '.');
  if (next)
  {
    size = strlen((&next[next_idx]) + 1);
    memmove(next, (&next[next_idx]) + 1, size + 1);
    if (size <= 4)
    {
      size = 4 - size;
      for (i = 0; i < size; i += 1)
        strcat(str, "0");

    }
    else
    {
      next[4 + next_idx] = 0;
    }
  }
  else
  {
    strcat(str, "0000");
  }
  return atoi64(str);
}


/*** DEPENDENCIES:
int64 atoi64(char *str)
{
  unsigned int str_idx = 0;
  int64 retval;
  int is_negative = 0;
  if (str[str_idx] == '-')
  {
    is_negative = 1;
    str_idx += 1;
  }
  retval = 0;
  for (; str[str_idx]; str_idx += 1)
  {
    retval = (10 * retval) + (str[str_idx] - '0');
  }

  if (is_negative)
  {
    retval *= -1;
  }
  return retval;
}


----------------------------
char tmp[128]
----------------------------
***/


int64 float_to_currency(double value)
{
  char buf[128];
  snprintf(buf, 127, "%.4f", value);
  return str_to_currency(buf);
}


/*** DEPENDENCIES:
int64 str_to_currency(char *str)
{
  unsigned int str_idx = 0;
  char *next;
  unsigned int next_idx = 0;
  int size;
  int i;
  if ((&str[str_idx]) == 0)
  {
    return 0;
  }
  strcpy(tmp, str);
  str_idx = tmp;
  next_idx = strchr(str, '.');
  if (next)
  {
    size = strlen((&next[next_idx]) + 1);
    memmove(next, (&next[next_idx]) + 1, size + 1);
    if (size <= 4)
    {
      size = 4 - size;
      for (i = 0; i < size; i += 1)
        strcat(str, "0");

    }
    else
    {
      next[4 + next_idx] = 0;
    }
  }
  else
  {
    strcat(str, "0000");
  }
  return atoi64(str);
}


----------------------------
***/


int64 mul_currency(int64 value1, int64 value2)
{
  return (value1 * value2) / 10000;
}


/*** DEPENDENCIES:
typedef long long int int64
----------------------------
***/


int64 div_currency(int64 value1, int64 value2)
{
  return (value1 * 10000) / value2;
}


/*** DEPENDENCIES:
typedef long long int int64
----------------------------
***/


unsigned short str_to_date(char *datestr)
{
  unsigned int datestr_idx = 0;
  unsigned short date;
  int day;
  int month;
  int year;
  char *next;
  unsigned int next_idx = 0;
  if ((&datestr[datestr_idx]) == 0)
  {
    return 0;
  }
  strcpy(tmp, datestr);
  datestr_idx = tmp;
  next_idx = stripchr(datestr, '-');
  year = atoi(datestr) - 1900;
  datestr_idx = &next[next_idx];
  next_idx = stripchr(datestr, '-');
  month = atoi(datestr);
  day = atoi(next);
  date = ((day << 11) | (month << 7)) | year;
  return date;
}


/*** DEPENDENCIES:
char tmp[128]
----------------------------
char *stripchr(char *mainstr, int separator)
{
  char *ptr;
  unsigned int ptr_idx = 0;
  if (mainstr == 0)
  {
    return 0;
  }
  ptr_idx = strchr(mainstr, separator);
  if ((&ptr[ptr_idx]) == 0)
  {
    return 0;
  }
  ptr[0 + ptr_idx] = '\0';
  ptr_idx += 1;
  return ptr;
}


----------------------------
***/


char *currency_to_str(int64 value)
{
  char *str;
  unsigned int str_idx = 0;
  char *ptr;
  unsigned int ptr_idx = 0;
  int size;
  int move;
  int i;
  i64toa(value, tmp, 10);
  str_idx = tmp;
  size = strlen(str);
  if (size > 4)
  {
    ptr_idx = ((&str[str_idx]) + size) - 4;
    memmove((&ptr[ptr_idx]) + 1, ptr, 4 + 1);
    ptr[0 + ptr_idx] = '.';
  }
  else
  {
    move = (2 + 4) - size;
    memmove((&str[str_idx]) + move, str, size + 1);
    str[0 + str_idx] = '0';
    str[1 + str_idx] = '.';
    for (i = 2; i < move; i += 1)
      str[i + str_idx] = '0';

  }
  return str;
}


/*** DEPENDENCIES:
char *i64toa(int64 value, char *buf, int radix)
{
  switch (radix)
  {
    case 10:
    {
      snprintf(buf, 64, "%lli", value);
      break;
    }

    case 16:
    {
      snprintf(buf, 64, "%llx", value);
      break;
    }

    default:
    {
      buf[0] = 0;
    }

  }

  return buf;
}


----------------------------
typedef long long int int64
----------------------------
char tmp[128]
----------------------------
***/


double currency_to_float(int64 value)
{
  currency_to_str(value);
  return atof(tmp);
}


/*** DEPENDENCIES:
typedef long long int int64
----------------------------
char tmp[128]
----------------------------
char *currency_to_str(int64 value)
{
  char *str;
  unsigned int str_idx = 0;
  char *ptr;
  unsigned int ptr_idx = 0;
  int size;
  int move;
  int i;
  i64toa(value, tmp, 10);
  str_idx = tmp;
  size = strlen(str);
  if (size > 4)
  {
    ptr_idx = ((&str[str_idx]) + size) - 4;
    memmove((&ptr[ptr_idx]) + 1, ptr, 4 + 1);
    ptr[0 + ptr_idx] = '.';
  }
  else
  {
    move = (2 + 4) - size;
    memmove((&str[str_idx]) + move, str, size + 1);
    str[0 + str_idx] = '0';
    str[1 + str_idx] = '.';
    for (i = 2; i < move; i += 1)
      str[i + str_idx] = '0';

  }
  return str;
}


----------------------------
***/


void test_int_conversion()
{
  printf("testing integer conversion...");
  vint8 = -110;
  vuint8 = 0;
  assert(copy_int_value(&vint8, &vuint8, 0x21, 0x20) == 0);
  assert(vint8 == (-110));
  assert(vuint8 == 0);
  vint8 = -110;
  vuint16 = 0;
  assert(copy_int_value(&vint8, &vuint16, 0x21, 0x40) == 0);
  assert(vint8 == (-110));
  assert(vuint16 == 0);
  vint8 = -110;
  vuint32 = 0;
  assert(copy_int_value(&vint8, &vuint32, 0x21, 0x60) == 0);
  assert(vint8 == (-110));
  assert(vuint32 == 0);
  vint8 = -110;
  vuint64 = 0;
  assert(copy_int_value(&vint8, &vuint64, 0x21, 0x80) == 0);
  assert(vint8 == (-110));
  assert(vuint64 == 0);
  vint16 = -123;
  vuint8 = 0;
  assert(copy_int_value(&vint16, &vuint8, 0x41, 0x20) == 0);
  assert(vint16 == (-123));
  assert(vuint8 == 0);
  vint16 = -123;
  vuint16 = 0;
  assert(copy_int_value(&vint16, &vuint16, 0x41, 0x40) == 0);
  assert(vint16 == (-123));
  assert(vuint16 == 0);
  vint16 = -32000;
  vuint32 = 0;
  assert(copy_int_value(&vint16, &vuint32, 0x41, 0x60) == 0);
  assert(vint16 == (-32000));
  assert(vuint32 == 0);
  vint16 = -32000;
  vuint64 = 0;
  assert(copy_int_value(&vint16, &vuint64, 0x41, 0x80) == 0);
  assert(vint16 == (-32000));
  assert(vuint64 == 0);
  vint32 = -123;
  vuint8 = 0;
  assert(copy_int_value(&vint32, &vuint8, 0x61, 0x20) == 0);
  assert(vint32 == (-123));
  assert(vuint8 == 0);
  vint32 = -123;
  vuint16 = 0;
  assert(copy_int_value(&vint32, &vuint16, 0x61, 0x40) == 0);
  assert(vint32 == (-123));
  assert(vuint16 == 0);
  vint32 = -123;
  vuint32 = 0;
  assert(copy_int_value(&vint32, &vuint32, 0x61, 0x60) == 0);
  assert(vint32 == (-123));
  assert(vuint32 == 0);
  vint32 = -123;
  vuint64 = 0;
  assert(copy_int_value(&vint32, &vuint64, 0x61, 0x80) == 0);
  assert(vint32 == (-123));
  assert(vuint64 == 0);
  vint64 = -123;
  vuint8 = 0;
  assert(copy_int_value(&vint64, &vuint8, 0x81, 0x20) == 0);
  assert(vint64 == (-123));
  assert(vuint8 == 0);
  vint64 = -123;
  vuint16 = 0;
  assert(copy_int_value(&vint64, &vuint16, 0x81, 0x40) == 0);
  assert(vint64 == (-123));
  assert(vuint16 == 0);
  vint64 = -123;
  vuint32 = 0;
  assert(copy_int_value(&vint64, &vuint32, 0x81, 0x60) == 0);
  assert(vint64 == (-123));
  assert(vuint32 == 0);
  vint64 = -123;
  vuint64 = 0;
  assert(copy_int_value(&vint64, &vuint64, 0x81, 0x80) == 0);
  assert(vint64 == (-123));
  assert(vuint64 == 0);
  vint16 = -32000;
  vint8 = 0;
  assert(copy_int_value(&vint16, &vint8, 0x41, 0x21) == 0);
  assert(vint16 == (-32000));
  assert(vint8 == 0);
  vint32 = -250;
  vint8 = 0;
  assert(copy_int_value(&vint32, &vint8, 0x61, 0x21) == 0);
  assert(vint32 == (-250));
  assert(vint8 == 0);
  vint32 = -35000;
  vint16 = 0;
  assert(copy_int_value(&vint32, &vint16, 0x61, 0x41) == 0);
  assert(vint32 == (-35000));
  assert(vint16 == 0);
  vint64 = -250;
  vint8 = 0;
  assert(copy_int_value(&vint64, &vint8, 0x81, 0x21) == 0);
  assert(vint64 == (-250));
  assert(vint8 == 0);
  vint64 = -35000;
  vint16 = 0;
  assert(copy_int_value(&vint64, &vint16, 0x81, 0x41) == 0);
  assert(vint64 == (-35000));
  assert(vint16 == 0);
  vint64 = -25470000000;
  vint32 = 0;
  assert(copy_int_value(&vint64, &vint32, 0x81, 0x61) == 0);
  assert(vint64 == (-25470000000));
  assert(vint32 == 0);
  vint16 = 250;
  vint8 = 0;
  assert(copy_int_value(&vint16, &vint8, 0x41, 0x21) == 0);
  assert(vint16 == 250);
  assert(vint8 == 0);
  vint32 = 250;
  vint8 = 0;
  assert(copy_int_value(&vint32, &vint8, 0x61, 0x21) == 0);
  assert(vint32 == 250);
  assert(vint8 == 0);
  vint32 = 35000;
  vint16 = 0;
  assert(copy_int_value(&vint32, &vint16, 0x61, 0x41) == 0);
  assert(vint32 == 35000);
  assert(vint16 == 0);
  vint64 = 250;
  vint8 = 0;
  assert(copy_int_value(&vint64, &vint8, 0x81, 0x21) == 0);
  assert(vint64 == 250);
  assert(vint8 == 0);
  vint64 = 35000;
  vint16 = 0;
  assert(copy_int_value(&vint64, &vint16, 0x81, 0x41) == 0);
  assert(vint64 == 35000);
  assert(vint16 == 0);
  vint64 = 25470000000;
  vint32 = 0;
  assert(copy_int_value(&vint64, &vint32, 0x81, 0x61) == 0);
  assert(vint64 == 25470000000);
  assert(vint32 == 0);
  vint16 = 300;
  vuint8 = 0;
  assert(copy_int_value(&vint16, &vuint8, 0x41, 0x20) == 0);
  assert(vint16 == 300);
  assert(vuint8 == 0);
  vint32 = 300;
  vuint8 = 0;
  assert(copy_int_value(&vint32, &vuint8, 0x61, 0x20) == 0);
  assert(vint32 == 300);
  assert(vuint8 == 0);
  vint32 = 70000;
  vuint16 = 0;
  assert(copy_int_value(&vint32, &vuint16, 0x61, 0x40) == 0);
  assert(vint32 == 70000);
  assert(vuint16 == 0);
  vint64 = 300;
  vuint8 = 0;
  assert(copy_int_value(&vint64, &vuint8, 0x81, 0x20) == 0);
  assert(vint64 == 300);
  assert(vuint8 == 0);
  vint64 = 70000;
  vuint16 = 0;
  assert(copy_int_value(&vint64, &vuint16, 0x81, 0x40) == 0);
  assert(vint64 == 70000);
  assert(vuint16 == 0);
  vint64 = 25470000000;
  vuint32 = 0;
  assert(copy_int_value(&vint64, &vuint32, 0x81, 0x60) == 0);
  assert(vint64 == 25470000000);
  assert(vuint32 == 0);
  vint8 = 123;
  vint16 = 0;
  assert(copy_int_value(&vint8, &vint16, 0x21, 0x41) == 1);
  assert(vint8 == 123);
  assert(vint16 == 123);
  vint8 = -110;
  vint16 = 0;
  assert(copy_int_value(&vint8, &vint16, 0x21, 0x41) == 1);
  assert(vint8 == (-110));
  assert(vint16 == (-110));
  vint8 = 123;
  vint32 = 0;
  assert(copy_int_value(&vint8, &vint32, 0x21, 0x61) == 1);
  assert(vint8 == 123);
  assert(vint32 == 123);
  vint8 = -110;
  vint32 = 0;
  assert(copy_int_value(&vint8, &vint32, 0x21, 0x61) == 1);
  assert(vint8 == (-110));
  assert(vint32 == (-110));
  vint8 = 123;
  vint64 = 0;
  assert(copy_int_value(&vint8, &vint64, 0x21, 0x81) == 1);
  assert(vint8 == 123);
  assert(vint64 == 123);
  vint8 = -120;
  vint64 = 0;
  assert(copy_int_value(&vint8, &vint64, 0x21, 0x81) == 1);
  assert(vint8 == (-120));
  assert(vint64 == (-120));
  vint8 = 123;
  vuint16 = 0;
  assert(copy_int_value(&vint8, &vuint16, 0x21, 0x40) == 1);
  assert(vint8 == 123);
  assert(vuint16 == 123);
  vint8 = 123;
  vuint32 = 0;
  assert(copy_int_value(&vint8, &vuint32, 0x21, 0x60) == 1);
  assert(vint8 == 123);
  assert(vuint32 == 123);
  vint8 = 123;
  vuint64 = 0;
  assert(copy_int_value(&vint8, &vuint64, 0x21, 0x80) == 1);
  assert(vint8 == 123);
  assert(vuint64 == 123);
  vuint8 = 123;
  vint16 = 0;
  assert(copy_int_value(&vuint8, &vint16, 0x20, 0x41) == 1);
  assert(vuint8 == 123);
  assert(vint16 == 123);
  vuint8 = 250;
  vint16 = 0;
  assert(copy_int_value(&vuint8, &vint16, 0x20, 0x41) == 1);
  assert(vuint8 == 250);
  assert(vint16 == 250);
  vuint8 = 123;
  vint32 = 0;
  assert(copy_int_value(&vuint8, &vint32, 0x20, 0x61) == 1);
  assert(vuint8 == 123);
  assert(vint32 == 123);
  vuint8 = 250;
  vint32 = 0;
  assert(copy_int_value(&vuint8, &vint32, 0x20, 0x61) == 1);
  assert(vuint8 == 250);
  assert(vint32 == 250);
  vuint8 = 123;
  vint64 = 0;
  assert(copy_int_value(&vuint8, &vint64, 0x20, 0x81) == 1);
  assert(vuint8 == 123);
  assert(vint64 == 123);
  vuint8 = 250;
  vint64 = 0;
  assert(copy_int_value(&vuint8, &vint64, 0x20, 0x81) == 1);
  assert(vuint8 == 250);
  assert(vint64 == 250);
  vuint8 = 123;
  vuint16 = 0;
  assert(copy_int_value(&vuint8, &vuint16, 0x20, 0x40) == 1);
  assert(vuint8 == 123);
  assert(vuint16 == 123);
  vuint8 = 250;
  vuint16 = 0;
  assert(copy_int_value(&vuint8, &vuint16, 0x20, 0x40) == 1);
  assert(vuint8 == 250);
  assert(vuint16 == 250);
  vuint8 = 123;
  vuint32 = 0;
  assert(copy_int_value(&vuint8, &vuint32, 0x20, 0x60) == 1);
  assert(vuint8 == 123);
  assert(vuint32 == 123);
  vuint8 = 250;
  vuint32 = 0;
  assert(copy_int_value(&vuint8, &vuint32, 0x20, 0x60) == 1);
  assert(vuint8 == 250);
  assert(vuint32 == 250);
  vuint8 = 123;
  vuint64 = 0;
  assert(copy_int_value(&vuint8, &vuint64, 0x20, 0x80) == 1);
  assert(vuint8 == 123);
  assert(vuint64 == 123);
  vuint8 = 250;
  vuint64 = 0;
  assert(copy_int_value(&vuint8, &vuint64, 0x20, 0x80) == 1);
  assert(vuint8 == 250);
  assert(vuint64 == 250);
  vint16 = 250;
  vuint8 = 0;
  assert(copy_int_value(&vint16, &vuint8, 0x41, 0x20) == 1);
  assert(vint16 == 250);
  assert(vuint8 == 250);
  vint32 = 250;
  vuint8 = 0;
  assert(copy_int_value(&vint32, &vuint8, 0x61, 0x20) == 1);
  assert(vint32 == 250);
  assert(vuint8 == 250);
  vint32 = 35000;
  vuint16 = 0;
  assert(copy_int_value(&vint32, &vuint16, 0x61, 0x40) == 1);
  assert(vint32 == 35000);
  assert(vuint16 == 35000);
  vint64 = 250;
  vuint8 = 0;
  assert(copy_int_value(&vint64, &vuint8, 0x81, 0x20) == 1);
  assert(vint64 == 250);
  assert(vuint8 == 250);
  vint64 = 35000;
  vuint16 = 0;
  assert(copy_int_value(&vint64, &vuint16, 0x81, 0x40) == 1);
  assert(vint64 == 35000);
  assert(vuint16 == 35000);
  vint64 = 2147000000;
  vuint32 = 0;
  assert(copy_int_value(&vint64, &vuint32, 0x81, 0x60) == 1);
  assert(vint64 == 2147000000);
  assert(vuint32 == 2147000000);
  vint8 = -110;
  vint16 = 0;
  assert(copy_int_value(&vint8, &vint16, 0x21, 0x41) == 1);
  assert(vint8 == (-110));
  assert(vint16 == (-110));
  vint8 = -110;
  vint32 = 0;
  assert(copy_int_value(&vint8, &vint32, 0x21, 0x61) == 1);
  assert(vint8 == (-110));
  assert(vint32 == (-110));
  vint8 = -110;
  vint64 = 0;
  assert(copy_int_value(&vint8, &vint64, 0x21, 0x81) == 1);
  assert(vint8 == (-110));
  assert(vint64 == (-110));
  vint16 = -123;
  vint8 = 0;
  assert(copy_int_value(&vint16, &vint8, 0x41, 0x21) == 1);
  assert(vint16 == (-123));
  assert(vint8 == (-123));
  vint16 = -32000;
  vint32 = 0;
  assert(copy_int_value(&vint16, &vint32, 0x41, 0x61) == 1);
  assert(vint16 == (-32000));
  assert(vint32 == (-32000));
  vint16 = -32000;
  vint64 = 0;
  assert(copy_int_value(&vint16, &vint64, 0x41, 0x81) == 1);
  assert(vint16 == (-32000));
  assert(vint64 == (-32000));
  vint32 = -123;
  vint8 = 0;
  assert(copy_int_value(&vint32, &vint8, 0x61, 0x21) == 1);
  assert(vint32 == (-123));
  assert(vint8 == (-123));
  vint32 = -123;
  vint16 = 0;
  assert(copy_int_value(&vint32, &vint16, 0x61, 0x41) == 1);
  assert(vint32 == (-123));
  assert(vint16 == (-123));
  vint32 = -32000;
  vint16 = 0;
  assert(copy_int_value(&vint32, &vint16, 0x61, 0x41) == 1);
  assert(vint32 == (-32000));
  assert(vint16 == (-32000));
  vint32 = -123;
  vint64 = 0;
  assert(copy_int_value(&vint32, &vint64, 0x61, 0x81) == 1);
  assert(vint32 == (-123));
  assert(vint64 == (-123));
  vint32 = -2147000000;
  vint64 = 0;
  assert(copy_int_value(&vint32, &vint64, 0x61, 0x81) == 1);
  assert(vint32 == (-2147000000));
  assert(vint64 == (-2147000000));
  vint64 = -123;
  vint8 = 0;
  assert(copy_int_value(&vint64, &vint8, 0x81, 0x21) == 1);
  assert(vint64 == (-123));
  assert(vint8 == (-123));
  vint64 = -250;
  vint16 = 0;
  assert(copy_int_value(&vint64, &vint16, 0x81, 0x41) == 1);
  assert(vint64 == (-250));
  assert(vint16 == (-250));
  vint64 = -35000;
  vint32 = 0;
  assert(copy_int_value(&vint64, &vint32, 0x81, 0x61) == 1);
  assert(vint64 == (-35000));
  assert(vint32 == (-35000));
  puts("OK");
}


/*** DEPENDENCIES:
signed char vint8
----------------------------
unsigned int vuint32
----------------------------
short vint16
----------------------------
int vint32
----------------------------
uint64 vuint64
----------------------------
unsigned short vuint16
----------------------------
static BOOL copy_int_value(void *psource, void *pdest, int source_type, int dest_type)
{
  uint64 vuint64 = 0;
  int64 vint64 = 0;
  switch (source_type)
  {
    case 0x21:
    {
      vint64 = *((signed char *) psource);
      break;
    }

    case 0x41:
    {
      vint64 = *((short *) psource);
      break;
    }

    case 0x61:
    {
      vint64 = *((int *) psource);
      break;
    }

    case 0x81:
    {
      vint64 = *((int64 *) psource);
      break;
    }

    case 0x20:
    {
      vuint64 = *((unsigned char *) psource);
      break;
    }

    case 0x40:
    {
      vuint64 = *((unsigned short *) psource);
      break;
    }

    case 0x60:
    {
      vuint64 = *((unsigned int *) psource);
      break;
    }

    case 0x80:
    {
      vuint64 = *((uint64 *) psource);
      break;
    }

    default:
    {
      return 0;
    }

  }

  if ((int_type(source_type) == 22) && (int_type(dest_type) == 11))
  {
    if (vuint64 > INT64_MAX)
    {
      return 0;
    }
    vint64 = vuint64;
  }
  else
    if ((int_type(source_type) == 11) && (int_type(dest_type) == 22))
  {
    if (vint64 < 0)
    {
      return 0;
    }
    vuint64 = vint64;
  }
  switch (dest_type)
  {
    case 0x21:
    {
      if ((vint64 < INT8_MIN) || (vint64 > INT8_MAX))
      {
        return 0;
      }
      *((signed char *) pdest) = (signed char) vint64;
      break;
    }

    case 0x41:
    {
      if ((vint64 < INT16_MIN) || (vint64 > INT16_MAX))
      {
        return 0;
      }
      *((short *) pdest) = (short) vint64;
      break;
    }

    case 0x61:
    {
      if ((vint64 < INT32_MIN) || (vint64 > INT32_MAX))
      {
        return 0;
      }
      *((int *) pdest) = (int) vint64;
      break;
    }

    case 0x81:
    {
      *((int64 *) pdest) = vint64;
      break;
    }

    case 0x20:
    {
      if (vuint64 > UINT8_MAX)
      {
        return 0;
      }
      *((unsigned char *) pdest) = (unsigned char) vuint64;
      break;
    }

    case 0x40:
    {
      if (vuint64 > UINT16_MAX)
      {
        return 0;
      }
      *((unsigned short *) pdest) = (unsigned short) vuint64;
      break;
    }

    case 0x60:
    {
      if (vuint64 > UINT32_MAX)
      {
        return 0;
      }
      *((unsigned int *) pdest) = (unsigned int) vuint64;
      break;
    }

    case 0x80:
    {
      *((uint64 *) pdest) = vuint64;
      break;
    }

    default:
    {
      return 0;
    }

  }

  return 1;
}


----------------------------
int64 vint64
----------------------------
unsigned char vuint8
----------------------------
***/


void test_binn_read(void *objptr)
{
  void *listptr;
  unsigned int listptr_idx = 0;
  char *ptr;
  unsigned int ptr_idx = 0;
  binn value = {0};
  printf("OK\nreading:\n");
  vint32 = 0;
  assert(binn_object_get(objptr, "int32", 0x61, &vint32, 0) == 1);
  printf("int32: %d\n", vint32);
  assert(vint32 == (-12345));
  vint16 = 0;
  assert(binn_object_get(objptr, "int16", 0x41, &vint16, 0) == 1);
  printf("int16: %d\n", vint16);
  assert(vint16 == (-258));
  vint8 = 0;
  assert(binn_object_get(objptr, "int8", 0x21, &vint8, 0) == 1);
  printf("int8: %d\n", vint8);
  assert(vint8 == (-120));
  vint64 = 0;
  assert(binn_object_get(objptr, "int64", 0x81, &vint64, 0) == 1);
  printf("int64: %lli\n", vint64);
  assert(vint64 == (-1234567890123));
  vuint32 = 0;
  assert(binn_object_get(objptr, "uint32", 0x60, &vuint32, 0) == 1);
  printf("uint32: %d\n", vuint32);
  assert(vuint32 == 123456);
  vuint16 = 0;
  assert(binn_object_get(objptr, "uint16", 0x40, &vuint16, 0) == 1);
  printf("uint16: %d\n", vuint16);
  assert(vuint16 == 60500);
  vuint8 = 0;
  assert(binn_object_get(objptr, "uint8", 0x20, &vuint8, 0) == 1);
  printf("uint8: %d\n", vuint8);
  assert(vuint8 == 250);
  vuint64 = 0;
  assert(binn_object_get(objptr, "uint64", 0x80, &vuint64, 0) == 1);
  printf("uint64: %llu\n", vuint64);
  assert(vuint64 == 1234567890123);
  vfloat32 = 0;
  assert(binn_object_get(objptr, "float32", 0x62, &vfloat32, 0) == 1);
  printf("float32: %f\n", vfloat32);
  assert(AlmostEqualFloats(vfloat32, -12.345, 2) == 1);
  vfloat64 = 0;
  assert(binn_object_get(objptr, "float64", 0x82, &vfloat64, 0) == 1);
  printf("float64: %f\n", vfloat64);
  assert((vfloat64 - (-123456.7895)) < 0.01);
  vfloat32 = 0;
  assert(binn_object_get(objptr, "single", 0x62, &vfloat32, 0) == 1);
  printf("single: %f\n", vfloat32);
  assert(AlmostEqualFloats(vfloat32, -12.345, 2) == 1);
  vfloat64 = 0;
  assert(binn_object_get(objptr, "double", 0x82, &vfloat64, 0) == 1);
  printf("double: %f\n", vfloat64);
  assert((vfloat64 - (-123456.7895)) < 0.01);
  ptr_idx = 0;
  assert(binn_object_get(objptr, "str", 0xA0, &(&ptr[ptr_idx]), 0) == 1);
  printf("ptr: (%p) '%s'\n", ptr, ptr);
  assert(strcmp(ptr, "the value") == 0);
  vint32 = 999;
  assert(binn_object_get(objptr, "bool_true", 0x80061, &vint32, 0) == 1);
  printf("bool true: %d\n", vint32);
  assert(vint32 == 1);
  vint32 = 999;
  assert(binn_object_get(objptr, "bool_false", 0x80061, &vint32, 0) == 1);
  printf("bool false: %d\n", vint32);
  assert(vint32 == 0);
  vint32 = 999;
  assert(binn_object_get(objptr, "null", 0x00, &vint32, 0) == 1);
  printf("null: %d\n", vint32);
  assert(binn_object_get(objptr, "null", 0x00, 0, 0) == 1);
  assert(binn_object_get(objptr, "list", 0xE0, &(&listptr[listptr_idx]), 0) == 1);
  printf("obj ptr: %p  list ptr: %p\n", objptr, listptr);
  assert((&listptr[listptr_idx]) != 0);
  assert((&listptr[listptr_idx]) > objptr);
  vint32 = 0;
  assert(binn_list_get(listptr, 2, 0x61, &vint32, 0) == 1);
  printf("int32: %d\n", vint32);
  assert(vint32 == 123);
  ptr_idx = 0;
  assert(binn_list_get(listptr, 3, 0xA0, &(&ptr[ptr_idx]), 0) == 1);
  printf("ptr: (%p) '%s'\n", ptr, ptr);
  assert(strcmp(ptr, "this is a string") == 0);
  vint32 = 0;
  assert(binn_object_get_int32(objptr, "int32", &vint32) == 1);
  printf("int32: %d\n", vint32);
  assert(vint32 == (-12345));
  vint16 = 0;
  assert(binn_object_get_int16(objptr, "int16", &vint16) == 1);
  printf("int16: %d\n", vint16);
  assert(vint16 == (-258));
  vint8 = 0;
  assert(binn_object_get_int8(objptr, "int8", &vint8) == 1);
  printf("int8: %d\n", vint8);
  assert(vint8 == (-120));
  vint64 = 0;
  assert(binn_object_get_int64(objptr, "int64", &vint64) == 1);
  printf("int64: %lli\n", vint64);
  assert(vint64 == (-1234567890123));
  vuint32 = 0;
  assert(binn_object_get_uint32(objptr, "uint32", &vuint32) == 1);
  printf("uint32: %d\n", vuint32);
  assert(vuint32 == 123456);
  vuint16 = 0;
  assert(binn_object_get_uint16(objptr, "uint16", &vuint16) == 1);
  printf("uint16: %d\n", vuint16);
  assert(vuint16 == 60500);
  vuint8 = 0;
  assert(binn_object_get_uint8(objptr, "uint8", &vuint8) == 1);
  printf("uint8: %d\n", vuint8);
  assert(vuint8 == 250);
  vuint64 = 0;
  assert(binn_object_get_uint64(objptr, "uint64", &vuint64) == 1);
  printf("uint64: %llu\n", vuint64);
  assert(vuint64 == 1234567890123);
  vfloat32 = 0;
  assert(binn_object_get_float(objptr, "float32", &vfloat32) == 1);
  printf("float32: %f\n", vfloat32);
  assert(AlmostEqualFloats(vfloat32, -12.345, 2) == 1);
  vfloat64 = 0;
  assert(binn_object_get_double(objptr, "float64", &vfloat64) == 1);
  printf("float64: %f\n", vfloat64);
  assert(AlmostEqualFloats(vfloat32, -12.345, 2) == 1);
  ptr_idx = 0;
  assert(binn_object_get_str(objptr, "str", &(&ptr[ptr_idx])) == 1);
  printf("ptr: (%p) '%s'\n", ptr, ptr);
  assert(strcmp(ptr, "the value") == 0);
  vint32 = 999;
  assert(binn_object_get_bool(objptr, "bool_true", &vint32) == 1);
  printf("bool true: %d\n", vint32);
  assert(vint32 == 1);
  vint32 = 999;
  assert(binn_object_get_bool(objptr, "bool_false", &vint32) == 1);
  printf("bool false: %d\n", vint32);
  assert(vint32 == 0);
  vbool = 0;
  assert(binn_object_null(objptr, "null") == 1);
  assert(binn_object_null(objptr, "bool_true") == 0);
  assert(binn_object_get_list(objptr, "list", &(&listptr[listptr_idx])) == 1);
  printf("obj ptr: %p  list ptr: %p\n", objptr, listptr);
  assert((&listptr[listptr_idx]) != 0);
  assert((&listptr[listptr_idx]) > objptr);
  vint32 = 0;
  assert(binn_list_get_int32(listptr, 2, &vint32) == 1);
  printf("int32: %d\n", vint32);
  assert(vint32 == 123);
  ptr_idx = 0;
  assert(binn_list_get_str(listptr, 3, &(&ptr[ptr_idx])) == 1);
  printf("ptr: (%p) '%s'\n", ptr, ptr);
  assert(strcmp(ptr, "this is a string") == 0);
  vint32 = binn_object_int32(objptr, "int32");
  printf("int32: %d\n", vint32);
  assert(vint32 == (-12345));
  vint16 = binn_object_int16(objptr, "int16");
  printf("int16: %d\n", vint16);
  assert(vint16 == (-258));
  vint8 = binn_object_int8(objptr, "int8");
  printf("int8: %d\n", vint8);
  assert(vint8 == (-120));
  vint64 = binn_object_int64(objptr, "int64");
  printf("int64: %lli\n", vint64);
  assert(vint64 == (-1234567890123));
  vuint32 = binn_object_uint32(objptr, "uint32");
  printf("uint32: %d\n", vuint32);
  assert(vuint32 == 123456);
  vuint16 = binn_object_uint16(objptr, "uint16");
  printf("uint16: %d\n", vuint16);
  assert(vuint16 == 60500);
  vuint8 = binn_object_uint8(objptr, "uint8");
  printf("uint8: %d\n", vuint8);
  assert(vuint8 == 250);
  vuint64 = binn_object_uint64(objptr, "uint64");
  printf("uint64: %llu\n", vuint64);
  assert(vuint64 == 1234567890123);
  vfloat32 = binn_object_float(objptr, "float32");
  printf("float32: %f\n", vfloat32);
  assert(AlmostEqualFloats(vfloat32, -12.345, 2) == 1);
  vfloat64 = binn_object_double(objptr, "float64");
  printf("float64: %f\n", vfloat64);
  assert(AlmostEqualFloats(vfloat32, -12.345, 2) == 1);
  ptr_idx = binn_object_str(objptr, "str");
  printf("ptr: (%p) '%s'\n", ptr, ptr);
  assert(strcmp(ptr, "the value") == 0);
  vint32 = binn_object_bool(objptr, "bool_true");
  printf("bool true: %d\n", vint32);
  assert(vint32 == 1);
  vint32 = binn_object_bool(objptr, "bool_false");
  printf("bool false: %d\n", vint32);
  assert(vint32 == 0);
  assert(binn_object_null(objptr, "null") == 1);
  assert(binn_object_null(objptr, "nonull") == 0);
  listptr_idx = binn_object_list(objptr, "list");
  printf("obj ptr: %p  list ptr: %p\n", objptr, listptr);
  assert((&listptr[listptr_idx]) != 0);
  assert((&listptr[listptr_idx]) > objptr);
  vint32 = binn_list_int32(listptr, 2);
  printf("int32: %d\n", vint32);
  assert(vint32 == 123);
  ptr_idx = binn_list_str(listptr, 3);
  printf("ptr: (%p) '%s'\n", ptr, ptr);
  assert(strcmp(ptr, "this is a string") == 0);
  assert(binn_object_get_value(objptr, "int32", &value) == 1);
  assert(value.type == 0x41);
  assert(value.vint16 == (-12345));
  assert(binn_object_get_value(objptr, "int16", &value) == 1);
  assert(value.type == 0x41);
  assert(value.vint16 == (-258));
  assert(binn_object_get_value(objptr, "int8", &value) == 1);
  assert(value.type == 0x21);
  assert(value.vint8 == (-120));
  assert(binn_object_get_value(objptr, "int64", &value) == 1);
  assert(value.type == 0x81);
  assert(value.vint64 == (-1234567890123));
  assert(binn_object_get_value(objptr, "uint32", &value) == 1);
  assert(value.type == 0x60);
  assert(value.vuint32 == 123456);
  assert(binn_object_get_value(objptr, "uint16", &value) == 1);
  assert(value.type == 0x40);
  assert(value.vuint16 == 60500);
  assert(binn_object_get_value(objptr, "uint8", &value) == 1);
  assert(value.type == 0x20);
  assert(value.vuint8 == 250);
  assert(binn_object_get_value(objptr, "uint64", &value) == 1);
  assert(value.type == 0x80);
  assert(value.vuint64 == 1234567890123);
  puts("reading... OK");
}


/*** DEPENDENCIES:
double vfloat64
----------------------------
BOOL vbool
----------------------------
inline static BOOL binn_object_get_int32(void *obj, const char *key, int *pvalue)
{
  return binn_object_get(obj, key, 0x61, pvalue, 0);
}


----------------------------
int64 binn_object_int64(void *obj, const char *key)
{
  int64 value;
  binn_object_get(obj, key, 0x81, &value, 0);
  return value;
}


----------------------------
inline static BOOL binn_object_get_double(void *obj, const char *key, double *pvalue)
{
  return binn_object_get(obj, key, 0x82, pvalue, 0);
}


----------------------------
int vint32
----------------------------
inline static BOOL binn_object_get_float(void *obj, const char *key, float *pvalue)
{
  return binn_object_get(obj, key, 0x62, pvalue, 0);
}


----------------------------
inline static BOOL binn_object_get_uint16(void *obj, const char *key, unsigned short *pvalue)
{
  return binn_object_get(obj, key, 0x40, pvalue, 0);
}


----------------------------
float vfloat32
----------------------------
inline static BOOL binn_object_get_int8(void *obj, const char *key, signed char *pvalue)
{
  return binn_object_get(obj, key, 0x21, pvalue, 0);
}


----------------------------
char *binn_object_str(void *obj, const char *key)
{
  char *value;
  binn_object_get(obj, key, 0xA0, &value, 0);
  return value;
}


----------------------------
inline static BOOL binn_list_get_int32(void *list, int pos, int *pvalue)
{
  return binn_list_get(list, pos, 0x61, pvalue, 0);
}


----------------------------
BOOL binn_object_null(void *obj, const char *key)
{
  return binn_object_get(obj, key, 0x00, 0, 0);
}


----------------------------
signed char vint8
----------------------------
inline static BOOL binn_object_get_list(void *obj, const char *key, void **pvalue)
{
  return binn_object_get(obj, key, 0xE0, pvalue, 0);
}


----------------------------
short vint16
----------------------------
uint64 vuint64
----------------------------
unsigned short vuint16
----------------------------
inline static BOOL binn_object_get_uint32(void *obj, const char *key, unsigned int *pvalue)
{
  return binn_object_get(obj, key, 0x60, pvalue, 0);
}


----------------------------
unsigned int binn_object_uint32(void *obj, const char *key)
{
  unsigned int value;
  binn_object_get(obj, key, 0x60, &value, 0);
  return value;
}


----------------------------
char *binn_list_str(void *list, int pos)
{
  char *value;
  binn_list_get(list, pos, 0xA0, &value, 0);
  return value;
}


----------------------------
BOOL binn_object_get_value(void *ptr, const char *key, binn *value)
{
  unsigned int ptr_idx = 0;
  int type;
  int count;
  int size = 0;
  int header_size;
  unsigned char *p;
  unsigned int p_idx = 0;
  ptr_idx = binn_ptr(ptr_idx);
  if ((((&ptr[ptr_idx]) == 0) || (key == 0)) || (value == 0))
  {
    return 0;
  }
  if (IsValidBinnHeader(ptr, &type, &count, &size, &header_size) == 0)
  {
    return 0;
  }
  if (type != 0xE2)
  {
    return 0;
  }
  if (count == 0)
  {
    return 0;
  }
  p_idx = (unsigned char *) ptr;
  p_idx = SearchForKey(p_idx, header_size, size, count, key);
  if ((&p[p_idx]) == 0)
  {
    return 0;
  }
  return GetValue(p, value);
}


----------------------------
double binn_object_double(void *obj, const char *key)
{
  double value;
  binn_object_get(obj, key, 0x82, &value, 0);
  return value;
}


----------------------------
uint64 binn_object_uint64(void *obj, const char *key)
{
  uint64 value;
  binn_object_get(obj, key, 0x80, &value, 0);
  return value;
}


----------------------------
BOOL binn_object_bool(void *obj, const char *key)
{
  BOOL value;
  binn_object_get(obj, key, 0x80061, &value, 0);
  return value;
}


----------------------------
int binn_object_int32(void *obj, const char *key)
{
  int value;
  binn_object_get(obj, key, 0x61, &value, 0);
  return value;
}


----------------------------
unsigned int vuint32
----------------------------
signed char binn_object_int8(void *obj, const char *key)
{
  signed char value;
  binn_object_get(obj, key, 0x21, &value, 0);
  return value;
}


----------------------------
void *binn_object_list(void *obj, const char *key)
{
  void *value;
  binn_object_get(obj, key, 0xE0, &value, 0);
  return value;
}


----------------------------
inline static BOOL binn_object_get_int64(void *obj, const char *key, int64 *pvalue)
{
  return binn_object_get(obj, key, 0x81, pvalue, 0);
}


----------------------------
unsigned short binn_object_uint16(void *obj, const char *key)
{
  unsigned short value;
  binn_object_get(obj, key, 0x40, &value, 0);
  return value;
}


----------------------------
typedef struct binn_struct binn
----------------------------
short binn_object_int16(void *obj, const char *key)
{
  short value;
  binn_object_get(obj, key, 0x41, &value, 0);
  return value;
}


----------------------------
int64 vint64
----------------------------
inline static BOOL binn_object_get_int16(void *obj, const char *key, short *pvalue)
{
  return binn_object_get(obj, key, 0x41, pvalue, 0);
}


----------------------------
unsigned char vuint8
----------------------------
inline static BOOL binn_object_get_uint64(void *obj, const char *key, uint64 *pvalue)
{
  return binn_object_get(obj, key, 0x80, pvalue, 0);
}


----------------------------
BOOL AlmostEqualFloats(float A, float B, int maxUlps)
{
  int aInt;
  int bInt;
  int intDiff;
  assert((maxUlps > 0) && (maxUlps < ((4 * 1024) * 1024)));
  aInt = *((int *) (&A));
  bInt = *((int *) (&B));
  if (aInt < 0)
  {
    aInt = 0x80000000 - aInt;
  }
  if (bInt < 0)
  {
    bInt = 0x80000000 - bInt;
  }
  intDiff = abs(aInt - bInt);
  if (intDiff <= maxUlps)
  {
    return 1;
  }
  return 0;
}


----------------------------
inline static BOOL binn_list_get_str(void *list, int pos, char **pvalue)
{
  return binn_list_get(list, pos, 0xA0, pvalue, 0);
}


----------------------------
BOOL binn_object_get(void *ptr, const char *key, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_object_get_value(ptr, key, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
unsigned char binn_object_uint8(void *obj, const char *key)
{
  unsigned char value;
  binn_object_get(obj, key, 0x20, &value, 0);
  return value;
}


----------------------------
BOOL binn_list_get(void *ptr, int pos, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_list_get_value(ptr, pos, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
inline static BOOL binn_object_get_str(void *obj, const char *key, char **pvalue)
{
  return binn_object_get(obj, key, 0xA0, pvalue, 0);
}


----------------------------
int binn_list_int32(void *list, int pos)
{
  int value;
  binn_list_get(list, pos, 0x61, &value, 0);
  return value;
}


----------------------------
float binn_object_float(void *obj, const char *key)
{
  float value;
  binn_object_get(obj, key, 0x62, &value, 0);
  return value;
}


----------------------------
inline static BOOL binn_object_get_bool(void *obj, const char *key, BOOL *pvalue)
{
  return binn_object_get(obj, key, 0x80061, pvalue, 0);
}


----------------------------
inline static BOOL binn_object_get_uint8(void *obj, const char *key, unsigned char *pvalue)
{
  return binn_object_get(obj, key, 0x20, pvalue, 0);
}


----------------------------
***/


void test_virtual_types()
{
  binn *list = 0;
  unsigned int list_idx = 0;
  void *ptr;
  unsigned int ptr_idx = 0;
  int storage_type;
  int extra_type;
  BOOL value;
  printf("testing binn virtual types... ");
  assert(binn_get_type_info(0x80061, &storage_type, &extra_type) == 1);
  assert(storage_type == 0x60);
  assert(extra_type == 1);
  list_idx = binn_list();
  assert((&list[list_idx]) != 0);
  assert(binn_list_add_bool(list, 1) == 1);
  assert(binn_list_add_bool(list, 0) == 1);
  assert(binn_list_add_null(list) == 1);
  ptr_idx = binn_ptr(list);
  assert((&ptr[ptr_idx]) != 0);
  assert(binn_list_get_bool(ptr, 1, &value) == 1);
  assert(value == 1);
  assert(binn_list_get_bool(ptr, 2, &value) == 1);
  assert(value == 0);
  assert(binn_list_null(ptr, 3) == 1);
  assert(binn_list_null(ptr, 1) == 0);
  assert(binn_list_null(ptr, 2) == 0);
  assert(binn_list_get_bool(ptr, 3, &value) == 0);
  binn_free(list);
  puts("OK");
}


/*** DEPENDENCIES:
inline static BOOL binn_list_get_bool(void *list, int pos, BOOL *pvalue)
{
  return binn_list_get(list, pos, 0x80061, pvalue, 0);
}


----------------------------
BOOL binn_list_null(void *list, int pos)
{
  return binn_list_get(list, pos, 0x00, 0, 0);
}


----------------------------
void *binn_ptr(void *ptr)
{
  binn *item;
  unsigned int item_idx = 0;
  switch (binn_get_ptr_type(ptr))
  {
    case 1:
    {
      item_idx = (binn *) ptr;
      if (item->writable && item->dirty)
      {
        binn_save_header(item);
      }
      return item->ptr;
    }

    case 2:
    {
      return ptr;
    }

    default:
    {
      return 0;
    }

  }

}


----------------------------
binn *binn_list()
{
  return binn_new(0xE0, 0, 0);
}


----------------------------
BOOL binn_get_type_info(int long_type, int *pstorage_type, int *pextra_type)
{
  int storage_type;
  int extra_type;
  BOOL retval = 1;
  again:
  if (long_type < 0)
  {
    goto loc_invalid;
  }
  else
    if (long_type <= 0xff)
  {
    storage_type = long_type & 0xE0;
    extra_type = long_type & 0x0F;
  }
  else
    if (long_type <= 0xffff)
  {
    storage_type = long_type & 0xE000;
    storage_type >>= 8;
    extra_type = long_type & 0x0FFF;
    extra_type >>= 4;
  }
  else
    if (long_type & 0x80000)
  {
    long_type &= 0xffff;
    goto again;
  }
  else
  {
    loc_invalid:
    storage_type = -1;

    extra_type = -1;
    retval = 0;
  }

  if (pstorage_type)
  {
    *pstorage_type = storage_type;
  }
  if (pextra_type)
  {
    *pextra_type = extra_type;
  }
  return retval;
}


----------------------------
inline static BOOL binn_list_add_null(binn *list)
{
  return binn_list_add(list, 0x00, 0, 0);
}


----------------------------
typedef struct binn_struct binn
----------------------------
void binn_free(binn *item)
{
  if (item == 0)
  {
    return;
  }
  if (item->writable && (item->pre_allocated == 0))
  {
    free_fn(item->pbuf);
  }
  if (item->freefn)
  {
    item->freefn(item->ptr);
  }
  if (item->allocated)
  {
    free_fn(item);
  }
  else
  {
    memset(item, 0, sizeof(binn));
    item->header = 0x1F22B11F;
  }
}


----------------------------
inline static BOOL binn_list_add_bool(binn *list, BOOL value)
{
  return binn_list_add(list, 0x80061, &value, 0);
}


----------------------------
typedef int BOOL
----------------------------
***/


char *test_create_object_2(int *psize)
{
  binn *obj = 0;
  unsigned int obj_idx = 0;
  binn *list = 0;
  unsigned int list_idx = 0;
  printf("creating object 2...\n");
  obj_idx = binn_object();
  assert((&obj[obj_idx]) != 0);
  assert(binn_object_set_int32(obj, "int32", -12345) == 1);
  assert(binn_object_set_int16(obj, "int16", -258) == 1);
  assert(binn_object_set_int8(obj, "int8", -120) == 1);
  assert(binn_object_set_int64(obj, "int64", -1234567890123) == 1);
  assert(binn_object_set_uint32(obj, "uint32", 123456) == 1);
  assert(binn_object_set_int16(obj, "uint16", 60500) == 1);
  assert(binn_object_set_int8(obj, "uint8", 250) == 1);
  assert(binn_object_set_uint64(obj, "uint64", 1234567890123) == 1);
  assert(binn_object_set_float(obj, "float32", -12.345) == 1);
  vfloat32 = -12.345;
  assert(binn_object_set(obj, "single", 0x62, &vfloat32, 0) == 1);
  assert(binn_object_set_double(obj, "float64", -123456.7895) == 1);
  vfloat64 = -123456.7895;
  assert(binn_object_set(obj, "double", 0x82, &vfloat64, 0) == 1);
  assert(binn_object_set_str(obj, "str", "the value") == 1);
  assert(binn_object_set_bool(obj, "bool_true", 1) == 1);
  assert(binn_object_set_bool(obj, "bool_false", 0) == 1);
  assert(binn_object_set_null(obj, "null") == 1);
  list_idx = binn_list();
  assert((&list[list_idx]) != 0);
  assert(binn_list_add_null(list) == 1);
  assert(binn_list_add_int32(list, 123) == 1);
  assert(binn_list_add_str(list, "this is a string") == 1);
  assert(binn_object_set_list(obj, "list", list) == 1);
  binn_free(list);
  list_idx = 0;
  *psize = binn_size(obj);
  return (char *) binn_ptr(obj);
}


/*** DEPENDENCIES:
double vfloat64
----------------------------
void *binn_ptr(void *ptr)
{
  binn *item;
  unsigned int item_idx = 0;
  switch (binn_get_ptr_type(ptr))
  {
    case 1:
    {
      item_idx = (binn *) ptr;
      if (item->writable && item->dirty)
      {
        binn_save_header(item);
      }
      return item->ptr;
    }

    case 2:
    {
      return ptr;
    }

    default:
    {
      return 0;
    }

  }

}


----------------------------
inline static BOOL binn_object_set_int8(binn *obj, const char *key, signed char value)
{
  return binn_object_set(obj, key, 0x21, &value, 0);
}


----------------------------
binn *binn_list()
{
  return binn_new(0xE0, 0, 0);
}


----------------------------
inline static BOOL binn_object_set_bool(binn *obj, const char *key, BOOL value)
{
  return binn_object_set(obj, key, 0x80061, &value, 0);
}


----------------------------
int binn_size(void *ptr)
{
  binn *item;
  unsigned int item_idx = 0;
  switch (binn_get_ptr_type(ptr))
  {
    case 1:
    {
      item_idx = (binn *) ptr;
      if (item->writable && item->dirty)
      {
        binn_save_header(item);
      }
      return item->size;
    }

    case 2:
    {
      return binn_buf_size(ptr);
    }

    default:
    {
      return 0;
    }

  }

}


----------------------------
float vfloat32
----------------------------
inline static BOOL binn_object_set_double(binn *obj, const char *key, double value)
{
  return binn_object_set(obj, key, 0x82, &value, 0);
}


----------------------------
inline static BOOL binn_object_set_int32(binn *obj, const char *key, int value)
{
  return binn_object_set(obj, key, 0x61, &value, 0);
}


----------------------------
inline static BOOL binn_object_set_list(binn *obj, const char *key, void *list)
{
  return binn_object_set(obj, key, 0xE0, binn_ptr(list), binn_size(list));
}


----------------------------
inline static BOOL binn_list_add_int32(binn *list, int value)
{
  return binn_list_add(list, 0x61, &value, 0);
}


----------------------------
binn *binn_object()
{
  return binn_new(0xE2, 0, 0);
}


----------------------------
inline static BOOL binn_list_add_null(binn *list)
{
  return binn_list_add(list, 0x00, 0, 0);
}


----------------------------
inline static BOOL binn_list_add_str(binn *list, char *str)
{
  return binn_list_add(list, 0xA0, str, 0);
}


----------------------------
inline static BOOL binn_object_set_int64(binn *obj, const char *key, int64 value)
{
  return binn_object_set(obj, key, 0x81, &value, 0);
}


----------------------------
inline static BOOL binn_object_set_str(binn *obj, const char *key, char *str)
{
  return binn_object_set(obj, key, 0xA0, str, 0);
}


----------------------------
inline static BOOL binn_object_set_null(binn *obj, const char *key)
{
  return binn_object_set(obj, key, 0x00, 0, 0);
}


----------------------------
typedef struct binn_struct binn
----------------------------
inline static BOOL binn_object_set_float(binn *obj, const char *key, float value)
{
  return binn_object_set(obj, key, 0x62, &value, 0);
}


----------------------------
inline static BOOL binn_object_set_int16(binn *obj, const char *key, short value)
{
  return binn_object_set(obj, key, 0x41, &value, 0);
}


----------------------------
BOOL binn_object_set(binn *obj, const char *key, int type, void *pvalue, int size)
{
  if (GetWriteConvertedData(&type, &pvalue, &size) == 0)
  {
    return 0;
  }
  return binn_object_set_raw(obj, key, type, pvalue, size);
}


----------------------------
void binn_free(binn *item)
{
  if (item == 0)
  {
    return;
  }
  if (item->writable && (item->pre_allocated == 0))
  {
    free_fn(item->pbuf);
  }
  if (item->freefn)
  {
    item->freefn(item->ptr);
  }
  if (item->allocated)
  {
    free_fn(item);
  }
  else
  {
    memset(item, 0, sizeof(binn));
    item->header = 0x1F22B11F;
  }
}


----------------------------
inline static BOOL binn_object_set_uint32(binn *obj, const char *key, unsigned int value)
{
  return binn_object_set(obj, key, 0x60, &value, 0);
}


----------------------------
inline static BOOL binn_object_set_uint64(binn *obj, const char *key, uint64 value)
{
  return binn_object_set(obj, key, 0x80, &value, 0);
}


----------------------------
***/


void init_udts()
{
  binn *obj = 0;
  unsigned int obj_idx = 0;
  unsigned short date;
  uint64 value;
  void *ptr;
  unsigned int ptr_idx = 0;
  puts("testing UDTs...");
  assert(strcmp(date_to_str(str_to_date("1950-08-15")), "1950-08-15") == 0);
  assert(strcmp(date_to_str(str_to_date("1900-12-01")), "1900-12-01") == 0);
  assert(strcmp(date_to_str(str_to_date("2000-10-31")), "2000-10-31") == 0);
  assert(strcmp(date_to_str(str_to_date("2014-03-19")), "2014-03-19") == 0);
  printf("curr=%s\n", currency_to_str(str_to_currency("123.456")));
  printf("curr=%s\n", currency_to_str(str_to_currency("123.45")));
  printf("curr=%s\n", currency_to_str(str_to_currency("123.4")));
  printf("curr=%s\n", currency_to_str(str_to_currency("123.")));
  printf("curr=%s\n", currency_to_str(str_to_currency("123")));
  printf("curr=%s\n", currency_to_str(str_to_currency("1.2")));
  printf("curr=%s\n", currency_to_str(str_to_currency("0.987")));
  printf("curr=%s\n", currency_to_str(str_to_currency("0.98")));
  printf("curr=%s\n", currency_to_str(str_to_currency("0.9")));
  printf("curr=%s\n", currency_to_str(str_to_currency("0.0")));
  printf("curr=%s\n", currency_to_str(str_to_currency("0")));
  printf("curr=%s\n", currency_to_str(str_to_currency("123.4567")));
  printf("curr=%s\n", currency_to_str(str_to_currency("123.45678")));
  printf("curr=%s\n", currency_to_str(str_to_currency("123.456789")));
  printf("curr=%s\n", currency_to_str(str_to_currency("0.1234")));
  printf("curr=%s\n", currency_to_str(str_to_currency(".1234")));
  assert(float_to_currency(2.5) == 25000);
  assert(float_to_currency(5) == 50000);
  assert(str_to_currency("1.1") == 11000);
  assert(str_to_currency("12") == 120000);
  assert(mul_currency(20000, 20000) == 40000);
  assert(mul_currency(20000, 25000) == 50000);
  assert(mul_currency(30000, 40000) == 120000);
  assert(div_currency(80000, 20000) == 40000);
  assert(div_currency(120000, 40000) == 30000);
  assert(div_currency(100000, 40000) == 25000);
  printf("1.1 * 2.5 = %s\n", currency_to_str(mul_currency(str_to_currency("1.1"), float_to_currency(2.5))));
  printf("12 / 5 = %s\n", currency_to_str(div_currency(str_to_currency("12"), float_to_currency(5))));
  MY_DATE = binn_create_type(0x40, 0x0a);
  MY_CURRENCY = binn_create_type(0x80, 0x0a);
  obj_idx = binn_object();
  assert((&obj[obj_idx]) != 0);
  date = str_to_date("1950-08-15");
  printf(" date 1: %d %s\n", date, date_to_str(date));
  assert(binn_object_set(obj, "date1", MY_DATE, &date, 0) == 1);
  assert(binn_object_set(obj, "date1", MY_DATE, &date, 0) == 0);
  date = str_to_date("1999-12-31");
  printf(" date 2: %d %s\n", date, date_to_str(date));
  binn_object_set(obj, "date2", MY_DATE, &date, 0);
  value = str_to_currency("123.456");
  printf(" curr 1: %llu %s\n", value, currency_to_str(value));
  binn_object_set(obj, "curr1", MY_CURRENCY, &value, 0);
  value = str_to_currency("123.45");
  printf(" curr 2: %llu %s\n", value, currency_to_str(value));
  binn_object_set(obj, "curr2", MY_CURRENCY, &value, 0);
  value = str_to_currency("12.5");
  printf(" curr 3: %llu %s\n", value, currency_to_str(value));
  binn_object_set(obj, "curr3", MY_CURRENCY, &value, 0);
  value = str_to_currency("5");
  printf(" curr 4: %llu %s\n", value, currency_to_str(value));
  binn_object_set(obj, "curr4", MY_CURRENCY, &value, 0);
  value = str_to_currency("0.75");
  printf(" curr 5: %llu %s\n", value, currency_to_str(value));
  binn_object_set(obj, "curr5", MY_CURRENCY, &value, 0);
  ptr_idx = binn_ptr(obj);
  assert(binn_object_get(ptr, "date1", MY_DATE, &date, 0) == 1);
  printf(" date 1: %d %s\n", date, date_to_str(date));
  assert(binn_object_get(ptr, "date2", MY_DATE, &date, 0) == 1);
  printf(" date 2: %d %s\n", date, date_to_str(date));
  assert(binn_object_get(ptr, "curr1", MY_CURRENCY, &value, 0) == 1);
  printf(" curr 1: %llu %s\n", value, currency_to_str(value));
  assert(binn_object_get(ptr, "curr2", MY_CURRENCY, &value, 0) == 1);
  printf(" curr 2: %llu %s\n", value, currency_to_str(value));
  assert(binn_object_get(ptr, "curr3", MY_CURRENCY, &value, 0) == 1);
  printf(" curr 3: %llu %s\n", value, currency_to_str(value));
  assert(binn_object_get(ptr, "curr4", MY_CURRENCY, &value, 0) == 1);
  printf(" curr 4: %llu %s\n", value, currency_to_str(value));
  assert(binn_object_get(ptr, "curr5", MY_CURRENCY, &value, 0) == 1);
  printf(" curr 5: %llu %s\n", value, currency_to_str(value));
  binn_free(obj);
  puts("testing UDTs... OK");
}


/*** DEPENDENCIES:
int binn_create_type(int storage_type, int data_type_index)
{
  if (data_type_index < 0)
  {
    return -1;
  }
  if ((storage_type < 0x00) || (storage_type > 0xE0))
  {
    return -1;
  }
  if (data_type_index < 16)
  {
    return storage_type | data_type_index;
  }
  else
    if (data_type_index < 4096)
  {
    storage_type |= 0x10;
    storage_type <<= 8;
    data_type_index >>= 4;
    return storage_type | data_type_index;
  }
  else
    return -1;
}


----------------------------
unsigned short str_to_date(char *datestr)
{
  unsigned int datestr_idx = 0;
  unsigned short date;
  int day;
  int month;
  int year;
  char *next;
  unsigned int next_idx = 0;
  if ((&datestr[datestr_idx]) == 0)
  {
    return 0;
  }
  strcpy(tmp, datestr);
  datestr_idx = tmp;
  next_idx = stripchr(datestr, '-');
  year = atoi(datestr) - 1900;
  datestr_idx = &next[next_idx];
  next_idx = stripchr(datestr, '-');
  month = atoi(datestr);
  day = atoi(next);
  date = ((day << 11) | (month << 7)) | year;
  return date;
}


----------------------------
int64 div_currency(int64 value1, int64 value2)
{
  return (value1 * 10000) / value2;
}


----------------------------
int MY_CURRENCY
----------------------------
typedef unsigned long long int uint64
----------------------------
void *binn_ptr(void *ptr)
{
  binn *item;
  unsigned int item_idx = 0;
  switch (binn_get_ptr_type(ptr))
  {
    case 1:
    {
      item_idx = (binn *) ptr;
      if (item->writable && item->dirty)
      {
        binn_save_header(item);
      }
      return item->ptr;
    }

    case 2:
    {
      return ptr;
    }

    default:
    {
      return 0;
    }

  }

}


----------------------------
BOOL binn_object_get(void *ptr, const char *key, int type, void *pvalue, int *psize)
{
  binn value;
  int storage_type;
  storage_type = binn_get_read_storage(type);
  if ((storage_type != 0x00) && (pvalue == 0))
  {
    return 0;
  }
  zero_value(pvalue, type);
  if (binn_object_get_value(ptr, key, &value) == 0)
  {
    return 0;
  }
  if (copy_value(value.ptr, pvalue, value.type, type, storage_type) == 0)
  {
    return 0;
  }
  if (psize)
  {
    *psize = value.size;
  }
  return 1;
}


----------------------------
typedef long long int int64
----------------------------
int MY_DATE
----------------------------
binn *binn_object()
{
  return binn_new(0xE2, 0, 0);
}


----------------------------
int64 float_to_currency(double value)
{
  char buf[128];
  snprintf(buf, 127, "%.4f", value);
  return str_to_currency(buf);
}


----------------------------
BOOL binn_object_set(binn *obj, const char *key, int type, void *pvalue, int size)
{
  if (GetWriteConvertedData(&type, &pvalue, &size) == 0)
  {
    return 0;
  }
  return binn_object_set_raw(obj, key, type, pvalue, size);
}


----------------------------
typedef struct binn_struct binn
----------------------------
void binn_free(binn *item)
{
  if (item == 0)
  {
    return;
  }
  if (item->writable && (item->pre_allocated == 0))
  {
    free_fn(item->pbuf);
  }
  if (item->freefn)
  {
    item->freefn(item->ptr);
  }
  if (item->allocated)
  {
    free_fn(item);
  }
  else
  {
    memset(item, 0, sizeof(binn));
    item->header = 0x1F22B11F;
  }
}


----------------------------
int64 str_to_currency(char *str)
{
  unsigned int str_idx = 0;
  char *next;
  unsigned int next_idx = 0;
  int size;
  int i;
  if ((&str[str_idx]) == 0)
  {
    return 0;
  }
  strcpy(tmp, str);
  str_idx = tmp;
  next_idx = strchr(str, '.');
  if (next)
  {
    size = strlen((&next[next_idx]) + 1);
    memmove(next, (&next[next_idx]) + 1, size + 1);
    if (size <= 4)
    {
      size = 4 - size;
      for (i = 0; i < size; i += 1)
        strcat(str, "0");

    }
    else
    {
      next[4 + next_idx] = 0;
    }
  }
  else
  {
    strcat(str, "0000");
  }
  return atoi64(str);
}


----------------------------
int64 mul_currency(int64 value1, int64 value2)
{
  return (value1 * value2) / 10000;
}


----------------------------
char *date_to_str(unsigned short date)
{
  int day;
  int month;
  int year;
  day = (date & 0xf800) >> 11;
  month = (date & 0x0780) >> 7;
  year = date & 0x007f;
  sprintf(tmp, "%.4d-%.2d-%.2d", year + 1900, month, day);
  return tmp;
}


----------------------------
char *currency_to_str(int64 value)
{
  char *str;
  unsigned int str_idx = 0;
  char *ptr;
  unsigned int ptr_idx = 0;
  int size;
  int move;
  int i;
  i64toa(value, tmp, 10);
  str_idx = tmp;
  size = strlen(str);
  if (size > 4)
  {
    ptr_idx = ((&str[str_idx]) + size) - 4;
    memmove((&ptr[ptr_idx]) + 1, ptr, 4 + 1);
    ptr[0 + ptr_idx] = '.';
  }
  else
  {
    move = (2 + 4) - size;
    memmove((&str[str_idx]) + move, str, size + 1);
    str[0 + str_idx] = '0';
    str[1 + str_idx] = '.';
    for (i = 2; i < move; i += 1)
      str[i + str_idx] = '0';

  }
  return str;
}


----------------------------
***/


void test_value_conversion()
{
  binn *value;
  unsigned int value_idx = 0;
  char *ptr;
  unsigned int ptr_idx = 0;
  char blob[64] = "test blob";
  void *pblob;
  unsigned int pblob_idx = 0;
  int size;
  int vint32;
  int64 vint64;
  double vdouble;
  BOOL vbool;
  printf("testing binn value conversion... ");
  ptr_idx = "static string";
  value_idx = binn_string(ptr, (binn_mem_free) 0);
  assert((&value[value_idx]) != 0);
  assert(value->type == 0xA0);
  assert(value->ptr != 0);
  assert(value->ptr == (&ptr[ptr_idx]));
  assert(value->freefn == 0);
  binn_free(value);
  ptr_idx = "transient string";
  value_idx = binn_string(ptr, (binn_mem_free) (-1));
  assert((&value[value_idx]) != 0);
  assert(value->type == 0xA0);
  assert(value->ptr != 0);
  assert(value->ptr != (&ptr[ptr_idx]));
  assert(strcmp((char *) value->ptr, ptr) == 0);
  assert(value->freefn != 0);
  binn_free(value);
  ptr_idx = strdup("dynamic allocated string");
  value_idx = binn_string(ptr, free);
  assert((&value[value_idx]) != 0);
  assert(value->type == 0xA0);
  assert(value->ptr != 0);
  assert(value->ptr == (&ptr[ptr_idx]));
  assert(value->freefn != 0);
  assert(value->freefn == (&free));
  binn_free(value);
  size = 64;
  pblob_idx = blob;
  value_idx = binn_blob(pblob, size, (binn_mem_free) 0);
  assert((&value[value_idx]) != 0);
  assert(value->type == 0xC0);
  assert(value->ptr != 0);
  assert(value->ptr == (&pblob[pblob_idx]));
  assert(value->freefn == 0);
  binn_free(value);
  size = 64;
  pblob_idx = blob;
  value_idx = binn_blob(pblob, size, (binn_mem_free) (-1));
  assert((&value[value_idx]) != 0);
  assert(value->type == 0xC0);
  assert(value->ptr != 0);
  assert(value->ptr != (&pblob[pblob_idx]));
  assert(memcmp(value->ptr, pblob, size) == 0);
  assert(value->freefn != 0);
  binn_free(value);
  size = 64;
  pblob_idx = memdup(blob, size);
  value_idx = binn_blob(pblob, size, free);
  assert((&value[value_idx]) != 0);
  assert(value->type == 0xC0);
  assert(value->ptr != 0);
  assert(value->ptr == (&pblob[pblob_idx]));
  assert(value->freefn == (&free));
  binn_free(value);
  ptr_idx = "123";
  value_idx = binn_string(ptr, (binn_mem_free) 0);
  assert((&value[value_idx]) != 0);
  assert(value->type == 0xA0);
  assert(value->ptr != 0);
  assert(value->ptr == (&ptr[ptr_idx]));
  assert(value->freefn == 0);
  assert(binn_get_str(value) == (&ptr[ptr_idx]));
  assert(binn_get_int32(value, &vint32) == 1);
  assert(vint32 == 123);
  assert(binn_get_int64(value, &vint64) == 1);
  assert(vint64 == 123);
  assert(binn_get_double(value, &vdouble) == 1);
  assert(AlmostEqualFloats(vdouble, 123, 4) == 1);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 1);
  assert(value->type == 0xA0);
  assert(value->ptr != 0);
  assert(value->ptr == (&ptr[ptr_idx]));
  assert(value->freefn == 0);
  binn_free(value);
  ptr_idx = "-456";
  value_idx = binn_string(ptr, (binn_mem_free) 0);
  assert((&value[value_idx]) != 0);
  assert(value->type == 0xA0);
  assert(value->ptr != 0);
  assert(value->ptr == (&ptr[ptr_idx]));
  assert(value->freefn == 0);
  assert(binn_get_str(value) == (&ptr[ptr_idx]));
  assert(binn_get_int32(value, &vint32) == 1);
  assert(vint32 == (-456));
  assert(binn_get_int64(value, &vint64) == 1);
  assert(vint64 == (-456));
  assert(binn_get_double(value, &vdouble) == 1);
  assert(AlmostEqualFloats(vdouble, -456, 4) == 1);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 1);
  assert(value->type == 0xA0);
  assert(value->ptr != 0);
  assert(value->ptr == (&ptr[ptr_idx]));
  assert(value->freefn == 0);
  binn_free(value);
  ptr_idx = "-4.56";
  value_idx = binn_string(ptr, (binn_mem_free) 0);
  assert((&value[value_idx]) != 0);
  assert(value->type == 0xA0);
  assert(value->ptr != 0);
  assert(value->ptr == (&ptr[ptr_idx]));
  assert(value->freefn == 0);
  assert(binn_get_str(value) == (&ptr[ptr_idx]));
  assert(binn_get_int32(value, &vint32) == 1);
  assert(vint32 == (-4));
  assert(binn_get_int64(value, &vint64) == 1);
  assert(vint64 == (-4));
  assert(binn_get_double(value, &vdouble) == 1);
  assert(AlmostEqualFloats(vdouble, -4.56, 4) == 1);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 1);
  assert(value->type == 0xA0);
  assert(value->ptr != 0);
  assert(value->ptr == (&ptr[ptr_idx]));
  assert(value->freefn == 0);
  binn_free(value);
  ptr_idx = "yes";
  value_idx = binn_string(ptr, (binn_mem_free) 0);
  assert((&value[value_idx]) != 0);
  assert(binn_get_str(value) == (&ptr[ptr_idx]));
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 1);
  binn_free(value);
  ptr_idx = "no";
  value_idx = binn_string(ptr, (binn_mem_free) 0);
  assert((&value[value_idx]) != 0);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 0);
  binn_free(value);
  ptr_idx = "on";
  value_idx = binn_string(ptr, (binn_mem_free) 0);
  assert((&value[value_idx]) != 0);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 1);
  binn_free(value);
  ptr_idx = "off";
  value_idx = binn_string(ptr, (binn_mem_free) 0);
  assert((&value[value_idx]) != 0);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 0);
  binn_free(value);
  ptr_idx = "true";
  value_idx = binn_string(ptr, (binn_mem_free) 0);
  assert((&value[value_idx]) != 0);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 1);
  binn_free(value);
  ptr_idx = "false";
  value_idx = binn_string(ptr, (binn_mem_free) 0);
  assert((&value[value_idx]) != 0);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 0);
  binn_free(value);
  ptr_idx = "1";
  value_idx = binn_string(ptr, (binn_mem_free) 0);
  assert((&value[value_idx]) != 0);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 1);
  binn_free(value);
  ptr_idx = "0";
  value_idx = binn_string(ptr, (binn_mem_free) 0);
  assert((&value[value_idx]) != 0);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 0);
  binn_free(value);
  value_idx = binn_int32(-345);
  assert((&value[value_idx]) != 0);
  assert(value->type == 0x61);
  assert(value->vint32 == (-345));
  assert(value->freefn == 0);
  assert(binn_get_int32(value, &vint32) == 1);
  assert(vint32 == (-345));
  assert(binn_get_int64(value, &vint64) == 1);
  assert(vint64 == (-345));
  assert(binn_get_double(value, &vdouble) == 1);
  assert(AlmostEqualFloats(vdouble, -345, 4) == 1);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 1);
  assert(value->type == 0x61);
  assert(value->vint32 == (-345));
  assert(value->freefn == 0);
  ptr_idx = binn_get_str(value);
  assert((&ptr[ptr_idx]) != 0);
  assert(strcmp(ptr, "-345") == 0);
  assert(value->type == 0xA0);
  assert(value->ptr != 0);
  assert(value->ptr == (&ptr[ptr_idx]));
  assert(value->freefn != 0);
  binn_free(value);
  value_idx = binn_int32(0);
  assert((&value[value_idx]) != 0);
  assert(value->type == 0x61);
  assert(value->vint32 == 0);
  assert(value->freefn == 0);
  assert(binn_get_int32(value, &vint32) == 1);
  assert(vint32 == 0);
  assert(binn_get_int64(value, &vint64) == 1);
  assert(vint64 == 0);
  assert(binn_get_double(value, &vdouble) == 1);
  assert(AlmostEqualFloats(vdouble, 0, 4) == 1);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 0);
  assert(value->type == 0x61);
  assert(value->vint32 == 0);
  assert(value->freefn == 0);
  ptr_idx = binn_get_str(value);
  assert((&ptr[ptr_idx]) != 0);
  assert(strcmp(ptr, "0") == 0);
  assert(value->type == 0xA0);
  assert(value->ptr != 0);
  assert(value->ptr == (&ptr[ptr_idx]));
  assert(value->freefn != 0);
  binn_free(value);
  value_idx = binn_int64(-345678);
  assert((&value[value_idx]) != 0);
  assert(value->type == 0x81);
  assert(value->vint64 == (-345678));
  assert(value->freefn == 0);
  assert(binn_get_int32(value, &vint32) == 1);
  assert(vint32 == (-345678));
  assert(binn_get_int64(value, &vint64) == 1);
  assert(vint64 == (-345678));
  assert(binn_get_double(value, &vdouble) == 1);
  assert(AlmostEqualFloats(vdouble, -345678, 4) == 1);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 1);
  assert(value->type == 0x81);
  assert(value->vint64 == (-345678));
  assert(value->freefn == 0);
  ptr_idx = binn_get_str(value);
  assert((&ptr[ptr_idx]) != 0);
  assert(strcmp(ptr, "-345678") == 0);
  assert(value->type == 0xA0);
  assert(value->ptr != 0);
  assert(value->ptr == (&ptr[ptr_idx]));
  assert(value->freefn != 0);
  binn_free(value);
  value_idx = binn_double(-345.678);
  assert((&value[value_idx]) != 0);
  assert(value->type == 0x82);
  assert(value->vdouble == (-345.678));
  assert(value->freefn == 0);
  assert(binn_get_int32(value, &vint32) == 1);
  assert(vint32 == (-345));
  assert(binn_get_int64(value, &vint64) == 1);
  assert(vint64 == (-345));
  assert(binn_get_double(value, &vdouble) == 1);
  assert(AlmostEqualFloats(vdouble, -345.678, 4) == 1);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 1);
  assert(value->type == 0x82);
  assert(value->vdouble == (-345.678));
  assert(value->freefn == 0);
  ptr_idx = binn_get_str(value);
  assert((&ptr[ptr_idx]) != 0);
  assert(strcmp(ptr, "-345.678") == 0);
  assert(value->type == 0xA0);
  assert(value->ptr != 0);
  assert(value->ptr == (&ptr[ptr_idx]));
  assert(value->freefn != 0);
  binn_free(value);
  value_idx = binn_double(0.0);
  assert((&value[value_idx]) != 0);
  assert(value->type == 0x82);
  assert(value->vdouble == 0.0);
  assert(value->freefn == 0);
  assert(binn_get_int32(value, &vint32) == 1);
  assert(vint32 == 0);
  assert(binn_get_int64(value, &vint64) == 1);
  assert(vint64 == 0);
  assert(binn_get_double(value, &vdouble) == 1);
  assert(AlmostEqualFloats(vdouble, 0, 4) == 1);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 0);
  assert(value->type == 0x82);
  assert(value->vdouble == 0.0);
  assert(value->freefn == 0);
  ptr_idx = binn_get_str(value);
  assert((&ptr[ptr_idx]) != 0);
  assert(strcmp(ptr, "0") == 0);
  assert(value->type == 0xA0);
  assert(value->ptr != 0);
  assert(value->ptr == (&ptr[ptr_idx]));
  assert(value->freefn != 0);
  binn_free(value);
  value_idx = binn_bool(0);
  assert((&value[value_idx]) != 0);
  assert(value->type == 0x80061);
  assert(value->vbool == 0);
  assert(value->freefn == 0);
  assert(binn_get_int32(value, &vint32) == 1);
  assert(vint32 == 0);
  assert(binn_get_int64(value, &vint64) == 1);
  assert(vint64 == 0);
  assert(binn_get_double(value, &vdouble) == 1);
  assert(AlmostEqualFloats(vdouble, 0, 4) == 1);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 0);
  assert(value->type == 0x80061);
  assert(value->vbool == 0);
  assert(value->freefn == 0);
  ptr_idx = binn_get_str(value);
  assert((&ptr[ptr_idx]) != 0);
  assert(strcmp(ptr, "false") == 0);
  assert(value->type == 0xA0);
  assert(value->ptr != 0);
  assert(value->ptr == (&ptr[ptr_idx]));
  assert(value->freefn != 0);
  binn_free(value);
  value_idx = binn_bool(1);
  assert((&value[value_idx]) != 0);
  assert(value->type == 0x80061);
  assert(value->vbool == 1);
  assert(value->freefn == 0);
  assert(binn_get_int32(value, &vint32) == 1);
  assert(vint32 == 1);
  assert(binn_get_int64(value, &vint64) == 1);
  assert(vint64 == 1);
  assert(binn_get_double(value, &vdouble) == 1);
  assert(AlmostEqualFloats(vdouble, 1, 4) == 1);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 1);
  assert(value->type == 0x80061);
  assert(value->vbool == 1);
  assert(value->freefn == 0);
  ptr_idx = binn_get_str(value);
  assert((&ptr[ptr_idx]) != 0);
  assert(strcmp(ptr, "true") == 0);
  assert(value->type == 0xA0);
  assert(value->ptr != 0);
  assert(value->ptr == (&ptr[ptr_idx]));
  assert(value->freefn != 0);
  binn_free(value);
  puts("OK");
}


/*** DEPENDENCIES:
BOOL binn_get_double(binn *value, double *pfloat)
{
  int64 vint;
  if ((value == 0) || (pfloat == 0))
  {
    return 0;
  }
  if (type_family(value->type) == 0xf2)
  {
    if (copy_int_value(value->ptr, &vint, value->type, 0x81) == 0)
    {
      return 0;
    }
    *pfloat = (double) vint;
    return 1;
  }
  switch (value->type)
  {
    case 0x62:
    {
      *pfloat = value->vfloat;
      break;
    }

    case 0x82:
    {
      *pfloat = value->vdouble;
      break;
    }

    case 0xA0:
    {
      if (is_integer((char *) value->ptr))
      {
        *pfloat = (double) atoi64((char *) value->ptr);
      }
      else
        if (is_float((char *) value->ptr))
      {
        *pfloat = atof((char *) value->ptr);
      }
      else
        return 0;
      break;
    }

    case 0x80061:
    {
      *pfloat = value->vbool;
      break;
    }

    default:
    {
      return 0;
    }

  }

  return 1;
}


----------------------------
int vint32
----------------------------
BOOL binn_get_bool(binn *value, BOOL *pbool)
{
  int64 vint;
  if ((value == 0) || (pbool == 0))
  {
    return 0;
  }
  if (type_family(value->type) == 0xf2)
  {
    if (copy_int_value(value->ptr, &vint, value->type, 0x81) == 0)
    {
      return 0;
    }
    *pbool = (vint != 0) ? (1) : (0);
    return 1;
  }
  switch (value->type)
  {
    case 0x80061:
    {
      *pbool = value->vbool;
      break;
    }

    case 0x62:
    {
      *pbool = (value->vfloat != 0) ? (1) : (0);
      break;
    }

    case 0x82:
    {
      *pbool = (value->vdouble != 0) ? (1) : (0);
      break;
    }

    case 0xA0:
    {
      return is_bool_str((char *) value->ptr, pbool);
    }

    default:
    {
      return 0;
    }

  }

  return 1;
}


----------------------------
typedef long long int int64
----------------------------
inline static binn *binn_int64(int64 value)
{
  return binn_value(0x81, &value, 0, 0);
}


----------------------------
void *memdup(void *src, int size)
{
  void *dest;
  unsigned int dest_idx = 0;
  if ((src == 0) || (size <= 0))
  {
    return 0;
  }
  dest_idx = malloc(size);
  if ((&dest[dest_idx]) == 0)
  {
    return 0;
  }
  memcpy(dest, src, size);
  return dest;
}


----------------------------
BOOL binn_get_int64(binn *value, int64 *pint)
{
  if ((value == 0) || (pint == 0))
  {
    return 0;
  }
  if (type_family(value->type) == 0xf2)
  {
    return copy_int_value(value->ptr, pint, value->type, 0x81);
  }
  switch (value->type)
  {
    case 0x62:
    {
      if ((value->vfloat < INT64_MIN) || (value->vfloat > INT64_MAX))
      {
        return 0;
      }
      *pint = (value->vfloat >= 0.0) ? ((int) (value->vfloat + 0.5)) : (((value->vfloat - ((double) ((int) value->vfloat))) <= (-0.5)) ? ((int) value->vfloat) : ((int) (value->vfloat - 0.5)));
      break;
    }

    case 0x82:
    {
      if ((value->vdouble < INT64_MIN) || (value->vdouble > INT64_MAX))
      {
        return 0;
      }
      *pint = (value->vdouble >= 0.0) ? ((int) (value->vdouble + 0.5)) : (((value->vdouble - ((double) ((int) value->vdouble))) <= (-0.5)) ? ((int) value->vdouble) : ((int) (value->vdouble - 0.5)));
      break;
    }

    case 0xA0:
    {
      if (is_integer((char *) value->ptr))
      {
        *pint = atoi64((char *) value->ptr);
      }
      else
        if (is_float((char *) value->ptr))
      {
        *pint = (atof((char *) value->ptr) >= 0.0) ? ((int) (atof((char *) value->ptr) + 0.5)) : (((atof((char *) value->ptr) - ((double) ((int) atof((char *) value->ptr)))) <= (-0.5)) ? ((int) atof((char *) value->ptr)) : ((int) (atof((char *) value->ptr) - 0.5)));
      }
      else
        return 0;
      break;
    }

    case 0x80061:
    {
      *pint = value->vbool;
      break;
    }

    default:
    {
      return 0;
    }

  }

  return 1;
}


----------------------------
inline static binn *binn_int32(int value)
{
  return binn_value(0x61, &value, 0, 0);
}


----------------------------
inline static binn *binn_string(char *str, binn_mem_free freefn)
{
  return binn_value(0xA0, str, 0, freefn);
}


----------------------------
inline static binn *binn_blob(void *ptr, int size, binn_mem_free freefn)
{
  return binn_value(0xC0, ptr, size, freefn);
}


----------------------------
inline static binn *binn_double(double value)
{
  return binn_value(0x82, &value, 0, 0);
}


----------------------------
char *binn_get_str(binn *value)
{
  int64 vint;
  char buf[128];
  if (value == 0)
  {
    return 0;
  }
  if (type_family(value->type) == 0xf2)
  {
    if (copy_int_value(value->ptr, &vint, value->type, 0x81) == 0)
    {
      return 0;
    }
    snprintf(buf, sizeof(buf), "%lli", vint);
    goto loc_convert_value;
  }
  switch (value->type)
  {
    case 0x62:
    {
      value->vdouble = value->vfloat;
    }

    case 0x82:
    {
      snprintf(buf, sizeof(buf), "%g", value->vdouble);
      goto loc_convert_value;
    }

    case 0xA0:
    {
      return (char *) value->ptr;
    }

    case 0x80061:
    {
      if (value->vbool)
      {
        strcpy(buf, "true");
      }
      else
        strcpy(buf, "false");
      goto loc_convert_value;
    }

  }

  return 0;
  loc_convert_value:
  value->ptr = strdup(buf);

  if (value->ptr == 0)
  {
    return 0;
  }
  value->freefn = free;
  value->type = 0xA0;
  return (char *) value->ptr;
}


----------------------------
typedef struct binn_struct binn
----------------------------
inline static binn *binn_bool(BOOL value)
{
  return binn_value(0x80061, &value, 0, 0);
}


----------------------------
int64 vint64
----------------------------
BOOL binn_get_int32(binn *value, int *pint)
{
  if ((value == 0) || (pint == 0))
  {
    return 0;
  }
  if (type_family(value->type) == 0xf2)
  {
    return copy_int_value(value->ptr, pint, value->type, 0x61);
  }
  switch (value->type)
  {
    case 0x62:
    {
      if ((value->vfloat < INT32_MIN) || (value->vfloat > INT32_MAX))
      {
        return 0;
      }
      *pint = (value->vfloat >= 0.0) ? ((int) (value->vfloat + 0.5)) : (((value->vfloat - ((double) ((int) value->vfloat))) <= (-0.5)) ? ((int) value->vfloat) : ((int) (value->vfloat - 0.5)));
      break;
    }

    case 0x82:
    {
      if ((value->vdouble < INT32_MIN) || (value->vdouble > INT32_MAX))
      {
        return 0;
      }
      *pint = (value->vdouble >= 0.0) ? ((int) (value->vdouble + 0.5)) : (((value->vdouble - ((double) ((int) value->vdouble))) <= (-0.5)) ? ((int) value->vdouble) : ((int) (value->vdouble - 0.5)));
      break;
    }

    case 0xA0:
    {
      if (is_integer((char *) value->ptr))
      {
        *pint = atoi((char *) value->ptr);
      }
      else
        if (is_float((char *) value->ptr))
      {
        *pint = (atof((char *) value->ptr) >= 0.0) ? ((int) (atof((char *) value->ptr) + 0.5)) : (((atof((char *) value->ptr) - ((double) ((int) atof((char *) value->ptr)))) <= (-0.5)) ? ((int) atof((char *) value->ptr)) : ((int) (atof((char *) value->ptr) - 0.5)));
      }
      else
        return 0;
      break;
    }

    case 0x80061:
    {
      *pint = value->vbool;
      break;
    }

    default:
    {
      return 0;
    }

  }

  return 1;
}


----------------------------
typedef int BOOL
----------------------------
BOOL AlmostEqualFloats(float A, float B, int maxUlps)
{
  int aInt;
  int bInt;
  int intDiff;
  assert((maxUlps > 0) && (maxUlps < ((4 * 1024) * 1024)));
  aInt = *((int *) (&A));
  bInt = *((int *) (&B));
  if (aInt < 0)
  {
    aInt = 0x80000000 - aInt;
  }
  if (bInt < 0)
  {
    bInt = 0x80000000 - bInt;
  }
  intDiff = abs(aInt - bInt);
  if (intDiff <= maxUlps)
  {
    return 1;
  }
  return 0;
}


----------------------------
void binn_free(binn *item)
{
  if (item == 0)
  {
    return;
  }
  if (item->writable && (item->pre_allocated == 0))
  {
    free_fn(item->pbuf);
  }
  if (item->freefn)
  {
    item->freefn(item->ptr);
  }
  if (item->allocated)
  {
    free_fn(item);
  }
  else
  {
    memset(item, 0, sizeof(binn));
    item->header = 0x1F22B11F;
  }
}


----------------------------
BOOL vbool
----------------------------
***/


void test_binn_int_conversion()
{
  binn *obj = 0;
  unsigned int obj_idx = 0;
  void *ptr;
  unsigned int ptr_idx = 0;
  printf("testing binn integer read conversion... ");
  obj_idx = binn_object();
  assert((&obj[obj_idx]) != 0);
  assert(binn_object_set_int8(obj, "int8", -8) == 1);
  assert(binn_object_set_int16(obj, "int16", -16) == 1);
  assert(binn_object_set_int32(obj, "int32", -32) == 1);
  assert(binn_object_set_int64(obj, "int64", -64) == 1);
  assert(binn_object_set_uint8(obj, "uint8", 111) == 1);
  assert(binn_object_set_uint16(obj, "uint16", 112) == 1);
  assert(binn_object_set_uint32(obj, "uint32", 113) == 1);
  assert(binn_object_set_uint64(obj, "uint64", 114) == 1);
  ptr_idx = binn_ptr(obj);
  assert(binn_object_int8(ptr, "int8") == (-8));
  assert(binn_object_int8(ptr, "int16") == (-16));
  assert(binn_object_int8(ptr, "int32") == (-32));
  assert(binn_object_int8(ptr, "int64") == (-64));
  assert(binn_object_int16(ptr, "int8") == (-8));
  assert(binn_object_int16(ptr, "int16") == (-16));
  assert(binn_object_int16(ptr, "int32") == (-32));
  assert(binn_object_int16(ptr, "int64") == (-64));
  assert(binn_object_int32(ptr, "int8") == (-8));
  assert(binn_object_int32(ptr, "int16") == (-16));
  assert(binn_object_int32(ptr, "int32") == (-32));
  assert(binn_object_int32(ptr, "int64") == (-64));
  assert(binn_object_int64(ptr, "int8") == (-8));
  assert(binn_object_int64(ptr, "int16") == (-16));
  assert(binn_object_int64(ptr, "int32") == (-32));
  assert(binn_object_int64(ptr, "int64") == (-64));
  assert(binn_object_int8(ptr, "uint8") == 111);
  assert(binn_object_int8(ptr, "uint16") == 112);
  assert(binn_object_int8(ptr, "uint32") == 113);
  assert(binn_object_int8(ptr, "uint64") == 114);
  assert(binn_object_int16(ptr, "uint8") == 111);
  assert(binn_object_int16(ptr, "uint16") == 112);
  assert(binn_object_int16(ptr, "uint32") == 113);
  assert(binn_object_int16(ptr, "uint64") == 114);
  assert(binn_object_int32(ptr, "uint8") == 111);
  assert(binn_object_int32(ptr, "uint16") == 112);
  assert(binn_object_int32(ptr, "uint32") == 113);
  assert(binn_object_int32(ptr, "uint64") == 114);
  assert(binn_object_int64(ptr, "uint8") == 111);
  assert(binn_object_int64(ptr, "uint16") == 112);
  assert(binn_object_int64(ptr, "uint32") == 113);
  assert(binn_object_int64(ptr, "uint64") == 114);
  binn_free(obj);
  puts("OK");
}


/*** DEPENDENCIES:
inline static BOOL binn_object_set_int32(binn *obj, const char *key, int value)
{
  return binn_object_set(obj, key, 0x61, &value, 0);
}


----------------------------
int binn_object_int32(void *obj, const char *key)
{
  int value;
  binn_object_get(obj, key, 0x61, &value, 0);
  return value;
}


----------------------------
short binn_object_int16(void *obj, const char *key)
{
  short value;
  binn_object_get(obj, key, 0x41, &value, 0);
  return value;
}


----------------------------
inline static BOOL binn_object_set_int16(binn *obj, const char *key, short value)
{
  return binn_object_set(obj, key, 0x41, &value, 0);
}


----------------------------
void *binn_ptr(void *ptr)
{
  binn *item;
  unsigned int item_idx = 0;
  switch (binn_get_ptr_type(ptr))
  {
    case 1:
    {
      item_idx = (binn *) ptr;
      if (item->writable && item->dirty)
      {
        binn_save_header(item);
      }
      return item->ptr;
    }

    case 2:
    {
      return ptr;
    }

    default:
    {
      return 0;
    }

  }

}


----------------------------
inline static BOOL binn_object_set_int8(binn *obj, const char *key, signed char value)
{
  return binn_object_set(obj, key, 0x21, &value, 0);
}


----------------------------
signed char binn_object_int8(void *obj, const char *key)
{
  signed char value;
  binn_object_get(obj, key, 0x21, &value, 0);
  return value;
}


----------------------------
int64 binn_object_int64(void *obj, const char *key)
{
  int64 value;
  binn_object_get(obj, key, 0x81, &value, 0);
  return value;
}


----------------------------
binn *binn_object()
{
  return binn_new(0xE2, 0, 0);
}


----------------------------
inline static BOOL binn_object_set_uint16(binn *obj, const char *key, unsigned short value)
{
  return binn_object_set(obj, key, 0x40, &value, 0);
}


----------------------------
inline static BOOL binn_object_set_int64(binn *obj, const char *key, int64 value)
{
  return binn_object_set(obj, key, 0x81, &value, 0);
}


----------------------------
inline static BOOL binn_object_set_uint8(binn *obj, const char *key, unsigned char value)
{
  return binn_object_set(obj, key, 0x20, &value, 0);
}


----------------------------
typedef struct binn_struct binn
----------------------------
void binn_free(binn *item)
{
  if (item == 0)
  {
    return;
  }
  if (item->writable && (item->pre_allocated == 0))
  {
    free_fn(item->pbuf);
  }
  if (item->freefn)
  {
    item->freefn(item->ptr);
  }
  if (item->allocated)
  {
    free_fn(item);
  }
  else
  {
    memset(item, 0, sizeof(binn));
    item->header = 0x1F22B11F;
  }
}


----------------------------
inline static BOOL binn_object_set_uint32(binn *obj, const char *key, unsigned int value)
{
  return binn_object_set(obj, key, 0x60, &value, 0);
}


----------------------------
inline static BOOL binn_object_set_uint64(binn *obj, const char *key, uint64 value)
{
  return binn_object_set(obj, key, 0x80, &value, 0);
}


----------------------------
***/


char *test_create_object_1(int *psize)
{
  binn *obj = 0;
  unsigned int obj_idx = 0;
  binn *list = 0;
  unsigned int list_idx = 0;
  printf("creating object 1...\n");
  obj_idx = binn_object();
  assert((&obj[obj_idx]) != 0);
  vint32 = -12345;
  assert(binn_object_set(obj, "int32", 0x61, &vint32, 0) == 1);
  vint16 = -258;
  assert(binn_object_set(obj, "int16", 0x41, &vint16, 0) == 1);
  vint8 = -120;
  assert(binn_object_set(obj, "int8", 0x21, &vint8, 0) == 1);
  vint64 = -1234567890123;
  assert(binn_object_set(obj, "int64", 0x81, &vint64, 0) == 1);
  vuint32 = 123456;
  assert(binn_object_set(obj, "uint32", 0x60, &vuint32, 0) == 1);
  vuint16 = 60500;
  assert(binn_object_set(obj, "uint16", 0x40, &vuint16, 0) == 1);
  vuint8 = 250;
  assert(binn_object_set(obj, "uint8", 0x20, &vuint8, 0) == 1);
  vuint64 = 1234567890123;
  assert(binn_object_set(obj, "uint64", 0x80, &vuint64, 0) == 1);
  vfloat32 = -12.345;
  assert(binn_object_set(obj, "float32", 0x62, &vfloat32, 0) == 1);
  vfloat32 = -12.345;
  assert(binn_object_set(obj, "single", 0x62, &vfloat32, 0) == 1);
  vfloat64 = -123456.7895;
  assert(binn_object_set(obj, "float64", 0x82, &vfloat64, 0) == 1);
  vfloat64 = -123456.7895;
  assert(binn_object_set(obj, "double", 0x82, &vfloat64, 0) == 1);
  assert(binn_object_set(obj, "str", 0xA0, "the value", 0) == 1);
  vint32 = 1;
  assert(binn_object_set(obj, "bool_true", 0x80061, &vint32, 0) == 1);
  vint32 = 0;
  assert(binn_object_set(obj, "bool_false", 0x80061, &vint32, 0) == 1);
  assert(binn_object_set(obj, "null", 0x00, 0, 0) == 1);
  list_idx = binn_list();
  assert((&list[list_idx]) != 0);
  assert(binn_list_add(list, 0x00, 0, 0) == 1);
  vint32 = 123;
  assert(binn_list_add(list, 0x61, &vint32, 0) == 1);
  assert(binn_list_add(list, 0xA0, "this is a string", 0) == 1);
  assert(binn_object_set(obj, "list", 0xE0, binn_ptr(list), binn_size(list)) == 1);
  binn_free(list);
  list_idx = 0;
  *psize = binn_size(obj);
  return (char *) binn_ptr(obj);
}


/*** DEPENDENCIES:
signed char vint8
----------------------------
double vfloat64
----------------------------
unsigned int vuint32
----------------------------
short vint16
----------------------------
int vint32
----------------------------
uint64 vuint64
----------------------------
unsigned short vuint16
----------------------------
void *binn_ptr(void *ptr)
{
  binn *item;
  unsigned int item_idx = 0;
  switch (binn_get_ptr_type(ptr))
  {
    case 1:
    {
      item_idx = (binn *) ptr;
      if (item->writable && item->dirty)
      {
        binn_save_header(item);
      }
      return item->ptr;
    }

    case 2:
    {
      return ptr;
    }

    default:
    {
      return 0;
    }

  }

}


----------------------------
binn *binn_list()
{
  return binn_new(0xE0, 0, 0);
}


----------------------------
binn *binn_object()
{
  return binn_new(0xE2, 0, 0);
}


----------------------------
int binn_size(void *ptr)
{
  binn *item;
  unsigned int item_idx = 0;
  switch (binn_get_ptr_type(ptr))
  {
    case 1:
    {
      item_idx = (binn *) ptr;
      if (item->writable && item->dirty)
      {
        binn_save_header(item);
      }
      return item->size;
    }

    case 2:
    {
      return binn_buf_size(ptr);
    }

    default:
    {
      return 0;
    }

  }

}


----------------------------
BOOL binn_object_set(binn *obj, const char *key, int type, void *pvalue, int size)
{
  if (GetWriteConvertedData(&type, &pvalue, &size) == 0)
  {
    return 0;
  }
  return binn_object_set_raw(obj, key, type, pvalue, size);
}


----------------------------
typedef struct binn_struct binn
----------------------------
float vfloat32
----------------------------
void binn_free(binn *item)
{
  if (item == 0)
  {
    return;
  }
  if (item->writable && (item->pre_allocated == 0))
  {
    free_fn(item->pbuf);
  }
  if (item->freefn)
  {
    item->freefn(item->ptr);
  }
  if (item->allocated)
  {
    free_fn(item);
  }
  else
  {
    memset(item, 0, sizeof(binn));
    item->header = 0x1F22B11F;
  }
}


----------------------------
int64 vint64
----------------------------
unsigned char vuint8
----------------------------
BOOL binn_list_add(binn *list, int type, void *pvalue, int size)
{
  if (GetWriteConvertedData(&type, &pvalue, &size) == 0)
  {
    return 0;
  }
  return binn_list_add_raw(list, type, pvalue, size);
}


----------------------------
***/


void test_binn_iter(BOOL use_int_compression)
{
  binn *list;
  unsigned int list_idx = 0;
  binn *map;
  unsigned int map_idx = 0;
  binn *obj;
  unsigned int obj_idx = 0;
  binn *list2;
  unsigned int list2_idx = 0;
  binn *copy = 0;
  unsigned int copy_idx = 0;
  binn_iter iter;
  binn_iter iter2;
  binn value;
  binn value2;
  int blob_size;
  int id;
  int id2;
  int list2size;
  void *ptr;
  unsigned int ptr_idx = 0;
  void *blob_ptr;
  unsigned int blob_ptr_idx = 0;
  char key[256];
  char key2[256];
  blob_ptr_idx = "key\0value\0\0";
  blob_size = 11;
  printf("testing binn sequential read (use_int_compression = %d)... ", use_int_compression);
  list_idx = binn_list();
  list2_idx = binn_list();
  map_idx = binn_map();
  obj_idx = binn_object();
  assert((&list[list_idx]) != 0);
  assert((&list2[list2_idx]) != 0);
  assert((&map[map_idx]) != 0);
  assert((&obj[obj_idx]) != 0);
  if (use_int_compression == 0)
  {
    list->disable_int_compression = 1;
    map->disable_int_compression = 1;
    obj->disable_int_compression = 1;
  }
  assert(binn_list_add_int32(list2, 250) == 1);
  assert(binn_list_add_null(list2) == 1);
  assert(binn_list_add_str(list2, "l1st2") == 1);
  assert(binn_list_add_bool(list2, 1) == 1);
  list2size = binn_size(list2);
  assert(binn_list_add_int8(list, 111) == 1);
  assert(binn_list_add_int32(list, 123456789) == 1);
  assert(binn_list_add_int16(list, -123) == 1);
  assert(binn_list_add_int64(list, 9876543210) == 1);
  assert(binn_list_add_float(list, 1.25) == 1);
  assert(binn_list_add_double(list, 25.987654321) == 1);
  assert(binn_list_add_bool(list, 1) == 1);
  assert(binn_list_add_bool(list, 0) == 1);
  assert(binn_list_add_null(list) == 1);
  assert(binn_list_add_str(list, "testing...") == 1);
  assert(binn_list_add_blob(list, (char *) blob_ptr, blob_size) == 1);
  assert(binn_list_add_list(list, list2) == 1);
  assert(binn_object_set_int8(obj, "a", 111) == 1);
  assert(binn_object_set_int32(obj, "b", 123456789) == 1);
  assert(binn_object_set_int16(obj, "c", -123) == 1);
  assert(binn_object_set_int64(obj, "d", 9876543210) == 1);
  assert(binn_object_set_float(obj, "e", 1.25) == 1);
  assert(binn_object_set_double(obj, "f", 25.987654321) == 1);
  assert(binn_object_set_bool(obj, "g", 1) == 1);
  assert(binn_object_set_bool(obj, "h", 0) == 1);
  assert(binn_object_set_null(obj, "i") == 1);
  assert(binn_object_set_str(obj, "j", "testing...") == 1);
  assert(binn_object_set_blob(obj, "k", (char *) blob_ptr, blob_size) == 1);
  assert(binn_object_set_list(obj, "l", list2) == 1);
  assert(binn_map_set_int8(map, 55010, 111) == 1);
  assert(binn_map_set_int32(map, 55020, 123456789) == 1);
  assert(binn_map_set_int16(map, 55030, -123) == 1);
  assert(binn_map_set_int64(map, 55040, 9876543210) == 1);
  assert(binn_map_set_float(map, 55050, 1.25) == 1);
  assert(binn_map_set_double(map, 55060, 25.987654321) == 1);
  assert(binn_map_set_bool(map, 55070, 1) == 1);
  assert(binn_map_set_bool(map, 55080, 0) == 1);
  assert(binn_map_set_null(map, 55090) == 1);
  assert(binn_map_set_str(map, 55100, "testing...") == 1);
  assert(binn_map_set_blob(map, 55110, (char *) blob_ptr, blob_size) == 1);
  assert(binn_map_set_list(map, 55120, list2) == 1);
  ptr_idx = binn_ptr(list);
  assert((&ptr[ptr_idx]) != 0);
  assert(binn_iter_init(&iter, ptr, 0xE0));
  assert(iter.pnext > (&ptr[ptr_idx]));
  assert(iter.plimit > (&ptr[ptr_idx]));
  assert(iter.count == 12);
  assert(iter.current == 0);
  assert(binn_list_next(&iter, &value) == 1);
  assert(iter.pnext > (&ptr[ptr_idx]));
  assert(iter.plimit > (&ptr[ptr_idx]));
  assert(iter.count == 12);
  assert(iter.current == 1);
  assert(value.type == 0x21);
  assert(value.vint8 == 111);
  assert(binn_list_next(&iter, &value) == 1);
  assert(iter.current == 2);
  if (use_int_compression)
  {
    assert(value.type == 0x60);
  }
  else
  {
    assert(value.type == 0x61);
  }
  assert(value.vint32 == 123456789);
  assert(binn_list_next(&iter, &value) == 1);
  assert(iter.current == 3);
  if (use_int_compression)
  {
    assert(value.type == 0x21);
    assert(value.vint8 == (-123));
  }
  else
  {
    assert(value.type == 0x41);
    assert(value.vint16 == (-123));
  }
  assert(binn_list_next(&iter, &value) == 1);
  assert(iter.current == 4);
  assert(value.type == 0x81);
  assert(value.vint64 == 9876543210);
  assert(binn_list_next(&iter, &value) == 1);
  assert(iter.current == 5);
  assert(value.type == 0x62);
  assert(AlmostEqualFloats(value.vfloat, 1.25, 2));
  assert(binn_list_next(&iter, &value) == 1);
  assert(iter.current == 6);
  assert(value.type == 0x82);
  assert((value.vdouble - 25.987654321) < 0.00000001);
  assert(binn_list_next(&iter, &value) == 1);
  assert(iter.current == 7);
  assert(value.type == 0x80061);
  assert(value.vbool == 1);
  assert(binn_list_next(&iter, &value) == 1);
  assert(iter.current == 8);
  assert(value.type == 0x80061);
  assert(value.vbool == 0);
  assert(binn_list_next(&iter, &value) == 1);
  assert(iter.current == 9);
  assert(value.type == 0x00);
  assert(binn_list_next(&iter, &value) == 1);
  assert(iter.current == 10);
  assert(value.type == 0xA0);
  assert(strcmp((char *) value.ptr, "testing...") == 0);
  assert(binn_list_next(&iter, &value) == 1);
  assert(iter.current == 11);
  assert(value.type == 0xC0);
  assert(memcmp(value.ptr, blob_ptr, blob_size) == 0);
  assert(binn_list_next(&iter, &value) == 1);
  assert(iter.current == 12);
  assert(value.type == 0xE0);
  assert(value.size == list2size);
  assert(value.count == 4);
  assert(value.ptr != 0);
  assert(binn_list_int32(value.ptr, 1) == 250);
  assert(binn_list_null(value.ptr, 2) == 1);
  ptr_idx = binn_list_str(value.ptr_idx, 3);
  assert((&ptr[ptr_idx]) != 0);
  assert(strcmp((char *) ptr, "l1st2") == 0);
  assert(binn_list_bool(value.ptr, 4) == 1);
  assert(binn_list_next(&iter, &value) == 0);
  assert(binn_list_next(&iter, &value) == 0);
  ptr_idx = binn_ptr(obj);
  assert((&ptr[ptr_idx]) != 0);
  assert(binn_iter_init(&iter, ptr, 0xE2));
  assert(iter.pnext > (&ptr[ptr_idx]));
  assert(iter.plimit > (&ptr[ptr_idx]));
  assert(iter.count == 12);
  assert(iter.current == 0);
  assert(binn_object_next(&iter, key, &value) == 1);
  assert(iter.pnext > (&ptr[ptr_idx]));
  assert(iter.plimit > (&ptr[ptr_idx]));
  assert(iter.count == 12);
  assert(iter.current == 1);
  assert(value.type == 0x21);
  assert(value.vint8 == 111);
  assert(strcmp(key, "a") == 0);
  assert(binn_object_next(&iter, key, &value) == 1);
  assert(iter.current == 2);
  if (use_int_compression)
  {
    assert(value.type == 0x60);
  }
  else
  {
    assert(value.type == 0x61);
  }
  assert(value.vint32 == 123456789);
  assert(strcmp(key, "b") == 0);
  assert(binn_object_next(&iter, key, &value) == 1);
  assert(iter.current == 3);
  if (use_int_compression)
  {
    assert(value.type == 0x21);
    assert(value.vint8 == (-123));
  }
  else
  {
    assert(value.type == 0x41);
    assert(value.vint16 == (-123));
  }
  assert(strcmp(key, "c") == 0);
  assert(binn_object_next(&iter, key, &value) == 1);
  assert(iter.current == 4);
  assert(value.type == 0x81);
  assert(value.vint64 == 9876543210);
  assert(strcmp(key, "d") == 0);
  assert(binn_object_next(&iter, key, &value) == 1);
  assert(iter.current == 5);
  assert(value.type == 0x62);
  assert(AlmostEqualFloats(value.vfloat, 1.25, 2));
  assert(strcmp(key, "e") == 0);
  assert(binn_object_next(&iter, key, &value) == 1);
  assert(iter.current == 6);
  assert(value.type == 0x82);
  assert((value.vdouble - 25.987654321) < 0.00000001);
  assert(strcmp(key, "f") == 0);
  assert(binn_object_next(&iter, key, &value) == 1);
  assert(iter.current == 7);
  assert(value.type == 0x80061);
  assert(value.vbool == 1);
  assert(strcmp(key, "g") == 0);
  assert(binn_object_next(&iter, key, &value) == 1);
  assert(iter.current == 8);
  assert(value.type == 0x80061);
  assert(value.vbool == 0);
  assert(strcmp(key, "h") == 0);
  assert(binn_object_next(&iter, key, &value) == 1);
  assert(iter.current == 9);
  assert(value.type == 0x00);
  assert(strcmp(key, "i") == 0);
  assert(binn_object_next(&iter, key, &value) == 1);
  assert(iter.current == 10);
  assert(value.type == 0xA0);
  assert(strcmp((char *) value.ptr, "testing...") == 0);
  assert(strcmp(key, "j") == 0);
  assert(binn_object_next(&iter, key, &value) == 1);
  assert(iter.current == 11);
  assert(value.type == 0xC0);
  assert(memcmp(value.ptr, blob_ptr, blob_size) == 0);
  assert(strcmp(key, "k") == 0);
  assert(binn_object_next(&iter, key, &value) == 1);
  assert(iter.current == 12);
  assert(value.type == 0xE0);
  assert(value.size == list2size);
  assert(value.count == 4);
  assert(value.ptr != 0);
  assert(binn_list_int32(value.ptr, 1) == 250);
  assert(binn_list_null(value.ptr, 2) == 1);
  ptr_idx = binn_list_str(value.ptr_idx, 3);
  assert((&ptr[ptr_idx]) != 0);
  assert(strcmp((char *) ptr, "l1st2") == 0);
  assert(binn_list_bool(value.ptr, 4) == 1);
  assert(strcmp(key, "l") == 0);
  assert(binn_object_next(&iter, key, &value) == 0);
  assert(binn_object_next(&iter, key, &value) == 0);
  ptr_idx = binn_ptr(map);
  assert((&ptr[ptr_idx]) != 0);
  assert(binn_iter_init(&iter, ptr, 0xE1));
  assert(iter.pnext > (&ptr[ptr_idx]));
  assert(iter.plimit > (&ptr[ptr_idx]));
  assert(iter.count == 12);
  assert(iter.current == 0);
  assert(binn_map_next(&iter, &id, &value) == 1);
  assert(iter.pnext > (&ptr[ptr_idx]));
  assert(iter.plimit > (&ptr[ptr_idx]));
  assert(iter.count == 12);
  assert(iter.current == 1);
  assert(value.type == 0x21);
  assert(value.vint8 == 111);
  assert(id == 55010);
  assert(binn_map_next(&iter, &id, &value) == 1);
  assert(iter.current == 2);
  if (use_int_compression)
  {
    assert(value.type == 0x60);
  }
  else
  {
    assert(value.type == 0x61);
  }
  assert(value.vint32 == 123456789);
  assert(id == 55020);
  assert(binn_map_next(&iter, &id, &value) == 1);
  assert(iter.current == 3);
  if (use_int_compression)
  {
    assert(value.type == 0x21);
    assert(value.vint8 == (-123));
  }
  else
  {
    assert(value.type == 0x41);
    assert(value.vint16 == (-123));
  }
  assert(id == 55030);
  assert(binn_map_next(&iter, &id, &value) == 1);
  assert(iter.current == 4);
  assert(value.type == 0x81);
  assert(value.vint64 == 9876543210);
  assert(id == 55040);
  assert(binn_map_next(&iter, &id, &value) == 1);
  assert(iter.current == 5);
  assert(value.type == 0x62);
  assert(AlmostEqualFloats(value.vfloat, 1.25, 2));
  assert(id == 55050);
  assert(binn_map_next(&iter, &id, &value) == 1);
  assert(iter.current == 6);
  assert(value.type == 0x82);
  assert((value.vdouble - 25.987654321) < 0.00000001);
  assert(id == 55060);
  assert(binn_map_next(&iter, &id, &value) == 1);
  assert(iter.current == 7);
  assert(value.type == 0x80061);
  assert(value.vbool == 1);
  assert(id == 55070);
  assert(binn_map_next(&iter, &id, &value) == 1);
  assert(iter.current == 8);
  assert(value.type == 0x80061);
  assert(value.vbool == 0);
  assert(id == 55080);
  assert(binn_map_next(&iter, &id, &value) == 1);
  assert(iter.current == 9);
  assert(value.type == 0x00);
  assert(id == 55090);
  assert(binn_map_next(&iter, &id, &value) == 1);
  assert(iter.current == 10);
  assert(value.type == 0xA0);
  assert(strcmp((char *) value.ptr, "testing...") == 0);
  assert(id == 55100);
  assert(binn_map_next(&iter, &id, &value) == 1);
  assert(iter.current == 11);
  assert(value.type == 0xC0);
  assert(memcmp(value.ptr, blob_ptr, blob_size) == 0);
  assert(id == 55110);
  assert(binn_map_next(&iter, &id, &value) == 1);
  assert(iter.current == 12);
  assert(value.type == 0xE0);
  assert(value.size == list2size);
  assert(value.count == 4);
  assert(value.ptr != 0);
  assert(binn_list_int32(value.ptr, 1) == 250);
  assert(binn_list_null(value.ptr, 2) == 1);
  ptr_idx = binn_list_str(value.ptr_idx, 3);
  assert((&ptr[ptr_idx]) != 0);
  assert(strcmp((char *) ptr, "l1st2") == 0);
  assert(binn_list_bool(value.ptr, 4) == 1);
  assert(id == 55120);
  assert(binn_map_next(&iter, &id, &value) == 0);
  assert(binn_map_next(&iter, &id, &value) == 0);
  copy_idx = binn_copy(list);
  assert((&copy[copy_idx]) != 0);
  assert(binn_type(copy) == binn_type(list));
  assert(binn_count(copy) == binn_count(list));
  assert(binn_size(copy) == binn_size(list));
  assert(binn_iter_init(&iter, list, 0xE0));
  assert(binn_iter_init(&iter2, copy, 0xE0));
  while (binn_list_next(&iter, &value))
  {
    assert(binn_list_next(&iter2, &value2) == 1);
    assert(value.type == value2.type);
  }

  assert(binn_list_add_str(copy, "testing...") == 1);
  assert(binn_type(copy) == binn_type(list));
  assert(binn_count(copy) == (binn_count(list) + 1));
  assert(binn_size(copy) > binn_size(list));
  binn_free(copy);
  copy_idx = binn_copy(map);
  assert((&copy[copy_idx]) != 0);
  assert(binn_type(copy) == binn_type(map));
  assert(binn_count(copy) == binn_count(map));
  assert(binn_size(copy) == binn_size(map));
  assert(binn_iter_init(&iter, map, 0xE1));
  assert(binn_iter_init(&iter2, copy, 0xE1));
  while (binn_map_next(&iter, &id, &value))
  {
    assert(binn_map_next(&iter2, &id2, &value2) == 1);
    assert(id == id2);
    assert(value.type == value2.type);
  }

  assert(binn_map_set_int32(copy, 5600, 123) == 1);
  assert(binn_type(copy) == binn_type(map));
  assert(binn_count(copy) == (binn_count(map) + 1));
  assert(binn_size(copy) > binn_size(map));
  binn_free(copy);
  copy_idx = binn_copy(obj);
  assert((&copy[copy_idx]) != 0);
  assert(binn_type(copy) == binn_type(obj));
  assert(binn_count(copy) == binn_count(obj));
  assert(binn_size(copy) == binn_size(obj));
  assert(binn_iter_init(&iter, obj, 0xE2));
  assert(binn_iter_init(&iter2, copy, 0xE2));
  while (binn_object_next(&iter, key, &value))
  {
    assert(binn_object_next(&iter2, key2, &value2) == 1);
    assert(strcmp(key, key2) == 0);
    assert(value.type == value2.type);
  }

  assert(binn_object_set_int32(copy, "another", 123) == 1);
  assert(binn_type(copy) == binn_type(obj));
  assert(binn_count(copy) == (binn_count(obj) + 1));
  assert(binn_size(copy) > binn_size(obj));
  binn_free(copy);
  ptr_idx = binn_ptr(list);
  copy_idx = binn_copy(ptr);
  assert((&copy[copy_idx]) != 0);
  assert(binn_type(copy) == binn_type(list));
  assert(binn_count(copy) == binn_count(list));
  assert(binn_size(copy) == binn_size(list));
  assert(binn_iter_init(&iter, ptr, 0xE0));
  assert(binn_iter_init(&iter2, copy, 0xE0));
  while (binn_list_next(&iter, &value))
  {
    assert(binn_list_next(&iter2, &value2) == 1);
    assert(value.type == value2.type);
  }

  assert(binn_list_add_str(copy, "testing...") == 1);
  assert(binn_type(copy) == binn_type(list));
  assert(binn_count(copy) == (binn_count(list) + 1));
  assert(binn_size(copy) > binn_size(list));
  binn_free(copy);
  ptr_idx = binn_ptr(map);
  copy_idx = binn_copy(ptr);
  assert((&copy[copy_idx]) != 0);
  assert(binn_type(copy) == binn_type(map));
  assert(binn_count(copy) == binn_count(map));
  assert(binn_size(copy) == binn_size(map));
  assert(binn_iter_init(&iter, ptr, 0xE1));
  assert(binn_iter_init(&iter2, copy, 0xE1));
  while (binn_map_next(&iter, &id, &value))
  {
    assert(binn_map_next(&iter2, &id2, &value2) == 1);
    assert(id == id2);
    assert(value.type == value2.type);
  }

  assert(binn_map_set_int32(copy, 5600, 123) == 1);
  assert(binn_type(copy) == binn_type(map));
  assert(binn_count(copy) == (binn_count(map) + 1));
  assert(binn_size(copy) > binn_size(map));
  binn_free(copy);
  ptr_idx = binn_ptr(obj);
  copy_idx = binn_copy(ptr);
  assert((&copy[copy_idx]) != 0);
  assert(binn_type(copy) == binn_type(obj));
  assert(binn_count(copy) == binn_count(obj));
  assert(binn_size(copy) == binn_size(obj));
  assert(binn_iter_init(&iter, ptr, 0xE2));
  assert(binn_iter_init(&iter2, copy, 0xE2));
  while (binn_object_next(&iter, key, &value))
  {
    assert(binn_object_next(&iter2, key2, &value2) == 1);
    assert(strcmp(key, key2) == 0);
    assert(value.type == value2.type);
  }

  assert(binn_object_set_int32(copy, "another", 123) == 1);
  assert(binn_type(copy) == binn_type(obj));
  assert(binn_count(copy) == (binn_count(obj) + 1));
  assert(binn_size(copy) > binn_size(obj));
  binn_free(copy);
  binn_free(list);
  binn_free(list2);
  binn_free(map);
  binn_free(obj);
  puts("OK");
}


/*** DEPENDENCIES:
inline static BOOL binn_list_add_int8(binn *list, signed char value)
{
  return binn_list_add(list, 0x21, &value, 0);
}


----------------------------
BOOL binn_list_bool(void *list, int pos)
{
  BOOL value;
  binn_list_get(list, pos, 0x80061, &value, 0);
  return value;
}


----------------------------
inline static BOOL binn_map_set_blob(binn *map, int id, void *ptr, int size)
{
  return binn_map_set(map, id, 0xC0, ptr, size);
}


----------------------------
void *binn_ptr(void *ptr)
{
  binn *item;
  unsigned int item_idx = 0;
  switch (binn_get_ptr_type(ptr))
  {
    case 1:
    {
      item_idx = (binn *) ptr;
      if (item->writable && item->dirty)
      {
        binn_save_header(item);
      }
      return item->ptr;
    }

    case 2:
    {
      return ptr;
    }

    default:
    {
      return 0;
    }

  }

}


----------------------------
binn *binn_list()
{
  return binn_new(0xE0, 0, 0);
}


----------------------------
int vint32
----------------------------
inline static BOOL binn_object_set_int8(binn *obj, const char *key, signed char value)
{
  return binn_object_set(obj, key, 0x21, &value, 0);
}


----------------------------
BOOL binn_list_null(void *list, int pos)
{
  return binn_list_get(list, pos, 0x00, 0, 0);
}


----------------------------
BOOL binn_list_next(binn_iter *iter, binn *value)
{
  unsigned char *pnow;
  unsigned int pnow_idx = 0;
  if (((((iter == 0) || (iter->pnext == 0)) || (iter->pnext > iter->plimit)) || (iter->current > iter->count)) || (iter->type != 0xE0))
  {
    return 0;
  }
  iter->current += 1;
  if (iter->current > iter->count)
  {
    return 0;
  }
  pnow_idx = iter->pnext;
  iter->pnext = AdvanceDataPos(pnow, iter->plimit);
  if ((iter->pnext != 0) && (iter->pnext < (&pnow[pnow_idx])))
  {
    return 0;
  }
  return GetValue(pnow, value);
}


----------------------------
inline static BOOL binn_object_set_bool(binn *obj, const char *key, BOOL value)
{
  return binn_object_set(obj, key, 0x80061, &value, 0);
}


----------------------------
int binn_size(void *ptr)
{
  binn *item;
  unsigned int item_idx = 0;
  switch (binn_get_ptr_type(ptr))
  {
    case 1:
    {
      item_idx = (binn *) ptr;
      if (item->writable && item->dirty)
      {
        binn_save_header(item);
      }
      return item->size;
    }

    case 2:
    {
      return binn_buf_size(ptr);
    }

    default:
    {
      return 0;
    }

  }

}


----------------------------
inline static BOOL binn_list_add_int64(binn *list, int64 value)
{
  return binn_list_add(list, 0x81, &value, 0);
}


----------------------------
inline static BOOL binn_object_set_double(binn *obj, const char *key, double value)
{
  return binn_object_set(obj, key, 0x82, &value, 0);
}


----------------------------
BOOL binn_object_next(binn_iter *iter, char *pkey, binn *value)
{
  return binn_read_next_pair(0xE2, iter, 0, pkey, value);
}


----------------------------
inline static BOOL binn_object_set_int32(binn *obj, const char *key, int value)
{
  return binn_object_set(obj, key, 0x61, &value, 0);
}


----------------------------
signed char vint8
----------------------------
inline static BOOL binn_object_set_list(binn *obj, const char *key, void *list)
{
  return binn_object_set(obj, key, 0xE0, binn_ptr(list), binn_size(list));
}


----------------------------
short vint16
----------------------------
inline static BOOL binn_map_set_int32(binn *map, int id, int value)
{
  return binn_map_set(map, id, 0x61, &value, 0);
}


----------------------------
typedef struct binn_iter_struct
{
  unsigned char *pnext;
  unsigned char *plimit;
  int type;
  int count;
  int current;
} binn_iter
----------------------------
inline static BOOL binn_list_add_int32(binn *list, int value)
{
  return binn_list_add(list, 0x61, &value, 0);
}


----------------------------
binn *binn_object()
{
  return binn_new(0xE2, 0, 0);
}


----------------------------
inline static BOOL binn_list_add_null(binn *list)
{
  return binn_list_add(list, 0x00, 0, 0);
}


----------------------------
inline static BOOL binn_list_add_str(binn *list, char *str)
{
  return binn_list_add(list, 0xA0, str, 0);
}


----------------------------
char *binn_list_str(void *list, int pos)
{
  char *value;
  binn_list_get(list, pos, 0xA0, &value, 0);
  return value;
}


----------------------------
inline static BOOL binn_object_set_int64(binn *obj, const char *key, int64 value)
{
  return binn_object_set(obj, key, 0x81, &value, 0);
}


----------------------------
inline static BOOL binn_list_add_bool(binn *list, BOOL value)
{
  return binn_list_add(list, 0x80061, &value, 0);
}


----------------------------
binn *binn_copy(void *old)
{
  int type;
  int count;
  int size;
  int header_size;
  unsigned char *old_ptr = binn_ptr(old);
  binn *item;
  unsigned int item_idx = 0;
  size = 0;
  if (!IsValidBinnHeader(old_ptr, &type, &count, &size, &header_size))
  {
    return 0;
  }
  item_idx = binn_new(type, (size - header_size) + 9, 0);
  if (item)
  {
    unsigned char *dest;
    unsigned int dest_idx = 0;
    dest_idx = ((unsigned char *) item->pbuf) + 9;
    memcpy(dest, old_ptr + header_size, size - header_size);
    item->used_size = (9 + size) - header_size;
    item->count = count;
  }
  return item;
}


----------------------------
BOOL binn_map_next(binn_iter *iter, int *pid, binn *value)
{
  return binn_read_next_pair(0xE1, iter, pid, 0, value);
}


----------------------------
inline static BOOL binn_object_set_str(binn *obj, const char *key, char *str)
{
  return binn_object_set(obj, key, 0xA0, str, 0);
}


----------------------------
inline static BOOL binn_map_set_bool(binn *map, int id, BOOL value)
{
  return binn_map_set(map, id, 0x80061, &value, 0);
}


----------------------------
inline static BOOL binn_map_set_list(binn *map, int id, void *list)
{
  return binn_map_set(map, id, 0xE0, binn_ptr(list), binn_size(list));
}


----------------------------
inline static BOOL binn_map_set_null(binn *map, int id)
{
  return binn_map_set(map, id, 0x00, 0, 0);
}


----------------------------
int binn_count(void *ptr)
{
  binn *item;
  unsigned int item_idx = 0;
  switch (binn_get_ptr_type(ptr))
  {
    case 1:
    {
      item_idx = (binn *) ptr;
      return item->count;
    }

    case 2:
    {
      return binn_buf_count(ptr);
    }

    default:
    {
      return -1;
    }

  }

}


----------------------------
BOOL binn_iter_init(binn_iter *iter, void *ptr, int expected_type)
{
  unsigned int ptr_idx = 0;
  int type;
  int count;
  int size = 0;
  int header_size;
  ptr_idx = binn_ptr(ptr_idx);
  if (((&ptr[ptr_idx]) == 0) || (iter == 0))
  {
    return 0;
  }
  memset(iter, 0, sizeof(binn_iter));
  if (IsValidBinnHeader(ptr, &type, &count, &size, &header_size) == 0)
  {
    return 0;
  }
  if (type != expected_type)
  {
    return 0;
  }
  iter->plimit = (((unsigned char *) ptr) + size) - 1;
  iter->pnext = ((unsigned char *) ptr) + header_size;
  iter->count = count;
  iter->current = 0;
  iter->type = type;
  return 1;
}


----------------------------
inline static BOOL binn_list_add_double(binn *list, double value)
{
  return binn_list_add(list, 0x82, &value, 0);
}


----------------------------
inline static BOOL binn_map_set_int8(binn *map, int id, signed char value)
{
  return binn_map_set(map, id, 0x21, &value, 0);
}


----------------------------
inline static BOOL binn_list_add_float(binn *list, float value)
{
  return binn_list_add(list, 0x62, &value, 0);
}


----------------------------
inline static BOOL binn_object_set_null(binn *obj, const char *key)
{
  return binn_object_set(obj, key, 0x00, 0, 0);
}


----------------------------
typedef struct binn_struct binn
----------------------------
inline static BOOL binn_object_set_float(binn *obj, const char *key, float value)
{
  return binn_object_set(obj, key, 0x62, &value, 0);
}


----------------------------
int64 vint64
----------------------------
typedef int BOOL
----------------------------
inline static BOOL binn_map_set_int16(binn *map, int id, short value)
{
  return binn_map_set(map, id, 0x41, &value, 0);
}


----------------------------
inline static BOOL binn_map_set_int64(binn *map, int id, int64 value)
{
  return binn_map_set(map, id, 0x81, &value, 0);
}


----------------------------
inline static BOOL binn_list_add_list(binn *list, void *list2)
{
  return binn_list_add(list, 0xE0, binn_ptr(list2), binn_size(list2));
}


----------------------------
inline static BOOL binn_map_set_float(binn *map, int id, float value)
{
  return binn_map_set(map, id, 0x62, &value, 0);
}


----------------------------
inline static BOOL binn_object_set_blob(binn *obj, const char *key, void *ptr, int size)
{
  return binn_object_set(obj, key, 0xC0, ptr, size);
}


----------------------------
BOOL AlmostEqualFloats(float A, float B, int maxUlps)
{
  int aInt;
  int bInt;
  int intDiff;
  assert((maxUlps > 0) && (maxUlps < ((4 * 1024) * 1024)));
  aInt = *((int *) (&A));
  bInt = *((int *) (&B));
  if (aInt < 0)
  {
    aInt = 0x80000000 - aInt;
  }
  if (bInt < 0)
  {
    bInt = 0x80000000 - bInt;
  }
  intDiff = abs(aInt - bInt);
  if (intDiff <= maxUlps)
  {
    return 1;
  }
  return 0;
}


----------------------------
inline static BOOL binn_list_add_blob(binn *list, void *ptr, int size)
{
  return binn_list_add(list, 0xC0, ptr, size);
}


----------------------------
inline static BOOL binn_object_set_int16(binn *obj, const char *key, short value)
{
  return binn_object_set(obj, key, 0x41, &value, 0);
}


----------------------------
int binn_type(void *ptr)
{
  binn *item;
  unsigned int item_idx = 0;
  switch (binn_get_ptr_type(ptr))
  {
    case 1:
    {
      item_idx = (binn *) ptr;
      return item->type;
    }

    case 2:
    {
      return binn_buf_type(ptr);
    }

    default:
    {
      return -1;
    }

  }

}


----------------------------
inline static BOOL binn_list_add_int16(binn *list, short value)
{
  return binn_list_add(list, 0x41, &value, 0);
}


----------------------------
inline static BOOL binn_map_set_double(binn *map, int id, double value)
{
  return binn_map_set(map, id, 0x82, &value, 0);
}


----------------------------
binn *binn_map()
{
  return binn_new(0xE1, 0, 0);
}


----------------------------
inline static BOOL binn_map_set_str(binn *map, int id, char *str)
{
  return binn_map_set(map, id, 0xA0, str, 0);
}


----------------------------
int binn_list_int32(void *list, int pos)
{
  int value;
  binn_list_get(list, pos, 0x61, &value, 0);
  return value;
}


----------------------------
void binn_free(binn *item)
{
  if (item == 0)
  {
    return;
  }
  if (item->writable && (item->pre_allocated == 0))
  {
    free_fn(item->pbuf);
  }
  if (item->freefn)
  {
    item->freefn(item->ptr);
  }
  if (item->allocated)
  {
    free_fn(item);
  }
  else
  {
    memset(item, 0, sizeof(binn));
    item->header = 0x1F22B11F;
  }
}


----------------------------
BOOL vbool
----------------------------
***/


void test_binn2()
{
  char *obj1ptr;
  unsigned int obj1ptr_idx = 0;
  char *obj2ptr;
  unsigned int obj2ptr_idx = 0;
  int obj1size;
  int obj2size;
  test_virtual_types();
  test_int_conversion();
  test_binn_int_conversion();
  test_value_conversion();
  test_value_copy();
  init_udts();
  obj1ptr_idx = test_create_object_1(&obj1size);
  obj2ptr_idx = test_create_object_2(&obj2size);
  assert((&obj1ptr[obj1ptr_idx]) != 0);
  assert((&obj2ptr[obj2ptr_idx]) != 0);
  printf("obj1size=%d obj2size=%d\n", obj1size, obj2size);
  assert(obj1size == obj2size);
  test_binn_read(obj1ptr);
  test_binn_iter(0);
  test_binn_iter(1);
}


/*** DEPENDENCIES:
void test_value_copy()
{
  printf("testing binn value copy... ");
  puts("TODO!!!");
}


----------------------------
void test_int_conversion()
{
  printf("testing integer conversion...");
  vint8 = -110;
  vuint8 = 0;
  assert(copy_int_value(&vint8, &vuint8, 0x21, 0x20) == 0);
  assert(vint8 == (-110));
  assert(vuint8 == 0);
  vint8 = -110;
  vuint16 = 0;
  assert(copy_int_value(&vint8, &vuint16, 0x21, 0x40) == 0);
  assert(vint8 == (-110));
  assert(vuint16 == 0);
  vint8 = -110;
  vuint32 = 0;
  assert(copy_int_value(&vint8, &vuint32, 0x21, 0x60) == 0);
  assert(vint8 == (-110));
  assert(vuint32 == 0);
  vint8 = -110;
  vuint64 = 0;
  assert(copy_int_value(&vint8, &vuint64, 0x21, 0x80) == 0);
  assert(vint8 == (-110));
  assert(vuint64 == 0);
  vint16 = -123;
  vuint8 = 0;
  assert(copy_int_value(&vint16, &vuint8, 0x41, 0x20) == 0);
  assert(vint16 == (-123));
  assert(vuint8 == 0);
  vint16 = -123;
  vuint16 = 0;
  assert(copy_int_value(&vint16, &vuint16, 0x41, 0x40) == 0);
  assert(vint16 == (-123));
  assert(vuint16 == 0);
  vint16 = -32000;
  vuint32 = 0;
  assert(copy_int_value(&vint16, &vuint32, 0x41, 0x60) == 0);
  assert(vint16 == (-32000));
  assert(vuint32 == 0);
  vint16 = -32000;
  vuint64 = 0;
  assert(copy_int_value(&vint16, &vuint64, 0x41, 0x80) == 0);
  assert(vint16 == (-32000));
  assert(vuint64 == 0);
  vint32 = -123;
  vuint8 = 0;
  assert(copy_int_value(&vint32, &vuint8, 0x61, 0x20) == 0);
  assert(vint32 == (-123));
  assert(vuint8 == 0);
  vint32 = -123;
  vuint16 = 0;
  assert(copy_int_value(&vint32, &vuint16, 0x61, 0x40) == 0);
  assert(vint32 == (-123));
  assert(vuint16 == 0);
  vint32 = -123;
  vuint32 = 0;
  assert(copy_int_value(&vint32, &vuint32, 0x61, 0x60) == 0);
  assert(vint32 == (-123));
  assert(vuint32 == 0);
  vint32 = -123;
  vuint64 = 0;
  assert(copy_int_value(&vint32, &vuint64, 0x61, 0x80) == 0);
  assert(vint32 == (-123));
  assert(vuint64 == 0);
  vint64 = -123;
  vuint8 = 0;
  assert(copy_int_value(&vint64, &vuint8, 0x81, 0x20) == 0);
  assert(vint64 == (-123));
  assert(vuint8 == 0);
  vint64 = -123;
  vuint16 = 0;
  assert(copy_int_value(&vint64, &vuint16, 0x81, 0x40) == 0);
  assert(vint64 == (-123));
  assert(vuint16 == 0);
  vint64 = -123;
  vuint32 = 0;
  assert(copy_int_value(&vint64, &vuint32, 0x81, 0x60) == 0);
  assert(vint64 == (-123));
  assert(vuint32 == 0);
  vint64 = -123;
  vuint64 = 0;
  assert(copy_int_value(&vint64, &vuint64, 0x81, 0x80) == 0);
  assert(vint64 == (-123));
  assert(vuint64 == 0);
  vint16 = -32000;
  vint8 = 0;
  assert(copy_int_value(&vint16, &vint8, 0x41, 0x21) == 0);
  assert(vint16 == (-32000));
  assert(vint8 == 0);
  vint32 = -250;
  vint8 = 0;
  assert(copy_int_value(&vint32, &vint8, 0x61, 0x21) == 0);
  assert(vint32 == (-250));
  assert(vint8 == 0);
  vint32 = -35000;
  vint16 = 0;
  assert(copy_int_value(&vint32, &vint16, 0x61, 0x41) == 0);
  assert(vint32 == (-35000));
  assert(vint16 == 0);
  vint64 = -250;
  vint8 = 0;
  assert(copy_int_value(&vint64, &vint8, 0x81, 0x21) == 0);
  assert(vint64 == (-250));
  assert(vint8 == 0);
  vint64 = -35000;
  vint16 = 0;
  assert(copy_int_value(&vint64, &vint16, 0x81, 0x41) == 0);
  assert(vint64 == (-35000));
  assert(vint16 == 0);
  vint64 = -25470000000;
  vint32 = 0;
  assert(copy_int_value(&vint64, &vint32, 0x81, 0x61) == 0);
  assert(vint64 == (-25470000000));
  assert(vint32 == 0);
  vint16 = 250;
  vint8 = 0;
  assert(copy_int_value(&vint16, &vint8, 0x41, 0x21) == 0);
  assert(vint16 == 250);
  assert(vint8 == 0);
  vint32 = 250;
  vint8 = 0;
  assert(copy_int_value(&vint32, &vint8, 0x61, 0x21) == 0);
  assert(vint32 == 250);
  assert(vint8 == 0);
  vint32 = 35000;
  vint16 = 0;
  assert(copy_int_value(&vint32, &vint16, 0x61, 0x41) == 0);
  assert(vint32 == 35000);
  assert(vint16 == 0);
  vint64 = 250;
  vint8 = 0;
  assert(copy_int_value(&vint64, &vint8, 0x81, 0x21) == 0);
  assert(vint64 == 250);
  assert(vint8 == 0);
  vint64 = 35000;
  vint16 = 0;
  assert(copy_int_value(&vint64, &vint16, 0x81, 0x41) == 0);
  assert(vint64 == 35000);
  assert(vint16 == 0);
  vint64 = 25470000000;
  vint32 = 0;
  assert(copy_int_value(&vint64, &vint32, 0x81, 0x61) == 0);
  assert(vint64 == 25470000000);
  assert(vint32 == 0);
  vint16 = 300;
  vuint8 = 0;
  assert(copy_int_value(&vint16, &vuint8, 0x41, 0x20) == 0);
  assert(vint16 == 300);
  assert(vuint8 == 0);
  vint32 = 300;
  vuint8 = 0;
  assert(copy_int_value(&vint32, &vuint8, 0x61, 0x20) == 0);
  assert(vint32 == 300);
  assert(vuint8 == 0);
  vint32 = 70000;
  vuint16 = 0;
  assert(copy_int_value(&vint32, &vuint16, 0x61, 0x40) == 0);
  assert(vint32 == 70000);
  assert(vuint16 == 0);
  vint64 = 300;
  vuint8 = 0;
  assert(copy_int_value(&vint64, &vuint8, 0x81, 0x20) == 0);
  assert(vint64 == 300);
  assert(vuint8 == 0);
  vint64 = 70000;
  vuint16 = 0;
  assert(copy_int_value(&vint64, &vuint16, 0x81, 0x40) == 0);
  assert(vint64 == 70000);
  assert(vuint16 == 0);
  vint64 = 25470000000;
  vuint32 = 0;
  assert(copy_int_value(&vint64, &vuint32, 0x81, 0x60) == 0);
  assert(vint64 == 25470000000);
  assert(vuint32 == 0);
  vint8 = 123;
  vint16 = 0;
  assert(copy_int_value(&vint8, &vint16, 0x21, 0x41) == 1);
  assert(vint8 == 123);
  assert(vint16 == 123);
  vint8 = -110;
  vint16 = 0;
  assert(copy_int_value(&vint8, &vint16, 0x21, 0x41) == 1);
  assert(vint8 == (-110));
  assert(vint16 == (-110));
  vint8 = 123;
  vint32 = 0;
  assert(copy_int_value(&vint8, &vint32, 0x21, 0x61) == 1);
  assert(vint8 == 123);
  assert(vint32 == 123);
  vint8 = -110;
  vint32 = 0;
  assert(copy_int_value(&vint8, &vint32, 0x21, 0x61) == 1);
  assert(vint8 == (-110));
  assert(vint32 == (-110));
  vint8 = 123;
  vint64 = 0;
  assert(copy_int_value(&vint8, &vint64, 0x21, 0x81) == 1);
  assert(vint8 == 123);
  assert(vint64 == 123);
  vint8 = -120;
  vint64 = 0;
  assert(copy_int_value(&vint8, &vint64, 0x21, 0x81) == 1);
  assert(vint8 == (-120));
  assert(vint64 == (-120));
  vint8 = 123;
  vuint16 = 0;
  assert(copy_int_value(&vint8, &vuint16, 0x21, 0x40) == 1);
  assert(vint8 == 123);
  assert(vuint16 == 123);
  vint8 = 123;
  vuint32 = 0;
  assert(copy_int_value(&vint8, &vuint32, 0x21, 0x60) == 1);
  assert(vint8 == 123);
  assert(vuint32 == 123);
  vint8 = 123;
  vuint64 = 0;
  assert(copy_int_value(&vint8, &vuint64, 0x21, 0x80) == 1);
  assert(vint8 == 123);
  assert(vuint64 == 123);
  vuint8 = 123;
  vint16 = 0;
  assert(copy_int_value(&vuint8, &vint16, 0x20, 0x41) == 1);
  assert(vuint8 == 123);
  assert(vint16 == 123);
  vuint8 = 250;
  vint16 = 0;
  assert(copy_int_value(&vuint8, &vint16, 0x20, 0x41) == 1);
  assert(vuint8 == 250);
  assert(vint16 == 250);
  vuint8 = 123;
  vint32 = 0;
  assert(copy_int_value(&vuint8, &vint32, 0x20, 0x61) == 1);
  assert(vuint8 == 123);
  assert(vint32 == 123);
  vuint8 = 250;
  vint32 = 0;
  assert(copy_int_value(&vuint8, &vint32, 0x20, 0x61) == 1);
  assert(vuint8 == 250);
  assert(vint32 == 250);
  vuint8 = 123;
  vint64 = 0;
  assert(copy_int_value(&vuint8, &vint64, 0x20, 0x81) == 1);
  assert(vuint8 == 123);
  assert(vint64 == 123);
  vuint8 = 250;
  vint64 = 0;
  assert(copy_int_value(&vuint8, &vint64, 0x20, 0x81) == 1);
  assert(vuint8 == 250);
  assert(vint64 == 250);
  vuint8 = 123;
  vuint16 = 0;
  assert(copy_int_value(&vuint8, &vuint16, 0x20, 0x40) == 1);
  assert(vuint8 == 123);
  assert(vuint16 == 123);
  vuint8 = 250;
  vuint16 = 0;
  assert(copy_int_value(&vuint8, &vuint16, 0x20, 0x40) == 1);
  assert(vuint8 == 250);
  assert(vuint16 == 250);
  vuint8 = 123;
  vuint32 = 0;
  assert(copy_int_value(&vuint8, &vuint32, 0x20, 0x60) == 1);
  assert(vuint8 == 123);
  assert(vuint32 == 123);
  vuint8 = 250;
  vuint32 = 0;
  assert(copy_int_value(&vuint8, &vuint32, 0x20, 0x60) == 1);
  assert(vuint8 == 250);
  assert(vuint32 == 250);
  vuint8 = 123;
  vuint64 = 0;
  assert(copy_int_value(&vuint8, &vuint64, 0x20, 0x80) == 1);
  assert(vuint8 == 123);
  assert(vuint64 == 123);
  vuint8 = 250;
  vuint64 = 0;
  assert(copy_int_value(&vuint8, &vuint64, 0x20, 0x80) == 1);
  assert(vuint8 == 250);
  assert(vuint64 == 250);
  vint16 = 250;
  vuint8 = 0;
  assert(copy_int_value(&vint16, &vuint8, 0x41, 0x20) == 1);
  assert(vint16 == 250);
  assert(vuint8 == 250);
  vint32 = 250;
  vuint8 = 0;
  assert(copy_int_value(&vint32, &vuint8, 0x61, 0x20) == 1);
  assert(vint32 == 250);
  assert(vuint8 == 250);
  vint32 = 35000;
  vuint16 = 0;
  assert(copy_int_value(&vint32, &vuint16, 0x61, 0x40) == 1);
  assert(vint32 == 35000);
  assert(vuint16 == 35000);
  vint64 = 250;
  vuint8 = 0;
  assert(copy_int_value(&vint64, &vuint8, 0x81, 0x20) == 1);
  assert(vint64 == 250);
  assert(vuint8 == 250);
  vint64 = 35000;
  vuint16 = 0;
  assert(copy_int_value(&vint64, &vuint16, 0x81, 0x40) == 1);
  assert(vint64 == 35000);
  assert(vuint16 == 35000);
  vint64 = 2147000000;
  vuint32 = 0;
  assert(copy_int_value(&vint64, &vuint32, 0x81, 0x60) == 1);
  assert(vint64 == 2147000000);
  assert(vuint32 == 2147000000);
  vint8 = -110;
  vint16 = 0;
  assert(copy_int_value(&vint8, &vint16, 0x21, 0x41) == 1);
  assert(vint8 == (-110));
  assert(vint16 == (-110));
  vint8 = -110;
  vint32 = 0;
  assert(copy_int_value(&vint8, &vint32, 0x21, 0x61) == 1);
  assert(vint8 == (-110));
  assert(vint32 == (-110));
  vint8 = -110;
  vint64 = 0;
  assert(copy_int_value(&vint8, &vint64, 0x21, 0x81) == 1);
  assert(vint8 == (-110));
  assert(vint64 == (-110));
  vint16 = -123;
  vint8 = 0;
  assert(copy_int_value(&vint16, &vint8, 0x41, 0x21) == 1);
  assert(vint16 == (-123));
  assert(vint8 == (-123));
  vint16 = -32000;
  vint32 = 0;
  assert(copy_int_value(&vint16, &vint32, 0x41, 0x61) == 1);
  assert(vint16 == (-32000));
  assert(vint32 == (-32000));
  vint16 = -32000;
  vint64 = 0;
  assert(copy_int_value(&vint16, &vint64, 0x41, 0x81) == 1);
  assert(vint16 == (-32000));
  assert(vint64 == (-32000));
  vint32 = -123;
  vint8 = 0;
  assert(copy_int_value(&vint32, &vint8, 0x61, 0x21) == 1);
  assert(vint32 == (-123));
  assert(vint8 == (-123));
  vint32 = -123;
  vint16 = 0;
  assert(copy_int_value(&vint32, &vint16, 0x61, 0x41) == 1);
  assert(vint32 == (-123));
  assert(vint16 == (-123));
  vint32 = -32000;
  vint16 = 0;
  assert(copy_int_value(&vint32, &vint16, 0x61, 0x41) == 1);
  assert(vint32 == (-32000));
  assert(vint16 == (-32000));
  vint32 = -123;
  vint64 = 0;
  assert(copy_int_value(&vint32, &vint64, 0x61, 0x81) == 1);
  assert(vint32 == (-123));
  assert(vint64 == (-123));
  vint32 = -2147000000;
  vint64 = 0;
  assert(copy_int_value(&vint32, &vint64, 0x61, 0x81) == 1);
  assert(vint32 == (-2147000000));
  assert(vint64 == (-2147000000));
  vint64 = -123;
  vint8 = 0;
  assert(copy_int_value(&vint64, &vint8, 0x81, 0x21) == 1);
  assert(vint64 == (-123));
  assert(vint8 == (-123));
  vint64 = -250;
  vint16 = 0;
  assert(copy_int_value(&vint64, &vint16, 0x81, 0x41) == 1);
  assert(vint64 == (-250));
  assert(vint16 == (-250));
  vint64 = -35000;
  vint32 = 0;
  assert(copy_int_value(&vint64, &vint32, 0x81, 0x61) == 1);
  assert(vint64 == (-35000));
  assert(vint32 == (-35000));
  puts("OK");
}


----------------------------
void test_binn_read(void *objptr)
{
  void *listptr;
  unsigned int listptr_idx = 0;
  char *ptr;
  unsigned int ptr_idx = 0;
  binn value = {0};
  printf("OK\nreading:\n");
  vint32 = 0;
  assert(binn_object_get(objptr, "int32", 0x61, &vint32, 0) == 1);
  printf("int32: %d\n", vint32);
  assert(vint32 == (-12345));
  vint16 = 0;
  assert(binn_object_get(objptr, "int16", 0x41, &vint16, 0) == 1);
  printf("int16: %d\n", vint16);
  assert(vint16 == (-258));
  vint8 = 0;
  assert(binn_object_get(objptr, "int8", 0x21, &vint8, 0) == 1);
  printf("int8: %d\n", vint8);
  assert(vint8 == (-120));
  vint64 = 0;
  assert(binn_object_get(objptr, "int64", 0x81, &vint64, 0) == 1);
  printf("int64: %lli\n", vint64);
  assert(vint64 == (-1234567890123));
  vuint32 = 0;
  assert(binn_object_get(objptr, "uint32", 0x60, &vuint32, 0) == 1);
  printf("uint32: %d\n", vuint32);
  assert(vuint32 == 123456);
  vuint16 = 0;
  assert(binn_object_get(objptr, "uint16", 0x40, &vuint16, 0) == 1);
  printf("uint16: %d\n", vuint16);
  assert(vuint16 == 60500);
  vuint8 = 0;
  assert(binn_object_get(objptr, "uint8", 0x20, &vuint8, 0) == 1);
  printf("uint8: %d\n", vuint8);
  assert(vuint8 == 250);
  vuint64 = 0;
  assert(binn_object_get(objptr, "uint64", 0x80, &vuint64, 0) == 1);
  printf("uint64: %llu\n", vuint64);
  assert(vuint64 == 1234567890123);
  vfloat32 = 0;
  assert(binn_object_get(objptr, "float32", 0x62, &vfloat32, 0) == 1);
  printf("float32: %f\n", vfloat32);
  assert(AlmostEqualFloats(vfloat32, -12.345, 2) == 1);
  vfloat64 = 0;
  assert(binn_object_get(objptr, "float64", 0x82, &vfloat64, 0) == 1);
  printf("float64: %f\n", vfloat64);
  assert((vfloat64 - (-123456.7895)) < 0.01);
  vfloat32 = 0;
  assert(binn_object_get(objptr, "single", 0x62, &vfloat32, 0) == 1);
  printf("single: %f\n", vfloat32);
  assert(AlmostEqualFloats(vfloat32, -12.345, 2) == 1);
  vfloat64 = 0;
  assert(binn_object_get(objptr, "double", 0x82, &vfloat64, 0) == 1);
  printf("double: %f\n", vfloat64);
  assert((vfloat64 - (-123456.7895)) < 0.01);
  ptr_idx = 0;
  assert(binn_object_get(objptr, "str", 0xA0, &(&ptr[ptr_idx]), 0) == 1);
  printf("ptr: (%p) '%s'\n", ptr, ptr);
  assert(strcmp(ptr, "the value") == 0);
  vint32 = 999;
  assert(binn_object_get(objptr, "bool_true", 0x80061, &vint32, 0) == 1);
  printf("bool true: %d\n", vint32);
  assert(vint32 == 1);
  vint32 = 999;
  assert(binn_object_get(objptr, "bool_false", 0x80061, &vint32, 0) == 1);
  printf("bool false: %d\n", vint32);
  assert(vint32 == 0);
  vint32 = 999;
  assert(binn_object_get(objptr, "null", 0x00, &vint32, 0) == 1);
  printf("null: %d\n", vint32);
  assert(binn_object_get(objptr, "null", 0x00, 0, 0) == 1);
  assert(binn_object_get(objptr, "list", 0xE0, &(&listptr[listptr_idx]), 0) == 1);
  printf("obj ptr: %p  list ptr: %p\n", objptr, listptr);
  assert((&listptr[listptr_idx]) != 0);
  assert((&listptr[listptr_idx]) > objptr);
  vint32 = 0;
  assert(binn_list_get(listptr, 2, 0x61, &vint32, 0) == 1);
  printf("int32: %d\n", vint32);
  assert(vint32 == 123);
  ptr_idx = 0;
  assert(binn_list_get(listptr, 3, 0xA0, &(&ptr[ptr_idx]), 0) == 1);
  printf("ptr: (%p) '%s'\n", ptr, ptr);
  assert(strcmp(ptr, "this is a string") == 0);
  vint32 = 0;
  assert(binn_object_get_int32(objptr, "int32", &vint32) == 1);
  printf("int32: %d\n", vint32);
  assert(vint32 == (-12345));
  vint16 = 0;
  assert(binn_object_get_int16(objptr, "int16", &vint16) == 1);
  printf("int16: %d\n", vint16);
  assert(vint16 == (-258));
  vint8 = 0;
  assert(binn_object_get_int8(objptr, "int8", &vint8) == 1);
  printf("int8: %d\n", vint8);
  assert(vint8 == (-120));
  vint64 = 0;
  assert(binn_object_get_int64(objptr, "int64", &vint64) == 1);
  printf("int64: %lli\n", vint64);
  assert(vint64 == (-1234567890123));
  vuint32 = 0;
  assert(binn_object_get_uint32(objptr, "uint32", &vuint32) == 1);
  printf("uint32: %d\n", vuint32);
  assert(vuint32 == 123456);
  vuint16 = 0;
  assert(binn_object_get_uint16(objptr, "uint16", &vuint16) == 1);
  printf("uint16: %d\n", vuint16);
  assert(vuint16 == 60500);
  vuint8 = 0;
  assert(binn_object_get_uint8(objptr, "uint8", &vuint8) == 1);
  printf("uint8: %d\n", vuint8);
  assert(vuint8 == 250);
  vuint64 = 0;
  assert(binn_object_get_uint64(objptr, "uint64", &vuint64) == 1);
  printf("uint64: %llu\n", vuint64);
  assert(vuint64 == 1234567890123);
  vfloat32 = 0;
  assert(binn_object_get_float(objptr, "float32", &vfloat32) == 1);
  printf("float32: %f\n", vfloat32);
  assert(AlmostEqualFloats(vfloat32, -12.345, 2) == 1);
  vfloat64 = 0;
  assert(binn_object_get_double(objptr, "float64", &vfloat64) == 1);
  printf("float64: %f\n", vfloat64);
  assert(AlmostEqualFloats(vfloat32, -12.345, 2) == 1);
  ptr_idx = 0;
  assert(binn_object_get_str(objptr, "str", &(&ptr[ptr_idx])) == 1);
  printf("ptr: (%p) '%s'\n", ptr, ptr);
  assert(strcmp(ptr, "the value") == 0);
  vint32 = 999;
  assert(binn_object_get_bool(objptr, "bool_true", &vint32) == 1);
  printf("bool true: %d\n", vint32);
  assert(vint32 == 1);
  vint32 = 999;
  assert(binn_object_get_bool(objptr, "bool_false", &vint32) == 1);
  printf("bool false: %d\n", vint32);
  assert(vint32 == 0);
  vbool = 0;
  assert(binn_object_null(objptr, "null") == 1);
  assert(binn_object_null(objptr, "bool_true") == 0);
  assert(binn_object_get_list(objptr, "list", &(&listptr[listptr_idx])) == 1);
  printf("obj ptr: %p  list ptr: %p\n", objptr, listptr);
  assert((&listptr[listptr_idx]) != 0);
  assert((&listptr[listptr_idx]) > objptr);
  vint32 = 0;
  assert(binn_list_get_int32(listptr, 2, &vint32) == 1);
  printf("int32: %d\n", vint32);
  assert(vint32 == 123);
  ptr_idx = 0;
  assert(binn_list_get_str(listptr, 3, &(&ptr[ptr_idx])) == 1);
  printf("ptr: (%p) '%s'\n", ptr, ptr);
  assert(strcmp(ptr, "this is a string") == 0);
  vint32 = binn_object_int32(objptr, "int32");
  printf("int32: %d\n", vint32);
  assert(vint32 == (-12345));
  vint16 = binn_object_int16(objptr, "int16");
  printf("int16: %d\n", vint16);
  assert(vint16 == (-258));
  vint8 = binn_object_int8(objptr, "int8");
  printf("int8: %d\n", vint8);
  assert(vint8 == (-120));
  vint64 = binn_object_int64(objptr, "int64");
  printf("int64: %lli\n", vint64);
  assert(vint64 == (-1234567890123));
  vuint32 = binn_object_uint32(objptr, "uint32");
  printf("uint32: %d\n", vuint32);
  assert(vuint32 == 123456);
  vuint16 = binn_object_uint16(objptr, "uint16");
  printf("uint16: %d\n", vuint16);
  assert(vuint16 == 60500);
  vuint8 = binn_object_uint8(objptr, "uint8");
  printf("uint8: %d\n", vuint8);
  assert(vuint8 == 250);
  vuint64 = binn_object_uint64(objptr, "uint64");
  printf("uint64: %llu\n", vuint64);
  assert(vuint64 == 1234567890123);
  vfloat32 = binn_object_float(objptr, "float32");
  printf("float32: %f\n", vfloat32);
  assert(AlmostEqualFloats(vfloat32, -12.345, 2) == 1);
  vfloat64 = binn_object_double(objptr, "float64");
  printf("float64: %f\n", vfloat64);
  assert(AlmostEqualFloats(vfloat32, -12.345, 2) == 1);
  ptr_idx = binn_object_str(objptr, "str");
  printf("ptr: (%p) '%s'\n", ptr, ptr);
  assert(strcmp(ptr, "the value") == 0);
  vint32 = binn_object_bool(objptr, "bool_true");
  printf("bool true: %d\n", vint32);
  assert(vint32 == 1);
  vint32 = binn_object_bool(objptr, "bool_false");
  printf("bool false: %d\n", vint32);
  assert(vint32 == 0);
  assert(binn_object_null(objptr, "null") == 1);
  assert(binn_object_null(objptr, "nonull") == 0);
  listptr_idx = binn_object_list(objptr, "list");
  printf("obj ptr: %p  list ptr: %p\n", objptr, listptr);
  assert((&listptr[listptr_idx]) != 0);
  assert((&listptr[listptr_idx]) > objptr);
  vint32 = binn_list_int32(listptr, 2);
  printf("int32: %d\n", vint32);
  assert(vint32 == 123);
  ptr_idx = binn_list_str(listptr, 3);
  printf("ptr: (%p) '%s'\n", ptr, ptr);
  assert(strcmp(ptr, "this is a string") == 0);
  assert(binn_object_get_value(objptr, "int32", &value) == 1);
  assert(value.type == 0x41);
  assert(value.vint16 == (-12345));
  assert(binn_object_get_value(objptr, "int16", &value) == 1);
  assert(value.type == 0x41);
  assert(value.vint16 == (-258));
  assert(binn_object_get_value(objptr, "int8", &value) == 1);
  assert(value.type == 0x21);
  assert(value.vint8 == (-120));
  assert(binn_object_get_value(objptr, "int64", &value) == 1);
  assert(value.type == 0x81);
  assert(value.vint64 == (-1234567890123));
  assert(binn_object_get_value(objptr, "uint32", &value) == 1);
  assert(value.type == 0x60);
  assert(value.vuint32 == 123456);
  assert(binn_object_get_value(objptr, "uint16", &value) == 1);
  assert(value.type == 0x40);
  assert(value.vuint16 == 60500);
  assert(binn_object_get_value(objptr, "uint8", &value) == 1);
  assert(value.type == 0x20);
  assert(value.vuint8 == 250);
  assert(binn_object_get_value(objptr, "uint64", &value) == 1);
  assert(value.type == 0x80);
  assert(value.vuint64 == 1234567890123);
  puts("reading... OK");
}


----------------------------
void test_virtual_types()
{
  binn *list = 0;
  unsigned int list_idx = 0;
  void *ptr;
  unsigned int ptr_idx = 0;
  int storage_type;
  int extra_type;
  BOOL value;
  printf("testing binn virtual types... ");
  assert(binn_get_type_info(0x80061, &storage_type, &extra_type) == 1);
  assert(storage_type == 0x60);
  assert(extra_type == 1);
  list_idx = binn_list();
  assert((&list[list_idx]) != 0);
  assert(binn_list_add_bool(list, 1) == 1);
  assert(binn_list_add_bool(list, 0) == 1);
  assert(binn_list_add_null(list) == 1);
  ptr_idx = binn_ptr(list);
  assert((&ptr[ptr_idx]) != 0);
  assert(binn_list_get_bool(ptr, 1, &value) == 1);
  assert(value == 1);
  assert(binn_list_get_bool(ptr, 2, &value) == 1);
  assert(value == 0);
  assert(binn_list_null(ptr, 3) == 1);
  assert(binn_list_null(ptr, 1) == 0);
  assert(binn_list_null(ptr, 2) == 0);
  assert(binn_list_get_bool(ptr, 3, &value) == 0);
  binn_free(list);
  puts("OK");
}


----------------------------
char *test_create_object_2(int *psize)
{
  binn *obj = 0;
  unsigned int obj_idx = 0;
  binn *list = 0;
  unsigned int list_idx = 0;
  printf("creating object 2...\n");
  obj_idx = binn_object();
  assert((&obj[obj_idx]) != 0);
  assert(binn_object_set_int32(obj, "int32", -12345) == 1);
  assert(binn_object_set_int16(obj, "int16", -258) == 1);
  assert(binn_object_set_int8(obj, "int8", -120) == 1);
  assert(binn_object_set_int64(obj, "int64", -1234567890123) == 1);
  assert(binn_object_set_uint32(obj, "uint32", 123456) == 1);
  assert(binn_object_set_int16(obj, "uint16", 60500) == 1);
  assert(binn_object_set_int8(obj, "uint8", 250) == 1);
  assert(binn_object_set_uint64(obj, "uint64", 1234567890123) == 1);
  assert(binn_object_set_float(obj, "float32", -12.345) == 1);
  vfloat32 = -12.345;
  assert(binn_object_set(obj, "single", 0x62, &vfloat32, 0) == 1);
  assert(binn_object_set_double(obj, "float64", -123456.7895) == 1);
  vfloat64 = -123456.7895;
  assert(binn_object_set(obj, "double", 0x82, &vfloat64, 0) == 1);
  assert(binn_object_set_str(obj, "str", "the value") == 1);
  assert(binn_object_set_bool(obj, "bool_true", 1) == 1);
  assert(binn_object_set_bool(obj, "bool_false", 0) == 1);
  assert(binn_object_set_null(obj, "null") == 1);
  list_idx = binn_list();
  assert((&list[list_idx]) != 0);
  assert(binn_list_add_null(list) == 1);
  assert(binn_list_add_int32(list, 123) == 1);
  assert(binn_list_add_str(list, "this is a string") == 1);
  assert(binn_object_set_list(obj, "list", list) == 1);
  binn_free(list);
  list_idx = 0;
  *psize = binn_size(obj);
  return (char *) binn_ptr(obj);
}


----------------------------
void init_udts()
{
  binn *obj = 0;
  unsigned int obj_idx = 0;
  unsigned short date;
  uint64 value;
  void *ptr;
  unsigned int ptr_idx = 0;
  puts("testing UDTs...");
  assert(strcmp(date_to_str(str_to_date("1950-08-15")), "1950-08-15") == 0);
  assert(strcmp(date_to_str(str_to_date("1900-12-01")), "1900-12-01") == 0);
  assert(strcmp(date_to_str(str_to_date("2000-10-31")), "2000-10-31") == 0);
  assert(strcmp(date_to_str(str_to_date("2014-03-19")), "2014-03-19") == 0);
  printf("curr=%s\n", currency_to_str(str_to_currency("123.456")));
  printf("curr=%s\n", currency_to_str(str_to_currency("123.45")));
  printf("curr=%s\n", currency_to_str(str_to_currency("123.4")));
  printf("curr=%s\n", currency_to_str(str_to_currency("123.")));
  printf("curr=%s\n", currency_to_str(str_to_currency("123")));
  printf("curr=%s\n", currency_to_str(str_to_currency("1.2")));
  printf("curr=%s\n", currency_to_str(str_to_currency("0.987")));
  printf("curr=%s\n", currency_to_str(str_to_currency("0.98")));
  printf("curr=%s\n", currency_to_str(str_to_currency("0.9")));
  printf("curr=%s\n", currency_to_str(str_to_currency("0.0")));
  printf("curr=%s\n", currency_to_str(str_to_currency("0")));
  printf("curr=%s\n", currency_to_str(str_to_currency("123.4567")));
  printf("curr=%s\n", currency_to_str(str_to_currency("123.45678")));
  printf("curr=%s\n", currency_to_str(str_to_currency("123.456789")));
  printf("curr=%s\n", currency_to_str(str_to_currency("0.1234")));
  printf("curr=%s\n", currency_to_str(str_to_currency(".1234")));
  assert(float_to_currency(2.5) == 25000);
  assert(float_to_currency(5) == 50000);
  assert(str_to_currency("1.1") == 11000);
  assert(str_to_currency("12") == 120000);
  assert(mul_currency(20000, 20000) == 40000);
  assert(mul_currency(20000, 25000) == 50000);
  assert(mul_currency(30000, 40000) == 120000);
  assert(div_currency(80000, 20000) == 40000);
  assert(div_currency(120000, 40000) == 30000);
  assert(div_currency(100000, 40000) == 25000);
  printf("1.1 * 2.5 = %s\n", currency_to_str(mul_currency(str_to_currency("1.1"), float_to_currency(2.5))));
  printf("12 / 5 = %s\n", currency_to_str(div_currency(str_to_currency("12"), float_to_currency(5))));
  MY_DATE = binn_create_type(0x40, 0x0a);
  MY_CURRENCY = binn_create_type(0x80, 0x0a);
  obj_idx = binn_object();
  assert((&obj[obj_idx]) != 0);
  date = str_to_date("1950-08-15");
  printf(" date 1: %d %s\n", date, date_to_str(date));
  assert(binn_object_set(obj, "date1", MY_DATE, &date, 0) == 1);
  assert(binn_object_set(obj, "date1", MY_DATE, &date, 0) == 0);
  date = str_to_date("1999-12-31");
  printf(" date 2: %d %s\n", date, date_to_str(date));
  binn_object_set(obj, "date2", MY_DATE, &date, 0);
  value = str_to_currency("123.456");
  printf(" curr 1: %llu %s\n", value, currency_to_str(value));
  binn_object_set(obj, "curr1", MY_CURRENCY, &value, 0);
  value = str_to_currency("123.45");
  printf(" curr 2: %llu %s\n", value, currency_to_str(value));
  binn_object_set(obj, "curr2", MY_CURRENCY, &value, 0);
  value = str_to_currency("12.5");
  printf(" curr 3: %llu %s\n", value, currency_to_str(value));
  binn_object_set(obj, "curr3", MY_CURRENCY, &value, 0);
  value = str_to_currency("5");
  printf(" curr 4: %llu %s\n", value, currency_to_str(value));
  binn_object_set(obj, "curr4", MY_CURRENCY, &value, 0);
  value = str_to_currency("0.75");
  printf(" curr 5: %llu %s\n", value, currency_to_str(value));
  binn_object_set(obj, "curr5", MY_CURRENCY, &value, 0);
  ptr_idx = binn_ptr(obj);
  assert(binn_object_get(ptr, "date1", MY_DATE, &date, 0) == 1);
  printf(" date 1: %d %s\n", date, date_to_str(date));
  assert(binn_object_get(ptr, "date2", MY_DATE, &date, 0) == 1);
  printf(" date 2: %d %s\n", date, date_to_str(date));
  assert(binn_object_get(ptr, "curr1", MY_CURRENCY, &value, 0) == 1);
  printf(" curr 1: %llu %s\n", value, currency_to_str(value));
  assert(binn_object_get(ptr, "curr2", MY_CURRENCY, &value, 0) == 1);
  printf(" curr 2: %llu %s\n", value, currency_to_str(value));
  assert(binn_object_get(ptr, "curr3", MY_CURRENCY, &value, 0) == 1);
  printf(" curr 3: %llu %s\n", value, currency_to_str(value));
  assert(binn_object_get(ptr, "curr4", MY_CURRENCY, &value, 0) == 1);
  printf(" curr 4: %llu %s\n", value, currency_to_str(value));
  assert(binn_object_get(ptr, "curr5", MY_CURRENCY, &value, 0) == 1);
  printf(" curr 5: %llu %s\n", value, currency_to_str(value));
  binn_free(obj);
  puts("testing UDTs... OK");
}


----------------------------
void test_value_conversion()
{
  binn *value;
  unsigned int value_idx = 0;
  char *ptr;
  unsigned int ptr_idx = 0;
  char blob[64] = "test blob";
  void *pblob;
  unsigned int pblob_idx = 0;
  int size;
  int vint32;
  int64 vint64;
  double vdouble;
  BOOL vbool;
  printf("testing binn value conversion... ");
  ptr_idx = "static string";
  value_idx = binn_string(ptr, (binn_mem_free) 0);
  assert((&value[value_idx]) != 0);
  assert(value->type == 0xA0);
  assert(value->ptr != 0);
  assert(value->ptr == (&ptr[ptr_idx]));
  assert(value->freefn == 0);
  binn_free(value);
  ptr_idx = "transient string";
  value_idx = binn_string(ptr, (binn_mem_free) (-1));
  assert((&value[value_idx]) != 0);
  assert(value->type == 0xA0);
  assert(value->ptr != 0);
  assert(value->ptr != (&ptr[ptr_idx]));
  assert(strcmp((char *) value->ptr, ptr) == 0);
  assert(value->freefn != 0);
  binn_free(value);
  ptr_idx = strdup("dynamic allocated string");
  value_idx = binn_string(ptr, free);
  assert((&value[value_idx]) != 0);
  assert(value->type == 0xA0);
  assert(value->ptr != 0);
  assert(value->ptr == (&ptr[ptr_idx]));
  assert(value->freefn != 0);
  assert(value->freefn == (&free));
  binn_free(value);
  size = 64;
  pblob_idx = blob;
  value_idx = binn_blob(pblob, size, (binn_mem_free) 0);
  assert((&value[value_idx]) != 0);
  assert(value->type == 0xC0);
  assert(value->ptr != 0);
  assert(value->ptr == (&pblob[pblob_idx]));
  assert(value->freefn == 0);
  binn_free(value);
  size = 64;
  pblob_idx = blob;
  value_idx = binn_blob(pblob, size, (binn_mem_free) (-1));
  assert((&value[value_idx]) != 0);
  assert(value->type == 0xC0);
  assert(value->ptr != 0);
  assert(value->ptr != (&pblob[pblob_idx]));
  assert(memcmp(value->ptr, pblob, size) == 0);
  assert(value->freefn != 0);
  binn_free(value);
  size = 64;
  pblob_idx = memdup(blob, size);
  value_idx = binn_blob(pblob, size, free);
  assert((&value[value_idx]) != 0);
  assert(value->type == 0xC0);
  assert(value->ptr != 0);
  assert(value->ptr == (&pblob[pblob_idx]));
  assert(value->freefn == (&free));
  binn_free(value);
  ptr_idx = "123";
  value_idx = binn_string(ptr, (binn_mem_free) 0);
  assert((&value[value_idx]) != 0);
  assert(value->type == 0xA0);
  assert(value->ptr != 0);
  assert(value->ptr == (&ptr[ptr_idx]));
  assert(value->freefn == 0);
  assert(binn_get_str(value) == (&ptr[ptr_idx]));
  assert(binn_get_int32(value, &vint32) == 1);
  assert(vint32 == 123);
  assert(binn_get_int64(value, &vint64) == 1);
  assert(vint64 == 123);
  assert(binn_get_double(value, &vdouble) == 1);
  assert(AlmostEqualFloats(vdouble, 123, 4) == 1);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 1);
  assert(value->type == 0xA0);
  assert(value->ptr != 0);
  assert(value->ptr == (&ptr[ptr_idx]));
  assert(value->freefn == 0);
  binn_free(value);
  ptr_idx = "-456";
  value_idx = binn_string(ptr, (binn_mem_free) 0);
  assert((&value[value_idx]) != 0);
  assert(value->type == 0xA0);
  assert(value->ptr != 0);
  assert(value->ptr == (&ptr[ptr_idx]));
  assert(value->freefn == 0);
  assert(binn_get_str(value) == (&ptr[ptr_idx]));
  assert(binn_get_int32(value, &vint32) == 1);
  assert(vint32 == (-456));
  assert(binn_get_int64(value, &vint64) == 1);
  assert(vint64 == (-456));
  assert(binn_get_double(value, &vdouble) == 1);
  assert(AlmostEqualFloats(vdouble, -456, 4) == 1);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 1);
  assert(value->type == 0xA0);
  assert(value->ptr != 0);
  assert(value->ptr == (&ptr[ptr_idx]));
  assert(value->freefn == 0);
  binn_free(value);
  ptr_idx = "-4.56";
  value_idx = binn_string(ptr, (binn_mem_free) 0);
  assert((&value[value_idx]) != 0);
  assert(value->type == 0xA0);
  assert(value->ptr != 0);
  assert(value->ptr == (&ptr[ptr_idx]));
  assert(value->freefn == 0);
  assert(binn_get_str(value) == (&ptr[ptr_idx]));
  assert(binn_get_int32(value, &vint32) == 1);
  assert(vint32 == (-4));
  assert(binn_get_int64(value, &vint64) == 1);
  assert(vint64 == (-4));
  assert(binn_get_double(value, &vdouble) == 1);
  assert(AlmostEqualFloats(vdouble, -4.56, 4) == 1);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 1);
  assert(value->type == 0xA0);
  assert(value->ptr != 0);
  assert(value->ptr == (&ptr[ptr_idx]));
  assert(value->freefn == 0);
  binn_free(value);
  ptr_idx = "yes";
  value_idx = binn_string(ptr, (binn_mem_free) 0);
  assert((&value[value_idx]) != 0);
  assert(binn_get_str(value) == (&ptr[ptr_idx]));
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 1);
  binn_free(value);
  ptr_idx = "no";
  value_idx = binn_string(ptr, (binn_mem_free) 0);
  assert((&value[value_idx]) != 0);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 0);
  binn_free(value);
  ptr_idx = "on";
  value_idx = binn_string(ptr, (binn_mem_free) 0);
  assert((&value[value_idx]) != 0);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 1);
  binn_free(value);
  ptr_idx = "off";
  value_idx = binn_string(ptr, (binn_mem_free) 0);
  assert((&value[value_idx]) != 0);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 0);
  binn_free(value);
  ptr_idx = "true";
  value_idx = binn_string(ptr, (binn_mem_free) 0);
  assert((&value[value_idx]) != 0);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 1);
  binn_free(value);
  ptr_idx = "false";
  value_idx = binn_string(ptr, (binn_mem_free) 0);
  assert((&value[value_idx]) != 0);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 0);
  binn_free(value);
  ptr_idx = "1";
  value_idx = binn_string(ptr, (binn_mem_free) 0);
  assert((&value[value_idx]) != 0);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 1);
  binn_free(value);
  ptr_idx = "0";
  value_idx = binn_string(ptr, (binn_mem_free) 0);
  assert((&value[value_idx]) != 0);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 0);
  binn_free(value);
  value_idx = binn_int32(-345);
  assert((&value[value_idx]) != 0);
  assert(value->type == 0x61);
  assert(value->vint32 == (-345));
  assert(value->freefn == 0);
  assert(binn_get_int32(value, &vint32) == 1);
  assert(vint32 == (-345));
  assert(binn_get_int64(value, &vint64) == 1);
  assert(vint64 == (-345));
  assert(binn_get_double(value, &vdouble) == 1);
  assert(AlmostEqualFloats(vdouble, -345, 4) == 1);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 1);
  assert(value->type == 0x61);
  assert(value->vint32 == (-345));
  assert(value->freefn == 0);
  ptr_idx = binn_get_str(value);
  assert((&ptr[ptr_idx]) != 0);
  assert(strcmp(ptr, "-345") == 0);
  assert(value->type == 0xA0);
  assert(value->ptr != 0);
  assert(value->ptr == (&ptr[ptr_idx]));
  assert(value->freefn != 0);
  binn_free(value);
  value_idx = binn_int32(0);
  assert((&value[value_idx]) != 0);
  assert(value->type == 0x61);
  assert(value->vint32 == 0);
  assert(value->freefn == 0);
  assert(binn_get_int32(value, &vint32) == 1);
  assert(vint32 == 0);
  assert(binn_get_int64(value, &vint64) == 1);
  assert(vint64 == 0);
  assert(binn_get_double(value, &vdouble) == 1);
  assert(AlmostEqualFloats(vdouble, 0, 4) == 1);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 0);
  assert(value->type == 0x61);
  assert(value->vint32 == 0);
  assert(value->freefn == 0);
  ptr_idx = binn_get_str(value);
  assert((&ptr[ptr_idx]) != 0);
  assert(strcmp(ptr, "0") == 0);
  assert(value->type == 0xA0);
  assert(value->ptr != 0);
  assert(value->ptr == (&ptr[ptr_idx]));
  assert(value->freefn != 0);
  binn_free(value);
  value_idx = binn_int64(-345678);
  assert((&value[value_idx]) != 0);
  assert(value->type == 0x81);
  assert(value->vint64 == (-345678));
  assert(value->freefn == 0);
  assert(binn_get_int32(value, &vint32) == 1);
  assert(vint32 == (-345678));
  assert(binn_get_int64(value, &vint64) == 1);
  assert(vint64 == (-345678));
  assert(binn_get_double(value, &vdouble) == 1);
  assert(AlmostEqualFloats(vdouble, -345678, 4) == 1);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 1);
  assert(value->type == 0x81);
  assert(value->vint64 == (-345678));
  assert(value->freefn == 0);
  ptr_idx = binn_get_str(value);
  assert((&ptr[ptr_idx]) != 0);
  assert(strcmp(ptr, "-345678") == 0);
  assert(value->type == 0xA0);
  assert(value->ptr != 0);
  assert(value->ptr == (&ptr[ptr_idx]));
  assert(value->freefn != 0);
  binn_free(value);
  value_idx = binn_double(-345.678);
  assert((&value[value_idx]) != 0);
  assert(value->type == 0x82);
  assert(value->vdouble == (-345.678));
  assert(value->freefn == 0);
  assert(binn_get_int32(value, &vint32) == 1);
  assert(vint32 == (-345));
  assert(binn_get_int64(value, &vint64) == 1);
  assert(vint64 == (-345));
  assert(binn_get_double(value, &vdouble) == 1);
  assert(AlmostEqualFloats(vdouble, -345.678, 4) == 1);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 1);
  assert(value->type == 0x82);
  assert(value->vdouble == (-345.678));
  assert(value->freefn == 0);
  ptr_idx = binn_get_str(value);
  assert((&ptr[ptr_idx]) != 0);
  assert(strcmp(ptr, "-345.678") == 0);
  assert(value->type == 0xA0);
  assert(value->ptr != 0);
  assert(value->ptr == (&ptr[ptr_idx]));
  assert(value->freefn != 0);
  binn_free(value);
  value_idx = binn_double(0.0);
  assert((&value[value_idx]) != 0);
  assert(value->type == 0x82);
  assert(value->vdouble == 0.0);
  assert(value->freefn == 0);
  assert(binn_get_int32(value, &vint32) == 1);
  assert(vint32 == 0);
  assert(binn_get_int64(value, &vint64) == 1);
  assert(vint64 == 0);
  assert(binn_get_double(value, &vdouble) == 1);
  assert(AlmostEqualFloats(vdouble, 0, 4) == 1);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 0);
  assert(value->type == 0x82);
  assert(value->vdouble == 0.0);
  assert(value->freefn == 0);
  ptr_idx = binn_get_str(value);
  assert((&ptr[ptr_idx]) != 0);
  assert(strcmp(ptr, "0") == 0);
  assert(value->type == 0xA0);
  assert(value->ptr != 0);
  assert(value->ptr == (&ptr[ptr_idx]));
  assert(value->freefn != 0);
  binn_free(value);
  value_idx = binn_bool(0);
  assert((&value[value_idx]) != 0);
  assert(value->type == 0x80061);
  assert(value->vbool == 0);
  assert(value->freefn == 0);
  assert(binn_get_int32(value, &vint32) == 1);
  assert(vint32 == 0);
  assert(binn_get_int64(value, &vint64) == 1);
  assert(vint64 == 0);
  assert(binn_get_double(value, &vdouble) == 1);
  assert(AlmostEqualFloats(vdouble, 0, 4) == 1);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 0);
  assert(value->type == 0x80061);
  assert(value->vbool == 0);
  assert(value->freefn == 0);
  ptr_idx = binn_get_str(value);
  assert((&ptr[ptr_idx]) != 0);
  assert(strcmp(ptr, "false") == 0);
  assert(value->type == 0xA0);
  assert(value->ptr != 0);
  assert(value->ptr == (&ptr[ptr_idx]));
  assert(value->freefn != 0);
  binn_free(value);
  value_idx = binn_bool(1);
  assert((&value[value_idx]) != 0);
  assert(value->type == 0x80061);
  assert(value->vbool == 1);
  assert(value->freefn == 0);
  assert(binn_get_int32(value, &vint32) == 1);
  assert(vint32 == 1);
  assert(binn_get_int64(value, &vint64) == 1);
  assert(vint64 == 1);
  assert(binn_get_double(value, &vdouble) == 1);
  assert(AlmostEqualFloats(vdouble, 1, 4) == 1);
  assert(binn_get_bool(value, &vbool) == 1);
  assert(vbool == 1);
  assert(value->type == 0x80061);
  assert(value->vbool == 1);
  assert(value->freefn == 0);
  ptr_idx = binn_get_str(value);
  assert((&ptr[ptr_idx]) != 0);
  assert(strcmp(ptr, "true") == 0);
  assert(value->type == 0xA0);
  assert(value->ptr != 0);
  assert(value->ptr == (&ptr[ptr_idx]));
  assert(value->freefn != 0);
  binn_free(value);
  puts("OK");
}


----------------------------
void test_binn_int_conversion()
{
  binn *obj = 0;
  unsigned int obj_idx = 0;
  void *ptr;
  unsigned int ptr_idx = 0;
  printf("testing binn integer read conversion... ");
  obj_idx = binn_object();
  assert((&obj[obj_idx]) != 0);
  assert(binn_object_set_int8(obj, "int8", -8) == 1);
  assert(binn_object_set_int16(obj, "int16", -16) == 1);
  assert(binn_object_set_int32(obj, "int32", -32) == 1);
  assert(binn_object_set_int64(obj, "int64", -64) == 1);
  assert(binn_object_set_uint8(obj, "uint8", 111) == 1);
  assert(binn_object_set_uint16(obj, "uint16", 112) == 1);
  assert(binn_object_set_uint32(obj, "uint32", 113) == 1);
  assert(binn_object_set_uint64(obj, "uint64", 114) == 1);
  ptr_idx = binn_ptr(obj);
  assert(binn_object_int8(ptr, "int8") == (-8));
  assert(binn_object_int8(ptr, "int16") == (-16));
  assert(binn_object_int8(ptr, "int32") == (-32));
  assert(binn_object_int8(ptr, "int64") == (-64));
  assert(binn_object_int16(ptr, "int8") == (-8));
  assert(binn_object_int16(ptr, "int16") == (-16));
  assert(binn_object_int16(ptr, "int32") == (-32));
  assert(binn_object_int16(ptr, "int64") == (-64));
  assert(binn_object_int32(ptr, "int8") == (-8));
  assert(binn_object_int32(ptr, "int16") == (-16));
  assert(binn_object_int32(ptr, "int32") == (-32));
  assert(binn_object_int32(ptr, "int64") == (-64));
  assert(binn_object_int64(ptr, "int8") == (-8));
  assert(binn_object_int64(ptr, "int16") == (-16));
  assert(binn_object_int64(ptr, "int32") == (-32));
  assert(binn_object_int64(ptr, "int64") == (-64));
  assert(binn_object_int8(ptr, "uint8") == 111);
  assert(binn_object_int8(ptr, "uint16") == 112);
  assert(binn_object_int8(ptr, "uint32") == 113);
  assert(binn_object_int8(ptr, "uint64") == 114);
  assert(binn_object_int16(ptr, "uint8") == 111);
  assert(binn_object_int16(ptr, "uint16") == 112);
  assert(binn_object_int16(ptr, "uint32") == 113);
  assert(binn_object_int16(ptr, "uint64") == 114);
  assert(binn_object_int32(ptr, "uint8") == 111);
  assert(binn_object_int32(ptr, "uint16") == 112);
  assert(binn_object_int32(ptr, "uint32") == 113);
  assert(binn_object_int32(ptr, "uint64") == 114);
  assert(binn_object_int64(ptr, "uint8") == 111);
  assert(binn_object_int64(ptr, "uint16") == 112);
  assert(binn_object_int64(ptr, "uint32") == 113);
  assert(binn_object_int64(ptr, "uint64") == 114);
  binn_free(obj);
  puts("OK");
}


----------------------------
char *test_create_object_1(int *psize)
{
  binn *obj = 0;
  unsigned int obj_idx = 0;
  binn *list = 0;
  unsigned int list_idx = 0;
  printf("creating object 1...\n");
  obj_idx = binn_object();
  assert((&obj[obj_idx]) != 0);
  vint32 = -12345;
  assert(binn_object_set(obj, "int32", 0x61, &vint32, 0) == 1);
  vint16 = -258;
  assert(binn_object_set(obj, "int16", 0x41, &vint16, 0) == 1);
  vint8 = -120;
  assert(binn_object_set(obj, "int8", 0x21, &vint8, 0) == 1);
  vint64 = -1234567890123;
  assert(binn_object_set(obj, "int64", 0x81, &vint64, 0) == 1);
  vuint32 = 123456;
  assert(binn_object_set(obj, "uint32", 0x60, &vuint32, 0) == 1);
  vuint16 = 60500;
  assert(binn_object_set(obj, "uint16", 0x40, &vuint16, 0) == 1);
  vuint8 = 250;
  assert(binn_object_set(obj, "uint8", 0x20, &vuint8, 0) == 1);
  vuint64 = 1234567890123;
  assert(binn_object_set(obj, "uint64", 0x80, &vuint64, 0) == 1);
  vfloat32 = -12.345;
  assert(binn_object_set(obj, "float32", 0x62, &vfloat32, 0) == 1);
  vfloat32 = -12.345;
  assert(binn_object_set(obj, "single", 0x62, &vfloat32, 0) == 1);
  vfloat64 = -123456.7895;
  assert(binn_object_set(obj, "float64", 0x82, &vfloat64, 0) == 1);
  vfloat64 = -123456.7895;
  assert(binn_object_set(obj, "double", 0x82, &vfloat64, 0) == 1);
  assert(binn_object_set(obj, "str", 0xA0, "the value", 0) == 1);
  vint32 = 1;
  assert(binn_object_set(obj, "bool_true", 0x80061, &vint32, 0) == 1);
  vint32 = 0;
  assert(binn_object_set(obj, "bool_false", 0x80061, &vint32, 0) == 1);
  assert(binn_object_set(obj, "null", 0x00, 0, 0) == 1);
  list_idx = binn_list();
  assert((&list[list_idx]) != 0);
  assert(binn_list_add(list, 0x00, 0, 0) == 1);
  vint32 = 123;
  assert(binn_list_add(list, 0x61, &vint32, 0) == 1);
  assert(binn_list_add(list, 0xA0, "this is a string", 0) == 1);
  assert(binn_object_set(obj, "list", 0xE0, binn_ptr(list), binn_size(list)) == 1);
  binn_free(list);
  list_idx = 0;
  *psize = binn_size(obj);
  return (char *) binn_ptr(obj);
}


----------------------------
void test_binn_iter(BOOL use_int_compression)
{
  binn *list;
  unsigned int list_idx = 0;
  binn *map;
  unsigned int map_idx = 0;
  binn *obj;
  unsigned int obj_idx = 0;
  binn *list2;
  unsigned int list2_idx = 0;
  binn *copy = 0;
  unsigned int copy_idx = 0;
  binn_iter iter;
  binn_iter iter2;
  binn value;
  binn value2;
  int blob_size;
  int id;
  int id2;
  int list2size;
  void *ptr;
  unsigned int ptr_idx = 0;
  void *blob_ptr;
  unsigned int blob_ptr_idx = 0;
  char key[256];
  char key2[256];
  blob_ptr_idx = "key\0value\0\0";
  blob_size = 11;
  printf("testing binn sequential read (use_int_compression = %d)... ", use_int_compression);
  list_idx = binn_list();
  list2_idx = binn_list();
  map_idx = binn_map();
  obj_idx = binn_object();
  assert((&list[list_idx]) != 0);
  assert((&list2[list2_idx]) != 0);
  assert((&map[map_idx]) != 0);
  assert((&obj[obj_idx]) != 0);
  if (use_int_compression == 0)
  {
    list->disable_int_compression = 1;
    map->disable_int_compression = 1;
    obj->disable_int_compression = 1;
  }
  assert(binn_list_add_int32(list2, 250) == 1);
  assert(binn_list_add_null(list2) == 1);
  assert(binn_list_add_str(list2, "l1st2") == 1);
  assert(binn_list_add_bool(list2, 1) == 1);
  list2size = binn_size(list2);
  assert(binn_list_add_int8(list, 111) == 1);
  assert(binn_list_add_int32(list, 123456789) == 1);
  assert(binn_list_add_int16(list, -123) == 1);
  assert(binn_list_add_int64(list, 9876543210) == 1);
  assert(binn_list_add_float(list, 1.25) == 1);
  assert(binn_list_add_double(list, 25.987654321) == 1);
  assert(binn_list_add_bool(list, 1) == 1);
  assert(binn_list_add_bool(list, 0) == 1);
  assert(binn_list_add_null(list) == 1);
  assert(binn_list_add_str(list, "testing...") == 1);
  assert(binn_list_add_blob(list, (char *) blob_ptr, blob_size) == 1);
  assert(binn_list_add_list(list, list2) == 1);
  assert(binn_object_set_int8(obj, "a", 111) == 1);
  assert(binn_object_set_int32(obj, "b", 123456789) == 1);
  assert(binn_object_set_int16(obj, "c", -123) == 1);
  assert(binn_object_set_int64(obj, "d", 9876543210) == 1);
  assert(binn_object_set_float(obj, "e", 1.25) == 1);
  assert(binn_object_set_double(obj, "f", 25.987654321) == 1);
  assert(binn_object_set_bool(obj, "g", 1) == 1);
  assert(binn_object_set_bool(obj, "h", 0) == 1);
  assert(binn_object_set_null(obj, "i") == 1);
  assert(binn_object_set_str(obj, "j", "testing...") == 1);
  assert(binn_object_set_blob(obj, "k", (char *) blob_ptr, blob_size) == 1);
  assert(binn_object_set_list(obj, "l", list2) == 1);
  assert(binn_map_set_int8(map, 55010, 111) == 1);
  assert(binn_map_set_int32(map, 55020, 123456789) == 1);
  assert(binn_map_set_int16(map, 55030, -123) == 1);
  assert(binn_map_set_int64(map, 55040, 9876543210) == 1);
  assert(binn_map_set_float(map, 55050, 1.25) == 1);
  assert(binn_map_set_double(map, 55060, 25.987654321) == 1);
  assert(binn_map_set_bool(map, 55070, 1) == 1);
  assert(binn_map_set_bool(map, 55080, 0) == 1);
  assert(binn_map_set_null(map, 55090) == 1);
  assert(binn_map_set_str(map, 55100, "testing...") == 1);
  assert(binn_map_set_blob(map, 55110, (char *) blob_ptr, blob_size) == 1);
  assert(binn_map_set_list(map, 55120, list2) == 1);
  ptr_idx = binn_ptr(list);
  assert((&ptr[ptr_idx]) != 0);
  assert(binn_iter_init(&iter, ptr, 0xE0));
  assert(iter.pnext > (&ptr[ptr_idx]));
  assert(iter.plimit > (&ptr[ptr_idx]));
  assert(iter.count == 12);
  assert(iter.current == 0);
  assert(binn_list_next(&iter, &value) == 1);
  assert(iter.pnext > (&ptr[ptr_idx]));
  assert(iter.plimit > (&ptr[ptr_idx]));
  assert(iter.count == 12);
  assert(iter.current == 1);
  assert(value.type == 0x21);
  assert(value.vint8 == 111);
  assert(binn_list_next(&iter, &value) == 1);
  assert(iter.current == 2);
  if (use_int_compression)
  {
    assert(value.type == 0x60);
  }
  else
  {
    assert(value.type == 0x61);
  }
  assert(value.vint32 == 123456789);
  assert(binn_list_next(&iter, &value) == 1);
  assert(iter.current == 3);
  if (use_int_compression)
  {
    assert(value.type == 0x21);
    assert(value.vint8 == (-123));
  }
  else
  {
    assert(value.type == 0x41);
    assert(value.vint16 == (-123));
  }
  assert(binn_list_next(&iter, &value) == 1);
  assert(iter.current == 4);
  assert(value.type == 0x81);
  assert(value.vint64 == 9876543210);
  assert(binn_list_next(&iter, &value) == 1);
  assert(iter.current == 5);
  assert(value.type == 0x62);
  assert(AlmostEqualFloats(value.vfloat, 1.25, 2));
  assert(binn_list_next(&iter, &value) == 1);
  assert(iter.current == 6);
  assert(value.type == 0x82);
  assert((value.vdouble - 25.987654321) < 0.00000001);
  assert(binn_list_next(&iter, &value) == 1);
  assert(iter.current == 7);
  assert(value.type == 0x80061);
  assert(value.vbool == 1);
  assert(binn_list_next(&iter, &value) == 1);
  assert(iter.current == 8);
  assert(value.type == 0x80061);
  assert(value.vbool == 0);
  assert(binn_list_next(&iter, &value) == 1);
  assert(iter.current == 9);
  assert(value.type == 0x00);
  assert(binn_list_next(&iter, &value) == 1);
  assert(iter.current == 10);
  assert(value.type == 0xA0);
  assert(strcmp((char *) value.ptr, "testing...") == 0);
  assert(binn_list_next(&iter, &value) == 1);
  assert(iter.current == 11);
  assert(value.type == 0xC0);
  assert(memcmp(value.ptr, blob_ptr, blob_size) == 0);
  assert(binn_list_next(&iter, &value) == 1);
  assert(iter.current == 12);
  assert(value.type == 0xE0);
  assert(value.size == list2size);
  assert(value.count == 4);
  assert(value.ptr != 0);
  assert(binn_list_int32(value.ptr, 1) == 250);
  assert(binn_list_null(value.ptr, 2) == 1);
  ptr_idx = binn_list_str(value.ptr_idx, 3);
  assert((&ptr[ptr_idx]) != 0);
  assert(strcmp((char *) ptr, "l1st2") == 0);
  assert(binn_list_bool(value.ptr, 4) == 1);
  assert(binn_list_next(&iter, &value) == 0);
  assert(binn_list_next(&iter, &value) == 0);
  ptr_idx = binn_ptr(obj);
  assert((&ptr[ptr_idx]) != 0);
  assert(binn_iter_init(&iter, ptr, 0xE2));
  assert(iter.pnext > (&ptr[ptr_idx]));
  assert(iter.plimit > (&ptr[ptr_idx]));
  assert(iter.count == 12);
  assert(iter.current == 0);
  assert(binn_object_next(&iter, key, &value) == 1);
  assert(iter.pnext > (&ptr[ptr_idx]));
  assert(iter.plimit > (&ptr[ptr_idx]));
  assert(iter.count == 12);
  assert(iter.current == 1);
  assert(value.type == 0x21);
  assert(value.vint8 == 111);
  assert(strcmp(key, "a") == 0);
  assert(binn_object_next(&iter, key, &value) == 1);
  assert(iter.current == 2);
  if (use_int_compression)
  {
    assert(value.type == 0x60);
  }
  else
  {
    assert(value.type == 0x61);
  }
  assert(value.vint32 == 123456789);
  assert(strcmp(key, "b") == 0);
  assert(binn_object_next(&iter, key, &value) == 1);
  assert(iter.current == 3);
  if (use_int_compression)
  {
    assert(value.type == 0x21);
    assert(value.vint8 == (-123));
  }
  else
  {
    assert(value.type == 0x41);
    assert(value.vint16 == (-123));
  }
  assert(strcmp(key, "c") == 0);
  assert(binn_object_next(&iter, key, &value) == 1);
  assert(iter.current == 4);
  assert(value.type == 0x81);
  assert(value.vint64 == 9876543210);
  assert(strcmp(key, "d") == 0);
  assert(binn_object_next(&iter, key, &value) == 1);
  assert(iter.current == 5);
  assert(value.type == 0x62);
  assert(AlmostEqualFloats(value.vfloat, 1.25, 2));
  assert(strcmp(key, "e") == 0);
  assert(binn_object_next(&iter, key, &value) == 1);
  assert(iter.current == 6);
  assert(value.type == 0x82);
  assert((value.vdouble - 25.987654321) < 0.00000001);
  assert(strcmp(key, "f") == 0);
  assert(binn_object_next(&iter, key, &value) == 1);
  assert(iter.current == 7);
  assert(value.type == 0x80061);
  assert(value.vbool == 1);
  assert(strcmp(key, "g") == 0);
  assert(binn_object_next(&iter, key, &value) == 1);
  assert(iter.current == 8);
  assert(value.type == 0x80061);
  assert(value.vbool == 0);
  assert(strcmp(key, "h") == 0);
  assert(binn_object_next(&iter, key, &value) == 1);
  assert(iter.current == 9);
  assert(value.type == 0x00);
  assert(strcmp(key, "i") == 0);
  assert(binn_object_next(&iter, key, &value) == 1);
  assert(iter.current == 10);
  assert(value.type == 0xA0);
  assert(strcmp((char *) value.ptr, "testing...") == 0);
  assert(strcmp(key, "j") == 0);
  assert(binn_object_next(&iter, key, &value) == 1);
  assert(iter.current == 11);
  assert(value.type == 0xC0);
  assert(memcmp(value.ptr, blob_ptr, blob_size) == 0);
  assert(strcmp(key, "k") == 0);
  assert(binn_object_next(&iter, key, &value) == 1);
  assert(iter.current == 12);
  assert(value.type == 0xE0);
  assert(value.size == list2size);
  assert(value.count == 4);
  assert(value.ptr != 0);
  assert(binn_list_int32(value.ptr, 1) == 250);
  assert(binn_list_null(value.ptr, 2) == 1);
  ptr_idx = binn_list_str(value.ptr_idx, 3);
  assert((&ptr[ptr_idx]) != 0);
  assert(strcmp((char *) ptr, "l1st2") == 0);
  assert(binn_list_bool(value.ptr, 4) == 1);
  assert(strcmp(key, "l") == 0);
  assert(binn_object_next(&iter, key, &value) == 0);
  assert(binn_object_next(&iter, key, &value) == 0);
  ptr_idx = binn_ptr(map);
  assert((&ptr[ptr_idx]) != 0);
  assert(binn_iter_init(&iter, ptr, 0xE1));
  assert(iter.pnext > (&ptr[ptr_idx]));
  assert(iter.plimit > (&ptr[ptr_idx]));
  assert(iter.count == 12);
  assert(iter.current == 0);
  assert(binn_map_next(&iter, &id, &value) == 1);
  assert(iter.pnext > (&ptr[ptr_idx]));
  assert(iter.plimit > (&ptr[ptr_idx]));
  assert(iter.count == 12);
  assert(iter.current == 1);
  assert(value.type == 0x21);
  assert(value.vint8 == 111);
  assert(id == 55010);
  assert(binn_map_next(&iter, &id, &value) == 1);
  assert(iter.current == 2);
  if (use_int_compression)
  {
    assert(value.type == 0x60);
  }
  else
  {
    assert(value.type == 0x61);
  }
  assert(value.vint32 == 123456789);
  assert(id == 55020);
  assert(binn_map_next(&iter, &id, &value) == 1);
  assert(iter.current == 3);
  if (use_int_compression)
  {
    assert(value.type == 0x21);
    assert(value.vint8 == (-123));
  }
  else
  {
    assert(value.type == 0x41);
    assert(value.vint16 == (-123));
  }
  assert(id == 55030);
  assert(binn_map_next(&iter, &id, &value) == 1);
  assert(iter.current == 4);
  assert(value.type == 0x81);
  assert(value.vint64 == 9876543210);
  assert(id == 55040);
  assert(binn_map_next(&iter, &id, &value) == 1);
  assert(iter.current == 5);
  assert(value.type == 0x62);
  assert(AlmostEqualFloats(value.vfloat, 1.25, 2));
  assert(id == 55050);
  assert(binn_map_next(&iter, &id, &value) == 1);
  assert(iter.current == 6);
  assert(value.type == 0x82);
  assert((value.vdouble - 25.987654321) < 0.00000001);
  assert(id == 55060);
  assert(binn_map_next(&iter, &id, &value) == 1);
  assert(iter.current == 7);
  assert(value.type == 0x80061);
  assert(value.vbool == 1);
  assert(id == 55070);
  assert(binn_map_next(&iter, &id, &value) == 1);
  assert(iter.current == 8);
  assert(value.type == 0x80061);
  assert(value.vbool == 0);
  assert(id == 55080);
  assert(binn_map_next(&iter, &id, &value) == 1);
  assert(iter.current == 9);
  assert(value.type == 0x00);
  assert(id == 55090);
  assert(binn_map_next(&iter, &id, &value) == 1);
  assert(iter.current == 10);
  assert(value.type == 0xA0);
  assert(strcmp((char *) value.ptr, "testing...") == 0);
  assert(id == 55100);
  assert(binn_map_next(&iter, &id, &value) == 1);
  assert(iter.current == 11);
  assert(value.type == 0xC0);
  assert(memcmp(value.ptr, blob_ptr, blob_size) == 0);
  assert(id == 55110);
  assert(binn_map_next(&iter, &id, &value) == 1);
  assert(iter.current == 12);
  assert(value.type == 0xE0);
  assert(value.size == list2size);
  assert(value.count == 4);
  assert(value.ptr != 0);
  assert(binn_list_int32(value.ptr, 1) == 250);
  assert(binn_list_null(value.ptr, 2) == 1);
  ptr_idx = binn_list_str(value.ptr_idx, 3);
  assert((&ptr[ptr_idx]) != 0);
  assert(strcmp((char *) ptr, "l1st2") == 0);
  assert(binn_list_bool(value.ptr, 4) == 1);
  assert(id == 55120);
  assert(binn_map_next(&iter, &id, &value) == 0);
  assert(binn_map_next(&iter, &id, &value) == 0);
  copy_idx = binn_copy(list);
  assert((&copy[copy_idx]) != 0);
  assert(binn_type(copy) == binn_type(list));
  assert(binn_count(copy) == binn_count(list));
  assert(binn_size(copy) == binn_size(list));
  assert(binn_iter_init(&iter, list, 0xE0));
  assert(binn_iter_init(&iter2, copy, 0xE0));
  while (binn_list_next(&iter, &value))
  {
    assert(binn_list_next(&iter2, &value2) == 1);
    assert(value.type == value2.type);
  }

  assert(binn_list_add_str(copy, "testing...") == 1);
  assert(binn_type(copy) == binn_type(list));
  assert(binn_count(copy) == (binn_count(list) + 1));
  assert(binn_size(copy) > binn_size(list));
  binn_free(copy);
  copy_idx = binn_copy(map);
  assert((&copy[copy_idx]) != 0);
  assert(binn_type(copy) == binn_type(map));
  assert(binn_count(copy) == binn_count(map));
  assert(binn_size(copy) == binn_size(map));
  assert(binn_iter_init(&iter, map, 0xE1));
  assert(binn_iter_init(&iter2, copy, 0xE1));
  while (binn_map_next(&iter, &id, &value))
  {
    assert(binn_map_next(&iter2, &id2, &value2) == 1);
    assert(id == id2);
    assert(value.type == value2.type);
  }

  assert(binn_map_set_int32(copy, 5600, 123) == 1);
  assert(binn_type(copy) == binn_type(map));
  assert(binn_count(copy) == (binn_count(map) + 1));
  assert(binn_size(copy) > binn_size(map));
  binn_free(copy);
  copy_idx = binn_copy(obj);
  assert((&copy[copy_idx]) != 0);
  assert(binn_type(copy) == binn_type(obj));
  assert(binn_count(copy) == binn_count(obj));
  assert(binn_size(copy) == binn_size(obj));
  assert(binn_iter_init(&iter, obj, 0xE2));
  assert(binn_iter_init(&iter2, copy, 0xE2));
  while (binn_object_next(&iter, key, &value))
  {
    assert(binn_object_next(&iter2, key2, &value2) == 1);
    assert(strcmp(key, key2) == 0);
    assert(value.type == value2.type);
  }

  assert(binn_object_set_int32(copy, "another", 123) == 1);
  assert(binn_type(copy) == binn_type(obj));
  assert(binn_count(copy) == (binn_count(obj) + 1));
  assert(binn_size(copy) > binn_size(obj));
  binn_free(copy);
  ptr_idx = binn_ptr(list);
  copy_idx = binn_copy(ptr);
  assert((&copy[copy_idx]) != 0);
  assert(binn_type(copy) == binn_type(list));
  assert(binn_count(copy) == binn_count(list));
  assert(binn_size(copy) == binn_size(list));
  assert(binn_iter_init(&iter, ptr, 0xE0));
  assert(binn_iter_init(&iter2, copy, 0xE0));
  while (binn_list_next(&iter, &value))
  {
    assert(binn_list_next(&iter2, &value2) == 1);
    assert(value.type == value2.type);
  }

  assert(binn_list_add_str(copy, "testing...") == 1);
  assert(binn_type(copy) == binn_type(list));
  assert(binn_count(copy) == (binn_count(list) + 1));
  assert(binn_size(copy) > binn_size(list));
  binn_free(copy);
  ptr_idx = binn_ptr(map);
  copy_idx = binn_copy(ptr);
  assert((&copy[copy_idx]) != 0);
  assert(binn_type(copy) == binn_type(map));
  assert(binn_count(copy) == binn_count(map));
  assert(binn_size(copy) == binn_size(map));
  assert(binn_iter_init(&iter, ptr, 0xE1));
  assert(binn_iter_init(&iter2, copy, 0xE1));
  while (binn_map_next(&iter, &id, &value))
  {
    assert(binn_map_next(&iter2, &id2, &value2) == 1);
    assert(id == id2);
    assert(value.type == value2.type);
  }

  assert(binn_map_set_int32(copy, 5600, 123) == 1);
  assert(binn_type(copy) == binn_type(map));
  assert(binn_count(copy) == (binn_count(map) + 1));
  assert(binn_size(copy) > binn_size(map));
  binn_free(copy);
  ptr_idx = binn_ptr(obj);
  copy_idx = binn_copy(ptr);
  assert((&copy[copy_idx]) != 0);
  assert(binn_type(copy) == binn_type(obj));
  assert(binn_count(copy) == binn_count(obj));
  assert(binn_size(copy) == binn_size(obj));
  assert(binn_iter_init(&iter, ptr, 0xE2));
  assert(binn_iter_init(&iter2, copy, 0xE2));
  while (binn_object_next(&iter, key, &value))
  {
    assert(binn_object_next(&iter2, key2, &value2) == 1);
    assert(strcmp(key, key2) == 0);
    assert(value.type == value2.type);
  }

  assert(binn_object_set_int32(copy, "another", 123) == 1);
  assert(binn_type(copy) == binn_type(obj));
  assert(binn_count(copy) == (binn_count(obj) + 1));
  assert(binn_size(copy) > binn_size(obj));
  binn_free(copy);
  binn_free(list);
  binn_free(list2);
  binn_free(map);
  binn_free(obj);
  puts("OK");
}


----------------------------
***/


