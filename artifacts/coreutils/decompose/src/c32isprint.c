int c32isprint(wint_t wc)
{
  if (wc != WEOF)
  {
    return uc_is_print(wc);
  }
  else
    return 0;
}


/*** DEPENDENCIES:
***/


