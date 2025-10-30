png_uint_32 png_access_version_number(void)
{
  return (png_uint_32) 10640;
}


/*** DEPENDENCIES:
***/


static int png_gt(size_t a, size_t b)
{
  return a > b;
}


/*** DEPENDENCIES:
***/


png_voidp png_get_io_ptr(png_const_structrp png_ptr)
{
  if (png_ptr == 0)
  {
    return 0;
  }
  return png_ptr->io_ptr;
}


/*** DEPENDENCIES:
typedef const png_struct *png_const_structrp
----------------------------
***/


png_const_charp png_get_copyright(png_const_structrp png_ptr)
{
  (void) png_ptr;
  return "\nlibpng version 1.6.40\nCopyright (c) 2018-2023 Cosmin Truta\nCopyright (c) 1998-2002,2004,2006-2018 Glenn Randers-Pehrson\nCopyright (c) 1996-1997 Andreas Dilger\nCopyright (c) 1995-1996 Guy Eric Schalnat, Group 42, Inc.\n";
}


/*** DEPENDENCIES:
typedef const png_struct *png_const_structrp
----------------------------
***/


png_const_charp png_get_header_ver(png_const_structrp png_ptr)
{
  (void) png_ptr;
  return "1.6.40";
}


/*** DEPENDENCIES:
typedef const png_struct *png_const_structrp
----------------------------
***/


png_const_charp png_get_header_version(png_const_structrp png_ptr)
{
  (void) png_ptr;
  return " libpng version 1.6.40 - June 21, 2023\n\n";
}


/*** DEPENDENCIES:
typedef const png_struct *png_const_structrp
----------------------------
***/


int png_sig_cmp(png_const_bytep sig, size_t start, size_t num_to_check)
{
  png_byte png_signature[8] = {137, 80, 78, 71, 13, 10, 26, 10};
  if (num_to_check > 8)
  {
    num_to_check = 8;
  }
  else
    if (num_to_check < 1)
  {
    return -1;
  }
  if (start > 7)
  {
    return -1;
  }
  if ((start + num_to_check) > 8)
  {
    num_to_check = 8 - start;
  }
  return (int) memcmp(&sig[start], &png_signature[start], num_to_check);
}


/*** DEPENDENCIES:
typedef const png_byte *png_const_bytep
----------------------------
typedef unsigned char png_byte
----------------------------
***/


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


/*** DEPENDENCIES:
typedef const png_byte *png_const_bytep
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


png_const_charp png_get_libpng_ver(png_const_structrp png_ptr)
{
  return png_get_header_ver(png_ptr);
}


/*** DEPENDENCIES:
png_const_charp png_get_header_ver(png_const_structrp png_ptr)
{
  (void) png_ptr;
  return "1.6.40";
}


----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


void png_zstream_error(png_structrp png_ptr, int ret)
{
  if (png_ptr->zstream.msg == 0)
  {
    switch (ret)
    {
      default:

      case 0:
      {
        png_ptr->zstream.msg = "unexpected zlib return code";
        break;
      }

      case 1:
      {
        png_ptr->zstream.msg = "unexpected end of LZ stream";
        break;
      }

      case 2:
      {
        png_ptr->zstream.msg = "missing LZ dictionary";
        break;
      }

      case -1:
      {
        png_ptr->zstream.msg = "zlib IO error";
        break;
      }

      case -2:
      {
        png_ptr->zstream.msg = "bad parameters to zlib";
        break;
      }

      case -3:
      {
        png_ptr->zstream.msg = "damaged LZ stream";
        break;
      }

      case -4:
      {
        png_ptr->zstream.msg = "insufficient memory";
        break;
      }

      case -5:
      {
        png_ptr->zstream.msg = "truncated";
        break;
      }

      case -6:
      {
        png_ptr->zstream.msg = "unsupported zlib version";
        break;
      }

      case -7:
      {
        png_ptr->zstream.msg = "unexpected zlib return";
        break;
      }

    }

  }
}


/*** DEPENDENCIES:
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


void png_zfree(voidpf png_ptr, voidpf ptr)
{
  png_free(png_ptr, ptr);
}


/*** DEPENDENCIES:
typedef void *voidpf
----------------------------
typedef void *voidp
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
***/


