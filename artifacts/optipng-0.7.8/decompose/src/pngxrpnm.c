static int pnm_fpeek_eof(pnm_struct *pnm_ptr, FILE *stream)
{
  int ch;
  if ((pnm_ptr->format >= PNM_P1) && (pnm_ptr->format <= PNM_P3))
  {
    do
    {
      ch = getc(stream);
      if (ch == '#')
      {
        do
        {
          ch = getc(stream);
        }
        while (((ch != EOF) && (ch != '\n')) && (ch != '\r'));
      }
      if (ch == EOF)
      {
        return 1;
      }
    }
    while ((((ch == ' ') || (ch == '\t')) || (ch == '\n')) || (ch == '\r'));
  }
  else
  {
    ch = getc(stream);
    if (ch == EOF)
    {
      return 1;
    }
  }
  ungetc(ch, stream);
  return 0;
}


/*** DEPENDENCIES:
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


// hint:  ['row_pointers_ref is a mutable refrence to png_bytepp', 'i_ref is a mutable refrence to unsigned int', 'j_ref is a mutable refrence to unsigned int', 'failed_ref is a mutable refrence to int', 'overflow_ref is a mutable refrence to int']
void helper_helper_pngx_read_pnm_1_1(png_bytepp * const row_pointers_ref, unsigned int * const i_ref, unsigned int * const j_ref, int * const failed_ref, int * const overflow_ref, FILE * const stream, pnm_struct pnminfo, unsigned int maxval, unsigned int num_samples, unsigned int * const pnmrow, unsigned int pnmrow_idx)
{
  png_bytepp row_pointers = *row_pointers_ref;
  unsigned int i = *i_ref;
  unsigned int j = *j_ref;
  int failed = *failed_ref;
  int overflow = *overflow_ref;
  if (pnm_fget_values(&pnminfo, pnmrow, 1, stream) <= 0)
  {
    failed = 1;
  }
  if (maxval <= 255)
  {
    for (j = 0; j < num_samples; j += 1)
    {
      unsigned int val = pnmrow[j + pnmrow_idx];
      if (val > maxval)
      {
        val = 255;
        overflow = 1;
      }
      else
        if (maxval != 255)
      {
        val = ((val * 255) + (maxval / 2)) / maxval;
      }
      row_pointers[i][j] = (png_byte) val;
    }

  }
  else
  {
    for (j = 0; j < num_samples; j += 1)
    {
      png_uint_32 val = pnmrow[j + pnmrow_idx];
      if (val > maxval)
      {
        val = 65535;
        overflow = 1;
      }
      else
        if (maxval != 65535)
      {
        val = ((val * 65535) + (maxval / 2)) / maxval;
      }
      row_pointers[i][2 * j] = (png_byte) (val >> 8);
      row_pointers[i][(2 * j) + 1] = (png_byte) (val & 0xff);
    }

  }
  if (failed)
  {
    break;
  }
  *row_pointers_ref = row_pointers;
  *i_ref = i;
  *j_ref = j;
  *failed_ref = failed;
  *overflow_ref = overflow;
}


/*** DEPENDENCIES:
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


----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_byte **png_bytepp
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
typedef png_byte *png_bytep
----------------------------
***/


// hint:  ['row_pointers_ref is a mutable refrence to png_bytepp', 'i_ref is a mutable refrence to unsigned int', 'j_ref is a mutable refrence to unsigned int', 'failed_ref is a mutable refrence to int', 'overflow_ref is a mutable refrence to int']
void helper_pngx_read_pnm_1(png_bytepp * const row_pointers_ref, unsigned int * const i_ref, unsigned int * const j_ref, int * const failed_ref, int * const overflow_ref, FILE * const stream, pnm_struct pnminfo, unsigned int height, unsigned int maxval, unsigned int num_samples, unsigned int * const pnmrow, unsigned int pnmrow_idx)
{
  png_bytepp row_pointers = *row_pointers_ref;
  unsigned int i = *i_ref;
  unsigned int j = *j_ref;
  int failed = *failed_ref;
  int overflow = *overflow_ref;
  for (i = 0; i < height; i += 1)
  {
    helper_helper_pngx_read_pnm_1_1(&row_pointers, &i, &j, &failed, &overflow, stream, pnminfo, maxval, num_samples, pnmrow, pnmrow_idx);
  }

  *row_pointers_ref = row_pointers;
  *i_ref = i;
  *j_ref = j;
  *failed_ref = failed;
  *overflow_ref = overflow;
}


