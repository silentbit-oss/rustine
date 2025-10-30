png_bytepp pngx_malloc_rows_extended(png_structp png_ptr, png_infop info_ptr, pngx_alloc_size_t min_row_size, int filler)
{
  pngx_alloc_size_t row_size;
  png_bytep row;
  png_bytepp rows;
  png_uint_32 height;
  png_uint_32 i;
  height = png_get_image_height(png_ptr, info_ptr);
  if (height == 0)
  {
    png_error(png_ptr, "Missing IHDR");
  }
  row_size = png_get_rowbytes(png_ptr, info_ptr);
  if ((row_size == 0) || (((pngx_alloc_size_t) height) > (((pngx_alloc_size_t) (-1)) / (sizeof(png_bytep)))))
  {
    png_error(png_ptr, "Can't handle exceedingly large image dimensions");
  }
  if (row_size < min_row_size)
  {
    row_size = min_row_size;
  }
  png_free_data(png_ptr, info_ptr, 0x0040U, 0);
  rows = (png_bytepp) png_malloc(png_ptr, (pngx_alloc_size_t) (height * (sizeof(png_bytep))));
  if (rows == 0)
  {
    return 0;
  }
  for (i = 0; i < height; i += 1)
  {
    row = (png_bytep) png_malloc(png_ptr, row_size);
    if (row == 0)
    {
      while (i > 0)
      {
        i -= 1;
        png_free(png_ptr, rows[i]);
      }

      png_free(png_ptr, rows);
      return 0;
    }
    if (filler >= 0)
    {
      memset(row, filler, row_size);
    }
    rows[i] = row;
  }

  png_set_rows(png_ptr, info_ptr, rows);
  return rows;
}


/*** DEPENDENCIES:
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
typedef png_struct *png_structp
----------------------------
typedef unsigned char png_byte
----------------------------
typedef unsigned int png_uint_32
----------------------------
typedef png_alloc_size_t pngx_alloc_size_t
----------------------------
size_t png_get_rowbytes(png_const_structrp png_ptr, png_const_inforp info_ptr)
{
  if ((png_ptr != 0) && (info_ptr != 0))
  {
    return info_ptr->rowbytes;
  }
  return 0;
}


----------------------------
typedef png_byte **png_bytepp
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
typedef png_info *png_infop
----------------------------
typedef struct png_struct_def png_struct
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


png_bytepp pngx_malloc_rows(png_structp png_ptr, png_infop info_ptr, int filler)
{
  return pngx_malloc_rows_extended(png_ptr, info_ptr, 0, filler);
}


/*** DEPENDENCIES:
typedef png_struct *png_structp
----------------------------
typedef png_info *png_infop
----------------------------
png_bytepp pngx_malloc_rows_extended(png_structp png_ptr, png_infop info_ptr, pngx_alloc_size_t min_row_size, int filler)
{
  pngx_alloc_size_t row_size;
  png_bytep row;
  png_bytepp rows;
  png_uint_32 height;
  png_uint_32 i;
  height = png_get_image_height(png_ptr, info_ptr);
  if (height == 0)
  {
    png_error(png_ptr, "Missing IHDR");
  }
  row_size = png_get_rowbytes(png_ptr, info_ptr);
  if ((row_size == 0) || (((pngx_alloc_size_t) height) > (((pngx_alloc_size_t) (-1)) / (sizeof(png_bytep)))))
  {
    png_error(png_ptr, "Can't handle exceedingly large image dimensions");
  }
  if (row_size < min_row_size)
  {
    row_size = min_row_size;
  }
  png_free_data(png_ptr, info_ptr, 0x0040U, 0);
  rows = (png_bytepp) png_malloc(png_ptr, (pngx_alloc_size_t) (height * (sizeof(png_bytep))));
  if (rows == 0)
  {
    return 0;
  }
  for (i = 0; i < height; i += 1)
  {
    row = (png_bytep) png_malloc(png_ptr, row_size);
    if (row == 0)
    {
      while (i > 0)
      {
        i -= 1;
        png_free(png_ptr, rows[i]);
      }

      png_free(png_ptr, rows);
      return 0;
    }
    if (filler >= 0)
    {
      memset(row, filler, row_size);
    }
    rows[i] = row;
  }

  png_set_rows(png_ptr, info_ptr, rows);
  return rows;
}


----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef struct png_info_def png_info
----------------------------
***/


