// hint:  ['ch_ref is a mutable refrence to int', 'mask_ref is a mutable refrence to int', 'i_ref is a mutable refrence to size_t', 'j_ref is a mutable refrence to size_t']
void helper_pnm_fput_values_1(int * const ch_ref, int * const mask_ref, size_t * const i_ref, size_t * const j_ref, const unsigned int * const sample_values, FILE * const stream, size_t row_length, size_t num_samples)
{
  int ch = *ch_ref;
  int mask = *mask_ref;
  size_t i = *i_ref;
  size_t j = *j_ref;
  for (i = (j = 0); i < num_samples;)
  {
    ch = 0;
    for (mask = 0x80; mask != 0; mask >>= 1)
    {
      if (sample_values[i++] == 0)
      {
        ch |= mask;
      }
      if ((++j) == row_length)
      {
        j = 0;
        break;
      }
    }

    if (putc(ch, stream) == EOF)
    {
      break;
    }
  }

  break;
  *ch_ref = ch;
  *mask_ref = mask;
  *i_ref = i;
  *j_ref = j;
}


/*** DEPENDENCIES:
***/


// hint:  ['i_ref is a mutable refrence to size_t']
int helper_pnm_fput_values_2(size_t * const i_ref, const unsigned int * const sample_values, FILE * const stream, unsigned int maxval, size_t num_samples)
{
  size_t i = *i_ref;
  if (maxval <= 0xffU)
  {
    for (i = 0; i < num_samples; i += 1)
    {
      if (putc(sample_values[i] & 0xff, stream) == EOF)
      {
        break;
      }
    }

  }
  else
    if (maxval <= 0xffffU)
  {
    for (i = 0; i < num_samples; i += 1)
    {
      if ((putc((sample_values[i] >> 8) & 0xff, stream) == EOF) || (putc(sample_values[i] & 0xff, stream) == EOF))
      {
        break;
      }
    }

  }
  else
    if (maxval <= 0xffffffffU)
  {
    for (i = 0; i < num_samples; i += 1)
    {
      if (maxval > 0xffffffU)
      {
        if (putc((sample_values[i] >> 24) & 0xff, stream) == EOF)
        {
          break;
        }
      }
      if (((putc((sample_values[i] >> 16) & 0xff, stream) == EOF) || (putc((sample_values[i] >> 8) & 0xff, stream) == EOF)) || (putc(sample_values[i] & 0xff, stream) == EOF))
      {
        break;
      }
    }

  }
  else
  {
    errno = EINVAL;
    return 0;
  }
  break;
  *i_ref = i;
}


/*** DEPENDENCIES:
***/


// hint:  ['ch_ref is a mutable refrence to int', 'mask_ref is a mutable refrence to int', 'i_ref is a mutable refrence to size_t', 'j_ref is a mutable refrence to size_t']
void helper_pnm_fput_bytes_1(int * const ch_ref, int * const mask_ref, size_t * const i_ref, size_t * const j_ref, const unsigned char * const sample_bytes, FILE * const stream, size_t row_length, size_t num_samples)
{
  int ch = *ch_ref;
  int mask = *mask_ref;
  size_t i = *i_ref;
  size_t j = *j_ref;
  for (i = (j = 0); i < num_samples;)
  {
    ch = 0;
    for (mask = 0x80; mask != 0; mask >>= 1)
    {
      if (sample_bytes[i++] == 0)
      {
        ch |= mask;
      }
      if ((++j) == row_length)
      {
        j = 0;
        break;
      }
    }

    if (putc(ch, stream) == EOF)
    {
      break;
    }
  }

  break;
  *ch_ref = ch;
  *mask_ref = mask;
  *i_ref = i;
  *j_ref = j;
}


/*** DEPENDENCIES:
***/


