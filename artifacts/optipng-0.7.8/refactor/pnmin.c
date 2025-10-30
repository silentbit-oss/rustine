#include <errno.h>
#include <limits.h>
#include <pnmin.c>
#include <pnmio.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

enum 
{
  PNM_P1 = 1,
  PNM_P2 = 2,
  PNM_P3 = 3,
  PNM_P4 = 4,
  PNM_P5 = 5,
  PNM_P6 = 6,
  PNM_P7 = 7
};
typedef struct pnm_struct
{
  unsigned int format;
  unsigned int depth;
  unsigned int width;
  unsigned int height;
  unsigned int maxval;
} pnm_struct;
int pnm_fget_header(pnm_struct *pnm_ptr, FILE *stream);
int pnm_fget_values(const pnm_struct *pnm_ptr, unsigned int *sample_values, unsigned int num_rows, FILE *stream);
int pnm_fget_bytes(const pnm_struct *pnm_ptr, unsigned char *sample_bytes, size_t sample_size, unsigned int num_rows, FILE *stream);
int pnm_fput_header(const pnm_struct *pnm_ptr, FILE *stream);
int pnm_fput_values(const pnm_struct *pnm_ptr, const unsigned int *sample_values, unsigned int num_rows, FILE *stream);
int pnm_fput_bytes(const pnm_struct *pnm_ptr, const unsigned char *sample_bytes, size_t sample_size, unsigned int num_rows, FILE *stream);
int pnm_is_valid(const pnm_struct *pnm_ptr);
size_t pnm_raw_sample_size(const pnm_struct *pnm_ptr);
size_t pnm_mem_size(const pnm_struct *pnm_ptr, size_t sample_size, unsigned int num_rows);
static int pnm_fget_char(FILE *stream)
{
  int ch = getc(stream);
  if (ch == '#')
  {
    do
    {
      ch = getc(stream);
    }
    while (((ch != EOF) && (ch != '\n')) && (ch != '\r'));
  }
  if (ch == '\r')
  {
    ch = getc(stream);
    if (ch != '\n')
    {
      ungetc(ch, stream);
      ch = '\n';
    }
  }
  return ch;
}

static int pnm_fscan_uint(FILE *stream, unsigned int *value)
{
  int ch;
  unsigned int tmp;
  do
  {
    ch = pnm_fget_char(stream);
  }
  while ((((ch == ' ') || (ch == '\t')) || (ch == '\n')) || (ch == '\r'));
  if (ch == EOF)
  {
    return EOF;
  }
  if (!((ch >= '0') && (ch <= '9')))
  {
    ungetc(ch, stream);
    return 0;
  }
  *value = 0;
  do
  {
    tmp = ((*value) * 10) + (ch - '0');
    if (tmp >= (*value))
    {
      *value = tmp;
    }
    else
    {
      *value = 4294967295U;
      errno = ERANGE;
    }
    ch = getc(stream);
  }
  while ((ch >= '0') && (ch <= '9'));
  if (!((((ch == ' ') || (ch == '\t')) || (ch == '\n')) || (ch == '\r')))
  {
    ungetc(ch, stream);
  }
  return 1;
}

int pnm_fget_header(pnm_struct *pnm_ptr, FILE *stream)
{
  unsigned int format;
  int ch;
  memset(pnm_ptr, 0, sizeof(pnm_struct));
  ch = getc(stream);
  if (ch == EOF)
  {
    return -1;
  }
  if (ch != 'P')
  {
    return -1;
  }
  ch = getc(stream);
  if ((ch < '1') || (ch > '9'))
  {
    return -1;
  }
  format = (unsigned int) (ch - '0');
  ch = pnm_fget_char(stream);
  if (!((((ch == ' ') || (ch == '\t')) || (ch == '\n')) || (ch == '\r')))
  {
    return -1;
  }
  pnm_ptr->format = format;
  if ((format >= PNM_P1) && (format <= PNM_P6))
  {
    pnm_ptr->depth = ((format == PNM_P3) || (format == PNM_P6)) ? (3) : (1);
    if ((pnm_fscan_uint(stream, &pnm_ptr->width) != 1) || (pnm_fscan_uint(stream, &pnm_ptr->height) != 1))
    {
      return -1;
    }
    if ((format == PNM_P1) || (format == PNM_P4))
    {
      pnm_ptr->maxval = 1;
    }
    else
    {
      if (pnm_fscan_uint(stream, &pnm_ptr->maxval) != 1)
      {
        return -1;
      }
    }
    return (pnm_is_valid(pnm_ptr)) ? (1) : (0);
  }
  else
    return -1;
}

