static int pngx_sig_is_png(png_structp png_ptr, png_bytep sig, size_t sig_size, png_const_charpp fmt_name_ptr, png_const_charpp fmt_long_name_ptr)
{
  static const char pngx_png_standalone_fmt_name[] = "PNG";
  static const char pngx_png_datastream_fmt_name[] = "PNG datastream";
  static const char pngx_png_standalone_fmt_long_name[] = "Portable Network Graphics";
  static const char pngx_png_datastream_fmt_long_name[] = "Portable Network Graphics embedded datastream";
  static const png_byte png_file_sig[8] = {137, 80, 78, 71, 13, 10, 26, 10};
  static const png_byte mng_file_sig[8] = {138, 77, 78, 71, 13, 10, 26, 10};
  static const png_byte png_ihdr_sig[8] = {0, 0, 0, 13, 73, 72, 68, 82};
  int has_png_sig;
  if (sig_size <= (25 + 18))
  {
    return -1;
  }
  has_png_sig = memcmp(sig, png_file_sig, 8) == 0;
  if (memcmp(sig + ((has_png_sig) ? (8) : (0)), png_ihdr_sig, 8) != 0)
  {
    if ((memcmp(sig, png_file_sig, 4) == 0) && ((sig[4] == 10) || (sig[4] == 13)))
    {
      png_error(png_ptr, "PNG file appears to be corrupted by text file conversions");
    }
    else
      if (memcmp(sig, mng_file_sig, 8) == 0)
    {
      png_error(png_ptr, "MNG decoding is not supported");
    }
    return 0;
  }
  if (fmt_name_ptr != 0)
  {
    *fmt_name_ptr = (has_png_sig) ? (pngx_png_standalone_fmt_name) : (pngx_png_datastream_fmt_name);
  }
  if (fmt_long_name_ptr != 0)
  {
    *fmt_long_name_ptr = (has_png_sig) ? (pngx_png_standalone_fmt_long_name) : (pngx_png_datastream_fmt_long_name);
  }
  return 1;
}


/*** DEPENDENCIES:
typedef png_struct *png_structp
----------------------------
typedef const char **png_const_charpp
----------------------------
typedef unsigned char png_byte
----------------------------
typedef const char *png_const_charp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef png_byte *png_bytep
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
***/


int pngx_read_image(png_structp png_ptr, png_infop info_ptr, png_const_charpp fmt_name_ptr, png_const_charpp fmt_long_name_ptr)
{
  png_byte sig[128];
  size_t num;
  int (*read_fn)(png_structp, png_infop, FILE *);
  unsigned int read_fn_idx = 0;
  FILE *stream;
  unsigned int stream_idx = 0;
  fpos_t fpos;
  int result;
  stream_idx = (FILE *) png_get_io_ptr(png_ptr);
  if (fgetpos(stream, &fpos) != 0)
  {
    png_error(png_ptr, "Can't ftell in input file stream");
  }
  num = fread(sig, 1, sizeof(sig), stream);
  if (fsetpos(stream, &fpos) != 0)
  {
    png_error(png_ptr, "Can't fseek in input file stream");
  }
  if (pngx_sig_is_png(png_ptr, sig, num, fmt_name_ptr, fmt_long_name_ptr) > 0)
  {
    png_read_png(png_ptr, info_ptr, 0, 0);
    if (getc(stream) != EOF)
    {
      png_warning(png_ptr, "Extraneous data found after IEND");
      fseek(stream, 0, 2);
    }
    return 1;
  }
  if (pngx_sig_is_bmp(sig, num, fmt_name_ptr, fmt_long_name_ptr) > 0)
  {
    read_fn_idx = pngx_read_bmp;
  }
  else
    if (pngx_sig_is_gif(sig, num, fmt_name_ptr, fmt_long_name_ptr) > 0)
  {
    read_fn_idx = pngx_read_gif;
  }
  else
    if (pngx_sig_is_jpeg(sig, num, fmt_name_ptr, fmt_long_name_ptr) > 0)
  {
    read_fn_idx = pngx_read_jpeg;
  }
  else
    if (pngx_sig_is_pnm(sig, num, fmt_name_ptr, fmt_long_name_ptr) > 0)
  {
    read_fn_idx = pngx_read_pnm;
  }
  else
    if (pngx_sig_is_tiff(sig, num, fmt_name_ptr, fmt_long_name_ptr) > 0)
  {
    read_fn_idx = pngx_read_tiff;
  }
  else
    return 0;
  result = read_fn(png_ptr, info_ptr, stream);
  if (result <= 0)
  {
    if (fsetpos(stream, &fpos) != 0)
    {
      png_error(png_ptr, "Can't fseek in input file stream");
    }
  }
  return result;
}


