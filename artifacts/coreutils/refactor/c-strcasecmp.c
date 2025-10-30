#include <assert.h>
#include <c-ctype.h>
#include <c-strcase.h>
#include <c-strcasecmp.c>
#include <config.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>

extern int c_strcasecmp(const char *s1, const char *s2);
extern int c_strncasecmp(const char *s1, const char *s2, size_t n);
inline bool c_isalnum(int c)
{
  switch (c)
  {
    case '0':

    case '1':

    case '2':

    case '3':

    case '4':

    case '5':

    case '6':

    case '7':

    case '8':

    case '9':

    case 'a' + 0:

    case 'b' + 0:

    case 'c' + 0:

    case 'd' + 0:

    case 'e' + 0:

    case 'f' + 0:

    case 'g' + 0:

    case 'h' + 0:

    case 'i' + 0:

    case 'j' + 0:

    case 'k' + 0:

    case 'l' + 0:

    case 'm' + 0:

    case 'n' + 0:

    case 'o' + 0:

    case 'p' + 0:

    case 'q' + 0:

    case 'r' + 0:

    case 's' + 0:

    case 't' + 0:

    case 'u' + 0:

    case 'v' + 0:

    case 'w' + 0:

    case 'x' + 0:

    case 'y' + 0:

    case 'z' + 0:

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
      return 1;

    default:
      return 0;

  }

}

inline bool c_isalpha(int c)
{
  switch (c)
  {
    case 'a' + 0:

    case 'b' + 0:

    case 'c' + 0:

    case 'd' + 0:

    case 'e' + 0:

    case 'f' + 0:

    case 'g' + 0:

    case 'h' + 0:

    case 'i' + 0:

    case 'j' + 0:

    case 'k' + 0:

    case 'l' + 0:

    case 'm' + 0:

    case 'n' + 0:

    case 'o' + 0:

    case 'p' + 0:

    case 'q' + 0:

    case 'r' + 0:

    case 's' + 0:

    case 't' + 0:

    case 'u' + 0:

    case 'v' + 0:

    case 'w' + 0:

    case 'x' + 0:

    case 'y' + 0:

    case 'z' + 0:

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
      return 1;

    default:
      return 0;

  }

}

inline bool c_isascii(int c)
{
  switch (c)
  {
    case ' ':

    case '\a':

    case '\b':

    case '\f':

    case '\n':

    case '\r':

    case '\t':

    case '\v':

    case '\x00':

    case '\x01':

    case '\x02':

    case '\x03':

    case '\x04':

    case '\x05':

    case '\x06':

    case '\x0e':

    case '\x0f':

    case '\x10':

    case '\x11':

    case '\x12':

    case '\x13':

    case '\x14':

    case '\x15':

    case '\x16':

    case '\x17':

    case '\x18':

    case '\x19':

    case '\x1a':

    case '\x1b':

    case '\x1c':

    case '\x1d':

    case '\x1e':

    case '\x1f':

    case '\x7f':

    case '0':

    case '1':

    case '2':

    case '3':

    case '4':

    case '5':

    case '6':

    case '7':

    case '8':

    case '9':

    case 'a' + 0:

    case 'b' + 0:

    case 'c' + 0:

    case 'd' + 0:

    case 'e' + 0:

    case 'f' + 0:

    case 'g' + 0:

    case 'h' + 0:

    case 'i' + 0:

    case 'j' + 0:

    case 'k' + 0:

    case 'l' + 0:

    case 'm' + 0:

    case 'n' + 0:

    case 'o' + 0:

    case 'p' + 0:

    case 'q' + 0:

    case 'r' + 0:

    case 's' + 0:

    case 't' + 0:

    case 'u' + 0:

    case 'v' + 0:

    case 'w' + 0:

    case 'x' + 0:

    case 'y' + 0:

    case 'z' + 0:

    case '!':

    case '"':

    case '#':

    case '$':

    case '%':

    case '&':

    case '\'':

    case '(':

    case ')':

    case '*':

    case '+':

    case ',':

    case '-':

    case '.':

    case '/':

    case ':':

    case ';':

    case '<':

    case '=':

    case '>':

    case '?':

    case '@':

    case '[':

    case '\\':

    case ']':

    case '^':

    case '_':

    case '`':

    case '{':

    case '|':

    case '}':

    case '~':

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
      return 1;

    default:
      return 0;

  }

}