int pnm_fget_values(const pnm_struct *pnm_ptr, unsigned int *sample_values, unsigned int num_rows, FILE *stream)
{
  unsigned int format = pnm_ptr->format;
  unsigned int depth = pnm_ptr->depth;
  unsigned int width = pnm_ptr->width;
  unsigned int maxval = pnm_ptr->maxval;
  size_t row_length = ((size_t) depth) * ((size_t) width);
  size_t num_samples = num_rows * row_length;
  int ch;
  int ch8;
  int ch16;
  int ch24;
  int mask;
  size_t i;
  size_t j;
  switch (format)
  {
    case PNM_P1:
    {
      for (i = 0; i < num_samples; i += 1)
      {
        do
        {
          ch = pnm_fget_char(stream);
        }
        while ((((ch == ' ') || (ch == '\t')) || (ch == '\n')) || (ch == '\r'));
        if ((ch != '0') && (ch != '1'))
        {
          ungetc(ch, stream);
          break;
        }
        sample_values[i] = (ch == '0') ? (1) : (0);
      }

      break;
    }

    case PNM_P2:

    case PNM_P3:
    {
      for (i = 0; i < num_samples; i += 1)
      {
        if (pnm_fscan_uint(stream, &sample_values[i]) != 1)
        {
          break;
        }
      }

      break;
    }

    case PNM_P4:
    {
      helper_pnm_fget_values_1(&ch, &mask, &i, &j, sample_values, stream, row_length, num_samples);
    }

    case PNM_P5:

    case PNM_P6:

    case PNM_P7:
    {
      helper_pnm_fget_values_2(&ch, &ch8, &ch16, &ch24, &i, sample_values, stream, maxval, num_samples);
    }

    default:
    {
      errno = EINVAL;
      return 0;
    }

  }

  if (i < num_samples)
  {
    memset(sample_values + i, 0, (num_samples - i) * (sizeof(unsigned int)));
    return -1;
  }
  return 1;
}

int pnm_fget_bytes(const pnm_struct *pnm_ptr, unsigned char *sample_bytes, size_t sample_size, unsigned int num_rows, FILE *stream)
{
  unsigned int format = pnm_ptr->format;
  unsigned int depth = pnm_ptr->depth;
  unsigned int width = pnm_ptr->width;
  unsigned int maxval = pnm_ptr->maxval;
  size_t row_length = ((size_t) depth) * ((size_t) width);
  size_t num_samples = num_rows * row_length;
  size_t raw_sample_size;
  int ch;
  int mask;
  size_t i;
  size_t j;
  if (maxval <= 0xffU)
  {
    raw_sample_size = 1;
  }
  else
    if (maxval <= 0xffffU)
  {
    raw_sample_size = 2;
  }
  else
    if (maxval <= 0xffffffU)
  {
    raw_sample_size = 3;
  }
  else
    if (maxval <= 0xffffffffU)
  {
    raw_sample_size = 4;
  }
  else
    raw_sample_size = !sample_size;
  if (raw_sample_size != sample_size)
  {
    errno = EINVAL;
    return 0;
  }
  switch (format)
  {
    case PNM_P4:
    {
      helper_pnm_fget_bytes_1(&ch, &mask, &i, &j, sample_bytes, stream, row_length, num_samples);
    }

    case PNM_P5:

    case PNM_P6:

    case PNM_P7:
    {
      i = fread(sample_bytes, sample_size, num_samples, stream);
      break;
    }

    default:
    {
      errno = EINVAL;
      return 0;
    }

  }

  if (i < num_samples)
  {
    memset(sample_bytes + i, 0, (sample_size * num_samples) - i);
    return -1;
  }
  return 1;
}


