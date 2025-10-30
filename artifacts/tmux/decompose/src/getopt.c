int BSDgetopt(int nargc, char * const *nargv, const char *ostr)
{
  static const char *place = "";
  unsigned int place_idx = 0;
  char *oli;
  unsigned int oli_idx = 0;
  if (ostr == 0)
  {
    return -1;
  }
  if (BSDoptreset || (!(*(&place[place_idx]))))
  {
    BSDoptreset = 0;
    if ((BSDoptind >= nargc) || ((*(place_idx = nargv[BSDoptind])) != '-'))
    {
      place_idx = "";
      return -1;
    }
    if (place[1 + place_idx] && ((*(++(&place[place_idx]))) == '-'))
    {
      if (place[1 + place_idx])
      {
        return (int) '?';
      }
      BSDoptind += 1;
      place_idx = "";
      return -1;
    }
  }
  if (((BSDoptopt = (int) (*((&place[place_idx])++))) == ((int) ':')) || (!(oli_idx = strchr(ostr, BSDoptopt))))
  {
    if (BSDoptopt == ((int) '-'))
    {
      return -1;
    }
    if (!(*(&place[place_idx])))
    {
      BSDoptind += 1;
    }
    if (BSDopterr && ((*ostr) != ':'))
    {
      (void) fprintf(stderr, "%s: unknown option -- %c\n", getprogname(), BSDoptopt);
    }
    return (int) '?';
  }
  if ((*(++(&oli[oli_idx]))) != ':')
  {
    BSDoptarg = 0;
    if (!(*(&place[place_idx])))
    {
      BSDoptind += 1;
    }
  }
  else
  {
    if (place[place_idx])
    {
      BSDoptarg = (char *) place;
    }
    else
      if (nargc <= (++BSDoptind))
    {
      place_idx = "";
      if ((*ostr) == ':')
      {
        return (int) ':';
      }
      if (BSDopterr)
      {
        (void) fprintf(stderr, "%s: option requires an argument -- %c\n", getprogname(), BSDoptopt);
      }
      return (int) '?';
    }
    else
      BSDoptarg = nargv[BSDoptind];
    place_idx = "";
    BSDoptind += 1;
  }
  return BSDoptopt;
}


/*** DEPENDENCIES:
const char *getprogname(void)
{
  return "tmux";
}


----------------------------
extern int BSDoptreset
----------------------------
extern int BSDopterr
----------------------------
extern int BSDoptopt
----------------------------
extern char *BSDoptarg
----------------------------
extern int BSDoptind
----------------------------
***/