/*** DEPENDENCIES:
typedef unsigned char png_byte
----------------------------
typedef png_byte **png_bytepp
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
void helper_helper_pngx_read_pnm_1_1(png_bytepp * const row_pointers_ref, unsigned int * const i_ref, unsigned int * const j_ref, int * const failed_ref, int * const overflow_ref, FILE * const stream, pnm_struct pnminfo, unsigned int maxval, unsigned int num_samples, unsigned int * const pnmrow, unsigned int pnmrow_idx)
{
  png_bytepp row_pointers = *row_pointers_ref;
  unsigned int i = *i_ref;
  unsigned int j = *j_ref;
  int failed = *failed_ref;
  int overflow = *overflow_ref;
  if (pnm_fget_values(&pnminfo, pnmrow, 1, stream) <= 0)
  {
    failed = 1;
  }
  if (maxval <= 255)
  {
    for (j = 0; j < num_samples; j += 1)
    {
      unsigned int val = pnmrow[j + pnmrow_idx];
      if (val > maxval)
      {
        val = 255;
        overflow = 1;
      }
      else
        if (maxval != 255)
      {
        val = ((val * 255) + (maxval / 2)) / maxval;
      }
      row_pointers[i][j] = (png_byte) val;
    }

  }
  else
  {
    for (j = 0; j < num_samples; j += 1)
    {
      png_uint_32 val = pnmrow[j + pnmrow_idx];
      if (val > maxval)
      {
        val = 65535;
        overflow = 1;
      }
      else
        if (maxval != 65535)
      {
        val = ((val * 65535) + (maxval / 2)) / maxval;
      }
      row_pointers[i][2 * j] = (png_byte) (val >> 8);
      row_pointers[i][(2 * j) + 1] = (png_byte) (val & 0xff);
    }

  }
  if (failed)
  {
    break;
  }
  *row_pointers_ref = row_pointers;
  *i_ref = i;
  *j_ref = j;
  *failed_ref = failed;
  *overflow_ref = overflow;
}


----------------------------
typedef png_byte *png_bytep
----------------------------
***/


int pngx_read_pnm(png_structp png_ptr, png_infop info_ptr, FILE *stream)
{
  pnm_struct pnminfo;
  unsigned int format;
  unsigned int depth;
  unsigned int width;
  unsigned int height;
  unsigned int maxval;
  unsigned int max_width;
  unsigned int num_samples;
  unsigned int sample_size;
  unsigned int *pnmrow;
  unsigned int pnmrow_idx = 0;
  size_t row_size;
  png_bytepp row_pointers;
  png_color_8 sig_bit;
  unsigned int i;
  unsigned int j;
  int failed;
  int overflow;
  if (pnm_fget_header(&pnminfo, stream) != 1)
  {
    return 0;
  }
  format = pnminfo.format;
  depth = pnminfo.depth;
  width = pnminfo.width;
  height = pnminfo.height;
  maxval = pnminfo.maxval;
  if (format > PNM_P6)
  {
    png_error(png_ptr, "Can't handle PNM formats newer than PPM (\"P6\")");
  }
  max_width = ((sizeof(size_t)) <= (sizeof(unsigned int))) ? ((4294967295U / (sizeof(unsigned int))) / depth) : (4294967295U);
  if (max_width > 0x7fffffffU)
  {
    max_width = 0x7fffffffU;
  }
  if (width > max_width)
  {
    png_error(png_ptr, "Can't handle exceedingly large PNM dimensions");
  }
  sample_size = 1;
  row_size = (num_samples = depth * width);
  if (maxval > 65535)
  {
    png_error(png_ptr, "Can't handle PNM samples larger than 16 bits");
  }
  else
    if (maxval > 255)
  {
    sample_size = 2;
    row_size *= 2;
  }
  png_set_IHDR(png_ptr, info_ptr, width, height, (maxval <= 255) ? (8) : (16), (depth == 1) ? (0) : (2), 0, 0, 0);
  for (i = 1, j = 2; (j - 1) < maxval; i += 1, j <<= 1)
  {
  }

  if ((j - 1) != maxval)
  {
    png_warning(png_ptr, "Possibly inexact sample conversion from PNM to PNG");
  }
  else
    if (((i % 8) != 0) && ((depth > 1) || ((8 % i) != 0)))
  {
    sig_bit.red = (sig_bit.green = (sig_bit.blue = (sig_bit.gray = (png_byte) i)));
    sig_bit.alpha = 0;
    png_set_sBIT(png_ptr, info_ptr, &sig_bit);
  }
  row_pointers = pngx_malloc_rows(png_ptr, info_ptr, -1);
  if ((format >= PNM_P4) && ((maxval == 255) || (maxval == 65535)))
  {
    pnmrow_idx = 0;
  }
  else
    pnmrow_idx = (unsigned int *) png_malloc(png_ptr, num_samples * (sizeof(unsigned int)));
  failed = 0;
  overflow = 0;
  if ((&pnmrow[pnmrow_idx]) != 0)
  {
    helper_pngx_read_pnm_1(&row_pointers, &i, &j, &failed, &overflow, stream, pnminfo, height, maxval, num_samples, pnmrow, pnmrow_idx);
  }
  else
  {
    for (i = 0; i < height; i += 1)
    {
      if (pnm_fget_bytes(&pnminfo, row_pointers[i], sample_size, 1, stream) <= 0)
      {
        failed = 1;
        break;
      }
    }

  }
  for (; i < height; i += 1)
  {
    memset(row_pointers[i], 0, row_size);
  }

  if ((&pnmrow[pnmrow_idx]) != 0)
  {
    png_free(png_ptr, pnmrow);
  }
  if (overflow)
  {
    png_warning(png_ptr, "Overflow in PNM samples");
  }
  if (failed)
  {
    png_error(png_ptr, "Error in PNM image file");
  }
  else
    if (!pnm_fpeek_eof(&pnminfo, stream))
  {
    png_warning(png_ptr, "Extraneous data found after PNM image");
  }
  return 1;
}