inline bool c_isblank(int c)
{
  return (c == ' ') || (c == '\t');
}

inline bool c_iscntrl(int c)
{
  switch (c)
  {
    case '\a':

    case '\b':

    case '\f':

    case '\n':

    case '\r':

    case '\t':

    case '\v':

    case '\x00':

    case '\x01':

    case '\x02':

    case '\x03':

    case '\x04':

    case '\x05':

    case '\x06':

    case '\x0e':

    case '\x0f':

    case '\x10':

    case '\x11':

    case '\x12':

    case '\x13':

    case '\x14':

    case '\x15':

    case '\x16':

    case '\x17':

    case '\x18':

    case '\x19':

    case '\x1a':

    case '\x1b':

    case '\x1c':

    case '\x1d':

    case '\x1e':

    case '\x1f':

    case '\x7f':
      return 1;

    default:
      return 0;

  }

}

inline bool c_isdigit(int c)
{
  switch (c)
  {
    case '0':

    case '1':

    case '2':

    case '3':

    case '4':

    case '5':

    case '6':

    case '7':

    case '8':

    case '9':
      return 1;

    default:
      return 0;

  }

}

inline bool c_isgraph(int c)
{
  switch (c)
  {
    case '0':

    case '1':

    case '2':

    case '3':

    case '4':

    case '5':

    case '6':

    case '7':

    case '8':

    case '9':

    case 'a' + 0:

    case 'b' + 0:

    case 'c' + 0:

    case 'd' + 0:

    case 'e' + 0:

    case 'f' + 0:

    case 'g' + 0:

    case 'h' + 0:

    case 'i' + 0:

    case 'j' + 0:

    case 'k' + 0:

    case 'l' + 0:

    case 'm' + 0:

    case 'n' + 0:

    case 'o' + 0:

    case 'p' + 0:

    case 'q' + 0:

    case 'r' + 0:

    case 's' + 0:

    case 't' + 0:

    case 'u' + 0:

    case 'v' + 0:

    case 'w' + 0:

    case 'x' + 0:

    case 'y' + 0:

    case 'z' + 0:

    case '!':

    case '"':

    case '#':

    case '$':

    case '%':

    case '&':

    case '\'':

    case '(':

    case ')':

    case '*':

    case '+':

    case ',':

    case '-':

    case '.':

    case '/':

    case ':':

    case ';':

    case '<':

    case '=':

    case '>':

    case '?':

    case '@':

    case '[':

    case '\\':

    case ']':

    case '^':

    case '_':

    case '`':

    case '{':

    case '|':

    case '}':

    case '~':

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
      return 1;

    default:
      return 0;

  }

}

inline bool c_islower(int c)
{
  switch (c)
  {
    case 'a' + 0:

    case 'b' + 0:

    case 'c' + 0:

    case 'd' + 0:

    case 'e' + 0:

    case 'f' + 0:

    case 'g' + 0:

    case 'h' + 0:

    case 'i' + 0:

    case 'j' + 0:

    case 'k' + 0:

    case 'l' + 0:

    case 'm' + 0:

    case 'n' + 0:

    case 'o' + 0:

    case 'p' + 0:

    case 'q' + 0:

    case 'r' + 0:

    case 's' + 0:

    case 't' + 0:

    case 'u' + 0:

    case 'v' + 0:

    case 'w' + 0:

    case 'x' + 0:

    case 'y' + 0:

    case 'z' + 0:
      return 1;

    default:
      return 0;

  }

}

