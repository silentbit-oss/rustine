size_t png_get_compression_buffer_size(png_const_structrp png_ptr)
{
  if (png_ptr == 0)
  {
    return 0;
  }
  if ((png_ptr->mode & 0x8000U) != 0)
  {
    return png_ptr->IDAT_read_size;
  }
  else
    return png_ptr->zbuffer_size;
}


/*** DEPENDENCIES:
typedef const png_struct *png_const_structrp
----------------------------
***/


png_uint_32 png_get_user_width_max(png_const_structrp png_ptr)
{
  return (png_ptr) ? (png_ptr->user_width_max) : (0);
}


/*** DEPENDENCIES:
typedef const png_struct *png_const_structrp
----------------------------
***/


png_uint_32 png_get_user_height_max(png_const_structrp png_ptr)
{
  return (png_ptr) ? (png_ptr->user_height_max) : (0);
}


/*** DEPENDENCIES:
typedef const png_struct *png_const_structrp
----------------------------
***/


png_uint_32 png_get_chunk_cache_max(png_const_structrp png_ptr)
{
  return (png_ptr) ? (png_ptr->user_chunk_cache_max) : (0);
}


/*** DEPENDENCIES:
typedef const png_struct *png_const_structrp
----------------------------
***/


png_alloc_size_t png_get_chunk_malloc_max(png_const_structrp png_ptr)
{
  return (png_ptr) ? (png_ptr->user_chunk_malloc_max) : (0);
}


/*** DEPENDENCIES:
typedef const png_struct *png_const_structrp
----------------------------
***/


png_uint_32 png_get_io_state(png_const_structrp png_ptr)
{
  return png_ptr->io_state;
}


/*** DEPENDENCIES:
typedef const png_struct *png_const_structrp
----------------------------
***/


png_uint_32 png_get_io_chunk_type(png_const_structrp png_ptr)
{
  return png_ptr->chunk_name;
}


/*** DEPENDENCIES:
typedef const png_struct *png_const_structrp
----------------------------
***/


size_t png_get_rowbytes(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    return info_ptr->rowbytes;
  }
  return 0;
}


