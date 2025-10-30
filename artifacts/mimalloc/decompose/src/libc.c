char _mi_toupper(char c)
{
  if ((c >= 'a') && (c <= 'z'))
  {
    return (c - 'a') + 'A';
  }
  else
    return c;
}


/*** DEPENDENCIES:
***/


void _mi_strlcpy(char *dest, const char *src, size_t dest_size)
{
  unsigned int src_idx = 0;
  unsigned int dest_idx = 0;
  if ((((&dest[dest_idx]) == 0) || ((&src[src_idx]) == 0)) || (dest_size == 0))
  {
    return;
  }
  while ((src[src_idx] != 0) && (dest_size > 1))
  {
    dest[dest_idx] = src[src_idx];
    src_idx += 1;
    dest_idx += 1;
    dest_size -= 1;
  }

  dest[dest_idx] = 0;
}


/*** DEPENDENCIES:
***/


size_t _mi_strlen(const char *s)
{
  if (s == 0)
  {
    return 0;
  }
  size_t len = 0;
  while (s[len] != 0)
  {
    len += 1;
  }

  return len;
}


/*** DEPENDENCIES:
***/


size_t _mi_strnlen(const char *s, size_t max_len)
{
  if (s == 0)
  {
    return 0;
  }
  size_t len = 0;
  while ((s[len] != 0) && (len < max_len))
  {
    len += 1;
  }

  return len;
}


/*** DEPENDENCIES:
***/


static void mi_outc(char c, char **out, char *end)
{
  char *p = *out;
  if (p >= end)
  {
    return;
  }
  *p = c;
  *out = p + 1;
}


/*** DEPENDENCIES:
***/


static void mi_outs(const char *s, char **out, char *end)
{
  unsigned int s_idx = 0;
  if ((&s[s_idx]) == 0)
  {
    return;
  }
  char *p = *out;
  unsigned int p_idx = 0;
  while ((s[s_idx] != 0) && ((&p[p_idx]) < end))
  {
    p[p_idx] = s[s_idx];
    s_idx += 1;
    p_idx += 1;
  }

  *out = &p[p_idx];
}


/*** DEPENDENCIES:
***/


static void mi_out_fill(char fill, size_t len, char **out, char *end)
{
  char *p = *out;
  unsigned int p_idx = 0;
  for (size_t i = 0; (i < len) && ((&p[p_idx]) < end); i += 1)
  {
    p[p_idx] = fill;
    p_idx += 1;
  }

  *out = &p[p_idx];
}


/*** DEPENDENCIES:
***/


static void mi_out_alignright(char fill, char *start, size_t len, size_t extra, char *end)
{
  if ((len == 0) || (extra == 0))
  {
    return;
  }
  if (((start + len) + extra) >= end)
  {
    return;
  }
  for (size_t i = 1; i <= len; i += 1)
  {
    start[(len + extra) - i] = start[len - i];
  }

  for (size_t i = 0; i < extra; i += 1)
  {
    start[i] = fill;
  }

}


/*** DEPENDENCIES:
***/


static size_t mi_byte_sum64(uint64_t x)
{
  x += x << 8;
  x += x << 16;
  x += x << 32;
  return (size_t) (x >> 56);
}


/*** DEPENDENCIES:
***/


// hint:  ['in_idx_ref is a mutable refrence to unsigned int', 'c_ref is a mutable refrence to char', 'numtype_ref is a mutable refrence to char']
void helper_helper_helper__mi_vsnprintf_1_1_1(unsigned int * const in_idx_ref, char * const c_ref, char * const numtype_ref, const char * const in)
{
  unsigned int in_idx = *in_idx_ref;
  char c = *c_ref;
  char numtype = *numtype_ref;
  numtype = c;
  c = in[in_idx];
  if (c == 0)
  {
    break;
  }
  in_idx += 1;
  ;
  if (c == 'l')
  {
    numtype = 'L';
    c = in[in_idx];
    if (c == 0)
    {
      break;
    }
    in_idx += 1;
    ;
  }
  *in_idx_ref = in_idx;
  *c_ref = c;
  *numtype_ref = numtype;
}


/*** DEPENDENCIES:
***/


// hint:  ['in_idx_ref is a mutable refrence to unsigned int', 'c_ref is a mutable refrence to char', 'width_ref is a mutable refrence to size_t']
void helper_helper_helper__mi_vsnprintf_1_1_3(unsigned int * const in_idx_ref, char * const c_ref, size_t * const width_ref, const char * const in)
{
  unsigned int in_idx = *in_idx_ref;
  char c = *c_ref;
  size_t width = *width_ref;
  width = c - '0';
  c = in[in_idx];
  if (c == 0)
  {
    break;
  }
  in_idx += 1;
  ;
  while ((c >= '0') && (c <= '9'))
  {
    width = (10 * width) + (c - '0');
    c = in[in_idx];
    if (c == 0)
    {
      break;
    }
    in_idx += 1;
    ;
  }

  if (c == 0)
  {
    break;
  }
  *in_idx_ref = in_idx;
  *c_ref = c;
  *width_ref = width;
}


