void colour_split_rgb(int c, u_char *r, u_char *g, u_char *b)
{
  *r = (c >> 16) & 0xff;
  *g = (c >> 8) & 0xff;
  *b = c & 0xff;
}


/*** DEPENDENCIES:
***/


const char *colour_tostring(int c)
{
  static char s[32];
  u_char r;
  u_char g;
  u_char b;
  if (c & 0x02000000)
  {
    colour_split_rgb(c, &r, &g, &b);
    xsnprintf(s, sizeof(s), "#%02x%02x%02x", r, g, b);
    return s;
  }
  if (c & 0x01000000)
  {
    xsnprintf(s, sizeof(s), "colour%u", c & 0xff);
    return s;
  }
  switch (c)
  {
    case 0:
    {
      return "black";
    }

    case 1:
    {
      return "red";
    }

    case 2:
    {
      return "green";
    }

    case 3:
    {
      return "yellow";
    }

    case 4:
    {
      return "blue";
    }

    case 5:
    {
      return "magenta";
    }

    case 6:
    {
      return "cyan";
    }

    case 7:
    {
      return "white";
    }

    case 8:
    {
      return "default";
    }

    case 90:
    {
      return "brightblack";
    }

    case 91:
    {
      return "brightred";
    }

    case 92:
    {
      return "brightgreen";
    }

    case 93:
    {
      return "brightyellow";
    }

    case 94:
    {
      return "brightblue";
    }

    case 95:
    {
      return "brightmagenta";
    }

    case 96:
    {
      return "brightcyan";
    }

    case 97:
    {
      return "brightwhite";
    }

  }

  return 0;
}


/*** DEPENDENCIES:
void colour_split_rgb(int c, u_char *r, u_char *g, u_char *b)
{
  *r = (c >> 16) & 0xff;
  *g = (c >> 8) & 0xff;
  *b = c & 0xff;
}


----------------------------
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


static int colour_dist_sq(int R, int G, int B, int r, int g, int b)
{
  return (((R - r) * (R - r)) + ((G - g) * (G - g))) + ((B - b) * (B - b));
}


/*** DEPENDENCIES:
***/


static int colour_to_6cube(int v)
{
  if (v < 48)
  {
    return 0;
  }
  if (v < 114)
  {
    return 1;
  }
  return (v - 35) / 40;
}


/*** DEPENDENCIES:
***/


int colour_find_rgb(u_char r, u_char g, u_char b)
{
  static const int q2c[6] = {0x00, 0x5f, 0x87, 0xaf, 0xd7, 0xff};
  int qr;
  int qg;
  int qb;
  int cr;
  int cg;
  int cb;
  int d;
  int idx;
  int grey_avg;
  int grey_idx;
  int grey;
  qr = colour_to_6cube(r);
  cr = q2c[qr];
  qg = colour_to_6cube(g);
  cg = q2c[qg];
  qb = colour_to_6cube(b);
  cb = q2c[qb];
  if (((cr == r) && (cg == g)) && (cb == b))
  {
    return (((16 + (36 * qr)) + (6 * qg)) + qb) | 0x01000000;
  }
  grey_avg = ((r + g) + b) / 3;
  if (grey_avg > 238)
  {
    grey_idx = 23;
  }
  else
    grey_idx = (grey_avg - 3) / 10;
  grey = 8 + (10 * grey_idx);
  d = colour_dist_sq(cr, cg, cb, r, g, b);
  if (colour_dist_sq(grey, grey, grey, r, g, b) < d)
  {
    idx = 232 + grey_idx;
  }
  else
    idx = ((16 + (36 * qr)) + (6 * qg)) + qb;
  return idx | 0x01000000;
}


/*** DEPENDENCIES:
static int colour_dist_sq(int R, int G, int B, int r, int g, int b)
{
  return (((R - r) * (R - r)) + ((G - g) * (G - g))) + ((B - b) * (B - b));
}


----------------------------
static int colour_to_6cube(int v)
{
  if (v < 48)
  {
    return 0;
  }
  if (v < 114)
  {
    return 1;
  }
  return (v - 35) / 40;
}


----------------------------
***/


u_char colour_256to16(u_char c)
{
  static const u_char table[256] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0, 4, 4, 4, 12, 12, 2, 6, 4, 4, 12, 12, 2, 2, 6, 4, 12, 12, 2, 2, 2, 6, 12, 12, 10, 10, 10, 10, 14, 12, 10, 10, 10, 10, 10, 14, 1, 5, 4, 4, 12, 12, 3, 8, 4, 4, 12, 12, 2, 2, 6, 4, 12, 12, 2, 2, 2, 6, 12, 12, 10, 10, 10, 10, 14, 12, 10, 10, 10, 10, 10, 14, 1, 1, 5, 4, 12, 12, 1, 1, 5, 4, 12, 12, 3, 3, 8, 4, 12, 12, 2, 2, 2, 6, 12, 12, 10, 10, 10, 10, 14, 12, 10, 10, 10, 10, 10, 14, 1, 1, 1, 5, 12, 12, 1, 1, 1, 5, 12, 12, 1, 1, 1, 5, 12, 12, 3, 3, 3, 7, 12, 12, 10, 10, 10, 10, 14, 12, 10, 10, 10, 10, 10, 14, 9, 9, 9, 9, 13, 12, 9, 9, 9, 9, 13, 12, 9, 9, 9, 9, 13, 12, 9, 9, 9, 9, 13, 12, 11, 11, 11, 11, 7, 12, 10, 10, 10, 10, 10, 14, 9, 9, 9, 9, 9, 13, 9, 9, 9, 9, 9, 13, 9, 9, 9, 9, 9, 13, 9, 9, 9, 9, 9, 13, 9, 9, 9, 9, 9, 13, 11, 11, 11, 11, 11, 15, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8, 8, 8, 7, 7, 7, 7, 7, 7, 15, 15, 15, 15, 15, 15};
  return table[c];
}