/*** DEPENDENCIES:
typedef const png_info *png_const_inforp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


png_bytepp png_get_rows(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    return info_ptr->row_pointers;
  }
  return 0;
}


/*** DEPENDENCIES:
typedef const png_info *png_const_inforp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


png_byte png_get_channels(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    return info_ptr->channels;
  }
  return 0;
}


/*** DEPENDENCIES:
typedef const png_info *png_const_inforp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


png_uint_32 png_get_image_width(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    return info_ptr->width;
  }
  return 0;
}


/*** DEPENDENCIES:
typedef const png_info *png_const_inforp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


png_uint_32 png_get_image_height(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    return info_ptr->height;
  }
  return 0;
}


/*** DEPENDENCIES:
typedef const png_info *png_const_inforp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


png_byte png_get_bit_depth(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    return info_ptr->bit_depth;
  }
  return 0;
}


/*** DEPENDENCIES:
typedef const png_info *png_const_inforp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


png_byte png_get_color_type(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    return info_ptr->color_type;
  }
  return 0;
}


/*** DEPENDENCIES:
typedef const png_info *png_const_inforp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


png_byte png_get_filter_type(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    return info_ptr->filter_type;
  }
  return 0;
}


/*** DEPENDENCIES:
typedef const png_info *png_const_inforp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


png_byte png_get_interlace_type(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    return info_ptr->interlace_type;
  }
  return 0;
}


/*** DEPENDENCIES:
typedef const png_info *png_const_inforp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


png_byte png_get_compression_type(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    return info_ptr->compression_type;
  }
  return 0;
}


/*** DEPENDENCIES:
typedef const png_info *png_const_inforp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


png_uint_32 png_get_pixels_per_meter(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  (void) png_ptr;
  (void) info_ptr;
  return 0;
}


/*** DEPENDENCIES:
typedef const png_info *png_const_inforp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


png_uint_32 png_get_x_pixels_per_meter(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  (void) png_ptr;
  (void) info_ptr;
  return 0;
}


/*** DEPENDENCIES:
typedef const png_info *png_const_inforp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


png_uint_32 png_get_y_pixels_per_meter(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  (void) png_ptr;
  (void) info_ptr;
  return 0;
}


/*** DEPENDENCIES:
typedef const png_info *png_const_inforp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


png_fixed_point png_get_pixel_aspect_ratio_fixed(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  (void) png_ptr;
  (void) info_ptr;
  return 0;
}


/*** DEPENDENCIES:
typedef const png_info *png_const_inforp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


png_int_32 png_get_x_offset_pixels(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  (void) png_ptr;
  (void) info_ptr;
  return 0;
}


/*** DEPENDENCIES:
typedef const png_info *png_const_inforp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


png_int_32 png_get_y_offset_pixels(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  (void) png_ptr;
  (void) info_ptr;
  return 0;
}


/*** DEPENDENCIES:
typedef const png_info *png_const_inforp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


png_int_32 png_get_x_offset_microns(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  (void) png_ptr;
  (void) info_ptr;
  return 0;
}


/*** DEPENDENCIES:
typedef const png_info *png_const_inforp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


png_int_32 png_get_y_offset_microns(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  (void) png_ptr;
  (void) info_ptr;
  return 0;
}


/*** DEPENDENCIES:
typedef const png_info *png_const_inforp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


png_const_bytep png_get_signature(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    return info_ptr->signature;
  }
  return 0;
}


/*** DEPENDENCIES:
typedef const png_info *png_const_inforp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


int png_get_palette_max(png_const_structp png_ptr, png_const_infop info_ptr)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    return png_ptr->num_palette_max;
  }
  return -1;
}


/*** DEPENDENCIES:
typedef const png_struct *png_const_structp
----------------------------
typedef const png_info *png_const_infop
----------------------------
***/


png_uint_32 png_get_valid(png_const_structrp png_ptr, png_const_inforp info_ptr, png_uint_32 flag)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    if ((flag == 0x0010U) && (png_ptr->num_trans == 0))
    {
      return 0;
    }
    return info_ptr->valid & flag;
  }
  return 0;
}