voidpf png_zalloc(voidpf png_ptr, uInt items, uInt size)
{
  png_alloc_size_t num_bytes = size;
  if (png_ptr == 0)
  {
    return 0;
  }
  if (items >= ((~((png_alloc_size_t) 0)) / size))
  {
    png_warning(png_ptr, "Potential overflow in png_zalloc()");
    return 0;
  }
  num_bytes *= items;
  return png_malloc_warn(png_ptr, num_bytes);
}


/*** DEPENDENCIES:
typedef size_t png_alloc_size_t
----------------------------
typedef void *voidp
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
typedef unsigned int uInt
----------------------------
typedef void *voidpf
----------------------------
***/


int png_user_version_check(png_structrp png_ptr, png_const_charp user_png_ver)
{
  if (user_png_ver != 0)
  {
    int i = -1;
    int found_dots = 0;
    do
    {
      i += 1;
      if (user_png_ver[i] != "1.6.40"[i])
      {
        png_ptr->flags |= 0x20000U;
      }
      if (user_png_ver[i] == '.')
      {
        found_dots += 1;
      }
    }
    while (((found_dots < 2) && (user_png_ver[i] != 0)) && ("1.6.40"[i] != 0));
  }
  else
    png_ptr->flags |= 0x20000U;
  if ((png_ptr->flags & 0x20000U) != 0)
  {
    size_t pos = 0;
    char m[128];
    pos = png_safecat(m, sizeof(m), pos, "Application built with libpng-");
    pos = png_safecat(m, sizeof(m), pos, user_png_ver);
    pos = png_safecat(m, sizeof(m), pos, " but running with ");
    pos = png_safecat(m, sizeof(m), pos, "1.6.40");
    (void) pos;
    png_warning(png_ptr, m);
    return 0;
  }
  return 1;
}


/*** DEPENDENCIES:
size_t png_safecat(png_charp buffer, size_t bufsize, size_t pos, png_const_charp string)
{
  if ((buffer != 0) && (pos < bufsize))
  {
    if (string != 0)
    {
      while (((*string) != '\0') && (pos < (bufsize - 1)))
      {
        buffer[pos] = *string;
        string += 1;
        pos += 1;
      }

    }
    buffer[pos] = '\0';
  }
  return pos;
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
typedef const char *png_const_charp
----------------------------
***/


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


/*** DEPENDENCIES:
void png_zfree(voidpf png_ptr, voidpf ptr)
{
  png_free(png_ptr, ptr);
}


----------------------------
typedef void (*png_free_ptr)(png_structp, png_voidp)
----------------------------
voidpf png_zalloc(voidpf png_ptr, uInt items, uInt size)
{
  png_alloc_size_t num_bytes = size;
  if (png_ptr == 0)
  {
    return 0;
  }
  if (items >= ((~((png_alloc_size_t) 0)) / size))
  {
    png_warning(png_ptr, "Potential overflow in png_zalloc()");
    return 0;
  }
  num_bytes *= items;
  return png_malloc_warn(png_ptr, num_bytes);
}


----------------------------
typedef void *voidp
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
typedef void (*png_error_ptr)(png_structp, png_const_charp)
----------------------------
typedef const char *png_const_charp
----------------------------
int png_user_version_check(png_structrp png_ptr, png_const_charp user_png_ver)
{
  if (user_png_ver != 0)
  {
    int i = -1;
    int found_dots = 0;
    do
    {
      i += 1;
      if (user_png_ver[i] != "1.6.40"[i])
      {
        png_ptr->flags |= 0x20000U;
      }
      if (user_png_ver[i] == '.')
      {
        found_dots += 1;
      }
    }
    while (((found_dots < 2) && (user_png_ver[i] != 0)) && ("1.6.40"[i] != 0));
  }
  else
    png_ptr->flags |= 0x20000U;
  if ((png_ptr->flags & 0x20000U) != 0)
  {
    size_t pos = 0;
    char m[128];
    pos = png_safecat(m, sizeof(m), pos, "Application built with libpng-");
    pos = png_safecat(m, sizeof(m), pos, user_png_ver);
    pos = png_safecat(m, sizeof(m), pos, " but running with ");
    pos = png_safecat(m, sizeof(m), pos, "1.6.40");
    (void) pos;
    png_warning(png_ptr, m);
    return 0;
  }
  return 1;
}


----------------------------
typedef struct png_struct_def png_struct
----------------------------
typedef png_struct *png_structrp
----------------------------
void png_set_error_fn(png_structrp png_ptr, png_voidp error_ptr, png_error_ptr error_fn, png_error_ptr warning_fn)
{
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->error_ptr = error_ptr;
  png_ptr->error_fn = error_fn;
  png_ptr->warning_fn = warning_fn;
}


----------------------------
typedef png_voidp (*png_malloc_ptr)(png_structp, png_alloc_size_t)
----------------------------
typedef void *png_voidp
----------------------------
***/


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