/*** DEPENDENCIES:
***/


int colour_join_rgb(u_char r, u_char g, u_char b)
{
  return (((((int) (r & 0xff)) << 16) | (((int) (g & 0xff)) << 8)) | ((int) (b & 0xff))) | 0x02000000;
}


/*** DEPENDENCIES:
***/


int colour_fromstring(const char *s)
{
  const char *errstr;
  const char *cp;
  unsigned int cp_idx = 0;
  int n;
  u_char r;
  u_char g;
  u_char b;
  if (((*s) == '#') && (strlen(s) == 7))
  {
    for (cp_idx = s + 1; isxdigit((u_char) cp[cp_idx]); cp_idx += 1)
    {
      ;
    }

    if (cp[cp_idx] != '\0')
    {
      return -1;
    }
    n = sscanf(s + 1, "%2hhx%2hhx%2hhx", &r, &g, &b);
    if (n != 3)
    {
      return -1;
    }
    return colour_join_rgb(r, g, b);
  }
  if (strncasecmp(s, "colour", (sizeof("colour")) - 1) == 0)
  {
    n = strtonum((s + (sizeof("colour"))) - 1, 0, 255, &errstr);
    if (errstr != 0)
    {
      return -1;
    }
    return n | 0x01000000;
  }
  if ((strcasecmp(s, "black") == 0) || (strcmp(s, "0") == 0))
  {
    return 0;
  }
  if ((strcasecmp(s, "red") == 0) || (strcmp(s, "1") == 0))
  {
    return 1;
  }
  if ((strcasecmp(s, "green") == 0) || (strcmp(s, "2") == 0))
  {
    return 2;
  }
  if ((strcasecmp(s, "yellow") == 0) || (strcmp(s, "3") == 0))
  {
    return 3;
  }
  if ((strcasecmp(s, "blue") == 0) || (strcmp(s, "4") == 0))
  {
    return 4;
  }
  if ((strcasecmp(s, "magenta") == 0) || (strcmp(s, "5") == 0))
  {
    return 5;
  }
  if ((strcasecmp(s, "cyan") == 0) || (strcmp(s, "6") == 0))
  {
    return 6;
  }
  if ((strcasecmp(s, "white") == 0) || (strcmp(s, "7") == 0))
  {
    return 7;
  }
  if ((strcasecmp(s, "default") == 0) || (strcmp(s, "8") == 0))
  {
    return 8;
  }
  if ((strcasecmp(s, "brightblack") == 0) || (strcmp(s, "90") == 0))
  {
    return 90;
  }
  if ((strcasecmp(s, "brightred") == 0) || (strcmp(s, "91") == 0))
  {
    return 91;
  }
  if ((strcasecmp(s, "brightgreen") == 0) || (strcmp(s, "92") == 0))
  {
    return 92;
  }
  if ((strcasecmp(s, "brightyellow") == 0) || (strcmp(s, "93") == 0))
  {
    return 93;
  }
  if ((strcasecmp(s, "brightblue") == 0) || (strcmp(s, "94") == 0))
  {
    return 94;
  }
  if ((strcasecmp(s, "brightmagenta") == 0) || (strcmp(s, "95") == 0))
  {
    return 95;
  }
  if ((strcasecmp(s, "brightcyan") == 0) || (strcmp(s, "96") == 0))
  {
    return 96;
  }
  if ((strcasecmp(s, "brightwhite") == 0) || (strcmp(s, "97") == 0))
  {
    return 97;
  }
  return -1;
}


/*** DEPENDENCIES:
long long strtonum(const char *numstr, long long minval, long long maxval, const char **errstrp)
{
  long long ll = 0;
  char *ep;
  int error = 0;
  struct errval
  {
    const char *errstr;
    int err;
  } ev[4] = {{0, 0}, {"invalid", EINVAL}, {"too small", ERANGE}, {"too large", ERANGE}};
  ev[0].err = errno;
  errno = 0;
  if (minval > maxval)
  {
    error = 1;
  }
  else
  {
    ll = strtoll(numstr, &ep, 10);
    if ((numstr == ep) || ((*ep) != '\0'))
    {
      error = 1;
    }
    else
      if (((ll == LLONG_MIN) && (errno == ERANGE)) || (ll < minval))
    {
      error = 2;
    }
    else
      if (((ll == LLONG_MAX) && (errno == ERANGE)) || (ll > maxval))
    {
      error = 3;
    }
  }
  if (errstrp != 0)
  {
    *errstrp = ev[error].errstr;
  }
  errno = ev[error].err;
  if (error)
  {
    ll = 0;
  }
  return ll;
}


----------------------------
int colour_join_rgb(u_char r, u_char g, u_char b)
{
  return (((((int) (r & 0xff)) << 16) | (((int) (g & 0xff)) << 8)) | ((int) (b & 0xff))) | 0x02000000;
}


----------------------------
***/