/*** DEPENDENCIES:
typedef unsigned int png_uint_32
----------------------------
typedef const png_info *png_const_inforp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


png_uint_32 png_get_IHDR(png_const_structrp png_ptr, png_const_inforp info_ptr, png_uint_32 *width, png_uint_32 *height, int *bit_depth, int *color_type, int *interlace_type, int *compression_type, int *filter_type)
{
  (void) 0;
  if ((png_ptr == 0) || (info_ptr == 0))
  {
    return 0;
  }
  if (width != 0)
  {
    *width = info_ptr->width;
  }
  if (height != 0)
  {
    *height = info_ptr->height;
  }
  if (bit_depth != 0)
  {
    *bit_depth = info_ptr->bit_depth;
  }
  if (color_type != 0)
  {
    *color_type = info_ptr->color_type;
  }
  if (compression_type != 0)
  {
    *compression_type = info_ptr->compression_type;
  }
  if (filter_type != 0)
  {
    *filter_type = info_ptr->filter_type;
  }
  if (interlace_type != 0)
  {
    *interlace_type = info_ptr->interlace_type;
  }
  png_check_IHDR(png_ptr, info_ptr->width, info_ptr->height, info_ptr->bit_depth, info_ptr->color_type, info_ptr->interlace_type, info_ptr->compression_type, info_ptr->filter_type);
  return 1;
}


/*** DEPENDENCIES:
void png_check_IHDR(png_const_structrp png_ptr, png_uint_32 width, png_uint_32 height, int bit_depth, int color_type, int interlace_type, int compression_type, int filter_type)
{
  int error = 0;
  if (width == 0)
  {
    png_warning(png_ptr, "Image width is zero in IHDR");
    error = 1;
  }
  if (width > ((png_uint_32) 0x7fffffffL))
  {
    png_warning(png_ptr, "Invalid image width in IHDR");
    error = 1;
  }
  if (png_gt((width + 7) & (~7U), (((((size_t) (-1)) - 48) - 1) / 8) - 1))
  {
    png_warning(png_ptr, "Image width is too large for this architecture");
    error = 1;
  }
  if (width > png_ptr->user_width_max)
  {
    png_warning(png_ptr, "Image width exceeds user limit in IHDR");
    error = 1;
  }
  if (height == 0)
  {
    png_warning(png_ptr, "Image height is zero in IHDR");
    error = 1;
  }
  if (height > ((png_uint_32) 0x7fffffffL))
  {
    png_warning(png_ptr, "Invalid image height in IHDR");
    error = 1;
  }
  if (height > png_ptr->user_height_max)
  {
    png_warning(png_ptr, "Image height exceeds user limit in IHDR");
    error = 1;
  }
  if (((((bit_depth != 1) && (bit_depth != 2)) && (bit_depth != 4)) && (bit_depth != 8)) && (bit_depth != 16))
  {
    png_warning(png_ptr, "Invalid bit depth in IHDR");
    error = 1;
  }
  if ((((color_type < 0) || (color_type == 1)) || (color_type == 5)) || (color_type > 6))
  {
    png_warning(png_ptr, "Invalid color type in IHDR");
    error = 1;
  }
  if (((color_type == (2 | 1)) && (bit_depth > 8)) || ((((color_type == 2) || (color_type == 4)) || (color_type == (2 | 4))) && (bit_depth < 8)))
  {
    png_warning(png_ptr, "Invalid color type/bit depth combination in IHDR");
    error = 1;
  }
  if (interlace_type >= 2)
  {
    png_warning(png_ptr, "Unknown interlace method in IHDR");
    error = 1;
  }
  if (compression_type != 0)
  {
    png_warning(png_ptr, "Unknown compression method in IHDR");
    error = 1;
  }
  if (filter_type != 0)
  {
    png_warning(png_ptr, "Unknown filter method in IHDR");
    error = 1;
  }
  if (error == 1)
  {
    png_error(png_ptr, "Invalid IHDR data");
  }
}


----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef const png_info *png_const_inforp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


png_uint_32 png_get_tRNS(png_const_structrp png_ptr, png_inforp info_ptr, png_bytep *trans_alpha, int *num_trans, png_color_16p *trans_color)
{
  png_uint_32 retval = 0;
  if (((png_ptr != 0) && (info_ptr != 0)) && ((info_ptr->valid & 0x0010U) != 0))
  {
    (void) 0;
    if (info_ptr->color_type == (2 | 1))
    {
      if (trans_alpha != 0)
      {
        *trans_alpha = info_ptr->trans_alpha;
        retval |= 0x0010U;
      }
      if (trans_color != 0)
      {
        *trans_color = &info_ptr->trans_color;
      }
    }
    else
    {
      if (trans_color != 0)
      {
        *trans_color = &info_ptr->trans_color;
        retval |= 0x0010U;
      }
      if (trans_alpha != 0)
      {
        *trans_alpha = 0;
      }
    }
    if (num_trans != 0)
    {
      *num_trans = info_ptr->num_trans;
      retval |= 0x0010U;
    }
  }
  return retval;
}


/*** DEPENDENCIES:
typedef struct png_color_struct
{
  png_byte red;
  png_byte green;
  png_byte blue;
} png_color
----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_color_16 *png_color_16p
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
typedef struct png_color_16_struct
{
  png_byte index;
  png_uint_16 red;
  png_uint_16 green;
  png_uint_16 blue;
  png_uint_16 gray;
} png_color_16
----------------------------
typedef struct png_info_def png_info
----------------------------
typedef png_byte *png_bytep
----------------------------
typedef png_info *png_inforp
----------------------------
***/