/*** DEPENDENCIES:
***/


static void mi_out_num(uintmax_t x, size_t base, char prefix, char **out, char *end)
{
  if (((x == 0) || (base == 0)) || (base > 16))
  {
    if (prefix != 0)
    {
      mi_outc(prefix, out, end);
    }
    mi_outc('0', out, end);
  }
  else
  {
    char *start = *out;
    while (x > 0)
    {
      char digit = (char) (x % base);
      mi_outc((digit <= 9) ? ('0' + digit) : (('A' + digit) - 10), out, end);
      x = x / base;
    }

    if (prefix != 0)
    {
      mi_outc(prefix, out, end);
    }
    size_t len = (*out) - start;
    for (size_t i = 0; i < (len / 2); i += 1)
    {
      char c = start[(len - i) - 1];
      start[(len - i) - 1] = start[i];
      start[i] = c;
    }

  }
}


/*** DEPENDENCIES:
static void mi_outc(char c, char **out, char *end)
{
  char *p = *out;
  if (p >= end)
  {
    return;
  }
  *p = c;
  *out = p + 1;
}


----------------------------
***/


void helper_helper_helper__mi_vsnprintf_1_1_2(va_list args, char * const end, char * const out, char numtype, char numplus)
{
  intmax_t x = 0;
  if (numtype == 'z')
  {
    x = __builtin_va_arg(args);
  }
  else
    if (numtype == 't')
  {
    x = __builtin_va_arg(args);
  }
  else
    if (numtype == 'L')
  {
    x = __builtin_va_arg(args);
  }
  else
    if (numtype == 'l')
  {
    x = __builtin_va_arg(args);
  }
  else
    x = __builtin_va_arg(args);
  char pre = 0;
  if (x < 0)
  {
    pre = '-';
    if (x > INTMAX_MIN)
    {
      x = -x;
    }
  }
  else
    if (numplus != 0)
  {
    pre = numplus;
  }
  mi_out_num((uintmax_t) x, 10, pre, &out, end);
}


/*** DEPENDENCIES:
static void mi_out_num(uintmax_t x, size_t base, char prefix, char **out, char *end)
{
  if (((x == 0) || (base == 0)) || (base > 16))
  {
    if (prefix != 0)
    {
      mi_outc(prefix, out, end);
    }
    mi_outc('0', out, end);
  }
  else
  {
    char *start = *out;
    while (x > 0)
    {
      char digit = (char) (x % base);
      mi_outc((digit <= 9) ? ('0' + digit) : (('A' + digit) - 10), out, end);
      x = x / base;
    }

    if (prefix != 0)
    {
      mi_outc(prefix, out, end);
    }
    size_t len = (*out) - start;
    for (size_t i = 0; i < (len / 2); i += 1)
    {
      char c = start[(len - i) - 1];
      start[(len - i) - 1] = start[i];
      start[i] = c;
    }

  }
}


----------------------------
***/


// hint:  ['fill_ref is a mutable refrence to char', 'width_ref is a mutable refrence to size_t', 'start_idx_ref is a mutable refrence to unsigned int']
void helper_helper_helper__mi_vsnprintf_1_1_4(char * const fill_ref, size_t * const width_ref, unsigned int * const start_idx_ref, va_list args, char * const end, char * const out, char c, char numtype, char numplus)
{
  char fill = *fill_ref;
  size_t width = *width_ref;
  unsigned int start_idx = *start_idx_ref;
  uintmax_t x = 0;
  if ((c == 'x') || (c == 'u'))
  {
    if (numtype == 'z')
    {
      x = __builtin_va_arg(args);
    }
    else
      if (numtype == 't')
    {
      x = __builtin_va_arg(args);
    }
    else
      if (numtype == 'L')
    {
      x = __builtin_va_arg(args);
    }
    else
      if (numtype == 'l')
    {
      x = __builtin_va_arg(args);
    }
    else
      x = __builtin_va_arg(args);
  }
  else
    if (c == 'p')
  {
    x = __builtin_va_arg(args);
    mi_outs("0x", &out, end);
    start_idx = out;
    width = (width >= 2) ? (width - 2) : (0);
  }
  if ((width == 0) && ((c == 'x') || (c == 'p')))
  {
    if (c == 'p')
    {
      width = 2 * ((x <= UINT32_MAX) ? (4) : (((x >> 16) <= UINT32_MAX) ? (6) : (sizeof(void *))));
    }
    if (width == 0)
    {
      width = 2;
    }
    fill = '0';
  }
  mi_out_num(x, ((c == 'x') || (c == 'p')) ? (16) : (10), numplus, &out, end);
  *fill_ref = fill;
  *width_ref = width;
  *start_idx_ref = start_idx;
}


