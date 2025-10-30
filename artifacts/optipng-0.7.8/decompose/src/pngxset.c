void pngx_set_interlace_type(png_structp png_ptr, png_infop info_ptr, int interlace_type)
{
  png_uint_32 width;
  png_uint_32 height;
  int bit_depth;
  int color_type;
  int compression_type;
  int filter_type;
  int old_interlace_type;
  if (!png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &old_interlace_type, &compression_type, &filter_type))
  {
    return;
  }
  if (interlace_type == old_interlace_type)
  {
    return;
  }
  png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type, interlace_type, compression_type, filter_type);
}


/*** DEPENDENCIES:
typedef png_struct *png_structp
----------------------------
typedef unsigned int png_uint_32
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


----------------------------
typedef png_info *png_infop
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef struct png_info_def png_info
----------------------------
***/


void pngx_set_compression_type(png_structp png_ptr, png_infop info_ptr, int compression_type)
{
  png_uint_32 width;
  png_uint_32 height;
  int bit_depth;
  int color_type;
  int interlace_type;
  int filter_type;
  int old_compression_type;
  if (!png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, &old_compression_type, &filter_type))
  {
    return;
  }
  if (compression_type == old_compression_type)
  {
    return;
  }
  png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type, interlace_type, compression_type, filter_type);
}


/*** DEPENDENCIES:
typedef png_struct *png_structp
----------------------------
typedef unsigned int png_uint_32
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


----------------------------
typedef png_info *png_infop
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef struct png_info_def png_info
----------------------------
***/


void pngx_set_filter_type(png_structp png_ptr, png_infop info_ptr, int filter_type)
{
  png_uint_32 width;
  png_uint_32 height;
  int bit_depth;
  int color_type;
  int interlace_type;
  int compression_type;
  int old_filter_type;
  if (!png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, &compression_type, &old_filter_type))
  {
    return;
  }
  if (filter_type == old_filter_type)
  {
    return;
  }
  png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type, interlace_type, compression_type, filter_type);
}


/*** DEPENDENCIES:
typedef png_struct *png_structp
----------------------------
typedef unsigned int png_uint_32
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


----------------------------
typedef png_info *png_infop
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef struct png_info_def png_info
----------------------------
***/


