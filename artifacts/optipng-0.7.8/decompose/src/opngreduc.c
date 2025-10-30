// hint:  ['src_sample_ptr_ref is a mutable refrence to png_bytep', 'dest_sample_ptr_ref is a mutable refrence to png_bytep', 'src_mask_ref is a mutable refrence to unsigned int', 'src_shift_ref is a mutable refrence to unsigned int', 'dest_shift_ref is a mutable refrence to unsigned int', 'sample_ref is a mutable refrence to unsigned int', 'dest_buf_ref is a mutable refrence to unsigned int']
void helper_helper_helper_opng_reduce_palette_bits_2_1_1(png_bytep * const src_sample_ptr_ref, png_bytep * const dest_sample_ptr_ref, unsigned int * const src_mask_ref, unsigned int * const src_shift_ref, unsigned int * const dest_shift_ref, unsigned int * const sample_ref, unsigned int * const dest_buf_ref, int src_bit_depth, int dest_bit_depth, unsigned int src_mask_init)
{
  png_bytep src_sample_ptr = *src_sample_ptr_ref;
  png_bytep dest_sample_ptr = *dest_sample_ptr_ref;
  unsigned int src_mask = *src_mask_ref;
  unsigned int src_shift = *src_shift_ref;
  unsigned int dest_shift = *dest_shift_ref;
  unsigned int sample = *sample_ref;
  unsigned int dest_buf = *dest_buf_ref;
  src_shift -= src_bit_depth;
  src_mask >>= src_bit_depth;
  sample = ((*src_sample_ptr) & src_mask) >> src_shift;
  dest_shift -= dest_bit_depth;
  if (dest_shift > 0)
  {
    dest_buf |= sample << dest_shift;
  }
  else
  {
    *dest_sample_ptr = (png_byte) (dest_buf | sample);
    dest_sample_ptr += 1;
    dest_shift = 8;
    dest_buf = 0;
  }
  if (src_shift == 0)
  {
    src_shift = 8;
    src_mask = src_mask_init;
    src_sample_ptr += 1;
  }
  *src_sample_ptr_ref = src_sample_ptr;
  *dest_sample_ptr_ref = dest_sample_ptr;
  *src_mask_ref = src_mask;
  *src_shift_ref = src_shift;
  *dest_shift_ref = dest_shift;
  *sample_ref = sample;
  *dest_buf_ref = dest_buf;
}


/*** DEPENDENCIES:
typedef png_byte *png_bytep
----------------------------
typedef unsigned char png_byte
----------------------------
***/


int opng_validate_image(png_structp png_ptr, png_infop info_ptr)
{
  (void) 0;
  if (png_get_bit_depth(png_ptr, info_ptr) == 0)
  {
    return 0;
  }
  if (png_get_color_type(png_ptr, info_ptr) & 1)
  {
    if (!png_get_valid(png_ptr, info_ptr, 0x0008U))
    {
      return 0;
    }
  }
  if (!png_get_valid(png_ptr, info_ptr, 0x8000U))
  {
    return 0;
  }
  return 1;
}


/*** DEPENDENCIES:
png_byte png_get_color_type(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    return info_ptr->color_type;
  }
  return 0;
}


----------------------------
png_byte png_get_bit_depth(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    return info_ptr->bit_depth;
  }
  return 0;
}


----------------------------
typedef png_struct *png_structp
----------------------------
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


----------------------------
typedef png_info *png_infop
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef struct png_info_def png_info
----------------------------
***/