/*** DEPENDENCIES:
int pngx_sig_is_jpeg(png_bytep sig, size_t sig_size, png_const_charpp fmt_name_ptr, png_const_charpp fmt_long_name_ptr)
{
  const char *fmt;
  unsigned int fmt_idx = 0;
  unsigned int marker;
  int result;
  if (sig_size < 12)
  {
    return -1;
  }
  if (((sig[0] == 0xff) && (sig[1] == 0xd8)) && (sig[2] == 0xff))
  {
    marker = 0xff00U | sig[3];
    if (((marker >= 0xffc0U) && (marker <= 0xffcfU)) || ((marker >= 0xffdaU) && (marker <= 0xfffeU)))
    {
      fmt_idx = "JPEG";
      result = 1;
    }
    else
      return 0;
  }
  else
    if ((memcmp(sig, jpeg_sig_jp2, 12) == 0) || (memcmp(sig, jpeg_sig_jpc, 4) == 0))
  {
    fmt_idx = "JPEG-2000";
    result = 2;
  }
  else
    if ((memcmp(sig, jpeg_sig_jng, 8) == 0) || (memcmp(sig, jpeg_sig_jng_jhdr, 8) == 0))
  {
    fmt_idx = "JNG";
    result = 3;
  }
  else
    return 0;
  if (fmt_name_ptr != 0)
  {
    *fmt_name_ptr = &fmt[fmt_idx];
  }
  if (fmt_long_name_ptr != 0)
  {
    *fmt_long_name_ptr = &fmt[fmt_idx];
  }
  return result;
}


----------------------------
void png_read_png(png_structrp png_ptr, png_inforp info_ptr, int transforms, voidp params)
{
  if ((png_ptr == 0) || (info_ptr == 0))
  {
    return;
  }
  png_read_info(png_ptr, info_ptr);
  if (info_ptr->height > (((png_uint_32) (-1)) / (sizeof(png_bytep))))
  {
    png_error(png_ptr, "Image is too high to process with png_read_png()");
  }
  if ((transforms & 0x8000) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_SCALE_16 not supported");
  }
  if ((transforms & 0x0001) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_STRIP_16 not supported");
  }
  if ((transforms & 0x0002) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_STRIP_ALPHA not supported");
  }
  if ((transforms & 0x0004) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_PACKING not supported");
  }
  if ((transforms & 0x0008) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_PACKSWAP not supported");
  }
  if ((transforms & 0x0010) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_EXPAND not supported");
  }
  if ((transforms & 0x0020) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_INVERT_MONO not supported");
  }
  if ((transforms & 0x0040) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_SHIFT not supported");
  }
  if ((transforms & 0x0080) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_BGR not supported");
  }
  if ((transforms & 0x0100) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_SWAP_ALPHA not supported");
  }
  if ((transforms & 0x0200) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_SWAP_ENDIAN not supported");
  }
  if ((transforms & 0x0400) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_INVERT_ALPHA not supported");
  }
  if ((transforms & 0x2000) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_GRAY_TO_RGB not supported");
  }
  if ((transforms & 0x4000) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_EXPAND_16 not supported");
  }
  (void) png_set_interlace_handling(png_ptr);
  png_read_update_info(png_ptr, info_ptr);
  png_free_data(png_ptr, info_ptr, 0x0040U, 0);
  if (info_ptr->row_pointers == 0)
  {
    png_uint_32 iptr;
    info_ptr->row_pointers = png_malloc(png_ptr, info_ptr->height * (sizeof(png_bytep)));
    for (iptr = 0; iptr < info_ptr->height; iptr += 1)
    {
      info_ptr->row_pointers[iptr] = 0;
    }

    info_ptr->free_me |= 0x0040U;
    for (iptr = 0; iptr < info_ptr->height; iptr += 1)
    {
      info_ptr->row_pointers[iptr] = png_malloc(png_ptr, info_ptr->rowbytes);
    }

  }
  png_read_image(png_ptr, info_ptr->row_pointers);
  info_ptr->valid |= 0x8000U;
  png_read_end(png_ptr, info_ptr);
  (void) params;
}


----------------------------
static int pngx_sig_is_png(png_structp png_ptr, png_bytep sig, size_t sig_size, png_const_charpp fmt_name_ptr, png_const_charpp fmt_long_name_ptr)
{
  static const char pngx_png_standalone_fmt_name[] = "PNG";
  static const char pngx_png_datastream_fmt_name[] = "PNG datastream";
  static const char pngx_png_standalone_fmt_long_name[] = "Portable Network Graphics";
  static const char pngx_png_datastream_fmt_long_name[] = "Portable Network Graphics embedded datastream";
  static const png_byte png_file_sig[8] = {137, 80, 78, 71, 13, 10, 26, 10};
  static const png_byte mng_file_sig[8] = {138, 77, 78, 71, 13, 10, 26, 10};
  static const png_byte png_ihdr_sig[8] = {0, 0, 0, 13, 73, 72, 68, 82};
  int has_png_sig;
  if (sig_size <= (25 + 18))
  {
    return -1;
  }
  has_png_sig = memcmp(sig, png_file_sig, 8) == 0;
  if (memcmp(sig + ((has_png_sig) ? (8) : (0)), png_ihdr_sig, 8) != 0)
  {
    if ((memcmp(sig, png_file_sig, 4) == 0) && ((sig[4] == 10) || (sig[4] == 13)))
    {
      png_error(png_ptr, "PNG file appears to be corrupted by text file conversions");
    }
    else
      if (memcmp(sig, mng_file_sig, 8) == 0)
    {
      png_error(png_ptr, "MNG decoding is not supported");
    }
    return 0;
  }
  if (fmt_name_ptr != 0)
  {
    *fmt_name_ptr = (has_png_sig) ? (pngx_png_standalone_fmt_name) : (pngx_png_datastream_fmt_name);
  }
  if (fmt_long_name_ptr != 0)
  {
    *fmt_long_name_ptr = (has_png_sig) ? (pngx_png_standalone_fmt_long_name) : (pngx_png_datastream_fmt_long_name);
  }
  return 1;
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


----------------------------
int pngx_sig_is_gif(png_bytep sig, size_t sig_size, png_const_charpp fmt_name_ptr, png_const_charpp fmt_long_name_ptr)
{
  if (sig_size < (6 + 7))
  {
    return -1;
  }
  if ((memcmp(sig, gif_sig_gif87a, 6) != 0) && (memcmp(sig, gif_sig_gif89a, 6) != 0))
  {
    return 0;
  }
  if (fmt_name_ptr != 0)
  {
    *fmt_name_ptr = gif_fmt_name;
  }
  if (fmt_long_name_ptr != 0)
  {
    *fmt_long_name_ptr = gif_fmt_long_name;
  }
  return 1;
}


----------------------------
int pngx_read_bmp(png_structp png_ptr, png_infop info_ptr, FILE *stream)
{
  png_byte bfh[14 + 124];
  const png_bytep bih = bfh + 14;
  png_byte rgbq[4];
  png_uint_32 offbits;
  png_uint_32 bihsize;
  png_uint_32 skip;
  png_uint_32 width;
  png_uint_32 height;
  png_uint_32 rowsize;
  int topdown;
  unsigned int pixdepth;
  png_uint_32 compression;
  unsigned int palsize;
  unsigned int palnum;
  png_uint_32 rgba_mask[4];
  png_byte rgba_sig[4];
  png_byte rgba_shift[4];
  int bit_depth;
  int color_type;
  png_color palette[256];
  png_color_8 sig_bit;
  png_bytepp row_pointers;
  png_bytepp begin_row;
  png_bytepp end_row;
  unsigned int i;
  size_t y;
  for (i = 0;; i += 1)
  {
    if (fread(bfh, 14 + 4, 1, stream) != 1)
    {
      i += 1;
    }
    else
      if (bmp_get_word(bfh + 0) == 0x4d42)
    {
      break;
    }
    if (fread(bfh, (128 - 14) - 4, 1, stream) != 1)
    {
      i += 1;
    }
    if (i > 0)
    {
      return 0;
    }
  }

  offbits = bmp_get_dword(bfh + 10);
  bihsize = bmp_get_dword(bfh + 14);
  if ((((offbits > ((png_uint_32) 0x7fffffffL)) || (bihsize > ((png_uint_32) 0x7fffffffL))) || (offbits < (bihsize + 14))) || ((bihsize != 12) && (bihsize < 40)))
  {
    return 0;
  }
  if (bihsize > 124)
  {
    skip = bihsize - 124;
    bihsize = 124;
  }
  else
    skip = 0;
  if (fread(bih + 4, bihsize - 4, 1, stream) != 1)
  {
    return 0;
  }
  if (skip > 0)
  {
    if (fseek(stream, (long) skip, 1) != 0)
    {
      return 0;
    }
  }
  skip = (offbits - bihsize) - 14;
  topdown = 0;
  if (bihsize < 40)
  {
    width = bmp_get_word(bih + 4);
    height = bmp_get_word(bih + 6);
    pixdepth = bmp_get_word(bih + 10);
    compression = 0;
    palsize = 3;
  }
  else
  {
    helper_pngx_read_bmp_1(&bihsize, &skip, &width, &height, &topdown, &pixdepth, &compression, &palsize, &i, stream, bih);
  }
  memset(rgba_mask, 0, sizeof(rgba_mask));
  if (pixdepth > 8)
  {
    helper_pngx_read_bmp_3(&compression, png_ptr, bih, bihsize, pixdepth, rgba_mask);
  }
  switch (compression)
  {
    case 0:
    {
      if (((pixdepth > 0) && ((32 % pixdepth) != 0)) && (pixdepth != 24))
      {
        pixdepth = 0;
      }
      break;
    }

    case 1:
    {
      if (pixdepth != 8)
      {
        pixdepth = 0;
      }
      break;
    }

    case 2:
    {
      if (pixdepth != 4)
      {
        pixdepth = 0;
      }
      break;
    }

    case 3:
    {
      if ((pixdepth != 16) && (pixdepth != 32))
      {
        pixdepth = 0;
      }
      break;
    }

    case 4:
    {
      png_error(png_ptr, "JPEG-compressed BMP files are not supported");
      break;
    }

    case 5:
    {
      if (ungetc(getc(stream), stream) == 0)
      {
        png_set_sig_bytes(png_ptr, 8);
      }
      png_set_read_fn(png_ptr, stream, 0);
      png_read_png(png_ptr, info_ptr, 0, 0);
      return 1;
    }

    default:
    {
      png_error(png_ptr, "Unsupported compression method in BMP file");
    }

  }

  if (((width == 0) || (width > ((png_uint_32) 0x7fffffffL))) || (height == 0))
  {
    png_error(png_ptr, "Invalid image dimensions in BMP file");
  }
  if (pixdepth == 0)
  {
    png_error(png_ptr, "Invalid pixel depth in BMP file");
  }
  if (pixdepth <= 8)
  {
    palnum = skip / palsize;
    if (palnum > 256)
    {
      palnum = 256;
    }
    skip -= palsize * palnum;
    rowsize = (((width + (32 / pixdepth)) - 1) / (32 / pixdepth)) * 4;
    bit_depth = pixdepth;
    color_type = (palnum > 0) ? (2 | 1) : (0);
  }
  else
  {
    helper_pngx_read_bmp_2(&rowsize, &palnum, &bit_depth, &color_type, width, pixdepth, rgba_mask);
  }
  if (rowsize == 0)
  {
    png_error(png_ptr, "Can't handle exceedingly large BMP dimensions");
  }
  png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type, 0, 0, 0);
  if (pixdepth > 8)
  {
    for (i = 0; i < 4; i += 1)
    {
      bmp_process_mask(rgba_mask[i], &rgba_sig[i], &rgba_shift[i]);
    }

    if (((rgba_sig[0] == 0) || (rgba_sig[1] == 0)) || (rgba_sig[2] == 0))
    {
      png_error(png_ptr, "Invalid color mask in BMP file");
    }
    if ((((rgba_sig[0] != 8) || (rgba_sig[1] != 8)) || (rgba_sig[2] != 8)) || ((rgba_sig[3] != 0) && (rgba_sig[3] != 8)))
    {
      sig_bit.red = rgba_sig[0];
      sig_bit.green = rgba_sig[1];
      sig_bit.blue = rgba_sig[2];
      sig_bit.alpha = rgba_sig[3];
      png_set_sBIT(png_ptr, info_ptr, &sig_bit);
    }
  }
  if (palnum > 0)
  {
    for (i = 0; i < palnum; i += 1)
    {
      if (fread(rgbq, palsize, 1, stream) != 1)
      {
        break;
      }
      palette[i].red = rgbq[2];
      palette[i].green = rgbq[1];
      palette[i].blue = rgbq[0];
    }

    png_set_PLTE(png_ptr, info_ptr, palette, i);
    if (i != palnum)
    {
      png_error(png_ptr, "Error reading color palette in BMP file");
    }
  }
  row_pointers = pngx_malloc_rows_extended(png_ptr, info_ptr, rowsize, -1);
  if (topdown)
  {
    begin_row = row_pointers;
    end_row = row_pointers + height;
  }
  else
  {
    begin_row = (row_pointers + height) - 1;
    end_row = row_pointers - 1;
  }
  if (skip > 0)
  {
    fseek(stream, (long) skip, 1);
  }
  y = bmp_read_rows(begin_row, end_row, rowsize, compression, stream);
  if (pixdepth > 8)
  {
    bmp_to_png_rows(row_pointers, width, height, pixdepth, rgba_sig, rgba_shift);
  }
  if (y != ((size_t) height))
  {
    png_error(png_ptr, "Error reading BMP file");
  }
  return 1;
}


----------------------------
typedef png_struct *png_structp
----------------------------
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


----------------------------
typedef const char *png_const_charp
----------------------------
typedef struct png_info_def png_info
----------------------------
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


----------------------------
int pngx_read_jpeg(png_structp png_ptr, png_infop info_ptr, FILE *stream)
{
  png_byte buf[12];
  int sig_code;
  if (fread(buf, 12, 1, stream) != 1)
  {
    return 0;
  }
  sig_code = pngx_sig_is_jpeg(buf, 12, 0, 0);
  switch (sig_code)
  {
    case 1:
    {
      png_error(png_ptr, "JPEG decoding is not supported");
      break;
    }

    case 2:
    {
      png_error(png_ptr, "JPEG-2000 decoding is not supported");
      break;
    }

    case 3:
    {
      png_error(png_ptr, "JNG (JPEG) decoding is not supported");
      break;
    }

  }

  if (info_ptr == 0)
  {
    return 0;
  }
  return 0;
}


----------------------------
typedef unsigned char png_byte
----------------------------
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


----------------------------
typedef const char **png_const_charpp
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
int pngx_read_gif(png_structp png_ptr, png_infop info_ptr, FILE *stream)
{
  struct GIFScreen screen;
  struct GIFImage image;
  struct GIFExtension ext;
  struct GIFGraphicCtlExt graphicExt;
  int blockCode;
  unsigned char *colorTable;
  unsigned int numColors;
  unsigned int transparent;
  unsigned int numImages;
  png_uint_32 width;
  png_uint_32 height;
  png_bytepp row_pointers;
  GIFError = pngx_gif_error;
  GIFWarning = pngx_gif_warning;
  err_png_ptr = png_ptr;
  err_gif_image_ptr = 0;
  err_gif_ext_ptr = 0;
  GIFReadScreen(&screen, stream);
  width = screen.Width;
  height = screen.Height;
  png_set_IHDR(png_ptr, info_ptr, width, height, 8, 2 | 1, 0, 0, 0);
  row_pointers = pngx_malloc_rows(png_ptr, info_ptr, (int) screen.Background);
  GIFInitImage(&image, &screen, row_pointers);
  err_gif_image_ptr = &image;
  GIFInitExtension(&ext, &screen, 256);
  err_gif_ext_ptr = &ext;
  numImages = 0;
  transparent = (unsigned int) (-1);
  for (;;)
  {
    helper_pngx_read_gif_1(&image, &blockCode, &transparent, &numImages, png_ptr, info_ptr, stream, ext, graphicExt, colorTable, numColors);
  }

  if (image.Rows != 0)
  {
    png_error(png_ptr, "No image in GIF file");
  }
  GIFDestroyImage(&image);
  GIFDestroyExtension(&ext);
  return numImages;
}


----------------------------
int pngx_sig_is_bmp(png_bytep sig, size_t sig_size, png_const_charpp fmt_name_ptr, png_const_charpp fmt_long_name_ptr)
{
  static const char bmp_fmt_name[] = "BMP";
  static const char os2bmp_fmt_long_name[] = "OS/2 Bitmap";
  static const char winbmp_fmt_long_name[] = "Windows Bitmap";
  png_uint_32 bihsize;
  if (sig_size < (14 + 4))
  {
    return -1;
  }
  if (bmp_get_word(sig) != 0x4d42)
  {
    return 0;
  }
  bihsize = bmp_get_dword(sig + 14);
  if ((bihsize > ((png_uint_32) 0x7fffffffL)) || ((bihsize != 12) && (bihsize < 40)))
  {
    return 0;
  }
  if (fmt_name_ptr != 0)
  {
    *fmt_name_ptr = bmp_fmt_name;
  }
  if (fmt_long_name_ptr != 0)
  {
    if (bihsize == 12)
    {
      *fmt_long_name_ptr = os2bmp_fmt_long_name;
    }
    else
      *fmt_long_name_ptr = winbmp_fmt_long_name;
  }
  return 1;
}


----------------------------
typedef png_info *png_infop
----------------------------
png_voidp png_get_io_ptr(png_const_structrp png_ptr)
{
  if (png_ptr == 0)
  {
    return 0;
  }
  return png_ptr->io_ptr;
}


----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