/*** DEPENDENCIES:
static void mi_out_num(uintmax_t x, size_t base, char prefix, char **out, char *end)
{
  if (((x == 0) || (base == 0)) || (base > 16))
  {
    if (prefix != 0)
    {
      mi_outc(prefix, out, end);
    }
    mi_outc('0', out, end);
  }
  else
  {
    char *start = *out;
    while (x > 0)
    {
      char digit = (char) (x % base);
      mi_outc((digit <= 9) ? ('0' + digit) : (('A' + digit) - 10), out, end);
      x = x / base;
    }

    if (prefix != 0)
    {
      mi_outc(prefix, out, end);
    }
    size_t len = (*out) - start;
    for (size_t i = 0; i < (len / 2); i += 1)
    {
      char c = start[(len - i) - 1];
      start[(len - i) - 1] = start[i];
      start[i] = c;
    }

  }
}


----------------------------
static void mi_outs(const char *s, char **out, char *end)
{
  unsigned int s_idx = 0;
  if ((&s[s_idx]) == 0)
  {
    return;
  }
  char *p = *out;
  unsigned int p_idx = 0;
  while ((s[s_idx] != 0) && ((&p[p_idx]) < end))
  {
    p[p_idx] = s[s_idx];
    s_idx += 1;
    p_idx += 1;
  }

  *out = &p[p_idx];
}


----------------------------
***/


int _mi_strnicmp(const char *s, const char *t, size_t n)
{
  unsigned int t_idx = 0;
  unsigned int s_idx = 0;
  if (n == 0)
  {
    return 0;
  }
  for (; ((s[s_idx] != 0) && (t[t_idx] != 0)) && (n > 0); s_idx += 1, t_idx += 1, n -= 1)
  {
    if (_mi_toupper(*(&s[s_idx])) != _mi_toupper(*(&t[t_idx])))
    {
      break;
    }
  }

  return (n == 0) ? (0) : (s[s_idx] - t[t_idx]);
}


/*** DEPENDENCIES:
char _mi_toupper(char c)
{
  if ((c >= 'a') && (c <= 'z'))
  {
    return (c - 'a') + 'A';
  }
  else
    return c;
}


----------------------------
***/


bool _mi_getenv(const char *name, char *result, size_t result_size)
{
  if (((name == 0) || (result == 0)) || (result_size < 64))
  {
    return 0;
  }
  return _mi_prim_getenv(name, result, result_size);
}


/*** DEPENDENCIES:
bool _mi_prim_getenv(const char *name, char *result, size_t result_size)
{
  if (name == 0)
  {
    return 0;
  }
  const size_t len = _mi_strlen(name);
  if (len == 0)
  {
    return 0;
  }
  char **env = mi_get_environ();
  if (env == 0)
  {
    return 0;
  }
  for (int i = 0; (i < 10000) && (env[i] != 0); i += 1)
  {
    const char *s = env[i];
    if ((_mi_strnicmp(name, s, len) == 0) && (s[len] == '='))
    {
      _mi_strlcpy(result, (s + len) + 1, result_size);
      return 1;
    }
  }

  return 0;
}


----------------------------
***/


void _mi_strlcat(char *dest, const char *src, size_t dest_size)
{
  unsigned int dest_idx = 0;
  if ((((&dest[dest_idx]) == 0) || (src == 0)) || (dest_size == 0))
  {
    return;
  }
  while ((dest[dest_idx] != 0) && (dest_size > 1))
  {
    dest_idx += 1;
    dest_size -= 1;
  }

  _mi_strlcpy(dest, src, dest_size);
}


/*** DEPENDENCIES:
void _mi_strlcpy(char *dest, const char *src, size_t dest_size)
{
  unsigned int src_idx = 0;
  unsigned int dest_idx = 0;
  if ((((&dest[dest_idx]) == 0) || ((&src[src_idx]) == 0)) || (dest_size == 0))
  {
    return;
  }
  while ((src[src_idx] != 0) && (dest_size > 1))
  {
    dest[dest_idx] = src[src_idx];
    src_idx += 1;
    dest_idx += 1;
    dest_size -= 1;
  }

  dest[dest_idx] = 0;
}


----------------------------
***/


int _mi_snprintf(char *buf, size_t buflen, const char *fmt, ...)
{
  va_list args;
  __builtin_va_start(args);
  const int written = _mi_vsnprintf(buf, buflen, fmt, args);
  ;
  return written;
}


/*** DEPENDENCIES:
None
----------------------------
***/


static size_t mi_popcount_generic64(uint64_t x)
{
  x = x - ((x >> 1) & 0x5555555555555555);
  x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
  x = (x + (x >> 4)) & 0x0F0F0F0F0F0F0F0F;
  return mi_byte_sum64(x);
}


/*** DEPENDENCIES:
static size_t mi_byte_sum64(uint64_t x)
{
  x += x << 8;
  x += x << 16;
  x += x << 32;
  return (size_t) (x >> 56);
}


----------------------------
***/


size_t _mi_popcount_generic(size_t x)
{
  return mi_popcount_generic64(x);
}


/*** DEPENDENCIES:
static size_t mi_popcount_generic64(uint64_t x)
{
  x = x - ((x >> 1) & 0x5555555555555555);
  x = (x & 0x3333333333333333) + ((x >> 2) & 0x3333333333333333);
  x = (x + (x >> 4)) & 0x0F0F0F0F0F0F0F0F;
  return mi_byte_sum64(x);
}


----------------------------
***/