static int opng_insert_palette_entry(png_colorp palette, int *num_palette, png_bytep trans_alpha, int *num_trans, int max_tuples, unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha, int *index)
{
  int low;
  int high;
  int mid;
  int cmp;
  int i;
  assert(((*num_palette) >= 0) && ((*num_palette) <= max_tuples));
  assert(((*num_trans) >= 0) && ((*num_trans) <= (*num_palette)));
  if (alpha < 255)
  {
    low = 0;
    high = (*num_trans) - 1;
    while (low <= high)
    {
      mid = (low + high) / 2;
      cmp = (((int) alpha) != ((int) trans_alpha[mid])) ? (((int) alpha) - ((int) trans_alpha[mid])) : ((((int) red) != palette[mid].red) ? (((int) red) - ((int) palette[mid].red)) : ((((int) green) != ((int) palette[mid].green)) ? (((int) green) - ((int) palette[mid].green)) : (((int) blue) - ((int) palette[mid].blue))));
      if (cmp < 0)
      {
        high = mid - 1;
      }
      else
        if (cmp > 0)
      {
        low = mid + 1;
      }
      else
      {
        *index = mid;
        return 0;
      }
    }

  }
  else
  {
    low = *num_trans;
    high = (*num_palette) - 1;
    while (low <= high)
    {
      mid = (low + high) / 2;
      cmp = (((int) red) != ((int) palette[mid].red)) ? (((int) red) - ((int) palette[mid].red)) : ((((int) green) != ((int) palette[mid].green)) ? (((int) green) - ((int) palette[mid].green)) : (((int) blue) - ((int) palette[mid].blue)));
      if (cmp < 0)
      {
        high = mid - 1;
      }
      else
        if (cmp > 0)
      {
        low = mid + 1;
      }
      else
      {
        *index = mid;
        return 0;
      }
    }

  }
  if (alpha > 255)
  {
    for (i = 0; i < (*num_trans); i += 1)
    {
      cmp = (((int) red) != ((int) palette[i].red)) ? (((int) red) - ((int) palette[i].red)) : ((((int) green) != ((int) palette[i].green)) ? (((int) green) - ((int) palette[i].green)) : (((int) blue) - ((int) palette[i].blue)));
      if (cmp == 0)
      {
        *index = i;
        return 0;
      }
    }

  }
  if ((*num_palette) >= max_tuples)
  {
    *num_palette = (*num_trans = (*index = -1));
    return -1;
  }
  assert((low >= 0) && (low <= (*num_palette)));
  for (i = *num_palette; i > low; i -= 1)
  {
    palette[i] = palette[i - 1];
  }

  palette[low].red = (png_byte) red;
  palette[low].green = (png_byte) green;
  palette[low].blue = (png_byte) blue;
  *num_palette += 1;
  if (alpha < 255)
  {
    assert(low <= (*num_trans));
    for (i = *num_trans; i > low; i -= 1)
    {
      trans_alpha[i] = trans_alpha[i - 1];
    }

    trans_alpha[low] = (png_byte) alpha;
    *num_trans += 1;
  }
  *index = low;
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
typedef png_byte *png_bytep
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_color *png_colorp
----------------------------
***/


// hint:  ['row_ptr_ref is a mutable refrence to png_bytepp', 'src_sample_ptr_ref is a mutable refrence to png_bytep', 'dest_sample_ptr_ref is a mutable refrence to png_bytep', 'dest_shift_ref is a mutable refrence to unsigned int', 'dest_buf_ref is a mutable refrence to unsigned int', 'i_ref is a mutable refrence to png_uint_32', 'j_ref is a mutable refrence to png_uint_32']
void helper_opng_reduce_palette_bits_1(png_bytepp * const row_ptr_ref, png_bytep * const src_sample_ptr_ref, png_bytep * const dest_sample_ptr_ref, unsigned int * const dest_shift_ref, unsigned int * const dest_buf_ref, png_uint_32 * const i_ref, png_uint_32 * const j_ref, png_uint_32 width, png_uint_32 height, int dest_bit_depth)
{
  png_bytepp row_ptr = *row_ptr_ref;
  png_bytep src_sample_ptr = *src_sample_ptr_ref;
  png_bytep dest_sample_ptr = *dest_sample_ptr_ref;
  unsigned int dest_shift = *dest_shift_ref;
  unsigned int dest_buf = *dest_buf_ref;
  png_uint_32 i = *i_ref;
  png_uint_32 j = *j_ref;
  for (i = 0; i < height; i += 1, row_ptr += 1)
  {
    src_sample_ptr = (dest_sample_ptr = *row_ptr);
    dest_shift = 8;
    dest_buf = 0;
    for (j = 0; j < width; j += 1)
    {
      dest_shift -= dest_bit_depth;
      if (dest_shift > 0)
      {
        dest_buf |= (*src_sample_ptr) << dest_shift;
      }
      else
      {
        *dest_sample_ptr = (png_byte) (dest_buf | (*src_sample_ptr));
        dest_sample_ptr += 1;
        dest_shift = 8;
        dest_buf = 0;
      }
      src_sample_ptr += 1;
    }

    if (dest_shift != 0)
    {
      *dest_sample_ptr = (png_byte) dest_buf;
    }
  }

  *row_ptr_ref = row_ptr;
  *src_sample_ptr_ref = src_sample_ptr;
  *dest_sample_ptr_ref = dest_sample_ptr;
  *dest_shift_ref = dest_shift;
  *dest_buf_ref = dest_buf;
  *i_ref = i;
  *j_ref = j;
}


/*** DEPENDENCIES:
typedef png_byte *png_bytep
----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_byte **png_bytepp
----------------------------
***/


// hint:  ['usage_map_ref is a mutable refrence to png_bytep', 'row_ptr_ref is a mutable refrence to png_bytepp', 'sample_ptr_ref is a mutable refrence to png_bytep', 'init_shift_ref is a mutable refrence to int', 'init_mask_ref is a mutable refrence to int', 'shift_ref is a mutable refrence to int', 'mask_ref is a mutable refrence to int', 'i_ref is a mutable refrence to png_uint_32', 'j_ref is a mutable refrence to png_uint_32']
void helper_opng_analyze_sample_usage_1(png_bytep * const usage_map_ref, png_bytepp * const row_ptr_ref, png_bytep * const sample_ptr_ref, int * const init_shift_ref, int * const init_mask_ref, int * const shift_ref, int * const mask_ref, png_uint_32 * const i_ref, png_uint_32 * const j_ref, png_uint_32 width, png_uint_32 height, int bit_depth)
{
  png_bytep usage_map = *usage_map_ref;
  png_bytepp row_ptr = *row_ptr_ref;
  png_bytep sample_ptr = *sample_ptr_ref;
  int init_shift = *init_shift_ref;
  int init_mask = *init_mask_ref;
  int shift = *shift_ref;
  int mask = *mask_ref;
  png_uint_32 i = *i_ref;
  png_uint_32 j = *j_ref;
  assert(bit_depth < 8);
  init_shift = 8 - bit_depth;
  init_mask = (1 << 8) - (1 << init_shift);
  for (i = 0; i < height; i += 1, row_ptr += 1)
  {
    for (j = 0, sample_ptr = *row_ptr; j < width; sample_ptr += 1)
    {
      mask = init_mask;
      shift = init_shift;
      do
      {
        usage_map[((*sample_ptr) & mask) >> shift] = 1;
        mask >>= bit_depth;
        shift -= bit_depth;
        j += 1;
      }
      while ((mask > 0) && (j < width));
    }

  }

  *usage_map_ref = usage_map;
  *row_ptr_ref = row_ptr;
  *sample_ptr_ref = sample_ptr;
  *init_shift_ref = init_shift;
  *init_mask_ref = init_mask;
  *shift_ref = shift;
  *mask_ref = mask;
  *i_ref = i;
  *j_ref = j;
}


/*** DEPENDENCIES:
typedef png_byte *png_bytep
----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_byte **png_bytepp
----------------------------
***/


// hint:  ['reductions_ref is a mutable refrence to png_uint_32', 'component_ptr_ref is a mutable refrence to png_bytep', 'j_ref is a mutable refrence to png_uint_32']
void helper_helper_opng_analyze_bits_1_1(png_uint_32 * const reductions_ref, png_bytep * const component_ptr_ref, png_uint_32 * const j_ref, png_bytepp row_ptr, png_uint_32 width, int sample_size, int offset_alpha)
{
  png_uint_32 reductions = *reductions_ref;
  png_bytep component_ptr = *component_ptr_ref;
  png_uint_32 j = *j_ref;
  if (reductions & 0x0004)
  {
    component_ptr = *row_ptr;
    for (j = 0; j < width; j += 1, component_ptr += sample_size)
    {
      if ((component_ptr[0] != component_ptr[1]) || (component_ptr[0] != component_ptr[2]))
      {
        reductions &= ~0x0004;
        break;
      }
    }

  }
  if (reductions & 0x0008)
  {
    component_ptr = (*row_ptr) + offset_alpha;
    for (j = 0; j < width; j += 1, component_ptr += sample_size)
    {
      if (component_ptr[0] != 255)
      {
        reductions &= ~0x0008;
        break;
      }
    }

  }
  *reductions_ref = reductions;
  *component_ptr_ref = component_ptr;
  *j_ref = j;
}


/*** DEPENDENCIES:
typedef png_byte *png_bytep
----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_byte **png_bytepp
----------------------------
***/


// hint:  ['reductions_ref is a mutable refrence to png_uint_32', 'component_ptr_ref is a mutable refrence to png_bytep', 'j_ref is a mutable refrence to png_uint_32']
void helper_helper_opng_analyze_bits_1_2(png_uint_32 * const reductions_ref, png_bytep * const component_ptr_ref, png_uint_32 * const j_ref, png_bytepp row_ptr, png_uint_32 width, int sample_size, int offset_alpha)
{
  png_uint_32 reductions = *reductions_ref;
  png_bytep component_ptr = *component_ptr_ref;
  png_uint_32 j = *j_ref;
  if (reductions & 0x0004)
  {
    component_ptr = *row_ptr;
    for (j = 0; j < width; j += 1, component_ptr += sample_size)
    {
      if ((((component_ptr[0] != component_ptr[2]) || (component_ptr[0] != component_ptr[4])) || (component_ptr[1] != component_ptr[3])) || (component_ptr[1] != component_ptr[5]))
      {
        reductions &= ~0x0004;
        break;
      }
    }

  }
  if (reductions & 0x0008)
  {
    component_ptr = (*row_ptr) + offset_alpha;
    for (j = 0; j < width; j += 1, component_ptr += sample_size)
    {
      if ((component_ptr[0] != 255) || (component_ptr[1] != 255))
      {
        reductions &= ~0x0008;
        break;
      }
    }

  }
  *reductions_ref = reductions;
  *component_ptr_ref = component_ptr;
  *j_ref = j;
}


/*** DEPENDENCIES:
typedef png_byte *png_bytep
----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_byte **png_bytepp
----------------------------
***/


// hint:  ['crt_trans_value_ref is a mutable refrence to png_byte', 'last_trans_value_ref is a mutable refrence to png_byte', 'gray_trans_ref is a mutable refrence to png_color_16', 'is_gray_ref is a mutable refrence to int', 'k_ref is a mutable refrence to int']
void helper_opng_reduce_palette_1(png_byte * const crt_trans_value_ref, png_byte * const last_trans_value_ref, png_color_16 * const gray_trans_ref, int * const is_gray_ref, int * const k_ref, png_colorp palette, png_bytep trans_alpha, int last_color_index, int last_trans_index, png_byte is_used[256])
{
  png_byte crt_trans_value = *crt_trans_value_ref;
  png_byte last_trans_value = *last_trans_value_ref;
  png_color_16 gray_trans = *gray_trans_ref;
  int is_gray = *is_gray_ref;
  int k = *k_ref;
  gray_trans.gray = palette[last_trans_index].red;
  last_trans_value = trans_alpha[last_trans_index];
  for (k = 0; k <= last_color_index; k += 1)
  {
    if (!is_used[k])
    {
      continue;
    }
    if (k <= last_trans_index)
    {
      crt_trans_value = trans_alpha[k];
      if ((crt_trans_value < 255) && (palette[k].red != gray_trans.gray))
      {
        is_gray = 0;
        break;
      }
    }
    else
      crt_trans_value = 255;
    if ((palette[k].red == gray_trans.gray) && (crt_trans_value != last_trans_value))
    {
      is_gray = 0;
      break;
    }
  }

  *crt_trans_value_ref = crt_trans_value;
  *last_trans_value_ref = last_trans_value;
  *gray_trans_ref = gray_trans;
  *is_gray_ref = is_gray;
  *k_ref = k;
}


/*** DEPENDENCIES:
typedef struct png_color_struct
{
  png_byte red;
  png_byte green;
  png_byte blue;
} png_color
----------------------------
typedef unsigned char png_byte
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
typedef png_byte *png_bytep
----------------------------
typedef png_color *png_colorp
----------------------------
***/


static void opng_realloc_PLTE(png_structp png_ptr, png_infop info_ptr, int num_palette)
{
  png_color buffer[256];
  png_colorp palette;
  int src_num_palette;
  png_bytep buffer_ptr;
  png_bytep trans_alpha;
  int num_trans;
  png_color_16p background;
  (void) 0;
  assert(num_palette > 0);
  src_num_palette = 0;
  png_get_PLTE(png_ptr, info_ptr, &palette, &src_num_palette);
  if (num_palette == src_num_palette)
  {
    return;
  }
  memcpy(buffer, palette, num_palette * (sizeof(png_color)));
  if (num_palette > src_num_palette)
  {
    memset(buffer + src_num_palette, 0, (num_palette - src_num_palette) * (sizeof(png_color)));
  }
  png_set_PLTE(png_ptr, info_ptr, buffer, num_palette);
  if (num_palette < src_num_palette)
  {
    if (png_get_tRNS(png_ptr, info_ptr, &trans_alpha, &num_trans, 0) && (num_trans > num_palette))
    {
      buffer_ptr = (png_bytep) ((png_voidp) buffer);
      png_warning(png_ptr, "Too many alpha values in tRNS");
      num_trans = num_palette;
      memcpy(buffer_ptr, trans_alpha, (size_t) num_trans);
      png_set_tRNS(png_ptr, info_ptr, buffer_ptr, num_trans, 0);
    }
    if (png_get_bKGD(png_ptr, info_ptr, &background) && (background->index >= num_palette))
    {
      png_warning(png_ptr, "Invalid color index in bKGD");
      png_set_invalid(png_ptr, info_ptr, 0x0020U);
    }
  }
}


/*** DEPENDENCIES:
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


----------------------------
void png_set_invalid(png_const_structrp png_ptr, png_inforp info_ptr, int mask)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    info_ptr->valid &= (unsigned int) (~mask);
  }
}


----------------------------
typedef png_struct *png_structp
----------------------------
typedef struct png_color_struct
{
  png_byte red;
  png_byte green;
  png_byte blue;
} png_color
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_color_16 *png_color_16p
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
typedef struct png_color_16_struct
{
  png_byte index;
  png_uint_16 red;
  png_uint_16 green;
  png_uint_16 blue;
  png_uint_16 gray;
} png_color_16
----------------------------
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


----------------------------
typedef png_info *png_infop
----------------------------
typedef struct png_struct_def png_struct
----------------------------
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


----------------------------
typedef struct png_info_def png_info
----------------------------
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


----------------------------
typedef png_byte *png_bytep
----------------------------
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


----------------------------
typedef png_color *png_colorp
----------------------------
***/


static void opng_analyze_sample_usage(png_structp png_ptr, png_infop info_ptr, png_bytep usage_map)
{
  png_bytepp row_ptr;
  png_bytep sample_ptr;
  png_uint_32 width;
  png_uint_32 height;
  int bit_depth;
  int init_shift;
  int init_mask;
  int shift;
  int mask;
  png_color_16p background;
  png_uint_32 i;
  png_uint_32 j;
  (void) 0;
  height = png_get_image_height(png_ptr, info_ptr);
  width = png_get_image_width(png_ptr, info_ptr);
  bit_depth = png_get_bit_depth(png_ptr, info_ptr);
  row_ptr = png_get_rows(png_ptr, info_ptr);
  memset(usage_map, 0, 256);
  if (bit_depth == 8)
  {
    for (i = 0; i < height; i += 1, row_ptr += 1)
    {
      for (j = 0, sample_ptr = *row_ptr; j < width; j += 1, sample_ptr += 1)
      {
        usage_map[*sample_ptr] = 1;
      }

    }

  }
  else
  {
    helper_opng_analyze_sample_usage_1(&usage_map, &row_ptr, &sample_ptr, &init_shift, &init_mask, &shift, &mask, &i, &j, width, height, bit_depth);
  }
  if (png_get_bKGD(png_ptr, info_ptr, &background))
  {
    usage_map[background->index] = 1;
  }
}


/*** DEPENDENCIES:
png_uint_32 png_get_image_width(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    return info_ptr->width;
  }
  return 0;
}


----------------------------
png_byte png_get_bit_depth(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    return info_ptr->bit_depth;
  }
  return 0;
}


----------------------------
typedef struct png_color_struct
{
  png_byte red;
  png_byte green;
  png_byte blue;
} png_color
----------------------------
typedef png_struct *png_structp
----------------------------
typedef unsigned char png_byte
----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef png_color_16 *png_color_16p
----------------------------
typedef png_byte **png_bytepp
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
png_uint_32 png_get_image_height(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    return info_ptr->height;
  }
  return 0;
}


----------------------------
void helper_opng_analyze_sample_usage_1(png_bytep * const usage_map_ref, png_bytepp * const row_ptr_ref, png_bytep * const sample_ptr_ref, int * const init_shift_ref, int * const init_mask_ref, int * const shift_ref, int * const mask_ref, png_uint_32 * const i_ref, png_uint_32 * const j_ref, png_uint_32 width, png_uint_32 height, int bit_depth)
{
  png_bytep usage_map = *usage_map_ref;
  png_bytepp row_ptr = *row_ptr_ref;
  png_bytep sample_ptr = *sample_ptr_ref;
  int init_shift = *init_shift_ref;
  int init_mask = *init_mask_ref;
  int shift = *shift_ref;
  int mask = *mask_ref;
  png_uint_32 i = *i_ref;
  png_uint_32 j = *j_ref;
  assert(bit_depth < 8);
  init_shift = 8 - bit_depth;
  init_mask = (1 << 8) - (1 << init_shift);
  for (i = 0; i < height; i += 1, row_ptr += 1)
  {
    for (j = 0, sample_ptr = *row_ptr; j < width; sample_ptr += 1)
    {
      mask = init_mask;
      shift = init_shift;
      do
      {
        usage_map[((*sample_ptr) & mask) >> shift] = 1;
        mask >>= bit_depth;
        shift -= bit_depth;
        j += 1;
      }
      while ((mask > 0) && (j < width));
    }

  }

  *usage_map_ref = usage_map;
  *row_ptr_ref = row_ptr;
  *sample_ptr_ref = sample_ptr;
  *init_shift_ref = init_shift;
  *init_mask_ref = init_mask;
  *shift_ref = shift;
  *mask_ref = mask;
  *i_ref = i;
  *j_ref = j;
}


----------------------------
typedef png_info *png_infop
----------------------------
typedef struct png_struct_def png_struct
----------------------------
png_bytepp png_get_rows(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    return info_ptr->row_pointers;
  }
  return 0;
}


----------------------------
typedef struct png_info_def png_info
----------------------------
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


----------------------------
typedef png_byte *png_bytep
----------------------------
***/


static void opng_realloc_tRNS(png_structp png_ptr, png_infop info_ptr, int num_trans)
{
  png_byte buffer[256];
  png_bytep trans_alpha;
  int src_num_trans;
  (void) 0;
  assert(num_trans > 0);
  src_num_trans = 0;
  png_get_tRNS(png_ptr, info_ptr, &trans_alpha, &src_num_trans, 0);
  if (num_trans == src_num_trans)
  {
    return;
  }
  memcpy(buffer, trans_alpha, (size_t) num_trans);
  if (num_trans > src_num_trans)
  {
    memset(buffer + src_num_trans, 0, num_trans - src_num_trans);
  }
  png_set_tRNS(png_ptr, info_ptr, buffer, num_trans, 0);
}


/*** DEPENDENCIES:
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


----------------------------
typedef png_struct *png_structp
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_info *png_infop
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef struct png_info_def png_info
----------------------------
typedef png_byte *png_bytep
----------------------------
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


----------------------------
***/


// hint:  ['src_sample_ptr_ref is a mutable refrence to png_bytep', 'dest_sample_ptr_ref is a mutable refrence to png_bytep', 'src_mask_ref is a mutable refrence to unsigned int', 'src_shift_ref is a mutable refrence to unsigned int', 'dest_shift_ref is a mutable refrence to unsigned int', 'sample_ref is a mutable refrence to unsigned int', 'dest_buf_ref is a mutable refrence to unsigned int', 'j_ref is a mutable refrence to png_uint_32']
void helper_helper_opng_reduce_palette_bits_2_1(png_bytep * const src_sample_ptr_ref, png_bytep * const dest_sample_ptr_ref, unsigned int * const src_mask_ref, unsigned int * const src_shift_ref, unsigned int * const dest_shift_ref, unsigned int * const sample_ref, unsigned int * const dest_buf_ref, png_uint_32 * const j_ref, png_uint_32 width, int src_bit_depth, int dest_bit_depth, png_bytepp row_ptr, unsigned int src_mask_init)
{
  png_bytep src_sample_ptr = *src_sample_ptr_ref;
  png_bytep dest_sample_ptr = *dest_sample_ptr_ref;
  unsigned int src_mask = *src_mask_ref;
  unsigned int src_shift = *src_shift_ref;
  unsigned int dest_shift = *dest_shift_ref;
  unsigned int sample = *sample_ref;
  unsigned int dest_buf = *dest_buf_ref;
  png_uint_32 j = *j_ref;
  src_sample_ptr = (dest_sample_ptr = *row_ptr);
  src_shift = (dest_shift = 8);
  src_mask = src_mask_init;
  dest_buf = 0;
  for (j = 0; j < width; j += 1)
  {
    helper_helper_helper_opng_reduce_palette_bits_2_1_1(&src_sample_ptr, &dest_sample_ptr, &src_mask, &src_shift, &dest_shift, &sample, &dest_buf, src_bit_depth, dest_bit_depth, src_mask_init);
  }

  if (dest_shift != 0)
  {
    *dest_sample_ptr = (png_byte) dest_buf;
  }
  *src_sample_ptr_ref = src_sample_ptr;
  *dest_sample_ptr_ref = dest_sample_ptr;
  *src_mask_ref = src_mask;
  *src_shift_ref = src_shift;
  *dest_shift_ref = dest_shift;
  *sample_ref = sample;
  *dest_buf_ref = dest_buf;
  *j_ref = j;
}


/*** DEPENDENCIES:
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_byte **png_bytepp
----------------------------
typedef png_byte *png_bytep
----------------------------
void helper_helper_helper_opng_reduce_palette_bits_2_1_1(png_bytep * const src_sample_ptr_ref, png_bytep * const dest_sample_ptr_ref, unsigned int * const src_mask_ref, unsigned int * const src_shift_ref, unsigned int * const dest_shift_ref, unsigned int * const sample_ref, unsigned int * const dest_buf_ref, int src_bit_depth, int dest_bit_depth, unsigned int src_mask_init)
{
  png_bytep src_sample_ptr = *src_sample_ptr_ref;
  png_bytep dest_sample_ptr = *dest_sample_ptr_ref;
  unsigned int src_mask = *src_mask_ref;
  unsigned int src_shift = *src_shift_ref;
  unsigned int dest_shift = *dest_shift_ref;
  unsigned int sample = *sample_ref;
  unsigned int dest_buf = *dest_buf_ref;
  src_shift -= src_bit_depth;
  src_mask >>= src_bit_depth;
  sample = ((*src_sample_ptr) & src_mask) >> src_shift;
  dest_shift -= dest_bit_depth;
  if (dest_shift > 0)
  {
    dest_buf |= sample << dest_shift;
  }
  else
  {
    *dest_sample_ptr = (png_byte) (dest_buf | sample);
    dest_sample_ptr += 1;
    dest_shift = 8;
    dest_buf = 0;
  }
  if (src_shift == 0)
  {
    src_shift = 8;
    src_mask = src_mask_init;
    src_sample_ptr += 1;
  }
  *src_sample_ptr_ref = src_sample_ptr;
  *dest_sample_ptr_ref = dest_sample_ptr;
  *src_mask_ref = src_mask;
  *src_shift_ref = src_shift;
  *dest_shift_ref = dest_shift;
  *sample_ref = sample;
  *dest_buf_ref = dest_buf;
}


----------------------------
***/


// hint:  ['row_ptr_ref is a mutable refrence to png_bytepp', 'src_sample_ptr_ref is a mutable refrence to png_bytep', 'dest_sample_ptr_ref is a mutable refrence to png_bytep', 'src_mask_init_ref is a mutable refrence to unsigned int', 'src_mask_ref is a mutable refrence to unsigned int', 'src_shift_ref is a mutable refrence to unsigned int', 'dest_shift_ref is a mutable refrence to unsigned int', 'sample_ref is a mutable refrence to unsigned int', 'dest_buf_ref is a mutable refrence to unsigned int', 'i_ref is a mutable refrence to png_uint_32', 'j_ref is a mutable refrence to png_uint_32']
void helper_opng_reduce_palette_bits_2(png_bytepp * const row_ptr_ref, png_bytep * const src_sample_ptr_ref, png_bytep * const dest_sample_ptr_ref, unsigned int * const src_mask_init_ref, unsigned int * const src_mask_ref, unsigned int * const src_shift_ref, unsigned int * const dest_shift_ref, unsigned int * const sample_ref, unsigned int * const dest_buf_ref, png_uint_32 * const i_ref, png_uint_32 * const j_ref, png_uint_32 width, png_uint_32 height, int src_bit_depth, int dest_bit_depth)
{
  png_bytepp row_ptr = *row_ptr_ref;
  png_bytep src_sample_ptr = *src_sample_ptr_ref;
  png_bytep dest_sample_ptr = *dest_sample_ptr_ref;
  unsigned int src_mask_init = *src_mask_init_ref;
  unsigned int src_mask = *src_mask_ref;
  unsigned int src_shift = *src_shift_ref;
  unsigned int dest_shift = *dest_shift_ref;
  unsigned int sample = *sample_ref;
  unsigned int dest_buf = *dest_buf_ref;
  png_uint_32 i = *i_ref;
  png_uint_32 j = *j_ref;
  src_mask_init = (1 << (8 + src_bit_depth)) - (1 << 8);
  for (i = 0; i < height; i += 1, row_ptr += 1)
  {
    helper_helper_opng_reduce_palette_bits_2_1(&src_sample_ptr, &dest_sample_ptr, &src_mask, &src_shift, &dest_shift, &sample, &dest_buf, &j, width, src_bit_depth, dest_bit_depth, row_ptr, src_mask_init);
  }

  *row_ptr_ref = row_ptr;
  *src_sample_ptr_ref = src_sample_ptr;
  *dest_sample_ptr_ref = dest_sample_ptr;
  *src_mask_init_ref = src_mask_init;
  *src_mask_ref = src_mask;
  *src_shift_ref = src_shift;
  *dest_shift_ref = dest_shift;
  *sample_ref = sample;
  *dest_buf_ref = dest_buf;
  *i_ref = i;
  *j_ref = j;
}


/*** DEPENDENCIES:
void helper_helper_opng_reduce_palette_bits_2_1(png_bytep * const src_sample_ptr_ref, png_bytep * const dest_sample_ptr_ref, unsigned int * const src_mask_ref, unsigned int * const src_shift_ref, unsigned int * const dest_shift_ref, unsigned int * const sample_ref, unsigned int * const dest_buf_ref, png_uint_32 * const j_ref, png_uint_32 width, int src_bit_depth, int dest_bit_depth, png_bytepp row_ptr, unsigned int src_mask_init)
{
  png_bytep src_sample_ptr = *src_sample_ptr_ref;
  png_bytep dest_sample_ptr = *dest_sample_ptr_ref;
  unsigned int src_mask = *src_mask_ref;
  unsigned int src_shift = *src_shift_ref;
  unsigned int dest_shift = *dest_shift_ref;
  unsigned int sample = *sample_ref;
  unsigned int dest_buf = *dest_buf_ref;
  png_uint_32 j = *j_ref;
  src_sample_ptr = (dest_sample_ptr = *row_ptr);
  src_shift = (dest_shift = 8);
  src_mask = src_mask_init;
  dest_buf = 0;
  for (j = 0; j < width; j += 1)
  {
    helper_helper_helper_opng_reduce_palette_bits_2_1_1(&src_sample_ptr, &dest_sample_ptr, &src_mask, &src_shift, &dest_shift, &sample, &dest_buf, src_bit_depth, dest_bit_depth, src_mask_init);
  }

  if (dest_shift != 0)
  {
    *dest_sample_ptr = (png_byte) dest_buf;
  }
  *src_sample_ptr_ref = src_sample_ptr;
  *dest_sample_ptr_ref = dest_sample_ptr;
  *src_mask_ref = src_mask;
  *src_shift_ref = src_shift;
  *dest_shift_ref = dest_shift;
  *sample_ref = sample;
  *dest_buf_ref = dest_buf;
  *j_ref = j;
}


----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_byte **png_bytepp
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


static png_uint_32 opng_reduce_palette_bits(png_structp png_ptr, png_infop info_ptr, png_uint_32 reductions)
{
  png_uint_32 result;
  png_bytepp row_ptr;
  png_bytep src_sample_ptr;
  png_bytep dest_sample_ptr;
  png_uint_32 width;
  png_uint_32 height;
  int color_type;
  int interlace_type;
  int compression_type;
  int filter_type;
  int src_bit_depth;
  int dest_bit_depth;
  unsigned int src_mask_init;
  unsigned int src_mask;
  unsigned int src_shift;
  unsigned int dest_shift;
  unsigned int sample;
  unsigned int dest_buf;
  png_colorp palette;
  int num_palette;
  png_uint_32 i;
  png_uint_32 j;
  (void) 0;
  if (!(reductions & 0x0002))
  {
    return 0x0000;
  }
  png_get_IHDR(png_ptr, info_ptr, &width, &height, &src_bit_depth, &color_type, &interlace_type, &compression_type, &filter_type);
  if (color_type != (2 | 1))
  {
    return 0x0000;
  }
  if (!png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette))
  {
    num_palette = 0;
  }
  result = 0x0000;
  if (num_palette > (1 << src_bit_depth))
  {
    png_warning(png_ptr, "Too many colors in PLTE");
    num_palette = 1 << src_bit_depth;
    opng_realloc_PLTE(png_ptr, info_ptr, num_palette);
    png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette);
    assert(num_palette == (1 << src_bit_depth));
    result |= 0x2000;
  }
  if (num_palette > 16)
  {
    return result;
  }
  else
    if (num_palette > 4)
  {
    dest_bit_depth = 4;
  }
  else
    if (num_palette > 2)
  {
    dest_bit_depth = 2;
  }
  else
  {
    assert(num_palette > 0);
    dest_bit_depth = 1;
  }
  if (src_bit_depth <= dest_bit_depth)
  {
    assert(src_bit_depth == dest_bit_depth);
    return result;
  }
  row_ptr = png_get_rows(png_ptr, info_ptr);
  if (src_bit_depth == 8)
  {
    helper_opng_reduce_palette_bits_1(&row_ptr, &src_sample_ptr, &dest_sample_ptr, &dest_shift, &dest_buf, &i, &j, width, height, dest_bit_depth);
  }
  else
  {
    helper_opng_reduce_palette_bits_2(&row_ptr, &src_sample_ptr, &dest_sample_ptr, &src_mask_init, &src_mask, &src_shift, &dest_shift, &sample, &dest_buf, &i, &j, width, height, src_bit_depth, dest_bit_depth);
  }
  png_set_IHDR(png_ptr, info_ptr, width, height, dest_bit_depth, color_type, interlace_type, compression_type, filter_type);
  result |= 0x0002;
  return result;
}


/*** DEPENDENCIES:
static void opng_realloc_PLTE(png_structp png_ptr, png_infop info_ptr, int num_palette)
{
  png_color buffer[256];
  png_colorp palette;
  int src_num_palette;
  png_bytep buffer_ptr;
  png_bytep trans_alpha;
  int num_trans;
  png_color_16p background;
  (void) 0;
  assert(num_palette > 0);
  src_num_palette = 0;
  png_get_PLTE(png_ptr, info_ptr, &palette, &src_num_palette);
  if (num_palette == src_num_palette)
  {
    return;
  }
  memcpy(buffer, palette, num_palette * (sizeof(png_color)));
  if (num_palette > src_num_palette)
  {
    memset(buffer + src_num_palette, 0, (num_palette - src_num_palette) * (sizeof(png_color)));
  }
  png_set_PLTE(png_ptr, info_ptr, buffer, num_palette);
  if (num_palette < src_num_palette)
  {
    if (png_get_tRNS(png_ptr, info_ptr, &trans_alpha, &num_trans, 0) && (num_trans > num_palette))
    {
      buffer_ptr = (png_bytep) ((png_voidp) buffer);
      png_warning(png_ptr, "Too many alpha values in tRNS");
      num_trans = num_palette;
      memcpy(buffer_ptr, trans_alpha, (size_t) num_trans);
      png_set_tRNS(png_ptr, info_ptr, buffer_ptr, num_trans, 0);
    }
    if (png_get_bKGD(png_ptr, info_ptr, &background) && (background->index >= num_palette))
    {
      png_warning(png_ptr, "Invalid color index in bKGD");
      png_set_invalid(png_ptr, info_ptr, 0x0020U);
    }
  }
}


----------------------------
typedef png_struct *png_structp
----------------------------
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
void helper_opng_reduce_palette_bits_1(png_bytepp * const row_ptr_ref, png_bytep * const src_sample_ptr_ref, png_bytep * const dest_sample_ptr_ref, unsigned int * const dest_shift_ref, unsigned int * const dest_buf_ref, png_uint_32 * const i_ref, png_uint_32 * const j_ref, png_uint_32 width, png_uint_32 height, int dest_bit_depth)
{
  png_bytepp row_ptr = *row_ptr_ref;
  png_bytep src_sample_ptr = *src_sample_ptr_ref;
  png_bytep dest_sample_ptr = *dest_sample_ptr_ref;
  unsigned int dest_shift = *dest_shift_ref;
  unsigned int dest_buf = *dest_buf_ref;
  png_uint_32 i = *i_ref;
  png_uint_32 j = *j_ref;
  for (i = 0; i < height; i += 1, row_ptr += 1)
  {
    src_sample_ptr = (dest_sample_ptr = *row_ptr);
    dest_shift = 8;
    dest_buf = 0;
    for (j = 0; j < width; j += 1)
    {
      dest_shift -= dest_bit_depth;
      if (dest_shift > 0)
      {
        dest_buf |= (*src_sample_ptr) << dest_shift;
      }
      else
      {
        *dest_sample_ptr = (png_byte) (dest_buf | (*src_sample_ptr));
        dest_sample_ptr += 1;
        dest_shift = 8;
        dest_buf = 0;
      }
      src_sample_ptr += 1;
    }

    if (dest_shift != 0)
    {
      *dest_sample_ptr = (png_byte) dest_buf;
    }
  }

  *row_ptr_ref = row_ptr;
  *src_sample_ptr_ref = src_sample_ptr;
  *dest_sample_ptr_ref = dest_sample_ptr;
  *dest_shift_ref = dest_shift;
  *dest_buf_ref = dest_buf;
  *i_ref = i;
  *j_ref = j;
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
typedef struct png_info_def png_info
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


----------------------------
png_bytepp png_get_rows(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    return info_ptr->row_pointers;
  }
  return 0;
}


----------------------------
void helper_opng_reduce_palette_bits_2(png_bytepp * const row_ptr_ref, png_bytep * const src_sample_ptr_ref, png_bytep * const dest_sample_ptr_ref, unsigned int * const src_mask_init_ref, unsigned int * const src_mask_ref, unsigned int * const src_shift_ref, unsigned int * const dest_shift_ref, unsigned int * const sample_ref, unsigned int * const dest_buf_ref, png_uint_32 * const i_ref, png_uint_32 * const j_ref, png_uint_32 width, png_uint_32 height, int src_bit_depth, int dest_bit_depth)
{
  png_bytepp row_ptr = *row_ptr_ref;
  png_bytep src_sample_ptr = *src_sample_ptr_ref;
  png_bytep dest_sample_ptr = *dest_sample_ptr_ref;
  unsigned int src_mask_init = *src_mask_init_ref;
  unsigned int src_mask = *src_mask_ref;
  unsigned int src_shift = *src_shift_ref;
  unsigned int dest_shift = *dest_shift_ref;
  unsigned int sample = *sample_ref;
  unsigned int dest_buf = *dest_buf_ref;
  png_uint_32 i = *i_ref;
  png_uint_32 j = *j_ref;
  src_mask_init = (1 << (8 + src_bit_depth)) - (1 << 8);
  for (i = 0; i < height; i += 1, row_ptr += 1)
  {
    helper_helper_opng_reduce_palette_bits_2_1(&src_sample_ptr, &dest_sample_ptr, &src_mask, &src_shift, &dest_shift, &sample, &dest_buf, &j, width, src_bit_depth, dest_bit_depth, row_ptr, src_mask_init);
  }

  *row_ptr_ref = row_ptr;
  *src_sample_ptr_ref = src_sample_ptr;
  *dest_sample_ptr_ref = dest_sample_ptr;
  *src_mask_init_ref = src_mask_init;
  *src_mask_ref = src_mask;
  *src_shift_ref = src_shift;
  *dest_shift_ref = dest_shift;
  *sample_ref = sample;
  *dest_buf_ref = dest_buf;
  *i_ref = i;
  *j_ref = j;
}


----------------------------
typedef png_byte *png_bytep
----------------------------
typedef png_color *png_colorp
----------------------------
***/


static png_uint_32 opng_reduce_palette(png_structp png_ptr, png_infop info_ptr, png_uint_32 reductions)
{
  png_uint_32 result;
  png_colorp palette;
  png_bytep trans_alpha;
  png_bytepp row_ptr;
  png_uint_32 width;
  png_uint_32 height;
  int bit_depth;
  int color_type;
  int interlace_type;
  int compression_type;
  int filter_type;
  int num_palette;
  int num_trans;
  int last_color_index;
  int last_trans_index;
  png_byte crt_trans_value;
  png_byte last_trans_value;
  png_byte is_used[256];
  png_color_16 gray_trans;
  int is_gray;
  png_color_16p background;
  png_uint_16p hist;
  png_color_8p sig_bits;
  png_uint_32 i;
  png_uint_32 j;
  int k;
  (void) 0;
  result = 0x0000;
  png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, &compression_type, &filter_type);
  row_ptr = png_get_rows(png_ptr, info_ptr);
  if (!png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette))
  {
    palette = 0;
    num_palette = 0;
  }
  if (!png_get_tRNS(png_ptr, info_ptr, &trans_alpha, &num_trans, 0))
  {
    trans_alpha = 0;
    num_trans = 0;
  }
  else
    assert((trans_alpha != 0) && (num_trans > 0));
  opng_analyze_sample_usage(png_ptr, info_ptr, is_used);
  is_gray = (reductions & 0x0080) && (bit_depth == 8);
  last_color_index = (last_trans_index = -1);
  for (k = 0; k < 256; k += 1)
  {
    if (!is_used[k])
    {
      continue;
    }
    last_color_index = k;
    if ((k < num_trans) && (trans_alpha[k] < 255))
    {
      last_trans_index = k;
    }
    if (is_gray)
    {
      if ((palette[k].red != palette[k].green) || (palette[k].red != palette[k].blue))
      {
        is_gray = 0;
      }
    }
  }

  assert(last_color_index >= 0);
  assert(last_color_index >= last_trans_index);
  if (last_color_index >= num_palette)
  {
    png_warning(png_ptr, "Too few colors in PLTE");
    opng_realloc_PLTE(png_ptr, info_ptr, last_color_index + 1);
    png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette);
    assert(num_palette == (last_color_index + 1));
    result |= 0x2000;
  }
  if (num_trans > num_palette)
  {
    png_warning(png_ptr, "Too many alpha values in tRNS");
    result |= 0x2000;
  }
  if (is_gray && (last_trans_index >= 0))
  {
    helper_opng_reduce_palette_1(&crt_trans_value, &last_trans_value, &gray_trans, &is_gray, &k, palette, trans_alpha, last_color_index, last_trans_index, is_used);
  }
  if ((num_trans > 0) && (last_trans_index < 0))
  {
    num_trans = 0;
    png_free_data(png_ptr, info_ptr, 0x2000U, -1);
    png_set_invalid(png_ptr, info_ptr, 0x0010U);
    result |= 0x0200;
  }
  if (reductions & 0x0200)
  {
    if (num_palette != (last_color_index + 1))
    {
      opng_realloc_PLTE(png_ptr, info_ptr, last_color_index + 1);
      png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette);
      assert(num_palette == (last_color_index + 1));
      result |= 0x0200;
    }
    if ((num_trans > 0) && (num_trans != (last_trans_index + 1)))
    {
      opng_realloc_tRNS(png_ptr, info_ptr, last_trans_index + 1);
      png_get_tRNS(png_ptr, info_ptr, &trans_alpha, &num_trans, 0);
      assert(num_trans == (last_trans_index + 1));
      result |= 0x0200;
    }
  }
  if (reductions & 0x0002)
  {
    result |= opng_reduce_palette_bits(png_ptr, info_ptr, reductions);
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);
  }
  if ((bit_depth < 8) || (!is_gray))
  {
    return result;
  }
  for (i = 0; i < height; i += 1)
  {
    for (j = 0; j < width; j += 1)
    {
      row_ptr[i][j] = palette[row_ptr[i][j]].red;
    }

  }

  if (num_trans > 0)
  {
    png_set_tRNS(png_ptr, info_ptr, 0, 0, &gray_trans);
  }
  if (png_get_bKGD(png_ptr, info_ptr, &background))
  {
    background->gray = palette[background->index].red;
  }
  if (png_get_hIST(png_ptr, info_ptr, &hist))
  {
    png_free_data(png_ptr, info_ptr, 0x0008U, -1);
    png_set_invalid(png_ptr, info_ptr, 0x0040U);
  }
  if (png_get_sBIT(png_ptr, info_ptr, &sig_bits))
  {
    png_byte max_sig_bits = sig_bits->red;
    if (max_sig_bits < sig_bits->green)
    {
      max_sig_bits = sig_bits->green;
    }
    if (max_sig_bits < sig_bits->blue)
    {
      max_sig_bits = sig_bits->blue;
    }
    sig_bits->gray = max_sig_bits;
  }
  png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, 0, interlace_type, compression_type, filter_type);
  png_free_data(png_ptr, info_ptr, 0x1000U, -1);
  png_set_invalid(png_ptr, info_ptr, 0x0008U);
  return 0x0080;
}