inline bool c_isprint(int c)
{
  switch (c)
  {
    case ' ':

    case '0':

    case '1':

    case '2':

    case '3':

    case '4':

    case '5':

    case '6':

    case '7':

    case '8':

    case '9':

    case 'a' + 0:

    case 'b' + 0:

    case 'c' + 0:

    case 'd' + 0:

    case 'e' + 0:

    case 'f' + 0:

    case 'g' + 0:

    case 'h' + 0:

    case 'i' + 0:

    case 'j' + 0:

    case 'k' + 0:

    case 'l' + 0:

    case 'm' + 0:

    case 'n' + 0:

    case 'o' + 0:

    case 'p' + 0:

    case 'q' + 0:

    case 'r' + 0:

    case 's' + 0:

    case 't' + 0:

    case 'u' + 0:

    case 'v' + 0:

    case 'w' + 0:

    case 'x' + 0:

    case 'y' + 0:

    case 'z' + 0:

    case '!':

    case '"':

    case '#':

    case '$':

    case '%':

    case '&':

    case '\'':

    case '(':

    case ')':

    case '*':

    case '+':

    case ',':

    case '-':

    case '.':

    case '/':

    case ':':

    case ';':

    case '<':

    case '=':

    case '>':

    case '?':

    case '@':

    case '[':

    case '\\':

    case ']':

    case '^':

    case '_':

    case '`':

    case '{':

    case '|':

    case '}':

    case '~':

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
      return 1;

    default:
      return 0;

  }

}

inline bool c_ispunct(int c)
{
  switch (c)
  {
    case '!':

    case '"':

    case '#':

    case '$':

    case '%':

    case '&':

    case '\'':

    case '(':

    case ')':

    case '*':

    case '+':

    case ',':

    case '-':

    case '.':

    case '/':

    case ':':

    case ';':

    case '<':

    case '=':

    case '>':

    case '?':

    case '@':

    case '[':

    case '\\':

    case ']':

    case '^':

    case '_':

    case '`':

    case '{':

    case '|':

    case '}':

    case '~':
      return 1;

    default:
      return 0;

  }

}

inline bool c_isspace(int c)
{
  switch (c)
  {
    case ' ':

    case '\t':

    case '\n':

    case '\v':

    case '\f':

    case '\r':
      return 1;

    default:
      return 0;

  }

}

inline bool c_isupper(int c)
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
      return 1;

    default:
      return 0;

  }

}

inline bool c_isxdigit(int c)
{
  switch (c)
  {
    case '0':

    case '1':

    case '2':

    case '3':

    case '4':

    case '5':

    case '6':

    case '7':

    case '8':

    case '9':

    case 'a' + 0:

    case 'b' + 0:

    case 'c' + 0:

    case 'd' + 0:

    case 'e' + 0:

    case 'f' + 0:

    case 'a' + ('A' - 'a'):

    case 'b' + ('A' - 'a'):

    case 'c' + ('A' - 'a'):

    case 'd' + ('A' - 'a'):

    case 'e' + ('A' - 'a'):

    case 'f' + ('A' - 'a'):
      return 1;

    default:
      return 0;

  }

}

inline int c_tolower(int c)
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
      return (c - 'A') + 'a';

    default:
      return c;

  }

}

inline int c_toupper(int c)
{
  switch (c)
  {
    case 'a' + 0:

    case 'b' + 0:

    case 'c' + 0:

    case 'd' + 0:

    case 'e' + 0:

    case 'f' + 0:

    case 'g' + 0:

    case 'h' + 0:

    case 'i' + 0:

    case 'j' + 0:

    case 'k' + 0:

    case 'l' + 0:

    case 'm' + 0:

    case 'n' + 0:

    case 'o' + 0:

    case 'p' + 0:

    case 'q' + 0:

    case 'r' + 0:

    case 's' + 0:

    case 't' + 0:

    case 'u' + 0:

    case 'v' + 0:

    case 'w' + 0:

    case 'x' + 0:

    case 'y' + 0:

    case 'z' + 0:
      return (c - 'a') + 'A';

    default:
      return c;

  }

}

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


