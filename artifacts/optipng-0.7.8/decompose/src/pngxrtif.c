static void pngx_tiff_warning(const char *msg)
{
  if (strstr(msg, "multi-image") != 0)
  {
    num_extra_images += 1;
  }
}


/*** DEPENDENCIES:
static unsigned int num_extra_images
----------------------------
***/


static void pngx_tiff_error(const char *msg)
{
  png_error(err_png_ptr, msg);
}


/*** DEPENDENCIES:
void png_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr != 0) && (png_ptr->error_fn != 0))
  {
    (*png_ptr->error_fn)((png_structrp) ((void *) ((const void *) png_ptr)), error_message);
  }
  png_default_error(png_ptr, error_message);
}


----------------------------
static png_structp err_png_ptr = 0
----------------------------
***/


// hint:  ['sample_overflow_ref is a mutable refrence to int', 'row_ref is a mutable refrence to png_bytep', 'i_ref is a mutable refrence to unsigned int', 'j_ref is a mutable refrence to unsigned int']
void helper_pngx_read_tiff_1(int * const sample_overflow_ref, png_bytep * const row_ref, unsigned int * const i_ref, unsigned int * const j_ref, FILE * const stream, struct minitiff_info tiff_info, unsigned int width, unsigned int height, unsigned int pixel_size, unsigned int sample_depth, unsigned int sample_max, png_bytepp row_pointers)
{
  int sample_overflow = *sample_overflow_ref;
  png_bytep row = *row_ref;
  unsigned int i = *i_ref;
  unsigned int j = *j_ref;
  for (i = 0; i < height; i += 1)
  {
    row = row_pointers[i];
    minitiff_read_row(&tiff_info, row, i, stream);
    if (sample_depth < 8)
    {
      for (j = 0; j < (pixel_size * width); j += 1)
      {
        unsigned int b = row[j];
        if (b > sample_max)
        {
          b = sample_max;
          sample_overflow = 1;
        }
        row[j] = (png_byte) (((b * 255) + (sample_max / 2)) / sample_max);
      }

    }
    if (tiff_info.photometric == 0)
    {
      for (j = 0; j < (pixel_size * width); j += 1)
      {
        row[j] = (png_byte) (255 - row[j]);
      }

    }
  }

  *sample_overflow_ref = sample_overflow;
  *row_ref = row;
  *i_ref = i;
  *j_ref = j;
}


