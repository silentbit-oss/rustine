#include <limits.h>
#include <ratio.c>
#include <ratio.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct opng_lratio
{
  long num;
  long denom;
};
struct opng_ulratio
{
  unsigned long num;
  unsigned long denom;
};
int opng_ulratio_to_factor_string(char *buffer, size_t buffer_size, const struct opng_ulratio *ratio);
int opng_ulratio_to_percent_string(char *buffer, size_t buffer_size, const struct opng_ulratio *ratio);
typedef long opng_xlong_impl_t;
typedef unsigned long opng_uxlong_impl_t;
static int opng_snprintf_impl(char *buffer, size_t buffer_size, const char *format, ...)
{
  va_list arg_ptr;
  int result;
  __builtin_va_start(arg_ptr);
  result = vsnprintf(buffer, buffer_size, format, arg_ptr);
  ;
  if ((result < 0) || (((size_t) result) >= buffer_size))
  {
    if (buffer_size > 0)
    {
      buffer[buffer_size - 1] = '\0';
    }
    return -1;
  }
  return result;
}

static int opng_sprint_uratio_impl(char *buffer, size_t buffer_size, opng_uxlong_impl_t num, opng_uxlong_impl_t denom, int always_percent)
{
  opng_uxlong_impl_t integer_part;
  opng_uxlong_impl_t remainder;
  unsigned int fractional_part;
  unsigned int scale;
  double scaled_ratio;
  if (denom == 0)
  {
    return opng_snprintf_impl(buffer, buffer_size, (num == 0) ? ("??%%") : ("INFINITY%%"));
  }
  if ((num < denom) && ((denom / (denom - num)) < 20000))
  {
    scale = 10000;
    scaled_ratio = (((double) num) * ((double) scale)) / ((double) denom);
    fractional_part = (unsigned int) (scaled_ratio + 0.5);
    if (fractional_part >= scale)
    {
      fractional_part = scale - 1;
    }
    return opng_snprintf_impl(buffer, buffer_size, "%u.%02u%%", fractional_part / 100, fractional_part % 100);
  }
  integer_part = num / denom;
  remainder = num % denom;
  scale = 100;
  scaled_ratio = (((double) remainder) * ((double) scale)) / ((double) denom);
  fractional_part = (unsigned int) (scaled_ratio + 0.5);
  if (fractional_part >= scale)
  {
    fractional_part = 0;
    integer_part += 1;
  }
  if (always_percent)
  {
    return opng_snprintf_impl(buffer, buffer_size, "%lu%02u%%", integer_part, fractional_part);
  }
  if (integer_part < 100)
  {
    return opng_snprintf_impl(buffer, buffer_size, "%lu.%02ux", integer_part, fractional_part);
  }
  integer_part = num / denom;
  if (remainder > ((denom - 1) / 2))
  {
    integer_part += 1;
  }
  return opng_snprintf_impl(buffer, buffer_size, "%lux", integer_part);
}

int opng_ulratio_to_factor_string(char *buffer, size_t buffer_size, const struct opng_ulratio *ratio)
{
  opng_uxlong_impl_t num = ratio->num;
  opng_uxlong_impl_t denom = ratio->denom;
  return opng_sprint_uratio_impl(buffer, buffer_size, num, denom, 0);
}

int opng_ulratio_to_percent_string(char *buffer, size_t buffer_size, const struct opng_ulratio *ratio)
{
  opng_uxlong_impl_t num = ratio->num;
  opng_uxlong_impl_t denom = ratio->denom;
  return opng_sprint_uratio_impl(buffer, buffer_size, num, denom, 1);
}


struct opng_lratio
{
  long num;
  long denom;
};
struct opng_ulratio
{
  unsigned long num;
  unsigned long denom;
};
int opng_ulratio_to_factor_string(char *buffer, size_t buffer_size, const struct opng_ulratio *ratio);
int opng_ulratio_to_percent_string(char *buffer, size_t buffer_size, const struct opng_ulratio *ratio);
typedef long opng_xlong_impl_t;
typedef unsigned long opng_uxlong_impl_t;
static int opng_snprintf_impl(char *buffer, size_t buffer_size, const char *format, ...)
{
  va_list arg_ptr;
  int result;
  __builtin_va_start(arg_ptr);
  result = vsnprintf(buffer, buffer_size, format, arg_ptr);
  ;
  if ((result < 0) || (((size_t) result) >= buffer_size))
  {
    if (buffer_size > 0)
    {
      buffer[buffer_size - 1] = '\0';
    }
    return -1;
  }
  return result;
}

static int opng_sprint_uratio_impl(char *buffer, size_t buffer_size, opng_uxlong_impl_t num, opng_uxlong_impl_t denom, int always_percent)
{
  opng_uxlong_impl_t integer_part;
  opng_uxlong_impl_t remainder;
  unsigned int fractional_part;
  unsigned int scale;
  double scaled_ratio;
  if (denom == 0)
  {
    return opng_snprintf_impl(buffer, buffer_size, (num == 0) ? ("??%%") : ("INFINITY%%"));
  }
  if ((num < denom) && ((denom / (denom - num)) < 20000))
  {
    scale = 10000;
    scaled_ratio = (((double) num) * ((double) scale)) / ((double) denom);
    fractional_part = (unsigned int) (scaled_ratio + 0.5);
    if (fractional_part >= scale)
    {
      fractional_part = scale - 1;
    }
    return opng_snprintf_impl(buffer, buffer_size, "%u.%02u%%", fractional_part / 100, fractional_part % 100);
  }
  integer_part = num / denom;
  remainder = num % denom;
  scale = 100;
  scaled_ratio = (((double) remainder) * ((double) scale)) / ((double) denom);
  fractional_part = (unsigned int) (scaled_ratio + 0.5);
  if (fractional_part >= scale)
  {
    fractional_part = 0;
    integer_part += 1;
  }
  if (always_percent)
  {
    return opng_snprintf_impl(buffer, buffer_size, "%lu%02u%%", integer_part, fractional_part);
  }
  if (integer_part < 100)
  {
    return opng_snprintf_impl(buffer, buffer_size, "%lu.%02ux", integer_part, fractional_part);
  }
  integer_part = num / denom;
  if (remainder > ((denom - 1) / 2))
  {
    integer_part += 1;
  }
  return opng_snprintf_impl(buffer, buffer_size, "%lux", integer_part);
}

int opng_ulratio_to_factor_string(char *buffer, size_t buffer_size, const struct opng_ulratio *ratio)
{
  opng_uxlong_impl_t num = ratio->num;
  opng_uxlong_impl_t denom = ratio->denom;
  return opng_sprint_uratio_impl(buffer, buffer_size, num, denom, 0);
}

int opng_ulratio_to_percent_string(char *buffer, size_t buffer_size, const struct opng_ulratio *ratio)
{
  opng_uxlong_impl_t num = ratio->num;
  opng_uxlong_impl_t denom = ratio->denom;
  return opng_sprint_uratio_impl(buffer, buffer_size, num, denom, 1);
}

