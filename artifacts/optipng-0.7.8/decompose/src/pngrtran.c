static void png_init_palette_transformations(png_structrp png_ptr)
{
  int input_has_alpha = 0;
  int input_has_transparency = 0;
  if (png_ptr->num_trans > 0)
  {
    int i;
    for (i = 0; i < png_ptr->num_trans; i += 1)
    {
      if (png_ptr->trans_alpha[i] == 255)
      {
        continue;
      }
      else
        if (png_ptr->trans_alpha[i] == 0)
      {
        input_has_transparency = 1;
      }
      else
      {
        input_has_transparency = 1;
        input_has_alpha = 1;
        break;
      }
    }

  }
  if (input_has_alpha == 0)
  {
    png_ptr->transformations &= ~0x800000U;
    png_ptr->flags &= ~0x2000U;
    if (input_has_transparency == 0)
    {
      png_ptr->transformations &= ~(0x0080U | 0x0100U);
    }
  }
}


/*** DEPENDENCIES:
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


static void png_init_rgb_transformations(png_structrp png_ptr)
{
  int input_has_alpha = (png_ptr->color_type & 4) != 0;
  int input_has_transparency = png_ptr->num_trans > 0;
  if (input_has_alpha == 0)
  {
    if (input_has_transparency == 0)
    {
      png_ptr->transformations &= ~(0x0080U | 0x0100U);
    }
  }
}


/*** DEPENDENCIES:
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


void png_init_read_transformations(png_structrp png_ptr)
{
  (void) 0;
  if (png_ptr->color_type == (2 | 1))
  {
    png_init_palette_transformations(png_ptr);
  }
  else
    png_init_rgb_transformations(png_ptr);
}


/*** DEPENDENCIES:
static void png_init_rgb_transformations(png_structrp png_ptr)
{
  int input_has_alpha = (png_ptr->color_type & 4) != 0;
  int input_has_transparency = png_ptr->num_trans > 0;
  if (input_has_alpha == 0)
  {
    if (input_has_transparency == 0)
    {
      png_ptr->transformations &= ~(0x0080U | 0x0100U);
    }
  }
}


----------------------------
static void png_init_palette_transformations(png_structrp png_ptr)
{
  int input_has_alpha = 0;
  int input_has_transparency = 0;
  if (png_ptr->num_trans > 0)
  {
    int i;
    for (i = 0; i < png_ptr->num_trans; i += 1)
    {
      if (png_ptr->trans_alpha[i] == 255)
      {
        continue;
      }
      else
        if (png_ptr->trans_alpha[i] == 0)
      {
        input_has_transparency = 1;
      }
      else
      {
        input_has_transparency = 1;
        input_has_alpha = 1;
        break;
      }
    }

  }
  if (input_has_alpha == 0)
  {
    png_ptr->transformations &= ~0x800000U;
    png_ptr->flags &= ~0x2000U;
    if (input_has_transparency == 0)
    {
      png_ptr->transformations &= ~(0x0080U | 0x0100U);
    }
  }
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


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
void png_do_check_palette_indexes(png_structrp png_ptr, png_row_infop row_info)
{
  if ((png_ptr->num_palette < (1 << row_info->bit_depth)) && (png_ptr->num_palette > 0))
  {
    helper_png_do_check_palette_indexes_1(&png_ptr, row_info);
  }
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef png_row_info *png_row_infop
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


/*** DEPENDENCIES:
typedef struct png_info_def png_info
----------------------------
typedef png_info *png_inforp
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


void png_set_crc_action(png_structrp png_ptr, int crit_action, int ancil_action)
{
  (void) 0;
  if (png_ptr == 0)
  {
    return;
  }
  switch (crit_action)
  {
    case 5:
    {
      break;
    }

    case 3:
    {
      png_ptr->flags &= ~(0x0400U | 0x0800U);
      png_ptr->flags |= 0x0400U;
      break;
    }

    case 4:
    {
      png_ptr->flags &= ~(0x0400U | 0x0800U);
      png_ptr->flags |= 0x0400U | 0x0800U;
      break;
    }

    case 2:
    {
      png_warning(png_ptr, "Can't discard critical data on CRC error");
    }

    case 1:

    case 0:

    default:
    {
      png_ptr->flags &= ~(0x0400U | 0x0800U);
      break;
    }

  }

  switch (ancil_action)
  {
    case 5:
    {
      break;
    }

    case 3:
    {
      png_ptr->flags &= ~(0x0100U | 0x0200U);
      png_ptr->flags |= 0x0100U;
      break;
    }

    case 4:
    {
      png_ptr->flags &= ~(0x0100U | 0x0200U);
      png_ptr->flags |= 0x0100U | 0x0200U;
      break;
    }

    case 1:
    {
      png_ptr->flags &= ~(0x0100U | 0x0200U);
      png_ptr->flags |= 0x0200U;
      break;
    }

    case 2:

    case 0:

    default:
    {
      png_ptr->flags &= ~(0x0100U | 0x0200U);
      break;
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
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


static int png_rtran_ok(png_structrp png_ptr, int need_IHDR)
{
  if (png_ptr != 0)
  {
    if ((png_ptr->flags & 0x0040U) != 0)
    {
      png_app_error(png_ptr, "invalid after png_start_read_image or png_read_update_info");
    }
    else
      if (need_IHDR && ((png_ptr->mode & 0x01) == 0))
    {
      png_app_error(png_ptr, "invalid before the PNG header has been read");
    }
    else
    {
      png_ptr->flags |= 0x4000U;
      return 1;
    }
  }
  return 0;
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
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


