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


/*** DEPENDENCIES:
***/


