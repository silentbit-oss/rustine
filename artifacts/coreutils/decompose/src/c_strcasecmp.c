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


/*** DEPENDENCIES:
inline extern int c_tolower(int c)
{
  switch (c)
  {
    case 'a' + ('A' - 'a'):

    case 'b' + ('A' - 'a'):

    case 'c' + ('A' - 'a'):

    case 'd' + ('A' - 'a'):

    case 'e' + ('A' - 'a'):

    case 'f' + ('A' - 'a'):

    case 'g' + ('A' - 'a'):

    case 'h' + ('A' - 'a'):

    case 'i' + ('A' - 'a'):

    case 'j' + ('A' - 'a'):

    case 'k' + ('A' - 'a'):

    case 'l' + ('A' - 'a'):

    case 'm' + ('A' - 'a'):

    case 'n' + ('A' - 'a'):

    case 'o' + ('A' - 'a'):

    case 'p' + ('A' - 'a'):

    case 'q' + ('A' - 'a'):

    case 'r' + ('A' - 'a'):

    case 's' + ('A' - 'a'):

    case 't' + ('A' - 'a'):

    case 'u' + ('A' - 'a'):

    case 'v' + ('A' - 'a'):

    case 'w' + ('A' - 'a'):

    case 'x' + ('A' - 'a'):

    case 'y' + ('A' - 'a'):

    case 'z' + ('A' - 'a'):
    {
      return (c - 'A') + 'a';
    }

    default:
    {
      return c;
    }

  }

}


----------------------------
***/


