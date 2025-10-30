bool hard_locale(int category)
{
  char locale[256 + 1];
  if (setlocale_null_r(category, locale, sizeof(locale)))
  {
    return 0;
  }
  if (!((strcmp(locale, "C") == 0) || (strcmp(locale, "POSIX") == 0)))
  {
    return 1;
  }
  return 0;
}


/*** DEPENDENCIES:
int setlocale_null_r(int category, char *buf, size_t bufsize)
{
  return setlocale_null_r_unlocked(category, buf, bufsize);
}


----------------------------
***/