/*** DEPENDENCIES:
void helper_opng_reduce_palette_1(png_byte * const crt_trans_value_ref, png_byte * const last_trans_value_ref, png_color_16 * const gray_trans_ref, int * const is_gray_ref, int * const k_ref, png_colorp palette, png_bytep trans_alpha, int last_color_index, int last_trans_index, png_byte is_used[256])
{
  png_byte crt_trans_value = *crt_trans_value_ref;
  png_byte last_trans_value = *last_trans_value_ref;
  png_color_16 gray_trans = *gray_trans_ref;
  int is_gray = *is_gray_ref;
  int k = *k_ref;
  gray_trans.gray = palette[last_trans_index].red;
  last_trans_value = trans_alpha[last_trans_index];
  for (k = 0; k <= last_color_index; k += 1)
  {
    if (!is_used[k])
    {
      continue;
    }
    if (k <= last_trans_index)
    {
      crt_trans_value = trans_alpha[k];
      if ((crt_trans_value < 255) && (palette[k].red != gray_trans.gray))
      {
        is_gray = 0;
        break;
      }
    }
    else
      crt_trans_value = 255;
    if ((palette[k].red == gray_trans.gray) && (crt_trans_value != last_trans_value))
    {
      is_gray = 0;
      break;
    }
  }

  *crt_trans_value_ref = crt_trans_value;
  *last_trans_value_ref = last_trans_value;
  *gray_trans_ref = gray_trans;
  *is_gray_ref = is_gray;
  *k_ref = k;
}


----------------------------
static void opng_realloc_PLTE(png_structp png_ptr, png_infop info_ptr, int num_palette)
{
  png_color buffer[256];
  png_colorp palette;
  int src_num_palette;
  png_bytep buffer_ptr;
  png_bytep trans_alpha;
  int num_trans;
  png_color_16p background;
  (void) 0;
  assert(num_palette > 0);
  src_num_palette = 0;
  png_get_PLTE(png_ptr, info_ptr, &palette, &src_num_palette);
  if (num_palette == src_num_palette)
  {
    return;
  }
  memcpy(buffer, palette, num_palette * (sizeof(png_color)));
  if (num_palette > src_num_palette)
  {
    memset(buffer + src_num_palette, 0, (num_palette - src_num_palette) * (sizeof(png_color)));
  }
  png_set_PLTE(png_ptr, info_ptr, buffer, num_palette);
  if (num_palette < src_num_palette)
  {
    if (png_get_tRNS(png_ptr, info_ptr, &trans_alpha, &num_trans, 0) && (num_trans > num_palette))
    {
      buffer_ptr = (png_bytep) ((png_voidp) buffer);
      png_warning(png_ptr, "Too many alpha values in tRNS");
      num_trans = num_palette;
      memcpy(buffer_ptr, trans_alpha, (size_t) num_trans);
      png_set_tRNS(png_ptr, info_ptr, buffer_ptr, num_trans, 0);
    }
    if (png_get_bKGD(png_ptr, info_ptr, &background) && (background->index >= num_palette))
    {
      png_warning(png_ptr, "Invalid color index in bKGD");
      png_set_invalid(png_ptr, info_ptr, 0x0020U);
    }
  }
}


----------------------------
void png_set_invalid(png_const_structrp png_ptr, png_inforp info_ptr, int mask)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    info_ptr->valid &= (unsigned int) (~mask);
  }
}


----------------------------
typedef struct png_color_struct
{
  png_byte red;
  png_byte green;
  png_byte blue;
} png_color
----------------------------
typedef png_uint_16 *png_uint_16p
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
typedef png_color_8 *png_color_8p
----------------------------
typedef png_byte *png_bytep
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
typedef unsigned int png_uint_32
----------------------------
typedef png_color_16 *png_color_16p
----------------------------
typedef struct png_info_def png_info
----------------------------
typedef unsigned short png_uint_16
----------------------------
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


----------------------------
typedef unsigned char png_byte
----------------------------
static void opng_analyze_sample_usage(png_structp png_ptr, png_infop info_ptr, png_bytep usage_map)
{
  png_bytepp row_ptr;
  png_bytep sample_ptr;
  png_uint_32 width;
  png_uint_32 height;
  int bit_depth;
  int init_shift;
  int init_mask;
  int shift;
  int mask;
  png_color_16p background;
  png_uint_32 i;
  png_uint_32 j;
  (void) 0;
  height = png_get_image_height(png_ptr, info_ptr);
  width = png_get_image_width(png_ptr, info_ptr);
  bit_depth = png_get_bit_depth(png_ptr, info_ptr);
  row_ptr = png_get_rows(png_ptr, info_ptr);
  memset(usage_map, 0, 256);
  if (bit_depth == 8)
  {
    for (i = 0; i < height; i += 1, row_ptr += 1)
    {
      for (j = 0, sample_ptr = *row_ptr; j < width; j += 1, sample_ptr += 1)
      {
        usage_map[*sample_ptr] = 1;
      }

    }

  }
  else
  {
    helper_opng_analyze_sample_usage_1(&usage_map, &row_ptr, &sample_ptr, &init_shift, &init_mask, &shift, &mask, &i, &j, width, height, bit_depth);
  }
  if (png_get_bKGD(png_ptr, info_ptr, &background))
  {
    usage_map[background->index] = 1;
  }
}


----------------------------
png_bytepp png_get_rows(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    return info_ptr->row_pointers;
  }
  return 0;
}


----------------------------
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


----------------------------
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


----------------------------
typedef png_color *png_colorp
----------------------------
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


----------------------------
png_byte png_get_bit_depth(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    return info_ptr->bit_depth;
  }
  return 0;
}


----------------------------
static void opng_realloc_tRNS(png_structp png_ptr, png_infop info_ptr, int num_trans)
{
  png_byte buffer[256];
  png_bytep trans_alpha;
  int src_num_trans;
  (void) 0;
  assert(num_trans > 0);
  src_num_trans = 0;
  png_get_tRNS(png_ptr, info_ptr, &trans_alpha, &src_num_trans, 0);
  if (num_trans == src_num_trans)
  {
    return;
  }
  memcpy(buffer, trans_alpha, (size_t) num_trans);
  if (num_trans > src_num_trans)
  {
    memset(buffer + src_num_trans, 0, num_trans - src_num_trans);
  }
  png_set_tRNS(png_ptr, info_ptr, buffer, num_trans, 0);
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
static png_uint_32 opng_reduce_palette_bits(png_structp png_ptr, png_infop info_ptr, png_uint_32 reductions)
{
  png_uint_32 result;
  png_bytepp row_ptr;
  png_bytep src_sample_ptr;
  png_bytep dest_sample_ptr;
  png_uint_32 width;
  png_uint_32 height;
  int color_type;
  int interlace_type;
  int compression_type;
  int filter_type;
  int src_bit_depth;
  int dest_bit_depth;
  unsigned int src_mask_init;
  unsigned int src_mask;
  unsigned int src_shift;
  unsigned int dest_shift;
  unsigned int sample;
  unsigned int dest_buf;
  png_colorp palette;
  int num_palette;
  png_uint_32 i;
  png_uint_32 j;
  (void) 0;
  if (!(reductions & 0x0002))
  {
    return 0x0000;
  }
  png_get_IHDR(png_ptr, info_ptr, &width, &height, &src_bit_depth, &color_type, &interlace_type, &compression_type, &filter_type);
  if (color_type != (2 | 1))
  {
    return 0x0000;
  }
  if (!png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette))
  {
    num_palette = 0;
  }
  result = 0x0000;
  if (num_palette > (1 << src_bit_depth))
  {
    png_warning(png_ptr, "Too many colors in PLTE");
    num_palette = 1 << src_bit_depth;
    opng_realloc_PLTE(png_ptr, info_ptr, num_palette);
    png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette);
    assert(num_palette == (1 << src_bit_depth));
    result |= 0x2000;
  }
  if (num_palette > 16)
  {
    return result;
  }
  else
    if (num_palette > 4)
  {
    dest_bit_depth = 4;
  }
  else
    if (num_palette > 2)
  {
    dest_bit_depth = 2;
  }
  else
  {
    assert(num_palette > 0);
    dest_bit_depth = 1;
  }
  if (src_bit_depth <= dest_bit_depth)
  {
    assert(src_bit_depth == dest_bit_depth);
    return result;
  }
  row_ptr = png_get_rows(png_ptr, info_ptr);
  if (src_bit_depth == 8)
  {
    helper_opng_reduce_palette_bits_1(&row_ptr, &src_sample_ptr, &dest_sample_ptr, &dest_shift, &dest_buf, &i, &j, width, height, dest_bit_depth);
  }
  else
  {
    helper_opng_reduce_palette_bits_2(&row_ptr, &src_sample_ptr, &dest_sample_ptr, &src_mask_init, &src_mask, &src_shift, &dest_shift, &sample, &dest_buf, &i, &j, width, height, src_bit_depth, dest_bit_depth);
  }
  png_set_IHDR(png_ptr, info_ptr, width, height, dest_bit_depth, color_type, interlace_type, compression_type, filter_type);
  result |= 0x0002;
  return result;
}


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
typedef png_info *png_infop
----------------------------
typedef struct png_struct_def png_struct
----------------------------
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


----------------------------
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


----------------------------
***/