png_uint_32 png_get_PLTE(png_const_structrp png_ptr, png_inforp info_ptr, png_colorp *palette, int *num_palette)
{
  (void) 0;
  if ((((png_ptr != 0) && (info_ptr != 0)) && ((info_ptr->valid & 0x0008U) != 0)) && (palette != 0))
  {
    *palette = info_ptr->palette;
    *num_palette = info_ptr->num_palette;
    (void) 0;
    return 0x0008U;
  }
  return 0;
}


/*** DEPENDENCIES:
typedef struct png_color_struct
{
  png_byte red;
  png_byte green;
  png_byte blue;
} png_color
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
typedef struct png_info_def png_info
----------------------------
typedef png_color *png_colorp
----------------------------
typedef png_info *png_inforp
----------------------------
***/


png_uint_32 png_get_bKGD(png_const_structrp png_ptr, png_inforp info_ptr, png_color_16p *background)
{
  if ((((png_ptr != 0) && (info_ptr != 0)) && ((info_ptr->valid & 0x0020U) != 0)) && (background != 0))
  {
    (void) 0;
    *background = &info_ptr->background;
    return 0x0020U;
  }
  return 0;
}


/*** DEPENDENCIES:
typedef struct png_color_struct
{
  png_byte red;
  png_byte green;
  png_byte blue;
} png_color
----------------------------
typedef png_color_16 *png_color_16p
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
typedef struct png_color_16_struct
{
  png_byte index;
  png_uint_16 red;
  png_uint_16 green;
  png_uint_16 blue;
  png_uint_16 gray;
} png_color_16
----------------------------
typedef struct png_info_def png_info
----------------------------
typedef png_info *png_inforp
----------------------------
***/


png_uint_32 png_get_hIST(png_const_structrp png_ptr, png_inforp info_ptr, png_uint_16p *hist)
{
  (void) 0;
  if ((((png_ptr != 0) && (info_ptr != 0)) && ((info_ptr->valid & 0x0040U) != 0)) && (hist != 0))
  {
    *hist = info_ptr->hist;
    return 0x0040U;
  }
  return 0;
}


/*** DEPENDENCIES:
typedef png_uint_16 *png_uint_16p
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
typedef struct png_info_def png_info
----------------------------
typedef unsigned short png_uint_16
----------------------------
typedef png_info *png_inforp
----------------------------
***/


png_uint_32 png_get_sBIT(png_const_structrp png_ptr, png_inforp info_ptr, png_color_8p *sig_bit)
{
  (void) 0;
  if ((((png_ptr != 0) && (info_ptr != 0)) && ((info_ptr->valid & 0x0002U) != 0)) && (sig_bit != 0))
  {
    *sig_bit = &info_ptr->sig_bit;
    return 0x0002U;
  }
  return 0;
}


/*** DEPENDENCIES:
typedef struct png_color_8_struct
{
  png_byte red;
  png_byte green;
  png_byte blue;
  png_byte gray;
  png_byte alpha;
} png_color_8
----------------------------
typedef struct png_color_struct
{
  png_byte red;
  png_byte green;
  png_byte blue;
} png_color
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
typedef struct png_info_def png_info
----------------------------
typedef png_color_8 *png_color_8p
----------------------------
typedef png_info *png_inforp
----------------------------
***/


int png_get_unknown_chunks(png_const_structrp png_ptr, png_inforp info_ptr, png_unknown_chunkpp unknowns)
{
  if (((png_ptr != 0) && (info_ptr != 0)) && (unknowns != 0))
  {
    *unknowns = info_ptr->unknown_chunks;
    return info_ptr->unknown_chunks_num;
  }
  return 0;
}


/*** DEPENDENCIES:
typedef const png_struct *png_const_structrp
----------------------------
typedef struct png_unknown_chunk_t
{
  png_byte name[5];
  png_byte *data;
  size_t size;
  png_byte location;
} png_unknown_chunk
----------------------------
typedef png_unknown_chunk **png_unknown_chunkpp
----------------------------
typedef png_unknown_chunk *png_unknown_chunkp
----------------------------
typedef struct png_info_def png_info
----------------------------
typedef png_info *png_inforp
----------------------------
***/


