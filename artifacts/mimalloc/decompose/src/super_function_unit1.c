// element in merge of:  _mi_assert_fail,_mi_fprintf,_mi_vsnprintf,helper__mi_vsnprintf_1,helper_helper__mi_vsnprintf_1_1,mi_vfprintf
// hint:  ['in_idx_ref is a mutable refrence to unsigned int']
void helper__mi_vsnprintf_1(unsigned int * const in_idx_ref, va_list args, char * const end, const char * const in, char * const out)
{
  unsigned int in_idx = *in_idx_ref;
  if (out >= end)
  {
    break;
  }
  char c;
  c = in[in_idx];
  if (c == 0)
  {
    break;
  }
  in_idx += 1;
  ;
  if (c != '%')
  {
    if (((((c >= ' ') && (c <= '~')) || (c == '\n')) || (c == '\r')) || (c == '\t'))
    {
      mi_outc(c, &out, end);
    }
  }
  else
  {
    helper_helper__mi_vsnprintf_1_1(&in_idx, &c, args, end, in, out);
  }
  *in_idx_ref = in_idx;
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
None
----------------------------
***/


// element in merge of:  _mi_assert_fail,_mi_fprintf,_mi_vsnprintf,helper__mi_vsnprintf_1,helper_helper__mi_vsnprintf_1_1,mi_vfprintf
void _mi_fprintf(mi_output_fun *out, void *arg, const char *fmt, ...)
{
  va_list args;
  __builtin_va_start(args);
  mi_vfprintf(out, arg, 0, fmt, args);
  ;
}


/*** DEPENDENCIES:
typedef void mi_output_fun(const char *msg, void *arg)
----------------------------
None
----------------------------
***/


// element in merge of:  _mi_assert_fail,_mi_fprintf,_mi_vsnprintf,helper__mi_vsnprintf_1,helper_helper__mi_vsnprintf_1_1,mi_vfprintf
int _mi_vsnprintf(char *buf, size_t bufsize, const char *fmt, va_list args)
{
  if (((buf == 0) || (bufsize == 0)) || (fmt == 0))
  {
    return 0;
  }
  buf[bufsize - 1] = 0;
  char * const end = buf + (bufsize - 1);
  const char *in = fmt;
  unsigned int in_idx = 0;
  char *out = buf;
  while (1)
  {
    helper__mi_vsnprintf_1(&in_idx, args, end, in, out);
  }

  (out <= end) ? ((void) 0) : (_mi_assert_fail("out <= end", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/libc.c", 266, __func__));
  *out = 0;
  return (int) (out - buf);
}


/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  _mi_assert_fail,_mi_fprintf,_mi_vsnprintf,helper__mi_vsnprintf_1,helper_helper__mi_vsnprintf_1_1,mi_vfprintf
static void mi_vfprintf(mi_output_fun *out, void *arg, const char *prefix, const char *fmt, va_list args)
{
  char buf[512];
  if (fmt == 0)
  {
    return;
  }
  if (!mi_recurse_enter())
  {
    return;
  }
  _mi_vsnprintf(buf, (sizeof(buf)) - 1, fmt, args);
  mi_recurse_exit();
  _mi_fputs(out, arg, prefix, buf);
}


/*** DEPENDENCIES:
void _mi_fputs(mi_output_fun *out, void *arg, const char *prefix, const char *message)
{
  unsigned int out_idx = 0;
  if ((((&out[out_idx]) == 0) || (((void *) out) == ((void *) stdout))) || (((void *) out) == ((void *) stderr)))
  {
    if (!mi_recurse_enter())
    {
      return;
    }
    out_idx = mi_out_get_default(&arg);
    if (prefix != 0)
    {
      out(prefix, arg);
    }
    out(message, arg);
    mi_recurse_exit();
  }
  else
  {
    if (prefix != 0)
    {
      out(prefix, arg);
    }
    out(message, arg);
  }
}


----------------------------
static void mi_recurse_exit(void)
{
  mi_recurse_exit_prim();
}


----------------------------
static bool mi_recurse_enter(void)
{
  return mi_recurse_enter_prim();
}


----------------------------
typedef void mi_output_fun(const char *msg, void *arg)
----------------------------
None
----------------------------
***/


// element in merge of:  _mi_assert_fail,_mi_fprintf,_mi_vsnprintf,helper__mi_vsnprintf_1,helper_helper__mi_vsnprintf_1_1,mi_vfprintf
void _mi_assert_fail(const char *assertion, const char *fname, unsigned line, const char *func)
{
  _mi_fprintf(0, 0, "mimalloc: assertion failed: at \"%s\":%u, %s\n  assertion: \"%s\"\n", fname, line, (func == 0) ? ("") : (func), assertion);
  abort();
}


/*** DEPENDENCIES:
None
----------------------------
***/


// element in merge of:  _mi_assert_fail,_mi_fprintf,_mi_vsnprintf,helper__mi_vsnprintf_1,helper_helper__mi_vsnprintf_1_1,mi_vfprintf
// hint:  ['in_idx_ref is a mutable refrence to unsigned int', 'c_ref is a mutable refrence to char']
void helper_helper__mi_vsnprintf_1_1(unsigned int * const in_idx_ref, char * const c_ref, va_list args, char * const end, const char * const in, char * const out)
{
  unsigned int in_idx = *in_idx_ref;
  char c = *c_ref;
  c = in[in_idx];
  if (c == 0)
  {
    break;
  }
  in_idx += 1;
  ;
  char fill = ' ';
  size_t width = 0;
  char numtype = 'd';
  char numplus = 0;
  bool alignright = 1;
  if ((c == '+') || (c == ' '))
  {
    numplus = c;
    c = in[in_idx];
    if (c == 0)
    {
      break;
    }
    in_idx += 1;
    ;
  }
  if (c == '-')
  {
    alignright = 0;
    c = in[in_idx];
    if (c == 0)
    {
      break;
    }
    in_idx += 1;
    ;
  }
  if (c == '0')
  {
    fill = '0';
    c = in[in_idx];
    if (c == 0)
    {
      break;
    }
    in_idx += 1;
    ;
  }
  if ((c >= '1') && (c <= '9'))
  {
    helper_helper_helper__mi_vsnprintf_1_1_3(&in_idx, &c, &width, in);
  }
  if (((c == 'z') || (c == 't')) || (c == 'L'))
  {
    numtype = c;
    c = in[in_idx];
    if (c == 0)
    {
      break;
    }
    in_idx += 1;
    ;
  }
  else
    if (c == 'l')
  {
    helper_helper_helper__mi_vsnprintf_1_1_1(&in_idx, &c, &numtype, in);
  }
  char *start = out;
  unsigned int start_idx = 0;
  if (c == 's')
  {
    const char *s = __builtin_va_arg(args);
    mi_outs(s, &out, end);
  }
  else
    if (((c == 'p') || (c == 'x')) || (c == 'u'))
  {
    helper_helper_helper__mi_vsnprintf_1_1_4(&fill, &width, &start_idx, args, end, out, c, numtype, numplus);
  }
  else
    if ((c == 'i') || (c == 'd'))
  {
    helper_helper_helper__mi_vsnprintf_1_1_2(args, end, out, numtype, numplus);
  }
  else
    if ((c >= ' ') && (c <= '~'))
  {
    mi_outc('%', &out, end);
    mi_outc(c, &out, end);
  }
  (out <= end) ? ((void) 0) : (_mi_assert_fail("out <= end", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/libc.c", 255, __func__));
  (out >= (&start[start_idx])) ? ((void) 0) : (_mi_assert_fail("out >= start", "/home/ubuntu/C2RustTranslation/subjects/mimalloc/src/libc.c", 256, __func__));
  const size_t len = out - (&start[start_idx]);
  if (len < width)
  {
    mi_out_fill(fill, width - len, &out, end);
    if (alignright && (out <= end))
    {
      mi_out_alignright(fill, start, len, width - len, end);
    }
  }
  *in_idx_ref = in_idx;
  *c_ref = c;
}


/*** DEPENDENCIES:
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


----------------------------
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


----------------------------
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


----------------------------
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


----------------------------
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


----------------------------
None
----------------------------
***/