/*** DEPENDENCIES:
typedef unsigned int png_uint_32
----------------------------
typedef const png_struct *png_const_structrp
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
typedef png_info *png_inforp
----------------------------
***/


void png_calculate_crc(png_structrp png_ptr, png_const_bytep ptr, size_t length)
{
  int need_crc = 1;
  if ((1 & (png_ptr->chunk_name >> 29)) != 0)
  {
    if ((png_ptr->flags & (0x0100U | 0x0200U)) == (0x0100U | 0x0200U))
    {
      need_crc = 0;
    }
  }
  else
  {
    if ((png_ptr->flags & 0x0800U) != 0)
    {
      need_crc = 0;
    }
  }
  if ((need_crc != 0) && (length > 0))
  {
    uLong crc = png_ptr->crc;
    do
    {
      uInt safe_length = (uInt) length;
      if (safe_length == 0)
      {
        safe_length = (uInt) (-1);
      }
      crc = crc32(crc, ptr, safe_length);
      ptr += safe_length;
      length -= safe_length;
    }
    while (length > 0);
    png_ptr->crc = (png_uint_32) crc;
  }
}


/*** DEPENDENCIES:
typedef unsigned long uLong
----------------------------
typedef const png_byte *png_const_bytep
----------------------------
typedef unsigned int uInt
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
unsigned long crc32(unsigned long crc, const unsigned char *buf, uInt len)
{
  return crc32_z(crc, buf, len);
}


----------------------------
***/


