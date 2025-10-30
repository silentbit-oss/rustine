void png_set_flush(png_structrp png_ptr, int nrows)
{
  (void) 0;
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->flush_dist = (nrows < 0) ? (0) : ((png_uint_32) nrows);
}


/*** DEPENDENCIES:
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


void png_set_compression_level(png_structrp png_ptr, int level)
{
  (void) 0;
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->zlib_level = level;
}


/*** DEPENDENCIES:
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


void png_set_compression_mem_level(png_structrp png_ptr, int mem_level)
{
  (void) 0;
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->zlib_mem_level = mem_level;
}


/*** DEPENDENCIES:
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


void png_set_compression_strategy(png_structrp png_ptr, int strategy)
{
  (void) 0;
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->flags |= 0x0001U;
  png_ptr->zlib_strategy = strategy;
}


/*** DEPENDENCIES:
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


static void png_write_destroy(png_structrp png_ptr)
{
  (void) 0;
  if ((png_ptr->flags & 0x0002U) != 0)
  {
    deflateEnd(&png_ptr->zstream);
  }
  png_free_buffer_list(png_ptr, &png_ptr->zbuffer_list);
  png_free(png_ptr, png_ptr->row_buf);
  png_ptr->row_buf = 0;
  png_free(png_ptr, png_ptr->prev_row);
  png_free(png_ptr, png_ptr->try_row);
  png_free(png_ptr, png_ptr->tst_row);
  png_ptr->prev_row = 0;
  png_ptr->try_row = 0;
  png_ptr->tst_row = 0;
  png_free(png_ptr, png_ptr->chunk_list);
  png_ptr->chunk_list = 0;
}


/*** DEPENDENCIES:
int deflateEnd(z_streamp strm)
{
  int status;
  if (deflateStateCheck(strm))
  {
    return -2;
  }
  status = strm->state->status;
  {
    if (strm->state->pending_buf)
    {
      (*strm->zfree)(strm->opaque, (voidpf) strm->state->pending_buf);
    }
  }
  ;
  {
    if (strm->state->head)
    {
      (*strm->zfree)(strm->opaque, (voidpf) strm->state->head);
    }
  }
  ;
  {
    if (strm->state->prev)
    {
      (*strm->zfree)(strm->opaque, (voidpf) strm->state->prev);
    }
  }
  ;
  {
    if (strm->state->window)
    {
      (*strm->zfree)(strm->opaque, (voidpf) strm->state->window);
    }
  }
  ;
  (*strm->zfree)(strm->opaque, (voidpf) strm->state);
  strm->state = 0;
  return (status == 113) ? (-3) : (0);
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
***/


void png_destroy_write_struct(png_structpp png_ptr_ptr, png_infopp info_ptr_ptr)
{
  (void) 0;
  if (png_ptr_ptr != 0)
  {
    png_structrp png_ptr = *png_ptr_ptr;
    if (png_ptr != 0)
    {
      png_destroy_info_struct(png_ptr, info_ptr_ptr);
      *png_ptr_ptr = 0;
      png_write_destroy(png_ptr);
      png_destroy_png_struct(png_ptr);
    }
  }
}


/*** DEPENDENCIES:
typedef png_struct **png_structpp
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
static void png_write_destroy(png_structrp png_ptr)
{
  (void) 0;
  if ((png_ptr->flags & 0x0002U) != 0)
  {
    deflateEnd(&png_ptr->zstream);
  }
  png_free_buffer_list(png_ptr, &png_ptr->zbuffer_list);
  png_free(png_ptr, png_ptr->row_buf);
  png_ptr->row_buf = 0;
  png_free(png_ptr, png_ptr->prev_row);
  png_free(png_ptr, png_ptr->try_row);
  png_free(png_ptr, png_ptr->tst_row);
  png_ptr->prev_row = 0;
  png_ptr->try_row = 0;
  png_ptr->tst_row = 0;
  png_free(png_ptr, png_ptr->chunk_list);
  png_ptr->chunk_list = 0;
}


----------------------------
***/