int pnm_fput_header(const pnm_struct *pnm_ptr, FILE *stream)
{
  unsigned int format = pnm_ptr->format;
  unsigned int depth = pnm_ptr->depth;
  unsigned int width = pnm_ptr->width;
  unsigned int height = pnm_ptr->height;
  unsigned int maxval = pnm_ptr->maxval;
  int result;
  if (!pnm_is_valid(pnm_ptr))
  {
    return 0;
  }
  switch (format)
  {
    case PNM_P1:

    case PNM_P4:
    {
      result = fprintf(stream, "P%c\n%u %u\n", format + '0', width, height);
      break;
    }

    case PNM_P2:

    case PNM_P3:

    case PNM_P5:

    case PNM_P6:
    {
      result = fprintf(stream, "P%c\n%u %u\n%u\n", format + '0', width, height, maxval);
      break;
    }

    case PNM_P7:
    {
      result = fprintf(stream, "P7\nDEPTH %u\nWIDTH %u\nHEIGHT %u\nMAXVAL %u\nENDHDR\n", depth, width, height, maxval);
      break;
    }

    default:
    {
      errno = EINVAL;
      return 0;
    }

  }

  return (result > 0) ? (1) : (-1);
}


/*** DEPENDENCIES:
int pnm_is_valid(const pnm_struct *pnm_ptr)
{
  unsigned int format = pnm_ptr->format;
  unsigned int depth = pnm_ptr->depth;
  unsigned int width = pnm_ptr->width;
  unsigned int height = pnm_ptr->height;
  unsigned int maxval = pnm_ptr->maxval;
  if ((((depth == 0) || (width == 0)) || (height == 0)) || (maxval == 0))
  {
    return 0;
  }
  switch (format)
  {
    case PNM_P1:

    case PNM_P4:
    {
      return ((depth == 1) && (maxval == 1)) ? (1) : (0);
    }

    case PNM_P2:

    case PNM_P5:
    {
      return (depth == 1) ? (1) : (0);
    }

    case PNM_P3:

    case PNM_P6:
    {
      return (depth == 3) ? (1) : (0);
    }

    case PNM_P7:
    {
      return 1;
    }

    default:
    {
      return 0;
    }

  }

}


----------------------------
typedef struct pnm_struct
{
  unsigned int format;
  unsigned int depth;
  unsigned int width;
  unsigned int height;
  unsigned int maxval;
} pnm_struct
----------------------------
***/


int pnm_fput_bytes(const pnm_struct *pnm_ptr, const unsigned char *sample_bytes, size_t sample_size, unsigned int num_rows, FILE *stream)
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
      helper_pnm_fput_bytes_1(&ch, &mask, &i, &j, sample_bytes, stream, row_length, num_samples);
    }

    case PNM_P5:

    case PNM_P6:

    case PNM_P7:
    {
      i = fwrite(sample_bytes, sample_size, num_samples, stream);
      break;
    }

    default:
    {
      errno = EINVAL;
      return 0;
    }

  }

  return (i == num_samples) ? (1) : (-1);
}


/*** DEPENDENCIES:
void helper_pnm_fput_bytes_1(int * const ch_ref, int * const mask_ref, size_t * const i_ref, size_t * const j_ref, const unsigned char * const sample_bytes, FILE * const stream, size_t row_length, size_t num_samples)
{
  int ch = *ch_ref;
  int mask = *mask_ref;
  size_t i = *i_ref;
  size_t j = *j_ref;
  for (i = (j = 0); i < num_samples;)
  {
    ch = 0;
    for (mask = 0x80; mask != 0; mask >>= 1)
    {
      if (sample_bytes[i++] == 0)
      {
        ch |= mask;
      }
      if ((++j) == row_length)
      {
        j = 0;
        break;
      }
    }

    if (putc(ch, stream) == EOF)
    {
      break;
    }
  }

  break;
  *ch_ref = ch;
  *mask_ref = mask;
  *i_ref = i;
  *j_ref = j;
}


----------------------------
typedef struct pnm_struct
{
  unsigned int format;
  unsigned int depth;
  unsigned int width;
  unsigned int height;
  unsigned int maxval;
} pnm_struct
----------------------------
***/