// hint:  ['alpha_row_ref is a mutable refrence to png_bytep', 'sample_ptr_ref is a mutable refrence to png_bytep', 'trans_red_ref is a mutable refrence to png_byte', 'trans_green_ref is a mutable refrence to png_byte', 'trans_blue_ref is a mutable refrence to png_byte', 'trans_gray_ref is a mutable refrence to png_byte', 'i_ref is a mutable refrence to png_uint_32']
void helper_opng_get_alpha_row_1(png_bytep * const alpha_row_ref, png_bytep * const sample_ptr_ref, png_byte * const trans_red_ref, png_byte * const trans_green_ref, png_byte * const trans_blue_ref, png_byte * const trans_gray_ref, png_uint_32 * const i_ref, png_color_16p trans_color, png_bytep row, png_uint_32 width, int color_type, int channels)
{
  png_bytep alpha_row = *alpha_row_ref;
  png_bytep sample_ptr = *sample_ptr_ref;
  png_byte trans_red = *trans_red_ref;
  png_byte trans_green = *trans_green_ref;
  png_byte trans_blue = *trans_blue_ref;
  png_byte trans_gray = *trans_gray_ref;
  png_uint_32 i = *i_ref;
  if (trans_color == 0)
  {
    memset(alpha_row, 255, (size_t) width);
    return;
  }
  if (color_type == 2)
  {
    assert(channels == 3);
    trans_red = (png_byte) trans_color->red;
    trans_green = (png_byte) trans_color->green;
    trans_blue = (png_byte) trans_color->blue;
    sample_ptr = row;
    for (i = 0; i < width; i += 1, sample_ptr += 3)
    {
      alpha_row[i] = (png_byte) ((((sample_ptr[0] == trans_red) && (sample_ptr[1] == trans_green)) && (sample_ptr[2] == trans_blue)) ? (0) : (255));
    }

  }
  else
  {
    assert(color_type == 0);
    assert(channels == 1);
    trans_gray = (png_byte) trans_color->gray;
    for (i = 0; i < width; i += 1)
    {
      alpha_row[i] = (png_byte) ((row[i] == trans_gray) ? (0) : (255));
    }

  }
  return;
  *alpha_row_ref = alpha_row;
  *sample_ptr_ref = sample_ptr;
  *trans_red_ref = trans_red;
  *trans_green_ref = trans_green;
  *trans_blue_ref = trans_blue;
  *trans_gray_ref = trans_gray;
  *i_ref = i;
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
typedef png_color_16 *png_color_16p
----------------------------
typedef unsigned char png_byte
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
typedef png_byte *png_bytep
----------------------------
***/


static void opng_get_alpha_row(png_row_infop row_info_ptr, png_color_16p trans_color, png_bytep row, png_bytep alpha_row)
{
  png_bytep sample_ptr;
  png_uint_32 width;
  int color_type;
  int bit_depth;
  int channels;
  png_byte trans_red;
  png_byte trans_green;
  png_byte trans_blue;
  png_byte trans_gray;
  png_uint_32 i;
  width = row_info_ptr->width;
  color_type = row_info_ptr->color_type;
  bit_depth = row_info_ptr->bit_depth;
  channels = row_info_ptr->channels;
  assert(!(color_type & 1));
  assert(bit_depth == 8);
  if (!(color_type & 4))
  {
    helper_opng_get_alpha_row_1(&alpha_row, &sample_ptr, &trans_red, &trans_green, &trans_blue, &trans_gray, &i, trans_color, row, width, color_type, channels);
  }
  assert(channels > 1);
  sample_ptr = row + (channels - 1);
  for (i = 0; i < width; i += 1, sample_ptr += channels, alpha_row += 1)
  {
    *alpha_row = *sample_ptr;
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
typedef struct png_color_16_struct
{
  png_byte index;
  png_uint_16 red;
  png_uint_16 green;
  png_uint_16 blue;
  png_uint_16 gray;
} png_color_16
----------------------------
void helper_opng_get_alpha_row_1(png_bytep * const alpha_row_ref, png_bytep * const sample_ptr_ref, png_byte * const trans_red_ref, png_byte * const trans_green_ref, png_byte * const trans_blue_ref, png_byte * const trans_gray_ref, png_uint_32 * const i_ref, png_color_16p trans_color, png_bytep row, png_uint_32 width, int color_type, int channels)
{
  png_bytep alpha_row = *alpha_row_ref;
  png_bytep sample_ptr = *sample_ptr_ref;
  png_byte trans_red = *trans_red_ref;
  png_byte trans_green = *trans_green_ref;
  png_byte trans_blue = *trans_blue_ref;
  png_byte trans_gray = *trans_gray_ref;
  png_uint_32 i = *i_ref;
  if (trans_color == 0)
  {
    memset(alpha_row, 255, (size_t) width);
    return;
  }
  if (color_type == 2)
  {
    assert(channels == 3);
    trans_red = (png_byte) trans_color->red;
    trans_green = (png_byte) trans_color->green;
    trans_blue = (png_byte) trans_color->blue;
    sample_ptr = row;
    for (i = 0; i < width; i += 1, sample_ptr += 3)
    {
      alpha_row[i] = (png_byte) ((((sample_ptr[0] == trans_red) && (sample_ptr[1] == trans_green)) && (sample_ptr[2] == trans_blue)) ? (0) : (255));
    }

  }
  else
  {
    assert(color_type == 0);
    assert(channels == 1);
    trans_gray = (png_byte) trans_color->gray;
    for (i = 0; i < width; i += 1)
    {
      alpha_row[i] = (png_byte) ((row[i] == trans_gray) ? (0) : (255));
    }

  }
  return;
  *alpha_row_ref = alpha_row;
  *sample_ptr_ref = sample_ptr;
  *trans_red_ref = trans_red;
  *trans_green_ref = trans_green;
  *trans_blue_ref = trans_blue;
  *trans_gray_ref = trans_gray;
  *i_ref = i;
}


----------------------------
typedef png_row_info *png_row_infop
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


// hint:  ['row_ptr_ref is a mutable refrence to png_bytepp', 'index_ref is a mutable refrence to int', 'red_ref is a mutable refrence to unsigned int', 'green_ref is a mutable refrence to unsigned int', 'blue_ref is a mutable refrence to unsigned int', 'alpha_ref is a mutable refrence to unsigned int', 'prev_red_ref is a mutable refrence to unsigned int', 'prev_green_ref is a mutable refrence to unsigned int', 'prev_blue_ref is a mutable refrence to unsigned int', 'prev_alpha_ref is a mutable refrence to unsigned int', 'j_ref is a mutable refrence to png_uint_32']
void helper_helper_helper_opng_reduce_to_palette_2_1_1(png_bytepp * const row_ptr_ref, int * const index_ref, unsigned int * const red_ref, unsigned int * const green_ref, unsigned int * const blue_ref, unsigned int * const alpha_ref, unsigned int * const prev_red_ref, unsigned int * const prev_green_ref, unsigned int * const prev_blue_ref, unsigned int * const prev_alpha_ref, png_uint_32 * const j_ref, png_bytep alpha_row, png_color palette[256], png_byte trans_alpha[256], int num_palette, int num_trans, png_bytep sample_ptr)
{
  png_bytepp row_ptr = *row_ptr_ref;
  int index = *index_ref;
  unsigned int red = *red_ref;
  unsigned int green = *green_ref;
  unsigned int blue = *blue_ref;
  unsigned int alpha = *alpha_ref;
  unsigned int prev_red = *prev_red_ref;
  unsigned int prev_green = *prev_green_ref;
  unsigned int prev_blue = *prev_blue_ref;
  unsigned int prev_alpha = *prev_alpha_ref;
  png_uint_32 j = *j_ref;
  red = sample_ptr[0];
  green = sample_ptr[1];
  blue = sample_ptr[2];
  alpha = alpha_row[j];
  if ((((red != prev_red) || (green != prev_green)) || (blue != prev_blue)) || (alpha != prev_alpha))
  {
    prev_red = red;
    prev_green = green;
    prev_blue = blue;
    prev_alpha = alpha;
    if (opng_insert_palette_entry(palette, &num_palette, trans_alpha, &num_trans, 256, red, green, blue, alpha, &index) != 0)
    {
      index = -1;
    }
  }
  assert(index >= 0);
  (*row_ptr)[j] = (png_byte) index;
  *row_ptr_ref = row_ptr;
  *index_ref = index;
  *red_ref = red;
  *green_ref = green;
  *blue_ref = blue;
  *alpha_ref = alpha;
  *prev_red_ref = prev_red;
  *prev_green_ref = prev_green;
  *prev_blue_ref = prev_blue;
  *prev_alpha_ref = prev_alpha;
  *j_ref = j;
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
typedef png_byte **png_bytepp
----------------------------
typedef png_byte *png_bytep
----------------------------
static int opng_insert_palette_entry(png_colorp palette, int *num_palette, png_bytep trans_alpha, int *num_trans, int max_tuples, unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha, int *index)
{
  int low;
  int high;
  int mid;
  int cmp;
  int i;
  assert(((*num_palette) >= 0) && ((*num_palette) <= max_tuples));
  assert(((*num_trans) >= 0) && ((*num_trans) <= (*num_palette)));
  if (alpha < 255)
  {
    low = 0;
    high = (*num_trans) - 1;
    while (low <= high)
    {
      mid = (low + high) / 2;
      cmp = (((int) alpha) != ((int) trans_alpha[mid])) ? (((int) alpha) - ((int) trans_alpha[mid])) : ((((int) red) != palette[mid].red) ? (((int) red) - ((int) palette[mid].red)) : ((((int) green) != ((int) palette[mid].green)) ? (((int) green) - ((int) palette[mid].green)) : (((int) blue) - ((int) palette[mid].blue))));
      if (cmp < 0)
      {
        high = mid - 1;
      }
      else
        if (cmp > 0)
      {
        low = mid + 1;
      }
      else
      {
        *index = mid;
        return 0;
      }
    }

  }
  else
  {
    low = *num_trans;
    high = (*num_palette) - 1;
    while (low <= high)
    {
      mid = (low + high) / 2;
      cmp = (((int) red) != ((int) palette[mid].red)) ? (((int) red) - ((int) palette[mid].red)) : ((((int) green) != ((int) palette[mid].green)) ? (((int) green) - ((int) palette[mid].green)) : (((int) blue) - ((int) palette[mid].blue)));
      if (cmp < 0)
      {
        high = mid - 1;
      }
      else
        if (cmp > 0)
      {
        low = mid + 1;
      }
      else
      {
        *index = mid;
        return 0;
      }
    }

  }
  if (alpha > 255)
  {
    for (i = 0; i < (*num_trans); i += 1)
    {
      cmp = (((int) red) != ((int) palette[i].red)) ? (((int) red) - ((int) palette[i].red)) : ((((int) green) != ((int) palette[i].green)) ? (((int) green) - ((int) palette[i].green)) : (((int) blue) - ((int) palette[i].blue)));
      if (cmp == 0)
      {
        *index = i;
        return 0;
      }
    }

  }
  if ((*num_palette) >= max_tuples)
  {
    *num_palette = (*num_trans = (*index = -1));
    return -1;
  }
  assert((low >= 0) && (low <= (*num_palette)));
  for (i = *num_palette; i > low; i -= 1)
  {
    palette[i] = palette[i - 1];
  }

  palette[low].red = (png_byte) red;
  palette[low].green = (png_byte) green;
  palette[low].blue = (png_byte) blue;
  *num_palette += 1;
  if (alpha < 255)
  {
    assert(low <= (*num_trans));
    for (i = *num_trans; i > low; i -= 1)
    {
      trans_alpha[i] = trans_alpha[i - 1];
    }

    trans_alpha[low] = (png_byte) alpha;
    *num_trans += 1;
  }
  *index = low;
  return 1;
}


----------------------------
***/


// hint:  ['row_ptr_ref is a mutable refrence to png_bytepp', 'sample_ptr_ref is a mutable refrence to png_bytep', 'index_ref is a mutable refrence to int', 'red_ref is a mutable refrence to unsigned int', 'green_ref is a mutable refrence to unsigned int', 'blue_ref is a mutable refrence to unsigned int', 'alpha_ref is a mutable refrence to unsigned int', 'prev_red_ref is a mutable refrence to unsigned int', 'prev_green_ref is a mutable refrence to unsigned int', 'prev_blue_ref is a mutable refrence to unsigned int', 'prev_alpha_ref is a mutable refrence to unsigned int', 'j_ref is a mutable refrence to png_uint_32']
void helper_helper_opng_reduce_to_palette_2_1(png_bytepp * const row_ptr_ref, png_bytep * const sample_ptr_ref, int * const index_ref, unsigned int * const red_ref, unsigned int * const green_ref, unsigned int * const blue_ref, unsigned int * const alpha_ref, unsigned int * const prev_red_ref, unsigned int * const prev_green_ref, unsigned int * const prev_blue_ref, unsigned int * const prev_alpha_ref, png_uint_32 * const j_ref, png_bytep alpha_row, png_uint_32 width, int channels, png_color palette[256], png_byte trans_alpha[256], int num_palette, int num_trans)
{
  png_bytepp row_ptr = *row_ptr_ref;
  png_bytep sample_ptr = *sample_ptr_ref;
  int index = *index_ref;
  unsigned int red = *red_ref;
  unsigned int green = *green_ref;
  unsigned int blue = *blue_ref;
  unsigned int alpha = *alpha_ref;
  unsigned int prev_red = *prev_red_ref;
  unsigned int prev_green = *prev_green_ref;
  unsigned int prev_blue = *prev_blue_ref;
  unsigned int prev_alpha = *prev_alpha_ref;
  png_uint_32 j = *j_ref;
  for (j = 0; j < width; j += 1, sample_ptr += channels)
  {
    helper_helper_helper_opng_reduce_to_palette_2_1_1(&row_ptr, &index, &red, &green, &blue, &alpha, &prev_red, &prev_green, &prev_blue, &prev_alpha, &j, alpha_row, palette, trans_alpha, num_palette, num_trans, sample_ptr);
  }

  *row_ptr_ref = row_ptr;
  *sample_ptr_ref = sample_ptr;
  *index_ref = index;
  *red_ref = red;
  *green_ref = green;
  *blue_ref = blue;
  *alpha_ref = alpha;
  *prev_red_ref = prev_red;
  *prev_green_ref = prev_green;
  *prev_blue_ref = prev_blue;
  *prev_alpha_ref = prev_alpha;
  *j_ref = j;
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
typedef png_byte **png_bytepp
----------------------------
void helper_helper_helper_opng_reduce_to_palette_2_1_1(png_bytepp * const row_ptr_ref, int * const index_ref, unsigned int * const red_ref, unsigned int * const green_ref, unsigned int * const blue_ref, unsigned int * const alpha_ref, unsigned int * const prev_red_ref, unsigned int * const prev_green_ref, unsigned int * const prev_blue_ref, unsigned int * const prev_alpha_ref, png_uint_32 * const j_ref, png_bytep alpha_row, png_color palette[256], png_byte trans_alpha[256], int num_palette, int num_trans, png_bytep sample_ptr)
{
  png_bytepp row_ptr = *row_ptr_ref;
  int index = *index_ref;
  unsigned int red = *red_ref;
  unsigned int green = *green_ref;
  unsigned int blue = *blue_ref;
  unsigned int alpha = *alpha_ref;
  unsigned int prev_red = *prev_red_ref;
  unsigned int prev_green = *prev_green_ref;
  unsigned int prev_blue = *prev_blue_ref;
  unsigned int prev_alpha = *prev_alpha_ref;
  png_uint_32 j = *j_ref;
  red = sample_ptr[0];
  green = sample_ptr[1];
  blue = sample_ptr[2];
  alpha = alpha_row[j];
  if ((((red != prev_red) || (green != prev_green)) || (blue != prev_blue)) || (alpha != prev_alpha))
  {
    prev_red = red;
    prev_green = green;
    prev_blue = blue;
    prev_alpha = alpha;
    if (opng_insert_palette_entry(palette, &num_palette, trans_alpha, &num_trans, 256, red, green, blue, alpha, &index) != 0)
    {
      index = -1;
    }
  }
  assert(index >= 0);
  (*row_ptr)[j] = (png_byte) index;
  *row_ptr_ref = row_ptr;
  *index_ref = index;
  *red_ref = red;
  *green_ref = green;
  *blue_ref = blue;
  *alpha_ref = alpha;
  *prev_red_ref = prev_red;
  *prev_green_ref = prev_green;
  *prev_blue_ref = prev_blue;
  *prev_alpha_ref = prev_alpha;
  *j_ref = j;
}


----------------------------
typedef png_byte *png_bytep
----------------------------
***/


// hint:  ['row_ptr_ref is a mutable refrence to png_bytepp', 'sample_ptr_ref is a mutable refrence to png_bytep', 'index_ref is a mutable refrence to int', 'gray_ref is a mutable refrence to unsigned int', 'red_ref is a mutable refrence to unsigned int', 'green_ref is a mutable refrence to unsigned int', 'blue_ref is a mutable refrence to unsigned int', 'alpha_ref is a mutable refrence to unsigned int', 'prev_gray_ref is a mutable refrence to unsigned int', 'prev_red_ref is a mutable refrence to unsigned int', 'prev_green_ref is a mutable refrence to unsigned int', 'prev_blue_ref is a mutable refrence to unsigned int', 'prev_alpha_ref is a mutable refrence to unsigned int', 'j_ref is a mutable refrence to png_uint_32']
void helper_opng_reduce_to_palette_2(png_bytepp * const row_ptr_ref, png_bytep * const sample_ptr_ref, int * const index_ref, unsigned int * const gray_ref, unsigned int * const red_ref, unsigned int * const green_ref, unsigned int * const blue_ref, unsigned int * const alpha_ref, unsigned int * const prev_gray_ref, unsigned int * const prev_red_ref, unsigned int * const prev_green_ref, unsigned int * const prev_blue_ref, unsigned int * const prev_alpha_ref, png_uint_32 * const j_ref, png_row_info row_info, png_bytep alpha_row, png_uint_32 width, int color_type, int channels, png_color palette[256], png_byte trans_alpha[256], png_color_16p trans_color, int num_palette, int num_trans)
{
  png_bytepp row_ptr = *row_ptr_ref;
  png_bytep sample_ptr = *sample_ptr_ref;
  int index = *index_ref;
  unsigned int gray = *gray_ref;
  unsigned int red = *red_ref;
  unsigned int green = *green_ref;
  unsigned int blue = *blue_ref;
  unsigned int alpha = *alpha_ref;
  unsigned int prev_gray = *prev_gray_ref;
  unsigned int prev_red = *prev_red_ref;
  unsigned int prev_green = *prev_green_ref;
  unsigned int prev_blue = *prev_blue_ref;
  unsigned int prev_alpha = *prev_alpha_ref;
  png_uint_32 j = *j_ref;
  sample_ptr = *row_ptr;
  opng_get_alpha_row(&row_info, trans_color, *row_ptr, alpha_row);
  if (color_type & 2)
  {
    helper_helper_opng_reduce_to_palette_2_1(&row_ptr, &sample_ptr, &index, &red, &green, &blue, &alpha, &prev_red, &prev_green, &prev_blue, &prev_alpha, &j, alpha_row, width, channels, palette, trans_alpha, num_palette, num_trans);
  }
  else
  {
    for (j = 0; j < width; j += 1, sample_ptr += channels)
    {
      gray = sample_ptr[0];
      alpha = alpha_row[j];
      if ((gray != prev_gray) || (alpha != prev_alpha))
      {
        prev_gray = gray;
        prev_alpha = alpha;
        if (opng_insert_palette_entry(palette, &num_palette, trans_alpha, &num_trans, 256, gray, gray, gray, alpha, &index) != 0)
        {
          index = -1;
        }
      }
      assert(index >= 0);
      (*row_ptr)[j] = (png_byte) index;
    }

  }
  *row_ptr_ref = row_ptr;
  *sample_ptr_ref = sample_ptr;
  *index_ref = index;
  *gray_ref = gray;
  *red_ref = red;
  *green_ref = green;
  *blue_ref = blue;
  *alpha_ref = alpha;
  *prev_gray_ref = prev_gray;
  *prev_red_ref = prev_red;
  *prev_green_ref = prev_green;
  *prev_blue_ref = prev_blue;
  *prev_alpha_ref = prev_alpha;
  *j_ref = j;
}


/*** DEPENDENCIES:
static int opng_insert_palette_entry(png_colorp palette, int *num_palette, png_bytep trans_alpha, int *num_trans, int max_tuples, unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha, int *index)
{
  int low;
  int high;
  int mid;
  int cmp;
  int i;
  assert(((*num_palette) >= 0) && ((*num_palette) <= max_tuples));
  assert(((*num_trans) >= 0) && ((*num_trans) <= (*num_palette)));
  if (alpha < 255)
  {
    low = 0;
    high = (*num_trans) - 1;
    while (low <= high)
    {
      mid = (low + high) / 2;
      cmp = (((int) alpha) != ((int) trans_alpha[mid])) ? (((int) alpha) - ((int) trans_alpha[mid])) : ((((int) red) != palette[mid].red) ? (((int) red) - ((int) palette[mid].red)) : ((((int) green) != ((int) palette[mid].green)) ? (((int) green) - ((int) palette[mid].green)) : (((int) blue) - ((int) palette[mid].blue))));
      if (cmp < 0)
      {
        high = mid - 1;
      }
      else
        if (cmp > 0)
      {
        low = mid + 1;
      }
      else
      {
        *index = mid;
        return 0;
      }
    }

  }
  else
  {
    low = *num_trans;
    high = (*num_palette) - 1;
    while (low <= high)
    {
      mid = (low + high) / 2;
      cmp = (((int) red) != ((int) palette[mid].red)) ? (((int) red) - ((int) palette[mid].red)) : ((((int) green) != ((int) palette[mid].green)) ? (((int) green) - ((int) palette[mid].green)) : (((int) blue) - ((int) palette[mid].blue)));
      if (cmp < 0)
      {
        high = mid - 1;
      }
      else
        if (cmp > 0)
      {
        low = mid + 1;
      }
      else
      {
        *index = mid;
        return 0;
      }
    }

  }
  if (alpha > 255)
  {
    for (i = 0; i < (*num_trans); i += 1)
    {
      cmp = (((int) red) != ((int) palette[i].red)) ? (((int) red) - ((int) palette[i].red)) : ((((int) green) != ((int) palette[i].green)) ? (((int) green) - ((int) palette[i].green)) : (((int) blue) - ((int) palette[i].blue)));
      if (cmp == 0)
      {
        *index = i;
        return 0;
      }
    }

  }
  if ((*num_palette) >= max_tuples)
  {
    *num_palette = (*num_trans = (*index = -1));
    return -1;
  }
  assert((low >= 0) && (low <= (*num_palette)));
  for (i = *num_palette; i > low; i -= 1)
  {
    palette[i] = palette[i - 1];
  }

  palette[low].red = (png_byte) red;
  palette[low].green = (png_byte) green;
  palette[low].blue = (png_byte) blue;
  *num_palette += 1;
  if (alpha < 255)
  {
    assert(low <= (*num_trans));
    for (i = *num_trans; i > low; i -= 1)
    {
      trans_alpha[i] = trans_alpha[i - 1];
    }

    trans_alpha[low] = (png_byte) alpha;
    *num_trans += 1;
  }
  *index = low;
  return 1;
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
typedef struct png_color_struct
{
  png_byte red;
  png_byte green;
  png_byte blue;
} png_color
----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef png_color_16 *png_color_16p
----------------------------
typedef unsigned char png_byte
----------------------------
static void opng_get_alpha_row(png_row_infop row_info_ptr, png_color_16p trans_color, png_bytep row, png_bytep alpha_row)
{
  png_bytep sample_ptr;
  png_uint_32 width;
  int color_type;
  int bit_depth;
  int channels;
  png_byte trans_red;
  png_byte trans_green;
  png_byte trans_blue;
  png_byte trans_gray;
  png_uint_32 i;
  width = row_info_ptr->width;
  color_type = row_info_ptr->color_type;
  bit_depth = row_info_ptr->bit_depth;
  channels = row_info_ptr->channels;
  assert(!(color_type & 1));
  assert(bit_depth == 8);
  if (!(color_type & 4))
  {
    helper_opng_get_alpha_row_1(&alpha_row, &sample_ptr, &trans_red, &trans_green, &trans_blue, &trans_gray, &i, trans_color, row, width, color_type, channels);
  }
  assert(channels > 1);
  sample_ptr = row + (channels - 1);
  for (i = 0; i < width; i += 1, sample_ptr += channels, alpha_row += 1)
  {
    *alpha_row = *sample_ptr;
  }

}


----------------------------
typedef png_byte **png_bytepp
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
typedef png_byte *png_bytep
----------------------------
void helper_helper_opng_reduce_to_palette_2_1(png_bytepp * const row_ptr_ref, png_bytep * const sample_ptr_ref, int * const index_ref, unsigned int * const red_ref, unsigned int * const green_ref, unsigned int * const blue_ref, unsigned int * const alpha_ref, unsigned int * const prev_red_ref, unsigned int * const prev_green_ref, unsigned int * const prev_blue_ref, unsigned int * const prev_alpha_ref, png_uint_32 * const j_ref, png_bytep alpha_row, png_uint_32 width, int channels, png_color palette[256], png_byte trans_alpha[256], int num_palette, int num_trans)
{
  png_bytepp row_ptr = *row_ptr_ref;
  png_bytep sample_ptr = *sample_ptr_ref;
  int index = *index_ref;
  unsigned int red = *red_ref;
  unsigned int green = *green_ref;
  unsigned int blue = *blue_ref;
  unsigned int alpha = *alpha_ref;
  unsigned int prev_red = *prev_red_ref;
  unsigned int prev_green = *prev_green_ref;
  unsigned int prev_blue = *prev_blue_ref;
  unsigned int prev_alpha = *prev_alpha_ref;
  png_uint_32 j = *j_ref;
  for (j = 0; j < width; j += 1, sample_ptr += channels)
  {
    helper_helper_helper_opng_reduce_to_palette_2_1_1(&row_ptr, &index, &red, &green, &blue, &alpha, &prev_red, &prev_green, &prev_blue, &prev_alpha, &j, alpha_row, palette, trans_alpha, num_palette, num_trans, sample_ptr);
  }

  *row_ptr_ref = row_ptr;
  *sample_ptr_ref = sample_ptr;
  *index_ref = index;
  *red_ref = red;
  *green_ref = green;
  *blue_ref = blue;
  *alpha_ref = alpha;
  *prev_red_ref = prev_red;
  *prev_green_ref = prev_green;
  *prev_blue_ref = prev_blue;
  *prev_alpha_ref = prev_alpha;
  *j_ref = j;
}


----------------------------
***/


// hint:  ['red_ref is a mutable refrence to unsigned int', 'green_ref is a mutable refrence to unsigned int', 'blue_ref is a mutable refrence to unsigned int', 'alpha_ref is a mutable refrence to unsigned int', 'prev_red_ref is a mutable refrence to unsigned int', 'prev_green_ref is a mutable refrence to unsigned int', 'prev_blue_ref is a mutable refrence to unsigned int', 'prev_alpha_ref is a mutable refrence to unsigned int', 'i_ref is a mutable refrence to png_uint_32']
void helper_helper_helper_opng_reduce_to_palette_1_1_1(unsigned int * const red_ref, unsigned int * const green_ref, unsigned int * const blue_ref, unsigned int * const alpha_ref, unsigned int * const prev_red_ref, unsigned int * const prev_green_ref, unsigned int * const prev_blue_ref, unsigned int * const prev_alpha_ref, png_uint_32 * const i_ref, png_bytep alpha_row, png_uint_32 height, png_color palette[256], png_byte trans_alpha[256], int num_palette, int num_trans, int index, png_bytep sample_ptr, png_uint_32 j)
{
  unsigned int red = *red_ref;
  unsigned int green = *green_ref;
  unsigned int blue = *blue_ref;
  unsigned int alpha = *alpha_ref;
  unsigned int prev_red = *prev_red_ref;
  unsigned int prev_green = *prev_green_ref;
  unsigned int prev_blue = *prev_blue_ref;
  unsigned int prev_alpha = *prev_alpha_ref;
  png_uint_32 i = *i_ref;
  red = sample_ptr[0];
  green = sample_ptr[1];
  blue = sample_ptr[2];
  alpha = alpha_row[j];
  if ((((red != prev_red) || (green != prev_green)) || (blue != prev_blue)) || (alpha != prev_alpha))
  {
    prev_red = red;
    prev_green = green;
    prev_blue = blue;
    prev_alpha = alpha;
    if (opng_insert_palette_entry(palette, &num_palette, trans_alpha, &num_trans, 256, red, green, blue, alpha, &index) < 0)
    {
      assert(num_palette < 0);
      i = height;
      break;
    }
  }
  *red_ref = red;
  *green_ref = green;
  *blue_ref = blue;
  *alpha_ref = alpha;
  *prev_red_ref = prev_red;
  *prev_green_ref = prev_green;
  *prev_blue_ref = prev_blue;
  *prev_alpha_ref = prev_alpha;
  *i_ref = i;
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
typedef png_byte *png_bytep
----------------------------
static int opng_insert_palette_entry(png_colorp palette, int *num_palette, png_bytep trans_alpha, int *num_trans, int max_tuples, unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha, int *index)
{
  int low;
  int high;
  int mid;
  int cmp;
  int i;
  assert(((*num_palette) >= 0) && ((*num_palette) <= max_tuples));
  assert(((*num_trans) >= 0) && ((*num_trans) <= (*num_palette)));
  if (alpha < 255)
  {
    low = 0;
    high = (*num_trans) - 1;
    while (low <= high)
    {
      mid = (low + high) / 2;
      cmp = (((int) alpha) != ((int) trans_alpha[mid])) ? (((int) alpha) - ((int) trans_alpha[mid])) : ((((int) red) != palette[mid].red) ? (((int) red) - ((int) palette[mid].red)) : ((((int) green) != ((int) palette[mid].green)) ? (((int) green) - ((int) palette[mid].green)) : (((int) blue) - ((int) palette[mid].blue))));
      if (cmp < 0)
      {
        high = mid - 1;
      }
      else
        if (cmp > 0)
      {
        low = mid + 1;
      }
      else
      {
        *index = mid;
        return 0;
      }
    }

  }
  else
  {
    low = *num_trans;
    high = (*num_palette) - 1;
    while (low <= high)
    {
      mid = (low + high) / 2;
      cmp = (((int) red) != ((int) palette[mid].red)) ? (((int) red) - ((int) palette[mid].red)) : ((((int) green) != ((int) palette[mid].green)) ? (((int) green) - ((int) palette[mid].green)) : (((int) blue) - ((int) palette[mid].blue)));
      if (cmp < 0)
      {
        high = mid - 1;
      }
      else
        if (cmp > 0)
      {
        low = mid + 1;
      }
      else
      {
        *index = mid;
        return 0;
      }
    }

  }
  if (alpha > 255)
  {
    for (i = 0; i < (*num_trans); i += 1)
    {
      cmp = (((int) red) != ((int) palette[i].red)) ? (((int) red) - ((int) palette[i].red)) : ((((int) green) != ((int) palette[i].green)) ? (((int) green) - ((int) palette[i].green)) : (((int) blue) - ((int) palette[i].blue)));
      if (cmp == 0)
      {
        *index = i;
        return 0;
      }
    }

  }
  if ((*num_palette) >= max_tuples)
  {
    *num_palette = (*num_trans = (*index = -1));
    return -1;
  }
  assert((low >= 0) && (low <= (*num_palette)));
  for (i = *num_palette; i > low; i -= 1)
  {
    palette[i] = palette[i - 1];
  }

  palette[low].red = (png_byte) red;
  palette[low].green = (png_byte) green;
  palette[low].blue = (png_byte) blue;
  *num_palette += 1;
  if (alpha < 255)
  {
    assert(low <= (*num_trans));
    for (i = *num_trans; i > low; i -= 1)
    {
      trans_alpha[i] = trans_alpha[i - 1];
    }

    trans_alpha[low] = (png_byte) alpha;
    *num_trans += 1;
  }
  *index = low;
  return 1;
}


----------------------------
***/


// hint:  ['sample_ptr_ref is a mutable refrence to png_bytep', 'red_ref is a mutable refrence to unsigned int', 'green_ref is a mutable refrence to unsigned int', 'blue_ref is a mutable refrence to unsigned int', 'alpha_ref is a mutable refrence to unsigned int', 'prev_red_ref is a mutable refrence to unsigned int', 'prev_green_ref is a mutable refrence to unsigned int', 'prev_blue_ref is a mutable refrence to unsigned int', 'prev_alpha_ref is a mutable refrence to unsigned int', 'i_ref is a mutable refrence to png_uint_32', 'j_ref is a mutable refrence to png_uint_32']
void helper_helper_opng_reduce_to_palette_1_1(png_bytep * const sample_ptr_ref, unsigned int * const red_ref, unsigned int * const green_ref, unsigned int * const blue_ref, unsigned int * const alpha_ref, unsigned int * const prev_red_ref, unsigned int * const prev_green_ref, unsigned int * const prev_blue_ref, unsigned int * const prev_alpha_ref, png_uint_32 * const i_ref, png_uint_32 * const j_ref, png_bytep alpha_row, png_uint_32 height, png_uint_32 width, int channels, png_color palette[256], png_byte trans_alpha[256], int num_palette, int num_trans, int index)
{
  png_bytep sample_ptr = *sample_ptr_ref;
  unsigned int red = *red_ref;
  unsigned int green = *green_ref;
  unsigned int blue = *blue_ref;
  unsigned int alpha = *alpha_ref;
  unsigned int prev_red = *prev_red_ref;
  unsigned int prev_green = *prev_green_ref;
  unsigned int prev_blue = *prev_blue_ref;
  unsigned int prev_alpha = *prev_alpha_ref;
  png_uint_32 i = *i_ref;
  png_uint_32 j = *j_ref;
  for (j = 0; j < width; j += 1, sample_ptr += channels)
  {
    helper_helper_helper_opng_reduce_to_palette_1_1_1(&red, &green, &blue, &alpha, &prev_red, &prev_green, &prev_blue, &prev_alpha, &i, alpha_row, height, palette, trans_alpha, num_palette, num_trans, index, sample_ptr, j);
  }

  *sample_ptr_ref = sample_ptr;
  *red_ref = red;
  *green_ref = green;
  *blue_ref = blue;
  *alpha_ref = alpha;
  *prev_red_ref = prev_red;
  *prev_green_ref = prev_green;
  *prev_blue_ref = prev_blue;
  *prev_alpha_ref = prev_alpha;
  *i_ref = i;
  *j_ref = j;
}


/*** DEPENDENCIES:
void helper_helper_helper_opng_reduce_to_palette_1_1_1(unsigned int * const red_ref, unsigned int * const green_ref, unsigned int * const blue_ref, unsigned int * const alpha_ref, unsigned int * const prev_red_ref, unsigned int * const prev_green_ref, unsigned int * const prev_blue_ref, unsigned int * const prev_alpha_ref, png_uint_32 * const i_ref, png_bytep alpha_row, png_uint_32 height, png_color palette[256], png_byte trans_alpha[256], int num_palette, int num_trans, int index, png_bytep sample_ptr, png_uint_32 j)
{
  unsigned int red = *red_ref;
  unsigned int green = *green_ref;
  unsigned int blue = *blue_ref;
  unsigned int alpha = *alpha_ref;
  unsigned int prev_red = *prev_red_ref;
  unsigned int prev_green = *prev_green_ref;
  unsigned int prev_blue = *prev_blue_ref;
  unsigned int prev_alpha = *prev_alpha_ref;
  png_uint_32 i = *i_ref;
  red = sample_ptr[0];
  green = sample_ptr[1];
  blue = sample_ptr[2];
  alpha = alpha_row[j];
  if ((((red != prev_red) || (green != prev_green)) || (blue != prev_blue)) || (alpha != prev_alpha))
  {
    prev_red = red;
    prev_green = green;
    prev_blue = blue;
    prev_alpha = alpha;
    if (opng_insert_palette_entry(palette, &num_palette, trans_alpha, &num_trans, 256, red, green, blue, alpha, &index) < 0)
    {
      assert(num_palette < 0);
      i = height;
      break;
    }
  }
  *red_ref = red;
  *green_ref = green;
  *blue_ref = blue;
  *alpha_ref = alpha;
  *prev_red_ref = prev_red;
  *prev_green_ref = prev_green;
  *prev_blue_ref = prev_blue;
  *prev_alpha_ref = prev_alpha;
  *i_ref = i;
}


----------------------------
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
typedef png_byte *png_bytep
----------------------------
***/


// hint:  ['sample_ptr_ref is a mutable refrence to png_bytep', 'gray_ref is a mutable refrence to unsigned int', 'red_ref is a mutable refrence to unsigned int', 'green_ref is a mutable refrence to unsigned int', 'blue_ref is a mutable refrence to unsigned int', 'alpha_ref is a mutable refrence to unsigned int', 'prev_gray_ref is a mutable refrence to unsigned int', 'prev_red_ref is a mutable refrence to unsigned int', 'prev_green_ref is a mutable refrence to unsigned int', 'prev_blue_ref is a mutable refrence to unsigned int', 'prev_alpha_ref is a mutable refrence to unsigned int', 'i_ref is a mutable refrence to png_uint_32', 'j_ref is a mutable refrence to png_uint_32']
void helper_opng_reduce_to_palette_1(png_bytep * const sample_ptr_ref, unsigned int * const gray_ref, unsigned int * const red_ref, unsigned int * const green_ref, unsigned int * const blue_ref, unsigned int * const alpha_ref, unsigned int * const prev_gray_ref, unsigned int * const prev_red_ref, unsigned int * const prev_green_ref, unsigned int * const prev_blue_ref, unsigned int * const prev_alpha_ref, png_uint_32 * const i_ref, png_uint_32 * const j_ref, png_row_info row_info, png_bytepp row_ptr, png_bytep alpha_row, png_uint_32 height, png_uint_32 width, int color_type, int channels, png_color palette[256], png_byte trans_alpha[256], png_color_16p trans_color, int num_palette, int num_trans, int index)
{
  png_bytep sample_ptr = *sample_ptr_ref;
  unsigned int gray = *gray_ref;
  unsigned int red = *red_ref;
  unsigned int green = *green_ref;
  unsigned int blue = *blue_ref;
  unsigned int alpha = *alpha_ref;
  unsigned int prev_gray = *prev_gray_ref;
  unsigned int prev_red = *prev_red_ref;
  unsigned int prev_green = *prev_green_ref;
  unsigned int prev_blue = *prev_blue_ref;
  unsigned int prev_alpha = *prev_alpha_ref;
  png_uint_32 i = *i_ref;
  png_uint_32 j = *j_ref;
  sample_ptr = *row_ptr;
  opng_get_alpha_row(&row_info, trans_color, *row_ptr, alpha_row);
  if (color_type & 2)
  {
    helper_helper_opng_reduce_to_palette_1_1(&sample_ptr, &red, &green, &blue, &alpha, &prev_red, &prev_green, &prev_blue, &prev_alpha, &i, &j, alpha_row, height, width, channels, palette, trans_alpha, num_palette, num_trans, index);
  }
  else
  {
    for (j = 0; j < width; j += 1, sample_ptr += channels)
    {
      gray = sample_ptr[0];
      alpha = alpha_row[j];
      if ((gray != prev_gray) || (alpha != prev_alpha))
      {
        prev_gray = gray;
        prev_alpha = alpha;
        if (opng_insert_palette_entry(palette, &num_palette, trans_alpha, &num_trans, 256, gray, gray, gray, alpha, &index) < 0)
        {
          assert(num_palette < 0);
          i = height;
          break;
        }
      }
    }

  }
  *sample_ptr_ref = sample_ptr;
  *gray_ref = gray;
  *red_ref = red;
  *green_ref = green;
  *blue_ref = blue;
  *alpha_ref = alpha;
  *prev_gray_ref = prev_gray;
  *prev_red_ref = prev_red;
  *prev_green_ref = prev_green;
  *prev_blue_ref = prev_blue;
  *prev_alpha_ref = prev_alpha;
  *i_ref = i;
  *j_ref = j;
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
typedef struct png_color_struct
{
  png_byte red;
  png_byte green;
  png_byte blue;
} png_color
----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef png_color_16 *png_color_16p
----------------------------
typedef unsigned char png_byte
----------------------------
static void opng_get_alpha_row(png_row_infop row_info_ptr, png_color_16p trans_color, png_bytep row, png_bytep alpha_row)
{
  png_bytep sample_ptr;
  png_uint_32 width;
  int color_type;
  int bit_depth;
  int channels;
  png_byte trans_red;
  png_byte trans_green;
  png_byte trans_blue;
  png_byte trans_gray;
  png_uint_32 i;
  width = row_info_ptr->width;
  color_type = row_info_ptr->color_type;
  bit_depth = row_info_ptr->bit_depth;
  channels = row_info_ptr->channels;
  assert(!(color_type & 1));
  assert(bit_depth == 8);
  if (!(color_type & 4))
  {
    helper_opng_get_alpha_row_1(&alpha_row, &sample_ptr, &trans_red, &trans_green, &trans_blue, &trans_gray, &i, trans_color, row, width, color_type, channels);
  }
  assert(channels > 1);
  sample_ptr = row + (channels - 1);
  for (i = 0; i < width; i += 1, sample_ptr += channels, alpha_row += 1)
  {
    *alpha_row = *sample_ptr;
  }

}


----------------------------
typedef png_byte **png_bytepp
----------------------------
void helper_helper_opng_reduce_to_palette_1_1(png_bytep * const sample_ptr_ref, unsigned int * const red_ref, unsigned int * const green_ref, unsigned int * const blue_ref, unsigned int * const alpha_ref, unsigned int * const prev_red_ref, unsigned int * const prev_green_ref, unsigned int * const prev_blue_ref, unsigned int * const prev_alpha_ref, png_uint_32 * const i_ref, png_uint_32 * const j_ref, png_bytep alpha_row, png_uint_32 height, png_uint_32 width, int channels, png_color palette[256], png_byte trans_alpha[256], int num_palette, int num_trans, int index)
{
  png_bytep sample_ptr = *sample_ptr_ref;
  unsigned int red = *red_ref;
  unsigned int green = *green_ref;
  unsigned int blue = *blue_ref;
  unsigned int alpha = *alpha_ref;
  unsigned int prev_red = *prev_red_ref;
  unsigned int prev_green = *prev_green_ref;
  unsigned int prev_blue = *prev_blue_ref;
  unsigned int prev_alpha = *prev_alpha_ref;
  png_uint_32 i = *i_ref;
  png_uint_32 j = *j_ref;
  for (j = 0; j < width; j += 1, sample_ptr += channels)
  {
    helper_helper_helper_opng_reduce_to_palette_1_1_1(&red, &green, &blue, &alpha, &prev_red, &prev_green, &prev_blue, &prev_alpha, &i, alpha_row, height, palette, trans_alpha, num_palette, num_trans, index, sample_ptr, j);
  }

  *sample_ptr_ref = sample_ptr;
  *red_ref = red;
  *green_ref = green;
  *blue_ref = blue;
  *alpha_ref = alpha;
  *prev_red_ref = prev_red;
  *prev_green_ref = prev_green;
  *prev_blue_ref = prev_blue;
  *prev_alpha_ref = prev_alpha;
  *i_ref = i;
  *j_ref = j;
}


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
typedef png_byte *png_bytep
----------------------------
static int opng_insert_palette_entry(png_colorp palette, int *num_palette, png_bytep trans_alpha, int *num_trans, int max_tuples, unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha, int *index)
{
  int low;
  int high;
  int mid;
  int cmp;
  int i;
  assert(((*num_palette) >= 0) && ((*num_palette) <= max_tuples));
  assert(((*num_trans) >= 0) && ((*num_trans) <= (*num_palette)));
  if (alpha < 255)
  {
    low = 0;
    high = (*num_trans) - 1;
    while (low <= high)
    {
      mid = (low + high) / 2;
      cmp = (((int) alpha) != ((int) trans_alpha[mid])) ? (((int) alpha) - ((int) trans_alpha[mid])) : ((((int) red) != palette[mid].red) ? (((int) red) - ((int) palette[mid].red)) : ((((int) green) != ((int) palette[mid].green)) ? (((int) green) - ((int) palette[mid].green)) : (((int) blue) - ((int) palette[mid].blue))));
      if (cmp < 0)
      {
        high = mid - 1;
      }
      else
        if (cmp > 0)
      {
        low = mid + 1;
      }
      else
      {
        *index = mid;
        return 0;
      }
    }

  }
  else
  {
    low = *num_trans;
    high = (*num_palette) - 1;
    while (low <= high)
    {
      mid = (low + high) / 2;
      cmp = (((int) red) != ((int) palette[mid].red)) ? (((int) red) - ((int) palette[mid].red)) : ((((int) green) != ((int) palette[mid].green)) ? (((int) green) - ((int) palette[mid].green)) : (((int) blue) - ((int) palette[mid].blue)));
      if (cmp < 0)
      {
        high = mid - 1;
      }
      else
        if (cmp > 0)
      {
        low = mid + 1;
      }
      else
      {
        *index = mid;
        return 0;
      }
    }

  }
  if (alpha > 255)
  {
    for (i = 0; i < (*num_trans); i += 1)
    {
      cmp = (((int) red) != ((int) palette[i].red)) ? (((int) red) - ((int) palette[i].red)) : ((((int) green) != ((int) palette[i].green)) ? (((int) green) - ((int) palette[i].green)) : (((int) blue) - ((int) palette[i].blue)));
      if (cmp == 0)
      {
        *index = i;
        return 0;
      }
    }

  }
  if ((*num_palette) >= max_tuples)
  {
    *num_palette = (*num_trans = (*index = -1));
    return -1;
  }
  assert((low >= 0) && (low <= (*num_palette)));
  for (i = *num_palette; i > low; i -= 1)
  {
    palette[i] = palette[i - 1];
  }

  palette[low].red = (png_byte) red;
  palette[low].green = (png_byte) green;
  palette[low].blue = (png_byte) blue;
  *num_palette += 1;
  if (alpha < 255)
  {
    assert(low <= (*num_trans));
    for (i = *num_trans; i > low; i -= 1)
    {
      trans_alpha[i] = trans_alpha[i - 1];
    }

    trans_alpha[low] = (png_byte) alpha;
    *num_trans += 1;
  }
  *index = low;
  return 1;
}


----------------------------
***/


static png_uint_32 opng_reduce_to_palette(png_structp png_ptr, png_infop info_ptr, png_uint_32 reductions)
{
  png_uint_32 result;
  png_row_info row_info;
  png_bytepp row_ptr;
  png_bytep sample_ptr;
  png_bytep alpha_row;
  png_uint_32 height;
  png_uint_32 width;
  int color_type;
  int interlace_type;
  int compression_type;
  int filter_type;
  int src_bit_depth;
  int dest_bit_depth;
  int channels;
  png_color palette[256];
  png_byte trans_alpha[256];
  png_color_16p trans_color;
  int num_palette;
  int num_trans;
  int index;
  unsigned int gray;
  unsigned int red;
  unsigned int green;
  unsigned int blue;
  unsigned int alpha;
  unsigned int prev_gray;
  unsigned int prev_red;
  unsigned int prev_green;
  unsigned int prev_blue;
  unsigned int prev_alpha;
  png_color_16p background;
  png_uint_32 i;
  png_uint_32 j;
  (void) 0;
  png_get_IHDR(png_ptr, info_ptr, &width, &height, &src_bit_depth, &color_type, &interlace_type, &compression_type, &filter_type);
  if (src_bit_depth != 8)
  {
    return 0x0000;
  }
  assert(!(color_type & 1));
  row_ptr = png_get_rows(png_ptr, info_ptr);
  channels = png_get_channels(png_ptr, info_ptr);
  alpha_row = (png_bytep) png_malloc(png_ptr, width);
  row_info.width = width;
  row_info.rowbytes = 0;
  row_info.color_type = (png_byte) color_type;
  row_info.bit_depth = (png_byte) src_bit_depth;
  row_info.channels = (png_byte) channels;
  row_info.pixel_depth = 0;
  num_palette = (num_trans = 0);
  trans_color = 0;
  png_get_tRNS(png_ptr, info_ptr, 0, 0, &trans_color);
  prev_gray = (prev_red = (prev_green = (prev_blue = (prev_alpha = (unsigned int) (-1)))));
  for (i = 0; i < height; i += 1, row_ptr += 1)
  {
    helper_opng_reduce_to_palette_1(&sample_ptr, &gray, &red, &green, &blue, &alpha, &prev_gray, &prev_red, &prev_green, &prev_blue, &prev_alpha, &i, &j, row_info, row_ptr, alpha_row, height, width, color_type, channels, palette, trans_alpha, trans_color, num_palette, num_trans, index);
  }

  if ((num_palette >= 0) && png_get_bKGD(png_ptr, info_ptr, &background))
  {
    if (color_type & 2)
    {
      red = background->red;
      green = background->green;
      blue = background->blue;
    }
    else
      red = (green = (blue = background->gray));
    if (((red > 255) || (green > 255)) || (blue > 255))
    {
      png_warning(png_ptr, "Invalid colors in bKGD");
      png_set_invalid(png_ptr, info_ptr, 0x0020U);
    }
    else
    {
      opng_insert_palette_entry(palette, &num_palette, trans_alpha, &num_trans, 256, red, green, blue, (unsigned int) (-1), &index);
      if (index >= 0)
      {
        background->index = (png_byte) index;
      }
    }
  }
  if (num_palette >= 0)
  {
    assert((num_palette > 0) && (num_palette <= 256));
    assert((num_trans >= 0) && (num_trans <= num_palette));
    if (num_palette <= 2)
    {
      dest_bit_depth = 1;
    }
    else
      if (num_palette <= 4)
    {
      dest_bit_depth = 2;
    }
    else
      if (num_palette <= 16)
    {
      dest_bit_depth = 4;
    }
    else
      dest_bit_depth = 8;
    if (((channels * 8) == dest_bit_depth) || (((((((3 * num_palette) + num_trans) * 8) / ((channels * 8) - dest_bit_depth)) / width) / height) >= 1))
    {
      num_palette = -1;
    }
  }
  if (num_palette < 0)
  {
    png_free(png_ptr, alpha_row);
    return 0x0000;
  }
  row_ptr = png_get_rows(png_ptr, info_ptr);
  index = -1;
  prev_red = (prev_green = (prev_blue = (prev_alpha = (unsigned int) (-1))));
  for (i = 0; i < height; i += 1, row_ptr += 1)
  {
    helper_opng_reduce_to_palette_2(&row_ptr, &sample_ptr, &index, &gray, &red, &green, &blue, &alpha, &prev_gray, &prev_red, &prev_green, &prev_blue, &prev_alpha, &j, row_info, alpha_row, width, color_type, channels, palette, trans_alpha, trans_color, num_palette, num_trans);
  }

  png_set_IHDR(png_ptr, info_ptr, width, height, 8, 2 | 1, interlace_type, compression_type, filter_type);
  png_set_PLTE(png_ptr, info_ptr, palette, num_palette);
  if (num_trans > 0)
  {
    png_set_tRNS(png_ptr, info_ptr, trans_alpha, num_trans, 0);
  }
  png_free(png_ptr, alpha_row);
  result = 0x0010;
  if (reductions & 0x0002)
  {
    result |= opng_reduce_palette_bits(png_ptr, info_ptr, reductions);
  }
  return result;
}


/*** DEPENDENCIES:
void png_set_invalid(png_const_structrp png_ptr, png_inforp info_ptr, int mask)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    info_ptr->valid &= (unsigned int) (~mask);
  }
}


----------------------------
typedef struct png_color_struct
{
  png_byte red;
  png_byte green;
  png_byte blue;
} png_color
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
png_byte png_get_channels(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    return info_ptr->channels;
  }
  return 0;
}


----------------------------
typedef png_struct *png_structp
----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef png_color_16 *png_color_16p
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
void helper_opng_reduce_to_palette_2(png_bytepp * const row_ptr_ref, png_bytep * const sample_ptr_ref, int * const index_ref, unsigned int * const gray_ref, unsigned int * const red_ref, unsigned int * const green_ref, unsigned int * const blue_ref, unsigned int * const alpha_ref, unsigned int * const prev_gray_ref, unsigned int * const prev_red_ref, unsigned int * const prev_green_ref, unsigned int * const prev_blue_ref, unsigned int * const prev_alpha_ref, png_uint_32 * const j_ref, png_row_info row_info, png_bytep alpha_row, png_uint_32 width, int color_type, int channels, png_color palette[256], png_byte trans_alpha[256], png_color_16p trans_color, int num_palette, int num_trans)
{
  png_bytepp row_ptr = *row_ptr_ref;
  png_bytep sample_ptr = *sample_ptr_ref;
  int index = *index_ref;
  unsigned int gray = *gray_ref;
  unsigned int red = *red_ref;
  unsigned int green = *green_ref;
  unsigned int blue = *blue_ref;
  unsigned int alpha = *alpha_ref;
  unsigned int prev_gray = *prev_gray_ref;
  unsigned int prev_red = *prev_red_ref;
  unsigned int prev_green = *prev_green_ref;
  unsigned int prev_blue = *prev_blue_ref;
  unsigned int prev_alpha = *prev_alpha_ref;
  png_uint_32 j = *j_ref;
  sample_ptr = *row_ptr;
  opng_get_alpha_row(&row_info, trans_color, *row_ptr, alpha_row);
  if (color_type & 2)
  {
    helper_helper_opng_reduce_to_palette_2_1(&row_ptr, &sample_ptr, &index, &red, &green, &blue, &alpha, &prev_red, &prev_green, &prev_blue, &prev_alpha, &j, alpha_row, width, channels, palette, trans_alpha, num_palette, num_trans);
  }
  else
  {
    for (j = 0; j < width; j += 1, sample_ptr += channels)
    {
      gray = sample_ptr[0];
      alpha = alpha_row[j];
      if ((gray != prev_gray) || (alpha != prev_alpha))
      {
        prev_gray = gray;
        prev_alpha = alpha;
        if (opng_insert_palette_entry(palette, &num_palette, trans_alpha, &num_trans, 256, gray, gray, gray, alpha, &index) != 0)
        {
          index = -1;
        }
      }
      assert(index >= 0);
      (*row_ptr)[j] = (png_byte) index;
    }

  }
  *row_ptr_ref = row_ptr;
  *sample_ptr_ref = sample_ptr;
  *index_ref = index;
  *gray_ref = gray;
  *red_ref = red;
  *green_ref = green;
  *blue_ref = blue;
  *alpha_ref = alpha;
  *prev_gray_ref = prev_gray;
  *prev_red_ref = prev_red;
  *prev_green_ref = prev_green;
  *prev_blue_ref = prev_blue;
  *prev_alpha_ref = prev_alpha;
  *j_ref = j;
}


----------------------------
typedef struct png_info_def png_info
----------------------------
static int opng_insert_palette_entry(png_colorp palette, int *num_palette, png_bytep trans_alpha, int *num_trans, int max_tuples, unsigned int red, unsigned int green, unsigned int blue, unsigned int alpha, int *index)
{
  int low;
  int high;
  int mid;
  int cmp;
  int i;
  assert(((*num_palette) >= 0) && ((*num_palette) <= max_tuples));
  assert(((*num_trans) >= 0) && ((*num_trans) <= (*num_palette)));
  if (alpha < 255)
  {
    low = 0;
    high = (*num_trans) - 1;
    while (low <= high)
    {
      mid = (low + high) / 2;
      cmp = (((int) alpha) != ((int) trans_alpha[mid])) ? (((int) alpha) - ((int) trans_alpha[mid])) : ((((int) red) != palette[mid].red) ? (((int) red) - ((int) palette[mid].red)) : ((((int) green) != ((int) palette[mid].green)) ? (((int) green) - ((int) palette[mid].green)) : (((int) blue) - ((int) palette[mid].blue))));
      if (cmp < 0)
      {
        high = mid - 1;
      }
      else
        if (cmp > 0)
      {
        low = mid + 1;
      }
      else
      {
        *index = mid;
        return 0;
      }
    }

  }
  else
  {
    low = *num_trans;
    high = (*num_palette) - 1;
    while (low <= high)
    {
      mid = (low + high) / 2;
      cmp = (((int) red) != ((int) palette[mid].red)) ? (((int) red) - ((int) palette[mid].red)) : ((((int) green) != ((int) palette[mid].green)) ? (((int) green) - ((int) palette[mid].green)) : (((int) blue) - ((int) palette[mid].blue)));
      if (cmp < 0)
      {
        high = mid - 1;
      }
      else
        if (cmp > 0)
      {
        low = mid + 1;
      }
      else
      {
        *index = mid;
        return 0;
      }
    }

  }
  if (alpha > 255)
  {
    for (i = 0; i < (*num_trans); i += 1)
    {
      cmp = (((int) red) != ((int) palette[i].red)) ? (((int) red) - ((int) palette[i].red)) : ((((int) green) != ((int) palette[i].green)) ? (((int) green) - ((int) palette[i].green)) : (((int) blue) - ((int) palette[i].blue)));
      if (cmp == 0)
      {
        *index = i;
        return 0;
      }
    }

  }
  if ((*num_palette) >= max_tuples)
  {
    *num_palette = (*num_trans = (*index = -1));
    return -1;
  }
  assert((low >= 0) && (low <= (*num_palette)));
  for (i = *num_palette; i > low; i -= 1)
  {
    palette[i] = palette[i - 1];
  }

  palette[low].red = (png_byte) red;
  palette[low].green = (png_byte) green;
  palette[low].blue = (png_byte) blue;
  *num_palette += 1;
  if (alpha < 255)
  {
    assert(low <= (*num_trans));
    for (i = *num_trans; i > low; i -= 1)
    {
      trans_alpha[i] = trans_alpha[i - 1];
    }

    trans_alpha[low] = (png_byte) alpha;
    *num_trans += 1;
  }
  *index = low;
  return 1;
}


----------------------------
typedef unsigned char png_byte
----------------------------
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


----------------------------
png_bytepp png_get_rows(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    return info_ptr->row_pointers;
  }
  return 0;
}


----------------------------
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


----------------------------
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


----------------------------
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


----------------------------
void helper_opng_reduce_to_palette_1(png_bytep * const sample_ptr_ref, unsigned int * const gray_ref, unsigned int * const red_ref, unsigned int * const green_ref, unsigned int * const blue_ref, unsigned int * const alpha_ref, unsigned int * const prev_gray_ref, unsigned int * const prev_red_ref, unsigned int * const prev_green_ref, unsigned int * const prev_blue_ref, unsigned int * const prev_alpha_ref, png_uint_32 * const i_ref, png_uint_32 * const j_ref, png_row_info row_info, png_bytepp row_ptr, png_bytep alpha_row, png_uint_32 height, png_uint_32 width, int color_type, int channels, png_color palette[256], png_byte trans_alpha[256], png_color_16p trans_color, int num_palette, int num_trans, int index)
{
  png_bytep sample_ptr = *sample_ptr_ref;
  unsigned int gray = *gray_ref;
  unsigned int red = *red_ref;
  unsigned int green = *green_ref;
  unsigned int blue = *blue_ref;
  unsigned int alpha = *alpha_ref;
  unsigned int prev_gray = *prev_gray_ref;
  unsigned int prev_red = *prev_red_ref;
  unsigned int prev_green = *prev_green_ref;
  unsigned int prev_blue = *prev_blue_ref;
  unsigned int prev_alpha = *prev_alpha_ref;
  png_uint_32 i = *i_ref;
  png_uint_32 j = *j_ref;
  sample_ptr = *row_ptr;
  opng_get_alpha_row(&row_info, trans_color, *row_ptr, alpha_row);
  if (color_type & 2)
  {
    helper_helper_opng_reduce_to_palette_1_1(&sample_ptr, &red, &green, &blue, &alpha, &prev_red, &prev_green, &prev_blue, &prev_alpha, &i, &j, alpha_row, height, width, channels, palette, trans_alpha, num_palette, num_trans, index);
  }
  else
  {
    for (j = 0; j < width; j += 1, sample_ptr += channels)
    {
      gray = sample_ptr[0];
      alpha = alpha_row[j];
      if ((gray != prev_gray) || (alpha != prev_alpha))
      {
        prev_gray = gray;
        prev_alpha = alpha;
        if (opng_insert_palette_entry(palette, &num_palette, trans_alpha, &num_trans, 256, gray, gray, gray, alpha, &index) < 0)
        {
          assert(num_palette < 0);
          i = height;
          break;
        }
      }
    }

  }
  *sample_ptr_ref = sample_ptr;
  *gray_ref = gray;
  *red_ref = red;
  *green_ref = green;
  *blue_ref = blue;
  *alpha_ref = alpha;
  *prev_gray_ref = prev_gray;
  *prev_red_ref = prev_red;
  *prev_green_ref = prev_green;
  *prev_blue_ref = prev_blue;
  *prev_alpha_ref = prev_alpha;
  *i_ref = i;
  *j_ref = j;
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
static png_uint_32 opng_reduce_palette_bits(png_structp png_ptr, png_infop info_ptr, png_uint_32 reductions)
{
  png_uint_32 result;
  png_bytepp row_ptr;
  png_bytep src_sample_ptr;
  png_bytep dest_sample_ptr;
  png_uint_32 width;
  png_uint_32 height;
  int color_type;
  int interlace_type;
  int compression_type;
  int filter_type;
  int src_bit_depth;
  int dest_bit_depth;
  unsigned int src_mask_init;
  unsigned int src_mask;
  unsigned int src_shift;
  unsigned int dest_shift;
  unsigned int sample;
  unsigned int dest_buf;
  png_colorp palette;
  int num_palette;
  png_uint_32 i;
  png_uint_32 j;
  (void) 0;
  if (!(reductions & 0x0002))
  {
    return 0x0000;
  }
  png_get_IHDR(png_ptr, info_ptr, &width, &height, &src_bit_depth, &color_type, &interlace_type, &compression_type, &filter_type);
  if (color_type != (2 | 1))
  {
    return 0x0000;
  }
  if (!png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette))
  {
    num_palette = 0;
  }
  result = 0x0000;
  if (num_palette > (1 << src_bit_depth))
  {
    png_warning(png_ptr, "Too many colors in PLTE");
    num_palette = 1 << src_bit_depth;
    opng_realloc_PLTE(png_ptr, info_ptr, num_palette);
    png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette);
    assert(num_palette == (1 << src_bit_depth));
    result |= 0x2000;
  }
  if (num_palette > 16)
  {
    return result;
  }
  else
    if (num_palette > 4)
  {
    dest_bit_depth = 4;
  }
  else
    if (num_palette > 2)
  {
    dest_bit_depth = 2;
  }
  else
  {
    assert(num_palette > 0);
    dest_bit_depth = 1;
  }
  if (src_bit_depth <= dest_bit_depth)
  {
    assert(src_bit_depth == dest_bit_depth);
    return result;
  }
  row_ptr = png_get_rows(png_ptr, info_ptr);
  if (src_bit_depth == 8)
  {
    helper_opng_reduce_palette_bits_1(&row_ptr, &src_sample_ptr, &dest_sample_ptr, &dest_shift, &dest_buf, &i, &j, width, height, dest_bit_depth);
  }
  else
  {
    helper_opng_reduce_palette_bits_2(&row_ptr, &src_sample_ptr, &dest_sample_ptr, &src_mask_init, &src_mask, &src_shift, &dest_shift, &sample, &dest_buf, &i, &j, width, height, src_bit_depth, dest_bit_depth);
  }
  png_set_IHDR(png_ptr, info_ptr, width, height, dest_bit_depth, color_type, interlace_type, compression_type, filter_type);
  result |= 0x0002;
  return result;
}


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
typedef png_info *png_infop
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


// hint:  ['reductions_ref is a mutable refrence to png_uint_32', 'component_ptr_ref is a mutable refrence to png_bytep', 'j_ref is a mutable refrence to png_uint_32']
png_uint_32 helper_opng_analyze_bits_1(png_uint_32 * const reductions_ref, png_bytep * const component_ptr_ref, png_uint_32 * const j_ref, png_bytepp row_ptr, png_uint_32 width, int bit_depth, int channels, int sample_size, int offset_alpha)
{
  png_uint_32 reductions = *reductions_ref;
  png_bytep component_ptr = *component_ptr_ref;
  png_uint_32 j = *j_ref;
  if (reductions == 0x0000)
  {
    return 0x0000;
  }
  if (reductions & 0x0001)
  {
    component_ptr = *row_ptr;
    for (j = 0; j < (channels * width); j += 1, component_ptr += 2)
    {
      if (component_ptr[0] != component_ptr[1])
      {
        reductions &= ~0x0001;
        break;
      }
    }

  }
  if (bit_depth == 8)
  {
    helper_helper_opng_analyze_bits_1_1(&reductions, &component_ptr, &j, row_ptr, width, sample_size, offset_alpha);
  }
  else
  {
    helper_helper_opng_analyze_bits_1_2(&reductions, &component_ptr, &j, row_ptr, width, sample_size, offset_alpha);
  }
  *reductions_ref = reductions;
  *component_ptr_ref = component_ptr;
  *j_ref = j;
}


/*** DEPENDENCIES:
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_byte **png_bytepp
----------------------------
void helper_helper_opng_analyze_bits_1_2(png_uint_32 * const reductions_ref, png_bytep * const component_ptr_ref, png_uint_32 * const j_ref, png_bytepp row_ptr, png_uint_32 width, int sample_size, int offset_alpha)
{
  png_uint_32 reductions = *reductions_ref;
  png_bytep component_ptr = *component_ptr_ref;
  png_uint_32 j = *j_ref;
  if (reductions & 0x0004)
  {
    component_ptr = *row_ptr;
    for (j = 0; j < width; j += 1, component_ptr += sample_size)
    {
      if ((((component_ptr[0] != component_ptr[2]) || (component_ptr[0] != component_ptr[4])) || (component_ptr[1] != component_ptr[3])) || (component_ptr[1] != component_ptr[5]))
      {
        reductions &= ~0x0004;
        break;
      }
    }

  }
  if (reductions & 0x0008)
  {
    component_ptr = (*row_ptr) + offset_alpha;
    for (j = 0; j < width; j += 1, component_ptr += sample_size)
    {
      if ((component_ptr[0] != 255) || (component_ptr[1] != 255))
      {
        reductions &= ~0x0008;
        break;
      }
    }

  }
  *reductions_ref = reductions;
  *component_ptr_ref = component_ptr;
  *j_ref = j;
}


----------------------------
void helper_helper_opng_analyze_bits_1_1(png_uint_32 * const reductions_ref, png_bytep * const component_ptr_ref, png_uint_32 * const j_ref, png_bytepp row_ptr, png_uint_32 width, int sample_size, int offset_alpha)
{
  png_uint_32 reductions = *reductions_ref;
  png_bytep component_ptr = *component_ptr_ref;
  png_uint_32 j = *j_ref;
  if (reductions & 0x0004)
  {
    component_ptr = *row_ptr;
    for (j = 0; j < width; j += 1, component_ptr += sample_size)
    {
      if ((component_ptr[0] != component_ptr[1]) || (component_ptr[0] != component_ptr[2]))
      {
        reductions &= ~0x0004;
        break;
      }
    }

  }
  if (reductions & 0x0008)
  {
    component_ptr = (*row_ptr) + offset_alpha;
    for (j = 0; j < width; j += 1, component_ptr += sample_size)
    {
      if (component_ptr[0] != 255)
      {
        reductions &= ~0x0008;
        break;
      }
    }

  }
  *reductions_ref = reductions;
  *component_ptr_ref = component_ptr;
  *j_ref = j;
}


----------------------------
typedef png_byte *png_bytep
----------------------------
***/


static png_uint_32 opng_analyze_bits(png_structp png_ptr, png_infop info_ptr, png_uint_32 reductions)
{
  png_bytepp row_ptr;
  png_bytep component_ptr;
  png_uint_32 height;
  png_uint_32 width;
  int bit_depth;
  int color_type;
  int byte_depth;
  int channels;
  int sample_size;
  int offset_alpha;
  png_color_16p background;
  png_uint_32 i;
  png_uint_32 j;
  (void) 0;
  png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, 0, 0, 0);
  if (bit_depth < 8)
  {
    return 0x0000;
  }
  if (color_type & 1)
  {
    return 0x0000;
  }
  byte_depth = bit_depth / 8;
  channels = png_get_channels(png_ptr, info_ptr);
  sample_size = channels * byte_depth;
  offset_alpha = (channels - 1) * byte_depth;
  reductions &= (0x0001 | 0x0004) | 0x0008;
  if (bit_depth <= 8)
  {
    reductions &= ~0x0001;
  }
  if (!(color_type & 2))
  {
    reductions &= ~0x0004;
  }
  if (!(color_type & 4))
  {
    reductions &= ~0x0008;
  }
  if (png_get_bKGD(png_ptr, info_ptr, &background))
  {
    if (reductions & 0x0001)
    {
      if (((((background->red % 257) != 0) || ((background->green % 257) != 0)) || ((background->blue % 257) != 0)) || ((background->gray % 257) != 0))
      {
        reductions &= ~0x0001;
      }
    }
    if (reductions & 0x0004)
    {
      if ((background->red != background->green) || (background->red != background->blue))
      {
        reductions &= ~0x0004;
      }
    }
  }
  row_ptr = png_get_rows(png_ptr, info_ptr);
  for (i = 0; i < height; i += 1, row_ptr += 1)
  {
    helper_opng_analyze_bits_1(&reductions, &component_ptr, &j, row_ptr, width, bit_depth, channels, sample_size, offset_alpha);
  }

  return reductions;
}


/*** DEPENDENCIES:
png_byte png_get_channels(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    return info_ptr->channels;
  }
  return 0;
}


----------------------------
typedef png_struct *png_structp
----------------------------
typedef struct png_color_struct
{
  png_byte red;
  png_byte green;
  png_byte blue;
} png_color
----------------------------
typedef unsigned char png_byte
----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef png_color_16 *png_color_16p
----------------------------
typedef png_byte **png_bytepp
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
png_bytepp png_get_rows(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    return info_ptr->row_pointers;
  }
  return 0;
}


----------------------------
typedef struct png_info_def png_info
----------------------------
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


----------------------------
typedef png_byte *png_bytep
----------------------------
png_uint_32 helper_opng_analyze_bits_1(png_uint_32 * const reductions_ref, png_bytep * const component_ptr_ref, png_uint_32 * const j_ref, png_bytepp row_ptr, png_uint_32 width, int bit_depth, int channels, int sample_size, int offset_alpha)
{
  png_uint_32 reductions = *reductions_ref;
  png_bytep component_ptr = *component_ptr_ref;
  png_uint_32 j = *j_ref;
  if (reductions == 0x0000)
  {
    return 0x0000;
  }
  if (reductions & 0x0001)
  {
    component_ptr = *row_ptr;
    for (j = 0; j < (channels * width); j += 1, component_ptr += 2)
    {
      if (component_ptr[0] != component_ptr[1])
      {
        reductions &= ~0x0001;
        break;
      }
    }

  }
  if (bit_depth == 8)
  {
    helper_helper_opng_analyze_bits_1_1(&reductions, &component_ptr, &j, row_ptr, width, sample_size, offset_alpha);
  }
  else
  {
    helper_helper_opng_analyze_bits_1_2(&reductions, &component_ptr, &j, row_ptr, width, sample_size, offset_alpha);
  }
  *reductions_ref = reductions;
  *component_ptr_ref = component_ptr;
  *j_ref = j;
}


----------------------------
***/


// hint:  ['trans_color_ref is a mutable refrence to png_color_16p']
void helper_opng_reduce_bits_1(png_color_16p * const trans_color_ref, png_structp png_ptr, png_infop info_ptr, png_uint_32 reductions)
{
  png_color_16p trans_color = *trans_color_ref;
  if (reductions & 0x0001)
  {
    if (((((trans_color->red % 257) == 0) && ((trans_color->green % 257) == 0)) && ((trans_color->blue % 257) == 0)) && ((trans_color->gray % 257) == 0))
    {
      trans_color->red &= 255;
      trans_color->green &= 255;
      trans_color->blue &= 255;
      trans_color->gray &= 255;
    }
    else
    {
      png_free_data(png_ptr, info_ptr, 0x2000U, -1);
      png_set_invalid(png_ptr, info_ptr, 0x0010U);
    }
  }
  if (reductions & 0x0004)
  {
    if ((trans_color->red == trans_color->green) || (trans_color->red == trans_color->blue))
    {
      trans_color->gray = trans_color->red;
    }
    else
    {
      png_free_data(png_ptr, info_ptr, 0x2000U, -1);
      png_set_invalid(png_ptr, info_ptr, 0x0010U);
    }
  }
  *trans_color_ref = trans_color;
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
void png_set_invalid(png_const_structrp png_ptr, png_inforp info_ptr, int mask)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    info_ptr->valid &= (unsigned int) (~mask);
  }
}


----------------------------
typedef struct png_color_struct
{
  png_byte red;
  png_byte green;
  png_byte blue;
} png_color
----------------------------
typedef png_struct *png_structp
----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef png_color_16 *png_color_16p
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
typedef png_info *png_infop
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef struct png_info_def png_info
----------------------------
***/


// hint:  ['sig_bits_ref is a mutable refrence to png_color_8p']
void helper_opng_reduce_bits_2(png_color_8p * const sig_bits_ref, png_uint_32 reductions)
{
  png_color_8p sig_bits = *sig_bits_ref;
  if (reductions & 0x0001)
  {
    if (sig_bits->red > 8)
    {
      sig_bits->red = 8;
    }
    if (sig_bits->green > 8)
    {
      sig_bits->green = 8;
    }
    if (sig_bits->blue > 8)
    {
      sig_bits->blue = 8;
    }
    if (sig_bits->gray > 8)
    {
      sig_bits->gray = 8;
    }
    if (sig_bits->alpha > 8)
    {
      sig_bits->alpha = 8;
    }
  }
  if (reductions & 0x0004)
  {
    png_byte max_sig_bits = sig_bits->red;
    if (max_sig_bits < sig_bits->green)
    {
      max_sig_bits = sig_bits->green;
    }
    if (max_sig_bits < sig_bits->blue)
    {
      max_sig_bits = sig_bits->blue;
    }
    sig_bits->gray = max_sig_bits;
  }
  *sig_bits_ref = sig_bits;
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
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_color_8 *png_color_8p
----------------------------
***/


static png_uint_32 opng_reduce_bits(png_structp png_ptr, png_infop info_ptr, png_uint_32 reductions)
{
  png_bytepp row_ptr;
  png_bytep src_ptr;
  png_bytep dest_ptr;
  png_uint_32 width;
  png_uint_32 height;
  int interlace_type;
  int compression_type;
  int filter_type;
  int src_bit_depth;
  int dest_bit_depth;
  int src_byte_depth;
  int dest_byte_depth;
  int src_color_type;
  int dest_color_type;
  int src_channels;
  int dest_channels;
  int src_sample_size;
  int dest_sample_size;
  int tran_tbl[8];
  png_color_16p trans_color;
  png_color_16p background;
  png_color_8p sig_bits;
  png_uint_32 i;
  png_uint_32 j;
  int k;
  (void) 0;
  reductions = opng_analyze_bits(png_ptr, info_ptr, reductions);
  if (reductions == 0x0000)
  {
    return 0x0000;
  }
  png_get_IHDR(png_ptr, info_ptr, &width, &height, &src_bit_depth, &src_color_type, &interlace_type, &compression_type, &filter_type);
  assert(src_bit_depth >= 8);
  if (reductions & 0x0001)
  {
    assert(src_bit_depth == 16);
    dest_bit_depth = 8;
  }
  else
    dest_bit_depth = src_bit_depth;
  src_byte_depth = src_bit_depth / 8;
  dest_byte_depth = dest_bit_depth / 8;
  dest_color_type = src_color_type;
  if (reductions & 0x0004)
  {
    assert(src_color_type & 2);
    dest_color_type &= ~2;
  }
  if (reductions & 0x0008)
  {
    assert(src_color_type & 4);
    dest_color_type &= ~4;
  }
  src_channels = png_get_channels(png_ptr, info_ptr);
  dest_channels = ((dest_color_type & 2) ? (3) : (1)) + ((dest_color_type & 4) ? (1) : (0));
  src_sample_size = src_channels * src_byte_depth;
  dest_sample_size = dest_channels * dest_byte_depth;
  for (k = 0; k < (4 * dest_byte_depth); k += 1)
  {
    tran_tbl[k] = (k * src_bit_depth) / dest_bit_depth;
  }

  if ((reductions & 0x0004) && (dest_color_type & 4))
  {
    tran_tbl[dest_byte_depth] = tran_tbl[3 * dest_byte_depth];
    if (dest_byte_depth == 2)
    {
      tran_tbl[dest_byte_depth + 1] = tran_tbl[(3 * dest_byte_depth) + 1];
    }
  }
  assert(src_sample_size > dest_sample_size);
  row_ptr = png_get_rows(png_ptr, info_ptr);
  for (i = 0; i < height; i += 1, row_ptr += 1)
  {
    src_ptr = (dest_ptr = *row_ptr);
    for (j = 0; j < width; j += 1)
    {
      for (k = 0; k < dest_sample_size; k += 1)
      {
        dest_ptr[k] = src_ptr[tran_tbl[k]];
      }

      src_ptr += src_sample_size;
      dest_ptr += dest_sample_size;
    }

  }

  if (png_get_tRNS(png_ptr, info_ptr, 0, 0, &trans_color))
  {
    helper_opng_reduce_bits_1(&trans_color, png_ptr, info_ptr, reductions);
  }
  if (png_get_bKGD(png_ptr, info_ptr, &background))
  {
    if (reductions & 0x0001)
    {
      background->red &= 255;
      background->green &= 255;
      background->blue &= 255;
      background->gray &= 255;
    }
    if (reductions & 0x0004)
    {
      background->gray = background->red;
    }
  }
  if (png_get_sBIT(png_ptr, info_ptr, &sig_bits))
  {
    helper_opng_reduce_bits_2(&sig_bits, reductions);
  }
  png_set_IHDR(png_ptr, info_ptr, width, height, dest_bit_depth, dest_color_type, interlace_type, compression_type, filter_type);
  return reductions;
}


/*** DEPENDENCIES:
typedef struct png_color_struct
{
  png_byte red;
  png_byte green;
  png_byte blue;
} png_color
----------------------------
typedef png_byte **png_bytepp
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
typedef png_color_8 *png_color_8p
----------------------------
typedef png_byte *png_bytep
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
png_byte png_get_channels(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    return info_ptr->channels;
  }
  return 0;
}


----------------------------
typedef png_struct *png_structp
----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef png_color_16 *png_color_16p
----------------------------
static png_uint_32 opng_analyze_bits(png_structp png_ptr, png_infop info_ptr, png_uint_32 reductions)
{
  png_bytepp row_ptr;
  png_bytep component_ptr;
  png_uint_32 height;
  png_uint_32 width;
  int bit_depth;
  int color_type;
  int byte_depth;
  int channels;
  int sample_size;
  int offset_alpha;
  png_color_16p background;
  png_uint_32 i;
  png_uint_32 j;
  (void) 0;
  png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, 0, 0, 0);
  if (bit_depth < 8)
  {
    return 0x0000;
  }
  if (color_type & 1)
  {
    return 0x0000;
  }
  byte_depth = bit_depth / 8;
  channels = png_get_channels(png_ptr, info_ptr);
  sample_size = channels * byte_depth;
  offset_alpha = (channels - 1) * byte_depth;
  reductions &= (0x0001 | 0x0004) | 0x0008;
  if (bit_depth <= 8)
  {
    reductions &= ~0x0001;
  }
  if (!(color_type & 2))
  {
    reductions &= ~0x0004;
  }
  if (!(color_type & 4))
  {
    reductions &= ~0x0008;
  }
  if (png_get_bKGD(png_ptr, info_ptr, &background))
  {
    if (reductions & 0x0001)
    {
      if (((((background->red % 257) != 0) || ((background->green % 257) != 0)) || ((background->blue % 257) != 0)) || ((background->gray % 257) != 0))
      {
        reductions &= ~0x0001;
      }
    }
    if (reductions & 0x0004)
    {
      if ((background->red != background->green) || (background->red != background->blue))
      {
        reductions &= ~0x0004;
      }
    }
  }
  row_ptr = png_get_rows(png_ptr, info_ptr);
  for (i = 0; i < height; i += 1, row_ptr += 1)
  {
    helper_opng_analyze_bits_1(&reductions, &component_ptr, &j, row_ptr, width, bit_depth, channels, sample_size, offset_alpha);
  }

  return reductions;
}


----------------------------
typedef struct png_info_def png_info
----------------------------
void helper_opng_reduce_bits_1(png_color_16p * const trans_color_ref, png_structp png_ptr, png_infop info_ptr, png_uint_32 reductions)
{
  png_color_16p trans_color = *trans_color_ref;
  if (reductions & 0x0001)
  {
    if (((((trans_color->red % 257) == 0) && ((trans_color->green % 257) == 0)) && ((trans_color->blue % 257) == 0)) && ((trans_color->gray % 257) == 0))
    {
      trans_color->red &= 255;
      trans_color->green &= 255;
      trans_color->blue &= 255;
      trans_color->gray &= 255;
    }
    else
    {
      png_free_data(png_ptr, info_ptr, 0x2000U, -1);
      png_set_invalid(png_ptr, info_ptr, 0x0010U);
    }
  }
  if (reductions & 0x0004)
  {
    if ((trans_color->red == trans_color->green) || (trans_color->red == trans_color->blue))
    {
      trans_color->gray = trans_color->red;
    }
    else
    {
      png_free_data(png_ptr, info_ptr, 0x2000U, -1);
      png_set_invalid(png_ptr, info_ptr, 0x0010U);
    }
  }
  *trans_color_ref = trans_color;
}


----------------------------
typedef unsigned char png_byte
----------------------------
png_bytepp png_get_rows(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    return info_ptr->row_pointers;
  }
  return 0;
}


----------------------------
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


----------------------------
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
typedef struct png_color_16_struct
{
  png_byte index;
  png_uint_16 red;
  png_uint_16 green;
  png_uint_16 blue;
  png_uint_16 gray;
} png_color_16
----------------------------
typedef png_info *png_infop
----------------------------
void helper_opng_reduce_bits_2(png_color_8p * const sig_bits_ref, png_uint_32 reductions)
{
  png_color_8p sig_bits = *sig_bits_ref;
  if (reductions & 0x0001)
  {
    if (sig_bits->red > 8)
    {
      sig_bits->red = 8;
    }
    if (sig_bits->green > 8)
    {
      sig_bits->green = 8;
    }
    if (sig_bits->blue > 8)
    {
      sig_bits->blue = 8;
    }
    if (sig_bits->gray > 8)
    {
      sig_bits->gray = 8;
    }
    if (sig_bits->alpha > 8)
    {
      sig_bits->alpha = 8;
    }
  }
  if (reductions & 0x0004)
  {
    png_byte max_sig_bits = sig_bits->red;
    if (max_sig_bits < sig_bits->green)
    {
      max_sig_bits = sig_bits->green;
    }
    if (max_sig_bits < sig_bits->blue)
    {
      max_sig_bits = sig_bits->blue;
    }
    sig_bits->gray = max_sig_bits;
  }
  *sig_bits_ref = sig_bits;
}


----------------------------
typedef struct png_struct_def png_struct
----------------------------
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


----------------------------
***/


png_uint_32 opng_reduce_image(png_structp png_ptr, png_infop info_ptr, png_uint_32 reductions)
{
  png_uint_32 result;
  int color_type;
  (void) 0;
  if (!opng_validate_image(png_ptr, info_ptr))
  {
    png_warning(png_ptr, "Image reduction requires the presence of all critical information");
    return 0x0000;
  }
  color_type = png_get_color_type(png_ptr, info_ptr);
  result = opng_reduce_bits(png_ptr, info_ptr, reductions);
  if ((color_type == (2 | 1)) && (reductions & ((0x0080 | 0x0200) | 0x0002)))
  {
    result |= opng_reduce_palette(png_ptr, info_ptr, reductions);
  }
  if ((((color_type & (~4)) == 0) && (reductions & 0x0040)) || (((color_type & (~4)) == 2) && (reductions & 0x0010)))
  {
    if (!(result & 0x0080))
    {
      result |= opng_reduce_to_palette(png_ptr, info_ptr, reductions);
    }
  }
  return result;
}


/*** DEPENDENCIES:
png_byte png_get_color_type(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    return info_ptr->color_type;
  }
  return 0;
}


----------------------------
typedef png_struct *png_structp
----------------------------
int opng_validate_image(png_structp png_ptr, png_infop info_ptr)
{
  (void) 0;
  if (png_get_bit_depth(png_ptr, info_ptr) == 0)
  {
    return 0;
  }
  if (png_get_color_type(png_ptr, info_ptr) & 1)
  {
    if (!png_get_valid(png_ptr, info_ptr, 0x0008U))
    {
      return 0;
    }
  }
  if (!png_get_valid(png_ptr, info_ptr, 0x8000U))
  {
    return 0;
  }
  return 1;
}


----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef struct png_info_def png_info
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
typedef png_info *png_infop
----------------------------
typedef struct png_struct_def png_struct
----------------------------
static png_uint_32 opng_reduce_palette(png_structp png_ptr, png_infop info_ptr, png_uint_32 reductions)
{
  png_uint_32 result;
  png_colorp palette;
  png_bytep trans_alpha;
  png_bytepp row_ptr;
  png_uint_32 width;
  png_uint_32 height;
  int bit_depth;
  int color_type;
  int interlace_type;
  int compression_type;
  int filter_type;
  int num_palette;
  int num_trans;
  int last_color_index;
  int last_trans_index;
  png_byte crt_trans_value;
  png_byte last_trans_value;
  png_byte is_used[256];
  png_color_16 gray_trans;
  int is_gray;
  png_color_16p background;
  png_uint_16p hist;
  png_color_8p sig_bits;
  png_uint_32 i;
  png_uint_32 j;
  int k;
  (void) 0;
  result = 0x0000;
  png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type, &interlace_type, &compression_type, &filter_type);
  row_ptr = png_get_rows(png_ptr, info_ptr);
  if (!png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette))
  {
    palette = 0;
    num_palette = 0;
  }
  if (!png_get_tRNS(png_ptr, info_ptr, &trans_alpha, &num_trans, 0))
  {
    trans_alpha = 0;
    num_trans = 0;
  }
  else
    assert((trans_alpha != 0) && (num_trans > 0));
  opng_analyze_sample_usage(png_ptr, info_ptr, is_used);
  is_gray = (reductions & 0x0080) && (bit_depth == 8);
  last_color_index = (last_trans_index = -1);
  for (k = 0; k < 256; k += 1)
  {
    if (!is_used[k])
    {
      continue;
    }
    last_color_index = k;
    if ((k < num_trans) && (trans_alpha[k] < 255))
    {
      last_trans_index = k;
    }
    if (is_gray)
    {
      if ((palette[k].red != palette[k].green) || (palette[k].red != palette[k].blue))
      {
        is_gray = 0;
      }
    }
  }

  assert(last_color_index >= 0);
  assert(last_color_index >= last_trans_index);
  if (last_color_index >= num_palette)
  {
    png_warning(png_ptr, "Too few colors in PLTE");
    opng_realloc_PLTE(png_ptr, info_ptr, last_color_index + 1);
    png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette);
    assert(num_palette == (last_color_index + 1));
    result |= 0x2000;
  }
  if (num_trans > num_palette)
  {
    png_warning(png_ptr, "Too many alpha values in tRNS");
    result |= 0x2000;
  }
  if (is_gray && (last_trans_index >= 0))
  {
    helper_opng_reduce_palette_1(&crt_trans_value, &last_trans_value, &gray_trans, &is_gray, &k, palette, trans_alpha, last_color_index, last_trans_index, is_used);
  }
  if ((num_trans > 0) && (last_trans_index < 0))
  {
    num_trans = 0;
    png_free_data(png_ptr, info_ptr, 0x2000U, -1);
    png_set_invalid(png_ptr, info_ptr, 0x0010U);
    result |= 0x0200;
  }
  if (reductions & 0x0200)
  {
    if (num_palette != (last_color_index + 1))
    {
      opng_realloc_PLTE(png_ptr, info_ptr, last_color_index + 1);
      png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette);
      assert(num_palette == (last_color_index + 1));
      result |= 0x0200;
    }
    if ((num_trans > 0) && (num_trans != (last_trans_index + 1)))
    {
      opng_realloc_tRNS(png_ptr, info_ptr, last_trans_index + 1);
      png_get_tRNS(png_ptr, info_ptr, &trans_alpha, &num_trans, 0);
      assert(num_trans == (last_trans_index + 1));
      result |= 0x0200;
    }
  }
  if (reductions & 0x0002)
  {
    result |= opng_reduce_palette_bits(png_ptr, info_ptr, reductions);
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);
  }
  if ((bit_depth < 8) || (!is_gray))
  {
    return result;
  }
  for (i = 0; i < height; i += 1)
  {
    for (j = 0; j < width; j += 1)
    {
      row_ptr[i][j] = palette[row_ptr[i][j]].red;
    }

  }

  if (num_trans > 0)
  {
    png_set_tRNS(png_ptr, info_ptr, 0, 0, &gray_trans);
  }
  if (png_get_bKGD(png_ptr, info_ptr, &background))
  {
    background->gray = palette[background->index].red;
  }
  if (png_get_hIST(png_ptr, info_ptr, &hist))
  {
    png_free_data(png_ptr, info_ptr, 0x0008U, -1);
    png_set_invalid(png_ptr, info_ptr, 0x0040U);
  }
  if (png_get_sBIT(png_ptr, info_ptr, &sig_bits))
  {
    png_byte max_sig_bits = sig_bits->red;
    if (max_sig_bits < sig_bits->green)
    {
      max_sig_bits = sig_bits->green;
    }
    if (max_sig_bits < sig_bits->blue)
    {
      max_sig_bits = sig_bits->blue;
    }
    sig_bits->gray = max_sig_bits;
  }
  png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, 0, interlace_type, compression_type, filter_type);
  png_free_data(png_ptr, info_ptr, 0x1000U, -1);
  png_set_invalid(png_ptr, info_ptr, 0x0008U);
  return 0x0080;
}


----------------------------
static png_uint_32 opng_reduce_to_palette(png_structp png_ptr, png_infop info_ptr, png_uint_32 reductions)
{
  png_uint_32 result;
  png_row_info row_info;
  png_bytepp row_ptr;
  png_bytep sample_ptr;
  png_bytep alpha_row;
  png_uint_32 height;
  png_uint_32 width;
  int color_type;
  int interlace_type;
  int compression_type;
  int filter_type;
  int src_bit_depth;
  int dest_bit_depth;
  int channels;
  png_color palette[256];
  png_byte trans_alpha[256];
  png_color_16p trans_color;
  int num_palette;
  int num_trans;
  int index;
  unsigned int gray;
  unsigned int red;
  unsigned int green;
  unsigned int blue;
  unsigned int alpha;
  unsigned int prev_gray;
  unsigned int prev_red;
  unsigned int prev_green;
  unsigned int prev_blue;
  unsigned int prev_alpha;
  png_color_16p background;
  png_uint_32 i;
  png_uint_32 j;
  (void) 0;
  png_get_IHDR(png_ptr, info_ptr, &width, &height, &src_bit_depth, &color_type, &interlace_type, &compression_type, &filter_type);
  if (src_bit_depth != 8)
  {
    return 0x0000;
  }
  assert(!(color_type & 1));
  row_ptr = png_get_rows(png_ptr, info_ptr);
  channels = png_get_channels(png_ptr, info_ptr);
  alpha_row = (png_bytep) png_malloc(png_ptr, width);
  row_info.width = width;
  row_info.rowbytes = 0;
  row_info.color_type = (png_byte) color_type;
  row_info.bit_depth = (png_byte) src_bit_depth;
  row_info.channels = (png_byte) channels;
  row_info.pixel_depth = 0;
  num_palette = (num_trans = 0);
  trans_color = 0;
  png_get_tRNS(png_ptr, info_ptr, 0, 0, &trans_color);
  prev_gray = (prev_red = (prev_green = (prev_blue = (prev_alpha = (unsigned int) (-1)))));
  for (i = 0; i < height; i += 1, row_ptr += 1)
  {
    helper_opng_reduce_to_palette_1(&sample_ptr, &gray, &red, &green, &blue, &alpha, &prev_gray, &prev_red, &prev_green, &prev_blue, &prev_alpha, &i, &j, row_info, row_ptr, alpha_row, height, width, color_type, channels, palette, trans_alpha, trans_color, num_palette, num_trans, index);
  }

  if ((num_palette >= 0) && png_get_bKGD(png_ptr, info_ptr, &background))
  {
    if (color_type & 2)
    {
      red = background->red;
      green = background->green;
      blue = background->blue;
    }
    else
      red = (green = (blue = background->gray));
    if (((red > 255) || (green > 255)) || (blue > 255))
    {
      png_warning(png_ptr, "Invalid colors in bKGD");
      png_set_invalid(png_ptr, info_ptr, 0x0020U);
    }
    else
    {
      opng_insert_palette_entry(palette, &num_palette, trans_alpha, &num_trans, 256, red, green, blue, (unsigned int) (-1), &index);
      if (index >= 0)
      {
        background->index = (png_byte) index;
      }
    }
  }
  if (num_palette >= 0)
  {
    assert((num_palette > 0) && (num_palette <= 256));
    assert((num_trans >= 0) && (num_trans <= num_palette));
    if (num_palette <= 2)
    {
      dest_bit_depth = 1;
    }
    else
      if (num_palette <= 4)
    {
      dest_bit_depth = 2;
    }
    else
      if (num_palette <= 16)
    {
      dest_bit_depth = 4;
    }
    else
      dest_bit_depth = 8;
    if (((channels * 8) == dest_bit_depth) || (((((((3 * num_palette) + num_trans) * 8) / ((channels * 8) - dest_bit_depth)) / width) / height) >= 1))
    {
      num_palette = -1;
    }
  }
  if (num_palette < 0)
  {
    png_free(png_ptr, alpha_row);
    return 0x0000;
  }
  row_ptr = png_get_rows(png_ptr, info_ptr);
  index = -1;
  prev_red = (prev_green = (prev_blue = (prev_alpha = (unsigned int) (-1))));
  for (i = 0; i < height; i += 1, row_ptr += 1)
  {
    helper_opng_reduce_to_palette_2(&row_ptr, &sample_ptr, &index, &gray, &red, &green, &blue, &alpha, &prev_gray, &prev_red, &prev_green, &prev_blue, &prev_alpha, &j, row_info, alpha_row, width, color_type, channels, palette, trans_alpha, trans_color, num_palette, num_trans);
  }

  png_set_IHDR(png_ptr, info_ptr, width, height, 8, 2 | 1, interlace_type, compression_type, filter_type);
  png_set_PLTE(png_ptr, info_ptr, palette, num_palette);
  if (num_trans > 0)
  {
    png_set_tRNS(png_ptr, info_ptr, trans_alpha, num_trans, 0);
  }
  png_free(png_ptr, alpha_row);
  result = 0x0010;
  if (reductions & 0x0002)
  {
    result |= opng_reduce_palette_bits(png_ptr, info_ptr, reductions);
  }
  return result;
}


----------------------------
static png_uint_32 opng_reduce_bits(png_structp png_ptr, png_infop info_ptr, png_uint_32 reductions)
{
  png_bytepp row_ptr;
  png_bytep src_ptr;
  png_bytep dest_ptr;
  png_uint_32 width;
  png_uint_32 height;
  int interlace_type;
  int compression_type;
  int filter_type;
  int src_bit_depth;
  int dest_bit_depth;
  int src_byte_depth;
  int dest_byte_depth;
  int src_color_type;
  int dest_color_type;
  int src_channels;
  int dest_channels;
  int src_sample_size;
  int dest_sample_size;
  int tran_tbl[8];
  png_color_16p trans_color;
  png_color_16p background;
  png_color_8p sig_bits;
  png_uint_32 i;
  png_uint_32 j;
  int k;
  (void) 0;
  reductions = opng_analyze_bits(png_ptr, info_ptr, reductions);
  if (reductions == 0x0000)
  {
    return 0x0000;
  }
  png_get_IHDR(png_ptr, info_ptr, &width, &height, &src_bit_depth, &src_color_type, &interlace_type, &compression_type, &filter_type);
  assert(src_bit_depth >= 8);
  if (reductions & 0x0001)
  {
    assert(src_bit_depth == 16);
    dest_bit_depth = 8;
  }
  else
    dest_bit_depth = src_bit_depth;
  src_byte_depth = src_bit_depth / 8;
  dest_byte_depth = dest_bit_depth / 8;
  dest_color_type = src_color_type;
  if (reductions & 0x0004)
  {
    assert(src_color_type & 2);
    dest_color_type &= ~2;
  }
  if (reductions & 0x0008)
  {
    assert(src_color_type & 4);
    dest_color_type &= ~4;
  }
  src_channels = png_get_channels(png_ptr, info_ptr);
  dest_channels = ((dest_color_type & 2) ? (3) : (1)) + ((dest_color_type & 4) ? (1) : (0));
  src_sample_size = src_channels * src_byte_depth;
  dest_sample_size = dest_channels * dest_byte_depth;
  for (k = 0; k < (4 * dest_byte_depth); k += 1)
  {
    tran_tbl[k] = (k * src_bit_depth) / dest_bit_depth;
  }

  if ((reductions & 0x0004) && (dest_color_type & 4))
  {
    tran_tbl[dest_byte_depth] = tran_tbl[3 * dest_byte_depth];
    if (dest_byte_depth == 2)
    {
      tran_tbl[dest_byte_depth + 1] = tran_tbl[(3 * dest_byte_depth) + 1];
    }
  }
  assert(src_sample_size > dest_sample_size);
  row_ptr = png_get_rows(png_ptr, info_ptr);
  for (i = 0; i < height; i += 1, row_ptr += 1)
  {
    src_ptr = (dest_ptr = *row_ptr);
    for (j = 0; j < width; j += 1)
    {
      for (k = 0; k < dest_sample_size; k += 1)
      {
        dest_ptr[k] = src_ptr[tran_tbl[k]];
      }

      src_ptr += src_sample_size;
      dest_ptr += dest_sample_size;
    }

  }

  if (png_get_tRNS(png_ptr, info_ptr, 0, 0, &trans_color))
  {
    helper_opng_reduce_bits_1(&trans_color, png_ptr, info_ptr, reductions);
  }
  if (png_get_bKGD(png_ptr, info_ptr, &background))
  {
    if (reductions & 0x0001)
    {
      background->red &= 255;
      background->green &= 255;
      background->blue &= 255;
      background->gray &= 255;
    }
    if (reductions & 0x0004)
    {
      background->gray = background->red;
    }
  }
  if (png_get_sBIT(png_ptr, info_ptr, &sig_bits))
  {
    helper_opng_reduce_bits_2(&sig_bits, reductions);
  }
  png_set_IHDR(png_ptr, info_ptr, width, height, dest_bit_depth, dest_color_type, interlace_type, compression_type, filter_type);
  return reductions;
}


----------------------------
***/


