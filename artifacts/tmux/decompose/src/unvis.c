int helper_unvis_1(char * const cp, char c, int * const astate)
{
  switch (c)
  {
    case '\\':
    {
      *cp = c;
      *astate = 0;
      return 1;
    }

    case '0':

    case '1':

    case '2':

    case '3':

    case '4':

    case '5':

    case '6':

    case '7':
    {
      *cp = c - '0';
      *astate = 5;
      return 0;
    }

    case 'M':
    {
      *cp = (char) 0200;
      *astate = 2;
      return 0;
    }

    case '^':
    {
      *astate = 4;
      return 0;
    }

    case 'n':
    {
      *cp = '\n';
      *astate = 0;
      return 1;
    }

    case 'r':
    {
      *cp = '\r';
      *astate = 0;
      return 1;
    }

    case 'b':
    {
      *cp = '\b';
      *astate = 0;
      return 1;
    }

    case 'a':
    {
      *cp = '\007';
      *astate = 0;
      return 1;
    }

    case 'v':
    {
      *cp = '\v';
      *astate = 0;
      return 1;
    }

    case 't':
    {
      *cp = '\t';
      *astate = 0;
      return 1;
    }

    case 'f':
    {
      *cp = '\f';
      *astate = 0;
      return 1;
    }

    case 's':
    {
      *cp = ' ';
      *astate = 0;
      return 1;
    }

    case 'E':
    {
      *cp = '\033';
      *astate = 0;
      return 1;
    }

    case '\n':
    {
      *astate = 0;
      return 3;
    }

    case '$':
    {
      *astate = 0;
      return 3;
    }

  }

  *astate = 0;
  return -1;
}


/*** DEPENDENCIES:
***/


int unvis(char *cp, char c, int *astate, int flag)
{
  if (flag & 1)
  {
    if (((*astate) == 5) || ((*astate) == 6))
    {
      *astate = 0;
      return 1;
    }
    return ((*astate) == 0) ? (3) : (-1);
  }
  switch (*astate)
  {
    case 0:
    {
      *cp = 0;
      if (c == '\\')
      {
        *astate = 1;
        return 0;
      }
      *cp = c;
      return 1;
    }

    case 1:
    {
      helper_unvis_1(cp, c, astate);
    }

    case 2:
    {
      if (c == '-')
      {
        *astate = 3;
      }
      else
        if (c == '^')
      {
        *astate = 4;
      }
      else
      {
        *astate = 0;
        return -1;
      }
      return 0;
    }

    case 3:
    {
      *astate = 0;
      *cp |= c;
      return 1;
    }

    case 4:
    {
      if (c == '?')
      {
        *cp |= 0177;
      }
      else
        *cp |= c & 037;
      *astate = 0;
      return 1;
    }

    case 5:
    {
      if ((((u_char) c) >= '0') && (((u_char) c) <= '7'))
      {
        *cp = ((*cp) << 3) + (c - '0');
        *astate = 6;
        return 0;
      }
      *astate = 0;
      return 2;
    }

    case 6:
    {
      *astate = 0;
      if ((((u_char) c) >= '0') && (((u_char) c) <= '7'))
      {
        *cp = ((*cp) << 3) + (c - '0');
        return 1;
      }
      return 2;
    }

    default:
    {
      *astate = 0;
      return -1;
    }

  }

}


/*** DEPENDENCIES:
int helper_unvis_1(char * const cp, char c, int * const astate)
{
  switch (c)
  {
    case '\\':
    {
      *cp = c;
      *astate = 0;
      return 1;
    }

    case '0':

    case '1':

    case '2':

    case '3':

    case '4':

    case '5':

    case '6':

    case '7':
    {
      *cp = c - '0';
      *astate = 5;
      return 0;
    }

    case 'M':
    {
      *cp = (char) 0200;
      *astate = 2;
      return 0;
    }

    case '^':
    {
      *astate = 4;
      return 0;
    }

    case 'n':
    {
      *cp = '\n';
      *astate = 0;
      return 1;
    }

    case 'r':
    {
      *cp = '\r';
      *astate = 0;
      return 1;
    }

    case 'b':
    {
      *cp = '\b';
      *astate = 0;
      return 1;
    }

    case 'a':
    {
      *cp = '\007';
      *astate = 0;
      return 1;
    }

    case 'v':
    {
      *cp = '\v';
      *astate = 0;
      return 1;
    }

    case 't':
    {
      *cp = '\t';
      *astate = 0;
      return 1;
    }

    case 'f':
    {
      *cp = '\f';
      *astate = 0;
      return 1;
    }

    case 's':
    {
      *cp = ' ';
      *astate = 0;
      return 1;
    }

    case 'E':
    {
      *cp = '\033';
      *astate = 0;
      return 1;
    }

    case '\n':
    {
      *astate = 0;
      return 3;
    }

    case '$':
    {
      *astate = 0;
      return 3;
    }

  }

  *astate = 0;
  return -1;
}


----------------------------
***/


