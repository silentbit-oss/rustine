const char *attributes_tostring(int attr)
{
  static char buf[128];
  size_t len;
  if (attr == 0)
  {
    return "none";
  }
  len = xsnprintf(buf, sizeof(buf), "%s%s%s%s%s%s%s%s", (attr & 0x1) ? ("bright,") : (""), (attr & 0x2) ? ("dim,") : (""), (attr & 0x4) ? ("underscore,") : (""), (attr & 0x8) ? ("blink,") : (""), (attr & 0x10) ? ("reverse,") : (""), (attr & 0x20) ? ("hidden,") : (""), (attr & 0x40) ? ("italics,") : (""), (attr & 0x100) ? ("strikethrough,") : (""));
  if (len > 0)
  {
    buf[len - 1] = '\0';
  }
  return buf;
}


/*** DEPENDENCIES:
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
***/


int attributes_fromstring(const char *str)
{
  unsigned int str_idx = 0;
  const char delimiters[] = " ,|";
  int attr;
  size_t end;
  if ((str[str_idx] == '\0') || (strcspn(str, delimiters) == 0))
  {
    return -1;
  }
  if (strchr(delimiters, str[(strlen(str) - 1) + str_idx]) != 0)
  {
    return -1;
  }
  if ((strcasecmp(str, "default") == 0) || (strcasecmp(str, "none") == 0))
  {
    return 0;
  }
  attr = 0;
  do
  {
    end = strcspn(str, delimiters);
    if (((end == 6) && (strncasecmp(str, "bright", end) == 0)) || ((end == 4) && (strncasecmp(str, "bold", end) == 0)))
    {
      attr |= 0x1;
    }
    else
      if ((end == 3) && (strncasecmp(str, "dim", end) == 0))
    {
      attr |= 0x2;
    }
    else
      if ((end == 10) && (strncasecmp(str, "underscore", end) == 0))
    {
      attr |= 0x4;
    }
    else
      if ((end == 5) && (strncasecmp(str, "blink", end) == 0))
    {
      attr |= 0x8;
    }
    else
      if ((end == 7) && (strncasecmp(str, "reverse", end) == 0))
    {
      attr |= 0x10;
    }
    else
      if ((end == 6) && (strncasecmp(str, "hidden", end) == 0))
    {
      attr |= 0x20;
    }
    else
      if ((end == 7) && (strncasecmp(str, "italics", end) == 0))
    {
      attr |= 0x40;
    }
    else
      if ((end == 13) && (strncasecmp(str, "strikethrough", end) == 0))
    {
      attr |= 0x100;
    }
    else
      return -1;
    str_idx += end + strspn(str_idx + end, delimiters);
  }
  while (str[str_idx] != '\0');
  return attr;
}


/*** DEPENDENCIES:
***/