enum 
{
  PNM_P1 = 1,
  PNM_P2 = 2,
  PNM_P3 = 3,
  PNM_P4 = 4,
  PNM_P5 = 5,
  PNM_P6 = 6,
  PNM_P7 = 7
};
typedef struct pnm_struct
{
  unsigned int format;
  unsigned int depth;
  unsigned int width;
  unsigned int height;
  unsigned int maxval;
} pnm_struct;
int pnm_fget_header(pnm_struct *pnm_ptr, FILE *stream);
int pnm_fget_values(const pnm_struct *pnm_ptr, unsigned int *sample_values, unsigned int num_rows, FILE *stream);
int pnm_fget_bytes(const pnm_struct *pnm_ptr, unsigned char *sample_bytes, size_t sample_size, unsigned int num_rows, FILE *stream);
int pnm_fput_header(const pnm_struct *pnm_ptr, FILE *stream);
int pnm_fput_values(const pnm_struct *pnm_ptr, const unsigned int *sample_values, unsigned int num_rows, FILE *stream);
int pnm_fput_bytes(const pnm_struct *pnm_ptr, const unsigned char *sample_bytes, size_t sample_size, unsigned int num_rows, FILE *stream);
int pnm_is_valid(const pnm_struct *pnm_ptr);
size_t pnm_raw_sample_size(const pnm_struct *pnm_ptr);
size_t pnm_mem_size(const pnm_struct *pnm_ptr, size_t sample_size, unsigned int num_rows);
static int pnm_fget_char(FILE *stream)
{
  int ch = getc(stream);
  if (ch == '#')
  {
    do
    {
      ch = getc(stream);
    }
    while (((ch != EOF) && (ch != '\n')) && (ch != '\r'));
  }
  if (ch == '\r')
  {
    ch = getc(stream);
    if (ch != '\n')
    {
      ungetc(ch, stream);
      ch = '\n';
    }
  }
  return ch;
}

static int pnm_fscan_uint(FILE *stream, unsigned int *value)
{
  int ch;
  unsigned int tmp;
  do
  {
    ch = pnm_fget_char(stream);
  }
  while ((((ch == ' ') || (ch == '\t')) || (ch == '\n')) || (ch == '\r'));
  if (ch == EOF)
  {
    return EOF;
  }
  if (!((ch >= '0') && (ch <= '9')))
  {
    ungetc(ch, stream);
    return 0;
  }
  *value = 0;
  do
  {
    tmp = ((*value) * 10) + (ch - '0');
    if (tmp >= (*value))
    {
      *value = tmp;
    }
    else
    {
      *value = 4294967295U;
      errno = ERANGE;
    }
    ch = getc(stream);
  }
  while ((ch >= '0') && (ch <= '9'));
  if (!((((ch == ' ') || (ch == '\t')) || (ch == '\n')) || (ch == '\r')))
  {
    ungetc(ch, stream);
  }
  return 1;
}

int pnm_fget_header(pnm_struct *pnm_ptr, FILE *stream)
{
  unsigned int format;
  int ch;
  memset(pnm_ptr, 0, sizeof(pnm_struct));
  ch = getc(stream);
  if (ch == EOF)
  {
    return -1;
  }
  if (ch != 'P')
  {
    return -1;
  }
  ch = getc(stream);
  if ((ch < '1') || (ch > '9'))
  {
    return -1;
  }
  format = (unsigned int) (ch - '0');
  ch = pnm_fget_char(stream);
  if (!((((ch == ' ') || (ch == '\t')) || (ch == '\n')) || (ch == '\r')))
  {
    return -1;
  }
  pnm_ptr->format = format;
  if ((format >= PNM_P1) && (format <= PNM_P6))
  {
    pnm_ptr->depth = ((format == PNM_P3) || (format == PNM_P6)) ? (3) : (1);
    if ((pnm_fscan_uint(stream, &pnm_ptr->width) != 1) || (pnm_fscan_uint(stream, &pnm_ptr->height) != 1))
    {
      return -1;
    }
    if ((format == PNM_P1) || (format == PNM_P4))
    {
      pnm_ptr->maxval = 1;
    }
    else
    {
      if (pnm_fscan_uint(stream, &pnm_ptr->maxval) != 1)
      {
        return -1;
      }
    }
    return (pnm_is_valid(pnm_ptr)) ? (1) : (0);
  }
  else
    return -1;
}

