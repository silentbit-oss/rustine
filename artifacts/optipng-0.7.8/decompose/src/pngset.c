void png_set_benign_errors(png_structrp png_ptr, int allowed)
{
  (void) 0;
  if (allowed != 0)
  {
    png_ptr->flags |= (0x100000U | 0x200000U) | 0x400000U;
  }
  else
    png_ptr->flags &= ~((0x100000U | 0x200000U) | 0x400000U);
}


/*** DEPENDENCIES:
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


void png_set_check_for_invalid_index(png_structrp png_ptr, int allowed)
{
  (void) 0;
  if (allowed > 0)
  {
    png_ptr->num_palette_max = 0;
  }
  else
    png_ptr->num_palette_max = -1;
}


/*** DEPENDENCIES:
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


static unsigned int add_one_chunk(png_bytep list, unsigned int count, png_const_bytep add, int keep)
{
  unsigned int i;
  for (i = 0; i < count; i += 1, list += 5)
  {
    if (memcmp(list, add, 4) == 0)
    {
      list[4] = (png_byte) keep;
      return count;
    }
  }

  if (keep != 0)
  {
    count += 1;
    memcpy(list, add, 4);
    list[4] = (png_byte) keep;
  }
  return count;
}


/*** DEPENDENCIES:
typedef const png_byte *png_const_bytep
----------------------------
typedef png_byte *png_bytep
----------------------------
typedef unsigned char png_byte
----------------------------
***/


// hint:  ['new_list_ref is a mutable refrence to png_bytep', 'num_chunks_ref is a mutable refrence to unsigned int', 'old_num_chunks_ref is a mutable refrence to unsigned int']
void helper_png_set_keep_unknown_chunks_1(png_bytep * const new_list_ref, unsigned int * const num_chunks_ref, unsigned int * const old_num_chunks_ref, png_structrp png_ptr, int keep, png_const_bytep chunk_list)
{
  png_bytep new_list = *new_list_ref;
  unsigned int num_chunks = *num_chunks_ref;
  unsigned int old_num_chunks = *old_num_chunks_ref;
  png_const_bytep inlist;
  png_bytep outlist;
  unsigned int i;
  for (i = 0; i < num_chunks; i += 1)
  {
    old_num_chunks = add_one_chunk(new_list, old_num_chunks, chunk_list + (5 * i), keep);
  }

  num_chunks = 0;
  for (i = 0, inlist = (outlist = new_list); i < old_num_chunks; i += 1, inlist += 5)
  {
    if (inlist[4])
    {
      if (outlist != inlist)
      {
        memcpy(outlist, inlist, 5);
      }
      outlist += 5;
      num_chunks += 1;
    }
  }

  if (num_chunks == 0)
  {
    if (png_ptr->chunk_list != new_list)
    {
      png_free(png_ptr, new_list);
    }
    new_list = 0;
  }
  *new_list_ref = new_list;
  *num_chunks_ref = num_chunks;
  *old_num_chunks_ref = old_num_chunks;
}


/*** DEPENDENCIES:
typedef const png_byte *png_const_bytep
----------------------------
typedef unsigned char png_byte
----------------------------
static unsigned int add_one_chunk(png_bytep list, unsigned int count, png_const_bytep add, int keep)
{
  unsigned int i;
  for (i = 0; i < count; i += 1, list += 5)
  {
    if (memcmp(list, add, 4) == 0)
    {
      list[4] = (png_byte) keep;
      return count;
    }
  }

  if (keep != 0)
  {
    count += 1;
    memcpy(list, add, 4);
    list[4] = (png_byte) keep;
  }
  return count;
}


----------------------------
typedef png_struct *png_structrp
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
typedef png_byte *png_bytep
----------------------------
***/


