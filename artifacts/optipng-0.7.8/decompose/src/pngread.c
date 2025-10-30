png_structp png_create_read_struct(png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn)
{
  png_structp png_ptr = png_create_png_struct(user_png_ver, error_ptr, error_fn, warn_fn, 0, 0, 0);
  if (png_ptr != 0)
  {
    png_ptr->mode = 0x8000U;
    png_ptr->IDAT_read_size = 8192;
    png_ptr->flags |= 0x100000U;
    png_ptr->flags |= 0x200000U;
    png_set_read_fn(png_ptr, 0, 0);
  }
  return png_ptr;
}


/*** DEPENDENCIES:
typedef void *png_voidp
----------------------------
typedef void *voidp
----------------------------
typedef png_struct *png_structp
----------------------------
png_structp png_create_png_struct(png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn, png_voidp mem_ptr, png_malloc_ptr malloc_fn, png_free_ptr free_fn)
{
  png_struct create_struct;
  memset(&create_struct, 0, sizeof(create_struct));
  create_struct.user_width_max = 1000000;
  create_struct.user_height_max = 1000000;
  create_struct.user_chunk_cache_max = 1000;
  create_struct.user_chunk_malloc_max = 8000000;
  (void) mem_ptr;
  (void) malloc_fn;
  (void) free_fn;
  png_set_error_fn(&create_struct, error_ptr, error_fn, warn_fn);
  {
    if (png_user_version_check(&create_struct, user_png_ver) != 0)
    {
      png_structrp png_ptr = png_malloc_warn(&create_struct, sizeof(*png_ptr));
      if (png_ptr != 0)
      {
        create_struct.zstream.zalloc = png_zalloc;
        create_struct.zstream.zfree = png_zfree;
        create_struct.zstream.opaque = png_ptr;
        *png_ptr = create_struct;
        return png_ptr;
      }
    }
  }
  return 0;
}


----------------------------
typedef void (*png_error_ptr)(png_structp, png_const_charp)
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef const char *png_const_charp
----------------------------
void png_set_read_fn(png_structrp png_ptr, png_voidp io_ptr, png_rw_ptr read_data_fn)
{
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->io_ptr = io_ptr;
  if (read_data_fn != 0)
  {
    png_ptr->read_data_fn = read_data_fn;
  }
  else
    png_ptr->read_data_fn = png_default_read_data;
  if (png_ptr->write_data_fn != 0)
  {
    png_ptr->write_data_fn = 0;
    png_warning(png_ptr, "Can't set both read_data_fn and write_data_fn in the same structure");
  }
  png_ptr->output_flush_fn = 0;
}


----------------------------
***/