extern int c_strcasecmp(const char *s1, const char *s2);
extern int c_strncasecmp(const char *s1, const char *s2, size_t n);
inline bool c_isalnum(int c)
{
  switch (c)
  {
    case '0':

    case '1':

    case '2':

    case '3':

    case '4':

    case '5':

    case '6':

    case '7':

    case '8':

    case '9':

    case 'a' + 0:

    case 'b' + 0:

    case 'c' + 0:

    case 'd' + 0:

    case 'e' + 0:

    case 'f' + 0:

    case 'g' + 0:

    case 'h' + 0:

    case 'i' + 0:

    case 'j' + 0:

    case 'k' + 0:

    case 'l' + 0:

    case 'm' + 0:

    case 'n' + 0:

    case 'o' + 0:

    case 'p' + 0:

    case 'q' + 0:

    case 'r' + 0:

    case 's' + 0:

    case 't' + 0:

    case 'u' + 0:

    case 'v' + 0:

    case 'w' + 0:

    case 'x' + 0:

    case 'y' + 0:

    case 'z' + 0:

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
      return 1;

    default:
      return 0;

  }

}

inline bool c_isalpha(int c)
{
  switch (c)
  {
    case 'a' + 0:

    case 'b' + 0:

    case 'c' + 0:

    case 'd' + 0:

    case 'e' + 0:

    case 'f' + 0:

    case 'g' + 0:

    case 'h' + 0:

    case 'i' + 0:

    case 'j' + 0:

    case 'k' + 0:

    case 'l' + 0:

    case 'm' + 0:

    case 'n' + 0:

    case 'o' + 0:

    case 'p' + 0:

    case 'q' + 0:

    case 'r' + 0:

    case 's' + 0:

    case 't' + 0:

    case 'u' + 0:

    case 'v' + 0:

    case 'w' + 0:

    case 'x' + 0:

    case 'y' + 0:

    case 'z' + 0:

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
      return 1;

    default:
      return 0;

  }

}

inline bool c_isascii(int c)
{
  switch (c)
  {
    case ' ':

    case '\a':

    case '\b':

    case '\f':

    case '\n':

    case '\r':

    case '\t':

    case '\v':

    case '\x00':

    case '\x01':

    case '\x02':

    case '\x03':

    case '\x04':

    case '\x05':

    case '\x06':

    case '\x0e':

    case '\x0f':

    case '\x10':

    case '\x11':

    case '\x12':

    case '\x13':

    case '\x14':

    case '\x15':

    case '\x16':

    case '\x17':

    case '\x18':

    case '\x19':

    case '\x1a':

    case '\x1b':

    case '\x1c':

    case '\x1d':

    case '\x1e':

    case '\x1f':

    case '\x7f':

    case '0':

    case '1':

    case '2':

    case '3':

    case '4':

    case '5':

    case '6':

    case '7':

    case '8':

    case '9':

    case 'a' + 0:

    case 'b' + 0:

    case 'c' + 0:

    case 'd' + 0:

    case 'e' + 0:

    case 'f' + 0:

    case 'g' + 0:

    case 'h' + 0:

    case 'i' + 0:

    case 'j' + 0:

    case 'k' + 0:

    case 'l' + 0:

    case 'm' + 0:

    case 'n' + 0:

    case 'o' + 0:

    case 'p' + 0:

    case 'q' + 0:

    case 'r' + 0:

    case 's' + 0:

    case 't' + 0:

    case 'u' + 0:

    case 'v' + 0:

    case 'w' + 0:

    case 'x' + 0:

    case 'y' + 0:

    case 'z' + 0:

    case '!':

    case '"':

    case '#':

    case '$':

    case '%':

    case '&':

    case '\'':

    case '(':

    case ')':

    case '*':

    case '+':

    case ',':

    case '-':

    case '.':

    case '/':

    case ':':

    case ';':

    case '<':

    case '=':

    case '>':

    case '?':

    case '@':

    case '[':

    case '\\':

    case ']':

    case '^':

    case '_':

    case '`':

    case '{':

    case '|':

    case '}':

    case '~':

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
      return 1;

    default:
      return 0;

  }

}