int strunvis(char *dst, const char *src)
{
  unsigned int dst_idx = 0;
  char c;
  char *start = dst;
  int state = 0;
  while (c = *(src++))
  {
    again:
    switch (unvis(dst, c, &state, 0))
    {
      case 1:
      {
        dst_idx += 1;
        break;
      }

      case 2:
      {
        dst_idx += 1;
        goto again;
      }

      case 0:

      case 3:
      {
        break;
      }

      default:
      {
        dst[dst_idx] = '\0';
        return -1;
      }

    }


  }

  if (unvis(dst, c, &state, 1) == 1)
  {
    dst_idx += 1;
  }
  dst[dst_idx] = '\0';
  return (&dst[dst_idx]) - start;
}


/*** DEPENDENCIES:
int unvis(char *cp, char c, int *astate, int flag)
{
  if (flag & 1)
  {
    if (((*astate) == 5) || ((*astate) == 6))
    {
      *astate = 0;
      return 1;
    }
    return ((*astate) == 0) ? (3) : (-1);
  }
  switch (*astate)
  {
    case 0:
    {
      *cp = 0;
      if (c == '\\')
      {
        *astate = 1;
        return 0;
      }
      *cp = c;
      return 1;
    }

    case 1:
    {
      helper_unvis_1(cp, c, astate);
    }

    case 2:
    {
      if (c == '-')
      {
        *astate = 3;
      }
      else
        if (c == '^')
      {
        *astate = 4;
      }
      else
      {
        *astate = 0;
        return -1;
      }
      return 0;
    }

    case 3:
    {
      *astate = 0;
      *cp |= c;
      return 1;
    }

    case 4:
    {
      if (c == '?')
      {
        *cp |= 0177;
      }
      else
        *cp |= c & 037;
      *astate = 0;
      return 1;
    }

    case 5:
    {
      if ((((u_char) c) >= '0') && (((u_char) c) <= '7'))
      {
        *cp = ((*cp) << 3) + (c - '0');
        *astate = 6;
        return 0;
      }
      *astate = 0;
      return 2;
    }

    case 6:
    {
      *astate = 0;
      if ((((u_char) c) >= '0') && (((u_char) c) <= '7'))
      {
        *cp = ((*cp) << 3) + (c - '0');
        return 1;
      }
      return 2;
    }

    default:
    {
      *astate = 0;
      return -1;
    }

  }

}


----------------------------
***/


ssize_t strnunvis(char *dst, const char *src, size_t sz)
{
  unsigned int dst_idx = 0;
  char c;
  char p;
  char *start = dst;
  char *end = ((&dst[dst_idx]) + sz) - 1;
  int state = 0;
  if (sz > 0)
  {
    *end = '\0';
  }
  while (c = *(src++))
  {
    again:
    switch (unvis(&p, c, &state, 0))
    {
      case 1:
      {
        if ((&dst[dst_idx]) < end)
        {
          dst[dst_idx] = p;
        }
        dst_idx += 1;
        break;
      }

      case 2:
      {
        if ((&dst[dst_idx]) < end)
        {
          dst[dst_idx] = p;
        }
        dst_idx += 1;
        goto again;
      }

      case 0:

      case 3:
      {
        break;
      }

      default:
      {
        if ((&dst[dst_idx]) <= end)
        {
          dst[dst_idx] = '\0';
        }
        return -1;
      }

    }


  }

  if (unvis(&p, c, &state, 1) == 1)
  {
    if ((&dst[dst_idx]) < end)
    {
      dst[dst_idx] = p;
    }
    dst_idx += 1;
  }
  if ((&dst[dst_idx]) <= end)
  {
    dst[dst_idx] = '\0';
  }
  return (&dst[dst_idx]) - start;
}


/*** DEPENDENCIES:
int unvis(char *cp, char c, int *astate, int flag)
{
  if (flag & 1)
  {
    if (((*astate) == 5) || ((*astate) == 6))
    {
      *astate = 0;
      return 1;
    }
    return ((*astate) == 0) ? (3) : (-1);
  }
  switch (*astate)
  {
    case 0:
    {
      *cp = 0;
      if (c == '\\')
      {
        *astate = 1;
        return 0;
      }
      *cp = c;
      return 1;
    }

    case 1:
    {
      helper_unvis_1(cp, c, astate);
    }

    case 2:
    {
      if (c == '-')
      {
        *astate = 3;
      }
      else
        if (c == '^')
      {
        *astate = 4;
      }
      else
      {
        *astate = 0;
        return -1;
      }
      return 0;
    }

    case 3:
    {
      *astate = 0;
      *cp |= c;
      return 1;
    }

    case 4:
    {
      if (c == '?')
      {
        *cp |= 0177;
      }
      else
        *cp |= c & 037;
      *astate = 0;
      return 1;
    }

    case 5:
    {
      if ((((u_char) c) >= '0') && (((u_char) c) <= '7'))
      {
        *cp = ((*cp) << 3) + (c - '0');
        *astate = 6;
        return 0;
      }
      *astate = 0;
      return 2;
    }

    case 6:
    {
      *astate = 0;
      if ((((u_char) c) >= '0') && (((u_char) c) <= '7'))
      {
        *cp = ((*cp) << 3) + (c - '0');
        return 1;
      }
      return 2;
    }

    default:
    {
      *astate = 0;
      return -1;
    }

  }

}


----------------------------
***/