/*** DEPENDENCIES:
typedef struct png_color_struct
{
  png_byte red;
  png_byte green;
  png_byte blue;
} png_color
----------------------------
void helper_pngx_read_pnm_1(png_bytepp * const row_pointers_ref, unsigned int * const i_ref, unsigned int * const j_ref, int * const failed_ref, int * const overflow_ref, FILE * const stream, pnm_struct pnminfo, unsigned int height, unsigned int maxval, unsigned int num_samples, unsigned int * const pnmrow, unsigned int pnmrow_idx)
{
  png_bytepp row_pointers = *row_pointers_ref;
  unsigned int i = *i_ref;
  unsigned int j = *j_ref;
  int failed = *failed_ref;
  int overflow = *overflow_ref;
  for (i = 0; i < height; i += 1)
  {
    helper_helper_pngx_read_pnm_1_1(&row_pointers, &i, &j, &failed, &overflow, stream, pnminfo, maxval, num_samples, pnmrow, pnmrow_idx);
  }

  *row_pointers_ref = row_pointers;
  *i_ref = i;
  *j_ref = j;
  *failed_ref = failed;
  *overflow_ref = overflow;
}


----------------------------
void png_warning(png_const_structrp png_ptr, png_const_charp warning_message)
{
  int offset = 0;
  if (png_ptr != 0)
  {
    {
      if ((*warning_message) == 0x23)
      {
        for (offset = 1; offset < 15; offset += 1)
        {
          if (warning_message[offset] == ' ')
          {
            break;
          }
        }

      }
    }
  }
  if ((png_ptr != 0) && (png_ptr->warning_fn != 0))
  {
    (*png_ptr->warning_fn)((png_structrp) ((void *) ((const void *) png_ptr)), warning_message + offset);
  }
  else
    png_default_warning(png_ptr, warning_message + offset);
}


----------------------------
typedef png_byte **png_bytepp
----------------------------
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


----------------------------
typedef png_byte *png_bytep
----------------------------
png_voidp png_malloc(png_const_structrp png_ptr, png_alloc_size_t size)
{
  png_voidp ret;
  if (png_ptr == 0)
  {
    return 0;
  }
  ret = png_malloc_base(png_ptr, size);
  if (ret == 0)
  {
    png_error(png_ptr, "Out of memory");
  }
  return ret;
}


----------------------------
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


----------------------------
typedef struct png_color_8_struct
{
  png_byte red;
  png_byte green;
  png_byte blue;
  png_byte gray;
  png_byte alpha;
} png_color_8
----------------------------
typedef png_struct *png_structp
----------------------------
void png_set_sBIT(png_const_structrp png_ptr, png_inforp info_ptr, png_const_color_8p sig_bit)
{
  (void) 0;
  if (((png_ptr == 0) || (info_ptr == 0)) || (sig_bit == 0))
  {
    return;
  }
  info_ptr->sig_bit = *sig_bit;
  info_ptr->valid |= 0x0002U;
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
void png_free(png_const_structrp png_ptr, png_voidp ptr)
{
  if ((png_ptr == 0) || (ptr == 0))
  {
    return;
  }
  free(ptr);
}


----------------------------
typedef struct png_info_def png_info
----------------------------
typedef unsigned char png_byte
----------------------------
static int pnm_fpeek_eof(pnm_struct *pnm_ptr, FILE *stream)
{
  int ch;
  if ((pnm_ptr->format >= PNM_P1) && (pnm_ptr->format <= PNM_P3))
  {
    do
    {
      ch = getc(stream);
      if (ch == '#')
      {
        do
        {
          ch = getc(stream);
        }
        while (((ch != EOF) && (ch != '\n')) && (ch != '\r'));
      }
      if (ch == EOF)
      {
        return 1;
      }
    }
    while ((((ch == ' ') || (ch == '\t')) || (ch == '\n')) || (ch == '\r'));
  }
  else
  {
    ch = getc(stream);
    if (ch == EOF)
    {
      return 1;
    }
  }
  ungetc(ch, stream);
  return 0;
}


----------------------------
void png_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr != 0) && (png_ptr->error_fn != 0))
  {
    (*png_ptr->error_fn)((png_structrp) ((void *) ((const void *) png_ptr)), error_message);
  }
  png_default_error(png_ptr, error_message);
}


----------------------------
void png_set_IHDR(png_const_structrp png_ptr, png_inforp info_ptr, png_uint_32 width, png_uint_32 height, int bit_depth, int color_type, int interlace_type, int compression_type, int filter_type)
{
  (void) 0;
  if ((png_ptr == 0) || (info_ptr == 0))
  {
    return;
  }
  info_ptr->width = width;
  info_ptr->height = height;
  info_ptr->bit_depth = (png_byte) bit_depth;
  info_ptr->color_type = (png_byte) color_type;
  info_ptr->compression_type = (png_byte) compression_type;
  info_ptr->filter_type = (png_byte) filter_type;
  info_ptr->interlace_type = (png_byte) interlace_type;
  png_check_IHDR(png_ptr, info_ptr->width, info_ptr->height, info_ptr->bit_depth, info_ptr->color_type, info_ptr->interlace_type, info_ptr->compression_type, info_ptr->filter_type);
  if (info_ptr->color_type == (2 | 1))
  {
    info_ptr->channels = 1;
  }
  else
    if ((info_ptr->color_type & 2) != 0)
  {
    info_ptr->channels = 3;
  }
  else
    info_ptr->channels = 1;
  if ((info_ptr->color_type & 4) != 0)
  {
    info_ptr->channels += 1;
  }
  info_ptr->pixel_depth = (png_byte) (info_ptr->channels * info_ptr->bit_depth);
  info_ptr->rowbytes = (info_ptr->pixel_depth >= 8) ? (((size_t) width) * (((size_t) info_ptr->pixel_depth) >> 3)) : (((((size_t) width) * ((size_t) info_ptr->pixel_depth)) + 7) >> 3);
}


----------------------------
typedef png_info *png_infop
----------------------------
typedef struct png_struct_def png_struct
----------------------------
png_bytepp pngx_malloc_rows(png_structp png_ptr, png_infop info_ptr, int filler)
{
  return pngx_malloc_rows_extended(png_ptr, info_ptr, 0, filler);
}


----------------------------
***/