int png_chunk_unknown_handling(png_const_structrp png_ptr, png_uint_32 chunk_name)
{
  png_byte chunk_string[5];
  (void) (((void) ((((char *) chunk_string)[0] = (char) ((chunk_name >> 24) & 0xff), ((char *) chunk_string)[1] = (char) ((chunk_name >> 16) & 0xff), ((char *) chunk_string)[2] = (char) ((chunk_name >> 8) & 0xff), ((char *) chunk_string)[3] = (char) (chunk_name & 0xff))), ((char *) chunk_string)[4] = 0));
  return png_handle_as_unknown(png_ptr, chunk_string);
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
typedef unsigned int png_uint_32
----------------------------
typedef unsigned char png_byte
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


void png_reset_crc(png_structrp png_ptr)
{
  png_ptr->crc = (png_uint_32) crc32(0, 0, 0);
}


/*** DEPENDENCIES:
unsigned long crc32(unsigned long crc, const unsigned char *buf, uInt len)
{
  return crc32_z(crc, buf, len);
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


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


/*** DEPENDENCIES:
typedef unsigned int png_uint_32
----------------------------
typedef const png_struct *png_const_structrp
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
static int png_gt(size_t a, size_t b)
{
  return a > b;
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


void png_set_sig_bytes(png_structrp png_ptr, int num_bytes)
{
  unsigned int nb = (unsigned int) num_bytes;
  (void) 0;
  if (png_ptr == 0)
  {
    return;
  }
  if (num_bytes < 0)
  {
    nb = 0;
  }
  if (nb > 8)
  {
    png_error(png_ptr, "Too many bytes for PNG signature");
  }
  png_ptr->sig_bytes = (png_byte) nb;
}


/*** DEPENDENCIES:
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


png_infop png_create_info_struct(png_const_structrp png_ptr)
{
  png_inforp info_ptr;
  (void) 0;
  if (png_ptr == 0)
  {
    return 0;
  }
  info_ptr = png_malloc_base(png_ptr, sizeof(*info_ptr));
  if (info_ptr != 0)
  {
    memset(info_ptr, 0, sizeof(*info_ptr));
  }
  return info_ptr;
}


/*** DEPENDENCIES:
typedef struct png_info_def png_info
----------------------------
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
typedef png_info *png_inforp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
***/


void png_data_freer(png_const_structrp png_ptr, png_inforp info_ptr, int freer, png_uint_32 mask)
{
  (void) 0;
  if ((png_ptr == 0) || (info_ptr == 0))
  {
    return;
  }
  if (freer == 1)
  {
    info_ptr->free_me |= mask;
  }
  else
    if (freer == 2)
  {
    info_ptr->free_me &= ~mask;
  }
  else
    png_error(png_ptr, "Unknown freer parameter in png_data_freer");
}


/*** DEPENDENCIES:
typedef unsigned int png_uint_32
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
typedef struct png_info_def png_info
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
typedef png_info **png_infopp
----------------------------
typedef const png_struct *png_const_structrp
----------------------------
typedef png_info *png_infop
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
typedef png_info *png_inforp
----------------------------
***/


int png_reset_zstream(png_structrp png_ptr)
{
  if (png_ptr == 0)
  {
    return -2;
  }
  return inflateReset(&png_ptr->zstream);
}


/*** DEPENDENCIES:
int inflateReset(z_streamp strm)
{
  struct inflate_state *state;
  unsigned int state_idx = 0;
  if (inflateStateCheck(strm))
  {
    return -2;
  }
  state_idx = (struct inflate_state *) strm->state_idx;
  state->wsize = 0;
  state->whave = 0;
  state->wnext = 0;
  return inflateResetKeep(strm);
}


----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


void png_init_io(png_structrp png_ptr, png_FILE_p fp)
{
  (void) 0;
  if (png_ptr == 0)
  {
    return;
  }
  png_ptr->io_ptr = (png_voidp) fp;
}


/*** DEPENDENCIES:
typedef FILE *png_FILE_p
----------------------------
typedef png_struct *png_structrp
----------------------------
typedef struct png_struct_def png_struct
----------------------------
***/


void png_save_int_32(png_bytep buf, png_int_32 i)
{
  png_save_uint_32(buf, (png_uint_32) i);
}


/*** DEPENDENCIES:
typedef int png_int_32
----------------------------
typedef png_byte *png_bytep
----------------------------
typedef unsigned char png_byte
----------------------------
void png_save_uint_32(png_bytep buf, png_uint_32 i)
{
  buf[0] = (png_byte) ((i >> 24) & 0xffU);
  buf[1] = (png_byte) ((i >> 16) & 0xffU);
  buf[2] = (png_byte) ((i >> 8) & 0xffU);
  buf[3] = (png_byte) (i & 0xffU);
}


----------------------------
***/


void png_info_init_3(png_infopp ptr_ptr, size_t png_info_struct_size)
{
  png_inforp info_ptr = *ptr_ptr;
  (void) 0;
  if (info_ptr == 0)
  {
    return;
  }
  if ((sizeof(png_info)) > png_info_struct_size)
  {
    *ptr_ptr = 0;
    free(info_ptr);
    info_ptr = png_malloc_base(0, sizeof(*info_ptr));
    if (info_ptr == 0)
    {
      return;
    }
    *ptr_ptr = info_ptr;
  }
  memset(info_ptr, 0, sizeof(*info_ptr));
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
typedef png_info **png_infopp
----------------------------
typedef png_info *png_infop
----------------------------
typedef struct png_info_def png_info
----------------------------
typedef png_info *png_inforp
----------------------------
***/


