const char *proper_name_lite(const char *name_ascii, const char *name_utf8)
{
  const char *translation = gettext(name_ascii);
  return (translation != name_ascii) ? (translation) : ((c_strcasecmp(locale_charset(), "UTF-8") == 0) ? (name_utf8) : (name_ascii));
}


/*** DEPENDENCIES:
int c_strcasecmp(const char *s1, const char *s2)
{
  register const unsigned char *p1 = (const unsigned char *) s1;
  unsigned int p1_idx = 0;
  register const unsigned char *p2 = (const unsigned char *) s2;
  unsigned int p2_idx = 0;
  unsigned char c1;
  unsigned char c2;
  if ((&p1[p1_idx]) == (&p2[p2_idx]))
  {
    return 0;
  }
  do
  {
    c1 = c_tolower(*(&p1[p1_idx]));
    c2 = c_tolower(*(&p2[p2_idx]));
    if (c1 == '\0')
    {
      break;
    }
    p1_idx += 1;
    p2_idx += 1;
  }
  while (c1 == c2);
  if (255 <= 2147483647)
  {
    return c1 - c2;
  }
  else
    return (c1 > c2) - (c1 < c2);
}


----------------------------
const char *locale_charset(void)
{
  const char *codeset;
  unsigned int codeset_idx = 0;
  codeset_idx = nl_langinfo(CODESET);
  if ((&codeset[codeset_idx]) == 0)
  {
    codeset_idx = "";
  }
  {
    {
      if (codeset[0 + codeset_idx] == '\0')
      {
        codeset_idx = "ASCII";
      }
    }
  }
  return codeset;
}


----------------------------
***/