// hint:  ['png_ptr_ref is a mutable refrence to png_structrp', 'keep_ref is a mutable refrence to int']
void helper_png_read_info_1(png_structrp * const png_ptr_ref, int * const keep_ref, png_inforp info_ptr)
{
  png_structrp png_ptr = *png_ptr_ref;
  int keep = *keep_ref;
  png_uint_32 length = png_read_chunk_header(png_ptr);
  png_uint_32 chunk_name = png_ptr->chunk_name;
  if (chunk_name == ((((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)))
  {
    if ((png_ptr->mode & 0x01) == 0)
    {
      png_chunk_error(png_ptr, "Missing IHDR before IDAT");
    }
    else
      if ((png_ptr->color_type == (2 | 1)) && ((png_ptr->mode & 0x02) == 0))
    {
      png_chunk_error(png_ptr, "Missing PLTE before IDAT");
    }
    else
      if ((png_ptr->mode & 0x08) != 0)
    {
      png_chunk_benign_error(png_ptr, "Too many IDATs found");
    }
    png_ptr->mode |= 0x04U;
  }
  else
    if ((png_ptr->mode & 0x04U) != 0)
  {
    png_ptr->mode |= 0x2000U;
    png_ptr->mode |= 0x08;
  }
  if (chunk_name == ((((((png_uint_32) 73) << 24) | (((png_uint_32) 72) << 16)) | (((png_uint_32) 68) << 8)) | (((png_uint_32) 82) << 0)))
  {
    png_handle_IHDR(png_ptr, info_ptr, length);
  }
  else
    if (chunk_name == ((((((png_uint_32) 73) << 24) | (((png_uint_32) 69) << 16)) | (((png_uint_32) 78) << 8)) | (((png_uint_32) 68) << 0)))
  {
    png_handle_IEND(png_ptr, info_ptr, length);
  }
  else
    if ((keep = png_chunk_unknown_handling(png_ptr, chunk_name)) != 0)
  {
    png_handle_unknown(png_ptr, info_ptr, length, keep);
    if (chunk_name == ((((((png_uint_32) 80) << 24) | (((png_uint_32) 76) << 16)) | (((png_uint_32) 84) << 8)) | (((png_uint_32) 69) << 0)))
    {
      png_ptr->mode |= 0x02;
    }
    else
      if (chunk_name == ((((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)))
    {
      png_ptr->idat_size = 0;
      break;
    }
  }
  else
    if (chunk_name == ((((((png_uint_32) 80) << 24) | (((png_uint_32) 76) << 16)) | (((png_uint_32) 84) << 8)) | (((png_uint_32) 69) << 0)))
  {
    png_handle_PLTE(png_ptr, info_ptr, length);
  }
  else
    if (chunk_name == ((((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)))
  {
    png_ptr->idat_size = length;
    break;
  }
  else
    if (chunk_name == ((((((png_uint_32) 98) << 24) | (((png_uint_32) 75) << 16)) | (((png_uint_32) 71) << 8)) | (((png_uint_32) 68) << 0)))
  {
    png_handle_bKGD(png_ptr, info_ptr, length);
  }
  else
    if (chunk_name == ((((((png_uint_32) 104) << 24) | (((png_uint_32) 73) << 16)) | (((png_uint_32) 83) << 8)) | (((png_uint_32) 84) << 0)))
  {
    png_handle_hIST(png_ptr, info_ptr, length);
  }
  else
    if (chunk_name == ((((((png_uint_32) 115) << 24) | (((png_uint_32) 66) << 16)) | (((png_uint_32) 73) << 8)) | (((png_uint_32) 84) << 0)))
  {
    png_handle_sBIT(png_ptr, info_ptr, length);
  }
  else
    if (chunk_name == ((((((png_uint_32) 116) << 24) | (((png_uint_32) 82) << 16)) | (((png_uint_32) 78) << 8)) | (((png_uint_32) 83) << 0)))
  {
    png_handle_tRNS(png_ptr, info_ptr, length);
  }
  else
    png_handle_unknown(png_ptr, info_ptr, length, 0);
  *png_ptr_ref = png_ptr;
  *keep_ref = keep;
}


/*** DEPENDENCIES:
void png_handle_sBIT(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
  unsigned int truelen;
  unsigned int i;
  png_byte sample_depth;
  png_byte buf[4];
  (void) 0;
  if ((png_ptr->mode & 0x01) == 0)
  {
    png_chunk_error(png_ptr, "missing IHDR");
  }
  else
    if ((png_ptr->mode & (0x04U | 0x02)) != 0)
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "out of place");
    return;
  }
  if ((info_ptr != 0) && ((info_ptr->valid & 0x0002U) != 0))
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "duplicate");
    return;
  }
  if (png_ptr->color_type == (2 | 1))
  {
    truelen = 3;
    sample_depth = 8;
  }
  else
  {
    truelen = png_ptr->channels;
    sample_depth = png_ptr->bit_depth;
  }
  if ((length != truelen) || (length > 4))
  {
    png_chunk_benign_error(png_ptr, "invalid");
    png_crc_finish(png_ptr, length);
    return;
  }
  buf[0] = (buf[1] = (buf[2] = (buf[3] = sample_depth)));
  png_crc_read(png_ptr, buf, truelen);
  if (png_crc_finish(png_ptr, 0) != 0)
  {
    return;
  }
  for (i = 0; i < truelen; i += 1)
  {
    if ((buf[i] == 0) || (buf[i] > sample_depth))
    {
      png_chunk_benign_error(png_ptr, "invalid");
      return;
    }
  }

  if ((png_ptr->color_type & 2) != 0)
  {
    png_ptr->sig_bit.red = buf[0];
    png_ptr->sig_bit.green = buf[1];
    png_ptr->sig_bit.blue = buf[2];
    png_ptr->sig_bit.alpha = buf[3];
  }
  else
  {
    png_ptr->sig_bit.gray = buf[0];
    png_ptr->sig_bit.red = buf[0];
    png_ptr->sig_bit.green = buf[0];
    png_ptr->sig_bit.blue = buf[0];
    png_ptr->sig_bit.alpha = buf[1];
  }
  png_set_sBIT(png_ptr, info_ptr, &png_ptr->sig_bit);
}


----------------------------
int png_chunk_unknown_handling(png_const_structrp png_ptr, png_uint_32 chunk_name)
{
  png_byte chunk_string[5];
  (void) (((void) ((((char *) chunk_string)[0] = (char) ((chunk_name >> 24) & 0xff), ((char *) chunk_string)[1] = (char) ((chunk_name >> 16) & 0xff), ((char *) chunk_string)[2] = (char) ((chunk_name >> 8) & 0xff), ((char *) chunk_string)[3] = (char) (chunk_name & 0xff))), ((char *) chunk_string)[4] = 0));
  return png_handle_as_unknown(png_ptr, chunk_string);
}


----------------------------
typedef unsigned int png_uint_32
----------------------------
png_uint_32 png_read_chunk_header(png_structrp png_ptr)
{
  png_byte buf[8];
  png_uint_32 length;
  png_ptr->io_state = 0x0001 | 0x0020;
  png_read_data(png_ptr, buf, 8);
  length = png_get_uint_31(png_ptr, buf);
  png_ptr->chunk_name = (((((png_uint_32) (0xff & (buf + 4)[0])) << 24) | (((png_uint_32) (0xff & (buf + 4)[1])) << 16)) | (((png_uint_32) (0xff & (buf + 4)[2])) << 8)) | (((png_uint_32) (0xff & (buf + 4)[3])) << 0);
  (void) 0;
  png_reset_crc(png_ptr);
  png_calculate_crc(png_ptr, buf + 4, 4);
  png_check_chunk_name(png_ptr, png_ptr->chunk_name);
  png_check_chunk_length(png_ptr, length);
  png_ptr->io_state = 0x0001 | 0x0040;
  return length;
}


----------------------------
void png_handle_IHDR(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
  png_byte buf[13];
  png_uint_32 width;
  png_uint_32 height;
  int bit_depth;
  int color_type;
  int compression_type;
  int filter_type;
  int interlace_type;
  (void) 0;
  if ((png_ptr->mode & 0x01) != 0)
  {
    png_chunk_error(png_ptr, "out of place");
  }
  if (length != 13)
  {
    png_chunk_error(png_ptr, "invalid");
  }
  png_ptr->mode |= 0x01;
  png_crc_read(png_ptr, buf, 13);
  png_crc_finish(png_ptr, 0);
  width = png_get_uint_31(png_ptr, buf);
  height = png_get_uint_31(png_ptr, buf + 4);
  bit_depth = buf[8];
  color_type = buf[9];
  compression_type = buf[10];
  filter_type = buf[11];
  interlace_type = buf[12];
  png_ptr->width = width;
  png_ptr->height = height;
  png_ptr->bit_depth = (png_byte) bit_depth;
  png_ptr->interlaced = (png_byte) interlace_type;
  png_ptr->color_type = (png_byte) color_type;
  png_ptr->compression_type = (png_byte) compression_type;
  switch (png_ptr->color_type)
  {
    default:

    case 0:

    case 2 | 1:
    {
      png_ptr->channels = 1;
      break;
    }

    case 2:
    {
      png_ptr->channels = 3;
      break;
    }

    case 4:
    {
      png_ptr->channels = 2;
      break;
    }

    case 2 | 4:
    {
      png_ptr->channels = 4;
      break;
    }

  }

  png_ptr->pixel_depth = (png_byte) (png_ptr->bit_depth * png_ptr->channels);
  png_ptr->rowbytes = (png_ptr->pixel_depth >= 8) ? (((size_t) png_ptr->width) * (((size_t) png_ptr->pixel_depth) >> 3)) : (((((size_t) png_ptr->width) * ((size_t) png_ptr->pixel_depth)) + 7) >> 3);
  (void) 0;
  (void) 0;
  (void) 0;
  png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type, interlace_type, compression_type, filter_type);
}


----------------------------
void png_handle_bKGD(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
  unsigned int truelen;
  png_byte buf[6];
  png_color_16 background;
  (void) 0;
  if ((png_ptr->mode & 0x01) == 0)
  {
    png_chunk_error(png_ptr, "missing IHDR");
  }
  else
    if (((png_ptr->mode & 0x04U) != 0) || ((png_ptr->color_type == (2 | 1)) && ((png_ptr->mode & 0x02) == 0)))
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "out of place");
    return;
  }
  else
    if ((info_ptr != 0) && ((info_ptr->valid & 0x0020U) != 0))
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "duplicate");
    return;
  }
  if (png_ptr->color_type == (2 | 1))
  {
    truelen = 1;
  }
  else
    if ((png_ptr->color_type & 2) != 0)
  {
    truelen = 6;
  }
  else
    truelen = 2;
  if (length != truelen)
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "invalid");
    return;
  }
  png_crc_read(png_ptr, buf, truelen);
  if (png_crc_finish(png_ptr, 0) != 0)
  {
    return;
  }
  if (png_ptr->color_type == (2 | 1))
  {
    background.index = buf[0];
    if ((info_ptr != 0) && (info_ptr->num_palette != 0))
    {
      if (buf[0] >= info_ptr->num_palette)
      {
        png_chunk_benign_error(png_ptr, "invalid index");
        return;
      }
      background.red = (png_uint_16) png_ptr->palette[buf[0]].red;
      background.green = (png_uint_16) png_ptr->palette[buf[0]].green;
      background.blue = (png_uint_16) png_ptr->palette[buf[0]].blue;
    }
    else
      background.red = (background.green = (background.blue = 0));
    background.gray = 0;
  }
  else
    if ((png_ptr->color_type & 2) == 0)
  {
    if (png_ptr->bit_depth <= 8)
    {
      if ((buf[0] != 0) || (buf[1] >= ((unsigned int) (1 << png_ptr->bit_depth))))
      {
        png_chunk_benign_error(png_ptr, "invalid gray level");
        return;
      }
    }
    background.index = 0;
    background.red = (background.green = (background.blue = (background.gray = (png_uint_16) ((((unsigned int) (*buf)) << 8) + ((unsigned int) (*(buf + 1)))))));
  }
  else
  {
    if (png_ptr->bit_depth <= 8)
    {
      if (((buf[0] != 0) || (buf[2] != 0)) || (buf[4] != 0))
      {
        png_chunk_benign_error(png_ptr, "invalid color");
        return;
      }
    }
    background.index = 0;
    background.red = (png_uint_16) ((((unsigned int) (*buf)) << 8) + ((unsigned int) (*(buf + 1))));
    background.green = (png_uint_16) ((((unsigned int) (*(buf + 2))) << 8) + ((unsigned int) (*((buf + 2) + 1))));
    background.blue = (png_uint_16) ((((unsigned int) (*(buf + 4))) << 8) + ((unsigned int) (*((buf + 4) + 1))));
    background.gray = 0;
  }
  png_set_bKGD(png_ptr, info_ptr, &background);
}


----------------------------
void png_chunk_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  char msg[18 + 196];
  if (png_ptr == 0)
  {
    png_error(png_ptr, error_message);
  }
  else
  {
    png_format_buffer(png_ptr, msg, error_message);
    png_error(png_ptr, msg);
  }
}


----------------------------
void png_handle_PLTE(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
  png_color palette[256];
  int max_palette_length;
  int num;
  int i;
  png_colorp pal_ptr;
  (void) 0;
  if ((png_ptr->mode & 0x01) == 0)
  {
    png_chunk_error(png_ptr, "missing IHDR");
  }
  else
    if ((png_ptr->mode & 0x02) != 0)
  {
    png_chunk_error(png_ptr, "duplicate");
  }
  else
    if ((png_ptr->mode & 0x04U) != 0)
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "out of place");
    return;
  }
  png_ptr->mode |= 0x02;
  if ((png_ptr->color_type & 2) == 0)
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "ignored in grayscale PNG");
    return;
  }
  if ((length > (3 * 256)) || (length % 3))
  {
    png_crc_finish(png_ptr, length);
    if (png_ptr->color_type != (2 | 1))
    {
      png_chunk_benign_error(png_ptr, "invalid");
    }
    else
      png_chunk_error(png_ptr, "invalid");
    return;
  }
  num = ((int) length) / 3;
  if (png_ptr->color_type == (2 | 1))
  {
    max_palette_length = 1 << png_ptr->bit_depth;
  }
  else
    max_palette_length = 256;
  if (num > max_palette_length)
  {
    num = max_palette_length;
  }
  for (i = 0, pal_ptr = palette; i < num; i += 1, pal_ptr += 1)
  {
    png_byte buf[3];
    png_crc_read(png_ptr, buf, 3);
    pal_ptr->red = buf[0];
    pal_ptr->green = buf[1];
    pal_ptr->blue = buf[2];
  }

  {
    png_crc_finish(png_ptr, (png_uint_32) (length - (((unsigned int) num) * 3)));
  }
  png_set_PLTE(png_ptr, info_ptr, palette, num);
  if ((png_ptr->num_trans > 0) || ((info_ptr != 0) && ((info_ptr->valid & 0x0010U) != 0)))
  {
    png_ptr->num_trans = 0;
    if (info_ptr != 0)
    {
      info_ptr->num_trans = 0;
    }
    png_chunk_benign_error(png_ptr, "tRNS must be after");
  }
  if ((info_ptr != 0) && ((info_ptr->valid & 0x0040U) != 0))
  {
    png_chunk_benign_error(png_ptr, "hIST must be after");
  }
  if ((info_ptr != 0) && ((info_ptr->valid & 0x0020U) != 0))
  {
    png_chunk_benign_error(png_ptr, "bKGD must be after");
  }
}


----------------------------
void png_handle_IEND(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
  (void) 0;
  if (((png_ptr->mode & 0x01) == 0) || ((png_ptr->mode & 0x04U) == 0))
  {
    png_chunk_error(png_ptr, "out of place");
  }
  png_ptr->mode |= 0x08 | 0x10U;
  png_crc_finish(png_ptr, length);
  if (length != 0)
  {
    png_chunk_benign_error(png_ptr, "invalid");
  }
  (void) info_ptr;
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef struct png_info_def png_info
----------------------------
void png_handle_hIST(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
  unsigned int num;
  unsigned int i;
  png_uint_16 readbuf[256];
  (void) 0;
  if ((png_ptr->mode & 0x01) == 0)
  {
    png_chunk_error(png_ptr, "missing IHDR");
  }
  else
    if (((png_ptr->mode & 0x04U) != 0) || ((png_ptr->mode & 0x02) == 0))
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "out of place");
    return;
  }
  else
    if ((info_ptr != 0) && ((info_ptr->valid & 0x0040U) != 0))
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "duplicate");
    return;
  }
  num = length / 2;
  if (((length != (num * 2)) || (num != ((unsigned int) png_ptr->num_palette))) || (num > ((unsigned int) 256)))
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "invalid");
    return;
  }
  for (i = 0; i < num; i += 1)
  {
    png_byte buf[2];
    png_crc_read(png_ptr, buf, 2);
    readbuf[i] = (png_uint_16) ((((unsigned int) (*buf)) << 8) + ((unsigned int) (*(buf + 1))));
  }

  if (png_crc_finish(png_ptr, 0) != 0)
  {
    return;
  }
  png_set_hIST(png_ptr, info_ptr, readbuf);
}


----------------------------
typedef png_info *png_inforp
----------------------------
void png_chunk_benign_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr->flags & 0x100000U) != 0)
  {
    png_chunk_warning(png_ptr, error_message);
  }
  else
    png_chunk_error(png_ptr, error_message);
}


----------------------------
void png_handle_unknown(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length, int keep)
{
  int handled = 0;
  (void) 0;
  {
    if (keep == 0)
    {
      keep = png_ptr->unknown_default;
    }
    if ((keep == 3) || ((keep == 2) && (1 & (png_ptr->chunk_name >> 29))))
    {
      if (png_cache_unknown_chunk(png_ptr, length) == 0)
      {
        keep = 1;
      }
    }
    else
      png_crc_finish(png_ptr, length);
  }
  if ((keep == 3) || ((keep == 2) && (1 & (png_ptr->chunk_name >> 29))))
  {
    switch (png_ptr->user_chunk_cache_max)
    {
      case 2:
      {
        png_ptr->user_chunk_cache_max = 1;
        png_chunk_benign_error(png_ptr, "no space in chunk cache");
      }

      case 1:
      {
        break;
      }

      default:
      {
        png_ptr->user_chunk_cache_max -= 1;
      }

      case 0:
      {
        png_set_unknown_chunks(png_ptr, info_ptr, &png_ptr->unknown_chunk, 1);
        handled = 1;
        break;
      }

    }

  }
  if (png_ptr->unknown_chunk.data != 0)
  {
    png_free(png_ptr, png_ptr->unknown_chunk.data);
  }
  png_ptr->unknown_chunk.data = 0;
  if ((handled == 0) && (!(1 & (png_ptr->chunk_name >> 29))))
  {
    png_chunk_error(png_ptr, "unhandled critical chunk");
  }
}


----------------------------
void png_handle_tRNS(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
  png_byte readbuf[256];
  (void) 0;
  if ((png_ptr->mode & 0x01) == 0)
  {
    png_chunk_error(png_ptr, "missing IHDR");
  }
  else
    if ((png_ptr->mode & 0x04U) != 0)
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "out of place");
    return;
  }
  else
    if ((info_ptr != 0) && ((info_ptr->valid & 0x0010U) != 0))
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "duplicate");
    return;
  }
  if (png_ptr->color_type == 0)
  {
    png_byte buf[2];
    if (length != 2)
    {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "invalid");
      return;
    }
    png_crc_read(png_ptr, buf, 2);
    png_ptr->num_trans = 1;
    png_ptr->trans_color.gray = (png_uint_16) ((((unsigned int) (*buf)) << 8) + ((unsigned int) (*(buf + 1))));
  }
  else
    if (png_ptr->color_type == 2)
  {
    png_byte buf[6];
    if (length != 6)
    {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "invalid");
      return;
    }
    png_crc_read(png_ptr, buf, length);
    png_ptr->num_trans = 1;
    png_ptr->trans_color.red = (png_uint_16) ((((unsigned int) (*buf)) << 8) + ((unsigned int) (*(buf + 1))));
    png_ptr->trans_color.green = (png_uint_16) ((((unsigned int) (*(buf + 2))) << 8) + ((unsigned int) (*((buf + 2) + 1))));
    png_ptr->trans_color.blue = (png_uint_16) ((((unsigned int) (*(buf + 4))) << 8) + ((unsigned int) (*((buf + 4) + 1))));
  }
  else
    if (png_ptr->color_type == (2 | 1))
  {
    if ((png_ptr->mode & 0x02) == 0)
    {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "out of place");
      return;
    }
    if (((length > ((unsigned int) png_ptr->num_palette)) || (length > ((unsigned int) 256))) || (length == 0))
    {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "invalid");
      return;
    }
    png_crc_read(png_ptr, readbuf, length);
    png_ptr->num_trans = (png_uint_16) length;
  }
  else
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "invalid with alpha channel");
    return;
  }
  if (png_crc_finish(png_ptr, 0) != 0)
  {
    png_ptr->num_trans = 0;
    return;
  }
  png_set_tRNS(png_ptr, info_ptr, readbuf, png_ptr->num_trans, &png_ptr->trans_color);
}


----------------------------
***/


void png_read_info(png_structrp png_ptr, png_inforp info_ptr)
{
  int keep;
  (void) 0;
  if ((png_ptr == 0) || (info_ptr == 0))
  {
    return;
  }
  png_read_sig(png_ptr, info_ptr);
  for (;;)
  {
    helper_png_read_info_1(&png_ptr, &keep, info_ptr);
  }

}


/*** DEPENDENCIES:
void png_read_sig(png_structrp png_ptr, png_inforp info_ptr)
{
  size_t num_checked;
  size_t num_to_check;
  if (png_ptr->sig_bytes >= 8)
  {
    return;
  }
  num_checked = png_ptr->sig_bytes;
  num_to_check = 8 - num_checked;
  png_ptr->io_state = 0x0001 | 0x0010;
  png_read_data(png_ptr, &info_ptr->signature[num_checked], num_to_check);
  png_ptr->sig_bytes = 8;
  if (png_sig_cmp(info_ptr->signature, num_checked, num_to_check) != 0)
  {
    if ((num_checked < 4) && png_sig_cmp(info_ptr->signature, num_checked, num_to_check - 4))
    {
      png_error(png_ptr, "Not a PNG file");
    }
    else
      png_error(png_ptr, "PNG file corrupted by ASCII conversion");
  }
  if (num_checked < 3)
  {
    png_ptr->mode |= 0x1000U;
  }
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef struct png_info_def png_info
----------------------------
void helper_png_read_info_1(png_structrp * const png_ptr_ref, int * const keep_ref, png_inforp info_ptr)
{
  png_structrp png_ptr = *png_ptr_ref;
  int keep = *keep_ref;
  png_uint_32 length = png_read_chunk_header(png_ptr);
  png_uint_32 chunk_name = png_ptr->chunk_name;
  if (chunk_name == ((((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)))
  {
    if ((png_ptr->mode & 0x01) == 0)
    {
      png_chunk_error(png_ptr, "Missing IHDR before IDAT");
    }
    else
      if ((png_ptr->color_type == (2 | 1)) && ((png_ptr->mode & 0x02) == 0))
    {
      png_chunk_error(png_ptr, "Missing PLTE before IDAT");
    }
    else
      if ((png_ptr->mode & 0x08) != 0)
    {
      png_chunk_benign_error(png_ptr, "Too many IDATs found");
    }
    png_ptr->mode |= 0x04U;
  }
  else
    if ((png_ptr->mode & 0x04U) != 0)
  {
    png_ptr->mode |= 0x2000U;
    png_ptr->mode |= 0x08;
  }
  if (chunk_name == ((((((png_uint_32) 73) << 24) | (((png_uint_32) 72) << 16)) | (((png_uint_32) 68) << 8)) | (((png_uint_32) 82) << 0)))
  {
    png_handle_IHDR(png_ptr, info_ptr, length);
  }
  else
    if (chunk_name == ((((((png_uint_32) 73) << 24) | (((png_uint_32) 69) << 16)) | (((png_uint_32) 78) << 8)) | (((png_uint_32) 68) << 0)))
  {
    png_handle_IEND(png_ptr, info_ptr, length);
  }
  else
    if ((keep = png_chunk_unknown_handling(png_ptr, chunk_name)) != 0)
  {
    png_handle_unknown(png_ptr, info_ptr, length, keep);
    if (chunk_name == ((((((png_uint_32) 80) << 24) | (((png_uint_32) 76) << 16)) | (((png_uint_32) 84) << 8)) | (((png_uint_32) 69) << 0)))
    {
      png_ptr->mode |= 0x02;
    }
    else
      if (chunk_name == ((((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)))
    {
      png_ptr->idat_size = 0;
      break;
    }
  }
  else
    if (chunk_name == ((((((png_uint_32) 80) << 24) | (((png_uint_32) 76) << 16)) | (((png_uint_32) 84) << 8)) | (((png_uint_32) 69) << 0)))
  {
    png_handle_PLTE(png_ptr, info_ptr, length);
  }
  else
    if (chunk_name == ((((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)))
  {
    png_ptr->idat_size = length;
    break;
  }
  else
    if (chunk_name == ((((((png_uint_32) 98) << 24) | (((png_uint_32) 75) << 16)) | (((png_uint_32) 71) << 8)) | (((png_uint_32) 68) << 0)))
  {
    png_handle_bKGD(png_ptr, info_ptr, length);
  }
  else
    if (chunk_name == ((((((png_uint_32) 104) << 24) | (((png_uint_32) 73) << 16)) | (((png_uint_32) 83) << 8)) | (((png_uint_32) 84) << 0)))
  {
    png_handle_hIST(png_ptr, info_ptr, length);
  }
  else
    if (chunk_name == ((((((png_uint_32) 115) << 24) | (((png_uint_32) 66) << 16)) | (((png_uint_32) 73) << 8)) | (((png_uint_32) 84) << 0)))
  {
    png_handle_sBIT(png_ptr, info_ptr, length);
  }
  else
    if (chunk_name == ((((((png_uint_32) 116) << 24) | (((png_uint_32) 82) << 16)) | (((png_uint_32) 78) << 8)) | (((png_uint_32) 83) << 0)))
  {
    png_handle_tRNS(png_ptr, info_ptr, length);
  }
  else
    png_handle_unknown(png_ptr, info_ptr, length, 0);
  *png_ptr_ref = png_ptr;
  *keep_ref = keep;
}


----------------------------
typedef png_info *png_inforp
----------------------------
***/


// hint:  ['png_ptr_ref is a mutable refrence to png_structrp', 'keep_ref is a mutable refrence to int']
void helper_png_read_end_1(png_structrp * const png_ptr_ref, int * const keep_ref, png_inforp info_ptr)
{
  png_structrp png_ptr = *png_ptr_ref;
  int keep = *keep_ref;
  png_uint_32 length = png_read_chunk_header(png_ptr);
  png_uint_32 chunk_name = png_ptr->chunk_name;
  if (chunk_name != ((((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)))
  {
    png_ptr->mode |= 0x2000U;
  }
  if (chunk_name == ((((((png_uint_32) 73) << 24) | (((png_uint_32) 69) << 16)) | (((png_uint_32) 78) << 8)) | (((png_uint_32) 68) << 0)))
  {
    png_handle_IEND(png_ptr, info_ptr, length);
  }
  else
    if (chunk_name == ((((((png_uint_32) 73) << 24) | (((png_uint_32) 72) << 16)) | (((png_uint_32) 68) << 8)) | (((png_uint_32) 82) << 0)))
  {
    png_handle_IHDR(png_ptr, info_ptr, length);
  }
  else
    if (info_ptr == 0)
  {
    png_crc_finish(png_ptr, length);
  }
  else
    if ((keep = png_chunk_unknown_handling(png_ptr, chunk_name)) != 0)
  {
    if (chunk_name == ((((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)))
    {
      if (((length > 0) && (!(png_ptr->flags & 0x0008U))) || ((png_ptr->mode & 0x2000U) != 0))
      {
        png_benign_error(png_ptr, ".Too many IDATs found");
      }
    }
    png_handle_unknown(png_ptr, info_ptr, length, keep);
    if (chunk_name == ((((((png_uint_32) 80) << 24) | (((png_uint_32) 76) << 16)) | (((png_uint_32) 84) << 8)) | (((png_uint_32) 69) << 0)))
    {
      png_ptr->mode |= 0x02;
    }
  }
  else
    if (chunk_name == ((((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)))
  {
    if (((length > 0) && (!(png_ptr->flags & 0x0008U))) || ((png_ptr->mode & 0x2000U) != 0))
    {
      png_benign_error(png_ptr, "..Too many IDATs found");
    }
    png_crc_finish(png_ptr, length);
  }
  else
    if (chunk_name == ((((((png_uint_32) 80) << 24) | (((png_uint_32) 76) << 16)) | (((png_uint_32) 84) << 8)) | (((png_uint_32) 69) << 0)))
  {
    png_handle_PLTE(png_ptr, info_ptr, length);
  }
  else
    if (chunk_name == ((((((png_uint_32) 98) << 24) | (((png_uint_32) 75) << 16)) | (((png_uint_32) 71) << 8)) | (((png_uint_32) 68) << 0)))
  {
    png_handle_bKGD(png_ptr, info_ptr, length);
  }
  else
    if (chunk_name == ((((((png_uint_32) 104) << 24) | (((png_uint_32) 73) << 16)) | (((png_uint_32) 83) << 8)) | (((png_uint_32) 84) << 0)))
  {
    png_handle_hIST(png_ptr, info_ptr, length);
  }
  else
    if (chunk_name == ((((((png_uint_32) 115) << 24) | (((png_uint_32) 66) << 16)) | (((png_uint_32) 73) << 8)) | (((png_uint_32) 84) << 0)))
  {
    png_handle_sBIT(png_ptr, info_ptr, length);
  }
  else
    if (chunk_name == ((((((png_uint_32) 116) << 24) | (((png_uint_32) 82) << 16)) | (((png_uint_32) 78) << 8)) | (((png_uint_32) 83) << 0)))
  {
    png_handle_tRNS(png_ptr, info_ptr, length);
  }
  else
    png_handle_unknown(png_ptr, info_ptr, length, 0);
  *png_ptr_ref = png_ptr;
  *keep_ref = keep;
}


/*** DEPENDENCIES:
int png_crc_finish(png_structrp png_ptr, png_uint_32 skip)
{
  while (skip > 0)
  {
    png_uint_32 len;
    png_byte tmpbuf[1024];
    len = sizeof(tmpbuf);
    if (len > skip)
    {
      len = skip;
    }
    skip -= len;
    png_crc_read(png_ptr, tmpbuf, len);
  }

  if (png_crc_error(png_ptr) != 0)
  {
    if (((1 & (png_ptr->chunk_name >> 29)) != 0) ? ((png_ptr->flags & 0x0200U) == 0) : ((png_ptr->flags & 0x0400U) != 0))
    {
      png_chunk_warning(png_ptr, "CRC error");
    }
    else
      png_chunk_error(png_ptr, "CRC error");
    return 1;
  }
  return 0;
}


----------------------------
void png_handle_sBIT(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
  unsigned int truelen;
  unsigned int i;
  png_byte sample_depth;
  png_byte buf[4];
  (void) 0;
  if ((png_ptr->mode & 0x01) == 0)
  {
    png_chunk_error(png_ptr, "missing IHDR");
  }
  else
    if ((png_ptr->mode & (0x04U | 0x02)) != 0)
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "out of place");
    return;
  }
  if ((info_ptr != 0) && ((info_ptr->valid & 0x0002U) != 0))
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "duplicate");
    return;
  }
  if (png_ptr->color_type == (2 | 1))
  {
    truelen = 3;
    sample_depth = 8;
  }
  else
  {
    truelen = png_ptr->channels;
    sample_depth = png_ptr->bit_depth;
  }
  if ((length != truelen) || (length > 4))
  {
    png_chunk_benign_error(png_ptr, "invalid");
    png_crc_finish(png_ptr, length);
    return;
  }
  buf[0] = (buf[1] = (buf[2] = (buf[3] = sample_depth)));
  png_crc_read(png_ptr, buf, truelen);
  if (png_crc_finish(png_ptr, 0) != 0)
  {
    return;
  }
  for (i = 0; i < truelen; i += 1)
  {
    if ((buf[i] == 0) || (buf[i] > sample_depth))
    {
      png_chunk_benign_error(png_ptr, "invalid");
      return;
    }
  }

  if ((png_ptr->color_type & 2) != 0)
  {
    png_ptr->sig_bit.red = buf[0];
    png_ptr->sig_bit.green = buf[1];
    png_ptr->sig_bit.blue = buf[2];
    png_ptr->sig_bit.alpha = buf[3];
  }
  else
  {
    png_ptr->sig_bit.gray = buf[0];
    png_ptr->sig_bit.red = buf[0];
    png_ptr->sig_bit.green = buf[0];
    png_ptr->sig_bit.blue = buf[0];
    png_ptr->sig_bit.alpha = buf[1];
  }
  png_set_sBIT(png_ptr, info_ptr, &png_ptr->sig_bit);
}


----------------------------
int png_chunk_unknown_handling(png_const_structrp png_ptr, png_uint_32 chunk_name)
{
  png_byte chunk_string[5];
  (void) (((void) ((((char *) chunk_string)[0] = (char) ((chunk_name >> 24) & 0xff), ((char *) chunk_string)[1] = (char) ((chunk_name >> 16) & 0xff), ((char *) chunk_string)[2] = (char) ((chunk_name >> 8) & 0xff), ((char *) chunk_string)[3] = (char) (chunk_name & 0xff))), ((char *) chunk_string)[4] = 0));
  return png_handle_as_unknown(png_ptr, chunk_string);
}


----------------------------
typedef unsigned int png_uint_32
----------------------------
png_uint_32 png_read_chunk_header(png_structrp png_ptr)
{
  png_byte buf[8];
  png_uint_32 length;
  png_ptr->io_state = 0x0001 | 0x0020;
  png_read_data(png_ptr, buf, 8);
  length = png_get_uint_31(png_ptr, buf);
  png_ptr->chunk_name = (((((png_uint_32) (0xff & (buf + 4)[0])) << 24) | (((png_uint_32) (0xff & (buf + 4)[1])) << 16)) | (((png_uint_32) (0xff & (buf + 4)[2])) << 8)) | (((png_uint_32) (0xff & (buf + 4)[3])) << 0);
  (void) 0;
  png_reset_crc(png_ptr);
  png_calculate_crc(png_ptr, buf + 4, 4);
  png_check_chunk_name(png_ptr, png_ptr->chunk_name);
  png_check_chunk_length(png_ptr, length);
  png_ptr->io_state = 0x0001 | 0x0040;
  return length;
}


----------------------------
void png_handle_IHDR(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
  png_byte buf[13];
  png_uint_32 width;
  png_uint_32 height;
  int bit_depth;
  int color_type;
  int compression_type;
  int filter_type;
  int interlace_type;
  (void) 0;
  if ((png_ptr->mode & 0x01) != 0)
  {
    png_chunk_error(png_ptr, "out of place");
  }
  if (length != 13)
  {
    png_chunk_error(png_ptr, "invalid");
  }
  png_ptr->mode |= 0x01;
  png_crc_read(png_ptr, buf, 13);
  png_crc_finish(png_ptr, 0);
  width = png_get_uint_31(png_ptr, buf);
  height = png_get_uint_31(png_ptr, buf + 4);
  bit_depth = buf[8];
  color_type = buf[9];
  compression_type = buf[10];
  filter_type = buf[11];
  interlace_type = buf[12];
  png_ptr->width = width;
  png_ptr->height = height;
  png_ptr->bit_depth = (png_byte) bit_depth;
  png_ptr->interlaced = (png_byte) interlace_type;
  png_ptr->color_type = (png_byte) color_type;
  png_ptr->compression_type = (png_byte) compression_type;
  switch (png_ptr->color_type)
  {
    default:

    case 0:

    case 2 | 1:
    {
      png_ptr->channels = 1;
      break;
    }

    case 2:
    {
      png_ptr->channels = 3;
      break;
    }

    case 4:
    {
      png_ptr->channels = 2;
      break;
    }

    case 2 | 4:
    {
      png_ptr->channels = 4;
      break;
    }

  }

  png_ptr->pixel_depth = (png_byte) (png_ptr->bit_depth * png_ptr->channels);
  png_ptr->rowbytes = (png_ptr->pixel_depth >= 8) ? (((size_t) png_ptr->width) * (((size_t) png_ptr->pixel_depth) >> 3)) : (((((size_t) png_ptr->width) * ((size_t) png_ptr->pixel_depth)) + 7) >> 3);
  (void) 0;
  (void) 0;
  (void) 0;
  png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type, interlace_type, compression_type, filter_type);
}


----------------------------
void png_handle_bKGD(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
  unsigned int truelen;
  png_byte buf[6];
  png_color_16 background;
  (void) 0;
  if ((png_ptr->mode & 0x01) == 0)
  {
    png_chunk_error(png_ptr, "missing IHDR");
  }
  else
    if (((png_ptr->mode & 0x04U) != 0) || ((png_ptr->color_type == (2 | 1)) && ((png_ptr->mode & 0x02) == 0)))
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "out of place");
    return;
  }
  else
    if ((info_ptr != 0) && ((info_ptr->valid & 0x0020U) != 0))
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "duplicate");
    return;
  }
  if (png_ptr->color_type == (2 | 1))
  {
    truelen = 1;
  }
  else
    if ((png_ptr->color_type & 2) != 0)
  {
    truelen = 6;
  }
  else
    truelen = 2;
  if (length != truelen)
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "invalid");
    return;
  }
  png_crc_read(png_ptr, buf, truelen);
  if (png_crc_finish(png_ptr, 0) != 0)
  {
    return;
  }
  if (png_ptr->color_type == (2 | 1))
  {
    background.index = buf[0];
    if ((info_ptr != 0) && (info_ptr->num_palette != 0))
    {
      if (buf[0] >= info_ptr->num_palette)
      {
        png_chunk_benign_error(png_ptr, "invalid index");
        return;
      }
      background.red = (png_uint_16) png_ptr->palette[buf[0]].red;
      background.green = (png_uint_16) png_ptr->palette[buf[0]].green;
      background.blue = (png_uint_16) png_ptr->palette[buf[0]].blue;
    }
    else
      background.red = (background.green = (background.blue = 0));
    background.gray = 0;
  }
  else
    if ((png_ptr->color_type & 2) == 0)
  {
    if (png_ptr->bit_depth <= 8)
    {
      if ((buf[0] != 0) || (buf[1] >= ((unsigned int) (1 << png_ptr->bit_depth))))
      {
        png_chunk_benign_error(png_ptr, "invalid gray level");
        return;
      }
    }
    background.index = 0;
    background.red = (background.green = (background.blue = (background.gray = (png_uint_16) ((((unsigned int) (*buf)) << 8) + ((unsigned int) (*(buf + 1)))))));
  }
  else
  {
    if (png_ptr->bit_depth <= 8)
    {
      if (((buf[0] != 0) || (buf[2] != 0)) || (buf[4] != 0))
      {
        png_chunk_benign_error(png_ptr, "invalid color");
        return;
      }
    }
    background.index = 0;
    background.red = (png_uint_16) ((((unsigned int) (*buf)) << 8) + ((unsigned int) (*(buf + 1))));
    background.green = (png_uint_16) ((((unsigned int) (*(buf + 2))) << 8) + ((unsigned int) (*((buf + 2) + 1))));
    background.blue = (png_uint_16) ((((unsigned int) (*(buf + 4))) << 8) + ((unsigned int) (*((buf + 4) + 1))));
    background.gray = 0;
  }
  png_set_bKGD(png_ptr, info_ptr, &background);
}


----------------------------
void png_handle_PLTE(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
  png_color palette[256];
  int max_palette_length;
  int num;
  int i;
  png_colorp pal_ptr;
  (void) 0;
  if ((png_ptr->mode & 0x01) == 0)
  {
    png_chunk_error(png_ptr, "missing IHDR");
  }
  else
    if ((png_ptr->mode & 0x02) != 0)
  {
    png_chunk_error(png_ptr, "duplicate");
  }
  else
    if ((png_ptr->mode & 0x04U) != 0)
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "out of place");
    return;
  }
  png_ptr->mode |= 0x02;
  if ((png_ptr->color_type & 2) == 0)
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "ignored in grayscale PNG");
    return;
  }
  if ((length > (3 * 256)) || (length % 3))
  {
    png_crc_finish(png_ptr, length);
    if (png_ptr->color_type != (2 | 1))
    {
      png_chunk_benign_error(png_ptr, "invalid");
    }
    else
      png_chunk_error(png_ptr, "invalid");
    return;
  }
  num = ((int) length) / 3;
  if (png_ptr->color_type == (2 | 1))
  {
    max_palette_length = 1 << png_ptr->bit_depth;
  }
  else
    max_palette_length = 256;
  if (num > max_palette_length)
  {
    num = max_palette_length;
  }
  for (i = 0, pal_ptr = palette; i < num; i += 1, pal_ptr += 1)
  {
    png_byte buf[3];
    png_crc_read(png_ptr, buf, 3);
    pal_ptr->red = buf[0];
    pal_ptr->green = buf[1];
    pal_ptr->blue = buf[2];
  }

  {
    png_crc_finish(png_ptr, (png_uint_32) (length - (((unsigned int) num) * 3)));
  }
  png_set_PLTE(png_ptr, info_ptr, palette, num);
  if ((png_ptr->num_trans > 0) || ((info_ptr != 0) && ((info_ptr->valid & 0x0010U) != 0)))
  {
    png_ptr->num_trans = 0;
    if (info_ptr != 0)
    {
      info_ptr->num_trans = 0;
    }
    png_chunk_benign_error(png_ptr, "tRNS must be after");
  }
  if ((info_ptr != 0) && ((info_ptr->valid & 0x0040U) != 0))
  {
    png_chunk_benign_error(png_ptr, "hIST must be after");
  }
  if ((info_ptr != 0) && ((info_ptr->valid & 0x0020U) != 0))
  {
    png_chunk_benign_error(png_ptr, "bKGD must be after");
  }
}


----------------------------
void png_handle_IEND(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
  (void) 0;
  if (((png_ptr->mode & 0x01) == 0) || ((png_ptr->mode & 0x04U) == 0))
  {
    png_chunk_error(png_ptr, "out of place");
  }
  png_ptr->mode |= 0x08 | 0x10U;
  png_crc_finish(png_ptr, length);
  if (length != 0)
  {
    png_chunk_benign_error(png_ptr, "invalid");
  }
  (void) info_ptr;
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef struct png_info_def png_info
----------------------------
void png_handle_hIST(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
  unsigned int num;
  unsigned int i;
  png_uint_16 readbuf[256];
  (void) 0;
  if ((png_ptr->mode & 0x01) == 0)
  {
    png_chunk_error(png_ptr, "missing IHDR");
  }
  else
    if (((png_ptr->mode & 0x04U) != 0) || ((png_ptr->mode & 0x02) == 0))
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "out of place");
    return;
  }
  else
    if ((info_ptr != 0) && ((info_ptr->valid & 0x0040U) != 0))
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "duplicate");
    return;
  }
  num = length / 2;
  if (((length != (num * 2)) || (num != ((unsigned int) png_ptr->num_palette))) || (num > ((unsigned int) 256)))
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "invalid");
    return;
  }
  for (i = 0; i < num; i += 1)
  {
    png_byte buf[2];
    png_crc_read(png_ptr, buf, 2);
    readbuf[i] = (png_uint_16) ((((unsigned int) (*buf)) << 8) + ((unsigned int) (*(buf + 1))));
  }

  if (png_crc_finish(png_ptr, 0) != 0)
  {
    return;
  }
  png_set_hIST(png_ptr, info_ptr, readbuf);
}


----------------------------
typedef png_info *png_inforp
----------------------------
void png_benign_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr->flags & 0x100000U) != 0)
  {
    if (((png_ptr->mode & 0x8000U) != 0) && (png_ptr->chunk_name != 0))
    {
      png_chunk_warning(png_ptr, error_message);
    }
    else
      png_warning(png_ptr, error_message);
  }
  else
  {
    if (((png_ptr->mode & 0x8000U) != 0) && (png_ptr->chunk_name != 0))
    {
      png_chunk_error(png_ptr, error_message);
    }
    else
      png_error(png_ptr, error_message);
  }
}


----------------------------
void png_handle_unknown(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length, int keep)
{
  int handled = 0;
  (void) 0;
  {
    if (keep == 0)
    {
      keep = png_ptr->unknown_default;
    }
    if ((keep == 3) || ((keep == 2) && (1 & (png_ptr->chunk_name >> 29))))
    {
      if (png_cache_unknown_chunk(png_ptr, length) == 0)
      {
        keep = 1;
      }
    }
    else
      png_crc_finish(png_ptr, length);
  }
  if ((keep == 3) || ((keep == 2) && (1 & (png_ptr->chunk_name >> 29))))
  {
    switch (png_ptr->user_chunk_cache_max)
    {
      case 2:
      {
        png_ptr->user_chunk_cache_max = 1;
        png_chunk_benign_error(png_ptr, "no space in chunk cache");
      }

      case 1:
      {
        break;
      }

      default:
      {
        png_ptr->user_chunk_cache_max -= 1;
      }

      case 0:
      {
        png_set_unknown_chunks(png_ptr, info_ptr, &png_ptr->unknown_chunk, 1);
        handled = 1;
        break;
      }

    }

  }
  if (png_ptr->unknown_chunk.data != 0)
  {
    png_free(png_ptr, png_ptr->unknown_chunk.data);
  }
  png_ptr->unknown_chunk.data = 0;
  if ((handled == 0) && (!(1 & (png_ptr->chunk_name >> 29))))
  {
    png_chunk_error(png_ptr, "unhandled critical chunk");
  }
}


----------------------------
void png_handle_tRNS(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
  png_byte readbuf[256];
  (void) 0;
  if ((png_ptr->mode & 0x01) == 0)
  {
    png_chunk_error(png_ptr, "missing IHDR");
  }
  else
    if ((png_ptr->mode & 0x04U) != 0)
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "out of place");
    return;
  }
  else
    if ((info_ptr != 0) && ((info_ptr->valid & 0x0010U) != 0))
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "duplicate");
    return;
  }
  if (png_ptr->color_type == 0)
  {
    png_byte buf[2];
    if (length != 2)
    {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "invalid");
      return;
    }
    png_crc_read(png_ptr, buf, 2);
    png_ptr->num_trans = 1;
    png_ptr->trans_color.gray = (png_uint_16) ((((unsigned int) (*buf)) << 8) + ((unsigned int) (*(buf + 1))));
  }
  else
    if (png_ptr->color_type == 2)
  {
    png_byte buf[6];
    if (length != 6)
    {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "invalid");
      return;
    }
    png_crc_read(png_ptr, buf, length);
    png_ptr->num_trans = 1;
    png_ptr->trans_color.red = (png_uint_16) ((((unsigned int) (*buf)) << 8) + ((unsigned int) (*(buf + 1))));
    png_ptr->trans_color.green = (png_uint_16) ((((unsigned int) (*(buf + 2))) << 8) + ((unsigned int) (*((buf + 2) + 1))));
    png_ptr->trans_color.blue = (png_uint_16) ((((unsigned int) (*(buf + 4))) << 8) + ((unsigned int) (*((buf + 4) + 1))));
  }
  else
    if (png_ptr->color_type == (2 | 1))
  {
    if ((png_ptr->mode & 0x02) == 0)
    {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "out of place");
      return;
    }
    if (((length > ((unsigned int) png_ptr->num_palette)) || (length > ((unsigned int) 256))) || (length == 0))
    {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "invalid");
      return;
    }
    png_crc_read(png_ptr, readbuf, length);
    png_ptr->num_trans = (png_uint_16) length;
  }
  else
  {
    png_crc_finish(png_ptr, length);
    png_chunk_benign_error(png_ptr, "invalid with alpha channel");
    return;
  }
  if (png_crc_finish(png_ptr, 0) != 0)
  {
    png_ptr->num_trans = 0;
    return;
  }
  png_set_tRNS(png_ptr, info_ptr, readbuf, png_ptr->num_trans, &png_ptr->trans_color);
}


----------------------------
***/


void png_read_end(png_structrp png_ptr, png_inforp info_ptr)
{
  int keep;
  (void) 0;
  if (png_ptr == 0)
  {
    return;
  }
  if (png_chunk_unknown_handling(png_ptr, (((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)) == 0)
  {
    png_read_finish_IDAT(png_ptr);
  }
  if ((png_ptr->color_type == (2 | 1)) && (png_ptr->num_palette_max > png_ptr->num_palette))
  {
    png_benign_error(png_ptr, "Read palette index exceeding num_palette");
  }
  do
  {
    helper_png_read_end_1(&png_ptr, &keep, info_ptr);
  }
  while ((png_ptr->mode & 0x10U) == 0);
}


/*** DEPENDENCIES:
int png_chunk_unknown_handling(png_const_structrp png_ptr, png_uint_32 chunk_name)
{
  png_byte chunk_string[5];
  (void) (((void) ((((char *) chunk_string)[0] = (char) ((chunk_name >> 24) & 0xff), ((char *) chunk_string)[1] = (char) ((chunk_name >> 16) & 0xff), ((char *) chunk_string)[2] = (char) ((chunk_name >> 8) & 0xff), ((char *) chunk_string)[3] = (char) (chunk_name & 0xff))), ((char *) chunk_string)[4] = 0));
  return png_handle_as_unknown(png_ptr, chunk_string);
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef struct png_info_def png_info
----------------------------
void png_benign_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr->flags & 0x100000U) != 0)
  {
    if (((png_ptr->mode & 0x8000U) != 0) && (png_ptr->chunk_name != 0))
    {
      png_chunk_warning(png_ptr, error_message);
    }
    else
      png_warning(png_ptr, error_message);
  }
  else
  {
    if (((png_ptr->mode & 0x8000U) != 0) && (png_ptr->chunk_name != 0))
    {
      png_chunk_error(png_ptr, error_message);
    }
    else
      png_error(png_ptr, error_message);
  }
}


----------------------------
void png_read_finish_IDAT(png_structrp png_ptr)
{
  if ((png_ptr->flags & 0x0008U) == 0)
  {
    png_read_IDAT_data(png_ptr, 0, 0);
    png_ptr->zstream.next_out = 0;
    if ((png_ptr->flags & 0x0008U) == 0)
    {
      png_ptr->mode |= 0x08;
      png_ptr->flags |= 0x0008U;
    }
  }
  if (png_ptr->zowner == ((((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)))
  {
    png_ptr->zstream.next_in = 0;
    png_ptr->zstream.avail_in = 0;
    png_ptr->zowner = 0;
    (void) png_crc_finish(png_ptr, png_ptr->idat_size);
  }
}


----------------------------
typedef png_info *png_inforp
----------------------------
void helper_png_read_end_1(png_structrp * const png_ptr_ref, int * const keep_ref, png_inforp info_ptr)
{
  png_structrp png_ptr = *png_ptr_ref;
  int keep = *keep_ref;
  png_uint_32 length = png_read_chunk_header(png_ptr);
  png_uint_32 chunk_name = png_ptr->chunk_name;
  if (chunk_name != ((((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)))
  {
    png_ptr->mode |= 0x2000U;
  }
  if (chunk_name == ((((((png_uint_32) 73) << 24) | (((png_uint_32) 69) << 16)) | (((png_uint_32) 78) << 8)) | (((png_uint_32) 68) << 0)))
  {
    png_handle_IEND(png_ptr, info_ptr, length);
  }
  else
    if (chunk_name == ((((((png_uint_32) 73) << 24) | (((png_uint_32) 72) << 16)) | (((png_uint_32) 68) << 8)) | (((png_uint_32) 82) << 0)))
  {
    png_handle_IHDR(png_ptr, info_ptr, length);
  }
  else
    if (info_ptr == 0)
  {
    png_crc_finish(png_ptr, length);
  }
  else
    if ((keep = png_chunk_unknown_handling(png_ptr, chunk_name)) != 0)
  {
    if (chunk_name == ((((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)))
    {
      if (((length > 0) && (!(png_ptr->flags & 0x0008U))) || ((png_ptr->mode & 0x2000U) != 0))
      {
        png_benign_error(png_ptr, ".Too many IDATs found");
      }
    }
    png_handle_unknown(png_ptr, info_ptr, length, keep);
    if (chunk_name == ((((((png_uint_32) 80) << 24) | (((png_uint_32) 76) << 16)) | (((png_uint_32) 84) << 8)) | (((png_uint_32) 69) << 0)))
    {
      png_ptr->mode |= 0x02;
    }
  }
  else
    if (chunk_name == ((((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)))
  {
    if (((length > 0) && (!(png_ptr->flags & 0x0008U))) || ((png_ptr->mode & 0x2000U) != 0))
    {
      png_benign_error(png_ptr, "..Too many IDATs found");
    }
    png_crc_finish(png_ptr, length);
  }
  else
    if (chunk_name == ((((((png_uint_32) 80) << 24) | (((png_uint_32) 76) << 16)) | (((png_uint_32) 84) << 8)) | (((png_uint_32) 69) << 0)))
  {
    png_handle_PLTE(png_ptr, info_ptr, length);
  }
  else
    if (chunk_name == ((((((png_uint_32) 98) << 24) | (((png_uint_32) 75) << 16)) | (((png_uint_32) 71) << 8)) | (((png_uint_32) 68) << 0)))
  {
    png_handle_bKGD(png_ptr, info_ptr, length);
  }
  else
    if (chunk_name == ((((((png_uint_32) 104) << 24) | (((png_uint_32) 73) << 16)) | (((png_uint_32) 83) << 8)) | (((png_uint_32) 84) << 0)))
  {
    png_handle_hIST(png_ptr, info_ptr, length);
  }
  else
    if (chunk_name == ((((((png_uint_32) 115) << 24) | (((png_uint_32) 66) << 16)) | (((png_uint_32) 73) << 8)) | (((png_uint_32) 84) << 0)))
  {
    png_handle_sBIT(png_ptr, info_ptr, length);
  }
  else
    if (chunk_name == ((((((png_uint_32) 116) << 24) | (((png_uint_32) 82) << 16)) | (((png_uint_32) 78) << 8)) | (((png_uint_32) 83) << 0)))
  {
    png_handle_tRNS(png_ptr, info_ptr, length);
  }
  else
    png_handle_unknown(png_ptr, info_ptr, length, 0);
  *png_ptr_ref = png_ptr;
  *keep_ref = keep;
}


----------------------------
***/


void png_start_read_image(png_structrp png_ptr)
{
  (void) 0;
  if (png_ptr != 0)
  {
    if ((png_ptr->flags & 0x0040U) == 0)
    {
      png_read_start_row(png_ptr);
    }
    else
      png_app_error(png_ptr, "png_start_read_image/png_read_update_info: duplicate call");
  }
}


/*** DEPENDENCIES:
void png_read_start_row(png_structrp png_ptr)
{
  static const png_byte png_pass_start[7] = {0, 4, 0, 2, 0, 1, 0};
  static const png_byte png_pass_inc[7] = {8, 8, 4, 4, 2, 2, 1};
  static const png_byte png_pass_ystart[7] = {0, 0, 4, 0, 2, 0, 1};
  static const png_byte png_pass_yinc[7] = {8, 8, 8, 4, 4, 2, 2};
  unsigned int max_pixel_depth;
  size_t row_bytes;
  (void) 0;
  png_init_read_transformations(png_ptr);
  if (png_ptr->interlaced != 0)
  {
    if ((png_ptr->transformations & 0x0002U) == 0)
    {
      png_ptr->num_rows = (((png_ptr->height + png_pass_yinc[0]) - 1) - png_pass_ystart[0]) / png_pass_yinc[0];
    }
    else
      png_ptr->num_rows = png_ptr->height;
    png_ptr->iwidth = (((png_ptr->width + png_pass_inc[png_ptr->pass]) - 1) - png_pass_start[png_ptr->pass]) / png_pass_inc[png_ptr->pass];
  }
  else
  {
    png_ptr->num_rows = png_ptr->height;
    png_ptr->iwidth = png_ptr->width;
  }
  max_pixel_depth = (unsigned int) png_ptr->pixel_depth;
  png_ptr->maximum_pixel_depth = (png_byte) max_pixel_depth;
  png_ptr->transformed_pixel_depth = 0;
  row_bytes = (png_ptr->width + 7) & (~((png_uint_32) 7));
  row_bytes = (((max_pixel_depth >= 8) ? (((size_t) row_bytes) * (((size_t) max_pixel_depth) >> 3)) : (((((size_t) row_bytes) * ((size_t) max_pixel_depth)) + 7) >> 3)) + 1) + ((max_pixel_depth + 7) >> 3U);
  if ((row_bytes + 48) > png_ptr->old_big_row_buf_size)
  {
    helper_png_read_start_row_1(&png_ptr, row_bytes);
  }
  if (png_ptr->rowbytes > (((size_t) (-1)) - 1))
  {
    png_error(png_ptr, "Row has too many bytes to allocate in memory");
  }
  memset(png_ptr->prev_row, 0, png_ptr->rowbytes + 1);
  (void) 0;
  (void) 0;
  (void) 0;
  (void) 0;
  (void) 0;
  (void) 0;
  if (png_ptr->read_buffer != 0)
  {
    png_bytep buffer = png_ptr->read_buffer;
    png_ptr->read_buffer_size = 0;
    png_ptr->read_buffer = 0;
    png_free(png_ptr, buffer);
  }
  if (png_inflate_claim(png_ptr, (((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)) != 0)
  {
    png_error(png_ptr, png_ptr->zstream.msg);
  }
  png_ptr->flags |= 0x0040U;
}


----------------------------
void png_app_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr->flags & 0x400000U) != 0)
  {
    png_warning(png_ptr, error_message);
  }
  else
    png_error(png_ptr, error_message);
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


void helper_png_read_row_1(png_structrp png_ptr, png_bytep dsp_row)
{
  switch (png_ptr->pass)
  {
    case 0:
    {
      if (png_ptr->row_number & 0x07)
      {
        if (dsp_row != 0)
        {
          png_combine_row(png_ptr, dsp_row, 1);
        }
        png_read_finish_row(png_ptr);
        return;
      }
      break;
    }

    case 1:
    {
      if ((png_ptr->row_number & 0x07) || (png_ptr->width < 5))
      {
        if (dsp_row != 0)
        {
          png_combine_row(png_ptr, dsp_row, 1);
        }
        png_read_finish_row(png_ptr);
        return;
      }
      break;
    }

    case 2:
    {
      if ((png_ptr->row_number & 0x07) != 4)
      {
        if ((dsp_row != 0) && (png_ptr->row_number & 4))
        {
          png_combine_row(png_ptr, dsp_row, 1);
        }
        png_read_finish_row(png_ptr);
        return;
      }
      break;
    }

    case 3:
    {
      if ((png_ptr->row_number & 3) || (png_ptr->width < 3))
      {
        if (dsp_row != 0)
        {
          png_combine_row(png_ptr, dsp_row, 1);
        }
        png_read_finish_row(png_ptr);
        return;
      }
      break;
    }

    case 4:
    {
      if ((png_ptr->row_number & 3) != 2)
      {
        if ((dsp_row != 0) && (png_ptr->row_number & 2))
        {
          png_combine_row(png_ptr, dsp_row, 1);
        }
        png_read_finish_row(png_ptr);
        return;
      }
      break;
    }

    case 5:
    {
      if ((png_ptr->row_number & 1) || (png_ptr->width < 2))
      {
        if (dsp_row != 0)
        {
          png_combine_row(png_ptr, dsp_row, 1);
        }
        png_read_finish_row(png_ptr);
        return;
      }
      break;
    }

    default:

    case 6:
    {
      if ((png_ptr->row_number & 1) == 0)
      {
        png_read_finish_row(png_ptr);
        return;
      }
      break;
    }

  }

}


/*** DEPENDENCIES:
void png_combine_row(png_const_structrp png_ptr, png_bytep dp, int display)
{
  unsigned int pixel_depth = png_ptr->transformed_pixel_depth;
  png_const_bytep sp = png_ptr->row_buf + 1;
  png_alloc_size_t row_width = png_ptr->width;
  unsigned int pass = png_ptr->pass;
  png_bytep end_ptr = 0;
  png_byte end_byte = 0;
  unsigned int end_mask;
  (void) 0;
  if (pixel_depth == 0)
  {
    png_error(png_ptr, "internal row logic error");
  }
  if ((png_ptr->info_rowbytes != 0) && (png_ptr->info_rowbytes != ((pixel_depth >= 8) ? (((size_t) row_width) * (((size_t) pixel_depth) >> 3)) : (((((size_t) row_width) * ((size_t) pixel_depth)) + 7) >> 3))))
  {
    png_error(png_ptr, "internal row size calculation error");
  }
  if (row_width == 0)
  {
    png_error(png_ptr, "internal row width error");
  }
  end_mask = (pixel_depth * row_width) & 7;
  if (end_mask != 0)
  {
    end_ptr = (dp + ((pixel_depth >= 8) ? (((size_t) row_width) * (((size_t) pixel_depth) >> 3)) : (((((size_t) row_width) * ((size_t) pixel_depth)) + 7) >> 3))) - 1;
    end_byte = *end_ptr;
    end_mask = 0xff >> end_mask;
  }
  if ((((png_ptr->interlaced != 0) && ((png_ptr->transformations & 0x0002U) != 0)) && (pass < 6)) && ((display == 0) || ((display == 1) && ((pass & 1) != 0))))
  {
    helper_png_combine_row_1(&dp, &pixel_depth, &sp, &row_width, png_ptr, display, pass);
  }
  else
    memcpy(dp, sp, (pixel_depth >= 8) ? (((size_t) row_width) * (((size_t) pixel_depth) >> 3)) : (((((size_t) row_width) * ((size_t) pixel_depth)) + 7) >> 3));
  if (end_ptr != 0)
  {
    *end_ptr = (png_byte) ((end_byte & end_mask) | ((*end_ptr) & (~end_mask)));
  }
}


----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
void png_read_finish_row(png_structrp png_ptr)
{
  static const png_byte png_pass_start[7] = {0, 4, 0, 2, 0, 1, 0};
  static const png_byte png_pass_inc[7] = {8, 8, 4, 4, 2, 2, 1};
  static const png_byte png_pass_ystart[7] = {0, 0, 4, 0, 2, 0, 1};
  static const png_byte png_pass_yinc[7] = {8, 8, 8, 4, 4, 2, 2};
  (void) 0;
  png_ptr->row_number += 1;
  if (png_ptr->row_number < png_ptr->num_rows)
  {
    return;
  }
  if (png_ptr->interlaced != 0)
  {
    png_ptr->row_number = 0;
    memset(png_ptr->prev_row, 0, png_ptr->rowbytes + 1);
    do
    {
      png_ptr->pass += 1;
      if (png_ptr->pass >= 7)
      {
        break;
      }
      png_ptr->iwidth = (((png_ptr->width + png_pass_inc[png_ptr->pass]) - 1) - png_pass_start[png_ptr->pass]) / png_pass_inc[png_ptr->pass];
      if ((png_ptr->transformations & 0x0002U) == 0)
      {
        png_ptr->num_rows = (((png_ptr->height + png_pass_yinc[png_ptr->pass]) - 1) - png_pass_ystart[png_ptr->pass]) / png_pass_yinc[png_ptr->pass];
      }
      else
        break;
    }
    while ((png_ptr->num_rows == 0) || (png_ptr->iwidth == 0));
    if (png_ptr->pass < 7)
    {
      return;
    }
  }
  png_read_finish_IDAT(png_ptr);
}


----------------------------
typedef png_byte *png_bytep
----------------------------
***/


void png_read_row(png_structrp png_ptr, png_bytep row, png_bytep dsp_row)
{
  png_row_info row_info;
  if (png_ptr == 0)
  {
    return;
  }
  (void) 0;
  if ((png_ptr->flags & 0x0040U) == 0)
  {
    png_read_start_row(png_ptr);
  }
  row_info.width = png_ptr->iwidth;
  row_info.color_type = png_ptr->color_type;
  row_info.bit_depth = png_ptr->bit_depth;
  row_info.channels = png_ptr->channels;
  row_info.pixel_depth = png_ptr->pixel_depth;
  row_info.rowbytes = (row_info.pixel_depth >= 8) ? (((size_t) row_info.width) * (((size_t) row_info.pixel_depth) >> 3)) : (((((size_t) row_info.width) * ((size_t) row_info.pixel_depth)) + 7) >> 3);
  if ((png_ptr->row_number == 0) && (png_ptr->pass == 0))
  {
  }
  if ((png_ptr->interlaced != 0) && ((png_ptr->transformations & 0x0002U) != 0))
  {
    helper_png_read_row_1(png_ptr, dsp_row);
  }
  if ((png_ptr->mode & 0x04U) == 0)
  {
    png_error(png_ptr, "Invalid attempt to read row data");
  }
  png_ptr->row_buf[0] = 255;
  png_read_IDAT_data(png_ptr, png_ptr->row_buf, row_info.rowbytes + 1);
  if (png_ptr->row_buf[0] > 0)
  {
    if (png_ptr->row_buf[0] < 5)
    {
      png_read_filter_row(png_ptr, &row_info, png_ptr->row_buf + 1, png_ptr->prev_row + 1, png_ptr->row_buf[0]);
    }
    else
      png_error(png_ptr, "bad adaptive filter value");
  }
  memcpy(png_ptr->prev_row, png_ptr->row_buf, row_info.rowbytes + 1);
  if (png_ptr->transformations)
  {
    png_do_read_transformations(png_ptr, &row_info);
  }
  if (png_ptr->transformed_pixel_depth == 0)
  {
    png_ptr->transformed_pixel_depth = row_info.pixel_depth;
    if (row_info.pixel_depth > png_ptr->maximum_pixel_depth)
    {
      png_error(png_ptr, "sequential row overflow");
    }
  }
  else
    if (png_ptr->transformed_pixel_depth != row_info.pixel_depth)
  {
    png_error(png_ptr, "internal sequential row size calculation error");
  }
  if ((png_ptr->interlaced != 0) && ((png_ptr->transformations & 0x0002U) != 0))
  {
    if (png_ptr->pass < 6)
    {
      png_do_read_interlace(&row_info, png_ptr->row_buf + 1, png_ptr->pass, png_ptr->transformations);
    }
    if (dsp_row != 0)
    {
      png_combine_row(png_ptr, dsp_row, 1);
    }
    if (row != 0)
    {
      png_combine_row(png_ptr, row, 0);
    }
  }
  else
  {
    if (row != 0)
    {
      png_combine_row(png_ptr, row, -1);
    }
    if (dsp_row != 0)
    {
      png_combine_row(png_ptr, dsp_row, -1);
    }
  }
  png_read_finish_row(png_ptr);
  if (png_ptr->read_row_fn != 0)
  {
    (*png_ptr->read_row_fn)(png_ptr, png_ptr->row_number, png_ptr->pass);
  }
}


/*** DEPENDENCIES:
void png_do_read_interlace(png_row_infop row_info, png_bytep row, int pass, png_uint_32 transformations)
{
  static const unsigned int png_pass_inc[7] = {8, 8, 4, 4, 2, 2, 1};
  (void) 0;
  if ((row != 0) && (row_info != 0))
  {
    helper_png_do_read_interlace_1(&row_info, row, pass, png_pass_inc);
  }
  (void) transformations;
}


----------------------------
void png_read_filter_row(png_structrp pp, png_row_infop row_info, png_bytep row, png_const_bytep prev_row, int filter)
{
  if ((filter > 0) && (filter < 5))
  {
    if (pp->read_filter[0] == 0)
    {
      png_init_filter_functions(pp);
    }
    pp->read_filter[filter - 1](row_info, row, prev_row);
  }
}


----------------------------
void png_combine_row(png_const_structrp png_ptr, png_bytep dp, int display)
{
  unsigned int pixel_depth = png_ptr->transformed_pixel_depth;
  png_const_bytep sp = png_ptr->row_buf + 1;
  png_alloc_size_t row_width = png_ptr->width;
  unsigned int pass = png_ptr->pass;
  png_bytep end_ptr = 0;
  png_byte end_byte = 0;
  unsigned int end_mask;
  (void) 0;
  if (pixel_depth == 0)
  {
    png_error(png_ptr, "internal row logic error");
  }
  if ((png_ptr->info_rowbytes != 0) && (png_ptr->info_rowbytes != ((pixel_depth >= 8) ? (((size_t) row_width) * (((size_t) pixel_depth) >> 3)) : (((((size_t) row_width) * ((size_t) pixel_depth)) + 7) >> 3))))
  {
    png_error(png_ptr, "internal row size calculation error");
  }
  if (row_width == 0)
  {
    png_error(png_ptr, "internal row width error");
  }
  end_mask = (pixel_depth * row_width) & 7;
  if (end_mask != 0)
  {
    end_ptr = (dp + ((pixel_depth >= 8) ? (((size_t) row_width) * (((size_t) pixel_depth) >> 3)) : (((((size_t) row_width) * ((size_t) pixel_depth)) + 7) >> 3))) - 1;
    end_byte = *end_ptr;
    end_mask = 0xff >> end_mask;
  }
  if ((((png_ptr->interlaced != 0) && ((png_ptr->transformations & 0x0002U) != 0)) && (pass < 6)) && ((display == 0) || ((display == 1) && ((pass & 1) != 0))))
  {
    helper_png_combine_row_1(&dp, &pixel_depth, &sp, &row_width, png_ptr, display, pass);
  }
  else
    memcpy(dp, sp, (pixel_depth >= 8) ? (((size_t) row_width) * (((size_t) pixel_depth) >> 3)) : (((((size_t) row_width) * ((size_t) pixel_depth)) + 7) >> 3));
  if (end_ptr != 0)
  {
    *end_ptr = (png_byte) ((end_byte & end_mask) | ((*end_ptr) & (~end_mask)));
  }
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
typedef struct png_row_info_struct
{
  png_uint_32 width;
  size_t rowbytes;
  png_byte color_type;
  png_byte bit_depth;
  png_byte channels;
  png_byte pixel_depth;
} png_row_info
----------------------------
void png_do_read_transformations(png_structrp png_ptr, png_row_infop row_info)
{
  (void) 0;
  if (png_ptr->row_buf == 0)
  {
    png_error(png_ptr, "NULL row buffer");
  }
  if (((png_ptr->flags & 0x4000U) != 0) && ((png_ptr->flags & 0x0040U) == 0))
  {
    png_error(png_ptr, "Uninitialized row");
  }
  if ((row_info->color_type == (2 | 1)) && (png_ptr->num_palette_max >= 0))
  {
    png_do_check_palette_indexes(png_ptr, row_info);
  }
}


----------------------------
typedef unsigned char png_byte
----------------------------
void png_read_IDAT_data(png_structrp png_ptr, png_bytep output, png_alloc_size_t avail_out)
{
  png_ptr->zstream.next_out = output;
  png_ptr->zstream.avail_out = 0;
  if (output == 0)
  {
    avail_out = 0;
  }
  do
  {
    helper_png_read_IDAT_data_1(&png_ptr, &avail_out, output);
  }
  while (avail_out > 0);
  if (avail_out > 0)
  {
    if (output != 0)
    {
      png_error(png_ptr, "Not enough image data");
    }
    else
      png_chunk_benign_error(png_ptr, "Too much image data");
  }
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
void png_read_start_row(png_structrp png_ptr)
{
  static const png_byte png_pass_start[7] = {0, 4, 0, 2, 0, 1, 0};
  static const png_byte png_pass_inc[7] = {8, 8, 4, 4, 2, 2, 1};
  static const png_byte png_pass_ystart[7] = {0, 0, 4, 0, 2, 0, 1};
  static const png_byte png_pass_yinc[7] = {8, 8, 8, 4, 4, 2, 2};
  unsigned int max_pixel_depth;
  size_t row_bytes;
  (void) 0;
  png_init_read_transformations(png_ptr);
  if (png_ptr->interlaced != 0)
  {
    if ((png_ptr->transformations & 0x0002U) == 0)
    {
      png_ptr->num_rows = (((png_ptr->height + png_pass_yinc[0]) - 1) - png_pass_ystart[0]) / png_pass_yinc[0];
    }
    else
      png_ptr->num_rows = png_ptr->height;
    png_ptr->iwidth = (((png_ptr->width + png_pass_inc[png_ptr->pass]) - 1) - png_pass_start[png_ptr->pass]) / png_pass_inc[png_ptr->pass];
  }
  else
  {
    png_ptr->num_rows = png_ptr->height;
    png_ptr->iwidth = png_ptr->width;
  }
  max_pixel_depth = (unsigned int) png_ptr->pixel_depth;
  png_ptr->maximum_pixel_depth = (png_byte) max_pixel_depth;
  png_ptr->transformed_pixel_depth = 0;
  row_bytes = (png_ptr->width + 7) & (~((png_uint_32) 7));
  row_bytes = (((max_pixel_depth >= 8) ? (((size_t) row_bytes) * (((size_t) max_pixel_depth) >> 3)) : (((((size_t) row_bytes) * ((size_t) max_pixel_depth)) + 7) >> 3)) + 1) + ((max_pixel_depth + 7) >> 3U);
  if ((row_bytes + 48) > png_ptr->old_big_row_buf_size)
  {
    helper_png_read_start_row_1(&png_ptr, row_bytes);
  }
  if (png_ptr->rowbytes > (((size_t) (-1)) - 1))
  {
    png_error(png_ptr, "Row has too many bytes to allocate in memory");
  }
  memset(png_ptr->prev_row, 0, png_ptr->rowbytes + 1);
  (void) 0;
  (void) 0;
  (void) 0;
  (void) 0;
  (void) 0;
  (void) 0;
  if (png_ptr->read_buffer != 0)
  {
    png_bytep buffer = png_ptr->read_buffer;
    png_ptr->read_buffer_size = 0;
    png_ptr->read_buffer = 0;
    png_free(png_ptr, buffer);
  }
  if (png_inflate_claim(png_ptr, (((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)) != 0)
  {
    png_error(png_ptr, png_ptr->zstream.msg);
  }
  png_ptr->flags |= 0x0040U;
}


----------------------------
void png_read_finish_row(png_structrp png_ptr)
{
  static const png_byte png_pass_start[7] = {0, 4, 0, 2, 0, 1, 0};
  static const png_byte png_pass_inc[7] = {8, 8, 4, 4, 2, 2, 1};
  static const png_byte png_pass_ystart[7] = {0, 0, 4, 0, 2, 0, 1};
  static const png_byte png_pass_yinc[7] = {8, 8, 8, 4, 4, 2, 2};
  (void) 0;
  png_ptr->row_number += 1;
  if (png_ptr->row_number < png_ptr->num_rows)
  {
    return;
  }
  if (png_ptr->interlaced != 0)
  {
    png_ptr->row_number = 0;
    memset(png_ptr->prev_row, 0, png_ptr->rowbytes + 1);
    do
    {
      png_ptr->pass += 1;
      if (png_ptr->pass >= 7)
      {
        break;
      }
      png_ptr->iwidth = (((png_ptr->width + png_pass_inc[png_ptr->pass]) - 1) - png_pass_start[png_ptr->pass]) / png_pass_inc[png_ptr->pass];
      if ((png_ptr->transformations & 0x0002U) == 0)
      {
        png_ptr->num_rows = (((png_ptr->height + png_pass_yinc[png_ptr->pass]) - 1) - png_pass_ystart[png_ptr->pass]) / png_pass_yinc[png_ptr->pass];
      }
      else
        break;
    }
    while ((png_ptr->num_rows == 0) || (png_ptr->iwidth == 0));
    if (png_ptr->pass < 7)
    {
      return;
    }
  }
  png_read_finish_IDAT(png_ptr);
}


----------------------------
typedef png_byte *png_bytep
----------------------------
void helper_png_read_row_1(png_structrp png_ptr, png_bytep dsp_row)
{
  switch (png_ptr->pass)
  {
    case 0:
    {
      if (png_ptr->row_number & 0x07)
      {
        if (dsp_row != 0)
        {
          png_combine_row(png_ptr, dsp_row, 1);
        }
        png_read_finish_row(png_ptr);
        return;
      }
      break;
    }

    case 1:
    {
      if ((png_ptr->row_number & 0x07) || (png_ptr->width < 5))
      {
        if (dsp_row != 0)
        {
          png_combine_row(png_ptr, dsp_row, 1);
        }
        png_read_finish_row(png_ptr);
        return;
      }
      break;
    }

    case 2:
    {
      if ((png_ptr->row_number & 0x07) != 4)
      {
        if ((dsp_row != 0) && (png_ptr->row_number & 4))
        {
          png_combine_row(png_ptr, dsp_row, 1);
        }
        png_read_finish_row(png_ptr);
        return;
      }
      break;
    }

    case 3:
    {
      if ((png_ptr->row_number & 3) || (png_ptr->width < 3))
      {
        if (dsp_row != 0)
        {
          png_combine_row(png_ptr, dsp_row, 1);
        }
        png_read_finish_row(png_ptr);
        return;
      }
      break;
    }

    case 4:
    {
      if ((png_ptr->row_number & 3) != 2)
      {
        if ((dsp_row != 0) && (png_ptr->row_number & 2))
        {
          png_combine_row(png_ptr, dsp_row, 1);
        }
        png_read_finish_row(png_ptr);
        return;
      }
      break;
    }

    case 5:
    {
      if ((png_ptr->row_number & 1) || (png_ptr->width < 2))
      {
        if (dsp_row != 0)
        {
          png_combine_row(png_ptr, dsp_row, 1);
        }
        png_read_finish_row(png_ptr);
        return;
      }
      break;
    }

    default:

    case 6:
    {
      if ((png_ptr->row_number & 1) == 0)
      {
        png_read_finish_row(png_ptr);
        return;
      }
      break;
    }

  }

}


----------------------------
***/


void png_read_image(png_structrp png_ptr, png_bytepp image)
{
  png_uint_32 i;
  png_uint_32 image_height;
  int pass;
  int j;
  png_bytepp rp;
  (void) 0;
  if (png_ptr == 0)
  {
    return;
  }
  if ((png_ptr->flags & 0x0040U) == 0)
  {
    pass = png_set_interlace_handling(png_ptr);
    png_start_read_image(png_ptr);
  }
  else
  {
    if ((png_ptr->interlaced != 0) && ((png_ptr->transformations & 0x0002U) == 0))
    {
      png_warning(png_ptr, "Interlace handling should be turned on when using png_read_image");
      png_ptr->num_rows = png_ptr->height;
    }
    pass = png_set_interlace_handling(png_ptr);
  }
  image_height = png_ptr->height;
  for (j = 0; j < pass; j += 1)
  {
    rp = image;
    for (i = 0; i < image_height; i += 1)
    {
      png_read_row(png_ptr, *rp, 0);
      rp += 1;
    }

  }

}


/*** DEPENDENCIES:
int png_set_interlace_handling(png_structrp png_ptr)
{
  (void) 0;
  if ((png_ptr != 0) && (png_ptr->interlaced != 0))
  {
    png_ptr->transformations |= 0x0002U;
    return 7;
  }
  return 1;
}


----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
void png_start_read_image(png_structrp png_ptr)
{
  (void) 0;
  if (png_ptr != 0)
  {
    if ((png_ptr->flags & 0x0040U) == 0)
    {
      png_read_start_row(png_ptr);
    }
    else
      png_app_error(png_ptr, "png_start_read_image/png_read_update_info: duplicate call");
  }
}


----------------------------
typedef png_byte **png_bytepp
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
void png_read_row(png_structrp png_ptr, png_bytep row, png_bytep dsp_row)
{
  png_row_info row_info;
  if (png_ptr == 0)
  {
    return;
  }
  (void) 0;
  if ((png_ptr->flags & 0x0040U) == 0)
  {
    png_read_start_row(png_ptr);
  }
  row_info.width = png_ptr->iwidth;
  row_info.color_type = png_ptr->color_type;
  row_info.bit_depth = png_ptr->bit_depth;
  row_info.channels = png_ptr->channels;
  row_info.pixel_depth = png_ptr->pixel_depth;
  row_info.rowbytes = (row_info.pixel_depth >= 8) ? (((size_t) row_info.width) * (((size_t) row_info.pixel_depth) >> 3)) : (((((size_t) row_info.width) * ((size_t) row_info.pixel_depth)) + 7) >> 3);
  if ((png_ptr->row_number == 0) && (png_ptr->pass == 0))
  {
  }
  if ((png_ptr->interlaced != 0) && ((png_ptr->transformations & 0x0002U) != 0))
  {
    helper_png_read_row_1(png_ptr, dsp_row);
  }
  if ((png_ptr->mode & 0x04U) == 0)
  {
    png_error(png_ptr, "Invalid attempt to read row data");
  }
  png_ptr->row_buf[0] = 255;
  png_read_IDAT_data(png_ptr, png_ptr->row_buf, row_info.rowbytes + 1);
  if (png_ptr->row_buf[0] > 0)
  {
    if (png_ptr->row_buf[0] < 5)
    {
      png_read_filter_row(png_ptr, &row_info, png_ptr->row_buf + 1, png_ptr->prev_row + 1, png_ptr->row_buf[0]);
    }
    else
      png_error(png_ptr, "bad adaptive filter value");
  }
  memcpy(png_ptr->prev_row, png_ptr->row_buf, row_info.rowbytes + 1);
  if (png_ptr->transformations)
  {
    png_do_read_transformations(png_ptr, &row_info);
  }
  if (png_ptr->transformed_pixel_depth == 0)
  {
    png_ptr->transformed_pixel_depth = row_info.pixel_depth;
    if (row_info.pixel_depth > png_ptr->maximum_pixel_depth)
    {
      png_error(png_ptr, "sequential row overflow");
    }
  }
  else
    if (png_ptr->transformed_pixel_depth != row_info.pixel_depth)
  {
    png_error(png_ptr, "internal sequential row size calculation error");
  }
  if ((png_ptr->interlaced != 0) && ((png_ptr->transformations & 0x0002U) != 0))
  {
    if (png_ptr->pass < 6)
    {
      png_do_read_interlace(&row_info, png_ptr->row_buf + 1, png_ptr->pass, png_ptr->transformations);
    }
    if (dsp_row != 0)
    {
      png_combine_row(png_ptr, dsp_row, 1);
    }
    if (row != 0)
    {
      png_combine_row(png_ptr, row, 0);
    }
  }
  else
  {
    if (row != 0)
    {
      png_combine_row(png_ptr, row, -1);
    }
    if (dsp_row != 0)
    {
      png_combine_row(png_ptr, dsp_row, -1);
    }
  }
  png_read_finish_row(png_ptr);
  if (png_ptr->read_row_fn != 0)
  {
    (*png_ptr->read_row_fn)(png_ptr, png_ptr->row_number, png_ptr->pass);
  }
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


void png_read_update_info(png_structrp png_ptr, png_inforp info_ptr)
{
  (void) 0;
  if (png_ptr != 0)
  {
    if ((png_ptr->flags & 0x0040U) == 0)
    {
      png_read_start_row(png_ptr);
      png_read_transform_info(png_ptr, info_ptr);
    }
    else
      png_app_error(png_ptr, "png_read_update_info/png_start_read_image: duplicate call");
  }
}


/*** DEPENDENCIES:
void png_app_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr->flags & 0x400000U) != 0)
  {
    png_warning(png_ptr, error_message);
  }
  else
    png_error(png_ptr, error_message);
}


----------------------------
void png_read_transform_info(png_structrp png_ptr, png_inforp info_ptr)
{
  (void) 0;
  if (info_ptr->bit_depth == 16)
  {
  }
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
  info_ptr->rowbytes = (info_ptr->pixel_depth >= 8) ? (((size_t) info_ptr->width) * (((size_t) info_ptr->pixel_depth) >> 3)) : (((((size_t) info_ptr->width) * ((size_t) info_ptr->pixel_depth)) + 7) >> 3);
  png_ptr->info_rowbytes = info_ptr->rowbytes;
  if (png_ptr != 0)
  {
    return;
  }
}


----------------------------
typedef struct png_info_def png_info
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
void png_read_start_row(png_structrp png_ptr)
{
  static const png_byte png_pass_start[7] = {0, 4, 0, 2, 0, 1, 0};
  static const png_byte png_pass_inc[7] = {8, 8, 4, 4, 2, 2, 1};
  static const png_byte png_pass_ystart[7] = {0, 0, 4, 0, 2, 0, 1};
  static const png_byte png_pass_yinc[7] = {8, 8, 8, 4, 4, 2, 2};
  unsigned int max_pixel_depth;
  size_t row_bytes;
  (void) 0;
  png_init_read_transformations(png_ptr);
  if (png_ptr->interlaced != 0)
  {
    if ((png_ptr->transformations & 0x0002U) == 0)
    {
      png_ptr->num_rows = (((png_ptr->height + png_pass_yinc[0]) - 1) - png_pass_ystart[0]) / png_pass_yinc[0];
    }
    else
      png_ptr->num_rows = png_ptr->height;
    png_ptr->iwidth = (((png_ptr->width + png_pass_inc[png_ptr->pass]) - 1) - png_pass_start[png_ptr->pass]) / png_pass_inc[png_ptr->pass];
  }
  else
  {
    png_ptr->num_rows = png_ptr->height;
    png_ptr->iwidth = png_ptr->width;
  }
  max_pixel_depth = (unsigned int) png_ptr->pixel_depth;
  png_ptr->maximum_pixel_depth = (png_byte) max_pixel_depth;
  png_ptr->transformed_pixel_depth = 0;
  row_bytes = (png_ptr->width + 7) & (~((png_uint_32) 7));
  row_bytes = (((max_pixel_depth >= 8) ? (((size_t) row_bytes) * (((size_t) max_pixel_depth) >> 3)) : (((((size_t) row_bytes) * ((size_t) max_pixel_depth)) + 7) >> 3)) + 1) + ((max_pixel_depth + 7) >> 3U);
  if ((row_bytes + 48) > png_ptr->old_big_row_buf_size)
  {
    helper_png_read_start_row_1(&png_ptr, row_bytes);
  }
  if (png_ptr->rowbytes > (((size_t) (-1)) - 1))
  {
    png_error(png_ptr, "Row has too many bytes to allocate in memory");
  }
  memset(png_ptr->prev_row, 0, png_ptr->rowbytes + 1);
  (void) 0;
  (void) 0;
  (void) 0;
  (void) 0;
  (void) 0;
  (void) 0;
  if (png_ptr->read_buffer != 0)
  {
    png_bytep buffer = png_ptr->read_buffer;
    png_ptr->read_buffer_size = 0;
    png_ptr->read_buffer = 0;
    png_free(png_ptr, buffer);
  }
  if (png_inflate_claim(png_ptr, (((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)) != 0)
  {
    png_error(png_ptr, png_ptr->zstream.msg);
  }
  png_ptr->flags |= 0x0040U;
}


----------------------------
typedef png_info *png_inforp
----------------------------
***/


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


/*** DEPENDENCIES:
void png_app_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr->flags & 0x400000U) != 0)
  {
    png_warning(png_ptr, error_message);
  }
  else
    png_error(png_ptr, error_message);
}


----------------------------
int png_set_interlace_handling(png_structrp png_ptr)
{
  (void) 0;
  if ((png_ptr != 0) && (png_ptr->interlaced != 0))
  {
    png_ptr->transformations |= 0x0002U;
    return 7;
  }
  return 1;
}


----------------------------
void png_free_data(png_const_structrp png_ptr, png_inforp info_ptr, png_uint_32 mask, int num)
{
  (void) 0;
  if ((png_ptr == 0) || (info_ptr == 0))
  {
    return;
  }
  if (((mask & 0x2000U) & info_ptr->free_me) != 0)
  {
    info_ptr->valid &= ~0x0010U;
    png_free(png_ptr, info_ptr->trans_alpha);
    info_ptr->trans_alpha = 0;
    info_ptr->num_trans = 0;
  }
  if ((info_ptr->unknown_chunks != 0) && (((mask & 0x0200U) & info_ptr->free_me) != 0))
  {
    if (num != (-1))
    {
      png_free(png_ptr, info_ptr->unknown_chunks[num].data);
      info_ptr->unknown_chunks[num].data = 0;
    }
    else
    {
      int i;
      for (i = 0; i < info_ptr->unknown_chunks_num; i += 1)
      {
        png_free(png_ptr, info_ptr->unknown_chunks[i].data);
      }

      png_free(png_ptr, info_ptr->unknown_chunks);
      info_ptr->unknown_chunks = 0;
      info_ptr->unknown_chunks_num = 0;
    }
  }
  if (((mask & 0x0008U) & info_ptr->free_me) != 0)
  {
    png_free(png_ptr, info_ptr->hist);
    info_ptr->hist = 0;
    info_ptr->valid &= ~0x0040U;
  }
  if (((mask & 0x1000U) & info_ptr->free_me) != 0)
  {
    png_free(png_ptr, info_ptr->palette);
    info_ptr->palette = 0;
    info_ptr->valid &= ~0x0008U;
    info_ptr->num_palette = 0;
  }
  if (((mask & 0x0040U) & info_ptr->free_me) != 0)
  {
    if (info_ptr->row_pointers != 0)
    {
      png_uint_32 row;
      for (row = 0; row < info_ptr->height; row += 1)
      {
        png_free(png_ptr, info_ptr->row_pointers[row]);
      }

      png_free(png_ptr, info_ptr->row_pointers);
      info_ptr->row_pointers = 0;
    }
    info_ptr->valid &= ~0x8000U;
  }
  if (num != (-1))
  {
    mask &= ~0x4220U;
  }
  info_ptr->free_me &= ~mask;
}


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
void png_read_info(png_structrp png_ptr, png_inforp info_ptr)
{
  int keep;
  (void) 0;
  if ((png_ptr == 0) || (info_ptr == 0))
  {
    return;
  }
  png_read_sig(png_ptr, info_ptr);
  for (;;)
  {
    helper_png_read_info_1(&png_ptr, &keep, info_ptr);
  }

}


----------------------------
typedef void *voidp
----------------------------
typedef unsigned int png_uint_32
----------------------------
void png_read_end(png_structrp png_ptr, png_inforp info_ptr)
{
  int keep;
  (void) 0;
  if (png_ptr == 0)
  {
    return;
  }
  if (png_chunk_unknown_handling(png_ptr, (((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)) == 0)
  {
    png_read_finish_IDAT(png_ptr);
  }
  if ((png_ptr->color_type == (2 | 1)) && (png_ptr->num_palette_max > png_ptr->num_palette))
  {
    png_benign_error(png_ptr, "Read palette index exceeding num_palette");
  }
  do
  {
    helper_png_read_end_1(&png_ptr, &keep, info_ptr);
  }
  while ((png_ptr->mode & 0x10U) == 0);
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef struct png_info_def png_info
----------------------------
void png_read_image(png_structrp png_ptr, png_bytepp image)
{
  png_uint_32 i;
  png_uint_32 image_height;
  int pass;
  int j;
  png_bytepp rp;
  (void) 0;
  if (png_ptr == 0)
  {
    return;
  }
  if ((png_ptr->flags & 0x0040U) == 0)
  {
    pass = png_set_interlace_handling(png_ptr);
    png_start_read_image(png_ptr);
  }
  else
  {
    if ((png_ptr->interlaced != 0) && ((png_ptr->transformations & 0x0002U) == 0))
    {
      png_warning(png_ptr, "Interlace handling should be turned on when using png_read_image");
      png_ptr->num_rows = png_ptr->height;
    }
    pass = png_set_interlace_handling(png_ptr);
  }
  image_height = png_ptr->height;
  for (j = 0; j < pass; j += 1)
  {
    rp = image;
    for (i = 0; i < image_height; i += 1)
    {
      png_read_row(png_ptr, *rp, 0);
      rp += 1;
    }

  }

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
void png_read_update_info(png_structrp png_ptr, png_inforp info_ptr)
{
  (void) 0;
  if (png_ptr != 0)
  {
    if ((png_ptr->flags & 0x0040U) == 0)
    {
      png_read_start_row(png_ptr);
      png_read_transform_info(png_ptr, info_ptr);
    }
    else
      png_app_error(png_ptr, "png_read_update_info/png_start_read_image: duplicate call");
  }
}


----------------------------
typedef png_info *png_inforp
----------------------------
***/


void png_set_read_status_fn(png_structrp png_ptr, png_read_status_ptr read_row_fn)
{
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->read_row_fn = read_row_fn;
}


/*** DEPENDENCIES:
typedef void (*png_read_status_ptr)(png_structp, png_uint_32, int)
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


static void png_read_destroy(png_structrp png_ptr)
{
  (void) 0;
  png_free(png_ptr, png_ptr->big_row_buf);
  png_ptr->big_row_buf = 0;
  png_free(png_ptr, png_ptr->big_prev_row);
  png_ptr->big_prev_row = 0;
  png_free(png_ptr, png_ptr->read_buffer);
  png_ptr->read_buffer = 0;
  if ((png_ptr->free_me & 0x1000U) != 0)
  {
    png_zfree(png_ptr, png_ptr->palette);
    png_ptr->palette = 0;
  }
  png_ptr->free_me &= ~0x1000U;
  if ((png_ptr->free_me & 0x2000U) != 0)
  {
    png_free(png_ptr, png_ptr->trans_alpha);
    png_ptr->trans_alpha = 0;
  }
  png_ptr->free_me &= ~0x2000U;
  inflateEnd(&png_ptr->zstream);
  png_free(png_ptr, png_ptr->unknown_chunk.data);
  png_ptr->unknown_chunk.data = 0;
  png_free(png_ptr, png_ptr->chunk_list);
  png_ptr->chunk_list = 0;
}


/*** DEPENDENCIES:
void png_zfree(voidpf png_ptr, voidpf ptr)
{
  png_free(png_ptr, ptr);
}


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
typedef struct png_struct_def png_struct
----------------------------
typedef png_struct *png_structrp
----------------------------
int inflateEnd(z_streamp strm)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (inflateStateCheck(strm))
  {
    return -2;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  if (state->window != 0)
  {
    (*strm->zfree)(strm->opaque, (voidpf) state->window);
  }
  (*strm->zfree)(strm->opaque, (voidpf) strm->state);
  strm->state = 0;
  ;
  return 0;
}


----------------------------
***/


void png_destroy_read_struct(png_structpp png_ptr_ptr, png_infopp info_ptr_ptr, png_infopp end_info_ptr_ptr)
{
  png_structrp png_ptr = 0;
  (void) 0;
  if (png_ptr_ptr != 0)
  {
    png_ptr = *png_ptr_ptr;
  }
  if (png_ptr == 0)
  {
    return;
  }
  png_destroy_info_struct(png_ptr, end_info_ptr_ptr);
  png_destroy_info_struct(png_ptr, info_ptr_ptr);
  *png_ptr_ptr = 0;
  png_read_destroy(png_ptr);
  png_destroy_png_struct(png_ptr);
}


/*** DEPENDENCIES:
typedef png_struct **png_structpp
----------------------------
static void png_read_destroy(png_structrp png_ptr)
{
  (void) 0;
  png_free(png_ptr, png_ptr->big_row_buf);
  png_ptr->big_row_buf = 0;
  png_free(png_ptr, png_ptr->big_prev_row);
  png_ptr->big_prev_row = 0;
  png_free(png_ptr, png_ptr->read_buffer);
  png_ptr->read_buffer = 0;
  if ((png_ptr->free_me & 0x1000U) != 0)
  {
    png_zfree(png_ptr, png_ptr->palette);
    png_ptr->palette = 0;
  }
  png_ptr->free_me &= ~0x1000U;
  if ((png_ptr->free_me & 0x2000U) != 0)
  {
    png_free(png_ptr, png_ptr->trans_alpha);
    png_ptr->trans_alpha = 0;
  }
  png_ptr->free_me &= ~0x2000U;
  inflateEnd(&png_ptr->zstream);
  png_free(png_ptr, png_ptr->unknown_chunk.data);
  png_ptr->unknown_chunk.data = 0;
  png_free(png_ptr, png_ptr->chunk_list);
  png_ptr->chunk_list = 0;
}


----------------------------
typedef png_struct *png_structp
----------------------------
typedef png_info **png_infopp
----------------------------
void png_destroy_info_struct(png_const_structrp png_ptr, png_infopp info_ptr_ptr)
{
  png_inforp info_ptr = 0;
  (void) 0;
  if (png_ptr == 0)
  {
    return;
  }
  if (info_ptr_ptr != 0)
  {
    info_ptr = *info_ptr_ptr;
  }
  if (info_ptr != 0)
  {
    *info_ptr_ptr = 0;
    png_free_data(png_ptr, info_ptr, 0xffffU, -1);
    memset(info_ptr, 0, sizeof(*info_ptr));
    png_free(png_ptr, info_ptr);
  }
}


----------------------------
typedef png_info *png_infop
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_info_def png_info
----------------------------
void png_destroy_png_struct(png_structrp png_ptr)
{
  if (png_ptr != 0)
  {
    png_struct dummy_struct = *png_ptr;
    memset(png_ptr, 0, sizeof(*png_ptr));
    png_free(&dummy_struct, png_ptr);
  }
}


----------------------------
***/


void png_read_rows(png_structrp png_ptr, png_bytepp row, png_bytepp display_row, png_uint_32 num_rows)
{
  png_uint_32 i;
  png_bytepp rp;
  png_bytepp dp;
  (void) 0;
  if (png_ptr == 0)
  {
    return;
  }
  rp = row;
  dp = display_row;
  if ((rp != 0) && (dp != 0))
  {
    for (i = 0; i < num_rows; i += 1)
    {
      png_bytep rptr = *rp;
      rp += 1;
      png_bytep dptr = *dp;
      dp += 1;
      png_read_row(png_ptr, rptr, dptr);
    }

  }
  else
    if (rp != 0)
  {
    for (i = 0; i < num_rows; i += 1)
    {
      png_bytep rptr = *rp;
      png_read_row(png_ptr, rptr, 0);
      rp += 1;
    }

  }
  else
    if (dp != 0)
  {
    for (i = 0; i < num_rows; i += 1)
    {
      png_bytep dptr = *dp;
      png_read_row(png_ptr, 0, dptr);
      dp += 1;
    }

  }
}


/*** DEPENDENCIES:
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_byte **png_bytepp
----------------------------
void png_read_row(png_structrp png_ptr, png_bytep row, png_bytep dsp_row)
{
  png_row_info row_info;
  if (png_ptr == 0)
  {
    return;
  }
  (void) 0;
  if ((png_ptr->flags & 0x0040U) == 0)
  {
    png_read_start_row(png_ptr);
  }
  row_info.width = png_ptr->iwidth;
  row_info.color_type = png_ptr->color_type;
  row_info.bit_depth = png_ptr->bit_depth;
  row_info.channels = png_ptr->channels;
  row_info.pixel_depth = png_ptr->pixel_depth;
  row_info.rowbytes = (row_info.pixel_depth >= 8) ? (((size_t) row_info.width) * (((size_t) row_info.pixel_depth) >> 3)) : (((((size_t) row_info.width) * ((size_t) row_info.pixel_depth)) + 7) >> 3);
  if ((png_ptr->row_number == 0) && (png_ptr->pass == 0))
  {
  }
  if ((png_ptr->interlaced != 0) && ((png_ptr->transformations & 0x0002U) != 0))
  {
    helper_png_read_row_1(png_ptr, dsp_row);
  }
  if ((png_ptr->mode & 0x04U) == 0)
  {
    png_error(png_ptr, "Invalid attempt to read row data");
  }
  png_ptr->row_buf[0] = 255;
  png_read_IDAT_data(png_ptr, png_ptr->row_buf, row_info.rowbytes + 1);
  if (png_ptr->row_buf[0] > 0)
  {
    if (png_ptr->row_buf[0] < 5)
    {
      png_read_filter_row(png_ptr, &row_info, png_ptr->row_buf + 1, png_ptr->prev_row + 1, png_ptr->row_buf[0]);
    }
    else
      png_error(png_ptr, "bad adaptive filter value");
  }
  memcpy(png_ptr->prev_row, png_ptr->row_buf, row_info.rowbytes + 1);
  if (png_ptr->transformations)
  {
    png_do_read_transformations(png_ptr, &row_info);
  }
  if (png_ptr->transformed_pixel_depth == 0)
  {
    png_ptr->transformed_pixel_depth = row_info.pixel_depth;
    if (row_info.pixel_depth > png_ptr->maximum_pixel_depth)
    {
      png_error(png_ptr, "sequential row overflow");
    }
  }
  else
    if (png_ptr->transformed_pixel_depth != row_info.pixel_depth)
  {
    png_error(png_ptr, "internal sequential row size calculation error");
  }
  if ((png_ptr->interlaced != 0) && ((png_ptr->transformations & 0x0002U) != 0))
  {
    if (png_ptr->pass < 6)
    {
      png_do_read_interlace(&row_info, png_ptr->row_buf + 1, png_ptr->pass, png_ptr->transformations);
    }
    if (dsp_row != 0)
    {
      png_combine_row(png_ptr, dsp_row, 1);
    }
    if (row != 0)
    {
      png_combine_row(png_ptr, row, 0);
    }
  }
  else
  {
    if (row != 0)
    {
      png_combine_row(png_ptr, row, -1);
    }
    if (dsp_row != 0)
    {
      png_combine_row(png_ptr, dsp_row, -1);
    }
  }
  png_read_finish_row(png_ptr);
  if (png_ptr->read_row_fn != 0)
  {
    (*png_ptr->read_row_fn)(png_ptr, png_ptr->row_number, png_ptr->pass);
  }
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