int pnm_fget_values(const pnm_struct *pnm_ptr, unsigned int *sample_values, unsigned int num_rows, FILE *stream)
{
  unsigned int format = pnm_ptr->format;
  unsigned int depth = pnm_ptr->depth;
  unsigned int width = pnm_ptr->width;
  unsigned int maxval = pnm_ptr->maxval;
  size_t row_length = ((size_t) depth) * ((size_t) width);
  size_t num_samples = num_rows * row_length;
  int ch;
  int ch8;
  int ch16;
  int ch24;
  int mask;
  size_t i;
  size_t j;
  switch (format)
  {
    case PNM_P1:
      for (i = 0; i < num_samples; i += 1)
    {
      do
      {
        ch = pnm_fget_char(stream);
      }
      while ((((ch == ' ') || (ch == '\t')) || (ch == '\n')) || (ch == '\r'));
      if ((ch != '0') && (ch != '1'))
      {
        ungetc(ch, stream);
        break;
      }
      sample_values[i] = (ch == '0') ? (1) : (0);
    }

      break;

    case PNM_P2:

    case PNM_P3:
      for (i = 0; i < num_samples; i += 1)
    {
      if (pnm_fscan_uint(stream, &sample_values[i]) != 1)
      {
        break;
      }
    }

      break;

    case PNM_P4:
      for (i = (j = 0); i < num_samples;)
    {
      ch = getc(stream);
      if (ch == EOF)
      {
        break;
      }
      for (mask = 0x80; mask != 0; mask >>= 1)
      {
        sample_values[i] = (ch & mask) ? (0) : (1);
        i += 1;
        if ((++j) == row_length)
        {
          j = 0;
          break;
        }
      }

    }

      break;

    case PNM_P5:

    case PNM_P6:

    case PNM_P7:
      if (maxval <= 0xffU)
    {
      for (i = 0; i < num_samples; i += 1)
      {
        ch = getc(stream);
        if (ch == EOF)
        {
          break;
        }
        sample_values[i] = (unsigned int) ch;
      }

    }
    else
      if (maxval <= 0xffffU)
    {
      for (i = 0; i < num_samples; i += 1)
      {
        ch8 = getc(stream);
        ch = getc(stream);
        if (ch == EOF)
        {
          break;
        }
        sample_values[i] = (((unsigned int) ch8) << 8) + ((unsigned int) ch);
      }

    }
    else
      if (maxval <= 0xffffffffU)
    {
      ch24 = 0;
      for (i = 0; i < num_samples; i += 1)
      {
        if (maxval > 0xffffffU)
        {
          ch24 = getc(stream);
        }
        ch16 = getc(stream);
        ch8 = getc(stream);
        ch = getc(stream);
        if (ch == EOF)
        {
          break;
        }
        sample_values[i] = (((((unsigned int) ch24) << 24) + (((unsigned int) ch16) << 16)) + (((unsigned int) ch8) << 8)) + ((unsigned int) ch);
      }

    }
    else
    {
      errno = EINVAL;
      return 0;
    }
      break;

    default:
      errno = EINVAL;
      return 0;

  }

  if (i < num_samples)
  {
    memset(sample_values + i, 0, (num_samples - i) * (sizeof(unsigned int)));
    return -1;
  }
  return 1;
}

int pnm_fget_bytes(const pnm_struct *pnm_ptr, unsigned char *sample_bytes, size_t sample_size, unsigned int num_rows, FILE *stream)
{
  unsigned int format = pnm_ptr->format;
  unsigned int depth = pnm_ptr->depth;
  unsigned int width = pnm_ptr->width;
  unsigned int maxval = pnm_ptr->maxval;
  size_t row_length = ((size_t) depth) * ((size_t) width);
  size_t num_samples = num_rows * row_length;
  size_t raw_sample_size;
  int ch;
  int mask;
  size_t i;
  size_t j;
  if (maxval <= 0xffU)
  {
    raw_sample_size = 1;
  }
  else
    if (maxval <= 0xffffU)
  {
    raw_sample_size = 2;
  }
  else
    if (maxval <= 0xffffffU)
  {
    raw_sample_size = 3;
  }
  else
    if (maxval <= 0xffffffffU)
  {
    raw_sample_size = 4;
  }
  else
    raw_sample_size = !sample_size;
  if (raw_sample_size != sample_size)
  {
    errno = EINVAL;
    return 0;
  }
  switch (format)
  {
    case PNM_P4:
      for (i = (j = 0); i < num_samples;)
    {
      ch = getc(stream);
      if (ch == EOF)
      {
        break;
      }
      for (mask = 0x80; mask != 0; mask >>= 1)
      {
        sample_bytes[i] = (unsigned char) ((ch & mask) ? (0) : (1));
        i += 1;
        if ((++j) == row_length)
        {
          j = 0;
          break;
        }
      }

    }

      break;

    case PNM_P5:

    case PNM_P6:

    case PNM_P7:
      i = fread(sample_bytes, sample_size, num_samples, stream);
      break;

    default:
      errno = EINVAL;
      return 0;

  }

  if (i < num_samples)
  {
    memset(sample_bytes + i, 0, (sample_size * num_samples) - i);
    return -1;
  }
  return 1;
}

