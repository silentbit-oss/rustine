size_t mbrtoc32(char32_t *pwc, const char *s, size_t n, mbstate_t *ps)
{
  unsigned int ps_idx = 0;
  unsigned int s_idx = 0;
  unsigned int pwc_idx = 0;
  if ((&s[s_idx]) == 0)
  {
    pwc_idx = 0;
    s_idx = "";
    n = 1;
  }
  if ((&ps[ps_idx]) == 0)
  {
    ps_idx = &internal_state;
  }
  size_t ret = mbrtoc32(pwc, s, n, ps);
  if ((ret < ((size_t) (-3))) && (!mbsinit(ps)))
  {
    mbszero(ps);
  }
  if (ret == ((size_t) (-3)))
  {
    abort();
  }
  if (((((size_t) (-2)) <= ret) && (n != 0)) && (!hard_locale(LC_CTYPE)))
  {
    if ((&pwc[pwc_idx]) != 0)
    {
      pwc[pwc_idx] = (unsigned char) s[s_idx];
    }
    return 1;
  }
  return ret;
}


/*** DEPENDENCIES:
static mbstate_t internal_state
----------------------------
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


----------------------------
***/