inline bool c_isblank(int c)
{
  return (c == ' ') || (c == '\t');
}

inline bool c_iscntrl(int c)
{
  switch (c)
  {
    case '\a':

    case '\b':

    case '\f':

    case '\n':

    case '\r':

    case '\t':

    case '\v':

    case '\x00':

    case '\x01':

    case '\x02':

    case '\x03':

    case '\x04':

    case '\x05':

    case '\x06':

    case '\x0e':

    case '\x0f':

    case '\x10':

    case '\x11':

    case '\x12':

    case '\x13':

    case '\x14':

    case '\x15':

    case '\x16':

    case '\x17':

    case '\x18':

    case '\x19':

    case '\x1a':

    case '\x1b':

    case '\x1c':

    case '\x1d':

    case '\x1e':

    case '\x1f':

    case '\x7f':
      return 1;

    default:
      return 0;

  }

}

inline bool c_isdigit(int c)
{
  switch (c)
  {
    case '0':

    case '1':

    case '2':

    case '3':

    case '4':

    case '5':

    case '6':

    case '7':

    case '8':

    case '9':
      return 1;

    default:
      return 0;

  }

}

inline bool c_isgraph(int c)
{
  switch (c)
  {
    case '0':

    case '1':

    case '2':

    case '3':

    case '4':

    case '5':

    case '6':

    case '7':

    case '8':

    case '9':

    case 'a' + 0:

    case 'b' + 0:

    case 'c' + 0:

    case 'd' + 0:

    case 'e' + 0:

    case 'f' + 0:

    case 'g' + 0:

    case 'h' + 0:

    case 'i' + 0:

    case 'j' + 0:

    case 'k' + 0:

    case 'l' + 0:

    case 'm' + 0:

    case 'n' + 0:

    case 'o' + 0:

    case 'p' + 0:

    case 'q' + 0:

    case 'r' + 0:

    case 's' + 0:

    case 't' + 0:

    case 'u' + 0:

    case 'v' + 0:

    case 'w' + 0:

    case 'x' + 0:

    case 'y' + 0:

    case 'z' + 0:

    case '!':

    case '"':

    case '#':

    case '$':

    case '%':

    case '&':

    case '\'':

    case '(':

    case ')':

    case '*':

    case '+':

    case ',':

    case '-':

    case '.':

    case '/':

    case ':':

    case ';':

    case '<':

    case '=':

    case '>':

    case '?':

    case '@':

    case '[':

    case '\\':

    case ']':

    case '^':

    case '_':

    case '`':

    case '{':

    case '|':

    case '}':

    case '~':

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
      return 1;

    default:
      return 0;

  }

}

inline bool c_islower(int c)
{
  switch (c)
  {
    case 'a' + 0:

    case 'b' + 0:

    case 'c' + 0:

    case 'd' + 0:

    case 'e' + 0:

    case 'f' + 0:

    case 'g' + 0:

    case 'h' + 0:

    case 'i' + 0:

    case 'j' + 0:

    case 'k' + 0:

    case 'l' + 0:

    case 'm' + 0:

    case 'n' + 0:

    case 'o' + 0:

    case 'p' + 0:

    case 'q' + 0:

    case 'r' + 0:

    case 's' + 0:

    case 't' + 0:

    case 'u' + 0:

    case 'v' + 0:

    case 'w' + 0:

    case 'x' + 0:

    case 'y' + 0:

    case 'z' + 0:
      return 1;

    default:
      return 0;

  }

}