void helper_pnm_fget_values_1(int * const ch_ref, int * const mask_ref, size_t * const i_ref, size_t * const j_ref, unsigned int * const sample_values, FILE * const stream, size_t row_length, size_t num_samples)
{
  int ch = *ch_ref;
  int mask = *mask_ref;
  size_t i = *i_ref;
  size_t j = *j_ref;
  for (i = (j = 0); i < num_samples;)
  {
    ch = getc(stream);
    if (ch == EOF)
    {
      break;
    }
    for (mask = 0x80; mask != 0; mask >>= 1)
    {
      sample_values[i] = (ch & mask) ? (0) : (1);
      i += 1;
      if ((++j) == row_length)
      {
        j = 0;
        break;
      }
    }

  }

  break;
  *ch_ref = ch;
  *mask_ref = mask;
  *i_ref = i;
  *j_ref = j;
}

int helper_pnm_fget_values_2(int * const ch_ref, int * const ch8_ref, int * const ch16_ref, int * const ch24_ref, size_t * const i_ref, unsigned int * const sample_values, FILE * const stream, unsigned int maxval, size_t num_samples)
{
  int ch = *ch_ref;
  int ch8 = *ch8_ref;
  int ch16 = *ch16_ref;
  int ch24 = *ch24_ref;
  size_t i = *i_ref;
  if (maxval <= 0xffU)
  {
    for (i = 0; i < num_samples; i += 1)
    {
      ch = getc(stream);
      if (ch == EOF)
      {
        break;
      }
      sample_values[i] = (unsigned int) ch;
    }

  }
  else
    if (maxval <= 0xffffU)
  {
    for (i = 0; i < num_samples; i += 1)
    {
      ch8 = getc(stream);
      ch = getc(stream);
      if (ch == EOF)
      {
        break;
      }
      sample_values[i] = (((unsigned int) ch8) << 8) + ((unsigned int) ch);
    }

  }
  else
    if (maxval <= 0xffffffffU)
  {
    ch24 = 0;
    for (i = 0; i < num_samples; i += 1)
    {
      if (maxval > 0xffffffU)
      {
        ch24 = getc(stream);
      }
      ch16 = getc(stream);
      ch8 = getc(stream);
      ch = getc(stream);
      if (ch == EOF)
      {
        break;
      }
      sample_values[i] = (((((unsigned int) ch24) << 24) + (((unsigned int) ch16) << 16)) + (((unsigned int) ch8) << 8)) + ((unsigned int) ch);
    }

  }
  else
  {
    errno = EINVAL;
    return 0;
  }
  break;
  *ch_ref = ch;
  *ch8_ref = ch8;
  *ch16_ref = ch16;
  *ch24_ref = ch24;
  *i_ref = i;
}

void helper_pnm_fget_bytes_1(int * const ch_ref, int * const mask_ref, size_t * const i_ref, size_t * const j_ref, unsigned char * const sample_bytes, FILE * const stream, size_t row_length, size_t num_samples)
{
  int ch = *ch_ref;
  int mask = *mask_ref;
  size_t i = *i_ref;
  size_t j = *j_ref;
  for (i = (j = 0); i < num_samples;)
  {
    ch = getc(stream);
    if (ch == EOF)
    {
      break;
    }
    for (mask = 0x80; mask != 0; mask >>= 1)
    {
      sample_bytes[i] = (unsigned char) ((ch & mask) ? (0) : (1));
      i += 1;
      if ((++j) == row_length)
      {
        j = 0;
        break;
      }
    }

  }

  break;
  *ch_ref = ch;
  *mask_ref = mask;
  *i_ref = i;
  *j_ref = j;
}

