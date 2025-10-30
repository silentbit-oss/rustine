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


/*** DEPENDENCIES:
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


// hint:  ['png_ptr_ref is a mutable refrence to png_structrp', 'padding_ref is a mutable refrence to int', 'rp_ref is a mutable refrence to png_bytep']
void helper_helper_png_do_check_palette_indexes_1_1(png_structrp * const png_ptr_ref, int * const padding_ref, png_bytep * const rp_ref)
{
  png_structrp png_ptr = *png_ptr_ref;
  int padding = *padding_ref;
  png_bytep rp = *rp_ref;
  for (; rp > png_ptr->row_buf; rp -= 1)
  {
    int i = ((*rp) >> padding) & 0x03;
    if (i > png_ptr->num_palette_max)
    {
      png_ptr->num_palette_max = i;
    }
    i = (((*rp) >> padding) >> 2) & 0x03;
    if (i > png_ptr->num_palette_max)
    {
      png_ptr->num_palette_max = i;
    }
    i = (((*rp) >> padding) >> 4) & 0x03;
    if (i > png_ptr->num_palette_max)
    {
      png_ptr->num_palette_max = i;
    }
    i = (((*rp) >> padding) >> 6) & 0x03;
    if (i > png_ptr->num_palette_max)
    {
      png_ptr->num_palette_max = i;
    }
    padding = 0;
  }

  break;
  *png_ptr_ref = png_ptr;
  *padding_ref = padding;
  *rp_ref = rp;
}


/*** DEPENDENCIES:
typedef png_byte *png_bytep
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


// hint:  ['png_ptr_ref is a mutable refrence to png_structrp']
void helper_png_do_check_palette_indexes_1(png_structrp * const png_ptr_ref, png_row_infop row_info)
{
  png_structrp png_ptr = *png_ptr_ref;
  int padding = (8 - ((row_info->pixel_depth * (row_info->width % ((png_uint_32) 8))) % 8)) % 8;
  png_bytep rp = (png_ptr->row_buf + row_info->rowbytes) - 1;
  switch (row_info->bit_depth)
  {
    case 1:
    {
      for (; rp > png_ptr->row_buf; rp -= 1)
      {
        if (((*rp) >> padding) != 0)
        {
          png_ptr->num_palette_max = 1;
        }
        padding = 0;
      }

      break;
    }

    case 2:
    {
      helper_helper_png_do_check_palette_indexes_1_1(&png_ptr, &padding, &rp);
    }

    case 4:
    {
      for (; rp > png_ptr->row_buf; rp -= 1)
      {
        int i = ((*rp) >> padding) & 0x0f;
        if (i > png_ptr->num_palette_max)
        {
          png_ptr->num_palette_max = i;
        }
        i = (((*rp) >> padding) >> 4) & 0x0f;
        if (i > png_ptr->num_palette_max)
        {
          png_ptr->num_palette_max = i;
        }
        padding = 0;
      }

      break;
    }

    case 8:
    {
      for (; rp > png_ptr->row_buf; rp -= 1)
      {
        if ((*rp) > png_ptr->num_palette_max)
        {
          png_ptr->num_palette_max = (int) (*rp);
        }
      }

      break;
    }

    default:
    {
      break;
    }

  }

  *png_ptr_ref = png_ptr;
}


/*** DEPENDENCIES:
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
typedef unsigned char png_byte
----------------------------
void helper_helper_png_do_check_palette_indexes_1_1(png_structrp * const png_ptr_ref, int * const padding_ref, png_bytep * const rp_ref)
{
  png_structrp png_ptr = *png_ptr_ref;
  int padding = *padding_ref;
  png_bytep rp = *rp_ref;
  for (; rp > png_ptr->row_buf; rp -= 1)
  {
    int i = ((*rp) >> padding) & 0x03;
    if (i > png_ptr->num_palette_max)
    {
      png_ptr->num_palette_max = i;
    }
    i = (((*rp) >> padding) >> 2) & 0x03;
    if (i > png_ptr->num_palette_max)
    {
      png_ptr->num_palette_max = i;
    }
    i = (((*rp) >> padding) >> 4) & 0x03;
    if (i > png_ptr->num_palette_max)
    {
      png_ptr->num_palette_max = i;
    }
    i = (((*rp) >> padding) >> 6) & 0x03;
    if (i > png_ptr->num_palette_max)
    {
      png_ptr->num_palette_max = i;
    }
    padding = 0;
  }

  break;
  *png_ptr_ref = png_ptr;
  *padding_ref = padding;
  *rp_ref = rp;
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef png_row_info *png_row_infop
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


void png_do_check_palette_indexes(png_structrp png_ptr, png_row_infop row_info)
{
  if ((png_ptr->num_palette < (1 << row_info->bit_depth)) && (png_ptr->num_palette > 0))
  {
    helper_png_do_check_palette_indexes_1(&png_ptr, row_info);
  }
}


/*** DEPENDENCIES:
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
void helper_png_do_check_palette_indexes_1(png_structrp * const png_ptr_ref, png_row_infop row_info)
{
  png_structrp png_ptr = *png_ptr_ref;
  int padding = (8 - ((row_info->pixel_depth * (row_info->width % ((png_uint_32) 8))) % 8)) % 8;
  png_bytep rp = (png_ptr->row_buf + row_info->rowbytes) - 1;
  switch (row_info->bit_depth)
  {
    case 1:
    {
      for (; rp > png_ptr->row_buf; rp -= 1)
      {
        if (((*rp) >> padding) != 0)
        {
          png_ptr->num_palette_max = 1;
        }
        padding = 0;
      }

      break;
    }

    case 2:
    {
      helper_helper_png_do_check_palette_indexes_1_1(&png_ptr, &padding, &rp);
    }

    case 4:
    {
      for (; rp > png_ptr->row_buf; rp -= 1)
      {
        int i = ((*rp) >> padding) & 0x0f;
        if (i > png_ptr->num_palette_max)
        {
          png_ptr->num_palette_max = i;
        }
        i = (((*rp) >> padding) >> 4) & 0x0f;
        if (i > png_ptr->num_palette_max)
        {
          png_ptr->num_palette_max = i;
        }
        padding = 0;
      }

      break;
    }

    case 8:
    {
      for (; rp > png_ptr->row_buf; rp -= 1)
      {
        if ((*rp) > png_ptr->num_palette_max)
        {
          png_ptr->num_palette_max = (int) (*rp);
        }
      }

      break;
    }

    default:
    {
      break;
    }

  }

  *png_ptr_ref = png_ptr;
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef png_row_info *png_row_infop
----------------------------
***/