inline bool c_isprint(int c)
{
  switch (c)
  {
    case ' ':

    case '0':

    case '1':

    case '2':

    case '3':

    case '4':

    case '5':

    case '6':

    case '7':

    case '8':

    case '9':

    case 'a' + 0:

    case 'b' + 0:

    case 'c' + 0:

    case 'd' + 0:

    case 'e' + 0:

    case 'f' + 0:

    case 'g' + 0:

    case 'h' + 0:

    case 'i' + 0:

    case 'j' + 0:

    case 'k' + 0:

    case 'l' + 0:

    case 'm' + 0:

    case 'n' + 0:

    case 'o' + 0:

    case 'p' + 0:

    case 'q' + 0:

    case 'r' + 0:

    case 's' + 0:

    case 't' + 0:

    case 'u' + 0:

    case 'v' + 0:

    case 'w' + 0:

    case 'x' + 0:

    case 'y' + 0:

    case 'z' + 0:

    case '!':

    case '"':

    case '#':

    case '$':

    case '%':

    case '&':

    case '\'':

    case '(':

    case ')':

    case '*':

    case '+':

    case ',':

    case '-':

    case '.':

    case '/':

    case ':':

    case ';':

    case '<':

    case '=':

    case '>':

    case '?':

    case '@':

    case '[':

    case '\\':

    case ']':

    case '^':

    case '_':

    case '`':

    case '{':

    case '|':

    case '}':

    case '~':

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
      return 1;

    default:
      return 0;

  }

}

inline bool c_ispunct(int c)
{
  switch (c)
  {
    case '!':

    case '"':

    case '#':

    case '$':

    case '%':

    case '&':

    case '\'':

    case '(':

    case ')':

    case '*':

    case '+':

    case ',':

    case '-':

    case '.':

    case '/':

    case ':':

    case ';':

    case '<':

    case '=':

    case '>':

    case '?':

    case '@':

    case '[':

    case '\\':

    case ']':

    case '^':

    case '_':

    case '`':

    case '{':

    case '|':

    case '}':

    case '~':
      return 1;

    default:
      return 0;

  }

}

inline bool c_isspace(int c)
{
  switch (c)
  {
    case ' ':

    case '\t':

    case '\n':

    case '\v':

    case '\f':

    case '\r':
      return 1;

    default:
      return 0;

  }

}

inline bool c_isupper(int c)
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
      return 1;

    default:
      return 0;

  }

}

inline bool c_isxdigit(int c)
{
  switch (c)
  {
    case '0':

    case '1':

    case '2':

    case '3':

    case '4':

    case '5':

    case '6':

    case '7':

    case '8':

    case '9':

    case 'a' + 0:

    case 'b' + 0:

    case 'c' + 0:

    case 'd' + 0:

    case 'e' + 0:

    case 'f' + 0:

    case 'a' + ('A' - 'a'):

    case 'b' + ('A' - 'a'):

    case 'c' + ('A' - 'a'):

    case 'd' + ('A' - 'a'):

    case 'e' + ('A' - 'a'):

    case 'f' + ('A' - 'a'):
      return 1;

    default:
      return 0;

  }

}

inline int c_tolower(int c)
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
      return (c - 'A') + 'a';

    default:
      return c;

  }

}

inline int c_toupper(int c)
{
  switch (c)
  {
    case 'a' + 0:

    case 'b' + 0:

    case 'c' + 0:

    case 'd' + 0:

    case 'e' + 0:

    case 'f' + 0:

    case 'g' + 0:

    case 'h' + 0:

    case 'i' + 0:

    case 'j' + 0:

    case 'k' + 0:

    case 'l' + 0:

    case 'm' + 0:

    case 'n' + 0:

    case 'o' + 0:

    case 'p' + 0:

    case 'q' + 0:

    case 'r' + 0:

    case 's' + 0:

    case 't' + 0:

    case 'u' + 0:

    case 'v' + 0:

    case 'w' + 0:

    case 'x' + 0:

    case 'y' + 0:

    case 'z' + 0:
      return (c - 'a') + 'A';

    default:
      return c;

  }

}

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