void png_set_keep_unknown_chunks(png_structrp png_ptr, int keep, png_const_bytep chunk_list, int num_chunks_in)
{
  png_bytep new_list;
  unsigned int num_chunks;
  unsigned int old_num_chunks;
  if (png_ptr == 0)
  {
    return;
  }
  if ((keep < 0) || (keep >= 4))
  {
    png_app_error(png_ptr, "png_set_keep_unknown_chunks: invalid keep");
    return;
  }
  if (num_chunks_in <= 0)
  {
    png_ptr->unknown_default = keep;
    if (num_chunks_in == 0)
    {
      return;
    }
  }
  if (num_chunks_in < 0)
  {
    static const png_byte chunks_to_ignore[] = {98, 75, 71, 68, '\0', 99, 72, 82, 77, '\0', 101, 88, 73, 102, '\0', 103, 65, 77, 65, '\0', 104, 73, 83, 84, '\0', 105, 67, 67, 80, '\0', 105, 84, 88, 116, '\0', 111, 70, 70, 115, '\0', 112, 67, 65, 76, '\0', 112, 72, 89, 115, '\0', 115, 66, 73, 84, '\0', 115, 67, 65, 76, '\0', 115, 80, 76, 84, '\0', 115, 84, 69, 82, '\0', 115, 82, 71, 66, '\0', 116, 69, 88, 116, '\0', 116, 73, 77, 69, '\0', 122, 84, 88, 116, '\0'};
    chunk_list = chunks_to_ignore;
    num_chunks = ((unsigned int) (sizeof(chunks_to_ignore))) / 5U;
  }
  else
  {
    if (chunk_list == 0)
    {
      png_app_error(png_ptr, "png_set_keep_unknown_chunks: no chunk list");
      return;
    }
    num_chunks = (unsigned int) num_chunks_in;
  }
  old_num_chunks = png_ptr->num_chunk_list;
  if (png_ptr->chunk_list == 0)
  {
    old_num_chunks = 0;
  }
  if ((num_chunks + old_num_chunks) > (4294967295U / 5))
  {
    png_app_error(png_ptr, "png_set_keep_unknown_chunks: too many chunks");
    return;
  }
  if (keep != 0)
  {
    new_list = png_malloc(png_ptr, 5 * (num_chunks + old_num_chunks));
    if (old_num_chunks > 0)
    {
      memcpy(new_list, png_ptr->chunk_list, 5 * old_num_chunks);
    }
  }
  else
    if (old_num_chunks > 0)
  {
    new_list = png_ptr->chunk_list;
  }
  else
    new_list = 0;
  if (new_list != 0)
  {
    helper_png_set_keep_unknown_chunks_1(&new_list, &num_chunks, &old_num_chunks, png_ptr, keep, chunk_list);
  }
  else
    num_chunks = 0;
  png_ptr->num_chunk_list = num_chunks;
  if (png_ptr->chunk_list != new_list)
  {
    if (png_ptr->chunk_list != 0)
    {
      png_free(png_ptr, png_ptr->chunk_list);
    }
    png_ptr->chunk_list = new_list;
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
typedef const png_byte *png_const_bytep
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
typedef unsigned char png_byte
----------------------------
void helper_png_set_keep_unknown_chunks_1(png_bytep * const new_list_ref, unsigned int * const num_chunks_ref, unsigned int * const old_num_chunks_ref, png_structrp png_ptr, int keep, png_const_bytep chunk_list)
{
  png_bytep new_list = *new_list_ref;
  unsigned int num_chunks = *num_chunks_ref;
  unsigned int old_num_chunks = *old_num_chunks_ref;
  png_const_bytep inlist;
  png_bytep outlist;
  unsigned int i;
  for (i = 0; i < num_chunks; i += 1)
  {
    old_num_chunks = add_one_chunk(new_list, old_num_chunks, chunk_list + (5 * i), keep);
  }

  num_chunks = 0;
  for (i = 0, inlist = (outlist = new_list); i < old_num_chunks; i += 1, inlist += 5)
  {
    if (inlist[4])
    {
      if (outlist != inlist)
      {
        memcpy(outlist, inlist, 5);
      }
      outlist += 5;
      num_chunks += 1;
    }
  }

  if (num_chunks == 0)
  {
    if (png_ptr->chunk_list != new_list)
    {
      png_free(png_ptr, new_list);
    }
    new_list = 0;
  }
  *new_list_ref = new_list;
  *num_chunks_ref = num_chunks;
  *old_num_chunks_ref = old_num_chunks;
}


----------------------------
typedef png_struct *png_structrp
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
typedef png_byte *png_bytep
----------------------------
***/


void png_set_user_limits(png_structrp png_ptr, png_uint_32 user_width_max, png_uint_32 user_height_max)
{
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->user_width_max = user_width_max;
  png_ptr->user_height_max = user_height_max;
}


/*** DEPENDENCIES:
typedef unsigned int png_uint_32
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


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


/*** DEPENDENCIES:
typedef struct png_info_def png_info
----------------------------
typedef const png_color_8 *png_const_color_8p
----------------------------
typedef png_info *png_inforp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


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


/*** DEPENDENCIES:
typedef unsigned int png_uint_32
----------------------------
typedef struct png_info_def png_info
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
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
typedef png_info *png_inforp
----------------------------
***/


void png_set_bKGD(png_const_structrp png_ptr, png_inforp info_ptr, png_const_color_16p background)
{
  (void) 0;
  if (((png_ptr == 0) || (info_ptr == 0)) || (background == 0))
  {
    return;
  }
  info_ptr->background = *background;
  info_ptr->valid |= 0x0020U;
}


/*** DEPENDENCIES:
typedef struct png_info_def png_info
----------------------------
typedef const png_color_16 *png_const_color_16p
----------------------------
typedef png_info *png_inforp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


void png_set_PLTE(png_structrp png_ptr, png_inforp info_ptr, png_const_colorp palette, int num_palette)
{
  png_uint_32 max_palette_length;
  (void) 0;
  if ((png_ptr == 0) || (info_ptr == 0))
  {
    return;
  }
  max_palette_length = (info_ptr->color_type == (2 | 1)) ? (1 << info_ptr->bit_depth) : (256);
  if ((num_palette < 0) || (num_palette > ((int) max_palette_length)))
  {
    if (info_ptr->color_type == (2 | 1))
    {
      png_error(png_ptr, "Invalid palette length");
    }
    else
    {
      png_warning(png_ptr, "Invalid palette length");
      return;
    }
  }
  if (((num_palette > 0) && (palette == 0)) || (num_palette == 0))
  {
    png_error(png_ptr, "Invalid palette");
  }
  png_free_data(png_ptr, info_ptr, 0x1000U, 0);
  png_ptr->palette = png_calloc(png_ptr, 256 * (sizeof(png_color)));
  if (num_palette > 0)
  {
    memcpy(png_ptr->palette, palette, ((unsigned int) num_palette) * (sizeof(png_color)));
  }
  info_ptr->palette = png_ptr->palette;
  info_ptr->num_palette = (png_ptr->num_palette = (png_uint_16) num_palette);
  info_ptr->free_me |= 0x1000U;
  info_ptr->valid |= 0x0008U;
}


/*** DEPENDENCIES:
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
typedef unsigned int png_uint_32
----------------------------
png_voidp png_calloc(png_const_structrp png_ptr, png_alloc_size_t size)
{
  png_voidp ret;
  ret = png_malloc(png_ptr, size);
  if (ret != 0)
  {
    memset(ret, 0, size);
  }
  return ret;
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
typedef png_struct *png_structrp
----------------------------
typedef const png_color *png_const_colorp
----------------------------
typedef struct png_info_def png_info
----------------------------
typedef struct png_struct_def png_struct
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
typedef png_info *png_inforp
----------------------------
***/


void png_set_hIST(png_const_structrp png_ptr, png_inforp info_ptr, png_const_uint_16p hist)
{
  int i;
  (void) 0;
  if ((png_ptr == 0) || (info_ptr == 0))
  {
    return;
  }
  if ((info_ptr->num_palette == 0) || (info_ptr->num_palette > 256))
  {
    png_warning(png_ptr, "Invalid palette size, hIST allocation skipped");
    return;
  }
  png_free_data(png_ptr, info_ptr, 0x0008U, 0);
  info_ptr->hist = png_malloc_warn(png_ptr, 256 * (sizeof(png_uint_16)));
  if (info_ptr->hist == 0)
  {
    png_warning(png_ptr, "Insufficient memory for hIST chunk data");
    return;
  }
  for (i = 0; i < info_ptr->num_palette; i += 1)
  {
    info_ptr->hist[i] = hist[i];
  }

  info_ptr->free_me |= 0x0008U;
  info_ptr->valid |= 0x0040U;
}


/*** DEPENDENCIES:
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
typedef const png_uint_16 *png_const_uint_16p
----------------------------
png_voidp png_malloc_warn(png_const_structrp png_ptr, png_alloc_size_t size)
{
  if (png_ptr != 0)
  {
    png_voidp ret = png_malloc_base(png_ptr, size);
    if (ret != 0)
    {
      return ret;
    }
    png_warning(png_ptr, "Out of memory");
  }
  return 0;
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
typedef const png_struct *png_const_structrp
----------------------------
typedef struct png_info_def png_info
----------------------------
typedef png_info *png_inforp
----------------------------
***/


static png_byte check_location(png_const_structrp png_ptr, int location)
{
  location &= (0x01 | 0x02) | 0x08;
  if ((location == 0) && ((png_ptr->mode & 0x8000U) == 0))
  {
    png_app_warning(png_ptr, "png_set_unknown_chunks now expects a valid location");
    location = (png_byte) (png_ptr->mode & ((0x01 | 0x02) | 0x08));
  }
  if (location == 0)
  {
    png_error(png_ptr, "invalid location in png_set_unknown_chunks");
  }
  while (location != (location & (-location)))
  {
    location &= ~(location & (-location));
  }

  return (png_byte) location;
}


/*** DEPENDENCIES:
void png_app_warning(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr->flags & 0x200000U) != 0)
  {
    png_warning(png_ptr, error_message);
  }
  else
    png_error(png_ptr, error_message);
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
typedef const png_struct *png_const_structrp
----------------------------
***/


void png_set_unknown_chunks(png_const_structrp png_ptr, png_inforp info_ptr, png_const_unknown_chunkp unknowns, int num_unknowns)
{
  png_unknown_chunkp np;
  if ((((png_ptr == 0) || (info_ptr == 0)) || (num_unknowns <= 0)) || (unknowns == 0))
  {
    return;
  }
  np = png_realloc_array(png_ptr, info_ptr->unknown_chunks, info_ptr->unknown_chunks_num, num_unknowns, sizeof(*np));
  if (np == 0)
  {
    png_chunk_report(png_ptr, "too many unknown chunks", 1);
    return;
  }
  png_free(png_ptr, info_ptr->unknown_chunks);
  info_ptr->unknown_chunks = np;
  info_ptr->free_me |= 0x0200U;
  np += info_ptr->unknown_chunks_num;
  for (; num_unknowns > 0; num_unknowns -= 1, unknowns += 1)
  {
    memcpy(np->name, unknowns->name, sizeof(np->name));
    np->name[(sizeof(np->name)) - 1] = '\0';
    np->location = check_location(png_ptr, unknowns->location);
    if (unknowns->size == 0)
    {
      np->data = 0;
      np->size = 0;
    }
    else
    {
      np->data = png_malloc_base(png_ptr, unknowns->size);
      if (np->data == 0)
      {
        png_chunk_report(png_ptr, "unknown chunk: out of memory", 1);
        continue;
      }
      memcpy(np->data, unknowns->data, unknowns->size);
      np->size = unknowns->size;
    }
    np += 1;
    info_ptr->unknown_chunks_num += 1;
  }

}


/*** DEPENDENCIES:
png_voidp png_malloc_base(png_const_structrp png_ptr, png_alloc_size_t size)
{
  (void) png_ptr;
  if ((size > 0) && (size <= ((size_t) (-1))))
  {
    return malloc((size_t) size);
  }
  else
    return 0;
}


----------------------------
png_voidp png_realloc_array(png_const_structrp png_ptr, png_const_voidp old_array, int old_elements, int add_elements, size_t element_size)
{
  if ((((add_elements <= 0) || (element_size == 0)) || (old_elements < 0)) || ((old_array == 0) && (old_elements > 0)))
  {
    png_error(png_ptr, "internal error: array realloc");
  }
  if (add_elements <= (2147483647 - old_elements))
  {
    png_voidp new_array = png_malloc_array_checked(png_ptr, old_elements + add_elements, element_size);
    if (new_array != 0)
    {
      if (old_elements > 0)
      {
        memcpy(new_array, old_array, element_size * ((unsigned) old_elements));
      }
      memset(((char *) new_array) + (element_size * ((unsigned) old_elements)), 0, element_size * ((unsigned) add_elements));
      return new_array;
    }
  }
  return 0;
}


----------------------------
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
typedef png_unknown_chunk *png_unknown_chunkp
----------------------------
static png_byte check_location(png_const_structrp png_ptr, int location)
{
  location &= (0x01 | 0x02) | 0x08;
  if ((location == 0) && ((png_ptr->mode & 0x8000U) == 0))
  {
    png_app_warning(png_ptr, "png_set_unknown_chunks now expects a valid location");
    location = (png_byte) (png_ptr->mode & ((0x01 | 0x02) | 0x08));
  }
  if (location == 0)
  {
    png_error(png_ptr, "invalid location in png_set_unknown_chunks");
  }
  while (location != (location & (-location)))
  {
    location &= ~(location & (-location));
  }

  return (png_byte) location;
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
typedef struct png_info_def png_info
----------------------------
void png_chunk_report(png_const_structrp png_ptr, png_const_charp message, int error)
{
  if ((png_ptr->mode & 0x8000U) != 0)
  {
    if (error < 2)
    {
      png_chunk_warning(png_ptr, message);
    }
    else
      png_chunk_benign_error(png_ptr, message);
  }
  else
    if ((png_ptr->mode & 0x8000U) == 0)
  {
    if (error < 1)
    {
      png_app_warning(png_ptr, message);
    }
    else
      png_app_error(png_ptr, message);
  }
}


----------------------------
typedef const png_unknown_chunk *png_const_unknown_chunkp
----------------------------
typedef png_info *png_inforp
----------------------------
***/


void png_set_tRNS(png_structrp png_ptr, png_inforp info_ptr, png_const_bytep trans_alpha, int num_trans, png_const_color_16p trans_color)
{
  (void) 0;
  if ((png_ptr == 0) || (info_ptr == 0))
  {
    return;
  }
  if (trans_alpha != 0)
  {
    png_free_data(png_ptr, info_ptr, 0x2000U, 0);
    if ((num_trans > 0) && (num_trans <= 256))
    {
      info_ptr->trans_alpha = png_malloc(png_ptr, 256);
      memcpy(info_ptr->trans_alpha, trans_alpha, (size_t) num_trans);
      info_ptr->free_me |= 0x2000U;
      info_ptr->valid |= 0x0010U;
    }
    png_ptr->trans_alpha = info_ptr->trans_alpha;
  }
  if (trans_color != 0)
  {
    if (info_ptr->bit_depth < 16)
    {
      int sample_max = (1 << info_ptr->bit_depth) - 1;
      if (((info_ptr->color_type == 0) && (trans_color->gray > sample_max)) || ((info_ptr->color_type == 2) && (((trans_color->red > sample_max) || (trans_color->green > sample_max)) || (trans_color->blue > sample_max))))
      {
        png_warning(png_ptr, "tRNS chunk has out-of-range samples for bit_depth");
      }
    }
    info_ptr->trans_color = *trans_color;
    if (num_trans == 0)
    {
      num_trans = 1;
    }
  }
  info_ptr->num_trans = (png_uint_16) num_trans;
  if (num_trans != 0)
  {
    info_ptr->free_me |= 0x2000U;
    info_ptr->valid |= 0x0010U;
  }
}


/*** DEPENDENCIES:
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
typedef const png_byte *png_const_bytep
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
typedef const png_color_16 *png_const_color_16p
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef struct png_info_def png_info
----------------------------
typedef png_info *png_inforp
----------------------------
***/


void png_set_rows(png_const_structrp png_ptr, png_inforp info_ptr, png_bytepp row_pointers)
{
  (void) 0;
  if ((png_ptr == 0) || (info_ptr == 0))
  {
    return;
  }
  if ((info_ptr->row_pointers != 0) && (info_ptr->row_pointers != row_pointers))
  {
    png_free_data(png_ptr, info_ptr, 0x0040U, 0);
  }
  info_ptr->row_pointers = row_pointers;
  if (row_pointers != 0)
  {
    info_ptr->valid |= 0x8000U;
  }
}


/*** DEPENDENCIES:
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
typedef unsigned char png_byte
----------------------------
typedef png_byte **png_bytepp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
typedef struct png_info_def png_info
----------------------------
typedef png_byte *png_bytep
----------------------------
typedef png_info *png_inforp
----------------------------
***/


void png_set_unknown_chunk_location(png_const_structrp png_ptr, png_inforp info_ptr, int chunk, int location)
{
  if ((((png_ptr != 0) && (info_ptr != 0)) && (chunk >= 0)) && (chunk < info_ptr->unknown_chunks_num))
  {
    if ((location & ((0x01 | 0x02) | 0x08)) == 0)
    {
      png_app_error(png_ptr, "invalid unknown chunk location");
      if ((((unsigned int) location) & 0x04U) != 0)
      {
        location = 0x08;
      }
      else
        location = 0x01;
    }
    info_ptr->unknown_chunks[chunk].location = check_location(png_ptr, location);
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
typedef const png_struct *png_const_structrp
----------------------------
static png_byte check_location(png_const_structrp png_ptr, int location)
{
  location &= (0x01 | 0x02) | 0x08;
  if ((location == 0) && ((png_ptr->mode & 0x8000U) == 0))
  {
    png_app_warning(png_ptr, "png_set_unknown_chunks now expects a valid location");
    location = (png_byte) (png_ptr->mode & ((0x01 | 0x02) | 0x08));
  }
  if (location == 0)
  {
    png_error(png_ptr, "invalid location in png_set_unknown_chunks");
  }
  while (location != (location & (-location)))
  {
    location &= ~(location & (-location));
  }

  return (png_byte) location;
}


----------------------------
typedef struct png_info_def png_info
----------------------------
typedef png_info *png_inforp
----------------------------
***/


void png_set_invalid(png_const_structrp png_ptr, png_inforp info_ptr, int mask)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    info_ptr->valid &= (unsigned int) (~mask);
  }
}


/*** DEPENDENCIES:
typedef struct png_info_def png_info
----------------------------
typedef png_info *png_inforp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


void png_set_chunk_cache_max(png_structrp png_ptr, png_uint_32 user_chunk_cache_max)
{
  if (png_ptr != 0)
  {
    png_ptr->user_chunk_cache_max = user_chunk_cache_max;
  }
}


/*** DEPENDENCIES:
typedef unsigned int png_uint_32
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


void png_set_chunk_malloc_max(png_structrp png_ptr, png_alloc_size_t user_chunk_malloc_max)
{
  if (png_ptr != 0)
  {
    png_ptr->user_chunk_malloc_max = user_chunk_malloc_max;
  }
}


/*** DEPENDENCIES:
typedef size_t png_alloc_size_t
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


void png_set_compression_buffer_size(png_structrp png_ptr, size_t size)
{
  if (png_ptr == 0)
  {
    return;
  }
  if ((size == 0) || (size > ((png_uint_32) 0x7fffffffL)))
  {
    png_error(png_ptr, "invalid compression buffer size");
  }
  if ((png_ptr->mode & 0x8000U) != 0)
  {
    png_ptr->IDAT_read_size = (png_uint_32) size;
    return;
  }
  if ((png_ptr->mode & 0x8000U) == 0)
  {
    if (png_ptr->zowner != 0)
    {
      png_warning(png_ptr, "Compression buffer size cannot be changed because it is in use");
      return;
    }
    if (size > ((uInt) (-1)))
    {
      png_warning(png_ptr, "Compression buffer size limited to system maximum");
      size = (uInt) (-1);
    }
    if (size < 6)
    {
      png_warning(png_ptr, "Compression buffer size cannot be reduced below 6");
      return;
    }
    if (png_ptr->zbuffer_size != size)
    {
      png_free_buffer_list(png_ptr, &png_ptr->zbuffer_list);
      png_ptr->zbuffer_size = (uInt) size;
    }
  }
}


/*** DEPENDENCIES:
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
typedef struct png_struct_def png_struct
----------------------------
void png_free_buffer_list(png_structrp png_ptr, png_compression_bufferp *listp)
{
  png_compression_bufferp list = *listp;
  if (list != 0)
  {
    *listp = 0;
    do
    {
      png_compression_bufferp next = list->next;
      png_free(png_ptr, list);
      list = next;
    }
    while (list != 0);
  }
}


----------------------------
typedef png_struct *png_structrp
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