// hint:  ['png_ptr_ref is a mutable refrence to png_structrp', 'filters_ref is a mutable refrence to int']
void helper_helper_png_set_filter_1_1(png_structrp * const png_ptr_ref, int * const filters_ref)
{
  png_structrp png_ptr = *png_ptr_ref;
  int filters = *filters_ref;
  int num_filters;
  png_alloc_size_t buf_size;
  if (png_ptr->height == 1)
  {
    filters &= ~((0x20 | 0x40) | 0x80);
  }
  if (png_ptr->width == 1)
  {
    filters &= ~((0x10 | 0x40) | 0x80);
  }
  if (((filters & ((0x20 | 0x40) | 0x80)) != 0) && (png_ptr->prev_row == 0))
  {
    png_app_warning(png_ptr, "png_set_filter: UP/AVG/PAETH cannot be added after start");
    filters &= ~((0x20 | 0x40) | 0x80);
  }
  num_filters = 0;
  if (filters & 0x10)
  {
    num_filters += 1;
  }
  if (filters & 0x20)
  {
    num_filters += 1;
  }
  if (filters & 0x40)
  {
    num_filters += 1;
  }
  if (filters & 0x80)
  {
    num_filters += 1;
  }
  buf_size = (((png_ptr->usr_channels * png_ptr->usr_bit_depth) >= 8) ? (((size_t) png_ptr->width) * (((size_t) (png_ptr->usr_channels * png_ptr->usr_bit_depth)) >> 3)) : (((((size_t) png_ptr->width) * ((size_t) (png_ptr->usr_channels * png_ptr->usr_bit_depth))) + 7) >> 3)) + 1;
  if (png_ptr->try_row == 0)
  {
    png_ptr->try_row = png_malloc(png_ptr, buf_size);
  }
  if (num_filters > 1)
  {
    if (png_ptr->tst_row == 0)
    {
      png_ptr->tst_row = png_malloc(png_ptr, buf_size);
    }
  }
  *png_ptr_ref = png_ptr;
  *filters_ref = filters;
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
typedef size_t png_alloc_size_t
----------------------------
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
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


// hint:  ['png_ptr_ref is a mutable refrence to png_structrp', 'filters_ref is a mutable refrence to int']
void helper_png_set_filter_1(png_structrp * const png_ptr_ref, int * const filters_ref)
{
  png_structrp png_ptr = *png_ptr_ref;
  int filters = *filters_ref;
  switch (filters & (((((0x08 | 0x10) | 0x20) | 0x40) | 0x80) | 0x07))
  {
    case 5:

    case 6:

    case 7:
    {
      png_app_error(png_ptr, "Unknown row filter for method 0");
    }

    case 0:
    {
      png_ptr->do_filter = 0x08;
      break;
    }

    case 1:
    {
      png_ptr->do_filter = 0x10;
      break;
    }

    case 2:
    {
      png_ptr->do_filter = 0x20;
      break;
    }

    case 3:
    {
      png_ptr->do_filter = 0x40;
      break;
    }

    case 4:
    {
      png_ptr->do_filter = 0x80;
      break;
    }

    default:
    {
      png_ptr->do_filter = (png_byte) filters;
      break;
    }

  }

  if (png_ptr->row_buf != 0)
  {
    helper_helper_png_set_filter_1_1(&png_ptr, &filters);
  }
  png_ptr->do_filter = (png_byte) filters;
  *png_ptr_ref = png_ptr;
  *filters_ref = filters;
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
void helper_helper_png_set_filter_1_1(png_structrp * const png_ptr_ref, int * const filters_ref)
{
  png_structrp png_ptr = *png_ptr_ref;
  int filters = *filters_ref;
  int num_filters;
  png_alloc_size_t buf_size;
  if (png_ptr->height == 1)
  {
    filters &= ~((0x20 | 0x40) | 0x80);
  }
  if (png_ptr->width == 1)
  {
    filters &= ~((0x10 | 0x40) | 0x80);
  }
  if (((filters & ((0x20 | 0x40) | 0x80)) != 0) && (png_ptr->prev_row == 0))
  {
    png_app_warning(png_ptr, "png_set_filter: UP/AVG/PAETH cannot be added after start");
    filters &= ~((0x20 | 0x40) | 0x80);
  }
  num_filters = 0;
  if (filters & 0x10)
  {
    num_filters += 1;
  }
  if (filters & 0x20)
  {
    num_filters += 1;
  }
  if (filters & 0x40)
  {
    num_filters += 1;
  }
  if (filters & 0x80)
  {
    num_filters += 1;
  }
  buf_size = (((png_ptr->usr_channels * png_ptr->usr_bit_depth) >= 8) ? (((size_t) png_ptr->width) * (((size_t) (png_ptr->usr_channels * png_ptr->usr_bit_depth)) >> 3)) : (((((size_t) png_ptr->width) * ((size_t) (png_ptr->usr_channels * png_ptr->usr_bit_depth))) + 7) >> 3)) + 1;
  if (png_ptr->try_row == 0)
  {
    png_ptr->try_row = png_malloc(png_ptr, buf_size);
  }
  if (num_filters > 1)
  {
    if (png_ptr->tst_row == 0)
    {
      png_ptr->tst_row = png_malloc(png_ptr, buf_size);
    }
  }
  *png_ptr_ref = png_ptr;
  *filters_ref = filters;
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


void png_set_filter(png_structrp png_ptr, int method, int filters)
{
  (void) 0;
  if (png_ptr == 0)
  {
    return;
  }
  if (method == 0)
  {
    helper_png_set_filter_1(&png_ptr, &filters);
  }
  else
    png_error(png_ptr, "Unknown custom filter method");
}


/*** DEPENDENCIES:
void helper_png_set_filter_1(png_structrp * const png_ptr_ref, int * const filters_ref)
{
  png_structrp png_ptr = *png_ptr_ref;
  int filters = *filters_ref;
  switch (filters & (((((0x08 | 0x10) | 0x20) | 0x40) | 0x80) | 0x07))
  {
    case 5:

    case 6:

    case 7:
    {
      png_app_error(png_ptr, "Unknown row filter for method 0");
    }

    case 0:
    {
      png_ptr->do_filter = 0x08;
      break;
    }

    case 1:
    {
      png_ptr->do_filter = 0x10;
      break;
    }

    case 2:
    {
      png_ptr->do_filter = 0x20;
      break;
    }

    case 3:
    {
      png_ptr->do_filter = 0x40;
      break;
    }

    case 4:
    {
      png_ptr->do_filter = 0x80;
      break;
    }

    default:
    {
      png_ptr->do_filter = (png_byte) filters;
      break;
    }

  }

  if (png_ptr->row_buf != 0)
  {
    helper_helper_png_set_filter_1_1(&png_ptr, &filters);
  }
  png_ptr->do_filter = (png_byte) filters;
  *png_ptr_ref = png_ptr;
  *filters_ref = filters;
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
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


void png_set_compression_window_bits(png_structrp png_ptr, int window_bits)
{
  if (png_ptr == 0)
  {
    return;
  }
  if (window_bits > 15)
  {
    png_warning(png_ptr, "Only compression windows <= 32k supported by PNG");
    window_bits = 15;
  }
  else
    if (window_bits < 8)
  {
    png_warning(png_ptr, "Only compression windows >= 256 supported by PNG");
    window_bits = 8;
  }
  png_ptr->zlib_window_bits = window_bits;
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


png_structp png_create_write_struct(png_const_charp user_png_ver, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warn_fn)
{
  png_structrp png_ptr = png_create_png_struct(user_png_ver, error_ptr, error_fn, warn_fn, 0, 0, 0);
  if (png_ptr != 0)
  {
    png_ptr->zbuffer_size = 8192;
    png_ptr->zlib_strategy = 1;
    png_ptr->zlib_level = -1;
    png_ptr->zlib_mem_level = 8;
    png_ptr->zlib_window_bits = 15;
    png_ptr->zlib_method = 8;
    png_ptr->flags |= 0x200000U;
    png_set_write_fn(png_ptr, 0, 0, 0);
  }
  return png_ptr;
}


/*** DEPENDENCIES:
typedef void *voidp
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
void png_set_write_fn(png_structrp png_ptr, png_voidp io_ptr, png_rw_ptr write_data_fn, png_flush_ptr output_flush_fn)
{
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->io_ptr = io_ptr;
  if (write_data_fn != 0)
  {
    png_ptr->write_data_fn = write_data_fn;
  }
  else
    png_ptr->write_data_fn = png_default_write_data;
  if (output_flush_fn != 0)
  {
    png_ptr->output_flush_fn = output_flush_fn;
  }
  else
    png_ptr->output_flush_fn = png_default_flush;
  if (png_ptr->read_data_fn != 0)
  {
    png_ptr->read_data_fn = 0;
    png_warning(png_ptr, "Can't set both read_data_fn and write_data_fn in the same structure");
  }
}


----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef const char *png_const_charp
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef void *png_voidp
----------------------------
***/


void helper_png_write_row_1(png_structrp png_ptr)
{
  switch (png_ptr->pass)
  {
    case 0:
    {
      if ((png_ptr->row_number & 0x07) != 0)
      {
        png_write_finish_row(png_ptr);
        return;
      }
      break;
    }

    case 1:
    {
      if (((png_ptr->row_number & 0x07) != 0) || (png_ptr->width < 5))
      {
        png_write_finish_row(png_ptr);
        return;
      }
      break;
    }

    case 2:
    {
      if ((png_ptr->row_number & 0x07) != 4)
      {
        png_write_finish_row(png_ptr);
        return;
      }
      break;
    }

    case 3:
    {
      if (((png_ptr->row_number & 0x03) != 0) || (png_ptr->width < 3))
      {
        png_write_finish_row(png_ptr);
        return;
      }
      break;
    }

    case 4:
    {
      if ((png_ptr->row_number & 0x03) != 2)
      {
        png_write_finish_row(png_ptr);
        return;
      }
      break;
    }

    case 5:
    {
      if (((png_ptr->row_number & 0x01) != 0) || (png_ptr->width < 2))
      {
        png_write_finish_row(png_ptr);
        return;
      }
      break;
    }

    case 6:
    {
      if ((png_ptr->row_number & 0x01) == 0)
      {
        png_write_finish_row(png_ptr);
        return;
      }
      break;
    }

    default:
    {
      break;
    }

  }

}


/*** DEPENDENCIES:
void png_write_finish_row(png_structrp png_ptr)
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
    if ((png_ptr->transformations & 0x0002U) != 0)
    {
      png_ptr->pass += 1;
    }
    else
    {
      do
      {
        png_ptr->pass += 1;
        if (png_ptr->pass >= 7)
        {
          break;
        }
        png_ptr->usr_width = (((png_ptr->width + png_pass_inc[png_ptr->pass]) - 1) - png_pass_start[png_ptr->pass]) / png_pass_inc[png_ptr->pass];
        png_ptr->num_rows = (((png_ptr->height + png_pass_yinc[png_ptr->pass]) - 1) - png_pass_ystart[png_ptr->pass]) / png_pass_yinc[png_ptr->pass];
        if ((png_ptr->transformations & 0x0002U) != 0)
        {
          break;
        }
      }
      while ((png_ptr->usr_width == 0) || (png_ptr->num_rows == 0));
    }
    if (png_ptr->pass < 7)
    {
      if (png_ptr->prev_row != 0)
      {
        memset(png_ptr->prev_row, 0, (((png_ptr->usr_channels * png_ptr->usr_bit_depth) >= 8) ? (((size_t) png_ptr->width) * (((size_t) (png_ptr->usr_channels * png_ptr->usr_bit_depth)) >> 3)) : (((((size_t) png_ptr->width) * ((size_t) (png_ptr->usr_channels * png_ptr->usr_bit_depth))) + 7) >> 3)) + 1);
      }
      return;
    }
  }
  png_compress_IDAT(png_ptr, 0, 0, 4);
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


void png_write_flush(png_structrp png_ptr)
{
  (void) 0;
  if (png_ptr == 0)
  {
    return;
  }
  if (png_ptr->row_number >= png_ptr->num_rows)
  {
    return;
  }
  png_compress_IDAT(png_ptr, 0, 0, 2);
  png_ptr->flush_rows = 0;
  png_flush(png_ptr);
}


/*** DEPENDENCIES:
void png_flush(png_structrp png_ptr)
{
  if (png_ptr->output_flush_fn != 0)
  {
    (*png_ptr->output_flush_fn)(png_ptr);
  }
}


----------------------------
void png_compress_IDAT(png_structrp png_ptr, png_const_bytep input, png_alloc_size_t input_len, int flush)
{
  if (png_ptr->zowner != ((((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0)))
  {
    if (png_ptr->zbuffer_list == 0)
    {
      png_ptr->zbuffer_list = png_malloc(png_ptr, offsetof(png_compression_buffer, output) + png_ptr->zbuffer_size);
      png_ptr->zbuffer_list->next = 0;
    }
    else
      png_free_buffer_list(png_ptr, &png_ptr->zbuffer_list->next);
    if (png_deflate_claim(png_ptr, (((((png_uint_32) 73) << 24) | (((png_uint_32) 68) << 16)) | (((png_uint_32) 65) << 8)) | (((png_uint_32) 84) << 0), png_image_size(png_ptr)) != 0)
    {
      png_error(png_ptr, png_ptr->zstream.msg);
    }
    png_ptr->zstream.next_out = png_ptr->zbuffer_list->output;
    png_ptr->zstream.avail_out = png_ptr->zbuffer_size;
  }
  png_ptr->zstream.next_in = input;
  png_ptr->zstream.avail_in = 0;
  for (;;)
  {
    helper_png_compress_IDAT_1(&png_ptr, &input_len, flush);
  }

}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


void png_write_row(png_structrp png_ptr, png_const_bytep row)
{
  png_row_info row_info;
  if (png_ptr == 0)
  {
    return;
  }
  (void) 0;
  if ((png_ptr->row_number == 0) && (png_ptr->pass == 0))
  {
    if ((png_ptr->mode & 0x400U) == 0)
    {
      png_error(png_ptr, "png_write_info was never called before png_write_row");
    }
    png_write_start_row(png_ptr);
  }
  if ((png_ptr->interlaced != 0) && ((png_ptr->transformations & 0x0002U) != 0))
  {
    helper_png_write_row_1(png_ptr);
  }
  row_info.color_type = png_ptr->color_type;
  row_info.width = png_ptr->usr_width;
  row_info.channels = png_ptr->usr_channels;
  row_info.bit_depth = png_ptr->usr_bit_depth;
  row_info.pixel_depth = (png_byte) (row_info.bit_depth * row_info.channels);
  row_info.rowbytes = (row_info.pixel_depth >= 8) ? (((size_t) row_info.width) * (((size_t) row_info.pixel_depth) >> 3)) : (((((size_t) row_info.width) * ((size_t) row_info.pixel_depth)) + 7) >> 3);
  (void) 0;
  (void) 0;
  (void) 0;
  (void) 0;
  (void) 0;
  (void) 0;
  memcpy(png_ptr->row_buf + 1, row, row_info.rowbytes);
  if ((png_ptr->interlaced && (png_ptr->pass < 6)) && ((png_ptr->transformations & 0x0002U) != 0))
  {
    png_do_write_interlace(&row_info, png_ptr->row_buf + 1, png_ptr->pass);
    if (row_info.width == 0)
    {
      png_write_finish_row(png_ptr);
      return;
    }
  }
  if ((row_info.pixel_depth != png_ptr->pixel_depth) || (row_info.pixel_depth != png_ptr->transformed_pixel_depth))
  {
    png_error(png_ptr, "internal write transform logic error");
  }
  if ((row_info.color_type == (2 | 1)) && (png_ptr->num_palette_max >= 0))
  {
    png_do_check_palette_indexes(png_ptr, &row_info);
  }
  png_write_find_filter(png_ptr, &row_info);
  if (png_ptr->write_row_fn != 0)
  {
    (*png_ptr->write_row_fn)(png_ptr, png_ptr->row_number, png_ptr->pass);
  }
}


/*** DEPENDENCIES:
typedef const png_byte *png_const_bytep
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
void png_write_finish_row(png_structrp png_ptr)
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
    if ((png_ptr->transformations & 0x0002U) != 0)
    {
      png_ptr->pass += 1;
    }
    else
    {
      do
      {
        png_ptr->pass += 1;
        if (png_ptr->pass >= 7)
        {
          break;
        }
        png_ptr->usr_width = (((png_ptr->width + png_pass_inc[png_ptr->pass]) - 1) - png_pass_start[png_ptr->pass]) / png_pass_inc[png_ptr->pass];
        png_ptr->num_rows = (((png_ptr->height + png_pass_yinc[png_ptr->pass]) - 1) - png_pass_ystart[png_ptr->pass]) / png_pass_yinc[png_ptr->pass];
        if ((png_ptr->transformations & 0x0002U) != 0)
        {
          break;
        }
      }
      while ((png_ptr->usr_width == 0) || (png_ptr->num_rows == 0));
    }
    if (png_ptr->pass < 7)
    {
      if (png_ptr->prev_row != 0)
      {
        memset(png_ptr->prev_row, 0, (((png_ptr->usr_channels * png_ptr->usr_bit_depth) >= 8) ? (((size_t) png_ptr->width) * (((size_t) (png_ptr->usr_channels * png_ptr->usr_bit_depth)) >> 3)) : (((((size_t) png_ptr->width) * ((size_t) (png_ptr->usr_channels * png_ptr->usr_bit_depth))) + 7) >> 3)) + 1);
      }
      return;
    }
  }
  png_compress_IDAT(png_ptr, 0, 0, 4);
}


----------------------------
void png_write_start_row(png_structrp png_ptr)
{
  static const png_byte png_pass_start[7] = {0, 4, 0, 2, 0, 1, 0};
  static const png_byte png_pass_inc[7] = {8, 8, 4, 4, 2, 2, 1};
  static const png_byte png_pass_ystart[7] = {0, 0, 4, 0, 2, 0, 1};
  static const png_byte png_pass_yinc[7] = {8, 8, 8, 4, 4, 2, 2};
  png_alloc_size_t buf_size;
  int usr_pixel_depth;
  png_byte filters;
  (void) 0;
  usr_pixel_depth = png_ptr->usr_channels * png_ptr->usr_bit_depth;
  buf_size = ((usr_pixel_depth >= 8) ? (((size_t) png_ptr->width) * (((size_t) usr_pixel_depth) >> 3)) : (((((size_t) png_ptr->width) * ((size_t) usr_pixel_depth)) + 7) >> 3)) + 1;
  png_ptr->transformed_pixel_depth = png_ptr->pixel_depth;
  png_ptr->maximum_pixel_depth = (png_byte) usr_pixel_depth;
  png_ptr->row_buf = png_malloc(png_ptr, buf_size);
  png_ptr->row_buf[0] = 0;
  filters = png_ptr->do_filter;
  if (png_ptr->height == 1)
  {
    filters &= 0xff & (~((0x20 | 0x40) | 0x80));
  }
  if (png_ptr->width == 1)
  {
    filters &= 0xff & (~((0x10 | 0x40) | 0x80));
  }
  if (filters == 0)
  {
    filters = 0x08;
  }
  png_ptr->do_filter = filters;
  if (((filters & (((0x10 | 0x20) | 0x40) | 0x80)) != 0) && (png_ptr->try_row == 0))
  {
    helper_png_write_start_row_1(&png_ptr, buf_size, filters);
  }
  if ((filters & ((0x40 | 0x20) | 0x80)) != 0)
  {
    png_ptr->prev_row = png_calloc(png_ptr, buf_size);
  }
  if (png_ptr->interlaced != 0)
  {
    if ((png_ptr->transformations & 0x0002U) == 0)
    {
      png_ptr->num_rows = (((png_ptr->height + png_pass_yinc[0]) - 1) - png_pass_ystart[0]) / png_pass_yinc[0];
      png_ptr->usr_width = (((png_ptr->width + png_pass_inc[0]) - 1) - png_pass_start[0]) / png_pass_inc[0];
    }
    else
    {
      png_ptr->num_rows = png_ptr->height;
      png_ptr->usr_width = png_ptr->width;
    }
  }
  else
  {
    png_ptr->num_rows = png_ptr->height;
    png_ptr->usr_width = png_ptr->width;
  }
}


----------------------------
void helper_png_write_row_1(png_structrp png_ptr)
{
  switch (png_ptr->pass)
  {
    case 0:
    {
      if ((png_ptr->row_number & 0x07) != 0)
      {
        png_write_finish_row(png_ptr);
        return;
      }
      break;
    }

    case 1:
    {
      if (((png_ptr->row_number & 0x07) != 0) || (png_ptr->width < 5))
      {
        png_write_finish_row(png_ptr);
        return;
      }
      break;
    }

    case 2:
    {
      if ((png_ptr->row_number & 0x07) != 4)
      {
        png_write_finish_row(png_ptr);
        return;
      }
      break;
    }

    case 3:
    {
      if (((png_ptr->row_number & 0x03) != 0) || (png_ptr->width < 3))
      {
        png_write_finish_row(png_ptr);
        return;
      }
      break;
    }

    case 4:
    {
      if ((png_ptr->row_number & 0x03) != 2)
      {
        png_write_finish_row(png_ptr);
        return;
      }
      break;
    }

    case 5:
    {
      if (((png_ptr->row_number & 0x01) != 0) || (png_ptr->width < 2))
      {
        png_write_finish_row(png_ptr);
        return;
      }
      break;
    }

    case 6:
    {
      if ((png_ptr->row_number & 0x01) == 0)
      {
        png_write_finish_row(png_ptr);
        return;
      }
      break;
    }

    default:
    {
      break;
    }

  }

}


----------------------------
void png_do_write_interlace(png_row_infop row_info, png_bytep row, int pass)
{
  static const png_byte png_pass_start[7] = {0, 4, 0, 2, 0, 1, 0};
  static const png_byte png_pass_inc[7] = {8, 8, 4, 4, 2, 2, 1};
  (void) 0;
  if (pass < 6)
  {
    helper_png_do_write_interlace_1(&row_info, row, pass, png_pass_start, png_pass_inc);
  }
}


----------------------------
void png_do_check_palette_indexes(png_structrp png_ptr, png_row_infop row_info)
{
  if ((png_ptr->num_palette < (1 << row_info->bit_depth)) && (png_ptr->num_palette > 0))
  {
    helper_png_do_check_palette_indexes_1(&png_ptr, row_info);
  }
}


----------------------------
void png_write_find_filter(png_structrp png_ptr, png_row_infop row_info)
{
  unsigned int filter_to_do = png_ptr->do_filter;
  png_bytep row_buf;
  png_bytep best_row;
  png_uint_32 bpp;
  size_t mins;
  size_t row_bytes = row_info->rowbytes;
  (void) 0;
  bpp = (row_info->pixel_depth + 7) >> 3;
  row_buf = png_ptr->row_buf;
  mins = ((size_t) (-1)) - 256;
  best_row = png_ptr->row_buf;
  if ((((size_t) (-1)) / 128) <= row_bytes)
  {
    filter_to_do &= 0U - filter_to_do;
  }
  else
    if (((filter_to_do & 0x08) != 0) && (filter_to_do != 0x08))
  {
    png_bytep rp;
    size_t sum = 0;
    size_t i;
    unsigned int v;
    {
      for (i = 0, rp = row_buf + 1; i < row_bytes; i += 1, rp += 1)
      {
        v = *rp;
        sum += (v < 128) ? (v) : (256 - v);
      }

    }
    mins = sum;
  }
  if (filter_to_do == 0x10)
  {
    png_setup_sub_row_only(png_ptr, bpp, row_bytes);
    best_row = png_ptr->try_row;
  }
  else
    if ((filter_to_do & 0x10) != 0)
  {
    size_t sum;
    size_t lmins = mins;
    sum = png_setup_sub_row(png_ptr, bpp, row_bytes, lmins);
    if (sum < mins)
    {
      mins = sum;
      best_row = png_ptr->try_row;
      if (png_ptr->tst_row != 0)
      {
        png_ptr->try_row = png_ptr->tst_row;
        png_ptr->tst_row = best_row;
      }
    }
  }
  if (filter_to_do == 0x20)
  {
    png_setup_up_row_only(png_ptr, row_bytes);
    best_row = png_ptr->try_row;
  }
  else
    if ((filter_to_do & 0x20) != 0)
  {
    size_t sum;
    size_t lmins = mins;
    sum = png_setup_up_row(png_ptr, row_bytes, lmins);
    if (sum < mins)
    {
      mins = sum;
      best_row = png_ptr->try_row;
      if (png_ptr->tst_row != 0)
      {
        png_ptr->try_row = png_ptr->tst_row;
        png_ptr->tst_row = best_row;
      }
    }
  }
  if (filter_to_do == 0x40)
  {
    png_setup_avg_row_only(png_ptr, bpp, row_bytes);
    best_row = png_ptr->try_row;
  }
  else
    if ((filter_to_do & 0x40) != 0)
  {
    size_t sum;
    size_t lmins = mins;
    sum = png_setup_avg_row(png_ptr, bpp, row_bytes, lmins);
    if (sum < mins)
    {
      mins = sum;
      best_row = png_ptr->try_row;
      if (png_ptr->tst_row != 0)
      {
        png_ptr->try_row = png_ptr->tst_row;
        png_ptr->tst_row = best_row;
      }
    }
  }
  if (filter_to_do == 0x80)
  {
    png_setup_paeth_row_only(png_ptr, bpp, row_bytes);
    best_row = png_ptr->try_row;
  }
  else
    if ((filter_to_do & 0x80) != 0)
  {
    size_t sum;
    size_t lmins = mins;
    sum = png_setup_paeth_row(png_ptr, bpp, row_bytes, lmins);
    if (sum < mins)
    {
      best_row = png_ptr->try_row;
      if (png_ptr->tst_row != 0)
      {
        png_ptr->try_row = png_ptr->tst_row;
        png_ptr->tst_row = best_row;
      }
    }
  }
  png_write_filtered_row(png_ptr, best_row, row_info->rowbytes + 1);
}


----------------------------
typedef png_struct *png_structrp
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
***/


void png_write_image(png_structrp png_ptr, png_bytepp image)
{
  png_uint_32 i;
  int pass;
  int num_pass;
  png_bytepp rp;
  if (png_ptr == 0)
  {
    return;
  }
  (void) 0;
  num_pass = png_set_interlace_handling(png_ptr);
  for (pass = 0; pass < num_pass; pass += 1)
  {
    for (i = 0, rp = image; i < png_ptr->height; i += 1, rp += 1)
    {
      png_write_row(png_ptr, *rp);
    }

  }

}


/*** DEPENDENCIES:
void png_write_row(png_structrp png_ptr, png_const_bytep row)
{
  png_row_info row_info;
  if (png_ptr == 0)
  {
    return;
  }
  (void) 0;
  if ((png_ptr->row_number == 0) && (png_ptr->pass == 0))
  {
    if ((png_ptr->mode & 0x400U) == 0)
    {
      png_error(png_ptr, "png_write_info was never called before png_write_row");
    }
    png_write_start_row(png_ptr);
  }
  if ((png_ptr->interlaced != 0) && ((png_ptr->transformations & 0x0002U) != 0))
  {
    helper_png_write_row_1(png_ptr);
  }
  row_info.color_type = png_ptr->color_type;
  row_info.width = png_ptr->usr_width;
  row_info.channels = png_ptr->usr_channels;
  row_info.bit_depth = png_ptr->usr_bit_depth;
  row_info.pixel_depth = (png_byte) (row_info.bit_depth * row_info.channels);
  row_info.rowbytes = (row_info.pixel_depth >= 8) ? (((size_t) row_info.width) * (((size_t) row_info.pixel_depth) >> 3)) : (((((size_t) row_info.width) * ((size_t) row_info.pixel_depth)) + 7) >> 3);
  (void) 0;
  (void) 0;
  (void) 0;
  (void) 0;
  (void) 0;
  (void) 0;
  memcpy(png_ptr->row_buf + 1, row, row_info.rowbytes);
  if ((png_ptr->interlaced && (png_ptr->pass < 6)) && ((png_ptr->transformations & 0x0002U) != 0))
  {
    png_do_write_interlace(&row_info, png_ptr->row_buf + 1, png_ptr->pass);
    if (row_info.width == 0)
    {
      png_write_finish_row(png_ptr);
      return;
    }
  }
  if ((row_info.pixel_depth != png_ptr->pixel_depth) || (row_info.pixel_depth != png_ptr->transformed_pixel_depth))
  {
    png_error(png_ptr, "internal write transform logic error");
  }
  if ((row_info.color_type == (2 | 1)) && (png_ptr->num_palette_max >= 0))
  {
    png_do_check_palette_indexes(png_ptr, &row_info);
  }
  png_write_find_filter(png_ptr, &row_info);
  if (png_ptr->write_row_fn != 0)
  {
    (*png_ptr->write_row_fn)(png_ptr, png_ptr->row_number, png_ptr->pass);
  }
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
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_byte **png_bytepp
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


static void write_unknown_chunks(png_structrp png_ptr, png_const_inforp info_ptr, unsigned int where)
{
  if (info_ptr->unknown_chunks_num != 0)
  {
    png_const_unknown_chunkp up;
    (void) 0;
    for (up = info_ptr->unknown_chunks; up < (info_ptr->unknown_chunks + info_ptr->unknown_chunks_num); up += 1)
    {
      if ((up->location & where) != 0)
      {
        int keep = png_handle_as_unknown(png_ptr, up->name);
        if ((keep != 1) && (((up->name[3] & 0x20) || (keep == 3)) || ((keep == 0) && (png_ptr->unknown_default == 3))))
        {
          if (up->size == 0)
          {
            png_warning(png_ptr, "Writing zero-length unknown chunk");
          }
          png_write_chunk(png_ptr, up->name, up->data, up->size);
        }
      }
    }

  }
}


/*** DEPENDENCIES:
int png_handle_as_unknown(png_const_structrp png_ptr, png_const_bytep chunk_name)
{
  png_const_bytep p;
  png_const_bytep p_end;
  if (((png_ptr == 0) || (chunk_name == 0)) || (png_ptr->num_chunk_list == 0))
  {
    return 0;
  }
  p_end = png_ptr->chunk_list;
  p = p_end + (png_ptr->num_chunk_list * 5);
  do
  {
    p -= 5;
    if (memcmp(chunk_name, p, 4) == 0)
    {
      return p[4];
    }
  }
  while (p > p_end);
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
typedef struct png_struct_def png_struct
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef const png_info *png_const_inforp
----------------------------
typedef const png_unknown_chunk *png_const_unknown_chunkp
----------------------------
void png_write_chunk(png_structrp png_ptr, png_const_bytep chunk_string, png_const_bytep data, size_t length)
{
  png_write_complete_chunk(png_ptr, (((((png_uint_32) (0xff & chunk_string[0])) << 24) | (((png_uint_32) (0xff & chunk_string[1])) << 16)) | (((png_uint_32) (0xff & chunk_string[2])) << 8)) | (((png_uint_32) (0xff & chunk_string[3])) << 0), data, length);
}


----------------------------
***/


void png_write_end(png_structrp png_ptr, png_inforp info_ptr)
{
  (void) 0;
  if (png_ptr == 0)
  {
    return;
  }
  if ((png_ptr->mode & 0x04U) == 0)
  {
    png_error(png_ptr, "No IDATs written into file");
  }
  if (png_ptr->num_palette_max > png_ptr->num_palette)
  {
    png_benign_error(png_ptr, "Wrote palette index exceeding num_palette");
  }
  if (info_ptr != 0)
  {
    write_unknown_chunks(png_ptr, info_ptr, 0x08);
  }
  png_ptr->mode |= 0x08;
  png_write_IEND(png_ptr);
}


/*** DEPENDENCIES:
typedef png_info *png_inforp
----------------------------
static void write_unknown_chunks(png_structrp png_ptr, png_const_inforp info_ptr, unsigned int where)
{
  if (info_ptr->unknown_chunks_num != 0)
  {
    png_const_unknown_chunkp up;
    (void) 0;
    for (up = info_ptr->unknown_chunks; up < (info_ptr->unknown_chunks + info_ptr->unknown_chunks_num); up += 1)
    {
      if ((up->location & where) != 0)
      {
        int keep = png_handle_as_unknown(png_ptr, up->name);
        if ((keep != 1) && (((up->name[3] & 0x20) || (keep == 3)) || ((keep == 0) && (png_ptr->unknown_default == 3))))
        {
          if (up->size == 0)
          {
            png_warning(png_ptr, "Writing zero-length unknown chunk");
          }
          png_write_chunk(png_ptr, up->name, up->data, up->size);
        }
      }
    }

  }
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
void png_error(png_const_structrp png_ptr, png_const_charp error_message)
{
  if ((png_ptr != 0) && (png_ptr->error_fn != 0))
  {
    (*png_ptr->error_fn)((png_structrp) ((void *) ((const void *) png_ptr)), error_message);
  }
  png_default_error(png_ptr, error_message);
}


----------------------------
void png_write_IEND(png_structrp png_ptr)
{
  (void) 0;
  png_write_complete_chunk(png_ptr, (((((png_uint_32) 73) << 24) | (((png_uint_32) 69) << 16)) | (((png_uint_32) 78) << 8)) | (((png_uint_32) 68) << 0), 0, 0);
  png_ptr->mode |= 0x10U;
}


----------------------------
***/


void png_write_info_before_PLTE(png_structrp png_ptr, png_const_inforp info_ptr)
{
  (void) 0;
  if ((png_ptr == 0) || (info_ptr == 0))
  {
    return;
  }
  if ((png_ptr->mode & 0x400U) == 0)
  {
    png_write_sig(png_ptr);
    png_write_IHDR(png_ptr, info_ptr->width, info_ptr->height, info_ptr->bit_depth, info_ptr->color_type, info_ptr->compression_type, info_ptr->filter_type, info_ptr->interlace_type);
    if ((info_ptr->valid & 0x0002U) != 0)
    {
      png_write_sBIT(png_ptr, &info_ptr->sig_bit, info_ptr->color_type);
    }
    write_unknown_chunks(png_ptr, info_ptr, 0x01);
    png_ptr->mode |= 0x400U;
  }
}


/*** DEPENDENCIES:
void png_write_sig(png_structrp png_ptr)
{
  png_byte png_signature[8] = {137, 80, 78, 71, 13, 10, 26, 10};
  png_ptr->io_state = 0x0002 | 0x0010;
  png_write_data(png_ptr, &png_signature[png_ptr->sig_bytes], (size_t) (8 - png_ptr->sig_bytes));
  if (png_ptr->sig_bytes < 3)
  {
    png_ptr->mode |= 0x1000U;
  }
}


----------------------------
void png_write_IHDR(png_structrp png_ptr, png_uint_32 width, png_uint_32 height, int bit_depth, int color_type, int compression_type, int filter_type, int interlace_type)
{
  png_byte buf[13];
  int is_invalid_depth;
  (void) 0;
  switch (color_type)
  {
    case 0:
    {
      switch (bit_depth)
      {
        case 1:

        case 2:

        case 4:

        case 8:

        case 16:
        {
          png_ptr->channels = 1;
          break;
        }

        default:
        {
          png_error(png_ptr, "Invalid bit depth for grayscale image");
        }

      }

      break;
    }

    case 2:
    {
      is_invalid_depth = bit_depth != 8;
      is_invalid_depth = is_invalid_depth && (bit_depth != 16);
      if (is_invalid_depth)
      {
        png_error(png_ptr, "Invalid bit depth for RGB image");
      }
      png_ptr->channels = 3;
      break;
    }

    case 2 | 1:
    {
      switch (bit_depth)
      {
        case 1:

        case 2:

        case 4:

        case 8:
        {
          png_ptr->channels = 1;
          break;
        }

        default:
        {
          png_error(png_ptr, "Invalid bit depth for paletted image");
        }

      }

      break;
    }

    case 4:
    {
      is_invalid_depth = bit_depth != 8;
      is_invalid_depth = is_invalid_depth && (bit_depth != 16);
      if (is_invalid_depth)
      {
        png_error(png_ptr, "Invalid bit depth for grayscale+alpha image");
      }
      png_ptr->channels = 2;
      break;
    }

    case 2 | 4:
    {
      is_invalid_depth = bit_depth != 8;
      is_invalid_depth = is_invalid_depth && (bit_depth != 16);
      if (is_invalid_depth)
      {
        png_error(png_ptr, "Invalid bit depth for RGBA image");
      }
      png_ptr->channels = 4;
      break;
    }

    default:
    {
      png_error(png_ptr, "Invalid image color type specified");
    }

  }

  if (compression_type != 0)
  {
    png_warning(png_ptr, "Invalid compression type specified");
    compression_type = 0;
  }
  if (filter_type != 0)
  {
    png_warning(png_ptr, "Invalid filter type specified");
    filter_type = 0;
  }
  if ((interlace_type != 0) && (interlace_type != 1))
  {
    png_warning(png_ptr, "Invalid interlace type specified");
    interlace_type = 1;
  }
  png_ptr->bit_depth = (png_byte) bit_depth;
  png_ptr->color_type = (png_byte) color_type;
  png_ptr->interlaced = (png_byte) interlace_type;
  png_ptr->compression_type = (png_byte) compression_type;
  png_ptr->width = width;
  png_ptr->height = height;
  png_ptr->pixel_depth = (png_byte) (bit_depth * png_ptr->channels);
  png_ptr->rowbytes = (png_ptr->pixel_depth >= 8) ? (((size_t) width) * (((size_t) png_ptr->pixel_depth) >> 3)) : (((((size_t) width) * ((size_t) png_ptr->pixel_depth)) + 7) >> 3);
  png_ptr->usr_width = png_ptr->width;
  png_ptr->usr_bit_depth = png_ptr->bit_depth;
  png_ptr->usr_channels = png_ptr->channels;
  png_save_uint_32(buf, width);
  png_save_uint_32(buf + 4, height);
  buf[8] = (png_byte) bit_depth;
  buf[9] = (png_byte) color_type;
  buf[10] = (png_byte) compression_type;
  buf[11] = (png_byte) filter_type;
  buf[12] = (png_byte) interlace_type;
  png_write_complete_chunk(png_ptr, (((((png_uint_32) 73) << 24) | (((png_uint_32) 72) << 16)) | (((png_uint_32) 68) << 8)) | (((png_uint_32) 82) << 0), buf, 13);
  if (png_ptr->do_filter == 0x00)
  {
    if ((png_ptr->color_type == (2 | 1)) || (png_ptr->bit_depth < 8))
    {
      png_ptr->do_filter = 0x08;
    }
    else
      png_ptr->do_filter = (((0x08 | 0x10) | 0x20) | 0x40) | 0x80;
  }
  png_ptr->mode = 0x01;
}


----------------------------
static void write_unknown_chunks(png_structrp png_ptr, png_const_inforp info_ptr, unsigned int where)
{
  if (info_ptr->unknown_chunks_num != 0)
  {
    png_const_unknown_chunkp up;
    (void) 0;
    for (up = info_ptr->unknown_chunks; up < (info_ptr->unknown_chunks + info_ptr->unknown_chunks_num); up += 1)
    {
      if ((up->location & where) != 0)
      {
        int keep = png_handle_as_unknown(png_ptr, up->name);
        if ((keep != 1) && (((up->name[3] & 0x20) || (keep == 3)) || ((keep == 0) && (png_ptr->unknown_default == 3))))
        {
          if (up->size == 0)
          {
            png_warning(png_ptr, "Writing zero-length unknown chunk");
          }
          png_write_chunk(png_ptr, up->name, up->data, up->size);
        }
      }
    }

  }
}


----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef png_struct *png_structrp
----------------------------
void png_write_sBIT(png_structrp png_ptr, png_const_color_8p sbit, int color_type)
{
  png_byte buf[4];
  size_t size;
  (void) 0;
  if ((color_type & 2) != 0)
  {
    png_byte maxbits;
    maxbits = (png_byte) ((color_type == (2 | 1)) ? (8) : (png_ptr->usr_bit_depth));
    if ((((((sbit->red == 0) || (sbit->red > maxbits)) || (sbit->green == 0)) || (sbit->green > maxbits)) || (sbit->blue == 0)) || (sbit->blue > maxbits))
    {
      png_warning(png_ptr, "Invalid sBIT depth specified");
      return;
    }
    buf[0] = sbit->red;
    buf[1] = sbit->green;
    buf[2] = sbit->blue;
    size = 3;
  }
  else
  {
    if ((sbit->gray == 0) || (sbit->gray > png_ptr->usr_bit_depth))
    {
      png_warning(png_ptr, "Invalid sBIT depth specified");
      return;
    }
    buf[0] = sbit->gray;
    size = 1;
  }
  if ((color_type & 4) != 0)
  {
    if ((sbit->alpha == 0) || (sbit->alpha > png_ptr->usr_bit_depth))
    {
      png_warning(png_ptr, "Invalid sBIT depth specified");
      return;
    }
    buf[size] = sbit->alpha;
    size += 1;
  }
  png_write_complete_chunk(png_ptr, (((((png_uint_32) 115) << 24) | (((png_uint_32) 66) << 16)) | (((png_uint_32) 73) << 8)) | (((png_uint_32) 84) << 0), buf, size);
}


----------------------------
typedef const png_info *png_const_inforp
----------------------------
***/


void png_write_info(png_structrp png_ptr, png_const_inforp info_ptr)
{
  (void) 0;
  if ((png_ptr == 0) || (info_ptr == 0))
  {
    return;
  }
  png_write_info_before_PLTE(png_ptr, info_ptr);
  if ((info_ptr->valid & 0x0008U) != 0)
  {
    png_write_PLTE(png_ptr, info_ptr->palette, (png_uint_32) info_ptr->num_palette);
  }
  else
    if (info_ptr->color_type == (2 | 1))
  {
    png_error(png_ptr, "Valid palette required for paletted images");
  }
  if ((info_ptr->valid & 0x0010U) != 0)
  {
    png_write_tRNS(png_ptr, info_ptr->trans_alpha, &info_ptr->trans_color, info_ptr->num_trans, info_ptr->color_type);
  }
  if ((info_ptr->valid & 0x0020U) != 0)
  {
    png_write_bKGD(png_ptr, &info_ptr->background, info_ptr->color_type);
  }
  if ((info_ptr->valid & 0x0040U) != 0)
  {
    png_write_hIST(png_ptr, info_ptr->hist, info_ptr->num_palette);
  }
  write_unknown_chunks(png_ptr, info_ptr, 0x02);
}


/*** DEPENDENCIES:
void png_write_info_before_PLTE(png_structrp png_ptr, png_const_inforp info_ptr)
{
  (void) 0;
  if ((png_ptr == 0) || (info_ptr == 0))
  {
    return;
  }
  if ((png_ptr->mode & 0x400U) == 0)
  {
    png_write_sig(png_ptr);
    png_write_IHDR(png_ptr, info_ptr->width, info_ptr->height, info_ptr->bit_depth, info_ptr->color_type, info_ptr->compression_type, info_ptr->filter_type, info_ptr->interlace_type);
    if ((info_ptr->valid & 0x0002U) != 0)
    {
      png_write_sBIT(png_ptr, &info_ptr->sig_bit, info_ptr->color_type);
    }
    write_unknown_chunks(png_ptr, info_ptr, 0x01);
    png_ptr->mode |= 0x400U;
  }
}


----------------------------
void png_write_tRNS(png_structrp png_ptr, png_const_bytep trans_alpha, png_const_color_16p tran, int num_trans, int color_type)
{
  png_byte buf[6];
  (void) 0;
  if (color_type == (2 | 1))
  {
    if ((num_trans <= 0) || (num_trans > ((int) png_ptr->num_palette)))
    {
      png_app_warning(png_ptr, "Invalid number of transparent colors specified");
      return;
    }
    png_write_complete_chunk(png_ptr, (((((png_uint_32) 116) << 24) | (((png_uint_32) 82) << 16)) | (((png_uint_32) 78) << 8)) | (((png_uint_32) 83) << 0), trans_alpha, (size_t) num_trans);
  }
  else
    if (color_type == 0)
  {
    if (tran->gray >= (1 << png_ptr->bit_depth))
    {
      png_app_warning(png_ptr, "Ignoring attempt to write tRNS chunk out-of-range for bit_depth");
      return;
    }
    png_save_uint_16(buf, tran->gray);
    png_write_complete_chunk(png_ptr, (((((png_uint_32) 116) << 24) | (((png_uint_32) 82) << 16)) | (((png_uint_32) 78) << 8)) | (((png_uint_32) 83) << 0), buf, 2);
  }
  else
    if (color_type == 2)
  {
    png_save_uint_16(buf, tran->red);
    png_save_uint_16(buf + 2, tran->green);
    png_save_uint_16(buf + 4, tran->blue);
    if ((png_ptr->bit_depth == 8) && (((buf[0] | buf[2]) | buf[4]) != 0))
    {
      png_app_warning(png_ptr, "Ignoring attempt to write 16-bit tRNS chunk when bit_depth is 8");
      return;
    }
    png_write_complete_chunk(png_ptr, (((((png_uint_32) 116) << 24) | (((png_uint_32) 82) << 16)) | (((png_uint_32) 78) << 8)) | (((png_uint_32) 83) << 0), buf, 6);
  }
  else
  {
    png_app_warning(png_ptr, "Can't write tRNS with an alpha channel");
  }
}


----------------------------
typedef const png_info *png_const_inforp
----------------------------
static void write_unknown_chunks(png_structrp png_ptr, png_const_inforp info_ptr, unsigned int where)
{
  if (info_ptr->unknown_chunks_num != 0)
  {
    png_const_unknown_chunkp up;
    (void) 0;
    for (up = info_ptr->unknown_chunks; up < (info_ptr->unknown_chunks + info_ptr->unknown_chunks_num); up += 1)
    {
      if ((up->location & where) != 0)
      {
        int keep = png_handle_as_unknown(png_ptr, up->name);
        if ((keep != 1) && (((up->name[3] & 0x20) || (keep == 3)) || ((keep == 0) && (png_ptr->unknown_default == 3))))
        {
          if (up->size == 0)
          {
            png_warning(png_ptr, "Writing zero-length unknown chunk");
          }
          png_write_chunk(png_ptr, up->name, up->data, up->size);
        }
      }
    }

  }
}


----------------------------
void png_write_bKGD(png_structrp png_ptr, png_const_color_16p back, int color_type)
{
  png_byte buf[6];
  (void) 0;
  if (color_type == (2 | 1))
  {
    if (back->index >= png_ptr->num_palette)
    {
      png_warning(png_ptr, "Invalid background palette index");
      return;
    }
    buf[0] = back->index;
    png_write_complete_chunk(png_ptr, (((((png_uint_32) 98) << 24) | (((png_uint_32) 75) << 16)) | (((png_uint_32) 71) << 8)) | (((png_uint_32) 68) << 0), buf, 1);
  }
  else
    if ((color_type & 2) != 0)
  {
    png_save_uint_16(buf, back->red);
    png_save_uint_16(buf + 2, back->green);
    png_save_uint_16(buf + 4, back->blue);
    if ((png_ptr->bit_depth == 8) && (((buf[0] | buf[2]) | buf[4]) != 0))
    {
      png_warning(png_ptr, "Ignoring attempt to write 16-bit bKGD chunk when bit_depth is 8");
      return;
    }
    png_write_complete_chunk(png_ptr, (((((png_uint_32) 98) << 24) | (((png_uint_32) 75) << 16)) | (((png_uint_32) 71) << 8)) | (((png_uint_32) 68) << 0), buf, 6);
  }
  else
  {
    if (back->gray >= (1 << png_ptr->bit_depth))
    {
      png_warning(png_ptr, "Ignoring attempt to write bKGD chunk out-of-range for bit_depth");
      return;
    }
    png_save_uint_16(buf, back->gray);
    png_write_complete_chunk(png_ptr, (((((png_uint_32) 98) << 24) | (((png_uint_32) 75) << 16)) | (((png_uint_32) 71) << 8)) | (((png_uint_32) 68) << 0), buf, 2);
  }
}


----------------------------
void png_write_hIST(png_structrp png_ptr, png_const_uint_16p hist, int num_hist)
{
  int i;
  png_byte buf[3];
  (void) 0;
  if (num_hist > ((int) png_ptr->num_palette))
  {
    (void) 0;
    png_warning(png_ptr, "Invalid number of histogram entries specified");
    return;
  }
  png_write_chunk_header(png_ptr, (((((png_uint_32) 104) << 24) | (((png_uint_32) 73) << 16)) | (((png_uint_32) 83) << 8)) | (((png_uint_32) 84) << 0), (png_uint_32) (num_hist * 2));
  for (i = 0; i < num_hist; i += 1)
  {
    png_save_uint_16(buf, hist[i]);
    png_write_chunk_data(png_ptr, buf, 2);
  }

  png_write_chunk_end(png_ptr);
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
void png_write_PLTE(png_structrp png_ptr, png_const_colorp palette, png_uint_32 num_pal)
{
  png_uint_32 max_palette_length;
  png_uint_32 i;
  png_const_colorp pal_ptr;
  png_byte buf[3];
  (void) 0;
  max_palette_length = (png_ptr->color_type == (2 | 1)) ? (1 << png_ptr->bit_depth) : (256);
  if ((num_pal == 0) || (num_pal > max_palette_length))
  {
    if (png_ptr->color_type == (2 | 1))
    {
      png_error(png_ptr, "Invalid number of colors in palette");
    }
    else
    {
      png_warning(png_ptr, "Invalid number of colors in palette");
      return;
    }
  }
  if ((png_ptr->color_type & 2) == 0)
  {
    png_warning(png_ptr, "Ignoring request to write a PLTE chunk in grayscale PNG");
    return;
  }
  png_ptr->num_palette = (png_uint_16) num_pal;
  (void) 0;
  png_write_chunk_header(png_ptr, (((((png_uint_32) 80) << 24) | (((png_uint_32) 76) << 16)) | (((png_uint_32) 84) << 8)) | (((png_uint_32) 69) << 0), (png_uint_32) (num_pal * 3));
  for (i = 0, pal_ptr = palette; i < num_pal; i += 1, pal_ptr += 1)
  {
    buf[0] = pal_ptr->red;
    buf[1] = pal_ptr->green;
    buf[2] = pal_ptr->blue;
    png_write_chunk_data(png_ptr, buf, 3);
  }

  png_write_chunk_end(png_ptr);
  png_ptr->mode |= 0x02;
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
***/


void png_write_png(png_structrp png_ptr, png_inforp info_ptr, int transforms, voidp params)
{
  if ((png_ptr == 0) || (info_ptr == 0))
  {
    return;
  }
  if ((info_ptr->valid & 0x8000U) == 0)
  {
    png_app_error(png_ptr, "no rows for png_write_image to write");
    return;
  }
  png_write_info(png_ptr, info_ptr);
  if ((transforms & 0x0020) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_INVERT_MONO not supported");
  }
  if ((transforms & 0x0040) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_SHIFT not supported");
  }
  if ((transforms & 0x0004) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_PACKING not supported");
  }
  if ((transforms & 0x0100) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_SWAP_ALPHA not supported");
  }
  if ((transforms & (0x1000 | 0x0800)) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_STRIP_FILLER not supported");
  }
  if ((transforms & 0x0080) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_BGR not supported");
  }
  if ((transforms & 0x0200) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_SWAP_ENDIAN not supported");
  }
  if ((transforms & 0x0008) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_PACKSWAP not supported");
  }
  if ((transforms & 0x0400) != 0)
  {
    png_app_error(png_ptr, "PNG_TRANSFORM_INVERT_ALPHA not supported");
  }
  png_write_image(png_ptr, info_ptr->row_pointers);
  png_write_end(png_ptr, info_ptr);
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
void png_write_image(png_structrp png_ptr, png_bytepp image)
{
  png_uint_32 i;
  int pass;
  int num_pass;
  png_bytepp rp;
  if (png_ptr == 0)
  {
    return;
  }
  (void) 0;
  num_pass = png_set_interlace_handling(png_ptr);
  for (pass = 0; pass < num_pass; pass += 1)
  {
    for (i = 0, rp = image; i < png_ptr->height; i += 1, rp += 1)
    {
      png_write_row(png_ptr, *rp);
    }

  }

}


----------------------------
typedef void *voidp
----------------------------
void png_write_end(png_structrp png_ptr, png_inforp info_ptr)
{
  (void) 0;
  if (png_ptr == 0)
  {
    return;
  }
  if ((png_ptr->mode & 0x04U) == 0)
  {
    png_error(png_ptr, "No IDATs written into file");
  }
  if (png_ptr->num_palette_max > png_ptr->num_palette)
  {
    png_benign_error(png_ptr, "Wrote palette index exceeding num_palette");
  }
  if (info_ptr != 0)
  {
    write_unknown_chunks(png_ptr, info_ptr, 0x08);
  }
  png_ptr->mode |= 0x08;
  png_write_IEND(png_ptr);
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef struct png_info_def png_info
----------------------------
void png_write_info(png_structrp png_ptr, png_const_inforp info_ptr)
{
  (void) 0;
  if ((png_ptr == 0) || (info_ptr == 0))
  {
    return;
  }
  png_write_info_before_PLTE(png_ptr, info_ptr);
  if ((info_ptr->valid & 0x0008U) != 0)
  {
    png_write_PLTE(png_ptr, info_ptr->palette, (png_uint_32) info_ptr->num_palette);
  }
  else
    if (info_ptr->color_type == (2 | 1))
  {
    png_error(png_ptr, "Valid palette required for paletted images");
  }
  if ((info_ptr->valid & 0x0010U) != 0)
  {
    png_write_tRNS(png_ptr, info_ptr->trans_alpha, &info_ptr->trans_color, info_ptr->num_trans, info_ptr->color_type);
  }
  if ((info_ptr->valid & 0x0020U) != 0)
  {
    png_write_bKGD(png_ptr, &info_ptr->background, info_ptr->color_type);
  }
  if ((info_ptr->valid & 0x0040U) != 0)
  {
    png_write_hIST(png_ptr, info_ptr->hist, info_ptr->num_palette);
  }
  write_unknown_chunks(png_ptr, info_ptr, 0x02);
}


----------------------------
typedef png_info *png_inforp
----------------------------
***/


void png_set_compression_method(png_structrp png_ptr, int method)
{
  (void) 0;
  if (png_ptr == 0)
  {
    return;
  }
  if (method != 8)
  {
    png_warning(png_ptr, "Only compression method 8 is supported by PNG");
  }
  png_ptr->zlib_method = method;
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


void png_set_write_status_fn(png_structrp png_ptr, png_write_status_ptr write_row_fn)
{
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->write_row_fn = write_row_fn;
}


/*** DEPENDENCIES:
typedef void (*png_write_status_ptr)(png_structp, png_uint_32, int)
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


void png_write_rows(png_structrp png_ptr, png_bytepp row, png_uint_32 num_rows)
{
  png_uint_32 i;
  png_bytepp rp;
  (void) 0;
  if (png_ptr == 0)
  {
    return;
  }
  for (i = 0, rp = row; i < num_rows; i += 1, rp += 1)
  {
    png_write_row(png_ptr, *rp);
  }

}


/*** DEPENDENCIES:
void png_write_row(png_structrp png_ptr, png_const_bytep row)
{
  png_row_info row_info;
  if (png_ptr == 0)
  {
    return;
  }
  (void) 0;
  if ((png_ptr->row_number == 0) && (png_ptr->pass == 0))
  {
    if ((png_ptr->mode & 0x400U) == 0)
    {
      png_error(png_ptr, "png_write_info was never called before png_write_row");
    }
    png_write_start_row(png_ptr);
  }
  if ((png_ptr->interlaced != 0) && ((png_ptr->transformations & 0x0002U) != 0))
  {
    helper_png_write_row_1(png_ptr);
  }
  row_info.color_type = png_ptr->color_type;
  row_info.width = png_ptr->usr_width;
  row_info.channels = png_ptr->usr_channels;
  row_info.bit_depth = png_ptr->usr_bit_depth;
  row_info.pixel_depth = (png_byte) (row_info.bit_depth * row_info.channels);
  row_info.rowbytes = (row_info.pixel_depth >= 8) ? (((size_t) row_info.width) * (((size_t) row_info.pixel_depth) >> 3)) : (((((size_t) row_info.width) * ((size_t) row_info.pixel_depth)) + 7) >> 3);
  (void) 0;
  (void) 0;
  (void) 0;
  (void) 0;
  (void) 0;
  (void) 0;
  memcpy(png_ptr->row_buf + 1, row, row_info.rowbytes);
  if ((png_ptr->interlaced && (png_ptr->pass < 6)) && ((png_ptr->transformations & 0x0002U) != 0))
  {
    png_do_write_interlace(&row_info, png_ptr->row_buf + 1, png_ptr->pass);
    if (row_info.width == 0)
    {
      png_write_finish_row(png_ptr);
      return;
    }
  }
  if ((row_info.pixel_depth != png_ptr->pixel_depth) || (row_info.pixel_depth != png_ptr->transformed_pixel_depth))
  {
    png_error(png_ptr, "internal write transform logic error");
  }
  if ((row_info.color_type == (2 | 1)) && (png_ptr->num_palette_max >= 0))
  {
    png_do_check_palette_indexes(png_ptr, &row_info);
  }
  png_write_find_filter(png_ptr, &row_info);
  if (png_ptr->write_row_fn != 0)
  {
    (*png_ptr->write_row_fn)(png_ptr, png_ptr->row_number, png_ptr->pass);
  }
}


----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef png_byte **png_bytepp
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef png_byte *png_bytep
----------------------------
***/