/*** DEPENDENCIES:
void minitiff_read_row(struct minitiff_info *info_ptr, unsigned char *row_ptr, size_t row_index, FILE *stream)
{
  size_t row_size;
  size_t strip_index;
  unsigned int bytes_per_sample;
  unsigned int sample_max;
  long offset;
  size_t i;
  bytes_per_sample = (info_ptr->bits_per_sample + 7) / 8;
  row_size = (info_ptr->width * info_ptr->samples_per_pixel) * bytes_per_sample;
  strip_index = row_index / info_ptr->rows_per_strip;
  if (strip_index >= info_ptr->strip_offsets_count)
  {
    goto err_invalid;
  }
  if (((long) info_ptr->strip_offsets[strip_index]) < 0)
  {
    goto err_range;
  }
  offset = (long) (info_ptr->strip_offsets[strip_index] + (row_size * (row_index % info_ptr->rows_per_strip)));
  seek_to_offset(info_ptr, offset, stream);
  if (fread(row_ptr, row_size, 1, stream) != 1)
  {
    goto err_read;
  }
  if (info_ptr->photometric == 0)
  {
    if (bytes_per_sample > 1)
    {
      goto err_unsupported;
    }
    sample_max = (1 << info_ptr->bits_per_sample) - 1;
    for (i = 0; i < row_size; i += 1)
    {
      row_ptr[i] = (unsigned char) (sample_max - row_ptr[i]);
    }

  }
  return;
  err_read:
  minitiff_error(info_ptr, msg_err_read);

  err_invalid:
  minitiff_error(info_ptr, msg_err_invalid);

  err_range:
  minitiff_error(info_ptr, msg_err_range);

  err_unsupported:
  minitiff_error(info_ptr, msg_err_unsupported);

}


----------------------------
struct minitiff_info
{
  void (*error_handler)(const char *msg);
  void (*warning_handler)(const char *msg);
  int byte_order;
  size_t width;
  size_t height;
  unsigned int bits_per_sample;
  unsigned int compression;
  unsigned int photometric;
  size_t strip_offsets_count;
  unsigned long *strip_offsets;
  unsigned int orientation;
  unsigned int samples_per_pixel;
  size_t rows_per_strip;
}
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_byte **png_bytepp
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


// hint:  ['sample_overflow_ref is a mutable refrence to int', 'row_ref is a mutable refrence to png_bytep', 'i_ref is a mutable refrence to unsigned int', 'j_ref is a mutable refrence to unsigned int', 'k_ref is a mutable refrence to unsigned int']
void helper_pngx_read_tiff_2(int * const sample_overflow_ref, png_bytep * const row_ref, unsigned int * const i_ref, unsigned int * const j_ref, unsigned int * const k_ref, FILE * const stream, struct minitiff_info tiff_info, unsigned int width, unsigned int height, unsigned int pixel_size, unsigned int sample_depth, unsigned int sample_max, png_bytepp row_pointers)
{
  int sample_overflow = *sample_overflow_ref;
  png_bytep row = *row_ref;
  unsigned int i = *i_ref;
  unsigned int j = *j_ref;
  unsigned int k = *k_ref;
  for (i = 0; i < height; i += 1)
  {
    row = row_pointers[i];
    minitiff_read_row(&tiff_info, row, i, stream);
    if (tiff_info.byte_order == 'I')
    {
      for (j = (k = 0); j < (pixel_size * width); j += 1, k += 2)
      {
        png_byte b = row[k];
        row[k] = row[k + 1];
        row[k + 1] = b;
      }

    }
    if (sample_depth < 16)
    {
      for (j = (k = 0); k < (pixel_size * width); j += 1, k += 2)
      {
        unsigned int b = (row[k] << 8) + row[k + 1];
        if (b > sample_max)
        {
          b = sample_max;
          sample_overflow = 1;
        }
        b = ((b * 65535U) + (sample_max / 2)) / sample_max;
        row[k] = (png_byte) (b >> 8);
        row[k + 1] = (png_byte) (b & 255);
      }

    }
  }

  *sample_overflow_ref = sample_overflow;
  *row_ref = row;
  *i_ref = i;
  *j_ref = j;
  *k_ref = k;
}


/*** DEPENDENCIES:
void minitiff_read_row(struct minitiff_info *info_ptr, unsigned char *row_ptr, size_t row_index, FILE *stream)
{
  size_t row_size;
  size_t strip_index;
  unsigned int bytes_per_sample;
  unsigned int sample_max;
  long offset;
  size_t i;
  bytes_per_sample = (info_ptr->bits_per_sample + 7) / 8;
  row_size = (info_ptr->width * info_ptr->samples_per_pixel) * bytes_per_sample;
  strip_index = row_index / info_ptr->rows_per_strip;
  if (strip_index >= info_ptr->strip_offsets_count)
  {
    goto err_invalid;
  }
  if (((long) info_ptr->strip_offsets[strip_index]) < 0)
  {
    goto err_range;
  }
  offset = (long) (info_ptr->strip_offsets[strip_index] + (row_size * (row_index % info_ptr->rows_per_strip)));
  seek_to_offset(info_ptr, offset, stream);
  if (fread(row_ptr, row_size, 1, stream) != 1)
  {
    goto err_read;
  }
  if (info_ptr->photometric == 0)
  {
    if (bytes_per_sample > 1)
    {
      goto err_unsupported;
    }
    sample_max = (1 << info_ptr->bits_per_sample) - 1;
    for (i = 0; i < row_size; i += 1)
    {
      row_ptr[i] = (unsigned char) (sample_max - row_ptr[i]);
    }

  }
  return;
  err_read:
  minitiff_error(info_ptr, msg_err_read);

  err_invalid:
  minitiff_error(info_ptr, msg_err_invalid);

  err_range:
  minitiff_error(info_ptr, msg_err_range);

  err_unsupported:
  minitiff_error(info_ptr, msg_err_unsupported);

}


----------------------------
struct minitiff_info
{
  void (*error_handler)(const char *msg);
  void (*warning_handler)(const char *msg);
  int byte_order;
  size_t width;
  size_t height;
  unsigned int bits_per_sample;
  unsigned int compression;
  unsigned int photometric;
  size_t strip_offsets_count;
  unsigned long *strip_offsets;
  unsigned int orientation;
  unsigned int samples_per_pixel;
  size_t rows_per_strip;
}
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_byte **png_bytepp
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


int pngx_read_tiff(png_structp png_ptr, png_infop info_ptr, FILE *stream)
{
  struct minitiff_info tiff_info;
  unsigned int width;
  unsigned int height;
  unsigned int pixel_size;
  unsigned int sample_depth;
  unsigned int sample_max;
  int color_type;
  int sample_overflow;
  png_bytepp row_pointers;
  png_bytep row;
  unsigned int i;
  unsigned int j;
  unsigned int k;
  err_png_ptr = png_ptr;
  num_extra_images = 0;
  minitiff_init_info(&tiff_info);
  tiff_info.error_handler = pngx_tiff_error;
  tiff_info.warning_handler = pngx_tiff_warning;
  minitiff_read_info(&tiff_info, stream);
  minitiff_validate_info(&tiff_info);
  width = (unsigned int) tiff_info.width;
  height = (unsigned int) tiff_info.height;
  pixel_size = tiff_info.samples_per_pixel;
  sample_depth = tiff_info.bits_per_sample;
  switch (pixel_size)
  {
    case 1:
    {
      color_type = 0;
      break;
    }

    case 2:
    {
      color_type = 4;
      break;
    }

    case 3:
    {
      color_type = 2;
      break;
    }

    case 4:
    {
      color_type = 2 | 4;
      break;
    }

    default:
    {
      png_error(png_ptr, "Unsupported TIFF color space");
      return 0;
    }

  }

  if (sample_depth > 16)
  {
    png_error(png_ptr, "Unsupported TIFF sample depth");
  }
  sample_max = (1 << sample_depth) - 1;
  sample_overflow = 0;
  png_set_IHDR(png_ptr, info_ptr, width, height, (sample_depth <= 8) ? (8) : (16), color_type, 0, 0, 0);
  row_pointers = pngx_malloc_rows(png_ptr, info_ptr, 0);
  if (sample_depth <= 8)
  {
    helper_pngx_read_tiff_1(&sample_overflow, &row, &i, &j, stream, tiff_info, width, height, pixel_size, sample_depth, sample_max, row_pointers);
  }
  else
  {
    helper_pngx_read_tiff_2(&sample_overflow, &row, &i, &j, &k, stream, tiff_info, width, height, pixel_size, sample_depth, sample_max, row_pointers);
  }
  if (sample_overflow)
  {
    png_warning(png_ptr, "Overflow in TIFF samples");
  }
  minitiff_destroy_info(&tiff_info);
  return 1 + num_extra_images;
}


/*** DEPENDENCIES:
void minitiff_read_info(struct minitiff_info *info_ptr, FILE *stream)
{
  struct minitiff_getter getter;
  unsigned char buf[12];
  unsigned char *vbuf = buf + 8;
  unsigned long ulvals[4];
  unsigned long ulval;
  long dir_offset;
  unsigned int dir_size;
  unsigned int i;
  unsigned int tag_id;
  unsigned int tag_type;
  size_t count;
  size_t bits_per_sample_count;
  unsigned int bits_per_sample_tag_type;
  unsigned int strip_offsets_tag_type;
  long bits_per_sample_offset;
  long strip_offsets_offset;
  int unknown_metadata_found;
  if (fread(buf, 8, 1, stream) != 1)
  {
    goto err_read;
  }
  if (memcmp(buf, minitiff_sig_m, 4) == 0)
  {
    info_ptr->byte_order = 'M';
    getter.get_ushort = get_ushort_m;
    getter.get_ulong = get_ulong_m;
  }
  else
    if (memcmp(buf, minitiff_sig_i, 4) == 0)
  {
    info_ptr->byte_order = 'I';
    getter.get_ushort = get_ushort_i;
    getter.get_ulong = get_ulong_i;
  }
  else
    if ((memcmp(buf, minitiff_sig_bigm, 4) == 0) || (memcmp(buf, minitiff_sig_bigi, 4) == 0))
  {
    minitiff_error(info_ptr, msg_err_bigtiff);
    return;
  }
  else
  {
    minitiff_error(info_ptr, msg_err_notiff);
    return;
  }
  bits_per_sample_count = 0;
  bits_per_sample_tag_type = (strip_offsets_tag_type = 0);
  bits_per_sample_offset = (strip_offsets_offset = 0);
  dir_offset = (long) getter.get_ulong(buf + 4);
  if ((dir_offset >= 0) && (dir_offset < 8))
  {
    goto err_invalid;
  }
  seek_to_offset(info_ptr, dir_offset, stream);
  if (fread(buf, 2, 1, stream) != 1)
  {
    goto err_read;
  }
  dir_size = getter.get_ushort(buf);
  unknown_metadata_found = 0;
  for (i = 0; i < dir_size; i += 1)
  {
    helper_minitiff_read_info_2(&ulval, &tag_id, &tag_type, &count, &bits_per_sample_count, &bits_per_sample_tag_type, &strip_offsets_tag_type, &bits_per_sample_offset, &strip_offsets_offset, &unknown_metadata_found, info_ptr, stream, getter, buf, vbuf);
  }

  if (fread(buf, 4, 1, stream) != 1)
  {
    goto err_read;
  }
  if (getter.get_ulong(buf) != 0)
  {
    minitiff_warning(info_ptr, msg_warn_multiple);
  }
  if (bits_per_sample_offset != 0)
  {
    helper_minitiff_read_info_1(&count, info_ptr, stream, getter, ulvals, bits_per_sample_count, bits_per_sample_tag_type, bits_per_sample_offset);
  }
  if (strip_offsets_offset != 0)
  {
    count = info_ptr->strip_offsets_count;
    if ((count == 0) || (count > info_ptr->height))
    {
      goto err_invalid;
    }
    if (info_ptr->strip_offsets != 0)
    {
      goto err_invalid;
    }
    info_ptr->strip_offsets = alloc_ulong_array(info_ptr, count);
    seek_to_offset(info_ptr, strip_offsets_offset, stream);
    if (read_ulong_values(&getter, strip_offsets_tag_type, info_ptr->strip_offsets, count, stream) != count)
    {
      goto err_read;
    }
  }
  return;
  err_read:
  minitiff_error(info_ptr, msg_err_read);

  err_invalid:
  minitiff_error(info_ptr, msg_err_invalid);

  err_unsupported:
  minitiff_error(info_ptr, msg_err_unsupported);

}


----------------------------
void minitiff_destroy_info(struct minitiff_info *info_ptr)
{
  if (info_ptr->strip_offsets != 0)
  {
    free(info_ptr->strip_offsets);
  }
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
static void pngx_tiff_error(const char *msg)
{
  png_error(err_png_ptr, msg);
}


----------------------------
typedef png_byte **png_bytepp
----------------------------
static unsigned int num_extra_images
----------------------------
typedef png_byte *png_bytep
----------------------------
typedef png_struct *png_structp
----------------------------
struct minitiff_info
{
  void (*error_handler)(const char *msg);
  void (*warning_handler)(const char *msg);
  int byte_order;
  size_t width;
  size_t height;
  unsigned int bits_per_sample;
  unsigned int compression;
  unsigned int photometric;
  size_t strip_offsets_count;
  unsigned long *strip_offsets;
  unsigned int orientation;
  unsigned int samples_per_pixel;
  size_t rows_per_strip;
}
----------------------------
typedef struct png_info_def png_info
----------------------------
void helper_pngx_read_tiff_1(int * const sample_overflow_ref, png_bytep * const row_ref, unsigned int * const i_ref, unsigned int * const j_ref, FILE * const stream, struct minitiff_info tiff_info, unsigned int width, unsigned int height, unsigned int pixel_size, unsigned int sample_depth, unsigned int sample_max, png_bytepp row_pointers)
{
  int sample_overflow = *sample_overflow_ref;
  png_bytep row = *row_ref;
  unsigned int i = *i_ref;
  unsigned int j = *j_ref;
  for (i = 0; i < height; i += 1)
  {
    row = row_pointers[i];
    minitiff_read_row(&tiff_info, row, i, stream);
    if (sample_depth < 8)
    {
      for (j = 0; j < (pixel_size * width); j += 1)
      {
        unsigned int b = row[j];
        if (b > sample_max)
        {
          b = sample_max;
          sample_overflow = 1;
        }
        row[j] = (png_byte) (((b * 255) + (sample_max / 2)) / sample_max);
      }

    }
    if (tiff_info.photometric == 0)
    {
      for (j = 0; j < (pixel_size * width); j += 1)
      {
        row[j] = (png_byte) (255 - row[j]);
      }

    }
  }

  *sample_overflow_ref = sample_overflow;
  *row_ref = row;
  *i_ref = i;
  *j_ref = j;
}


----------------------------
static void pngx_tiff_warning(const char *msg)
{
  if (strstr(msg, "multi-image") != 0)
  {
    num_extra_images += 1;
  }
}


----------------------------
typedef unsigned char png_byte
----------------------------
void minitiff_validate_info(const struct minitiff_info *info_ptr)
{
  if ((info_ptr->width == 0) || (info_ptr->height == 0))
  {
    minitiff_error(info_ptr, "Invalid image dimensions in TIFF file");
  }
  if ((info_ptr->bits_per_sample == 0) || (info_ptr->samples_per_pixel == 0))
  {
    minitiff_error(info_ptr, "Invalid pixel info in TIFF file");
  }
  if ((info_ptr->strip_offsets == 0) || (info_ptr->rows_per_strip == 0))
  {
    minitiff_error(info_ptr, "Invalid strip info in TIFF file");
  }
  if (info_ptr->compression != MINITIFF_COMPRESSION_NONE)
  {
    minitiff_error(info_ptr, "Unsupported compression method in TIFF file");
  }
  if (info_ptr->photometric >= MINITIFF_PHOTOMETRIC_PALETTE)
  {
    minitiff_error(info_ptr, "Unsupported photometric interpretation in TIFF file");
  }
}


----------------------------
void minitiff_init_info(struct minitiff_info *info_ptr)
{
  memset(info_ptr, 0, sizeof(*info_ptr));
  info_ptr->photometric = (unsigned int) (-1);
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
static png_structp err_png_ptr = 0
----------------------------
typedef struct png_struct_def png_struct
----------------------------
png_bytepp pngx_malloc_rows(png_structp png_ptr, png_infop info_ptr, int filler)
{
  return pngx_malloc_rows_extended(png_ptr, info_ptr, 0, filler);
}


----------------------------
void helper_pngx_read_tiff_2(int * const sample_overflow_ref, png_bytep * const row_ref, unsigned int * const i_ref, unsigned int * const j_ref, unsigned int * const k_ref, FILE * const stream, struct minitiff_info tiff_info, unsigned int width, unsigned int height, unsigned int pixel_size, unsigned int sample_depth, unsigned int sample_max, png_bytepp row_pointers)
{
  int sample_overflow = *sample_overflow_ref;
  png_bytep row = *row_ref;
  unsigned int i = *i_ref;
  unsigned int j = *j_ref;
  unsigned int k = *k_ref;
  for (i = 0; i < height; i += 1)
  {
    row = row_pointers[i];
    minitiff_read_row(&tiff_info, row, i, stream);
    if (tiff_info.byte_order == 'I')
    {
      for (j = (k = 0); j < (pixel_size * width); j += 1, k += 2)
      {
        png_byte b = row[k];
        row[k] = row[k + 1];
        row[k + 1] = b;
      }

    }
    if (sample_depth < 16)
    {
      for (j = (k = 0); k < (pixel_size * width); j += 1, k += 2)
      {
        unsigned int b = (row[k] << 8) + row[k + 1];
        if (b > sample_max)
        {
          b = sample_max;
          sample_overflow = 1;
        }
        b = ((b * 65535U) + (sample_max / 2)) / sample_max;
        row[k] = (png_byte) (b >> 8);
        row[k + 1] = (png_byte) (b & 255);
      }

    }
  }

  *sample_overflow_ref = sample_overflow;
  *row_ref = row;
  *i_ref = i;
  *j_ref = j;
  *k_ref = k;
}


----------------------------
***/


int pngx_sig_is_tiff(png_bytep sig, size_t sig_size, png_const_charpp fmt_name_ptr, png_const_charpp fmt_long_name_ptr)
{
  if (sig_size < 8)
  {
    return -1;
  }
  if ((memcmp(sig, minitiff_sig_m, 4) != 0) && (memcmp(sig, minitiff_sig_i, 4) != 0))
  {
    return 0;
  }
  if (fmt_name_ptr != 0)
  {
    *fmt_name_ptr = tiff_fmt_name;
  }
  if (fmt_long_name_ptr != 0)
  {
    *fmt_long_name_ptr = tiff_fmt_long_name;
  }
  return 1;
}


/*** DEPENDENCIES:
extern const char minitiff_sig_m[4]
----------------------------
typedef unsigned char png_byte
----------------------------
static const char tiff_fmt_long_name[] = "Tagged Image File Format"
----------------------------
static const char tiff_fmt_name[] = "TIFF"
----------------------------
extern const char minitiff_sig_i[4]
----------------------------
typedef const char *png_const_charp
----------------------------
typedef png_byte *png_bytep
----------------------------
typedef const char **png_const_charpp
----------------------------
***/