int pngx_sig_is_pnm(png_bytep sig, size_t sig_size, png_const_charpp fmt_name_ptr, png_const_charpp fmt_long_name_ptr)
{
  static const char *fmt_names[] = {pbm_fmt_name, pgm_fmt_name, ppm_fmt_name, pbm_fmt_name, pgm_fmt_name, ppm_fmt_name, pam_fmt_name};
  static const char *fmt_long_names[] = {pbm_fmt_long_name, pgm_fmt_long_name, ppm_fmt_long_name, pbm_fmt_long_name, pgm_fmt_long_name, ppm_fmt_long_name, pam_fmt_long_name};
  if (sig_size < 4)
  {
    return -1;
  }
  if (((sig[0] != 'P') || (sig[1] < '1')) || (sig[1] > '7'))
  {
    return 0;
  }
  if (((((sig[2] != ' ') && (sig[2] != '\t')) && (sig[2] != '\n')) && (sig[2] != '\r')) && (sig[2] != '#'))
  {
    return 0;
  }
  if (fmt_name_ptr != 0)
  {
    *fmt_name_ptr = fmt_names[sig[1] - '1'];
  }
  if (fmt_long_name_ptr != 0)
  {
    *fmt_long_name_ptr = fmt_long_names[sig[1] - '1'];
  }
  return 1;
}


/*** DEPENDENCIES:
static const char pbm_fmt_name[] = "PBM"
----------------------------
static const char pgm_fmt_name[] = "PGM"
----------------------------
static const char ppm_fmt_long_name[] = "Portable Pixmap"
----------------------------
typedef unsigned char png_byte
----------------------------
static const char pam_fmt_name[] = "PAM"
----------------------------
static const char pbm_fmt_long_name[] = "Portable Bitmap"
----------------------------
static const char pam_fmt_long_name[] = "Portable Anymap"
----------------------------
static const char pgm_fmt_long_name[] = "Portable Graymap"
----------------------------
typedef const char *png_const_charp
----------------------------
typedef png_byte *png_bytep
----------------------------
typedef const char **png_const_charpp
----------------------------
static const char ppm_fmt_name[] = "PPM"
----------------------------
***/