int pnm_fput_values(const pnm_struct *pnm_ptr, const unsigned int *sample_values, unsigned int num_rows, FILE *stream)
{
  unsigned int format = pnm_ptr->format;
  unsigned int depth = pnm_ptr->depth;
  unsigned int width = pnm_ptr->width;
  unsigned int maxval = pnm_ptr->maxval;
  size_t row_length = ((size_t) depth) * ((size_t) width);
  size_t num_samples = num_rows * row_length;
  int ch;
  int mask;
  size_t i;
  size_t j;
  switch (format)
  {
    case PNM_P1:
    {
      for (i = (j = 0); i < num_samples; i += 1)
      {
        if (putc((sample_values[i] != 0) ? ('0') : ('1'), stream) == EOF)
        {
          break;
        }
        if ((++j) == row_length)
        {
          j = 0;
          if (putc('\n', stream) == EOF)
          {
            break;
          }
        }
      }

      break;
    }

    case PNM_P2:

    case PNM_P3:
    {
      for (i = (j = 0); i < num_samples; i += 1)
      {
        if ((++j) == row_length)
        {
          j = 0;
        }
        if (fprintf(stream, (j == 0) ? ("%u\n") : ("%u "), sample_values[i]) <= 0)
        {
          break;
        }
      }

      break;
    }

    case PNM_P4:
    {
      helper_pnm_fput_values_1(&ch, &mask, &i, &j, sample_values, stream, row_length, num_samples);
    }

    case PNM_P5:

    case PNM_P6:

    case PNM_P7:
    {
      helper_pnm_fput_values_2(&i, sample_values, stream, maxval, num_samples);
    }

    default:
    {
      errno = EINVAL;
      return 0;
    }

  }

  return (i == num_samples) ? (1) : (-1);
}


/*** DEPENDENCIES:
void helper_pnm_fput_values_1(int * const ch_ref, int * const mask_ref, size_t * const i_ref, size_t * const j_ref, const unsigned int * const sample_values, FILE * const stream, size_t row_length, size_t num_samples)
{
  int ch = *ch_ref;
  int mask = *mask_ref;
  size_t i = *i_ref;
  size_t j = *j_ref;
  for (i = (j = 0); i < num_samples;)
  {
    ch = 0;
    for (mask = 0x80; mask != 0; mask >>= 1)
    {
      if (sample_values[i++] == 0)
      {
        ch |= mask;
      }
      if ((++j) == row_length)
      {
        j = 0;
        break;
      }
    }

    if (putc(ch, stream) == EOF)
    {
      break;
    }
  }

  break;
  *ch_ref = ch;
  *mask_ref = mask;
  *i_ref = i;
  *j_ref = j;
}


----------------------------
int helper_pnm_fput_values_2(size_t * const i_ref, const unsigned int * const sample_values, FILE * const stream, unsigned int maxval, size_t num_samples)
{
  size_t i = *i_ref;
  if (maxval <= 0xffU)
  {
    for (i = 0; i < num_samples; i += 1)
    {
      if (putc(sample_values[i] & 0xff, stream) == EOF)
      {
        break;
      }
    }

  }
  else
    if (maxval <= 0xffffU)
  {
    for (i = 0; i < num_samples; i += 1)
    {
      if ((putc((sample_values[i] >> 8) & 0xff, stream) == EOF) || (putc(sample_values[i] & 0xff, stream) == EOF))
      {
        break;
      }
    }

  }
  else
    if (maxval <= 0xffffffffU)
  {
    for (i = 0; i < num_samples; i += 1)
    {
      if (maxval > 0xffffffU)
      {
        if (putc((sample_values[i] >> 24) & 0xff, stream) == EOF)
        {
          break;
        }
      }
      if (((putc((sample_values[i] >> 16) & 0xff, stream) == EOF) || (putc((sample_values[i] >> 8) & 0xff, stream) == EOF)) || (putc(sample_values[i] & 0xff, stream) == EOF))
      {
        break;
      }
    }

  }
  else
  {
    errno = EINVAL;
    return 0;
  }
  break;
  *i_ref = i;
}


----------------------------
typedef struct pnm_struct
{
  unsigned int format;
  unsigned int depth;
  unsigned int width;
  unsigned int height;
  unsigned int maxval;
} pnm_struct
----------------------------
***/


